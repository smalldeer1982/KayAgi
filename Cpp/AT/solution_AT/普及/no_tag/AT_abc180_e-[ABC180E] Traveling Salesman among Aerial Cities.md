# [ABC180E] Traveling Salesman among Aerial Cities

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc180/tasks/abc180_e

$ 3 $ 次元空間内に $ N $ 個の都市、都市 $ 1 $ から 都市 $ N $ があります。都市 $ i $ は座標 $ (X_i,Y_i,Z_i) $ にあります。

座標 $ (a,b,c) $ の都市から $ (p,q,r) $ の都市に移動する際には $ |p-a|+|q-b|+\max(0,r-c) $ のコストがかかります。

都市 $ 1 $ からスタートし、全ての都市を $ 1 $ 度以上巡って都市 $ 1 $ に戻るまでの最小コストを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 17 $
- $ -10^6\ \leq\ X_i,Y_i,Z_i\ \leq\ 10^6 $
- 同じ座標に複数の都市があることはない
- 入力は全て整数

### Sample Explanation 1

都市 $ 1 $ から都市 $ 2 $ へ向かう時には $ |1-0|+|2-0|+\max(0,3-0)=6 $ のコストがかかります。 都市 $ 2 $ から都市 $ 1 $ へ向かう時には $ |0-1|+|0-2|+\max(0,0-3)=3 $ のコストがかかります。 よって合計で $ 9 $ のコストがかかります。

### Sample Explanation 2

例えば 都市 $ 1 $, $ 2 $, $ 1 $, $ 3 $, $ 1 $ の順に移動するとコストが $ 10 $ になります。途中で都市 $ 1 $ に戻ってきても構いません。

## 样例 #1

### 输入

```
2
0 0 0
1 2 3```

### 输出

```
9```

## 样例 #2

### 输入

```
3
0 0 0
1 1 1
-1 -1 -1```

### 输出

```
10```

## 样例 #3

### 输入

```
17
14142 13562 373095
-17320 508075 68877
223606 -79774 9979
-24494 -89742 783178
26457 513110 -64591
-282842 7124 -74619
31622 -77660 -168379
-33166 -24790 -3554
346410 16151 37755
-36055 51275 463989
37416 -573867 73941
-3872 -983346 207417
412310 56256 -17661
-42426 40687 -119285
43588 -989435 -40674
-447213 -59549 -99579
45825 7569 45584```

### 输出

```
6519344```

# 题解

## 作者：Llx2022 (赞：4)



# 题意

有  $N$  个点  $(x_i,y_i,z_i)$，从 $1$  号点出发，经过所有点，最后返回 $1$ 号点，求最小代价。


$(a,b,c)$   到   $(p,q,r)$     的代价为    $|p-a|+|q-b|+\max(0,r-c)$。 
___
# 思路

**说明**：这是一道旅行旅行商问题，这是一个 **NP** 完全问题。若用暴力解法，即暴力搜索，枚举所有情况，会达到     $O(N!)$   的时间复杂度，因此我们需要使用动态规划解决。


状态压缩是解决该问题已知的最好算法。

**状态定义：**$dp_{vis,city}$   表示已经访问   $vis$ 这个子集，当前在  $city$ 这个点的最小代价。



**转移方程：** 

$$
dp_{S,i}= \min_{j\neq i,j\in S} \left(dp_{S-2^{i},j} + dist_{j,i}\right) 
$$


**初始化**：$\mathit{dp}_{2^{i},i}$      表示从 $1$ 号点直接访问   $i+1$ 号点的代价，这个可以直接算出来。其他状态初始化为 **INF**。


**处理答案：**对于每个   $vis$  和    $city$，我们有两种选择：
    从 $vis$ 中某个已经访问过的点 $i$ 出发，通过     $cost_{i+1,city+1}$       到达     $city+1$   这个点，然后加上已经访问过 $i$ 的最小代价     $dp_{vis-2^{city},i}$。我们取两种选择中最小的一个，作为      $dp_{vis,city}$   的最终值。这样我们就可以得到 $dp$ 数组，最后的答案为    $\min$($dp_{2^{N-1}-1,i}+cost_{i+1,0}$)，即从最后一个     $vis$  中某个点出发经过   $N$ 号点返回 $1$ 号点的最小代价。

**时间复杂度：**

外层循环 $vis$ 有 $2^{N-1}$ 个状态，内层循环   $city$ 有 $N-1$ 个状态，$dp$ 数组的计算代价为 $O(N)$，所以总时间复杂度为 


$${O(2^{N-1} \times (N-1) \times N) = O(2^N \times N^2)}$$  

**空间复杂度：**

$$O(2^{N-1} \times (N-1))=O(2^N)$$  
___


