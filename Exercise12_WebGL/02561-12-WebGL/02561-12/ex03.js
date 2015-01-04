
var gl;
var vertices;

window.onload = function init()
{
    //Get Canvas
    var canvas = document.getElementById("gl-canvas");

    //Get WebGL Context
    gl = WebGLUtils.setupWebGL(canvas);
    if (!gl)
    {
        alert("Failed to get context!");
        return;
    }

    //Setup viewport and clear color
    gl.viewport(0, 0, canvas.width, canvas.height);
    gl.clearColor(0.3921, 0.5843, 0.9294, 1.0);


    //Init vertices
    vertices = [
        vec2(0, 0),
        vec2(1, 0),
        vec2(1, 1)
    ];

    //Init colors
    colorArray = [
       vec3(1, 0, 0),
       vec3(0, 1, 0),
       vec3(0, 0, 1)
    ];

    //Load, compile and link the shaders
    var program = initShaders(gl, "vertex-shader", "fragment-shader");
    gl.useProgram(program);

    //Create and bind vertex buffer
    var buf = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, buf);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW);

    //Associate vertex shader position attribute with vertex buffer
    var attribPos = gl.getAttribLocation(program, "inPosition");
    gl.vertexAttribPointer(attribPos, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(attribPos);


    //create and bind color buffer
    var colorBuf = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, colorBuf);
    gl.bufferData(gl.ARRAY_BUFFER, flatten(colorArray), gl.STATIC_DRAW);


    //Associate vertex shader color attribute with color buffer
    var attributeColor = gl.getAttribLocation(program, "attributeColor");
    gl.vertexAttribPointer(attributeColor, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(attributeColor);


    //Draw stuff
    render();
}

function render()
{
    gl.clear(gl.COLOR_BUFFER_BIT);
    gl.drawArrays(gl.TRIANGLES, 0, vertices.length);
}

