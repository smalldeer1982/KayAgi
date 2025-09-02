# [GDCPC 2023] Traveling in Cells

## 题目描述

有 $n$ 个格子排成一行，第 $i$ 个格子的颜色为 $c_i$，上面放置着一个权值为 $v_i$ 的球。

您将要在格子中进行若干次旅行。每次旅行时，您会得到旅行的起点 $x$ 与一个颜色集合 $\mathbb{A} = \{a_1, a_2, \cdots, a_k\}$，且保证 $c_x \in \mathbb{A}$。旅行将从第 $x$ 个格子上开始。在旅行期间，如果您在格子 $i$ 处，那么您可以向格子 $(i - 1)$ 或 $(i + 1)$ 处移动，但不能移动到这 $n$ 个格子之外。且在任意时刻，您所处的格子的颜色必须在集合 $\mathbb{A}$ 中。

当您位于格子 $i$ 时，您可以选择将格子上的球取走，并获得 $v_i$ 的权值。由于每个格子上只有一个球，因此一个格子上的球只能被取走一次。

您的任务是依次处理 $q$ 次操作，每次操作形如以下三种操作之一：

- $1\; p \; x$：将 $c_p$ 修改为 $x$。
- $2\; p \; x$：将 $v_p$ 修改为 $x$。
- $3\; x\; k\; a_1\; a_2 \; \ldots\; a_k$：给定旅行的起点 $x$ 与一个颜色集合 $\mathbb{A} = \{a_1, a_2, \cdots, a_k\}$。假设如果进行这样的一次旅行，求出取走的球的权值之和最大是多少。注意，由于我们仅仅假设进行一次旅行，因此并不会真的取走任何球。即，所有询问之间是独立的。

## 样例 #1

### 输入

```
2
5 10
1 2 3 1 2
1 10 100 1000 10000
3 3 1 3
3 3 2 2 3
2 5 20000
2 3 200
3 3 2 1 3
3 3 3 1 2 3
1 3 4
2 1 100000
1 2 2
3 1 2 1 2
4 1
1 2 3 4
1000000 1000000 1000000 1000000
3 4 4 1 2 3 4```

### 输出

```
100
110
1200
21211
100010
4000000```

# 题解

## 作者：lizhous (赞：3)

