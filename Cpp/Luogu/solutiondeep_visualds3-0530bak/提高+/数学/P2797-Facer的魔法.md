# 题目信息

# Facer的魔法

## 题目背景

Facer 误闯入禁地，学会了魔法。

## 题目描述

Facer 闯入禁地之后，遇到了对手。

具体来说，Facer 魔法是一串数字。

但是 Facer 能力有限，这串数字只能从给定的 $n$ 个数中选择，能产生的魔法值为选择出的这些数字的平均数。

他的对手不会像 Facer 这样的强大的魔法，但是他会克制招数，即从 Facer 选出的数字中找出中位数，便是他的魔法值。

求 Facer 最多能克制对方多少点魔法。

一句话题意：给你 $n$ 个数，你可以选若干个数，使得平均数减中位数最大。

## 说明/提示

- 对于 $20\%$ 的数据，$n \leq 100$；
- 对于 $50\%$ 的数据，$n \leq 2000$；
- 对于 $100\%$ 的数据，$n \leq 10^5$，$0 \leq x_i \leq 10^6$。

## 样例 #1

### 输入

```
4
1 2 3 4```

### 输出

```
0.33```

## 样例 #2

### 输入

```
4
1 2 3 9```

### 输出

```
2.00```

## 样例 #3

### 输入

```
2
1 2```

### 输出

```
0.00```

# AI分析结果



## 算法分类
组合数学

---

## 题解思路与算法分析

### 核心数学原理
1. **奇数性质**：最优解必为奇数个元素，偶数解可用奇数解替代且更优
2. **贪心策略**：选定中位数后，从两侧尽可能选取大的数值以最大化平均数
3. **单峰性证明**：对于固定中位数，平均数的变化呈现单峰特性，可用二分/三分法快速定位极值

### 关键公式推导
设排序后数组为a[1..n]，当前中位数为a[i]，左右各取k个元素：
- 平均数 = (前缀和[i-k-1..i-1] + 后缀和[n-k..n] + a[i]) / (2k+1)
- 目标函数 = 平均数 - a[i]

### 算法可视化设计
1. **排序动画**：展示数组排序过程，用不同颜色标记后续将选取的左右区间
2. **单峰曲线**：以折线图显示不同k值对应的目标函数值，动态标注二分/三分点
3. **元素标记**：用高亮框标记当前选取的左右k个元素及中位数

```javascript
// 伪代码示例：单步三分法可视化
function visualizeTernary(i, l, r) {
  drawArray(); // 绘制排序后的数组
  highlightElement(i, 'median'); // 高亮当前中位数
  drawSelection(i-l, i-1, 'left'); // 左侧选取元素
  drawSelection(n-r, n, 'right'); // 右侧选取元素
  updateChart(l, r); // 更新目标函数曲线
}
```

---

## 最优题解推荐 (4星以上)

### 1. XG_Zepto 题解 (⭐⭐⭐⭐⭐)
- **亮点**：严格数学证明 + 高效二分实现
- **核心代码**：
```cpp
ll sum(int x,int l) { 
    return s[n]-s[n-l]+s[x]-s[x-l-1]; 
}
while(l<r) {
    ll s1=sum(i,mid)*(2*mid+3); // 避免浮点运算
    ll s2=sum(i,mid+1)*(2*mid+1);
    if(s1>s2) r=mid; else l=mid+1;
}
```

### 2. TonyYin 题解 (⭐⭐⭐⭐)
- **亮点**：完整推导过程 + 分步优化指导
- **调试心得**：通过构造差值公式证明单峰性，确保二分正确性

### 3. zhn_666 题解 (⭐⭐⭐⭐)
- **亮点**：三分法实现 + 整数域处理技巧
- **特色代码**：
```cpp
mid=(l*2+r)/3; 
midr=(l+r*2+2)/3; // 整数三分特殊处理
```

---

## 核心实现代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
double ans;
int a[MAXN];
long long prefix[MAXN];

double evaluate(int i, int k) {
    long long sum = prefix[i] - prefix[i-k-1];
    sum += prefix[n] - prefix[n-k];
    return (double)sum / (2*k+1) - a[i];
}

int main() {
    int n; cin >> n;
    for(int i=1; i<=n; ++i) cin >> a[i];
    sort(a+1, a+n+1);
    for(int i=1; i<=n; ++i) 
        prefix[i] = prefix[i-1] + a[i];
    
    for(int i=1; i<=n; ++i) {
        int l=1, r=min(i-1,n-i);
        while(l <= r) {
            int mid = (l+r)/2;
            if(evaluate(i,mid) > evaluate(i,mid-1)) 
                l = mid+1;
            else 
                r = mid-1;
        }
        ans = max(ans, evaluate(i,r));
    }
    printf("%.2f\n", ans);
}
```

---

## 同类题目推荐
1. [CF626E](https://codeforces.com/problemset/problem/626/E) 原题变形
2. [P1471 方差](https://www.luogu.com.cn/problem/P1471) 统计量优化
3. [P2115 子串平均数](https://www.luogu.com.cn/problem/P2115) 滑动窗口应用

---

## 可视化实现方案

### 复古像素风格设计
1. **颜色方案**：8位色系，中位数用黄色，左侧选区红色，右侧选区蓝色
2. **动画元素**：
   - 排序过程：元素冒泡动画，每次交换播放"滴"声
   - 选区扩展：左右选区以像素块向外延伸，伴随扫描线效果
3. **音效设计**：
   - 正确选择：8-bit 上升音阶
   - 错误选择：短促爆破音
   - 峰值到达：长鸣提示音

```javascript
// 示例音效触发
function playSound(type) {
    const ctx = new AudioContext();
    const osc = ctx.createOscillator();
    osc.frequency.value = type === 'success' ? 880 : 220;
    osc.connect(ctx.destination);
    osc.start(); osc.stop(ctx.currentTime + 0.1);
}
```

---

## 关键思维突破点
1. **逆向思维**：不是直接最大化平均数，而是通过控制中位数位置进行约束
2. **单调性转换**：将看似复杂的二维问题（选数个数+中位位置）拆解为排序后的一维枚举问题
3. **计算优化**：前缀和预处理将O(k)求和降为O(1)查询，实现复杂度质的飞跃

---
处理用时：76.40秒