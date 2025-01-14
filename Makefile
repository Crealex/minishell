NAME	=	minishell
LIBFT	=	libft/libft.a
SRCS	=	$(addprefix srcs/, main.c parsing.c)
BUILTINS	=	$(addprefix srcs/builtins/, ft_echo.c)
#prevoir plusieurs dossier dans srcs
OBJS	=	${SRCS:%.c=${OBJDIR}/%.o}
OBJSB	=	${BUILTINS:%.c=${OBJDIR}/%.o}
CC		=	gcc
CFLAGS	=	-Werror -Wextra -Wall
OBJDIR	=	objets

# Colors and style
END		:= \033[0m
WHITE	:= \033[1;37m
NC		:= \033[0m
PINK	:= \033[1;35m
GREEN	:= \033[32m
BOLD	:= \033[1m
L_PURPLE:= \033[38;5;55m
YELLOW	:= \033[33m
BLUE	:= \033[34m

# Counter for compiled files
TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE = 0

all:	${NAME} display_ascii

${NAME}:	${OBJS} ${OBJSB} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJS} ${OBJSB} ${LIBFT} -lreadline -o ${NAME}
	@echo "${BOLD}${GREEN}📦 Link complete: ${NAME}${END}"

${LIBFT}:
	@echo "${BOLD}${BLUE}🔨 Building LIBFT...${END}"
	@${MAKE} -C ./libft/ bonus
	@echo "${BOLD}${GREEN}✓ LIBFT ready${END}"

${OBJDIR}/%.o: %.c | ${OBJDIR}
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@printf "${BOLD}${L_PURPLE}⚡ [%2d/%2d] Compiling: %-20s ${END}" $(CURRENT_FILE) $(TOTAL_FILES) "$<"
	@${CC} ${CFLAGS} -c -o $@ $<
	@echo "${BOLD}${GREEN}✓${END}"

${OBJDIR}:
	@mkdir -p ${OBJDIR}
	@mkdir -p ${OBJDIR}/srcs
	@mkdir -p ${OBJDIR}/srcs/builtins
	@echo "${BOLD}${BLUE}📁 Created objects directory${END}"

test: ${TSRCS}
	${CC} $(TSRCS) -o test

clean:
	@echo "${BOLD}${YELLOW}🧹 Cleaning objects...${END}"
	@rm -rf ${OBJDIR}
	@${MAKE} -C ./libft/ clean
	@echo "${BOLD}${GREEN}✓ Clean complete${END}"

fclean: clean
	@echo "${BOLD}${YELLOW}🗑️  Deep cleaning...${END}"
	@rm -f ${NAME}
	@${MAKE} -C ./libft/ fclean
	@echo "${BOLD}${GREEN}✨ All clean ✨${END}"

re: fclean all

.PHONY: all clean fclean re display_ascii

display_ascii:
	@echo "$(BOLD)$(L_PURPLE)"
	@if [ -f ascii_art.txt ]; then \
		cat ascii_art.txt; \
	fi
	@echo "$(END)"
	@echo "${BOLD}${L_PURPLE} ✨minishell✨ ${GREEN}is ready 🎉 ${END}"
	@echo "${BOLD}${BLUE}➜ Use ./${NAME} to run the program${END}"
