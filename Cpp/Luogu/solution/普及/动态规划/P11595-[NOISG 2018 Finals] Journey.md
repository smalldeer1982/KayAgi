# [NOISG 2018 Finals] Journey

## 题目背景

译自 [NOISG 2018 Finals B. Journey](https://github.com/noisg/sg_noi_archive/tree/master/2018/tasks/journey)。

## 题目描述

Kuno 要从 A 市到 B 市旅行，但在路途中他可能会停下来休息。

允许他停留的共有 $N$ 个城市，编号为 $0$ 到 $N-1$，其中 $0$ 号城市表示 A 市，$N-1$ 号城市表示 B 市，编号越大的城市距离 B 市越近。

为了让旅行保持一定的效率，中途停留需要满足以下限制：

- 第 $i$ 次停留的城市必须比第 $i-1$ 次离 B 市**严格**更近。特别地，我们认为第 $0$ 次停留的城市是 A 市。
- 从 A 市出发，直到从 B 市结束停留离开，整个过程不能超过 $M$ 天。换句话说，我们不允许你在 A 市停留，但允许你在 B 市停留。

Kuno 在城市之间的移动和停留基于城市之间的航线和城市中的酒店系统。每个城市 $i$ 都存在 $H$ 条用 $(j,k)$ 表示的航线，表示你可以通过这条航线从城市 $i$ 前往城市 $j$，但是一旦使用这条航线，就必须在城市 $j$ 中停留不少于 $k$ 天。**特别地，每个城市都有一条直接前往 B 市的航线**。

注意可能存在完全相同或起点终点相同的航线，此时你需要把它们视为**不同航线**。你应当忽略远离 B 市的航线。

在飞机中度过的时间忽略不计。

到达一个城市即算作在该城市停留，即使停留了 $0$ 天。

你的任务是，对每一个 $d\in[1,m]$，帮助 Kuno 计数他从 A 市出发到从 B 市结束停留返回花费 $d$ 天的方案数。特别地，若方案数超过 $5\times 10^8$，你只需输出 $5\times 10^8+1$。

两个旅行方案不同当且仅当以下三条任意一条成立：

1. 一个旅行方案中需要在城市 $i$ 停留，而另一个不用。
2. 存在一个城市 $i$，使得两个旅行方案离开该城市的时间不同。**特别地，也包括从 B 市离开的时间不同**。
3. 两个行程都从城市 $i$ 到城市 $j$，但使用的航线不同。

例如，对于两个均为 A 市到 C 市，再从 C 市到 D 市，最后从 D 市到 B 市的旅行方案，如果一个是在第二天离开 C 市，另一个是在第三天离开 C 市，那么它们就是不同的方案。此外，如果输入中存在两条同样从 D 市前往 B 市的航线，即便出发时间和到达时间相同，也是不同的方案。

如你仍无法完全理解题意，请阅读**样例解释**。

## 说明/提示

### 样例 #1 解释

样例 #1 输入描述了一个具有 $4$ 座城市，每个城市有 $3$ 条不同的航线出发的情况：

| 出发城市 | 航线 $1$ 终点 | $\text{Min.}$ | 航线 $2$ 终点 | $\text{Min.}$ | 航线 $3$ 终点 | $\text{Min.}$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| A 市 | 城市 $1$ | $2$ 天 | 城市 $2$ | $2$ 天 | B 市 | $0$ 天 |
| 城市 $1$ | 城市 $2$ | $2$ 天 | 城市 $2$ | $3$ 天 | B 市 | $0$ 天 |
| 城市 $2$ | B 市 | $1$ 天 | B 市 | $3$ 天 | B 市 | $0$ 天 |

为了方便表格描述，我们用 $\text{Min.}$ 表示了每条航线对目的地最少停留天数的要求。

所有 $1$ 天的旅行方案如下；

| 旅行方案 | 方案 |
| :----------: | :----------: |
| $1$ | 在第 $1$ 天从 A 市通过航线 $3$ 抵达 B 市，在 B 市停留 $0$ 天。 |

所有 $2$ 天的旅行方案如下：

| 旅行方案 | 方案 |
| :----------: | :----------: |
| $1$ | 在第 $1$ 天从 A 市通过航线 $3$ 抵达 B 市，在 B 市停留 $1$ 天。 |

所有 $3$ 天的旅行方案如下：

| 旅行方案 | 方案 |
| :----------: | :----------: |
| $1$ | 在第 $1$ 天从 A 市通过航线 $1$ 抵达城市 $1$，在城市 $1$ 停留 $2$ 天；在第 $3$ 天从城市 $1$ 通过航线 $3$ 抵达 B 市，在 B 市停留 $0$ 天。 |
| $2$ | 在第 $1$ 天从 A 市通过航线 $2$ 抵达城市 $2$，在城市 $2$ 停留 $2$ 天；在第 $3$ 天从城市 $2$ 通过航线 $3$ 抵达 B 市，在 B 市停留 $0$ 天。 |
| $3$ | 在第 $1$ 天从 A 市通过航线 $3$ 抵达 B 市，在 B 市停留 $2$ 天。 |

所有 $4$ 天的旅行方案如下：

| 旅行方案 | 方案 |
| :----------: | :----------: |
| $1$ | 在第 $1$ 天从 A 市通过航线 $1$ 抵达城市 $1$，在城市 $1$ 停留 $2$ 天；在第 $3$ 天从城市 $1$ 通过航线 $3$ 抵达 B 市，在 B 市停留 $1$ 天。 |
| $2$ | 在第 $1$ 天从 A 市通过航线 $1$ 抵达城市 $1$，在城市 $1$ 停留 $3$ 天；在第 $4$ 天从城市 $1$ 通过航线 $3$ 抵达 B 市，在 B 市停留 $0$ 天。 |
| $3$ | 在第 $1$ 天从 A 市通过航线 $2$ 抵达城市 $2$，在城市 $2$ 停留 $2$ 天；在第 $3$ 天从城市 $2$ 通过航线 $3$ 抵达 B 市，在 B 市停留 $1$ 天。 |
| $4$ | 在第 $1$ 天从 A 市通过航线 $2$ 抵达城市 $2$，在城市 $2$ 停留 $3$ 天；在第 $4$ 天从城市 $2$ 通过航线 $3$ 抵达 B 市，在 B 市停留 $0$ 天。 |
| $5$ | 在第 $1$ 天从 A 市通过航线 $2$ 抵达城市 $2$，在城市 $2$ 停留 $2$ 天；在第 $3$ 天从城市 $2$ 通过航线 $1$ 抵达 B 市，在 B 市停留 $1$ 天。 |
| $6$ | 在第 $1$ 天从 A 市通过航线 $3$ 抵达 B 市，在 B 市停留 $3$ 天。 |

### 样例 #2 解释

这组样例中除 A 市外所有城市的出发航线均直接到达 B 市。它满足子任务 $1,3,4$。

### 样例 #3 解释

这组样例中所有的航线均不限制目的地最少停留天数。它满足子任务 $2,3,4$。

### 样例 #4 解释

注意若方案数超过 $5\times 10^8$，你只需输出 $5\times 10^8+1$。它满足子任务 $2,3,4$。

### 子任务

对于 $100\%$ 的数据，$N\le 10^4,M\le 400,H\le 100$，其余输入均在此范围下合法。

| 子任务 | 得分 | 数据范围及特殊性质 |
| :----------: | :----------: | :----------: |
| $1$ | $20$ | 除 A 市外所有城市的出发航线均直接到达 B 市，$N,M,H\le 10$ |
| $2$ | $23$ | 所有的航线均不限制目的地最少停留天数，$N,M,H\le 20$ |
| $3$ | $26$ | $N,M,H\le 100$ |
| $4$ | $31$ | 无特殊限制 |


## 样例 #1

### 输入

```
4 4 3
1 2 2 2 3 0
2 2 2 3 3 0
3 1 3 3 3 0```

### 输出

```
1 1 3 6```

## 样例 #2

### 输入

```
4 8 3
1 0 2 1 3 0
3 1 3 2 3 0
3 1 3 1 3 0```

### 输出

```
2 5 11 17 23 29 35 41```

## 样例 #3

### 输入

```
4 11 3
1 0 2 0 3 0
0 0 2 0 3 0
0 0 0 0 3 0```

### 输出

```
4 8 13 19 26 34 43 53 64 76 89```

## 样例 #4

### 输入

```
8 8 8
1 0 1 0 1 0 1 0 1 0 1 0 1 0 7 0
2 0 2 0 2 0 2 0 2 0 2 0 2 0 7 0
3 0 3 0 3 0 3 0 3 0 3 0 3 0 7 0
4 0 4 0 4 0 4 0 4 0 4 0 4 0 7 0
5 0 5 0 5 0 5 0 5 0 5 0 5 0 7 0
6 0 6 0 6 0 6 0 6 0 6 0 6 0 7 0
7 0 7 0 7 0 7 0 7 0 7 0 7 0 7 0```

### 输出

```
960800 6702725 26746084 80092734 199948848 439388874 500000001 500000001```

# 题解

## 作者：tjdyzh (赞：8)

# 主要思路
对于本题，就我而言，第一眼并没有想到动态规划，随即，我打了 dfs。
## 朴素 dfs
定义函数 `dfs(u,val)` 表示现在在城市 $u$ 且时间为 $val$，按题意模拟即可，$20$ 分。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=5e8+1;
struct node{
	int v,w;
	node(){
		v=w=0;
	}
	node(int x,int y){
		v=x;
		w=y;
	}
};
vector<node> e[10010];
//邻接表存图
int ans[410];
int n,m,h;
void dfs(int u,int val){
	//搜到目标，计入答案，跳出递归
	if(u==n-1){
		if(ans[val]==inf) return;
		ans[val]++;
		return ;
	}
	for(auto t:e[u]){
    //沿边搜索
		int v=t.v;
		int w=val+t.w;
		if(w>m){
			continue;
		}
		for(int i=w;i<=m;i++){
			dfs(v,i);
		}
	}
}
int main(){
  //关同步流
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>h;
	for(int i=0;i<n-1;i++){
		for(int j=1;j<=h;j++){
			int v,w;
			cin>>v>>w;
			e[i].push_back(node(v,w));
      //建边
		}
	}
	dfs(0,1);
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<' ';
	}
	return 0;
}
```

## 记忆化搜索
定义函数 `dfs(u,val)` 表示现在在城市 $u$ 且时间为 $val$，令 $f_{i,j}$ 表示现在在城市 $i$ 且时间为 $j$ 的方案数，由于递归的劣势，$43$ 分。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=5e8+1;
struct node{
	int v,w;
	node(){
		v=w=0;
	}
	node(int x,int y){
		v=x;
		w=y;
	}
};
vector<node> e[10010];
int n,m,h;
int f[10010][410];
int dfs(int u,int val){
	int sum=0;
	if(f[u][val]!=0){
		return f[u][val];
	}
	if(u==0&&val==1){
		return 1;
	}
	for(auto t:e[u]){
		int v=t.v;
		int w=val-t.w;
		for(int i=w;i>=1;i--){
			sum+=dfs(v,i);
		}
	}
	return sum;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>h;
	for(int i=0;i<n-1;i++){
		for(int j=1;j<=h;j++){
			int v,w;
			cin>>v>>w;
			if(v>i)
			e[v].push_back(node(i,w));
		}
	}
	for(int i=1;i<=m;i++){
		cout<<dfs(n-1,i)<<' ';
	}
	return 0;
}
```

