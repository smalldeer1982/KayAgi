# Closest Cities

## 题目描述

There are $ n $ cities located on the number line, the $ i $ -th city is in the point $ a_i $ . The coordinates of the cities are given in ascending order, so $ a_1 < a_2 < \dots < a_n $ .

The distance between two cities $ x $ and $ y $ is equal to $ |a_x - a_y| $ .

For each city $ i $ , let's define the closest city $ j $ as the city such that the distance between $ i $ and $ j $ is not greater than the distance between $ i $ and each other city $ k $ . For example, if the cities are located in points $ [0, 8, 12, 15, 20] $ , then:

- the closest city to the city $ 1 $ is the city $ 2 $ ;
- the closest city to the city $ 2 $ is the city $ 3 $ ;
- the closest city to the city $ 3 $ is the city $ 4 $ ;
- the closest city to the city $ 4 $ is the city $ 3 $ ;
- the closest city to the city $ 5 $ is the city $ 4 $ .

The cities are located in such a way that for every city, the closest city is unique. For example, it is impossible for the cities to be situated in points $ [1, 2, 3] $ , since this would mean that the city $ 2 $ has two closest cities ( $ 1 $ and $ 3 $ , both having distance $ 1 $ ).

You can travel between cities. Suppose you are currently in the city $ x $ . Then you can perform one of the following actions:

- travel to any other city $ y $ , paying $ |a_x - a_y| $ coins;
- travel to the city which is the closest to $ x $ , paying $ 1 $ coin.

You are given $ m $ queries. In each query, you will be given two cities, and you have to calculate the minimum number of coins you have to spend to travel from one city to the other city.

## 说明/提示

Let's consider the first two queries in the example from the statement:

- in the first query, you are initially in the city $ 1 $ . You can travel to the closest city (which is the city $ 2 $ ), paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 3 $ ) again, paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 4 $ ) again, paying $ 1 $ coin. In total, you spend $ 3 $ coins to get from the city $ 1 $ to the city $ 4 $ ;
- in the second query, you can use the same way to get from the city $ 1 $ to the city $ 4 $ , and then spend $ 5 $ coins to travel from the city $ 4 $ to the city $ 5 $ .

## 样例 #1

### 输入

```
1
5
0 8 12 15 20
5
1 4
1 5
3 4
3 2
5 1```

### 输出

```
3
8
1
4
14```

# 题解

## 作者：__zhuruirong__ (赞：4)

## 题目大意

有一个 $n$ 个城市，第 $i$ 个点坐标是 $a_i$ 上，每个城市有 $2$ 条边连向左右相邻两个城市，其中离得近的那个距离为 $1$，另一个若位置为 $a_j$，则距离为 $|a_i - a_j|$，有 $m$ 祖询问，问第 $i$ 个城市到第 $j$ 个城市的最近距离是多少。

## 题目分析

这道题一看就是一个裸 DP，我们可以预处理出距离 $i$ 最近的点是哪个，然后跑两遍 DP，第一遍用 $dp1_i$ 记录从 $1$ 出发到第 $i$ 个点距离，第二遍用 $dp2_i$ 记录从 $n$ 出发到第 $i$ 个点的距离，如果询问的 $i\le j$ 则答案为 $dp1_j - dp1_i$，否则为 $dp2_j - dp2_i$。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
int a[N], nxt[N], pre[N], suf[N], n, m, T;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> T;
	while(T--) {
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		for(int i = 1; i <= n; i++) {
			if(i == 1)
				nxt[i] = 2;
			else if(i == n)
				nxt[i] = n - 1;
			else
				if(a[i] - a[i - 1] < a[i + 1] - a[i])
					nxt[i] = i - 1;
				else
					nxt[i] = i + 1;
		}
		for(int i = 1; i <= n; i++)
			if(nxt[i] == i + 1)
				pre[i + 1] = pre[i] + 1;
			else
				pre[i + 1] = pre[i] + (a[i + 1] - a[i]);
		for(int i = n; i >= 1; i--)
			if(nxt[i] == i - 1)
				suf[i - 1] = suf[i] + 1;
			else
				suf[i - 1] = suf[i] + (a[i] - a[i - 1]);
		cin >> m;
		while(m--) {
			int l, r;
			cin >> l >> r;
			if(l <= r)
				cout << pre[r] - pre[l] << endl;
			else
				cout << suf[r] - suf[l] << endl;
		}
	}

	return 0;
}


