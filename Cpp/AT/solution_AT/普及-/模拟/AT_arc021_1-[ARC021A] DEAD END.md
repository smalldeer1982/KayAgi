# [ARC021A] DEAD END

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc021/tasks/arc021_1

あなたは友人の高橋君からとあるゲームを熱烈にオススメされている。

このゲームは $ 4\ \times\ 4 $ のグリッド状に区切られた $ 16 $ 個のセルと、その上に置かれた数が書かれたタイルを使ってプレーする。$ 1 $ 回の操作では上下左右の $ 4 $ 方向のうちいずれかを指定することができ、指定した方向に向かってセル上のタイルが滑っていく。このとき、同じ数の書かれたタイル $ 2 $ 枚がぶつかるとその $ 2 $ 枚はグリッド上から取り除かれ、代わりに数を $ 2 $ 倍した別のタイルが $ 1 $ 枚新たに置かれる。

次の図は盤面の状態と、そこから右に向かって $ 1 $ 回操作を行った後の盤面の例である。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc021_1/bc1076be37559526a99cf6453c91f645c5d9b10f.png)

上下左右のどの方向を指定してもタイルがまったく滑ることができず、同じ数のタイルをぶつけることもできなくなったらゲームオーバーで、それまでに出来るだけ大きい数の書かれたタイルを作るのが目的だ。

このゲームは確かに非常に面白そうだと思ったが、まだ慣れていないからか、グリッド上がタイルでいっぱいになったときにゲームオーバーなのかをなかなか判別できない。そこで、グリッド上のタイルの情報が与えられたときにゲームオーバーの状態なのかどうかを判定するようなプログラムを書くことにした。

## 说明/提示

### Sample Explanation 1

上下にはタイルを動かすことができませんが、左右に動かせば $ 2 $ が書かれたタイルどうしや $ 8 $ が書かれたタイルどうしをぶつけることが可能です。

### Sample Explanation 2

どの方向に動かそうとしても同じ数の書かれたタイルをぶつけることができません。

## 样例 #1

### 输入

```
2 8 2 2
32 2 8 8
4 64 2 128
2 8 4 2```

### 输出

```
CONTINUE```

## 样例 #2

### 输入

```
2 4 16 4
8 32 128 8
2 64 16 2
32 4 32 4```

### 输出

```
GAMEOVER```

## 样例 #3

### 输入

```
2 4 2 4
4 2 4 2
2 4 2 4
4 2 4 2```

### 输出

```
GAMEOVER```

# 题解

## 作者：stry (赞：4)

### ~~这题是$\color{red}\text{入门}$题吧~~

解题思路；

1.定义一个二维数组（尽量定大一点）

2.读入（您玩过2048吗？玩过的话应该知道是一个4宫格）

3.边读入边判断这个数的附近有没有跟它相同的数，如果有的话就输出"CONTINUE"

4.如果全部输入完也没有找到，输出"GAMEOVER"

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110][110];
int main()
{
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
        {
            cin>>a[i][j];
            if(a[i-1][j]==a[i][j]||a[i+1][j]==a[i][j]||a[i][j-1]==a[i][j]||a[i][j+1]==a[i][j])
            {
                cout<<"CONTINUE"<<endl; 
                return 0;
            }
        }
    cout<<"GAMEOVER"<<endl;
    return 0;
}
```
评个论再走吧QAQ

---

## 作者：百里亦守约 (赞：3)

#      ~~本蒟蒻又来发题解了.. ~~

思路：
这一道题我就是不明白，为什么其他的题解都要判断上下左右或者都要输入完再判断。
所以我就有了一种更好的方法：边输入边做，因为输入时后面还没有记录到，所以就可以直接判断它的前面和上面是否相等，如果重复就直接输出就可以了。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105][105];
int main()
{
	for(int i=1;i<=4;i++)
	    for(int j=1;j<=4;j++)
	    {
	    	cin>>a[i][j]; //边输入边做
	    	if(a[i-1][j]==a[i][j] || a[i][j-1]==a[i][j]) //判断它的前面和后面是否相等
	    	{
	    		cout<<"CONTINUE"<<endl; //输出
	    		return 0;
	    	}
	    }
	cout<<"GAMEOVER"<<endl; //否则输出
	return 0;
}
```


