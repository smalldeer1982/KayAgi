# A Heap of Heaps

## 题目描述

Andrew skipped lessons on the subject 'Algorithms and Data Structures' for the entire term. When he came to the final test, the teacher decided to give him a difficult task as a punishment.

The teacher gave Andrew an array of $ n $ numbers $ a_{1} $ , $ ... $ , $ a_{n} $ . After that he asked Andrew for each $ k $ from 1 to $ n-1 $ to build a $ k $ -ary heap on the array and count the number of elements for which the property of the minimum-rooted heap is violated, i.e. the value of an element is less than the value of its parent.

Andrew looked up on the Wikipedia that a $ k $ -ary heap is a rooted tree with vertices in elements of the array. If the elements of the array are indexed from 1 to $ n $ , then the children of element $ v $ are elements with indices $ k(v-1)+2 $ , $ ... $ , $ kv+1 $ (if some of these elements lie outside the borders of the array, the corresponding children are absent). In any $ k $ -ary heap every element except for the first one has exactly one parent; for the element 1 the parent is absent (this element is the root of the heap). Denote $ p(v) $ as the number of the parent of the element with the number $ v $ . Let's say that for a non-root element $ v $ the property of the heap is violated if $ a_{v}&lt;a_{p(v)} $ .

Help Andrew cope with the task!

## 说明/提示

Pictures with the heaps for the first sample are given below; elements for which the property of the heap is violated are marked with red.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF538F/93339df0bb68880a8de271a66f4adc3a53f4751c.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF538F/09a247d73f8afabd6ccdbd7561ab6cba57bb254c.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF538F/3c0e248cafc99373f75eddf4c10072a9aa8272ce.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF538F/7432dc3933cf2b180164676f7f3edca3f7ec9ee0.png)In the second sample all elements are equal, so the property holds for all pairs.

## 样例 #1

### 输入

```
5
1 5 4 3 2
```

### 输出

```
3 2 1 0
```

## 样例 #2

### 输入

```
6
2 2 2 2 2 2
```

### 输出

```
0 0 0 0 0
```

# 题解

## 作者：应吟吟 (赞：7)

###### 安利一下[本蒟蒻的博客](https://yingyinyin.blog.luogu.org/#)

### 需要部分分的同学[戳我](https://www.luogu.org/problemnew/show/U64420)呀

# 方法①

## 树状数组

- 对于$20\%$的数据我也不知道怎么做

- 对于$30\%$的数据方法跟正解有关，后面再讲

- 对于$50\%$的数据请先看提示第二条，然后我们就可以对于每一个堆枚举所有的点，暴力计算不合法的数量

- ~~个人认为以上所有分数都应该拿到~~

- 对于$30\%$的数据，我们考虑来枚举父亲，计算每一个父亲对于答案的贡献

- 首先我们可以发现一个父亲的儿子是连续的一段，对于$i$叉堆，节点$j$的儿子为$i*j+2-i$到$i*j+1$，可以直接枚举每个父亲的贡献。

- 暴力计算贡献是$O(n)$级别的，对于$i$叉堆，父亲的个数为$\dfrac{n}{i}$，因为提示三，所以总的个数为$nlog_n$个，所以复杂度为$O(n^2log_2n)$

- ~~其实因为均摊的原因还是$O(n^2)$的~~

***

此上，都是部分分的写法，

接下来，就是$100\%$的写法啦。

- 计算贡献本质上就是求一段区间内小于一个数的数量

- 然后就可以欢快的用数据结构进行优化了。

- 我们考虑用树状数组，将元素位置为下标，按元素大小一个个插入，这样每次计算只要$O(logn)$的复杂度

- 然后总的复杂度为$O(nlog^2n)$

