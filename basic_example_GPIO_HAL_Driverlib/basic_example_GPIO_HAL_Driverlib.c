// This application uses button 1 and LED 1.
// The operation is such that if you press the left button, as long as you keep the button pressed,
// the LED is on. As soon as you release the button, LED is off and stays off until the button is pressed again.
// This example uses Driverlib functions. It also builds a HAL.

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


// According to the schematics on page 37 of the Launchpad user guide,
// left button (button 1) is connected to pin 1 (bit1)
#define LEFT_BUTTON (1<<1)

// According to the schematics on page 37 of the Launchpad user guide,
// left LED (LED 1) is connected to pin 0 (bit0)
#define LEFT_LED (1<<0)

// According to the schematics on page 37 of the Launchpad user guide,
// When a button is pressed, it is grounded (logic 0)
#define PRESSED 0


void TurnOn_Launchpad_LED1();
void TurnOff_Launchpad_LED1();
char S1isPressed();

// This function initializes all the peripherals
void initialize();

// In this example, the high-level function, main, is readable.
// It is also easy to port this function to other platforms with similar peripherals such as an LED and a switch
int main(void)
{
    // initialize all the peripherals
    initialize();

    while (1) {
        // If the button is not pressed, keep the LED off
        if (!S1isPressed())
            TurnOff_Launchpad_LED1();

        // otherwise, turn the LED on
        else
            TurnOn_Launchpad_LED1();
    }
}

// The HAL itself is written using Driverlib, so it is much easier to implement.
void initialize()
{

    // step 1: Stop watchdog timer
    // We do this at the beginning of all our programs for now.Later we learn more about it.
    WDT_A_hold(WDT_A_BASE);

    // step 2: Initializing LED1, which is on Pin 0 of Port P1 (from page 37 of the Launchpad User Guide)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // step 3: Initializing S1 (switch 1 or button 1),
    // which is on Pin1 of Port 1 (from page 37 of the Launchpad User Guide)
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);}


void TurnOn_Launchpad_LED1()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void TurnOff_Launchpad_LED1()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

char S1isPressed()
{
    return ((GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == PRESSED));
}
