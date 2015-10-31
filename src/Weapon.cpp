#include "Weapon.hpp"

#include <cstdio>

Weapon::Weapon() {

}

Weapon::Weapon(float rateOfFire, int projectileIndex, int behavior, int weaponHUDIndex, int playerSpriteIndex) : rateOfFire(rateOfFire), projectileIndex(projectileIndex), behavior(behavior), weaponHUDIndex(weaponHUDIndex), playerSpriteIndex(playerSpriteIndex) {

}

// Default destructor

void Weapon::fire(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies) {
    switch(behavior) {
        case 0:
            fireSingleProjectile(player, projectiles, projectileInstances, enemies);
        break;
        case 1:
            fireShotgun(player, projectiles, projectileInstances, enemies);
        break;
        case 2:
            fireLaser(player, projectiles, projectileInstances, enemies);
        break;
        case 3:
            fireMelee(player, projectiles, projectileInstances, enemies);
        break;
        default:
            fireSingleProjectile(player, projectiles, projectileInstances, enemies);
        break;
    }
}

void Weapon::fireSingleProjectile(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies) {

}

void Weapon::fireShotgun(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies) {

}

void Weapon::fireLaser(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies) {

}

void Weapon::fireMelee(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies) {

}

bool Weapon::importWeapons(const std::string& weaponFilePath, std::vector<Weapon>* weaponVector, int numProjectiles) {
    std::FILE* weaponsFile = std::fopen(weaponFilePath.c_str(), "r");
    
    if (nullptr == weaponsFile) {
        fprintf(stderr, "Error: Unable to open file: %s for reading.\n", weaponFilePath.c_str());
        return false;
    }
    
    if (nullptr == weaponVector) {
        fprintf(stderr, "Error: Weapon vector is nullptr\n");
        return false;
    }
    
    bool parseSuccess = parseWeapons(weaponsFile, weaponVector, numProjectiles);
    
    std::fclose(weaponsFile);
    
    return parseSuccess;
}

bool Weapon::parseWeapons(std::FILE* weaponsFile, std::vector<Weapon>* weaponVector, int numProjectiles) {
    char buf[256];
    int intBuf[5];
    float tempFloat;
    
    int numWeapons = -1;
    
    // while we have not reached the end of the weapons file, read the next token
    while(std::fscanf(weaponsFile, "%s", buf) != EOF) {
        // switch on the first character of the line read
        switch(buf[0]) {
            // 'n', number of weapons to be defined
            case 'n': 
                std::fscanf(weaponsFile, "%d", &numWeapons);
                
                // the weapons file needs to define at least one weapon
                if (numWeapons < 1) {
                    fprintf(stderr, "Error: The weapons file must define at least one weapon.\n");
                    return false;
                }
                
                weaponVector->resize(numWeapons);
            break;
            // 'w', weapon declaration
            case 'w': 
                std::fscanf(weaponsFile, "%d %d %d %d %d %f", &intBuf[0], &intBuf[1], &intBuf[2], &intBuf[3], &intBuf[4], &tempFloat);
                
                // the rate of fire must be greater than or equal to zero
                if (tempFloat < 0.0f) {
                    fprintf(stderr, "Error: The rate of fire must be greater than or equal to zero.\n");
                    return false;
                }
                
                // we must have seen the 'n' line
                if (numWeapons < 1) {
                    fprintf(stderr, "Error: The weapons file must define the number of weapons (n) before a weapon definition (w).\n");
                    return false;
                }
                
                // the weapon index must be valid
                if (intBuf[0] < 0 || intBuf[0] >= numWeapons) {
                    fprintf(stderr, "Error: The weapon number must be greater than or equal to zero and less than the number of weapons defined.\n");
                    return false;
                }
                
                // the weapon index must be valid
                if (intBuf[0] < 0 || intBuf[0] >= numWeapons) {
                    fprintf(stderr, "Error: The weapon number must be greater than or equal to zero and less than the number of weapons defined.\n");
                    return false;
                }
                
                // the projectile index must be valid
                if (intBuf[1] < 0 || intBuf[1] >= numProjectiles) {
                    fprintf(stderr, "Error: The projectile index must be greater than or equal to zero and less than the number of projectiles defined.\n");
                    return false;
                }
                
                // both the sprite sheet indexes must be between 0 and numWeapons - 1
                if (intBuf[3] < 0 || intBuf[4] < 0 || intBuf[3] >= numWeapons || intBuf[4] >= numWeapons) {
                    fprintf(stderr, "Error: The sprite sheet positions must be greater than or equal to zero and less than the number of weapons.\n");
                    return false;
                }
                
                // don't check the behavior because we default in the fire method
                
                // create the weapon here and add it to the vector
                {
                    Weapon weapon(tempFloat, intBuf[1], intBuf[2], intBuf[3], intBuf[4]);
                    (*weaponVector)[intBuf[0]] = weapon;
                }
            break;
            // something else, ignore it
            default:
                std::fgets(buf, sizeof(buf), weaponsFile);
            break;
        }
    }
    
    return true;
}