```cpp
#include <bits/stdc++.h>

#define Max 200005

using namespace std;

inline char gc()
{
	static char buf[100000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
#define getchar gc
inline int read()
{
	int x=0;
	char ch=gc();
	bool positive=1;
	for(; !isdigit(ch); ch=gc())if(ch=='-')positive=0;
	for(; isdigit(ch); ch=gc())x=x*10+ch-'0';
	return positive?x:-x;
}

inline void write(int x)
{
	if(x<0)x=-x,putchar('-');
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

inline void writeln(int x)
{
	write(x);
	puts("");
}//输入输出优化

struct node
{
	int a,b;
} s[Max];

int n,ans[Max],c[Max];

inline bool cmp(node x,node y)
{
	if(x.a!=y.a)
	{
		return x.a<y.a;
	}
	else
	{
		return x.b<y.b;
	}
}//cmp函数，sort用

inline int lowbit(int x)
{
	return x&-x;
}

inline void add(int x)
{
	while(x<=n)
	{
		c[x]++;
		x+=lowbit(x);
	}
}

inline int sum(int x)
{
	int ans=0;
	while(x>0)
	{
		ans+=c[x];
		x-=lowbit(x);
	}
	return ans;
}

int main()
{
	n=read();
	for(int i=1; i<=n; i++)
	{
		s[i].a=read();
		s[i].b=i;
	}
	sort(s+1,s+n+1,cmp);
	for(int i=1; i<=n; i++)
	{
		add(s[i].b);
		for(int j=1; j<n&&s[i].b*j-j+2<=n; j++)
		{
			ans[j]+=sum(min(n,s[i].b*j+1))-sum(s[i].b*j-j+1);
		}
	}
	for(int i=1; i<n; i++)
	{
		write(ans[i]);
		putchar(' ');
	}
	return 0;
}

```

# 方法②

## ~~找规律~~ 呸,  暴力

- 我们可以列一个表

- ![](https://cdn.luogu.com.cn/upload/pic/53247.png )

- 我们定义在$i$叉堆中$j$的父亲是$\dfrac{i+j-2}{i}$(事实证明这样是可以的~~我也不知道为什么~~),

- 可以发现一个规律:$i$的父亲呈递减关系直到$f_i=1$。

- 所以我们可以从上一次转移到下一次，复杂度~~应该是~~$O(n\sqrt{n})$的

- 详见代码

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>

using namespace std;

// typedef long long ll;

const int FFF=200000+5;

const int L=1000000;
char LZH[L];
char *SSS,*TTT;
inline char gc(){
	if (SSS==TTT) TTT=(SSS=LZH)+fread(LZH,1,L,stdin);
	return *SSS++;
}
inline int read(){
	int x=0,f=1;
	char c=gc();
	for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;
	for (;c>='0'&&c<='9';c=gc())
		x=(x<<1)+(x<<3)+c-48;
	return x*f;
}
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)write(x/10);
	putchar(x%10+48);
}//输入输出优化

int n,a[FFF];
int f[FFF];
int ans;
int maxx;
int minn;

int main()
{
	if(fopen("23333.in", "r"))
	{
		freopen("23333.in", "r", stdin);
		freopen("23333.out", "w", stdout);
	}
	n=read();
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
	}
	for(int i=1;i<=n;++i)
	{
		f[i]=i-1;
		if(a[i]<a[i-1])
		{
			ans+=1;//预处理ans，顺便把一叉堆的情况写了
		}
	}
	write(ans);
	putchar(' ');
	for(int i=2;i<=n-1;++i)//从二叉堆开始讨论
	{
		if((n-1)%i==0)
		{
			maxx=(n-1)/i;
		}
		else
		{
			maxx=(n-1)/i+1;
		}//计算出相同父亲的最长长度
		for(int q=1;q<=maxx;++q)
		{
			minn=1+(q-1)*i+1;//算出当f[i]=q时，最后一位在整串数列中位置
			for(int j=min(1+q*i,n);j>=minn;--j)//从后面开始搜索，这样可以减少搜索的次数
			{
				if(f[j]!=q)//如果f[j]不等于上一次的f[j](不理解的可以看一下上面的表)
				{
					if(a[j]<a[f[j]])
					{
						ans--;//如果上一次的f[j]是不合理的，为了避免重复，ans-=1
					}
					f[j]=q;//转移
					if(a[j]<a[f[j]])
					{
						ans++;//如果这一次的f[j]是不合理的，ans+=1;
					}
				}
				else
				{
					break;//如果搜索到与上一次一样的话，直接break，减少搜索次数，这就是为什么要从后面开始搜索的原因
				}
			}
		}
		write(ans);
		putchar(' ');
	}
	return 0;
}

