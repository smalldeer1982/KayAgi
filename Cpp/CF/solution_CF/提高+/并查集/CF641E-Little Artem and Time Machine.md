# Little Artem and Time Machine

## 题目描述

Little Artem has invented a time machine! He could go anywhere in time, but all his thoughts of course are with computer science. He wants to apply this time machine to a well-known data structure: multiset.

Artem wants to create a basic multiset of integers. He wants these structure to support operations of three types:

1. Add integer to the multiset. Note that the difference between set and multiset is that multiset may store several instances of one integer.
2. Remove integer from the multiset. Only one instance of this integer is removed. Artem doesn't want to handle any exceptions, so he assumes that every time remove operation is called, that integer is presented in the multiset.
3. Count the number of instances of the given integer that are stored in the multiset.

But what about time machine? Artem doesn't simply apply operations to the multiset one by one, he now travels to different moments of time and apply his operation there. Consider the following example.

- First Artem adds integer $ 5 $ to the multiset at the $ 1 $ -st moment of time.
- Then Artem adds integer $ 3 $ to the multiset at the moment $ 5 $ .
- Then Artem asks how many $ 5 $ are there in the multiset at moment $ 6 $ . The answer is $ 1 $ .
- Then Artem returns back in time and asks how many integers $ 3 $ are there in the set at moment $ 4 $ . Since $ 3 $ was added only at moment $ 5 $ , the number of integers $ 3 $ at moment $ 4 $ equals to $ 0 $ .
- Then Artem goes back in time again and removes $ 5 $ from the multiset at moment $ 3 $ .
- Finally Artyom asks at moment $ 7 $ how many integers $ 5 $ are there in the set. The result is $ 0 $ , since we have removed $ 5 $ at the moment $ 3 $ .

Note that Artem dislikes exceptions so much that he assures that after each change he makes all delete operations are applied only to element that is present in the multiset. The answer to the query of the third type is computed at the moment Artem makes the corresponding query and are not affected in any way by future changes he makes.

Help Artem implement time travellers multiset.

## 样例 #1

### 输入

```
6
1 1 5
3 5 5
1 2 5
3 6 5
2 3 5
3 7 5
```

### 输出

```
1
2
1
```

## 样例 #2

### 输入

```
3
1 1 1
2 2 1
3 3 1
```

### 输出

```
0
```

# 题解

## 作者：DPair (赞：3)

完全不需要CDQ，只需要朴素的树状数组就行了。

提供一种纯树状数组的做法，目前似乎是洛谷最优解。

## 【思路】
首先我们不难判断，这道题中的时间戳其实可以看成一个序列，你修改一个点会对其后面所有点产生影响。

这启示我们要用树状数组。

然后我们又发现，每一个 $x$ 都是互相独立的。

一种很暴力的思路是对于每一个 $x$ 开一个树状数组，但是必然会炸空间。

于是我们考虑只用一个数组完成所有处理。

需要离线。

我们可以这么做：

设 $id$ 表示一个询问是第几个询问。

我们以 $x$ 为第一关键字，$id$ 为第二关键字对所有询问排序。最后所有相同的 $x$ 都排在了一起，而且对于 **同一个** $x$ ，其操作顺序先后是不变的。

而不同的 $x$ 显然互不影响，所以打乱了也没关系。

然后我们就成功的把询问按 $x$ 分组了，对于每一组直接跑朴素的树状数组就行。

唯一的细节就是清空树状数组时，需要把刚刚进行过的操作全部撤销而不是直接使用 `memset` ，因为一遍 `memset` 是 $O(n)$ 的，复杂度会炸。

由于时间戳值域为 $10^9$ ，把时间戳离散化一下就行了。（我脑残一开始没看到这个。。。）

最终复杂度是 $O(nlogn)$ 的。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() printf("I am a cheater!I AK IOI!%c", 10)
template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}
inline char next_char(){
    char ch = getchar();
    while(ch == 9 || ch == 10 || ch == 32) ch = getchar();
    return ch;
}

#define MAXN 100005

