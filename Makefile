CC = clang++
CFLAGS = -Wall -Wextra -Werror -lncurses

NAME = ft_retro

SRC = class/AEntity.cpp \
		class/Projectile.cpp \
		class/SpaceShip.cpp \
		src/gameMgt.cpp \
		src/ncurses.cpp \
		src/main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
		@$(CC) $(CFLAGS) $^

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all