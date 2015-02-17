
#ifndef DEBUG_H
#define DEBUG_H
/*****************************************************************
 * Dateiname:       debug.h
 * Ort:             ..\include\
 * GIT:             nios_includes.git
 * Beschreibung:    Debugroutinen
 * Datum:           24.03.2009
 * Autor:           Marco Brinker
 *
 * Diese Datei enthält alle Debugroutinen für die Softwareerstellung
 * im Linux-NIOS.
 * Änderungen sind am Anfang der Datei zu kommentieren. 
 * 
 * 
 * Änderungshistorie
 * 2009-03-24 Marco Brinker
 * Datei erstellt. Erste Definitionen eingefügt. 
 * 
 *****************************************************************/
#include <stdarg.h>
#include <stdio.h>
void dprint(int debuglevel, char* format, ...)
{
#ifndef DPRINT
	/*Leer damit Compiler bei nichtbenutzung rauscompiliert*/
#else
        //TODO: Debuglevel wird noch nicht benutzt....
	va_list args;
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
#endif /* DPRINT */
}
#endif /* DEBUG_H */

