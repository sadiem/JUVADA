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
 13;
 0.00000;1.87500;0.00000;,
 0.87500;1.00000;-0.00000;,
 0.00000;1.00000;0.87500;,
 0.00000;1.87500;0.00000;,
 -0.00000;1.00000;-0.87500;,
 0.00000;1.87500;0.00000;,
 -0.87500;1.00000;0.00000;,
 0.00000;1.87500;0.00000;,
 0.00000;1.00000;0.87500;,
 0.00000;0.12500;0.00000;,
 0.00000;0.12500;0.00000;,
 0.00000;0.12500;0.00000;,
 0.00000;0.12500;0.00000;;
 
 8;
 3;2,1,0;,
 3;1,4,3;,
 3;4,6,5;,
 3;6,8,7;,
 3;9,1,2;,
 3;10,4,1;,
 3;11,6,4;,
 3;12,8,6;;
 
 MeshMaterialList {
  3;
  8;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   6.000000;
   0.700000;0.700000;0.700000;;
   0.480000;0.480000;0.480000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   6.000000;
   0.700000;0.700000;0.700000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "D:\\å¬êl\\èAêEçÏïi\\JUVADA\\mqo\\player_inner.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  8;
  0.577350;0.577350;0.577350;,
  0.577350;0.577350;-0.577350;,
  -0.577350;0.577350;-0.577350;,
  0.577350;-0.577350;0.577350;,
  -0.577350;0.577350;0.577350;,
  0.577350;-0.577350;-0.577350;,
  -0.577350;-0.577350;-0.577350;,
  -0.577350;-0.577350;0.577350;;
  8;
  3;0,0,0;,
  3;1,1,1;,
  3;2,2,2;,
  3;4,4,4;,
  3;3,3,3;,
  3;5,5,5;,
  3;6,6,6;,
  3;7,7,7;;
 }
 MeshTextureCoords {
  13;
  0.125000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.375000;0.000000;,
  0.500000;0.500000;,
  0.625000;0.000000;,
  0.750000;0.500000;,
  0.875000;0.000000;,
  1.000000;0.500000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
 MeshVertexColors {
  13;
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
  12;1.000000;1.000000;1.000000;1.000000;;
 }
}
