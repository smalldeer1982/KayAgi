# Capture

## 题目描述

# 题目大意

在东西方向延伸的细长的森林里栖息着 $N$ 只动物。从森林的最左端到 $p$ 米的地点称为地点 $p$ 。若第i头动物到森林最左端的距离为 $x$（1≤i≤N）那么它就在地点 $x_i$ ，若捕获的话你可以以 $s_i$ 日元卖出。

选择两个整数 $L$ 和 $R$（L≤R），那么，从 $L$ 到 $R$ 范围内的动物就会全部被捕获。但是，买网要花费 $R$-$L$日元，所以你的利益=(被捕获的所有的除物i的合计)-($R$-$L$)日元。

若你只放一次网，得到的最大利益是多少呢？

## 说明/提示

1 ≤ $N$ ≤ 2 × $10_5$

1 ≤ x1 < x2 < ... < $x_N$ ≤ $10_15$

1 ≤ $s_i$ ≤ $10_9$

所有输入数据皆为整数.

## 样例 #1

### 输入

```
5
10 20
40 50
60 30
70 40
90 10```

### 输出

```
90```

## 样例 #2

### 输入

```
5
10 2
40 5
60 3
70 4
90 1```

### 输出

```
5```

## 样例 #3

### 输入

```
4
1 100
3 200
999999999999999 150
1000000000000000 150```

### 输出

```
299```

# 题解

## 作者：Acerkaio (赞：1)

### [题面](https://www.luogu.com.cn/problem/AT3631)
### 思路
本题类似 [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)，优先考虑 DP 做法。

可得两种情况：
1. 如果一个数加上上一个有效序列得到的结果比这个数大，那么该数也属于这个有效序列。  
2. 如果一个数加上上一个有效序列得到的结果比这个数小，那么这个数单独成为一个新的有效序列。  
by _Arahc_

设 $dp_i$ 表示以第 $i$ 个动物结尾的最大价值。

可得状态转移方程：

$dp_i=\max(s_i,dp_{i-1}+s_i-(x_i-x_{i-1}))$
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int w,v;
}a[1000401];
bool cmp(node x,node y)
{
	return x.w<y.w;	
}
int dp[100001];
signed main()
{	
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].w>>a[i].v;	
	}
	sort(a+1,a+n+1,cmp);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		dp[i]=max(a[i].v,dp[i-1]+a[i].v-(a[i].w-a[i-1].w));	
		ans=max(ans,dp[i]);
	}
	cout<<ans<<'\n';
	return 0;
}

