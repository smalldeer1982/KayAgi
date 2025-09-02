# 题目信息

# OpenStreetMap

## 题目描述

Seryozha conducts a course dedicated to building a map of heights of Stepanovo recreation center. He laid a rectangle grid of size $ n \times m $ cells on a map (rows of grid are numbered from $ 1 $ to $ n $ from north to south, and columns are numbered from $ 1 $ to $ m $ from west to east). After that he measured the average height of each cell above Rybinsk sea level and obtained a matrix of heights of size $ n \times m $ . The cell $ (i, j) $ lies on the intersection of the $ i $ -th row and the $ j $ -to column and has height $ h_{i, j} $ .

Seryozha is going to look at the result of his work in the browser. The screen of Seryozha's laptop can fit a subrectangle of size $ a \times b $ of matrix of heights ( $ 1 \le a \le n $ , $ 1 \le b \le m $ ). Seryozha tries to decide how the weather can affect the recreation center — for example, if it rains, where all the rainwater will gather. To do so, he is going to find the cell having minimum height among all cells that are shown on the screen of his laptop.

Help Seryozha to calculate the sum of heights of such cells for all possible subrectangles he can see on his screen. In other words, you have to calculate the sum of minimum heights in submatrices of size $ a \times b $ with top left corners in $ (i, j) $ over all $ 1 \le i \le n - a + 1 $ and $ 1 \le j \le m - b + 1 $ .

Consider the sequence $ g_i = (g_{i - 1} \cdot x + y) \bmod z $ . You are given integers $ g_0 $ , $ x $ , $ y $ and $ z $ . By miraculous coincidence, $ h_{i, j} = g_{(i - 1) \cdot m + j - 1} $ .

## 说明/提示

The matrix from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195E/f7a7b9ecd6a8532f015eda872ed84e65d4581837.png)

## 样例 #1

### 输入

```
3 4 2 1
1 2 3 59
```

### 输出

```
111
```

# AI分析结果

### 题目翻译
Seryozha正在开展一个课程项目，致力于绘制Stepanovo休闲中心的高度地图。他在地图上绘制了一个大小为 $n \times m$ 的矩形网格（网格的行从北到南编号为 $1$ 到 $n$，列从西到东编号为 $1$ 到 $m$）。随后，他测量了每个网格单元相对于雷宾斯克海平面的平均高度，得到了一个大小为 $n \times m$ 的高度矩阵。单元格 $(i, j)$ 位于第 $i$ 行和第 $j$ 列的交叉处，其高度为 $h_{i, j}$。

Seryozha打算在浏览器中查看他的工作成果。他的笔记本电脑屏幕可以显示高度矩阵中一个大小为 $a \times b$ 的子矩形（$1 \leq a \leq n$，$1 \leq b \leq m$）。Seryozha试图判断天气会如何影响休闲中心，例如，如果下雨，所有的雨水会聚集在哪里。为此，他打算找出笔记本电脑屏幕上显示的所有单元格中高度最小的单元格。

请帮助Seryozha计算他在屏幕上能看到的所有可能子矩形中，这些最小高度单元格的高度之和。换句话说，你需要计算所有左上角位于 $(i, j)$ 的 $a \times b$ 子矩阵中最小高度的总和，其中 $1 \leq i \leq n - a + 1$ 且 $1 \leq j \leq m - b + 1$。

考虑序列 $g_i = (g_{i - 1} \cdot x + y) \bmod z$。给定整数 $g_0$、$x$、$y$ 和 $z$。神奇的是，$h_{i, j} = g_{(i - 1) \cdot m + j - 1}$。

### 算法分类
队列

### 综合分析与结论
这些题解主要围绕如何高效计算二维矩阵中所有指定大小子矩形的最小值之和展开。大部分题解采用单调队列的方法，通过两次滑动窗口操作来解决问题，先处理每行的长度为 $b$ 的滑动窗口，再处理每列的长度为 $a$ 的滑动窗口。部分题解还提到了二维RMQ的思路，但由于空间复杂度问题不适用。

### 所选题解
- 作者：柳易辰 (赞：7)，4星
  - 关键亮点：思路清晰，详细解释了单调队列的使用过程，通过图片辅助理解，代码注释清晰。
- 作者：redegg (赞：4)，4星
  - 关键亮点：对单调队列的实现过程解释详细，证明了复杂度为 $O(n\times m)$。
- 作者：Cappuccino_mjj (赞：1)，4星
  - 关键亮点：思路步骤明确，代码结构清晰，使用 `deque` 实现单调队列。

