#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include<strings.h>
#include<stdarg.h>//Needed for the function print_and_exit()
#define M_PI 3.14159265358979323846

#define PERIOD 10000
#define NXMAX 2000
#define MAXFRAMES 20000

double hgt_profile[MAXFRAMES][NXMAX];

int NX,NY,RUNS,steps,frames;
double KAPPA;

void print_and_exit(char *, ...); //Print out an error message and exits

 
int main(int argc, char **argv)
{

   FILE *Fin,*pf;
   char data_file[1024],profile_file[1024];
   int i,RUNNUM,valid_runs,flag;
   int nx,total_frames; //read from the bin files
   switch (argc){
   case 7:
       NX = atoi(argv[1]);
       NY = atoi(argv[2]);
       KAPPA = atof(argv[3]);
       steps = atoi(argv[4]);
       RUNNUM = atoi(argv[5]);
       flag = atoi(argv[6]);
       break;
   default:
       print_and_exit("Usage Pass command line arguments:NX NY Kappa steps RUNNUM(pick from validruns.log file) flag(0-bb 1-width)\n");
   }

   frames = steps/PERIOD;

   if(flag == 1)
   {
   	sprintf(data_file,"../Sim_dump_ribbon/L%d/W%d/k%.1f/r%d/width.bin",NX,NY,KAPPA,RUNNUM);
   	//printf("%s\n",data_file);
   }
   else if (flag == 0)
	sprintf(data_file,"../Sim_dump_ribbon/L%d/W%d/k%.1f/r%d/backbone.bin",NX,NY,KAPPA,RUNNUM);
   else
	print_and_exit("Choose a valid flag value 1 - width average 0 - backbone\n");

   if(NULL==(Fin=fopen(data_file,"rb")))
   	print_and_exit("I could not open binary file with ribbon height averaged over width data%s\n",data_file);

  //Output file with profile data
  sprintf(profile_file,"L%d_W%d_k%.1f_R%d.dat",NX,NY,KAPPA,RUNNUM);
  printf("Profile data written to File: %s\n",profile_file);

  pf = fopen(profile_file, "w");
  if (pf == NULL)
   {
        print_and_exit("Could Not Open File to write profile data");
   }

   //We read the data file
  fread(&nx,sizeof(int),1,Fin);
  fread(&total_frames,sizeof(int),1,Fin);
  if(nx != NX || total_frames != frames)
	print_and_exit("nx and total frames in bin file dont reconcile with the system parameters provided\n");
	
  for(int i=0;i<total_frames;i++)
  {
        for(int j=0;j<nx;j++)
        {
                fread(&hgt_profile[i][j],sizeof(double),1,Fin);
        }
  }
  fclose(Fin);

  for(int i=0;i<nx;i++)
  {
	fprintf(pf,"%d\t",i);
	for(int j=0;j<=total_frames;j++)
	{
		fprintf(pf,"%.8f\t",hgt_profile[j][i]);
	}
	fprintf(pf,"\n");
  }

  fclose(pf);

   return 0;   
}

void print_and_exit(char *format, ...)
{
    va_list list;

    va_start(list,format);
    vprintf(format,list);
    va_end(list);
    exit(1);
}

