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

### 题目内容重写

#### 最小化距离

#### 题目描述

在数轴上有 $n$ 个仓库，第 $i$ 个仓库位于坐标 $x_i$，其中 $1 \le i \le n$。

你是一名销售员，有 $n$ 袋货物需要分别送到这 $n$ 个仓库。你和这 $n$ 袋货物最初位于原点 $0$。你一次最多可以携带 $k$ 袋货物。你必须从原点收集所需的货物，将它们送到相应的仓库，然后返回原点以收集下一批货物。

计算你需要覆盖的最小距离，以将所有货物送到仓库。在送完所有货物后，你不需要返回原点。

#### 说明/提示

在第一个测试用例中，你一次只能携带一袋货物。因此，以下是一个最小化旅行距离的解决方案序列：$0 \to 2 \to 0 \to 4 \to 0 \to 3 \to 0 \to 1 \to 0 \to 5$，其中每个 $0$ 表示你回到原点并取一袋货物，每个正整数表示你将货物送到该坐标的仓库，总距离为 $25$ 单位。需要注意的是，还有其他序列可以得到相同的距离。

在第二个测试用例中，你可以遵循以下序列（在多个这样的序列中）以最小化旅行距离：$0 \to 6 \to 8 \to 7 \to 0 \to 5 \to 4 \to 3 \to 0 \to (-5) \to (-10) \to (-15)$，距离为 $41$。可以证明 $41$ 是该测试用例的最优距离。

#### 样例 #1

##### 输入

```
4
5 1
1 2 3 4 5
9 3
-5 -10 -15 6 5 8 3 7 4
5 3
2 2 3 3 3
4 2
1000000000 1000000000 1000000000 1000000000
```

##### 输出

```
25
41
7
3000000000
```

### 算法分类

贪心

### 题解分析与结论

所有题解都采用了贪心算法，核心思路是将数轴上的仓库分为正负两部分，分别处理。每次尽可能多地携带货物（最多 $k$ 袋），以减少往返次数。最终不需要返回原点，因此可以减去最远的一次单程距离。

### 所选高星题解

#### 题解1：xiaozeyu (5星)

**关键亮点**：
- 详细解释了贪心策略，特别是如何处理正负两端的货物。
- 代码简洁明了，逻辑清晰。
- 强调了最后不需要返回原点的情况，并给出了相应的优化。

**代码核心实现**：
```cpp
for(int i=n;i>=1&&a[i]>0;i-=k) ans+=a[i];
for(int i=1;i<=n&&a[i]<0;i+=k) ans-=a[i];
printf("%lld\n",ans*2-max(abs(a[1]),a[n]));
```

#### 题解2：Hutao__ (4星)

**关键亮点**：
- 思路清晰，代码简洁。
- 强调了每次携带货物时尽量拿满 $k$ 个，以减少往返次数。
- 最后减去最远的一次单程距离，优化了总距离。

**代码核心实现**：
```cpp
for(int i=1;i<=n;i+=k){
    if(a[i]>0)break;
    sum+=2*abs(a[i]);
}
for(int i=n;i>=1;i-=k){
    if(a[i]<0)break;
    sum+=2*abs(a[i]);
}
cout<<sum-max(abs(a[1]),abs(a[n]))<<'\n';
```

#### 题解3：ghx0052 (4星)

**关键亮点**：
- 详细描述了贪心策略，特别是如何处理正负两端的货物。
- 代码简洁，逻辑清晰。
- 强调了最后不需要返回原点的情况，并给出了相应的优化。

**代码核心实现**：
```cpp
for (int i = 1; i <= n && a[i] < 0; i += k) ans += abs(2 * a[i]);
for (int i = n; i >= 1 && a[i] >= 0; i -= k) ans += abs(2 * a[i]);
cout << ans - max(abs(a[1]), abs(a[n])) << endl;
```

### 最优关键思路或技巧

1. **贪心策略**：将数轴上的仓库分为正负两部分，分别处理，每次尽可能多地携带货物。
2. **优化往返次数**：通过每次携带 $k$ 袋货物，减少往返次数。
3. **最后不返回原点**：在计算总距离时，减去最远的一次单程距离，以优化总距离。

### 可拓展之处

类似的问题可以出现在其他需要优化路径或资源分配的题目中，例如：
- 快递员送货问题，每次携带一定数量的包裹，优化送货路径。
- 资源调度问题，如何最优地分配资源以减少总成本。

### 推荐题目

1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录

- **xiaozeyu**：强调了贪心策略的合理性，特别是在处理正负两端的货物时，如何避免不必要的往返。
- **Hutao__**：提到了代码的简洁性和逻辑的清晰性，强调了每次携带货物时尽量拿满 $k$ 个的重要性。
- **ghx0052**：详细描述了贪心策略，并强调了最后不需要返回原点的优化。

---
处理用时：40.44秒