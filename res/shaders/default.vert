
//"in" attributes from our SpriteBatch 
in vec2 TexCoord;
in vec4 Color;

//"out" varyings to our fragment shader
varying vec4 vColor;
varying vec2 vTexCoord;
varying vec4 vPosition;

void main() {
    vColor = Color;
    vTexCoord = TexCoord;
    //gl_Vertex.y = gl_Vertex.x/16 + gl_Vertex.y;
    vPosition = gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex * vec4(1.0, 1.0, 1.0, 1.0);
   // gl_Position.y = sin(gl_Vertex.x) * sin(gl_Vertex.x)*.1  + gl_Position.y;
}