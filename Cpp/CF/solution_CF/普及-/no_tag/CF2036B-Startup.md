# Startup

## 题目描述

Arseniy came up with another business plan — to sell soda from a vending machine! For this, he purchased a machine with $ n $ shelves, as well as $ k $ bottles, where the $ i $ -th bottle is characterized by the brand index $ b_i $ and the cost $ c_i $ .

You can place any number of bottles on each shelf, but all bottles on the same shelf must be of the same brand.

Arseniy knows that all the bottles he puts on the shelves of the machine will be sold. Therefore, he asked you to calculate the maximum amount he can earn.

## 说明/提示

In the first test case, Arseniy has $ 3 $ shelves in the vending machine. He can place, for example, two bottles of the brand $ 2 $ on the first shelf and a bottle of the brand $ 1 $ on the second shelf. Then the total cost of the bottles would be $ 6 + 7 + 15 = 28 $ .

In the second test case, he has only one shelf. It is not difficult to show that the optimal option is to place a bottle of the brand $ 1 $ on it. Then the total cost will be $ 15 $ .

In the third test case, he has as many as $ 6 $ shelves, so he can place all available bottles with a total cost of $ 7 + 5 = 12 $ .

## 样例 #1

### 输入

```
4
3 3
2 6
2 7
1 15
1 3
2 6
2 7
1 15
6 2
1 7
2 5
190000 1
1 1000```

### 输出

```
28
15
12
1000```

# 题解

## 作者：Yxy7952 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF2036B)

建议评橙。

## 思路

这是道非常简单的贪心题。

根据这句话：
>他可以将任意数量的瓶子放到货架上，但同一货架上的瓶子必须来自同一个品牌。

显然，我们只需要把所有品牌的商品的价值之和，从大到小排个序，选取前 $n$ 个品牌的商品放在货架上，这时候，收益一定是最大的。

因为太过简单，直接展示代码。
## 代码

$m$ 表示品牌的个数。

$t_{i}$ 表示第 $i$ 个品牌如果放在货架上的收益总和。

$sum$ 表示总收益。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n,k;
ll b[200005],c[200005],t[200005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		ll m=0,sum=0;
		for(int i=0;i<=200005;i++) t[i]=0;//初始化为 0。
		for(int i=1;i<=k;i++){
			cin>>b[i]>>c[i];
			t[b[i]]+=c[i];
			m=max(m,b[i]);
		}
		sort(t+1,t+m+1);//这里从小到大排序
		for(int i=m;i>=m-n+1;i--) sum+=t[i];
    	//因为从小到大排序，这里从后往前找寻前 n 个物品。 
		cout<<sum<<"\n";
	}
	return 0;
}
```

---

## 作者：zhang_kevin (赞：2)

首先我们发现一个架子上只限制放置种类，没有限制个数。因此得到贪心策略：

- 如果一个架子上放第 $i$ 种瓶子，则把所有这种瓶子放在这个架子上（减少架子的使用数量）。
- 在满足上一条的前提下，把同种类最多的优先放（尽可能多的瓶子）。

于是可以开一个桶，记录每种瓶子的个数。把这个桶按照从大到小排序后，按顺序计算答案即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001], box[200001];
inline bool cmp(int x, int y){
    return x > y;
}
inline void Solve(){
    memset(box, 0, sizeof(box));
    int n, k;
    cin >> n >> k;
    for(int i = 1, b, c; i <= k; i++){
        cin >> b >> c;
        box[b] += c;
    }
    sort(box+1, box+1+k, cmp);
    long long ans = 0;
    for(int i = 1; i <= n; i++){
        ans += box[i];
    }
    cout << ans << endl;
    return;
}
int main(){
	int t;
    cin >> t;
    while(t--){
        Solve();
    }
    return 0;
}
```

---

## 作者：GreenMelon (赞：1)

难度橙。

对于 $t$ 组数据，可以设个大小为 $2\cdot10^5$ 的桶数组 $a$，每次输入 $b_i$ 和 $c_i$ 时 $a_{b_i}$ 就加一下 $c_i$。最后从 $1$ 到 $k$ 依次**降序排序**，前 $n$ 大的数求和就行。

放心大胆模拟，不会超时。

