# [ABC155D] Pairs

## 题目描述

$N$个数两两相乘的结果有 $\frac{N(N-1)}{2}$ 种，问第 $K$ 小的乘积是多少。

## 说明/提示

$N \leq 2 \times 10^5,-10^9 \leq A_i \leq 10^9$

## 样例 #1

### 输入

```
4 3
3 3 -4 -2```

### 输出

```
-6```

## 样例 #2

### 输入

```
10 40
5 4 3 2 -1 0 0 0 0 0```

### 输出

```
6```

## 样例 #3

### 输入

```
30 413
-170202098 -268409015 537203564 983211703 21608710 -443999067 -937727165 -97596546 -372334013 398994917 -972141167 798607104 -949068442 -959948616 37909651 0 886627544 -20098238 0 -948955241 0 -214720580 277222296 -18897162 834475626 0 -425610555 110117526 663621752 0```

### 输出

```
448283280358331064```

# 题解

## 作者：GUO120822 (赞：6)

题目就是叫我们求一个序列选两个数乘积的第 $k$ 小，但数据量很大，不能暴力。

考虑二分，这一定具备单调性。如果比它小的乘积的数量小于 $k$，则满足条件。最后取满足条件的右边界，不能再大了，则为答案。

于是，问题就变成了这样：给定一个数，让你求序列中两两乘积小于它的个数。

这个问题就需要分类讨论了。因为负负得正！

把数组排序，在一个有序数组里，考虑以下两种情况：

若 $a_i<0$，则和它配对的数越大乘积越小。

否则，就是配对数越大乘积越大。

因为是有序数组，所以又可以二分。

若 $a_i<0$，找到乘积小于 $mid$ 的第一个数 $l$。那么后面的都满足。$ans$ 加上 $i-l$。 

否则，找到乘积小于 $mid$ 的最后一个数 $r$。那么前面的都满足。$ans$ 加上 $r$。

