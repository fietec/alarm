#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <mmsystem.h>

#define ALARM_RING_NUMBER 20

char* shift_args(int *argc, char ***argv)
{
    assert(*argc > 0 && "Args out of bounce!");
    char *arg = **argv;
    *argc -= 1;
    *argv += 1;
    return arg;
}

void print_usage(char *name)
{
    if (!name) return;
    printf("Alarm: How to use:\n");
    printf("  %s [flags] <hour> <minute>\n\n", name);
    printf("  Arguments:\n");
    printf("    <hour>:               (int)       hour of the alarm time\n");
    printf("    <minute>:             (int)       minute of the alarm time\n");
    printf("    --rings [-r] <rings>: (flag)[int] number or ringtones\n");
    printf("    --silent [-s]:        (flag)      disable ring tone\n");
    printf("    --help [-h]:          (flag)      print this help dialog\n");
}

int main(int argc, char **argv)
{
    char *program_name = shift_args(&argc, &argv);
    size_t args_found = 0;
    int alarm_hour = 0;
    int alarm_minute = 0;
    int ring_number = ALARM_RING_NUMBER;
    bool silent = false;
    while (argc > 0){
        char *arg = shift_args(&argc, &argv);
        if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0){
            print_usage(program_name);
            return 0;
        }
        if (strcmp(arg, "--silent") == 0 || strcmp(arg, "-s") == 0){
            silent = true;
            continue;
        }
        if (strcmp(arg, "--rings") == 0 || strcmp(arg, "-r") == 0){
            char *sn = shift_args(&argc, &argv);
            int n = atoi(sn);
            if (n != 0){
                ring_number = n;
                continue;
            }
            fprintf(stderr, "Invalid integer: \"%s\"\n", sn);
            print_usage(program_name);
            return 1;
        }
        args_found += 1;
        switch(args_found){
            case 1:{
                alarm_hour = atoi(arg);
            } break;
            case 2:{
                alarm_minute = atoi(arg);
            } break;
            default:{
                fprintf(stderr, "Unknown argument: \"%s\"\n", arg);
                print_usage(program_name);
                return 1;
            }
        }
    }
    if (args_found != 2){
        fprintf(stderr, "Too few arguments provided!\n");
        print_usage(program_name);
        return 1;
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
    // alarm time reached
    if (silent){
        printf("Time to wake up! Press ENTER to exit..\n");
        getchar();
        printf("Good morning!\n");
    }
    else{
        // TODO: make this platform independent
        printf("Time to wake up! Press Ctrl-C to exit..\n");
        for (size_t i=0; i<ring_number; ++i){
            PlaySound("iphone_alarm.wav", NULL, SND_FILENAME); 
        }
	    printf("Finished but nobody woke :(\n");
    }
    return 0;
}