# Happy New Year

## 题目描述

Being Santa Claus is very difficult. Sometimes you have to deal with difficult situations.

Today Santa Claus came to the holiday and there were $ m $ children lined up in front of him. Let's number them from $ 1 $ to $ m $ . Grandfather Frost knows $ n $ spells. The $ i $ -th spell gives a candy to every child whose place is in the $ [L_i, R_i] $ range. Each spell can be used at most once. It is also known that if all spells are used, each child will receive at most $ k $ candies.

It is not good for children to eat a lot of sweets, so each child can eat no more than one candy, while the remaining candies will be equally divided between his (or her) Mom and Dad. So it turns out that if a child would be given an even amount of candies (possibly zero), then he (or she) will be unable to eat any candies and will go sad. However, the rest of the children (who received an odd number of candies) will be happy.

Help Santa Claus to know the maximum number of children he can make happy by casting some of his spells.

## 说明/提示

In the first example, Santa should apply the first and third spell. In this case all children will be happy except the third.

## 样例 #1

### 输入

```
3 5 3
1 3
2 4
3 5```

### 输出

```
4```

# 题解

## 作者：George1123 (赞：33)

# 题解-Happy New Year

## [在垃圾桶里读这篇文章](https://www.cnblogs.com/Wendigo/p/12654517.html)

> [Happy New Year](https://www.luogu.com.cn/problem/CF1313D)

> 给定 $n$，$m$ 和 $k$。有一个序列 $a\{m\}$ 初始值为 $0$。有 $n$ 种操作，每种可以使 $[L_i,R_i]$ 区间序列值 $+1$。每个操作最多用 $1$ 次（可以不用）。保证对于每个 $i(1\le i\le n)$ 最多存在 $k$ 个不同的 $j$ 满足 $i\in[L_j,R_j]$。求最后的序列中奇数最多个数。

> 数据范围：$1\le n\le 10^5$，$1\le m\le 10^9$，$1\le k\le 8$。

---
状压 $\texttt{dp}$ 水题，连我这个小蒟蒻都几下就做出来了。

---
**从数据范围和时间复杂度入手分析题目：**

1. 首先看到 $n$ 的大小，就知道复杂度中要带个 $n$。
2. 时间复杂度中不能带 $m$，而且这题也**不能二分倍增分治之类的**，所以也不带 $\log m$。
3. 时间复杂度可以带 $k$，甚至还可以带个 $2^k$。考虑到这个 $k$ 真是小到离奇，于是想着带 $2^k$——写个状压 $\texttt{dp}$。

---
将每个区间 $i$ 的 $L_i$ 和 $R_i+1$ 带信息放进数组 $p$ 中，按如下的 $\texttt{cmp}$ 排序：

```cpp
struct point{
	int op,w,d; //如果是L_i，op=1，w=L_i；如果是R_i，op=-1，w=R_i+1。d=i
	point(int OP=0,int W=0,int D=0){op=OP,w=W,d=D;}
};
int cmp(point x,point y){
	if(x.w==y.w) return x.op<y.op; //※先处理R_i，防止中途当前覆盖区间数 >k
	return x.w<y.w; //按大小排序
}
```

从左到右枚举每个端点，将当前覆盖着的区间放进数组 $d$。

**令 $f_{i,j}$ 表示到第 $i$ 个端点，选择的区间覆盖状态为 $j$ 的最大答案。**

$j$ 中二进制下如果第 $at-1$ 位是 $1$，则表示选择了区间 $d_{at}$ 并且 $d_{at}$ 正覆盖在当前端点上。

如果 $at$ 表示该端点在数组 $d$ 中的位置，那么相邻两个端点之间可以如下递推：

![QQ图片20200407205442.png](https://i.loli.net/2020/04/07/Vl1hyLq9as4UNc3.png)

最后的答案就是 $f_{2n,\varnothing}$。

---
小蒟蒻怕自己讲不清楚，于是做了个动画：

**Input**

```cpp
3 10 2
2 5
5 7
8 9
```

![gif5新文件 _1_.gif](https://i.loli.net/2020/04/07/TZyj57G36EUViWo.gif)

---
**时间复杂度 $\Theta(n2^k)$，空间复杂度 $\Theta(n2^k)$。**

---

## Code

蒟蒻的做法比较玄学，但是又很简单，所以放个代码走人吧。

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
#define lng long long
#define db double
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define rz resize
const int inf=0x3f3f3f3f;
const lng INF=0x3f3f3f3f3f3f3f3f;

//Data
const int N=1e5,K=8;
int n,m,k;
int l[N+7],r[N+7];
struct point{
	int op,w,d;
	point(int OP=0,int W=0,int D=0){op=OP,w=W,d=D;}
};
int cmp(point x,point y){
	if(x.w==y.w) return x.op<y.op;
	return x.w<y.w;
}
int pcnt;
point p[(N<<1)+7];

//DP
int d[K+7],one[(1<<K)+7];
int f[(N<<1)+7][(1<<K)+7];
void Max(int&x,int y){x=max(x,y);}
int DP(){
	int ful=(1<<k)-1;
	for(int i=1;i<=ful;i++) one[i]=one[i-(i&-i)]+1;
	for(int i=0;i<=pcnt;i++)
		for(int j=0;j<=ful;j++) f[i][j]=-inf;
	f[0][0]=0;
	for(int j=1;j<=k;j++) d[j]=-1;
	int now=0;
	for(int i=1;i<=pcnt;i++){
		int at=-1;
		if(p[i].op==1){
			for(int j=1;j<=k;j++)
				if(d[j]==-1){at=j,d[j]=p[i].d;break;}
			assert(~at);
			for(int j=0;j<=now;j++)if((j&now)==j){
				Max(f[i][j],f[i-1][j]+(one[j]&1)*(p[i].w-p[i-1].w));
				Max(f[i][j|(1<<(at-1))],f[i-1][j]+(one[j]&1)*(p[i].w-1-p[i-1].w)+((one[j]+1)&1));
			}
			now|=(1<<(at-1));
		} else {
			for(int j=1;j<=k;j++)
				if(d[j]==p[i].d){at=j,d[j]=-1;break;}
			assert(~at);
			now^=(1<<(at-1));
			for(int j=0;j<=now;j++)if((j&now)==j){
				Max(f[i][j],f[i-1][j]+(one[j]&1)*(p[i].w-p[i-1].w));
				Max(f[i][j],f[i-1][j|(1<<(at-1))]+((one[j]+1)&1)*(p[i].w-1-p[i-1].w)+(one[j]&1));
			}
		}
	}
	return f[pcnt][0];
}

//Main
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l[i],&r[i]);
		p[++pcnt]=point(1,l[i],i);
		p[++pcnt]=point(-1,r[i]+1,i);
	}
	sort(p+1,p+pcnt+1,cmp);
	printf("%d\n",DP());
	return 0;
}
```
---
**祝大家学习愉快！**

---

## 作者：OMG_wc (赞：29)

本题总人数 $m$ 很大，但咒语数 $n\le 10^5$ ，因而离散化后最多也只有 $2n$ 个本质不同的位置。当然不需要真的实现离散化（实现起来太复杂），只需把第 $i$ 个咒语拆分为两个事件 $(l,i)$ 和 $(r+1,-i)$ ，存到 `pair<int,int>` 中，然后用扫描线解决。

虽然咒语总数有 $n$ 个，但对每个位置而言最多只会受 $8$ 个咒语影响，考虑状压 DP 来解决本题（这里需要用一个 `vis` 数组来分配编号，详情见代码）。

两个事件中间的段就是离散化后的点，记长度为`len`。设 $f_{i,j}$ 表示第 $i$  段状态为 $j$ 时前 $i$ 段快乐数最大值 ，每个状态的转移一定是 $O(1)$ 的，因为连续两个事件之间，最多只有一个状态位会改变（不变、增、删）。具体分成下面两种情况 ：

- 这段的起点添加了某个咒语，设该咒语在状态中是第 $k$ 位，当前考虑的状态为 $j$。
  - 若 $s$ 的第 $k$ 位为 $1$，那么 `f[i][j]`是唯一从 ` f[i-1][j ^ 1 << k]` 转移过来的，若 $j$ 中包含奇数个 $1$，还要再加上`len`。
  - 若 $s$ 的第 $k$ 位为 $0$，那么 `f[i][j]`是唯一从 ` f[i-1][j]` 转移过来的，若 $j$ 中包含奇数个 $1$，还要再加上`len`。
- 这段起点结束了某个咒语
  - 若 $s$ 的第 $k$ 位为 $1$，那么 `f[i][j]` 不存在。
  - 若 $s$ 的第 $k$ 位为 $0$，那么 `f[i][j]`是从 ` f[i-1][j]` 和 `f[i-1][j^1<<k]` 较大的那个转移过来的，若 $j$ 中包含奇数个 $1$，还要再加上`len`。

很容易发现，空间上第一维可以省略，最终答案就是 $f_0$ （最后一段是空的，无任何咒语）。

参考代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
const int N = 100005;

vector<pair<int, int>> a;
int f[1 << 8], vis[8];
int main() {
    int n;
    scanf("%d%*d%*d", &n);
    for (int i = 1; i <= n; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        a.push_back({l, i});
        a.push_back({r + 1, -i});
    }
    sort(a.begin(), a.end());
    for (int i = 1; i < 256; i++) f[i] = -INF;
    for (int u = 0; u < a.size(); u++) {
        int id = a[u].second, k;
        int len = u == a.size() - 1 ? 0 : a[u + 1].first - a[u].first;
        if (id > 0) {
            for (int i = 0; i < 8; i++) {
                if (vis[i] == 0) {
                    vis[k = i] = id;
                    break;
                }
            }
            for (int i = 255; i >= 0; i--) {
                if (i >> k & 1) {
                    f[i] = f[i ^ 1 << k] + len * __builtin_parity(i);
                } else {
                    f[i] = f[i] + len * __builtin_parity(i);
                }
            }
        } else {
            for (int i = 0; i < 8; i++) {
                if (vis[i] == -id) {
                    vis[k = i] = 0;
                    break;
                }
            }
            for (int i = 0; i < 256; i++) {
                if (i >> k & 1) {
                    f[i] = -INF;
                } else {
                    f[i] = max(f[i], f[i ^ 1 << k]) + len * __builtin_parity(i);
                }
            }
        }
    }
    printf("%d\n", f[0]);
    return 0;
}

```


