# Kindergarten

## 题目描述

In a kindergarten, the children are being divided into groups. The teacher put the children in a line and associated each child with his or her integer charisma value. Each child should go to exactly one group. Each group should be a nonempty segment of consecutive children of a line. A group's sociability is the maximum difference of charisma of two children in the group (in particular, if the group consists of one child, its sociability equals a zero).

The teacher wants to divide the children into some number of groups in such way that the total sociability of the groups is maximum. Help him find this value.

## 说明/提示

In the first test sample one of the possible variants of an division is following: the first three children form a group with sociability 2, and the two remaining children form a group with sociability 1.

In the second test sample any division leads to the same result, the sociability will be equal to 0 in each group.

## 样例 #1

### 输入

```
5
1 2 3 1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
3 3 3
```

### 输出

```
0
```

# 题解

## 作者：肖恩Sean (赞：11)

### 贪心

首先证明：所有串都是单调的，否则的话，将其分成若干个单调的串的结果一定比原结果更优

既然所有串都是单调的，那么只需要贪心处理两串相交的部分分给哪个串

数组转移如下：
- 如果 a[i-2],a[i-1],a[i]都是单调的，
- f[i]=f[i-1]+abs(a[i]-a[i-1])
- 否则，f[i]=max(f[i-1],f[i-2]+abs(a[i]-a[i-1])

另：数据范围n<=10^6,a[i]<=10^9
```cpp
#include<bits/stdc++.h>
#define LL long long
#define For(i,l,r) for(int i=(l);i<=(r);++i)
#define ReFor(i,l,r) for(int i=(l);i>=(r);--i)
using namespace std;
const int N=1e6+9;
int n,a[N];
LL f[N];
int read(){
	int x=0,f=1;char c;
	while(c<'0'||c>'9'){if(c=='-') f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
bool is_mon(int i){
	if(a[i]>a[i-1]&&a[i-1]>a[i-2]) return true;
	if(a[i]<a[i-1]&&a[i-1]<a[i-2]) return true;
	return false;
}
int main(){
	n=read();
	For(i,1,n) a[i]=read();
	f[1]=0;f[2]=abs(a[2]-a[1]);
	For(i,3,n){
		if(is_mon(i)) f[i]=f[i-1]+abs(a[i]-a[i-1]);
		else f[i]=max(f[i-1],f[i-2]+abs(a[i]-a[i-1]));
	}
	printf("%lld\n",f[n]);
	return 0;
}

```

---

## 作者：Miraik (赞：7)

**贪心+DP。**

每一段的值，定义为这一段数中**最大值与最小值的差**。

如果分出的串不是**单调递增/递减**的话，将该串分为若干**单调递增/递减**的串总是更好的选择。

以样例为例：

$\{ 1,2,3,1,2 \}$

显然这串数的值为 $3-1=2$。

我们把他们分为2个单调递增串：

$\{ 1,2,3 \}$

$\{ 1,2 \}$

这两串数的和为 $(3-1)+(2-1)=3$。

因此，将这串数分为若干单调串是最优的选择。

这样这题就简单了。

所有串保证单调，因此只用考虑峰顶和峰底。

设$f_{i}$为前$i$个数组成的最大值，$j$为上一个峰顶/峰底的下标。

可得转移方程

$f_{i}=\max(f_{j}+|a_{i}-a_{j+1}|,f_{j-1}+|a_{j}-a_{i}|)$

**记得开```long long```！**

完整代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){//快读，本题数据较大
	ll x=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
ll n,a[1000005],f[1000005],j=1;
inline ll _max(ll x,ll y){return x>y?x:y;}
inline ll _abs(ll x){return x>0?x:-x;}
bool h(ll x){//峰顶或峰底
	return (a[x]>=a[x-1]&&a[x]>=a[x+1])||(a[x]<=a[x-1]&&a[x]<=a[x+1]);
}
int main(){
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();//读入
	for(ll i=2;i<=n;i++)f[i]=_max(f[j]+_abs(a[i]-a[j+1]),f[j-1]+_abs(a[j]-a[i])),j=h(i)?i:j;//转移
	printf("%lld\n",f[n]);//输出
	return 0;
}

```


---

## 作者：ln001 (赞：4)

总体思路：贪心 + dp

~~从MLE大佬文章过来的。~~

不考虑数据范围，能够想到 $O(n^2)$ 的暴力 dp，肯定是不能通过此题的，接下来思考结果为何时答案最优。

答案为极差之和，答案最大值时极差最大，极差只与一个序列中的最大最小值有关，所以我们需要尽量让每个偏小数对最小值存在贡献，让每个偏大数对最大数存在贡献，也就是**尽量减少每个子串被包含的情况**。
具体的就是**将序列划分为单调的几段**，因为这样能最大化最值对答案的贡献。

下面借分类讨论**简单解释**一下。

###  1.原序列单调递增
此时无论从何处切开，最终极差和仍不变。

###  2.原序列单调递增
与上一种情况同理。
###  3.原序列先降后增
先上个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dc6no1i6.png)

我们钦定极低点为 $k$，序列的左右端点分别为         $l,r$。

若不进行操作，答案为 $\max(l,r)-k$ 。

若在 $c$ 处操作，不妨设 $l<c<k$ ，则答案为 $l-c+r-k$，若 $c$ 位于右侧也同理。

若恰在 $k$ 操作，则答案为 $l+r-2k$。

不等式简单传递一下即可得证。

###  4.原序列先增后降
与上一种情况同理。

---
其他情况都可以~~应该~~转化为以上情况。（当然只是证明思想可以转化，最终答案肯定不是简单的拼接）

有了这些就可以优化 dp 了，设 $f_i$ 为前 $i$ 个数组成的最大值，转移中的 $j$ 为上一个极点的下标。

转移，取 $max$ 是因为极点的最终归属不确定：
$$ f_i=\max(f_j+\lvert a_i-a_{j+1} \rvert ,f_{j-1}+\lvert a_j-a_i\rvert)$$

# Code
还有一个注意事项放在代码里了。
```cpp
// Problem: Kindergarten
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF484D
// Time Limit: 2000 ms
// Start Time:2024-05-03 15:29:20
//
// Powered by CP Editor (https://cpeditor.org)

#ifndef LOCAL
#include <bits/stdc++.h>
#define csf std::cerr.setstate(std::ios_base::failbit)
#define db(x)
#else
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#define db(x) cerr << __FUNCTION__ << " L" << __LINE__ << " " << #x " = " << (x) << endl
#define csf
#endif
#define ll long long
#define f(x, y, z) for (ll x = (y); x <= (z); x++)
using namespace std;
inline ll read();
const ll INF = 0x3f3f3f3f3f3f3f3f, N = 1e6 + 10;
ll f[N]; // 前i个数最大答案是多少
ll n;
ll a[N];
ll bfg = 1;

signed main()
{
    csf;
    n = read();
    f(i, 1, n) cin >> a[i];
    f[0] = 0;
    f[1] = 0;
    f(i, 2, n) // 贪心可知划分出的序列为单调
    {
        ll x = f[bfg] + abs(a[i] - a[bfg + 1]);
        ll y = f[bfg - 1] + abs(a[i] - a[bfg]);
        f[i] = max(x, y); // 5 3 1 2 3
        if (a[i - 1] >= a[i] && a[i + 1] >= a[i])
            bfg = i;
        else if (a[i - 1] <= a[i] && a[i + 1] <= a[i])
            bfg = i;
        // 此处判断转折点需带=，因为若有多个相同的点，可缩为两个，归到不同集合，若不带等号，当相同元素恰好有两个时，dfg=前者，此时通过转移方程无法把他们划分到两个集合中
    }
    f(i, 1, n) db(f[i]);
    cout << f[n] << endl;
    return 0;
}
inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

```

---

## 作者：HHH6666666666 (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF484D)

有点水的 DP。

不难发现一定存在最优划分满足其中每一个区间的左右端点均为最值。即对于其中划分的任意一个区间 $[l,r]$，均满足 $\min(a_l,a_r) = \min(a_l,a_{l+1},...,a_r),
\max(a_l,a_r)=\max(a_l,a_{l+1},...,a_r)$。

证明：若某一个区间左端点不为区间最值，则将其划分入该区间左侧的区间，答案不会更劣。右端点同理。

这样一来，设 $f_i$ 表示将子段 $[1,i]$ 划分完毕后的最大结果。两个转移方程显然：

1. $f_i=\max\limits_{j=1}^{i-1}(f_j+a_{j+1}-a_i) = \max\limits_{j=1}^{i-1}(f_j+a_{j+1})-a_i$。

1. $f_i=\max\limits_{j=1}^{i-1}(f_j-a_{j+1}+a_i) = \max\limits_{j=1}^{i-1}(f_j-a_{j+1})+a_i$。

不用担心具体转移时两个端点是否为区间最值，因为根据刚才的结论，当端点不是最值时转移不是最优的，也就不会影响答案。

如何优化这个 DP？只要从左到右扫描过程中记录式子里的 $\max(f_j-a_{j+1})$ 与 $\max(f_j+a_{j+1})$ 即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int MAXN = 1e6 + 10;

int n;
int a[MAXN];

int main() {
    ios:: sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll amx = a[1], amn = -a[1];
    for (int i = 1; i < n; ++i) {
        ll t = max(amx - a[i], amn + a[i]);
        ll tmx = t + a[i + 1];
        ll tmn = t - a[i + 1];
        amx = max(amx, tmx), amn = max(amn, tmn);
    }
    cout << max(amx - a[n], amn + a[n]) << endl;
    return 0;
}

```




---

## 作者：fade_away (赞：2)

看了一下题解大家好像都是贪心，其实也可以直接 dp 。

事实上题意可以转化为：从 $a_1...a_n$ 中依次选出 $2m$ 个数 $b_1,b_2...b_{2m}$，使得 $\sum_{i=1}^m b_{2i}-b_{2i-1}$ 最大。

于是我们就可以直接令 $f_i$ 为前 $i$ 个数，$a_i$ 是 $b_{2k}$ 的最优答案。

转移就是 $f_{i}=\max_{j=1}^{i-1}g_{j-1}+|a_i-a_j|$ 。

其中 $g_j=\min_{t=1}^{j}f_t$。

我们可以把 $|a_i-a_j|$ 拆成 $max(a_i-a_j,a_j-a_i)$ 。于是就有： 
$$
f_i = max\{\max_{j=1}^{i-1}(g_{j-1}-a_j)+a_i, \max_{j=1}^{i-1}(g_{j-1}+a_j)-a_i\}
$$

然后我们分别维护 $g_i,\max_{j=1}^{i-1}(g_{j-1}-a_j),\max_{j=1}^{i-1}(g_{j-1}+a_j)$ 即可 $O(n)$ 求出答案。

```cpp
ll a[MAXN], f[MAXN];
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	int n;
	read(n);
	for (int i = 1; i <= n ; ++ i) read(a[i]);

	ll mx = 0, x = -a[1], y = a[1];
	for (int i = 2; i <= n ; ++ i) {
		f[i] = max(x + a[i], y - a[i]);
		upmax(mx, f[i - 1]);
		upmax(x, mx - a[i]);
		upmax(y, mx + a[i]);
	}
	print(max(mx, f[n]));
	return 0;
}
```


---

## 作者：Msents (赞：2)

考虑暴力 DP。

转移方程：

$$f_i=\max_{j=0}^{i-1}(f_j+\max_{k=j+1}^{i}(a_k)-\min_{k=j+1}^{i}(a_k))$$

直接做是 $O(n^2)$ 的，考虑优化转移。可以发现 $\max_{k=j+1}^{i}(a_k)$ 和 $\min_{k=j+1}^{i}(a_k)$ 这两项能用单调栈均摊 $O(1)$ 维护，于是剩下的取最大值这一过程用线段树加速就完了。

时间复杂度 $O(n \log n)$，完全不要脑子，但很卡常，建议吸氧且标准开最新的。

码：

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MaxN=1000000;
int n,a[MaxN+1];
struct Node{
	int max,add;
	int l,r;
}tree[MaxN*4+1];
inline int Left(int u){return u<<1;}
inline int Right(int u){return u<<1|1;}
void Build(int u,int l,int r){
	tree[u].l=l,tree[u].r=r;
	if(l==r)return;
	int mid=(l+r)/2;
	Build(Left(u),l,mid);
	Build(Right(u),mid+1,r);
}
inline void PushDown(int u){
	if(tree[u].add){
		tree[Left(u)].add+=tree[u].add;
		tree[Left(u)].max+=tree[u].add;
		tree[Right(u)].add+=tree[u].add;
		tree[Right(u)].max+=tree[u].add;
		tree[u].add=0;
	}
}
inline void PushUp(int u){tree[u].max=max(tree[Left(u)].max,tree[Right(u)].max);}
void Add(int u,int l,int r,int val){
	if(r<tree[u].l||tree[u].r<l)return;
	if(l<=tree[u].l&&tree[u].r<=r){
		tree[u].add+=val;
		tree[u].max+=val;
		return;
	}
	PushDown(u);
	Add(Left(u),l,r,val);
	Add(Right(u),l,r,val);
	PushUp(u);
}
inline void Solve(){
	cin>>n;
	vector<int>stkMax,stkMin;
	Build(1,0,n);
	stkMax.push_back(1),stkMin.push_back(1);
	for(int i=1;i<=n;i++){
		cin>>a[i];
		while(stkMax.size()&&a[stkMax.back()]<a[i]){
			int t=stkMax.back();
			stkMax.pop_back();
			Add(1,stkMax.size()?stkMax.back()+1:0,t,-a[t]);
		}
		Add(1,stkMax.size()?stkMax.back()+1:0,i,a[i]);
		stkMax.push_back(i);
		while(stkMin.size()&&a[stkMin.back()]>a[i]){
			int t=stkMin.back();
			stkMin.pop_back();
			Add(1,stkMin.size()?stkMin.back()+1:0,t,a[t]);
		}
		Add(1,stkMin.size()?stkMin.back()+1:0,i,-a[i]);
		stkMin.push_back(i);
		Add(1,i+1,i+1,tree[1].max);
	}
	cout<<tree[1].max;
}
#undef int
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	Solve();
	return 0;
}
```

---

## 作者：傅思维666 (赞：2)

## 题解：

正解：贪心+DP。

贪心策略：一定是单调连续串（递增递减都可以）使得最终加出来的和最优。否则都可以拆成单调串来处理。

然后第一感觉不需要DP，直接模拟然后累加就可以。但是发现不太对劲，因为对于序列的峰值和谷值来讲，我们不知道把它归属于前面最优还是后面更优。所以需要一个DP来保证每次决策的局部最优性，从而递推得出全局最优性。

显然，需要记录前方的峰值或谷值的位置，这里记为pos。

然后设$dp[i]$表示前i个数所获得的最大价值。

那么转移方程就是：
$$
dp[i]=\max(dp[pos]+|a[i]-a[pos+1]|,dp[pos-1]+|a[pos]-a[i]|)
$$
也就是把pos值分别归属于前面的串和自己的贡献取较大。

然后再更新pos值即可。更新pos值的过程只需要用当前数前后各一个数来判就可以。

代码：

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=1e6+6;
ll n,a[maxn],dp[maxn],pos=1;
bool check(ll x)
{
	return (a[x]>=a[x-1]&&a[x]>=a[x+1])||(a[x]<=a[x-1]&&a[x]<=a[x+1]);
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int i=2;i<=n;i++)
	{
		dp[i]=max(dp[pos]+abs(a[i]-a[pos+1]),dp[pos-1]+abs(a[pos]-a[i]));
		pos=check(i)?i:pos;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
```



