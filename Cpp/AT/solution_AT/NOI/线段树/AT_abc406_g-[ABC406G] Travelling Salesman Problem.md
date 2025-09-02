# [ABC406G] Travelling Salesman Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc406/tasks/abc406_g

在数轴上，有你和 $N$ 个商人。商人编号为 $1, 2, \ldots, N$。

开始时，你在坐标 $0$ 处，商人 $i$ 在坐标 $X_i$ 处。此外，每个商人都持有一个物品，商人 $i$ 持有的物品记为物品 $i$。

你的目标是按顺序接收物品 $1, 2, \ldots, N$。

你可以按任意顺序重复任意次数以下三种操作：

-   你自己移动 $1$ 个单位长度。此操作的成本为 $C$。
-   选择一个商人，让选定的商人移动 $1$ 个单位长度。此操作的成本为 $D$。
-   选择一个商人，设选定的商人为商人 $i$。如果你和商人 $i$ 所在的坐标相同，并且你还没有从商人 $i$ 那里收到物品，则从商人 $i$ 那里接收物品 $i$。否则，不执行任何操作。此操作的成本为 $0$。

请找出达成目标所需的最小总成本。

此外，请找出在最小化达成目标所需总成本时，可以作为从每个商人处接收物品的坐标的一种可能方案。

## 说明/提示

**「数据范围」**

-   $1 \leq N \leq 2 \times 10^5$
-   $1 \leq C, D \leq 10^5$
-   $-10^5 \leq X_i \leq 10^5$
-   输入的所有值均为整数

**「样例 1 解释」**

例如，通过如下操作，可以使总成本为 $10$ 并达成目标。
-   让商人 $1$ 从坐标 $1$ 移动到坐标 $0$。此操作的成本为 $3$。
-   让商人 $2$ 从坐标 $-1$ 移动到坐标 $0$。此操作的成本为 $3$。
-   从商人 $1$ 处接收物品 $1$。此操作的成本为 $0$。
-   从商人 $2$ 处接收物品 $2$。此操作的成本为 $0$。
-   你从坐标 $0$ 移动到坐标 $1$。此操作的成本为 $2$。
-   你从坐标 $1$ 移动到坐标 $2$。此操作的成本为 $2$。
-   从商人 $3$ 处接收物品 $3$。此操作的成本为 $0$。
无法以低于 $10$ 的总成本达成目标。

## 样例 #1

### 输入

```
3 2 3
1 -1 2```

### 输出

```
10
0 0 2```

## 样例 #2

### 输入

```
2 100000 60000
100000 -100000```

### 输出

```
12000000000
0 0```

## 样例 #3

### 输入

```
6 4 4
2 -1 5 -2 -2 2```

### 输出

```
56
0 -1 -1 -2 -2 2```

# 题解

## 作者：EricWan (赞：7)

比较优秀的一道 slope trick 题目。是一个练习带权 slope trick 的题，并不需要手写数据结构加速。

Rosabel 大佬的线段树解法太长了，像我这样的刚学 OI 的萌新完全写不了，这里介绍一种很玄学的 `std::map` 维护的方法。

