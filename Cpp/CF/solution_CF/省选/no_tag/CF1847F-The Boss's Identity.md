# The Boss's Identity

## 题目描述

While tracking Diavolo's origins, Giorno receives a secret code from Polnareff. The code can be represented as an infinite sequence of positive integers: $ a_1, a_2, \dots  $ . Giorno immediately sees the pattern behind the code. The first $ n $ numbers $ a_1, a_2, \dots, a_n $ are given. For $ i > n $ the value of $ a_i $ is $ (a_{i-n}\ |\ a_{i-n+1}) $ , where $ | $ denotes the [bitwise OR operator](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

Pieces of information about Diavolo are hidden in $ q $ questions. Each question has a positive integer $ v $ associated with it and its answer is the smallest index $ i $ such that $ a_i > v $ . If no such $ i $ exists, the answer is $ -1 $ . Help Giorno in answering the questions!

## 说明/提示

In the first test case, $ a = [2,1,3,3,\ldots] $ .

- For the first question, $ a_1=2 $ is the element with the smallest index greater than $ 1 $ .
- For the second question, $ a_3=3 $ is the element with the smallest index greater than $ 2 $ .
- For the third question, there is no index $ i $ such that $ a_i > 3 $ .

## 样例 #1

### 输入

```
3
2 3
2 1
1
2
3
4 5
0 2 1 3
0
1
2
3
4
5 5
1 2 3 4 5
7
2
6
0
4```

### 输出

```
1
3
-1
2
2
4
-1
-1
-1
3
8
1
5```

# 题解

## 作者：XeCtera (赞：6)

