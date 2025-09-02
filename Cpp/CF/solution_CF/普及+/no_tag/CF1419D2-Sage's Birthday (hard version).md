# Sage's Birthday (hard version)

## 题目描述

This is the hard version of the problem. The difference between the versions is that in the easy version all prices $ a_i $ are different. You can make hacks if and only if you solved both versions of the problem.

Today is Sage's birthday, and she will go shopping to buy ice spheres. All $ n $ ice spheres are placed in a row and they are numbered from $ 1 $ to $ n $ from left to right. Each ice sphere has a positive integer price. In this version, some prices can be equal.

An ice sphere is cheap if it costs strictly less than two neighboring ice spheres: the nearest to the left and the nearest to the right. The leftmost and the rightmost ice spheres are not cheap. Sage will choose all cheap ice spheres and then buy only them.

You can visit the shop before Sage and reorder the ice spheres as you wish. Find out the maximum number of ice spheres that Sage can buy, and show how the ice spheres should be reordered.

## 说明/提示

In the sample it's not possible to place the ice spheres in any order so that Sage would buy $ 4 $ of them. If the spheres are placed in the order $ (3, 1, 4, 2, 4, 2, 5) $ , then Sage will buy one sphere for $ 1 $ and two spheres for $ 2 $ each.

## 样例 #1

### 输入

```
7
1 3 2 2 4 5 4```

### 输出

```
3
3 1 4 2 4 2 5```

# 题解

## 作者：素质玩家孙1超 (赞：5)

本题最短做法，所有操作放到主函数里面不压行只有8行。

题目要求是只有一个便宜的夹在两个大的中间才算有效。并且边上的是没用的。

所以我们只要按照题目所要求的，在奇数位放大的，偶数位放小的就好了。

但有一点要注意，尽量避免小的旁边“比他大的”其实和他一样大。

其实只要保证单独偶数位或奇数位都为升序或都为降序即可。

代码:
```cpp

#include<bits/stdc++.h>
using namespace std;
const int Maxn=1e5+5;
inline int R()
{
	char ch=getchar();int x=0;bool f=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
int a[Maxn],n,ans[Maxn];
int main()
{
	n=R();
	for(int i=1;i<=n;i++) a[i]=R();
	sort(a+1,a+1+n);
	int p1=1,p2=n/2+1,num=0;
	for(int i=1;i<=n;i++)ans[i]=i%2?a[p2++]:a[p1++];
	for(int i=1;i<=n;i++)num+=(ans[i]<ans[i-1]&&ans[i]<ans[i+1]);
	printf("%d\n",num);
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
}


```

---

## 作者：7KByte (赞：3)

这里提供一个不同的做法。

比赛时和前几篇题解思路一样，然后交了一发``WA``了？？？

然后直接上平衡树。。。

不难证明偶数位上的最大值不大于奇数位上的最小值。

这样我们对$A$排序，排序后前一半放偶数位，后一半放奇数位。

然后考虑每个偶数位，在它前一位贪心的放比它大的最小的数，这可以通过二分或平衡树来完成。

我们并不需要手写平衡树，直接``multiset``即可。