```



---

## 作者：FZzzz (赞：4)

~~翻集训队作业翻到两道不会做的神题（对我说的就是 538G 和 538H），然后就一气之下把这场的 F 水了。~~

~~你以为我是数据结构，其实我是数论哒！~~

好吧数论算不上但是这题真和数据结构没啥关系。

------------
根据惯例我们钦定个啥再去算。

如果我们枚举叉数，那恭喜你你没了。

如果枚举父亲，似乎是可以有很神奇的 $O(n\log^2)$ 做法的，但是我不会。

我们考虑枚举儿子，然后再看在每一种叉数下它的父亲是谁。

$x$ 号点在 $k$ 叉树上的父亲是 $\lfloor\frac{x+k-2}k\rfloor=\lfloor\frac{x-2}k\rfloor+1$。

我们优化这个算法，发现其实在很多情况下一个点的父亲是相同的。

再看一遍上面那个式子，想到了什么？

对，整除分块。

我们枚举每个点，整除分块一下，差分算答案即可。

这样复杂度是 $O(\sum\limits_{i=1}^n\sqrt i)$，上界肯定是 $O(n\sqrt n)$，再紧一点的界我就不知道了。

~~特别短的~~代码：
```cpp
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
const int maxn=2e5+5;
int n,a[maxn];
int ans[maxn];
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    for(int i=1;i<=n;i++) a[i]=readint();
    for(int i=2;i<=n;i++){
    	int l=1;
    	while(l<=i-2){
    		int r=(i-2)/((i-2)/l);
    		if(a[(i-2)/l+1]>a[i]){
    			ans[l]++;
    			ans[r+1]--;
			}
			l=r+1;
		}
		if(a[1]>a[i]) ans[l]++;
	}
	for(int i=2;i<n;i++) ans[i]+=ans[i-1];
	for(int i=1;i<n;i++) printf("%d ",ans[i]);
	printf("\n");
    return 0;
}
```


---

## 作者：Farkas_W (赞：3)

### 思路：

$\quad$因为此题的答案就像树上的逆序对 $(x,y)$ 个数， $y$ 比 $x$ 的编号大但数值小，这不就是树上的逆序对吗？但是不用考虑所有编号大于它的，只需要考虑它的 $k$ 个儿子(也可能没有 $k$ 个儿子)，儿子的子树不算。

$\quad$考虑用树状数组维护，记录每一个点的编号和大小，因为只有小于这个点的才有可能对这个点产生贡献，按大小从小到大排序，先每次计算贡献，再将它插入它的编号的位置即可，计算和插入的顺序不重要，注意要判断节点 $i$ 是否为叶子节点，是就直接停止，因为之后节点 $i$ 都会是叶子节点，对于 $k$ 叉堆来说， $k$ 越大，叶子节点越多，这个剪枝很必要。

$\quad$另外英文题面中提供了对于 $k$ 叉堆中编号为  $x$ 的 $k$ 个儿子编号由 $k\times (x-1)+2$ 至 $k\times x+1$ (也可能没有 $k$ 个儿子)

$\quad$想看的可以看看[中文题面](https://www.luogu.com.cn/paste/gaojsey3)。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cstring>
using namespace std;
#define re register int
#define int long long
#define LL long long
#define il inline
#define lowbit(x) x&(-x)
#define next nee
#define inf 1e18
il int read()
{
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)&&ch!='-')ch=getchar();
  if(ch=='-')f=-1,ch=getchar();
  while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
  return x*f;
}
il void print(int x)
{
  if(x<0)putchar('-'),x=-x;
  if(x/10)print(x/10);
  putchar(x%10+'0');
}
const int N=2e5+5;
int n,m,b[N],c[N];
struct node{int num,size;}a[N];
il bool cmp(node a1,node a2){return a1.size==a2.size?a1.num<a2.num:a1.size<a2.size;}
il void update(int x,int y){while(x<=n){c[x]+=y;x+=lowbit(x);}}
il int sum(int x){int res=0;while(x){res+=c[x];x-=lowbit(x);}return res;}
signed main()
{
  n=read();
  for(re i=1;i<=n;i++){a[i].num=i;a[i].size=read();}
  sort(a+1,a+n+1,cmp);
  update(a[1].num,1);
  for(re i=2;i<=n;i++)
    {
      for(re j=1;j<n&&j*(a[i].num-1)+2<=n;j++)//限制中的剪枝
	{
	  int suml=sum(j*(a[i].num-1)+1),sumr=sum(min(j*a[i].num+1,n));//编号最小的儿子-1和编号最大的儿子(不可超过n，因为树状数组最大到n)
	  b[j]+=(sumr-suml);
	}
      update(a[i].num,1);//最后更新这个点
    }
  for(re i=1;i<n;i++)
    print(b[i]),putchar(' ');
  return 0;
}
```

---

## 作者：hgckythgcfhk (赞：2)

看题面中极具误导性的这句话：

