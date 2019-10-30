//    ****************************************************************************
//                cairo3.c     
//   image window   with GTK3 
// 
//   by windy
//    ****************************************************************************

#include <gtk/gtk.h>
#include <stdlib.h>

static cairo_surface_t * surface=NULL;

GdkPixbuf *offscreen; // offscreen
int        width=640;		// screen width
int        height=480;		// screen height

// ******************* init_drawing_area ****************************************
static gboolean init_drawing_area(GtkWidget *widget , GdkEventConfigure *event, gpointer data) {

	offscreen = gdk_pixbuf_new( GDK_COLORSPACE_RGB, FALSE, 8, width ,height);
	if( offscreen ==NULL)
		{
		 g_print("Error Create GdkPixbuf \n");
		 exit(1);
		}
	
	int n_ch = gdk_pixbuf_get_n_channels( offscreen);
	int row  = gdk_pixbuf_get_rowstride( offscreen);

	g_print("n_ch=%d  row=%d \n",n_ch , row);
	guchar *pixels;
	for(int h =0 ; h< height ; h++)
		{
		for(int w=0; w<width ; w++)
			{
			 	pixels = gdk_pixbuf_get_pixels(offscreen)+h*row+ w *n_ch;
				pixels[0] = rand()%255;			// random color pixels
				pixels[1] = rand()%255;
				pixels[2] = rand()%255;
			}
		}

	surface = cairo_image_surface_create( CAIRO_FORMAT_RGB24 , width ,height);
	cairo_t *cr = cairo_create(surface);

	gdk_cairo_set_source_pixbuf( cr, offscreen ,0,0);
	cairo_paint(cr);
	cairo_destroy(cr);

	return TRUE;
}

// ****************** draw callback *************************************
static gboolean draw_cb( GtkWidget *widget, cairo_t * cr , gpointer data)
{
	cairo_set_source_surface( cr, surface,0,0);
	cairo_paint(cr);

	return FALSE;
}

// ****************** close window *************************************
static void close_window(void)
{
	if(surface) 
		{
		cairo_surface_destroy( surface);
		}
	gtk_main_quit();
}


int main(int argc, char *argv[])
{
	// init gtk
	gtk_init( &argc, &argv);

	// window
	GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title( GTK_WINDOW(window), "cairo 3");
	g_signal_connect( window, "destroy", G_CALLBACK( close_window), NULL);

	// create frame
	GtkWidget *frame = gtk_frame_new(NULL);
	gtk_container_add( GTK_CONTAINER(window) ,frame);

	// create drawing area
	GtkWidget *da = gtk_drawing_area_new();
	gtk_widget_set_size_request( da, width ,height);
	gtk_container_add( GTK_CONTAINER( frame),da);

	// event
	g_signal_connect(da, "draw",G_CALLBACK(draw_cb), NULL);			// re-draw event
	g_signal_connect(da, "configure-event",G_CALLBACK(init_drawing_area),NULL); // change size event
	
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
