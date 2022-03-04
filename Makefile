SERVER_SRCS	= server.c server_utils.c
CLIENT_SRCS = client.c
UTILS_SRCS = utils.c

SERVER_OBJS	= ${SERVER_SRCS:.c=.o}
CLIENT_OBJS = ${CLIENT_SRCS:.c=.o}
UTILS_OBJS = ${UTILS_SRCS:.c=.o}

SERVER_SRCS_B =	server_bonus.c server_utils_bonus.c
CLIENT_SRCS_B =	client_bonus.c
UTILS_SRCS_B = utils_bonus.c

SERVER_OBJS_B =	${SERVER_SRCS_B:.c=.o}
CLIENT_OBJS_B =	${CLIENT_SRCS_B:.c=.o}
UTILS_OBJS_B = ${UTILS_SRCS_B:.c=.o}

NAME1 = server
NAME2 = client

CC	= gcc
RM	= rm -f
FLAGS	= -Wall -Werror -Wextra
D_FILES	= $(patsubst %.c,%.d,$(SERVER_SRCS) $(CLIENT_SRCS) $(UTILS_SRCS) $(SERVER_SRCS_B) $(CLIENT_SRCS_B) $(UTILS_SRCS_B))

%.o:	%.c
		${CC} ${FLAGS} -c $< -o ${<:.c=.o} -MMD

all:	$(NAME1) $(NAME2)

$(NAME1):	.server_b $(SERVER_OBJS) $(UTILS_OBJS)
			$(CC) $(FLAGS) $(SERVER_OBJS) $(UTILS_OBJS) -o $(NAME1)
			@touch .server

$(NAME2):	.client_b $(CLIENT_OBJS) $(UTILS_OBJS)
			$(CC) $(FLAGS) $(CLIENT_OBJS) $(UTILS_OBJS) -o $(NAME2)
			@touch .client

server_b:	.server $(SERVER_OBJS_B) $(UTILS_OBJS_B)
			$(CC) $(FLAGS) $(SERVER_OBJS_B) $(UTILS_OBJS_B) -o $(NAME1)
			@touch server_b
			@touch .server_b

client_b:	.client $(CLIENT_OBJS_B) $(UTILS_OBJS_B)
			$(CC) $(FLAGS) $(CLIENT_OBJS_B) $(UTILS_OBJS_B) -o $(NAME2)
		@touch client_b
		@touch .client_b

-include	$(D_FILES)

clean:
		${RM} $(SERVER_OBJS) $(CLIENT_OBJS) $(UTILS_OBJS)
		$(RM) $(SERVER_OBJS_B) $(CLIENT_OBJS_B) $(UTILS_OBJS_B)
		$(RM) .server .server_b .client .client_b
		$(RM) server_b client_b
		$(RM) $(D_FILES)

fclean:	clean
		${RM} $(NAME1) $(NAME2)

re:	fclean all

bonus:	server_b client_b

.server:
		@touch .server

.server_b:
		@touch .server_b

.client:
		@touch .client

.client_b:
		@touch .client_b



.PHONY:	all clean fclean re bonus
