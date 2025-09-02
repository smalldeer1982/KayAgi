# Xor-Subsequence (hard version)

## 题目描述

这是此问题的困难版本。简单版本与困难版本的唯一区别在于：在困难版本中，$a_i\leq 10^9$。

给你一个长为 $n$ 的整数数组 $a$，从 $0$ 开始编号。

一个长为 $m$ ，从 $0$ 开始编号的整数数组 $b$ 是数组 $a$ 的 subsequence，当且仅当 $0\leq b_0<b_1<\dots<b_{m-1}<n$。

若 $b$ 是 $a$ 的 beautiful subsequence，当且仅当满足以下条件：

+ $b$ 是 $a$ 的 subsequence；
+ $\forall p\in[0,m)\cap\textbf{N},a_{b_p}\oplus b_{p+1}<a_{b_{p+1}}\oplus b_p$。

其中 $\oplus$ 表示位运算中的异或运算。

现在，你需要求出最长的 beautiful subsequence 有多长。

## 说明/提示

$1\leq T\leq 10^5,2\leq n\leq 3\times 10^5,0\leq a_i\leq 10^9,\sum n\leq 3\times 10^5$。

## 样例 #1

### 输入

```
3
2
1 2
5
5 2 4 3 1
10
3 8 8 2 9 1 6 2 8 3```

### 输出

```
2
3
6```

# 题解

## 作者：E1_de5truct0r (赞：20)

## 前言

01Trie 优化 dp 好题，这是我第一道模板性不那么强的 01Trie 题（

注明：下文的 $\oplus$ 符号均代表异或（$\operatorname{xor}$，`^`）运算。

## 思路

如果 $a_i \oplus j<a_j \oplus i$，那么说明，$a_i \oplus j$ 和 $a_j \oplus i$ 一定有前面 $k$ 位都是相同的，第 $k+1$ 位的时候，前者是 $0$ 而后者是 $1$。

但是这样维护的话，是包含两个参数 $i,j$ 的，我们尝试把它变成只有一个参数进行维护。

对于前面 $k$ 位，我们假设 $a_i$ （后面都指在二进制下）第 $k$ 位是 $A$，$j$ 第 $k$ 位是 $B$，$a_j$ 第 $k$ 位是 $C$，$i$ 第 $k$ 位是 $D$。

那么有：$A \oplus B = C \oplus D$。

我们进行移项得到，$A \oplus D=B\oplus C$，即 $a_i \oplus i$ 的第 $k$ 位 $=a_j \oplus j$ 的第 $k$ 位。于是前 $k$ 位我们转化成了一个参数的问题。

而第 $k+1$ 位怎么解决呢？我们现在可以得到，$A \oplus B=0,C \oplus  D=1$。也就是说，$A=B=C,D$ 中任意一个。

考虑进行分类讨论：

1. 若 $A=B=C$，则 $A \oplus D=1,B \oplus C=0$。

2. 若 $A=B=D$，则 $A \oplus D=0,B \oplus C=1$。

所以我们发现它们一定是在相反的那一方更新到的答案。至此，我们把它成功的转化成了只含有一个参数的问题。

剩下的就比较显然了。我们只需要找到所有的满足上述条件的 dp 的最大值即可。显然用 01Trie 即可维护。

查询最大值的时候，我们就从前往后一位一位找，每次用当前位取反的那一边更新答案。然后继续往下找，直到找不到了就停止。

然后我们把当前的值插入 Trie。对 $a_i \oplus i$ 进行拆位，插入 $01 \operatorname{Trie}$ 中，对每一个节点更新它的 $\max$。

最后输出即可。复杂度是 $O(n \log w)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=300005;
int tr[MAXN*31][2],mx[MAXN*31][2],tot=1; // 空间开 30 倍
int a[MAXN],dp[MAXN];
void insert(int x,int val){
	int now=1,p=a[x]^(x-1); // 这里要减一，因为题目中下标从零开始，我一开始没看到调了好久。 
	for(int j=30;j>=0;j--){
//		cout<<"qwq "<<now<<endl;
		bool bitp=p&(1<<j),bitx=(x-1)&(1<<j); // 分别记录两个二进制位（要用 bool 存储！） 
//		cout<<bitp<<" "<<bitx<<endl;
		if(!tr[now][bitp]) tr[now][bitp]=++tot; // 如果没有，那么新建节点 
		mx[tr[now][bitp]][bitx]=max(mx[tr[now][bitp]][bitx],val); // 更新最大值 
		now=tr[now][bitp]; // 往后接着找 
	}
}
int query(int x){
	int now=1,p=a[x]^(x-1),ans=0; // 这里减一是同理的 
	for(int j=30;j>=0;j--){
//		cout<<"qwq "<<now<<endl;
		bool bitp=p&(1<<j),bitx=a[x]&(1<<j); // 这里要用 a[x]，至于是为什么，留给读者思考（其实随便推一推就好了） 
//		cout<<bitp<<" "<<bitx<<endl;
		if(tr[now][!bitp]) ans=max(ans,mx[tr[now][!bitp]][!bitx]); // 如果另一边有数，说明有贡献 
		if(tr[now][bitp]) now=tr[now][bitp]; // 然后往下走 
		else break; // 如果没了就撤出 
	}
	return ans;
}
int main(){
	int T; cin>>T;
	while(T--){
		int n,maxn=-1e9; cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			dp[i]=query(i)+1; // 每次在最大值的基础上加一 
//			cout<<"dp["<<i<<"]="<<dp[i]<<endl;
			insert(i,dp[i]); // 插入最大值 
			maxn=max(maxn,dp[i]); // 求 max 
		}
		cout<<maxn<<endl;
		for(int i=1;i<=tot;i++){ // 最后记得清空字典树！ 
			tr[i][0]=tr[i][1]=0;
			mx[i][0]=mx[i][1]=0;
		}tot=1;
	}
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：13)

