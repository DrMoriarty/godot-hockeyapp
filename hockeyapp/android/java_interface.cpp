#include "cpp/exception_handler.h"
#include "java_interface.h"

extern "C" {

    JNIEXPORT void JNICALL Java_org_godotengine_godot_GodotHockeyapp_setUpBreakpad(JNIEnv* env, jobject obj, jstring filepath) {
        const char *path = env->GetStringUTFChars(filepath, 0);
        SetupCrashHandler(path);
    }

    JNIEXPORT void JNICALL Java_org_godotengine_godot_GodotHockeyapp_nativeCrash(JNIEnv* env, jobject obj) {
        Crash();
    }

}

