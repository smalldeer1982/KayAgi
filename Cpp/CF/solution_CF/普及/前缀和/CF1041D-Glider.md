# Glider

## 题目描述

```
你在玩一个吃鸡游戏，你现在要跳伞。你的飞机现在在高度为$h$的空中飞行，你每飞一个单位长度的距离，你就会下落一个单位长度的高度，当然，有些地方是上升气流，你不会下落，你会往前直飞，由于你想在空中就被人打死，求你最远的飞行距离

## 样例 #1

### 输入

```
3 4
2 5
7 9
10 11
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 10
5 7
11 12
16 20
25 26
30 33
```

### 输出

```
18
```

## 样例 #3

### 输入

```
1 1000000000
1 1000000000
```

### 输出

```
1999999999
```

# 题解

## 作者：ezoixx130 (赞：9)

### 题意：

一个飞行员要跳伞，他可以从任意点开始跳，从高度$h$开始下降，每秒向前移动一个单位，下降一个单位。

有$n$个区间，每个区间有左右端点$l,r$，飞行员经过$l$至$r$时不会下降。保证区间不相交。

给你$n,h$和每个区间，让你求飞行员能飞行的最远距离。

### 题解：

首先有一个结论：最优解一定是从某个区间的左端点起跳。

那么我们只需要判断他从每个区间的左端点起跳的飞行距离，取最大值即可。

那么预处理出每个区间之间飞行员会下降的距离的前缀和，对于每个区间，二分找出飞行员触地的位置，计算答案并更新即可。

时间复杂度：$O(nlog(n))$

空间复杂度：$O(n)$

其实容易想到$O(n)$的做法，每次触地的位置一定是递增的，直接扫描即可。

代码：（是不是很短）

```cpp
#include <bits/stdc++.h>
using namespace std;

#define MAXN 200010
int n,h,ans,l[MAXN],r[MAXN],d[MAXN];

int main()
{
    scanf("%d%d",&n,&h);
    for(int i=1;i<=n;++i)scanf("%d%d",l+i,r+i),d[i]=d[i-1]+l[i]-r[i-1];
    for(int i=1;i<=n;++i)
    {
        int id=lower_bound(d+i+1,d+n+1,h+d[i])-d-1;
        ans=max(ans,r[id]-l[i]+h-d[id]+d[i]);
    }
    printf("%d\n",ans);
}
```

---

## 作者：Bobi2014 (赞：2)

## 这题是一道~~可爱的~~二分+前缀和题目
### 必备知识
- ### [二分](https://oi.wiki/basic/binary/)
- ### [前缀和（如果有空就顺便把差分也学习一下）](https://oi.wiki/basic/prefix-sum/)
### 题目大意
有一个数轴、$n$ 个区间和一个值 $h$，从一个点出发，每走一步如果不属于任何一个区间的话 $h$ 就减一，$h$ 为 $0$ 就不能走了，求最多能走多少步。
### 解体方法
通过观察题目，我们不难发现最优解一定是从一个区间的开始点走起的，所以枚举起始点，这里已经用掉了 $O(n)$ 的时间复杂度，我们最多还有 $O(\log(n))$ 的时间复杂度可以使用，所以立刻联想到二分~~大法~~，我们可以二分最后经过的是哪一个区间，但是每一次检查是否满足条件只能 $O(1)$ 求，所以又联想到了前缀和优化，`sum[i]`表示从第一个区间到第 $i$ 个区间 $h$ 需要减掉的值。
### 时间、空间复杂度分析
- 时间复杂度枚举起点 $O(n)$，二分 $O(\log(n))$，二分中的检查是否满足条件 $O(1)$，故得时间复杂度 $O(n \log(n))$。

- 空间只需要开 $3$ 个数组，分别存区间的`l`与`r`以及前缀和的`sum`数组，故得空间复杂度 $O(n)$。

---

## 作者：clearlove7777 (赞：2)

    emmmmm
    这道题算是比较简单的了
    用两个指针分别指开始和结束位置
    根据贪心的思想，出发点一定在某个上升气流的左端点
    首先处理l=1的情况
    我在代码中用了一个now记录当前高度
    如果从第一个区间出发可以通过最后一个区间，那么不用说，这显然最优
    否则的话我们记录下滑翔机最远能到达的区间y（无法到达y+1）
    此时让now记录刚通过y区间时的高度
    这样我们就可以逐步将区间向右移动了
    我们每次移动直接将起点x移到x+1区间的左端点
    这样的话当我们到达y区间右端是就能比之前高l[x+1]-r[x]
    然后继续向右更新y
    注意当y==n时，以后的状态就没有必要继续更新了，因为显然我们通过的区间总长度越长答案越优，以后的右移x只会减少区间。
    那就直接上代码了
    
   ```cpp
