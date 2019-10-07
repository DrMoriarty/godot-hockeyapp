#include <jni.h>

extern "C" {
    JNIEXPORT void JNICALL Java_org_godotengine_godot_GodotHockeyapp_setUpBreakpad(JNIEnv* env, jobject obj, jstring filepath);
    JNIEXPORT void JNICALL Java_org_godotengine_godot_GodotHockeyapp_nativeCrash(JNIEnv* env, jobject obj);
}
