## Shaders
source: [Learn OpenGL](https://learnopengl.com/Getting-started/Shaders)

### What are shaders
Shaders are little programs that rest on the **GPU**. These programs are run for each specific section of the graphics pipeline. 

In a basic sense, shaders are nothing more than programs transforming **inputs to outputs**. 

Shaders are also very **isolated programs** in that they're not allowed to communicate with each other; the only communication they have is via their inputs and outputs. 

### GLSL
Shaders are written in the C-like language **GLSL**.

Shaders always begin with a **version declaration**, followed by a **list of input and output variables**, **uniforms** and its **main function**.

Typicall structure:
```C
 #version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;
  
uniform type uniform_name;
  
void main()
{
  // process input(s) and do some weird graphics stuff
  ...
  // output processed stuff to output variable
  out_variable_name = weird_stuff_we_processed;
} 
```

### Vartex shader
When we're talking specifically about the vertex shader **each input variable** is also known as a **vertex attribute**. 

There is a maximum number of vertex attributes we're allowed to declare limited by the hardware. OpenGL guarantees there are always at least **16 4-component vertex attributes** available, but some hardware may allow for more which you can retrieve by querying `GL_MAX_VERTEX_ATTRIBS`:

```C
int nrAttributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
```

This often returns the minimum of 16 which should be more than enough for most purposes. 

### Types in GLSL
- basic types (`int`, `float`, `double`, `uint`, `bool`)
- `vectors` and `matrices`

#### Vectors
 A vector in GLSL is a 2,3 or 4 component container for any of the basic types just mentioned. They can take the following form (n represents the number of components):

- `vecn`: the default vector of n floats.
- `bvecn`: a vector of n booleans.
- `ivecn`: a vector of n integers.
- `uvecn`: a vector of n unsigned integers.
- `dvecn`: a vector of n double components.

Components of a vector can be accessed via vec.x You can use .x, .y, .z and .w to access their first, second, third and fourth component respectively. 

GLSL also allows you to use **rgba** for colors or **stpq** for texture coordinates, accessing the same components.

The vector datatype allows for some interesting and flexible component selection called **swizzling**. Swizzling allows us to use syntax like this:

```C
vec2 someVec;
vec4 differentVec = someVec.xyxx;
vec3 anotherVec = differentVec.zyw;
vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
```
We can also pass vectors as arguments to different vector constructor calls, reducing the number of arguments required:
```C
vec2 vect = vec2(0.5, 0.7);
vec4 result = vec4(vect, 0.0, 0.0);
vec4 otherResult = vec4(result.xyz, 1.0);
```

### Vertex shader
The vertex shader should receive some form of input otherwise it would be pretty ineffective. 

The vertex shader differs in its input, in that **it receives its input straight from the vertex data**. 

To define how the vertex data is organized we specify the input variables with **location metadata** so we can configure the vertex attributes on the CPU. We've seen this in the previous chapter as layout `(location = 0)`. The vertex shader thus requires an extra layout specification for its inputs so we can link it with the vertex data.

```C
#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
  
out vec4 vertexColor; // specify a color output to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}
```

### Fragment shader
The fragment shader requires a **vec4 color output variable**, since the fragment shaders needs to generate a final output color. If you fail to specify an output color in your fragment shader, the color buffer output for those fragments will be undefined (which usually means OpenGL will render them either black or white). 

```C
#version 330 core
out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

void main()
{
    FragColor = vertexColor;
} 
```

Since they both have the same type and name, the vertexColor in the fragment shader is linked to the vertexColor in the vertex shader. Because we set the color to a dark-red color in the vertex shader, the resulting fragments should be dark-red as well.

### Uniforms
Uniforms are another way to pass data from our application on the CPU to the shaders on the GPU. 

Uniforms are however slightly different compared to vertex attributes. First of all, uniforms are **global**. Global, meaning that a uniform variable is unique per shader program object, and can be accessed from any shader at any stage in the shader program. Second, whatever you set the uniform value to, uniforms will keep their values until they're either reset or updated. 
```C
#version 330 core
out vec4 FragColor;
  
uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main()
{
    FragColor = ourColor;
}   
```