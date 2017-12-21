#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

// Define signal handlers here.
void sigkill() 
{
	pid_t my_pid = getpid();
	kill(my_pid, SIGKILL);
}
void sig0()
{
	char value = 0;
	int filedesc = open("/dev/rps", O_RDWR);
	write(filedesc, &value, sizeof(char));
	close(filedesc);
}
void sig1()
{
	char value = 1;
	int filedesc = open("/dev/rps", O_RDWR);
	write(filedesc, &value, sizeof(char));
	close(filedesc);
}
void sig2()
{
	char value = 2;
	int filedesc = open("/dev/rps", O_RDWR);
	write(filedesc, &value, sizeof(char));
	close(filedesc);
}
void sig3()
{
	char value = 3;
	int filedesc = open("/dev/rps", O_RDWR);
	write(filedesc, &value, sizeof(char));
	close(filedesc);
}
int main()
{
  // Register signal handlers here.
  signal(SIGTERM, sigkill);
  signal(SIGRTMIN, sig0);
  signal(SIGRTMIN+1, sig1);
  signal(SIGRTMIN+2, sig2);
  signal(SIGRTMIN+3, sig3);
  while(1) pause();
  return 0;
}
