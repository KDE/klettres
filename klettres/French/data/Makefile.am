####### kdevelop will overwrite this part!!! (begin)##########


EXTRA_DIST = level1.txt level3.txt 

install-data-local:
	$(mkinstalldirs) $(kde_datadir)/klettres/French/data/
	$(INSTALL_DATA) $(srcdir)/level1.txt $(kde_datadir)/klettres/French/data/level1.txt
	$(mkinstalldirs) $(kde_datadir)/klettres/French/data/
	$(INSTALL_DATA) $(srcdir)/level3.txt $(kde_datadir)/klettres/French/data/level3.txt

uninstall-local:
	-rm -f $(kde_datadir)/klettres/French/data/level1.txt
	-rm -f $(kde_datadir)/klettres/French/data/level3.txt

####### kdevelop will overwrite this part!!! (end)############
