#include "PlayerProgress.hpp"
#include <EngineManagers/SceneManager.hpp>
#include <Components/RectangleComponent.hpp>
#include "../Src/Helpers/RogueLikeSheetMap.hpp"
#include "UserInputMovement.hpp"
#include "../Src/Scenes/EndScreen.hpp"

void PlayerProgress::onStart() {

}

void PlayerProgress::onUpdate(milliseconds deltaTime) {
    int totalProgress = beersCollected - foodCollected;

    auto& progressBar = getGameObjectByTag("ProgressBar").value().tryGetComponent<RectangleComponent>();
    int progressWidth = 300 / 100 * (totalProgress * 10);
    progressBar.size->setX(progressWidth);

    if(totalProgress >= maxForLevel) {
        maxForLevel += 10;
        auto scene = new EndScreen();
        SceneManager::getInstance().goToNewScene(scene);
    }
}