我的方法大部分来自[官方题解](https://atcoder.jp/contests/abc406/editorial/13055)，一部分来自 [Rosabel 大佬的题解](https://www.luogu.com.cn/article/ool4tjy6)，如果部分推理过程与官方题解雷同，属正常现象。

不会维护拐点的 slope trick 的人看起来可能比较费劲。

## 开始讲解

先不思考如何记录过程，下面先说一下转移方法。

考虑朴素 DP，定义 $f_{i,j}$ 为吃掉前 $i$ 个商人后，位置在 $j$ 的最小代价，范围为 $i\in[0,n]$ 和 $j\in[\min x,\max x]$，初始化为 $f_{0,j}=c\times|j|$，答案为 $\min f_{n,j}$。

转移为 $dp_{i,j}=\min dp_{i-1,k}+c\times|j-k|+d\times|x_i-j|$，其中 $c\times|j-k|$ 表示移动 You，$d\times|x_i-j|$ 表示移动商人。

下面开始考虑如何维护。

这是一个基础的带权 slope trick 题目，后面讲得会很慢，

两步分开处理，我们用经典的 slope trick 维护方法，左右各开一个数据结构维护拐点信息，平常我们都是使用 `std::priority_queue` 或者 `std::multiset` 维护，但是这一题中拐点斜率变化量可以达到 $O(n\times c)$ 级别，因此改为 `std::map`。（我是不会告诉你我不会自己写数据结构的）

我们用两个 `std::map` 维护拐点，斜率为 $0$ 的段（或点）左右分别为 $L$ 和 $R$，每一对 $(Key,Value)$ 代表函数 $f$ 在 $Key$ 处斜率变化了 $Value$。

上面的过程中，第一步形如让斜率小于 $-c$ 的都变为 $-c$，斜率大于 $c$ 的都变为 $c$，这对应在左右两只 `std::map` 上的维护就是不断删或减小每一侧的 `std::map` 的 `Value`，直到每一侧的 `Value` 和均为 $c$。

第二步形如插入一个绝对值的倍数，这是维护拐点的 slope trick 很 static 的操作，将这玩意分为 $d$ 个 $(x_i-j)_+$ 和 $d$ 个 $(j-x_i)_+$。考虑到插入一堆基础函数后，DP 数组 $f$ 值取 $\min f$ 的点可能无法在点 $\min\{R\}$ 或 $\max\{L\}$ 上了，我们就需仔细地维护 $\min f$。这里我们就必须一点一点维护 $\min f$，形象的说，就是一点一点插入那 $2d$ 个基础函数，慢慢地转这个，每次根据到底是加入 $(x_i-j)_+$ 还是 $(j-x_i)_+$ 只插入 $\max\{L\}.Value$ 或 $\min\{R\}.Value$ 个。

因此我们就可以写出一个最基础的代码了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, c, d, Lcnt, Rcnt, x[1000005], minf;
map<int, int> L, R;
signed main() {
	cin >> n >> c >> d;
	L[0] = R[0] = c;
	Lcnt = Rcnt = c;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		while (Lcnt > c) { // 削掉 < -c 的斜率
			if (L.begin()->second > Lcnt - c) {
				L.begin()->second -= Lcnt - c;
				Lcnt = c;
			} else {
				Lcnt -= L.begin()->second;
				L.erase(L.begin());
			}
		}
		while (Rcnt > c) { // 削掉 > c 的斜率
			if ((--R.end())->second > Rcnt - c) {
				(--R.end())->second -= Rcnt - c;
				Rcnt = c;
			} else {
				Rcnt -= (--R.end())->second;
				R.erase(--R.end());
			}
		}
		int add_k = d;
		if (R.begin()->first >= x[i]) { // 插入 (j-x[i])+
			L[x[i]] += add_k;
		} else {
			int td = add_k;
			while (td) {
				if (R.begin()->second > td) { // 当前的 min{R}.Value 已经够大了，將剩下的 td 个 (j-x[i])+ 全部插入，minf 还可以在 min{R} 取值
					minf += max(0ll, x[i] - R.begin()->first) * td;
					L[R.begin()->first] += td;
					R.begin()->second -= td;
					R[x[i]] += td;
					td = 0;
				} else {
					int num = R.begin()->second; // 当前的 min{R}.Value 不够大，先放进去 min{R}.Value 个 (j-x[i])+，minf 可以在 min{R} 取值
					minf += max(0ll, x[i] - R.begin()->first) * num;
					td -= num;
					L[R.begin()->first] += num; // 随后是维护拐点的 slope trick 的标准代码
					R.erase(R.begin());
					R[x[i]] += num; // 这次只放 min{R}.Value 个，并让新的新的 minf 可以在新的 min{R}.Value 上取到
				}
			}
		}
		if ((--L.end())->first <= x[i]) { // 插入 (x[i]-j)+，同理
			R[x[i]] += add_k;
		} else {
			int td = add_k;
			while (td) {
				map<int, int>::iterator it = --L.end();
				if (it->second > td) {
					minf += max(0ll, it->first - x[i]) * td;
					R[it->first] += td;
					it->second -= td;
					L[x[i]] += td;
					td = 0;
				} else {
					int num = it->second;
					minf += max(0ll, it->first - x[i]) * num;
					td -= num;
					R[it->first] += num;
					L.erase(it);
					L[x[i]] += num;
				}
			}
		}
		Lcnt += add_k; // 维护一下 L 和 R 的和
		Rcnt += add_k;
	}
	cout << minf << endl;
	return 0;
}
```

但是这个会 TLE 九个点，为什么？因为复杂度不正确，如果这个 $c$ 恰好卡出了一堆 $Value$ 很小的节点然后 $x$ 不断在 $-\inf$ 和 $+\inf$ 之间跳，我们会把这些 $Value$ 特别小的折点不断地在 $L$ 和 $R$ 间移动。

怎么优化？我们可以只插入 $\min\{d,2\times c\}$ 个函数，可以证明，这样正确性是没影响的（因为插入多了也会被有关 $c$ 的限制砍掉）。

我们将代码中的 `add_k` 设为 $\min\{d,2\times c\}$ 就可以正确而快速地算出答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, c, d, Lcnt, Rcnt, x[1000005], minf;
map<int, int> L, R;
signed main() {
	cin >> n >> c >> d;
	L[0] = R[0] = c;
	Lcnt = Rcnt = c;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		while (Lcnt > c) { // 削掉 < -c 的斜率
			if (L.begin()->second > Lcnt - c) {
				L.begin()->second -= Lcnt - c;
				Lcnt = c;
			} else {
				Lcnt -= L.begin()->second;
				L.erase(L.begin());
			}
		}
		while (Rcnt > c) { // 削掉 > c 的斜率
			if ((--R.end())->second > Rcnt - c) {
				(--R.end())->second -= Rcnt - c;
				Rcnt = c;
			} else {
				Rcnt -= (--R.end())->second;
				R.erase(--R.end());
			}
		}
		int add_k = min(d, 2 * c);
		if (R.begin()->first >= x[i]) { // 插入 (j-x[i])+
			L[x[i]] += add_k;
		} else {
			int td = add_k;
			while (td) {
				if (R.begin()->second > td) { // 当前的 min{R}.Value 已经够大了，將剩下的 td 个 (j-x[i])+ 全部插入，minf 还可以在 min{R} 取值
					minf += max(0ll, x[i] - R.begin()->first) * td;
					L[R.begin()->first] += td;
					R.begin()->second -= td;
					R[x[i]] += td;
					td = 0;
				} else {
					int num = R.begin()->second; // 当前的 min{R}.Value 不够大，先放进去 min{R}.Value 个 (j-x[i])+，minf 可以在 min{R} 取值
					minf += max(0ll, x[i] - R.begin()->first) * num;
					td -= num;
					L[R.begin()->first] += num; // 随后是维护拐点的 slope trick 的标准代码
					R.erase(R.begin());
					R[x[i]] += num; // 这次只放 min{R}.Value 个，并让新的新的 minf 可以在新的 min{R}.Value 上取到
				}
			}
		}
		if ((--L.end())->first <= x[i]) { // 插入 (x[i]-j)+，同理
			R[x[i]] += add_k;
		} else {
			int td = add_k;
			while (td) {
				map<int, int>::iterator it = --L.end();
				if (it->second > td) {
					minf += max(0ll, it->first - x[i]) * td;
					R[it->first] += td;
					it->second -= td;
					L[x[i]] += td;
					td = 0;
				} else {
					int num = it->second;
					minf += max(0ll, it->first - x[i]) * num;
					td -= num;
					R[it->first] += num;
					L.erase(it);
					L[x[i]] += num;
				}
			}
		}
		Lcnt += add_k; // 维护一下 L 和 R 的和
		Rcnt += add_k;
	}
	cout << minf << endl;
	return 0;
}
```

