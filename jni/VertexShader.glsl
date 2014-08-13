uniform mat4 u_Matrix;
uniform mat4 u_changeMatrix;
attribute vec4 a_position;
attribute vec2 a_TextureCoordinates;
varying vec2 v_TextureCoordinates;
varying vec4 v_originalPosition;
varying vec4 v_changedPosition;
void main() {
    v_originalPosition = a_position;
    v_TextureCoordinates = a_TextureCoordinates;
    gl_Position = u_Matrix * a_position;
    v_changedPosition = u_changeMatrix * a_position;
    gl_PointSize = 10.0;
}