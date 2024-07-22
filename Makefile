NAME        = Minesweeper

CXX         = g++

CXXFLAGS    = -Wall -Wextra -Werror -g

RM          = rm -f

SRCS        = $(wildcard *.cpp) 

OBJS        = $(SRCS:.cpp=.o)

%.o: %.cpp
			$(CXX) $(CXXFLAGS) -c $< -o $@

all:        $(NAME)

$(NAME):    $(OBJS) 
			$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS) 

fclean:     clean
			$(RM) $(NAME)

re:         fclean all

.PHONY:     all clean fclean re