[link](https://www.luogu.com.cn/problem/P9695)

不用什么脑子。

注意到 $1\le v_i$。

显然贪心的想，每个格子能走就走是最优的，每个能到达的格子的球都被取走是最优的。

问题就被转化成求出 $x$ 左边最大的位置 $L$ 满足 $c_L\notin  \mathbb{A}$，右边最小的位置 $R$ 满足 $c_R\notin \mathbb{A}$，答案就是 $\sum\limits^{R}_{i=L} v_i$。

考虑如何维护。不难发现左右两边是独立的，所以这里只对左边进行考虑。

假如对于每个 $c_w\in \mathbb{A}$，使 $t_w=1$，其余 $t_w=0$，则对于一个点 $L'$，如果 $L'$ 到 $x$ 全部在集合 $\mathbb{A}$ 内，即 $\sum\limits^{x}_{i=L'}t_i=x-L'+1$，则 $L'\ge L$，否则 $L'<L$。

发现这是有单调性的，可以二分。

那么问题就在如何求出 $\sum\limits^{x}_{i=L'}t_i$。

区间求和想到线段树。很健康的，我们想到开 $n$ 棵线段树，第 $i$ 棵的 $j$ 位置为 $1$ 表示 $c_j=i$。不难发现同一位置最多只有一棵线段树有值，所以可以动态开点。求和就是对于 $\mathbb{A}$ 中每个数，求对应线段树的和。修改是容易的。

$\sum\limits^{R}_{i=L} v_i$ 使用树状数组维护。

时间复杂度 $O(q\log n+\sum k\log n)$。

---

## 作者：RDFZchenyy (赞：2)

| 时间限制 | 空间限制 | 链接 |
| :----------: | :----------: | :----------: |
| 5.00s | 1.00GB | [link](https://www.luogu.com.cn/problem/P9695) |


**【题意简述】**

有一个长为 $n$ 的一排格子，每个格有一个颜色值 $c_i$ 和一个权值 $v_i$。

有 $q$ 次操作，每次为以下三种操作之一：

+ 操作 1：修改一个格的颜色值为 $c'$；
+ 操作 2：修改一个格的权值 $v'$；
+ 操作 3：给定一个位置 $x$ 和一个大小为 $k$ 的集合 $A$，求从 $x$ 出发，只经由颜色值属于 $A$ 的格子能抵达的所有格子的权值和。

数据范围：$1\le n,q\le 10^5,1\le c_i,c'\le n,1\le v_i,v'\le 10^9$ 且 $1\le \sum k\le 10^6$。

**【做法分析】**

本题的数据范围不大，为 $10^5$。

我们考虑把操作 3 拆成两部分，第一部分是求出一个格子可达的最左、最右格，第二部分是对在其之间的格子求和。

那么此时，我们可以容易的使用一个树状数组维护操作 3 的第二部分以及操作 2。

接着考虑操作 1 及操作 3 的第一部分。

较为困难地发现，这是可以使用分块来维护的，我们对方格表分块，对于每一个块用数组记录各种颜色的数量，我们从 $x$ 所在块开始，向左向右依次处理每一个块是否可以全部经过。如果到某一个块不能，那么暴力按格推进即可。取块长 $b=\sqrt{n}$。

做法时间复杂度 $O(\sqrt{n}\sum k)$，空间复杂度 $O(n\sqrt{n})$，可以通过。

**【代码示例】**

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 100005
#define MAXBLK 505

int n,q;
int c[MAXN];
long long v[MAXN];

int bsz,bnm;
int l[MAXBLK],r[MAXBLK];
int bel[MAXN];

int cnt[MAXBLK][MAXN];

long long sum[MAXN];
int lowbit(int x){
    return x&(-x);
}
void add(int pos,long long val){
    while(pos<=n){
        sum[pos]+=val;
        pos+=lowbit(pos);
    }
    return;
}
long long gsum(int pos){
    long long ret=0;
    while(pos){
        ret+=sum[pos];
        pos-=lowbit(pos);
    }
    return ret;
}
long long gsum(int l,int r){
    return gsum(r)-gsum(l-1);
}

int op,p,x,k,rcol;
vector<int> col;
int cc[MAXN];

void run(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        cin>>v[i];
        add(i,v[i]);
    }
    bsz=sqrt(n); bnm=ceil(n*1.0/bsz);
    for(int i=1;i<=bnm;i++){
        l[i]=(i-1)*bsz+1;
        r[i]=min(i*bsz,n);
        for(int j=l[i];j<=r[i];j++){
            bel[j]=i;
            cnt[i][c[j]]++;
        }
    }
    
    for(int i=1;i<=q;i++){
        cin>>op;
        if(op==1){
            cin>>p>>x;
            cnt[bel[p]][c[p]]--;
            cnt[bel[p]][x]++;
            c[p]=x;
        }else if(op==2){
            cin>>p>>x;
            add(p,-v[p]);
            add(p,x);
            v[p]=x;
        }else{
            cin>>x>>k;
            for(int x=1;x<=k;x++){
                cin>>rcol; col.push_back(rcol);
            }

            sort(col.begin(),col.end()); unique(col.begin(),col.end());
            for(auto i:col){
                cc[i]=1;
            }
            
            int lsd,rsd; lsd=rsd=x;
            while(lsd>l[bel[x]]){
                if(!cc[c[lsd-1]]){
                    break;
                }
                lsd--;
            }
            while(rsd<r[bel[x]]){
                if(!cc[c[rsd+1]]){
                    break;
                }
                rsd++;
            }

            if(lsd==l[bel[x]]){
                int lbk=bel[x];
                while(lbk>1){
                    int cs=0;
                    for(auto j:col){
                        cs+=cnt[lbk-1][j];
                    }
                    if(cs!=(r[lbk-1]-l[lbk-1]+1)){
                        break;
                    }
                    lbk--;
                }
                lsd=l[lbk];
                while(lsd>1){
                    if(!cc[c[lsd-1]]){
                        break;
                    }
                    lsd--;
                }
            }
            if(rsd==r[bel[x]]){
                int rbk=bel[x];
                while(rbk<bnm){
                    int cs=0;
                    for(auto j:col){
                        cs+=cnt[rbk+1][j];
                    }
                    if(cs!=(r[rbk+1]-l[rbk+1]+1)){
                        break;
                    }
                    rbk++;
                }
                rsd=r[rbk];
                while(rsd<n){
                    if(!cc[c[rsd+1]]){
                        break;
                    }
                    rsd++;
                }
            }

            cout<<gsum(lsd,rsd)<<endl;

            for(auto j:col){
                cc[j]=0;
            }
            col.clear();
        }
    }

    for(int i=1;i<=n;i++){
        add(i,-v[i]);
        cnt[bel[i]][c[i]]--;
    }

    return;
}

int T;
int main(){
    ios::sync_with_stdio(false);

    cin>>T;
    for(int i=1;i<=T;i++){
        run();
    }

    return 0;
}
```

---

## 作者：寒鸽儿 (赞：2)

### 题意

$T$ 组询问，有一个长为 $n$ 的序列，$<c_i, v_i>$ 表示 $i$ 的颜色和权值。 $q$ 次询问：  

1. $c_i \gets c'$
2. $v_i \gets v'$
3. 给定 $x, S = \{t_1, t_2, \cdots, t_k\}$ ，求包含 $x$ 的极大区间的权值和，满足区间内的点的颜色 $\in S$ 。  

$1 \leq n, q \leq 10^5, \sum n, q \leq 3 \times 10^5, \sum |S| \leq 10^6$ 。

### 题解

考虑把颜色和权值分开维护。  

权值的区间和显然只需要用树状数组即可区间查询。  

对于颜色，有一个 $\mathcal{O}(\sum |S| \log^2 n)$ 的暴力：  

对每种颜色开一个下标线段树，动态开点，对于某个位置 $i$ 的颜色 $c_i$ ，则把代表 $c_i$ 的线段树的下标 $i$ 设为 $1$ 。  

二分 $x$ 所在区间的右端点 $r$，如果从 $S$ 中所有颜色对应线段树查出的 $[x,r]$ 之和相加等于 $r - x + 1$ ，说明极大的右端点 $R \leq r$ 。则二分的单次 check 复杂度为 $\mathcal{O}(|S| \log n)$ 。

考虑优化：其实查询时可以把 $|S|$ 棵线段树叠加在一起，每个结点的和等于 $|S|$ 棵线段树对应节点的和，则访问这个虚构的树的节点的复杂度为 $\mathcal{O}(|S|)$ ，直接在线段树上二分 $\mathcal{O}(\log n)$ 次遍历结点可以得到极大区间的右端点，左端点的求法一样。这样复杂度降到 $\mathcal{O}(\sum |S| \log n)$ 。  

处理时可以差分后直接二分前缀，为了保证前缀和的单调性，可以令每个位置 -1（颜色包含的下标对应位置为 $0$ ，不包含的为 $-1$（只需要让结点的值等于实际值 - 区间长度即可））。

### Code

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)

using namespace std;
using ll = long long;

const int N = 1e5 + 10, Q = 1e5 + 10;
namespace SEG {
    int ls[(N + Q) * 20], rs[(N + Q) * 20], cnt[(N + Q) * 20], n, tot;
    int *root;
    void init(int N, int *ROOT) {
        n = N; root = ROOT;
        rep(i,1,n) root[i] = 0;
        rep(i,1,tot) ls[i] = rs[i] = cnt[i] = 0;
        tot = 0;
    }
    void insert(int &p, int lp, int rp, int x, int v) {
        if(!p) p = ++ tot;
        if(lp == rp) { cnt[p] += v; return ; }
        int mid = (lp + rp) >> 1;
        if(x <= mid) insert(ls[p], lp, mid, x, v);
        else insert(rs[p], mid + 1, rp, x, v);
        cnt[p] = cnt[ls[p]] + cnt[rs[p]];
    }
    int qry(int p, int lp, int rp, int l, int r) {
        if(!p) return 0;
        if(l <= lp && rp <= r) return cnt[p];
        int mid = (lp + rp) >> 1;
        if(r <= mid) return qry(ls[p], lp, mid, l, r);
        if(l > mid) return qry(rs[p], mid + 1, rp, l, r);
        return qry(ls[p], lp, mid, l, r) + qry(rs[p], mid + 1, rp, l, r);
    }
    int qL(vector<int> &ps, int lp, int rp, int val) {
        if(lp == rp) return lp;
        int mid = (lp + rp) >> 1;
        int right = - (rp - mid);
        for(int p : ps) right += cnt[rs[p]];
        if(right <= val) {
            for(int &p : ps) p = rs[p];
            return qL(ps, mid + 1, rp, val);
        }
        for(int &p : ps) p = ls[p];
        return qL(ps, lp, mid, val - right);
    }
    int qR(vector<int> &ps, int lp, int rp, int val) {
        if(lp == rp) return lp;
        int mid = (lp + rp) >> 1;
        int left = - (mid - lp + 1);
        for(int p : ps) left += cnt[ls[p]];
        if(left <= val) {
            for(int &p : ps) p = ls[p];
            return qR(ps, lp, mid, val);
        }
        for(int &p : ps) p = rs[p];
        return qR(ps, mid + 1, rp, val - left);
    }
    int qryLeft(vector<int> roots, int x) {
        for(int &c : roots) c = root[c];
        int sum = 0;
        for(int rt : roots) sum += qry(rt, 0, n + 1, x + 1, n + 1);
        return qL(roots, 0, n + 1, sum - n + x - 2);
    }
    int qryRight(vector<int> roots, int x) {
        for(int &c : roots) c = root[c];
        int sum = 0;
        for(int rt : roots) sum += qry(rt, 0, n + 1, 0, x - 1);
        return qR(roots, 0, n + 1, sum - x - 1);
    }
}

namespace BIT {
    ll c[N];
    int n;
    inline void init(int N) {
        n = N;
        rep(i,1,n) c[i] = 0;
    }
    inline void add(int x, int v) {
        for(; x <= n; x += x & (-x)) c[x] += v;
    }

    inline ll qry(int x) {
        ll ret = 0;
        for(; x; x -= x & (-x)) ret += c[x];
        return ret;
    }
    inline ll qry(int l, int r) {
        return l == 1 ? qry(r) : qry(r) - qry(l - 1);
    }
}

int root[N], col[N], v[N], n;

signed main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    if(fopen("yl.in", "r")) {
        freopen("yl.in", "r", stdin);
        freopen("yl.out", "w", stdout);
    }

    int T;
    cin >> T;

    while(T --) {
        int q;
        cin >> n >> q;
        SEG::init(n, root);
        BIT::init(n);
        rep(i,1,n) cin >> col[i];
        rep(i,1,n) cin >> v[i];
        rep(i,1,n) SEG::insert(SEG::root[col[i]], 0, n + 1, i, 1);
        rep(i,1,n) BIT::add(i, v[i]);
        int opt, p, x, k;
        while(q --) {
            cin >> opt;
            if(opt == 1) {
                cin >> p >> x;
                SEG::insert(root[col[p]], 0, n + 1, p, -1);
                SEG::insert(root[col[p] = x], 0, n + 1, p, 1);
            } else if(opt == 2) {
                cin >> p >> x;
                BIT::add(p, x - v[p]);
                v[p] = x;
            } else {
                cin >> x >> k;
                vector<int> vec(k);
                rep(i,0,k - 1) cin >> vec[i];
                int ansL = SEG::qryLeft(vec, x) + 1;
                int ansR = SEG::qryRight(vec, x) - 1;
                cout << BIT::qry(ansL, ansR) << endl;
            }
        }
    }

    return 0;
}
```

---

## 作者：苏联小渣 (赞：2)

题目相当于：支持单点修改颜色或权值，查询最长的 $l \le x \le r$，使得 $[l,r]$ 的颜色都在集合里面。

我们发现左右端点的选取具有单调性，所以可以考虑二分。以左端点为例，假设二分 $L$，那么需要判断 $[L,x-1]$ 内是否只有集合内的颜色。我们计算集合内颜色在这个区间的出现次数总和，判断是否等于 $x-L$ 就行了。

那么现在考虑怎么计算出现次数总和。如果不带修我们可以给每个颜色开一个 vector，然后二分。如果带修，我们需要支持查询 $[l,r]$ 中有多少个 $x$。我们给每个 $x$ 开一棵线段树，下标是序列的下标，某个位置为 $1$ 表示这个位置的颜色是 $x$。其单点修改容易维护，二分的时候直接在 $k$ 棵线段树上分别求区间和，判断加起来后是否等于区间长度即可。

这么做是 2log 的，可能会被卡。发现二分套线段树可以换成线段树上二分，只不过这里变成了在 $k$ 棵线段树上一起二分（其实可以理解为把 $k$ 棵线段树合并起来，在合并的那棵线段树上二分）。那么要求出最长的左端点，对于 $[1,x-1]$ 在线段树上划分成的若干个区间，从右往左遍历，看哪个区间是第一个使得加上这个区间后，$k$ 棵线段树上的区间和不等于区间长度的。那直接在这个区间上继续二分即可。时间复杂度 $O((n+k) \log n)$。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int tt, n, q, op, k, x, y, cnt, now, len, lef, rig, flag, a[100010], b[100010], t[100010];
vector <int> id, ask;
struct BIT{
	ll d[100010];
	void clear(){
		for (int i=1; i<=n; i++) d[i] = 0;
	}
	void add(int p, int x){
		for (; p<=n; p+=p&-p) d[p] += x;
	}
	ll query(int p){
		ll ret = 0;
		for (; p; p-=p&-p) ret += d[p];
		return ret;
	}
}S;
struct node{
	int l, r, s;
}d[10000010];
void modify(int &p, int l, int r, int x, int y){
	if (!p) p = ++cnt;
	d[p].s += y;
	if (l == r) return ;
	int mid = l + r >> 1;
	if (x <= mid) modify(d[p].l, l, mid, x, y);
	else modify(d[p].r, mid+1, r, x, y);
}
void findl(int l, int r){
	if (l == r) return ;
	int mid = l + r >> 1, tmp = 0;
	for (int i=0; i<id.size(); i++){
		tmp += d[d[id[i]].r].s;
	}
	vector <int> cun = id;
	if (tmp != r - mid){
		id.clear();
		for (int i=0; i<cun.size(); i++){
			id.push_back(d[cun[i]].r);
		}
		findl(mid+1, r);
	}
	else{
		id.clear();
		for (int i=0; i<cun.size(); i++){
			id.push_back(d[cun[i]].l);
		}
		lef = min(lef, mid+1);
		findl(l, mid);
	}
}
void queryl(int l, int r, int x, int y){
	if (x > y) return ;
	if (x <= l && r <= y){
		len += r - l + 1;
		for (int i=0; i<id.size(); i++){
			now += d[id[i]].s;
		}
		if (now != len){
			if (!flag){
				flag = 1;
				findl(l, r);
			}
		}
		else lef = min(lef, l);
		return ;
	}
	int mid = l + r >> 1;
	vector <int> tmp = id;
	if (y > mid){
		id.clear();
		for (int i=0; i<tmp.size(); i++){
			id.push_back(d[tmp[i]].r);
		}
		queryl(mid+1, r, x, y);
	}
	if (x <= mid){
		id.clear();
		for (int i=0; i<tmp.size(); i++){
			id.push_back(d[tmp[i]].l);
		}
		queryl(l, mid, x, y);
	}
}
void findr(int l, int r){
	if (l == r) return ;
	int mid = l + r >> 1, tmp = 0;
	for (int i=0; i<id.size(); i++){
		tmp += d[d[id[i]].l].s;
	}
	vector <int> cun = id;
	if (tmp != mid - l + 1){
		id.clear();
		for (int i=0; i<cun.size(); i++){
			id.push_back(d[cun[i]].l);
		}
		findr(l, mid);
	}
	else{
		rig = max(rig, mid);
		id.clear();
		for (int i=0; i<cun.size(); i++){
			id.push_back(d[cun[i]].r);
		}
		findr(mid+1, r);
	}
}
void queryr(int l, int r, int x, int y){
	if (x <= l && r <= y){
		for (int i=0; i<id.size(); i++){
			now += d[id[i]].s;
		}
		len += r - l + 1;
		if (now != len){
			if (!flag){
				flag = 1;
				findr(l, r);
			}
		}
		else rig = max(rig, r);
		return ;
	}
	int mid = l + r >> 1;
	vector <int> tmp = id;
	if (x <= mid){
		id.clear();
		for (int i=0; i<tmp.size(); i++){
			id.push_back(d[tmp[i]].l);
		}
		queryr(l, mid, x, y);
	}
	if (y > mid){
		id.clear();
		for (int i=0; i<tmp.size(); i++){
			id.push_back(d[tmp[i]].r);
		}
		queryr(mid+1, r, x, y);
	}
}
int main(){
	scanf ("%d", &tt);
	while (tt --){
		for (int i=1; i<=cnt; i++){
			d[i].l = d[i].r = d[i].s = 0;
		}
		cnt = 0;
		scanf ("%d%d", &n, &q);
		S.clear();
		for (int i=1; i<=n; i++){
			scanf ("%d", &a[i]);
			t[i] = 0;
		}
		for (int i=1; i<=n; i++){
			scanf ("%d", &b[i]);
			S.add(i, b[i]);
		}
		for (int i=1; i<=n; i++){
			modify(t[a[i]], 1, n, i, 1);
		}
		for (int i=1; i<=q; i++){
			scanf ("%d%d", &op, &x);
			if (op == 1){
				scanf ("%d", &y);
				modify(t[a[x]], 1, n, x, -1);
				modify(t[y], 1, n, x, 1);
				a[x] = y;
			}
			else if (op == 2){
				scanf ("%d", &y);
				S.add(x, y-b[x]);
				b[x] = y;
			}
			else{
				id.clear();
				ask.clear();
				scanf ("%d", &k);
				for (int j=1; j<=k; j++){
					scanf ("%d", &y);
					id.push_back(t[y]);
					ask.push_back(t[y]);
				}
				now = len = flag = 0, lef = x;
				queryl(1, n, 1, x-1);
				id = ask;
				now = len = flag = 0, rig = x;
				queryr(1, n, x+1, n);
				printf ("%lld\n", S.query(rig) - S.query(lef-1));
			}
		}
	}
	return 0;
}

```

---

## 作者：SICKO (赞：1)

序列分块模板题。

### 1. 分析题目

题目要求我们维护一个 $n$ 个点的序列，序列有值与颜色。操作有两个，一个是单点修改值或颜色；另一个是神秘的区间查询，查询对于一个点，在限定颜色的条件下，最远能向左右扩展到哪里，回答这个范围值的和。

### 2. 思路

实际上这个查询就非常的线段树上二分，写了一下发现其实我不会线段树上二分~恼~。进一步观察发现 $\sum k$ 是有上限的，于是开始思考能不能分块解决这个问题。

对于分块来说，两个修改操作都非常直接，查询答案的思路也都是显然的。对于查询操作，你只需要对序列分块，然后先跳散块跳到边界，然后整块整块跳直到无法继续，然后接着跳散块就行了。我们回顾这个过程，对于跳散块来说，块的长度是 $\sqrt{n}$ 的，每跳一步，所需要的时间是 $O(1)$ 的，我们只需看看这个散块的颜色属于给定颜色即可，所以跳散块的时间复杂度是 $O(\sqrt{n})$ 的。

但是整块呢？我们需要匹配整个整块的所有含有颜色与所给限定颜色，我们发现一个 trick，如果整块含有的颜色种类数量大于限定的，那么一定跳不过去。跳一个整块的时间复杂度就是 $k$ 的，总的来说一次查询操作就是 $O(k\sqrt{n})$ 的。

修改操作显然是 $O(1)$，所以对于整个过程来说，维护一组样例算法的时间复杂度就是 $O(n\sqrt{n}+\sum k\sqrt{n})$。发现 $\sum n \leq 3\times10^5, \sum k \leq 10^6$，时限是 $\text{5s}$，可以通过本题。

### 3. 代码

代码使用了 `set` 来存储颜色，所以时间复杂度变成了 $O((n+\sum k) \sqrt{n} \log{n})$，但还是不会很吃力就跑完了。

```c++
#include <bits/stdc++.h>
//#define int long long
using namespace std;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> c(n + 1), v(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> v[i];
    int blk = (int) sqrt(n) + 1, idx = 1;
    vector<int> bel(n + 1), blt(n + 1), brt(n + 1);
    for (int i = 1, cnt = 0; i <= n; i++) {
        bel[i] = idx;
        cnt += 1;
        if(cnt == 1) blt[idx] = i;
        if (cnt == blk) {
            brt[idx] = i;
            cnt = 0;
            idx = idx + 1;
        }
    }
    brt[idx] = n;
    vector<long long> tot(idx + 1);
    for (int i = 1; i <= n; i++) tot[bel[i]] += v[i];
    vector<vector<int>> tr(idx + 1, vector<int>(n + 1));
    vector<set<int>> hvc(idx + 1);
    for (int i = 1; i <= n; i++) {
        int block = bel[i];
        tr[block][c[i]] += 1;
        if (tr[block][c[i]] == 1) hvc[block].insert(c[i]);
    }
    auto find_rt = [&brt, &bel, &c, &idx, &v, &hvc, &tot, &blt](int pos, const set<int> &mst) -> long long {
        // 将散块推至边界
        long long res = 0;
        int rt = pos, blk = bel[rt];
        for (; rt <= brt[blk]; rt++) {
            if (mst.find(c[rt]) == mst.end()) return res;
            res = res + v[rt];
        }
        // 推整块
        blk += 1;
        for (; blk <= idx; blk++) {
            if (hvc[blk].size() > mst.size()) break;
            bool flag = false;
            for (auto &it: hvc[blk]) {
                if (mst.find(it) == mst.end()) {
                    flag = true;
                    break;
                }
            }
            if (flag) break;
            res = res + tot[blk];
        }
        if (blk > idx) return res;
        // 继续推散块
        rt = blt[blk];
        for (; rt <= brt[blk]; rt++) {
            if (mst.find(c[rt]) == mst.end()) return res;
            res = res + v[rt];
        }
        return res;
    };
    auto find_lt = [&brt, &bel, &c, &idx, &v, &hvc, &tot, &blt](int pos, const set<int> &mst) -> long long{
        int lt = pos, blk = bel[pos];
        long long res = 0;
        for(; lt >= blt[blk]; lt--) {
            if (mst.find(c[lt]) == mst.end()) return res;
            res += v[lt];
        }
        // 推整块
        blk -= 1;
        for(; blk >= 1; blk --) {
            if (hvc[blk].size() > mst.size()) break;
            bool flag = false;
            for (auto &it: hvc[blk]) {
                if (mst.find(it) == mst.end()) {
                    flag = true;
                    break;
                }
            }
            if (flag) break;
            res = res + tot[blk];
        }
        lt = brt[blk];
        for (; lt >= blt[blk]; lt--) {
            if (mst.find(c[lt]) == mst.end()) return res;
            res = res + v[lt];
        }
        return res;
    };
    for (int _ = 1; _ <= q; _++) {
        int opt;
        cin >> opt;
        if (opt == 2) {
            int pos, val;
            cin >> pos >> val;
            tot[bel[pos]] -= v[pos];
            v[pos] = val;
            tot[bel[pos]] += v[pos];
        } else if (opt == 1) {
            int pos, col;
            cin >> pos >> col;
            tr[bel[pos]][c[pos]] -= 1;
            if (tr[bel[pos]][c[pos]] == 0) hvc[bel[pos]].erase(c[pos]);
            c[pos] = col;
            tr[bel[pos]][col] += 1;
            if (tr[bel[pos]][col] == 1) hvc[bel[pos]].insert(col);
        } else {
            int pos, num;
            cin >> pos >> num;
            set<int> mst;
            for (int i=1; i<=num; i++) {
                int x; cin>>x;
                mst.insert(x);
            }
            // 向左
            long long res = find_lt(pos, mst) + find_rt(pos, mst) - v[pos];
            cout<<res<<"\n";
        }
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}
```

---

## 作者：Llx2022 (赞：1)

[P9695 [GDCPC2023] Traveling in Cells](https://www.luogu.com.cn/problem/P9695)

启发：同一个区间多个不同的等价类不好维护，可以对不同的等价类维护同一个区间。

因为是要走连续的且颜色在集合中出现的位置，考虑对每个颜色维护 $0/1$ 线段树，线段树上二分走的位置（单调性易证），对位置 $pos$ 左右分别找到第一个不合法位置，同时维护区间和即可。

开 $cnt_{color}$ 颗动态开点线段树维护颜色块，树状数组维护权值和。

$O((q+n)\log n+\sum k\log n )$

# Code

```cpp
#include<iostream>
#include<vector>
using namespace std;
#define int long long 
template<typename T>inline void read(T &x){
	x=0;T f=1;char ch=getchar();
	while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=getchar();}
	while(ch>=48&&ch<=57){x=x*10+ch-48;ch=getchar();}
	x*=f;
}
template<typename T>inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
const int N=1e5+8;
const int Q=3e5+8;
const int M=17*(N+Q);
int T,n,q;
int sum[M],ls[M],rs[M],cnt;
int v[N],c[N],rt[N];
void ins(int &u,int l,int r,int pos,int val){
    if(!u) u=++cnt,ls[u]=rs[u]=sum[u]=0;
    sum[u]+=val;
    if(l==r) return ;
    int mid=l+r>>1;
    if(pos<=mid) ins(ls[u],l,mid,pos,val);
    else ins(rs[u],mid+1,r,pos,val);
}
int calc(vector<int> &sub){
    int ans=0;
    for(auto v:sub){
        ans+=sum[v];
    }
    return ans;
}
vector<int> gotols(vector<int> sub){
    for(auto &v:sub){
        v=ls[v];
    }
    return sub;
}
vector<int> gotors(vector<int> sub){
    for(auto &v:sub){
        v=rs[v];
    }
    return sub;
}
//找pos位置较左
int findl(vector<int> u,int l,int r,int pos){
    if(calc(u)==r-l+1)return 0;
    if(l==r) return l;
    int mid=l+r>>1;
    if(pos<=mid){
        return findl(gotols(u),l,mid,pos);
    }
    else{
        int res=findl(gotors(u),mid+1,r,pos);
        return res==0?findl(gotols(u),l,mid,pos):res;
    }
}
//找pos位置较右
int findr(vector<int> u,int l,int r,int pos){
    //不递归合法
    if(calc(u)==r-l+1)return n+1;
    //递归就是不合法
    if(l==r) return l;//找到一个不合法
    int mid=l+r>>1;
    if(pos<=mid){
        int res=findr(gotols(u),l,mid,pos);
        return res==n+1?findr(gotors(u),mid+1,r,pos):res;
    }
    else{
        return findr(gotors(u),mid+1,r,pos);
    }
}
#define lowbit(x) (x&(-x))
int ct[N];
void add(int pos,int val){
    for(int i=pos;i<=n;i+=lowbit(i)){
        ct[i]+=val;
    }
}
int query(int pos){
    int res=0;
    for(int i=pos;i;i-=lowbit(i)){
        res+=ct[i];
    }
    return res;
}
void solve(){
    for(int i=1;i<=n;i++) ct[i]=0,rt[i]=0;
    cnt=0;
    read(n),read(q);
    for(int i=1;i<=n;i++){
        read(c[i]);
        ins(rt[c[i]],1,n,i,1);
    }
    for(int i=1;i<=n;i++){
        read(v[i]);
        add(i,v[i]);
    }
    while(q--){
        int op,pos,val;
        read(op),read(pos),read(val);
        if(op==1){
            ins(rt[c[pos]],1,n,pos,-1);
            c[pos]=val;
            ins(rt[c[pos]],1,n,pos,1);
        }
        else if(op==2){
            add(pos,val-v[pos]);
            v[pos]=val;
        }
        else{
            vector<int> co(val);
            for(auto &x:co){
                read(x);
                x=rt[x];
            }
            //找到第一个不满足在集合中的点的位置
            int l=findl(co,1,n,pos);
            int r=findr(co,1,n,pos);
            write(query(r-1)-query(l)),putchar('\n');
        }
    }
}
signed main(){
    read(T);
    while(T--){
        solve();
    }
    return 0;
}
```

---

## 作者：youdu666 (赞：1)

思路：平衡树，倍增，树状数组

由于 $ 1 \leq v_i $，故可以选一定选，所以询问可以转化为从 $x$ 往左往右走，如果走到非选中的颜色则停下，询问这一段的价值之和。

价值之和可以用树状数组等求出来，往左右走稍微麻烦一点。可以对于每一种颜色开一个平衡树，然后就可以在平衡树上查询每种颜色在一段区间里有多少个了，于是可以对于左右端点进行倍增处理了。当然也不用真的写平衡树，直接上一棵封装的红黑树就完事了。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long 
using namespace std;
using namespace __gnu_pbds;
const int N=1e5+5,d=17;
int n,q,x,l,r,y,k,opt;
struct BIT{
	int t[N];
	int lowbit(int x){return x&(-x);}
	void add(int x,int v){for(;x<=n;x+=lowbit(x))t[x]+=v;}
	int ask(int x){int res=0;for(;x;x-=lowbit(x))res+=t[x];return res;}
	int query(int l,int r){return ask(r)-ask(l-1);}
}bt;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> s[N];
int col[N],val[N];
vector<int> v;
inline int qw(int k,int l,int r){//询问第k个set中值在[l,r]的数量
	if(s[k].size()==0)return 0;
	int x=s[k].order_of_key(l);
	int y=s[k].order_of_key(r+1);
	return y-x;
}
inline bool chk(int l,int r){//查询l-r是不是都是v中的颜色
	int cnt=0;
	for(auto i:v)cnt+=qw(i,l,r);
	return cnt==(r-l+1);
}
int T;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>q;
		for(int i=1;i<=n;i++)s[i].clear(),bt.t[i]=0;
		for(int i=1;i<=n;i++)cin>>col[i],s[col[i]].insert(i);
		for(int i=1;i<=n;i++)cin>>val[i],bt.add(i,val[i]);
		while(q--){
			cin>>opt;
			if(opt==1){
				cin>>x>>y;
				s[col[x]].erase(x);
				s[y].insert(x);
				col[x]=y;
			}
			else if(opt==2){
				cin>>x>>y;
				bt.add(x,-val[x]);
				bt.add(x,y);
				val[x]=y;
			}
			else {
				cin>>x>>k;v.clear();l=r=x;
				for(int i=1;i<=k;i++)cin>>y,v.emplace_back(y);
				for(int i=d;i>=0;i--){
					if((l-(1<<i))<1)continue;
					if(chk(l-(1<<i),r))l-=(1<<i);
				}
				for(int i=d;i>=0;i--){
					if((r+(1<<i))>n)continue;
					if(chk(l,r+(1<<i)))r+=(1<<i);
				}
				cout<<bt.query(l,r)<<"\n";
			}
		}
	}
}
```


---

## 作者：RYANGSJ (赞：1)

我们发现询问显然是具有单调性的，考虑对于每次询问，进行两次二分，第一次二分出能到达的最左边的位置，第二次二分出能到达的最右边的位置。

考虑如何进行check，对于一个区间 $[l,r]$ ,设每个颜色在这个区间中出现的次数为 $b_i$，设询问给出的颜色是 $a_i$，如果 $(\sum_{i=1}^k b_{a_i}) = r-l+1$，那么显然这个区间是合法的。

再考虑如何计算 $b_i$，可以对于每一个颜色建一棵动态开点线段树。

```cpp
#include<bits/stdc++.h>
#define int long long
#define LL long long
using namespace std;

inline int read(){
    int s=0,k=1;
    char c=getchar();
    while(c>'9'||c<'0'){
        if(c=='-') k=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        s=(s<<3)+(s<<1)+(c^48);
        c=getchar();
    }
    return s*k;
}
int T,n,q,c[200005],val[200005];
int sum[200005],a[200005],k,tot,rt[200005];
struct node{
    int sum,lc,rc;
}tree[12000005];
int build(){
    tot++;
    return tot;
}
void pushup(int x){
    tree[x].sum=tree[tree[x].lc].sum+tree[tree[x].rc].sum;
    return;
}
void change(int x,int l,int r,int w,int v){
    if(l==r){
        tree[x].sum+=v;
        return;
    }
    int mid=(l+r)/2;
    if(w<=mid){
        if(!tree[x].lc)tree[x].lc=build();
        change(tree[x].lc,l,mid,w,v);
    }
    else{
        if(!tree[x].rc)tree[x].rc=build();
        change(tree[x].rc,mid+1,r,w,v);
    }
    pushup(x);
    return;
}
int query(int x,int l,int r,int ll,int rr){
    if(r<ll||l>rr)return 0;
    if(l>=ll&&r<=rr){
        return tree[x].sum;
    }
    int mid=(l+r)/2;
    int res=0;
    res+=query(tree[x].lc,l,mid,ll,rr);
    res+=query(tree[x].rc,mid+1,r,ll,rr);
    return res;
}
int lowbit(int x){
    return (x&(-x));
}
void add(int x,int v){
    while(x<=n){
        sum[x]+=v;
        x+=lowbit(x);
    }
    return;
}
int query(int x){
    int res=0;
    while(x>0){
        res+=sum[x];
        x-=lowbit(x);
    }
    return res;
}

bool check(int l,int r){
    int len=r-l+1;
    int sm=0;
    for(int i=1;i<=k;i++){
        sm+=query(rt[a[i]],1,n,l,r);
    }
    return sm==len;
}
void solve(){
    n=read(),q=read();
    tot=0;
    for(int i=1;i<=n;i++){
        rt[i]=build();
    }
    for(int i=1;i<=n;i++){
        c[i]=read();
        change(rt[c[i]],1,n,i,1);
    }
    for(int i=1;i<=n;i++){
        val[i]=read();
        add(i,val[i]);
    }
    for(int oo=1;oo<=q;oo++){
        int opt=read();
        if(opt==1){
            int p=read(),x=read();
            change(rt[c[p]],1,n,p,-1);
            c[p]=x;
            change(rt[c[p]],1,n,p,1);
        }else if(opt==2){
            int p=read(),x=read();
            add(p,-val[p]);
            val[p]=x;
            add(p,val[p]);
        }else{
            int x=read();
            k=read();
            for(int i=1;i<=k;i++){
                a[i]=read();
            }
            bool fl=false;
            for(int i=1;i<=k;i++){
                if(c[x]==a[i])fl=true;
            }
            if(!fl){
                cout<<"0\n";
                continue;
            }
            int l=1,r=x,ans=0,res=1;
            while(l<=r){
                int mid=(l+r)/2;
                if(check(x-mid+1,x)){
                    l=mid+1,res=mid;
                }else{
                    r=mid-1;
                }
            }
            ans+=query(x)-query(x-res);
            l=1,r=n-x+1,res=1;
            while(l<=r){
                int mid=(l+r)/2;
                if(check(x,x+mid-1)){
                    l=mid+1,res=mid;
                }else{
                    r=mid-1;
                }
            }
            ans+=query(x+res-1)-query(x);
            cout<<ans<<endl;
        }
    }

    for(int i=1;i<=n;i++) sum[i]=0;
    for(int i=1;i<=tot;i++) tree[i]={0,0,0};
    return;
}
signed main(){
    T=read();
    for(int i=1;i<=T;i++){
        solve();
    }
    return 0;
}
```


---

## 作者：cannotdp (赞：1)

### 题目分析

$2$ 操作是平凡的单点修改区间求和，直接上小常数 BIT。显然的，对于 $3$ 操作可以二分出左右端点，那么该如何 check 呢？既然带修，肯定要用数据结构来维护。vp 的时候只能想到开 $1 \times 10^6$ 个 $3 \times 10^5$ 的 BIT，这肯定不行。观察到每一个格子只会被染上一种颜色，因此可以直接使用动态开点线段树，维护每个颜色在各个区间有多少个，然后判断给定的颜色集合中的颜色在 $[Lmid,pos - 1]$ 或者在 $[pos + 1,Rmid]$ 中出现的数目之和是否等于区间长度即可。这样实现是双 log 的，也有单 log 的线段树上二分做法。我最慢的点跑了 3.48s，可以通过本题。

### 代码实现


```cpp

#include <bits/stdc++.h>
#define ll long long
#define PII pair<int, int>
#define lowbit(x) (x & (-x))
using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7, INF = 0x3f3f3f3f;
int n, m, k, T, tot, q;
int c[N], v[N], rt[N], s[N];
ll bc[N];

struct ST {
    int l, r;
    ll val;
}t[10000010];

void pre() {
    for(int i = 1; i <= n; i++) {
        rt[i] = 0;
        bc[i] = 0;
    }
    for(int i = 1; i <= tot; i++) t[i].l = t[i].r = t[i].val = 0;
    tot = 0;
}

void update(int p) {
    t[p].val = t[t[p].l].val + t[t[p].r].val;
}

void add(int x, int val) {
    for(; x <= n; x += lowbit(x)) bc[x] += val;
}

ll ask(int x) {
    ll res = 0;
    for(; x; x -= lowbit(x)) res += bc[x];
    return res;
}

void change(int &p, int l, int r, int x, int val) {
    if(!p) p = ++tot;
    if(l == r) {
        t[p].val += val;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) change(t[p].l, l, mid, x, val);
    else change(t[p].r, mid + 1, r, x, val);
    update(p);
}

int query(int p, int l, int r, int L, int R) {
    if(!p) return 0;
    if(L <= l && R >= r) return t[p].val;
    int mid = (l + r) >> 1;     
    int res = 0;
    if(L <= mid) res += query(t[p].l, l, mid, L, R);
    if(R > mid) res += query(t[p].r, mid + 1, r, L, R);
    return res; 
}

bool check(int l, int m, int r) {
    int cnt = 0;
    for(int i = 1; i <= m; i++) 
        cnt += query(rt[s[i]], 1, n, l, r);
    return cnt == (r - l + 1);
}

void solve() {
    scanf("%d%d", &n, &q);
    pre();
    for(int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
        change(rt[c[i]], 1, n, i, 1);
    }
    for(int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        add(i, v[i]);
    }
    while(q--) {
        int opt, p, x;
        scanf("%d%d%d", &opt, &p, &x);
        if(opt == 1) {
            change(rt[c[p]], 1, n, p, -1);
            change(rt[x], 1, n, p, 1);
            c[p] = x;
        }
        else if(opt == 2) {
            add(p, x - v[p]);
            v[p] = x;
        }
        else {
            for(int i = 1; i <= x; i++) scanf("%d", &s[i]);
            int l = 1, r = p - 1, posl = p, posr = p;
            while(l <= r) {
                int mid = (l + r) >> 1;
                if(check(mid, x, p - 1)) r = mid - 1, posl = mid;
                else l = mid + 1;
            }
            l = p + 1, r = n;
            while(l <= r) {
                int mid = (l + r) >> 1;
                if(check(p + 1, x, mid)) l = mid + 1, posr = mid;
                else r = mid - 1;
            }
            printf("%lld\n", ask(posr) - ask(posl - 1));
        }
    }
}

int main() {
    scanf("%d", &T);
    while(T--) solve();
    return 0;
}
```


---

## 作者：lfxxx (赞：1)

重现赛时一遍过加首杀。

考虑一种非常简洁的思路，首先可以达到的各自肯定是一段区间，这段区间内的数肯定也要全部选上，区间内数的和可以用树状数组处理，现在的问题在于怎么处理出这个区间的左右端点。

把这个问题拆成起点往两边的区间后，问题具有了单调性，可以二分转判断是否合法。

注意到我们要判断一个区间内的数的颜色是否全部在一个集合中，由于集合大小较小，所以考虑一次询问每个数在区间中的出现次数并判断加起来是否等于区间长度，可以使用平衡树维护，代码为了方便直接用的 pbds 库。

时间复杂度是 $O((\sum k) \log^2 n)$ 由于常数小加上时限较大所以可以过。

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
using namespace __gnu_pbds;
const int maxn = 1e5+114;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> S[maxn];
int query(int l,int r,int x){
    return S[x].order_of_key(r+1)-S[x].order_of_key(l); 
}
int a[maxn];
int c[maxn];
int n,q;
vector<int> col;
bool check(int l,int r){//妫€楠岃寖鍥?[l,r] 涓殑鏁扮殑棰滆壊鏄惁鍦ㄩ泦鍚?col 涓?
    int cnt=0;
    for(int x:col){
        cnt+=query(l,r,x);
    }
    return cnt==(r-l+1);
}
int tr[maxn];
void add(int x,int v){
    while(x<=n) tr[x]+=v,x+=lowbit(x);
}
int pre(int x){
    int ans=0;
    while(x>0) ans+=tr[x],x-=lowbit(x);
    return ans;
}
int ask(int l,int r){return pre(r)-pre(l-1);}
void work(){
    cin>>n>>q;
    for(int i=0;i<=n;i++){
        tr[i]=a[i]=c[i]=0;
        S[i].clear();
    }
    for(int i=1;i<=n;i++){
        cin>>c[i];
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        S[c[i]].insert(i);
    }
    for(int i=1;i<=n;i++){
        add(i,a[i]);
    }
    while(q--){
        int opt;
        cin>>opt;
        if(opt==1){
            int p,x;
            cin>>p>>x;
            S[c[p]].erase(p);
            c[p]=x;
            S[c[p]].insert(p);
        }
        else if(opt==2){
            int p,x;
            cin>>p>>x;
            add(p,-a[p]);
            a[p]=x;
            add(p,a[p]);
        }
        else{
            int x,k;
            cin>>x>>k;
            col.clear();
            for(int i=1;i<=k;i++){
                int x;
                cin>>x;
                col.push_back(x);
            }
            int l=0,r=x;
            while(l+1<r){
                int mid=(l+r)>>1;
                if(check(mid,x)==true) r=mid;
                else l=mid;
            }
            int Lt=r;
            l=x,r=n+1;
            while(l+1<r){
                int mid=(l+r)>>1;
                if(check(x,mid)==true) l=mid;
                else r=mid;
            }
            int Rt=l;
            cout<<ask(Lt,Rt)<<'\n';
        }
    }
}
int t;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--) work();
}
```


---

## 作者：Error_Eric (赞：0)

### 题意

数字序列，每个数字有颜色，维护以下操作：

- 单点修改数字
- 单点修改颜色
- 求颜色在给定颜色集合内的，包含第 $p$ 个元素的极大子串内的数字和。

### Sol

考试的时候没想到二分，这里提供一种分块做法。

~~考试的时候复杂度分析错了没敢写，但是事实证明以我的代码能力即使知道这是对的也写不出来。~~

考虑维护每个块的内部每个颜色出现的次数。这是 $O(n+q\sqrt n)$ 的。

然后从考虑找最靠左的颜色不在集合内的。在散块内就暴力跳。遇到整块的时候就计算整块内集合内颜色出现的次数。不难发现每次询问，散块内是 $O(\sqrt n)$，整块是 $O(|A|\sqrt n) $ 的。

块内部分不会超时，而整块因为 $\sum|A|\le10^6$ 也就是 $\sum |A| \sqrt n_i\le\sqrt{\max\{n_i\}}\sum |A|\le\sqrt{10^5}\times10^6\le4\times10^8$  也不会超时。所以复杂度是对的。

细节就是常规的分块细节。当然分块分都分了，不如用分块维护区间和。

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<vector>
#include<math.h>
using namespace std;
const int _=1e5+50,K0=317;
int t,n,q,c[_],v[_],k[_],kuai,ks;
int o,p,x,qk,a[_],ql,qr;
bool inc[_];
int kl[K0],kr[K0],kc[K0][_];
long long kv[K0];

bool jdg(int kid){
    int cnt=0;
    for(int i=0;i<qk;i++)
        cnt+=kc[kid][a[i]];
    return cnt==kr[kid]-kl[kid]+1;
}
long long sum(int pos){
    if(pos==-1) return 0;
    int i0=0; long long res=0;
    while(k[i0]<k[pos])
        res+=kv[k[i0]],i0+=kuai;
    while(i0<=pos)
        res+=v[i0],i0++;
    return res;
}
void que(){
    cin>>qk;
    for(int i=0;i<qk;i++)
        cin>>a[i],inc[a[i]]=1;
    ql=qr=p;

    while(ql>0&&k[ql]==k[p])
        if(inc[c[ql-1]])--ql;
        else break;
    if(jdg(k[ql])){
        while(0<k[ql]&&k[ql]<k[p])
            if(jdg(k[ql]-1))ql-=kuai;
            else break;
    }
    while(ql>0)
        if(inc[c[ql-1]])--ql;
        else break;
    
    while(qr<n-1&&k[qr]==k[p])
        if(inc[c[qr+1]])++qr;
        else break;
    if(jdg(k[qr])){
        while(k[p]<k[qr]&&k[qr]+1<ks)
            if(jdg(k[qr]+1))qr+=kuai;
            else break;
    }
    while(qr<n-1)
        if(inc[c[qr+1]])++qr;
        else break;
        
    cout<<sum(qr)-sum(ql-1)<<endl;
    for(int i=0;i<qk;i++)
        inc[a[i]]=0;
}
void mian(){
    cin>>n>>q,kuai=sqrt(n)+1,ks=n/kuai;
    for(int i=0;i<n;i++){
        kr[k[i]=i/kuai]=i;
        if(i==0||k[i]!=k[i-1]) kl[k[i]]=i,kv[k[i]]=0;
        for(int j=0;j<=ks;j++)
            kc[j][i+1]=0;
    }
    for(int i=0;i<n;i++)
        cin>>c[i],kc[k[i]][c[i]]++;
    for(int i=0;i<n;i++)
        cin>>v[i],kv[k[i]]+=v[i];
    while(q--){
        cin>>o>>p,--p;
        switch(o){
            case 1: 
                cin>>x,kc[k[p]][c[p]]--,kc[k[p]][c[p]=x]++;break;
            case 2:
                cin>>x,kv[k[p]]-=v[p],kv[k[p]]+=(v[p]=x);break;
            case 3:
                que();break;
        }
    }
}
int main(){
    ios::sync_with_stdio(0),cin>>t;
    while(t--) mian();
}
```

---

## 作者：rui_er (赞：0)

显然，询问的答案即为 $x$ 所在的极长的满足颜色均在 $\mathbb{A}$ 内的连续段的权值和。如果我们能维护对颜色的单点修改，以及求出某个位置所在极长连续段的左右端点 $l,r$，只需要树状数组即可求出答案。

一个朴素的想法是对每种颜色开一棵线段树，单点修改是平凡的，极长连续段左端点只需要线段树上二分找到最靠右的 $l$，使得 $\mathbb{A}$ 中每种颜色在 $[l,x]$ 的出现次数之和恰好等于 $x-l+1$，极长连续段右端点同理。

咱赛时没算这玩意的空间开销有多大，就直接莽了个主席树上去。主席树的话空间复杂度显然为 $O((n+q)\log n)$，实现中开了 $64$ 倍数组。

赛时懒得写线段树上二分的 $O((n+q)\log n)$ 做法，写了二分套线段树的 $O(n\log n+q\log^2n)$ 跑过去了。

```cpp
// Problem: T368285 [GDCPC2023] F-Traveling in Cells
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T368285?contestId=135929
// Memory Limit: 1 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x, y, z) for(ll x = (y); x <= (z); ++x)
#define per(x, y, z) for(ll x = (y); x >= (z); --x)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do {freopen(s".in", "r", stdin); freopen(s".out", "w", stdout);} while(false)
#define endl '\n'
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
ll randint(ll L, ll R) {
    uniform_int_distribution<ll> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const ll N = 1e5 + 5;

ll T, n, q, c[N], v[N];

struct BIT {
    ll c[N];
    void init(ll x) {rep(i, 1, x) c[i] = 0;}
    ll lowbit(ll x) {return x & (-x);}
    void add(ll x, ll k) {for(; x <= n; x += lowbit(x)) c[x] += k;}
    ll ask(ll x) {ll k = 0; for(; x; x -= lowbit(x)) k += c[x]; return k;}
    ll Ask(ll l, ll r) {return ask(r) - ask(l - 1);}
}bit;

struct PersSegTree {
    ll cnt[N << 6], lc[N << 6], rc[N << 6], rt[N], sz;
    void clear() {
        rep(i, 1, sz) cnt[i] = lc[i] = rc[i] = 0;
        rep(i, 1, n) rt[i] = 0;
        sz = 0;
    }
    ll copy(ll u) {
        ++sz;
        cnt[sz] = cnt[u];
        lc[sz] = lc[u];
        rc[sz] = rc[u];
        return sz;
    }
    void pushup(ll u) {
        cnt[u] = cnt[lc[u]] + cnt[rc[u]];
    }
    ll insert(ll u, ll l, ll r, ll pos, ll k) {
        ll v = copy(u);
        if(l == r) {
            cnt[v] += k;
            return v;
        }
        ll mid = (l + r) >> 1;
        if(pos <= mid) lc[v] = insert(lc[u], l, mid, pos, k);
        else rc[v] = insert(rc[u], mid + 1, r, pos, k);
        pushup(v);
        return v;
    }
    ll query(ll u, ll l, ll r, ll ql, ll qr) {
        if(!u) return 0;
        if(ql <= l && r <= qr) return cnt[u];
        ll mid = (l + r) >> 1, ans = 0;
        if(ql <= mid) ans += query(lc[u], l, mid, ql, qr);
        if(qr > mid) ans += query(rc[u], mid + 1, r, ql, qr);
        return ans;
    }
}psgt;

ll findL(const vector<ll>& vec, ll x) {
    ll L = 1, R = x + 1;
    auto check = [&](ll M) -> bool {
        ll len = x - M + 1, cnt = 0;
        for(ll c : vec) cnt += psgt.query(psgt.rt[c], 1, n, M, x);
        return cnt == len;
    };
    while(L < R) {
        ll M = (L + R) >> 1;
        if(check(M)) R = M;
        else L = M + 1;
    }
    return L;
}

ll findR(const vector<ll>& vec, ll x) {
    ll L = x, R = n + 1;
    auto check = [&](ll M) -> bool {
        ll len = M - x + 1, cnt = 0;
        for(ll c : vec) cnt += psgt.query(psgt.rt[c], 1, n, x, M);
        return cnt == len;
    };
    while(L < R) {
        ll M = (L + R) >> 1;
        if(check(M)) L = M + 1;
        else R = M;
    }
    return L - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(cin >> T; T; --T) {
        cin >> n >> q;
        rep(i, 1, n) cin >> c[i];
        rep(i, 1, n) cin >> v[i];
        bit.init(n);
        psgt.clear();
        rep(i, 1, n) bit.add(i, v[i]);
        rep(i, 1, n) psgt.rt[c[i]] = psgt.insert(psgt.rt[c[i]], 1, n, i, +1);
        while(q--) {
            ll op;
            cin >> op;
            if(op == 1) {
                ll x, y;
                cin >> x >> y;
                psgt.rt[c[x]] = psgt.insert(psgt.rt[c[x]], 1, n, x, -1);
                c[x] = y;
                psgt.rt[c[x]] = psgt.insert(psgt.rt[c[x]], 1, n, x, +1);
            }
            else if(op == 2) {
                ll x, y;
                cin >> x >> y;
                bit.add(x, -v[x]);
                v[x] = y;
                bit.add(x, +v[x]);
            }
            else {
                ll x, k;
                cin >> x >> k;
                vector<ll> vec(k);
                for(ll& i : vec) cin >> i;
                ll L = findL(vec, x), R = findR(vec, x);
                cout << bit.Ask(L, R) << endl;
            }
        }
    }
    return 0;
}
```

---

