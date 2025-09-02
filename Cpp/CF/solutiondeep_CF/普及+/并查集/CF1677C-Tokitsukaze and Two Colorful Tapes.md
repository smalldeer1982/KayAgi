# 题目信息

# Tokitsukaze and Two Colorful Tapes

## 题目描述

Tokitsukaze has two colorful tapes. There are $ n $ distinct colors, numbered $ 1 $ through $ n $ , and each color appears exactly once on each of the two tapes. Denote the color of the $ i $ -th position of the first tape as $ ca_i $ , and the color of the $ i $ -th position of the second tape as $ cb_i $ .

Now Tokitsukaze wants to select each color an integer value from $ 1 $ to $ n $ , distinct for all the colors. After that she will put down the color values in each colored position on the tapes. Denote the number of the $ i $ -th position of the first tape as $ numa_i $ , and the number of the $ i $ -th position of the second tape as $ numb_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ba8639f69fd74760b5261096016619c105b9cbe6.png)For example, for the above picture, assuming that the color red has value $ x $ ( $ 1 \leq x \leq n $ ), it appears at the $ 1 $ -st position of the first tape and the $ 3 $ -rd position of the second tape, so $ numa_1=numb_3=x $ .

Note that each color $ i $ from $ 1 $ to $ n $ should have a distinct value, and the same color which appears in both tapes has the same value.

After labeling each color, the beauty of the two tapes is calculated as $ $$$\sum_{i=1}^{n}|numa_i-numb_i|. $ $$$

Please help Tokitsukaze to find the highest possible beauty.

## 说明/提示

An optimal solution for the first test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/eb5a2fd8a44a35877d106dc26e9dcf9fd0a2a486.png)The beauty is $ \left|4-3 \right|+\left|3-5 \right|+\left|2-4 \right|+\left|5-2 \right|+\left|1-6 \right|+\left|6-1 \right|=18 $ .

An optimal solution for the second test case is shown in the following figure:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ec6542f7ba45f38760ee0d113e52ba6999ceef87.png)The beauty is $ \left|2-2 \right|+\left|1-6 \right|+\left|3-3 \right|+\left|6-1 \right|+\left|4-4 \right|+\left|5-5 \right|=10 $ .

## 样例 #1

### 输入

```
3
6
1 5 4 3 2 6
5 3 1 4 6 2
6
3 5 4 6 2 1
3 6 4 5 2 1
1
1
1```

### 输出

```
18
10
0```

# AI分析结果

### 题目中文重写
# Tokitsukaze与两条彩色胶带

## 题目描述
Tokitsukaze有两条彩色胶带。有 $ n $ 种不同的颜色，编号从 $ 1 $ 到 $ n $，且每种颜色在两条胶带上都恰好出现一次。记第一条胶带第 $ i $ 个位置的颜色为 $ ca_i $，第二条胶带第 $ i $ 个位置的颜色为 $ cb_i $。

现在Tokitsukaze想为每种颜色从 $ 1 $ 到 $ n $ 中选取一个整数值，且所有颜色的值都不同。之后，她会将颜色值写在胶带上每个有颜色的位置上。记第一条胶带第 $ i $ 个位置的数字为 $ numa_i $，第二条胶带第 $ i $ 个位置的数字为 $ numb_i $。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ba8639f69fd74760b5261096016619c105b9cbe6.png)例如，对于上图，假设红色的值为 $ x $（$ 1 \leq x \leq n $），它出现在第一条胶带的第 $ 1 $ 个位置和第二条胶带的第 $ 3 $ 个位置，所以 $ numa_1=numb_3=x $。

注意，从 $ 1 $ 到 $ n $ 的每种颜色 $ i $ 都应该有一个不同的值，并且在两条胶带上都出现的相同颜色具有相同的值。

标记完每种颜色后，两条胶带的美观度计算如下：
$$\sum_{i=1}^{n}|numa_i - numb_i|$$

请帮助Tokitsukaze找到可能的最高美观度。

## 说明/提示
第一个测试用例的一个最优解如下图所示：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/eb5a2fd8a44a35877d106dc26e9dcf9fd0a2a486.png)美观度为 $ \left|4 - 3 \right| + \left|3 - 5 \right| + \left|2 - 4 \right| + \left|5 - 2 \right| + \left|1 - 6 \right| + \left|6 - 1 \right| = 18 $。

