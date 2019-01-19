//SpriteBatch will use texture unit 0
uniform sampler2D u_texture;


//"in" varyings from our vertex shader
varying vec4 vColor;
varying vec2 vTexCoord;
varying vec4 vPosition;

void main() {
    //sample the texture
    vec4 texColor = texture2D(u_texture, vTexCoord, 0);

    //invert the red, green and blue channels
   // texColor.rgb = 1.0 - texColor.rgb;
    //texColor.w =  cos(vTexCoord.xy);
    //final color
    gl_FragColor = texColor; 
    
   // if(abs(mod(vPosition.x,16.f)) < 0.9) gl_FragColor = vec4(0.0,0.0,0.0,1.0);
}