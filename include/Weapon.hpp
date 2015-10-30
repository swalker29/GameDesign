#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <list>
#include <vector>

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
        
        Weapon(float rateOfFire, int projectileIndex, int behavior, int weaponHUDIndex, int playerSpriteIndex);
        
        // Default destructor
        
        void fire(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        
    private:
        void fireSingleProjectile(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        void fireShotgun(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        void fireLaser(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        void fireMelee(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
};
#endif
