# Spotlights

## 题目描述

Theater stage is a rectangular field of size $ n×m $ . The director gave you the stage's plan which actors will follow. For each cell it is stated in the plan if there would be an actor in this cell or not.

You are to place a spotlight on the stage in some good position. The spotlight will project light in one of the four directions (if you look at the stage from above) — left, right, up or down. Thus, the spotlight's position is a cell it is placed to and a direction it shines.

A position is good if two conditions hold:

- there is no actor in the cell the spotlight is placed to;
- there is at least one actor in the direction the spotlight projects.

Count the number of good positions for placing the spotlight. Two positions of spotlight are considered to be different if the location cells or projection direction differ.

## 说明/提示

In the first example the following positions are good:

1. the (1, 1) cell and right direction;
2. the (1, 1) cell and down direction;
3. the (1, 3) cell and left direction;
4. the (1, 3) cell and down direction;
5. the (1, 4) cell and left direction;
6. the (2, 2) cell and left direction;
7. the (2, 2) cell and up direction;
8. the (2, 2) and right direction;
9. the (2, 4) cell and left direction.

Therefore, there are $ 9 $ good positions in this example.

## 样例 #1

### 输入

```
2 4
0 1 0 0
1 0 1 0
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4 4
0 0 0 0
1 0 0 1
0 1 1 0
0 1 0 0
```

### 输出

```
20
```

# 题解

## 作者：Zhuluoan (赞：3)

## 题目简述

给出一个 $n$ 行 $m$ 列的 $01$ 矩阵，定义每个点的价值为上下左右四个方向有 $1$ 的方向数，求所有为 $0$ 的点的价值和。

## 题目分析

我们首先可以考虑暴力，但是发现是不行的。于是我们考虑**动态规划**。

