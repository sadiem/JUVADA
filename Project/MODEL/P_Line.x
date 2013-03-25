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
 22;
 2.57820;0.65388;-0.19789;,
 2.57820;0.65388;0.19789;,
 1.12434;0.52403;0.19789;,
 1.12434;0.52403;-0.19789;,
 3.98332;1.08961;-0.19789;,
 3.98332;1.08961;0.19789;,
 5.26278;1.80979;-0.19789;,
 5.26278;1.80979;0.19789;,
 6.40275;2.80007;-0.19790;,
 6.40275;2.80007;0.19789;,
 7.52852;4.01997;-0.19789;,
 7.52852;4.01998;0.19789;,
 8.58229;5.40503;-0.19789;,
 8.58229;5.40503;0.19789;,
 9.62221;6.90367;-0.19789;,
 9.62221;6.90367;0.19789;,
 10.59694;8.45015;-0.19789;,
 10.59694;8.45015;0.19789;,
 11.50425;10.04165;-0.19789;,
 11.50425;10.04166;0.19790;,
 12.34208;11.67522;-0.19790;,
 12.34208;11.67522;0.19789;;
 
 20;
 3;2,1,0;,
 3;3,2,0;,
 3;1,5,4;,
 3;0,1,4;,
 3;5,7,6;,
 3;4,5,6;,
 3;7,9,8;,
 3;6,7,8;,
 3;9,11,10;,
 3;8,9,10;,
 3;11,13,12;,
 3;10,11,12;,
 3;13,15,14;,
 3;12,13,14;,
 3;15,17,16;,
 3;14,15,16;,
 3;17,19,18;,
 3;16,17,18;,
 3;19,21,20;,
 3;18,19,20;;
 
 MeshMaterialList {
  1;
  20;
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
   6.000000;
   0.700000;0.700000;0.700000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "LineTex.png";
   }
  }
 }
 MeshNormals {
  21;
  -0.088960;0.996035;0.000000;,
  -0.158825;0.987307;0.000000;,
  -0.362771;0.931878;0.000000;,
  -0.548105;0.836410;0.000000;,
  -0.683088;0.730336;0.000000;,
  -0.755968;0.654608;-0.000011;,
  -0.804596;0.593822;-0.000005;,
  -0.829891;0.557925;0.000000;,
  -0.853753;0.520678;0.000000;,
  -0.875950;0.482402;-0.000009;,
  -0.889795;0.456362;-0.000006;,
  -0.228246;0.973603;0.000000;,
  -0.427870;0.903840;0.000000;,
  -0.603454;0.797398;0.000000;,
  -0.709487;0.704719;-0.000006;,
  -0.776308;0.630354;-0.000011;,
  -0.813173;0.582022;0.000000;,
  -0.838028;0.545627;0.000000;,
  -0.861342;0.508025;-0.000004;,
  -0.882969;0.469431;-0.000009;,
  -0.889794;0.456363;0.000000;;
  20;
  3;0,11,1;,
  3;0,0,1;,
  3;11,12,2;,
  3;1,11,2;,
  3;12,13,3;,
  3;2,12,3;,
  3;13,14,4;,
  3;3,13,4;,
  3;14,15,5;,
  3;4,14,5;,
  3;15,16,6;,
  3;5,15,6;,
  3;16,17,7;,
  3;6,16,7;,
  3;17,18,8;,
  3;7,17,8;,
  3;18,19,9;,
  3;8,18,9;,
  3;19,20,10;,
  3;9,19,10;;
 }
 MeshTextureCoords {
  22;
  0.060570;0.737350;,
  0.315260;0.737350;,
  0.315260;0.625750;,
  0.060570;0.625750;,
  0.060570;0.816910;,
  0.315250;0.816910;,
  0.060570;0.875890;,
  0.315250;0.875890;,
  0.060570;0.915410;,
  0.315250;0.915410;,
  0.060570;0.942360;,
  0.315250;0.942360;,
  0.060570;0.961300;,
  0.315250;0.961300;,
  0.060570;0.971090;,
  0.315250;0.971090;,
  0.060570;0.979730;,
  0.315250;0.979730;,
  0.060570;0.984950;,
  0.315250;0.984950;,
  0.060570;0.991300;,
  0.315250;0.991300;;
 }
 MeshVertexColors {
  22;
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
  21;1.000000;1.000000;1.000000;1.000000;;
 }
}