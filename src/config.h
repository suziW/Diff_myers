//
// Created by admin1 on 2020/7/7.
//

#ifndef MSTT_CONFIG_H
#define MSTT_CONFIG_H

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

// about music and records
const float SAMPLE_RATE = 16000;
const float HOPLENGTH = 512;
const float FRAMES_PER_SECOND = SAMPLE_RATE/HOPLENGTH;
const float SECONDS_PER_FRAME = HOPLENGTH/SAMPLE_RATE;
const int MIN_PITCH = 21;
const int MAX_PITCH = 108;
const int NUM_PITCHES = MAX_PITCH - MIN_PITCH + 1;

#endif //MSTT_CONFIG_H
