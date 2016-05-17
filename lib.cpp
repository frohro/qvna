#include <QDebug>
#include "config.h"
#include "lib.h"

int debugLevel = 4;

void PDEBUG (int Level, const char *Format, ... ) {
#ifndef QT_NO_DEBUG
	va_list ap;
	char s[64*1024];
	va_start(ap, Format);
	if (debugLevel >= Level) {
		vsprintf(s,Format,ap);
		qDebug() << s;
	}
	va_end(ap);
#endif
}

double parallel(double a, double b) {
	return (a*b)/(a+b);
}


double round(double val, int width)
{
	double v[] = { 1, 10, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8 };
	return floor(val * v[width] + 0.5) / v[width];
}

QString engOut(double val, int width) {

	char siPre[] = "YZEPTGMk munpfaz";
	double pre = 1e24;
	int pos = 0;
	int sign = 1;
	int fw = width+2;

	if (val==0)
		return QString("0 ");

	if (val<0) {
		val =-val;
		sign = -1;
	}

	while (val/pre < 1 && pos++ < (int)sizeof(siPre)) 
		pre /= 1000;
	val /= pre;

	if (val<10) 
		width -= 1;
	else if (val<100) 
		width -= 2;
	else
		width -= 3;

	if (width<0)
		width = 0;

	if (sign<0)
		val = -val;

	return QString("%1 %2").arg(round(val,width),fw).arg(siPre[pos]);
}

double zCompensation (dcomplex in, double rl, double f, bool tp, double &l, double &c, bool &onTX) {

	double xl,xc,Q,r1,r2;

	dcomplex xs = in;

	Q=imag(in)/real(in);
	dcomplex xp(real(in)*(1+Q*Q), imag(in)*(1+Q*Q)/(Q*Q));

	r1=rl;;
	r2=real(xs);

	if (r2 > r1)
		r2 = real(xp);

	if (tp) {
		if (r2>r1) {
			xl = sqrt(r1*(r2-r1));
			xc = r2*sqrt(r1/(r2-r1));
			xc = parallel(xc,imag(xp));
			onTX = false;
			//      -L---
			//        |
			// tx     C    ant
			//        |
			//      -----
		} else {
			xl = sqrt(r2*(r1-r2));
			xc = r1*sqrt(r2/(r1-r2));
			xl += -imag(xs);
			onTX = true;
			//      ---L-
			//        |
			// tx     C    ant
			//        |
			//      -----
		}
	} else {
		if (r2>r1) {
			xl = r2*sqrt(r1/(r2-r1));
			xc = sqrt(r1*(r2-r1)); 
			xl = parallel(xl,-imag(xp));
			onTX = false;
			//      -C---
			//        |
			// tx     L    ant
			//        |
			//      -----
		} else {
			xl =  r1*sqrt(r2/(r1-r2));
			xc =  sqrt(r2*(r1-r2));
			xc += imag(xs);
			onTX = true;
				//      ---C-
				//        |
				// tx     L    ant
				//        |
				//      -----
		}
	}

	if (xl>=0)
		l = xl/(2*M_PI*f);
	else
		l = 1/(xl*2*M_PI*f);

	if (xc>0)
		c = 1/(xc*2*M_PI*f);
	else if (xc==0)
		c=-1e-12; // may be a wire	
	else
		c = xc/(2*M_PI*f);
	
	return Q;
}
