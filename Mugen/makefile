
OBJDIR=C:\TMP\YSCLASS

.SUFFIXES: .c .cpp .obj

LIBEXE = lib.exe
LIBFLAGS = /NOLOGO

CC = cl.exe

PROJECTNAME=YSCLASS
PDBFILE=$(PROJECTNAME).pdb
PCHFILE=$(PROJECTNAME).pch

CFLAGS=/nologo /W3 /Zi /O2 /D "WIN32" /D "_WINDOWS" /c /Fd$(OBJDIR)\$(PDBFILE) /Fp$(OBJDIR)\$(PCHFILE) /wd4996

TARGET=$(PROJECTNAME).lib
REALTARGET = $(USERLIBDIR)\$(TARGET)


MV = mv
CP = copy
USERINCDIR = C:\INCLUDE
USERLIBDIR = C:\LIB

all : envCheck makefile $(REALTARGET)

cln :
	del $(OBJDIR)\*.obj
	del $(OBJDIR)\*.lib

makefile : makemake
	makemake.exe
	@echo "MAKEFILE IS REFRESHED.  RE-RUN NMAKE"

inst : envCheck
	$(CP) $(OBJDIR)\$(TARGET) $(USERLIBDIR)
	$(CP) $(OBJDIR)\$(PDBFILE) $(USERLIBDIR)
	$(CP) ysbi\*.h $(USERINCDIR)
	$(CP) *.h $(USERINCDIR)

envCheck :
	isX86env.exe




SRC0=ysprintf.cpp ysclassmgr.cpp ysbase.cpp ysgeometry.cpp ysmath.cpp ysmatrix.cpp ysmatrix3x3.cpp ysmatrix4x4.cpp ysreldir.cpp ysargs.cpp ysadvgeometry.cpp yswizard.cpp ysproperty.cpp ysshellutil.cpp yssword.cpp ysequation.cpp ysadvgeometryx.cpp ysstring.cpp yspixelmap.cpp ysfilename.cpp ysshell2d.cpp ysclip.cpp ysshellsearch.cpp ysshellblend.cpp ysshelllattice.cpp yshash.cpp yskdtree.cpp yspredefined.cpp ysveci.cpp ysshellblend2.cpp ysexception.cpp yslist.cpp

OBJ0=$(OBJDIR)/ysprintf.obj $(OBJDIR)/ysclassmgr.obj $(OBJDIR)/ysbase.obj $(OBJDIR)/ysgeometry.obj $(OBJDIR)/ysmath.obj $(OBJDIR)/ysmatrix.obj $(OBJDIR)/ysmatrix3x3.obj $(OBJDIR)/ysmatrix4x4.obj $(OBJDIR)/ysreldir.obj $(OBJDIR)/ysargs.obj $(OBJDIR)/ysadvgeometry.obj $(OBJDIR)/yswizard.obj $(OBJDIR)/ysproperty.obj $(OBJDIR)/ysshellutil.obj $(OBJDIR)/yssword.obj $(OBJDIR)/ysequation.obj $(OBJDIR)/ysadvgeometryx.obj $(OBJDIR)/ysstring.obj $(OBJDIR)/yspixelmap.obj $(OBJDIR)/ysfilename.obj $(OBJDIR)/ysshell2d.obj $(OBJDIR)/ysclip.obj $(OBJDIR)/ysshellsearch.obj $(OBJDIR)/ysshellblend.obj $(OBJDIR)/ysshelllattice.obj $(OBJDIR)/yshash.obj $(OBJDIR)/yskdtree.obj $(OBJDIR)/yspredefined.obj $(OBJDIR)/ysveci.obj $(OBJDIR)/ysshellblend2.obj $(OBJDIR)/ysexception.obj $(OBJDIR)/yslist.obj

SRC1=ysshell.cpp ysshellstl.cpp

OBJ1=$(OBJDIR)/ysshell.obj $(OBJDIR)/ysshellstl.obj

SRC2=

OBJ2=
$(REALTARGET) : $(OBJDIR)/$(TARGET)
		$(CP) $(OBJDIR)\$(PDBFILE) $(USERLIBDIR)
		$(CP) ysbi\*.h $(USERINCDIR)
		$(CP) *.h $(USERINCDIR)
		$(CP) $(OBJDIR)\$(TARGET) $(USERLIBDIR)

$(OBJDIR)/$(TARGET) : $(OBJ0) $(OBJ1)
		$(LIBEXE) @<<
	$(LIBFLAGS) /OUT:"$(OBJDIR)/$(TARGET)" $(OBJ0) $(OBJ1)
<<







$(OBJDIR)/ysprintf.obj : ysprintf.cpp
	cl /c ysprintf.cpp /Fo$(OBJDIR)/ysprintf.obj $(CFLAGS)


$(OBJDIR)/ysclassmgr.obj : ysclassmgr.cpp
	cl /c ysclassmgr.cpp /Fo$(OBJDIR)/ysclassmgr.obj $(CFLAGS)


$(OBJDIR)/ysbase.obj : ysbase.cpp
	cl /c ysbase.cpp /Fo$(OBJDIR)/ysbase.obj $(CFLAGS)


$(OBJDIR)/ysgeometry.obj : ysgeometry.cpp
	cl /c ysgeometry.cpp /Fo$(OBJDIR)/ysgeometry.obj $(CFLAGS)


$(OBJDIR)/ysmath.obj : ysmath.cpp
	cl /c ysmath.cpp /Fo$(OBJDIR)/ysmath.obj $(CFLAGS)