**记得每次清空 $a$。**


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int a[200005];
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(a, 0, sizeof(a));
		int n, k, ans=0;
		cin>>n>>k;
		for(int i=1;i<=k;i++){
			int b, c;
			cin>>b>>c;
			a[b]+=c;
		}
		sort(a+1, a+1+k, [](int x, int y){return x>y;});
		for(int i=1;i<=n;i++){
			ans+=a[i];
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

[AC 记录](https://codeforces.com/problemset/submission/2036/289929490)

---

## 作者：Scean_Tong (赞：1)

## CF2036B Startup 题解

### 题意

有 $n$ 个货架和 $k$ 个瓶子，每个瓶子有品牌 $b_i$ 和价格 $c_i$。每个货架上可以放任意数量的相同品牌的瓶子。问能赚的最大金额。

### 思路

考虑贪心。

定义 $f_i$ 表示品牌为 $i$ 的瓶子一共的金额，求出所有 $f_i$ 后从大到小排序取前 $n$ 个牌子的 $f_i$ 求和。

多测记得清空 $f$ 数组。

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T=1;
const int maxn=2e5+7;
int mp[maxn],n,k;
bool cmp(int a,int b){
	return a>b;
}
void solve(){
	cin>>n>>k;
	for(int i=1,u,v;i<=k;i++){
		cin>>u>>v;
		mp[u]+=v;
	}
	sort(mp+1,mp+k+1,cmp);
	cout<<accumulate(mp+1,mp+n+1,0)<<'\n';
	for(int i=1;i<=k;i++){
		mp[i]=0;
	}
}
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：Sakura_Emilia (赞：1)

# Question

给出 $n$ 个货架，$k$ 个不同品牌的瓶子。在同一货架上只能放一种品牌瓶子，但数量不限。给定 $k$ 个瓶子的品牌和价值，问如何放置可以使得 $n$ 个货架上总价值最大？

多组测试数据。每组测试数据第一行给出 $n$ 和 $k$，第二行给定 $k$ 个数，对应 $k$ 个瓶子所属的品牌编号；第三行给定 $k$ 个数，对应 $k$ 个瓶子的价值。

# Solution

注意审题。直接使用贪心即可，使用一个 `map` 来统计各个品牌下瓶子的价值总和。最后从 `map` 中取出所有的品牌，按照其价值总和进行排序。选取价值最大的前 $n$ 个值即可。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;
const int N = 2e6 + 8;

int T, n, k, b, c;
int x[N], idx, ans;
map<int, int> mp;

inline void solve() {
    mp.clear();
    ans = idx = 0;

    cin >> n >> k;
    for(int i = 1; i <= k; i++) {
        cin >> b >> c;
        mp[b] += c;
    }

    for(auto t: mp)
        x[++idx] = t.second;
    sort(x + 1, x + 1 + idx, greater<>());

    for(int i = 1; i <= n and i <= idx; i++)
        ans += x[i];
    cout << ans << endl;
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
```

---

## 作者：linch (赞：1)

## Problem
你有 $n$ 个货架和 $k$ 个瓶子，每个瓶子属于一种品牌，并有一个价值。你可以在一个货架上摆放相同品牌的瓶子。求出你摆放瓶子总价值的最大值。

## Solution
考虑贪心。

一个货架上摆的瓶子数量没有限制，所以我们在每个货架上都要放尽可能多的瓶子，也就是把同一个品牌的全部放上去。然而，最多能放 $n$ 个品牌，那就贪心地选择价值之和最高的 $n$ 个品牌放上去。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int t, n, k, a[maxn];//a 数组存储每个品牌价值和。
int main() {
	cin >> t;
	while(t--) {
		cin >> n >> k;
		for(int i = 1; i <= k; i++) {
			a[i] = 0;
		}//注意清空。
		for(int i = 1; i <= k; i++) {
			int b, c;
			cin >> b >> c;
			a[b] += c;
		}
		sort(a + 1, a + k + 1, greater<int>());//从大到小排序。
		int sum = 0;
		for(int i = 1; i <= min(n, k); i++) {//注意处理 n>k 的情况，防止越界。
			sum += a[i];
		}
		cout << sum << "\n";
	}
	return 0;
}
```

---

## 作者：jess1ca1o0g3 (赞：1)

## 思路

非常简单。由于最多选 $n$ 个品牌的汽水，所以要让利益最大化，优先选价值高的品牌。统计每个品牌的价值，从大到小选过来就行。

## 代码

```cpp
#include<bits/stdc++.h>
#define i64 long long
#define L(a,b,c,d) for(int a=b;a<=c;a+=d)
#define R(a,b,c,d) for(int a=b;a>=c;a-=d)

using namespace std;
const int N=2e5+5,M=998244353;

void solve();
int T,n,k,a[1005],ans,x,y;
map<int,int> m;
vector<int> b;

signed main(){
  scanf("%d",&T);
  while(T--) solve();
  return 0;
}

void solve(){
  scanf("%d%d",&n,&k);
  m.clear();
  L(i,1,k,1){
    scanf("%d%d",&x,&y);
    m[x]+=y;
  }
  b.clear();
  for(map<int,int>::iterator it=m.begin();it!=m.end();it++){
    b.push_back(it->second);
  }
  sort(b.begin(),b.end());
  ans=0;
  for(int i=b.size()-1;i>=0;i--){
    if(!n) break;
    ans+=b[i];
    n--;
  }
  printf("%d\n",ans);
}
```

---

## 作者：xcms (赞：0)

# CF2036B 题解

本题考虑使用桶来求解，考虑到 $1\le b_i\le k$，而 $1\le k\le 2\times 10^5$，所以只需要开一个桶数组并从大到小排序，然后求和即可。

坑点在于初始化上，注意每次循环之前把桶数组清空。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int b[N],c[N],f[N];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=max(n,k);i++)f[i]=0;//初始化数组 
		for(int i=1;i<=k;i++)cin>>b[i]>>c[i];
		int ans=0;
		for(int i=1;i<=k;i++)f[b[i]]+=c[i];//桶排 
		sort(f+1,f+1+k,greater<int>());//排序 
		for(int i=1;i<=n;i++)ans+=f[i];//求答案 
		cout<<ans<<"\n"; 
	}
	return 0;
}
```

---

## 作者：YuYuanPQ (赞：0)

考虑贪心：因为单个货架上不限放多少，所以将所有同品牌的瓶子都放上去。

那么要求的最大值显然是：将每个品牌的瓶子总价值从大到小排序，前 $n$ 个的和。

## Code
[Link](https://codeforces.com/contest/2036/submission/289491819)

---

## 作者：wuyouawa (赞：0)

### 题目大意

阿尔谢尼想出了一个新的商业计划——在自动售货机中出售汽水！为此，他购买了一台有 $ n $ 个架子的机器，以及 $ k $ 瓶饮料，其中第 $ i $ 瓶饮料由品牌索引 $ b_i $ 和价格 $ c_i $ 特征。

你可以在每个架子上放置任意数量的瓶子，但同一架子上的所有瓶子必须是同一品牌。

阿尔谢尼知道他放在机器架子上的所有瓶子都会被售出。因此，他请你计算他能赚取的最大金额。

### 思路

可以用结构体排序实现。

就是每次先用记录品牌的数组标记那些是已有的，如果未有就加进去，如果有了，就用原来的价格加上现在的价格，就算总价格。

最后按从大到小排个序，因为要尽量选大的，然后加上前 $\min(n,cnt)$ 个，其中 $cnt$ 是不同品牌的数量，因为有可能多了，也有可能不够。

细节

- 多测，注意清空。

### CODE

[提交记录及代码](https://codeforces.com/problemset/submission/2036/289728592)

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2036B)

一道贪心题。

因为一层货架上可以放无限个罐头，且只能是同一种类的。所以我们不可能在一层货架上摆若干个第 $x$ 类罐头，又在另一层货架上摆若干个第 $x$ 类罐头。

我们可以将每一种类的罐头美味度之和求出后从小到大排序，取前 $n$ 个最大的即是答案。

### Code
```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

