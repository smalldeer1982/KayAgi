# [ABC380E] 1D Bucket Tool

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc380/tasks/abc380_e

$ 1 $ から $ N $ の番号がついた $ N $ 個のマスが一列に並んでいます。  
$ 1\ \leq\ i\ <\ N $ について、マス $ i $ とマス $ i+1 $ は隣接しています。

最初、マス $ i $ は色 $ i $ で塗られています。

クエリが $ Q $ 個与えられるので、順に処理してください。クエリは次の $ 2 $ 種類のいずれかです。

- `1 x c`: マス $ x $ から始めて「いまいるマスと同じ色に塗られている隣接するマス」への移動を繰り返すことで到達可能なマスを全て色 $ c $ に塗り替える
- `2 c`: 色 $ c $ で塗られているマスの個数を答える

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 1 $ 種類目のクエリにおいて、$ 1\ \leq\ x\ \leq\ N $
- $ 1,2 $ 種類目のクエリにおいて、$ 1\ \leq\ c\ \leq\ N $
- $ 2 $ 種類目のクエリが少なくとも $ 1 $ つ存在する
- 入力は全て整数である

### Sample Explanation 1

クエリにより、マスの色は図のように塗り替えられていきます。 
![図](https://img.atcoder.jp/abc380/c3bf3eec819a7b7fcbfd21065c06bab2.png)

## 样例 #1

### 输入

```
5 6
1 5 4
1 4 2
2 2
1 3 2
1 2 3
2 3```

### 输出

```
3
4```

# 题解

## 作者：liluhexuan (赞：18)

~~我不会告诉你我在结束后 8 分钟做出来了~~

这个题可以将一些颜色相同的相邻单元格抽象成一个集合（也就是后面的一个块），而改变颜色就是改变这个块的颜色标签。于是想到并查集，我们来一步一步将问题逐个击破。

这里规定一下，一个块的老大指的是并查集的每一个集合中 $p_i=i$ 的节点（也就是 find 函数找的）。

在引入一个数组 $col$。$col_i$ 表示一个单元格的颜色（不过由于并查集的优良特性，只有一个块的老大的 $col$ 是正确的）。

### 问题一：如果一个块改变颜色后与相邻的块颜色相同，怎么办？

考虑并查集的合并。如果改变颜色后与相邻的块颜色相同，那就将这两个块合并为一个新的块。于是写出这样的代码：

```cpp
if(x>1&&col[find(x-1)]==c) join(x-1,x);
if(x<n&&col[find(x+1)]==c) join(x,x+1);
```

但如果这么写是会出问题的（我就被这里卡了）。如果我们修改一个长度为三的块的中间为相邻块的颜色，那理论上这两个块应该合并。但由于 $x-1$ 属于这个块，所以就会出现问题。具体看这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/plottvs3.png)

为了防止出现这个错误，我们可以引入一个 $mn$ 数组和 $mx$ 数组，分别表示一个块的最小节点编号和最大节点编号。而相邻两个块就应该是 $mn_x-1$ 和 $mx_x+1$。这两个数组可以在合并时更新。

### 问题2（难点）：如何统计答案？

我们需要引入两个数组：$sum$ 数组和 $s$ 数组。$sum_i$ 表示 $i$ 节点的孩子数量；$s_i$ 表示第 $i$ 种颜色的节点数量。

我们考虑当一个块变色时，这个块原来的颜色应该会减少这个块的点的数量，而新的颜色应该会增加这个块的节点数量。也就是代码中的

```cpp
s[col[find(x)]]-=sum[find(x)];
s[c]+=sum[find(x)];
```

好了，终于可以放代码了：

```cpp
#include<iostream>
using namespace std;
#define int long long //可有可无
const int N=5e5+10;
int p[N],col[N],sum[N],s[N],mn[N],mx[N];
int find(int x){ //非常标准的并查集
	if(x==p[x]) return x;
	return p[x]=find(p[x]);
}
void join(int x,int y){
	x=find(x),y=find(y);
	if(x!=y) sum[x]+=sum[y],p[y]=x; //一定要判定 x!=y
	mx[x]=max(mx[x],mx[y]); //更新最小节点编号
	mn[x]=min(mn[x],mn[y]); //更新最大节点编号
}
bool query(int x,int y){
	return find(x)==find(y);
}
signed main(){
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++) //像屎的初始化
		p[i]=i,col[i]=i,sum[i]=1,s[i]=1,mn[i]=i,mx[i]=i;
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x,c;
			cin>>x>>c;
			s[col[find(x)]]-=sum[find(x)]; //统计答案
			s[c]+=sum[find(x)];
			col[find(x)]=c; //变色
			//合并
			if(x>1&&col[find(mn[find(x)]-1)]==c) join(mn[find(x)]-1,x);
			if(x<n&&col[find(mx[find(x)]+1)]==c) join(x,mx[find(x)]+1);
		}
		else{
			int c; //这要还看不懂就可以退役了
			cin>>c;
			cout<<s[c]<<endl;
		}
	}
	return 0; //拜拜程序
}
```

最后说个注意事项：
1. 程序第 $12$ 行一定要加判定，不然会多算！！！
2. 萌新的拙作，大佬勿喷。
3. 求过，求点赞，求评论。

---

## 作者：Moya_Rao (赞：12)

# 题目大意
给你 $N$ 个格子，编号为 $1 \sim N$，它们按照编号从小到大排成一排。最初，编号为 $i$ 的格子被涂上了颜色 $i$。

现在有 $Q$ 次操作要你按顺序完成，其中每次操作是以下两种之一：
- `1 x c`：表示把编号为 $x$ 的格子，以及 $x$ 左边连续一串和编号为 $x$ 的格子颜色相同的那些格子，还有 $x$ 右边连续一串和编号为 $x$ 的格子颜色相同的那些格子，全部涂成颜色 $c$。
- `2 c`：输出当前颜色为 $c$ 的格子的个数。

# 思路
赛时硬控我一直到结束，最后题目理解出错，思路偏离正解很远很远，第二天再来一看，恍然大悟，拿着第一次的错误代码一调，就过了。不得不说，我还只是一只菜鸡呀，需要多练练。

现在我们回到正题。

其实上，$x$ 还有 $x$ 左边的连续一样颜色以及 $x$ 右边的连续一样颜色，可以看做一个连通块，涂色的时候一起改就是了，是吧？现在你想到了什么？对，就是我们熟悉的并查集！如果你不会并查集，那么请先把 [P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)做掉并学习完并查集后再来做这道题目。

那么我们要怎么合并这些连通块呢？很简单，记录一下这个连通块的左端点和右端点，因为这道题目很特殊，它的一个连通块定是一个区间。合并的时候，就看看当前这个连通块的左端点左边的那个格子（如果存在），所处的那个集合，可不可以经过这次涂色把它们连成一个连通块。还要看当前这个连通块的右端点右边的那个格子（如果存在），所处的那个集合，是不是也可以经过这次涂色把它们连成一个连通块。这些步骤都可以在进行操作 $1$ 时完成。

