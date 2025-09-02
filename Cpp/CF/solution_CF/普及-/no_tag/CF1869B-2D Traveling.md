# 2D Traveling

## 题目描述

Piggy lives on an infinite plane with the Cartesian coordinate system on it.

There are $ n $ cities on the plane, numbered from $ 1 $ to $ n $ , and the first $ k $ cities are defined as major cities. The coordinates of the $ i $ -th city are $ (x_i,y_i) $ .

Piggy, as a well-experienced traveller, wants to have a relaxing trip after Zhongkao examination. Currently, he is in city $ a $ , and he wants to travel to city $ b $ by air. You can fly between any two cities, and you can visit several cities in any order while travelling, but the final destination must be city $ b $ .

Because of active trade between major cities, it's possible to travel by plane between them for free. Formally, the price of an air ticket $ f(i,j) $ between two cities $ i $ and $ j $ is defined as follows:

 $ $$$ f(i,j)= \begin{cases} 0, & \text{if cities }i \text{ and }j \text{ are both major cities} \\ |x_i-x_j|+|y_i-y_j|, & \text{otherwise} \end{cases}  $ $$$

Piggy doesn't want to save time, but he wants to save money. So you need to tell him the minimum value of the total cost of all air tickets if he can take any number of flights.

## 说明/提示

In the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1869B/5d562a7fae0997b047c9a0448bd832cdb0a43e6a.png) The major cities are marked red.The optimal way to choose the flights is: $ 3\rightarrow 1 \rightarrow 2 \rightarrow 5 $ , which will cost $ 3+0+1=4 $ . Note that the flight $ 1\rightarrow 2 $ costs $ 0 $ , because both city $ 1 $ and $ 2 $ are major cities.

In the second test case, since there are only $ 2 $ cities, the only way is to take a flight from city $ 1 $ to $ 2 $ .

In the third test case, since city $ 2 $ and $ 4 $ are both major cities, Piggy can directly take a flight from city $ 2 $ to $ 4 $ , which costs $ 0 $ .

In the fourth test case, Piggy can choose to take the following flights: $ 3\rightarrow 2\rightarrow 1 $ , and the cost is $ 11+11=22 $ .

## 样例 #1

### 输入

```
5
6 2 3 5
0 0
1 -2
-2 1
-1 3
2 -2
-3 -3
2 0 1 2
-1000000000 -1000000000
1000000000 1000000000
7 5 4 2
154 147
-154 -147
123 456
20 23
43 20
998 244
353 100
3 1 3 1
0 10
1 20
2 30
4 3 2 4
0 0
-100 100
-1 -1
-1 0```

### 输出

```
4
4000000000
0
22
1```

# 题解

## 作者：include13_fAKe (赞：5)

## 前言
蒟蒻的第一篇 CF 题解。
## 题意
$t$ 组数据。

对于每组数据，给定 $1$ 个含 $n$ 个结点的图，其中前 $k$ 个点为关键点，同时给出这 $n$ 个点的坐标 $(x_i,y_i)$。求从编号为 $a$ 的点走到编号为 $b$ 的点的最小花费。

定义从 $s$ 点走到 $t$ 点的花费如下：

- 若两个点均为关键点，则它们的花费为 $0$。
- 否则，它们的花费为它们的**曼哈顿距离**。即 $|x_s-x_t|+|y_s-y_t|$。

## 思路
首先可以确定的一点是，**从一个关键点走到另一个关键点的行动，如果要发生，就可以只发生一次**。

若 $a,b$ 均为关键点，则它们的最小花费为 $0$。

若 $a,b$ 中有一个是关键点，我们可以枚举全部关键点，找出与 $a,b$ 中的那个非关键点花费最小的点，最终答案就是这个值。

若 $a,b$ 都不是关键点，则答案是与 $a$ 花费最小的关键点的花费和与 $b$ 花费最小的关键点的花费之和。

但有可能会遇到一种特例，就是**直接从 $a$ 走到 $b$ 的情况可能会更优**。要对此加以考虑。