# 代码实现
~~~cpp
#include <iostream>
using namespace std;
using ll = long long;
ll N;
ll cost[20][20];
ll pt[20][3];
ll dp[1<<16][16];
ll INF = 1e18;
int main() {
	cin >> N ;
	for(int i=0;i<N;i++){
		cin >> pt[i][0]>>pt[i][1]>>pt[i][2];
	}
    //j到i的代价
	for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
	    	cost[i][j] = abs(pt[i][0] - pt[j][0])+abs(pt[i][1] - pt[j][1])+max(0LL, pt[i][2]-pt[j][2]);
        }
    }
    //dp的含义是S这个局面,当前所处的位置是j,值是所消耗的代价
    for(int i=0;i<(1<<(N-1));i++){
        for(int j=0;j<N-1;j++){
            dp[i][j]=INF;
        }
    }
    for(int i=0;i<N-1;i++){
        dp[1<<i][i]=cost[0][i+1];
    }
	for(int vis = 1; vis <(1<<(N-1));vis++){
		for(int city = 0; city < N-1; city++){
            //若该点未被访问过
			if((vis>>city)%2==0)continue;
			for(int i=0;i<N-1;i++){
                dp[vis][city]=min(dp[vis][city],dp[vis-(1<<city)][i]+cost[i+1][city+1]);
            }
		}
	}
	ll ans = INF;
	for(int i=0;i<N-1;i++){
        ans=min(ans,dp[(1<<(N-1))-1][i]+cost[i+1][0]);
    }
	cout << ans << endl;
	return 0;

}
~~~

---

## 作者：Strelitzia_ (赞：4)

## 题目大意

三维空间中有 $n$ 个点，第 $i$ 个点的坐标为 $(x_i,y_i,z_i)$。定义从点 $i$ 到点 $j$ 的距离为 $|x_i-x_j|+|y_i-y_j|+\max(0,z_j-z_i)$。问从 $1$ 号点出发经过所有点最后回到 $1$ 号点的最短距离。

## 思路

注意到 $n\le 17$，考虑状态压缩。

我们用 $k$ 表示我们当前考虑到的状态。其中，$k$ 在二进制下的第 $i$ 位上，若为 $1$ 表示已经走过这个点，否则表示没走过。这样我们就保证最后得到的最短路径一定是走过了所有点的，这时的状态为 $2^n-1$。

我们假设已经求出了 $1$ 到所有点的经过所有点的最短路径。那么我们只要找到一个点使 $1$ 到该点的路程与该点到 $1$ 的距离之和最小即可。

接下来考虑用动态规划求最短路径。我们用 $f_{i,k}$ 表示当前在第 $i$ 号点、状态为 $k$ 时的最短路径，此时 $k$ 的第 $i$ 位为 $1$。我们用 $g(i,k)$ 表示在状态 $k$ 中将第 $i$ 位改为 $0$（即将 $i$ 从 $k$ 中去除），那么对于同样在 $k$ 中且不为 $i$ 的点 $j$，有

$$f_{i,k}=\min\{f_{j,g(i,k)}+\text{dis}(j,i)\}\ \ (j\in k,\ j\ne i)$$

于是我们得到了 $O(n^22^n)$ 的可过做法。代码如下：

```cpp
int f[19][1<<19],n;struct T{int x,y,z;}e[N];
int dis(int i,int j){
	return abs__(e[i].x-e[j].x)+abs__(e[i].y-e[j].y)+max(0ll,e[j].z-e[i].z);
}
signed main(){
	memset(f,0x7f,sizeof(f));
	n=read();for(int i=1;i<=n;i++){
		e[i].x=read(),e[i].y=read(),e[i].z=read();
	}f[0][0]=1;for(int i=1;i<=n;i++) f[i][(1<<(i-1))]=0;
	for(int k=1;k<(1<<(n));k++)
		for(int i=2;i<=n;i++){
			if(!((1<<(i-1))&k)) continue;
			for(int j=1;j<=n;j++){
				if(!((1<<(j-1))&k)||i==j) continue;
				f[i][k]=min(f[i][k],f[j][k^(1<<(i-1))]+dis(j,i));
			}
		}
	for(int i=2;i<=n;i++) ans=min(ans,f[i][(1<<n)-1]+dis(i,1));
//	for(int i=1;i<=n;i++) printf("%lld ",f[i][(1<<n)-1]);
	printf("%lld",ans);
}
```

---

## 作者：yuruilin2026 (赞：3)

