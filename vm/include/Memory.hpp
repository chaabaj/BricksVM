#ifndef __BRICKSVM_MEMORY_HPP__
# define __BRICKSVM_MEMORY_HPP__

# include <string>
# include <vector>
# include <memory>
# include <unordered_map>
# include "event/EventThread.hpp"

namespace bricksvm
{
    class Memory
    {
    public:
        
        Memory(unsigned int size, std::vector<std::string> const &progIds);
        ~Memory();

        template<typename T>
        void write(std::string const &progId, uint64_t addr, T *buffer, uint64_t size)
        {
            uint64_t    realAddr = this->getRealAddr(progId, addr);
            auto        lastAddr = _memIndexes[progId].second;
            uint64_t    j = 0;

            if (realAddr + size > lastAddr)
            {
                throw bricksvm::exception::InvalidOperationException("Memory overflow");
            }
            std::memcpy(_memory.get() + realAddr, buffer, size * sizeof(T));
        }

        template<typename T>
        void read(std::string const &progId, uint64_t addr, T *buffer, uint64_t size) const
        {
            uint64_t    realAddr = this->getRealAddr(progId, addr);
            auto        lastAddr = (*_memIndexes.find(progId)).second.second;
            uint64_t    j = 0;

            if (realAddr + size > lastAddr)
            {
                throw bricksvm::exception::InvalidOperationException("Memory overflow");
            }
            std::memcpy(buffer, _memory.get() + realAddr, size * sizeof(T));
        }

        void onRead(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

        void onWrite(bricksvm::event::EventThread &self, bricksvm::event::Message &msg);

    private:
        uint64_t    getRealAddr(std::string const &progId, uint64_t virtualAddr) const;

    private:
        typedef std::pair<uint64_t, uint64_t>               IndexMemoryType;
        typedef std::unordered_map<std::string, IndexMemoryType>    IndexMemoryMapType;
        typedef std::unique_ptr<char>                               MemoryBufferType;

        MemoryBufferType    _memory;
        unsigned int        _size;
        IndexMemoryMapType  _memIndexes;
    };
}

#endif // __BRICKSVM_MEMORY_HPP__