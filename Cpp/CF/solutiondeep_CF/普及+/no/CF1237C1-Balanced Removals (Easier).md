# 题目信息

# Balanced Removals (Easier)

## 题目描述

This is an easier version of the problem. In this version, $ n \le 2000 $ .

There are $ n $ distinct points in three-dimensional space numbered from $ 1 $ to $ n $ . The $ i $ -th point has coordinates $ (x_i, y_i, z_i) $ . The number of points $ n $ is even.

You'd like to remove all $ n $ points using a sequence of $ \frac{n}{2} $ snaps. In one snap, you can remove any two points $ a $ and $ b $ that have not been removed yet and form a perfectly balanced pair. A pair of points $ a $ and $ b $ is perfectly balanced if no other point $ c $ (that has not been removed yet) lies within the axis-aligned minimum bounding box of points $ a $ and $ b $ .

Formally, point $ c $ lies within the axis-aligned minimum bounding box of points $ a $ and $ b $ if and only if $ \min(x_a, x_b) \le x_c \le \max(x_a, x_b) $ , $ \min(y_a, y_b) \le y_c \le \max(y_a, y_b) $ , and $ \min(z_a, z_b) \le z_c \le \max(z_a, z_b) $ . Note that the bounding box might be degenerate.

Find a way to remove all points in $ \frac{n}{2} $ snaps.

## 说明/提示

In the first example, here is what points and their corresponding bounding boxes look like (drawn in two dimensions for simplicity, as all points lie on $ z = 0 $ plane). Note that order of removing matters: for example, points $ 5 $ and $ 1 $ don't form a perfectly balanced pair initially, but they do after point $ 3 $ is removed.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237C1/7ad611aa18ed85b1538cfecdeefb390344c16862.png)

## 样例 #1

### 输入

```
6
3 1 0
0 3 0
2 2 0
1 0 0
1 3 0
0 1 0
```

### 输出

```
3 6
5 1
2 4
```

## 样例 #2

### 输入

```
8
0 1 1
1 0 1
1 1 0
1 1 1
2 2 2
3 2 2
2 3 2
2 2 3
```

### 输出

```
4 5
1 6
2 7
3 8
```

# AI分析结果

### 题目内容翻译
# 平衡移除（简单版）

## 题目描述
这是该问题的简单版本。在这个版本中，$ n \le 2000 $。

在三维空间中有 $ n $ 个不同的点，编号从 $ 1 $ 到 $ n $。第 $ i $ 个点的坐标为 $ (x_i, y_i, z_i) $。点的数量 $ n $ 是偶数。

你希望通过 $ \frac{n}{2} $ 次“快照”操作移除所有的 $ n $ 个点。在一次“快照”中，你可以移除任意两个尚未被移除的点 $ a $ 和 $ b $，且这两个点需构成一个完全平衡对。如果没有其他尚未被移除的点 $ c $ 位于点 $ a $ 和 $ b $ 的轴对齐最小边界框内，则称点 $ a $ 和 $ b $ 构成一个完全平衡对。

形式上，点 $ c $ 位于点 $ a $ 和 $ b $ 的轴对齐最小边界框内，当且仅当 $ \min(x_a, x_b) \le x_c \le \max(x_a, x_b) $，$ \min(y_a, y_b) \le y_c \le \max(y_a, y_b) $，且 $ \min(z_a, z_b) \le z_c \le \max(z_a, z_b) $。注意，边界框可能是退化的。

找到一种在 $ \frac{n}{2} $ 次“快照”中移除所有点的方法。

## 说明/提示
在第一个示例中，以下是这些点及其对应的边界框的样子（为简单起见，在二维中绘制，因为所有点都位于 $ z = 0 $ 平面上）。请注意，移除的顺序很重要：例如，点 $ 5 $ 和 $ 1 $ 最初并不构成完全平衡对，但在点 $ 3 $ 被移除后，它们就构成了。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1237C1/7ad611aa18ed85b1538cfecdeefb390344c16862.png)

