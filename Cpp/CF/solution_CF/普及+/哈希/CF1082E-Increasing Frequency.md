# Increasing Frequency

## 题目描述

给你一个长度为 $n$ 的数列 $a$ ,你可以任意选择一个区间 $[l,r]$, 并给区间每个数加上一个整数 $k$, 求这样一次操作后数列中最多有多少个数等于 $c$.

## 样例 #1

### 输入

```
6 9
9 9 9 9 9 9
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 2
6 2 6
```

### 输出

```
2
```

# 题解

## 作者：redegg (赞：17)

很明显的前缀和啊。

首先声明一下用到的几个字符：$x$表示当前枚举的位置，$a$表示输入的序列，$sum_[i][x]$表示数字$i$在$(1~x)$区间的个数，$c$表示所要求的数字，$min[i][x]$表示$i$数字个数与$c$数字个数在$(1,x)$区间的差的最小值，$ans$是答案，$delta$是增量。

$delta=ans-sum[c][n]$

我们可以转化问题，：找到一个$(l,r)$区间，使区间里面数字$i$的个数与数字$c$的个数的差最大，因为我更新$(l,r)$区间，是将某个数字变成$c$，而原本的$c$就会变成其他数字。

我们可以得到，
$delta=max(sum[i][r]-sum[c][r]-sum[i][l-1]+sum[c][l-1],delta)$

$delta=max(sum[i][r]-sum[c][r]-(sum[i][l-1]-sum[c][l-1]),delta)$

那么在此变一下$sum[i][j]$的含义，现在的$sum[i][j]$就是之前的$sum[i][j]-sum[c][j]$。

那么$min[i][x]=min(sum[i][j],min[i][j])$

而要使$delta$最大，delta的转移变成了：$delta=max(delta,sum[i][j]-min[i][j])$。

现在就是最关键的了，我们会发现，如果$a_j=c$，那么$sum[i][j]=sum[i][j-1]-1$ $(i\ne c)$

所以所有满足$i \ne c$的数字$i$，最小值一定是在某一个$a_j=c$后面取到，而最大值是在某一个$a_j=i$后取到。

所以我们没必要维护二维的前缀和$sum$数组和二维的$min$数组，我们可以直接把二维数组最后一维$j$去掉，然后我们只需要在枚举$j$时,当$a_j=i$时，直接更新数字$i$的最小值和$delta$的值，最后直接$ans=delta+sum[c]$就好了。具体看代码（代码中的$ans[i]$表示的是单个数字$i$的$delta$）：

```cpp
#include <bits/stdc++.h>
using namespace std;


int n,c;

int a[600005];
int minn[600005];
int sum[600005];
int ans[600005];

int main()
{
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }

    for(int i=1;i<=n;i++)
    {

        minn[a[i]]=min(sum[a[i]]-sum[c],minn[a[i]]);
        sum[a[i]]++;
        ans[i]=max(ans[i],sum[a[i]]-sum[c]-minn[a[i]]);
    }
    int maxn=sum[c];
    for(int i=1;i<=n;i++)
    {
        maxn=max(maxn,ans[i]+sum[c]);
    }
    printf("%d\n",maxn);
    return 0;
}

```

---

## 作者：Sakura_梦瑶 (赞：15)

我们可以直接考虑贪心,我们考虑以当前数为赋值基准下的最大贡献,这样变成了多意义的最大子段和,每当经过一个m我们的总m数要+1,但是我们如果用一大片的时间去赋值比对很麻烦,这个时候可以开个辅助数组作差,很巧妙的一个思想（我是指这个作差）.
因为看错题目,中途写到一半偷换了自己的概念导致不断wa..

```cpp
#include<bits/stdc++.h>
#define N 1<<22
using namespace std;
int n,m,c,t,cnt,ans,a[N],b[N];
int main(){
	cin>>n>>m;for(int i=1;i<=n;i++){scanf("%d",&c);if(c==m)cnt++;
		else if(c!=m){
			if(a[c]&&a[c]+b[c]-cnt>=0)a[c]+=b[c]-cnt;
			else a[c]=0;b[c]=cnt,a[c]++;ans=max(ans,a[c]);
		} 
	}cout<<ans+cnt;
}
```

