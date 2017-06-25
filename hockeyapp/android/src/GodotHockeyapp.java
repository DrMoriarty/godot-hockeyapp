package org.godotengine.godot;

import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import java.util.Map;
import java.util.List;
import java.util.Arrays;
import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;
import net.hockeyapp.android.CrashManager;
import net.hockeyapp.android.UpdateManager;

public class GodotHockeyapp extends Godot.SingletonBase {

    private Godot activity = null;
    static private final String TAG = "GodotHockeyapp";

    static public Godot.SingletonBase initialize(Activity p_activity) 
    {
        Log.i(TAG, "Init singleton");
        return new GodotHockeyapp(p_activity); 
    } 

    public GodotHockeyapp(Activity p_activity) 
    {
        registerClass("GodotHockeyapp", new String[]{});
        activity = (Godot)p_activity;
        UpdateManager.register(activity);
        Log.d(TAG, "Create hockeyapp instance");
    }

    @Override protected void onMainActivityResult (int requestCode, int resultCode, Intent data)
    {
    }

    protected void onMainPause() {
        UpdateManager.unregister();
    }

    protected void onMainResume() {
        CrashManager.register(activity);
    }

    protected void onMainDestroy() {
        UpdateManager.unregister();
    }
}
