let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/develop/tile-sfml-game/src
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +0 Camera.cpp
badd +0 Camera.hpp
badd +0 GameEngine.cpp
badd +0 GameEngine.hpp
badd +0 GameObject.cpp
badd +0 GameObject.hpp
badd +0 GameState.hpp
badd +0 IntroState.cpp
badd +0 IntroState.hpp
badd +0 main.cpp
badd +0 MainMenuState.cpp
badd +0 MainMenuState.hpp
badd +0 MenuState.cpp
badd +0 MenuState.hpp
badd +0 Player.cpp
badd +0 Player.hpp
badd +0 PlayState.cpp
badd +0 PlayState.hpp
badd +0 RenderObject.cpp
badd +0 RenderObject.hpp
badd +0 TextureManager.cpp
badd +0 TextureManager.hpp
badd +0 Tile.cpp
badd +0 TileFloor.cpp
badd +0 TileFloor.hpp
badd +0 Tile.hpp
badd +0 TileMap.cpp
badd +0 TileMap.hpp
argglobal
silent! argdel *
argadd Camera.cpp
argadd Camera.hpp
argadd GameEngine.cpp
argadd GameEngine.hpp
argadd GameObject.cpp
argadd GameObject.hpp
argadd GameState.hpp
argadd IntroState.cpp
argadd IntroState.hpp
argadd main.cpp
argadd MainMenuState.cpp
argadd MainMenuState.hpp
argadd MenuState.cpp
argadd MenuState.hpp
argadd Player.cpp
argadd Player.hpp
argadd PlayState.cpp
argadd PlayState.hpp
argadd RenderObject.cpp
argadd RenderObject.hpp
argadd TextureManager.cpp
argadd TextureManager.hpp
argadd Tile.cpp
argadd TileFloor.cpp
argadd TileFloor.hpp
argadd Tile.hpp
argadd TileMap.cpp
argadd TileMap.hpp
edit Camera.cpp
set splitbelow splitright
wincmd t
set winheight=1 winwidth=1
argglobal
setlocal fdm=indent
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=91
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 1 - ((0 * winheight(0) + 42) / 85)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabnext 1
if exists('s:wipebuf') && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOIac
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
let g:this_session = v:this_session
let g:this_obsession = v:this_session
let g:this_obsession_status = 2
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
