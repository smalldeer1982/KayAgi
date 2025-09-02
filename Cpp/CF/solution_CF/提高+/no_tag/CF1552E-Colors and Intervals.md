# Colors and Intervals

## 题目描述

The numbers $ 1, \, 2, \, \dots, \, n \cdot k $ are colored with $ n $ colors. These colors are indexed by $ 1, \, 2, \, \dots, \, n $ . For each $ 1 \le i \le n $ , there are exactly $ k $ numbers colored with color $ i $ .

Let $ [a, \, b] $ denote the interval of integers between $ a $ and $ b $ inclusive, that is, the set $ \{a, \, a + 1, \, \dots, \, b\} $ . You must choose $ n $ intervals $ [a_1, \, b_1], \, [a_2, \, b_2], \, \dots, [a_n, \, b_n] $ such that:

- for each $ 1 \le i \le n $ , it holds $ 1 \le a_i < b_i \le n \cdot k $ ;
- for each $ 1 \le i \le n $ , the numbers $ a_i $ and $ b_i $ are colored with color $ i $ ;
- each number $ 1 \le x \le n \cdot k $ belongs to at most $ \left\lceil \frac{n}{k - 1} \right\rceil $ intervals.

One can show that such a family of intervals always exists under the given constraints.

## 说明/提示

In the first sample, each number can be contained in at most $ \left\lceil \frac{4}{3 - 1} \right\rceil = 2 $ intervals. The output is described by the following picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1552E/357ee458ed0b41175ab4d6d5282731204fd88de0.png)In the second sample, the only interval to be chosen is forced to be $ [1, \, 2] $ , and each number is indeed contained in at most $ \left\lceil \frac{1}{2 - 1} \right\rceil = 1 $ interval.

In the third sample, each number can be contained in at most $ \left\lceil \frac{3}{3 - 1} \right\rceil = 2 $ intervals. The output is described by the following picture:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1552E/5bede56472d45bf512432afa3ad4f14a8a3b2bc1.png)

## 样例 #1

### 输入

```
4 3
2 4 3 1 1 4 2 3 2 1 3 4```

### 输出

```
4 5
1 7
8 11
6 12```

## 样例 #2

### 输入

```
1 2
1 1```

### 输出

```
1 2```

## 样例 #3

### 输入

```
3 3
3 1 2 3 2 1 2 1 3```

### 输出

```
6 8
3 7
1 4```

## 样例 #4

### 输入

```
2 3
2 1 1 1 2 2```

### 输出

```
2 3
5 6```

# 题解

## 作者：Lynkcat (赞：10)

题面中说每个位置只能被覆盖到$\lceil \frac{n}{k-1}\rceil$ 次，我们可以把它做个小转化：我们对每 $k-1$ 种颜色分段，那么问题就转化成了每个位置最多只能被覆盖到一次。

那么转化过后的问题如何解决呢？

考虑这样一个算法，我们将颜色在 $l$ 到 $l+k-2$ 这段区间的位置抠出来，然后预处理每个位置下一个与其颜色相同的位置是什么。

接着我们用 $k-1$ 个指针表示当前颜色匹配的左边的位置，每当我们扫描到一个位置 $i$ ，如果 $col_i$ 没有左匹配位置就把 $i$ 当作左匹配位置，否则就将 $i$ 当成右匹配位置，并将其他颜色的指针都往后跳直到比当前位置大。

我们大胆猜测，无论什么情况下都一定能得出合法的匹配。因为现在有 $k-1$ 种颜色，每种颜色都有 $k$ 个位置，那么我们很容易证明，每次匹配成功的时候，其余指针只会往后跳最多一次，因为如果能跳多次要么前面已经匹配掉了要么前面的已经跳过来了，不可能跳多次。所以每种颜色跳最多 $k-2$ 次，那么还剩余第 $k-1$ 个位置和第 $k$ 个位置也能顺利匹配。

所以就做完了（

```c++
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
//#define int ll
#define N 100005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,k,a[N],b[N],nxt[N];
pa ans[N];
signed main()
{
	n=read(),k=read();
	for (int i=1;i<=n*k;i++) a[i]=read();
	for (int j=1;j<=n;j+=k-1)
	{
		int p=min(n,j+k-2);
		int now=0;
		vector<int>G;
		for (int l=1;l<=n*k;l++)
			if (a[l]>=j&&a[l]<=p) G.push_back(l);
		memset(b,0,sizeof(b));
		memset(nxt,0,sizeof(nxt));
		for (int i=0;i<G.size();i++)
		{
			if (b[a[G[i]]])
			{
				nxt[b[a[G[i]]]]=G[i];
			}
			b[a[G[i]]]=G[i];
		}
		for (int i=1;i<=n;i++) nxt[b[a[i]]]=n*k+1;
		memset(b,0,sizeof(b));
		for (int i=0;i<G.size();i++)
		{
			if (b[a[G[i]]]&&b[a[G[i]]]!=G[i])
			{
				ans[a[G[i]]]={b[a[G[i]]],G[i]};
				b[a[G[i]]]=0;
				for (int l=j;l<=p;l++)
					if (b[l])
					{
						while (b[l]<=G[i]) b[l]=nxt[b[l]];
					}
			} else 
			{
				if (ans[a[G[i]]].fi==0) b[a[G[i]]]=G[i];
			}
		}
	}
	for (int i=1;i<=n;i++) writesp(ans[i].fi),writeln(ans[i].se);
				
		
}
/*

*/
```

