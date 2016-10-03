# irrAddOn
The additional functions that based on irrlicht.  
为irrlicht 1.8.1 写的扩展功能。

To compile this porject, you need eclipse cdt and irrlicht 1.8.1  
你需要eclipse cdt来编译这个工程。由于没有包含irrlicht，所以你需要自己去下载irrlicht 1.8.1 ，然后再修改头文件路径和库路径。

And there's a compiled library already in Release/ for linux.  
在release文件夹里面，有一个已经编好的linux库文件。（windows的以后再说）
### Modify the macro symbol in eclipse from _LINUX to _WINDOWS to compile windows dll  
### 如果要编译windows下的dll，请在eclipse中的“符号”选项卡中，把 _LINUX 改成 _WINDOWS  
## Features
* A customized particle emmiter for expolision effect.  
* A colour affector for particle system that similar to fade out affector, but change particle colours instead. 
* A simple sprite animater that changes the texure of the mash (especially for billboard) based on sprite sheet. Currently only for sprite sheet that contain tiles of the same size.

## 功能  
* 为爆炸特效专门写的自定义的粒子发射器。（鬼火自带的粒子发射器烂的一B）  
* 颜色渐变器，和渐出效果器相似，只是根据参数变颜色。  
* Sprite动画器，使用tilemap来切换贴图，专为billborad设计，目前只支持所有动画帧大小一致的tilemap。