操作 $2$ 呢？这只能 $O(1)$ 回答啦！弄一个 $cnt$ 数组记录下呗，还是在操作 $1$ 里涂色的时候更新一下就成啦！

是不是还挺简单滴？

# [AC](https://atcoder.jp/contests/abc380/submissions/59904012) 代码
这份代码是加了注释的哟！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+5;
struct node{int l,r,c;}p[N];
//l 和 r 分别是这个集合的两个端点，c 是这个集合目前的颜色
//当然了，只有在 i 是某个集合的代表物时，p[i] 里的数据才是准的
int n,Q,fa[N],cnt[N];//fa 是父亲，cnt 是每种颜色当前个数
int FF(int u){return fa[u]==u?u:fa[u]=FF(fa[u]);}
//经过了路径压缩的找代表物代码，还用了三目运算符（这个总应该懂吧）缩短代码长度
int main(){
    cin>>n>>Q;
    for(int i=1;i<=n;i++)p[i]={i,i,i},fa[i]=i,cnt[i]=1;//初始化
    while(Q--){
        int opt;cin>>opt;//opt 表示操作编号
        if(opt==1){//如果是操作 1
            int id,co;cin>>id>>co;//输入编号以及颜色
            int fid=FF(id);//首先找到当前这个 id 所在集合的代表物
            cnt[p[fid].c]-=p[fid].r-p[fid].l+1;
            //fid 这个集合的所有格子都不再是这个颜色了，要从 cnt 里减去
            p[fid].c=co;//更换颜色
            cnt[p[fid].c]+=p[fid].r-p[fid].l+1;
            //fid 这个集合的所有格子全都变成这个新的颜色了，cnt 要加上
            if(p[fid].l!=1){//如果存在左边的集合
                int fsm=FF(p[fid].l-1);//左边的集合代表物是谁
                if(p[fid].c==p[fsm].c)fa[fsm]=fid,p[fid].l=p[fsm].l;
                //左边的集合与当前集合颜色相同，合并为一个
            }
            if(p[fid].r!=n){//如果存在右边的集合
                int fbg=FF(p[fid].r+1);//右边的集合代表物是谁
                if(p[fid].c==p[fbg].c)fa[fbg]=fid,p[fid].r=p[fbg].r;
                //右边的集合与当前集合颜色相同，合并为一个
            }
        }
        else{//否则是操作 2
            int c;cin>>c;
            cout<<cnt[c]<<"\n";//直接报告答案即可
        }
    }
    return 0;
}
```

---

## 作者：SegmentTree_ (赞：4)

考虑使用珂朵莉树。  
操作 $1$，找到 $x$ 所在的颜色段，然后暴力往外扩展，最后像 `assign` 操作一样，把中间的全删了，插入一个大块。  
操作 $2$ 可以在操作 $1$ 的同时维护一个 $cnt$ 数组。  
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define ui unsigned int
#define i128 __int128
#define lid (id << 1)
#define rid (id << 1 | 1)
const int N = 2e5+5;
namespace tianyu{
    int n, q;
    int cnt[500005];
    struct node{
        int l, r;
        mutable int v;
        node(int L, int R, int V) : l(L), r(R), v(V) {}
        inline bool operator <(const node &b)const{return l == b.l ? r < b.r : l < b.l;}
    };set<node>odt;
    inline auto split(int x){
        auto pos = odt.lower_bound({x, 0, 0});
        if (pos != odt.end() && pos->l == x) return pos;
        if ((--pos)->r < x) return odt.end();
        int l = pos->l, r = pos->r, v = pos->v;
        return (odt.erase(pos), odt.insert({l, x - 1, v}), odt.insert({x, r, v})).first;
    }
    inline void update(int x, int c){
        auto pos = prev(odt.upper_bound({x, (int)1e9, 0}));
        auto pl = pos, pr = next(pos);
        int l = pos->l, r = pos->r;
        cnt[pos->v] -= r - l + 1;
        for (;pl != odt.begin() && prev(pl)->v == pos->v;--pl, cnt[pl->v] -= l - pl->l, l = pl->l) ;
        for (;pr != odt.end() && pr->v == pos->v;cnt[pr->v] -= pr->r - r, r = pr->r, ++pr) ;
        odt.erase(pl, pr);odt.insert({l, r, c});cnt[c] += r - l + 1;
    }
	void awa(){
        cin >> n >> q;
        for (int i = 1;i <= n;i++) odt.insert({i, i, i}), ++cnt[i];
        while (q--){
            int op;
            cin >> op;
            if (op == 1){
                int x, c;
                cin >> x >> c;
                update(x, c);
            }
            else{
                int x;
                cin >> x;
                cout << cnt[x] << '\n';
            }
        }
	}
}
signed main(){
	int T = 1;
	while (T--) tianyu::awa();
	return 0;
}
```

---

## 作者：Zhang_Wenjie (赞：4)

维护序列的全相等联通块，感觉是个很常见的东西，确实做法很多，set，dsu 都可以，

原谅我只想到复杂度更劣的 **线段树 + 二分** qwq



---



一眼看上去，是个很可以用线段树维护的 ds 题。

区间修改很简单，

主要是如何维护，给定一个位置，找该位置的颜色的最大连通块，还要是 $\log$ 级别的时间。

一开始是想倍增跳，但是发现不好维护 **连续相同**。

最后只能是从线段树直接维护的角度想，注意到，**找连通块的左右界，是可以二分的**。

这是显然的，可以简单考虑为区间长度越长，越更可能 **不连续相同**，也就是说如果长度更短的区间都不能连续，那么更长的不可能更优。

然后考虑区间连续相同是不是等价于 $\bigcap\limits_{i = l}^r a_i = a_k~(k\in[l, r])$ 呢？然后 wa 了一大堆。。。

赛后发现随便举出反例 `10 & 11 & 10 = 10`

其实是可以直接维护这个逻辑的，，，子区间相同或否，`pushup` 维护一个标志值就可以了。

最后区间查询，发现数据范围比较小，直接开个颜色的桶就可以了。

复杂度 $O(q\log^2n)$


