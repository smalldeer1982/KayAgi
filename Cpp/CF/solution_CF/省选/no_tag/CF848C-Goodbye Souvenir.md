# Goodbye Souvenir

## 题目描述

给定长度为 $n$ 的数组，定义数字 $X$ 在 $[l,r]$ 内的值为数字 $X$ 在 $[l,r]$ 内最后一次出现位置的下标减去第一次出现位置的下标。

给定 $m$ 次询问，每次询问有三个整数 $a, b, c$，询问规则如下：

当 $a = 1$ 时，将数组内第 $b$ 个元素更改为 $c$。

当 $a = 2$ 时，求区间 $[b, c]$ 所有数字的值的和。

## 样例 #1

### 输入

```
7 6
1 2 3 1 3 2 1
2 3 7
2 1 3
1 7 2
1 3 2
2 1 6
2 5 7
```

### 输出

```
5
0
7
1
```

## 样例 #2

### 输入

```
7 5
1 3 2 1 4 2 3
1 1 4
2 2 3
1 1 7
2 4 5
1 1 7
```

### 输出

```
0
0
```

# 题解

## 作者：E_huan (赞：16)

# 二维数点（带修）

今天很想写二维数点，这里从二维数点的角度思考。（什么鬼理由）

二维数点实际上就是解决矩形求和的问题，可能带修改，一般需要离线给询问排序。

### 前置：

二维数点（静态）：[二维数点板子](https://www.luogu.com.cn/problem/P2163)

给询问排序，这样就可以数据结构维护一维，随着询问插入时间上作为一维。

### 本题可以转化成二维数点问题：（先不考虑修改）

首先，“最右和最左的差值”可以转化成“相邻的每一对同色的距离差的和”。

把和第 $i$ 个颜色相同且在它前面的离它最近的点的下标记为 $pre[i]$。

本题要求的式子可以写成：$ \sum\limits_{(l\le pre[i],i \le r)}{i-pre[i]}$

由于 $i>pre[i]$，这个限制可以简化成：$(pre[i] \ge l)$ 且 $(i \le r)$

把 $(pre[i],i)$ 看做一个点，在二维的矩阵上这个点的权值是 $i-pre[i]$ 即可转化成二维数点问题。查询就是查在横坐标区间为 $[l,r]$，纵坐标区间为 $[l,r]$ 的矩形中的权值和。

### 而本题需要修改。

修改会影响:

$1$.被修改位置的。

$2$.原本的颜色的后一个同色的位置。

$3$.新颜色的后一个同色的位置。

所以把修改拆成多个在二维平面上对点的修改，并采用 cdq 分治，来把动态修改转化成静态问题的时间维度。


### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=800010;
int n,m,cnt,v[N],pre[N];
set<int> s[N];
ll ans[N];
struct node
{
    int sign;//1/-1表示加入删除 0表示查询
    int l,r;//查询的两个限制 l,r 或者修改的点的两维坐标（权值是sign*(r-l))
    int id;//询问的编号 修改为0 
}q[N],tmp[N];//不用存时间，因为时间维度自然有序，后面也不会因为时间维度而排序
ll tr[N];
inline int lowbit(int x) {return x&(-x);}
inline void add(int x,ll v)
{
    for(;x<=n;x+=lowbit(x)) tr[x]+=v;
}
inline ll ask(int x)
{
    ll res=0;
    for(;x;x-=lowbit(x)) res+=tr[x];
    return res;
}
void cdq(int l,int r)//(pre[i]>=l) && (i<=r)
{
    if(l>=r) return;
    int mid=(l+r)>>1;
    cdq(l,mid); cdq(mid+1,r);
    int i=l,j=mid+1,k=0;
    while(i<=mid&&j<=r)//左边的天然满足t比右边小，所以右边到左边查询
        if(q[i].l>=q[j].l) 
        {
            if(q[i].sign) add(q[i].r,q[i].sign*(q[i].r-q[i].l));
            tmp[++k]=q[i],i++;
        }
        else{
            if(!q[j].sign) ans[q[j].id]+=ask(q[j].r);
            tmp[++k]=q[j],j++;
        }
    while(i<=mid)
    {
        if(q[i].sign) add(q[i].r,q[i].sign*(q[i].r-q[i].l));
        tmp[++k]=q[i],i++;
    }
    while(j<=r)
    {
        if(!q[j].sign) ans[q[j].id]+=ask(q[j].r);
        tmp[++k]=q[j],j++;
    }
    for(int i=l;i<=mid;i++) if(q[i].sign) add(q[i].r,-q[i].sign*(q[i].r-q[i].l));//消除影响
    for(int i=l,j=1;i<=r;i++,j++) q[i]=tmp[j];//按照l排好序了(从大到小排序)
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&v[i]); 
        if(s[v[i]].size())
        {
            auto pre=s[v[i]].end();
            q[++cnt]={1,(*(--pre)),i,0};
        }
        s[v[i]].insert(i);
    } 
    for(int i=1,a,b,c;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        if(a==1)
        {
            auto it=s[v[b]].find(b);//一定存在
            it++;
            if(it!=s[v[b]].end()) 
            {
                int u=(*it);    
                q[++cnt]={-1,b,u,0}; //后一个和我的连接
                it--;
                if(it!=s[v[b]].begin())
                    q[++cnt]={1,(*(--it)),u,0};//后一个和前一个的连接
            }//pre[*it]:从b变成b前面一个
            it=s[v[b]].find(b);
            if(it!=s[v[b]].begin())
                q[++cnt]={-1,(*(--it)),b,0};//我和前一个的连接
            s[v[b]].erase(b);
            
            v[b]=c;
            s[v[b]].insert(b);
            it=s[v[b]].find(b);
            if(it!=s[v[b]].begin())
                q[++cnt]={1,(*(--it)),b,0};
            it=s[v[b]].find(b); it++;
            if(it!=s[v[b]].end()) 
            {
                int u=(*it);
                q[++cnt]={1,b,u,0}; 
                it--;
                if(it!=s[v[b]].begin())
                    q[++cnt]={-1,(*(--it)),u,0};
            }   
            ans[i]=-1; //标记这个问题不需要回答
        }
        else q[++cnt]={0,b,c,i};
    }
    cdq(1,cnt);
    for(int i=1;i<=m;i++)
        if(ans[i]!=-1)
            printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：ff_666 (赞：15)

神仙CDQ分治%%%
-

~~刚听神仙讲完神仙的CDQ分治，顺便做了一道神仙例题~~

这题，$\sum i-last_{A_i}$ 显然不好求，考虑转化成

$\sum_{i=L}^{R} i-pre_{A_i}  [pre_{A_i}>=L]$

又由于$pre_{A_i}<=i$，那么答案也可以直接写成

$\sum_{i=1}^{R} i-pre_{A_i}  [pre_{A_i}>=L]$

即

$\sum i-pre_{A_i}  [i<=R][pre_{A_i}>=L]$

- $i<=R$　　　
- $pre_{A_i}>=L$　　
- 再加上操作的时间轴 $t$ 

没错，就是三维偏序，CDQ分治！！！

----
#### 具体操作
- 对于每个节点，就为$(t,i,pre_{A_i})$，权值为$i-pre_{A_i}$

- 修改的时候，删除只要把上次的抵消掉即可，即加入$(t,i,pre_{A_i})$，权值为$-(i-pre_{A_i})$，然后加入新节点就同上

- 对于每次询问，就为$(t,r,l)$

至于维护pre，用set即可，复杂度$O(N(log_2^N)^2)$

Code
--
```java
#include<bits/stdc++.h>
#define gt() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++)
#define pt(ch) (Top<1000000?St[Top++]=ch:(Out(),St[(Top=0)++]=ch))
#define Out() (fwrite(St,1,Top,stdout))
#define LL unsigned int
using namespace std;
int Top;static char St[1000000],buf[1000000],*p1=buf,*p2=buf;
const int maxn=(1e5)+5;
int N,M,T,Q,P[maxn],cnt;LL Ans[maxn],c[maxn];
set<int>S[maxn];
struct ff{
	int x,y,o,f;
	inline int val(){return (~f)?(x-y):(y-x);}
}A[maxn<<3],C[maxn<<3];
int Re(){
	int ret=0;char ch=gt();
	while(ch<'0'||ch>'9') ch=gt();
	while(ch>='0'&&ch<='9') ret=ret*10+(ch^'0'),ch=gt();
	return ret;
}
void Wri(LL x){if(x>9) Wri(x/10);pt(x%10+'0');}
void Add(int i,int x){while(i<=N) c[i]+=x,i+=i&-i;}
int Get(int i){int Res=0;while(i) Res+=c[i],i^=i&-i;return Res;}
void Merge(int L,int mid,int R){
	for(int k=L,i=L,j=mid+1;k<=R;k++) C[k]=(j>R||(i<=mid&&A[i].x<=A[j].x))?A[i++]:A[j++];
	for(int k=L;k<=R;k++) A[k]=C[k];
}
void Solve(int L,int R){
	if(L>=R) return;
	int mid=L+R>>1,i,j;Solve(L,mid),Solve(mid+1,R);
	for(i=mid+1,j=L;i<=R;i++)if(A[i].o){
		while(j<=mid&&A[j].x<=A[i].x){if(!A[j].o) Add(A[j].y,A[j].val());j++;}
		Ans[A[i].o]+=Get(N)-Get(A[i].y-1);
	}
	for(i=L;i<j;i++) if(!A[i].o) Add(A[i].y,-A[i].val());
	Merge(L,mid,R);
}
int main(){
	#ifdef hhh
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	#endif
	N=Re(),Q=Re();
	for(int i=1;i<=N;i++){
		S[P[i]=Re()].insert(i);
		if(S[P[i]].size()>1) 
		A[++M]=(ff){i,*(--S[P[i]].rbegin()),0,1}; 
	}
	while(Q--){
		int opt=Re(),x=Re(),y=Re();++T;
		if(opt==2){A[++M]=(ff){y,x,++cnt,0};continue;}
		
		auto i=S[P[x]].find(x);int L=0,R=0;
		if(i!=S[P[x]].begin()) A[++M]=(ff){x,L=*--i,0,-1},i++;
		if(++i!=S[P[x]].end()) A[++M]=(ff){R=*i,x,0,-1};
		if(L&&R) A[++M]=(ff){R,L,0,1};
		S[P[x]].erase(x);//Del
		
		S[P[x]=y].insert(x),i=S[y].find(x),L=R=0;
		if(i!=S[y].begin()) A[++M]=(ff){x,L=*--i,0,1},i++;
		if(++i!=S[y].end()) A[++M]=(ff){R=*i,x,0,1};
		if(L&&R) A[++M]=(ff){R,L,0,-1};//Insert
	}
	Solve(1,M);
	for(int i=1;i<=cnt;i++) Wri(Ans[i]),pt('\n');
    return Out(),0;
}
```


---

## 作者：p_b_p_b (赞：13)

