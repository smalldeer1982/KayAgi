# Prefix Function Queries

## 题目描述

You are given a string $ s $ , consisting of lowercase Latin letters.

You are asked $ q $ queries about it: given another string $ t $ , consisting of lowercase Latin letters, perform the following steps:

1. concatenate $ s $ and $ t $ ;
2. calculate the prefix function of the resulting string $ s+t $ ;
3. print the values of the prefix function on positions $ |s|+1, |s|+2, \dots, |s|+|t| $ ( $ |s| $ and $ |t| $ denote the lengths of strings $ s $ and $ t $ , respectively);
4. revert the string back to $ s $ .

The prefix function of a string $ a $ is a sequence $ p_1, p_2, \dots, p_{|a|} $ , where $ p_i $ is the maximum value of $ k $ such that $ k < i $ and $ a[1..k]=a[i-k+1..i] $ ( $ a[l..r] $ denotes a contiguous substring of a string $ a $ from a position $ l $ to a position $ r $ , inclusive). In other words, it's the longest proper prefix of the string $ a[1..i] $ that is equal to its suffix of the same length.

## 样例 #1

### 输入

```
aba
6
caba
aba
bababa
aaaa
b
forces```

### 输出

```
0 1 2 3 
1 2 3 
2 3 4 5 6 7 
1 1 1 1 
2 
0 0 0 0 0 0```

## 样例 #2

### 输入

```
aacba
4
aaca
cbbb
aab
ccaca```

### 输出

```
2 2 3 1 
0 0 0 0 
2 2 0 
0 0 1 0 1```

# 题解

## 作者：Lynkcat (赞：7)

NOI 后第一篇题解，我是字符串萌新轻喷。

首先 KMP 复杂度基于均摊肯定不能每次都重新跑暴力。我们考虑尽可能保留一些东西。

于是考虑建自动机，先对原串 $s$ 建 KMP 自动机，方法就是顺着扫一遍如果下一个位置能匹配上当前字符那么后继状态就是 $i+1$ 否则从 border 转移过来因为 border 的每个转移都已经求出来了那么就直接继承过来。暴力做 $O(26n)$ 的，当然也可以用可持久化线段树做 $O(n \log 26)$ 但是这道题里没有什么必要。

然后就很自然了，扫一遍询问串，用 KMP 匹配，判断一下如果当前指针在 $n$ 以内的话用处理好的自动机 $O(1)$ 转移。复杂度是单次 $O(|t|)$ 的。

```c++
#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 1000005
using namespace std;
string st;
int dp[N][26];
int kmp[N];
int q;
void BellaKira()
{
	cin>>st;
	int n=st.size();
	st=' '+st;
	for (int i=1,j=0;i<=n;i++)
	{
		if (i!=1)
		{
			while (j&&st[j+1]!=st[i]) j=kmp[j];
			kmp[i]=j;
			if (st[kmp[i]+1]==st[i]) kmp[i]++,j++;
		}
		for (int k=0;k<26;k++)
		{
			if (i!=n&&st[i+1]==char('a'+k)) dp[i][k]=i;
			else dp[i][k]=dp[kmp[i]][k];
		}
	}
	cin>>q;
	while (q--)
	{
		string st1;
		cin>>st1;
		int m=st1.size();
		int j=kmp[n];
		st+=st1;
		for (int i=n+1,j=kmp[n];i<=n+m;i++)
		{
			while (j&&st[j+1]!=st[i]) 
			{
				if (j<=n) 
				{
					j=dp[j][st[i]-'a'];
					break;
				}
				j=kmp[j];
			}
			kmp[i]=j;
			if (st[kmp[i]+1]==st[i]) kmp[i]++,j++;
			cout<<kmp[i]<<" ";
		}
		cout<<'\n';
		while (m--) st.pop_back();
	}
}
signed main()
{
	IOS;cin.tie(0);
	int T=1;
	while (T--)
	{
		BellaKira();
	}
}
```

---

## 作者：include_BM (赞：6)

