# 入力フォーム

## 题目描述

[problemUrl]: https://atcoder.jp/contests/njpc2017/tasks/njpc2017_a

英小文字のみからなる文字列 $ S $ と 表示する最大の長さ $ L $ が入力として与えられる。

$ S $ の文字数が $ L $ より大きい場合は初めの $ L $ 文字のみを出力せよ。そうでない場合には $ S $ をそのまま出力せよ。

## 说明/提示

### ストーリー

こんにちは。NJPCにご参加いただきありがとうございます。

NJPCの正式名称は「Nara institute of science and technology &amp; Japan advanced institute of science and technology Programming Contest」というのですが、いかんせん長すぎます。

そこであなたに、長過ぎる文字列は初めの $ L $ 文字のみを表示するプログラムの作成をお願いしたいのです。

### 制約

- $ 1≦L,|S|≦10^5 $
- $ L $ は整数である
- $ S $ は英小文字のみからなる

## 样例 #1

### 输入

```
10
hello```

### 输出

```
hello```

## 样例 #2

### 输入

```
37
narasenntannkagakugijyutudaigakuinndaigaku```

### 输出

```
narasenntannkagakugijyutudaigakuinnda```

# 题解

## 作者：HuangBo (赞：2)

没有看翻译，只看样例就秒懂的题;


做法:

给一个n

输入字符串s

if(字符串长度<=n)

输出字符串;

else 

for(int i=0;i<n;i++)//输出前n个字符;

cout<<s[i];


------------

~~对于新手来说可以练习一下下标的运用吧~~
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	string s;
	cin>>s;
	int l=s.size();
	if(l<=n)cout<<s;
	else
	for(int i=0;i<n;i++)cout<<s[i];
    return 0;
}
```

---

## 作者：Wy_x (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_njpc2017_a)

[更好的阅读体验？](https://www.luogu.com.cn/blog/73-54-16/solution-at-njpc2017-a)

### 做法：

- 可以**边输入边判断**。

- 程序在读入字符时，是一个一个读入的，依照这个性质可以读一个就判断一个，省去存储字符的麻烦。

- 每读入一个字符，$L$ 就减 $1$，当 $L$ 为 $0$ 时就可以跳出循环（注意跳出时机）。

- `cin` 读入失败返回值为 $0$。

- AT 的题最后要有换行（现在好像不加也行）。

### 无注释代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	char c;
	int l;
	cin>>l;
	while(cin>>c)
	{
		if(l<=0)  break;
		l--;
		cout<<c;
	}
	cout<<endl;
	return 0;
}
```

### 有注释代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	char c;
	int l;
	cin>>l;//要求长度 
	while(cin>>c)
	{
		//只有一行字符，可以用 cin 读 
		//cin 读入失败返回值为 0 
		//还可以过滤行末回车 
		//getchar() 不行，需要特判 
		if(l<=0)  break;
		//如果长度够了，就跳出 
		l--;//长度减一 
		cout<<c;//输出字符 
	}
	cout<<endl;//AT 的题最后要有换行
	return 0;
}
```

---

