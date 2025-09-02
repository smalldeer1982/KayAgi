# 题目信息

# PolandBall and Gifts

## 题目描述

It's Christmas time! PolandBall and his friends will be giving themselves gifts. There are $ n $ Balls overall. Each Ball has someone for whom he should bring a present according to some permutation $ p $ , $ p_{i}≠i $ for all $ i $ .

Unfortunately, Balls are quite clumsy. We know earlier that exactly $ k $ of them will forget to bring their gift. A Ball number $ i $ will get his present if the following two constraints will hold:

1. Ball number $ i $ will bring the present he should give.
2. Ball $ x $ such that $ p_{x}=i $ will bring his present.

What is minimum and maximum possible number of kids who will not get their present if exactly $ k $ Balls will forget theirs?

## 说明/提示

In the first sample, if the third and the first balls will forget to bring their presents, they will be th only balls not getting a present. Thus the minimum answer is $ 2 $ . However, if the first ans the second balls will forget to bring their presents, then only the fifth ball will get a present. So, the maximum answer is $ 4 $ .

## 样例 #1

### 输入

```
5 2
3 4 1 5 2
```

### 输出

```
2 4```

## 样例 #2

### 输入

```
10 1
2 3 4 5 6 7 8 9 10 1
```

### 输出

```
2 2```

# AI分析结果



**唯一算法分类**  
置换环分解、贪心、动态规划（背包问题）

---

**综合分析与结论**  

**核心思路**  
1. **置换环分解**：将排列分解为若干环，每个环独立处理。  
2. **最大值计算（贪心）**：  
   - 每个环贡献的“无法收到礼物的人数”最大值为环长。  
   - 偶环：每次选择相邻两个节点，贡献两次，最多选 `len/2` 次。  
   - 奇环：前 `(len-1)/2` 次贡献两次，最后剩余一个节点贡献一次。  
   - 贪心选择贡献最大的环，优先处理偶数部分，再处理奇数剩余。  
3. **最小值计算（背包问题）**：  
   - 每个环的选择必须覆盖整个环或部分链式覆盖。  
   - 若能用若干环长度之和等于 `k`，则最小值为 `k`，否则为 `k+1`。  
   - 使用二进制拆分优化多重背包，结合 `bitset` 加速可行性判断。  

**可视化设计思路**  
- **置换环动画**：用不同颜色标记环的节点，动态展示环的分解过程。  
- **贪心过程**：高亮当前处理的环及选择的节点，实时更新贡献值。  
- **背包填充**：用像素块表示背包容量，动态绘制 `bitset` 的位变化。  
- **复古风格**：  
  - **像素网格**：每个环表示为圆形排列的像素块，颜色区分不同环。  
  - **音效触发**：选择节点时播放“点击”音效，填充背包时播放“填充”音效。  
  - **自动演示**：模拟贪心选择和背包填充的 AI 决策过程，支持单步调试。  

---

**题解清单 (评分≥4星)**  

1. **未来姚班zyl（5星）**  
   - **亮点**：清晰的贪心策略与二进制优化的 `bitset` 实现，复杂度分析准确。  
   - **代码关键**：`solve1` 处理最大值，`solve2` 处理最小值，高效简洁。  

2. **do_while_true（4星）**  
   - **亮点**：详细解释置换环的贡献机制，多重背包的二进制分组优化。  
   - **代码关键**：使用 `bitset` 的背包可行性判断，逻辑清晰。  

3. **lsj2009（4星）**  
   - **亮点**：深入分析最小值的贡献机制，明确背包问题的转化过程。  
   - **代码关键**：`solve1` 和 `solve2` 函数分离，结构清晰。  

---

**最优思路或技巧提炼**  
1. **置换环分解**：排列问题的核心，将复杂关系转化为环结构。  
2. **贪心策略**：最大化每次选择的贡献，优先处理偶数环的完整贡献。  
3. **二进制分组优化**：将多重背包转化为 `01` 背包，结合 `bitset` 加速。  

---

**同类型题或类似算法套路**  
- **置换环相关**：如 [洛谷 P1550](https://www.luogu.com.cn/problem/P1550)。  
- **贪心+背包**：如 [洛谷 P5020](https://www.luogu.com.cn/problem/P5020)。  
- **`bitset` 优化**：如 [洛谷 P2340](https://www.luogu.com.cn/problem/P2340)。  

---

**推荐相似题目**  
1. **P1550**：置换中的轮换问题。  
2. **P5020**：货币系统的贪心与背包结合。  
3. **P2340**：`bitset` 优化背包可行性。  

---

**个人心得摘录**  
- **未来姚班zyl**：强调复杂度分析的重要性，指出其他题解在此处的不足。  
- **do_while_true**：通过根号分治优化背包问题，平衡时间与空间复杂度。  

---

**可视化与算法演示**  
```javascript
// 示例：置换环分解与贪心选择的可视化（伪代码）
class Visualizer {
  constructor(permutation) {
    this.permutation = permutation;
    this.cycles = this.findCycles();
    this.canvas = initCanvas(); // 初始化像素画布
  }

  // 分解置换环
  findCycles() {
    // 返回环的数组，如 [[1,3,5], [2,4]]
  }

  // 绘制环结构
  drawCycles() {
    // 不同环用不同颜色，节点排列成圆形
  }

  // 贪心选择最大值过程
  animateMax() {
    // 高亮当前处理的环，逐步选择节点并更新贡献值
  }

  // 背包填充过程
  animateMin() {
    // 用像素块表示背包容量，动态更新 bitset 状态
  }
}
```

**复古游戏化设计**  
- **颜色方案**：16色调色板，环节点用对比色区分。  
- **音效**：选择节点时播放 `8-bit` 音效，填充背包时触发“成功”音调。  
- **自动演示**：按贪心策略自动选择节点，支持暂停/继续。  

---

**代码片段**  
```cpp
// 核心代码（未来姚班zyl的 solve1 和 solve2）
int solve1(int k) {
    int ans = 0;
    repm(i) {
        int w = a[i] / 2;
        ans += min(w, k) * 2, k -= min(w, k);
        if (!k) return ans;
    }
    repm(i) if (a[i] & 1) {
        k--, ans++;
        if (!k) return ans;
    }
    return ans;
}

int solve2(int k) {
    B[0] = 1;
    repm(i) c[a[i]]++;
    rep(i, 1, k) if (c[i]) {
        int kk = 1, w = i;
        while (1) {
            if (c[i] >= kk) B |= (B << w), c[i] -= kk;
            else { B |= (B << (c[i] * i)); break; }
            kk <<= 1, w <<= 1;
        }
    }
    return k + (!B[k]);
}
```

---
处理用时：106.49秒