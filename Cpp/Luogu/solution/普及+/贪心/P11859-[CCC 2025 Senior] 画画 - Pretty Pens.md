# [CCC 2025 Senior] 画画 / Pretty Pens

## 题目背景

译自 CCC 2025 Senior T3。本题满分为 $15$。


## 题目描述


有 $n$ 支笔，$m$ 种颜色。第 $i$ 支笔的**颜色**为 $c_i$，**美丽度**为 $p_i$。

现在要用这些笔来画画。画会用到 $m$ 种颜色，所以要从每种颜色的笔中各选出一支，画的**美丽度**就是选出的笔的美丽度之和。

在下笔前，你可以选择**至多一支**笔，将这支笔的颜色改成 $[1,m]$ 中的任意一种。**画完后，这支笔的颜色将恢复为原本的颜色。**

有 $q$ 次操作：

- $\texttt{1}$ $i$ $x$：令 $c_i\gets x$。
- $\texttt{2}$ $i$ $y$：令 $p_i\gets y$。

对于 $i=1,2,\ldots,q+1$，求出：在完成前 $(i-1)$ 次操作后，用这些笔画出画的美丽度最大值。

再次强调，**画完一幅画后，这支笔的颜色将恢复为原本的颜色。**


## 说明/提示


#### 样例解释

- 样例 $1$ 解释：

起初，有三种颜色的笔：

- 颜色 $1$ 的笔的美丽度为 $3,6$。
- 颜色 $2$ 的笔的美丽度为 $7,9$。
- 颜色 $3$ 的笔的美丽度为 $4,9$。

如果不改变笔的颜色，画的最大美丽度为 $6+9+9=24$。

然而，将第 $4$ 支笔的颜色从 $2$ 改成 $1$ 可以获得 $7+9+9=25$ 的美丽度，这也是最优方案。

- 样例 $2$ 解释：

在第一次修改前和第二次修改前，选择第 $1,2$ 支笔是最优的。

在第二次修改后，选择第 $2,3$ 支笔是最优的。

#### 子任务

对于 $100\%$ 的数据，保证：

- $1\le m\le n\le 2\times 10^5$；
- $0\le q\le 2\times 10^5$；
- $1\le c_i,x\le m$；
- $1\le p_i,y\le 10^9$；
- $1\le i\le n$；
- 在任意时刻，每种颜色都至少有一支笔。

---

子任务 $0$ 为样例。

| $\text{Subtask}$ | $n\le$ |$ m$ | $q\le $ | 特殊性质 | 得分 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $2\times 10^5$ | $\le 2\times 10^5$ | $0$ | / | $5$ |
| $2$ | $2\times 10^5$ | $=1$ | $\le 2\times 10^5$ | / | $2$ |
| $3$ | $2\times 10^5$ | $=2$ | $\le 2\times 10^5$ | / | $2$ |
| $4$ | $2\times 10^5$ | $\le 10$ | $\le 2\times 10^5$ | / | $2$ |
| $5$ | $2\times 10^5$ | $\le 2\times 10^5$ | $\le 2\times 10^5$ | $\text{A}$ | $2$ |
| $6$ | $2\times 10^5$ | $\le 2\times 10^5$ | $\le 2\times 10^5$ | / | $2$ |

- 特殊性质 $\text{A}$：数据保证在任意时刻，$n$ 支笔的美丽度都是两两不同的。

## 样例 #1

### 输入

```
6 3 0
1 6
2 9
3 4
2 7
3 9
1 3```

### 输出

```
25```

## 样例 #2

### 输入

```
3 2 2
1 20
2 30
1 10
1 3 2
2 3 25```

### 输出

```
50
50
55```

# 题解

## 作者：Acit (赞：5)

**思路**

不难发现如果要更改颜色，应该用每种颜色的次大值的最大值替换最大值最小的那种颜色（用最大值替换后选择次大值与之是等价的）。

明白这一点后就很简单了，我们可以用 multiset 维护每种颜色的最大值，以及最大值和次大值集合，查询时简单判断即可（注释在代码里）。

**Code**


