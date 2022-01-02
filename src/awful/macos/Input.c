#include <awful/Global.h>

#ifdef __MACOS__

#include <awful/Input.h>
#include <termios.h>
#include <unistd.h>

int InputGetChar() {
  // fd = sys.stdin.fileno()
  int ttyDevice = STDOUT_FILENO;
  struct termios old_settings;
  struct termios tty;
  // old_settings = termios.tcgetattr(fd)
  tcgetattr(ttyDevice, &old_settings);
  // try:
  //     tty.setraw(sys.stdin.fileno())
  cfmakeraw(&tty);
  //     start_pos = sys.stdin.buffer.tell()
  //     seq = sys.stdin.read(1)
  //     end_pos = sys.stdin.buffer.tell()
  //     seq_length = end_pos - start_pos
  //     if seq_length < 1:
  //         return ''
  //     seq += sys.stdin.read(seq_length-1)
  //     return seq
  // except KeyboardInterrupt:
  //     print("\b\b  ")
  //     pass
  // finally:
  //     termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
}

#endif