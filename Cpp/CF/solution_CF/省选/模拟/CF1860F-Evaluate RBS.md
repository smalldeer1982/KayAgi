# Evaluate RBS

## 题目描述

现有 $2n$ 个形如 $(a, b, c)$ 的三元组，其中 $a, b$ 均为正整数， $c$ 是字符 `(` 或 `)`（左圆括号或右圆括号)。其中恰有 $n$ 个三元组的 $c$ 为 `(`，另外 $n$ 个为 `)`。

对于两个正实数 $x,y$ ，记一个三元组的特征值为 $\lambda = ax+by$ 。你需要选择 $x,y$ 并对三元组按其特征值升序排序。若多个三元组的特征值相同，可以选择随意排列。

问，是否存在一种选法，使得排序后的序列能让 $c$ 组成一个合法的括号序列。

## 样例 #1

### 输入

```
4
1
1 4 (
2 3 )
1
1 2 )
3 4 (
4
16 5 (
12 3 (
19 6 )
4 10 )
3 10 )
19 11 (
19 7 )
7 14 (
4
16 8 (
11 9 )
20 10 )
20 19 )
2 13 (
18 7 (
15 19 )
5 6 (```

### 输出

```
YES
NO
NO
YES```

# 题解

## 作者：stntn (赞：11)

给你 $n$ 个二元组 $(a,b)$，每个二元组有一个左或右括号，要求找到一组 $(x,y)$ 使得所有 $(a,b)$ 以其与 $(x,y)$ 的点积大小排序后形成的括号序合法。

套路地将点积的 $y$ 提出来，变成 $y(a\frac{x}{y}+b)$，将所有值除去一个 $y$ 大小顺序不变，令 $k=\frac{x}{y}(k > 0)$，点积形式变为 $ka+b$。

我们发现在 $k$ 允许的值域内，两个点 $(a_1,b_1)$，$(a_2,b_2)$ 的大小关系至多变化一次，即在使二者相等的 $k$ 前后发生变化。

数据大小只有 $1500$，暴力求出可能发生变化的点对的斜率，数量是 $O(n^2)$ 级别的，每次变化只涉及 $O(1)$ 个点对，从小到大枚举每个 $k$ ，使用线段树维护括号序，当全局最小值 $\ge0$ 时合法。

注意一些实现细节，对于一些相等的斜率，我们贪心地将左括号向前移动的变化优先实现。

### CODE

