NAME		=	cub3d
CFLAGS		=	-fsanitize=address -g
FLAGS       =   -lmlx -framework OpenGL -framework AppKit
CC			=	cc
OBJ			=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
OBJDIR		=	.objfiles
MLX			=	mlx/libmlx.a
LIBFT		=	libft/libft.a
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
GRAY		=	\033[1;37m
RESET		=	\033[0m
PARSING		=	check_map.c get_next_line.c utils_00.c utils_01.c\
				check_content.c check_texts_colors.c utils_02.c\
				check_player.c check_surrounded.c check_floor_outside.c\
				get_map.c splite_color.c utils_03.c 

EXEC		=	press.c render_minimap.c render_scene.c utils_00.c\
				movements.c hooks.c get_distance.c mouse.c
SRC 		=	cub3d.c $(EXEC_SRC) $(PARSE_SRC)
HEADERS		=	parsing.h
EXEC_SRC	=	$(addprefix execution/, $(EXEC))
PARSE_SRC	=	$(addprefix parsing/, $(PARSING))
HEADER		=	$(addprefix includes/, $(HEADERS))


all			:	$(NAME)
	
$(NAME)		:	$(LIBFT) $(OBJ)
				@$(CC) $(OBJ) -o $(NAME) $(LIBFT) $(MLX) $(FLAGS) $(CFLAGS) -I mlx/mlx.h
				@echo "$(BLUE)cub3d$(GREEN)\r\t\t\t compiled$(RESET)"

$(LIBFT)	:
				@make -C ./libft
				@echo "$(GREEN)libft:\r\t\t\t compiled$(RESET)"

$(OBJDIR)/%.o	:	%.c $(HEADER)
				@mkdir -p $(dir $@)
				@$(CC) -c $< -o $@
				@echo "$(BLUE)$<:$(RESET)\r\t\t\t $(GREEN)compiled$(RESET)"

clean		:
				@rm -rf $(OBJDIR)
				@echo "$(YELLOW)object files cleaned$(RESET)"

fclean		:	clean
				@rm -rf $(NAME) $(OBJDIR)
				@echo "$(RED)cub3d cleaned$(RESET)"

re			:	fclean all

norm		:
				@printf "$(RED)"
				@norminette | grep Error
				@printf "$(RESET)"
				
run			:	$(NAME)
				@./$(NAME) maps/map1.cub

run2		:	$(NAME)
				@./$(NAME) maps/map2.cub

large		:	$(NAME)
				@./$(NAME) maps/large.cub

big		:	$(NAME)
				@./$(NAME) maps/big.cub

push		:
				@./push.sh

backup		:
				make fclean
				git add *
				git commit -m "backup"

.PHONY		:	clean all fclean re