# Microtransactions (hard version)

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

## 作者：GoWithTheFlow (赞：3)

### 思路分析
首先，如果假定要买物品总数为 $sum$，则所需天数的取值范围应该在 $[sum,2 \times sum]$ 这个区间之内。如果采用枚举这个区间的每一天的方法来求解的话，显然会超时。因此我们考虑使用二分天数。二分中的 $check$ 函数我们需要设计一种贪心策略来计算出在 $mid$ 天购买 $sum$ 件物品需要的最少金额 $money$，令它与 $2 \times mid$ 进行比较，如果前者小于后者，则令 $r = mid$，反之，则令 $l = mid$。
### 贪心策略
可以想到的是，我们可以选择只在一种打折商品的**最后一次打折日**购买，在此之前一直存钱。且在执行玩上面操作后，对于剩余的商品，我们可以在**集中在最后一天**购买剩余的所有商品，而在之前的几天只在一个物品的打折日的最后一天购买该打折物品（简单来说就是，前期攒钱，直到遇到某一物品最后一次打折或最后一天才购买）。如此，我们就能保证计算出的 $money$ 是最少的。
如果没有看懂，可以结合下面的代码理解。
### 预处理分析
```cpp
int n,m,cnt[N],sum;
int dis[N],pos[N]; 
vector<int> q[N]; 
```
$cnt[N]$ 为物品需求数，$sum$ 为需求总数，$dis[N]$ 存储的是物品种类，方便按最后打折日排序，$pos[N]$ 存储每种物品小于 $x$ 天的最大打折日，$q[N]$ 存储每种物品的所有打折日。
### AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 400000;
int n,m,cnt[N],sum;
int dis[N],pos[N]; 
vector<int> q[N];  //存储打折日 
bool compare(int a, int b) {
    return a > b;  
}
bool cmp(int a,int b)
{
	return pos[a] < pos[b];
}
bool check(int x)
{
	//求pos 
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j < q[i].size(); j++)
			if(q[i][j] <= x)
			{
				pos[i] = q[i][j];
				break;
			}
	}
	//排序
	sort(dis+1,dis+1+n,cmp);
	//遍历需要的物品 
	int money = 0,last = 0,num = 0;  // money是这些天赚的钱，last是之前天数中花的钱，num是集中到最后一天买的物品数

	for(int i = 1; i <= n; i++)
	{
		if(cnt[dis[i]]==0) continue;	//不用买该物品
		int days = pos[dis[i]];		//该物品小于x的最大打折日
		if(days==0) num += cnt[dis[i]];  //没有打折日，直接加到num中，集中到最后一天购买
		else
		{
			money = days - last; 	//剩余能用的钱
			if(money >= cnt[dis[i]])  //能一次性买完所需的所有物品
			{
				last += cnt[dis[i]];
			}
			else  //不能一次性买完，能买多少是多少
			{
				last += money;
				num += cnt[dis[i]] - money;
			}
		}
	}
	last += 2 * num; // 剩余物品
	return last<=x;
	
}
int main()
{
	cin>>n>>m;
	for(int i = 1; i <= n; i++) 
	{
		dis[i] = i; // 存商品编号，用于排序 
		q[i].push_back(0); //没有打折日为0 
		scanf("%d",&cnt[i]);
		sum += cnt[i];
	}
	for(int i = 0; i < m; i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		q[b].push_back(a); //存打折日 
	}
	for(int i = 1; i <= n; i++)
	{
		if(cnt[i]) sort(q[i].begin(),q[i].end(),compare); //打折日升序排 
	}
	//二分 
	int l = sum-1,r = 2*sum;
	while(l + 1 < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid;
	}
	cout<<r;
    return 0;
}