## 一些闲话：
一道状压 DP，但不理解为什么是黄题。\
[一道差不多的题目](https://www.luogu.com.cn/problem/P1433)。\
好了，不管那么多了，开始讲解：
## 做题思路：
令 $dp_{S,i}$ 表示当前状态为 $S$，目前在第 $i$ 个位置的路径长度。\
这里的状态是一个二进制数，记 $S$ 第 $j$ 位的数字为 $S_j$。\
若 $S_j = 1$，表示第 $j$ 个点走过；否则表示第 $j$ 个点没有走过。\
若上一步在 $j$，这一步在 $i$，则耗费代价记为 $dist_{j,i}$。\
这里注意不是 $dist_{i,j}$，因为从 $i$ 到 $j$ 和从 $j$ 到 $i$ 的距离可能不一样。\
那么可得以下 DP 方程式：$dp_{S,i} = dp_{S-i,j} + dist_{i,j}$。\
其中 $S_j = S_i = 1$。\
注意：$S-i$ 指的是将 $S_i$ 设为 $0$ 之后的状态。
## 一些细节：
由于状压 DP 是把状态压成一个数，所以 $i$ 对应的二进制位为 $S_{i-1}$，前面写 $S_i$ 是为了方便理解。\
取出一个数中的二进制位可以用位运算，具体实现见代码。
## AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
int n;
int dp[514514][20],dist[20][20],x[20],y[20],z[20],answer;
int main(){
	memset(dp,127,sizeof(dp));//初始化 dp[S][i] 为最大值 
	answer = dp[0][0];//初始化 answer 为最大值 
	cin >> n;
	for(int i = 1;i <= n;++i){
		cin >> x[i] >> y[i] >> z[i];
	}
	for(int i = 1;i <= n;++i){
		for(int j = 1;j <= n;++j){
			if(i == j) continue;
			dist[i][j] = abs(x[i]-x[j])+abs(y[i]-y[j])+max(0,z[j] - z[i]);//计算距离 
			//cout << i << " " << j << " " << dist[i][j] << endl;
		}
	}
	for(int i = 1;i <= n;++i) dp[1 << (i-1)][i] = dist[1][i];//初始化状态 
	for(int S = 1;S <= (1 << n)-1;++S){
		for(int i = 1;i <= n;++i){
			if(S & (1 << (i-1))){//取出二进制位并判断是否为 1 
				for(int j = 1;j <= n;++j){
					if(i == j || (S & (1 << (j-1))) == 0) continue;
					dp[S][i] = min(dp[S][i],dp[S-(1 << (i-1))][j] + dist[j][i]);
				}
			}
		}
	}
	for(int i = 1;i <= n;i++) answer = min(answer,dp[(1<<n)-1][i]+dist[i][1]);//记得还要回到 1 
	cout << answer;
	return 0;//完美结束 
}
```

---

## 作者：Your_Name (赞：3)

## 题解

考虑状压。

（一）状态设计：

因为在一样的状态下，最后在哪里才和我们的转移有关，所以设计出如下状态。

$f_{i,j}$ （$i$ 是二进制状态）表示当前状态为 $i$，最后在 $j$ 的最少花费。

这里显然满足 $j\in i$。

（二）状态转移：

转移是显然的：
$$
f_{i,j}=\min_{k\in i} f_{i-2^j,k}+dis(k,j)
$$

（三）实现：

发现直接暴力枚举状态，当前结束点，上一次的结束点，复杂度为 $O(2^N\times N^2)$ 可以通过此题。

注意他最后要回原点，所以统计答案时记得加上。

## AC_Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 20;
int n, x[N], y[N], z[N], f[1 << N][N], ans = 1e9;
int get(int i, int j){
    return abs(x[i] - x[j]) + abs(y[i] - y[j]) + max(0, z[j] - z[i]);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for(int i = 0; i < n; i ++){
        cin >> x[i] >> y[i] >> z[i];
    }
    memset(f, 0x3f, sizeof f);
    f[1][0] = 0;//最开始在0号点
    for(int i = 3; i < (1 << n); i += 2){//0号点永远走了
        for(int j = 0; j < n; j ++){
            if((i >> j) & 1){//j在i中
                for(int k = 0; k < n; k ++){
                    if(k == j)continue;//不能从自己走过来
                    if((i >> k) & 1){//k在i中
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + get(k, j));//上述转移
                    }
                }
            }
        }
    }
    for(int i = 0; i < n; i ++){
        ans = min(ans, f[(1 << n) - 1][i] + get(i, 0));
    }
    cout << ans;
    return 0;
}
```
 _完结撒花。_

---

## 作者：MinimumSpanningTree (赞：2)

由于 $N$ 最大只有 $17$，可以想到状压 dp。

因为遍历完所有点之后还要回到 $1$，但是遍历所有的点的最优方案不一定是回到 $1$ 的最优方案（有可能最后一个被遍历的点到 $1$ 的距离很长），所以考虑加上一维表示最后一个被遍历的点。

于是状态表示就出来了。$dp_{i,j}$ 表示已经被遍历的点的二进制表示集合为 $i$，最后一个被遍历的点为 $j$。对于转移，枚举 $i$ 中为 $1$ 的 $k(k\neq j)$，$dp_{i,j}=min(dp_{i,j},dp_{i\oplus2^{j-1},k}+dis(j,k))$。

最后枚举被遍历的最后一个点，加上最后一个点到 $1$ 的距离，答案即为最小值。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=20,INF=0x3f3f3f3f;
int n,dp[1<<N][N],ans=INF;
struct node
{
	int x,y,z;
}a[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	memset(dp,0x3f,sizeof dp);
	dp[1][1]=0;
	for(int i=2;i<(1<<n);i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(!(i&(1<<(j-1)))) continue;
			for(int k=1;k<=n;k++)
			{
				if(k==j||!(i&(1<<(j-1)))) continue;
				dp[i][j]=min(dp[i][j],dp[i^(1<<(j-1))][k]+abs(a[j].x-a[k].x)+abs(a[j].y-a[k].y)+max(0,a[j].z-a[k].z));
			}
		}
	}
	for(int i=2;i<=n;i++) ans=min(ans,dp[(1<<n)-1][i]+abs(a[1].x-a[i].x)+abs(a[1].y-a[i].y)+max(0,a[1].z-a[i].z));
	printf("%d",ans);
	return 0;
}
```

---

## 作者：umcalla (赞：2)

## 思路
本题要求每个点都走一遍的最小路径，并且 $n \le 17$，那么显然是用状压 DP 来做。

这道题类似于 [P1171](https://www.luogu.com.cn/problem/P1171)，只不过路程改为 $\lvert p - a \rvert + \lvert q - b \rvert + \max(0,r-c)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long dp[1<<19][20];
struct node{
	int x,y,z;
}a[20];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].z);
	memset(dp,0x3f,sizeof dp);
	dp[1][1]=0;
	for(int i=1;i<=1<<n;i++)
		for(int j=1;j<=n;j++)
			if(i&(1<<(j-1)))
				for(int k=1;k<=n;k++)
					if(!(i&(1<<(k-1)))&&j!=k)
						dp[i|(1<<k-1)][k]=min(dp[i|(1<<k)][k],dp[i][j]+abs(a[k].x-a[j].x)+abs(a[k].y-a[j].y)+max(0,a[k].z-a[j].z));
	long long ans=LONG_LONG_MAX;
	for(int i=1;i<=n;i++)
		ans=min(ans,dp[(1<<n)-1][i]+abs(a[1].x-a[i].x)+abs(a[1].y-a[i].y)+max(0,a[1].z-a[i].z));
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：CSPAK_Zhangxiuqi0011 (赞：1)

# 题目描述
一个三维空间内共有 $n$ 个城市，第 $i$ 个城市坐标为 $x_i,y_i,z_i$。定义从 $(a,b,c)$ 到 $(p,q,r)$ 的距离为 $\left\vert p-a \right\vert + \left\vert q-b \right\vert + \max(0,r-c)$。求从 $1$ 城市点出发经过所有城市再返回 $1$ 号城市的最小距离。
# 思路
观察数据范围：$2 \le n \le 17$，很容易就可以想到状压 DP ~~和 dfs~~。这里我们采用状压 DP 来解决。   
我们先定义 $dp_i$ 表示目前我们的访问情况，即访问过的城市对应的二进制位是 $1$，反之则为 $0$。进一步观察可以发现，由于代价和起点终点有关，而仅仅通过 $dp_j$ 转移到 $dp_i$ 我们是不知道是以哪个点为起点的。所以，我们还要记录一下最后一个到达的点是哪个。  
定义 $dp_{i,j}$ 为当前城市访问的情况为 $i$，最后一个到达的城市是 $j$ 号城市。**注意：一定要保证状态 $i$ 里面 $j$ 号城市已经到达了再转移**。那么转移已经很明显了：枚举所有城市，设当前城市编号为 $x$，且未到达 $j$ 号城市的状态是 $l$。若第 $x$ 个城市在状态 $l$ 中被访问过，那么将 $dp_{l,x}$ 转移过来即可。  
最后是输出部分。可以对于城市全部访问的状态下枚举每一个最后访问的城市，将总距离加上该城市到 $1$ 号城市的距离即可算入答案。  
# 注意事项
1. 所有被转移的状态中 $1$ 号城市必须已经经过。
2. 被转移状态的最后到达城市不要是 $1$ 号城市。  
   第 $1$ 条和本条只选择一个应该是可以通过的。
3. 计算答案时一定不要让最后到达的城市是 $1$。  
   第 $2$ 条和本条只选择一个应该是可以通过的。
5. 不要忘记赋初值。
# Code
代码最好别看，自己写哦。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int dp[1048576][25],n;
struct node{
	int x,y,z;
}a[25];
int dis(int x,int y){
	return abs(a[x].x-a[y].x)+abs(a[x].y-a[y].y)+max(0ll,a[x].z-a[y].z); 
}
signed main() {
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i = 1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1][1] = 0;
	for(int i = 3;i<=(1<<n)-1;i = i+2){//i状态始终为奇数，其实就是二进制下个位一定是1，也就是1号城市一定已经经过
		for(int j = 2;j<=n;j++){//枚举最后到达的城市
			if(i&(1<<(j-1))){//确保这个城市在i状态中已经经过
				int now;
				now = i-(1<<(j-1));//即题解中的l（小写的L）状态
				for(int k = 1;k<=n;k++){
					dp[i][j] = min(dp[i][j],dp[now][k]+dis(j,k));
				}
			}
		}
	}
	int ans;
	ans = INT_MAX;
	for(int i = 2;i<=n;i++){
		ans = min(ans,dp[(1<<n)-1][i]+dis(1,i));
	}
	cout<<ans<<"\n";
	return 0;
}

```

