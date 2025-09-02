# Two Different

## 题目描述

You are given an integer $ n $ .

You should find a list of pairs $ (x_1, y_1) $ , $ (x_2, y_2) $ , ..., $ (x_q, y_q) $ ( $ 1 \leq x_i, y_i \leq n $ ) satisfying the following condition.

Let's consider some function $ f: \mathbb{N} \times \mathbb{N} \to \mathbb{N} $ (we define $ \mathbb{N} $ as the set of positive integers). In other words, $ f $ is a function that returns a positive integer for a pair of positive integers.

Let's make an array $ a_1, a_2, \ldots, a_n $ , where $ a_i = i $ initially.

You will perform $ q $ operations, in $ i $ -th of them you will:

1. assign $ t = f(a_{x_i}, a_{y_i}) $ ( $ t $ is a temporary variable, it is used only for the next two assignments);
2. assign $ a_{x_i} = t $ ;
3. assign $ a_{y_i} = t $ .

In other words, you need to simultaneously change $ a_{x_i} $ and $ a_{y_i} $ to $ f(a_{x_i}, a_{y_i}) $ . Note that during this process $ f(p, q) $ is always the same for a fixed pair of $ p $ and $ q $ .

In the end, there should be at most two different numbers in the array $ a $ .

It should be true for any function $ f $ .

Find any possible list of pairs. The number of pairs should not exceed $ 5 \cdot 10^5 $ .

## 说明/提示

In the first example, after performing the only operation the array $ a $ will be $ [f(a_1, a_2), f(a_1, a_2), a_3] $ . It will always have at most two different numbers.

In the second example, after performing two operations the array $ a $ will be $ [f(a_1, a_2), f(a_1, a_2), f(a_3, a_4), f(a_3, a_4)] $ . It will always have at most two different numbers.

## 样例 #1

### 输入

```
3```

### 输出

```
1
1 2```

## 样例 #2

### 输入

```
4```

### 输出

```
2
1 2
3 4```

# 题解

## 作者：wmy_goes_to_thu (赞：8)

真的没有人写题解。。。我来写一篇吧。

显然这是一道构造题，我们先来看小范围。

n=3 和 n=4 已经在样例中给了，我先做的是 n=5。

其实，n=5 可以这么做：

abcde->ffcde->ffgge->hfhge->hhhhe

同理，n=6 也可以。

但是 n=7 就不行了，于是我们采用另一种做法：

abcdefg->hhcdefg->hhiiefg->jhjiefg->jjjjefg->jjjkkfg->jjjkkll->jjjmkml->jjjmmmm

所以说，其实这道题做法是这样的：

1) 找到一个最大的 $k$，使得 $2^k \leq n$。

2) 处理前一部分 $(1,2^k)$

3) 处理后一部分 $(n-2^k+1,n)$

那么如何处理呢？显然可以递归处理：

solve(1,8)->bbbbcccc（递归之后的答案）->dbbbdccc->ddbbddcc->dddbdddc->dddddddd