---

## 作者：sinsop90 (赞：7)

题意:给定一个序列, 选择一段区间将里面所有数加上一个数, 求操作完之后序列中最多有多少个 $c$。

假设原本的序列中有 $k$ 个 $c$, 想象一下如果我们把一个区间 $[l, r]$ 加上一个数后会发生什么。

显然, 原本等于 $c$ 的数会不等于 $c$, 而原本等于 $c$ 减去加上的那个数的那些数会变成 $c$。

因此, 可以将问题转换为:找到区间 $[l, r]$, 使得里面出现次数最多的数字的个数与 $c$ 的个数最大。

考虑怎么维护一个区间中某个数字的个数, 显然可以用前缀和。

如果我们设 $pre[a_i][x]$ 为数字 $a_i$ 在 $[1,r]$ 出现的个数。

那么 $a_i$ 在 $[l,r]$ 出现的个数就是 $pre[a_i][r] - pre[a_i][l-1]$。

因此, 区间 $[l,r]$ 中 $a_i$ 出现的次数和 $c$ 的个数就是 $pre[a_i][r]-pre[a_i][l-1]-(pre[c][r]-pre[c][l-1])$

也就是 $pre[a_i][r]-pre[c][r]-(pre[a_i][l-1]-pre[c][l-1])$

后面括号里的可以在遍历 $i$ 的时候动态存储, 因此复杂度为 $O(n)$

代码如下:

```
#include <bits/stdc++.h>
#define maxn 500005
using namespace std;
int n, a[maxn], m, minn[maxn], pre[maxn], ans[maxn], ansn = -1;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++) minn[i] = 2147483647;
	for(int i = 1;i <= n;i++) scanf("%d", &a[i]);
	for(int i = 1;i <= n;i++) {
		minn[a[i]] = min(pre[a[i]] - pre[m], minn[a[i]]);
		pre[a[i]] ++;
		ans[i] = max(ans[i], pre[a[i]] - pre[m] - minn[a[i]]);
	}
	for(int i = 1;i <= n;i++) ansn = max(ansn, ans[i] + pre[m]);
	printf("%d\n", ansn);
}
```


---

## 作者：赫鲁老七 (赞：5)


假设当前选择区间的右端点为 $r$，那我们要强制将 $a_r$ 这个元素变为 $c$ （即钦定 $k=c-a_r$ ），不然可以通过让右端点 $-1$ 使答案变得不劣。

同理，对于左端点 $l$ 的元素 $a_l$ 我们也要让其强制等于 $a_r$，不然同样可以通过让左端点 $+1$ 使答案变的不劣。

所以这个性质告诉我们选中的区间 $[l,r]$ 一定满足 $a_l=a_r$。

这启发我们对于每种取值分开做

设 $f(x)$ 是右端点为 $x$ 时最多有多少个元素取到 $c$ 。

考虑列出 $DP$ 式

$f(x)=\max \left\{pre(las-1)+count(las,x)+suf(x+1)\right\}$，其中 $pre(i)$ 表示从 $1\sim i$ 有多少个元素为 $c$，同理 $suf(i)$ 表示从 $i\sim n$ 有多少个元素为 $c$, $count(l,r)$ 表示在区间 $[l,r]$ 里有多少个元素等于这个区间的端点即 $a_r$。

发现如果拿 $vector$ 存的话这是一个单调队列优化 $DP$ 的标准式子

随便优化一下就吼了

### Code

