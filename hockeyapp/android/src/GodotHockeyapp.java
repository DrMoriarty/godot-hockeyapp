package org.godotengine.godot;

import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ApplicationInfo;
import android.util.Log;
import java.util.Map;
import java.util.List;
import java.util.Arrays;
import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;
import net.hockeyapp.android.Constants;
import net.hockeyapp.android.CrashManager;
import net.hockeyapp.android.UpdateManager;
import net.hockeyapp.android.metrics.MetricsManager;
import net.hockeyapp.android.FeedbackManager;
import net.hockeyapp.android.Tracking;

public class GodotHockeyapp extends Godot.SingletonBase {

    private Godot activity = null;
    static private String HOCKEYAPP_ID = null;
    static private final String TAG = "GodotHockeyapp";

    static public Godot.SingletonBase initialize(Activity p_activity) 
    {
        Log.i(TAG, "Init singleton");
        try {
            ApplicationInfo ai = p_activity.getPackageManager().getApplicationInfo(p_activity.getPackageName(), PackageManager.GET_META_DATA);
            Bundle aBundle = ai.metaData;
            HOCKEYAPP_ID = aBundle.getString("net.hockeyapp.android.appIdentifier");
        } catch (Exception ex) {
            Log.e(TAG, ex.toString());
        }
        Log.i(TAG, "HockeyApp ID: "+HOCKEYAPP_ID);
        return new GodotHockeyapp(p_activity); 
    } 

    public GodotHockeyapp(Activity p_activity) 
    {
        registerClass("GodotHockeyapp", new String[]{"forceCrash", "forceNativeCrash", "trackEvent", "feedback"});
        activity = (Godot)p_activity;
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                // Handle NDK crashes
                Constants.loadFromContext(activity);
                setUpBreakpad(Constants.FILES_PATH);
                NativeCrashManager.handleDumpFiles(activity, HOCKEYAPP_ID);

                CrashManager.register(activity);
                UpdateManager.register(activity);
                MetricsManager.register(activity, activity.getApplication());
                FeedbackManager.register(activity);
            }
        });
        Log.d(TAG, "Create hockeyapp instance");
    }

    public void forceCrash()
    {
        throw new RuntimeException("This is a crash");
    }

    public void forceNativeCrash()
    {
        nativeCrash();
    }

    public void trackEvent(final String event)
    {
        MetricsManager.trackEvent(event);
    }

    public void feedback()
    {
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                FeedbackManager.showFeedbackActivity(activity);
            }
        });
    }

    @Override protected void onMainActivityResult (int requestCode, int resultCode, Intent data)
    {
    }

    protected void onMainPause() {
        UpdateManager.unregister();
        Tracking.stopUsage(activity);
    }

    protected void onMainResume() {
        CrashManager.register(activity);
        Tracking.startUsage(activity);
    }

    protected void onMainDestroy() {
        UpdateManager.unregister();
    }

    private native void nativeCrash();
    private native void setUpBreakpad(String filepath);
}