---

## 作者：251Sec (赞：1)

为啥题解区没有这个做法来着。

看到最大化极差，套路地，直接改成分段后在每一段选两个数（可以一样），然后一个数获得正的贡献，一个数获得负的贡献，问分段的最大贡献和。直接 DP 设 $f(i,0/1,0/1)$，代表给前 $i$ 个数分段，目前最后一段是否选出了正贡献，是否选出了负贡献，直接转移即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll a[1000005], f[1000005][2][2];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	memset(f, 0xc0, sizeof(f)), f[0][0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 2; y++) {
				f[i][x][y] = f[i - 1][x][y];
			}
		}
		f[i][0][0] = max(f[i][0][0], f[i - 1][1][1]);
		for (int y = 0; y < 2; y++) {
			f[i][1][y] = max(f[i][1][y], f[i][0][y] + a[i]);
		}
		for (int x = 0; x < 2; x++) {
			f[i][x][1] = max(f[i][x][1], f[i][x][0] - a[i]);
		}
	}
	printf("%lld\n", f[n][1][1]);
	return 0;
}
```

---

## 作者：wrzSama (赞：1)

## 题意

给定一个长度为 $n$ 的序列 $a$，将其分成任意个连续子段，定义一个子段的价值为其中元素的最大值减去最小值，问所有子段的价值的和的最大值。

## 思路

设 $dp_i$ 表示将前 $i$ 个元素分成任意子段的所有子段的价值的和的最大值，那么$dp_i=max(dp_{j-1}+getmax(j,i)-getmin(j,i))$，$getmax(j,i)$ 表示区间 $[j,i]$ 中所有元素的最大值，$getmin(j,i)$ 表示区间 $[j,i]$ 中所有元素的最小值。设 $l$ 表示使得 $dp_i$ 取得最大值的 $j$，即最优决策点，如果 $l$ 有多种取值那么就找最大的 $l$。那么随着 $i$ 的增大，$l$ 单调不降，而且 $l$ 一定是区间 $[l,i]$ 中最小值和最大值的位置中更靠前的。下面我们需要考虑在那些情况下，$l$ 的值会发生改变。我们记录区间中最小值和最大值即其位置，当新加进来一个数 $a_i$ 时，首先要先用 $a_i$ 更新区间的最值。接着，尝试用 $a_i$ 代替原本的 $l$ 位置上的最值，$l$ 移到其后另一个最值的位置。如果 $dp_i$ 在此时的值不小于从原本的 $l$ 转移过来的值，那么就可以将 $l$ 的位置往后移到另一个最值的位置。最后我们再尝试用 $a_i$ 同时代替最大值和最小值，即 $dp_i$ 从 $dp_{i-1}$ 转移，如果此时的 $dp_i$ 的值不小于原来 $dp_i$ 的值，则说明可行，令 $l=i$。最后从 $1$ 到 $n$ 依次求出所有 $dp$ 的值，输出 $dp_n$ 即为答案。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
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
inline void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n;
ll dp[1000001];
int main()
{
	n=read();
	int mina=1e9,maxa=-1e9,minp=1,maxp=1;
	for(int i=1;i<=n;++i)
	{
		int a=read();
		if(a>maxa)
		{
			maxa=a;
			maxp=i;
		}
		if(a<mina)
		{
			mina=a;
			minp=i;
		}
		if(minp<maxp&&dp[maxp-1]+maxa-a>=dp[minp-1]+maxa-mina)
		{
			mina=a;
			minp=i;
		}
		if(maxp<minp&&dp[minp-1]+a-mina>=dp[maxp-1]+maxa-mina)
		{
			maxa=a;
			maxp=i;
		}
		if(dp[i-1]>=dp[min(maxp,minp)-1]+maxa-mina)
		{
			maxa=mina=a;
			minp=maxp=i;
		}
		dp[i]=dp[min(maxp,minp)-1]+maxa-mina;
	}
	write(dp[n]);
	return 0;
}
```


