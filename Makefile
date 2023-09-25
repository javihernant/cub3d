NAME=cub3d
CC=gcc
CFLAGS=-Wall -Wextra -Werror
IFLAGS=-I. -I./include -I./minilibx-linux
LFLAGS=-Lminilibx-linux -L/usr/lib
TESTS=
SRC=src/main.c src/minimap.c src/position.c src/raycast.c src/init.c src/libft/errors.c src/mlxutils/utils1.c src/mlxutils/draw_line.c
OBJ=$(SRC:.c=.o)
COMPILED_OBJS=$(shell find . -name '*.o')
DBG=-g
LIBS= -lmlx_Linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME) $(LIBS) $(DBG)

%.o:%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ $(DBG) $(LIBS)

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(COMPILED_OBJS)

re: fclean all
