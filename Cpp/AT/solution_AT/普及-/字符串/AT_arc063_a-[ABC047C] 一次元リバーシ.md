# [ABC047C] 一次元リバーシ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc047/tasks/arc063_a

きつねの次郎と三郎が一次元リバーシで遊んでいます。一次元リバーシでは、盤面には白か黒の石が一列に並んだ状態となっており、列の右端か左端に新たに石を打っていきます。通常のリバーシと同じように、たとえば白の石を打つことで黒の石を挟むと、挟まれた黒の石は白い石に変わります。

ゲームの途中で三郎に急用ができて帰ってしまうことになりました。このとき、盤面の状態は文字列 $ S $ で表されます。石は $ |S| $ (文字列の長さ) 個並んでおり、左から $ i $ ($ 1\ ≦\ i\ ≦\ |S| $) 個目の石の色は、$ S $ の $ i $ 文字目が `B` のとき黒、`W` のとき白です。

次郎は現在の盤面に対して、できるだけ少ない個数の石を新たに打つことで全ての石を同じ色にしようと考えました。最小で何個の石を打てばよいかを求めてください。

## 说明/提示

### 制約

- $ 1\ ≦\ |S|\ ≦\ 10^5 $
- $ S $ に含まれる文字は `B` または `W` のいずれかである

### Sample Explanation 1

たとえば右端に黒い石を打つとすべての白い石を黒い石にすることができます。他にも、左端に白い石を打つことでもすべての石の色を同じにできます。 いずれの場合も $ 1 $ 個の石ですべての石を同じ色にすることができるので、$ 1 $ を出力します。

### Sample Explanation 2

最初から全ての石が同じ色の場合、新たに石を打つ必要はありません。

## 样例 #1

### 输入

```
BBBWW```

### 输出

```
1```

## 样例 #2

### 输入

```
WWWWWW```

### 输出

```
0```

## 样例 #3

### 输入

```
WBWBWBWBWB```

### 输出

```
9```

# 题解

## 作者：I_will (赞：1)

我来拉！又来写题解啦。

这道题是用'M'和'B'。
只需判断前一个和后一个相不相同，唯一不同的是，我是用一个字符存。

* 输入：用字符一个一个输入。
* 过程：用h记录次数，当z==1，h不++，且将当次输入的字符用另一个字符（x）存起来，当z!=1，且（&&）输入的字符不等于存字符（x），h++，存字符（x）赋值成输入的字符。
* 输出h。

程序来了----：
```cpp
#include<bits/stdc++.h>
using namespace std;
char x[100005],y;
int g,z;
int main()
{
	while(x[z]=getchar(),x[z]!='\n')
	{
		
		if(z==0)y=x[z];
		if(x[z]!=y)g++,y=x[z];
		
		z++;
	}
	
	cout<<g;
	
	return 0;
}
```


---

## 作者：moqizhu2005 (赞：1)

# ~~一道字符串水题~~
### 一个一个判断是否与前一个数相等即可
#### 可以用string来做（~~STL~~）
###### 代码如下
```cpp
#include<iostream>
#include<string>
using namespace std;
string a;
long long b;
int main()
{
	cin>>a;
	for(int i=1;i<a.length();i++)
		if(a[i-1]!=a[i]) b++;
	cout<<b;
	return 0;
}
```


---

## 作者：wushuang0828 (赞：1)

蛮水的一道题，直接for循环，但是从2开始到字符串的最后

特别注意：
### **length(s)是求s字符串的长度**

废话不多说，AC代码如下：
```pascal
var
 s:ansistring;
 i,ss:longint;
begin
 readln(s);
 for i:=2 to length(s) do
  if s[i]<>s[i-1] then inc(ss);//比较字符串当前这个字符和前一个字符是否相同，不相同就累加ss
 writeln(ss);//输出s字符串前后两个字符有多少个不相同
end.
```

---

## 作者：不到前10不改名 (赞：1)

```
#include<stdio.h>
#include<string.h>
char srx[100001];
int main()
{
    gets(srx);
    int i,zjq=0;
    for(i=1;i<strlen(srx);i++)//注意从1开始，不然就会多一个
    if(srx[i]!=srx[i-1])
    zjq++;//判断成功就加1（还是C语言的char好用~，可以当数组用）
    printf("%d\n",zjq);//回车注意++
    return 0;
}
```

---

## 作者：konglk (赞：0)

虽说题目中提到了字符串，但是这题并没有必要用。
只需要存下来两个字符，一比较就可以了。
一边阅读代码一边说思路吧。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	char c1,c2;//存相邻的两个字符，c2是输入的，c1是前一个输入的
	cin>>c1;//第一个没必要比较，直接视为前输入的
	int c=0;//这就是此题要去输出的
	while(~scanf("%c",&c2)&&c2!='\n')//只要没有读到换行符就一直读入
	{
		if(c1!=c2)c++;//如果不一样，答案+1
		c1=c2;//把新输入的视为前一个输入的存起来
	}
	cout<<c<<endl;//AT的题目一般都需要换行
	return 0;
}
```


---

## 作者：CZQ_King (赞：0)

看到大佬们都用的$if$，蒟蒻这里推荐一下$find$函数。

$find$函数：用于查找字符串里第一次出现目标字符串的位置。

用法：``s.find(v)``或``s.find(v,a)``。其中``s``是原字符串，``v``是目标字符串，``a``是起始位置。例如``s.find(v,5)``就是从``s``的第$5$个字符开始查找``v``。

如果没有找到目标字符串，函数返回$-1$。

------------
本题做法：

因为只包含$B$或$W$，要求的是前后字符不一样的个数，所以我们可以用$find$函数寻找$BW$或$WB$的个数，答案累加最后输出即可。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int a,i,ans;
int main(){
	cin>>s;
	while(s.find("BW",i)!=-1){//寻找BW的个数
		i=s.find("BW",i)+1;//记得要加一，不然会死循环
		ans++;//答案累加
	}
	i=0;//记得i要清零
	while(s.find("WB",i)!=-1){//寻找WB的个数
		i=s.find("WB",i)+1;
		ans++;
	}
	cout<<ans<<endl;
}
```

---

