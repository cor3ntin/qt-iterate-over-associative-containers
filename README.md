# Research ways to get both the key and the value while itering over Q associative containers in a range-based loop.

## range.h 

Solution using range-v3.
I had to patch range-v3 to support Qt containers ( range-v3 assumes unsigned size type)
