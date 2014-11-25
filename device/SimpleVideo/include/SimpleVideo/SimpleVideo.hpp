#ifndef __BRICKSVM_DEVICE_SIMPLEVIDEO_HPP__
# define __BRICKSVM_DEVICE_SIMPLEVIDEO_HPP__

# include <map>
# include "SimpleVideo/Screen.hpp"
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
            void onInitialize(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onPutPixel(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onReadPixel(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onWriteBuffer(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onGetScreenWidth(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onGetScreenHeight(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onGetPixelFormat(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onWriteCharacter(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onWriteNumber(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);


        private:
            typedef std::map<std::string, Screen>   ScreenContainerType;

            ScreenContainerType _screens;
		};
	}
}

#endif