# [USACO23OPEN] Field Day S

## 题目描述

**提示：本题的 Python 时限为 15s。其它语言默认 2s。**

Farmer John 的 $N$ 个牛棚都会选出包含 $C$ 只奶牛的队伍去参加户外聚会。所有奶牛的品种都只可能是根西牛（`G`）或荷斯坦奶牛（`H`）。

我们将两个奶牛队伍中，同一位置对应的两头奶牛品种不同的所有位置 $i(1 \leq i \leq C)$ 的个数，定义为的两个奶牛队伍的差异。对于编号 $1...N$ 的每个奶牛队伍 $t$，请计算出 $t$ 和其它所有队伍的差异的最大值。

## 说明/提示

第一个和第三个队伍的差异为 $5$。第二个和第三个队伍的差异为 $3$。

$2 \leq N \leq 10^5,1 \leq C \leq 18$。

- 对于测试点 2-5：$C = 10$。
- 对于测试点 6-9：所有答案最少为 $C - 3$。
- 对于测试点 10-20：没有额外条件。

## 样例 #1

### 输入

```
5 3
GHGGH
GHHHH
HGHHG```

### 输出

```
5
3
5```

# 题解

## 作者：IamZZ (赞：24)

### 题目大意

​	现在有 $N(2\leq N\leq10^5)$ 个长度为 $C(1\leq C\leq18)$ 的字符串，由字符 `G` 与 `H` 组成。

