# 题目信息

# Manhattan Subarrays

## 题目描述

Suppose you have two points $ p = (x_p, y_p) $ and $ q = (x_q, y_q) $ . Let's denote the Manhattan distance between them as $ d(p, q) = |x_p - x_q| + |y_p - y_q| $ .

Let's say that three points $ p $ , $ q $ , $ r $ form a bad triple if $ d(p, r) = d(p, q) + d(q, r) $ .

Let's say that an array $ b_1, b_2, \dots, b_m $ is good if it is impossible to choose three distinct indices $ i $ , $ j $ , $ k $ such that the points $ (b_i, i) $ , $ (b_j, j) $ and $ (b_k, k) $ form a bad triple.

You are given an array $ a_1, a_2, \dots, a_n $ . Calculate the number of good subarrays of $ a $ . A subarray of the array $ a $ is the array $ a_l, a_{l + 1}, \dots, a_r $ for some $ 1 \le l \le r \le n $ .

Note that, according to the definition, subarrays of length $ 1 $ and $ 2 $ are good.

## 说明/提示

In the first test case, it can be proven that any subarray of $ a $ is good. For example, subarray $ [a_2, a_3, a_4] $ is good since it contains only three elements and:

- $ d((a_2, 2), (a_4, 4)) = |4 - 3| + |2 - 4| = 3 $ $ < $ $ d((a_2, 2), (a_3, 3)) + d((a_3, 3), (a_4, 4)) = 3 + 1 + 2 + 1 = 7 $ ;
- $ d((a_2, 2), (a_3, 3)) $ $ < $ $ d((a_2, 2), (a_4, 4)) + d((a_4, 4), (a_3, 3)) $ ;
- $ d((a_3, 3), (a_4, 4)) $ $ < $ $ d((a_3, 3), (a_2, 2)) + d((a_2, 2), (a_4, 4)) $ ;

In the second test case, for example, subarray $ [a_1, a_2, a_3, a_4] $ is not good, since it contains a bad triple $ (a_1, 1) $ , $ (a_2, 2) $ , $ (a_4, 4) $ :

- $ d((a_1, 1), (a_4, 4)) = |6 - 9| + |1 - 4| = 6 $ ;
- $ d((a_1, 1), (a_2, 2)) = |6 - 9| + |1 - 2| = 4 $ ;
- $ d((a_2, 2), (a_4, 4)) = |9 - 9| + |2 - 4| = 2 $ ;

So, $ d((a_1, 1), (a_4, 4)) = d((a_1, 1), (a_2, 2)) + d((a_2, 2), (a_4, 4)) $ .

## 样例 #1

### 输入

```
3
4
2 4 1 3
5
6 9 1 9 6
2
13 37```

### 输出

```
10
12
3```

# AI分析结果

### 题目内容中文重写
# 曼哈顿子数组

## 题目描述
假设你有两个点 $ p = (x_p, y_p) $ 和 $ q = (x_q, y_q) $ 。我们用 $ d(p, q) = |x_p - x_q| + |y_p - y_q| $ 来表示它们之间的曼哈顿距离。

如果三个点 $ p $ 、 $ q $ 、 $ r $ 满足 $ d(p, r) = d(p, q) + d(q, r) $ ，我们就称这三个点构成一个坏三元组。

如果一个数组 $ b_1, b_2, \dots, b_m $ 中，不可能选出三个不同的下标 $ i $ 、 $ j $ 、 $ k $ ，使得点 $ (b_i, i) $ 、 $ (b_j, j) $ 和 $ (b_k, k) $ 构成一个坏三元组，那么我们就称这个数组是好的。

现在给你一个数组 $ a_1, a_2, \dots, a_n $ ，请你计算 $ a $ 的好子数组的数量。数组 $ a $ 的子数组是指对于某些 $ 1 \le l \le r \le n $ 所构成的数组 $ a_l, a_{l + 1}, \dots, a_r $ 。

需要注意的是，根据定义，长度为 $ 1 $ 和 $ 2 $ 的子数组都是好的。

## 说明/提示
在第一个测试用例中，可以证明 $ a $ 的任何子数组都是好的。例如，子数组 $ [a_2, a_3, a_4] $ 是好的，因为它只包含三个元素，并且：
- $ d((a_2, 2), (a_4, 4)) = |4 - 3| + |2 - 4| = 3 $  $ < $  $ d((a_2, 2), (a_3, 3)) + d((a_3, 3), (a_4, 4)) = 3 + 1 + 2 + 1 = 7 $ ；
- $ d((a_2, 2), (a_3, 3)) $  $ < $  $ d((a_2, 2), (a_4, 4)) + d((a_4, 4), (a_3, 3)) $ ；
- $ d((a_3, 3), (a_4, 4)) $  $ < $  $ d((a_3, 3), (a_2, 2)) + d((a_2, 2), (a_4, 4)) $ ；

在第二个测试用例中，例如，子数组 $ [a_1, a_2, a_3, a_4] $ 不是好的，因为它包含一个坏三元组 $ (a_1, 1) $ 、 $ (a_2, 2) $ 、 $ (a_4, 4) $ ：
- $ d((a_1, 1), (a_4, 4)) = |6 - 9| + |1 - 4| = 6 $ ；
- $ d((a_1, 1), (a_2, 2)) = |6 - 9| + |1 - 2| = 4 $ ；
- $ d((a_2, 2), (a_4, 4)) = |9 - 9| + |2 - 4| = 2 $ ；

