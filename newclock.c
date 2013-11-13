#include <cairo.h>
#include <gtk/gtk.h>
#include <time.h>
#include <math.h>


int c;
int mode;


typedef struct pars_{
int sec;
int hour;
int minute;
}pars;

pars gettime()
{
 pars p;
 time_t t;
 struct tm *tm_p;
 t=time(NULL);
 tm_p=localtime(&t);
 p.sec=tm_p->tm_sec;
 p.minute=tm_p->tm_min;
 p.hour=tm_p->tm_hour;
 
 return p;
}


static gboolean on_expose_event(GtkWidget *widget,GdkEventExpose *event, gpointer data)
{
  cairo_t *cr;

  cr = gdk_cairo_create(widget->window);
  if(c==0){
  pars p;
  p=gettime();
  if((mode==12)&&(p.hour>12))p.hour=p.hour-12;
  if((mode==12)&&(p.hour==0))p.hour=12;
  cairo_move_to(cr, 50, 100);
  cairo_set_font_size(cr, 20);
  char c[9];
  if(p.hour<10 && p.minute<10 && p.sec<10) sprintf(c,"0%d:0%d:0%d",p.hour,p.minute,p.sec);
  if(p.hour<10 && p.minute<10 && p.sec>9) sprintf(c,"0%d:0%d:%d",p.hour,p.minute,p.sec);

  if(p.hour<10 && p.minute>9 && p.sec<10) sprintf(c,"0%d:%d:0%d",p.hour,p.minute,p.sec);
  if(p.hour<10 && p.minute>9 && p.sec>9) sprintf(c,"0%d:%d:%d",p.hour,p.minute,p.sec);

  if(p.hour>9 && p.minute<10 && p.sec<10) sprintf(c,"%d:0%d:0%d",p.hour,p.minute,p.sec);
  if(p.hour>9 && p.minute<10 && p.sec>9) sprintf(c,"%d:0%d:%d",p.hour,p.minute,p.sec);

  if(p.hour>9 && p.minute>9 && p.sec<10) sprintf(c,"%d:%d:0%d",p.hour,p.minute,p.sec);
  if(p.hour>9 && p.minute>9 && p.sec>9) sprintf(c,"%d:%d:%d",p.hour,p.minute,p.sec);
  
  cairo_show_text(cr,c);
  }

  else if(c==1){
int h[24],hh1,hh2,mm2,mm1,ss1,ss2,i,j,k=0;
pars p;
p=gettime();
//process to create h1,h2...
hh2=p.hour%10;
hh1=p.hour/10;
mm2=p.minute%10;
mm1=p.minute/10;
ss2=p.sec%10;
ss1=p.sec/10;

//process to put in arrays

h[0]=-1;
h[1]=-1;
h[8]=-1;
h[16]=-1;

h[3]=hh1&1;
h[2]=(hh1/2)&1;
h[7]=hh2&1;
h[6]=(hh2/2)&1;
h[5]=(hh2/4)&1;
h[4]=(hh2/8)&1;
h[11]=mm1&1;
h[10]=(mm1/2)&1;
h[9]=(mm1/4)&1;
h[15]=mm2&1;
h[14]=(mm2/2)&1;
h[13]=(mm2/4)&1;
h[12]=(mm2/8)&1;
h[19]=ss1&1;
h[18]=(ss1/2)&1;
h[17]=(ss1/4)&1;
h[23]=ss2&1;
h[22]=(ss2/2)&1;
h[21]=(ss2/4)&1;
h[20]=(ss2/8)&1;

int arrx[6]={16,42,87,113,158,184};
int arry[4]={90,116,142,168};
for(i=0;i<6;i++) {
	for(j=0;j<4;j++) {
		if(h[k]!=-1) {
            if(h[k]==0){
                cairo_set_source_rgba(cr,0.5,0.5,0.5, 0.8);
                cairo_arc(cr,arrx[i],arry[j],10, 0 , 2 * M_PI) ;
                cairo_fill(cr);
                cairo_stroke(cr);}
				else if(h[k]==1) {
				cairo_set_source_rgba(cr,0,0,0,0.8);
				cairo_arc(cr,arrx[i],arry[j],10, 0 , 2 * M_PI) ;
				cairo_fill(cr);
				cairo_stroke(cr);}
			}
			k++;
		}
	}	
}
  else if(c==2) {
	float i=0;
	for(i=0;i<4;i++) {
		cairo_move_to(cr,100+94*cos(i*M_PI/2),100+94*sin(i*M_PI/2));
		cairo_line_to(cr,100+(94-25)*cos(i*M_PI/2),100+(94-25)*sin(i*M_PI/2));
		cairo_stroke(cr);
	}

	for(i=0;i<12;i++) {
		cairo_move_to(cr,100+94*cos(i*M_PI/6),100+94*sin(i*M_PI/6));
		cairo_line_to(cr,100+(94-10)*cos(i*M_PI/6),100+(94-10)*sin(i*M_PI/6));
		cairo_stroke(cr);
	}
	
	for(i=0;i<60;i++) {
		cairo_move_to(cr,100+94*cos(i*M_PI/30),100+94*sin(i*M_PI/30));
		cairo_line_to(cr,100+(94-4)*cos(i*M_PI/30),100+(94-4)*sin(i*M_PI/30));
		cairo_stroke(cr);
	}


	cairo_set_line_width(cr,3);
	//cairo_arc(cr,200,200, lesser / 4.0, 0.0, 2.0 * 3.14);
	//cairo_set_source_rgba(cr,1, 0.2, 0.2, 0);
	cairo_arc(cr,100, 100,94, 0 , 2 * M_PI) ;
	
	//cairo_fill(cr);
	//cairo_set_source_rgb(cr,0,0,0);
	//cairo_arc(cr,100, 100,94, 0 , 2 * M_PI) ;
	cairo_stroke(cr);

	pars p;
	p=gettime();
	cairo_set_line_width(cr,2);
	cairo_set_source_rgb(cr,0.8,0,0);
	cairo_move_to(cr,100, 100);
        cairo_line_to(cr,100+60*cos(((p.sec*2*M_PI)/60 - M_PI/2)),100+60*sin(((p.sec*2*M_PI)/60 - M_PI/2)));
	cairo_stroke(cr);

	cairo_set_line_width(cr,2);
	cairo_set_source_rgb(cr,0,0.8,0);
	cairo_move_to(cr,100, 100);
        cairo_line_to(cr,100+45*cos(((p.minute*2*M_PI)/60 - M_PI/2)),100+45*sin(((p.minute*2*M_PI)/60 - M_PI/2)));
	cairo_stroke(cr);

	cairo_set_line_width(cr,2);
	cairo_set_source_rgb(cr,0,0,0.8);
	cairo_move_to(cr,100, 100);
        cairo_line_to(cr,100+35*cos(((p.hour*2*M_PI)/12 - M_PI/2)),100+35*sin(((p.hour*2*M_PI)/12 - M_PI/2)));
	cairo_stroke(cr);

        char cc[3];
        cc[2]=0;
	    cairo_set_source_rgb(cr,0,0,0);
        cairo_move_to(cr,88.5,49);
        cairo_set_font_size(cr, 16);
        if(p.hour>12){cc[0]='P';cc[1]='M';}
        else {cc[0]='A';cc[1]='M';}
        cairo_show_text(cr,cc);       


}

  
  cairo_destroy(cr);

  return FALSE;
}

