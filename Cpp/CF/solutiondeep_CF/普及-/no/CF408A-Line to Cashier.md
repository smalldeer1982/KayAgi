# 题目信息

# Line to Cashier

## 题目描述

Little Vasya went to the supermarket to get some groceries. He walked about the supermarket for a long time and got a basket full of products. Now he needs to choose the cashier to pay for the products.

There are $ n $ cashiers at the exit from the supermarket. At the moment the queue for the $ i $ -th cashier already has $ k_{i} $ people. The $ j $ -th person standing in the queue to the $ i $ -th cashier has $ m_{i,j} $ items in the basket. Vasya knows that:

- the cashier needs 5 seconds to scan one item;
- after the cashier scans each item of some customer, he needs 15 seconds to take the customer's money and give him the change.

Of course, Vasya wants to select a queue so that he can leave the supermarket as soon as possible. Help him write a program that displays the minimum number of seconds after which Vasya can get to one of the cashiers.

## 说明/提示

In the second test sample, if Vasya goes to the first queue, he gets to the cashier in $ 100·5+15=515 $ seconds. But if he chooses the second queue, he will need $ 1·5+2·5+2·5+3·5+4·15=100 $ seconds. He will need $ 1·5+9·5+1·5+3·15=100 $ seconds for the third one and $ 7·5+8·5+2·15=105 $ seconds for the fourth one. Thus, Vasya gets to the cashier quicker if he chooses the second or the third queue.

## 样例 #1

### 输入

```
1
1
1
```

### 输出

```
20
```

## 样例 #2

### 输入

```
4
1 4 3 2
100
1 2 2 3
1 9 1
7 8
```

### 输出

```
100
```

# AI分析结果

【题目内容（中文重写）】
# 收银台排队

## 题目描述
小瓦西亚去超市买了些杂货。他在超市里逛了很久，篮子里装满了商品。现在他需要选择一个收银台来付款。

超市出口处有 $n$ 个收银台。此刻，第 $i$ 个收银台的队伍里已经有 $k_{i}$ 个人。排在第 $i$ 个收银台队伍里的第 $j$ 个人的篮子里有 $m_{i,j}$ 件商品。瓦西亚知道：
- 收银员扫描一件商品需要 5 秒钟；
- 收银员扫描完某位顾客的所有商品后，需要 15 秒钟来收取顾客的钱并找零。

当然，瓦西亚希望选择一个队伍，以便能尽快离开超市。请帮助他编写一个程序，显示瓦西亚最快能在多少秒后到达其中一个收银台。

## 说明/提示
在第二个测试样例中，如果瓦西亚去第一个队伍，他需要 $100×5 + 15 = 515$ 秒才能到达收银台。但如果他选择第二个队伍，他将需要 $1×5 + 2×5 + 2×5 + 3×5 + 4×15 = 100$ 秒。去第三个队伍需要 $1×5 + 9×5 + 1×5 + 3×15 = 100$ 秒，去第四个队伍需要 $7×5 + 8×5 + 2×15 = 105$ 秒。因此，如果瓦西亚选择第二个或第三个队伍，他能更快到达收银台。

## 样例 #1
### 输入
```
1
1
1
```
### 输出
```
20
```

## 样例 #2
### 输入
```
4
1 4 3 2
100
1 2 2 3
1 9 1
7 8
```
### 输出
```
100
```

【算法分类】
模拟

【综合分析与结论】
这些题解的核心思路都是模拟计算每个收银台队列的总用时，然后找出其中的最小值。
- **思路**：先读取每个队列的人数，再对每个队列，依次读取每个人的商品数量，计算该队列所有人的总用时，最后比较各队列用时得到最小值。
- **算法要点**：准确计算每个顾客的用时（商品数乘以 5 加上 15），并累加得到队列总用时，再更新最小用时。
- **解决难点**：正确处理输入数据，避免数组越界等问题；初始化最小用时为一个足够大的值，确保能正确更新最小值。

【题解评分】
- RainFestival：4 星。思路清晰，代码简洁易懂，直接实现核心逻辑。
- 小小蒟弱：3 星。使用了快读，有一定优化，但代码相对复杂一些。
- hanyuchen2019：3 星。思路正确，但代码存在拼写错误（`algortihm`、`snyc_with_stdio` 等）。
- Aya_tt：2 星。代码存在错误（`k[i]` 未正确赋值），逻辑有瑕疵。
- HarryKane：3 星。使用了快读快输，代码结构较清晰，但实现相对复杂。
- Firstly：3 星。使用优先队列实现，思路独特，但对于本题来说有些复杂。
- fox_nice：3 星。代码简洁，但变量命名不够规范。

【所选题解】
- RainFestival（4 星）：关键亮点是思路清晰，代码简洁，直接实现了核心逻辑。

【重点代码】
```cpp
#include<cstdio>
int n,f[105],ans=1000000000;
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&f[i]);
    for (int i=1;i<=n;i++)
    {
        int s=0;
        while (f[i]--){int x;scanf("%d",&x);s=s+x*5+15;}
        if (s<ans) ans=s;
    }
    printf("%d\n",ans); 
}
```
**核心实现思想**：先读取每个队列的人数，然后对每个队列，依次读取每个人的商品数量，计算该队列所有人的总用时，更新最小用时，最后输出最小用时。

【可拓展之处】
同类型题可能会改变规则，如增加不同类型商品的扫描时间、增加不同收银员的工作效率差异等。类似算法套路就是按照题目给定的规则进行模拟计算，再根据要求找出最优解。

【推荐题目】
1. P1003 铺地毯
2. P1047 校门外的树
3. P1098 字符串的展开

【个人心得】
无。

---
处理用时：27.05秒