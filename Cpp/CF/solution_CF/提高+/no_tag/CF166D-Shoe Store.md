# Shoe Store

## 题目描述

The warehouse in your shop has $ n $ shoe pairs. Each pair is characterized by two integers: its price $ c_{i} $ and its size $ s_{i} $ . We know that on this very day all numbers $ s_{i} $ are different, that is, there is no more than one pair of each size.

The shop has $ m $ customers who came at the same time. The customer number $ i $ has $ d_{i} $ money and the size of his feet equals $ l_{i} $ . The customer number $ i $ can buy the pair number $ j $ , if $ c_{j}<=d_{i} $ , and also if $ l_{i}=s_{j} $ or $ l_{i}=s_{j}-1 $ ; that is, it is necessary that he has enough money to pay for the shoes. It is also necessary that the size of his feet equals to or is less by $ 1 $ than the size of the shoes he chooses.

Your task is to sell some customers pairs of shoes (a pair per person) so as to maximize the sum of the sold pairs $ c_{j} $ that is, the profit. It is guaranteed that each customer buys no more than one pair and each pair will be bought by no more than one customer.

## 样例 #1

### 输入

```
3
10 1
30 2
20 3
2
20 1
20 2
```

### 输出

```
30
2
2 3
1 1
```

## 样例 #2

### 输入

```
3
10 4
20 5
30 6
2
70 4
50 5
```

### 输出

```
50
2
2 3
1 2
```

# 题解

## 作者：Hooch (赞：1)

