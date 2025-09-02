# 题目信息

# [NOI Online #3 入门组] 买表

## 题目描述

Jimmy 到 Symbol 的手表店买手表，Jimmy 只带了 $n$ 种钱币，第 $i$ 种钱币的面额为 $k_i$ 元，张数为 $a_i$ 张。Symbol 的店里一共有 $m$ 块手表，第 $i$ 块手表的价格为 $t_i$ 元。

Symbol 的手表店不能找零，所以 Jimmy 只能在凑出恰好的钱数时才能购买一块手表。现在对于店里的每块手表，Jimmy 想知道他能不能凑出恰好的钱数进行购买。


## 说明/提示

#### 样例 1 解释

- 第二块手表 $19=6 \times 3+1=6 \times 2+5+1 \times 2$，可以恰好凑出。
- 第四块手表 $1=1 \times 1$，可以恰好凑出。
- 第五块手表 $7=5+2\times 1=6 \times 1+1$，可以恰好凑出。

#### 数据规模与约定
- 对于 $50\%$ 的数据，保证 $n\leq 10$，$m \leq 60$，$a_i \leq 20$，$k_i \leq 5000$，$t_i \leq 250$。
- 对于 $100\%$ 的数据，保证 $1 \leq n \leq 200$，$1 \leq m \leq 10^5$，$1 \leq a_i \leq 1000$，$1 \leq k_i \leq 500000$，$0 \leq t_i \leq 500000$。

#### 说明

data provider：@皎月半洒花。

## 样例 #1

### 输入

```
3 5
1 2
5 1
6 3
3 19 21 1 7```

### 输出

```
No
Yes
No
Yes
Yes
```

# AI分析结果



# 算法分类
**多重背包**

---

# 题解思路与解决难点

## 核心思路
题目本质是多重背包可行性问题，需判断能否用有限数量的不同面额钱币组合出指定金额。关键解法为 **二进制优化 + bitset 位运算加速**。

### 状态转移设计
- **状态定义**：`dp[i]` 表示能否凑出金额 `i`
- **转移方程**：对每个钱币的二进制拆分块 `l*k`，执行 `dp |= dp << l*k`
- **优化核心**：将 `a_i` 个面额拆分为 `log(a_i)` 个二进制块，转化为 01 背包问题

### 解决难点对比
| 题解方法 | 时间复杂度 | 空间复杂度 | 优化点 |
|---------|------------|------------|--------|
| 朴素多重背包 | O(n * a_i * max_t) | O(max_t) | 无优化，50分做法 |
| 二进制拆分优化 | O(n * log(a_i) * max_t) | O(max_t) | 物品数量降为对数级 |
| bitset 位运算 | O(n * log(a_i) * max_t / 64) | O(max_t / 64) | 位运算加速状态转移 |
| 贪心计数法 | O(n * max_t) | O(max_t) | 无需拆分但常数较大 |

---

# 最优题解与评分

## ⭐⭐⭐⭐⭐ critnos 题解
**核心亮点**：
1. 二进制拆分将物品数量降为对数级
2. 使用 `bitset` 实现位运算批量更新状态
3. 代码极简（仅 26 行），可读性强

**关键代码**：
```cpp
bitset<500005> dp;
for(int i=0;i<n;i++){
    scanf("%d%d",&k,&a);
    for(int l=1; a>=l; l*=2){ // 二进制拆分
        dp |= dp << l*k;      // 位运算加速转移
        a -= l;
    }
    if(a) dp |= dp << a*k;    // 处理剩余部分
}
```

## ⭐⭐⭐⭐ 翼德天尊 题解
**核心亮点**：
1. 双数组计数法维护使用次数
2. 内层循环正序优化空间连续性
3. 快读与 IO 优化提升速度

**关键代码**：
```cpp
for(int i=1;i<=n;i++){
    memset(dp,0,sizeof(dp));
    for(int j=k[i];j<=maxn;j++){
        if(!can[j] && can[j-k[i]] && dp[j-k[i]]<a[i]){
            can[j]=1, dp[j]=dp[j-k[i]]+1;
        }
    }
}
```

## ⭐⭐⭐⭐ Mine_King 题解
**核心亮点**：
1. 二进制拆分模板清晰易理解
2. 预处理最大金额优化循环范围
3. 动态更新已确定范围加速

**关键代码**：
```cpp
for(rg int j=1;vv-j>=0;j*=2){ // 二进制拆分
    a[++cnt]=j*aa;
    vv-=j;
}
if(vv>0) a[++cnt]=vv*aa;
```

---

# 最优思路提炼
1. **二进制拆分**：将 `a_i` 分解为 `1,2,4,...,2^k,rem`，物品数从 O(a_i) 降为 O(loga_i)
2. **bitset 加速**：利用位运算的并行特性，单次操作处理 64 位状态
3. **离线预处理**：先处理所有钱币组合，再批量回答查询

---

# 同类型题目与算法套路
**通用多重背包优化套路**：
1. 二进制拆分 → 01 背包
2. 单调队列优化 → 线性复杂度
3. 贪心计数法 → 限制使用次数

**相似题目推荐**：
1. 洛谷 P1776 宝物筛选（多重背包最大值）
2. 洛谷 P6567 [NOI Online #3] 买表（本题）
3. HDU 1059 Dividing（多重背包可行性）

---

# 可视化设计要点

## 动态规划矩阵动画
![DP Matrix Demo](https://i.imgur.com/8W3yGv8.gif)
1. **网格绘制**：创建 500x500 的 Canvas 网格，每个单元格表示 1000 元
2. **颜色编码**：
   - 红色：当前处理的二进制块
   - 绿色：已可达的金额
   - 黄色：新更新的状态
3. **位运算特效**：显示 `dp |= dp << k` 的波浪式更新动画

## 复古像素风格实现
```javascript
// Canvas 初始化
const canvas = document.getElementById('dp-canvas');
const ctx = canvas.getContext('2d');
const PIXEL_SIZE = 4; // 4x4 像素块

function drawPixel(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x*PIXEL_SIZE, y*PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE);
}

// 音效触发
function playSound(type) {
    const sfx = {
        update: new Audio('data:audio/wav;base64,UklGRl9...'), // 短促哔声
        success: new Audio('data:audio/wav;base64,UklGRk9...') // 上扬音效
    };
    sfx[type].play();
}
```

---

# 个人心得摘录
> "在考场中因大小写错误丢分，提醒我以后要复制输出样例的'Yes'/'No'。二进制优化的关键在于理解任何数都能表示为 2 的幂次和，这需要数学直觉的积累。" —— critnos

---

# 核心代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
bitset<500005> dp; // 核心数据结构

int main() {
    int n, m, k, a;
    scanf("%d%d", &n, &m);
    dp[0] = 1;
    
    while(n--) {
        scanf("%d%d", &k, &a);
        // 二进制拆分部分
        for(int l=1; a >= l; l *= 2) {
            dp |= dp << (l * k);
            a -= l;
        }
        if(a) dp |= dp << (a * k);
    }
    
    // 查询处理
    while(m--) {
        scanf("%d", &k);
        puts(dp[k] ? "Yes" : "No");
    }
    return 0;
}
```

---
处理用时：62.57秒