题目链接：[Luogu](https://www.luogu.com.cn/problem/CF1847F) | [Codeforces](https://codeforces.com/contest/1847/problem/F)

## Description

有无穷项的非负整数序列 $a$。  
前 $n$ 项给定，之后的项的递推式为 $a_i=a_{i-n}|a_{i-n+1}$（其中 $|$ 为位运算 $\rm OR$）。

$q$ 次询问，每次给定 $v$，求最小的正整数 $i$，使得 $a_i>v$。

多组数据。

~~本来就有多组询问了，还非套个多组数据，怕不是有什么大病。~~

$1\le \sum n,\sum q\le 2\times10^5,0\le a_i,x\le 10^9.$

## Solution

先用递推式手算几项找找规律。以 $n=5$ 的情形为例，前几项依次为：

（为了方便，只记录下标，例如 $12$ 表示 $a_1|a_2$）

$$\begin{matrix}
1\sim 5:& 1&2&3&4&5\\
6\sim 10:&12&23&34&45&512\\
11\sim15:&123&234&345&4512&5123\\
16\sim20:&1234&2345&34512&45123&51234
\end{matrix}
$$

可以得到一些初步的观察：

 - 第 $i$ 列包含以 $a_i$ 为左端点的所有区间 $\rm OR$ 的值。（认为下标是循环的，即 $a_n$ 右边是 $a_1$）  
 	但是 $51,451,3451$ 这些以 $a_1$ 结尾的项缺失了。在最后的解法中，这容易用特判处理，所以我们暂时不管。

 - 大约第 $n^2$ 项之后的所有元素均为 $a_1|a_2|\cdots|a_n$。  
 	那么回答询问时可以只考虑前 $n^2$ 项。

不过 $n^2$ 项还是太多了。

注意到 $\rm OR$ 运算的一条经典性质：  

考虑将一个数不断 $\rm OR$ 上一些别的东西。  
由于每个二进制位至多发生一次变化，所以过程中只会产生 $O(\log V)$ 个不同值。（$V$ 为值域）

而第 $i$ 列的元素恰好是 $a_i$ 不断 $\rm OR$ 上 $a_{i+1},a_{i+2},\cdots$ 得到的。因此只会有 $O(\log V)$ 种不同的元素值。  

显然，对于值相同的元素，下标较大的一定不优，所以只需保留下标最小的。

那么需要用到的元素其实只有 $O(n\log V)$ 个。  
不妨预处理出这些元素以及它们的下标。

预处理的写法并不唯一，选择你喜欢的方法即可。

这样问题就转化为：  
已知一个长为 $O(n\log V)$ 的数列，每个元素有 $x,id$ 两种属性。  
每次询问给定 $v$，查询 $x>v$ 的所有元素中 $id$ 的最小值。  

这是经典的，仍然选择你喜欢的方法处理即可。  

给出一种比较常见的做法，作为参考：  
将数列按 $x$ 从大到小排序，所求即为 $id$ 的某个前缀 $\min$。可以预处理 + 二分回答询问。

总复杂度最优可以做到单 $\log$。不过双 $\log$ 的实现一般也能通过。

## Code

写得很丑，就不贴出来了。只挂一下提交记录。

[AC submission](https://codeforces.com/contest/1847/submission/212441553)

---

## 作者：BigJoker (赞：2)

对于 $n$ 后面的每一项来说，都来自于 $1\sim n$ 中某些数进行或操作得到的，那么不妨写几个出来，找一找规律，钦定 $n=6$

$$\begin{aligned}1\sim n:&1,2,3,4,5,6\\n+1\sim 2n:&12,23,34,45,56,612\\2n+1\sim 3n:&123,234,345,456,5612,6123\\3n+1\sim 4n:&1234,2345,3456,45612,56123,61234\\4n+1\sim 5n:&12345,23456,345612,456123,561234,612345\\5n+1\sim 6n:&123456,234561,...\end{aligned}$$

观察到每一列的第一项都是相等的，且后面遇到以 $1$ 结尾的都会跳过，否则就是往后面加一项，而且在 $n^2$ 项以内就已经出现了全部数或操作的情况。

考虑单独的每一列：因为或操作不可逆，每次改变值至少要将某一位上的数改成 $1$，而至多有 $\log V$ 个二进制位，所以实际上每一列的有效值只有 $\log V$ 个，将每一列这 $\log V$ 个有效值处理下来，并记录上编号，就可以将问题实现转化：多组询问，求数列中满足 $>x$ 的数的最小编号。

考虑如何处理出每一列的 $\log V$ 个值，可以使用二分加上 st 表，每次钦定左端点，然后向右跳，跳到与前一个异或值不相等即可。

注意特殊判断一下末位为 $1$ 的情况，因为这个是不能加进来的。

将存放这 $n\log V$ 个数的数列叫做 $g$，然后就得到了一个更简单的问题，有很多种做法，我的做法是对 $g$ 按照值的大小进行排序后，求一个后缀的编号最小值，然后把 $x$ 按从小到大的顺序离线下来，然后用指针扫到 $g_j>x$ 的情况，然后此后缀的编号最小值即为答案。

```cpp
#include<bits/stdc++.h>
#define mem(a,x) memset(a,x,sizeof(a))
#define re register
#define il inline
using namespace std;
typedef long long LL;
typedef pair<int,LL>PII;
const int N=2e5+5;
const int inf=0x3f3f3f3f;
int sq;
int Log[N<<1];
int n,q,a[N<<1],f[N<<1][21];
int k[N*30];
LL ans[N],p[N*30],s[N*30];
PII qe[N];
map<int,LL>dt;
il void init(){
	for(re int i=1;i<=n<<1;i++) f[i][0]=a[i];
	for(re int j=1;j<=20;j++)
		for(int i=1;i+(1<<j)-1<=n<<1;i++) f[i][j]=f[i][j-1]|f[i+(1<<j-1)][j-1];
}
il int get(int l,int r){
	int k=Log[r-l+1];
	return f[l][k]|f[r-(1<<k)+1][k];
}
il int solve(int i,int l,int r,int lst){
	if(l==r) return l;
	if(l+1==r) return get(i,l)^lst?l:r;
	int mid=l+r>>1;
	return get(i,mid)^lst?solve(i,l,mid,lst):solve(i,mid+1,r,lst);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	for(re int i=2;i<N<<1;i++) Log[i]=Log[i>>1]+1;
	while(T--){
		dt.clear();
		cin>>n>>q;
		for(re int i=1;i<=n;i++){
			cin>>a[i];
			a[i+n]=a[i];
		}
		init();
		for(re int i=1;i<=n;i++){
			int pl=i-1,pv=-1,del=0;
			while(pl-i+1<=n){
				int r=solve(i,pl+1,n<<1,pv);
				if(get(i,r)==pv) break;
				pv=get(i,r),pl=r;
				if(pl==n+1){
					pv=-1;
					continue;
				}
				if(!dt.count(pv)) dt[pv]=1ll*(r-i-(pl>=n+1)<0?0:r-i-(pl>=n+1))*n+i;
				else dt[pv]=min(dt[pv],1ll*(r-i-(pl>=n+1)<0?0:r-i-(pl>=n+1))*n+i);	
			}
		}
		int m=0;
		for(auto x:dt) k[++m]=x.first,p[m]=x.second;
		s[m]=p[m];
		for(re int i=m-1;i;i--) s[i]=min(s[i+1],p[i]);
		for(re int i=1;i<=q;i++){
			cin>>qe[i].first;
			qe[i].second=i;
		}
		sort(qe+1,qe+1+q);
		for(re int i=1,j=1;i<=q;i++){
			while(k[j]<=qe[i].first && j<=m) j++;
			if(j==m+1){
				ans[qe[i].second]=-1;
				continue;
			}
			ans[qe[i].second]=s[j];
		}
		for(re int i=1;i<=q;i++) cout<<ans[i]<<endl; 
	}
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

写臭了，导致调了挺久。

首先我们肯定会关心有哪些可能的下标组合，使它们的按位或会出现在 $a$ 中。简单写个打表程序：

```cpp
int n,m;
set<int> s[N];
void Yorushika(){
	scanf("%d",&n);
	rep(i,1,n*n){
		if(i<=n)s[i].insert(i);
		else{
			for(int j:s[i-n])s[i].insert(j);
			for(int j:s[i-n+1])s[i].insert(j);
		}
		for(int j:s[i])printf("%d ",j);
		puts("");
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

然后发现每种组合都是将给出的 $a$ 数组连成环后的一段区间，并且可行的区间所在位置只和其长度与 $n$ 有关。

而我们有经典结论：一个序列中以 $l$ 为左端点的区间，最多有 $\log V$ 个不同的按位与/或值。所以我们可以预处理出这些值以及对应的最左的右端点，并求出其中的一些存在于 $a$ 中的区间的位置。

断环成链后问题就变成了求所有 $>x$ 合法区间按位或值，所对应的 $a$ 中的位置的最小值。直接将这些东西存进 pair 里排个序，再求第二关键字的后缀 $\min$。每次二分一个位置解决。

然后交上去，wa 2。为什么呢？

这里有一个细节：如 $n=6$。如果 $x+1=a_6|a_1$，它会在哪里被统计？会发现，我们可能只会记录链上 $[6,7]$ 这个区间，而 $[6,8]$ 因为右端点更靠右，有可能因为 $a_8$ 即 $a_2=0$ 而被丢掉。但事实上 $[6,7]$ 不合法而 $[6,8]$ 合法。

这个问题怎么解决呢？可以令每个值最多被记录 $2$ 次，就可以有效避免了。

代码不长，但是细节不少。

code：

```cpp
// Problem: The Boss's Identity
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1847F
// Memory Limit: 500 MB
// Time Limit: 3000 ms
// Written by yinhee.
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
namespace my_std{
#define mems(x,y) memset(x,y,sizeof x)
#define Mp make_pair
#define eb emplace_back
#define gc getchar
#define pc putchar
#define fi first
#define se second
#define il inline
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define drep(i,a,b) for(int i=(a);i>=(b);i--)
#define go(i,u) for(int i=head[u];i;i=e[i].nxt)
	typedef long long ll;
	typedef pair<int,int> pii;
	inline int read(){
		int x=0,f=1;char c=gc();
		while(!isdigit(c)){if(c=='-')f=-1;c=gc();}
		while(isdigit(c))x=x*10+c-48,c=gc();
		return x*f;
	}
}
using namespace my_std;
const int N=1e7+7,M=-1,inf=0x3f3f3f3f,mod=0;
int n,m,a[N],Case;ll f[N];
bool fl;
vector<pii> s;vector<pair<int,ll>> t;
void Yorushika(){
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%d",&a[i]),a[n+i]=a[i];
	s.clear(),t.clear();
	drep(i,n*2,1){
		vector<pii> tmp;tmp.clear();tmp.eb(Mp(a[i],i));
		for(auto [j,k]:s)tmp.eb(Mp(j|a[i],k));
		while(tmp.back().se>=i+n)tmp.pop_back();
		sort(tmp.begin(),tmp.end());
		s.clear();
		for(pii j:tmp)if(s.size()<2||j.fi!=s.back().fi||j.fi!=prev(prev(s.end()))->fi)s.eb(j);
		for(auto [j,k]:s){
			int len=k-i+1;
			if(i<=n-len+1||len>1&&i==n-len+2)continue;
			t.eb(Mp(j,len<=2?i-n*(len==1):1ll*(len-1)*(n-1)+(i-(n-len+1))));
		}
	}
	sort(t.begin(),t.end());
	t.eb(Mp(inf,1ll*inf*inf));
	f[(int)t.size()-1]=1ll*inf*inf;
	drep(i,(int)t.size()-2,0)f[i]=min(f[i+1],t[i].se);
	rep(i,1,m){
		int x;scanf("%d",&x);
		int p=upper_bound(t.begin(),t.end(),Mp(x+1,-1ll))-t.begin();
		printf("%lld\n",f[p]>1e12?-1:f[p]);
	}
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

其实那个 corner case 是我设法搞到 cf 数据调出来的。可以参考以下数据：

```
1
6 5
1 0 0 0 0 2 
0
1
2
3
4
```

---

## 作者：EuphoricStar (赞：0)

我们首先观察 $a$ 的形态。令题面中给出的 $a_{1 \sim n}$ 为 $b_{1 \sim n}$。先从 $n$ 比较小的情况开始分析，若 $n = 6$，那么 $a$ 从第 $n + 1$ 位开始长这样（数字拼接代表下标对应的值按位或起来）：

$$12, 23, 34, 45, 56$$

$$612, 123, 234, 345, 456$$

$$5612, 6123, 1234, 2345, 3456$$

$$45612, 56123, 61234, 12345, 23456$$

$$123456 \cdots$$

我们发现 $a$ 的值是由一些环形子区间的按位或组成的，且长度较小的在长度较大的前面。

现在一个简单的想法是对于每个询问都二分找到第一个满足的位置。先二分区间长度，再二分区间左端点。注意到固定左端点，以这个点的后缀按位或最多变化 $O(\log V)$ 次。因此我们可以预处理出 $O(n \log V)$ 个按位或和相同的区间，从而得到固定长度的区间按位或最大值。但是我们发现没办法快速回答左端点在一个区间内，区间长度固定的区间按位或最大值。

考虑离线，枚举区间长度 $i$，将 $O(n \log V)$ 个按位或和相同的区间按照长度从小到大处理，这样我们能顺便用线段树维护，长度为 $i$ 的以每个点为左端点的区间按位或。我们把最短区间长度为 $i$ 的询问放在一起处理，二分区间左端点即可。

[code](https://codeforces.com/contest/1847/submission/212518428)

---

## 作者：Polaris_Australis_ (赞：0)

暴力推出数列的前 $n^2$ 项可以发现，整个序列的每一项都是由原序列首尾相接形成的环上的一个区间，这些区间以长度为第一关键字，末位下标为第二关键字排序，且所有长度大于 $1$ 的区间均不包含以 $1$ 为末位下标的区间。

不难发现，以某一个下标为末位下标的所有区间，最多只有 $\log_2 V$ 种不同的权值（$V=\max\limits_{i=1}^{n}a_i$），而每个权值只有在它第一次出现的时候才会有贡献，所以有用的区间只有 $n\log_2 V$ 个。

求出所有有用的区间并按照长度为第一关键字，末位下标为第二关键字排序，记录权值的前缀最大值，询问二分即可。精细实现可以做到 $\mathcal{O}(n\log_2 V+q\log_2(n\log_2V))$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Umekawa_Kouko{
	void main();
}
int main(){
	return Umekawa_Kouko::main(),0;
}
namespace Umekawa_Kouko{
	const int N=200010;
	int n,q,a[N<<1],mxw[N<<1][30],tot,mx[N<<5],id[N<<1][30],c[N],cc[N<<5],po[N<<5];
	struct node{
		int val,len,bel;
		node(){}
		node(int _val,int _len,int _bel):val(_val),len(_len),bel(_bel){}
	}sta[N<<5];
	void solve(){
		cin>>n>>q;
		for(int i=1;i<=n;++i)cin>>a[i];
		for(int i=1;i<=n;++i)a[i+n]=a[i];
		for(int i=0;i<=29;++i)id[0][i]=i;
		for(int i=1;i<=(n<<1);++i){
			for(int j=0;j<=29;++j){
				mxw[i][j]=mxw[i-1][j];
				if((a[i]>>j)&1)mxw[i][j]=i;
			}
			int tt=-1;
			for(int j=0;j<=29;++j)if(mxw[i][id[i-1][j]]==i)id[i][++tt]=id[i-1][j];
			for(int j=0;j<=29;++j)if(mxw[i][id[i-1][j]]!=i)id[i][++tt]=id[i-1][j];
		}
		tot=0;
		sta[++tot]=node(a[1],1,1);
		for(int i=n+2;i<=(n<<1);++i){
			int t=0;
			for(int zz=0;zz<=29;++zz){
				if((t>>id[i][zz])&1)continue;
				if(i-mxw[i][id[i][zz]]+1>n)break;
				t|=a[mxw[i][id[i][zz]]];
				sta[++tot]=node(t,i-mxw[i][id[i][zz]]+1,i-n);
			}
		}
        for(int i=1;i<=n;++i)c[i]=0;
		for(int i=1;i<=tot;++i)++c[sta[i].bel];
		for(int i=1;i<=n;++i)c[i]+=c[i-1];
		for(int i=1;i<=tot;++i)cc[c[sta[i].bel]--]=i;
		for(int i=1;i<=n;++i)c[i]=0;
		for(int i=1;i<=tot;++i)++c[sta[i].len];
		for(int i=1;i<=n;++i)c[i]+=c[i-1];
		for(int i=tot;i;--i)po[c[sta[cc[i]].len]--]=cc[i];
		for(int i=1;i<=tot;++i)mx[i]=max(mx[i-1],sta[po[i]].val);
		while(q--){
			int v;
			cin>>v;
			if(sta[po[tot]].val<=v){
				cout<<"-1\n";
				continue;
			}
			int l=1,r=tot;
			while(l<r){
				int mid=(l+r)>>1;
				if(mx[mid]>v)r=mid;
				else l=mid+1;
			}
			cout<<1ll*(n-1)*(sta[po[l]].len-1)+sta[po[l]].bel<<"\n";
		}
	}
	void main(){
		ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
		int T;
		cin>>T;
		while(T--)solve();
	}
}
```


---

