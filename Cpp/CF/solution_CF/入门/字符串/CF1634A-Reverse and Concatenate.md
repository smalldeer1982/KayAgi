# Reverse and Concatenate

## 题目描述

Real stupidity beats artificial intelligence every time.

— Terry Pratchett, Hogfather, Discworld



You are given a string $ s $ of length $ n $ and a number $ k $ . Let's denote by $ rev(s) $ the reversed string $ s $ (i.e. $ rev(s) = s_n s_{n-1} ... s_1 $ ). You can apply one of the two kinds of operations to the string:

- replace the string $ s $ with $ s + rev(s) $
- replace the string $ s $ with $ rev(s) + s $

How many different strings can you get as a result of performing exactly $ k $ operations (possibly of different kinds) on the original string $ s $ ?

In this statement we denoted the concatenation of strings $ s $ and $ t $ as $ s + t $ . In other words, $ s + t = s_1 s_2 ... s_n t_1 t_2 ... t_m $ , where $ n $ and $ m $ are the lengths of strings $ s $ and $ t $ respectively.

## 说明/提示

In the first test case of the example:

After the first operation the string $ s $ can become either aabbaa or baaaab. After the second operation there are 2 possibilities for $ s $ : aabbaaaabbaa and baaaabbaaaab.

## 样例 #1

### 输入

```
4
3 2
aab
3 3
aab
7 1
abacaba
2 0
ab```

### 输出

```
2
2
1
1```

# 题解

## 作者：feicheng (赞：1)

## Description

给定长度为 $n$ 的字符串 $s$，你可以进行恰好 $k$ 次操作，每次操作可以令 $s$ 变为 $s+\text{rev}(s)$ 或是 $\text{rev}(s)+s$。求可以变成的字符串方案数。

多测。

**限制**：$1\le n \le 100$，$1\le t\le 100$，$1\le k\le 10^3$。

## Solution

注意到对一个回文串进行上述两种操作得到的结果是相同的。

而对一个字符串进行一次上述操作会得到一个回文串。

于是如果原字符串是一个回文串，那么只有一种可能的结果，反之有两种。

所以只需要判断一下原串是否是回文串即可。

时间复杂度：$\mathcal O(nt)$。




---

## 作者：newbie_QwQ (赞：1)

通过读题可以发现，进行了一次操作一或操作二之后的字符串一定是个回文串，而且回文串经过一次操作一或操作二之后的产生的字符串都是一样的，种类没有变多，也就不会再更新答案。

------------

如果输入的字符串是回文串，因为回文串**不会**再产生新种类，所以答案就是 $1$，如果输入的串不是回文串，因为进行一次操作会变成**两个回文串**，所以答案就是 $2$。不过还有一个小地方需要注意一下，就是当输入的 $k = 0$ 时，不能进行操作，**无论**是不是回文串**都**需要输出 $1$，需要**特判**一下。

------------

## AC 代码：
```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
long long n,i,j,k,t,flag; 
string s;
int main()
{
	cin>>t; 
	while(t--)
  	{
  		cin>>n>>k;
  		cin>>s;
  		if(k==0)//k=0 时的特殊判断。
  		{
  			cout<<1<<endl;
  			continue;
		}
  		flag=1;
  		for(i=0,j=s.size()-1;i<=j;i++,j--)//判断回文。
		{
			if(s[i]!=s[j]) 
			{
				flag=0;
				break;
			}
		}
		if(flag) cout<<1<<endl;//是回文串输出 1。
		else cout<<2<<endl;//不是回文串输出 2。
	}
	return 0;//再见！
}
```

---

## 作者：XiaoQuQu (赞：1)

很简单的一道题目。

若 $s$ 为回文串，则进行操作 (1),(2) 后会产生一个相同的回文串。因为都是相当于把 $s$ 重复了一遍。

若 $s$ 不为回文串，则进行 (1),(2) 操作后会分别产生两个不同的回文串。

所以若 $s$ 回文，则答案为 $1$，否则为 $2$。

注意，当 $k=0$ 的时候，根本无法操作，答案即为 $1$。

判断回文的方法（Hack 别人的时候看到的）：

### 1.普通方法。
挨个判断 $s_i$ 与 $s_{n-i+1}$ 是否相等。
### 2.构造方法
判断 $rev(s)$ 与 $s$ 是否相等，若相等即为回文。

