HockeyApp module for [Godot Game Engine](http://godotengine.org/) (Android only). 

To use it, make sure you're able to compile the Godot android template, you can find the instructions [here](http://docs.godotengine.org/en/latest/reference/compiling_for_android.html). Set your AppId in hockeyapp/android/AndroidManifestChunk.xml file and in hockeyapp/config.py files. After that, just copy the the hockeyapp folder to godot/modules and recompile it.


**Module name (engine.cfg):**
```
[android]
modules="org/godotengine/godot/GodotHockeyapp"
```

**Functions:**
* (TODO)


**Example:**
```python
func _ready():
    if(Globals.has_singleton("GodotHockeyapp")):
        var ha = Globals.get_singleton("GodotHockeyapp")

```        

