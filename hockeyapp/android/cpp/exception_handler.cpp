#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <android/log.h>
#include <execinfo.h>
#include <errno.h>
#include <cxxabi.h>
//#include <libunwind.h>
#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"
#include "exception_handler.h"
 
#define  LOG_TAG    "NativeExceptionHandler"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static google_breakpad::ExceptionHandler* exceptionHandler;

void Crash() {
    LOGE("Generating crash from c++ code!");
    volatile int* a = reinterpret_cast<volatile int*>(NULL);
    *a = 1;
}


bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded) {
  LOGE("Dump path: %s\n", descriptor.path());
  return succeeded;
}

static inline void printStackTrace( FILE *out = stderr, unsigned int max_frames = 63 )
{
    LOGE("stack trace:\n");
    /*
    unw_cursor_t    cursor;
    unw_context_t   context;

    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    while (unw_step(&cursor) > 0)
    {
        unw_word_t  offset, pc;
        char        fname[64];

        unw_get_reg(&cursor, UNW_REG_IP, &pc);

        fname[0] = '\0';
        (void) unw_get_proc_name(&cursor, fname, sizeof(fname), &offset);

        LOGE ("%p : (%s+0x%x) [%p]\n", pc, fname, offset, pc);
    } 
    */
}

void abortHandler( int signum )
{
    // associate each signal with a signal name string.
    const char* name = NULL;
    switch( signum )
        {
        case SIGABRT: name = "SIGABRT";  break;
        case SIGSEGV: name = "SIGSEGV";  break;
        case SIGBUS:  name = "SIGBUS";   break;
        case SIGILL:  name = "SIGILL";   break;
        case SIGFPE:  name = "SIGFPE";   break;
        }
 
    // Notify the user which signal was caught. We use printf, because this is the 
    // most basic output function. Once you get a crash, it is possible that more 
    // complex output systems like streams and the like may be corrupted. So we 
    // make the most basic call possible to the lowest level, most 
    // standard print function.
    if ( name )
        LOGE("Caught signal %d (%s)\n", signum, name );
    else
        LOGE("Caught signal %d\n", signum );
 
    // Dump a stack trace.
    // This is the function we will be implementing next.
    printStackTrace();
 
    // If you caught one of the above signals, it is likely you just 
    // want to quit your program right now.
    exit( signum );
}

void SetupCrashHandler(const char* path)
{
    LOGD("Setup signal handlers for c++ code");

    google_breakpad::MinidumpDescriptor descriptor(path);
    exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback, NULL, true, -1);

    /*
    signal( SIGABRT, abortHandler );
    signal( SIGSEGV, abortHandler );
    signal( SIGILL,  abortHandler );
    signal( SIGFPE,  abortHandler );        
    */
}

/*
extern "C" {

    JNIEXPORT void JNICALL Java_org_godotengine_godot_GodotHockeyapp_setUpBreakpad(JNIEnv* env, jobject obj, jstring filepath) {
        const char *path = env->GetStringUTFChars(filepath, 0);
        SetupCrashHandler();
    }

    JNIEXPORT void JNICALL Java_org_godotengine_godot_GodotHockeyapp_nativeCrash(JNIEnv* env, jobject obj) {
        Crash();
    }

}
*/
