# Integration instruction for Android. #

There are 3 components which you have to implement in your application. All components are located in tke "**Lib\Android**" folder.

1.  **PeakNdkWrapper** - NDK wrapper written in Java. It makes communication between Java-side and native library.
2.  **peak-sdk-<version>.aar** and **peak-sdk-<version>-test server.aar** - target peak SDKs. Difference between those 2 packages is server connection. The former uses the "live" server, latter uses the "test" server. You have to choose either of them according to your purpose. The PeakNdkWrapper uses this module for advertiising.
3.  **peakSdkModule** - folder with NDK modules for different architectures.

Information about the android project architecture is located in the "**project\Android\readme.html**" file.

## How to integrate the Peak sdk into the android cocos2dx project? ##

**Attach native modules:** 

1. Open your cocos2dx project.
2. Copy the **peakSdkModule** folder to the **proj.android-studio\app\jni** folder.
3. Open the Android.mk file of your project. 
4. To attach the native module you have to do the next:  
   Add `$(call import-add-path, $(LOCAL_PATH))` line after all `$(call import-add-path )` declarations to make header from the peak sdk visible.  
   Add `LOCAL_WHOLE_STATIC_LIBRARIES := peakSdkModule` line somewhere in the middle.  
   Add `$(call import-module, ./peakSdkModule)` in the end of the file after `$(call import-module,.)` line.
5. Open Application.mk.
   You have to implement ABI compatibility at least for 2 platforms: armeabi and armeabi-v7a.  
   Add `LOCAL_LDLIBS := -landroid -llog` line in the Application.mk file.

Example of the Android.mk file:

```xml
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)
$(call import-add-path, $(LOCAL_PATH))

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := peakSdkModule

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module, ./peakSdkModule)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
```

**Setup android studio project.**

1. In the Android Studio import **PeakNdkWrapper.aar** and **peak-sdk-<version>.aar** packages. To import packages go to the File→New→New Module→Import .JAR/.AAR Package menu, and then select appropriate packages.
2. On the next step you have to establish module dependencies.
In the Android studio, right click on your project, select “Open Module settings”, select your cocos2dx project, go to the “Dependencies” tab, Add the PeakNdkWrapper module and the peak-sdk-<version>.
3. Include Google Play Services to your application's build.gradle for better compatibility:
```java

 dependencies {  
        ...  
        compile 'com.google.android.gms:play-services-ads:8.4.0'  
        compile 'com.google.android.gms:play-services-location:8.4.0'  
        ...  
  } 
```

**Modify AppActivity file in your android cocos2dx project.**  

Implementation of the Peak SDK for cocos2dx requires a few changes in the main .java file.

1. Open AppActivity.java file (this file must be created automatically by cocos2dx deploy system, as enter point for the android projects.) 
2. You have to initialize the PeakNdkWrapper. To do this just add the next code to the AppActivity.java file  


```java

public class AppActivity extends Cocos2dxActivity {
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        PeakNdkWrapper.init(this);
    }
    protected void onPause() {
        PeakNdkWrapper.onPause();
        super.onPause();
    }
    @Override
    protected void onResume() {
        super.onResume();
        PeakNdkWrapper.onResume();
    }
    @Override
    protected void onDestroy() {
        PeakNdkWrapper.onDestroy();
        super.onDestroy();
    }
}
```

After all changes in the your cocos2dx project for android you have to rebuild native modules. You can do this by using the next command `cocos compile -p android –-android-studio` in the **proj.android-studio** folder.

# Integration instruction for iOS. #