```cpp
#include<bits/stdc++.h>
using std::min;
using std::max;
using std::swap;
using std::vector;
typedef double db;
typedef long long ll;
#define pb(A) push_back(A)
#define pii std::pair<int,int>
#define all(A) A.begin(),A.end()
#define mp(A,B) std::make_pair(A,B)
const int N=5e5+5;

vector<int> v[N];
int n,m,val[N],vis[N],q[N],hd;
int pre[N],suf[N],tot[N],tail;

int getint(){
    int X=0,w=0;char ch=getchar();
    while(!isdigit(ch))w|=ch=='-',ch=getchar();
    while( isdigit(ch))X=X*10+ch-48,ch=getchar();
    if(w) return -X;return X;
}

signed main(){
    n=getint(),m=getint();
    for(int i=1;i<=n;i++)
        val[i]=getint(),pre[i]=pre[i-1]+(val[i]==m),v[val[i]].pb(i);
    for(int i=n;i;i--)
        suf[i]=suf[i+1]+(val[i]==m);
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!vis[val[i]]){
            vis[val[i]]=1;
            hd=1,tail=0;
            for(int j=0;j<v[val[i]].size();j++){
                while(hd<=tail and pre[ v[ val[i] ][ j ] -1 ]-j>=pre[ v[ val[i] ][ q[tail] ] -1 ]-q[tail]) tail--;
                q[++tail]=j;
                if(hd<=tail) ans=max(ans,pre[ v[ val[i] ][ q[hd] ] -1 ]+j-q[hd]+1+suf[ v[ val[i] ][ j ] +1 ]);
            }
        }
    } printf("%d\n",ans);
    return 0;
}

```



---

## 作者：_edge_ (赞：4)

很不错的一道思维题，又被 dp 的标签骗了。

这里提供一种线性，并且 pj 以内的做法。

我们先来分析一下题面的条件，可以发现，我们每一次在一个区间内都只能将一个数变为 $c$，然后会把这个区间内的 $c$ 都抹去。

更具体的，假设 $sum_i$ 表示 $1 \sim i$ 之间 $c$ 的数量。

那么我们选择一个区间 $[l,r]$ 则会产生贡献，$sum_{l-1}+sum_n-sum_r+v$。

其中 $v$ 是我们在区间内产生的贡献，这个值应该最大，所以应该取的是区间的众数。

欸，这个东西乍一看非常的难搞呀，因为有一个区间众数的条件限制的。

但是有一个比较优美的定理，就是我们取的这个区间众数它必然是区间的端点，这个非常好证，可以考虑如果不是就往回缩，而往回缩会使得答案变大。

因此，我们在求这个问题的时候，可以把同一个数的都扔到一个 vector 里面，并且枚举两个点，计算贡献。

然而这样还是会 TLE 起飞，考虑优化这个柿子。

$sum_{v_l-1}+sum_n-sum_{v_r}+r-l+1$。

我们可以移项！

变形，$sum_{v_l-1}-l+sum_n-sum_{v_r}+r+1$。

我们发现前面的 $sum_{v_l-1}-l$ 和后面的 $r$ 没有任何关系，可以直接前缀最大值来维护。

后面的，我们可以枚举 $r$ 来计算贡献。

然后这题就过了。

