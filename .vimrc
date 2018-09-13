"09-24-2016 create by ChuanqiDuan
"注：配置文件中，以单个双引号开头的文字为注释
"09-13-2018 update by ChuanqiDuan
"[add]自动注释文件信息 [modify]基本设置


"----------------------------------------------
" < 基本设置 >
"----------------------------------------------
"(自动)缩进使用4个空格
set shiftwidth=4

"设置软制表符宽度
set softtabstop=4

"设置制表符(tab键)宽度
"set tabstop=4

"行号显示
set nu

"设置自动对齐：即每行的缩进值与上一行相等;使用noautoindent取消设置
set autoindent
"使用C/C++语言的自动缩进方式
"set cindent

"设置backspace键可用
"set backspace=2

"语法高亮
if has("syntax")
syntax on
endif

"设置鼠标可用
"set mouse=a

"设置历史记录
"set history=

"光标从行首和行末时可以跳到另一行去
"set whichwrap=b,s,<,>,[,]

"整词换行
"set linebreak

"设置匹配模式,显示匹配的括号
"set showmatch

"set ignorecase " 搜索模式里忽略大小写
"set smartcase " 如果搜索模式包含大写字符，不使用 'ignorecase' 选项。只有在输入搜索模式并且>打开 'ignorecase' 选项时才会使用。

"检测文件类型
"filetype on
"filetype plugin on

set encoding=utf-8 fileencodings=ucs-bom,utf-8,cp936


"----------------------------------------------
" < 状态行设置 >
"----------------------------------------------
"标尺，用于显示光标位置的行号和列号，逗号分隔。每个窗口都有自己的标尺。如果窗口有状态行，标>尺在那里显示。否则，它显示在屏幕的最后一行上
"set ruler

"总显示最后一个窗口的状态行；设为1则窗口数多于一个的时候显示最后一个窗口的状态行；0不显示最>后一个窗口的状态行
"set laststatus=2

"显示光标位置
"set cuc
set cul



"----------------------------------------------
" < 命令行设置 >
"----------------------------------------------
"命令行显示输入的命令
"set showcmd

"命令行显示vim当前模式
"set showmode



"----------------------------------------------
" < 搜索设置 >
"----------------------------------------------
"高亮搜索
set hlsearch

"输入字符串就先是匹配点
"set incsearch


"----------------------------------------------
" < catgs setting >
"----------------------------------------------
" 按下F9重新生成tag文件，并更新taglist
map <F9> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR><CR> :TlistUpdate<CR>
imap <F9> <ESC>:!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<CR><CR> :TlistUpdate<CR>

"add current directory's generated tags file
set tags=tags
"表示在当前工作目录下搜索tags文件
"set tags+=/mnt/hgfs/cqd/linux_header/tags

 "add new tags file(刚刚生成tags的路径，在ctags -R 生成tags文件后，不要将tags移动到别的目录>，否则ctrl+］时，会提示找不到源码文件)
set tags+=./tagsset tags+=/mnt/hgfs/cqd/linux_header/tags tags+=/home/farsight/uboot2013/u-boot-2013.01/tags tags+=/home/farsight/linux-3.14/linux-3.14 tags+=/home/farsight/linux-3.14/linux-3.14

"tags表示在搜寻tags文件的时候，也要搜寻/mnt/hgfs/cqd/linux_header/文件夹下的tags文件。然后保存并退出vi。这样，你就可以用vim在任意地方查看有关Linux的函数原形
set tags+=/mnt/hgfs/cqd/linux_header/tags



"----------------------------------------------
" < taglist setting >
"----------------------------------------------
"F4映射taglist快捷键
nmap <F4> :Tlist<CR>

"因为我们放在环境变量里，所以可以直接执行
let Tlist_Ctags_Cmd='ctags'

"让窗口显示在右边，0的话就是显示在左边
let Tlist_Use_Right_Window=0

"让taglist可以同时展示多个文件的函数列表
let Tlist_Show_One_File=0

"非当前文件，函数列表折叠隐藏
let Tlist_File_Fold_Auto_Close=1

"当taglist是最后一个分割窗口时，自动退出vim
let Tlist_Exit_OnlyWindow=1

"是否一直处理tags.1:处理;0:不处理
let Tlist_Process_File_Always=1

"实时更新tags
let Tlist_Inc_Winwidth=0



"----------------------------------------------
" < cscope setting >
"----------------------------------------------
if has("cscope")
" 指定用来执行cscope的命令
set csprg=/usr/bin/cscope
" 设置cstag命令查找次序：0先找cscope数据库再找标签文件；1先找标签文件再找cscope数据库
set csto=0
" 同时搜索cscope数据库和标签文件
set cst
" 使用QuickFix窗口来显示cscope查找结果
set cscopequickfix=s-,c-,d-,i-,t-,e-
set nocsverb
" 若当前目录下存在cscope数据库，添加该数据库到vim
if filereadable("cscope.out")
cs add cscope.out
" 否则只要环境变量CSCOPE_DB不为空，则添加其指定的数据库到vim
elseif $CSCOPE_DB != ""
cs add $CSCOPE_DB
endif
set csverb
endif

