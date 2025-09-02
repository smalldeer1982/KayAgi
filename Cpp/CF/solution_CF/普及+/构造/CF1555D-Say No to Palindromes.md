# Say No to Palindromes

## 题目描述

Let's call the string beautiful if it does not contain a substring of length at least $ 2 $ , which is a palindrome. Recall that a palindrome is a string that reads the same way from the first character to the last and from the last character to the first. For example, the strings a, bab, acca, bcabcbacb are palindromes, but the strings ab, abbbaa, cccb are not.

Let's define cost of a string as the minimum number of operations so that the string becomes beautiful, if in one operation it is allowed to change any character of the string to one of the first $ 3 $ letters of the Latin alphabet (in lowercase).

You are given a string $ s $ of length $ n $ , each character of the string is one of the first $ 3 $ letters of the Latin alphabet (in lowercase).

You have to answer $ m $ queries — calculate the cost of the substring of the string $ s $ from $ l_i $ -th to $ r_i $ -th position, inclusive.

## 说明/提示

Consider the queries of the example test.

- in the first query, the substring is baa, which can be changed to bac in one operation;
- in the second query, the substring is baacb, which can be changed to cbacb in two operations;
- in the third query, the substring is cb, which can be left unchanged;
- in the fourth query, the substring is aa, which can be changed to ba in one operation.

## 样例 #1

### 输入

```
5 4
baacb
1 3
1 5
4 5
2 3```

### 输出

```
1
2
0
1```

# 题解

## 作者：NXYorz (赞：13)

