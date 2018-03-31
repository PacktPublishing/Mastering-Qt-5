import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.0
import "factory.js" as Factory

GameEntity {

    id: root
    type: Factory.APPLE_TYPE

    property alias position: transform.translation
    property alias color: material.diffuse

    Transform {
        id: transform
        scale: 0.5
    }

    Mesh {
        id: mesh
        source: "models/apple.obj"
    }

    DiffuseMapMaterial {
        id: material
        diffuse:  TextureLoader { source: "qrc:/models/apple-texture.png" }
    }

    components: [material, mesh, transform]
}
