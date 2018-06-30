#ifndef _SIG_DRC_H
#define _SIG_DRC_H

class sigDRC : public baseEffect {
public:
    sigDRC();
    ~sigDRC();
    /* virtual functions */
    void init(int mode);
    void process(float *ibuf, float *obuf, int num_frames, int num_chn);
};

#endif
