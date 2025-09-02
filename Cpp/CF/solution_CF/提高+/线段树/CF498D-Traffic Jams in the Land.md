# Traffic Jams in the Land

## 题目描述

Some country consists of $ (n+1) $ cities, located along a straight highway. Let's number the cities with consecutive integers from $ 1 $ to $ n+1 $ in the order they occur along the highway. Thus, the cities are connected by $ n $ segments of the highway, the $ i $ -th segment connects cities number $ i $ and $ i+1 $ . Every segment of the highway is associated with a positive integer $ a_{i}&gt;1 $ — the period of traffic jams appearance on it.

In order to get from city $ x $ to city $ y $ ( $ x&lt;y $ ), some drivers use the following tactics.

Initially the driver is in city $ x $ and the current time $ t $ equals zero. Until the driver arrives in city $ y $ , he perfors the following actions:

- if the current time $ t $ is a multiple of $ a_{x} $ , then the segment of the highway number $ x $ is now having traffic problems and the driver stays in the current city for one unit of time (formally speaking, we assign $ t=t+1 $ );
- if the current time $ t $ is not a multiple of $ a_{x} $ , then the segment of the highway number $ x $ is now clear and that's why the driver uses one unit of time to move to city $ x+1 $ (formally, we assign $ t=t+1 $ and $ x=x+1 $ ).

You are developing a new traffic control system. You want to consecutively process $ q $ queries of two types:

1. determine the final value of time $ t $ after the ride from city $ x $ to city $ y $ ( $ x&lt;y $ ) assuming that we apply the tactics that is described above. Note that for each query $ t $ is being reset to $ 0 $ .
2. replace the period of traffic jams appearing on the segment number $ x $ by value $ y $ (formally, assign $ a_{x}=y $ ).

Write a code that will effectively process the queries given above.

## 样例 #1

### 输入

```
10
2 5 3 2 3 5 3 4 2 4
10
C 10 6
A 2 6
A 1 3
C 3 4
A 3 11
A 4 9
A 5 6
C 7 3
A 8 10
A 2 5
```

### 输出

```
5
3
14
6
2
4
4
```

# 题解

## 作者：Dilute (赞：7)