------------

（即有若干个节点小于它的父亲）

------------

我们发现，一个 $k$ 叉堆的子结点一定在一个长为 $k$ 的区间内，上面这句话等价于，“即有**一个**父亲大于它的儿子”，这样是不是舒服多了。

于是做法非常显然了，每次向右滑动一个长为 $k$ 的区间，并向右移动一个表示当前节点的指针，求当前元素在区间的排名，直接套主席树模板即可。

证明时间复杂度正确，每次移动的区间不交，所以每个 $k$ 会运行 $O(\frac{n}{k})$ 次，这个结果不是很好看，它等价于 $O(\frac{1}{k}\times n)$，故运行次数为：

$$\sum_{k=2}^{k<n}O(\frac{1}{k}\times n)=O(n)\times \sum_{k=2}^{k<n}O(\frac{1}{k})$$ 

后面是调和级数，可以视为 $\log n$，由于每次主席树是 $O(\log n)$ 的，所以最终时间复杂度为 $O(n\log^2n)$。

为什么求和从 $2$ 开始？因为 $k=1$ 的情况可以在建树过程中顺带着求出来。

这个想法的来源是暴力，我想的暴力是跑 bfs，发现 bfs 序是一个 $1$ 到 $n$ 的序列，bfs 的正确性显然，故此算法正确性得证。

主席树动态开点不要用 vector，CF 上会 RE。
```
#include<bits/stdc++.h>
#define cit const register unsigned
#define open ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)//,freopen("1.in","r",stdin),freopen("1.out","w",stdout)
#define int register unsigned
#define void inline void
using namespace std;constexpr unsigned N=2e5+1;
struct A{unsigned a,b,c;}t[N<<7];unsigned rt[N<<1],x,cnt;
#define ls(o) t[o].a
#define rs(o) t[o].b
#define s(o)  t[o].c
//#define ne(id) 
void ins(cit&pre,int&o,cit l,cit r){t[o=++cnt]=t[pre];++s(o);if(l==r)return;
cit m=l+r>>1;x<=m?ins(ls(pre),ls(o),l,m):ins(rs(pre),rs(o),m+1,r);}
inline unsigned rnk(cit&a,cit&b,cit l,cit r){if(l==r)return 0;cit _=s(ls(b))-s(ls(a))
	,m=l+r>>1;return x<=m?rnk(ls(a),ls(b),l,m):rnk(rs(a),rs(b),m+1,r)+_;}
signed a[N];set<signed>lsh;unordered_map<signed,unsigned>mp;unsigned id;
signed main(){open;int n,ans=0;cin>>n;//t.emplace_back(A{0,0,0});
	for(int i=1;i<=n;++i)cin>>a[i],lsh.emplace(a[i]);
	for(const register signed i:lsh)mp[i]=++id;//t.emplace_back(A{0,0,0});
	for(int i=1;i<=n;++i)a[i]=mp[a[i]],ans+=(a[i]<a[i-1]);
	for(int i=1;i<=n;++i)x=a[i],ins(rt[i-1],rt[i],1,id);
	for(int i=1;i<=n;++i)rt[n+i]=rt[n];cout<<ans<<' ';
	for(int len=2;len<n;++len){ans=0;
		for(int l=2,r=l+len-1,p=1;l<=n;l=r+1,r=l+len-1,++p){
			x=a[p];ans+=rnk(rt[l-1],rt[r],1,id);}cout<<ans<<' ';}
	
}

```


---

## 作者：bsdsdb (赞：1)

题意：给序列 $\{a_n\}$，对 $k\in[1,n)$，询问以 $a$ 为点权的完全 $k$ 叉树有多少个 $i$ 满足 $a_i<a_{p_i}$。

一个 $i$ 的子节点一定是 $[k(i-1)+2,ki+1]$，故 $n-1$ 个树中有子节点的节点总个数为 $\sum_{k=1}^{n-1}\sum_{i=1}^n[k(i-1)+2\le n]=\sum_{k=1}^{n-1}\sum_{i=1}^n\left[i\le\frac{n-2}{k}+1\right]=\mathcal O(n\log n)$，可以对于每个节点求子节点贡献的答案。现在问题变成了静态数组多个询问 $[l,r]$ 中 $<v$ 的个数。转化成 $\operatorname{ans}([1,r],v)-\operatorname{ans}([1,l-1],v)$，然后将询问离线，BIT 扫描处理即可。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef int ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
#define invarg invalid_argument
#define cus_throw(msg) throw invarg(string(msg) + " at " + __FILE__ + ":" + to_string(__LINE__))
random_device rndv;
mt19937 rd(rndv());
const ll inf = 0x3f3f3f3f3f3f3f3fll;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
//inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma GCC optimize(1,2,3,"Ofast","inline")
#define MAXN (200005)

