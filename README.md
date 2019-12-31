# random_case generator
## ソースコード
- random_case.cpp ... ランダムケース生成をするプログラム
- main.cpp ... 提出予定のソースコード  
  ```shell
  $ make main
  ```
  から実行できる
- correct.cpp ... 愚直解のソースコード
- check.cpp ... main.cppとcheck.cppの実行結果を比べる
  ```shell
  $ make check
  ```
  から実行できる。  
  生成されたテストケースや出力は generated_cases/ 以下に保存される。  
  Makefileの RANDOM_DIR を変更することでディレクトリの変更可。
## Makefile
- RANDOM_DIR ... テストケースや出力を格納するディレクトリ
- CXXFLAGS ... check.cpp と random_case.cpp コンパイルオプション
- main ... main.cpp の実行
- check ... check.cpp の実行
- clean ... オブジェクトファイルや実行ファイルの削除
- clean_txt ... RANDOM_DIR 以下のテストケースなどの削除
- clean_all ... make clean と make clean_txt の実行