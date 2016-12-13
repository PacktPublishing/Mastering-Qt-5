#version 150

in vec3 normal;
in vec3 position;
in vec2 texCoord;
in vec2 fragCoord;

uniform int score;
uniform sampler2D diffuseTexture;
uniform vec2 resolution;
uniform float time;

out vec4 fragColor;

void main()
{
    vec4 texture = texture2D(diffuseTexture, texCoord);

    vec2 uv = gl_FragCoord.xy / resolution.xy;
    float speed = 0.03 * time;
    uv.x -= 0.5;
    uv.y += uv.x * cos(10.0 * uv.x * uv.x - 3.0 * speed) - 0.5;

    float width = 0.8 * uv.x;
    float intensity = (0.02 + (0.01 * score)) * abs(width / uv.y);
    float waveIntensity = 0.85;

    fragColor = vec4(mix(texture.r, intensity, waveIntensity),
                     mix(texture.g, intensity, waveIntensity),
                     mix(texture.b, intensity * 3.0, waveIntensity),
                     1.0);
}
