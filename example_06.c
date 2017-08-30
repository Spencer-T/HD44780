#include "beagle_gpio.h"
#include "beagle_hd44780.h"

//Connect a HD44780 compatible screen to the beaglebone using the 
//follwing connections:
//P8_12 ==> DB7
//P8_14 ==> DB6
//P8_16 ==> DB5
//P8_18 ==> DB4 
//P8_8  ==> RS
//P8_10  ==> E

/*
void turn_ON_OFF_pins(struct gpioID selected_GPIOs[],unsigned int data_to_write,int nbr_selectedPins)
{
	int i;
	
	for (i=0;i<nbr_selectedPins;i++)
	{
		//code that turns ON/OFF a pin
		write_GPIO_value(selected_GPIOs[i].GPIONUMBER,bitRead(data_to_write,i));
        
		//this is just for debugging purposes
//		if (DEBUG)
//		{ 
//			if (bitRead(data_to_write,i) == 1) printf("turning ON");	
//			else printf("turning OFF");	
//			printf(	"\t%s (%s %d %s)\n",selected_GPIOs[i].PINNAME,selected_GPIOs[i].GPIOID,selected_GPIOs[i].GPIONUMBER,selected_GPIOs[i].GPIOMUX);				
//		}
	}
//	if (DEBUG) printf("\n");
}
*/

int main()
{

	int count=0;
		
	//specifies the pins that will be used

	int selectedPins[]={P8_12,P8_14,P8_16,P8_18,P8_8,P8_10};
//	int selectedPins[]={P8_10,P8_8,P8_18,P8_16,P8_14,P8_12};

//	unsigned int data_to_write=0;
//	int nbr_selectedPins=sizeof(selectedPins)/sizeof(*selectedPins);

	struct gpioID enabled_gpio[6];
	struct gpioID LED1;
//	struct gpioID selectedPins[nbr_selectedPins];

	pinMode(&LED1,P9_23,"out");
	digitalWrite(LED1,1);

//	struct gpioID selectedPins[nbr_selectedPins];
	
	initialize_Screen(enabled_gpio,selectedPins);
	
	// Turn on P9_23, look at selectedPins[]arrry. P9_23 at position 6
	// need to set bits 6 on the variable data_to_write. In base 2,
	//setting bit 6 looks like:
	// 0100 0000, this is equivalent to 40, in base 10

//	data_to_write=40;
//	turn_ON_OFF_pins(enabled_gpio,data_to_write,nbr_selectedPins);
//	sleep(1);	


//	pinMode(&LED1, P9_23, "out");
//	digitalWrite(LED1,1);
	
	//clear screen
	clear_Screen(enabled_gpio);

	
//      digitalWrite(LED1,1);
	//types "yo!" to the screen
	stringToScreen("yo!",enabled_gpio);

	//go to the the second line 
	goto_ScreenLine(1,enabled_gpio);
	
	//stringToScreen(datetime.now().strftime('%b %d %H:%M:%S'));
	//types "how are you?"
	stringToScreen("execute code..",enabled_gpio);
	sleep(2.0);
	while (count<5)
	{	
	//wait 2 seconds and return to first line
//		initialize_Screen(enabled_gpio,selectedPins);
	
		clear_Screen(enabled_gpio);
		time_t t=time(NULL);
        	struct tm *tm=localtime(&t);
        	char s[64];
		sleep(1.0);
		goto_ScreenLine(0,enabled_gpio);
        	strftime(s, sizeof(s), "%x",tm);

//		sleep(1.0);
		digitalWrite(LED1,0);
		
	
	//and types "Done!"
//		stringToScreen("Done!",enabled_gpio);
//		goto_ScreenLine(1, enabled_gpio);
		stringToScreen(s, enabled_gpio);


//	digitalWrite(LED1,1);
	//don't forget to terminate the screen... or you may get
		digitalWrite(LED1,1);
		goto_ScreenLine(1, enabled_gpio);
		sleep(1.0);
		strftime(s, sizeof(s), "%X",tm);
		stringToScreen(s, enabled_gpio);
//		clear_Screen(enabled_gpio);
//  		terminate_Screen(enabled_gpio,selectedPins);
		sleep(1.0);
		digitalWrite(LED1,0);
		cleanup(LED1);
		count++;
	}
	terminate_Screen(enabled_gpio,selectedPins);
	return 1;
}

