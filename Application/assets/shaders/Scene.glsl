#type vertex
#version 410 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec3 a_Normal;
// layout(location = 3) in float a_TextureIndex;
layout(location = 5) in int a_EntityID;

uniform mat4 u_View;
uniform mat4 u_Projection;

uniform vec3 u_LightPosition;
uniform vec3 u_LightColor;	

// uniform mat4 u_Transform;

out vec2 v_TexCoord;
out vec4 v_Color; 
// out float v_TextureIndex;
flat out int v_EntityID;

void main() {
    v_TexCoord = a_TexCoord;
    
    // vec3 lightDir = normalize(u_LightPosition - a_Position);
    // vec3 normal = normalize(a_Normal);
    // float dotProduct = dot(lightDir, normal);
    // float lightValue = max(dotProduct, 0.15f);
    
    vec3 lightDir = normalize(u_LightPosition - a_Position);
    float lightDot = dot(lightDir, a_Normal);
    float lightValue = max(lightDot, 0.25f); 
    v_Color *= a_Color * lightValue * vec4(u_LightColor, 1.0f);
    v_Color.w = 1.0f;
    
    // v_TextureIndex = a_TextureIndex;
    v_EntityID = a_EntityID; 
    gl_Position = u_Projection * u_View * vec4(a_Position, 1.0f);
    // gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 410 core

layout(location = 0) out vec4 color;
layout(location = 1) out int entityID;

in vec4 v_Color;
in vec2 v_TexCoord;
// in float v_TextureIndex;
flat in int v_EntityID; 

uniform sampler2D u_Texture;

// uniform sampler2D u_Textures[32];

void main() {
    color = texture(u_Texture, v_TexCoord);
    entityID = v_EntityID;
}
