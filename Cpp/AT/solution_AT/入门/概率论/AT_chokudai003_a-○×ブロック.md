# ○×ブロック

## 题目描述

[problemUrl]: https://atcoder.jp/contests/chokudai003/tasks/chokudai003_a

$ N $ × $ N $ の正方形のブロックが与えられます。 ブロックは、 `o`ブロック、 `x`ブロック、 `.`ブロックの $ 3 $ つが与えられています。

しばらくすると`.`ブロックが全て消滅し、上にあるブロックが落ちてくることを知っています。

あなたは、ブロックが消滅する前に、`.` ブロックを、以下の $ 2 $ 種類のブロックのどちらかに変換することが可能です。

- `+`ブロック：消滅しない普通のブロック
- `-`ブロック：消滅しないことに加え、自由落下もしないブロック

あなたは、書き換えた後に、`.`ブロック消滅後の、上下左右方向に連結する`o`ブロックの最大数と、同様に連結する`x`ブロックの最大数の和を できるだけ大きくしたいです。

ブロックを変更する前の状態が与えられるので、ブロックを変更した後の状態を出力してください。

## 说明/提示

### 制約

- $ N $ = $ 50 $
- $ S_i $ は $ N $ 文字の文字列であり、 $ j $ 番目の文字 $ S_{i,j} $ は、`o`,`x`,`.`の $ 3 $ 種類のどれかである。
- 入力は、各文字に対し、$ 50% $ の確率で `.`、残りの $ 25% $ の確率で`o`か`x`になるようにランダムで生成される。

### Sample Explanation 1

