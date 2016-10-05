# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "gnuplot_i.h"

# define SLEEP_LGTH  1
# define NPOINTS     50

int main ( int argc, char *argv[] );
void slow_print ( char *s );

/******************************************************************************/

int main ( int argc, char *argv[] ) 

/******************************************************************************/
/*
  Purpose:

    MAIN is the main program for ANIM.

  Modified:

    24 June 2011
*/
{
  double d[NPOINTS];
  dpoint dp[NPOINTS];
  gnuplot_ctrl *h1;
  gnuplot_ctrl *h2;
  gnuplot_ctrl *h3;
  gnuplot_ctrl *h4;
  int i;
  int j;
  double x[NPOINTS];
  double y[NPOINTS];

  printf ( "\n" );
  printf ( "EXAMPLE:\n" );
  printf ( "  C++ version.\n" );
  printf ( "  Demonstrate how a running C++ program can produce plots\n" );
  printf ( "  through GNUPLOT, by invoking the GNUPLOT_I interface library.\n" );
/*
  Initialize the gnuplot handle
*/
  h1 = gnuplot_init();

  if ( h1 == NULL )
  {
    printf ( "\n" );
    printf ( "EXAMPLE - Fatal error!\n" );
    printf ( "  GNUPLOT is not available in your path.\n" );
    exit ( 1 );
  }
/* 
  Slopes 
*/    
  gnuplot_setstyle(h1, "lines");
    
  slow_print("*** plotting slopes\n");
  slow_print("y = x\n");
  gnuplot_plot_slope(h1, 1.0, 0.0, "unity slope");
  sleep(SLEEP_LGTH);

  
  return 0;
}
/******************************************************************************/

void slow_print ( char *s )

/******************************************************************************/
{
  int i;

  for ( i = 0; i < ( int ) strlen ( s ); i++ )
  {
    printf ( "%c", s[i] );
    fflush ( stdout );
    usleep ( 100000 );
  }
  return;
}

