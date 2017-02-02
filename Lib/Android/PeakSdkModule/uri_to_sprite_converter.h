#ifndef PEAKSDKNDKMODULE_URITOSPRITECONVERTER_H
#define PEAKSDKNDKMODULE_URITOSPRITECONVERTER_H
#include "cocos2d.h"
#include <functional>
#include <string>
#include "cocos2d.h"
namespace PeakSdk
{
   class URIToSpriteConverter
   {
   public:
      static void apply( const std::string&& path, const std::function<void( cocos2d::Sprite* )> callback );
   };
}

#endif //PEAKSDKNDKMODULE_URITOSPRITECONVERTER_H
