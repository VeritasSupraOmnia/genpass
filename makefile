install:
	chmod 755 genpass.c
	cp -f genpass.c /bin/genpass
uninstall:
	rm /bin/genpass
