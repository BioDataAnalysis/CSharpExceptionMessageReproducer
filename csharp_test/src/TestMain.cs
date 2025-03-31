
using System;

class TestMain
{
    static int Main(string[] aArguments)
    {
        ExceptionMessageReproducer vExceptionMessageReproducer = new ExceptionMessageReproducer();

        try
        {

            vExceptionMessageReproducer.test();

        }
        catch (System.Exception vEx)
        {
            Console.WriteLine("TestMain::Main(): Caught 'System.Exception' with message '" + vEx.Message + "'");
        }

        return 0;
    }
}