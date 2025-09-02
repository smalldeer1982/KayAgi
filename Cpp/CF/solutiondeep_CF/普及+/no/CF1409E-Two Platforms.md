# 题目信息

# Two Platforms

## 题目描述

There are $ n $ points on a plane. The $ i $ -th point has coordinates $ (x_i, y_i) $ . You have two horizontal platforms, both of length $ k $ . Each platform can be placed anywhere on a plane but it should be placed horizontally (on the same $ y $ -coordinate) and have integer borders. If the left border of the platform is $ (x, y) $ then the right border is $ (x + k, y) $ and all points between borders (including borders) belong to the platform.

Note that platforms can share common points (overlap) and it is not necessary to place both platforms on the same $ y $ -coordinate.

When you place both platforms on a plane, all points start falling down decreasing their $ y $ -coordinate. If a point collides with some platform at some moment, the point stops and is saved. Points which never collide with any platform are lost.

Your task is to find the maximum number of points you can save if you place both platforms optimally.

You have to answer $ t $ independent test cases.

For better understanding, please read the Note section below to see a picture for the first test case.

## 说明/提示

The picture corresponding to the first test case of the example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1409E/939a53d6a5db677af525f764b29caa6d8ff8f49a.png)

Blue dots represent the points, red segments represent the platforms. One of the possible ways is to place the first platform between points $ (1, -1) $ and $ (2, -1) $ and the second one between points $ (4, 3) $ and $ (5, 3) $ . Vectors represent how the points will fall down. As you can see, the only point we can't save is the point $ (3, 7) $ so it falls down infinitely and will be lost. It can be proven that we can't achieve better answer here. Also note that the point $ (5, 3) $ doesn't fall at all because it is already on the platform.

## 样例 #1

### 输入

```
4
7 1
1 5 2 3 1 5 4
1 3 6 7 2 5 4
1 1
1000000000
1000000000
5 10
10 7 5 15 8
20 199 192 219 1904
10 10
15 19 8 17 20 10 9 2 10 19
12 13 6 17 1 14 7 9 19 3```

### 输出

```
6
1
5
10```

# AI分析结果

### 题目内容翻译
## 两个平台

### 题目描述
平面上有 $n$ 个点。第 $i$ 个点的坐标为 $(x_i, y_i)$。你有两个水平平台，长度均为 $k$。每个平台可以放置在平面上的任意位置，但必须水平放置（即在相同的 $y$ 坐标上），并且边界必须为整数。如果平台的左边界为 $(x, y)$，那么右边界为 $(x + k, y)$，所有位于边界之间（包括边界）的点都属于该平台。

注意，平台可以有公共点（重叠），并且不要求两个平台放置在相同的 $y$ 坐标上。

当你将两个平台放置在平面上后，所有点开始向下掉落，其 $y$ 坐标逐渐减小。如果某个点在某一时刻与某个平台碰撞，该点就会停止并被接住。那些从未与任何平台碰撞的点将会丢失。

你的任务是找到在最优放置两个平台的情况下，能够接住的最多点数。

你需要回答 $t$ 个独立的测试用例。

为了更好地理解，请阅读下面注释部分的内容，查看第一个测试用例的图示。

### 说明/提示
对应示例中第一个测试用例的图示：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1409E/939a53d6a5db677af525f764b29caa6d8ff8f49a.png)

蓝色圆点代表点，红色线段代表平台。一种可能的放置方式是将第一个平台放置在点 $(1, -1)$ 和 $(2, -1)$ 之间，将第二个平台放置在点 $(4, 3)$ 和 $(5, 3)$ 之间。箭头表示点下落的方向。如你所见，我们唯一无法接住的点是 $(3, 7)$，因此它会无限下落并丢失。可以证明，在这里我们无法得到更好的答案。此外，注意点 $(5, 3)$ 根本不会下落，因为它已经在平台上了。

### 样例 #1
#### 输入
```
4
7 1
1 5 2 3 1 5 4
1 3 6 7 2 5 4
1 1
1000000000
1000000000
5 10
10 7 5 15 8
20 199 192 219 1904
10 10
15 19 8 17 20 10 9 2 10 19
12 13 6 17 1 14 7 9 19 3
```

