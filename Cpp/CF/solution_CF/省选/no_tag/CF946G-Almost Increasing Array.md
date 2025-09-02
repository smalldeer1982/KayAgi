# Almost Increasing Array

## 题目描述

We call an array almost increasing if we can erase not more than one element from it so that the array becomes strictly increasing (that is, every element is striclty greater than every element before it).

You are given an array $ a $ consisting of $ n $ elements. You are allowed to replace any element with any integer number (and you may do so any number of times you need). What is the minimum number of replacements you have to perform in order to make the array almost increasing?

## 样例 #1

### 输入

```
5
5 4 3 2 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2 8 9 5
```

### 输出

```
0
```

# 题解

## 作者：xtx1092515503 (赞：5)

先为自己的[DPblog](https://www.luogu.com.cn/blog/Troverld/dp-shua-ti-bi-ji)打个广告~~

不知道大家有没有做过[这道题](https://www.luogu.com.cn/problem/P2501)啊。

在链接的那题中，有个小trick：如果要把一个序列修改成单调上升的序列，设原本的序列为$a_i$，我们算出序列$b$，且$b_i=a_i-i$。则所有不用修改的位置，就是序列$b$中最长不降子序列的位置。

证明：

当$a_i$可以放在$a_j$前面时，必有$a_i-a_j\leq i-j$，

则有$a_i-i\leq a_j-j$，

即$b_i\leq b_j$。

现在这题允许我们删除一个位置，那么我们可以找出$b_i$的前缀不降子序列长度$f_i$以及后缀不降子序列长度$g_i$。

则如果一段$f_i$和一段$g_j$可以通过删掉一个位置拼在一起，必有

$b_i\leq b_j+1$，因为中间删掉了一个位置。并且，必须有$i<j-1$，因为中间必须有位置可删。

则我们在拼接时，就可以用树状数组储存前缀的$f_i$的最大值，并与$g_j$拼接即可。

复杂度$O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200100],f[200100],g[200100],t[200100],res;
vector<int>v;
void add(int x,int y){
	while(x<=m)t[x]=max(t[x],y),x+=x&-x;
}
int sum(int x){
	int s=0;
	x=min(x,m);
	while(x)s=max(s,t[x]),x-=x&-x;
	return s;
}
int main(){
//	freopen("!dp!.in","r",stdin);
//	freopen("!dp_std_cpp.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]-=i,v.push_back(a[i]);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin()),m=v.size();
	for(int i=1;i<=n;i++)a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
	memset(t,0,sizeof(t));
	for(int i=1;i<=n;i++)f[i]=sum(a[i])+1,add(a[i],f[i]),res=max(res,f[i]+1);
	memset(t,0,sizeof(t));
	for(int i=n;i>=1;i--)g[i]=sum(m-a[i]+1)+1,add(m-a[i]+1,g[i]),res=max(res,g[i]+1);
//	for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");
//	for(int i=1;i<=n;i++)printf("%d ",f[i]);puts("");
//	for(int i=1;i<=n;i++)printf("%d ",g[i]);puts("");
	memset(t,0,sizeof(t));
	for(int i=2;i<=n;i++){
		int tmp=upper_bound(v.begin(),v.end(),v[a[i]-1]+1)-v.begin();
//		printf("%d\n",tmp);
		res=max(res,sum(tmp)+g[i]+1);
		if(a[i-1]<=a[i])res=max(res,f[i-1]+g[i]);
		add(a[i-1],f[i-1]);
	}
	res=min(res,n);
	printf("%d\n",n-res);
	return 0;
}
/*
10
757147 167851000 301413356 336971124 659598368 160567225 391749387 4890851 35766290 26239572 
*/
```


---

## 作者：小周猪猪 (赞：4)

## $\mathrm{Problem}$
We call an array almost increasing if we can erase not more than one element from it so that the array becomes strictly increasing (that is, every element is striclty greater than every element before it).

You are given an array $a$ consisting of $n$ elements. You are allowed to replace any element with any integer number (and you may do so any number of times you need). What is the minimum number of replacements you have to perform in order to make the array almost increasing?

---

## $\mathrm{Translation}$
定义一个序列$A$是$Almost\;Increasing$的，当$A$满足从$A$中去掉一个位置之后剩下的序列形成了一个严格递增序列。

给出一个长度为$n$的序列，问最小需要改动多少个位置的值，使得这个序列变成$Almost\;Increasing$的。


---

## $\mathrm{Solution}$
解决这道题我要知道一个结论：
- 一串序列$\{a_i\}$要单调递增需要改变的数值个数，那么我们所求的代价相当于**序列$\{a_i-i\}$中最长不下降子序列**的长度。

证明：
考虑元素 $a_i$ 和 $a_j$ 能够共存的条件。
显然 $a_i$ 和 $a_j$ 是单调递增的两个元素，且单调递增序列中相邻两个元素之间增量至少为$1$.
因此我们就有：$a_i-a_j\ge i-j(i>j)$，则移项可以得到$a_i-i\ge a_j-j$.

所以，我们的问题就转化为了序列$\{a_i-i\}$去掉一个数以后的最长不下降子序列。

我们设$f[i][0/1]$表示前i个数字中，还没有删除数字/已经删除数字的最长不下降子序列。

那么十分显然的就有：$$f[i][0]=\max\{f[j][0]\}+1(a_j-j\le a_i-i)$$
$$f[i][1]=\max\{f[j][1]\}+1(a_j-j\le a_i-i)$$
这两步和经典的最长不下降子序列相同。

对于去掉一个元素的情况，我们发现后面的所有点下标都会减去1，因此：
$$f[i][1]=\max\{f[j][0]\}+1(a_j-j\le a_i-i+1,j<i-1)$$
对于值域的限制，我们用树状数组维护即可。

---
## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 6e5;

int n, m(0), cnt(0);
int a[N], b[N], c[N], f[N][2];
map < int, int > tag;

int read(void)
{
	int s = 0, w = 0; char c = getchar();
	while (c < '0' || c > '9') w |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') s = s*10+c-48, c = getchar();
	return w ? -s : s;
}

void input(void)
{
	n = read();
	for (int i=1;i<=n;++i) {
		a[i] = read() - i;
		b[i] = a[i] + 1;
		c[++ m] = a[i], c[++ m] = b[i]; 
	}	
	sort(c + 1, c + m + 1);
	for (int i=1;i<=m;++i)
	{
		if (c[i] != c[i-1]) tag[c[i]] = ++ cnt;
		else if (i == 1) tag[c[i]] = ++ cnt;
	}
	for (int i=1;i<=m;++i) {
		a[i] = tag[a[i]];
		b[i] = tag[b[i]];
	}
	//for (int i=1;i<=n;++i) cout<<a[i]<<' ';cout<<endl;
	//for (int i=1;i<=n;++i) cout<<b[i]<<' ';cout<<endl;
}

struct BIT
{
	#define lowbit(i) (i & -i)
	int S[N * 10] = {};
	void add(int x, int v) {
		for (int i=x;i<=cnt;i+=lowbit(i))
			S[i] = max(S[i], v);
		return;
	}
	int ask(int x) {
		int res = 0;
		for (int i=x;i>=1;i-=lowbit(i))
			res = max(res, S[i]);
		return res;
	}
}  tree1, tree2, tree3;

void work(void)
{
	int res = 0;
	for (int i=1;i<=n;++i)
	{
		int val1 = tree1.ask(a[i]);
		int val2 = tree2.ask(a[i]);
		int val3 = tree3.ask(b[i]);
		f[i][0] = val1 + 1;
		if (val2 > 0) f[i][1] = val2 + 1;
		if (i > 2) f[i][1] = max(f[i][1], val3 + 1);
		tree1.add(a[i], f[i][0]);
		tree2.add(a[i], f[i][1]);
		if (i > 1) tree3.add(a[i-1], f[i-1][0]);
		res = max(res, max(f[i][0], f[i][1]));
	}
	cout << max(n - 1 - res, 0) << endl;
	return;
}

int main(void)
{
	input();
	work();
	return 0;
} 
```


---

## 作者：Skeleton_Huo (赞：3)

感觉题解区对问题转化的描述有点不完善，我来补充一下。

#### 弱化问题
先不考虑删除一个数。即一个序列需要修改多少次才能变得严格单调递增。

这需要用到一个结论：在一种修改方案中，如果一个子序列未被修改，则其相邻两项 $a_i,a_j (i > j)$，一定满足 $a_i - a_j \ge i - j$，即 $a_i - i \ge a_j - j$。同时，若我们规定了原序列 $\{a_i\}$ 中的满足该条件的最长子序列，不被修改，则其他位置，一定被修改（否则可以推出矛盾）。

因此问题转化为了求 $\{a_i - i\}$ 的最长不降子序列，答案为 $n - \max\{f[i]\}$，其中 $f[i]$ 为以 $i$ 为结尾的最长不降子序列。

#### 原问题
现在考虑删除一个数。有两种做法，第一种是枚举删除点，将两部分拼在一起。第二种是重新设计状态。这里用第二种。

首先想一想在有了删除点后原来选择子序列的规则是否有改变。如果子序列相邻两个元素间没有删除，规则仍然是 $a_i - i \ge a_j - j$。但要是有删除，则考虑到区间长度会减 1，应改为 $a_i - a_j \ge i - j - 1, i - j > 1$，即 $a_i - i + 1 \ge a_j - j, i - 1 > j$。

状态定义：$f[i,0/1]$ 表示以第 $i$ 个元素结尾，且前 $i$ 个元素中没有/有被删除的数时，满足上述条件的最长子序列（即最长可保留子序列）。

$$
\begin{aligned}
& f[i,0] = \max_{j<i,a_j-j\le a_i-i}\{f[j,0]+1\} \\
& f[i,1] = \max
\begin{cases}
\max_{j<i,a_j-j\le a_i-i}\{f[j,1]+1\} \\
\max_{j<i-1,a_j-j\le a_i-i+1}\{f[j,0]+1\} \\
\end{cases}
\end{aligned}
$$

求解这个可以用树状数组优化，就不多说了。

最后的答案就是 $n - 1 - res$，其中 $res$ 表示
$$
\max
\begin{cases}
\max_{1\le i<n}\{f[i,0]\} \\
\max_{1<i\le n}\{f[i,1]\} \\
\end{cases}
$$

写代码有个陷阱：如果原来两个数相差 1，离散化后仍然相差 1，但如果离散化后相差 1，并不能得到离散化前相差几。

为了处理第三个 $\max$ 式，我们可以将 $a_i - i + 1$ 也一起离散化，这样，所有有用数的集合就掌握在我们手中了。

#### Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, a[N], b[N], c[N];
int lsh[N << 2], len;
int f[N][2];

int getid(int x) { return lower_bound(lsh + 1, lsh + len + 1, x) - lsh; }

struct BIT {
  int c[N << 2];
  // 这里别写成 p <= n 
  void update(int p, int x) { for (; p <= len; p += p & -p) c[p] = max(c[p], x); }
  int query(int p) {
    int res = 0;
    for (; p; p -= p & -p) res = max(res, c[p]);
    return res;
  }
} bit[3];

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); 
  
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    lsh[++len] = a[i] - i;
    lsh[++len] = a[i] - i + 1;
  }
  
  sort(lsh + 1, lsh + len + 1);
  len = unique(lsh + 1, lsh + len + 1) - lsh - 1;
  for (int i = 1; i <= n; i++) b[i] = getid(a[i] - i), c[i] = getid(a[i] - i + 1);
  // 注意树状数组的目的是求前缀max，是可以离散化的 
  
  for (int i = 1; i <= n; i++) {
    if (i > 1) bit[0].update(b[i - 1], f[i - 1][0]);
    if (i > 1) bit[1].update(b[i - 1], f[i - 1][1]);
    if (i > 2) bit[2].update(b[i - 2], f[i - 2][0]);
    f[i][0] = 1 + bit[0].query(b[i]);
    if (i > 1) f[i][1] = 1 + max(bit[1].query(b[i]), bit[2].query(c[i]));
  }
  
  int res = 0;
  for (int i = 1; i < n; i++) res = max(res, f[i][0]);
  for (int i = 2; i <= n; i++) res = max(res, f[i][1]);
  
  cout << n - 1 - res << "\n";
  
  return 0;
}
```

---

## 作者：chenxia25 (赞：3)

whkzb 了，先做个题快乐一下（

没错这就是我 NOIP 前夜开的最后一道题目。当时我看错题了，以为是要删掉元素，WA 了之后才发现是修改。然后发现需要分析分析就弃了。今天来补一个。

我们考虑最终改成的那个序列，删掉其中一个成为的严格递增序列，中的没被修改的序列。考虑对这个序列 DP，$dp0_i$ 表示考虑到第 $i$ 位，前 $i$ 位都不能被删除，第 $i$ 没被修改且不被删除时候的最多不被修改的元素数量，$dp1_i$ 则表示前 $i$ 位必须有一个被删除。

那么转移就是 $dp0_i$ 可以转移到 $j$ 当且仅当 $a_j\leq a_i-i+j$ 即 $a_j-j\leq a_i-i$。$dp1_i$ 可以转移到 $dp0$ 和 $dp1$，后者的条件跟上面一样，前者因为在这一段里面删除了一个，所以 $\leq$ 右边要 $+1$，但是因为删除的那个不算被修改了，所以 $\max$ 里面的式子里要 $+2$。然后把涉及到的式子的值都离散化，维护三个 BIT 即可。

为了方便，我们假设 $a_{n+1}=+\infty$ 然后它必须不变且选。最后答案就用 $n+1$ 减一下即可。

---

## 作者：Nightingale_OI (赞：1)

## Almost Increasing Array

### 大意

给定一个序列 $a_n$，问至少**修改**多少元素使得其**删除**一个元素后严格递增。

### 思路

令 $a_0=-\infty,a_{n+1}=+\infty$。

若不考虑删除操作，则设 $dp_i$ 表示**不修改** $a_i$，至少要修改多少元素使得前 $i$ 个数严格递增。

$$dp_i=\max_{j<i,i-j\leq a_i-a_j}dp_j+i-j-1=i+\max_{j<i,a_j-j\leq a_i-i}dp_j-j-1$$

将 $a_i-i$ 离散化后树状数组维护即可。

---

那么记 $f_{i,t}$ 表示**不修改（也不删去）** $a_i$，至少要修改多少元素使得前 $i$ 个数删去 $t$ 个数严格递增，正常转移：

$$f_{i,t}=i+\max_{j<i,a_j-j\leq a_i-i}f_{j,t}-j-1$$

由于可以删一个数，所以特殊转移的条件是 $i-j<=a_i-a_j+1$：

$$f_{i,1}=i-1+\max_{j<i-1,a_j-j\leq a_i-i+1}f_{j,0}-j-1$$

同时离散化 ${a_i-i,a_i-i+1}$，树状数组维护即可。


### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
const int N=404040,inf=1e18;
int a[N],b[N],c[2][N],f[N][2];
inline void add(int*c,int x,int y){x=lower_bound(b+1,b+m+1,x)-b;for(int i=x;i<=m;i+=-i&i)c[i]=min(c[i],y);}
inline int sum(int*c,int x,int y=-1){x=lower_bound(b+1,b+m+1,x)-b;for(int i=x;i;i-=-i&i)y=min(y,c[i]);return y;}
signed main(){
	cin>>n;
	f(i,1,n)scanf("%lld",&a[i]);a[++n]=inf;
	f(i,1,n)b[++m]=a[i]-i,b[++m]=a[i]-i+1;
	sort(b+1,b+m+1);
	f(i,1,m)f(t,0,1)c[0][i]=f[i][0]=f[i][1]=inf;
	f(i,1,n){
		if(i<n)f[i+1][1]=i+sum(c[0],a[i+1]-i);
		f(t,0,1){
			f[i][t]=min(f[i][t],i+sum(c[t],a[i]-i));
			add(c[t],a[i]-i,f[i][t]-i-1);
		}
	}
	printf("%lld\n",f[n][1]);
	return 0;
} 
```

