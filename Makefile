NAME := philo
CC := cc
CFLAGS := -Wall -Werror -Wextra -g -I includes#-fsanitize=address

SRC_DIR := src

SRC := main.c init_philosophers.c philo_routine_helpers.c philo_routine_helpers_utils.c \
		philo_utils.c init_philosophers_utils.c monitoring.c cleanup.c

SRC_FILES := $(addprefix ./$(SRC_DIR)/, $(SRC))

OBJ_DIR := obj
OBJ := $(SRC:.c=.o)
OBJ_FILES := $(addprefix ./$(OBJ_DIR)/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

./$(OBJ_DIR)/%.o : ./$(SRC_DIR)/%.c
	mkdir -p ./$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

./$(OBJ_DIR)/%.o : ./$(SRC_BONUS_DIR)/%.c
	mkdir -p ./$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ./$(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