```cpp
/*
..l...r..
r+1+sumc[v[l]-1]-l+sumc[n]-sumc[v[r]]

*/

#include <iostream>
#include <cstdio>
#include <vector>
#define pb push_back
using namespace std;
const int INF=5e5+5;
int n,m,a[INF],sum[INF],tree[INF];
vector <int> v[INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++) 
		cin>>a[i],v[a[i]].pb(i);
	for (int i=1;i<=n;i++)
		sum[i]=sum[i-1]+(a[i]==m);
	int ans=min(n,sum[n]+1);
	for (int i=1;i<=5e5;i++) {
		int len=v[i].size();if (len<=1) continue;
		int Max=sum[v[i][0]-1]-0;
		for (int j=1;j<len;j++) {
//			if (j==3) cout<<sum[v[i][j]]+Max<<" xiwangren\n";
			ans=max(ans,j+1+Max+sum[n]-sum[v[i][j]]);
			Max=max(Max,sum[v[i][j]-1]-j);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：1saunoya (赞：3)

暴力分治。

每次只考虑跨区间的即可。

设 $mx_i$ 是左边 $i$ 的个数-x的个数

$mx2_i$ 同理，然后答案就是 $\max\{mx_i + mx2_i\}$。

做完了。

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x,I=y+1;i<I;++i)
#define per(i,x,y) for(int i=x,I=y-1;i>I;--i)
using namespace std;
using ll=long long;
void cmax(int&x,const int&y){x=x>y?x:y;}
void cmin(int&x,const int&y){x=x<y?x:y;}
template<class T>istream&operator>>(istream&in,vector<T>&V){for(auto&x:V)in>>x;return in;}
template<class T>ostream&operator<<(ostream&out,const vector<T>&V){for(auto x:V)out<<x<<' ';return out;}
template<class T>void sort(vector<T>&V){sort(V.begin(),V.end());}
template<class T>void reverse(vector<T>&V){reverse(V.begin(),V.end());}
template<class T>int SZ(const vector<T>&V){return (int)V.size();}
void debug(){cerr<<"whxorz"<<'\n';}

const int N = 5e5 + 5;

int n, x;
int a[N];
int ans = 0;
int all = 0;

int cnt[N];
int mx[N], mx2[N];
void solve(int l, int r) {
	if (l == r) { return cmax(ans, all + (a[l] != x)); }
	int mid = l + r >> 1;
	for (int i = l; i <= r; i++) { cnt[a[i]] = 0; mx[a[i]] = 0; }
	for (int i = mid, c = 0; i >= l; i--) {
		if (a[i] == x) { ++c; continue; }
		++cnt[a[i]]; cmax(mx[a[i]], cnt[a[i]] - c);
	}
	for (int i = l; i <= r; i++) { cnt[a[i]] = 0; mx2[a[i]] = 0; }
	for (int i = mid + 1, c = 0; i <= r; i++) {
		if (a[i] == x) { ++c; continue; }
		++cnt[a[i]]; cmax(mx2[a[i]], cnt[a[i]] - c);
	}
	int res = 0;
	for (int i = l; i <= r; i++) { cmax(res, mx[a[i]] + mx2[a[i]]); }
	cmax(ans, res + all);
	solve(l, mid);
	solve(mid + 1, r);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n >> x;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		if (a[i] == x)
			++all;
	solve(1, n);
	cout << ans << '\n';
	return 0;
}

```

---

## 作者：ywy_c_asm (赞：3)

这题直接无脑分治就行了。。。毕竟就是找一个区间的问题。

显然你要找一个区间$[l,r]$满足$maxcnt[l,r]+Ccnt[1,l-1]+Ccnt[r+1,n]$最大，maxcnt为区间众数个数，然后一个比较显然的性质就是你选这个区间的时候让端点为众数并不会使答案更差，所以就分治考虑跨中点的区间，先用前缀和求区间内有多少个c，然后我们先倒着扫一遍左区间，令$f[i]$为左端点的值为i在左区间能够取得的最大收益，就是后缀的$Cnt_i+$左区间剩下部分的c的个数，然后我们正着扫一遍右区间对每个值为$i$的右端点和左区间算出来的$f[i]$合并一下就行了。