---

## 作者：love_luke (赞：1)

这道题让本蒟蒻很心累啊。。。

首先是思路。我们可以知道，每个被分隔的区间的端点就是这个区间的两个极值。也就是说，每个区间都是单增或单减的。如果这个区间不满足单调性，那它必然可以拆成几个单调区间，其值之和必大于原区间。在此不再赘述。

那问题就简单了。我们只要找出极值点，就方便更新了。

状态转移方程：
```cpp
f[i]=max(f[lin]+abs(a[i]-a[lin+1]),f[lin-1]+abs(a[i]-a[lin]));
```
其中lin所代表的即为极值下标。

根据以上分析，可以编出如下程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001],f[1000001];
int main()
{
    int n,i,lin=1;
    cin>>n;
    for (i=1;i<=n;++i)
    {
        cin>>a[i];
    }
    for (i=2;i<=n;++i)
    {
        f[i]=max(f[lin]+abs(a[i]-a[lin+1]),f[lin-1]+abs(a[i]-a[lin]));
        if (((a[i]>=a[i-1])&&(a[i]>=a[i+1]))||((a[i]<=a[i-1])&&(a[i]<=a[i+1])))//更新极值位置
        {
            lin=i;
        }
    }
    cout<<f[n];
    return 0;
}
```
信心满满的我把这份程序交了上去，结果。。。T了！！！（为自己偷懒打cincout而羞愧）

改完再交，结果。。。W了！！！再回头看一眼数据范围，好像要开long long。。。（是我蠢）

这道题让我认识到了我的缺点，于是决定写篇题解纪念一下（手动滑稽）

AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000001],f[1000001];
int main()
{
	int n,i,lin=1;
	cin>>n;
	for (i=1;i<=n;++i)
	{
		scanf("%lld",&a[i]);
	}
	for (i=2;i<=n;++i)
	{
		f[i]=max(f[lin]+abs(a[i]-a[lin+1]),f[lin-1]+abs(a[i]-a[lin]));
		if (((a[i]>=a[i-1])&&(a[i]>=a[i+1]))||((a[i]<=a[i-1])&&(a[i]<=a[i+1])))
		{
			lin=i;
		}
	}
	printf("%lld",f[n]);
	return 0;
}
```


