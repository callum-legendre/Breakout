#include "scripts/brickscript.h"
#include "components/colliderComponent.h"
#include "components/spriteComponent.h"
#include "gameObject.h"

BrickScript::BrickScript(GameObject* parent, int health) : Script(parent)
{
    mHealth = health;
}

void BrickScript::OnCollision(ColliderComponent*, ColliderComponent*)
{
    if (mHealth > 0){

        mHealth--;

        if (mHealth == 0){
            mParent->Destroy();
        }
        else {
            mParent->GetComponent<SpriteComponent>()->ChangeFrame(mHealth-1);
        }
    }
}
