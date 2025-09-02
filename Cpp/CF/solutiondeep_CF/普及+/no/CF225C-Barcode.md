# 题目信息

# Barcode

## 题目描述

You've got an $ n×m $ pixel picture. Each pixel can be white or black. Your task is to change the colors of as few pixels as possible to obtain a barcode picture.

A picture is a barcode if the following conditions are fulfilled:

- All pixels in each column are of the same color.
- The width of each monochrome vertical line is at least $ x $ and at most $ y $ pixels. In other words, if we group all neighbouring columns of the pixels with equal color, the size of each group can not be less than $ x $ or greater than $ y $ .

## 说明/提示

In the first test sample the picture after changing some colors can looks as follows:

 `<br></br>.##..<br></br>.##..<br></br>.##..<br></br>.##..<br></br>.##..<br></br>.##..<br></br>`In the second test sample the picture after changing some colors can looks as follows:

 `<br></br>.#.#.<br></br>.#.#.<br></br>`

## 样例 #1

### 输入

```
6 5 1 2
##.#.
.###.
###..
#...#
.##.#
###..
```

### 输出

```
11
```

## 样例 #2

### 输入

```
2 5 1 1
#####
.....
```

### 输出

```
5
```

# AI分析结果

### 题目内容
# 条形码

## 题目描述
你有一张 $n×m$ 像素的图片。每个像素可以是白色或黑色。你的任务是改变尽可能少的像素颜色，以获得一张条形码图片。

如果满足以下条件，则一张图片是条形码：
- 每一列中的所有像素颜色相同。
- 每个单色竖线的宽度至少为 $x$ 且至多为 $y$ 像素。换句话说，如果我们将所有颜色相同的相邻列分组，每个组的大小不能小于 $x$ 或大于 $y$。

## 说明/提示
在第一个测试样例中，改变一些颜色后的图片可能如下所示：
`<br></br>.##..<br></br>.##..<br></br>.##..<br></br>.##..<br></br>.##..<br></br>.##..<br></br>`
在第二个测试样例中，改变一些颜色后的图片可能如下所示：
`<br></br>.#.#.<br></br>.#.#.<br></br>`

## 样例 #1
### 输入
```
6 5 1 2
##.#.
.###.
###..
#...#
.##.#
###..
```
### 输出
```
11
```

## 样例 #2
### 输入
```
2 5 1 1
#####
.....
```
### 输出
```
5
```

### 算法分类
动态规划

### 综合分析与结论
这些题解思路基本一致，均采用动态规划解决该问题。核心思路是将二维矩阵转化为线性问题，记录每列转化为黑或白的代价，通过状态转移方程计算最小修改数。解决难点在于如何在动态规划中体现连续相同颜色列数的范围限制。题解们通过设置状态，枚举从当前位置往后 $x$ 到 $y$ 之间的列数进行状态转移，成功解决该难点。

### 所选的题解
- **作者：45dinо (5星)**
    - **关键亮点**：思路清晰，状态定义明确，$dp_{i,0/1}$ 表示考虑到第 $i$ 位，这一位是 $0/1$ ，从下一位开始颜色不同，且前面颜色都符合条件的最小修改数，状态转移方程简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum[1001],n,m,x,y,dp[1001][2];
