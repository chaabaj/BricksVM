#include <SDL_ttf.h>
#include "SimpleVideo/Screen.hpp"
#include "core/Console.hpp"
#include "exception/InvalidOperationException.hpp"


namespace bricksvm
{
    namespace device
    {
        Screen::Screen()
        {
            _window = nullptr;
            bricksvm::core::Console::log("SimpleVideo") << "Create a new screen" << std::endl;
            _running = false;
        }

        Screen::~Screen()
        {
            bricksvm::core::Console::log("SimpleVideo") << "Waiting displayer thread" << std::endl;
            if (_running == true)
            {
                _running = false;
                _displayThread.join();
            }
            SDL_DestroyWindow(_window);
            SDL_FreeSurface(_render);
            bricksvm::core::Console::log("SimpleVideo") << "closed" << std::endl;
        }

        void Screen::display(uint16_t width, uint16_t height, uint8_t colors)
        {
            uint32_t    oldTime = SDL_GetTicks();
            uint32_t    currentTime = oldTime;
            uint32_t    diffTime;
            SDL_Event   evt;
            SDL_Surface *windowSurface;

            bricksvm::core::Console::log("SimpleVideo") << "Opening a new window" << std::endl;
            _window = SDL_CreateWindow("Screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
            _render = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0, 0, 0, 0);
            windowSurface = SDL_GetWindowSurface(_window);
            _running = true;
            _condVar.notify_one();
            while (_running)
            {
                SDL_PollEvent(&evt);
                currentTime = SDL_GetTicks();
                diffTime = currentTime - oldTime;
                if (diffTime < Screen::_frequency)
                {
                    SDL_Delay(Screen::_frequency - diffTime);
                    currentTime = SDL_GetTicks();
                    oldTime = currentTime;
                }
                SDL_BlitSurface(_render, NULL, windowSurface, NULL);
                SDL_UpdateWindowSurface(_window);
            }
            bricksvm::core::Console::success("SimpleVideo") << "Window opened" << std::endl;
        }

        void Screen::initialize(uint16_t width, uint16_t height, uint8_t nbColors)
        {
            if (_window == nullptr)
            {
                _displayThread = std::thread(std::bind(&Screen::display, this, width, height, nbColors));
                {
                    LockType    lock(_mutex);

                    _condVar.wait(lock, [this]()
                    {
                        return _running;
                    });
                }
            }
        }

        void Screen::putPixel(uint32_t x, uint32_t y, uint32_t color)
        {
            int         bpp = _render->format->BytesPerPixel;
            uint8_t     *pixel = reinterpret_cast<uint8_t*>(_render->pixels) + y * _render->pitch + x * bpp;

            switch (bpp)
            {
            case 1:
                *pixel = color;
            case 2:
                *reinterpret_cast<uint16_t*>(pixel) = color;
            case 3:
            {
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                {
                    pixel[0] = (color >> 16) & 0xff;
                    pixel[1] = (color >> 8) & 0xff;
                    pixel[2] = (color & 0xff);
                }
                else
                {
                    pixel[0] = color & 0xff;
                    pixel[1] = (color >> 8) & 0xff;
                    pixel[2] = (color >> 16) & 0xff;
                }
            }
            case 4:
                *reinterpret_cast<uint32_t*>(pixel) = color;
            default:
                break;
            }
        }

        uint32_t Screen::getPixelColor(uint32_t x, uint32_t y) const
        {
            int         bpp = _render->format->BytesPerPixel;
            uint8_t     *pixel = reinterpret_cast<uint8_t*>(_render->pixels) + y * _render->pitch + x * bpp;

            switch (bpp)
            {
            case 1:
                return *pixel;
            case 2:
                return *reinterpret_cast<uint16_t*>(pixel);
            case 3:
            {
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                {
                    return pixel[0] << 16 | pixel[1] << 8 | pixel[2];
                }
                return pixel[0] | pixel[1] << 8 | pixel[2] << 16;
            }
            case 4:
                return *reinterpret_cast<uint32_t*>(pixel);
            default:
                return 0;
            }
        }

        void Screen::putPixels(uint32_t x, 
                               uint32_t y, 
                               uint8_t *pixels,
                               uint32_t size)
        {
            int         bpp = _render->format->BytesPerPixel;
            uint8_t     *dstPtr = reinterpret_cast<uint8_t*>(_render->pixels) + y * _render->pitch + x * bpp;

            std::memcpy(dstPtr, pixels, size);
        }

        uint32_t    Screen::getWidth() const
        {
            return _render->w;
        }

        uint32_t    Screen::getHeight() const
        {
            return _render->h;
        }

        uint32_t    Screen::getPixelFormat() const
        {
            return _render->format->BitsPerPixel;
        }


        void Screen::putChar(uint32_t x, 
                             uint32_t y, 
                             uint32_t charSize, 
                             uint8_t c,
                             uint32_t color)
        {

        }
    }
}