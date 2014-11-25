#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include "exception/InvalidOperationException.hpp"
#include "interpreter/Value.hpp"
#include "SimpleVideo/SimpleVideo.hpp"
#include "core/Console.hpp"
#include "device/Memory.hpp"

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

            if (SDL_Init(SDL_INIT_VIDEO) < 0 == -1)
            {
                throw bricksvm::exception::InvalidOperationException(SDL_GetError());
            }
            bricksvm::core::Console::log(this->getName()) << "initialize " << this->getName() << std::endl;
            this->on("svid_put_pixel", std::bind(&SimpleVideo::onPutPixel, this, _1, _2));
            this->on("svid_read_pixel", std::bind(&SimpleVideo::onReadPixel, this, _1, _2));
            this->on("svid_put_char", std::bind(&SimpleVideo::onWriteCharacter, this, _1, _2));
            this->on("svid_init", std::bind(&SimpleVideo::onInitialize, this, _1, _2));
            this->on("svid_write_buffer", std::bind(&SimpleVideo::onWriteBuffer, this, _1, _2));
            this->on("svid_get_width", std::bind(&SimpleVideo::onGetScreenWidth, this, _1, _2));
            this->on("svid_get_height", std::bind(&SimpleVideo::onGetScreenHeight, this, _1, _2));
            this->on("svid_get_pixel_format", std::bind(&SimpleVideo::onGetPixelFormat, this, _1, _2));
            this->on("svid_put_number", std::bind(&SimpleVideo::onWriteNumber, this, _1, _2));
            bricksvm::core::Console::success(this->getName()) << this->getName() << " initialized" << std::endl;
		}
		
        SimpleVideo::~SimpleVideo()
        {
            SDL_Quit();
            bricksvm::core::Console::success(this->getName()) << " closed" << std::endl;
		}

        void SimpleVideo::onInitialize(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            uint16_t                        width = msg.getParameter<interpreter::Value>(3);
            uint16_t                        height = msg.getParameter<interpreter::Value>(4);
            uint8_t                         nbColors = msg.getParameter<interpreter::Value>(5);

            try
            {
                _screens[progId].initialize(width, height, nbColors);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
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
                _screens[progId].putPixel(x, y, color);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

        void SimpleVideo::onWriteBuffer(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &mem = msg.getParameter<Memory>(1);
            std::string                     progId = msg.getParameter<std::string>(2);
            int                             x = msg.getParameter<interpreter::Value>(3);
            int                             y = msg.getParameter<interpreter::Value>(4);
            uint32_t                        memAddr = msg.getParameter<interpreter::Value>(5);
            uint32_t                        size = msg.getParameter<interpreter::Value>(6);

            try
            {
                std::vector<uint8_t>   buffer;

                buffer.resize(size);
                mem.read(progId, memAddr, &buffer[0], size);
                _screens[progId].putPixels(x, y, &buffer[0], size);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

        void SimpleVideo::onGetScreenHeight(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            uint32_t                        height;

            height = _screens[progId].getHeight();
            src.emit("instruction:finished", self, progId, interpreter::Value(height));
        }

        void SimpleVideo::onGetPixelFormat(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            uint32_t                        pixelFormat;

            pixelFormat = _screens[progId].getPixelFormat();
            src.emit("instruction:finished", self, progId, interpreter::Value(pixelFormat));
        }

        void SimpleVideo::onGetScreenWidth(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            uint32_t                        width;

            width = _screens[progId].getWidth();
            src.emit("instruction:finished", self, progId, interpreter::Value(width));

        }

        void SimpleVideo::onReadPixel(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            int                             x = msg.getParameter<interpreter::Value>(3);
            int                             y = msg.getParameter<interpreter::Value>(4);

            try
            {
                uint32_t    hexColor;

                hexColor = _screens[progId].getPixelColor(x, y);
                src.emit("instruction:finished", self, progId, interpreter::Value(hexColor));
            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        }

        void SimpleVideo::onWriteNumber(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     progId = msg.getParameter<std::string>(2);
            int                             x = msg.getParameter<interpreter::Value>(3);
            int                             y = msg.getParameter<interpreter::Value>(4);
            interpreter::Value const        &number = msg.getParameter<interpreter::Value>(5);
            uint32_t                        charSize = msg.getParameter<interpreter::Value>(6);
            int                             hexColor = msg.getParameter<interpreter::Value>(7);

            try
            {
                _screens[progId].putText(x, y, charSize, number.toString(), hexColor);
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
            uint32_t                        charSize = msg.getParameter<interpreter::Value>(6);
            int                             hexColor = msg.getParameter<interpreter::Value>(7);

            try
            {
                std::string str;

                str.resize(1);
                str[0] = charCode;
                _screens[progId].putText(x, y, charSize, str, hexColor);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));

            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", self, progId, std::string(err.what()));
            }
        
        }
	}
}