代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
string s;
bool is_hw(){
    for(int i=1;i<=n/2;++i){
        if(s[i-1]!=s[n-i]){
            return false;
        }
    }
    return true;
}
int main(void){
    cin>>t;
    while(t--){
        cin>>n>>k;
        cin>>s;
        if(k==0){
            cout<<'1'<<endl;
            continue;
        }
        if(is_hw()){
            cout<<"1"<<endl;
        }
        else{
            cout<<"2"<<endl;
        }
    }
    return 0;
}
```

---

## 作者：yinhy09 (赞：0)

## 思路讲解：

本题其实主要难点就是对于回文串的判断。

如果原串不是回文串，那么 $rev(s)+s$ 和 $s+rev(s)$ 就是两个不同的串；然而如果原串 $s$ 本身回文，那么 $rev(s)+s$ 和 $s+rev(s)$ 就是两个一样的串，都为 $s+s$。

所以，当 $s$ 回文的时候，结果为 $1$，否则为 $0$。不过还有一个特殊情况，就是 $k=0$ 的时候，因为不能变换，所以无论 $s$ 是否回文，结果都为 $1$。

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
bool rev(string a,int n)//回文串判断
{
	for(int i=0;i<=(n+1)/2-1;i++)
	{
		if(a[i]!=a[n-i-1])return false;
	}
	return true;
}
int main(){
	int T;
	cin>>T;
	while(T--)
	{
		int n,k;
		string a;
		cin>>n>>k>>a;
		if(k==0)cout<<1<<endl;//k=0的特判
		else
		{
			if(rev(a,n)==1)cout<<1<<endl;//是回文
			else cout<<2<<endl;//非回文
		}
	}
	return 0;
}
```

谢谢观看~

---

## 作者：CmsMartin (赞：0)

[题目传送门](https://codeforces.com/contest/1634/problem/A)

## 分析

实际上就是裸的分类讨论，手工枚举几轮便可以发现：

当现在的字符串回文字符串时，那么进行；两种操作是相同的，会产生一种答案。

若其不为回文穿，进行操作后会变为两个回文字符串。

综上，当原字符串是回文字符串时答案为 $1$ , 不为回文字符串时答案为 $2$。

**最后，别忘了特判 $0$ 无法操作，答案为 $1$   !!!**

建议评橙。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int T;
int N , K;
string S;
 
 
int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        cin >> N >> K >> S;
        if(K == 0) {
            cout << 1 << endl;
            continue;
        }
        bool flag = false;
        for(int i = 0 , j = N - 1; i < N , j >= 0; i++ , j--) {
            if(S[i] != S[j]) flag = true;
        }
        if(flag == true) {
            cout << 2 << endl;
        }
        else {
            cout << 1 << endl;
        }
    }
    return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
给定一个长度为 $n$ 的字符串 $s$ 和一个整数 $k$。定义 $rev(s)$ 为将 $s$ 反转后得到的字符串。你可以执行恰好 $k$ 次操作，每次操作你可以将 $s$ 替换为 $s+rev(s)$ 或 $rev(s)+s$（其中 $+$ 为拼接操作），求在恰好 $k$ 次操作之后得到的字符串一共有多少种。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 100$，$1\leqslant n\leqslant 100$，$0\leqslant k\leqslant 1000$。**
## Solution
简单题，但由于垃圾 Pretest 赛时被 hack 了一大堆，下面先讲讲正解做法。

经过一番思考，我们不难发现如下性质：

- 回文串经过一次操作能够得到的字符串只有一种。
- $s$ 经过至多一次操作即可变为回文串。

当然，我们要先特判 $k=0$ 的情况，显然能够得到的字符串只有 $s$ 本身。然后我们分 $s$ 是否为回文串讨论。由上述性质不难发现，当 $s$ 本身是回文串时，经过恰好 $k$ 次操作能够得到的回文串只有 $1$ 种；当 $s$ 本身不是回文串时则有 $2$ 种。

再讲讲本题在赛时一大堆 Pretest Passed 的代码被 hack 的原因：他们无一例外都特判了 $k=1$ 的时候的答案只能是 $1$。显然可以通过下列数据把这种代码给 hack 掉：

```
1
3 1
aab
```

上述数据的答案是 $2$，因为不难看出通过恰好 $1$ 次操作可以得到 $\texttt{aabbaa}$ 和 $\texttt{baaaab}$ 这两种字符串，而被 hack 的代码输出 $1$。
## Code
```cpp
namespace Solution {
	iv Main() {
		MT {
			int n, k; string s;
			cin >> n >> k >> s;
			if(!k) println(1);
			else {
				string revs = s;
				reverse(revs.begin(), revs.end());
				println((revs != s) + 1);
			}
		}
		return;
	}
}
```