```

写篇题解不容易，点个赞再走吧~

---

## 作者：MhxMa (赞：2)

### 题意

题目给出了一些城市在数轴上的坐标，城市之间的距离是它们坐标之差的绝对值。对于每个城市，定义最近的城市为与其距离最小的城市。可以进行两种操作：花费城市间的距离个硬币旅行，或者花费 $1$ 个硬币旅行到最近的城市。给定多个查询，每个查询包含两个城市，要求计算从一个城市到另一个城市的最小花费。

### 思路

对于每个城市，预处理出到它左边和右边最近的城市的距离，可以用两个数组分别存储在 $pre$ 和 $suff$。然后对于每个查询，判断目标城市在起始城市的左边还是右边，分别输出对应的最小花费。

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        int m;
        cin >> m;
        vector<pair<int, int>> queries;

        while (m--) {
            int a, b;
            cin >> a >> b;
            queries.push_back({a, b});
        }

        vector<int> pre(n), suff(n);

        pre[0] = 0;
        pre[1] = 1;

        for (int i = 2; i < n; i++) {
            pre[i] = (abs(arr[i - 1] - arr[i - 2]) > abs(arr[i - 1] - arr[i])) ?
                        pre[i - 1] + 1 :
                        pre[i - 1] + abs(arr[i - 1] - arr[i]);
        }

        suff[n - 1] = 0;
        suff[n - 2] = 1;

        for (int i = n - 3; i >= 0; i--) {
            suff[i] = (abs(arr[i + 1] - arr[i]) > abs(arr[i + 1] - arr[i + 2])) ?
                        suff[i + 1] + abs(arr[i + 1] - arr[i]) :
                        suff[i + 1] + 1;
        }

        for (auto& q : queries) {
            int x = q.first;
            int y = q.second;

            if (x < y) {
                cout << pre[y - 1] - pre[x - 1] << "\n";
            } else {
                cout << suff[y - 1] - suff[x - 1] << "\n";
            }
        }
    }

    return 0;
}
```

---

## 作者：Crazyouth (赞：2)

## 分析

注意到从 $1\sim n$ 的旅游费用单调递增，从 $n\sim 1$ 的旅游费用也是单调递增，考虑前缀和维护。先对每个城市维护一下最近的城市，再从 $1\sim n$，$n\sim1$ 两个方向扫一遍，就得到了两个 $sum$ 数组（前缀和数组），记为 $sum_1,sum_2$，对于每次询问，若 $x<y$，输出 ${sum_1}_y-{sum_1}_x$，否则输出 ${sum_2}_y-{sum_2}_x$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[100010],sum1[100010],sum2[100010],nc[100010];
void solve()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	nc[1]=2;
	nc[n]=n-1;
	for(int i=2;i<n;i++)
	nc[i]=(abs(a[i]-a[i-1])>abs(a[i]-a[i+1])?i+1:i-1);
	for(int i=2;i<=n;i++) sum1[i]=sum1[i-1]+(nc[i-1]==i?1:abs(a[i-1]-a[i]));
	for(int i=n-1;i;i--) sum2[i]=sum2[i+1]+(nc[i+1]==i?1:abs(a[i+1]-a[i]));
	int q;
	cin>>q;
	while(q--)
	{
		int a,b;
		cin>>a>>b;
		if(a<b) cout<<sum1[b]-sum1[a]<<endl;
		else cout<<sum2[b]-sum2[a]<<endl;
	}
}
signed main()
{
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}

---

## 作者：Engulf (赞：0)

依题意算出任意两点之间的距离，**注意 $x \rightarrow y$ 与 $y \rightarrow x$** 的花费可能不一样。

