import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.0
import "factory.js" as Factory

GameEntity {

    id: root
    type: Factory.SNAKE_TYPE

    property alias position: transform.translation

    PhongMaterial {
        id: material
        diffuse: "green"
    }

    CuboidMesh {
        id: mesh
    }

    Transform {
        id: transform
    }

    components: [material, mesh, transform]
}
