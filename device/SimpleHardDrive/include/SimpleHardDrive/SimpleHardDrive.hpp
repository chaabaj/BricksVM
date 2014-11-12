#ifndef __BRICKSVM_DEVICE_SIMPLEHARDDRIVE_HPP__
# define __BRICKSVM_DEVICE_SIMPLEHARDDRIVE_HPP__

# include <fstream>
# include "rapidjson/document.h"
# include "core/DllExport.hpp"
# include "event/EventThread.hpp"
# include "device/Memory.hpp"

namespace bricksvm
{
	namespace device
	{
		class EXPORT_DLL SimpleHardDrive : public bricksvm::event::EventThread
		{
			public:
			
				SimpleHardDrive(rapidjson::Value *config);
				~SimpleHardDrive();

        private:
            void onWriteMsg(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);
            void onReadMsg(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            std::size_t    readBytes(bricksvm::device::Memory &mem, 
                                     std::string const &progId,
                                     uint64_t hdAddr,
                                     uint64_t memAddr, 
                                     std::size_t size) const;

            std::size_t    writeBytes(bricksvm::device::Memory const &mem,
                                      std::string const &progId,
                                      uint64_t hdAddr, 
                                      uint64_t memAddr, 
                                      std::size_t size);


        private:
            std::string         _file;
            uint64_t            _size;
            std::fstream        _fileStream;
            static const int    _maxReadWriteSize = 30000;
		};
	}
}

#endif