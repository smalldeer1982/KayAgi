# 题目信息

# Minimize Distance

## 题目描述

A total of $ n $ depots are located on a number line. Depot $ i $ lies at the point $ x_i $ for $ 1 \le i \le n $ .

You are a salesman with $ n $ bags of goods, attempting to deliver one bag to each of the $ n $ depots. You and the $ n $ bags are initially at the origin $ 0 $ . You can carry up to $ k $ bags at a time. You must collect the required number of goods from the origin, deliver them to the respective depots, and then return to the origin to collect your next batch of goods.

Calculate the minimum distance you need to cover to deliver all the bags of goods to the depots. You do not have to return to the origin after you have delivered all the bags.

## 说明/提示

In the first test case, you can carry only one bag at a time. Thus, the following is a solution sequence that gives a minimum travel distance: $ 0 \to 2 \to 0 \to 4 \to 0 \to 3 \to 0 \to 1 \to 0 \to 5 $ , where each $ 0 $ means you go the origin and grab one bag, and each positive integer means you deliver the bag to a depot at this coordinate, giving a total distance of $ 25 $ units. It must be noted that there are other sequences that give the same distance.

In the second test case, you can follow the following sequence, among multiple such sequences, to travel minimum distance: $ 0 \to 6 \to 8 \to 7 \to 0 \to 5 \to 4 \to 3 \to 0 \to (-5) \to (-10) \to (-15) $ , with distance $ 41 $ . It can be shown that $ 41 $ is the optimal distance for this test case.

## 样例 #1

### 输入

```
4
5 1
1 2 3 4 5
9 3
-5 -10 -15 6 5 8 3 7 4
5 3
2 2 3 3 3
4 2
1000000000 1000000000 1000000000 1000000000```

### 输出

```
25
41
7
3000000000```

# AI分析结果

【题目内容】
# 最小化距离

## 题目描述

在数轴上有 $n$ 个仓库。第 $i$ 个仓库位于坐标 $x_i$，其中 $1 \le i \le n$。

你是一名销售员，有 $n$ 袋货物，需要将每袋货物送到对应的仓库。你和这些货物最初位于原点 $0$。你一次最多可以携带 $k$ 袋货物。你必须从原点收集所需数量的货物，将它们送到相应的仓库，然后返回原点以获取下一批货物。

计算将所有货物送到仓库所需的最小距离。在送完所有货物后，你不需要返回原点。

## 说明/提示

在第一个测试用例中，你一次只能携带一袋货物。因此，以下是一个最小旅行距离的解决方案序列：$0 \to 2 \to 0 \to 4 \to 0 \to 3 \to 0 \to 1 \to 0 \to 5$，其中每个 $0$ 表示你回到原点取一袋货物，每个正整数表示你将货物送到该坐标的仓库，总距离为 $25$ 单位。需要注意的是，还有其他序列可以得到相同的距离。

在第二个测试用例中，你可以按照以下序列（在多个这样的序列中）以最小距离旅行：$0 \to 6 \to 8 \to 7 \to 0 \to 5 \to 4 \to 3 \to 0 \to (-5) \to (-10) \to (-15)$，距离为 $41$。可以证明 $41$ 是该测试用例的最优距离。

## 样例 #1

### 输入

```
4
5 1
1 2 3 4 5
9 3
-5 -10 -15 6 5 8 3 7 4
5 3
2 2 3 3 3
4 2
1000000000 1000000000 1000000000 1000000000```

### 输出

```
25
41
7
3000000000```

【算法分类】
贪心

【题解分析与结论】
该题的核心思路是通过贪心算法，每次尽可能多地携带货物，减少往返次数，从而最小化总距离。具体来说，将正方向和负方向的仓库分开处理，每次从最远的仓库开始，携带最多 $k$ 袋货物，最后减去最远的一次单程距离，因为最后一次不需要返回原点。

【评分较高的题解】

1. **作者：封禁用户 (4星)**
   - **关键亮点**：清晰地解释了贪心策略的实现，代码简洁且易于理解。通过分别处理正负方向的仓库，并减去最远的一次单程距离，实现了最优解。
   - **核心代码**：
     ```cpp
     for(int i = atmp - 1 ; i >= 0 ; i -= k)
     {
         cnt += a[i] + a[i];
     }
     for(int i = btmp - 1 ; i >= 0 ; i -= k)
     {
         cnt += b[i] + b[i];
     }
     cnt -= max(a[atmp - 1] , b[btmp - 1]);
     ```

2. **作者：xiaozeyu (4星)**
   - **关键亮点**：详细解释了贪心策略的合理性，代码实现简洁且高效。通过从两端分别处理正负方向的仓库，并减去最远的一次单程距离，实现了最优解。
   - **核心代码**：
     ```cpp
     for(int i=n;i>=1&&a[i]>0;i-=k) ans+=a[i];
     for(int i=1;i<=n&&a[i]<0;i+=k) ans-=a[i];
     printf("%lld\n",ans*2-max(abs(a[1]),a[n]));
     ```

3. **作者：dd_d (4星)**
   - **关键亮点**：代码实现清晰，思路明确。通过分别处理正负方向的仓库，并减去最远的一次单程距离，实现了最优解。
   - **核心代码**：
     ```cpp
     for(int i=n1;i>=1;i-=m) ans+=a[i]*2;
     for(int i=n2;i>=1;i-=m) ans+=b[i]*2;
     if(n1&&n2) ans-=max(a[n1],b[n2]);
     else if(n1) ans-=a[n1];
     else if(n2) ans-=b[n2];
     ```

【最优关键思路或技巧】
- **贪心策略**：每次从最远的仓库开始，携带最多 $k$ 袋货物，减少往返次数。
- **正负方向分开处理**：将正方向和负方向的仓库分开处理，简化问题。
- **减去最远单程距离**：最后一次不需要返回原点，因此减去最远的一次单程距离。

【可拓展之处】
- 类似的问题可以扩展到二维平面或更高维空间，处理多个方向的最短路径问题。
- 可以扩展到每个仓库需要多个货物的情况，进一步优化携带策略。

【推荐题目】
1. P1044 仓库选址
2. P1056 货车运输
3. P1060 最短路径问题

---
处理用时：37.01秒