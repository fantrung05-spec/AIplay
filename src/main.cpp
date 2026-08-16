#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static bool g_aiEnabled = false;
static float g_scanDistance = 60.0f;

// 1. Logic AI quet vat can va tu dong nhay
class $modify(AIPlayer, PlayerObject) {
    void update(float dt) {
        PlayerObject::update(dt);

        if (!g_aiEnabled || !this->m_isOnGround) return;

        auto playLayer = PlayLayer::get();
        if (!playLayer) return;

        auto playerPos = this->getPosition();
        bool hasObstacle = false;

        CCRect scanBox = CCRect(
            playerPos.x + 5.0f,
            playerPos.y - 10.0f,
            g_scanDistance,
            40.0f
        );

        auto objects = playLayer->m_objects;
        if (objects) {
            for (int i = 0; i < objects->count(); ++i) {
                auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
                if (!obj || obj->m_isDestroyed) continue;

                if (scanBox.intersectsRect(obj->getObjectRect())) {
                    if (obj->m_objectType == GameObjectType::Spike || 
                        obj->m_objectType == GameObjectType::Hazard) {
                        hasObstacle = true;
                        break;
                    }
                }
            }
        }

        if (hasObstacle) {
            this->pushButton(PlayerButton::Jump);
        }
    }
};

// 2. Tao Nut Tron Noi va Menu trong PlayLayer
class $modify(AIPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        auto circleSprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        
        auto circleBtn = CCMenuItemSpriteExtra::create(
            circleSprite,
            this,
            menu_selector(AIPlayLayer::onToggleAIMenu)
        );

        auto menu = CCMenu::create();
        menu->addChild(circleBtn);
        menu->setPosition({ winSize.width - 30.0f, winSize.height - 30.0f });
        menu->setZOrder(100);

        this->addChild(menu);
        return true;
    }

    void onToggleAIMenu(CCObject* sender) {
        g_aiEnabled = !g_aiEnabled;
        std::string statusMessage = g_aiEnabled 
            ? "AI Auto Play: ON" 
            : "AI Auto Play: OFF";

        FLAlertLayer::create("AI Menu Control", statusMessage.c_str(), "OK")->show();
    }
};