char c;
int main()
{
    scanf("%d %d %d %d",&n,&m,&x,&y);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            c=0;
            while(c!='#'&&c!='.')
                c=getchar();
            if(c=='#')
                sum[j]++;
        }
    for(int i=1;i<=m;i++)
        sum[i]+=sum[i-1];
    memset(dp,63,sizeof(dp));
    dp[0][0]=0;
    dp[0][1]=0;
    for(int i=0;i<m;i++)
        for(int j=x;j<=y;j++)
        {
            if(i+j>m)
                break;
            dp[i+j][0]=min(dp[i+j][0],dp[i][1]+sum[i+j]-sum[i]);
            dp[i+j][1]=min(dp[i+j][1],dp[i][0]+n*j-sum[i+j]+sum[i]);
        }
    cout<<min(dp[m][0],dp[m][1]);
    return 0;
}
```
    - **核心实现思想**：先统计每列黑色像素的前缀和，初始化动态规划数组，通过两层循环枚举位置和连续列数进行状态转移，最后返回考虑完所有列后两种状态下的最小修改数。
- **作者：fuxuantong123 (4星)**
    - **关键亮点**：详细阐述了动归从收集型到扩散型的转变思路，状态 $f_{i,0/1}$ 表示从 $1$ 到 $i$ 列都满足条件，并且当前列颜色是黑或白的最少修改数，转移方程清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1010];
int b[1010];
int f[2010][2];
int main(){
    int n,m,x,y;
    scanf("%d%d%d%d",&n,&m,&x,&y);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin>>c;
            if(c=='#'){
                b[j]++;
            }
            if(c=='.'){
                a[j]++;
            }
        }
    }
    for(int i=1;i<=m;i++){
        a[i]+=a[i-1];
        b[i]+=b[i-1];
    }
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    f[0][1]=0;
    for(int i=0;i<m;i++){
        for(int j=x;i+j<=m && j<=y;j++){
            f[i+j][0]=min(f[i+j][0],f[i][1]+a[i+j]-a[i]);
            f[i+j][1]=min(f[i+j][1],f[i][0]+b[i+j]-b[i]);
        }
    }
    
    printf("%d",min(f[m][0],f[m][1]));
return 0;
}
```
    - **核心实现思想**：分别统计每列转化为黑色和白色的代价前缀和，初始化动态规划数组，通过两层循环枚举位置和连续列数，根据状态转移方程更新最小修改数。
- **作者：wxzzzz (4星)**
    - **关键亮点**：题意分析清晰，状态定义 $f_{i,k}$ 为使 $1$ 到 $i$ 列满足条件，并且当前位置的颜色为 $k$ 的最小修改数，辅助数组 $w,b$ 定义直观，转移方程简洁。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, x, y, w[1005], b[1005], f[1005][2];
char g[1005][1005];
int main() {
    cin >> n >> m >> x >> y;

    for (int i = 1; i <= n; i++)
        scanf("%s", g[i] + 1);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[j][i] == '.')
                w[i]++;
            else
                b[i]++;
        }

        w[i] += w[i - 1], b[i] += b[i - 1];
    }

    memset(f, 0x3f, sizeof f);
    f[0][0] = f[0][1] = 0;

    for (int i = 0; i < m; i++) {
        for (int j = x; i + j <= m && j <= y; j++) {
            f[i + j][0] = min(f[i + j][0], f[i][1] + b[i + j] - b[i]);
            f[i + j][1] = min(f[i + j][1], f[i][0] + w[i + j] - w[i]);
        }
    }

    cout << min(f[m][0], f[m][1]);
    return 0;
}
```
    - **核心实现思想**：通过遍历矩阵统计每列白色和黑色像素数量的前缀和，初始化动态规划数组，利用两层循环枚举位置和连续列数，依据状态转移方程计算最小修改数。

### 最优关键思路或技巧
将二维矩阵问题转化为线性问题，通过设置合适的动态规划状态（如 $dp_{i,0/1}$ 表示当前列的颜色状态及前面列满足条件的最小修改数），结合前缀和优化计算修改代价，利用双重循环枚举当前位置和连续列数范围进行状态转移，有效解决连续相同颜色列数范围限制的难点。

### 同类型题或类似算法套路拓展
此类题目通常具有一定的限制条件，可通过动态规划解决。关键在于合理定义状态，将复杂限制融入状态转移方程中。类似套路包括在矩阵或序列问题中，对连续段的长度、和、最值等进行限制，通过状态设计和转移方程实现对这些限制的处理。

### 洛谷相似题目推荐
- [P1439 【模板】最长公共子序列](https://www.luogu.com.cn/problem/P1439)：通过动态规划求解两个序列的最长公共子序列，锻炼状态定义和转移方程推导能力。
- [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)：二维动态规划问题，在矩阵中传递纸条求最大得分，涉及状态设计和路径规划。
- [P2782 友好城市](https://www.luogu.com.cn/problem/P2782)：通过动态规划解决区间不相交问题，与本题类似，需合理设计状态和转移方程。 

---
处理用时：93.10秒