$(OBJDIR)/ysmatrix.obj : ysmatrix.cpp
	cl /c ysmatrix.cpp /Fo$(OBJDIR)/ysmatrix.obj $(CFLAGS)


$(OBJDIR)/ysmatrix3x3.obj : ysmatrix3x3.cpp
	cl /c ysmatrix3x3.cpp /Fo$(OBJDIR)/ysmatrix3x3.obj $(CFLAGS)


$(OBJDIR)/ysmatrix4x4.obj : ysmatrix4x4.cpp
	cl /c ysmatrix4x4.cpp /Fo$(OBJDIR)/ysmatrix4x4.obj $(CFLAGS)


$(OBJDIR)/ysreldir.obj : ysreldir.cpp
	cl /c ysreldir.cpp /Fo$(OBJDIR)/ysreldir.obj $(CFLAGS)


$(OBJDIR)/ysargs.obj : ysargs.cpp
	cl /c ysargs.cpp /Fo$(OBJDIR)/ysargs.obj $(CFLAGS)


$(OBJDIR)/ysadvgeometry.obj : ysadvgeometry.cpp
	cl /c ysadvgeometry.cpp /Fo$(OBJDIR)/ysadvgeometry.obj $(CFLAGS)


$(OBJDIR)/yswizard.obj : yswizard.cpp
	cl /c yswizard.cpp /Fo$(OBJDIR)/yswizard.obj $(CFLAGS)


$(OBJDIR)/ysproperty.obj : ysproperty.cpp
	cl /c ysproperty.cpp /Fo$(OBJDIR)/ysproperty.obj $(CFLAGS)


$(OBJDIR)/ysshellutil.obj : ysshellutil.cpp
	cl /c ysshellutil.cpp /Fo$(OBJDIR)/ysshellutil.obj $(CFLAGS)


$(OBJDIR)/yssword.obj : yssword.cpp
	cl /c yssword.cpp /Fo$(OBJDIR)/yssword.obj $(CFLAGS)


$(OBJDIR)/ysequation.obj : ysequation.cpp
	cl /c ysequation.cpp /Fo$(OBJDIR)/ysequation.obj $(CFLAGS)


$(OBJDIR)/ysadvgeometryx.obj : ysadvgeometryx.cpp
	cl /c ysadvgeometryx.cpp /Fo$(OBJDIR)/ysadvgeometryx.obj $(CFLAGS)


$(OBJDIR)/ysstring.obj : ysstring.cpp
	cl /c ysstring.cpp /Fo$(OBJDIR)/ysstring.obj $(CFLAGS)


$(OBJDIR)/yspixelmap.obj : yspixelmap.cpp
	cl /c yspixelmap.cpp /Fo$(OBJDIR)/yspixelmap.obj $(CFLAGS)


$(OBJDIR)/ysfilename.obj : ysfilename.cpp
	cl /c ysfilename.cpp /Fo$(OBJDIR)/ysfilename.obj $(CFLAGS)


$(OBJDIR)/ysshell2d.obj : ysshell2d.cpp
	cl /c ysshell2d.cpp /Fo$(OBJDIR)/ysshell2d.obj $(CFLAGS)


$(OBJDIR)/ysclip.obj : ysclip.cpp
	cl /c ysclip.cpp /Fo$(OBJDIR)/ysclip.obj $(CFLAGS)


$(OBJDIR)/ysshellsearch.obj : ysshellsearch.cpp
	cl /c ysshellsearch.cpp /Fo$(OBJDIR)/ysshellsearch.obj $(CFLAGS)


$(OBJDIR)/ysshellblend.obj : ysshellblend.cpp
	cl /c ysshellblend.cpp /Fo$(OBJDIR)/ysshellblend.obj $(CFLAGS)


$(OBJDIR)/ysshelllattice.obj : ysshelllattice.cpp
	cl /c ysshelllattice.cpp /Fo$(OBJDIR)/ysshelllattice.obj $(CFLAGS)


$(OBJDIR)/yshash.obj : yshash.cpp
	cl /c yshash.cpp /Fo$(OBJDIR)/yshash.obj $(CFLAGS)


$(OBJDIR)/yskdtree.obj : yskdtree.cpp
	cl /c yskdtree.cpp /Fo$(OBJDIR)/yskdtree.obj $(CFLAGS)


$(OBJDIR)/yspredefined.obj : yspredefined.cpp
	cl /c yspredefined.cpp /Fo$(OBJDIR)/yspredefined.obj $(CFLAGS)


$(OBJDIR)/ysveci.obj : ysveci.cpp
	cl /c ysveci.cpp /Fo$(OBJDIR)/ysveci.obj $(CFLAGS)


$(OBJDIR)/ysshellblend2.obj : ysshellblend2.cpp
	cl /c ysshellblend2.cpp /Fo$(OBJDIR)/ysshellblend2.obj $(CFLAGS)


$(OBJDIR)/ysexception.obj : ysexception.cpp
	cl /c ysexception.cpp /Fo$(OBJDIR)/ysexception.obj $(CFLAGS)


$(OBJDIR)/yslist.obj : yslist.cpp
	cl /c yslist.cpp /Fo$(OBJDIR)/yslist.obj $(CFLAGS)




$(OBJDIR)/ysshell.obj : ysshell.cpp
	cl /c ysshell.cpp /Fo$(OBJDIR)/ysshell.obj $(CFLAGS)


$(OBJDIR)/ysshellstl.obj : ysshellstl.cpp
	cl /c ysshellstl.cpp /Fo$(OBJDIR)/ysshellstl.obj $(CFLAGS)