```

---

## 作者：巴菲特 (赞：3)


# 解

### 大体思路：二分最短天数，判断这些天数里能否买完所有物品

### 判断能否买完的函数check(int x):

主要的参数其实就一个x,表示天数。在这些天里，我们一共可以赚x元钱，设dollor=x表示总钱数。具体在买东西的时候，我们先把能打折的买了，最后在以固定单价2元清算无法打折的原价商品。在买东西的时候，我们把总钱数dollor随时减去所花的钱，最后如果dollor>=0,说明可行，return 1；否则 return 0。

#### 最优地买打折的商品——贪心

- 参数：a[i]

a[i]表示第i种商品需要的数量

- 参数：vector<int> sale[i] 

有的商品不打折，有的商品不止一天打折，每一天可能有好几种商品打折。我们用一个不定长数组sale[i]存第i中商品在哪些天打折，就像这样：

```
	for(int i=1;i<=m;i++){
		cin>>xx>>yy;//在第xx天，yy商品打折
		sale[yy].push_back(xx);
	}
```



有这么多天可以给我打折，我在哪一天买呢？是只要打折我就能买多少买多少，然后从需要的数量a[i]里减去已购买的，直到a[i]==0或是所有的打折日都过去了吗？

事实上，我们可以只在第i个商品的最后一个打折日买所有能买的。之前的打折日我不买东西，把钱留到最后一天来用，不会造成什么影响。但是如果我在第一个打折日就花了我的钱去买第i个东西，有可能会让本来可以打折购买的商品j没钱买，所以答案会更劣。也就是说，如果我们总是在第i个商品的最后一个打折日尽可能的买东西的话，会让结果最优。这就是在买打折商品时应用的贪心思想。

所以我们要给sale[i]排序，在天数x里找到小于等于x的最后一个打折日，来买商品i。

- 参数：pos[i]

是sale[i]的下表，sale[i] [pos[i]]表示最后一个打折日。

like this:

```
	for(int i=1;i<=n;i++){//寻找1~n件商品的pos
		pos[i]=sale[i].size()-1;//初定为最后一天，防止找不到那个合法的“最后一个打折日”的时候pos[i]随随便便等于个什么值，然后出事
		for(int j=1;j<sale[i].size();j++){
			if(sale[i][j] > x){//如果这一天比x来的晚
				pos[i]=j-1;//那上一天就是我们要找的最后一个打折日
				break;//找到了赶紧溜
			}	
		}
	}

```

​	现在我们已经确定了第i个物品在哪一天买，接下来就要从第一天往第x天来买东西了。

具体地，根据这个最后一个打折日sale[i] [pos[i]] 为关键字来确定商品顺序。

like this:

```
int tem[200010]; 
int main(){
	for(int i=1;i<=n;i++){	
		tem[i]=i;
	}	
}
bool cmp(int x,int y){
	return sale[x][pos[x]] < sale[y][pos[y]];
}
bool check(int x){
	sort(tem+1,tem+1+n,cmp);
}

```

#### 然后我们就可以愉快的买打折商品了~

- 参数：t1,money,left

  

​	在每一天，我们用一个money表示手中能自由支配的钱

```
t1=0;//表示我还没花钱
left=0;
for(int i=1;i<=n;i++){//枚举i,tem[i]表示商品
	int money=sale[tem[i]][pos[tem[i]]]-t1;//sale[tem[i]][pos[tem[i]]]表示天数，t1是目前已经花的钱，money=sale[tem[i]][pos[tem[i]]]-t1表示我目前能花的钱
	if(money >= a[tem[i]]){//我有money元，只要买a[tem[i]]件商品
		dollor -= a[tem[i]];//那就都买了，总钱数dollor减去相应的花费
		t1+=a[tem[i]];//钱，花了，没了
	}
	else{
		dollor -= money;//money不够买所有的商品时，只好能买多少买多少
		left+=a[tem[i]]-money;//left是无法以打折价格购买的，存下来以原价2元买。进了这个else的可能是真的在这一天打折但是钱不够买所有；也可能是根本没有打折日的混子，没有打折日pos[tem[i]]就等于0，在第0天只有0元钱啥也买不了
		t1+=money;
	}
}
dollor-=left*2;
```

注意不打折的商品我们人为令其sale[] [0] =0 , pos等于0， 这样它就会在第0天被买

就是说要往sale[i]里先塞一个0。like this:

```
int main(){
	for(int i=1;i<=n;i++){
		sale[i].push_back(0);	
	}
}
	