[题目链接](https://www.luogu.com.cn/problem/CF1555D)

-----------
### 题目大意

给定长度为 $n$ 的字符串 $s$ 以及 $m$ 次询问。
每次询问回答使区间 $[l,r]$ 的字符不回文需要修改多少次字符。

$s$ 中的每个字符都是前三个小写字母，每次修改后的字符也是前三个小写字母。

--------
### 分析

可以尝试模拟一下:  a 不回文，尝试添加一个字符，可以添加 b 或者 c， 这里选择添加 b， 于是字符串变成了 ab； 
再次尝试添加字符，发现只能添加 c，于是字符串变成了 abc; 
再次尝试添加字符，发现只能添加 a，于是字符串变成了 abca；再次尝试添加字符，发现只能添加 b,于是字符串变成了 abcab；再次尝试添加字符，发现只能添加 c,于是字符串变成了 abcabc。

发现不回文的字符串只能使一个以前三个字符组成的循环，而且前三种字符只有 $A_3^3$ 种排列方式。

对于每次询问，可以枚举这 $6$ 种排列方式，取最小值即可。

--------
### $\texttt{Code}$
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N = 2e5 + 10;

int n,m;
int sum[7][N];
string s;

void work(char x , char y , char z , int t)
{
    for(int i = 0; i < n; i++)
    {
        sum[t][i + 1] += sum[t][i];
        if(i % 3 == 0 && s[i] != x) sum[t][i + 1]++;
        if(i % 3 == 1 && s[i] != y) sum[t][i + 1]++;
        if(i % 3 == 2 && s[i] != z) sum[t][i + 1]++;
    }
}

int main()
{
  //  freopen("aa.in","r",stdin);
    scanf("%d%d",&n,&m);
    cin >> s;

    work('a' , 'b' , 'c' , 1);
    work('b' , 'a' , 'c' , 2);
    work('c' , 'a' , 'b' , 3);
    work('c' , 'b' , 'a' , 4);
    work('a' , 'c' , 'b' , 5);
    work('b' , 'c' , 'a' , 6);

    for(int i = 1; i <= m; i++)
    {
        int l , r; scanf("%d%d",&l,&r);
        int ans = 1e9 + 10;
        for(int j = 1; j <= 6; j++)
            ans = min(ans , sum[j][r] - sum[j][l - 1]);
        printf("%d\n",ans);
    }
}
```

---

## 作者：iMya_nlgau (赞：6)

我们先思考一下一个 beautiful 的串是什么样子的。

如果第一个字符是 $\texttt{a}$，第二个字符就不能是 $\texttt{a}$，否则就构成了回文串 $\texttt{aa}$，假设第二个字符是 $\texttt{b}$，那么第三个字符就不能是 $\texttt{a}$ 或 $\texttt{b}$，否则就会产生回文子串，所以第三个字符只能是 $\texttt{c}$。同理，第四个字符只能是 $\texttt{a}$，第五个字符只能是 $\texttt{b}$。最终的字符串就是 $\texttt{abcabcabc}\cdots$。

当然循环节可能是 $\texttt{abc}$ $6$ 种排列的任一种，枚举这 $6$ 种情况计算答案即可。

我们分别预处理出模 $3$ 等于 $0,1,2$ 的位置上的不为 $\texttt{a}$，不为 $\texttt{b}$，不为 $\texttt{c}$的位置的前缀和，就可以快速计算答案。具体可以参考我的代码。

复杂度大概就是 $O(9n+18m)$。

#### 代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
using namespace std;
inline int read(){
	int x=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+(c^'0'),c=getchar();
	return x;
}
const int maxn=2e5+10;
char str[maxn];
int n,m,a[maxn],s[3][3][maxn];
int c[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
int main(){
	n=read(),m=read();
	scanf("%s",str+1);
	for(int i=1;i<=n;i++) a[i]=str[i]-'a';
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			for(int k=i+1;k<=n;k+=3)
				s[i][j][k]=s[i][j][k+1]=s[i][j][k+2]=s[i][j][k-1]+(a[k]!=j);
	while(m--){
		int l=read(),r=read(),ans=0x3f3f3f3f;
		for(int i=0;i<6;i++){
			int res=0;
			for(int j=0;j<3;j++) res+=s[j][c[i][j]][r]-s[j][c[i][j]][l-1];
			ans=min(ans,res);
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：Sih_qwq (赞：1)

[洛谷题目链接](https://www.luogu.com.cn/problem/CF1555D) && [CF 题目链接](https://codeforces.com/problemset/problem/1555/D)。

## 题意

给你一个长度为 $n$ 的字符串，询问区间 $[l, r]$ 至少要改变多少个字符，使字符串不存在任何回文串（除单个字符外），其中字符串与改变的字符仅限于 $\texttt{a,b,c}$ 三个字符。

## 思路

首先我们要知道符合要求的串是什么样的。

假设我们的字符串有一个字符 $\texttt{a}$，那么下一个字符只能是 $\texttt{b}$ 或 $\texttt{c}$，因为如果还是 $\texttt{a}$ 的话会构成回文串 $\texttt{aa}$。

假设我们上一步构成的回文串为 $\texttt{ab}$（两种情况的讨论是一样的），那么下一个字符只能是 $\texttt{c}$，如果是 $\texttt{a}$ 会构成回文串 $\texttt{aba}$，是 $\texttt{b}$ 会包含回文串 $\texttt{bb}$。同理，下一个字符只能是 $\texttt{a}$，因为取其他两个字符会出现回文串。

发现规律了吗？只包含 $\texttt{a,b,c}$ 三个字符的不包含回文串的字符串，只能由 $\texttt{a,b,c}$ 三个字符以任意顺序重复，例如 $\texttt{abcabcabc...}$。

现在我们知道了符合要求的串是什么样的了。由于循环节只有六种情况，我们可以枚举六种情况预处理将原字符串改为符合要求的串所需要的操作数，由于要处理区间，所以将所有原串与枚举的串不符合的数做前缀和，询问时六种情况操作数取最小值即可。


[AC Code](https://codeforces.com/contest/1555/submission/275330228)。（登录 CF 后可以看。）

---

## 作者：BotDand (赞：1)

# $\text{Problems}$

定义一个字符串 $s$ 是 “好的”，当且仅当 $s$ 不包含任何长度大于等于 2 的回文子串。

给定一个长度为 $n$ 的字符串 $S$ 和 $m$ 个询问，每次询问给定一个区间 $[l, r]$，求字符串 $S_{l, \dots, r}$ 变成 “好的” 字符串至少需要修改多少个字符。本题中字符集为前三个字母（`a b c`）。

数据范围 $n, m \le 200000$。

# $\text{Answer}$

考虑构造“好的”字符串。

因为只有 `a,b,c` 三种字符，于是不难发现之后如下构造：

* `abcabc...`
* `acbacb...`
* `bacbac...`
* `bcabca...`
* `cabcab...`
* `cbacba...`

然后考虑这六种构造方案与原字符串相差的位数，用前缀和维护即可。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3fffffff;
int n,m;
int s[1000002];
char ch;
int mi;
int a[7][1000002],sum[7][1000002];
int l,r;
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
int main()
{
    // freopen("b.in","r",stdin);
    // freopen("b.out","w",stdout);
    n=read();m=read();
    for(int i=1;i<=n;++i)
    {
        ch=getchar();
        if(ch=='a') s[i]=1;
        if(ch=='b') s[i]=2;
        if(ch=='c') s[i]=3;
    }
    a[1][1]=1;a[1][2]=2;a[1][3]=3;
    a[2][1]=1;a[2][2]=3;a[2][3]=2;
    a[3][1]=2;a[3][2]=1;a[3][3]=3;
    a[4][1]=2;a[4][2]=3;a[4][3]=1;
    a[5][1]=3;a[5][2]=1;a[5][3]=2;
    a[6][1]=3;a[6][2]=2;a[6][3]=1;
    for(int i=1;i<=6;++i)
        for(int j=4;j<=n;++j)
            a[i][j]=a[i][j-3];
    for(int i=1;i<=6;++i)
        for(int j=1;j<=n;++j)
            if(s[j]==a[i][j]) sum[i][j]=sum[i][j-1];
                else sum[i][j]=sum[i][j-1]+1;
    while(m--)
    {
        l=read();r=read();
        mi=inf;
        for(int i=1;i<=6;++i) mi=min(mi,sum[i][r]-sum[i][l-1]);
        print(mi);
    }
    return 0;
}
```


---

## 作者：water_tomato (赞：1)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1555d-say-no-to-palindromes-%e9%a2%98%e8%a7%a3/)。

[题目链接](https://www.luogu.com.cn/problem/CF1555D)。

## 解析

考虑最终序列。由于序列较长，先考虑序列短小的情况，即长度为 $3$ 时。

对于一个长度为 $3$ 的序列 $S_{1,2,3}$，要使其不存在回文串，需要满足 $S_1\neq S_2,S_2\neq S_3,S_1\neq S_3$，你发现这三个字母必须是互不相同的，由于字符串仅由三种字母组成，最终序列的前三个字母一定是以下六种情况的一种并由其中一种情况循环得到：`abc`,`acb`,`bac`,`bca`,`cab`,`cba`。

问题转化为了给定一个区间，将这个区间改变为以上六种循环中的一种的最小操作次数。而对于某种循环的操作次数即为当前序列与最终序列不同的字符个数，这可以使用前缀和来维护。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m;
char a[N],s[7][3]={{'a','b','c'},{'a','c','b'},{'b','a','c'},{'b','c','a'},{'c','a','b'},{'c','b','a'}};
int sum[N][7];
int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",a+1);
	for(int k=0;k<=6;k++){
		int now=0;
		for(int i=1;i<=n;i++,now++){
			if(now==3) now=0;
			if(a[i]!=s[k][now]) sum[i][k]++;
			sum[i][k]+=sum[i-1][k];
		}//六种情况的前缀和
	}
	for(int i=1,l,r;i<=m;i++){
		scanf("%d%d",&l,&r);
		int ans=1e9;
		for(int k=0;k<=6;k++){
			ans=min(ans,sum[r][k]-sum[l-1][k]);
		}//选取代价最小的那一个
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：longStone (赞：0)

# CF-1555D 题解

## 观察

因为修改后的字符串要求任何一个子串都不回文，所以要求任意三个连续的字符互相都不同。

若两个相邻的字符相同，一定回文，比如：`aa`。若两个相邻的字符不同，但三个字符中有相同，说明第 $1,3$ 个字符相同，也是回文的，比如：`aba`。其他情况下不可能出现回文。

## 思考

因为只有 $3$ 个字符，再不回文的情况下，字符串只能是像 `abcabcabc` 一样不断的重复一种排列，$3$ 个字符共有 $6$ 种排列：`abc`，`acb`，`bac`，`bca`，`cab`，`cba`。

提前计算每一种排列需要更改的字符数，对于每一次询问，选择最佳排列即可。

## 代码

```c++
#include "bits/stdc++.h"
using namespace std;
int n, m, l, r, ans[7][200005];
char c, d[7][5] = {{""},{"abc"},{"acb"},{"bac"},{"bca"},{"cab"},{"cba"}};

int main()
{
    cin >> n >> m;
    for(int i = 1;i <= n;i++)
    {
        cin >> c;
        for(int j = 1;j <= 6;j++)
        {
            ans[j][i] = ans[j][i - 1];
            if(c != d[j][(i - 1) % 3])	ans[j][i]++;
        }
    }
    while(m--)
    {
        cin >> l >> r;
        int tmp = 0x3f3f3f3f;
        for(int i = 1;i <= 6;i++)	tmp = min(tmp,ans[i][r] - ans[i][l - 1]);
        cout << tmp << '\n';
    }
    return 0;
}
```

---

## 作者：xujingyu (赞：0)

## 题意

求字符串 $s_{l,\dots,r}$ 变成没有任何长度大于等于 $2$ 的回文子串的最小替换字符次数。

**注意：** 字符串 $s$ 下标是从 $0$ 开始的，但是输入的 $l$ 和 $r$ 却是从 $1$ 开始的，代码中应注意。为方便后文都将 $s$ 下标改为 $1$ 开始。

## 解法

* 当 $|s|=2$ 时，它只需要两个字符不相等即可；
* 当 $|s|=3$ 时，首先连续的两个字符不能相等，即 $s_1\ne s_2$ 且 $s_2\ne s_3$，并且，如果 $s_1=s_3$，它依然是回文的，所以 $s_1\ne s_2\ne s_3$。
* 当 $|s|\ge4$ 时，同上情况首尾不能相等，相邻的不能相等，相隔 $1$ 个字符的不能相等，那么就只能是前三个字符放在前三位，然后后面循环前三位的字符。

综上，能满足条件的只有 `abc` 或 `acb` 或 `bac` 等六个三个字符的全排列之一的循环。

那么暴力就很好想了，暴力对比字符串与每种排列，取最小值。


```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,l,r;
string ss,s;
char a1[4] = {'.','a','b','c'};
char a2[4] = {'.','a','c','b'};
char a3[4] = {'.','b','a','c'};
char a4[4] = {'.','b','c','a'};
char a5[4] = {'.','c','a','b'};
char a6[4] = {'.','c','b','a'};

int c(char t[])
{
	int cnt = 0;
	for(int i = 1,j = 1;i < s.size();i++,j++)
	{
		if(j > 3) j -= 3;
		if(s[i] != t[j]) cnt++;
	}
	return cnt;
}

signed main()
{
	scanf("%d%d",&n,&m);
	cin >> ss;
	ss = " " + ss;
	while(m--)
	{
		scanf("%d%d",&l,&r);
		s = "";
		for(int i = l;i <= r;i++) s += ss[i];
		s = " " + s;
		printf("%d\n",min(c(a1),min(c(a2),min(c(a3),min(c(a4),min(c(a5),c(a6)))))));
	}
	return 0;
}
/*
abc 0
abb 1
cca 1
aaa 3
*/
```

发现在第五个点超时。

发现重复计算很耗时间，即使用多次计算多少个字符不一样的函数。

那么可以加上前缀和优化。设 $m1_i$ 表示选第一个排列，到第 $i$ 个字符的上文函数值，$m2_i$、$m3_i$ 等以此类推。最后输出 $m1_r-m1_{l-1}$ 与其它该数组的最小值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,m,l,r;
string ss;
char a1[4] = {'a','b','c'};
char a2[4] = {'a','c','b'};
char a3[4] = {'b','a','c'};
char a4[4] = {'b','c','a'};
char a5[4] = {'c','a','b'};
char a6[4] = {'c','b','a'};
int m1[200001],m2[200001],m3[200001],m4[200001],m5[200001],m6[200001];

signed main()
{
	scanf("%d%d",&n,&m);
	cin >> ss;
	ss = " " + ss;
	for(int i = 1;i <= n;i++)
	{
		m1[i] = m1[i - 1];
		m2[i] = m2[i - 1];
		m3[i] = m3[i - 1];
		m4[i] = m4[i - 1];
		m5[i] = m5[i - 1];
		m6[i] = m6[i - 1];
		if(ss[i] != a1[i % 3]) m1[i]++;
		if(ss[i] != a2[i % 3]) m2[i]++;
		if(ss[i] != a3[i % 3]) m3[i]++;
		if(ss[i] != a4[i % 3]) m4[i]++;
		if(ss[i] != a5[i % 3]) m5[i]++;
		if(ss[i] != a6[i % 3]) m6[i]++;//计算前缀和
	}
	while(m--)
	{
		scanf("%d%d",&l,&r);
		printf("%d\n",min(m1[r] - m1[l - 1],min(m2[r] - m2[l - 1],min(m3[r] - m3[l - 1],min(m4[r] - m4[l - 1],min(m5[r] - m5[l - 1],m6[r] - m6[l - 1]))))));
	}
	return 0;
}
/*
abc 0
abb 1
cca 1
aaa 3
*/
```

---

## 作者：TheShuMo (赞：0)

#### 题面
定义一个字符串 $s$ 是“好的”，当且仅当 $s$ 不包含任何长度大于等于 $2$ 的回文子串。给定一个长度为 $n$ 的字符串 $S$ 和 $m$ 个询问，每次询问给定一个区间 $[l,r]$，求字符串 $S_{l,\dots,r}$ 变成“好的”字符串至少需要修改多少个字符。本题中字符集为 `abc`。数据范围 $n,m\le 200000$。
#### 分析
奇妙绿题，因为要判断修改几个保证不是回文串，那么可以直接考虑在只有 `abc` 三种字符的情况下，什么才一定不是回文串，比如说当前有 `xy`，`x` 和 `y` 都是 `abc` 三个字符中的之一，那么下一个就只能填除了 `xy` 以外的剩下那一个，否则就会产生形如 `xyx` 或者是 `yy` 的回文串。
所以只要对于六种情况都跑一遍前缀和，查询的时候减一下就行了。
#### Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define mp make_pair
namespace IO {
    #define int long long 
    #define gh getchar
    inline int read(){char ch=gh();int x=0;bool t=0;while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();return t?-x:x;}
    inline char getc(){char ch=gh();while(ch<'a'||ch>'z') ch=gh();return ch;}
    inline void write(int x){if(x < 0){putchar('-');x = -x;}if(x > 9){write(x / 10);}putchar((x % 10 + '0'));}
}
using namespace IO;
using namespace std;
const int Maxn = 200010;
char a[Maxn];
int sm[Maxn][7];
int ask(int l, int r){
    int _1 = sm[r][1] - sm[l-1][1];
    int _2 = sm[r][2] - sm[l-1][2];
    int _3 = sm[r][3] - sm[l-1][3];
    int _4 = sm[r][4] - sm[l-1][4];
    int _5 = sm[r][5] - sm[l-1][5];
    int _6 = sm[r][6] - sm[l-1][6];
    return min(min(min(min(min(_1,_2),_3),_4),_5),_6);
}
signed main(){
    int n, m, l, r;
    cin >> n >> m;
    cin >> a;
    for(int i = n; i >= 1; i--) a[i] = a[i - 1];
    int now = 0;
    for(int i = 1; i <= n; i++)
        sm[i][1] = sm[i-1][1] + ((now + 'a') != (int)a[i]), (now += 1) %= 3; now = 0;
    for(int i = 1; i <= n; i++)
        sm[i][2] = sm[i-1][2] + ((now + 'a') != (int)a[i]), now = (now - 1 + 3) % 3;now = 1;
    for(int i = 1; i <= n; i++)
        sm[i][3] = sm[i-1][3] + ((now + 'a') != (int)a[i]), (now += 1) %= 3;now = 1;
    for(int i = 1; i <= n; i++)
        sm[i][4] = sm[i-1][4] + ((now + 'a') != (int)a[i]), now = (now - 1 + 3) % 3;now = 2;
    for(int i = 1; i <= n; i++)
        sm[i][5] = sm[i-1][5] + ((now + 'a') != (int)a[i]), (now += 1) %= 3;now = 2;
    for(int i = 1; i <= n; i++)
        sm[i][6] = sm[i-1][6] + ((now + 'a') != (int)a[i]), now = (now - 1 + 3) % 3;
    while(m--){
        cin >> l >> r;
        int ans = ask(l,r);
        cout << ans << endl;
    }
}
```

---

## 作者：Gaode_Sean (赞：0)

对于任意三个字符，第一个和第二个不能相同，第一个和第三个不能相同，第二个和第三个不能相同。可以得到三个字符互不相同，即任意三个字符有六种排法：abc,acb,bac,bca,cab,cba。

所以本题可以转化成：对于一个区间 $[l,r]$，最少改变几个字符，使区间的字符按照六种排法之一排列？

记前缀和 $s_{i,j}$ 表示第 $i$ 种排法，$[1,j]$ 需要改变几个字符？

以第一种排法 abc 为例，下标 $\mod 3≡1$ 的字符需修改成 $a$，下标 $\mod 3≡2$ 的字符需修改成 $b$，下标 $\mod 3≡0$ 的字符需修改成 $c$。

对于一个区间 $[l,r]$ 它的第 $i$ 种排法的修改次数是 $s_{i,r}-s_{i,l-1}$ 。取六种排法的最小值即可。

## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char ch[200001],a1[3]={'a','b','c'},a2[3]={'a','c','b'},a3[3]={'b','a','c'},a4[3]={'b','c','a'},a5[3]={'c','a','b'},a6[3]={'c','b','a'};
int s[7][200001];
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",ch+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=6;j++) s[j][i]=s[j][i-1];
		if(ch[i]!=a1[i%3]) s[1][i]++;
		if(ch[i]!=a2[i%3]) s[2][i]++;
		if(ch[i]!=a3[i%3]) s[3][i]++;
		if(ch[i]!=a4[i%3]) s[4][i]++;
		if(ch[i]!=a5[i%3]) s[5][i]++;
		if(ch[i]!=a6[i%3]) s[6][i]++;
	}
	while(m--){
		int l,r,ans=1e9;
		scanf("%d%d",&l,&r);
		for(int i=1;i<=6;i++) ans=min(ans,s[i][r]-s[i][l-1]);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：mcDinic (赞：0)

首先对满足条件的字符串进行分析，据题意，则好的字符串不能有长度为二与长度为三的回文串，即**任意两个相邻的字符及任意两个间隔为一的字符不能相同。**

这样，长度为偶数的回文串，最中间两个字符必须相同，但任意两个相邻的字符不能相同，所以只要没有长度为二的回文串，则长度为偶数的就没有了。至于长度为奇数的字符串同理可得。

所以，**任意两个相邻的字符及任意两个间隔为一的字符不相同，该字符串即为好的字符串，若不满足，就不是。**

接下来进一步分析。若某字符串前两个字符确定，且不相同，那么第三个跟前两个都不同，只能为字符集中的另一个字符······这样递推，有：**若某字符串前两个字符确定，且不相同，则能且只能构成一个好的字符串。**

要满足前两个字符的条件，有 $A_3^2$ 种情况，枚举后取最优的改变方式，输出答案即可。（当然，写出字符串后发现每三个为一周期，分别判断也行）。

但是问题来了，这样时间复杂度会减少很多，但依旧会超时，需要弄个前缀和数组。

## Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,l,r,sum[10][200005];
char st[200005];
void dfs(char a,char b,char c,int fj){
	for(int i=1;i<=n;i++){
		int u=(i+3)%3;
		if(u==0)u=3;
		sum[fj][i]=sum[fj][i-1];
		if(u==1&&st[i]!=a)sum[fj][i]++;
		if(u==2&&st[i]!=b)sum[fj][i]++;
		if(u==3&&st[i]!=c)sum[fj][i]++;
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	scanf("%s",st+1);
	dfs('a','b','c',1);dfs('a','c','b',2);dfs('b','a','c',3);dfs('b','c','a',4);dfs('c','a','b',5);dfs('c','b','a',6);	
	while(m--){
		scanf("%lld%lld",&l,&r);
		int ans=0x3f3f3f3f;
		for(int i=1;i<=6;i++)ans=min(ans,sum[i][r]-sum[i][l-1]);
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Need_No_Name (赞：0)

# CF1555D Say No to Palindromes

## 题意：

定义一个字符串中要是未出现长度超过二的回文**子串**，就称这个字符串为“美丽的”。

先给定一个长度为 $n$ 的字符串 $S$，在给定 $m$ 次询问，每次询问包含 $l, r$ ，询问在字符串的 $[l, r]$ 区间中要至少进行多少次修改字母，使得字符串 $S_l - S_r$ 这个区间的字符串为“美丽的”。

同时，字符串 $S$ 仅由小写字母 $a, b, c$ 构成。

## 数据范围

$n, m ≤200000$

## 思路

先通过观察，首先出现两个相同的字母的肯定不行。我们以三个字母作为例子，可以看出只有六种搭配可以使得这个字符串为“美丽的”，也就是在三个字母各不相同的状态下，也就是`a, b, c` , `a, c, b` , `b, c, a` , `b, a, c`  , `c, a, b` , `c, b, a` 这六种排列，则最终的答案计算就是用这六种排列进行比较去输出即可。那么三个以上该如何处理呢？

观察可得，以上这六种方法中，只能以每一种方案为循环节这样持续循环下去，无法两两组合。两两组合可以发现无论如何都会构成回文子串。

那么就可以将这六种方法打成一张表，去用二维前缀和数组去比对。分别以这六种方案做前缀和，求出以每一种方案后需要的修改次数，最终在去输出这几种方案的 $min$ 值即可。



## 代码

```c++
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 2 * 1e5 + 10;
int n, m;
char ch[N];
int l, r;
int pre[N][7];
int ans = 0;
int s[7][3] = {{'a', 'b', 'c'}, {'a', 'c', 'b'}, {'b', 'a', 'c'}, {'b', 'c', 'a'}, {'c', 'b', 'a'}, {'c', 'a', 'b'}};
signed main()
{
	memset(pre, 0, sizeof(pre));
	cin >> n >> m;
	int tmp = 0;
	cin >> (ch + 1);
	for(int i = 0; i <= 6; i++)
	{
		tmp = 0;
		for(int j = 1; j <= n; j++)
		{
			tmp++;
			if(tmp == 3) tmp = 0;
			if(ch[j] != s[i][tmp]) pre[j][i]++;
			pre[j][i] += pre[j - 1][i];
		}
	}
	for(int i = 1; i <= m; i++)
	{
		cin >> l >> r;
		ans = INT_MAX;
		for(int j = 0; j <= 6; j++) ans = min(ans, pre[r][j] - pre[l - 1][j]);
		cout << ans << endl;
	}
	return 0;
}
```





---

## 作者：huayucaiji (赞：0)

看题目问法是线段树来做的。

仔细分一下发现，若有一个没有回文子串的串 $s$，对于任意 $i$，一定有 $s_i\neq s_{i-1}\neq s_{i+1}$。也就是说吗，这三个字符分别对应 `a,b,c`。也就是说， $s$ 的形式只有一下 $6$ 种：

- `abcabc...`
- `bcabca...`
- `cabcab...`
- `acbacb...`
- `cbacba...`
- `bacbac...`

对于线段树一个区间，我们维护 $s_{l,r}$ 对应 $6$ 种可能修改后的形式修改的字符数量即可。

明显我们可以通过这 $6$ 的两完成 `pushup`。

其他操作和基础线段树差不多。

为了写代码方便，你需要对着 $6$ 种形式合理编号。

```cpp
//Don't act like a loser.
//This code is written by huayucaiji
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
#include<bits/stdc++.h>
using namespace std;

int read() {
	char ch=getchar();
	while(ch<'a'||ch>'c') {
		ch=getchar();
	}
	return (ch-'a'+1)%3;
}

const int MAXN=2e5+10;

int n,m;
int a[MAXN];

struct segment {
	int val[2][3],len;
}s[MAXN<<2];

segment pushup(segment lft,segment rgt) {
	segment ret;
	ret.len=lft.len+rgt.len;
	
	for(int j=0;j<2;j++) {
		for(int i=0;i<3;i++) {
			ret.val[j][i]=lft.val[j][i]+rgt.val[j][(i+lft.len%3)%3];
		}
	}
	return ret;
}

void build(int l,int r,int p) {
	if(l==r) {
		for(int j=0;j<2;j++) {
			for(int i=0;i<3;i++) {
				s[p].val[j][i]=1;
			}
		}
		if(a[l]==1) {
			s[p].val[0][0]=s[p].val[1][0]=0;
		}
		if(a[l]==2) {
			s[p].val[0][1]=s[p].val[1][2]=0;
		}
		if(a[l]==0) {
			s[p].val[0][2]=s[p].val[1][1]=0;
		}
		s[p].len=1;
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	s[p]=pushup(s[p<<1],s[p<<1|1]);
}
segment query(int l,int r,int p,int x,int y) {
	if(r<x||y<l) {
		return s[0];
	}
	if(x<=l&&r<=y) {
		return s[p];
	}
	int mid=(l+r)>>1;
	return pushup(query(l,mid,p<<1,x,y),query(mid+1,r,p<<1|1,x,y));
}

signed main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		a[i]=read();
	}
	build(1,n,1);
	
	while(m--) {
		int l,r;
		scanf("%d%d",&l,&r);
		segment tmp=query(1,n,1,l,r);
		int ans=1e9;
		for(int j=0;j<2;j++) {
			for(int i=0;i<3;i++) {
				ans=min(ans,tmp.val[j][i]);
			}
		}
		printf("%d\n",ans);
	}

	return 0;
}
```

看了一眼官方题解后发现这个题是傻题。

希望大家学习一下这个思路就行，以官方题解的解法为主。

---

## 作者：_Clown_ (赞：0)

# D.Say No to Palindromes
$\mathtt{Difficulty}$=$\mathtt{1600}$

这道题放在第四道，差评！

实际上，看懂题目之后，我们不难想到一个结论：

> 该字符串一定是 $a,b,c$ 的一个排列不断重复

然后我们干脆暴力枚举 $6$ 种情况，但是我们会发现自己 $\texttt{TLE}$ 了

于是我们考虑加上一个前缀和维护，然后差分一把答案即可

然后就不难写出代码了
```cpp
#include<bits/stdc++.h>
using namespace std;
int N,M;
string S,S0[7]={"","abc","acb","bac","bca","cab","cba"};
int Prefix[7][200011];
int main(void)
{
    register int i,j;cin>>N>>M;cin>>S;S="@"+S;
    for(i=1;i<=6;i++)
    {
        for(j=1;j<=N;j++)if(S0[i][(j-1)%3]!=S[j])Prefix[i][j]=Prefix[i][j-1]+1;
                         else Prefix[i][j]=Prefix[i][j-1];
    }
    while(M--)
    {
        register int Left,Right;cin>>Left>>Right;
        register int Ans=Right-Left+1;
        for(i=1;i<=6;i++)Ans=min(Ans,Prefix[i][Right]-Prefix[i][Left-1]);
        cout<<Ans<<endl;
    }
    return 0;
}
```

---

## 作者：A_zjzj (赞：0)

[更好的阅读体验](https://blog.csdn.net/A_zjzj/article/details/119281513)

## 题目大意
给你一个字符串，每次询问区间 $[l,r]$ 最小需要改变几个才能使得这个区间的所有子区间都不是长度至少为 $2$ 的回文串。

## 思路
首先我们想一想所有子区间都不是长度至少为 $2$ 的回文串长什么样子。

- $a_i\ne a_{i+1}$
- $a_i\ne a_{i+2}$

这两个性质足够了。

所以这个串一定是形如 `123123···` 这样三个不同的字母组成的循环。

那么，对于每次询问，考虑枚举这个串的最终形式：

- `abcabc···`
- `acbacb···`
- `bacbac···`
- `bcabca···`
- `cabcab···`
- `cbacba···`

然后，要修改最少的步数变成这个目标串，可以看成算和这个目标串匹配的个数。

那么我们就可以把这三位分开处理，就只要询问一段区间中每隔三个是这个字符的数量就可以了，所以前缀和预处理递推一下就完事了。

最后要注意查询时区间前缀和左右端点是哪个减掉哪个就好了。

这个画个图就很直观的。

```cpp
1 2 3 1 2 3 1 2 3
1 2 3 4 5 6 7 8 9
    i     j
```
```cpp
1 2 3 1 2 3 1 2 3
1 2 3 4 5 6 7 8 9
    i       j
```
```cpp
1 2 3 1 2 3 1 2 3
1 2 3 4 5 6 7 8 9
    i         j
```
具体细节见代码。

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
void read(){}
template<typename _Tp,typename... _Tps>
void read(_Tp &x,_Tps &...Ar){
	x=0;char c=getchar();bool flag=0;
	while(c<'0'||c>'9')flag|=(c=='-'),c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(flag)x=-x;
	read(Ar...);
}
const int N=2e5+10;
int n,m,cnt[3][N],a[N];
char c[N];
int min(int a,int b,int c,int d,int e,int f){
	if(b<a)a=b;
	if(c<a)a=c;
	if(d<a)a=d;
	if(e<a)a=e;
	if(f<a)a=f;
	return a;
}
int solve(int l,int r,int x,int y,int z){
	int k;x--;y--;z--;
	if((r-l+1)%3==0){//对区间长度模 3 分类讨论
		k=cnt[x][r-2]-cnt[x][l-3]+cnt[y][r-1]-cnt[y][l-2]+cnt[z][r]-cnt[z][l-1];//计算匹配数
	}
	else if((r-l+1)%3==1){
		k=cnt[x][r]-cnt[x][l-3]+cnt[y][r-2]-cnt[y][l-2]+cnt[z][r-1]-cnt[z][l-1];
	}
	else{
		k=cnt[x][r-1]-cnt[x][l-3]+cnt[y][r]-cnt[y][l-2]+cnt[z][r-2]-cnt[z][l-1];
	}
	return r-l+1-k;//修改的个数就是区间长度减去匹配的个数
}
int get(){
	int i,l,r;
	for(read(n,m),scanf("%s",c+1),i=1;i<=n;i++)a[i]=c[i]-'a';
	for(i=1;i<=3;i++)cnt[a[i]][i]=1;
	for(i=4;i<=n;i++)cnt[0][i]=cnt[0][i-3]+(a[i]==0),cnt[1][i]=cnt[1][i-3]+(a[i]==1),cnt[2][i]=cnt[2][i-3]+(a[i]==2);
	while(m--){
		read(l,r);
		if(l==r)printf("0\n");//这里一定要特判掉
		else printf("%d\n",min(solve(l,r,1,2,3),solve(l,r,1,3,2),solve(l,r,2,1,3),solve(l,r,2,3,1),solve(l,r,3,1,2),solve(l,r,3,2,1)));//枚举每一种情况
	}
	return 0;
}
int main(){
	return get();
}
```
## 谢谢--zhengjun

---

## 作者：AmamiyaYuuko (赞：0)

首先注意到形成回文串的前提：必有长度为 $2$ 或 $3$ 的回文串。

由于题目限制字符集大小为 $3$，我们可以发现可能的不存在回文串的字符串只有六种：

- $s_1 = \text{abcabcabc} \cdots$

- $s_2 = \text{acbacbacb} \cdots$

- $s_3 = \text{bacbacbac} \cdots$

- $s_4 = \text{bcabcabca} \cdots$

- $s_5 = \text{cabcabcab} \cdots$

- $s_6 = \text{cbacbacba} \cdots$

将 $s$ 与上述所有串匹配，得到 $t_{i, j}$，表示 $[1, j]$ 需要修改几个字符得到 $s_i$，利用前缀和的思想可知询问的答案为 $\min \limits_{i = 1}^6(t_{i, r} - t_{i, l - 1})$。

代码实在太丑就不放了。

---