int n;
struct Quest{
    int x, t, opt, id;
    inline bool operator < (const Quest &tmp) const{//排序的两个关键字
        return x < tmp.x || (x == tmp.x && id < tmp.id);
    }
}q[MAXN];
int c[MAXN];
inline int lowbit(int x){return x & -x;}
inline int query(int x){int ret = 0;for (;x;x -= lowbit(x)) ret += c[x];return ret;}
inline void modify(int x, int y){for (;x <= n;x += lowbit(x)) c[x] += y;}
int ans[MAXN], b[MAXN];
int main(){
    read(n);
    memset(ans, -1, sizeof(ans));
    for (register int i = 1;i <= n;i ++){
        read(q[i].opt);read(q[i].t);read(q[i].x);
        b[i] = q[i].t;
        q[i].id = i;
    }
    sort(b + 1, b + n + 1);//离散化
    int tot = unique(b + 1, b + n + 1) - b - 1;
    for (register int i = 1;i <= n;i ++) q[i].t = lower_bound(b + 1, b + tot + 1, q[i].t) - b;
    sort(q + 1, q + n + 1);
    int it = 1;//对于每一组询问跑树状数组
    while(it <= n){
        int mem = it;
        while(q[it].x == q[mem].x){
            if(q[it].opt == 1) modify(q[it].t, 1);
            if(q[it].opt == 2) modify(q[it].t, -1);
            if(q[it].opt == 3) ans[q[it].id] = query(q[it].t);
            it ++;
        }
        it = mem;
        while(q[it].x == q[mem].x){
            if(q[it].opt == 1) modify(q[it].t, -1);
            if(q[it].opt == 2) modify(q[it].t, 1);
            it ++;
        }
    }
    for (register int i = 1;i <= n;i ++){//由于离线了，要这么输出答案
        if(~ans[i]) fprint(ans[i], 10);
    }
}
```

---

## 作者：龙之吻—水货 (赞：3)

# CF641E Little Artem and Time Machine

## 题目大意

直接看翻译还是能看懂的吧 QwQ

## 个人感觉

CDQ 分治入门题目

## 解题报告

其他题解也有 CDQ 分治的做法，不过似乎及其概括，这里稍微补充一下。

首先，这道题有三维 ： 操作的顺序，时间轴，以及 x 的值。

由于第一维本身有序，所以暂时不考虑去动它，选择对第二维进行 CDQ 分治。

考虑如何统计左区间对右区间的影响，假设 $a[i]$ 在左区间， $a[j]$ 在有区间，发现只有当 $a[i].t <= a[j].t$, 且 $a[i].x == a[j].x$ 的时候， $a[i]$ 对 $a[j]$ 才会产生贡献，所以在 CDQ 分治的时候只需要维护一个桶就可以了。

因为 $x$ 可能会比较大，所以可以使用 unordered_map 或者先离散化一下。

复杂度 : $O(n\log n)$

实测结果(时间常数大小) ：
[离散化 + 桶](https://www.luogu.org/recordnew/show/18350392) < [un_map + 逐个删除](https://www.luogu.org/recordnew/show/18350482) << [un_map + un_map::clear()](https://www.luogu.org/recordnew/show/18349711)

附上使用离散化的 Code ：
```cpp
#include<cstdio>
#include<algorithm>

class Solution{
private :
    static const int maxn = 1e5 + 7;

    struct Oper{
        int op, t, x, id;
    };

    int n, cnt, b[maxn], ct, ans[maxn];
    Oper p[maxn];

    void CDQ(int l, int r) {
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        CDQ(l, mid), CDQ(mid + 1, r);

        static Oper tmp[maxn];
        static int tot[maxn];

        int i = l, j = mid + 1, tp = l;
        while (i <= mid && j <= r) {
            if (p[i].t <= p[j].t) {
                if (p[i].op == 1) {
                    tot[p[i].x]++;
                } else if (p[i].op == 2) {
                    tot[p[i].x]--;
                }
                tmp[tp++] = p[i++];
            } else {
                if (p[j].op == 3) {
                    ans[p[j].id] += tot[p[j].x];
                }
                tmp[tp++] = p[j++];
            }
        }

        while (i <= mid) {
            tmp[tp++] = p[i++];
        }
        while (j <= r) {
            if (p[j].op == 3) {
                ans[p[j].id] += tot[p[j].x];
            }
            tmp[tp++] = p[j++];
        }
        for (register int i = l; i <= mid; i++) {
            tot[p[i].x] = 0;
        }
        for (register int i = l; i <= r; i++) {
            p[i] = tmp[i];
        }
    }
    
public :
    Solution() {
        get();
        solve();
    }

    void get() {
        scanf("%d", &n);
        for (register int i = 1; i <= n; i++) {
            scanf("%d %d %d", &p[i].op, &p[i].t, &p[i].x);
            b[i] = p[i].x;
            if (p[i].op == 3) {
                p[i].id = ++cnt;
            }
        }
    }

    void solve() {
        std::sort(b + 1, b + 1 + n);
        ct = std::unique(b + 1, b + 1 + n) - b + 1;
        for (register int i = 1; i <= n; i++) {
            p[i].x = std::lower_bound(b + 1, b + 1 + ct, p[i].x) - b;
        }
        CDQ(1, n);
        for (register int i = 1; i <= cnt; i++) {
            printf("%d\n", ans[i]);
        }
    }
};
Solution sol;

int main() {}

```

---

## 作者：Super_Cube (赞：2)

# Solution

很好笑的题。

所有操作只与单个数字相关，那对于每个 $x$ 单独考虑。

现在对于每个值有一个操作序列，内容为在 $t$ 时刻使答案加一或减一。对于查询只需要维护在不超过 $t$ 时刻内一共有多少个加一操作，多少个减一操作，相减即为答案。

你当然可以离线下来通过离散化和树状数组或者在线动态开点线段树做，但是为了偷懒可利用 `std::map` 与 `__gnu_pbds::tree` 在不到 500B 代码成功解决。

时间复杂度：$O(n\log^2 n)$。

# Code

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace __gnu_pbds;
std::map<int,tree<int,null_type,std::less<int>,rb_tree_tag,tree_order_statistics_node_update> >mp1,mp2; 
int T;
int main(){
	scanf("%d",&T);
	for(int op,x,y;T--;){
		scanf("%d%d%d",&op,&x,&y);
		if(op==1)mp1[y].insert(x);
		else if(op==2)mp2[y].insert(x);
		else printf("%d\n",mp1[y].order_of_key(x+1)-mp2[y].order_of_key(x+1));
	}
	return 0;
}
```

