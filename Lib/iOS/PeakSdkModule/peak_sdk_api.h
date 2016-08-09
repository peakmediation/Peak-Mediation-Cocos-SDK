#ifndef PROJ_PEAK_SDK_API_H
#define PROJ_PEAK_SDK_API_H

#include <functional>
#include <string>

namespace PeakSdk
{
    class CPeakNativeAd
    {
    public:
        CPeakNativeAd();
        CPeakNativeAd( const std::string& actionText,
                      const std::string& icon,
                      const std::string& mainImage,
                      const std::string& text,
                      const std::string& title );
        
        std::string getActionText() const;
        std::string getIcon() const;
        std::string getMainImage() const;
        std::string getText() const;
        std::string getTitle() const;
        
    private:
        std::string m_actionText;
        std::string m_icon;
        std::string m_mainImage;
        std::string m_text;
        std::string m_title;
    };
    
    class CPeakSdkApi
    {
    public:
        //////////////////////////////////////// API SDK Functions ////////////////////////////////////////
        /** @function Initialize
         Initializes Peak Sdk with the given application id
         @param[in] peakAppId - application id.
         */
        static void  Initialize( const char* peakAppId );
        
        /** @function CheckAdAvailable
         Check if an advertising is available by given advertising zone.
         @param[in] adZoneId - advertising zone. The parameter could be for banner or interstitial advertising.
         */
        static bool CheckAdAvailable( const char* adZoneId );
        
        /** @function ShowInterstitial
         Show fullscreen advertising.
         @param[in] adZoneId - advertising zone. The parameter could be for banner or interstitial advertising.
         */
        static void ShowInterstitial( const char* adZoneId );
        
        /** @function ShowBanner
         Show little banner on the screen with advertising
         @param[in] adZoneId - advertising zone. The parameter could be for banner or interstitial advertising.
         @param[in] xPos - banner X position from the left side of the screen.
         @param[in] yPos - banner Y position from the top side of the screen.
         @param[in] width - banner width.
         @param[in] height - banner height.
         */
        static void ShowBanner( const char* adZoneId, int xPos, int yPos, int width, int height );
        
        /** @function RemoveBanner
         Remove existed banner from the screen.
         */
        static void RemoveBanner();
        
        //////////////////////////////////////// API Native SDK Functions  ////////////////////////////////////////
        
        /** @function ShowNativeAd
         Get native ad. Native Ads will allow developers to show ads in custom formats in their applications:
         @param[in] nativeAdId - advertising zone.
         @return information about native ad.
         */
        static CPeakNativeAd ShowNativeAd( const char* nativeAdId );
        
        /** @function TrackNativeAdShown
         Unlike Banner and Interstitial ads, the impressions and clicks are not automatically handled, and need to be wrapped when events do occur.
         Call the next method to track that native ad for current zone was shown:
         @param[in] nativeAdId - advertising zone.
         */
        static void TrackNativeAdShown( const char* nativeAdId );
        
        /** @function HandleNativeAdClicked
         Use the next method to handle click on the "Call to Action" button.
         Call of this method will redirect the user to the website for that ad:
         @param[in] nativeAdId - advertising zone.
         */
        static void HandleNativeAdClicked( const char* nativeAdId );
        
        //////////////////////////////////////// API Callbacks ////////////////////////////////////////
        
        /** @function SetInitializationSuccessListener
         Set listener for the OnInitializationSuccess event.
         @param[in] callback - the callback is called when the event is occurred.
         */
        static void SetInitializationSuccessListener( const std::function<void()>& callback );
        
        /** @function SetInitializationFailedListener
         Set listener for the didFailInitializationWithError event.
         @param[in] callback - the callback is called when the event is occurred.
         */
        static void SetInitializationFailedListener( const std::function<void( const std::string& )>& callback );
        
        /** @function SetBannerShowSuccessListener
         Set listener for the didShowBanner event.
         @param[in] callback - the callback is called when the event is occurred.
         */
        static void SetBannerShowSuccessListener( const std::function<void(const std::string&)>& callback );
        
        /** @function SetBannerShowFailedListener
         Set listener for the didFailToShowBannerWithError event.
         @param[in] callback - the callback is called when the event is occurred.
         @warning the target thread, where the callback will be called, depends on implementation of the PeakSdkListenerAdapter class.
         The callback preferably should be called in the android UI Thread.
         */
        static void SetBannerShowFailedListener( const std::function<void( const std::string&,const std::string& )>& callback );
        
        /** @function SetInterstitialShowSuccessListener
         Set listener for the didShowInterstitial event.
         @param[in] callback - the callback is called when the event is occurred.
         */
        static void SetInterstitialShowSuccessListener( const std::function<void(const std::string&)>& callback );
        
        /** @function SetInterstitialShowFailedListener
         Set listener for the didFailToShowInterstitialWithError event.
         @param[in] callback - the callback is called when the event is occurred.
         */
        static void SetInterstitialShowFailedListener( const std::function<void( const std::string&, const std::string& )>& callback );
        
        /** @function SetInterstitialClosedListener
         Set listener for the didCloseInterstitial event.
         @param[in] callback - the callback is called when the event is occurred.
         */
        static void SetInterstitialClosedListener( const std::function<void(const std::string&)>& callback );
        
        /** @function SetCompletedRewardExperienceListener
         Set listener for the didCompleteRewardExperience event.
         @param[in] callback - the callback is called when the event is occurred.
         */
        static void SetCompletedRewardExperienceListener( const std::function<void(const std::string&)>& callback );
        
        /** @function SetShowNativeAdFailedListener
         Set listener for the didFailToShowNativeWithError event.
         @param[in] callback - the callback is called when the event is occurred.
         */
        static void SetShowNativeAdFailedListener( const std::function<void(const std::string&, const std::string&)>& callback );
    };
}
#endif //PROJ_PEAK_SDK_API_H