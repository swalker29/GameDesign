#include "Weapon.hpp"

#include <cstdio>
#include <cmath>
#include <memory>

#include "Game.hpp"
#include "Utils.hpp"

static constexpr float EPSILON = 0.15f;
static constexpr float CHAINSAW_DISTANCE = 1.5f;
static constexpr float CHAINSAW_ARC = 0.86f; // 30 degrees
static constexpr float CHAINSAW_DAMAGE = 2.5f;

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

Weapon::Weapon() {

}

Weapon::Weapon(float rateOfFire, int projectileIndex, int behavior, int weaponHUDIndex, int playerSpriteIndex) : rateOfFire(rateOfFire), projectileIndex(projectileIndex), behavior(behavior), weaponHUDIndex(weaponHUDIndex), playerSpriteIndex(playerSpriteIndex) {

}

// Default destructor

bool Weapon::fire(Player& player, std::vector<Projectile>* projectiles, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies, b2World* b2world) {
    if (clock.getElapsedTime().asSeconds() > rateOfFire) {
        clock.restart();
        
        playFireSound();
        
        switch(behavior) {
            case 0:
                fireSingleProjectile(player, projectiles, projectileInstances, b2world);
            break;
            case 1:
                fireShotgun(player, projectiles, projectileInstances, b2world);
            break;
            case 2:
                fireLaser(player, projectiles, projectileInstances, enemies);
            break;
            case 3:
                fireMelee(player, enemies);
            break;
            default:
                fireSingleProjectile(player, projectiles, projectileInstances, b2world);
            break;
        }
    }
}

void Weapon::fireSingleProjectile(Player& player, std::vector<Projectile>* projectiles, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, b2World* b2world) {
    createProjectile(player, projectiles, player.direction, projectileInstances, b2world);	
}

void Weapon::fireShotgun(Player& player, std::vector<Projectile>* projectiles, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, b2World* b2world) {
	for (int x = -3; x <= 3; x++) {
	    float theta = x * M_PI / 90.0f; // 1.5 degree spread between each projectile
	    sf::Vector2f direction(player.direction.x * std::cos(theta) - player.direction.y * std::sin(theta), player.direction.x * std::sin(theta) + player.direction.y * std::cos(theta));
	    createProjectile(player, projectiles, direction, projectileInstances, b2world);
    }
}

void Weapon::fireLaser(Player& player, std::vector<Projectile>* projectiles, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies) {
}

void Weapon::fireMelee(Player& player, std::list<std::unique_ptr<Enemy>>* enemies) {
	// We need to check all of the enemies to see if they are in.
	// We intersect the enemy's bounding circle with an arc. Check the distance and then check the angle.
	for (auto& enemy : *enemies) {
	    float distanceSq = distanceSquared(player.position, enemy->position);
	    
	    if (distanceSq < (CHAINSAW_DISTANCE + enemy->circle.m_radius)*(CHAINSAW_DISTANCE + enemy->circle.m_radius)) {
	        sf::Vector2f direction = enemy->position - player.position;
	        normalizeVector2f(direction);
	        float dot = dotProductVector2f(player.direction, direction);
	        
	        if (dot > CHAINSAW_ARC) {
	            enemy->health -= CHAINSAW_DAMAGE;
            }
        }
    }
	
	//playFireSound();
}

void Weapon::createProjectile(Player& player, std::vector<Projectile>* projectiles, sf::Vector2f direction, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, b2World* b2world) {
    float radiusSum = player.circle.m_radius + (*projectiles)[projectileIndex].circle.m_radius + EPSILON;
    
    std::unique_ptr<ProjectileInstance> projectileInstance(new ProjectileInstance(projectileIndex, player.position + radiusSum * direction, direction, &((*projectiles)[projectileIndex].circle), b2world));
    
    // set the velocity
    sf::Vector2f vel = direction * (*projectiles)[projectileIndex].velocity;
    b2Vec2 velocity(vel.x, vel.y);
    projectileInstance->b2body->SetLinearVelocity(velocity);
    
    projectileInstances->push_back(std::move(projectileInstance));
    
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
                std::fscanf(weaponsFile, "%d %d %d %d %d %f %s", &intBuf[0], &intBuf[1], &intBuf[2], &intBuf[3], &intBuf[4], &tempFloat, buf);
                
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
                    
                    std::string soundFile(buf);
                    if(!(*weaponVector)[intBuf[0]].sBuffer.loadFromFile(soundFile)) {
		                fprintf(stderr, "Error: Unable to weapon sound file: %s\n", buf);
		                return false;
	                }
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

void Weapon::playFireSound() {
    Game::playSound(sBuffer);
}
