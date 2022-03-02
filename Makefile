SERVER_SRCS	= server.c server_utils.c utils.c
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
CHECK_FILE_B = check_b.tmp
CC	= gcc
RM	= rm -f
FLAGS	= -Wall -Werror -Wextra
D_FILES	= $(patsubst %.c,%.d,$(SERVER_SRCS) $(SERVER_SRCS_B) $(CLIENT_SRCS) $(CLIENT_SRCS_B))
%.o:	%.c
		${CC} ${FLAGS} -c $< -o ${<:.c=.o} -MMD

all:	$(SERVER) $(CLIENT)


$(SERVER):	$(SERVER_OBJS)
			CC $(FLAGS) $(SERVER_OBJS) -o $(SERVER)

$(CLIENT):	$(CLIENT_OBJS)
			CC $(FLAGS) $(CLIENT_OBJS) -o $(CLIENT)

$(SERVER_B):	$(SERVER_OBJS_B)
				CC $(FLAGS) $(SERVER_OBJS_B) -o $(SERVER)

$(CLIENT_B):	$(CLIENT_OBJS_B)
				CC $(FLAGS) $(CLIENT_OBJS_B) -o $(CLIENT)

$(CHECK_FILE):	$(SERVER_B) $(CLIENT_B)

#@touch CHECK_FILE

$(CHANGE):	$(CHECK_FILE)

-include	$(D_FILES)
clean:
		${RM} ${SERVER_OBJS} ${CLIENT_OBJS}
		$(RM) $(SERVER_OBJS_B) $(CLIENT_OBJS_B)
		$(RM) $(CHECK_FILE)
		$(RM) $(D_FILES)

fclean:	clean
		${RM} ${SERVER} ${CLIENT}

re:	fclean all

bonus:	$(CHECK_FILE)

#make SERVER_OBJS="$(SERVER_OBJS_B)" CLIENT_OBJS="$(CLIENT_OBJS_B)" HEADER="$(HEADER_B)" $(CHECK_FILE)

.PHONY:	all clean fclean re bonus