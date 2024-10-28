#ifndef ABILITIES_HPP
#define ABILITIES_HPP

#include "Field.hpp"
#include "Structs.hpp"

class Ability {
    public:
        virtual ~Ability() = default;
        virtual void apply_ability() = 0;
};

class DoubleDamageAbility : public Ability {
    private:
        Field& field;
        Coordinate coordinate;
    public:
        DoubleDamageAbility(Field& field, Coordinate coordinate);
        void apply_ability() override;
};

class ScannerAbility : public Ability {
    private:
        Field& field;
        Coordinate coordinate;
    public:
        ScannerAbility(Field& field, Coordinate coordinate);
        void apply_ability() override;
};

class RandomHitAbility : public Ability {
    private:
        Field& field;
    public:
        RandomHitAbility(Field& field);
        void apply_ability() override;
};

#endif