To implement the peak SDK for iOS you have to deploy original PeakSDK iOS framework to the "**proj.ios_mac**" folder of your cocos2dx project. Read this documentation [iOS PeakSDK](https://github.com/peakmediation/Peak-Mediation-iOS-SDK) for deployment up to the "Using PeakSDK" topic.  
When you deploy PeakSDK iOS framework, you have to open the "**Lib/IOS**" folder, add the **libPeakSdkWrapper.a** library and the **PeakSdkModule** folder with headers to your project.

1. Copy the PeakSdkModule folder form the "**Lib/IOS**" to the "**proj.ios_mac/ios folder**".
2. In the Xcode, right click on the **ios** folder, click "Add files to <your project name>", add  the copied **PeakSdkModule** folder to the project.
3. In the project settings select tab "Build Phases".
4. In the menu "Link Binary With Libraries" add the **libPeakSdkWrapper.a** library from the "**Lib/IOS**" folder.

*Additional information*: There is possibility to change advertising server between "test" and "live". To change it you have to use **PKEndPointEnvironment.h** header and insert the next code somewhere in your project. ( for example in the main.m file ):  
 ```
 [[PKEndPointEnvironment sharedInstance] setMode:PKEndPointEnvironmentModeTest];
 ```
- for the "test" server or  
 ```
 [[PKEndPointEnvironment sharedInstance] setMode:PKEndPointEnvironmentModeLive];
 ```
- for the "live" server.

# Using Peak sdk. #
1. In your cocos2dx project initialize library with your application id:  
 ```
 PeakSdk::CPeakSdkApi::Initialize(PEAK_APP_ID);
 ```
2. Check ad availability for specified zone:  
 ```
 bool isAvailable = PeakSdk::CPeakSdkApi::CheckAdAvailable(AD_ZONE_ID);
 ```
3. Show interstitial ad:  
 ```
 PeakSdk::CPeakSdkApi::ShowInterstitial(AD_ZONE_ID);
 ```
4. Show banner:  
**xPos, yPos** - banner positions on the screen.  
**width, height** - banner size.  
 ```
 PeakSdk::CPeakSdkApi::ShowBanner(AD_ZONE_ID, xPos, yPos, width, height);
 ```
5. Remove banner from the screen:  
 ```
 PeakSdk::CPeakSdkApi::RemoveBanner();
 ```
6. Get native ad. Native Ads will allow developers to show ads in custom formats in their applications. The next function returns structure with information about advertising:  
 ``` 
 PeakSdk::CPeakNativeAd data = PeakSdk::CPeakSdkApi::ShowNativeAd(NATIVE_AD_ZONE_ID);
 ```
7. Unlike Banner and Interstitial ads, the impressions and clicks are not automatically handled, and need to be wrapped when events do occur. Call the next method to track that native ad for current zone was shown:  
 ``` 
 PeakSdk::CPeakSdkApi::TrackNativeAdShown(NATIVE_AD_ZONE_ID);
 ```
8. Use the next method to handle click on the "Call to Action" button. Call of this method will redirect the user to the website for that ad:   
 ``` 
 PeakSdk::CPeakSdkApi::HandleNativeAdClicked(NATIVE_AD_ZONE_ID);
 ```
9. You can use API listeners to get notifications from the JAVA Peak SDK listener when something is changed. For example you can process notifications when the Peak SDK is initialized:    
 ``` 
 PeakSdk::CPeakSdkApi::SetInitializationSuccessListener( [] ()
    {
       ... Your code ...
    } );
 ```
 10. Make async call that checks ad availability and executes completionBlock if ad is available and async call is not canceled. All UI changes should be handled in completionBlock, do not change UI in other place, if you use this call.

 std::unique_ptr< PeakSdk::CPeakAsyncAdRequestInterface > asyncReq = PeakSdk::CPeakSdkApi::createAsyncRequest( AD_ZONE_ID );
 asyncReq->start( [this]( std::string id )
   {
      /*do something here*/
   });
If you want to cancel async call use following method:
   asyncReq->cancel();

Don’t forget to cancel async request if you don’t need one anymore. It prevent unexpected ads presentations and other unhandled behaviour.

10. Get more personalized ads with higher revenue. Just provide consumer's targeting info:
```
   PeakSdk::ETargetGender g = PeakSdk::ETargetGender::ETargetGenderUnspecified;
   /*
   g = PeakSdk::ETargetGender::ETargetGenderMale;
   g = PeakSdk::ETargetGender::ETargetGenderFemale;   
   */
   PeakSdk::CPeakSdkApi::setTargetingGender( g );
   
   PeakSdk::CPeakSdkApi::setTargetingAge( age );
```
   You must set this info before calling `PeakSdk::CPeakSdkApi::Initialize( PEAK_APP_ID )` method.