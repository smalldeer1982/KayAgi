# Chopping Carrots (Hard Version)

## 题目描述

这是该问题的困难版本。两个版本间的区别仅为 $n$、$k$、$a_i$ 和 $\sum n$ 的上界。

注意不正常的空间限制。

给出长度为 $n$ 的整数数组 $ a_1, a_2, \ldots, a_n $，以及一个整数 $k$。

一个长度为 $n$ 的整数数组 $ p_1, p_2, \ldots, p_n $ 的花费为 $\max\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right) - \min\limits_{1 \le i \le n}\left(\left \lfloor \frac{a_i}{p_i} \right \rfloor \right)$。
此处，$ \lfloor \frac{x}{y} \rfloor $ 表示 $x$ 除以 $y$ 的整数部分。
请找到花费最小的数组 $p$，且满足对任意 $ 1 \le i \le n$ 都有 $ 1 \le p_i \le k $。

## 说明/提示

在第一个测试组中，最优的数组是 $ p = [1, 1, 1, 2, 2] $。
$ \lfloor \frac{a_i}{p_i} \rfloor $ 得到的结果数组为 $ [4, 5, 6, 4, 5] $。
数组 $p$ 的花费为 $ \max\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) - \min\limits_{1 \le i \le n}(\lfloor \frac{a_i}{p_i} \rfloor) = 6 - 4 = 2 $。
可以证明，没有（满足题目条件的）数组的花费更小。

在第二个测试组中，最优的数组之一为 $ p = [12, 12, 12, 12, 12] $，它使得所有的 $ \lfloor \frac{a_i}{p_i} \rfloor $ 的值都为 $0$。

在第三个测试组中，唯一可能的数组为 $ p = [1, 1, 1] $。

## 样例 #1

### 输入

```
7
5 2
4 5 6 8 11
5 12
4 5 6 8 11
3 1
2 9 15
7 3
2 3 5 5 6 9 10
6 56
54 286 527 1436 2450 2681
3 95
16 340 2241
2 2
1 3```

### 输出

```
2
0
13
1
4
7
0```

# 题解

## 作者：hgzxwzf (赞：9)

## 解题思路：
### D1:
$n,k\le3000$，直接暴力 $O(n^2)$。

首先预处理出来每个数字 $a_i$ 当 $p\in[1,k]$ 时 $\lfloor \frac{a_i}{p}\rfloor$ 能取到的值。

然后枚举最大值，再用二分找到对于每个 $i$ 的最接近但比枚举到的最大值小的 $\lfloor \frac{a_i}{p}\rfloor$，记为 $w_i$，取所有 $w_i$ 的最小值即可，最后的答案就是最小的最大值减最小值。

#### 代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
using namespace std;

const int N=3000+10;

int a[N],te[N][N];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(te,0,sizeof(te));
		int n,k;
		scanf("%d%d",&n,&k);
		rep(i,1,n) scanf("%d",&a[i]);
		rep(i,1,n)
			per(j,1,k)
				te[i][++te[i][0]]=a[i]/j;
		int ans=1e9;
		rep(i,1,3000)
		{
			bool f=1;
			int mmin=1e9;
			rep(j,1,n)
			{
				int pos=upper_bound(te[j]+1,te[j]+1+te[j][0],i)-te[j]-1;
				if(pos==0) {f=0;break;}
				mmin=min(mmin,te[j][pos]);
			}
			if(f) ans=min(ans,i-mmin);
		}
		printf("%d\n",ans);
	 }
	return 0;
 } 
```
### D2：
$n,k\le100000$，$n^2$ 肯定不太行。

观察到预处理部分可以用数论分块把时间优化到 $O(n\sqrt{n})$。

但如果把所有的 $\lfloor \frac{a_i}{p}\rfloor$ 可能的取值都存下来空间会炸，实际上我们只关心比一个数小的最大数。

对于每个 $i$，首先得到 $\lfloor \frac{a_i}{p}\rfloor$ 可能的取值，记录在 $te$ 中，然后排序，执行：
```cpp
rep(j,1,tot) mx[te[j]]=max(mx[te[j]],te[j+1]);
```
$te_{j+1}$ 就是 $te$ 中比 $tr_j$ 大的最小数，$mx$ 是全局数组。

求答案：
```cpp
rep(i,0,100000)
{
	ans=min(ans,mmax-i);
	mmax=max(mmax,mx[i]);
}
```
首先 $mmax$ 一定大于等于 $i$，因为 $mmax\ge mx_{i-1}$，而 $mx_{i-1}>i-1$，所以 $mmax\ge i$。

其次 $mmax$ 一定是能取到的大于等于 $i$ 的数中最小的。

#### 代码：
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)

using namespace std;

const int N=1e5+10;

void R(int &x)
{
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
}

int a[N],te[N],mx[N];

inline int get(int l,int n)
{
	return n/(n/l);
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(mx,0,sizeof(mx));
		int n,k,mmax=0;
		R(n),R(k);
		rep(i,1,n) R(a[i]);
		rep(i,1,n)
		{
			int tot=0;
			for(int l=1,r=0;l<=min(k,a[i]);l=r+1)
			{
				r=get(l,a[i]);
				te[++tot]=a[i]/l;
			}
			if(k>a[i]) te[++tot]=0;
			reverse(te+1,te+1+tot);
			mmax=max(mmax,te[1]);
			te[tot+1]=1e9;
			rep(j,1,tot) mx[te[j]]=max(mx[te[j]],te[j+1]);
		}
		int ans=1e9;
		rep(i,0,100000)
		{
			ans=min(ans,mmax-i);
			mmax=max(mmax,mx[i]);
		}
		printf("%d\n",ans);
	 }
	return 0;
 } 
```


