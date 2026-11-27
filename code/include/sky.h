#ifndef SKY_H
#define SKY_H

#include "moby.h"
struct sky_sprite;

struct sky_tex {
    unsigned long tex0;
    unsigned short tex_ofs;
    unsigned short pal_ofs;
    short u_log;
    short v_log;
};

struct sky_cluster {
    Vec4 bsphere;
    void *data;
    short vert_cnt;
    short tri_cnt;
    short vert_ofs;
    short st_ofs;  // Colour data for Gouraud shells.
    short tri_ofs;
    short data_size;
};

// Novalis uses full words for the cluster count and Gouraud flag.
struct sky_shell {
    int cluster_cnt;
    int gouraud;
    int unk_08[2];
    sky_cluster clusters[0];
};

struct SKY {
    int pad;
    short clear_screen;
    short shell_cnt;
    short sprite_cnt;
    short sprite_max;
    short tex_cnt;
    short fx_cnt;
    sky_tex *tex_defs;
    void *tex_data;
    char *fx_list;
    sky_sprite *sprites;
    sky_shell *shells[8];
};

extern SKY *Sky;
extern Mtx4 outMatrix;

void SkyDrawShell(int ishell);
void SkyDrawShellTextured(sky_shell *shell);
void SkyDrawShellGouraud(sky_shell *shell);

void SkyBsphereCheck(sky_cluster *clusters, int cluster_count, unsigned char *visible);
int SkyProcessVerts(void *source, void *destination, int vertex_count);
void SkyDrawClusterTextured(int triangle_count, void *triangles, void *texcoords, void *vertices);
void SkyDrawClusterGouraud(int triangle_count, void *triangles, void *colors, void *vertices);

void SetupSkyGifPaging(void);
void DoSkyGifPaging(void);

// Per-level sky setup.
void SkyLevelNone(void);
void SkyLevel_01(void);

void InitSky(void);

#endif
