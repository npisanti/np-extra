np-extra
==============
[![Build status](https://travis-ci.org/npisanti/np-extra.svg?branch=master)](https://travis-ci.org/npisanti/np-extra) [![Build status](https://ci.appveyor.com/api/projects/status/wqie34342ep7d78l?svg=true)](https://ci.appveyor.com/project/npisanti/np-extra)


Extra classes for openFrameworks. Includes:

- `np::Phasor` class for cyclic animations.
- `np::PaletteTable` class for smooth transitions between palettes.
- Serialize and deserialize std::vector of glm::vec3, ofVec3f or ofPolyline.
- `np::Playlist` class to load randomly videos on the fly.
- `np::AlphaMasker` class to mask a source texture using a mask texture, can also be used with static methods as `np::masker::draw(...)`
- `np::LiveParameters` link an ofParameterGroup to a JSON file and watches for changes to the file
- `np::SpriteSheets` loads a .png horizontal spritesheet
- Classes for managing Scenes and transitions between them.
- functions for warping and transitioning between `ofPolyline`.

No other addons required for those classes, just oF. Those classes should work on all the oF platforms.

DISCLAIMER:    
I will treat everything in the `np` namespace as in constant alpha state, the code should be bug-free but the API will be subject to change, so if you want to use one of the classes just fork this repo or copy the .h and .cpp files you need.

Donate
------------ 
I support you, you support me!    
If you find this code useful, consider [fueling me with coffee](https://ko-fi.com/npisanti)!

License 
------------
Nicola Pisanti, MIT License 2018.

