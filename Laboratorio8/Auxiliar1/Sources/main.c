#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

char dato[] = "1023";
unsigned short varDelay;

void SCI_send(char dato);
void sendString(char dato[]);
void delay(unsigned short);

void setSCI() {
	SCGC1_SCI2 = 1;
    SCI2BDH = 0x00;
    SCI2BDL = 14;
    SCI2C1 = 0x00;
    SCI2C2_TE = 1;
}


void SCI_send(char dato){
	//byte bandera;
	while(SCI2S1_TDRE == 0);
	//bandera = SCI2S1;
	SCI2D = dato;
	return;
}
void sendString(char data[]){
    unsigned volatile int i = 0;
	while(data[i]!='\0'){
		SCI_send(data[i]);
		i++;
    }
	SCI_send('\n');
	
}


void main(void) {
  SOPT1 = 0x02;
  setSCI();
	

	
  EnableInterrupts;
  /* include your code here */

  

  for(;;) {
	 sendString(dato);
	 delay(1000);/* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}




void delay(unsigned short tope) {
	for (varDelay = 0; varDelay < tope; ++varDelay) {
		
	}
}
