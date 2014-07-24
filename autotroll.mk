# Makerules.
# This file is part of AutoTroll.
# Copyright (C) 2006  Benoit Sigoure.
#
# AutoTroll is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
# USA.

 # ------------- #
 # DOCUMENTATION #
 # ------------- #

# See autotroll.m4 :)

#NOTE MV: Il s'agit de règles implicites avec double suffixe
# .ui.ui.h: signifie %.ui: %.ui.h

SUFFIXES = .moc.cpp .moc.cc .moc.cxx .moc.C .h .hh \
           .ui .ui.h .ui.hh \
           .qrc .qrc.cpp .qrc.cc .qrc.cxx .qrc.C\
           _ui.h

# --- #
# MOC #
# --- #

.h.moc.cpp:
	$(MOC) $< -o $@

# --- #
# UIC #
# --- #

.ui.ui.hh:
	$(UIC) $< -o $@

#.ui.ui.h:
#	$(UIC) $< -o $@
%_ui.h: %.ui
	$(UIC) $< -o $@

# --- #
# RCC #
# --- #

.qrc.qrc.cpp:
	$(RCC) -name `echo "$<" | sed 's/\.qrc$$//'` $< -o $@

.qrc.qrc.cc:
	$(RCC) -name `echo "$<" | sed 's/\.qrc$$//'` $< -o $@

.qrc.qrc.cxx:
	$(RCC) -name `echo "$<" | sed 's/\.qrc$$//'` $< -o $@

.qrc.qrc.C:
	$(RCC) -name `echo "$<" | sed 's/\.qrc$$//'` $< -o $@

DISTCLEANFILES = $(BUILT_SOURCES)