## 动态规划
由记忆化搜索更改为递推形式，得出动态规划 AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=5e8+1;
struct node{
	int v,w;
	node(){
		v=w=0;
	}
	node(int x,int y){
		v=x;
		w=y;
	}
};
vector<node> e[10010];
int n,m,h;
int f[10010][410];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>h;
	f[0][1]=1;
	for(int i=0;i<n-1;i++){
		for(int j=1;j<=h;j++){
			int v,w;
			cin>>v>>w;
			if(v>i)
			e[i].push_back(node(v,w));
		}
	}
	for(int i=0;i<n-1;i++){
		if(i!=0)
			for(int j=1;j<=m;j++){
				f[i][j]+=f[i][j-1];
				if(f[i][j]>inf) f[i][j]=inf;
			}
		for(auto t:e[i]){
			int v=t.v;
			int w=t.w;
			for(int j=w;j<=m;j++){
				f[v][j]+=f[i][j-w];
				if(f[v][j]>inf) f[v][j]=inf;
			}
		}
	}
	for(int j=1;j<=m;j++){
		f[n-1][j]+=f[n-1][j-1];
		if(f[n-1][j]>inf) f[n-1][j]=inf;
	}
	for(int i=1;i<=m;i++){
		cout<<f[n-1][i]<<' ';
	}
	return 0;
}
```

---

## 作者：AnotherDream (赞：2)

# [P11595](https://www.luogu.com.cn/problem/P11595) 题解
## 思路
简单的 DP，令 $dp_{i,j}$ 为 Kuno 在时间 $j$ 到达城市 $i$ 的方案数。  
初始状态是 $dp_{0,0}$，显然是 $1$。
先枚举所在城市 $i$ 和航线到达的城市 $j$，再枚举到达城市的时间 $k$ 和离开城市的前一天 $l$，将到达的方案数 $dp_{j,l}$ 加上到达前的方案数 $dp_{i,k}$。
## 代码
``` cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, M = 4e2 + 10, K = 1e2 + 10;
int dp[N][M],to[N][K],sty[N][K];
int n,m,h;
signed main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); //快读快写好习惯
    cin>>n>>m>>h;
    for(int i=1;i<n;i++) {
    	for(int j=1;j<=h;j++) {
    		cin>>to[i][j]>>sty[i][j];
    		to[i][j]++;//从1开始
		}
	}
	dp[1][1]=1;//设置初始状态
	for(int i=1;i<n;i++) {//枚举城市
		for(int j=1;j<=h;j++) {
			if(to[i][j]<=i) continue;//不符合严格更近的条件
			for(int k=1;k+sty[i][j]<=m;k++) {
				for(int l=k+sty[i][j];l<=m;l++) {//必须停留sty[i][j]天
                    if(dp[to[i][j]][l]==-114514) break;//避免有溢出
					dp[to[i][j]][l]+=dp[i][k];//状态转移
					if(dp[to[i][j]][l]>500000000) {
						dp[to[i][j]][l]=-114514;//避免有溢出
					}
				}
			}
		}
	}
	for(int i=1;i<=m;i++) {
		if(dp[n][i]==-114514) cout<<"500000001 ";//方案数大于5e8
		else cout<<dp[n][i]<<" ";
	}
	return 0;
}
```

---

## 作者：signed_long_long (赞：2)

# 题目解法

~~看了标签后~~想到 DP。

定义 $f_{i,j}$ 表示第 $j$ 天**离开** $i$ 城的方案数量，那么对于每条航线，所有的 $l\in[b+1,m]$，都可以把 $f_{j,l}$ 增加 $f_{i,l-k}$（就是对于每个可以飞到的时间，把方案数增加飞之前的方案数），在每个循环之前，对于每个 $j\in[2,m]$，都要把 $f_{i,j}$ 增加 $f_{i,j-1}$（停留）。

（表达可能不是特别好，看不懂的看代码）

代码：

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int n,m,h;
int f[10050][404];//第j天离开i城的方案个数 
const int maxn=5e8;
signed main(){
	cin>>n>>m>>h;
	f[0][1]=1;
	for(int i=0;i<n-1;i++){
		if(i!=0){
			for(int j=1;j<=m;j++){
				f[i][j]+=f[i][j-1];
				if(f[i][j]>maxn) f[i][j]=maxn+1;
			}
		}
		for(int j=1;j<=h;j++){
			int a,b;//即题目中的j,k 
			cin>>a>>b;
			if(a<=i) {continue;}
			for(int k=b+1;k<=m;k++){
				f[a][k]+=f[i][k-b];
				if(f[a][k]>maxn) f[a][k]=maxn+1;
			}
		}
	}
	int sum=0;
	for(int i=1;i<=m;i++){
		sum+=f[n-1][i];
		if(sum>maxn) sum=maxn+1;
		printf("%lld ",sum);
	}
	return 0;
}
```

