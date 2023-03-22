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
        detect,
    };

    // ŠÖ”
    virtual ~IBlock(void) = default;

    inline void Update(void) override {};
    inline void Draw(void) override {};

    inline void SetBlockType(Type id) { type_ = id; }
    inline const Type& GetBlockType(void) { return type_; }

private:
    // •Ï”
    Type type_{ Type::NONE };
};

