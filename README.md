FenneXEmptyProject
=========

Introduction
--

FenneXEmptyProject serve as a starting point to create an iOS and Android project using FenneX. 
For more information on FenneX, see https://github.com/FenneX/FenneX
If you want to see code samples, see https://github.com/FenneX/FenneXTestProject

Setup
--
1. pull the repo

         $ git clone git@github.com:fennex/fennexemptyproject.git

2. add FenneX as a remote

         $ git remote add fennex git@github.com:fennex/fennex.git

3. when you want to update FenneX, pull it

         $ git pull fennex master
 

Building for iOS
--
Simply open the proj.ios_mac/FenneXEmptyProject.xcodeproj and run scheme EmptyProject iOS

Building for Android
--
1. create a file local.properties in proj.android which points to your Android SDK

         sdk.dir=/Path/To/Your/SDK/adt-bundle-mac/sdk/

2. make sure your gradle.properties file at ~/.gradle/gradle.properties have ANDROID_NDK_HOME path pointing to NDK r9d or newer

         ANDROID_NDK_HOME=/Path/To/Your/NDK/android-ndk-r9d

3. run Gradle from proj.android with a connected Android device

         $ ./gradlew installDebug

4. you can also import the build.gradle in Android Studio and launch it
       

Support
--
Building tested on Mac OS X 10.8 and 10.9 with Xcode 5.1 and NDK r9d
Runtime iOS 5.0+ and Android 2.3.3+

Additional features of FenneXEmptyProject
--
More than being a simple empty project, FenneXEmptyProject have a few features out of the box:
* implement back button and quit app with back on Android
* automatic reporting of language and visited scenes on Google Analytics and Flurry
* have a structure for multi-resolution support
* "Monkey" to automatically test your app

Contributors
--
* François Dupayrat
* Pierre Bertinet
* Alexandre Mili
* Vincent Te

Auticiel
--
The company behind FenneX, Auticiel, is recruiting an experienced developer in Paris, France. Contact us at jobs[at]auticiel[dot]com