先别走，我们还没有记录方案，记录方案的方法很简单，我们每一次砍完 $c$，留下的 $\min\{L\}$ 和 $\max\{R\}$ 外的点一定是从 $\min\{L\}$ 或 $\max\{R\}$ 转移的，因此记录每一步砍完 $c$ 后的 $\min\{L\}$ 和 $\max\{R\}$ 即可。

输出时，我们知道 $\min f$ 取值的点（$[\max\{L\},\min\{R\}]$ 内的点都行），然后我们倒着计算方案，如果超过了记录的 $\max\{R\}$，就让人退到 $\max\{R\}$，如果超过了记录的 $\min\{L\}$，就让人退到 $\min\{L\}$。

完整代码，91 行，2KB 出头：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, c, d, Lcnt, Rcnt, current_min[1000005], current_max[1000005], x[1000005], minf;
map<int, int> L, R;
signed main() {
	cin >> n >> c >> d;
	L[0] = R[0] = c;
	Lcnt = Rcnt = c;
	for (int i = 1; i <= n; i++) {
		cin >> x[i];
		while (Lcnt > c) { // 削掉 < -c 的斜率
			if (L.begin()->second > Lcnt - c) {
				L.begin()->second -= Lcnt - c;
				Lcnt = c;
			} else {
				Lcnt -= L.begin()->second;
				L.erase(L.begin());
			}
		}
		while (Rcnt > c) { // 削掉 > c 的斜率
			if ((--R.end())->second > Rcnt - c) {
				(--R.end())->second -= Rcnt - c;
				Rcnt = c;
			} else {
				Rcnt -= (--R.end())->second;
				R.erase(--R.end());
			}
		}
		current_min[i] = L.begin()->first;
		current_max[i] = (--R.end())->first;
		int add_k = min(d, 2 * c);
		if (R.begin()->first >= x[i]) { // 插入 (j-x[i])+
			L[x[i]] += add_k;
		} else {
			int td = add_k;
			while (td) {
				if (R.begin()->second > td) { // 当前的 min{R}.Value 已经够大了，將剩下的 td 个 (j-x[i])+ 全部插入，minf 还可以在 min{R} 取值
					minf += max(0ll, x[i] - R.begin()->first) * td;
					L[R.begin()->first] += td;
					R.begin()->second -= td;
					R[x[i]] += td;
					td = 0;
				} else {
					int num = R.begin()->second; // 当前的 min{R}.Value 不够大，先放进去 min{R}.Value 个 (j-x[i])+，minf 可以在 min{R} 取值
					minf += max(0ll, x[i] - R.begin()->first) * num;
					td -= num;
					L[R.begin()->first] += num; // 随后是维护拐点的 slope trick 的标准代码
					R.erase(R.begin());
					R[x[i]] += num; // 这次只放 min{R}.Value 个，并让新的新的 minf 可以在新的 min{R}.Value 上取到
				}
			}
		}
		if ((--L.end())->first <= x[i]) { // 插入 (x[i]-j)+，同理
			R[x[i]] += add_k;
		} else {
			int td = add_k;
			while (td) {
				map<int, int>::iterator it = --L.end();
				if (it->second > td) {
					minf += max(0ll, it->first - x[i]) * td;
					R[it->first] += td;
					it->second -= td;
					L[x[i]] += td;
					td = 0;
				} else {
					int num = it->second;
					minf += max(0ll, it->first - x[i]) * num;
					td -= num;
					R[it->first] += num;
					L.erase(it);
					L[x[i]] += num;
				}
			}
		}
		Lcnt += add_k; // 维护一下 L 和 R 的和
		Rcnt += add_k;
	}
	cout << minf << endl;
	int ans_pos = R.begin()->first;
	vector<int> ans_poss;
	for (int i = n; i >= 1; i--) {
		ans_poss.push_back(ans_pos);
		ans_pos = max(min(current_max[i], ans_pos), current_min[i]);
	}
	reverse(ans_poss.begin(), ans_poss.end());
	for (int i : ans_poss) {
		cout << i << " ";
	}
	return 0;
}
```

---

## 作者：MisaYuzuki (赞：4)

比较优秀的一道 slope trick 题目。

函数的凸性可以在构造过程中归纳证明。对于商家，实际上是提供了一个“V”字形函数与原函数相加，两段斜率分别为 $d$ 和 $-d$；对于自身，实际上是需要把斜率 $\lt-c$ 的拍成 $-c$，同时把斜率 $\gt c$ 的拍成 $c$。由于函数总是递增的，我们需要维护一个斜率序列，支持区间加，区间赋值和查区间 $\min,\max$。线段树可以支持这个操作。

求出答案之后我们需要还原原来操作序列，注意到在执行商家函数的时候实际上每一个点的转移是原原本本继承的，而执行自身函数的时候是把两边的端点继承到两边的所有点上，所以只需要与两边的端点分别取 $\min$ 和取 $\max$ 就好了。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define REP(i,l,r) for(int i=(l);i<=(r);i++)
#define PER(i,r,l) for(int i=(r);i>=(l);i--)
using namespace std;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(isdigit(c)){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const int N=2e5+5;
int n,m=1e5,c,d,lpos[N],rpos[N],nid;
namespace SGT{// 线段树
    struct DP{
        ll minn,maxn,sum,tag,len,tag2;
        void init(int val){
            minn=maxn=sum=val;
            tag=tag2=0,len=1;
        }
        void add(ll v){// 区间加
            minn+=v;maxn+=v;tag+=v;
            sum+=len*v;
        }
        void toval(ll v){// 区间赋值
            minn=maxn=v*d;
            sum=v*d*len;
            tag=0;// 由于区间赋值优先级更大，记得把 tag（区间加的标记）清空
            tag2=v;
        }
        friend DP operator+(DP A,DP B){
            return DP{A.minn,B.maxn,A.sum+B.sum,0,A.len+B.len,0};
        }
    };
    struct node{
        int ch[2];
        DP val;
    }tr[N<<1];
    int rt,idx;
    struct segTree{
        #define lc tr[i].ch[0]
        #define rc tr[i].ch[1]
        #define mid (l+r)/2
        void pushup(int i){
            tr[i].val=tr[lc].val+tr[rc].val;
        }
        void build(int &i,int l,int r){
            i=++idx;
            if(l==r){
                if(l<=m)tr[i].val.init(-d);
                else tr[i].val.init(d);
                return;
            }
            build(lc,l,mid);
            build(rc,mid+1,r);
            pushup(i);
        }
        void lazy(int i,ll v,ll v2=0){// v2 表示是否执行区间赋值的操作，不为零则执行
            if(v2)tr[i].val.toval(v2);
            else tr[i].val.add(v);
        }
        void pushdown(int i){
            if(tr[i].val.tag2){
                lazy(lc,0,tr[i].val.tag2);
                lazy(rc,0,tr[i].val.tag2);
                tr[i].val.tag2=0;
            }
            lazy(lc,tr[i].val.tag);
            lazy(rc,tr[i].val.tag);
            tr[i].val.tag=0;
        }
        void modify(int i,int l,int r,int L,int R,ll v){// 区间加
            if(L<=l&&R>=r){
                lazy(i,v);
                return;
            }
            pushdown(i);
            if(L<=mid)modify(lc,l,mid,L,R,v);
            if(R>mid)modify(rc,mid+1,r,L,R,v);
            pushup(i);
        }
        ll updateL(int i,int l,int r){// 将 < -c 的部分修改为 -c，同时求出改变的总值
            if(tr[i].val.minn>=-d)return 0;
            if(tr[i].val.maxn<-d){
                ll sum=-d*tr[i].val.len-tr[i].val.sum;
                lazy(i,0,-1);
                lpos[nid]=max(lpos[nid],r);
                return sum;
            }
            pushdown(i);
            ll res=0;
            if(tr[lc].val.maxn<-d)res=updateL(lc,l,mid)+updateL(rc,mid+1,r);
            else res=updateL(lc,l,mid);
            pushup(i);
            return res;
        }
        ll updateR(int i,int l,int r){// 将 >c 的部分修改为 c
            if(tr[i].val.maxn<=d)return 0;
            if(tr[i].val.minn>d){
                ll sum=d*tr[i].val.len-tr[i].val.sum;
                lazy(i,0,1);
                rpos[nid]=min(rpos[nid],l-1);
                return sum;
            }
            pushdown(i);
            ll res=0;
            if(tr[rc].val.minn>d)res=updateR(rc,mid+1,r)+updateR(lc,l,mid);
            else res=updateR(rc,mid+1,r);
            pushup(i);
            return res;
        }
        ll query(int i,int l,int r,int x){// 最终查询每个位置的
            if(l==r)return tr[i].val.sum;
            pushdown(i);
            if(x<=mid)return query(lc,l,mid,x);
            else return query(rc,mid+1,r,x);
        }
        #undef lc
        #undef rc
        #undef mid
    }sgt;
}
using namespace SGT;
int ans[N];
int main(){
    n=read(),d=read(),c=read();// 这里由于是考场代码把 c 和 d 弄混了，带来阅读不便感到抱歉
    sgt.build(rt,1,2*m);
    ll sum=1ll*m*d,res=0;
    REP(i,1,n){
        nid=i;
        rpos[i]=2*m;
        sum-=sgt.updateL(rt,1,2*m);
        sgt.updateR(rt,1,2*m);
        int x=read()+m;// 注意先操作自身再操作商家，因为自身的决策是根据上一轮决定的，而商家的贡献不影响这一轮的决策
        if(1<=x)sgt.modify(rt,1,2*m,1,x,-c);
        if(x+1<=2*m)sgt.modify(rt,1,2*m,x+1,2*m,c);
        sum+=1ll*c*x;
    }
    res=sum;
    int pos=0;
    REP(i,1,2*m){
        sum+=sgt.query(rt,1,2*m,i);
        if(sum<res){
            res=sum;
            pos=i;
        }
    }
    ans[n]=pos;
    PER(i,n,2){// 还原操作序列
        pos=max(pos,lpos[i]);
        pos=min(pos,rpos[i]);
        ans[i-1]=pos;
    }
    write(res),putchar('\n');
    REP(i,1,n)write(ans[i]-m),putchar(' ');
    putchar('\n');
    return 0;
}
```