---

## 作者：Morpheuse (赞：0)

自己手玩一下不难发现对于任意一个字符串 $s$ 只有以下两种情况 $:$

1. 如果 $s$ 为回文串 ,  $s+rev(s)$ 和 $rev(s) + s$ 没有区别 此时答案为 $1$.

2. 如果 $s$ 不为回文串 在进行 $s+rev(s)$ 或 $rev(s) + s$ 后会变成一个回文串 回到情况 $1$.

所以如果初始字符串为回文串 输出 $1$ 即可.

否则 因为 $1 + 1 = 2$ 所以输出 $2$.

问题变成判断是否为回文串.

考场代码：

```cpp
 #include<bits/stdc++.h>
using namespace std;
int n,k;
int t;
string s;
 
int main()
{
	scanf("%d", &t);
	while(t --)
	{
		scanf("%d%d", &n,&k);
		cin>>s;
		if(k == 0)
		{
			printf("%d\n", 1);
			continue;
		}
		int flag = 0;
		for(int i = 0 ; i < n ; ++ i)
		{
			if(s[i] != s[n - i - 1])
			{
	//			cout<<s[i]<<"!="<<s[n - i - 1]<<endl;
				flag = 1;
				break;
			}
		}
		if(flag == 1)
		{
			printf("%d\n", 2);
		}
		else
		{
			printf("%d\n", 1);
		}
	}
}
/*
1
3 2
abb
*/
```


---

## 作者：Toorean (赞：0)

## 题意
- 定义 $\operatorname{rev}(str)$ 代表将 $str$ 内字符翻转（即倒序）。
- 对一个字符串 $str$ 进行 $k$ 操作，问最终字符串有多少种可能。

操作1：将 $str$ 替换为 $(str +\operatorname{rev}(str))$。

操作2：将 $str$ 替换为 $(\operatorname{rev}(str) +str)$。

## 思路
由题意不能发现：
- 当 $k=0$ 时，最终的字符串已经确定，只有一种可能。
- 当 $\operatorname{rev}(str)=str$ 时，$(\operatorname{rev}(str) +str) = (str +\operatorname{rev}(str))$，既也只有一种可能。

由此，我们就可以写出一个递归函数：$\operatorname{f}(str,k) = \operatorname{f}((str +\operatorname{rev}(str)),k-1) + )+\operatorname{f}((\operatorname{rev}(str) +str, k-1))$,当 $k=0$ 或 $\operatorname{rev}(str)=str$ 时，$\operatorname{f}(str,k) = 1$。

## AC Code
```cpp
#include <iostream>

using namespace std;

int t, n, k;
string tmp;

bool isWell (string str) {
    int i = 0, j = str.size () - 1;
    while (i < j) {
        if (str[i] != str[j]) {
            return false;
        }

        i ++, j --;
    }

    return true;
}

string rev (string str) {
    string ans = "";
    for (int i = str.size () - 1; i >= 0; i--) {
        ans += str[i];
    }

    return ans;
}

int getAns (string str, int k) {
    if (isWell (str) || !k) {
        return 1;
    }

    return getAns (str + rev (str), k - 1) + getAns (rev (str) + str, k - 1);
}

int main (void) {

    cin >> t;
    while (t--) {
        cin >> n >> k;
        cin >> tmp;
        
        cout << getAns (tmp, k) << endl;
    }

    return 0;
}

/*
113 k = 1
311113
113311

113 k = 2
113:
    113311:
        return 1
311:
    311113:
        return 1

*/
```

---

## 作者：miao5 (赞：0)

题意很简单就不说了。

这道题可以分成两种情况来讨论：给的字符串本身是回文串，或它不是回文串。

如果给定的字符串本身就是一个回文串，那么它旋转过后和原串还是一样的，把它接到原串的前面或者后面，会得到一个新的回文串。这样周而复始，最终只能得到一个一定的字符串。

如果给定的字符串不是一个回文串，那么旋转过后和原串是不一样的，接到前面和后面产生的串也是不一样的，这样第一次旋转和拼接会产生两个不同的字符串。可以轻易看出这次产生的两个字符串一定都是回文串，最后一定会产生两个不同的字符串。