---

## 作者：fishing_cat (赞：1)

### 思路

一看数据范围，状压。

考虑状态。一维记录已经到过的点，一维表示当前所在点，记录当前的最小代价。

考虑转移。对于每个合法状态 $dp_{i,j}$，即 $j$ 点属于状态 $i$。记 $get(a,b)$ 为 $a$ 点到 $b$ 点的代价，枚举此次移动前的点 $k$，可以得 
$$dp_{i,j} = \min\{dp_{i - 2^{j-1},k} + get(k, j)\}$$ 

考虑初始化。因为起点为 $1$ 号点，所以可以直接将第一步移动到 $i$ 点初始化，即 $dp_{2^{i-1},i} = get(1, i)$，其余状态初始为负无穷。

最后，输出遍历完所有点后又回到 $1$ 号点的状态，即 $dp_{2^{n}-1, 1}$。 

### code

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define il inline

using namespace std;

const ll inf = 1e18;

ll n, x[20], y[20], z[20], dp[1<<18][20];

il ll get(ll a, ll b) {	return abs(x[a] - x[b]) + abs(y[a] - y[b]) + max(0LL, z[b] - z[a]); }

int main() {
	read(n);
	for (int i = 1; i <= n; i++) 
		read(x[i]); read(y[i]); read(z[i]);

	for (int i = 0; i < (1 << n); i++) 
		for (int j = 1; j <= n; j++) 
			dp[i][j] = inf;

 	for (int i = 2; i <= n; i++) 
		dp[1 << (i-1)][i] = get(1, i);
	
	for (int i = 1; i < (1 << n); i++) 
		for (int j = 1; j <= n; j++) 
			if (((1 << (j-1)) & i) != 0) 
				for (int k = 1; k <= n; k++) 
					dp[i][j] = min(dp[i][j], dp[i - (1 << (j-1))][k] + get(k, j));

	cout << dp[(1 << n) - 1][1] << endl;
	return 0;
}
```

---

## 作者：ICE__LX (赞：1)

典型的平面坐标 TSP 问题，由于数据范围不允许用搜索剪枝，因此考虑状压 dp，那么这就是一道板题了。   
开两个维度，第一维表示压缩的状态，第二维表示到达某个城市的最短距离。易得转换方程：  
$$dp_{s,i}=\min\{dp_{f(s,i),j}+cost(j,i)\}$$
其中 $i,j$ 表示枚举的两个城市，$cost(j,i)$ 表示题目要求的价值函数，$f(s,i)$ 表示在压缩集合中访问的状态。  
时间复杂度 $O(2^n n^2)$，可以通过。
### 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
#define I_love_Foccarus return
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define in(a) a=read()
const int N = 18;
const int inf = 0x7f7f7f7f;
inline int read(){int x=0,f=1,ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-')f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}I_love_Foccarus x*f;}
int x[N],y[N],z[N],n,minx=inf,dp[1<<17][N];
#define cost(i,j) (abs(x[i]-x[j])+abs(y[i]-y[j])+max(0,z[j]-z[i]))   
#define f(s,i) (1<<(i-1))^s
signed main() {
	in(n);
	rep(i,1,n)in(x[i]),in(y[i]),in(z[i]);
	rep(s,1,(1<<n)-1)rep(i,1,n) dp[s][i]=inf;
	rep(i,1,n) dp[(1<<(i-1))][i]=0;
	rep(s,1,(1<<n)-1)rep(i,2,n)if(s&(1<<(i-1)))rep(j,1,n)if((s&(1<<(j-1)))&&i!=j)dp[s][i]=min(dp[s][i],dp[f(s,i)][j]+cost(j,i));
	rep(i,2,n)minx=min(minx,dp[(1<<n)-1][i]+cost(i,1));
	cout<<minx;
	I_love_Foccarus 0;
}
```

