.HONY: all run

TARGET := MazeApp
SRC := 
SRC := $(SRC) ./App.cpp ./MazeLayer.cpp


CC := clang
CXX := clang++
LD := clang++
AR := ar
RANLIB :=
CFLAGS := -g -O3 -MP -MMD
CXXFLAGS := $(CFLAGS) -std=c++20 -xc++
APPROOT := ./
ENGINENAME := DrawEngine
ENGINEROOT := ./../$(ENGINENAME)/
ENGINESRC := $(ENGINEROOT)/DrawEngine/
OBJDIR := ./obj/
BINDIR := ./../bin/
SRCDIR := ./src/
INCLUDE := -I/opt/homebrew/include/ -I/usr/include/ -I/usr/local/include/ 
INCLUDE := $(INCLUDE) -I/opt/homebrew/Cellar/sfml/2.6.1/include/
INCLUDE := $(INCLUDE) -I$(ENGINEROOT)/vendor/spdlog/include/
INCLUDE := $(INCLUDE) -I$(ENGINESRC) 
INCLUDE := $(INCLUDE) -I$(ENGINESRC)Core -I$(ENGINESRC)Debug 
INCLUDE := $(INCLUDE) -I$(ENGINESRC)Utils -I$(ENGINESRC)MacOs -I$(ENGINESRC)Events -I$(ENGINESRC)UI
INCLUDE := $(INCLUDE) -I$(ENGINESRC)SFML -I$(ENGINESRC)Renderer

LIBS := -lm
SFMLLIB := -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
LDFLAGS := -L/usr/lib -L/usr/local/lib $(SFMLLIB)
PCH_OUT := $(OBJDIR)$(ENGINENAME)/pch.gch
PCH_SRC := $(ENGINESRC)pch.cpp
PCH_HEADERS := $(ENGINESRC)pch.h

SRC := $(SRC) ./Core/Application.cpp ./Core/Layer.cpp ./Core/LayerStack.cpp ./Core/Log.cpp ./Core/Window.cpp
SRC := $(SRC) ./MacOs/MacOsWindow.cpp ./MacOs/MacOsInput.cpp ./MacOs/MacOsPlatformUtils.cpp
SRC := $(SRC) ./SFML/SfmlContext.cpp ./SFML/SfmlRendererAPI.cpp
SRC := $(SRC) ./Renderer/GraphicsContext.cpp ./Renderer/RenderCommand.cpp ./Renderer/Renderer.cpp ./Renderer/RendererAPI.cpp
SRC := $(SRC) ./Renderer/Renderer2D.cpp

OBJS  := $(addprefix $(OBJDIR), $(SRC:.cpp=.o)) 
DEPS  := $(addprefix $(OBJDIR), $(SRC:.cpp=.d))

all: $(BINDIR)$(TARGET)

run:
	$(BINDIR)$(TARGET)

$(BINDIR)$(TARGET): $(OBJS)
	@echo '$$'LDFLAGS is $(LDFLAGS)
	mkdir -p $(@D)
	$(LD) $^ -o $@ $(LDFLAGS) $(FRAMEWORKS)

$(PCH_OUT): $(PCH_SRC) $(PCH_HEADERS)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -x c++-header

$(OBJDIR)%.o: $(SRCDIR)/%.cpp $(PCH_OUT)
	# @[ -d $(OBJDIR) ]
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -include $(PCH_HEADERS)

$(OBJDIR)%.o: $(ENGINESRC)/%.cpp $(PCH_OUT)
	# @[ -d $(OBJDIR) ]
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -include $(PCH_HEADERS)

$(OBJDIR)%.o: %.cpp $(PCH_OUT)
	# @[ -d $(OBJDIR) ]
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $< -include $(PCH_HEADERS)

debug : $(BINDIR)$(TARGET)
	@echo "debug $(BINDIR)$(TARGET)"
	lldb $(BINDIR)$(TARGET)

clean :
	rm -rf $(BINDIR) $(OBJDIR) *.json *.log

-include $(DEPS)