对于一个询问 $x \rightarrow y$，因为是在数轴上移动，只有唯一的路径，所以直接用前缀和计算一下即可，讨论一下从左到右与从右到左。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<ll> pre(n), suf(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        pre[1] = suf[n - 2] = 1;
        for (int i = 1; i < n - 1; i++) {
            int x = a[i] - a[i - 1], y = a[i + 1] - a[i];
            if (x < y) suf[i - 1] = 1, pre[i + 1] = y;
            else suf[i - 1] = x, pre[i + 1] = 1;
        }
        for (int i = 1; i < n; i++) pre[i] += pre[i - 1];
        for (int i = n - 2; ~i; i--) suf[i] += suf[i + 1];
        int q;
        cin >> q;
        while (q--) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            cout << (x < y ? pre[y] - pre[x] : suf[y] - suf[x]) << "\n";
        }
    }
    return 0;
}
```

---

## 作者：Jerry_heng (赞：0)

（一）

从 $i$ 到 $j$ 有两种走法，一种是用 $a_j-a_i$ 的代价，一种是用 $1$ 的代价，前提是 $j$ 是 $i$ 最近的。

~~显然如果符合条件选第二种。~~

先考虑从左向右走。（和从右向左相同）

考虑走到了节点 $i$，如果 $a_{i+1}-a_{i}>a_{i}-a_{i-1}$，那么花费 $1$ 的代价向右走，否则花费 $a_{i+1}-a_{i}$ 的代价向右走。

用类似于前缀和的方法统计，由于每一步用哪种与前面无关（肯定能选第二种就第二种），那么只用从左到右，从右到左都扫一遍即可。

$ltor_{i}$ 表示从 $1$ 走到 $i$ 最少代价。

从 $l$ 到 $r$ 最少代价即为 $ltor_{r}-ltor_{l}$。

（二）

AC 代码。
````cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,l,r,q,a[100010],ltor[100010],rtol[100010];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		for(int i=2;i<=n;i++){
			if(a[i]-a[i-1]<=a[i-1]-a[i-2]||i==2)ltor[i]=ltor[i-1]+1;
			else ltor[i]=ltor[i-1]+a[i]-a[i-1];
		}
		for(int i=n-1;i>=1;i--){
			if(a[i+1]-a[i]<=a[i+2]-a[i+1]||i==n-1)rtol[i]=rtol[i+1]+1;
			else rtol[i]=rtol[i+1]+a[i+1]-a[i];
		}
		scanf("%lld",&q);
		while(q--){
			scanf("%lld%lld",&l,&r);
			if(l<r)printf("%lld\n",ltor[r]-ltor[l]);
			else printf("%lld\n",rtol[r]-rtol[l]);
		}
	}
	return 0;
}
```

---

## 作者：Zemu_Ooo (赞：0)

做前缀和遇到的比较喜欢的题。当时考场上其实想的解和这个差不多，但优化方面我觉得这一版做的更好。

总结来说，就是要求我们找到从一点到另一点的最小代价。那策略显而易见是预处理数组 $A$ 和 $B$ 来存储每个城市到其他城市的最小代价。

对于数组 $A$，我们从左到右遍历原始数组，每次遍历到一个新的城市时，我们计算从上一个城市到当前城市的代价，并累加到当前城市。这样，$A_i$ 就存储了从第一个城市到第 $i$ 个城市的最小代价。

类似地，对于数组 $B$，我们从右到左遍历，每次计算从右侧的城市到当前城市的代价，并累加。

最后，对于每个询问比较 $x$ 和 $y$ 的大小，以确定使用哪个数组来计算答案。如果 $x < y$，我们使用数组 $A$ 并计算 $A_y - A_x$ 作为答案。如果 $x > y$，我们使用数组 $B$ 并计算 $B_y - B_x$。这样就能得到从第 $x$ 个城市到第 $y$ 个城市的最小代价。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define endl "\n";

int a[1145141], sum[1145141], num[1145141];

