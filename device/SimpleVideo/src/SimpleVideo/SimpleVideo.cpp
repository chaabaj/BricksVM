#include <memory>
#include "exception/InvalidOperationException.hpp"
#include "interpreter/Value.hpp"
#include "SimpleVideo/SimpleVideo.hpp"

extern "C"
{
    EXPORT_DLL bricksvm::event::EventThread *construct(rapidjson::Value *config)
	{
		return new bricksvm::device::SimpleVideo(config);
	}
}

namespace bricksvm
{
	namespace device
	{
		SimpleVideo::SimpleVideo(rapidjson::Value *config) : bricksvm::event::EventThread("SimpleVideo")
		{            
            using namespace std::placeholders;

            unsigned int width = SimpleVideo::_defaultWidth;
            unsigned int height = SimpleVideo::_defaultHeight;
            unsigned int colors = SimpleVideo::_defaultColors;

            this->on("svid_put_pixel", std::bind(&SimpleVideo::onPutPixel, this, _1, _2));
            this->on("svid_read_pixel", std::bind(&SimpleVideo::onReadPixel, this, _1, _2));
            this->on("svid_put_char", std::bind(&SimpleVideo::onWriteCharacter, this, _1, _2));

            if (config != nullptr)
            {
                if (config->HasMember("width"))
                {
                    width = (*config)["width"].GetUint();
                }
                if (config->HasMember("height"))
                {
                    height = (*config)["height"].GetUint();
                }
                if (config->HasMember("colors"))
                {
                    colors = (*config)["colors"].GetUint();
                }
            }
            _window.create(sf::VideoMode(width, height, colors), "Video");
            _render.create(width, height);
            _sprite.setTexture(_render.getTexture());
            if (!_window.isOpen())
            {
                throw std::runtime_error("Cannot open window");
            }
            _window.setActive(false);
            _isOpen = true;
            _displayThread = std::thread(std::bind(&SimpleVideo::display, this));
		}
		
        SimpleVideo::~SimpleVideo()
        {
            _isOpen = false;
            _displayThread.join();
		}

        void SimpleVideo::display()
        {
            sf::Clock       clock;

            clock.restart();
            _window.setActive(true);
            while (_isOpen)
            {
                if (clock.getElapsedTime().asMilliseconds() >= SimpleVideo::_frequency)
                {
                    _window.draw(_sprite);
                    _window.display();
                    clock.restart();
                }
                else
                {
                    uint32_t    waitTime = SimpleVideo::_frequency - clock.getElapsedTime().asMilliseconds();

                    sf::sleep(sf::milliseconds(waitTime));
                }
            }
        }
        
        sf::Color SimpleVideo::fromHexColor(int hexColor) const
        {
            sf::Color   color;

            color.r = hexColor >> 16 & 0xFF;
            color.g = hexColor >> 8 & 0xFF;
            color.b = hexColor & 0xFF;
            return color;
        }

        bool SimpleVideo::pixelIsVisible(int x, int y, sf::IntRect const &zone) const
        {
            if (x > zone.left && x <= (zone.left + zone.width) && y > zone.top && y < (zone.top + zone.height))
            {
                return true;
            }
            return false;
        }

        sf::Vector2f SimpleVideo::toAbsolutePosition(std::string const &progId, int x, int y) const
        {
            sf::Vector2f    realPos;
            sf::IntRect     zone;
            auto            it = _programsZone.find(progId);

            if (it != _programsZone.end())
            {
                zone = it->second;
                if (this->pixelIsVisible(x, y, zone))
                {
                    return sf::Vector2f(x + zone.left, y + zone.top);
                }
                return sf::Vector2f(-1, -1);
            }
            throw bricksvm::exception::InvalidOperationException("Unknow program");
        }

        int SimpleVideo::toHexColor(sf::Color const &color) const
        {
            return (color.r << 16) + (color.g << 8) + (color.b);
        }


        void SimpleVideo::onPutPixel(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            int                             x = msg.getParameter<interpreter::Value>(3);
            int                             y = msg.getParameter<interpreter::Value>(4);
            int                             color = msg.getParameter<interpreter::Value>(5);

            try
            {
                sf::Vector2f                    realPos = this->toAbsolutePosition(progId, x, y);

                if (realPos.x >= 0 && realPos.y >= 0)
                {
                    _image.setPixel(realPos.x, realPos.y, this->fromHexColor(color));
                    const_cast<sf::Texture&>(_render.getTexture()).update(_image.getPixelsPtr(), 1, 1, realPos.x, realPos.y);
                }
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        
        }


        void SimpleVideo::onReadPixel(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            int                             x = msg.getParameter<interpreter::Value>(3);
            int                             y = msg.getParameter<interpreter::Value>(4);

            try
            {
                sf::Vector2f    realPos = this->toAbsolutePosition(progId, x, y);
                int             hexColor;

                hexColor = this->toHexColor(_image.getPixel(realPos.x, realPos.y));
                src.emit("instruction:finished", self, progId, interpreter::Value(hexColor));
            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        }

        void SimpleVideo::onWriteCharacter(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            int                             x = msg.getParameter<interpreter::Value>(3);
            int                             y = msg.getParameter<interpreter::Value>(4);
            char                            charCode = msg.getParameter<interpreter::Value>(5);
            int                             hexColor = msg.getParameter<interpreter::Value>(6);

            try
            {
                sf::Text        text;
                sf::Vector2f    realPos = this->toAbsolutePosition(progId, x, y);

                text.setString(sf::String(charCode));
                text.setPosition(realPos);
                text.setColor(this->fromHexColor(hexColor));
                _render.draw(text);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));

            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        
        }
	}
}