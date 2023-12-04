TARGET  = PmergeMe

CC      = c++

OBJDIR  = obj

CXXFLAG += -Werror -Wall -Wextra -std=c++98 -g3 -fsanitize=address

SRC     = PmergeMe.cpp main.cpp

OBJ     = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

all: $(TARGET) 

$(TARGET): $(OBJ)
	$(CC) $(CXXFLAG) -o $@ $^

$(OBJDIR)/%.o: %.cpp %.hpp
	@rm -rf $(OBJDIR)/main.o
	@mkdir -p $(@D)
	$(CC) $(CXXFLAG) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CXXFLAG) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -fr $(TARGET) $(OBJDIR)

re: fclean $(TARGET)

.PHONY: clean fclean re