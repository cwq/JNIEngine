precision mediump float;
uniform sampler2D u_TextureUnit;
uniform vec4 u_color;
uniform float u_alpha;
uniform vec4 u_inVec4;
uniform vec4 u_showVec4;
varying vec2 v_TextureCoordinates;
varying vec4 v_originalPosition;
varying vec4 v_changedPosition;
void main() {
    if((v_changedPosition.x >= u_showVec4.x - u_showVec4.z)
            && (v_changedPosition.x <= u_showVec4.x + u_showVec4.z)
            && (v_changedPosition.y >= u_showVec4.y - u_showVec4.w)
            && (v_changedPosition.y <= u_showVec4.y + u_showVec4.w)) {
        gl_FragColor = texture2D(u_TextureUnit, v_TextureCoordinates);
        if(gl_FragColor.a == 0.0)
            discard;
        gl_FragColor = gl_FragColor + u_color;
        if(u_color.w != 0.0)
            gl_FragColor.a = u_color.w;
        if((v_originalPosition.x >= u_inVec4.x - u_inVec4.z)
                && (v_originalPosition.x <= u_inVec4.x + u_inVec4.z)
                && (v_originalPosition.y >= u_inVec4.y - u_inVec4.w)
                && (v_originalPosition.y <= u_inVec4.y + u_inVec4.w))
            gl_FragColor.a = u_alpha;  
    }
}