题意：给定字符串 $s$，多次询问，每次给定字符串 $t$，要求输出将 $s,t$ 拼接后形成的字符串所有长度 $>|s|$ 的前缀的最长 border。

前置知识：[P3375【模板】KMP 字符串匹配](https://www.luogu.com.cn/problem/P3375)。

设 $nxt_i$ 表示第 $i$ 个前缀的最长 border，$n=|s|$。

若只有一次询问，直接将 $t$ 接在 $s$ 后面跑一遍 KMP 即可。

由于当 $i\le n$ 时，$nxt_i$ 只与 $s$ 有关，故可以先对这一部分跑一遍 KMP，每次询问再将 $t$ 接在 $s$ 后面，跑剩下的部分。

```cpp
scanf("%s",s+n+1),m=strlen(s+n+1);
for(int i=n+1,j=nxt[n];i<=n+m;++i){
    while(j&&s[j+1]!=s[i]) j=nxt[j];
    if(s[j+1]==s[i]) ++j;
    printf("%d ",nxt[i]=j);
}
```

但是直接这样写会 TLE，因为第 $3$ 行不断跳 border 的部分还是 $O(n)$ 的。

设 $las_{i,j}$ 表示第 $i$ 个前缀的所有 border 中，最长的使得下一位刚好是 $j$ 的位置，当 $s_{i+1}=j$ 时 $las_{i,j}=i$，否则 $las_{i,j}=las_{nxt_i,j}$。

```cpp
signed main(){
    scanf("%s",s+1),n=strlen(s+1);
    for(int i=2,j=0;i<=n;++i){
        while(j&&s[j+1]!=s[i]) j=nxt[j];
        if(s[j+1]==s[i]) ++j;
        nxt[i]=j;
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<26;++j) las[i][j]=las[nxt[i]][j]; las[i][s[i+1]-'a']=i;
    }
    for(int q=read();q;--q,puts("")){
        scanf("%s",s+n+1),m=strlen(s+n+1);
        for(int i=n+1;i<=n+m;++i){
            nxt[i]=0; for(int j=0;j<26;++j) las[i][j]=0;
        }
        for(int j=0;j<26;++j) las[n][j]=las[nxt[n]][j]; las[n][s[n+1]-'a']=n;
        for(int i=n+1,j=nxt[n];i<=n+m;++i){
            if(s[j+1]!=s[i]) j=las[j][s[i]-'a'];
            if(s[j+1]==s[i]) ++j;
            printf("%d ",nxt[i]=j);
            for(int k=0;k<26;++k) las[i][k]=las[j][k]; if(i!=n+m) las[i][s[i+1]-'a']=i;
        }
    }
    return 0;
}
```

---

## 作者：Leasier (赞：5)

1. 简介

KMP 自动机主要用于动态 / 可持久化字符串匹配等。

说白了就是单串的 AC 自动机~~但显然更好写~~。

2. 构造

前置芝士：[KMP](https://oi-wiki.org/string/kmp/)

设原串为 $s$，$nxt_{i, j}$ 表示从 $i$ 开始沿着 fail 树向上跳得到的最大的位置 $k$ 使 $s_{k + 1} = j$。

注意到此时我们可以把 KMP 求前缀函数的过程表示为：对于 $i$，从 $fail_{i - 1}$ 开始沿着 fail 树向上跳找到的最大的位置 $k$ 使 $s_{k + 1} = s_i$，若不存在则为 $0$。这也可以让我们得到 $fail_i = nxt_{fail_{i - 1}, s_i}$。

由此我们可以想到对于 $nxt_{i, j}$：

- 当 $j = s_{i + 1}$，$nxt_{i, j} = i$。
- 当 $j \neq s_{i + 1}$，$nxt_{i, j} = nxt_{fail_i, j}$。

3. 应用

下文设字符集大小为 $w$。

这个东西的优点在于每步操作的时间复杂度不再是 KMP 的均摊 $O(1)$，而是严格的 $O(w)$。

**动态 / 可持久化字符串匹配**

显然每一步对于 $i$ 的转移我们都只会复制 $fail_i$ 的状态并进行一次单点修改。

当 $w$ 较小，直接暴力就行；当 $w$ 较大，可能需要可持久化线段树等支持复制历史版本和单点修改的数据结构。

- [例 1] [CF1721E Prefix Function Queries](https://www.luogu.com.cn/problem/CF1721E)

先求出 $s$ 的 KMP 自动机，每次询问在线构造 $s + t$ 中 $t$ 部分的 KMP 自动机并输出对应的 fail 值即可。时间复杂度为 $O(w(|s| + q|t|))$。

代码：
```cpp
#include <stdio.h>
#include <string.h>

int fail[1000017], nxt[1000017][27];
char s[1000017];

inline void kmp(){
	int n = strlen(&s[1]);
	for (register int i = 2, j = 0; i <= n; i++){
		while (j >= 1 && s[i] != s[j + 1]) j = fail[j];
		if (s[i] == s[j + 1]) j++;
		fail[i] = j;
	}
	for (register int i = 0; i < n; i++){
		for (register int j = 1; j <= 26; j++){
			nxt[i][j] = nxt[fail[i]][j];
		}
		nxt[i][s[i + 1] - 'a' + 1] = i;
	}
}

int main(){
	int n, ni, q;
	scanf("%s", &s[1]);
	n = strlen(&s[1]);
	ni = n + 1;
	kmp();
	scanf("%d", &q);
	for (register int i = 1; i <= q; i++){
		int m;
		scanf("%s", &s[ni]);
		m = n + strlen(&s[ni]);
		for (register int j = ni, k = fail[n]; j <= m; j++){
			int jd = j - 1;
			k = nxt[k][s[j] - 'a' + 1];
			if (s[j] == s[k + 1]) k++;
			fail[j] = k;
			printf("%d ", k);
			for (register int l = 1; l <= 26; l++){
				nxt[jd][l] = nxt[fail[jd]][l];
			}
			nxt[jd][s[j] - 'a' + 1] = jd;
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：OldDriverTree (赞：3)

KMP 自动机模板题。
___

# Solution

由于 KMP 是基于均摊的，所以显然不能每次询问暴力跑一遍 KMP，最坏时间复杂度 $O(\vert s\vert q)$。

考虑优化询问时 KMP 跳 nxt 的过程：预处理时记录每种状态后面加每种字符的 nxt，其实就是单串的 AC 自动机，当询问 KMP 时跳到原串部分后，直接返回结果。

时间复杂度 $O(\vert s\vert+\sum t_i)$。

# Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+11;
int n,m,q,nxt[N];
int f[N][26];
string s,t;

int main()
{
	cin.tie(0);
	cin>>s>>q,n=s.size(),s=' '+s;
	for (int i=1,j=0;i<=n;i++)
	{
		if (i>1) {
			while (j&&s[j+1]^s[i]) j=nxt[j];
			if (s[j+1]==s[i]) j++; nxt[i]=j;
		}
		for (int c=0;c<26;c++) {
			if (s[i+1]=='a'+c) f[i][c]=i;
			else f[i][c]=f[j][c];
		}
	}
	while (q--)
	{
		cin>>t,m=t.size(),s+=t;
		for (int i=n+1,j=nxt[n];i<=n+m;i++)
		{
			while (s[j+1]^s[i]) {
				if (j<=n) { j=f[j][s[i]-'a']; break; }
				j=nxt[j];
			}
			if (s[j+1]==s[i]) j++;
			printf("%d ",nxt[i]=j);
		}
		printf("\n");
		while (m--) s.pop_back();
	}
	return 0;
}
```

---

## 作者：Qzong (赞：3)

很可惜，这种做法可以过去此题。

这是一种快乐又暴力的方法。

考虑暴力匹配，复杂度是 $O(q|s|)$ 的。

我们考虑怎样的串会使询问卡到复杂度上界。

容易发现当且仅当字符串全部相同时，跳 $fail$ 树的次数会达到 $|S|$。

构造方法为询问串形如 $a...az$。

仔细观察，发现在此串的情况下，当 $fail$ 跳到底时本质不同的串（可能长度不同）只有 $26|t|$ 种。

所以，我们只需记入下跳过 $fail$ 的字符串，记下此时所在的位置，不再重复跳即可。

感性理解，其余情况均优于此情况。

复杂度上界 $O(|s||t|+q|t|\log q|t|)$。

非常的不讲道理，非常的快乐。

```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
const int N=1000100;
char s[N],t[N];
int net[N],n,now;
std::map<unsigned long long,int>p;
unsigned long long tmp;
int main(){
	int i,j=0;
	scanf("%s",s+1),n=strlen(s+1); 
	for(i=2;i<=n;i++){
		while(j!=0&&s[i]!=s[j+1])j=net[j];
		if(s[i]==s[j+1])j++;
		net[i]=j;
	}
	now=j;
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%s",t+1);
		int m=strlen(t+1);
		for(i=n+1;i<=n+m;i++)s[i]=t[i-n];
		j=now;
		tmp=0;
		int flag=1;
		for(i=n+1;i<=n+m;i++){
			tmp=tmp*29+s[i]-'a'+1;
			if(flag&&p.count(tmp)){
				j=net[i]=p[tmp];continue;
			}
			else flag=0;
			while(j!=0&&s[i]!=s[j+1])j=net[j];
			if(s[i]==s[j+1])j++;
			net[i]=j;
			p[tmp]=j;
		}
		for(i=n+1;i<=n+m;i++)printf("%d ",net[i]);
		puts("");
	}
	return 0;
}
```


---

## 作者：Mirasycle (赞：1)

kmp 自动机模板题。

最直观的解法就是我们先对于串 $s$ 求一遍 kmp。然后对于加入的后缀 $t$ 接到 $s$ 后面，对于串 $s+t$ 从 $\lvert s\rvert+1$ 位置开始跑 kmp。

但是这个复杂度是错的，因为思考原版 kmp 是如果保证复杂度的，由于每次指针最多往后移动一位，所以我们的指针 $j$ 向右的移动量最大为 $n$。因此向左的最大移动量也为 $n$，这个是依赖均摊做到 $O(n)$ 的。

但是如果这次我们还均摊的话，会把 $\lvert s\rvert$ 也给摊上，做 $q$ 次显然是不对的。思考如果加速 $s$ 部分的转移，我们建立 kmp 自动机，对于每个位置往后加一个字符跳到哪里直接做一个链接，这样子在 $i\le \lvert S\rvert$ 的部分就可以 $O(1)$ 直接跳了。于是复杂度就正确了。

---

## 作者：AZYDLL (赞：0)

KMP 自动机模板题。

## 思路

在字符串 $s$ 上建立 KMP 自动机，并保留 $s$ 末尾的状态。每次输入 $t_i$ 就将 $t_i$ 接在 $s$ 的后面并从 $s$ 末尾的状态开始跑 KMP。由于已经建立了自动机，所以在对每个 $t_i$ 跑 KMP 的过程中只要状态 $k$ 满足 $k<|s|$ 就可以在自动机上直接转移。可以证明对于每个 $t_i$，这个过程是 $O(|t_i|)$ 的。

令字符集大小为 $w$（在本题中 $w \le 26$），则总时间复杂度为 $O(w|s|+\sum t_i)$。

## 代码


```cpp
#include<bits/stdc++.h>
#define MAXN 1100005
#define MAXW 35

using namespace std;
namespace FastIO
{
	inline string _rs()
	{
		string str="";
		int ch=getchar();
		while(ch==' ' || ch=='\n' || ch=='\r') ch=getchar();
		while(ch!=' ' && ch!='\n' && ch!='\r' && ch!=EOF){
			str.push_back(ch);
			ch=getchar();
		}
		return str;
	}
	inline void _ws(string a,char b)
	{
		int len=a.size();
		for(int i=0;i<len;i++) putchar(a[i]);
		putchar(b);
		return ;
	}
	inline int _r()
	{
		int flag=1,ans=0,ch=getchar();
		while((ch<'0' || ch>'9') && ch!=EOF){
			if(ch=='-') flag=-1;
			ch=getchar();
		}
		while(ch>='0' && ch<='9'){
			ans=(ans<<1)+(ans<<3)+(ch^48);
			ch=getchar();
		}
		return flag*ans;
	}
	inline void _w(int a,char b)
	{
		if(a<0) a=-a,putchar('-');
		int sta[22],top=0;
		do{
			sta[top++]=a%10;
			a/=10;
		}while(a);
		while(top) putchar(sta[--top]+48);
		putchar(b);
		return ;
	}
}
using namespace FastIO;

int n,q,len,flag,kmp[MAXN],fsm[MAXW][MAXN];
string str,s1;

int main()
{
	str=" "+_rs();
	n=str.size()-1;
	for(int i=2;i<=n;i++){
		kmp[i]=kmp[i-1];
		while(kmp[i] && str[i]!=str[kmp[i]+1]) kmp[i]=kmp[kmp[i]];
		if(str[i]==str[kmp[i]+1]) kmp[i]++;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<26;j++){
			if(i && 'a'+j!=str[i+1]) fsm[j][i]=fsm[j][kmp[i]];
			else fsm[j][i]=i+('a'+j==str[i+1]);
		}
	}
	
	q=_r();
	while(q--){
		s1=_rs();
		str+=s1;
		s1=" "+s1;
		len=s1.size()-1;
		for(int i=1,j=kmp[n];i<=len;i++){
			flag=1;
			while(j && s1[i]!=str[j+1]){
				if(j<n){
					j=fsm[s1[i]-'a'][j];
					flag=0;
					break;
				}
				j=kmp[j];
			}
			if(flag && s1[i]==str[j+1]) j++;
			kmp[n+i]=j;
			_w(j,' ');
		}
		while(len--) str.pop_back();
		_ws("",'\n');
	}
	
	return 0;
}
```

---

## 作者：Le0Chan (赞：0)

来点 SAM 题解。

首先分类讨论：

先计算对于第 $i$ 个串的长为 $j$ 前缀 $\le j$ 的 border。下面都对第 $i$ 个串进行考虑。对于位置 $k$，考虑其对哪些 $j\ge k$ 能产生贡献，当然是 $j\in[k,k+\operatorname{lcp}(s,t_{i,k})-1]$，直接做一个区间取 $\max$ 即可。

下来计算 border 更长的答案。容易发现答案形如一段 $s$ 既是前缀又是后缀的串拼上 $t_{i,j}$。这样的前缀只有 $O(|s|)$ 种，预处理出来。则对于其中的某个前缀 $x$，能对 $t_{i,j}$ 产生贡献当且仅当 $\operatorname{lcp}(x,i)\ge j$。放在后缀树上看，就是某个点 $x$ 与 $i$ 的 $\operatorname{lca}$ 的长度 $\ge j$。

由于后缀树上呈后代关系的点，深度也是单调的。所以树上倍增出一条链满足当 $\operatorname{lca}$ 在这条链上时，$x$ 能产生贡献。再预处理出每个点子树的最大 $x$，即可直接求链 $\max$。倍增的时候顺便算一下即可。

复杂度没算错的话是一只 $\log$。本来要写的，但是发现 SAM 空间太大夭折了。写哈希表存边有可能能过。内容全口胡，有问题私信。

---

## 作者：naroto2022 (赞：0)

# CF1721E 题解

### 题面

[原题传送门](https://www.luogu.com.cn/problem/CF1721E)

### 前置知识

KMP，基本的字符串函数。

（不懂 KMP 的可以翻到最底下看看后记）

### 思路

对于每个询问，其实只要把 $t$ 接在 $s$ 的后面跑 KMP 即可。（不懂 KMP 的看后记！）

但这样会 TLE。。。

很遗憾，那就多设一个数组 $last$。

设 $last_{i,j}$ 表示第 $i$ 个前缀的所有 border（最长公共前后缀）中，最长的使得下一位刚刚好是 $j$ 的位置。

如：若 $s_{i+1}=j$，则 $last_{i,j}=i$，否则 $last_{i,j}=last_{f_i,j}$

好了，不多说了，上代码！

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=1000025;
char s[N];
int n,m,q,last[N][35],f[N];
void init(){
	int j=0; 
    for(int i=2; i<=n; i++){
        while(j&&s[j+1]!=s[i]) j=f[j];
        f[i]=j+=s[j+1]==s[i];
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<26; j++) last[i][j]=last[f[i]][j]; 
		last[i][s[i+1]-'a']=i;
    }
}
int main(){
    scanf("%s",s+1);//从1开始输入 
	n=strlen(s+1);//求原字符串的长度 
	init();//初始化 
	scanf("%d",&q); 
    while(q--){
        scanf("%s",s+n+1);//从n+1开始输入，直接接在原字符串后面 
		m=strlen(s+n+1);//求新输入的字符串的长度 
        for(int i=n+1; i<=n+m; i++){
            f[i]=0; 
			for(int j=0; j<26; j++) last[i][j]=0;
        }
        for(int j=0; j<26; j++) last[n][j]=last[f[n]][j]; 
		last[n][s[n+1]-'a']=n;
		int j=f[n];
        for(int i=n+1; i<=n+m; i++){
            if(s[j+1]!=s[i]) j=last[j][s[i]-'a'];
        	f[i]=j+=s[j+1]==s[i];
            printf("%d ",f[i]);
            for(int k=0; k<26; k++) last[i][k]=last[j][k]; 
			if(i!=n+m) last[i][s[i+1]-'a']=i;
        }
        printf("\n");//别忘了换行 
    }
    return 0;
}
```


### 后记

### KMP

#### 问题引入

[P3375 【模板】KMP](https://www.luogu.com.cn/problem/P3375)

#### 算法简介

KMP 算法（Knuth-Morris-Pratt 算法）是一个字符串匹配算法。

即对于两个字符串 $s$ 和 $t$，长度分别为 $n$ 和 $m$。我们分别称它为文本串 $s$ 和模式串 $t$。

KMP 可以在 $O(n+m)$ 求得模式串 $t$ 在文本串 $s$ 中的所有出现位置和出现次数。

这里 $t$ 在 $s$ 中出现即为 $t$ 作为 $s$ 的子串。

在 KMP 算法中，我们需要对于模式串先预处理出一个 $fail$ 数组，记为 $f$ 数组。

$f[i]$ 表示 $t$ 的前缀 $t_0,t_1,\cdots,t_i$ 的 border 长度。

border 的中文意思为“最长公共前后缀”。对于某个字符串，他的 border 定义为该串最长的不为自身的前缀，使得该串存在一个后缀与这个前缀相同。

#### 算法流程

朴素的暴力方法是枚举 $s$ 的每个长为 $m$ 的子串，暴力判断是否相同，时间复杂度 $O(nm)$。

暴力复杂度不太能接受。

也许在学习了哈希后你会想，上述过程是否可以用哈希优化呢？

但哈希在代码实现上比 KMP 更为复杂，以及常数较大、正确性上的问题也很难使得我们可以“舒服得”使用哈希代替 KMP。

而且 KMP 的核心思想与部分字符串问题的核心思想类似，即在失配的
时候，运用已经配对成功的前缀这个信息。

在匹配过程中，我们一般用两个双指针 $i,j$，分别指向 $s$ 串和 $t$ 串。

假设我们在 $s[i]$ 和 $t[j]$ 处发生失配，则：

- 若 $j==0$，则 $i++$。
- 若 $j>0$，则 $j=f[j - 1]$。

若配对成功，我们可以当作 $s[i]$ 和 $t[m]$ 发生失配，$j=f[m-1]$（$m$ 为 $t$ 的长度）。

上述过程中，每次配对成功 $i,j$ 都会加 $1$（最多 $n$ 次）。

失配时，若 $j==0$，则 $i$ 会加 $1$（最多 $n$ 次）。

若 $j>0$，则 $j$ 至少减少 $1$，显然也不超过增加时的 $n$ 次。也就是 $s$ 和 $t$ 串匹配的过程，时间复杂度为 $O(n)$ 的。

求 $fail$ 数组的部分与匹配的部分类似。

我们发现，前缀 $t_0,t_1,\cdots,t_i$ 的 border 去掉末尾的字符后，一定是前缀 $t_0,t_1,\cdots,t_{i-1}$ 的公共前后缀。

因此，我们考虑从前往后递推计算 $fail$ 数组。

设当前需要计算 $f[i]$，我们按长度从大到小遍历前缀 $t_0,t_1,\cdots,t_{i-1}$ 的所有公共前后缀。

若均未找到或找到某个公共前后缀，使得其后面加一个字符 $t_i$ 后能成为 $t_0,t_1,\cdots,t_i$ 的公共前后缀，即为所求 border。


---

## 作者：蒟蒻君HJT (赞：0)

比较简单的一个字符串题目，前缀知识是 KMP 模式串匹配算法，对失配树有所了解更好。

## 一、题意

- 给定字符串 $s$，以及 $q$ 个串 $t_i$，求将 $s$ 分别与每个 $t_i$ 拼接起来后，最靠右的 $|t_i|$ 个前缀的 border 长度。询问间相互独立。

- $|s|\leq 10^6, q \leq 10^5, |t_i|\leq 10$ 。

## 二、解法

考虑暴力怎么做。首先我们对 $s$ 跑 KMP 求出 $fail$ 数组。

接下来每次接上 $t_i$ 时，再求出后面 $|t_i|$ 位的 $fail$ 数组（ border 长度）。

那么我们可以写出朴素的代码：



```cpp
scanf("%s", s + 1);
fail[0] = -1, fail[1] = 0;
for(int i = 2; i <= strlen(s + 1); ++i){
	int j = fail[i - 1];
	while(j != -1 && s[j + 1] != s[i]) j = fail[j];
	fail[i] = j + 1;
}
for(int i = 1; i <= q; ++i){
	scanf("%s", t + 1);
	for(int j = 1; j <= strlen(t + 1); ++j){
		int k = fail[strlen(s + 1) + j - 1];
		while(k != -1 && s[k + 1] != t[j]) k = fail[k];
		fail[j] = k + 1;
		printf("%d ", fail[j]);
	}
	printf("\n");
}
```

但是这样的复杂度是 $O(q(|s|+|t|))$ 的，因为 KMP 算法线性的原因是复杂度在整个串跑 KMP 的时候均摊掉了，而这道题每个询问都是在一个前缀（即 $s$ 串）固定的情况下继续求出后面的 $fail$ 数组，单次复杂度可以达到 $O(|s|)$ 级别。

因此，需要一些优化。注意到如果我们把 $fail_i$ 设置为 $i$ 节点的父节点 （$0$ 没有父节点）的话，一定可以形成一棵树，而每次跳转 $fail$ 就相当于走到父节点。这就是 $fail$ 树。那么我们每次求询问的第 $j$ 位的答案时，要求的本质就是在 $fail$ 树上的某一个节点上，最近的一个祖先 $x$ 存在 $t_j$ 这个转移边，即满足 $(s+t)_{x+1}=t_j$ 。 为了加速这一过程，我们用一个二维数组 $next_{i,j}$ 表示节点 $i$ 的第一个有字符 $j$ 的转移边祖先的编号。显然存在以下递推式：

$next_{0,j}= -1, j \neq (s+t)_1 $

$next_{0,j}= 0, j = (s+t)_1$

$next_{i,j} = next_{fail_i,j}, j \neq (s+t)_{i+1}$

$next_{i,j} = i, j = (s+t)_{i+1}$ 

说人话就是把父节点的状态继承下来，并更新一个转移边。

有了 $next$ 数组后，我们就可以一步跳转到应该到达的节点并更新 $fail$ 了。唯一需要注意的是当我们在串的末尾加入一个字符时（求 $fail$），应该同时更新**上一个字符**的 $next$ 数组。原因自己想。

由此，时间复杂度降低为 $O(26(|s|+q|t|))$ 。
当然也可以用可持久化线段树把 $26$ 变成 $\log 26$ ，不过没必要。

## 三、代码

提交记录： [link](https://codeforces.com/contest/1721/submission/169891936)


---

