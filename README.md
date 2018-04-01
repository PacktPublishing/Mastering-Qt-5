# Mastering Qt 5
This is the code repository for the book [Mastering Qt 5](https://www.packtpub.com/application-development/mastering-qt-5?utm_source=github&utm_medium=repository&utm_campaign=9781786467126), published by [Packt](https://www.packtpub.com). It contains all the supporting project files necessary to work through the book from start to finish.

<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/mastering_qt_5_cover.jpg?raw=true" width="300" height="370"></p>

## Authors
[Guillaume Lazar](https://github.com/GuillaumeLazar) and [Robin Penea](https://github.com/synapticvoid) are software engineers living near Paris in France. They founded NeuronalMotion together in 2014 to implement their vision of entrepreneurship and project development. They aim to achieve a self-organized company.

## Book description
We aim to teach the reader to be proficient with Qt mechanisms to resolve real world problems. We put a strong focus on the latest version of C++14 to see how it can fit with a well designed Qt 5 application.

Here is a summary of the covered topics:
* Create stunning UIs with Qt Widget and Qt Quick
* Develop powerful, cross-platform applications with the Qt framework
* Design GUIs with the Qt Designer and build a library in it for UI preview
* Handle user interaction with the Qt signal/slot mechanism in C++
* Prepare a cross-platform project to host a third-party library
* Build a Qt application using the OpenCV API
* Use the Qt Animation framework to display stunning effects
* Deploy mobile apps with Qt and embedded platforms

## Technical instructions
* All the code in this book can be compiled and run from Qt Creator using Qt 5.7. You can do it from your preferred OS: Windows, Linux, or Mac OS.
* About the mobile-specific chapters, either an Android or an iOS device works, but it is not mandatory (the simulator/emulator can be enough).
* Chapter 6, Even Qt deserves a slice of Raspberry Pi, offers to build an application running on a Raspberry Pi. Although it is more fun if we can do it with a real Raspberry Pi, it is not necessary to have one to complete the chapter.

## Errata
Official Packt errata page is https://www.packtpub.com/books/content/support/25651

### Chapter 2
* Add charts in .pro file, page 49/54/58 (paper book)
  * Your QT module import should be "QT += core gui charts"
  * Check the file [ch02-sysinfo.pro](https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/Chapter_02/ch02-sysinfo.pro)
* The MainWindow must define a QHBoxLayout
  * The application will crash with no layout in MainWindow
  * You can update your MainWindow.ui like this [MainWindow.ui](https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/Chapter_02/MainWindow.ui) 
  * Or you can add "ui->centralWidget->setLayout(new QHBoxLayout());" in the MainWindow constructor
  * Check this [question](https://stackoverflow.com/questions/42353352/sigsegv-when-adding-widget-in-qt) on StackOverflow
* CpuWidget typo, page 63 (paper book)
  * "we have to include the Q_OBJECT macro to allow **CpuWidget**" (not CPUWidget)
* Run the application too soon, page 65 (paper book)
  * "If you run the pplication, you should see something like this", in fact you can't run the application at this step because CpuWidget::updateSeries() is a pure virual function and we implement the body function at the page 66!
  * Page 46, there is a typo the Windows structure name, is is `FILETIME` and not `FILEFTIME`
  * Page 47, in the second bullet point, the sentence should be "The second one is retrieved when the `cpuRawData()` function is called

### Chapter 5
* Cache issue in PictureImageProvider::pictureFromCache(), page 189 (paper book)
  * Replace "mPicturesCache.contains(pictureSize)" by "mPicturesCache.contains(key)"
  * Replace "mPicturesCache[pictureSize]" by "mPicturesCache[key]"
  * Check the updated file [PictureImageProvider.cpp](https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/Chapter_05/gallery-mobile/PictureImageProvider.cpp)

### Chapter 6
* Qt3D API instability
  * Due to some changes of the Qt3D module from Qt 5.7, the code has been updated and tested for Qt 5.10.1
   * Check this [commit](https://github.com/PacktPublishing/Mastering-Qt-5/commit/06e3493a3c27a2211317f4bdb6e8c40a5c2d9982)


## Chapters description
### Chapter 1, Get Your Qt Feet Wet
Lays the fundamentals of Qt and refreshes your memory with a todo application. This chapter covers the Qt project structure, how to use the designer, basic principles of the signals and slots mechanism, and introduces new features of C++14.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_01_09.png?raw=true"></p>

### Chapter 2, Discovering QMake Secrets
Takes a deep dive in the heart of the Qt compilation system: qmake. This chapter will help you understand how it works, how to use it, and how you can structure a Qt application with platform-specific code by designing a system monitoring application.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_02_05.png?raw=true" width="729" height="501"></p>

### Chapter 3, Dividing Your Project and Ruling Your Code 
Analyzes the Qt model/view architecture and how a project can be organized by developing a custom library with the core logic of the application. The project example is a persistent gallery application.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_03_01.png?raw=true" width="729" height="194"></p>

### Chapter 4, Conquering the Desktop UI
Studies the UI perspective of the model/view architecture with a Qt Widget application relying on the library completed in the previous chapter.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_04_09.png?raw=true"></p>

### Chapter 5, Dominating the Mobile UI
Adds the missing part of the gallery application with the mobile version (Android and iOS); the chapter covers it with the use of QML, Qt Quick controls, and QML / C++ interactions.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_05_09.png?raw=true" width="729" height="583"></p>

### Chapter 6, Even Qt Deserves a Slice of Raspberry Pi
Continues to the road on Qt Quick application with the Qt 3D perspective. This chapter covers how to build a 3D snake game
targeted at the Raspberry Pi.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_06_12.png?raw=true" width="729" height="457"></p>

### Chapter 7, Third-Party Libraries Without a Headache
Covers how a third-party library can be integrated in a Qt project. OpenCV will be integrated with an image filter application that also provides a custom QDesigner plugin.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_07_06.png?raw=true"></p>

### Chapter 8, Animations, It’s Alive, Alive!
Extends the image filter application by adding animations and the ability to distribute a custom SDK to let other developers add their own filters.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_08_03.png?raw=true"></p>

### Chapter 9, Keeping Your Sanity with Multithreading
Investigates the multithreading facilities provided by Qt by building a multithreaded Mandelbrot fractal drawing application.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_09_04.png?raw=true" width="729" height="574"></p>

### Chapter 10, Need IPC? Get Your Minions to Work
Broadens the Mandelbrot fractal application by moving the calculation to other processes and managing the communication
using sockets.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_10_04.png?raw=true"></p>

### Chapter 11, Having Fun with Serialization
Covers multiple serialization formats (JSON, XML, and binary) inside a drum machine application in which you can record and load sound loops.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_11_04.png?raw=true"></p>

### Chapter 12, You Shall (Not) Pass with QTest
Adds tests to the drum machine application and studies how the Qt Test frameworks can be used to make unit tests, benchmarking, and GUI events simulation.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_12_01.png?raw=true" width="729" height="191"></p>

### Chapter 13, All Packed and Ready to Deploy
Gives insights into how to package an application on all desktop OSes (Windows, Linux, and Mac OS) and mobile platforms
(Android and iOS).
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_13_05.png?raw=true"></p>

### Chapter 14, Qt Hat Tips and Tricks
Gathers some tips and tricks to develop with Qt with pleasure. It shows how to manage sessions in Qt Creator, useful Qt Creator keyboard shortcuts, how you can customize the logging, save it to disk, and much more.
<p align="center"><img src="https://github.com/PacktPublishing/Mastering-Qt-5/blob/master/media/B05566_14_04.png?raw=true"></p>

## Other Qt books of the same publisher
* [Application Development with Qt Creator - Second Edition](https://www.packtpub.com/application-development/application-development-qt-creator-second-edition?utm_source=github&utm_medium=repository&utm_campaign=9781784398675)

* [Qt5 C++ GUI Programming Cookbook](https://www.packtpub.com/application-development/qt5-c-gui-programming-cookbook?utm_source=github&utm_medium=repository&utm_campaign=9781783280278)

* [Qt 5 Blueprints](https://www.packtpub.com/application-development/qt-5-blueprints?utm_source=github&utm_medium=repository&utm_campaign=9781784394615)

## Suggestions and Feedback
[Click here](https://docs.google.com/forms/d/e/1FAIpQLSe5qwunkGf6PUvzPirPDtuy1Du5Rlzew23UBp2S-P3wB-GcwQ/viewform) if you have any feedback or suggestions.
