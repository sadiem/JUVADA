xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 254;
 0.29661;1.34141;-0.59053;,
 0.59592;1.34141;-0.29122;,
 0.43407;1.81534;-0.42868;,
 0.59592;1.34141;0.30739;,
 0.29661;1.34141;0.60670;,
 0.43407;1.81534;0.44485;,
 -0.30200;1.34141;0.60670;,
 -0.60131;1.34141;0.30739;,
 -0.43946;1.81534;0.44485;,
 -0.60131;1.34141;-0.29122;,
 -0.30200;1.34141;-0.59053;,
 -0.43946;1.81534;-0.42868;,
 0.59592;0.65859;-0.29122;,
 0.29661;0.65859;-0.59053;,
 0.43407;0.18466;-0.42868;,
 0.29661;0.65859;0.60670;,
 0.59592;0.65859;0.30739;,
 0.43407;0.18466;0.44485;,
 -0.60131;0.65859;0.30739;,
 -0.30200;0.65859;0.60670;,
 -0.43946;0.18466;0.44485;,
 -0.30200;0.65859;-0.59053;,
 -0.60131;0.65859;-0.29122;,
 -0.43946;0.18466;-0.42868;,
 -0.00270;1.94400;-0.31809;,
 0.43407;1.81534;-0.42868;,
 0.32348;1.94400;0.00809;,
 -0.00270;1.21507;-0.53884;,
 0.11335;1.00000;-0.34004;,
 0.59592;1.34141;-0.29122;,
 0.34543;1.00000;-0.10796;,
 0.54423;1.21507;0.00809;,
 0.32348;1.94400;0.00809;,
 0.43407;1.81534;0.44485;,
 -0.00270;1.94400;0.33426;,
 0.54423;1.21507;0.00809;,
 0.34543;1.00000;0.12413;,
 0.59592;1.34141;0.30739;,
 0.11335;1.00000;0.35621;,
 -0.00270;1.21507;0.55501;,
 -0.00270;1.94400;0.33426;,
 -0.43946;1.81534;0.44485;,
 -0.32887;1.94400;0.00809;,
 -0.00270;1.21507;0.55501;,
 -0.11874;1.00000;0.35621;,
 -0.30200;1.34141;0.60670;,
 -0.35082;1.00000;0.12413;,
 -0.54962;1.21507;0.00809;,
 -0.32887;1.94400;0.00809;,
 -0.43946;1.81534;-0.42868;,
 -0.00270;1.94400;-0.31809;,
 -0.54962;1.21507;0.00809;,
 -0.35082;1.00000;-0.10796;,
 -0.60131;1.34141;-0.29122;,
 -0.30200;1.34141;-0.59053;,
 -0.11874;1.00000;-0.34004;,
 -0.00270;1.21507;-0.53884;,
 0.32348;0.05600;0.00809;,
 0.43407;0.18466;-0.42868;,
 -0.00270;0.05600;-0.31809;,
 0.54423;0.78493;0.00809;,
 0.59592;0.65859;-0.29122;,
 -0.00270;0.78493;-0.53884;,
 -0.00270;0.05600;0.33426;,
 0.43407;0.18466;0.44485;,
 0.32348;0.05600;0.00809;,
 -0.00270;0.78493;0.55501;,
 0.59592;0.65859;0.30739;,
 0.34543;1.00000;0.12413;,
 0.54423;0.78493;0.00809;,
 -0.32887;0.05600;0.00809;,
 -0.43946;0.18466;0.44485;,
 -0.00270;0.05600;0.33426;,
 -0.54962;0.78493;0.00809;,
 -0.60131;0.65859;0.30739;,
 -0.30200;0.65859;0.60670;,
 -0.11874;1.00000;0.35621;,
 -0.00270;0.78493;0.55501;,
 -0.00270;0.05600;-0.31809;,
 -0.43946;0.18466;-0.42868;,
 -0.32887;0.05600;0.00809;,
 -0.00270;0.78493;-0.53884;,
 -0.11874;1.00000;-0.34004;,
 -0.30200;0.65859;-0.59053;,
 -0.60131;0.65859;-0.29122;,
 -0.35082;1.00000;-0.10796;,
 -0.54962;0.78493;0.00809;,
 -0.00270;1.71223;-0.73787;,
 0.29661;1.34141;-0.59053;,
 0.25678;1.00000;-0.25139;,
 0.59592;1.34141;-0.29122;,
 0.43407;1.81534;-0.42868;,
 0.74326;1.71223;0.00809;,
 0.74326;1.71223;0.00809;,
 0.59592;1.34141;0.30739;,
 0.43407;1.81534;0.44485;,
 0.59592;1.34141;0.30739;,
 0.25678;1.00000;0.26757;,
 0.29661;1.34141;0.60670;,
 -0.00270;1.71223;0.75405;,
 -0.00270;1.71223;0.75405;,
 -0.30200;1.34141;0.60670;,
 -0.43946;1.81534;0.44485;,
 -0.30200;1.34141;0.60670;,
 -0.26218;1.00000;0.26757;,
 -0.60131;1.34141;0.30739;,
 -0.74865;1.71223;0.00809;,
 -0.74865;1.71223;0.00809;,
 -0.60131;1.34141;-0.29122;,
 -0.26218;1.00000;-0.25139;,
 -0.30200;1.34141;-0.59053;,
 -0.43946;1.81534;-0.42868;,
 -0.30200;1.34141;-0.59053;,
 -0.00270;1.71223;-0.73787;,
 0.74326;0.28777;0.00809;,
 0.43407;0.18466;-0.42868;,
 0.59592;0.65859;-0.29122;,
 0.25678;1.00000;-0.25139;,
 0.29661;0.65859;-0.59053;,
 -0.00270;0.28777;-0.73787;,
 -0.00270;0.28777;0.75405;,
 0.29661;0.65859;0.60670;,
 0.25678;1.00000;0.26757;,
 0.59592;0.65859;0.30739;,
 0.43407;0.18466;0.44485;,
 0.59592;0.65859;0.30739;,
 0.74326;0.28777;0.00809;,
 -0.74865;0.28777;0.00809;,
 -0.43946;0.18466;0.44485;,
 -0.60131;0.65859;0.30739;,
 -0.26218;1.00000;0.26757;,
 -0.30200;0.65859;0.60670;,
 -0.00270;0.28777;0.75405;,
 -0.00270;0.28777;-0.73787;,
 -0.30200;0.65859;-0.59053;,
 -0.43946;0.18466;-0.42868;,
 -0.30200;0.65859;-0.59053;,
 -0.26218;1.00000;-0.25139;,
 -0.60131;0.65859;-0.29122;,
 -0.74865;0.28777;0.00809;,
 -0.00270;2.00000;0.00809;,
 -0.00270;1.71223;-0.73787;,
 0.74326;1.71223;0.00809;,
 -0.00270;1.00000;-0.35887;,
 0.11335;1.00000;-0.34004;,
 0.34543;1.00000;-0.10796;,
 0.36426;1.00000;0.00809;,
 -0.00270;2.00000;0.00809;,
 0.32348;1.94400;0.00809;,
 -0.00270;1.94400;0.33426;,
 0.32348;1.94400;0.00809;,
 0.74326;1.71223;0.00809;,
 0.43407;1.81534;0.44485;,
 -0.00270;1.71223;0.75405;,
 0.74326;1.71223;0.00809;,
 0.54423;1.21507;0.00809;,
 0.59592;1.34141;0.30739;,
 0.54423;1.21507;0.00809;,
 0.36426;1.00000;0.00809;,
 0.34543;1.00000;0.12413;,
 0.34543;1.00000;0.12413;,
 0.11335;1.00000;0.35621;,
 -0.00270;1.00000;0.37505;,
 -0.00270;2.00000;0.00809;,
 -0.00270;1.94400;0.33426;,
 -0.32887;1.94400;0.00809;,
 -0.00270;1.94400;0.33426;,
 -0.00270;1.71223;0.75405;,
 -0.43946;1.81534;0.44485;,
 -0.74865;1.71223;0.00809;,
 -0.00270;1.71223;0.75405;,
 -0.00270;1.21507;0.55501;,
 -0.30200;1.34141;0.60670;,
 -0.00270;1.21507;0.55501;,
 -0.00270;1.00000;0.37505;,
 -0.11874;1.00000;0.35621;,
 -0.11874;1.00000;0.35621;,
 -0.35082;1.00000;0.12413;,
 -0.36965;1.00000;0.00809;,
 -0.00270;2.00000;0.00809;,
 -0.32887;1.94400;0.00809;,
 -0.00270;1.94400;-0.31809;,
 -0.32887;1.94400;0.00809;,
 -0.74865;1.71223;0.00809;,
 -0.43946;1.81534;-0.42868;,
 -0.00270;1.94400;-0.31809;,
 -0.43946;1.81534;-0.42868;,
 -0.00270;1.71223;-0.73787;,
 -0.74865;1.71223;0.00809;,
 -0.54962;1.21507;0.00809;,
 -0.60131;1.34141;-0.29122;,
 -0.54962;1.21507;0.00809;,
 -0.36965;1.00000;0.00809;,
 -0.35082;1.00000;-0.10796;,
 -0.35082;1.00000;-0.10796;,
 -0.00270;1.71223;-0.73787;,
 -0.30200;1.34141;-0.59053;,
 -0.00270;1.21507;-0.53884;,
 -0.11874;1.00000;-0.34004;,
 -0.00270;1.21507;-0.53884;,
 -0.11874;1.00000;-0.34004;,
 -0.00270;1.00000;-0.35887;,
 -0.00270;0.00000;0.00809;,
 0.74326;0.28777;0.00809;,
 -0.00270;0.28777;-0.73787;,
 0.34543;1.00000;-0.10796;,
 0.11335;1.00000;-0.34004;,
 -0.00270;0.00000;0.00809;,
 -0.00270;0.05600;0.33426;,
 0.32348;0.05600;0.00809;,
 -0.00270;0.28777;0.75405;,
 0.32348;0.05600;0.00809;,
 0.43407;0.18466;0.44485;,
 0.74326;0.28777;0.00809;,
 0.11335;1.00000;0.35621;,
 0.74326;0.28777;0.00809;,
 0.59592;0.65859;0.30739;,
 0.54423;0.78493;0.00809;,
 0.34543;1.00000;0.12413;,
 0.54423;0.78493;0.00809;,
 -0.00270;0.00000;0.00809;,
 -0.32887;0.05600;0.00809;,
 -0.00270;0.05600;0.33426;,
 -0.74865;0.28777;0.00809;,
 -0.00270;0.05600;0.33426;,
 -0.43946;0.18466;0.44485;,
 -0.00270;0.28777;0.75405;,
 -0.35082;1.00000;0.12413;,
 -0.00270;0.28777;0.75405;,
 -0.30200;0.65859;0.60670;,
 -0.00270;0.78493;0.55501;,
 -0.11874;1.00000;0.35621;,
 -0.00270;0.78493;0.55501;,
 -0.00270;0.00000;0.00809;,
 -0.00270;0.05600;-0.31809;,
 -0.32887;0.05600;0.00809;,
 -0.00270;0.05600;-0.31809;,
 -0.00270;0.28777;-0.73787;,
 -0.43946;0.18466;-0.42868;,
 -0.32887;0.05600;0.00809;,
 -0.43946;0.18466;-0.42868;,
 -0.74865;0.28777;0.00809;,
 -0.00270;0.28777;-0.73787;,
 -0.00270;0.78493;-0.53884;,
 -0.30200;0.65859;-0.59053;,
 -0.00270;0.78493;-0.53884;,
 -0.00270;1.00000;-0.35887;,
 -0.11874;1.00000;-0.34004;,
 -0.11874;1.00000;-0.34004;,
 -0.74865;0.28777;0.00809;,
 -0.60131;0.65859;-0.29122;,
 -0.54962;0.78493;0.00809;,
 -0.35082;1.00000;-0.10796;,
 -0.54962;0.78493;0.00809;;
 
 128;
 3;2,1,0;,
 3;5,4,3;,
 3;8,7,6;,
 3;11,10,9;,
 3;14,13,12;,
 3;17,16,15;,
 3;20,19,18;,
 3;23,22,21;,
 3;26,25,24;,
 3;0,28,27;,
 3;31,30,29;,
 3;34,33,32;,
 3;37,36,35;,
 3;39,38,4;,
 3;42,41,40;,
 3;45,44,43;,
 3;47,46,7;,
 3;50,49,48;,
 3;53,52,51;,
 3;56,55,54;,
 3;59,58,57;,
 3;61,30,60;,
 3;62,28,13;,
 3;65,64,63;,
 3;15,38,66;,
 3;69,68,67;,
 3;72,71,70;,
 3;74,46,73;,
 3;77,76,75;,
 3;80,79,78;,
 3;83,82,81;,
 3;86,85,84;,
 3;2,0,87;,
 3;90,89,88;,
 3;92,29,91;,
 3;95,94,93;,
 3;98,97,96;,
 3;99,4,5;,
 3;102,101,100;,
 3;105,104,103;,
 3;106,7,8;,
 3;11,9,107;,
 3;110,109,108;,
 3;113,112,111;,
 3;115,61,114;,
 3;118,117,116;,
 3;119,13,14;,
 3;17,15,120;,
 3;123,122,121;,
 3;126,125,124;,
 3;128,74,127;,
 3;131,130,129;,
 3;132,19,20;,
 3;135,134,133;,
 3;138,137,136;,
 3;139,22,23;,
 3;26,24,140;,
 3;25,141,24;,
 3;142,25,26;,
 3;0,27,87;,
 3;28,143,27;,
 3;89,144,88;,
 3;31,29,92;,
 3;145,89,90;,
 3;146,30,31;,
 3;149,148,147;,
 3;152,151,150;,
 3;153,33,34;,
 3;156,155,154;,
 3;159,158,157;,
 3;97,160,96;,
 3;39,4,99;,
 3;161,97,98;,
 3;162,38,39;,
 3;165,164,163;,
 3;168,167,166;,
 3;169,41,42;,
 3;172,171,170;,
 3;175,174,173;,
 3;104,176,103;,
 3;47,7,106;,
 3;177,104,105;,
 3;178,46,47;,
 3;181,180,179;,
 3;184,183,182;,
 3;187,186,185;,
 3;190,189,188;,
 3;193,192,191;,
 3;109,194,108;,
 3;197,196,195;,
 3;198,109,110;,
 3;201,200,199;,
 3;59,57,202;,
 3;58,203,57;,
 3;204,58,59;,
 3;61,60,114;,
 3;30,146,60;,
 3;117,205,116;,
 3;62,13,119;,
 3;206,117,118;,
 3;143,28,62;,
 3;209,208,207;,
 3;64,210,63;,
 3;213,212,211;,
 3;15,66,120;,
 3;38,162,66;,
 3;122,214,121;,
 3;217,216,215;,
 3;218,122,123;,
 3;158,159,219;,
 3;222,221,220;,
 3;71,223,70;,
 3;226,225,224;,
 3;74,73,127;,
 3;46,178,73;,
 3;130,227,129;,
 3;230,229,228;,
 3;231,130,131;,
 3;174,175,232;,
 3;235,234,233;,
 3;238,237,236;,
 3;241,240,239;,
 3;244,243,242;,
 3;247,246,245;,
 3;137,248,136;,
 3;251,250,249;,
 3;252,137,138;,
 3;192,193,253;;
 
 MeshMaterialList {
  1;
  128;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "00tex_master.BMP";
   }
  }
 }
 MeshNormals {
  128;
  0.166824;0.971771;-0.166825;,
  0.123507;-0.636823;-0.761053;,
  0.761052;-0.636825;-0.123502;,
  0.123501;-0.636824;0.761054;,
  -0.761054;-0.636824;0.123501;,
  0.166825;-0.971771;-0.166825;,
  0.554497;0.120367;-0.823435;,
  0.556238;-0.617412;-0.556239;,
  0.823435;0.120369;-0.554497;,
  0.556238;-0.617412;0.556239;,
  0.554497;0.120367;0.823435;,
  -0.556239;-0.617411;0.556239;,
  -0.823435;0.120368;0.554496;,
  -0.556239;-0.617411;-0.556239;,
  0.823435;-0.120369;-0.554497;,
  0.554497;-0.120367;-0.823435;,
  0.554496;-0.120368;0.823435;,
  -0.823436;-0.120370;0.554495;,
  0.706638;0.036355;-0.706640;,
  0.706638;0.036355;0.706641;,
  -0.706639;0.036354;0.706639;,
  -0.706639;0.036354;-0.706639;,
  0.706638;-0.036355;-0.706641;,
  0.706639;-0.036355;0.706639;,
  -0.706638;-0.036355;0.706641;,
  -0.706639;-0.036354;-0.706639;,
  0.223056;0.948942;-0.223057;,
  0.135134;-0.632248;-0.762890;,
  0.762890;-0.632248;-0.135133;,
  0.223056;0.948942;0.223056;,
  0.762890;-0.632248;0.135134;,
  0.135133;-0.632246;0.762892;,
  -0.223056;0.948942;0.223056;,
  -0.135133;-0.632246;0.762891;,
  -0.762892;-0.632246;0.135133;,
  -0.762892;-0.632246;-0.135133;,
  -0.135134;-0.632248;-0.762890;,
  0.223056;-0.948942;-0.223056;,
  0.762891;0.632247;-0.135131;,
  0.135131;0.632247;-0.762891;,
  0.223056;-0.948942;0.223057;,
  0.135133;0.632246;0.762891;,
  -0.223056;-0.948942;0.223057;,
  -0.762891;0.632247;0.135131;,
  -0.223056;0.948942;-0.223057;,
  0.762891;0.632247;0.135131;,
  -0.135134;0.632247;0.762891;,
  -0.223056;-0.948942;-0.223056;,
  -0.135132;0.632247;-0.762891;,
  -0.762891;0.632247;-0.135134;,
  0.823434;0.120368;0.554498;,
  -0.554497;0.120367;0.823435;,
  -0.823435;0.120367;-0.554497;,
  -0.554497;0.120367;-0.823435;,
  0.823434;-0.120368;0.554498;,
  -0.554497;-0.120367;0.823435;,
  -0.554497;-0.120367;-0.823435;,
  -0.823435;-0.120367;-0.554497;,
  0.166824;0.971771;0.166824;,
  0.478973;0.867500;0.134267;,
  0.928361;-0.371664;-0.003439;,
  0.761052;-0.636826;0.123500;,
  -0.166824;0.971771;0.166824;,
  -0.134267;0.867500;0.478974;,
  0.003439;-0.371664;0.928361;,
  -0.123502;-0.636824;0.761054;,
  -0.166824;0.971771;-0.166825;,
  -0.478974;0.867500;-0.134267;,
  -0.134267;0.867500;-0.478974;,
  -0.928361;-0.371664;0.003439;,
  -0.761054;-0.636824;-0.123502;,
  0.003439;-0.371664;-0.928361;,
  -0.123508;-0.636823;-0.761053;,
  0.166824;-0.971771;0.166824;,
  0.478974;-0.867500;0.134268;,
  0.928361;0.371664;-0.003440;,
  0.761054;0.636824;0.123501;,
  -0.166824;-0.971771;0.166824;,
  -0.134266;-0.867500;0.478974;,
  0.003438;0.371663;0.928361;,
  -0.123502;0.636824;0.761054;,
  -0.166825;-0.971771;-0.166825;,
  -0.134266;-0.867500;-0.478974;,
  -0.478974;-0.867500;-0.134267;,
  0.003440;0.371664;-0.928361;,
  -0.123508;0.636821;-0.761055;,
  -0.928361;0.371663;0.003438;,
  -0.761054;0.636824;-0.123502;,
  0.556238;0.617412;-0.556239;,
  0.556238;0.617412;0.556238;,
  -0.556238;0.617412;0.556239;,
  -0.556239;0.617411;-0.556239;,
  0.134267;0.867500;-0.478974;,
  0.478974;0.867500;-0.134268;,
  -0.003439;-0.371664;-0.928361;,
  0.389549;-0.671539;-0.630306;,
  0.928361;-0.371664;0.003439;,
  0.630305;-0.671540;-0.389550;,
  0.134267;0.867500;0.478974;,
  0.630305;-0.671540;0.389550;,
  -0.003439;-0.371664;0.928361;,
  0.389553;-0.671539;0.630305;,
  -0.478974;0.867500;0.134267;,
  -0.389551;-0.671539;0.630306;,
  -0.928361;-0.371664;-0.003439;,
  -0.630306;-0.671539;0.389551;,
  -0.630306;-0.671539;-0.389551;,
  -0.389547;-0.671540;-0.630307;,
  0.478974;-0.867500;-0.134267;,
  0.134266;-0.867500;-0.478974;,
  0.928361;0.371664;0.003440;,
  0.761054;0.636824;-0.123502;,
  0.630305;0.671540;-0.389550;,
  -0.003440;0.371664;-0.928361;,
  0.389549;0.671539;-0.630306;,
  0.123507;0.636821;-0.761055;,
  0.134266;-0.867500;0.478974;,
  -0.003438;0.371663;0.928361;,
  0.123501;0.636824;0.761054;,
  0.389553;0.671539;0.630305;,
  0.630305;0.671540;0.389550;,
  -0.478975;-0.867500;0.134267;,
  -0.928361;0.371663;-0.003441;,
  -0.761054;0.636824;0.123501;,
  -0.630305;0.671540;0.389550;,
  -0.389551;0.671539;0.630306;,
  -0.389547;0.671540;-0.630307;,
  -0.630306;0.671539;-0.389551;;
  128;
  3;18,18,18;,
  3;19,19,19;,
  3;20,20,20;,
  3;21,21,21;,
  3;22,22,22;,
  3;23,23,23;,
  3;24,24,24;,
  3;25,25,25;,
  3;26,26,26;,
  3;27,27,27;,
  3;28,28,28;,
  3;29,29,29;,
  3;30,30,30;,
  3;31,31,31;,
  3;32,32,32;,
  3;33,33,33;,
  3;34,34,34;,
  3;44,44,44;,
  3;35,35,35;,
  3;36,36,36;,
  3;37,37,37;,
  3;38,38,38;,
  3;39,39,39;,
  3;40,40,40;,
  3;41,41,41;,
  3;45,45,45;,
  3;42,42,42;,
  3;43,43,43;,
  3;46,46,46;,
  3;47,47,47;,
  3;48,48,48;,
  3;49,49,49;,
  3;6,6,6;,
  3;7,7,7;,
  3;8,8,8;,
  3;50,50,50;,
  3;9,9,9;,
  3;10,10,10;,
  3;51,51,51;,
  3;11,11,11;,
  3;12,12,12;,
  3;52,52,52;,
  3;13,13,13;,
  3;53,53,53;,
  3;14,14,14;,
  3;88,88,88;,
  3;15,15,15;,
  3;16,16,16;,
  3;89,89,89;,
  3;54,54,54;,
  3;17,17,17;,
  3;90,90,90;,
  3;55,55,55;,
  3;56,56,56;,
  3;91,91,91;,
  3;57,57,57;,
  3;0,0,0;,
  3;92,92,92;,
  3;93,93,93;,
  3;94,94,94;,
  3;1,1,1;,
  3;95,95,95;,
  3;96,96,96;,
  3;97,97,97;,
  3;2,2,2;,
  3;58,58,58;,
  3;59,59,59;,
  3;98,98,98;,
  3;60,60,60;,
  3;61,61,61;,
  3;99,99,99;,
  3;100,100,100;,
  3;101,101,101;,
  3;3,3,3;,
  3;62,62,62;,
  3;63,63,63;,
  3;102,102,102;,
  3;64,64,64;,
  3;65,65,65;,
  3;103,103,103;,
  3;104,104,104;,
  3;105,105,105;,
  3;4,4,4;,
  3;66,66,66;,
  3;67,67,67;,
  3;68,68,68;,
  3;69,69,69;,
  3;70,70,70;,
  3;106,106,106;,
  3;71,71,71;,
  3;107,107,107;,
  3;72,72,72;,
  3;5,5,5;,
  3;108,108,108;,
  3;109,109,109;,
  3;110,110,110;,
  3;111,111,111;,
  3;112,112,112;,
  3;113,113,113;,
  3;114,114,114;,
  3;115,115,115;,
  3;73,73,73;,
  3;116,116,116;,
  3;74,74,74;,
  3;117,117,117;,
  3;118,118,118;,
  3;119,119,119;,
  3;75,75,75;,
  3;120,120,120;,
  3;76,76,76;,
  3;77,77,77;,
  3;121,121,121;,
  3;78,78,78;,
  3;122,122,122;,
  3;123,123,123;,
  3;124,124,124;,
  3;79,79,79;,
  3;125,125,125;,
  3;80,80,80;,
  3;81,81,81;,
  3;82,82,82;,
  3;83,83,83;,
  3;84,84,84;,
  3;85,85,85;,
  3;126,126,126;,
  3;86,86,86;,
  3;127,127,127;,
  3;87,87,87;;
 }
 MeshTextureCoords {
  254;
  0.070990;0.107520;,
  0.008370;0.107520;,
  0.042230;0.008370;,
  0.275580;0.107520;,
  0.212970;0.107520;,
  0.241720;0.008370;,
  0.417560;0.107520;,
  0.354940;0.107520;,
  0.383700;0.008370;,
  0.605030;0.107520;,
  0.542420;0.107520;,
  0.576280;0.008370;,
  0.008370;0.250380;,
  0.070990;0.250380;,
  0.042230;0.349530;,
  0.212970;0.250380;,
  0.275580;0.250380;,
  0.241720;0.349530;,
  0.465130;0.539080;,
  0.527750;0.539080;,
  0.498990;0.638230;,
  0.542420;0.124260;,
  0.605030;0.124260;,
  0.576280;0.223410;,
  0.008370;0.454100;,
  0.099750;0.430960;,
  0.076610;0.522340;,
  0.133610;0.133960;,
  0.109330;0.178950;,
  0.496920;0.107520;,
  0.458580;0.178950;,
  0.434300;0.133960;,
  0.360560;0.366270;,
  0.383700;0.457650;,
  0.292320;0.434510;,
  0.070990;0.907220;,
  0.046710;0.952210;,
  0.008370;0.880780;,
  0.174620;0.178950;,
  0.150350;0.133960;,
  0.164440;0.607320;,
  0.073060;0.630460;,
  0.096190;0.539080;,
  0.354940;0.907220;,
  0.330660;0.952210;,
  0.292320;0.880780;,
  0.316600;0.178950;,
  0.292320;0.133960;,
  0.747940;0.868900;,
  0.724800;0.777530;,
  0.816180;0.800660;,
  0.580760;0.791320;,
  0.556480;0.836320;,
  0.518140;0.764890;,
  0.243790;0.885640;,
  0.205450;0.957070;,
  0.181170;0.912070;,
  0.468680;0.366270;,
  0.491820;0.457650;,
  0.400440;0.434510;,
  0.434300;0.223950;,
  0.496920;0.250380;,
  0.133610;0.223950;,
  0.181170;0.454100;,
  0.272550;0.430960;,
  0.249410;0.522340;,
  0.150350;0.223950;,
  0.607100;0.957070;,
  0.645440;0.885640;,
  0.669720;0.930640;,
  0.380150;0.630450;,
  0.357010;0.539080;,
  0.448390;0.562210;,
  0.292320;0.223950;,
  0.354940;0.250380;,
  0.724800;0.957070;,
  0.763140;0.885640;,
  0.787420;0.930640;,
  0.501400;0.833130;,
  0.410020;0.856270;,
  0.433160;0.764890;,
  0.832920;0.927080;,
  0.857200;0.882090;,
  0.895540;0.953520;,
  0.518140;0.944440;,
  0.556480;0.873010;,
  0.580760;0.918000;,
  0.133610;0.029940;,
  0.330660;0.748150;,
  0.322330;0.677200;,
  0.393280;0.685530;,
  0.525680;0.008370;,
  0.434300;0.029940;,
  0.823330;0.387840;,
  0.760720;0.465430;,
  0.731960;0.366270;,
  0.510980;0.709810;,
  0.440030;0.718140;,
  0.448360;0.647190;,
  0.150350;0.029940;,
  0.855130;0.029940;,
  0.792510;0.107520;,
  0.763750;0.008370;,
  0.749080;0.539080;,
  0.757410;0.610030;,
  0.686460;0.601700;,
  0.292320;0.029940;,
  0.667650;0.029940;,
  0.701130;0.278490;,
  0.772080;0.270160;,
  0.763750;0.341110;,
  0.855130;0.124260;,
  0.826370;0.223410;,
  0.763750;0.145830;,
  0.434300;0.327960;,
  0.525680;0.349530;,
  0.282130;0.722450;,
  0.211180;0.730780;,
  0.219510;0.659830;,
  0.133610;0.327960;,
  0.150350;0.327960;,
  0.645440;0.760790;,
  0.637110;0.689840;,
  0.708060;0.698170;,
  0.008370;0.864050;,
  0.037130;0.764890;,
  0.099750;0.842470;,
  0.292320;0.327960;,
  0.383700;0.349530;,
  0.008370;0.685530;,
  0.079320;0.677200;,
  0.070990;0.748150;,
  0.590370;0.616660;,
  0.292320;0.842470;,
  0.354940;0.764890;,
  0.383700;0.864050;,
  0.787420;0.659830;,
  0.795750;0.730780;,
  0.724800;0.722450;,
  0.667650;0.201840;,
  0.008370;0.522340;,
  0.008370;0.366270;,
  0.164440;0.522340;,
  0.133610;0.178950;,
  0.292320;0.695750;,
  0.340880;0.647190;,
  0.434300;0.178950;,
  0.087730;0.880780;,
  0.155970;0.880780;,
  0.087730;0.949020;,
  0.181170;0.777530;,
  0.269000;0.777530;,
  0.204310;0.868900;,
  0.292320;0.522340;,
  0.635860;0.366270;,
  0.635860;0.470290;,
  0.573240;0.443850;,
  0.150350;0.647190;,
  0.150350;0.692190;,
  0.126070;0.692190;,
  0.458580;0.748150;,
  0.410020;0.699600;,
  0.150350;0.178950;,
  0.940110;0.124260;,
  0.940110;0.192500;,
  0.871860;0.124260;,
  0.895540;0.539080;,
  0.895540;0.626900;,
  0.804160;0.562210;,
  0.008370;0.539080;,
  0.605030;0.240150;,
  0.605030;0.344170;,
  0.542420;0.317730;,
  0.552000;0.647190;,
  0.552000;0.692190;,
  0.527720;0.692190;,
  0.787420;0.591480;,
  0.738860;0.640040;,
  0.292320;0.178950;,
  0.980520;0.607320;,
  0.912270;0.607320;,
  0.980520;0.539080;,
  0.906650;0.331530;,
  0.818830;0.331530;,
  0.883520;0.240150;,
  0.924300;0.865350;,
  0.832920;0.842210;,
  0.924300;0.777530;,
  0.243790;0.539080;,
  0.243790;0.643090;,
  0.181170;0.616660;,
  0.896140;0.008370;,
  0.896140;0.053360;,
  0.871860;0.053360;,
  0.753530;0.240150;,
  0.607100;0.539080;,
  0.669720;0.616660;,
  0.607100;0.643090;,
  0.802090;0.288710;,
  0.116480;0.764890;,
  0.140760;0.809890;,
  0.116480;0.809890;,
  0.400440;0.366270;,
  0.556500;0.366270;,
  0.400440;0.522340;,
  0.229730;0.760790;,
  0.181170;0.712230;,
  0.912270;0.950330;,
  0.912270;0.882090;,
  0.980520;0.950330;,
  0.181170;0.366270;,
  0.840070;0.457650;,
  0.863210;0.366270;,
  0.927900;0.457650;,
  0.607100;0.708380;,
  0.684390;0.344160;,
  0.621770;0.266580;,
  0.684390;0.240150;,
  0.655660;0.659830;,
  0.150350;0.737190;,
  0.981120;0.076610;,
  0.912880;0.076610;,
  0.981120;0.008370;,
  0.292320;0.630460;,
  0.933880;0.747650;,
  0.842500;0.724510;,
  0.933880;0.659830;,
  0.060770;0.647190;,
  0.715220;0.470290;,
  0.652600;0.392700;,
  0.715220;0.366270;,
  0.109330;0.695750;,
  0.552000;0.737190;,
  0.991630;0.240150;,
  0.991630;0.308390;,
  0.923390;0.240150;,
  0.501400;0.873010;,
  0.501400;0.960830;,
  0.410020;0.896140;,
  0.694930;0.777530;,
  0.671790;0.868900;,
  0.607100;0.777530;,
  0.684390;0.112380;,
  0.684390;0.008370;,
  0.747010;0.034800;,
  0.731960;0.527160;,
  0.731960;0.482160;,
  0.756230;0.482160;,
  0.825760;0.712230;,
  0.747010;0.228270;,
  0.684390;0.150690;,
  0.747010;0.124260;,
  0.777210;0.760790;,
  0.896140;0.098360;;
 }
 MeshVertexColors {
  254;
  0;1.000000;1.000000;1.000000;1.000000;,
  1;1.000000;1.000000;1.000000;1.000000;,
  2;1.000000;1.000000;1.000000;1.000000;,
  3;1.000000;1.000000;1.000000;1.000000;,
  4;1.000000;1.000000;1.000000;1.000000;,
  5;1.000000;1.000000;1.000000;1.000000;,
  6;1.000000;1.000000;1.000000;1.000000;,
  7;1.000000;1.000000;1.000000;1.000000;,
  8;1.000000;1.000000;1.000000;1.000000;,
  9;1.000000;1.000000;1.000000;1.000000;,
  10;1.000000;1.000000;1.000000;1.000000;,
  11;1.000000;1.000000;1.000000;1.000000;,
  12;1.000000;1.000000;1.000000;1.000000;,
  13;1.000000;1.000000;1.000000;1.000000;,
  14;1.000000;1.000000;1.000000;1.000000;,
  15;1.000000;1.000000;1.000000;1.000000;,
  16;1.000000;1.000000;1.000000;1.000000;,
  17;1.000000;1.000000;1.000000;1.000000;,
  18;1.000000;1.000000;1.000000;1.000000;,
  19;1.000000;1.000000;1.000000;1.000000;,
  20;1.000000;1.000000;1.000000;1.000000;,
  21;1.000000;1.000000;1.000000;1.000000;,
  22;1.000000;1.000000;1.000000;1.000000;,
  23;1.000000;1.000000;1.000000;1.000000;,
  24;1.000000;1.000000;1.000000;1.000000;,
  25;1.000000;1.000000;1.000000;1.000000;,
  26;1.000000;1.000000;1.000000;1.000000;,
  27;1.000000;1.000000;1.000000;1.000000;,
  28;1.000000;1.000000;1.000000;1.000000;,
  29;1.000000;1.000000;1.000000;1.000000;,
  30;1.000000;1.000000;1.000000;1.000000;,
  31;1.000000;1.000000;1.000000;1.000000;,
  32;1.000000;1.000000;1.000000;1.000000;,
  33;1.000000;1.000000;1.000000;1.000000;,
  34;1.000000;1.000000;1.000000;1.000000;,
  35;1.000000;1.000000;1.000000;1.000000;,
  36;1.000000;1.000000;1.000000;1.000000;,
  37;1.000000;1.000000;1.000000;1.000000;,
  38;1.000000;1.000000;1.000000;1.000000;,
  39;1.000000;1.000000;1.000000;1.000000;,
  40;1.000000;1.000000;1.000000;1.000000;,
  41;1.000000;1.000000;1.000000;1.000000;,
  42;1.000000;1.000000;1.000000;1.000000;,
  43;1.000000;1.000000;1.000000;1.000000;,
  44;1.000000;1.000000;1.000000;1.000000;,
  45;1.000000;1.000000;1.000000;1.000000;,
  46;1.000000;1.000000;1.000000;1.000000;,
  47;1.000000;1.000000;1.000000;1.000000;,
  48;1.000000;1.000000;1.000000;1.000000;,
  49;1.000000;1.000000;1.000000;1.000000;,
  50;1.000000;1.000000;1.000000;1.000000;,
  51;1.000000;1.000000;1.000000;1.000000;,
  52;1.000000;1.000000;1.000000;1.000000;,
  53;1.000000;1.000000;1.000000;1.000000;,
  54;1.000000;1.000000;1.000000;1.000000;,
  55;1.000000;1.000000;1.000000;1.000000;,
  56;1.000000;1.000000;1.000000;1.000000;,
  57;1.000000;1.000000;1.000000;1.000000;,
  58;1.000000;1.000000;1.000000;1.000000;,
  59;1.000000;1.000000;1.000000;1.000000;,
  60;1.000000;1.000000;1.000000;1.000000;,
  61;1.000000;1.000000;1.000000;1.000000;,
  62;1.000000;1.000000;1.000000;1.000000;,
  63;1.000000;1.000000;1.000000;1.000000;,
  64;1.000000;1.000000;1.000000;1.000000;,
  65;1.000000;1.000000;1.000000;1.000000;,
  66;1.000000;1.000000;1.000000;1.000000;,
  67;1.000000;1.000000;1.000000;1.000000;,
  68;1.000000;1.000000;1.000000;1.000000;,
  69;1.000000;1.000000;1.000000;1.000000;,
  70;1.000000;1.000000;1.000000;1.000000;,
  71;1.000000;1.000000;1.000000;1.000000;,
  72;1.000000;1.000000;1.000000;1.000000;,
  73;1.000000;1.000000;1.000000;1.000000;,
  74;1.000000;1.000000;1.000000;1.000000;,
  75;1.000000;1.000000;1.000000;1.000000;,
  76;1.000000;1.000000;1.000000;1.000000;,
  77;1.000000;1.000000;1.000000;1.000000;,
  78;1.000000;1.000000;1.000000;1.000000;,
  79;1.000000;1.000000;1.000000;1.000000;,
  80;1.000000;1.000000;1.000000;1.000000;,
  81;1.000000;1.000000;1.000000;1.000000;,
  82;1.000000;1.000000;1.000000;1.000000;,
  83;1.000000;1.000000;1.000000;1.000000;,
  84;1.000000;1.000000;1.000000;1.000000;,
  85;1.000000;1.000000;1.000000;1.000000;,
  86;1.000000;1.000000;1.000000;1.000000;,
  87;1.000000;1.000000;1.000000;1.000000;,
  88;1.000000;1.000000;1.000000;1.000000;,
  89;1.000000;1.000000;1.000000;1.000000;,
  90;1.000000;1.000000;1.000000;1.000000;,
  91;1.000000;1.000000;1.000000;1.000000;,
  92;1.000000;1.000000;1.000000;1.000000;,
  93;1.000000;1.000000;1.000000;1.000000;,
  94;1.000000;1.000000;1.000000;1.000000;,
  95;1.000000;1.000000;1.000000;1.000000;,
  96;1.000000;1.000000;1.000000;1.000000;,
  97;1.000000;1.000000;1.000000;1.000000;,
  98;1.000000;1.000000;1.000000;1.000000;,
  99;1.000000;1.000000;1.000000;1.000000;,
  100;1.000000;1.000000;1.000000;1.000000;,
  101;1.000000;1.000000;1.000000;1.000000;,
  102;1.000000;1.000000;1.000000;1.000000;,
  103;1.000000;1.000000;1.000000;1.000000;,
  104;1.000000;1.000000;1.000000;1.000000;,
  105;1.000000;1.000000;1.000000;1.000000;,
  106;1.000000;1.000000;1.000000;1.000000;,
  107;1.000000;1.000000;1.000000;1.000000;,
  108;1.000000;1.000000;1.000000;1.000000;,
  109;1.000000;1.000000;1.000000;1.000000;,
  110;1.000000;1.000000;1.000000;1.000000;,
  111;1.000000;1.000000;1.000000;1.000000;,
  112;1.000000;1.000000;1.000000;1.000000;,
  113;1.000000;1.000000;1.000000;1.000000;,
  114;1.000000;1.000000;1.000000;1.000000;,
  115;1.000000;1.000000;1.000000;1.000000;,
  116;1.000000;1.000000;1.000000;1.000000;,
  117;1.000000;1.000000;1.000000;1.000000;,
  118;1.000000;1.000000;1.000000;1.000000;,
  119;1.000000;1.000000;1.000000;1.000000;,
  120;1.000000;1.000000;1.000000;1.000000;,
  121;1.000000;1.000000;1.000000;1.000000;,
  122;1.000000;1.000000;1.000000;1.000000;,
  123;1.000000;1.000000;1.000000;1.000000;,
  124;1.000000;1.000000;1.000000;1.000000;,
  125;1.000000;1.000000;1.000000;1.000000;,
  126;1.000000;1.000000;1.000000;1.000000;,
  127;1.000000;1.000000;1.000000;1.000000;,
  128;1.000000;1.000000;1.000000;1.000000;,
  129;1.000000;1.000000;1.000000;1.000000;,
  130;1.000000;1.000000;1.000000;1.000000;,
  131;1.000000;1.000000;1.000000;1.000000;,
  132;1.000000;1.000000;1.000000;1.000000;,
  133;1.000000;1.000000;1.000000;1.000000;,
  134;1.000000;1.000000;1.000000;1.000000;,
  135;1.000000;1.000000;1.000000;1.000000;,
  136;1.000000;1.000000;1.000000;1.000000;,
  137;1.000000;1.000000;1.000000;1.000000;,
  138;1.000000;1.000000;1.000000;1.000000;,
  139;1.000000;1.000000;1.000000;1.000000;,
  140;1.000000;1.000000;1.000000;1.000000;,
  141;1.000000;1.000000;1.000000;1.000000;,
  142;1.000000;1.000000;1.000000;1.000000;,
  143;1.000000;1.000000;1.000000;1.000000;,
  144;1.000000;1.000000;1.000000;1.000000;,
  145;1.000000;1.000000;1.000000;1.000000;,
  146;1.000000;1.000000;1.000000;1.000000;,
  147;1.000000;1.000000;1.000000;1.000000;,
  148;1.000000;1.000000;1.000000;1.000000;,
  149;1.000000;1.000000;1.000000;1.000000;,
  150;1.000000;1.000000;1.000000;1.000000;,
  151;1.000000;1.000000;1.000000;1.000000;,
  152;1.000000;1.000000;1.000000;1.000000;,
  153;1.000000;1.000000;1.000000;1.000000;,
  154;1.000000;1.000000;1.000000;1.000000;,
  155;1.000000;1.000000;1.000000;1.000000;,
  156;1.000000;1.000000;1.000000;1.000000;,
  157;1.000000;1.000000;1.000000;1.000000;,
  158;1.000000;1.000000;1.000000;1.000000;,
  159;1.000000;1.000000;1.000000;1.000000;,
  160;1.000000;1.000000;1.000000;1.000000;,
  161;1.000000;1.000000;1.000000;1.000000;,
  162;1.000000;1.000000;1.000000;1.000000;,
  163;1.000000;1.000000;1.000000;1.000000;,
  164;1.000000;1.000000;1.000000;1.000000;,
  165;1.000000;1.000000;1.000000;1.000000;,
  166;1.000000;1.000000;1.000000;1.000000;,
  167;1.000000;1.000000;1.000000;1.000000;,
  168;1.000000;1.000000;1.000000;1.000000;,
  169;1.000000;1.000000;1.000000;1.000000;,
  170;1.000000;1.000000;1.000000;1.000000;,
  171;1.000000;1.000000;1.000000;1.000000;,
  172;1.000000;1.000000;1.000000;1.000000;,
  173;1.000000;1.000000;1.000000;1.000000;,
  174;1.000000;1.000000;1.000000;1.000000;,
  175;1.000000;1.000000;1.000000;1.000000;,
  176;1.000000;1.000000;1.000000;1.000000;,
  177;1.000000;1.000000;1.000000;1.000000;,
  178;1.000000;1.000000;1.000000;1.000000;,
  179;1.000000;1.000000;1.000000;1.000000;,
  180;1.000000;1.000000;1.000000;1.000000;,
  181;1.000000;1.000000;1.000000;1.000000;,
  182;1.000000;1.000000;1.000000;1.000000;,
  183;1.000000;1.000000;1.000000;1.000000;,
  184;1.000000;1.000000;1.000000;1.000000;,
  185;1.000000;1.000000;1.000000;1.000000;,
  186;1.000000;1.000000;1.000000;1.000000;,
  187;1.000000;1.000000;1.000000;1.000000;,
  188;1.000000;1.000000;1.000000;1.000000;,
  189;1.000000;1.000000;1.000000;1.000000;,
  190;1.000000;1.000000;1.000000;1.000000;,
  191;1.000000;1.000000;1.000000;1.000000;,
  192;1.000000;1.000000;1.000000;1.000000;,
  193;1.000000;1.000000;1.000000;1.000000;,
  194;1.000000;1.000000;1.000000;1.000000;,
  195;1.000000;1.000000;1.000000;1.000000;,
  196;1.000000;1.000000;1.000000;1.000000;,
  197;1.000000;1.000000;1.000000;1.000000;,
  198;1.000000;1.000000;1.000000;1.000000;,
  199;1.000000;1.000000;1.000000;1.000000;,
  200;1.000000;1.000000;1.000000;1.000000;,
  201;1.000000;1.000000;1.000000;1.000000;,
  202;1.000000;1.000000;1.000000;1.000000;,
  203;1.000000;1.000000;1.000000;1.000000;,
  204;1.000000;1.000000;1.000000;1.000000;,
  205;1.000000;1.000000;1.000000;1.000000;,
  206;1.000000;1.000000;1.000000;1.000000;,
  207;1.000000;1.000000;1.000000;1.000000;,
  208;1.000000;1.000000;1.000000;1.000000;,
  209;1.000000;1.000000;1.000000;1.000000;,
  210;1.000000;1.000000;1.000000;1.000000;,
  211;1.000000;1.000000;1.000000;1.000000;,
  212;1.000000;1.000000;1.000000;1.000000;,
  213;1.000000;1.000000;1.000000;1.000000;,
  214;1.000000;1.000000;1.000000;1.000000;,
  215;1.000000;1.000000;1.000000;1.000000;,
  216;1.000000;1.000000;1.000000;1.000000;,
  217;1.000000;1.000000;1.000000;1.000000;,
  218;1.000000;1.000000;1.000000;1.000000;,
  219;1.000000;1.000000;1.000000;1.000000;,
  220;1.000000;1.000000;1.000000;1.000000;,
  221;1.000000;1.000000;1.000000;1.000000;,
  222;1.000000;1.000000;1.000000;1.000000;,
  223;1.000000;1.000000;1.000000;1.000000;,
  224;1.000000;1.000000;1.000000;1.000000;,
  225;1.000000;1.000000;1.000000;1.000000;,
  226;1.000000;1.000000;1.000000;1.000000;,
  227;1.000000;1.000000;1.000000;1.000000;,
  228;1.000000;1.000000;1.000000;1.000000;,
  229;1.000000;1.000000;1.000000;1.000000;,
  230;1.000000;1.000000;1.000000;1.000000;,
  231;1.000000;1.000000;1.000000;1.000000;,
  232;1.000000;1.000000;1.000000;1.000000;,
  233;1.000000;1.000000;1.000000;1.000000;,
  234;1.000000;1.000000;1.000000;1.000000;,
  235;1.000000;1.000000;1.000000;1.000000;,
  236;1.000000;1.000000;1.000000;1.000000;,
  237;1.000000;1.000000;1.000000;1.000000;,
  238;1.000000;1.000000;1.000000;1.000000;,
  239;1.000000;1.000000;1.000000;1.000000;,
  240;1.000000;1.000000;1.000000;1.000000;,
  241;1.000000;1.000000;1.000000;1.000000;,
  242;1.000000;1.000000;1.000000;1.000000;,
  243;1.000000;1.000000;1.000000;1.000000;,
  244;1.000000;1.000000;1.000000;1.000000;,
  245;1.000000;1.000000;1.000000;1.000000;,
  246;1.000000;1.000000;1.000000;1.000000;,
  247;1.000000;1.000000;1.000000;1.000000;,
  248;1.000000;1.000000;1.000000;1.000000;,
  249;1.000000;1.000000;1.000000;1.000000;,
  250;1.000000;1.000000;1.000000;1.000000;,
  251;1.000000;1.000000;1.000000;1.000000;,
  252;1.000000;1.000000;1.000000;1.000000;,
  253;1.000000;1.000000;1.000000;1.000000;;
 }
}