---

## 作者：Exschawasion (赞：18)

好题。想通一个点之后就轻松了。

$k \leq 8$，肯定要状压。但是状压什么呢？肯定是要状压当前线段的覆盖状况，但是 $2\times 10^5$ 怎么状压？

打过定轨音游的都知道所谓的**轨道**。它的本质就是：**任何一个**线段都会在**某个单一的轨道**中固定移动。如下图，$7$ 条线段被放进了 $3$ 个轨道中。

![](https://s3.uuu.ovh/imgs/2022/11/23/f601fe441ac0415e.png)

这道题里，每个位置都只会被最多 $8$ 个线段覆盖，也就是说，所有线段一定可以**无重叠**地放置进 $8$ 个轨道。因此只要记录当前位置的所有轨道上是否有线段即可。

现在问题是如何把线段放进轨道里。直接扫描线过去，开一个 `vis` 数组记录轨道是否占用即可。之后，第 $i$ 条线段将拥有一个编号 $id_i$ 表示所在轨道的编号。

转移就很显然了。枚举 $2n$ 个线段的端点，再枚举 $2^8-1=255$ 种状态，直接转移即可。注意判断当前枚举到的端点是左端点还是右端点、状态的 `popcount` 个数是奇数还是偶数。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100000+5;
struct seg{
	int x,id;
	int tag;//1=insert,0=delete
	bool operator<(const seg&s)const{
		if(x!=s.x)return x<s.x;
		else return tag<s.tag;
	}
};
vector<seg>Q;
int n,m,k;
int f[256+5];
inline int chk(int x){
	return __builtin_popcount(x)%2==1;
}
int used[8];
int ID[maxn];
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	memset(f,-0x3f,sizeof(f));
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		int l,r;cin>>l>>r;
		Q.emplace_back((seg){l,i,1});
		Q.emplace_back((seg){r+1,i,0});//note: r+1
	}
	sort(Q.begin(),Q.end()),f[0]=0;
	for(auto a:Q){
		if(a.tag){
			for(int i=0;i<8;i++)if(!used[i]){
				used[i]=1,ID[a.id]=i;
				break;
			}
		}
		else used[ID[a.id]]=0;
	}
	for(unsigned i=0;i<Q.size();i++){
		seg cur=Q[i];
		int id=ID[cur.id];
		if(cur.tag){
			for(int S=(1<<8)-1;~S;S--){
				int v=(i+1<Q.size()?(Q[i+1].x-Q[i].x):0);
				if(!chk(S))v=0;
				if((S>>id)&1)f[S]=f[S^(1<<id)]+v;
				else f[S]=f[S]+v;
			}
		}
		else{
			for(int S=0;S<(1<<8);S++){
				if(!((S>>id)&1)){
					if(chk(S))f[S]=max(f[S],f[S^(1<<id)])+(i+1<Q.size()?(Q[i+1].x-Q[i].x):0);
					else f[S]=max(f[S],f[S^(1<<id)]);
				}
				else{
					f[S]=-0x3f3f3f3f;
				}
			}
		}
	}
	cout<<f[0];
}
```



---

## 作者：YLWang (赞：10)

比较套路的小清新题。被 B 坑了导致没写完。~~但莫名其妙地上分了~~

我们考虑先离散化每一条线段。注意因为需要维护出每一个离散点所代表的大小，需要把线段左端点左边的点也放进去离散。这是常见套路。

注意到 $k$ 只有 $8$， 这启示我们使用一个 $O(n \times 2^k)$的算法。

然后设 $dp_{i, st}$ 表示当前到了第 $i$ 个点，覆盖它的线段的状态为 $st$ 。其中 $st$ 为一个八位二进制数。$st$ 的第 $k$ 位为 $1$ 表示覆盖点 $i$ 的第 $k$ 条线段取了。反之相反。

我们枚举 $st$，考虑 $i$ 和 $i-1$ 的所有覆盖着的线段的关系。

- 存在连着的线段（设为第 $k$ 条）。则若$st_k = 1$，必须取上一个的第 $k$ 位

- 存在 $i$有，$i-1$没有的线段（设为第 $k$ 条）。则不会影响。

- 存在 $i$没有，$i-1$有的线段（设为第 $k$ 条）。则$i-1$的这些线段可以任意取。

那么转移方程就很显然了。

注意滚动一下，卡卡常数。

```cpp
const int MAXN = 400005;
struct Line {
	int l, r;
	bool operator < (const Line b) const {return l != b.l ? l < b.l : r < b.r;}
}p[MAXN];
int disc[MAXN], dcnt = 0, n, m, K, t, used[MAXN], id[9][MAXN], ed[9][MAXN], mst[MAXN], mask[MAXN], f[2][1 << 9];
int siz[MAXN], adt[1 << 9];
void init() {
	sort(disc + 1, disc + 1 + dcnt);
	t = unique(disc + 1, disc + 1 + dcnt) - disc - 1;
	For(i, 1, n) {
		p[i].l = lower_bound(disc + 1, disc + 1 + t, p[i].l) - disc;
		siz[p[i].l] = disc[p[i].l] - disc[p[i].l-1];
		p[i].r = lower_bound(disc + 1, disc + 1 + t, p[i].r) - disc; 
		siz[p[i].r] = disc[p[i].r] - disc[p[i].r-1];
	}
	For(i, 1, t) siz[i] = disc[i] - disc[i-1];
}
signed main()
{
	cin >> n >> m >> K;
	For(i, 1, n)
		p[i].l = read(), p[i].r = read(), disc[++dcnt] = p[i].l, disc[++dcnt] = p[i].r, disc[++dcnt] = max(p[i].l - 1, 1);
	init();
	sort(p + 1, p + 1 + n);
	For(i, 0, K-1) {
		int lst = 0, cnt = 0;
		For(j, 1, n) {
			if(!used[j] && p[j].l > lst) {
				lst = p[j].r; used[j] = 1; cnt++;
				For(k, p[j].l, p[j].r)
					id[i][k] = cnt;
				ed[i][p[j].r] = 1;
			}
		}
	}
	
	For(j, 1, t)
		For(i, 0, K-1)
			mst[j] |= (1 << i) * (id[i][j] != 0), mask[j] |= (1 << i) * (ed[i][j] == 1);
	For(i, 0, (1 << K) - 1) adt[i] = (__builtin_popcount(i) & 1);
	For(i, 1, t) {
		memset(f[i&1], 0, sizeof(f[i&1]));
		For(j, 0, (1 << K) - 1) {
			if((j | mst[i]) != mst[i]) continue;
			int lst = (j & mst[i-1]) & (mask[i-1] ^ mst[i-1]);
			for(int k = mask[i-1]; k; k = (k - 1) & mask[i-1])
				ckmax(f[i&1][j], f[(i&1)^1][lst | k] + adt[j] * siz[i]);
			ckmax(f[i&1][j], f[(i&1)^1][lst] + adt[j] * siz[i]) ; 
		}
	} 
	int res = 0;
	For(j, 0, (1 << K) - 1) ckmax(res, f[t&1][j]);
	cout << res << endl;
    return 0;
}
```


---

## 作者：AIskeleton (赞：9)

[博客园查看](https://www.cnblogs.com/AIskeleton/p/16281428.html)
## 题目
> [CF1313D Happy New Year](https://codeforces.com/problemset/problem/1313/D)

> 给定 $n,m,k$ 和 $n$ 个区间 $\left[ l_i,r_i \right]$。

> 对于一个长为 $m$ 的初始值为 $0$ 的序列 $a$，在给定的 $n$ 个区间中选择若干个，使序列 $a$ 在区间 $\left[ l_i,r_i \right]$ 之间的值 $+1$，其中保证任何时刻序列 $a$ 中最大值小于 $k$。

> 求问序列中最多奇数个数。

> $1 \le n \le 10^5, 1 \le m \le 10^9,1 \le k \le 8$。

## 题解
### **思路：**
首先注意到 $k$ 的取值范围，可以想到要用**状压**。

对于数据范围 $1 \le m \le 10^9$，显然 $O(m\, 2^k)$ 的时间复杂度无法接受。

可以发现，$n$ 个序列中不同的点最多只有 $2 \times n$ 个，所以进行离散化。
奇偶数之间的转化可以用异或实现。

对于状态 $s$，可以通过 `__builtin_parity()` 函数快速求得其中有奇数个还是偶数个 $1$，返回值为 $1$ 则个数为奇数个，这在 DP 转移时可以用到。
### **预处理：**
应用**差分**的思想，对于一个区间 $\left[ l_i,r_i \right]$，将其拆成 $l_i$ 和 $r_i+1$，分成开始目前区间和结束目前区间两种操作。

具体实现可以用 STL： `vector <pair <int,int> >`，分别存入 $\left( l_i,i \right)$ 和 $\left( r_i+1,-i \right)$，按序列中位置排序。
### **DP**：
设 $f_{i,j}$ 表示离散化后序列第 $i$ 个位置的状态为 $j$ 时，第 $i$ 个位置及其之前的序列中最多的奇数个数，初始值为极小值。

设 $g_{i,j}$ 表示在序列第 $i$ 个位置时，第 $j$ 个对其有影响的区间（没有就是 $0$）。
- 如果当前操作是开始某个区间
遍历数组 $g_i$，找到第一个 $0$ 的位置 $p$，此时 $g_{i,p}$ 即当前区间是第 $p$ 个对位置 $i$ 有影响的区间。
   + 如果状态 $j$ 的第 $p$ 位是 $1$，即状态 $j$ 下加入了当前区间，则 `f[i][j]` 应由 `f[i-1][j^(1<<p)]` 转移而来。
   + 如果状态 $j$ 的第 $p$ 位是 $0$，即状态 $j$ 下未加入当前区间，则 `f[i][j]` 应由 `f[i-1][j]` 转移而来。

对于开始某个区间的转移，其中都要先记录下离散化后当前位置与下一个位置之间的长度 $len$（最后一个位置为 $0$），转移时加上 `len*__builtin_parity(j)`，即当前状态下增加的奇数个数。
- 如果当前操作是结束某个区间
遍历数组 $g_i$，找到当前结束的区间的位置 $p$ 并清空 $g_{i,p}$，具体原因可以结合前文理解。
   + 如果状态 $j$ 的第 $p$ 位是 $1$，即状态 $j$ 下依然存在当前区间，可知状态 $j$ 不合法，所以赋极小值。
   + 如果状态 $j$ 的第 $p$ 位是 $0$，即状态 $j$ 下已不存在当前区间，则 `f[i][j]` 应由两个合法状态 `f[i-1][j]` 和 `f[i-1][j^(1<<p)]` 中的较大值转移而来。
   
     因为当前状态的前一步状态可以本来就没有当前区间即 `f[i-1][j]`，也可以是在位置 $i$ 时去掉了当前区间即 `f[i-1][j^(1<<p)]`。所以取较大值转移。

对于结束某个区间的转移，如果情况合法，也要在转移时加上 `len*__builtin_parity(j)`。
### **优化：**
此时的空间复杂度达到了 $O(2n2^k)$，所以要对空间进行优化。
- 可以发现，对于开始某个区间的 DP 转移，在 `f[i][j]` 由 `f[i-1][j^(1<<p)]` 转移而来的情况下，`j` 一定大于 `j^(1<<p)`。

- 可以发现，对于结束某个区间的 DP 转移，在 `f[i][j]` 由 `f[i-1][j]` 和 `f[i-1][j^(1<<p)]` 中的较大值转移而来的情况下，`j` 一定小于 `j^(1<<p)`。

所以可以将数组 $f$ 的第一维省略掉，即设 $f_i$ 为状态为 $i$ 时的当前位置前的奇数最大值，并对 DP 的转移略为改动：

- 如果操作是开始区间，就逆向遍历所有状态：`for(int i=(1<<k)-1;i>=0;i--)`，转移时也直接去掉第一维即可。

- 如果操作是结束区间，就正向遍历所有状态，可以类比开始区间的操作。

最后的输出值是 $f_0$，也就是序列离散化后最后一个位置在不受任何区间影响时的值。

时间复杂度 $O(n\log_2n+2^k)$，空间复杂度 $O(2^k)$。

完结。
## 代码
```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;int rd(){
	int w=0,v=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')v=-1;c=getchar();}
	while(c>='0'&&c<='9'){w=(w<<1)+(w<<3)+(c&15);c=getchar();}return w*v;
}const int N=8;int n,k,f[1<<N],g[N];vector <pair <int,int> > a;
signed main(){
	n=rd(),rd(),k=rd();for(int i=1,l,r;i<=n;i++)l=rd(),r=rd(),a.pb({l,i}),a.pb({r+1,-i});
	sort(a.begin(),a.end());for(int i=1;i<(1<<k);i++)f[i]=-0x7f;
	for(int v=0,l,b,p;v<a.size();v++){
		b=a[v].second;if(v==a.size()-1)l=0;else l=a[v+1].first-a[v].first;
		if(b>0){
			for(int i=0;i<k;i++)if(!g[i]){g[p=i]=b;break;}
			for(int i=(1<<k)-1;i>=0;i--)
				if(i&(1<<p))f[i]=f[i^(1<<p)]+l*__builtin_parity(i);
				else f[i]+=l*__builtin_parity(i);
		}else{
			for(int i=0;i<k;i++)if(g[i]==-b){g[p=i]=0;break;}
			for(int i=0;i<(1<<k);i++)
				if(i&(1<<p))f[i]=-0x7f;
				else f[i]=max(f[i],f[i^(1<<p)])+l*__builtin_parity(i);
		}
	}cout<<f[0]<<endl;return 0;
}
```

---

## 作者：NaCN (赞：4)

---
title: CF1313D
date: 2020-2-24 12:14:13
tags: dp 
mathjax: true
---
给$n$个区间$[l_i,r_i]$。若选择区间$[l_i,r_i]$，区间上的值$+1$,问求使$[1,n]$点值为奇数的个数最大，最大个数是多少，$1$个点最多被覆盖$k$次。$(n\leq 10^5,l,r\leq 10^9,k\leq 8)$
<!--more-->

---
这题关键点在$k$。显然$2^k*n$复杂度可以接受。由于$l,r$大，把一个点覆盖$k$次，转换为离散化，一个区间最多覆盖$k$次。

$dp[i][j]$表示到$[i]$这个区间，且区间的状态为$j=10101001$,二进制每一位表示他是否含有覆盖自己的区间中的第$k$个。

举个例子$[2,3)$,题目给出$[3,7),[1,5],[2,4),[2,6)...$如果选择$2,4$原区间，$j=101$

### 如何转移?

$seg[i]=[l[i],l[i+1]],len(seg)=li[i+1]-li[i]$

找到都覆盖$seg[i]$与$seg[i-1]$的原区间。若$dp[i-1][st1]$($st1$含有这些区间),就可以转移到$dp[i][st2]$（$st2$也含有这些区间)。

过于唠口,所以借助$tmp[st]=max(tmp[st],dp[i-1][st1])(st1这个状态的区间里含有st)$,然后让其映射到$st2$上。

$
    st|= (st1>>pre[j] \& 1) << j
$
,得到st1对应的st.

$
	st|= (st2>>now[j] \& 1) \<< j
$,得到st2对应的st



    dp[i][st2] = max(dp[i][st2], st[st] + [st2是否有奇数个1]\times len)

+ $pre[]$存的是共有的原区间，再$seg[i-1]$所有覆盖它的第几位。
+ $now[]$存的是共有的原区间，再$now[i-1]$所有覆盖它的第几位。




``` c++

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
const int M = 8;
const int mod = 1e9 + 7;
int li[N], l[N], r[N], num, n;
int dp[N][1 << M], st[1 << M];
vector<int> seg[N];
int m, k;
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &l[i], &r[i]);
        r[i]++;
        li[++num] = l[i];
        li[++num] = r[i];
    }
    sort(1 + li, 1 + li + num);
    num = unique(1 + li, 1 + li + num) - li - 1;
    for (int i = 1; i <= n; i++)
    {
        l[i] = lower_bound(li + 1, li + 1 + num, l[i]) - li;
        r[i] = lower_bound(li + 1, li + 1 + num, r[i]) - li;
        for (int j = l[i]; j < r[i]; j++)
            seg[j].push_back(i);
    }
    int ans = 0;
    for (int i = 1; i < num; i++)
    {
        memset(st, 0, sizeof(st));
        vector<int> pre, now;
        int len = li[i + 1] - li[i];
        for (int t = 0; t < seg[i - 1].size(); t++)
            for (int k = 0; k < seg[i].size(); k++)
                if (seg[i - 1][t] == seg[i][k])
                    pre.push_back(t), now.push_back(k);
        int pst = 1 << seg[i - 1].size(), nst = 1 << seg[i].size();
        for (int s = 0; s < pst; s++)
        {
            int ss = 0;
            for (int j = 0; j < pre.size(); j++)
                ss |= (s >> pre[j] & 1) << j; //s这个状态里是否含有pre[j]
            st[ss] = max(st[ss], dp[i - 1][s]);
        }
        for (int s = 0; s < nst; s++)
        {
            int ss = 0;
            for (int j = 0; j < now.size(); j++)
                ss |= (s >> now[j] & 1) << j; //s这个状态里是否含有now[j]
            dp[i][s] = max(dp[i][s], st[ss] + (__builtin_popcount(s) & 1) * len);
            ans = max(dp[i][s], ans);//__builtin_popcount(s) 判断二进制有几个1
        }
    }

    printf("%d\n", ans);
}
```




---

## 作者：chenxia25 (赞：3)

我在[1313E的题解](https://www.luogu.com.cn/blog/Chenxiao-Yan/CodeForces-1313E)里提到本题非常难，~~是我出言不逊了。。~~ 我之前读错题意了。。

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF1313D) & [CodeForces题目页面传送门](https://codeforces.com/contest/1313/problem/D)

>有$m$孩子，编号为$1\sim m$。有$n$条咒语，第$i$条可以让编号在$[l_i,r_i]$内的所有孩子得到$1$颗糖，每条咒语可以施或不施。要求最大化得到奇数颗糖的孩子的数量。输出这个数量。保证若施所有咒语，那么每个孩子得到的糖的数量不超过$s$。

>$n\in
\left[1,10^5\right],m\in\left[1,10^9\right],s\in[1,8]$。

“保证若施所有咒语，那么每个孩子得到的糖的数量不超过$s$”这句话极其重要，它告诉我们每个孩子都在不超过$s$条咒语的区间里，即每个孩子都只有不超过$s$条咒语对他/她有效。这启示我们对每个孩子枚举所有对他/她有效的$x$条咒语哪些施、哪些不施的$2^x$种情况，从而状压DP。

DP之前，这个$m$的范围一看就是要离散化。我们把$\forall i\in[1,n],l_i-1,r_i$这$2n$个数压入即将`sort`、`unique`的1-indexed数列$nums$里，`sort`、`unique`之后，$\forall i\in[1,|nums|]$，今后的数$i$就代表从前的区间$(nums_{i-1},nums_i]$，特殊地，$nums_0=0$。这样可以保证今后的每个孩子代表的从前的区间内每个数所在咒语区间情况相同，因为咒语区间的端点代表所在咒语区间情况相同段的分界。但还有一个问题：有可能从前的某个后缀内的数都没有被包含到任何今后的数所表示的区间里。很简单，只要再往$nums$里加一个数$m$即可。时间复杂度$\mathrm O(n\log_2n)$。

接下来考虑DP。先预处理出0-indexed数列数组$in$，$in_i$表示今后的数$i$所表示的从前的区间内每个孩子所在的咒语区间编号组成的数列（对于区间内每个孩子生成的数列都是一样的），顺序随意。这样一来，$\forall i\in[1,n],\forall j\in[1,|nums|]$，若$\forall k\in(nums_{j-1},nums_j],k\in[l_i,r_i]$，则咒语$i$对于今后的数$j$便有了一个新编号。显然，预处理这个数列数组的时间复杂度为$\mathrm O(ns)$。

设$dp_{i,j}$表示考虑到今后的数$i$，对于bitmask$j$满足$x\in j$当且仅当施咒语$in_{i,x}$时，前$nums_i$个孩子得到奇数颗糖的最大的数量。显然边界是$dp_{0,0}=0$，目标是$\max\limits_i\{dp_{|nums|,i}\}$。转移时只需要注意$1$个限制：$\{in_{i}\}$和$\{in_{i-1}\}$可能交集不为空，此时那些交集里的咒语不能精神分裂，即$\forall x\in\{in_{i}\}\cap\{in_{i-1}\}$，咒语$x$在$j$和转移到的bitmask$k$里状态必须相等。

那么状态转移方程是：

$$dp_{i,j}=\max\limits_{cantrs(i,j,k)}\{dp_{i-1,k}+|j|\bmod2\times(nums_i-nums_{i-1})\}$$

其中$cantrs(i,j,k)$表示$dp_{i,j}$转移到$dp_{i-1,k}$满足上述限制。

这样直接按方程来转移的话，状态数$\mathrm O(2^sn)$，每次转移对象$\mathrm O(2^s)$，$cantrs$判断$\mathrm O(s)$，所以时间复杂度是$\mathrm O(4^sns)$，太大了。显然我们最多只能接受$\mathrm O(2^sn)$的。

注意到若对于$2$个状态$j_1,j_2$，$\forall x\in\{in_{i}\}\cap\{in_{i-1}\}$，咒语$x$在$j_1,j_2$内的状态相同，那么$dp_{i,j_1},dp_{i,j_2}$能转移到的合法状态集合是完全相同的。于是设$and_i=\{in_{i}\}\cap\{in_{i-1}\}$，我们可以按$and$内所有元素的$2^{|ans|}$种状态分类，这样对每类统一找合法转移对象，计算对于此类中所有bitmask$j$，$\max\limits_{cantrs(i,j,k)}\{dp_{i-1,k}\}$，然后对于此类中所有状态$\mathrm O(1)$计算DP值。但是复杂度依然没有变。

要想改变复杂度，最重要的是去除$cantrs$判断。注意到$\forall k$，$dp_{i-1,k}$能且仅能转移到$1$个状态，于是我们若能找到命中率$100\%$且不用判断的找合法转移对象方式就能保证$\mathrm O(2^sn)$的复杂度。这非常简单，只需要将每个$k$拆成$\in and$和$\notin and$这$2$部分，对于每类，直接固定$\in and$的部分，枚举$\notin and$的部分即可。但是实现起来并不会那么顺利，因为$2$部分分别可能在$k$中不连续，无法直接用位运算$\mathrm O(1)$合并，于是我们可以预处理，对于$2$个部分都给此部分每种状态编个号，并记录它在$k$中的状态，最后将$2$部分在$k$中的状态$\mathrm{or}$起来即可得到$k$。对于每类，现在已经找到所有合法转移对象，即算出了对于此类中所有bitmask$j$，$\max\limits_{cantrs(i,j,k)}\{dp_{i-1,k}\}$，现在只需再命中率$100\%$且不用判断地找到此类中所有状态（方法和上述找转移对象类似），即可$\mathrm O(1)$得到每个$dp_{i,j}$的值。

最终总复杂度为$\mathrm O(n\log_2n)+\mathrm O(ns)+\mathrm O(2^sn)=\mathrm O(n(\log_2n+2^s))$，轻微卡常，但不用在意。

下面上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
int lowbit(int x){return x&-x;}
int lbt(int x){return __builtin_ctz(x);}
const int N=100000;
int n/*咒语数*/,m/*孩子数*/,s/*每个孩子最多在的咒语区间数量*/;
int l[N+1],r[N+1];//咒语区间 
vector<int> nums;//离散化数组 
void discrete(){//离散化 
	sort(nums.begin(),nums.end());
	nums.resize(unique(nums.begin(),nums.end())-nums.begin());
	for(int i=1;i<=n;i++)
		l[i]=lower_bound(nums.begin(),nums.end(),l[i])-nums.begin(),
		r[i]=lower_bound(nums.begin(),nums.end(),r[i])-nums.begin();
}
vector<int> in[3*N+1];//所在咒语区间编号数列数组 
vector<int> dp[3*N+1];//DP数组 
int main(){
	cin>>n>>m>>s;
	nums.pb(0);nums.pb(m); 
	for(int i=1;i<=n;i++)scanf("%d%d",l+i,r+i),nums.pb(l[i]-1),nums.pb(r[i]);
	discrete();
	for(int i=1;i<=n;i++)for(int j=l[i];j<=r[i];j++)in[j].pb(i);//预处理 
	dp[0].resize(1,0);//边界 
	for(int i=1;i<nums.size();i++){
//		printf("%d dping\n",i);
//		printf("\tin=",i);for(int j=0;j<in[i].size();j++)cout<<in[i][j]<<" ";puts("");
		dp[i].resize(1<<in[i].size());//决定dp[i]元素个数 
		vector<pair<int,int> > _and;//对于所有x in {in[i]} cap {in[i-1]}，(x在in[i]中的编号，x在in[i-1]中的编号)组成的二元组序列 
		for(int j=0;j<in[i].size();j++)for(int k=0;k<in[i-1].size();k++)if(in[i][j]==in[i-1][k])_and.pb(mp(j,k));//预处理and 
//		printf("\t_and=");for(int j=0;j<_and.size();j++)printf("(%d,%d) ",_and[j].X,_and[j].Y);puts("");
		vector<int> nin_and1/*j中不在and中的部分*/,nin_and2/*k中不在and中的部分*/; 
		for(int j=0,k=0;j<in[i].size();j++)if(k>=_and.size()||(j==_and[k].X?k++,false:true))nin_and1.pb(j);//预处理nin_and1 
		for(int j=0,k=0;j<in[i-1].size();j++)if(k>=_and.size()||(j==_and[k].Y?k++,false:true))nin_and2.pb(j);//预处理nin_and2 
//		printf("\tnin_and1=");for(int j=0;j<nin_and1.size();j++)cout<<nin_and1[j]<<" ";puts("");
//		printf("\tnin_and2=");for(int j=0;j<nin_and2.size();j++)cout<<nin_and2[j]<<" ";puts("");
		vector<int> chg1(1<<_and.size(),0),chg2(1<<nin_and1.size(),0),chg3(1<<_and.size(),0),chg4(1<<nin_and2.size(),0);
		for(int j=1;j<chg1.size();j++)chg1[j]=chg1[j^lowbit(j)]|1<<_and[lbt(j)].X;//预处理j中在and中的部分的每种状态在j中的状态 
		for(int j=1;j<chg2.size();j++)chg2[j]=chg2[j^lowbit(j)]|1<<nin_and1[lbt(j)];//预处理j中不在and中的部分的每种状态在j中的状态
		for(int j=1;j<chg3.size();j++)chg3[j]=chg3[j^lowbit(j)]|1<<_and[lbt(j)].Y;//预处理k中在and中的部分的每种状态在j中的状态
		for(int j=1;j<chg4.size();j++)chg4[j]=chg4[j^lowbit(j)]|1<<nin_and2[lbt(j)];//预处理k中不在and中的部分的每种状态在j中的状态
		for(int j=0;j<chg1.size();j++){//枚举类 
			int mx=0;//对于此类中所有bitmask j，max[cantrs(i,j,k)]{dp[i-1][k]} 
			for(int k=0;k<chg4.size();k++)mx=max(mx,dp[i-1][chg3[j]|chg4[k]]);//算mx 
			for(int k=0;k<chg2.size();k++)dp[i][chg1[j]|chg2[k]]=mx+__builtin_parity(chg1[j]|chg2[k])*(nums[i]-nums[i-1]);//转移此类中的每个状态 
		}
//		for(int j=0;j<dp[i].size();j++)printf("\tdp[%d]=%d\n",j,dp[i][j]);
	}
	cout<<*max_element(dp[nums.size()-1].begin(),dp[nums.size()-1].end());//目标 
	return 0;
}
```

