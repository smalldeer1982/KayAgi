# [USACO1.1] 你的飞碟在这儿 Your Ride Is Here

## 题目描述

众所周知，在每一个彗星后都有一只 UFO。这些 UFO 时常来收集地球上的忠诚支持者。不幸的是，他们的飞碟每次出行都只能带上一组支持者。因此，他们要用一种聪明的方案让这些小组提前知道谁会被彗星带走。他们为每个彗星起了一个名字，通过这些名字来决定这个小组是不是被带走的那个特定的小组（你认为是谁给这些彗星取的名字呢？）。关于如何搭配的细节会在下面告诉你；你的任务是写一个程序，通过小组名和彗星名来决定这个小组是否能被那颗彗星后面的 UFO 带走。


小组名和彗星名都以下列方式转换成一个数字：最终的数字就是名字中所有字母的积，其中 $\texttt A$ 是 $1$，$\texttt Z$ 是 $26$。例如，$\texttt{USACO}$ 小组就是 $21 \times 19 \times 1 \times 3 \times 15=17955$。如果小组的数字 $\bmod 47$ 等于彗星的数字 $\bmod 47$,你就得告诉这个小组需要准备好被带走！（记住“$a \bmod b$”是 $a$ 除以 $b$ 的余数，例如 $34 \bmod 10$ 等于 $4$）


写出一个程序，读入彗星名和小组名并算出用上面的方案能否将两个名字搭配起来，如果能搭配，就输出 `GO`，否则输出 `STAY`。小组名和彗星名均是没有空格或标点的一串大写字母（不超过 $6$ 个字母）。



## 说明/提示

题目翻译来自 NOCOW。

USACO Training Section 1.1


## 样例 #1

### 输入

```
COMETQ
HVNGAT```

### 输出

```
GO```

## 样例 #2

### 输入

```
ABSTAR
USACO```

### 输出

```
STAY```

# 题解

## 作者：Vanyun (赞：493)

（*有同学说我代码太长了，于是于2018.12.18简化了代码，麻烦管理员重审一下...*）

一道挺简单的题的呢...刚刚接触noip的时候难得我吃xiang，现在回头一看，真的感觉不一样了
#用string就好了，再注意一下ASCII的转换，就轻松ac啦

      #include <iostream>
      #include <cstring>
      using namespace std ;
      
      string a , b ;
      int ans = 1 , num = 1 ; //这里要注意起始值必须为1，要是0的话所有的数乘出来都是0了....

      main(){
          cin >> a >> b ; // 输入
          for( int i = 0 ; i < a.length() ; i ++ ) ans *= a[i] - '@' ; 
          // @的编号为64 ，A的编号65-@的编号64不就是所对应的英语字母序号了嘛...
          for( int i = 0 ; i < b.length() ; i ++ ) num *= b[i] - '@' ; 
          // 同上
          ans %= 47 , num %= 47 ; // 根据题意，mod 47
          if( ans == num ) cout << "GO" ; 
          else cout << "STAY" ; //输出
          return 0 ; //完美结束
      }
PS:如果不知道@的ASCII的值的话，可以直接减A的ASCII码然后再+1（其实是一个效果啦...）

---

## 作者：DrinkOnstage (赞：234)

扫了一下题解好像没有用回车结束输入的
个人认为比较简洁的写法
```cpp
#include <iostream>
int main()
{
	using namespace std;
	int a = 1 , b = 1;
	char v;
	while ( (v = cin.get() ) != '\n') a *= v - 'A' + 1;
	while ( (v = cin.get() ) != '\n') b *= v - 'A' + 1;
	if (a % 47 == b % 47) cout << "GO";
	else cout << "STAY";
	return 0;
}
```

---

## 作者：Carl__2015 (赞：4)

模拟题。  
## 分析
按题目意思，将两个彗星的名字转换成数字，再依次相乘，得到的结果通过取模进行判断。  
没什么多说的，上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int turn(char c)//将字母转换成数字
{
	return c - 'A' + 1;
}
int main()
{
	ios::sync_with_stdio(false);//优化，可不加
	cin.tie(0);
	cout.tie(0);
	string s,t;
	cin >> s >> t;
	int lens = s.size(),lent = t.size();
	int a = 1,b = 1;
	for(int i = 0;i < lens;i++)
	{
		a = a * turn(s[i]);//转换成数字并相乘
	}
	for(int i = 0;i < lent;i++)
	{
		b = b * turn(t[i]);//转换成数字并相乘
	}
	cout << ((a % 47) == (b % 47)? "GO":"STAY");//三目判断
	return 0;
}
```
完美的结束。

---

## 作者：return_third (赞：3)

# 思路

对于每一个字符 $c$，可以用 $c$ 减去 `A` 的 ASCII 值再加一得出它是第几个字母，最后相乘后取模判断相等即可。

# 代码实现

给出代码：

```cpp
#include<iostream>
using namespace std;
string a,b;
int main()
{
    cin>>a>>b;
    int lena=a.size(),lenb=b.size();
    int cnta=1,cntb=1;
    for(int i=0;i<lena;i++)
        cnta*=a[i]-'A'+1;
    for(int i=0;i<lenb;i++)
        cntb*=b[i]-'A'+1;
    if(cnta%47==cntb%47)
        cout<<"GO"<<endl;
    else
        cout<<"STAY"<<endl;
    return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/221826155)

---