设 $dp_{i,j,0/1/2/3}$ 分别表示 $(i,j)$ 这个点上方，左方，下方，右方是否有 $1$。接下来考虑如何转移，我们先考虑上方，显然当 $a_{i-1,j}=1$ 时，$dp_{i,j,1} \leftarrow 1$。如果 $dp_{i-1,j,1}=1$，这也说明 $(i,j)$ 上方有 $1$，所以也有 $dp_{i,j,1} \leftarrow 1$。知道了上方怎么转移，那么其他三个方向也是一样的道理。但是要注意左方和下方的转移顺序。时间复杂度 $\mathcal{O}(n \times m)$，可以通过。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) (rand()%(b-a+1)+a)
#define se second
#define fi first
#define pr pair<int,int>
#define pb push_back
#define ph push
#define ft front
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
const int N=1010;
int n,m,a[N][N],ans,dp[N][N][4]; 
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
	For(i,1,n)
	{
		For(j,1,m)
		{
			cin>>a[i][j];
		}
	} 
	For(i,1,n)
	{
		For(j,1,m)
		{
			if(!a[i][j])
			{
				dp[i][j][0]=dp[i-1][j][0]|a[i-1][j];//利用位运算精简一下
			    dp[i][j][1]=dp[i][j-1][1]|a[i][j-1];
			    ans+=dp[i][j][0]+dp[i][j][1];
			}
		}
	}
	Rep(i,n,1)
	{
		Rep(j,m,1)
		{
			if(!a[i][j])
			{
				dp[i][j][2]=dp[i+1][j][2]|a[i+1][j];
			    dp[i][j][3]=dp[i][j+1][3]|a[i][j+1];
			    ans+=dp[i][j][2]+dp[i][j][3];
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：GaryH (赞：2)

## 蒟蒻又来发题解啦！

本蒟蒻刚刚看见这道题，还以为就是一个纯模拟，然而一写代码，就像这样：

```
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){ans=0;
			if(a[i][j]==0){
				if(i+1<=n&&a[i+1][j]==1)ans++;
				if(i-1>=1&&a[i-1][j]==1)ans++;
				if(j+1<=m&&a[i][j+1]==1)ans++;
				if(j-1>=1&&a[i][j-1]==1)ans++;
				sum+=ans;
			}
		}
	}
```
就在我信心满满时，一测样例——**错了？！**

我又检查了n遍，在确定没有低级代码错误时，便只好从新看看题——**啊！**原来是我把题读错了呀！

然后我便意识到此题应该把每个方向都算出来，于是有了这样的暴力：

```

	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){p1=p2=p3=p4=0;
			if(a[i][j]==0){
				for(register int k=1;k<i;k++){
					if(a[k][j]==1){
						p1=1;break;
					}
				}
				for(register int k=i+1;k<=n;k++){
					if(a[k][j]==1){
						p2=1;break;
					}
				}
				for(register int k=1;k<j;k++){
					if(a[i][k]==1){
						p3=1;break;
					}
				}
				for(register int k=j+1;k<=m;k++){
					if(a[i][k]==1){
						p4=1;break;
					}
				}
			}
			sum+=p1+p2+p3+p4;
		}
	}
	cout<<sum;
```

结果...

[TLE #1](https://www.luogu.com.cn/record/28303112)

所以现在必须想到优化方法，使得此代码复杂度为${O(m*n)}$ ，而不是${O(m*n*log(m*n))}$.

那这样就可以想到用前缀和的方法了,即用ll[i][j][3]表示a(i,j)左边和上面的1的数量，最后再对每一个点进行运算即可.

那我放一下**代码**和**AC记录**：（有注释）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1001][1001],ll[1001][1001][3],ans;
int main(void){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			std::scanf("%d",&a[i][j]);
			//输入,scanf比cin快一些 
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			ll[i][j][1]=ll[i-1][j][1]+a[i][j];
			ll[i][j][2]=ll[i][j-1][2]+a[i][j];
			//预处理ll(前缀和) 
		}
	}
	for(register int i=1;i<=n;i++){
		for(register int j=1;j<=m;j++){
			if(a[i][j]==0){//核心代码 
				ans+=bool(ll[i][j][1]);
				ans+=bool(ll[i][j][2]);
				ans+=bool(ll[n][j][1]-ll[i][j][1]);
				ans+=bool(ll[i][m][2]-ll[i][j][2]);
				//通过已存前缀和计算每一个点的方向值,再用ans累加答案
				//注意,在使用bool强行转换int时,只要原数不是0就是true,只有0才表示false 
			}
		}
	}
	cout<<ans;
	//输出答案
	return 0;
}
```

**AC记录：**

[AC #1](https://www.luogu.com.cn/record/28305815)

### 好了，题解结束了，各位再见！

---

## 作者：pengbubu (赞：1)

## 题意
不得不承认此题的题目意思值得我们细细揣摩（勿喷，语文太差）。我相信在此题的领导下，许多同学都会理解成算出每行的总计加上每列的总计（$0$ 所在的列和行）。

“失败乃成功之母”——这道题既然是统计方案数，那么肯定不是用暴力枚举。那我们就会有一些思考。如果是输出所有为 $0$ 的点的价值和。我们就可以采用逆向思维：**计算所有为 $1$ 的点能影响多少 $0$ 点的数量。**

好吧，既然如此这道题就跟红题没什么区别了。
## 思路
接下来，我们惊奇的发现每一个 $1$，就像**辐射状**扩散至四周。

可是，马上我们就会发现：它好像不是单纯的辐射，有终止条件。通过本人画图实践——发现了触发条件是遇到下一个 $1$，就停止辐射散开。

另一个问题接踵而至：那怎么统计四个方向的情况？

我最终选择的是用一个数组来统计（毕竟此题的数据范围仅仅是 $1000$），当此 $1$ 辐射至一个 $0$ 点（截止到下一个点 $1$），我们就相对应的记录数组对应的点增加 $1$。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
long long ans;//怕炸
bool graph[1005][1005];//因为只有0和1，用bool型存的下
int score[1005][1005];//如果嫌浪费，就用short
void find();//函数声明，见下（个人特殊书写癖好）
int main(){
	scanf("%d%d",&n,&m);//先输入行数和列数
	for(int i=1;i<=n;i++)//再输入整个图
		for(int j=1;j<=m;j++) cin >> graph[i][j];
	find(); //调用函数
	cout << ans;//输出答案
	return 0;
} 
void find(){//函数真身
	for(int i=1;i<=n;i++){//i表示x坐标，j表示y坐标 
	    for(int j=1;j<=m;j++){
	    	if(graph[i][j] == 1){//k是纵坐标 
	    		for(int k=j+1;k<=m;k++){ //先把行全部标记 - 右 
	    			if(graph[i][k] == 1) break;//如果扩散至1，停止。
	    			score[i][k] ++;//将扩散至的0的方向（有1）数+1
	    		} 
	    		for(int k=j-1;k>=0;k--){ //左 
	    			if(graph[i][k] == 1) break;
	    			score[i][k] ++;//和上面的差不多
	    		}//k是横坐标 
	    		for(int k=i+1;k<=n;k++){ //再把列全部标记 - 下 
	    			if(graph[k][j] == 1) break;
	    			score[k][j] ++;
	    		}
	    		for(int k=i-1;k>=0;k--){ //上 
	    			if(graph[k][j] == 1) break;
	    			score[k][j] ++;
	    		}
	    	}
	    }
	}
	//cout << "\n";——>检验代码（输出各个方向有一的数量）。
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(graph[i][j] == 0) ans += score[i][j];
           // cout << score[i][j] << " ";——>检验代码，too
		}
       // cout << "\n";——>检验
	}
}
```
[AC 记录](https://www.luogu.com.cn/record/list?pid=CF729B&user=1163176)

---

## 作者：T_TLucas_Yin (赞：1)

按照题意模拟即可。注意不是指一个点上下左右相邻的格子上 $1$ 的数量，也不是一个点所在行和列上所有 $1$ 的数量和，而是**有 $1$ 的方向的数量**。有点坑。

我们建四个方向的前缀和，但要用布尔类型存，这样对于一个方向上重叠的 $1$ 可以直接过滤为一个 $1$，不会重复判断。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005][1005],sum;
bool f[4][1005][1005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) f[0][i][j]=f[0][i][j-1]+a[i][j];
	for(int i=1;i<=n;i++) for(int j=m;j>=1;j--) f[1][i][j]=f[1][i][j+1]+a[i][j];
	for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) f[2][j][i]=f[2][j-1][i]+a[j][i];
	for(int i=1;i<=m;i++) for(int j=n;j>=1;j--) f[3][j][i]=f[3][j+1][i]+a[j][i];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		if(a[i][j]==0) for(int k=0;k<4;k++) sum+=f[k][i][j];
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：过氧化氢_syq0057 (赞：1)