注意下，如果没有比它大的了随便填一个没有被填的数即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,m,a[N],c[N];
multiset<int>q;
typedef multiset<int>::iterator it;
void solve(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int k=n>>1;
	rep(i,k+1,n){
		q.insert(a[i]);
	}
	int ans=0,T=0;
	rep(i,1,k){
		it y=q.upper_bound(a[i]);
		if(y==q.end())y--;
		q.erase(y);
		c[++T]=*y;
		c[++T]=a[i];
	}
	if(n&1)c[++T]=*q.begin();
	rep(i,2,n-1)if(c[i-1]>c[i]&&c[i+1]>c[i])ans++;
	printf("%d\n",ans);
	rep(i,1,n)printf("%d ",c[i]);
}
int main(){
	solve();
	return 0;
} 
```

---

## 作者：0xFF (赞：2)

#### 题目简述


------------
给一个序列 $a$，设序列 $a$ 中有 ```cnt``` 个数字满足其小于其左右两边的数，最大化 ```cnt``` 同时输出构造的 $a$ 序列。

#### 题目分析


------------
根据题设可以知道 ```cnt``` 最多不会超过 $\frac{n}{2}$ 因为不可能有连续的两个数同时满足题设。

接下来就是考虑如何构造才能使得 ```cnt``` 最大。

首先考虑序列最两边的数字是不满足题设的，所以我们可以令其最大，同时为了最大化 ```cnt```，可以考虑令奇数位上的数字都不满足题设，偶数位上的数字满足题设。

除此之外还需要考虑相邻两个数字如果相等的情况，其实只需要在开始操作之前将 $a$ 序列排序即可。

最后扫一遍整个序列记录答案。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define int long long
using namespace std;
const int N = 100010;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
    return x*f;
}
int a[N],n,ans[N];
signed main(){
	n = read();
	for(int i=1;i<=n;i++){
		a[i] = read();
	}
	sort(a+1,a+n+1);
	int pos1 = 1,pos2 = n/2+1;
	int num = 0;
	for(int i=1;i<=n;i++){
		if(i % 2 == 0){
			ans[i] = a[pos1++];
		}
		else ans[i] = a[pos2++];
	}
	for(int i=1;i<=n;i++){
		if(ans[i] < ans[i-1] && ans[i] < ans[i+1])
			num++;
	}
	printf("%lld\n",num);
	for(int i=1;i<=n;i++){
		printf("%lld ",ans[i]);
	}
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：2)

想要让“山谷”更多，我们最好使用一高一低相结合的方法。

所以，我们从低到高格一个放一个，轮流放，小的配比较小的，大的配比较大的，很容易。

最后会组成这样：

$A_x$ $A_1$ $A_{x+1}$ $A_2$ $A_{x+2}$ $A_3$ $...$ $A_n$

根据奇偶型会有细微差别。

然后，先把数列排好，再进行计算有多少商品可以购买。

代码如下：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int n,sum=0;
	cin>>n;
	int a[n+1],b[n+1];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n/2;i++){
		b[i*2]=a[i];
	}
	if(n%2==1){
		for(int i=n/2+1;i<=n;i++){
			b[i*2-n]=a[i];
		}
	}
	else{
		for(int i=n/2+1;i<=n;i++){
			b[i*2-n-1]=a[i];
		}
	}
	for(int i=2;i<n;i++){
		if(b[i-1]>b[i]&&b[i]<b[i+1]){
			sum++;
		}
	}
	cout<<sum;
	cout<<endl;
	for(int i=1;i<=n;i++){
		cout<<b[i]<<" ";
	}
	return 0;
}
```

---

## 作者：dead_X (赞：2)

## 前言
好像是重题。

抱歉觉得 D1 没什么价值就直接把 D2 的题解 Copy 过来了。
## 题意
给定 $n$ 个数 $a_i$ ，重排它们使得 $|S|$ 最大，其中 $S=\{x|1<x<n,a_{x-1}>a_x<a_{x+1}\}$
## 思路
二分答案。

显然如果答案为 $x$ ，我们只需要构造 $2x+1$ 个数并判断是否满足即可。

构造的方法如下：小配小，大配大。

也就是 $\red{a_{n-x}},a_1,\red{a_{n-x+1}},a_2,\red{a_{n-x+2}},a_3,\cdots,\red{a_{n-1}},a_x,\red{a_n}$。

为了方便理解，这里区分了颜色，红色为最大的数，黑色为最小的数，两者都从小到大排序。

注意一下二分的右区间。
## 代码
```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003],b[1000003],c[1000003];
bool check(int n,int x)
{
	int t=n-x-1;
	for(int i=1; i<=x; i++) b[i*2-1]=a[++t],b[i*2]=a[i];
	b[x*2+1]=a[++t];
	
	for(int i=1; i<=x; i++) if(b[i*2-1]<=b[i*2] || b[i*2]>=b[i*2+1]) return 0;
	
	t=x;
	for(int i=1; i<=x*2+1; i++) c[i]=b[i];
	for(int i=x*2+2; i<=n; i++) c[i]=a[++t];
	return 1;
}
int main()
{
	int n=read();
	for(int i=1; i<=n; i++) c[i]=a[i]=read();
	sort(a+1,a+n+1);
	int l=1,r=(n-1)/2;
	int res=0;
	while(l<=r)
	{
		int mid=(l+r)/2;
		if(check(n,mid)) res=mid,l=mid+1; else r=mid-1;
	}
	printf("%d\n",res);
	for(int i=1; i<=n; i++) printf("%d ",c[i]);
	return 0;
}
```

---

## 作者：MVP_Harry (赞：2)

