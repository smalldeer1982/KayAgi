# 题目信息

# LuoTianyi and the Table

## 题目描述

LuoTianyi gave an array $ b $ of $ n \cdot m $ integers. She asks you to construct a table $ a $ of size $ n \times m $ , filled with these $ n \cdot m $ numbers, and each element of the array must be used exactly once. Also she asked you to maximize the following value:

  $ \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\left(\max\limits_{1 \le x \le i, 1 \le y \le j}a_{x,y}-\min\limits_{1 \le x \le i, 1 \le y \le j}a_{x,y}\right) $ This means that we consider $ n \cdot m $ subtables with the upper left corner in $ (1,1) $ and the bottom right corner in $ (i, j) $ ( $ 1 \le i \le n $ , $ 1 \le j \le m $ ), for each such subtable calculate the difference of the maximum and minimum elements in it, then sum up all these differences. You should maximize the resulting sum.

Help her find the maximal possible value, you don't need to reconstruct the table itself.

## 说明/提示

In the first test case, the table is follows:

4113In the subtable with the bottom right corner in $ (1, 1) $ , the difference of the maximal and minimal elements is $ 4 - 4 = 0 $ .

In the subtable with the bottom right corner in $ (1, 2) $ , the difference of the maximal and minimal elements is $ 4 - 1 = 3 $ .

In the subtable with the bottom right corner in $ (2, 1) $ , the difference of the maximal and minimal elements is $ 4 - 1 = 3 $ .

In the subtable with the bottom right corner in $ (2, 2) $ , the difference of the maximal and minimal elements is $ 4 - 1 = 3 $ .

Then the maximum possible value is $ 0+3+3+3=9 $ .

In the second test case, all elements are equal, so all differences are $ 0 $ , and the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
2 2
1 3 1 4
2 2
-1 -1 -1 -1
2 3
7 8 9 -3 10 8
3 2
4 8 -3 0 -7 1
4 3
-32030 59554 16854 -85927 68060 -64460 -79547 90932 85063 82703 -12001 38762```

### 输出

```
9
0
64
71
1933711```

# AI分析结果

### 题目内容翻译
# 洛天依与表格

## 题目描述
洛天依给出了一个包含 $n \cdot m$ 个整数的数组 $b$。她要求你构造一个大小为 $n \times m$ 的表格 $a$，用这 $n \cdot m$ 个数填充该表格，且数组中的每个元素必须恰好使用一次。此外，她要求你最大化以下值：

$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\left(\max\limits_{1 \le x \le i, 1 \le y \le j}a_{x,y}-\min\limits_{1 \le x \le i, 1 \le y \le j}a_{x,y}\right)$ 

这意味着我们考虑 $n \cdot m$ 个子表格，这些子表格的左上角为 $(1,1)$，右下角为 $(i, j)$（$1 \le i \le n$，$1 \le j \le m$），对于每个这样的子表格，计算其中最大元素和最小元素的差值，然后将所有这些差值相加。你应该最大化最终的和。

请帮助她找到最大可能的值，你不需要重构表格本身。

## 说明/提示
在第一个测试用例中，表格如下：
4 1
1 3
在右下角为 $(1, 1)$ 的子表格中，最大元素和最小元素的差值为 $4 - 4 = 0$。
在右下角为 $(1, 2)$ 的子表格中，最大元素和最小元素的差值为 $4 - 1 = 3$。
在右下角为 $(2, 1)$ 的子表格中，最大元素和最小元素的差值为 $4 - 1 = 3$。
在右下角为 $(2, 2)$ 的子表格中，最大元素和最小元素的差值为 $4 - 1 = 3$。
那么最大可能的值为 $0 + 3 + 3 + 3 = 9$。
在第二个测试用例中，所有元素都相等，所以所有差值都为 $0$，答案为 $0$。

## 样例 #1
### 输入
```
5
2 2
1 3 1 4
2 2
-1 -1 -1 -1
2 3
7 8 9 -3 10 8
3 2
4 8 -3 0 -7 1
4 3
-32030 59554 16854 -85927 68060 -64460 -79547 90932 85063 82703 -12001 38762
```
### 输出
```
9
0
64
71
1933711
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是构造合适的表格来最大化给定的差值和。由于答案主要与数组中的最大值、次大值、最小值和次小值有关，所以各题解都围绕如何放置这些值来使贡献最大。
- **思路对比**：大部分题解都考虑将最大值或最小值放在 $(1, 1)$ 位置，再将次大、次小值合理放置在 $(1, 2)$ 和 $(2, 1)$ 位置，通过分类讨论不同放置情况来计算结果并取最大值。
- **算法要点**：先对数组进行排序以找出最大、次大、最小、次小值，然后根据不同的放置方案计算差值和，最后比较不同方案的结果得到最大值。
- **解决难点**：难点在于如何确定最大值、次大值、最小值和次小值的最佳放置位置，以使得尽可能多的子表格的差值最大。

