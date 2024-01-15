# -*- Mode: Python3; coding: utf-8; indent-tabs-mpythoode: nil; tab-width: 4 -*-

'''
    Custom WebCam Control using OpenCV.

    Functionalities:

        Image preview.
        Button with time counter.
'''

import os
import sys
import time

import cv2
from PySide6.QtCore    import Qt, QThread, QTimer, Signal, Slot
from PySide6.QtGui     import QAction, QImage, QKeySequence, QPixmap, QFont, QColor
from PySide6.QtWidgets import QApplication, QMainWindow, QWidget, QLabel, QPushButton, QVBoxLayout


class WebCamThread(QThread):
    updateFrame = Signal(QImage)

    def __init__(self, parent=None):
        QThread.__init__(self, parent)
        self.width  = 250
        self.height = 250
        self.status = True
        self.cap    = True

    def size(self, width: float, height: float):
        self.width  = width
        self.height = height

    def run(self):
        self.cap = cv2.VideoCapture(0)
        if not self.cap.isOpened():
            print ("Webcam not opened!")
            self.status = False

        while self.status:
            ret, frame = self.cap.read()
            if not ret:
                continue

            color_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            h, w, ch = color_frame.shape
            img = QImage(color_frame.data, w, h, ch * w, QImage.Format_RGB888)
            scaled_img = img.scaled(self.width, self.height, Qt.KeepAspectRatio)

            self.updateFrame.emit(scaled_img)

        sys.exit(-1)


class Window(QMainWindow):

    def __init__(self, title: str, width: int, height: int , minutes: int):
        """
        :param title: Title displayed in the window.
        :param width: Window width.
        :param height: Window height.
        :param minutes: Maximum limit in minutes to alert.
        """
        super().__init__()
        self.setWindowTitle(title)
        self.setGeometry(0, 0, width, height)

        self.label = QLabel(self)
        self.label.setFixedSize(width, int(height * 0.90))

        self.th = WebCamThread(self)
        self.th.size(self.label.width(), self.label.height())
        self.th.finished.connect(self.close)
        self.th.updateFrame.connect(self.setImage)
        
        timer = QTimer(self)
        timer.timeout.connect(self.showTime)
        timer.start(1000)

        self.seconds   = 0
        self.limit     = minutes * 60
        self.tolerance = 70 / 100

        self.button = QPushButton("Start")
        self.button.setFont(QFont('Arial', 12))
        self.button.setStyleSheet("background-color : blue; color : white;")
        self.button.pressed.connect(self.restart)

        layout = QVBoxLayout()
        layout.addWidget(self.label)
        layout.addWidget(self.button)

        widget = QWidget(self)
        widget.setLayout(layout)
        self.setCentralWidget(widget)

    def convert(self, seconds: int) -> str:
        minutes  = seconds // 60
        seconds -= minutes * 60
        return "{:02d} : {:02d}".format(minutes, seconds)

    def restart(self):
        if self.button.text() == "Start":
            self.th.start()
        self.seconds = 0
        self.button.setText("-- : --")            

    def lineargradient(self, color1: QColor, color2: QColor, stop: float = 1):
        stop = 0.000 if stop < 0 else stop
        stop = 0.999 if stop >= 1 else stop        
        return "background: qlineargradient( x1:0 y1:0, x2:{stop} y2:0, stop:{stop} {color1}, stop:1 {color2});".format(
            color1=color1.name(), color2=color2.name(), stop=stop)

    def showTime(self):
        if self.button.text() == "Start":
            return
        self.seconds += 1
        self.button.setText(self.convert(self.seconds))
        self.button.setStyleSheet(self.lineargradient(QColor(255, 0, 0), QColor(54, 115, 50), self.seconds / self.limit))
        # print(self.button.text())
  
    @Slot(QImage)
    def setImage(self, image: QImage):
        self.label.setPixmap(QPixmap.fromImage(image))


if __name__ == "__main__":
    app = QApplication()
    w = Window("WebCam", 200, 200, 10)
    w.show()
    sys.exit(app.exec())