其实这个hard version跟上一题区别不是很大。

我们的策略还是这样：从小到大将数列放到$2, 4, 6, \cdots $这些位置上。为什么呢？因为我们知道相邻两个里面至多只有一个满足条件，那么肯定是尽量把小的不要放在一起。

由于数组有可能有一样的，只需要最后扫一遍计算答案即可。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;

template<class Ty> 
inline void read(Ty & X) {
    X = 0; Ty flag = 1; char ch = getchar();
    while(ch < '0' || ch > '9') { if (ch == '-') flag = 0; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { X = (X << 1) + (X << 3) + ch - '0'; ch = getchar(); }
    if (!flag) X = ~(X - 1);
}

template<class Ty> 
inline void write(Ty X) {
    if (X < 0) { X = ~(X - 1); putchar('-'); }
    if (X > 9) write(X / 10);
    putchar(X % 10 + '0');
}

const int maxn = 1e5 + 5;

int N, b[maxn], c[maxn]; 

int main() {
    read(N);
    rep(i, 1, N) read(b[i]);
    sort(b + 1, b + N + 1);
    int cnt = 0; 
    /* 按照我们的贪心策略 */
    for (int i = 2; i <= N; i += 2) {
    	c[i] = b[i / 2];
    	++cnt;  
    }
    for (int i = 1; i <= N; i += 2) {
    	c[i] = b[++cnt]; 
    }
    int ans = 0; 
    /* 扫一遍统计答案 */
    for (int i = 2; i <= N - 1; i++) {
    	if (c[i] < c[i - 1] && c[i] < c[i + 1]) ++ans; 
    }
    cout << ans << endl; 
    for (int i = 1; i <= N; i++) cout << c[i] << " ";
   	cout << endl; 
    return 0; 
}

---

## 作者：cwd2023 (赞：1)

# CF1419D题解
### by cwd2023


---

### 题目描述：
有一个长度为 $n$ 的序列，你可以将其重新排列使满足**要求**的位置的数量最大。

要求：对于一个位置 $i$ $(1<i<n)$，满足 $a_{i-1}<a_i>a_{i+1}$。


---

### 思路：
不难看出，这是一道构造题，那么如果知道构造的上限，并向上限靠拢，这题就迎刃而解。

通过观察可以发现，主角不会选择两个连续的数，因为不可能满足：
- $a_{i-1}>a_i$
- $a_i>a_{i-1}$

所以，答案的上限就是 $\frac{n}{2}$。

怎么尽量靠拢呢？我们不妨假设能取到这个上界，且位置全是奇数或偶数（代码中是偶数）。

贪心地想，如果一个偶数位置旁放了比它大许多的数，好像有些大材小用，会导致后面大数不够用，所以我们在每个能取到的位置旁放上略大一些的便可。

如何保证偶数位尽量的都能有贡献呢？可以优先把小的数放在偶数位啊，即把前 $\frac{n}{2}$ 小的数放在偶数位，后面再在奇数位上按顺序放置。


---

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k;
ll a[100010],ans[100010];
int main(){
	cin>>n;
	for(ll i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	ll pos1=1,pos2=n/2+1;
	for(ll i=1;i<=n;i++){
		if(i%2==0)ans[i]=a[pos1++];
		else ans[i]=a[pos2++];
	}
	for(ll i=1;i<=n;i++)
		if(ans[i]<ans[i-1]&&ans[i]<ans[i+1])k++;
	cout<<k<<"\n";
	for(ll i=1;i<=n;i++)cout<<ans[i]<<" ";
	return 0;
}
```
最后，希望本篇题解对你有所帮助，感谢观看。
### 望管理员通过。

---

## 作者：Tjaweiof (赞：1)

# CF1419D2 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1419D2)

因为不可能同时满足 $a_i<a_{i+1}$ 和 $a_{i+1}<a_i$，所以相邻的两个不可能同时被 Sage 买。由此可以得出每隔一个放一个比较便宜的商品是最优的，于是我们可以先将商品按价格排序，然后从小到大依次放在编号为偶数的位置，然后再放在编号为奇数的位置。最后统计一下 Sage 会买多少个商品即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100001], b[100001], cnt, ans;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	for (int i = 2; i <= n; i += 2){
		b[i] = a[++cnt];
	}
	for (int i = 1; i <= n; i += 2){
		b[i] = a[++cnt];
	}
	for (int i = 2; i < n; i++){
		if (b[i - 1] > b[i] && b[i] < b[i - 1]){
			ans++;
		}
	}
	cout << ans << endl;
	for (int i = 1; i <= n; i++){
		cout << b[i] << " ";
	}
	return 0;
}

```

---

## 作者：ql12345 (赞：1)

#### [弱化版](https://www.luogu.com.cn/problem/CF1419D1)

#### [加强版](https://www.luogu.com.cn/problem/CF1419D2)

如果想做出加强版的话，建议不要看弱化版浪费时间，因为弱化版错误贪心也能过 ~~别问我怎么知道的~~

### 题意：

只有1组数据，一个n表示长度，n个数字[1,1e9]，要求任意排列n个数字，使得“严格小于左右两个数字的数字”个数最大

输出最大个数 和 排列， spj

### Solution：

先看样例：

```
3
3 1 4 2 4 2 5
```

~~是不是什么都没看出~~ ~~你看了结论就咋看咋觉得不应该看不出了~~

#### 结论（~~自己找~~）：

```
3 # 4 # 4 # 5
# 1 # 2 # 2 #
```

代码就不难写啦~

#### 简单口胡一下为什么是对的：

1. 首先分出“上下”两行，即“胜者组”跟“败者组”，败者组个数即为答案

这样为什么优呢？

首先明确：胜者一定大于等于败者

假如最后答案不是这样的，让一个“放错位置的胜者组”和一个“放错位置的败者组”交换位置：

之前败者能干的事，胜者也能，所以败者夹的数仍有贡献

胜者两边的数比它大，一定也比败者大，所以之前胜者的贡献也不会减少

2. 再让小的胜者匹配小的败者，大的胜者匹配大的败者

假如将这样得到的方案改动一下：

如果能力小的人有一件事做不了（证明这个“败者”和它一样大），而能力大的胜者可以做，

能力大的人一定严格大于所有败者，所以将它们换位置，能力大的人能做的事没有变多，能力小的人能做的事也没有变多

### Code:

```cpp
int n,a[N],b[N],ans,j;
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)if(!(i&1))b[i]=a[++j];
	for(int i=1;i<=n;++i)if(i&1)b[i]=a[++j];
	for(int i=2;i<n;++i)if(b[i]<b[i-1]&&b[i]<b[i+1])++ans;
	cout<<ans<<endl;
	for(int i=1;i<=n;++i)cout<<b[i]<<' ';
}
```

你可以去交弱化版~~随便AC~~啦！

---

## 作者：封禁用户 (赞：0)

# CF1419D2 Sage's Birthday (hard version) 题解

## 思路

- 这是一道构造题，需要构造波浪形的商品价格。

- 显然这是一道贪心 ~~（非常适合非常贪心的某人，我也不说是谁）~~。

- 贪心的思路
	- 对于奇数位，放价格高的商品。
   - 对于偶数位，放价格低的商品。

- 最后再扫一遍，计算出实际购买商品个数，因为是严格小于，所以不能直接输出 $\lfloor \frac{n}{2} \rfloor$ 。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
//#define double long double
#define il inline
#define endl '\n'
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define abs(x) (x<0?-x:x)
#define fast_io ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const int maxn=1e5+1;
int n,a[maxn],ans[maxn];

signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	fast_io;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	int l1=1,l2=n/2+1;
	for(int i=1;i<=n;i++)
	{
		if(i%2)
		{
			ans[i]=a[l2++];
		}
		else
		{
			ans[i]=a[l1++];
		}
	}
	int sum=0;
	for(int i=2;i<n;i++)
	{
		if(ans[i-1]>ans[i]&&ans[i]<ans[i+1])
		{
			sum++;
		}
	}
	cout<<sum<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<ans[i]<<' ';
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：qiuzijin2026 (赞：0)

# Sage's Birthday (hard version)

## [题面](https://www.luogu.com.cn/problem/CF1419D2)

## 思路

一道构造题。

既然 Sage 只会买价格比左右两边商品价格都严格低的商品，而且他不会买最左边和最右边的商品，那么我们只需排个序后让奇数位上的尽量小，偶数位上的尽量大即可。

因为 Sage 不会买价格与左右两边相等的商品，所以最后扫一遍判断一下有几个价格比左右两边商品价格都严格低的商品即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[100005]; 
int l1,l2;
int s;
int ans[100005];
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	l1=1;
	l2=n/2+1;
	for(int i=1;i<=n;i++) 
		if(i%2==1){
			ans[i]=a[l2];
			l2++;
		}
		else{
			ans[i]=a[l1];
			l1++;
		}
	for(int i=1;i<=n;i++) 
		if(ans[i]<ans[i-1]&&ans[i]<ans[i+1])
			s++;
	printf("%d\n",s);
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	return 0;
}

```

---

## 作者：Wf_yjqd (赞：0)

我愿称之为构造基础题。

------------

显然，最优情况下每隔一个出现一个答案。

考虑贪心，从小到大排序。

让后 $\lceil\frac{n}{2}\rceil$ 个隔开前 $\lfloor\frac{n}{2}\rfloor$ 个。

为了让相邻的相等的浪费情况尽可能少，用后面剩下的最小的两个隔开前面剩下的最小的一个。

处理一些细节就好了。

------------

没人看的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+84;
int n,a[maxn],ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=2;i<n;i+=2)
        ans+=a[i/2]<a[n/2+i/2];
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        printf("%d ",a[i/2+(i&1?n/2+1:0)]);
    return 0;
}
```


---

## 作者：onglu (赞：0)

## D. Sage's Birthday  
### 题目大意   
一个数可以被选择当且仅当这个数不是第$1$或第$n$个数并且这个数两边的数都比他大。  
然后有一列数，你要给他们调换顺序，使得被选择的数最多。  
### 思路   
显然最好的情况就是一大一小一大一小。  
因为假如把数列化成图像，那么一个凹型只有最底部的那个元素贡献答案。  
于是我们看看能不能直接这样构造，排序，然后偶数位置的排最小的那些数，奇数位置排最大的那些数。  
手算一下发现可以。  
注意答案并不是$(n-1)/2$因为可能会有一下数是一样的，然后像$555$这样三个数就不计算贡献。  
排列完数后统计答案输出即可。  
### 代码  
```cpp
#include <bits/stdc++.h>
#define Mid ((l + r) >> 1)
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define ll long long
#define ull unsigned long long
#define FILL ""
using namespace std;
const int N = 0, M = 0;
int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-')f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return num * f;
}
int n, a[100009], vis[100009];
int main()
{
	//freopen(FILL".in", "r", stdin);
	//freopen(FILL".out", "w", stdout);
	n = read();
	for(int i = 1; i <= n; i++)a[i] = read();
	sort(a + 1, a + 1 + n);
	int now = 1;
	for(int i = 2; i <= n; i += 2)
		vis[i] = a[now++];
	for(int i = 1; i <= n; i += 2)
		vis[i] = a[now++];
	int ans = 0;
	for(int i = 2; i < n; i++){
		if(vis[i] < vis[i - 1] && vis[i] < vis[i + 1])ans++;
	}
	printf("%d\n",ans);
	for(int i = 1; i <= n; i++){
		printf("%d ",vis[i]);
	}
	printf("\n");
	return 0;
}
```

---

## 作者：king_xbz (赞：0)

不难的构造题，此题为困难版。然而好像没有详细讲述如何构造的题解，我来发一发，造福人类（doge）。
# 题意简述
当i位置价格比i-1位置和i+1位置低时，就买i位置物品，**物品价格可能会相同**，求最多能买多少个
# 思路分析
很显然，我们想让有最多的“山”字序列（中间低，两边高）。这样即为最优解。

那么，如何构造呢？

我们可以考虑进行排序，把前$i/2$小的从小到大放在偶数位上，剩下的从小到大依次放到奇数位上，这样一定满足“山”字序列最多。

注意这里需要满足严格的小于，所以形如`1 1 1`这样的序列是不被Sage认可的哟！
# 代码实现
注意以上几点，AC不成问题！

代码：
```cpp
int main()
{
	int n;
	cin>>n;
	for(fint i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+n+1);
	int cnt=0;
	for(fint i=2;i<=n;i+=2)
	s[i]=a[++cnt];
	for(fint i=1;i<=n;i+=2)
	s[i]=a[++cnt];
	int ans=0;
	for(fint i=1;i<=n;i++)
	if(s[i]<s[i-1]&&s[i]<s[i+1])
	ans++;
	cout<<ans<<endl;
	for(fint i=1;i<=n;i++)
	cout<<s[i]<<" ";
	return 0;
}
```
祝大家AC愉快哦！

---

