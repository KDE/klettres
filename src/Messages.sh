#! /bin/sh
$EXTRACTRC *.rc *.ui *.kcfg >> rc.cpp
$XGETTEXT *.cpp -o $podir/klettres.pot