---

## 作者：Jadonyzx (赞：2)

**状压 dp 好题**

观察数据范围，感觉这个 $k$ 大小很奇怪，考虑状压 dp。

显然不是什么一维 dp，考虑另一维的定义。

$O(2^kn)$ 和 $O(2^km)$ 的空间复杂度都可以接受，那么是哪一个呢？

$n$ 个咒语具有后效性，不妨选择 $m$。

因此我们需要对所有的 $l$ 和 $r$ 进行离散化，将整个数轴离散成点和线段。

不妨设 $dp_{i,S}$ 表示考虑到第 $i$ 个点，对于这个点选择了集合 $S$ 作为覆盖它的咒语时的最大快乐孩子数。

那么很自然地想到转移分为两种：

1.由 $i-1$ 向 $i$ 转移，若令 $T$ 为覆盖 $i$ 的线段集合，则用 $dp_{i-1,S}$ 向 $dp_{i,S\cap T}$ 转移。

2.由 $i$ 向 $i$ 转移，转移很显然。

实现留给读者思考。

---

## 作者：RockyYue (赞：2)

### 题意

有 $n$ 个操作，$m$ 个数，初始为 $0$，每次操作表示为 $(l,r)$，表示可以对 $[l,r]$ 这一段数区间 $+1$，每一位最多受到 $k$ 个操作。求选择若干操作执行后最大的奇数个数。

