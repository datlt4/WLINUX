from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

print("0000000000000000000000000000000000")
try:
    import pkg_resources.py2_warn
except ImportError:
    pass
import sys
OS = sys.platform
if "win" in OS:
    OS = "windows"
elif "linux" in OS:
    OS = "jetson"
else:
    sys.exit("Which OS is used (Windows or Jetson)?")

print("111111111111111111111111111111111")
import fix_qt_import_error

from PyQt5.QtCore import Qt, QRect, QTimer, pyqtSlot, QThread
from PyQt5.QtWidgets import QMainWindow, QVBoxLayout, QHBoxLayout, QMessageBox, QProgressBar
from PyQt5.QtWidgets import QLabel, QFileDialog, QPushButton, QLineEdit, QFrame, QMenu, QInputDialog
from PyQt5.QtWidgets import QTabWidget, QApplication, QWidget, QAction, qApp, QGroupBox, QRadioButton
from PyQt5.QtGui import QFont, QPixmap, QIcon, QImage
import cv2
print("77777777777777777777777777777777")
import numpy as np
import sys
import logging
from datetime import datetime
from threading import Thread

strSrc = None
print("888888888888888888888888888888888")
logging.basicConfig(level=logging.INFO, filename='app.log', filemode='w', format='%(name)s - %(levelname)s - %(message)s')

TITLE = "Test camera"
print("99999999999999999999999999999999999")

debug=True
def _print(_str):
    if debug:
        print(_str)


class MainWindow(QMainWindow):
    def __init__(self, app):
        super(MainWindow, self).__init__()
        print("MainWindow.__init__")
        screen = app.primaryScreen()
        rect = screen.availableGeometry()
        self.title = TITLE
        self.l = 0
        self.t = 0
        self.w = rect.width()
        self.h = rect.height() - self.t
        self.initUI()

    def initUI(self):
        # Set font size
        print("MainWindow.initUI")
        self.setWindowTitle(self.title)
        self.setGeometry(self.l, self.t, self.w, self.h)

        self.statusBar = self.statusBar()
        self._menuBar()
        self.main = MyLayout(self)
        self.setCentralWidget(self.main)

        self.show()

    def _menuBar(self):
        print("MainWindow._menuBar")
        menubar = self.menuBar()

        streamSrcMenu = menubar.addMenu('Stream')
        streamSrcMenu.addMenu(self._sourceMenu())
        streamSrcMenu.addAction(self._exitActMenu())
        return menubar

    def _sourceMenu(self):
        print("MainWindow._sourceMenu")
        sourceMenu = QMenu('Source', self)
        sourceMenu.addAction(self._selectWebcam0Menu())
        sourceMenu.addAction(self._selectWebcam1Menu())
        sourceMenu.addAction(self._selectVideoMenu())
        sourceMenu.addAction(self._selectRtspMenu())
        return sourceMenu

    def _webcam0(self):
        print("MainWindow._webcam0")
        self.statusBar.showMessage("Camera No.0 was selected")
        global strSrc
        strSrc = 0

    def _selectWebcam0Menu(self):
        print("MainWindow._selectWebcam0Menu")
        selectWebcam0Menu = QAction("Select Webcam 0", self)
        selectWebcam0Menu.setShortcut('Ctrl+0')
        selectWebcam0Menu.setStatusTip('Open webcam 0')
        selectWebcam0Menu.triggered.connect(self._webcam0)
        return selectWebcam0Menu

    def _webcam1(self):
        print("MainWindow._webcam1")
        self.statusBar.showMessage("Camera No.1 was selected")
        global strSrc
        strSrc = 1

    def _selectWebcam1Menu(self):
        print("MainWindow._selectWebcam1Menu")
        selectWebcam1Menu = QAction("Select Webcam 1", self)
        selectWebcam1Menu.setShortcut('Ctrl+1')
        selectWebcam1Menu.setStatusTip('Open webcam 1')
        selectWebcam1Menu.triggered.connect(self._webcam1)
        return selectWebcam1Menu

    def _showDialog(self):
        print("MainWindow._showDialog")
        fname = QFileDialog.getOpenFileName(self, 'Open file', '/home')
        if fname[0]:
            self.statusBar.showMessage("Selected video " + fname[0])
            global strSrc
            strSrc = fname[0] + '0'

    def _selectVideoMenu(self):
        print("MainWindow._selectVideoMenu")
        selectVideoMenu = QAction('Open Video', self)
        selectVideoMenu.setShortcut('Ctrl+O')
        selectVideoMenu.setStatusTip('Open available video')
        selectVideoMenu.triggered.connect(self._showDialog)
        return selectVideoMenu

    def _showInputDialog(self):
        text, ok = QInputDialog.getText(self, 'Input Dialog', 'Enter RTSP link')
        if ok:
            global strSrc
            strSrc = text + "1"
            self.statusBar.showMessage("Ready to stream " + strSrc)

    def _selectRtspMenu(self):
        selectRtspMenu = QAction('Input RTSP link', self)
        selectRtspMenu.setShortcut('Ctrl+R')
        selectRtspMenu.setStatusTip('Stream RTSP to')
        selectRtspMenu.triggered.connect(self._showInputDialog)
        return selectRtspMenu

    def _exitActMenu(self):
        print("MainWindow._exitActMenu")
        exitActMenu = QAction('Exit', self)
        exitActMenu.setShortcut('Ctrl+Q')
        exitActMenu.setStatusTip('Exit application')
        if strSrc is not None:
            self.main.faceCompareUI.stream.release()
            print("Stream was released!")
        else:
            print(strSrc)
        exitActMenu.triggered.connect(qApp.quit)
        return exitActMenu