---

## 作者：_SunLig (赞：0)

# CF484D Kindergarten 题解

设 $dp_i$ 表示将前缀 $i$ 划分成若干段的最大答案。

有转移方程 $dp_i=\max_{j=0}^{i-1}(dp_j+\max_{k=j+1}^ia_k-\min_{k=j+1}^ia_k)$。

注意到这个式子可以写成 $dp_i=\max_{j=0}^{i-1}(dp_j+|a_i-a_{j+1}|)$，因为如果 $a_i$ 和 $a_{j+1}$ 不是最值的话，从最值处将区间劈开显然更优。

进一步，这个式子又可以写成 $dp_i=\max_{j=0}^{i-1}\max(dp_j+a_i-a_{j+1},dp_j-a_i+a_{j+1})$。

转移是简单的，时间复杂度 $O(n)$。

---

## 作者：_lgh_ (赞：0)

看到 $n\le 10^6$，考虑 dp。

设 $f_i$ 表示前 $i$ 个位置的权值，则有转移方程 $f_i=f_j+|a_i-a_j|(j<i)$。

观察极差的性质，容易注意到将序列划分为若干段单调序列后，每个位置从上一个单调序列的末尾或者这个单调序列的开头的转移一定是不劣的。 因此只需要记录上一个单调序列的末尾即可。

