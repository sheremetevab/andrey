#ifndef VOXELS_CHUNK_H_
#define VOXELS_CHUNK_H_

// объем чанков
#define CHUNK_W 16 
#define CHUNK_H 16
#define CHUNK_D 16
#define CHUNK_VOL (CHUNK_W * CHUNK_H * CHUNK_D)

class voxel;

class Chunk {
public:
    voxel* voxels;  // массив вокселей
    Chunk();  // создание чанка
    ~Chunk();  // удаление чанка
};

#endif