其中 $n\le 10^5,m\le 10^9,k\le 8$。

### 解法

考虑前缀和，将一次操作拆分为两次单点操作：```++s[l]```和```--s[r+1]```，定义 $l$ 为操作起始点，$r+1$ 为操作终止点。我们对每个操作点记录一个 $id$，对于第 $i$ 次操作，起始点 $id$ 为 $i$，终止点 $id$ 为 $-i$，这样我们可以方便地判断操作点类型和匹配情况。

我们对操作点进行按位置排序，要注意的是若位置相同，优先终止点，为了防止这一段的操作点过多。

那么便可以按操作来划分区间处理。设 $f_{i,j}$ 为考虑第 $i$ 个操作点到第 $i+1$ 个操作点前这部分区间（我们定义这一段为操作段 $i$），对于对这部分区间有影响的所有起始点选择状态为 $j$。这里有必要解释一下：

1. 如果一次个起始点对应终止点也被选择包括，那么这个点就不予考虑，这样即可以保证 $j$ 的大小，也可以只考虑起始点。

2. 选择状态是指将这些有影响的起始点编号（最多 $1$ 到 $8$)，$j$ 的第 $i$ 位为 $1$ 表示编号为 $i$ 的操作点被选择。
3. 注意这里的操作点集中，点的实际编号不需要有序，我们只需要在上一次的基础上改变最多一个位（因为操作段 $i$ 只会增加操作点 $i$，这样遇到起始点增加或需要终止点取消操作即可），这样可以方便转移。

