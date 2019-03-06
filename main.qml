import QtQuick 2.9
import QtQuick.Controls 2.2
import QtMultimedia 5.8

import DesktopVideoProducer 0.1

Item {
    visible: true

    anchors.fill: parent

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

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 10
        width: parent.width / 2

        VideoOutput {
            id: videoIn
            source: camera
            anchors.fill: parent
            focus : visible // to receive focus and capture key events when visible
        }
    }


    VideoOutput {
        id: videoOut
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 2
        anchors.margins: 10
        source: videoHandler
    }

    Timer {
        id: main_loop
        interval: 100; running: true; repeat: true;
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