看到 Indjy 大佬写了篇四叉 trie 的[题解](https://www.luogu.com.cn/blog/_post/470623)，我来个二叉（就是 01trie）的。

## 思路

设 $f_i$ 表示以 $i$ 为结尾的最长的漂亮子序列长度。

$$f_i=1+\max(f_j)\quad a_j\operatorname{xor}i<a_i\operatorname{xor}j$$

已知的是 $i$ 和 $a_i$，我们可以操控 $j$ 和 $a_j$。

从高位往低位考虑：

1. 使 $a_j\operatorname{xor}i=0,a_i\operatorname{xor}j=1$。这种情况可直接计入 $f_i$。
2. 使 $a_j\operatorname{xor}i=a_i\operatorname{xor}j$。这种情况需要再向低位去判断。

根据需要，把 $\large a_j\operatorname{xor}j$ 丢进 trie 树，并在每个节点记录 $\large a_j$ 的这一位为 $0/1$ 的最大 $f$ 值。

1. 使 $a_j\operatorname{xor}i=0,a_i\operatorname{xor}j=1$。查询 $a_j\operatorname{xor}j=a_i\operatorname{xor}i\operatorname{xor}1,a_j=i$。
2. 使 $a_j\operatorname{xor}i=a_i\operatorname{xor}j$。向 $a_j\operatorname{xor}j=a_i\operatorname{xor}i$ 走到下一层。

## code

```cpp
#include<stdio.h>
#define N 300000
#define M 9999999
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int t,n,m,a,f,ans,tre[M][2],maxn[M][2];
inline void max(int&x,const int&y){if(x<y)x=y;}
main()
{
	for(read(t);t--;)
	{
		for(;m;maxn[m][0]=maxn[m][1]=tre[m][0]=tre[m][1]=0,--m);
		maxn[0][0]=maxn[0][1]=tre[0][0]=tre[0][1]=0;
		read(n);ans=0;
		for(int i=0;i<n;++i)
		{
			read(a);f=0;
			for(int j=0,k=29;k>=0&&(j||k==29);j=tre[j][(a>>k&1)^(i>>k&1)],--k)
				if(tre[j][(a>>k&1)^(i>>k&1)^1])
					max(f,maxn[tre[j][(a>>k&1)^(i>>k&1)^1]][i>>k&1]);
			max(ans,++f);
			for(int j=0,k=29;k>=0;j=tre[j][(a>>k&1)^(i>>k&1)],--k)
			{
				if(!tre[j][(a>>k&1)^(i>>k&1)])tre[j][(a>>k&1)^(i>>k&1)]=++m;
				max(maxn[tre[j][(a>>k&1)^(i>>k&1)]][a>>k&1],f);
			}
		}
		printf("%d\n",ans);
	}
}
```

祭我的第一次 vp。

---

## 作者：lndjy (赞：9)

一眼优化 dp，显然设 $f_i$ 表示以 $i$ 结尾的最长子序列，$f_i=\max(f_j)+1$，其中 $a_j \operatorname{xor} i<a_i \operatorname{xor} j$。

但是这样是 $n^2$ 的，D1 都过不去。

如果你做过一些 dp 优化题的话，你应该了解这种 dp 一般是想办法把和 $i,j$ 有关的项分离开。

但是这个异或，没法分啊？那怎么办？拆位！

考虑对于每一位，将 $(i,a_i)$ 视为一个二元组，重新定义比较：

$$(0,0)=(1,1),(0,1)=(1,0)$$

$$(0,0)>(1,0),(0,1)>(0,0)$$

$$(1,0)>(1,1),(1,1)>(0,1)$$

按照这个规则，$i$ 能从 $j$ 转移的条件就变为了从高到低若干位，$(i,a_i)=(j,a_j)$，且对于下一位，$(i,a_i)>(j,a_j)$。

只分析到这里，就可以通过 D1 了：对于每个数，把它塞进一个 Trie，这个 Trie 是 4 叉的，在哪个儿子对应当前位是哪个二元组。（细节见代码）

Trie 上维护子树 max，查询的时候大力 dfs 这个 Trie 即可。

D1 code:

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=3e5+5;
int b[N],f[N],n;
int son[N*32][2][2],maxx[N*32];
int tot=1;
bool a[32][2];
int val;
void ins()
{
	int now=1;
	for(int i=30;i>=0;i--)
	{
		maxx[now]=max(maxx[now],val);
		if(!son[now][a[i][0]][a[i][1]]) son[now][a[i][0]][a[i][1]]=++tot;
		now=son[now][a[i][0]][a[i][1]];
	}
	maxx[now]=max(maxx[now],val);
}
int ask(int now,int dep)
{
	int ans=0;
	if(a[dep][0]==0&&a[dep][1]==0)
	{
		if(son[now][0][0])
		ans=max(ans,ask(son[now][0][0],dep-1));
		if(son[now][1][1])
		ans=max(ans,ask(son[now][1][1],dep-1));
		ans=max(ans,maxx[son[now][1][0]]);
		return ans;
	}
	if(a[dep][0]==0&&a[dep][1]==1)
	{
		if(son[now][0][1])
		ans=max(ans,ask(son[now][0][1],dep-1));
		if(son[now][1][0])
		ans=max(ans,ask(son[now][1][0],dep-1));
		ans=max(ans,maxx[son[now][0][0]]);
		return ans;
	}
	if(a[dep][0]==1&&a[dep][1]==0)
	{
		if(son[now][1][0])
		ans=max(ans,ask(son[now][1][0],dep-1));
		if(son[now][0][1])
		ans=max(ans,ask(son[now][0][1],dep-1));
		ans=max(ans,maxx[son[now][1][1]]);
		return ans;
	}
	if(a[dep][0]==1&&a[dep][1]==1)
	{
		if(son[now][0][0])
		ans=max(ans,ask(son[now][0][0],dep-1));
		if(son[now][1][1])
		ans=max(ans,ask(son[now][1][1],dep-1));
		ans=max(ans,maxx[son[now][0][1]]);
		return ans;
	}
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;n--;
		for(int i=0;i<=n;i++)
		cin>>b[i],f[i]=0;
		int ans=0;
		for(int i=0;i<=n;i++)
		{
			for(int j=30;j>=0;j--)
			a[j][0]=i&(1<<j),a[j][1]=b[i]&(1<<j);//,cout<<a[j][0]<<" "<<a[j][1]<<endl;
			val=ask(1,30)+1;
			//cout<<val<<endl;
			ans=max(ans,val);
			ins();
		}
		cout<<ans<<endl;
		for(int i=1;i<=tot;i++)
		maxx[i]=son[i][0][0]=son[i][1][0]=son[i][0][1]=son[i][1][1]=0;
		tot=1;
	}
 	return 0;
}
```

然后考虑 D2。

你对着 D1 的代码看，发现这个 dfs 的过程很蠢，就像 P4169 KDT dfs 了整个树一样。

回想一下，P4169 是怎么优化的？最优性剪枝！ 在 D1 代码中，我们先 ask 了两个儿子，然后在和当前节点比较，那不如，维护一个全局 ans，每次先用当前节点的更新，然后查询的时候如果子树最大值已经小于答案了，就直接 return。

复杂度还是不对的，但是常数大大减小，考虑这是 div2，没几个人过，过了的不一定叉你，所以它不会 FST，不过可以 hack。

D2 code1：

```
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=3e5+5;
int b[N],f[N],n;
int son[N*32][2][2],maxx[N*32];
int tot=1;
bool a[32][2];
int val;
void ins()
{
	int now=1;
	for(int i=30;i>=0;i--)
	{
		maxx[now]=max(maxx[now],val);
		if(!son[now][a[i][0]][a[i][1]]) son[now][a[i][0]][a[i][1]]=++tot;
		now=son[now][a[i][0]][a[i][1]];
	}
	maxx[now]=max(maxx[now],val);
}
int ans;
void ask(int now,int dep)
{
	if(maxx[now]<=ans) return;
	if(a[dep][0]==0&&a[dep][1]==0)
	{
		ans=max(ans,maxx[son[now][1][0]]);
		if(son[now][0][0])
		ask(son[now][0][0],dep-1);
		if(son[now][1][1])
		ask(son[now][1][1],dep-1);
	}
	if(a[dep][0]==0&&a[dep][1]==1)
	{
		ans=max(ans,maxx[son[now][0][0]]);
		if(son[now][0][1])
		ask(son[now][0][1],dep-1);
		if(son[now][1][0])
		ask(son[now][1][0],dep-1);
	}
	if(a[dep][0]==1&&a[dep][1]==0)
	{
		ans=max(ans,maxx[son[now][1][1]]);
		if(son[now][1][0])
		ask(son[now][1][0],dep-1);
		if(son[now][0][1])
		ask(son[now][0][1],dep-1);
	}
	if(a[dep][0]==1&&a[dep][1]==1)
	{
		ans=max(ans,maxx[son[now][0][1]]);
		if(son[now][0][0])
		ask(son[now][0][0],dep-1);
		if(son[now][1][1])
		ask(son[now][1][1],dep-1);
	}
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;n--;
		for(int i=0;i<=n;i++)
		cin>>b[i],f[i]=0;
		int anss=0;
		for(int i=0;i<=n;i++)
		{
			for(int j=30;j>=0;j--)
			a[j][0]=i&(1<<j),a[j][1]=b[i]&(1<<j);//,cout<<a[j][0]<<" "<<a[j][1]<<endl;
			ans=0;
			ask(1,30);
			ans++;
			//cout<<val<<endl;
			anss=max(ans,anss);
			val=ans;
			ins();
		}
		cout<<anss<<endl;
		for(int i=1;i<=tot;i++)
		maxx[i]=son[i][0][0]=son[i][1][0]=son[i][0][1]=son[i][1][1]=0;
		tot=1;
	}
 	return 0;
}
```

能不能考虑复杂度正确的做法呢？继续盯着 D1 的代码看，发现：dfs 一个 $(0,0)$ 儿子必然 dfs 一个 $(1,1)$ 儿子，dfs 一个 $(0,1)$ 儿子必然 dfs 一个 $(1,0)$ 儿子！

那么，我们能不能根据这个，压缩四叉树，变成一个真正的 01Trie 呢？

直接根据 $i \operatorname{xor} a_i$ 建树，似乎是可行的，但是，除去相同的位，不同的位怎么办呢？

我们不仅仅维护子树 max，维护子树且下一位是每个二元组分别的 max 不就好了吗？

D2 code2：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int N=3e5+5;
int b[N],f[N],n;
int son[N*32][2],maxx[N*32][2][2];
int tot=1;
bool a[32][2];
int val;
void ins()
{
	int now=1;
	for(int i=30;i>=0;i--)
	{
		maxx[now][a[i][0]][a[i][1]]=max(maxx[now][a[i][0]][a[i][1]],val);
		if(!son[now][a[i][0]^a[i][1]]) son[now][a[i][0]^a[i][1]]=++tot;
		now=son[now][a[i][0]^a[i][1]];
	}
}
int ans;
void ask(int now,int dep)
{
//	if(maxx[now]<=ans) return;
	if(now==0) return;
	if(a[dep][0]==0&&a[dep][1]==0)
	{
		ans=max(ans,maxx[now][1][0]);
		ask(son[now][0],dep-1);
	}
	if(a[dep][0]==0&&a[dep][1]==1)
	{
		ans=max(ans,maxx[now][0][0]);
		ask(son[now][1],dep-1);
	}
	if(a[dep][0]==1&&a[dep][1]==0)
	{
		ans=max(ans,maxx[now][1][1]);
		ask(son[now][1],dep-1);
	}
	if(a[dep][0]==1&&a[dep][1]==1)
	{
		ans=max(ans,maxx[now][0][1]);
		ask(son[now][0],dep-1);
	}
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;n--;
		for(int i=0;i<=n;i++)
		cin>>b[i],f[i]=0;
		int anss=0;
		for(int i=0;i<=n;i++)
		{
			for(int j=30;j>=0;j--)
			a[j][0]=i&(1<<j),a[j][1]=b[i]&(1<<j);//,cout<<a[j][0]<<" "<<a[j][1]<<endl;
			ans=0;
			ask(1,30);
			ans++;
			//cout<<val<<endl;
			anss=max(ans,anss);
			val=ans;
			ins();
		}
		cout<<anss<<endl;
		for(int i=1;i<=tot;i++)
		son[i][0]=son[i][1]=maxx[i][0][0]=maxx[i][1][0]=maxx[i][0][1]=maxx[i][1][1]=0;
		tot=1;
	}
 	return 0;
}
```


