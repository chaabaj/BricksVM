#include <memory>
#include "interpreter/Value.hpp"
#include "SimpleAudio/SimpleAudio.hpp"
#include "core/Console.hpp"

extern "C"
{
    EXPORT_DLL bricksvm::event::EventThread *construct(rapidjson::Value *config)
	{
		return new bricksvm::device::SimpleAudio(config);
	}
}

namespace bricksvm
{
	namespace device
	{
		SimpleAudio::SimpleAudio(rapidjson::Value *config) : bricksvm::event::EventThread("SimpleAudio")
		{
            using namespace std::placeholders;

            bricksvm::core::Console::log(this->getName()) << "initialize " << this->getName() << std::endl;
            this->on("saudio_play_music", std::bind(&SimpleAudio::onPlayMusic, this, _1, _2));
            this->on("saudio_play_sound", std::bind(&SimpleAudio::onPlaySound, this, _1, _2));
            this->on("saudio_load_music", std::bind(&SimpleAudio::onLoadMusic, this, _1, _2));
            this->on("saudio_load_sound", std::bind(&SimpleAudio::onLoadSound, this, _1, _2));
            this->on("saudio_stop_music", std::bind(&SimpleAudio::onPlayMusic, this, _1, _2));
            this->on("saudio_stop_sound", std::bind(&SimpleAudio::onPlayMusic, this, _1, _2));
            this->on("saudio_play_music", std::bind(&SimpleAudio::onPlayMusic, this, _1, _2));
            bricksvm::core::Console::success(this->getName()) << this->getName() << " Initialized" << std::endl;

		}
		
		SimpleAudio::~SimpleAudio()
		{
            bricksvm::core::Console::log(this->getName()) << "closed" << std::endl;
		}

        void SimpleAudio::onPlayMusic(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     &progId = msg.getParameter<std::string>(2);
            uint8_t                         channel = msg.getParameter<interpreter::Value>(3);
            
            try
            {
                _audioDevices[progId].playMusic(channel);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

        void SimpleAudio::onPlaySound(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            std::string                     &progId = msg.getParameter<std::string>(2);
            uint8_t                         channel = msg.getParameter<interpreter::Value>(3);

            try
            {
                _audioDevices[progId].playSound(channel);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

        void SimpleAudio::onLoadMusic(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &mem = msg.getParameter<Memory>(1);
            std::string                     &progId = msg.getParameter<std::string>(2);
            uint8_t                         channel = msg.getParameter<interpreter::Value>(3);
            uint64_t                        memAddr = msg.getParameter<interpreter::Value>(4);
            uint32_t                        size = msg.getParameter<interpreter::Value>(5);

            try
            {
                _audioDevices[progId].loadMusic(progId, mem, channel, memAddr, size);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

        void SimpleAudio::onLoadSound(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &mem = msg.getParameter<Memory>(1);
            std::string                     &progId = msg.getParameter<std::string>(2);
            uint8_t                         channel = msg.getParameter<interpreter::Value>(3);
            uint64_t                        memAddr = msg.getParameter<interpreter::Value>(4);
            uint32_t                        size = msg.getParameter<interpreter::Value>(5);

            try
            {
                _audioDevices[progId].loadSound(progId, mem, channel, memAddr, size);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

        void SimpleAudio::onStopMusic(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &mem = msg.getParameter<Memory>(1);
            std::string                     &progId = msg.getParameter<std::string>(2);
            uint8_t                         channel = msg.getParameter<interpreter::Value>(3);

            try
            {
                _audioDevices[progId].stopMusic(channel);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

        void SimpleAudio::onStopSound(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &mem = msg.getParameter<Memory>(1);
            std::string                     &progId = msg.getParameter<std::string>(2);
            uint8_t                         channel = msg.getParameter<interpreter::Value>(3);

            try
            {
                _audioDevices[progId].stopSound(channel);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

        void SimpleAudio::onUnloadMusic(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &mem = msg.getParameter<Memory>(1);
            std::string                     &progId = msg.getParameter<std::string>(2);
            uint8_t                         channel = msg.getParameter<interpreter::Value>(3);

            try
            {
                _audioDevices[progId].unloadMusic(channel);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

        void SimpleAudio::onUnloadSound(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            Memory                          &mem = msg.getParameter<Memory>(1);
            std::string                     &progId = msg.getParameter<std::string>(2);
            uint8_t                         channel = msg.getParameter<interpreter::Value>(3);

            try
            {
                _audioDevices[progId].unloadSound(channel);
                src.emit("instruction:finished", self, progId, interpreter::Value(0));
            }
            catch (bricksvm::exception::InvalidOperationException &ex)
            {
                src.emit("instruction:error", self, progId, std::string(ex.what()));
            }
        }

	}
}