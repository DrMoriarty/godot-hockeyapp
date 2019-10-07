def can_build(platform):
	return platform=="android"

def configure(env):
	if (env['platform'] == 'android'):
		env.android_add_dependency("compile 'net.hockeyapp.android:HockeySDK:4.1.4'")
		env.android_add_dependency("compile 'org.apache.httpcomponents:httpcore:4.2.+'")
		env.android_add_dependency("compile 'org.apache.httpcomponents:httpmime:4.2.+'")
		env.android_add_default_config("manifestPlaceholders = [HOCKEYAPP_APP_ID: 'c805e5c3ddcd40f2afce4535211345e1']")
		env.android_add_to_manifest("android/AndroidManifestChunk.xml")
		env.android_add_to_permissions("android/AndroidManifestPermissionsChunk.xml")
		env.android_add_java_dir("android/src/")
		#env.disable_module()

