TARGET  = btc

CXX      = c++

OBJDIR  = obj

CXXFLAGS = -Werror -Wall -Wextra -std=c++98 -g3 -fsanitize=address

SRC     = BitcoinExchange.cpp parseFile.cpp main.cpp

OBJ     = $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.cpp %.hpp
	@rm -rf $(OBJDIR)/main.o
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -fr $(TARGET) $(OBJDIR)

re: fclean $(TARGET)

.PHONY: clean fclean re