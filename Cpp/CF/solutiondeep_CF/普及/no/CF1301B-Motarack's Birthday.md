# 题目信息

# Motarack's Birthday

## 题目描述

Dark is going to attend Motarack's birthday. Dark decided that the gift he is going to give to Motarack is an array $ a $ of $ n $ non-negative integers.

Dark created that array $ 1000 $ years ago, so some elements in that array disappeared. Dark knows that Motarack hates to see an array that has two adjacent elements with a high absolute difference between them. He doesn't have much time so he wants to choose an integer $ k $ ( $ 0 \leq k \leq 10^{9} $ ) and replaces all missing elements in the array $ a $ with $ k $ .

Let $ m $ be the maximum absolute difference between all adjacent elements (i.e. the maximum value of $ |a_i - a_{i+1}| $ for all $ 1 \leq i \leq n - 1 $ ) in the array $ a $ after Dark replaces all missing elements with $ k $ .

Dark should choose an integer $ k $ so that $ m $ is minimized. Can you help him?

## 说明/提示

In the first test case after replacing all missing elements with $ 11 $ the array becomes $ [11, 10, 11, 12, 11] $ . The absolute difference between any adjacent elements is $ 1 $ . It is impossible to choose a value of $ k $ , such that the absolute difference between any adjacent element will be $ \leq 0 $ . So, the answer is $ 1 $ .

In the third test case after replacing all missing elements with $ 6 $ the array becomes $ [6, 6, 9, 6, 3, 6] $ .

- $ |a_1 - a_2| = |6 - 6| = 0 $ ;
- $ |a_2 - a_3| = |6 - 9| = 3 $ ;
- $ |a_3 - a_4| = |9 - 6| = 3 $ ;
- $ |a_4 - a_5| = |6 - 3| = 3 $ ;
- $ |a_5 - a_6| = |3 - 6| = 3 $ .

So, the maximum difference between any adjacent elements is $ 3 $ .

## 样例 #1

### 输入

```
7
5
-1 10 -1 12 -1
5
-1 40 35 -1 35
6
-1 -1 9 -1 3 -1
2
-1 -1
2
0 -1
4
1 -1 3 -1
7
1 -1 7 5 2 -1 5```

### 输出

```
1 11
5 35
3 6
0 42
0 0
1 2
3 4```

# AI分析结果

### 题目内容重写
# Motarack的生日

## 题目描述

Dark决定参加Motarack的生日。Dark决定送给Motarack的礼物是一个包含$n$个非负整数的数组$a$。

Dark在1000年前创建了这个数组，所以数组中的一些元素已经丢失了。Dark知道Motarack讨厌看到相邻元素之间绝对值差很大的数组。他没有太多时间，所以他决定选择一个整数$k$（$0 \leq k \leq 10^{9}$），并将数组$a$中所有丢失的元素替换为$k$。

设$m$为替换后数组中所有相邻元素之间绝对差的最大值（即$|a_i - a_{i+1}|$的最大值，$1 \leq i \leq n - 1$）。

Dark应该选择一个整数$k$，使得$m$最小。你能帮助他吗？

## 说明/提示

在第一个测试用例中，将所有丢失的元素替换为$11$后，数组变为$[11, 10, 11, 12, 11]$。任何相邻元素之间的绝对差为$1$。无法选择一个$k$值，使得任何相邻元素之间的绝对差$\leq 0$。因此，答案是$1$。

在第三个测试用例中，将所有丢失的元素替换为$6$后，数组变为$[6, 6, 9, 6, 3, 6]$。

- $|a_1 - a_2| = |6 - 6| = 0$；
- $|a_2 - a_3| = |6 - 9| = 3$；
- $|a_3 - a_4| = |9 - 6| = 3$；
- $|a_4 - a_5| = |6 - 3| = 3$；
- $|a_5 - a_6| = |3 - 6| = 3$。

因此，任何相邻元素之间的最大差值为$3$。

## 样例 #1

### 输入

