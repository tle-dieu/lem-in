NAME := lem-in
CFLAG = -Wall -Werror -Wextra
CC = gcc $(CFLAG)
LDFLAG = -L./$(LIBDIR) -lft

RM = rm -rf

SOURCES_FOLDER := sources/
INCLUDES_FOLDER := includes/
OBJECTS_FOLDER := objects/

vpath %.c $(SOURCES_FOLDER)

SOURCES = main.c \
		  parsing.c \
		  utils.c \
		  edmonds_karp.c \
		  room.c \
		  pipe.c \
		  bfs.c \
		  ants.c \
		  free.c \
		  send.c \
		  path.c

OBJECTS = $(SRC:.c=.o)

LIBDIR := libft/
LIBFT := $(LIBDIR)libft.a
LIBINC := $(LIBDIR)includes/
INCLUDES := $(LIBINC)libft.h $(INCLUDES_FOLDER)lem_in.h
OBJECTS := $(addprefix $(OBJECTS_FOLDER), $(SOURCES:.c=.o))

GREEN := \033[38;2;12;231;58m
YELLOW := \033[38;2;251;196;15m
RED := \033[38;2;255;60;51m
BLUE := \033[38;2;0;188;218m
RMLINE := \033[2K
RESET := \033[0m

ifneq (,$(filter $(fsanitize),y yes))
	CFLAG += -g3
	CFLAG += -fsanitize=address
endif
ifneq (,$(filter $(time),y yes))
	RUN_OPTION := time -p
endif
ifneq (,$(filter $(valgrind),y yes))
	RUN_OPTION += valgrind --leak-check=full --track-origins=yes --read-inline-info=yes --read-var-info=yes --num-callers=100 --show-possibly-lost=no
	CFLAG += -g3
endif
ifneq (,$(filter $(visu),y yes))
	VISU := | python3 visu/visu.py
endif
MAP_FOLDER := maps/

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@printf "$(RMLINE)$(YELLOW)🌘  All compiled$(RESET)\n"
	@$(CC) -o $(NAME) $(OBJECTS) $(LDFLAG)
	@printf "$(GREEN)$(NAME) has been created$(RESET)\n"
	@tput cnorm

objects/%.o: %.c $(INCLUDES)
	@tput civis
	@mkdir -p $(dir $@)
	@$(CC) -I $(INCLUDES_FOLDER) -I $(LIBINC) -o $@ -c $<
	@printf "$(RMLINE)\r🚀 $(GREEN)$(YELLOW) Compiling:$(RESET) $(notdir $<)\r"
	@sleep 0.02

$(LIBFT): force
	@$(MAKE) -C $(LIBDIR)

force:
	@true

clean:
	@$(MAKE) $@ -C $(LIBDIR)
	@$(RM) $(OBJECTS_FOLDER)
	@printf "$(RED)The lem_in objects have been removed$(RESET)\n"

fclean:
	@$(MAKE) $@ -C $(LIBDIR)
	@$(RM) $(OBJECTS_FOLDER) $(NAME)
	@printf "$(RED)The lem_in objects have been removed$(RESET)\n"
	@printf "$(RED)$(NAME) has been removed$(RESET)\n"

run: $(NAME)
ifneq ($(generator),)
ifneq (,$(filter $(generator),flow-one flow-ten flow-thousand big big-superposition))
		$(MAP_FOLDER)./generator --$(generator) > $(MAP_FOLDER)generator_map
		$(RUN_OPTION) ./$(NAME) < $(MAP_FOLDER)generator_map $(VISU)
else
		$(MAP_FOLDER)./generator --$(generator)
endif
else
	-@if [ -f $(map) ]; then $(RUN_OPTION) ./$(NAME) < $(map) $(VISU); \
		else printf "$(BLUE)List of maps: maps/\n$(RESET)" && ls $(MAP_FOLDER); fi
ifneq (,$(filter $(valgrind),y yes))
		@$(RM) $(NAME).dSYM
endif
endif

re: fclean all

.PHONY: all clean fclean run visu
