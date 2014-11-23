#ifndef __BRICKSVM_DEVICE_AUDIODEVICE_HPP__
# define __BRICKSVM_DEVICE_AUDIODEVICE_HPP__

# include <SFML/Audio.hpp>
# include <device/Memory.hpp>

namespace bricksvm
{
    namespace device
    {
        class AudioDevice
        {
        public:
            AudioDevice();
            ~AudioDevice();

            void playMusic(uint8_t channel);

            void loadMusic(std::string const &progId,
                           Memory &memory,
                           uint8_t channel, 
                           uint64_t memAddr, 
                           uint32_t size);

            void loadSound(std::string const &progId,
                           Memory &memory,
                           uint8_t channel, 
                           uint64_t memAddr, 
                           uint32_t size);

            void playSound(uint8_t channel);

            void stopSound(uint8_t channel);

            void stopMusic(uint8_t channel);

            void unloadMusic(uint8_t channel);

            void unloadSound(uint8_t channel);

        private:

            typedef sf::Sound           SoundContainerType[16];
            typedef sf::SoundBuffer     SoundBufferContainerType[16];
            typedef std::vector<char>   MusicBufferContainerType[16];
            typedef sf::Music           MusicContainerType[16];

            SoundContainerType          _sounds;
            SoundBufferContainerType    _soundsBuffer;
            MusicContainerType          _musics;
            MusicBufferContainerType    _musicsBuffer;
        };
    }
}

#endif // __BRICKSVM_DEVICE_AUDIODEVICE_HPP__