[更好的体验](https://www.cnblogs.com/CTHOOH/p/18259093)

看到其它题解代码颇长，蒟蒻在此贡献一个二分图最大匹配的解法。

### 题意

鞋店里有 $n$ 双鞋子，第 $i$ 双鞋子有价格 $c_i$ 与尺码 $s_i$，保证 $s_i$ 互不相同。

有 $m$ 位顾客光临，第 $i$ 位顾客有 $d_i$ 元钱，他可以穿尺码为 $l_i$ 或者 $l_i + 1$ 的鞋子。

求出一种将鞋子卖给顾客的方法，使得获利最大，输出方案。

### 题解

观察到题目相当于将顾客与鞋子进行匹配，因为 $s_i$ 互不相同，所以每个顾客最多可以匹配两个鞋子。问题转化为：有一个二分图，左右分别有 $n, m$ 个点，左边的点有点权，右边的每个点的度数不超过 $2$，求最大带权匹配。

注意到右边每个点度数不大于 $2$，这保证了可以用匈牙利算法跑二分图最大带权匹配，若 $n, m$ 同阶那么复杂度是 $O(n)$ 的。

我们贪心地将左边的点按点权从大到小排序，然后依次匹配，要求每次匹配不能挤掉已经匹配的点，这样答案一定是最大的。

代码非常好写：

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, r, l) for (int i = r; i >= l; --i)
using namespace std;
using i64 = long long;
const int N = 1E5 + 5;
int n, m, L[N], vis[N], ans;
i64 Ans;
map<int, int> mp;
vector<int> adj[N];
struct shoe {int c, s, id;} a[N];
bool cmp(shoe a, shoe b) {return a.c > b.c;}
bool match(int x, int f) {
    if (vis[x] == f) return 0; vis[x] = f;
    for (auto v : adj[x]) {
        if (!L[v] || match(L[v], f)) return L[v] = x, 1;
    } return 0;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    rep(i, 1, n) cin >> a[i].c >> a[i].s, a[i].id = i;
    sort(a + 1, a + 1 + n, cmp);
    rep(i, 1, n) mp[a[i].s] = i;
    cin >> m;
    rep(i, 1, m) {
        int d, l; cin >> d >> l;
        auto check = [&](int k) {
            if (mp.count(k) && a[mp[k]].c <= d)
                adj[mp[k]].push_back(i);
        } ;
        check(l); check(l + 1);
    }
    rep(i, 1, n) if (match(i, i)) ++ans, Ans += a[i].c;
    cout << Ans << '\n' << ans << '\n';
    rep(i, 1, m) if (L[i]) cout << i << ' ' << a[L[i]].id << '\n';
}
```

---

## 作者：thostever (赞：0)

我们先把所有顾客按照 $l_i$ 排序，这样我们就发现每个顾客只能对后面的人造成影响。

令 $dp_{i,0/1,0/1}$ 表示排完序后的前 $i$ 个人，$s_i$ 尺码的鞋子有没有买，$s_i+1$ 尺码的鞋子有没有买时的最多挣钱数。

那么我们考虑对于 $s_i$，它与 $s_{i-1}$ 的关系有什么影响：

若 $s_{i-1}==s_i$，则 dp 转移时的后面两维是对应的。

若 $s_{i-1}==s_i-1$，则 dp 转移时 $dp_{i-1}$ 的最后一维与 $dp_i$ 的第二维是相对应的。

若 $s_{i-1}\leq s_i-2$，那么就不需要考虑对应关系了。

在转移的时候枚举第 $i$ 个人买 $l_i$、买 $l_i+1$、还是不买。

对于能不能买，我们可以开个 map 来记录一下每个尺码的鞋的价格。

用 $p$ 数组记录 dp 路径，用 $t$ 数组记录买了哪双鞋。

转移不太好写，看代码自行理解一下吧。

一个 dp 码出了儒略日的感觉。。。

~~十年 OI 一场空，不开 ll 见祖宗~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf=0x3f3f3f3f3f3f3f3f;
int n,m;
struct node
{
	int v,s,id;
}a[100010],b[100010];
bool cmp(node x,node y)
{
	return x.s<y.s;
}
map<int,int> mp,pm;
int dp[100010][2][2];
int t[100010][2][2];
int p[100010][2][2];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].v>>a[i].s;
	for(int i=1;i<=n;i++) mp[a[i].s]=a[i].v,pm[a[i].s]=i;
	cin>>m;
	for(int i=1;i<=m;i++) cin>>b[i].v>>b[i].s;
	for(int i=1;i<=m;i++) b[i].id=i;
	sort(b+1,b+m+1,cmp);
	memset(dp,-0x3f,sizeof(dp));
	dp[0][0][0]=0;
	b[0].s=-inf;
	for(int i=1;i<=m;i++)
	{
		int v1=mp[b[i].s],v2=mp[b[i].s+1];//两个价格 
		if(!v1) v1=inf; if(!v2) v2=inf;
		int i1=pm[b[i].s],i2=pm[b[i].s+1];//两个鞋的编号 
		if(b[i-1].s==b[i].s)
		{
			if(dp[i-1][0][0]>=dp[i][0][0]) dp[i][0][0]=dp[i-1][0][0],t[i][0][0]=0,p[i][0][0]=1;
			if(dp[i-1][1][0]>=dp[i][1][0]) dp[i][1][0]=dp[i-1][1][0],t[i][1][0]=0,p[i][1][0]=2;
			if(dp[i-1][0][1]>=dp[i][0][1]) dp[i][0][1]=dp[i-1][0][1],t[i][0][1]=0,p[i][0][1]=3;
			if(dp[i-1][1][1]>=dp[i][1][1]) dp[i][1][1]=dp[i-1][1][1],t[i][1][1]=0,p[i][1][1]=4;
			if(b[i].v>=v1)
			{
				if(dp[i-1][0][0]+v1>=dp[i][1][0]) dp[i][1][0]=dp[i-1][0][0]+v1,t[i][1][0]=i1,p[i][1][0]=1;
				if(dp[i-1][0][1]+v1>=dp[i][1][1]) dp[i][1][1]=dp[i-1][0][1]+v1,t[i][1][1]=i1,p[i][1][1]=3;
			}
			if(b[i].v>=v2)
			{
				if(dp[i-1][0][0]+v2>=dp[i][0][1]) dp[i][0][1]=dp[i-1][0][0]+v2,t[i][0][1]=i2,p[i][0][1]=1;
				if(dp[i-1][1][0]+v2>=dp[i][1][1]) dp[i][1][1]=dp[i-1][1][0]+v2,t[i][1][1]=i2,p[i][1][1]=2;
			}
		}
		else if(b[i-1].s==b[i].s-1)
		{
			if(dp[i-1][0][0]>=dp[i][0][0]) dp[i][0][0]=dp[i-1][0][0],t[i][0][0]=0,p[i][0][0]=1;
			if(dp[i-1][1][0]>=dp[i][0][0]) dp[i][0][0]=dp[i-1][1][0],t[i][0][0]=0,p[i][0][0]=2;
			if(dp[i-1][0][1]>=dp[i][1][0]) dp[i][1][0]=dp[i-1][0][1],t[i][1][0]=0,p[i][1][0]=3;
			if(dp[i-1][1][1]>=dp[i][1][0]) dp[i][1][0]=dp[i-1][1][1],t[i][1][0]=0,p[i][1][0]=4;
			if(b[i].v>=v1)
			{
				if(dp[i-1][0][0]+v1>=dp[i][1][0]) dp[i][1][0]=dp[i-1][0][0]+v1,t[i][1][0]=i1,p[i][1][0]=1;
				if(dp[i-1][1][0]+v1>=dp[i][1][0]) dp[i][1][0]=dp[i-1][1][0]+v1,t[i][1][0]=i1,p[i][1][0]=2;
			}
			if(b[i].v>=v2)
			{
				if(dp[i-1][0][0]+v2>=dp[i][0][1]) dp[i][0][1]=dp[i-1][0][0]+v2,t[i][0][1]=i2,p[i][0][1]=1;
				if(dp[i-1][1][0]+v2>=dp[i][0][1]) dp[i][0][1]=dp[i-1][1][0]+v2,t[i][0][1]=i2,p[i][0][1]=2;
				if(dp[i-1][0][1]+v2>=dp[i][1][1]) dp[i][1][1]=dp[i-1][0][1]+v2,t[i][1][1]=i2,p[i][1][1]=3;
				if(dp[i-1][1][1]+v2>=dp[i][1][1]) dp[i][1][1]=dp[i-1][1][1]+v2,t[i][1][1]=i2,p[i][1][1]=4;
			}
		}
		else
		{
			if(dp[i-1][0][0]>=dp[i][0][0]) dp[i][0][0]=dp[i-1][0][0],t[i][0][0]=0,p[i][0][0]=1;
			if(dp[i-1][1][0]>=dp[i][0][0]) dp[i][0][0]=dp[i-1][1][0],t[i][0][0]=0,p[i][0][0]=2;
			if(dp[i-1][0][1]>=dp[i][0][0]) dp[i][0][0]=dp[i-1][0][1],t[i][0][0]=0,p[i][0][0]=3;
			if(dp[i-1][1][1]>=dp[i][0][0]) dp[i][0][0]=dp[i-1][1][1],t[i][0][0]=0,p[i][0][0]=4;
			if(b[i].v>=v1)
			{
				if(dp[i-1][0][0]+v1>=dp[i][1][0]) dp[i][1][0]=dp[i-1][0][0]+v1,t[i][1][0]=i1,p[i][1][0]=1;
				if(dp[i-1][1][0]+v1>=dp[i][1][0]) dp[i][1][0]=dp[i-1][1][0]+v1,t[i][1][0]=i1,p[i][1][0]=2;
				if(dp[i-1][0][1]+v1>=dp[i][1][0]) dp[i][1][0]=dp[i-1][0][1]+v1,t[i][1][0]=i1,p[i][1][0]=3;
				if(dp[i-1][1][1]+v1>=dp[i][1][0]) dp[i][1][0]=dp[i-1][1][1]+v1,t[i][1][0]=i1,p[i][1][0]=4;
			}
			if(b[i].v>=v2)
			{
				if(dp[i-1][0][0]+v2>=dp[i][0][1]) dp[i][0][1]=dp[i-1][0][0]+v2,t[i][0][1]=i2,p[i][0][1]=1;
				if(dp[i-1][1][0]+v2>=dp[i][0][1]) dp[i][0][1]=dp[i-1][1][0]+v2,t[i][0][1]=i2,p[i][0][1]=2;
				if(dp[i-1][0][1]+v2>=dp[i][0][1]) dp[i][0][1]=dp[i-1][0][1]+v2,t[i][0][1]=i2,p[i][0][1]=3;
				if(dp[i-1][1][1]+v2>=dp[i][0][1]) dp[i][0][1]=dp[i-1][1][1]+v2,t[i][0][1]=i2,p[i][0][1]=4;
			}
		}
	}
	//下面是输出部分 
	int f,maxn=-inf;
	if(dp[m][0][0]>=maxn) maxn=dp[m][0][0],f=1;
	if(dp[m][1][0]>=maxn) maxn=dp[m][1][0],f=2;
	if(dp[m][0][1]>=maxn) maxn=dp[m][0][1],f=3;
	if(dp[m][1][1]>=maxn) maxn=dp[m][1][1],f=4;
	cout<<maxn<<"\n";
	int sum=0,ff=f;
	for(int i=m;i>=1;i--)
	{
		int x,y;
		if(f==1) x=0,y=0;
		if(f==2) x=1,y=0;
		if(f==3) x=0,y=1;
		if(f==4) x=1,y=1;
		if(t[i][x][y]) sum++;
		f=p[i][x][y];
	}
	cout<<sum<<"\n";
	f=ff;
	for(int i=m;i>=1;i--)
	{
		int x,y;
		if(f==1) x=0,y=0;
		if(f==2) x=1,y=0;
		if(f==3) x=0,y=1;
		if(f==4) x=1,y=1;
		if(t[i][x][y]) cout<<b[i].id<<" "<<t[i][x][y]<<"\n";
		f=p[i][x][y];
	}
	return 0;
}
```


---

