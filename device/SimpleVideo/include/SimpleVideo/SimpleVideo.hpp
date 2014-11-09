#ifndef __BRICKSVM_DEVICE_SIMPLEVIDEO_HPP__
# define __BRICKSVM_DEVICE_SIMPLEVIDEO_HPP__

# include <map>
# include <SFML/Graphics.hpp>
# include "rapidjson/document.h"
# include "core/DllExport.hpp"
# include "event/EventThread.hpp"

namespace bricksvm
{
	namespace device
	{
		class EXPORT_DLL SimpleVideo : public bricksvm::event::EventThread
		{
			public:
			
				SimpleVideo(rapidjson::Value *config);
				~SimpleVideo();

        private:
            void onPutPixel(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onReadPixel(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onWriteCharacter(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            sf::Color       fromHexColor(int color) const;
            int             toHexColor(sf::Color const &color) const;
            sf::Vector2f    toAbsolutePosition(std::string const &progId, int x, int y) const;
            bool            pixelIsVisible(int x, int y, sf::IntRect const &zone) const;

            void            display();


        private:
            typedef std::map<std::string, sf::IntRect>  ProgramZoneMapType;

            sf::RenderWindow    _window;
            sf::Image           _image;
            sf::RenderTexture   _render;
            std::thread         _displayThread;
            bool                _isOpen;
            sf::Sprite          _sprite;
            ProgramZoneMapType  _programsZone;

            static const int    _defaultWidth = 640;
            static const int    _defaultHeight = 480;
            static const int    _defaultColors = 32;
            static const int    _frequency = 60 / 25;
		};
	}
}

#endif