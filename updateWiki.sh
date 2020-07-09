#!/bin/bash
cp  ~/Downloads/wiki/tiddlywiki.html /Users/yonghao.hu/mycode/YongHaoWu.github.io/index.html ; 
cd /Users/yonghao.hu/mycode/YongHaoWu.github.io/; git add -u ; git cmm "new wiki" ; git pull  origin master -r && git push origin master