时间复杂度 $O(n)$。

```cpp
int main() {
	int n; cin>>n;
	vector<int>a(n+1);
	vector<i64>f(n+1);
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=2,lst=1; i<=n; i++) {
		f[i]=max(f[lst]+abs(a[i]-a[lst+1]),f[lst-1]+abs(a[i]-a[lst]));
		if(a[i]>=a[i-1]&&a[i]>=a[i+1]) lst=i;
		else if(a[i]<=a[i-1]&&a[i]<=a[i+1]) lst=i;
	}
	cout<<f[n]<<'\n';
    return 0;
}
```

---

## 作者：Hot_tear (赞：0)

题意不再赘述。

考虑 dp ：不难列出一个转移方程：记 $f_i$ 为以 $i$ 为右端点 $1\sim i$ 整个序列的最大价值，那么可以得出 $f_i=\mathrm{max}_{j<i}(f_j+\max_{k=i}^ja_k-\mathrm{min}_{k=i}^ja_k)$ ，但是这个式子无法用线段树等一系列数据结构化简到比 $\mathrm{O}(n^2)$ 更优秀的算法了

考虑贪心：每一个非严格递增/非严格递减的序列一定可以拆成若干严格递增/递减的序列，并且价值是最优的

关于这样贪心证明：考虑左右端点若非此序列唯一最值，那么将左边的数让给左边的序列一定不会更劣，因为答案与它无关，同理可得右端点也无影响，最后得到的就是一些严格递增/递减的序列，这样答案是最优的

那么根据此最优性，可以得出最优划分方法每一块的左右端点为最值，即可以得出 $f_i=\mathrm{max}_{j<i}(f_j+|a_i-a_{j+1}|)$

$f_i=\mathrm{max}_{j<i}(f_j+|a_i-a_{j+1}|)$，此时根据上述最优性原则，那么答案一定是可以找到的，实质就是减少了大量无用状态的枚举

因为并不知道绝对值内部的正负性，那么需要分类讨论，即

$f_i=\mathrm{max}_{j<i}(f_j+a_i-a_{j+1})$ 和         $f_i=\mathrm{max}_{j<i}(f_j+a_{j+1}-a_i)$

也就是

$f_i=\mathrm{max}_{j<i}(f_j-a_{j+1})+a_i$ 和         $f_i=\mathrm{max}_{j<i}(f_j+a_{j+1})-a_i$

括号里的东西分别用一个线段树在 $j$ 点上维护就好了，查询的时候直接拿过来两棵线段树的根即可，在写代码的时候因为只需要用到修改操作并且修改操作本质一样，那么这个时候直接把两棵线段树的数组地址传到函数里分别处理，就可以不用再写一遍了

