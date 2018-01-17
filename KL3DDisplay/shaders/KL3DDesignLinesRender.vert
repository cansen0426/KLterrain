uniform sampler2D terrainTexture;

uniform vec3 minCoord;
uniform vec3 maxCoord;
uniform bool isTerrainExist;
uniform float terrainScale;

varying vec3 color;

in vec3 vertexArr;
in vec3 colorArr;

void main()
{
	vec2 texcoord = (vertexArr.xy - minCoord.xy) / (maxCoord.xy - minCoord.xy);

	vec4 position;
	position.x = vertexArr.x;
	position.y = vertexArr.y;
	if(isTerrainExist)
	{
			if(texcoord.x >= -0.001 && texcoord.x < 1.0002 && texcoord.y >= -0.001 && texcoord.y < 1.0002)
				{
						//处理炮检线在地形边界处，高程拾取存在无效值的问题；
						if(texcoord.x <= 0.001)
							texcoord.x = texcoord.x + 0.001;
						if(texcoord.x >= 0.999)
					    texcoord.x = texcoord.x - 0.001; 
						if(texcoord.y <= 0.001)
							texcoord.y = texcoord.y + 0.001;
						if(texcoord.y >= 0.999)
					    texcoord.y = texcoord.y - 0.001; 
					      		
					  position.z = texture2D(terrainTexture, texcoord).r/terrainScale + 15.0f;
				}
				else
						position.z = 0.0;
							      		
	}
	else
	{
			position.z = vertexArr.z;
	}
	position.w = 1.0;

	gl_Position = gl_ModelViewProjectionMatrix * position;

	color = colorArr;
}