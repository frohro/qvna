#ifndef _LIB_H_
#define _LIB_H_

#define ERR1 1
#define	MSG1 2
#define	MSG2 3
#define	MSG3 4

void PDEBUG  (int Level, const char *Format, ... );
double zCompensation (dcomplex in, double rl, double f, bool tp, double &l, double &c, bool &onTX);
QString engOut(double val, int width);

extern int debugLevel; 

#endif
