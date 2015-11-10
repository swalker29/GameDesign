#include "Projectile.hpp"

#include <cstdio>

Projectile::Projectile() {

}

Projectile::Projectile(float damage, float velocity, int behavior, int projectileSpriteIndex) : damage(damage), velocity(velocity), behavior(behavior), projectileSpriteIndex(projectileSpriteIndex) {

}

// Default destructor

/*
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
*/
bool Projectile::importProjectiles(const std::string& projectileFilePath, std::vector<Projectile>* projectileVector) {
    std::FILE* projectilesFile = std::fopen(projectileFilePath.c_str(), "r");
    
    if (nullptr == projectilesFile) {
        fprintf(stderr, "Error: Unable to open file: %s for reading.\n", projectileFilePath.c_str());
        return false;
    }
    
    if (nullptr == projectileVector) {
        fprintf(stderr, "Error: Projectile vector is nullptr\n");
        return false;
    }
    
    bool parseSuccess = parseProjectiles(projectilesFile, projectileVector);
    
    std::fclose(projectilesFile);
    
    return parseSuccess;
}

bool Projectile::parseProjectiles(std::FILE* projectilesFile, std::vector<Projectile>* projectileVector) {
    char buf[256];
    int intBuf[3];
    float floatBuf[3];
    
    int numProjectiles = -1;
    
    // while we have not reached the end of the projectile file, read the next token
    while(std::fscanf(projectilesFile, "%s", buf) != EOF) {
        // switch on the first character of the line read
        switch(buf[0]) {
            // 'n', number of projectiles to be defined
            case 'n': 
                std::fscanf(projectilesFile, "%d", &numProjectiles);
                
                // the projectiles file needs to define at least one projectile
                if (numProjectiles < 1) {
                    fprintf(stderr, "Error: The projectiles file must define at least one projectile.\n");
                    return false;
                }
                
                projectileVector->resize(numProjectiles);
            break;
            // 'p', projectile declaration
            case 'p': 
                std::fscanf(projectilesFile, "%d %d %d %f %f %f", &intBuf[0], &intBuf[1], &intBuf[2], &floatBuf[0], &floatBuf[1], &floatBuf[2]);
                
                // the damage, velocity, and radius must be greater than zero
                if (floatBuf[0] <= 0.0f || floatBuf[1] <= 0.0f || floatBuf[2] <= 0.0f) {
                    fprintf(stderr, "Error: The damage, velocity, and radius must be greater than zero.\n");
                    return false;
                }
                
                // we must have seen the 'n' line
                if (numProjectiles < 1) {
                    fprintf(stderr, "Error: The projectiles file must define the number of weapons (n) before a projectile definition (w).\n");
                    return false;
                }
                
                // the projectile index must be valid
                if (intBuf[0] < 0 || intBuf[0] >= numProjectiles) {
                    fprintf(stderr, "Error: The projectile number must be greater than or equal to zero and less than the number of projectiles defined.\n");
                    return false;
                }
                
                // the sprite sheet index must be between 0 and numProjectiles - 1
                if (intBuf[2] < 0 || intBuf[2] >= numProjectiles) {
                    fprintf(stderr, "Error: The sprite sheet position must be greater than or equal to zero and less than the number of projectiles.\n");
                    return false;
                }
                
                // don't check the behavior because we default in the impact method
                
                // create the weapon here and add it to the vector
                {
                    Projectile projectile(floatBuf[0], floatBuf[1], intBuf[1], intBuf[2]);
                    projectile.circle.m_p.Set(0.0f, 0.0f);
                    projectile.circle.m_radius = floatBuf[2];
                    (*projectileVector)[intBuf[0]] = projectile;
                }
            break;
            // something else, ignore it
            default:
                std::fgets(buf, sizeof(buf), projectilesFile);
            break;
        }
    }
    
    return true;
}