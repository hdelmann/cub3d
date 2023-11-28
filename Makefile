NAME        := cub3d
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -g
SRCS        :=      src/fct_utils.c \
                          src/calculate_line.c \
                          src/calculate_line2.c \
                          src/calculate_line3.c \
                          src/texture_handling.c \
                          src/main.c \
						  src/key_handler.c \
						  src/key_handler2.c \
                          src/rendering3D.c \
                          src/mapset.c \
                          src/mapset2.c \
                          src/mapset3.c \
                          src/rendering2d.c \
                          src/draw.c \
                          getnext/get_next_line_utils.c \
                          getnext/get_next_line.c \
						  src/txt_utils.c \
						  src/fct_utils2.c \
						  src/fct_utils3.c \
						  src/fct_utils4.c \
						  src/fct_utils5.c \
                          src/parsing.c \
						  src/parsing2.c \
						  src/parsing3.c \
						  src/parsing4.c \
						  src/parsing5.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

RM		    := rm -f

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Darwin)
$(NAME): ${OBJS}
			@ $(MAKE) -C mlx all >/dev/null 2>&1
			@ cp ./mlx/libmlx.a .
			$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(OBJS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
endif

ifeq ($(UNAME), Linux)
$(NAME): ${OBJS}
			@chmod 777 mlx_linux/configure
			@ $(MAKE) -C mlx_linux all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
endif

all:		${NAME}

ifeq ($(UNAME), Darwin)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
endif

ifeq ($(UNAME), Linux)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
endif


ifeq ($(UNAME), Linux)
fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean 
endif

ifeq ($(UNAME), Darwin)
fclean:		clean
			@ ${RM} ${NAME}
			@ rm libmlx.a
endif

re:			fclean all

.PHONY:		all clean fclean re


