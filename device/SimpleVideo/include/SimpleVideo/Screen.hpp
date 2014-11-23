#ifndef __BRICKSVM_DEVICE_SCREEN_HPP__
# define __BRICKSVM_DEVICE_SCREEN_HPP__

# include <memory>
# include <thread>
# include <mutex>
# include <condition_variable>
# include <SDL.h>
# include "core/DllExport.hpp"

namespace bricksvm
{
    namespace device
    {
        class EXPORT_DLL Screen
        {
        public:
            Screen();
            ~Screen();

            void        initialize(uint16_t width, uint16_t height, uint8_t nbColors);
            void        putPixel(uint32_t x, uint32_t y, uint32_t color);
            void        putPixels(uint32_t x, 
                                  uint32_t y, 
                                  uint8_t *pixels, 
                                  uint32_t size);
            uint32_t    getPixelColor(uint32_t x, uint32_t y) const;
            void        putChar(uint32_t x, 
                                uint32_t y, 
                                uint32_t charSize, 
                                uint8_t c,
                                uint32_t color);
            uint32_t    getWidth() const;
            uint32_t    getHeight() const;
            uint32_t    getPixelFormat() const;

        private:
            void display(uint16_t width, uint16_t height, uint8_t colors);

        private:

            typedef std::unique_lock<std::mutex>    LockType;
           
            std::thread             _displayThread;
            bool                    _running;
            SDL_Window              *_window;
            SDL_Surface             *_render;
            std::mutex              _mutex;
            std::condition_variable _condVar;

            static const int    _frequency = 60 / 25;
        };
    }
}

#endif