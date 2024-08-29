CC=cc
CFLAGS=-Wall -Wextra -Werror -Wunreachable-code


# ชื่อของโปรแกรม
NAME=pipex

# ไฟล์ทั้งหมดที่เกี่ยวข้อง
SRCS=main.c utils.c utils2.c ft_split.c process.c free.c find_env.c extend.c err_msg.c
OBJS=$(SRCS:.c=.o)
HEADER=pipex.h
# กฎสำหรับการคอมไพล์ .c เป็น .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# กฎสำหรับการสร้างโปรแกรมหลัก
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# กฎสำหรับสร้างทุกอย่าง
all: $(NAME)
# $(NAME): $(OBJS)
# 	@if [ ! -f $(NAME) ]; then \
# 		$(CC) $(CFLAGS) $(OBJS) -o $(NAME); \
# 	fi

# กฎสำหรับการลบไฟล์ที่สร้างจากการคอมไพล์
clean:
	rm -f $(OBJS)

# กฎสำหรับการลบไฟล์ทั้งหมด
fclean: clean
	rm -f $(NAME)

# กฎสำหรับการสร้างทุกอย่างใหม่
re: fclean all

# กฎสำหรับไม่ต้องพิจารณาไฟล์ชั่วคราวหรือโปรแกรมที่มีชื่อเหมือนกัน
.PHONY: all clean fclean re