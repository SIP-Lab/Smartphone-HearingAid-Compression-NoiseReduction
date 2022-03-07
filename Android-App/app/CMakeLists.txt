# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

PROJECT(matlabNative C)
# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             matlabNative

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).

              src/main/jni/MatlabNative.c
              src/main/jni/CoderFile/tmwtypes.h
		src/main/jni/CoderFile/omp.h
	      src/main/jni/CoderFile/applyBinaryScalarFunction.c
        src/main/jni/CoderFile/applyBinaryScalarFunction.h
        src/main/jni/CoderFile/casyi.c
        src/main/jni/CoderFile/casyi.h
        src/main/jni/CoderFile/cbesi.c
        src/main/jni/CoderFile/cbesi.h
        src/main/jni/CoderFile/cmlri.c
        src/main/jni/CoderFile/cmlri.h
        src/main/jni/CoderFile/cospiAndSinpi.c
        src/main/jni/CoderFile/cospiAndSinpi.h
        src/main/jni/CoderFile/FFTImplementationCallback.c
        src/main/jni/CoderFile/FFTImplementationCallback.h
        src/main/jni/CoderFile/gammaln.c
        src/main/jni/CoderFile/gammaln.h
		src/main/jni/CoderFile/rt_defines.h
        src/main/jni/CoderFile/rt_nonfinite.c
        src/main/jni/CoderFile/rt_nonfinite.h
        src/main/jni/CoderFile/rtGetInf.c
        src/main/jni/CoderFile/rtGetInf.h
        src/main/jni/CoderFile/rtGetNaN.c
        src/main/jni/CoderFile/rtGetNaN.h
        src/main/jni/CoderFile/rtwtypes.h
        src/main/jni/CoderFile/sort.c
        src/main/jni/CoderFile/sort.h
        src/main/jni/CoderFile/sortIdx.c
        src/main/jni/CoderFile/sortIdx.h
        src/main/jni/CoderFile/SpeechNoiseEstimator.c
        src/main/jni/CoderFile/SpeechNoiseEstimator.h
        src/main/jni/CoderFile/SPL.c
        src/main/jni/CoderFile/SPL.h
        src/main/jni/CoderFile/SPL_data.c
        src/main/jni/CoderFile/SPL_data.h
        src/main/jni/CoderFile/SPL_emxutil.c
        src/main/jni/CoderFile/SPL_emxutil.h
        src/main/jni/CoderFile/SPL_initialize.c
        src/main/jni/CoderFile/SPL_initialize.h
        src/main/jni/CoderFile/SPL_internal_types.h
        src/main/jni/CoderFile/SPL_terminate.c
        src/main/jni/CoderFile/SPL_terminate.h
        src/main/jni/CoderFile/SPL_types.h
        src/main/jni/CoderFile/splMeter.c
        src/main/jni/CoderFile/splMeter.h
        src/main/jni/CoderFile/StatCircBuffer.c
        src/main/jni/CoderFile/StatCircBuffer.h
        src/main/jni/CoderFile/SystemCore.c
        src/main/jni/CoderFile/SystemCore.h
		src/main/jni/CoderFile/SystemCoreSPL.c
		src/main/jni/CoderFile/SystemCoreSPL.h
        src/main/jni/CoderFile/VAD.c
        src/main/jni/CoderFile/VAD.h
        src/main/jni/CoderFile/VAD_data.c
        src/main/jni/CoderFile/VAD_data.h
        src/main/jni/CoderFile/VAD_initialize.c
        src/main/jni/CoderFile/VAD_initialize.h
        src/main/jni/CoderFile/VAD_internal_types.h
        src/main/jni/CoderFile/VAD_rtwutil.c
        src/main/jni/CoderFile/VAD_rtwutil.h
        src/main/jni/CoderFile/VAD_terminate.h
        src/main/jni/CoderFile/VAD_terminate.c
        src/main/jni/CoderFile/VAD_types.h
        src/main/jni/CoderFile/weightingFilter.c
        src/main/jni/CoderFile/weightingFilter.h
)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       matlabNative

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )