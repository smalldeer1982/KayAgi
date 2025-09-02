# 题目信息

# 250 Thousand Tons of TNT

## 题目描述

Alex is participating in the filming of another video of BrMeast, and BrMeast asked Alex to prepare 250 thousand tons of TNT, but Alex didn't hear him well, so he prepared $ n $ boxes and arranged them in a row waiting for trucks. The $ i $ -th box from the left weighs $ a_i $ tons.

All trucks that Alex is going to use hold the same number of boxes, denoted by $ k $ . Loading happens the following way:

- The first $ k $ boxes goes to the first truck,
- The second $ k $ boxes goes to the second truck,
- $ \dotsb $
- The last $ k $ boxes goes to the $ \frac{n}{k} $ -th truck.

Upon loading is completed, each truck must have exactly $ k $ boxes. In other words, if at some point it is not possible to load exactly $ k $ boxes into the truck, then the loading option with that $ k $ is not possible.

Alex hates justice, so he wants the maximum absolute difference between the total weights of two trucks to be as great as possible. If there is only one truck, this value is $ 0 $ .

Alex has quite a lot of connections, so for every $ 1 \leq k \leq n $ , he can find a company such that each of its trucks can hold exactly $ k $ boxes. Print the maximum absolute difference between the total weights of any two trucks.

## 说明/提示

In the first case, we should pick two trucks, so the first one will have only the first box, and the second one will have only the second box.

In the second case, we should pick six trucks, so the maximum will be $ 10 $ , the minimum will be $ 1 $ , and the answer is $ 10 - 1 = 9 $ .

In the third case, for any possible $ k $ , the trucks will have the same total weight of boxes, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
2
1 2
6
10 2 3 6 1 3
4
1000000000 1000000000 1000000000 1000000000
15
60978 82265 78961 56708 39846 31071 4913 4769 29092 91348 64119 72421 98405 222 14294
8
19957 69913 37531 96991 57838 21008 14207 19198```

### 输出

```
1
9
0
189114
112141```

# AI分析结果

### 题目内容（中文重写）
# 25 万吨 TNT

## 题目描述
Alex 正在参与 BrMeast 的另一个视频拍摄，BrMeast 要求 Alex 准备 25 万吨 TNT，但 Alex 没听清楚，于是他准备了 $n$ 个箱子，并将它们排成一排，等待卡车来运输。从左边数第 $i$ 个箱子重 $a_i$ 吨。

Alex 打算使用的所有卡车的载货量相同，用 $k$ 表示每辆卡车能装载的箱子数。装载过程如下：
- 前 $k$ 个箱子装到第一辆卡车上；
- 接下来的 $k$ 个箱子装到第二辆卡车上；
- ……
- 最后 $k$ 个箱子装到第 $\frac{n}{k}$ 辆卡车上。

装载完成后，每辆卡车必须正好装载 $k$ 个箱子。换句话说，如果在某个时刻无法正好将 $k$ 个箱子装入卡车，那么使用该 $k$ 值的装载方案就不可行。

Alex 讨厌公平，所以他希望任意两辆卡车总重量的最大绝对差值尽可能大。如果只有一辆卡车，这个值为 0。

Alex 人脉很广，对于每一个 $1 \leq k \leq n$，他都能找到一家公司，其每辆卡车恰好能装载 $k$ 个箱子。请输出任意两辆卡车总重量的最大绝对差值。

## 说明/提示
在第一个样例中，我们应该选择两辆卡车，这样第一辆卡车只装第一个箱子，第二辆卡车只装第二个箱子。

在第二个样例中，我们应该选择六辆卡车，这样最大重量为 10，最小重量为 1，答案是 $10 - 1 = 9$。

在第三个样例中，对于任何可能的 $k$，卡车装载箱子的总重量都相同，所以答案是 0。

## 样例 #1
### 输入
```
5
2
1 2
6
10 2 3 6 1 3
4
1000000000 1000000000 1000000000 1000000000
15
60978 82265 78961 56708 39846 31071 4913 4769 29092 91348 64119 72421 98405 222 14294
8
19957 69913 37531 96991 57838 21008 14207 19198
```

### 输出
```
1
9
0
189114
112141
```

### 算法分类
枚举、前缀和

### 综合分析与结论
这些题解的核心思路都是枚举 $n$ 的因数 $k$，对于每个 $k$ 计算分组后每组重量的最大值和最小值的差值，最后取所有差值中的最大值作为答案。为了优化计算每组重量的过程，题解们都使用了前缀和的技巧。

不同题解的主要差异在于枚举因数的方式和代码实现细节。部分题解通过枚举到 $\sqrt{n}$ 来优化因数的枚举过程，减少了不必要的计算。

### 所选题解
- **wmrqwq（4星）**
    - **关键亮点**：思路清晰，详细说明了暴力枚举的复杂度问题，并给出了优化方法，通过枚举到 $\sqrt{n}$ 来减少因数的枚举次数。代码结构清晰，注释较少但不影响理解。
    - **重点代码**：
```cpp
for(int i=1;i*i<=n;i++)
{
    if(n%i==0)
    {
        long long maxn=-1e18,minn=1e18;
        for(int j=i;j<=n;j+=i)
        {
            maxn=max(maxn,sum[j]-sum[j-i]);
            minn=min(minn,sum[j]-sum[j-i]);
        }
        ans=max(ans,maxn-minn);
        maxn=-1e18,minn=1e18;
        for(int j=n/i;j<=n;j+=n/i)
        {
            maxn=max(maxn,sum[j]-sum[j-n/i]);
            minn=min(minn,sum[j]-sum[j-n/i]);
        }
        ans=max(ans,maxn-minn);
    }
}
```
    - **核心实现思想**：先枚举 $n$ 的因数 $i$（只枚举到 $\sqrt{n}$），对于每个因数 $i$，计算按 $i$ 个一组分组时每组的最大和最小重量，更新答案。同时，对于 $n/i$ 也进行同样的计算，避免遗漏。

- **lailai0916（4星）**
    - **关键亮点**：思路简洁明了，直接指出 $n$ 的因子就是所有可能的 $k$，并使用前缀和计算每组重量。代码可读性高，有一定的注释。
    - **重点代码**：
```cpp
ll f(int n,int k)
{
    ll mx=-inf,mn=inf;
    for(int i=0;i<n/k;i++)
    {
        ll val=a[k*(i+1)]-a[k*i];
        mx=max(mx,val);
        mn=min(mn,val);
    }
    return mx-mn;
}
for(int i=1;i<=n;i++)
{
    if(n%i==0)
    {
        ans=max(ans,f(n,i));
    }
}
```
    - **核心实现思想**：定义函数 `f` 用于计算按 $k$ 个一组分组时的最大和最小重量的差值。然后枚举 $n$ 的所有因数 $i$，调用 `f` 函数计算差值并更新答案。

- **zhangshuhang2011（4星）**
    - **关键亮点**：思路清晰，强调了要开 `long long` 以避免溢出问题。代码实现简洁，通过枚举到 $\sqrt{n}$ 优化因数的枚举。
    - **重点代码**：
```cpp
for(int i = 1; i*i <= n; i++){
    if(n % i == 0){
        int maxx = 0;
        int minx = 1e18;
        for(int j = 1; j <= n; j += i){
            int x = sa[j+i-1] - sa[j-1];
            minx = min(minx, x);
            maxx = max(maxx, x);
        }
        maxd = max(maxd, maxx - minx);
        if(i * i < n){
            maxx = 0;
            minx = 1e18;
            for(int j = 1; j <= n; j += n/i){
                int x = sa[j+n/i-1] - sa[j-1];
                minx = min(minx, x);
                maxx = max(maxx, x);
            }
            maxd = max(maxd, maxx - minx);
        }
    }
}
```
    - **核心实现思想**：枚举 $n$ 的因数 $i$（只枚举到 $\sqrt{n}$），对于每个因数 $i$，计算按 $i$ 个一组分组时每组的最大和最小重量，更新答案。同时，对于 $n/i$ 也进行同样的计算，避免遗漏。

### 最优关键思路或技巧
- **枚举优化**：只枚举到 $\sqrt{n}$ 来找出 $n$ 的所有因数，减少不必要的计算。
- **前缀和优化**：使用前缀和数组可以在 $O(1)$ 时间内计算出连续区间的和，从而优化计算每组重量的过程。

### 拓展思路
同类型题目通常会涉及到对数据的分组和统计，并且可能会有一些限制条件。解题的关键在于合理枚举可能的分组情况，并使用合适的数据结构（如前缀和）来优化计算过程。例如，可能会要求计算分组后的平均值、中位数等统计量，或者在分组的基础上进行其他操作。

### 推荐题目
- [P1168 中位数](https://www.luogu.com.cn/problem/P1168)：涉及到数据的统计和处理，与本题的分组统计有一定的相似性。
- [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)：需要对连续区间进行求和和比较，可使用前缀和优化。
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)：同样需要对区间进行求和和计算，与本题的思路有一定的关联。

### 个人心得摘录与总结
部分题解提到了“不开 long long 见祖宗”“多测不清空，亲人两行泪”等，总结起来就是在处理数据范围较大的题目时，要注意数据类型的选择，避免溢出问题；在有多组测试数据的题目中，要注意清空相关变量，避免数据干扰。 

---
处理用时：50.74秒