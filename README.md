[![Actions Status](https://github.com/spihill/random_case/workflows/verify/badge.svg)](https://github.com/spihill/random_case/actions)  
# random_case generator
## ソースコード
- random_case.cpp ... ランダムケース生成をするプログラム。標準出力にテストケースを流す。
- main.cpp ... 提出予定のソースコード  
  ```shell
  $ make main
  ```
  から実行できる
- correct.cpp ... 愚直解のソースコード
- verify.cpp ... 出力が正しいかを検証するソースコード
- check.cpp ... main.cpp と correct.cpp の実行結果を比べたり、 main.cpp の出力を verify.cpp で検証する。
  ```shell
  $ make compare
  ```
  や
  ```shell
  $ make verify
  ```
  から実行できる。  
  生成されたテストケースや出力は generated_cases/ 以下に保存される。  
  Makefile の RANDOM_DIR を変更することでディレクトリの変更できる。  
## Makefile
- RANDOM_DIR ... テストケースや出力を格納するディレクトリ
- CXXFLAGS ... C++のコンパイルオプション
- main ... main.cpp の実行
- compare (co) ... check.cpp の実行 (愚直解 (correct.cpp) との比較)
- verify (ve) ... check.cpp の実行 (verify.cpp を用いた検証)
- clean (cl) ... オブジェクトファイルや実行ファイルの削除
- clean_txt (ct) ... RANDOM_DIR 以下のテストケースなどの削除
- clean_all (ca) ... make clean と make clean_txt の実行
## random_case.cpp
- argv[1] の値を乱数の seed に用いている。
- 乱数はすべて一様分布で生成している。
- グラフを生成するものは単純 (自己ループや多重辺無し) でDAG (頂点番号でトポロジカルソート可能) なグラフを生成する。  
  すべて 0-indexed で生成されるので要注意。
## 備考
- random_case.cpp で用いる seed は check.cpp で指定しているので、同じ seed を使いまわさないように注意。
- UNIX系のOSでGNU C++ (g++) じゃないと動かない。ヘッダファイルを適切に変えると動くかもしれない(未検証)が、make は必要。
- 例外処理が不十分。
- clone して
  ```shell
  make compare
  ```
  ```shell
  make verify
  ```
  で動作確認できる。
  ```shell
  Running case number : 118, WA: 4 RE: 6
  WA on case 0 2 3 6
  RE on case 1 4 5 7 8 9
  ```
  と表示されるならば正しい。  
  ただし、 distribution の実装依存らしいので、全く同じ結果にはならない可能性がある。 [参考](https://qiita.com/kusano_k/items/19b92af89f873f4bc1f7) 