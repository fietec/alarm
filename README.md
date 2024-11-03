# Alarm
A minimalistic alarm application written in C.

## How to build
NOTE: This application is **Windows-only**! This is due to the use of the `PlaySound` function from the **win32-api** for which I have not yet found a cross-platform alternative.
To build, run `build.sh` or directly in the terminal:
```
gcc -o alarm c:\windows\system32\winmm.dll alarm.c
```
## How to use

To set an alarm run `alarm` with the following arguments:
```
alarm [..flags] <hour> <minute>
```
The supported arguments are:
- `<hour>`:                 (int)  hour of the alarm time
- `<minute>`:               (int)  minute of the alarm time
- `--rings` [`-r`] `<rings>`: (flag)[int] number or ringtones
- `--silent` [`-s`]:        (flag) disable ring tone
- `--help` [`-h`]:          (flag) print help info

For `<hour>` and `<minute>`, all arguments which are not valid integers are interpreted as 0.
Therefore, e.g. running alarm like this:
```
alarm -s 09 fifteen
```
will result in the alarm going off at *09:00*.

If the `--silent` flag is not set, the default Apple ring tone will play at the specified alarm time.

## License
This project is licensed under the MIT License - see the `LICENSE` file for details.