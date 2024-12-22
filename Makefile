# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrafai <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 00:51:04 by yrafai            #+#    #+#              #
#    Updated: 2024/12/18 00:51:10 by yrafai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
CLIENT_SRCS = src/client.c
SERVER_SRCS = src/server.c
CLIENT_BONUS_SRCS = src/client_bonus.c
SERVER_BONUS_SRCS = src/server_bonus.c
LIBFT_PATH = libft
LIBFT_ARCHIVE = $(LIBFT_PATH)/libft.a
CLIENT_NAME = client
SERVER_NAME = server
CLIENT_BONUS_NAME = client_bonus
SERVER_BONUS_NAME = server_bonus

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_SRCS) -L$(LIBFT_PATH) -lft

$(SERVER_NAME): $(SERVER_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_SRCS) -L$(LIBFT_PATH) -lft

$(CLIENT_BONUS_NAME): $(CLIENT_BONUS_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_BONUS_SRCS) -L$(LIBFT_PATH) -lft

$(SERVER_BONUS_NAME): $(SERVER_BONUS_SRCS) $(LIBFT_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_BONUS_SRCS) -L$(LIBFT_PATH) -lft

$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

re: fclean all

bonus: $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

.PHONY: all clean fclean re bonus
