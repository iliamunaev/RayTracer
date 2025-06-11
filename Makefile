
# --------------------------- Executable and Library ------------------------- #
NAME    := miniRT

CC      := cc
CFLAGS  := -Wextra -Wall -Werror 

LIBMLX  := ./lib/MLX42
LIBFT   := ./lib/libft

HEADERS := -Iinclude -Ilib/MLX42/include -I../include

# lglfw: OpenGL graphics library
# ldl: Dynamic linking library for runtime symbol resolution
LIBS    := lib/MLX42/build/libmlx42.a lib/libft/libft.a -ldl -lglfw -lm

SRCS    :=	src/minirt.c \
			src/utils/utils.c\
			src/utils/color_utils.c \
			src/utils/colors.c \
			src/math/math.c \
			/src/matrix/shear.c \
			src/matrix/math_matrix.c \
			src/matrix/matrix_manipulations.c \
			src/matrix/matrix_utils.c \
			src/matrix/matrix.c

OBJ_DIR := obj
OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ------------------------------ Colors -------------------------------------- #
RESET   := \033[0m
GREEN   := \033[32m
BLUE    := \033[34m
RED     := \033[31m

# ------------------------------- Targets ------------------------------------ #
all: libmlx libft $(NAME)
	@echo "$(GREEN)Program $(NAME) compiled successfully!$(RESET)"

# Build MLX42
libmlx:
	@echo "$(BLUE)[LIBMLX] Building MLX42 library...$(RESET)"
	cmake $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

libft:
	@echo "$(BLUE)[LIBFT] Building Libft library...$(RESET)"
	make -C $(LIBFT)

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking executable: $(NAME)$(RESET)"
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

# Rule to compile .c files into .o and store them in obj/
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling: $(notdir $<)...$(RESET)"
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@


# Create obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(GREEN)Removing object files...$(RESET)"
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBMLX)/build
	rm -rf $(LIBFT)/obj
	@echo "$(BLUE)Cleaned object files and directories.$(RESET)"

fclean: clean
	@echo "$(GREEN)Removing executable: $(NAME)...$(RESET)"
	rm -rf $(NAME)
	@echo "$(GREEN)'$(NAME)' executable successfully removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re 