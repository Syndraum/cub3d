SCRS		= 	main.c \
				ft_img.c \
				ft_print.c \
				ft_windows.c \
				ft_map.c \
				${GNL}

GNL			= get_next_line.c

OBJS		= ${SCRS:.c=.o}

RM			= rm -f

NAME		= cube3d.out

CC			= gcc

CFLAG		= -Wall -Werror -Wextra

DIR_LIBFT	= libft

all:		${NAME}

.c.o:
	${CC} -g ${CFLAG} -c  $< -o ${<:.c=.o}

${NAME}:	lib ${OBJS}
	${CC} -g -lmlx -framework OpenGL -framework AppKit ${DIR_LIBFT}/libft.a ${OBJS} -o ${NAME}

lib:
	make -C $(DIR_LIBFT) all

clean:
	make -C $(DIR_LIBFT) clean
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all