/*
 * Simon.c
 *
 * Created: 4/20/2023 3:10:19 PM
 * Author : brackermh
 */ 

/*
 * GccApplication4.c
 *
 * Created: 4/20/2023 11:36:58 AM
 * Author : Matt Bracker
 */ 

//Designed for ATmega328PB 

#include <avr/io.h>
#include <stdlib.h>

void playred(){
	//Turn on red led
	//Play sound for red
	PORTC = PORTC | 0x01;
	OCR0A = 0x4D;
	TCCR0B = 0x05;
	for(unsigned int i=0; i<32000; i++){}

}

void playblue(){
	//Turn on blue led and play sound for blue
	PORTC = PORTC | 0x04;
	OCR0A = 0x26;
	TCCR0B = 0x05;
	for(unsigned int i=0; i<32000; i++){}
}

void playgreen(){
	//Turn on green LED and play sound for green
	PORTC = PORTC | 0x02;
	OCR0A = 0x19;
	TCCR0B = 0x05;
	for(unsigned int i=0; i<32000; i++){}
}

void playyellow(){
	//Turn on yellow LED and play sound for yellow
	PORTC = PORTC | 0x08;
	OCR0A = 0x0D;
	TCCR0B = 0x05;
	for(unsigned int i=0; i<32000; i++){}
}

int button() {
	int ret = -1;
	if ((PINB & 0x08) != 0) {	//Yellow
		playyellow();
		ret = 0;
	}
	else{
		PORTC = 0x00;
	}
	if ((PINB & 0x04) != 0) {		//Blue
		playblue();
		ret = 1;
	}
	else{
		PORTC = 0x00;
	}
	if ((PINB & 0x02) != 0) {		//Green
		playgreen();
		ret = 2;
	}
	else{
		PORTC = 0x00;
	}
	if ((PINB & 0x01) != 0) {		//Red
		playred();
		ret = 3;
	}
	else{
		PORTC = 0x00;
	}
	playnone();
	return ret;
}


void playlose(){
	playnone();
	TCCR0B = 0x05;
	for(int i=0; i<5; i++) {
	PORTC |= 0x0F; // Turn lights on
	OCR0A = 0x26;
	for(unsigned int i=0; i<64000; i++){
		for(unsigned int j=0; j<5; j++) {}
	}
	PORTC &= ~0x0F; // Turn lights off
	OCR0A = 0x4D;
	for(unsigned int i=0; i<64000; i++){
		for(unsigned int j=0; j<5; j++) {}
	}
	}
	TCCR0B = 0x00;
}
	
void playwin(){
	playnone();
	TCCR0B = 0x05;
	for(int i=0; i<10; i++) {
	PORTC |= 0x0F; // Turn lights on
	OCR0A = 0x0D;
	for(unsigned int i=0; i<64000; i++){
	}
	PORTC &= ~0x0F; // Turn lights off
	OCR0A = 0x00;
	for(unsigned int i=0; i<64000; i++){
	}
	}
}

void playnone(){
	//Turn everything off
	PORTC = 0x00;
	OCR0A = 0x00;
	TCCR0B = 0x00;
}

void play(int z){
	if (z == 0) {
		playyellow();
	}
	if (z == 1) {
		playblue();
	}
	if (z == 2) {
		playgreen();
	}
	if (z == 3) {
		playred();
	}
	
	for(unsigned int i=0; i<64000; i++){
		for(unsigned int j=0; j<10; j++) {}
	}
	playnone();
}

void playPress(int z){
	if (z == 0) {
		playyellow();
	}
	if (z == 1) {
		playblue();
	}
	if (z == 2) {
		playgreen();
	}
	if (z == 3) {
		playred();
	}
	
	while(z == button()) {} // Wait for button to be released
	
	playnone();
}

int main(void)
{
	DDRB = DDRB & ~0x00;
	PORTB = PORTB & ~0x00;
	DDRC = DDRC | 0xFF;
	PORTC = PORTC | 0x00;
	//Sets mode normal
	TCCR0A = TCCR0A & ~0x01;
	TCCR0A = TCCR0A | 0x02;
	TCCR0B = TCCR0B & ~0x08;
	//Set Comparators
	TCCR0A = TCCR0A & ~0x80;
	TCCR0A = TCCR0A | 0x40;
	//Sets prescaler to 0 (off)
	TCCR0B = 0x00;
	
	DDRD = DDRD | 0x40;
	unsigned int x = -1;
	int last_x = -1;
	
	while (1)
	{
		int seq[10];
		int ans;
		int seed;
		int g;
		int i = 0;
		
		last_x = -1;
		x = -1;
		//When button is pressed begins the game and locks in value of i to continue the loop
		while (last_x == x){
			x = button();
			i = i + 1;
		} 
		seed = i;
		last_x = x;
		srand(seed);
		for (int y=0;y<10;y++){		//Generates 10 colors to play in sequence
			seq[y] = (rand()%4);
		}
		for(unsigned int A=0; A<64000; A++){
	}
		
		
		for (int j=1;j<10;j++){			//Tracks which loop we're in
			if (a==1){
				break; }
			for (int k=0;k<j;k++){			//Count number of presses in loop
				play(seq[k]);
				playnone();
				for(unsigned int b=0; b<64000; b++){
				}
			}
			for (g=0;g<j;g++){
				int result = seq[g];
				last_x = x;
				while (last_x == x){ // Wait for press
					x = button();
				}
				last_x = x;
				while (last_x == x){ // Wait for release
					x = button();
					playPress(x);
				}
				
				if (x == result){
				}	
				else{break;}
				}
		if (g!=j){
			playlose();
			break;
			
		}
		if(g==10){
			playwin();
			
		}
		}
		
	
	}
	return 0;
		}
