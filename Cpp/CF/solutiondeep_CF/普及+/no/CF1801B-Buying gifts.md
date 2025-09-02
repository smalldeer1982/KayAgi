# 题目信息

# Buying gifts

## 题目描述

Little Sasha has two friends, whom he wants to please with gifts on the Eighth of March. To do this, he went to the largest shopping center in the city.There are $ n $ departments in the mall, each of which has exactly two stores. For convenience, we number the departments with integers from $ 1 $ to $ n $ . It is known that gifts in the first store of the $ i $ department cost $ a_i $ rubles, and in the second store of the $ i $ department — $ b_i $ rubles.

Entering the mall, Sasha will visit each of the $ n $ departments of the mall, and in each department, he will enter exactly one store. When Sasha gets into the $ i $ -th department, he will perform exactly one of two actions:

1. Buy a gift for the first friend, spending $ a_i $ rubles on it.
2. Buy a gift for the second friend, spending $ b_i $ rubles on it.

Sasha is going to buy at least one gift for each friend. Moreover, he wants to pick up gifts in such a way that the price difference of the most expensive gifts bought for friends is as small as possible so that no one is offended.

More formally: let $ m_1 $ be the maximum price of a gift bought to the first friend, and $ m_2 $ be the maximum price of a gift bought to the second friend. Sasha wants to choose gifts in such a way as to minimize the value of $ \lvert m_1 - m_2 \rvert $ .

## 说明/提示

In the first test case, Sasha has two possible options: buy a gift for the first friend in the first department, and the second friend — in the second department, or vice versa. In the first case, $ m_1 = m_2 = 1 $ , and in the second case — $ m_1 = m_2 = 2 $ . In both cases, the answer is $ 0 $ . In the second test case, you can buy gifts for the first friend in the $ 2 $ , $ 4 $ and $ 5 $ departments, and for the second friend — in the $ 1 $ and $ 3 $ departments.So $ m_1 = \max(2, 4, 2) = 4 $ , $ m_2 = \max(5, 3) = 5 $ . The answer is $ \lvert 4 - 5 \rvert = 1 $ .

## 样例 #1

### 输入

```
2
2
1 2
2 1
5
1 5
2 7
3 3
4 10
2 5```

### 输出

```
0
1```

# AI分析结果

### 题目内容重写

#### 购买礼物

**题目描述**

小Sasha有两个朋友，他想在三八妇女节给他们送礼物。为此，他去了城里最大的购物中心。购物中心有$n$个部门，每个部门恰好有两家商店。为了方便，我们用从$1$到$n$的整数给部门编号。已知第$i$个部门的第一家商店的礼物价格为$a_i$卢布，第二家商店的礼物价格为$b_i$卢布。

进入购物中心后，Sasha将依次访问每个部门，并且在每个部门中，他将进入其中一家商店。当Sasha进入第$i$个部门时，他将执行以下两个操作之一：

1. 为第一个朋友购买礼物，花费$a_i$卢布。
2. 为第二个朋友购买礼物，花费$b_i$卢布。

Sasha打算为每个朋友至少购买一个礼物。此外，他希望选择礼物时，使得为两个朋友购买的最贵礼物的价格差尽可能小，以免让任何朋友感到不公平。

更正式地说：设$m_1$为为第一个朋友购买的礼物的最高价格，$m_2$为为第二个朋友购买的礼物的最高价格。Sasha希望选择礼物，使得$|m_1 - m_2|$的值最小。

**说明/提示**

在第一个测试用例中，Sasha有两种选择：在第一个部门为第一个朋友购买礼物，在第二个部门为第二个朋友购买礼物，或者反之。在第一种情况下，$m_1 = m_2 = 1$，在第二种情况下，$m_1 = m_2 = 2$。两种情况下，答案都是$0$。在第二个测试用例中，可以在第$2$、$4$和$5$个部门为第一个朋友购买礼物，在第$1$和$3$个部门为第二个朋友购买礼物。此时$m_1 = \max(2, 4, 2) = 4$，$m_2 = \max(5, 3) = 5$。答案为$|4 - 5| = 1$。