---

## 作者：DaiRuiChen007 (赞：9)

# CF1552E 题解



## 思路分析

记 $p_{i,j}$ 表示第 $i$ 个颜色在原序列中第 $j$ 次出现的下标。

注意到每个点至多被覆盖 $\left\lceil\dfrac n{k-1}\right\rceil$ 这个条件很特殊，考虑从这里入手。

首先，根据贪心观察知道，对于每个颜色 $i$，对应的区间 $[a_i,b_i]$ 中应该没有颜色为 $i$ 的其他位置，不然缩短区间长度不会更劣，所以每个 $[a_i,b_i]$ 都应该是颜色 $i$ 在原序列出现的 $k$ 个位置中相邻的某两个，即某个 $[p_{i,j},p_{i,j+1}]$。

对于一个给定的 $j$ 不妨统称对于所有 $i$，区间 $[p_{i,j},p_{i,j+1}]$ 都叫做“第 $j$ 段”颜色段。

所以对于每个颜色 $i$，我们把其可以选择的区间数缩小到了 $k-1$ 个。

此时我们可以这样想：由于每个颜色有 $k-1$ 个区间可以选，因此我们可以把 $n$ 个颜色分别划分到 $\left\lceil\dfrac n{k-1}\right\rceil$ 个序列里，且这样的每个序列包含的颜色段恰好是第 $1\sim k-1$ 段各一个。

假如每个序列中的颜色段互不相交，则对于每个序列，每个位置至多被覆盖一次，此时的构造方案是满足要求的。

注意到每次生成一个序列不好做，那么考虑从一次取出所有选择了第 $j$ 段的颜色，再把这些颜色塞进不同的序列里面。

因此我们要做的就是对于每个 $1\sim k-1$ 的 $j$，在还没被选的颜色中，选 $\left\lceil\dfrac n{k-1}\right\rceil$ 个颜色，而对于这些颜色都选择其对应的第 $j$ 段，假如这样的每个这样的第 $j$ 段都不与所有选过的其他段相交的话，那么这样的构造满足要求。

考虑在解“选出尽可能多的不相交线段”这一问题的方法，我们在处理第 $j$ 段的时候，对于每个颜色 $i$，按照 $p_{i,j+1}$ 的值从小到大排序，选出其中值最小的若干个。

事实上这个做法是正确的：

> 证明：
>
> 采用反证法：假设这样选择后存在两个区间 $[p_{i_1,j_1},p_{i_1,j_1+1}]$ 和 $[p_{i_2,j_2},p_{i_2,j_2+1}]$ 相交，其中 $j_1\ne j_2$。
>
> 那么不妨假设 $j_1<j_2$。
>
> 由于颜色 $i_2$ 并没有被选做第 $j_1$ 段，那么我们知道 $p_{i_1,j_1+1}<p_{i_2,j_1+1}$。
>
> 由于 $j_1<j_2$，所以 $j_2\ge j_1+1$，所以 $p_{i_2,j_2}\ge p_{i_2,j_1+1}>p_{i_1,j_1+1}$，因此这样相交的区间不存在，所以原命题得证。

因此对于每个 $j$，进行一次排序即可。

时间复杂度 $\Theta(kn\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
const int MAXN=101;
pii ans[MAXN];
vector <int> p[MAXN];
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	vector <pii> vec;
	for(int i=1;i<=n;++i) vec.push_back(make_pair(0,i));
	int t=ceil((double)n/(m-1));
	for(int i=1;i<=n*m;++i) {
		int col;
		scanf("%d",&col);
		p[col].push_back(i); 
	}
	for(int i=1;i<m;++i) {
		for(auto &u:vec) u.first=p[u.second][i];
		sort(vec.begin(),vec.end());
		for(int j=1;!vec.empty()&&j<=t;++j) {
			int k=vec.begin()->second;
			vec.erase(vec.begin());
			ans[k]=make_pair(p[k][i-1],p[k][i]);
		}
	}
	for(int i=1;i<=n;++i) printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}