---

## 作者：Hhy140516 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc180_e)
# 前言
[这篇题解](https://www.luogu.com.cn/article/25i726q4)害得我对拍了半天，结果是题解错了，请求撤下此篇题解。
# 暴力思路
这题有很强的回溯的感觉，所以我们可以用回溯。

找到它的全排列，然后用 $sum$ 记录此个全排列的权值，求出最小的权值就行了。
# 暴力代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
struct node
{
    int x , y , z ;
}a[18] ;
int n ;
int minn = 1e9 ;
int f[18] ;
void dfs(int step , int sum , int la)
{
    if( step > n + 1 )
    {
        minn = min(minn , sum) ; //求最小的权值
        return ;
    }
    for( int i = 2 ; i <= n ; i++ )
    {
        if(f[i]) continue ;
        f[i] = 1 ;
        if( step <= n )
        {
            dfs( step + 1 , sum + (abs(a[la].x - a[i].x) + abs(a[la].x - a[i].x)) + max(0 , a[i].z - a[la].z) , i ) ; //从上一个的点last到现在的点i的权值
        }
        else
        {
            dfs( step + 1 , sum + (abs(a[la].x - a[1].x) + abs(a[la].x - a[1].x)) + max(0 , a[1].z - a[la].z) , i ) ; //最后要回到1
        }
        f[i] = 0 ;
    }
}
int main()
{
    cin >> n ;
    for( int i = 1 ; i <= n ; i++ )
    {
        cin >> a[i].x >> a[i].y >> a[i].z ;
    }
    dfs(2 , 0 , 1) ; //第一个永远是1
    cout << minn ;
    return 0 ;
}
```
# 正确思路
如果要 AC 的话，就需要用状态压缩。

设计一个状态 $dp _ {i , j}$，表示现在的状态用十进制表示是 $i$，上一个选的点是 $j$。

它的转移也十分简单 $dp _ {i , j} = dp _ {x , k} + jl(k , j)$。

其中，$x$ 是还没有到达过 $i$ 时的十进制状态；而 $k$ 是状态 $x$ 时最后一个到达的点；$jl(i , j)$ 表示 $i$ 到 $j$ 的权值。

初始化时，因为一开始，是在 1 号点，所以 $dp _ {1 , 0} = 0$，一开始没有权值，其余初始化成极大值。
# 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
#define int long long
struct node
{
    int x , y , z ;
}a[17] ;
int n ;
int dp[1 << 17][17] ;
int jl(int i , int j) //计算距离
{
	return abs(a[i].x - a[j].x) + abs(a[i].y - a[j].y) + max(0LL , a[j].z - a[i].z) ;
}
signed main()
{
    memset(dp , 0x3f , sizeof dp) ; //初始成inf
    cin >> n ;
    for( int i = 0 ; i < n ; i++ )
    {
        cin >> a[i].x >> a[i].y >> a[i].z ;
    }
    dp[1][0] = 0 ; //初始化
    for( int i = 1 ; i < (1 << n) ; i++ )
    {
    	for( int j = 1 ; j < n ; j++ ) //中间的时候不能到1点
    	{
    		if((i >> j) & 1) //必须是已经到过的点，才能
    		{
    			int x = (i ^ (1 << j)) ;
    			for( int k = 0 ; k < n ; k++ )
    			{
    				if((x >> k) & 1) //必须是已经到过的点，才能
    				{
    					dp[i][j] = min(dp[i][j] , dp[x][k] + jl(k , j)) ; //转移方程
					}
				}
			}
		}
	}
	int minn = 1e18 ; //没有固定答案，要在最后的所有转态是 (1 << n) - 1 的结果中取最小值
	for( int i = 1 ; i < n ; i++ )
	{
		minn = min(minn , dp[(1 << n) - 1][i] + jl(i , 0)) ;
	}
	cout << minn ;
    return 0 ; //完结撒花
}
```

---

## 作者：Demons_Killer (赞：1)

# 解题思路
该题打暴力的情况会超时，所以我们可以考虑使用动态规划去求所要花费的最小代价。记得要使用状态压缩。状态定义 $dp_{i,j}$ 表示在 $i$ 个子集中，当前在 $j$ 城市要花费的最小代价。可得状态转移方程为 $dp_{i,j}=\min(dp_{i-2^i,j}+dist_{i,j})$。我们所求的答案为对应的子集中加上花费的最小值。

# code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int N;
int cost[20][20];
int pt[20][3];
int dp[1<<16][16];
int maxn = 1e18;
signed main() {
	cin >> N ;
	for(int i=0;i<N;i++){
		cin >> pt[i][0]>>pt[i][1]>>pt[i][2];
	}
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)cost[i][j] = abs(pt[i][0] - pt[j][0])+abs(pt[i][1] - pt[j][1])+max(0ll, pt[i][2]-pt[j][2]);
    for(int i=0;i<(1<<(N-1));i++)for(int j=0;j<N-1;j++)dp[i][j]=maxn;
    for(int i=0;i<N-1;i++){
        dp[1<<i][i]=cost[0][i+1];
    }
	for(int vis = 1; vis <(1<<(N-1));vis++){
		for(int city = 0; city < N-1; city++){
			if((vis>>city)%2==0)continue;
			for(int i=0;i<N-1;i++)dp[vis][city]=min(dp[vis][city],dp[vis-(1<<city)][i]+cost[i+1][city+1]);
		}
	}
	int ans = maxn;
	for(int i=0;i<N-1;i++)ans=min(ans,dp[(1<<(N-1))-1][i]+cost[i+1][0]);
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Symbolize (赞：1)

# $\tt{Solution}$
数据范围很小，但是并不能进行暴搜，所以考虑状压 DP，$f_{s,i}$ 表示，移动到 $j$ 时状态为 $i$ 的最小代价（状态为 $i$ 即当 $i$ 的二进制下第 $k$ 位的数为 $1$，则已经访问过 $k$ 号点了）。我们可以预处理出 $dist_{s,i}$ 表示从 $i$ 到 $j$ 的代价，那么状态转移方程即为：

$$f_{s,i}=\min\limits_{j \in s,i \neq j} (f_{s-2^i,j}+dist_{j,i})$$


```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=1e2+10;
const int M=(1<<20)+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,x[N],y[N],z[N],dist[N][N],f[M][N];
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	rep1(i,0,n-1)
	{
		x[i]=read();
		y[i]=read();
		z[i]=read();
	}
	rep1(i,0,n-1) rep1(j,0,n-1) dist[i][j]=abs(x[i]-x[j])+abs(y[i]-y[j])+max(0ll,z[i]-z[j]);
	memset(f,inf,sizeof f);
	f[1][0]=0;
	rep1(s,1,(1<<n)-1)
		rep1(i,0,n-1)
			if((s>>i)&1)
				rep1(j,0,n-1)
					if(((s^(1<<i))>>j)&1)
						f[s][i]=min(f[s][i],f[s^(1<<i)][j]+dist[j][i]);
	int ans=inf;
	rep1(i,1,n) ans=min(ans,f[(1<<n)-1][i]+dist[i][0]);
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：liruizhou_lihui (赞：0)

这个题根[售货员的难题](https://www.luogu.com.cn/problem/P1171)整体结构不能说完全相同只能说一模一样。只不过计算路程的方法变了。

评黄感觉低了。

状态定义：$dp[i][j]$ 表示在 $i$ 个子集中，当前在 $j$ 城市要花费的最小代价。可得状态转移方程为：


$$dp_{i,j}=\min\{dp_{i-2^i,j},dis_{i,j}\}$$

我们所求的答案为对应的子集中加上花费的最小值。

[AC 记录](https://atcoder.jp/contests/abc180/submissions/63699491)

---

## 作者：AMlhd (赞：0)

## 题目分析

这是一道变种的旅行商问题。不同之处在于城市是在三维空间中，且距离计算有特殊规则：
从坐标 $(x_1,y_1,z_1)$ 到 $(x_2,y_2,z_2)$ 的『距离』为：$|x_2-x_1| + |y_2-y_1| + \max(0,z_2-z_1)$

## 解题思路

使用状态压缩 dp 来解决。设计状态：

- $dp_{S,i}$ 表示已经访问过的城市集合为 S（二进制表示），当前在城市 i 的最小花费
- S 是一个二进制数，其中第 j 位为 1 表示城市 j 已经被访问过

对于当前状态 $dp_{S,i}$，我们可以转移到任何一个未访问过的城市 j：$dp_{S|(1<<j),j} = \min(dp_{S|(1<<j),j}, dp_{S,i} + dist(i,j))$

其中：

- $S|(1<<j)$ 表示将城市 j 标记为已访问

- $dist(i,j)$ 表示从城市 i 到城市 j 的距离

- $dp_{1,0} = 0$（表示初始只访问了城市 0，花费为 0）

- 其他状态初始化为无穷大

最终答案需要考虑从最后一个城市返回城市 0：$ans = \min_{i=0}^{n-1}(dp_{(1<<n)-1,i} + dist(i,0))$

- 时间复杂度：$O(2^n \times n^2)$
  - &#x20;状态数：$2^n \times n$
  - 每个状态的转移需要 $O(n)$ 的时间
- 空间复杂度：$O(2^n \times n)$
  - &#x20;需要储存所有状态

## 代码实现

```cpp
#include <bits/stdc++.h>
#define N 20
#define ll long long
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;

int n;
ll x[N], y[N], z[N], d[N][N], dp[1 << 17][N];

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(ll x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

inline void writeln(ll x) {
	write(x);
	putchar('\n');
}

int main() {
	n = read();
	for (int i = 0; i < n; i++) {
		x[i] = read();
		y[i] = read();
		z[i] = read();
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			d[i][j] =
				abs(x[j] - x[i]) + abs(y[j] - y[i]) + max(0ll, z[j] - z[i]);
		}
	}

	for (int i = 0; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = INF;
		}
	}
	dp[1][0] = 0;

	for (int S = 0; S < (1 << n); S++) {
		if (!(S & 1)) continue;
		for (int i = 0; i < n; i++) {
			if (!(S >> i & 1)) continue;
			for (int j = 0; j < n; j++) {
				if (S >> j & 1) continue;
				dp[S | (1 << j)][j] =
					min(dp[S | (1 << j)][j], dp[S][i] + d[i][j]);
			}
		}
	}

	ll ans = INF;
	for (int i = 1; i < n; i++) {
		ans = min(ans, dp[(1 << n) - 1][i] + d[i][0]);
	}
	writeln(ans);
	return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

$1 \le N \le 17$，一眼状压。

定义 $f_{s,i}$ 表示从 $1$ 走到 $i$，且经过点的状态为 $s$ 的最小代价。不难推出转移方程：$f_{s+2^{j-1},j}=\min(f_{s,i}+val_{i,j})$。其中 $val_{i,j}$ 表示从 $i$ 走到 $j$ 的代价。由于我们在最后还需要回到 $1$，所以答案就是 $\min\{f_{2^n-1,i}+val_{i,1}|1 \le i \le n\}$。

复杂度 $O(2^nn^2)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=18,M=1<<18;
int n;
int x[N],y[N],z[N];
int f[M][N];
int Min=1e18;

il void solve(){
	memset(f,0x3f,sizeof(f)),f[1][1]=0;
	cin>>n;
	for(re int i=1;i<=n;++i) 
		cin>>x[i]>>y[i]>>z[i];
	for(re int i=1;i<(1<<(n));++i)
	for(re int now=1;now<=n;++now)
	if((i>>(now-1))&1)
		for(re int j=1;j<=n;++j)
		if(!((i>>(j-1))&1))
			f[i+(1<<(j-1))][j]=min(f[i+(1<<(j-1))][j],f[i][now]+(abs(x[j]-x[now])+abs(y[j]-y[now])+max(0LL,z[j]-z[now])));
	for(re int i=1;i<=n;++i) 
		Min=min(Min,f[(1<<n)-1][i]+(abs(x[1]-x[i])+abs(y[1]-y[i])+max(0LL,z[1]-z[i])));
	cout<<Min;
	return ;
}

signed main(){
	solve();
	return 0;
}

```


---

## 作者：joe_zxq (赞：0)

# 思路

由于 $1 \le N \le 17$，很显然是一道状压 DP。

$dp_{i,j}$ 指的是状态为 $i$，到达 $j$ 号城市时的最小代价。其中，状态 $i$ 在二进制下从右往左第 $k$ 位指是否访问过 $k$ 号城市。

时间复杂度：$O(2^NN^2)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x[20],y[20],z[20],dis[20][20],dp[(1<<17)+5][20],ans=INT_MAX;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d%d%d",&x[i],&y[i],&z[i]);
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)dis[i][j]=abs(x[i]-x[j])+abs(y[i]-y[j])+max(0,z[j]-z[i]);
	memset(dp,0x3f,sizeof(dp));
	dp[1][0]=0;
	for(int i=1;i<(1<<n);i++)for(int j=0;j<n;j++)if((i>>j)&1){
		int lst=i^(1<<j);
		for(int k=0;k<n;k++)if((lst>>k)&1)dp[i][j]=min(dp[i][j],dp[lst][k]+dis[k][j]);
	}
	for(int i=0;i<n;i++)ans=min(ans,dp[(1<<n)-1][i]+dis[i][0]);
	printf("%d",ans);
	return 0;
}

```

---

