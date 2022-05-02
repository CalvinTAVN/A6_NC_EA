/*---------------------------------------------*/
/*createdataAplus.c                            */
/*Author: Calvin Nguyen and Alex Eng           */
/*---------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "miniassembler.h"

/*Main function creates a file called dataA or overwrites
  dataA if it already exists. outputs a new file called 
  dataA that contains our name, null chars, and an address */
int main(void)
{

   /*variable to traverse loop*/
   int i;

   /*file to be added on*/
   FILE *psFile;

   /*address of "grade = B"*/
   unsigned long address;

   unsigned int instructions;
   
   /*assigning values*/
   psFile = fopen("dataAplus", "w");
   address = 0x0000000000420060;
 
   /*writing our name into the file */
   /* Write total of 48 bytes*/
   /*writes 8 bytes*/
   fprintf(psFile, "%c", 'C'); /* offset 32*/
   fprintf(psFile, "%c", 'a'); /* 33  */
   fprintf(psFile, "%c", 'l'); /* 34*/
   fprintf(psFile, "%c", 'v'); /* 35*/
   fprintf(psFile, "%c", 'i'); /* *36*/
   fprintf(psFile, "%c", 'n'); /* 37*/
   fprintf(psFile, "%c", '\0'); /* 0x42005E*/ /* 38*/
   fprintf(psFile, "%c", '\0'); /*0x42005F*/

   
   /* Instructions that are followed to get A+ Grade*/
   /* Writing 20 bytes*/
   instructions = MiniAssembler_adr(2, 0x420044, 0x420060); /*gets the address of grade */
   fwrite(&instructions, sizeof(unsigned int), 1, psFile);

   
   instructions = MiniAssembler_mov(1, 0x41); /*moves 0x41(A) into x1*/ /* 0x420064*/
   fwrite(&instructions, sizeof(unsigned int), 1, psFile);

   /* 0x420068*/
   instructions = MiniAssembler_strb(1, 2);  /* stores A which is 1 byte into x0 register 
                                                which is grade*/
   fwrite(&instructions, sizeof(unsigned int), 1, psFile);
   
   /*0x42006C */
   instructions = MiniAssembler_adr(0, 0x420071, 0x42006C);
   fwrite(&instructions, sizeof(unsigned int), 1, psFile);

   /* 0x420070*/
   instructions = MiniAssembler_b(0x40086c, 0x420070);   /* Branch to printing Grade*/
   fwrite(&instructions, sizeof(unsigned int), 1, psFile);

   /* used 28 bytes out of 48 */

   /* Writing 20 bytes */
   fprintf(psFile, "%c", '%'); /* 0x420071 */
   fprintf(psFile, "%c", 'c');
   fprintf(psFile, "%c", '+');
   fprintf(psFile, "%c", ' '); /*4 */
   fprintf(psFile, "%c", 'L'); /* i*/
   fprintf(psFile, "%c", 's');
   fprintf(psFile, "%c", ' ');
   fprintf(psFile, "%c", 'y');/* 4 */
   fprintf(psFile, "%c", 'o');
   fprintf(psFile, "%c", 'u');
   fprintf(psFile, "%c", 'r');
   fprintf(psFile, "%c", ' '); /*4 */
   fprintf(psFile, "%c", 'g');
   fprintf(psFile, "%c", 'r');
   fprintf(psFile, "%c", 'a');
   fprintf(psFile, "%c", 'd'); /* 4*/
   fprintf(psFile, "%c", 'e');
   fprintf(psFile, "%c", '.');
   fprintf(psFile, "%c", '\n');
   fprintf(psFile, "%c", '\0'); /*4 */
   
   /* 20 bytes used*/
   /* all 48 bytes used*/
   
   /*writing 24 null chars */
   /*
   for (i = 0; i < 24; i++)
      fprintf(psFile, "%c", '\0');
   */
   
   /*going to address 0x420060
     added 10 additional hex values since 400858 is only 3 bytes
     so we need 5 more bytes = 10 digits of HEX
     0x0000000000400858 */
   fwrite(&address, sizeof(unsigned long), 1, psFile);
   

   fclose(psFile);

   return 0;
      
}