```

that's all

```
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
#include<vector>
#include<bitset>
#include<set>
#include<map>

using namespace std;

int n,m,a[200010],xx,yy,pos[200010],ans;
vector <int> sale[200010];
int tem[200010]; 
bool cmp(int x,int y){
	return sale[x][pos[x]] < sale[y][pos[y]];
}
bool check(int x){
	int dollor=x,left=0;
		
	for(int i=1;i<=n;i++){
		pos[i]=sale[i].size()-1;
		for(int j=1;j<sale[i].size();j++){
			if(sale[i][j] > x){
				pos[i]=j-1;
				break;
			}	
		}
	}
	
	sort(tem+1,tem+1+n,cmp);
	int t1=0;//表示我还没花钱
	
	//按pos[i]从前往后for 	
for(int i=1;i<=n;i++){//枚举i,tem[i]表示商品
	int money=sale[tem[i]][pos[tem[i]]]-t1;//sale[tem[i]][pos[tem[i]]]表示天数，t1是目前已经花的钱，money=sale[tem[i]][pos[tem[i]]]-t1表示我目前能花的钱
	if(money >= a[tem[i]]){//我有money元，只要买a[tem[i]]件商品
		dollor -= a[tem[i]];//那就都买了，总钱数dollor减去相应的花费
		t1+=a[tem[i]];//钱，花了，没了
	}
	else{
		dollor -= money;//money不够买所有的商品时，只好能买多少买多少
		left+=a[tem[i]]-money;//left是无法以打折价格购买的，存下来以原价2元买。进了这个else的可能是真的在这一天打折但是钱不够买所有；也可能是根本没有打折日的混子，没有打折日pos[tem[i]]就等于0，在第0天只有0元钱啥也买不了
		t1+=money;
	}
}
	dollor -= left*2;
	return dollor>=0?1:0;
}

int main(){
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		tem[i]=i;sale[i].push_back(0);	
	}
	for(int i=1;i<=n;i++)	cin>>a[i];
	for(int i=1;i<=m;i++){
		cin>>xx>>yy;
		sale[yy].push_back(xx);
	}
	for(int i=1;i<=n;i++){
		sort(sale[i].begin(), sale[i].end() );//vector排序，前闭后闭 
	}
	int l,r,mid;
	l=0;r=400010;
	while(l<r){
		
		mid=(l+r)>>1;
		if(check(mid))	r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}

```



---

## 作者：Priestess_SLG (赞：1)

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

## 作者：Ak_hjc_using (赞：0)

### 思路

1. 贪心\
   内容：每一个商品都在最后一个打折日买。\
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

## 作者：gesong (赞：0)

题目传送门：[Microtransactions (hard version)](https://www.luogu.com.cn/problem/CF1165F2)。
# 思路
首先我们发现，如果 $x$ 天能购买所有商品，那么 $x+1$ 天一定也可以，因此这道题目的答案具有单调性，可以使用二分。

这时候考虑判断 $x$ 天能否购买所有的商品。

我们贪心的想：如果这个商品在 $1$ 到 $x$ 天内根本没有打折，那我们就选择在最后一天购买，否则的话我们尽量在它能打折的最后一天进行购买，如果打折日无法购买，就最后用 $2$ 块钱购买。


# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int d[N],t[N],c[N],n,m,b[N];
vector<int>a[N]; 
inline bool check(int mid){
	for (int i=1;i<=n;i++) b[i]=0;
	for (int i=1;i<=mid;i++) a[i].clear();
	for (int i=1;i<=m;i++) 
		if (d[i]<=mid) b[t[i]]=max(b[t[i]],d[i]);
	int ans=0,sum=0;
	for (int i=1;i<=n;i++)
		if (b[i]) a[b[i]].push_back(i);
		else sum+=2*c[i];
	for (int i=1;i<=mid;i++){
		ans++;
		for (auto j:a[i]){
			int x=c[j];
			if (i==mid&&ans<x) return 0;
			if (ans<x) sum+=2*(x-ans),ans=0;
			else ans-=x;
		}
	}
	return ans>=sum;
}
inline int read(){
	char c=getchar();
	int f=1,ans=0;
	while(c<48||c>57) f=(c==45?f=-1:1),c=getchar();
	while(c>=48&&c<=57) ans=(ans<<1)+(ans<<3)+(c^48),c=getchar();
	return ans*f;
}
main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++) c[i]=read();
	for (int i=1;i<=m;i++) d[i]=read(),t[i]=read();
	int l=1,r=400010ll,ans=1;
	while(l<=r){
		int mid=l+r>>1;
		if (check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout <<ans;
    return 0;
}
```

