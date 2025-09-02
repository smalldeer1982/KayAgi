# [AGC003A] Wanna go back home

## 题目描述

高桥君将在一个平面上行走 $n$ 次。

他最开始从 $(0, 0)$ 出发，每次行走的方向已经确定，但是距离没有确定。

请确定每次走路的距离（至少为 $1$），使高桥君在这 $n$ 次行走后可以回到 $(0, 0)$。

## 样例 #1

### 输入

```
SENW```

### 输出

```
Yes```

## 样例 #2

### 输入

```
NSNNSNSN```

### 输出

```
Yes```

## 样例 #3

### 输入

```
NNEW```

### 输出

```
No```

## 样例 #4

### 输入

```
W```

### 输出

```
No```

# 题解

## 作者：Ender_NaCl (赞：2)

稍加观察一下样例就会发现，假如两个相反方向都同时出现或者同时不出现，那么就可以到达，否则不行

那么为什么呢？

简单分析一下：
举个例子 N 和 S 这两个相反的方向，假如 N 出现6次，而 S 出现3次。由于他的速度是可以随意取的，那么只要取往 S 的速度是往 N 的速度的2倍就可回到原点。

但如果只出现了 N 没有 S ，那么无论怎么走都回不到原点。

W 和 E 同理

那么实现就很简单了

下面是代码

```cpp
#include <iostream>

using namespace std;

int main()
{
	bool n = false,w = false,s = false,e = false; //分别统计四个方向有没有出现 
	char c;
	while(cin>>c)
	{
		if(c == 'N') n = true;
		else if(c == 'W') w = true;
		else if(c == 'S') s = true;
		else if(c == 'E') e = true;   //如果出现就标记为true 
	}
	if((n == s)&&(w == e)) cout<<"Yes";  //判断相反方向有没有都出现或都没有出现 
	else cout<<"No";
	return 0; //华丽结尾 
}
```


---

## 作者：Jiyuu_no_Tsubasa (赞：1)

对于这道题，我们可以有一个显而易见的思路：

因为每次行走距离至少为 $1$，

所以我们只需要判断每个方向有没有走过。

以 $S$ 方向与 $N$ 方向举例：
+ 若 $S$ 没走，$N$ 没走，则一定在 $(0,0)$ 点；
+ 若 $S$ 走了，$N$ 走了，则可以构建方程 $sum_s\times dis_s=sum_n\times dis_n$，得到可在 $(0,0)$的点；
+ 若 $S$ 走了，$N$ 没走，则方程变为 $sum_s\times dis_s \ne 0\times dis_n$，不成立；
+ 若 $S$ 没走，$N$ 走了，情况与上面类似，不成立。

这一段程序在加上对 $E$ 与 $W$ 的类似判断，就是正解了。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    string a; cin>>a;
    int n,s,e,w;
    n=s=e=w=0;
    for(int i=0;i<a.size();i++){
        n|=a[i]=='N';//判断每个方向是否走过
        s|=a[i]=='S';
        e|=a[i]=='E';
        w|=a[i]=='W';
    }
    cout<<(n==s&&e==w?"Yes":"No");
    return 0;
}

```

---

## 作者：wushuang0828 (赞：1)

翻译见讨论帖

**思路：只要先求出输入字符串中有没有出现过W、N、E、S，然后判断一下W.E出现性是否相同以及N.S出现性是否相同就行了**

详见代码：
```pascal
var
 s:ansistring;
 i,x,y,z,k:longint;
begin
 readln(s);
 for i:=1 to length(s) do
  begin
   if s[i]='W' then x:=1;//如果W出现过，x就等于1
   if s[i]='N' then z:=1;//如果N出现过，z就等于1
   if s[i]='E' then y:=1;//如果E出现过，y就等于1
   if s[i]='S' then k:=1;//如果S出现过，k就等于1
  end;
 if (x=1) and (y=1) and (z=1) and (k=1) then writeln('Yes') else
  if (x=1) and (y=1) and (z=0) and (k=0) then writeln('Yes') else
   if (x=0) and (y=0) and (z=1) and (k=1) then writeln('Yes') else
    if (x=0) and (y=0) and (z=0) and (k=0) then writeln('Yes') else
     writeln('No');//判断一下W.E出现性是否相同以及N.S出现性是否相同，相同输出Yes，不相同输出No