---

## 作者：wrzSama (赞：1)

## 题目大意

给定一个长度为 $n$ 的整数序列 $a$，若序列 $a$ 是 Almost Increasing 的，则满足该序列去掉一个数后是严格递增的。每次操作我们可以将一个位置上的数改成任意整数，问将序列 $a$ 改成 Almost Increasing 的最小操作次数。

## 思路

我们知道最小的操作次数就是序列的长度减去不需要改变的值的数量，那么我们可以尝试 $dp$ 找到最多有多少个值不需要改变。$dp_i$ 表示前 $i$ 个数以第 $i$ 个数为结尾的不需要改变的值的最大数量，那么 $dp_i$ 可以从 $dp_j$ 转移当且仅当 $a_i-a_j \geq i-j$ （因为最后形成的序列是严格递增的，所以 $a_i$ 和 $a_j$ 之间一定至少要留下 $i-j$ 个整数的位置）。将 $a_i-a_j \geq i-j$ 移项，得到 $a_i-i \geq a_j-j$。令每个位置上的 $a_i$ 减去 $i$，问题就转化成了在序列中找最长的不下降子序列。那么此时 $dp_i$ 就可以从所有的满足 $a_j \le a_i$ 且 $j<i$ 的 $dp_j$ 转移，$dp_i=max(dp_j)+1$。我们可以对所有 $a_i$ 的值域开一颗线段树，维护每一段值域中最大的 $dp$ 的值，$dp_i$ 就等于值域 $(-\infty,a_i]$ 中最大的 $dp$ 值加 $1$。接下来我们考虑删掉一个数对答案的影响，将 $dp$ 加 $1$ 维表示是否已经删除了一个数，$dp_{i,k}$ 中若 $k$ 为 $0$ 就表示还没有删除一个数，若 $k$ 为 $1$ 就表示已经删除了一个数。我们对于 $k$ 为 $0$ 和 $1$ 时分别开一颗线段树来维护转移。若 $k$ 的值不发生改变，那么转移就和之前没加这一维一样；若 $k$ 在转移时由 $0$ 变成了 $1$，即让 $dp_{i,1}=dp_{j,0}+1$，则需要满足 $a_i+1 \geq a_j$ 且 $j<i-1$ 。因为删去 $[j+1,i-1]$ 中的一个数会使 $i$ 及其之后的下标减 $1$，$a$ 的值就加了 $1$。最后输出 $n$ 减去最大的 $dp_{i,0}$ 和 $n$ 减去最大的 $dp_{i,1}$ 再减 $1$ 中较小的就是答案。如果给出的序列本身就严格递增，最后的答案会小于 $0$（减去了 $1$ 个不存在的数）,将答案和 $0$ 取较大值即可。

