# --------------------------- Executable and Library ------------------------- #
NAME    := test

CC      := cc
CFLAGS  := -O3 -flto -ffast-math -march=native -g -Wextra -Wall -Werror

LIBDIR  := ../lib
# LIBDIR  := lib  // for production
LIBMLX  := $(LIBDIR)/MLX42
LIBFT   := $(LIBDIR)/libft

HEADERS := -I../include -I$(LIBMLX)/include -I../include
LIBS    := $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -lm

SRCS	:=  test_main.c \
			print_matrix.c \
			../src/primitives/scale_object.c \
			../src/primitives/primitive_utils.c \
			../src/primitives/primitive_intersections.c \
			../src/ray/ray.c \
			../src/utils/utils.c \
			../src/colors/colors.c \
			../src/math/color_ops.c \
			../src/math/tuple_ops.c \
			../src/math/vector_math.c \
			../src/math/ft_strtof.c \
			../src/matrix/matrix_determinant.c \
			../src/matrix/matrix_div.c \
			../src/matrix/matrix_inverse.c \
			../src/matrix/matrix_mult.c \
			../src/matrix/matrix_rotation.c \
			../src/matrix/matrix_transform.c \
			../src/matrix/matrix_transpose.c \
			../src/matrix/matrix_utils.c \
			../src/matrix/matrix.c \
			../src/lighting/reflection_math.c \
			../src/lighting/lighting.c \
			../src/lighting/precompute_values.c \
			../src/parsing/parsing.c \
			../src/parsing/parse_primitives.c \
			../src/parsing/init_world.c \
			../src/parsing/parsing_utils_1.c \
			../src/parsing/parsing_utils_2.c \
			../src/parsing/fillup_world.c \
			../src/parsing/parse_cam_light.c \
			../src/parsing/setup_mlx.c \
			../src/validation/validate_file.c \
			../src/validation/validation_1.c \
			../src/validation/validation_2.c \
			../src/validation/validation_utils.c \
			../src/validation/validate_primitives.c \
			../src/validation/validate_cam_light.c \
			../src/loop/world_loop.c \
			../src/loop/mouse_loop.c \
			../src/loop/loop_utils.c \
			../src/loop/key_action.c \
			../src/loop/cam_action.c \
			../src/camera/transform_cam_view.c \
			../src/camera/camera.c \
			../src/camera/camera_utils_1.c \
			../src/camera/camera_utils_2.c \
			../src/render/render.c

OBJ_DIR := obj
OBJS    := $(SRCS:%.c=$(OBJ_DIR)/%.o)

# ------------------------------ Colors -------------------------------------- #
RESET   := \033[0m
GREEN   := \033[32m
BLUE    := \033[34m
RED     := \033[31m

# ------------------------------ Targets ------------------------------------- #

all: $(LIBDIRS) $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a $(NAME)
	@echo "$(GREEN)➤➤➤ Program $(NAME) compiled successfully!$(RESET)"

$(NAME): $(OBJS)
	@echo "$(BLUE)🔗 Linking executable: $(NAME)$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling: $(notdir $<)...$(RESET)"
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

# ----------------------------- External Libraries --------------------------- #

$(LIBMLX)/build/libmlx42.a:
	@echo "$(BLUE)Checking MLX42...$(RESET)"
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "$(RED)➤ Cloning MLX42...$(RESET)"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi
	@echo "$(BLUE)Building MLX42...$(RESET)"
	cmake -S $(LIBMLX) -B $(LIBMLX)/build
	make -C $(LIBMLX)/build -j4

$(LIBFT)/libft.a:
	@echo "$(BLUE)Checking Libft...$(RESET)"
	@if [ ! -d "$(LIBFT)" ]; then \
		echo "$(RED)➤ Cloning Libft...$(RESET)"; \
		git clone https://github.com/iliamunaev/libft-C-library.git $(LIBFT); \
	fi
	@echo "$(BLUE)Building Libft...$(RESET)"
	make -C $(LIBFT)

clean:
	@echo "$(GREEN)Removing object files...$(RESET)"
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBMLX)/build
	@if [ -d "$(LIBFT)" ]; then \
		$(MAKE) -C $(LIBFT) clean; \
	fi
	@echo "$(GREEN)➤➤➤ Objects files removed$(RESET)"

fclean: clean
	@echo "$(GREEN)Removing executable: $(NAME)...$(RESET)"
	rm -rf $(NAME)
	@make -C $(LIBFT) fclean || true
	rm -rf $(LIBMLX)/build
	rm -rf $(LIBMLX)
	rm -rf $(LIBFT)
	@echo "$(GREEN)➤➤➤ All built files and libraries removed!$(RESET)"


re: fclean all

.PHONY: all clean fclean re
