# [POI 2018 R2] 电信中继站 Transceivers

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5070)。

## 题目描述

**题目译自 [XXV Olimpiada Informatyczna — II etap](https://sio2.mimuw.edu.pl/c/oi25-2/dashboard/) [Przekaźniki telekomunikacyjne](https://szkopul.edu.pl/problemset/problem/GmAagCBetbskP0qiKlgVd-6A/statement/)**

国王 Bajtazar 顺应时代潮流，决定为拜托尼亚王国铺设移动电话网络，覆盖所有村庄和城市。这些地点分布在一条笔直的道路上，可视为数轴。

新任命的电信顾问需要一个程序，测试中继站天线杆的位置。每根天线杆顶端装有中继站，由参数 $s$ 和 $a$ 描述。在杆位置 $x$，信号强度为 $s$；在其他点，信号强度随距离线性下降，即在点 $x \pm d$，强度为 $\max(0, s - a \cdot d)$。

道路上某点的信号覆盖强度为所有中继站信号强度的总和。

程序需支持添加或移除天线杆，以及查询某段整数点平均信号覆盖强度的操作。

## 说明/提示

**样例 1 解释**

| 操作 | 结果 | 说明 |
|:------:|:------:|:------:|
| $\texttt{P}\ 5\ 30\ 10$ | - | 在点 $x=5$ 架设天线杆，中继站参数 $s=30, a=10$。 |
| $\texttt{Z}\ 6\ 7$ | $15$ | 点 $6$ 信号强度为 $30-10=20$，点 $7$ 为 $30-2 \cdot 10=10$，区间 $[6,7]$ 整数点的平均强度为 $(20+10)/2=15$。 |
| $\texttt{P}\ 10\ 22\ 5$ | - | 在点 $x=10$ 架设天线杆，中继站参数 $s=22, a=5$。 |
| $\texttt{Z}\ 6\ 7$ | $19$ | 两杆存在，点 $6$ 强度为 $20+2=22$，点 $7$ 为 $10+7=17$，平均强度为 $(22+17)/2=19.5$，向下取整为 $19$。 |
| $\texttt{Z}\ 6\ 6$ | $22$ | 点 $6$ 强度为 $22$，平均为 $22$。 |
| $\texttt{U}\ 5$ | - | 移除点 $x=5$ 的天线杆。 |
| $\texttt{Z}\ 6\ 6$ | $2$ | 点 $6$ 强度为 $2$（仅剩 $x=10$ 的中继站）。 |

**附加样例**

1. $n=101, m=500$，道路首尾中各一杆，随机查询。
2. $n=300000$，点 $1$ 有一杆，$s=100000, a=100$，查询各前缀 $[1, i]$ 的平均强度，$1 \leq i \leq 300000$。
3. $n=300000, m=500000$，每点有杆，$s=1000, a=1$，查询整条路的平均强度。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n, m \leq 2000$         | $8$  |
| $2$    | $n \leq 300000, m \leq 500000$，$\texttt{Z}$ 操作在所有 $\texttt{P}$、$\texttt{U}$ 操作后 | $24$ |
| $3$    | $n \leq 300000, m \leq 500000$，同时最多 $50$ 个中继站 | $16$ |
| $4$    | $n \leq 300000, m \leq 500000$，$\texttt{Z}$ 操作总有 $x_1=x_2$ | $15$ |
| $5$    | $n, m \leq 100000$       | $15$ |
| $6$    | $n \leq 300000, m \leq 500000$，$\texttt{P}$ 操作总有 $a=1$ | $12$ |
| $7$    | $n \leq 300000, m \leq 500000$ | $10$ |

## 样例 #1

### 输入

```
11 7
P 5 30 10
Z 6 7
P 10 22 5
Z 6 7
Z 6 6
U 5
Z 6 6
```

### 输出

```
15
19
22
2
```

# 题解

## 作者：xpigeon (赞：3)

# 二次差分+树状数组

## 前言

场上被创飞了，见过区间加等差序列，没见过要求区间查的，还是太菜了，本题我目前知道两个做法，一种是在线段树上打首项与公差的标记的（题解区有），一种是本题解待会要讲的，比较神秘，我也是从学长那里学来的（学得不是很精髓，可能讲得不太好，如有狗叫之处欢迎指出）。

同时个人认为这题能到上位绿下位蓝的程度，建议蓝一下（小声）。

## 正文

先来看点做法没什么关联但是是本题弱化版的 [P1438 无聊的数列](https://www.luogu.com.cn/problem/P1438) 

两个操作分别是对一个区间加上首项为 $K$ 公差为 $D$ 的等差数列，并单点查询位置 $p$ 上的值。

由于区间加的值有等差的性质，我们可以考虑把维护的原序列转换成差分序列，在差分序列上进行单点加首项，区间加公差即可完成一操作。单点查询 $p$ 也就变成了区间查询 $[1,p]$ 的和，因为我们在线段树上维护的是差分数组，故查询区间和也就变成了原数组上的单点查询。

再回到这道题，题目诡异的查询操作竟然是对原序列求区间和，如果我们继续按照 $P1438$ 的做法维护差分序列，那么我们要查询的是区间前缀和的前缀和，接下来我们慢慢分析并尝试解决这个乱七八糟的东西。

设原序列为:

$$a_1,a_2,a_3 \cdots a_n$$

差分一次后：

$$b_1,b_2,b_3 \cdots b_n$$

我们暂且把 $b$ 序列放到线段树上，并按单点加首项，区间加公差来完成修改操作，那么查询区间 $[1,n]$ 即为查询：

$$\sum_{i=1}^{n} \sum_{j=1}^{i}b_j$$

困难在于，式子的后半部分是一个区间信息，前面又带一个 $\sum_{i=1}^{n}$ 导致这个式子没法在正确的时间复杂度下求出，如果能把后半部分转化成单点信息，我们就可以试着考虑每一个单点的贡献，从而转化成一个区间的查询。

说起来太抽象了，我直接说做法，你们进行一些体会。

我们把差分序列再差分一次得到：

$$c_1,c_2,c_3 \cdots c_n$$

这时对于修改操作就变成了两个单点修改，在 $l$ 加首项在 $r+1$ 加整个等差数列的和，查询区间 $[1,n]$ 变成了：

$$\sum_{i=1}^{n} \sum_{j=1}^{i}\sum_{k=1}^{j}c_k$$

考虑把每一个 $c_k$ 的贡献拆开来看，式子变成：

$$\sum_{k=1}^{n}c_k \times \sum_{i=1}^{n}\sum_{i=1}^{n}[k\leq j \leq i\leq n]$$

后半部分可以直接化出式子,变成：

$$\sum_{k=1}^{n}c_k \times\frac{(n-k+1)(n-k+2)}{2}$$

简单说一下后半部分怎么化的（反正我一开始没反应过来）：考虑 $j\in [k,n]$,一共有 $(n-k+1)$ 种取值，$i\in [j,n]$，对于 $j$ 取不同的值，$i$ 的取值数量有 $n-k+1,n-k,n-k-1 \cdots 1$，求和公式算一下这俩就总共 $\frac{(n-k+1)(n-k+2)}{2}$ 种合法状态。

我们把式子拆拆再归归类：

$$\sum_{k=1}^{n} [k^2 -(2 \cdot n+3) \cdot k+(n^2+3 \cdot n+2)] \cdot c_k$$

发现有关 $k$ 的可以拆成 $0$ 次项、$1$ 次项和 $2$ 次项，我们可以用三个树状数组来维护对应的次项。

这样一来我的查询就优化成了正常的 $O(\log n)$ 级别，核心思想就是对每个单点的信息拆开来计算，保证式子只有一个 $\sum_{k=1}^{n}$。

代码：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define lb(x) ((x)&(-x))
using namespace std;
const int N=3e5+5;
int n,m;
struct {
    int sx,gc;
}ev[N];
struct BIT{
    int t[N];
    void add(int x,int v){
        while(x<=n){
            t[x]+=v;
            x+=lb(x);
        }
    }
    int query(int x){
        int res=0;
        while(x){
            res+=t[x];
            x-=lb(x);
        }
        return res;
    }
}p0,p1,p2;
void add(int x,int v){
    p0.add(x,v),p1.add(x,v*x),p2.add(x,v*x*x);
}
void update(int l,int r,int k,int d){
    //点修首项
    add(l,k),add(l+1,d-k);
    //点修右端点，二次差分后差值为等差数列的和
    add(r+1,-(k+d*(r-l+1))),add(r+2,k+d*(r-l));
}
int query(int x){
    int res=0;
    //0次项计算，后面也可写成(x*x+3*x+2)
    res+=p0.query(x)*(x+1)*(x+2);
    //一次项
    res-=(2*x+3)*p1.query(x);
    //二次项
    res+=p2.query(x);
    return res/2;
}

void xpigeon(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        char opt;
        cin>>opt;
        if(opt=='P'){
            int x,s,a;
            cin>>x>>s>>a;
            ev[x].sx=s;
            ev[x].gc=a;
            int l=max(1ll,x-s/a),r=min(x+s/a,n);
            update(l,x-1,s-a*(x-l),a);
            update(x,r,s,-a);
            
        }else if(opt=='U'){
            int x,s,a;
            cin>>x;
            s=-ev[x].sx,a=-ev[x].gc;
            int l=max(1ll,x-s/a),r=min(x+s/a,n);
            update(l,x-1,s-a*(x-l),a);
            update(x,r,s,-a);
            
        }else{
            int l,r;
            cin>>l>>r;
            cout<<(query(r)-query(l-1))/(r-l+1)<<'\n';
        }
    }
    return ;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    xpigeon();
    return 0;
}

```

---

## 作者：WanderFreeFish (赞：3)

### Basically

首先看完题之后发现需要维护的是区间的修改和区间的求和（和求平均一个意思），那么马上想到用线段树。

接下来面临的问题有两个：如何将单点的向外扩散转化为区间修改？线段树中的懒标记又应该维护什么？

第一个很好解决。容易发现，对于添加操作，第 $i$ 个点所在的位置 $x$ 左边是一个单调递增的等差数列，所在位置 $x$ 右边是一个对称的单调递减的等差数列。而对于删除操作，则是取相反数即可。

现在看第二个问题。对于区间加等差数列的线段树，写法有很多种，应该大部分人会选择差分。我这里选择的是懒标记暴力维护首项与公差。

### More specifically

在线段树中，定义两个标记数组，`lzd` 与 `lzk`，分别负责记录当前的公差，首项。然后利用等差数列求和公式算出当前区间的和。

在 `pushdown()` 函数中，懒标记传给左儿子时，不用修改直接传，因为两者首项相同，公差不变。而在传给右儿子时，首项应是“公差乘左儿子长度加原首项”，公差不变。（这里可能比较不好理解，所以举个例子）

对于一个长度为 $4$ 的等差数列 $[2, 4, 6, 8]$，该序列子树的根上存储的应是 $lzd_i = 2$，$lzk_i = 2$，如果下传，右儿子上的序列应是 $[6, 8]$ 公差为 $2$，首项为 $6$，因为左儿子占据了前缀，这个前缀的长度就为左儿子的长度。综上，在下传右儿子时，$lzk_{rs} \gets lzk_{rs} + (lzk_{root} + (mid - l + 1) \times lzd_{root})$。

还有一个比较简单需要处理的就是通过当前维护的首项与公差计算区间和，这我相信看代码的时候能懂，小学学的那个公式，套上就行了。$tr_{root} \gets tr_{root} + (lzk_{root} + (lzk_{root} + (r - l) \times lzd_{root})) \times (r - l + 1) \div 2$

### Code


```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#define mid (l + r >> 1)
#define ls (root << 1)
#define rs (root << 1 | 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

using ll = long long int;
using PII = std::pair <int, int>;
const int MAXN = 3e5 + 10;

struct segment_tree {
	std::vector <ll> tr, lzd, lzk;
	
	segment_tree (int l = 1) : tr(l << 2), lzd(l << 2), lzk(l << 2) {}
	
	void push_up(int root, int l, int r) {
		push_down(lson); push_down(rson);
		tr[root] = tr[ls] + tr[rs];
	}
	
	void push_down(int root, int l, int r) {
		tr[root] += (lzk[root] + (lzk[root] + (r - l) * lzd[root])) * (r - l + 1) / 2;
		
		if (l != r) {
			lzd[ls] += lzd[root], lzk[ls] += lzk[root];
			lzd[rs] += lzd[root], lzk[rs] += lzk[root] + (mid - l + 1) * lzd[root];
		}
		
		lzk[root] = lzd[root] = 0;
	}
	
	void build(int root, int l, int r) {
		if (l == r) {
			tr[root] = 0;
			return;
		}
		
		build(lson);
		build(rson);
		push_up(root, l, r);
	}
	
	void update(int root, int l, int r, int ql, int qr, int K, int D) {
		push_down(root, l, r);
		if (ql <= l && r <= qr) {
			lzd[root] += D, lzk[root] += K + D * (l - ql); //这里有可能看不懂 其实和 push_down() 中是一样的 都是要先排除前面的前缀 从当前左端点开始
			return;
		}
		
		if (ql <= mid) update(lson, ql, qr, K, D);
		if (mid + 1 <= qr) update(rson, ql, qr, K, D);
		push_up(root, l, r);
	}
	
	ll query(int root, int l, int r, int ql, int qr) {
		push_down(root, l, r);
		
		if (ql <= l && r <= qr) {
			return tr[root];
		}
		
		if (qr <= mid) return query(lson, ql, qr);
		else if (ql > mid) return query(rson, ql, qr);
		else return query(lson, ql, qr) + query(rson, ql, qr);
	}
};

int n, T;
PII info[MAXN];

int main() {
	
	std::cin >> n >> T;
	
	segment_tree sgtree(n + 1);
	sgtree.build(1, 1, n);
	
	while (T--) {
		char op; std::cin >> op;
		if (op == 'P') {
			int x, s, a; std::cin >> x >> s >> a; info[x].first = s, info[x].second = a;
			
			{ //left
				int l = std::max(1, x - s / a), r = x, k = s - (x - l) * a;
				sgtree.update(1, 1, n, l, r, k, a);
			}
			
			{ //right
				if (x + 1 > n) continue;
				int l = x + 1, r = std::min(n, x + s / a), k = s - a;
				sgtree.update(1, 1, n, l, r, k, -a);
			}
		}
		else if (op == 'U') {
			int x, s, a; std::cin >> x; s = info[x].first, a = info[x].second;
			
			{ //left
				int l = std::max(1, x - s / a), r = x, k = s - (x - l) * a;
				sgtree.update(1, 1, n, l, r, -k, -a);
			}
			
			{ //right
				if (x + 1 > n) continue;
				int l = x + 1, r = std::min(n, x + s / a), k = s - a;
				sgtree.update(1, 1, n, l, r, -k, a);
			}
		}
		else {
			int l, r; std::cin >> l >> r;
			std::cout << sgtree.query(1, 1, n, l, r) / (r - l + 1) << '\n';
		}
	}
	return 0;
}
```

### Additionally

这里解释一下，这个算法为什么是对的。可能有的人无法理解为什么能在首项与公差上做结合律。

给你看一个示例：

$S_1 = k_1 + (k_1 + d_1) + (k_1 + 2d_1) + (k_1 + 3d_1) + ... + (k_1 + nd_1)$

$S_2 = k_2 + (k_2 + d_2) + (k_2 + 2d_2) + (k_2 + 3d_2) + ... + (k_2 + nd_2)$

$S_1 + S_2 = k_1 + (k_1 + d_1) + (k_1 + 2d_1) + (k_1 + 3d_1) + ... + (k_1 + nd_1) + k_2 + (k_2 + d_2) + (k_2 + 2d_2) + (k_2 + 3d_2) + ... + (k_2 + nd_2) $

容易发现 $k_1, k_2$ 可以合并。令 $d = d_1 + d_2$，则

$S_1 + S_2 = (k_1 + k_2) + ((k_1 + k_2) + d) + ... + ((k_1 + k_2) + nd)$

合并后的等差数列形式相同，满足加法结合律。这是对于相同长度。至于不同的，注意到在 `update()` 函数中开头的那句，已经下放标记了。

---

## 作者：_H17_ (赞：1)

## 题目分析

注意到差相等，考虑存差分数组。

同时我们需要对它们求和，所以要对差分求前缀和的前缀和。

所以我们维护差分的区间和以及区间前缀和数组的和。

删除操作把加入操作倒着做一遍即可。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
constexpr int N=3e5+1;
int n,q,rt,tot;
map<int,pair<int,int> >mp;
char op;
struct SegmentTreeNode{
	int l,r,ls,rs,sum,ssum,tag;
	SegmentTreeNode(int l=0,int r=0):l(l),r(r),ls(0),rs(0),sum(0),ssum(0),tag(0){}
}f[N<<1];
void pushup(int cur){
	f[cur].sum=f[f[cur].ls].sum+f[f[cur].rs].sum;
	f[cur].ssum=f[f[cur].ls].ssum+f[f[cur].rs].ssum+f[f[cur].ls].sum*(f[f[cur].rs].r-f[f[cur].rs].l+1);
	return;
}
void pushdown(int cur){
	int tag=f[cur].tag,ls=f[cur].ls,rs=f[cur].rs;
	f[ls].tag+=tag,f[rs].tag+=tag;
	f[ls].sum+=tag*(f[ls].r-f[ls].l+1),f[rs].sum+=tag*(f[rs].r-f[rs].l+1),
	f[ls].ssum+=tag*(f[ls].r-f[ls].l+1)*(f[ls].r-f[ls].l+2)/2,
	f[rs].ssum+=tag*(f[rs].r-f[rs].l+1)*(f[rs].r-f[rs].l+2)/2;
	f[cur].tag=0;
	return;
}
void build(int l,int r,int&cur){
	f[cur=(++tot)]=SegmentTreeNode(l,r);
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(l,mid,f[cur].ls),build(mid+1,r,f[cur].rs);
	return pushup(cur);
}
void modify(int l,int r,int val,int cur){
	if(l>r)
		return;
	if(l<=f[cur].l&&f[cur].r<=r){
		f[cur].sum+=val*(f[cur].r-f[cur].l+1);
		f[cur].ssum+=val*(f[cur].r-f[cur].l+1)*(f[cur].r-f[cur].l+2)/2;
		f[cur].tag+=val;
		return;
	}
	pushdown(cur);
	int mid=(f[cur].l+f[cur].r)>>1;
	if(l<=mid)
		modify(l,r,val,f[cur].ls);
	if(mid<r)
		modify(l,r,val,f[cur].rs);
	return pushup(cur);
}
pair<int,int>query(int l,int r,int cur){
	if(l>r)
		return{0,0};
	if(l<=f[cur].l&&f[cur].r<=r)
		return{f[cur].sum,f[cur].ssum};
	pushdown(cur);
	int mid=(f[cur].l+f[cur].r)>>1,sum=0,ssum=0;
	pair<int,int>a,b;
	if(mid<l)
		return query(l,r,f[cur].rs);
	if(r<=mid)
		return query(l,r,f[cur].ls);
	a=query(l,r,f[cur].ls),b=query(l,r,f[cur].rs);
	sum=a.first+b.first;
	ssum=a.second+b.second+a.first*(min(f[f[cur].rs].r,r)-f[f[cur].rs].l+1);
	return{sum,ssum};
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>q;
    build(1,n,rt);
    for(int x1,x2,s,a;q;--q){
    	cin>>op>>x1;
    	if(op=='P'){
    		cin>>s>>a;
    		int tmp=s/a,st,ed,val=s%a,val_=val;
    		st=x1-tmp,ed=x1+tmp;
    		if(st<=0)
    			val+=a*(1-st),st=1;
//    		cerr<<st<<' '<<ed<<' '<<val<<' '<<a<<'\n';
    		modify(st,st,val,rt);
    		modify(st+1,x1,a,rt);
    		modify(x1+1,min(ed,n),-a,rt);
    		if(ed+1<=n)
    			modify(ed+1,ed+1,-val_,rt);
    		mp[x1]={s,a};
		}
		else if(op=='U'){
			s=mp[x1].first,a=mp[x1].second;
			mp[x1]={0,0};
    		int tmp=s/a,st,ed,val=s%a,val_=val;
    		st=x1-tmp,ed=x1+tmp;
    		if(st<=0)
    			val+=a*(1-st),st=1;
    		modify(st,st,-val,rt);
    		modify(st+1,x1,-a,rt);
    		modify(x1+1,min(ed,n),a,rt);
    		if(ed+1<=n)
    			modify(ed+1,ed+1,val_,rt);
		}
		else{
			cin>>x2;
			cout<<(query(1,x2,rt).second-query(1,x1-1,rt).second)/(x2-x1+1)<<'\n';
		}/*
		for(int i=1;i<=4;i++)
			for(int j=1;j<=4;j++){
				auto p=query(i,j,1);
				cerr<<i<<' '<<j<<' '<<p.first<<' '<<p.second<<'\n';
			}*/
	}
    return 0;
}
```

---

