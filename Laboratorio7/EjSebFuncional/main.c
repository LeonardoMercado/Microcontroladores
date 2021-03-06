#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

void SCI_send(char);
unsigned char flag_rx;		//variable dummy para mecanismo que limpia interrupcion de SCI_rx

void kbi_init() {
	KBI2SC_KBIE = 0;//deshabilitar interrupcion para evitar falsas interrupciones
	KBI2SC_KBIMOD = 0;			//interrupcion por solo flanco
	KBI2ES = 0x00;				//interrupcion por flanco de bajada
	KBI2PE = 0x80;		//habilitacion de pines como fuente de interrupcion
	KBI2SC_KBACK = 0;			//bandera para evitar falsas interrupciones
	KBI2SC_KBIE = 1;			//habilitacion de la interrupcion por KBI
}
interrupt 18 void kbi_isr() {
	KBI2SC_KBACK = 1;				//acknowledge de la interrupcion por kbi
	SCI_send(144);
}

interrupt VectorNumber_Vsci2rx void sci_rx(){
	flag_rx=SCI2S1_RDRF;
	if(SCI2D == 101){
			PTCD_PTCD0 = !PTCD_PTCD0;
		}
}

void SCI_init(){
	SCI2BDH = 0;
	SCI2BDL = 14;
	SCI2C1 = 0x00;
	SCI2C2_TE = 1;
	SCI2C2_RE = 1;
	SCI2C2_RIE = 1;
}

void SCI_send(char dato){
	while(SCI2S1_TDRE == 0);
	SCI2D = dato;
	return;
}

void main(void) {
	SOPT1 = 0x02;
	PTDDD = 0x00;				//inicializacion del puerto D
	PTDPE = 0x80;				//enable resistencias pull	
	
	PTCDD_PTCDD0 = 1;
	PTCD_PTCD0 = 1;
	
	kbi_init();
	SCI_init();
	
  EnableInterrupts;  

  for(;;) {
    
  } /* loop forever */
  /* please make sure that you never leave main */
}
