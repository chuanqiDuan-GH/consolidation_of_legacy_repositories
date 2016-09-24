"09-24-2016 create by chuanqiDuan
"注：配置文件中，以单个双引号开头的文字为注释

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
"set smartcase " 如果搜索模式包含大写字符，不使用 'ignorecase' 选项。只有在输入搜索模式并且打开 'ignorecase' 选项时才会使用。

"检测文件类型
"filetype on
"filetype plugin on



"-------------------状态行设置------------------
"标尺，用于显示光标位置的行号和列号，逗号分隔。每个窗口都有自己的标尺。如果窗口有状态行，标尺在那里显示。否则，它显示在屏幕的最后一行上
"set ruler

"总显示最后一个窗口的状态行；设为1则窗口数多于一个的时候显示最后一个窗口的状态行；0不显示最后一个窗口的状态行
"set laststatus=2



"-------------------命令行设置-----------------
"命令行显示输入的命令
"set showcmd

"命令行显示vim当前模式
"set showmode



"-------------------搜索设置-------------------
"高亮搜索
set hlsearch

"输入字符串就先是匹配点
"set incsearch

