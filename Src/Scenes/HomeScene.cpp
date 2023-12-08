#include "HomeScene.hpp"
#include <Components/AIComponent.hpp>
#include <Objects/Button.hpp>
#include <Components/SpriteComponent.hpp>
#include <Components/SoundTrackComponent.hpp>
#include "BrackEngine.hpp"
#include "../../Brack-Engine/src/ConfigSingleton.hpp"
#include "../Helpers/RogueLikeSheetMap.hpp"
#include "../Player.hpp"
#include "DemoLevel.hpp"

HomeScene::HomeScene() : Scene() {
    auto& camera = getCameras()[0];
    camera->addComponent(VelocityComponent());
    camera->SetBackgroundColor(Color(0, 255, 0, 255));
    auto backgroundSound = std::make_unique<SoundTrackComponent>("Sounds/atje.mp3");
    backgroundSound->volume = 0.1;
    backgroundSound->startPlaying = true;
    camera->addComponent(std::move(backgroundSound));

    auto imageBg = std::make_unique<GameObject>();
    auto spriteBg = std::make_unique<SpriteComponent>();
    spriteBg->spritePath = "Sprites/logo.png";
    spriteBg->spriteSize = std::make_unique<Vector2>(736, 105);
    spriteBg->imageSize = std::make_unique<Vector2>(100,100);
    spriteBg->tileOffset = std::make_unique<Vector2>(0, 0);

    auto transformBg = std::make_unique<TransformComponent>();
    auto windowSize = ConfigSingleton::GetInstance().GetWindowSize();
    transformBg->position = std::make_unique<Vector2>(0, -100);
    transformBg->scale = std::make_unique<Vector2>(0.6, 0.6);
    imageBg->addComponent(std::move(spriteBg));
    imageBg->addComponent(std::move(transformBg));
    addGameObject(std::move(imageBg));

    //Start button
    auto startButton = std::make_unique<Button>(Vector2(210, 70), "Start game");
    startButton->setFontSize(40);
    startButton->setClickEvent([](){
        auto scene = DemoLevel();
        SceneManager::getInstance().setActiveScene(scene);
    });

    auto centerY = ConfigSingleton::GetInstance().GetWindowSize().getY() / 2;
    auto centerX = ConfigSingleton::GetInstance().GetWindowSize().getX() / 2;

    auto& transformStartButton = startButton->tryGetComponent<TransformComponent>();
    transformStartButton.position = std::make_unique<Vector2>(-150+ centerX - 105, centerY + 50);
    addGameObject(std::move(startButton));

    //Quit button
    auto quitButton = std::make_unique<Button>(Vector2(210, 70), "Quit");
    quitButton->setFontSize(40);
    quitButton->setClickEvent([](){
        ConfigSingleton::GetInstance().ToggleIsRunning();
    });

    auto& transformQuitButton = quitButton->tryGetComponent<TransformComponent>();
    transformQuitButton.position = std::make_unique<Vector2>(150 + centerX - 105, centerY + 50);
    addGameObject(std::move(quitButton));
}