```cpp
#include <bits/stdc++.h>
#define re register int 
#define lp p * 2
#define rp p * 2 + 1
#define int long long

using namespace std;
typedef pair<int, int> PII;
const int N = 5e5 + 10;

struct Tree { int l, r, sum, tag, flag; } t[N << 2];
int n, q, num[N];

inline void push_up(int p)
{
	t[p].sum = t[lp].sum + t[rp].sum;
	t[p].flag = ((t[lp].flag == t[rp].flag && t[lp].flag) ? t[lp].flag : 0); // 维护一个区间是否全相等的标志
}

inline void push_down(int p)
{
	if (t[p].tag)
	{
		t[lp].sum = (t[lp].r - t[lp].l + 1) * t[p].tag;
		t[rp].sum = (t[rp].r - t[rp].l + 1) * t[p].tag;
		t[lp].flag = t[rp].flag = t[p].tag;
		t[lp].tag = t[p].tag;
		t[rp].tag = t[p].tag;
		t[p].tag = 0;
	}
}

inline void build(int p, int l, int r)
{
	t[p].l = l, t[p].r = r;
	if (l == r)
	{
		t[p].sum = t[p].flag = l;
		return;
	}
	int mid = (l + r) >> 1;
	build(lp, l, mid); build(rp, mid + 1, r);
	push_up(p);
}

inline void update(int p, int l, int r, int k)
{
	if (l <= t[p].l && t[p].r <= r)
	{
		t[p].sum = (t[p].r - t[p].l + 1) * k;
		t[p].flag = k;
		t[p].tag = k;
		return;
	}
	push_down(p);
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) update(lp, l, r, k);
	if (r > mid) update(rp, l, r, k);
	push_up(p);
}

inline int query(int p, int l, int r)
{
	if (l <= t[p].l && t[p].r <= r) return t[p].sum;
	push_down(p);
	int res = 0;
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) res += query(lp, l, r);
	if (r > mid) res += query(rp, l, r);
	
	return res;
}

inline bool ask(int p, int l, int r, int k)
{
	if (l <= t[p].l && t[p].r <= r)
	{
		if (t[p].flag != k) return false;
		return true;
	}
	push_down(p);
	bool res = true;
	int mid = (t[p].l + t[p].r) >> 1;
	if (l <= mid) res &= ask(lp, l, r, k);
	if (r >mid) res &= ask(rp, l, r, k);
	
	return res;
}

inline PII search(int x)
{
	int a = query(1, x, x);	
	int L, R;
	
	int l = 1, r = x;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (ask(1, mid, x, a)) r = mid; 
		else l = mid + 1;
	}
	L = l;
	
	l = x, r = n;
	while (l < r)
	{
		int mid = (l + r + 1) >> 1;
		if (ask(1, x, mid, a)) l = mid;
		else r = mid - 1;
	}
	R = l;
	
	return {L, R};
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> q;
	build(1, 1, n);	
	for (re i = 1; i <= n; i ++) num[i] = 1;
	
	while (q --)
	{
		int op, x, y; cin >> op;
		if (op == 1)
		{
			cin >> x >> y;
			PII k = search(x); int l = k.first, r = k.second;
			
			num[query(1, x, x)] -= (r - l + 1);
			update(1, l, r, y);	
			num[y] += (r - l + 1);
			
		}
		else 
		{
			cin >> x;
			cout << num[x] << '\n';
		}
	}
	
	return 0;
}
```

---

## 作者：daitangchen2008 (赞：3)

## 分析  
初始时每个位置看成一个单独的段，可发现，在染色的过程中段只会在端点颜色相同的时候变少，不会增加。  
于是可以用 set 来维护整个过程。初始时放入每一个段的左端点，每次操作先二分出其所在的端点，然后暴力修改左右端点，并暴力判断是否能合并段，同时在这个过程中修改每个颜色的数量即可。  
时间复杂度 $O(Q\log n)$，可以通过。  
## 代码  

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+10;
const int mod=998244353;
int a[N];
int mhash[N];
int siz[N];
string st;
set<int> s;
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		s.insert(i);a[i]=i;
		siz[i]=1;
	}
		
	s.insert(n+1);
	int q;
	cin>>q;
	while(q--)
	{
		int opt,x,y;
		cin>>opt>>x;
		if(opt==2)
		{
			cout<<siz[x]<<endl;
			continue;
		}
		cin>>y;
		set<int>::iterator it =s.upper_bound(x);
		it--;
		int l=*it;
		it++;
		int r=*it;
		r--;
		it--;
		int num=r-l+1;
		siz[a[l]]-=num;
		a[l]=y;
		siz[a[l]]+=num;
		a[r]=y;
		if(l>=2)
		{
			if(a[l-1]==a[l])
				s.erase(l);
		}
		if(r<n)
		{
			if(a[r]==a[r+1])
				s.erase(r+1);
		}
	}
	return 0;
 } 
