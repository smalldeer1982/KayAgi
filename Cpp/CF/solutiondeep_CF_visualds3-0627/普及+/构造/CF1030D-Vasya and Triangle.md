# 题目信息

# Vasya and Triangle

## 题目描述

Vasya has got three integers $ n $ , $ m $ and $ k $ . He'd like to find three integer points $ (x_1, y_1) $ , $ (x_2, y_2) $ , $ (x_3, y_3) $ , such that $ 0 \le x_1, x_2, x_3 \le n $ , $ 0 \le y_1, y_2, y_3 \le m $ and the area of the triangle formed by these points is equal to $ \frac{nm}{k} $ .

Help Vasya! Find such points (if it's possible). If there are multiple solutions, print any of them.

## 说明/提示

In the first example area of the triangle should be equal to $ \frac{nm}{k} = 4 $ . The triangle mentioned in the output is pictured below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1030D/7ee3f0a3ce75449bbc8ed199a32a394763a46df2.png)In the second example there is no triangle with area $ \frac{nm}{k} = \frac{16}{7} $ .

## 样例 #1

### 输入

```
4 3 3
```

### 输出

```
YES
1 0
2 3
4 1
```

## 样例 #2

### 输入

```
4 4 7
```

### 输出

```
NO
```

# AI分析结果



# 算法分类
**数论**

---

## 综合分析与结论

### 核心思路与难点
**问题核心**：构造格点三角形满足面积 S = nm/k。  
**核心难点**：  
1. 面积必须满足半整数条件（2S ∈ ℕ） → 需判断 2nm 能否被 k 整除  
2. 分解因数构造直角边，确保 x ≤ n, y ≤ m  
**通用解法**：  
1. 判断 2nm 能否被 k 整除，否则直接输出 NO  
2. 分解 k 的质因数，分配到 n 和 m 上得到 x,y  
3. 对奇偶情况特殊处理（奇数 k 需调整 ×2）  

---

## 题解清单（≥4星）

### 1. 作者：da32s1da（★★★★☆）
**亮点**：  
- 利用 GCD 分解因数，公式推导清晰  
- 通过调整 x/2 和 y×2 保证边界条件  
- 代码简洁，直接构造原点+坐标轴端点  

### 2. 作者：DJRzjl（★★★★☆）
**亮点**：  
- 奇偶分类讨论，严谨处理因数分配  
- 通过质因数分解实现 O(1) 构造  
- 代码复用质因数分解函数，模块化设计  

### 3. 作者：unputdownable（★★★★☆）
**亮点**：  
- 分情况讨论因数分配策略  
- 代码实现简洁，直接输出坐标轴端点  
- 包含质因数分解的优化步骤  

---

## 最优思路与技巧提炼

### 关键算法步骤
1. **条件检查**：计算 `if (2*n*m) % k != 0` → 无解  
2. **因数分配**：  
   - 分解 k 的质因数，优先分配至 n 或 m 的约数中  
   - 奇数 k 处理：将多余的 2 乘到较小的一边  
3. **构造直角边**：取 (0,0), (x,0), (0,y) 三点  

### 代码实现片段
```cpp
// da32s1da 的核心代码（调整版）
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

void solve() {
    LL n, m, k; 
    cin >> n >> m >> k;
    if (2LL * n * m % k != 0) { cout << "NO"; return; }
    
    LL g = gcd(2 * n, k);
    LL x = (2 * n) / g;
    k /= g;
    LL y = m / k;
    
    if (x > n) { x /= 2; y *= 2; }
    cout << "YES\n0 0\n" << x << " 0\n0 " << y;
}
```

---

## 同类型题与算法套路

### 相似算法题
1. **分解因数构造问题**：如矩形面积分解、最大公约数应用  
2. **格点几何问题**：皮克定理相关题目  
3. **数论构造题**：需通过因数分解/模运算构造解  

### 推荐题目
1. [CF1C Ancient Berland Circus](https://www.luogu.com.cn/problem/CF1C)  
2. [ABC191E Come to Quickly](https://atcoder.jp/contests/abc191/tasks/abc191_e)  
3. [洛谷P2651 添加括号](https://www.luogu.com.cn/problem/P2651)  

---

## 可视化与算法演示

### 核心动画设计
1. **像素化网格**：以 16x16 像素块绘制 n×m 矩形，坐标轴端点用不同颜色标记  
2. **因数分解过程**：  
   - 高亮当前分解的质因数（如红色块）  
   - 显示质因数分配到 n/m 的过程（箭头动画）  
3. **调整步骤**：  
   - 当 x 超过 n 时，显示 x/2 和 y×2 的缩放动画  
   - 播放 8-bit 音效（如 "blip" 声）提示调整成功  

### 复古游戏 UI 设计
- **背景**：深蓝网格，类似示波器效果  
- **控制面板**：  
  - 按钮：播放/暂停/重置（像素风格贴图）  
  - 速度滑块：控制分解动画速度  
- **音效**：  
  - 分解成功：上升音阶（Do→Mi→So）  
  - 调整操作：经典 FC 跳跃音效  

---

## 个人心得摘录
- **调试教训**：未处理 k 的奇偶性导致构造失败（来自 wjyyy 的题解）  
- **顿悟点**：直角边构造法将三维问题降维到二维分解（来自 da32s1da 的推导）

---
处理用时：102.66秒