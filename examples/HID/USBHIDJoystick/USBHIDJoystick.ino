#include <hid.h>
#include <hiduniversal.h>
#include <usbhub.h>

#include "hidjoystickrptparser.h"

// On SAMD boards where the native USB port is also the serial console, use
// Serial1 for the serial console. This applies to all SAMD boards except for
// Arduino Zero and M0 boards.
#if defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAM_ZERO)
#define SerialDebug SERIAL_PORT_MONITOR
#else
#define SerialDebug Serial1
#endif

USBHost UsbH;
USBHub Hub(&UsbH);
HIDUniversal Hid(&UsbH);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

void setup() {
        SerialDebug.begin(115200);
        SerialDebug.println("Start");

        if (UsbH.Init())
                SerialDebug.println("USB host did not start.");

        delay(200);

        if (!Hid.SetReportParser(0, &Joy))
                ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
}

void loop() {
        UsbH.Task();
}
