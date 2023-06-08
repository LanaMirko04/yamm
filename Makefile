CC := gcc
CFLAGS := -g -Wall -D_SLOG_DEBUG
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lslog
TARGET := yamm
SRCDIR := src
BUILDDIR := build
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)