static gboolean time_handler(GtkWidget *widget) {
  if (widget->window== NULL) return FALSE;



  gtk_widget_queue_draw(widget);
  return TRUE;
}


static gboolean change_c(gpointer data)
{	
 if(c==0)c=1;	
 else if(c==1)c=2;
 else if(c==2)c=0;
 return TRUE;

}

static gboolean clock_mode(gpointer data)
{
 if(mode==24)mode=12;
 else mode=24;
}

int
main (int argc, char *argv[])
{
  c=0;
  mode=24;
  GtkWidget *window;
  GtkWidget *darea;
  GtkWidget *calendar;
  GtkWidget *fixed;
  GtkWidget *frame1;
  GtkWidget *frame2;
  GtkWidget *button;
  gint day;
  day=13;
  

  gtk_init(&argc, &argv);
  
  calendar=gtk_calendar_new();
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  

  darea = gtk_drawing_area_new();
  

  frame1 = gtk_frame_new (NULL);
  frame2 = gtk_frame_new (NULL);
  gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_IN);
  gtk_frame_set_shadow_type (GTK_FRAME (frame2), GTK_SHADOW_IN);
  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);
  button = gtk_button_new_with_label("12Hour <--> 24Hour");
  gtk_fixed_put(GTK_FIXED(fixed), button, 0, 200);
  gtk_widget_set_size_request(button, 200, 30);
  gtk_fixed_put(GTK_FIXED(fixed), frame1, 0, 0);
  gtk_fixed_put(GTK_FIXED(fixed), frame2, 200, 0);
  gtk_container_add (GTK_CONTAINER (frame1),darea);
  gtk_widget_set_size_request (darea, 200,200);
  gtk_container_add (GTK_CONTAINER (frame2),calendar);
  gtk_widget_set_size_request (calendar,200,200);
  
  g_signal_connect(button,"clicked",G_CALLBACK(clock_mode),NULL);
  g_signal_connect(darea, "expose-event",G_CALLBACK(on_expose_event), NULL);
  g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect (darea, "button-press-event",G_CALLBACK (change_c), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
  gtk_widget_set_size_request (darea, 200,200);

  gtk_window_set_title(GTK_WINDOW(window), "lol'C'lock");
  gtk_widget_set_events (darea, gtk_widget_get_events (darea)
                             | GDK_BUTTON_PRESS_MASK);
  g_timeout_add(300, (GSourceFunc) time_handler, (gpointer) window);
  gtk_widget_show_all(window);
  time_handler(window);

  gtk_main();

  return 0;
}
