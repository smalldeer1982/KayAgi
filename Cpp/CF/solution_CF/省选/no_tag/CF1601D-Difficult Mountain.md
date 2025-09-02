# Difficult Mountain

## 题目描述

$n$ 个人相约去爬山。  
山的初始攀登难度为 $d$。  
每位登山者有两个属性：技巧 $s$ 和整洁度 $a$。

技巧为 $s$ 的登山者能登上攀登难度为 $p$ 的山当且仅当 $p\leq s$。  
在一位整洁度为 $a$ 的登山者登上攀登难度为 $p$ 的山后，山的攀登难度会变为 $\max(p,a)$。

请给这些登山者指定一个爬山的先后顺序，最大化登上山的人数。  
如果轮到一位登山者时他能登上山，则他一定会选择登山。

## 样例 #1

### 输入

```
3 2
2 6
3 5
5 7```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
2 4
6 4
4 6```

### 输出

```
2```

## 样例 #3

### 输入

```
5 0
1 5
4 8
2 7
7 6
3 2```

### 输出

```
3```

# 题解

## 作者：0htoAi (赞：28)

输入时先将 $s$ 值比初始 $d$​ 值还小的人删掉，显然他们没用。

剩下的人按 $\max(a_i,s_i)$ 从小到大排序。如果 $\max(a_i,s_i)$ 相等，则按 $s_i$​ 从小到大排序。

### 证明：

设排序后当前执行到第 $i$ 个人，$d$ 为山目前难度。

#### 1.

$\max(a_i,s_i)$ 为 $s_i$ 时，显然 $s_i \geq d$，因为在 $i$ 之前的人只有两种：

* $\max(s_j,a_j)< s_i$ 时，显然 $d<s_i$。
* $max(s_j,a_j)=s_i$​​ 时，显然 $d \leq s_i$。

所以这种情况的话就能更新答案。



证明为什么这种情况直接更新答案一定是最优的：

在 $i$ 之后有 $2$ 种情况，分开考虑。

* $i$ 之后的所有 $\max(s_j,a_j)$ 都取的是 $s_j$ 的值：$a_i$ 不会对这些数产生任何影响，因为 $s_j \geq s_i \geq a_i$。

* $i$ 之后有至少 $1$ 个 $\max$ 取了 $a_j$ 的值，设这个人为 $k$ 。

  $i+1$ 到 $k-1$​ 号人都同上。

  若第 $k$ 号人的 $s_k \geq a_i$，那么 $a_i$ 也不会对 $k$ 号人产生影响。

  否则如果非要让这个人去，**至少** 得让 $i$ 号人走，答案不会变大，但因为 $a_k\geq a_i$，所以 $d$ 不会变小，所以遇到这种情况选 $i$ 而不是 $k$ 依然是最优的。

  对于 $i$ 之后的每一个可能的 $k$ 值都是一样的道理。



#### 2.

$\max(a_i,s_i)$ 为 $a_i$ 时，用前文的证明方式可得：$d\leq a_i$。

此时如果 $s_i \geq d$ ，显然直接更新答案了，证明同上。

否则不更新答案。显然如果非要让这个人去，**至少**也要让之前的一个人不去，总答案不变，但 $d$​ 不会变得更小，所以最好的策略是不去。 



然后程序就很简单了。

```cpp
#include <bits/stdc++.h>

