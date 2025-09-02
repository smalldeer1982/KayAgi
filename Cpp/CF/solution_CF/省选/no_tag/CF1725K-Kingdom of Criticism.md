# Kingdom of Criticism

## 题目描述

Pak Chanek is visiting a kingdom that earned a nickname "Kingdom of Criticism" because of how often its residents criticise each aspect of the kingdom. One aspect that is often criticised is the heights of the buildings. The kingdom has $ N $ buildings. Initially, building $ i $ has a height of $ A_i $ units.

At any point in time, the residents can give a new criticism, namely they currently do not like buildings with heights between $ l $ and $ r $ units inclusive for some two integers $ l $ and $ r $ . It is known that $ r-l $ is always odd.

In $ 1 $ minute, the kingdom's construction team can increase or decrease the height of any building by $ 1 $ unit as long as the height still becomes a positive number. Each time they receive the current criticism from the residents, the kingdom's construction team makes it so that there are no buildings with heights between $ l $ and $ r $ units inclusive in the minimum time possible. It can be obtained that there is only one way to do this.

Note that the construction team only cares about the current criticism from the residents. All previous criticisms are forgotten.

There will be $ Q $ queries that you must solve. Each query is one of the three following possibilities:

- 1 k w: The kingdom's construction team changes the height of building $ k $ to be $ w $ units ( $ 1 \leq k \leq N $ , $ 1 \leq w \leq 10^9 $ ).
- 2 k: The kingdom's construction team wants you to find the height of building $ k $ ( $ 1 \leq k \leq N $ ).
- 3 l r: The residents currently do not like buildings with heights between $ l $ and $ r $ units inclusive ( $ 2 \leq l \leq r \leq 10^9-1 $ , $ r-l $ is odd).

Note that each change in height still persists to the next queries.

## 说明/提示

After the $ 1 $ -st query, the height of each building is $ 2, 6, 5, 6, 10 $ .

After the $ 3 $ -rd query, the height of each building is $ 3, 6, 5, 6, 10 $ .

After the $ 4 $ -th query, the height of each building is $ 2, 7, 7, 7, 10 $ .

After the $ 5 $ -th query, the height of each building is $ 2, 7, 7, 7, 10 $ .

After the $ 6 $ -th query, the height of each building is $ 2, 9, 7, 7, 10 $ .

## 样例 #1

### 输入

```
5
2 6 5 6 2
9
1 5 10
2 5
1 1 3
3 3 6
3 8 9
1 2 9
2 3
2 2
2 4```

### 输出

```
10
7
9
7```

# 题解

## 作者：Tjqq (赞：9)

提供一个比较好想的**平衡树**解法

