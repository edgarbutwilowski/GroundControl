using System.IO.Ports;

public class SerialReader
{
    public static void readSerial(string comPort)
    {
        SerialPort telemetryPort = new SerialPort(comPort, 9600,
                Parity.None, 8, StopBits.One);
        telemetryPort.DataReceived +=
            new SerialDataReceivedEventHandler((object sender, SerialDataReceivedEventArgs e) =>
            {
                string measuredValuesCsv = telemetryPort.ReadExisting();
                Console.WriteLine("measuredValuesCsv: " + measuredValuesCsv);
                string[] measuredValues = measuredValuesCsv.Split(";");
                foreach (string measuredValue in measuredValues)
                {
                    Console.WriteLine("measuredValue: " + measuredValue);
                }
            });  // Zeremonie (Methode beim Event-Handler registrieren, Lambda-Ausdruck)
    }
}