using namespace std;
const int MAXN=5e5+50;
int N,d;
struct Dot
{
	int s,a;
}p[MAXN];
bool cmp(Dot x,Dot y)
{
	if(max(x.a,x.s)==max(y.a,y.s))
	{
		return x.s<y.s;
	}
	return max(x.a,x.s)<max(y.a,y.s);
}
int main()
{
	scanf("%d%d",&N,&d);
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d",&p[i].s,&p[i].a);
	}
	sort(p+1,p+N+1,cmp);
	int ans=0;
	for(int i=1;i<=N;i++)
	{
		if(p[i].s>=d)
		{
			d=max(d,p[i].a);
			ans++;
		}
	}
	printf("%d",ans);
}
```







---

## 作者：Alex_Wei (赞：18)

> *CF1601D. [Difficult Mountain](https://www.luogu.com.cn/problem/CF1601D) *2700

一般这种神仙贪心题都做不来。

把所有登山者分成两类：一类是 $a_i\leq s_i$ 的记为集合 $S$，一类是 $s_i<a_i$ 的记为集合 $T$。前者内部互不干扰，而后者可以按照 $a_i$ 从小到大排序贪心。观察 $S$ 对 $T$ 的影响，对于 $i\in S$，$j\in T$，若 $s_j<a_i\leq s_i<a_j$，那么 $i,j$ 之间只能选一个，显然选 $i$ 更优因为 $a_i<a_j$，其他情况下可以证明 $i,j$ 可以同时选择。

如果将所有 $(s_i,a_i)$ 按照 $\max(a_i,s_i)$ 为第一关键字，$s_i$ 为第二关键字（主要考虑到 $s_j<a_i\leq s_i=a_j$ 的情况，此时 $j$ 应先被选）排序，那么对于上面的特殊情况，$i$ 一定先于 $j$ 被选。故排序后直接贪心就行，时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
const int N = 5e5 + 5;
int n, d, ans;
struct node {
	int s, a, mx;
	bool operator < (const node &v) const {
		return mx != v.mx ? mx < v.mx : s < v.s;
	}
} c[N];
int main(){
	cin >> n >> d;
	for(int i = 1; i <= n; i++) {
		cin >> c[i].s >> c[i].a, c[i].mx = max(c[i].s, c[i].a);
		if(c[i].s < d) i--, n--;
	} sort(c + 1, c + n + 1);
	for(int i = 1; i <= n; i++) if(c[i].s >= d) cmax(d, c[i].a), ans++;
	cout << ans << endl;
    return 0;
}
```

---

## 作者：gyh20 (赞：17)

给一个基于 DP 的做法。

首先将所有的人按照 $a_i$ 排序。

但此时可以发现最后选出的人的顺序不一定是按照 $a_i$ 从小到大的顺序，所以这里的 DP 状态不能是简单的最后一个选在 $i$ 的最多人数。

我们发现，一些人出发会影响 $d$ 的值但一些人不会，一个人会影响当且仅当他是出发的人中 $a$ 的前缀最大值，若一个人不会被影响，那么他可以尽量早的走（满足仍然不会影响最大值）。

我们设 $f_i$ 表示前 $i$ 个人，最后一个前缀最大值在 $i$ 处取到的最多人数，则，枚举上一个前缀最大值位置 $j$，得到：

$f_i=\max\{f_j+W(j+1,i-1,a_i)\}$

其中：

$a_j\leq s_i$

$W(l,r,x)=\sum\limits_{i=l}^r[s_i\geq x]$

前者表示 $i$ 可以作为下一个选择的，后者表示 $(j,i)$ 之间所有能选的都可以直接放在 $i$ 之后立刻选。

