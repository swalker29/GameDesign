#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <list>
#include <string>
#include <vector>

class Projectile {
    public:
        float damage;
        float velocity;
        float radius;
        
        int behavior; // how this projectile behaves on impact
        int projectileSpriteIndex;
        
        // collision entity
        
        Projectile();
        
        Projectile(float damage, float velocity, float radius, int behavior, int projectileSpriteIndex);
        
        // Default destructor
        
        //void impact(std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        
        static bool importProjectiles(const std::string& projectileFilePath, std::vector<Projectile>* projectileVector);
        
    private:
        //void fireSingleProjectile(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        //void fireShotgun(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        //void fireLaser(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        //void fireMelee(Player& player, std::vector<Projectile>* projectiles, std::list<ProjectileInstance>* projectileInstances, std::list<std::unique_ptr<Enemy>>* enemies);
        
        static bool parseProjectiles(std::FILE* projectilesFile, std::vector<Projectile>* projectileVector);
};
#endif
