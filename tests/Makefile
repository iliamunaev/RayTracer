
# --------------------------- Executable and Library ------------------------- #
NAME    := test

CC      := cc
CFLAGS  := #-Wextra -Wall -Werror 

LIBMLX  := ../lib/MLX42
LIBFT   := ../lib/libft


HEADERS := -I../include -I../lib/MLX42/include -I../include

# lglfw: OpenGL graphics library
# ldl: Dynamic linking library for runtime symbol resolution
LIBS    := ../lib/MLX42/build/libmlx42.a ../lib/libft/libft.a -ldl -lglfw -lm -g

SRCS	:=  test_sphere_ray_interaction.c \
			print_matrix.c \
			../src/primitives/sphere.c \
			../src/ray/ray.c \
			../src/utils/utils.c\
			../src/utils/color_utils.c \
			../src/utils/colors.c \
			../src/math/math.c \
			../src/matrix/shear.c \
			../src/matrix/math_matrix.c \
			../src/matrix/matrix_manipulations.c \
			../src/matrix/matrix_utils.c \
			../src/matrix/matrix.c



SRC_DIR := ../
OBJ_DIR := obj

OBJ_TEST := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
# OBJS := $(SRCS:%.c=$(OBJ_DIR)/%.o)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

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


$(NAME): $(OBJS) $(OBJ_TEST)
	@echo "$(BLUE)Linking executable: $(NAME)$(RESET)"
	$(CC) $(OBJS) $(OBJ_TEST) $(LIBS) -o $(NAME)

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
	@echo "$(BLUE)Cleaned object files and directories.$(RESET)"

fclean: clean
	@echo "$(GREEN)Removing executable: $(NAME)...$(RESET)"
	rm -rf $(NAME)
	@echo "$(GREEN)'$(NAME)' executable successfully removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re 