接下来考虑转移。对于操作段 $i$，我们用 $vis$ 数组（下标 $0$ 到 $7$）记录当前段相关的 $id$（当前位为空则 $0$），同时记 $len$ 为这一段长度。

1. 先用点 $i$ 更新 $vis$ 数组，同时记 $k$ 为 $vis$ 中改变位的编号（详见代码）。

2. 然后枚举这一段的选择状态 $j$，进行转移，记 $p$ 为 $j$ 中 $1$ 的个数 $\bmod$ $2$，用来更新这一次的答案。这里对两种操作点类型分别说明。

   - 点 $i$ 为起始点

     我们用没有第 $k$ 位的状态更新当前状态的答案，即```f[i][j]=f[i-1][min(j,j^(1<<t)]+len*p```。

   - 点 $i$ 为终止点

     这时候就要注意状态不合法的情况了，即这一个操作已经结束了，但是状态中还有这一位。具体地，```if((j>>t)&1) f[i][j]=-1e9```

     否则，这个时候要选择是否选择点 $i$ 对应的操作，因为状态并不能表示这个的选择状态，即```f[i][j]=max(f[i-1][j],f[i-1][j+(1<<t)])+len*p```。

转移完毕，这时候我们发现第一维可以滚动，注意当 $i$ 为起始点是要状态从大往小更新，最后答案则为 $f[0]$，初始化 $f[0]=0$，因为最后的操作点后面一定是不会选择任何操作点的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int K = 8;
struct Op {
	int pos, id;
	bool operator < (const Op& rhs) const {
		if (pos != rhs.pos) return pos < rhs.pos;
		return id < rhs.id;
	}
};
vector<Op> op;
int f[1 << K], vis[K], popcnt[1 << K];
signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n, m, k; cin >> n >> m >> k;
	for (int i = 1; i < (1 << k); ++i) popcnt[i] = popcnt[i >> 1] + (i & 1);
	for (int i = 1; i <= n; ++i) {
		int l, r; cin >> l >> r;
		op.push_back({l, i}), op.push_back({r + 1, -i});
	}
	sort(op.begin(), op.end());
	memset(f, ~0x3f, sizeof f); f[0] = 0;
	for (int i = 0; i < (int)op.size(); ++i) {
		int id = op[i].id, t, len = (i == (int)op.size() - 1) ? 0 : op[i + 1].pos - op[i].pos;
		if (id > 0) {
			for (int j = 0; j < k; ++j) {
				if (vis[j] == 0) { t = j, vis[j] = id; break; } 
			}
			for (int j = (1 << k) - 1; j >= 0; --j) f[j] = f[min(j, j ^ (1 << t))] + len * (popcnt[j] & 1);
		} else {
			for (int j = 0; j < k; ++j) {
				if (vis[j] == -id) { t = j, vis[j] = 0; break; }
			}
			for (int j = 0; j < (1 << k); ++j) {
				if ((j >> t) & 1) f[j] = -1e9;
				else f[j] = max(f[j], f[j + (1 << t)]) + len * (popcnt[j] & 1);
			}
		}
	}
	cout << f[0] << '\n';
	return 0;
}
```

---

## 作者：lyhqwq (赞：1)

# Solution

小清新 dp。

$m$ 很大，但有用的关键点很小，考虑将每个咒语的关键点离散化。

我们从左往右扫，状压每个点被覆盖的状态，令 $f_{i,S}$ 表示第 $i$ 个关键点，覆盖的状态为 $S$，的答案。

我们给每个咒语钦定一个覆盖的位置 $id$，转移时让 $f_{i,S}\gets f_{i-1,S^\prime}+val\times \operatorname{popcount}(S)$。其中 $val$ 表示这个关键点到下一个关键点之间的点的个数，$S^\prime$ 表示加入第 $i$ 个咒语后新的覆盖状态。

最后的答案为 $f_{2\times n,0}$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
const int INF=2147483747;
struct node{
    int id,x,op;
    bool operator < (const node &rhs)const{
        if(x!=rhs.x) return x<rhs.x;
        else return op<rhs.op;
    }
}a[N];
int n,m,k;
int vis[8],id[N];
int f[(1<<8)];
int popcnt(int x){
    int res=0;
    for(int i=x;i;i-=(i&(-i))) res++;
    return res%2==1;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1,l,r;i<=n;i++){
        scanf("%d%d",&l,&r);
        a[2*i-1]=(node){i,l,1};
        a[2*i]=(node){i,r+1,0};
    }
    sort(a+1,a+1+2*n);
    for(int i=1;i<=2*n;i++){
        if(a[i].op){
            for(int j=0;j<=7;j++){
                if(!vis[j]){
                    id[a[i].id]=j,vis[j]=1;
                    break;
                }
            }
        }
        else vis[id[a[i].id]]=0;
    }
    for(int i=1;i<(1<<8);i++) f[i]=-INF;
    for(int i=1;i<=2*n;i++){
        int _id=id[a[i].id],len=(i==2*n?0:a[i+1].x-a[i].x);
        if(a[i].op){
            for(int S=(1<<8)-1;~S;S--){
                if((S>>_id)&1) f[S]=f[S^(1<<_id)]+popcnt(S)*len;
                else f[S]=f[S]+popcnt(S)*len;
            }
        }
        else{
            for(int S=0;S<(1<<8);S++){
                if(!((S>>_id)&1)) f[S]=max(f[S],f[S^(1<<_id)])+popcnt(S)*len;
                else f[S]=-INF;
            }
        }
    }
    printf("%d\n",f[0]);
    return 0;
}

```

