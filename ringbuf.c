#include <stdio.h>
#include <stdint.h>

#define BUFFER_SIZE 8

typedef struct
{
    uint8_t buffer[BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t count;

} ringbuffer;

void initbuffer(ringbuffer *rb);
int writebuffer(ringbuffer *rb, uint8_t data);
int readbuffer(ringbuffer *rb, uint8_t *data);
int isfull(ringbuffer *rb);
int isempty(ringbuffer *rb);
uint8_t getcount(ringbuffer *rb);

int main()
{
    ringbuffer rb;
    uint8_t data;
    int i;

    initbuffer(&rb);

    uint8_t arr1[] =
    {
        0x41,0x42,0x43,0x44,
        0x45,0x46,0x47,0x48
    };

    for(i = 0; i < 8; i++)
    {
        writebuffer(&rb, arr1[i]);

        printf("[WRITE] 0x%02X -> OK (count=%d)",
               arr1[i], (int)getcount(&rb));

        if(isfull(&rb))
        {
            printf(" FULL");
        }

        printf("\n");
    }

    if(writebuffer(&rb, 0x99) == -1)
    {
        printf("[WRITE] 0x99 -> FAIL (buffer full)\n");
    }

    for(i = 0; i < 3; i++)
    {
        readbuffer(&rb, &data);

        // Fixed: Added spaces to perfectly align with the PDF layout
        printf("[READ]      -> 0x%02X (count=%d)\n",
               data, (int)getcount(&rb));
    }

    uint8_t arr2[] = {0x49,0x4A,0x4B};

    for(i = 0; i < 3; i++)
    {
        writebuffer(&rb, arr2[i]);

        printf("[WRITE] 0x%02X -> OK (count=%d)",
               arr2[i], (int)getcount(&rb));

        // Fixed: Added the check here so 0x4B prints "FULL" properly
        if(isfull(&rb))
        {
            printf(" FULL");
        }

        printf("\n");
    }

    while(!isempty(&rb))
    {
        readbuffer(&rb, &data);

        // Fixed: Added spaces to perfectly align with the PDF layout
        printf("[READ]      -> 0x%02X (count=%d)\n",
               data, (int)getcount(&rb));
    }

    if(readbuffer(&rb, &data) == -1)
    {
        printf("[READ] (empty) -> FAIL (buffer empty)\n");
    }

    return 0;
}

void initbuffer(ringbuffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

int isfull(ringbuffer *rb)
{
    if(rb->count == BUFFER_SIZE)
    {
        return 1;
    }

    return 0;
}

int isempty(ringbuffer *rb)
{
    if(rb->count == 0)
    {
        return 1;
    }

    return 0;
}

uint8_t getcount(ringbuffer *rb)
{
    return rb->count;
}

int writebuffer(ringbuffer *rb, uint8_t data)
{
    if(isfull(rb))
    {
        return -1;
    }

    rb->buffer[rb->head] = data;

    /*
       Using bitwise AND instead of modulo (%).
       This is faster on many microcontrollers because it avoids a division operation.
       It works correctly only when BUFFER_SIZE is a power of 2.
       BUFFER_SIZE = 8, so this optimization is valid.
    */
    rb->head = (rb->head + 1) & (BUFFER_SIZE - 1);

    rb->count++;

    return 0;
}

int readbuffer(ringbuffer *rb, uint8_t *data)
{
    if(isempty(rb))
    {
        return -1;
    }

    *data = rb->buffer[rb->tail];

    rb->tail = (rb->tail + 1) & (BUFFER_SIZE - 1);

    rb->count--;

    return 0;
}
