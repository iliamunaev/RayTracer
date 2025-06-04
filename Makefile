
# --------------------------- Executable and Library ------------------------- #
NAME    := miniRT

CC      := cc
CFLAGS  := -Wextra -Wall -Werror 

LIBMLX  := ./lib/MLX42


HEADERS := -Iinclude -Ilib/MLX42/include -I../include

# lglfw: OpenGL graphics library
# ldl: Dynamic linking library for runtime symbol resolution
LIBS    := lib/MLX42/build/libmlx42.a -ldl -lglfw

SRCS    := $(shell find ./src -name "*.c")
OBJ_DIR := obj
OBJS    := $(SRCS:./src/%.c=$(OBJ_DIR)/%.o)

# ------------------------------ Colors -------------------------------------- #
RESET   := \033[0m
GREEN   := \033[32m
BLUE    := \033[34m
RED     := \033[31m

# ------------------------------- Targets ------------------------------------ #
all: libmlx $(NAME)
	@echo "$(GREEN)Program $(NAME) compiled successfully!$(RESET)"

# Download and build MLX42
libmlx:
	@echo "$(BLUE)[LIBMLX] Building MLX42 library...$(RESET)"
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4


$(NAME): $(OBJS)
	@echo "$(BLUE)Linking executable: $(NAME)$(RESET)"
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

# Rule to compile .c files into .o and store them in obj/
$(OBJ_DIR)/%.o: ./src/%.c | $(OBJ_DIR)
	@echo "$(BLUE)Compiling: $(notdir $<)...$(RESET)"
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(GREEN)Removing object files...$(RESET)"
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBMLX)/build
	@echo "$(BLUE)Cleaned object files and directories.$(RESET)"

fclean: clean
	@echo "$(GREEN)Removing executable: $(NAME)...$(RESET)"
	rm -rf $(NAME)
	@echo "$(GREEN)'$(NAME)' executable successfully removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re 