上代码~

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
namespace ywy{
	inline int get(){
		int n=0;char c;while((c=getchar())||23333){
			if(c>='0'&&c<='9')break;if(c=='-')goto s;
		}n=c-'0';while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10+c-'0';else return(n);
		}s:while((c=getchar())||23333){
			if(c>='0'&&c<='9')n=n*10-c+'0';else return(n);
		}
	}
	int maxn=0,ints[500001],dp[500001],sums[500001],cnt[500001];
	void digui(int l,int r,int sig){
		if(l==r){
			maxn=max(maxn,sig+1);
			return;
		}
		int mid=(l+r)>>1;
		digui(l,mid,sig+sums[r]-sums[mid]);
		digui(mid+1,r,sums[mid]-sums[l-1]+sig);
		for(register int i=mid;i>=l;i--){
			cnt[ints[i]]++;
			dp[ints[i]]=max(dp[ints[i]],cnt[ints[i]]+sums[i-1]-sums[l-1]);
			maxn=max(maxn,dp[ints[i]]+sig+sums[r]-sums[mid]);
		}
		for(register int i=l;i<=mid;i++)cnt[ints[i]]=0;
		for(register int i=mid+1;i<=r;i++){
			cnt[ints[i]]++;
			maxn=max(maxn,dp[ints[i]]+sig+cnt[ints[i]]+sums[r]-sums[i]);
			maxn=max(maxn,cnt[ints[i]]+sums[r]-sums[i]+sums[mid]-sums[l-1]+sig);
		}
		for(register int i=l;i<=r;i++)cnt[ints[i]]=dp[ints[i]]=0;
	}
	void ywymain(){
		int n=get()，c=get();
		for(register int i=1;i<=n;i++)sums[i]=sums[i-1]+((ints[i]=get())==c);
		maxn=sums[n];
		digui(1,n,0);
		cout<<maxn<<endl;
	}
}
int main(){
	ywy::ywymain();return(0);
}
```

---

## 作者：_ajthreac_ (赞：2)

Sakura 巨神的贪心解释得不太清楚啊……我来尝试复述一下。

首先我们思考答案的构成，它一定是选择一个区间，将区间内的某个数 $x$ 替换为 $c$，再加上剩余部分的 $c$ 组成的。而对于这个 $x$，我们需要找到 $cnt_x-cnt_c$ 最大的那个。

考虑如何动态维护这个东西，发现我们要的是当前位置到上一个 $x$ 这段区间中 $c$ 的个数，如果总的 $c$ 多于了 $x$ 就不能选上这段，这个可以通过记一个 $lst$ 来实现。

以下是代码，代码中 `cnt` 数组记录的是修改数字 $x$ 时带来的最大收益（也就是上文的 $cnt_x-cnt_c$），`lst` 数组记录的是上次遇到 $x$ 时 $c$ 的数量： 

```cpp
const int N=500010;
int n,c,cnt[N],lst[N],tot,res;
int main(){
  Read(n),Read(c);
  for(rg int i=1,x;i<=n;i++){
    Read(x);
    if(x==c)tot++;
    else {
      cnt[x]=max(cnt[x]+lst[x]-tot,0)+1;
      lst[x]=tot,res=max(res,cnt[x]);
    }
  }
  cout<<tot+res<<endl;
  KafuuChino HotoKokoa
}
```

---

## 作者：shao0320 (赞：2)

#### CF1082E Increasing Frequency

考虑选择一段区间$[l,r]$的答案，设$[l,r]$中的众数为$x$，那么答案即为$pre(l-1)+count(l,r,x)+suf(r+1)$，其中$pre$和$suf$是$c$这个数出现次数的前缀和与后缀和。

但这个带着区间众数的做法显然并不好搞，我们这里思考一个问题，假如说这个区间，左右端点并不是区间众数，那么我们就可以把这个区间往里"缩"，直到左右端点都缩成$x$为止，我们设这个缩得的新区间为$[ll,rr]$，那么显然$count(ll,rr,x)=count(l,r,x)$，$pre(l-1)\leq pre(ll-1)$，$suf(r+1)\leq suf(rr+1)$。

那么自然以$[ll,rr]$为操作区间的答案不劣于以$[l,r]$为操作区间的答案。

那考虑对于这些区间进行计算，对于$a$值相同的点我们拿出来跑$dp$，在这里我们直接假设这个$a$值就是区间众数，因为我们枚举这个$a$值总会枚举到区间众数，或者我们直接不管肾么区间众数了，直接就把当前这个$a$值变成$c$。

设$f(x)$表示右端点为$x$的最大答案，那么显然有暴力转移：
$$
f(x)=\max ^{x}_{lst=1 \& a_{lst}=a_x} {pre(lst-1)+count(lst,x,a_x)+suf(x+1)}
$$
也就是枚举左端点。

但是这样做最坏可以被卡到$O(n^2)$。

首先一个显然可以的优化就是因为这个式子可以写成如下形式
$$
f(x)=\max ^{x}_{lst=1 \& a_{lst}=a_x} {pre(lst-1)+count(1,x,a_x)-count(1,lst,a_x)+1+suf(x+1)}
$$
那么这个式子只跟每个决策点$lst$有关，因此直接单调队列即可。

但是没必要这么复杂，我们仔细观察这个式子，对于两个不同的决策点$i,j (i<j)$，当我们要计算的$x\geq j$时，那么随着这个$x$递增的时候，$count(i,x,a_x)$和$count(j,x,a_x)$都会每次加$1$，这说明什么，说明如果最开始$i$就没有$j$优的话那后边也不可能了，反之亦然，因此我们只需要扫过来的时候判断当前决策点优还是之前优即可。

时间复杂度$O(n)$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define N 500005
#define pb push_back
#define MAXN 500000
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,c,a[N],pre[N],suf[N],ans;
vector<int>G[N];
int main()
{
	n=read();c=read();
	for(int i=1;i<=n;i++)a[i]=read(),G[a[i]].pb(i);
	for(int i=1;i<=n;i++)pre[i]=pre[i-1]+(a[i]==c);
	for(int i=n;i>=1;i--)suf[i]=suf[i+1]+(a[i]==c);
	for(int i=1;i<=MAXN;i++)
	{
		if(!G[i].size())continue;
		int siz=G[i].size(),pos=0,maxn=pre[G[i][0]-1];
		ans=max(ans,1+maxn+suf[G[i][0]+1]);
		for(int j=1;j<siz;j++)
		{
			if((j-pos+1)+maxn>=1+pre[G[i][j]-1])ans=max(ans,(j-pos+1)+maxn+suf[G[i][j]+1]);
			else pos=j,maxn=pre[G[i][j]-1],ans=max(ans,1+pre[G[i][j]-1]+suf[G[i][j]+1]);
		}
	}
	printf("%d\n",ans);
	return 0;
}

```