之后就只需要判给定的字符串是否为回文串，如果是回文串输出 $1$，否则输出 $2$。

```
#include<iostream>
using namespace std;
char c[105];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		cin>>c+1;
		if(k==0){
			cout<<1<<endl;
			continue;
		}
		bool flag=0;
		for(int i=1;i<=n;i++){
			if(c[i]!=c[n-i+1]) flag=1;
		}
		if(flag==1) cout<<2<<endl;
		else cout<<1<<endl;
	}
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 题意

首先输入一个正整数 $t$ 表示数据组数。

然后 $t$ 组数据，第一行两个整数 $n$ 和 $k$，第二行一行长度为 $n$ 的字符串。

设 $\operatorname{rev}(s)$ 表示 $s$ 的反向字符串。有两种操作：

+ $s=s+\operatorname{rev}(s)$；

+ $s=\operatorname{rev}(s)+s$。

请问，现在要执行且仅执行 $k$ 次操作，有多少种结果？

### 2 思路

首先特判 $k=0$，有且仅有 $1$ 种结果。

然后，我们发现，对于一个回文字符串执行一次操作，有 $1$ 种结果；对于一个不回文的字符串执行一次操作，有 $2$ 种结果。并且，一个字符串被执行完操作后必定是个回文字符串。

所以，无论 $k$ 是多少，只要输入的字符串是回文的，答案就是 $1$；否则为 $2$。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
#define max_n 100000
int t;
int n;
int x;
long long y;
long long a[max_n+2];
bool u;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1634B_1.in","r",stdin);
	freopen("CF1634B_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%lld",&n,&x,&y);
		u=x&1;
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			if(a[i]&1)u^=1;
		}
		if(u==(y&1))printf("Alice\n");
		else printf("Bob\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/68887604)

By **dengziyue**

---

## 作者：zhicheng (赞：0)

### 分析

我们考虑每一次操作，分两种情况：

- 当原字符串 $s$ 为回文串，两个操作只能生成一个新的字符串。
- 当原字符串 $s$ 不为回文串，可以生成两个新的字符串，**并且生成的字符串都是回文串**。

因此，我们得到如下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[110];
int main(){
	int n,a,p,k;
	cin>>n;
	while(n--){
		p=1;
		cin>>a>>k>>s;
		if(k==0){  //特判一次操作都没有的情况
			cout<<1<<endl;
			continue;
		}
		for(int i=0;i<=a-1;i++){  //判断是否为回文串
			if(s[i]!=s[a-i-1]){
				p=0;
				break;
			}
		}
		if(p==1){  //如果本来就是回文串，只能生成一个串
			cout<<1<<endl;
		}
		else{  //否则只能在第一次操作时生成两个不一样的串
			cout<<2<<endl;
		}
	}
}
```

---

## 作者：IYSY2009I (赞：0)

赛时 6min A 掉。

作为一道 div2 的 A 题，它肯定不会很难。所以经过我们的细（cu）致（lue）观察，我们可以发现：

- 如果当前要翻转的字符串是回文串，那么它只能翻转出来一段回文字符串；
- 如果当前要翻转的字符串不是回文串，那么它只能翻转出来两段回文字符串。

综上所述，如果初始字符串为回文串，那么答案为 ```1```；如果初始字符串不是回文串，那么答案为 ```2```。

多看看样例是个好习惯，注意特判 $k=0$。

shou code time:

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
void cf(){
	int n=read(),k=read();
	char s[105];
	cin>>s;
	if(k==0){ //如果 k=0,显然你不能翻转当前字符串了，那么答案为1
		printf("1\n");
		return;
	}
	for(int i=0;i<=n/2;i++)
		if(s[i]!=s[n-i-1]){ //判断回文
			printf("2\n");
			return;
		}
	printf("1\n");
	return;
}
int main(){
	int t=read();
	for(int i=1;i<=t;i++)
		cf(); 
	return 0;
}
```


---

## 作者：Elgo87 (赞：0)

很容易可以发现，无论是操作一还是操作二，字符串经过操作后必定回文。

回文之后，无论怎么操作都不会产生新的种类。

故若原串不回文，则答案是 $2$，否则答案是 $1$。

特别地，若 $k=1$，则答案只能为 $1$。

参考程序：

```cpp
# include <bits/stdc++.h>
# define max(a,b) ((a)>(b) ? (a) : (b))
# define min(a,b) ((a)<(b) ? (a) : (b))
# define abs(a,b) ((a)> 0  ? (a) : -(a))
# define endl putchar('\n')
# define space putchar(' ');
# define begining {
# define ending }
# define int long long

