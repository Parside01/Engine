#type Vertex
#version 330 core

layout(location = 0) a_Position;
layout(location = 1) a_TexCoord;

uniform mat4 u_ViewProjection; 
uniform mat4 u_Transform; 

out vec2 v_TexCoord;

void main() {
    v_TexCoord = a_TexCoord;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type Fragment
#version 330 core

layout(location = 0) out vec4 color;
int vec2 v_TexCoord;

uniform sampler2D u_Texture; 

void main() {
    color = texture(u_Texture, v_TexCoord);
}