​	求 $N$ 个字符串中与第 $i$ 个字符串最大的[汉明距离](https://baike.baidu.com/item/汉明距离/475174?fr=aladdin)了。

### 题解思路

​	首先，一个挺好的思路，我们可以先把每个字符串按二进制转换成数，便于处理。

​	我们发现，与数 $x$ 最大的汉明距离难以处理，而最小汉明距离却不难，考虑如何转化。

​	对于 $x$，与之最大的汉明距离其实就是 $C$ 减去与 $2^C-1-x$（$x$ 的反码）最小的汉明距离。

​	试着证明一下，我们现在已知有一个数与 $x$ 的反码有最小的汉明距离 $k$ 。

​	那这个数与 $x$ 的汉明距离就要将原本需要取反的 $k$ 位保持不变，另外相同的 $C-k$ 位却需要取反了，汉明距离也变成了 $C-k$。

​	现在题目似乎更明了了，我们首先要预处理出 $0 \sim 2^C-1$ 所有数能找到的最小汉明距离（$f$）。

​	先把输入的数（字符串）最小值设为 $0$，别的数就可以按照位枚举，依次转移。

​	之后的输出按照上面的结论就可以啦~

​	时间复杂度 $\Theta(2^C·C)$

### 题解代码

```c++
#include<cstdio>
using namespace std;
int c,n,f[1000001],m,o[100001],v;
char s[21];
int min(int a,int b)
{
	if(a<b)
	  return a;
	return b;
}
int main()
{
	int i,j;
	scanf("%d%d",&c,&n);
	for(i=0;i<=(1<<c)-1;++i)
	  f[i]=99999999;
	for(i=1;i<=n;++i)
	{
		scanf("%s",s+1);
		for(j=1;j<=c;++j)
		{
			v=0;
			if(s[j]=='G')
			  v=1;
			o[i]=o[i]<<1|v;
		}
		f[o[i]]=0;
	}
	for(j=1;j<=c;++j)
	{
		for(i=0;i<=(1<<c)-1;++i)
		  f[(1<<j-1)^i]=min(f[(1<<j-1)^i],f[i]+1);
	}
	for(i=1;i<=n;++i)
	{
		m=c-f[(1<<c)-1^o[i]];
		printf("%d\n",m);
	}
	return 0;
}

```

谢谢您选择这篇题解！

---

## 作者：普通的名字 (赞：10)

这里提供一个不同的思路。

首先把每个字符串压缩成一个数。数的范围显然是 $[0,2^C)$，记第 $i$ 个字符串对应的数为 $a_i$。

对于第 $i$ 个询问，答案等于 $\max\limits_{j\in[1,N]}\operatorname{popcount}(a_i\oplus a_j)$

如果暴力做，时间复杂度是 $O(N^2)$ 的，不能通过。

换一个思路，从大到小枚举答案 $x$，判断是否可行。若存在 $y\in[0,2^C),j\in[1,N]$，使得 $\operatorname{popcount}(y)=x$，且 $y\oplus a_j=a_i$，就是可行的。

观察关键条件：$y\oplus a_j=a_i$，这让我们联想到 $\text{FWT}$。

将 $a$ 中的各个元素丢进桶 $t$ 里面，对于所有 $j\in[0,2^C)$，按照二进制 $1$ 的个数归类，也按照类丢进桶里。然后对于每个类与 $t$ 进行 $\text{FWT}$。在判断时，只需要判断下标 $a_i$ 的数是否大于 $0$ 即可。

时间复杂度为 $O(C^2\cdot2^C)$

$\text{FWT}$ 数组记得开 `long long`。可能需要一些卡常技巧。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int C=18,N=1e5+1;
int c,n;
char s[C];
ll a[N],t[1<<C],b[C+1][1<<C],cnt[1<<C];
void fwt_xor(ll a[],int fl)
{
    int n=1<<c;
    for(int i=2;i<=n;i<<=1){
        for(int j=0;j<n;j+=i){
            for(int k=j;k<j+i/2;k++){
                ll x=a[k]+a[k+i/2],y=a[k]-a[k+i/2];
                a[k]=x>>(fl==-1),a[k+i/2]=y>>(fl==-1);
            }
        }
    }
}
int main()
{
    scanf("%d%d",&c,&n);
    for(int i=0;i<(1<<c);i++) cnt[i]=cnt[i>>1]+(i&1),b[cnt[i]][i]=1;
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        for(int j=0;j<c;j++) a[i]=(a[i]<<1)|(s[j]=='G');
        t[a[i]]++;
    }
    fwt_xor(t,1);
    for(int i=0;i<=c;i++){
        fwt_xor(b[i],1);
        for(int j=0;j<(1<<c);j++) b[i][j]=b[i][j]*t[j];
        fwt_xor(b[i],-1);
    }
    for(int i=1;i<=n;i++){
        for(int j=c;j>=0;j--){
            if(b[j][a[i]]){
                printf("%d\n",j);
                break;
            }
        }
    }
}
```


---

## 作者：FFTotoro (赞：9)

## 前言

一月进金组之后，就没怎么关注银组的消息。

3 月的 OPEN 赛季我们学校有几个人去参加银组，赛后 @[ZYC210712](https://www.luogu.com.cn/user/744885) 大佬分享了他在银组 T2 的广搜思路。本篇题解的思路就来自该大佬。

## 解法

本题可以使用**广度优先搜索**。

将 `G` 和 `H` 视为二进制下的 $0$ 和 $1$，本题就可以转化成：

给定 $n$ 整数 $a_1,a_2,\ldots,a_n$ 的二进制表示，$\forall 1\le i\le n$，求 $\max\limits_{j=1}^n\ \operatorname{popcount}\left(a_i\bigoplus a_j\right)$ 的值。

*这里 $\bigoplus$ 表示按位异或，$\operatorname{popcount}$ 表示一个整数二进制表示下 $1$ 的个数。*

定义两个“相邻”的整数 $a,b$ 为满足如下条件的整数：

- $a\bigoplus b$ 是 $2$ 的非负整数次幂。也就是说，它们的二进制表示下仅有一位不同。

考虑广搜，对于每个给出的整数为源点开始搜。每次搜相邻的整数，若该整数没被搜过，该整数步数 $+1$，将该整数放入队列。

最后对于每个 $a_i$，求出 $b=2^c-1-a_i$（即 $a_i$ 从右往左数 $c$ 位按位取反的值）的“步数”$x$，答案即为 $c-x$。

原理：最大的异或 $\operatorname{popcount}$ 即为总位数 $c$ 减去“$b$ 最小的异或 $\operatorname{popcount}$”，而最小的答案即为广搜出来 $b$ 的步数。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(false);
  int c,n; cin>>c>>n;
  vector<int> a(n),m(1<<c,-1);
  queue<pair<int,int> > q;
  for(auto &i:a){
    for(int j=0;j<c;j++){
      char x; cin>>x;
      if(x=='G')i|=1<<j;
    }
    q.emplace(i,m[i]=0);
  }
  while(!q.empty()){
    auto [u,w]=q.front(); q.pop();
    for(int i=0;i<c;i++)
      if(int v=u^(1<<i);m[v]==-1)
        q.emplace(v,m[v]=w+1);
  }
  for(int i:a)cout<<c-m[(1<<c)-1^i]<<endl;
  return 0;
}
```

---

## 作者：Nuyoah_awa (赞：7)


