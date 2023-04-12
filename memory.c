#include <stdio.h>
#include "oslabs.h"


struct MEMORY_BLOCK NULLBLOCK = {
    0,0,0,0
};


int is_null_block(struct MEMORY_BLOCK block) {
    if (block.start_address !=0 || block.end_address !=0 || block.segment_size !=0 || block.process_id !=0) {
        return 0;
    }

    return 1;

};

struct MEMORY_BLOCK split_block_in_map(int request_size,int fit_index, struct MEMORY_BLOCK memory_map[MAPMAX], int *map_cnt, int process_id) {
    for (int i=*map_cnt; i > fit_index; i--) {
        memory_map[i] = memory_map[i-1];
    }

    memory_map[fit_index].process_id = process_id;
    memory_map[fit_index].end_address = memory_map[fit_index].start_address + request_size - 1;
    memory_map[fit_index].segment_size = request_size;


    memory_map[fit_index+1].process_id = 0;
    memory_map[fit_index+1].start_address = memory_map[fit_index].end_address + 1;
    memory_map[fit_index+1].segment_size = memory_map[fit_index+1].segment_size - request_size;

    (*map_cnt)++;

    return memory_map[fit_index];
};

struct MEMORY_BLOCK best_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {
    // find what segment fit that block
    int fit_index = 0;
    int fit_size = 0;
    for (int i=0; i<*map_cnt; i++) {
        if (is_null_block(memory_map[i])) {
            continue;
        }

        if (memory_map[i].process_id !=0) {
            continue;
        }

        if (memory_map[i].segment_size < request_size) {
            continue;
        } 

        if (memory_map[i].segment_size >= request_size && (memory_map[i].segment_size < fit_size || fit_size ==0)) {
            fit_index = i;
            fit_size = memory_map[i].segment_size;
        }

    }


    // If the free block found is exactly of the same size as the requested size, the method updates the process id to allocate it and returns this memory block.
    if (fit_size == request_size) {
        memory_map[fit_index].process_id = process_id;
        return memory_map[fit_index];
    }

    // If the free block found is larger than the requested size, the block is split into two pieces - the first piece allocated and the second piece becoming a free block in the memory map. Thus, the method may alter the memory map appropriately.
    if (fit_size > request_size) {
        return split_block_in_map(request_size, fit_index, memory_map, map_cnt, process_id);
    }
    
    // Note that if there is no free block of memory(in the memory map) that is at least as large as the requested size, the method returns the NULLBLOCK.
    return NULLBLOCK;


};



struct MEMORY_BLOCK first_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {
    // find what segment fit that block
    int fit_index = 0;
    int fit_start_address = 0;
    for (int i=0; i<*map_cnt; i++) {
        if (is_null_block(memory_map[i])) {
            continue;
        }

        if (memory_map[i].process_id !=0) {
            continue;
        }

        if (memory_map[i].segment_size < request_size) {
            continue;
        } 

        if (memory_map[i].segment_size >= request_size && (memory_map[i].start_address < fit_start_address || fit_start_address ==0)) {
            fit_index = i;
            fit_start_address = memory_map[i].start_address;
            break;
        }

    }

    // If the free block found is exactly of the same size as the requested size, the method updates the process id to allocate it and returns this memory block.
    if (memory_map[fit_index].segment_size == request_size) {
        memory_map[fit_index].process_id = process_id;
        return memory_map[fit_index];
    }

    // If the free block found is larger than the requested size, the block is split into two pieces - the first piece allocated and the second piece becoming a free block in the memory map. Thus, the method may alter the memory map appropriately.
    if (memory_map[fit_index].segment_size > request_size) {
        return split_block_in_map(request_size, fit_index, memory_map, map_cnt, process_id);
    }
    
    // Note that if there is no free block of memory(in the memory map) that is at least as large as the requested size, the method returns the NULLBLOCK.
    return NULLBLOCK;

};  


