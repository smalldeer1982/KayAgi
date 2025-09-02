# フードコート (Foodcourt)

## 题目描述

translate from P7560，copied by @[Network_Error](https://www.luogu.com.cn/user/534654) 


有 $N$ 家书虫食品店，有 $M$ 个家庭来享受用书虫制作的美味食物。

因为食品店十分火爆，所以顾客需要排队，刚开始所有队列都是空的。

今天食品店又全部开张了，发生了 $Q$ 个事件：

- **加入事件**：编号位于区间 $[L,R]$ 内的所有食品店中，都有编号为 $C$ 的家庭加入队尾，每个满足要求的食品店队尾都加入了 $K$ 个人。
- **离开事件**：编号位于区间 $[L,R]$ 内的所有食品店中，如果队列有超过 $K$ 个人，那么队列的前 $K$ 个人离开队列，否则队列里的所有人离开队列。
- **白嫖事件**：如果编号为 $A$ 的食品店的队列中有大于等于 $B$ 个人，那么食品店就会赠送从队列开头开始数第 $B$ 个人一份秘制书虫，否则店员会吃掉书虫。

求每次 **白嫖事件** 是否有顾客被赠送了秘制书虫，如果有的话，求顾客所在的家庭。

## 说明/提示

#### 样例 1 解释

我们用 $Q_i(a_1,a_2,\cdots,a_k)$ 代表第 $i$ 个食品店的队列，$a_1$ 为队首，$a_k$ 为队尾，其中 $a_i=p$ 就代表第 $i$ 个位置的人来自第 $p$ 个家庭。特殊地，$Q_i()$ 就代表当前队列为空。

根据样例 1 的这几个事件：

- 第 $1$ 个 **加入事件**：

$$Q_1(),Q_2(5,5),Q_3(5,5)$$

- 第 $2$ 个 **加入事件**：

$$Q_1(2,2,2,2),Q_2(5,5,2,2,2,2),Q_3(5,5)$$

- 第 $3$ 个 **白嫖事件**，第 $2$ 个食品店的第 $3$ 个人（第 $2$ 个家庭）被送上秘制书虫。
- 第 $4$ 个 **离开事件**：

$$Q_1(2),Q_2(2,2,2),Q_3()$$

- 第 $5$ 个 **白嫖事件**，第 $1$ 个食品店不够 $2$ 个人，店员会吃掉书虫。
- 第 $6$ 个 **加入事件**：

$$Q_1(2),Q_2(2,2,2,4,4),Q_3(4,4)$$

- 第 $7$ 个 **白嫖事件**，第 $3$ 个食品店的第 $2$ 个人（第 $4$ 个家庭）被送上秘制书虫。

#### 数据规模与约定

对于 $100\%$ 的数据：

- $1 \le N,M,Q \le 25 \times 10^4$。
- $T \in \{1,2,3\}$。
- 对于所有 **加入事件**，$1 \le L \le R \le N$，$1 \le C \le M$，$1 \le K \le 10^9$。
- 对于所有 **离开事件**，$1 \le L \le R \le N$，$1 \le K \le 10^9$。
- 对于所有 **白嫖事件**，$1 \le A \le N$，$1 \le B \le 10^{15}$。
- 至少有一个 **白嫖事件**。

有以下若干个性质：

- 性质 A：对于所有 **加入事件** 和 **离开事件**，有 $K=1$。
- 性质 B：对于所有 **加入事件**，有 $R-L \le  10$ 和 $K=1$。
- 性质 C：只有 **加入事件** 和 **白嫖事件**。


翻译自 [第２０回日本情報オリンピック　春季トレーニング合宿](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/index.html) [Day1 C フードコート (Food Court) 的英文版本](https://www.ioi-jp.org/camp/2021/2021-sp-tasks/day1/foodcourt-en.pdf)。

# 题解

## 作者：KazamaRuri (赞：5)

被这题搞了好久。。

## 题意

维护一个序列，序列中每个元素是一个队列。

入队操作，往队列 $[l,r]$ 里放进 $k$ 个 $c$。

出队操作，让 $[l,r]$ 的队列从队首出 $k$ 个数，不足 $k$ 则只清空。

询问操作，问当前时刻队列 $a$ 里第 $b$ 个数是多少，没有则为 0。

## 分析

发现修改非常难办，考虑把时间轴竖过来，按序列维扫描线，转化成单点修改。

思考：删除元素的时候会“顶格”，即对 $0$ 取 $\max$。如果不会顶格，那我们可以把所有加操作提前，把减操作后置，然后二分到最靠前的加操作使得 $\sum add \ge \sum del + b$，其中 $b$ 为询问中的。发现如果我们找到当前询问的时间戳 $t$ 之前的最后一次队列为 $0$ 的时刻，那么只考虑这个时刻后面的加减操作，就可以套用上述算法。

现在问题在于，如何求出“时间戳 $t$ 之前的最后一次队列为 $0$ 的时刻”。序列被清空的充要条件是经过一段操作后，变化量 $\le 0$。这就说明时间戳上每一个前缀最小值的位置都对应了一次清空。

维护前缀最小值位置不好做，差分一下转变成整体最小值位置，这是可以维护区间最小值 + 线段树二分解决的。同时，单点修改变成一段后缀的修改，这是 ez 的。

顺带一提，如果前缀最小值 $>0$，即没有被清空过，要把上一次清空的时刻视作所有操作开始前（$0$ 时刻）。

至此，问题解决完了。实现上，按时间轴维护两颗线段树，一颗处理所有操作，即加减操作的贡献，维护最小值以查找最后一次序列被清空的位置；另一颗只维护加操作，维护最大值以处理无顶格情况下对形如 $\ge x$ 的最后一个位置的询问。为什么不维护减法的呢？因为 $\sum add - \sum del = \sum total$。

时间复杂度 $O(n \log n)$。

## 代码

我把维护的两个东西并到一个线段树里了。

值得注意的是，$b \le 10^{14}$，我因为这个调了半天。

```cpp
#include <bits/stdc++.h>
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
using namespace std;
using ll=long long;
using pii=pair<int,int>;
const int N=2.5e5+5;
int n,m,m0,m1,c[N],ans[N],tg[N];
ll h[N],f[N<<2],g[N<<2],tgf[N<<2],tgg[N<<2];
vector<pii>p[N],q[N];
void addf(int x,ll k){ f[x]+=k,tgf[x]+=k; }
void addg(int x,ll k){ g[x]+=k,tgg[x]+=k; }
void pushup(int x){ f[x]=max(f[lc(x)],f[rc(x)]),g[x]=min(g[lc(x)],g[rc(x)]); }
void pushdw(int x){
	if(tgf[x]) addf(lc(x),tgf[x]),addf(rc(x),tgf[x]),tgf[x]=0;
	if(tgg[x]) addg(lc(x),tgg[x]),addg(rc(x),tgg[x]),tgg[x]=0;
}
void updf(int x,int l,int r,int u,int v,ll k){
	if(l>v||r<u) return ; if(u<=l&&r<=v) return addf(x,k); int mid=l+r>>1;
	pushdw(x),updf(lc(x),l,mid,u,v,k),updf(rc(x),mid+1,r,u,v,k),pushup(x);
}
void updg(int x,int l,int r,int u,int v,ll k){
	if(l>v||r<u) return ; if(u<=l&&r<=v) return addg(x,k); int mid=l+r>>1;
	pushdw(x),updg(lc(x),l,mid,u,v,k),updg(rc(x),mid+1,r,u,v,k),pushup(x);
}
ll askF(int x,int l,int r,int u,int v){
	if(l>v||r<u) return -1e16; if(u<=l&&r<=v) return f[x]; int mid=l+r>>1;
	pushdw(x); return max(askF(lc(x),l,mid,u,v),askF(rc(x),mid+1,r,u,v));
}
ll askG(int x,int l,int r,int u,int v){
	if(l>v||r<u) return 1e16; if(u<=l&&r<=v) return g[x]; int mid=l+r>>1;
	pushdw(x); return min(askG(lc(x),l,mid,u,v),askG(rc(x),mid+1,r,u,v));
}
ll askf(int x,int l,int r,int u,int v,ll k){
	if(f[x]<k||l>v||r<u) return 0;
	if(l==r) return l; int mid=l+r>>1,w; pushdw(x);
	return (w=askf(lc(x),l,mid,u,v,k))?w:askf(rc(x),mid+1,r,u,v,k);
}
ll askg(int x,int l,int r,int u,int v,ll k){
	if(g[x]>k||l>v||r<u) return 0;
	if(l==r) return l; int mid=l+r>>1,w; pushdw(x);
	return (w=askg(rc(x),mid+1,r,u,v,k))?w:askg(lc(x),l,mid,u,v,k);
}
inline ll F(int x){ return x?askF(1,1,m0,x,x):0; }
inline ll G(int x){ return x?askG(1,1,m0,x,x):0; }
int main(){
	scanf("%d%d%d",&n,&m,&m);
	for(int i=1;i<=m;i++){
		int op,l,k; ll r;
		scanf("%d%d%lld",&op,&l,&r);
		if(op==3) ++m1,p[l].push_back({m0,m1}),h[m1]=r;
		else{
			++m0,op==1?scanf("%d%d",c+m0,&k),tg[m0]=1:(scanf("%d",&k),k=-k);
			q[l].push_back({m0,k}),q[r+1].push_back({m0,-k});
		}
	} if(m0)
	for(int i=1;i<=n;i++){
		for(auto x:q[i]){ if(tg[x.first])
			updf(1,1,m0,x.first,m0,x.second);
			updg(1,1,m0,x.first,m0,x.second);
		}
		for(auto x:p[i]){
			if(!x.first) continue;
			ll w=askG(1,1,m0,1,x.first),k=w>0?0:askg(1,1,m0,1,x.first,w);
			ans[x.second]=c[askf(1,1,m0,k+1,x.first,F(x.first)-G(x.first)+G(k)+h[x.second])];
		}
	}
	for(int i=1;i<=m1;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：acb437 (赞：3)

# 题解：[AT_JOISC2021_C 饮食区](https://www.luogu.com.cn/problem/AT_joisc2021_c)
## 题目大意
给定 $n$ 个队列，进行 $q$ 次操作，分别为：

1. 向 $l\sim r$ 个队列末尾插入 $k$ 个元素 $c$（下称为 $\operatorname{push}$）。
2. 从 $l\sim r$ 个队列开头删除 $k$ 个元素，如果有队列的元素个数不到 $k$ 个（下称“过删除”），则清空该队列（下称为 $\operatorname{pop}$）。
3. 查询第 $a$ 个队列的第 $b$ 个位置的值，如果该队列中没有 $b$ 个元素，则输出 $0$。

## 思路简述
### 思路
**本题的套路是：从按照时间顺序维护序列转变为按照序列顺序维护时间（即将要求维护的操作按时间顺序排布到每一个队列上）。**

对 $n$ 个队列进行区间 $\operatorname{push}$ 和 $\operatorname{pop}$ 多个数，信息量太大。转变为维护时间（操作序列）后，可以维护每一个队列在某一操作后（即某一时间）的长度和每一个操作对应的颜色。这样，通过查找要查询的位置在哪一次操作插入，就可以知道要查询的颜色了。

如果没有 $\operatorname{pop}$ 操作，直接进行线段树上二分即可找出要查询的位置是在哪一次操作插入的，但有了 $\operatorname{pop}$ 之后，队列长度不再满足单调性，无法进行二分。

考虑有了 $\operatorname{pop}$ 之后怎么做。如果没有出现“过删除”情况的话，由于 $\operatorname{push}$ 和 $\operatorname{pop}$ 其实并不改变队列内元素的顺序，这个操作序列其实等价于先执行全部 $\operatorname{push}$，再执行全部 $\operatorname{pop}$，所以现在（查询时）队列的第 $b$ 项，等价于执行 $\operatorname{pop}$ 操作前的第 $b + \sum_{t_i=2}k_i$（把被 $\operatorname{pop}$ 掉的元素全部加回去，$b$ 也就往后移动了）。

考虑存在上述“过删除”情况下如何处理。队列每一次清空后，清空前的操作都不会对答案产生影响，而“过删除”一定会造成队列的清空，因此可以直接找出最后一次清空的位置，从这个位置开始按照不存在“过删除”的情况处理，即可得出答案。

### 实现细节
使用线段树 + 扫描线维护每一个队列不同时间的长度。由于线段树上二分需要在抛去 $\operatorname{pop}$ 的情况下进行，所以需要维护计算了 $\operatorname{pop}$ 和没计算 $\operatorname{pop}$ 两种情况下的队列长度。因为每一个操作都会影响一个后缀，所以可以直接用区间加，也可以差分后单点加。

计算时，可以算真实的队列长度，即产生“过删除”时将队列长度置零，也可以保留负数，是没有影响的。直接保留负数会短一点。

无论是否保留负数，最后一次清空的位置就是查询的时间点前的队列长度的最后一个前缀最小值的位置。不保留负数的话，最小值就是零，所以最后一此清空的位置当然是最后一个零。保留负数的话，因为上一次清空时的前缀和实际上就是零，所以满足当前前缀和小于等于上一次清空时的前缀和时，才会再产生一次清空。

综上所述，用扫描线扫队列，将修改操作用标记挂在 $l$ 的位置（插入）和 $r+1$ 的位置（撤销），用线段树进行修改。或者说，以队列编号为 $x$ 轴，以修改编号（时间）为 $y$ 轴，用线段树从左往右扫描，对当前扫到的 $x$，维护每一个 $y$ 位置上的队列长度。通过线段树上二分找出要查询的值是在哪一次操作中插入的即可。
## 代码
```cpp
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 2.5e5 + 5;
int n, m, q, ans[N], col[N];bool qry[N];
struct option{ll opt, pos, val;};
vector <option> opt[N];

struct node
{
    int l, r;
    ll pop, sum, pre;int pos;
};
struct SegTree
{
    #define lc(u) u << 1
    #define rc(u) u << 1 | 1
    node tr[N << 2];
    node merge(node a, node b)
    {
        node res;
        res.sum = a.sum + b.sum;
        res.pop = a.pop + b.pop;
        res.l = a.l, res.r = b.r;
        res.pre = min(a.pre, a.sum + b.pre);
        res.pos = res.pre == a.sum + b.pre ? b.pos : a.pos;
        return res;
    }
    void build(int u, int l, int r)
    {
        tr[u].l = l, tr[u].r = r, tr[u].pos = r;
        if(l == r)return;
        int m = (l + r) >> 1;
        build(lc(u), l, m), build(rc(u), m + 1, r);
    }
    void modify(int u, int pos, ll val, bool flag)
    {
        if(tr[u].l == tr[u].r)return (void)(tr[u].sum += val, tr[u].pre += val, tr[u].pop += flag * -val);
        int m = (tr[u].l + tr[u].r) >> 1;
        if(pos <= m)modify(lc(u), pos, val, flag);
        else modify(rc(u), pos, val, flag);
        tr[u] = merge(tr[lc(u)], tr[rc(u)]);
    }
    node queryMn(int u, int pos)
    {
        if(tr[u].l == tr[u].r)return tr[u];
        int m = (tr[u].l + tr[u].r) >> 1;
        if(pos <= m)return queryMn(lc(u), pos);
        else return merge(tr[lc(u)], queryMn(rc(u), pos));
    }
    ll queryPop(int u, int l, int r)
    {
        if(l <= tr[u].l && tr[u].r <= r)return tr[u].pop;
        if(tr[u].r < l || r < tr[u].l)return 0;
        return queryPop(lc(u), l, r) + queryPop(rc(u), l, r);
    }
    ll querySum(int u, int l, int r)
    {
        if(l <= tr[u].l && tr[u].r <= r)return tr[u].sum;
        if(tr[u].r < l || r < tr[u].l)return 0;
        return querySum(lc(u), l, r) + querySum(rc(u), l, r);
    }
    int queryPos(int u, int l, ll val)
    {
        if(tr[u].sum + tr[u].pop < val)return 0;
        if(tr[u].l == tr[u].r)return tr[u].l;
        if(tr[u].l >= l)
        {
            ll sum = tr[lc(u)].sum + tr[lc(u)].pop;
            if(val <= sum)return queryPos(lc(u), l, val);
            else return queryPos(rc(u), l, val - sum);
        }
        else
        {
            int m = (tr[u].l + tr[u].r) >> 1, res = 0;
            if(l <= m)res = queryPos(lc(u), l, val), val -= querySum(lc(u), l, m) + queryPop(lc(u), l, m);
            if(m < l || !res)res = queryPos(rc(u), l, val);
            return res;
        }
    }
    #undef lc
    #undef rc
}tr;

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    tr.build(1, 1, q);
    for(int i = 1;i <= q;i++)
    {
        ll t, l, r, c, k;
        scanf("%lld", &t);
        if(t == 1)
        {
            scanf("%lld%lld%lld%lld", &l, &r, &c, &k);
            col[i] = c, opt[l].emplace_back(t, i, k), opt[r + 1].emplace_back(t, i, -k);
        }
        else if(t == 2)
        {
            scanf("%lld%lld%lld", &l, &r, &k);
            opt[l].emplace_back(t, i, -k), opt[r + 1].emplace_back(t, i, k);
        }
        else scanf("%lld%lld", &l, &r), opt[l].emplace_back(t, i, r), qry[i] = true;
    }
    for(int i = 1;i <= n;i++)
        for(option x : opt[i])
            if(x.opt == 1)tr.modify(1, x.pos, x.val, false);
            else if(x.opt == 2)tr.modify(1, x.pos, x.val, true);
            else
            {
                int l = 0;
                node tmp = tr.queryMn(1, x.pos);
                l = (tmp.pre <= 0) * tmp.pos + 1;
                ans[x.pos] = tr.queryPos(1, l, x.val + tr.queryPop(1, l, x.pos));
                ans[x.pos] = ans[x.pos] > x.pos ? 0 : col[ans[x.pos]];
            }
    for(int i = 1;i <= q;i++)
        if(qry[i])
            printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：NahX_ (赞：3)

发现删除操作会出现过删（即删除的个数大于序列中元素数），这个很难处理。

思考一下应该能想到将每次询问查询的 $b\to cnt_{del}+b$ 其中 $cnt_{del}$ 为在该询问之前这个序列删除的数的个数，这样就不用删除只需插入即可。但是这样对于每个删除操作操作的每个序列都要求出删了多少个数，很困难，时间复杂度不能接受。

对于一个询问 $(A,B)$ 发现如果能找到序列 $A$ 在此询问之前操作序列中最后一次出现过删的操作，对于该位置后的操作序列对 $B$ 的贡献就可以用上文的方法求，而该操作及之前加入的所有元素都已经清空，只需将 $b\to cnt_{add}$ 即可，这里的 $cnt_{add}$ 表示该操作前加入的元素个数和。

扫描线。以序列编号为做扫描线，以操作编号建立线段树，叶子节点 $[i,i]$ 上维护第 $1$ 到第 $i$ 次操作的过程中共加的元素总数（不计删除）记为 $add_i$ 以及经过 $1$ 到 $i$ 操作加的元素总数减去删除的元素总数记为 $sum_i$（不考虑过删），节点 $[l,r]$ 维护 $\max_{i=l}^{r}add_i,\min_{i=l}^{r}sum_i$。

下文区间 $[l,r]$ 某值记为 $f(l,r)$，$f(i,i)$ 简记为 $f(i)$。 

将修改 $(l,r,c,k)$ 拆分成在第 $l$ 个序列将 $[id,q]$ 区间加 $k$，在第 $r+1$ 个序列将 $[id,q]$ 区间加 $-k$，其中 $id$ 为这个操作是操作序列中第几个操作，$q$ 是总操作数（均不计询问）。

假设当前询问操作前进行了 $x$ 次操作，线段树上二分出 $[1,x]$ 中最后一个 $sum$ 等于 $\min_{i=l}^{r} sum$ 的位置，就是上文最后一次出现过删的操作（因为对于 $i<j,sum_j>sum_i$ 则第 $i$ 次操作到第 $j$ 次操作的变化量 $<0$ 即删除数大于加入数，出现过删），记为 $p$。假设询问 $(A,B)$ 前有 $m$ 此操作，在线段树上二分出 $[p,m]$ 中第一个 $add$ 大于等于 $add(m)-sum(m)+sum(p)+B$ 的位置，记为 $p_1$。上述值即为第二段中贡献 $B$ 的值 $add(m)-sum(m)+sum(p)=del(m)+sum(p)=add(p)+del(p+1,m)$，其中 $del$ 是删除的元素个数。则第 $p_1$ 次操作加入元素即为答案。

时间复杂度 $O(n\log n)$。

```
// Problem: フードコート (Foodcourt)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_joisc2021_c
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mp make_pair
const int N=3e5+5;int num[N],ans[N];
struct oper{int opt,id,k,c;};vector<oper>g[N],a[N];
struct node{int l,r,add,sum,la,ls;}tr[N<<2];
void pushup(int u){tr[u].add=max(tr[u<<1].add,tr[u<<1|1].add),tr[u].sum=min(tr[u<<1].sum,tr[u<<1|1].sum);}
void pd(int u){
	if(tr[u].ls)tr[u<<1].ls+=tr[u].ls,tr[u<<1|1].ls+=tr[u].ls,tr[u<<1].sum+=tr[u].ls,tr[u<<1|1].sum+=tr[u].ls,tr[u].ls=0;
	if(tr[u].la)tr[u<<1].la+=tr[u].la,tr[u<<1|1].la+=tr[u].la,tr[u<<1].add+=tr[u].la,tr[u<<1|1].add+=tr[u].la,tr[u].la=0;
}
void build(int u,int l,int r){tr[u]={l,r};if(l==r)return;int mid=l+r>>1;build(u<<1,l,mid),build(u<<1|1,mid+1,r);}
void add(int u,int l,int r,int d){if(tr[u].l>=l&&tr[u].r<=r)return tr[u].add+=d,tr[u].la+=d,void();
	pd(u);int mid=tr[u].l+tr[u].r>>1;if(l<=mid)add(u<<1,l,r,d);if(r>mid)add(u<<1|1,l,r,d);pushup(u);
}
void adds(int u,int l,int r,int d){if(tr[u].l>=l&&tr[u].r<=r)return tr[u].sum+=d,tr[u].ls+=d,void();
	pd(u);int mid=tr[u].l+tr[u].r>>1;if(l<=mid)adds(u<<1,l,r,d);if(r>mid)adds(u<<1|1,l,r,d);pushup(u);
}
int gtad(int u,int x){if(tr[u].l==tr[u].r)return tr[u].add;
	pd(u);int mid=tr[u].l+tr[u].r>>1;return (x<=mid?gtad(u<<1,x):gtad(u<<1|1,x));
}
int gtsum(int u,int l,int r){if(!l&&!r)return 0;if(tr[u].l>=l&&tr[u].r<=r)return tr[u].sum;
	pd(u);int mid=tr[u].l+tr[u].r>>1,mn=1e16;if(l<=mid)mn=min(mn,gtsum(u<<1,l,r));if(r>mid)mn=min(mn,gtsum(u<<1|1,l,r));return mn;
}
int askad(int u,int l,int r,int d){
	if(tr[u].add<d||tr[u].l>r||tr[u].r<l)return 0;if(tr[u].l==tr[u].r)return tr[u].l;
	pd(u);int w=askad(u<<1,l,r,d);return (w?w:askad(u<<1|1,l,r,d));
}
int asksum(int u,int l,int r,int d){
	if(tr[u].sum>d||tr[u].l>r||tr[u].r<l)return 0;if(tr[u].l==tr[u].r)return tr[u].l;
	pd(u);int w=asksum(u<<1|1,l,r,d);return (w?w:asksum(u<<1,l,r,d));
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,m,q,c0=0,c1=0;cin>>n>>m>>q;
	for(int i=1,opt,l,r,c,k;i<=q;i++){cin>>opt>>l>>r;
		if(opt==1)cin>>num[++c0]>>k,g[l].push_back(oper{1,c0,k}),g[r+1].push_back(oper{1,c0,-k});
		else if(opt==2)++c0,cin>>k,g[l].push_back(oper{2,c0,-k}),g[r+1].push_back(oper{2,c0,k});
		else a[l].push_back(oper{3,++c1,c0,r});
	}build(1,1,c0);
	for(int i=1;i<=n;i++){
		for(oper j:g[i]){
			if(j.opt==1)add(1,j.id,c0,j.k);
			adds(1,j.id,c0,j.k);
		}
		for(oper j:a[i]){int mn=gtsum(1,1,j.k);
			int beg=(mn<0?asksum(1,1,j.k,mn):0);
			ans[j.id]=num[askad(1,beg+1,j.k,gtad(1,j.k)-gtsum(1,j.k,j.k)+gtsum(1,beg,beg)+j.c)];
		}
	}
	for(int i=1;i<=c1;i++)cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：panyanppyy (赞：3)

~~模拟赛前偷过还不会做的屑~~。

轻轻轻工业还非常好理解，感谢 @houzhiyuan 巨佬。

## Problem

$n$ 家店，$m$ 个团队，$q$ 次操作，有三种操作：

`1 l r c k` 表示 $[l,r]$ 店来了 $k$ 个来自 $c$ 团队的人排队。

`2 l r k` 表示 $[l,r]$ 有 $k$ 个人从前面排完离开。

`3 a b` 表示询问第 $a$ 家店当前队伍第 $b$ 个人属于的团队。

$n,q\le 2.5\times10^5\ ,k\le 10^9\ ,b\le 10^{15}$
### Algorithm 1
$\mathcal O(n^2)\ $ 

直接开 $n$ 个 `deque<pair<int,int>>` 对每次询问直接做就可以了。

期望得分 14pts。
### Algorithm 2

$m=1$ 相当于询问当前队伍有没有人，BIT 维护即可。

期望得分 21pts。

### Algorithm 3
没有删除操作，可以考虑整体二分：

现在我们把问题转化为对每个询问求其对应的答案在哪次操作 $1$。

已知集合 $S$ 的答案全部位于区间 $[l,r]$，考虑求出 $mid =\dfrac{l+r}{2}$ 时每个队列的长度，然后
将能确定答案 $\le mid$ 的询问和 $\gt mid$ 的分成两半，然后继续递归。

期望得分 13pts。

这时候问题显现出来了，删除操作对 $0$ 取 $\max$ 很难处理。

**Trick:** 转换一下，假设删除操作的数没有删除，而是在询问的时候加上删除的人。

$\mathcal O(n\log^2n)$

现在就可以用整体二分求答案了。

线段树维护一下 `max(x+a,b)` 就能求出实际询问的点了。

$\mathcal O(n\log n)$

把整体二分换成线段树分治就能做到。

期望得分 100pts。
### Algorithm 4
**轻工业：** 把时间轴和店反一下，从第 $1$ 家店到第 $n$ 家店做一遍扫描线。

可以发现，实际上每次删除操作是对一段后缀产生贡献，这样直接用一颗线段树维护最小值，然后每次询问最小值就是上面 Trick 里删除的人数了。

然后直接在另一颗记录线段树上二分出第一个大于等于 删除人数+当点人数 的人群编号即可。

两颗线段树都只要维护 $\max$ 或 $\min$，直接用一个结构体就行了。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
using namespace std;
template<typename T_>void operator+=(vector<T_>&x,const T_&y){x.push_back(y);}
const int N=2.5e5+7;
const ll inf=1e18;
int n,m,q,id[N],ans[N];
ll B;
struct SegmentTree{
	ll t[N<<2],mi[N<<2],mx[N<<2],lzy[N<<2];
	void push_up(int rt){
		mx[rt]=max(mx[rt<<1],mx[rt<<1|1]);
		mi[rt]=min(mi[rt<<1],mi[rt<<1|1]); 
	}
	void f(int rt,ll k){mi[rt]+=k,t[rt]+=k,mx[rt]+=k,lzy[rt]+=k;}
	void push_down(int rt){
		if(!lzy[rt])return;
		f(rt<<1,lzy[rt]),f(rt<<1|1,lzy[rt]);
		lzy[rt]=0; 
	}
	ll query(int x,int l,int r,int rt){
		if(l==r)return t[rt];
		push_down(rt);int mid=(l+r)>>1;
		if(x<=mid)return query(x,l,mid,rt<<1);
		if(x>mid) return query(x,mid+1,r,rt<<1|1);
		return-1;
	}
	ll qmi(int L,int R,int l,int r,int rt){
		if(L<=l&&r<=R)return mi[rt];
		push_down(rt);int mid=(l+r)>>1;ll res=inf;
		if(L<=mid)res=min(res,qmi(L,R,l,mid,rt<<1));
		if(R>mid) res=min(res,qmi(L,R,mid+1,r,rt<<1|1));
		return res;
	}
	int find(int L,int R,ll x,int l,int r,int rt){
		if(mx[rt]<x)return 0;
		if(l==r)return id[l];
		push_down(rt);int mid=(l+r)>>1;
		if(L<=l&&r<=R){
			if(mx[rt<<1|1]>=x)return find(L,R,x,mid+1,r,rt<<1|1);
			return find(L,R,x,l,mid,rt<<1);
		}else if(R>mid){
			int k=find(L,R,x,mid+1,r,rt<<1|1);
			if(k)return k;
		}
		return find(L,R,x,l,mid,rt<<1);
	}
	void update(int L,int R,int k,int l,int r,int rt){
		if(L<=l&&r<=R)return f(rt,k);
		push_down(rt);int mid=(l+r)>>1;
		if(L<=mid)update(L,R,k,l,mid,rt<<1);
		if(R>mid) update(L,R,k,mid+1,r,rt<<1|1);
		push_up(rt);
	}
}T1,T2;
vector<pair<int,int>>ad[N],del[N];
vector<pair<int,ll>>Q[N];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1,op,l,r,c,k;i<=q;i++){
		cin>>op;
		switch(op){
			case 1:
				cin>>l>>r>>c>>k,id[i]=c;
				ad[l]+={i,k},ad[r+1]+={i,-k};
				break;
			case 2:
				cin>>l>>r>>k;
				del[l]+={i,-k},del[r+1]+={i,k};
				break;
			case 3:
				cin>>l>>B,Q[l]+={i,B};
				break;
		}
	}
	memset(ans,-1,sizeof(ans));
	for(int i=1;i<=n;i++){
		for(auto j:ad[i])
			T1.update(j.fi,q,j.se,1,q,1),T2.update(1,j.fi,j.se,1,q,1);
		for(auto j:del[i])T1.update(j.fi,q,j.se,1,q,1);
		for(auto j:Q[i]){
			ll x=T1.query(j.fi,1,q,1)-min(T1.qmi(1,j.fi,1,q,1),0ll),y=j.se;
			if(y>x)ans[j.fi]=0;
			else{
				x=x-y+1;
				ans[j.fi]=T2.find(1,j.fi,x+T2.query(j.fi,1,q,1),1,q,1);
			}
		}
	}
	for(int i=1;i<=q;i++)
		if(~ans[i])cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：Pink_Dove (赞：1)

[更美味的食用体验](https://yumomeow.github.io/2025/02/25/solution-JOISC2021_c/)
## 题意
有 $n$ 个队列，要求支持以下三种操作：
- 在区间 $[l,r]$ 中每个队列的队尾插入 $k$ 个 $c$。
- 取出区间 $[l,r]$ 中每个队列的前 $k$ 个数，不足则清空队列。
- 输出指定队列从队头开始的第 $b$ 项，如果大小不足 $b$ 则输出 $0$。

## 题解
修改的操作不方便维护，考虑**换维扫描线**。

以队列为横轴，时间为纵轴，从左往右扫描，用线段树维护队列每个时刻的人数。这样修改操作就可以转化为差分，即在 $l$ 处增加 $k$ 个人，在 $r+1$ 处减去 $k$ 个人。

但是这样有一个问题，删除操作时队列的人数需要对 $0$ 取 $max$，这个不好直接维护。我们先忽略它，看如果队列人数始终 $\ge 0$ 时怎么做。将加操作与减操作分别求和，则每个位置上的值可以转化为 $\sum add-\sum del$。每次询问 $b$ 时，二分查找第一个 $\sum add\ge b+\sum del$ 的数的位置，返回它对应的数即可。

如果我们可以得知在询问前最后一个队列长为 $0$ 的时刻，就可以使用上述做法来计算。仅当 $\sum add-\sum del\le 0$ 时队列才会被清空，且显然这个值必然随着每次清空越来越小。于是我们只需要维护出序列中的前缀和最小值，它的位置即是上次被清零的位置，由于求了前缀和，单点加需要改为后缀加。

总结一下，设每次查询时的时间为 $t$，我们要先找到队列上次被清空的时间，即区间 $[1,t)$ 的前缀和最小值出现的时间。设它为 $p$。

这样，我们就可以在区间 $(p,t)$ 上套用前文的算法，在线段树上二分查找出 $\sum add\ge b+\sum del$ 的最小位置。其中的 $\sum del$ 可以转化为 $\sum sum-\sum add$。

线段树上需要维护的信息：考虑所有操作时人数的前缀最小值 $mi$、它出现的位置 $posmi$、只考虑加操作的和 $add$，考虑所有操作的和 $sum$。时间复杂度 $O(q \log q)$。

不懂可以看代码注释。

## 代码
```cpp
//参考了 P2441M 大佬的实现方式，拜谢Orz
#include<iostream>
#include<algorithm>
#define int long long
#define ls (u<<1)
#define rs (u<<1|1)
#define mid ((l+r)>>1)
using namespace std;
const int N=5e5+10;
int n,m,q,c[N],cntop,cntqu,ans[N];
struct Op{
    int tim,pos,k;//什么时间，哪个队列，加减多少
    bool op;//加还是减
    bool operator < (const Op &t) const{
        return pos<t.pos;
    }
}op[N];
struct Query{
    int id,tim,pos,b;//第几个询问，什么时间，哪个队列，B
    bool operator < (const Query &t) const{
        return pos<t.pos;
    }    
}qu[N];
struct Node{
    int sum,add;//操作1-操作2，操作1
    int mi,posmi,tag;//前缀最小值，前缀最小值位置，后缀加标记
}tr[N<<2];
void pushup(Node &u,Node lc,Node rc){
    u.mi=min(lc.mi,rc.mi);
    u.posmi=lc.mi<=rc.mi?lc.posmi:rc.posmi;
    u.sum=lc.sum+rc.sum;
    u.add=lc.add+rc.add;
    return;
}
void build(int u,int l,int r){
    if(l==r){
        tr[u].posmi=l;
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
}
void updadd(int u,int k){
    tr[u].mi+=k;
    tr[u].tag+=k;
    return;
}
void pushdown(int u){
    updadd(ls,tr[u].tag);
    updadd(rs,tr[u].tag);
    tr[u].tag=0;
    return;
}
void add(int u,int l,int r,int L,int R,int k){
    //后缀加
    if(L<=l&&r<=R){
        updadd(u,k);
        return;
    }
    pushdown(u);
    if(L<=mid) add(ls,l,mid,L,R,k);
    if(R>mid) add(rs,mid+1,r,L,R,k);
    pushup(tr[u],tr[ls],tr[rs]);
}
void add(int u,int l,int r,int U,int k,bool op){
    //单点加
    if(l==r){
        tr[u].sum+=k;
        if(op) tr[u].add+=k;//仅当现在是加操作，计算加操作的和
        return;
    }
    pushdown(u);
    if(U<=mid) add(ls,l,mid,U,k,op);
    else add(rs,mid+1,r,U,k,op);
    pushup(tr[u],tr[ls],tr[rs]);
}
Node query(int u,int l,int r,int L,int R){
    if(L<=l&&r<=R) return tr[u];
    pushdown(u);
    if(L<=mid&&R>mid){
        Node res;
        pushup(res,query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
        return res;
    }
    else if(L<=mid) return query(ls,l,mid,L,R);
    else return query(rs,mid+1,r,L,R);
}
int find(int u,int l,int r,int U,int &v){
    if(r<U) return 0;//跑出边界
    pushdown(u);
    if(l>=U){
        if(tr[u].add<v){
            v-=tr[u].add;
            return 0;
        }
        if(l==r) return l;
    }
    int res=find(ls,l,mid,U,v);//左边找不到找右边
    if(!res) res=find(rs,mid+1,r,U,v);
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=q;i++){
        int opt;
        cin>>opt;
        if(opt==1){
            int l,r,k;
            cin>>l>>r>>c[i]>>k;
            op[++cntop]=(Op){i,l,k,1};
            op[++cntop]=(Op){i,r+1,-k,1};
        }
        if(opt==2){
            int l,r,k;
            cin>>l>>r>>k;
            op[++cntop]=(Op){i,l,-k,0};
            op[++cntop]=(Op){i,r+1,k,0};
        }
        if(opt==3){
            int a,b;
            cin>>a>>b;cntqu++;
            qu[cntqu]=(Query){cntqu,i,a,b};
        }
        ans[i]=m+1;
    }
    sort(op+1,op+cntop+1);
    sort(qu+1,qu+cntqu+1);
    build(1,1,q);
    //i 当前处理的队列 j 当前处理的操作 k 当前处理的询问
    for(int i=1,j=1,k=1;i<=n;i++){
        while(j<=cntop&&op[j].pos==i){
            //先操作完当前队列
            add(1,1,q,op[j].tim,q,op[j].k);//后缀加
            add(1,1,q,op[j].tim,op[j].k,op[j].op);//单点加/减
            j++;
        }
        while(k<=cntqu&&qu[k].pos==i){
            //处理当前队列的询问
            if(qu[k].tim==1){ans[qu[k++].id]=0;continue;}//特判询问1
            Node t=query(1,1,q,1,qu[k].tim-1);//查询前缀最小值
            int p=t.mi>=0?0:t.posmi;//大于0代表没清空过，否则是最小值位置
            t=query(1,1,q,p+1,qu[k].tim);
            int val=qu[k].b+(t.add-t.sum);
            int pos=find(1,1,q,p+1,val);//二分找时刻p右边>=b+del的第一个时刻
            //因为我们已经在b上减去了删掉的人，因而只需要在add上面找
            //又因为add单调不减，所以可以二分。
            ans[qu[k].id]=(!pos||pos>qu[k].tim)?0:c[pos];
            k++;
        }
    }
    for(int i=1;i<=cntqu;i++) cout<<ans[i]<<'\n';
    return 0;
}
```

---

## 作者：P2441M (赞：1)

## 题意简述
有 $n$ 个队列。给出值域 $m$，进行 $q$ 次操作，操作有以下三种：

1. 向编号在 $[l,r]$ 中的队列的尾部加入 $k$ 个 $c$；
2. 把编号在 $[l,r]$ 中的队列的前 $k$ 个数删去，若队列大小不足 $k$ 则清空队列；
3. 查询编号为 $a$ 的队列中从队头开始的第 $b$ 个数，若队列大小不足 $b$ 则返回 $0$。

对于所有数据，$1\leq c\leq m$，$1\leq n,m,q\leq 2.5\times 10^5$。

## 题解
~~被代码实现击杀了 /fn~~

发现这个操作看上去很难维护的样子，但是是经典的单点查询和可差分修改，考虑**换维扫描线**，即我们对序列维做扫描线而不是对时间维做。在这题中，我们对队列的编号做扫描线，用 DS 维护时间轴上的信息。然后对操作 $1,2$ 差分一下，让它在 $L$ 处产生 $k$ 的贡献，在 $R+1$ 处删除贡献。

先考虑没有操作 $2$ 怎么做，显然直接在时间轴上把最小的前缀和 $\ge b$ 的位置二分出来，对应的插入的数就是答案。那有操作 $2$ 之后，这个方法为什么不能沿用呢？因为删除操作破坏了前缀和的**单调性**使得我们不能二分求出答案。

我们再尝试弱化一下，发现这个清空使得我们要对 $0$ 取 $\max$，有点烦，考虑前缀和始终 $\ge 0$ 怎么做。容易观察到，此时我们把删除操作全部延后不影响正确性，那么我们记录当前询问操作之前操作 $2$ 的贡献和 $\sum{del}$，然后在只考虑操作 $1$ 的操作序列上把前缀和 $\ge b+\sum{del}$ 的最小位置二分出来就是答案。

最后回到前缀和可能触底 $<0$ 的情况，这时考虑当前询问前的最后一次触底的时刻，在这个时刻之后，我们套用上面的做法就是正确的！

> **key observation**：最后一次触底的时刻就是前缀和最小的时刻。
> 
> **证明**：注意到在时刻 $i$ 触底之后再一次在时刻 $j$ 触底等价于 $sum_j-sum_i<0$，显然得证。

想想我们现在需要支持什么操作。首先需要支持查询 $[1,b)$ 的前缀和最小值，而修改操作已经被换维扫描线转化成了单点加操作，因此维护前缀和序列，查询时查询 $[1,b)$ 的前缀最小值，单点加转化为后缀加即可。找到前缀最小值的位置 $p$ 后，我们需要在只考虑操作 $1$ 的操作序列的 $(p,t]$ 子区间上，二分出前缀和 $\ge b+\sum{del}$ 的最小位置，其中 $t$ 为当前询问的时间。我们用线段树维护贡献和 $\sum{sum}$ 和只考虑操作 $1$ 的贡献和 $\sum{add}$，此时 $\sum{del}=\sum{add}-\sum{sum}$，询问时做线段树二分即可。

所以开两颗线段树就能维护出所有需要的信息。时间复杂度 $O(q\log{q})$。

## 代码
实现时注意一些特判。我把两颗线段树合并在一起了。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int Q = 5e5 + 5;

int n, m, q, num[Q];
ll ans[Q];
int cnt_qr, cnt_ops;
struct Query {
	ll num, id, a, b;
	bool operator<(const Query &x) const { return a < x.a; }
} qr[Q];
struct Op {
	ll id, tp, a, k;
	bool operator<(const Op &x) const { return a < x.a; }
} ops[Q];

struct SegTree {
#define ls(p) (p << 1)
#define rs(p) (p << 1 | 1)
	struct Node { ll sum, add_sum, mn, amn, tg; } nodes[Q << 2];
	void push_up(Node &p, Node &lp, Node &rp) {
		p.sum = lp.sum + rp.sum; p.add_sum = lp.add_sum + rp.add_sum;
		p.mn = min(lp.mn, rp.mn);
		p.amn = rp.mn <= lp.mn ? rp.amn : lp.amn;
	}
	void push_up(int p) { push_up(nodes[p], nodes[ls(p)], nodes[rs(p)]); }
	void make_add(int p, int l, int r, ll v) { nodes[p].tg += v; nodes[p].mn += v; }
	void push_down(int p, int l, int r) {
		if (!nodes[p].tg) return;
		int mid = (l + r) >> 1;
		make_add(ls(p), l, mid, nodes[p].tg); make_add(rs(p), mid + 1, r, nodes[p].tg);
		nodes[p].tg = 0;
	}
	void build(int p, int l, int r) {
		if (l == r) { nodes[p].amn = l; return; }
		int mid = (l + r) >> 1;
		build(ls(p), l, mid); build(rs(p), mid + 1, r);
		push_up(p);
	}
	Node query(int p, int l, int r, int x, int y) {
		if (x <= l && y >= r) return nodes[p];
		push_down(p, l, r);
		int mid = (l + r) >> 1;
		if (x <= mid && y > mid) {
			Node lres = query(ls(p), l, mid, x, y);
			Node rres = query(rs(p), mid + 1, r, x, y), res;
			return push_up(res, lres, rres), res;
		}
		return x <= mid ? query(ls(p), l, mid, x, y) : query(rs(p), mid + 1, r, x, y);
	}
	int find(int p, int l, int r, int x, ll &v) {
		if (r < x) return 0;
		push_down(p, l, r);
		if (x <= l) {
			if (nodes[p].add_sum < v) { v -= nodes[p].add_sum; return 0; }
			if (l == r) return l;
		}
		int mid = (l + r) >> 1;
		int res = find(ls(p), l, mid, x, v);
		return res ? res : find(rs(p), mid + 1, r, x, v);
	}
	void add(int p, int l, int r, int x, int y, ll v) {
		if (x <= l && y >= r) { make_add(p, l, r, v); return; }
		push_down(p, l, r);
		int mid = (l + r) >> 1;
		if (x <= mid) add(ls(p), l, mid, x, y, v);
		if (y > mid) add(rs(p), mid + 1, r, x, y, v);
		push_up(p);
	}
	void add2(int p, int l, int r, int x, ll v, int tp) {
		if (l == r) {
			nodes[p].sum += v;
			if (tp) nodes[p].add_sum += v;
			return;
		}
		push_down(p, l, r);
		int mid = (l + r) >> 1;
		if (x <= mid) add2(ls(p), l, mid, x, v, tp);
		else add2(rs(p), mid + 1, r, x, v, tp);
		push_up(p);
	}
#undef ls
#undef rs
} sgt;
using Node = SegTree::Node;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1, tp; i <= q; ++i) {
    	cin >> tp;
    	if (tp == 1) {
    		ll l, r, k; cin >> l >> r >> num[i] >> k;
    		ops[++cnt_ops] = { i, 1, l, k }; ops[++cnt_ops] = { i, 1, r + 1, -k };
    	} else if (tp == 2) {
    		ll l, r, k; cin >> l >> r >> k;
    		ops[++cnt_ops] = { i, 0, l, -k }; ops[++cnt_ops] = { i, 0, r + 1, k };
    	} else {
    		ll a, b; cin >> a >> b; ++cnt_qr;
    		qr[cnt_qr] = { cnt_qr, i, a, b };
    	}
    	ans[i] = m + 1;
    }
    sort(ops + 1, ops + cnt_ops + 1); sort(qr + 1, qr + cnt_qr + 1);
    sgt.build(1, 1, q);
    for (int i = 1, j = 1, k = 1; i <= n; ++i) {
    	while (j <= cnt_ops && ops[j].a == i)
    		sgt.add(1, 1, q, ops[j].id, q, ops[j].k), 
    		sgt.add2(1, 1, q, ops[j].id, ops[j].k, ops[j].tp), ++j;
    	while (k <= cnt_qr && qr[k].a == i) {
    		if (qr[k].id == 1) { ans[qr[k++].num] = 0; continue; }
    		Node res = sgt.query(1, 1, q, 1, qr[k].id - 1);
    		int p = res.mn >= 0 ? 0 : res.amn;
    		Node res2 = sgt.query(1, 1, q, p + 1, qr[k].id);
    		ll del = res2.add_sum - res2.sum, val = qr[k].b + del;
    		int pos = sgt.find(1, 1, q, p + 1, val);
    		ans[qr[k].num] = (!pos || pos > qr[k].id) ? 0 : num[pos];
    		++k;
    	}
    }
    for (int i = 1; i <= cnt_qr; ++i) cout << ans[i] << '\n';
    return 0;
}
```

---

## 作者：strcmp (赞：1)

**题目大意：**

维护 $n$ 个序列，$m$ 次操作。每次在 $[l,\,r]$ 的序列末尾加 $k$ 个数字 $c$，或者在开头删去 $k$ 个数字（如果 $k$ 大于等于序列长度则删完），或者查询序列 $a$ 的第 $b$ 个位置的数字。

------------

提供一个题解里没有的树状数组上二分写法。

因为是单点查询，考虑扫描线，枚举 $1 \le i \le n$，回答第 $i$ 个序列上的询问。具体的，对于 $[l,\,r]$ 的加入和离开事件，我们差分成 $l$ 开始，到 $r + 1$ 结束的一段影响区间。

不妨先去掉离开事件。

$f_j$ 代表序列 $i$ 上的第 $j$ 次操作插入了 $f_j$ 个数，$g_j$ 代表第 $j$ 次操作插入的数。（如果第 $j$ 次操作不是插入则 $f_j = g_j = 0$）

在实现中我们开一个大小为 $m$ 的树状数组，每次把所有 $l = i$ 的加入给加进树状数组里，并撤回所有 $r = i - 1$ 的加入，下标为这些加入的出现时间，这是可以简单维护的。然后询问最大的 $k$ 使得 $(\sum^{k}_{j=1} f_j \ge b) \wedge k < t$，其中 $t$ 是当前询问的出现时间。此时 $g_k$ 为所求。

显然可以树状数组上二分维护 $f$，$g$ 开个数组就行了。

考虑有离开事件的情况。

我们发现只需要求出询问 $(a,\,b)$ 之前，$a$ 出去了多少个，然后 $b$ 加上这个数就行了。显然因为我们先进先出的操作顺序这不影响答案。

就是询问时间 $t$ 时，$a$ 序列出去了多少个。挂在询问上，枚举时间轴扫一遍即可。

那么每次就是区间加，区间减并对 $0$ 取 $\max$，单点查询。

Segment Tree Beats 可以搞，但是没必要，有一种巧妙的方法可以避免势能线段树。

具体的，线段树上结点 $(x,\,y)$ 代表这个区间要加上 $x$，并对 $y$ 取 $\max$。

那么我们发现，$(x',\,y')$ 下传到子节点 $(x,\,y)$ 这个标记时，会使得 $(x,\,y)$ 变成 $(x + x',\,\max(y + x',\,y'))$。

这样查询的时候可以一直查到叶子结点，然后返回叶子结点的标记即可。

时间复杂度是严格 $\Theta(n \log n)$ 的。

然后就做完了，注意一下有些细节，应该没有什么离谱的压行。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int maxn = 2.5e5 + 10;
const ll inf = 114514191981052013LL;
using pll = pair<ll, ll>;
struct Q { int id; ll c, k; };
vector<Q> q[maxn]; ll d[2][maxn], ex[maxn], ans[maxn]; int n, m; ll C;
inline void add(int x, ll v, int o) { while (x <= 250010) d[o][x] += v, x += x & -x; }
inline ll qry(int x) {
    ll sum = 0;
    while (x) sum += d[1][x], x -= x & -x;
    return sum;
}
inline int kth(ll k, int top) {
    int p = 0; ll s = 0;
    for (int i = 20; i >= 0; i--) {
        int np = p + (1 << i);
        if (np <= top && s + d[0][np] < k) p = np, s += d[0][np];
    }
    return p + 1 > top ? m + 1 : p + 1;
}
struct Node { 
    ll a, b;
    Node() { b = -inf; }
    Node(ll c, ll d) { a = c, b = d; }
} t[maxn << 2];
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define A(x) (t[x].a)
#define B(x) (t[x].b)
inline void pushdw(int x) {
    if (A(x) || B(x) > -inf) {
        t[ls(x)] = { A(ls(x)) + A(x), max(B(ls(x)) + A(x), B(x)) };
        t[rs(x)] = { A(rs(x)) + A(x), max(B(rs(x)) + A(x), B(x)) };
        A(x) = 0; B(x) = -inf;
    }
}
void sgtadd(int l, int r, int ml, int mr, ll LA, ll LB, int x) {
    if (ml <= l && r <= mr) { A(x) += LA; B(x) = max(B(x) + LA, LB); return; }
    int mid = l + r >> 1; pushdw(x);
    if (ml <= mid) sgtadd(l, mid, ml, mr, LA, LB, ls(x));
    if (mr > mid) sgtadd(mid + 1, r, ml, mr, LA, LB, rs(x));
}
ll sgtqry(int l, int r, int v, int x) {
    if (l == r) { return max(A(x), B(x)); }
    int mid = l + r >> 1; pushdw(x);
    if (v <= mid) return sgtqry(l, mid, v, ls(x));
    else return sgtqry(mid + 1, r, v, rs(x));
}
int o[maxn], l[maxn], r[maxn]; ll c[maxn], k[maxn];
void input() {
    scanf("%d%lld%d", &n, &C, &m); c[m + 1] = inf;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &o[i]);
        switch (o[i]) {
        case 1:
            scanf("%d%d%lld%lld", &l[i], &r[i], &c[i], &k[i]);
            q[l[i]].push_back({ i, c[i], k[i] });
            q[r[i] + 1].push_back({ i, 0, -k[i] });
            break;
            // k >= 1
        case 2:
            scanf("%d%d%lld", &l[i], &r[i], &k[i]);
            break;
        default:
            scanf("%d%lld", &l[i], &c[i]);
            q[l[i]].push_back({ i, c[i], 0 });
            break;
        }
    }
    for (int i = 1; i <= m; i++) {
        if (o[i] == 1 || o[i] == 2) {
            if (o[i] == 1) add(l[i], k[i], 1), add(r[i] + 1, -k[i], 1);
            sgtadd(1, n, l[i], r[i], o[i] == 1 ? k[i] : -k[i], o[i] == 2 ? 0 : -inf, 1);
        }
        else ex[i] = qry(l[i]) - sgtqry(1, n, l[i], 1);
    }
}
void solve() {
    for (int i = 1; i <= n; i++) 
        for (auto x : q[i]) x.k ? add(x.id, x.k, 0), 0 : ans[x.id] = c[kth(x.c + ex[x.id], x.id - 1)], 0;
    for (int i = 1; i <= m; i++) if (ans[i]) ans[i] < inf ? printf("%lld\n", ans[i]) : puts("0");
}
int main() {
    input();
    solve();
    return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：0)

### Solution

区间神秘修改，从时间维一看就不是很好考虑。因为查询只有单点，我们换个维考虑：从 $1$ 扫到 $n$，维护影响这个位置的所有操作。

首先我们可以把在当前窗口排过队的人维护出来。考虑维护 $(l,r)$ 表示当前队列里的人对应排过队的人中的 $[l,r)$ 的位置，则操作一相当于 $r\gets r+k$，操作二相当于 $l\gets \min(l+k,r)$。

通过 $(\min,+)$ 矩阵乘法表示操作一二的复合。对于操作一有：

$$
\begin{bmatrix}
0 & +\infty\\
+\infty & k
\end{bmatrix}
\begin{bmatrix}
l\\
r
\end{bmatrix}
=
\begin{bmatrix}
l'\\
r'
\end{bmatrix}
$$

对于操作二有：

$$
\begin{bmatrix}
k & 0\\
+\infty & 0
\end{bmatrix}
\begin{bmatrix}
l\\
r
\end{bmatrix}
=
\begin{bmatrix}
l'\\
r'
\end{bmatrix}
$$

一个时间的 $(l,r)$ 相当于矩阵前缀积与初始矩阵的乘积。不难通过线段树维护。

然后考虑查询。实际上相当于查第 $l+B-1$ 个人，可以直接在排队序列中二分找到。这也可以通过线段树完成。

总的时间复杂度即为 $O(n\log n)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=__uint128_t;
using pii=pair<int,int>;
#define fi first
#define se second
constexpr int N=2.5e5+5;
constexpr ll INF=1e18;
int n,m,q;
struct node{
	int op,c;ll k;int id;
	node(){op=c=k=id=0;}
	node(int _op,int _c,ll _k,int _id){op=_op,c=_c,k=_k,id=_id;}
};
vector<node> mdf[N],qry[N];
struct Mat{
	ll a[2][2];
	Mat(){a[0][0]=a[0][1]=a[1][0]=a[1][1]=0;}
	Mat(ll a00,ll a01,ll a10,ll a11){a[0][0]=a00,a[0][1]=a01,a[1][0]=a10,a[1][1]=a11;}
	inline ll* operator [](int i){return a[i];}
	inline const ll* operator [](int i)const{return a[i];}
	friend inline Mat operator *(const Mat &A,const Mat &B){
		return Mat(min(A[0][0]+B[0][0],A[0][1]+B[1][0]),min(A[0][0]+B[0][1],A[0][1]+B[1][1]),
				   min(A[1][0]+B[0][0],A[1][1]+B[1][0]),min(A[1][0]+B[0][1],A[1][1]+B[1][1]));
	}
	inline void out(){
		cerr<<a[0][0]<<' '<<a[0][1]<<'\n'<<a[1][0]<<' '<<a[1][1]<<'\n';
	}
};
const Mat I(0,INF,INF,0);
namespace SGT1{
	int L[N<<2],R[N<<2],M[N<<2];Mat T[N<<2];
	void build(int l,int r,int p=1){
		L[p]=l,R[p]=r,M[p]=(l+r)>>1;
		if(l==r){
			T[p]=I;
			return;
		}
		build(L[p],M[p],p<<1);
		build(M[p]+1,R[p],p<<1|1);
		T[p]=T[p<<1|1]*T[p<<1];
	}
	void update(int x,const Mat &v,int p=1){
		if(L[p]==R[p]){
			T[p]=v;
			return;
		}
		if(x<=M[p])update(x,v,p<<1);
		else update(x,v,p<<1|1);
		T[p]=T[p<<1|1]*T[p<<1];
	}
	Mat query(int l,int r,int p=1){
		if(l<=L[p]&&R[p]<=r)return T[p];
		Mat res=I;
		if(l<=M[p])res=res*query(l,r,p<<1);
		if(M[p]<r)res=query(l,r,p<<1|1)*res;
		return res;
	}
}
namespace SGT2{
	int L[N<<2],R[N<<2],M[N<<2],Code[N<<2];ll Cnt[N<<2];
	void build(int l,int r,int p=1){
		L[p]=l,R[p]=r,M[p]=(l+r)>>1;
		if(l==r){
			Code[p]=Cnt[p]=0;
			return;
		}
		build(L[p],M[p],p<<1);
		build(M[p]+1,R[p],p<<1|1);
		Cnt[p]=Cnt[p<<1]+Cnt[p<<1|1];
	}
	void update(int x,int c,ll k,int p=1){
		if(L[p]==R[p]){
			Code[p]=c,Cnt[p]=k;
			return;
		}
		if(x<=M[p])update(x,c,k,p<<1);
		else update(x,c,k,p<<1|1);
		Cnt[p]=Cnt[p<<1]+Cnt[p<<1|1];
	}
	int query(ll k,int p=1){
		if(L[p]==R[p])return Code[p];
		if(k<=Cnt[p<<1])return query(k,p<<1);
		else return query(k-Cnt[p<<1],p<<1|1);
	}
}
bool out[N];int ans[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++){
		int op;cin>>op;
		if(op==1){
			int l,r,c,k;
			cin>>l>>r>>c>>k;
			mdf[l].emplace_back(1,c,k,i);
			mdf[r+1].emplace_back(-1,c,k,i);
		}
		else if(op==2){
			int l,r,k;
			cin>>l>>r>>k;
			mdf[l].emplace_back(2,0,k,i);
			mdf[r+1].emplace_back(-2,0,k,i);
		}
		else{
			int a;ll b;
			cin>>a>>b;
			out[i]=1;
			qry[a].emplace_back(3,0,b,i);
		}
	}
	SGT1::build(1,q),SGT2::build(1,q);
	for(int i=1;i<=n;i++){
		for(auto &o:mdf[i]){
			if(abs(o.op)==1){
				if(o.op>0){
					SGT1::update(o.id,Mat(0,INF,INF,o.k));
					SGT2::update(o.id,o.c,o.k);
				}
				else{
					SGT1::update(o.id,I);
					SGT2::update(o.id,0,0);
				}
			}
			else{
				if(o.op>0)
					SGT1::update(o.id,Mat(o.k,0,INF,0));
				else
					SGT1::update(o.id,I);
			}
		}
		for(auto &o:qry[i]){
			auto tmp=SGT1::query(1,o.id)*Mat(1,0,1,0);
			ll l=tmp[0][0],r=tmp[1][0];
			if(r-l<o.k)ans[o.id]=0;
			else ans[o.id]=SGT2::query(l+o.k-1);
		}
	}
	for(int i=1;i<=q;i++)
		if(out[i])cout<<ans[i]<<'\n';
	return 0;
}

```

---

