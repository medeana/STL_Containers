NAME	= vector

GCC	= c++  

FLAGS	= -Wall -Wextra -Werror -std=c++98

SRCS	= main.cpp

OBJS	= $(SRCS:.cpp=.o)

%.o: %.cpp iterator_traits.hpp random_access_iterator.hpp reverse_iterator.hpp vector.hpp
	$(GCC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(GCC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re