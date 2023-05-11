# define standard colors
ifneq (,$(findstring xterm,${TERM}))
	BLACK        := $(shell tput -Txterm setaf 0)
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	WHITE        := $(shell tput -Txterm setaf 7)
	RESET := $(shell tput -Txterm sgr0)
else
	BLACK        := ""
	RED          := ""
	GREEN        := ""
	YELLOW       := ""
	LIGHTPURPLE  := ""
	PURPLE       := ""
	BLUE         := ""
	WHITE        := ""
	RESET        := ""
	NEWLINE      := "
	"
endif

define \n
endef
define \t
endef


CC=c++
RM = rm -f
NAME = main
CFLAGS=-Wall -Wextra -Werror -std=c++98

SRCS = main.cpp\
		utils.cpp
		

OBJ = $(SRCS:.cpp=.o) 

%.o: %.cpp
	@echo ""
	$(CC) -g $(CFLAGS) -c $< -o $@
	@echo "${RED}OBJECT CREATED${RESET}"
	
$(info ${\n})
$(info ${\n}${\t}${WHITE}                              CONTAINERS${RESET})
$(info ${\n})

all : $(NAME)



$(NAME) : $(OBJ)
	$(info ${\n})
	$(CC) -o $(NAME) $^ $(CFLAGS) && valgrind ./main > outfile1
	$(CC) -g -D STD -o $(NAME) $^ $(CFLAGS) && valgrind ./main > outfile2
	@echo "${RED}MAINS BASIC TEST COMPILED && EXECUTED${RESET}"
	@echo ""
	@echo "diff outfile1 outfile2 | wc -l"
	@echo -n "===> "
	@echo -n "${BLUE}"
	@diff outfile1 outfile2 | wc -l
	@echo "${RESET}"

clean :
	$(RM) $(OBJ)
	$(RM) outfile1
	$(RM) outfile2

fclean : clean
	$(RM) $(NAME)
	@echo ""

re : fclean all

.PHONY: fclean re all clean
