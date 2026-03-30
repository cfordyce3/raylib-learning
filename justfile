alias b := build
alias r := run

# build main
@build:
    gcc -Wall -Wextra -std=c23 -pedantic -o obj/rl src/rl.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    echo "Built successfully to obj/rl"

# build and run main
@run: build
    ./obj/rl