```

---

## 作者：Aegleseeker_ (赞：3)

注意到每次修改的是一个区间，即对整个 **同色连通块** 修改，于是我们关心的是那些与自己同色的点，不难发现我们可以用 **并查集** 维护。

考虑带权并查集，对于每个集合我们维护其颜色 $col$，块的左端点 $l$，块的右端点 $r$。对于一次修改，设 $x$ 为修改哪个连通块，我们对于答案将原 $col_x$ 的贡献减去，再加上 $c$ 的贡献，同时维护更新 $col,l,r$ 数组即可。

具体来说，分别判断 $l_x-1$ 的集合的 $col$ 和 $r_x+1$ 的集合 $col$ 是否与 $c$ 相等，如果相等的话将两集合合并。

难度评价是绿。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int fa[N],col[N],sz[N],l[N],r[N];
int find(int x){
	if(fa[x]!=x){
		fa[x]=find(fa[x]);
	}
	return fa[x];
}
int main(){
	int n,q;
	cin>>n>>q;
	for(int i=0;i<N;i++){
		fa[i]=i;sz[i]=1;col[i]=i;
		l[i]=r[i]=i;
	}
	while(q--){
		int op;
		cin>>op;
		if(op==1){
			int x,c;
			cin>>x>>c;
			x=find(x);
			//cout<<x<<'\n';
			if(col[x]==c) continue;
			sz[col[x]]-=r[x]-l[x]+1;sz[c]+=r[x]-l[x]+1;
			int lf=find(l[x]-1),rt=find(r[x]+1);
			if(l[x]-1>=1&&col[lf]==c){
				fa[lf]=x;
				l[x]=l[lf];
				//cout<<find(l[x]-1)<<' '<<fa[find(l[x]-1)]<<'\n';
			}
			if(r[x]+1<=n&&col[rt]==c){
				fa[rt]=x;
				r[x]=r[rt];
			}
			col[x]=c;
			//cout<<l[x]<<' '<<r[x]<<' '<<fa[l[x]]<<'\n';
		}else{
			int c;
			cin>>c;
			cout<<sz[c]<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：bszhangzheng (赞：2)

这里给一个并查集做法，如果你不会并查集就[戳这里](https://www.luogu.com.cn/problem/solution/P3367)。  
我们可以在每次操作中找到当前颜色区间的左端点和右端点，将整个区间改为另一种颜色同时记录答案。但是显然，这种算法的复杂度是 $O(N^2)$ 的。  
考虑优化，因为我们只要知道当前区间的左右端点就可以修改答案了，所以我们可以用并查集维护所有位置所在颜色区间的左端点和右端点，类似于并查集中的父亲，如果颜色修改后和相邻区间颜色相同，就把这两个区间合并起来，即 $fa_i=i\pm1$，每次求出左右端点后修改一下答案即可，时间复杂度应该比 $O(N \log N)$ 快一点。  
代码还是挺短的。

```cpp
//本人喜欢压行，码风良好
#include <bits/stdc++.h>
using namespace std;
const int N=500005;
int cl[N],n,nxt[N],lst[N],c[N],q;
/*
cl：颜色为i时的答案； 
c：当前位置的颜色（不一定是现在的颜色，因为它有可能已经不是端点了）； 
lst,nxt：当前节点的左父亲和右父亲。 
*/
int find(int x){return lst[x]==x?x:lst[x]=find(lst[x]);}//找左端点 
int find2(int x){return nxt[x]==x?x:nxt[x]=find2(nxt[x]);}//找右端点
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++) cl[i]=1,nxt[i]=i,lst[i]=i,c[i]=i;//初始化 
	while(q--)
	{
		int x,y,z;
		cin>>z;
		if(z==2) cin>>x,cout<<cl[x]<<'\n';//直接输出即可 
		else
		{
			cin>>x>>y;
			int l=find(x),r=find2(x);//找左右端点 
			cl[c[l]]-=r-l+1,cl[y]+=r-l+1;//更新答案 
			c[l]=c[r]=y;//只用更改左右端点的颜色 
			if(c[l]==c[l-1]) lst[l]=l-1,nxt[l-1]=l;
			if(c[r]==c[r+1]) nxt[r]=r+1,lst[r+1]=r;
			//如果相邻区间颜色相同就合并区间 
		}
	}
	return 0;
}
```

---

## 作者：zjj2024 (赞：2)

### 思路
看到题目不难想到并查集。

考虑如果一些位置已经合并在一起了，则以后一定不会再分开。

所以用普通并查集记录每个位置所属的连通块标号即可。

记录每个连通块的颜色、左端点、右端点、位置数目。

再计数即可。

注意合并时左右都要合并。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500005;
int fa[N],c[N],cnt[N],l[N],r[N],num[N];
int find(int x)//并查集
{
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,T;
	cin>>n>>T;
	for(int i=1;i<=n;i++)//初始化
	{
		fa[i]=i;
		c[i]=i;
		l[i]=i;
		r[i]=i;
		num[i]=1;
		cnt[i]=1;
	}
	while(T--)
	{
		int op,x,k;
		cin>>op>>k;
		if(op==1)//合并集合、改变颜色
		{
			cin>>x;
			int xx=find(k);
			cnt[c[xx]]-=num[xx];//颜色个数改变
			c[xx]=x;
			cnt[x]+=num[xx];
			int y=find(l[xx]-1);
			if(x==c[y])//合并左边集合
			{
				fa[y]=xx;
				num[xx]+=num[y];
				l[xx]=l[y];
			}
			y=find(r[xx]+1);
			if(x==c[y])//合并右边集合
			{
				fa[y]=xx;
				num[xx]+=num[y];
				r[xx]=r[y];
			}
		}
		else cout<<cnt[k]<<'\n';
	}
	return 0;
}
```

---

## 作者：qfy123 (赞：2)

# Solution
第一眼看上去就像一个用并查集维护的题。想了下发现的确如此。

具体地，对于操作 $1$，我们分解为如下两个操作：
1. 将当前 $x$ 所在的同颜色连通块整体改成颜色 $c$。
2. 更改颜色后，判断这个连通块的颜色分别和左右两边连通块的颜色是否相同，如果相同就合并成一个连通块。