---

## 作者：Charlie_ljk (赞：1)

每次操作对应三个参数 $id,t,x$，$t,x$ 同题面，$id$ 表示其为第几个操作。

那么对于查询 $i$ 即为求集合 $\{(i,j)|id_j<id_i ∧ time_j\le time_i\}$ 中 $x_i$ 的个数，于是转化为了一道二维偏序的板子题，可以用 cdq 分治解决。

复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=1e5+10;
template<typename Tp> inline void read(Tp&x)
{
	x=0;register bool z=true;
	register char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) if(c=='-') z=0;
	for(;'0'<=c&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(z?x:~x+1);
}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y){read(x);read(y...);}
template<typename Tp> inline void wt(Tp x)
{if(x>9)wt(x/10);putchar((x%10)+'0');}
template<typename Tp> inline void write(Tp x)
{if(x<0)putchar('-'),x=~x+1;wt(x);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x);putchar(' ');write(y...);}
int n,b[N],cnt[N],ans[N];
struct aa {int id,t,x,val;}e[N],tmp[N];
void cdq(int l,int r)
{
	if(l==r) return ;
	int mid=(l+r)>>1,x=l,y=mid+1,tot=l;
	cdq(l,mid),cdq(mid+1,r);
	for(;y<=r;y++)
	{
		for(;e[x].t<=e[y].t&&x<=mid;x++)
		{
			cnt[e[x].x]+=e[x].val;
			tmp[tot++]=e[x];
		}
		if(e[y].val==0) 
		{
			if(ans[e[y].id]==-0x3f3f3f3f) ans[e[y].id]=0;
			ans[e[y].id]+=cnt[e[y].x];
		}
		tmp[tot++]=e[y];
	}
	for(int i=l;i<=x-1;i++) cnt[e[i].x]-=e[i].val;
	for(;x<=mid;x++) tmp[tot++]=e[x];
	for(int i=l;i<=r;i++) e[i]=tmp[i];
}
signed main()
{
	read(n);
	for(int i=1,op,t,x;i<=n;i++) 
	{
		read(op,t,x);
		b[i]=x;
		e[i]={i,t,x,op==1?1:(op==2?-1:0)};
	}
	sort(b+1,b+1+n);
	b[0]=unique(b+1,b+1+n)-(b+1);
	for(int i=1;i<=n;i++)
		e[i].x=lower_bound(b+1,b+1+b[0],e[i].x)-b;
	for(int i=1;i<=n;i++) ans[i]=-0x3f3f3f3f;
	cdq(1,n);
	for(int i=1;i<=n;i++)
		if(ans[i]>=0) write(ans[i]),puts("");
}
```

---

## 作者：zyh_helen (赞：1)

提供一个题解区中还没有人写的 $O(n \times \log^3n)$ 的非正解。（极其生草

----

考虑使用线段树维护时间轴，每个节点维护一个 map，每次加入一个数直接对线段树上途径的每一个节点的 map 里使该数加一。

删除一个数则先查询 $t$ 之前最近的 $x$ 在哪里，接着每一个 map 里减一即可。

查询时查询 $t$ 之前每个 map 里 $x$ 的个数即可。

---

但是由于删除可能影响到这之前的位置，所以需要用一个小根堆来维护删除操作，每次查询把时间小于该操作的删除操作处理并弹出即可。

---

代码略显冗长。

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<set>
#include<bitset>
//#define int long long
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 1e5 + 10, M = 1e5, inf = 1e9, mod = 998244353;
//const double eps = 1e-8;
/*
       					  _      _        _          
				  ____  _| |_   | |_  ___| |___ _ _  
				 |_ / || | ' \  | ' \/ -_) / -_) ' \ 
				 /__|\_, |_||_|_|_||_\___|_\___|_||_|
				     |__/    |___|     
				        
*/
//int head[N], tot;
//struct edge{
//	int t;
//	int next;
//}e[N << 1];
//void edge_add(int u, int v){
//	e[++tot].next = head[u];
//	e[tot].t = v;
//	head[u] = tot;
//}
//int qmr(int x, int a){
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}

struct sgt{
	map<int, int>s;
	int l, r;
}t[N << 2];
void pushup(int p){
	
}
void build(int p, int l, int r){
	t[p].l = l;
	t[p].r = r;
	if(l == r){
		return;
	}
	int mid = l + r >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
int ask(int p, int l, int r, int x){
	if(l <= t[p].l && r >= t[p].r)return t[p].s[x];
	int mid = t[p].l + t[p].r >> 1;
	int ret = 0;
	if(l <= mid)ret += ask(p << 1, l, r, x);
	if(r > mid)ret += ask(p << 1 | 1, l, r, x);
	return ret;
}
void tql(int p, int x, int d){
	t[p].s[d]--;
	if(t[p].l == t[p].r){
		return;
	}
	int mid = t[p].l + t[p].r >> 1;
	if(mid < x && t[p >> 1 | 1].s[d] >= 1)tql(p << 1 | 1, x, d);
	else tql(p << 1, x, d);
}
void add(int p, int x, int d, int f){
	t[p].s[d]++;
	if(t[p].l == t[p].r){
		return;
	}
	int mid = t[p].l + t[p].r >> 1;
	if(x <= mid)add(p << 1, x, d, f);
	else add(p << 1 | 1, x, d, f);
}
int n, b[N];
priority_queue<pair<int, int> >q;
struct node{
	int x, y, t;
}a[N];
signed main(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		scanf("%d%d%d", &a[i].x, &a[i].t, &a[i].y);
		b[i] = a[i].t;
	}
	sort(b + 1, b + n + 1);
	build(1, 1, M);
	for(int i = 1;i <= n;i++){
		a[i].t = lower_bound(b + 1, b + n + 1, a[i].t) - b;
		if(a[i].x == 1){
			add(1, a[i].t, a[i].y, 1);
		}
		else if(a[i].x == 2){
			q.push({-a[i].t, a[i].y});
//			tql(1, a[i].t, a[i].y);
		}
		else {
			while(q.size() && a[i].t >= -q.top().first){
				tql(1, -q.top().first, q.top().second);
				q.pop();
			}
			printf("%d\n", ask(1, 1, a[i].t, a[i].y));
		}
	}
	return 0;
}

---

## 作者：JWRuixi (赞：1)

~~写到一半脑子短路，以为错了，实际上是对的。~~

- 题意

维护一个待时间戳的 `multiset`，进行 $n$ 此操作。
1. `1 t x`，在时间 $t$ 加入一个数 $x$。
2. `2 t x`，在时间 $t$ 删除一个数 $x$。
3. `3 t x`，查询时间为 $t$ 时，`multiset` 中 $x$ 的数量。

- 分析

考虑一个修改 $i$ 对询问 $j$ 有贡献当且仅当 $i<j,t_i<t_j,x_i=x_j$，发现好棒耶，这是个二维偏序，直接 cdq 分治就行了，因为不需要树状数组所以时间复杂度 $\mathcal O(n\log n)$，不会 cdq 分治的出门右转我的博客 [CDQ 分治笔记](https://www.luogu.com.cn/blog/BingAD/cdq-fen-zhi-bi-ji)。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define LL long long
using namespace std;

namespace IO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
#if ONLINE_JUDGE
#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
#else
#define gh() getchar()
#endif
    inline long long read () {
        char ch = gh();
        long long x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void write(long long x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9)
            write(x / 10);
        putchar(x % 10 + '0');
    }
}

using IO::read;
using IO::write;

const int maxn(1e5 + 500);
int n, dsp[maxn], len, sum[maxn], ans[maxn], tot;

struct Node {
    int t, x, v, id;
} q[maxn];

inline void cdq (int l, int r) {
    if (l == r) return;
    const int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    int i = l, j = mid + 1;
    for (; j <= r; j++) {
        for (; i <= mid && q[i].t < q[j].t; i++) 
            if (!q[i].id) sum[q[i].x] += q[i].v;
        if (q[j].id) ans[q[j].id] += sum[q[j].x];
    }
    for (int k = l; k < i; k++) if (!q[k].id) sum[q[k].x] -= q[k].v;
    inplace_merge(q + l, q + mid + 1, q + r + 1, [] (const Node &x, const Node &y) -> bool { return x.t < y.t; });
}

int main () {
    n = read();
    for (int i = 1, opt, t, x; i <= n; i++) {
        opt = read(), t = read(), x = read();
        if (opt == 1) q[i] = {t, x, 1, 0};
        else if (opt == 2) q[i] = {t, x, -1, 0};
        else q[i] = {t, x, 0, ++tot};
        dsp[++len] = x;
    }
    sort(dsp + 1, dsp + len + 1);
    len = unique(dsp + 1, dsp + len + 1) - dsp - 1;
    for (int i = 1; i <= n; i++) q[i].x = lower_bound(dsp + 1, dsp + len + 1, q[i].x) - dsp;
    cdq(1, n);
    for (int i = 1; i <= tot; i++) write(ans[i]), putchar('\n');
}
// I love WHQ!
```

