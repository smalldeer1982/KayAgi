# [ABC325D] Printing Machine

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc325/tasks/abc325_d

$ 1 $ から $ N $ までの番号が付けられた $ N $ 個の商品がベルトコンベア上を流れています。 ベルトコンベアには印字機が取り付けられており、商品 $ i $ は今から $ T_i $ \[μs\] 後に印字機の範囲に入り、その $ D_i $ \[μs\] 後に印字機の範囲から出ます。

キーエンスの印字機は、印字機の範囲内にある商品 $ 1 $ つに一瞬で印字することができます（特に、商品が印字機の範囲に入る瞬間や範囲から出る瞬間に印字することも可能です）。 ただし、$ 1 $ 度印字すると、次に印字するまでに $ 1 $ \[μs\] のチャージ時間が必要です。 印字機が印字をする商品とタイミングをうまく選んだとき、最大で何個の商品に印字することができますか？

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ T_i,D_i\ \leq\ 10^{18} $
- 入力は全て整数
 
### Sample Explanation 1

以下、今から $ t $ \\\[μs\\\] 後のことを単に時刻 $ t $ とよびます。 例えば、次のようにして $ 4 $ 個の商品に印字することができます。 - 時刻 $ 1 $ : 商品 $ 1,2,4,5 $ が印字機の範囲に入る。商品 $ 4 $ に印字する。 - 時刻 $ 2 $ : 商品 $ 3 $ が印字機の範囲に入り、商品 $ 1,2 $ が印字機の範囲から出る。商品 $ 1 $ に印字する。 - 時刻 $ 3 $ : 商品 $ 3,4 $ が印字機の範囲から出る。商品 $ 3 $ に印字する。 - 時刻 $ 4.5 $ : 商品 $ 5 $ に印字する。 - 時刻 $ 5 $ : 商品 $ 5 $ が印字機の範囲から出る。 $ 5 $ 個の商品すべてに印字することはできないため、答えは $ 4 $ です。

## 样例 #1

### 输入

```
5
1 1
1 1
2 1
1 2
1 4```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1 1
1000000000000000000 1000000000000000000```

### 输出

```
2```

## 样例 #3

### 输入

```
10
4 1
1 2
1 4
3 2
5 1
5 1
4 1
2 1
4 1
2 4```

### 输出

```
6```

# 题解

## 作者：FL_sleake (赞：5)

### 题意简述

给定 $n$ 个球，$10^{100}$ 个格子，第 $i$ 个球需要放在 $x_i,x_i+y_i$ 格子中的某一个。已经放过球的格子不能再放。问最多能放多少个球。

### 解题思路

首先考虑一种贪心策略。

对于格子 $T=1,2,3…$，若此时有球能放，取一个 $x_i+y_i$ 最小的放进去。因为 $x_i+y_i$ 更大的球**有可能**可以放在更后面，这一定比将它放在 $T$ 更优。

但这样做会 TLE。考虑先将球对于 $x_i$ 排个序，$x_i$ 相同的按照 $x_i+y_i$ 排序。我们在将 $T$ 扫过去的过程中，很多格子其实都放不了球，白白浪费了时间。所以我们用一个优先队列 $q$ 记录当前等待放入的球，如果 $q$ 空了，就将 $T$ 跳到下一个球的可放置的起始位置。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
vector<pair<int,int> > a;
priority_queue<int,vector<int>,greater<> > q;
signed main(){
	cin>>n;
	a.push_back({-1,0});
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		a.push_back({x,x+y});
	}
	sort(a.begin(),a.end());
	int cnt=0,ans=0;
	for(int T=1;;T++){
		if(q.empty()){
			if(cnt==n) break;
			T=a[++cnt].first;
			q.push(a[cnt].second);
		}
		while(cnt<=n-1&&a[cnt+1].first==T) q.push(a[++cnt].second);
		while(!q.empty()&&q.top()<T) q.pop();
		if(!q.empty()) ans++,q.pop();
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：FireRain (赞：3)

# 思路

首先由一个很显然的贪心当在同一时刻内在打印机里面的物品，显然现将最早退出打印机的打印最优。

那么考虑用一个优先队列维护。枚举一个 $i$，表示将所有的 $t_j = t_i$ 的 $t_j + d_j$ 加到优先队列里面，然后一直用一个 $now$ 记录当前时间即可，然后再将 $i \leftarrow j - 1$。

需要注意的是，当 $now$ 变到下一个时间时就先不计算答案了，先将那一时刻的物品加入进优先队列即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 2e5 + 10,inf = (int)(2e18) + 10;
int n,ans;
priority_queue<int,vector<int>,greater<int>> q;

struct point{
	int l;
	int r;
	
	friend bool operator <(const point &a,const point &b){
		return a.l < b.l;
	}
}arr[N];

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

signed main(){
	n = read();
	for (re int i = 1;i <= n;i++){
		int x,l;
		x = read();
		l = read();
		arr[i] = {x,x + l};
	}
	arr[n + 1] = {inf,inf};
	sort(arr + 1,arr + n + 1);
	for (re int i = 1;i <= n;i++){
		int j = i,now = arr[i].l;
		while (j <= n && arr[j].l == now) q.push(arr[j++].r);
		while (!q.empty() && now < arr[j].l){
			int t = q.top();
			q.pop();
			if (t >= now){
				now++;
				ans++;
			}
		}
		i = j - 1;
	}
	printf("%lld",ans);
	return 0;
}
```

---

