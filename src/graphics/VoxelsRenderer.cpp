
#include "VoxelsRenderer.h"
#include "mesh.h"
#include "../voxels/chunk.h"
#include "../voxels/voxel.h"

#define VERTEX_SIZE (3 + 2 + 1)  // размер вершины

#define IS_IN(X,Y,Z) ((X) >= 0 && (X) < CHUNK_W && (Y) >= 0 && (Y) < CHUNK_H && (Z) >= 0 && (Z) < CHUNK_D)  // проверка находится ли координаты вокселя за пределами чанка
#define VOXEL(X,Y,Z) (chunk->voxels[((Y) * CHUNK_D + (Z)) * CHUNK_W + (X)])  // взятие вокселя по координатам
#define IS_BLOCKED(X,Y,Z) ((IS_IN(X, Y, Z)) && VOXEL(X, Y, Z).id)  // проверка есть ли такая сторона и заблокирована ли она другим вокселем(отрисовываем только видимые нам грани)

// запись вершинных данных
#define VERTEX(INDEX, X,Y,Z, U,V, L) buffer[INDEX+0] = (X);\
								  buffer[INDEX+1] = (Y);\
								  buffer[INDEX+2] = (Z);\
								  buffer[INDEX+3] = (U);\
								  buffer[INDEX+4] = (V);\
								  buffer[INDEX+5] = (L);\
								  INDEX += VERTEX_SIZE;

int chunk_attrs[] = {3,2,1, 0};

VoxelRenderer::VoxelRenderer(size_t capacity) : capacity(capacity) {
	buffer = new float[capacity * VERTEX_SIZE * 6];  // создание буффера
}

VoxelRenderer::~VoxelRenderer(){
	delete[] buffer;  // удаление буффера
}

Mesh* VoxelRenderer::render(Chunk* chunk){
	size_t index = 0;
//  получение координат вокселя
	for (int y = 0; y < CHUNK_H; y++){
		for (int z = 0; z < CHUNK_D; z++){
			for (int x = 0; x < CHUNK_W; x++){
				voxel vox = chunk->voxels[(y * CHUNK_D + z) * CHUNK_W + x];
				unsigned int id = vox.id;  // получение id вокселя

				if (!id){
					continue;
				}

				float l;
				float uvsize = 1.0f/16.0f;
				float u = (id % 16) * uvsize;
				float v = 1-((1 + id / 16) * uvsize);

//              проверки видимости сторон
				if (!IS_BLOCKED(x,y+1,z)){  // проверка есть ли такая сторона и заблокирована ли она другим вокселем
					l = 1.0f;
//                  генерация треугольников
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, 1,0, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, 1,1, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 0,1, l);

					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, 1,0, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 0,1, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, 0,0, l);
				}
				if (!IS_BLOCKED(x,y-1,z)){  // проверка есть ли такая сторона и заблокирована ли она другим вокселем
					l = 0.3f;
//                  генерация треугольников
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 0,0, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, 1,1, l);
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, 0,1, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 0,0, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, 1,0, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, 1,1, l);
				}

				if (!IS_BLOCKED(x+1,y,z)){  // проверка есть ли такая сторона и заблокирована ли она другим вокселем
					l = 0.75f;
//                  генерация треугольников
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, 1,0, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, 1,1, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 0,1, l);

					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, 1,0, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 0,1, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, 0,0, l);
				}
				if (!IS_BLOCKED(x-1,y,z)){  // проверка есть ли такая сторона и заблокирована ли она другим вокселем
					l = 0.75f;
//                  генерация треугольников
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 0,0, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, 1,1, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, 0,1, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 0,0, l);
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, 1,0, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, 1,1, l);
				}

				if (!IS_BLOCKED(x,y,z+1)){  // проверка есть ли такая сторона и заблокирована ли она другим вокселем
					l = 0.75f;
//                  генерация треугольников
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, 0,0, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 1,1, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, 0,1, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, 0,0, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, 1,0, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 1,1, l);
				}
				if (!IS_BLOCKED(x,y,z-1)){  // проверка есть ли такая сторона и заблокирована ли она другим вокселем
					l = 0.75f;
//                  генерация треугольников
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 1,0, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, 1,1, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, 0,1, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 1,0, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, 0,1, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, 0,0, l);
				}
			}
		}
	}
	return new Mesh(buffer, index / VERTEX_SIZE, chunk_attrs);  // возвращение Mesh
}