```cpp
#include<bits/stdc++.h>
#define int long long
#define SET multiset<int>::iterator
using namespace std;
const int N=2e5+10;
int n,m,q,totmx;
//totmx是最大值之和
int c[N],p[N];
multiset<int> st[N];
multiset<int> secmx,mx;
void delsec(int x){
	//在次大值集合中删除某颜色集合的次大值
	if(st[x].size()>1){
		SET T=st[x].end();
		T--;T--;
		secmx.erase(secmx.lower_bound(*T));
	}
}
void delmx(int x){
	//在最大值集合中删除某颜色集合的最大值
	if(st[x].size()>=1){
		SET T=st[x].end();
		T--;
		totmx-=(*T);
		mx.erase(mx.lower_bound(*T));
	}
}
void addsec(int x){
	//在次大值集合中加入某颜色集合的次大值
	if(st[x].size()>1){
		SET T=st[x].end();
		T--;T--;
		secmx.insert(*T);
	}
}
void addmx(int x){
	//在最大值集合中加入某颜色集合的最大值
	if(st[x].size()>=1){
		SET T=st[x].end();
		T--;
		totmx+=(*T);
		mx.insert(*T);
	}
}
void out(){
	int ans=totmx;
	int ssmx=0;
	if(secmx.size()>=1){
		SET T=secmx.end();
		T--;
		ssmx=*T;
		//ssmx是次大值的最大值
	}
	ans=max(ans,ans-*mx.begin()+ssmx);//判断更改颜色是否更优
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)cin>>c[i]>>p[i],st[c[i]].insert(p[i]);
	for(int i=1;i<=m;i++){
		addsec(i);addmx(i);
		//初始化集合
	}
	out();
	for(int i=1;i<=q;i++){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1){
			delsec(c[x]);delsec(y);delmx(c[x]);delmx(y);
			st[c[x]].erase(st[c[x]].lower_bound(p[x]));
			st[y].insert(p[x]);
			addsec(c[x]);addsec(y);addmx(c[x]);addmx(y);
			c[x]=y;
			//注意在更改前删去更改集合的最大值和次大值，改完后加回来
		}
		else if(op==2){
			delsec(c[x]);delmx(c[x]);
			st[c[x]].erase(st[c[x]].lower_bound(p[x]));
			st[c[x]].insert(y);
			addsec(c[x]);addmx(c[x]);
			p[x]=y;
		}
		out();
	}
	return 0;
}

```

---

## 作者：_xzhdsnh1364 (赞：4)

考试时盯了一两个小时，最终还是听同学思路写出来的。

# 思路

我们将每个颜色分为几个集合，记得是可重的，我有个同学就这样写挂的。然后里面存入美丽度。

这里我们先讲述查询操作。我们看到题目中说了，这道题在每次查询的时候，可以修改任意一支笔的颜色，那究竟怎么修改呢？我们将最大值最小的和次大值最大的给挑出来，这里就需要再用两个新集合存着。有童鞋会问了，为什么要挑这俩出来呢？下面给出证明：

我们先挑出两个颜色集合，分别叫 $t1$ 和 $t2$，我们分成两种情况：

1. $t1$ 的最大值转入 $t2$。
2. $t1$ 的次大值转入 $t2$。

第一种情况：$-$ $t1$ 最大值 $+$ $t1$ 最大值 $-$ $t2$ 最大值 $+$ $t1$ 次大值。

第二种情况：$-$ $t2$ 最大值 $+$ $t1$ 次大值。

当然，$t1$ 次大值 $<$ $t2$ 最大值时便没有必要这样操作了。

接下来看修改操作，第一个修改，将对应的那一个要修改的挑出来再将它对应的丢入相应颜色的集合中。第二个修改，直接将他删除，改值再入集合就行了。

# 代码时间


