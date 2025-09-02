# 题目信息

# Cat, Fox and Double Maximum

## 题目描述

Fox loves permutations! She came up with the following problem and asked Cat to solve it:

You are given an even positive integer $ n $ and a permutation $ ^\dagger $ $ p $ of length $ n $ .

The score of another permutation $ q $ of length $ n $ is the number of local maximums in the array $ a $ of length $ n $ , where $ a_i = p_i + q_i $ for all $ i $ ( $ 1 \le i \le n $ ). In other words, the score of $ q $ is the number of $ i $ such that $ 1 < i < n $ (note the strict inequalities), $ a_{i-1} < a_i $ , and $ a_i > a_{i+1} $ (once again, note the strict inequalities).

Find the permutation $ q $ that achieves the maximum score for given $ n $ and $ p $ . If there exist multiple such permutations, you can pick any of them.

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first example, $ a = [3, 6, 4, 7] $ . The array has just one local maximum (on the second position), so the score of the chosen permutation $ q $ is $ 1 $ . It can be proven that this score is optimal under the constraints.

In the last example, the resulting array $ a = [6, 6, 12, 7, 14, 7, 14, 6] $ has $ 3 $ local maximums — on the third, fifth and seventh positions.

## 样例 #1

### 输入

```
4
4
1 2 3 4
4
4 3 1 2
6
6 5 1 4 2 3
8
1 2 4 5 7 6 8 3```

### 输出

```
2 4 1 3
3 1 4 2
2 5 1 4 3 6
5 4 8 2 7 1 6 3```

# AI分析结果



## 唯一算法分类
构造

---

## 综合分析与结论

### 核心思路
所有题解均围绕构造排列 q 使得 a_i = p_i + q_i 的局部最大值最多。关键点在于局部最大值不能相邻，最优解最多有 n/2-1 个。核心构造策略为：

1. **奇偶位分治**：选择奇数或偶数位作为候选局部最大值位，通过调整 q 的值让这些位的 a_i 比相邻位大 1
2. **双重调整机制**：先构造 q 使所有 a_i = n+1，再对候选位加 1 使其成为局部最大值，最后处理重复元素
3. **贪心替换**：使用未占用的小数替换重复元素，保持排列性质

### 可视化设计要点
**动画方案**：
1. **初始构造阶段**：将所有位置染成灰色，显示 a_i = n+1
2. **候选位加亮**：将偶数位染成蓝色并加 1，显示 a_i = n+2
3. **冲突检测**：用红色闪烁标出重复的 q 值
4. **替换过程**：将奇数位的重复值排序后，用绿色箭头指向未使用的最小值替换

**复古像素风格**：
- 使用 8-bit 音效：候选位加 1 时播放 "beep"，替换时播放 "click"
- Canvas 网格显示数值变化，每步操作伴随像素块移动动画
- 自动演示模式下，算法按固定节奏执行关键步骤，背景播放 8-bit 风格循环音乐

---

## 题解清单 (≥4星)

### 1. 作者：gan1234（★★★★★）
- **核心亮点**：首创奇偶位双重调整机制，通过排序+贪心替换巧妙解决重复问题
- **代码亮点**：用 `book` 数组标记已用数值，`vector` 存储待处理位实现 O(n) 复杂度
```cpp
for(int i=2-pp;n>=i;i+=2)  // 候选位加1
if(!(i&1)&&b[i]==n)pp=1;   // 处理边界值
sort(v.begin(),v.end());    // 排序待处理位
while(book[t])t++;          // 贪心找最小可用值
```

### 2. 作者：hsy8116（★★★★）
- **核心亮点**：详细数学证明替换策略的正确性，强调被替换值必然小于原值
- **代码亮点**：使用 `pos` 数组记录原始位置，维护双指针实现高效替换
```cpp
int avb = 1; // 可用值指针
while(vis[avb]) avb++;      // 线性扫描未使用值
```

### 3. 作者：linyuhuai（★★★★）
- **核心亮点**：提出"反悔机会"概念，处理 n 出现在候选位的特殊情况
- **代码亮点**：分奇偶两组排序处理，直接倒序赋值最大化差值
```cpp
sort(b+1,b+1+cnt,cmp);      // 候选位从小到大排序
int tot=n;                  // 最大值倒序赋值
for(int i=1;i<=cnt;i++) ans[b[i].id]=tot--;
```

---

## 最优思路提炼

### 关键技巧
1. **奇偶位分离构造**：通过强制候选位（如偶数位）的 a_i 比相邻大 1，确保局部最大值
2. **双重保险机制**：
   - 初始构造 q_i = n+1 - p_i 使 a_i 全为 n+1
   - 候选位加 1 使其变为 n+2，相邻位保持 n+1
3. **贪心替换策略**：
   - 将候选位重复值排序后，用未使用的最小值按序替换
   - 保证替换后的值不会破坏局部最大值结构

### 实现范式
```python
def construct_q(p):
    n = len(p)
    q = [n+1 - pi for pi in p]  # 初始构造
    used = [False]*(n+2)
    
    # 候选位调整
    for i in even_positions:
        q[i] += 1
        used[q[i]] = True
    
    # 处理剩余位
    remain = sorted(未被使用的数)
    for i in non_candidate_positions:
        if q[i] in used:
            q[i] = remain.pop(0)
    
    return q
```

---

## 相似题目推荐

1. **CF1542C Strange Function**  
   - 构造特殊函数满足相邻元素关系
2. **Luogu P2894 Hotel**  
   - 利用奇偶性质进行区间操作
3. **Atcoder ARC108C Keep Graph Connected**  
   - 基于奇偶性质的图构造问题

---

## 可视化算法演示

**核心步骤动画**：
1. **初始构造**：所有位置显示为灰色方块，内部显示 `n+1`
2. **候选位加亮**：偶数位变为蓝色，数值更新为 `n+2`，播放 "up" 音效
3. **冲突检测**：重复值所在位置闪烁红光，显示警告标志
4. **贪心替换**：
   - 左侧面板显示可用数值队列（1,2,3...n）
   - 重复值被绿色箭头指向队列中最小的可用值
   - 替换时播放 "swap" 音效，旧值打上删除线，新值填入

**复古风格控制**：
- 背景：8-bit 星空像素画
- 音效：使用 Web Audio API 生成方波音效
- 自动演示：按 2秒/步 自动执行，可暂停调整速度
- 得分系统：每成功构造一个局部最大值位 +10 分，替换操作 -5 分

---

```javascript
// 伪代码示例：音效与动画控制
class PixelAnimator {
  constructor(canvas) {
    this.ctx = canvas.getContext('2d');
    this.sounds = { beep: new SineWave(440), click: new SquareWave(220) };
  }

  async highlightStep(pos, color) {
    this.flash(pos, color);
    this.sounds.beep.play(0.5); // 播放 500ms 提示音
    await sleep(1000);
  }

  async swapValues(pos, oldVal, newVal) {
    this.drawStrikeThrough(pos, oldVal);
    this.sounds.click.play(0.2);
    this.ctx.fillText(newVal, pos.x, pos.y);
  }
}
```

---
处理用时：84.84秒