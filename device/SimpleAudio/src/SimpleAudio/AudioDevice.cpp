#include <core/Utils.hpp>
#include <exception/InvalidOperationException.hpp>
#include "SimpleAudio/AudioDevice.hpp"
#include "core/Console.hpp"

namespace bricksvm
{
    namespace device
    {
        AudioDevice::AudioDevice()
        {
            bricksvm::core::Console::log("SimpleAudio") << "create new audio device" << std::endl;
        }

        AudioDevice::~AudioDevice()
        {
            bricksvm::core::Console::log("SimpleAudio") << "destroy new audio device" << std::endl;
        }

        void AudioDevice::loadMusic(std::string const &progId,
                                    Memory &memory,
                                    uint8_t channel,
                                    uint64_t memAddr,
                                    uint32_t size)
        {
            bricksvm::core::throwIf<bricksvm::exception::InvalidOperationException>(channel >= 16, "Channel is too high");

            _musics[channel].stop();
            _musicsBuffer[channel].resize(size);
            memory.read(progId, memAddr, &_musicsBuffer[channel][0], size);
            _musics[channel].openFromMemory(&_musicsBuffer[channel][0], size);
        }

        void AudioDevice::loadSound(std::string const &progId,
                                    Memory &memory,
                                    uint8_t channel,
                                    uint64_t memAddr,
                                    uint32_t size)
        {
            std::vector<char>   buffer;

            bricksvm::core::throwIf<bricksvm::exception::InvalidOperationException>(channel >= 16, "Channel is too high");
            _sounds[channel].stop();
            buffer.resize(size);
            memory.read(progId, memAddr, &buffer[0], size);
            _soundsBuffer[channel].loadFromMemory(&buffer[0], size);
        }

        void AudioDevice::playMusic(uint8_t channel)
        {
            bricksvm::core::throwIf<bricksvm::exception::InvalidOperationException>(channel >= 16, "Channel is too high");
            _musics[channel].play();
        }

        void AudioDevice::playSound(uint8_t channel)
        {
            bricksvm::core::throwIf<bricksvm::exception::InvalidOperationException>(channel >= 16, "Channel is too high");
            _sounds[channel].play();
        }

        void AudioDevice::stopMusic(uint8_t channel)
        {
            bricksvm::core::throwIf<bricksvm::exception::InvalidOperationException>(channel >= 16, "Channel is too high");

            _musics[channel].stop();
        }

        void AudioDevice::stopSound(uint8_t channel)
        {
            bricksvm::core::throwIf<bricksvm::exception::InvalidOperationException>(channel >= 16, "Channel is too high");

            _sounds[channel].stop();
        }

        void AudioDevice::unloadMusic(uint8_t channel)
        {
            bricksvm::core::throwIf<bricksvm::exception::InvalidOperationException>(channel >= 16, "Channel is too high");

            _musics[channel].stop();
            _musicsBuffer[channel].clear();
        }

        void AudioDevice::unloadSound(uint8_t channel)
        {
            bricksvm::core::throwIf<bricksvm::exception::InvalidOperationException>(channel >= 16, "Channel is too high");

            _sounds[channel].stop();
            _sounds[channel] = sf::Sound();
            _soundsBuffer[channel] = sf::SoundBuffer();
        }
    }
}