この入力は、説明のため、実際には存在しない小さい入力を使用しております。 全ての `.`ブロックが消滅したとき、以下のような状態になります。 図は、`o`ブロックを○、`x`ブロックを×、`+`ブロックを★、`-`ブロックを■で表現したものになります。 !\[例\](https://atcoder.jp/img/chokudai003/board.png)

## 样例 #1

### 输入

```
o.xx..ox..
..o.xx.o.x
.xxoo...o.
o..x.ox.x.
..o.o..ox.
..x..oo..x
.o.x.xxo..
x..xo.xxoo
.o..oox...
x.o.x.ox.x```

### 输出

```
o.xx..ox..
..o.xx.o.x
-xxoo...o.
o..x.ox.x.
..o.o+.ox.
..x..oo..x
.o.x.xxo..
x.+xo-xxoo
.o..oox+++
x.o.x.ox.x```

## 样例 #2

### 输入

```
.oo...x....xoo.xooooo.xx..xxo..xx.xoox.o..x..oo.o.
o..ox.xoxxox.xo..ooxx.ox.o.xooo.....x...ooxxo.o..x
x...x..oxxox.o..oxox.xoxo...oxo..oo....oxx.x...x.x
.xoo.........xo.xxx...x.o.xoox...o.o.x..ox.xx.oxo.
o.x...x.x.o.o...xo..oxxxo.xoo.xo.xo.ox.o...o...o..
xo.o.x..o.xx..o.....x..o.o....x.....ooo.oo.ooxx..o
.xx.o.xoo.x.xxx.x.o.xxoo.ox.o.oo.x.xxo..ox.x.o.o.o
.ox.o..xxo.ooxo.x.x.xx.xx.x...ooo.o..x....xo....ox
xx..ox.xx.x.x...ooxxox.oxx.o.oo.xo.o..x.x.xx..xxx.
o....o..x..xoxxx....o....x....x.o.o.x....ooo...o..
.xo.x...xox.............xo..xo....x..xoo.xx...x.ox
.oxxxxx.xx..o.oxoxx...x...x..x.oxxoxxo..oxx..xx...
.o..x.x.o...x..oo..o.x..xxox..o.oo.....x..x..o.oo.
ox.xo.xx.x..xo.oxooo..o.xxo.xox.o.x..xoo..o.x..oo.
.xoox...xoox...ooxx......o.oox....x.x.ox..o.ox.o.x
.o..x.xx..x....o..x.ox...oxooo....x..x.......o..x.
.o.xx..x..ox...o.o.xoo..oxx..oxo.oo..o.x.o.o....oo
x..xx.....x...o.xx.x..xo..x.oxx...xo.o...xx...xo.o
xx.oox.oxxo...ox...o.x..xo.oooxo..x..ox.ox...o...x
.oo...o.....o...xooxoxox.x.x...oo..xo.x.oo.x.xxxo.
oox..o.x.xo...oox.x..x..o.x.xxxo.x.x...o.o..o.....
xo.xx.o.x.xx.xo..oox..o..xoo...xo.o..ooo......oxox
.o..xx..xxo.....x...o.x..xxoxooxo..ooo.xx.....x..o
o..o.x..x.o.ox.oxx.o.xo.xox.o....o.o.x.ox...x.xox.
...o..oxoooo.x.o..oo....xo.xxxxxox..o.o.o....oo.o.
.xxo..x.x.oxoo.x.o....xxoxoo...ooxx.ox...ooo..x.x.
.xo..xxx.o..ox.oo....oox...xxo...oxx.o.ooo.o...oox
....ox.x.oo.o.x..x....o...o...x.oxx.oxo..o...oooo.
xxx..ox...x.x.x.o.x......xx..xx.ox.x......o.x..o.x
...oox.xox.ox.xx.x....x.oxxx..xxoxo.o.o....oxx...x
xoo.....ooxxxoxxxxx.....oxxx.....x..x...x..o.x..oo
..xo.oooxo...xx..x....x..oox.x.oxooo.oxoox...oxxo.
...ox.o.xo.oxxx....o..xooxox..x.xo...oo.xooo.x.xox
xx..o.oo...ox.x.x.ooxxxox...o..ox...ox....xx..xo..
xx.ooo..o.xoox.x.oox.o.xxxoooox.o..oo..x.x.xx....o
.oo...oxo.x.o.xx.o..xoxxox..x.xx.......xoxoxx.oxoo
...ox.ooooo.xxx.x..o.x.x.....xo..oo.xx..xo....ooox
.o.xx..o..xoxxo.xoo..xooo.xx.ox.xxxo.o.xo..o...x..
.xx...xoo.x.x.o.xo.o.xoxxo..oxo.ox....xoox.ox.xxxo
x.x..xox.....oxo..oo.ooxo...xo...ox.o..oo....ox.xo
.xx....xx.o....x.xoo.x.x.oxxooxxo..x..x..xxxxxo.ox
.o.x.x..x.oxoxx.xo..ox...ox.o......x.xxo...oo.oxx.
xx.xoxo.oo....ooxoxxxxxxxxoxxxx...oxx.o..oo.xo..xo
xx....o.o.xo.oox...o..o.x..o..x..x..xoxooxo.ox.oox
o.x..o.x..o.oo..ooo.x.......x.xx.o...oo..ox.x.xxx.
.xxoxoxxoo.o.o......xx..xxo.x....oox.x.xo.x..x....
oxx.oox....oxxx....x.oox..o.xx..xoxx.x.oo.o.o.x..x
....x.x.ox.xooxo.x..x.xo....oxoo..o.x.oo..o..x..x.
..o.o.xx....o...oooo...x.oox..oxox.x.x.x.xx...o.oo
..x.o.xo...xxx.x.ox.....oxo..ooxo..x.o.x..ooooxxox```

### 输出

```
.oo...x....xoo.xooooo.xx..xxo..xx.xoox.o..x..oo.o.
o..ox.xoxxox.xo..ooxx.ox.o.xooo.....x...ooxxo.o..x
x...x..oxxox.o..oxox.xoxo...oxo..oo....oxx.x...x.x
.xoo.........xo.xxx...x.o.xoox...o.o.x..ox.xx.oxo.
o.x...x.x.o.o...xo..oxxxo.xoo.xo.xo.ox.o...o...o..
xo.o.x..o.xx..o.....x..o.o....x.....ooo.oo.ooxx..o
.xx.o.xoo.x.xxx.x.o.xxoo.ox.o.oo.x.xxo..ox.x.o.o.o
.ox.o..xxo.ooxo.x.x.xx.xx.x...ooo.o..x....xo....ox
xx..ox.xx.x.x...ooxxox.oxx.o.oo.xo.o..x.x.xx..xxx.
o....o..x..xoxxx....o....x....x.o.o.x....ooo...o..
.xo.x...xox.............xo..xo....x..xoo.xx...x.ox
.oxxxxx.xx..o.oxoxx...x...x..x.oxxoxxo..oxx..xx...
.o..x.x.o...x..oo..o.x..xxox..o.oo.....x..x..o.oo.
ox.xo.xx.x..xo.oxooo..o.xxo.xox.o.x..xoo..o.x..oo.
.xoox...xoox...ooxx......o.oox....x.x.ox..o.ox.o.x
.o..x.xx..x....o..x.ox...oxooo....x..x.......o..x.
.o.xx..x..ox...o.o.xoo..oxx..oxo.oo..o.x.o.o....oo
x..xx.....x...o.xx.x..xo..x.oxx...xo.o...xx...xo.o
xx.oox.oxxo...ox...o.x..xo.oooxo..x..ox.ox...o...x
.oo...o.....o...xooxoxox.x.x...oo..xo.x.oo.x.xxxo.
oox..o.x.xo...oox.x..x..o.x.xxxo.x.x...o.o..o.....
xo.xx.o.x.xx.xo..oox..o..xoo...xo.o..ooo......oxox
.o..xx..xxo.....x...o.x..xxoxooxo..ooo.xx.....x..o
o..o.x..x.o.ox.oxx.o.xo.xox.o....o.o.x.ox...x.xox.
...o..oxoooo.x.o..oo....xo.xxxxxox..o.o.o....oo.o.
.xxo..x.x.oxoo.x.o....xxoxoo...ooxx.ox...ooo..x.x.
.xo..xxx.o..ox.oo....oox...xxo...oxx.o.ooo.o...oox
....ox.x.oo.o.x..x....o...o...x.oxx.oxo..o...oooo.
xxx..ox...x.x.x.o.x......xx..xx.ox.x......o.x..o.x
...oox.xox.ox.xx.x....x.oxxx..xxoxo.o.o....oxx...x
xoo.....ooxxxoxxxxx.....oxxx.....x..x...x..o.x..oo
..xo.oooxo...xx..x....x..oox.x.oxooo.oxoox...oxxo.
...ox.o.xo.oxxx....o..xooxox..x.xo...oo.xooo.x.xox
xx..o.oo...ox.x.x.ooxxxox...o..ox...ox....xx..xo..
xx.ooo..o.xoox.x.oox.o.xxxoooox.o..oo..x.x.xx....o
.oo...oxo.x.o.xx.o..xoxxox..x.xx.......xoxoxx.oxoo
...ox.ooooo.xxx.x..o.x.x.....xo..oo.xx..xo....ooox
.o.xx..o..xoxxo.xoo..xooo.xx.ox.xxxo.o.xo..o...x..
.xx...xoo.x.x.o.xo.o.xoxxo..oxo.ox....xoox.ox.xxxo
x.x..xox.....oxo..oo.ooxo...xo...ox.o..oo....ox.xo
.xx....xx.o....x.xoo.x.x.oxxooxxo..x..x..xxxxxo.ox
.o.x.x..x.oxoxx.xo..ox...ox.o......x.xxo...oo.oxx.
xx.xoxo.oo....ooxoxxxxxxxxoxxxx...oxx.o..oo.xo..xo
xx....o.o.xo.oox...o..o.x..o..x..x..xoxooxo.ox.oox
o.x..o.x..o.oo..ooo.x.......x.xx.o...oo..ox.x.xxx.
.xxoxoxxoo.o.o......xx..xxo.x....oox.x.xo.x..x....
oxx.oox....oxxx....x.oox..o.xx..xoxx.x.oo.o.o.x..x
....x.x.ox.xooxo.x..x.xo....oxoo..o.x.oo..o..x..x.
..o.o.xx....o...oooo...x.oox..oxox.x.x.x.xx...o.oo
..x.o.xo...xxx.x.ox.....oxo..ooxo..x.o.x..ooooxxox```

# 题解

## 作者：回青绝影 (赞：2)

**不能再短了！！！**

利用了scanf可以读入‘\n’的特性，所以只要读到文件末就是了！！！

超短！！！

```
#include<cstdio>
char s;int main(){while(~scanf("%c",&s))putchar(s);return 0;}
```

还没有一篇题解用到scnf诶……

---

## 作者：TRZ_2007 (赞：1)

$AtCoder$万岁！  
~~题目实在是太水了~~  
这题的翻译，讨论中已经讲过了，所以就不加阐述了，逃~~  
简单来讲，就是把一个字符矩阵读入，再输出就好了  
看看代码吧$qwq$  
```
#include <stdio.h>
int main()
{
	char str[101][101];//题意上说只要50*50就够了，但为了保险起见，就定义成101*101的
	int i=0,j;//i来统计字符串有几列，j就来代替for循环中i的功效
	while(scanf("%s",str[i])!=EOF)//不停地输入字符串，直到读到“Ctrl+z”为止
		i++;//不停地记录矩阵的列数
	for(j=0;j<i;j++)//循环输出
		puts(str[j]);
}//完美收场2333
```

---

## 作者：A_Plus_Gu (赞：0)

### 我的思路是：

1.读入第一个字符，这时可以算出n的大小；

2.读入第二到第n个字符；

3.输出！

### 上代码：

```
#include<iostream>
#include<string>
using namespace std;
string s[1000001];
int main(){
	cin>>s[1];//读入第一个字符，这时可以算出n的大小
	for(int i=2;i<=s[1].length();i++) cin>>s[i];//读入第二到第n个字符；
	for(int i=1;i<=s[1].length();i++)cout<<s[i]<<endl;//输出
	return 0;
} 
```


---

## 作者：yazzkl (赞：0)

# 翻译
cz有一个由o,x,.组成的矩形，保证N<=50.然后再输出原矩阵。

# 正文

这道题，您需要看看atcoder就可以了

看样例。

发现：只要输入什么，就可以输出什么（nice！）

找到规律！

实现就很简单了。一个for循环，原读入+原输出。

就是基础字符串操作，我用string

# code
```
#include <iostream>
#include <string> //用string，调用string库
using namespace std;
string S;  //string最保险
int main(){
  for(int i=0;i<50;i++){  //题意要求到50，枚举到50
    cin >> S;         //原封不动输入
    cout << S << endl;//原封不动输出
  }
}

```
这道题告诉我们，**看样例**很重要！！

但是普及-难度还是难以理解，我觉得入门难度就可以了

---

## 作者：人间凡人 (赞：0)

这道题最大的难点就是不知道n的值为多少

但是我们有很多种办法解决，我就来将其中的一种吧。

思路：可以先输入第一行的字符串，求出它的长度$len$，因为输出的为一个正方形，所以行数也应该为$len$，这样就轻而易举，迎刃可解了。

因为没有$pascal$代码 所以我就来写一篇吧！

$Code:$

```pascal
var
s:string;
len,i:longint;
begin
  readln(s);writeln(s);
  len:=length(s);
  for i:=1 to len-1 do
  begin
        readln(s);
        writeln(s);
  end;
end.
```


---

## 作者：Kcyzy (赞：0)

其实题目还是挺难的。。。   
只是数据太水了。。。 ~~无奈~~   
~~十分蒟蒻的我选择用这道题作为我的博客开通祭~~
```cpp
#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    char t=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>t;
            cout<<t;
        }
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：CZQ_King (赞：0)

## $C++$代码来一发
看来输入输出样例有问题

------------
思路：一行一行的读入，读完就输出$+$回车

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
string a;//一个字符串，待会拿来读入
int main(){
    while(getline(cin,a))//一行一行的循环读入
    	cout<<a<<endl;//读完就输出（别忘了回车）
    return 0;//结束
}
```

---

