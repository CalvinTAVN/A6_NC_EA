/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{
   /* Your code here */
   unsigned int src;

   assert (puiDest != NULL);
   /*assert(uiSrc != NULL);
   assert(uiSrcStartBit != NULL);
   assert(puiDest != NULL);
   assert(uiDestStartBit != NULL);
   assert(uiNumBits != NULL);*/
   
   src = uiSrc;
   src = src  >> uiSrcStartBit;
   src = src << (32 - uiNumBits);
   src = src>> (32 - uiNumBits);
   src = src << uiDestStartBit;
   *puiDest = (*puiDest | src);
   
   

}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   /* Your code here */
   unsigned int uiInstr;

   /* Base Instruction Code */
   uiInstr = 0x52800000;

   /* Register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* Placing uiReg, number inserted in Instruction*/
   setField(iImmed, 0, &uiInstr, 5, 16);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   /* Your code here */
   unsigned int uiInstr;
   
   /* Base Instruction Code*/
   uiInstr = 0x39000000;

   /*transferring from register uiFromReg to  Rt in uiInstr.*/
   setField(uiFromReg, 0, &uiInstr, 0, 5);

   /* Transferring from r*/
   setField(uiToReg, 0, &uiInstr, 5, 5);

   return uiInstr;

}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   /* Your code here */
   unsigned int uiInstr;
   signed int cutAddress;

   /* Base Instruction Code*/
   uiInstr = 0x14000000;

   /* Must cut the address to fit into instruction*/
   cutAddress = (signed int)(ulAddr - ulAddrOfThisInstr);

   /* If the label is encoded as imm26 times 4,
      then imm26 is cutAddress divided by 4*/
   cutAddress /= 4;
   
   /* Transferring cut address*/
   setField(cutAddress, 0, &uiInstr, 0, 26);

   return uiInstr;
}
