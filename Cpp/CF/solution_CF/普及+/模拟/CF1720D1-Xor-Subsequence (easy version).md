# Xor-Subsequence (easy version)

## 题目描述

这是此问题的简单版本。简单版本与困难版本的唯一区别在于：在简单版本中，$a_i\leq 200$。

给你一个长为 $n$ 的整数数组 $a$，从 $0$ 开始编号。

一个长为 $m$ ，从 $0$ 开始编号的整数数组 $b$ 是数组 $a$ 的 subsequence，当且仅当 $0\leq b_0<b_1<\dots<b_{m-1}<n$。

若 $b$ 是 $a$ 的 beautiful subsequence，当且仅当满足以下条件：

+ $b$ 是 $a$ 的 subsequence；
+ $\forall p\in[0,m)\cap\textbf{N},a_{b_p}\oplus b_{p+1}<a_{b_{p+1}}\oplus b_p$。

其中 $\oplus$ 表示位运算中的异或运算。

现在，你需要求出最长的 beautiful subsequence 有多长。

## 说明/提示

$1\leq T\leq 10^5,2\leq n\leq 3\times 10^5,0\leq a_i\leq 200,\sum n\leq 3\times 10^5$。

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

## 作者：liangbowen (赞：25)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/CF1720D1)

[更好的阅读体验？](https://liangbowen.blog.luogu.org/solution-cf1720d1)

有点思维难度的 DP 优化题。

## 小知识

在做这道题之前，你需要知道：$x - y, y - x
\le x \oplus y \le x + y$。

证明非常简单，利用异或的性质即可。

## 思路

容易想到类似 LIS 的东西。设 $dp_i$ 表示以 $i$ 下标元素结尾，最长子序列长度，有：

$$dp_i = \max\limits_{j=1}^{i-1}\left[a_j \oplus i < a_i \oplus j\right] \{dp_j + 1\}$$

注意下标，如题从 $0$ 开始。

然后我们得到一个 $O(n^2)$ 的 DP。题目告诉我们 $a_i$ 较小，必定有端倪。于是尝试对 $a_j \oplus i < a_i \oplus j$ 化简。


根据上面的引理，可得：$i - a_j < a_i + j$。进而得 $i - j < a_i + a_j \le 200 + 200 = 400$。

进一步地，$i- j \le 400$ 可以得出 $j \ge i - 400$。

故，枚举 $i$ 后，$j$ 只需枚举 $\max\{0, i - 400\}$ 到 $(i - 1)$ 就够了。

时间复杂度 $O(k n)$，其中 $k$ 为 $400$。$(3 \times 10^5) \times 400 = 12 \times 10^7 = 1.2 \times 10^8$。

有点大，但其余常数极小，并且没有极限数据，因此能过。

## 完整代码

```cpp
#include <iostream>
#include <cstdio>
#define endl putchar('\n')
using namespace std;
int read()
{
	char op = getchar(); int x = 0, f = 1;
	while (op < 48 || op > 57) {if (op == '-') f = -1; op = getchar();}
	while (48 <= op && op <= 57) x = (x << 1) + (x << 3) + (op ^ 48), op = getchar();
	return x * f;
}
void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48); 
}
const int N = 3e5 + 5;
int a[N], dp[N];
void solve()
{
	int n = read(), maxn = 0;
	for (int i = 0; i < n; i++) a[i] = read(), dp[i] = 1; //注意要按题目的下标来 
	for (int i = 0; i < n; maxn = max(maxn, dp[i]), i++) //稍微严重的压行，意思是 maxn = max{ dp[i] } 
		for (int j = max(i - 400, 0); j < i; j++)  
			if ( (a[j] ^ i) < (a[i] ^ j) ) //需要注意，小于号两边的异或运算都要加括号，避免优先级错误
				dp[i] = max(dp[i], dp[j] + 1);
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

## 作者：Nephren_Sakura (赞：10)

神仙 dp 题。

首先可以设出一个状态：

$dp_i$ 表示以 $i$ 结尾的最长美丽子序列的长度。

那么 $dp_i=\max\limits_{j=1}^{i-1}dp_j|a_j \oplus i < a_i \oplus j$

最后取 $\max\limits_{i=1}^ndp_i$ 即可，复杂度 $O(n^2)$

考虑优化 $dp$

我们发现题目中有一个 $a_i \le 200$ 的限制没有用上。

我们发现，$a_i$ 的二进制表示中最多只有八位。

所以 $a$ 数组最多影响 $i$ 的低八位。

又因为 $i>j,a_j \oplus i < a_i \oplus j$

所以满足条件的 $i,j$ 的除低八位以外的所有位数必定相同。

那么对于所有的 $i$，只需要枚举到 $i-256$ 即可。

时间复杂度 $O(256 \times n)$。~~省略小常数得到 O(n)~~

下贴代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[1000005],dp[1000005];
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=0; i<n; i++)
            cin>>a[i],dp[i]=1;
        dp[0]=1;
        for(int i=1; i<n; i++)
            for(int j=i-1; j>=0&&j>=i-256; j--)
                if((a[j]^i)<(a[i]^j))
                    dp[i]=max(dp[i],dp[j]+1);
        int maxi=-1e18;
        for(int i=0; i<n; i++)
            maxi=max(maxi,dp[i]);
        cout<<maxi<<endl;
    }
    return 0;
}
```

---

## 作者：Blunt_Feeling (赞：9)

## CF1720D1 Xor-Subsequence (easy version) 题解

先考虑一个简单的 $n^2$ DP，设 $f(i)$ 表示以 $i$ 结尾的、最长的、满足条件的子序列的长度。容易想到转移：

$$f(i)=\max_{j=0}^{i-1} f(j)[a_j\oplus i<a_i\oplus j]+1$$

easy version 保证 $a_i<200$，而 $i$ 和 $j$ 都是 $3\cdot 10^5$ 级别。接下来考虑优化这个式子。

根据按位异或的性质，有

$$
\begin{cases}
i-a_j\le i\oplus a_j \\
j\oplus a_i\le j+a_i
\end{cases}
$$

带入原式，可得

$$a_j\oplus i<a_i\oplus j$$

$$\Rightarrow i-a_j<j+a_i$$

$$\Leftrightarrow i-j<a_i+a_j<400$$

于是 $j$ 的枚举范围可以缩小到 $\max\{0,i-400\}$，复杂度减到 $\mathcal{O}(400n)$，想到这差不多就可以 AC 这道题了。

以上为本蒟蒻自己的推导过程，可能与官方题解有所出入，如有错误恳请指正。

### Code
```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int maxn=300050;
int T,n,a[maxn],f[maxn],ans;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		For(i,0,n-1) cin>>a[i];
		ans=f[0]=1;
		For(i,1,n-1)
		{
			f[i]=1;
			For(j,max(0,i-401),i-1)
				if((a[j]^i)<(a[i]^j))
					f[i]=max(f[i],f[j]+1);
			ans=max(ans,f[i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：simonG (赞：7)

由于该题涉及到了子序列，我们先一眼看出这一题是一道动态规划。  
根据以往的经验，于是我们先列出状态 $f_i$ 表示以 $i$ 结尾的 $b$ 序列最长长度。  
$O(n^2)$ 暴力方程为： $f_i=\max_{0\le j <i}(f_j+1),(a_j⊕i<a_i⊕j)$.  

瓶颈为寻找最大的 $f_j$ 需在 $0\le j <i$ 中寻找。  
在这一题中 $a_i\le 200$ ，那么我们思考：  
当$i>j+256$ 时，不考虑二进制后面 $8$ 位，$i>j$.  

由于 $a_i\le200$，所以 $a_i$ 只能影响后 $8$ 位。  
所以 $a_j⊕i<a_i⊕j$ 一定对 $i>j+256$ 不成立。

所以新的方程是： $f_i=\max_{i-256+1\le j <i}(f_j+1),(a_j⊕i<a_i⊕j)$.  
复杂度 $O(256n)$.

```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N=3e5+10,M=256;
int t,n,a[N],f[N],ans;
int main() {
	scanf("%d",&t);
	for(; t; t--) {
		scanf("%d",&n);
		ans=0;
		for(int i=0; i<n; i++)
			scanf("%d",&a[i]);
		for(int i=0; i<n; i++)
			f[i]=1;
		for(int i=0; i<n; i++) {
			for(int j=max(0,i-M+1); j<i; j++) {
				if((a[j]^i)<(a[i]^j)) {
					f[i]=max(f[i],f[j]+1);
				}
			}
		}
		for(int i=0; i<n; i++) ans=max(ans,f[i]);
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：lndjy (赞：4)

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

## 作者：sgl654321 (赞：3)

第一篇绿题题解！注意下面的方法只有 D1 可做。

### 题目大意
- 子序列定义：从最初序列通过**去除**某些元素，但不破坏余下元素的**相对位置**而形成的新序列。例如，有一个序列为 $[1,2,3,4,5]$，则 $[1,4,5]$ 是这个序列的一个子序列。
- 给定一个长度为 $n$ 的整数序列 $a$，从 $0$ 开始编号。其中所有的元素 $a_i$ 都满足 $a_i\le 200$。
- 如果 $a$ 有一个子序列 $b$，从 $0$ 开始编号，并且它的长度为 $m$。其中，对于所有的 $0\le i<m$ ，满足 $b_i \oplus (i+1)<b_{i+1}\oplus i$。那么这个子序列就被称作**美丽的子序列**。
- 求 $a$ 中最长的美丽的子序列。

### 解题思路
首先，我们会想到 $O(n^2)$ 的做法。这就是 dp 中非常基础的一个问题：[B3637 最长上升子序列](https://www.luogu.com.cn/problem/B3637)。我们可以用 $f_i$ 表示到 $i$ 为止的最长上升子序列，一开始初始值都设为 $1$。随后，再遍历所有的 $j\in[0,i-1]$，若满足 $a_j<a_i$ 并且 $f_j+1>f_i$，那么就把 $f_i$ 的值设为 $f_j+1$。

在这一题中也是一样的，只不过是把最长上升子序列换成了最长美丽子序列。那么我们只需要把 $f_i$ 的含义到 $i$ 为止的最长美丽子序列，然后把 $a_j<a_i$ 换成 $a_j\oplus i<a_i\oplus j$ 就可以了。

但是我们看一看数据规模，发现 $n$ 达到了 $3 \cdot 10^5$，于是乎 $O(n^2)$ 的做法就超时了。

那么我们想一想，有没有更快速的方法呢？我们可以从异或的性质出发思考。

异或的运算法则是：**同假异真**。就是说将两个数进行二进制拆分，如果某一位上两数都是 $1$ 或都是 $0$，那么这一位的运算结果就是 $0$。如果某一位上两数一个是 $1$，一个是 $0$，那么这一位的运算结果就是 $1$。

下面我们证明一个重要结论：$\lvert a-b\rvert \le a\oplus b \le a+b$。

证明：分类讨论。首先证明 $a\oplus b\le a+b$。


1. 如果两个数 $a,b$ 在二进制下每一位都不相同，那么 $a\oplus b=a+b$。
2. 其余情况，至少有一位相同，那么至少有一位会变成假。
- 如果相同的每一位都是 $0$，则 $a\oplus b=a+b$。
- 如果有一位相同的是 $1$，则 $1$ 就变成了 $0$，于是 $a\oplus b<a+b$。

综合上述， $a\oplus b\le a+b$。类似的，我们可以证明 $a\oplus b\ge \lvert a-b\rvert$。这里不加赘述了。

我们有了这个结论可以干什么呢？我们可以比较一下 $a_{401}\oplus 0$ 和 $a_0\oplus 401$ 的大小。 

$a_{401}\oplus 0\le a_{401}+0=a_{401}\le200$。

$a_0\oplus 401\ge \lvert a_0-401\rvert=401-a_0\ge 201$。

所以 $a_0 \oplus 401$ 一定大于 $a_{401}\oplus 0$。

我们再看看一般情况：比较大小： $a_{i+401}\oplus i$ 与 $a_i\oplus (i+401)$。

$a_{i+401}\oplus i\le a_{i+401}+i\le 200+i$

$a_i\oplus (i+401)\ge\lvert a_i-(i+401)\rvert=i+401-a_i\ge201+i$。

所以 $a_i\oplus (i+401)$ 一定大于 $a_{i+401}\oplus i$。


因此，在遍历的时候，我们不需要遍历 $i-400$ 以前的数，因为它之前的是一定满足该条件的。我们只需要遍历 $[\max\{i-400,0\},i-1]$ 就行啦！

此时，我们的时间复杂度就从 $O(n^2)$ 变成了 $O(n)$，可以通过这一道题。为什么不能通过 D2 呢？因为 D2 的 $a_i$ 达到了恐怖的 $10^9$，不能当作小常数来处理。
### 参考代码
本题有多组数据。在 C++ 中，异或可以用 ```^``` 或 ```xor``` 来表示，注意套括号。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[300010],f[300010],ans; 
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		//cout<<(2 xor 2)<<endl;
		ans=0;
		for(int i=0;i<n;i++)
			cin>>a[i];
		for(int i=0;i<n;i++){
			f[i]=1;
			for(int j=max(0,i-400);j<i;j++)
				if((a[j] xor i)<(a[i] xor j)&&f[j]+1>f[i]){
				//	cout<<i<<" "<<a[i]<<" "<<j<<" "<<a[j]<<endl;
				//	cout<<(a[j] xor i)<<" "<<(a[i] xor j)<<endl;
					f[i]=f[j]+1; 
				}
		}
		for(int i=0;i<n;i++)
			ans=max(ans,f[i]);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Leasier (赞：3)

枚举当前子序列终点再暴力 dp 的时间复杂度是 $O(\sum n^2)$ 的，显然无法通过。

考虑异或的性质，注意到 $\forall x \geq y, x \operatorname{xor} y \in [x - y, x + y]$，则 $i \operatorname{xor} a_j \in [i - 200, i + 200]$，$j \operatorname{xor} a_i \in [j - 200, j + 200]$，于是为了让两者相等，最坏情况下 $i - 200 = j + 200$ 即 $j = i - 400$。

于是我们对于每个 $i$，只需要枚举 $j \in [\max(i - 400, 1), i)$ 即可。时间复杂度为 $O(\sum n \max a_i)$。

代码：
```cpp
#include <stdio.h>

const int N = 3e5 + 7, M = 400;
int a[N], dp[N];

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++){
		int n, ans = 0;
		scanf("%d", &n);
		for (int j = 1; j <= n; j++){
			scanf("%d", &a[j]);
		}
		for (int j = 1; j <= n; j++){
			dp[j] = 0;
			for (int k = max(j - M, 1); k < j; k++){
				if ((a[j] ^ (k - 1)) > (a[k] ^ (j - 1))) dp[j] = max(dp[j], dp[k]);
			}
			ans = max(ans, ++dp[j]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：1)

看到一道很有意思的 dp。

## 思路

首先这种子序列的题，首先能想到的就是一个朴素的 $dp$ 状态：$dp_{i}$ 表示以 $i$ 结尾的“beautiful subsequence”最长长度是多少。

转移最显然的显然是：

$dp_{i}=\max\limits_{j=1}^{i-1} dp_j[a_j \oplus i<a_i \oplus j]+1$

时间复杂度 $O(n^2)$。考虑进行优化。

首先观察到 $a_i \leq 200$。由于异或不会产生进位，它最多影响 $200$ 的大小（注意可能会变小 $200$），即 $\forall j \in [1,n],\mid i \oplus a_j-i \mid \leq 200$。感性理解一下，如果 $i-j\geq 400$，假设 $a_i$ 足够大，也无法弥补这个巨大的差距。

所以我们每次 $j$ 从 $\max(1,i-400)$ 到 $i$ 枚举即可。时间复杂度 $O(400 \cdot n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ili inline int
#define cint const int
using namespace std;
const int MAXN=300005;
int a[MAXN],dp[MAXN];

ili qmax(cint &a,cint &b){return a>b?a:b;} // 建议手写 max，感觉系统自带的慢的要死。
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int T; cin>>T;
	while(T--){
		int n,ans=0; cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],dp[i]=1; // 初始化
		for(int i=1;i<=n;i++){
			for(int j=qmax(1,i-400);j<i;j++)
				if((a[i]^j-1)>(a[j]^i-1)) // 减 1 是为了和题目中的下标匹配（加法优先级高于异或所以懒得加括号了）
					dp[i]=qmax(dp[i],dp[j]+1);
			ans=qmax(ans,dp[i]); // 最后输出的是 max(dp[i])，我差点忘了
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Daidly (赞：1)

[Codeforces Round #815 (Div. 2) 全场题解以及更好的阅读体验](https://www.cnblogs.com/Daidly/p/16607199.html)

有意思的题。

首先你要读懂题，读透题。

然后我们考虑 $dp$，记 $f[i]$ 为以 $i$ 为结尾的最长的 $b$ 序列长度。

可以枚举 $j$ 转移 $f[i]=\max_{j<i}(f[i],f[j]+1)$，总时间复杂度 $O(Tn^2)$，显然不行。

考虑不枚举 $j$。

发现这题的特别点：$0\leq a_i\leq 200$，由于异或，考虑二进制。

显然 $a_i$ 在二进制下最多有 $8$ 位。

分析这个式子：$a_j\oplus i<a_i\oplus j$，其中 $j<i$ 为枚举的转移点。

由于 $i>j$ 但是 $i$ 在式子的左边，并且 $a_i,a_j$ 又特别小，所以要想满足此式，$i,j$ 在二进制下位数大于 $8$ 时必须有最高位到第 $8$ 位相等，再比较第 $0\sim 7$ 位。

我们考虑通过此优化转移过程：

- $i<256$ 时，暴力转移；
- $i\ge 256$ 时，我们可以限定 $j$ 的范围 $256\times\lfloor\frac{i}{256}\rfloor\leq j<i$，暴力转移。

这样时间复杂度就优化到了 $O(256Tn)$，足以通过。

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
 
int main(){
	t=read();
	while(t--){
		n=read(),ans=0;
		for(int i=0;i<n;++i)a[i]=read(),f[i]=1;
		for(int i=0;i<n;++i){
			if(i<256){
				for(int j=0;j<i;++j){
					if((a[j]^i)<(a[i]^j))f[i]=max(f[i],f[j]+1);
				}
			}else{
				int tmp=((i>>8)<<8); 
				for(int j=tmp;j<i;++j){
					if((a[j]^i)<(a[i]^j))f[i]=max(f[i],f[j]+1);
				}
			}
			ans=max(ans,f[i]);
		}
		print(ans),puts("");
	}
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：1)

可以想到一个十分 naive 的 dp，我们设 $dp_{i}$ 表示「good subsequence」的最大长度，那状态转移方程就是这样的。

$$dp_i = \max^i_{j=0} dp_j + 1 \  \ \ \ \text{if}\ a_j\oplus i < a_i \oplus j$$

显然 TLE。

考虑优化，我们注意到 $a_i \leq 200$，所以你发现如果 $i,j$ 相差很大的话那么 $a_j\oplus i$ 必定大于 $a_i \oplus j$。

所以我们不用跑完所有 $j$，让 $i,j$ 的差值在一个合理范围之内就行了。


[参考代码](https://www.luogu.com.cn/paste/o90h8k45)。

---

## 作者：_lfxxx_ (赞：0)

这题是最长子序列问题，但是要满足一个异或不等式。容易写出一个 $O(n^2)$ DP。

记 $f_i$ 为末尾是 $a_i$ 的最长子序列长度，我们可以按照下式 DP。

$$f_i=\max_{j<i\operatorname{and}{a_j \oplus i<a_i \oplus j}}f_j+1$$

其中 $\oplus$ 是异或。

但 $n\le3\times10^5$，无法通过。

我们注意到 $0 \le a_i \le 200$，所以说 $i$ 异或上 $a_j$ 变化不超过 $200$，即 $|(i \oplus a_j)-i|\le200$，所以当 $i-j>400$ 时，一定没有 $a_j \oplus i<a_i \oplus j$，因此我们的 DP 遍历到 $i-400$ 就好了。

这时复杂度为 $O(nw)$，$w$ 为值域，可以通过弱化版。

### 代码：
```cpp
namespace solution{
void main(){
	int T,n,ans;
	cin>>T;
	while(T--){
		ans=0;
		cin>>n;
		for(int i=0;i<n;++i)
			cin>>a[i];
		for(int i=0;i<n;++i){
			f[i]=1;
			for(int j=max(0,i-400);j<i;++j)
				if((a[j]^i)<(a[i]^j))
					f[i]=max(f[i],f[j]+1);
			ans=max(ans,f[i]);
		}
		cout<<ans<<'\n';
	}
}
}
```

---