最后发一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct apple
{
	int l,r;
	apple(int l=0,int r=0):l(l),r(r){}
}ans[1000005];
int n,tot=0,lg[1000005];
void gds(int l,int r)
{
	if(l==r)return;
	int mid=l+r>>1;
	gds(l,mid);
	gds(mid+1,r);
	for(int i=l;i<=mid;i++)ans[++tot]=apple(i,i-l+mid+1);
}
int main()
{
	lg[1]=1;
	for(int i=2;i<=1000000;i++)lg[i]=lg[i>>1]<<1;
	int n;
	cin>>n;
	gds(1,lg[n]);
	gds(n-lg[n]+1,n);
	cout<<tot<<endl;
	for(int i=1;i<=tot;i++)printf("%d %d\n",ans[i].l,ans[i].r);
	return 0;
}
```

---

## 作者：Soulist (赞：6)

我们发现操作每次可以将两个相同的值赋为相同的，我们认为这个操作是合并集合。

考虑这样来构造：

先两两合并，如果多了一个那么剩余这个元素（单独当作一个集合）

接下来我们有 $k$ 个大小为 $2$ 的集合，显然也可以两两合并。

可以这样一直操作下去，每次多余一个就剩余下来，最后我们有若干个，大小形如 $2^k$ 的集合。

我们发现小的集合的大小之和一定会小于最大的集合，同时考虑最小的集合，我们每次可以通过从最大的集合选一些数出来使其大小倍增。

假设最小的大小到达了次小的大小，那么我们就可以合并这两个集合，如果不够再找最大的借即可。

操作次数大概是 $\mathcal O(2n\log n)$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define pb push_back
#define vi vector<int>
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 5e5 + 5 ; 
const int M = 50 + 5 ; 
int n, top, cnt, num ;
struct node {
	int x, y ; 
} st[N] ; 
vi col[N], rev[N], lst[M] ;
vi merge( vi x, vi y ) {
	int m = x.size() ; vi ans ; ans.clear() ; 
	for(int i = 0; i < m; ++ i) {
		st[++ cnt] = (node){x[i], y[i]} ;
		ans.pb(x[i]), ans.pb(y[i]) ; 
	}
	return ans ; 
}
void output() {
	printf("%d\n", cnt ) ; 
	rep( i, 1, cnt ) printf("%d %d\n", st[i].x, st[i].y ) ; 
}
signed main()
{
	n = gi() ; 
	if( n <= 2 ) {
		puts("0") ; exit(0) ;  
	}
	rep( i, 1, n ) col[i].pb(i) ; 
	top = n ; 
	while(1) {
		int id = 0, bef = top ; 
		while(top >= 2) {
			++ id ; 
			rev[id] = merge(col[top], col[top - 1]) ; 
			top -= 2 ; 
		}
		if( top ) lst[++ num] = col[top] ; 
		if( id == 0 ) break ; 
		rep( i, 1, bef ) col[i].clear() ;  
		top = id ; 
		rep( i, 1, id ) col[i] = rev[i], rev[i].clear() ;  
	}
	if( num <= 2 ) output() ;
	else {
		int siz = lst[1].size(), bef = 0 ; 
		for( re int i = 2; i < num; ++ i ) {
			while( siz < lst[i].size() ) {
				vi tk ; tk.clear() ; 
				for(re int j = 0; j < siz; ++ j) {
					tk.pb(lst[1][j]), tk.pb(lst[num][j + bef]) ; 
					st[++ cnt] = (node){lst[1][j], lst[num][j + bef]} ;
				}
				lst[1].clear(), lst[1] = tk ; 
				bef += siz ; 
				siz *= 2 ; 
			}
			lst[1] = merge(lst[1], lst[i]) ;
			siz *= 2 ; 
		}
		output() ; 
	}
	return 0 ;
}
//1 + 2 + 4 + 8
```



---

## 作者：_edge_ (赞：2)

目前不知道多少交换次数的做法，但是比标程的少。

讲一下我的做法：

一开始是这样一个 $a$ 序列。

$a_1,a_2,a_3, \cdots ,a_n$。

那么我们先相邻合并，把数值相同的记为一样，也就是说下面的 $a_i$ 表示的其实是 $f(a_i,a_{i+1})$。

$a_1,a_1,a_3,a_3, \cdots,a_n$。

那么再对于相邻进行合并。

这里的合并要稍微搞一搞，比如 $a_1,a_1,a_3,a_3$ 合并，那么就是 $(1,3)$ 然后再 $(2,4)$。

然后会发现这样合并出来会合并成 $n$ 的二进制位。

比如 $n$ 是 `11010`，最终会合并出来 $16,8,2$。

然后我们肯定是要把小的数合并到大的数，那么我们就要有借位的操作，比如最小的那个数 $2$ 要向 $16$ 借 $6$ 位来和 $8$ 合并。

然后这样依次合并下去即可。

合并过程类似与后缀数组。

