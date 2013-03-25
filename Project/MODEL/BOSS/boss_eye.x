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
 181;
 0.00000;6.89400;0.00000;,
 1.31911;6.36922;2.28477;,
 0.00000;6.36922;2.63822;,
 2.28477;6.36922;1.31911;,
 2.63822;6.36922;0.00000;,
 2.28477;6.36922;-1.31911;,
 1.31911;6.36922;-2.28477;,
 0.00000;6.36922;-2.63822;,
 -1.31911;6.36922;-2.28477;,
 -2.28476;6.36922;-1.31911;,
 -2.63822;6.36922;0.00000;,
 -2.28477;6.36922;1.31911;,
 -1.31911;6.36922;2.28476;,
 0.00000;-6.36922;2.63822;,
 1.31911;-6.36922;2.28477;,
 0.00000;-6.89400;0.00000;,
 2.28477;-6.36922;1.31911;,
 2.63822;-6.36922;-0.00000;,
 2.28477;-6.36922;-1.31911;,
 1.31911;-6.36922;-2.28477;,
 0.00000;-6.36922;-2.63822;,
 -1.31911;-6.36922;-2.28477;,
 -2.28476;-6.36922;-1.31911;,
 -2.63822;-6.36922;0.00000;,
 -2.28477;-6.36922;1.31911;,
 -1.31911;-6.36922;2.28476;,
 2.43740;4.87479;4.22170;,
 0.00000;4.87479;4.87479;,
 4.22170;4.87479;2.43740;,
 4.87479;4.87479;0.00000;,
 4.22170;4.87479;-2.43740;,
 2.43740;4.87479;-4.22170;,
 0.00000;4.87479;-4.87479;,
 -2.43740;4.87479;-4.22170;,
 -4.22169;4.87479;-2.43740;,
 -4.87479;4.87479;0.00000;,
 -4.22170;4.87479;2.43739;,
 -2.43740;4.87479;4.22169;,
 2.43740;4.87479;4.22170;,
 3.18461;2.63822;5.51591;,
 0.00000;2.63822;6.36922;,
 0.00000;4.87479;4.87479;,
 4.22170;4.87479;2.43740;,
 5.51591;2.63822;3.18461;,
 3.18461;2.63822;5.51591;,
 2.43740;4.87479;4.22170;,
 4.87479;4.87479;0.00000;,
 6.36922;2.63822;0.00000;,
 4.22170;4.87479;-2.43740;,
 5.51591;2.63822;-3.18461;,
 2.43740;4.87479;-4.22170;,
 3.18461;2.63822;-5.51591;,
 0.00000;4.87479;-4.87479;,
 0.00000;2.63822;-6.36922;,
 3.18461;2.63822;-5.51591;,
 2.43740;4.87479;-4.22170;,
 -2.43740;4.87479;-4.22170;,
 -3.18461;2.63822;-5.51591;,
 -4.22169;4.87479;-2.43740;,
 -5.51591;2.63822;-3.18461;,
 -3.18461;2.63822;-5.51591;,
 -2.43740;4.87479;-4.22170;,
 -4.87479;4.87479;0.00000;,
 -6.36922;2.63822;0.00000;,
 -4.22170;4.87479;2.43739;,
 -5.51591;2.63822;3.18461;,
 -2.43740;4.87479;4.22169;,
 -3.18462;2.63822;5.51591;,
 -3.18462;2.63822;5.51591;,
 -2.43740;4.87479;4.22169;,
 3.44700;0.00000;5.97038;,
 0.00000;0.00000;6.89400;,
 5.97038;0.00000;3.44700;,
 3.44700;0.00000;5.97038;,
 6.89400;-0.00000;-0.00000;,
 5.97038;-0.00000;-3.44700;,
 3.44700;-0.00000;-5.97038;,
 0.00000;-0.00000;-6.89400;,
 3.44700;-0.00000;-5.97038;,
 -3.44700;0.00000;-5.97038;,
 -5.97038;0.00000;-3.44700;,
 -3.44700;0.00000;-5.97038;,
 -6.89400;0.00000;0.00000;,
 -5.97038;0.00000;3.44700;,
 -3.44700;0.00000;5.97038;,
 -3.44700;0.00000;5.97038;,
 3.18461;-2.63822;5.51591;,
 0.00000;-2.63822;6.36922;,
 5.51591;-2.63822;3.18461;,
 3.18461;-2.63822;5.51591;,
 6.36922;-2.63822;-0.00000;,
 5.51591;-2.63822;-3.18461;,
 3.18461;-2.63822;-5.51591;,
 0.00000;-2.63822;-6.36922;,
 3.18461;-2.63822;-5.51591;,
 -3.18461;-2.63822;-5.51591;,
 -5.51591;-2.63822;-3.18461;,
 -3.18461;-2.63822;-5.51591;,
 -6.36922;-2.63822;0.00000;,
 -5.51591;-2.63822;3.18461;,
 -3.18462;-2.63822;5.51591;,
 -3.18462;-2.63822;5.51591;,
 2.43740;-4.87479;4.22170;,
 0.00000;-4.87479;4.87479;,
 4.22170;-4.87479;2.43740;,
 2.43740;-4.87479;4.22170;,
 4.87479;-4.87479;-0.00000;,
 4.22170;-4.87479;-2.43740;,
 2.43740;-4.87479;-4.22170;,
 0.00000;-4.87479;-4.87479;,
 2.43740;-4.87479;-4.22170;,
 -2.43740;-4.87479;-4.22170;,
 -4.22169;-4.87479;-2.43740;,
 -2.43740;-4.87479;-4.22170;,
 -4.87479;-4.87479;0.00000;,
 -4.22170;-4.87479;2.43739;,
 -2.43740;-4.87479;4.22169;,
 -2.43740;-4.87479;4.22169;,
 2.43740;-4.87479;4.22170;,
 0.00000;-4.87479;4.87479;,
 4.22170;-4.87479;2.43740;,
 4.87479;-4.87479;-0.00000;,
 4.22170;-4.87479;-2.43740;,
 2.43740;-4.87479;-4.22170;,
 0.00000;-4.87479;-4.87479;,
 -2.43740;-4.87479;-4.22170;,
 -4.22169;-4.87479;-2.43740;,
 -4.87479;-4.87479;0.00000;,
 -4.22170;-4.87479;2.43739;,
 -2.43740;-4.87479;4.22169;,
 0.00000;1.35000;6.13827;,
 0.25831;1.24724;6.58568;,
 0.00000;1.24724;6.65489;,
 0.44741;1.24724;6.39658;,
 0.51662;1.24724;6.13827;,
 -0.44741;1.24724;6.39658;,
 -0.51662;1.24724;6.13827;,
 -0.25831;1.24724;6.58568;,
 0.00000;-1.24724;6.65489;,
 0.25831;-1.24724;6.58568;,
 0.00000;-1.35000;6.13827;,
 0.44741;-1.24724;6.39658;,
 0.51662;-1.24724;6.13827;,
 -0.51662;-1.24724;6.13827;,
 -0.44741;-1.24724;6.39658;,
 -0.25831;-1.24724;6.58568;,
 0.47730;0.95459;6.96497;,
 0.00000;0.95459;7.09286;,
 0.82670;0.95459;6.61557;,
 0.95459;0.95459;6.13827;,
 -0.82670;0.95459;6.61557;,
 -0.95459;0.95459;6.13827;,
 -0.47730;0.95459;6.96497;,
 0.62362;0.51662;7.21841;,
 0.00000;0.51662;7.38551;,
 1.08014;0.51662;6.76189;,
 1.24724;0.51662;6.13827;,
 -1.08014;0.51662;6.76189;,
 -1.24724;0.51662;6.13827;,
 -0.62362;0.51662;7.21841;,
 0.67500;0.00000;7.30740;,
 0.00000;0.00000;7.48827;,
 1.16913;0.00000;6.81327;,
 1.35000;0.00000;6.13827;,
 -1.16913;0.00000;6.81327;,
 -1.35000;0.00000;6.13827;,
 -0.67500;0.00000;7.30740;,
 0.62362;-0.51662;7.21841;,
 0.00000;-0.51662;7.38551;,
 1.08014;-0.51662;6.76189;,
 1.24724;-0.51662;6.13827;,
 -1.08014;-0.51662;6.76189;,
 -1.24724;-0.51662;6.13827;,
 -0.62362;-0.51662;7.21841;,
 0.47730;-0.95459;6.96497;,
 0.00000;-0.95459;7.09286;,
 0.82670;-0.95459;6.61557;,
 0.95459;-0.95459;6.13827;,
 -0.82670;-0.95459;6.61557;,
 -0.95459;-0.95459;6.13827;,
 -0.47730;-0.95459;6.96497;;
 
 252;
 3;2,1,0;,
 3;1,3,0;,
 3;3,4,0;,
 3;4,5,0;,
 3;5,6,0;,
 3;6,7,0;,
 3;7,8,0;,
 3;8,9,0;,
 3;9,10,0;,
 3;10,11,0;,
 3;11,12,0;,
 3;12,2,0;,
 3;15,14,13;,
 3;15,16,14;,
 3;15,17,16;,
 3;15,18,17;,
 3;15,19,18;,
 3;15,20,19;,
 3;15,21,20;,
 3;15,22,21;,
 3;15,23,22;,
 3;15,24,23;,
 3;15,25,24;,
 3;15,13,25;,
 3;27,26,1;,
 3;2,27,1;,
 3;26,28,3;,
 3;1,26,3;,
 3;28,29,4;,
 3;3,28,4;,
 3;29,30,5;,
 3;4,29,5;,
 3;30,31,6;,
 3;5,30,6;,
 3;31,32,7;,
 3;6,31,7;,
 3;32,33,8;,
 3;7,32,8;,
 3;33,34,9;,
 3;8,33,9;,
 3;34,35,10;,
 3;9,34,10;,
 3;35,36,11;,
 3;10,35,11;,
 3;36,37,12;,
 3;11,36,12;,
 3;37,27,2;,
 3;12,37,2;,
 3;40,39,38;,
 3;41,40,38;,
 3;44,43,42;,
 3;45,44,42;,
 3;43,47,46;,
 3;42,43,46;,
 3;47,49,48;,
 3;46,47,48;,
 3;49,51,50;,
 3;48,49,50;,
 3;54,53,52;,
 3;55,54,52;,
 3;53,57,56;,
 3;52,53,56;,
 3;60,59,58;,
 3;61,60,58;,
 3;59,63,62;,
 3;58,59,62;,
 3;63,65,64;,
 3;62,63,64;,
 3;65,67,66;,
 3;64,65,66;,
 3;68,40,41;,
 3;69,68,41;,
 3;71,70,39;,
 3;40,71,39;,
 3;73,72,43;,
 3;44,73,43;,
 3;72,74,47;,
 3;43,72,47;,
 3;74,75,49;,
 3;47,74,49;,
 3;75,76,51;,
 3;49,75,51;,
 3;78,77,53;,
 3;54,78,53;,
 3;77,79,57;,
 3;53,77,57;,
 3;81,80,59;,
 3;60,81,59;,
 3;80,82,63;,
 3;59,80,63;,
 3;82,83,65;,
 3;63,82,65;,
 3;83,84,67;,
 3;65,83,67;,
 3;85,71,40;,
 3;68,85,40;,
 3;87,86,70;,
 3;71,87,70;,
 3;89,88,72;,
 3;73,89,72;,
 3;88,90,74;,
 3;72,88,74;,
 3;90,91,75;,
 3;74,90,75;,
 3;91,92,76;,
 3;75,91,76;,
 3;94,93,77;,
 3;78,94,77;,
 3;93,95,79;,
 3;77,93,79;,
 3;97,96,80;,
 3;81,97,80;,
 3;96,98,82;,
 3;80,96,82;,
 3;98,99,83;,
 3;82,98,83;,
 3;99,100,84;,
 3;83,99,84;,
 3;101,87,71;,
 3;85,101,71;,
 3;103,102,86;,
 3;87,103,86;,
 3;105,104,88;,
 3;89,105,88;,
 3;104,106,90;,
 3;88,104,90;,
 3;106,107,91;,
 3;90,106,91;,
 3;107,108,92;,
 3;91,107,92;,
 3;110,109,93;,
 3;94,110,93;,
 3;109,111,95;,
 3;93,109,95;,
 3;113,112,96;,
 3;97,113,96;,
 3;112,114,98;,
 3;96,112,98;,
 3;114,115,99;,
 3;98,114,99;,
 3;115,116,100;,
 3;99,115,100;,
 3;117,103,87;,
 3;101,117,87;,
 3;13,14,118;,
 3;119,13,118;,
 3;14,16,120;,
 3;118,14,120;,
 3;16,17,121;,
 3;120,16,121;,
 3;17,18,122;,
 3;121,17,122;,
 3;18,19,123;,
 3;122,18,123;,
 3;19,20,124;,
 3;123,19,124;,
 3;20,21,125;,
 3;124,20,125;,
 3;21,22,126;,
 3;125,21,126;,
 3;22,23,127;,
 3;126,22,127;,
 3;23,24,128;,
 3;127,23,128;,
 3;24,25,129;,
 3;128,24,129;,
 3;25,13,119;,
 3;129,25,119;,
 3;132,131,130;,
 3;131,133,130;,
 3;133,134,130;,
 3;136,135,130;,
 3;135,137,130;,
 3;137,132,130;,
 3;140,139,138;,
 3;140,141,139;,
 3;140,142,141;,
 3;140,144,143;,
 3;140,145,144;,
 3;140,138,145;,
 3;147,146,131;,
 3;132,147,131;,
 3;146,148,133;,
 3;131,146,133;,
 3;148,149,134;,
 3;133,148,134;,
 3;151,150,135;,
 3;136,151,135;,
 3;150,152,137;,
 3;135,150,137;,
 3;152,147,132;,
 3;137,152,132;,
 3;154,153,146;,
 3;147,154,146;,
 3;153,155,148;,
 3;146,153,148;,
 3;155,156,149;,
 3;148,155,149;,
 3;158,157,150;,
 3;151,158,150;,
 3;157,159,152;,
 3;150,157,152;,
 3;159,154,147;,
 3;152,159,147;,
 3;161,160,153;,
 3;154,161,153;,
 3;160,162,155;,
 3;153,160,155;,
 3;162,163,156;,
 3;155,162,156;,
 3;165,164,157;,
 3;158,165,157;,
 3;164,166,159;,
 3;157,164,159;,
 3;166,161,154;,
 3;159,166,154;,
 3;168,167,160;,
 3;161,168,160;,
 3;167,169,162;,
 3;160,167,162;,
 3;169,170,163;,
 3;162,169,163;,
 3;172,171,164;,
 3;165,172,164;,
 3;171,173,166;,
 3;164,171,166;,
 3;173,168,161;,
 3;166,173,161;,
 3;175,174,167;,
 3;168,175,167;,
 3;174,176,169;,
 3;167,174,169;,
 3;176,177,170;,
 3;169,176,170;,
 3;179,178,171;,
 3;172,179,171;,
 3;178,180,173;,
 3;171,178,173;,
 3;180,175,168;,
 3;173,180,168;,
 3;138,139,174;,
 3;175,138,174;,
 3;139,141,176;,
 3;174,139,176;,
 3;141,142,177;,
 3;176,141,177;,
 3;143,144,178;,
 3;179,143,178;,
 3;144,145,180;,
 3;178,144,180;,
 3;138,175,180;,
 3;145,138,180;;
 
 MeshMaterialList {
  3;
  252;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   6.000000;
   0.700000;0.700000;0.700000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "boss_armor_bump.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   6.000000;
   0.700000;0.700000;0.700000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\nhs00469\\Desktop\\medama.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   11.000000;
   0.990000;0.990000;0.990000;;
   1.000000;1.000000;1.000000;;
   TextureFilename {
    "C:\\Users\\nhs00469\\Desktop\\medama.jpg";
   }
  }
 }
 MeshNormals {
  137;
  -0.000000;1.000000;0.000000;,
  -0.030204;0.907906;0.418085;,
  0.182885;0.907906;0.377174;,
  0.346970;0.907906;0.235198;,
  0.418085;0.907906;0.030203;,
  0.377174;0.907906;-0.182885;,
  0.235198;0.907906;-0.346970;,
  0.030203;0.907906;-0.418085;,
  -0.182885;0.907906;-0.377173;,
  -0.346971;0.907906;-0.235198;,
  -0.418085;0.907906;-0.030204;,
  -0.377173;0.907906;0.182886;,
  -0.235199;0.907906;0.346971;,
  -0.012144;0.707987;0.706121;,
  0.342544;0.707987;0.617591;,
  0.605449;0.707986;0.363576;,
  0.706122;0.707986;0.012143;,
  0.617591;0.707987;-0.342544;,
  0.363576;0.707986;-0.605449;,
  0.012143;0.707986;-0.706122;,
  -0.342545;0.707987;-0.617590;,
  -0.605448;0.707987;-0.363576;,
  -0.706121;0.707987;-0.012144;,
  -0.617591;0.707987;0.342544;,
  -0.363577;0.707987;0.605447;,
  -0.006421;0.383519;0.923511;,
  0.456195;0.383518;0.802994;,
  0.796574;0.383518;0.467315;,
  0.923511;0.383519;0.006421;,
  0.802994;0.383518;-0.456195;,
  0.467315;0.383518;-0.796574;,
  0.006421;0.383519;-0.923511;,
  -0.456195;0.383518;-0.802994;,
  -0.796574;0.383519;-0.467315;,
  -0.923511;0.383519;-0.006421;,
  -0.802994;0.383519;0.456194;,
  -0.467316;0.383519;0.796573;,
  0.000000;0.000000;1.000000;,
  0.500000;-0.000000;0.866026;,
  0.866026;0.000000;0.500000;,
  1.000000;-0.000000;0.000000;,
  0.866026;-0.000000;-0.500000;,
  0.500000;0.000000;-0.866026;,
  0.000000;-0.000000;-1.000000;,
  -0.500000;-0.000000;-0.866026;,
  -0.866026;0.000000;-0.500000;,
  -1.000000;-0.000000;0.000000;,
  -0.866026;-0.000001;0.500000;,
  -0.500000;0.000000;0.866025;,
  0.006421;-0.383519;0.923511;,
  0.467315;-0.383518;0.796574;,
  0.802994;-0.383518;0.456195;,
  0.923511;-0.383519;-0.006421;,
  0.796574;-0.383518;-0.467315;,
  0.456195;-0.383518;-0.802994;,
  -0.006421;-0.383519;-0.923511;,
  -0.467315;-0.383518;-0.796574;,
  -0.802994;-0.383519;-0.456195;,
  -0.923511;-0.383519;0.006420;,
  -0.796575;-0.383518;0.467314;,
  -0.456195;-0.383519;0.802994;,
  0.012141;-0.707986;0.706122;,
  0.363576;-0.707986;0.605449;,
  0.617591;-0.707987;0.342544;,
  0.706122;-0.707986;-0.012143;,
  0.605449;-0.707986;-0.363576;,
  0.342544;-0.707987;-0.617591;,
  -0.012143;-0.707986;-0.706122;,
  -0.363576;-0.707987;-0.605448;,
  -0.617591;-0.707987;-0.342543;,
  -0.706122;-0.707987;0.012142;,
  -0.605448;-0.707987;0.363575;,
  -0.342544;-0.707987;0.617590;,
  0.030201;-0.907906;0.418085;,
  0.235198;-0.907906;0.346970;,
  0.377173;-0.907906;0.182885;,
  0.418085;-0.907906;-0.030203;,
  0.346970;-0.907906;-0.235198;,
  0.182885;-0.907906;-0.377173;,
  -0.030203;-0.907906;-0.418085;,
  -0.235199;-0.907906;-0.346970;,
  -0.377174;-0.907906;-0.182886;,
  -0.418085;-0.907906;0.030202;,
  -0.346970;-0.907906;0.235199;,
  -0.182886;-0.907906;0.377174;,
  -0.000000;-1.000000;0.000000;,
  -0.000000;0.991322;0.131454;,
  -0.030203;0.907903;0.418090;,
  0.182884;0.907904;0.377178;,
  0.346974;0.907904;0.235199;,
  0.439145;0.890678;0.117664;,
  -0.379823;0.919444;0.101768;,
  -0.377178;0.907904;0.182885;,
  -0.235199;0.907904;0.346975;,
  -0.012144;0.707986;0.706122;,
  0.342545;0.707985;0.617592;,
  0.605451;0.707984;0.363576;,
  0.736775;0.646675;0.197417;,
  -0.647914;0.741667;0.173603;,
  -0.617592;0.707985;0.342546;,
  -0.363575;0.707984;0.605452;,
  -0.006422;0.383521;0.923510;,
  0.456197;0.383517;0.802994;,
  0.796574;0.383518;0.467316;,
  0.917830;0.311614;0.245936;,
  -0.871406;0.431430;0.233493;,
  -0.802994;0.383517;0.456197;,
  -0.467316;0.383518;0.796574;,
  0.000000;0.000000;1.000000;,
  0.500002;-0.000000;0.866024;,
  0.866024;0.000001;0.500002;,
  0.963950;-0.063911;0.258295;,
  -0.963950;0.063911;0.258295;,
  -0.866024;-0.000001;0.500002;,
  -0.500002;0.000000;0.866024;,
  0.006422;-0.383521;0.923510;,
  0.467316;-0.383518;0.796574;,
  0.802994;-0.383517;0.456197;,
  0.871406;-0.431430;0.233493;,
  -0.917830;-0.311614;0.245936;,
  -0.796574;-0.383518;0.467316;,
  -0.456197;-0.383517;0.802994;,
  0.045111;-0.678679;0.733049;,
  0.363575;-0.707984;0.605452;,
  0.617592;-0.707985;0.342546;,
  0.647914;-0.741667;0.173603;,
  -0.736775;-0.646675;0.197417;,
  -0.605451;-0.707984;0.363576;,
  -0.314858;-0.727413;0.609701;,
  0.000000;-0.896908;0.442217;,
  0.235199;-0.907904;0.346975;,
  0.377178;-0.907904;0.182885;,
  0.379823;-0.919444;0.101768;,
  -0.439145;-0.890678;0.117664;,
  -0.346974;-0.907904;0.235199;,
  -0.190900;-0.924243;0.330654;,
  -0.000000;-0.991322;0.131454;;
  252;
  3;1,2,0;,
  3;2,3,0;,
  3;3,4,0;,
  3;4,5,0;,
  3;5,6,0;,
  3;6,7,0;,
  3;7,8,0;,
  3;8,9,0;,
  3;9,10,0;,
  3;10,11,0;,
  3;11,12,0;,
  3;12,1,0;,
  3;85,74,73;,
  3;85,75,74;,
  3;85,76,75;,
  3;85,77,76;,
  3;85,78,77;,
  3;85,79,78;,
  3;85,80,79;,
  3;85,81,80;,
  3;85,82,81;,
  3;85,83,82;,
  3;85,84,83;,
  3;85,73,84;,
  3;13,14,2;,
  3;1,13,2;,
  3;14,15,3;,
  3;2,14,3;,
  3;15,16,4;,
  3;3,15,4;,
  3;16,17,5;,
  3;4,16,5;,
  3;17,18,6;,
  3;5,17,6;,
  3;18,19,7;,
  3;6,18,7;,
  3;19,20,8;,
  3;7,19,8;,
  3;20,21,9;,
  3;8,20,9;,
  3;21,22,10;,
  3;9,21,10;,
  3;22,23,11;,
  3;10,22,11;,
  3;23,24,12;,
  3;11,23,12;,
  3;24,13,1;,
  3;12,24,1;,
  3;25,26,14;,
  3;13,25,14;,
  3;26,27,15;,
  3;14,26,15;,
  3;27,28,16;,
  3;15,27,16;,
  3;28,29,17;,
  3;16,28,17;,
  3;29,30,18;,
  3;17,29,18;,
  3;30,31,19;,
  3;18,30,19;,
  3;31,32,20;,
  3;19,31,20;,
  3;32,33,21;,
  3;20,32,21;,
  3;33,34,22;,
  3;21,33,22;,
  3;34,35,23;,
  3;22,34,23;,
  3;35,36,24;,
  3;23,35,24;,
  3;36,25,13;,
  3;24,36,13;,
  3;37,38,26;,
  3;25,37,26;,
  3;38,39,27;,
  3;26,38,27;,
  3;39,40,28;,
  3;27,39,28;,
  3;40,41,29;,
  3;28,40,29;,
  3;41,42,30;,
  3;29,41,30;,
  3;42,43,31;,
  3;30,42,31;,
  3;43,44,32;,
  3;31,43,32;,
  3;44,45,33;,
  3;32,44,33;,
  3;45,46,34;,
  3;33,45,34;,
  3;46,47,35;,
  3;34,46,35;,
  3;47,48,36;,
  3;35,47,36;,
  3;48,37,25;,
  3;36,48,25;,
  3;49,50,38;,
  3;37,49,38;,
  3;50,51,39;,
  3;38,50,39;,
  3;51,52,40;,
  3;39,51,40;,
  3;52,53,41;,
  3;40,52,41;,
  3;53,54,42;,
  3;41,53,42;,
  3;54,55,43;,
  3;42,54,43;,
  3;55,56,44;,
  3;43,55,44;,
  3;56,57,45;,
  3;44,56,45;,
  3;57,58,46;,
  3;45,57,46;,
  3;58,59,47;,
  3;46,58,47;,
  3;59,60,48;,
  3;47,59,48;,
  3;60,49,37;,
  3;48,60,37;,
  3;61,62,50;,
  3;49,61,50;,
  3;62,63,51;,
  3;50,62,51;,
  3;63,64,52;,
  3;51,63,52;,
  3;64,65,53;,
  3;52,64,53;,
  3;65,66,54;,
  3;53,65,54;,
  3;66,67,55;,
  3;54,66,55;,
  3;67,68,56;,
  3;55,67,56;,
  3;68,69,57;,
  3;56,68,57;,
  3;69,70,58;,
  3;57,69,58;,
  3;70,71,59;,
  3;58,70,59;,
  3;71,72,60;,
  3;59,71,60;,
  3;72,61,49;,
  3;60,72,49;,
  3;73,74,62;,
  3;61,73,62;,
  3;74,75,63;,
  3;62,74,63;,
  3;75,76,64;,
  3;63,75,64;,
  3;76,77,65;,
  3;64,76,65;,
  3;77,78,66;,
  3;65,77,66;,
  3;78,79,67;,
  3;66,78,67;,
  3;79,80,68;,
  3;67,79,68;,
  3;80,81,69;,
  3;68,80,69;,
  3;81,82,70;,
  3;69,81,70;,
  3;82,83,71;,
  3;70,82,71;,
  3;83,84,72;,
  3;71,83,72;,
  3;84,73,61;,
  3;72,84,61;,
  3;87,88,86;,
  3;88,89,86;,
  3;89,90,86;,
  3;91,92,86;,
  3;92,93,86;,
  3;93,87,86;,
  3;136,130,129;,
  3;136,131,130;,
  3;136,132,131;,
  3;136,134,133;,
  3;136,135,134;,
  3;136,129,135;,
  3;94,95,88;,
  3;87,94,88;,
  3;95,96,89;,
  3;88,95,89;,
  3;96,97,90;,
  3;89,96,90;,
  3;98,99,92;,
  3;91,98,92;,
  3;99,100,93;,
  3;92,99,93;,
  3;100,94,87;,
  3;93,100,87;,
  3;101,102,95;,
  3;94,101,95;,
  3;102,103,96;,
  3;95,102,96;,
  3;103,104,97;,
  3;96,103,97;,
  3;105,106,99;,
  3;98,105,99;,
  3;106,107,100;,
  3;99,106,100;,
  3;107,101,94;,
  3;100,107,94;,
  3;108,109,102;,
  3;101,108,102;,
  3;109,110,103;,
  3;102,109,103;,
  3;110,111,104;,
  3;103,110,104;,
  3;112,113,106;,
  3;105,112,106;,
  3;113,114,107;,
  3;106,113,107;,
  3;114,108,101;,
  3;107,114,101;,
  3;115,116,109;,
  3;108,115,109;,
  3;116,117,110;,
  3;109,116,110;,
  3;117,118,111;,
  3;110,117,111;,
  3;119,120,113;,
  3;112,119,113;,
  3;120,121,114;,
  3;113,120,114;,
  3;121,115,108;,
  3;114,121,108;,
  3;122,123,116;,
  3;115,122,116;,
  3;123,124,117;,
  3;116,123,117;,
  3;124,125,118;,
  3;117,124,118;,
  3;126,127,120;,
  3;119,126,120;,
  3;127,128,121;,
  3;120,127,121;,
  3;128,122,115;,
  3;121,128,115;,
  3;129,130,123;,
  3;122,129,123;,
  3;130,131,124;,
  3;123,130,124;,
  3;131,132,125;,
  3;124,131,125;,
  3;133,134,127;,
  3;126,133,127;,
  3;134,135,128;,
  3;127,134,128;,
  3;129,122,128;,
  3;135,129,128;;
 }
 MeshTextureCoords {
  181;
  0.072210;0.095230;,
  0.075960;0.105750;,
  0.072210;0.107380;,
  0.078710;0.101300;,
  0.079710;0.095230;,
  0.078710;0.089160;,
  0.075960;0.084710;,
  0.072210;0.083080;,
  0.068460;0.084710;,
  0.065720;0.089160;,
  0.064720;0.095230;,
  0.065720;0.101300;,
  0.068460;0.105750;,
  0.072210;0.130520;,
  0.075960;0.132140;,
  0.072210;0.142660;,
  0.078710;0.136590;,
  0.079710;0.142660;,
  0.078710;0.148740;,
  0.075960;0.153180;,
  0.072210;0.154810;,
  0.068460;0.153180;,
  0.065720;0.148740;,
  0.064720;0.142660;,
  0.065720;0.136590;,
  0.068460;0.132140;,
  0.079140;0.114670;,
  0.072210;0.117680;,
  0.084210;0.106450;,
  0.086070;0.095230;,
  0.084210;0.084010;,
  0.079140;0.075790;,
  0.072210;0.072780;,
  0.065290;0.075790;,
  0.060220;0.084010;,
  0.058360;0.095230;,
  0.060220;0.106450;,
  0.065290;0.114670;,
  0.104360;0.072780;,
  0.106480;0.083080;,
  0.097430;0.083080;,
  0.097430;0.072780;,
  0.032900;0.072780;,
  0.030770;0.083080;,
  0.024150;0.083080;,
  0.027830;0.072780;,
  0.039820;0.072780;,
  0.039820;0.083080;,
  0.046750;0.072780;,
  0.048880;0.083080;,
  0.051820;0.072780;,
  0.055500;0.083080;,
  0.097430;0.120220;,
  0.097430;0.130520;,
  0.088380;0.130520;,
  0.090500;0.120220;,
  0.104360;0.120220;,
  0.106480;0.130520;,
  0.032900;0.120220;,
  0.030770;0.130520;,
  0.024150;0.130520;,
  0.027830;0.120220;,
  0.039820;0.120220;,
  0.039820;0.130520;,
  0.046750;0.120220;,
  0.048880;0.130520;,
  0.051820;0.120220;,
  0.055500;0.130520;,
  0.088380;0.083080;,
  0.090500;0.072780;,
  0.107230;0.095230;,
  0.097430;0.095230;,
  0.030030;0.095230;,
  0.022860;0.095230;,
  0.039820;0.095230;,
  0.049620;0.095230;,
  0.056790;0.095230;,
  0.097430;0.142660;,
  0.087630;0.142660;,
  0.107230;0.142660;,
  0.030030;0.142660;,
  0.022860;0.142660;,
  0.039820;0.142660;,
  0.049620;0.142660;,
  0.056790;0.142660;,
  0.087630;0.095230;,
  0.106480;0.107380;,
  0.097430;0.107380;,
  0.030770;0.107380;,
  0.024150;0.107380;,
  0.039820;0.107380;,
  0.048880;0.107380;,
  0.055500;0.107380;,
  0.097430;0.154810;,
  0.088380;0.154810;,
  0.106480;0.154810;,
  0.030770;0.154810;,
  0.024150;0.154810;,
  0.039820;0.154810;,
  0.048880;0.154810;,
  0.055500;0.154810;,
  0.088380;0.107380;,
  0.104360;0.117680;,
  0.097430;0.117680;,
  0.032900;0.117680;,
  0.027830;0.117680;,
  0.039820;0.117680;,
  0.046750;0.117680;,
  0.051820;0.117680;,
  0.097430;0.165110;,
  0.090500;0.165110;,
  0.104360;0.165110;,
  0.032900;0.165110;,
  0.027830;0.165110;,
  0.039820;0.165110;,
  0.046750;0.165110;,
  0.051820;0.165110;,
  0.090500;0.117680;,
  0.079140;0.123220;,
  0.072210;0.120220;,
  0.084210;0.131440;,
  0.086070;0.142660;,
  0.084210;0.153890;,
  0.079140;0.162100;,
  0.072210;0.165110;,
  0.065290;0.162100;,
  0.060220;0.153890;,
  0.058360;0.142660;,
  0.060220;0.131440;,
  0.065290;0.123220;,
  0.498800;0.062150;,
  0.583320;0.095770;,
  0.498800;0.095770;,
  0.645190;0.095770;,
  0.667840;0.095770;,
  0.352410;0.095770;,
  0.329760;0.095770;,
  0.414280;0.095770;,
  0.498800;0.911960;,
  0.583320;0.911960;,
  0.498800;0.945590;,
  0.645190;0.911960;,
  0.667840;0.911960;,
  0.329760;0.911960;,
  0.352410;0.911960;,
  0.414280;0.911960;,
  0.654970;0.191520;,
  0.498800;0.191520;,
  0.769300;0.191520;,
  0.811140;0.191520;,
  0.228300;0.191520;,
  0.186460;0.191520;,
  0.342630;0.191520;,
  0.702850;0.334830;,
  0.498800;0.334830;,
  0.852220;0.334830;,
  0.906900;0.334830;,
  0.145380;0.334830;,
  0.090700;0.334830;,
  0.294750;0.334830;,
  0.719660;0.503870;,
  0.498800;0.503870;,
  0.881340;0.503870;,
  0.940520;0.503870;,
  0.116260;0.503870;,
  0.057080;0.503870;,
  0.277940;0.503870;,
  0.702850;0.672900;,
  0.498800;0.672900;,
  0.852220;0.672900;,
  0.906900;0.672900;,
  0.145380;0.672900;,
  0.090700;0.672900;,
  0.294750;0.672900;,
  0.654970;0.816210;,
  0.498800;0.816210;,
  0.769300;0.816210;,
  0.811140;0.816210;,
  0.228300;0.816210;,
  0.186460;0.816210;,
  0.342630;0.816210;;
 }
 MeshVertexColors {
  181;
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
  180;1.000000;1.000000;1.000000;1.000000;;
 }
}