#include "../include/AbilityManager.hpp"


AbilityManager::AbilityManager() {
    std::vector <Ability*> defaultAbilities = {
        new DoubleDamageAbility(),
        new ScannerAbility(),
        new RandomHitAbility()
    };

    std::random_device randomDevice;
    std::mt19937 g(randomDevice());
    std::shuffle(defaultAbilities.begin(), defaultAbilities.end(), g);

    for (auto ability : defaultAbilities) {
        abilities.push(ability);
    }
}

AbilityManager::~AbilityManager() {
    while (!abilities.empty()) {
        delete abilities.front();
        abilities.pop();
    }
}

Ability* AbilityManager::getAbility() {
    if (abilities.empty()) {
        throw NoAbilitiesException();
    }

    Ability* ability = abilities.front();
    abilities.pop();
    return ability;
}

void AbilityManager::addAbility() {
    int randomAbilityIndex = std::rand() % 3;
    switch (randomAbilityIndex) {
        case 0:
            abilities.push(new DoubleDamageAbility());
            break;
        case 1:
            abilities.push(new ScannerAbility());
            break;
        case 2:
            abilities.push(new RandomHitAbility());
            break;
        default:
            break;
    }
}

void AbilityManager::addAbility(AbilityType type) {
    switch (type) {
        case AbilityType::DoubleDamage:
            abilities.push(new DoubleDamageAbility());
            break;
        case AbilityType::Scanner:
            abilities.push(new ScannerAbility());
            break;
        case AbilityType::RandomHit:
            abilities.push(new RandomHitAbility());
            break;
        default:
            break;
    }
}

void AbilityManager::checkAbilitiesEmpty() {
    if (abilities.empty()) {
        throw NoAbilitiesException();;
    }
}

bool AbilityManager::isAbilitiesEmpty() {
    if (abilities.empty()) {
        return true;
    }
    return false;
}

std::vector <AbilityType> AbilityManager::getAbilitiesTypes() {
    std::vector<AbilityType> abilityTypes;
    std::queue<Ability*> tempQueue = abilities;

    while (!tempQueue.empty()) {
        Ability* ability = tempQueue.front();
        tempQueue.pop();

        if (ability) {
            abilityTypes.push_back(ability->getAbilityType());
        }
    }

    return abilityTypes;
}