总的次数应该是 $2 \times n \log n$，但是严重跑不满。

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define int long long
#define pii pair<int,int>
#define fi first
#define se second 
using namespace std;
const int INF=5e5+5;
struct _node_data{
    int l,r;
}aa[INF];
int n,p[INF];
vector < pii >ans;
vector <int> v[INF];
signed main()
{
    // freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin>>n;
    for (int w=1;w<n;w*=2) {
        for (int i=1;i<=n;i++) {
            int r=i+2*w-1;
            if (r>n) break;
            for (int j=i;j<=i+w-1;j++)
                ans.pb({j,i+w+j-i});
            i=r;
        }
    }

    for (int i=0;i<30;i++)
        if (n&(1<<i)) p[++p[0]]=1<<i;
    
    sort(p+1,p+1+p[0],[](int x,int y){return x>y;});
    int la=1;
    for (int i=1;i<=p[0];i++) {
        aa[i].l=la,aa[i].r=la+p[i]-1,la+=p[i];
        for (int j=aa[i].l;j<=aa[i].r;j++)
            v[i].pb(j);
    }


    for (int i=p[0];i>2;i--) {
        // if (i==3) {
        //     cout<<"print\n";
        //     for (int j:v[i]) cout<<j<<" ";
        //     cout<<" endl\n";
        // }
        int L=v[i-1].size()-v[i].size(),pp=0,P=v[i].size();
        while (L--) {
            // if (i==3) {
            //     cout<<" neld\n";
            //     cout<<v[i][pp]<<" "<<v[1].back()<<" this?\n";
            // }
            ans.pb({v[i][pp],v[1].back()}),pp++,
            v[i].pb(v[1].back()),v[1].pop_back();
            if (pp>=P) pp=0,P*=2;
        }
        pp=0;
        for (int j:v[i]) v[i-1].pb(j),ans.pb({v[i-1][pp],j}),pp++;
    }
    cout<<ans.size()<<"\n";
    for (pii y:ans) cout<<y.fi<<" "<<y.se<<"\n";
    return 0;
}
```


---

## 作者：7KByte (赞：2)

简单题。

我们发现长度为$2^k$的序列可以在$\rm N\ log\ N$次操作内被推平为相同的区间。

那么我们找到最大的$k$使得$2^k<n $，然后先推平区间$[1,2^k]$，然后推平$[n-2^k+1,n]$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
using namespace std;
int n;
vector<pair<int,int> >u;
void solve(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	solve(l,mid);solve(mid+1,r);
	rep(i,0,mid-l)u.push_back(make_pair(l+i,mid+1+i));
}
int main(){
	int n;scanf("%d",&n);
	int k=0,l=1;
	while((l<<1)<n)l<<=1,k++;
	solve(1,l);solve(n-l+1,n);
	printf("%d\n",(int)u.size());
	for(int i=0;i<(int)u.size();i++)printf("%d %d\n",u[i].first,u[i].second); 
	return 0;
} 
```

---

## 作者：tommymio (赞：2)

非常 $\text{Naive}$ 的构造题。

下列叙述中，称一个区间内的数通过操作变成同一个数为推平（参考珂朵莉树）

手玩一会，发现对于 $n=2^i$ 的情况，我们有非常好的解决方式，可以只通过 $\sum\limits_{k=1}^i \frac{n}{2^k}\times 2^{k-1}=\frac{n}{2} \log n$ 次操作推平 $[1,n]$。而对于那些非 $2$ 的自然数次幂的 $n$，似乎并没有什么非常好的做法。

但是，由于推平操作是将一个区间内的所有数变为某一个相同的数，因此我们将某一段区间推平两次并不会影响答案。

于是想到一个这样的做法，求出 $2^k\leq n$ 的最大的 $k$，分别将 $[1,2^k]$ 和 $[n-2^k+1,n]$ 推平即可。总操作次数不会超过 $n \log n$ ，符合题目限制。