[$$\huge\color{darkblue}\texttt{My blog}$$](https://dilute.xyz/2019/09/01/Solutions/Solution-CF498D/)

## 线段树

首先观察数据范围，发现$a_i \le6$，这个是一个非常有用的性质。

发现$\mathrm{lcm}(1, 2, 3, 4, 5, 6)=60$，这个数有一个非常优美的性质：把$t$再$\mod 60$意义下进行不会影响结果的正确性。

接下来继续考虑线段树，对于每个区间$[l, r]$，再对于每个可能的时间$\mod 60$意义下的结果，我们维护如果在达到$l$的时候$t \mod 60 = i$，那么达到$r + 1$需要花费多少时间。

这个玩意儿可以$O(60)$的$push\_up$。

那么我们就可以以$O(n \log n \times 60)$  的优秀复杂度通过此题。

代码：

```cpp
#include<bits/stdc++.h>

#define ll long long
#define INF 2147483647
#define lc(a) ((a) << 1)
#define rc(a) ((a) << 1 | 1)

int inp(){
    char c = getchar();
    while(c < '0' || c > '9')
        c = getchar();
    int sum = 0;
    while(c >= '0' && c <= '9'){
        sum = sum * 10 + c - '0';
        c = getchar();
    }
    return sum;
}

int a[100010];
struct SEG_Tree{
    struct SEG{
        int l;
        int r;
        int f[61];
    }t[400010];

    void push_up(int cur){
        for(int i = 0; i < 60; i++)
            t[cur].f[i] = t[rc(cur)].f[(i + t[lc(cur)].f[i]) % 60] + t[lc(cur)].f[i];
    }

    void build(int cur, int l, int r){
        t[cur].l = l;
        t[cur].r = r;
        if(l == r){
            for(int i = 59; i >= 0; i--)
                t[cur].f[i] = 1 + (i % a[l] == 0);
            return ;
        }
        int mid = (l + r) >> 1;
        build(lc(cur), l, mid);
        build(rc(cur), mid + 1, r);
        push_up(cur);
    }

    void modify(int cur, int x, int c){
        if(t[cur].l == t[cur].r){
            a[x] = c;
            for(int i = 59; i >= 0; i--)
                t[cur].f[i] = 1 + (i % a[x] == 0);
            return ;
        }
        if(x <= t[lc(cur)].r)
            modify(lc(cur), x, c);
        else
            modify(rc(cur), x, c);
        push_up(cur);
    }

    int query(int cur, int l, int r, int x){
        if(t[cur].l > r || t[cur].r < l)
            return 0;
        if(t[cur].l >= l && t[cur].r <= r){
            // printf("[%d, %d].f[%d] = %d\n", t[cur].l, t[cur].r, x, t[cur].f[x]);
            return t[cur].f[x];
        }
        int ls = query(lc(cur), l, r, x);
        return ls + query(rc(cur), l, r, (x + ls) % 60);
    }
}t;

int main(){
    int n = inp();
    for(int i = 1; i <= n; i++)
        a[i] = inp();
    t.build(1, 1, n);
    int m = inp();
    while(m--){
        char op = getchar();
        while(op != 'C' && op != 'A')
            op = getchar();
        if(op == 'C'){
            int x = inp();
            int c = inp();
            t.modify(1, x, c);
        } else {
            int l = inp();
            int r = inp() - 1;
            printf("%d\n", t.query(1, l, r, 0));
        }
    }
}
```



---

## 作者：FutaRimeWoawaSete (赞：3)

样例好强，点赞！   

中文翻译太烂了，点踩！

考虑如果采用分治数据结构维护就必须要知道左端点要从什么时间开始跳，否则就无法转移。              

考虑到转移的瓶颈在于状态太多，所以大胆猜测正解得优化转移的状态量。   

不妨还是先把暴力转移的式子写出来：

令 $sum_{x,i}$ 表示线段树上第 $x$ 个节点，此时从时间 $i$ 向右走完整个区间相对于 $i$ 增加的时间量，记左儿子为 $Lson$，右儿子为 $rson$，那么我们可以得到下面这个转移状态：     

$sum_{x,i} = sum_{lson , i} + sum_{rson , i + sum_{lson,i}}$       

~~第一次写就把这个状态转移推错了导致样例都过不了~~          

我们考虑的是减少状态，不妨思考是否可以去掉重复状态。            

我们发现，$1 , 2 , 3 , 4 , 5 , 6$ 的最小公倍数是 $60$，并且我们发现 $sum_{x , i} = sum_{x , i \mod 60}$，解一下同余方程就不难发现如果任意两个时间 $x,y$ 对 $60$ 取模的余数相等，那么它们对于 $1,2,3,4,5,6$ 取模得到的余数也是相等的，自然 $x$ 和 $y$ 跑完一个区间的时间增长量是一样的。               

那么我们只要在线段树上维护一下这个东西就好了，查询时把 $\log n$ 个节点拿出来重新建树即可，时间复杂度 $O(60n\log n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,m,a[Len],sum[Len << 2][60],USED[35][60],SUM[35 << 2][60],qcnt;
int ls(int x){return x << 1;}
int rs(int x){return x << 1 | 1;}
void push_up(int x){for(int i = 0 ; i < 60 ; i ++) sum[x][i] = sum[ls(x)][i] + sum[rs(x)][(i + sum[ls(x)][i]) % 60];}
void build(int p,int l,int r)
{
	if(l == r)
	{
		for(int i = 0 ; i < 60 ; i ++) sum[p][i] = (i % a[l] == 0) ? 2 : 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
	//printf("###%d %d\n",l,r);
	//for(int i = 0 ; i < 60 ; i ++) printf("%d %d\n",i,sum[p][i]);
}
void update(int p,int l,int r,int idx)
{
	if(l == r)
	{
		for(int i = 0 ; i < 60 ; i ++) sum[p][i] = (i % a[l] == 0) ? 2 : 1;
		return;
	}
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx);
	else update(rs(p) , mid + 1 , r , idx);
	push_up(p);
}
void query(int p,int l,int r,int nl,int nr)
{
	if(nl <= l && nr >= r) 
	{
		qcnt ++;
		for(int i = 0 ; i < 60 ; i ++) USED[qcnt][i] = sum[p][i];
		return;
	}
	int mid = (l + r) >> 1;
	if(nl <= mid) query(ls(p) , l , mid , nl , nr);
	if(nr > mid) query(rs(p) , mid + 1 , r , nl , nr);
	push_up(p);
} 
void BUILD(int p,int l,int r)
{
	if(l == r) 
	{
		for(int i = 0 ; i < 60 ; i ++) SUM[p][i] = USED[l][i];
		return;
	}
	int mid = (l + r) >> 1;
	BUILD(ls(p) , l , mid);
	BUILD(rs(p) , mid + 1 , r);
	for(int i = 0 ; i < 60 ; i ++) SUM[p][i] = SUM[ls(p)][i] + SUM[rs(p)][(i + SUM[ls(p)][i]) % 60];
}
char s[5];
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	build(1 , 1 , n);
	scanf("%d",&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		scanf("%s",s);int l,r;scanf("%d %d",&l,&r);
		if(s[0] == 'C')
		{
			a[l] = r;
			update(1 , 1 , n , l);	
		}
		else 
		{
			qcnt = 0;
			query(1 , 1 , n , l , r - 1);
			BUILD(1 , 1 , qcnt);
			printf("%d\n",SUM[1][0]);
		}
	}
	return 0;
}
```

---

## 作者：Naoxiaoyu (赞：2)

# 分析
首先，观察题目，我们发现单点修改和区间查询，考虑**线段树**。

那么，我们的问题就在于如何处理走一段公路需要 $1$ 分钟还是 $2$ 分钟，也就是时间是否整除拥堵值 $a_i$。

# 思路
这道题关键在于，我们要考虑将所有时间对于 $a_i$ 是否整除的状态表示出来。

观察数据范围，$2 \le a_i \le 6$，可以算出，$a_i$ 的所有取值的最小公倍数为 $60$，也就是说，**走到这段路的时间设为 $t$，$t \mid a_i$ 就相当于 $(t \bmod 60) \mid a_i$**，于是我们便可以开 $60$ 棵线段树表示出所有状态，$pushup$ 时循环调用即可。

那么就有了 $pushup$ 的代码：
```cpp
for(int i=0;i<60;i++)
	t[p][i]=t[p*2+1][(i+t[p*2][i])%60]+t[p*2][i];
```
其中，$i$ 表示到某区间开头时所处的时间，$t_{p,i}$ 表示从 $i$ 时开始，走完这个区间所需的时间。

剩下的按照线段树写就可以，时间复杂度 $O(60 \times n \log_2n)$。

**注意：最后区间查询的时候右区间要减一，因为问的是城市而存储的是公路。**

# AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t[4*N][65],a[N];
void build(int p,int l,int r)
{
	if(l==r)
	{
		for(int i=0;i<60;i++)
		{
			if(i%a[l]==0) t[p][i]=2;
			else t[p][i]=1;
		}//建树时先处理出时间 
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	for(int i=0;i<60;i++)
		t[p][i]=t[p*2+1][(i+t[p*2][i])%60]+t[p*2][i];//push_up 
}
void change(int p,int l,int r,int x,int y)
{
	if(l==r)
	{
		for(int i=0;i<60;i++)
		{
			if(i%a[x]==0) t[p][i]=2;
			else t[p][i]=1;
		}//单点修改与建树类似 
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid) change(p*2,l,mid,x,y);
	else change(p*2+1,mid+1,r,x,y);
	for(int i=0;i<60;i++)
		t[p][i]=t[p*2+1][(i+t[p*2][i])%60]+t[p*2][i];
}
int ask(int p,int l,int r,int x,int y,int ti)
{
	if(x<=l && r<=y)
	{
		return t[p][ti];
	}
	int mid=(l+r)/2;
	int ans=0;
	if(x<=mid) ans+=ask(p*2,l,mid,x,y,ti);
	if(y>=mid+1) ans+=ask(p*2+1,mid+1,r,x,y,(ti+ans)%60);
	return ans;
}
int main()
{
	int n,q;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	build(1,1,n);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		char s[2];
		int x,y;
		scanf("%s",s);
		scanf("%d%d",&x,&y);
		if(s[0]=='C') 
		{
			a[x]=y;//先修改a[x] 
			change(1,1,n,x,y);
		}
		else 
		{
			printf("%d\n",ask(1,1,n,x,y-1,0));//注意y要减一 
		}
	}
	return 0;
}
```

---

## 作者：KazamaRuri (赞：1)

题意清晰，不再赘述。

## 分析

数据结构题，看到要维护这种~~奇奇怪怪~~可可爱爱的东西当然是用根号科技——分块了。

一开始没什么思路，直到看到数据范围里的 $ 2 \le a_i \le 6 $，就猜测复杂和值域有关。

经过一条道路的花费是否多 $ 1 $，取决于花费时间是不是 $ a_i $ 的倍数。结合值域进一步推测，经过某一段的时间对于进入该路程的时间是具有**周期性**的。假设一段路程中的 $ a_i $ 全部相等，那么对于进入时间 $ t_1 \equiv t_2 \: （\bmod \: a_i） $，有经过的时间 $ \Delta{t_1} = \Delta {t_2} $（$ \Delta $ 表示差值，即经过该路程的时间花费）。由此，考虑从余数的角度优化，当然不可能所有 $ a_i $ 都相等。根据 $ 2 \le a_i \le 6 $ 模数最小可以取 $ \operatorname{lcm}（2,3,4,5,6） = 60 $。

之后就直接上分块了，每个块内维护每个余数经过该块的时间花费。修改的话毕竟是单点修改，直接暴力重构块就好了。设块长为 $ B $，则修改时间复杂度为 $ O( \operatorname{lcm} \times B ) $，查询时间复杂度为 $ O( B + \frac{n}{B} ) $。理论上修改和查询时间复杂度相等时最优，大概是 $ B = 40 $ 时，but 实测会 T，取 $ 30 $ 跑的会快很多，这样就能过掉了。

## 代码

没有刻意压行。

```cpp
// 我从来就没有太阳，所以不怕失去。 ——东野圭吾《白夜行》
#include <iostream>
#include <cmath>
#define Kamisato namespace
#define Ayaka std;
using Kamisato Ayaka

const int N=1e5+5,B=320;
int n,m,a[N],len,b[N],t[60][N],L[N],R[N];
void upd(int x,int k){ int p=b[x]; a[x]=k;
	for(int i=0;i<60;i++){ t[i][p]=i;
		for(int j=L[p];j<=R[p];j++)
			t[i][p]+=1+(t[i][p]%a[j]==0);
	}
}
int ask(int l,int r){ int u=b[l],v=b[r],ret=0;
	if(u==v){ for(int i=l;i<=r;i++) ret+=1+(ret%a[i]==0); return ret; }
	for(int i=l;i<=R[u];i++) ret+=1+(ret%a[i]==0);
	for(int i=u+1;i^v;i++) ret+=t[ret%60][i]-(ret%60);
	for(int i=L[v];i<=r;i++) ret+=1+(ret%a[i]==0); return ret;
}
int main(){
	scanf("%d",&n),len=30;
	for(int i=1;i<=n;i++)
		scanf("%d",a+i),b[i]=(i-1)/len+1,
		L[b[i]]=(b[i]^b[i-1]?i:L[b[i]]),R[b[i]]=i;
	for(int i=1;i<=b[n];i++){
		for(int j=0;j<60;j++){ t[j][i]=j;
			for(int k=L[i];k<=R[i];k++)
				t[j][i]+=1+(t[j][i]%a[k]==0);
		}
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		char op[2]; int x,y;
		scanf("%s%d%d",&op,&x,&y);
		if(op[0]=='C') upd(x,y);
		else printf("%d\n",ask(x,y-1));
	} return 0;
}
```

---

## 作者：Silvestorm (赞：0)

### 题目大意

一些国家由 $n+1$ 个城市组成，这些城市位于一个笔直的路上，我们把按照他们在路上的顺序把这些城市编号为 $1$ 到 $n+1$，这样，第 $i$ 个线段连接着第 $i$ 个和第 $i+1$ 个城市。每一个城市有一个拥堵值 $a_i$，如果当前时间能被 $a_i$ 整除，那么通过这条公路需要两分钟，否则需要一分钟。

给出每条公路的 $a_i$，以及 $m$ 次操作。

操作有两种：

给出 $C,x,d$：把第 $x$ 条路的拥堵时刻改成 $d$。

给出 $A,x,y$：问 $x$ 到 $y$ 城市所需要的时间。

$1\le n,m\le 10^5$，$2\le a_i\le 6$。

### 题目类型

线段树。

### 解题思路

注意到 $a_i$ 的范围只 $2$ 到 $6$，其最小公倍数的值为 $60$，那么到达任意一点时，状态数都只有 $60$ 种，也就是说，对于一段区间，我们只需要枚举起始点的所有状态并记录这个状态下该区间的答案即可。

推广到两个区间的合并，查询到的左区间的答案，就是右区间的初始状态，找到右区间对应的答案即可合并区间。

总之，转化一下就是很板的线段树题了。

注意查询时，查询到一段区间时，一定要根据前面区间得到的答案去选择该区间的答案。

### code

```cpp
#include <bits/stdc++.h>
#define ll int
using namespace std;

ll n, m, sum, ans[1000100][63], k, q, num[100100];
ll ls(ll p) { return p << 1; }
ll rs(ll p) { return p << 1 | 1; }
void pushup(ll p)
{
	for (int i = 0; i <= 60; i++)
	{
		ll tem = (ans[ls(p)][i] + i) % 60; // 左区间的答案就是右区间的初始状态
		ans[p][i] = ans[ls(p)][i] + ans[rs(p)][tem];
	}
}
void build(ll l, ll r, ll p)
{
	if (l == r)
	{
		for (int i = 0; i <= 60; i++) // 枚举初始状态
			if (i % num[l] == 0)
				ans[p][i] = 2;
			else
				ans[p][i] = 1;
		return;
	}
	ll mid = (l + r) >> 1;
	build(l, mid, ls(p));
	build(mid + 1, r, rs(p));
	pushup(p);
}
void update(ll nl, ll nr, ll l, ll r, ll p, ll k)
{
	if (l == r)
	{
		for (int i = 0; i <= 60; i++)
			if (i % k == 0)
				ans[p][i] = 2;
			else
				ans[p][i] = 1;
		return;
	}
	ll mid = (l + r) >> 1;
	if (nl <= mid)
		update(nl, nr, l, mid, ls(p), k);
	if (nr > mid)
		update(nl, nr, mid + 1, r, rs(p), k);
	pushup(p);
}
void query(ll nl, ll nr, ll l, ll r, ll p)
{
	if (nl <= l && r <= nr)
	{
		sum += ans[p][sum % 60];
		return;
	}
	ll mid = (l + r) >> 1;
	if (nl <= mid)
		query(nl, nr, l, mid, ls(p));
	if (nr > mid)
		query(nl, nr, mid + 1, r, rs(p));
}
void solve()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> num[i];
	build(1, n, 1);
	cin >> q;
	string s;
	ll x, y;
	while (q--)
	{
		cin >> s;
		if (s == "A")
		{
			cin >> x >> y;
			sum = 0;
			query(x, y - 1, 1, n, 1);
			cout << sum << '\n';
		}
		else
		{
			cin >> x >> y;
			update(x, x, 1, n, 1, y);
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t = 1;
	// cin >> t;
	while (t--)
		solve();
	return 0;
}
```

---

## 作者：_WRYYY_ (赞：0)

[使用博客园以获得不知道会不会更好的阅读体验](https://www.cnblogs.com/wryyy-233/p/18025527)

看题目似乎没什么思路，但是翻到数据范围，我们发现拥堵程度 $a_i$ 和修改值的值域是 $[2,6]$，而边权为二时的条件是当前时间 $t$ 满足 $t\equiv 0 \pmod{a_i}$，也就是说点 $i$ 对最终答案的贡献在 $t$ 属于一定区间时内是相同的，而我们也可以把这个结论扩展到区间上去。

根据以上结论，我们只需要对齐区间内每个值的循环节，就可以保证即使进入区间的 $t$ 是不同，我们依然可以把 $t$ 对应到区间循环节的某个部位直接求出区间的贡献，再由数据范围可知，我们最长循环节长度为 60。因为需要支持单点修改，区间查询，并且答案都是从左到右计算，我们考虑使用线段树维护，时间复杂度 $O(n\log_2n)$，因为要维护循环节的值，会带一个 60 的常数。

Code：

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
#define N 100010
using namespace std;
using namespace __gnu_pbds;
int val[N], tr[N << 2][60];
void build(int k, int l, int r)
{
	if (l == r)
	{
		for (int i = 0; i < 60; i++)
			tr[k][i] = 1 + !(i % val[l]);
		return;
	}
	int mid = l + r >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	for (int i = 0; i < 60; i++)
		tr[k][i] = tr[k << 1][i] + tr[k << 1 | 1][(tr[k << 1][i] + i) % 60];
}
void tr_c(int k, int l, int r, int x)
{
	if (l > x || r < x)
		return;
	if (l == r && l == x)
	{
		for (int i = 0; i < 60; i++)
			tr[k][i] = 1 + !(i % val[l]);
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid)
		tr_c(k << 1, l, mid, x);
	else
		tr_c(k << 1 | 1, mid + 1, r, x);
	for (int i = 0; i < 60; i++)
		tr[k][i] = tr[k << 1][i] + tr[k << 1 | 1][(tr[k << 1][i] + i) % 60];
}
int aans;
void tr_a(int k, int l, int r, int x, int y)
{
	if (l > y || r < x)
		return;
	if (l >= x && r <= y)
	{
		aans += tr[k][aans % 60];
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid)
		tr_a(k << 1, l, mid, x, y);
	if (y > mid)
		tr_a(k << 1 | 1, mid + 1, r, x, y);
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n, q, x, y, ans;
	char opt;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> val[i];
	cin >> q;
	build(1, 1, n);
	while (q--)
	{
		cin >> opt >> x >> y;
		if (opt == 'C')
		{
			val[x] = y;
			tr_c(1, 1, n, x);
		}
		else
		{
			aans = 0;
			tr_a(1, 1, n, x, y - 1);
			cout << aans << "\n";
		}
	}

	return 0;
}
```


关于 ``tr_a`` 即询问函数，因为我们知道时间是从左到右计算的，线段树也是从左到右扫的，所以我这里干脆使用了全局变量，这样就可以比较方便的知道某个区间应该是算循环节的哪个部分。

题外话，%你赛考了这题，当时写的是分块，因为脑抽忘记线段树也是从左到右扫的，所以没写线段树，最后十五分钟突然想起来线段树好像也能维护，然后从左到右的查询不知道哪里写锅了，结果没写出来，暴扣 70。

---

## 作者：Planetary_system (赞：0)

## 题面解释：
有 $n+1$ 个城市，通过 $n$ 条边形成链，每个边有其权值 $a$，若其时间为边权的倍数，代价为 $2$，否则为 $1$。两种操作，单点修改于区间查询。

## 思路分析：
由于需要判断是否是倍数，我们先观察 $a$ 的数据范围，发现有 $2\le a\le6$，最大公倍数为 $60$ 。

再加上这两种操作的要求，那肯定考虑线段树嘛，我们就开 $60$ 颗线段树，每次操作 $\bmod 60$，同时在`push_up`时，把 $60$ 棵线段树一起更新，其余不变，就好了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,ans[N<<2][60],a[N];
char c[3];
void push_up(int p) {
	for(int i=0; i<=59; i++)
		ans[p][i]=ans[p<<1][i]+ans[p<<1|1][(ans[p<<1][i]+i)%60];
	return;
}
void build(int p,int l,int r) {
	if(l==r) {
		for(int i=0; i<=59; i++)
			ans[p][i]=((i%a[l]==0)?2:1);
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	push_up(p);
	return;
}
void update(int p,int l,int r,int x,int k) {
	if(l==r) {
		for(int i=0; i<=59; i++)
			ans[p][i]=(i%k==0)?2:1;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(p<<1,l,mid,x,k);
	else update(p<<1|1,mid+1,r,x,k);
	push_up(p);
	return;
}
int query(int p,int l,int r,int x,int y,int t) {
	if(y<l||r<x)return 0;
	if(x<=l&&r<=y)return ans[p][t];
	int mid=(l+r)>>1,res=0;
	res=query(p<<1,l,mid,x,y,t);
	res+=query(p<<1|1,mid+1,r,x,y,(t+res)%60);
	return res;
}
signed main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)scanf("%d",&a[i]);
	build(1,1,n);
	scanf("%d",&m);
	while(m--) {
		int x,y;
		scanf("%s%d%d",c,&x,&y);
		if(c[0]=='C')update(1,1,n,x,y);
		else printf("%d\n",query(1,1,n,x,y-1,0));
	}
	return 0;
}
```

谢谢！

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

$N$ 条带权道路连接了 $N+1$ 座城市。现在要从一座城市走向它右侧的一座城市，在遇到一条道路时，如果花费的时间正好是这条边权的倍数，则需要花 $2$ 的时间，否则花费 $1$ 的时间。要求支持查询和单点修改。

## 题目分析

在 AtCoder 中有这道题的[弱化版](https://www.luogu.com.cn/problem/AT_abc319_e)。思路很简单，我们求出时间对于所有权值的 $lcm$ 取模的所有值在一段区间花费的时间。这显然是可以轻松求出的。而为了支持单点修改和区间查询，我们需要一个数据结构来维护。显然这个信息是支持区间合并的，可以用线段树维护。这还是很简单的。复杂度 $O(n\log n)$，带个 $60$ 的常数。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1LL)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
#define ADD(a,b) to[++cnt]=b,nxt[cnt]=h[a],h[a]=cnt
inline ll read(){ll s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =1e5+5,M=2e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=998244353;
const ui base=13331;
using namespace std;
int n=read(),a[N],m;
char opt;
int xd[N<<2][60];
inline void getup(int x){
	rep(i,0,59)xd[x][i]=xd[L][i]+xd[R][(i+xd[L][i])%60];
}
inline void build(int x,int l,int r){
	if(l==r){
		rep(i,0,59)xd[x][i]=1+(i%a[l]==0);
		return;
	}
	build(lc),build(rc),getup(x);
}
inline void modify(int x,int l,int r,int p){
	if(l==r){
		rep(i,0,59)xd[x][i]=1+(i%a[l]==0);
		return;
	}
	if(p<=mid)modify(lc,p);
	else modify(rc,p);
	getup(x); 
}
inline int query(int x,int l,int r,int Ll,int Rr,int k){
	if(l>r)return 0;
	if(OK)return xd[x][k];
	if(Rr<=mid)return query(lc,Ll,Rr,k);
	if(Ll>mid)return query(rc,Ll,Rr,k);
	int lk=query(lc,Ll,Rr,k);
	return lk+query(rc,Ll,Rr,(k+lk)%60);
}
int main(){
	rep(i,1,n)a[i]=read();
	build(Root);
	m=read();
	for(int i=1,l,r;i<=m;i++){
		opt=getchar(),l=read(),r=read();
		if(opt=='C')a[l]=r,modify(Root,l);
		else pf(query(Root,l,r-1,0)),putchar('\n');
	}
	return 0;
}
```


---

## 作者：Wings_of_liberty (赞：0)

# 分析
首先，我在看这道题最开始没有思路，这个输入输出非常线段树，于是我就思考线段树用来维护什么，一般来说，线段树维护的是具有结合律的数据，那么很明显，本题的两个量：拥堵值和时间中，只有时间符合条件，所以我们想到线段树维护时间。

但是如何维护时间？这里有两个问题：  
首先是线段树具体维护什么，这里我参考了一下先前的题解（感谢写题解的大佬们），基本都是维护：到 $l$ 的时间为 $i$ 时（模60意义下）到 $r+1$ 需要的时间，然后输入 $y$ 时减一再查询，我看大家没有怎么解释，我来说一下我的看法。  
实际上，我们输入的是一条路的拥堵值，也就是说，我们维护的其实是从 $l$ 这条路的左端点到 $r$ 这条路的右端点的时间，举个例子：题目中询问1到3的时间，实际上只经过了1，2两条路，这就是减一的原因（我是这么想的）。

然后就是模60的原因，实际上如果没有小于6这个条件这道题不能这么做（没有这个条件我不会做），很明显，到 $l$ 的时间可以很大，但是我们既不能开这么大的数组，也没有那么多的时间。如果有了小于6的条件，我们可以用1，2，3，4，5，6的最小公倍数来模一下时间，这样吵闹值不会对答案其他影响，还可以降低需要的空间时间。

# 注意
与正常线段树不同，我们需要维护的值是一个数组。  
这次是单点修改，不用区间的写法（也可以，但是容易错）。  
如果你使用三目运算符且习惯用取反来判断整除后是否为0，一定要注意别写反了。  
我使用的是动态开点线段树，能节省一点空间，如果不习惯可以看楼上大佬们的代码。

# 代码
```
#include <bits/stdc++.h>
using namespace std;
#define op(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
#define cl() fclose(stdin),fclose(stdout)
#define F(i,x,y) for(ll i=(x);i<=(y);i++)
typedef long long ll;
const ll MAX=1e5+10;
ll n,m,ro;
ll a[MAX];
struct segment_tree{
	struct node{
		ll son[2];//动态开点 
		ll time_[70];//到l时的时间（模60意义下）时到R+1的时间 
	}f[MAX<<1];
	ll cnt=0;
	inline void push_up(ll x){
		F(i,0,59){
			f[x].time_[i]=f[f[x].son[0]].time_[i]+f[f[x].son[1]].time_[(i+f[f[x].son[0]].time_[i])%60];
		}
	}
	inline void build(ll &p,ll l,ll r){
		if(!p){
			p=++cnt;
		}
		if(l==r){
			F(i,0,59){
				f[p].time_[i]=(i%a[l])?1:2;//别写反了 
			}
			return;
		}
		int mid=(l+r)>>1;
		build(f[p].son[0],l,mid);
		build(f[p].son[1],mid+1,r);
		push_up(p);
	}
	inline void change(ll x,ll l,ll r,ll lpos,ll num){
		if(!x){
			x=++cnt;
		}
		if(l==r){
			F(i,0,59){
				f[x].time_[i]=(i%a[l])?1:2;
			}
			return;
		}
		int mid=(l+r)>>1;
		if(lpos<=mid){
			change(f[x].son[0],l,mid,lpos,num);
		}else{
			change(f[x].son[1],mid+1,r,lpos,num);
		}
		push_up(x);
	}
	inline ll check_(ll x,ll l,ll r,ll lpos,ll rpos,ll now){
		if(lpos<=l&&rpos>=r){
			return f[x].time_[now];
		}
		ll mid=(l+r)>>1;
		ll ans=0;
		if(lpos<=mid){
			ans+=check_(f[x].son[0],l,mid,lpos,rpos,now);
		}
		if(mid<rpos){
			ans+=check_(f[x].son[1],mid+1,r,lpos,rpos,(now+ans)%60);
		}
		return ans;
	}
}st;
inline void init(){
	cin>>n;
	F(i,1,n){
		cin>>a[i];
	}
	st.build(ro,1,n);
}
inline void work(){
	cin>>m;
	char opt;
	ll x,y;
	F(i,1,m){
		cin>>opt>>x>>y;
		if(opt=='C'){
			a[x]=y;
			st.change(1,1,n,x,y);
		}else{
			y--;
			if(x>y){
				swap(x,y);
			}
			cout<<st.check_(1,1,n,x,y,0)<<endl;
		}
	}
}
int main(){
//	op("");
	ios::sync_with_stdio(false);
	init();
	work();
//	cl();
	return 0;
}

```


---

## 作者：yizhiming (赞：0)

## 题目大意

$n+1$ 个点，$n$ 条边，每条边连接 $i$ 和 $i+1$，边有边权 $a_i$，若当前时间能被 $a_i$ 整除，则时间 $+1$，否则时间 $+2$。多组询问从 $l$ 到 $r$ 所需的时间，单点修改边权为 $v$。

$1\leq n,q\leq 10^5,2\leq a_i,v\leq6$。

一定要看见 $a_i$ 的大小啊，翻译没写，我想了半天。。。


## 题目分析

注意到 $a_i$ 很小，那么这就是突破口了，我们发现 $\operatorname{lcm(2,3,4,5,6)} = 60$，是的只有区区 $60$，这意味着什么？假设当前时间为 $k$，等价于时间为 $k\bmod60$，这意味这时间的取值便只有 $60$，所以我们考虑直接维护当时间为 $k$ 时的答案。

既然查询是区间，那就需要用一些数据结构维护，我选择的是线段树，貌似有神仙拿分块卡过去了，我们考虑设 $val_{u,k}$ 表示节点 $u$ 开始时间为 $k$ 时的答案，$\text{pushup}$ 的时候直接从 $0$ 枚举到 $59$ 即可，只需要稍微处理一下，将左儿子所需的时间累加到当前的时间上，再加上右儿子对应值即可，单点修改也直接线段树上修改即可。

## Code

代码上的细节也不多，注意一下查询就行了（查询貌似没说查询的左右端点的大小关系，所以我稍微特殊处理了一下）

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
int read(){
	int x=0,f=1;char ch = getchar();
	while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch = getchar();}
	while(ch>='0'&&ch<='9'){x = x*10+ch-'0';ch = getchar();}
	return x*f;
}
const int N = 1e5+5;
struct aa{
	int lc,rc,val[65];
}node[N*2];
int tot=1;
int a[N];
void pushup(int u){
	for(int i=0;i<60;i++){
		int res=node[node[u].lc].val[i];
		res+=node[node[u].rc].val[(i+res)%60];
		node[u].val[i] = res; 
	}
}
void build(int u,int l,int r){
	if(l==r){
		for(int i=1;i<=60;i++){
			node[u].val[i%60] = (i%a[l]==0?2:1);
		}
		return;
	}
	int mid = (l+r)/2;
	node[u].lc = ++tot;
	build(node[u].lc,l,mid);
	node[u].rc = ++tot;
	build(node[u].rc,mid+1,r);
	pushup(u);
}
void add(int u,int l,int r,int p,int x){
	if(l==r){
		a[l] = x;
		for(int i=1;i<=60;i++){
			node[u].val[i%60] = (i%a[l]==0?2:1);
		}
		return ;
	}
	int mid = (l+r)/2;
	if(p<=mid){
		add(node[u].lc,l,mid,p,x);
	}else{
		add(node[u].rc,mid+1,r,p,x);
	}
	pushup(u);
}
int query(int u,int l,int r,int ll,int rr,int k){
	if(l==ll&&r==rr){
		return node[u].val[k];
	}
	int mid = (l+r)/2;
	if(rr<=mid){
		return query(node[u].lc,l,mid,ll,rr,k);
	}else if(ll>mid){
		return query(node[u].rc,mid+1,r,ll,rr,k);
	}else{
		int res = query(node[u].lc,l,mid,ll,mid,k);
		res+=query(node[u].rc,mid+1,r,mid+1,rr,(k+res)%60);
		return res;
	}
}
int main(){
	int n,m;
	n = read();
	for(int i=1;i<=n;i++){
		a[i] = read();
	}
	build(1,1,n);
	m = read();
	int l,r;
	char opt[5];
	while(m--){
		scanf("%s",opt);
		if(opt[0]=='A'){
			l = read();r = read();
			if(l==r){
				cout<<0<<"\n";
				continue;
			}else if(l>r){
				swap(l,r);
			}
			cout<<query(1,1,n,l,r-1,0)<<"\n";
		}else{
			l = read();r = read();
			add(1,1,n,l,r);
		}
	}
	return 0;
}

```

最后吐槽一下，这道题有 2400 的难度嘛。。。

---

## 作者：Cylete (赞：0)

首先这玩意就是一个序列

~~然后我并没有什么思路~~

回去看了下英文题面，欸，这个$a_i \le 6 $！！！

因为$lcm(1, 2, 3, 4, 5, 6) = 60$

所以考虑线段树在时间$mod 60$的意义下暴力搞

$tree[o][i]$维护的是$[L, R]$，这表示当前到$L$需要的时间$mod 60 = i$，到达$R + 1$需要的时间

复杂度$O(60 * nlog_2n)$

```cpp
#define int long long
#define mid ((l+r)>>1)
#define lson (o<<1)
#define rson (o<<1|1)
#define R register

const int N = 1e5 + 10;

int n, m, a[N];

int tree[N << 2][60];

inline void pushup(int o)
{
	for(R int i = 0; i < 60; i++) tree[o][i] = tree[lson][i] + tree[rson][(i + tree[lson][i]) % 60];
}

inline void build(int o, int l, int r)
{
	if(l == r)
	{
		for(R int i = 0; i < 60; i++) tree[o][i] = 1 + (i % a[l] == 0);
		return;
	}
	build(lson, l, mid);
	build(rson, mid + 1, r);
	pushup(o);
}

inline void update(int o, int l, int r, int pos, int val)
{
	if(l == r)
	{
		for(R int i = 0; i < 60; i++) tree[o][i] = 1 + (i % a[l] == 0);
		return;
	}
	if(pos <= mid) update(lson, l, mid, pos, val);
	else update(rson, mid + 1, r, pos, val);
	pushup(o);
}

inline int query(int o, int l, int r, int ql, int qr, int now)
{
	if(ql <= l && r <= qr) return tree[o][now];
	int res = 0;
	if(ql <= mid) res += query(lson, l, mid, ql, qr, now);
	if(qr > mid) res += query(rson, mid + 1, r, ql, qr, (now + res) % 60);
	return res;
}

signed main()
{
	into();
	read(n);
	for(R int i = 1; i <= n; i++) read(a[i]);
	build(1, 1, n);
	read(m);
	while(m--)
	{
		char ch = getchar();
		while(ch != 'C' && ch != 'A') ch = getchar();
		R int x, y;
		read(x); read(y);
		if(ch == 'C')
		{
			a[x] = y;
			update(1, 1, n, x, y);
		}
		else
		{
			y--;
			if(x > y) swap(x, y);
			writeln(query(1, 1, n, x, y, 0));
		}
	}
	return 0;
}
```

---

