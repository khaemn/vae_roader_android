import QtQuick 2.9
import QtQuick.Controls 2.2
import QtMultimedia 5.8

import DesktopVideoProducer 0.1

ApplicationWindow {
    visible: true

    width: 1000
    height: 1000

    title: qsTr("Scroll")

    Rectangle {
        anchors.fill: parent
        anchors.margins: 5
        color: "black"
    }

    Camera {
        id: camera

        imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash

        exposure {
            exposureCompensation: -1.0
            exposureMode: Camera.ExposurePortrait
        }

        flash.mode: Camera.FlashRedEyeReduction

        imageCapture {
            onImageCaptured: {
                photoPreview.source = preview  // Show the preview in an Image
            }
        }
    }

    DesktopVideoProducer {
        id: videoHandler;
    }

    Item {
        id: grabSurface

        anchors.fill: parent

        VideoOutput {
            id: videoIn
            source: camera
            anchors.fill: parent
            focus : visible // to receive focus and capture key events when visible
        }

        visible: false
    }


    VideoOutput {
        id: videoOut
        anchors.fill: parent

        source: videoHandler
        anchors.rightMargin: 100
    }

    Timer {
        id: main_loop
        interval: 1000; running: true; repeat: true;
        onTriggered:
        {
            videoHandler.recognize();
        }
    }

    Component.onCompleted:
    {
        videoHandler.setCamera(grabSurface);
    }
}
