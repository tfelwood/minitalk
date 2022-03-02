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

CC	= gcc
RM	= rm -f
FLAGS	= -Wall -Werror -Wextra
D_FILES	= $(patsubst %.c,%.d,$(SERVER_SRCS) $(SERVER_SRCS_B) $(CLIENT_SRCS) $(CLIENT_SRCS_B))

%.o:	%.c
		${CC} ${FLAGS} -c $< -o ${<:.c=.o} -MMD

all:	.mandatory

$(SERVER): .check_bonus $(SERVER_OBJS)
			CC $(FLAGS) $(SERVER_OBJS) -o $(SERVER)


$(CLIENT):	.check_bonus $(CLIENT_OBJS)
			CC $(FLAGS) $(CLIENT_OBJS) -o $(CLIENT)

clean:
		${RM} ${SERVER_OBJS} ${CLIENT_OBJS}
		$(RM) $(SERVER_OBJS_B) $(CLIENT_OBJS_B)
		$(RM) .check .check_bonus
		$(RM) .bonus .mandatory
		$(RM) $(D_FILES)

fclean:	clean
		${RM} ${SERVER} ${CLIENT}

re:	fclean all

.check:
		touch .check

.check_bonus:
		touch .check_bonus

.bonus: .check $(SERVER_OBJS_B) $(CLIENT_OBJS_B)
		CC $(FLAGS) $(SERVER_OBJS_B) -o $(SERVER)
		CC $(FLAGS) $(CLIENT_OBJS_B) -o $(CLIENT)
		touch .check_bonus
		touch .bonus

.mandatory: .check_bonus $(SERVER_OBJS) $(CLIENT_OBJS)
		CC $(FLAGS) $(SERVER_OBJS) -o $(SERVER)
		CC $(FLAGS) $(CLIENT_OBJS) -o $(CLIENT)
		touch .check
		touch .mandatory

bonus: .bonus

-include	$(D_FILES)

.PHONY:	all clean fclean re bonus