### 所选题解
- **作者：Pt_crN (赞：3)，4星**
  - **关键亮点**：思路简洁，代码实现简单，通过交换 $n$ 和 $m$ 简化了后续的计算。
- **作者：ScapegoatTree (赞：1)，4星**
  - **关键亮点**：代码结构清晰，使用 `memset` 初始化数组，逻辑明确。
- **作者：fengziyi (赞：1)，4星**
  - **关键亮点**：详细阐述了思路，通过直接比较找出最大、次大、最小、次小值，避免了排序操作。

### 重点代码
#### Pt_crN 的代码
```cpp
int n,m,e[200007];
void solve(){
    scanf("%d%d",&n,&m);
    if(n<m)
        swap(n,m);
    for(int i=1;i<=n*m;i++)
        scanf("%d",&e[i]);
    sort(e+1,e+n*m+1);
    printf("%lld\n",1ll*(n-1)*m*(e[n*m]-e[1])+1ll*(m-1)*max(e[n*m-1]-e[1],e[n*m]-e[2]));
}
signed main(){
    int t=1;
    scanf("%d",&t);
    while(t--)
        solve();
}
```
**核心实现思想**：先交换 $n$ 和 $m$ 使得 $n \geq m$，然后读取数组并排序，最后根据公式计算结果。

#### ScapegoatTree 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,m;
int b[10005];
void solve(){
    cin>>n>>m;
    memset(b,0,sizeof(b));
    for(int i=0;i<n*m;i++) cin>>b[i];
    sort(b,b+n*m);
    long long ans1=((b[n*m-1]-b[1])*(min(n,m)-1))+((b[n*m-1]-b[0])*(n*m-(min(n,m)-1)-1));
    long long ans2=((b[n*m-2]-b[0])*(min(n,m)-1))+((b[n*m-1]-b[0])*(n*m-(min(n,m)-1)-1));
    long long ans=max(ans1,ans2);
    cout<<ans<<'\n';
}
int main(){
    cin>>T;
    while(T--)solve();
    return 0;
}
```
**核心实现思想**：读取输入，初始化数组，排序后计算两种放置方案的结果，取最大值输出。

#### fengziyi 的代码
```cpp
while (T--)
{
    cin >> n >> m;
    int len = n * m;
    int mx = -inf, smx = -inf, mn = inf, smn = inf;
    for (reg int i = 1, x; i <= len; ++i)
    {
        cin >> x;
        if (x >= mx)       { smx = mx; mx = x; }
        else if (x >= smx) { smx = x; }
        if (x <= mn)       { smn = mn; mn = x; }
        else if (x <= smn) { smn = x; }
    }
    i64 res1 = (mx - smn) * (min(n, m) - 1)
             + (max(n, m) - 1) * min(n, m) * (mx - mn);
    i64 res2 = (smx - mn) * (min(n, m) - 1) 
             + (max(n, m) - 1) * min(n, m) * (mx - mn);
    cout << max(res1, res2) << endl;
}
```
**核心实现思想**：通过遍历数组找出最大、次大、最小、次小值，然后计算两种放置方案的结果，取最大值输出。

### 最优关键思路或技巧
- 贪心思想：通过合理放置最大值、次大值、最小值和次小值，使得尽可能多的子表格的差值最大。
- 分类讨论：考虑最大值或最小值在 $(1, 1)$ 位置的不同情况，计算不同方案的结果并取最大值。

### 拓展思路
同类型题或类似算法套路通常涉及构造满足特定条件的结构以优化某个目标值。解题时可先分析目标值与哪些元素相关，再通过合理的放置或组合这些元素来达到最优解。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得
- **fengziyi**：赛时先做 C 题没做出来，在夜自修结束前在机房卡点通过本题，提醒我们做题时要合理分配时间，遇到难题可先跳过。

---
处理用时：51.12秒