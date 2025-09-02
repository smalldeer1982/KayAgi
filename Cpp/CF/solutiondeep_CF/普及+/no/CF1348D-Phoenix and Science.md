# 题目信息

# Phoenix and Science

## 题目描述

Phoenix has decided to become a scientist! He is currently investigating the growth of bacteria.

Initially, on day $ 1 $ , there is one bacterium with mass $ 1 $ .

Every day, some number of bacteria will split (possibly zero or all). When a bacterium of mass $ m $ splits, it becomes two bacteria of mass $ \frac{m}{2} $ each. For example, a bacterium of mass $ 3 $ can split into two bacteria of mass $ 1.5 $ .

Also, every night, the mass of every bacteria will increase by one.

Phoenix is wondering if it is possible for the total mass of all the bacteria to be exactly $ n $ . If it is possible, he is interested in the way to obtain that mass using the minimum possible number of nights. Help him become the best scientist!

## 说明/提示

In the first test case, the following process results in bacteria with total mass $ 9 $ :

- Day $ 1 $ : The bacterium with mass $ 1 $ splits. There are now two bacteria with mass $ 0.5 $ each.
- Night $ 1 $ : All bacteria's mass increases by one. There are now two bacteria with mass $ 1.5 $ .
- Day $ 2 $ : None split.
- Night $ 2 $ : There are now two bacteria with mass $ 2.5 $ .
- Day $ 3 $ : Both bacteria split. There are now four bacteria with mass $ 1.25 $ .
- Night $ 3 $ : There are now four bacteria with mass $ 2.25 $ .

 The total mass is $ 2.25+2.25+2.25+2.25=9 $ . It can be proved that $ 3 $ is the minimum number of nights needed. There are also other ways to obtain total mass 9 in 3 nights.  $   $

In the second test case, the following process results in bacteria with total mass $ 11 $ :

- Day $ 1 $ : The bacterium with mass $ 1 $ splits. There are now two bacteria with mass $ 0.5 $ .
- Night $ 1 $ : There are now two bacteria with mass $ 1.5 $ .
- Day $ 2 $ : One bacterium splits. There are now three bacteria with masses $ 0.75 $ , $ 0.75 $ , and $ 1.5 $ .
- Night $ 2 $ : There are now three bacteria with masses $ 1.75 $ , $ 1.75 $ , and $ 2.5 $ .
- Day $ 3 $ : The bacteria with mass $ 1.75 $ and the bacteria with mass $ 2.5 $ split. There are now five bacteria with masses $ 0.875 $ , $ 0.875 $ , $ 1.25 $ , $ 1.25 $ , and $ 1.75 $ .
- Night $ 3 $ : There are now five bacteria with masses $ 1.875 $ , $ 1.875 $ , $ 2.25 $ , $ 2.25 $ , and $ 2.75 $ .

 The total mass is $ 1.875+1.875+2.25+2.25+2.75=11 $ . It can be proved that $ 3 $ is the minimum number of nights needed. There are also other ways to obtain total mass 11 in 3 nights.  $   $

In the third test case, the bacterium does not split on day $ 1 $ , and then grows to mass $ 2 $ during night $ 1 $ .

## 样例 #1

### 输入

```
3
9
11
2```

### 输出

```
3
1 0 2 
3
1 1 2
1
0```

# AI分析结果

### 题目内容中文重写
# 菲尼克斯与科学

## 题目描述
菲尼克斯决定成为一名科学家！他目前正在研究细菌的生长情况。

最初，在第 1 天，有一个质量为 1 的细菌。

每天，会有一些细菌分裂（可能为零个或全部）。当一个质量为 $m$ 的细菌分裂时，它会变成两个质量均为 $\frac{m}{2}$ 的细菌。例如，一个质量为 3 的细菌可以分裂成两个质量为 1.5 的细菌。

此外，每天晚上，每个细菌的质量都会增加 1。

菲尼克斯想知道所有细菌的总质量是否有可能恰好为 $n$。如果可能，他想知道使用最少的夜晚数来达到该质量的方法。帮助他成为最优秀的科学家！