```


---

## 作者：jiangjiangQwQ (赞：0)

### 思路
考虑动态规划，定义 $dp_i$ 为以 $i$ 为结尾的最大收益，包含 $i$ 这个位置。最终的答案为每个位置的 $dp_i$ 最大值。接下来，是如何推导转移方程。对于当前位置，要么当前面的“小弟”，就是将当前位置加入上一个位置所在的最优区间。收益为上一段的最大收益加上加入这个位置的贡献，要么另起一段，即自己为这段区间的开头，收益为 $s_i$，$dp_i$ 取两个之间最大值。 主要代码：
```cpp
cin>>n;
for(int i=1;i<=n;i++){
	cin>>x[i]>>s[i];
	dp[i]=max(s[i],dp[i-1]+s[i]-(x[i]-x[i-1]));
	ans=max(ans,dp[i]);
}cout<<ans;
```

---

## 作者：ICU152_lowa_IS8 (赞：0)

本题和[ P1115 最大子段和](https://www.luogu.com.cn/problem/P1115) 十分类似，采用的思想也差不多。

对于每一个数字，显然只有两种取法：

- 连着前面的一起取；

- 自己单飞。

从 $1$ 到 $n$ 循环一下并进行判断，输出即可。

本题解相比于其它题解，没有使用数组，算是一大优化。

贴代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,last=0,x,y;
	cin>>n;
	int ans=0,cnt=0;
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		cnt=max(y,cnt-x+last+y);//化简过后的，原式子为cnt-(x-last)+y
		ans=max(ans,cnt);
		last=x;
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：零殇 (赞：0)

#### 题意

有 $n$ 个点，每个点都有一个权值和距离，选定区间 $[L,R]$ 可以获得这个区间的权值和，花费为 $R-L$。最后得到的值为权值和减花费，求一次最多能获得多少。

#### 思路

考虑 `DP`。

对于 $dp[i]$，表示以 $i$ 为结尾的能取得的最大值。

那么，对于每一个 $dp[i]$，要么和前面的一起取，要么单独选择（因为只能选一个区间）。

如果和前面一起，那么就是 $dp[i-1]+s[i]-(x[i]-x[i-1])$。

如果单独选择，那么就是 $s[i]$。

只要选其中的最大值就好了。

即 $dp[i]=\max(s[i],dp[i-1]+s[i]-(x[i]-x[i-1]))$。

上代码：
```
#include<bits/stdc++.h>
const int N=3e5+5;
using namespace std;
int n;
long long ans;
long long x[N],s[N],dp[N];
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&x[i],&s[i]);
	for(int i=1;i<=n;i++) {
		dp[i]=max(s[i],dp[i-1]+s[i]-(x[i]-x[i-1]));
		ans=max(ans,dp[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

完结撒花~

---

## 作者：cjZYZtcl (赞：0)

## AT3631 Capture 题解
我看大佬Doveqise用的是单调队列，然而我不怎么会单调队列（太菜了awa） ，所以发一篇DP的题解给不会单调队列的萌新们（其实就是我自己awa）。

### 题目大意：

给出一段序列，让你找其中一段区间 $[l,r]$，使得

$x[l-1]+\sum^{i=l}_{r}s[i]+x[i]-x[i-1]$

的值最大。

### 思路：

对于第 $i$ 只小动物，$dp[i]$ 表示以当前点为最后一个点的区间的总价值，那么有两种情况：

1. 这只小动物也是这个区间的第一个点（也就是这个区间只有一个点）
1. 这只小动物不是这个区间的第一个点（也就是这个区间还有其他点）

那么可以发现，对于第一种情况， $dp[i]=s[i]$。

而对于第二种情况，$dp[i]=dp[i-1]+s[i]+(x[i]-x[i-1])$。

所以可以得出状态转移方程：$dp[i]=\max(s[i],dp[i-1]+s[i]+(x[i]-x[i-1]))$

由于可能由任意一只小动物作为区间结尾，所以最终答案是 $1$ 到 $n$ 间所有 $dp[i]$ 中最大的那个。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
	int x, s;
};
int f[200005];
node a[200005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
bool cmp(node x1, node y){
	return x1.x < y.x;
}
signed main(){
	int n = read(), ans = -0x3f3f3f3f;
	for(int i = 1; i <= n; i++){
		a[i].x = read();
		a[i].s = read();
	}
	sort(a + 1, a + n + 1, cmp);
	f[0] = 0;
	for(int i = 1; i <= n; i++){
		f[i] = max(a[i].s, f[i - 1] + a[i].s - (a[i].x - a[i - 1].x));
		ans = max(ans, f[i]);
	}
	write(ans);
}
```


---

## 作者：Doveqise (赞：0)

（动物保护协会表示不服系列）这道题是单调队列，（其实可以贪心），压一个pair进单调队列，枚一遍这个小动物取不取，（记得加换行！），细节下见代码↓
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<long long,int>P;
const int maxn=2e5+5;
long long n,x[maxn],s[maxn],m;
signed main(){
    priority_queue<P>q;
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&x[i],&s[i]);
        s[i]+=s[i-1];q.push(P(s[i]-x[i],i));}
    for(int i=1,flag;i<=n;i++){
        flag=1;while(flag){
            P p=q.top();
            if(p.second<i)q.pop();
            else{m=max(m,p.first-s[i-1]+x[i]);flag=0;}
        }
    }
    printf("%lld\n",m); return 0;
}
```


---