signed main() {
    int t = 1;
    cin >> t;
    while(t--) {
        int n, m, x, y;
    	cin >> n;
    	for(int i = 1; i <= n; i++) {
        	cin >> a[i];
    	}

    	sum[1] = 0;
    	sum[2] = 1;
    	for(int i = 2; i <= n; i++) {
        	if((a[i + 1] - a[i]) < (a[i] - a[i - 1])) {
            	sum[i + 1] = sum[i] + 1;
        	} else {
            	sum[i + 1] = sum[i] + a[i + 1] - a[i];
        	}
    	}

    	num[n] = 0;
    	num[n - 1] = 1;
    	for(int i = n - 1; i > 0; i--) {
        	if((a[i + 1] - a[i]) > (a[i] - a[i - 1])) {
            	num[i - 1] = num[i] + 1;
        	} else {
            	num[i - 1] = num[i] + a[i] - a[i - 1];
        	}
    	}

    	cin >> m;
    	while(m--) {
        	cin >> x >> y;
        	if(x < y) {
            	cout << sum[y] - sum[x] << endl;
        	} else {
            	cout << num[y] - num[x] << endl;
        	}
    	}
    }
    return 0;
}
```

---

## 作者：UncleSam_Died (赞：0)

### 解题思路

贪心，能走距离最短的城市就一定走。

分别考虑 $x>y$ 和 $x<y$ 的情况，两种情况分别是从后向前转移和从前往后转移，分别预处理一个前缀和和后缀和即可。

### AC 代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include <valarray>
#define N 100005
#define ll long long
int n,m,a[N],clo[N];
ll sum[N],suf[N];
inline void work(){
    scanf("%d",&n);
    for(register int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    clo[1]=2,clo[n]=n-1;
    for(register int i=2;i<n;++i){
        int d1=a[i+1]-a[i];
        int d2=a[i]-a[i-1];
        clo[i]=d1<d2?i+1:i-1;
    }
    for(register int i=2;i<=n;++i)
        sum[i]=sum[i-1]+(clo[i-1]==i?1:a[i]-a[i-1]);
    for(register int i=n-1;i>=1;--i)
        suf[i]=suf[i+1]+(clo[i+1]==i?1:a[i+1]-a[i]);
    scanf("%d",&m);
    int x,y;while(m--){
        scanf("%d%d",&x,&y);
        if(x<y)
            printf("%lld\n",sum[y]-sum[x]);
        else printf("%lld\n",suf[y]-suf[x]);
    }
}
signed main(){
    int T;scanf("%d",&T);
    while(T--) work();
}
```

---

## 作者：__Dist__ (赞：0)

### 题目描述

给定一条直线上 $n$ 个城市的坐标 $a_i$，保证坐标单调递增。设两城市坐标为 $a_x$ 和 $a_y$，那么两城市之间的距离为 $|a_x-a_y|$。

城市 $x$ 到与它距离最近的城市的花费是 $1$，到其他城市的花费是 $|a_x-a_y|$。

有 $q$ 次询问，每次给定 $x, y$，问从编号 $x$ 的城市到编号 $y$ 的城市最小花费是多少。

### 思路讲解

用 $qzh_i$ 表示从第 $1$ 个城市到第 $i + 1$ 个城市的最小花费。

我们遍历 $1\sim n$：如果第 $i$ 个城市到第 $i + 1$ 个城市的花费小于第 $i - 1$ 个城市到第 $i$ 个城市的花费，那么 $qzh_i=qzh_{i-1}+1$；否则，$qzh_i=qzh_{i-1}+a_{i+1}-a_i$。为了方便处理，我们可以把 $a_0$ 赋最小值，把 $a_{n+1}$ 赋最大值。

如果询问中 $x<y$，那么答案显然就是 $qzh_{y-1}-qzh_{x-1}$。

同理，用 $hzh_i$ 表示第 $n$ 个城市到第 $i-1$ 个城市的最小花费。转移类似，这里不推导了。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 2e5 + 5;

long long a[MAXN];
long long n, m;
long long qzh[MAXN];
long long hzh[MAXN];

void solve() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
	}
	a[0] = INT_MIN, a[n + 1] = INT_MAX;
	for (int i = 1; i <= n; i++) {
		if(a[i] - a[i - 1] > a[i + 1] - a[i]) qzh[i] = qzh[i - 1] + 1;
		else qzh[i] = qzh[i - 1] + a[i + 1] - a[i];
	}
	for (int i = n; i >= 1; i--) {
		if(a[i] - a[i - 1] < a[i + 1] - a[i]) hzh[i] = hzh[i + 1] + 1;
		else hzh[i] = hzh[i + 1] + a[i] - a[i - 1];
	}
//	printf("\n%lld\n\n", qzh[1]);
	scanf("%lld", &m);
	while(m--) {
//    	int ans = 0;
		int x, y;
		scanf("%lld%lld", &x, &y);
		if(x > y) printf("%lld", hzh[y + 1] - hzh[x + 1]);
		else printf("%lld", qzh[y - 1] - qzh[x - 1]);
		puts("");
	}
}