## 代码

```cpp
#include<bits/stdc++.h>
#pragma GCC O(2)
#pragma GCC O(3)
#pragma O(fast)
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
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
struct segment_tree
{
	int ls,rs,val;
}tr1[4000005],tr2[4000005];
int n,a[200005],dp[200005][2],tot1=1,tot2=1,ans;
int update1(int o,int l,int r,int x,int k)
{
	if(!o) o=++tot1;
	if(l==r)
	{
		tr1[o].val=k;
		return o;
	}
	int mid=(l+r)>>1;
	if(x<=mid) tr1[o].ls=update1(tr1[o].ls,l,mid,x,k);
	else tr1[o].rs=update1(tr1[o].rs,mid+1,r,x,k);
	tr1[o].val=max(tr1[tr1[o].ls].val,tr1[tr1[o].rs].val);
	return o;
}
int query1(int o,int l,int r,int x)
{
	if(!o) return 0;
	if(r<=x) return tr1[o].val;
	int mid=(l+r)>>1,res=query1(tr1[o].ls,l,mid,x);
	if(x>mid) res=max(res,query1(tr1[o].rs,mid+1,r,x));
	return res;
}
int update2(int o,int l,int r,int x,int k)
{
	if(!o) o=++tot2;
	if(l==r)
	{
		tr2[o].val=k;
		return o;
	}
	int mid=(l+r)>>1;
	if(x<=mid) tr2[o].ls=update2(tr2[o].ls,l,mid,x,k);
	else tr2[o].rs=update2(tr2[o].rs,mid+1,r,x,k);
	tr2[o].val=max(tr2[tr2[o].ls].val,tr2[tr2[o].rs].val);
	return o;
}
int query2(int o,int l,int r,int x)
{
	if(!o) return 0;
	if(r<=x) return tr2[o].val;
	int mid=(l+r)>>1,res=query2(tr2[o].ls,l,mid,x);
	if(x>mid) res=max(res,query2(tr2[o].rs,mid+1,r,x));
	return res;
}
int main()
{
	n=read();
	int l=2e9,r=-2e9;
	for(int i=1;i<=n;++i)
	{
		a[i]=read()-i;
		l=min(l,a[i]);
		r=max(r,a[i]);
	}
	for(int i=1;i<=n;++i)
	{
		dp[i][1]=max(query1(1,l,r,min(r,a[i]+1)),query2(1,l,r,a[i]))+1;
		if(i>1) update1(1,l,r,a[i-1],dp[i-1][0]);
		dp[i][0]=query1(1,l,r,a[i])+1;
		update2(1,l,r,a[i],dp[i][1]);
		ans=max(ans,max(dp[i][0],dp[i][1]));
	}
	write(max(0,n-ans-1));
	return 0;
}
```


