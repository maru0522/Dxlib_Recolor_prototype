#pragma once
#include "IEntity.h"

class IBlock :
    public IEntity
{
public:
    // 定義
    enum class Type
    {
        NONE,
        BASIC,
        STONE,
    };

    static constexpr float defaultRadius_{ 16.f};

    // 関数
    virtual ~IBlock(void) = default;

    inline virtual void Update(void) {};
    inline virtual void Draw(void) {};

    inline void SetType(const Type& type) { type_ = type; }
    inline const Type& GetType(void) { return type_; }

private:
    // 変数
    Type type_{Type::NONE};
};

