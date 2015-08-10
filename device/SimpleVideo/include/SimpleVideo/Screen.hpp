#ifndef __BRICKSVM_DEVICE_SCREEN_HPP__
# define __BRICKSVM_DEVICE_SCREEN_HPP__

# include <memory>
# include <thread>
# include <mutex>
# include <vector>
# include <condition_variable>
# include <SDL.h>
# include "interpreter/Value.hpp"
# include "core/DllExport.hpp"
# include "core/NewPolicy.hpp"

namespace bricksvm
{
    namespace device
    {
        class EXPORT_DLL Screen : public bricksvm::core::NewPolicy<Screen>
        {
        public:
            Screen(uint64_t const videoBufferSize);
            ~Screen();

            void        initialize(uint16_t width, uint16_t height, uint8_t nbColors);
            void        putPixel(uint32_t x, uint32_t y, uint32_t color);
            void        writeVideoMemory(uint64_t index, 
                                         uint8_t *pixels,
                                         uint64_t size);

            void        drawFromVideoMemory(uint64_t index, 
                                            uint16_t x, 
                                            uint16_t y,
                                            uint16_t width, 
                                            uint16_t height, 
                                            uint8_t bpp);
            void        putText(uint32_t x,
                                uint32_t y,
                                uint32_t charSize,
                                std::string const &str,
                                uint32_t color);
            uint32_t    getPixelColor(uint32_t x, uint32_t y) const;
            uint32_t    getWidth() const;
            uint32_t    getHeight() const;
            uint32_t    getPixelFormat() const;
            void        clearScreen();

        private:
            void display(uint16_t width, uint16_t height, uint8_t colors);

            static TTF_Font *initFont();
            static void freeFont();


            uint32_t    rgbToHex(uint8_t *buffer, uint8_t bpp) const;

        private:

            typedef std::unique_lock<std::mutex>    LockType;
            typedef std::vector<char>               VideoMemoryType;
           
            std::thread             _displayThread;
            bool                    _running;
            SDL_Window              *_window;
            SDL_Surface             *_render;
            VideoMemoryType         _videoMem;
            std::mutex              _mutex;
            std::condition_variable _condVar;

            static const int            _frequency = 60 / 25;
            static TTF_Font             *_font;
        };
    }
}

#endif