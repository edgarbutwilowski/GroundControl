using System.IO.Ports;

public class SerialReader {

    public static void readSerial(){
        SerialPort telemetryPort = new SerialPort("COM1", 9600,
                Parity.None, 8, StopBits.One);
        telemetryPort.DataReceived +=
            new SerialDataReceivedEventHandler((object sender, SerialDataReceivedEventArgs e) => {
                Console.WriteLine(telemetryPort.ReadExisting());
        });  // Zeremonie (Methode beim Event-Handler registrieren, Lambda-Ausdruck)

    }

}