[$$\large \color{purple} My\;Blog$$](https://www.cnblogs.com/p-b-p-b/p/10360662.html)

-----------

我这题共写了四种做法，其中两种可以通过。感兴趣的可以去博客里面看，这里仅给出正解。

----------

## 思路

考虑最后的减去开始的等价于每一位减去前面的。

即位置$x$对$[l,r]$的贡献是$x-pre_x,pre_x\geq l$。

那么题目转化为二维数点：一维是位置$x$，一维是前驱$pre_x$，权值是$x-pre_x$。

当$pre_x$发生改变时消除原来的贡献，并加上新的。

询问可以变为查询以$(l,l)$为左下角，$(r,n)$为右上角的矩形之和。按照时间CDQ分治，每次算左边的点对右边的矩形的贡献。

然而这个矩形不好看，似乎还要差分？

其实并不用。考虑$x>pre_x$，所以直线$y=x$上方是没有点的，可以把查询变成以$(1,l)$为左下角，$(r,n)$为右上角的矩形。这样可以扫描线+树状数组了。

时间复杂度应该是$O(n\log^2 n)$。

---------

## 代码

```cpp
#include<bits/stdc++.h>
namespace my_std{
	using namespace std;
	#define pii pair<int,int>
	#define fir first
	#define sec second
	#define MP make_pair
	#define rep(i,x,y) for (int i=(x);i<=(y);i++)
	#define drep(i,x,y) for (int i=(x);i>=(y);i--)
	#define go(x) for (int i=head[x];i;i=edge[i].nxt)
	#define sz 101010
	typedef long long ll;
	template<typename T>
	inline void read(T& t)
	{
		t=0;char f=0,ch=getchar();
		double d=0.1;
		while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
		while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
		if(ch=='.')
		{
			ch=getchar();
			while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();
		}
		t=(f?-t:t);
	}
	template<typename T,typename... Args>
	inline void read(T& t,Args&... args){read(t); read(args...);}
	void file()
	{
		#ifndef ONLINE_JUDGE
		freopen("a.txt","r",stdin);
		#endif
	}
//	inline ll mul(ll a,ll b){ll d=(ll)(a*(double)b/mod+0.5);ll ret=a*b-d*mod;if (ret<0) ret+=mod;return ret;}
}
using namespace my_std;

int n,m,Q;
int a[sz];
int pre[sz],nxt[sz];
set<int>s[sz];

int calcPre(int x,int col){set<int>::iterator it=s[col].lower_bound(x);--it;return *it;}
int calcNxt(int x,int col){return *(s[col].upper_bound(x));}

ll ans[sz];
struct hh
{
	int type; // 0:modify 1:query
	int x,y,val;
	int id;
}q[sz*6];
inline bool cmp(const hh &x,const hh &y)
{
	if (x.type!=y.type) return x.type<y.type;
	if (x.type) return x.y<y.y;
	return x.x<y.x;
}
inline void calc(int x,int v) // pre[x]->v
{
	q[++m]=(hh){0,x,pre[x],pre[x]-x,0};
	pre[x]=v;
	q[++m]=(hh){0,x,v,x-v,0};
}

ll sum[sz];
void add(int x,ll v){ if (!x) return; while (x<=n) sum[x]+=v,x+=(x&(-x)); }
ll query(int x){ ll ret=0; while (x) ret+=sum[x],x-=(x&(-x)); return ret; }

void solve(int l,int r)
{
	if (l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid);solve(mid+1,r);
	int p=l-1;
	rep(i,mid+1,r) if (q[i].type)
	{
		while (p<mid&&(q[p+1].type||q[p+1].x<=q[i].y))
		{
			++p;
			if (!q[p].type) add(q[p].y,q[p].val);
		}
		ans[q[i].id]+=query(n)-query(q[i].x-1);
	}
	rep(i,l,p) if (!q[i].type) add(q[i].y,-q[i].val);
	sort(q+l,q+r+1,cmp);
}

int main()
{
	file();
	int x,y,z;
	read(n,Q);
	rep(i,1,n) s[i].insert(0),s[i].insert(n+1);
	rep(i,1,n) read(a[i]),s[a[i]].insert(i);
	rep(i,1,n) pre[i]=calcPre(i,a[i]),nxt[i]=calcNxt(i,a[i]),q[++m]=(hh){0,i,pre[i],i-pre[i],0};
	int c=0;
	while (Q--)
	{
		read(z,x,y);
		if (z==1)
		{
			if (y==a[x]) continue;
			int Pre=calcPre(x,y),Nxt=calcNxt(x,y);
			s[a[x]].erase(x);s[y].insert(x);
			a[x]=y;
			if (nxt[x]!=n+1) calc(nxt[x],pre[x]);
			if (pre[x]!=0) nxt[pre[x]]=nxt[x];
			if (Pre!=0) nxt[Pre]=x;
			if (Nxt!=n+1) calc(Nxt,x);
			calc(x,Pre);
			nxt[x]=Nxt;
		}
		else ++c,q[++m]=(hh){1,x,y,0,c};
	}
	solve(1,m);
	rep(i,1,c) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Katyusha_01 (赞：11)

### 这是一篇姿势手法题解

众所周知，只要内存访问连续，不使用除法、模法、分支结构，$1s$ 跑 $2e9$ 根本不是事儿。

这道题显然没有除法和模法，那么我们只需要做到内存访问连续以及去掉分支结构就行了，分支结构可以使用乘一个布尔值代替；要想使内存访问连续，就对于每个位置 $i$ 维护出 $a_i$ 上一次出现的位置 $lp_i$，答案就是 $\sum_{i=l}^{r} (l \le lp_i) \times (i - lp_i)$。

这样就能轻松跑进三秒，[提交记录](https://codeforces.com/contest/848/submission/301703195)

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(3)
using namespace std;
int n,m;
set<int> s[100011];
int a[100011];
unsigned int lp[100011];
int Mx(int x)
{
	if(s[x].empty()) return 0;
	auto p = s[x].end();
	return *(--p);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
		cin >> a[i],lp[i] = Mx(a[i]),s[a[i]].insert(i);
	while(m--)
	{
		int op;
		cin >> op;
		if(op == 1)
		{
			int p,x;
			cin >> p >> x;
			auto r = s[a[p]].upper_bound(p);
			if(r != s[a[p]].end())
				lp[*r] = lp[p];
			s[a[p]].erase(p);
			r = s[x].upper_bound(p);
			if(r != s[x].end())
				lp[*r] = p;
			auto l = r;
			if(l != s[x].begin())
				l--,lp[p] = *l;
			else
				lp[p] = 0;
			s[a[p] = x].insert(p);
		}else{
			int l,r;
			cin >> l >> r;
			unsigned int ans = 0;
			for(int i = l + 1;i <= r;i++)
				ans += (l <= lp[i]) * (i - lp[i]);
			cout << ans << "\n";
		}
	}
	return 0;
}
```

---

## 作者：yzy1 (赞：6)

题解区好像都是 polylog 的解法，我来发一个 $O(n^{\frac 5 3}\log n)$ 的解法。

## 题目大意

设 $F(i,l,r)$ 为值 $i$ 在区间 $[l,r]$ 内最后一次出现的下标减第一次出现的下标。

- `1 x y`：单点修改 $a_x \gets y$。
- `2 l r`：求 $\sum_{i=1}^n F(i,l,r)$。

## 做法 1（TLE）

考虑带修莫队。对于每个不同的颜色，开一个 `set` 维护该颜色出现的下标。则颜色 $i$ 对答案的贡献就为 `*st[i].rbegin()-*st[i].begin()`。按照一般带修莫队的套路维护即可。

每移动一次端点是 $O(\log n)$ 的，故时间复杂度为 $O(n^{\frac 5 3}\log n)$，常数较大。加上奇偶优化后本机 $n=10^5$ 随机数据大概 $5.8$ 秒。

```cpp
void Add(int x) {
  if (st[a[x]].size()) res -= *st[a[x]].rbegin() - *st[a[x]].begin();
  st[a[x]].insert(x);
  res += *st[a[x]].rbegin() - *st[a[x]].begin();
}
void Del(int x) {
  res -= *st[a[x]].rbegin() - *st[a[x]].begin();
  st[a[x]].erase(x);
  if (st[a[x]].size()) res += *st[a[x]].rbegin() - *st[a[x]].begin();
}
void AddT(int x, int l, int r) {
  if (l <= q1[x].x && q1[x].x <= r) Del(q1[x].x);
  a[q1[x].x] = q1[x].y;
  if (l <= q1[x].x && q1[x].x <= r) Add(q1[x].x);
}
void DelT(int x, int l, int r) {
  if (l <= q1[x].x && q1[x].x <= r) Del(q1[x].x);
  a[q1[x].x] = q1[x].lst;
  if (l <= q1[x].x && q1[x].x <= r) Add(q1[x].x);
}

signed main() {
  in(n)(msum)(a_, n), sz = pow(n, 2.0 / 3);
  re (i, n)
    a[i] = a_[i];
  int cnt1 = 0;
  re (i, msum) {
    int op = in(), x = in(), y = in();
    if (op == 1) {
      q1[++cnt1] = {x, y, a[x]};
      a[x] = y;
    } else {
      ++m2;
      q2[m2] = {x, y, cnt1, m2};
    }
  }
  re (i, n)
    a[i] = a_[i];
  sort(q2 + 1, q2 + m2 + 1);
  int l = 1, r = 0, t = 0;
  re (i, m2) {
    while (t < q2[i].t) AddT(++t, l, r);
    while (t > q2[i].t) DelT(t--, l, r);
    while (l > q2[i].l) Add(--l);
    while (r < q2[i].r) Add(++r);
    while (l < q2[i].l) Del(l++);
    while (r > q2[i].r) Del(r--);
    ans[q2[i].id] = res;
  }
  re (i, m2)
    out(ans[i])('\n');
  return 0;
}
```

## 做法 2（AC）

我们发现做法 1 中的平衡树常数巨大，考虑换一种维护方式。

我们发现每种颜色最后一次出现和第一次出现之间的差值等于相邻出现次数对之间差值的总和。也就是说，我们可以维护每个前缀对答案造成的贡献。每加入一个下标为 $x$ 的数，则对答案的贡献为 $x-pre(x)$，其中 $pre(x)$ 代表 $x$ 的相同颜色前缀。我们可以用树状数组很方便的维护这个东西。

时间复杂度还是 $O(n^{\frac 5 3}\log n)$，但是这个 $\log$ 是树状数组的 $\log$，常数比平衡树小得多。本地随机数据 $n=10^5$ 只用了不到两秒就跑完了。

```cpp
void Add(int x) {
  if (pre[x]) bit.Add(pre[x], x - pre[x]);
}
void Del(int x) {
  if (pre[x]) bit.Add(pre[x], pre[x] - x);
}
void AddT(int x, int l, int r) {
  if (l <= q1[x].x && q1[x].x <= r) Del(q1[x].x);
  pre[q1[x].x] = q1[x].y;
  if (l <= q1[x].x && q1[x].x <= r) Add(q1[x].x);
}
void DelT(int x, int l, int r) {
  if (l <= q1[x].x && q1[x].x <= r) Del(q1[x].x);
  pre[q1[x].x] = q1[x].lst;
  if (l <= q1[x].x && q1[x].x <= r) Add(q1[x].x);
}

signed main() {
  in(n)(msum)(a, n), sz = pow(n, 2.0 / 3);
  int m1 = 0;
  re (i, n)
    st[i].insert(0), st[i].insert(n + 1), st[a[i]].insert(i);
  re (i, n)
    pre_[i] = pre[i] = *prev(st[a[i]].lower_bound(i)), suf[i] = *st[a[i]].upper_bound(i);
  re (i, msum) {
    int op = in(), x = in(), y = in();
    if (op == 1) {
      if (y == a[x]) continue;
      int p = *prev(st[y].lower_bound(x)), s = *st[y].upper_bound(x);
      st[a[x]].erase(x), a[x] = y, st[a[x]].insert(x);
      if (suf[x] != n + 1) pre[suf[x]] = pre[x], q1[++m1] = {suf[x], pre[suf[x]], x};
      if (pre[x]) suf[pre[x]] = suf[x];
      if (p) suf[p] = x;
      if (s != n + 1) q1[++m1] = {s, x, pre[s]}, pre[s] = x;
      q1[++m1] = {x, p, pre[x]};
      pre[x] = p, suf[x] = s;
    } else
      ++m2, q2[m2] = {x, y, m1, m2};
  }
  re (i, n)
    pre[i] = pre_[i];
  sort(q2 + 1, q2 + m2 + 1);
  int l = 1, r = 0, t = 0;
  re (i, m2) {
    while (t < q2[i].t) AddT(++t, l, r);
    while (t > q2[i].t) DelT(t--, l, r);
    while (l > q2[i].l) Add(--l);
    while (r < q2[i].r) Add(++r);
    while (l < q2[i].l) Del(l++);
    while (r > q2[i].r) Del(r--);
    ll res = bit.Ask(n) - bit.Ask(l - 1);
    ans[q2[i].id] = res;
  }
  re (i, m2)
    out(ans[i])('\n');
  return 0;
}
```



---

## 作者：intel_core (赞：4)

来一个 $O(n\sqrt{n \log n})$ 的在线做法。

如果要求的序列是 $a_1,a_2,\cdots,a_m$，那么答案为 $\sum\limits_{i=1}^n[pre_i\ge 1](i-pre_i)$，这里 $pre_i$ 表示最大的下标 $k$ 使得 $k<i$ 且 $a_i=a_k$。

放到一个区间 $[l,r]$ 中，求和式变为 $\sum\limits_{i=l}^r[pre_i\ge l](i-pre_i)$。

观察到求和式有两个限制条件 $pre_i\ge l$ 和 $i\in [l,r]$。

这不就裸的树套树吗？

然鹅你发现这题空间 $\text{256MB}$，所有树套树都寄了。

或者可以用 $\text{CDQ}$ 分治， $\text{KD-Tree}$ ，或者用一些神奇的办法突破空间限制。

这里直接无脑分块，整块开对 $pre$ 数组开线段树，散点直接暴力。

如果块长为 $B$ ，那么单次复杂度 $O(\frac{n}{B}\log n+B)$ , 当 $B=\sqrt{n \log n}$ 时复杂度达到最优。

所以复杂度 $O(n \sqrt{n \log n})$，可以在 $\text{1s}$ 内完成。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int NR=1e5+10;
const int MR=2e3+10;
int n,q,a[NR],pre[NR];
int Block,from[NR],l[MR],r[MR],rt[MR];
set<int>s[NR];

int tot,ch[NR<<5][2],sum[NR<<5];
#define mid ((l+r)>>1)
void change(int &id,int l,int r,int pos,int k){
	if(!id)id=++tot;
	sum[id]+=k;
	if(l==r)return;
	if(pos<=mid)change(ch[id][0],l,mid,pos,k);
	else change(ch[id][1],mid+1,r,pos,k);
}
int query(int id,int l,int r,int L,int R){
	if(!id)return 0;
	if(r<L||R<l)return 0;
	if(L<=l&&r<=R)return sum[id];
	return query(ch[id][0],l,mid,L,R)+query(ch[id][1],mid+1,r,L,R);
}

void init(){
	Block=max(1ll,(int)sqrt(n*log(n)/log(2)));
	for(int i=1;i<=n;i++)from[i]=(i-1)/Block+1;
	for(int i=1;i<=n;i++){
		if(from[i]!=from[i-1])l[from[i]]=i;
		if(from[i]!=from[i+1])r[from[i]]=i;
		if(pre[i])change(rt[from[i]],1,n,pre[i],i-pre[i]);
	}
}
void modify(int x,int y){
	set<int>::iterator it1=s[a[x]].upper_bound(x),it2;
	if(it1!=s[a[x]].end()){
		int k=*it1;
		change(rt[from[k]],1,n,x,x-k);
		if(pre[x])change(rt[from[k]],1,n,pre[x],k-pre[x]);
		pre[k]=pre[x];
	}
	s[a[x]].erase(x);a[x]=y;
	if(pre[x])change(rt[from[x]],1,n,pre[x],pre[x]-x);
	it2=s[y].upper_bound(x);
	if(s[y].empty())pre[x]=0;
	else if(!s[y].empty()&&it2==s[y].begin()){
		int k=*it2;pre[k]=x;pre[x]=0;
		change(rt[from[k]],1,n,x,k-x);
	}
	else{
		it1=it2;it1--;
		int k1=*it1;pre[x]=k1;
		change(rt[from[x]],1,n,k1,x-k1);
		if(it2!=s[y].end()){
			int k2=*it2;pre[k2]=x;
			change(rt[from[k2]],1,n,k1,k1-k2);
			change(rt[from[k2]],1,n,x,k2-x);
		}
	}
	s[y].insert(x);
}
int calc(int L,int R){
	int res=0;
	if(from[L]==from[R]){
		for(int i=L;i<=R;i++)
			if(pre[i]>=L)res+=i-pre[i];
		return res;
	}
	for(int i=from[L]+1;i<from[R];i++)res+=query(rt[i],1,n,L,R);
	for(int i=L;i<=r[from[L]];i++)
		if(pre[i]>=L)res+=i-pre[i];
	for(int i=l[from[R]];i<=R;i++)
		if(pre[i]>=L)res+=i-pre[i];
	return res;
}

signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(!s[a[i]].empty()){
			set<int>::iterator it=s[a[i]].end();
			pre[i]=*(--it);
		}
		s[a[i]].insert(i);
	}
	init();
	while(q--){
		int opt,x,y;scanf("%lld%lld%lld",&opt,&x,&y);
		if(opt==1)modify(x,y);
		else printf("%lld\n",calc(x,y));
	}
	return 0;
} 
```

---

## 作者：xfrvq (赞：4)

[$\tt Link$](/problem/CF848C)

## 前言

题解清一色的 $\tt CDQ$，树套树，但是有个 $\mathcal O(n^{\frac 53}\log n)$ 是什么鬼？

这是一个分块做法，复杂度 $\mathcal O(n\sqrt n)$，但是非常阴间，建议谨慎尝试。

如果你真心想写这个做法，建议写完这题就去写 [$\tt rdiq$](/problem/P7448)，[$\tt rcn$](/problem/P7721)。

## 转化

考虑记下每个位置前一个与它颜色相同的位置 $P_i$。

那么我们可以把这个贡献从每种颜色转化到每个位置。

方法是定义每个位置的贡献为 $i-P_i$，当然要 $P_i\ge$ 询问左端点。

假如一个颜色所有出现的位置为 $b_1,\cdots,b_k$，那么总贡献为：

$$
\begin{aligned}
Sum&=(b_k-P_{b_k})+\cdots+(b_2-P_{b_2})\\
&=(b_k-b_{k-1})+\cdots+(b_2-b_1)\\
&=b_k-b_1
\end{aligned}
$$

可以看出最后就是我们想求的。

转化完后，我们把这个问题换成一个二维数点的形式，即有 $n$ 个点 $(i,P_i)$，其权值为 $i-P_i$。询问就相当于求 $[l,r][l,n]$ 这一段的和。

**关于点的性质：所有点的 $x$ 坐标互不相同，$y$ 坐标除了可能有多个 $0$ 之外，互不相同.**

## 修改操作

很平凡。你维护每个点出现位置的 `set`，然后就可以 $O(\log n)$ 计算每个位置的上一个/下一个颜色相同位置。

## 二维分块

这个题用这玩意确实大材小用了，但是还是想说说。

**注意：下面介绍的是一种 $O(\sqrt n)$ 前缀矩形加 $O(1)$ 单点查询的数据结构。转化一下可以得到适合原问题的单点加矩形查**

举个例子，假设我们要加的是这么一个矩形（左下角是原点，右上角是询问点）。

![](https://cdn.luogu.com.cn/upload/image_hosting/76po4cy3.png)

为了方便，以下记 $\mathbf a=n^{0.25},\mathbf b=n^{0.5},\mathbf c=n^{0.75}$。

首先因为整块复杂度要保证，所以块数是 $O(\sqrt n)$ 的，于是你就应该用 $\bf c\times c$ 来分块，这样总块数就是 $O(\mathbf{a\times a}=\sqrt n)$ 的。

![](https://cdn.luogu.com.cn/upload/image_hosting/04pkufgz.png)

但是我们整块复杂度保证，散块又不行了。于是考虑在现在的灰色部分分块用来辅助原来的散块，分出

+ $\bf a\times b$ 个 $\bf c\times b$ 的块
+ $\bf b\times a$ 个 $\bf b\times c$ 的块
+ $\bf b\times b$ 个 $\bf b\times b$ 的块

![](https://cdn.luogu.com.cn/upload/image_hosting/d5tnp5jb.png)

现在总共分了 $4$ 种块，对于每种块我们都维护块和。

现在来算一下复杂度。

+ 对于红色块而言，它一定不超过 $\sqrt n$ 个。
+ 对于橙色块而言，它一行最多只有 $n\div\mathbf c=n^{0.25}$ 个，一列最多只有 $\mathbf{c\div b}=n^{0.25}$ 个，乘起来不超过 $\sqrt n$ 个。
+ 对于蓝色块而言，它一行最多只有 $\mathbf{c\div b}=n^{0.25}$ 个，一列最多只有 $n\div\mathbf c=n^{0.25}$ 个，乘起来不超过 $\sqrt n$ 个。
+ 对于绿色块而言，它一行/一列最多只有 $\mathbf{c\div b}=n^{0.25}$ 个，乘起来也不超过 $\sqrt n$ 个。
+ 散块需要结合这题的特殊性质才可做，这里不作讨论，下面讲。

那散块如何做呢？

首先，散块本身的定义是：**一个询问覆盖了一个点但没有完全覆盖这个点所在的 $\bf b\times b$ 块**，就是上图中的黄色部分。

上文所说的性质，就是说 $x,y$ 坐标都互不相同（如果 $y=0$，这时我们再写一个一维分块做就好了。）

**基于性质**，我们把散块拆分为三部分。

![](https://cdn.luogu.com.cn/upload/image_hosting/ntxsmopv.png)

对于紫色部分，枚举紫色范围内 $x$ 坐标，然后查看 $y$ 坐标是否也在紫色范围内，如果是就加上贡献。

对于粉色部分，枚举粉色范围内 $y$ 坐标，然后查看 $x$ 坐标是否也在粉色范围内，如果是就加上贡献。

你可以在紫色部分的时候算上蓝色部分，也可以在粉色部分的时候算上蓝色部分，不要算重就行了。

## Code

```cpp
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<set>

