# Makefile.am par Mael Valais - 2014
# Nécessaire à automake

# Ce fichier contient les noms des fichiers qui permettent la compilation Autotools

# Les fichiers Makefile.am (vides) dans tous les sous-dossiers sont obligatoires mais
# j'ai décidé de tout mettre dans celui-ci pour simplifier (grâce à subdir-objects dans 
# configure.ac)

# CONCERNANT Qt (à travers autotroll.m4 et autotroll.mk) : 
# - include autotroll.mk permet d'ajouter les règles implicites pour compiler 
#		les .ui en _ui.h, les .moc en .moc.cpp...
# - BUILT_SOURCES= contient tous les fichiers .ui ou .moc ou .rcc qui devront être
# 		compilés par les outils uic, moc ou rcc. Si on met mainwindow_ui.h dans
#		prog_SOURCES par exemple, il faudra qu'on écrive : 
#		BUILT_SOURCES=mainwindow_ui.h

# Appel au makefile pour les moc, uic, rcc 
# provenant de autotroll
include ../autotroll.mk

# Pour que aclocal puisse trouver les fichiers .m4
ACLOCAL_AMFLAGS = -I ../m4

# Les headers
noinst_HEADERS = supervclimso.h pointscomm.h ListesCommandesReponsesCamerOA.h \
	ListesCommandesReponsesTerminOA.h WidgetPoseCentrage.h WidgetPoseImage.h calculsastronomiques.h \
	WidgetSoleilHeliographique.h WidgetRoueOuvertureCLIMSO.h WidgetRoueFiltresC2.h trameimagecameroa.h \
	trameimageterminoa.h ListesCommandesReponsesRobOA.h

# Nom des executables à compiler
bin_PROGRAMS = supervclimso

# Fichiers source (.c, .cpp, .h ou tout autre fichier utile aux étapes de compilation)
supervclimso_SOURCES = \
		main.cpp supervclimso.cpp pointscomm.cpp \
		WidgetPoseCentrage.cpp WidgetPoseImage.cpp calculsastronomiques.cpp \
		WidgetSoleilHeliographique.cpp WidgetRoueOuvertureCLIMSO.cpp WidgetRoueFiltresC2.cpp\
		$(BUILT_SOURCES)

# -Ox correspond au mode d'optimisation. -O2 est une bonne optimisation.
# -O0 désactive l'optimisation  	

supervclimso_CXXFLAGS = $(QT_CXXFLAGS) $(AM_CXXFLAGS)
supervclimso_CFLAGS = $(QT_CFLAGS) $(AM_CFLAGS)
supervclimso_CPPFLAGS = $(QT_CPPFLAGS) $(AM_CPPFLAGS) -I/usr/include/kde
supervclimso_LDFLAGS = $(QT_LDFLAGS) $(LDFLAGS) 
supervclimso_LDADD = $(QT_LIBS) $(LDADD) -lcfitsio -lssl -lcrypto -L/usr/lib/kde -lkdeui -lkdecore


# Fichiers qui devront être compilés par uic ou moc avant la compilation
# Voir CONCERNANT Qt au dessus
BUILT_SOURCES=\
	WidgetSoleilHeliographique.moc.cpp WidgetRoueOuvertureCLIMSO.moc.cpp WidgetRoueFiltresC2.moc.cpp\
	WidgetPoseCentrage.moc.cpp WidgetPoseImage.moc.cpp\
	supervclimso.moc.cpp

# Règle perso car la règle présente dans autotroll.mk (%ui_.h: %.ui) ne marche pas
# pour produire du src/ui_blabla.h (car il faut deux wildcards, genre %ui_%.h)
#src/ui_%.h: src/%.ui
#	$(UIC) $< -o $@

# NOTE sur $(srcdir) et $(includedir)
# il faudrait théoriquement préfixer tous les fichiers source par $(srcdir)
# et tous les fichiers header par $(includedir)
