# [ABC374C] Separated Lunch

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc374/tasks/abc374_c

キーエンス本社に勤務する人数が増えてきたので、本社に存在する部署を $ 2 $ つのグループに分け、昼休みの時間帯を分けることにしました。

キーエンス本社には $ N $ 個の部署が存在し、$ i $ 番目 $ (1\leq\ i\leq\ N) $ の部署に所属する人数は $ K_i $ 人です。

それぞれの部署をグループ $ A $, $ B $ のいずれか一方に割り当て、グループごとに同時に昼休みをとり、 かつグループ $ A $, $ B $ の昼休みの時間が重ならないようにしたとき、同時に昼休みをとる最大人数としてあり得る最小の値を求めてください。  
 すなわち、グループ $ A $ に割り当てられた部署に所属する人数の合計とグループ $ B $ に割り当てられた部署に所属する人数の合計 のうち大きい方の値としてあり得る最小の値を求めてください。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 20 $
- $ 1\leq\ K_i\ \leq\ 10^8 $
- 入力はすべて整数
 
### Sample Explanation 1

$ 1,2,5 $ 番目の部署をグループ $ A $ に、$ 3,4 $ 番目の部署をグループ $ B $ に割り当てたとき、 グループ $ A $ に割り当てられた部署に所属する人数の合計は $ 2+3+12=17 $ 、 グループ $ B $ に割り当てられた部署に所属する人数の合計は $ 5+10=15 $ となり、 このとき同時に昼休みを取る最大人数は $ 17 $ となります。 一方で、グループ $ A,B $ それぞれに割り当てられた部署に所属する人数の合計がいずれも $ 16 $ 以下になるように 部署を割り当てることはできないため、$ 17 $ を出力します。

### Sample Explanation 2

同一人数の部署が複数存在する可能性もあります。

### Sample Explanation 3

例えば、$ 1,4,5 $ 番目の部署をグループ $ A $ に、$ 2,3,6 $ 番目の部署をグループ $ B $ に割り当てたとき同時に昼休みを取る最大人数は $ 89 $ となります。

## 样例 #1

### 输入

```
5
2 3 5 10 12```

### 输出

```
17```

## 样例 #2

### 输入

```
2
1 1```

### 输出

```
1```

## 样例 #3

### 输入

```
6
22 25 26 45 22 31```

### 输出

```
89```

# 题解

## 作者：A_R_O_N_A (赞：6)

## 题意

给你一个长度为 $n$ 的数组 $K$，现需要将数组中的数划分成为两个子集。

求这两个子集的子集和中的最大的那个子集和的可能的最小值。

$1 \le n \le 20$ 且 $1 \le K_i \le 10^8$。

## 分析

首先注意到 $1\le n\le 20$，范围极小。

那么我们就考虑用类似于状压 DP 的算法来解决这道题。

