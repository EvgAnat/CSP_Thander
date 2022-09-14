
int Whr_InitMorning(int n)
{

/// ====================================================================
// Morning2

	Weathers[n].id = "6 Hours";
	Weathers[n].Hour.Min = 6;
	Weathers[n].Hour.Max = 6;
	Weathers[n].Lighting = "morning6";
	Weathers[n].LightingLm = "morning";
	Weathers[n].InsideBack = "m";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\06\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2000.0;
	Weathers[n].Sky.Angle = 0.0;
	Weathers[n].Planets.enable = true;

	Weathers[n].Stars.Enable = true;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 125;
	Weathers[n].Fog.Start = 0;
	Weathers[n].Fog.Density = 0.0005;
	Weathers[n].Fog.IslandDensity = 0.0005;
	Weathers[n].Fog.SeaDensity = 0.0005;
	Weathers[n].Fog.Color = argb(0,75,60,65);
	
	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(48, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,145,98,90);
	Weathers[n].Sun.Ambient = argb(0,55,44,44);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(337.0);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(160.0);
	Weathers[n].Sun.HeightAngle = 0.12;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,150,150,150);
	Weathers[n].Sun.Overflow.Enable = true;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 120, 120, 120);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.2;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,30,42,55);
	Weathers[n].Sea.Pena.Color = argb(0,55,55,55);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,255,55,44);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,100,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	//угол, частота, высота волны в метрах, начальная позиция волны, скорость волны
	Weathers[n].Sea.Harmonics.h1 = "90.0, 2.0, 4.0, 0.0, 20.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 2.0, 2.0, 0.0, 40.0";
	Weathers[n].Sea.Harmonics.h3 = "45.0, 5.0, 1.0, 0.0, 60.0";
	Weathers[n].Sea.Harmonics.h4 = "90.0, 10.0, 0.2, 0.0, 80.0";
	Weathers[n].Sea.Harmonics.h5 = "0.0, 15.0, 0.3, 0.0, 90.0";
	Weathers[n].Sea.Harmonics.h6 = "45.0, 20.0, 0.4, 0.0, 100.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05; //МЕЛКИЕ ВОЛНЫ
	Weathers[n].Sea2.PosShift = 2.0; //остроконечность волн
	
	Weathers[n].Sea2.WaterColor = argb(0,30,42,55);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.7;
	Weathers[n].Sea2.Transparency = 0.2;
	Weathers[n].Sea2.Frenel = 0.7; 
	Weathers[n].Sea2.Attenuation = 0.8;

	Weathers[n].Sea2.Amp1 = 5.0; //амплитуда 1 волны
	Weathers[n].Sea2.AnimSpeed1 = 2.0; //скорость анимации
	Weathers[n].Sea2.Scale1 = 0.5; //размеры волны
	Weathers[n].Sea2.MoveSpeed1 = "2.0, 0.0, 0.0"; //скорость движения

	Weathers[n].Sea2.Amp2 = 1.0;
	Weathers[n].Sea2.AnimSpeed2 = 2.0;
	Weathers[n].Sea2.Scale2 = 1.5;
	Weathers[n].Sea2.MoveSpeed2 = "0.0, 0.0, -1.5";

	Weathers[n].Sea2.FoamK = 0.05;//яркость пены по высоте 0.1 - пена яркая с 10 метров 1.0 через метр после начала
	Weathers[n].Sea2.FoamV = 2.5;//высота с которой начинается пена
	Weathers[n].Sea2.FoamUV = 0.5; //тайлинг пены
	Weathers[n].Sea2.FoamTexDisturb = 1.0;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0
	

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 2.0;
	Weathers[n].Wind.Speed.Max = 9.0;
	
	n++;
	