---

## 作者：FlyPancake (赞：0)

# [CF1165F2 Microtransactions (hard version)](https://www.luogu.com.cn/problem/CF1165F2) 题解

核心思想：贪心 and 二分。

## Ideas


贪心：在第 $i$ 个商品的最后一个打折日买所有能买的。

证明：若要买商品 $i$ 时，不管挑哪一个打折日，对购买 $i$ 花费的金额不会造成什么影响。但如果在第一个打折日就花了钱去买第 $i$ 个东西，有可能会让本来可以打折购买的商品 $j$ 没钱买，答案会更劣。所以将 $i$ 放在最后一天买最好。

所以对打折日排序，按打折日从大到小的顺序买对应的商品即可。剩下的商品就按原价买。

二分答案，找天数最小值。

**细节：** 因为 $sum$ 总和最大值为 $2 \cdot 10^5$，二分 $mid$ 会大于其值，所以数组最好开大点。

## Code

```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+5;

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

## 作者：Scean_Tong (赞：0)

## 思路
很容易知道，买完所有东西的最小花费是 $\sum_i^n k_i$，最大花费是 $\sum_i^n (k_i\times 2)$，所以，我们可以得出，买完所有物品的最小天数是 $\sum_i^n k_i$，最大天数是 $\sum_i^n (k_i\times 2)$，因此，我们只需要在这个区间内求出一个能够买完所有物品的最小天数。

随着时间的增长，能够买到的物品的数量也会增长，即在 $t_i$ 天内能够买到所有物品，那么在 $t_{i+1}$ 天之内肯定能够买到所有的物品。显然，暴力枚举区间 $[ \sum_i^n k_i,\sum_i^n (k_i\times 2) ]$ 会超时，那么我们可以考虑二分答案来求得最小天数，即每次找到区间 $[l,r]$ 的中点 $mid$，判断在这个天数的时候能否买到所有的物品，如果能，继续查找区间 $[l,mid - 1]$；如果不能，查找区间 $[mid,r]$。

对于二分答案中的 `Check` 函数（判断当前决策是否可行的函数），我们可以知道，当前的钱数 $M$ 等于天数 $T$，那么我们找到从第一天到第 $T$ 天中的每一个打折的日期，然后判断一下，当前的钱数能否把这个物品买完，如果不能，就买一部分；如果能，那么判断钱是否有剩余，如果有的话，就加入剩余的钱的数量 $RMB$ 中。当我们判断完打折天数后，我们还需要判断当前剩余的钱能不能够买得到剩余的在打折的时候没有买的物品，如果不能，返回 `false`，能得话，返回 `true`。

以上是本题的思路，代码就不贴了。

---

## 作者：liuyongle (赞：0)

做本题之前建议先完成本题的[简化版](https://www.luogu.com.cn/problem/CF1165F1)。

#### 思路分析

这题 hard version 的主要思想与 [easy version](https://www.luogu.com.cn/problem/CF1165F1) 相同。我们唯一应替换的是搜索的方式。用二分搜索替换线性搜索可以将时间复杂度从 $O(n^2)$ 降低到 $O(n \log n)$。

很明显，我们可以在此处应用二分搜索，因为如果我们可以在 $d$ 这天订购所有微交易，那么我们就可以在 $d+1$ 天的所有订单中订购所有微交易（即使使用 $d$ 天的答案，也可以在 $d+1$ 的日子不做任何交易）。

代码：


本题：
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> k;
vector<pair<int, int>> q(200001);

bool can(int day) {
	vector<int> lst(n, -1);
	for (int i = 0; i < m; ++i) {
		if (q[i].first <= day) {
			lst[q[i].second] = max(lst[q[i].second], q[i].first);
		}
	}
	vector<vector<int>> off(200001);
	for (int i = 0; i < n; ++i) {
		if (lst[i] != -1) {
			off[lst[i]].push_back(i);
		}
	}
	vector<int> need = k;
	int cur_money = 0;
	for (int i = 0; i <= day; ++i) {
		++cur_money;
		if (i > 200000) continue;
		for (auto it : off[i]) {
			if (cur_money >= need[it]) {
				cur_money -= need[it];
				need[it] = 0;
			} else {
				need[it] -= cur_money;
				cur_money = 0;
				break;
			}
		}
	}
	return accumulate(need.begin(), need.end(), 0) * 2 <= cur_money;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	
	cin >> n >> m;
	k = vector<int>(n);
	for (int i = 0; i < n; ++i) {
		cin >> k[i];
	}
	for (int i = 0; i < m; ++i) {
		cin >> q[i].first >> q[i].second;
		--q[i].first;
		--q[i].second;
	}
	
	int l = 0, r = 400000;
	while (r - l > 1) {
		int mid = (l + r) >> 1;
		if (can(mid)) r = mid;
		else l = mid;
	}
	
	for (int i = l; i <= r; ++i) {
		if (can(i)) {
			cout << i + 1 << endl;
			return 0;
		}
	}
	
	assert(false);
	
	return 0;
}
```

