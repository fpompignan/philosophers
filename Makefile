NAME = philo

SRC =	main.c \
		utils.c \
		exit.c \
		thread.c \
		routine.c \
		affichage.c \

### Librairies ###
HEADERS = ./includes/
INC = philo.h
vpath %.h $(HEADERS)

### Sources ###
PATHSRCS = ./srcs
SRCS = $(addprefix $(PATHSRCS)/,$(SRC))

### Objets ###

OBJS = $(SRCS:.c=.o)

### Flags ###
FLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

LIBS = -lpthread

all: $(NAME)

$(NAME): $(OBJS)
		gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)



re:	fclean all

.PHONY:	all clean fclean re titre