---

## 作者：FelFa_1414666 (赞：1)

[codeforces 传送门](https://codeforces.com/contest/946/problem/G) & [洛谷传送门](https://www.luogu.com.cn/problem/CF946G)

---

## Description

有一个长度为 $n$ 的整数序列，每次操作可以把一个元素修改为任意整数。求最少要几次操作，使得序列能满足：删除一个元素后是严格单调增的。

- $2\le n\le 2\times 10^5$
- $1\le a_i\le 10^9$

---

## Solution

要求最小修改次数，我们不妨考虑求最大保留元素个数。

这样其实类似于求最长上升子序列，但是因为要求严格单增且必须是整数，所以又不能直接套用最长上升子序列。

先考虑直接构造严格单增序列，我们思考什么情况下两个元素可以同时保留。

假设两个元素下标分别为 $j$ 和 $i$，$j<i$。那么它们中间会有 $i-j-1$ 个严格单增的整数，所以要满足：

$$\forall i,j\quad a_i-a_j\ge i-j$$

$$a_i-i\ge a_j-j$$

所以对于一个元素，我们定义它的权值为 $a_i-i$。可以用类似最长上升子序列的方式用线段树优化 dp 求解。

> $dp_i$ 表示结尾权值为 $i$ 的最长保留元素个数

$$dp_i=\min\limits_{j\le i}(dp_j)+1$$

然后考虑删除一个元素的情况，我们发现删除的元素右边的元素相当于下标统一减一。设删除元素下标为 $k$，元素$j<k,i>k$ 那么 $i$ 和 $j$ 可以同时保留的充要条件变为:

$$a_i-i+1\ge a_j-j$$

所以可以看作删除位置左边的元素以 $a_i-i$ 为权值，右边元素以 $a_i-i+1$ 为权值。

然后可以先以 $a_i-i+1$ 倒序求一遍 dp 记录答案，然后再正序以 $a_i-i$ 求一遍，同时记录左右两边拼接的最大答案。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define mp make_pair
#define F first
#define S second
using namespace std;
const int INF=1e9+7;
int n,a1[200005],a2[200005],dp[800005],sufmx[200005],sz,ans;
void modify(int l,int x)//线段树单点修改
{
	l+=sz;
	dp[l]=x;
	while(l>1)
	{
		l>>=1;
		dp[l]=max(dp[l<<1],dp[l<<1|1]);
	}
}
int query(int l,int r)//线段树区间查询
{
	int res=-INF;
	for(l+=sz,r+=sz;l<r;l>>=1,r>>=1)
	{
		if (l&1) res=max(res,dp[l++]);
		if (r&1) res=max(res,dp[--r]);
	}
	return res;
}
int main()
{
	ios::sync_with_stdio(false),cin.tie(nullptr);
	vector<int> b;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a1[i];
		b.pb(a1[i]-i),b.pb(a1[i]-i+1);
	}
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());//将所有权值离散化排序
	sz=b.size();
	for(int i=0;i<n;i++)
	{//两种权值
		a2[i]=lower_bound(b.begin(),b.end(),a1[i]-i+1)-b.begin();
		a1[i]=lower_bound(b.begin(),b.end(),a1[i]-i)-b.begin();
	}
	memset(dp,0,sizeof(dp));
	for(int i=n-1;i>=0;i--)//后缀求一遍
	{
		modify(a2[i],query(a2[i],sz)+1);
		if (i>0)
			sufmx[i]=query(a1[i-2],sz);//记录右半边最大答案
	}
	ans=sufmx[1]+1;//删除0号元素的情况
	memset(dp,0,sizeof(dp));
	for(int i=0;i<n-1;i++)//前缀求一边
	{
		modify(a1[i],query(0,a1[i]+1)+1);
		ans=max(ans,query(0,a1[i]+1)+sufmx[i+2]+1);//左右拼接
	}
	cout<<n-ans<<endl;
	return 0;
}
```

- 时间复杂度：$\operatorname O(n\log n)$

- 空间复杂度：$\operatorname O(n)$

希望题解对你有帮助！

---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF946G)

# 前置知识

[最长不下降子序列](https://oi-wiki.org//dp/basic/#%E6%9C%80%E9%95%BF%E4%B8%8D%E4%B8%8B%E9%99%8D%E5%AD%90%E5%BA%8F%E5%88%97) | [权值树状数组及应用](https://oi-wiki.org//ds/fenwick/#%E6%9D%83%E5%80%BC%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84%E5%8F%8A%E5%BA%94%E7%94%A8)

# 解法

若将 $\{ a \}$ 变成严格递增序列，至少需要更改 $n$ 减去 $\{ a_{i}-i \}$ 的最长不下降子序列长度个数。
  - 证明
    - 对于 $a_{i},a_{j}(i<j)$ 若都在最终的严格递增序列里，则有 $a_{i}-a_{j} \le i-j$，即 $a_{i}-i \le a_{j}-j$。而这 $\{ a_{i}-i \}$ 的最长不下降子序列长度个数是不需要更改的。
     
考虑计算最多能保留的数的个数。

令 $\forall i \in [1,n],b_{i}=a_{i}-i$。

设 $f_{i,0/1}$ 表示以 $i$ 结尾的前缀中没有/有删除过的数时（删除的这个数仅能 $\in [1,i-1]$，能够在最终保留但不参与运算）最多能保留的数的个数，状态转移方程为 $\begin{cases} f_{i,0}=\max\limits_{j=1}^{i-1} \{ [b_{j} \le b_{i}] \times (f_{j,0}+1) \} \\ f_{i,1}=\max(\max\limits_{j=1}^{i-1} \{ [b_{j} \le b_{i}] \times (f_{j,1}+1) \},\max\limits_{j=1}^{i-2} \{ [b_{j} \le b_{i}+1] \times (f_{j,0}+1) \}) \end{cases}$，边界为 $\begin{cases} f_{1,0}=1 \\ f_{1,1}=0 \end{cases}$。

权值树状数组优化 DP 即可。

最终，有 $\max(n-1-\max\limits_{i=1}^{n} \{ f_{i,0},f_{i,1} \},0)$ 即为所求。
  - 使用删除一定比不使用删除不劣。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll a[200010],b[200010],c[400010],f[200010][2];
struct BIT
{
	ll c[400010];
	ll lowbit(ll x)
	{
		return (x&(-x));
	}
	void add(ll n,ll x,ll val)
	{
		for(ll i=x;i<=n;i+=lowbit(i))
		{
			c[i]=max(c[i],val);
		}
	}
	ll getsum(ll x)
	{
		ll ans=0;
		for(ll i=x;i>=1;i-=lowbit(i))
		{
			ans=max(ans,c[i]);
		}
		return ans;
	}
}T[3];
int main()
{
	ll n,ans=0,i;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=a[i]-i;
		c[2*i-1]=b[i];
		c[2*i]=b[i]+1;
	}
	sort(c+1,c+2*n+1);
	c[0]=unique(c+1,c+2*n+1)-(c+1);
	for(i=1;i<=n;i++)
	{
		f[i][0]=T[0].getsum(lower_bound(c+1,c+1+c[0],b[i])-c)+1;
		f[i][1]=T[1].getsum(lower_bound(c+1,c+1+c[0],b[i])-c);
		f[i][1]+=(f[i][1]!=0);
		if(i-2>=1)
		{
			f[i][1]=max(f[i][1],T[2].getsum(lower_bound(c+1,c+1+c[0],b[i]+1)-c)+1);		
		}
		T[0].add(c[0],lower_bound(c+1,c+1+c[0],b[i])-c,f[i][0]);
		T[1].add(c[0],lower_bound(c+1,c+1+c[0],b[i])-c,f[i][1]);
		if(i-1>=1)
		{
			T[2].add(c[0],lower_bound(c+1,c+1+c[0],b[i-1])-c,f[i-1][0]);
		}
	}
	for(i=1;i<=n;i++)
	{
		ans=max(ans,max(f[i][0],f[i][1]));
	}
	cout<<max(n-1-ans,0ll)<<endl;
	return 0;
}
```

---

