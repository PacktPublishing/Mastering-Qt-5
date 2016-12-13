import Qt3D.Core 2.0
import "factory.js" as Factory

GameEntity {

    id: root
    type: Factory.WALL_TYPE

    property alias position: transform.translation

    Transform {
        id: transform
    }

    components: [transform]
}
