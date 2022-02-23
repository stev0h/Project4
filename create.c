
 * @file create.c
 * @provides create, newpid, userret
 *
 * COSC 3250 / COEN 4820 Assignment 4
 *OSC 3250 - Project #2
 * This code is helping xinu keep secerts from his babymama
 *  * @author [JJ Mansour, Steve McDonough]
 *   * Instructor [Dennis Brylow]
 *    *    * TA-BOT:MAILTO [jack.mansour@marquette.edu, stephen.mcdonough@marquette.edu]
 */
/* Embedded XINU, Copyright (C) 2008.  All rights reserved. */

@@ -28,7 +32,6 @@ syscall create(void *funcaddr, ulong ssize, char *name, ulong nargs, ...)
    ulong i;
    va_list ap;                 /* points to list of var args   */
    ulong pads = 0;             /* padding entries in record.   */
    void INITRET(void);

    if (ssize < MINSTK)
        ssize = MINSTK;
@@ -44,9 +47,13 @@ syscall create(void *funcaddr, ulong ssize, char *name, ulong nargs, ...)

    numproc++;
    ppcb = &proctab[pid];

    // TODO: Setup PCB entry for new process.


	// TODO: Setup PCB entry for new process.
	ppcb -> state = PRSUSP;
	ppcb -> stkbase = (ulong*)((ulong)(saddr)- ssize);
	ppcb -> stklen = ssize;
	ppcb -> stkptr = NULL;
	strncpy(ppcb -> name,name, PNMLEN);
    /* Initialize stack with accounting block. */
    *saddr = STACKMAGIC;
    *--saddr = pid;
@@ -60,16 +67,37 @@ syscall create(void *funcaddr, ulong ssize, char *name, ulong nargs, ...)
    }
    /* If more than 4 args, pad record size to multiple of native memory */
    /*  transfer size.  Reserve space for extra args                     */
	 ulong *saddrVar = saddr;

    for (i = 0; i < pads; i++)
    {
        *--saddr = 0;
    }

/*       for(i =0; i < pads; i++){
                *--saddr = 0;
}*/
	ppcb -> stkptr = saddr;	
	// TODO: Initialize process context.
		saddr[CTX_LR] = (int) funcaddr;
		saddr[CTX_SP] = (int)userret;
	// TODO:  Place arguments into activation record.
	//        See K&R 7.3 for example using va_start, va_arg and
	//        va_end macros for variable argument functions.
//maybe:  int should be ulong 
	va_start(ap,nargs);
	for(i =0; i < nargs; i++){

		if(i < 4){
			saddr[i] = va_arg(ap, int);

		}else{
			saddrVar[i-4] = va_arg(ap,int);

		}

    // TODO: Initialize process context.
    //
    // TODO:  Place arguments into activation record.
    //        See K&R 7.3 for example using va_start, va_arg and
    //        va_end macros for variable argument functions.
	}
	va_end(ap);

    return pid;
}
