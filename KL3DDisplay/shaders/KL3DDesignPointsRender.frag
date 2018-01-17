uniform float colorFlag;
uniform sampler2D pointTexture;

varying vec3 color;
varying float flag;

bool isDefaultColor(vec3 c)
{
		if((c.r > 0.999999 && c.r < 1.000001) && c.g == 0.0 && c.b == 0.0)
		{
				return true;
		}
		else if((c.b > 0.999999 && c.b < 1.000001) && c.r == 0.0 && c.g == 0.0)
		{
				return true;
		}
		else
		{
				return false;
		}

}


void main()
{
		bool isDefault = isDefaultColor(color);
		if(flag > 0.999999 && flag < 1.000001 && isDefault)
		{
				gl_FragColor = texture2D(pointTexture, gl_PointCoord);
		}
		else
		{
				gl_FragColor = vec4(color, 1.0);
		}

}