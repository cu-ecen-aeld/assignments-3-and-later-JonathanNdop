/**
 * @file aesd-circular-buffer.c
 * @brief Functions and data related to a circular buffer imlementation
 *
 * @author Dan Walkes
 * @date 2020-03-01
 * @copyright Copyright (c) 2020
 *
 */

#ifdef __KERNEL__
#include <linux/string.h>
#else
#include <string.h>
#endif

#include "aesd-circular-buffer.h"

/**
 * @param buffer the buffer to search for corresponding offset.  Any necessary locking must be performed by caller.
 * @param char_offset the position to search for in the buffer list, describing the zero referenced
 *      character index if all buffer strings were concatenated end to end
 * @param entry_offset_byte_rtn is a pointer specifying a location to store the byte of the returned aesd_buffer_entry
 *      buffptr member corresponding to char_offset.  This value is only set when a matching char_offset is found
 *      in aesd_buffer.
 * @return the struct aesd_buffer_entry structure representing the position described by char_offset, or
 * NULL if this position is not available in the buffer (not enough data is written).
 */
struct aesd_buffer_entry *aesd_circular_buffer_find_entry_offset_for_fpos(struct aesd_circular_buffer *buffer,
            size_t char_offset, size_t *entry_offset_byte_rtn )
{
    /**
    * TODO: implement per description
    */
    
    /**	
    size_t cumulative_length = 0;
    struct aesd_buffer_entry *entryptr;
    int index;

    AESD_CIRCULAR_BUFFER_FOREACH(entryptr, buffer, index) {
	    if (entryptr->size + cumulative_length > char_offset) {
		    // The desired character offset is within this entry
		    *entry_offset_byte_rtn = char_offset - cumulative_length;
		    return entryptr;
	    }
    	    cumulative_length += entryptr->size;
	}
    */

    size_t offset = buffer->out_offs;
    size_t char_sum = 0;

    // Iterate through the buffer to find the char_offset
    do {
	// Check if the char_offset is in the current entry
	if(char_sum + buffer->entry[offset].size > char_offset){
	    // Calculate the entry_offset_byte_rtn
	    *entry_offset_byte_rtn = char_offset - char_sum;

	    // Return the entry
	    return &buffer->entry[offset];
	}

	// Update the char sum
	char_sum += buffer->entry[offset].size;
	
	// Move to the next entry
	offset = (offset + 1) % AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED;
    } while(offset != buffer->in_offs);	
    
    // If no entry contains the char_offset, return NULL	    
    return NULL;
}

/**
* Adds entry @param add_entry to @param buffer in the location specified in buffer->in_offs.
* If the buffer was already full, overwrites the oldest entry and advances buffer->out_offs to the
* new start location.
* Any necessary locking must be handled by the caller
* Any memory referenced in @param add_entry must be allocated by and/or must have a lifetime managed by the caller.
*/
void aesd_circular_buffer_add_entry(struct aesd_circular_buffer *buffer, const struct aesd_buffer_entry *add_entry)
{
    /**
    * TODO: implement per description
    */

    
    // Check if the buffer is full
    if (buffer->full) {
            // If the buffer is full, increment out_offs to the next position
            buffer->out_offs = (buffer->out_offs + 1) % AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED;
    }
	
    // Add the new entry at the in_offs position
    buffer->entry[buffer->in_offs] = *add_entry;

    // Move in_offs to the next position
    buffer->in_offs = (buffer->in_offs + 1) % AESDCHAR_MAX_WRITE_OPERATIONS_SUPPORTED;


    // If in_offs catches up to out_offs, the buffer is now full
    buffer->full = (buffer->in_offs == buffer->out_offs);

}

/**
* Initializes the circular buffer described by @param buffer to an empty struct
*/
void aesd_circular_buffer_init(struct aesd_circular_buffer *buffer)
{
    memset(buffer,0,sizeof(struct aesd_circular_buffer));
}
