/*
 *   File name:	kdirstatmain.cpp
 *   Summary:	Main program for KDirStat
 *   License:	GPL - See file COPYING for details.
 *
 *   Author:	Stefan Hundhammer <sh@suse.de>
 *		Parts auto-generated by KDevelop (sorry for the mess)
 *
 *   Updated:	2001-08-16
 *
 *   $Id: kdirstatmain.cpp,v 1.2 2001/08/16 14:36:08 hundhammer Exp $
 *
 *   $Log: kdirstatmain.cpp,v $
 *   Revision 1.2  2001/08/16 14:36:08  hundhammer
 *   New: Iterator classes
 *   Fixed segfault upon reading very flat dir trees
 *   Added 'CREDITS' file
 *   Added 'Credits' section to 'About' box
 *
 *   Revision 1.1.1.1  2001/06/29 16:37:49  hundhammer
 *   Initial import
 *
 *
 */



#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>
#include <kdebug.h>

#include "kdirstatapp.h"


static const char *description =
	I18N_NOOP("KDirStat - Directory statistics.\n"
		  "\n"
		  "Shows where all your disk space has gone\n"
		  "and helps you clean it up.");


static KCmdLineOptions options[] =
{
    { "+[Dir/URL]", I18N_NOOP("Directory or URL to open"), 0 },
    { 0, 0, 0 }
};

int main(int argc, char *argv[])
{

    KAboutData aboutData( "kdirstat", I18N_NOOP("KDirStat"),
			  VERSION, description, KAboutData::License_GPL,
			  "(c) 2001, Stefan Hundhammer", 0, 0, 
			  "sh@suse.de" );
    
    aboutData.addAuthor( "Stefan Hundhammer",
			 I18N_NOOP("Core engine, application, cleanup actions"),
			 "sh@suse.de", "http://www.suse.de/~sh/kdirstat/" );
    
    aboutData.addAuthor( "Alexander Rawass", I18N_NOOP( "Tree maps" ),
			 "alexannika@users.sourceforge.net" );
    
    aboutData.addCredit( I18N_NOOP( "All the people who worked on SequoiaView" ),
			 I18N_NOOP( "for giving us the inspiration just how useful treemaps really can be - \n"
				    "even though that program runs on that 'other' OS only...\n"
				    ";-) \n"),
			 0,	// e-mail
			 "http://www.win.tue.nl/sequoiaview" );
    
    aboutData.addCredit( I18N_NOOP( "Jarke J. van Wijk and Huub van de Wetering" ),
			 I18N_NOOP( "for their papers about treemaps.\n" ),
			 "vanwijk@win.tue.nl",
			 "http://www.win.tue.nl/~vanwijk/" );
    
    aboutData.addCredit( "Ben Shneiderman",
			 I18N_NOOP( "for his ingenious idea of treemaps -\n"
				    "a truly intuitive way of visualizing tree contents." ),
			 "",	// E-Mail
			 "http://www.cs.umd.edu/hcil/treemaps/" );
    
    KCmdLineArgs::init( argc, argv, &aboutData );
    KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

    KApplication app;

    if ( app.isRestored() )
    {
	RESTORE(KDirStatApp);
    }
    else
    {
	KDirStatApp *kdirstat = new KDirStatApp();
	kdirstat->show();

	KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

	if ( args->count() )
	{
	    // Process command line arguments as URLs or paths to scan

	    KURL url = args->arg( 0 );		// Maybe a valid URL was passed (with protocol!)?

	    if ( url.isMalformed() )		// No? Maybe it's just a path spec.
	    {
		url = KURL();			// Clear the URL
		url.setPath( args->arg( 0 ) );	// and use just its path part
	    }

	    kdDebug() << "Opening " << url.url() << endl;
	    kdirstat->openURL( url );
	}
	
	args->clear();
    }

    kdDebug() << "Entering main loop" << endl;

    return app.exec();
}

