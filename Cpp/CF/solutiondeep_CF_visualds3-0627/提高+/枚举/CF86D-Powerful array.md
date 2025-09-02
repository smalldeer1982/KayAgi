# 题目信息

# Powerful array

## 题目描述

An array of positive integers $ a_{1},a_{2},...,a_{n} $ is given. Let us consider its arbitrary subarray $ a_{l},a_{l+1}...,a_{r} $ , where $ 1<=l<=r<=n $ . For every positive integer $ s $ denote by $ K_{s} $ the number of occurrences of $ s $ into the subarray. We call the power of the subarray the sum of products $ K_{s}·K_{s}·s $ for every positive integer $ s $ . The sum contains only finite number of nonzero summands as the number of different values in the array is indeed finite.

You should calculate the power of $ t $ given subarrays.

## 说明/提示

Consider the following array (see the second sample) and its \[2, 7\] subarray (elements of the subarray are colored):

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF86D/5e3c36b108711f9f95c3c3519472e9f583328f8b.png) Then $ K_{1}=3 $ , $ K_{2}=2 $ , $ K_{3}=1 $ , so the power is equal to $ 3^{2}·1+2^{2}·2+1^{2}·3=20 $ .

## 样例 #1

### 输入

```
3 2
1 2 1
1 2
1 3
```

### 输出

```
3
6
```

## 样例 #2

### 输入

```
8 3
1 1 2 2 1 3 1 1
2 7
1 6
2 7
```

### 输出

```
20
20
20
```

# AI分析结果



### 算法分类
**莫队算法**

---

### 综合分析与结论
本题核心是多次区间查询统计元素出现次数的平方乘值的总和。莫队算法通过离线排序查询和增量更新的方式实现 O(n√n) 时间复杂度，是最优解法。

#### 核心算法流程与可视化设计
1. **增量更新公式**  
   当元素 x 出现次数从 cnt[x] 变为 cnt[x]±1 时，总和变化量为：  
   `Δ = x * ( (cnt[x]±1)^2 - cnt[x]^2 ) = x * (2*cnt[x] ± 1)`  
   在代码中用 `sum += x * (2*cnt[x] + 1)` 和 `sum -= x * (2*cnt[x] - 1)` 实现。

2. **可视化设计要点**  
   - **指针移动动画**：用左右指针的移动轨迹展示当前处理区间，高亮新加入或删除的元素。  
   - **颜色标记**：当前处理的元素用红色边框标记，cnt[x] 的变化用颜色渐变（如蓝色加深表示增加次数）。  
   - **复古像素风格**：数组元素显示为像素方块，每个方块显示值和当前出现次数。背景音乐使用 8-bit 风格循环音轨，指针移动时播放“滴”声，更新 sum 时播放“叮”声。  
   - **交互面板**：支持暂停/继续、调整动画速度，提供“自动演示”模式模拟算法执行流程。

---

### 题解清单（评分≥4星）

1. **cyffff 的莫队实现（5星）**  
   **亮点**：  
   - 奇偶排序优化减少指针移动次数  
   - 使用位运算压缩代码，提升效率  
   - 完整注释和复杂度分析  

   **核心代码**：  
   ```cpp
   inline void add(int p){ cnt[a[p]]++, ans += (2*cnt[a[p]]-1)*a[p]; }
   inline void del(int p){ cnt[a[p]]--, ans -= (2*cnt[a[p]]+1)*a[p]; }
   ```

2. **maowuyou 的莫队实现（4.5星）**  
   **亮点**：  
   - 清晰展示平方差公式推导过程  
   - 代码结构简洁，适合初学者理解  

   **核心代码**：  
   ```cpp
   void add(int x){ sum += a[x]*(2*cnt[a[x]]+1); cnt[a[x]]++; }
   void del(int x){ cnt[a[x]]--; sum -= a[x]*(2*cnt[a[x]]+1); }
   ```

3. **Gu_Pigeon 的分块实现（4星）**  
   **亮点**：  
   - 尝试分块解法提供不同视角  
   - 包含离散化和块长调优的调试经验  

---

### 最优思路提炼
1. **莫队算法核心**：离线排序查询，按块奇偶性交替排序右端点，减少指针移动距离。  
2. **增量更新技巧**：利用平方差公式将 O(1) 更新操作化简为一次乘法和加法。  
3. **奇偶排序优化**：同一块内奇偶交替排序右端点，避免指针“震荡”移动。

---

### 同类型题推荐
1. **P2709 小B的询问**（莫队模板题，统计出现次数平方和）  
2. P1903 数颜色（带修莫队，支持单点修改）  
3. P1494 小Z的袜子（概率计算，莫队结合组合数学）

---

### 个人心得摘录
- **cyffff**：块长设为 `n/sqrt(m*2/3)` 避免除零错误，强调奇偶排序的实践效果。  
- **ykuouzf**：分块解法在 MLE 和 TLE 间反复调整块长，最终通过离散化勉强通过。  
- **Gu_Pigeon**：调试中发现 `sum` 必须用 `long long`，否则会溢出导致 WA。

---

### 核心代码实现（cyffff 题解节选）
```cpp
void add(int p){ cnt[a[p]]++, ans += (2*cnt[a[p]]-1)*a[p]; }
void del(int p){ cnt[a[p]]--, ans -= (2*cnt[a[p]]+1)*a[p]; }

// 排序函数
bool operator<(const que &a,const que &b){
    return a.l/sz^b.l/sz ? a.l<b.l : (a.l/sz&1 ? a.r<b.r : a.r>b.r);
}

// 主循环
int L=1, R=0;
for(int i=1; i<=m; i++){
    while(L < q[i].l) del(L++);
    while(L > q[i].l) add(--L);
    while(R < q[i].r) add(++R);
    while(R > q[i].r) del(R--);
    res[q[i].id] = ans;
}
```

---

### 可视化方案设计（伪代码）
```javascript
// Canvas初始化
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const PIXEL_SIZE = 20; // 像素块大小
let isAutoPlay = true;

// 绘制数组元素
function drawArray(arr, L, R) {
  arr.forEach((num, i) => {
    ctx.fillStyle = (i >= L && i <= R) ? '#FF0000' : '#FFFFFF';
    ctx.fillRect(i*PIXEL_SIZE, 0, PIXEL_SIZE, PIXEL_SIZE);
    ctx.fillStyle = '#000';
    ctx.fillText(num, i*PIXEL_SIZE + 5, 15);
  });
}

// 播放音效
function playSound(type) {
  const freq = type === 'add' ? 440 : 220;
  const oscillator = audioCtx.createOscillator();
  oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
  oscillator.connect(audioCtx.destination);
  oscillator.start();
  oscillator.stop(audioCtx.currentTime + 0.1);
}
```

---

### 复古游戏化效果
- **8-bit 风格**：使用 16 色调色板，数组元素显示为红白机风格的像素块。  
- **自动演示模式**：算法自动运行，每步间隔 500ms，按空格键暂停/继续。  
- **积分系统**：正确完成查询+100 分，错误操作-50 分，连击正确加倍奖励。  
- **音效设计**：指针移动时播放“哔”声，更新 cnt 时播放“咔”声，完成查询播放胜利音效。

---
处理用时：90.29秒