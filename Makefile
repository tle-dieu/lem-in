NAME := lem_in
CFLAG = -Wall -Werror -Wextra
CC = gcc $(CFLAG)
LDFLAG = -L./$(LIBDIR) -lft

RM = rm -rf

SRC = main.c \
	  parsing.c \
	  utils.c

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


MAP_FOLDER := maps/

ifneq (,$(filter $(debug),y yes))
	CFLAG += -g3
endif
ifneq (,$(filter $(fsanitize),y yes))
	CFLAG += -fsanitize=address
endif
ifneq (,$(filter $(valgrind),y yes))
	EXEC_LINE := valgrind --leak-check=full --track-origins=yes --read-inline-info=yes --read-var-info=yes --num-callers=100 --show-possibly-lost=no
endif
EXEC_LINE += ./lem_in < $(MAP_FOLDER)$(map)

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
	@$(CC) $(CFLAG) -I $(INCLUDE_FOLDER) -o $@ -c $<
	@printf "$(RMLINE)\r🚀 $(GREEN)$(YELLOW) Compiling:$(NC) $(notdir $<)\r"
	@sleep .01

clean:
	@(cd $(LIBDIR) && $(MAKE) $@)
	@$(RM) $(OBJ)
	@printf "$(RED)The lem_in objects have been removed$(NC)\n"

fclean:
	@(cd $(LIBDIR) && $(MAKE) $@)
	@$(RM) $(OBJ) $(NAME)
	@printf "$(RED)The lem_in objects have been removed$(NC)\n"
	@printf "$(RED)$(NAME) has been removed$(NC)\n"

debug: CFLAG += -g3
debug: re

run: $(NAME) Makefile
	$(EXEC_LINE)
ifneq (,$(filter $(valgrind),y yes))
	@$(RM) $(NAME).dSYM
endif

re: fclean all

.PHONY: clean fclean run