map <F8> :cs add ./cscope.out .<CR><CR><CR> :cs reset<CR>
imap <F8> <ESC>:cs add ./cscope.out .<CR><CR><CR> :cs reset<CR>
" 将:cs find c等Cscope查找命令映射为<C-_>c等快捷键（按法是先按Ctrl+Shift+-, 然后很快再按下c>）
nmap <C-_>c :cs find c <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>
nmap <C-_>d :cs find d <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>
nmap <C-_>e :cs find e <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>
nmap <C-_>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-_>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-_>i :cs find i <C-R>=expand("<cfile>")<CR><CR> :copen<CR><CR>
nmap <C-_>s :cs find s <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>
nmap <C-_>t :cs find t <C-R>=expand("<cword>")<CR><CR> :copen<CR><CR>



" -----------------------------------------------------------------------------
"  < 自动补齐>
" -----------------------------------------------------------------------------
"inoremap ( ()<ESC>i
"inoremap [ []<ESC>i
"inoremap { {}<ESC>i<Enter><ESC><s-o>
"inoremap ' ''<ESC>i
"inoremap " ""<ESC>i
"inoremap < <><ESC>i
":inoremap ) <c-r>=ClosePair(')')<CR>
":inoremap } <c-r>=ClosePair('}')<CR>
":inoremap ] <c-r>=ClosePair(']')<CR>
":inoremap ' <c-r>=ClosePair(''')<CR>
"这一行是双引号的自动补齐
":inoremap " <c-r>=ClosePair('"')<CR>
"func! ClosePair(char)
"    if getline('.')[col('.') -1] == a:char
"        return "\<Right>"
"    else
"        return a:char
"    endif
"endf
"cnoremap <expr> %% getcmdtype() == ':' ? expand('%:h').'/' : '%%'



" -----------------------------------------------------------------------------
"  < WinManager setting >
" -----------------------------------------------------------------------------
" 设置我们要管理的插件
let g:winManagerWindowLayout='FileExplorer|TagList'
"let g:persistentBehaviour=0 " 如果所有编辑文件都关闭了，退出vim
nmap <F5> :WMToggle<cr>



" -----------------------------------------------------------------------------
"  < 自动添加注释文件信息 >
" -----------------------------------------------------------------------------
autocmd BufNewFile *.[ch],*.hpp,*.cpp exec ":call SetTitle()"

func SetTitle()
    call SetComment()
"    if expand("%:e") == 'hpp'
"    call append(line(".")+9, "#ifndef _".toupper(expand("%:t:r"))."_H")
"    call append(line(".")+10, "#define _".toupper(expand("%:t:r"))."_H")
"    call append(line(".")+11, "#ifdef __cplusplus")
"    call append(line(".")+12, "extern \"C\"")
"    call append(line(".")+13, "{")
"    call append(line(".")+14, "#endif")
"    call append(line(".")+15, "")
"    call append(line(".")+16, "#ifdef __cplusplus")
"    call append(line(".")+17, "}")
"    call append(line(".")+18, "#endif")
"    call append(line(".")+19, "#endif //".toupper(expand("%:t:r"))."_H")
"    elseif expand("%:e") == 'h'
"    call append(line(".")+9, "#ifndef _".toupper(expand("%:t:r"))."_H")
"    call append(line(".")+10, "#define _".toupper(expand("%:t:r"))."_H")
"    call append(line(".")+11," ")
"    call append(line(".")+12, "#endif")
"    call append(line(".")+13, "#endif //".toupper(expand("%:t:r"))."_H")
"    elseif &filetype == 'c'
"    call append(line(".")+9,"#include \"".expand("%:t:r").".h\"")
"    elseif &filetype == 'cpp'
"    call append(line(".")+9, "#include \"".expand("%:t:r").".h\"")
"    endif
endfunc

func SetComment()
    call setline(1,"/********************************************************")
    call append(line(".")+0, "*   Copyright (C) ".strftime("%Y")." All rights reserved.")
    call append(line(".")+1, "*   ")
    call append(line(".")+2, "*   Filename:".expand("%:t"))
    call append(line(".")+3, "*   Author  :Chuanqi.Duan")
    call append(line(".")+4, "*   Email   :chuanqiDuan@foxmail.com")
    call append(line(".")+5, "*   Date    :".strftime("%Y-%m-%d %H:%M"))
    call append(line(".")+6, "*   Describe:")
    call append(line(".")+7, "********************************************************/")
endfunc