```cpp
#include<bits/stdc++.h>
typedef long long ll;
#define mi multiset<ll>::iterator
using namespace std;
const int N = 2e5 + 5;
ll n , m , q , c[N] , p[N] , sum , op , d , x;
multiset<ll>st[N] , ansf , anss;
ll query(){
    mi it = ansf.begin();
    ll r1 = *it;
    mi it2 = anss.end();
    if(anss.empty())return sum;
    it2--;
    ll r2 = *it2;
    if(r2 - r1 < 0)return sum;
    return sum + r2 - r1;
}
void del1(int x){
	if(st[x].size() < 1)return;
	mi it = st[x].end();
	it--;
	sum -= *it;
	ansf.erase(ansf.find(*it));
}
void del2(int x){
	if(st[x].size() < 2)return;
	mi it = st[x].end();
	it--;
	it--;
	anss.erase(anss.find(*it));
}
void ins1(int x){
	if(st[x].size() < 1)return;
	mi it = st[x].end();
    it--;
    ansf.insert(*it);
    sum += *it;
}
void ins2(int x){
	if(st[x].size() < 2)return;
	mi it = st[x].end();
    it--;
    it--;
    anss.insert(*it);
}
int main(){
    cin >> n >> m >> q;
    for(int i = 1;i <= n;i++){cin >> c[i] >> p[i];st[c[i]].insert(p[i]);}
    for(int i = 1;i <= m;i++){ins1(i);ins2(i);}
    cout << query() << '\n';
    for(int i = 1;i <= q;i++){
		cin >> op >> d >> x;
		if(op == 1){
			del1(c[d]) , del1(x) , del2(c[d]) , del2(x);
			st[c[d]].erase(st[c[d]].find(p[d]));
			st[x].insert(p[d]);
			ins1(c[d]) , ins1(x) , ins2(c[d]) , ins2(x);
			c[d] = x;
		}else{
			del1(c[d]) , del2(c[d]);
			st[c[d]].erase(st[c[d]].find(p[d]));
			st[c[d]].insert(x);
			ins1(c[d]) , ins2(c[d]);
			p[d] = x;
		}
		cout << query() << '\n';
    }
    return 0;
}
```

---

## 作者：madfallen (赞：3)

STL 水题。

显然每次计算时比较每种颜色中最大值的最小值和次大值的最大值，取大者做出决策即可。

于是我们开 multiset 维护每种颜色中的值，以及上述两个需要比较的量即可。

注意 multiset 的使用细节。

```c++
#include<iostream>
#include<cstdio>
#include<set>
#define int long long
using namespace std;
const int N=2e5;
multiset<int>s[N+5];
multiset<int>maxa,mina;//次大值的最大值，最大值的最小值
int c[N+5],p[N+5];
int n,m,q;
int sum=0;//最大值之和
inline int f(){
	if(maxa.empty())return sum;
	int mm=*--maxa.end(),nn=*mina.begin();
	return sum-nn+max(mm,nn);
}
inline void e1(int u){
	mina.erase(mina.find(u));//在重复元素中只删除一个
}
inline void e2(int u){
	maxa.erase(maxa.find(u));
}
signed main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",c+i,p+i);
		s[c[i]].insert(p[i]);
	} 
	for(int i=1;i<=m;i++)sum+=*--s[i].end();
	for(int i=1;i<=m;i++){
		mina.insert(*--s[i].end());
		if(s[i].size()>1)maxa.insert(*----s[i].end());
	}
	cout<<f()<<endl;
	while(q--){
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1){
			sum-=*--s[c[x]].end();
			e1(*--s[c[x]].end());
			if(s[c[x]].size()>1)e2(*----s[c[x]].end());
			s[c[x]].erase(s[c[x]].find(p[x]));
			sum+=*--s[c[x]].end();
			mina.insert(*--s[c[x]].end());
			if(s[c[x]].size()>1)maxa.insert(*----s[c[x]].end());
			c[x]=y;
			sum-=*--s[c[x]].end();
			e1(*--s[c[x]].end());
			if(s[c[x]].size()>1)e2(*----s[c[x]].end());
			s[c[x]].insert(p[x]);
			sum+=*--s[c[x]].end();
			mina.insert(*--s[c[x]].end());
			if(s[c[x]].size()>1)maxa.insert(*----s[c[x]].end());
		}
		else{
			sum-=*--s[c[x]].end();
			e1(*--s[c[x]].end());
			if(s[c[x]].size()>1)e2(*----s[c[x]].end());
			s[c[x]].erase(s[c[x]].find(p[x]));
			p[x]=y;
			s[c[x]].insert(p[x]);
			sum+=*--s[c[x]].end();
			mina.insert(*--s[c[x]].end());
			if(s[c[x]].size()>1)maxa.insert(*----s[c[x]].end());
		}
		cout<<f()<<endl;
	}
}
```

---