另外，最好打开 ```long long```，以防被卡。

此外向各位选手推荐一道好题：[P9065](https://www.luogu.com.cn/problem/P9065)。那道题的思路和这道题很相似，只是还要复杂一点而已。
## 代码
代码写得和讲的有点不一样，敬请见谅。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,k,a,b;
int x[2*114514],y[2*114514];
void solve(){
	cin>>n>>k>>a>>b;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>y[i];
	}
	if(a<=k&&b<=k){
		puts("0");
		return;
	}
	if(a<=k||b<=k){
		int c=max(a,b);
		int ans=1e18;
		for(int i=1;i<=k;i++){
			ans=min(ans,abs(x[c]-x[i])+abs(y[c]-y[i]));
		}
		cout<<ans<<endl;
		return;
	}
	int ans1=1e18,ans2=1e18;
	int ans3=abs(x[b]-x[a])+abs(y[b]-y[a]);
	for(int i=1;i<=k;i++){
		ans1=min(ans1,abs(x[a]-x[i])+abs(y[a]-y[i]));
		ans2=min(ans2,abs(x[b]-x[i])+abs(y[b]-y[i]));
	}
	cout<<min(ans1+ans2,ans3)<<endl;
	return ;
}
int T;
signed main(){
	cin>>T;
	while(T--)	solve();
	return 0;
}
```
最后预祝洛谷的 RemoteJudge 功能能够尽快恢复正常，也祝大家 **CSP-J/S 2023 第一轮 RP++**！

---

## 作者：One_JuRuo (赞：4)

## 思路

首先思考，除了 $a$ 和 $b$ 我们不应该到达任何非主要城市。

理由很简单，两点之间线段最短，如果我们目前要从 $u$ 前往 $v$ 且 $u$ 和 $v$ 不都是主要城市，即 $u$ 到 $v$ 需要花钱，那么如果再选择一个不是主要城市的 $k$，那么就要增加若干的花费。当然，增加的花费可能为 $0$，但是我们完全没必要多转几次，因为这无法让答案变得更优。

但是主要城市之间可以随便转乘，因为都不增加花费，那么就有两种方式：

- 直接从 $a$ 到 $b$。

- 从 $a$ 到离它最近的主要城市，途中转移几次到离 $b$ 最近的主要城市，再到 $b$。

如果令 $dis(i,j)$ 表示从 $i$ 到 $j$ 的花费，$fa$ 表示离 $a$ 最近的主要城市，$fb$ 表示离 $b$ 最近的主要城市，那么答案就是 $\min(dis(a,b),dis(a,fa)+dis(fa,fb)+dis(fb,b))$。

首先 $dis(i,j)$ 可以直接计算得出，所以不需要考虑，又因为 $dis(fa,fb)=0$ 所以也不需要考虑，我们只需要提前预处理出 $fa$ 和 $fb$，或者预处理 $dis(a,fa)$ 和 $dis(b,fb)$ 即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,k,a,b,x[200005],y[200005],ans1,ans2;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld%lld%lld",&n,&k,&a,&b),ans1=ans2=0x3f3f3f3f3f3f3f3f;
		for(long long i=1;i<=n;++i) scanf("%lld%lld",&x[i],&y[i]);
		if(a<=k) ans1=0;//注意特判a、b本身就是主要城市的情况
		else for(long long i=1;i<=k;++i) ans1=min(ans1,abs(x[i]-x[a])+abs(y[i]-y[a]));
		if(b<=k) ans2=0;
		else for(long long i=1;i<=k;++i) ans2=min(ans2,abs(x[i]-x[b])+abs(y[i]-y[b]));
		printf("%lld\n",min(ans1+ans2,abs(x[a]-x[b])+abs(y[a]-y[b])));
	}
	return 0;
}
```

---

## 作者：BugGod (赞：1)

显然的，想要求出最小花费，有两种情况。

