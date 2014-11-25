#ifndef __BRICKSVM_DEVICE_MEMORY_HPP__
# define __BRICKSVM_DEVICE_MEMORY_HPP__

# include <string>
# include <vector>
# include <memory>
# include <unordered_map>
# include <cstring>
# include "exception/InvalidOperationException.hpp"
# include "event/EventThread.hpp"
# include "core/DllExport.hpp"

namespace bricksvm
{
    namespace device
    {
        class EXPORT_DLL Memory
        {
        public:

            Memory(unsigned int size, std::vector<std::string> const &progIds);
            ~Memory();

            template<typename T>
            void write(std::string const &progId, uint64_t addr, T *buffer, uint64_t size)
            {
                uint64_t    realAddr = this->getRealAddr(progId, addr);
                auto        lastAddr = _memIndexes[progId].second;
                char        *dest;

                if (realAddr + size > lastAddr)
                {
                    throw bricksvm::exception::InvalidOperationException("Memory overflow");
                }
                dest = _memory.get() + realAddr;
                std::memcpy(dest, buffer, static_cast<std::size_t>(size * sizeof(T)));
            }

            template<typename T>
            void read(std::string const &progId, uint64_t addr, T *buffer, uint64_t size) const
            {
                uint64_t    realAddr = this->getRealAddr(progId, addr);
                auto        lastAddr = (*_memIndexes.find(progId)).second.second;
                char        *src;

                if (realAddr + (size * sizeof(T)) > lastAddr)
                {
                    throw bricksvm::exception::InvalidOperationException("Memory overflow");
                }
                src = _memory.get() + realAddr;
                std::memcpy(buffer, src, size * sizeof(T));
            }

            const char *getMemAddr(std::string const &progId, uint64_t addr, uint64_t size) const;

            void onRead(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            void onWrite(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

            uint64_t    getRealAddr(std::string const &progId, uint64_t virtualAddr) const;

            void dumpMemory(std::string const &progId, std::pair<uint64_t, uint64_t> const &range) const;

            void onDumpMemory(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

        private:
            typedef std::pair<uint64_t, uint64_t>             IndexMemoryType;
            typedef std::map<std::string, IndexMemoryType>    IndexMemoryMapType;
            typedef std::unique_ptr<char>                     MemoryBufferType;

            MemoryBufferType    _memory;
            unsigned int        _size;
            IndexMemoryMapType  _memIndexes;
        };

    }
}

#endif // __BRICKSVM_DEVICE_MEMORY_HPP__