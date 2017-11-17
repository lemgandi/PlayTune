#ifndef PLAYTUNE_H
#define PLAYTUNE_H


typedef enum Button {
   Right,
   Up,
   Down,
   Left,
   Select,
   NullButton
};

typedef struct 
{
   int pitch;
   int duration;
} note;


#endif
