# Colors
RED				= "\033[1;31m"
GREEN			= "\033[1;32m"
RESET			= "\033[m"
BLUE			= \033[1;34m
END				= \e[0m

# Variables
NAME			=	ircserv
CXX				=	c++ -std=c++98
CXXFLAGS		=	-Wall -Wextra -Werror -g3

OBJ_DIR			=	obj/

SRC_DIR			= 	src/
SRC_CMD			=	Command/
SRC_CMD_CHAN	=	$(addprefix ${SRC_CMD}, Channel/)
SRC_CMD_SERVER	=	$(addprefix ${SRC_CMD}, Server/)
SRC_CMD_USER	=	$(addprefix ${SRC_CMD}, User/)


SRC				=	main.cpp utils.cpp \
					Server.cpp User.cpp Command.cpp Channel.cpp \
					$(addprefix ${SRC_CMD}, \
						DIE.cpp ERRORS.cpp KICK.cpp \
						PING.cpp PONG.cpp REPLIES.cpp) \
					$(addprefix ${SRC_CMD_CHAN}, \
						INVITE.cpp JOIN.cpp KILL.cpp LIST.cpp \
						NAMES.cpp PART.cpp TOPIC.cpp) \
					$(addprefix ${SRC_CMD_SERVER}, \
						INFO.cpp STAT.cpp TIME.cpp \
						VERSION.cpp) \
					$(addprefix ${SRC_CMD_USER}, \
						MODE.cpp NICK.cpp NOTICE.cpp OPER.cpp \
						PASS.cpp PRIVMSG.cpp QUIT.cpp \
						USER.cpp)

OBJ				=	$(addprefix ${OBJ_DIR}, ${SRC:.cpp=.o})

INC				=	-I./inc/

ifeq ($(DMEM),1)
CXXFLAGS 		+= -fsanitize=address -fno-omit-frame-pointer -g3
endif

all: $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	@mkdir -p ${@D}
	@$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@
	@printf	"\033[2K\r${BLUE}[Building - $<] $(END)"

$(NAME): $(OBJ)
	@printf "\nCompiling $(NAME)"; \
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@; \
	echo $(GREEN) " OK" $(RESET)

clean:
	@echo " ... Deleting obj folder"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo " ... Deleting binary and output files"
	@rm -f $(NAME)

re: clean fclean all

.PHONY: re clean fclean