class MyLayout(QTabWidget):
    def __init__(self, parent):
        print("MyLayout.__init__")
        super(QTabWidget, self).__init__(parent)
        self.l = parent.x()
        self.t = parent.y()
        self.w = parent.width()
        self.h = parent.height()
        self.setGeometry(QRect(self.l, self.t, self.w, self.h * 0.95))
        self.initMyUI()

    def initMyUI(self):
        print("MyLayout.initMyUI")
        self.faceCompareUI = FaceCompareUI(self)
        self.addTab(self.faceCompareUI, "Compare")

class FaceCompareUI(QGroupBox):
    def __init__(self, parent):
        super(QGroupBox, self).__init__(parent)
        self.l = parent.x()
        self.t = parent.y()
        self.h = parent.height()
        self.w = parent.width()
        if self.h < 800:
            self.rowCompareResultUI = 4
        else:
            self.rowCompareResultUI = 5
        self.stream = None
        self.timer = QTimer()
        self.flipFrame = True
        self.timer.timeout.connect(self.timeout)
        self.readingStreamFlag = False
        self.rtspConnectFlag = False
        self.rtspCaptureFlag = False
        self.status = None
        self.initTabUI()

    def initTabUI(self):
        tabLayout = QHBoxLayout(self)
        tabLayout.addWidget(self.compareResultUI())
        tabLayout.addWidget(self.streamUI())
        self.setLayout(tabLayout)

    def compareResultUI(self):
        column1 = QGroupBox("Column 1")
        column1.setGeometry(self.l, self.t, self.w * 0.4, self.h)
        column1.setMaximumWidth(self.w * 0.15)
        # column1.setMaximumHeight(self.h)
        layout = QVBoxLayout(column1)
        self.labelFaceDetected = []
        self.labelFaceSaved = []
        self.groupFace = []
        self.listIDShow = []
        self.listGenderShow = []
        self.listAgeShow = []
        self.listMaskShow = []
        self.listEmotionShow = []
        self.listGroupFace = []
        self.listLabelImg = []
        self.flag = False
        for i in range(self.rowCompareResultUI):
            groupFace = QGroupBox(str(i + 1))
            self.listGroupFace.append(groupFace)
            groupFaceLayout = QHBoxLayout(groupFace)
            labelImg = QLabel(groupFace)
            self.listLabelImg.append(labelImg)
            groupFaceLayout.addWidget(labelImg)
            groupFaceLayout.setAlignment(Qt.AlignCenter)
            groupFace.setLayout(groupFaceLayout)

        camBox = QGroupBox("Control camera")
        camBox.setMaximumHeight(self.h * 0.1)
        camBoxLayout = QHBoxLayout(camBox)
        self.flipButton = QRadioButton("Flip frame")
        self.flipButton.setChecked(True)
        self.flipButton.toggled.connect(self.onFlipClicked)
        self.resetButn = QPushButton("Clear")
        self.resetButn.setMinimumHeight(self.w * 0.03)
        self.resetButn.clicked.connect(self.resetButnHandle)
        self.camButn = QPushButton("Open Camera")
        self.camButn.setMinimumHeight(self.w * 0.03)
        self.camButn.clicked[bool].connect(self.OStream)
        self.camButn.setCheckable(True)
        # camBoxLayout.addWidget(self.flipButton)
        camBoxLayout.addWidget(self.resetButn)
        camBoxLayout.addWidget(self.camButn)
        camBox.setLayout(camBoxLayout)

        for i in range(self.rowCompareResultUI):
            layout.addWidget(self.listGroupFace[i])
        layout.addWidget(camBox)
        column1.setLayout(layout)
        return column1

    def resetButnHandle(self):
        for i in range(self.rowCompareResultUI):
            self.listGroupFace[i].setTitle(str(i + 1))
            self.listLabelImg[i].clear()
            self.listIDShow = []
            self.listGenderShow = []
            self.listAgeShow = []
            self.listMaskShow = []
            self.listEmotionShow = []

    def onFlipClicked(self):
        radioButton = self.sender()
        if radioButton.isChecked():
            self.flipFrame = True
        else:
            self.flipFrame = False

    def streamUI(self):
        column2 = QGroupBox("Column 2")
        column2.setGeometry(self.l, self.t, self.w * 0.6, self.h)
        layout = QHBoxLayout(column2)
        self.labelVideo = QLabel(column2)
        layout.addWidget(self.labelVideo)
        layout.setAlignment(Qt.AlignCenter)
        column2.setLayout(layout)
        return column2

    def OStream(self, pressed):
        if pressed:
            self.openStream()
        else:
            self.closeStream()

    def openStream(self):
        _print(strSrc)
        # import ipdb; ipdb.set_trace()
        if strSrc is not None:
            if self.stream is not None:
                self.stream.release()
            if isinstance(strSrc, int):
                if OS == 'windows':
                    self.stream = cv2.VideoCapture(strSrc + cv2.CAP_DSHOW)
                    self.rtspConnectFlag = False
                elif OS == 'jetson':
                    self.stream = cv2.VideoCapture(strSrc + cv2.CAP_V4L)
                    self.rtspConnectFlag = False
                else:
                    sys.exit(1)
            elif isinstance(strSrc, str):
                if strSrc[-1] == "0":
                    self.stream = cv2.VideoCapture(strSrc[:-1])
                    self.rtspConnectFlag = False
                elif strSrc[-1] == "1":
                    self.stream = cv2.VideoCapture(strSrc[:-1], cv2.CAP_FFMPEG)
                    self.rtspConnectFlag = True
                    self._streamThread()
                else:
                    sys.exit(1)
            self.status = None
            self.stream.set(3, 1280)
            self.stream.set(4, 960)
            _print("Open cam" + str(strSrc))
            self.timer.start(5)
            self.camButn.setText("Close camera")
        else:
            self.camButn.toggle()
            msgBox = QMessageBox.information(
                self, "Notification", "There was no Streamming Source selected")

    def closeStream(self):
        self.timer.stop()
        if self.stream is not None:
            while self.readingStreamFlag:
                _print("Wait reading!")
            if not self.rtspConnectFlag:
                self.stream.release()
                self.stream = None
            else:
                self.rtspCaptureFlag = True
            self.camButn.setText("Open camera")
        _print("Camera was closed")

    def _streamThread(self):
        self.status = None
        self.thread = Thread(target=self.streamThread, args=())
        self.thread.daemon = True
        self.thread.start()

    def streamThread(self):
        while True:
            if self.rtspCaptureFlag:
                self.stream.release()
                self.timer.stop()
                break
            self.readingStreamFlag = True
            if self.stream.isOpened():
                self.status, self.frame = self.stream.read()
            self.readingStreamFlag = False

    def timeout(self):
        global flagFaceDetect
        global ID
        # global tt_fps
        _print("----timeout")
        if self.rtspConnectFlag:
            if self.status is None:
                self.timer.start(1)
                return
            elif self.status == True:
                status, frame = self.status, self.frame
            else:
                msgBox = QMessageBox.information(
                    self, "Notification", "Run out of Stream")
                self.status = None
                # self.timer.stop()
                self.camButn.toggle()
                self.closeStream()
                return
        else:
            if self.stream is not None:
                if self.stream.isOpened():
                    status, frame = self.stream.read()
            else:
                # self.timer.stop()
                return
            if not status:
                _print("stop timer in timeout")
                if isinstance(strSrc, int):
                    msgBox = QMessageBox.information(
                        self, "Notification", "Disconnected to camera")
                elif isinstance(strSrc, str):
                    msgBox = QMessageBox.information(
                        self, "Notification", "Run out of video")
                else:
                    pass
                self.status = None
                # self.timer.stop()
                self.camButn.toggle()
                self.closeStream()
                # self.timer.start(1)
                return
        

        if self.flipFrame:
            frame = cv2.flip(frame, flipCode=1)
        heightFrame, widthFrame = frame.shape[:2]
        ratioFrame = heightFrame / widthFrame
        displayFrame = np.copy(frame)
  
        height, width, channel = displayFrame.shape
        bytesPerLine = 3 * width
        displayFrame = cv2.cvtColor(displayFrame, cv2.COLOR_BGR2RGB)
        qImg = QImage(
            displayFrame.data,
            width,
            height,
            bytesPerLine,
            QImage.Format_RGB888)
        hh = self.h * 0.9
        qImg = qImg.scaled(int(hh / ratioFrame), int(hh))
        pix = QPixmap(qImg)
        self.labelVideo.setPixmap(pix)
        self.timer.start(1)
        _print("----end--timeout")
        return



# ===== main =====================================================================

# def main():
if __name__ == '__main__':
    print("__main__")
    print("app = QApplication(sys.argv)")
    app = QApplication(sys.argv)
    print("window = MainWindow(app)")
    window = MainWindow(app)
    print("sys.exit(app.exec_())")
    sys.exit(app.exec_())