---

## 作者：lzx111218 (赞：0)

# P11595 [NOISG 2018 Finals] Journey
[题目传送门](https://www.luogu.com.cn/problem/P11595)
## 思路

1. **定义状态**：
   - 设 $f_i,_j$ 为从 A 市出发，经过第 $i$ 个城市，花费恰好 $j$ 天的方案数。
   - $e_i$ 用来存储城市 $i$ 出发的航线信息，包括每条航线的目标城市 $v$ 和最小停留天数 $w$。

2. **初始化**：
   - 初始化 $f_0,_1 = 1$，表示从 A 市出发，在第 $1$ 天到达 A 市，开始旅程。

3. **状态转移**：
   - 对于每个城市 $i$，通过航线到达其他城市 $v$，更新 $f_v,_j$。
   - 对每个城市 $i$，每条航线的最小停留天数 $w$ 是已知的，从城市 $i$ 到城市 $v$ 的最大天数 $j$ 也必须满足。

4. **结果**：
   - 通过最终的 $f_n-1_j$，统计从 A 市到 B 市所有可能的旅行方案数。特别地，如果超过 $5 \times 10^8$，就直接返回 $5 \times 10^8 + 1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int MOD = 5e8 + 1,N = 10010,M = 410;
int n, m, h,f[N][M],e[N][M]; 
signed main(){
    scanf("%lld%lld%lld",&n,&m,&h);
    f[0][1] = 1;
    for (int i = 0; i < n - 1; i++) {
        int k = 0;  
        for (int j = 1; j <= h; j++) {
            int v, w;
            scanf("%lld%lld",&v,&w);
            if (v > i) {
                e[i][0]++;  
                e[i][2 * k + 1] = v;  
                e[i][2 * k + 2] = w;  
                k++;
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (i != 0)
            for (int j = 1; j <= m; j++) {
                f[i][j] += f[i][j - 1];
                if (f[i][j] > MOD) f[i][j] = MOD;
            }
        for (int k = 0; k < e[i][0]; k++) {
            int v = e[i][2 * k + 1];  
            int w = e[i][2 * k + 2];  
            for (int j = w; j <= m; j++) {
                f[v][j] += f[i][j - w];
                if (f[v][j] > MOD) f[v][j] = MOD;
            }
        }
    }
    for (int j = 1; j <= m; j++) {
        f[n - 1][j] += f[n - 1][j - 1];
        if (f[n - 1][j] > MOD) f[n - 1][j] = MOD;
    }
    for (int i = 1; i <= m; i++) {
        printf("%lld ",f[n - 1][i]);
    }
    return 0;
}

```

---

## 作者：nightwatch.ryan (赞：0)

### Analysis
本题解中部分思路借鉴了题解区的其他题解，在此表示感谢。

根据题意，定义 $dp_{i,j}$ 为到达第 $i$ 个城市，使用 $j$ 天的方案数。

对于第 $i$ 个城市，有 $H$ 条航线，设第 $j$ 条航线的终点为 $x$，停留时间为 $y$。因为 Kuno 是从第 $1$ 天出发的，且整个过程不能超过 $M$ 天，且到达城市 $x$ 至少要停留 $y$ 天，所以到达城市 $x$ 的合法时间为 $[1 + y, M]$，我们记这个值为 $k$。

则有： 
$$\sum_{k = 1 + y}^{M} dp_{i,k - y} + dp_{x,k} \to dp_{x,k}$$

注意，对于城市 $i$（$i \neq 0$），我们需要在计算上述式子前计算:

$$\sum_{j = 1}^{M} dp_{i,j - 1} + dp_{i,j} \to dp_{i,j}$$

这样才能保证方案数不遗漏。

最后，我们还要累加 $dp_{n - 1,i}$，$i \in [1,M]$，边累加边输出答案。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4 + 5;
const int M = 400 + 5;
const int MOD = 5e8;
int dp[N][M];
int main(){
    int n, m, h, x, y;
    cin >> n >> m >> h;
    dp[0][1] = 1;
    for(int i = 0; i < n - 1; i ++){
        if(i != 0){
            for(int j = 1; j <= m; j ++){
                dp[i][j] += dp[i][j - 1];
                if(dp[i][j] > MOD)
                 dp[i][j] = MOD + 1;
            }
        }
        for(int j = 1; j <= h; j ++){
            cin >> x >> y;
            if(x > i){
                for(int k = y + 1; k <= m; k ++){
                    dp[x][k] += dp[i][k - y];
                    if(dp[x][k] > MOD)
                     dp[x][k] = MOD + 1; 
                }
            }
        }
    }
    for(int i = 1; i <= m; i ++){
        dp[n - 1][i] += dp[n - 1][i - 1];
        if(dp[n - 1][i] > MOD)
         dp[n - 1][i] = MOD + 1;
        cout << dp[n - 1][i] << " ";
    }
}
```

---

## 作者：not_so_littlekayen (赞：0)

代码不难，但思维量不小。

首先看标签，动态规划，那么就意味着我们要去推状态转移方程了。先别急，让我们按照[动态规划五部曲](https://www.bilibili.com/video/BV13Q4y197Wg/?spm_id_from=333.1391.0.0&vd_source=5bfd5c13ee6752dc66a8a4ad62eff9a3)来一遍。


### 1.dp数组及下标的含义

  显然，由题目条件我们定义 $dp_{i,j}$ 为到达第 $i$ 个城市用 $j$ 天的**总方案数**。为什么强调总方案数呢？别急，后面会解释。

### 2.递推公式

  若第 $i$ 个城市前往第 $t$ 个城市需要 $d$ 天（此处 $i < t$），那么我们可以知道

  $\Large dp_{t, p} = dp_{t, p}+dp_{i, p-d}$
  
  这里 $d+1 \leq p \leq m$，解释一下，$d+1$ 是因为默认出发时是第 $1$ 天，剩下的应该很好理解。

  但这个题目有一个特殊的地方在于每个循环开始时有这么一段程序：

  
```cpp
for(int j = 1;j <= m;j++)
{
    dp[i][j] += dp[i][j-1];
  	if(dp[i][j] > Mod)dp[i][j] = Mod;
}
```

这个也不难说明，只要在前一种情况的任意一个城市多停留一天就行。不明白的同学可以看样例一的解析的前两种旅行方案，做个对比或许更好理解。
### 3.初始化
  根据前面所说的
  
      dp[0][1] = 1;
  结束。

### 4.遍历顺序
这个更没啥好说了，按照题目的输入顺序来即可。

### 5.打印数组
略。


代码呢？

有需要的请自取：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, a, b) for(register int i = a;i <= b;i++)
const int Max = 1e4+5, Mod = 5e8+1;
int n, m, h, dp[Max][505], ans;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n >> m >> h;
	dp[0][1] = 1;//非常重要的初始化 
	rep(i, 0, n-2)
	{
		if(i)
		{
			rep(j, 1, m)	
			{
				dp[i][j] += dp[i][j-1];
				if(dp[i][j] > Mod)dp[i][j] = Mod;
			}
		}
		rep(j, 1, h)
		{
			int t, d;//t指到达的城市 d指需要的天数 
			cin >> t >> d;
			if(t <= i)continue ;
			//第 i 次停留的城市必须比第 i-1 次离 B 市严格更近
			rep(p, d+1, m)
			{
				dp[t][p] += dp[i][p-d];
				if(dp[t][p] > Mod)dp[t][p] = Mod;
			}
		}
	}
	rep(i, 1, m)
	{
		dp[n-1][i] += dp[n-1][i-1];
		if(dp[n-1][i] > Mod)dp[n-1][i] = Mod;
	}
	rep(i, 1, m)cout << dp[n-1][i] << " ";
	return 0;
}
```

---

