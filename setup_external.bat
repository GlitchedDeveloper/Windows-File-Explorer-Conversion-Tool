@echo off
setlocal

if not exist external mkdir external
cd external

if not exist imgui mkdir imgui
cd imgui

echo [Downloading files...]

set IMGUI=https://raw.githubusercontent.com/ocornut/imgui/master
curl -s -L -o imgui.h              %IMGUI%/imgui.h                       && echo external/imgui/imgui.h
curl -s -L -o imgui.cpp            %IMGUI%/imgui.cpp                     && echo external/imgui/imgui.cpp
curl -s -L -o imgui_draw.cpp       %IMGUI%/imgui_draw.cpp                && echo external/imgui/imgui_draw.cpp
curl -s -L -o imgui_tables.cpp     %IMGUI%/imgui_tables.cpp              && echo external/imgui/imgui_tables.cpp
curl -s -L -o imgui_widgets.cpp    %IMGUI%/imgui_widgets.cpp             && echo external/imgui/imgui_widgets.cpp
curl -s -L -o imconfig.h           %IMGUI%/imconfig.h                    && echo external/imgui/imconfig.h
curl -s -L -o imgui_internal.h     %IMGUI%/imgui_internal.h              && echo external/imgui/imgui_internal.h
curl -s -L -o imstb_textedit.h     %IMGUI%/imstb_textedit.h              && echo external/imgui/imstb_textedit.h
curl -s -L -o imstb_rectpack.h     %IMGUI%/imstb_rectpack.h              && echo external/imgui/imstb_rectpack.h
curl -s -L -o imstb_truetype.h     %IMGUI%/imstb_truetype.h              && echo external/imgui/imstb_truetype.h

if not exist backends mkdir backends
cd backends

curl -s -L -o imgui_impl_win32.h   %IMGUI%/backends/imgui_impl_win32.h   && echo external/imgui/backends/imgui_impl_win32.h
curl -s -L -o imgui_impl_win32.cpp %IMGUI%/backends/imgui_impl_win32.cpp && echo external/imgui/backends/imgui_impl_win32.cpp
curl -s -L -o imgui_impl_dx11.h    %IMGUI%/backends/imgui_impl_dx11.h    && echo external/imgui/backends/imgui_impl_dx11.h
curl -s -L -o imgui_impl_dx11.cpp  %IMGUI%/backends/imgui_impl_dx11.cpp  && echo external/imgui/backends/imgui_impl_dx11.cpp

echo.
pause
endlocal