signed main() {
	int T;
	scanf("%lld", &T);
	while(T--) {
		solve();
	}
	return 0;
}

```


---

## 作者：飘然归隐 (赞：0)

由题意可知，要么一路向左，要么一路向右，所以预处理的时候处理好每一步向左和向右分别需要多少代价，最后使用前缀和加在一起就行。

要注意边界条件，从左往右和从右往左不一样。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[100005],b[100005],c[100005];
ll sumb[100005],sumc[100005];
int main() {
    int t;
    cin >> t; 
 
    while (t--) {
        ll n;
        cin >> n; 
        for(int i=1;i<=n;i++)
        {
        	cin>>a[i];
		}
	//b是从左往右，c是从右往左
		b[1]=1;
		c[n]=1;
      		//边界条件
		sumb[1]=b[1];
		sumc[1]=c[2];
        //从左往右 顺路就前缀和
		for(int i=2;i<n;i++)
		{
			if(abs(a[i]-a[i-1])<abs(a[i]-a[i+1]))
			{
				b[i]=abs(a[i]-a[i+1]);
				c[i]=1;
				sumb[i]=sumb[i-1]+b[i];
			
			}
			else
			{
				b[i]=1;
				c[i]=abs(a[i]-a[i-1]);
				sumb[i]=sumb[i-1]+b[i];
				
			}
		}
        //b和c不一样 所以要单独出来前缀和
		for(int i=1;i<n;i++)
		{
			sumc[i]=sumc[i-1]+c[i+1];
		}
		ll m;
		cin>>m;
		while(m--)
		{
			ll x,y;
			cin>>x>>y;
			if(x<y)
			{
				cout<<sumb[y-1]-sumb[x-1]<<endl;
			}
			else
			{
				cout<<sumc[x-1]-sumc[y-1]<<endl;
			}
		}
		
    }
 
    return 0;
}
```


---

## 作者：nyC20 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1922C)
# 思路
每一个点的位置都为整数，所以最佳的方案应该是能用花费 $1$ 就花费 $1$，不行才用两者位置之差的花费。然后如果直接按照题目给的询问去遍历的话，写出来的代码是这样的:
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, x, y, a[1000003], ans;
int main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		scanf("%d",&m);
		while(m--){
			scanf("%d%d",&x,&y);
			ans=0;
			if(x<y){
				while(true){
					if(x==y)break;
					if(x==1)ans++;
					else if(a[x+1]-a[x]<a[x]-a[x-1])ans+=1;
					else ans+=a[x+1]-a[x];
					x++;
				}
			}
			else{
				while(true){
					if(x==y)break;
					if(x==n)ans++;
					else if(a[x]-a[x-1]<a[x+1]-a[x])ans+=1;
					else ans+=a[x]-a[x-1];
					x--;
				}
			}
			
			printf("%d\n",ans);
		}
	}
	return 0;
}

```
然后 TLE 了。

接下来就开始思考，为什么会 T 呢？这道题需要在一个一维的数轴上不断访问两者的距离差，可以用前缀和优化！
# 坑点
正向和反向的花费并不是一样的，比如从 $1$ 到 $5$ 和从 $5$ 到 $1$ 的花费是不一样的，所以需要两个前缀和数组，正向和反向各求一遍前缀和。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, m, x, y, a[1000003], ans, sum[1000003], sum_[1000003];
int main() {
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		for(int i=2;i<=n;i++){
			if(a[i-1]-a[i-2]>a[i]-a[i-1]||i==2){//特判，第一个点到前一个点没有距离 
				sum[i]=sum[i-1]+1;//用1的花费 
				continue;
			}
			sum[i]=sum[i-1]+a[i]-a[i-1];//用两者距离地花费 
		}
		for(int i=n-1;i>=1;i--){
			if(a[i+2]-a[i+1]>a[i+1]-a[i]||i==n-1){//同上 
				sum_[i]=sum_[i+1]+1;
				continue;
			}
			sum_[i]=sum_[i+1]+a[i+1]-a[i];
		}
		scanf("%lld",&m);
		while(m--){//询问 
			scanf("%d%d",&x,&y);
			if(x<y)printf("%lld\n",sum[y]-sum[x]);
			else printf("%lld\n",sum_[y]-sum_[x]);
		}
	}
	return 0;
}
```




---

