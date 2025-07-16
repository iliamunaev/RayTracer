NAME    := miniRT

CC      := cc
CFLAGS  := -O3 -flto -ffast-math -march=native -Wextra -Wall -Werror

# Enable BONUS if target is 'bonus'
ifeq ($(MAKECMDGOALS),bonus)
	CFLAGS += -DBONUS
endif

LIBDIR  := lib
LIBMLX  := $(LIBDIR)/MLX42
LIBFT   := $(LIBDIR)/libft
SRC_DIR := src
OBJ_DIR := obj

HEADERS := -Iinclude -I$(LIBMLX)/include
LIBS    := $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -lm

SRCS := \
	$(SRC_DIR)/minirt.c \
	$(SRC_DIR)/primitives/scale_object.c \
	$(SRC_DIR)/primitives/primitive_intersections.c \
	$(SRC_DIR)/ray/ray.c \
	$(SRC_DIR)/ray/ray_math.c \
	$(SRC_DIR)/utils/utils.c \
	$(SRC_DIR)/math/color_ops.c \
	$(SRC_DIR)/math/tuple_ops.c \
	$(SRC_DIR)/math/vector_math.c \
	$(SRC_DIR)/math/ft_strtof.c \
	$(SRC_DIR)/math/math_utils.c \
	$(SRC_DIR)/matrix/matrix_determinant.c \
	$(SRC_DIR)/matrix/matrix_div.c \
	$(SRC_DIR)/matrix/matrix_inverse.c \
	$(SRC_DIR)/matrix/matrix_mult.c \
	$(SRC_DIR)/matrix/matrix_rotation.c \
	$(SRC_DIR)/matrix/matrix_transform.c \
	$(SRC_DIR)/matrix/matrix_transpose.c \
	$(SRC_DIR)/matrix/matrix_utils.c \
	$(SRC_DIR)/matrix/matrix.c \
	$(SRC_DIR)/lighting/reflection_math.c \
	$(SRC_DIR)/lighting/lighting.c \
	$(SRC_DIR)/lighting/precompute_values.c \
	$(SRC_DIR)/lighting/refraction_containers.c \
	$(SRC_DIR)/lighting/reflection_refraction_shadow_checker.c \
	$(SRC_DIR)/lighting/specular_diffuse.c \
	$(SRC_DIR)/parsing/parsing.c \
	$(SRC_DIR)/parsing/parse_primitives.c \
	$(SRC_DIR)/parsing/init_world.c \
	$(SRC_DIR)/parsing/parsing_utils_1.c \
	$(SRC_DIR)/parsing/parsing_utils_2.c \
	$(SRC_DIR)/parsing/fillup_world.c \
	$(SRC_DIR)/parsing/parse_cam_light.c \
	$(SRC_DIR)/parsing/setup_mlx.c \
	$(SRC_DIR)/parsing/set_matereal.c \
	$(SRC_DIR)/validation/validate_file.c \
	$(SRC_DIR)/validation/validation_1.c \
	$(SRC_DIR)/validation/validation_2.c \
	$(SRC_DIR)/validation/validation_utils_1.c \
	$(SRC_DIR)/validation/validation_utils_2.c \
	$(SRC_DIR)/validation/validate_primitives.c \
	$(SRC_DIR)/validation/validate_cam_light.c \
	$(SRC_DIR)/validation/ft_strtof_valid.c \
	$(SRC_DIR)/loop/world_loop.c \
	$(SRC_DIR)/loop/mouse_loop.c \
	$(SRC_DIR)/loop/loop_utils.c \
	$(SRC_DIR)/loop/key_action.c \
	$(SRC_DIR)/loop/cam_action.c \
	$(SRC_DIR)/loop/resize_loop.c \
	$(SRC_DIR)/camera/transform_cam_view.c \
	$(SRC_DIR)/camera/camera.c \
	$(SRC_DIR)/camera/camera_utils_1.c \
	$(SRC_DIR)/camera/camera_utils_2.c \
	$(SRC_DIR)/render/render.c

OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# ------------------------------ Colors -------------------------------------- #
RESET := \033[0m
GREEN := \033[32m
BLUE  := \033[34m
RED   := \033[31m

# ------------------------------ Targets ------------------------------------- #

all: $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a $(NAME)
	@echo "$(GREEN)➤➤➤ Program $(NAME) compiled successfully!$(RESET)"

$(NAME): $(OBJS)
	@echo "$(BLUE)🔗 Linking executable: $(NAME)$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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

bonus: all

.PHONY: all clean fclean re bonus
