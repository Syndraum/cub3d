SCRS		= 	main.c \
				ft_img.c \
				ft_print.c \
				ft_windows.c

OBJS		= ${SCRS:.c=.o}

RM			= rm -f

NAME		= cube3d.out

CC			= gcc

CFLAG		= -Wall -Werror -Wextra

all:		${NAME}

.c.o:
	${CC} ${CFLAG} -c  $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	${CC} -lmlx -framework OpenGL -framework AppKit ${OBJS} -o ${NAME}

clean:	
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all