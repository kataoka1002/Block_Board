# 自己紹介
>
> * ### 氏名　　[片岡海人](https://ja.wikipedia.org/wiki/%E5%90%89%E6%B2%A2%E4%BA%AE)
> * ### 所属　　~~東大医学部~~ 河原電子ビジネス専門学校

<br />

# ゲーム
>### **Block Board**
>![スクリーンショット_20230114_150001](https://user-images.githubusercontent.com/122655580/214465611-5f0677d7-fcde-4d7f-83c2-5cf3e4f91016.png)
>
> * ### プレイ人数　　　　　
>   - #### 2人　※コントローラー1個で遊ぶか2個で遊ぶか選べます。
> * ### ゲームジャンル　　　
>    - #### パズルゲーム
> * ### 制作環境 
>    - #### プログラム　　　　Visual Studio2022
>    - #### 3Ⅾモデル　　　　　3DS Max
>    - #### エフェクト　　　　Effeckseer
>    - #### バージョン管理　　GitHub
> * ### ゲーム内容
>    - #### プレイヤーが盾を置いたり壊したりしながら相手の敷地に侵入するパズルゲームです。
> * ### 操作方法　
>   - ### Xbox360コントローラー
> ![padsetumei](https://user-images.githubusercontent.com/122655580/214471063-f58db7d9-f54b-407c-a030-57077c8f302e.png)

<br />

# 内容
> ### ＜移動＞
>> #### マスからマスへ移動するときに自然に移動しているように見せるために目標地点から今の自分の座標を引いて、
>> #### ある数で割ったものを速さににすることで初速は速く、止まる前は遅くなるようにしました。
>> #### プレイヤーの状態を十数個のステートに分けることで、目的の操作しかできないようにしています。
> 
> <br />
> 
> ### ＜盾＞
>> * #### 配列を使うことで盾を複数作成しています。盾とキャラクターに自分の座標を覚えさせて、
>> #### 　　キャラクター座標と盾座標を比べることで移動できるかできないかを判断しています。
>> |盾のナンバー|X座標|Z座標|Y座標|
>> |------------|-|-|-|
>> |0|60|80|5|
>> |1|40|20|5|
>> |:|:|:|:|
>> |29|80|60|5|
>> 
>>  ※1人15枚の盾を置けるので、合わせて30個分の配列を準備しています。
>>  
>> <br />
>> 
>> * #### 盾は置いた直後のターンでは壊せないので、それを分かりやすくするために
>> #### 　　壊せる盾と壊せない盾でテクスチャを変更しています。
>> ![tatetigai](https://user-images.githubusercontent.com/122655580/214482039-b0394f16-390c-4bd8-a279-075af13cae15.png)