---

## 作者：tder (赞：0)

在数轴上有 $n$ 条线段 $[L,R]$，从中选取若干条组成 $c$，试最大化 $\displaystyle\sum_{i=1}^m\left[\left(\sum_{j\in c}\left[L_j\le i\le R_j\right]\right)\bmod2=1\right]$。保证对于 $1\le i\le m$ 都有 $\displaystyle\left(\sum_{j=1}^n\left[L_j\le i\le R_j\right]\right)\le k\le8$。

考虑状压 dp，分开处理左右端点 $\{p_{n\times2}\}$，按点的坐标排序。用 $f_{i,\text{msk}}$ 表示到第 $i$ 个端点当前覆盖的线段集为 $\text{msk}$ 的答案。

在转移时，分左右端点两种情况分开考虑，参考 [George1123 的题解](https://www.luogu.com.cn/article/rs5029y4)。

而最终的答案即为选完所有 $n\times2$ 个点且最终没有被任何线段覆盖的答案，即 $f_{n\times2,\varnothing}$。

---

## 作者：L_zaa_L (赞：0)

状压 dp 题。

对于 $m$ 我们发现他非常的大，我们复杂度不好带，不妨先将他离散化一下，把每个端点都提取出来，然后经过每个点的线段又非常的少，我们可以考虑进行状压 dp。
 
我们记 $dp_{i,j}$ 表示我们到达了第 $i$ 个端点，然后选择覆盖的区间的情况为 $j$ 时的答案最大值。然后就直接  dp：

$\begin{cases}dp_{i,j}\gets dp_{i-1,j\oplus 2^k}+(|j|\mod 2)\times(q_{i+1}-q_i)&(id_i\ge 0\land (i\operatorname{and} 2^k))\\ dp_{i,j}\gets dp_{i-1,j}+(|j|\mod 2)\times(q_{i+1}-q_i)&(id_i\ge 0\land \neg (i\operatorname{and}  2^k))\\ dp_{i,j}\gets -\inf&(id_i< 0\land (i\operatorname{and}  2^k))\\ dp_{i,j}\gets\max(dp_{i-1,j},dp_{i,j\oplus 2^k})+(|j|\mod 2)\times(q_{i+1}-q_i)&(id_i<0\land \neg (i\operatorname{and}  2^k))\\ \end{cases}$

$q_i$ 代表每个端点的位置，$id_i$ 表示这个点区间的编号。

然后压维一下保证空间不超就行了。

时间复杂度：$O(n2^k)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e6+5;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
//inline void Add(int &x,int y){(x=x+y+Mod)%Mod;}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
int n,m,k;
int dp[N],c2[N],g[N];
vector<pair<int,int> > q;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++){
		int l=read(),r=read();
		q.push_back({l,i});
		q.push_back({r+1,-i});
	}
	sort(q.begin(),q.end());
	for(int i=1;i<(1<<k);i++){
		c2[i]=c2[i>>1]+(i&1);
	}
	for(int i=0;i<(1<<k);i++)c2[i]=(c2[i]&1);
	for(int i=1;i<(1<<k);i++) dp[i]=-1e16;
	for(int j=0;j<q.size();j++){
		int b=q[j].second;
		int len=0;
		if(j==q.size()-1) len=0;
		else len=q[j+1].first-q[j].first;
//		cout<<b<<" "<<len<<endl;
//		cout<<len;
		if(b>=0){
			int gg=0;
			for(int i=0;i<k;i++){
				if(!g[i]){
					g[i]=b;
					gg=i;
					break;
				}
			}
//			cout<<gg<<endl;
			for(int i=(1<<k)-1;i>=0;i--){
				if(i&(1<<gg)) dp[i]=dp[i^(1<<gg)]+len*c2[i];
				else dp[i]=dp[i]+len*c2[i];
			}
		}
		else{
			int gg=0;
			for(int i=0;i<k;i++){
				if(g[i]==abs(b)){
					g[i]=0;
					gg=i;
					break;
				}
			}
//			cout<<gg<<endl; 
//			cout<<1;
			for(int i=0;i<(1<<k);i++){
				if(i&(1<<gg)) dp[i]=-1e16;
				else chmx(dp[i],dp[i^(1<<gg)]),dp[i]+=len*c2[i];
			}
		}
//		for(int i=0;i<(1<<k);i++){
//			cout<<dp[i]<<" ";
//		}
//		cout<<endl;
	}
	cout<<dp[0]<<endl;
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：123456xwd (赞：0)

