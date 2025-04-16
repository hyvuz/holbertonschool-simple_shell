# Final program name
NAME = simple_shell

# Source files
SRC = main.c execv.c shell.c

# Object files
OBJ = $(SRC:.c=.o)

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# Final target
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJ)

# Full clean (including the executable)
fclean: clean
	rm -f $(NAME)

# Rebuild everything from scratch
re: fclean $(NAME)
