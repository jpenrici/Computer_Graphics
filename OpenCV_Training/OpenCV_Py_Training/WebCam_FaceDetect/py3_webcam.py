# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

'''
    Custom WebCam Control via OpenCV
'''

import cv2

message = "Message"

normal = {
    "width" : 160,
    "height" : 120,
    "text" : {
        "color": (255, 255, 255),
        "fontScale": 0.4,
        "thickness" : 1,
        "xy" : (5, 110)
    },
    "rect" : {
        "color" : (0, 0, 0),
        "x0y0" : (0, 95),
        "x1y1" : (160, 120)
    }
}

extra = {
    "width" : 320,
    "height" : 240,
    "text" : {
        "color": (255, 255, 255),
        "fontScale": 0.8,
        "thickness" : 2,
        "xy" : (5, 225)
    },
    "rect" : {
        "color" : (0, 0, 0),
        "x0y0" : (0, 195),
        "x1y1" : (320, 240)
    }
}


def main():

    title = "WEBCAM"
    data = normal
    alert = False    
    detect = False

    cascade_path = "haarcascade_frontalface_default.xml"
    clf = cv2.CascadeClassifier(cascade_path)

    cv2.namedWindow(title)
    vc = cv2.VideoCapture(0)

    if vc.isOpened():
        rval, frame = vc.read()
    else:
        rval = False

    while rval:

        img = cv2.resize(frame, (data['width'], data['height']))
        img = cv2.flip(img, 1)

        if not clf.empty() and detect:
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            faces = clf.detectMultiScale(
                gray,
                scaleFactor=1.1,
                minNeighbors=5,
                minSize=(30, 30),
                flags=cv2.CASCADE_SCALE_IMAGE
            )        
            for (x, y, w, h) in faces:
                img = cv2.rectangle(img, (x,y), (x+w, y+h), (0, 0, 255), 2)

        if alert:
            font = cv2.FONT_HERSHEY_SIMPLEX
            img = cv2.rectangle(
                img,
                data['rect']['x0y0'],
                data['rect']['x1y1'],
                data['rect']['color'],
                -1  # Fill
            )
            cv2.putText(
                img,
                message,
                data['text']['xy'],
                font,
                data['text']['fontScale'],
                data['text']['color'],
                data['text']['thickness'],
                cv2.LINE_4)

        cv2.imshow(title, img)
        rval, frame = vc.read()
        
        key = cv2.waitKey(20)

        if key == 27:       # ESC
            print("Exit ...")
            break

        if key == ord('A'):
            data = extra
            print(data['width'], data['height'], sep="x")
        if key == ord('a'):
            data = normal
            print(data['width'], data['height'], sep="x")

        if key == ord('F'):
            detect = True
            print("Detect Faces ...")
        if key == ord('f'):
            detect = False
            print("Stop Face Detection...")

        if key == ord('M'):
            alert = True
            print("Mensage:", message, "...")
        if key == ord('m'):
            alert = False
            print("Message disabled ...")

        if key == 32:        # Space
            alert = False
            detect = False
            # data = normal

    vc.release()
    cv2.destroyWindow(title)


if __name__ == '__main__':
    main()