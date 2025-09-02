# [ARC133B] Dividing Subsequence

## 题目描述

**【题目大意】**

给定两个长度为 $n(n\le 2\times 10^5)$ 的 $1\sim n$ 的排列 $\text{P}$ 和 $\text{Q}$。

现在需要在 $\text{P}$ 和 $\text{Q}$ 中分别取出长度为 $k$ 两个子序列 $\text{A}$ 和 $\text{B}$，满足 $\forall i\in [1,k],a_i\mid b_i$。

最大化 $k$，求 $k$。

## 样例 #1

### 输入

```
4
3 1 4 2
4 2 1 3```

### 输出

```
2```

## 样例 #2

### 输入

```
5
1 2 3 4 5
5 4 3 2 1```

### 输出

```
3```

## 样例 #3

### 输入

```
10
4 3 1 10 9 2 8 6 5 7
9 6 5 4 2 3 8 10 1 7```

### 输出

```
6```

# 题解

## 作者：yukimianyan (赞：4)

## problem
长为 $n$ 的排列 $A,B$。

提取两个可以不连续的子序列 $a\subseteq A,b\subseteq B$，满足：

- $|a|=|b|.$
- $\forall i\in[1,n],a_i|b_i.$

求 $\max |a|$。$n\leq 10^5$。

## solution 1
考虑拎出所有的 $(i,j),s.t.,a_i|b_j$，因为是排列，所以是调和级数， 只有 $O(n\log n)$ 对。

那么我们要选出若干对 $(i,j)$ 使得 $i,j$ 分别单调，且不重复。

忽略重复的限制，我们可以先对着 $j$ 排序，再对 $i$ 做最长上升子序列，同时满足了两个限制。

为了避免选到相同的 $j$，对于 $(i_1,j),(i_2,j)$，我们可以将 $i$ 倒序排序，也就是使 $i_1>i_2$。由于是上升子序列，因此不会选到相同的 $j$ 了。
## code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
int n,cnt,a[200010],p[200010],c[200010<<4];
pair<int,int> b[200010<<4];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1,x;i<=n;i++) scanf("%d",&x),p[x]=i;
	for(int i=1;i<=n;i++){
		for(int j=a[i];j<=n;j+=a[i]){
			b[++cnt]={i,p[j]};
		}
	}
	sort(b+1,b+cnt+1,[](pair<int,int> a,pair<int,int> b){
		return a.second!=b.second?a.second<b.second:a.first>b.first;
	});
	int top=0;
	for(int i=1;i<=cnt;i++){
		if(!top||c[top]<b[i].first) c[++top]=b[i].first;
		else *lower_bound(c+1,c+top+1,b[i].first)=b[i].first;
	}
	printf("%d\n",top);
	return 0;
}


