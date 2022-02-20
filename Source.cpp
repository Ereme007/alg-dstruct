#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Header.h"


void* Start_Memory = NULL;
int Size_Memory = 0;
Descriptor* Head_ykaz = NULL;
Descriptor* Curret_ykaz = NULL;

int Return_min_Size_Memory() {
    return sizeof(Descriptor) + sizeof(int);
}

int Return_Block_Size_Memory() {
    return sizeof(Descriptor) + sizeof(int);
}

int* End_Descriptor(Descriptor* descriptor) {
    return (int*)((char*)descriptor + (descriptor->Size) - sizeof(int));
}

int Init_Memory(void* ykazat_Memory, int Size) {
    if (Size <= Return_min_Size_Memory())
    {
        return 0;
    }


    Start_Memory = (void*)ykazat_Memory;
    Head_ykaz = (Descriptor*)ykazat_Memory;
    Head_ykaz->Size = Size;
    Head_ykaz->Next = NULL;
    Head_ykaz->Previous = NULL;
    int* endDescriptor = End_Descriptor(Head_ykaz);
    *endDescriptor = Size;
    Curret_ykaz = Head_ykaz;
    Size_Memory = Size;

    return Size;
}

void* Malloc_Memory(int Size) {
    if ((Size < 1) || (Size > Size_Memory))
    {
        return NULL;
    }

    Descriptor* Current = Curret_ykaz;
    int* End_Description = NULL;
    int* New_End_Description = NULL;
    
    if (Current != NULL)
        do {
            End_Description = End_Descriptor(Current);
            if ((Current->Size) - Size > 2 * Return_Block_Size_Memory())
            {
                Descriptor* New_Block_Memory = (Descriptor*)((char*)Current + Return_Block_Size_Memory() + Size);
                (New_Block_Memory->Previous) = (Current->Previous);
                (New_Block_Memory->Next) = (Current->Next);
                (New_Block_Memory->Size) = (Current->Size) - Size - Return_Block_Size_Memory();
                
                if ((Current->Previous) != NULL)
                {
                    (Current->Previous->Next) = New_Block_Memory;
                }
                else Head_ykaz = New_Block_Memory;
                
                if ((Current->Next) != NULL)
                {
                    (Current->Next->Previous) = New_Block_Memory;
                }

                (Current->Size) = Return_Block_Size_Memory() + Size;

                New_End_Description = End_Descriptor(New_Block_Memory);
                *New_End_Description = (New_Block_Memory->Size);

                End_Description = End_Descriptor(Current);
                *End_Description = -Current->Size;
                Curret_ykaz = New_Block_Memory;

                return (void*)((char*)Current + sizeof(Descriptor));
            }
            else { 
                if (Current->Size - Return_Block_Size_Memory() >= Size) {
                    End_Description = End_Descriptor(Current);
                    *End_Description = -Current->Size;

                    if ((Current->Previous) != NULL)
                    {
                        Current->Previous->Next = Current->Next;
                    }

                    if (Head_ykaz == Current) 
                    {
                        Head_ykaz = (Current->Next);
                    }

                    if ((Current->Next) != NULL) 
                    {
                        Curret_ykaz = (Current->Next);
                        (Current->Next->Previous) = (Current->Previous);
                    }
                    else Curret_ykaz = Head_ykaz;

                    return (void*)((char*)Current + sizeof(Descriptor));
                }
            }
            Current = (Current->Next);
            if (Current == NULL) 
            {
                Current = Head_ykaz;
            }
        } while (Current != Curret_ykaz);

        Curret_ykaz = Head_ykaz;
        return NULL;
}

void Free_Malloc(void* ykazat) {
    Descriptor* ykaz_Description = (Descriptor*)((char*)ykazat - sizeof(Descriptor));
    int* End_Description = End_Descriptor(ykaz_Description);
    int Left_Flag = 0;
    int Right_Flag = 0;

    *End_Description = (ykaz_Description->Size);


    //merge left
    if ((char*)(ykaz_Description - 1) > (char*)Start_Memory) {
        int* leftBlockEndDesc = (int*)((char*)ykaz_Description - sizeof(int));
        if (*leftBlockEndDesc > 0) {
            Descriptor* Left_Block_Description_Memory = (Descriptor*)((char*)ykaz_Description - *leftBlockEndDesc);

            (Left_Block_Description_Memory->Size) = (Left_Block_Description_Memory->Size) + (ykaz_Description->Size);

            *End_Descriptor(Left_Block_Description_Memory) = Left_Block_Description_Memory->Size;
            ykaz_Description = Left_Block_Description_Memory;

            if (Curret_ykaz == ykaz_Description)
                Curret_ykaz = Left_Block_Description_Memory;

            Left_Flag = 1;
        }
    }

    //merge right
    if ((char*)(End_Description + 1) < (char*)Start_Memory + Size_Memory) {
        Descriptor* Right_Block_Description_Memory = (Descriptor*)((char*)ykaz_Description + ykaz_Description->Size);
        int* rightBlockEndDesc = End_Descriptor(Right_Block_Description_Memory);

        if (*rightBlockEndDesc > 0) {


            Right_Flag = 1;
            if (Left_Flag == 0) {
                ykaz_Description->Next = Head_ykaz;
                Head_ykaz->Previous = ykaz_Description;
                ykaz_Description->Previous = NULL;
                Head_ykaz = ykaz_Description;
            }

            if (Right_Block_Description_Memory == Head_ykaz) {
                Head_ykaz = Right_Block_Description_Memory->Next;
                Head_ykaz->Previous = NULL;
            }
            else {
                if (Right_Block_Description_Memory->Previous != NULL)
                {
                    Right_Block_Description_Memory->Previous->Next = Right_Block_Description_Memory->Next;
                }

                if (Right_Block_Description_Memory->Next != NULL)
                {
                    Right_Block_Description_Memory->Next->Previous = Right_Block_Description_Memory->Previous;
                }
            }

            ykaz_Description->Size += Right_Block_Description_Memory->Size;
            *End_Descriptor(ykaz_Description) = ykaz_Description->Size;
            
            if (Curret_ykaz == Right_Block_Description_Memory) 
            {
                Curret_ykaz = ykaz_Description;
            }

        }

    }

    if (Right_Flag == 0 && Left_Flag == 0) 
    {
        ykaz_Description->Previous = NULL;
        ykaz_Description->Next = Head_ykaz;
        
        if (Head_ykaz != NULL)
        {
            Head_ykaz->Previous = ykaz_Description;
        }

        Head_ykaz = ykaz_Description;
        if (ykaz_Description->Next != NULL)
        {
            ykaz_Description->Next->Previous = ykaz_Description;
        }
    }
    if (Curret_ykaz == NULL)
    {
        Curret_ykaz = ykaz_Description;
    }
}

void Chek_Memory() {
    Descriptor* Current = (Descriptor*)Start_Memory;

    while ((char*)Current < (char*)Start_Memory + Size_Memory) {
        if (*End_Descriptor(Current) < 0)
            fprintf(stderr, "Memory leak , block %ykazat\n", (char*)Current + sizeof(Descriptor));
        Current = (Descriptor*)((char*)Current + Current->Size);
    }
}