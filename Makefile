NAME1 = predict
NAME2 = train
SRC1 = ./linear_reg.cpp
SRC2 = ./train.cpp
OBJ1 = ./linear_reg.o
OBJ2 = ./train.o

all: $(NAME1) $(NAME2)

$(NAME1):
		@g++ -c ./linear_reg.cpp
		@g++ ./linear_reg.o -o predict

$(NAME2):
		@g++ -c $(SRC2)
		@g++ $(OBJ2) -o $(NAME2)

clean:
		@rm -f $(OBJ1)
		@rm -f $(OBJ2)

fclean: clean
		@rm -f $(NAME1)
		@rm -f $(NAME2)
		@rm -f out_put.csv
		@rm -f model.txt

re: fclean all