using namespace std;

inline int read() {
	int num = 0; int nev = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') nev = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { num = (num<<1) + (num<<3) + (ch ^ 48); ch = getchar(); }
	return num * nev;
}

inline void print(const int& x) {
	if (x < 0) { putchar('-'); print(-x); return ; }
	if (x < 10) { putchar(x+'0'); return ;}
	print(x/10), putchar(x%10 + '0'); return ;
}

signed main()
{
	int T = read();
	while (T --)
	{
		int n = read(), k = read();
		if (!k) { print(1), endl; continue; }
		
		string s; cin >> s;
		int ans = 1;
		for (int i = 0; s[i]; i ++)
			if (s[i] != s[n - i - 1]) ans = 2;
		print(ans), endl;
	}
	return 0;
}
 
```

---

## 作者：N1K_J (赞：0)

## 思路
一道结论题

先举个例子：`abcba`，这是一个回文的序列，无论将 $rev(s) = abcba$ 放在他的前面还是后面，结果都是一样的，经过几次尝试·，可以猜测在序列 $s$ 回文时最后的结果唯一。



证明：

设 $s$ 为回文字符串，则 $rev(s) = s$。

故：$rev(s)+s = s+s$，$s+rev(s) = s+s$。

所以对回文字符串进行一次操作，结果唯一。

特别的，注意到结果为 $s+s$，同样回文，所以易得**当初始字符串 $s$ 回文时，结果为 $1$**。

再来讨论 $s$ 不回文的情况。

显然，经过一次操作后，结果为 $2$ 个**不同**回文字符串

所以当初始字符串 $s$ 回文时，结果为 $1$，当初始字符串 $s$ 不回文时，结果为 $2$。

**特别注意 $k$ 可能为 $0$**，所以要特判一下，$k=0$ 时结果字符串即初始字符串 $s$，答案为 $1$。

## Code
```cpp
#include<iostream>
using namespace std;
int t,n,k;
char str[1010];
bool huiwen(){
	for(int i = 1; i <= n/2+1; i++) if(str[i]!=str[n-i+1]) return false;
	return true;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		scanf("%s", str+1);
		if(k==0) printf("1\n");//不要忘记特判 
		else if(huiwen()) printf("1\n");
		else printf("2\n");
	}
	return 0;
}
```

---

## 作者：cyrxdzj (赞：0)

### 一、思路

首先，无论是哪两种操作，最终的结果均为回文。

然后，若 $s$ 为回文，则两种操作的结果一样。

然后，若 $s$ 不为回文，则两种操作的结果一定不一样。

因此，若开始时的字符串为回文或者 $k=0$，则答案为 $1$，因为两种操作结果一样，操作次数又是固定的。对于 $k=0$ 的情况，都无法操作，答案就只有 $1$。

若开始时的字符串不为回文并且 $k\ne0$，则答案为 $2$，因为第一次操作结果一定不同，但都是回文，因此之后的操作不会使可能性增加。

### 二、完整代码

```
#include<cstdio>
using namespace std;
int t;
int n,k;
char s[105];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%s",&n,&k,s+1);
		if(k==0)//无法操作，当然输出1
		{
			printf("1\n");
			continue;
		}
		bool flag=true;
		for(int i=1;i*2<=n;i++)//判断回文
		{
			if(s[i]!=s[n-i+1])
			{
				flag=false;
				break;
			}
		}
		printf(flag?"1\n":"2\n");
	}
	return 0;
}

```

By [dengzijun](https://www.luogu.com.cn/user/387836)

---

## 作者：bmatrix (赞：0)

简单分析容易发现，若 $s=rev(s)$，则无论 $rev(s)$ 放在前面还是后面，生成的新串都相同，只有一种情况。

相反，如果 $s\neq rev(s)$，则一次操作后可以出现两种情况。而无论是哪种情况，生成的新串都是回文串，即 $s'=rev(s')$，根据乘法原理，后面的情况数都是前一个情况数 $\times 1$，也就是说都不会再增添新的情况数。

因此有结论：如果 $s$ 回文，则最终情况数是 $1$，否则是 $2$。  
以及特判：$k=0$ 时，答案为 $1$，因为没有操作，只有一种情况。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=100005;
int n,a[N];double m;
int main(){
	int t;cin>>t;
    while(t--){
        int n,k;scanf("%d%d",&n,&k);
        char s[105];scanf("%s",s+1);
        bool flg=0;
        for(int i=1;i<=n/2;i++)if(s[i]!=s[n-i+1]){flg=1;break;}
        puts(flg&&k?"2":"1");
    }
	return 0;
}
```