### 重点代码
#### 柳易辰的代码
```c++
#include <stdio.h>
int n, m, a, b, x, y, z;
int g[3001][3001], c[3001][3001], q[3001]; // q 为手写队列
long long w; // w 记录答案
int main()
{
    
    scanf("%d%d%d%d%d%d%d%d", &n, &m, &a, &b, &g[1][1], &x, &y, &z);
    for (int i(1); i < n * m; ++i) // 直接求出原矩形
        g[i / m + 1][i % m + 1] = (1ll * x * g[(i - 1) / m + 1][(i - 1) % m + 1] + y) % z;
    for (int i(1); i <= n; ++i)
    {
        int head(0), tail(-1);
        for (int j(1); j <= m; ++j) // 每行进行滑动窗口
        {
            if (q[head] == j - b && j > b) ++head; // 窗口大小为 b
            while (head <= tail && g[i][q[tail]] >= g[i][j]) --tail;
            q[++tail] = j;
            c[i][j] = g[i][q[head]];
        }
    }
    for (int j(b); j <= m; ++j) // 每列进行滑动窗口
    {
        int head(0), tail(-1);
        for (int i(1); i <= n; ++i)
        {
            if (q[head] == i - a && i > a) ++head; // 窗口大小为 a
            while (head <= tail && c[q[tail]][j] >= c[i][j]) --tail;
            q[++tail] = i;
            if (i >= a && j >= b) w += c[q[head]][j];
        }
    }
    printf("%lld\n", w);
    return 0;
}
```
核心实现思想：先根据给定公式生成原矩阵，然后对每行进行长度为 $b$ 的滑动窗口操作，求出每行每个长度为 $b$ 区间的最小值，存入 $c$ 数组。最后对 $c$ 数组的每列进行长度为 $a$ 的滑动窗口操作，累加每个窗口的最小值得到最终答案。

#### redegg的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
 
int n,m,a,b;
long long x,y,z;
long long g[9000010];
int h[3005][3005];
int minn[3005][3005];
long long ans;
deque<int> p;
 
int main()
{
    scanf("%d%d%d%d",&n,&m,&a,&b);
    scanf("%lld%lld%lld%lld",&g[0],&x,&y,&z);
    for(int i=1;i<=9000005;i++)g[i]=(g[i-1]*x+y)%z;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            h[i][j]=g[(i-1)*m+j-1];
    }
    for(int i=1;i<=n;i++)
    {
        while(!p.empty())p.pop_back();
        for(int j=1;j<=m;j++)
        {
            while(!p.empty()&&p.front()<=j-b)if(!p.empty())p.pop_front();
            while(!p.empty()&&h[i][p.back()]>=h[i][j])if(!p.empty())p.pop_back();
            p.push_back(j);
            minn[i][j]=h[i][p.front()];
        }
    }
    while(!p.empty())p.pop_back();
    for(int j=1;j<=m;j++)
    {
        while(!p.empty())p.pop_back();
        for(int i=1;i<=n;i++)
        {
            while(!p.empty()&&p.front()<=i-a)if(!p.empty())p.pop_front();
            while(!p.empty()&&minn[p.back()][j]>=minn[i][j])if(!p.empty())p.pop_back();
            p.push_back(i);
            if(i>=a&&j>=b)
                ans+=minn[p.front()][j];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```
核心实现思想：先生成原矩阵，然后用双端队列对每行进行长度为 $b$ 的滑动窗口操作，记录每行每个长度为 $b$ 区间的最小值到 `minn` 数组。最后对 `minn` 数组的每列进行长度为 $a$ 的滑动窗口操作，累加最小值得到答案。

#### Cappuccino_mjj的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=9e6+10;
int n,m,a,b;
int x,y,z;
int g[N];
int h[3005][3005];
int hh[3005][3005];
int ans;
signed main()
{
	cin>>n>>m>>a>>b>>g[0]>>x>>y>>z;
	for(int i=1;i<=N;i++)
		g[i]=(g[i-1]*x+y)%z;
	for(int i=1;i<=n;i++)//建造高度数组
		for(int j=1;j<=m;j++)
			h[i][j]=g[(i-1)*m+j-1];
	for(int i=1;i<=n;i++)//扫行
	{
		deque<int>q;//双端队列
		for(int j=1;j<=m;j++)
		{
        //如果超出窗口的范围了，就出队
			while(!q.empty()&&q.front()<=j-b)
				q.pop_front();
        //如果高度搞过枚举的高度，出队
			while(!q.empty()&&h[i][q.back()]>=h[i][j])
				q.pop_back();
			q.push_back(j);
			hh[i][j]=h[i][q.front()];
        //用新建的数组保存新的值
		}
	}
	for(int j=1;j<=m;j++)//扫列
	{
		deque<int>q;
		for(int i=1;i<=n;i++)
		{
        //超出范围就出队
			while(!q.empty()&&q.front()<=i-a)
				q.pop_front();
        //不符合要求就出队
			while(!q.empty()&&hh[q.back()][j]>=hh[i][j])
				q.pop_back();
			q.push_back(i);
			if(i>=a&&j>=b)//保存答案
				ans+=hh[q.front()][j];
		}
	}
	cout<<ans;
	return 0;
}
```
核心实现思想：先生成原矩阵，然后用双端队列对每行进行长度为 $b$ 的滑动窗口操作，将结果存入 `hh` 数组。最后对 `hh` 数组的每列进行长度为 $a$ 的滑动窗口操作，累加最小值得到最终答案。

### 最优关键思路或技巧
使用单调队列进行两次滑动窗口操作，先处理行，再处理列，将二维矩阵的最小值查询问题转化为一维的滑动窗口问题，时间复杂度为 $O(nm)$。

### 拓展思路
同类型题或类似算法套路：可以应用于其他需要在二维矩阵中求指定大小子矩阵最值的问题，如求子矩阵的最大值、子矩阵的和的最值等。还可以拓展到更高维度的数组中，通过多次滑动窗口操作来解决问题。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P2216 [HAOI2007]理想的正方形](https://www.luogu.com.cn/problem/P2216)
3. [P3865 【模板】ST表](https://www.luogu.com.cn/problem/P3865)

### 个人心得
无。

---
处理用时：69.04秒