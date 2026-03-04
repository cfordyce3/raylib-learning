alias b := build
alias r := run

# build main
build:
    gcc -o rl rl.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# build and run main
run: build
    ./rl
