# 题目信息

# Modified GCD

## 题目描述

Well, here is another math class task. In mathematics, GCD is the greatest common divisor, and it's an easy task to calculate the GCD between two positive integers.

A common divisor for two positive numbers is a number which both numbers are divisible by.

But your teacher wants to give you a harder task, in this task you have to find the greatest common divisor $ d $ between two integers $ a $ and $ b $ that is in a given range from $ low $ to $ high $ (inclusive), i.e. $ low<=d<=high $ . It is possible that there is no common divisor in the given range.

You will be given the two integers $ a $ and $ b $ , then $ n $ queries. Each query is a range from $ low $ to $ high $ and you have to answer each query.

## 样例 #1

### 输入

```
9 27
3
1 5
10 11
9 11
```

### 输出

```
3
-1
9
```

# AI分析结果



# Modified GCD 题解分析

## 算法分类
**数学（因数分解与二分查找）**

---

## 题解思路与核心难点

### 核心思路
1. **数学性质**：所有公约数必定是两数最大公约数（gcd）的因数
2. **因数预处理**：枚举 gcd(a,b) 的所有因数并排序
3. **快速查询**：在预处理的有序因数数组中，使用二分查找定位区间内的最大因数

### 解决难点
- **数学推导**：证明公约数与 gcd 的因数等价关系（反证法）
- **高效因数分解**：利用 sqrt(gcd) 优化因数枚举时间复杂度至 O(√n)
- **查询优化**：通过排序 + 二分查找将查询复杂度优化至 O(log n)

---

## 题解评分（≥4星）

### ADay（★★★★☆）
- **亮点**：简洁的 STL 应用，数学推导完整
- **关键代码**：
  ```cpp
  pos = upper_bound(v.begin(), v.end(), y) - v.begin();
  if(v[pos-1] >= x) return v[pos-1];
  ```

### tobie（★★★★☆）
- **亮点**：手写二分查找，代码控制力强
- **关键代码**：
  ```cpp
  while(ll <= rr) { // 手动二分查找最后一个 <=y 的元素
    if(ans[mid] <= y) ll = mid+1;
    else rr = mid-1;
  }
  ```

### 李至擎（★★★★☆）
- **亮点**：详细注释，适合教学
- **个人心得**：通过反例说明为何要判断 i²≠gcd 来避免重复插入

---

## 最优思路提炼
1. **关键性质**：所有公约数都是 gcd(a,b) 的因数
2. **因数生成**：通过 1~sqrt(gcd) 遍历同时记录 i 和 gcd/i
3. **查询优化**：排序后使用 upper_bound 快速定位区间右边界
4. **去重处理**：使用 unique 或插入时判断 i²≠gcd 来避免重复存储

---

## 同类型题目推荐
1. **P1414 又是毕业季II**（因数个数统计）
2. **P2424 约数和**（区间因数性质）
3. **P1072 Hankson的趣味题**（进阶因数应用）

---

## 算法可视化设计

### 核心动画流程
1. **生成因数**：展示从 1 到 sqrt(gcd) 的遍历过程，每次发现因数时：
   - **高亮**当前 i 和对应的 gcd/i
   - **插入动画**：将因数加入数组时显示飞入效果
2. **二分查找**：以渐变颜色标记查找区间 [low, high]，动态显示：
   - **当前中点**：红色高亮 mid 值
   - **区间收缩**：用箭头指示 left/right 的移动

### 复古像素风格实现
```javascript
// 示例：Canvas 绘制因数生成过程
function drawFactors() {
  ctx.fillStyle = "#8B0000"; // 暗红色像素块
  factors.forEach((f, i) => {
    const x = 10 + (i%10)*32; // 10列网格布局
    const y = 50 + Math.floor(i/10)*32;
    ctx.fillRect(x, y, 28, 28); // 绘制因数方块
    drawText(f.toString(), x+4, y+20); // 8位风格数字
  });
}
```

### 音效设计
- **发现因数**：播放 8-bit "叮" 声（440Hz 方波）
- **查询命中**：播放上升音阶（C→E→G）
- **无解情况**：播放短促低频噪音

---

## 核心代码实现
```cpp
vector<int> get_factors(int g) {
  vector<int> res;
  for(int i=1; i*i<=g; ++i) {
    if(g%i == 0) {
      res.push_back(i);
      if(i != g/i) res.push_back(g/i);
    }
  }
  sort(res.begin(), res.end());
  return res;
}

int query(int L, int R, vector<int>& factors) {
  auto it = upper_bound(factors.begin(), factors.end(), R);
  if(it == factors.begin()) return -1;
  int val = *prev(it);
  return val >= L ? val : -1;
}
```

---

## 学习心得
- **调试经验**：因数生成时忘记处理平方数导致重复元素，通过测试用例 gcd=25 发现错误
- **优化启发**：直接处理 gcd 的因数比分别处理 a、b 的因数效率提升 10 倍以上
- **思维突破**：理解「因数包含关系」是解题的关键转折点

---

通过本案例，可深入掌握数学性质推导与高效查询的结合应用，为处理类似数论问题提供通用框架。

---
处理用时：70.16秒