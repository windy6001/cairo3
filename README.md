# example_cairo

GTK3 の cairo 周りのサンプルプログラムを公開しています。

## 説明

### Cairo3

起動すると、ウインドウを開いて、ランダムなカラーのピクセルを描画します。
ウインドウのサイズを変更すると、内容が変化します。

### Cairo4

Cairo3 と同じように、ランダムなカラーのピクセルを描画しますが、１秒ごとに内容が自動で書き換わります。

## ビルドの仕方

 - GTK 3をインストールしてください。 (home brew の場合: brew install gtk+3  )
 - make -f cairo3.mak 
 - make -f cairo4.mak 
