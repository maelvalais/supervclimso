# set the include path for X, qt and KDE
INCLUDES = $(all_includes)

# these are the headers for your project
noinst_HEADERS = supervclimso.h pointscomm.h ListesCommandesReponsesCamerOA.h \
	ListesCommandesReponsesTerminOA.h WidgetPoseCentrage.h WidgetPoseImage.h calculsastronomiques.h \
	WidgetSoleilHeliographique.h WidgetRoueOuvertureCLIMSO.h WidgetRoueFiltresC2.h trameimagecameroa.h \
	trameimageterminoa.h ListesCommandesReponsesRobOA.h

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(EXTRACTRC) `find . -name \*.ui -o -name \*.rc` > rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/supervclimso.pot

KDE_ICON = AUTO

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = supervclimso

# the application source, library search path, and link libraries
supervclimso_SOURCES = \
		main.cpp supervclimso.cpp pointscomm.cpp \
		WidgetPoseCentrage.cpp WidgetPoseImage.cpp calculsastronomiques.cpp \
		WidgetSoleilHeliographique.cpp WidgetRoueOuvertureCLIMSO.cpp WidgetRoueFiltresC2.cpp\
		WidgetSoleilHeliographique.moc.cpp WidgetRoueOuvertureCLIMSO.moc.cpp WidgetRoueFiltresC2.moc.cpp\
		WidgetPoseCentrage.moc.cpp WidgetPoseImage.moc.cpp

supervclimso_CPPFLAGS = -I/usr/include/kde
supervclimso_LDFLAGS = $(KDE_RPATH) $(all_libraries) -L/usr/lib/kde
supervclimso_LDADD = -lcfitsio -lssl $(LIB_KDEUI) -lcrypto 

# this is where the desktop file will go 
shelldesktopdir   = $(kde_appsdir)/Utilities
shelldesktop_DATA = supervclimso.desktop

# this is where the shell's XML-GUI resource file goes
shellrcdir   = $(kde_datadir)/supervclimso
shellrc_DATA = supervclimsoui.rc

