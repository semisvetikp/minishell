/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_errno_strerror_ipen_readdir.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jradioac <jradioac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 21:46:10 by jradioac          #+#    #+#             */
/*   Updated: 2021/04/05 22:02:13 by jradioac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

int main1(int argc, const char * argv[]) 
{
    // Generate unique filename.
    char *file_name;

    file_name = "PATH";
    errno = 0;
    FILE *file = fopen(file_name, "rb");
    // Save error number. 
    errno_t error_num = errno;
	
    if (file) {
        // Do something useful. 
        fclose(file);
    }
    else {
        char *errorbuf = strerror(error_num);
        fprintf(stderr, "Error message : %s\n", errorbuf);
    }
    
    return EXIT_SUCCESS;
}

// it is example using "errno" and functions "strerror". 
// Function "execve" have own error handling. 
// This functions we can use when check file descriptors or path put in execve.


//Sample code which searches a directory for entry ``name'' is:

#include <sys/types.h>
#include <dirent.h>


int main2(int argc, const char * argv[]) 
{
    int     len;
    char    *name;
    DIR     *dirp;
    struct dirent *dp;

    len = strlen(name);
    dirp = opendir(".");
    while ((dp = readdir(dirp)) != NULL)
    {
        if (dp->d_namlen == len && !strcmp(dp->d_name, name)) 
        {
            (void)closedir(dirp);
            return (0); //FOUND
        }
    }
    (void)closedir(dirp);
    return (1); //NOT FOUND
}
