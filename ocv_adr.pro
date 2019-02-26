QT += core gui quick multimedia
CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

TARGET = ocv_adr
TEMPLATE = app

SOURCES += main.cpp \
    desktopvideoproducer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

CONFIG += mobility
MOBILITY =

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

# Change this paths to your own OpenCV  for Android installation
INCLUDEPATH += /home/rattus/opencv/opencv-android-sdk/sdk/native/jni/include

#LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs

android {
    # Change the last part (armeabi-v7a) according to your build
    OPENCV3RDPARTYLIBS = /home/rattus/opencv/opencv-android-sdk/sdk/native/3rdparty/libs/armeabi-v7a
    OPENCVNATIVELIBS = /home/rattus/opencv/opencv-android-sdk/sdk/native/libs/armeabi-v7a

    #INCLUDEPATH += /usr/local/include/

    LIBS += $$OPENCV3RDPARTYLIBS/liblibtiff.a \
        $$OPENCV3RDPARTYLIBS/liblibjpeg.a \
        $$OPENCV3RDPARTYLIBS/liblibjasper.a \
        $$OPENCV3RDPARTYLIBS/liblibpng.a \
        $$OPENCV3RDPARTYLIBS/libIlmImf.a \
        $$OPENCV3RDPARTYLIBS/libtbb.a

    LIBS += $$OPENCVNATIVELIBS/libopencv_core.a \
        $$OPENCVNATIVELIBS/libopencv_androidcamera.a \
        $$OPENCVNATIVELIBS/libopencv_flann.a \
        $$OPENCVNATIVELIBS/libopencv_imgproc.a \
        $$OPENCVNATIVELIBS/libopencv_highgui.a \
        $$OPENCVNATIVELIBS/libopencv_features2d.a \
        $$OPENCVNATIVELIBS/libopencv_calib3d.a \
        $$OPENCVNATIVELIBS/libopencv_ml.a \
        $$OPENCVNATIVELIBS/libopencv_objdetect.a \
        $$OPENCVNATIVELIBS/libopencv_photo.a \
        $$OPENCVNATIVELIBS/libopencv_stitching.a \
        $$OPENCVNATIVELIBS/libopencv_superres.a \
        $$OPENCVNATIVELIBS/libopencv_ts.a \
        $$OPENCVNATIVELIBS/libopencv_video.a \
        $$OPENCVNATIVELIBS/libopencv_videostab.a \
        $$OPENCVNATIVELIBS/libopencv_java.so \
        $$OPENCVNATIVELIBS/libopencv_info.so
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    desktopvideoproducer.h