发现上述两个操作可以用并查集维护（具体见代码和注释），操作 $2$ 直接输出当前颜色集合的大小即可。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define pii pair<int,int>
#define PB push_back
#define lson p << 1
#define rson p << 1 | 1
#define ls(p) tr[p].ch[0]
#define rs(p) tr[p].ch[1]
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline string Rs(){
	string str = "";
	char ch = gtc();
	while(ch == ' ' || ch == '\n' || ch == '\r') ch = gtc();
	while(ch != ' ' && ch != '\n' && ch != '\r' && ch > '\0') str += ch, ch = gtc();
	return str;
}
inline int rS(char s[]){
	int tot = 0; char ch = gtc();
	while(ch == ' ' || ch == '\n' || ch == '\r') ch = gtc();
	while(ch != ' ' && ch != '\n' && ch != '\r' && ch > '\0') s[++tot] = ch, ch = gtc();
	return tot; 
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void Ps(string s, int type){
	int m = s.length();
	rep(i, 0, m - 1) pc(s[i]); 
	if(type == 1) pc(' ');
	if(type == 2) pc('\n');
}
inline void pS(char *s, int type){
	int m = strlen(s + 1);
	rep(i, 1, m) pc(s[i]);
	if(type == 1) pc(' ');
	if(type == 2) pc('\n');
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N = 5e5 + 10;
int fa[N], n, q, siz[N], col[N], l[N], r[N];
// l[]: 一个同颜色连通块的左端点， r[]: 一个同颜色连通块的右端点
int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
inline void solve(){
	n = R(), q = R();
	rep(i, 1, n) fa[i] = l[i] = r[i] = col[i] = i, siz[i] = 1;
	while(q--){
		int opt = R();
		if(opt == 1){
			int x = R(), c = R();
			int fx = find(x); //找出 x 所在的一个同颜色连通块
			if(col[fx] == c) continue;
			siz[col[fx]] -= r[fx] - l[fx] + 1; //由于颜色改变，这个连通块原本的颜色的集合大小要减去这个连通块的大小
			col[fx] = c, siz[c] += r[fx] - l[fx] + 1;//然后更改颜色，并将新颜色集合的大小加上这个连通块的大小
			if(l[fx] > 1){ //如果有机会合并左边的连通块
				int fy = find(l[fx] - 1); //找到左边这个点所在的连通块
				if(col[fx] == col[fy]) fa[fy] = fx, l[fx] = l[fy]; //如果两个连通块颜色相同，合并成一个连通块
			}
			if(r[fx] < n){ //同理
				int fy = find(r[fx] + 1);
				if(col[fx] == col[fy]) fa[fy] = fx, r[fx] = r[fy]; 
			}
		}else{
			int c = R();
			out(siz[c], 2);//查询一种颜色集合的大小。
		}
	}
}
signed main(){
    // OI();
    int T = 1;
    // T = R();
	while(T--) solve();
	return 0;
}

```

---

## 作者：BrSt_Spike (赞：1)

## 0.题目大意
给出编号从 $1$ 到 $n$ 的 $n$ 个格子，初始第 $i$ 个格子的颜色为 $i$，接着需要你维护两种操作，第一种操作是将 $x$ 所在的色块（与第 $x$ 个格子颜色相同且包含第 $x$ 个格子的最大区间）全涂成颜色 $c$，第二种操作是输出颜色为 $c$ 的格子数量。
## 1.大致思路
这种区间上的染色问题一般有两种思路：线段树或并查集。但由于这道题的操作一中找色块和并查集中查找集合的操作很类似，所以决定使用并查集。将同一色块内的格子都并在一个集合内。
## 2.具体细节
可以维护以下信息：

- $fa_i$ 这个不用多说
- $siz_i$ 表示集合 $i$ 的大小
- $L_i$ 表示集合 $i$ 的左端点
- $R_i$ 表示集合 $i$ 的右端点
- $col_i$ 表示集合 $i$ 的颜色
- $cnt_i$ 表示颜色为 $i$ 的格子数量

理解了信息含义之后，代码就很好理解了，直接上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5 + 5;
int fa[MAXN], col[MAXN], L[MAXN], R[MAXN], siz[MAXN], cnt[MAXN];
inline int find(int v){
	return (fa[v] == v) ? v : (fa[v] = find(fa[v]));
}
inline void unite(int x, int y){
	int fx = find(x), fy = find(y);
	if(fx == fy) return;
	if(siz[fx] > siz[fy]) swap(fx, fy);
	fa[fx] = fy;
	siz[fy] += siz[fx];
	L[fy] = min(L[fy], L[fx]);
	R[fy] = max(R[fy], R[fx]);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		fa[i] = col[i] = L[i] = R[i] = i;
		siz[i] = cnt[i] = 1;
	}
	while(q--){
		int opt, p, c;
		cin >> opt;
		if(opt == 1){
			cin >> p >> c;
			int fp = find(p);
			cnt[col[fp]] -= siz[fp];
			cnt[c] += siz[fp];
			col[fp] = c;
			if(c == col[find(L[fp] - 1)]) unite(fp, L[fp] - 1);
			if(c == col[find(R[fp] + 1)]) unite(fp, R[fp] + 1);//更改颜色后要判断能否和左右的色块合并
		}else{
			cin >> c;
			cout << cnt[c] << "\n";
		}
	}
	return 0;
}
```

---

## 作者：Nagato__Yuki (赞：1)

[题目传送门](https://atcoder.jp/contests/abc380/tasks/abc380_e)
# Solution
可以用并查集来维护。对于每一个块，维护其颜色以及左右端点。重新涂色的时候，判断涂完色后的块的颜色是否与相邻块的颜色相同，是则用并查集合并一下。

同时维护每种颜色格的数量，查询时直接输出就行了。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mxn 500010
int n,q,f[mxn],sze[mxn],col[mxn],l[mxn],r[mxn];
int fnd(int x){
    return x==f[x]?x:f[x]=fnd(f[x]);
}
void merge(int x,int c){
    int fx=fnd(x);
    int L=l[fx],R=r[fx];
    if(col[fx]==c)return;
    sze[col[fx]]-=R-L+1,col[fx]=c,sze[c]+=R-L+1;
    if(L>1){
        int fl=fnd(L-1);
        if(col[fl]==col[fx])f[fl]=fx,l[fx]=l[fl];
    }
    if(R<n){
        int fr=fnd(R+1);
        if(col[fr]==col[fx])f[fr]=fx,r[fx]=r[fr];
    }
}
void solve(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)f[i]=col[i]=l[i]=r[i]=i,sze[i]=1;
    while(q--){
        int opt,x,c;cin>>opt;
        if(opt==1)cin>>x>>c,merge(x,c);
        else cin>>c,cout<<sze[c]<<'\n';
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int T=1;while(T--)solve();
    return 0;
}
```

---

## 作者：coding_goat (赞：1)

并查集基础练习题，我们记录连通块的左/右端点 $l,r$，父亲节点对应的颜色 $col$，颜色的个数 $siz$，那么每一次合并只用考虑区间左/右侧一个格子是否和现在的格子颜色相同，维护 $l,r$ 即可。合并时要注意使用的变量会不会因为更改导致前后表达的意思不同。

``` cpp
#include<bits/stdc++.h>

#define mem(a,b) memset((a),(b),sizeof(a))
#define m0(a) memset((a),0,sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
#define For(a,b,c) for(int a=(b);a<=(c);a++)
#define Rep(a,b,c) for(int a=(b);a>=(c);a--)
#define in1(a) a=read()
#define in2(a,b) a=read(), b=read()
#define in3(a,b,c) a=read(), b=read(), c=read()
#define inn(i,n,a) For(i,1,n) a[i]=read();

#define ll long long
#define i128 __int128

using namespace std;
inline int read() {
	int xx= 0;int f= 1;
	char c = getchar();
	while(c<'0'||c>'9') { 
		if(c=='-') f= -1;
		c= getchar();
	}
	while(c>='0'&&c<='9') {
		xx= (xx<<1)+(xx<<3)+(c^48);
		c= getchar();
	}
	return xx*f;
}
#define maxn 500050
int fa[maxn];
int col[maxn];
int l[maxn],r[maxn],siz[maxn];
int n,q;
int find(int x) {return x==fa[x]?x:fa[x]=find(fa[x]); }
signed main() {
	in2(n,q);
	For(i,1,n) col[i]=i,fa[i]=i,l[i]=i,r[i]=i,siz[i]=1;
	while(q--) {
		int opt=read();
		if(opt==1) {
			int x=read(),c=read();
			int X=find(x);
			if(col[X]==c) continue;
			siz[col[X]]-=r[X]-l[X]+1;
			col[X]=c;
			siz[col[X]]+=r[X]-l[X]+1;
			if(l[X]>1) {
				int L=find(l[X]-1);
				if(col[L]==c) {
					l[X]=l[L];
					fa[L]=X;
				}
			}
			if(r[X]<n) {
				int R=find(r[X]+1);
				if(col[R]==c) {
					r[X]=r[R];
					fa[R]=X;
				}
			}
		} else {
			int c=read();
			cout<<siz[c]<<'\n';
		}
	}
}
```

---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/AT_abc380_e)

不知道自己在干嘛，一直在考虑分块。如果有老哥会分块做法的话希望留言/kel。

我的做法是考虑重构树的类似结构。

一开始的时候我们看做有 $n$ 个点，对每个点维护覆盖的左右端点，以及颜色。

对于修改操作，我们先把 $x$ 所在的连通块的代表的点改成颜色 $c$，然后观察 $x$ 左边的连通块以及右边的连通块是否相同，如果相同那就合并起来。

注意到只有当前块的颜色改变，所以我们只用维护一个数组 $t_x$ 表示颜色 $x$ 的数量，然后两次单点修改即可。

合并的话，就是新建立一个结点，连向需要合并的两个连通块，同时更新新节点的信息。

这样做是对的，是因为合并操作不会是可逆的，一旦某个连通块变成同一颜色，那么在后续操作里面这个块里面所有点的颜色一定是一起变化的。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
#define DEBUG cout<<"when can get npy"<<endl;
int n,T,fa[N],t[N];
struct node{
	int l,r,col,siz;
}c[N];
int Find(int x){
	return fa[x]==x?x:fa[x]=Find(fa[x]);
}
signed main(){
	cin>>n>>T;
	for(int i=1;i<=n;i++)	fa[i]=i,c[i].l=i,c[i].r=i,c[i].col=i,c[i].siz=1,t[i]=1;
	int tot=n;
	while(T--){
		int op;
		cin>>op;
		if(op==1){
			int x,C;
			cin>>x>>C;
			int now=Find(x);
			int pre=c[now].col;
			t[c[now].col]-=c[now].siz; 
			t[C]+=c[now].siz;
			c[now].col=C,pre=C;
			int l=c[now].l,r=c[now].r;
//			if(x==3&&C==2)	cout<<now<<endl;
			if(l-1>0&&c[Find(l-1)].col==pre){
				int prenow=Find(l-1);
				tot++;
				c[tot].l=c[prenow].l,c[tot].r=c[now].r,c[tot].col=pre,
				c[tot].siz=c[prenow].siz+c[now].siz;
				fa[now]=fa[prenow]=tot,fa[tot]=tot;
//				if(x==3&&C==2)	cout<<c[tot].siz<<endl;
			}
			if(r+1<=n&&c[Find(r+1)].col==pre){
				int prenow=Find(r+1),prelst=Find(now);
				tot++;
				c[tot].l=c[prelst].l,c[tot].r=c[prenow].r,
				c[tot].col=pre,c[tot].siz=c[prenow].siz+c[prelst].siz;
				fa[prelst]=fa[prenow]=tot,fa[tot]=tot;
			}
		}
		else{
			int x;
			cin>>x;
			cout<<t[x]<<endl;
		}
	}
	return 0;
}

```

---

## 作者：hellolin (赞：1)

首先维护各个节点的颜色，以及颜色的节点数。

考虑怎么支持修改，用并查集维护一个连通块最左端的节点，由于之后的操作肯定是块内一起改，所以只修改这个节点的颜色即可。额外维护一个连通块大小，方便计算修改过后的每种颜色节点数。

修改后需要尝试向左 / 右扩展连通块。

时间复杂度 $O(n\alpha(n))$。

---

## 作者：卡卡卡卡卡卡 (赞：1)

萌萌简单题。
## 题解：
考虑这样一件事，一个连通块的大小只会增加，而不会减少，并且只能与相邻的块合并。

我们考虑并查集，当一个块的颜色与相邻的块相等就合并，将块的左端点和右端点更新，再记录每个块的颜色和每个颜色的数量即可。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long fa[500005],col[500005],wh[500005],L[500005],R[500005];
long long opt,x,c;
long long find(long long x)
{
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
void unionn(long long x,long long y)
{
	long long fx=find(x),fy=find(y);
	L[fx]=min(L[fx],L[fy]);
	R[fx]=max(R[fx],R[fy]);
	fa[fy]=fx;
}
int main()
{
	long long n,q;
	cin>>n>>q;
	for(long long i=1;i<=n;i++)fa[i]=i,siz[i]=1,col[i]=1,wh[i]=i,L[i]=i,R[i]=i;
	while(q--)
	{
		cin>>opt;
		if(opt==1)
		{
			cin>>x>>c;
			long long fx=find(x),l=L[fx],r=R[fx];
			col[wh[fx]]-=r-l+1;
			col[c]+=r-l+1;
			wh[fx]=c;
			while(l>1)
			{
				long long f=find(l-1);
				if(wh[f]!=wh[fx])break;
				l--;
				unionn(fx,l);
			}
			while(r<n)
			{
				long long f=find(r+1);
				if(wh[f]!=wh[fx])break;
				r++;
				unionn(fx,r);
			}
		}
		else 
		{
			cin>>x;
			cout<<col[x]<<endl;
		}
	}
}
```

---

## 作者：chenxi2009 (赞：1)

# 思路
用并查集维护连续的同色区间。

每一次修改操作之后用并查集合并颜色相同的相邻的色块。需要维护并查集的大小、颜色和左右端点。修改时根据并查集大小改变颜色对应位置的数量。

时间复杂度 $O(Q\alpha(N))$，$\alpha(N)$ 为查询并查集的复杂度。
# 代码
```cpp

#include<bits/stdc++.h>
using namespace std;
int n,q,op,x,c,f[500001],sum[500001],col[500001],siz[500001],l[500001],r[500001];
int find(int x){//并查集
	return x == f[x] ? x : f[x] = find(f[x]);
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i = 1;i <= n;i ++)l[i] = r[i] = f[i] = col[i] = i,sum[i] = siz[i] = 1;//初始化
	for(int i = 1;i <= q;i ++){
		scanf("%d",&op);
		if(op == 1){
			scanf("%d%d",&x,&c);
			int u = find(x);
			sum[col[u]] -= siz[u],sum[c] += siz[u],col[u] = c;
			if(l[u] > 1 && col[find(l[u] - 1)] == c){//与左侧同色并查集合并 
				int v = find(l[u] - 1);
				siz[v] += siz[u],r[v] = r[u],f[u] = v;
			}
			u = find(x);// 
			if(r[u] < n && col[find(r[u] + 1)] == c){//与右侧同色并查集合并
				int v = find(r[u] + 1);
				siz[v] += siz[u],l[v] = l[u],f[u] = v;
			}
		}
		else{
			scanf("%d",&c);
			printf("%d\n",sum[c]);
		}
	}
	return 0;
}
```

---

## 作者：xixisuper (赞：0)

# AT_abc380_e [ABC380E] 1D Bucket Tool 题解

简单题。

## 思路

注意到颜色连续段的长度只会增加，不会减小，所以我们考虑用并查集来维护每一个连续颜色段。

定义 $lft_i$ 表示 $i$ 左侧满足 $[lst_i,i]$ 颜色相同的某个位置，$rgt_i$ 表示 $i$ 右侧满足 $[i,rgt_i]$ 颜色相同的某个位置（实际上就是并查集里的 `fa`）。初始化时令 $lft_i\gets i,rgt_i\gets i$。对于一次修改，我们只需要找到对于查询的位置 $p$ 来说，满足 $lft_L=L,rgt_R=R$ 的相同颜色段 $[L,R]$，且 $L\le p\le R$。我们只修改 $L,R$ 对应的颜色，来代表这整个颜色块的颜色。修改完之后判断现在这一段是否和与其相邻的两段颜色相同，如果颜色相同就合并。

套上路径压缩，我们就在 $O(q\log n)$ 的时间复杂度解决了该问题。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const ll N=5e5+10;
ll n,q;
ll col[N],lft[N],rgt[N],cnt[N];
ll findlft(ll x){
	if(lft[x]==x) return x;
	return lft[x]=findlft(lft[x]);
}
ll findrgt(ll x){
	if(rgt[x]==x) return x;
	return rgt[x]=findrgt(rgt[x]);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(ll i=1;i<=n;i++){
		col[i]=i;
		cnt[i]=1;
		rgt[i]=lft[i]=i;
	}
	while(q--){
		ll opt,pos,chg;
		cin>>opt;
		if(opt==1){
			cin>>pos>>chg;
			ll gt_lft=findlft(pos);
			ll gt_rgt=findrgt(pos);
			cnt[col[gt_lft]]-=(gt_rgt-gt_lft+1);
			cnt[chg]+=(gt_rgt-gt_lft+1);
			col[gt_lft]=col[gt_rgt]=chg;
			if(gt_lft-1>0){
				if(col[gt_lft-1]==col[gt_lft]){
					rgt[gt_lft-1]=gt_lft;
					lft[gt_lft]=gt_lft-1;
				}
			}
			if(gt_rgt+1<=n){
				if(col[gt_rgt+1]==col[gt_rgt]){
					rgt[gt_rgt]=gt_rgt+1;
					lft[gt_rgt+1]=gt_rgt;
				}
			}
		}
		else{
			cin>>pos;
			cout<<cnt[pos]<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Frictional (赞：0)

## 题意
有一个长度为 $n$ 的序列，第 $i$ 个元素的颜色为 $i$。有两种操作，操作一是找到第 $x$ 个元素，将与他相邻的且颜色相同的元素的颜色都改成 $c$。操作二是查询颜色为 $c$ 的元素个数。
## 解法
这种合并的操作一看就很像并查集，但是我们要考虑怎么去维护。

首先看操作一，因为合并是区间合并，我们在更改完颜色后要判断是不是可以和左右区间合并，这我们就要维护区间左端点和右端点，每次将更改的颜色与左端点的前一个和右端点的后一个比较以下，同时显然肯定要记录一下这个并查集的颜色。

再来看操作二，这就很简单了，我们维护完操作一，只需要维护并查集大小和每种颜色个数，每次修改时加上或减去就可以了。
## [Code](https://atcoder.jp/contests/abc380/submissions/59873396)

---

## 作者：Your_Name (赞：0)

## 题意
$n$ 个格子，如果他和他相邻的格子是同样颜色就把他们合并。

两张操作：
* 把第 $x$ 个元素所在的块染成 $c$ 这个颜色。
* 输出有几个格子是 $c$ 这个颜色。

## 题解
首先看到要合并，直接想到并查集。

但是我们想想怎么处理每次更改的时候怎么合并。

首先直接判他左右和他要改的颜色是不是相同是不行的，因为有可能左右本身就和自己是一个块的。因此我们要看每一个块的左右，而不是每个格子的左右。

代码就很简单了，直接维护每个块的大小，颜色，左右就行。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, q, sz[N], fa[N], col[N], cnt[N], l[N], r[N];
int find(int x){
    if(fa[x] != x)fa[x] = find(fa[x]);
    return fa[x];
}
void merge(int x, int y){
    x = find(x), y = find(y);
    if(x == y)return;
    l[y] = min(l[y], l[x]);//更新左
    r[y] = max(r[x], r[y]);//更新右
    fa[x] = y;//合并
    sz[y] += sz[x];//更新大小
    sz[x] = 0;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i ++){
        fa[i] = i;
        l[i] = r[i] = i;
        col[i] = i;
        cnt[i] = 1;
        sz[i] = 1;
    }//初始化
    while(q --){
        int op, x, c;
        cin >> op;
        if(op == 1){
            cin >> x >> c;
            x = find(x);
            cnt[c] += sz[x];//新颜色个数加上大小
            cnt[col[x]] -= sz[x];//老颜色个数减掉大小
            if(c == col[find(r[x] + 1)]){
                merge(x, r[x] + 1);//合并块右
            }
            if(c == col[find(l[x] - 1)]){
                merge(x, l[x] - 1);//合并块左
            }
            col[find(x)] = c;//修改颜色
        }else{
            cin >> c;
            cout << cnt[c] << '\n';
        }
    }
    return 0;
}
```
 _完结撒花_

---

## 作者：lihaochen123 (赞：0)

### 题目大意

有 $N$ 个格子，$Q$ 此操作，有 $2$ 种操作：
1. 把 $x$ 所在的一段连续的相同颜色的段的颜色涂成 $c$。
2. 询问有多少格子的颜色是 $c$.

### 思路

用并查集维护连续颜色相同的段，具体的，记录每一段的颜色和左右端点。再维护每个颜色的格子个数,。修改颜色时把当前这一段之前的颜色的格子的个数减去这一段的长度，再把修改后的颜色的格子的个数加上长度，然后看前一段和后一段的颜色和修改的颜色是否相同，如果是就合并两段。由于已经维护了每个颜色的格子的个数，查询时可以直接输出答案。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, q, fa[500001], l[500001], r[500001], a[500001], ans[500001];

int findset(int x) {
    if (x == fa[x])
        return x;
    return fa[x] = findset(fa[x]);
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        fa[i] = l[i] = r[i] = a[i] = i;
        ans[i] = 1;
    }
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, c;
            scanf("%d%d", &x, &c);
            int fx = findset(x);
            ans[a[fx]] -= r[fx] - l[fx] + 1;
            ans[c] += r[fx] - l[fx] + 1; //修改答案
            a[fx] = c;
            if (l[fx] > 1) {
                int fy = findset(l[fx] - 1);
                if (a[fx] == a[fy]) {//合并两段
                    fa[fy] = fx;//这样保证了当前这一段的代表元不会改变
                    l[fx] = l[fy];
                }
            }
            if (r[fx] < n) {//同上
                int fy = findset(r[fx] + 1);
                if (a[fx] == a[fy]) {
                    fa[fy] = fx;
                    r[fx] = r[fy];
                }
            }
        } else {
            int c;
            scanf("%d", &c);
            printf("%d\n", ans[c]);
        }
    }
}
```

---

## 作者：Binah_cyc (赞：0)

第一次看见并查集同时维护这么多东西的。

看见这个题的第一眼就感觉像并查集之类的东西能够维护的，考虑如何维护。

动态维护每一种颜色的出现次数，在修改的时候，将 $x$ 所在的并查集颜色修改，同时更新答案。如果它能够和它左面或右面的某一个位置合并，那就合并。

现在，我们考虑这个并查集需要维护什么。因为要更新答案，所以需要维护并查集大小与颜色。同时，还要维护这一段区间的左右端点以方便合并。

代码
```c
// Problem: E - 1D Bucket Tool
// Contest: AtCoder - AtCoder Beginner Contest 380
// URL: https://atcoder.jp/contests/abc380/tasks/abc380_e
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int N=5e5+5;
int n,q,a[N];

