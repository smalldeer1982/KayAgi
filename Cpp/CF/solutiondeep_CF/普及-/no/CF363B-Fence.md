# 题目信息

# Fence

## 题目描述

There is a fence in front of Polycarpus's home. The fence consists of $ n $ planks of the same width which go one after another from left to right. The height of the $ i $ -th plank is $ h_{i} $ meters, distinct planks can have distinct heights.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF363B/89891f9a8aa0dbd268db12cc4f373a8fc8629b6b.png)Fence for $ n=7 $ and $ h=[1,2,6,1,1,7,1] $ Polycarpus has bought a posh piano and is thinking about how to get it into the house. In order to carry out his plan, he needs to take exactly $ k $ consecutive planks from the fence. Higher planks are harder to tear off the fence, so Polycarpus wants to find such $ k $ consecutive planks that the sum of their heights is minimal possible.

Write the program that finds the indexes of $ k $ consecutive planks with minimal total height. Pay attention, the fence is not around Polycarpus's home, it is in front of home (in other words, the fence isn't cyclic).

## 说明/提示

In the sample, your task is to find three consecutive planks with the minimum sum of heights. In the given case three planks with indexes 3, 4 and 5 have the required attribute, their total height is 8.

## 样例 #1

### 输入

```
7 3
1 2 6 1 1 7 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# Fence

## 题目描述
在Polycarpus家前面有一道栅栏。栅栏由 $n$ 块宽度相同的木板组成，这些木板从左到右依次排列。第 $i$ 块木板的高度为 $h_{i}$ 米，不同的木板可能有不同的高度。

![栅栏示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF363B/89891f9a8aa0dbd268db12cc4f373a8fc8629b6b.png)（图为 $n = 7$ 且 $h = [1, 2, 6, 1, 1, 7, 1]$ 时的栅栏）

Polycarpus买了一架豪华钢琴，正在思考如何把它搬进屋里。为了实施他的计划，他需要从栅栏上恰好取下 $k$ 块连续的木板。较高的木板更难从栅栏上拆下来，所以Polycarpus想找到这样 $k$ 块连续的木板，使得它们高度的总和尽可能小。

编写一个程序，找到总高度最小的 $k$ 块连续木板的索引。注意，栅栏不是环绕在Polycarpus家周围，而是在他家前面（换句话说，栅栏不是循环的）。

## 说明/提示
在示例中，你的任务是找到三块连续木板，其高度总和最小。在给定的例子中，索引为3、4和5的三块木板具有所需的属性，它们的总高度为8。

## 样例 #1
### 输入
```
7 3
1 2 6 1 1 7 1
```
### 输出
```
3
```

### 算法分类
前缀和

### 综合分析与结论
所有题解都围绕寻找长度为 $k$ 的连续木板最小高度和这一核心问题，多数题解采用前缀和优化暴力枚举的方法。不同之处在于部分题解使用直接计算相邻区间和的递推方式，部分使用前缀和数组计算区间和。核心难点在于如何优化暴力枚举的时间复杂度，前缀和的使用将查询区间和的时间复杂度从 $O(k)$ 降为 $O(1)$，从而满足数据范围要求。

### 所选的题解
 - **作者：L_zaa_L（5星）**
    - **关键亮点**：思路清晰，直接点明暴力不可行，并通过分析相邻区间和的变化规律，采用递推方式计算区间和，无需额外数组记录前缀和，空间复杂度较低。
    - **重点代码**：
```cpp
int a[1500005],minn=INT_MAX,x;
int main(){
    int n,m;
    cin>>n>>m;
    int h = 1, t = m, qjh = 0;
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= m; i++) qjh += a[i];
    while(t <= n){
        if(qjh < minn){
            minn = qjh;
            x = h;
        }
        qjh -= a[h];
        t++;
        h++;
        qjh += a[t];
    }
    cout<<x;
    return 0;
} 
```
    - **核心实现思想**：初始化区间和 `qjh` 及区间头尾指针 `h` 和 `t`，通过循环移动区间，每次更新区间和并与最小值比较，记录最小和的起始位置。
 - **作者：_JF_（4星）**
    - **关键亮点**：思路清晰，结合前缀和数组的介绍，详细阐述利用前缀和数组计算区间和的方法，代码简洁明了。
    - **重点代码**：
```cpp
int a[1500005],sum[1500005];
signed main()
{
    int x;
    int minn = INT_MAX;
    int n,m;
    cin>>n>>m;
    for(int i = 1; i <= n; i++)
        cin>>a[i],sum[i] = sum[i - 1] + a[i];
    for(int i = m; i <= n; i++)
    {
        if(sum[i] - sum[i - m] < minn)
            minn = sum[i] - sum[i - m],x = i - m + 1;
    }
    cout<<x<<endl;
}
```
    - **核心实现思想**：先预处理前缀和数组 `sum`，通过枚举区间右端点 `i`，利用前缀和公式 `sum[i] - sum[i - m]` 计算长度为 `m` 的区间和，并与最小值比较更新。
 - **作者：正负君（4星）**
    - **关键亮点**：不仅介绍前缀和思想，还提及C++标准库中的 `std::partial_sum` 函数，同时代码实现简洁，对细节处理有说明，如数组初始化。
    - **重点代码**：
```cpp
int n,k,ans;
int main()
{
    cin>>n>>k;
    int min = 2147483647;
    int h[n + 1];
    h[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        cin>>h[i];
        h[i] += h[i - 1];
    }
    for(int i = k; i <= n; i++)
    {
        if(h[i] - h[i - k] < min)
        {
            min = h[i] - h[i - k];
            ans = i - k + 1;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
    - **核心实现思想**：将输入数组 `h` 同时作为前缀和数组使用，通过循环计算前缀和，再枚举区间右端点，利用前缀和计算区间和并更新最小值及起始位置。

### 最优关键思路或技巧
利用前缀和优化暴力枚举。通过预处理前缀和数组，使得查询固定长度区间和的时间复杂度降为 $O(1)$，从而高效解决问题。部分题解还利用相邻区间和的关系，通过递推方式避免使用额外数组记录前缀和，进一步优化空间复杂度。

### 可拓展思路
此类题目属于固定长度区间和问题，类似套路可应用于求固定长度子数组的最大/最小和、平均数等问题。例如，在一些滑动窗口类型的题目中，也可使用前缀和或类似的递推方式优化计算。

### 洛谷相似题目推荐
 - [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)：通过前缀和优化，求满足条件的最大正方形面积。
 - [P3397 地毯](https://www.luogu.com.cn/problem/P3397)：利用二维前缀和解决矩形区域的查询问题。
 - [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：与本题类似，求最大子段和，可通过前缀和思想辅助解决。

### 个人心得摘录与总结
无明显个人心得相关内容。 

---
处理用时：59.89秒