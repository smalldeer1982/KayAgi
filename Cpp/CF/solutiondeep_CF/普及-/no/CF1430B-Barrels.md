# 题目信息

# Barrels

## 题目描述

You have $ n $ barrels lined up in a row, numbered from left to right from one. Initially, the $ i $ -th barrel contains $ a_i $ liters of water.

You can pour water from one barrel to another. In one act of pouring, you can choose two different barrels $ x $ and $ y $ (the $ x $ -th barrel shouldn't be empty) and pour any possible amount of water from barrel $ x $ to barrel $ y $ (possibly, all water). You may assume that barrels have infinite capacity, so you can pour any amount of water in each of them.

Calculate the maximum possible difference between the maximum and the minimum amount of water in the barrels, if you can pour water at most $ k $ times.

Some examples:

- if you have four barrels, each containing $ 5 $ liters of water, and $ k = 1 $ , you may pour $ 5 $ liters from the second barrel into the fourth, so the amounts of water in the barrels are $ [5, 0, 5, 10] $ , and the difference between the maximum and the minimum is $ 10 $ ;
- if all barrels are empty, you can't make any operation, so the difference between the maximum and the minimum amount is still $ 0 $ .

## 样例 #1

### 输入

```
2
4 1
5 5 5 5
3 2
0 0 0```

### 输出

```
10
0```

# AI分析结果

### 题目内容
# 桶

## 题目描述
你有 $n$ 个桶排成一排，从左到右依次编号为1。最初，第 $i$ 个桶中装有 $a_i$ 升水。

你可以将水从一个桶倒入另一个桶。在一次倒水操作中，你可以选择两个不同的桶 $x$ 和 $y$（第 $x$ 个桶不能为空），并将任意可能量的水从桶 $x$ 倒入桶 $y$（可能是全部的水）。假设桶的容量是无限的，所以你可以在每个桶中倒入任意量的水。

计算如果你最多可以倒水 $k$ 次，桶中最大水量与最小水量之间的最大可能差值。

一些示例：
- 如果你有四个桶，每个桶装有5升水，并且 $k = 1$，你可以将第二个桶中的5升水倒入第四个桶，所以桶中的水量为 $[5, 0, 5, 10]$，最大水量与最小水量的差值为10；
- 如果所有桶都是空的，你无法进行任何操作，所以最大水量与最小水量的差值仍然为0。

## 样例 #1
### 输入
```
2
4 1
5 5 5 5
3 2
0 0 0
```
### 输出
```
10
0
```

• **算法分类**：贪心
• **综合分析与结论**：这些题解的核心思路都是基于贪心策略。大家都意识到通过一次操作就能使某个桶的水量变为0，从而让最小值为0 。为使差值最大，需让最大值尽可能大，方法是将前 $k + 1$ 大的数汇聚起来，这个和就是所求的最大差值。各题解在代码实现上略有不同，比如排序方式、求和方式等，但整体思路一致。
• **所选的题解**：
  - **作者：vectorwyx (5星)**
    - **关键亮点**：思路清晰，代码结构完整，详细地给出了读入优化函数，且对数组进行从大到小排序后直接求和，逻辑连贯。
    - **重点代码**：
```cpp
bool cmp(int x,int y){
    return x>y;
}
void work(){
    int n=read(),k=read();
    ll ans=0;
    fo(i,1,n) a[i]=read();
    sort(a+1,a+1+n,cmp);
    fo(i,1,k+1) ans+=a[i];
    printf("%lld\n",ans); 
}
```
    - **核心实现思想**：定义比较函数 `cmp` 用于从大到小排序，`work` 函数中读入数据，排序后对前 `k + 1` 个数求和并输出。
  - **作者：Jay142753869 (4星)**
    - **关键亮点**：代码简洁明了，直接使用 `sort` 从小到大排序后从后往前求和，符合逻辑且代码量少。
    - **重点代码**：
```cpp
signed main(){
    t=read();
    while(t--){
        n=read(),k=read();
        for(int i=1;i<=n;i++)
            a[i]=read();
        sort(a+1,a+n+1);
        for(int i=n;i>=n-k;i--)
            anss+=a[i];
        printf("%lld\n",anss);
        anss=0;
    }
    return 0;
}
```
    - **核心实现思想**：在主函数中读入数据，排序后通过循环对后 `k + 1` 个数求和并输出结果。
  - **作者：Konnyaku_LXZ (4星)**
    - **关键亮点**：代码结构清晰，将输入、求解、输出分别封装在不同函数中，可读性强。
    - **重点代码**：
```cpp
void Init(){
    scanf("%lld%lld",&N,&K);
    for(int i=1;i<=N;++i) scanf("%lld",&a[i]);
}
void Solve(){
    Ans=0;
    sort(a+1,a+1+N,cmp);
    for(int i=1;i<=K+1;++i) Ans+=a[i];
}
void Print(){
    printf("%lld\n",Ans);
}
```
    - **核心实现思想**：`Init` 函数负责读入数据，`Solve` 函数排序后对前 `K + 1` 个数求和，`Print` 函数负责输出结果。
• **最优关键思路或技巧**：利用贪心思想，明确使差值最大就是让最小值为0且最大值最大，通过排序汇聚较大值。
• **可拓展之处**：类似的贪心题目通常围绕资源分配、最值求解等场景，解题时需抓住关键因素，明确如何通过有限操作使目标最优。
• **洛谷相似题目**：
  - P1090 [合并果子](https://www.luogu.com.cn/problem/P1090)
  - P1199 [三国游戏](https://www.luogu.com.cn/problem/P1199)
  - P1080 [国王游戏](https://www.luogu.com.cn/problem/P1080) 
• **个人心得**：无 

---
处理用时：43.30秒