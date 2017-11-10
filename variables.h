#define PERIOD 10000
#define NMAX 5000
#define a 1.0
#define NXMAX 500
#define MAXFRAMES 10000
#define MAXRUN 20
#define MAXPARTICLETYPE 10

extern int N,Nb,Nd,bondGroup[NMAX*2],dihedralGroup[NMAX*4];
//N:#particles, Nb:#bonds, Nd:#dihedrals
extern float position[NMAX*3];
extern uint32_t particleID[NMAX];
extern char particleType[MAXPARTICLETYPE][2];
extern double h_width[MAXFRAMES][NXMAX];
extern double h_bb[MAXFRAMES][NXMAX];
extern int nx,NY,RUN,STEPS,LEN,FRAMES;
extern double KAPPA,EPSILON;

