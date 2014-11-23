#ifndef __BRICKSVM_DEVICE_SIMPLEAUDIO_HPP__
# define __BRICKSVM_DEVICE_SIMPLEAUDIO_HPP__

# include <SFML/Audio.hpp>
# include "rapidjson/document.h"
# include "core/DllExport.hpp"
# include "event/EventThread.hpp"
# include "AudioDevice.hpp"

namespace bricksvm
{
	namespace device
	{
		class EXPORT_DLL SimpleAudio : public bricksvm::event::EventThread
		{
			public:
			
				SimpleAudio(rapidjson::Value *config);
				~SimpleAudio();

        private:
            void    onPlayMusic(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void    onPlaySound(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void    onLoadMusic(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void    onLoadSound(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void    onUnloadMusic(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void    onUnloadSound(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void    onStopSound(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void    onStopMusic(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
        private:
            typedef std::map<std::string, AudioDevice>   AudioDeviceContainerType;

            AudioDeviceContainerType    _audioDevices;
		};
	}
}

#endif