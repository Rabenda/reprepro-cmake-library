/*  written 2007 by Bernhard R. Link
 *  This file is in the public domain.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
#include <config.h>

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "filecntl.h"

#ifndef HAVE_CLOSEFROM
void closefrom(int lowfd) {
	long maxopen;
	int fd;

# ifdef F_CLOSEM
	if( fcntl(lowfd, F_CLOSEM, NULL) == 0 )
		return;
# endif
	maxopen = sysconf(_SC_OPEN_MAX);
	if( maxopen > INT_MAX )
		maxopen = INT_MAX;
	if( maxopen < 0 )
		maxopen = 1024;
	for( fd = lowfd ; fd <= maxopen ; fd++ )
		close(fd);
}
#endif

void markcloseonexec(int fd) {
	long l;
	l = fcntl(fd, F_GETFD, 0);
	if( l >= 0 ) {
		fcntl(fd, F_SETFD, l|FD_CLOEXEC);
	}
}