#define rep(i,a,b) for(int i = (a);i <= (b);++i)
#define Rep(i,a,b) for(int i = (a);i >= (b);--i)
#define clr(M) memset(M,0,sizeof M)

const int N = 1e5 + 5;

typedef long long ll;

int n,m,a[N],p[N],q[N];

namespace blk2d{
	const int B1 = 18,B2 = 324,B3 = 5832;
	const int S1 = 25,S2 = 330,S3 = 5840;
	
	int st2[S2],bl2[N],st3[S1],bl3[N]; ll c0[N],s0[S2];
	ll c1[S1][S1],c2[S2][S1],c3[S1][S2],c4[S2][S2],c5[N],c6[N];
	
	#define F1(i,z) rep(i,1,bl3[z] - 1)
	#define F2(i,z) rep(i,st3[bl3[z]],bl2[z] - 1)
	#define F3(i,z) rep(i,st2[bl2[z]],z)
	#define bl(i,t) (i - 1) / t + 1
	
	void init(){
		rep(i,1,n) bl2[i] = bl(i,B2),bl3[i] = bl(i,B3);
		Rep(i,n,1) st2[bl2[i]] = i,st3[bl3[i]] = bl2[i];
	}
	
	void upd(int x,int y,ll t){
		p[x] = y; q[y] = x;
		if(y == 0) return c0[x] += t,void(s0[bl2[x]] += t);
		int a = bl3[x],b = bl2[x],c = bl3[y],d = bl2[y];
		c1[a][c] += t; c2[b][c] += t; c3[a][d] += t; c4[b][d] += t;
		c5[x] += t; c6[y] += t;
	}
	
	ll qry(int x,int y){
		ll sum = 0;
		F1(i,x) F1(j,y) sum += c1[i][j];
		F2(i,x) F1(j,y) sum += c2[i][j];
		F1(i,x) F2(j,y) sum += c3[i][j];
		F2(i,x) F2(j,y) sum += c4[i][j];
		F3(i,x) if(p[i] <= y) sum += c5[i];
		F3(i,y) if(q[i] < st2[bl2[x]]) sum += c6[i];
		rep(i,1,bl2[x] - 1) sum += s0[i];
		rep(i,st2[bl2[x]],x) sum += c0[i];
		return sum;
	}
}

