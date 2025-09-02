# 题目信息

# Colored Rectangles

## 题目描述

You are given three multisets of pairs of colored sticks:

- $ R $ pairs of red sticks, the first pair has length $ r_1 $ , the second pair has length $ r_2 $ , $ \dots $ , the $ R $ -th pair has length $ r_R $ ;
- $ G $ pairs of green sticks, the first pair has length $ g_1 $ , the second pair has length $ g_2 $ , $ \dots $ , the $ G $ -th pair has length $ g_G $ ;
- $ B $ pairs of blue sticks, the first pair has length $ b_1 $ , the second pair has length $ b_2 $ , $ \dots $ , the $ B $ -th pair has length $ b_B $ ;

You are constructing rectangles from these pairs of sticks with the following process:

1. take a pair of sticks of one color;
2. take a pair of sticks of another color different from the first one;
3. add the area of the resulting rectangle to the total area.

Thus, you get such rectangles that their opposite sides are the same color and their adjacent sides are not the same color.

Each pair of sticks can be used at most once, some pairs can be left unused. You are not allowed to split a pair into independent sticks.

What is the maximum area you can achieve?

## 说明/提示

In the first example you can construct one of these rectangles: red and green with sides $ 3 $ and $ 5 $ , red and blue with sides $ 3 $ and $ 4 $ and green and blue with sides $ 5 $ and $ 4 $ . The best area of them is $ 4 \times 5 = 20 $ .

In the second example the best rectangles are: red/blue $ 9       \times 8 $ , red/blue $ 5 \times 5 $ , green/blue $ 2 \times       1 $ . So the total area is $ 72 + 25 + 2 = 99 $ .

In the third example the best rectangles are: red/green $ 19       \times 8 $ and red/blue $ 20 \times 11 $ . The total area is $ 152 + 220 = 372 $ . Note that you can't construct more rectangles because you are not allowed to have both pairs taken to be the same color.

## 样例 #1

### 输入

```
1 1 1
3
5
4```

### 输出

```
20```

## 样例 #2

### 输入

```
2 1 3
9 5
1
2 8 5```

### 输出

```
99```

## 样例 #3

### 输入

```
10 1 1
11 7 20 15 19 14 2 4 13 14
8
11```

### 输出

```
372```

# AI分析结果

### 题目翻译
你会得到三堆带颜色的成对木棍：
- $R$ 对红色木棍，第一对长度为 $r_1$，第二对长度为 $r_2$，以此类推，第 $R$ 对长度为 $r_R$；
- $G$ 对绿色木棍，第一对长度为 $g_1$，第二对长度为 $g_2$，以此类推，第 $G$ 对长度为 $g_G$；
- $B$ 对蓝色木棍，第一对长度为 $b_1$，第二对长度为 $b_2$，以此类推，第 $B$ 对长度为 $b_B$；

你将用这些成对的木棍按以下步骤构建矩形：
1. 选取一对某一种颜色的木棍；
2. 选取一对与第一种颜色不同的木棍；
3. 将得到的矩形面积累加到总面积中。

这样，你得到的矩形其对边颜色相同，邻边颜色不同。

每对木棍最多只能使用一次，有些木棍对可以不使用。不允许将一对木棍拆分成单独的木棍。

你能获得的最大面积是多少？

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是通过动态规划来解决问题。首先根据排序不等式，将每种颜色的木棍按长度从大到小排序，以保证长的边尽可能匹配长的边，使乘积最大化。然后定义状态 $dp_{i,j,k}$ 表示红色取了前 $i$ 个，绿色取了前 $j$ 个，蓝色取了前 $k$ 个时的面积最大值。转移时考虑三种情况：取红色和绿色、红色和蓝色、绿色和蓝色的木棍对组成矩形，取这三种情况的最大值更新当前状态。

不同题解的区别主要在于实现方式，有的使用记忆化搜索（递归），有的使用迭代（循环）；在边界条件处理和最终答案的获取上也有细微差异，部分题解考虑了状态是否可达的判断，而有些题解直接对所有 $dp$ 值取最大值作为答案。

### 所选题解
- **作者：lndjy (赞：8)  ★★★★**
    - 关键亮点：思路清晰，通过记忆化搜索实现动态规划，代码简洁易懂。
- **作者：Ryo_Yamada (赞：7)  ★★★★**
    - 关键亮点：先尝试贪心算法，发现错误后及时转向动态规划，通过记忆化搜索实现，给出了贪心算法的错误示例，对理解题目有帮助。
- **作者：b6e0_ (赞：7)  ★★★★**
    - 关键亮点：考虑了状态是否可达的判断，给出了详细的判断条件，对动态规划的理解有一定的提升。

### 重点代码
#### 作者：lndjy
```cpp
int f[205][205][205];
int r,g,x;
int a[205],b[205],c[205];
long long ans;
int dfs(int i,int j,int k)
{
    if(f[i][j][k]) return f[i][j][k];
    if(i&&j) f[i][j][k]=max(f[i][j][k],dfs(i-1,j-1,k)+a[i]*b[j]);
    if(i&&k) f[i][j][k]=max(f[i][j][k],dfs(i-1,j,k-1)+a[i]*c[k]);
    if(j&&k) f[i][j][k]=max(f[i][j][k],dfs(i,j-1,k-1)+b[j]*c[k]);
    return f[i][j][k];
}
signed main()
{
    cin>>r>>g>>x;
    for(int i=1;i<=r;i++)  cin>>a[i];
    for(int i=1;i<=g;i++)  cin>>b[i];
    for(int i=1;i<=x;i++)  cin>>c[i];
    sort(a+1,a+r+1);
    sort(b+1,b+g+1);
    sort(c+1,c+x+1);
    cout<<dfs(r,g,x);
    return 0;
}
```
核心实现思想：使用记忆化搜索，$dfs(i,j,k)$ 表示红色用了前 $i$ 个，绿色用了前 $j$ 个，蓝色用了前 $k$ 个时的最大面积。通过递归调用 $dfs$ 函数，更新 $f[i][j][k]$ 的值。

