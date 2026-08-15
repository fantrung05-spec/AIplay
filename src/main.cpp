#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static bool g_aiEnabled = true;
static float g_scanDistance = 60.0f;

class $modify(AIPlayPlayer, PlayerObject) {
    void update(float dt) {
        PlayerObject::update(dt);

        if (!g_aiEnabled || !PlayLayer::get()) return;

        auto playerPos = this->getPosition();
        CCRect scanBox = CCRect(
            playerPos.x + 5.0f,
            playerPos.y - 10.0f,
            g_scanDistance,
            40.0f
        );

        auto playLayer = PlayLayer::get();
        auto objects = playLayer->m_objects;

        bool hasObstacleAhead = false;

        if (objects) {
            for (int i = 0; i < objects->count(); ++i) {
                auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
                if (!obj || obj->m_isDestroyed) continue;

                if (scanBox.intersectsRect(obj->getObjectRect())) {
                    if (obj->m_objectType == GameObjectType::Hazard || 
                        obj->m_objectType == GameObjectType::Spike) {
                        hasObstacleAhead = true;
                        break;
                    }
                }
            }
        }

        if (hasObstacleAhead && this->m_isOnGround) {
            this->pushButton(PlayerButton::Jump);
        }
    }
};