---

## 作者：liangbowen (赞：9)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1720D2)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1720d2)

感觉 D1 和 D2 不是同一个难度档次的呀......

## 思路

设 $a_j\oplus i < a_i \oplus j$，这意味着数字 $a_j\oplus i$ 中，从个位起前 $k$ 位和 $a_i \oplus j$ 相同，之后第 $k+1$ 位就不同了。

两个不同下标的数有点难处理，考虑转化为同一个下标的数之间异或（例如 $a_i \oplus i$）。

发现，如果 $a_j\oplus i$ 和 $a_i\oplus j$ 中的第 $k$ 位相同，那么这些位在 $a_j \oplus j$ 和 $a_i \oplus i$ 也是**相同**的。

异或容易联想到 01 trie。考虑对 $a_i \oplus i$ 拆位，每一位都添加到 trie 里。

可以先计算这个数的贡献值，然后在 trie 中一边插入，一边用这个贡献值更新答案。

发现 $x \oplus y = 1$，肯定是 $x = 0, y = 1$ 或者 $x = 1, y = 0$。

所以，这一位有贡献，当且仅当两个数位的值不同。因此这时，我们就在 trie 的**另一边**计算贡献。

差不多就这样了。需要注意，应该先计算贡献，再插入。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#define space putchar(' ')
#define endl putchar('\n')
using namespace std;
typedef long long LL;
typedef long double LD;
void fastio()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
}
LL read()
{
	char op = getchar(); LL x = 0, f = 1;
	while (op < 48 || op > 57) {if (op == '-') f = -1; op = getchar();}
	while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar();
	return x * f;
}
void write(LL x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
const int N = 3e5 + 5;
int a[N], n;
struct Trie
{
	int ch[N * 31][2], dp[N * 31][2], cur;
	void init() //多测不清空，爆零两行泪！ 
	{
		for (int i = 0; i <= cur; i++)
			for (int j = 0; j <= 1; j++)
				ch[i][j] = dp[i][j] = 0;
		cur = 0;
	}
	#define bit(x) (bool)(x & (1 << j)) //求x二进制下的第j位
	#define upd(x, y) x = max(x, y) //x = max(x, y)
	
	int getDP(int i) //i表示下标 
	{
		int x = a[i] ^ i, pos = 0;
		int maxn = 0; //用于更新dp
		for (int j = 30; j >= 0; j--)
		{
			//printf("bit = %d.\n", bit(x));
			if (ch[pos][!bit(x)]) upd(maxn, dp[ch[pos][!bit(x)]][!bit(a[i])]); //数位不同，异或才有贡献
			if (ch[pos][bit(x)]) pos = ch[pos][bit(x)];
			else break; //有就继续往下upd maxn，没有就停止 
		}
		return maxn;
	}
	void insert(int i, int maxn) //使用maxn更新字典树与dp 
	{
		int x = a[i] ^ i, pos = 0;
		for (int j = 30; j >= 0; j--)
		{
			if (!ch[pos][bit(x)]) ch[pos][bit(x)] = ++cur; //字典树基本操作
			upd(dp[ch[pos][bit(x)]][bit(i)], maxn);
			pos = ch[pos][bit(x)];
		}
	}
}trie;
void solve()
{
	trie.init();
	int n = read();
	for (int i = 0; i < n; i++) a[i] = read(); //题目要求下标从0开始。 
	int maxn = -2147483647; //最终的答案
	for (int i = 0; i < n; i++)
	{
		int mx = trie.getDP(i) + 1;
		upd(maxn, mx);
		trie.insert(i, mx);
	}
	write(maxn), endl;
}
int main()
{
	int T = read();
	while (T--) solve();
	return 0;
}
```

希望能帮助到大家！

---

## 作者：EnofTaiPeople (赞：5)

讲的是 [CF1720D2](/problem/CF1720D2)。

简要题意：

有 $t$ 组数据，对于每组数据，给定 $n$ 和 $a_0,...,a_{n-1}$，均为自然数，求一个最长的自然数列 $b_i$，设其长度为 $m$ 需要满足 $0\le b_1<...<b_m<n$ 且 $\forall i\in[1,m),a_{b_i}\otimes b_{i+1}<a_{b_{i+1}}\otimes b_i$。

$t\le10^5,\sum n\le3\times10^5,0\le a_i\le 10^9$.

容易发现这是一个动态规划的模型，我们需要找到 $\max\limits_{j<i,a_j\otimes i<a_i\otimes j}f_j$，由于只有位运算，不难想到按位考虑。

从高到低考虑每一位，如果 $a_j\otimes i$ 和 $a_i\otimes j$ 在该位相同，这等价于 $a_j\otimes j$ 与 $a_i\otimes i$ 在该位相同，就继续下一位，否则一定是 $a_i\otimes j$ 在这一位为一。

将 $i$ 从小到大计算，在求出 $f_i$ 后，可以将 $a_i\otimes i$ 插入到一棵 $\text{01trie}$ 内，对于每一个节点记录 $i$ 在上一位为一的最大值，和为零的最大值。

查询就顺着 $a_i\otimes i$ 走 $\text{01trie}$，沿途处理相反方向的答案（即该位不同的情况）。

不到 1k 的 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
using ll=long long;
ll A,B,C,D;
ll T,n,m,f[N],a[N];
int t[N<<4][2],mx[N<<4][2],ans;
inline void Mx(int &x,int y){if(x<y)x=y;}
int cnt,rt,v1,v2,v3,nw;
void ins(int &x,int w=31){
	if(!x)x=++cnt;
	int p=v1^v2;
	Mx(mx[x][(v2>>w)&1],v3);
	if(w--)ins(t[x][(p>>w)&1],w);
}
void qry(int &x,int w=31){
	if(x&&w--){
		int k=((v1^v2)>>w)&1;
		Mx(nw,mx[t[x][!k]][((v1>>w)&1)^1]);
		qry(t[x][k],w);
	}
}
int main(){
	int i,j,k,l,md,r;
	ios::sync_with_stdio(false);
	cin>>T;while(T--){
		for(i=1;i<=cnt;++i)
			mx[i][0]=mx[i][1]=t[i][0]=t[i][1]=0;
		cin>>n,ans=cnt=rt=0;
		for(i=1;i<=n;++i)cin>>a[i];
		for(i=1;i<=n;++i){
			v1=a[i],v2=i-1,nw=0,qry(rt);
			Mx(ans,v3=f[i]=nw+1),ins(rt);
		}printf("%d\n",ans);
	}return 0;
}
```

---

## 作者：Leasier (赞：4)

Update on 2022.8.19：感谢 @[xianggl](https://www.luogu.com.cn/user/201278)。

该题 easy version 中 $0 \leq a_i \leq 200$ 的好条件没有了（悲）。

注意到异或运算是可以拆位的，我们不妨逐位考虑。

对于 $i, a_i$ 和 $j, a_j$，若 $i \operatorname{xor} a_j$ 与 $j \operatorname{xor} a_i$ 在前 $k - 1$ 位完全相同，在第 $k$ 位恰好出现了前者小于后者的情况，则我们可以得到：

- $i \operatorname{xor} a_i$ 在前 $k - 1$ 位也与 $j \operatorname{xor} a_j$ 完全相同。
- 设 $i$ 的第 $k$ 位为 $u$，$a_i$ 的第 $k$ 位为 $v$，$j$ 的第 $k$ 位为 $w$，$a_j$ 的第 $k$ 位为 $x$，则 $u \operatorname{xor} x = 0 < 1 = v \operatorname{xor} w$。进一步地，我们可以得到 $w = v \operatorname{xor} 1$，$x = u$。

由上述第一个性质，对于前面相等的部分，是否满足条件只与 $i \operatorname{xor} a_i, j \operatorname{xor} a_j$ 有关；由上述第二个性质，假如枚举上述的第 $k$ 位，我们可以 $O(1)$ 求出 $j, a_j$ 的第 $k$ 位。

于是可以想到把 $i \operatorname{xor} a_i$ 扔进一棵 01-Trie 来维护，在树上的每个节点存下 $f_{pos, u, v}$ 表示在 $pos$ 节点，$j$ 的当前位为 $u$，$a_j$ 的当前位为 $v$ 对应的 $dp_j$ 的最大值，每次沿着 $i \operatorname{xor} a_i$ 的位从高到低遍历，将答案与 $f_{pos, u, v \operatorname{xor} 1}$ 取 $\max$，最后再沿着该路径更新 $dp_i$ 的答案即可。时间复杂度为 $O(\sum n \log \max(n, \max a_i))$。

代码中的 $i$ 是从 $1$ 开始的。

代码：
```cpp
#include <stdio.h>

const int N = 9e6 + 7, M = 1 + 1, K = 29;
int cnt, root;
int son[N][M], max_val[N][M][M];

inline int new_node(){
	cnt++;
	son[cnt][0] = son[cnt][1] = max_val[cnt][0][0] = max_val[cnt][0][1] = max_val[cnt][1][0] = max_val[cnt][1][1] = 0;
	return cnt;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

inline int insert(int pos, int val){
	int ans = 0;
	for (int i = K, j = root; i >= 0; i--){
		int u = (pos - 1) >> i & 1, v = val >> i & 1, ch = u ^ v;
		ans = max(ans, max_val[j][v ^ 1][u]);
		if (son[j][ch] == 0) break;
		j = son[j][ch];
	}
	ans++;
	for (int i = K, j = root; i >= 0; i--){
		int u = (pos - 1) >> i & 1, v = val >> i & 1, ch = u ^ v;
		max_val[j][u][v] = max(max_val[j][u][v], ans);
		if (son[j][ch] == 0) son[j][ch] = new_node();
		j = son[j][ch];
	}
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, ans = 0;
		scanf("%d", &n);
		cnt = 0;
		root = new_node();
		for (int j = 1; j <= n; j++){
			int a;
			scanf("%d", &a);
			ans = max(ans, insert(j, a));
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：huangkx (赞：1)

## 思路

考虑用求最长不下降子序列的 $\texttt {DP}$ 方法求解。设 $f _ i$ 为以 $a _ i$ 结尾的最长美丽子序列的长度，则 $f _ i = \max f _ j + 1$，其中 $j < i , a _ j \operatorname { xor } i < a _ i \operatorname { xor } j$。考虑优化上述算法：

$a _ j \operatorname { xor } i < a _ i \operatorname { xor } j$ 成立的条件是把式子两边的值拆成二进制后，它们有一段相同前缀，而它们的这个前缀的后一位的值分别是 $0$ 和 $1$。

因为式子两边前缀相同可以看成 $a _ j \operatorname { xor } j$ 和 $a _ i \operatorname { xor } i$ 前缀相同，所以可以枚举 $a _ i \operatorname { xor } i$ 的前缀，并找到与它的相同前缀是这个前缀的 $a _ j \operatorname { xor } j$。确定相同前缀后，就可以确定相同前缀的后一位是第几位，又因为当前的 $a _ i$ 和 $i$ 是确定的，而 $a _ j \operatorname { xor } i$ 的这一位的值为 $0$，$a _ i \operatorname { xor } j$ 的这一位的值为 $1$，所以可以确定 $a _ j$ 和 $j$ 的这一位的值，从而找到满足条件的 $a _ j$ 和 $j$。找到满足条件的 $j$ 后，就可以用 $f _ j$ 更新 $f _ i$ 了。

用 $\texttt {01-Trie}$ 实现上述过程即可。

时间复杂度为 $\mathcal { O } ( n \log ( \max a _ i ) )$。

## 代码

```c++
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5;
int t, n, ans;
int a[N + 5], f[N + 5];
int cld[32 * N + 5][2], mx[32 * N + 5][2], idx;
int Query(int i)
{
	int ans = 0;
	for(int j = 30, x = !! ((a[i] ^ (i - 1)) & (1 << j)), y = !! (a[i] & (1 << j)), v = cld[1][! x], u = cld[1][x]; ~ (j --) && ! u ? ans = max(ans, mx[v][! y]), 0 : 1;
	x = !! ((a[i] ^ (i - 1)) & (1 << j)), y = !! (a[i] & (1 << j)), v = cld[u][! x], u = cld[u][x]) ans = max(ans, mx[v][! y]);
	return ans;
}
void Insert(int i)
{
	for(int j = 30, x = !! ((a[i] ^ (i - 1)) & (1 << j)), y = !! ((i - 1) & (1 << j)), u = (! cld[1][x]) ? (cld[1][x] = ++ idx) : cld[1][x]; ~ (j --);
	x = !! ((a[i] ^ (i - 1)) & (1 << j)), y = !! ((i - 1) & (1 << j)), u = (! cld[u][x]) ? (cld[u][x] = ++ idx) : cld[u][x]) mx[u][y] = max(mx[u][y], f[i]);
}
int main()
{
	scanf("%d", & t);
	while(t --){
		scanf("%d", & n);
		for(int i = 1; i <= n; i ++) scanf("%d", & a[i]);
		while(idx --) cld[idx][0] = cld[idx][1] = mx[idx][0] = mx[idx][1] = 0;
		ans = 0, idx = 1;
		for(int i = 1; i <= n; i ++){
			f[i] = Query(i) + 1;
			Insert(i);
			ans = max(ans, f[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

## 闲话

为了减小常数，这份代码的码风可能有点奇怪。

截止 2022.10.24，这份代码在洛谷的提交记录中运行时间排名第二，运行时间为 $280 ms$，排名第一的是一份运行时间只有 $0 ms$ 的代码。

2022.10.24

2022.10.25 修改了一个错别字

---

## 作者：jrxxx (赞：1)

## 前置知识

$\text{01-trie}$。

## 题意

选出 $\{a_i\}$ 的一个最长子序列满足：

对于子序列中相邻两个位置 $i,j(j<i)$，$a_j\oplus i<a_i\oplus j$ 。

输出最大长度。

$(1\le n\le 3\times 10^5)$

## 思路

- **easy version** ：$a_i\le 200$

首先我们有一个 $O(n^2)$ 的 $dp$：$f_i=\max(f_j)+1\ (j<i\land a_j\oplus i<a_i\oplus j)$

因为异或满足性质：$|a-b|\le a\oplus b\le a+b$ 

故 $i-a_j\le a_j\oplus i<a_i\oplus j\le j+a_i$

则有 $i-a_j<j+a_i \iff i-j<a_j+a_i\le 400$。

因此，只需要枚举到 $400$ 个就够了，复杂度 $O(400n)$。

- **hard version**

$\text{trick}$ 几乎完全一样： [P7502](https://www.luogu.com.cn/problem/P7502)

对于一个 $i$，计算答案需要查询满足条件的 $j$ 中 $f_j$ 的 $\max$。

位运算经典思路：拆位。

将 $(a_i,i)$ 两数的二进制位分别拆开，可以得到 $(0,0),(0,1),(1,0),(1,1)$ $4$ 种。

对于 $4\times 4$ 种组合，根据 $a_j\oplus i<a_i\oplus j$ 的条件，定义比较函数 。

|$j / i$  | $(0,0)$ | $(0,1)$ | $(1,0)$ | $(1,1)$ |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $(0,0)$ | $=$ | $>$ | $<$ | $=$ |
| $(0,1)$ | $<$ | $=$ | $=$ | $>$ |
| $(1,0)$ | $>$ | $=$ | $=$ | $<$
| $(1,1)$ | $=$ | $<$ | $>$ | $=$ |

那么对于一个 $(a_i,i)$ 满足条件的 $(a_j,j)$ $(j<i)$ 应该满足从高位开始，有若干位相等后有一个 $(b_{a_j},b_j)<(b_{a_i},b_i)$。($b$ 表示拆位出来的值)（注意理解这里的相等不是相同，而是上表中的"$=$"）

在魔改的 $4$ 叉 $\text{01-trie}$ 上维护 $\max$，查询时直接往相等的位置走就行了，每走一步查一下在这个位置上比 $(b_{a_i},b_i)$ 小的答案。

完了吗？发现一个很致命的事情——相等的不唯一，这意味着每次查询并不是走了一条链，复杂度无法保证。

不过这也很好办，因为我们并不在乎走过的都是什么，我们只在乎走过的与要查询的相等。于是，我们可以在维护 $\max$ 时将 $4$ 个儿子分开，但是在树形上将相等的 $(0,0)(1,1)$ 和 $(0,1)(1,0)$ 分别合并起来，这样每次只向一个儿子递归，复杂度就对了。（具体可以看代码，很清晰的）

复杂度：$O(n\log V)$。

## 代码

```cpp
#include<bits/stdc++.h>
const int op[4]={1,3,0,2};//预先存好小于的位置
const int N=3e5+7,D=31;
int f[N];
namespace Trie
{
	struct node{int ch[2],val[4];} tr[N*D];//儿子建2个，但val存4个
	int tot=1;
	void insert(int x,int y,int z)
	{
		int p=1;
		for(int i=D,c,d;~i;--i)
		{
			c=(((x>>i)&1)<<1)|((y>>i)&1);//这一位上拆出来的具体值
			d=((x>>i)&1)^((y>>i)&1);//该向哪个儿子走
			tr[p].val[c]=std::max(tr[p].val[c],z);
			if(!tr[p].ch[d]) tr[p].ch[d]=++tot;
			p=tr[p].ch[d];
 		}
	}
	int query(int x,int y)
	{
		int res=0,p=1;
		for(int i=D,c,d;~i;--i)
		{
			c=(((x>>i)&1)<<1)|((y>>i)&1);
			d=((x>>i)&1)^((y>>i)&1);
			res=std::max(res,tr[p].val[op[c]]);//op[c]-小于c的是哪个
			p=tr[p].ch[d];
		}
		return res+1;
	}
}
int main()
{
	std::ios::sync_with_stdio(0),std::cin.tie(0);
	int T,n,i,x;
	for(std::cin>>T;T--;)
	{
		Trie::tr[1].ch[0]=0;//多测要清空
		Trie::tr[1].ch[1]=0;
		std::cin>>n;
		for(i=0;i<n;++i)//注意从0开始
		{
			std::cin>>x;
			f[i]=Trie::query(x,i);
			Trie::insert(x,i,f[i]);
		}
		std::cout<<*std::max_element(f,f+n)<<'\n';
	}
	return 0;
}
```

---

## 作者：Yansuan_HCl (赞：0)

处理异或问题有三大工具：拆位、01-Trie、线性基。

题目中的不等式并没有很好的处理方法。拆位比较，发现：对于任意 $a<b$，存在一个极小的 $k$ 满足其 $(k,31]$ 位相同，第 $k$ 位上 $a<b$。

枚举 $k$，不等式就被转化为等式。异或等式可以**两边同时异或**进行**移项**。

记 $x_i$ 表示 $x$ 的第 $i$ 位。则有 $\forall i>k, (a_{p_1})_i \oplus (p_2)_i=(a_{p_2})_i \oplus (p_1)_i$。移项，得 $(a_{p_1})_i \oplus (p_1)_i = (a_{p_2})_i \oplus (p_2)_i$。这样 $p_1$ 和 $p_2$ 就被**分离开**了。


可以把 $a_p \oplus p$ 插入到 01-Trie 中，以此优化 dp. 每个 Trie 节点需要保存 $a_i$ 是否为 $1$ 以钦定第 $k$ 位的大小关系。

```cpp
const int N = 300005;
struct Node { int son[2], v[2];} tr[N << 5];
int ptr;

void insert(int x, int j, int v, int p) {
    for (int i = 30; i + 1; --i) {
        if (!tr[p].son[((x ^ j) >> i) & 1])
            tr[p].son[((x ^ j) >> i) & 1] = ++ptr;
        p = tr[p].son[((x ^ j) >> i) & 1];
        tr[p].v[(x >> i) & 1] = max(tr[p].v[(x >> i) & 1], v);
    }
}
void clear(int p) {
    if (!p) return;
    clear(tr[p].son[0]);
    clear(tr[p].son[1]);
    tr[p].son[0] = tr[p].son[1] = tr[p].v[0] = tr[p].v[1] = 0;
}

int n, a[N];

void solve() {
    int ans = 0;
    for (int i = n - 1; i + 1; --i) {
        int p = 1, f = 0;
        D (k, 30, 0) { // [30, k) 位相等
            int api = (a[i] >> k) & 1, pi = (i >> k) & 1;
            // a_p,i ^ q_i = a_q,i ^ p_i
            // a_p,i ^ p_i = q_q,i ^ q_i
            // a_p,i ^ q_i ^ 1 = a_q,i ^ p_i
            // a_p,i ^ p_i ^ 1 = a_q,i ^ q_i
            f = max(f, tr[tr[p].son[api ^ pi ^ 1]].v[pi ^ 1]);
            p = tr[p].son[api ^ pi];
        }
        ++f;
        ans = max(ans, f);
        insert(a[i], i, f, 1);
    }
    printf("%u\n", ans);
}

int main() {    
    int T; rd(T);
    while (T--) {
        clear(1);
        ptr = 1;
        rd(n);
        U (i, 0, n - 1) rd(a[i]);
        solve();
    }
}
```

---

## 作者：Lates (赞：0)

有暴力的 dp

$$f_i = \max_{i \ \text{xor} \ a_j < j \ \text{xo}r \ a_i}\{f_j + 1\}$$

---

D1 中满足 $a\le 200$，于是可以得到一个明显的 $j > i-400$ 的限制，因为 $\text{xor}$ 至多有 $200$ 的正或负增量。

---

D2 中，$a \le 10^9$。按位从高到低考虑，则以上不等式表明，左右式一段前缀 $k$ 位都相同，第 $k+1$ 位，满足 $(i \ \text{xor} \ a_j)_{k+1} = 0$, ${(j \ \text{xor} \ a_{i})}_{k+1} = 1$。 那么前面 $k$ 位满足都相等，那么 $i\ \text{xor} \ a_i = j \ \text{xor} \ a_j$。

那可以把算完 dp 值的位置 $i\ \text{xor} \ a_i$ 丢到 01trie 上，那么更新的时候，需要求 按自己的走，下一个不是自己应该走的子树，满足上面那个 $k+1$ 位的条件的最大值。

那么记个 $f[x][0/1][0/1]$ 表示 trie 树上 $x$ 子树内，$a[i]$ 的第 $k$ 位为 $0 / 1$，和 $i$ 的 $k$ 位为 $0 / 1$。 $k$ 表示 $x$ 点是第几位。 这个插入时容易维护。

时间复杂度 $\mathcal{O(n\log a)}$。

---

## 作者：Daidly (赞：0)

[Codeforces Round #815 (Div. 2) 全场题解以及更好的阅读体验](https://www.cnblogs.com/Daidly/p/16607199.html)

我们无法再分块 $dp$ 了。

考虑解决异或问题最常见的三种方法：按位讨论，字典树，线性基。这里考虑字典树，按位讨论。

观察这个式子 $a_j\oplus i<a_i\oplus j$，我们发现两者从最高位向下一直相等直到第 $k$ 位才不同，而这个不同，一定是：$a_j\oplus i$ 的第 $k$ 位为 $0$，$a_i\oplus j$ 的第 $k$ 位为 $1$。

相等？异或虽然不能在不等式里移项，但可以在等式中移项。

所以有：从最高位到第 $k$ 位，$a_j\oplus i=a_i\oplus j$，等价于 $a_j\oplus j=a_i\oplus i$。

列出满足$a_j\oplus i$ 第 $k$ 位为 $0$，$a_i\oplus j$ 第 $k$ 位为 $1$ 的四种有关于 $a_j,i,a_i,j$ 在第 $k$ 位的情况：

 | $a_j$ | $i$  | $a_i$ | $j$  |
 | :---: | :--: | :---: | :--: |
 |  $0$  | $0$  |  $0$  | $1$  |
 |  $1$  | $1$  |  $0$  | $1$  |
 |  $0$  | $0$  |  $1$  | $0$  |
 |  $1$  | $1$  |  $1$  | $0$  |

可以发现，$a_i\oplus i$ 正好与 $a_j\oplus j$ 相反，而此时正好满足 $a_j\oplus i<a_i\oplus j$。  

结合上面两种发现，我们考虑在字典树中插入 $a_i\oplus i$。

我们记 $nxt[p][0/1]$ 为节点 $p$ 的 $0/1$ 儿子的编号。既然想用字典树优化 $dp$ 的转移，就要统计节点所在子树内的 $f[j]$ 最大值，所以我们插入的时候加上一个参数 $i$ 以便计算子树内 $f$ 最大值。

而想要满足不等式，除了让两者相反，还必须让 $a_i,j$ 相反，要不然第 $k$ 位 $a_j=1,i=0,a_i=0,j=0$ 虽然相反，却无法保证小于。

所以我们在记录节点子树内最大值时还要记录经过该点的数在这一位上的 $0/1$ 值。

记 $g[p][0/1]$ 为插入的 $a_i\oplus i$ 经过 $p$ 点后，以 $p$ 为根，$i$ 在此位上为 $0/1$ 时的子树内最大 $f$ 值。

寻找时我们将 $a_i\oplus i$ 的第 $k$ 位取反并且满足 $i$ 与此点表示的 $a_j$ 相反此位相反的 $g$ 值取最大即可，可以看看代码。

每一次先通过字典树寻找最优的 $j$，再插入 $a_i\oplus i$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
 
void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}
 
const int N=3e5+5;
int t,n,a[N],f[N],ans;
int nxt[N*31][2],g[N*31][2],cnt;
 
void insert(int x,int k){
	int p=0;
	for(int i=29;i>=0;--i){
		if(!nxt[p][x>>i&1])nxt[p][x>>i&1]=++cnt;
		p=nxt[p][x>>i&1];
		g[p][k>>i&1]=max(g[p][k>>i&1],f[k]);
	}
}
 
int find(int x,int k){
	int p=0,ans=0;
	for(int i=29;i>=0;--i){
		ans=max(ans,g[nxt[p][!(x>>i&1)]][!(k>>i&1)]);
		p=nxt[p][x>>i&1];
		if(!p)break;
	}
	return ans; 
} 
 
int main(){
	t=read();
	while(t--){
		n=read(),ans=cnt=0;
		for(int i=0;i<=n*30;++i)nxt[i][0]=nxt[i][1]=g[i][0]=g[i][1]=0;
		for(int i=0;i<n;++i)a[i]=read();
		for(int i=0;i<n;++i){
			f[i]=find(a[i]^i,a[i])+1;
			insert(a[i]^i,i);
			ans=max(ans,f[i]);
		}
		print(ans),puts("");
	}
	return 0;
}
```

---

## 作者：cc0000 (赞：0)

## 题意

给出一段序列 $a_1,a_2,....a_n$ ，要求取出一段 **由 a 的下标** 构成的上升子序列 $b$，使得对任意的 $p$ ,都有 $a_{b_p} \bigoplus b_{p+1} < a_{b_{p+1}} \bigoplus b_p$ ,求 $b$ 是最长长度。
## 题解

DP 优化的题

暴力 $n^2$ 的是 $f_{i}$ 表示 $b$ 数组以 $i$ 为结尾的最长长度，$f_i=max\{f_j\}+1 ,(a_j \bigoplus i < a_i \bigoplus j)$

显然不行。

异或的题当然要拆位分开算啦

设 $u,v,w,p$ 分别为 $i,a_i,j,a_j$ 的二进制那几位对应的数，而如果前几位都是相等的，那 $ v\bigoplus u =w \bigoplus p$ （自己再分类讨论一下就好）。

假如对于一对 $i,j$ , 它们二进制的前几位都是相同的，如果要在这一位决定能否转移出答案，那必然满足 $j \bigoplus a_i = 0< 1 =i\bigoplus a_j$，（这里的都是指对于某一二进制的位数），也就是说 $p\bigoplus v =0 < 1 = w \bigoplus u$,也就是说 $p=v,w\not = u$

我们可以考虑用 $i \bigoplus a_i$ 来表示转移的方式。所以我们建出一颗 01 trie ，用当前位的 $i \bigoplus a_i$ 作为 0/1 的路径，同时在节点上记录个 $f_{pos,j,k}$，表示在节点 $pos$ 上，$i$ 的二进制位为 $j$ ,$a_i$ 的二进制位为 $k$，的最大答案。

在插入的过程中寻找答案。当找到 $pos$时，设当前位插入的数值 $i$ 的二进制位 为 $u$, $a_i$ 的二进制位为 $v$，用 $f_{pos,v,u\bigoplus 1}$(上面推了为什么)更新答案。找完答案后就更新沿途对应位置的 $f$ 值就好啦

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
const int maxn=300002;
const int maxm=4000002;
int a[maxn],n,rt;
int f[maxm][3][3],ch[maxm][3],tot;
int newnode()
{
	tot++;
	f[tot][0][0]=f[tot][0][1]=f[tot][1][0]=f[tot][1][1]=ch[tot][0]=ch[tot][1]=0;
	return tot;
}
int insert(int idx,int x)
{
	int p=rt;int ans=0;
	for(int i=30;i>=0;i--)
	{
		int u=idx>>i&1,v=x>>i&1,w=u^v;
		ans=max(ans,f[p][v^1][u]);
		if(!ch[p][w])
			break;
		p=ch[p][w];
	}
	ans++;
	p=rt;
	for(int i=30;i>=0;i--)
	{
		int u=idx>>i&1,v=x>>i&1,w=u^v;
		f[p][u][v]=max(ans,f[p][u][v]);
		if(!ch[p][w])
			ch[p][w]=newnode();
		p=ch[p][w];
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		tot=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		rt=newnode();
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			ans=max(ans,insert(i-1,a[i]));
		}
		printf("%d\n",ans);
	}	
}
```

---

## 作者：滑蒻稽 (赞：0)


### Des

给定 $n$ 个整数 $a_0,a_1,\dots,a_{n-1}$。称一个递增的下标序列 $b_0,b_1,\dots,b_{m-1}$ 是美丽的，当其满足对于 $0\le p<m-1$，$a[b_{p}]\oplus b_{p+1}< a[b_{p+1}]\oplus b_p$。求最长的美丽的下标序列的长度。

$n\le 3\times 10^{5}$，$a_{i}\le 10^9$。

### Sol

先考虑本题的弱化版 $a_{i} \le 200$ 的情况。朴素的 DP 是 $f(i)=\max\limits_{j=0,a_{j}\oplus i<a_{i}\oplus j}^{i-1}(f(j)+1)$。但 $a_i$ 异或上下标 $j$，最多会改变 $j$ 最低的 8 位。而 $a_{i}\oplus j$ 与 $a_{j}\oplus i$ 在比较时，如果 $j$ 在某个高位就比 $i$ 小，那不管 $a_i$ 是什么都没有意义了。不难证明当 $j<i-256$ 的时候，$a_{j}\oplus i>a_{i}\oplus j$ 必然成立（因为从低数第 9 位及以上的位必然更小了）。

对于 $a_{i}\le 10^9$，我们似乎应该用其他的方法优化这个 DP。一般来说这个时候应该上一个数据结构，存点值然后查一下（比如最长上升子序列这里可以用线段树），但这题的条件 $a_j \oplus i<a_i\oplus j$ 里面的 $i$ 在式子两边都有，看起来很难搞。

我们尝试转化条件，把和 $i$ 有关的东西都移到式子一边。这个时候直接上位运算的基操，即一位一位的考虑。这道题要按位考虑的话，大概是在 trie 树上以某个值下降，在前 $k$ 位相同的情况下考虑 $k+1$ 位更小的答案。这样做复杂度大概会多个 $\log V$，所以应该可以拆，那么我们只需要具体的操作即可。

在 trie 树上下降时要求 $a_j\oplus i=a_i\oplus j$。分类讨论考虑如何才能做到（下面分类讨论中的等号仅表示一位上的值）：

1. $a_i=0,i=0$，必有 $j=0,a_j=0$ 或 $j=1,a_j=1$。
2. $a_i=0,i=1$，必有 $j=1,a_j=0$ 或 $j=0,a_j=1$。
3. $a_i=1,i=0$，必有 $j=0,a_j=1$ 或 $j=1,a_j=0$。
4. $a_i=1,i=1$，必有 $j=0,a_j=0$ 或 $j=1,a_j=1$。

归纳发现必须满足 $a_i\oplus i=a_j\oplus j$。

在 trie 树上查询时，要满足 $a_j \oplus i<a_i\oplus j$。分类讨论考虑如何才能做到：

1. $a_i=0,i=0$，要满足 $a_j \oplus i<a_i\oplus j$ 必有 $j=1,a_j=0$.
2. $a_i=0,i=1$，要满足 $a_j \oplus i<a_i\oplus j$ 必有 $j=1,a_j=1$。
3. $a_i=1,i=0$，要满足 $a_j \oplus i<a_i\oplus j$ 必有 $j=0,a_j=0$。
4. $a_i=1,i=1$，要满足 $a_j \oplus i<a_i\oplus j$ 必有 $j=0,a_j=1$。

归纳发现 $a_i$  和 $j$ 相反，$i$ 和 $a_j$ 相同，完全可以在 trie 树节点上记录 $a_i$ 和 $i$ 四种情况下的答案。但因为我们下降时用到了 $a_i\oplus i$，所以可以尝试利用已有的 $a_i\oplus i$ 省一点力。发现必有 $a_i\oplus i$ 与 $a_j\oplus j$ 相反，所以在 trie 树上记录两个值就可以了（代码里选择记录 $i$ 的值）。

### Code

```cpp
// Problem: D1. Xor-Subsequence (easy version)
// Contest: Codeforces - Codeforces Round #815 (Div. 2)
// URL: https://codeforces.com/contest/1720/problem/D1
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Created: 2022-08-19 08:30:07

#include <bits/stdc++.h>

using namespace std;
namespace FI {
	#define getchar() (S == T && (T = (S = B) + fread(B, 1, 1 << 16, stdin), S == T) ? EOF : *S++)
	char B[1 << 16], *S = B, *T = B;
	template<typename Tp> inline void read(Tp &o) {
		o = 0; bool s = 0; char c = getchar();
		while(c > '9' || c < '0') s |= c == '-', c = getchar();
		while(c >= '0' && c <= '9') o = o * 10 + c - '0', c = getchar();
		if(s) o = -o;
	}
} using FI::read;
const int N = 3e5 + 5;
int T, n, a[N];
int node_cnt, rt;
struct node { // 存 a_i ^ i 建成的 trie 树
	int c[2]; // 一个节点的两个儿子
	int a[2]; // a_i 这一位是 0/1 情况下的答案
} c[N * 30];
inline int new_node() {
	++node_cnt;
	c[node_cnt].c[0] = c[node_cnt].c[1] = 0;
	c[node_cnt].a[0] = c[node_cnt].a[1] = 0;
	return node_cnt;
}
inline void cmax(int &a, int b) { if(a < b) a = b; }
inline int gb(int i, int j) { return (i >> j) & 1;} // getbit

void Main() {
	read(n);
	node_cnt = 0, rt = new_node();
	int ans = 0;
	for(int i = 0; i < n; i++) {
		read(a[i]);
		int p = rt, v = a[i] ^ i, mx = 0;
		for(int j = 30; j >= 0; j--) {
			if(c[p].c[gb(v, j) ^ 1])
				cmax(mx, c[c[p].c[gb(v, j) ^ 1]].a[gb(a[i], j) ^ 1]);
			p = c[p].c[gb(v, j)];
			if(!p) break;
		}
		ans = max(ans, mx + 1);
		p = rt;
		for(int j = 30; j >= 0; j--) {
			if(!c[p].c[gb(v, j)]) c[p].c[gb(v, j)] = new_node();
			cmax(c[c[p].c[gb(v, j)]].a[gb(i, j)], mx + 1);
			p = c[p].c[gb(v, j)];
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	for(read(T); T; T--) Main();
	
	return 0;
}
```

---

## 作者：UperFicial (赞：0)

$\text{Update 8.26}$：交错题了。

解决关键在于异或的性质：$x-y\le x\operatorname{xor} y\le x+y$。

那么，序列中两点 $i,j(i<j)$ 匹配的条件 $a_i\operatorname{xor} j<a_j\operatorname{xor} i$ 可以转化为 $j-a_i<a_j+i$。

注意到值域很小，那么可以把 $a_i$ 和 $a_j$ 放到一起，$i$ 相对于 $j$ 的范围也就可以得出，即：$j-i<a_i+a_j$。

注意到值域 $0\le V\le 200$，所以 $a_i+a_j\le  400$。

由此我们得到 $j-i<400$ 即 $i>j-400$。

显然我们确定了一个 $j$ 后 $i$ 的范围也随之确定：$[\max\{j-400,0\},j)$。复杂度为 $\Theta(400n)$，可以通过本题。



---

