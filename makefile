SCRS		= 	ft_main.c ft_img.c ft_utils.c ft_free.c\
				ft_windows.c ft_map.c ft_extractmap.c \
				ft_utils_map.c ft_player.c ft_raycast.c \
				ft_bmp.c ft_xpm.c ft_hook.c ft_error.c \
				ft_sprite.c ft_list.c ft_wall.c ft_init.c\
				ft_is_sprite.c ft_object.c\
				${GNL}

DEFAULT		=	ft_move.c ft_extract_color.c ft_sprite_utils.c ft_floor.c
BONUS		=	ft_move_bonus.c ft_extract_bonus.c ft_sprite_utils_bonus.c ft_floor_bonus.c \
				ft_skybox_bonus.c ft_minimap_bonus.c ft_sprite_bonus.c ft_jauge_bonus.c

GNL			= get_next_line.c

OBJS		= ${SCRS:.c=.o}

DEFAULT_OBJS= ${DEFAULT:.c=.o}
BONUS_OBJS	= ${BONUS:.c=.o}

RM			= rm -f

NAME		= Cub3D

CC			= gcc

CFLAG		= -Ofast -Wall -Werror -Wextra

DIR_LIBFT	= libft

all:	${NAME}

.c.o:
	${CC} -g ${CFLAG} -c  $< -o ${<:.c=.o}

${NAME}:	${DIR_LIBFT}/libft.a ${OBJS} ${DEFAULT_OBJS} cub3d.h
	${RM} ${NAME} ${BONUS_OBJS}
	${CC} -g -lmlx -framework OpenGL -framework AppKit ${DIR_LIBFT}/libft.a ${OBJS} ${DEFAULT_OBJS} -o ${NAME}

${DIR_LIBFT}/libft.a :
	make -C $(DIR_LIBFT)

clean:
	make -C $(DIR_LIBFT) clean
	${RM} ${OBJS} ${DEFAULT_OBJS} ${BONUS_OBJS}

fclean:		clean
	make -C $(DIR_LIBFT) fclean
	${RM} ${NAME}

bonus:	${DIR_LIBFT}/libft.a ${OBJS} ${BONUS_OBJS} cub3d.h
	${RM} ${NAME} ${DEFAULT_OBJS}
	${CC} -g -lmlx -framework OpenGL -framework AppKit ${DIR_LIBFT}/libft.a ${OBJS} ${BONUS_OBJS} -o ${NAME}

re:			fclean all

re_bonus:	fclean bonus

.PHONY: all clean fclean re bonus re_bonus