## 作者：chenxi2009 (赞：2)

## 思路
考虑维护每种颜色最漂亮画笔的可重集合（令其为 $f$）。由于可以转变一支画笔的颜色，考虑再维护每种颜色第二漂亮画笔的可重集合（令其为 $s$）。

当需要答案时，比较 $f$ 最小元素和 $s$ 最大元素的大小，如果后者大那么我们可以让后者的颜色变得与前者相同并替换，答案时替换后（如果有）$f$ 的元素和。注意这个替换是临时的。

具体实现考虑维护每一种颜色对应画笔的集合（记为 $p=(p_1,p_2,\cdots,p_M)$），每一次修改前先把可能影响到的 $p_i$ 对 $f$、$s$ 和答案的贡献去除，修改完后再加回去。

具体实现可以用 multiset，时间复杂度 $O((N+M+Q)\log(N+M))$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,c[300000],p[300000],op,x,y;
long long ans;
multiset<int>s[300000],cry,sc;//cry 为 f，sc 为 s 
inline void erase_element(multiset<int>&x,int y){if(x.lower_bound(y) != x.end()) x.erase(x.lower_bound(y));}//从一个多重集合 x 中删去一个元素 y 
inline void add_contribution(int x){//累计 p_x 对答案的贡献 
	ans += *(-- s[x].end()),cry.insert(*(-- s[x].end()));//最大元素的累计总和并加入 f 
	if(s[x].size() > 1) sc.insert(*(-- -- s[x].end()));//次大元素加入 s 
}
inline void erase_contribution(int x){//去除 p_x 对答案的贡献 
	ans -= (*(-- s[x].end())),erase_element(cry,*(-- s[x].end()));
	if(s[x].size() > 1) erase_element(sc,*(-- -- s[x].end()));
} 
inline void print_ans(){
	if(sc.size() && cry.size()) printf("%lld\n",ans + max(0,(*(-- sc.end())) - (*cry.begin())));//这里两个都要判，空的情况是有的，搬到洛谷因此 RE 了
	else printf("%lld\n",ans);
}//输出答案
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i = 1;i <= n;i ++) scanf("%d%d",&c[i],&p[i]);
	for(int i = 1;i <= n;i ++) s[c[i]].insert(p[i]);
	for(int i = 1;i <= m;i ++) add_contribution(i);
	print_ans();
	for(int i = 1;i <= q;i ++){
		scanf("%d%d%d",&op,&x,&y);
		if(op != 1 || c[x] != y){
			erase_contribution(c[x]),erase_element(s[c[x]],p[x]);
			if(op == 1) add_contribution(c[x]),erase_contribution(y),c[x] = y,s[y].insert(p[x]);
			else p[x] = y,s[c[x]].insert(y);
			add_contribution(c[x]);
		}
		print_ans();
	}
	return 0;
}
```

---

## 作者：canwen (赞：2)

只有一次修改的机会，那么就有两种方案：

记 $f_i$ 为颜色为 $i$ 的画笔集合，每支画笔记录两个值，一个是它的美丽度 $fst$，一个是它的编号 $snd$。
- 将所有颜色中的最大相加。

- 将所有颜色**次大**中的**最大**，替换所有颜色的**最大美丽度**中的**最小**。

以上很好想，难在维护。

维护可重集合 $maxn$ 存储每个颜色的美丽度最大的画笔，$maxn1$ 存储每个颜色的美丽度次大的画笔（没有次大就不存）。

定义 $sum$ 表示所有颜色中最大的美丽度之和，先预处理出来。

其余见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mk make_pair
#define pint pair<int,int>
#define fst first
#define snd second
const int N = 2e5 + 5;
int n,m,c[N],p[N];
multiset <pint> maxn,maxn1,f[N];
int sum;
int in(){
	char a = getchar();
	int k=0,kk=1;
	while(!isdigit(a)){
		if(a=='-') kk=-1;
		a=getchar(); 
	}
	while(isdigit(a)){
		k=k*10+a-'0',a=getchar();
	}
	return k*kk;
}
void out(int a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) out(a/10);
	putchar('0'+a%10);
}
void update1(int x){
	// 更新颜色 x 的最大值在 maxn 中 
	sum += (*--f[x].end()).fst;
	maxn.insert(*--f[x].end());
}
void update2(int x){
	// 更新颜色 x 的次大值在 maxn 中 
	if(f[x].size() > 1){
		maxn1.insert(*----f[x].end());
	}
}
void del(int x){
	// 删除颜色 x 的最大值在 maxn 中，次大值在 maxn1 中 
	sum -= (*--f[x].end()).fst;
	maxn.erase(maxn.find(*--f[x].end()));
	if(f[x].size() > 1) maxn1.erase(maxn1.find(*----f[x].end()));
}
void print_ans(){
	// 打印答案 
	int ans = sum;
	if(maxn1.size()) ans = max(ans,ans+(*--maxn1.end()).fst-(*maxn.begin()).fst);
	out(ans), putchar('\n');
}
signed main(){
	n=in(),m=in();
	int q = in();
	for(int i=1;i<=n;i++){
		c[i]=in(), p[i]=in();
		f[c[i]].insert(mk(p[i],i));
	}
	for(int i=1;i<=m;i++){
		maxn.insert(*--f[i].end()), sum += (*--f[i].end()).fst;
		if(f[i].size() > 1) maxn1.insert(*----f[i].end());
	}
	print_ans();
	while(q--){
		int op=in(),i=in(),x=in();
		if(op == 1){
			// c_i <- x
			del(c[i]);
			f[c[i]].erase(f[c[i]].find(mk(p[i],i))); // 删掉最大，次大 
			update1(c[i]), update2(c[i]); // 更新 
			del(x); 
			c[i] = x;
			f[x].insert(mk(p[i],i));// 加进新的颜色集合中 
			update1(x), update2(x); // 更新 
		}else{
			del(c[i]); // 删掉最大，次大 
			f[c[i]].erase(f[c[i]].find(mk(p[i],i))); // 删掉过时的自己 
			p[i] = x;
			f[c[i]].insert(mk(p[i],i));
			update1(c[i]), update2(c[i]); // 更新 
		}
		print_ans();
	}
	return 0;
}
```