```
7
5
-1 10 -1 12 -1
5
-1 40 35 -1 35
6
-1 -1 9 -1 3 -1
2
-1 -1
2
0 -1
4
1 -1 3 -1
7
1 -1 7 5 2 -1 5```

### 输出

```
1 11
5 35
3 6
0 42
0 0
1 2
3 4```

### 算法分类
贪心

### 题解分析与结论
题目要求通过选择一个整数$k$来替换数组中的缺失元素，使得相邻元素之间的最大绝对差最小化。通过分析，我们发现$k$的选择应使得$k$与缺失元素相邻的已知元素之间的差最小化。因此，最优的$k$通常是这些相邻元素的中位数或平均值。

### 所选题解
#### 题解1：作者：JS_TZ_ZHR (赞：4)
- **星级**：5
- **关键亮点**：通过找到缺失元素相邻的已知元素的最大值和最小值，取其中位数作为$k$，从而最小化最大绝对差。
- **个人心得**：作者一开始尝试取所有已知元素的平均值，但发现不适用，最终通过分析发现只需考虑缺失元素相邻的已知元素的最值。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[1000005],Max,Min,k,ans;
int main() {
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        Max=-1,Min=2e9;
        a[n+1]=0;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
            if(a[i]!=-1&&(a[i-1]==-1||a[i+1]==-1)){
                Max=max(Max,a[i]);
                Min=min(Min,a[i]);
            } 
        }
        k=(Max+Min)>>1;
        for(int i=1;i<=n;i++){
            if(a[i]==-1)a[i]=k;
            if(i!=1)ans=max(ans,abs(a[i]-a[i-1]));
        }
        printf("%d %d\n",ans,k);
        ans=k=0;
    }
    return 0; 
}
```

#### 题解2：作者：liqiqi (赞：2)
- **星级**：4
- **关键亮点**：使用三分法来寻找最优的$k$值，通过不断缩小搜索范围来找到最小化最大绝对差的$k$。
- **个人心得**：作者一开始尝试贪心取平均值，但发现不适用，最终通过三分法找到最优解。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000000];
int m;
long long tt = 1e9;
inline long long read() {
    long long x = 0; bool s = 0; char ch = 0;
    while (!isdigit(ch)) { s |= (ch == '-'); ch = getchar(); }
    while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch - 48); ch = getchar(); }
    return s ? -x : x;
}
long long check(long long x) {
    long long ans = 0;
    for (int i = 0; i < m-1; i++) {
        int q, w;
        if (a[i] < 0) q = x;
        else q = a[i];
        if (a[i + 1] < 0) w = x;
        else w = a[i + 1];
        ans = max(ans, (long long )abs(q - w));
    }
    tt = min(tt, ans);
    return ans;
}
long long dfs(long long l, long long r) {
    while (r - l > 1) {
        long long lmid = l+r>>1;
        long long rmid = lmid + r >> 1;
        if (check(lmid) < check(rmid)) r = rmid;
        else l = lmid;
    }
    return check(l) < check(r) ? l : r;
}
int main() {
    int n;
    cin >> n;
    while (n--) {
        cin >> m;
        tt = 1e9;
        long long mx = 0;
        for (int i = 0; i < m; i++) {
            long long h;
            h = read();
            a[i] = h;
            if (a[i] > mx) mx = a[i];
        }
        long long k=dfs(0, mx);
        cout << tt << " " << k << endl;
    }
}
```

### 最优关键思路
通过分析，我们发现$k$的选择应使得$k$与缺失元素相邻的已知元素之间的差最小化。最优的$k$通常是这些相邻元素的中位数或平均值。这种方法可以有效地最小化最大绝对差。

### 拓展思路
类似的问题可以通过贪心或三分法来解决，尤其是在需要最小化某个最大值或最大化某个最小值的情况下。这类问题通常涉及到对最优解的搜索和优化。

### 推荐题目
1. [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
2. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
3. [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)

---
处理用时：50.14秒