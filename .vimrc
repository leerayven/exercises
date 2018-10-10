set nocompatible
filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'Vundle/Vundle.vim'
Plugin 'scrooloose/nerdtree'
Plugin 'Valloric/YouCompleteMe'
"Plugin 'rdnetto/YCM-Generator'
"Plugin 'SirVer/ultisnips'

call vundle#end()
filetype plugin on


set cursorline
colorscheme desert
set number
syntax on
syntax enable
set autoindent
set ts=4
set sw=4
set expandtab
set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8
"set foldmethod=indent
set backspace=indent,eol,start
"set background=dark
"colorscheme solarized
"call plug#begin()
"Plug 'fatih/vim-go', { 'do': ':GoInstallBinaries' }
"call plug#end()
let g:ycm_server_python_interpreter='/usr/bin/python'
"let g:ycm_global_ycm_extra_conf='~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py'
let g:ycm_global_ycm_extra_conf='/home/mie/code/brpc/src/.ycm_extra_conf.py'
let g:ycm_key_invoke_completion='<C-A>'
let g:ycm_autoclose_preview_window_after_completion = 1
let g:ycm_semantic_triggers =  {
            \ 'c,cpp,python,java,go,erlang,perl': ['re!\w{2}'],
            \ 'cs,lua,javascript': ['re!\w{2}'],
            \ }
let mapleader=';'
nnoremap <leader>gl :YcmCompleter GoToDefinitionElseDeclaration<CR>

"autocmd vimenter * NERDTree
map <C-n> :NERDTreeToggle<CR>