---

## 作者：STARSczy (赞：1)

设 $f_{i,j}$ 为收到了 $i$ 个物品，位置在 $j$ 的最小花费。

容易得出 $f_{i,j}=\min f_{i-1,k}+c|j-k|+d|x_i-k|$。这里和 [EricWan](\user\377873) 的式子一样。

但是 [EricWan](\user\377873) 后面对于 $c|j-k|$ 的做法就有点看不懂了，这里解释一下。

$$\begin{aligned}
f_{i,j}
&=\min f_{i-1,k}+c|j-k|+d|x_i-k| \\
&=d|x_i-k|+\min(\min_{k\leq j} f_{i-1,k}+c|j-k|,\min_{k\geq j} f_{i-1,k}+c|j-k|)\\
&=d|x_i-k|+\min(\min_{k\leq j} f_{i-1,k}+c|j-k|,\min_{k\geq j} f_{i-1,k}+c|j-k|)\\
&=d|x_i-k|+\min(cj+\min_{k\leq j} f_{i-1,k}-ck,-cj+\min_{k\geq j} f_{i-1,k}+ck)
\end{aligned}$$

设 $g_{0,i,j}=\min(f_{i,j}-cj,g_{0,i,j-1})+cj,g_{1,i,j}=\min(f_{i,j}+cj,g_{1,i,j+1})-cj$，则有：

