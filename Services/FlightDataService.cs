public class FlightDataService
{
    public static FlightDataItem[] FlightData = new FlightDataItem[10];

    private static int sec = 10;
    private static double val = 10.0;


    public static FlightDataItem GetNextDataItem()
    {
        FlightDataItem testData = new FlightDataItem();
        sec++;
        val += new Random().Next(10);
        testData.Seconds = sec;
        testData.Pressure = val;
        testData.Temperature = val;
        testData.Altitude = val;
        testData.VerticalSpeed = val;
        return testData;
    }

    public static void shiftArrayValues(FlightDataItem[] flightData)
    {
        for (int i = 0; i < flightData.Length - 1; i++)
        {
            flightData[i].Seconds = flightData[i + 1].Seconds;
            flightData[i].Pressure = flightData[i + 1].Pressure;
            flightData[i].Temperature = flightData[i + 1].Temperature;
            flightData[i].Altitude = flightData[i + 1].Altitude;
            flightData[i].VerticalSpeed = flightData[i + 1].VerticalSpeed;
        }
        flightData[flightData.Length - 1].Seconds = 0;
        flightData[flightData.Length - 1].Pressure = 0.0;
        flightData[flightData.Length - 1].Temperature = 0.0;
        flightData[flightData.Length - 1].Altitude = 0.0;
        flightData[flightData.Length - 1].VerticalSpeed = 0.0;
    }

    private double averagePressure = 0.0;
    public void calibratePressure(double[] pressure)
    {
        for (int i = 0; i < pressure.Length; i++)
        {
            averagePressure += pressure[i];
        }
        averagePressure = averagePressure / pressure.Length;
    }

}