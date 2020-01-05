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
## 備考
- random_case.cpp で用いる seed は check.cpp で指定しているので、同じ seed を使いまわさないように注意。