struct BIT {
	#define lb(x) (x&-x)
	ll size, val[MAXN];
	void init(ll x = 0) {
		size = x;
		fill_n(val, x + 3, 0);
	}
	void add(ll p, ll x) {
		while (p <= size) {
			val[p] += x;
			p += lb(p);
		}
	}
	ll qry(ll p) {
		ll ret = 0;
		while (p) {
			ret += val[p];
			p -= lb(p);
		}
		return ret;
	}
} bit;

ll n, a[MAXN], anss[MAXN];
vector<pll> qry[MAXN];
map<pll, ll> ans;
map<ll, ll> dc;

int main() {
//	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
	read(n);
	for (ll i = 1; i <= n; ++i) {
		read(a[i]);
		dc[a[i]] = 1;
	}
	ll dcc = 0;
	for (auto& i : dc) {
		i.second = ++dcc;
	}
	for (ll i = 1; i <= n; ++i) {
		a[i] = dc[a[i]];
	}
	for (ll k = 1; k < n; ++k) {
		for (ll i = 1; k * (i - 1) + 2 <= n; ++i) {
			qry[k * (i - 1) + 1].empb(a[i] - 1, -k);
			qry[min(n, k * i + 1)].empb(a[i] - 1, k);
		}
	}
//	for (ll i : qry[0]) {
//		ans[mkp(0, i)] = 0;
//	}
	bit.init(n);
	for (ll i = 1; i <= n; ++i) {
		bit.add(a[i], 1);
		for (pll j : qry[i]) {
//			ans[mkp(i, j)] = bit.qry(j);
			anss[abs(j.second)] += abs(j.second) / j.second * bit.qry(j.first);
		}
	}
	for (ll k = 1; k < n; ++k) {
//		ll anss = 0;
//		for (ll i = 1; k * (i - 1) + 2 <= n; ++i) {
//			anss += ans[mkp(min(n, k * i + 1), a[i] - 1)] - ans[mkp(k * (i - 1) + 1, a[i] - 1)];
//		}
		write(anss[k]), space();
	}
	enter();
	return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：GIFBMP (赞：1)

首先我们发现，对于一个 $k$ 叉树，一个节点 $x$ 的子节点编号区间为 $[k\times x-k+2,k\times x+1]$，它的父节点编号为 $\lfloor\dfrac{x+k-2}{k}\rfloor$。

同时我们可以发现，对于一个 $k$ 叉树，它的非叶子节点数量是 $\Theta(\dfrac{n}{k})$ 级别的，因此我们考虑根号分治，设分治点为 $B$，那么对于 $k\le B$ 的情况，我们对于每个节点检测一遍即可，时间复杂度 $\Theta(nB)$。

那么对于 $k>B$ 的情况，问题转化为对于每个非叶子节点 $x$，在 $[k\times x-k+2,k\times x+1]$ 中有多少元素小于 $a_x$。主席树维护即可。时间复杂度 $\Theta(\dfrac{n^2}{B^2}\log n)$。

那么总时间复杂度为 $\Theta(nB+\dfrac{n^2}{B^2}\log n)$，可以列出方程：

$$nB=\dfrac{n^2}{B^2}\log n$$

解得 $B=\sqrt[3]{n\log n}$ 时，时间复杂度最优，为 $\Theta(n\sqrt[3]{n\log n})$。

Code:

```cpp
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std ;
const int MAXN = 2e5 + 10 ;
int n , a[MAXN] , t[MAXN] ; 
int rt[MAXN] , s[MAXN * 25] , lc[MAXN * 25] , rc[MAXN * 25] , tot ;
#define mid ((l + r) >> 1)
void build (int &o , int l , int r) {
	if (!o) o = ++tot ;
	if (l == r) return ;
	build (lc[o] , l , mid) , build (rc[o] , mid + 1 , r) ;
}
void upd (int &o , int l , int r , int x , int k) {
	lc[++tot] = lc[o] , rc[tot] = rc[o] , s[tot] = s[o] + k , o = tot ;
	if (l == r) return ;
	if (x <= mid) upd (lc[o] , l , mid , x , k) ;
	else upd (rc[o] , mid + 1 , r , x , k) ;
}
int query (int o1 , int o2 , int l , int r , int x , int y) {
	//printf ("%d %d:%d %d\n" , o1 , o2 , l , r) ; 
	if (x <= l && r <= y) return s[o2] - s[o1] ;
	int ret = 0 ;
	if (x <= mid) ret += query (lc[o1] , lc[o2] , l , mid , x , y) ;
	if (mid < y) ret += query (rc[o1] , rc[o2] , mid + 1 , r , x , y) ;
	return ret ;
}
int main () {
	scanf ("%d" , &n) ;
	for (int i = 1 ; i <= n ; i++) scanf ("%d" , &a[i]) , t[i] = a[i] ;
	sort (t + 1 , t + n + 1) ;
	int len = unique (t + 1 , t + n + 1) - t - 1 ;
	for (int i = 1 ; i <= n ; i++) a[i] = lower_bound (t + 1 , t + len + 1 , a[i]) - t ;
	int tmp = pow (n * log2 (n) , 1.0 / 3.0) ;
	for (int i = 1 ; i <= tmp ; i++) {
		int ret = 0 ;
		for (int j = 2 ; j <= n ; j++) if (a[j] < a[(j + i - 2) / i]) ret++ ;
		printf ("%d " , ret) ;
	}
	build (rt[0] , 1 , n) ;
	for (int i = 1 ; i <= n ; i++) rt[i] = rt[i - 1] , upd (rt[i] , 1 , n , a[i] , 1) ;
	for (int i = tmp + 1 ; i < n ; i++) {
		int m = (n + i - 2) / i , ret = 0 ;
		for (int j = 1 ; j <= m ; j++)
			if (a[j] > 1) ret += query (rt[i * j - i + 1] , rt[min (i * j + 1 , n)] , 1 , n , 1 , a[j] - 1) ;
		printf ("%d " , ret) ;
	}
	return 0 ;
} 
```

---

## 作者：Cesare (赞：1)

用啥树状数组，~~分块大法好~~。

我们观察一个对于一棵 $j$ 叉树，求他的父亲的公式： $ (i + j - 2) / i $。

这表示啥？这不就是表示对于许多的节点，他的父亲相同吗。

对于父亲相同的节点，我们把它分成一个块，然后直接用一个差分数组实现区间加，先判断是否不合法，不合法就用差分数组搞一搞，最后做一遍前缀和，输出答案即可。

```cpp
#include<bits/stdc++.h>
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define mid ( ( l + r ) >> 1 )
#define debug(x) cout << "#x = " << x << endl
#define re register
#define For( i, j, k ) for( re int i = j; i >= k; i-- )
#define foR( i, j, k ) for( re int i = j; i <= k; i++ )
using namespace std;
typedef long long ll;
const ll N = 5011;
const ll inf = 0x3f3f3f3f3f3f;

ll n, a[200011], fa[N][N];

namespace IO {

	inline ll read() {
		ll x = 0; bool f = 0; char ch = getchar();
		for ( ; !isdigit(ch); ch = getchar() ) f ^= ( ch == '-' );
		for ( ; isdigit(ch); ch = getchar() ) x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 );
		return f? -x: x;
	}
	
	inline void write ( ll x ) {
		if ( x < 0 ) x = -x, putchar ( '-' );
		if ( x > 9 ) write ( x / 10 );
		putchar ( x % 10 | 48 );
	}
	
	inline void wln ( ll x ) { write (x); putchar ( ' ' ); }

}

using namespace IO;

ll ans[200011];
//priority_queue < ll > q;

int main() {
	freopen("23333.in", "r", stdin);
	freopen("23333.out", "w", stdout);
	n = read(); For ( i, 0, n - 1 ) a[i] = read();
	for ( re int i = 1, l, r; i < n; i++ ) {
		l = 1;
		while ( l <= i - 1 ) {
			r = ( i - 1 ) / ( ( i - 1 ) / l );
			if ( a[i] < a[( i - 1 ) / l] ) ans[l]++, ans[r + 1]--;
			l = r + 1;
		} if ( a[i] < a[0] ) ans[i]++;
	}
	For ( i, 1, n - 1 ) ans[i] += ans[i - 1];
	For ( i, 1, n - 1 ) wln ( ans[i] );
	return 0;
}
```
温馨提示：不要抄代码。

~~老爷机上$T$了，艹~~

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2200}$
---
### 解题思路：

