#pragma once
#include "IEntity.h"
#include <DxLib.h>

class IBlock :
    public IEntity
{
public:
    // íËã`
    enum class Type
    {
        NONE,
        BASIC,
        STONE,
    };

    static constexpr float defaultRadius_{ 16.f};

    // ä÷êî
    IBlock(const Vector2& pos, const Vector2& radius);
    virtual ~IBlock(void) = default;

    inline virtual void Update(void) {};
    inline virtual void Draw(void) { DrawBox(GetPos().x - defaultRadius_, GetPos().y + defaultRadius_, GetPos().x + defaultRadius_, GetPos().y - defaultRadius_, 0xff0000, false); };

    inline void SetType(const Type& type) { type_ = type; }
    inline const Type& GetType(void) { return type_; }

private:
    // ïœêî
    Type type_{Type::NONE};
};