第二个测试用例的一个最优解如下图所示：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1677C/ec6542f7ba45f38760ee0d113e52ba6999ceef87.png)美观度为 $ \left|2 - 2 \right| + \left|1 - 6 \right| + \left|3 - 3 \right| + \left|6 - 1 \right| + \left|4 - 4 \right| + \left|5 - 5 \right| = 10 $。

## 样例 #1

### 输入
```
3
6
1 5 4 3 2 6
5 3 1 4 6 2
6
3 5 4 6 2 1
3 6 4 5 2 1
1
1
1
```

### 输出
```
18
10
0
```

### 综合分析与结论
- **思路对比**：四位作者均将问题转化为图论中的环问题，通过分析环的性质来求解。其中，I_am_Accepted、Leasier和Renshey思路相似，都从边权和的角度出发，考虑点权的正负贡献；Union_Find则使用并查集来处理环。
- **算法要点**：核心要点是找出图中的环，计算每个环的长度，确定每个环中能作为“山峰”（正贡献）和“山谷”（负贡献）的点的数量，进而计算出所有环中“山峰”的总数 $k$，最终答案为 $2k(n - k)$。
- **解决难点**：关键在于理解如何将问题转化为环问题，以及如何确定每个环中能产生最大贡献的点的数量。

### 所选题解
- **I_am_Accepted（5星）**
    - **关键亮点**：思路清晰，引入“山峰”“山谷”“山坡”的概念，便于理解；代码简洁，使用深度优先搜索（DFS）来计算环的长度。
    - **核心代码**：
```cpp
int dfs(int x){
    vis[x]=1;
    if(vis[b[x]]) return 1;
    else return 1+dfs(b[x]);
}
void work(){
    cin>>n;
    int x;
    For(i,1,n){
        cin>>x;
        a[x]=i;
    }
    For(i,1,n){
        cin>>x;
        b[i]=a[x];
    }
    ans=0;
    For(i,1,n) vis[i]=0;
    For(i,1,n) if(!vis[i]) ans+=dfs(i)>>1;
    cout<<2*ans*(n-ans)<<endl;
}
```
核心实现思想：通过DFS遍历图，找出所有环并计算其长度，将每个环长度的一半累加到 `ans` 中，最后根据公式 $2\times ans\times(n - ans)$ 计算答案。

- **Leasier（4星）**
    - **关键亮点**：详细分析了绝对值展开后的三种情况，贪心策略明确；代码使用传统的输入输出方式，可读性较高。
    - **核心代码**：
```cpp
for (int j = 1; j <= n; j++){
    if (!vis[j]){
        int size = 0;
        for (int k = j;!vis[k]; k = b[pos[k]]){
            vis[k] = true;
            size++;
        }
        sum += size / 2;
    }
}
printf("%lld\n", (ll)2 * sum * (n - sum));
```
核心实现思想：遍历所有未访问的点，通过循环找出环的长度，将每个环长度的一半累加到 `sum` 中，最后根据公式 $2\times sum\times(n - sum)$ 计算答案。

- **Renshey（4星）**
    - **关键亮点**：对题意的转化和分析准确，给出了详细的时间复杂度和空间复杂度分析；使用快速读入优化输入。
    - **核心代码**：
```cpp
inline void solve (void)
{
    n = read(); int w = 0;
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) b[read()] = i;
    for (int i = 1; i <= n; i++) if (!vis[i])
    {
        int len = 0;
        for (int j = i;!vis[j]; j = b[a[j]]) vis[j] = true, len++;
        w += len >> 1;
    }
    printf("%lld\n", 2LL * (n - w) * w);
    for (int i = 1; i <= n; i++) vis[i] = false;
}
```
核心实现思想：通过快速读入读取数据，遍历所有未访问的点，找出环的长度，将每个环长度的一半累加到 `w` 中，最后根据公式 $2\times w\times(n - w)$ 计算答案。

### 最优关键思路或技巧
- **图论建模**：将问题转化为图论中的环问题，通过分析环的性质来求解。
- **贪心策略**：尽量让较大的数产生正贡献，较小的数产生负贡献，以达到边权和最大。
- **深度优先搜索（DFS）**：用于找出图中的环并计算其长度。

### 可拓展之处
同类型题或类似算法套路包括：
- 其他排列组合问题，可通过构建图模型，利用环的性质求解。
- 涉及绝对值求和的优化问题，可考虑拆分绝对值，分析正负贡献。

### 洛谷推荐题目
- P1387 最大正方形
- P1006 传纸条
- P1169 棋盘制作

---
处理用时：40.72秒