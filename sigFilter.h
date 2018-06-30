#ifndef _SIG_FILTER_H
#define _SIG_FILTER_H

class sigFilter : public baseEffect {
public:
    sigFilter();
    ~sigFilter();
    /* virtual functions */
    void init(int mode);
    void process(float *ibuf, float *obuf, int num_frames, int num_chn);
};

#endif