在此基础上稍作修改即可完成简化版题目：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> k;
vector<pair<int, int>> q(1001);

bool can(int day) {
	vector<int> lst(n, -1);
	for (int i = 0; i < m; ++i) {
		if (q[i].first <= day) {
			lst[q[i].second] = max(lst[q[i].second], q[i].first);
		}
	}
	vector<vector<int>> off(1001);
	for (int i = 0; i < n; ++i) {
		if (lst[i] != -1) {
			off[lst[i]].push_back(i);
		}
	}
	vector<int> need = k;
	int cur_money = 0;
	for (int i = 0; i <= day; ++i) {
		++cur_money;
		if (i > 1000) continue;
		for (auto it : off[i]) {
			if (cur_money >= need[it]) {
				cur_money -= need[it];
				need[it] = 0;
			} else {
				need[it] -= cur_money;
				cur_money = 0;
				break;
			}
		}
	}
	return accumulate(need.begin(), need.end(), 0) * 2 <= cur_money;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
#endif
	
	cin >> n >> m;
	k = vector<int>(n);
	for (int i = 0; i < n; ++i) {
		cin >> k[i];
	}
	for (int i = 0; i < m; ++i) {
		cin >> q[i].first >> q[i].second;
		--q[i].first;
		--q[i].second;
	}
	
	for (int l = 0; l <= 2000; ++l) {
		if (can(l)) {
			cout << l + 1 << endl;
			return 0;
		}
	}
	
	assert(false);
	
	return 0;
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [Microtransactions (hard version)](https://www.luogu.com.cn/problem/CF1165F2)

这个题与的简化版 [CF1165F1](https://www.luogu.com.cn/problem/CF1165F1)差不多，只是数据范围扩大了。
## 思路分析

我们可以模拟 Ivan 在第几天可以完成任务，对于 Ivan 想要购买的物品数量 $k$，最少需要 $k$ 天，最大要 $2\times k$ 天，如果直接遍历的话，就会 TLE，所以使用二分枚举可行的天数。

在二分 ```check``` 函数中，我们在后往前枚举天数的时候是要将打折的物品都买掉。最后判断我们多余的钱能否将剩余的物品给买完即可。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=4e5+1;
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
```

---

