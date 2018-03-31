import Qt3D.Core 2.0
import Qt3D.Render 2.0

Material {
    id: material

    parameters:  [
        Parameter {
            name: "score"
            value: score
        },

        Parameter {
            name: "resolution"
            value: Qt.vector2d(window.width, window.height)
        },

        Parameter {
            name: "diffuseTexture"
            value: Texture2D {
                id: diffuseTexture
                minificationFilter: Texture.LinearMipMapLinear
                magnificationFilter: Texture.Linear

                wrapMode {
                    x: WrapMode.Repeat
                    y: WrapMode.Repeat
                }
                generateMipMaps: true
                maximumAnisotropy: 16.0
                TextureImage {
                    source: "qrc:/images/grass.jpg"
                }
            }
        }
    ]

    effect: Effect {

        FilterKey {
                   id: forward
                   name: "renderingStyle"
                   value: "forward"
               }

        techniques: [
            Technique {
                filterKeys: [forward]
                graphicsApiFilter {
                    api: GraphicsApiFilter.OpenGL
                    profile: GraphicsApiFilter.CoreProfile
                    majorVersion: 3
                    minorVersion: 2
                }

                renderPasses: RenderPass {
                    shaderProgram: ShaderProgram {
                        vertexShaderCode: loadSource("qrc:/shaders/gl3/grass.vert")
                        fragmentShaderCode: loadSource("qrc:/shaders/gl3/grass.frag")
                    }
                }
            },
            Technique {
                filterKeys: [forward]
                graphicsApiFilter {
                    api: GraphicsApiFilter.OpenGLES
                    profile: GraphicsApiFilter.CoreProfile
                    majorVersion: 2
                    minorVersion: 0
                }

                renderPasses: RenderPass {
                    shaderProgram: ShaderProgram {
                        vertexShaderCode: loadSource("qrc:/shaders/es2/grass.vert")
                        fragmentShaderCode: loadSource("qrc:/shaders/es2/grass.frag")
                    }
                }
            }
        ]
    }
}