首先容易发现直接枚举 $k$ 叉树对于每一种计算贡献会寄。

然后就从每一个节点考虑了，接下来有两种思路。

#### 作为父亲节点计算贡献

这一个部分的朴素想法就是对于一个区间中找到比当前数小的数的数量。

明显，这个过程可以用数据结构优化，优化的方式和树状数组求逆序对类似。将所有数按照大小为关键字排序，每处理一个数，直接枚举叉树 $k$，则儿子区间为 $[(i-1)k+2,ik+1]$ 中的所有已经被插入的数就都算作贡献。

这样的复杂度正确性需要一个结论，即满 $k$ 叉树的有儿子的节点数量是 $O(\dfrac{n}{k})$ 的，一种可行的证明思路是用完全二叉树计算出非叶节点数，再补上若干叶子结点算。

所以这里的总复杂度就是 $O(n\log^2 n)$ 的了。

#### 作为儿子节点计算贡献

这种思路则不需要借助数据结构，根据上面固定父亲的儿子区间，可以算出固定儿子的父亲节点编号为 $\lfloor\dfrac{i-2}{k}\rfloor+1$，在 $k$ 变化的时候，这个式子一共只有 $\sqrt n$ 种取值，直接整除分块就得到一个 $\sum_{i=1}^n \sqrt i=O(n\sqrt n)$ 的做法。


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;
int a[MAXN],n,ans[MAXN],l,r;
void work(int x){
	for(int i=1;i<=n-1&&(x-2)/i>0;){
		l=((x-2)/i);r=(x-2)/l;
		if(a[l+1]>a[x])ans[i]++,ans[r+1]--;
		i=r+1;
	}
	ans[x-1]+=a[1]>a[x];
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=2;i<=n;i++)work(i);
	for(int i=2;i<=n;i++)ans[i]+=ans[i-1];
	for(int i=1;i<n;i++)printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：7KByte (赞：0)