## 样例 #1
### 输入
```
6
3 1 0
0 3 0
2 2 0
1 0 0
1 3 0
0 1 0
```
### 输出
```
3 6
5 1
2 4
```

## 样例 #2
### 输入
```
8
0 1 1
1 0 1
1 1 0
1 1 1
2 2 2
3 2 2
2 3 2
2 2 3
```
### 输出
```
4 5
1 6
2 7
3 8
```

### 算法分类
枚举

### 综合分析与结论
- **思路对比**：
    - 梧桐灯的题解先按 $x$ 为第一关键字、$y$ 为第二关键字、$z$ 为第三关键字从小到大排序，然后枚举点对，用并查集维护已访问的点，判断点对是否满足条件。
    - Create_Random 的题解认为距离最近的两个点之间无其他点，通过 $n^2$ 暴力求出所有点对的距离，从小到大排序，选择未被标记的点对。
- **算法要点对比**：
    - 梧桐灯使用排序和并查集，通过排序确定枚举顺序，用并查集避免重复访问。
    - Create_Random 使用排序，对所有点对距离排序后按顺序选择。
- **解决难点对比**：
    - 梧桐灯的难点在于判断点对是否满足条件，需要遍历可能的点并检查是否在边界框内。
    - Create_Random 的难点在于证明距离最近的点对一定满足条件，且要处理好标记和选择点对的逻辑。
- **评分**：
    - 梧桐灯：3星。思路较清晰，但代码中嵌套循环较多，复杂度较高，且对并查集的使用在本题中略显复杂。
    - Create_Random：3星。思路简单直接，但距离最近的点对不一定满足条件的证明缺失，存在逻辑漏洞。

### 通用建议与扩展思路
- 对于此类枚举问题，可以先对数据进行预处理，如排序，以减少不必要的枚举。
- 在判断条件时，可以考虑使用更高效的数据结构或算法，如空间划分等，来优化时间复杂度。
- 同类型题或类似算法套路：对于空间中的点的问题，可以考虑使用分治法，将空间划分成更小的区域，减少枚举范围。

### 推荐洛谷题目
- P1036 选数：考察组合枚举的思想。
- P1088 火星人：涉及到全排列的枚举。
- P1157 组合的输出：直接考察组合的枚举实现。

### 重点代码
#### 梧桐灯题解核心代码
```cpp
inline int pd (const int L, const int R) {
    int i, mny = min (s[L].y, s[R].y), mxy = s[L].y + s[R].y - mny;
    int mnz = min (s[L].z, s[R].z), mxz = s[L].z + s[R].z - mnz;
    for (i = Find (1); i <= n && s[i].x <= s[R].x; i = Find (i + 1)) {
        if (i == L || i == R) continue;
        if (s[i].x >= s[L].x && s[i].x <= s[R].x && s[i].y >= mny && s[i].y <= mxy && s[i].z >= mnz && s[i].z <= mxz) return 0;
    }
    return 1;
}
```
核心实现思想：判断点对 $L$ 和 $R$ 是否满足完全平衡对的条件，即检查是否有其他点在它们的轴对齐最小边界框内。

#### Create_Random 题解核心代码
```cpp
for(int i=1;i<=n;i++)
{
    for(int j=i+1;j<=n;j++)
    {
        a[++cnt].l=i;
        a[cnt].r=j;
        a[cnt].v=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j]);
    }
}
sort(a+1,a+cnt+1,cmp);
for(int i=1;i<=cnt;i++)
{
    if(flag[a[i].l]==0&&flag[a[i].r]==0)
    {
        printf("%lld %lld\n",a[i].l,a[i].r);
        flag[a[i].l]=1;
        flag[a[i].r]=1;
    }
}
```
核心实现思想：计算所有点对的距离，排序后按顺序选择未被标记的点对。

---
处理用时：49.53秒