#include<cstdio>
using namespace std;
int n,h;
int max(int a,int b){
	return a>b?a:b;
}
struct node{
	int l,r;
}p[200005];
int main(){
	scanf("%d%d",&n,&h);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].l,&p[i].r);
	int s=p[1].l,x=1,y,now=h;
	for(int i=1;i<n;i++){
		now-=p[i+1].l-p[i].r;
		if(now>0)
			y=i+1;
		else
			break;
	}
	if(h==1){
		int ans=0;
		for(int i=1;i<=n;i++)
			ans=max(ans,p[i].r-p[i].l+1);
		printf("%d",ans);
		return 0;
	}
	if(now>0){//能直接从第一个上升气流飞到最后一个上升气流，显然没有更优解 
		printf("%d",p[n].r-s+now);
		return 0;
	}
	//其余情况：只能刚好飞到y区间，飞不到y+1
	now+=p[y+1].l-p[y].r;
	int ans=p[y].r-s+now;
	while(x<n){//x表示在那个区间出发，y表示在那个区间之后结束,now即当先高度，用来判断能飞到那个区间 
		x++;
		now+=p[x].l-p[x-1].r;
		while(now>p[y+1].l-p[y].r&&y<n){
			now-=p[y+1].l-p[y].r;
			y++;
		}
		ans=max(ans,p[y].r-p[x].l+now);
		if(y==n)
			break;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：QWQ_jyc (赞：1)

首先因题目所知最优解是从左端点起跳的飞行距离的最大值。

因此只需要提前算出每个区间中飞行员会下降的距离的前缀和，再二分找出触地的位置，计算答案并更新直到算出其中的最大值。
### 代码
```cpp
#include<iostream>
using namespace std;
long long n,h,s,l[1145141],r[1145141],d[1145141];
int main(){
    cin>>n>>h;
    for(long long i=1;i<=n;i++){
    	cin>>l[i]>>r[i];
		d[i]=d[i-1]+l[i]-r[i-1];	
	}
    for(long long i=1;i<=n;i++){
        long long x=lower_bound(d+i+1,d+n+1,h+d[i])-d-1,y=r[x]-l[i]+h-d[x]+d[i];
        s=max(s,y);
    }
    cout<<s;
}

```

---

## 作者：Echo_Long (赞：1)

### [Glider](https://www.luogu.com.cn/problem/CF1041D)

~~大家写双指针好像都喜欢移动 $l$ 指针，那就来一篇移动 $r$ 指针的题解。~~

对于本题，移动区间显然有单调性，因为走越多的区间，高度一定不会上升，那么可以采用双指针来统计。

我们设 $ll_i$ 为一段上升气流区间的左端点，$rr_i$ 为右端点，$l$ 为左指针，$r$ 为右指针，$tot$ 为当前的高度。

那么初始条件为 $l=r=1$，$tot=m$。

当当前高度 $\le0$ 的时候，尝试移动左指针，使得区间合法（$tot\ge 0$）。

否则计入答案并移动右指针，注意在统计完区间之后还要加上剩余的单调下降高度 $tot$。

```c++
#include<bits/stdc++.h>
using namespace std;
#define inl inline
#define eb emplace_back
#define pb pop_back
#define endl '\n'
#define mid (l+r>>1)
#define ls p<<1
#define rs p<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define pii pair<int,int>
#define fi first
#define se second
#define getchar() cin.get()
#define int long long
const int N = 2e5 + 5;
const int inf = 0x3f3f3f3f;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int n , m , ll[N] , rr[N] , ans;

vector<int> vec[N];

signed main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	n = read() , m = read();
	for ( int i = 1 ; i <= n ; i ++ ) ll[i] = read() , rr[i] = read();
	int l = 1 , r = 1 , tot = m;
	while ( r <= n )
	{
		while ( l <= r && tot <= 0 ) tot += ll[l+1] - rr[l], ++ l;
		ans = max ( ans , rr[r] - ll[l] + tot );
		tot -= ll[r+1] - rr[r]; ++ r;
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：Yuexingfei_qwq (赞：0)

二分和前缀和的练手题。
## 思路  
脑子动一动就能得出最优解一定是从某一个区间的左端点开始跳。  

于是预处理前缀和，枚举每个区间的左端点，然后用 `lower_bound` 求出从目前区间的左端点开始跳的答案，最后在所有答案中取最大值即可。

## AC CODE
```cpp
#include <bits/stdc++.h>
#define el "\n"
#define sp " "
#define fi first
#define se second
#define inf 1e18
#define r0 return 0
#define int long long
#define F(i, a, b, c) for (int i = a; i <= b; i += c)
#define debug printf ("bug is in here\n")
#define TheEnd continue
#define base(s) s = sp + s
#define lcm(a, b) a * b / __gcd(a, b)
#define setp(x) fixed << setprecision(x)

using namespace std;

typedef long long ll;
typedef string str;
using ull = unsigned ll;

int n, h;
int l[210000], r[210000], s[210000], tot[210000];
int ans = 0;

signed main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	cin >> n >> h;
	F(i, 1, n, 1) {
		cin >> l[i] >> r[i];
		if (i > 1) {
			s[i] = s[i - 1] + l[i] - r[i - 1];
		}
		tot[i] = tot[i - 1] + r[i] - l[i];
	}
	F(i, 1, n, 1) {
		int x = lower_bound(s + i + 1, s + n + 1, h + s[i]) - s - 1;
		ans = std::max(ans, tot[x] - tot[i - 1] + h);
	}
	cout << ans << el;
	r0;
}
```

[AC 记录](https://codeforces.com/contest/1041/submission/303461665)

--- 
完结~~不~~散花。

---

## 作者：Disjoint_cat (赞：0)

# [CF1041D](https://www.luogu.com.cn/problem/CF1041D) [Glider](http://codeforces.com/problemset/problem/1041/D)

## 形式化题意

给定正整数 $n,h$ 以及互不相交、递增的区间 $[l_i,r_i)$。

在一个平面上，有一个点，它会从 $(x_0,h)$ 处落下，其中 $x_0$ 是任意整数。

设某个时刻这个点处于 $(x,y)$，它会执行以下操作：

- 如果 $y=0$，停止。
- 否则，如果 $\exists1\le i\le n,x\in[l_i,r_i)$，移动到 $(x+1,y)$。
- 否则，移动到 $(x+1,y-1)$。

设这个点最后移动到 $(x_1,0)$，求 $x_1-x_0$ 的最大值。

$n\le2\times10^5$。

## 题解

这题是怎么评上蓝的。完全只有黄难度。本人一眼秒了。

显然最优的情况肯定是从某一个 $x_0=l_i$ 处落下。

显然，你的出发点越靠右，终点也会越靠右。

那么想到双指针，在枚举出发点时同时维护**经过的最后一段区间**。

在移动右指针时，计算从这个区间到下一段区间的下降距离，再和当前高度判断即可。

移动左指针时，只需将高度加上少下降的距离。

时间复杂度为 $\Theta(n)$。

## 代码片段

```cpp
const int N=200005;
int n,h,l[N],r[N];
void Solve(int CASE)
{
	cin>>n>>h;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	l[n+1]=r[n+1]=INT_MAX;
	int ans=0;
	for(int i=1,j=1,k=h;i<=n;i++)
	{//i 是左指针，j 是右指针，k 是当前高度
		if(i>1)k+=l[i]-r[i-1];
		while(k>l[j+1]-r[j])k-=l[j+1]-r[j],j++;
		ans=max(ans,r[j]-l[i]+k);
	}
	cout<<ans;
}
```

---

## 作者：chlchl (赞：0)

水题 + 一眼题，建议降绿。

## Solution
显然最优答案一定从某个上升气流区间的左端点开始，因为这一段可以直接白嫖，不会影响当前高度。

那我们直接用前缀和预处理出两个数组 $sum_i,tot_i$，$sum_i$ 表示到达第 $i$ 个上升气流空间的左端点时，一共要走多少下降路；$tot_i$ 表示前 $i$ 个上升气流空间一共有多少个格子。

然后枚举从每个左端点出发，可以直接在 $sum$ 上二分找到最远能到达的地方。

最后利用 $tot$ 计算一下答案即可。这题不注意边界还是会耗一点时间的。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5 + 10;
int n;
ll h, s[N], t[N], sum[N], tot[N];

int main(){
	scanf("%d%lld", &n, &h);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld", &s[i], &t[i]);
		if(i > 1)
			sum[i] = sum[i - 1] + s[i] - t[i - 1];//sum[i] 表示飞到第 i 个上升气流区间需要下降多少格 
		tot[i] = tot[i - 1] + t[i] - s[i];
	}
	ll ans = 0;
	for(int i=1;i<=n;i++){
		int p = lower_bound(sum + i + 1, sum + 1 + n, h + sum[i]) - sum - 1;//由于从第 i 个出发，因此要额外加上（这段路程没有花费） 
		ans = max(ans, tot[p] - tot[i - 1] + h);
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

