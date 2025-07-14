# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/12 13:07:24 by jlima-so          #+#    #+#              #
#    Updated: 2025/06/20 13:13:10 by jlima-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLB_DIR=			minilibx-linux/

MLB_FILE=			$(wildcard ${MLB_DIR}*.c)

MLB_OBJ=			${MLB_FILE:.c=.o}

MLBLIB=				minilibx-linux/libmlx_Linux.a

MLBMAC=				minilibx-linux/libmlx.a

MLX_LINUX_FLAGS=	-Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz

MLX_MAC_FLAGS=		

PROJ=fractol

PROJ_BONUS=	${PROJ}_bonus

FRCT_DIR=	${PROJ}_dir/

BONUS_DIR=	${PROJ}_bonus_dir/

SRC_DIR1=my_libft/
SRC_DIR2=my_libft/libft/
SRC_DIR3=my_libft/get_next_line/

SRC_LIB=	$(wildcard ${SRC_DIR1}*.c) \
			$(wildcard ${SRC_DIR2}*.c) \
			$(wildcard ${SRC_DIR3}*.c)

OBJ_LIB=	${SRC_LIB:.c=.o}

SRC_FILES=  $(wildcard ${FRCT_DIR}*.c) \
			$(wildcard ${FRCT_DIR}*.c) \

OBJ_FILES=	${SRC_FILES:.c=.o}

SRC_BONUS=	$(wildcard ${BONUS_DIR}*.c)

OBJ_BONUS=	${SRC_BONUS:.c=.o}

NAME=${PROJ}.a

LIBFT=libft.a

BONUS_ARQ=bonus.a

HDR_FILE= ${PROJ}.h

CC=cc

AR=ar rcs

CFLAGS= -w -I/usr/include -O3

HD=
#-D HIGHT=100

all: re ${PROJ}

libx:minilibx-linux

minilibx-linux:
	git clone https://github.com/42paris/minilibx-linux.git

${MLBLIB}:
	cd minilibx-linux && make

${MLBMAC}:
	cd minilibx-linux && make

gpu.o: make_fractols.cu
	nvcc -lineinfo -Xcompiler -Iminilibx-linux -I/usr/include -O3 -c make_fractols.cu -o gpu.o

cpu.o: make_fractols.c
	cc ${CFLAGS} -c make_fractols.c -o cpu.o

cuda: ${MLBLIB} cuda.a

cuda.a: re ${OBJ_FILES} gpu.o ${LIBFT} 
	${AR} cuda.a ${OBJ_FILES} gpu.o
	${CC} ${CFLAGS} ${PROJ}.c cuda.a ${LIBFT} ${MLBLIB} ${MLX_LINUX_FLAGS} ${HD} -lcudart -o ${PROJ}

${NAME}: ${OBJ_FILES} cpu.o 
	${AR} ${NAME} ${OBJ_FILES} cpu.o 

${LIBFT}: ${OBJ_LIB}
	cd my_libft && make

#${BONUS_ARQ}: ${OBJ_BONUS}
#	${AR} ${BONUS_ARQ} $?

${PROJ}: ${NAME} ${LIBFT} ${PROJ}.c ${HDR_FILE} ${MLBLIB}
	${CC} ${CFLAGS} ${PROJ}.c ${NAME} ${LIBFT} ${MLBLIB} ${MLX_LINUX_FLAGS} ${HD} -o ${PROJ}

#${PROJ_BONUS}: ${NAME} ${LIBFT} ${BONUS_ARQ} ${PROJ_BONUS}.c ${HDR_FILE} ${MLBLIB}
#	${CC} ${CFLAGS} ${PROJ_BONUS}.c ${BONUS_ARQ} ${NAME} ${LIBFT} ${MLBLIB} ${MLX_LINUX_FLAGS} ${HD} -o ${PROJ_BONUS}

#mac: ${NAME} ${LIBFT} ${PROJ}.c ${HDR_FILE}
#	${CC} ${CFLAGS} ${PROJ}.c ${NAME} ${LIBFT} ${MLBMAC} ${MLX_MAC_FLAGS} ${HD} -o ${PROJ}
#	touch mac

#mac_bonus: ${NAME} ${LIBFT} ${BONUS_ARQ} ${PROJ_BONUS}.c ${HDR_FILE}
#	${CC} ${CFLAGS} ${PROJ_BONUS}.c ${BONUS_ARQ} ${NAME} ${LIBFT} ${MLBMAC} ${MLX_MAC_FLAGS} ${HD} -o ${PROJ_BONUS}
#	touch mac_bonus

bonus: ${PROJ_BONUS}
	@touch bonus

clean:
	rm -f *.o ${OBJ_FILES} ${OBJ_BONUS} ${OBJ_LIB} ${BONUS_ARQ} ${NAME} ${LIBFT} bonus

fclean: clean
	rm -f ${NAME} ${PROJ}

re: fclean all

.PHONY: re fclean clean all

# so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC_FILES)
#	gcc -nostartfiles -shared -o libft.so $(OBJ_FILES)
# 