# 题目信息

# [ARC121C] Odd Even Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc121/tasks/arc121_c

$ (1,2,\ \ldots,\ N) $ を並び替えた数列 $ p $ が与えられます。 はじめ、$ p $ の第 $ n $ 項は $ p_{n} $ です。

あなたの目的は $ N^2 $ 回以下 *操作* を行い $ p $ を昇順に並び替えることです。 あなたは操作により以下のように $ p $ を変更することができます。

- **奇数** 回目の操作では $ 1 $ 以上 $ N-1 $ 以下の **奇数** $ n $ を選んで $ p_n $ と $ p_{n+1} $ を入れ替えます。
- **偶数** 回目の操作では $ 2 $ 以上 $ N-1 $ 以下の **偶数** $ n $ を選んで $ p_n $ と $ p_{n+1} $ を入れ替えます。

この問題の制約下で必ず目的を達成できることが証明できます。 そのような操作列を $ 1 $ つ求めてください。

$ T $ 個のテストケースが与えられるのでそれぞれについて答えを求めてください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 1\ \leq\ T\ \leq\ 250 $
- $ 2\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ p_i\ \leq\ N $
- $ p $ は $ (1,2,\ldots,N) $ を並び替えて得られる。
- $ 1 $ つの入力ファイルにおいて $ N $ の総和は $ 500 $ を超えない。

### Sample Explanation 1

\- $ 1 $ つ目のテストケースについて説明します。 - $ 1 $ 回目の操作で $ 1 $ を選ぶと $ p $ は $ (1,2,3,5,4) $ となります。 - $ 2 $ 回目の操作で $ 4 $ を選ぶと $ p $ は $ (1,2,3,4,5) $ となります。 - $ (1,4) $ は操作列として正しいですが、$ (4,1) $ は操作列として正しくないことに注意してください。 - 操作を $ 1 $ 度も行わなくともよいこと、操作回数を最小にする必要はないことに注意してください。

## 样例 #1

### 输入

```
2

5

2 1 3 5 4

2

1 2```

### 输出

```
2

1 4

0```

# AI分析结果



---

### 唯一算法分类  
**构造性排序算法**

---

### 综合分析与结论  
本题核心在于设计满足奇偶性限制的交换策略。各题解均采用类似冒泡/选择排序的思路，通过构造性步骤处理奇偶性冲突，关键点如下：  
1. **核心算法流程**：  
   - 每次将一个元素（如当前最大的数）移动到其正确位置  
   - 当需要交换的位置与当前步骤奇偶性不符时，**故意进行无效交换**（如交换已排序的部分）以改变奇偶性  
   - 最终通过最多 O(N²) 次操作完成排序  

2. **解决难点**：  
   - **奇偶性冲突**：通过无效交换调整奇偶性状态  
   - **尾部处理**：对最后 2-3 个元素需特殊处理，避免死循环  

3. **可视化设计**：  
   - **动画方案**：  
     - 显示排列数组，用不同颜色标记当前操作位置（红色表奇数步骤操作点，蓝色表偶数步骤操作点）  
     - 高亮当前正在移动的目标元素（如黄色方框）  
     - 右侧面板显示操作次数、当前奇偶性状态  
   - **复古风格**：  
     - 使用 8 位像素字体和 16 色调色板，排列显示为方格阵列  
     - 每次交换时播放短促的“哔”音效，成功排序后播放胜利旋律  
     - 操作面板支持单步调试（空格键步进，方向键调整速度）  

---

### 题解清单 (≥4星)  
1. **lmy_2011（4.5星）**  
   - 亮点：递归式处理，维护 `cur` 逐步归位元素，代码结构清晰  
   - 关键逻辑：通过 `nxt ^= 1` 维护奇偶性，尾部循环确保顺序  

2. **wzt2012（4星）**  
   - 亮点：非递归实现，直接模拟元素移动，处理奇偶冲突简洁  
   - 关键逻辑：从前往后逐个归位元素，`work` 函数封装交换与状态更新  

---

### 核心代码实现  
```cpp
// 作者：wzt2012 的 solve 函数（核心逻辑）
void solve(int x) {
    if (x == n - 2) { // 处理最后三个元素
        while (!(p[n-2]<p[n-1] && p[n-1]<p[n])) {
            if (nw) swap(p[ji], p[ji+1]), ans.push_back(ji);
            else swap(p[ou], p[ou+1]), ans.push_back(ou);
            nw ^= 1;
        }
        return;
    }
    for (int i = x; i <= n; i++) {
        if (p[i] == x) {
            if (i == x) { solve(x+1); return; }
            if (i % 2 == nw) { // 奇偶性匹配时直接移动
                if (i == n) { // 处理末尾特殊情况
                    swap(p[n-2], p[n-1]);
                    ans.push_back(n-2);
                    nw ^= 1;
                } else {
                    swap(p[i], p[i+1]); ans.push_back(i);
                    swap(p[i-1], p[i]); ans.push_back(i-1);
                    i++;
                }
            }
            for (int j = i-1; j >= x; j--) { // 向前冒泡
                swap(p[j], p[j+1]);
                ans.push_back(j);
                nw ^= 1;
            }
            solve(x+1);
            return;
        }
    }
}
```

---

### 同类型题与算法套路  
- **类似构造性排序**：需在特定限制下完成排序（如只能交换相邻元素、特定位置等）  
- **相关题目**：  
  1. [Luogu P1583] 笨小猴（构造特定操作序列）  
  2. [Luogu P1966] 火柴排队（最小交换次数达成目标排列）  
  3. [Luogu P4378] Sort with Swap(0,*)（限定交换规则的最优策略）  

---

### 个人心得摘录  
- **lmy_2011**：调试中发现递归边界处理不当导致死循环，最终通过特殊处理 `n-2` 解决  
- **promise_**：实践发现连续三次无效交换可打破某些死循环模式  

---

### 可视化 JavaScript 代码片段  
```javascript
// 初始化 Canvas 与音效
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
const swapSound = new Audio('data:audio/wav;base64,UklGRl9...'); // 短音效

function drawArray(arr, stepType, activeIdx) {
  ctx.fillStyle = '#2D142C'; // 复古背景色
  ctx.fillRect(0, 0, canvas.width, canvas.height);
  arr.forEach((num, i) => {
    ctx.fillStyle = (i === activeIdx && stepType === 'odd') ? '#FF4848' :
                    (i === activeIdx) ? '#484AFF' : '#E7F2F2';
    ctx.fillRect(i * 32, 0, 30, 30); // 绘制像素方块
    ctx.fillStyle = '#2D142C';
    ctx.fillText(num, i * 32 + 8, 20);
  });
}

// 示例动画步骤
let step = 0;
function nextStep() {
  const activeIdx = operations[step].pos;
  drawArray(currentArr, operations[step].type, activeIdx);
  swapSound.play();
  swapElements(currentArr, activeIdx, activeIdx + 1);
  step++;
}
```

---
处理用时：74.60秒