$$\begin{aligned}
f_{i,j}
&=d|x_i-k|+\min(cj+\min_{k\leq j} f_{i-1,k}-ck,-cj+\min_{k\geq j} f_{i-1,k}+ck)\\
&=d|x_i-k|+\min(g_{0,i,j},g_{1,i,j})
\end{aligned}$$

发现 $g_{0,i},g_{1,i},f_{i}$ 其实都是下凸壳，且 $g_{0,i}$ 是把 $f_{i}$ 中斜率大于 $c$ 的变成 $c$、$g_{1,i}$ 是把 $f_{i}$ 中斜率小于 $-c$ 的变成 $-c$，取 $\min$ 操作互不影响。

故从 $f_{i-1}$ 到 $f_i$ 的操作为：将斜率小于 $-c$ 的改为 $-c$，斜率大于 $c$ 的改为 $c$，加入 $d|x_i-k|$。

然后存方案就是记录每次斜率大于小于 $-c$ 和 $c$ 的边界，如果超过这个范围了，就取 $\max$ 或 $\min$。统计出方案后计算出 $ans$。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/rope>
#define rep(i,l,r) for(int i=(l),i##end=(r);i<=i##end;++i)
#define per(i,r,l) for(int i=(r),i##end=(l);i>=i##end;--i)
#define int long long
#define double long double
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define rbtree(way) tree<way,null_type,less<way>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;
const int maxn=1e6+10,maxm=1e6+10,mod=998244353,inf=1e9;
inline int ksm(int x,int k,int mod=mod){
	int ans=1;
	for(;k;k>>=1,x=x*x%mod) if(k&1) ans=ans*x%mod;
	return ans;
}