---

## 作者：ExplodingKonjac (赞：9)

**[原题链接](https://www.luogu.com.cn/problem/CF1706D2)**

本题和 [D1](https://www.luogu.com.cn/problem/CF1706D1) 的唯一区别是数据范围。

## 题目分析

题意：给长度为 $n$ 的序列 $a$ 和正整数 $k$，你需要构造一个序列 $p$，最小化 $\displaystyle\max_{i=1}^n\left\{\left\lfloor\frac{a_i}{p_i}\right\rfloor\right\}-\displaystyle\min_{i=1}^n\left\{\left\lfloor\frac{a_i}{p_i}\right\rfloor\right\}$。输出最小值。

设 $b_i=\left\lfloor\dfrac{a_i}{p_i}\right\rfloor$。假设我们限定了一个区间 $[l,r]$，要求所有 $b_i$ 都能够在这个区间内取到值。那么答案就是可行区间的最小的 $r-l$。

考虑一个双指针，我自小到大枚举 $r$，不断尝试收缩 $l$，并时刻更新答案。那么我们要解决的问题就是加入或删除一个数后判断是否可行。

根据[整除分块](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)的结论，$b_i$ 的数量是 $O(\sqrt a_i)$ 的。所以我们可以用整除分块的那套技巧找到所有可行 $b_i$，并且在这些 $b_i$ 位置上挂上一个 $i$。这样在双指针扫的时候，对于每个 $i$ 维护一个 $cnt_i$，表示当前区间内有多少个合法的 $b_i$，当 $cnt_i>0$ 时称 $i$ 被满足。于是就可以维护出一个 $tot$ 表示被满足的 $i$ 的数量，当前区间可行等价于 $tot=n$。$a_i$ 与 $n$ 同阶，复杂度 $O(n\sqrt n)$。

但是你发现这题空间限制只有 $\text{64MB}$。所以不能存下来所有 $b_i$。

但是 $b_i$ 是可以在线地求出来的。把双指针方向改成从右往左，对于 $l$ 和 $r$ 分开考虑。存下来每个 $i$ 当前的 $p_i$，在 $a_i$ 上挂一个 $i$。当在一个位置上找到了 $i$ 时，用整除分块的方法更新 $p_i\gets\lfloor a_i/\lfloor a_i/p_i\rfloor\rfloor$，然后在新的 $b_i$ 上挂上 $i$，处理完这个位置后及时清空内存。这样就可以保证空间为 $O(n)$ 了。如果不懂可以参考一下代码。

## 代码实现

一个细节：如果你使用 `std::vector`，注意 `vector::clear()` **不会释放内存**，如果你要释放内存，可以这么干：`vector<int>().swap(vec)`。

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

int T,n,m,k,ans,a[100005],pl[100005],pr[100005];
int tot,cnt[100005];
vector<int> ql[100005],qr[100005];
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n>>k,m=0;
		for(int i=1;i<=n;i++) qin>>a[i],cnt[i]=0,m=max(m,a[i]);
		for(int i=0;i<=m;i++)
		{
			vector<int>().swap(ql[i]);
			vector<int>().swap(qr[i]);
		}
		for(int i=1;i<=n;i++)
		{
			pl[i]=1,ql[a[i]].push_back(i);
			pr[i]=1,qr[a[i]].push_back(i);
		}
		tot=0,ans=1e9;
		for(int l=m,r=m;l>=0;l--)
		{
			for(auto &i: ql[l])
			{
				if(!cnt[i]++) tot++;
				pl[i]=a[i]/(a[i]/pl[i])+1;
				if(pl[i]<=min(a[i],k)) ql[a[i]/pl[i]].push_back(i);
			}
			vector<int>().swap(ql[l]);
			while(tot==n && r>=l)
			{
				ans=min(ans,r-l);
				for(auto &i: qr[r])
				{
					if(!--cnt[i]) tot--;
					pr[i]=a[i]/(a[i]/pr[i])+1;
					if(pr[i]<=min(a[i],k)) qr[a[i]/pr[i]].push_back(i);
				}
				vector<int>().swap(qr[r--]);
			}
		}
		qout.writeln(ans);
	}
	return 0;
}
```


---

## 作者：xuanxuan001 (赞：5)

我的做法不太一样，所以发一篇题解。

考虑二分极差 $ans$。验证时维护一个值域数组，对于每个数 $a_i$，它可能除出来的结果至多有 $O(\sqrt n)$ 个，对于每个结果 $x = \lfloor \dfrac{a_i}{y} \rfloor$，将区间 $[x-ans,x]$ 加一，注意要将所有的区间取并再加，否则可能会出现一个位置被加多次的情况。

具体就是设 $b = \sqrt a_i$，然后对于 $y \le b$ 的情况，直接枚举 $y$ 即可，对于 $y > b$ 的部分（如果还有）就是区间 $[\lfloor \dfrac{a_i}{k} \rfloor,\lfloor \dfrac{a_i}{b+1} \rfloor]$ 中的所有数，对应到数组区间就是区间 $[\lfloor \dfrac{a_i}{k} \rfloor-ans,\lfloor \dfrac{a_i}{b+1} \rfloor]$。

然后由于每次加的区间下标不断下降，所以记一下上次区间加到了哪个点，下次右端点对这个取 $\min$ 就可以避免重复统计，或者判断与上一个有重叠就合并两个区间（我赛时这么写的）。

区间加可以用一个差分维护，最后看一下数组中有没有一个位置的值是 $n$，有就 $r=mid$，否则 $l=mid+1$。

最后复杂度 $O(n \sqrt a \log a)$。

代码
```cpp
#include<cstdio>
#define TY int
#define MAXN 100002
#define debug if( 1 &&putchar('>'))
#define FOR(i,a,b) for(TY i=(a);i<=(b);++i)
#define fOR(i,a,b) for(TY i=(a);i<(b);++i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);--i)
#define rOF(i,a,b) for(TY i=(a);i>(b);--i)
using namespace std;
typedef long long ll;
const TY M=998244353;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(b&1)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10,0);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY T=qr(),n,k,a[MAXN],b[MAXN],c[MAXN],sqr[MAXN],lst,p,q,l,r,mid;
bool check(TY x){
	fOR(i,1,MAXN)c[i]=0;//差分数组
	FOR(i,1,n){
		lst=MAXN<<1;//lst记录个区间的左端点
		if(b[i]>=k){//没有y>b部分
			FOR(j,1,k){
				if(a[i]/j+x+1<lst){
					if(lst<(MAXN<<1))++c[maxn(1,lst-x)];
					--c[a[i]/j+1];
				}lst=a[i]/j;
			}++c[maxn(1,lst-x)];continue;
		}FOR(j,1,b[i]){
			if(a[i]/j+x+1<lst){
				if(lst<(MAXN<<1))++c[maxn(1,lst-x)];
				--c[a[i]/j+1];
			}lst=a[i]/j;
		}p=a[i]/k;q=a[i]/(b[i]+1);
		//赛时由于这里写了个q=a[i]/b[i]-1而fst了。。。
		//整除分块的边界一定要想清楚，一段时间不写又忘了。。。
		//但我D1也交的这个代码居然没fst
		if(q+x+1<lst){
			if(lst<(MAXN<<1))++c[maxn(1,lst-x)];
			--c[q+1];
		}++c[maxn(1,p-x)];
	}fOR(i,1,MAXN){
		c[i]+=c[i-1];
		if(c[i]==n)return true;
	}return false;
}int main(){
	fOR(i,1,316)fOR(j,i*i,(i+1)*(i+1))sqr[j]=i;
	fOR(i,99856,MAXN)sqr[i]=316;//预处理每个数的sqrt向下取整
	while(T--){
		n=qr();k=qr();l=0;r=MAXN;
		FOR(i,1,n)b[i]=sqr[a[i]=qr()];
		while(l<r){
			mid=l+r>>1;
			if(check(mid))r=mid;
			else l=mid+1;
		}qw(l,'\n');
	}return 0;
}
```

---

## 作者：happy_dengziyue (赞：3)

### 1 视频题解

![](bilibili:BV1S94y1Q7zs)

### 2 思路

我们可以发现，根据整除分块的思想，$\lfloor\dfrac{a_i}{p_i}\rfloor$ 的取值最多只有 $\sqrt{a_i}$ 的可能。

所以，我们可以将 $p_i$ 先全部取为 $k$，这样可以得到最小的 $\max_{i=1}^n\{\lfloor\dfrac{a_i}{p_i}\rfloor\}$。

然后，我们使用优先队列，不断调整最小值，同时更新最大值，最终得出答案。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
#define max_n 100000
#define inf 0x3f3f3f3f
int t;
int n;
int k;
int a[max_n+2];
int p[max_n+2];
int w[max_n+2];
struct Q{
	int w,id;
	bool operator<(const Q&a)const{
		return a.w<w;
	}
};
priority_queue<Q>q;
int ansma;
int ansmi;
int ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1706D2_2.in","r",stdin);
	freopen("CF1706D2_2.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i)scanf("%d",a+i);
		sort(a+1,a+n+1);
		while(!q.empty())q.pop();
		ansma=-inf;
		ansmi=inf;
		for(int i=1;i<=n;++i){
			p[i]=k;
			w[i]=a[i]/p[i];
			q.push((Q){w[i],i});
			ansma=max(ansma,w[i]);
			ansmi=min(ansmi,w[i]);
		}
		ans=ansma-ansmi;
		while(true){
			int x=q.top().id;
			q.pop();
			ans=min(ans,ansma-w[x]);
			if(ans==0)break;
			++w[x];
			if(p[x]==1)break;
			p[x]=a[x]/w[x];
			w[x]=a[x]/p[x];
			q.push((Q){w[x],x});
			ansma=max(ansma,w[x]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/80266038)

By **dengziyue**

---

## 作者：zmza (赞：2)

这个做法好像不是很一样。

首先，考虑枚举 $\min$，然后算最大值。怎么算最大值呢？发现枚举 $\min$ 时能将序列按照值域每 $x$ 个分为一段，然后这一段的最大的 $p$ 都是一样的。所以我们取出这一段内最大的值，用它除以这个最大的 $p$ 和目前的最大值取 $\max$ 即可。注意，$\min$ 只能枚举到 $a_1$。因为最大的最小值就是 $a_1$。然后还要将最大值和 $\lfloor\frac{a_n}{k}\rfloor$ 取 $\max$。因为有可能最大的 $p$ 超过了 $k$，没有办法取到。时间复杂度是一个调和级数和二分查找，$O(n \log^2n)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int n, k, a[maxn];
void solve()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	n = unique(a + 1, a + 1 + n) - a - 1;
	int ans = 1e9, maxx = 0, minn = 1e9;
	for (int i = 1; i <= n; i++) maxx = max(maxx, a[i] / k), minn = min(minn, a[i] / k);
	ans = maxx - minn;
	for (int i = 1; i <= a[1]; i++) //枚举最小的值 
	{
		maxx = i;
		for (int j = 1; j <= min(k, a[n] / i); j++)
			maxx = max(maxx, a[lower_bound(a + 1, a + 1 + n, (j + 1) * i) - a - 1] / j);
		maxx = max(maxx, a[n] / k);
		ans = min(ans, maxx - i);
	}
	cout << ans << '\n';
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：RuntimeErr (赞：2)

怎么好像没看到有人介绍官方的做法？这里写一篇题解。

通过 [弱化版本](https://www.luogu.com.cn/problem/CF1706D1) 我们知道可以枚举最小值 $v\in[0,a_1]$（注意 $a$ 是递增给出的），对于 $1\le i\le n$ 计算  $\max_{i=1}^n (\left\lfloor\frac{a_i}{p_i}\right\rfloor)-v $ 的最小值，其中 $p_i$ 尽量大，这可以通过 $p_i=\left\lfloor\frac{a_i}{v}\right\rfloor$ 得到。时间复杂度是 $O(n\times a_1)$。

这个做法的瓶颈就是对于枚举的每一个 $v$ 都要 $O(n)$ 算一遍能取到的最大值，考虑如何通过预处理优化这个过程。

记 $maxn(v)$ 表示当取 $v$ 为最小值时，取到的最大值，也就是上面 $O(n)$ 算的东西。考虑每个 $a_i$ 对其有什么影响。

注意到 $\left\lfloor\frac{a_i}{p_i}\right\rfloor$ 的取值只有 $O(\min(k,\sqrt{a_i}))$ 种（整除分块的结论），记为 $s_1,s_2,...,s_x$，显然对于 $s_j<v\le s_{j+1}$，$maxn(v)$ 至少为 $s_{j+1}$。于是我们可以用 $s_{j+1}$ 去更新 $maxn(s_j+1)$，最后计算答案的时候扫描一遍就可以了。总共时间复杂度 $O((\sum_{i=1}^n\min(k,\sqrt{a_i}))+a_1)$。

```cpp
int n,k,a[N],maxn[N];

