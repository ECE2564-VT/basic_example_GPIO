// This application uses button 1 and LED 1
// The operation is such that if you press the left button, as long as you keep the button pressed,
// the LED is on. As soon as you release the button, LED is off and stays off until the button is pressed again.
// This example uses Driverlib functions, so it is easier than using memory-mapped registers directly.
// However, it does not build a Hardware Abstraction Layer (HAL), and therefore, the code is not easy to read and impossible to port.
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

// According to the schematics on page 37 of the Launchpad user guide,
// When a button is pressed, it is grounded (logic 0)
#define PRESSED 0


 // This example does not use a HAL and therefore, it is hard to read, and hard to port to other platforms.
 // Since it uses Driverlib functions, it is easier to write it compared to the noDriverlib counterpart.
int main(void)
{

    // step 1: Stop watchdog timer
    // We do this at the beginning of all our programs for now.Later we learn more about it.
    WDT_A_hold(WDT_A_BASE);

    // step 2: Initializing LED1, which is on Pin 0 of Port P1 (from page 37 of the Launchpad User Guide)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // step 3: Initializing S1 (switch 1 or button 1),
    // which is on Pin1 of Port 1 (from page 37 of the Launchpad User Guide)
    GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P1, GPIO_PIN1);


    while (1) {
        // If the button is not pressed, keep the LED off

        if (GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) != PRESSED)
            GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

        // otherwise, turn the LED on
        else
            GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
    }
}