---

## 作者：_dijkstra_ (赞：1)

cdq 分治。

将 $x$ 离散化。

只要 $p_i.time \le p_j.time$ 即可统计。

小于时看 $p_i.op = 1$ 与 $2$ 的情况，大于时统计 $p_i.op = 3$ 的答案。

代码如下，码风非主流，凑合着看看。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct Data {
	int o, t, v, i;
} a[100010], t[100010];
int cnt[100010], ans[100010];
void cdq(int l, int r) {
	if (l >= r) {
		return;
	}
	int mid = (l + r) / 2;
	cdq(l, mid), cdq(mid + 1, r);
	int L = l, R = mid + 1, tot = 0;
	while (L <= mid && R <= r)
		if (a[L].t <= a[R].t) {
			if (a[L].o == 1) {
				cnt[a[L].v]++;
			}
			if (a[L].o == 2) {
				cnt[a[L].v]--;
			}
			tot++, t[tot] = a[L], L++;
		} else {
			if (a[R].o == 3) {
				ans[a[R].i] += cnt[a[R].v];
			}
			tot++, t[tot] = a[R], R++;
		}
	while (L <= mid) {
		tot++, t[tot] = a[L], L++;
	}
	while (R <= r) {
		if (a[R].o == 3) {
			ans[a[R].i] += cnt[a[R].v];
		}
		tot++, t[tot] = a[R], R++;
	}
	for (int i = l; i <= mid; i++) {
		cnt[a[i].v] = 0;
	}
	for (int i = l, j = 1; j <= tot; i++, j++) {
		a[i] = t[j];
	}
}
int A[100010];
int main() {
	int n, r = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &a[i].o, &a[i].t, &a[i].v);
		A[i] = a[i].v;
		if (a[i].o == 3) {
			r++, a[i].i = r;
		}
	}
	sort(A + 1, A + n + 1);
	int aaaa = unique(A + 1, A + n + 1) - A + 1;
	for (int i = 1; i <= n; i++) {
		a[i].v = lower_bound(A + 1, A + aaaa + 1, a[i].v) - A;
	}
	cdq(1, n);
	for (int i = 1; i <= r; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：wgyhm (赞：1)

# 【水题解记录】CF641E Little Artem and Time Machine

## 题意

给你一个带时间戳的可重集，进行 $n$ 次操作：

1. 在 $t$ 时刻插入一个 $x$
2. 在 $t$ 时刻删除一个 $x$
3. 询问在 $t$ 时刻有几个 $x$

在 $t$ 时刻操作会对之后的可重集影响。

操作按照给定的顺序进行。

$1\le n\le 10^5$

## 题解

对于不同的 $x$ ，其操作是独立的。所以我们以 $x$ 为第一关键字，给定顺序为第二关键字进行排序。

在相同的 $x$ 下，对于时刻 $t$ ，会影响之后的时刻。暴力是单点修改，区间求和。用树状数组优化即可。注意要离散化。

最后按照顺序输出。

复杂度 $O(n\log n)$。

## Code

```cpp
#define maxn 100005
struct node{int op,id,x,cur;}f[maxn];
inline bool cmp(node x,node y){
	if (x.x^y.x) return x.x<y.x;
	return x.cur<y.cur;
}
int g[maxn],n,ans[maxn];
struct BIT{
	#define lowbit(x) ((x)&(-x))
	int f[maxn];
	inline void add(int x,int y){rg int i;for (i=x;i<=n;i+=lowbit(i)) f[i]+=y;}
	inline int query(int x){rg int i,sum=0;for (i=x;i;i-=lowbit(i)) sum+=f[i];return sum;}
}t;//树状数组
signed main(){
	rg int i,j,l,r,mid,pus;
	memset(ans,-1,sizeof(ans));
	read(n);
	for (i=1;i<=n;i++) read(f[i].op),read(f[i].id),read(f[i].x),f[i].cur=i,g[i]=f[i].id;
	sort(g+1,g+1+n);
	int tot=unique(g+1,g+1+n)-g-1;
	for (i=1;i<=n;i++){
		l=0;r=tot+1;
		while (l+1<r){
			mid=l+r>>1;
			if (g[mid]<=f[i].id) l=mid;
			else r=mid;
		}
		f[i].id=l;
	}//离散化
	sort(f+1,f+1+n,cmp);
	for (i=1;i<=n;i++){
		for (j=i;j<=n+1;j++) if (f[i].x^f[j+1].x) break;pus=j;
		for (j=i;j<=pus;j++){
			if (f[j].op==1) t.add(f[j].id,1);
			else if (f[j].op==2) t.add(f[j].id,-1);
			else ans[f[j].cur]=t.query(f[j].id);
		}
		for (j=i;j<=pus;j++){
			if (f[j].op==1) t.add(f[j].id,-1);
			else if (f[j].op==2) t.add(f[j].id,1);
		}
		i=pus;
	}
	for (i=1;i<=n;i++) if (ans[i]!=-1) printf("%d\n",ans[i]);
	return 0;
}
```





---

## 作者：chengni (赞：1)

根据题意，直接使用离散化树状数组按题意操作即可

树状数组要开 map

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read(){
	char ch=getchar();ll x=0,f=1;
    while(ch<'0' || ch>'9') {
       if(ch=='-') f=-1;
	  	  ch=getchar();
	}
    while(ch<='9' && ch>='0') {
	   x=x*10+ch-'0';
	   ch=getchar();
	}
    return x*f;
}


map<int,int> s[1010011],vis;

int lowbit(int x){
	return x&-x;
}

void add(int k,int x,int v){
	while(k<1e9+7){
		s[x][k]+=v;
		k+=lowbit(k);
	}
}

int ans(int k,int x){
	int res=0;
	while(k){
		res+=s[x][k];
		k-=lowbit(k);
	}
	return res;
}

int cnt=0;

int q[2002002],t[2020002],x[2020022];
int y[2020022];
int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		q[i]=read(),t[i]=read(),x[i]=read();
		y[i]=x[i];
	}
	sort(y+1,y+n+1);
	for(int i=1;i<=n;i++){
		if(y[i]!=y[i-1]){
			cnt++;
			vis[y[i]]=cnt;
		}
	}
	for(int i=1;i<=n;i++){
		if(q[i]==1){
			add(t[i],vis[x[i]],1);
		}
		if(q[i]==2){
			add(t[i],vis[x[i]],-1);
		}
		if(q[i]==3){
			cout<<ans(t[i],vis[x[i]])<<endl;
		}
	}

	return 0;
}
```

还有一种 cdq 的做法

第一维是给的顺序，第二维是时间顺序，开个 map 桶记录答案

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

inline ll read(){
	char ch=getchar();ll x=0,f=1;
    while(ch<'0' || ch>'9') {
       if(ch=='-') f=-1;
	  	  ch=getchar();
	}
    while(ch<='9' && ch>='0') {
	   x=x*10+ch-'0';
	   ch=getchar();
	}
    return x*f;
}


struct node{
	int t,x,id,q;
}t[4040045];

int v[2020022];
int ans[2020022];

bool cmp1(node a,node b){
	return a.t<b.t;
}

bool cmp(node a,node b){
	return a.id<b.id;
}

map<int,int> s;

void cdq(int l,int r){
	if(l==r) return;
	int mid=l+r>>1;
	cdq(l,mid);cdq(mid+1,r);
	sort(t+l,t+r+1,cmp1);
	for(int i=l;i<=r;i++){
		node x=t[i];
		if(x.id<=mid){
			if(x.q==1) s[x.x]++;
			if(x.q==2) s[x.x]--;
		}
		else if(x.q==3){
			ans[x.id]+=s[x.x];
		}
	}
	for(int i=l;i<=r;i++){
		node x=t[i];
		if(x.id<=mid){
			if(x.q==1) s[x.x]--;
			if(x.q==2) s[x.x]++;
		}
	}
	sort(t+l,t+r+1,cmp);
}

int main(){
	int n=read();
	for(int i=1;i<=n;i++){
		t[i].q=read();
		t[i].t=read();
		t[i].x=read();
		t[i].id=i;
		if(t[i].q==3) v[i]=1;
	}
	cdq(1,n);
	for(int i=1;i<=n;i++){
		if(v[i]){
			cout<<ans[i]<<endl;
		}
	} 
	return 0;
}




```