const long long MOD1 = 998244353;
const long long MOD2 = 1000000007;
const long long MOD3 = 1000000009;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	#define SZ(x) (x.size())
	#define fst first
	#define snd second
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
const int K = 200005;
ll T, n, k, ans;
int sum[K];
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> T;
	while (T--) {
		cin >> n >> k;
		ans = 0;
		for (int i = 1; i <= k; i++) sum[i] = 0;
		for (int i = 1; i <= k; i++) {
			int a, b;
			cin >> a >> b;
			sum[a] += b;
		}
		sort(sum + 1, sum + 1 + k, greater <int>());
		for (int i = 1; i <= Min(n, k); i++) ans += sum[i];
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：xingshuyan000 (赞：0)

[题目传送门 1（洛谷 CF2036B）](https://www.luogu.com.cn/problem/CF2036B)

[题目传送门 2（Codeforces 2036B）](https://codeforces.com/problemset/problem/2036/B)

[我的博客本文链接，~~欢迎点赞~~](https://www.cnblogs.com/xingshuyan/articles/18523103)

# 题目大意

某人有 $n$ 个货架和 $k$ 个瓶子的自动售货机，第 $i$ 个瓶子的品牌指数和售价分别为 $b_i,c_i$，每个货架上只能放同一种品牌的瓶子任意多个，而且每个瓶子都会被卖掉。求他卖出能获得的最大金额。

# 题目分析

这是一个比较简单的贪心。

我们可以预先处理出每一种品牌所有的瓶子的总金额，这里可以用一个 unordered_map 来存，把每个 $b_i$ 放在 map 的第一维，然后对于这个 $b_i$，map 的第二维存总金额。然后可以把第二维的数据存入一个 vector，并对 vector 从大往小排序，这个 vector 的大小记为 $s$。接着，从大往小取出来前 $n$ 个的总金额（如果 $s < n$，那么有多少取多少），可以把每个 $b_i$ 的总金额记为 $sum_j$，答案就是 $sum_j$ 的总和，即 $ans=\sum _j^{\min(n,s)}sum_j$，其中，$ans$ 为最终的答案。

单组数据的时间复杂度为 $O(k+s+s\log s+\min(n,s))$，在最坏情况下，$s$ 和 $\min(n,s)$ 都等于 $k$，所以总的时间复杂度为 $O(k \log k)$，而本题中保证 $1 \le  \sum n,\sum k \le 2\times 10^5$，可以通过此题。

# Code

~~（码风良好，适宜阅读）~~


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 50;
struct node{
	int b, c;
}a[N];
void solve()
{
	int n, k;
	cin >> n >> k;
	unordered_map<int, int> mp;
	for(int i = 1; i <= k; i ++)
	{
		cin >> a[i].b >> a[i].c;
		mp[a[i].b] += a[i].c; //把 b 对应的 c 加到 map 中
	}
	vector<int> sum;
	for(auto &i : mp) sum.push_back(i.second); //把 map 中的 c 添加到 sum 中
	sort(sum.rbegin(), sum.rend()); //对 sum 从大到小排序
	long long ans = 0;
	for(int i = 0; i < min(n, (int)sum.size()); i ++)
	{
		ans += sum[i]; //累加答案
	}
	cout << ans << "\n"; //输出
	return ;
}
int main()
{
	cin.tie(0) -> sync_with_stdio(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Jason_Ming (赞：0)

### 思路

我们可以注意到，把同一品牌的汽水放在同一个货架上一定比分开放在不同的货架上更优。

所以我们可以把同品牌的汽水的价值都加起来，作为这一个品牌的**品牌价值**。

那么问题就转化为，在所有的品牌中，**品牌价值**最大的前 $n$ 个品牌的**品牌价值**的和是多少。

排序再求和即可。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int t,n,k,p=1,ans;
int b[200005],c[200005],f[200005];

bool cmp(int x,int y)//从大到小排序 
{
	return x>y;
}

int main()
{
	cin>>t;
	while(t--)//本题多测 
	{
		memset(f,0,sizeof(f));//多测要清空 
		ans=0;
		cin>>n>>k;
		for(int i=1;i<=k;i++)
		{
			cin>>b[i]>>c[i];
			f[b[i]]+=c[i];
		}
		sort(f+1,f+k+1,cmp);//品牌的编号最大不会超过 k 
		for(int i=1;i<=n;i++)
		{
			ans+=f[i];
		}
		cout<<ans<<endl;
	}
}
```


**拒绝抄袭，从我做起。**

---

## 作者：long_long__int (赞：0)

# 题目翻译
阿森尼想出了另一个商业计划——从销售机器上销售苏打水！为此，他购买了一台带有 $N$ 个架子和 $K$ 个瓶子的机器，其中第 $i$ 个瓶子的品牌是 $B_i$，成本是 $C_i$。

您可以在每个架子上放置任意数量的瓶子，但同一架子上的所有瓶子都必须是同一品牌的。

阿森尼知道，他放在机器架子上的所有瓶子都会被卖掉。因此，他要求你计算他能赚的最大金额。
# 题目解法
显而易见，做法是贪心。因为每个架子上可以放无限个瓶子，所以只需要计算一下每个品牌能卖出的总价钱，再从大到小排个序，用变量把从能卖出价钱最高的品牌到第 $N$ 高的加起来就行了。另外，记得清空数组。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
struct node{
	int b,c;
}g[10050];
int money[205000//每个品牌能卖的钱
bool cmp(int a,int b) {return a>b;}
void work(){
	memset(money,0,sizeof money);
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>g[i].b>>g[i].c;
		money[g[i].b]+=g[i].c;
	}
	sort(money+1,money+n+1,cmp);
	int ans=0;
	for(int i=1;i<=n;i++) ans+=money[i];
	cout<<ans<<"\n";
}
int main(){
	int T;
	cin>>T;
	while(T--) work();
	return 0;
}
```

---

