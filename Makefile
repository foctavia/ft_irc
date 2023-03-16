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

SRC				=	main.cpp utils.cpp \
					Server.cpp User.cpp Command.cpp \
					$(addprefix ${SRC_CMD}, NICK.cpp PASS.cpp USER.cpp QUIT.cpp PRIVMSG.cpp PING.cpp PONG.cpp) \
					$(addprefix ${SRC_CMD}, ERRORS.cpp REPLIES.cpp)

OBJ				=	$(addprefix ${OBJ_DIR}, ${SRC:.cpp=.o})

INC				=	-I./inc/

ifeq ($(DMEM),1)
CXXFLAGS 		+= -fsanitize=address -fno-omit-frame-pointer -g3
endif

all: $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	@mkdir -p ${@D}
	@$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@
	@printf	"\033[2K\r${BLUE}[Building - $<] $(END)\n"

$(NAME): $(OBJ)
	@printf "Compiling $(NAME)"; \
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