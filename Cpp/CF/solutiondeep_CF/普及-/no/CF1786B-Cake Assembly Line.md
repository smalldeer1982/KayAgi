# 题目信息

# Cake Assembly Line

## 题目描述

A cake assembly line in a bakery was once again optimized, and now $ n $ cakes are made at a time! In the last step, each of the $ n $ cakes should be covered with chocolate.

Consider a side view on the conveyor belt, let it be a number line. The $ i $ -th cake occupies the segment $ [a_i - w, a_i + w] $ on this line, each pair of these segments does not have common points. Above the conveyor, there are $ n $ dispensers, and when a common button is pressed, chocolate from the $ i $ -th dispenser will cover the conveyor segment $ [b_i - h, b_i + h] $ . Each pair of these segments also does not have common points.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1786B/346ba483d975827d12cf4a1c8655bc16066dc283.png) Cakes and dispensers corresponding to the first example.The calibration of this conveyor belt part has not yet been performed, so you are to make it. Determine if it's possible to shift the conveyor so that each cake has some chocolate on it, and there is no chocolate outside the cakes. You can assume that the conveyour is long enough, so the cakes never fall. Also note that the button can only be pressed once.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1786B/9d91448781ebe899dcbaa2a5c7ae76c17064ee03.png) In the first example we can shift the cakes as shown in the picture.

## 说明/提示

The first example is shown in the figures in the statement.

In the second example, we can move the conveyor, for example, so that the centers of the cakes are at $ 4, 9, 14, 19, 24 $ .

In the third example, we can't move the conveyor accordingly.

## 样例 #1

### 输入

```
4
3 10 5
65 95 165
40 65 145
5 2 1
1 6 11 16 21
4 9 14 19 24
3 3 2
13 22 29
5 16 25
4 4 1
27 36 127 136
35 50 141 144```

### 输出

```
YES
YES
NO
YES```

# AI分析结果

### 蛋糕生产线
#### 题目描述
一家面包店的蛋糕生产线再次进行了优化，现在一次可以制作 $n$ 个蛋糕！在最后一步，每个蛋糕都应该覆盖上巧克力。

考虑传送带的侧视图，将其看作一条数轴。第 $i$ 个蛋糕占据数轴上的区间 $[a_i - w, a_i + w]$，这些区间两两没有公共点。在传送带上方，有 $n$ 个分配器，当按下一个公共按钮时，第 $i$ 个分配器的巧克力将覆盖传送带区间 $[b_i - h, b_i + h]$。这些区间两两也没有公共点。

![蛋糕和分配器对应第一个示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1786B/346ba483d975827d12cf4a1c8655bc16066dc283.png)

这个传送带部分的校准尚未完成，所以你来完成它。判断是否有可能移动传送带，使得每个蛋糕上都有一些巧克力，并且巧克力不会超出蛋糕范围。你可以假设传送带足够长，所以蛋糕永远不会掉落。另外请注意，按钮只能按下一次。

![在第一个示例中我们可以像图中那样移动蛋糕](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1786B/9d91448781ebe899dcbaa2a5c7ae76c17064ee03.png)

#### 说明/提示
第一个示例在题目中的图中展示。

在第二个示例中，我们可以移动传送带，例如，使蛋糕的中心位于 $4, 9, 14, 19, 24$。

在第三个示例中，我们无法相应地移动传送带。

#### 样例 #1
**输入**
```
4
3 10 5
65 95 165
40 65 145
5 2 1
1 6 11 16 21
4 9 14 19 24
3 3 2
13 22 29
5 16 25
4 4 1
27 36 127 136
35 50 141 144
```
**输出**
```
YES
YES
NO
YES
```

- **算法分类**：数学
- **综合分析与结论**：这些题解的核心思路都是通过计算每个蛋糕与对应分配器之间的相对位置关系，确定蛋糕可移动的范围，然后判断所有蛋糕可移动范围是否存在交集来得出能否满足题目要求。不同题解在具体计算可移动范围的方式和判断逻辑上略有差异，但本质相同。时间复杂度均为 $O(n)$。
- **所选的题解**：
  - **作者：c20231020（5星）**
    - **关键亮点**：思路清晰简洁，直接计算每个蛋糕合法移动区间的左端点最大值与右端点最小值，通过比较两者大小判断是否有解，代码实现简洁明了。
    - **核心代码**：
```cpp
void solve(){
    cin>>n>>w>>h;int l=-2e9,r=2e9;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)cin>>b[i];
    for(int i=1;i<=n;++i){
        l=max(a[i]-w-b[i]+h,l);r=min(a[i]+w-b[i]-h,r);
        if(l>r){
            cout<<"no\n";
            return;
        }
    }
    cout<<"Yes\n";
    return;
}
```
  - **作者：qfpjm（4星）**
    - **关键亮点**：通过第一个蛋糕位置确定后续蛋糕位置，利用每个蛋糕对应喷嘴限制第一个蛋糕可移动范围，逐步缩小范围判断是否有解，思路独特。
    - **核心代码**：
```cpp
for (int i = 2 ; i <= n ; i ++)
{
    c[i] = a[i] - a[i - 1];
}
bool flag = 0;
int l = min(b[1] - h + w, b[1] + h - w);
int r = max(b[1] - h + w, b[1] + h - w);
int L = l, R = r;
for (int i = 2 ; i <= n ; i ++)
{
    l = min(b[i] - h + w, b[i] + h - w);
    r = max(b[i] - h + w, b[i] + h - w);
    L = max(L + c[i], l);
    R = min(R + c[i], r);
    if (L > R)
    {
        flag = 1;
        break;
    }
}
if (flag)
{
    puts("NO");
    continue;
}
puts("YES");
```
  - **作者：BFSDFS123（4星）**
    - **关键亮点**：直接计算每个蛋糕所能移动的距离区间，然后判断这些区间是否有交集，逻辑直接易懂，代码实现较为简洁。
    - **核心代码**：
```cpp
int L=-inf,R=inf;
for(int i=1;i<=n;i++)
{
    int nl=Ar[i]-b[i]-(w-h);
    int nr=Ar[i]-b[i]+(w-h);
    if(L>nr)
    {
        puts("NO");
        return ;
    }
    if(nl>R)
    {
        puts("NO");
        return ;
    }
    L=max(L,nl);
    R=min(R,nr);
}
if(L>R)
{
    puts("NO");
    return ;
}
puts("YES");
```
- **最优关键思路或技巧**：通过分析蛋糕和分配器覆盖区间的相对位置，计算每个蛋糕可移动的区间范围，然后通过判断这些区间的交集情况来解决问题，这种将实际问题转化为区间计算和判断的思维方式是关键。
- **可拓展之处**：同类型题可考察不同形状物体的覆盖、排列等问题，类似算法套路是先确定每个元素的可行范围，再通过判断范围的交集、并集等情况得出结论。
- **推荐洛谷题目**：
  - P1083 [NOIP2012 提高组] 借教室：同样涉及区间判断与可行性分析。
  - P2678 [NOIP2015 提高组] 跳石头：通过二分答案结合区间判断来解决问题，与本题思路有相似之处。
  - P3957 [NOIP2017 提高组] 跳房子：涉及区间的计算和决策，与本题在分析区间关系上有类似思维。
- **个人心得**：无。 

---
处理用时：42.83秒