#### 输出
```
6
1
5
10
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是先忽略点的纵坐标，仅考虑横坐标，通过排序和不同的数据结构或算法来解决问题。多数题解利用了贪心思想，即认为在最优方案中平台的左端点一定与某一个点的 $x$ 坐标一样。不同题解在实现细节和使用的数据结构上有所不同，如有的使用双指针，有的使用线段树、ST 表等。

### 所选题解
- **Karry5307（5星）**
    - **关键亮点**：思路清晰，代码简洁，不使用复杂数据结构和双指针，仅通过简单的指针扫描和后缀最大值的计算就解决了问题，时间复杂度低。
    - **核心代码**：
```cpp
inline void solve()
{
    n=read(),kk=read();
    for(register int i=1;i<=n;i++)
    {
        x[i]=read();
    }
    for(register int i=1;i<=n;i++)
    {
        read();
    }
    sort(x+1,x+n+1),r=1,res=0,f[n+1]=mx[n+1]=0;
    for(register int i=1;i<=n;i++)
    {
        while(r<n&&x[r+1]-x[i]<=kk)
        {
            r++;
        }
        f[i]=r-i+1;
    }
    for(register int i=n;i;i--)
    {
        mx[i]=max(mx[i+1],f[i]);
    }
    for(register int i=1;i<=n;i++)
    {
        res=max(res,f[i]+mx[i+f[i]]);
    }
    printf("%d\n",res);
}
```
    - **核心实现思想**：先读取输入并对 $x$ 坐标排序，然后用指针扫描计算以每个点为左端点的平台能接住的点数 $f[i]$，再计算后缀最大值 $mx[i]$，最后枚举第一个平台的左端点，通过 $f[i]+mx[i+f[i]]$ 计算最大接住点数。

- **EternalEpic（4星）**
    - **关键亮点**：通过预处理 $lpos$ 和 $rpos$ 数组，分别表示在区间 $[1, i]$ 和 $[i, n]$ 中放板的最大答案，最后将每一项加起来得到结果，思路简洁，时间复杂度合理。
    - **核心代码**：
```cpp
for (int i = 1, pos = 1; i <= n; i++) {
    while (pos < n && a[pos + 1] - a[i] <= k) ++pos;
    rpos[i] = pos - i + 1;
} for (int i = n - 1; i >= 1; i--) chkmax(rpos[i], rpos[i + 1]);

for (int i = n, pos = n; i >= 1; i--) {
    while (pos > 1 && a[i] - a[pos - 1] <= k) --pos;
    lpos[i] = i - pos + 1; 
} for (int i = 2; i <= n; i++) chkmax(lpos[i], lpos[i - 1]);

int ans = 0;
for (int i = 1; i < n; i++) chkmax(ans, lpos[i] + rpos[i + 1]);
```
    - **核心实现思想**：先计算 $rpos$ 数组，表示以每个点为左端点的平台能覆盖的点数，再处理得到后缀最大值；然后计算 $lpos$ 数组，表示以每个点为右端点的平台能覆盖的点数，处理得到前缀最大值；最后枚举中间点，计算 $lpos[i] + rpos[i + 1]$ 的最大值。

- **MagicalSheep（4星）**
    - **关键亮点**：使用线性 DP 的方法，通过状态转移方程逐步求解，思路清晰，代码实现简洁，易于理解。
    - **核心代码**：
```cpp
for (int i = 1, j = 1, cnt = 1; i <= n; i++)
{
    while (x[j] + k < x[i])
        ++j, --cnt;
    f[i][0] = max(f[i - 1][0], cnt);
    f[i][1] = max(f[i - 1][1], f[j - 1][0] + cnt);
    ++cnt;
}
```
    - **核心实现思想**：使用滑动窗口的方式计算以第 $i$ 个点为结尾的平台能接住的点数 $cnt$，通过状态转移方程 $f[i][0] = \max\{f[i - 1][0], cnt\}$ 和 $f[i][1] = \max\{f[i - 1][1], f[j - 1][0] + cnt\}$ 逐步更新状态，最终得到 $f[n][1]$ 即为答案。

### 最优关键思路或技巧
- 忽略纵坐标，仅考虑横坐标，简化问题。
- 利用贪心思想，认为平台左端点与某点 $x$ 坐标相同能得到最优解。
- 通过预处理数组（如后缀最大值、前缀最大值等）来优化枚举过程，降低时间复杂度。

### 拓展思路
同类型题目通常会涉及在一维或二维空间中放置线段、矩形等图形，以覆盖最多的点或满足其他条件。类似算法套路包括贪心策略的运用、动态规划的状态设计与转移、双指针或二分查找的优化等。

### 推荐题目
- P2642 双子序列最大和
- P3143 [USACO16OPEN] Diamond Collector S
- P1886 滑动窗口 /【模板】单调队列

### 个人心得摘录与总结
- **二gou子**：一开始使用错误的贪心策略，认为先放入能接住最多点的平台，再从剩下的中找最大值是最优的，但最后一组数据成为反例。之后尝试暴力枚举超时，最终通过 ST 表和倒着循环解决了区间定位问题，总结出做题时不能盲目使用贪心，要多考虑特殊情况，遇到区间查询问题可以考虑合适的数据结构优化。
- **kradcigam**：通过参加 div3 并 AK 该题，总结出在解决问题时要善于发现问题的本质，将问题转化为已有的模型（如双子序列最大和），同时利用贪心结论（线段不重叠、端点为点的坐标）简化问题。 

---
处理用时：65.37秒