观察一下二叉堆中，节点$x$的父节点为$\left\lfloor\dfrac{x}{2}\right\rfloor$，可以写作$\left\lfloor\dfrac{x-2}{2}\right\rfloor+1$。

为什么要写成这样的形式呢，因为我么发现三叉堆可以写成$\left\lfloor\dfrac{x-2}{3}\right\rfloor+1$。

不难验证k叉堆可以写成$\left\lfloor\dfrac{x-2}{k}\right\rfloor+1$。

那么我们枚举节点$x$，根据数论分块，父节点不超过$\sqrt{x}$种，并且相同的父节点对应的$k$是连续的一段，所以我们再差分一下答案数组即可。

时间复杂度$\rm O(N\sqrt{N})$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define N 200005
using namespace std;
int ans[N],n,a[N];
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	rep(x,2,n){
		for(int i=1;i<n&&(x-2)/i>0;){
			int j=(x-2)/i,k=min(n-1,(x-2)/j);
			if(a[x]<a[j+1])ans[i]++,ans[k+1]--;
			i=k+1;
		}
		ans[x-1]+=a[x]<a[1];
	}
	rep(i,1,n-1)ans[i]+=ans[i-1],printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：fighter (赞：0)

# CF538F A Heap of Heaps 

## 题意简述

​	给定一个序列，求按顺序将此序列构建成1~n-1叉小根堆时，不合法元素分别有多少。一个元素不合法，当且仅当它的值严格小于父亲节点。

## Solution

​	首先我们可以得知，对于一个父亲，不管几叉堆，它的儿子一定是一段连续的区间。并且对于$i$叉堆$fa$节点，这一段区间为$[fa*i-i+2,fa*i+1]$。

​	那么我们自然想到用数据结构来维护这一段区间中小于某个值的元素个数。~~于是我在考场上愚蠢地选择了分块~~。

​	实际上这可以用树状数组维护，原理和求逆序对类似。首先我们记录每一个数的初始编号，然后将元素从小到大排序，依次插入树状数组。插入时，将元素的初始位置在树状数组中加1；查询时只要统计树状数组中给定区间内的和即可。

​	为什么这样插入就是正确的呢？~~废话，不正确怎么能过呢~~。感性理解一下，由于排序后保证了小的数字会被抢先插入，而当前节点要插入时，在树状数组中的元素一定比当前元素小，那么只要在当前元素的儿子区间中查询区间和就是比他小的儿子个数了。