void solve(){
    read(n),read(k);
    memset(maxn,0,sizeof maxn);
    for(int i=1;i<=n;++i){
        read(a[i]);int pre=-1,cur;
        //注意这里枚举取值是递减的，所以是用 pre 更新 cur+1
        for(int j=1;j<=min(a[i],k);j=(a[i]/(a[i]/j))+1){
            cur=a[i]/j;
            maxn[cur+1]=max(maxn[cur+1],pre);
            pre=cur;
        }maxn[0]=max(maxn[0],pre);
    }
    int qwq=0,ans=1e9;
    for(int i=0;i<=a[1];++i){
        qwq=max(qwq,maxn[i]);
        ans=min(ans,qwq-i);
    }printf("%d\n",ans);
}
```


---

## 作者：Erica_N_Contina (赞：1)

## 思路

### EV

$1 \le n, k \le 3000$，$1 \le a_1 \le a_2 \le \ldots \le a_n \le 3000$，$\sum n \le 3000$。

我们发现 $V$（值域）不大，所以我们可以预处理出来每个数字 $a_i$​ 当 $p∈[1,k] $ 时 $\lfloor\frac{a_i}{p}\rfloor $ 能取到的值，记录在二维 vector $v_i$ 中。然后我们在 $V$ 里面枚举最大值 $maxn$。对于最小值，我们对于每一个 $i$ 都用二分在 $v_i$ 中找到小于等于 $maxn$ 的最大的值 $v_{i,k}$，我们记为 $minn_i$。最后我们在 $minn_i$ 中去最小值就是当前 $maxn$ 对应的 $minn$ 了。

每次枚举 $maxn$ 我们都求出一个最终的 $minn$，然后我们用 $maxn-minn$ 更新答案即可。时间复杂度是 $O(n^2+n\log n)$。对于预处理的 $O(n^2)$，我们可以用数论分块来优化到 $O(n\sqrt n)$。


### HV

简单版在此，可能可以帮助开阔思路。

[www.luogu.com.cn](https://www.luogu.com.cn/problem/CF1706D1)


$1 \le n, k \le 10^5$，$1 \le a_1 \le a_2 \le \ldots \le a_n \le 10^5$， $\sum n \le 10^5$。

对于加强版，我们不能用普通版的算法了。除了对预处理的**数论分块优化**，我们还要优化空间复杂度。


我们要知道我们都预处理的目的是什么——我们还是在 $V$ 中枚举 $maxn$，然后我们要对于每一个 $a_i$ 求小于 $maxn$ 的最大的取值，然后在这些取值中取最小值。那么我们在预处理时只记录对于每一个 $maxn$ 我们 $minn$ 所有取值中的最小值即可。

事实上，这里我们可以在 $V$ 中**枚举 $minn$**，然后求出对于每一个数 $x\in V$，小于它的最大的、$\lfloor\frac{a_i}{p}\rfloor $ 能取到的数是多少。最后我们在枚举 $minn$ 时不断转移当前可以取到的最小的 $maxn$，就可以 $O(1)$ 得到大于 $minn$ 的可以被取到的最小值了。

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
const int E=1e6;
const int M=1e9;

#define rd read()
inline int read() {
    int xx = 0, ff = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            ff = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') xx = xx * 10 + (ch - '0'), ch = getchar();
    return xx * ff;
}
inline void write(int out) {
    if (out < 0)
        putchar('-'), out = -out;
    if (out > 9)
        write(out / 10);
    putchar(out % 10 + '0');
}


int n,K,m;
int a[N],stk[N],top,T;
map<int,int>cnt;
int ans;
int k,maxn;
int tmp[N],nxt[N];

void solve(){

	for(int i=1;i<=n;i++){
        int tot=0,r=0;
        for(int l=1;l<=min(k,a[i]);l=r+1) {//数论分块
            r=a[i]/(a[i]/l);
            tmp[++tot]=a[i]/l;
        }
        if(k>a[i]) tmp[++tot]=0;//特殊处理k>a_i的情况
        maxn=max(maxn,tmp[tot]);
        tmp[0]=M;
        for(int j=tot;j;j--)nxt[tmp[j]]=max(nxt[tmp[j]],tmp[j-1]);
    }


    ans=M;
    for(int i=0;i<=E;i++){//枚举最小值
        ans=min(ans,maxn-i);
        maxn=max(maxn,nxt[i]);//nxt记录的就是i时能取到的最小的，因此这里取max而不是取min因为要保证可取性
    }
    printf("%d\n",ans);
}

signed main() {
	
	T=rd;
	while(T--){
        memset(nxt,0,sizeof(nxt));
        maxn=0;
        n=rd,k=rd;
        for(int i=1;i<=n;i++)a[i]=rd;
		solve();
	}

	return 0;
}

```


