#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>

/*
    How to build: gcc -o alarm C:\Windows\System32\winmm.dll alarm.c
*/

int main(int argc, char** argv)
{
    if (argc != 3){
        fprintf(stderr, "Incorrect argument count!\nPlease use the following format:\n");
        fprintf(stderr, "  alarm <hour> <min>\n");
        return 1;
    }
    int alarm_hour = atoi(argv[1]);
    if (alarm_hour == 0){
        fprintf(stderr, "This is no valid hour: \"%s\"!\n", argv[1]);
    }
    int alarm_minute = atoi(argv[2]);
    if (alarm_minute == 0){
        fprintf(stderr, "This is no valid minute: \"%s\"!\n", argv[2]);
    }
    printf("Alarm: Sleeping until %02d:%02d..\n", alarm_hour, alarm_minute);
    while (1){
        time_t curr_time = time(NULL);
        struct tm *ctm = localtime(&curr_time);
        if (ctm->tm_hour == alarm_hour && ctm->tm_min == alarm_minute){
            break;
        }
        sleep(1);
    }
    printf("Time to wake up! Press Ctrl-C to exit..\n");
    for (size_t i=0; i<20; ++i){
        PlaySound("iphone_alarm.wav", NULL, SND_FILENAME); 
    }
	printf("Finished but nobody woke :(\n");
    return 0;
}