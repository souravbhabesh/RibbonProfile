#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "stdint.h"
#include "gsd.h"
#include "variables.h"
#include "gsd_read.h"
#include "analyze.h"


int nx,NY,LEN,RUN;
double KAPPA,EPSILON;
int STEPS,FRAMES;


int main(int argc, char **argv)
{
  FILE *pf;
  char init_strip[256],trajectory_file[256],profile_file[256];
  int frame_cnt=0;
  int START_FRAME,END_FRAME,FLAG;

   switch (argc){
     case 9:
       sscanf(argv[1],"%d",&nx);    
       sscanf(argv[2],"%d",&NY);
       sscanf(argv[3],"%lf",&KAPPA);
       sscanf(argv[4],"%d",&RUN);
       sscanf(argv[5],"%d",&STEPS); 
       sscanf(argv[6],"%d",&START_FRAME);
       sscanf(argv[7],"%d",&END_FRAME);
       sscanf(argv[8],"%d",&FLAG);
       break;
     default:
       print_and_exit("Usage: %s nx NY KAPPA RUN STEPS START_FRAME END_FRAME FLAG(0-bb,1-yavg)\n",
           argv[0]);
   }

  printf("nx = %d\n",nx);

  FRAMES=STEPS/PERIOD;

  if(END_FRAME > FRAMES)
	print_and_exit("END_FRAME cannot be greater than FRAMES\n");

  int initialize();

  // Init_strip.gsd filepath
  sprintf(init_strip,"../Sim_dump_ribbon/init_strip_L%d_W%d.gsd",nx,NY);
  printf("Init_strip.gsd : %s\n",init_strip);

  load_gsd(init_strip,0); 
  printf("nx = %d\n",nx);

  // Trajectory.gsd filepath
  sprintf(trajectory_file,"../Sim_dump_ribbon/L%d/W%d/k%.1f/r%d/traj_thermal.gsd",nx,NY,KAPPA,RUN);

  //Output file with profile data
  sprintf(profile_file,"L%d_W%d_k%.1f_R%d.dat",nx,NY,KAPPA,RUN);
  printf("Profile data written to File: %s\n",profile_file);

  pf = fopen(profile_file, "w");
  if (pf == NULL)
   {
        print_and_exit("Could Not Open File to write profile data");
   }


  frame_cnt=START_FRAME;
  //Looping through frames from a START to END frame
  for(int frames=START_FRAME+FRAMES/2;frames<=END_FRAME+FRAMES/2;frames++)
  {
	load_gsd(trajectory_file,frames);	
	width_hgt(frame_cnt);
	bb_hgt(frame_cnt);
	frame_cnt++;
  }

  if(FLAG == 0)
  {
	  for(int i=0;i<nx;i++)
	  {
		fprintf(pf,"%d\t",i);	
		for(int j=START_FRAME;j<=END_FRAME;j++)
		{
			fprintf(pf,"%.8f\t",h_bb[j][i]);
		}
		fprintf(pf,"\n");
	  }
  }

 else
 {
	for(int i=0;i<nx;i++)
          {
                fprintf(pf,"%d\t",i);
                for(int j=START_FRAME;j<=END_FRAME;j++)
                {
                        fprintf(pf,"%.8f\t",h_width[j][i]);
                }
                fprintf(pf,"\n");
          }
 }

  return 0;
}
