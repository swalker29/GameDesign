#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <list>
#include <string>
#include <vector>

#include <Box2D/Box2D.h>
#include <SFML/Audio.hpp>

#include "Enemy.hpp"
#include "Player.hpp"
#include "ProjectileInstance.hpp"

class Projectile {
    public:
        float damage;
        float velocity;
        
        int behavior; // how this projectile behaves on impact
        int projectileSpriteIndex;
        int soundNumber;
		
		sf::SoundBuffer sBuffer;
		sf::Sound impactSound;
		
        b2CircleShape circle; // can get the radius through here
        
        Projectile();
        
        Projectile(float damage, float velocity, int behavior, int projectileSpriteIndex);
        
        // Default destructor
        
        void impact(ProjectileInstance& projectileInstance, Player& player, std::list<std::unique_ptr<Enemy>>* enemies, Character* characterHit);
        
        static bool importProjectiles(const std::string& projectileFilePath, std::vector<Projectile>* projectileVector);
        
    private:
        void bulletImpact(Character* characterHit);
        void explosiveImpact(ProjectileInstance& projectileInstance, Player& player, std::list<std::unique_ptr<Enemy>>* enemies, Character* characterHit);
        void webImpact(Character* characterHit);
        
        static bool parseProjectiles(std::FILE* projectilesFile, std::vector<Projectile>* projectileVector);
        
        void playImpactSound();
};
#endif