### 题目分析
首先想到暴力，先讲一种优化暴力：
$g_i$ 记录列哪些行是 `G`，哪些行是 `H`，然后每次枚举每行，这行的答案就是 $g_i$（$1 \le i \le c$） 的最大交集，这样时间复杂度是小于 $\mathcal O(n ^ 2 \times c)$ 的，如果数据够水，是可以接近 $\mathcal O(n\log n \times c)$ 的。

仔细观察数据范围发现：$c \le 18$。并且所有字符都是 `H` 或 `G`，所以最多有 $2 ^ c$ 个不同的字符串，于是可以考虑 dp。

我们定义 $dp[i]$：字符串 $s$ 转为二进制后再转为 `int`，即为 $i$；$dp[i]$ 存 $s$ 与其字符串的差异最大值。

dp 转移：对于一个字符串 $s$ 和另一个字符串 $t$，令 $s$ 和 $t$ 只有第 $i$ 位不同，也就是说他们其他位都相同，所以若与 $t$ 差异最大的某个字符串 $u$ 与 $t$ 的第 $i$ 位相同，那么，$u$ 与 $s$ 的差异为 $u$ 与 $t$ 的差异加一。

为方便表示，设根据位数 $c$，一共有 $m$ 个不同的字符串。

于是我们分别通过第 $k$ 位不同，其他位相同来将所有字符串分成 $\dfrac{m}{2}$ 对，我们对于每一对字符串 $s[i],s[j]$，转移方程为：$dp[s[i]] = \max (dp[s[i]], dp[s[j]] + 1)$。

特殊地，将 $dp[i]$ 的初值赋为 $-\infty$，对于出现过的字符串，赋为 $0$。

由于这种 dp 刨除了 $n$ 的影响，所以时间复杂度是 $\mathcal O(2 ^ {c-1} \times c)$ 的。

### code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 1e5 + 5, M = (1 << 18) + 5; 
string s[N];
int x[N], dp[M], n, m;

int main()
{
	scanf("%d %d", &m, &n);
	for(int i = 1;i <= n;i++)
		cin >> s[i];
	memset(f, -0x3f, sizeof(f));
	for(int i = 1;i <= n;i++)
	{
		for(int j = 0;j < m;j++)
			if(s[i][j] == 'H')
				x[i] |= (1 << j);
		dp[x[i]] = 0;
	}
	for(int j = 0;j < m;j++)
		for(int i = 0;i < (1 << m);i += (1 << (j + 1)))
			for(int k = i;k < i + (1 << j);k++)
			{
				int tmp1 = dp[k], tmp2 = dp[k ^ (1 << j)];
				dp[k] = max(tmp1, tmp2 + 1);
				dp[k ^ (1 << j)] = max(tmp2, tmp1 + 1);
			}
	for(int i = 1;i <= n;i++)
		printf("%d\n", dp[x[i]]);
	return 0;
}
```

---

## 作者：NaN_HQJ2007_NaN (赞：5)

简单题。

考虑到直接求最大不同位数不方便，我们不妨改为求最少相同位数。

于是对于每一个字符串，我们将其转化为二进制数并取反，放入队列中。

跑一遍 BFS，求出每种二进制数所需的最小变换次数。

最后每个字符串的答案为 $m-d_i$。

复杂度 $O(n\cdot 2^n)$。

#### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int m,n,s[N],mp[N];
struct node{
	int s,d;
	node(int s=0,int d=0):s(s),d(d){}
}tmp;
queue<node> q;
string str;
int main(){
 ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>m>>n;
	for(int i=1;i<=n;++i){
		cin>>str;int t=0;
		for(int j=0;j<m;++j)s[i]=s[i]*2+(str[j]=='G'),t=t*2+(str[j]=='H');
		mp[t]=1;q.push(node(t,1));
	}
	while(!q.empty()){
		node u=q.front();q.pop();
		for(int i=0;i<m;++i){
			int t=(u.s^(1<<i));
			if(!mp[t])mp[t]=u.d+1,q.push(node(t,u.d+1));
		}
	}
	for(int i=1;i<=n;++i)cout<<m-mp[s[i]]+1<<endl;
  return 0;
}
```


---

## 作者：H_Kaguya (赞：4)

简单转化一下题意，就是给定 $n$ 个数，然后对于每个数，求和其他数异或值的 `popcount` 的最大值。  

