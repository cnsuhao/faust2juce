//-----------------------------------------------------
// name : "multibandfilter"
// version : "1.0"
// author : "Grame" 
// license : "BSD"
// copyright : "(c)GRAME 2006"
//
// Code generated with Faust 0.9.9.4 (http://faust.grame.fr)
//-----------------------------------------------------
/* link with  */
#include <math.h>
#include "FaustJuce.h"

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <time.h>
//#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <string>
#include <vector>
#include <math.h>

using namespace std ;


inline int lsr (int x, int n) { return int(((unsigned int)x) >> n); }

inline int int2pow2 (int x) { int r=0; while ((1<<r)<x) r++; return r; }

/******************************************************************************
 *******************************************************************************
 *
 *							       VECTOR INTRINSICS
 *
 *******************************************************************************
 *******************************************************************************/

//inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((unsigned)(calloc((nmemb*size)+15,sizeof(char)))+15 & 0xfffffff0); }
inline void *aligned_calloc(size_t nmemb, size_t size) { return (void*)((size_t)(calloc((nmemb*size)+15,sizeof(char)))+15 & ~15); }


//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------


class mydsp : public dsp {
  private:
	float 	fentry0;
	float 	fConst0;
	float 	fslider0;
	float 	fentry1;
	float 	fentry2;
	float 	fslider1;
	float 	fentry3;
	float 	fentry4;
	float 	fslider2;
	float 	fentry5;
	float 	fentry6;
	float 	fslider3;
	float 	fentry7;
	float 	fentry8;
	float 	fslider4;
	float 	fentry9;
	float 	fentry10;
	float 	fslider5;
	float 	fentry11;
	float 	fentry12;
	float 	fslider6;
	float 	fentry13;
	float 	fentry14;
	float 	fslider7;
	float 	fentry15;
	float 	fentry16;
	float 	fslider8;
	float 	fentry17;
	float 	fentry18;
	float 	fslider9;
	float 	fentry19;
	float 	fRec9[3];
	float 	fRec8[3];
	float 	fRec7[3];
	float 	fRec6[3];
	float 	fRec5[3];
	float 	fRec4[3];
	float 	fRec3[3];
	float 	fRec2[3];
	float 	fRec1[3];
	float 	fRec0[3];
  public:
	virtual int getNumInputs() 	{ return 1; }
	virtual int getNumOutputs() 	{ return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fentry0 = 10000.000000f;
		fConst0 = (3.141593f / fSamplingFreq);
		fslider0 = 0.000000f;
		fentry1 = 50.000000f;
		fentry2 = 9000.000000f;
		fslider1 = 0.000000f;
		fentry3 = 50.000000f;
		fentry4 = 8000.000000f;
		fslider2 = 0.000000f;
		fentry5 = 50.000000f;
		fentry6 = 7000.000000f;
		fslider3 = 0.000000f;
		fentry7 = 50.000000f;
		fentry8 = 6000.000000f;
		fslider4 = 0.000000f;
		fentry9 = 50.000000f;
		fentry10 = 5000.000000f;
		fslider5 = 0.000000f;
		fentry11 = 50.000000f;
		fentry12 = 4000.000000f;
		fslider6 = 0.000000f;
		fentry13 = 50.000000f;
		fentry14 = 3000.000000f;
		fslider7 = 0.000000f;
		fentry15 = 50.000000f;
		fentry16 = 2000.000000f;
		fslider8 = 0.000000f;
		fentry17 = 50.000000f;
		fentry18 = 1000.000000f;
		fslider9 = 0.000000f;
		fentry19 = 50.000000f;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<3; i++) fRec5[i] = 0;
		for (int i=0; i<3; i++) fRec4[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void buildUserInterface(UI* interface) {
		interface->openHorizontalBox("Multi Band Filter");
		interface->openVerticalBox("peak 0");
		interface->addNumEntry("Q factor", &fentry19, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry18, 1000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider9, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->openVerticalBox("peak 1");
		interface->addNumEntry("Q factor", &fentry17, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry16, 2000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider8, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->openVerticalBox("peak 2");
		interface->addNumEntry("Q factor", &fentry15, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry14, 3000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider7, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->openVerticalBox("peak 3");
		interface->addNumEntry("Q factor", &fentry13, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry12, 4000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider6, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->openVerticalBox("peak 4");
		interface->addNumEntry("Q factor", &fentry11, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry10, 5000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider5, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->openVerticalBox("peak 5");
		interface->addNumEntry("Q factor", &fentry9, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry8, 6000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider4, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->openVerticalBox("peak 6");
		interface->addNumEntry("Q factor", &fentry7, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry6, 7000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider3, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->openVerticalBox("peak 7");
		interface->addNumEntry("Q factor", &fentry5, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry4, 8000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider2, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->openVerticalBox("peak 8");
		interface->addNumEntry("Q factor", &fentry3, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry2, 9000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider1, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->openVerticalBox("peak 9");
		interface->addNumEntry("Q factor", &fentry1, 50.000000f, 0.100000f, 100.000000f, 0.100000f);
		interface->addNumEntry("freq (Hz)", &fentry0, 10000.000000f, 20.000000f, 20000.000000f, 1.000000f);
		interface->addVerticalSlider("gain (dB)", &fslider0, 0.000000f, -50.000000f, 50.000000f, 0.100000f);
		interface->closeBox();
		interface->closeBox();
	}
	virtual void compute (int count, float** input, float** output) {
		float* input0 = input[0];
		float* output0 = output[0];
		float fSlow0 = tanf((fConst0 * fentry0));
		float fSlow1 = (fSlow0 * fSlow0);
		float fSlow2 = ((1.000000f / fentry1) * fSlow0);
		float fSlow3 = (fSlow2 * powf(10, (0 - (5.000000e-02f * fslider0))));
		float fSlow4 = (1 + fSlow1);
		float fSlow5 = (fSlow4 + fSlow3);
		float fSlow6 = ((2.000000f / fSlow5) * (fSlow1 - 1));
		float fSlow7 = (1.000000f / fSlow5);
		float fSlow8 = (fSlow7 * (fSlow4 - fSlow3));
		float fSlow9 = tanf((fConst0 * fentry2));
		float fSlow10 = (fSlow9 * fSlow9);
		float fSlow11 = ((1.000000f / fentry3) * fSlow9);
		float fSlow12 = (fSlow11 * powf(10, (0 - (5.000000e-02f * fslider1))));
		float fSlow13 = (1 + fSlow10);
		float fSlow14 = (fSlow13 + fSlow12);
		float fSlow15 = ((2.000000f / fSlow14) * (fSlow10 - 1));
		float fSlow16 = (1.000000f / fSlow14);
		float fSlow17 = (fSlow16 * (fSlow13 - fSlow12));
		float fSlow18 = tanf((fConst0 * fentry4));
		float fSlow19 = (fSlow18 * fSlow18);
		float fSlow20 = ((1.000000f / fentry5) * fSlow18);
		float fSlow21 = (fSlow20 * powf(10, (0 - (5.000000e-02f * fslider2))));
		float fSlow22 = (1 + fSlow19);
		float fSlow23 = (fSlow22 + fSlow21);
		float fSlow24 = ((2.000000f / fSlow23) * (fSlow19 - 1));
		float fSlow25 = (1.000000f / fSlow23);
		float fSlow26 = (fSlow25 * (fSlow22 - fSlow21));
		float fSlow27 = tanf((fConst0 * fentry6));
		float fSlow28 = (fSlow27 * fSlow27);
		float fSlow29 = ((1.000000f / fentry7) * fSlow27);
		float fSlow30 = (fSlow29 * powf(10, (0 - (5.000000e-02f * fslider3))));
		float fSlow31 = (1 + fSlow28);
		float fSlow32 = (fSlow31 + fSlow30);
		float fSlow33 = ((2.000000f / fSlow32) * (fSlow28 - 1));
		float fSlow34 = (1.000000f / fSlow32);
		float fSlow35 = (fSlow34 * (fSlow31 - fSlow30));
		float fSlow36 = tanf((fConst0 * fentry8));
		float fSlow37 = (fSlow36 * fSlow36);
		float fSlow38 = ((1.000000f / fentry9) * fSlow36);
		float fSlow39 = (fSlow38 * powf(10, (0 - (5.000000e-02f * fslider4))));
		float fSlow40 = (1 + fSlow37);
		float fSlow41 = (fSlow40 + fSlow39);
		float fSlow42 = ((2.000000f / fSlow41) * (fSlow37 - 1));
		float fSlow43 = (1.000000f / fSlow41);
		float fSlow44 = (fSlow43 * (fSlow40 - fSlow39));
		float fSlow45 = tanf((fConst0 * fentry10));
		float fSlow46 = (fSlow45 * fSlow45);
		float fSlow47 = ((1.000000f / fentry11) * fSlow45);
		float fSlow48 = (fSlow47 * powf(10, (0 - (5.000000e-02f * fslider5))));
		float fSlow49 = (1 + fSlow46);
		float fSlow50 = (fSlow49 + fSlow48);
		float fSlow51 = ((2.000000f / fSlow50) * (fSlow46 - 1));
		float fSlow52 = (1.000000f / fSlow50);
		float fSlow53 = (fSlow52 * (fSlow49 - fSlow48));
		float fSlow54 = tanf((fConst0 * fentry12));
		float fSlow55 = (fSlow54 * fSlow54);
		float fSlow56 = ((1.000000f / fentry13) * fSlow54);
		float fSlow57 = (fSlow56 * powf(10, (0 - (5.000000e-02f * fslider6))));
		float fSlow58 = (1 + fSlow55);
		float fSlow59 = (fSlow58 + fSlow57);
		float fSlow60 = ((2.000000f / fSlow59) * (fSlow55 - 1));
		float fSlow61 = (1.000000f / fSlow59);
		float fSlow62 = (fSlow61 * (fSlow58 - fSlow57));
		float fSlow63 = tanf((fConst0 * fentry14));
		float fSlow64 = (fSlow63 * fSlow63);
		float fSlow65 = ((1.000000f / fentry15) * fSlow63);
		float fSlow66 = (fSlow65 * powf(10, (0 - (5.000000e-02f * fslider7))));
		float fSlow67 = (1 + fSlow64);
		float fSlow68 = (fSlow67 + fSlow66);
		float fSlow69 = ((2.000000f / fSlow68) * (fSlow64 - 1));
		float fSlow70 = (1.000000f / fSlow68);
		float fSlow71 = (fSlow70 * (fSlow67 - fSlow66));
		float fSlow72 = tanf((fConst0 * fentry16));
		float fSlow73 = (fSlow72 * fSlow72);
		float fSlow74 = ((1.000000f / fentry17) * fSlow72);
		float fSlow75 = (fSlow74 * powf(10, (0 - (5.000000e-02f * fslider8))));
		float fSlow76 = (1 + fSlow73);
		float fSlow77 = (fSlow76 + fSlow75);
		float fSlow78 = ((2.000000f / fSlow77) * (fSlow73 - 1));
		float fSlow79 = (1.000000f / fSlow77);
		float fSlow80 = (fSlow79 * (fSlow76 - fSlow75));
		float fSlow81 = tanf((fConst0 * fentry18));
		float fSlow82 = (fSlow81 * fSlow81);
		float fSlow83 = ((1.000000f / fentry19) * fSlow81);
		float fSlow84 = (fSlow83 * powf(10, (0 - (5.000000e-02f * fslider9))));
		float fSlow85 = (1 + fSlow82);
		float fSlow86 = (fSlow85 + fSlow84);
		float fSlow87 = ((2.000000f / fSlow86) * (fSlow82 - 1));
		float fSlow88 = (1.000000f / fSlow86);
		float fSlow89 = (fSlow88 * (fSlow85 - fSlow84));
		float fSlow90 = (fSlow88 * (fSlow85 + fSlow83));
		float fSlow91 = (fSlow88 * (fSlow85 - fSlow83));
		float fSlow92 = (fSlow79 * (fSlow76 + fSlow74));
		float fSlow93 = (fSlow79 * (fSlow76 - fSlow74));
		float fSlow94 = (fSlow70 * (fSlow67 + fSlow65));
		float fSlow95 = (fSlow70 * (fSlow67 - fSlow65));
		float fSlow96 = (fSlow61 * (fSlow58 + fSlow56));
		float fSlow97 = (fSlow61 * (fSlow58 - fSlow56));
		float fSlow98 = (fSlow52 * (fSlow49 + fSlow47));
		float fSlow99 = (fSlow52 * (fSlow49 - fSlow47));
		float fSlow100 = (fSlow43 * (fSlow40 + fSlow38));
		float fSlow101 = (fSlow43 * (fSlow40 - fSlow38));
		float fSlow102 = (fSlow34 * (fSlow31 + fSlow29));
		float fSlow103 = (fSlow34 * (fSlow31 - fSlow29));
		float fSlow104 = (fSlow25 * (fSlow22 + fSlow20));
		float fSlow105 = (fSlow25 * (fSlow22 - fSlow20));
		float fSlow106 = (fSlow16 * (fSlow13 + fSlow11));
		float fSlow107 = (fSlow16 * (fSlow13 - fSlow11));
		float fSlow108 = (fSlow7 * (fSlow4 + fSlow2));
		float fSlow109 = (fSlow7 * (fSlow4 - fSlow2));
		for (int i=0; i<count; i++) {
			float fTemp0 = (fSlow6 * fRec0[1]);
			float fTemp1 = (fSlow15 * fRec1[1]);
			float fTemp2 = (fSlow24 * fRec2[1]);
			float fTemp3 = (fSlow33 * fRec3[1]);
			float fTemp4 = (fSlow42 * fRec4[1]);
			float fTemp5 = (fSlow51 * fRec5[1]);
			float fTemp6 = (fSlow60 * fRec6[1]);
			float fTemp7 = (fSlow69 * fRec7[1]);
			float fTemp8 = (fSlow78 * fRec8[1]);
			float fTemp9 = (fSlow87 * fRec9[1]);
			fRec9[0] = (input0[i] - ((fSlow89 * fRec9[2]) + fTemp9));
			fRec8[0] = (((fTemp9 + (fSlow91 * fRec9[2])) + (fSlow90 * fRec9[0])) - ((fSlow80 * fRec8[2]) + fTemp8));
			fRec7[0] = (((fTemp8 + (fSlow93 * fRec8[2])) + (fSlow92 * fRec8[0])) - ((fSlow71 * fRec7[2]) + fTemp7));
			fRec6[0] = (((fTemp7 + (fSlow95 * fRec7[2])) + (fSlow94 * fRec7[0])) - ((fSlow62 * fRec6[2]) + fTemp6));
			fRec5[0] = (((fTemp6 + (fSlow97 * fRec6[2])) + (fSlow96 * fRec6[0])) - ((fSlow53 * fRec5[2]) + fTemp5));
			fRec4[0] = (((fTemp5 + (fSlow99 * fRec5[2])) + (fSlow98 * fRec5[0])) - ((fSlow44 * fRec4[2]) + fTemp4));
			fRec3[0] = (((fTemp4 + (fSlow101 * fRec4[2])) + (fSlow100 * fRec4[0])) - ((fSlow35 * fRec3[2]) + fTemp3));
			fRec2[0] = (((fTemp3 + (fSlow103 * fRec3[2])) + (fSlow102 * fRec3[0])) - ((fSlow26 * fRec2[2]) + fTemp2));
			fRec1[0] = (((fTemp2 + (fSlow105 * fRec2[2])) + (fSlow104 * fRec2[0])) - ((fSlow17 * fRec1[2]) + fTemp1));
			fRec0[0] = (((fTemp1 + (fSlow107 * fRec1[2])) + (fSlow106 * fRec1[0])) - ((fSlow8 * fRec0[2]) + fTemp0));
			output0[i] = ((fTemp0 + (fSlow109 * fRec0[2])) + (fSlow108 * fRec0[0]));
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec4[2] = fRec4[1]; fRec4[1] = fRec4[0];
			fRec5[2] = fRec5[1]; fRec5[1] = fRec5[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
		}
	}
};



dsp* faustCreateDSP()
{
	return new mydsp();
}