## Solution

考虑存下每一行每一列最靠边的 ```1``` 的位置，遍历矩阵，每次遇到 ```0``` 判这行这列最靠边的 ```1``` 是否在当前位置的上、下、左或右，最后统计答案即可。

详见代码。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cmath>
#include <queue>
using namespace std;
const int N = 1005;
const int M = 200005;
#define ll long long
const int INF = 0x3f3f3f3f;
const int mod = 1000000007;
inline int read() {
	ll x = 0, f = 1; char ch;
	ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x * f;
}
int n, m;
int a[N][N];
int s[N][2], c[N][2];//s[i][j] j:0min 1max s行c列
int ans; 
int Max(int x, int y) {
	if (x > y) return x;
	return y;
}
int Min(int x, int y) {
	if (x < y) return x;
	return y;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i=1; i<=n; ++i)
		s[i][0] = INF;
	for (int i=1; i<=m; ++i)
		c[i][0] = INF;
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=m; ++j) {
			scanf("%d", &a[i][j]);
			if (a[i][j] == 1) {
				s[i][0] = Min(s[i][0], j);
				s[i][1] = Max(s[i][1], j);
				c[j][0] = Min(c[j][0], i);
				c[j][1] = Max(c[j][1], i);//存最靠边的1
			}
		}
	}
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=m; ++j) {
			if (a[i][j] == 0) {
				if (s[i][0] < j) ans++;
				if (s[i][1] > j) ans++;
				if (c[j][0] < i) ans++;
				if (c[j][1] > i) ans++;//分别统计四个方向的答案
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：I_never_left (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF729B)
### 题目解释
求矩阵中数值为 $0$ 的位置的四个方向有 $1$ 的个数的和。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/gylkx5qk.png)

位置为 $(2,2)$ 的点上、左方都有 $1$ ，而右、下方虽然没有相邻，但也算，所以 $(2,2)$ 点的价值和为 $4$ 。其他点雷同，价值和为 $16$ 。

### 思路
最开始我们想到的是暴力，每次向四个方向循环查找，但 $n$ 和 $m$ 最大 $1000$ ，所以暴力必 $TLE$ 。

然后我们想优化。因为要求四个方向有无 $1$ ，我们就可以在输入时判断当前位置的值如果是 $1$ ，那么说明当前行和列都有 $1$ 。这样算贡献值时，如果当前行有，就查左、右方；如果当前列有，就查上、下方。

继续想，因为每个点只要求每个方向前面有无 $1$ ，所以只要算出每一行、列 $1$ 出现的第一个位置和最后一个位置就可以了。

### 求值细节
算每行、列第一个 $1$ 可以在输入时同时求值，算最后一个 $1$ 时，可以分开算行和列的，两次双重循环，比较好理解。

### 代码和记录
[代码（稍长，放在此处）](https://www.luogu.com.cn/paste/tkwbajck)

[记录（最优解）](https://www.luogu.com.cn/record/98877364)

---

## 作者：LouYiYang1 (赞：0)

# 思路
按题意模拟。

用四个数组来存每个点四个方向有没有 $1$。

## 注意
这道题求的是上下左右四个方向有 $1$ 的方向数，而不是 $1$ 的个数。

至于具体的代码，相信各位仁兄都可以自己写出来，就不放了。

---

## 作者：qusia_MC (赞：0)

## 题意
求所有的 $0$ 上下左右有 $1$ 的方向数之和。**不一定是和 $1$ 紧挨着**。

## 思路

我们可以一下打出暴力，最坏情况是全是 $0$，复杂度为 $O(nm(n+m))$。肯定超时。平均时间复杂度也差不多吧，设 $k$ 为 $0$ 的个数则时间复杂度为 $O(k(n+m))$ 但是 $k$ 是 $10^6$ 级别的，一定超时。

这时候我们就要考虑了：

有什么办法能一下就求出一个区间里有没有 $1$ 呢？？

咱可以这么想：

有 $1\rightarrow$ 查找区间内的和必定 $\ge 1$。

再看一下题，为什么要搞成 $0,1$ 这两个特殊的数字呢？这么一想，就明白了。

那么在想，怎么能快速查找某个区间的和是不是 $\ge 1$ 呢？

那就是：前缀和！

二维的前缀和能做这个（黄）题的人肯定都会吧，不说了。

## 代码

```
#include <bits/stdc++.h>
using namespace std;
int sum[1010][1010], a[1010][1010];
int main()
{
    int n, m, ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
        {
            cin >> a[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];//统计前缀和
        }
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j <= m; j ++)
        {
            if (a[i][j] == 0)//是 0 的话
            {
                if (sum[i][j] - sum[i][j - 1] >= 1) ans ++;//求上面那“条”的和（其他几个是sum[?][0]之类的省略了）若大于等于1就说明有1，答案加1
                if (sum[i][j] - sum[i - 1][j] >= 1) ans ++;//求左面那一“条”的和若大于等于1就说明有1，答案加1
                if (sum[n][j] - sum[i][j] - sum[n][j - 1] + sum[i][j - 1] >= 1)ans ++;
//求下面那“条”的和若大于等于1就说明有1，答案加1
                if (sum[i][m] - sum[i][j] - sum[i - 1][m] + sum[i - 1][j] >= 1)ans ++;
//求右面那“条”的和若大于等于1就说明有1，答案加1
            }
        }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Ryan_Adam (赞：0)

# CF729B Spotlights 题解
**注意此题判的是一整个方向上有没有 $1$。**
## 分析
可以用记忆化搜索的方式来做。

用 $dp_{i,j,0\sim 3}$ 来表示 $i$ 行 $j$ 列的上下左右有没有 $1$。一但你搜索到了 $1$，或者这个位置的同样方向之前搜索到有 $1$，就标记为真。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    const int N = 1005;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int n, m, ans;
    int dp[N][N][4], a[N][N];
    int dfs(int x, int y, int p)
    {
        if (x > n || y > m)
            return 0;
        if (x < 1 || y < 1)
            return 0;
        if (dp[x][y][p] != -1)
            return dp[x][y][p];
        if (a[x][y])
            return 1;
        dp[x][y][p] = dfs(x + dx[p], y + dy[p], p);
        return dp[x][y][p];
    }
    signed work()
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];
        memset(dp,255,sizeof(dp));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (!a[i][j])
                    for (int k = 0; k <= 3; k++)
                        if (dfs(i, j, k))
                            ans++;
        cout << ans << '\n';
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：ivyjiao (赞：0)

**不需要前缀和**。

### 暴力为什么能过？

$1\leq n,m\leq 1000$，因为 CF 机子跑得快，所以 $O(n^3)$ 级别的时间复杂度可过。

而暴力正好就是 $O(n^3)$ 的，但是常数太大，过不了。

显然，暴力需要一定的优化。

### 优化 $1$：快读。

```
inline int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
```

不多解释。

本题读入量较大，能快不少。

### 优化 $2$：记录该点左面、上面是否出现过 $1$。

这个很好记录，开两个一维数组即可。

代码在优化 $3$ 里。

### 优化 $3$：如果该点为 $1$，不对其计算贡献。

显然计算了也无意义。

```
if(a[i][j]){
    c[i]=1;
    d[j]=1;
    continue;
}
if(c[i]) ++b[i][j];
if(d[j]) ++b[i][j];
```

但即使这样，依然 TLE，还有别的优化？

众所周知，CF 可以开火车头，所以我们只需要把火车头加上就能跑得飞快，最大点不超过 700ms。

### 代码：

```
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
using namespace std;
int n,m,b[1001][1001],ans;
bool a[1001][1001],c[1001],d[1001];
inline int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
int main(){
    n=read();
    m=read();
    for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) a[i][j]=read();
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(a[i][j]){
                c[i]=1;
                d[j]=1;
                continue;
            }
            if(c[i]) ++b[i][j];
            if(d[j]) ++b[i][j];
            for(int k=i+1;k<=n;++k){
                if(a[k][j]){
                    ++b[i][j];
                    break;
                }
            }
            for(int k=j+1;k<=m;++k){
                if(a[i][k]){
                    ++b[i][j];
                    break;
                }
            }
            ans+=b[i][j];
        }
    }
    printf("%d",ans);
}
```

---

## 作者：Cute__yhb (赞：0)

## 思路

按题意模拟。用四个数组来存每个点四个方向有没有 $1$。

有一点需要注意，这道题求的是**上下左右四个方向有 $1$ 的方向数**，而不是 $1$ 的个数。

时间复杂度为 $O(nm)$，不会超时。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1005][1005];
bool up[1005][1005],down[1005][1005],Left[1005][1005],Right[1005][1005];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
    //求出四个方向有没有1
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) Left[i][j]=a[i][j]|Left[i][j-1];
		for(int j=m;j;j--) Right[i][j]=a[i][j]|Right[i][j+1];
	}
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++) up[i][j]=a[i][j]|up[i-1][j];
		for(int i=n;i;i--) down[i][j]=down[i+1][j]|a[i][j];
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==0)sum+=Left[i][j]+Right[i][j]+up[i][j]+down[i][j];//统计答案
		}
	}
	cout<<sum;//输出
    return 0;
}
```

---

