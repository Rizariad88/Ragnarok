
COMMON_H = $(shell ls ../common/*.hpp)
COMMON_AR = ../common/obj/common.a
COMMON_INCLUDE = -I../common

LIBCONFIG_H = $(shell ls ../../3rdparty/libconfig/*.h)
LIBCONFIG_AR = ../../3rdparty/libconfig/obj/libconfig.a
LIBCONFIG_INCLUDE = -I../../3rdparty/libconfig

RAPIDYAML_OBJ = $(shell find ../../3rdparty/rapidyaml/ -type f -name "*.cpp" | sed -e "s/\.cpp/\.o/g" )
RAPIDYAML_DIR_OBJ = $(RAPIDYAML_OBJ:%=obj/%)
RAPIDYAML_AR = ../../3rdparty/rapidyaml/obj/ryml.a
RAPIDYAML_H = $(shell find ../../3rdparty/rapidyaml/ -type f -name "*.h*")
RAPIDYAML_INCLUDE = -I../../3rdparty/rapidyaml/src -I../../3rdparty/rapidyaml/ext/c4core/src

HTTPLIB_OBJ = $(shell find ../../3rdparty/httplib/ -type f -name "*.cc" | sed -e "s/\.cc/\.o/g" )
HTTPLIB_DIR_OBJ = $(HTTPLIB_OBJ:%=obj/%)
HTTPLIB_AR = ../../3rdparty/httplib/obj/httplib.a
HTTPLIB_H = $(shell find ../../3rdparty/httplib/ -type f -name "*.h")
HTTPLIB_INCLUDE = -I../../3rdparty/httplib

NLOHMANN_H = $(shell find ../../3rdparty/json/include/nlohmann/ -type f -name "*.hpp")
NLOHMANN_INCLUDE = -I../../3rdparty/json/include

WEB_OBJ = $(shell ls *.cpp | sed -e "s/\.cpp/\.o/g")
WEB_DIR_OBJ = $(WEB_OBJ:%=obj/%)
WEB_H = $(shell ls *.hpp)


SERVER_DEPENDS=web-server

HAVE_MYSQL=yes
ifeq ($(HAVE_MYSQL),yes)
	SERVER_DEPENDS=web-server
else
	SERVER_DEPENDS=needs_mysql
endif

ALL_DEPENDS=server



#####################################################################
.PHONY :all server clean help

all: $(ALL_DEPENDS)

server: $(SERVER_DEPENDS)

clean:
	@echo "	CLEAN	web"
	@rm -rf *.o obj ../../web-server

help:
	@echo "possible targets are 'server' 'all' 'clean' 'help'"
	@echo "'server'    - web server"
	@echo "'all'       - builds all above targets"
	@echo "'clean'     - cleans builds and objects"
	@echo "'help'      - outputs this message"

#####################################################################

needs_mysql:
	@echo "MySQL not found or disabled by the configure script"
	@exit 1

# object directories

obj:
	@echo "	MKDIR	obj"
	@-mkdir obj

#executables

web-server: obj $(WEB_DIR_OBJ) $(COMMON_AR) $(LIBCONFIG_AR) $(RAPIDYAML_AR) $(HTTPLIB_AR)
	@echo "	LD	web-server"
	@g++  -L/usr/lib -o ../../web-server $(WEB_DIR_OBJ) $(COMMON_AR) $(LIBCONFIG_AR) $(RAPIDYAML_AR) $(HTTPLIB_AR) -lpcre -lpthread -lz  -ldl -L/usr/lib64/mysql -lmysqlclient -lpthread -lz -lm -ldl -lssl -lcrypto

# web object files

obj/%.o: %.cpp $(WEB_H) $(COMMON_H) $(LIBCONFIG_H) $(HTTPLIB_H) $(RAPIDYAML_H) $(NLOHMANN_H)
	@echo "	CXX	$<"
	@g++ -g -O2 -std=c++11 $(COMMON_INCLUDE) $(LIBCONFIG_INCLUDE) $(HTTPLIB_INCLUDE) $(RAPIDYAML_INCLUDE) $(NLOHMANN_INCLUDE) -I/usr/include/mysql  -I../common -DHAS_TLS -fno-strict-aliasing -DHAVE_SETRLIMIT -DHAVE_STRNLEN  -I/usr/include -DHAVE_MONOTONIC_CLOCK -c $(OUTPUT_OPTION) $<

# missing object files
$(COMMON_AR):
	@$(MAKE) -C ../common server

$(LIBCONFIG_AR):
	@$(MAKE) -C ../../3rdparty/libconfig

$(RAPIDYAML_AR):
	@$(MAKE) -C ../../3rdparty/rapidyaml

$(HTTPLIB_AR):
	@$(MAKE) -C ../../3rdparty/httplib
