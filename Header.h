#pragma once
#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif

	//���������� ������� �� �������, ��������� �� ����, ��������� �� ������
	typedef struct Descriptor {
		int Size;
		struct Descriptor* Next;
		struct Descriptor* Previous;
	} Descriptor;

	int* End_Descriptor(Descriptor* descriptor);
	// ������� - ������������ ������
	int Init_Memory(void* ykazat_Memory, int Size);

	// �������� ������
	void Chek_Memory();

	// ��������� ������ Size
	void* Malloc_Memory(int Size);

	// ������������
	void Free_Malloc(void* ykazat);

	// ��������� ����������� ������
	int Return_min_Size_Memory();


	// ��������� ������ �����
	int Return_Block_Size_Memory();

#ifdef __cplusplus
}
#endif

#endif