## [ [CF1313D] Happy New Year](https://www.luogu.com.cn/problem/CF1313D)

### 一，题目：

**题目大意：**

给你一个长度为 $m$ 的序列 $a$，初始值为 0，现在有 $n$ 个操作，第 $i$ 个操作是将区间 $[L_i,R_i]$ 内的元素的值都加 1，你可以选择进行任意个操作，旦每个操作都只能进行一次。问你最多可以使得多少个元素的值为奇数。

题目会保证若将所有操作都进行后，每个元素最大为 $k$。

**数据范围：**

$1\le n \le 1\times 10^{5},1\le m \le 1\times 10^{9},1\le k \le 8$。

**读入格式：**

第一行 $n,m,k$。

接下来的 $n$ 行，第 $i+1$ 行为 $L_i,R_i$。

##### 样例输入：

```
3 5 3
1 3
2 4
3 5
```

##### 样例输出：

```
4
```



### 二，solution：

先把题意转化一下。

我们可以把 $a$ 抽象为一个长度为 $m$ 的数轴，每个操作其实就是用一个线段覆盖 $[L_i,R_i]$ 这个区间，问你最多有几个点被覆盖被覆盖了奇数次，如下图（是样例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/ru1odqc3.png)

而，看到这个 $k\le 8$，（代表一个点最多被 $k$ 条线覆盖），自然而然的想到状压。

不妨设 $f[i][S]$ 表示第 $i$ 个点被集合为 $S$ 的这些线覆盖住。

但是，这个集合 $S$ 中每一位所代表的点是一直在变化的，怎么办呢？

我们设 $vis[i]$ 表示当前 $S$ 的第 $i$ 位代表的线段的编号，在每次有线段加入、退出的时候，利用 $vis$ 进行更改即可。

加入：

```c++
for(int j=0;j<k;j++){
    if(vis[j]==0){
        now=j;//now表示当前处理到的线段对应的二进制位
        vis[j]=id;//标记一下
        break;
    }
}
```