```cpp
#include<cstdio>
#include<vector>
#include<functional>
std::vector<std::pair<int,int> > res;
inline void solve(int l,int r) {
	if(l==r) return;
	int mid=l+r>>1; solve(l,mid);solve(mid+1,r);
	for(register int i=l;i<=mid;++i) res.push_back(std::make_pair(i,i+mid-l+1));
}
int main() {
	int n,k=0; scanf("%d",&n);
	while((1<<k)<=n) ++k; --k;
	solve(1,1<<k); if((1<<k)<n) solve(n-(1<<k)+1,n);
	printf("%d\n",res.size()); 
	for(register int i=0;i<res.size();++i) printf("%d %d\n",res[i].first,res[i].second);
	return 0;
}
```

---

## 作者：s_r_f (赞：1)

### 难写的做法

一开始 $n$ 个数互不相等，我们把这个局面记为 $n$ 个大小为 $1$ 的下标集合。

不难发现，我们可以做以下两种操作：

1、花费 $n$ 次操作的代价，把两个大小为 $n$ 的集合合并为一个大小为 $2n$ 的集合，这个下标集合内所有下标对应的数仍然是全相等的。

2、花费 $0$ 次操作，分裂两个下标集合。

那我们只需要合并到最后只有两个集合即可。

考虑二进制合并，然后剩下 $\Theta(\log n)$ 个集合，其中最大的集合大小大于 $n$ 的一半。

然后利用最大的集合，把其它集合一一合并起来，这样就只剩两个集合了。

实际测试中对于 $n = 15000$ 的情况只需要 $100068$ 次操作 。

