
using System;

class TestMain
{
    static int Main(string[] aArguments)
    {
        ExceptionMessageReproducer vExceptionMessageReproducer = new ExceptionMessageReproducer();

        try
        {
            vExceptionMessageReproducer.testCLRException();
        }
        catch (System.Exception vEx)
        {
            Console.WriteLine("TestMain::Main(): From testCLRException(), caught 'System.Exception' with message '" + vEx.Message + "'");
        }

        try
        {
            vExceptionMessageReproducer.testNonCLRException();
        }
        catch (System.Exception vEx)
        {
            Console.WriteLine("TestMain::Main(): From testNonCLRException(), caught 'System.Exception' with message '" + vEx.Message + "'");
        }

        return 0;
    }
}