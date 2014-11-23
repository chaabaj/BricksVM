#include <memory>
#include <functional>
#include "interpreter/Value.hpp"
#include "SimpleHardDrive/SimpleHardDrive.hpp"
#include "exception/InvalidOperationException.hpp"
#include "core/String.hpp"
#include "core/Console.hpp"

extern "C"
{
    EXPORT_DLL bricksvm::event::EventThread *construct(rapidjson::Value *config)
	{
		return new bricksvm::device::SimpleHardDrive(config);
	}
}

namespace bricksvm
{
	namespace device
	{
		SimpleHardDrive::SimpleHardDrive(rapidjson::Value *config) : bricksvm::event::EventThread("SimpleHardDrive")
		{
            using namespace std::placeholders;

            bricksvm::core::Console::log(this->getName()) << "initialize " << this->getName() << std::endl;
            bricksvm::core::throwIf<std::runtime_error>(config == nullptr, "Configuration not found");
            _file = (*config)["disk-file"].GetString();
            _size = bricksvm::core::getMemSize((*config)["size"].GetString());
            bricksvm::core::Console::log(this->getName()) << "disk size : " << ((*config)["size"]).GetString() << std::endl;
            bricksvm::core::Console::log(this->getName()) << "try to open the virtual hard drive file" << _file << std::endl;
            _fileStream.open(_file.c_str(), std::ios::binary | std::ios::in | std::ios::out);
            bricksvm::core::throwIf<std::runtime_error>(!_fileStream.is_open(), "No such file");
            this->on("shd_read", std::bind(&SimpleHardDrive::onReadMsg, this, _1, _2));
            this->on("shd_write", std::bind(&SimpleHardDrive::onWriteMsg, this, _1, _2));
            bricksvm::core::Console::success(this->getName()) << this->getName() << " initialized" << std::endl;
		}
		
		SimpleHardDrive::~SimpleHardDrive()
		{
            bricksvm::core::Console::log(this->getName()) << "close the hard drive" << std::endl;
            _fileStream.close();
            bricksvm::core::Console::success(this->getName()) << "closed" << std::endl;

		}

        void SimpleHardDrive::onWriteMsg(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            bricksvm::device::Memory        &mem = msg.getParameter<bricksvm::device::Memory>(1);
            std::string                     &prgId = msg.getParameter<std::string>(2);
            uint64_t                        hdAddr = msg.getParameter<interpreter::Value>(3);
            uint64_t                        memAddr = msg.getParameter<interpreter::Value>(4);
            std::size_t                     size = msg.getParameter<interpreter::Value>(5);
            std::size_t                     bytesWritten;

            try
            {
                bricksvm::core::Console::log("SHD write") << "hdAddr : " << hdAddr << " memAddr : " << memAddr << " size : " << size << std::endl;
                bytesWritten = this->writeBytes(mem, prgId, hdAddr, memAddr, size);
                src.emit("instruction:finished", std::ref(*this), prgId, interpreter::Value(bytesWritten));

            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", std::ref(*this), prgId, std::string(err.what()));
            }
        }

        void SimpleHardDrive::onReadMsg(bricksvm::event::EventThread &self, bricksvm::event::Message &msg)
        {
            bricksvm::event::EventThread    &src = msg.getParameter<bricksvm::event::EventThread>(0);
            bricksvm::device::Memory        &mem = msg.getParameter<bricksvm::device::Memory>(1);
            std::string                     &prgId = msg.getParameter<std::string>(2);
            uint64_t                        hdAddr = msg.getParameter<interpreter::Value>(3);
            uint64_t                        memAddr = msg.getParameter<interpreter::Value>(4);
            std::size_t                     size = msg.getParameter<interpreter::Value>(5);
            std::size_t                     bytesReaded;

            try
            {
                bytesReaded = this->readBytes(mem, prgId, hdAddr, memAddr, size);
                src.emit("instruction:finished", std::ref(*this), prgId, interpreter::Value(bytesReaded));
            }
            catch (bricksvm::exception::InvalidOperationException &err)
            {
                src.emit("instruction:error", std::ref(*this), prgId, std::string(err.what()));
            }
        }

        std::size_t SimpleHardDrive::readBytes(bricksvm::device::Memory &mem, 
                                               std::string const &prgId,
                                               uint64_t hdAddr, 
                                               uint64_t memAddr, 
                                               std::size_t size) const
        {
            std::vector<char>   bytes;

            if (size > SimpleHardDrive::_maxReadWriteSize)
            {
                size = SimpleHardDrive::_maxReadWriteSize;
            }
            bytes.resize(size);
            const_cast<std::fstream&>(_fileStream).seekg(hdAddr, std::ios::beg);
            const_cast<std::fstream&>(_fileStream).read(&bytes[0], size);
            mem.write(prgId, memAddr, &bytes[0], _fileStream.gcount());
            return _fileStream.gcount();
        }

        std::size_t SimpleHardDrive::writeBytes(bricksvm::device::Memory const &mem, 
                                                std::string const &prgId,
                                                uint64_t hdAddr, 
                                                uint64_t memAddr, 
                                                std::size_t size)
        {
            std::vector<char>   bytes;

            if (size > SimpleHardDrive::_maxReadWriteSize)
            {
                size = SimpleHardDrive::_maxReadWriteSize;
            }
            bytes.resize(size);
            bricksvm::core::Console::log("SHD write") << hdAddr << std::endl;
            _fileStream.seekp(hdAddr, std::ios::beg);
            mem.read(prgId, memAddr, &bytes[0], size);
            bricksvm::core::Console::log("SHD write ") << bytes[0] << std::endl;
            _fileStream.write(&bytes[0], size);
            _fileStream.flush();
            bricksvm::core::Console::log("SHD write") << "size : " << _fileStream.gcount() << std::endl;
            return _fileStream.gcount();
        }
	}
}