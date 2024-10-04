TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = runner app

OTHER_FILES += \ 
	$$files(rpm/*) \
	LICENSE.BSD-3-CLAUSE.md \
	README.md \