// ====================================================================
// Morning3 7 часов 

	Weathers[n].id = "7 Hour";
	Weathers[n].Hour.Min = 7;
	Weathers[n].Hour.Max = 7;
	Weathers[n].Lighting = "morning8";
	Weathers[n].LightingLm = "morning";
	Weathers[n].InsideBack = "m";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\07\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2000.0;
	Weathers[n].Sky.Angle = 0.0;
	Weathers[n].Planets.enable = true;

	Weathers[n].Stars.Enable = true;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 140;
	Weathers[n].Fog.Start = 0;
	Weathers[n].Fog.Density = 0.0005;
	Weathers[n].Fog.IslandDensity = 0.0005;
	Weathers[n].Fog.SeaDensity = 0.0005;
	Weathers[n].Fog.Color = argb(0,60,70,90);
	
	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(48, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,145,98,90);
	Weathers[n].Sun.Ambient = argb(0,55,44,44);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(337.0);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(160.0);
	Weathers[n].Sun.HeightAngle = 0.12;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,150,150,150);
	Weathers[n].Sun.Overflow.Enable = true;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 120, 120, 120);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.2;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,30,42,55);
	Weathers[n].Sea.Pena.Color = argb(0,55,55,55);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,255,55,44);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,100,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	//угол, частота, высота волны в метрах, начальная позиция волны, скорость волны
	Weathers[n].Sea.Harmonics.h1 = "90.0, 2.0, 4.0, 0.0, 20.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 2.0, 2.0, 0.0, 40.0";
	Weathers[n].Sea.Harmonics.h3 = "45.0, 5.0, 1.0, 0.0, 60.0";
	Weathers[n].Sea.Harmonics.h4 = "90.0, 10.0, 0.2, 0.0, 80.0";
	Weathers[n].Sea.Harmonics.h5 = "0.0, 15.0, 0.3, 0.0, 90.0";
	Weathers[n].Sea.Harmonics.h6 = "45.0, 20.0, 0.4, 0.0, 100.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05; //МЕЛКИЕ ВОЛНЫ
	Weathers[n].Sea2.PosShift = 2.0; //остроконечность волн
	
	Weathers[n].Sea2.WaterColor = argb(0,30,42,55);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.7;
	Weathers[n].Sea2.Transparency = 0.2;
	Weathers[n].Sea2.Frenel = 0.7; 
	Weathers[n].Sea2.Attenuation = 0.8;

	Weathers[n].Sea2.Amp1 = 6.0; //амплитуда 1 волны
	Weathers[n].Sea2.AnimSpeed1 = 10.0; //скорость анимации
	Weathers[n].Sea2.Scale1 = 0.8; //размеры волны
	Weathers[n].Sea2.MoveSpeed1 = "4.0, 0.0, 0.0"; //скорость движения

	Weathers[n].Sea2.Amp2 = 1.0;
	Weathers[n].Sea2.AnimSpeed2 = 12.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "-1.0, 0.0, 2.0";
	
	Weathers[n].Sea2.FoamK = 0.03;//яркость пены по высоте 0.1 - пена яркая с 10 метров 1.0 через метр после начала
	Weathers[n].Sea2.FoamV = 3.0;//высота с которой начинается пена
	Weathers[n].Sea2.FoamUV = 0.5; //тайлинг пены
	Weathers[n].Sea2.FoamTexDisturb = 1.0;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 6.0;
	Weathers[n].Wind.Speed.Max = 11.5;
	
	n++;