```
## solution 2
考虑暴力 DP。

$$f_{i,j}=\max(f_{i',j'}+1)\quad(a_i|b_j).$$

优化之。滚掉 $j$，逐个加入 $b_j$，用 $b_j$ 更新 $f$：

$$f_i=\max(f_i,1+\max_{k<i} f_{k})\quad(a_i|b_j).$$

由于满足 $a_i|b_j$ 的数量是调和级数，因此只有 $O(n\log n)$ 的枚举量。

对于 $\max_{k<i} f_{k}$，线段树维护之。总的复杂度 $O(n\log^2 n)$。

---

## 作者：mountain_climber (赞：3)

有动态规划做法，但是本蒟蒻不会，所以我就直接上 LCS 套路了。

考虑所有可能加入答案的下标 $(i,j)$，有 $ka_i = b_i$，考虑对于一个 $a_i$，在 $B$ 中有 $\lfloor \frac{n}{a_i} \rfloor$ 个能与之对应的下标，也就是说可能为答案的下标对数有 $\displaystyle \sum_{i}^{n} \lfloor \frac{n}{i} \rfloor$ 个，级别是 $O(n \log n)$ 的。

所以说我们预处理出来所有的下标对 $(i,j)$ 答案变成对于两个下标序列的 LCS 问题。

按照 LCS 问题的一般套路，我们先将下标对按照 $i$ 排序，之后对 $j$ 做 LIS。但是我们发现，如果只按照 $i$ 排序的话，$j$ 的 LIS 序列中可能含有相同的 $i$，但这是不被题意允许的，观察 LIS 的性质，我们可以对于每个 $i$，将其对应的所有 $j$ 从大到小排序，再 LIS, 因为选到了最大的一定不会往后选小的，就可以避免重复了，同时 LIS 必须是严格递增的，否则可能会选到相同的 $j$。

注意 LIS 需要用树状数组来 $O(n \log n)$ 来维护才能通过。

最终的复杂度：$n^1 = n \log n, O(n^1 \log n^1)$。

注意处理 LIS 的时候空间需要开到 $n \log n$。

CODE：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
const int N = 2e6 + 10; //其实开到1.7e6就可以
int n, a[N], b[N], box[N], dp[N], bitr[N];
vector<pii> vec;
inline bool cmp(pii p1, pii p2) // 排序i，排序j
{
    if (p1.first == p2.first) return p1.second > p2.second;
    return p1.first < p2.first;
}
//树状数组部分
int lowbit(int x)
{
    return x & -x;
}
void add(int idx, int val)
{
    while (idx < N)
    {
        bitr[idx] = max(bitr[idx], val);
        idx += lowbit(idx);
    }
}
int query(int idx)
{
    int ret = 0;
    while (idx)
    {
        ret = max(ret, bitr[idx]);
        idx -= lowbit(idx);
    }
    return ret;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &b[i]);
    // 求出所有的(i,j)放入
    for (int i = 1; i <= n; i ++ ) box[b[i]] = i;
    for (int i = 1; i <= n; i ++ )
    {
        int kk = 1;
        while (kk * a[i] <= n)
        {
            pii pr;
            pr.first = i, pr.second = box[a[i] * kk];
            vec.push_back(pr);
            kk ++ ;
        }
    }
    //排序，然后做LIS
    sort(vec.begin(), vec.end(), cmp);
    int len = vec.size();
    for (int i = 0; i < len; i ++ )
    {
        dp[i] = query(vec[i].second - 1) + 1;
        add(vec[i].second, dp[i]);
    }
    int ans = 0;
    for (int i = 0; i < len; i ++ ) ans = max(ans, dp[i]);
    printf("%d\n", ans);
    return 0;
}
```

不会树状数组求 LIS 的建议去学一下。

---

## 作者：xhhhh36 (赞：2)

[传送门](https://www.luogu.com.cn/problem/AT_arc133_b)

这题可以使用 dp 来解决。设 $dp_{i,j}$ 表示选用排列 $P$ 的前 $i$ 个数和排列 $Q$ 的前 $j$ 个数能够组成的二元组的最大组数，最终的答案是 $dp_{n,n}$ 的值。暴力转移的 dp 式子是：
$$dp_{i,j}=\max_{a_i|k,pos_k\le j} dp_{i-1,pos_k-1}+1$$
其中 $pos_k$ 表示排列 $Q$ 中 $k$ 所在的位置，然后发现 $dp_{i}$ 的转移只和 $dp_{i-1}$ 的值有关，所以可以滚动数组，便有了下面的代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N=2e5+5;
int n,p[N],q[N],dp[N],f[N],pos[N];
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>p[i];
	for (int i=1;i<=n;i++) cin>>q[i],pos[q[i]]=i;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			for (int k=p[i];k<=n;k+=p[i]){
				if (pos[k]>j) continue ;
				dp[j]=max(dp[j],f[pos[k]-1]+1);
			}
		}
		for (int i=1;i<=n;i++){
			f[i]=dp[i];
		}
	}
	cout<<dp[n]<<endl;
	return 0;
}
```
因为可以[证明](https://www.cnblogs.com/qscqesze/p/4317860.html)枚举因子是 $O(n\log n)$ 的，总时间复杂度为 $O(n^2\log n)$，考虑使用数据结构优化 $dp$ 转移的过程。可以发现上面这份代码每次用 $dp_{i-1,pos_k-1}+1$ 去更新了 $j\ge pos_k,dp_{i,j}$ 的值，也就是后缀取 $max$，单点查询。考虑使用树状数组来维护即可，要注意细节。因为转移时将滚动数组的上一个版本也储存在了树状数组中，所以每次要先询问所有的 $dp_{i-1,pos_k-1}+1$ 的值再一起更新 dp 值。
# AC code

```cpp
#include <bits/stdc++.h>