using namespace blk2d;

std::set<int> P[N];

int pre(int x){
	auto i = P[a[x]].lower_bound(x);
	return i == begin(P[a[x]]) ? 0 : *--i;
}

int nxt(int x){
	auto i = P[a[x]].upper_bound(x);
	return i == end(P[a[x]]) ? 0 : *i;
}

void cpre(int u){
	if(!u) return;
	int v = pre(u);
	upd(u,p[u],p[u] - u);
	upd(u,v,u - v);
}

int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",a + i),P[a[i]].insert(i);
	init();
	rep(u,1,n) p[u] = pre(u),upd(u,p[u],u - p[u]);
	while(m--){
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		if(op == 1){
			int w = nxt(x);
			P[a[x]].erase(x); P[a[x] = y].insert(x);
			cpre(x); cpre(w); int v = nxt(x); cpre(v);
			q[p[x]] = x; q[p[w]] = w; q[p[v]] = v;
		} else printf("%lld\n",qry(y,n) - qry(y,x - 1) - qry(x - 1,n) + qry(x - 1,x - 1));
	}
	return 0;
}
```

---

## 作者：mulberror (赞：4)

## 题目大意
两种操作   
$1 \ l \ r$表示将$l$位置上的颜色变成$r$     
$2 \ l \ r$表示查询区间$[l,r]$中权值和。    
**权值的定义：区间内最后一次出现颜色$x$的下标减去第一次出现颜色$x$位置的下标**   
## 题解
神仙题一道。    
话说为什么一大堆人都是写cdq分治，虽然我也会一点点，但是就是写不出来。  
我写了树状数组套线段树。（其实本质差不多，只是代码量树套树常规比cdq分治代码长，而且容易调qwq）。
先讲一下cdq分治怎么做。
这题一维难以维护的地方是，一个点的权值可能是和不在查询区间的点产生的。   
于是有把一维问题转换成二维问题的想法，一个点的横坐标就是这个点的位置，纵坐标是这个点前一个与它颜色相同的点的位置，权值是横坐标减纵坐标。   
这样查询$[l,r]$区间的答案，就是二维平面上，$(l,l)$点和$(r,r)$点组成的矩阵内的权值之和。
考虑没有修改的情况，矩阵求和是一个经典问题，一次扫描线就可以求出答案了，现在有了修改操作，所以利用cdq分治，把动态问题变静态，而后再用扫描线求答案。 
cdq分治的过程中，考虑左右子问题的答案都已经求出，现在要考虑左子问题的修改操作对右子问题的查询操作的影响。  
把左边的修改操作和右边的查询操作放在一起，进行扫描线即可。
然后我们来讲一下如何用树套树水过这一题目。
其实可以用树状数组当做第一维，线段树维护第二维，直接模拟平面上的矩阵。
每次需要修改就用$set$来水一下。暴力乱搞大法吼呀！
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IOstream {
	#define gc getchar
	template <typename T>
	inline void read(T &x) {
		x = 0; T fl = 1; char c = 0;
		for (; c < '0' || c > '9'; c = gc())
			if (c == '-') fl = -1;
		for (; c >= '0' && c <= '9'; c = gc())
			x = (x << 1) + (x << 3) + (c ^ 48);
		x *= fl;
	}
	#undef gc
} using namespace IOstream;

typedef long long ll;
typedef set<int>::iterator sit;
const int N = 100000 + 6;
set<int> st[N];
int n, m;
int rt[N], a[N], fst[N];

namespace seg {
	#define ls(x) tr[x].lc
	#define rs(x) tr[x].rc
	int ntot = 0; 
	struct node {
		int lc, rc;
		ll s; 
		node() { lc = rc = s = 0; }
	} tr[N * 120];
	void upd(int &nod, int l, int r, int k, ll val) {
		if (!nod) nod = ++ ntot;
		tr[nod].s += val; 
		if (l == r) return; 
		int mid = (l + r) >> 1;
		if (k <= mid) upd(ls(nod), l, mid, k, val);
		else upd(rs(nod), mid + 1, r, k, val);
	}
	ll query(int nod, int l, int r, int k) {
		if (!nod) return 0;
		if (l == r) return tr[nod].s;
		int mid = (l + r) >> 1;
		if (k <= mid) return query(ls(nod), l, mid, k) + tr[rs(nod)].s;
		else return query(rs(nod), mid + 1, r, k);
	}
	#undef ls
	#undef rs
}

namespace BIT_TREE {
	#define lowbit(x) (x & -x) 
	void add(int k, int q, ll val, int n) {
		for (int i = k; i <= n; i += lowbit(i)) seg::upd(rt[i], 1, n, q, val);
	}
	ll sum(int k, int q, int n) {
		ll res = 0ll;
		for (int i = q; i; i -= lowbit(i)) res += seg::query(rt[i], 1, n, k);
		return res; 
	}
	#undef lowbit
}

sit lst(sit it) {
	return -- it;
}
sit nxt(sit it) {
	return ++ it;
}
void upd(int x, int y, int n){
	if(fst[x]) BIT_TREE::add(x, fst[x], fst[x] - x, n);
	if(y) BIT_TREE::add(x, y, x - y, n);
	fst[x] = y;
}
int main() {
	read(n); read(m);
	for (int i = 1; i <= n; i ++) read(a[i]);
	for (int i = 1; i <= n; i ++) {
		if (st[a[i]].size()) { // if set isn't empty
			fst[i] = *st[a[i]].rbegin(); 
			BIT_TREE::add(i, fst[i], i - fst[i], n);
		}
		st[a[i]].insert(i);
	}
	while (m --) {
		int opt, x, y;
		read(opt); read(x); read(y); 
		if (opt == 1) { //  operation of upd
			sit it = st[a[x]].find(x);
			if (nxt(it) != st[a[x]].end()) 
				upd(*nxt(it), (it == st[a[x]].begin() ? 0 : *lst(it)), n);
			st[a[x]].erase(x);
			a[x] = y; 
			it=st[y].insert(x).first;
			upd(x, (it == st[y].begin() ? 0 : *lst(it)), n);
			if(nxt(it) != st[y].end())
				upd(*nxt(it), x, n);
		} else { // operation of query ans
			printf("%lld\n", BIT_TREE::sum(x, y, n));
		}
	}
	return 0;
}
```

---

## 作者：_Arahc_ (赞：3)

还没有 KDTree 的题解？

~~那这一波叫趁虚而入~~。

## 题目定位

KDT、CDQ、树套树……任何可以数点的做法都可以做，再加上平衡树维护一个颜色上次和下次出现位置。