---

## 作者：zimindaada (赞：1)

[博客宣传](https://www.luogu.com.cn/blog/zimindaada/)

[CF641E 题面](https://www.luogu.com.cn/problem/CF641E)

这一道题是一道很好的```CDQ```的练手题。我们根据[模板题](https://www.luogu.com.cn/problem/P3810)的思路，可以想出来这一道题的三个值按顺序分别为 $a$ : 输入顺序， $b$ : 输入中的时间顺序（即$t$)， $c$ :输入中的值$x$。我们所需的左半区间对右半区间的贡献为：若左半区间有$a_i$，右半区间有$a_j$，则当$a_i.a < a_j.a, \space a_i.b \leq a_i.b, \space a_i.c=a_j.c$的时候，$a_i$对$a_j$有贡献。由于初始输入决定了$a$有序，所以只需对第二维排序，用桶维护第三维即可。
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
namespace ztd{
    using namespace std;
    #define reg register
    #define ms(a) memset(a,0,sizeof(a))
    typedef long long ll;
    typedef unsigned long long ull;
    typedef unsigned int uint;
    typedef double db;
    //basic I/O
    template<typename T> inline T read(T& t) {//fast read
        t=0;short f=1;char ch=getchar();double d = 0.1;
        while (ch<'0'||ch>'9') {if (ch=='-') f=-f;ch=getchar();}
        while (ch>='0'&&ch<='9') t=t*10+ch-'0',ch=getchar();
        if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
        t*=f;
        return t;
    }
}
using namespace ztd;
const int maxn = 2e5+7;
int n, m, len;

struct node{int a, b, c, opt;}a[maxn];
int ac[maxn], ab[maxn], b[maxn], tmp[maxn], ans[maxn], opt[maxn];
bool cmp(node x, node y){
	return x.a<y.a;
}
bool cmp2(node x, node y){
	return x.b<y.b;
}

int lsh(int *a, int n){
//离散化，由于值太大，n比较小，所以适合用桶+离散化，比map要快。
	for(int i = 1; i <= n; ++i) tmp[i] = a[i];
	sort(tmp+1,tmp+n+1);
	int l = unique(tmp+1,tmp+n+1) - tmp - 1;
	for(int i = 1; i <= n; ++i) a[i] = lower_bound(tmp+1, tmp+l+1, a[i]) - tmp;
	return l;
}

void CDQ(int l, int r){
	if(l == r) return;
	int mid = (l+r)>>1;
	CDQ(l, mid); CDQ(mid+1, r);
	sort(a+l, a+r+1, cmp2);
	for(int i = l; i <= r; ++i){
        if(a[i].a <= mid){
            if(a[i].opt ^ 3)
			    b[a[i].c] += ((a[i].opt == 1) ? 1 : -1);
		}else if(a[i].opt == 3) {
            ans[a[i].a] += b[a[i].c];
        }
	}
	
    //把桶带来的修改删掉
	for(int i = l; i <= r; ++i){
		if(a[i].a <= mid && a[i].opt ^ 3){
			b[a[i].c] += ((a[i].opt == 1) ? -1 : 1);
		}
	}
	sort(a+l,a+r+1, cmp);
}
signed main(){
	read(n);
	for(int i = 1; i <= n; ++i){ 
		opt[i] = read(a[i].opt); 
		a[i].a = i;//id
		read(ab[i]);/*t*/ read(ac[i]); /*value or "x" */
	}
	lsh(ab,n); lsh(ac, n);
	for(int i = 1; i <= n; ++i) {
		a[i].b = ab[i], a[i].c = ac[i];
	}
	CDQ(1,n);
	for(int i = 1; i <= n; ++i){
    	//注意！因为只要操作3才要输出，且cdq会打乱顺序，所以要记录opt顺序
		if(opt[i] == 3) printf("%d\n", ans[i]);
	}
	return 0;
}
/*
自己编的数据
input 1:
6
1 4 6
1 2 8
1 3 8
2 3 8
2 2 8
3 7 8
output 1:
0

input 2:
4
1 4 6
1 2 8
2 2 8
3 7 8

output 2:
0

*/

```

# 这就完了？就这？

其实这一道题还有另外一种做法，就是离散化加树状数组。这里用的是```map```，防止内存爆炸。很好理解，就是所有的输入塞到一个树状数组，维护后缀和。

```cpp
#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
template<typename T> inline T read(T& t) {//fast read
    t=0;short f=1;char ch=getchar();double d = 0.1;
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f;ch=getchar();}
    while (ch>='0'&&ch<='9') t=t*10+ch-'0',ch=getchar();
    if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
    t*=f;
    return t;
}
typedef map<int,int> mii;
const int maxn = 1e5+7;
int n, opt[maxn], t[maxn], a[maxn], tmp[maxn+5], len;
int lsh(int *a, int n){
	for(int i = 1; i <= n; ++i) tmp[i] = a[i];
	sort(tmp+1,tmp+n+1);
	int l = unique(tmp+1,tmp+n+1) - tmp - 1;
	for(int i = 1; i <= n; ++i) a[i] = lower_bound(tmp+1, tmp+l+1, a[i]) - tmp;
	return l;
}


mii T[maxn];
inline int lowbit(int x){return x & -x;}
void add(int c, int x, int k){
	while(x <= len){
		T[c][x] += k;
		x += lowbit(x);
	}
}
int ask(int c, int x){
    int ans = 0;
    while(x){
    	ans += T[c][x];
        x -= lowbit(x);
    }
    return ans;
}


int main(){
	read(n);
	for(int i = 1; i <= n; ++i){ read(opt[i]); read(t[i]); read(a[i]); }
	lsh(a,n); len = lsh(t,n);
	for(int i = 1; i <= n; ++i){
		if(opt[i] == 1) add(a[i], t[i], 1);
		else if(opt[i] == 2) add(a[i], t[i], -1);
		else printf("%d\n", ask(a[i], t[i]));
	}
	return 0;
}
```

---

## 作者：LEE114514 (赞：0)

## 思路：离线树状数组

首先，因为每个 $x$ 的处理方式相同，发现可以通过离线处理规避掉 $x$ 这个条件，所以只需要考虑一条时间轴上的操作。

然后我们发现需要的操作可以转化成单点加减 $1$，前缀求和，于是把 $t$ 离散化之后维护一个树状数组。

复杂度 $O(n \log n)$。

实现时只维护一颗树状数组，把所有 $x$ 相同的剥离出来一起处理，详见代码。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
vector<int> lsh;
int n,x;
int opp[maxn][3];
vector<int> op[maxn];
int ans[maxn];
int trr[maxn];
void add(int p,int x){
	while(p<=1e5) trr[p]+=x,p+=p&-p;
}
int qry(int p){
	int res=0;
	while(p) res+=trr[p],p^=p&-p;
	return res;
}
vector<pair<int,int> > backup;
void mdf(int pos,int x){
	backup.emplace_back(pos,x);
	add(pos,x);
}
void init(){
	for(auto iter:backup) add(iter.first,-iter.second);
	backup.clear();
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i) cin>>opp[i][0]>>opp[i][1]>>opp[i][2],lsh.emplace_back(opp[i][2]);

	sort(lsh.begin(),lsh.end());
	lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
	for(int i=1;i<=n;++i) opp[i][2]=lower_bound(lsh.begin(),lsh.end(),opp[i][2])-lsh.begin();

	for(int i=1;i<=n;++i) op[opp[i][2]].emplace_back(i);//按照 x 分离

	int len=lsh.size();
	for(int i=0;i<len;++i){
		lsh.clear();
		for(auto iter:op[i]) lsh.emplace_back(opp[iter][1]);
		sort(lsh.begin(),lsh.end());
		lsh.erase(unique(lsh.begin(),lsh.end()),lsh.end());
		for(auto iter:op[i]) opp[iter][1]=lower_bound(lsh.begin(),lsh.end(),opp[iter][1])-lsh.begin()+1;

		for(auto iter:op[i]){
			if(opp[iter][0]==1) mdf(opp[iter][1],1);
			else if(opp[iter][0]==2) mdf(opp[iter][1],-1);
			else ans[iter]=qry(opp[iter][1]);
		}
		init();
	}
	for(int i=1;i<=n;++i) if(opp[i][0]==3) cout<<ans[i]<<'\n';
}
```

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P8575)

# 前置知识

[CDQ 分治](https://oi-wiki.org/misc/cdq-divide/) 

# 解法

单点修改区间查询，但值域巨大，考虑离散化掉 $x$。

时刻 $t$ 仍很大，考虑将其作为 CDQ 分治的第一维，然后套个 CDQ 分治即可，注意及时清空桶数组。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct node
{
	int pd,pos,val,col,id;
	bool operator < (const node &another) const
	{
		return (pos==another.pos)?(pd>another.pd):(pos<another.pos);
	}
}a[300010],tmp[300010];
int b[300010],ans[300010],sum[300010],cnt=0,q_cnt=0;
void add(int pd,int pos,int val,int col,int id)
{
	cnt++;
	a[cnt].pd=pd;
	a[cnt].pos=pos;
	a[cnt].val=val;
	a[cnt].col=col;
	a[cnt].id=id;
}
void cdq(int l,int r)
{
	if(l>=r)
	{
		return;
	}
	int mid=(l+r)/2,x=l,y=mid+1,pos=l;
	cdq(l,mid);
	cdq(mid+1,r);
	while(x<=mid&&y<=r)
	{
		if(a[x]<a[y])
		{
			sum[a[x].col]+=a[x].pd*a[x].val;
			tmp[pos]=a[x];
			pos++;
			x++;
		}
		else
		{
			ans[a[y].id]+=a[y].val*sum[a[y].col];
			tmp[pos]=a[y];
			pos++;
			y++;
		}
	}
	while(x<=mid)
	{
		tmp[pos]=a[x];
		pos++;
		x++;
	}
	while(y<=r)
	{
		ans[a[y].id]+=a[y].val*sum[a[y].col];
		tmp[pos]=a[y];
		pos++;
		y++;
	}
	for(int i=l;i<=mid;i++)
	{
		sum[a[i].col]=0;
	}
	for(int i=l;i<=r;i++)
	{
		a[i]=tmp[i];
	}
}
int main()
{
	int n,pd,t,x,i;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>pd>>t>>x;
		b[i]=x;
		if(pd==1)
		{
			add(1,t,1,x,0);
		}
		if(pd==2)
		{
			add(1,t,-1,x,0);
		}
		if(pd==3)
		{
			q_cnt++;
			add(0,t,1,x,q_cnt);
		}
	}
	sort(b+1,b+1+n);
	b[0]=unique(b+1,b+1+n)-(b+1);
	for(i=1;i<=n;i++)
	{
		a[i].col=lower_bound(b+1,b+1+b[0],a[i].col)-b;
	}
	cdq(1,cnt);
	for(i=1;i<=q_cnt;i++)
	{
		cout<<ans[i]<<endl;
	}
	return 0;
} 
```

---

## 作者：Luciylove (赞：0)

[题面](https://www.luogu.com.cn/problem/CF641E)。

- 题意 ：

给定一个 带 **时间戳** 的 **可重集** （一开始为 **空集**）， 每次进行以下几种操作。

1. 在时刻 $t$ 加入一个数 $x$

1. 在时刻 $t$ 删除一个数 $x$

1. 在时刻 $t$ 查询一个数 $x$ 的出现次数

- 思路 :

在线很棘手，考虑离线下来做。用一个状态四元组 $(tim, b,c, d)$ 去表示一个操作。

分别表示为 第 $tim$ 个操作，第 $op$ 种操作， 第 $b$ 号时间，元素为 $c$, 对于元素的出现次数影响为 $d$ (若为查询则为 $0$ ).

然后对于一个 第 $tim$ 个操作为询问 的答案就是 :

$$\sum_{i < tim} \sum_{a[i].b \leq b,a[i].c = c}a[i].d$$

显然，这变成了一个三维偏序问题，做 $CDQ$ 分治即可。
可以考虑容斥, 也可以开个桶去解决，后者加个离散化和前者一样。

- 代码 :

桶使用 $map$ 来实现，总时间复杂度为 $O(n\log^2n)$ 。

```cpp
// Coding by Custlo

// Tag : CDQ Method 

// Time : 2022 - 3 - 26

#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cmath>
#include <map>

using namespace std;

const int N = 2e5 + 5;

inline int read () {
    int ans = 0; char c = getchar(), last = ' ';
    while(c < '0' || c > '9') last = c,c = getchar();
    while(c >= '0' && c <= '9') ans = (ans << 1) + (ans << 3) + c - '0',c = getchar();
    return last == '-' ? - ans : ans;
}

map <int, int> exists; 

struct NODE {
	int a, b, c, op;
} a[N];
// 状态
inline bool cmp (NODE a, NODE b) { return a.a < b.a; }
inline bool cmp2 (NODE a, NODE b) { return a.b < b.b; }

int n, op[N], res[N];
inline void CdqMethod (int l, int r) {
	if (l == r) return ;
	int mid = (l + r) >> 1;
	CdqMethod(l, mid), CdqMethod(mid + 1, r);
	sort(a + l, a + r + 1, cmp2);
	for (int i = l; i <= r; i ++) {
		if (a[i].a <= mid ) {
            if (a[i].op != 3) exists[a[i].c] += (a[i].op == 1 ? 1 : -1); // 计算贡献
        }
        else if (a[i].op == 3) res[a[i].a] += exists[a[i].c]; // 求答案
	}
	for (int i = l; i <= r; i ++)
		if (a[i].a <= mid && a[i].op != 3) exists[a[i].c] -= (a[i].op == 1 ? 1 : -1); // 撤销贡献
	sort(a + l, a + r + 1, cmp);
} // cdq 分治
int main () {
	n = read();
	for (int i = 1; i <= n; i ++) {
		op[i] = a[i].op = read(), a[i].a = i, a[i].b = read(), a[i].c = read(); 
	}
	CdqMethod(1, n);
	for (int i = 1; i <= n; i ++) if (op[i] == 3) printf("%d\n", res[i]); // 输出答案
	return 0;
}
```



---

