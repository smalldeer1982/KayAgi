# Equidistant String

## 题目描述

Susie 喜欢字符串。她的字符串只包含数字 $0$ 和 $1$。今天，她使用了[汉明距离法](https://baike.baidu.com/item/%E6%B1%89%E6%98%8E%E8%B7%9D%E7%A6%BB/475174?fr=aladdin)计算了它们之间的距离。

汉明距离的定义表示两个相同长度字符串对应位置的不同字符的数量。

有2个长度为 $n$ 的字符串 $s$ 和 $t$ 她还想要一个长度为 $n$ 的字符串 $p$ 使得 $p$ 到 $s$ 的距离等于 $p$ 到 $t$ 的距离

请你帮她找到这样的字符串 $p$。可能有很多种答案，找到一种即可。

## 说明/提示

第一组样例：汉明距离为3

答案也可以为 $1001$

第二组样例：无法找到满足要求的字符串

translated by [Yang080108](https://www.luogu.com.cn/user/422348)

## 样例 #1

### 输入

```
0001
1011
```

### 输出

```
0011
```

## 样例 #2

### 输入

```
000
111
```

### 输出

```
impossible
```

# 题解

## 作者：Yang818 (赞：2)

## 题目

[传送门](https://www.luogu.com.cn/problem/CF545B)

此题目的翻译翻的很好~~因为是我翻的~~，题目大意就不多叙述了

## 样例分析

先来看第一组样例：

标准输入：
>0001

>1011

标准输出：
>0011

或

>1001

通过找规律，我们不难发现，两种答案的第 2 位和第 4 位没有变，只有第 1 位和第 3 位变了，样例输入中的 2 个字符串恰好也是第 2 位和第 4 位一样，只有第 1 位和第 3 位不一样，这是巧合吗？

## 题目解答

由汉明距离的定义可得：

如果字符串 $s$ 和 $t$ 在第 $i$ 位上一样，那么新字符串的第 $i$ 位不用改动就不用加距离

如果字符串 $s$ 和 $t$ 在第 $i$ 位不一样，那么新字符串的第 $i$ 位无论是 0 还是 1 都会和其中一个字符串的距离加上 1。

所以我们要在字符串 $s$ 和 $t$ 在第 $i$ 位不一样的时候才能控制距离。

当这是第 $k$ 次出现不一样时：

如果 $k$ 是奇数，那么新字符串的这一位保持和 $s$ 的这一位一样，该新字符串和 $t$ 的距离就会加 1。

如果 $k$ 是偶数，那么新字符串的这一位保持和 $t$ 的这一位一样，该新字符串和 $s$ 的距离就会加 1。

这样可以报证当 $k$ 是偶数的时候，新字符串到 $s$ 和 $t$ 的距离一样，最后输出该字符串就行了。

如果最后的时候 $k$ 是奇数，那么就输出 $impossible$。

## 代码

献上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int main(){
	int cnt=0;
	cin>>s>>t;
	for(int i=0;i<s.size();i++){
		if(s[i]==t[i])
			continue;
		cnt++;
		if(cnt%2!=0)
			s[i]=t[i];
	}
	if(cnt%2==0)
		cout<<s;
	else
		cout<<"impossible";
	return 0;
} 
```

既然看到这里了，就点个赞再走吧Orz






---

## 作者：Laisira (赞：1)

### 先扒一个汉明距离的定义
汉明距离是使用在数据传输差错控制编码里面的，汉明距离是一个概念，它表示两个（相同长度）字符串对应位置的不同字符的数量，我们以 $d(x,y)$ 表示两个字 $x,y$ 之间的汉明距离。对两个字符串进行异或运算，并统计结果为 $1$ 的个数，那么这个数就是汉明距离。

### 题面
给定 $01$ 字符串 $s$ 和 $t$，构造一个 $01$ 字符串 $p$ 使得 $s$ 到 $p$ 的汉明距离等于 $t$ 到 $p$ 的汉明距离。

### 思路
由定义可知，在 $s_i=t_i$ 时，不管 $p_i$ 如何，都不影响合法性，于是考虑不相同的地方。因为距离要相等，所以最简单的就是 $s$ 和 $t$ 一个一半，显然不相同的数为奇数时无法构造，特判一下就没了。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,ans=0;
    string s[2];
    cin>>s[0]>>s[1];
    n=s[0].size();
    for(int i=0;i<n;i++)
        ans+=(s[0][i]!=s[1][i]);
    if(ans&1)cout<<"impossible";
    else {
        int flag=0;
        for(int i=0;i<n;i++)
            if(s[0][i]==s[1][i])cout<<s[0][i];
            else cout<<s[flag][i],flag^=1;
    }
    return 0;
}
```

---

## 作者：__DayLight__ (赞：0)

## 前言
[翻译](https://www.luogu.com.cn/problem/CF545B)有误啊，样例 #1 的汉明距离是 $2$。

## 思路
通过理解题目，我们可以发现：

- 如果字符串 $s$ 与 $t$ 第 $i$ 位字符相同，那么 $p_i$ 并**不会影响** $p$ 到 $s$ 与 $t$ 的汉明距离的异同，要么两个距离都不增加，要么两个距离都增加 $1$。

- 反之，$p_i$ **会影响** $p$ 到 $s$ 与 $t$ 的汉明距离的异同，要么 $p$ 到 $s$ 的距离增加 $1$，要么 $p$ 到 $t$ 的距离增加 $1$。

综上所述，能推导出：

- 如果 $p$ 到 $s$ 与 $t$ 的汉明距离相同，那么该距离就是 $s$ 与 $t$ 对应位置的不同字符的数量的一半。

再往下推：

- 如果 $p$ 到 $s$ 与 $t$ 的汉明距离相同，那么 $s$ 与 $t$ 对应位置的不同字符的数量就必须为**偶数**，否则答案为 `impossible`。

以此就能写出代码了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int p;//记录 p 到 s 的汉明距离，用于输出。 
signed main(){
	cin>>s>>t;
	int hm=0,n=s.size();//hm 记录 s 与 t 的汉明距离。 
	s=" "+s,t=" "+t;
	for(int i=1; i<=n; i++)
		if(s[i]!=t[i])hm++;
	if(hm%2)cout<<"impossible";//如果不同的数量是奇数。 
	else
		for(int i=1; i<=n; i++)
			if(s[i]!=t[i])//对应位置的字符不同。 
			{
				if(p<hm/2)cout<<s[i],p++; 
				else cout<<t[i];
			}
			else cout<<s[i];//相同，不用操作，随便输出一个。 
	return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目大意
给出两个长度为 $n$ 的字符串 $a$，$b$，让你求出一个字符串 $c$，使得字符串 $c$ 与字符串 $a$，$b$ 不相同的位置的个数相同。

# 题目思路
先使字符串 $c$ 等于字符串 $a$，然后遍历一共有多少个 $a$，$b$ 不相同位置，在第奇数/偶数个位置使字符串 $c$ 等于字符串 $b$。最后判断两者不相同的位置有几个，奇数个输出 `impossible`，否则输出字符串 $c$。

# AC Code
```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f
#define lnf 0x3f3f3f3f3f3f3f3f

//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
//#pragma GCC optimize("Os")
//#pragma GCC optimize("Ofast")

using namespace std;

inline bool input (int& x) {
	x = 0;
	int f = 1;
	bool flag = 0;
	char c = getchar ();

	while (!isdigit(c)) {
		if (c == '-') {
			c = getchar ();

			if (isdigit (c)) {
				f = -1;
				break;
			}
		} else {
			c = getchar ();
		}
	}

	while (isdigit (c)) {
		flag = 1;
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar ();
	}

	x *= f;
	return flag;
}

inline bool output (int x) {
	if (x < 0) {
		putchar ('-');
		x = -x;
	}

	char write[25], cnt = 0;

	do {
		write[++ cnt] = x % 10;
		x /= 10;
	} while (x);

	do {
		putchar (write[cnt --] | 48);
	} while (cnt);

	return x;
}

void init ();

string a, b, c;
int n, ans;

signed main () {
	init ();
	cin >> a >> b;
	n = a.size ();
//	cout << n;
	
	for (int i = 0; i < n; ++ i) {
		c += a[i];//这里也可以是c += b[i]，只不过下面的 if 里面就变成 c[i] = a[i];
		
		if (a[i] != b[i]) {
			++ ans;
			
			if (ans % 2) {//这里也可以是 if (ans % 2 == 1)
				c[i] = b[i];
			}
		}
	}
	
	if (ans % 2) {
		puts ("impossible");
	} else {
		cout << c;
	}
	
	return 0;
}

void init () {
//	freopen (".in", "r", stdin);
//	freopen (".out", "w", stdout);
//	ios::sync_with_stdio (false);
//	cin.tie (0);
//	cout.tie (0);
}

```

---

## 作者：Last_kiss_Snow_Dog6 (赞：0)

### 汉明距离

汉明距离说的就是两个字符串之间不同字符的个数，所以这道题要先求所给两个字符串不同的数字个数。

### 判断可不可行

如果两个字符串之间的汉明距离为偶数，那么只需要第奇数个不同取第一个字符串里面的位置上的，第偶数个不同取第二个字符串里面位置上的即可。但如果两个字符串之间的汉明距离为奇数，无论怎么凑离两个字符串的汉明距离都会差一个。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string a,b;
	cin>>a>>b;
	int len,ans=0;
	len=a.size();
	char anser[len];
	for(int i=0;i<len;i++)
	{
		if(a[i]==b[i]) anser[i]=a[i];
		else
		{
			ans++;
		}
	}
	if(ans%2==0)
	{
		int x=1;
		for(int i=0;i<len;i++)
		{
			if(a[i]!=b[i]&&x%2==0) anser[i]=a[i],x++;
			else if(a[i]!=b[i]&&x%2==1) anser[i]=b[i],x++;
		}
	}
	else
	{
		cout<<"impossible";
		return 0;
	}
	for(int i=0;i<len;i++)
	{
		cout<<anser[i];
	}
}
//QAQ
```

---

## 作者：liuhaopeng666 (赞：0)

建议评橙

# 思路：

一眼 ```s.length```，发现暴搜肯定会超时，所以考虑另外一种方法。

1.首先，先求出两个字符串的汉明距离，记为 $cnt$。

2.其次，判断 $cnt$ 是否是奇数，如果是的话，不管怎么样这个字符串到原本两个字符串的汉明距离都会不一样，所以直接输出 impossible 即可。

3.如果 $cnt$ 为偶数，将其除以 $2$。然后我们就扫一遍，把不一样的地方改成一样的，一样的地方不变，直到两个字符串的汉明距离除以 $2$ 的值为 $0$ 为止，这样正好改完了一半，则这个字符串到原本的两个字符串的距离相同，都是一半的距离。（详见代码）

## Code：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    string s,t;
    cin>>s>>t;//输入两个字符串
    int cnt=0;
    for(int i=0;i<s.length();i++){
        if(s[i]!=t[i]){
            cnt++;//计算汉明距离
        }
    }
    if(cnt%2){//如果是奇数
        cout<<"impossible"<<endl;//直接输出impossible即可
    }
    else{//如果是偶数
        cnt/=2;//分半
        for(int i=0;i<s.size();i++){
            if(!cnt) break;//如果cnt减到0了，就直接输出就行了
            if(s[i]!=t[i]){//如果他们不一样
                t[i]=s[i];//替换成一样的
                cnt--;//自减
            }
        }
        cout<<t;//输出更改后的字符串
    }
    return 0;//完结撒花！！！
}  
```

---

## 作者：zjjc1104111 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF545B)

# 思路

本题需要构造一个字符串 ${p}$ 使得它和字符串 ${s}$ 和 ${t}$ 的距离相等。

由于数据太大，深搜一定会超时，因此，我们可以直接构造字符串。

但怎么构造呢？

我们可以让不同的字符平分。

因此，我们就可以判断，如果两个字符串不同的字符为偶数，那就把不同字符平分，否则只输出 ```impossible``` 就可以了。

# AC Code

```
#include<bits/stdc++.h>
using namespace std;
string s,t,ans;
int main(){
	int op=0;
	cin>>s>>t;
	for(int i=0;i<s.size();i++){
		if(s[i]==t[i]) ans+=t[i];
		else{
			if(op%2==0) ans+=s[i];
			else ans+=t[i];
			op++;
		}
	}
	if(op%2) cout<<"impossible\n";
	else cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：Terry2011 (赞：0)

# 题目分析

- 因为这道题需要使得 $p$ 到 $s$ 的距离等于 $p$ 到 $t$ 的距离。
- 所以，如果两个字符串相同位置的字符也相同，输出的字符串在这个位置也应当是这个字符。
- 如果一个位置的字符不同，我们需要在答案中平分。

这样就简单了！如果不同的数量是偶数，平分即可。否则输出 `impossible` 即可。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t,a;
int sum;
int main()
{
	cin>>s>>t;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==t[i])
		{
			sum++;
         if(sum%2==0) a+=s[i];
         else a+=t[i];
		}
		else a+=s[i];
	}
	if(sum%2) cout<<"impossible";
	else cout<<a;
	return 0;
}
```

---

## 作者：LegendaryGrandmaster (赞：0)

先求出两个字符串的汉明距离。

因为求出的字符串到这两个字符串的汉明距离相同，因此如果这两个字符串的汉明距离是**奇数**，不管怎么样这个字符串到原本两个字符串的汉明距离都会不一样，则输出 `impossible`。

否则把它除 $2$，重新扫一遍，把不一样的地方改成一样的，一样的地方不变，直到两个字符串的汉明距离除 $2$ 的值为 $0$ 为止。

这样正好改完了一半，则这个字符串到原本的两个字符串的距离相同，都是一半的距离。

最终输出这个字符串即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    string a,b;
    cin>>a>>b;
    int c=0;
    for(int i=0;i<a.size();i++)
    	if(a[i]!=b[i])c++;
    if(c%2){
    	cout<<"impossible";
    	return 0;
    }
    c/=2;
    for(int i=0;i<a.size()&&c;i++)
    	if(a[i]!=b[i])b[i]=a[i],c--;
    cout<<b;
}
```

---

## 作者：WA_sir (赞：0)

## [题目](https://codeforces.com/problemset/problem/545/B)|[链接](https://www.luogu.com.cn/problem/CF545B)

对于这道题，只能先找找规律了。

|1|2|3|4||
|-|-|-|-|-|
|0|0|0|1|$s$|
|1|0|1|1|$t$|
|0|0|1|1|$ans$|

可以看到，表中的第 $2$ 列和第 $4$ 列全是一样的字符。这就说明，当 $s_i$ 与 $t_i$ 相等时，$ans_i$ 取值为 $s_i$（也就是 $3$ 个字符均相等）。

但在表中的 $1$、$3$ 列，$s_i$ 均为 `0`，而 $t_i$ 均为 `1`。但在相同的情况下，$ans_i$ 的取值却发生了变化。这时回到题目，发现要使得 $s$ 到 $ans$ 与 $t$ 到 $ans$ 的[汉明距离](https://baike.baidu.com/item/%E6%B1%89%E6%98%8E%E8%B7%9D%E7%A6%BB/475174?fr=aladdin)相等。那么让其相等的办法，就是将每次“不等”平分给 $s$ 和 $t$。所以，每次出现 $s_i$ 与 $t_i$ 不等的情况时，可以在奇数次时使 $ans_i$ 与 $s_i$ 相等（也就是与 $t_i$ 不等），在偶数次时使 $ans_i$ 与 $t_i$ 相等。

相对应的，如果“不等”的次数为奇数，就无法将“不等”的次数平分给 $s$ 和 $t$。这时输出 `impossible`。只有次数为偶数，才输出结果 $ans$。

参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t,a;
int sum;
int main()
{
	cin>>s>>t;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]-t[i])
		{
			sum++;
			a+=sum%2?s[i]:t[i];
		}
		else a+=s[i];
	}
	if(sum%2)printf("impossible");
	else cout<<a;
	return 0;
}
```
感谢你读到这里！

---

## 作者：XL4453 (赞：0)

### 解题思路：

对于所有的相同位，无论怎么变换都无法改变新的字符串到 $a$ 和 $b$ 距离，需要考虑的只有不一样的位置。

可以发现，不一样的位置有奇数个的时候一定无解，否则一定有解。

对于后者，一种可行的构造方案是将其中奇数位的与 $b$ 相同，偶数位的与 $a$ 相同。


---
### 代码：

```cpp
#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
string a,b;
int cnt;
int main(){
	cin>>a>>b;
	for(int i=0;i<a.size();i++){
		if(a[i]!=b[i]){
			cnt++;
			if(cnt&1)a[i]=b[i];
		}
	}
	if(!(cnt&1))cout<<a<<endl;
	else printf("impossible\n");
	return 0;
}
```


---

## 作者：louliu (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF545B)

### 分析

首先，我们来看一看汉明距离的定义：

汉明距离是以理查德·卫斯里·汉明的名字命名的。在信息论中，两个等长字符串之间的汉明距离是两个字符串对应位置的不同字符的个数。换句话说，它就是将一个字符串变换成另外一个字符串所需要替换的字符个数。例如：

$1011101$ 与 $1001001$ 之间的汉明距离是 $2$。

$2143896$ 与 $2233796$ 之间的汉明距离是 $3$。

toned 与 roses 之间的汉明距离是 $3$。

那么我们就可以把这道题看做贪心题：

```cpp

0001

1011
  
```

1. 那么如果它两同位置上数字相同，那么我们就不用变（因为对汉明距离没有影响）。

1. 如果不同，那要让它相等，那是不是要平分可以“变化的数”（才能保证汉明距离相等）。

1. 最终结果无法平分，我们就输出 impossible，因为汉明距离一定不相等！

```cpp
000
  
111
```

就是因为无法平分而输出 impossible（有三个“变化的数”）。

## 极简代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b,c;
long long ans;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>a>>b;
	for(int i=0;i<a.size();i++){
		if(a[i]!=b[i]){
			ans++;
			if(ans%2==0){//平分策略
				a[i]=b[i];
			}
		}
	}
	if(ans%2==1) cout<<"impossible";//不满足
	else cout<<a;//满足输出
	return 0;
}

```

---

## 作者：Nuclear_Fish_cyq (赞：0)

我们知道汉明距离是对应位置的不同字符的数量，这是要遍历每个字符才能算出的。于是我们对每个 $i$，讨论 $s,t$ 的 $i$ 个字符 $s_i,t_i$。我们分类讨论：

当 $s_i=t_i$ 时,我们会发现答案的第 $i$ 位如果取 $s_i$ 的话对汉明距离不会有任何贡献，如果不取 $s_i$ 的话只会对两方的汉明距离都增加 $1$。换言之，在这种情况下答案的第 $i$ 位取啥都不会对汉明距离的差产生贡献。在这篇题解的代码里，这种情况下我们会选择 $s_i$，但是实际上都是可以的。

当 $s_i\ne t_i$ 时，就复杂了。如果我们选 $s_i$，那么会对答案和 $t$ 的汉明距离产生 $1$ 点贡献，不然会对答案和 $s$ 的汉明距离产生 $1$ 点贡献。我们单独把这种情况拿出来讨论。

设这种情况有 $k$ 次，那么问题就变成了有 $k$ 次选择，每次 $+1$ 或 $-1$,要使总和为 $0$。那么很显然，当 $k$ 为奇数时无解。然后我们 $+1,-1,+1,-1\cdots$ 的选就可以得到答案。

我们可以把两种情况整合到一起，边记录答案边统计 $k$。这取决于个人习惯。

上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
//#define mod
//#define range
using namespace std;
int n, k;
string a, b, ans; 
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> a >> b;
	n = a.size();
	for(int i = 0; i < n; i++){
		if(a[i] != b[i]){//在这位上有差异 
			if(k % 2){ 
				ans += b[i];
			}
			else{
				ans += a[i];
			}
			k++;
		}
		else{
			ans += a[i];
		} 
	}
	if(k % 2){//无解 
		cout << "impossible" << endl;
		return 0;
	}
	cout << ans << endl;
	return 0;
}

```

---

