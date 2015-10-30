#include "Weapon.hpp"

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