看上去像一个板子，但是想了想确实没什么思路，于是根据数据范围分析性质。  
$2^C$ 与 $n$ 是同阶的，所以考虑基于值域预处理出来所有数的答案。  

### $O(2^{2C} \times C)$

首先我们去枚举一个数 $D \in [ 0, 2^C)$，用线段树去维护 $D$ 和 $[0, 2^C)$ 中所有数的异或值和 `popcount`。  
每次 $D$ 的二进制位发生变化的时候就在线段树上做相应的修改即可。  
修改只有区间加，查询是全局 $\max$，普通线段树维护。  
容易发现这样的时间复杂度是 $O(2^{2C} \times C)$，显然过不去。  

### $O(2^C \times C^2)$

但是我们继续分析性质。  
容易发现，$D$ 从高到低的第 $i$ 个二进制位一共会被修改 $2^i$ 次。  
同时，当我们修改 $D$ 的第 $i$ 个二进制位的时候，会对 $2^i$ 个区间进行修改。  
这就启发我们反着维护贡献来平衡复杂度。  

具体的，我们对所有数进行位逆序变换，然后接着跑上面的暴力。  
这样，对于第 $i$ 个二进制位，会被修改 $2^i$ 次，每次修改会涉及 $2^{C - i}$ 个区间。  
所以一共会进行 $O(2^C \times C)$ 次修改。  
再加上我们线段树的深度是 $O(C)$ 的，所以整体复杂度是 $O(2^C \times C^2)$ 的。  

### $O(2^C \times C)$

复杂度里的 $C^2$ 就让人看着很不舒服。  
所以我们继续分析性质。  

首先，由于值域是二的整数幂，所以线段树只需要二倍空间。  
其次，每次修改只会涉及到线段树中的一个节点及其父链。  
这样，使用标记永久化就可以避免递归和麻烦的标记下放。  

每次我们让 $D$ 自加的时候，$D$ 的二进制位一定是最低的**连续的**若干位被取反。  
在线段树里表示也就是和根节点距离小于等于某个定值的整个连通块。  
那么借助标记永久化，我们在修改的时候可以直接自下而上，每次 $O(1)$ 修改一个节点并 `pushup`。  
实现也很容易，从高到低枚举被修改的二进制位即可。  
由于这次的线段树是满二叉树，可以简单的定位到要修改的位置。  

贴一份代码~

```cpp
#include <stdio.h>
#include <algorithm>
#define sz 262144
struct site
{
	char laz, mx;
};
site tree[sz << 1];
int n, m, c;
bool vis[sz];
int num[sz], ans[sz];
int read();
int stread();
void build(int, int, int);
void fix(int, int);
void sol(int, int);
int main()
{
	n = read(); c = read();
	m = 1 << c;
	for (int i = 1; i < m; ++i)
	{
		ans[i] = ans[i >> 1] >> 1;
		if (i & 1)
			ans[i] |= m >> 1;
	}
	for (int i = 1; i <= n; ++i)
	{
		num[i] = stread();
		vis[ans[num[i]]] = true;
	}
	build(1, 1, m);
	for (int i = 0; i < m; ++i)
	{
		ans[i] = std::max(tree[2].mx, tree[3].mx);
		if (i + 1 == m)
			break;
		int x = 1 << __builtin_ctz(i + 1);
		sol(x << 1, 1); x >>= 1;
		while (x)
		{
			sol(x << 1, -1);
			x >>= 1;
		}
	}
	for (int i = 1; i <= n; ++i)
		printf ("%hhd\n", ans[num[i]]);
	return 0;
}

int read()
{
	int x = 0;
	char c = getchar();
	while (c < '0') c = getchar();
	do {
		x = x * 10 + (c & 15);
		c = getchar();
	}while (c >= '0');
	return x;
}

int stread()
{
	int x = 0;
	char c = getchar();
	while (c < 'A') c = getchar();
	do {
		x = x << 1 | (c == 'G');
		c = getchar();
	}while (c >= 'A');
	return x;
}

void build(int a, int lf, int rt)
{
	if (lf == rt)
	{
		if (vis[lf - 1])
			tree[a].mx = __builtin_popcount(lf - 1);
		else
			tree[a].mx = -100;
		return;
	}
	int mid = lf + rt >> 1;
	build(a << 1, lf, mid);
	build(a << 1 | 1, mid + 1, rt);
	tree[a].mx = std::max(tree[a << 1].mx, tree[a << 1 | 1].mx);
}

void fix(int a, int b)
{
	tree[a].laz += b;
	tree[a].mx = std::max(tree[a << 1].mx, tree[a << 1 | 1].mx) + tree[a].laz;
}

void sol(int a, int b)
{
	if (a == m)
		for (int i = 0; i < a; i += 2)
		{
			tree[a | i].mx += b;
			tree[a | i | 1].mx -= b;
		}
	else
		for (int i = 0; i < a; i += 2)
		{
			fix(a | i, b);
			fix(a | i | 1, -b);
		}
}

```