---

## 作者：Leasier (赞：1)

Update on 2020.7.30：感谢 [Stinger](https://www.luogu.com.cn/user/361308)。

前置芝士：[数论分块](https://oi-wiki.org/math/number-theory/sqrt-decomposition/)、[线段树](https://oi-wiki.org/ds/seg/)

请先查看[这篇](https://www.luogu.com.cn/blog/Leasier/solution-CF1706D1)题解。

注意到对于每个 $a_i$，如果 $\lceil \frac{a_i + 1}{x + 1} \rceil = \lfloor \frac{a_i}{x + 1} \rfloor + 1$ 相等，其对满足条件的所有 $x$ 所对应的 $y$ 贡献恒定。

由于 $y$ 的贡献为取 $\min$ 的形式，我们可以通过对所有 $a_i$ 数论分块求得 $x + 1$ 贡献恒定的区间，并将该区间内的每个 $y$ 值与 $\lfloor \frac{a_i}{\lceil \frac{a_i + 1}{x + 1} \rceil} \rfloor$ 取 $\min$，最后扫一遍即可。这个操作显然可以用一棵维护区间 $\min$ 的线段树维护。时间复杂度为 $O(\sum \log a_n \sum \sqrt{a_i})$。

但这样是无法通过的，因为数论分块和线段树的常数均较大。于是我们在区间较短时（我这里取的是 $r - l + 1 \leq 10$）暴力取 $\min$ 即可。

但实际上我们也可以用 ST 表维护区间取 $\min$，因为查询只有一次且是整体查询。具体操作为每次将普通 ST 表维护的区间 $\min$ 跟当前值取 $\min$，最后扫一遍下放即可。时间复杂度为 $O(\sum (a_n \log a_n + \sum \sqrt{a_i}))$。

代码：
```cpp
#include <stdio.h>

typedef struct {
	int l;
	int r;
	int tag;
	int min;
} Node;

int a[100007], val[100007];
Node tree[400007];

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	tree[x].tag = tree[x].min = 1e9;
	if (l == r){
		val[l] = 1e9;
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
}

inline int min(int a, int b){
	return a < b ? a : b;
}

inline void pushdown(int x){
	if (tree[x].tag != 1e9){
		int ls = x * 2, rs = x * 2 + 1;
		tree[ls].tag = min(tree[ls].tag, tree[x].tag);
		tree[rs].tag = min(tree[rs].tag, tree[x].tag);
		tree[ls].min = min(tree[ls].min, tree[x].tag);
		tree[rs].min = min(tree[rs].min, tree[x].tag);
		tree[x].tag = 1e9;
	}
}

inline void update(int x){
	tree[x].min = min(tree[x * 2].min, tree[x * 2 + 1].min);
}

void modify(int x, int l, int r, int k){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].tag = min(tree[x].tag, k);
		tree[x].min = min(tree[x].min, k);
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) modify(x * 2, l, r, k);
	if (r > mid) modify(x * 2 + 1, l, r, k);
	update(x);
}

int dfs(int x){
	if (tree[x].l == tree[x].r) return tree[x].l - min(tree[x].min, val[tree[x].l]);
	pushdown(x);
	return min(dfs(x * 2), dfs(x * 2 + 1));
}

int main(){
	int t;
	scanf("%d", &t);
	for (register int i = 1; i <= t; i++){
		int n, k;
		scanf("%d %d", &n, &k);
		for (register int j = 1; j <= n; j++){
			scanf("%d", &a[j]);
		}
		int l = a[n] / k + 1;
		build(1, l - 1, a[n]);
		for (register int j = 1; j <= n; j++){
			modify(1, a[j], a[n], a[j]);
			for (register int x = l, y; x <= a[j]; x = y + 1){
				int ta = a[j] / x;
				y = a[j] / ta;
				if (y - x + 1 <= 10){
					int cur = a[j] / (ta + 1);
					for (register int z = x - 1; z < y; z++){
						val[z] = min(val[z], cur);
					}
				} else {
					modify(1, x - 1, y - 1, a[j] / (ta + 1));
				}
			}
		}
		printf("%d\n", dfs(1));
	}
	return 0;
}
```

---

## 作者：lgvc (赞：1)

小萌新第一次 AK div2。 ![](https://啧.tk/hsh)

我们可以先考虑 D1 的做法。

可以先枚举 $\min\limits_{1 \le i \le n}\left(\left \lfloor \dfrac{a_i}{p_i} \right \rfloor \right)$ ，然后 $\mathcal O(n)$ 扫描一遍，算出 $\max\limits_{1 \le i \le n}\left(\left \lfloor \dfrac{a_i}{p_i} \right \rfloor \right)$ 的最小值，并更新答案。

时间复杂度 $\mathcal O(n\cdot a_n)$。

[AC code for D1](https://www.luogu.com.cn/paste/sdn1pfhf)

然后考虑 D2。

考虑继续使用上述做法，不过使用一棵线段树来维护 :

 > 如果 $\min\limits_{1 \le i \le n}\left(\left \lfloor \dfrac{a_i}{p_i} \right \rfloor \right)$ 为 $i$，那么 $\max\limits_{1 \le i \le n}\left(\left \lfloor \dfrac{a_i}{p_i} \right \rfloor \right)$ 最小为 $b$，则线段树上第 $i$ 位是 $b$。

那如何构建出这样的线段树？

可以先拆开计算数列 $a$ 中每一个数的贡献。

对于第 $i$ 个数，如果 $\left \lfloor \dfrac{a_i}{j+1} \right \rfloor < k \le \left \lfloor \dfrac{a_i}{j} \right \rfloor$，那么如果 $\min\limits_{1 \le i \le n}\left(\left \lfloor \dfrac{a_i}{p_i} \right \rfloor \right)$ 为 $k$，则 $\max\limits_{1 \le i \le n}\left(\left \lfloor \dfrac{a_i}{p_i} \right \rfloor \right)$ 至少是 $\left \lfloor \dfrac{a_i}{j} \right \rfloor$。

于是，我们可以在线段树上对每一个 $(\left \lfloor \dfrac{a_i}{j+1} \right \rfloor , \left \lfloor \dfrac{a_i}{j} \right \rfloor]$ 做一次权值为  $\left \lfloor \dfrac{a_i}{j} \right \rfloor$ 的取 $\max$ 操作。

由于对于 $1 \le b \le a$，$\dfrac{a}{b}$ 最多只有 $2 \sqrt{a}$ 种取值，那么这个方法时间复杂度为 $\mathcal O(N\sqrt{a_N}\log{a_N})$。

[TLE code for D2](https://www.luogu.com.cn/paste/6t2534fi)

非常遗憾的是，这份代码无法通过。

于是我使用了 $2$ 个常数优化 ：

1.  对于右端点小于 $1000$ 的修改，直接使用暴力修改。根据数论分块的性质，这样可以省掉一半的修改。

2.  使用 `pragma` 优化：

```
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
```

[AC code for D2](https://www.luogu.com.cn/paste/k6coxg8h)

时间复杂度 $\mathcal O(N\sqrt{a_N}\log{a_N})$。

---

## 作者：sinestrea (赞：0)

我们先让 $p_i$ 全都为 $k$，就求出了最小的最大值和最小的最小值。

然后都放到优先队列里，每次更新最大值最小值，做差，然后比较原来的 $ans$ 就可以了。

根据根号分治，我们可以得出一个数被整除后的结果最多有 $2 \sqrt n$ 种，用优先队列维护，时间复杂度 $n \log{n} \sqrt n$。

```cpp
//url:https://www.luogu.com.cn/problem/CF1706D2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#define pd __gnu_pbds

class Node final {
public:
    int w{}, id{};
    bool operator<(const Node &cur) const {return cur.w < w;}
};

const int MAX = 100005;

int t{}, n{}, k{}, a[MAX]{}, p[MAX]{}, w[MAX]{};
int max{}, min{}, ans{};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> t;
    while (t--) {
        std::cin >> n >> k;
        min = INT_MAX, max = INT_MIN;
        pd::priority_queue<Node> save{};
        for (int i = 1; i <= n; i++) {
            std::cin >> a[i];
            p[i] = k, w[i] = a[i] / k;
            save.push(Node{w[i], i});
            max = std::max(max, w[i]);
            min = std::min(min, w[i]);
        }
        ans = max - min;
        while (1) {
            int x = save.top().id, y = save.top().w;
            save.pop();
            ans = std::min(ans, max - y);
            if (ans == 0 || p[x] == 1) break;
            p[x] = a[x] / (w[x] + 1);
            w[x] = a[x] / p[x];
            save.push(Node{w[x], x});
            max = std::max(max, w[x]);
        }
        std::cout << ans << '\n';
    }
}
```

---

## 作者：5ab_juruo (赞：0)

赛时脑子一糊涂，没想到一个根号或一个 $\log$ 的做法，小修改一下 D1 的暴力就过了/kx。

---

D1 的做法是直接枚举，考虑优化这个枚举。

把所有的取值塞到一个堆里面，一开始 $p_i\leftarrow 1$，每次将取值的最大值改小并更新答案即可。

一个显然的性质是 $\left\lfloor\dfrac{a_i}{p_i}\right\rfloor$ 只有 $\mathcal{O}(\sqrt a_i)$ 种取值（以 $\sqrt a_i$ 为界分类即证）。所以每个数 $a_i$ 只会被操作 $\mathcal{O}(\sqrt a_i)$ 次。再乘上堆的复杂度，整体是 $\mathcal{O}(n\log n\sqrt{\max a_i})$。

常数很小，用 64 位交 3600ms 卡过去了/kx。

```cpp
/* name: 1706D
 * author: 5ab
 * created at: 22-07-18 23:02
 */
#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;
const int max_n = 100000;

struct nd
{
	int id, vl;
	nd(int _i = 0, int _v = 0) : id(_i), vl(_v) { }
	bool operator<(const nd& n) const
	{
		return vl < n.vl;
	}
};
priority_queue<nd> pq;
int a[max_n];

inline void chmin(int& a, int b) { if (a > b) a = b; }
signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int cas, n, m, ans, nn, id, mn;
	bool rc;
	
	cin >> cas;
	while (cas--)
	{
		cin >> n >> m, mn = 1145141919;
		for (int i = 0; i < n; i++)
		{
			cin >> a[i];
			pq.emplace(i, a[i]);
			chmin(mn, a[i]);
		}
		
		ans = 1145141919;
		while (!pq.empty())
		{
			auto p = pq.top();
			chmin(ans, p.vl - mn);
			if (!p.vl)
				break;
			nn = p.vl, id = p.id;
			if (a[id] / nn + 1 > m)
				break;
			nn = a[id] / (a[id] / nn + 1);
			pq.pop();
			pq.emplace(id, nn);
			chmin(mn, nn);
		}
		while (!pq.empty())
			pq.pop();
		cout << ans << "\n";
	}
	
	return 0;
}

```

---

## 作者：2018ljw (赞：0)

题目大意：给定一个长为 $n$ 的序列 $a$，构造等长序列 $p$ 满足：
1. $1\le p_i\le k$。
2. 最小化 $\lfloor\frac{a_i}{p_i}\rfloor$ 的极差。
求这个最小的极差。

$n,a_i,k\le 10^5$。

------------

首先去重排序是显然的，因为给相同的 $a$ 分配相同的 $p$ 一定是最优的。

考虑一个事情：$\lfloor\frac{x}{i}\rfloor$ 的取值个数为 $\sqrt x$ 级别。证明：$0\le i\le \sqrt x$ 时，每个 $\lfloor\frac{x}{i}\rfloor$ 互不相同；$\sqrt x\le i\le x$ 时，$\lfloor\frac{x}{i}\rfloor$ 分布在 $[1,\sqrt x]$ 之间。$i>x$ 时，$\lfloor\frac{x}{i}\rfloor=0$。

所以取值最多 $2\sqrt x+1$ 个。

不妨我们钦定 $\lfloor\frac{a_1}{p_1}\rfloor$ 的取值 $w$，然后考虑接下来会发生什么：

对于 $a_{2\dots n}$，其有效的取值有且仅有第一个 $\ge w$ 与第一个 $\le w$ 的数。因为如果我们选择了更大或更小的值 $val$，$|val-x|$ 更新最大值一定更劣。

所以我们对于 $a_{2\dots n}$，求出其可行取值中，第一个 $\ge w$ 与第一个 $\le w$ 的值。需要注意的是，由于 $k$ 的约束，后者可能不存在，这时我们认为其值为 $-\inf$。现在假设我们已经得到了一堆 $(l_i,r_i)$，考虑更新答案。

不妨钦定最小的 $l_i$，那么显然不小于其的均使用 $l_i$，大于其的均使用 $r_i$。因此答案大概长这样：$\min\limits_{i=2}^n\{\max\limits_{l_j<l_i}\{w-l_i,r_j-w\}\}$。

发现其性质不是很优秀。考虑从小到大枚举 $l_i$，那么我们每次扩大 $l$ 时一定会多出一堆必须用 $r$ 的，用这些更新 $\max\{r_i-w\}$ 即可。

最后考虑如何根据 $w,a_i,k$ 求出 $(l_i,r_i)$。

首先，$k$ 的影响有且仅有可能让 $r_i$ 变大、$l_i$ 无解。所以暂时不考虑 $k$。对于无解的情况，为了防止更新答案，赋成负无穷即可。

1. $a_i$ 可以通过某个数除出来 $w$，那么最大的 $p_i$ 就是 $\lfloor\frac{a_i}{\lfloor\frac{a_i}{w}\rfloor}\rfloor$。进一步的，我们让商数 $+1$，就可以得到最小的 $p_i=\lfloor\frac{a_i}{\lfloor\frac{a_i}{w}+1\rfloor}\rfloor+1$。那么如果这个 $p_i\le k$，我们可以直接凑出 $w$，即 $l_i=r_i=w$。否则，我们的 $l_i$ 无解，$r_i=\lfloor\frac{a_i}{k}\rfloor$。
2. $a_i$ 无法直接整除得到。此时右端点的计算方式没有实质性的改变。求出右端点需要的 $p_i$ 后我们可以使用与上一类相同的方式求出左端点。依旧单独判断 $>k$ 的情况即可。

由于答案不会超过 $a_n$，所以负无穷设为 $-a_n$ 即可。

此外，$w=0$ 的时候除法会出问题，但不难发现此时不需要考虑 $l_i$，因此答案即为最大的 $r_i=\lfloor\frac {a_n}k\rfloor$。

总复杂度 $O(n\sqrt n+\sqrt n\log n)$
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[100001],k;
int pb[100001][2],qz[100001],m;
struct itm{
	int a,b;
}w[100001];
bool operator<(itm x,itm y){
	return x.a<y.a;
}
int main(){
	int i,j,t;
	scanf("%d",&t);
	while(t--){
		m=0;
		int ans=167772161;
		scanf("%d%d",&n,&k);
		for(i=1;i<=n;i++)scanf("%d",&a[i]);
		n=unique(a+1,a+n+1)-a-1;
		for(i=1;i<=k&&i<=a[1];i++)qz[++m]=a[1]/i;
		sort(qz+1,qz+m+1);
		m=unique(qz+1,qz+m+1)-qz-1;
		if(k>a[1])ans=a[n]/k;
		//取值可能为 0 的情况
		for(i=1;i<=m;i++){
			if(!ans)break;
			//剪枝，ans=0 一定是最小的，没必要再试图更新
			for(j=2;j<=n;j++){
				if(a[j]/(a[j]/qz[i])==qz[i]){
					if(a[j]/(qz[i]+1)+1<=k)pb[j][0]=pb[j][1]=qz[i];
					else pb[j][1]=a[j]/k,pb[j][0]=-a[n];
					continue;
				}
				if(a[j]/(qz[i]+1)+1>k){
					int tst=a[j]/k;
					pb[j][0]=-a[n];pb[j][1]=tst;
				}
				else{
					int mrv=a[j]/(a[j]/qz[i]),mrl=a[j]/(a[j]/mrv+1);
					pb[j][0]=mrl;pb[j][1]=mrv;
				}
				//两种情况分类讨论，赛时时间不够代码逻辑可能有些混乱。
				//pb[i][0/1] 即为题解中 l[i] 与 r[i]
			}
			int cnt=0;
			for(j=2;j<=n;j++)w[++cnt].a=pb[j][0],w[cnt].b=pb[j][1];
			sort(w+1,w+cnt+1);
			//按 l[i] 排序。
			int lp=0,maxr=qz[i];
			for(j=1;j<=cnt;j++){
				if(j==cnt||w[j].a!=w[j+1].a){
					ans=min(ans,maxr-w[j].a);
					while(lp!=j){
						lp++;
						maxr=max(maxr,w[lp].b);
					}
				}
			}
			ans=min(ans,maxr-qz[i]);
			//全选右端点的情况。
		}
		printf("%d\n",ans);
	}
}

```

---

