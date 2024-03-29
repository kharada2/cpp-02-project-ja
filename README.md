# cpp-02-project-ja
## README
#### セットアップと実行の手順
- ビルドコマンドは以下の通り
  - `g++ --std=c++17 *.cpp -o elevator`
- 実行コマンドは「./elevator インプットファイルのパス」
  - 実行コマンドサンプル`./elevator C:\Users\cpp-02-project-ja\base_input.txt`
#### プロジェクトにおける重要な設計やその設計理由
- [図](https://docs.google.com/presentation/d/1bA3KirMn_il-RubIFEMaonWPbj1fI-meYPS08ZQUFsc/edit#slide=id.p)を作成し要件を満たせる構成および各classの持つ関数や項目を検討
- 複数台エレベータがあるときに、どちらのエレベータをcallするのか判定するロジックを追加（例：近い方、とか）
- 重量オーバーで乗車拒否された乗客のIDを表示
- 乗車拒否された乗客は次の機会まで待機
- 乗客の折り返し乗車には対応していない（１Fから５Fまで乗ったとしてそのまま下車せず１Fに向かうことはできない）
#### このツールまたはサービスの使い方の説明 (ユーザー向けの説明)
- 入力ファイルに記載された情報をもとにエレベータ制御のシミュレーションを行うツールです
- 入力ファイルのフォーマットは以下の通り
  - １行目：エレベータの台数　フロア数　最大積載量
  - ２行目：乗客数
  - ３行目以降乗客数：乗客ID　乗客体重
  - ３行目＋乗客数以降：エレベータ呼び出し時間　エレベータを呼んだ乗客ID　乗客の現在フロア　行先希望フロア
- エレベータの現在位置は赤い表示になります
- 乗客がエレベータに乗車するとエレベータ内に乗客IDが表示されます
- Enterを押すとシミュレーション時間が進みます
- エレベータを待っている客がいる場合は待っているフロアの一番左に乗客IDを表示します

