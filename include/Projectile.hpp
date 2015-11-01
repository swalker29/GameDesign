#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <list>
#include <string>
#include <vector>

#include <Box2D/Box2D.h>

class Projectile {
    public:
        float damage;
        float velocity;
        
        int behavior; // how this projectile behaves on impact
        int projectileSpriteIndex;
        
        b2CircleShape circle; // can get the radius through here
        
        Projectile();
        
        Projectile(float damage, float velocity, int behavior, int projectileSpriteIndex);
        
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