思路讲的很清楚了，下面是[代码](https://www.luogu.com.cn/record/152971539)。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int n,i;
ll k,a[N];
ll l,r,mid;
bool check(ll x)
{
	int i,l,r,mid;
	ll sum=0;
	for (i=1;i<=n;i++)
	{
		if (a[i]<0)
		{
			//越大越小 
			l=1;
			r=i-1;
			while (l<=r)
			{
				mid=l+r>>1;
				if (a[i]*a[mid]<x) r=mid-1;
				else l=mid+1;
			}
			//l:乘积小于 x 的第一个数。那么后面的都满足。 
			sum+=i-l;
		}
		else
		{
			//越大越大 
			l=1;
			r=i-1;
			while (l<=r)
			{
				mid=l+r>>1;
				if (a[i]*a[mid]<x) l=mid+1;
				else r=mid-1;
			}
			//r:乘积小于 x 的最后一个数。那么前面的都满足。 
			sum+=r;
		}
	}
	return sum<k;
}
int main()
{
	scanf("%d%lld",&n,&k);
	for (i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	l=-1e18;
	r=1e18;
	while (l<=r)
	{
		mid=l+r>>1;
		if (check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%lld",r);
	return 0;
}
```

---

## 作者：dd_d (赞：6)

## Sol  
考虑转换一下题意。  
题目中要求我们求第 $K$ 小，实际上就是第 $N*(N-1)/2-K+1$ 大。  
考虑二分这个值，记这个值为 $mid$  
分以下情况进行讨论。  

- 当 $mid<0$ 时，那么显然，任意 $a[i]$ 为正数或 $0$ 的组合都满足要求。然后对每个 $a_i$ 为正数，$a_j$ 为负数这样的组合进行判断是否大于 $mid$，这一步操作可以用二分实现，时间复杂度 $O(n\ \log\ n)$。  
- 当 $mid=0$ 时，显然，除了 $a_i$ 为正，$a_j$ 为负的组合其余都满足要求。  
- 当 $mid>0$ 时，显然，只有当 $a_i$ 和 $a_j$ 同号时才有可能满足要求。而判断积是否大于 $mid$ 同样可以用二分实现。  

具体细节看代码。  
代码中用双指针来替代二分。
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=3e5+1;
int n,k,a[N],l,r,ans,nnn,m,cnt,b[N];
int solve(int x)
{
	int sum=n*(n-1)/2+m*(m-1)/2+cnt*n+cnt*m+cnt*(cnt-1)/2;
	reverse(b+1,b+m+1);
	reverse(a+1,a+n+1);
	for (int i=1,j=n;i<=m;i++)
	{
		while (j>=1&&b[i]*a[j]>=x) 
			j--;
//			cout<<j<<endl;
		sum+=n-j;
	}
	reverse(b+1,b+m+1);
	reverse(a+1,a+n+1);
	return sum;
}
int SOLVE(int x)
{
	int sum=0;
	for (int i=1,j=n;i<=n;i++)
	{
		while (j>=1&&a[i]*a[j]>=x)
			j--;
		sum+=(n-j);
	}
	for (int i=1,j=m;i<=m;i++)
	{
		while (j>=1&&b[i]*b[j]>=x)
			j--;
		sum+=(m-j);
	}
	for (int i=1;i<=n;i++)
		if (a[i]*a[i]>=x) sum--;
	for (int i=1;i<=m;i++)
		if (b[i]*b[i]>=x) sum--;
	return sum/2;
}
bool check(int x)
{
	int ans=0;
	if (x==0) ans=nnn*(nnn-1)/2-n*m;
	if (x<0) ans=solve(x);
	if (x>0) ans=SOLVE(x);
//	writeln(ans);
	return k<=ans;
}
signed main()
{
	nnn=read(); k=read();
	for (int i=1;i<=nnn;i++)
	{
		int x=read();
		if (x>0) a[++n]=x;
		if (x<0) b[++m]=x;
		if (x==0) cnt++;
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1,greater<int>());
	k=nnn*(nnn-1)/2-k+1;
	l=-1e18; r=-l;
	while (l<=r)
	{
		int mid=(l+r)>>1;
		if (check(mid))
		{
			l=mid+1;
			ans=mid;
		}
		else r=mid-1;
//		cout<<mid<<' '<<l<<' '<<r<<endl;
//		putchar('\n');
	}
	writeln(ans);
}

```


---

## 作者：Erica_N_Contina (赞：3)

# [ABC155D] Pairs

## 题面

$N\ (N \leq 2 \times 10^5,-10^9 \leq A_i \leq 10^9)$ 个数两两相乘的结果有 $\frac{N(N-1)}{2}$ 种，问第 $K$ 小的乘积是多少。

## 思路

复杂二分。



我们采用排序 + 二分答案 + 二分来实现。

实现在 `long long` 范围内二分答案 $num$，进入判定 `judge(num)`。

然后枚举 $a1$ 从 $a_{1\sim n}$ 中，计算出 $aa=num÷a1$。

我们要统计 $a1\times a_i<num$ 的个数 $s$，如果 $s>k$，那么二分答案 $num$ 区间取 $l\sim mid$。

那么如何统计 $a1\times a_i<num$ 的个数 $s$ 呢？

我们用二分枚举 $a_i$ 从 $a_{1\sim n}$，找到一个 $a_i$ 使得其一边是 $a_j\times a1<num$，另一边 $a_j\times a1>num$。

那么我们就开始写吧！

第一个二分答案。

```C++
    int l=-1e18,r=1e18;
	while(l<r){
		int mid=(l+r)/2;
		if(judge(mid))l=mid+1;//judge()中如果a[i]*a[j]比mid小的有>k个，会返回假
		else r=mid;
	}
    cout<<mid<<endl;
```


第二个二分，统计在乘积和 $a_i$ 固定下，满足：$a_j\times a_i<$ 乘积 的 $a_j$ 个数。


`judge()` 函数：

```C++
bool judge(int num){
	int res,sum=0;
	for(int i=1;i<n&&a[i]<=0;i++){//枚举<=0的a[i] 
		if(a[i]*a[i+1]<num)continue;
		int l=i+1,r=n;
		while(l<r){//找到<a2的a[mid] 
		     int mid=(l+r)/2;
		     if(a[mid]*a[i]>=num)l=mid+1;//乘积大了，注意，a[i]<0，a[mid]越大，乘积越小，若a[mid]<0也一样 
		     else r=mid-1;
		}
		sum+=res-i;//a[i+1~res]*a[i]均<num//(<=??)
	}
    int sz=b.size();
	for(int i=0;i<sz-1;i++){//枚举>0的a[i] (已经存在b中了,b中从小到大存储),二分a[j](j>i)
		if(b[i]*b[i+1]<num)continue;
		int l=i+1,r=sz-1;
		while(l<r){//找到<a2的a[mid] 
		     int mid=(l+r)/2;
		     if(b[mid]*b[i]>=num)r=mid-1;//乘积大了 
		     else l=mid+1;
		}
		sum+=res-i;
	}
	return sum<=k;
}

```


我们要意识到：

- 当 $a_i>0$ 时，**$a_j$** **一定 $>0$**，这样就可以优化一种情况。

- 当 $a_i<0$，$a_{mid}$ 越大，乘积越小，**若 $a_{mid}<0$** **也一样**。

所以我们只把情况分为 $a_i>0$ 与 $a_i≤0$ 两种。


注释：$a1$ 即 $a_i$。

因为这样划分的话区间内 $a_i\times a_j$ 单调性一定是单调递增 / 递减的，不会有分块单调性不同的情况，这样我们就好写多了。注意一点，$a1>0$ 和 $a1<0$ 的单调性是相反的，因此在代码中：

```C++
if(b[mid]*b[i]>=num)r=mid-1;
if(a[mid]*a[i]>=num)l=mid+1;
```


在代码中，我们将 $b$ 进行翻转，就不需要这样了。

## Code

```C++
/*////////ACACACACACACAC///////////
      . Coding by Ntsc .
      . ToFind Chargcy .
      . Prove Yourself .
/*////////ACACACACACACAC///////////

#include <bits/stdc++.h>
#define int long long
#define db double
#define rtn return
#define i1n int i=1;i<=n;i++
#define in1 int i=n;i>=1;i--
using namespace std;

const int N = 2e5 + 5;
const int M = 1e5;
const int Mod = 1e5;
const int INF = 1e5;

vector<int> b;
int n, a[N], k, ans;

bool judge(int num) {
	int res, sum = 0;
	for (int i = 1; i < n && a[i] <= 0; i++) { //枚举<=0的a[i]
		if (a[i]*a[i + 1] < num)//优化
			continue;
		int l = i + 1, r = n;
		while (l <= r) { //找到<a2的a[mid]
			int mid = (l + r) /2;
			if (a[mid]*a[i] >= num)
				l = mid + 1, res = mid; //乘积大了，注意，a[i]<0，a[mid]越大，乘积越小，若a[mid]<0也一样
			else
				r = mid - 1;
		}
		sum += res - i; //a[i+1~res]*a[i]均<num//(<=??)
	}
	int sz=b.size();//注意这里b.size()要先存起来,否则会RE
	for (int i = 0; i < sz - 1; i++) { //枚举>0的a[i] (已经存在b中了,b中从小到大存储),二分a[j](j>i)
		if (b[i]*b[i + 1] < num)
			continue;
		int l = i + 1, r = sz - 1;
		while (l <= r) { //找到<a2的a[mid]
			int mid = (l + r) /2;
			if (b[mid]*b[i] >= num)
				l = mid + 1, res = mid;//乘积大了
			else
				r = mid - 1;
		}
		sum += res - i;
	}
	return sum >= k;
}

signed main() {
	cin >> n >> k;
	k = n * (n - 1) / 2 - k + 1; //转化为求第k大
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		if (a[i] > 0)
			b.push_back(a[i]);
	}
	reverse(b.begin(), b.end());
	int l = -1e18, r = 1e18;
	while (l <= r) {
		int mid = (l + r) >>1;
		if (judge(mid))
			l = mid + 1, ans = mid; //judge()中如果a[i]*a[j]比mid小的有>k个，会返回假
		else
			r = mid - 1;
	}
	cout << ans << endl;
	return 0;
}


```


**一个问题**

在代码中 `int sz=b.size();` 这里 `b.size()` 要先存起来，否则会 RE，为啥？

引用 wyhnet 大佬回答：因为 `size()` 返回 unsigned，如果 $size $ 为 $0$ 那么 $size-1=2\times INT_{max}$，访问越界所以 RE。


## Updates
23.7.26 解决问题。




---

## 作者：hyxgg (赞：2)

[题目](https://www.luogu.com.cn/problem/AT_abc155_d)
## 思路
### 主体思路
先分正负两类讨论，再二分答案。
### 实现
#### 分类
输入时将正负分开存，设正数 $zd$ 个，负数 $fd$ 个，当 $zd \times fd\geq k$ 时答案为负数，反之为正数（零在哪都无所谓）。
#### 负数
在最小的负数乘积和最大的负数乘积之间二分。

对于二分到的答案找比其小的乘积的个数，以此判断大了还是小了。
怎么找呢？枚举正数（或负数）数组，二分（或者用单调性优化）另一个数组即可。

最后二分到的答案即为所求。
#### 正数
大体与负数相同，但因为是在数组内部找乘积，所以要额外判个重。
## 代码
代码如下，有问题评论区见。
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
ll n,k,a[200005],z[200005],f[200005],zd,fd;
int main(){
	scanf("%lld%lld",&n,&k);
	ll aa;
	for(ll i=1;i<=n;i++){
		scanf("%lld",&aa);
		if(aa<0){
			f[++fd]=aa;
		}
		else{
			z[++zd]=aa;
		}
	}
	sort(f+1,f+1+fd);
	sort(z+1,z+1+zd);
	ll l,r,ans=0;
	if(k<=fd*zd){
		r=f[fd]*z[1],l=f[1]*z[zd];
		while(l<=r){
			ll mid=(l+r)>>1,dk=0;
			for(ll i=fd,j=zd+1;i>=1;i--){
				while(f[i]*z[j-1]<=mid&&j)j--;
				dk+=zd-j+1;
			}
			if(dk>=k){
				
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
	}
	else{
		k-=fd*zd;
		for(ll i=1;i<=fd;i++){
			f[i]*=-1;
		}
		sort(f+1,f+1+fd);
		l=min(f[1]*f[2],z[1]*z[2]),r=max(f[fd]*f[fd-1],z[zd]*z[zd-1]);
		while(l<=r){
			ll mid=(l+r)>>1,dk=0;
			for(ll i=zd,j=0;i>=1;i--){
				while(z[i]*z[j+1]<=mid&&j<zd)j++;
				dk+=min(j,i-1);
			}
			for(ll i=fd,j=0;i>=1;i--){
				while(f[i]*f[j+1]<=mid&&j<fd)j++;
				dk+=min(j,i-1);
			}
			if(dk>=k){
				ans=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
	}
	printf("%lld",ans);
	return 0;
} 
```

---

## 作者：abensyl (赞：2)

原题：[ABC155D Pairs](https://www.luogu.com.cn/problem/AT_abc155_d)。

一道非常好，非常经典的题目。

## 做法

很明显，本题朴素做法时间复杂度 $O(n^2\log n)$，不可取。

然后我们可以二分答案：

- 问题来了，二分的判断函数怎么写？

> 假设二分传参为 $x$，考虑有多少对 $(i,j)$，满足 $a_i\times a_j\leq x$，设为 $t$，比较 $k$ 与 $t$ 大小即可。

- 如何快速判断 $a_i\times a_j\leq x$ 的对数？

> 也可以使用二分，但是注意，这里要分情况讨论：

> - $a[i]\geq0$，我们需要找到所有 $a[j]\leq {x\over a[i]}$。  
> - $a[i]>0$，我们需要找到所有 $a[j]\geq {x\over a[i]}$。  
> 注意：如果写除法需要特判 $a[i]=0$ 的情况并且自己不能和自己相乘。

本题的几个坑点总结：

1. 有正数有负数和 $0$，要分别处理。  
2. 二分的时候很不好写，也很难调。  
3. 不要忽略自己乘以自己的情况。  

时间复杂度：$O(n\log^2n)$，可接受。

## 代码：

```cpp
#include <bits/stdc++.h>

#define int long long
#define cmp1 [&](int i, int j) {return i * j <= m;}
#define cmp2 [&](int i, int j) {return i * j > m;}

using namespace std;

const int N = 5e5 + 3;
int a[N];

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  int n; cin >> n;
  int k; cin >> k;
  k = (k - 1) * 2;
  for (int i = 0; i < n; ++i) cin >> a[i];
  sort(a, a + n);
  int l = -1e18, r = 1e18;
  while (r - l > 1) {
    int m = l + (r - l) / 2;
    int tot = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] > 0) tot += lower_bound(a, a + n, a[i], cmp1) - a;
      else if (a[i] < 0) tot += a + n - lower_bound(a, a + n, a[i], cmp2);
      else tot += m >= 0 ? n : 0;
      if (a[i] * a[i] <= m) tot--;
    }
    if (tot <= k) l = m;
    else r = m;
  }
  cout << r << '\n';
  return 0;
}
```

---

## 作者：Nemlit (赞：2)

~~这其实是一篇求助帖~~

要求出第k小的乘积，有负数有正数，不太好处理，于是不难想到二分答案，所以问题转化成给定一个k，求出有多少对数的乘积$\leq  mid$

我们分两类类讨论：

$Case1:$ 如果我们二分的值$x>=0$，所有乘积$<=0$的数对全部成立，那么任意负数与正数都成立，任意的0与所有非零数都成立，所有0内部组合也成立

然后我们考虑乘积大于0的。枚举每一个数，那么合法的另一个数的取值一定是在一段区间，二分找到端点就可以了。

$Case2:$ 对于所有$x<0$的二分值，一定是需要一个负数乘以一个正数，也可以用二分来找到对应合法区间

总复杂度$O(N*log_2N*log_2{10^{18}})$，其实二分值域以后内部可以用双指针来实现，复杂度为$O(N*log_2{10^{18}})$。

~~好的回归正题，这是一篇求助帖：~~

为什么$lower$_$bound$不加一些边界处理会有问题啊？（见代码打注释的那两行）

### $Code:$
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define int long long
#define D double
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define rep(i , a , b) for(int i = (a) , i##Limit = (b) ; i <= i##Limit ; ++ i)
#define maxn 200005
int n, m, a[maxn], ans, Mi = -1e18, Ma = 1e18, c1, c2, b[maxn], c[maxn], g, d[maxn], c3;
il int check(int x) {
	int tem = 0;
	if(x >= 0) {
		tem = g * (c1 + c2) + g * (g - 1) / 2 + c1 * c2;
		rep(i, 1, c1 - 1) tem += upper_bound(b + i + 1, b + c1 + 1, x / b[i]) - b - 1 - i;
		rep(i, 1, c2 - 1) tem += upper_bound(c + i + 1, c + c2 + 1, x / c[i]) - c - 1 - i;
	}
	else {
		x = -x;
		rep(i, 1, c1){
            int pos = lower_bound(c + 1, c + c2 + 1, (int)ceil((D)x / (D)b[i])) - c;
            ////对就是这两行
            if(b[i] * c[pos] < x) pos++;
            if(b[i] * c[pos - 1] >= x) -- pos;
            ////对就是这两行
            if(c2 >= pos) tem += c2 - pos + 1;
        } 
	}
	return tem >= m;
}
signed main() {
	n = read(), m = read();
	rep(i, 1, n) a[i] = read();
	rep(i, 1, n) {
		if(a[i] < 0) b[++ c1] = -a[i];
		else if(a[i] > 0) c[++ c2] = a[i];
		else ++ g;
	}
	sort(b + 1, b + c1 + 1), sort(c + 1, c + c2 + 1);
	while(Mi < Ma){
        int Mid = (Mi + Ma) >> 1;
        if(check(Mid)) Ma = Mid;
        else Mi = Mid + 1;
    }
	cout << Ma;
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：2)

对一个数 $r$ 有多少个乘积在这个数列里会小于等于 $r$？如果把这个数量称为 $f(r)$，可以得出来它的非递减性质：$f(r) \le f(r+1)$。应为我们希望找到最小的数 $R$ 满足 $f(R) = K$，可以二分答案。

如何求 $f(r)$ 呢？定义函数 $g(i, r)$ 为第 $i$ 个元素可以与多少不等于本身的元素乘是的乘积小于等于 $r$。现在有 
$$f(r) = \frac{1}{2}\sum^{n}_{i=1}g(i,r)$$
$g(i,r)$ 可以使用二分查找求：先排序所有元素。如果第 $i$ 个元素是负数，它和所有元素的乘积会非递增；如果是整数会非递减。先特判第 $i$ 元素为0的时候（答案为 $N-1$ 如果 $r$ 是非负整数，否则是 $0$）然后直接二分查找。

这样得到 $O(N\log^2N)$ 的时间效率，可过。

代码：

```
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

vector<int> A;
int n;

int ansify(int el, ll lim) {
    ll v = A[el];
    if(!v) return (lim >= 0)?(A.size()-1):0;
    int l = 0, r = n-1, ans = (v < 0)?n:(-1);
    while(l <= r) {
        int mid = (l+r)/2;
        if(v*A[mid] <= lim) {
            ans = mid;
            if(v < 0) r = mid-1;
            else l = mid+1;
        } else {
            if(v < 0) l = mid+1;
            else r = mid-1;
        }
    }
    if(v < 0) {
        int cnt = 0; if(ans <= el) cnt = -1;
        cnt += (n-ans); return cnt;
    } else {
        int cnt = 0; if(el <= ans) cnt = -1;
        cnt += (ans+1); return cnt;
    }
}

ll ttt(ll lim) {
    ll ans = 0;
    rep(i, n) ans += ansify(i, lim);
    return ans/2;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    ll K; cin >> K;
    rep(i, n) {
        int t; cin >> t;
        A.pb(t);
    }
    sort(all(A));
    ll l = -1000000000000000009ll, r = -l, ans = r;
    while(l <= r) {
        ll mid = (l+r)/2;
        if(K <= ttt(mid)) {
            ans = mid;
            r = mid-1;
        } else l = mid+1;
    }
    cout << ans << endl;
}

```

---

## 作者：Rain_Brush (赞：0)

题意：给定 $n$ 个数 $a_i$，求任意 $2$ 个数相乘结果第 $k$ 小的值。

考虑二分，记这个值为 $m$，分下列情况讨论：
- $m<0$，那么用对于每个 $a_i \times a_j$ 的组合进行对比，调整，时间复杂度 $O(n\ \text{log}\ n)$；
- $m=0$，那么除了 $a_i>0,a_j<0$ 的组合都可以；
- $m>0$，$a_i$ 与 $a_j$ 同号才能满足要求。

细节看代码。

$\text{AC Code:}$
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N=2e5+10;
ll inf=1e10;
ll a[N];
int n;ll k;
ll ans;

bool check(ll x){
	ll cnt=0,i,j;
	for(ll i=0;i<n;i++){
		if(a[i]*a[i]<=x) cnt--;
		if(a[i]>0){
			j=floor((long double)x/a[i]);
			ll pos=upper_bound(a,a+n,j)-a;
			cnt+=pos;
		}
		
		else if(a[i]<0){
			j=ceil((long double)x/a[i]);
			ll pos=lower_bound(a,a+n,j)-a;
			cnt+=(n-pos);
		}
		else
			if(x>=0) cnt+=n;
	}
	
	cnt/=2;
	return cnt>=k;
}

int main(){
	ios::sync_with_stdio(0);
	
	cin >> n >> k;	
	for(ll i=0;i<n;i++) cin >> a[i];
	
	sort(a,a+n);
	ll l=-(1ll<<60),r=1ll<<60;
	
	while(l<=r){
		ll mid=(l+r)>>1;
		
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	
	cout << ans;
	return 0;
}
```

[AC 记录](/record/116016496)

---

## 作者：I_am_sb___ (赞：0)

这是一道比较套路的题，题意要求将给出的 $N$ 个数分别两两相乘的 $ \frac{N(N-1)}{2} $ 个数中第 $K$ 小的数，这与一个经典二分答案模型非常类似，于考虑二分答案。

可以先二分答案两两相乘的数，则 `check` 的就用于判断这个数是第几大的数，我们发现在大于 $0$ 和小于等于 $0$ 时分别进行乘法就可以保证其单调性，先考虑对这个 $N$ 个数进行排序，现在看排序之后的序列。

枚举 $a_i \leq 0$，对于序列中所有下标大于 $i$ 的 $a_j$（即 $i<j$），其相乘都满足单调性，因此可以二分求出此时 $a_i$ 对于排名的贡献，当 $a_i > 0$ 时，单调性明显也存在，因此可以求解，由于在二分答案时我们又用了一次二分来判断排名，所以时间复杂为 $O(N \log^2N)$。

code：
```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

template <typename T>
inline void read(T &FF) {
    T RR = 1;
    FF = 0;
    char CH = getchar();
    for (; !isdigit(CH); CH = getchar())
        if (CH == '-')
            RR = -1;
    for (; isdigit(CH); CH = getchar()) FF = (FF << 1) + (FF << 3) + (CH ^ 48);
    FF *= RR;
}

template <typename T>
inline void write(T x) {
    if (x < 0)
        putchar('-'), x *= -1;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}

using namespace std;

const int N = 200007;
int n, k;
int ans;
int a[N];
vector<int> b;

bool check(int X) {
    int sum = 0, res;
    for (int i = 1; i < n && a[i] <= 0; ++i) {
        if (a[i] * a[i + 1] < X)
            continue;
        int l = i + 1, r = n;
        int mid = (l + r) >> 1;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (a[i] * a[mid] >= X) {
                res = mid;
                l = mid + 1;
            } else
                r = mid - 1;
        }
        sum += res - i;
    }
    int m = b.size();
    for (int i = 0; i < m - 1; ++i) {
        if (b[i] * b[i + 1] < X)
            continue;
        int l = i + 1, r = m - 1;
        int mid = (l + r) >> 1;
        while (l <= r) {
            mid = (l + r) >> 1;
            if (b[i] * b[mid] >= X) {
                res = mid;
                l = mid + 1;
            } else
                r = mid - 1;
        }
        sum += res - i;
    }
    return sum >= k;
}

signed main() {
    read(n);
    read(k);
    k = n * (n - 1) / 2 - k + 1;  //转化为求第k大（都一样
    for (int i = 1; i <= n; ++i) read(a[i]);
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
        if (a[i] > 0)
            b.emplace_back(a[i]);
    reverse(b.begin(), b.end());
    int l = -1e18, r = 1e18;  //范围值域
    int mid = (l + r) >> 1;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid + 1;
            ans = mid;
        } else
            r = mid - 1;
    }
    write(ans);
    return 0;
}
```

---

## 作者：suxxsfe (赞：0)

[题目](https://atcoder.jp/contests/abc155/tasks/abc155_d)  
**两次二分**  
首先对ans进行二分，在$[-10^{18},10^{18}]$之间  
考虑怎么check  
对于每个ans，枚举每个$a_i$，二分查找有几个$a_j$，使得$a_i\times a_j<ans$  
对于每对合法的$(a_i,a_j)$，枚举到$a_i$和$a_j$的时候都被找了一遍，所以最后应该除以2来去重  
因为不能出现$a_i=a_j$，所以返回的时候要把$i=j$的情况去掉  
两个数组a,b  
将输入的数在a中按升序排序，在b中按降序排  
在第二次二分时，当$a_i<0$，用b数组二分（负负得正，所以此时绝对值更大的负时是“大”的，因为它与$a_i$的乘积更大），当$a_i\geq 0$，用a数组，这样保证了可二分性  
通过第一层二分，我们找到的其实是在n个$a_i$两两相乘得到的数中，比从小到大第k个数大的最小数，所以要输出$ans-1$  
复杂度$O(n\log n\log 10^{18})$  
code.  
```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<cstring>
#define R register
#define EN std::puts("")
#define LL long long
inline LL read(){
	LL x=0,y=1;
	char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
//a:abs大的负数->abs小的负数->小正数->大正数
//b:大正数->小正数->abs小的负数->abs大的负数 
int n,fir;//a[fir]是a数组中第一个非负数
LL k;
LL a[200006],b[200006];
inline int finda(int i,LL ans){
	R int l=1,r=n,mid,ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(a[mid]*a[i]<ans) ret=mid,l=mid+1;
		else r=mid-1;
	}
	return ret>=i?(ret-1):ret;//如果ret>=i，说明其中有一对是两个a[i]相乘得到，此时要减1
}
inline int findb(int i,LL ans){
	R int l=1,r=n,mid,ret=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(b[mid]*a[i]<ans) ret=mid,l=mid+1;
		else r=mid-1;
	}
	return (ret+i>n)?(ret-1):ret;//同理，但b是倒序
}
inline int check(LL ans){
	LL nowk=0;
	for(R int i=1;i<fir;i++)//负数 
		nowk+=findb(i,ans);
	for(R int i=fir;i<=n;i++)//正数
		nowk+=finda(i,ans);
	nowk/=2;//去重
	return nowk>=k;
}
inline int cmp(int x,int y){
	return x<y;
}
int main(){
	n=read();k=read();
	for(R int i=1;i<=n;i++) a[i]=read(); 
	std::sort(a+1,a+1+n,cmp);
	fir=n+1;
	for(R int i=1;i<=n;i++)
		if(a[i]>=0){fir=i;break;}
	for(R int i=1;i<=n;i++) b[n-i+1]=a[i];//存入b数组，对负数二分时使用
	R LL l=-1e18,r=1e18,mid,ans;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	std::printf("%lld",ans-1);
	return 0;
}
```

---

## 作者：MikukuOvO (赞：0)

比较套路的一道题，话说谁告诉我$ABC$都是语言基础题来着。。。

首先我们考虑二分答案，这样我们只需要判断有多少个点对小于等于$val$然后和$k$进行比较即可。

考虑到有负数和零的情况，首先我们将正负数分开，这样我们大力分类讨论：

先考虑零的情况，发现这个只和$val$的正负有关。

考虑两个整数相乘或两个负数相乘，发现$twopointer$维护或直接二分即可。

考虑一个整数和一个负数相乘，发现还是具有单调性，维护方法同上。

---

## 作者：StevenLiTheOIer (赞：0)

## 思路：
二分答案。

我们考虑怎么写 check 函数。对于一个数 $x$，二分出有多少个数乘 $a_i$ 的积小于 $x$，最后把答案除以 $2$，看是否小于 $k$。

但是因为 $a_i$ 分正负数和 $0$，分类讨论：

+ $a_i<0$，则另一个因数越小积越大。
+ $a_i\ge0$，则另一个因数越大积越大。

所以需要原数组 $a$ 的倒序数组 $b$，用来对负数二分。

详细请见代码。
## Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, offset, a[200006], b[200006];
int lowerbound(long long x, long long y) //二分正数
{
	int l = 1, r = n, pos = 0;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (a[y] * a[mid] < x) l = mid + 1, pos = mid;
		else r = mid - 1;
	}
	return pos >= y ? pos - 1 : pos; //当 pos >= y 时，出现了 a[y] * a[y] < x，所以要减 1，下同
}
int upperbound(long long x, long long y) //二分负数
{
	int l = 1, r = n, pos = 0;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (a[y] * b[mid] < x) l = mid + 1, pos = mid;
		else r = mid - 1;
	}
	return pos >= n - y + 1 ? pos - 1 : pos;
}
bool check(long long x)
{
	long long cnt = 0;
	for (int i = 1; i < offset; i++)
		cnt += upperbound(x, i);
	for (int i = offset; i <= n; i++)
		cnt += lowerbound(x, i);
	return cnt / 2 <= k - 1;
}
int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a + 1, a + n + 1);
	offset = n + 1;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] >= 0)
		{
			offset = i; //找出正负数的分界点
			break;
		}
	}
	for (int i = 1; i <= n; i++)
		b[n - i + 1] = a[i];
	long long l = -1ll * 1e18, r = 1e18; //单个数范围是1e9，乘积的范围是[-1e18, 1e18]
	while (l <= r) //比较标准的二分答案
	{
		long long mid = l + r >> 1;
		if (!check(mid)) r = mid - 1;
		else l = mid + 1;
	}
	cout << r << endl;
	return 0;
}
```

---

