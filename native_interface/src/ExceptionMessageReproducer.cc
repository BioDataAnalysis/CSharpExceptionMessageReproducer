
#include <ExceptionMessageReproducer.hh>

#pragma managed(push, off)
#include <cstdlib>
#include <exception>
#include <stdexcept>
#pragma managed(pop)

#include <msclr\marshal_cppstd.h>

ExceptionMessageReproducer::ExceptionMessageReproducer() {
}

ExceptionMessageReproducer::~ExceptionMessageReproducer() {
}

ExceptionMessageReproducer::!ExceptionMessageReproducer() {
}

void ExceptionMessageReproducer::test() {
    const std::string vNativeExceptionMessage = "This is a test exception";

    try {

        throw(std::runtime_error(vNativeExceptionMessage));

    } catch (const std::exception& vEx) {
        System::Console::WriteLine("Will wrap native exception '" + msclr::interop::marshal_as<System::String^>(vEx.what()) + "'.\n");
        throw gcnew System::Exception(msclr::interop::marshal_as<System::String^>(vEx.what()));
    }
    catch (System::Runtime::InteropServices::SEHException ^ vEx) {
        if (vEx->Message->Equals(msclr::interop::marshal_as<System::String ^>(vNativeExceptionMessage))) {
            System::Console::WriteLine("The exception message matches and is correct. This is good.\n");
        } else {
            System::Console::WriteLine("The exception messages '" + msclr::interop::marshal_as<System::String ^>(vNativeExceptionMessage) + "' and ''" + vEx->Message + "'' *do not match*! This is bad.\n");
        }

        System::Console::WriteLine("Will forward a managed SEHException '" + vEx->Message + "'.\n");
        throw;
    } catch (System::Exception ^ vEx) {
        System::Console::WriteLine("Caught managed exception '" + vEx->Message + "' in the native code wrapper.\n");
        throw;
    } catch (Object ^ vEx) {
        System::Console::WriteLine("Caught a managed object in the native code wrapper.\n");
        throw;
    } catch (...) {
        System::Console::WriteLine("Caught an unknown exception.\n");
        throw gcnew System::Exception("Caught an unknown exception");
    }
}