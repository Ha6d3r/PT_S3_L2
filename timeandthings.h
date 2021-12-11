#ifndef TIMEANDTHINGS_H
#define TIMEANDTHINGS_H

#include <string>

unsigned int str_to_seconds(std::string str);

std::string seconds_to_str(unsigned int seconds);

const unsigned char big_dash      [12]  =  {196,196,196,196,196,196,196,196,196,196,196,0}; // ────────────
const unsigned char link_box_start[4]   =  {196,196,194,0};                                 // ──┬
const unsigned char link_box_down [4]   =  {32,32,179,0};                                   //   │
const unsigned char link_box_end  [4]   =  {32,32,192,0};                                   //   └
const unsigned char save_pos      []   =  "\0337\0";
const unsigned char load_pos      []   =  "\0338\0";

#endif // TIMEANDTHINGS_H