[题目地址](https://codeforces.com/contest/848/problem/C)，大意如下：

> 给定一个长度为 $n$ 的数组，多组操作，每组操作为修改一个数的值，或者查询区间内所有数的权值和。
>
> 一个数的权值，定义为其在区间中第一次出现和最后一次出现的下标的差，相同的数字权值只计算一次。
>
> $n,q,a_i\leqslant 10^5$

## 题目分析

询问和数值大小无关，把填数看成染色。设一段查询区间内，某个颜色出现的位置分别为 $i_1,i_2,i_3,\cdots,i_m$。

根据定义，这个颜色产生的贡献是 $i_m-i_1$。这就让中间的一堆数没有参与贡献计算，不方便维护，这不好。但是我们发现：
$$
(i_2-i_1)+(i_3-i_2)+(i_4-i_3)+\cdots+(i_m-i_{m-1})=i_m-i_1
$$
因此对于每一个颜色，设其位于位置 $i$，则找到其上一次出现的位置（若不存在，则为 $0$）$pre_i$。题目转化为：给定区间 $[l,r]$，求 $\sum i-pre_i$，其中 $l\leqslant pre_i<i\leqslant r$。

我们将一个位置扩展成一个二维平面上的点，设其位置为 $i$，则以 $i$ 为横坐标，$pre_i$ 为纵坐标。那么符合条件的点就位于左下角为 $(l,l)$，右上角为 $(r,r)$ 的矩形内。不妨再给每个点赋予一个权值 $i-pre_i$，询问就转化为查询矩阵内点权和。就是经典的数点问题了。

需要注意的是单点修改会产生什么影响，设位置 $i$ 的颜色从 $a$ 被修改为 $b$。从 $a$ 颜色看，这个点被删除了，随之影响了它右边的第一个颜色为 $a$ 的点的 $pre$ 改变了。从 $b$ 颜色看，新增了一个点，随之影响的也是它右边第一个颜色为 $b$ 的点的 $pre$。

开 $n$ 个 ```set``` 维护每一个颜色的位置，就可以快速查询与修改下标 $i$ 的前驱后继。数点用 KDTree 维护即可。

还补充一个简单小 Trick，KDTree 写删除的确有些烦人，但是因为我们要查询的是点权和，因此不妨直接在原位置上加一个点，权值为原来的相反数就行了；修改一个点权等价于删除这个点再加一个点。如果怕加入的点过多导致爆炸，就写一个特判，如果两个点位置相同就合并权值。

## 代码

KDT 本来就够卡了，```#define int long long``` 会 T 飞，注意一下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int max_n=600005; // 非常保守的数组大小
inline int read(){
    int x=0;bool w=0;char c=getchar();
    while(c<'0' || c>'9') w|=c=='-',c=getchar();
    while(c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return w?-x:x;
}
inline void write(ll x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10^48);
}
inline bool interv(int mid,int l,int r){ // 判断 mid 在不在 [l,r] 内
    if(l<=mid && mid<=r) return 1;
    return 0;
}

int n,m,a[max_n],pre[max_n],nxt[max_n];

// ---------------KDT板子---------------

struct point{
    int x,y,val;
    point(){x=y=val=0;}
    bool operator == (const point &b) const{
        point a=*this;
        return (a.x==b.x && a.y==b.y);
    }
}pos[max_n];
inline point makep(int a,int b,int c){ // make point
    point res;
    res.x=a,res.y=b,res.val=c;
    return res;
}
bool cmpt=0;
inline bool cmp(point i,point j){
    if(cmpt) return i.x<j.x;
    return i.y<j.y;
}
int fre[max_n],tp;
struct KD_Tree{
    const double alpha=0.75;
    int root,tot,tmp;
    bool chgr;
    KD_Tree(){root=tot=tmp=0;}
    inline int newnode(){
        int x;
        if(tp) x=fre[tp--];
        else x=++tot;
        return x;
    }
    struct dot{
        point x,l,r;
        int tp,sz,ls,rs;ll sm;
        dot(){tp=sz=ls=rs=sm=0;}
    }a[max_n];
    #define ls(x) (a[x].ls)
    #define rs(x) (a[x].rs)
    inline void pushup(int x){
        a[x].l=a[x].r=a[x].x,a[x].sm=a[x].x.val;
        a[x].sz=a[ls(x)].sz+a[rs(x)].sz+1;
        if(ls(x)){
            a[x].sm+=a[ls(x)].sm;
            a[x].l.x=min(a[x].l.x,a[ls(x)].l.x),a[x].r.x=max(a[x].r.x,a[ls(x)].r.x);
            a[x].l.y=min(a[x].l.y,a[ls(x)].l.y),a[x].r.y=max(a[x].r.y,a[ls(x)].r.y);
        }
        if(rs(x)){
            a[x].sm+=a[rs(x)].sm;
            a[x].l.x=min(a[x].l.x,a[rs(x)].l.x),a[x].r.x=max(a[x].r.x,a[rs(x)].r.x);
            a[x].l.y=min(a[x].l.y,a[rs(x)].l.y),a[x].r.y=max(a[x].r.y,a[rs(x)].r.y);
        }
    }
    inline int build(int l,int r,int t){
        int x=newnode(),mid=(l+r)>>1;
        cmpt=t;
        nth_element(pos+l,pos+mid,pos+r+1,cmp);
        a[x].tp=t,a[x].x=pos[mid],ls(x)=rs(x)=0;
        if(l<=mid-1) ls(x)=build(l,mid-1,t^1);
        if(r>=mid+1) rs(x)=build(mid+1,r,t^1);
        pushup(x);
        return x;
    }
    inline void get(int x){
        if(ls(x)) get(ls(x));
        pos[++tmp]=a[x].x,fre[++tp]=x;
        if(x==root) chgr=1;
        if(rs(x)) get(rs(x));
    }
    inline void rebuild(int &x){
        if(alpha*a[x].sz>max(a[ls(x)].sz,a[rs(x)].sz)) return;
        tmp=0,chgr=0;
        get(x),x=build(1,tmp,0);
        if(chgr) root=x;
    }
    inline void insert(int &x,point pt,int t){
        if(!x){
            x=newnode();
            a[x].sz=1,a[x].x=pt,a[x].tp=t;
            pushup(x);
            return;
        }
        if(pt==a[x].x){ // 小 Trick
            a[x].x.val+=pt.val;
            pushup(x);
            return;
        }
        cmpt=t;
        if(cmp(pt,a[x].x)) insert(ls(x),pt,t^1);
        else insert(rs(x),pt,t^1);
        pushup(x),rebuild(x);
    }
    inline ll ask(int x,point i,point j){
        if(!x || a[x].l.x>j.x || a[x].r.x<i.x || a[x].l.y>j.y || a[x].r.y<i.y) return 0;
        if(a[x].l.x>=i.x && a[x].r.x<=j.x && a[x].l.y>=i.y && a[x].r.y<=j.y)
            return a[x].sm;
        ll res=0;
        if(interv(a[x].x.x,i.x,j.x) && interv(a[x].x.y,i.y,j.y)) res+=a[x].x.val;
        res+=ask(ls(x),i,j)+ask(rs(x),i,j);
        return res;
    }
}kdt;

// ---------------KDT板子结束---------------

set<int> st[max_n];
inline int Pre(int x,int col){ // 查询前驱
    auto it=st[col].lower_bound(x);
    --it;
    return *it;
}
inline int Nxt(int x,int col){ // 查询后继
    return *(st[col].upper_bound(x));
}

signed main(){
    n=read(),m=read();
    for(register int i=1;i<=n;++i)
        st[i].insert(0),st[i].insert(n+1);
    for(register int i=1;i<=n;++i){
        a[i]=read(),st[a[i]].insert(i);
        pre[i]=Pre(i,a[i]);
        kdt.insert(kdt.root,makep(i,pre[i],i-pre[i]),0);
    }
    for(register int i=1;i<=n;++i)
        nxt[i]=Nxt(i,a[i]);
    while(m--){
        int op=read();
        if(op==1){
            int i=read(),val=read();
            kdt.insert(kdt.root,makep(i,pre[i],pre[i]-i),0),
            kdt.insert(kdt.root,makep(nxt[i],i,i-nxt[i]),0);
            // 先把原颜色的的点删掉
            st[a[i]].erase(i),st[val].insert(i);
            pre[nxt[i]]=pre[i],nxt[pre[i]]=nxt[i];
            // 修改原颜色的前驱后继关系
            kdt.insert(kdt.root,makep(nxt[i],pre[i],nxt[i]-pre[i]),0);
            // 修改原颜色的点权
            a[i]=val;
            pre[i]=Pre(i,a[i]),nxt[i]=Nxt(i,a[i]);
            // 更新这个点前驱后继关系
            kdt.insert(kdt.root,makep(nxt[i],pre[nxt[i]],pre[nxt[i]]-nxt[i]),0);
            nxt[pre[i]]=pre[nxt[i]]=i;
            kdt.insert(kdt.root,makep(i,pre[i],i-pre[i]),0),
            kdt.insert(kdt.root,makep(nxt[i],i,nxt[i]-i),0);
            // 更新新颜色前驱后继关系和权值
        }
        if(op==2){
            int l=read(),r=read();
            write(kdt.ask(kdt.root,makep(l,l,0),makep(r,r,0))),putchar('\n');
        }
    }
    return 0;
}
```



---

## 作者：FZzzz (赞：2)

这里说一个有点不一样的方法。

记录每个点的前驱后继，然后对于每个点，如果他的前驱在区间左边就有负的贡献，后继在右边就有正的贡献，否则没有贡献。

这样的话可以拆成两个带修二维偏序问题，据说树套树会 MLE？那就跑两遍 cdq 就行了。
```cpp
#include<set>
#include<vector>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=1e5+5;
int n,m,a[maxn];
set<int> s[maxn];
typedef set<int>::iterator iter;
int pre[maxn],suc[maxn];
int get_pre(int x){
	iter it=s[a[x]].lower_bound(x);
	if(it==s[a[x]].begin()) return 0;
	else return *(--it);
}
int get_suc(int x){
	iter it=s[a[x]].upper_bound(x);
	if(it==s[a[x]].end()) return n+1;
	else return *it;
}
struct point{
	int x,y,w,id;
	bool flag;
	point(int x,int y,int w,int id,bool flag)
	:x(x),y(y),w(w),id(id),flag(flag){}
};
vector<point> q1,q2;
void modify(int x){
	q1.push_back(point(x,pre[x],x,-1,0));
	q1.push_back(point(x,pre[x]=get_pre(x),-x,-1,0));
	q2.push_back(point(n+1-x,n+1-suc[x],-x,-1,0));
	q2.push_back(point(n+1-x,n+1-(suc[x]=get_suc(x)),x,-1,0));
}
typedef long long ll;
ll c[maxn];
inline int lowbit(int x){
	return x&-x;
}
void modify(int x,ll k){
	while(x<=n+1){
		c[x]+=k;
		x+=lowbit(x);
	}
}
ll query(int x){
	ll s=0;
	while(x>0){
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
int ord[maxn*11];
ll ans[maxn];
void solve(vector<point>& q,int l,int r){
	if(l==r){
		ord[r]=r;
		return;
	}
	int mid=l+(r-l)/2;
	solve(q,l,mid);
	solve(q,mid+1,r);
	int cur=l;
	vector<int> res;
	for(int i=mid+1;i<=r;i++){
		while(cur<=mid&&q[ord[cur]].x<=q[ord[i]].x){
			modify(q[ord[cur]].y+1,q[ord[cur]].w);
			res.push_back(ord[cur]);
			cur++;
		}
		if(q[ord[i]].id>=0){
			ll s=query(q[ord[i]].y+1);
			if(q[ord[i]].flag) ans[q[ord[i]].id]+=s;
			else ans[q[ord[i]].id]-=s;
		}
		res.push_back(ord[i]);
	}
	for(int i=cur;i<=mid;i++) res.push_back(ord[i]);
	for(int i=l;i<cur;i++) modify(q[ord[i]].y+1,-q[ord[i]].w);
	for(int i=l;i<=r;i++) ord[i]=res[i-l];
}
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    m=readint();
    for(int i=1;i<=n;i++) s[a[i]=readint()].insert(i);
    for(int i=1;i<=n;i++){
    	q1.push_back(point(i,pre[i]=get_pre(i),-i,-1,0));
    	q2.push_back(point(n+1-i,n+1-(suc[i]=get_suc(i)),i,-1,0));
	}
	int cnt=0;
	while(m--){
		int opt=readint();
		if(opt==1){
			int b,c;
			b=readint();
			c=readint();
			s[a[b]].erase(b);
			s[a[b]=c].insert(b);
			modify(pre[b]);
			modify(suc[b]);
			modify(b);
			modify(pre[b]);
			modify(suc[b]);
		}
		else{
			int b,c;
			b=readint();
			c=readint();
			q1.push_back(point(c,b-1,0,cnt,1));
			q1.push_back(point(b-1,b-1,0,cnt,0));
			q2.push_back(point(n+1-b,n-c,0,cnt,1));
			q2.push_back(point(n-c,n-c,0,cnt,0));
			cnt++;
		}
	}
	solve(q1,0,q1.size()-1);
	solve(q2,0,q2.size()-1);
	for(int i=0;i<cnt;i++) printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：Uuuuuur_ (赞：1)

提供一种时间复杂度 $O(n^{\frac{5}{3}}+n \log n)$ 的带修莫队解法。总体思想和其他题解差不多，所以会讲的比较简略。

这种区间统计的题，用莫队做再合适不过了。

## 不考虑修改
如果没有修改操作，就是莫队裸题，考虑对每一种数字，维护当前区间最靠左和最靠右的下标，然后 $O(1)$ 更新就好了。复杂度是 $O(n \sqrt{n})$。

## 修改操作
那就变成了带修莫队，我们加一维时间维，根据带修莫队的模版，我们只要再考虑时间维左右移动对**答案和之后操作贡献的变化**。

这时候，如果单单只维护区间最左最右下标是不行的，因为如果删掉中间那个元素，无法考虑对之后操作的影响。这时候，就有一个绝妙的想法：

对于 $[l,r]$ 内所有值为 $x$ 的元素，只要把所有相邻的两个（中间没有 $x$ 了）下标减一减，然后加起来，就是 $x$ 的贡献。所以，我们只要维护前驱 $last_i$ 和后继 $next_i$（在相同值的集合中），总答案就是 $\displaystyle\sum_{l \le i <next_i \le r}{(next_i-i)}$。

那么莫队更改一个元素，可以看成先删除后加入，就是在更新 $next_{last_i},last_{next_i},last_i,next_i$，如果能动态维护序列的前驱后继，那么更新答案也不在话下。

以加入操作为例。

若 $i \in [l,r]$，且 $last_i$，$next_i$ 一个在区间内，一个不在，说明 $i$ 为端点，需要增加答案。

反之对当前答案没有更新，只需要更新前驱后继即可。

由于需要维护前驱后继，且要快速查找，每次修改操作都要 $O(\log n)$ 的时间。总时间复杂度就是 $O(n^{\frac{3}{5}}\log n)$。时间复杂度过高。

## 预处理优化
其实，上述算法的瓶颈就在于 $O(\log n)$ 维护前驱后继，不过，我们每次修改的位置和值是固定的，那么就不用在莫队里边维护边算答案，不如预处理一下，直接把每次修改元素（包括删除和加入的）的前驱后继算出来，这样莫队就能 $O(1)$ 转移，复杂度就变成了 $O( n^{\frac{5}{3}} + n \log n)$。~~十分优秀，没有什么优化最慢只有 2000ms。~~

没错，这就是莫队二次离线，把端点移动时对数据结构影响预处理出来，加速莫队过程中的转移。
## 代码
分类讨论情况可能有点多，$las$ 和 $nex$ 维护莫队中的前缀后缀，$pre$ 和 $suf$ 便是记录每次修改相关的前缀后缀。

注意修改操作，对应着删除和加入两种操作，如果时间戳反向移动，就要删除“应该加入的”，加入“应该删除的”。



```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const int N = 2e5 + 100;
typedef long long ll;
int B, n, m, qid, cid;
struct node {
	int l, r, t, id;
	bool operator < (const node& b) const {
		if (l / B == b.l / B) {
			return r / B == b.r / B ? t < b.t : r < b.r;
		}
		return l < b.l;
	}
}q[N];
struct Ch {
	int x = 0, val = 0;
}c[N];
int nex[N], las[N], pos[N];
int a[N];
int b[N];
int pre[N], suf[N];
ll res[N];
set<int> s[N];
ll ans;
int L = 1, R , ti, now;
void add_L(int x) {
	if (nex[x] <= R) ans += nex[x] - x;
}
void add_R(int x) {
	if (las[x] >= L) ans += x - las[x];
}
void del_L(int x) {
	if (nex[x] <= R) ans -= nex[x] - x;
}
void del_R(int x) {
	if (las[x] >= L) ans -= x - las[x];
}
void add_int(int t, int x) {
	int l = pre[t], r = suf[t];
	nex[l] = x, las[r] = x;
	las[x] = l, nex[x] = r;
	if (x >= L && x <= R) {
		if (l >= L && l <= R && r > R) ans += x - l;
		else if (r >= L && r <= R && l < L) ans += r - x;
	}
}
void del_int(int t, int x) {
	int l = pre[t], r = suf[t];
	nex[l] = r, las[r] = l;
	if (x >= L && x <= R) {
		if (l >= L && l <= R && r > R) ans -= x - l;
		else if (r >= L && r <= R && l < L) ans -= r - x;
	}
}
void add_t(int t) {
	del_int(2 * t, c[t].x);
	add_int(2 * t + 1, c[t].x);
}
void del_t(int t) {
	del_int(2 * t + 1, c[t].x);
	add_int(2 * t, c[t].x);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	B = pow(n, 0.667);
	for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i], s[a[i]].insert(i);
	for (int i = 1; i <= n; i++) s[i].insert(0), s[i].insert(N - 1);
	for (int i = 1; i <= n; i++) {
		las[i] = pos[a[i]];
		nex[las[i]] = pos[a[i]] = i;
		nex[i] = N - 1;
	}
	
	for (int i = 1; i <= m; i++) {
		int op, a, b;
		cin >> op >> a >> b;
		if (op == 1) {
			c[++cid] = {a, b};
		} else {
			++qid;
			q[qid] = {a, b, cid, qid};
		}
	}	
	
	for (int i = 1; i <= cid; i++) {
		int x = c[i].x, val = c[i].val;
		s[b[x]].erase(x);
		auto it = s[b[x]].upper_bound(x);
		suf[2 * i] = *it;
		pre[2 * i] = *(--it);
		it = s[val].upper_bound(x);
		suf[2 * i + 1] = *it;
		pre[2 * i + 1] = *(--it);
		b[x] = val;
		s[val].insert(x);
	}
	sort(q + 1, q + 1 + qid);
	
	for (int i = 1; i <= qid; i++) {
		int l = q[i].l, r = q[i].r, t = q[i].t;
		while (L > l) add_L(--L);
		while (R < r) add_R(++R);
		while (ti < t) add_t(++ti);
		while (L < l) del_L(L++);
		while (R > r) del_R(R--);
		while (ti > t) del_t(ti--);
		res[q[i].id] = ans;
	}
	for (int i = 1; i <= qid; i++) cout << res[i] << '\n';
	return 0;
}
```


---

## 作者：moosssi (赞：1)

一道不错的 $cdq$ 分治练手题。

题目求的是在给定区间内，每种数最后一次出现位置的下标减去第一次出现位置的下标的值的和。

这里对于每一种数，我们可以把大区间（第一次到最后一次）转化为一个一个的小区间（每个数和它的前驱），即为 $\sum\limits_{i=1}^Ri-pre(L\le pre)$。

将它转化为三维偏序问题，对于 $i$ 和它的前驱 $pre_i$，时间戳 $t_i$ 若满足：$(L\le pre,i\le R,t_i<t_j)$，则对答案贡献为 $i-pre_i$。

以输入先后，为天然的时间顺序，不用再排序，求 $cdq$ 过程不再赘述，用好 $set$ 可以方便地动态更新前驱。

修改需要格外细心，原来的数，删去两小区间，加上一个大的区间，而新的数，加上两小区间，删去一个大的区间，删去时和之前加的情况一样，把贡献值改成负的即可。

注意开longlong。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
struct nod{
	int x,y,p;
	ll v;
	int id;
}q[N],w[N];
int n,m,pre[N],d[N];
ll tr[N];
set<int>p[N];
bool cmp(nod a,nod b){
	return a.id<b.id;
}
int lowbit(int x){
	return x&-x;
}
void add(int x,int v){
	for(int i=x;i<N;i+=lowbit(i)){
		tr[i]+=v;
	}
}
ll query(int x){
	ll res=0;
	for(int i=x;i;i-=lowbit(i)){
		res+=tr[i];
	}
	return res;
}
void merg_sort(int l,int r){
	if(l>=r)return ;
	int mid=(l+r)/2;
	merg_sort(l,mid);
	merg_sort(mid+1,r);
	int i=l,j=mid+1,k=1;
	while(i<=mid&&j<=r){
		if(q[i].y>=q[j].y){
			if(q[i].p==1)add(q[i].x,q[i].v);
			w[k++]=q[i++];
		}
		else {
			if(q[j].p==2)q[j].v+=query(q[j].x);
			w[k++]=q[j++];
		}
	}
	while(i<=mid){
		if(q[i].p==1)add(q[i].x,q[i].v);
		w[k++]=q[i++];		
	}
	while(j<=r){
		if(q[j].p==2)q[j].v+=query(q[j].x);
		w[k++]=q[j++];		
	}
	for(i=l;i<=mid;i++){
		if(q[i].p==1)add(q[i].x,-q[i].v);
	}
	for(i=l,j=1;j<k;i++,j++){
		q[i]=w[j];
	}
}
int main(){
	int l=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		int j;
		scanf("%d",&j);
		d[i]=j;
		p[j].insert(i);
		set<int>::iterator k=p[j].find(i);
		if(k!=p[j].begin()){
			k--;
			q[++l]={i,*k,1,i-*k,l};
		}
	}
	for(int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(a==1){
			if(d[b]==c)continue;
			int pre=0,let=0;
			set<int>::iterator k=p[d[b]].find(b);
			if(k!=p[d[b]].begin())k--,pre=*k;
			k++;
			if(pre)k++;
			if(k!=p[d[b]].end())let=*k;
			if(pre)q[++l]={b,pre,1,-b+pre,l};
			if(let)q[++l]={let,b,1,-let+b,l};
			if(pre&&let)q[++l]=	{let,pre,1,let-pre,l};	
			p[d[b]].erase(b);
			p[c].insert(b);
			d[b]=c;
			k=p[c].find(b),pre=0,let=0;		
			if(k!=p[c].begin())k--,pre=*k;
			k++;
			if(pre)k++;
			if(k!=p[c].end())let=*k;
			if(pre)q[++l]={b,pre,1,b-pre,l};
			if(let)q[++l]={let,b,1,let-b,l};
			if(pre&&let)q[++l]={let,pre,1,-let+pre,l};							
		}
		else q[++l]={c,b,2,0,l};
	}
	merg_sort(1,l);
	sort(q+1,q+l+1,cmp);
	for(int i=1;i<=l;i++){
		if(q[i].p==2)printf("%lld\n",q[i].v);
	}
	return 0;
}
```


---

## 作者：Gmt丶FFF (赞：0)

二维分块，写了一遍不想写第二遍系列。

对于二维分块是什么，这里建议看 [xfrvq](https://www.luogu.com.cn/blog/368107/from-range-color-count-to-2-d-block) 巨佬的博客，讲的十分清楚，我也是从这里入门的。

那么看一下本题，我们要解决一维区间带修数颜色问题，我们对于每个元素将其映射为二维坐标上的一个点 $(i,pre_i)$，权值为 $i-pre_i$，其中 $pre_i$ 为在 $i$ 之前第一个与 $i$ 相等的数的下标。

那么询问即为求 $(l,l)$ 到 $(r,r)$ 的点权和，修改为单点修改。

可以知道，由于每个点的 $i$ 不重复，每个点的 $pre_i$ 也不重复，若 $pre_i=0$，实际上是没用贡献的，所以当 $pre_i=0$ 时不加入此点，所以符合二维分块使用条件。

我们就可以维护 $n^{0.5}$ 个大小为 $n^{0.75}\times n^{0.75}$ 的大块，对于每排大块，分成 $n^{0.5}$ 个大小为 $n^{0.75}\times n^{0.5}$ 的横块，对于每列大块，分成 $n^{0.75}$ 个大小为 $n^{0.5}\times n^{0.75}$ 的竖块，再对于每个大块，分成 $n^{0.5}$ 个 $n^{0.5}\times n^{0.5}$ 的小块，然后维护所有大块前缀和，对于每一排或列的大块维护横块或竖块的前缀和，再对于每一个大块维护小块的前缀和。

对于单点修改，直接对上述四种前缀和暴力修改即可，对于询问，先利用前缀拆成四个从 $(1,1)$ 到 $(x,y)$ 的询问，然后对于整块，直接查前缀和，对于散块，我们暴力枚举，看这些区间内是否有点即可，具体实现就是枚举散块的行与列，然后看这一行和这一列的点在哪里，看是否在范围内，因为一行和一列最多只有一个点，所以正确性可以保证。

注意，修改一个下标为 $x$ 的点，会影响在 $x$ 之后第一个与 $x$ 原权值相等的点与在 $x$ 之后第一个与 $x$ 现权值相等的点，要找到这两个点可以用 set 暴力维护每种数的下标集合即可。

```cpp
#include<iostream>
#include<cstdio>
#include<set>
#define int long long
using namespace std;
const int N=1e5+5;
const int K=316;
const int K2=5688;
const int M=K+5;
const int M2=K2+5;
const int T=N/K+5;
const int T2=N/K2+5;
const int P=K2/K;
int n,m,a[N],pre[N],suf[N],B[N],L[T],R[T],B2[N],L2[T],R2[T];
int f1[T2][T2],f2[T2][T],f3[T][T2],f4[T][T],g1[N],g2[N];
set<int>s[N];
void init()
{
	for(int i=1;i<=n;i++)B[i]=i/K+1,B2[i]=i/K2+1;
	for(int i=1;i<=B[n];i++)L[i]=max(1ll,(i-1)*K),R[i]=min(n,i*K-1);
	for(int i=1;i<=B2[n];i++)L2[i]=max(1ll,(i-1)*K2),R2[i]=min(n,i*K2-1);
}
void update(int x,int y,int k)
{
//	cout<<x<<" "<<y<<" "<<k<<" ???\n";
	if(k<0)g1[x]=g2[y]=0;
	else g1[x]=y,g2[y]=x;
	if(y==0)return;
	for(int i=B2[x];i<=B2[n];i++)for(int j=B2[y];j<=B2[n];j++)f1[i][j]+=k;
	for(int i=B2[x];i<=B2[n];i++)for(int j=B[y];R[j]<=R2[B2[y]]&&j<=B[n];j++)f2[i][j]+=k;
	for(int i=B[x];R[i]<=R2[B2[x]]&&i<=B[n];i++)for(int j=B2[y];j<=B2[n];j++)f3[i][j]+=k;
	for(int i=B[x];R[i]<=R2[B2[x]]&&i<=B[n];i++)for(int j=B[y];R[j]<=R2[B2[y]]&&j<=B[n];j++)f4[i][j]+=k;
}
inline int search(int x,int y)
{
	if(x==0||y==0)return 0;
	int sum=f1[B2[x]-1][B2[y]-1];
	if(B2[y]==B2[L[B[y]-1]])sum+=f2[B2[x]-1][B[y]-1];
	if(B2[x]==B2[L[B[x]-1]])sum+=f3[B[x]-1][B2[y]-1];
	if(B2[y]==B2[L[B[y]-1]]&&B2[x]==B2[L[B[x]-1]])sum+=f4[B[x]-1][B[y]-1];	
	for(int i=L[B[x]];i<=x;i++)if(g1[i]<L[B[y]]&&pre[i])sum+=i-pre[i];
	for(int i=L[B[y]];i<=y;i++)if(g2[i]<=x&&g2[i])sum+=g2[i]-i;
//	cout<<x<<" "<<y<<" ??? "<<sum<<" "<<f2[B2[x]-1][B[y]-1]<<" "<<f3[B[x]-1][B2[y]-1]<<" "<<f4[B[x]-1][B[y]-1]<<" "<<B2[x]<<" "<<B2[y]<<" "<<B[x]<<" "<<B[y]<<" "<<endl;
	
	return sum;
}
inline int query(int x1,int y1,int x2,int y2)
{
	return search(y1,y2)-search(y1,x2-1)-search(x1-1,y2)+search(x1-1,x2-1);
}
signed main()
{
//	freopen("data.in","r",stdin);
//	freopen("a.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	init();
	for(int i=1;i<=n;i++)s[i].insert(0),s[i].insert(n+1);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),pre[i]=*(--s[a[i]].lower_bound(i)),suf[pre[i]]=i,s[a[i]].insert(i),update(i,pre[i],i-pre[i]);
	for(int i=1;i<=m;i++)
	{
		int opt,l,r;
		scanf("%lld%lld%lld",&opt,&l,&r);
		if(opt==1)
		{
			update(l,pre[l],-l+pre[l]);
			suf[pre[l]]=suf[l];
			if(suf[l]<=n&&suf[l])
			{
				update(suf[l],l,-suf[l]+l);
				pre[suf[l]]=pre[l];
				update(suf[l],pre[l],suf[l]-pre[l]);
			}
			s[a[l]].erase(l);
//			cout<<a[l]<<" "<<l<<" !?\n";
			a[l]=r;
			int x=*(--s[a[l]].lower_bound(l)),y=*(s[a[l]].lower_bound(l));
			if(y<=n)
			{
				update(y,pre[y],-y+pre[y]);
				pre[y]=l;
				update(y,l,y-l);
			}
			suf[x]=l;
			suf[l]=y;
			pre[l]=x;
			update(l,pre[l],l-pre[l]);
			s[a[l]].insert(l);
		}
		else
		{
			int res=query(l,r,l,r);
			printf("%lld\n",res);
		}
	}
	return 0;
}
/*
10 10
2 7 8 8 5 2 9 10 2 5 
1 10 9
1 5 4
2 3 10
2 2 7
1 10 2
1 5 3
1 3 4
*/
```


---

## 作者：L0vely_NaiL0ng (赞：0)

带修莫队 $O(n^{\frac{5}{3}} \log n)$ 要卡常。

记 $pre_i$ 为 $i$ 前面第一个 $j$ 使得 $a_i = a_j$，我们要求的柿子其实是 $\sum_{i = l}^{r} [pre_i \ge l] \times (i - pre_i)$，因为如果 $i \le l - 1$，$pre_i \le l - 1$，所以上式可以简化为 $\sum_{i = 1}^{r} [pre_i \ge l] \times (i - pre_i) $，这就是个标准的二维数点。

具体的，$pre_i$ 为横坐标，$i$ 为纵坐标，点权为 $i - pre_i$，询问形如求 $x \ge l$ 且 $y \le r$ 的点权和。

但是这题带修，所以我们考虑加一个维度时间维，转化为三维偏序（用 set 维护 $a_i$ 相同的所有 $i$，提前预处理好将修改转化为 $O(1)$ 个加点、删点），cdq 分治，归并按照 $x$ 从大到小排序，边归并边用个树状数组维护即可。

复杂度 $O(n \log^2 n)$。

```
#include<bits/stdc++.h>
#define int long long
#define lb lower_bound
#define ub upper_bound
#define fi first
#define se second
#define mid ((l + r) >> 1)
#define ls (p << 1)
#define rs (p << 1 | 1)
#define pb push_back
#define For(i, x, y) for (int i = (x); i <= (y); i++)
#define foR(i, x, y) for (int i = (x); i >= (y); i--)
#define pii pair<int, int>
using namespace std;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
const int N = 1e6 + 5, mod = 1e9 + 7;
void cmin(int &x, int y) { x = min(x, y); return; }
void cmax(int &x, int y) { x = max(x, y); return; }
namespace BIT {
	int t[N];
	void add(int x, int v) {
		while (x < N) t[x] += v, x += x & -x; 
	}
	int query(int x) {
		int s = 0;
		while (x) s += t[x], x -= x & -x;
		return s;
	}
	int query(int l, int r) {
		return query(r) - query(l - 1);
	}
}
struct node {
	int op, x, y, id;//1 加入 -1 删除 0询问
	//x pre y i
	//x >= l y <= r 
} q[N], p[N];
int ans[N];
void cdq(int l, int r) {
	if (l >= r) return;
	cdq(l, mid); cdq(mid + 1, r);
	int i = l, j = mid + 1, k = l - 1;
	while (i <= mid || j <= r) {
		if (i == mid + 1) {
			if (!q[j].op) ans[q[j].id] += BIT::query(q[j].y);
			p[++k] = q[j]; j++;
		} else if (j == r + 1) {
			if (q[i].op) BIT::add(q[i].y, (q[i].y - q[i].x) * q[i].op);
			p[++k] = q[i]; i++;
		} else {
			if (q[i].x >= q[j].x) {
				if (q[i].op) BIT::add(q[i].y, (q[i].y - q[i].x) * q[i].op);
				p[++k] = q[i]; i++;				
			} else {
				if (!q[j].op) ans[q[j].id] += BIT::query(q[j].y);
				p[++k] = q[j]; j++;			
			}
		}
	}
	For (i, l, mid)
		if (q[i].op) 
			BIT::add(q[i].y, -(q[i].y - q[i].x) * q[i].op);
	For (i, l, r) q[i] = p[i];
	return;
}
int n, m, t, a[N];
set<int> pos[N];
signed main() {
	//freopen("1.in", "r", stdin);
	cin >> n >> m;
	For (i, 1, n) {
		cin >> a[i];
		if (pos[a[i]].size()) {
			q[++t] = {1, *(prev(pos[a[i]].end())), i, 0};
		}
		pos[a[i]].insert(i);
	} 
	For (i, 1, m) {
		int op, x, y; cin >> op >> x >> y;
		if (op == 1) {
			auto it = pos[a[x]].find(x); it++;
			if (it != pos[a[x]].end()) {
				q[++t] = {-1, x, *it, 0}; it--;
				if (it != pos[a[x]].begin()) q[++t] = {1, *(prev(it)), *(next(it)), 0};	
			}
			it = pos[a[x]].find(x);
			if (it != pos[a[x]].begin()) q[++t] = {-1, *(prev(it)), x, 0};
			pos[a[x]].erase(x); a[x] = y; pos[a[x]].insert(x);
			it = pos[a[x]].find(x); 
			if (it != pos[a[x]].begin()) q[++t] = {1, *(prev(it)), x, 0};
			it++;
			if (it != pos[a[x]].end()) {
				q[++t] = {1, x, *it, 0}; it--;
				if (it != pos[a[x]].begin()) q[++t] = {-1, *(prev(it)), *(next(it)), 0};
			}
			ans[i] = -1;
		} else {
			q[++t] = {0, x, y, i};
		}
	}
	cdq(1, t);
	For (i, 1, m) {
		if (ans[i] != -1) cout << ans[i] << endl;
	}
	return 0;
}
```

---

## 作者：Alex_Eon (赞：0)

[博客内食用效果更佳](https://www.luogu.com.cn/blog/Ksy/solution-cf848c)

思路：CDQ 分治（三维偏序）

对于给出的一个序列 $val$，设 $pre_i$ 为上一个值为 $val_i$ 的元素下标，即：
$$pre_i=\max\left\{j\right\}\quad \left(val_j=val_i,j<i\right)$$
所以对于 $l,r$ 的询问我们可以转化为：
$$ans_{l,r}=\sum\limits_{i=l}^r\left(val_i-pre_i\right)\quad \left(pre_i\ge l\right)$$
显然地，当 $pre_i\ge l$ 时，一定有 $i>l$，所以答案转化为：
$$ans_{l,r}=\sum\left(val_i-pre_i\right)\quad \left(pre_i\ge l,i\le r\right)$$
现在已经有两维度的条件，加上时间维度便是三维条件，所以可以用三维偏序进行求解。

具体实现：
1. 对于 $pre$ 的维护
	- 采用 set 维护，对于数值 $v$ 来说，我们用 $s_v$ 存储所有 $v$ 出现的位置。
2. 对于初始序列
	- 只需要加入每个点的贡献，对于第 $i$ 个位置，将 $\left(pre_i,i,t\right)$ 加入 CDQ 中，值为 $i-pre_i$。
3. 对于修改操作 $\left(a,b,c\right)$
	- 将原来的值的贡献减掉：删除 $b$ 对 $pre_b$ 的贡献，删除 $nex_b$ 对 $b$ 的贡献，加入 $nex_b$ 对 $pre_b$ 的贡献。
	- 将 $b$ 从 $s_{val_b}$ 中删除，将 $b$ 加入 $s_c$，将 $val_b$ 更新为 $c$。
   - 将新的值的贡献加入，与前面的操作类似。
4. 对于询问操作 $\left(a,b,c\right)$
	- 直接将 $\left(b,c,t\right)$ 加入 CDQ 中。

代码实现需要注意的地方：
- set 的迭代器左闭右开，即 `s.end()` 所指的位置不在序列中。

我的代码采用的是先对 $t$ 排序（本身加入的时候就是有序的），再对 $l$ 排序，将 $r$ 插入树状数组中。

参考代码：
```cpp
#define LL long long
#define UN unsigned
#include<bits/stdc++.h>
using namespace std;
//--------------------//
const int N=1e5+1;

int n,m;
int val[N];
set<int>s[N];
//--------------------//
struct CT//树状数组
{
	LL t[N];
	int lobit(int x){return x&-x;}
	void change(int p,LL val)
	{
		while(p<=n)
			t[p]+=val,p+=lobit(p);
		return;
	}
	LL query(int p)
	{
		LL res=0;
		while(p>0)
			res+=t[p],p-=lobit(p);
		return res;
	}
}T;
//--------------------//
//CDQ
const int NM=1e6+1;
struct CDQ_Node
{
	int l,r,t;
	LL val;
	int type;
}cdq[NM],tem[NM];
int cnt;

int ast;//ast 是询问操作计数
LL ans[N];

void CDQ(int l,int r)
{
	if(l==r)
		return;
	int mid=l+r>>1,p1=l,p2=mid+1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	for(int i=l;i<=r;i++)
	{
		if(p1<=mid&&(p2>r||cdq[p1].l>=cdq[p2].l))//按照 l 大小排序
		{
			if(cdq[p1].type==1)
				T.change(cdq[p1].r,cdq[p1].val);
			tem[i]=cdq[p1++];
		}
		else
		{
			if(cdq[p2].type==2)
				ans[cdq[p2].val]+=T.query(cdq[p2].r);
			tem[i]=cdq[p2++];
		}
	}
	for(int i=l;i<=mid;i++)//回溯
		if(cdq[i].type==1)
			T.change(cdq[i].r,-cdq[i].val);
	for(int i=l;i<=r;i++)
	{
		cdq[i]=tem[i];
	}
	return;
}
//--------------------//
int main()
{
	multiset<int>::iterator it;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&val[i]);
		s[val[i]].insert(i);
		it=s[val[i]].find(i);
		if(it!=s[val[i]].begin())//没有前缀则不需要修改
		{
			--it;
			cdq[++cnt]={*it,i,cnt,i-*it,1};
		}
	}
	int a,b,c,last,pre,nex;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		if(a==1)
		{
			if(val[b]==c)
				continue;

			pre=0,nex=0;
			it=s[val[b]].find(b);
			if(it!=s[val[b]].begin())--it,pre=*it,++it;
			++it;
			if(it!=s[val[b]].end())nex=*it;
			//删除原先的贡献
			if(pre)cdq[++cnt]={pre,b,cnt,pre-b,1};
			if(nex)cdq[++cnt]={b,nex,cnt,b-nex,1};
			if(pre&&nex)cdq[++cnt]={pre,nex,cnt,nex-pre,1};

			s[val[b]].erase(b);
			val[b]=c;
			s[c].insert(b);

			pre=0,nex=0;
			it=s[c].find(b);
			if(it!=s[c].begin())--it,pre=*it,++it;
			++it;
			if(it!=s[c].end())nex=*it;
			//添加新的贡献
			if(pre)cdq[++cnt]={pre,b,cnt,b-pre,1};
			if(nex)cdq[++cnt]={b,nex,cnt,nex-b,1};
			if(pre&&nex)cdq[++cnt]={pre,nex,cnt,pre-nex,1};
		}
		else
			cdq[++cnt]={b,c,cnt,++ast,2};
	}
	CDQ(1,cnt);
	for(int i=1;i<=ast;i++)
		printf("%lld\n",ans[i]);
    return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：0)