---

## 作者：wuyutong111 (赞：2)


```
这道题得写明确思路，其实就是输入个4*4的方阵，寻找是否有两个数相邻并相等（相邻知道是左右相邻或上下相邻）。

接下来看看我的程序吧↓

```

```
var
 i,j:longint;
 p:boolean;
 a:array[0..5,0..5] of longint;//因为是4*4，所以可以定的小些
begin
 for i:=1 to 4 do
  for j:=1 to 4 do
   read(a[i,j]);//输入4*4方阵
 for i:=1 to 4 do
  begin
   for j:=1 to 4 do
    begin
     if a[i,j]=a[i,j+1] then p:=true;//判断是否有左右元素相等
     if a[i,j]=a[i-1,j] then p:=true;//判断是否有上下元素相等
    end;
   if p then break;
  end;
 if p then writeln('CONTINUE')
  else writeln('GAMEOVER');//输出相应指令
end.

```

---

## 作者：zoobidubi (赞：2)

很简单的一题二维数组的题目啦

闲话不多说

附上代码。。。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[11][11];
int main()
{
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
            cin>>a[i][j];//简单的读入不解释（printf也是可以的）
    for(int i=1;i<=4;i++)
    {
    	for(int j=1;j<=4;j++)
    	{
    		if(a[i][j+1]==a[i][j]||a[i][j-1]==a[i][j]||a[i-1][j]==a[i][j]||a[i+1][j]==a[i][j])//判断是否边上是否有能够消的
    		{
    		    cout<<"CONTINUE";//如果有一个的话就直接输出并结束程序
				return 0;	
			}    
		}
	}
    cout<<"GAMEOVER";//如果都没有能消的就游戏结束
	return 0;//好习惯。。。
}

```

---

## 作者：CZQ_King (赞：1)

超暴力的判断$+$打表

------------
做法：先把所有情况的表打出来，然后一个$if$完事。

------------

先把表打出来：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("1.txt","w",stdout);
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(j!=3){
				cout<<"a["<<i<<"]["<<j<<"]!=";
				cout<<"a["<<i<<"]["<<j+1<<"]";
				if(i!=3||j!=2)cout<<"&&";
			}
			if(i!=3){
				cout<<"a["<<i<<"]["<<j<<"]!=";
				cout<<"a["<<i+1<<"]["<<j<<"]&&";
			}
		}
	}
	return 0;
}
```
然后把表粘贴到这里：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4][4];
int main(){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			cin>>a[i][j];//逐个输入
	if(/*复制到这里*/)
	cout<<"GAMEOVER\n";//如果都不符合
	else cout<<"CONTINUE\n";//否则
    /*懒得打endl了*/
	return 0;
}
```

---

## 作者：RioBlu (赞：1)

因为题目说了不会出现空的地方，所以只要判断是否有两个一样的数存在相邻的情况

存在，输出"CONTINUE"，否则输出"GAMEOVER"
```
#include<string>
#include<iostream>
using namespace std;
long long block[7][7];
int main()
{
    for(int s=1;s<=4;s++)
    {
    	for(int v=1;v<=4;v++)
		{
			cin>>block[s][v];
		}
	}
	for(int s=1;s<=4;s++)
    {
    	for(int v=1;v<=4;v++)
		{
			if(block[s][v]==block[s][v-1]||block[s][v]==block[s][v+1]||block[s][v]==block[s+1][v]||block[s][v]==block[s-1][v])//是否相邻
			{
				cout<<"CONTINUE"<<endl;//相邻
				return 0;
			}
		}
	}
	cout<<"GAMEOVER"<<endl;
    return 0;
}
```

---

