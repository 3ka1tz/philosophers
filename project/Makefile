NAME = philo

CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)
OBJ_DIR = obj

all: $(NAME)
	@if [ "$(REBUILD)" = "1" ]; then \
		echo "\033[32m$(NAME) has been successfully built.\033[0m"; \
		$(MAKE) -s usage; \
	else \
		echo "\033[32mNo changes detected, $(NAME) is up to date.\033[0m"; \
		$(MAKE) -s usage; \
	fi

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@$(eval REBUILD := 1)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

obj/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@$(eval REBUILD := 1)

clean:
	rm -f $(OBJ)
	@echo "\033[32mCleaned up object files and dependencies.\033[0m"

fclean: clean
	rm -rf obj
	rm -f $(NAME)
	@echo "\033[32mFully cleaned up all build artifacts.\033[0m"

re: fclean all

usage:
	@echo "\033[33mUsage: ./$(NAME) number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
	@echo "Example 1: ./$(NAME) 5 800 200 200"
	@echo "Example 2: ./$(NAME) 5 800 200 200 7"
	@printf "The maximum number of philosophers is set to ";
	@echo "$(shell gcc -E -dM include/philo.h | grep PHILO_MAX | awk '{print $$3}').\033[0m"

.PHONY: all clean fclean re usage