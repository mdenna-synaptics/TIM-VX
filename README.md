
# TIM-VX - Tensor Interface Module
[Introduction](https://github.com/VeriSilicon/TIM-VX/blob/main/README.md)

## Framework Support

- [Tensorflow-Lite](https://github.com/VeriSilicon/tflite-vx-delegate) (External Delegate)

## Build and Run

----
### Build for x86:

```shell
mkdir host_build
cd host_build
cmake .. -G Ninja -DSYNAP_DIR=/path/to/synap/build/install -DSOC=VS680A0 -DTIM_VX_BUILD_EXAMPLES=ON
ninja install
```
----
### Build for Android

```shell

mkdir android_build
cd android_build

cmake .. -G Ninja -DSYNAP_DIR=/path/to/syna/synap-build/install -DSOC=VS680A0 \
-DTIM_VX_BUILD_EXAMPLES=ON \
-DANDROID_PLATFORM="android-31" \
-DANDROID_ABI="armeabi-v7a with NEON" \
-DANDROID_STL=c++_static \
-DCMAKE_TOOLCHAIN_FILE=/opt/bin/toolchain/android-ndk-r25c/build/cmake/android.toolchain.cmake

ninja install

```