#### 作者：Ryo_Yamada
```cpp
const int N = 205;
int R, G, B;
int r[N], g[N], b[N];
long long dp[N][N][N];
long long dfs(int x, int y, int z) {
    if(dp[x][y][z]) return dp[x][y][z];
    if(x && y) dp[x][y][z] = max(dp[x][y][z], dfs(x - 1, y - 1, z) + r[x] * g[y]);
    if(x && z) dp[x][y][z] = max(dp[x][y][z], dfs(x - 1, y, z - 1) + r[x] * b[z]);
    if(z && y) dp[x][y][z] = max(dp[x][y][z], dfs(x, y - 1, z - 1) + b[z] * g[y]);
    return dp[x][y][z];
}
int main() {
    cin >> R >> G >> B;
    for(int i = 1; i <= R; i++) scanf("%d", r + i);
    for(int i = 1; i <= G; i++) scanf("%d", g + i);
    for(int i = 1; i <= B; i++) scanf("%d", b + i);
    sort(r + 1, r + R + 1);
    sort(g + 1, g + G + 1);
    sort(b + 1, b + B + 1);
    cout << dfs(R, G, B);
    return 0;
}
```
核心实现思想：同样使用记忆化搜索，$dfs(x,y,z)$ 表示红、绿、蓝三种颜色分别还剩 $x, y, z$ 个时的最大面积。通过递归更新 $dp[x][y][z]$ 的值。

#### 作者：b6e0_
```cpp
long long a[205],b[205],c[205],dp[205][205][205],ans;
signed main()
{
    int r,g,B,i,j,k;
    cin>>r>>g>>B;
    for(i=1;i<=r;i++)
        cin>>a[i];
    for(i=1;i<=g;i++)
        cin>>b[i];
    for(i=1;i<=B;i++)
        cin>>c[i];
    sort(a+1,a+r+1,greater<long long>());
    sort(b+1,b+g+1,greater<long long>());
    sort(c+1,c+B+1,greater<long long>());
    dp[1][1][0]=a[1]*b[1];
    dp[1][0][1]=a[1]*c[1];
    dp[0][1][1]=b[1]*c[1];
    for(i=0;i<=r;i++)
        for(j=0;j<=g;j++)
            for(k=0;k<=B;k++)
                if(!((i+j+k)&1)&&i+j>=k&&i+k>=j&&j+k>=i)
                {
                    if(i&&j&&dp[i-1][j-1][k])
                        dp[i][j][k]=dp[i-1][j-1][k]+a[i]*b[j];
                    if(i&&k&&dp[i-1][j][k-1])
                        dp[i][j][k]=max(dp[i][j][k],dp[i-1][j][k-1]+a[i]*c[k]);
                    if(j&&k&&dp[i][j-1][k-1])
                        dp[i][j][k]=max(dp[i][j][k],dp[i][j-1][k-1]+b[j]*c[k]);
                    ans=max(ans,dp[i][j][k]);
                }
    cout<<ans;
    return 0;
}
```
核心实现思想：使用迭代方式实现动态规划，通过三重循环遍历所有可能的状态。在更新状态时，先判断状态是否可达（$i+j+k$ 为偶数且满足 $i+j\ge k$、$i+k\ge j$、$j+k\ge i$），然后根据三种情况更新 $dp[i][j][k]$ 的值，并更新最终答案 $ans$。

### 最优关键思路或技巧
- 利用排序不等式，将每种颜色的木棍按长度从大到小排序，保证长的边尽可能匹配长的边，使乘积最大化。
- 定义三维状态 $dp_{i,j,k}$ 来表示不同颜色木棍的选取情况，通过状态转移方程更新状态。
- 可以使用记忆化搜索或迭代的方式实现动态规划。

### 拓展思路
同类型题或类似算法套路：
- 多维动态规划问题，如背包问题的变种，有多个约束条件，需要定义多维状态来解决。
- 涉及多种元素组合并求最优解的问题，通常可以考虑动态规划。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 0 - 1 背包问题，是动态规划的基础题目。
- [P1854 花店橱窗布置](https://www.luogu.com.cn/problem/P1854)：二维动态规划问题，需要考虑多个因素进行状态转移。
- [P2722 总分 Score Inflation](https://www.luogu.com.cn/problem/P2722)：完全背包问题，也是动态规划的常见题型。

### 个人心得摘录与总结
- **作者：Ryo_Yamada**：看到题目第一反应是贪心，交了一发后 WA6，冷静下来造了组 hack 数据发现贪心算法错误，然后转向动态规划。总结：对于此类问题，不能盲目使用贪心算法，要通过具体数据验证算法的正确性，当贪心算法不成立时，考虑动态规划等其他算法。
- **作者：123zbk**：第一眼以为是贪心，但是贪心会漏掉剩余的很多数，然后考虑动态规划。总结：在解题时，要全面考虑各种情况，当贪心算法不能覆盖所有情况时，及时转换思路。

---
处理用时：64.93秒