**样例 #1**

**输入**

```
2
2
1 2
2 1
5
1 5
2 7
3 3
4 10
2 5
```

**输出**

```
0
1
```

### 算法分类
贪心、排序

### 题解分析与结论

这道题的核心在于如何选择每个部门的礼物，使得为两个朋友购买的礼物的最高价格差最小。题解中普遍采用了贪心策略，结合排序和二分查找来优化时间复杂度。

### 精选题解

#### 题解1：芷陌陌吖（4星）

**关键亮点：**
- 使用`multiset`来动态维护前后两部分的最大值，确保每次枚举时都能快速找到最接近的值。
- 通过排序和双指针技巧，优化了查找过程，时间复杂度为$O(n \log n)$。

**核心代码：**
```cpp
multiset <int> pre,nxt;
for (int i=1;i<=n;i++) {
    nxt.erase(nxt.find(s[i].b));
    auto w=nxt.end();
    int maxn=-0x3fffffff;
    if (!nxt.empty()) {
        w--;
        maxn=*w;
    }
    if (maxn>s[i].a) {
        if (ans>maxn-s[i].a) ans=maxn-s[i].a;
    } else {
        if (ans>s[i].a-maxn) ans=s[i].a-maxn;
        auto it=pre.insert(s[i].a),ed=pre.end();
        ed--;
        if (it!=pre.begin()) {
            it--;
            if (ans>s[i].a-(*it)) ans=s[i].a-(*it);
            it++;
        }
        if (it!=ed) {
            it++;
            if (ans>(*it)-s[i].a) ans=(*it)-s[i].a;
            it--;
        }
        pre.erase(it);
    }
    pre.insert(s[i].b);
}
```

#### 题解2：lingying（4星）

**关键亮点：**
- 通过预处理和后缀最大值，简化了查找过程。
- 使用`set`维护前驱和后继，确保每次枚举时都能快速找到最接近的值。

**核心代码：**
```cpp
set<int> s;
for (int i=1;i<=n;i++) {
    ans=min(ans,abs(maxn[i]-a[i].a));
    if (maxn[i]<a[i].a) {
        auto it=s.lower_bound(a[i].a);
        if (it!=s.end()) ans=min(ans,abs(*it-a[i].a));
        if (it!=s.begin()) --it, ans=min(ans,abs(*it-a[i].a));
    }
    s.insert(a[i].b);
}
```

#### 题解3：chlchl（4星）

**关键亮点：**
- 详细讨论了边界条件和特殊情况，确保代码的鲁棒性。
- 使用`multiset`和二分查找，优化了查找过程。

**核心代码：**
```cpp
set<int> s;
for (int i=1;i<=n;i++) {
    ans=min(ans,abs(gft[i].first-suf[i+1]));
    if (gft[i].first>suf[i+1]) {
        set<int>::iterator it=s.lower_bound(gft[i].first),jt=it;
        if (it!=s.end()) {
            if (*it>suf[i+1]) ans=min(ans,abs(gft[i].first-*it));
            if (it!=s.begin()) {
                jt--;
                if (*jt>suf[i+1]) ans=min(ans,abs(gft[i].first-*jt));
            }
        } else {
            if (s.size()>0&&*s.rbegin()>suf[i+1]) ans=min(ans,abs(gft[i].first-*s.rbegin()));
        }
    }
    s.insert(gft[i].second);
    if (ans==0) break;
}
```

### 最优关键思路与技巧

1. **排序与贪心**：通过将部门按照$a_i$排序，可以方便地枚举每个部门作为最大值的情况，从而简化问题。
2. **动态维护最大值**：使用`multiset`或`set`来动态维护前后两部分的最大值，确保每次枚举时都能快速找到最接近的值。
3. **二分查找**：利用二分查找来快速找到前驱和后继，进一步优化查找过程。

### 可拓展之处

类似的问题可以扩展到多个朋友或多个选择的情况，核心思路仍然是贪心结合排序和二分查找。此外，可以尝试使用其他数据结构如堆来优化查找过程。

### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

---
处理用时：54.92秒