#pragma once
#include "IEntity.h"
#include <array>

class IBlock : public IEntity
{
public:
    // ’è‹`
    enum class Type
    {
        NONE,
        BASIC,
        STONE,
    };

    // ŠÖ”
    virtual ~IBlock(void) = default;

    inline void Update(void) override {};
    inline void Draw(void) override {};

    inline void SetBlockType(Type id) { type_ = id; }

private:
    // •Ï”
    Type type_{ Type::NONE };
};

