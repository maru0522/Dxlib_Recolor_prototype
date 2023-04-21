#pragma once
#include "IEntity.h"

class IBlock :
    public IEntity
{
protected:
    // ��`
    enum class Type
    {
        NONE,
        BASIC,
        STONE,
    };

public:
    static constexpr float defaultRadius_{ 16.f};

    // �֐�
    virtual ~IBlock(void) = default;

    inline virtual void Update(void) = 0;
    inline virtual void Draw(void) = 0;

    inline void SetType(const Type& type) { type_ = type; }
    inline const Type& GetType(void) { return type_; }

private:
    // �ϐ�
    Type type_{Type::NONE};
};

