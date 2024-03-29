# cpp-02-project-ja
## README
### セットアップと実行の手順
- ビルドコマンドは以下の通り
    ```
    cpp-02-project-ja/src$ g++ --std=c++17 *.cpp -o elevator
    ```
- 実行コマンドは「./elevator インプットファイルのパス」
  - 実行コマンドサンプル
    ```
    cpp-02-project-ja/src$ ./elevator C:\Users\cpp-02-project-ja\base_input.txt
    ```

### プロジェクトにおける重要な設計やその設計理由
- 始めに発展要件まで見据えて複数の乗客とエレベータに対応できるようにclass設計を検討した。（[図](https://docs.google.com/presentation/d/1bA3KirMn_il-RubIFEMaonWPbj1fI-meYPS08ZQUFsc/edit#slide=id.p)）始めに全体像を整理することで、その後の詳細設計にスムーズに進むことができた。
- 複数台エレベータがあるときに、どのエレベータをcallするのか判定する機能を追加。今回は一番近いエレベータを呼ぶようにした。何かしらの優先度を定義しないと、毎回同じエレベータが呼ばれることになるため。
- 重要オーバーで乗車拒否された場合の挙動を設計した。今回は、乗車拒否された場合、次の機会まで待機するような仕様とした。

### このツールまたはサービスの使い方の説明 (ユーザー向けの説明)
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

#### 要件に対するセルフチェック

| 要件                               | 確認結果 | 理由                                                    |
|------------------------------------|---------|--------------------------------------------------------------|
| base_input.txt を正常に実行する    | 〇    | base_input.txtを用いて実行し、期待する動作がなされることを確認した。 |
| さまざまな入力値で実行する         | 〇     | エレベータ３台、乗客３台でシミュレーションし適切に動作刷ることを確認した。(e3_p3.txt) |
| 最大積載荷重を超えた場合は乗車を拒否する | 〇  |base_over_load.txtを用いて実行し、期待する動作がなされることを確認した。 |
| 指定したフロアに到着したことがわかるようにする | 〇 | 毎時刻エレベータの位置と乗車中の乗員IDを表示しているため、到着したことがわかる。|
| 発展レベルの要件を満たす           | 〇     | 「複数の乗客に対応する」を対応した。e3_p3.txtで確認した。 |