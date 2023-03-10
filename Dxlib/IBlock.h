#pragma once
#include "IEntity.h"
#include <array>

class IBlock : public IEntity
{
public:
    // 定義
    enum class Type
    {
        NONE,
        BASIC,
        STONE,
    };

    // 関数
    virtual ~IBlock(void) = default;

    inline void Update(void) override {};
    inline void Draw(void) override {};

    inline void SetBlockType(Type id) { type_ = id; }

private:
    // 変数
    Type type_{ Type::NONE };
};