我们可以把数组种的每个元素映射到平衡树上的每个节点，这里我选择使用好写的 fhq-treap（可以参考[书架](https://www.luogu.com.cn/problem/P2596)）。合并和分裂的时候维护值域就行了。

对于操作一：直接求出节点 $x$ 的排名，分裂出来改值后插入即可。

对于操作二，就是 $x$ 的值，注意要从根节点向下全部下传标记。

对于操作三，分裂出 $l$ 至 $mid$ 和 $mid+1$ 至 $r$ 两颗树，打上标记后合并回去即可。

### 代码：

```cpp

#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>
#define ll long long
#define pb emplace_back
#define INF_INT 0x3f3f3f3f
char Ch;
int ff;
inline void rd(int &x) {
	x=0,ff=1,Ch=getchar();
	while((Ch<'0'||Ch>'9')&&Ch!='-') Ch=getchar();
	if(Ch=='-')Ch=getchar(),ff=-1;
	while(Ch>='0'&&Ch<='9') {
		x=(x<<1)+(x<<3)+Ch-'0';
		Ch=getchar();
	}
	x*=ff;
}
using namespace std;
const int N=4e5+5;
int n,Q,rt,a,b,c,d,e;
int sz[N],val[N],pro[N],add[N];
int ch[N][2],prt[N];
mt19937 rnd(time(0));
inline void push_up(int x) {
	sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
	prt[ch[x][0]]=prt[ch[x][1]]=x;
}
inline void push_down(int x) {
	if(add[x]) {
		add[ch[x][0]]=add[x];
		add[ch[x][1]]=add[x];
		val[ch[x][0]]=add[x];
		val[ch[x][1]]=add[x];
		add[x]=0;
	}
}
void split_val(int x,int k,int &ls,int &rs) {
	if(!x) return ls=rs=0,void();
	push_down(x); 
	if(val[x]<=k)
		ls=x,split_val(ch[x][1],k,ch[x][1],rs);
	else 
		rs=x,split_val(ch[x][0],k,ls,ch[x][0]);
	push_up(x);
}
void split_rnk(int x,int k,int &ls,int &rs) {
	if(!x) return ls=rs=0,void();
	int u=sz[ch[x][0]]+1;
	push_down(x);
	if(k>=u)
		ls=x,split_rnk(ch[x][1],k-u,ch[x][1],rs);
	else 
		rs=x,split_rnk(ch[x][0],k,ls,ch[x][0]);
	push_up(x);
}
void update(int x) {
	if(prt[x]) update(prt[x]);
	push_down(x);
}
inline int rnk(int x) {
	update(x);
	int res=sz[ch[x][0]]+1;
	while(prt[x]) {
		if(ch[prt[x]][1]==x)
			res+=sz[ch[prt[x]][0]]+1;
		x=prt[x];
	}
	return res;
}
int merge(int x,int y) {
	if(!x || !y) return x|y;
	push_down(x),push_down(y);
	if(pro[x]<pro[y]) {
		ch[x][1]=merge(ch[x][1],y);
		return push_up(x),x;
	}
	else {
		ch[y][0]=merge(x,ch[y][0]);
		return push_up(y),y;
	}
}
signed main() {
	rd(n);
	for(int i=1; i<=n; i++) {
		rd(val[i]);
		sz[i]=1;
		pro[i]=rnd();
		split_val(rt,val[i]-1,a,b);
		rt=merge(merge(a,i),b);
	}
	rd(Q);
	for(int op,x,y,k,mid; Q--; ) {
		rd(op),rd(x);
		if(op==1) {
			rd(y);
			k=rnk(x);
			split_rnk(rt,k,a,c);
			split_rnk(a,k-1,a,b);
//			printf("pos %d Get %d\n",x,b);
			prt[b]=0,val[b]=y;
			rt=merge(a,c);
			split_val(rt,y-1,a,c);
			rt=merge(merge(a,b),c);
		}
		if(op==2) {
			update(x);
			printf("%d\n",val[x]);
		}
		if(op==3) {
			rd(y);
			mid=x+y>>1;
			split_val(rt,x-1,a,b);
			split_val(b,y,c,b);
			split_val(c,mid,d,e);
			val[d]=x-1;
			add[d]=x-1;
			add[e]=y+1;
			val[e]=y+1;
			c=merge(d,e);
			rt=merge(a,merge(c,b));
		}
//		puts("Treap");
//		for(int i=1; i<=n; i++) {
//			update(i);
//			printf("%d ",val[i]);
//		}
//		puts("");
	}
	return 0;
}
/*
*/
```


---

## 作者：lowbit (赞：4)

发现每次操作 3 至多会增加两种数值，故总的数值不会超过  $O(n+q)$ 个。所以考虑**暴力合并**，合并的总次数不会超过 $O(n+q)$ 次。

使用并查集模拟合并即可，实现时用 set 维护现有的数的集合，每次二分出要修改的数，时空复杂度 $O((n+q)\log (n+q))$。（trick：可以在初始时插入一个极大值方便操作。）

Code：
```cpp
#include <bits/stdc++.h>

typedef long long ll;
typedef double db;
#define ull unsigned long long
#define ldb long double
#define pii pair<int, int>
#define mkp make_pair
#define pb push_back
#define pc putchar
#define sp pc(' ')
#define et puts("")
#define debug cerr<<"--ERROR--"<<endl
#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define per(i, a, b) for(int i = (a); i >= (b); --i)
#define mem(a, x) memset(a, x, sizeof(a))
#define in(a, n) rep(i, 1, n) a[i]=rd()
#define all(x) x.begin(), x.end()

using namespace std;
inline ll rd(){ll x=0, f=1; char c=getchar(); while(c<'0' || c>'9') {if(c=='-') f=-1; c=getchar();} while(c>='0' && c<='9') {x=x*10+c-48; c=getchar();} return x*f;}
inline void wr(ll x){if(x<0) putchar('-'), x=-x; if(x>9) wr(x/10); putchar(x%10+48);}

const ldb eps = 1e-9;
const ll INF = 0x3f3f3f3f;
const int mo = 1e9+7;
const int N = 1.6e6+3;

int n, q, f[N], val[N], tot;
map <int, int> pos;
set <int> s;

void clear() {  }

int find(int k) {
    return f[k]==k ? k : f[k]=find(f[k]);
}
int newnode(int x) {
    s.insert(x);
    val[++tot]=x, f[tot]=tot;
    return tot;
}
void modify(int i, int x) {
    if(!pos[x]) pos[x] = newnode(x);
    f[i] = pos[x];
}
signed main() {
//  freopen(".in", "r", stdin);
//  freopen(".out", "w", stdout);

int TT = 1;
//TT = rd();
while(TT--)
{
    cin >> n;
    rep(i, 1, n) f[i]=i;
    tot=n;
    rep(i, 1, n) {
        int x=rd();
        modify(i, x);
    }
    s.insert(INF);
    cin >> q;
    while(q--) {
        int op, k, v, l, r;
        op=rd();
        if(op == 1) {
            k=rd(), v=rd();
            modify(k, v);
        }
        if(op == 2) {
            k=rd();
            wr(val[find(k)]), et;
        }
        if(op == 3) {
            l=rd(), r=rd();
            for(auto it = s.lower_bound(l); (v=*it) <= r; it = s.lower_bound(l)) {
                modify(pos[v], v-l < r-v ? l-1 : r+1);
                pos[v]=0, s.erase(it);
            }
        }
    }
    et;
    if(TT) clear();
}
    return 0;
}

/*

*/
```

并查集数组记得要开两倍。

---

## 作者：Muel_imj (赞：2)

显然每个二操作是把 $[l,mid]$ 数改为 $l-1$，把 $(mid,r]$ 的数改为 $r+1$。其中 $mid=\lfloor\frac{(l+r)}{2}\rfloor$。

先考虑没有一操作怎么做。

所有修改都是对整个序列的修改，所以把整个序列糊到一块也没问题呐。再注意到操作是值域上的，可以根据这个找个数据结构维护。

我一开始想直接莽平衡树了，但是 CF 上有个标签叫 `dsu`。

然后正解的做法是把权值相同的数放到一个并查集里，再把每个并查集按权值塞进一个 `set` 里，修改的时候二分找到需要修改的东西，然后暴力改即可。

由于每次修改都会有与修改次数同阶的删除，所以复杂度是优秀的 $n\log n$。

再考虑有一操作的话，并查集的结构就会改变，那么如何避免？不能删除就新建好了。单点修改直接开个新点附上相应权值，再把点的编号映射过去即可。复杂度仍是 $n \log n$ 级别的。记得数组稍微开大一点。

码喵：

```cpp
const int maxn=1e6+3,INF=0x3f3f3f3f;
struct dsu{
	int fa[maxn],rk[maxn];
	inline void init(int n){for(reg i=1;i<=n;++i)fa[i]=i;}
	inline int find(int x){return fa[x]^x?fa[x]=find(fa[x]):x;}
	inline void merge(int x,int y){
		x=find(x),y=find(y);
		if(rk[x]<rk[y])fa[x]=y,rk[y]=max(rk[y],rk[x]+1);
		else fa[y]=x,rk[x]=max(rk[x],rk[y]+1);
	}
}V;
int n,m,a[maxn],b[maxn];
set<pair<int,int> > S;
inline void MyDearMoments(){
	n=read(),V.init(n);
	for(reg i=1;i<=n;++i)a[b[i]=i]=read();
	sort(b+1,b+n+1,[](const int x,const int y){return a[x]<a[y];});
	for(reg i=1;i<=n;++i)if(a[b[i]]==a[b[i-1]])V.merge(b[i],b[i-1]);
	for(reg i=1;i<=n;++i)if(V.find(b[i]=i)==i)S.insert(make_pair(a[i],i));
	m=read();
	while(m--){
		switch(read()){
			case 1:{
				int k=read(),w=read();
				a[b[k]=++n]=w,V.fa[n]=n;
				auto it=S.lower_bound(make_pair(w,0));
				if(it!=S.end()&&(*it).first==w)V.merge((*it).second,n);
				else S.insert(make_pair(w,n));
				break;
			}
			case 2:printf("%d\n",a[V.find(b[read()])]);break;
			case 3:{
				int l=read(),r=read(),mid=(l+r)>>1,tmp;
				auto it1=S.lower_bound(make_pair(l,0));
				auto it2=S.upper_bound(make_pair(mid,INF));
				auto it3=S.upper_bound(make_pair(r,INF));
				if(it3==S.begin())break;
				if(it1!=it2){
					a[V.find(tmp=(*it1).second)]=l-1,it1=S.erase(it1);
					for(reg u;it1!=it2;it1=S.erase(it1))
						a[u=V.find((*it1).second)]=l-1,V.merge(tmp,u);
					if(it1!=S.end()&&(*(it1=S.lower_bound(make_pair(l-1,0)))).first==l-1)
						V.merge(tmp,(*it1).second);
					else S.insert(make_pair(l-1,tmp));
				}
				if(it2!=it3){
					a[V.find(tmp=(*it2).second)]=r+1,it2=S.erase(it2);
					for(reg u;it2!=it3;it2=S.erase(it2))
						a[u=V.find((*it2).second)]=r+1,V.merge(tmp,u);
					if(it2!=S.end()&&(*(it2=S.lower_bound(make_pair(r+1,0)))).first==r+1)
						V.merge(tmp,(*it2).second);
					else S.insert(make_pair(r+1,tmp));
				}
			}
		}
	}
}
int main(){return MyDearMoments(),0;}
```

---

## 作者：rizynvu (赞：1)

首先考虑转化一下操作 $3$。  
令 $m = \lfloor\frac{l + r}{2}\rfloor$，操作 $3$ 就相当于是在 $[l, m]$ 内的数变为 $l - 1$，在 $(m, r]$ 内的数变为 $r + 1$。

于是现在对于操作 $3$ 其实就是将一个区间内的数都转为同一个值。  
其实对于这类将大量信息整合为一体的题目，往往运用势能分析能得到更优美的结果。

先给出对应的做法，再对时间复杂度进行一定的分析。  

考虑把相同的 $a_i$ 放在一起处理，因为这些值肯定对于 $3$ 操作也是共同变化的。  
那么就可以用并查集保存信息，每个位置在并查集上对应找到的祖先就为其对应的权值，同时用 `set` 维护下所有的不同的值和对应的并查集的点的编号。

- 对于操作 $1$，直接新开一个节点表示 $a_x = y$ 即可，同时在 `set` 中删去 $a'_x$ 的信息（若存在），并加入 $a_x$ 的信息。  
- 对于操作 $2$，直接并查集查祖先即可。  
- 对于操作 $3$，以将 $[l, m]$ 内的值变为 $l - 1$ 举例。  
  考虑新建一个表示值 $l - 1$ 的点，然后直接暴力在 `set` 中枚举在区间内的值，直接删去这些信息并把其在并查集中的父亲改为新建的 $l - 1$ 的点。  
  最后在 `set` 加入 $l - 1$ 的点的信息即可。

对于操作 1 和 2，显然单次的复杂度为 $\mathcal{O}(\log n)$。

这里着重考虑操作 $3$ 暴力的时间复杂度。

考虑令势能函数 $\varphi(i)$ 为第 $i$ 次操作后不同的 $a_i$ 的值的数量。  
- 如果是 $2$ 操作，因为不会使数发生改变，于是有 $\varphi(i) = \varphi(i - 1)$。
- 如果为 $1$ 操作，那么其实就是删一个数加一个数，肯定势能变化不会超过 $+ 1$，于是有 $\varphi(i) \le \varphi(i - 1) + 1$。
- 如果为 $3$ 操作，不妨先只考虑一半。  
  考虑到这个时候因为会多加入一个值，$\varphi(i)$ 可能会多 $1$。  
  对于暴力删除，设删除了 $c$ 个不同的值，那么就有 $\varphi(i) \le \varphi(i - 1) - c + 1$，此时对应的代价为 $\mathcal{O}(c\log n)$。

那么有 $\varphi(q) \le \varphi(0) + \sum\limits_{i = 1}^q [op_i = 1] + 2\sum\limits_{i = 1}^q [op_i = 3] - \sum c\le n + 2q - \sum c$。  
又因为有 $\varphi(q) > 0$，所以可以知道 $\sum c < n + 2q$。
那么总代价 $\mathcal{O}(\sum c\log n)$ 就是 $\mathcal{O}((n + q)\log n)$ 级别的了。

于是时间复杂度就为 $\mathcal{O}((n + q)\log n)$。

```cpp
#include<bits/stdc++.h>
constexpr int maxn = (4e5 + 10) * 3;
int fa[maxn], val[maxn];
inline int getfa(int x) {
   return ! fa[x] ? x : (fa[x] = getfa(fa[x]));
}
std::set<std::pair<int, int> > s;
int a[maxn], id[maxn];
int main() {
   int n, q, m = 0;
   scanf("%d", &n);
   for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      val[++m] = a[i], s.emplace(a[i], m), id[i] = m;
   }
   scanf("%d", &q);
   for (int op; q--; ) {
      scanf("%d", &op);
      if (op == 1) {
         int x, y;
         scanf("%d%d", &x, &y);
         if (s.find({a[x], id[x]}) != s.end()) {
            s.erase({a[x], id[x]});
         }
         val[++m] = a[x] = y, s.emplace(y, m), id[x] = m;
      } else if (op == 2) {
         int x;
         scanf("%d", &x);
         printf("%d\n", val[getfa(id[x])]);
      } else {
         int l, r;
         scanf("%d%d", &l, &r);
         int mid = l + r >> 1;
         val[++m] = l - 1;
         for (auto it = s.lower_bound({l, 0}); it != s.end() && (*it).first <= mid; ) {
            fa[(*it).second] = m;
            it = s.erase(it);
         }
         s.emplace(l - 1, m);
         val[++m] = r + 1;
         for (auto it = s.lower_bound({mid + 1, 0}); it != s.end() && (*it).first <= r; ) {
            fa[(*it).second] = m;
            it = s.erase(it);
         }
         s.emplace(r + 1, m);
      }
   }
   return 0;
}
```

---

## 作者：ReTF (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1725K)
### 题目描述

> 你需要维护一个长度为 $n$ 的序列，支持以下三个操作：
>
> 1. `1 k w`：单点修改。
> 2. `2 k`：单点查询。
> 3. `3 l r`：对整个区间中值 $\in[l,r]$ 的，将其修改为 $l-1$ 与 $r+1$ 中离他更近的那一个。保证 $r-l$ 为奇数。
>
> 如果后面的操作与前面的矛盾，不管前面的。数据范围：$1\leq n,q\leq 4\times 10^5$。

### 题目分析

容易看出操作 $3$ 的实质是将值 $\in [l,\dfrac{l+r-1}{2}]$ 的位置的值全变为 $l-1$，将值在 $\in [\dfrac{l+r+1}{2},r]$ 的位置的值全变为 $r+1$。

因为有集合之间的合并操作，考虑使用并查集。可以对序列中出现的每一个值 $v$ 建立虚点 $v'$，然后由序列中的每一个位置 $i$ 向其值对应的虚点 $a_i'$ 连边。对于操作 $3$，可以把所有的并查集塞进一个 set，每次在 set 中暴力找到一段区间内的所有虚点，然后将其所在的集合全部合并到一个集合中。

然后可以思考一下操作 $1$ 如何维护。这里我用了一种不同于官方题解的做法。

我们在写并查集时，通常将它视为一个集合，其实它的本质是

**树。**

所以我们可以单点修改 `fa` 数组的值，将某一棵树的子树完整地接到另一棵树上。

所有虚点都是其所在并查集的“根节点”，所以合并时只可能将一个虚点向另一个虚点连边。序列中的每一个位置都是其所在并查集的“叶子节点”。

所以修改时，就可以把要修改的位置与其“父亲节点”断开，然后将其与要改成的值所在的集合合并即可。

每次操作 $1$ 和 $3$ 最多会建立 $1$ 个虚点，开始最多有 $n$ 个虚点，虚点总数上界为 $n+q$，总时间复杂度为 $O((n+q)\log(n+q))$

[代码](https://codeforces.com/contest/1725/submission/220121705) 

---

## 作者：Caiest_Oier (赞：1)

# [CF1725K](https://www.luogu.com.cn/problem/CF1725K)   

第一次见到题号是 K 的题。第一次在 CF 见到这么纯的数据结构题。    

因为需要对某段区间的值修改成统一的值，所以我们考虑对值进行并查集。具体的，对每一个出现的值都开一个点，$A_i$ 连向 $A_i$ 的值所代表的点。在单点修改时，如果未出现这样的点（合并掉的算不出现），新开一个连上去，否则直接连，查询并查集查到根即可。区间修改可以考虑先用 set 存一个当前未合并的值的位置，二分遍历合并即可（合并掉的记得删掉），复杂度是 $O(n\log n)$ 的。   

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,bcj[3000003],tot,v[3000003],k1,k2,k3,k4,k5,k6,k7,k8,k9;
int stk[3000003],tots;
unordered_map<int,int>mp;
set<int>r;
int finf(int now){
	if(bcj[now]!=now)bcj[now]=finf(bcj[now]);
	return bcj[now];
}
int main(){
	scanf("%d",&n);
	tot=n;
	for(int i=1;i<=n;i++)bcj[i]=i;
	for(int i=1;i<=n;i++){
		scanf("%d",&k1);
		if(mp[k1]==0){
			v[++tot]=k1;
			bcj[tot]=tot;
			mp[k1]=tot;
			bcj[i]=tot;
			r.insert(k1);
		}
		else bcj[i]=mp[k1];
	}
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&k1,&k2);
		if(k1==1){
			scanf("%d",&k3);
			if(mp[k3]==0){
				v[++tot]=k3;
				bcj[tot]=tot;
				mp[k3]=tot;
				bcj[k2]=tot;
				r.insert(k3);
			}
			else bcj[k2]=mp[k3];
		}
		if(k1==2)printf("%d\n",v[finf(k2)]);
		if(k1==3){
			scanf("%d",&k3);
			tots=0;
			if(mp[k2-1]==0){
				v[++tot]=k2-1;
				bcj[tot]=tot;
				mp[k2-1]=tot;
				r.insert(k2-1);
			}
			if(mp[k3+1]==0){
				v[++tot]=k3+1;
				bcj[tot]=tot;
				mp[k3+1]=tot;
				r.insert(k3+1);
			}
			k6=mp[k2-1];
			k7=mp[k3+1];
			auto p=r.lower_bound(k2);
			for(;p!=r.end()&&(*p)<=k3;p++){
				k4=(*p);
				stk[++tots]=k4;
				if(abs(k4-(k2-1))<abs(k4-(k3+1))){
					bcj[mp[k4]]=k6;
					mp[k4]=0;
				}
				else{
					bcj[mp[k4]]=k7;
					mp[k4]=0;
				}
			}
			for(int i=1;i<=tots;i++)r.erase(stk[i]);
		}
	}
	return 0;
}
```


---

## 作者：scp020 (赞：0)

# CF1725K Kingdom of Criticism 题解

感觉这个题类似于方伯伯的 OJ 那题。

## 解法

还是考虑使用普通平衡树维护。这里使用 fhq_treap 维护普通平衡树。

平衡树每个节点维护的是值，平衡树外维护每个位置对应的是哪个平衡树节点。这样我们就可以直接单点查询了。

再考虑单点修改。我们找到这个节点的位置，把他左边和右边分裂出去，这个过程即按排名分裂，再更改这个位置的值，把左边右边合并起来，再按值分裂把这个位置插回去。

不难发现正常的平衡树的写法是不支持任取一点将其左右分裂出去的。考虑维护每个节点的父节点，这样可以通过在一个节点一直向上跳进行查询排名，然后按排名分裂就行了。

考虑区间修改，区间修改是不影响平衡树形态的，所以把需要修改的部分拿出来修改打标记再合并回去就行了。

但是回头看单点查询，发现并不能直接查询了，因为这个节点的祖先可能有懒惰标记还没有下传。所以我们从这个节点向上跳，把祖先的懒标记全都下放。

所有操作复杂度均为 $\mathcal{O}(\log n)$。

## 代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
	/**
	 * useless fast IO
	 */
};
using namespace fast_IO;
int n,m,a[400010];
struct fhq_node
{
	int val,w,siz,lazy;
	fhq_node *lc,*rc,*fa;
	inline fhq_node(int val)
	{
		this->val=val,w=rand(),siz=1,lazy=-1,lc=rc=fa=nullptr;
	}
	inline void pushup()
	{
		siz=(lc==nullptr?0:lc->siz)+(rc==nullptr?0:rc->siz)+1;
		if(lc!=nullptr) lc->fa=this;
		if(rc!=nullptr) rc->fa=this;
	}
	inline void pushdown()
	{
		if(lazy!=-1)
		{
			if(lc!=nullptr) lc->lazy=lazy,lc->val=lazy;
			if(rc!=nullptr) rc->lazy=lazy,rc->val=lazy;
			lazy=-1;
		}
	}
};
class fhq_treap
{
private:
	fhq_node *root,*index[400010];
	inline fhq_node *merge(fhq_node *l,fhq_node *r)
	{
		if(l==nullptr && r==nullptr) return nullptr;
		if(l==nullptr) return r;
		if(r==nullptr) return l;
		l->pushdown(),r->pushdown();
		if(l->w<r->w)
		{
			l->rc=merge(l->rc,r),l->pushup();
			return l;
		}else
		{
			r->lc=merge(l,r->lc),r->pushup();
			return r;
		}
	}
	inline std::pair<fhq_node *,fhq_node *> split_rank(fhq_node *rt,const int k)
	{
		std::pair<fhq_node *,fhq_node *> ret;
		if(rt==nullptr) return std::make_pair(nullptr,nullptr);
		rt->pushdown();
		int left=rt->lc==nullptr?0:rt->lc->siz;
		if(k<=left) ret=split_rank(rt->lc,k),rt->lc=ret.second,rt->pushup(),ret.second=rt;
		else ret=split_rank(rt->rc,k-left-1),rt->rc=ret.first,rt->pushup(),ret.first=rt;
		return ret;
	}
	inline std::pair<fhq_node *,fhq_node *> split_val(fhq_node *rt,const int k)
	{
		std::pair<fhq_node *,fhq_node *> ret;
		if(rt==nullptr) return std::make_pair(nullptr,nullptr);
		rt->pushdown();
		if(k<rt->val) ret=split_val(rt->lc,k),rt->lc=ret.second,rt->pushup(),ret.second=rt;
		else ret=split_val(rt->rc,k),rt->rc=ret.first,rt->pushup(),ret.first=rt;
		return ret;
	}
	inline void upd(fhq_node *rt)
	{
		if(rt==nullptr) return;
		if(rt->fa!=nullptr) upd(rt->fa);
		rt->pushdown();
	}
	inline int ask_rank(fhq_node *rt)
	{
		upd(rt);
		int ret=(rt->lc==nullptr?0:rt->lc->siz)+1;
		while(rt->fa!=nullptr)
		{
			if(rt->fa->rc==rt) ret+=(rt->fa->lc==nullptr?0:rt->fa->lc->siz)+1;
			rt=rt->fa;
		}
		return ret;
	}
public:
	inline void add(const int i,const int x)
	{
		std::pair<fhq_node *,fhq_node *> a;
		index[i]=new fhq_node(x),a=split_val(root,x-1);
		root=merge(merge(a.first,index[i]),a.second),root->fa=nullptr;
	}
	inline int ask(const int x)
	{
		upd(index[x]);
		return index[x]->val;
	}
	inline void fix1(const int x,const int y)
	{
		std::pair<fhq_node *,fhq_node *> a,b;
		int rank=ask_rank(index[x]);
		b=split_rank(root,rank),a=split_rank(b.first,rank-1);
		a.second->val=y,root=merge(a.first,b.second),b=split_val(root,y-1);
		root=merge(merge(b.first,a.second),b.second),root->fa=nullptr;
	}
	/**
	 * || 1 ... l-1 || l ... mid || mid+1 ... r || r+1 ... n  ||
	 * ||       a.first          ||         a.second          ||
	 * ||  b.first  || b.second  ||   c.first   ||  c.second  ||
	 *                    l-1            r+1
	 */
	inline void fix2(const int l,const int r)
	{
		std::pair<fhq_node *,fhq_node *> a,b,c;
		int mid=(l+r)/2;
		a=split_val(root,mid),b=split_val(a.first,l-1),c=split_val(a.second,r);
		if(b.second!=nullptr) b.second->val=l-1,b.second->lazy=l-1;
		if(c.first!=nullptr) c.first->val=r+1,c.first->lazy=r+1;
		root=merge(merge(b.first,b.second),merge(c.first,c.second)),root->fa=nullptr;
	}
};
fhq_treap tree;
int main()
{
	srand(time(0));
	in>>n;
	for(int i=1;i<=n;i++) in>>a[i],tree.add(i,a[i]);
	in>>m;
	for(int i=1,op,x,y;i<=m;i++)
	{
		in>>op>>x;
		if(op==1) in>>y,tree.fix1(x,y);
		else if(op==2) out<<tree.ask(x)<<'\n';
		else in>>y,tree.fix2(x,y);
	}
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```