```



---

## 作者：Cutest_Junior (赞：6)

## CF1552E 【Colors and Intervals】

### 题意

+ 长度 $n\times k$ 的颜色序列 $c$，任意颜色 $1\le i\le n$ 都出现过 $k$ 次；
+ 选 $n$ 个区间，其中第 $i$ 个区间为 $[l_i,r_i]$，满足
1. $c_{l_i}=c_{r_i}=i$；
2. 且任意 $1\le j\le n\times k$，覆盖点 $j$ 的区间不超过 $\lceil\dfrac{n}{k-1}\rceil$；
+ One can show that such a family of intervals always exists under the given constraints.；
+ $n,k\le100$。

### 做法

题目已经保证当 $n\le k-1$ 时，一定存在每个点被至多 $\lceil\dfrac{n}{k-1}\rceil=1$ 个区间覆盖的方案。

把每 $k-1$ 种颜色拆出来，分别构造方案，然后再合并，一共只需要 $\lceil\dfrac{n}{k-1}\rceil$ 层，每层每个点最多被覆盖一次，合并后每个点最多被覆盖 $\lceil\dfrac{n}{k-1}\rceil$ 次，正好符合答案。

然后问题就转化成 $n<k$，每个点最多被一个区间覆盖。

考虑贪心。记 $cur$ 表示 $[1,cur]$ 中已经无法找到其它合法的未出现过的区间，且 $(cur,n\times k]$ 中任何点都未被覆盖。

每次找到最小的 $r$ 满足存在 $l$ 使 $cur<l<r,c_l=c_r$，且边界颜色与之相同的区间还未出现过，这时候记录区间 $[l,r]$，把 $r$ 赋值给 $cur$。

证明用数学归纳法。

1. 当前问题为 $q(n,k)$，且 $n<k$。每次找到区间都会少一个需要找区间的颜色，即 $n\leftarrow n-1$；而剩下的 $n-1$ 种颜色中，任意颜色在 $(cur,r]$ 中的出现次数均不超过 $1$（否则就能找到更小的 $r$。所以就能在 $(r,n]$ 中删掉几个点，使之变成问题 $q(n-1,k-1)$。
2. 当 $n=1$ 时，$k\ge2$，显然可以找到区间。

赛时一直在考虑怎么优化到 $k\log k$，其实只需要 $k^2$ 即可。

---

## 作者：imfbust (赞：2)

题目要求每个格子被包含不超过 $\lceil \dfrac{n}{k-1} \rceil$，那我们可以考虑每次求出 $k-1$ 个**不连续**的区间，总共求出 $n$ 个后，即可确保每段被包含的次数满足条件。

先来证明每次都能求出 $k-1$ 个区间：

可以用数学归纳法来证明。证明的命题为：对于 $k-1$ 种颜色 (由于此时要取 $k-1$ 个区间，只与 $k-1$ 个颜色有关，其他颜色在其他轮的取区间中再考虑)，每种 $k$ 个，可以去到 $k-1$ 个区间。

- 当 $k=2$ 时，一种颜色，且有两个，显然成立。
- 假设 $k=k_1-1$ 时成立，对于 $k_1-2$ 种颜色，每种 $k_1-1$ 个，可以取到 $k_1-2$ 个区间。
- 当 $k=k_1$ 时，令第一个取到的区间为 $[l_1,r_1]$，可以证明 $[1,r_1-1]$ 中没有一种颜色出现两次（若有，则 $r_1$ 可以更小），此时一种颜色被取过后，不需要考虑这种颜色，所以此时颜色还剩 $k_1-2$ 种，每种 $k_1-1$ 或 $k_1$ 个，显然，每种颜色越多，越容易取到区间，所以可令每种还有 $k_1-1$ 个，要取 $k_1-2$ 个区间，所以命题成立。

考虑每次如何取区间，取到 $[l_1,r_1]$ 后，清空记录的前驱信息，从 $r_1+1$ 开始遍历，然后取区间。

注意题目要求每个区间要按颜色输出。

**Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int n,k,cnt,pre[N],a[N*N];
bitset<N> vis;
pair<int,int> ans[N];
//ans记录答案，vis记录颜色是否取过
//cnt记录还能取几个区间
//pre记录每个颜色最后出现的位置
int main(){
    scanf("%d%d",&n,&k);cnt=n;
    for(int i=1;i<=n*k;i++) scanf("%d",&a[i]);
    while(cnt){
        for(int i=1;i<=n*k;i++){
            if(vis[a[i]]) continue;
            if(pre[a[i]]){
                ans[a[i]]={pre[a[i]],i};
                cnt--;
                vis[a[i]]=1;
                memset(pre,0,sizeof(pre));
            }
            else pre[a[i]]=i;
        }
        memset(pre,0,sizeof(pre));
    }
    for(int i=1;i<=n;i++) printf("%d %d\n",ans[i].first,ans[i].second);
    return 0;
}

```

---