提供一种树套树卡空间的做法。

最开始是想用类似差分的方法做但是萎掉了。           

考虑一种很正常的想法，还是基于差分，我们对序列上每个数用 $(pre_x , x)$，其中 $pre_x$ 表示的是对于在 $x$ 之前的第一个 $j$ 使得和 $a_x = a_j$，并将一个点的权值置为 $x - pre_x$。             

显然对于 $pre_x$ 可以直接用 set 维护。

现在问题转化成了查询将 $l \leq pre_x < x \leq r$ 的点的权值之和，用树套树，cdq 分治等都可以解决。              

若直接开 long long，会 MLE，我在卡了很久空间后终究还是放弃了直接卡空间大小，但后来上网一查，发现还有 unsigned int 这种好东西，又由于原题的运算数大小都在 $2.5 \times 10 ^ 9$ 之内，所以直接开 unsigned int 后把空间调大点就好了。         

时空复杂度 $O(n \log ^ 2 n)$。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,q,a[Len],pre[Len],v[Len],rt[Len << 2];
set<int> st[Len];
set<int>::iterator it;
struct Seg
{
	unsigned int sum[Len * 178];int tot,lc[Len * 178],rc[Len * 178];
	void push_up(int x){sum[x] = sum[lc[x]] + sum[rc[x]];}
	void del(int &p,int l,int r,int idx)
	{
		if(!p) p = ++ tot;
		if(l == r){sum[p] = 0;return;}
		int mid = (l + r) >> 1;
		if(idx <= mid) del(lc[p] , l , mid , idx);
		else del(rc[p] , mid + 1 , r , idx);
		push_up(p);
	}
	void update(int &p,int l,int r,int idx,int w)
	{
		if(!p) p = ++ tot;
		if(l == r){sum[p] = w;return;}
		int mid = (l + r) >> 1;
		if(idx <= mid) update(lc[p] , l , mid , idx , w);
		else update(rc[p] , mid + 1 , r , idx , w);
		push_up(p); 
	}
	unsigned int query(int &p,int l,int r,int nl,int nr)
	{
		if(!p) return 0;
		if(nl <= l && nr >= r) return sum[p];
		int mid = (l + r) >> 1;unsigned int res = 0;
		if(nl <= mid) res += query(lc[p] , l , mid , nl , nr);
		if(nr > mid) res += query(rc[p] , mid + 1 , r , nl , nr);
		return res;
	}
}S1;
#define ls(p) p << 1
#define rs(p) p << 1 | 1
void del(int p,int l,int r,int idx,int y)
{
	S1.del(rt[p] , 1 , n , y);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(idx <= mid) del(ls(p) , l , mid , idx , y);
	else del(rs(p) , mid + 1 , r , idx , y);
}
void update(int p,int l,int r,int idx,int y,int w)
{
	S1.update(rt[p] , 1 , n , y , w);
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(idx <= mid) update(ls(p) , l , mid , idx , y , w);
	else update(rs(p) , mid + 1 , r , idx , y , w);
}
unsigned int query(int p,int l,int r,int nl,int nr,int L,int R)
{
	if(nl <= l && nr >= r) return S1.query(rt[p] , 1 , n , L , R);
	int mid = (l + r) >> 1;unsigned int res = 0;
	if(nl <= mid) res += query(ls(p) , l , mid , nl , nr , L , R);
	if(nr > mid) res += query(rs(p) , mid + 1 , r  , nl , nr , L , R);
	return res;
}
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(unsigned int x) {
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
	n = read() , q = read();
	for(int i = 1 ; i <= n ; i ++) a[i] = read();
	for(int i = 1 ; i <= n ; i ++)
	{
		st[a[i]].insert(i);
		it = st[a[i]].lower_bound(i);it --;
		if(*it && *it < i) pre[i] = *it;
	}
	for(int i = 1 ; i <= n ; i ++) if(pre[i]) update(1 , 1 , n , pre[i] , i , v[i] = i - pre[i]);
	for(int i = 1 ; i <= q ; i ++) 
	{
		int A,B,C;A = read() , B = read() , C = read();
		if(A == 1) 
		{
			it = st[a[B]].upper_bound(B);
			//printf("!!!%d %d\n",a[B],*it);
			if(B < *it) 
			{
				int suf = *it , prre;
				it = st[a[B]].lower_bound(B);if(it != st[a[B]].begin()) it --;
				if(*it >= B) prre = 0;
				else prre = *it;
				if(pre[suf]) del(1 , 1 , n , pre[suf] , suf);
				pre[suf] = prre;
				if(pre[suf]) update(1 , 1 , n , pre[suf] , suf , v[suf] = suf - pre[suf]);
			}
			if(pre[B]) del(1 , 1 , n , pre[B] , B);
			st[a[B]].erase(B);a[B] = C;st[a[B]].insert(B);
			it = st[a[B]].lower_bound(B);if(it != st[a[B]].begin()) it --;
			if(*it < B) 
			{
				//printf("!!!%d %d %d\n",i,B,*it);
				pre[B] = *it;
				if(pre[B]) update(1 , 1 , n , pre[B] , B , v[B] = B - pre[B]);
			}
			else pre[B] = 0;
			it = st[a[B]].upper_bound(B);
			if(B < *it)
			{
				int suf = *it;
				if(pre[suf]) del(1 , 1 , n , pre[suf] , suf);
				pre[suf] = B;
				if(pre[suf]) update(1 , 1 , n , pre[suf] , suf , v[suf] = suf - pre[suf]);
			}
 		}
 		else 
		{
			write(query(1 , 1 , n , B , C , B , C));
			putchar('\n');
		}
	}
	return 0;
}
```

---

## 作者：zhengrunzhe (赞：0)

吐了，树套树会mle

过不过不重要，重要的是做法

首先这种跟颜色有关的问题，会考虑维护个前驱$pre_i$表示在$i$前面的与$i$颜色相同的最近的**位置**

然后我们发现对于一个区间内同一种颜色，所有具有这个颜色的位置$p_1,p_2, \cdots,p_k$

答案是最后一次和第一次的位置差:$p_k-p_1$

然后我们发现$p_k-p_1=p_2-p_1+p_3-p_2+p_4-p_3+\cdots+p_k-p_{k-1}$

也是说一个位置$i$的贡献是$i-pre_i$

然后区间求和即可，由于$pre_i<l$的部分是某颜色第一次在区间内出现的位置，没有贡献，所以写出偏序组：

$$ans=\sum i-pre_i\ [pre_i\geq l,\ l\leq i\leq r]$$

然而由于如果一个$i<l$，由于$pre_i<i$，它也会满足$pre_i<l$，不会被计入答案，所以查询的时候只需要差一个$[1,r]$前缀就好了

带修二维偏序显然直接树套树维护，可惜mle了

关于如何动态维护$pre$

对每个颜色开一个$set$表示具有该颜色的位置

那么一个$i$的$pre_i$就是它在其所在颜色的$set$的前一个数

时间复杂度：$O(n\log^2n)$

空间复杂度：$O(n\log n)$
```cpp
#include<set>
#include<cstdio>
#include<cstdlib>
using std::set;
typedef set<int>Set;
typedef long long ll;
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
const int N(1e5+5);
int n,m,pre[N],a[N],tmp[N];
namespace Treap
{
	struct tree
	{
		int key,val,sum,pro;
		static tree *null;
		tree *son[2];
		void *operator new(size_t size);
		void operator delete(void *ptr);
		inline tree(const int &key=0,const int &val=0):key(key),val(val),sum(val),pro(rand()){son[0]=son[1]=null;}
		inline const void pushup(){sum=son[0]->sum+val+son[1]->sum;}
	}*tree::null;
	#define null tree::null
	char memory_pool[N*20*sizeof(tree)],*tail(memory_pool+sizeof memory_pool);
	void *recycle[N*20],**top(recycle);
	inline void *tree::operator new(size_t size){return top!=recycle?*--top:tail-=size;}
	inline void tree::operator delete(void *ptr){*top++=ptr;}
	inline const void init()
	{
		null=new tree;
		null->pro=0;
		null->son[0]=null->son[1]=null;
	}
	inline const void rotate(tree *&fa,const bool &f)
	{
		tree *p(fa->son[f]);
		fa->son[f]=p->son[!f];
		p->son[!f]=fa;
		fa->pushup();(fa=p)->pushup();
	}
	inline const void insert(tree *&p,const int &key,const int &val)
	{
		if (p==null)return p=new tree(key,val),void();
		const bool f(p->key<key);
		insert(p->son[f],key,val);
		p->pushup();
		if (p->son[f]->pro<p->pro)rotate(p,f);
	}
	inline const void remove(tree *&p,const int &key)
	{
		if (p->key==key)
		{
			if (p->son[0]==null&&p->son[1]==null)
			{tree *q(p);p=null;delete q;}
			if (p->son[0]==null)return p=p->son[1],void();
			if (p->son[1]==null)return p=p->son[0],void();
			const bool f(p->son[0]->pro>p->son[1]->pro);
			rotate(p,f);remove(p,key);
		}
		else remove(p->son[p->key<key],key),p->pushup();
	}
	inline const ll query(tree *p,const int &key)
	{
		if (p==null)return 0;
		if (p->key==key)return p->son[1]->sum+p->val;
		if (key>p->key)return query(p->son[1],key);
		return query(p->son[0],key)+p->son[1]->sum+p->val;
	}
}
namespace Binary_Indexed_Tree
{
	Treap::tree *root[N];
	inline const int lowbit(const int &x){return x&-x;}
	inline const void init()
	{
		for (int i(1);i<=n;i++)root[i]=Treap::null;
	}
	inline const void insert(int k,const int &x,const int &y)
	{
		for (;k<=n;k+=lowbit(k))Treap::insert(root[k],x,y);
	}
	inline const void remove(int k,const int &x)
	{
		for (;k<=n;k+=lowbit(k))Treap::remove(root[k],x);
	}
	inline const ll query(int k,const int &x)
	{
		ll sum(0ll);
		for (;k;k-=lowbit(k))sum+=Treap::query(root[k],x);
		return sum;
	}
}using namespace Binary_Indexed_Tree;
Set s[N];
inline const void del(const int &c,const int &x)
{
	Set::iterator it(s[c].find(x));
	const int lst(*--it),nxt(*++++it);
	if (nxt<=n)
	{
		if (pre[nxt])remove(nxt,pre[nxt]);
		if (pre[nxt]=lst)insert(nxt,lst,nxt-lst);
	}
	if (pre[x])remove(x,pre[x]);
	s[c].erase(--it);
}
inline const void add(const int &c,const int &x)
{
	Set::iterator it(s[c].insert(x).first);
	const int lst(*--it),nxt(*++++it);
	if (nxt<=n)
	{
		if (pre[nxt])remove(nxt,pre[nxt]);
		pre[nxt]=x;insert(nxt,x,nxt-x);
	}
	if (lst)insert(x,lst,x-lst);
}
int main()
{
	Treap::init();
	read(n);read(m);
	for (int i(1);i<=n;i++)
		read(a[i]),
		s[i].insert(0),
		s[i].insert(n+1),
		s[a[i]].insert(i),
		pre[i]=tmp[a[i]],
		tmp[a[i]]=i;
	init();
	for (int i(1);i<=n;i++)if (pre[i])insert(i,pre[i],i-pre[i]);
	for (int opt,x,y;m--;)
		if (read(opt),read(x),read(y),opt&1)del(a[x],x),add(a[x]=y,x);
		else printf("%lld\n",query(y,x));
	return 0;
}
```

---

