# 题目信息

# Square Subsets

## 题目描述

Petya was late for the lesson too. The teacher gave him an additional task. For some array $ a $ Petya should find the number of different ways to select non-empty subset of elements from it in such a way that their product is equal to a square of some integer.

Two ways are considered different if sets of indexes of elements chosen by these ways are different.

Since the answer can be very large, you should find the answer modulo $ 10^{9}+7 $ .

## 说明/提示

In first sample product of elements chosen by any way is $ 1 $ and $ 1=1^{2} $ . So the answer is $ 2^{4}-1=15 $ .

In second sample there are six different ways to choose elements so that their product is $ 4 $ , and only one way so that their product is $ 16 $ . So the answer is $ 6+1=7 $ .

## 样例 #1

### 输入

```
4
1 1 1 1
```

### 输出

```
15
```

## 样例 #2

### 输入

```
4
2 2 2 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
5
1 2 4 5 8
```

### 输出

```
7
```

# AI分析结果



# Square Subsets 题解分析

## 算法分类
**线性基** 或 **状压动态规划**

---

## 核心思路与解决难点

### 核心思路
1. **质因数奇偶性**：平方数的质因数指数均为偶数，将每个数转换为质因数指数奇偶性的二进制状态。
2. **异或性质**：子集乘积的质因数奇偶性等价于各元素状态的异或和为零。
3. **线性基**：将每个数的状态插入线性基，答案由基外元素的自由组合数决定。
4. **状压DP**：维护状态掩码，通过动态规划统计合法子集数。

### 解决难点
- **状态压缩**：70以内质数共19个，需将每个数转换为19位的二进制状态。
- **高效计算组合数**：利用二项式定理简化奇偶选法数（2^{k-1}）。
- **滚动数组优化**：状压DP使用滚动数组节省空间至 O(2^19)。
- **线性基构造**：正确维护线性基的插入操作，统计基的大小。

---

## 题解评分（≥4星）

### 1. 作者：bztMinamoto（线性基） ★★★★★
- **亮点**：代码简洁，时间复杂度 O(n·19)，空间高效。
- **关键代码**：
  ```cpp
  void insert(int x) {
    for(int i=18;i>=0;--i) if(x>>i&1) {
      if(!b[i]) {b[i]=x; break;}
      x^=b[i];
    }
  }
  ```

### 2. 作者：pmt2018（状压DP） ★★★★☆
- **亮点**：详细推导状态转移，预处理幂次优化。
- **关键代码**：
  ```cpp
  for(int mask=0; mask < (1<<19); mask++){
    int mask1 = mask ^ state[i];
    dp[I][mask1] += dp[I^1][mask] * h[cnt[i]-1];
  }
  ```

### 3. 作者：rui_er（线性基） ★★★★☆
- **亮点**：清晰的质因数分解与线性基插入流程。
- **关键代码**：
  ```cpp
  for(int j=0; j<=18; j++) {
    while(a[i]%p[j]==0) now ^= (1<<j), a[i]/=p[j];
  }
  ```

---

## 最优思路提炼
1. **线性基法**：
   - 将每个数转换为质因数奇偶性状态（19位掩码）。
   - 插入线性基，统计基大小 `cnt`。
   - 答案为 `2^(n-cnt) - 1`（排除空集）。

2. **状压DP法**：
   - 预处理每个数的出现次数和状态。
   - 动态维护状态掩码，分奇偶选法转移。
   - 最终答案 `dp[70][0] - 1`。

---

## 同类题目推荐
1. **P4301 [CQOI2013] 新Nim游戏**（线性基应用）
2. **P4869 Albus的第一次出场**（子集异或问题）
3. **P2114 质数检测**（质因数分解与状态处理）

---

## 可视化与算法演示

### 算法流程（线性基）
1. **像素化状态表示**：每个质数对应一个像素块，奇数为红色，偶数为绿色。
2. **插入动画**：
   - 当前数状态以8位风格显示，插入时播放"滴"声。
   - 线性基数组动态更新，成功插入时基元素闪烁。
3. **自动演示模式**：
   - 模拟AI逐步插入每个数，显示异或过程。
   - 完成时播放胜利音效，显示最终答案。

### 复古游戏设计
- **音效**：插入成功（8-bit "beep"），计算完成（胜利旋律）。
- **积分系统**：每正确插入一个基元素+10分，错误无扣分。
- **Canvas动画**：基元素以网格显示，状态变化时更新颜色。

---

## 代码片段（线性基核心）

```cpp
const int p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int b[20], cnt;

void insert(int x) {
    for(int i=18; i>=0; i--) if(x>>i&1) {
        if(!b[i]) { b[i]=x; cnt++; break; }
        x ^= b[i];
    }
}

int main() {
    int n; cin >> n;
    for(int i=1; i<=n; i++) {
        int a, s=0; cin >> a;
        for(int j=0; j<19; j++) {
            int c=0;
            while(a%p[j]==0) a/=p[j], c^=1;
            s |= c << j;
        }
        insert(s);
    }
    cout << (1LL << (n - cnt)) - 1;
}
```

---

## 总结
**线性基法**以其高效性和简洁性成为最优解，适用于大n场景；**状压DP**则直观展示了状态转移过程。可视化设计通过复古像素风格和音效增强学习趣味性，帮助理解核心的异或性质与线性基操作。

---
处理用时：77.78秒