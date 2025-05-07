#include "collidermanager.h"
#include "point.h"

ColliderManager::ColliderManager() {}

void ColliderManager::subscribe(int id, std::shared_ptr<ColliderManaged> collider) {
    collidersById[id] = collider;
}

void ColliderManager::unsubscribe(int id) {
    collidersById.erase(id);
}

void ColliderManager::notify() {
    for(auto& [id1, obj1w] : collidersById) {
        std::shared_ptr<ColliderManaged> obj1 = obj1w.lock();
        for(auto& [id2, obj2w] : collidersById) {
            if(id1 == id2) continue;
            std::shared_ptr<ColliderManaged> obj2 = obj2w.lock();
            Point pos1 = obj1->getPosition();
            Point pos2 = obj2->getPosition();
            Point size1 = obj1->getSize();
            Point size2 = obj2->getSize();

            if(pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x &&
               pos1.y < pos2.y + size2.y && pos1.y + size1.y > pos2.y) {
                obj1->onCollision(obj2);
                obj2->onCollision(obj1);
            }
        }
    }
}