// ====================================================================
// Morning4 8 часов

	Weathers[n].id = "8 Hour";
	Weathers[n].Hour.Min = 8;
	Weathers[n].Hour.Max = 8;
	Weathers[n].Lighting = "morning8";
	Weathers[n].LightingLm = "morning";
	Weathers[n].InsideBack = "m";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\08\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2000.0;
	Weathers[n].Sky.Angle = 0.0;
	Weathers[n].Planets.enable = true;

	Weathers[n].Stars.Enable = true;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 160;
	Weathers[n].Fog.Start = 0;
	Weathers[n].Fog.Density = 0.0005;
	Weathers[n].Fog.IslandDensity = 0.0005;
	Weathers[n].Fog.SeaDensity = 0.0005;
	Weathers[n].Fog.Color = argb(0,85,85,105);
	
	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(48, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,145,98,90);
	Weathers[n].Sun.Ambient = argb(0,55,44,44);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(337.0);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(160.0);
	Weathers[n].Sun.HeightAngle = 0.12;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,150,150,150);
	Weathers[n].Sun.Overflow.Enable = true;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 120, 120, 120);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.2;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,30,42,55);
	Weathers[n].Sea.Pena.Color = argb(0,55,55,55);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,255,55,44);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,100,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	//угол, частота, высота волны в метрах, начальная позиция волны, скорость волны
	Weathers[n].Sea.Harmonics.h1 = "90.0, 2.0, 4.0, 0.0, 20.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 2.0, 2.0, 0.0, 40.0";
	Weathers[n].Sea.Harmonics.h3 = "45.0, 5.0, 1.0, 0.0, 60.0";
	Weathers[n].Sea.Harmonics.h4 = "90.0, 10.0, 0.2, 0.0, 80.0";
	Weathers[n].Sea.Harmonics.h5 = "0.0, 15.0, 0.3, 0.0, 90.0";
	Weathers[n].Sea.Harmonics.h6 = "45.0, 20.0, 0.4, 0.0, 100.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05; //МЕЛКИЕ ВОЛНЫ
	Weathers[n].Sea2.PosShift = 2.0; //остроконечность волн
	
	Weathers[n].Sea2.WaterColor = argb(0,30,42,55);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.7;
	Weathers[n].Sea2.Transparency = 0.2;
	Weathers[n].Sea2.Frenel = 0.7; 
	Weathers[n].Sea2.Attenuation = 0.8;

	Weathers[n].Sea2.Amp1 = 17.0; //амплитуда 1 волны
	Weathers[n].Sea2.AnimSpeed1 = 0.5; //скорость анимации
	Weathers[n].Sea2.Scale1 = 0.17 //размеры волны9
	Weathers[n].Sea2.MoveSpeed1 = "0.0, 0.0, 8.0"; //скорость движения

	Weathers[n].Sea2.Amp2 = 1.0;
	Weathers[n].Sea2.AnimSpeed2 = 0.2;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "4.0, 0.0, 4.0";	

	Weathers[n].Sea2.FoamK = 0.025;//яркость пены по высоте 0.1 - пена яркая с 10 метров 1.0 через метр после начала
	Weathers[n].Sea2.FoamV = 6.0;//высота с которой начинается пена
	Weathers[n].Sea2.FoamUV = 0.3; //тайлинг пены
	Weathers[n].Sea2.FoamTexDisturb = 0.5;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 5.5;
	Weathers[n].Wind.Speed.Max = 13.0;
	
	n++;


// ====================================================================
// Morning1 9 часов

	Weathers[n].id = "9 Hours";
	Weathers[n].Hour.Min = 9;
	Weathers[n].Hour.Max = 9;
	Weathers[n].Lighting = "morning8";
	Weathers[n].LightingLm = "morning";
	Weathers[n].InsideBack = "m";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\09\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2000.0;
	Weathers[n].Sky.Angle = 0.0;
	Weathers[n].Planets.enable = true;

	Weathers[n].Stars.Enable = false;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 200;
	Weathers[n].Fog.Start = 0;
	Weathers[n].Fog.Density = 0.0005;
	Weathers[n].Fog.IslandDensity = 0.0005;
	Weathers[n].Fog.SeaDensity = 0.0005;
	Weathers[n].Fog.Color = argb(0,90,90,100);
	
	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(48, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,173,129,116);
	Weathers[n].Sun.Ambient = argb(0,70,59,56);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(337.0);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(160.0);
	Weathers[n].Sun.HeightAngle = 0.12;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,150,150,150);
	Weathers[n].Sun.Overflow.Enable = true;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 120, 120, 120);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.2;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,30,46,70);
	Weathers[n].Sea.Pena.Color = argb(0,55,55,55);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,255,55,44);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,100,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	//угол, частота, высота волны в метрах, начальная позиция волны, скорость волны
	Weathers[n].Sea.Harmonics.h1 = "90.0, 2.0, 4.0, 0.0, 20.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 2.0, 2.0, 0.0, 40.0";
	Weathers[n].Sea.Harmonics.h3 = "45.0, 5.0, 1.0, 0.0, 60.0";
	Weathers[n].Sea.Harmonics.h4 = "90.0, 10.0, 0.2, 0.0, 80.0";
	Weathers[n].Sea.Harmonics.h5 = "0.0, 15.0, 0.3, 0.0, 90.0";
	Weathers[n].Sea.Harmonics.h6 = "45.0, 20.0, 0.4, 0.0, 100.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05; //МЕЛКИЕ ВОЛНЫ
	Weathers[n].Sea2.PosShift = 2.0; //остроконечность волн
	
	Weathers[n].Sea2.WaterColor = argb(0,30,46,70);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.7;
	Weathers[n].Sea2.Transparency = 0.2;
	Weathers[n].Sea2.Frenel = 0.7; 
	Weathers[n].Sea2.Attenuation = 0.8;

	Weathers[n].Sea2.Amp1 = 25.0; //амплитуда 1 волны
	Weathers[n].Sea2.AnimSpeed1 = 2.0; //скорость анимации
	Weathers[n].Sea2.Scale1 = 0.17; //размеры волны
	Weathers[n].Sea2.MoveSpeed1 = "7.0, 0.0, 0.0"; //скорость движения

	Weathers[n].Sea2.Amp2 = 1.5;
	Weathers[n].Sea2.AnimSpeed2 = 10.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "0.0, 0.0, -1.0";	

	Weathers[n].Sea2.FoamK = 0.015;//яркость пены по высоте 0.1 - пена яркая с 10 метров 1.0 через метр после начала
	Weathers[n].Sea2.FoamV = 5.5;//высота с которой начинается пена
	Weathers[n].Sea2.FoamUV = 0.1; //тайлинг пены
	Weathers[n].Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 6.0;
	Weathers[n].Wind.Speed.Max = 14.0;
	
	n++;

