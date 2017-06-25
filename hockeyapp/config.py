def can_build(plat):
	return plat=="android"

def configure(env):
	if (env['platform'] == 'android'):
		env.android_add_dependency("compile 'net.hockeyapp.android:HockeySDK:4.1.4'")
		env.android_add_default_config("manifestPlaceholders = [HOCKEYAPP_APP_ID: 'YOUR APP ID HERE']")
		env.android_add_to_manifest("android/AndroidManifestChunk.xml")
		env.android_add_to_permissions("android/AndroidManifestPermissionsChunk.xml")
		env.android_add_java_dir("android/src/")
		env.disable_module()

