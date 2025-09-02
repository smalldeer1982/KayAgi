# Microtransactions (easy version)

## 题目描述

有 $n$ 种物品，对于第 $i$ $(1\le i \le n)$ 个物品，你需要买 $k_i$ 个（你每次购物是在**晚上**），每个物品在非打折日买是 $2$ 块钱，在打折日买是 $1$ 块钱，每天**早上**你可以赚 $1$ 块钱，一共有 $m$ 个打折日，在第 $d_i$ 天第 $t_i$ 种物品打折，问最少需要多少天可以买完你需要的物品。注意，你每天可以买任意多数量以及种类的商品（只要你有足够的余额）。

## 样例 #1

### 输入

```
5 6
1 2 0 2 0
2 4
3 3
1 5
1 2
1 5
2 3
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5 3
4 2 1 3 2
3 5
4 2
2 5
```

### 输出

```
20
```

# 题解

## 作者：UncleSam_Died (赞：1)

### 解题思路
很容易知道，买完所有东西的最小花费是 $\sum_i^n k_i$，最大花费是 $\sum_i^n (k_i\times 2)$，所以，我们可以得出，买完所有物品的最小天数是 $\sum_i^n k_i$，最大天数是 $\sum_i^n (k_i\times 2)$，因此，我们只需要在这个区间内求出一个能够买完所有物品的最小天数。

随着时间的增长，能够买到的物品的数量也会增长，即在 $t_i$ 天内能够买到所有物品，那么在 $t_{i+1}$ 天之内肯定能够买到所有的物品。显然，暴力枚举区间 $[ \sum_i^n k_i,\sum_i^n (k_i\times 2) ]$ 会超时，那么我们可以考虑二分答案来求得最小天数，即，每次找到区间 $[l,r]$ 的中点 $mid$，判断在这个天数的时候能否买到所有的物品，如果能，继续查找区间 $[l,mid - 1]$；如果不能，查找区间 $(mid,r]$。

对于二分答案中的 `Check` 函数（判断当前决策是否可行的函数），我们可以知道，当前的钱数 $M$ 等于天数 $T$，那么我们找到从第一天到第 $T$ 天中的每一个打折的日期，然后判断一下，当前的钱数能否把这个物品买完，如果不能，就买一部分；如果能，那么判断钱是否有剩余，如果有的话，就加入剩余的钱的数量 $RM$ 中。当我们判断完打折天数后，我们还需要判断当前剩余的钱能不能够买得到剩余的在打折的时候没有买的物品，如果不能，返回 `false`，能得话，返回 `true`。

以上是本题的思路，代码就不贴了。

---

## 作者：Ak_hjc_using (赞：0)

### 思路
  1. 贪心\
    内容： 每一个商品都在最后一个打折日买。\
    证明：如果随便花前面天数挣的钱，可能会使打折日靠前的物品无法享受到优惠，故只要由当前日期从后往前花（同时判断这天挣的钱是否被花过）就可以了。
      
  2. 二分\
    内容：二分最小的天数，最后的答案就是 $r$。\
    证明：二分可以非常容易发现如果 $mid$ 天能购买所有商品，那么 $mid + 1$ 天一定也可以，故本题有单调性，故可以使用二分答案。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;

#define int long long 
int n, m;
int a[N], d[N], t[N];
int Day[N];
vector<int> G[N];
bool vis[N];
int Max_Day = 0;
bool check(int x)
{
	int ans = 0;
	for (int i = 1;i <= Max_Day;i ++) G[i].clear(), Day[i] = 0;
	for (int i = 1;i <= m;i ++)
	{
		if (d[i] <= x)
		{
			Day[t[i]] = max(Day[t[i]], d[i]);
		}
	}
	for (int i = 1;i <= n;i ++)
	{
		if (Day[i] != 0)
		{
			G[Day[i]].push_back(i);
		}	
		else
		{
			ans += a[i] + a[i];
		}
	}
	int cnt = 0; // 现在的钱数
	for (int i = 1;i <= x;i ++)
	{
		cnt ++; // 每天赚一块钱
		if (G[i].size() >= 1)
		{
			for (int j = 0;j < G[i].size();j ++)
			{
				int num = G[i][j];
				if (cnt < a[num] && i == x)  // 没钱买，并且是最后一天了
				{
					return false;
				}
				else if (cnt < a[num]) // 无法买完
				{
					ans += 2 * (a[num] - cnt);
					cnt = 0; // 剩余的用2元钱买
				}
				else
				{
					cnt -= a[num]; // 直接买了
				}
			}
		}
	}
	return cnt >= ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1;i <= n;i ++) cin >> a[i];
	for (int i = 1;i <= m;i ++) cin >> d[i] >> t[i], Max_Day = max(Max_Day, d[i]);
	int l = 0, r = 1e5 + 1; // 二分答案
	while (l + 1 < r)
	{
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid;
	}
	cout << r << endl;
	return 0;
}