如果您还不知道什么是状压 DP，可参照[此处](https://oi-wiki.org/dp/state/)。

## 思路


使用一个二进制数 $i$ 来表示选中的数字有哪些，那么用 $dp_i$ 来表示选中的数字的总和，设数组总和为 $s$，那么另一个子集和可轻松表示为 $s-dp_i$。为什么说是类似于状压 DP 呢？是因为这道题并不需要什么所谓的转移方程，只是用二进制数表示状态而已。具体实现见代码及注释。

时间复杂度 $O(2^n\times n)$。


```cpp
ll n,a[25],dp[1<<20],sum,ans=LLONG_MAX;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		sum+=a[i];//求总和
	}
	for(int i=0;i<(1<<n);i++){//慢慢枚举状态
		for(int j=0;j<n;j++){
			if(i&(1<<j))dp[i]+=a[j];//若当前数的第j位为1，则选中了第j个数
		}
	}
	for(int i=0;i<(1<<n);i++){
		ans=min(ans,max(dp[i],sum-dp[i]));//统计答案
	}
	write(ans);
	return 0;
}
//一道用于理解状压思想的入门题
```

---

## 作者：fishing_cat (赞：4)

### 题意

给你 $n$ 个数，要求你将这 $n$ 个数分成两组，使两组中较多人数的组人数最小。

### 思路

发现 $n$ 只有 $20$，指数复杂度的深度优先搜索是可以过的。

所以，只要在深索中分两种方案，进第一组和进第二组。

时间复杂度 $O(2 ^ n)$。

### code 


```cpp
#include<bits/stdc++.h>
#define ll long long

const ll inf = 1e16;
using namespace std;

ll n, k[50], ans = inf, z;

void dfs(ll id, ll now) {
	if (id > n) {
		ans = min(ans,max(now, z - now)); // 统计最优解
		return ;
	}
	dfs(id+1, now + k[id]);
	dfs(id+1, now);
}

int main() {
	read(n);
	for (int i = 1; i <= n; i++) {
		read(k[i]);
		z += k[i]; // z 存储总值
	}
	dfs(1, 0);
	cout << ans << "\n";
 	return 0; // 完结撒花
}
```

---

## 作者：Bobxing (赞：3)

注意到 $n$ 很小，可以 dfs 暴力搜索。

首先将数组存储下来，dfs 中存储三个参数，分别是现在枚举到的位置，到这一步 $a$ 数组的和，以及到这一步 $b$ 数组的和，终止情况就是枚举到的位置等于 $n+1$，更新 $ans$ 并返回即可。至于转移，分两种情况讨论：

1. 这一位归到 $a$ 里。
2. 这一位归到 $b$ 里。

于是本题就做完了。

献上丑陋无比的代码：

```cpp
#include<iostream>
using namespace std;
int a[ 40 ], n, ans = 0x3f3f3f3f;
void dfs( int now, int asum, int bsum )
{
    if( now == n + 1 )
    {
        ans = min( ans, max( asum, bsum ) );
        return;
    }
    dfs( now + 1, asum + a[ now ], bsum );
    dfs( now + 1, asum, bsum + a[ now ] );
}
int main()
{
    cin >> n;
    for( int i = 1; i <= n; i++ )
        cin >> a[ i ];
    dfs( 1, 0, 0 );
    cout << ans;
    return 0;
}

```

---

## 作者：XXh0919 (赞：2)

高级暴力 C 题。

### 解法

当看到 $N\leq20$ 的数据时，我：心里窃喜。

于是直接开始暴力！我们只抓一个组，对于每一个部门都有两种情况，一是将该部门加到这个组里，二是将该部门不加到这个组里，当所有部门被分配完毕后按照题意取答案即可。

### AC Code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
#define pi pair<int,int>
#define mkp(a,b) make_pair((a),(b))
#define IOS cin.tie(0)->sync_with_stdio(0)
using namespace std;
const int N=2e6+15,mod=1e9+7;

int n,sum,ans;
int k[N],f[N];

void dfs(int x,int y){
	if(x>n){
		ans=min(ans,max(y,sum-y));//因为一共只有 sum 个人，所以当一个组分配 y 人后剩下一个组就是 sum-y 人
	}else{
		dfs(x+1,y+k[x]);//加入这个组
		dfs(x+1,y);//不加入这个组
	}
}

signed main(){
	IOS;
	ans=0x3f3f3f3f;
	cin>>n;
	rep(i,1,n)cin>>k[i],sum+=k[i];//求一个和方便后续操作
	dfs(1,0);//从一号部门开始，人数为 0
	cout<<ans<<endl;
	return 0;
} 
```

---

## 作者：zhengyi0402 (赞：1)

# ABC374 C题题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc374_c)

数据范围：

$2 \le n \le  \color{red} 20 $

$1 \le k \le 10^8$

~~呵呵，dfs 萌新准备用一下 dfs。~~

## 主要思路

我们记输入的数组为 $a$ 数组，$tsum$ 为所有元素的和。

dfs 时，因为只可能将元素加入两个部门的其中一个，所以我们可以考虑先将他加入一号部门，再加入二号部门。

一号部门人数需要一个变量记录，我们记为 $sum$。

每一次人手全部分完时，拿一个变量打个擂台就行了。

打擂台代码：


```cpp
ans=min(ans,max(tsum-sum,sum));
```

这样，我们就不需要写一个很长的 dfs，只需要寥寥几行就能通过这道题啦！

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[22],tsum;int n,pans;int ans = LONG_LONG_MAX;
void dfs(int x,int sum){
	if(x>n){ans=min(ans,max(tsum-sum,sum));return ;}
	dfs(x+1,sum+a[x]);dfs(x+1,sum);
}
signed main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i = 1;i <= n;i++){cin>>a[i];tsum+=a[i];}
	dfs(1,0);
	cout<<ans;
	return 0;
	//十年OI一场空，define int 见祖宗。
	//十年OI一场空，不开long long见祖宗。
}
```

[提交记录](https://atcoder.jp/contests/abc374/submissions/58460763)

此代码时间复杂度：$O(2^n)$。

## 后记（题外话）

~~话说这一次比赛的页面死红死红的，也不知道出题组怎么想的。~~

## 修改日志

一改：对思路部分的空白处进行了补全。

---

## 作者：mirance2025 (赞：1)

### 题目描述

众所周知，一位 OIer 需要讲题目读 3 遍。

### 题意分析
简单 dfs。~~一位蒟蒻卡了那么长时间。。。~~

由于本题中 $N$ 的数据范围较小，可以考虑暴搜。

用 dfs 来求任意几个数的和，然后判断较大者的最小值即可。详见代码。

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 25;

ll n;
ll k[N];
ll sum;
ll ans = 1e18;

void dfs(ll depth, ll res){
	ans = min(ans, max(sum, res));
	for (ll i = depth + 1; i <= n; i ++ ){
		sum -= k[i];
		dfs(i, res + k[i]);
		sum += k[i];
	}
}
int main(){
	scanf("%lld", &n);
	for (ll i = 1; i <= n; i ++ )
	    scanf("%lld", &k[i]), sum += k[i];
	    
	dfs(0, 0);
	
	printf("%lld\n", ans);
	
	return 0;
}

```

---

## 作者：Liuhy2996 (赞：1)

## 题意
将 $N$ 个数分成两部分，设 $S$ 是每部分的和的最大值，求 $S$ 的最小值。
## 思路
因为 $N\le 20$，所以直接枚举所有情况就行。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,inf=1e15;
int n,mx=inf,ans,sum,a[N];
signed main(){
	cin>>n;
	for(int i=0;i<n;++i) cin>>a[i],ans+=a[i];
	for(int i=0;i<1<<n;++i){ //二进制枚举
		sum=0;
		for(int j=0;j<n;++j) sum+=((i>>j)&1)*a[j];
		mx=min(mx,max(sum,ans-sum));
	}
	cout<<mx;
	return 0;
}
```

---

## 作者：under_the_time (赞：1)

## 题意

> 给定 $n$ 个数 $\{a_n\}$，要求将所有元素分成两个集合 $A,B$，使得 $\max(\sum_{b\in A}b,\sum_{c\in B}c)$ 尽可能小，即两个集合中的数分别求和后，两者和的较大者最小。求这个最小值。
>
> $2\le n\le 20$，$1\le a_i\le 10^8$。

## 解法

发现 $n$ 很小，我们考虑枚举一个 $n$ 位的二进制数表示每个数被分进了哪个集合中。具体地，对于一个 $n$ 位的二进制数 $X$，若第 $i$ 位为 $0$ 则表示 $a_i$ 在 $A$ 中，反之 $a_i$ 在 $B$ 中。我们就从 $0$ 枚举到 $2^n-1$，然后‘枚举每一位统计两个集合的和即可。时间复杂度 $O(n2^n)$。

## 代码

为了方便代码中下标均从 $0$ 开始。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define open(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
const int maxn = 25;
int f[maxn], n;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i ++)
		scanf("%d", &f[i]);
	int ans = __INT_MAX__; // __INT_MAX__ 即为 2147483647
	for (int s = 0; s < (1 << n); s ++) {
		int a = 0, b = 0;
		for (int i = 0; i < n; i ++)
			(s & (1 << i)) ? a += f[i] : b += f[i];
		ans = min(ans, max(a, b));
	} printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Leo2011 (赞：1)

~~无耻的广告~~[更好的阅读体验~](https://leo2011.eu.org/2024/10/05/ti-jie-at-abc374-c-abc374c-separated-lunch/)

---

~~已经沦落到在写这种水题题解了。~~

# 题目翻译

有 $n$ 队人，每个队人数不同，把他们分成 2 组（同一队的不能拆开），使两组人数差距尽量小。

形式化题意：有 $n$ 个数，把它们分成两组，使两组和的差尽量小。

说句闲话：感觉这题目很经典，但我没有原题作为证据（大雾

# 解法

本来觉得我这菜鸡实力是不可能做出来的，~~已经准备摆烂了~~，此时我突然发现 $n \le 20$。

这是啥概念？

![时间复杂度对应表](https://cdn.luogu.com.cn/upload/pic/26845.png)

看图，$n \le 25$ 都是可以用 $O(2 ^ n)$ 做法解决的，这不结束了？直接枚举每一组，分类讨论是 A 组还是 B 组，就可以了。

给个小建议：可以记录总人数，这样子只需要记录 A 组人数，B 组人数可以直接 $O(1)$ 计算，这样就变成选与不选的 dfs 模板题目了……更关键的是这样子不需要记录为每一队对应哪一组了。

# 代码

ACCode with 注释：

```cpp
/*Code by Leo2011*/
#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define EPS 1e-8
#define FOR(i, l, r) for (int(i) = (l); (i) <= (r); ++(i))
#define log printf
#define IOS                      \
	ios::sync_with_stdio(false); \
	cin.tie(nullptr);            \
	cout.tie(nullptr);

using namespace std;

typedef __int128 i128;
typedef long long ll;
typedef pair<int, int> PII;

const int N = 30;
int n, a[N], ans = INF, sum;

template <typename T>

inline T read() {
	T sum = 0, fl = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T>

inline void write(T x) {
	if (x < 0) {
		putchar('-'), write<T>(-x);
		return;
	}
	static T sta[35];
	int top = 0;
	do { sta[top++] = x % 10, x /= 10; } while (x);
	while (top) putchar(sta[--top] + 48);
}

void dfs(int group, int cnt) {
	if (group == n) {
		ans = min(ans, max(cnt, sum - cnt));
		return;
	}
  // 组 A
	dfs(group + 1, cnt + a[group]);
  // 组 B
	dfs(group + 1, cnt);
}

int main() {
	n = read<int>();
	FOR(i, 1, n) a[i] = read<int>(), sum += a[i];
	dfs(1, 0);
	write<int>(ans);
	return 0;
}
// 20组---》爆搜挂着机，打表出 AC
```

[赛时 AC 记录~](https://atcoder.jp/contests/abc374/submissions/58457793)

理解万岁！

---

## 作者：xdogg (赞：1)

### 题意简述

有 $n$ 个部门，需要将这些部门分成两组，使得两组之间人数差距最小，并求出人数较多的一组人数。

### 思路

看到此题数据范围 $n\le 20$，即想到可以将所有分组情况枚举一遍，时间 $O(2^n)$。对每种情况进行处理，时间 $O(n)$，可以通过此题。

一些细节见代码。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum=0,ans=2e9,a[25];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	for(int i=0;i<(1<<n);i++){//枚举所有情况
		int k=i,s=0;
    for(int j=0;j<n;j++){//依次遍历每个部门
			if(k&(1<<j)) s+=a[j];//当前位为1则选入
		}
		ans=min(ans,max(s,sum-s));
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：_JF_ (赞：1)

[Link](https://www.luogu.com.cn/problem/AT_abc374_c)

？？简单题。

直接 $2^n$ 枚举每个人要放在哪个集合即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long 
int ans=LLONG_MAX,n,a[N],c[N];
int calc(){
	int s1=0,s2=0;
	for(int i=1;i<=n;i++){
		if(c[i]==0)	s1+=a[i];
		else	s2+=a[i];
	}
	return max(s1,s2);
}
void dfs(int dis){
	if(dis==n+1){
		ans=min(ans,calc());
		return ;
	}
	c[dis]=0,dfs(dis+1),c[dis]=1,dfs(dis+1);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	dfs(1);
	cout<<ans<<endl;
} 
```

---

## 作者：JXR_Kalcium (赞：1)

## 题目大意

给定一个长为 $N$ 的序列 $K$，需要对于每个 $1\le i\le N$ 都把 $K_i$ 放进堆 $A$ 或者堆 $B$ 中，使得 $\max\left(\sum_{i\in A}i,\sum_{i\in B}i\right)$ 最小，求这个最小值，数据范围 $N\le 20$。

## 解题思路

看到这个数据范围，再想到每一个数只有放 $A$ 和放 $B$ 两种可能，所以如果暴搜的话时间复杂度只有 $O(2^N)$，可以通过本题。具体来说，搜索时记录两个参数，一个是当前考虑的位置，一个是放进某一堆里的数字和 $x$，这样另一堆的数字和就是 $\left(\sum_{i=1}^{N} K_i\right)-x$，只需要搜到最后一个数时计算上面两个式子的最大值，并对每一个最大值取最小值即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll n,a[21],ans=INT_MAX,sum;

void dfs(ll x, ll y)
{
    if(x==n)
    {ans=min(ans,max(y,sum-y)); return;}
    dfs(x+1,y); dfs(x+1,y+a[x+1]);
}

int main()
{
    n=read();
    for(R int i=1; i<=n; ++i)
    a[i]=read(), sum+=a[i];
    dfs(0,0); write(ans);
    return 0;
}
```

---

## 作者：hjyowl (赞：1)

### 题目大意

有一个 $n$ 个部门，第 $i$ 个部门有 $a_i$ 人，要求把 $n$ 部门分成两边，要求两边的人数中的最大值最小，输出最小的方案。

### 思路

注意到 $n \le 20$，思路很明显，对于每一个部门，枚举他放在那边，然后把答案记录起来最后去一个最小的方案即可。

时间复杂度：$\Theta(2^n)$。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int n,m;
int a[N];
int res = 1e9;
void dfs(int u,int x,int y){
	if (u == n + 1){
		res = min(res,max(x,y));
		return ;
	}
	dfs(u + 1,x + a[u],y);
	dfs(u + 1,x,y + a[u]);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
	}
	dfs(1,0,0);
	cout << res;
	return 0;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 思路

考虑到 $n$ 很小，可以直接通过爆搜去枚举第 $i$ 个部门是否放在 $A$ 组，最后放在 $B$ 组的人数就是总人数减去 $A$ 组人数，然后答案取 $A$ 组人数和 $B$ 组人数的最大值中的最小值即可。

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define rep( i , l , r ) for (int i = (l) ; i <= (r) ; i++)
#define per( i , r , l ) for (int i = (r) ; i >= (l) ; i--)
#define umap unordered_map
#define uset unordered_set
using u64 = unsigned long long ;

int n ;
int k[31] ;
int ans = 0x3f3f3f3f ;
int gb ;
void dfs ( int idx , int sum ){
	if ( idx > n ){
		int a = sum , b = gb - sum ;
		ans = min ( ans , max ( a, b ) ) ;
		return ;
	}
	dfs ( idx + 1 , sum ) ;
	dfs ( idx + 1 , sum + k[idx] ) ;
}
void solve (){
	cin >> n ;
	rep ( i , 1 , n ){
		cin >> k[i] ;
		gb += k[i] ; 
	}
	dfs ( 1 , 0 ) ;
	cout << ans ;
}

signed main (){
	int _ = 1 ;
	//cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：yegengghost (赞：0)

冷知识之：该题与后面的题数据都很水。

这个题的数据范围：$1\le n\le 20$。

题面的二分瞬间不香了。

直接暴力枚举，时间复杂度~~撑死~~为 $O(2^nn)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
	cin>>n;
	vector<int>k(n);
	for(int i=0;i<n;i++)
		cin>>k[i];
	int ans=numeric_limits<int>::max();
	//数据很水，直接暴力，不要二分。
	for(int i=0;i<(1<<n);++i)//这一个循环复杂度为O（2^n）
	{
		int a=0,b=0;
		for(int j=0;j<n;j++)//这个是O（n）
		{
			if(i&(1<<j))
				a+=k[j];
			else
				b+=k[j];
		}
		ans=min(ans,max(a,b));
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：ATION001 (赞：0)

## 题目描述
给定一串长度为 $n$ 的整数序列，你需要选择一些数字将它们放到序列 $A$。记 $A$ 序列中数字之和为 $x$，记原来的序列中剩下的数字之和为 $y$，请问 $\max(x,y)$ 的值最小为多少？
## 思路
这题纯暴力就可以过了。

没看数据范围之前我还以为可能是贪心，但是一看数据范围：$1\le n\le 20$。

直接写暴力。

枚举每一位选和不选求出结果，时间复杂度为 $O(2^n\times n)$（相对于我的写法来说），可以通过本题。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[25],tot,ans=LLONG_MAX;
signed main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		tot+=a[i]; // 提前处理总和，避免重复计算（主要是我懒得再写一个循环）
	}
	for(int i=0;i<(1ll<<n);i++){ // 我使用的是二进制枚举，其他的方法还有 DFS
// 这种方法时间复杂度相对 DFS 来说较大，但是代码简短（还能用来装逼（逃））
		int sum=0;
		for(int j=31;j>=0;j--){ // 二进制拆分，这种小技巧在状压 DP 中很常见
			if(i&(1ll<<j)){ // 选择当前位置
				 sum+=a[j];
			}
		}
		ans=min(ans,max(sum,tot-sum));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lucasincyber (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc374_c)
## 思路
我们发现 $n$ 的范围十分小，那就考虑 dfs。每一个小组有 $2$ 种情况：进第一个组，或第二个组。那就暴力 dfs 即可。

时间复杂度为 $O(2^n)$，可以通过本题。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 25;

int n, ans = 2e9;
int k[N];

void dfs(int u, int sumA, int sumB)
{
	if (u == n + 1)
	{
		ans = min(ans, max(sumA, sumB));
		return;
	}
	if (max(sumA, sumB) >= ans) return;
	dfs(u + 1, sumA + k[u], sumB);
	dfs(u + 1, sumA, sumB + k[u]);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &k[i]);
	dfs(1, 0, 0);
	printf("%d\n", ans);
	return 0;
}
```

---

