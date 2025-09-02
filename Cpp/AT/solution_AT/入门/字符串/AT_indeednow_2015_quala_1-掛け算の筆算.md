# 掛け算の筆算

## 题目描述

[problemUrl]: https://atcoder.jp/contests/indeednow-quala/tasks/indeednow_2015_quala_1

あなたは算数を学んでいます。 あなたは $ 2 $ つの数の掛け算を行いたいと思っています。

あなたが学んでいる掛け算の筆算では、$ 2 $ つの数の掛け算を行うために、$ 1 $ 桁の数同士の掛け算をちょうど ($ A $ の桁数) $ × $ ($ B $の桁数) 回だけ行います。

あなたには正の整数 $ A $ と $ B $ が与えられます。この $ 2 $ つの数の掛け算を筆算で行うとき、$ 1 $ 桁の数同士の掛け算を何回行うか出力してください。

## 说明/提示

### Sample Explanation 1

$ 123 $ は $ 3 $ 桁の数、$ 12 $ は $ 2 $ 桁の数です。 したがって、答えは $ 6(=2×3) $ となります。

## 样例 #1

### 输入

```
123
12```

### 输出

```
6```

## 样例 #2

### 输入

```
10
1000```

### 输出

```
8```

## 样例 #3

### 输入

```
2
3```

### 输出

```
1```

## 样例 #4

### 输入

```
1000000
1000000```

### 输出

```
49```

# 题解

## 作者：CZQ_King (赞：1)

~~呵呵，感觉要过水而隐藏~~
## 老师：又是一道送分题！
#### 坚持没让自己用$string$
#### 用了$int$，~~居~~果然一次过
```cpp
#include<bits/stdc++.h> //头文件
using namespace std;
int a,b,c,d;//定义数字与长度
int main(){
    cin>>a>>b;//输入这两个数
    while(a>=10){
        a/=10;
        c++;
    }//获取a的长度
    while(b>=10){
        b/=10;
        d++;
    }//获取b的长度
    cout<<(c+1)*(d+1)<<endl;//因为while的问题，最后要加1个长度
    return 0;//AT必备
}
```

---

## 作者：InversionShadow (赞：0)

## AT_indeednow_2015_quala_1 掛け算の筆算 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_indeednow_2015_quala_1)

### 题目大意：

给定两个字符串，求它们各自的长度之积。

### 思路：

用 string 类的长度函数 .size() 即可。

### Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

string s, s1;

int main() {
  cin >> s >> s1;
  cout << s.size() * s1.size() << endl;  // s.size() 求的是 s 的长度，s1.size() 求的是 s1 的长度，它们之积直接乘起来就好了
  return 0;
}

```

## 大佬勿喷！ 



---

## 作者：durbin中将 (赞：0)

直接用string的length函数就解决了
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a,b;//定义这两个数
	cin>>a>>b;//输入这两个数
	cout<<a.length()*b.length()<<endl;//输出两个数长度的乘积
	return 0;//结束
}
```

---

## 作者：封禁用户 (赞：0)

其实这道题就是考大家的字符串应用
代码（勿喷）：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;//定义字符串
int len,len1,x;//用变量来记录字符串长度
int main()
{
 cin>>a>>b;//输入
 len=a.size();//教大家一个知识变量名.size();就是它的长度
 len1=b.size();
 x=len*len1;//把a和b的长度相乘
 cout<<x<<endl;//愉快输出
 
 return 0;
}

```
OVER  
(求通过)

---

## 作者：Hola_chen (赞：0)

# 非喜勿喷
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//本题思路：string输入，运用size函数计算长度，最后计算 
	string a;//string 
	string b;//string
	getline(cin,a);//string读入 getline函数 
	getline(cin,b);//string读入 getline函数 
	int x;//int 
	int n;//int
	//----------------------华丽的分割线---------------------------- 
	x=a.size();//size函数直接算长度
	n=b.size();//size函数直接算长度
	//----------------------华丽的分割线---------------------------- 
	cout<<x*n;//索性直接计算输出 
    return 0;
}

```

---

## 作者：xyn0901 (赞：0)

一道很水的题。。。

直接字符串测长就能过
```pascal
var s:string;
l:integer;
begin
readln(s);
l:=length(s);
readln(s);
writeln(l*length(s));
end.
```

---

## 作者：Xxzxx (赞：0)

这题巨简单，我给大家简单翻译一下：

给你两个数，输出他们的位数之积/两个数的位数相乘

2话不说，贴代码喽：：：：：：
c++
```cpp
#include<iostream>
using namespace std;
int main()
{
    string a,b;
    cin>>a>>b;
    cout<<a.length()*b.length()<<endl;
    return 0;
}
```
超简单的，祝AC

---

## 作者：da32s1da (赞：0)

读入用char，strlen()为长度。
```
#include<cstdio>
#include<cstring>
char a[10],b[10];
int main(){
    scanf("%s%s",a,b);
    printf("%d\n",strlen(a)*strlen(b));
}
```

---

