SERVER_SRCS	= server.c utils.c
CLIENT_SRCS = client.c utils.c
SERVER_OBJS	= ${SERVER_SRCS:.c=.o}
CLIENT_OBJS = ${CLIENT_SRCS:.c=.o}
SERVER_SRCS_B =	server_bonus.c utils_bonus.c
CLIENT_SRCS_B =	client_bonus.c utils_bonus.c
SERVER_OBJS_B =	${SERVER_SRCS_B:.c=.o}
CLIENT_OBJS_B =	${CLIENT_SRCS_B:.c=.o}
SERVER	= server
CLIENT = client
HEADER	= minitalk.h
HEADER_B = minitalk_bonus.h
CHECK_FILE = check.tmp
CC	= gcc
RM	= rm -f
FLAGS	= -Wall -Werror -Wextra

%.o:	%.c $(HEADER)
		${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all:	$(SERVER) $(CLIENT)
		touch $(CHECK_FILE)

$(SERVER):	$(SERVER_OBJS)
			CC $(FLAGS) $(SERVER_OBJS) -o $(SERVER)

$(CLIENT):	$(CLIENT_OBJS)
			CC $(FLAGS) $(CLIENT_OBJS) -o $(CLIENT)

$(CHECK_FILE):	$(SERVER_OBJS) $(CLIENT_OBJS)
				$(all)

$(CHANGE):	$(CHECK_FILE)


clean:
		${RM} ${SERVER_OBJS} ${CLIENT_OBJS}
		$(RM) $(SERVER_OBJS_B) $(CLIENT_OBJS_B)
		$(RM) $(CHECK_FILE)

fclean:	clean
		${RM} ${SERVER} ${CLIENT}

re:	fclean all

bonus:	$(CHECK_FILE)
		make SERVER_OBJS="$(SERVER_OBJS_B)" CLIENT_OBJS="$(CLIENT_OBJS_B)" HEADER="$(HEADER_B)" $(CHECK_FILE)

.PHONY:	all clean fclean re bonus