关于时间复杂度： $\mathrm{O}(n\log n)$

Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for(ll i=a;i<=b;i++)
#define R(i,a,b) for(ll i=a;i>=b;i--)
#define sc(a) scanf("%lld",&a)
#define ps(a) printf("%lld ",a)
#define pn(a) printf("%lld\n",a)
using namespace std;
const ll N=3e6+7;
ll n,a[N],t1[N],t2[N],f[N];
inline void pushup(ll k){
	t1[k]=max(t1[k<<1],t1[k<<1|1]);
	t2[k]=max(t2[k<<1],t2[k<<1|1]);
}
inline void build_tree(ll l,ll r,ll k){
	if(l==r){
		t1[k]=t2[k]=-1e18;
		return ;
	}
	ll mid=(l+r)>>1;
	build_tree(l,mid,k<<1);
	build_tree(mid+1,r,k<<1|1);
	pushup(k);
}
inline ll query(ll *t,ll now_l,ll now_r,ll l,ll r,ll k){
	if(l<=now_l&&r>=now_r){
		return t[k];
	}
	ll mid=(now_l+now_r)>>1,ans=-1e18;
	if(l<=mid) ans=max(ans,query(t,now_l,mid,l,r,k<<1));
	if(r>mid) ans=max(ans,query(t,mid+1,now_r,l,r,k<<1|1));
	return ans;
}
inline void update(ll *t,ll now_l,ll now_r,ll l,ll r,ll k,ll q){
	if(l<=now_l&&r>=now_r){
		t[k]=q;
		return ;
	}
	ll mid=(now_l+now_r)>>1;
	if(l<=mid) update(t,now_l,mid,l,r,k<<1,q);
	if(r>mid) update(t,mid+1,now_r,l,r,k<<1|1,q);
	pushup(k);
}
int main(){
	sc(n);
	F(i,1,n) sc(a[i]);
	build_tree(0,n,1);
	F(i,0,n){
		f[i]=max(t1[1]+a[i],t2[1]-a[i]);
		f[i]=max(f[i],0ll);
		update(t1,0,n,i,i,1,f[i]-a[i+1]);
		update(t2,0,n,i,i,1,f[i]+a[i+1]);
	}
	pn(f[n]);
	return 0;
}

#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for(ll i=a;i<=b;i++)
#define R(i,a,b) for(ll i=a;i>=b;i--)
#define sc(a) scanf("%lld",&a)
#define ps(a) printf("%lld ",a)
#define pn(a) printf("%lld\n",a)
using namespace std;
const ll N=3e6+7;
ll n,a[N],t1[N],t2[N],f[N];
inline void pushup(ll k){
	t1[k]=max(t1[k<<1],t1[k<<1|1]);
	t2[k]=max(t2[k<<1],t2[k<<1|1]);
}
inline void build_tree(ll l,ll r,ll k){
	if(l==r){
		t1[k]=t2[k]=-1e18;
		return ;
	}
	ll mid=(l+r)>>1;
	build_tree(l,mid,k<<1);
	build_tree(mid+1,r,k<<1|1);
	pushup(k);
}
inline ll query(ll *t,ll now_l,ll now_r,ll l,ll r,ll k){
	if(l<=now_l&&r>=now_r){
		return t[k];
	}
	ll mid=(now_l+now_r)>>1,ans=-1e18;
	if(l<=mid) ans=max(ans,query(t,now_l,mid,l,r,k<<1));
	if(r>mid) ans=max(ans,query(t,mid+1,now_r,l,r,k<<1|1));
	return ans;
}
inline void update(ll *t,ll now_l,ll now_r,ll l,ll r,ll k,ll q){
	if(l<=now_l&&r>=now_r){
		t[k]=q;
		return ;
	}
	ll mid=(now_l+now_r)>>1;
	if(l<=mid) update(t,now_l,mid,l,r,k<<1,q);
	if(r>mid) update(t,mid+1,now_r,l,r,k<<1|1,q);
	pushup(k);
}
int main(){
	sc(n);
	F(i,1,n) sc(a[i]);
	build_tree(0,n,1);
	F(i,0,n){
		f[i]=max(t1[1]+a[i],t2[1]-a[i]);
		f[i]=max(f[i],0ll);
		update(t1,0,n,i,i,1,f[i]-a[i+1]);
		update(t2,0,n,i,i,1,f[i]+a[i+1]);
	}
	pn(f[n]);
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

~~这道题贪心和 DP 这么简单吗？！~~

------------
注：
1. 本题由于比较简单，笔者不会将证明和解析讲得十分详细，望周知！

2. 本题解似乎与[大佬题解](https://www.luogu.com.cn/blog/jdoiFSW/solution-cf484d)撞山，望大佬理解（但思路是笔者自己一上午想的）！

------------
## 大致思路：
本题一看，就和贪心脱不了干系，由于题目要求找出一种方案将一整个数列 $a$ 划分成若干个子串使得每个字串的最大值和最小值之差加起来最大，很显然，我们可以想到这样的贪心思路：**只有单调不下降序列或者单调不上升子序列的组合使得最终加出来的和最优，否则的话我们就将这个字符串拆成若干个别的串在进行**。

第一感觉不需要 DP，直接模拟然后累加就可以。但是发现不太对劲，**因为对于序列的最大值最小值来讲，我们不知道把它归属于前面的串最优还是后面的串更优（更具点讲就是将其归为不下降子序列还是不上升子序列更优）**。所以需要一个 DP 来保证每次决策的**局部最优性**，这也是 DP 所追求的，用局部最优来保证全局最优。

根据上述推理，我们需要一个 $pos$ 数组来记录最大值和最小值的位置。然后设 $dp[i]$ 表示前 $i$ 个数所获得的最大的最大值和最小值之和，转移方程也不难推出：

$dp[i] = \max(dp[pos] + \operatorname{abs}(a[i] - a[pos + 1]), dp[pos - 1] + \operatorname{abs}(a[pos] - a[i]))$。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int maxn = 1e6 + 6;
int n, a[maxn], dp[maxn], pos = 1;
bool up_or_down(int x)
{
    return (a[x] >= a[x - 1] && a[x] >= a[x + 1]) || (a[x] <= a[x - 1] && a[x] <= a[x + 1]);
}// 判断是否为单调不下降序列或者单调不上升子序列
signed main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    for (int i = 2; i <= n; i++)
    {
        dp[i] = max(dp[pos] + abs(a[i] - a[pos + 1]), dp[pos - 1] + abs(a[pos] - a[i]));
        pos = up_or_down(i) ? i : pos;
    }
    cout << dp[n];
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122536895)

---

## 作者：CQ_Bab (赞：0)

# 思路
这道题有一个结论，就是若你分的是单调递增或递减的序列那么一定就比把不是单调序列的分发要好（这个就不证明了）。有了这个结论，我们就会发现一个分开的序列一定是以这个序列中的极值开头或结尾的。那么我们就可以用动态规划，并在其中把极值给统计出来即可。

$f_i$ 表示从 $1$ 到 $i$ 能得到的最大和，从 $2$ 推起，最后输出 $f_n$。

那么状态转移方程就为 $f_i=\max(f_{ji}+abs(a_i-a_{ji+1}),f_{ji-1}+abs(a_{i}-a_{ji}))$，$ji$ 为极值，在更新完后也要记得把极值也更新一下。
# 代码
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[1000001];
int ji=1; //初始化为1
int f[1000001];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++) {
		f[i]=max(f[ji]+abs(a[i]-a[ji+1]),f[ji-1]+abs(a[i]-a[ji])); //更新
		if(a[i]>=a[i-1]&&a[i]>=a[i+1]||(a[i]<=a[i-1]&&a[i]<=a[i+1])) ji=i;//更新极值
	}
	cout<<f[n]<<endl;
	return false;
}
```


---

## 作者：WaterSun (赞：0)

# 思路

首先，我们知道一个很显然的结论：如果你分的每一段都是单调递增或者是单调递减的，那么，这种分法一定最好。

然后，我们定义 $dp_i$ 表示取前 $i$ 个数的最大价值。

那么，我们的状态转移方程只需考虑一下，上一个峰顶（峰底）是算在当前这部分还是上一个部分。

最后，状态转移方程得：$dp_i = \max(dp_l + |a_{l + 1} - a_i|,dp_{l - 1} + |a_l - a_i|)$（其中 $l$ 表示上一个峰顶或峰底）

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 1e6 + 10;
int n,l = 1;
int arr[N],dp[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline bool check(int x){//判断 
	return ((arr[x - 1] <= arr[x] && arr[x] >= arr[x + 1]) || (arr[x - 1] >= arr[x] && arr[x] <= arr[x + 1]));
}

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++) arr[i] = read();
	for (re int i = 2;i <= n;i++){
		dp[i] = max(dp[l] + abs(arr[l + 1] - arr[i]),dp[l - 1] + abs(arr[l] - arr[i]));//状态转移 
		if (check(i)) l = i;//更新 l 的值 
	}
	printf("%lld",dp[n]);
	return 0;
}
```