using namespace std;
const int N=2e5+5;
int n,p[N],q[N],pos[N],tp,t[N];
int lowbit(int x){
	return x&(-x);
}
void update(int x,int a){
	while (x<=n){
		t[x]=max(t[x],a);x+=lowbit(x);
	}
}
int query(int x){int ans=0;
	while (x){
		ans=max(ans,t[x]);x-=lowbit(x);
	}return ans;
}
struct ask{
	int l,mx;
}st[N];
static char buf[100000], * pa(buf), * pb(buf);
#define getchar() pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
inline int read(){
	int n=0,f=1;char c=getchar();
	while (c<'0'||c>'9'){
		if (c=='-') f=-1;c=getchar();
	}
	while (c>='0'&&c<='9'){
		n=(n<<3)+(n<<1)+(c^48);c=getchar();
	}return n*f;
}
signed main(){
	//freopen("T1.in","r",stdin);
	ios::sync_with_stdio(0);
	n=read();
	for (int i=1;i<=n;i++) p[i]=read();
	for (int i=1;i<=n;i++) q[i]=read(),pos[q[i]]=i;
	for (int i=1;i<=n;i++){tp=0;
		for (int k=p[i];k<=n;k+=p[i]){
			int z=query(pos[k]-1)+1;
			st[++tp]={pos[k],z};
		}
		for (int i=1;i<=tp;i++){
			update(st[i].l,st[i].mx);
		}
	}
	cout<<query(n)<<"\n";
	return 0;
}
```

---

## 作者：toolong114514 (赞：1)

# AT_arc133_b [ARC133B] Dividing Subsequence 题解
## 题面大意
[传送门。](https://www.luogu.com.cn/problem/AT_arc133_b)
## 解题思路
这题被搬去某模拟赛当 T1，赛时想了一个非常智障的 $O(n\log^3{n})$ 的 DP，~~只比暴力多 10pts。~~

我们考虑对于每一个 $a_i$，枚举它的倍数，将所有对应的 $b_j$ 记为若干个二元组 $(i,j)$。

那么原问题就变为选取若干个二元组，使其成为合法的序列。

又注意到选取出来的必须是原来的子序列，所以将选取的二元组按 $i$ 排序后，$j$ 也得单调递增，同时 $i,j$ 均不能重复。

这是典型的 LIS（最长上升子序列）问题。

排序时，要按 $i$ 为第一关键字升序，$j$ 为第二关键字降序排序，这样跑 DP 时可以避免 $i$ 的重复。

只要保证严格上升，跑 DP 时选取的 $j$ 显然不会重复。

处理是简单的。

观察到二元组 $(i,j)$ 一共只有 $\sum^{n}_{i=1}\frac{n}{i}\approx n\ln{n}$ 个，所以用树状数组优化 DP 跑 LIS 与排序的总时间复杂度约为 $O(n\log^2{n})$，可以通过本题。
## 参考代码

```cpp
#include<unordered_map>
#include<algorithm>
#include<iostream>
using namespace std;
const int N=2e5+10;
int lowbit(int x){
	return x&(-x);
}
struct ccf{
	int val1,val2;
}arr[20*N];
bool cmp(ccf pre,ccf nxt){
	if(pre.val1!=nxt.val1) return pre.val1<nxt.val1;
	else return pre.val2>nxt.val2;
}
int a[N],b[N],tr[N],f[N],maxn[N];
int n,ans,cnt;
void upd(int x,int val){
	while(x<=n){
		maxn[x]=max(maxn[x],val);
		x+=lowbit(x);
	}
}
int ask(int x){
	int res=0;
	while(x>0){
		res=max(res,maxn[x]);
		x-=lowbit(x);
	}
	return res;
}
int main(){
//	freopen("sample/T1.in","r",stdin);
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		tr[b[i]]=i;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;a[i]*j<=n;j++){
			arr[++cnt]={i,tr[a[i]*j]};
		}
	}
	sort(arr+1,arr+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		f[i]=ask(arr[i].val2-1)+1;
		upd(arr[i].val2,f[i]);
		ans=max(ans,f[i]);
	}
	cout<<ans;
	return 0;
}
```
[本代码可以通过 AT 的评测。](https://www.luogu.com.cn/record/171990164)

Written by [toolong114514](https://www.luogu.com/user/477821) on 2024/8/11.

---

## 作者：__FL__ (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_arc133_b)

## 题意

题意。其中 $\forall$ 表示“任意”。

## 思路

发现是两个 $1$ 到 $n$ 的排列找子序列，考虑用类似[最长公共子序列](https://www.luogu.com.cn/problem/P1439)的方法来做。

用桶来记录 $q$ 中元素出现的位置，枚举 $p_i$ 的倍数 $q_j$，保留 $(i,j)$ 压入数组 $f$，以 $i$ 为第一关键字进行排序，对 $j$ 跑一遍最长上升子序列就是答案，这时可以保证每个 $p_i$ 对应的 $q_j$ 都是 $p_i$ 的倍数。

如果直接这样跑最长上升子序列的话，序列中多个 $j$ 可能会匹配同一个 $i$，导致答案过大。想要避免这种问题，只要在 $i$ 已经有序的情况下，以 $j$ 为第二关键字降序排序就好了。

## 复杂度分析

考虑调和级数复杂度，枚举 $(i,j)$ 部分复杂度 $m$ 为 $O(n\log{n})$，这里不予详解，有需要请自行百度。

最长上升子序列方面时间复杂度为 $O(m\log{m})$，省略低次项，最终时间复杂度为 $O(n\log^2{n})$。

## Code


```cpp
#include<bits/stdc++.h>
#define PII pair<int,int>
using namespace std;
int n,p[4000005],q,book[4000005],l,sz;
PII f[4000005];
vector<int>ans;
bool cmp(PII a,PII b)
{
	if (a.second != b.second) return a.second < b.second;
	else return a.first > b.first;
}
int main()
{
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
		scanf("%d",&p[i]);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d",&q);
		book[q] = i;
	}
	for (int i = 1; i <= n; i++)
		for (int j = p[i]; j <= n; j += p[i])
		{
			if (book[j]) f[++l] = {i,book[j]};
		}
	sort(f+1,f+l+1,cmp);
	for (int i = 1; i <= l; i++)
	{
		if (!sz || ans[sz-1] < f[i].first) ans.push_back(f[i].first),sz++;
		else *lower_bound(ans.begin(),ans.end(),f[i].first) = f[i].first;
	}
	printf("%d",sz);
	return 0;
}
```

---

## 作者：zhu_wen (赞：1)

# Dividing Subsequence
这道题与[最长公共子序列](https://www.luogu.com.cn/problem/P1439)类似，可以先去水一水那道题。
## 题意
本题就是让你从 $p$ 里面选出一个子序列 $b_i$ 和 $q$ 里面选出一个子序列 $a_i$，我们要使 $b_i$ 是 $a_i$ 的倍数。
## 解法
本题直接用动态规划，是 $O(n^2)$ 做法，会超时，因此我们用树状数组维护区间最值来进行优化，那么本题与最长上升子序列的解法类似——因为我们求了前面的可以求后面的，但是求了后面的就不能求前面的了，而且还要求最长，因此是一个最长上升子序列问题。注意对于 $p_i$ 更新 $q_i$ 时要从大到小。

解释很多在代码上，请看代码：
## 代码
```cpp
// Problem: [ARC133B] Dividing Subsequence
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_arc133_b
// Memory Limit: 1 MB
// Time Limit: 5000 ms
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