code 见[我的提交](https://codeforces.ml/contest/1408/submission/94334631)

---
### 好写的做法

还有一种做法，先求出 $k$ 满足 $2^{k+1} \geq n$ , 然后直接做两次,先使前 $2^k$ 个数变为相等的，再让后 $2^k$ 个数变为相等的即可，操作数比我当场写的做法多一点，但是很好写。

code ：
```cpp
#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T &x){
	static char ch; x = 0,ch = getchar();
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
inline void write(int x){if (x > 9) write(x/10); putchar(x%10+'0'); }
int ansx[500005],ansy[500005],lans;
inline void print(){
	write(lans),putchar('\n');
	for (int i = 1; i <= lans; ++i) write(ansx[i]),putchar(' '),write(ansy[i]),putchar('\n'); 
	exit(0); 
}
inline void add(int x,int y){ ++lans; ansx[lans] = x; ansy[lans] = y; }
inline void solve(int l,int r){
	if (l == r) return; if (l+1 == r){ add(l,r); return; }
	int mid = l+r>>1,i,j; solve(l,mid),solve(mid+1,r);
	for (i = l,j = mid+1; i <= mid; ++i,++j) add(i,j);
}
int main(){ int n,m; read(n),m = 1; while (m<<1 < n) m <<= 1; solve(1,m),solve(n-m+1,n),print(); return 0; }
```

---

## 作者：Dzhao (赞：1)

## 题解 CF1408F 
题意：你需要选择 $q$ 个二元组 $(x_i,y_i)$，每次使得 $a_{x_i}$ 和 $a_{y_i}$ 的值变为 $f(a_{x_i},a_{y_i})$。$f(x,y)$ 的值为任意值，对于相同的 $x,y$，$f(x,y)$ 的值相同，请你找出一种可能使得对于任意函数 $f$ 经过 $q$ 次操作后数列中最多只有 $2$ 个不同的数。

我们需要做到的，就是尽可能把所有的数变为一样的，我们可以发现，对于一个长度为 $2n$ 的序列，要是他所有的数都变为相等的，可以使$a[1...n]$ 相等，$a[n+1...2n]$ 相等，然后将 $a_i$ 和 $a_{i+n}$ 变为 $f(a_i,a_{i+n})$ 即可 $(i\leq n)$。这样，我们要将一个序列变的全都相等，只要将他不停分成两半就行了。于是我们就发现，长度为 $2^k$ 的序列可以全部变为相同的数，于是我们可以将序列分为两段：$[1,2^k]$ 和 $[n-2^k+1,n]$ 使两段相交即可将序列变为只有两个数不同的序列。

因为最多进行 $\log n$ 次分段，每次分段最多 $n$ 次操作，所以 $q$ 不超过 $n\log n$，一定 $\le5\times 10^5$。

$\mathcal{View \ Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[500005],y[500005],q;

int main()
{
	scanf("%d",&n);
	int k=log2(n),mx=1<<k;
	for(int i=0;i<k;i++)
		for(int l=1;l<=mx-(1<<i);l+=(1<<i+1))
			for(int j=l;j<l+(1<<i);j++) 
				x[++q]=j,y[q]=j+(1<<i);
	int su=n-mx;
	for(int i=0;i<k;i++)
		for(int l=1;l<=mx-(1<<i);l+=(1<<i+1))
			for(int j=l;j<l+(1<<i);j++) 
				x[++q]=j+su,y[q]=j+(1<<i)+su;
	printf("%d\n",q);
	for(int i=1;i<=q;i++) printf("%d %d\n",x[i],y[i]);
	return 0;
}
```
$\mathcal{Thanks\ for\ watching}$

---

## 作者：_zhx (赞：0)

# CF1408F Two Different 题解

## 题目大意

给定一个正整数 $n$ 和一个长度为 $n$ 的序列 $a$，其中 $a_i=i$。

需要构造出若干次以下的操作：

- 选择一个二元组 $(x_i,y_i)$ 使得每次 $a_{x_i},a_{y_i}$ 的值是 $f(a_{x_i},a_{y_i})$ 的任意值。

并且 $a$ 序列最多有 $2$ 个不同的数。

### 大致思路

当 $n=2^l$ 时，我们可以通过 $\frac{1}{2}\times n \log n$ 次

$$(\sum\limits_{l=1}^in\div2^l\times2^{l-1})$$

来把 $1$ 到 $n$ 的区间内变成相同的数。

但是，数据不全是 $2$ 的若干次方。

这时，我们可以先用循环求出次大的 $l$ 且满足 $2^l\le n$，然后再把 $1$ 到 $2^l$ 和 $n+1-2^l$ 到 $n$ 的区间变成相同的数。

code：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ilv inline void
#define uf(i,x,y) for(int i=x;i<=y;i++)
#define df(i,x,y) for(int i=x;i>=y;i--)
#define pb push_back
#define mk make_pair
#define pll pair<ll,ll>
#define fi first
#define se second
using std::vector;
using std::cout;ll n;
vector<std::pll>v;
namespace HaHa{namespace Haha
	{
		ilv dg(ll l,ll r)
		{
	    	if(l==r) return;
	   	 	ll mid=l+r>>1;
	   	 	Haha::dg(l,mid),HaHa::Haha::dg(mid+1,r);
	  	  	uf(i,l,mid) v.pb(std::mk(i,i+mid+1-l));
		}}}
ll Read()
{
    ll fff=1,xxx=0;char ccc=getchar();
    while(ccc<'0'||ccc>'9'){
        if(ccc=='-')fff=-fff;ccc=getchar();}
    while(ccc>='0'&&ccc<='9'){
        xxx=xxx*10+ccc-'0';ccc=getchar();}
    return fff*xxx;
}
int main()
{
    ll n,l=1;n=Read();while((1<<l)<=n) l++;
    HaHa::Haha::dg(1,1<<--l),HaHa::Haha::dg(n-(1<<l)+1,n);
    cout<<v.size()<<'\n';for(auto i:v) cout<<i.fi<<' '<<i.se<<'\n';
    return 0;
}
```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路
先考虑如何将一堆数变为相同的。

显然，这里有一个条件 $n=2^k,k\in \mathbb Z$，证明如下：
- 每次操作只能将两个数变为相同的，那么一个数在使得其他数变为相同数的操作中（我们不妨将所有数进行这种操作称为**一轮操作**），一个数最多被使用一次；
- 按照错位操作，即第一轮 $1$ 和 $2$、$3$ 和 $4$，第二轮 $1$ 和 $3$、$2$ 和 $4$ 这种最优决策（这样可以保证每一轮结束后不同数的数量最少）每一轮也最多减少 $\displaystyle \left\lfloor \frac{n}{2} \right\rfloor$ 种数量；
- 按照如上方法，在第 $i$ 轮会有 $a_i\bmod 2^i=1$ 的数无法被操作到，那么当且仅当 $n=2^k,k\in \mathbb Z$ 的时候，所有数可以变为相同的；

由上可以推出，当且仅当 $n=2^k+z,k\in \mathbb Z,z\le 1$ 的时候，序列可以根据以上操作变为最多有两个不同的，而这种情况也即为样例中的情况。

那么考虑 $n$ 为其他数的情况。我们发现对于任意大于 $1$ 的正整数，都可以找到一个 $x$ 使得 $x=2^k,k\in \mathbb Z$ 且 $\displaystyle x\ge \frac{n}{2}$。我们还发现，因为对于任意的序列 $a$ 和函数 $f$，构造方案都应成立，那么可以认为 $a$ 对于构造方案没有影响。那么我们考虑将序列拆为 $[1,x]$ 和 $[n-x+1,n]$ 两个长度均为 $x$ 的部分，不妨先通过上文操作使得区间 $[1,x]$ 中的数全部相等，然后再通过上文操作使得区间 $[n-x+1,n]$ 中的数全部相等，由于 $[1,n-x]$ 的数在两次操作后一定是相等的，而 $[n-x+1,n]$ 中的数在两次操作后是相等的，那么在这种操作方案下，最终序列一定有小于等于两种不同的数。

由于我们在使一个序列相同时错位操作，那么每个数在一轮中会被恰好操作一次，又由于每轮操作会使不同的数的数量减半，那么最多进行 $O(\log_2x)$ 轮操作，那么我们最终总共会进行 $O(2\cdot x\log_2x)$ 次操作，而在 $n\le 1.5\times 10^4$ 的数据范围下，操作次数是小于等于 $229376$ 次的，可以通过本题。

时间复杂度 $O(n\log n)$ ，空间 $O(n\log n)$，可以通过本题。
### 注意事项
 错位操作时细节有亿点多，如果是循环写法，一定要注意倍增的时候不要超出 $n$ 的范围了；如果是递归或 vector 合并写法，注意数组的清空。
 ### AC 代码
 ```cpp
 #include<stdio.h>
#include<stdlib.h>
#include<vector>
#define N 15005
#define pii std::pair<int,int>
int n,cnt,c[N];
std::vector<pii> ans;
std::vector<int> a[N],b[N];
inline void print(){
    printf("%d\n",ans.size());
    for(auto now:ans){
        int x=now.first;
        int y=now.second;
        printf("%d %d\n",x,y);
    }
}
inline void GetAns(int l,int r){
    int m=r-l+1,now=2;while(m>1){
        for(register int i=l;i<=r;i+=now)
        for(register int j=i;j<i+(now>>1);++j)
            ans.push_back({j,j+(now>>1)});
        m>>=1;now<<=1;
    }
}
signed main(){
	scanf("%d",&n);
    for(register int i=1;i<=n;++i)
        c[i]=i;int mid=1;
    while((mid<<1)<n) mid<<=1;
    GetAns(1,mid);
    GetAns(n-mid+1,n);
    print();
}
 ```

---

## 作者：wrzSama (赞：0)

## 题意

给定一个正整数 $n$ 和一个长度为 $n$ 的序列 $a$，其中 $a_i=i$。

你需要构造出若干次以下的操作：

选择一个二元组 $(x_i,y_i)$ ，每次使得 $a_{x_i}$ 和 $a_{y_i}$ 的值变为 $f(a_{x_i},a_{y_i})$。$f(a_{x_i},a_{y_i})$ 为任意值，但是对于相同的 $a_{x_i},a_{y_i}$，$f(a_{x_i},a_{y_i})$ 相同。

使得最终 $a$ 序列中至多有 $2$ 个不同的数。

## 思路

我们发现有一种类似归并排序的操作方式可以令该区间内所有 $a_i$ 的值相等：先把区间分成相等的左右两段，先用同样的方法令左右两段分别相等，然后左右一一对应进行一次操作。因为对于相同的 $a_{x_i},a_{y_i}$，$f(a_{x_i},a_{y_i})$ 相同，所以该区间操作后一定全是相同的数。但是，此方法仅能处理长度为 $2^k$ 的区间。所以，我们先找到一个最大的 $k$ 使得 $2^k\le n$，依次处理一遍区间 $1\sim 2^k$ 和 $n-2^k+1\sim n$ 就可以让序列中最多有 $2$ 个不同的值。

## 代码

```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
using namespace std;
inline int read()
{
	int res=0;
	bool op=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
	 	if(ch=='-') op=0;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9')
	{
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	return op?res:-res;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,tot,ansl[1000005],ansr[1000005];
void solve(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	for(re int i=l;i<=mid;++i)
	{
		ansl[++tot]=i;
		ansr[tot]=i-l+mid+1;
	}
}
int main()
{
	n=read();
	int tmp=1;
	while((tmp<<1)<=n) tmp<<=1;
	if(n==1)
	{
		puts("0");
		return 0;
	}
	solve(1,tmp);
	solve(n-tmp+1,n);
	write(tot);
	puts(""); 
	for(re int i=1;i<=tot;++i)
	{
		write(ansl[i]);
		putchar(' ');
		write(ansr[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：Fairicle (赞：0)

~~真 就 简 单 题 呗~~

容易发现对于一段长度为 $2^k,k\in{N}$ 能在 $2^{k-1}\times k$ 次操作中将其变成相同的一个数，过程类似于一个分治然后合并。于是可以对$[1,2^{log_{2}n}],[n-2^{log_{2}n}+1,n]$ 分别做一次。就，真的很好写。

巨丑的code：
```cpp
#include"bits/stdc++.h"
using namespace std;
#define ri register int
#define ll long long
#define N 500010
int n,tot,x[N],y[N];
inline void solve(int l,int r){
	if(l==r-1){tot++,x[tot]=l,y[tot]=r;return;}
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	for(ri i=l,j=mid+1;i<=mid&&j<=r;++i,++j) tot++,x[tot]=i,y[tot]=j;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	if(n==1||n==2){cout<<0<<endl;return 0;}int bas=1;
	while(bas<=n) bas*=2;
	bas/=2;
	solve(1,bas);
	solve(n-bas+1,n);
	cout<<tot<<endl;
	for(ri i=1;i<=tot;++i) cout<<x[i]<<" "<<y[i]<<endl;
	return 0;
}
```


---

## 作者：Fuyuki (赞：0)

如果存在 $n$ 个 $a$  和 $n$ 个 $b$，那么可以通过 $n$ 次操作将其变为 $2n$ 个 $f(a,b)$。

因此，采用这种类似倍增的方法，可以在 $k2^k$ 次操作中将任意 $2^k$ 个数变成相等的。

那么找到最大的 $k$ 使得 $2^k<n$，然后将序列的前 $2^k$ 和后 $2^k$ 都推成相等的数，那么整个序列就至多只有两个不同数字了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define V inline void
#define FOR(i,a,b) for(int i=a;i<=b;i++)
const int N=1e6+1;
int n,k,tot,X[N],Y[N];
V solve(int l,int r){
	if(l==r)return;
	int mid=l+r>>1,len=mid-l+1;
	solve(l,mid),solve(mid+1,r);
	FOR(i,1,len)tot++,X[tot]=l+i-1,Y[tot]=mid+i;
}
int main(){
	for(cin>>n,k=1;k*2<n;k<<=1);
	solve(1,k),solve(n-k+1,n);
	cout<<tot<<'\n';
	FOR(i,1,tot)cout<<X[i]<<' '<<Y[i]<<'\n';
	return 0;
}

```



---

## 作者：gyh20 (赞：0)

先想一个比较明显的“合并”方法。

从小到大合并每一个 $2^k$ 的区间，具体合并方法就是做 $f(x,x+(1<<(k-1))$对于所有的 $x\&((1<<k)-1)<(1<<k-1)$。

这个代码很像 FFT，所以是 $\log$ 级别的:

```cpp
inline void work(re int n,re int k){
	for(re int j=0;(1<<j)<=n;++j)
	for(re int ii=1;ii+(1<<j)<=n;ii+=(1<<(j+1))){
		for(re int i=ii;i<ii+(1<<j);++i)
		ans1[++m]=i+k,ans2[m]=i+k+(1<<j);
	}
}
```

但这样完全没有到题目的精髓，两种颜色？

一个很巧妙的思路（我也不知道怎么想到的），直接用两个区间覆盖，类似 ST 表，这样就可以恰好两种颜色了！


---

## 作者：feecle6418 (赞：0)

假如有 $2^n$ 个数，可以通过类似 FFT 蝶形变换的方法全部变成相同的。具体地，先把相邻两个弄成一样的 $((1,2),(3,4),\dots)$，再把相邻四个弄成一样的 $((1,3),(2,4),\dots)$，一直这样，直到全部相同。

假如不是，就把前 $2^n$ 个和后 $2^n$ 个弄成一样。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
struct Y{
	int x,y;
}s[500005]; 
int main(){
	cin>>n;
	if(n<=2)return puts("0"),0;
	int o=1;
	while(o*2<=n)o<<=1;
	for(int i=1;(1<<i)<=o;i++){
		for(int j=1;j<=o;j+=(1<<i)){
			for(int k=j;k<j+(1<<i-1);k++)if(k+(1<<i-1)<=n)s[++ans]={k,k+(1<<i-1)};
		}
	}
	for(int i=1;(1<<i)<=o;i++){
		for(int j=1;j<=o;j+=(1<<i)){
			for(int k=j;k<j+(1<<i-1);k++)if(k+(1<<i-1)<=n)s[++ans]={n-o+k,n-o+k+(1<<i-1)};
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)cout<<s[i].x<<' '<<s[i].y<<endl;
	return 0;
}
```

---

## 作者：Jayun (赞：0)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF1408F)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14613075.html)

# 题目大意：

构造 $q$ 个二元组 $(x_i,y_i)$，每个二元组的操作是把 $a_{x_i},a_{y_i}$ 的值都变为 $f(a_{x_i},a_{y_i})$。$f(x)$ 意义不重要。顺序对二元组进行操作，你要使得最后 $a_i$ 最多只有两个不同的数。

$1\leq n\leq 15000$，$1\leq q\leq 5\times 10^5$。

# 正文：

## n 在 2 的整次幂：

按照样例所给的方法，很容易想到一种构造方案（假设 $n$ 是 $2$ 的整次幂）：

![](https://img2020.cnblogs.com/blog/1748322/202104/1748322-20210403085928529-1270662365.png)

粗略计算一下，如果要把 $n$ 个数全合并为同一个，方案数有 $\frac{n\log n}{2}$ 个，可以过。

但是直接算有点麻烦，就可以逆向递归跑。

## n 不在 2 的整次幂：

把 $n$ 分成两个部分 $[1,2^k],[n-2^k+1,n]$ 跑，其中 $k$ 是最大数且满足 $2^k<n$。

# 代码：

```cpp
const int N = 135010;

int n, m;
int a[N][2], cnt;

void dfs (int l, int r)
{
	if (l == r) return;
	int mid = l + r >> 1;
	dfs(l, mid), dfs(mid + 1, r);
	for (int i = l; i <= mid; i ++)
		a[++cnt][0] = i, a[cnt][1] = i - l + mid + 1;
}

int main()
{
	scanf ("%d", &n);
	for (m = 1; (m << 1) < n; m <<= 1);
	dfs(1, m), dfs(n - m + 1, n);
	printf ("%d\n", cnt);
	for (int i = 1; i <= cnt; i++) printf ("%d %d\n", a[i][0], a[i][1]);
	return 0;
}
```

---

