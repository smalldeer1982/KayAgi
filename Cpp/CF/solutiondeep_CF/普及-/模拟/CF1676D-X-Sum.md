# 题目信息

# X-Sum

## 题目描述

Timur's grandfather gifted him a chessboard to practice his chess skills. This chessboard is a grid $ a $ with $ n $ rows and $ m $ columns with each cell having a non-negative integer written on it.

Timur's challenge is to place a bishop on the board such that the sum of all cells attacked by the bishop is maximal. The bishop attacks in all directions diagonally, and there is no limit to the distance which the bishop can attack. Note that the cell on which the bishop is placed is also considered attacked. Help him find the maximal sum he can get.

## 说明/提示

For the first test case here the best sum is achieved by the bishop being in this position:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676D/ef38eda1ec7208a8243b8f6ac83d0d9df8a29fbb.png)

## 样例 #1

### 输入

```
4
4 4
1 2 2 1
2 4 2 4
2 2 3 1
2 4 2 4
2 1
1
0
3 3
1 1 1
1 1 1
1 1 1
3 3
0 1 1
1 0 1
1 1 0```

### 输出

```
20
1
5
3```

# AI分析结果

### 题目中文重写
# X - 和

## 题目描述
铁木尔的祖父送给他一个棋盘来练习他的国际象棋技巧。这个棋盘是一个有 $n$ 行和 $m$ 列的网格 $a$，每个单元格上都写有一个非负整数。

铁木尔面临的挑战是在棋盘上放置一个象，使得该象所能攻击到的所有单元格上的数字之和最大。象可以沿对角线的所有方向进行攻击，并且攻击距离没有限制。请注意，象所在的单元格也被视为可攻击的单元格。请帮助他找到他能得到的最大和。

## 说明/提示
对于第一个测试用例，通过将象放置在以下位置可以获得最大和：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676D/ef38eda1ec7208a8243b8f6ac83d0d9df8a29fbb.png)

## 样例 #1

### 输入
```
4
4 4
1 2 2 1
2 4 2 4
2 2 3 1
2 4 2 4
2 1
1
0
3 3
1 1 1
1 1 1
1 1 1
3 3
0 1 1
1 0 1
1 1 0
```

### 输出
```
20
1
5
3
```

### 综合分析与结论
这些题解主要围绕在 $n×m$ 的棋盘上放置象，计算象攻击范围内数字最大和的问题展开，有暴力枚举和预处理优化两种思路。
- **暴力枚举思路**：枚举象的每个可能位置，再遍历其所在的四条斜线上的所有格子，计算攻击范围内的数字和，最后取最大值。时间复杂度为 $O(n^3)$，在数据规模较大时可能超时。
- **预处理优化思路**：利用斜线上点的坐标特征（左下 - 右上斜线上的点 $i + j$ 相等，左上 - 右下斜线上的点 $i - j$ 相等），预处理出每条斜线上数字的总和。枚举象的位置时，直接通过坐标计算该象攻击范围的数字和，避免重复计算。时间复杂度为 $O(n^2)$，效率更高。

### 高评分题解
- **作者：5k_sync_closer（5星）**
    - **关键亮点**：思路清晰，详细解释了利用坐标特征预处理斜线和的方法，代码简洁高效。
    - **核心代码**：
```cpp
#include <cstdio>
#include <cstring>
int T, n, m, s, a[250][250], l[550], r[550];
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        memset(l, 0, sizeof l);
        memset(r, 0, sizeof r);
        scanf("%d%d", &n, &m);s = 0;
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= m;++j)
                scanf("%d", &a[i][j]), l[i + j] += a[i][j], r[i - j + m] += a[i][j];
        for(int i = 1, t;i <= n;++i)
            for(int j = 1;j <= m;++j)
                if((t = l[i + j] + r[i - j + m] - a[i][j]) > s) s = t;
        printf("%d\n", s);
    }
    return 0;
}
```
核心思想：先初始化存储斜线和的数组，输入棋盘数据时计算每条斜线的数字和，最后枚举象的位置，计算攻击范围和并更新最大值。

- **作者：Rosemary_dream（4星）**
    - **关键亮点**：结合图形详细解释了预处理的原理，代码规范，注释清晰。
    - **核心代码**：
```cpp
#include<cstdio>
#include<cstring>
long long ans=0;
long long n,m,t,x,y;
long long p[300][300];
long long L[600],R[600];
signed main()
{
    scanf("%lld",&t);
    while(t--){
	ans=0;
	memset(L,0,sizeof(L));
	memset(R,0,sizeof(R));
	scanf("%lld %lld",&n,&m);
	for(register int i=1;i<=n;i++){
	    for(register int j=1;j<=m;j++){
		scanf("%lld",&p[i][j]);
		L[i+j]+=p[i][j];
		R[i-j+m]+=p[i][j];
		}
	}
	for(register int i=1;i<=n;i++){
	    for(register int j=1;j<=m;j++){
		if(ans<L[i+j]+R[i-j+m]-p[i][j]){
		    ans=L[i+j]+R[i-j+m]-p[i][j];
		}
            }
        }
	printf("%lld\n",ans);
    }
    return 0;
}
```
核心思想：与上一题解类似，先初始化数组，输入数据时预处理斜线和，枚举象位置更新最大和。

- **作者：Mr__Cat（4星）**
    - **关键亮点**：使用 `map` 处理可能出现的负数坐标，思路独特，代码简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101][101];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m,ans=0;;
        cin>>n>>m;
        map<int,int> l,r;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                cin>>a[i][j];
                l[i+j]+=a[i][j];
                r[i-j]+=a[i][j];
            }
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                ans=max(ans,l[i+j]+r[i-j]-a[i][j]);
        cout<<ans<<'\n';
    }
}
```
核心思想：用 `map` 存储斜线和，输入数据时更新，枚举象位置计算最大和。

### 最优关键思路与技巧
利用斜线上点的坐标特征进行预处理，避免了暴力枚举时的重复计算，将时间复杂度从 $O(n^3)$ 优化到 $O(n^2)$。

### 拓展思路
同类型题目可能会改变棋子的移动规则或棋盘的形状，解题时可以先分析棋子移动路径上点的坐标特征，再考虑是否能通过预处理来优化算法。

### 洛谷相似题目推荐
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)：二维平面上的模拟问题，需要考虑坐标和覆盖范围。
- [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)：在方格中寻找最优路径，涉及二维数组和动态规划。
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)：对数字进行排列组合，需要考虑数字拼接后的大小比较。

### 个人心得摘录与总结
题解中未包含个人心得相关内容。 

---
处理用时：40.84秒