---

## 作者：piggy123 (赞：2)

我的做法好像很奇怪，也很劣，但能过。

发现暴力过不去，考虑折半搜索。

下面仅讨论 $C=18$ 时的情况，其他类似。对于每个询问，枚举前 $9$ 位，然后对于固定的前 $9$ 位，预处理出对于某一个后 $9$ 位的最大汉明距离，类似这样：

```cpp
for (ll i=0;i<=(1<<hf)-1;i++){
	for (ll j=0;j<=(1<<hf2)-1;j++){
		vv[i][j]=-1e18;
		for (ll k:vct[i]){
			vv[i][j]=max(vv[i][j],(ll)__builtin_popcount(k^j));
		}
	}
}
```

因为第一层循环和第三层循环最多执行 $n$ 次，所以这一部分复杂度是 $O(n2^{\frac{C}{2}})$ 的。

对于每个询问，复杂度是 $O(2^{\frac{C}{2}})$ 的。

总体复杂度就是 $O(n2^{\frac{C}{2}})$ 的。

---

## 作者：ppip (赞：2)

[题目传送门](/problem/P9187)

题意转化为对于每个 $i$，求 $\max_j\{\text{popcount}(a_i\oplus a_j)\}$。

我们考虑对于 $[0,2^C]$ 中的每个数 $x$，求出 $f_x=\min_j\{\text{popcount}(x\oplus a_j)\}$。这样 $i$ 的答案就是 $a_i$ 逐位取反后的 $f$ 值。

求出 $f$ 也很简单。令 $g$ 和 $f$ 定义类似，但是只考虑是 $x$ 的超集的这些 $a_j$。于是就有转移 $g_x=\min_y(g_y+1)$，其中 $y$ 是和 $x$ 相差一位的超集。

思考这样一件事情：如果 $\text{popcount}(x\oplus a_j)$ 最小，则必定存在一个 $x$ 的子集 $y$，使得 $a_j$ 是 $y$ 的超集，且 $\text{popcount}(x\oplus a_j)=\text{popcount}(x\oplus y)+\text{popcount}(y\oplus a_j)$（当然不是最小也成立，只是取最小的时候对写出转移方程有帮助）。

所以可以写出方程 $f_x=\min_y\{\text{popcount}(x\oplus y)+g_y\}$，其中 $y$ 为 $x$ 的一个子集。

这也可以像 $g$ 一样，只转移差一位的子集。考虑 $x$ 的一个差一位子集 $y$ 的一个子集，它到 $x$ 的距离就是到 $y$ 的距离 $+1$，所以 $f_y+1$ 就是 $y$ 的所有子集对 $f_x$ 的贡献。

方程即为 $f_x=\min(g_x,\min_y\{f_y+1\})$，总复杂度 $\Theta(n+C2^C)$。

然后注意到 $f_x\leq g_x$，因为转移的式子里有一项 $g_x$，所以我们求出 $g$ 后，可以直接在这个数组上跑 $f$ 的转移。

代码很好写。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N(1e5),LG{18};
int f[1<<LG];
int a[N+5];
int main() {
    int n,m;cin>>m>>n;
    for (int i{1};i<=n;++i) {
        char s[19];scanf("%s",s);
        for (int j{0};j<m;++j) a[i]=a[i]<<1|s[j]=='H';
    }
    fill_n(f,1<<m,m+1);
    for (int i{1};i<=n;++i) f[a[i]]=0;
    for (int i{(1<<m)-1};~i;--i)
        for (int j{0};j<m;++j)
            if (~i>>j&1) f[i]=min(f[i],f[i^1<<j]+1);
    for (int i{0};i<1<<m;++i)
        for (int j{0};j<m;++j)
            if (i>>j&1) f[i]=min(f[i],f[i^1<<j]+1);
    for (int i{1};i<=n;++i) cout<<m-f[(1<<m)-1-a[i]]<<"\n" ;
    return 0;
}
```

---