[提交记录](https://codeforces.com/contest/1860/submission/221642198)

---

## 作者：Raisetsu41 (赞：3)

好题，但是没啥人补。  
观察一下式子的形式 $ax + by$，给定了一堆 $(a_i, b_i)$，现在要求满足要求的 $(x, y)$，可以放到平面上，把这些二元组看成向量。  
于是相当于按 $(a_i, b_i)$ 和 $(x, y)$ 的点乘结果排序，于是现在假想一个动态的过程，一个向量绕着原点转一圈，查看是否能满足条件。  
于是对于两个点对 $(a_1, b_1)$ 和 $(a_2, b_2)$，我们只用关心在某个时刻，他们的顺序会交换，那么拎出来每个会产生交换的向量 $(x, y)$，数量级是 $n^2$ 的可以接受，将它们按极角排序，思考一下，可以想到向量 $(x, y)$ 每变动一下产生修改的区间是一个连续的段（按该向量上的模排序），检验的方法很典，左右括号赋值，检验是否有前缀值小于 $0$ 即可。  
于是此时直接将修改过的点拎出来，重新排序，然后塞回去即可，动态维护前缀值，只要小于 $0$ 的前缀个数为 $0$ 即可。  
官方题解的代码非常优美，可以反复读一下。

```cpp
int n; read(n);

vector<Bracket> p(n << 1);
for (int i = 0; i < (n << 1); i++) {
  read(p[i].a, p[i].b); char c; cin >> c;
  if (c == '(') p[i].c = +1;
  else p[i].c = -1;
}

map<Point, vector<int>> opt;
for (int i = 0; i < (n << 1); i++) {
  for (int j = 0; j < (n << 1); j++) {
    int x = p[i].b - p[j].b;
    int y = p[j].a - p[i].a;
    if (x <= 0 || y <= 0) continue;
    opt[{ x, y }].push_back(i), opt[{ x, y }].push_back(j);
  }
}
opt[{ 1, INF }];

vector<int> ind(n << 1), reind(n << 1);
iota(all(ind), 0);

sort(all(ind), [&](int i, int j) {
  LL di = dot({ INF, 1 }, p[i]);
  LL dj = dot({ INF, 1 }, p[j]);
  if (di == dj) return p[i].c > p[j].c;
  else return di < dj;
});
for (int i = 0; i < (n << 1); i++) reind[ind[i]] = i;

int neg = 0, now = 0;
vector<int> bal(1, 0);

for (int i : ind) now += p[i].c, bal.push_back(now), neg += now < 0;

bool res = neg == 0;
vector<int> pre;
for (auto it : opt) {
  vector<int> tot = pre;
  for (int x : it.second) tot.push_back(x);
  sort(all(tot), [&](int x, int y) { return reind[x] < reind[y]; });
  tot.resize(unique(all(tot)) - tot.begin());
  for (int x : tot) neg -= bal[reind[x] + 1] < 0;
  vector<int> tmp = tot;
  sort(all(tmp), [&](int i, int j) {
    LL di = dot(it.first, p[i]);
    LL dj = dot(it.first, p[j]);
    if (di == dj) return p[i].c > p[j].c;
    else return di < dj;
  });
  vector<int> nind(tot.size());
  for (int i = 0; i < tot.size(); i++) nind[i] = reind[tmp[i]];
  for (int i = 0; i < tot.size(); i++) reind[tot[i]] = nind[i];
  for (int x : tot) bal[reind[x] + 1] = bal[reind[x]] + p[x].c, neg += bal[reind[x] + 1] < 0;
  if (neg == 0) { res = true; break; }
  pre = it.second;
}

if (res) printf("YES\n");
    else printf("NO\n");
```

---

## 作者：linyihdfj (赞：2)

[更好的阅读体验](https://www.cnblogs.com/linyihdfj/p/17673671.html)
## F.Evaluate RBS
### 题目分析：
看到 $ax + by$ 这种形式一个经典的想法就是转化为比较 $a + b \times \frac{y}{x}$，这样我们相当于只需要考虑 $t = \frac{y}{x}$ 而不用在意 $x,y$ 具体是啥。

也就是可以看成一条与 $y$ 轴截距为 $a$ 斜率为 $b$ 的直线，这样随着 $t$ 的增大必然存在一个位置 $t'$ 使得 $t'$ 之前 $(a_1,b_1)$ 优于 $(a_2,b_2)$ 而在 $t'$ 之后 $(a_1,b_1)$ 劣于 $(a_2,b_2)$。

显然若对于 $(a_1,b_1)$ 和 $(a_2,b_2)$ 存在这样的位置，也就是必然满足 $a_1 > a_2$ 和 $b_1 < b_2$，此时推推就可以知道 $t' = \frac{a_1-a_2}{b_2-b_1}$。

或者如果相反即之前劣于之后优于也行，会发现 $t'$ 的值也是这个式子。

所以其实我们关心的 $t$ 的值只有 $O(n^2)$ 个，也就是只有这些值会直接造成三元组特征值大小关系的变化。

所以就可以考虑直接维护出这 $O(n^2)$ 个值（这里其实是直接维护的分子和分母，这样没有误差），然后从左到右扫描线，每次将会更改大小关系的三元组拿出来更改大小关系，对于特征值相同的三元组为了让它尽可能地形成合法括号序列，则显然应当让左括号放在左边，右括号放在右边。

快速判断合法括号序列可以考虑经典做法：将左括号记为 $1$ 将右括号记为 $-1$，若对于任意位置序列的前缀和均大于 $0$ 则为合法括号序列，这里显然只需要维护一下更改的影响即可。

可以查看 CF 题解区代码，写的十分清晰高妙。

---

## 作者：spdarkle (赞：2)



萌萌题，但是细节比较麻烦。

首先注意到，$ax+by=\lambda$，由于我们只需要若干括号的**相对顺序**，其中一个未知数完全可以舍去，因为可以通过另一个未知数达到相同值。

设我们只关心 $x$ 的取值，变为按照 $ax+b$ 排序。那么设 $k'=a$，变成 $\lambda =k'x+b$，这是一个直线方程，而我们需要选取一个 $x$ 坐标。

那么如何判断一个括号序列合法呢？将左括号看作 $1$，右括号看作 $-1$。则对于该括号序列而言，任意前缀之和不小于 $0$，且全局和为零，即满足条件。

通过以上分析，原问题化为：给定若干条直线，第 $i$ 条权值为 $w_i(w_i\in \lbrace 1,-1\rbrace)$，需要选出一个 $x$，使得将对应 $y$ 坐标排序后，前缀和任意位置不小于零。

这是一个简单的问题。注意到 $n\le 1500$，这说明直线不超过 $3000$ 条，也即交点最多只有 $9\times 10^6$ 个，而一看时间限制有十秒，稳稳地 $n^2\log n$。

可以考虑将每一个交点处理出来。排序，从左往右处理每一个交点，并且动态维护前缀和即可。

详细地说：

根据直线求交公式：$x=\frac{b_2-b_1}{k_1-k_2}$，我们处理出 $x>0$ 的两条直线的交点。（注意选择的横坐标需要是正实数。）

然后记录一下这两条直线的编号。将这些交点排序，依次处理。

处理时，我们动态维护每个直线的排名 $rk_i$，执行到点 $(x,y,p_1,p_2)$  时，先撤销 $p_1,p_2$ 对前缀和的影响，再互换二者的 $rk$，加上其影响。

最后判断全局最小值是否小于零即可。

前缀和的维护可以使用线段树，执行区间修改和最小值维护。

说一些细节和实现上的技巧：

1. 在最初的时候，我们以 $x=0$ 做一次排序为最初的 $rk$，这里可以方便地直接将所有直线排序。排序规则比较复杂，首先按 $b$ 自小到大，$b$ 相同的时候按照 $k$ 自小到大排序。若 $k$ 仍然相同，说明两直线重合，此时按照其权值贪心地自大到小即可。

2. 在求交的时候需要注意通过对 $a$ 的排序，我们只需要枚举 $(i,j),j>i$，但需要满足 $k_i>k_j$。注意是严格大于。

3. 为了保证精度，交点的横坐标可以存下分子分母，否则可能 $eps$ 需要设置的非常小才可以通过，比如 $eps=10^{-18}$。

4. 在对点排序时，先按照 $x$ 坐标排序，若相同则按照左右两端点的权值排序。需要注意的是右端点优先左端点，原因是右端点在交换后排名更靠前。

5. 在修改点的时候，若遇到 $rk_l>rk_r$ 的情况，可以直接略去。

   >这种情况是很巧妙的解决。此时会有多线共交，两个端点在与其他直线操作的时候，就已经更改了排名，此处是满足了更改后 $rk'_l>rk'_r$ 的情况，故不用操作。
   >
   >事实上，这里它潜在地完成了一次排序操作，即将排名倒转。
   >
   >如果不进行该操作会在第三个点出错。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 3050
struct line{
	int k,b,w;
	bool operator<(const line t)const {
		return b==t.b?(k==t.k?w>t.w:k<t.k):b<t.b;
	} 
}a[N];
struct node{
	int l,r,lz,mn;
}t[N<<2];
#define lc x<<1
#define rc x<<1|1
void pushdown(int x){
	if(t[x].lz!=0){
		t[lc].mn+=t[x].lz;t[lc].lz+=t[x].lz;
		t[rc].mn+=t[x].lz;t[rc].lz+=t[x].lz;
		t[x].lz=0;
	}	
}
void pushup(int x){
	t[x].mn=min(t[lc].mn,t[rc].mn);
}
void build(int x,int l,int r){
	t[x].l=l,t[x].r=r,t[x].mn=t[x].lz=0;
	if(l==r)return ;
	int mid=l+r>>1;
	build(lc,l,mid);build(rc,mid+1,r);
	pushup(x);
}
void change(int x,int l,int r,int k){
	if(l<=t[x].l&&t[x].r<=r){
		t[x].mn+=k,t[x].lz+=k;return ;
	}
	pushdown(x);
	if(t[lc].r>=l)change(lc,l,r,k);
	if(t[rc].l<=r)change(rc,l,r,k);
	pushup(x);
} 
#define db double
struct point{
	int p,q,l,r;
	bool operator<(const point  b)const {
		return p*b.q==q*b.p?(a[r].w==a[b.r].w?a[l].w<a[b.l].w:a[r].w>a[b.r].w):p*b.q<q*b.p;
	}
}p[N*N];
int tot,rk[N];
signed main(){
	ios::sync_with_stdio(false);
	int T;cin>>T;
	while(T--){
		int n;cin>>n;tot=0;
		n<<=1;build(1,1,n);
		for(int i=1;i<=n;i++){
			cin>>a[i].k>>a[i].b;char c;
			cin>>c;a[i].w=(c==')'?-1:1);
			rk[i]=i;
		} 
		sort(a+1,a+n+1);build(1,1,n);
		for(int i=1;i<=n;i++)change(1,i,n,a[i].w);
		for(int i=1;i<=n;i++)
			for(int j=n;j>i;j--)
				if(a[i].k>a[j].k)p[++tot]=(point){a[j].b-a[i].b,a[i].k-a[j].k,i,j};
		sort(p+1,p+tot+1);int tag=0;
		if(t[1].mn>=0){
			cout<<"Yes\n";continue;
		}
		for(int i=1;i<=tot;i++){
			int x=p[i].l,y=p[i].r;
			if(rk[x]>rk[y])continue;
			change(1,rk[x],n,-a[x].w);
			change(1,rk[y],n,-a[y].w);
			swap(rk[x],rk[y]);
			change(1,rk[x],n,a[x].w);
			change(1,rk[y],n,a[y].w);
			if(t[1].mn>=0){
				tag=1;break;
			}
		}
		if(tag)cout<<"Yes\n";
		else cout<<"No\n";
	}
} 
// 2 9
// x+7,2x+5,4x+1
```



---

## 作者：封禁用户 (赞：1)

首先，三元组序列实际上是和 $\frac{x}{y}$ 有关，接下来我们不难发现，对于任意两个三元组都只有两种情况：
- 两者大小关系为大于，小于或者等于恒成立。
- 大小关系随 $\frac{x}{y}$ 的变化而变化，存在某个临界点使得两者相等，而临界点上下的不等关系相反。

$n \leq 1500 $，那么一共最多存在 $n^2$ 个临界点，同时每个临界点需要考虑的不等关系个数的总和也是 $n^2$，复杂度合理那么我们以此继续思考。

将三元组先按照 $\{a,b,c\}$ 排序，此时 $\frac{x}{y}$ 处于极大状态，然后从大到小遍历临界点，每到达一个临界点，我们进行两次排序操作：

- 首先考虑将所有以此为临界点的三元组对先按照 $c$ 排列，即 $\frac{x}{y}$ 取值为当前临界点时恰好相等的值。
- 再考虑将所有以此为临界点的三元组按照 $\frac{x}{y}$ 较临界点略小的情况排序，以满足后续条件。

序列合法性用线段树判断即可，排序可以考虑直接对点对进行两两交换，但是为了防止出现交换错位而使得某些（被换到等值的）后面，需要对该临界点的三元组进行排序，优先进行在序列中相对靠后的元素的交换。

只要存在某个时刻合法，那么答案即为 Yes。
```
#include<bits/stdc++.h>
#define ll long long
#define lowbit(x) (x&-x)
using namespace std;
int n,ans,qq,tt;
int a[3005],b[3005],c[3005],p[3005],sum[3005],l[3005];
double now;
vector<pair<double,pair<int,int>>>s;
vector<pair<int,int>>t;
int tree[3005<<2],tag[3005<<2];
const double eps=1e-6;
inline void push_up(int u){
    tree[u]=min(tree[u*2],tree[u*2+1]);
}
inline void push_down(int u){
    tree[u*2]+=tag[u];
    tree[u*2+1]+=tag[u];
    tag[u*2]+=tag[u];
    tag[u*2+1]+=tag[u];
    tag[u]=0;
}
inline void build(int u,int l,int r){
    tag[u]=0;
    if(l==r){
        tree[u]=sum[l];
        return;
    }
    build(u*2,l,l+r>>1);
    build(u*2+1,l+r+2>>1,r);
    push_up(u);
}
inline void add(int u,int l,int r,int L,int R,int k){
    if(k==0)return;
    if(l>R||r<L)return;
    if(l>=L&&r<=R){
        tree[u]+=k;
        tag[u]+=k;
        return;
    }
    push_down(u);
    add(u*2,l,l+r>>1,L,R,k);
    add(u*2+1,l+r+2>>1,r,L,R,k);
    push_up(u);
}
inline void change(int x,int y){
    x=l[x];y=l[y];
    if(y<x)swap(x,y);
    add(1,1,n,x,y-1,c[p[y]]-c[p[x]]);
    swap(p[x],p[y]);
    l[p[x]]=x;l[p[y]]=y;
}
bool cmp1(int x,int y){
    if(a[x]!=a[y])return a[x]<a[y];
    if(b[x]!=b[y])return b[x]<b[y];
    return c[x]>c[y];
}
bool cmp(pair<int,int>x,pair<int,int>y){
    int xx,yy;
    xx=max(l[x.first],l[x.second]);
    yy=max(l[y.first],l[y.second]);
    if(xx!=yy)return xx>yy;
    xx=min(l[x.first],l[x.second]);
    yy=min(l[y.first],l[y.second]);
    return xx>yy;
}
void solve(){
    s.clear();ans=0;
    scanf("%d",&n);n*=2;
    for(int i=1;i<=n;i++){
        char cc;
        scanf("%d%d %c",&a[i],&b[i],&cc);
        if(cc=='(')c[i]=1;
        else c[i]=-1;
        p[i]=i;
    }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            if(a[i]>=a[j]&&b[i]>=b[j])continue;
            if(a[i]<=a[j]&&b[i]<=b[j])continue;
            s.push_back({(double)(b[j]-b[i])/(a[i]-a[j]),{i,j}});
            if(c[i]<c[j])swap(s.back().second.first,s.back().second.second);
        }
    sort(s.begin(),s.end());
    sort(p+1,p+n+1,cmp1);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+c[p[i]];
        l[p[i]]=i;
    }
    build(1,1,n);
    if(tree[1]>=0)ans=1;
    while(!s.empty()&&(!ans)){
        t.clear();
        now=s.back().first;
        while(!s.empty()&&(now==s.back().first)){
            t.push_back(s.back().second);
            s.pop_back();
        }
        sort(t.begin(),t.end(),cmp);
        for(auto i:t)
            if(l[i.first]>l[i.second]&&c[i.first]>c[i.second])
                change(i.first,i.second);
        if(tree[1]>=0)ans=1;
        sort(t.begin(),t.end(),cmp);
        for(auto i:t){
			int x,y;
			x=min(l[i.first],l[i.second]);
			y=max(l[i.first],l[i.second]);
			x=p[x];y=p[y];
			if(b[x]>b[y])change(x,y);
		}
    }
    if(ans)puts("Yes");
    else puts("No");
}
int main(){
    int t=1;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
```

---

## 作者：Leasier (赞：1)

考虑减小我们需要讨论的 $(x, y)$ 的状态数，可知：

- $(+\infty, 1)$。
- $\forall 1 \leq i, j \leq 2n$，$a_i < a_j, b_i > b_j$，$(b_i - b_j, a_i - a_j)$。

或者说，我们只需要讨论所有使得两项交换的临界点。按 $\frac{y}{x}$ 排序时，相邻临界点之间的状态不变，在临界点上我们只需在值相同的情况下把左括号尽量往前放，于是临界点不劣于它和与其相邻的临界点之间的项。

现在我们只需要知道如何在从一个临界点到下一个临界点时维护括号序列的前缀和是否存在 $< 0$ 的项。

注意到每次临界点变化只会给与这两个临界点有关的项带来影响，于是我们把它们抓出来重排后重算这些位置的括号序列前缀和，并维护全局括号序列的前缀和有几个位置 $< 0$ 即可。

由于与这每个临界点有关的项数之和为 $O(n^2)$，时间复杂度为 $O(n^2 \log n)$。

~~排序时需要注意对每一维（包括下标）排序，要不然就会像我因为值相同的元素 unique 不掉而使劲 WA on 3。~~

代码：
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

typedef struct {
	bool operator ()(const pair<int, int> a, const pair<int, int> b){
		return (ll)a.second * b.first < (ll)a.first * b.second;
	}
} Compare;

int x, y;
int a[3007], b[3007], op[3007], id[3007], ref[3007], sum[3007];
map<pair<int, int>, vector<int>, Compare> mp;

inline bool cmp(int p, int q){
	ll val1 = (ll)a[p] * x + (ll)b[p] * y, val2 = (ll)a[q] * x + (ll)b[q] * y;
	if (val1 != val2) return val1 < val2;
	if (op[p] != op[q]) return op[p] > op[q];
	return p < q;
}

int main(){
	int t;
	cin >> t;
	for (register int i = 1; i <= t; i++){
		int n, m, cnt = 0;
		bool ans;
		cin >> n;
		m = n * 2;
		for (register int j = 1; j <= m; j++){
			char ch;
			cin >> a[j] >> b[j] >> ch;
			op[j] = ch == '(' ? 1 : -1;
		}
		mp.clear();
		for (register int j = 1; j <= m; j++){
			for (register int k = 1; k <= m; k++){
				int x = b[j] - b[k], y = a[k] - a[j];
				if (x > 0 && y > 0){
					pair<int, int> pr(x, y);
					mp[pr].push_back(j);
					mp[pr].push_back(k);
				}
			}
		}
		x = 1e9;
		y = 1;
		for (register int j = 1; j <= m; j++){
			id[j] = j;
		}
		sort(id + 1, id + m + 1, cmp);
		for (register int j = 1; j <= m; j++){
			ref[id[j]] = j;
			sum[j] = sum[j - 1] + op[id[j]];
			if (sum[j] < 0) cnt++;
		}
		if (cnt == 0){
			ans = true;
		} else {
			vector<int> v1;
			ans = false;
			for (register map<pair<int, int>, vector<int>, Compare>::iterator j = mp.begin(); j != mp.end(); j++){
				int size = v1.size();
				vector<int> v2 = j->second, v3;
				for (register int k = 0; k < size; k++){
					v2.push_back(v1[k]);
				}
				sort(v2.begin(), v2.end(), cmp);
				v2.erase(unique(v2.begin(), v2.end()), v2.end());
				size = v2.size();
				for (register int k = 0; k < size; k++){
					v3.push_back(ref[v2[k]]);
				}
				x = j->first.first;
				y = j->first.second;
				sort(v2.begin(), v2.end(), cmp);
				for (register int k = 0; k < size; k++){
					ref[v2[k]] = v3[k];
					id[v3[k]] = v2[k];
				}
				for (register int k = 0; k < size; k++){
					if (sum[v3[k]] < 0) cnt--;
					sum[v3[k]] = sum[v3[k] - 1] + op[v2[k]];
					if (sum[v3[k]] < 0) cnt++;
				}
				if (cnt == 0){
					ans = true;
					break;
				}
				v1 = j->second;
			}
		}
		if (ans){
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

设 $x'=\frac xy$，即按 $ax'+b$ 排序，类似直线点斜式。

于是转化为了：有若干一次函数 $f_n(x)=k_nx+b_n$，钦定 $x'>0$，按照 $f_n(x')$ 排序，交点处顺序任意。

先按照 $x'=0+\varepsilon$ 排序，产生排名 $rk_i$，然后扫描线，按 $x$ 左到右枚举每对交点 $(f_i,f_j,x)$，交换 $rk_i,rk_j$ 的位置即可。判断合法也好做，维护 $\pm1$ 的前缀和 $s_i$，再把所有 $s_i$ 放进 set，看最小值是否非负即可。

现在处理不了多线共点，但是注意到共点的线一定 $rk$ 是段区间 $[l,r]$，暂时把 $s_l,\cdots,s_{r-1}$ 从 set 删掉即可。因为顺序任意，一定能通过重排让 $s_l,\cdots,s_{r-1}\gt s_r$。

总复杂度 $O(n^2\log n)$，实现需要用 `pair` 实现分数类，对 $(k,b)$ 去重，有点难写。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define mp make_pair
 
using ll = long long;
 
const int N = 3e3 + 5;
 
struct val{
	ll u,v;
	bool operator<(const val& x) const { return u * x.v < v * x.u; }
	bool operator==(const val& x) const { return u * x.v == v * x.u; }
};
 
int _,n,m,id[N],pos[N],A[N],S[N];
multiset<int> T;
map<pair<int,int>,int> M;
map<val,vector<int>> a;
ll K[N],B[N];

val Pnt(int i,int j){ return val(B[i] - B[j],K[j] - K[i]); }
 
int main(){
	for(cin >> _;_--;){
		cin >> n,n *= 2,M.clear(),T.clear(),a.clear(),m = 0;
		memset(A,0,sizeof A);
		for(int i = 1,k,b;i <= n;++i){
			char c;
			cin >> k >> b >> c;
			if(!M[mp(k,b)]) M[mp(k,b)] = ++m,K[m] = k,B[m] = b,id[m] = m;
			A[M[mp(k,b)]] += c == '(' ? 1 : -1;
		}
		for(int i = 1;i <= m;++i)
			for(int j = 1;j <= m;++j) if(K[i] < K[j]){
				val x = Pnt(i,j);
				if(x.u > 0) a[x].push_back(i),a[x].push_back(j);
			}
		sort(id + 1,id + m + 1,[](int i,int j){ return tie(B[i],K[i]) < tie(B[j],K[j]); });
		for(int i = 1;i <= m;++i) pos[id[i]] = i,S[i] = S[i - 1] + A[id[i]],T.insert(S[i]);
		bool flg = 0;
		for(auto&[x,V] : a){
			sort(begin(V),end(V),[](int i,int j){ return pos[i] < pos[j]; });
			V.erase(unique(begin(V),end(V)),end(V));
			for(int R = 0,L = 0;R < V.size();++R)
				if(R == V.size() - 1 || !(Pnt(V[R],V[R + 1]) == x)){
					for(int i = pos[V[L]];i < pos[V[R]];++i) T.erase(T.find(S[i]));
					L = R + 1;
				}
			if(*T.begin() >= 0){ flg = 1; break; }
			for(int R = 0,L = 0;R < V.size();++R)
				if(R == V.size() - 1 || !(Pnt(V[R],V[R + 1]) == x)){
					int x = pos[V[L]],y = pos[V[R]];
					reverse(id + x,id + y + 1);
					for(int i = x;i <= y;++i) pos[id[i]] = i;
					for(int i = x;i < y;++i) S[i] = S[i - 1] + A[id[i]],T.insert(S[i]);
					L = R + 1;
				}
		}
		if(*T.begin() >= 0) flg = 1;
		puts(flg ? "YES" : "NO");
	}
	return 0;
}
```

---

