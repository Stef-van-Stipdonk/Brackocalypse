#include <Components/AIComponent.hpp>
#include <Components/AnimationComponent.hpp>
#include <Components/BoxCollisionComponent.hpp>
#include "Objects/Scene.hpp"
#include "BrackEngine.hpp"
#include "../Brack-Engine/src/ConfigSingleton.hpp"
#include "Src/RogueLikeSheetMap.hpp"
#include "Scripts/CameraFocussedUserInput.hpp"
#include "Src/Player.hpp"
#include "Src/Level.hpp"

int main() {
    Config config = new Config();
    config.windowTitle = "Brackocalypse";
    config.windowSize = Vector2(640, 640);

    BrackEngine brackEngine = BrackEngine(std::move(config));
    auto camera = Camera();
    camera.AddComponent(VelocityComponent());
    camera.SetBackgroundColor(Color(0, 255, 0, 255));
    auto scene = Scene(std::move(camera));

    int spriteMargin = 1;
    Vector2 spriteScale = Vector2(4,4);
    Vector2 spriteSize = Vector2(16,16);
    std::string spritePath = "Sprites/roguelikeSheet_transparent_1.bmp";
    RogueLikeSheetMap rogueLikeSheetMap = RogueLikeSheetMap();

    std::vector<std::vector<std::string>> map{};
    map.push_back({});
    map[0].push_back("WWWWWWWWWWWWWWWWWWWW");
    map[0].push_back("WWWWWWWWWWWWWWWWWWWW");
    map[0].push_back("WWWWWWWWWWWWWWWWWWWW");
    map[0].push_back("WWWWLQQQQQQQQQQNWWWW");
    map[0].push_back("WWWWUGGGGGGGGGGPWWWW");
    map[0].push_back("WWWWUGGGGGGGGGGPWWWW");
    map[0].push_back("WWWWUGGGGGGGGGGPWWWW");
    map[0].push_back("WWWWUGGGGGGGGGGPWWWW");
    map[0].push_back("WWWWUGGGGGGGGGGPWWWW");
    map[0].push_back("WWWWUGGGGGGGGGGPWWWW");
    map[0].push_back("WWWWUGGGGGGGGGGPWWWW");
    map[0].push_back("WWWWUGGGGGGGGGGPWWWW");
    map[0].push_back("WWWWUGGGGGGGGGGPWWWW");
    map[0].push_back("WWWWVYYYYYYYYYYCWWWW");
    map[0].push_back("WWWWWWWWWWWWWWWWWWWW");
    map[0].push_back("WWWWWWWWWWWWWWWWWWWW");
    map[0].push_back("WWWWWWWWWWWWWWWWWWWW");

    int y = 0;
    for (std::string row : map[0]) {
        int x = 0;
        for (char c : row) {
            auto object = std::make_unique<GameObject>();
            auto sprite = std::make_unique<SpriteComponent>();
            auto& transform = object->TryGetComponent<TransformComponent>();
            sprite->spritePath = spritePath;
            sprite->spriteSize = std::make_unique<Vector2>(spriteSize);
            sprite->margin = spriteMargin;
            sprite->sortingLayer = 2;
            float posX = ((x * (spriteSize.getX() * spriteScale.getX())) + ((spriteSize.getX() * spriteScale.getX()) / 2)) - (20*64 / 2);
            float posY = ((y * (spriteSize.getY() * spriteScale.getY())) + ((spriteSize.getY() * spriteScale.getY()) / 2)) - (17*64 / 2);
            transform.position = std::make_unique<Vector2>(posX,posY);
            transform.scale =std::make_unique<Vector2>(spriteScale);
            sprite->tileOffset = std::make_unique<Vector2>(rogueLikeSheetMap.map[static_cast<RogueLikeSheetType>(c)]);
            object->AddComponent(std::move(sprite));
            scene.AddGameObject(std::move(object));
            x++;
        }
        y++;
    }

    auto player = std::make_unique<Player>();
    player->AddComponent(std::make_unique<CameraFocussedUserInput>());
    scene.AddGameObject(std::move(player));

    SceneManager::GetInstance().SetActiveScene(scene);

    brackEngine.Run();
    return 0;
}