---

## 作者：超级玛丽王子 (赞：0)

如题，这是一道诈骗题。

注意题目构造的形式，可以发现以下两点：

1. $s+\text{rev}(s)$ 必定是一个**回文串**；
2. 任何一个回文串 $\text{palin}$ 在操作后只有一种结果。

分别解释如下：

1. $s+\text{rev}(s)=s_1s_2\cdots s_ns_n\cdots s_2s_1$；
2. 由于对于回文串 $\text{palin}$，有 $\text{palin}+\text{rev}(\text{palin})=\text{rev}(\text{palin})+\text{palin}$，所以两种结果相同。

于是我们可以发现，对于任意字符串，经过一次操作以后必定变成回文串，此后的结果就不会再变化了。

于是我们可以判断一下这个字符串是否是回文串，并根据操作次数做出决策：
1. 如果是回文串，那么答案**必定**是 $1$；
2. 如果不是回文串，且操作次数为 $0$，那么答案是 $1$；
3. 如果不是回文串，且操作次数大于 $0$，那么答案是 $2$。

可以写出如下代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(void)  {
	int t;
	cin>>t;
	while(t--) {
		int n,k;
		cin>>n>>k;
		string str;
		cin>>str;
		bool ok=true;
		for(int i=0;i<=n-i-1;++i)
			if(str[i]!=str[n-i-1]) ok=false;
		if(ok) cout<<1<<endl;
		else if(k) cout<<2<<endl;
		else cout<<1<<endl;
	}
}
```

---

## 作者：FFTotoro (赞：0)

这一题就是判断回文。

显然答案最多为 $2$。考虑如果 $s$ 是回文串，那么就有 $rev(s)+s=s+rev(s)=s+s$，那么答案为 $1$；否则答案为 $2$。当然还有一种情况：$k=0$ 时答案一定为 $1$。

这一题可以使用 algorithm 库中的 `std::reverse` 函数。它可以将一个字符串倒置并赋值给该字符串，可以反转 $[st,ed)$ 范围内的元素。然后就可以使用该函数来判断给定字符串是否是回文串。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool pd(string s){
  string s1=s;
  reverse(s.begin(),s.end()); // 反转字符串
  return s1==s;
}
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t;
  while(t--){
    int n,k; string s; cin>>n>>k>>s;
    if(pd(s)||!k)cout<<"1\n";
    else cout<<"2\n";
  }
  return 0;
}
```

---

## 作者：ttq012 (赞：0)

**Sol**

这一个题我们可以举例子模拟一下。

对于样例 $1$，输入的字符串为 $\texttt{aab}$，我们要对他进行两次操作。

第一次操作，$rev(s)$ 是 $\texttt{baa}$，可以产生以下的两种结果：$\texttt{aabbaa}$ 和 $\texttt{baaaab}$。

第二次操作，我们定义当前的 $s'$ 是 $\texttt{aabbaa}$，$rev(s')$ 是 $\texttt{aabbaa}$，可以产生以下的两种结果：$\texttt{aabbaaaabbaa}$ 和 $\texttt{aabbaaaabbaa}$，我们可以发现这两种结果是一样的。

对于 $0$ 次操作的字符串，如样例 $4$，无论字符串 $s$ 是什么，都必然只有 $1$ 种结果。

通过上面的分析，我们可以看出，当字符串 $s$ 是回文字符串，或者操作数量 $m$ 为 $0$ 的时候，只会产生 $1$ 种字符串。否则，我们进行一次拼接操作之后，字符串会变成回文字符串，变成了情况 $1$。由于我们在进行拼接操作的时候产生了两种不同的字符串，所以有 $2$ 种结果。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

bool ishw(string &s, int l, int r) { // 回文字符串，递归方式
    if (l >= r) return true;
    if (s[l] != s[r]) return false;
    return ishw(s, l + 1, r - 1);
}

signed main() {
    int t;
    cin >> t;
    while (t --) {
        int n, m;
        scanf ("%d%d", &n, &m);
        string s;
        cin >> s;
        if (m == 0 || ishw(s, 0, n - 1)) puts("1");
        else puts("2");
    }
    return 0;
}
```


---

