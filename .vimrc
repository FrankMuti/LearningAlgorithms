syntax on

set guifont=Fira\ Code\ Retina\ 9

set tabstop=2
set shiftwidth=2
set expandtab
set autoindent
set smartindent
set cindent
set nu


autocmd filetype cc nnoremap <F5> :w <bar> !g++ main.cc -o main && ./main<CR>
autocmd filetype cc nnoremap <F6> :!source run a <CR>

command! -nargs=1 Rf !source run <q-args>

