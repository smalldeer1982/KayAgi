# 题目信息

# Taxes

## 题目描述

Mr. Funt now lives in a country with a very specific tax laws. The total income of mr. Funt during this year is equal to $ n $ ( $ n>=2 $ ) burles and the amount of tax he has to pay is calculated as the maximum divisor of $ n $ (not equal to $ n $ , of course). For example, if $ n=6 $ then Funt has to pay $ 3 $ burles, while for $ n=25 $ he needs to pay $ 5 $ and if $ n=2 $ he pays only $ 1 $ burle.

As mr. Funt is a very opportunistic person he wants to cheat a bit. In particular, he wants to split the initial $ n $ in several parts $ n_{1}+n_{2}+...+n_{k}=n $ (here $ k $ is arbitrary, even $ k=1 $ is allowed) and pay the taxes for each part separately. He can't make some part equal to $ 1 $ because it will reveal him. So, the condition $ n_{i}>=2 $ should hold for all $ i $ from $ 1 $ to $ k $ .

Ostap Bender wonders, how many money Funt has to pay (i.e. minimal) if he chooses and optimal way to split $ n $ in parts.

## 样例 #1

### 输入

```
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
27
```

### 输出

```
3
```

# AI分析结果



### 算法分类
数论（质数判断与哥德巴赫猜想应用）

---

### 题解思路与核心逻辑

#### 核心算法流程
1. **质数判断**：使用试除法（复杂度 O(√n)）
2. **决策树**：
   - 若 n 是质数 → 税金 1
   - 若 n 是偶数 → 税金 2（哥德巴赫猜想保证）
   - 若 n 是奇数：
     - 检查 n-2 是否为质数 → 是则税金 2（拆分为 2 和质数）
     - 否则税金 3（拆分为 3 和偶数）

#### 解决难点
1. **奇数拆分**：当 n 为奇数时，若 n-2 是质数则能拆分，否则需拆成三部分
2. **边界处理**：正确处理 n=2 的特殊情况（质数且偶数）

---

### 题解评分（≥4星）

1. **yyyer（5星）**  
   - 完整覆盖所有情况，代码简洁
   - 注释清晰，处理逻辑直击核心
   - 关键注释点明哥德巴赫猜想应用

2. **ADivT（4星）**  
   - 使用高效质数判断逻辑
   - 合并判断条件减少冗余代码
   - 代码注释解释猜想应用

3. **SqrtSecond（4星）**  
   - 添加错误修正说明，体现调试过程
   - 通过失败案例强调核心判断条件的重要性
   - 提供错误与正确代码对比

---

### 最优思路提炼

**关键技巧**：
- 哥德巴赫猜想简化决策树：
  ```python
  if is_prime(n): return 1
  elif n%2 ==0: return 2
  else: return 2 if is_prime(n-2) else 3
  ```
- 质数判断优化：只需检查到 √n 的整数范围

**思维突破**：
- 将大数拆解问题转化为质数组合问题
- 利用奇偶性分析降低问题复杂度

---

### 同类题目推荐
1. P1217 [USACO1.5] 回文质数
2. P3383 【模板】线性筛素数
3. P1304 哥德巴赫猜想

---

### 可视化设计（像素版）

**动画规则**：
```javascript
// 初始化
const canvas = 创建16x16网格()
const 音效库 = {
  质数: 加载音效('8bit-bling.wav'),
  拆分: 加载音效('coin-collect.wav')
}

function 主流程(n) {
  高亮数字(n, 黄色)
  if (is_prime(n)) {
    播放音效(质数)
    显示爆炸特效(n)
    return 1
  }
  
  if (n % 2 === 0) {
    分解动画(n, 蓝色粒子, 分解为两个质数)
    return 2
  }

  const 候选数 = n - 2
  显示浮动箭头(候选数)
  if (is_prime(候选数)) {
    播放拆分音效
    显示组合动画(2, 候选数)
    return 2
  } else {
    显示三部分爆炸(n => 3 + 偶数分解)
    return 3
  }
}
```

**交互特性**：
- WASD 控制数字选择
- 空格键单步执行算法
- F 键自动播放完整流程
- 右侧面板显示当前税金计算逻辑树

---

### 代码实现（核心逻辑）

```cpp
bool is_prime(int x) {
  if (x < 2) return false;
  for (int i=2; i*i<=x; ++i)
    if (x%i == 0) return false;
  return true;
}

int main() {
  int n; cin >> n;
  if (is_prime(n)) cout << 1;
  else if (n%2 == 0) cout << 2;
  else cout << (is_prime(n-2) ? 2 : 3);
  return 0;
}
```

---

### 思维拓展

**进阶问题**：
若 n ≤ 1e18，如何优化质数判断？
- 应用米勒-拉宾素性测试（概率算法）
- 预处理小质数进行快速试除

**数学证明**：
- 哥德巴赫猜想在 4e18 内已被验证成立
- 奇数拆解定理：任何奇数 ≥7 可表示为 3 + 偶数

---
处理用时：65.67秒