int fa[N],l[N],r[N],sze[N],col[N];
int ask(int a){return (fa[a]==a?a:fa[a]=ask(fa[a]));}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++) a[i]=1,fa[i]=l[i]=r[i]=col[i]=i,sze[i]=1;
	while(q--)
	{
		int op,x,y;
		cin>>op;
		if(op==1)
		{
			cin>>x>>y;
			int fx=ask(x);
			a[col[fx]]-=sze[fx];
			a[y]+=sze[fx];//更新答案
			col[fx]=y;//更新颜色
			int lx=ask(l[fx]-1),rx=ask(r[fx]+1);
			if(col[lx]==col[fx]) l[fx]=l[lx],sze[fx]+=sze[lx],fa[lx]=fx;
			if(col[rx]==col[fx]) r[fx]=r[rx],sze[fx]+=sze[rx],fa[rx]=fx;
			//合并
		}
		else cin>>x,cout<<a[x]<<'\n';
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

对于操作 $1$，我们需要找出 $x$ 向左最远连续同色块和向右最远连续同色块。

考虑使用线段树维护每个位置的颜色，区间的最大值，最小值；若区间 $[l,r]$ 的最大值等于最小值，容易得到 $[l,r]$ 内的数都是相同的。

故考虑二分，使用线段树区间查询判断是否都是一个颜色的即可；此时找到了 $[L, R]$ 这个连续同色块，区间赋值即可。

记录每个颜色的数量，询问的话可以 $O(1)$ 回答。

时间复杂度为 $O(n \log^2 n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 5e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Node{
	int l, r;
	int Min, Max;
	int tag;
}X[N << 2];
int n, q, op, x, y;
int a[N], ans[N];
inline void pushup(int k){
	X[k].Max = max(X[k << 1].Max, X[k << 1 | 1].Max);
	X[k].Min = min(X[k << 1].Min, X[k << 1 | 1].Min);
}
inline void assign(int k, int v){
	X[k].Max = X[k].Min = X[k].tag = v;
}
inline void push_down(int k){
	if(X[k].tag){
		assign(k << 1, X[k].tag);
		assign(k << 1 | 1, X[k].tag);
		X[k].tag = 0;
	}
}
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l == r){
		X[k].Max = X[k].Min = l;
		return ;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void update(int k, int l, int r, int v){
	if(X[k].l == l && r == X[k].r){
		assign(k, v);
		return ;
	}
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  update(k << 1, l, r, v);
	else if(l > mid)
	  update(k << 1 | 1, l, r, v);
	else{
		update(k << 1, l, mid, v);
		update(k << 1 | 1, mid + 1, r, v);
	}
	pushup(k);
}
inline pair<int, int> query(int k, int l, int r){
	if(X[k].l == l && r == X[k].r)
	  return {X[k].Max, X[k].Min};
	push_down(k);
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  return query(k << 1, l, r);
	else if(l > mid)
	  return query(k << 1 | 1, l, r);
	else{
		auto A = query(k << 1, l, mid);
		auto B = query(k << 1 | 1, mid + 1, r);
		return {max(A.fi, B.fi), min(A.se, B.se)};
	}
}
bool End;
int main(){
	n = read(), q = read();
	for(int i = 1; i <= n; ++i){
		a[i] = i;
		ans[i] = 1;
	}
	build(1, 1, n);
	while(q--){
		op = read(), x = read();
		if(op == 1){
			y = read();
			int now = query(1, x, x).fi;
			int l = 1, r = x, L = 0;
			while(l <= r){
				int mid = (l + r) >> 1;
				auto t = query(1, mid, x);
				if(t.fi == t.se){
					L = mid;
					r = mid - 1;
				}
				else
				  l = mid + 1;
			}
			l = x, r = n;
			int R = 0;
			while(l <= r){
				int mid = (l + r) >> 1;
				auto t = query(1, x, mid);
				if(t.fi == t.se){
					R = mid;
					l = mid + 1;
				}
				else
				  r = mid - 1;
			}
			ans[now] -= (R - L + 1);
			ans[y] += (R - L + 1);
			update(1, L, R, y);
		}
		else{
			write(ans[x]);
			putchar('\n'); 
		}
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：zengziqvan (赞：0)

注意到原序列的极长同色连续段个数单调不增。

可以使用 set 维护原序列中所有极长同色连续段的左右端点以及颜色，对于每次询问的 $x$ 在 set 上二分所在区间并考虑与相邻两个区间能否合并即可。

这里维护颜色用的是并查集。

复杂度 $O(n\log n)$。

```c++
const int N=5e5+10;
int n,q,col[N],cl[N];
int fa[N],siz[N];
int Get(int x) {
	return fa[x]==x?x:fa[x]=Get(fa[x]);
}
void Merge(int x,int y) {
	int fx=Get(x),fy=Get(y);
	if(fx==fy) return ;
	fa[fy]=fx;
}
set<pair<int,int> >s;
main() {
	cin>>n>>q;
	FOR(i,1,n) fa[i]=i,siz[i]=1;
	FOR(i,1,n) {
		col[i]++;s.insert({i,i});
		cl[i]=i;
	}
	while(q--) {
		int op=read(),x=read(),c;
		if(op==2) cout<<col[x]<<"\n";
		else {
			c=read();
			auto it=prev(s.upper_bound({x,1e9}));
//			cout<<(it->fr)<<" "<<(it->se)<<"RP++\n";
			int l=it->fr,r=it->se;
			col[cl[Get(l)]]-=r-l+1;
			col[c]+=r-l+1;
			cl[Get(l)]=c;
			if(it!=s.begin()) {
				auto it2=prev(it);
				int r2=it2->se,l2=it2->fr;
				if(cl[Get(r2)]==c) {
					Merge(r2,l);
					cl[Get(r2)]=c;
					s.erase(it);s.erase(it2);
					s.insert({l2,r});
				}
			}
			it=prev(s.upper_bound({x,1e9}));
//			cout<<(it->fr)<<" "<<(it->se)<<" "<<(Get(it->se))<<"++RP\n";
//			cout<<cl[Get(4)]<<"fajklfsls\n";
			l=it->fr,r=it->se;
			if(it!=prev(s.end())) {
				auto it2=next(it);
				int r2=it2->se,l2=it2->fr;
				if(cl[Get(r2)]==c) {
					Merge(r2,l);
					cl[Get(r2)]=c;
					s.erase(it),s.erase(it2);
					s.insert({l,r2});
				}
			}
		}
//		for(auto o:s) cout<<(o.fr)<<" "<<(o.se)<<"\n";
	}
	return 0;
}
```

---

