# 题目信息

# [USACO07MAR] Monthly Expense S

## 题目描述

Farmer John is an astounding accounting wizard and has realized he might run out of money to run the farm. He has already calculated and recorded the exact amount of money (1 ≤ moneyi ≤ 10,000) that he will need to spend each day over the next N (1 ≤ N ≤ 100,000) days.

FJ wants to create a budget for a sequential set of exactly M (1 ≤ M ≤ N) fiscal periods called "fajomonths". Each of these fajomonths contains a set of 1 or more consecutive days. Every day is contained in exactly one fajomonth.

FJ's goal is to arrange the fajomonths so as to minimize the expenses of the fajomonth with the highest spending and thus determine his monthly spending limit.

给出农夫在n天中每天的花费，要求把这n天分作m组，每组的天数必然是连续的，要求分得各组的花费之和应该尽可能地小，最后输出各组花费之和中的最大值


## 说明/提示

If Farmer John schedules the months so that the first two days are a month, the third and fourth are a month, and the last three are their own months, he spends at most $500 in any month. Any other method of scheduling gives a larger minimum monthly limit.


## 样例 #1

### 输入

```
7 5
100
400
300
100
500
101
400```

### 输出

```
500```

# AI分析结果



算法分类：二分

### 综合分析与结论
题目要求将连续天数分组，使各组花费之和的最大值最小。所有题解均采用**二分答案+贪心验证**框架：
1. **二分范围**：左边界为单日花费最大值（保证分组合法），右边界为总花费（所有天分1组）。
2. **贪心验证**：遍历数组累加花费，超过mid则新建分组，统计所需组数是否≤m。
3. **调整区间**：组数过多说明mid太小需增大左边界，反之减小右边界。

---

### 精选题解与亮点

#### 1. 作者：zhaowangji（5星）
**关键亮点**：
- 代码简洁清晰，二分处理标准
- 正确初始化左边界为max(a[i])
- 验证函数逻辑直白易懂
```cpp
int main() {
    cin>>n>>m;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        l=max(l,a[i]); // 左边界初始化为最大值
        r+=a[i];
    }
    while(l<r) {
        mid=(l+r)/2;
        int sum=0,cnt=0;
        for(int i=1;i<=n;i++) {
            if(sum+a[i]>mid) sum=a[i], cnt++;
            else sum += a[i];
        }
        if(cnt>=m) l=mid+1; // 组数过多需增大mid
        else r=mid;
    }
    cout<<l;
}
```

#### 2. 作者：Mysterious_bird（4星）
**亮点**：
- 详细手动模拟样例解释二分过程
- 强调分组时需确保单个元素不超过mid
```cpp
bool check(int x) {
    int total=0, cnt=1;
    for(int i=1;i<=n;i++) {
        if(a[i]>x) return false; // 单日花费超过mid直接非法
        if(total+a[i]>x) {
            total = a[i];
            cnt++;
        } else total += a[i];
    }
    return cnt <= m;
}
```

#### 3. 作者：s_ShotღMaki（4星）
**亮点**：
- 指出与P1182为同一题型，提供迁移思路
- 代码中动态更新ans变量
```cpp
while(l <= r) {
    mid = l + r >> 1;
    if(check(mid)) l=mid+1, ans=l;
    else r=mid-1, ans=l;
}
```

---

### 核心技巧总结
1. **二分边界处理**：左边界必须为max(a[i])，否则无法处理包含大值的天数。
2. **贪心分组策略**：线性扫描累加，超限则新建分组，时间复杂度O(n)。
3. **终止条件**：当l>r时，左边界即为最小合法值。

---

### 拓展练习
1. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182) - 完全相同题型
2. [P1281 书的复制](https://www.luogu.com.cn/problem/P1281) - 最大值最小化变体
3. [P4344 [SHOI2015] 脑洞治疗仪](https://www.luogu.com.cn/problem/P4344) - 结合二分与区间操作

---

### 题解心得摘录
- *Mysterious_bird*："手动模拟样例后发现必须将左边界设为最大值，否则根本不能分"
- *ctq1999*："比赛时没注意单个元素超过mid的情况，导致100→60分"
- *天才颓废学家*："看到‘最大值最小’立刻想到二分，类似双指针但效率更高"

---
处理用时：53.32秒