[通过记录](https://www.luogu.com.cn/record/209514035)。

---

## 作者：run_away (赞：2)

## 题意

$n$ 支有颜色和权值的笔。$q$ 次修改，每次修改一支笔的颜色或权值，修改完后查询所有颜色最大权值的和，且每次修改后可以选择一支笔改变它的颜色，每次输出后回复原色。

## 分析

可以维护每个颜色所对应的权值，不考虑修改的那支笔时，我们只需要求最大值即可，用 `multiset`。

考虑何时会选择主动修改一支笔的颜色，看看样例可以发现当一种颜色的最大值很小，而另外一种颜色有一个较大的值，就会选择修改。

这样需要额外维护所有颜色的最大值和次大值，当“最大值”的最小值小于“次大值”的最大值时，用大的替换小的是最优的。

再开两个 `multiset` 分别维护即可，注意 `fir` 一定不为空而 `sec` 不一定为空，所以**一定要判空**。

复杂度 $O(q\log n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<ll,ll> pll;
using namespace std;
static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
#define dbg(x) cout<<#x<<": "<<x<<"\n"
#define usetime() printf("time: %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}short top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
namespace tobe{
    const ll maxn=2e5+5,mod=1e9+7;
	ll n,m,q;
	pair<ll,ll>pen[maxn];
	multiset<ll>col[maxn],fir,sec;
	inline void mian(){
		n=read(),m=read(),q=read();
		for(ll i=1;i<=n;++i){
			pen[i]={read(),read()};
			col[pen[i].first].insert(pen[i].second);
		}
		for(ll i=1;i<=m;++i){
			if(col[i].empty())continue;
			auto it=col[i].rbegin();
			fir.insert(*it),++it;
			if(col[i].size()>1)sec.insert(*it);
		}
		ll sum=0;
		for(auto it=fir.begin();it!=fir.end();++it){
			sum+=*it;
		}
		if(!sec.empty()&&*fir.begin()<*sec.rbegin()){
			write(sum+*sec.rbegin()-*fir.begin());
		}
		else write(sum);
		while(q--){
			ll op=read(),p=read(),k=read();
			if(op==1){
				ll c=pen[p].first;
				auto it1=col[c].rbegin();
				sum-=*it1,fir.erase(fir.lower_bound(*it1)),++it1;
				if(col[c].size()>1)sec.erase(sec.lower_bound(*it1));
				auto it2=col[k].rbegin();
				if(col[k].size())sum-=*it2,fir.erase(fir.lower_bound(*it2)),++it2;
				if(col[k].size()>1)sec.erase(sec.lower_bound(*it2));
				col[c].erase(col[c].lower_bound(pen[p].second));
				col[k].insert(pen[p].second);
				pen[p].first=k;
				it1=col[c].rbegin();
				if(col[c].size())sum+=*it1,fir.insert(*it1),++it1;
				if(col[c].size()>1)sec.insert(*it1);
				it2=col[k].rbegin();
				sum+=*it2,fir.insert(*it2),++it2;
				if(col[k].size()>1)sec.insert(*it2);
			}
			else{
				ll c=pen[p].first;
				auto it=col[c].rbegin();
				sum-=*it,fir.erase(fir.lower_bound(*it)),++it;
				if(col[c].size()>1)sec.erase(sec.lower_bound(*it));
				col[c].erase(col[c].lower_bound(pen[p].second));
				col[c].insert(k);
				it=col[c].rbegin();
				sum+=*it,fir.insert(*it),++it;
				if(col[c].size()>1)sec.insert(*it);
				pen[p].second=k;
			}
			if(!sec.empty()&&*fir.begin()<*sec.rbegin()){
				write(sum+*sec.rbegin()-*fir.begin());
			}
			else write(sum);
		}
	}
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ll t=1;
    while(t--)tobe::mian();
    fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

## 作者：Night_sea_64 (赞：2)

最终的答案一定是 所有颜色内部美丽度最大值 之和，然后可以选择用 所有颜色内部美丽度次大值 的最大值替换 所有颜色内部美丽度最大值 的最小值。

所以直接 multiset 按颜色分类维护美丽度。再开两个 multiset 分别维护所有颜色内部的最大值和次大值即可。

时间复杂度 $O(q\log q)$。

```cpp
#include<iostream>
#include<set>
using namespace std;
int n,m,q,c[200010],p[200010];
struct node{int id,x;};
bool operator<(const node &x,const node &y){
    if(x.x!=y.x)return x.x>y.x;
    return x.id<y.id;
}
multiset<node>s[200010],a,b;
long long sum=0;
void del(int col)
{
    auto pos=a.lower_bound(*s[col].begin());
    sum-=s[col].begin()->x;
    a.erase(pos);
    if(s[col].size()>1)
    {
        pos=b.lower_bound(*next(s[col].begin()));
        b.erase(pos);
    }
}
void add(int col)
{
    sum+=s[col].begin()->x;
    a.insert(*s[col].begin());
    if(s[col].size()>1)
    {
        b.insert(*next(s[col].begin()));
    }
}
int main()
{
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)
    {
        cin>>c[i]>>p[i];
        s[c[i]].insert({i,p[i]});
    }
    for(int i=1;i<=m;i++)
    {
        add(i);
    }
    if(b.size()>0)
    {
        if(b.begin()->x>prev(a.end())->x)
        {
            cout<<sum-prev(a.end())->x+b.begin()->x<<endl;
        }
        else cout<<sum<<endl;
    }
    else cout<<sum<<endl;
    while(q--)
    {
        int op,i,x;
        cin>>op>>i>>x;
        if(op==1)
        {
            auto pos=s[c[i]].lower_bound({i,p[i]});
            del(c[i]);
            del(x);
            s[x].insert(*pos);
            s[c[i]].erase(pos);
            add(c[i]);
            add(x);
            c[i]=x;
        }
        if(op==2)
        {
            auto pos=s[c[i]].lower_bound({i,p[i]});
            del(c[i]);
            s[c[i]].insert({i,x});
            s[c[i]].erase(pos);
            add(c[i]);
            p[i]=x;
        }
        if(b.size()>0)
        {
            if(b.begin()->x>prev(a.end())->x)
            {
                cout<<sum-prev(a.end())->x+b.begin()->x<<endl;
            }
            else cout<<sum<<endl;
        }
        else cout<<sum<<endl;
    }
    return 0;
}
```

---

## 作者：ycy1124 (赞：1)

### 前置知识
[multiset 的性质与操作。](https://www.cnblogs.com/miao-jc/p/18171506)
### 题意
你有 $m$ 种颜色的画笔，你希望在一幅画作中使用每种颜色的画笔各一支，每只画笔还会有一个美丽值 $p_i$ 你希望你选出来的所有画笔的美丽值之和最大。在每次绘画之前你可以选择至多一支画笔将其改成另一种颜色（也可以不选），这支笔在画完这次画之后便会变回原来的颜色。现在有两种操作，操作一可以修改一只画笔的颜色，操作二可以修改一支画笔的美丽值，要求在每次操作后输出你所能画出的画的最大美丽值。
### 思路
我们先不考虑我们可以更换画笔颜色的操作，我们发现我们每次肯定会选取每种颜色美丽值最高的画笔。我们可以对每一种颜色开一个 multiset 去维护每种颜色的画笔的最大美丽值以及修改操作。

接下来考虑我们可以在每次绘画前修改某一支画笔的颜色。我们考虑什么时候这个操作会让我们的答案变优，我们会选取某一种颜色的画笔的次大值去替换掉某一种颜色的画笔的最大值。为什么呢，首先不难证明我们要么拿最大值去换要么拿次大值去换。而我们拿最大值去换后次大值一定会被取，所以我们拿次大值去换一定不劣。于是我们每次只需要找到所有颜色的画笔的次大值中的最大值去和所有颜色的最大值的最小值去比较取哪个更优。这个也很好用 multiset 维护。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
multiset<int>s[N], ma, mma;
int p[N], c[N], n, m, q, ans;
signed main()
{
	ios :: sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> q;
	for(int i = 1; i <= m; i ++)
	{
		s[i].insert(0);
		s[i].insert(0);
	}
	for(int i = 1; i <= n; i ++)
	{
		cin >> c[i] >> p[i];
		s[c[i]].insert(p[i]);
	}
	for(int i = 1; i <= m; i ++)
	{
		auto it = s[i].end();
		it --;
		ans += *it;
		mma.insert(*it);
		it --;
		ma.insert(*it);
	}
	auto it = ma.end();
	it --;
	cout << max(ans + *it - *mma.begin(), ans) << '\n';
	while(q --)
	{
		int op, x, y;
		cin >> op >> x >> y;
		if((op == 1 && c[x] == y) || (op == 2 && p[x] == y))//判掉避免出问题
		{
			it = ma.end();
			it --;
			cout << max(ans + *it - *mma.begin(), ans) << '\n';
			continue;
		}
		if(op == 1)
		{
			auto i = s[c[x]].end(), j = s[y].end();
			i --, j --;
			ans -= *i;
			ans -= *j;
			mma.erase(mma.lower_bound(*i));//首先更新最大值
			mma.erase(mma.lower_bound(*j));
			i --, j --;
			ma.erase(ma.lower_bound(*i));//更新次大值
			ma.erase(ma.lower_bound(*j));
			s[y].insert(p[x]);
			s[c[x]].erase(s[c[x]].lower_bound(p[x]));//更新这种颜色
			i = s[c[x]].end(), j = s[y].end();
			i --, j --;
			mma.insert(*i);
			mma.insert(*j);
			ans += *i;//我们只需要给答案加上被修改掉的部分
			ans += *j;
			i --, j --;
			ma.insert(*i);
			ma.insert(*j);
			it = ma.end();
			it --;
			cout << max(ans + *it - *mma.begin(), ans) << '\n';
			c[x] = y;//最后别忘了修改数组
		}
		else
		{//本质与上一个操作相同
			auto i = s[c[x]].end();
			i --;
			mma.erase(mma.lower_bound(*i));
			ans -= *i;
			i --;
			ma.erase(ma.lower_bound(*i));
			s[c[x]].erase(s[c[x]].lower_bound(p[x]));
			s[c[x]].insert(y);
			i = s[c[x]].end();
			i --;
			mma.insert(*i);
			ans += *i;
			i --;
			ma.insert(*i);
			it = ma.end();
			it --;
			cout << max(ans + *it - *mma.begin(), ans) << '\n';//换了颜色不一定最优
			p[x] = y;
		}
	}
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/231282918)。

---

## 作者：Your_Name (赞：1)

## 题解
发现答案就是这两个的最大值：
* 每个颜色的最大值之和
* 每个颜色的最大值之和加上所有颜色最大的次大值减去所有颜色最小的最大值。

解释一下：

首先我不改颜色那答案就是第一种情况。

然后，如果我改，那么就是让我的某个原来被最大值盖过的次大值出来贡献，那相对应的，也要有一个原来的最大值被我替代。

所以我新的贡献就是我选出的次大值减去我选的要改的那个颜色的最大值。

如果我想让贡献尽可能大，那么只要选出的次大最大，选的那个颜色的最大最小即可。

具体来说，我们只要维护最大的次大和所有颜色最小的最大值即可。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N = 2e5 + 10;
LL n, m, q, c[N], p[N], sum;
multiset<LL> s[N], top, cd;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> q;
    for(LL i = 1; i <= n; i ++){
        cin >> c[i] >> p[i];
        s[c[i]].insert(p[i]);
    }
    for(LL i = 1; i <= m; i ++){
        sum += *s[i].rbegin();//原始的最大
        if(s[i].size() >= 2){
            auto j = s[i].end();
            j --, j --;
            cd.insert(*j);//次大
        }
        top.insert(*s[i].rbegin());//最大
    }
    LL ans = sum;//不改
    if(!cd.empty())ans += max(0ll, *cd.rbegin() - *top.begin());//改
    cout << ans << '\n';
    for(LL i = 1; i <= q; i ++){
        LL op, x, y;
        cin >> op >> x >> y;
        if(op == 1){
            if(c[x] != y){
                if(s[c[x]].size() >= 2){
                    auto j = s[c[x]].rbegin();
                    j ++;
                    if(!cd.empty())cd.erase(cd.find(*j));
                }//删掉次大
                if(!top.empty())top.erase(top.find(*s[c[x]].rbegin()));//删掉原来的最大
                if(!s[c[x]].empty())sum -= *s[c[x]].rbegin();//更新最大值之和
                if(!s[c[x]].empty())s[c[x]].erase(s[c[x]].find(p[x]));//删掉这个颜色
                if(!s[c[x]].empty())top.insert(*s[c[x]].rbegin());//加上新的
                if(!s[c[x]].empty())sum += *s[c[x]].rbegin();//更新最大值之和
                if(s[c[x]].size() >= 2){
                    auto j = s[c[x]].rbegin();
                    j ++;
                    cd.insert(*j);
                }//加上新的次大
                c[x] = y;
                if(!top.empty())top.erase(top.find(*s[c[x]].rbegin()));
                if(!s[c[x]].empty())sum -= *s[c[x]].rbegin();
                if(s[c[x]].size() >= 2){
                    auto j = s[c[x]].rbegin();
                    j ++;
                    if(!cd.empty())cd.erase(cd.find(*j));
                }
                s[c[x]].insert(p[x]);
                top.insert(*s[c[x]].rbegin());
                sum += *s[c[x]].rbegin();
                if(s[c[x]].size() >= 2){
                    auto j = s[c[x]].rbegin();
                    j ++;
                    cd.insert(*j);
                }
            }//同上
            LL ans = sum;
            if(!cd.empty())ans += max(0ll, *cd.rbegin() - *top.begin());
            cout << ans << '\n';
        }else{
            if(p[x] != y){
                if(s[c[x]].size() >= 2){
                    auto j = s[c[x]].rbegin();
                    j ++;
                    if(!cd.empty())cd.erase(cd.find(*j));
                }
                top.erase(top.find(*s[c[x]].rbegin()));
                sum -= *s[c[x]].rbegin();
                s[c[x]].erase(s[c[x]].find(p[x]));
                p[x] = y;
                s[c[x]].insert(p[x]);
                sum += *s[c[x]].rbegin();
                top.insert(*s[c[x]].rbegin());
                if(s[c[x]].size() >= 2){
                    auto j = s[c[x]].rbegin();
                    j ++;
                    cd.insert(*j);
                }
            }//同理
            LL ans = sum;
            if(!cd.empty())ans += max(0ll, *cd.rbegin() - *top.begin());
            cout << ans << '\n';
        }
    }
    return 0;
}
```
 _完结撒花。_

---

