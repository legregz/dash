# Variables
CXX = g++
CXXFLAGS = -Wall -O2
LDFLAGS = -lSDL2 -lSDL2_ttf
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TARGET = dash

# Liste des fichiers source
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Règle par défaut
all: $(BINDIR)/$(TARGET)

# Règle pour créer l'exécutable
$(BINDIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Règle pour compiler les fichiers source en fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(BINDIR)/$(TARGET)
