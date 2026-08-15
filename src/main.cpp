#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static bool g_aiEnabled = true;
static float g_scanDistance = 60.0f;

class $modify(AIPlayPlayer, PlayerObject) {
    void update(float dt) {
        PlayerObject::update(dt);

        auto playLayer = PlayLayer::get();
        if (!g_aiEnabled || !playLayer) return;

        auto playerPos = this->getPosition();
        CCRect scanBox = CCRect(
            playerPos.x + 5.0f,
            playerPos.y - 10.0f,
            g_scanDistance,
            40.0f
        );

        bool hasObstacleAhead = false;
        auto objects = playLayer->m_objects;

        if (objects) {
            for (int i = 0; i < objects->count(); ++i) {
                auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
                if (!obj || obj->m_isDestroyed) continue;

                if (scanBox.intersectsRect(obj->getObjectRect())) {
                    // Trong Geode SDK v3, kiem tra vat can bang m_objectType
                    if (obj->m_objectType == GameObjectType::Spike || 
                        obj->m_objectType == GameObjectType::Hazard) {
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