int n,k1,k2,sum,ans,a[maxn],l[maxn],r[maxn],way[maxn];
map<int,int> t;
void dfs(int nw,int x){
	if(!x) return;
	dfs(max(min(nw,r[x]),l[x]),x-1),way[x]=nw;
}

signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>k1>>k2,sum=k1,t[-inf]=-k1,t[0]=2*k1,l[0]=-inf,r[0]=inf;
	rep(i,1,n){
		cin>>a[i],l[i]=-inf,r[i]=inf;
		for(int x=r[i]=prev(t.end())->fi;sum>k1;r[i]=x=prev(t.end())->fi)
			if(sum-k1>=t[x]) sum-=t[x],t.erase(x);
			else{
				t[x]-=sum-k1,sum=k1;
				break;
			}
		for(int lst=-inf,x=l[i]=next(t.begin())->fi;t[-inf]<-k1;l[i]=x=next(t.begin())->fi)
			if(t[-inf]+t[x]<=-k1) t[-inf]+=t[x],lst=x,t.erase(x);
			else{
				t[x]+=t[-inf]+k1,t[-inf]=-k1;
				break;
			}
		t[-inf]-=k2,t[a[i]]+=k2<<1,sum+=k2;
	}
	int tmp=0,sumk=0,mn=inf*inf,mnid=-inf;
	for(auto it=t.begin();next(it)!=t.end();++it)
		tmp+=(next(it)->fi-it->fi)*(sumk+=it->se),tmp<mn?mn=tmp,mnid=next(it)->fi:0;
	dfs(mnid,n);
	rep(i,1,n) ans+=k1*abs(way[i-1]-way[i])+k2*abs(a[i]-way[i]);
	cout<<ans<<'\n';
	rep(i,1,n) cout<<way[i]<<' ';
	return 0;
}
```

---