退出：

```c++
for(int j=0;j<k;j++){
    if(-id==vis[j]){
        vis[j]=0;//清空
        now=j;//now表示当前处理到的线段对应的二进制位
        break;
    }
}
```

但是 $M$ 最大有 $10^{9}$，时间复杂度为 $\mathcal{O}(M\times 2^k)$，绝对过不了，若不进行滚动数组优化的话空间也受不了。

**需要优化**。

我们发现，操作的个数是 $1\times 10^{5}$，若把上面的那个 $M$ 换为 $N$，就可以接受了。

不妨把每个操作抽象为两个二元组扫描线 $(L_i,i)$ 和 $(R_i+1,-i)$。（第二位为整数表示是一个操作的开头，否则为结尾），分别表示从这个点开始就多了、少了一条线段。

这样子，最多会有 $2\times n$ 个点，空间复杂度可以接受。

我们在把这些扫描线按照第一项排序后，很明显，在相邻的两条扫描线中间的元素被覆盖的情况是可以用同一个二进制数表示的。

设 $f_{i,S}$ 表示第 $i$ 个操作点被集合为 $S$ 的这些线覆盖住。（则代表当前这个扫描线到下一条扫描线之间的左闭右开的区间被覆盖情况都为 $S$）。

好了，接下来正儿八经的推式子。

设 $len$ 表示当前这个扫描线到下一条扫描线的长度，$now$ 表示当前的扫描线在 $S$ 中对应的二进制位，$ask(S)$ 表示 $S$ 二进制下是否有奇数个一。

若这个扫描线为线段的左端点，则：
```c++
for(int j=0;j<(1<<k);j++){
	if((j>>now)&1) f[i][j]=f[i-1][j^(1<<now)]+len*ask(j);
	else f[i][j]=f[i-1][j]+len*ask(j);
}
```
若这个扫描线为线段的右端点，则：
```c++
for(int j=0;j<(1<<k);j++){
	if((j>>now)&1) f[i][j]=0xcfcfcfcf;
	else f[i][j]=max(f[i-1][j],f[i-1][j^(1<<now)])+len*ask(j);			
}
```
初始化时，其他 $f_{i,j}$ 都为 $-INF$，$f_{0,0}=0$。

$f_{n\times 2,0}$ 即为所求，因为最后一个扫描线一定是代表右端点，则他一定不会被任何一条线覆盖。

好了，最后注意一下，将扫描线进行排序时，同一个点上，代表右端点的扫描线因该在左端点的扫描线前。

另外，这道题其实可以用将第一维优化掉或者用滚动数组，感兴趣的可以写一写。

代码：

```c++
#include<bits/stdc++.h>
#define ll long long
#define m_p make_pair
using namespace std;
const int N=1e5+5,K=8;
int n,m,k;
int f[N*2][(1<<K)];//到第i条线时，用了的线的集合为j，最多高兴的孩子的数量 
vector<pair<int,int> > a;
int vis[K];

inline int ask(int x){//x二进制下是否有奇数个一。
	int sum=0;
	while(x){
		if(x&1) sum++;
		x>>=1;
	}
	return (sum&1);
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	int l,r;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l,&r);
		a.push_back(m_p(l,i));
		a.push_back(m_p(r+1,-i));//处理为两条扫描线
	}
	sort(a.begin(),a.end());//进行排序
    //初始化：
	memset(f,0xcf,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n*2;i++){
		int id=a[i-1].second;
		int len= (a[i-1].first==a[n*2-1].first) ? 0 : a[i].first-a[i-1].first;//注意，最后一个点的扫描线代表的区间长度为0
		int now;//当前的扫描线在对应的二进制位
		if(id<0){//右端点 
			for(int j=0;j<k;j++){
				if(-id==vis[j]){
					vis[j]=0;
					now=j;
					break;
				}
			}
			for(int j=0;j<(1<<k);j++){
				if((j>>now)&1) f[i][j]=0xcfcfcfcf;
				else f[i][j]=max(f[i-1][j],f[i-1][j^(1<<now)])+len*ask(j);
			}
		}
		else{//左端点 
			for(int j=0;j<k;j++){
				if(vis[j]==0){
					now=j;
					vis[j]=id;
					break;
				}
			}
			for(int j=0;j<(1<<k);j++){
				if((j>>now)&1) f[i][j]=f[i-1][j^(1<<now)]+len*ask(j);
				else f[i][j]=f[i-1][j]+len*ask(j);
			}
		}
	}
	cout<<f[n*2][0];//最后一个扫描线一定是代表右端点，则他一定不会被任何一条线覆盖。
	return 0;
} 
```

---

## 作者：Find_Yourself (赞：0)

带有小 trick 的 DP，长知识了。

$m$ 很大，需要离散化。

为了方便，采用扫描线的方式，不对其进行实际意义上的离散，而是对于第 $i$ 个区间 $[l,r]$，插入 $(l,i),(r+1,-i)$ 两个 pair，最后排个序。这样相邻两个 pair 之间的部分就缩成了一个点。

同时我们还发现 $k\le 8$，也就是说经过每个点的区间个数不超过 $8$。于是在遍历每一个点的时候，我们记录当前有哪些区间经过它，并给它们编号（小于等于 $8$）。

定义 $f_{i,j}$ 表示已经遍历到第 $i$ 个点，经过点 $i$ 的所有区间中被选的状态为 $j$，最大的快乐值。

定义 $\operatorname{chk}(j)$ 表示集合 $j$ 中有奇数个元素还是偶数个元素。如果是奇数个，返回 $1$；否则返回 $0$。

定义 $len$ 表示当前点对应的实际长度。

转移分两类讨论。

1. 新遍历到了一个区间：

	- 选：$f_{i,j}=f_{i-1,j-(1<<id)}+len\cdot \operatorname{chk}(j)$
    
    - 不选：$f_{i,j}=f_{i-1,j}+len\cdot \operatorname{chk}(j)$

2. 遍历到了一个区间的结尾，需要删除：

	- 不删（不符合条件）：$f_{i,j}=-inf$
    
    - 删：$f_{i,j}=\max(f_{i-1,j},f_{i-1,j+(1<<k)})+len\cdot \operatorname{chk}(j)$
    
复杂度 $O(nk2^k)$，实际上达不到。

记得滚动数组。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,inf=INT_MAX>>1;
int n,m,k,vis[10],f[N];
pair<int,int>a[N*2];
inline int chk(int x){
  int cnt=0;
  while(x){x-=x&(-x);++cnt;}
  return cnt&1;
}
int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>n>>m>>k;
  for(int i=1;i<=n;++i){
    int l,r;cin>>l>>r;
    a[i]=make_pair(l,i);a[i+n]=make_pair(r+1,-i);
  }
  sort(a+1,a+2*n+1);
  for(int i=1;i<=256;++i)f[i]=-inf;
  for(int i=1;i<=2*n;++i){
    int t=a[i].second,k,len=(i==2*n?0:a[i+1].first-a[i].first);
    if(t>0){
      for(int j=0;j<8;++j)if(!vis[j]){vis[j]=t;k=j;break;}
      for(int j=255;j;--j){
        if((j>>k)&1)f[j]=f[j-(1<<k)]+len*chk(j);
        else f[j]+=len*chk(j);
      }
    }else{
      for(int j=0;j<8;++j)if(vis[j]==-t){vis[j]=0;k=j;break;}
      for(int j=0;j<256;++j){
        if((j>>k)&1)f[j]=-inf;
        else f[j]=max(f[j],f[j+(1<<k)])+len*chk(j);
      }
    }
  }
  cout<<f[0]<<endl;
  return 0;
}

```


---

