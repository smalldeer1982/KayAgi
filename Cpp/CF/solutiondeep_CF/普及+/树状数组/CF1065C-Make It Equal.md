# 题目信息

# Make It Equal

## 题目描述

There is a toy building consisting of $ n $ towers. Each tower consists of several cubes standing on each other. The $ i $ -th tower consists of $ h_i $ cubes, so it has height $ h_i $ .

Let's define operation slice on some height $ H $ as following: for each tower $ i $ , if its height is greater than $ H $ , then remove some top cubes to make tower's height equal to $ H $ . Cost of one "slice" equals to the total number of removed cubes from all towers.

Let's name slice as good one if its cost is lower or equal to $ k $ ( $ k \ge n $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1065C/658a593f32bf5073d4f1a1a7bd7987feaeb4f838.png)Calculate the minimum number of good slices you have to do to make all towers have the same height. Of course, it is always possible to make it so.

## 说明/提示

In the first example it's optimal to make $ 2 $ slices. The first slice is on height $ 2 $ (its cost is $ 3 $ ), and the second one is on height $ 1 $ (its cost is $ 4 $ ).

## 样例 #1

### 输入

```
5 5
3 1 2 2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 5
2 3 4 5
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
## 使其相等

### 题目描述
有一个由 $n$ 座塔组成的玩具建筑。每座塔由若干个相互堆叠的立方体组成。第 $i$ 座塔由 $h_i$ 个立方体组成，因此它的高度为 $h_i$。

我们定义在某个高度 $H$ 上进行“切片”操作如下：对于每座塔 $i$，如果它的高度大于 $H$，则移除一些顶部的立方体，使塔的高度等于 $H$。一次“切片”的代价等于从所有塔中移除的立方体的总数。

如果一次“切片”的代价小于或等于 $k$（$k \ge n$），则称这次切片为“好的切片”。

计算为了使所有塔的高度相同，你必须进行的最少“好的切片”次数。当然，这总是可以实现的。

### 说明/提示
在第一个样例中，最优的做法是进行 2 次切片。第一次切片在高度 2 处（代价为 3），第二次切片在高度 1 处（代价为 4）。

### 样例 #1
#### 输入
```
5 5
3 1 2 2 4
```
#### 输出
```
2
```

### 样例 #2
#### 输入
```
4 5
2 3 4 5
```
#### 输出
```
2
```

### 综合分析与结论
|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|Blunt_Feeling|用桶标记所有 $h_i$，利用桶的前缀和求出每个高度的方格个数，从上往下遍历，前缀和超过 $k$ 时增加操作次数，最后特判剩余方块|前缀和、桶排序|处理剩余方块的特判|4星|
|Zechariah|用树状数组处理每个高度的箱子数，从上往下模拟切割过程，注意处理最后剩余和 $min==max$ 的情况|树状数组|处理最后剩余和边界情况|3星|
|Z_drj|先枚举切的高度，用线段树维护区间和，二分查找合适的高度，递推记录切高度 $h$ 的贡献开始位置优化复杂度|线段树、二分查找|递推贡献开始位置和线段树操作|3星|
|MY_Lee|用差分统计大于每个数的个数，从最大数开始贪心选择切割高度|差分、贪心|差分优化统计过程|4星|
|bztMinamoto|按高度横着分割，开桶记录点数为 $i$ 的层数，贪心计算每次最多取多少层|桶排序、贪心|处理剩余贡献|3星|
|Fan_Tuan|桶排序统计每种高度正方体的个数，从高到低贪心判断是否能砍|桶排序、贪心|处理不需要砍的情况|3星|

### 所选题解
- **Blunt_Feeling（4星）**
    - 关键亮点：思路清晰，利用前缀和和桶排序简化计算，代码可读性高。
    - 个人心得：作者提到如果不进行最后剩余方块的特判会在测试点 6 出错，强调了特判的重要性。
    - 核心代码：
```cpp
For(i,1,n)
{
    register int a=read();
    h[a]++;
    Min=min(Min,a); //找最大和最小值
    Max=max(Max,a);
}
Rep(i,Max,Min) sum[i]=sum[i+1]+h[i]; //前缀和
int tot=0; //前缀和的和
Rep(i,Max,Min)
{
    if(tot+sum[i]>k)
    {
        ans++;
        tot=0; //tot归零不要忘
    }
    tot+=sum[i];
}
if(tot>n) ans++;
```
- **MY_Lee（4星）**
    - 关键亮点：使用差分优化统计过程，复杂度较低，代码简洁。
    - 核心代码：
```cpp
// 差分预处理
for(register int i=1;i<=n;i++){
    scanf("%d",&x);
    mx=mx>x+1?mx:x+1;
    mn=mn<x?mn:x;
    tong[1]++;
    tong[x+1]--;
}
for(register int i=1;i<=mx;i++){
    tong[i]+=tong[i-1];
}
// 主程序
now=mx-1;
while(now>mn){
    int sum=0;
    while(sum+tong[now]<=k&&now>mn){
        sum+=tong[now];
        now--;
    }
    ans++;
}
```

### 最优关键思路或技巧
- 使用前缀和、差分等技巧优化统计过程，减少时间复杂度。
- 贪心思想，能多取就多取，保证操作次数最少。
- 利用桶排序统计每个高度的方块或箱子数量，方便后续计算。

### 拓展思路
同类型题可以是其他的切割、合并问题，例如木板切割、区间合并等，解题思路通常是先统计相关信息，再利用贪心、二分等算法进行优化。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列的使用。
- [P1181 数列分段Section I](https://www.luogu.com.cn/problem/P1181)：考察二分查找和贪心思想。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：考察二分查找和贪心算法的结合。

### 个人心得总结
- Blunt_Feeling 提到不进行最后剩余方块的特判会导致 WA，强调了边界情况处理的重要性。
- MY_Lee 表示虽然使用的是暴力算法，但通过差分优化可以达到较好的复杂度，说明合理运用算法技巧可以优化暴力算法。 

---
处理用时：33.40秒