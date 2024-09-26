#ifndef KDATAPROCESSOR_H
#define KDATAPROCESSOR_H
#include <cstdint>
class KDataProcessor
{
public:
    virtual ~KDataProcessor() = default;
    virtual bool addPacket(const uint8_t* packet, int length) = 0;
    virtual bool isComplete() const = 0;
    virtual void reset() = 0;
};

#endif // KDATAPROCESSOR_H