#define lowbit(x) x & -x
#define pb push_back
#define all(x) x.begin(), x.end()
#define fst ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);

typedef long long ll;

const ll N = 1e6 + 10;

int n;     // n个元素
int a[N];  // p数组的每个元素
int b[N];  // q数组的每个元素
int c[N];  // c[]表示i元素在q数组中的位置

vector<int> v[N];  //存储i元素所有的倍数位置
int d[N];
void update(int x, int v) {
  while (x <= n) {
    d[x] = max(d[x], v);
    x += lowbit(x);
  }
}
int query(int x) {
  int res = 0;
  while (x) {
    res = max(d[x], res);
    x -= lowbit(x);
  }
  return res;
}

int main() {
  fst;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  // 3 1 4 2
  // 2 4 1 3
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    c[b[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      //对于i元素，i的倍数是j
      v[i].pb(c[j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    //目标维护a[i]的所有倍数出现的位置
    //对这个位置进行降序排列
    int t = a[i];
    sort(all(v[t]));
    reverse(all(v[t]));
    //就是求这个的最长上升子序列
    for (auto e : v[t]) {
      //对于e元素来说，求来的比我早的，且数值比我小的最大值
      int tmp = query(e - 1);
      update(e, tmp + 1);
    }
  }
  cout << query(n) << endl;
  return 0;
}
```
本题就愉快地结束了。

---

## 作者：FiraCode (赞：1)

### 思路：

发现是排列，于是考虑直接枚举 $a_i$ 的倍数对应 $b$ 序列中哪个数，显然的调和级数时间复杂度 $\mathcal{O(n \log n)}$。

于是对于每个数对 $(i,j)$，其实就是选出尽可能多的点使得 $i$ 和 $j$ 都严格单调递增，那么可以考虑将其中一维排序（满足一维的单调状态），然后对另一维再去用经典的贪心或权值树状数组做即可。

---

## 作者：w9095 (赞：0)

[AT_arc133_b [ARC133B] Dividing Subsequence](https://www.luogu.com.cn/problem/AT_arc133_b)

模拟赛原题，来写篇题解。

只考虑匹配的状态，根据调和级数的数学知识，匹配的状态数不多，为 $O(n\log n)$，考虑动态规划。

我们对于每个 $a_i$ 预处理出可以匹配的位置 $c_{i,j}$ 表示第 $i$ 位可以匹配的第 $j$ 个位置，记 $f_{i,j}$ 表示第 $i$ 位匹配第 $j$ 个可以匹配的位置的最长子序列长度。显然有以下转移方程：

$$f_{i,j}=\max_{l\lt i,c_{l,k}\lt c_{i,j}}\{f_{l,k}\}+1$$

线段树优化 dp，每次把 $f_{i,j}$ 插到 $c_{i,j}$ 上，查询时直接查询 $\lt c_{i,j}$ 的位置即可，时间复杂度 $O(n\log^2n)$。

模拟赛时被卡常了，不过 Atcoders 上稳过。

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int mx;
}tr[900000];
int n,a[300000],b[300000],p[300000],ans=0,cnt=0,rt=1;
vector<int>c[300000],f[300000];
void pushup(int x)
{
	tr[x].mx=max(tr[(x<<1)].mx,tr[(x<<1)|1].mx);
}

void update(int x,int l,int r,int p,int k)
{
	if(l==r)
	   {
	   	tr[x].mx=max(tr[x].mx,k);
	   	return;
	   }
	int mid=(l+r)>>1;
	if(p<=mid)update((x<<1),l,mid,p,k);
	else update((x<<1)|1,mid+1,r,p,k);
	pushup(x);
}

int query(int x,int l,int r,int lx,int rx)
{
	if(lx==0||rx==0)return 0;
	if(l>=lx&&r<=rx)return tr[x].mx;
	int mid=(l+r)>>1,ans=0;
	if(lx<=mid)ans=max(ans,query((x<<1),l,mid,lx,rx));
	if(rx>=mid+1)ans=max(ans,query((x<<1)|1,mid+1,r,lx,rx));
	return ans;
} 

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]),p[b[i]]=i;
	for(int i=1;i<=n;i++)
	    for(int j=a[i];j<=n;j+=a[i])
	        c[i].push_back(p[j]);
	for(int i=0;i<c[1].size();i++)f[1].push_back(1);
	for(int i=0;i<c[1].size();i++)update(rt,1,n,c[1][i],f[1][i]);
	for(int i=2;i<=n;i++)
	    {
	    for(int j=0;j<c[i].size();j++)f[i].push_back(query(rt,1,n,1,c[i][j]-1)+1);
		for(int j=0;j<c[i].size();j++)update(rt,1,n,c[i][j],f[i][j]);
	    }
	for(int i=1;i<=n;i++)
	    for(int j=0;j<f[i].size();j++)
	        ans=max(ans,f[i][j]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：N1K_J (赞：0)

模拟赛偶遇。

不妨取出所有满足 $a_i \mid b_j$ 的组 $(i,j)$，应当注意到这样的组至多 $O(n \log n)$ 组。

要取出尽可能多的组使得取出的相邻组满足二维偏序。

那么不妨先把这些组按照 $i$ 从小到大排序，我们用类似二维偏序计数的方式来维护一个值域。

例如对于当前的一组 $(i,j)$，我们来查询所有 $[1,j)$ 范围内的最大值，那么对于组 $(i,j)$，可以构成的最长序列是这个最大值 $+1$，然后把这个新的结果覆盖到 $j$​ 上就好。

这个是可以用树状数组来维护的，注意 $i$ 相同的组要先查询 $j$ 大的。

核心代码：

```cpp
bool cmp(const ll x,const ll y){return x>y;}
void main(){
  n = read();
  for(ll i = 1; i <= n; i++) p[i] = read();
  for(ll i = 1; i <= n; i++) pos[read()] = i;
  for(ll i = 1; i <= n; i++) for(ll j = p[i]; j <= n; j+=p[i]) vec[i].push_back(pos[j]);
  for(ll i = 1; i <= n; i++){
    sort(vec[i].begin(),vec[i].end(),cmp);
    for(auto v : vec[i]) upd(v,query(v-1)+1);
  }
  printf("%lld\n",query(n));
```

---

## 作者：Union_Find (赞：0)

# 题面

给你两个序列 $a$ 和 $b$，从 $a$ 中取出一个长度为 $k$ 的子序列 $p$，从 $b$ 中取出一个长度为 $k$ 的子序列 $b$，满足 $a_i \mid b_i$，求最大的 $k$。

# 分析

首先一点很明显，满足 $a_i \mid b_j$ 的二元组 $(i,j)$ 只有 $O(n \log n)$ 对，所以我们可以先预处理出所有合法的 $(i,j)$。

我们可以把这些二元组视为平面上的点，先画到平面上找规律。

![](https://cdn.luogu.com.cn/upload/image_hosting/agan4mee.png)

如果我们把最优的子序列对应的点对连起来，我们发现它是单调上升的。

我们如果先将所有点对按照 $i$ 排序，然后按照 $j$ 求最长上升子序列，答案是不是就对了呢？

并不是，因为他有可能会选到 $i$ 是相同的两个点对。

这里就有两种解决方法。第一种就是在二分优化的时候，只有所有 $i$ 相同的点对都 dp 完了再加入二分的数组。因为每个点对只加入一次，所以加入的时间复杂度是 $O(m)$ 的，dp 转移是 $O(m \log m)$ 的。这里 $m$ 表示点对数，大约是 $O(n \log n)$ 的，最终时间复杂度是 $O(n \log^2 n)$ 的。

但是这种写法太麻烦了。我们可以把排序改一改。在 $i$ 相同的时候按照 $j$ 倒序排序，就可以避免选到相同的 $i$。

我写的是第二种写法，比较好写。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 200005
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll n = rd(), a[N], p[N], cnt, d[N], ans, minn = 1e18;
struct P{
	ll a, b;
}t[N << 5];
il bool cmp(P a, P b){
	if (a.b != b.b) return a.b < b.b;
	return a.a > b.a;
}
int main(){
	for (int i = 1; i <= n; i++) a[i] = rd();
	for (int i = 1; i <= n; i++) p[rd()] = i;
	for (int i = 1; i <= n; i++) for (int j = a[i]; j <= n; j += a[i]) t[++cnt] = P{i, p[j]};
	sort (t + 1, t + cnt + 1, cmp);
	for (int i = 1; i <= cnt; i++){
		ll p = lower_bound(d + 1, d + ans + 1, t[i].a) - d;
		d[p] = t[i].a;
		ans = max(ans, p);
		//cout << t[i].a << " " << t[i].b << "\n";
	}
	printf ("%lld\n", ans);
	return 0;
}

```

---

## 作者：complete_binary_tree (赞：0)

考虑 DP。

设 $f_{i,j}$ 为 $a$ 前 $i$ 个数和 $b$ 前 $j$ 个数能组成的最长序列长度。

发现 $i$ 无用，可以枚举 $i$ 将其压缩掉。（此时状态为 $f_j$）

对于 $a_i$，发现 $\sum_{b_j} [a_i \mid b_j]$ 是调和级数复杂度。所以可以枚举 $b_j = k \cdot a_i$ 中的 $k$ 进行转移。

对于 $a_i \mid b_j$，转移为 $f_j = \max_{l=1}^{j-1} \{f_l\} + 1$。暴力转移为 $O(n^2 \ln n)$，考虑线段树优化转移。

线段树维护单点修改和区间查询，时间复杂度 $O(n \ln n \log n)$。

细节：

- 建立一个 $b_i \to i$ 的映射（程序中为 `mp[]` 数组）方便枚举 $b_j$ 时查询其位置。

- 不能求值后马上赋值（因为可能影响到下个求值），需要将其储存下来待全部修改完统一赋值；或者从后往前求值并修改。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

struct tree { int l, r, mx; };
struct st {
    tree t[N << 2];
    void build ( int x, int l, int r ) {
        t[x].l = l, t[x].r = r;
        if ( l == r ) {
            t[x].mx = 0;
            return ;
        }
        int mid = ( l + r ) >> 1;
        build ( 2 * x, l, mid ), build ( 2 * x + 1, mid + 1, r );
        t[x].mx = max ( t[2 * x].mx, t[2 * x + 1].mx );
    }
    void change ( int x, int pos, int y ) {
        if ( t[x].l == t[x].r ) {
            t[x].mx = y;
            return ;
        }
        int mid = ( t[x].l + t[x].r ) >> 1;
        if ( pos <= mid ) change ( 2 * x, pos, y );
        else change ( 2 * x + 1, pos, y );
        t[x].mx = max ( t[2 * x].mx, t[2 * x + 1].mx );
    }
    int query ( int x, int l, int r ) {
        if ( r < l ) return 0;
        if ( t[x].l > r || t[x].r < l ) return 0;
        if ( t[x].l >= l && t[x].r <= r ) return t[x].mx;
        return max ( query ( 2 * x, l, r ), query ( 2 * x + 1, l, r ) );
    }
} t1;

int n, a[N], b[N], mp[N], lin[N];

int main() {
    ios::sync_with_stdio( 0 ), cin.tie( 0 ), cout.tie( 0 );
    cin >> n;
    t1.build ( 1, 1, n );
    for ( int i = 1; i <= n; ++i ) cin >> a[i];
    for ( int i = 1; i <= n; ++i ) cin >> b[i], mp[b[i]] = i;
    for ( int i = 1; i <= n; ++i ) {
        for ( int j = 1; a[i] * j <= n; ++j )
            lin[a[i] * j] = t1.query ( 1, 1, mp[a[i] * j] - 1 ) + 1;
        for ( int j = 1; a[i] * j <= n; ++j )
            t1.change ( 1, mp[a[i] * j], lin[a[i] * j] );
    }
    cout << t1.query ( 1, 1, n ) << endl;
    return 0;
}
```

---

## 作者：Windy_Hill (赞：0)

## 题意
题意够清楚了，主要解释一下 $\forall i\in [1,k],a_i\mid b_i$。这个指的就是对于你选出来的子序列 $a$ 与 $b$，每个 $b$ 中的数都是 $a$ 所对应的数的倍数。

## 思路
我们可以用 ```dp``` 来解决问题，但是如果直接暴力会得到一篇 $O(n^2)$ 的代码，直接 ```TLE```。但是我们可以用树状数组去维护，每次 ```dp``` 转移的时候都将 ```dp``` 压到树状数组里。那么时间复杂度 $ O(n\log{^2}n)$。那就可以过掉了。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int tr[N], f[N], n;
int a[N], b[N], c[N];

//树状数组
int lowbit(int x)
{
    return -x & x;
}

void update(int x, int c)
{
    if (x == 0) return ;
    for (int i = x; i < 200010; i += lowbit(i)) tr[i] = max(tr[i], c);
}

int query(int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res = max(res, tr[i]);
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    //读入
    cin >> n;
    
    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    for (int i = 1; i <= n; i ++ ) cin >> b[i];
    //将位置存下来
    for (int i = 1; i <= n; i ++ ) c[b[i]] = i;
    
    for (int i = 1; i <= n; i ++ )
    {
        for (int j = a[i]; j <= n; j += a[i]) f[j] = query(c[j] - 1) + 1;//存储结果
        for (int j = a[i]; j <= n; j += a[i]) update(c[j], f[j]);//将结果上传
    }
    cout << query(n) << endl;
    
    return 0;
}
```

---

