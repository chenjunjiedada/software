if [ "$1" == "" ]; then
  echo "Usage: sh .vim_runtime/install <system>"
  echo "       <system> can be 'mac', 'linux' or 'windows'"
fi
echo '
fun! MySys()
   return "$1"
endfun
set runtimepath=~/.vim_runtime,~/.vim_runtime/after,\$VIMRUNTIME
source ~/.vim_runtime/vimrc
helptags ~/.vim_runtime/doc' > ~/.vimrc
echo "Installed amix's vim configuration successfully! Enjoy :)"
