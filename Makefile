NAME := philo
NAME_BONUS := so_long_bonus
CC := cc
CFLAGS := -Wall -Werror -Wextra -g -I includes#-fsanitize=address

SRC_DIR := src
SRC_BONUS_DIR := src_bonus

SRC := main.c init_philosophers.c philostuff.c helpers.c philo_utils.c

SRC_BONUS :=

SRC_FILES := $(addprefix ./$(SRC_DIR)/, $(SRC))
SRC_BONUS_FILES := $(addprefix ./$(SRC_DIR)/, $(SRC_BONUS))

OBJ_DIR := obj
OBJ := $(SRC:.c=.o)
OBJ_BONUS := $(SRC_BONUS:.c=.o)
OBJ_FILES := $(addprefix ./$(OBJ_DIR)/, $(OBJ))
OBJ_BONUS_FILES := $(addprefix ./$(OBJ_DIR)/, $(OBJ_BONUS))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(MACROLIBX) $(OBJ_BONUS_FILES)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS_FILES)

./$(OBJ_DIR)/%.o : ./$(SRC_DIR)/%.c
	mkdir -p ./$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

./$(OBJ_DIR)/%.o : ./$(SRC_BONUS_DIR)/%.c
	mkdir -p ./$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ./$(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re

