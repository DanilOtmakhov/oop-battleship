#ifndef ABILITY_MANAGER_HPP
#define ABILITY_MANAGER_HPP

#include "Ability.hpp"
#include "DoubleDamageAbility.hpp"
#include "ScannerAbility.hpp"
#include "RandomHitAbility.hpp"
#include "NoAbilitiesException.hpp"
#include <random>


class AbilityManager {
    private:
        std::queue <Ability*> abilities;
    public:
        AbilityManager();
        ~AbilityManager();
        Ability* getAbility();
        void addAbility();
        void addAbility(AbilityType type);
        std::vector <AbilityType> getAbilitiesTypes();
        void checkAbilitiesEmpty();
        bool isAbilitiesEmpty();
};

#endif
