#include <stdio.h>
#include <stdlib.h>
#include "oslabs.h"


void print_block(struct MEMORY_BLOCK b) {
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("start_address=%d\n", b.start_address);
    printf("end_address=%d\n", b.end_address);
    printf("segment_size=%d\n", b.segment_size);
    printf("process_id=%d\n", b.process_id);
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
};

void print_map(struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt) {
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n");
    printf("total map count = %d \n\n", *map_cnt);
    for (int i=0;i<*map_cnt;i++) {
        printf("block item %d\n", i);
        print_block(memory_map[i]);
    }
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    
};

int main( int argc, char* argv[])
{

    struct MEMORY_BLOCK memory_map[MAPMAX] = {
        {0,19,20, 10},
        {20,39,20, 0},
        {40,49,10, 20},
        {50,1023,974, 10},
    };
    
    int map_cnt = 4;
    int request_size = 20;
    int process_id = 40;


    print_block(best_fit_allocate(request_size, memory_map, &map_cnt, process_id));
    
    print_map(memory_map, &map_cnt);



    // struct MEMORY_BLOCK memory_map[MAPMAX] = {
    //     {0,7,8,12},
    //     {8,15,8,0},
    //     {16,23,8,13},
    //     {24,27,4,0},
    //     {28,29,2,11},
    // };
    
    // int map_cnt = 5;

    // struct MEMORY_BLOCK freed_block = {
    //     16,23,8,13
    // };


    // release_memory(freed_block, memory_map, &map_cnt);

    // print_map(memory_map, &map_cnt);

}