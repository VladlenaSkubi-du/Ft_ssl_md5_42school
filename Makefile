# ------------  PROJECT  ----------------------------------------------------- #

NAME :=	ft_ssl

# ------------  FLAGS  ------------------------------------------------------- #

FLAGS := -Wall -Wextra #-Werror
FLAGS += -g

# ------------  SOURCE FILES  ------------------------------------------------ #

PRINT_FUNCTIONS_DIR := print_functions
PRINT_FUNCTIONS := \
			$(PRINT_FUNCTIONS_DIR)/print_options.c \
			$(PRINT_FUNCTIONS_DIR)/print_bits_little_endian.c \
			$(PRINT_FUNCTIONS_DIR)/print_bits_big_endian.c \
			$(PRINT_FUNCTIONS_DIR)/md5_print_round_values.c \
			$(PRINT_FUNCTIONS_DIR)/md5_print_algo_values.c

MD5_DIR := md5
MD5 := \
			$(MD5_DIR)/md5_start.c \
			$(MD5_DIR)/md5_prepare_message.c \
			$(MD5_DIR)/md5_calculation_algo.c \
			$(MD5_DIR)/md5_init_plays.c \
			$(MD5_DIR)/md5_init_fun_functions.c \
			$(MD5_DIR)/md5_logic_bit_operations.c \
			$(MD5_DIR)/md5_smessage_block_methods.c \
			$(MD5_DIR)/md5_sconst_and_shift_methods.c \
			$(MD5_DIR)/md5_svariables_buffer_methods.c \
			$(MD5_DIR)/md5_svariables_block_methods.c

SHA256_DIR := sha256
SHA256 := \
			$(SHA256_DIR)/sha256_start.c

SOURCES := main.c \
			ssl_parsing.c \
			$(MD5) \
			$(SHA256) \
			$(PRINT_FUNCTIONS)

# ------------  DIRECTORIES  ------------------------------------------------- #

DIR_O := objs
DIR_S := srcs
INCLUDE_DIR = includes

# ------------  LIBFT  ------------------------------------------------------- #

LIBFT_DIR := libft
LIB_INCLUDE_DIR := $(LIBFT_DIR)/includes
LIB_PRINTF_INCLUDE_DIR := $(LIBFT_DIR)/ft_printf/includes
LIB_HEADERS := \
			$(wildcard $(LIB_INCLUDE_DIR)/*.h) \
			$(wildcard $(LIB_PRINTF_INCLUDE_DIR)/*.h)

# ------------  INCLUDE FILES  ----------------------------------------------- #

INCLUDES := \
			-I $(INCLUDE_DIR) \
			-I $(LIB_INCLUDE_DIR) \
			-I $(LIB_PRINTF_INCLUDE_DIR)

# ------------  FILEPATHS  --------------------------------------------------- #

SRCS := $(addprefix $(DIR_S)/,$(SOURCES))
OBJS := $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))
LIBFT := $(addsuffix .libft , $(LIBFT_DIR)/)

# ------------  RULES  ------------------------------------------------------- #

.PHONY: all clean fclean re

%.libft:  $(LIB_HEADERS)
	make -C $*

LIBS_INCLUDED = -L $(LIBFT_DIR) -lft

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJS)
	@echo "\033[32;01mCompiling ft_ssl...\033[0m"
	gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBS_INCLUDED)
	@echo "\033[32;01mft_ssl is ready\033[0m"

$(OBJS): $(DIR_O)/%.o: $(DIR_S)/%.c $(wildcard $(INCLUDE_DIR)/*.h) | $(DIR_O)

	gcc $(FLAGS) -c $(INCLUDES) -o $@ $<

$(DIR_O):
	mkdir -p $(DIR_O)
	mkdir -p $(DIR_O)/$(MD5_DIR)
	mkdir -p $(DIR_O)/$(SHA256_DIR)
	mkdir -p $(DIR_O)/$(PRINT_FUNCTIONS_DIR)

clean:
	@echo "\033[34mDeleting ft_ssl o-files\033[0m"
	/bin/rm -rf $(DIR_O)
	make clean --directory $(LIBFT_DIR)

fclean: clean
	@echo "\033[34mDeleting ft_ssl binary\033[0m"
	/bin/rm -f $(NAME)
	make fclean --directory $(LIBFT_DIR)

re: fclean all