## 说明/提示
在第一个测试用例中，以下过程会使细菌的总质量达到 9：
- 第 1 天：质量为 1 的细菌分裂。现在有两个质量均为 0.5 的细菌。
- 第 1 晚：所有细菌的质量增加 1。现在有两个质量为 1.5 的细菌。
- 第 2 天：没有细菌分裂。
- 第 2 晚：现在有两个质量为 2.5 的细菌。
- 第 3 天：两个细菌都分裂。现在有四个质量为 1.25 的细菌。
- 第 3 晚：现在有四个质量为 2.25 的细菌。

总质量为 $2.25 + 2.25 + 2.25 + 2.25 = 9$。可以证明，3 是所需的最少夜晚数。也有其他方法可以在 3 个夜晚内使总质量达到 9。

在第二个测试用例中，以下过程会使细菌的总质量达到 11：
- 第 1 天：质量为 1 的细菌分裂。现在有两个质量为 0.5 的细菌。
- 第 1 晚：现在有两个质量为 1.5 的细菌。
- 第 2 天：一个细菌分裂。现在有三个细菌，质量分别为 0.75、0.75 和 1.5。
- 第 2 晚：现在有三个细菌，质量分别为 1.75、1.75 和 2.5。
- 第 3 天：质量为 1.75 的细菌和质量为 2.5 的细菌分裂。现在有五个细菌，质量分别为 0.875、0.875、1.25、1.25 和 1.75。
- 第 3 晚：现在有五个细菌，质量分别为 1.875、1.875、2.25、2.25 和 2.75。

总质量为 $1.875 + 1.875 + 2.25 + 2.25 + 2.75 = 11$。可以证明，3 是所需的最少夜晚数。也有其他方法可以在 3 个夜晚内使总质量达到 11。

在第三个测试用例中，细菌在第 1 天不分裂，然后在第 1 晚生长到质量为 2。

## 样例 #1
### 输入
```
3
9
11
2
```
### 输出
```
3
1 0 2 
3
1 1 2
1
0
```

### 算法分类
贪心

### 综合分析与结论
这些题解都围绕贪心算法来解决问题。核心思路是利用细菌分裂和生长的规律，尽可能让每次操作增加的质量最大，从而用最少的天数达到目标质量。

不同题解的差异在于对问题的转化和实现细节。有的题解直接模拟细菌的分裂和生长过程，有的则通过数学推导得出规律，还有的使用二分查找来优化查找过程。

### 所选的题解
- **dp_everyday（4星）**
    - **关键亮点**：思路清晰，将题目转化为对数字的操作问题，代码简洁易懂。
    - **重点代码**：
```cpp
void solve() {
    int n;
    scanf("%d", &n);
    vector<int> v;
    int x = 1;
    while(n > 0) {
        if(n > x) v.push_back(x);
        else v.push_back(n);
        n -= x;
        x <<= 1;
    }
    sort(v.begin(), v.end());
    printf("%d\n", v.size() - 1);
    for(int i = 1; i < v.size(); i++) {
        printf("%d ", v[i] - v[i - 1]);
    }
    puts("");
}
```
**核心实现思想**：通过不断将当前的 $x$ 加入到结果数组中，直到 $n$ 变为 0，最后对结果数组排序并输出相邻元素的差值。

### 最优关键思路或技巧
- **贪心策略**：每次尽可能让细菌分裂，以增加总质量，从而减少达到目标质量所需的天数。
- **数学规律**：发现第 $i$ 天最多能增加 $2^{i - 1}$ 个细菌，利用这个规律来构造答案。

### 可拓展之处
同类型题可能会改变细菌的分裂规则或生长规则，或者增加其他限制条件。类似的算法套路包括在资源分配问题中，每次都选择最优的分配方案，以达到整体最优的结果。

### 推荐洛谷题目
- P1223 排队接水（贪心算法）
- P1090 合并果子（贪心算法）
- P2240 部分背包问题（贪心算法）

### 个人心得
无

---
处理用时：33.35秒