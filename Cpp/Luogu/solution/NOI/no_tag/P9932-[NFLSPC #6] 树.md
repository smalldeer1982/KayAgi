# [NFLSPC #6] 树

## 题目背景

# 请不要使用 C++14 (GCC 9) 提交

## 题目描述

给定一棵 $n$ 个点的树，标号从 $0$ 到 $n-1$，每个点有一个 $0$ 到 $n-1$ 之间的颜色。

$q$ 次询问，每次查询 $x$ 的祖先中颜色为 $c$ 的点中离 $x$ 最近的一个（也就是深度最大的一个）的编号，**强制在线**。

**点的颜色在数据生成完之后进行了一次随机打乱（也就是作用了一个均匀随机的排列）**。

## 说明/提示

对于所有数据，$2\leq n\leq 2\times 10^6$，$q=5n\leq 10^7$，$-1\leq fa_i<i$，$0\leq col_i<n$，$fa_0=-1$ 且对任意 $1\leq i < n$，$fa_i\geq 0$。

- 子任务 1（$5$ 分）：$n\leq 1000$。
- 子任务 2（$20$ 分）：$n\leq 200000$。
- 子任务 3（$30$ 分）：$fa_i=i-1$。
- 子任务 4（$45$ 分）：无特殊限制。

每个子任务评分方式为子任务内所有点的得分取最小值。交互库运行时长不超过 600ms，消耗空间不超过 140MB。

**本题在 OJ 上显示的时限不是真正的时限**。若你的代码没有在规定的时间和空间内正常运行并正确回答所有询问，该测试点获得 0 分。若你实现的函数运行时间不小于 2400ms，你将获得 `Time Limit Exceeded`（实际测试时会通过让 grader 死循环来实现这一点）。否则若你实现的函数共运行了 $x$（$x<2400$） 毫秒，你获得的分数为：
- $x\leq 1200$，返回 `Accepted`, 获得该测试点全部分数。
- $1200<x<2400$，返回 `Partially Correct`, 获得该测试点 $(\frac {2400 - x} {1200}) ^ 2$ 倍的分数。

**测试点信息上显示的不是真正的耗时，SPJ 详细信息里显示的才是你实现的部分的耗时**。

Source：NFLSPC #6 H by asmend

## 样例 #1

### 输入

```
5 25
-1 0 1 1 0
0 1 0 2 2
0 0
0 1
0 2
0 3
0 4
1 0
1 1
1 2
1 3
1 4
2 0
2 1
2 2
2 3
2 4
3 0
3 1
3 2
3 3
3 4
4 0
4 1
4 2
4 3
4 4
```

### 输出

```
0
-1
-1
-1
-1
0
1
-1
-1
-1
2
1
-1
-1
-1
0
1
3
-1
-1
0
-1
4
-1
-1
```

# 题解

## 作者：asmend (赞：7)

考虑列出整棵树的欧拉序，对于每个颜色 $c$，设它出现了 $m_c$ 次，那么它将欧拉序划分为 $2m_c$ 个区间，每个区间答案相同。于是我们把问题转化为，有若干个有序数组，它们的长度之和为 $O(n)$，每次查询在其中一个数组中求 lower bound。直接对每次询问二分即可做到 $O(n+q\log n)$，可以获得约 $[30,40]$ 分。

对每个数组，设数组中元素个数为 $m$，我们对欧拉序以 $\frac{n}{m}$ 为块长分块，然后对块的端点预处理出 lower bound 的结果。查询时，找到查询位置所在块的端点，然后在此基础上暴力计算块内的部分。

由于颜色经过随机打乱，dfs 进栈序和出栈序都可视为均匀随机（尽管它们两个之间不独立），而欧拉序是进栈序和出栈序的某种归并，所以每块内期望有 $O(1)$ 个元素。于是复杂度为 $O(n+q)$。

接下来还可以加一些常数优化，例如：

- 不要使用 vector，存图用前向星，按颜色归类用桶排。
- 特判链，此时不需要存图和 dfs 求欧拉序。
- dfs 到最后一个叶子之后，后面的欧拉序就不需要存了。
- 当 $m$ 很小时，不做分块预处理。

std 实现如下。

``` cpp
#define fz1(i,n) for ((i)=1;(i)<=(n);(i)++)
#define fd1(i,n) for ((i)=(n);(i)>=1;(i)--)
#define fz0g(i,n) for ((i)=0;(i)<=(n);(i)++)
#define fd0g(i,n) for ((i)=(n);(i)>=0;(i)--)
#define fz0k(i,n) for ((i)=0;(i)<(n);(i)++)
#define fd0k(i,n) for ((i)=(((long long)(n))-1);(i)>=0;(i)--)
#define fz(i,x,y) for ((i)=(x);(i)<=(y);(i)++)
#define ff(c,itr) for (__typeof((c).begin()) itr=(c).begin();itr!=(c).end();++itr)
#define pb push_back
#define mk make_pair
#define rdst(st,len){static char ss[len];scanf(" %s",ss);(st)=ss;}
#define spln(i,n) (i==n?'\n':' ')
#define fac_init(n){fac[0]=fac[1]=inv[1]=fi[0]=fi[1]=1;fz(i,2,n){fac[i]=1ll*fac[i-1]*i%mod;inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;fi[i]=1ll*fi[i-1]*inv[i]%mod;}}
using namespace std;
typedef long long i64;
typedef long double f80;
typedef unsigned int u32;
typedef unsigned long long u64;
#include "tree.h"
const int maxn=2000000;
int lg[maxn+5];
int n,i,j,dfn[maxn+5],lst[maxn+5],cc;
int a[maxn*2+5],c[maxn*2+5],cnt;
int fa[maxn+5],col[maxn+5];
int hd[maxn+5],nxt[maxn+5];
int _1[maxn*3+5],tot;
int *f[maxn+5];
int c0[maxn*2+5],s0[maxn*2+5];
int seq[maxn*2+5];
int len[maxn+5];
void dfs(int x)
{
	cc++;dfn[x]=++cnt;int mem=lst[col[x]];
	a[cnt]=col[x];c[cnt]=lst[col[x]]=x;
	int i;for(i=hd[x];i;i=nxt[i])dfs(i);
	cnt++;a[cnt]=col[x];c[cnt]=lst[col[x]]=mem;
}
void init(int nn,vector<int> fa1,vector<int> col1)
{
	n=nn;bool flg=1;
	fz0k(i,n)fa[i]=fa1[i],col[i]=col1[i],flg&=(fa[i]==i-1);
	fz(i,2,maxn)lg[i]=lg[i/2]+1;
	if(flg){
		cnt=n;
		fz0k(i,n){
			dfn[i]=i+1;
			a[i+1]=col[i];
			c[i+1]=i;
		}
	}
	else{
		fd1(i,n-1) nxt[i]=hd[fa[i]],hd[fa[i]]=i;
		fz0k(i,n)lst[i]=-1;
		dfs(0);
	}
	fz1(i,cnt) c0[a[i]]++;
	fz0k(i,n) s0[i]+=c0[i],s0[i+1]+=s0[i];
	fd1(i,cnt) seq[s0[a[i]]--]=i;
	fz0k(i,n)if(c0[i]>3){
		len[i]=lg[cnt/c0[i]];
		int len=(1<<::len[i]),num=(cnt>>::len[i]);
		f[i]=(_1+tot);tot+=num+1;
		int k=0;f[i][0]=0;
		fz1(j,num){
			while(k+1<=c0[i]&&seq[s0[i]+k+1]<=j*len) k++;
			f[i][j]=k;
		}
	}
}
int query(int x,int y)
{
	if(!c0[y]) return -1;x=dfn[x];
	int t=(c0[y]>3?f[y][x>>len[y]]:0);
	while(t+1<=c0[y]&&seq[s0[y]+t+1]<=x) t++;
	if(t==0) return -1; else return c[seq[s0[y]+t]];
}
```

---

## 作者：critnos (赞：2)

非常非常恶心的乱搞题。我交了 166 发才过。

考虑离线的 dfs 做法得到的操作序列，那么树就是等价于序列的，且我们猜测这个序列的每种颜色也是均匀随机的。

那么就相当于给若干个随机集合每次在一个集合里面找（非严格）前驱。因为这个序列是均匀的，所以可以用值估计出 $x$ 的大概位置 $\dfrac x {n/(|S|+1)}$，然后真实位置离这个是很近的，可以在一个比较短的距离里面二分。

过不去，开始卡常：

1. 如果 $|S|$ 比较大，大概位置距离实际位置就比较远。所以对于前 $B$ 大的集合，可以 $O(\dfrac {nB} w+q)$ 处理（巨大优化，实际上不知道对复杂度有没有优化）。

2. `vector` 换手动分配（巨大优化）。

3. 集合大小较小直接暴力

4. 二分比较拉跨，我是选一个步长暴力跳，然后往回跳。

5. 换成 $\dfrac x {(S_{max}-S_{min})/(|S|-1)}$。

6. 洗把脸。

https://www.luogu.com.cn/paste/qbouurmi

---

