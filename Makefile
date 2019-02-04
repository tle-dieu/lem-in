NAME = lem_in
CC = gcc
FLAG = -Wall -Werror -Wextra
LDFLAG = -L./$(LIBDIR) -lft


RM = rm -rf

SRC = main.c \
	  parsing.c
OBJ = $(SRC:.c=.o)

LIBDIR := libft/
LIBFT := $(LIBDIR)libft.a
INCLUDE_FOLDER := $(LIBDIR)includes
INCLUDE := lem_in.h

GREEN := \033[38;2;12;231;58m
YELLOW := \033[38;2;251;196;15m
RED := \033[38;2;255;60;51m
BLUE := \033[38;2;0;188;218m
RMLINE = \033[2K
NC := \033[0m

MAP_FOLDER := ./maps/

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@printf "$(RMLINE)$(YELLOW)🌘  All compiled$(NC)\n"
	@$(CC) -o $@ $(LDFLAG) $^
	@printf "$(GREEN)$(NAME) has been created$(NC)\n"
	@tput cnorm

$(LIBFT):
	@(cd $(LIBDIR) && $(MAKE))

%.o: %.c $(INCLUDE)
	@tput civis
	@$(CC) $(FLAG) -I $(INCLUDE_FOLDER) -o $@ -c $<
	@printf "$(RMLINE)\r🚀 $(GREEN)$(YELLOW) Compiling:$(NC) $(notdir $<)\r"
	@sleep 0.01

clean:
	@(cd $(LIBDIR) && $(MAKE) $@)
	@$(RM) $(OBJ)
	@printf "$(RED)The lem_in objects have been removed$(NC)\n"

fclean:
	@(cd $(LIBDIR) && $(MAKE) $@)
	@$(RM) $(OBJ) $(NAME)
	@printf "$(RED)The lem_in objects have been removed$(NC)\n"
	@printf "$(RED)$(NAME) has been removed$(NC)\n"

run: $(NAME)
	./lem_in < $(MAP_FOLDER)$(map)

re: fclean all

.PHONY: clean fclean run
