#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <list>
#include <vector>

class Projectile {
    public:
        float damage;
        float velocity;
        
        int behavior; // how this projectile behaves on impact
        int projectileSpriteIndex;
        
        // collision entity
        
        Projectile(float damage, float velocity, int behavior, int weaponHUDIndex, int playerSpriteIndex);
        
        // Default destructor
        
        //void impact(std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        
    private:
        //void fireSingleProjectile(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        //void fireShotgun(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        //void fireLaser(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        //void fireMelee(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
};
#endif
