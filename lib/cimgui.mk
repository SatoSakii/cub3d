SRCS = ./lib/cimgui/cimgui.cpp \
       ./lib/cimgui/imgui/imgui.cpp \
       ./lib/cimgui/imgui/imgui_draw.cpp \
       ./lib/cimgui/imgui/imgui_demo.cpp \
       ./lib/cimgui/imgui/imgui_tables.cpp \
       ./lib/cimgui/imgui/imgui_widgets.cpp \
       ./lib/cimgui/imgui/backends/imgui_impl_sdl2.cpp \
       ./lib/cimgui/imgui/backends/imgui_impl_vulkan.cpp

CXXFLAGS = -O3 -fno-exceptions -fno-rtti -I /usr/include/SDL2 \
           -D CIMGUI_USE_VULKAN -D CIMGUI_USE_SDL2 \
           -D IMGUI_IMPL_VULKAN_NO_PROTOTYPES -D IMGUI_IMPL_API="extern \"C\"" \
           -I ./lib/cimgui/imgui/ -Wall -shared -fPIC

LDFLAGS = -pthread

OUTPUT = ./lib/cimgui/cimgui.so

all: $(OUTPUT)

$(OUTPUT): $(SRCS)
	@mkdir -p $(dir $(OUTPUT))  # Assure que le dossier existe
	$(CXX) -o $(OUTPUT) $(SRCS) $(CXXFLAGS) $(LDFLAGS)

clean:
	@echo "hihi"

fclean: clean
	@rm -f $(OUTPUT)

re: fclean all

.PHONY: all fclean re