​	最后分析一下复杂度，由于我们对于$i$叉堆，肯定需要扫描$\frac{n}{i}$个区间，而每个区间都由树状数组在$logn$时间内给出答案。所以我们的复杂度应为$nlogn \cdot \sum \limits_{i=1}^{n} \frac{n}{i}$。由于$ \sum \limits_{i=1}^{n} \frac{n}{i}=logn$，所以最后的复杂度为$O(nlog^2 n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define MAX 500005
using namespace std;

struct node{
    int val, ord;
    friend bool operator <(node n1, node n2){
        if(n1.val == n2.val)
            return n1.ord < n2.ord;
        return n1.val < n2.val;
    }
}a[MAX];

int n;
int s[MAX], ans[MAX];

void add(int x){
    while(x <= n){
        s[x]++;
        x += lowbit(x);
    }
}

int sum(int x){
    int res = 0;
    while(x){
        res += s[x];
        x -= lowbit(x);
    }
    return res;
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i].val);
        a[i].ord = i;
    }
    sort(a+1, a+n+1);
    for(int i = 1; i <= n; i++){
        add(a[i].ord);
        for(int j = 1; j<n && a[i].ord*j-j+2 <= n; j++){
            ans[j] += sum(min(a[i].ord*j+1, n)) - sum(a[i].ord*j-j+1);
        }
    }
    for(int i = 1; i < n; i++){
        printf("%d ", ans[i]);
    }
    
    return 0;
}
```

## 彩蛋

其实这道题还有两三种$\sqrt{n}$的做法（如除法分块）~~但我太弱了不会写~~。值得思考思考。

还有，那位FAQ*****，直接复制模拟赛题解ppt来水题解是不是有点过分啊！！

---

## 作者：FAQmother (赞：0)

我们考虑来枚举父亲，计算每一个父亲对于答案的贡献
首先我们可以发现一个父亲的儿子是连续的一段，对于i叉堆，节点j的儿子为i*j+2-i到i*j+1，可以直接枚举每个父亲的贡献。

暴力计算贡献是O(n)级别的，对于i叉堆，父亲的个数为n/i，因为提示三，所以总的个数为nlogn个，所以复杂度为O(n^2logn)

计算贡献本质上就是求一段区间内小于一个数的数量，然后就可以欢快的用数据结构进行优化了。

我们考虑用树状数组，将元素位置为下标，按元素大小一个个插入，这样每次计算只要O(logn)的复杂度然后总的复杂度为O(nlog^2n)

代码
```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;

inline char gc()
{
	static const int L = 1000;
	static char sxd[L], *sss = sxd, *ttt = sxd;
	if(sss == ttt)
	{
		ttt = (sss = sxd) + fread(sxd, 1, L, stdin);
		if(sss == ttt)
			return EOF;
	}
	return *sss++;
}
#define dd c = getchar()
inline int read(int& x)
{
	x = 0;
	char dd;
	bool f = false;
	for(; !isdigit(c); dd)
	{
		if(c == EOF)
			return -1;
		if(c == '-')
			f = true;
	}
	for(; isdigit(c); dd)
		x = (x << 1) + (x << 3) + (c ^ 48);
	if(f)
		x = -x;
	return 1;
}
#undef dd//快读

struct node
{
	int a,b;
}s[300000];

int i,j,n,z[300000],c[300000];

bool cmp(node x,node y)
{
	if(x.a!=y.a)
	{
		return x.a<y.a;
	}
	else
	{
		return x.b<y.b;
	}
}

int bit(int x)
{
	return x&-x;
}

void add(int x)
{
	while(x<=n)
	{
		c[x]++;
		x+=bit(x);
	}
	return;
}

int sum(int x)
{
	int z=0;
	while(x>0)
	{
		z+=c[x];
		x-=bit(x);
	}
	return z;
}

int main()
{
//	freopen("23333.in","r",stdin);
//	freopen("23333.out","w",stdout);
	read(n);
	
	for(i=1;i<=n;i++)
	{
		read(s[i].a);
		s[i].b=i;
	}
	
	sort(s+1,s+n+1,cmp);
	
	for(i=1;i<=n;i++)
	{
		add(s[i].b);
		for(j=1;(j<n)&&(s[i].b*j-j+2<=n);j++)
		  z[j]+=sum(min(n,s[i].b*j+1))-sum(s[i].b*j-j+1);
	}
	
	for(i=1;i<n;i++)
	  printf("%d ",z[i]);
	
	return 0;
}
```



---