// ====================================================================
// Morning1 10 часов

	Weathers[n].id = "10 Hours";
	Weathers[n].Hour.Min = 10;
	Weathers[n].Hour.Max = 10;
	Weathers[n].Lighting = "morning8";
	Weathers[n].LightingLm = "morning";
	Weathers[n].InsideBack = "m";

	Weathers[n].Storm = false;
	Weathers[n].Tornado = false;
	Weathers[n].Shark = true;
	Weathers[n].Lights = 0;
	Weathers[n].Night = false;

	Weathers[n].Shadow.Density.Head = argb(255,96,96,96);
	Weathers[n].Shadow.Density.Foot = argb(255,96,96,64);

	Weathers[n].Lightning.Enable = false;
	Weathers[n].Lightning.Texture = "Weather\lightning\lightning.tga.tx";
	Weathers[n].Lightning.FlickerTime = 32;
	Weathers[n].Lightning.SubTexX = 1;
	Weathers[n].Lightning.SubTexY = 1;

	Weathers[n].Sky.Dir = "weather\skies\10\";
	Weathers[n].Sky.Color = argb(0,255,255,255);
	Weathers[n].Sky.Rotate.Min = 0.0;
	Weathers[n].Sky.Rotate.Max = 0.0;
	Weathers[n].Sky.Size = 2000.0;
	Weathers[n].Sky.Angle = 0.0;
	Weathers[n].Planets.enable = true;

	Weathers[n].Stars.Enable = true;
	Weathers[n].Stars.Texture = "weather\astronomy\stars.tga.tx";
	Weathers[n].Stars.Color = argb(0, 255, 255, 255);
	Weathers[n].Stars.Radius = 2000.0;
	Weathers[n].Stars.Size = 15.0;
	Weathers[n].Stars.HeightFade = 200.0;
	Weathers[n].Stars.SunFade = 1.0;
	Weathers[n].Stars.VisualMagnitude = 8.0;

	Weathers[n].Fog.Enable = true;
	Weathers[n].Fog.Height = 200;
	Weathers[n].Fog.Start = 0;
	Weathers[n].Fog.Density = 0.0005;
	Weathers[n].Fog.IslandDensity = 0.0005;
	Weathers[n].Fog.SeaDensity = 0.0005;
	Weathers[n].Fog.Color = argb(0,95,105,105);
	
	Weathers[n].Rain.NumDrops = 0;
	Weathers[n].Rain.Color = argb(0,73,73,73);
	Weathers[n].Rain.DropLength = 2.12;
	Weathers[n].Rain.Height = 30.0;
	Weathers[n].Rain.Radius = 30.0;
	Weathers[n].Rain.Speed = 18.0;
	Weathers[n].Rain.Jitter = 0.4;
	Weathers[n].Rain.WindSpeedJitter = 0.5;
	Weathers[n].Rain.MaxBlend = 49;
	Weathers[n].Rain.TimeBlend = 2000;

	Weathers[n].Rain.DropsNearNum = 500;
	Weathers[n].Rain.DropsFarNum = 500;
	Weathers[n].Rain.DropsNearRadius = 25.0;
	Weathers[n].Rain.DropsFarRadius = 75.0;
	Weathers[n].Rain.DropsLifeTime = 0.25;
	Weathers[n].Rain.DropsSize = 0.06;
	Weathers[n].Rain.DropsTexture = "weather\rain_drops.tga.tx";
	Weathers[n].Rain.DropsColor = argb(48, 255, 255, 255);

	Weathers[n].Rainbow.Enable = false;
	Weathers[n].Rainbow.Texture = "weather\rainbow\rainbow.tga.tx";

	Weathers[n].Sun.Color = argb(0,131,100,82);
	Weathers[n].Sun.Ambient = argb(0,85,74,68);
	//Weathers[n].Sun.AzimuthAngle = Degree2Radian(337.0);
	Weathers[n].Sun.AzimuthAngle = Degree2Radian(160.0);
	Weathers[n].Sun.HeightAngle = 0.12;
	Weathers[n].Sun.Glow.Enable = true;
	Weathers[n].Sun.Glow.Dist = 3500.0;
	Weathers[n].Sun.Glow.Size = 1250.0;
	Weathers[n].Sun.Glow.RotateSpeed = 1.0;
	Weathers[n].Sun.Glow.Texture = "weather\sun\glow\sunglow.tga.tx";
	Weathers[n].Sun.Glow.DecayTime = 8.0;
	Weathers[n].Sun.Glow.TechniqueNoZ = "sunglow_noz";
	Weathers[n].Sun.Glow.TechniqueZ = "sunglow_z";
	Weathers[n].Sun.Glow.Color = argb(0,150,150,150);
	Weathers[n].Sun.Overflow.Enable = true;
	Weathers[n].Sun.Overflow.Texture = "Weather\lightning\flash.tga.tx";
	Weathers[n].Sun.Overflow.Color = argb(0, 120, 120, 120);
	Weathers[n].Sun.Overflow.Size = 5500.0;
	Weathers[n].Sun.Overflow.Technique = "sunoverflow";
	Weathers[n].Sun.Overflow.Start = 0.7;
	Weathers[n].Sun.Flare.Enable = true;
	Weathers[n].Sun.Flare.Texture = "weather\sun\flare\allflares.tga.tx";
	Weathers[n].Sun.Flare.Dist = 3500.0;
	Weathers[n].Sun.Flare.TexSizeX = 2;
	Weathers[n].Sun.Flare.TexSizeY = 2;
	Weathers[n].Sun.Flare.Technique = "sunflare";
	Weathers[n].Sun.Flare.Scale = 2.0;
	Weathers[n].Sun.Flares.f1 = "1.0,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f2 = "0.9,20.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f3 = "0.8,30.0,2,0x0F0F0F";
	Weathers[n].Sun.Flares.f4 = "0.6,150.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f5 = "0.5,50.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f6 = "0.4,100.0,1,0x0F0F0F";
	Weathers[n].Sun.Flares.f7 = "0.3,200.0,0,0x0F0F0F";
	Weathers[n].Sun.Flares.f8 = "0.2,200.0,0,0x0F0F0F";

	Weathers[n].Sea.GF2MX.Sky.Color = argb(0,160,210,255);
	Weathers[n].Sea.GF2MX.Water.Color = argb(0,0,5,10);
	Weathers[n].Sea.GF2MX.Bump.Tile = 0.05;
	Weathers[n].Sea.GF2MX.Bump.AnimSpeed = 7.0;
	Weathers[n].Sea.GF2MX.Bump.Dir = "weather\sea\bump_g2mx\";

	Weathers[n].Sea.Transparency = 0.2;
	Weathers[n].Sea.FrenelCoefficient = 0.7;
	Weathers[n].Sea.WaterReflection = 0.7;
	Weathers[n].Sea.WaterAttenuation = 0.8;
	Weathers[n].Sea.Sky.Color = argb(0,255,255,255);
	Weathers[n].Sea.Water.Color = argb(0,30,50,85);
	Weathers[n].Sea.Pena.Color = argb(0,55,55,55);
	Weathers[n].Sea.Bump.Dir = "resource\textures\weather\sea\bump_g3\";
	Weathers[n].Sea.Bump.Tile = 0.04;
	Weathers[n].Sea.Bump.Ang = 0.0;
	Weathers[n].Sea.Bump.Speed = 0.01;
	Weathers[n].Sea.Bump.AnimSpeed = 15.0;
	Weathers[n].Sea.Bump.Scale = 2.0;
	Weathers[n].Sea.SunRoad.Start = 0.99;
	Weathers[n].Sea.SunRoad.Color1 = argb(0,255,55,44);
	Weathers[n].Sea.SunRoad.Color2 = argb(0,255,100,0);
	Weathers[n].Sea.SunRoad.Power = 3.0;
	//угол, частота, высота волны в метрах, начальная позиция волны, скорость волны
	Weathers[n].Sea.Harmonics.h1 = "90.0, 2.0, 4.0, 0.0, 20.0";
	Weathers[n].Sea.Harmonics.h2 = "0.0, 2.0, 2.0, 0.0, 40.0";
	Weathers[n].Sea.Harmonics.h3 = "45.0, 5.0, 1.0, 0.0, 60.0";
	Weathers[n].Sea.Harmonics.h4 = "90.0, 10.0, 0.2, 0.0, 80.0";
	Weathers[n].Sea.Harmonics.h5 = "0.0, 15.0, 0.3, 0.0, 90.0";
	Weathers[n].Sea.Harmonics.h6 = "45.0, 20.0, 0.4, 0.0, 100.0";

	Weathers[n].Sun.Reflection.Enable = true;
	Weathers[n].Sun.Reflection.Texture = "weather\sun\reflection\refl_evening.tga.tx";
	Weathers[n].Sun.Reflection.Technique = "sunreflection";
	Weathers[n].Sun.Reflection.Dist = 3500.0;
	Weathers[n].Sun.Reflection.Size = 500.0;
	Weathers[n].Sun.Reflection.Color = argb(200, 200, 200, 200);

	Weathers[n].Sea2.BumpScale = 0.05; //МЕЛКИЕ ВОЛНЫ
	Weathers[n].Sea2.PosShift = 2.0; //остроконечность волн
	
	Weathers[n].Sea2.WaterColor = argb(0,30,50,85);
	Weathers[n].Sea2.SkyColor = argb(0, 255, 255, 255);

	Weathers[n].Sea2.Reflection = 0.7;
	Weathers[n].Sea2.Transparency = 0.2;
	Weathers[n].Sea2.Frenel = 0.7; 
	Weathers[n].Sea2.Attenuation = 0.8;

	Weathers[n].Sea2.Amp1 = 25.0; //амплитуда 1 волны
	Weathers[n].Sea2.AnimSpeed1 = 2.0; //скорость анимации
	Weathers[n].Sea2.Scale1 = 0.17; //размеры волны
	Weathers[n].Sea2.MoveSpeed1 = "7.0, 0.0, 0.0"; //скорость движения

	Weathers[n].Sea2.Amp2 = 1.0;
	Weathers[n].Sea2.AnimSpeed2 = 10.0;
	Weathers[n].Sea2.Scale2 = 2.0;
	Weathers[n].Sea2.MoveSpeed2 = "0.0, 0.0, -1.0";	

	Weathers[n].Sea2.FoamK = 0.03;//яркость пены по высоте 0.1 - пена яркая с 10 метров 1.0 через метр после начала
	Weathers[n].Sea2.FoamV = 10.0;//высота с которой начинается пена
	Weathers[n].Sea2.FoamUV = 0.3; //тайлинг пены
	Weathers[n].Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

	Weathers[n].Wind.Angle = 2.0;
	Weathers[n].Wind.Speed.Min = 7.0;
	Weathers[n].Wind.Speed.Max = 14.0;
	
	n++;

	return n;
}
