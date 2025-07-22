SRC = src
BUILD = build
BIN = bin

ASM_SRC = $(SRC)\asmfile.asm
C_SRC = $(SRC)\cfile.c
ASM_OBJ = $(BUILD)\asmfile.obj
C_OBJ = $(BUILD)\cfile.obj
EXE = $(BIN)\a.exe

all: build bin $(EXE)

build:
	@echo Creating build directory...
	mkdir build
	@echo.

bin:
	@echo Creating bin directory...
	mkdir bin
	@echo.

$(EXE): $(ASM_OBJ) $(C_OBJ)
	@echo Linking objects to create executable...
	gcc $^ -o $@ -m64
	@echo.

$(ASM_OBJ): $(ASM_SRC)
	@echo Assembling $(ASM_SRC) to $(ASM_OBJ)...
	nasm -f win64 $< -o $@
	@echo.

$(C_OBJ): $(C_SRC)
	@echo Compiling $(C_SRC) to $(C_OBJ)...
	gcc -c $< -o $@ -m64
	@echo.

run: build bin $(EXE)
	@echo Running executable...
	@echo.
	@$(EXE)
	@echo.

clean:
	@echo Cleaning build and bin directories...
	del /Q build\* bin\* 2>nul
	@echo.