1. 直接从 $a$ 走到 $b$。
1. 从 $a$ 开始，经过一些 $\texttt{major city}$，再到达 $b$。

那么我们就可以分别把这两种情况算出来，然后取最小值。

对于第一种情况，直接求曼哈顿距离即可。

对于第二种情况，分别求出距离 $a,b$ 最近的 $\texttt{major city}$，距离相加即可（因为 $\texttt{major city}$ 之间距离为0）。

几个坑点（可能只有我会踩）

1. 计算 $a,b$ 与中转点距离的变量要初始化，且不能太大，否则会溢出，导致答案错误。
1. 不要用 `memset`！不要用 `memset`！不要用 `memset`！会 TLE！
1. 十年 OI 一场空，不开 `long long` 见祖宗！

代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,x[200010],y[200010],a,b,ak=1e18,bk=1e18;
int dis(int i,int j)
{
	return abs(x[i]-x[j])+abs(y[i]-y[j]);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--)
	{
//		memset(x,0,sizeof(x));
//		memset(y,0,sizeof(y));
		ak=1e18;
		bk=1e18;
		cin>>n>>k>>a>>b;//
		for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
		if(a>k)
		{
			for(int i=1;i<=k;i++)
			{
				ak=min(ak,dis(a,i));//a与中转点最小距离
			}
		}
		else ak=0;
		if(b>k)
		{
			for(int i=1;i<=k;i++)
			{
				bk=min(bk,dis(b,i));//b与中转点最小距离
			}
		}
		else bk=0;
		cout<<min(ak+bk,dis(a,b))<<endl;
		//printf("\n::%lld %lld %lld %lld::\n\n",ak,bk,ak+bk,dis(a,b));
	}
	return 0;
}
```

---

## 作者：fls233666 (赞：1)

题目要求从 $a$ 到 $b$ 的最小代价，显然我们要从代价本身入手，即 **曼哈顿距离** :$d=|x_1-x_2|+|y_1-y_2|$。

我们把曼哈顿距离在 2D 平面上面表示出来，并把它跟欧几里得距离 $d=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$ 做个对比：

![pic 1](https://cdn.luogu.com.cn/upload/image_hosting/7q0bnnpt.png)

图中，线段 $|AB|$ 代表了欧几里得距离，而 $|AC|+|CB|$ 代表了曼哈顿距离。

可以看出，曼哈顿距离转换到 2D 平面上时，相当于是沿着坐标轴方向从点 $a$ 走到点 $b$。

那么，先不考虑重要城市的存在。假设所有城市都不是重要城市，直接从 $a$ 到 $b$ 与寻找一个中转点 $c$，两个方案哪个更优？

不妨再用一张图来思考：

![pic 2](https://cdn.luogu.com.cn/upload/image_hosting/sr2h79n1.png)

- 直接从 $a$ 到 $b$，转化为曼哈顿距离，相当于走了线段 $k+j$。
- 找一个点 $c$，从 $a$ 到 $c$ 再到 $b$，相当于走了线段 $g+f+i+h$。
|
而在曼哈顿距离下，我们会发现：$|x_A-x_B|+|y_A-y_B|=(|x_A-x_C|+|y_A-y_C|)+(|x_C-x_B|+|y_C-y_B|)$

于是我们有了一个重要结论：**在不考虑重要城市的情况下，找中转城市不会改变从 $a$ 到 $b$ 所需要的代价。**

接下来，进一步考虑存在重要城市的情况。

因为重要城市之间的飞行不需要代价，所以我们就想到，**利用重要城市进行中转，使从 $a$ 到 $b$ 需要的总代价更小。**

如何进行中转？找到分别离 $a$ 曼哈顿距离最近的重要城市 $k_1$ 和离 $b$ 曼哈顿距离最近的重要城市 $k_2$，由于 $k_1$ 到 $k_2$ 需要的代价是 $0$，所以此时需要的总代价是 $(|x_A-x_{K1}|+|y_A-y_{K1}|)+(|x_{K2}-x_B|+|y_{K2}-y_B|)$。

而当不利用重要城市进行中转时，根据上述结论，$a$ 到 $b$ 的代价应该始终是 $|x_A-x_B|+|y_A-y_B|$。

将上述两种方案转换到图上，应该这样表示：

![pic 3](https://cdn.luogu.com.cn/upload/image_hosting/upn0hka2.png)

将寻找重要城市作为中转的代价【上图蓝色部分】与直接从 $a$ 到 $b$ 的代价【上图红色部分】分别计算，最后互相比较，取其中更小值就是答案，

下面放上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define ll long long
#define qmx(a,b) a<b?b:a
#define qmn(a,b) a>b?b:a
using namespace std;

const int mxn = 2e5+5;
int nk,n,na,nb;
ll nx[mxn],ny[mxn];
ll ans,ans1,ans2[2];

inline ll abc(ll u){
    return u<0?-u:u;
}  //手写绝对值

inline ll dis(ll x1,ll y1,ll x2,ll y2){
    return abc(x1-x2)+abc(y1-y2);
}  //计算曼哈顿距离

int main(){
    int test;
    scanf("%d",&test);
    while(test--){
        scanf("%d%d%d%d",&n,&nk,&na,&nb);
        for(int i=1;i<=n;i++)
            scanf("%lld%lld",&nx[i],&ny[i]);
        ans1=dis(nx[na],ny[na],nx[nb],ny[nb]);  //不中转，直接从 a 到 b 的代价
        ans2[0]=ans2[1]=1145141919810;
        for(int i=1;i<=nk;i++){  //O(K) 暴力找离 a 离 b 最近的重要城市进行中转
            ans2[0]=qmn(dis(nx[na],ny[na],nx[i],ny[i]),ans2[0]);  //计算 a 到最近的重要城市的代价
            ans2[1]=qmn(dis(nx[nb],ny[nb],nx[i],ny[i]),ans2[1]);  //计算 b 到最近的重要城市的代价
        }
        ans=qmn(ans1,ans2[0]+ans2[1]);  //两种方案取最小值作为答案
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：SunnyYuan (赞：1)

## 思路

如果 $a, b \le k$，那么从 $a$ 直接到 $b$ 不需要花钱。

然后我们来想一想如何应对 $a, b$ 两个**都不** $\le k$。

接下来就又分了 $2$ 种情况：

1. 从 $a$ 直接到 $b$，花费 $|x_a - x_b| + |y_a - y_b|$。
2. 从 $a$ 到离 $a$ 最近的编号小于等于 $k$ 的城市 $v$，然后再免费到离 $b$ 最近的编号小于等于 $k$ 的城市 $u$，再到 $b$，花费 $|x_v - x_a| + |y_v - y_a| + |x_u - x_b| + |y_u - y_b|$。

最后我们再来想一想如何应对 $a, b$ 有一个 $\le k$ 的情况：

假设 $b \le k$ 且 $a > k$，如果不是这样，交换一下 $a, b$ 对答案没有影响。

又分为 $2$ 种情况：

1. 从 $b$ 直接到 $a$,花费 $|x_a - x_b| + |y_a - y_b|$。
2. 从 $b$ 免费到离 $a$ 最近的编号小于等于 $k$ 的城市 $u$，然后再到 $b$，花费 $|x_u - x_b| + |y_u - y_b|$。

## 代码

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 200010;

int n, k, a, b;
int x[N], y[N];

int dis(int a, int b) {
	return llabs(x[a] - x[b]) + llabs(y[a] - y[b]);
}

void solve() {
	cin >> n >> k >> a >> b;
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	if (a <= k && b <= k) {
		cout << "0\n";
		return;
	}
	bool flag = false;
	if ((a <= k) && (b > k)) swap(a, b);
	if ((b <= k) && (a > k)) flag = true;
	int mdis = 0x3f3f3f3f3f3f3f3f, xdis = 0x3f3f3f3f3f3f3f3f;
	for (int i = 1; i <= k; i++) mdis = min(mdis, dis(i, a));
	for (int i = 1; i <= k; i++) xdis = min(xdis, dis(i, b));
	int ans = dis(a, b);
	if (flag) ans = min(ans, mdis);
	ans = min(ans, xdis + mdis);
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：Imken (赞：0)

思路：

因为任意两个城市的距离为它们的曼哈顿距离，因此任意两个城市之间的路径（不考虑主要城市的情况下）若有第三点的出现，则这条路径不可能比这两点的直接距离更短。

因此，我们可以贪心地构造一条路径，分为两种情况：

1. $a \to {\rm major\ cities} \to b$（因为通过价花费为 $0$ 的边才有可能出现更优的解）
2. $a \to b$

两种情况取最优即可。

Code:

```cpp
inline void solve()
{
	cin >> n >> k >> a >> b;
	for (int i = 1; i <= n; i++) {
		cin >> ct[i].x >> ct[i].y;
		ct[i].maj = (i <= k);
	}
	if (ct[a].maj && ct[b].maj) {
		cout << "0\n";
		return;
	}
	i64 adis = LONG_LONG_MAX / 3, bdis = LONG_LONG_MAX / 3;
	if (!ct[a].maj || k <= 1)
		for (int i = 1; i <= n; i++) {
			if (i == a) continue;
			if (ct[i].maj) {
				i64 dst = dis(ct[i].x, ct[i].y, ct[a].x, ct[a].y);
				if (dst < adis) adis = dst;
			}
		}
	else adis = 0;
	if (!ct[b].maj || k <= 1)
		for (int i = 1; i <= n; i++) {
			if (i == b) continue;
			if (ct[i].maj) {
				i64 dst = dis(ct[i].x, ct[i].y, ct[b].x, ct[b].y);
				if (dst < bdis) bdis = dst;
			}
		}
	else bdis = 0;
	cout << min(adis + bdis, dis(ct[a].x, ct[a].y, ct[b].x, ct[b].y)) << '\n';
}
```


---

## 作者：wanghaoran00 (赞：0)

### 思路
如果希望两点之间**曼哈顿距离**最短，在 $a,b\le k$ 时花费为 $0$。其余情况开始贪心，分别找到距离 $a,b$ 曼哈顿距离最小的点与直接从 $a$ 到 $b$ 比较，取最小值即可。


AC code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define max_n 4000000005
int t,n,k,a,b,ans1,ans2,ans3,maxab,minab;
int x[200005],y[200005];
signed main(){
	scanf("%lld",&t);
	while(t--){
		ans1=max_n,ans2=max_n,ans3=max_n;
		scanf("%lld %lld %lld %lld",&n,&k,&a,&b);
		minab=min(a,b);
		maxab=max(a,b);
        for(int i=1;i<=n;i++){
            scanf("%lld%lld",&x[i],&y[i]);
        }
        //cout<<minab<<" "<<maxab<<endl;
		if(maxab<=k){
			printf("0\n");
		}
		else{
			if(minab<=k){
				for(int i=1;i<=k;i++){
					if(i!=maxab){
						ans1=min(ans1,abs(x[i]-x[maxab])+abs(y[i]-y[maxab]));
					}
				}
				ans3=abs(x[maxab]-x[minab])+abs(y[maxab]-y[minab]);
				printf("%lld\n",min(ans1,ans3));
			}
			else{
				for(int i=1;i<=k;i++){
					if(i!=maxab){//千万不要自己-自己，不然会字面意思爆0
						ans1=min(ans1,abs(x[i]-x[maxab])+abs(y[i]-y[maxab]));
					}
					if(i!=minab){
						ans2=min(ans2,abs(x[i]-x[minab])+abs(y[i]-y[minab]));
					}	
				}
				ans3=abs(x[maxab]-x[minab])+abs(y[maxab]-y[minab]);
				printf("%lld\n",min(ans1+ans2,ans3));
			}
		}
	}
	return 0;
}


```

---