---

## 作者：happybob (赞：0)

考虑使用并查集维护答案。对于目前每种数建立一个虚点，每个点初始父亲就是其权值对应的虚点。

考虑操作 $1$ 是什么。将 $a_x$ 改成 $y$，新建一个 $y$ 的虚点，将 $x$ 的父亲改成新的虚点即可。

操作 $2$ 直接输出 $x$ 在并查集的根对应的权值。

考虑操作 $3$。在所有操作时维护一个 `set` 表示现在存在哪些权值。操作 $3$ 时二分出 $[l,r]$ 内所有权值，将其合并到 $l-1$ 或 $r+1$，然后更新 `set` 即可。

---

## 作者：DengDuck (赞：0)

如果你做过第一分块，第二分块，那么这就是一个水题。

很容易想到用并查集维护数值合并，由于一个数值只会出现一次，删除一次，所以用 `set` 暴力找 $[l,r]$ 的数值就行，然后直接合并，时间复杂度显然是对的。

我的写法比较好懂，对于每一种数值建一个根，所有的这个值的元素作为儿子，合并就是数值的根当成儿子连上去，很好写。

时间复杂度为 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=2e6+5;
//const LL M;
//const LL Mod;
//const LF eps;
//const LL P;
LL n,q,a[N],A[N],tot,Fa[N];
unordered_map<LL,LL>Cnt,Rt;
set<LL>s;
LL Fd(LL x)
{
	if(Fa[x]==x)return x;
	return Fa[x]=Fd(Fa[x]);
}
void Make(LL x)
{
	if(!Rt[x])
	{
		++tot;
		Rt[x]=tot,Fa[tot]=tot,A[tot]=x;		
	}
}
int main()
{
	scanf("%lld",&n);
	tot=n;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		Make(a[i]);
		Fa[i]=Rt[a[i]];
		s.insert(a[i]);
	}
	scanf("%lld",&q);
	while(q--)
	{
		LL op;
		scanf("%lld",&op);
		if(op==1)
		{
			LL x,y;
			scanf("%lld%lld",&x,&y);
			Make(y);
			Fa[x]=Rt[y],a[x]=y;
			s.insert(y);
		}
		if(op==2)
		{
			LL x;
			scanf("%lld",&x);
			LL rt=Fd(x);
			printf("%lld\n",A[rt]);
		}
		if(op==3)
		{
			LL l,r;
			scanf("%lld%lld",&l,&r);
			l--,r++;
			Make(l),Make(r);
			auto p=s.upper_bound(l);
			if(p==s.end())continue;
			LL t=*p;
			if(t>=r)continue;
			s.insert(l),s.insert(r);
			while(t<r)
			{
				if(t-l<=r-t)
				{
					Fa[Rt[t]]=Rt[l];
					Rt[t]=0;
				}
				else
				{
					Fa[Rt[t]]=Rt[r];
					Rt[t]=0;
				}
				s.erase(t);
				t=*s.lower_bound(t+1);
			}
		}
//		cout<<"Look:";
//		for(int i=1;i<=n;i++)
//		{
//			LL rt=Fd(i);
//			cout<<A[rt]<<' ';
//		}
//		cout<<endl;
	}
	return 0;
}
//RP++
```

---