struct MEMORY_BLOCK worst_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id) {
    // find what segment fit that block
    int fit_index = 0;
    int fit_size = 0;
    for (int i=0; i<*map_cnt; i++) {
        if (is_null_block(memory_map[i])) {
            continue;
        }

        if (memory_map[i].process_id !=0) {
            continue;
        }

        if (memory_map[i].segment_size < request_size) {
            continue;
        } 

        if (memory_map[i].segment_size >= request_size && (memory_map[i].segment_size > fit_size || fit_size ==0)) {
            fit_index = i;
            fit_size = memory_map[i].segment_size;
        }

    }

    // If the free block found is exactly of the same size as the requested size, the method updates the process id to allocate it and returns this memory block.
    if (fit_size == request_size) {
        memory_map[fit_index].process_id = process_id;
        return memory_map[fit_index];
    }

    // If the free block found is larger than the requested size, the block is split into two pieces - the first piece allocated and the second piece becoming a free block in the memory map. Thus, the method may alter the memory map appropriately.
    if (fit_size > request_size) {
        return split_block_in_map(request_size, fit_index, memory_map, map_cnt, process_id);
    }
    
    // Note that if there is no free block of memory(in the memory map) that is at least as large as the requested size, the method returns the NULLBLOCK.
    return NULLBLOCK;
};  


struct MEMORY_BLOCK next_fit_allocate(int request_size, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt, int process_id, int last_address) {
    // find what segment fit that block
    int fit_index = 0;
    for (int i=0; i<*map_cnt; i++) {
        if (is_null_block(memory_map[i])) {
            continue;
        }

        if (memory_map[i].process_id !=0) {
            continue;
        }

        if (memory_map[i].segment_size < request_size) {
            continue;
        } 

        if (memory_map[i].segment_size >= request_size && (memory_map[i].start_address > last_address)) {
            fit_index = i;
            break;
        }

    }

    // If the free block found is exactly of the same size as the requested size, the method updates the process id to allocate it and returns this memory block.
    if (memory_map[fit_index].segment_size == request_size) {
        memory_map[fit_index].process_id = process_id;
        return memory_map[fit_index];
    }

    // If the free block found is larger than the requested size, the block is split into two pieces - the first piece allocated and the second piece becoming a free block in the memory map. Thus, the method may alter the memory map appropriately.
    if (memory_map[fit_index].segment_size > request_size) {
        return split_block_in_map(request_size, fit_index, memory_map, map_cnt, process_id);
    }
    
    // Note that if there is no free block of memory(in the memory map) that is at least as large as the requested size, the method returns the NULLBLOCK.
    return NULLBLOCK;
}; 

void release_memory(struct MEMORY_BLOCK freed_block, struct MEMORY_BLOCK memory_map[MAPMAX],int *map_cnt) {
    int fit_index = 0;
    for (int i=0; i< *map_cnt; i++) {
        if (memory_map[i].process_id == freed_block.process_id)
        {
            fit_index = i;
            break;
        };
    };



    // merge target block and next
    if (fit_index+1 < *map_cnt && memory_map[fit_index+1].process_id == 0) {
        memory_map[fit_index].end_address = memory_map[fit_index+1].end_address;
        memory_map[fit_index].segment_size += memory_map[fit_index+1].segment_size;
    }

    for (int i=fit_index+1;i+1<*map_cnt;i++) {
        memory_map[i] = memory_map[i+1];
    }

    (*map_cnt)--;


    // merge target block and prev
    if (fit_index > 0 && memory_map[fit_index-1].process_id == 0) {
        memory_map[fit_index-1].end_address = memory_map[fit_index].end_address;
        memory_map[fit_index-1].segment_size += memory_map[fit_index].segment_size;
    }

    for (int i=fit_index;i+1<*map_cnt;i++) {
        memory_map[i] = memory_map[i+1];
    }

    (*map_cnt)--;


};  