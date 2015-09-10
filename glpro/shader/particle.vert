attribute vec4 a_position;
attribute vec4 a_color;

uniform mat4 u_matrixModelViewProj;

varying vec4 v_fragmentColor;

void main()
{
    v_fragmentColor = a_color;
    gl_Position = u_matrixModelViewProj * a_position;
}