所以， $ d((a_1, 1), (a_4, 4)) = d((a_1, 1), (a_2, 2)) + d((a_2, 2), (a_4, 4)) $ 。

## 样例 #1
### 输入
```
3
4
2 4 1 3
5
6 9 1 9 6
2
13 37
```
### 输出
```
10
12
3
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先分析出坏三元组对应序列中长度为 3 的单调不升或不降子序列，再利用组合数学相关结论（如 Erdős–Szekeres 定理）得出长度大于等于 5 的子数组一定不是好的，进而通过枚举长度为 1 - 4 的子数组来计算好子数组的数量。

不同题解的差异主要体现在实现方式上，有的采用暴力枚举，有的使用树状数组、单调栈、线段树等数据结构优化，还有的结合了离散化处理。暴力枚举的实现简单但效率较低，使用数据结构的方法虽然复杂度低，但实现相对复杂。

### 所选题解
- **liangbowen（5星）**
    - **关键亮点**：思路清晰，通过画图直观展示结论，代码实现简洁，对复杂度的分析详细且准确。
    - **个人心得**：比赛时写了 $O(n^3)$ 算法就过了，原以为是数据水，后续证明了实际复杂度是 $O(n)$ ，体现了对复杂度分析的重要性。
- **sunzz3183（4星）**
    - **关键亮点**：详细分析了不同长度子数组的情况，通过分类讨论的方式，使思路易于理解，代码简洁明了。
- **xkcdjerry（4星）**
    - **关键亮点**：利用 Erdős–Szekeres 定理严谨证明结论，代码实现简洁高效，复杂度分析准确。

### 重点代码
#### liangbowen 的核心代码
```cpp
const int N = 2e5 + 5;
int a[N];
bool chk(int l, int r) // [l,r] 区间是否是坏的
{
    for (int i = l; i < r; i++)
        for (int j = l; j < i; j++) //j<i<r
        {
            if (a[j] <= a[i] && a[i] <= a[r]) return true;
            if (a[j] >= a[i] && a[i] >= a[r]) return true; //符号反过来 
        }
    return false;
}
void solve()
{
    int n;
    long long cnt = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int l = 1, r = 1; r <= n; r++) //顺序枚举右端点，左端点尺取
    {
        for (; l <= r && chk(l, r); l++);
        cnt += (r - l + 1);
    }
    printf("%lld\n", cnt);
}
```
**核心实现思想**：定义 `chk` 函数判断区间是否为坏区间，通过尺取法枚举右端点，移动左端点使当前区间为好区间，统计好子数组的数量。

#### sunzz3183 的核心代码
```cpp
bool cyl_ak_ioi(int a,int b,int c){//判断递增还是递减 
    if((a<=b&&b<=c)||(a>=b&&b>=c))
        return 0;
    else
        return 1;
}
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sum=n*2-1;//一、二种情况 
        for(int i=1;i<=n-2;i++)//第三种情况 
            if(cyl_ak_ioi(a[i],a[i+1],a[i+2]))
                sum++;
        for(int i=1;i<=n-3;i++)//第四种情况 
            if(cyl_ak_ioi(a[i],a[i+1],a[i+2])&&cyl_ak_ioi(a[i],a[i+1],a[i+3])&&cyl_ak_ioi(a[i],a[i+2],a[i+3])&&cyl_ak_ioi(a[i+1],a[i+2],a[i+3]))
                sum++;
        cout<<sum<<"\n";
    }
    return 0;
}
```
**核心实现思想**：定义 `cyl_ak_ioi` 函数判断三个数是否单调，分别处理长度为 1、2、3、4 的子数组，统计好子数组的数量。

#### xkcdjerry 的核心代码
```cpp
inline bool test3(int a,int b,int c)
{
    return !((a<=b&&b<=c)||(a>=b&&b>=c));
}
inline bool test4(int a,int b,int c,int d)
{
    return test3(a,b,c)&&test3(a,b,d)&&test3(a,c,d)&&test3(b,c,d);
}
int a[N];
void once()
{
    int n;
    scanf("%lld",&n);
    for(int i=0;i<n;i++) scanf("%lld",a+i);
    int ans=2*n-1;
    for(int i=0;i<=n-3;i++)
        if(test3(a[i],a[i+1],a[i+2]))
            ans++;
    for(int i=0;i<=n-4;i++)
        if(test4(a[i],a[i+1],a[i+2],a[i+3]))
            ans++;
    printf("%lld\n",ans);
}
```
**核心实现思想**：定义 `test3` 和 `test4` 函数分别判断长度为 3 和 4 的子数组是否为好子数组，统计好子数组的数量。

### 最优关键思路或技巧
- **数学结论的应用**：利用 Erdős–Szekeres 定理证明长度大于等于 5 的子数组一定不是好的，将问题的复杂度大大降低。
- **分类讨论**：对不同长度的子数组进行分类讨论，分别处理，使问题更加清晰。
- **尺取法**：通过尺取法枚举右端点，移动左端点，避免了不必要的计算，提高了效率。

### 拓展思路
同类型题目可能会改变距离的定义或条件的限制，但核心思路都是分析出坏情况对应的序列特征，再利用数学结论缩小枚举范围。类似的算法套路包括利用组合数学定理简化问题、分类讨论处理不同情况、使用数据结构优化枚举过程等。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：考察区间处理和枚举思想。
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：涉及数学分析和枚举操作。
- [P1200 [USACO1.1]你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)：需要对字符进行处理和简单的数学计算。

---
处理用时：74.08秒