```

---

## 作者：Priestess_SLG (赞：0)

首先问题具有单调性，因此考虑二分答案。设当前二分到的答案为 $p$，则对于每一个商品考虑贪心：

+ 前 $p$ 天内没有活动，那么最后一天以 $2$ 的价格购买。
+ 前 $p$ 天内有活动，那么在最后一个活动日以 $1$ 的价格购买，剩下部分以 $2$ 的价格购买。

时间复杂度为 $O(n\log n)$，可以简单通过问题。

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define eb emplace_back
#define pb push_back
#define int long long
#define F(i,x,y) for(int i=x;i<=y;++i)
#define G(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
const int N=500100;
vector<int>z[N];
int k[N],d[N],t[N],b[N],n,m;
int chk(int p){
    F(i,1,N-1)b[i]=0,z[i].clear();int s=0;
    F(i,1,m)if(d[i]<=p)b[t[i]]=max(b[t[i]],d[i]);
    F(i,1,n){
        if(!b[i])s+=k[i]*2;
        else z[b[i]].eb(i);
    }
    int rem=0;
    for(int i=1;i<=p;++i){
        ++rem;
        if(z[i].size())for(auto &j:z[i]){
            if(rem<k[j]&&i==p)return 0;
            else if(rem<k[j])s+=2*(k[j]-rem),rem=0;
            else rem-=k[j];
        }
    }
    return rem>=s;
}
signed main(){
    cin>>n>>m;
    F(i,1,n)cin>>k[i];
    F(i,1,m)cin>>d[i]>>t[i];
    int l=1,r=N-100,best=-1;
    while(l<=r){
        int mid=l+r>>1;
        if(chk(mid))best=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<best<<'\n';
    return 0;
}
```

---

## 作者：FlyPancake (赞：0)

# [CF1165F1 Microtransactions (easy version)](https://www.luogu.com.cn/problem/CF1165F2) 题解

[加强版，只有数据范围不一样。](https://www.luogu.com.cn/problem/CF1165F2)

核心思想：贪心 and 二分。

## Ideas


贪心：在第 $i$ 个商品的最后一个打折日买所有能买的。

证明：若要买商品 $i$ 时，不管挑哪一个打折日，对购买 $i$ 花费的金额不会造成什么影响。但如果在第一个打折日就花了钱去买第 $i$ 个东西，有可能会让本来可以打折购买的商品 $j$ 没钱买，答案会更劣。所以将 $i$ 放在最后一天买最好。

所以对打折日排序，按打折日从大到小的顺序买对应的商品即可。剩下的商品就按原价买。

二分答案，找天数最小值。

**细节：** 因为 $sum$ 总和最大值为 $10^3$，二分 $mid$ 会大于其值，所以数组最好开大点。

## Code

```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4+5;

int k[N], now[N], sum, n, m;
vector<int> sale[N];

bool check(int x){
    int nx = x, nsum = sum, left = 0;
    for(int i=1; i<=n; i++) now[i] = k[i];
    for(int i=x; i>=1; i--){
		for(int j=0; j<sale[i].size(); j++)
			while(now[sale[i][j]] && nx)
				nx--, nsum--, now[sale[i][j]]--;
        if(nx>=i) nx--, left++;
    }
    return left>=nsum*2; // 是否能原价买下剩下的
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        cin>>k[i];
        sum += k[i];
    }
    for(int i=1; i<=m; i++){
        int x, y; cin>>x>>y;
        sale[x].push_back(y);
    }
    int l=sum, r=sum*2;
    while(l<r){
        int mid = (l+r)>>1;
        if(check(mid)) r = mid;
        else l = mid+1;
    }
    cout<<l;
    return 0;
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [Microtransactions (easy version)](https://www.luogu.com.cn/problem/CF1165F1)
## 思路分析
我们可以模拟 Ivan 在第几天可以完成任务，对于 Ivan 想要购买的物品数量 $k$，最少需要 $k$ 天，最大要 $2\times k$ 天，如果直接遍历的话，就会 TLE，所以使用二分枚举可行的天数。

在二分 ```check``` 函数中，我们在后往前枚举天数的时候是要将打折的物品都买掉。最后判断我们多余的钱能否将剩余的物品给买完即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=1e3+1;
int n,m,a[N],b[N],sum;
vector<int>v[N];//v[i] 表示第 i 天打折的种类编号
bool check(int x,int y){
	int res=x,f=0;//res 表示当前的钱数
	for(R i=1; i<=n; i++)b[i]=a[i];
	for(R i=x; i; i--){
		R tmp=v[i].size();//获取当天打折的物品数量
		for(R j=0; j<tmp; j++)
			while(b[v[i][j]]&&res)
				res--,y--,b[v[i][j]]--;
		if(res>=i)res--,f++;
	}
	return f>=y*2;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
   	//sum 统计需要购买的物品总数
	for(R i=1; i<=n; i++)cin>>a[i],sum+=a[i];
	for(R i=1,x,y; i<=m; i++)cin>>x>>y,v[x].push_back(y);
	int l=sum,mid,r=sum*2;
	while(l<r){
		mid=l+r>>1;
		if(check(mid,sum))r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
//已加防抄袭处理，误抄
```

---