---

## 作者：End1essSummer (赞：0)

> 题面简述：有一组数，你要把他分成若干连续段。每一段的值，定义为这一段 数中最大值与最小值的差。 求一种分法，使得这若干段的值的和最大。 $N$ < 1e6, $a_i$ < 1e9。

观察题面，我们可以得出最优分法：最后每一段都是一个满足单调性的区间。

为什么这样做是最优的？

因为如果原串不是单调的，我们定可以通过把原串通过分成一个又一个的单调子串来使的答案更优，这便是这道题的难点之一。

第二个难点其实也说不上是难点，其实就是关于这道题需要使用的算法问题。

首先我们考虑贪心，因为贪心策略就是第一个难点，接下来贪心的去取或者 dp 取都可以。

这里我觉得用 dp 会更简洁一点，也更易上手。贪心的去取的话难以实现。

并且你需要记录这个区间的开头以方便计算。

代码如下

```cpp
//CF484D
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[1000010],dp[1000010],f=1;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }for(int i=2;i<=n;i++){
        dp[i]=max(dp[f]+abs(a[i]-a[f+1]),dp[f-1]+abs(a[f]-a[i]));
        if(!(a[i+1]>a[i]&&a[i]>a[i-1])&&!(a[i+1]<a[i]&&a[i]<a[i-1])) f=i;
    }cout<<dp[n];
    return 0;
}
```




---

## 作者：RainFestival (赞：0)

$\rm Difficulty = \color{red}2400$

这里是一个非常无脑的做法。

我们发现这个题目有决策单调性，具体可以用四边形不等式证明。

也就是要证明下面这个东西：

考虑 $l\le x\le r\le y$，则 $s(l,r)+s(x,y)\ge s(l,y)+s(x,r)$。

我们把最大值和最小值的贡献分开，假设我们现在正在考虑最大值。记录 $s(l,r)+s(x,y)=w$，$s(l,y)+s(x,r)=w'$。

+ 假设最大值 $k$ 在 $[x,r]$ 这一段，那么它对于 $w$ 和 $w'$ 贡献都是相同的。

+ 假设最大值 $k$ 在 $[l,x-1]$ 这一段，那么 $w=k+[x-1,y]$ 这段区间的最大值，$w'=k+[x-1,r]$ 这一段区间的最大值。显然 $[x-1,r]\subset [x-1,y]$。

所以无论如何 $w>w'$。

这就说明了问题具有决策单调性。

然后决策单调性该怎么做就怎么做。

注意这个方案是 $\mathcal{O(n\log n)}$ 的。所以必须稍微实现得精细一些，不然会 $\rm TLE$。

