#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <list>
#include <string>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>

#include "Enemy.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "ProjectileInstance.hpp"

class Weapon {
    public:
        float rateOfFire; // in seconds
        int projectileIndex; // represents which projectile this gun fires
        int behavior; // how this weapon shoots
        int weaponHUDIndex;
        int playerSpriteIndex;
        
		sf::SoundBuffer sBuffer;
		sf::Sound weaponSound;
		
        Weapon();
        
        Weapon(float rateOfFire, int projectileIndex, int behavior, int weaponHUDIndex, int playerSpriteIndex);
        
        // Default destructor
        
        void fire(Player& player, std::vector<Projectile>* projectiles, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies, b2World* b2world);
        
        static bool importWeapons(const std::string& weaponFilePath, std::vector<Weapon>* weaponVector, int numProjectiles);
        
    private:
        void fireSingleProjectile(Player& player, std::vector<Projectile>* projectiles, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, b2World* b2world);
        void fireShotgun(Player& player, std::vector<Projectile>* projectiles, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, b2World* b2world);
        void fireLaser(Player& player, std::vector<Projectile>* projectiles, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        void fireMelee(Player& player, std::vector<Projectile>* projectiles, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        
        void createProjectile(Player& player, std::vector<Projectile>* projectiles, sf::Vector2f direction, std::list<std::unique_ptr<ProjectileInstance>>* projectileInstances, b2World* b2world);
        
        static bool parseWeapons(std::FILE* weaponsFile, std::vector<Weapon>* weaponVector, int numProjectiles);
        
        void playFireSound(const std::string& soundFile);
};
#endif