end.
```

---

## 作者：MattL (赞：0)

[洛谷题目链接](https://www.luogu.com.cn/problem/AT2001)

[原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/2001)


**题意：**

输入若干个字符，有 W,S,N,E 分别代表 西边，南边，北边，东边。距离随便（但不能为 0 ），请问是否可以走回原点。

---


**分析：**

这题是一题模拟。

可以无视输入了多少个字符，只需统计出现过哪种字符，视为这种字符加起来走过了 1 个单位距离，输出即可。

~~不懂的看代码。~~

---

**例子：**

样例 1 ：

SENW

向东南西北都走 1 米，当然会走到原点。

样例2：

NSNNSNSN

假设往南走的距离加起来为 1 米，往北走的距离加起来为 1  米，相互抵消，可以走到原点。

---

**核心：字符串。**

字符串，顾名思义，就是若干字符构成的串。

字符串有两种风格：

C 语言 风格字符串：
```cpp
char[100] s;
```

---
C++ 风格字符串：
```cpp
string s;
``` 
**注意：要包含 string 头文件**

---

上代码↓

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
bool q,w,e,r;
int main()
{
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='S')
			q=true;
		if(s[i]=='E')
			w=true;
		if(s[i]=='N')
			e=true;
		if(s[i]=='W')
			r=true;
	}
	if(q==e&&w==r)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：szkzyc (赞：0)

这道题的意思就是说输入一个字符串，出现 $N$ 为向北走，   $S$ 为向南走，$W$ 为往西走，$E$ 为往东走。最后让你判断是否能走到原点。

这个题目你一看肯定就会觉得很水，但这题一定比你想象的还要水沝淼。

空口无凭，接下来让我们分析一下这道题：

首先，题目中并没有说要走的步数，所以出现一堆跟出现一个是一样的。

其次，方向也只可能出现 $NSWE$，也就只有两组相反的方向：$(NS)(WE)$。

又因没有走的步数之分，所以要想回到原点，所以只要向南走后再向北走就相当于没有走。

最后一句话总结：只要 $N$ 跟 $S$ 同时出现或不出现，以及 $W$ 跟 $E$ 同时出现或不出现，都跟没走一样，所以只要 $N$ 是否出现 $=S$ 是否出现并且 $W$ 是否出现 $=E$ 是否出现就输出 `Yes`，否则就输出 `No`。

也就是：

```cpp
if(N == S && W == E) puts("Yes");
else puts("No")
```
接下来，就该上代码了。

我本来是觉得这题写个代码没有啥挑战性，所以我要：


## 压  行!（代码已AC）

```cpp
#include<bits/stdc++.h>
std::map <char, bool> m;char c;
int main(){
    while(std::cin >> c) m[c] = true;	return ((m['N'] == m['S'] && m['W'] == m['E']) ? puts("Yes") : puts("No")), 0;
}

```
这个代码这么短的原因是利用了 map 映射。

本人亲测 AC。

### ---end---



---

## 作者：No_Au_No_Name (赞：0)

### 直接模拟

直接读入串，然后枚举每一位，开变量计算每一种情况的个数。最后直接判断四面东西、南北相不相等。End 撒花！

```
#include<bits/stdc++.h>
using namespace std;
string a;
int w,e,n,s;
int main()
{
	cin>>a;
	for(int i=0;i<a.length();i++)
	{
		if(a[i]=='W') w=1;
		else if(a[i]=='E') e=1;
		else if(a[i]=='N') n=1;
		else if(a[i]=='S') s=1;
	}
	if(w==e and n==s) cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
```

---

## 作者：DeepSkyBlue__ (赞：0)

一串字符串，如果`W`和`E`出现次数相同且`N`和`S`出现次数也相同，那么输出`Yes`，否则输出`No`。

那么我们只要记录下每个字母是否出现过就珂以了。

CODE：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	int w=0,e=0,ss=0,n=0;
	cin>>s;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='W')w=1;
		else if(s[i]=='E')e=1;
		else if(s[i]=='S')ss=1;
		else if(s[i]=='N')n=1;
	}
	if(w==e&&n==ss)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
 } 
```


---

## 作者：F_S_R_M (赞：0)

##### 这个题呢还可以吧
### 重要的事情说在前面：一定要输换行符！！！，不然后果很严重
# 思路：
通俗一点来说：不管有多少向北的、向南的、向西的、向东的。

只要有一个与他方向相反的就都可以解决，

只要有一个与他方向相反的就都可以解决，

只要有一个与他方向相反的就都可以解决。

重要的事情说三遍（真的特别重要）

# 代码：
```cpp
#include<iostream>
#include<bits/stdc++.h> 
using namespace std;
int b;
int main()
{
	string a;
	cin>>a;
	int l=a.size();
	for(int i=0;i<l;i++)		//枚举每一个点 
	{
		if(a[i]=='S')			//如果有向南的 
		{
			b=0;				//清空 
			for(int i=0;i<l;i++)
			{
				if(a[i]=='N')	//只要有一个向北的就OK 
				{
					b=1;		//赋值为1 
					break;		//找到一个就退出 
				}
			}
			if(b==0)		//如果b==0，就是如果没找到N（北） 
			{
				cout<<"No"<<'\n';	//输出"No",注意换行，不然会全WA 
				return 0;				//直接退出 
			}
		}
		if(a[i]=='N')					//同上 
		{
			b=0;
			for(int i=0;i<l;i++)
			{
				if(a[i]=='S')
				{
					b=1;
					break;
				}
			}
			if(b==0)
			{
				cout<<"No"<<'\n';
				return 0;
			}
		}
		if(a[i]=='E')			//同上 
		{
			b=0;
			for(int i=0;i<l;i++)
			{
				if(a[i]=='W')
				{
					b=1;
					break;
				}
			}
			if(b==0)
			{
				cout<<"No"<<'\n';
				return 0;
			}
		}
		if(a[i]=='W')			//同上 
		{
			b=0;
			for(int i=0;i<l;i++)
			{
				if(a[i]=='E')
				{
					b=1;
					break;
				}
			}
			if(b==0)
			{
				cout<<"No"<<'\n';
				return 0;
			}
		}
	}
	cout<<"Yes"<<'\n';		//最后直接输出Yes就OK 
	return 0;
}
```
##### 有点小长，但是解释的很清楚，通俗易懂

---