---

## 作者：Wf_yjqd (赞：1)

看似很难，其实但凡试一试，就觉得很水。

------------

首先贪心，把总共 $c$ 的个数求出来，答案必定大于等于它。

需要线性 dp，考虑先转化问题。

求子区间内任意数与 $c$ 的出现个数差值的最大值加上 $c$ 的总个数。

$c$ 的个数可用前缀和维护，但前者前缀和的空间复杂度太大了。

所以考虑预处理每个数上次出现的位置，用每段的贡献转移，最后合并并取出最大值。

具体来说，用 $last_i$ 表示上一个值为 $a_i$ 的位置，$dp_i$ 表示以第 $i$ 个为结尾的区间中，$a_i$ 和 $c$ 出现次数差的最大值。

有 $dp_i=\max(0,dp_{last_i}-(cnt_i-cnt_{last_i}))+1$。

这类似于一个最大子段和问题，如果总的答案小于 $1$，就重新开始一个区间。

时间复杂度 $\operatorname{O}(n)$。

------------

模拟赛时现推的，有疏漏请指出。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+84;
int n,c,ans,a[maxn],dp[maxn],last[maxn],lst[maxn],cnt[maxn];
int main(){
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        last[i]=lst[a[i]];
        lst[a[i]]=i;
        cnt[i]=cnt[i-1]+(a[i]==c);
    }
    for(int i=1;i<=n;i++){
        if(a[i]==c)
            continue;
        dp[i]=max(0,dp[last[i]]-(cnt[i]-cnt[last[i]]))+1;
        ans=max(ans,dp[i]);
    }
    printf("%d",ans+cnt[n]);
    return 0;
}
```


---

## 作者：stansxt (赞：1)

# 前言
- [这是我的提交记录](https://www.luogu.com.cn/record/54661354) 。当时是最快的，复杂度严格$O(n)$。

# 思路
- 分为两个点。
- 第一，题目是让我们找一个区间 $[l,r]$ 的众数并加上区间外的 $c$ 的数量。进行一步转化，变成区间内众数减去 $c$ 的数量，再加上所有 $c$ 的数量。


- 这时候我们钦定区间最右端的数 $a[r]$ 为该区间的众数。因为若众数不是 $a[r]$ 而是 $a[j]$ 那么区间 $[l,j]$ 的答案一定不比 $[l,r]$ 劣。

- 第二，我们可以从左往右扫一遍 $r$。那么 $l$ 怎么办呢？注意到此时相当于是要求一个最大子段和，那么我们直接暴力维护一个当前的 $a[r]$（这里开个桶就行了）减去当前段的 $c$ 的数量，如果是负的那么就置成1（新开一段），否则直接加上。注意到这里的难点是怎样维护当前段 $c$ 的数量。我的做法是：维护一个变量表示当前总共几个 $c$，再维护一下上次遇到 $a[r]$ 这个数是 $c$ 的数量，两者相减即可。

- 到这里，这题就做完了。感觉难度其实并不高，主要是需想到第一步的转化，和第二步维护当前段 $c$ 的数量。

- 代码我放在 [云剪贴板](https://www.luogu.com.cn/paste/o840dulz) 里面了，本题实现并不难，代码也很短，希望大家尽量自己写，实在调不对可以参考我的代码。

-----
### 谢谢观看！

---

## 作者：wcyQwQ (赞：0)

简单题，设 $pre_i$ 表示上一个和 $a_i$ 相同的位置，$f_i$ 表示 $[1, i]$ 中有多少和 $a_i$ 相同的数，$g_i$ 表示 $[1, i]$ 中有多少个 $c$。然后我们考虑枚举 $i$，统计操作右端点为 $i$ 时的答案，显然地，我们会贪心的把左端点选在和 $a_i$ 相同的位置上，我们设这个位置是 $j$，那么此时的答案即为 $g_n + (f_i - f_{pre_j}) - (g_i - g_{j - 1})$（这里是通过计算增加的贡献来统计答案），然后我们发现其实只要求 $f_{pre_j} - g_{j - 1}$ 的最小值即可，我们对于每一个 $a_i$ 都开桶维护最小值即可。

时间复杂度 $O(n)$。[Code](https://codeforces.com/contest/1082/submission/205997781)

---

## 作者：JasonL (赞：0)

### CF1082E 【Increasing Frequency】

[题目传送门](https://www.luogu.com.cn/problem/CF1082E)

#### 分析

提供一个链表实现的贪心做法。

首先我们注意到不在选择区间外的数也可能对答案作出贡献。假定我们在最优方案中选择的改为$c$的数字为$b$。那么我们的答案应该为

$\max(cnt[1][l-1]+f[l][r]+cnt[r+1][n]),l,r\in[1,n]$

其中$cnt[i][j]$表示$[i,j]$区间内权值为$c$的个数，$f[i][j]$表示$[i,j]$区间内权值为$b$的个数。

我们也可以这样看：在修改前，我们的所有数字都没有改变。此时的答案为$cnt[1][n]$。现在我们要选定一个区间进行修改，而这个区间的最大贡献就应该为区间中出现最多的数字个数减去区间中权值为$c$的数的个数。这样计算的答案为

$cnt[1][n]+\max\limits_{1\le l\le r\le n} (f[l][r]-cnt[l][r])$

当我们选定好要修改的数字，我们可以将数列$a$变成这样的一个模型：

$-cnt[p_0][p_1],1,-cnt[p_1][p_2],1,-cnt[p_2][p_3],1\dots$

其中$1$的位置对应原先数列$a$中权值为$b$的数的位置。而两个$1$中间夹着的就是原数列的两数所夹区间内权值为$c$的数的个数。

那么我们只需要对它求最大子段和即可，等价于求$\max\limits_{1\le l\le r\le n} (f[l][r]-cnt[l][r])$。

这里我们可以先通过前缀和求得$cnt$，然后通过链表在上面做最大子段和。最大子段和可以贪心（累加后若为负数则舍去归0，否则可以保留，为后面的区间带来更大贡献）。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=510000;
int n,c,ans;
int head[maxn],nxt[maxn],cnt[maxn];
bool vis[maxn];
inline int read(){
	int res=0;
	char ch=getchar(),ch1=ch;
	while(!isdigit(ch))ch1=ch,ch=getchar();
	while(isdigit(ch))res=(res<<3)+(res<<1)+ch-'0',ch=getchar();
	return ch1=='-'?-res:res;
}
int main(){
	n=read();c=read();
	for(register int i=1,x;i<=n;++i){
		x=read();
		nxt[i]=head[x];head[x]=i;
		if(x==c){
			++cnt[i];vis[i]=true;
		}
		cnt[i]+=cnt[i-1];
	}
	ans=cnt[n];
	for(register int i=n;i;--i){
		if(vis[i])continue;
		for(register int j=i,dval=1;j;j=nxt[j]){
			vis[j]=true;
			ans=max(ans,dval+cnt[n]);
			dval=1+max(0,dval-(cnt[j]-cnt[nxt[j]]));
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

