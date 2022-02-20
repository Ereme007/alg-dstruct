#pragma once
#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif

	//Дескриптор состоит из Размера, Указатель на след, Указатель на предыд
	typedef struct Descriptor {
		int Size;
		struct Descriptor* Next;
		struct Descriptor* Previous;
	} Descriptor;

	int* End_Descriptor(Descriptor* descriptor);
	// функция - иницилизация памяти
	int Init_Memory(void* ykazat_Memory, int Size);

	// проверка утечки
	void Chek_Memory();

	// выделение памяти Size
	void* Malloc_Memory(int Size);

	// освобождение
	void Free_Malloc(void* ykazat);

	// возращает минимальный размер
	int Return_min_Size_Memory();


	// возращает размер блока
	int Return_Block_Size_Memory();

#ifdef __cplusplus
}
#endif

#endif