代码贼长就是了：

```cpp
#include<cstdio>
#include<cstdlib>
#include<utility>
int n,lg[1000005],pp[1000005];
std::pair<int,int> st[25][1000005];
long long f[1000005],dp[1000005];
void pre()
{
	int t=2;
	lg[1]=0;
	for (int i=2;i<=n;i++) if (i==t) lg[i]=lg[i-1]+1,t=t*2;else lg[i]=lg[i-1];
	for (int i=1;i<=n;i++) st[0][i]=std::make_pair(i,i);
	for (int k=1;k<=lg[n];k++)
	    for (int i=1;i<=n-(1<<k)+1;i++)
	    {
	    	int mx,mn;
			std::pair<int,int> l=st[k-1][i],r=st[k-1][i+(1<<(k-1))];
	    	if (f[l.first]>f[r.first]) mx=l.first;else mx=r.first;
			if (f[l.second]<f[r.second]) mn=l.second;else mn=r.second;
			st[k][i]=std::make_pair(mx,mn);
		}
}
long long ask(int x,int y)
{
	int lay=lg[y-x+1],mx,mn;
	std::pair<int,int> l=st[lay][x],r=st[lay][y-(1<<lay)+1];
	if (f[l.first]>f[r.first]) mx=l.first;else mx=r.first;
	if (f[l.second]<f[r.second]) mn=l.second;else mn=r.second;
	long long ans=f[mx]-f[mn];
	return ans;
}
long long calc(int x,int y){return dp[x]+ask(x+1,y);}
int bs(int l,int r,int x,int y)
{
	if (l==r) return l;
	int mid=l+(r-l)/2;
	if (calc(x,mid)<calc(y,mid)) return bs(l,mid,x,y);
	else return bs(mid+1,r,x,y);
}
int hd,tl,q[1000005];
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&f[i]);
	pre();
	int hd=1,tl=0;
	q[tl++]=0;
	for (int i=1;i<=n;i++)
	{
		while (tl-hd+1>1)
		{
			int y=q[hd+1];
			if (pp[y]<=i) q[hd++]=0;
			else break;
		}
		int k=q[hd];
		dp[i]=dp[k]+ask(k+1,i);
		int pt=0;
		while (tl-hd+1>1)
		{
			int y=q[tl];
			pt=bs(i+1,n+1,y,i);
			if (pt<=pp[y]) q[tl--]=0,pt=0;
			else break;
		}
		q[++tl]=i;
		if (tl-hd+1==1) continue;
		if (!pt) pt=bs(i+1,n+1,q[tl-1],i);
		pp[i]=pt;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
```

代码长度 $\tt 1.69KB$，用时 $\tt 98s$，内存 $\tt 217.79MB$。非常垃圾。

---

## 作者：fisheep (赞：0)

## 思路:
首先明确的是这是一道**贪心**，，但同时它也是一道$dp$题，感觉
~~(dp和贪心是两个不可能同时存在的东西)~~。

看到这种题不难想到要去处理它的极值点，

$dp[i]$表示到$i$点处的最大划分情况。

$a[i]>=a[i+1],a[i]>=a[i-1]$或者$a[i]<=a[i+1],a[i]<=a[i-1]$时，超过$i$多取没有意义，所以寻找距离$i$最近的极值点作为转移条件即可，令最近的极值点为$p$，有两种情况，$p$属于前段序列中，$p$属于后段序列。

最后也就相当于找出所有单调的区间。

*  转移方程：

$dp[i]=max(dp[p-1]+abs(a[i]-a[p]),dp[p]+abs(a[i]-a[p+1]))$


* 寻找保存$i$之前最近的极值点：

```cpp
if(i<n){
 if(a[i]>=a[i-1]&&a[i]>=a[i+1]) p=i;
 else if(a[i]<=a[i-1]&&a[i]<=a[i+1]) p=i;
		}
   ```
   
## Code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e6+10;
#define int long long
inline int read(){
  int x=0,f=1;
  char ch=getchar();
  while(ch>'9'||ch<'0'){
    if(ch=='-') f=-1;
    ch=getchar();
  }
  while(ch>='0'&&ch<='9'){
    x=(x<<1)+(x<<3)+(ch^48);
    ch=getchar();
  }
  return x*f;
}

#define ll long long
int n;
ll a[maxn];
ll dp[maxn];

signed main(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	int p=1;
	for(int i=2;i<=n;i++){
		dp[i]=max(dp[p-1]+abs(a[i]-a[p]),dp[p]+abs(a[i]-a[p+1]));
		if(i<n){
		if(a[i]>=a[i-1]&&a[i]>=a[i+1]) p=i;
		else if(a[i]<=a[i-1]&&a[i]<=a[i+1]) p=i;
		}
	}
	printf("%lld\n",dp[n]);
	return 0;
}

```

---

## 作者：ZVitality (赞：0)

**证明：每个子串单调最优。**

证明如下：

当前为 $x$，在子串 $a_i,a_{i+1},a_{i+2},\dots a_{x-1}$，最大值和最小值已经确定。

我们加入 $a_x$，如果它不是单调的，把它丢进去显然没用，所以分出来。

值得一提的是，它有**单调递增**和**单调递减**两种可能。

---

初始边界：$dp_2 = abs(a_2 - a_1)$。

注：只要内存大，变量开`long long`。

---

