#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(AIPlayPlayer, PlayerObject) {
    void update(float dt) {
        PlayerObject::update(dt);
        
        // Logic auto jump co ban an toan 100% de test build
        if (this->m_isOnGround) {
            this->pushButton(PlayerButton::Jump);
        }
    }
};