由于 $a$ 已经排好序，容易用线段树维护。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
struct node{
	int x,y;
	bool operator <(const node A)const{return y==A.y?x<A.x:y<A.y;}
}p[500002];
int n,m,P[500002],f[500002],mx[2000002],tg[2000002];
inline void Add(re int p,re int x){
	tg[p]+=x,mx[p]+=x;
}
inline void pd(re int p){
	if(tg[p]){
		Add(p<<1,tg[p]),Add(p<<1|1,tg[p]);
		tg[p]=0;
	}
}
inline void add(re int p,re int l,re int r,re int x,re int y,re int z){
	if(l>=x&&r<=y)return Add(p,z);
	pd(p);
	re int mid=l+r>>1;
	if(x<=mid)add(p<<1,l,mid,x,y,z);
	if(y>mid)add(p<<1|1,mid+1,r,x,y,z);
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
inline int ask(re int p,re int l,re int r,re int x,re int y){
	if(l>=x&&r<=y)return mx[p];
	pd(p);
	re int mid=l+r>>1,s=0;
	if(x<=mid)s=max(s,ask(p<<1,l,mid,x,y));
	if(y>mid)s=max(s,ask(p<<1|1,mid+1,r,x,y));
	return s;
}
inline bool cmp(re int x,re int y){return p[x].x<p[y].x;}
int main(){
	n=read(),m=read();
	for(re int i=1;i<=n;++i){
		p[i].x=read(),p[i].y=read();
		if(p[i].x<m)--i,--n;
	}
	if(!n)return puts("0"),0;
	sort(p+1,p+n+1);
	for(re int i=1;i<=n;++i)P[i]=i;
	sort(P+1,P+n+1,cmp);
	re int p1=1,ans=0;
	p[0].x=-1;
	for(re int i=1;i<=n;++i){
		while(p1<=n&&p[P[p1]].x<p[i].y){
			if(P[p1]<i)add(1,0,n,0,P[p1]-1,-1);
			++p1;
		}
		re int pos=upper_bound(p+1,p+n+1,(node){2000000000,p[i].x})-p-1;
		f[i]=ask(1,0,n,0,pos)+1;
		add(1,0,n,i,i,f[i]);
		if(p[i].x>p[P[p1-1]].x)add(1,0,n,0,i-1,1);
		ans=max(ans,f[i]);
	}
	printf("%d",ans);
}

```


---

## 作者：万弘 (赞：13)

提供一个场上写的，有点奇怪的做法。

首先题目要求有序的选取一些尽量大的元素。

那么按照套路，我们可以按某种规则排序，然后考虑dp。

那么问题变成

- 怎么排序，使得存在最优解是排序后序列的一个子序列（即让dp无后效性）
- 已知顺序，怎么dp。

其中dp部分其实是很简单的。

令 $ f(i,j) $ 为考虑前 $ i $ 个人，山高度为 $ j, $  最多有多少个人爬过山。

考虑加入一个 $ (s,a) $ ,用线段树优化即可， $ O(n\log n) $ ,因为不是精妙之处就不细讲了。

然后考虑排序。对于 $ (s_i,a_i) $ 和 $ (s_j,a_j) $ ,若 $ a_i\le s_j,a_j\le s_i $ 那么两者顺序无所谓，否则若 $ a_i\le s_j $ ,那么 $ i $ 应该在 $ j $ 前。

但容易发现这样没有传递性，无法排序。

然后我手搓出来了一个方案：若 $ \frac{a_i}{s_j}<\frac{a_j}{s_i} $ ,那么令 $ i $ 在 $ j $ 前。

传递性：其实就是按 $ a_i\times s_i $ 排序。然后若 $ a_i\le s_j $ 而 $ a_j> s_i $  那么也一定有 $ i $ 在 $ j $ 前。

总复杂度 $ O(n\log n) $ .

---

## 作者：_OMA_ (赞：6)

牛逼贪心题。

以 $\max(a_{i},s_{i})$ 为第一关键字， $s_{i}$ 为第二关键字从小到大排序。

然后依次枚举，能选就选，就是最优答案。

证明：

按 $\max(a,s)=a/s$ 分类讨论。

+ $\max_{i}=a_{i},\max_{j}=a_{j}$ ，不妨设 $a_{i}<a_{j}$ ，如果 $j$ 先上， $i$ 一定上不去，所以不如让 $i$ 先去试试。

+ $\max_{i}=a_{i},\max_{j}=s_{j}$ ，如果 $a_{i}>s_{j}$ 则同上， $i$ 先上， $j$ 一定上不去，所以不如让 $j$ 先去试试。 如果 $a_{i}\le s_{j}$ ，那么 $i$ 先上对 $j$ 显然不会有影响。

+ $\max_{i}=s_{i},\max_{j}=s_{j}$ ，不妨设 $s_{i}<s_{j}$ ，如果 $s_{i}<a_{j}$ ，显然是要 $i$ 先去试试，如果 $s_{i}>a_{j}$ ，先让 $i$ 上，对 $j$ 显然没有影响。

取等类似，此处不再展开。


``` cpp
#include<cstdio>
#include<cctype>
#include<iostream>
#include<algorithm>
using std::max;
using std::sort;
#define re register
const int MAX = 5e5+3;
#define long long long
#define scanf oma=scanf
#define freopen file freopen
int oma;
FILE* file;
namespace some
{
	struct stream
	{
		template<typename type>inline stream &operator >>(type &s)
		{
			bool w=0; s=0; char ch=getchar();
			while(!isdigit(ch)){ w|=ch=='-'; ch=getchar(); }
			while(isdigit(ch)){ s=(s<<1)+(s<<3)+(ch^48); ch=getchar(); }
			return s=w?-s:s,*this;
		}
	}cin;
	int ans;
	int n,d;
	struct data
	{
		int s,a;
		inline friend bool operator <(const data &x,const data &y)
		{ return max(x.s,x.a)==max(y.s,y.a)?x.s<y.s:max(x.s,x.a)<max(y.s,y.a); }
	}p[MAX];
	#define debug(s) printf("%s\n",s)
}using namespace some;
namespace OMA
{
	auto main = []() -> signed
	{
		//#define local
		#ifdef local
		debug("look here! if you want submit,please closed this");
		freopen("node.in","r",stdin); freopen("my.out","w",stdout);
		#endif
		cin >> n >> d;
		for(re int i=1; i<=n; i++)
		{ cin >> p[i].s >> p[i].a; }
		sort(p+1,p+1+n);
		for(re int i=1; i<=n; i++)
		{
			if(d<=p[i].s)
			{ ans++,d = max(d,p[i].a); }
		}
		printf("%d\n",ans);
		return 0;
	};
};
signed main()
{ return OMA::main(); }
```

---

## 作者：little_sheep917 (赞：4)

> 有 $n$ 个人要登山，每个人有两个值 $s_i,a_i$ .
>
> 设山原始的高度是 $h$ . 如果一个人的 $s_i$ 不小于 $h$ ，就可以登上一座山 , 等上这座山之后山的高度会变成 $\max(a_i,h)$ . 山原始的高度为 $d$ .
>
> 求怎样安排登山的顺序，使得能登山的人数最多 .
>
> $1\leq n\leq 500000,0\leq h\leq 10^9,0\leq s_i,a_i\leq 10^9$

#### sol1

观察到山的高度是在不断增加的 .

可以把人分为两类 $s_i\geq a_i,s_i<a_i$ .

$s_i\geq a_i$ 的人可以全部都选，观察得到，有些 $s_i<a_i$ 的人选了，会导致一些人选不了 .

但是选了 $s_i<a_i$ 的人一定没有选 $s_i\geq a_i$ 的人优 .

所以 $s_i\geq a_i$ 的人必须选 .

那么，现在的问题转化成，如何在全选 $s_i\geq a_i$ 的情况下，选最多的 $s_i<a_i$.

考虑用线段树维护 $f(i)$ 表示当前山的高度为 $i$ 时最多有过少个人登过山 . $i$ 可以离散化 。

将 $s_i<a_i$ 的人按照 $a_i$ 排序，依次选择 .

要实现区间最小值，单点修改的功能 .

时间复杂度 : $O(n\log n)$

空间复杂度 : $O(n)$

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9'){
		res=(res<<3)+(res<<1)+ch-'0';
		ch=getchar();
	}
	return res;
}
inline void print(int res){
	if(res==0){
		putchar('0');
		return;
	}
	int a[10],len=0;
	while(res>0){
		a[len++]=res%10;
		res/=10;
	}
	for(int i=len-1;i>=0;i--)
		putchar(a[i]+'0');
}
const int inf=1e9+10;
int n,d,m=0,ex=0;
int a[500010],s[500010];
int b[500010],cnt=0;
vector<int>v[500010];
int dp[500010];
multiset<pair<int,int> >st;
int tree[500010<<2],tag[500010<<2];
void build(int x,int l,int r){
	if(l==r){
		tree[x]=-inf;
		tag[x]=0;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	tree[x]=-inf;
	tag[x]=0;
}
inline void pd(int x){
	if(tag[x]==0)return;
	tree[x<<1]+=tag[x];
	tag[x<<1]+=tag[x];
	tree[x<<1|1]+=tag[x];
	tag[x<<1|1]+=tag[x];
	tag[x]=0;
}
void upd(int x,int l,int r,int pos,int val){
	if(l==r){
		tree[x]=max(tree[x],val);
		return;
	}
	pd(x);
	int mid=(l+r)>>1;
	if(pos<=mid)upd(x<<1,l,mid,pos,val);
	else upd(x<<1|1,mid+1,r,pos,val);
	tree[x]=max(tree[x<<1],tree[x<<1|1]);
}
void upd(int x,int l,int r,int cl,int cr,int val){
	if(l==cl&&r==cr){
		if(l!=r)pd(x);
		tree[x]+=val;
		tag[x]+=val;
		return;
	}
	pd(x);
	int mid=(l+r)>>1;
	if(cr<=mid)upd(x<<1,l,mid,cl,cr,val);
	else if(mid+1<=cl)upd(x<<1|1,mid+1,r,cl,cr,val);
	else{
		upd(x<<1,l,mid,cl,mid,val);
		upd(x<<1|1,mid+1,r,mid+1,cr,val);
	}
	tree[x]=max(tree[x<<1],tree[x<<1|1]);
}
int qry(int x,int l,int r,int cl,int cr){
	if(l==cl&&r==cr)return tree[x];
	pd(x);
	int mid=(l+r)>>1;
	if(cr<=mid)return qry(x<<1,l,mid,cl,cr);
	else if(mid+1<=cl)return qry(x<<1|1,mid+1,r,cl,cr);
	else return max(qry(x<<1,l,mid,cl,mid),qry(x<<1|1,mid+1,r,mid+1,cr));
}
int main(){
	n=read();d=read();
	b[cnt++]=d;
	for(int i=0;i<n;i++){
		int S=read(),A=read();
		if(S<d)continue;
		if(A<=d)ex++;
		else{
			a[m]=A;
			s[m]=S;
			m++;
			b[cnt++]=A;
		}
	}
	n=m;
	sort(b,b+cnt);
	cnt=unique(b,b+cnt)-b;
	for(int i=0;i<n;i++){
		int id=lower_bound(b,b+cnt,a[i])-b;
		v[id].push_back(i);
	}	
	build(1,0,cnt-1);
	dp[0]=0;
	upd(1,0,cnt-1,0,0);
	for(int i=1;i<cnt;i++){
		while(!st.empty()&&st.begin()->first<b[i]){
			upd(1,0,cnt-1,0,st.begin()->second-1,-1);
			st.erase(st.begin());
		}
		int mx=-1,tmp=0;
		for(int j=0;j<(int)v[i].size();j++){
			int id=v[i][j];
			if(a[id]>s[id]){
				mx=max(mx,s[id]);
			}else{
				tmp++;
			}
		}
		if(mx==-1){
			dp[i]=qry(1,0,cnt-1,0,i-1)+tmp;
		}
		else{
			int id=upper_bound(b,b+cnt,mx)-b-1;
			int mx1=qry(1,0,cnt-1,0,id)+tmp+1;
			int mx2=qry(1,0,cnt-1,0,i-1)+tmp;
			dp[i]=max(mx1,mx2);
		}
		upd(1,0,cnt-1,i,dp[i]);
		for(int j=0;j<(int)v[i].size();j++){
			int id=v[i][j];
			if(a[id]<=s[id]){
				upd(1,0,cnt-1,0,i-1,1);
				st.insert(make_pair(s[id],i));
			}
		}
	}
	int ans=-inf;
	for(int i=0;i<cnt;i++)ans=max(ans,dp[i]);
	print(ans+ex);
	return 0;
}
```

#### sol2

考虑 $f(i)$ 为山的高度为 $i$ 时，在 $s_i\geq a_i$ 的人全选的时候，能最多选择的 $s_i<a_i$ 的人数 .

依旧按照 $a_i$ 排序，判断当前的 $(s_i,a_i)$ 是否会影响 $s_i\geq a_i$ .

如果不会影响，则有转移 $f(s_i-1)+1\longrightarrow f(a_i)$ .

还有转移 $f(i-1)\longrightarrow f(i)$ .

山的高度可以离散化，转移的时候二分一下转移来的位置 .

时间复杂度 : $O(n\log n)$

空间复杂度 : $O(n)$


```c++
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9'){
		res=(res<<3)+(res<<1)+ch-'0';
		ch=getchar();
	}
	return res;
}
inline void print(int res){
	if(res==0){
		putchar('0');
		return;
	}
	int a[10],len=0;
	while(res>0){
		a[len++]=res%10;
		res/=10;
	}
	for(int i=len-1;i>=0;i--)
		putchar(a[i]+'0');
}
int n,d,cnt=0;
vector<pair<pair<int,int>,int> >v;
int dp[500010];
int main(){
	n=read();d=read();
	for(int i=0;i<n;i++){
		int s=read(),a=read();
		if(s<d)continue;
		if(a<=d)cnt++;
		else if(s>=a)v.push_back(make_pair(make_pair(s,a),0));
		else v.push_back(make_pair(make_pair(a,s),1));
	}
	sort(v.begin(),v.end());
	int mx=0;
	for(int i=0;i<(int)v.size();i++){
		if(!v[i].second)mx=max(mx,v[i].first.second);
		if(i!=0)dp[i]=max(dp[i],dp[i-1]);
		if(v[i].second){
			if(mx<=v[i].first.second){
				int pos=lower_bound(v.begin(),v.end(),
				make_pair(make_pair(v[i].first.second+1,-1),-1))-v.begin()-1;
				if(pos>=0)dp[i]=max(dp[i],dp[pos]+1);
				else dp[i]=max(dp[i],1);
			}
		}else cnt++;
	}
	print(dp[(int)v.size()-1]+cnt);
	return 0;
}
/*inline? ll or int? size? min max?*/
```

#### sol3

考虑贪心地选 $s_i>a_i$ 的人，按照 $(a_i,s_i)$ 排序，顺着选择下来，一定是最优的 .

那么，直接可以将人按照 $\max(s_i,a_i)$ 的顺序排序，顺着选择下来，能选就选，就是最优解 .

时间复杂度 : $O(n\log n)$

空间复杂度 : $O(n)$

```c++
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	int res=0;
	while(ch>='0'&&ch<='9'){
		res=(res<<3)+(res<<1)+ch-'0';
		ch=getchar();
	}
	return res;
}
inline void print(int res){
	if(res==0){
		putchar('0');
		return;
	}
	int a[10],len=0;
	while(res>0){
		a[len++]=res%10;
		res/=10;
	}
	for(int i=len-1;i>=0;i--)
		putchar(a[i]+'0');
}
int n,d;
int a[500010],s[500010];
int p[500010];
inline bool cmp(const int&x,const int&y){
	if(max(a[x],s[x])!=max(a[y],s[y]))return max(a[x],s[x])<max(a[y],s[y]);
	return s[x]<s[y];
}
int main(){
	n=read();d=read();
	for(int i=0;i<n;i++){
		s[i]=read();
		a[i]=read();
		p[i]=i;
	}
	sort(p,p+n,cmp);
	int ans=0;
	for(int i=0;i<n;i++){
		if(d<=s[p[i]]){
			ans++;
			d=max(d,a[p[i]]);
		}
	}
	print(ans);
	return 0;
}
/*inline? ll or int? size? min max?*/
```
写在最后，希望能去我的cnblog看一看哦
[link](https://www.cnblogs.com/suadwm/p/15509811.html)

---

## 作者：SunsetSamsara (赞：1)

## 分析

因为攀登难度只增不减，所以把所有初始技巧值 $s < d$ 的人都 ~~杀掉~~ 干掉。

然后我们可以考虑剩下的人。

按照普通的贪心思路，我们要把这些人排序然后贪心选择。

那么，该按什么排序呢？

通过简单地对数据的分析，发现似乎是以 $\max\left\{a_i, s_i\right\}$ 排序？

我们来尝试证明一下。

### 证明：

为了下面讨论的简洁，我们用 $v_i$ 表示第 $i$ 个人的权值 $\max\left\{a_i, s_i\right\}$

对于两个人 $i$ 和 $j$：

1. 如果 $v_i=a_i,v_j=a_j$，不妨设 $a_i < a_j$，如果 $j$ 先上，那么攀登难度和 $a_j$ 取 $\max$，大于等于 $a_j$。但是，因为 $s_i \le a_i < a_j$，所以如果 $j$ 先上去 $i$ 绝对上不去。但如果 $i$ 先上，那 $j$ 可能上得去。所以这种情况下把 $i$ 排在前面。
 
2. 如果 $v_i=a_i,v_j=s_j$：

$\hspace{1cm}$ 1. 如果 $a_i > s_j$，那么 $i$ 上去后 $j$ 一定上不去，$j$ 扔前面。

$\hspace{1cm}$ 2. 如果 $a_i \le s_j$，那么 $i$ 先上去和 $j$ 一点关系没有。

3. 如果 $v_i=s_i,v_j=s_j$：

$\hspace{1cm}$ 1. 如果 $s_i < a_j$，那么 $j$ 上去后 $i$ 绝对上不去，所以先把 $i$ 扔在前面。

$\hspace{1cm}$ 2. 如果 $s_i \ge a_j$，那么 $i$ 先上去和 $j$ 一点关系没有。

### 证毕

最后贪心能选就选。

### 代码

```cpp
#include <bits/stdc++.h> 
#define lld long long
using namespace std;
int n, d;
struct node {
	int a, s;
} a[500010];
bool cmp(const node & a, const node & b) {
	return max(a.a, a.s) != max(b.a, b.s) ? max(a.a, a.s) < max(b.a, b.s) : a.s < b.s;
	// 结论 
}
int main() {
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; ++ i)
		scanf("%d%d", &a[i].s, &a[i].a);
	sort(a + 1, a + n + 1, cmp);
	int cnt = 0;
	for (int i = 1; i <= n; ++ i)
		if (a[i].s >= d) {
			d = max(d, a[i].a);
			++ cnt;
			//贪心 
		}
	printf("%d\n", cnt);
}
```


---

## 作者：天梦 (赞：1)

这个题贪心非常妙，这个题其实我如果一个贪心策略与两个元素的大小都有关系，不妨考虑其最小值或最大值，或者加减乘除运算。这个题就是一个典型的考虑最大值的贪心。

先说贪心策略：按照 $\max(s,a)$ 排序，从小到大；然后再按照 $s$ 从小到大排序，最后按照 $a$。

我们考虑上面贪心策略的正确性：设 $\max(s_i,a_i)<\max(s_j,a_j)$

+ $s_i\ge a_i,s_j\ge a_j$

  这种情况不难发现，如果我们先让 $i$ 爬，$j$ 一定可以爬，但是如果我们先让 $j$ 爬，$i$ 可能不能爬，所以我们先让 $i$ 爬，不会使答案变劣。

+ $s_i\ge a_i,s_j<a_j$

  如果我们先让 $i$ 爬，然后 $j$ 一定可以爬，如果我们先让 $j$ 爬，$i$ 一定不能爬。我们先让 $i$ 爬，会使答案变优。

+ $s_i< a_i,s_j\ge a_j$

  如果我们先让 $i$ 爬，然后 $j$ 一定可以爬，但是如果我们先让 $j$ 爬，$i$ 可能不能爬，所以我们先让 $i$ 爬不会使答案变劣。

+ $s_i<a_i,s_j<a_j$

  如果我们先让 $i$ 爬，$j$ 可能能爬，如果 $j$ 先爬，则 $i$ 一定不能爬，让 $i$ 先爬，不会是答案变劣。

同理，经过同样的分析，我们可以得到当最值相等时我们让 $s$ 小的先爬不会使答案变劣。

排序直接跑就可以。

代码：

```c++
#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define int long long
#define uint unsigned int
#define ull unsigned long long
#define N 1000100
#define M number
using namespace std;

const int INF=0x3f3f3f3f;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int posi[N],a[N],b[N],n,m,c[N<<1],tail,t,Pre[N],Suf[N];

struct BIT{
    int p[N<<1];
    inline int lowbit(int x){return x&(-x);}
    inline void PreAdd(int w,int x){
        for(int i=w;i<=tail;i+=lowbit(i)) p[i]+=x;
    }
    inline int PreAsk(int w){
        int res=0;for(int i=w;i>=1;i-=lowbit(i)) res+=p[i];return res;
    }
    inline void SufAdd(int w,int x){
        for(int i=w;i>=1;i-=lowbit(i)) p[i]+=x;
    }
    inline int AskSuf(int w){
        int res=0;for(int i=w;i<=tail;i+=lowbit(i)) res+=p[i];return res;
    }
    inline void Clear(int n){
        for(int i=1;i<=n;i++) p[i]=0;
    }
}bit;

inline void Init(){
    read(n);read(m);
    for(int i=1;i<=n;i++) read(a[i]);
    for(int i=1;i<=m;i++) read(b[i]);
    for(int i=1;i<=n;i++) c[++tail]=a[i];
    for(int i=1;i<=m;i++) c[++tail]=b[i];
    sort(c+1,c+tail+1);int len=unique(c+1,c+tail+1)-c-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(c+1,c+len+1,a[i])-c;
    for(int i=1;i<=m;i++) b[i]=lower_bound(c+1,c+len+1,b[i])-c;
    sort(b+1,b+m+1);a[n+1]=INF;
}

inline void Solve(int l,int r,int Rl,int Rr){
    if(r<l) return;
    int mid=(l+r)>>1;
    Pre[Rl]=0;
    for(int i=Rl+1;i<=Rr;i++){
        Pre[i]=Pre[i-1];
        if(a[i-1]>b[mid]) Pre[i]++;
    }
    Suf[Rr]=0;
    for(int i=Rr-1;i>=Rl;i--){
        Suf[i]=Suf[i+1];
        if(b[mid]>a[i]) Suf[i]++;
    }
    int minn=INF,minp=-1;
    for(int i=Rl;i<=Rr;i++){
        if(minn>Pre[i]+Suf[i]){
            minn=Pre[i]+Suf[i];
            minp=i;
        }
    }
    posi[mid]=minp;
    Solve(l,mid-1,Rl,minp);
    Solve(mid+1,r,minp,Rr);
}

inline int GetAns(){
    // for(int i=1;i<=m;i++) printf("%d ",posi[i]);puts("");
    int now=0,ans=0;
    for(int i=1;i<=m;i++){
        while(now<posi[i]-1){
            now++;
            bit.SufAdd(a[now],1);
        }
        ans+=bit.AskSuf(b[i]+1);
    }
    // printf("ans=%d\n",ans);
    bit.Clear(tail);
    now=n+1;
    for(int i=m;i>=1;i--){
        while(now>posi[i]){
            now--;
            bit.PreAdd(a[now],1);
        }
        ans+=bit.PreAsk(b[i]-1);
    }
    // printf("ans=%d\n",ans);
    bit.Clear(tail);
    for(int i=n;i>=1;i--){
        ans+=bit.PreAsk(a[i]-1);
        bit.PreAdd(a[i],1);
    }
    // printf("ans=%d\n",ans);
    bit.Clear(tail);
    tail=0;
    return ans;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        Init();Solve(1,m,1,n+1);
        printf("%lld\n",GetAns());
    }
    return 0;
}
```



---

## 作者：StayAlone (赞：0)

不小心搞了个新做法。。。看起来要好理解一些。

先扔掉 $s$ 小于 $d$ 的部分。

考虑邻项交换，$i$ 优先于 $j$ 当且仅当先做 $i$ 还能做 $j$，同时先做 $j$ 就不能做 $i$ 了。记 $pre$ 表示之前所得的山高，则条件等价于 $\max\{a_i,pre\}\le s_j, \max\{a_j,pre\}>s_i$。显然 $s_i\ge pre$ 且 $s_j\ge pre$ 时才有比较的意义，故前式等价于 $a_i\le s_j,a_j>s_i$，相加得 $a_i+s_i\le a_j+s_j$。

那么按照这种方式排序，就得到了操作顺序。

后续考虑反悔贪心，用优先队列维护 $a$ 的值。

- 若可以做 $i$，插入 $a_i$，累加计数器；
- 否则，若删除堆顶后，可以做 $i$，则删除堆顶并插入 $a_i$；否则，跳过。

[AC record](https://codeforces.com/contest/1601/submission/324033323)

```cpp
int n, d, cnt;
 
struct node {
    int s, t;
 
    il bool operator < (const node &p) const {
        return s + t != p.s + p.t ? s + t < p.s + p.t : t < p.t;
    }
} a[MAXN];
 
il void solve() {
    read(n, d); int m = 0;
    priority_queue <int> q;
    rep1(i, 1, n) {
        read(a[i].s, a[i].t);
        if (a[i].s >= d) a[++m] = a[i];
    } sort(a + 1, a + 1 + m);
    #define get() (q.size() ? q.top() : 0)
    rep1(i, 1, m) {
        if (get() <= a[i].s) ++cnt, q.emplace(a[i].t);
        else if (q.top() > a[i].t) {
            int t = q.top(); q.pop();
            if (get() <= a[i].s) q.emplace(a[i].t);
            else q.emplace(t);
        }
    } printf("%d\n", cnt);
}
 
int main() {
    for (int T = 1; T--; ) solve();
    return 0;
}
```

---

