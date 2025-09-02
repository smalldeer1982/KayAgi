# 题目信息

# Run For Your Prize

## 题目描述

You and your friend are participating in a TV show "Run For Your Prize".

At the start of the show $ n $ prizes are located on a straight line. $ i $ -th prize is located at position $ a_{i} $ . Positions of all prizes are distinct. You start at position $ 1 $ , your friend — at position $ 10^{6} $ (and there is no prize in any of these two positions). You have to work as a team and collect all prizes in minimum possible time, in any order.

You know that it takes exactly $ 1 $ second to move from position $ x $ to position $ x+1 $ or $ x-1 $ , both for you and your friend. You also have trained enough to instantly pick up any prize, if its position is equal to your current position (and the same is true for your friend). Carrying prizes does not affect your speed (or your friend's speed) at all.

Now you may discuss your strategy with your friend and decide who will pick up each prize. Remember that every prize must be picked up, either by you or by your friend.

What is the minimum number of seconds it will take to pick up all the prizes?

## 说明/提示

In the first example you take all the prizes: take the first at $ 1 $ , the second at $ 2 $ and the third at $ 8 $ .

In the second example you take the first prize in $ 1 $ second and your friend takes the other in $ 5 $ seconds, you do this simultaneously, so the total time is $ 5 $ .

## 样例 #1

### 输入

```
3
2 3 9
```

### 输出

```
8
```

## 样例 #2

### 输入

```
2
2 999995
```

### 输出

```
5
```

# AI分析结果

### 题目内容（中文重写）
# 为你的奖品奔跑

## 题目描述
你和你的朋友正在参加一个名为“为你的奖品奔跑”的电视节目。

节目开始时，有 $n$ 个奖品位于一条直线上。第 $i$ 个奖品位于位置 $a_{i}$，所有奖品的位置都不同。你从位置 $1$ 开始，你的朋友从位置 $10^{6}$ 开始（这两个位置都没有奖品）。你们必须团队协作，以尽可能短的时间收集所有奖品，奖品的收集顺序任意。

你知道，无论是你还是你的朋友，从位置 $x$ 移动到位置 $x + 1$ 或 $x - 1$ 都恰好需要 $1$ 秒。你们都经过了足够的训练，只要奖品的位置与你当前的位置相同，就可以立即捡起奖品（你的朋友也是如此）。携带奖品完全不会影响你们的速度。

现在，你可以和你的朋友讨论策略，决定谁去捡起每个奖品。请记住，每个奖品都必须被捡起，要么由你捡起，要么由你的朋友捡起。

捡起所有奖品最少需要多少秒？

## 说明/提示
在第一个样例中，你捡起所有的奖品：在位置 $1$ 捡起第一个，在位置 $2$ 捡起第二个，在位置 $8$ 捡起第三个。

在第二个样例中，你用 $1$ 秒捡起第一个奖品，你的朋友用 $5$ 秒捡起另一个奖品，你们同时进行，所以总时间是 $5$ 秒。

## 样例 #1
### 输入
```
3
2 3 9
```
### 输出
```
8
```

## 样例 #2
### 输入
```
2
2 999995
```
### 输出
```
5
```

### 算法分类
模拟

### 综合分析与结论
这些题解的主要思路都是围绕如何模拟你和朋友捡奖品的过程，以求出捡起所有奖品的最短时间。不同题解的具体实现方式有所不同，但核心都是比较每个奖品离你和朋友的距离，让距离近的人去捡。

| 作者 | 思路 | 算法要点 | 解决难点 | 评分 |
| --- | --- | --- | --- | --- |
| Yaixy | 1. 暴力枚举每个奖品，分别计算你和朋友到达该奖品的时间，取最小值，最后取所有最小值中的最大值。2. 根据奖品位置与中点的关系，直接确定是你还是朋友去捡，再取最大值。 | 1. 循环计算时间。2. 利用中点判断谁去捡奖品。 | 确定每个奖品由谁去捡能使总时间最短。 | 4星 |
| Anguei | 开一个数组记录每个坐标是否有奖品，然后从两头遍历数组，直到所有奖品都被捡起。 | 数组标记奖品位置，双指针遍历。 | 处理同时遇到奖品的情况。 | 3星 |
| Moon_Lighter | 求每个奖品距你和朋友的距离，取最小值，然后对所有最小值进行排序，取最大的最小值。 | 计算距离、排序。 | 正确计算每个奖品的最短到达时间。 | 3星 |
| syanoeclipse | 定义函数判断每个奖品由谁捡及所需时间，然后找出所有奖品中所需时间的最大值。 | 函数封装判断逻辑。 | 准确实现判断逻辑。 | 3星 |
| zqwzqwzqw | 把你和朋友看做两个端点，一起相向前进，每遇到一个礼物就捡起来，直至所有礼物都被捡起。 | 双指针模拟前进过程。 | 避免重复计数。 | 3星 |
| Chthology | 计算不同位置组合下你和朋友跑到的最大时间，取最小值。 | 循环计算时间并取最小值。 | 确定合适的位置组合。 | 3星 |
| xgwpp6710 | 贪心策略，看一个奖品离谁近就让谁去捡，找到朋友需要捡的最靠左的奖品，然后计算时间。 | 贪心选择。 | 正确找到朋友要捡的第一个奖品。 | 3星 |
| BMTXLRC | 你和朋友每人分 $5\times10^5$ 的距离，向中间靠近，遇到礼物计数器自增，直到计数器等于总礼物数。 | 双指针模拟靠近过程。 | 确定停止条件。 | 3星 |
| Eason_AC | 将奖品按位置划给你和朋友，分别计算你和朋友取到各自最远距离奖品的时间，取较大值。 | 划分奖品、计算时间。 | 正确划分奖品。 | 3星 |
| houpingze | 用桶标记礼物位置，你和朋友同时前进，捡起路过的礼物，直到所有礼物都被捡起。 | 桶标记、双指针模拟。 | 处理一个位置有多个礼物的情况。 | 3星 |
| TianLuen | 将路径折叠，变成一个人行走，计算折叠后各个礼物的位置，取最大距离减1。 | 路径折叠。 | 理解路径折叠的原理。 | 3星 |
| XMK_萌新 | 找到离中点距离最短的礼物，计算你和朋友到该礼物的最短距离。 | 计算中点距离。 | 准确找到离中点最近的礼物。 | 3星 |
| EAT_NH4HCO3 | 用 multiset 存储礼物位置，你和朋友同时前进，遇到礼物就从 multiset 中删除，直到 multiset 为空。 | multiset 存储和查找。 | 正确处理 multiset 的查找和删除操作。 | 3星 |

### 所选题解
- Yaixy（4星）
  - 关键亮点：提供了两种思路，一种是暴力枚举，另一种是根据奖品位置与中点的关系直接判断，思路清晰，代码实现简洁。

### 重点代码
```cpp
// Yaixy 第二种思路代码
#include<bits/stdc++.h>
using namespace std;
int a[500005],n,x,y,mid,sum,ans;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    x=1;
    y=1000000;
    mid=(x+y)/2;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        if(a[i]<=mid) sum=a[i]-x; // 取你的时间
        if(a[i]>mid) sum=y-a[i]; // 取朋友的时间
        ans=max(sum,ans);
    }
    cout<<ans<<"\n";
    return 0;
}
```
核心实现思想：先计算出中点位置，然后遍历每个奖品的位置，根据奖品位置与中点的关系，确定是你还是朋友去捡该奖品，计算所需时间，最后取所有时间中的最大值。

### 最优关键思路或技巧
- 利用中点判断每个奖品由谁去捡，避免了复杂的计算。
- 双指针模拟你和朋友的移动过程，简单直观。

### 拓展思路
同类型题或类似算法套路：这类模拟题通常可以通过双指针、数组标记等方法来解决。例如，在一些两人相向而行的问题中，可以用双指针模拟他们的移动过程；在一些位置相关的问题中，可以用数组标记位置信息。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

### 个人心得
- xgwpp6710：因为没有及时 break 导致 friendMin 一直更新，WA 了两次，提醒我们在编写代码时要注意逻辑的正确性，避免不必要的错误。

---
处理用时：51.10秒