# 题目信息

# [ABC358D] Souvenirs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc358/tasks/abc358_d

AtCoder Land のお土産屋に $ N $ 個の箱が売られています。

箱には $ 1,\ 2,\ \ldots,\ N $ の番号が付いており、箱 $ i $ の価格は $ A_i $ 円であり、$ A_i $ 個のお菓子が入っています。

高橋君は $ N $ 個の箱のうち $ M $ 個の箱を選んで買って帰り、$ 1,\ 2,\ \ldots,\ M $ の名前が付いた $ M $ 人の人に $ 1 $ つずつ箱を渡そうとしています。

ただし、高橋君は以下の条件を満たすことができるように箱を買いたいです。

- 各 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、人 $ i $ には $ B_i $ 個以上のお菓子が入った箱を渡す
 
$ 1 $ 人に $ 2 $ 個以上の箱を渡すことや同じ箱を複数人に渡すことはできないことに注意してください。

適切に箱を $ M $ 個買うことで条件を満たすことができるか判定し、条件を満たすことができる場合は高橋君が支払う金額の合計の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ M\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ 10^9 $
- 入力される値はすべて整数
 
### Sample Explanation 1

高橋君は箱 $ 1,\ 4 $ を買い、箱 $ 1 $ を人 $ 1 $、箱 $ 4 $ を人 $ 2 $ に渡すことで条件を満たすことができます。 このとき高橋君が支払う金額の合計は $ 7 $ 円であり、支払う金額が $ 7 $ 円未満のときは条件を満たすことはできないため、$ 7 $ を出力します。

## 样例 #1

### 输入

```
4 2

3 4 5 4

1 4```

### 输出

```
7```

## 样例 #2

### 输入

```
3 3

1 1 1

1000000000 1000000000 1000000000```

### 输出

```
-1```

## 样例 #3

### 输入

```
7 3

2 6 8 9 5 1 11

3 5 7```

### 输出

```
19```

# AI分析结果



## 唯一算法分类
贪心

---

## 综合分析与结论

### 核心思路
题目要求选择 M 个盒子满足每个人对糖果数量的最低要求，并使总花费最小。通过以下步骤实现：
1. **排序**：将盒子糖果数 A 和需求 B 分别排序
2. **贪心匹配**：对每个 B_i 选择最小的满足条件的 A_j，保证全局最优
3. **线性扫描**：利用双指针或二分查找高效匹配，避免重复选择

### 解决难点
- **动态可用性维护**：每个盒子只能选一次，需高效标记已选元素
- **时间复杂度控制**：需 O(N log N) 的排序 + O(N) 的线性扫描

### 可视化设计
**双指针动画方案**：
- **颜色标记**：已处理的 B_i 显示为绿色，当前 B_i 高亮为黄色
- **指针移动**：A 数组指针用红色箭头标识，实时显示移动过程
- **匹配高亮**：成功匹配时对应的 A_j 闪烁金色边框
- **进度面板**：显示已选盒子数、当前总价、剩余可用盒子数

**复古像素风格实现**：
```javascript
// Canvas 初始化（像素风格）
const canvas = document.getElementById('pixel-canvas');
ctx = canvas.getContext('2d');
ctx.imageSmoothingEnabled = false; // 关闭抗锯齿

// 绘制排序后的数组（像素块表示）
function drawArray(arr, x, y, highlightIdx) {
  arr.forEach((val, idx) => {
    ctx.fillStyle = (idx === highlightIdx) ? '#FFD700' : '#4A90E2';
    ctx.fillRect(x + idx*20, y, 18, 18); // 每个元素占20x20像素
    // 绘制数值（8x8 像素字体）
    ctx.font = '8px "Press Start 2P"';
    ctx.fillStyle = '#000';
    ctx.fillText(val, x + idx*20 + 2, y + 12);
  });
}

// 音效触发（Web Audio API）
function playSound(freq) {
  const oscillator = audioCtx.createOscillator();
  oscillator.type = 'square';
  oscillator.frequency.setValueAtTime(freq, audioCtx.currentTime);
  oscillator.connect(audioCtx.destination);
  oscillator.start();
  oscillator.stop(audioCtx.currentTime + 0.1);
}
```

---

## 题解清单（≥4星）

### 1. 双指针法（Barryb，5星）
**亮点**：时间复杂度最优（O(N log N)），代码极简
```cpp
sort(a+1,a+n+1); sort(b+1,b+m+1);
for(int i=1; i<=m; i++) {
    while(now<=n && a[now]<b[i]) now++;
    if(now<=n) sum+=a[now++];
    else return cout<<-1,0;
}
```

### 2. Multiset 解法（stripe_python，4星）
**亮点**：利用 STL 特性代码简洁，逻辑直观
```cpp
multiset<int> st;
for(int i=1; i<=n; i++) st.insert(a[i]);
for(int i=1; i<=m; i++) {
    auto it = st.lower_bound(b[i]);
    if(it == st.end()) return cout<<-1, 0;
    tot += *it;
    st.erase(it);
}
```

### 3. 二分查找法（luobotianle，4星）
**亮点**：显式维护指针，适合理解二分原理
```cpp
sort(a+1,a+1+n); sort(b+1,b+m+1);
int last=0;
for(int i=1; i<=m; i++) {
    int pos = lower_bound(a+last+1,a+1+n,b[i])-a;
    if(pos>n) return cout<<-1,0;
    ans += a[pos];
    last = pos;
}
```

---

## 最优思路提炼

### 关键技巧
- **排序预处理**：将问题转化为有序序列的匹配问题
- **单调性利用**：B 的递增性保证指针只需单向移动
- **最小可用值选择**：通过线性扫描或二分快速定位

### 思维模式
**早停剪枝**：当剩余盒子数 < 剩余人数时立即返回 -1  
**资源池维护**：通过指针或集合动态跟踪可用盒子

---

## 类似题目推荐
1. P1090 [NOIP2004 提高组] 合并果子（贪心+优先队列）
2. P1209 [USACO1.3]修理牛棚（区间覆盖与贪心选择）
3. P4995 跳跳！（排序后交替取最大最小值）

---

## 个人心得摘录
> "十年 OI 一场空，不开 long long 见祖宗" —— 多个题解强调数据范围  
> "为什么赛时用 lower_bound 寄了？" —— 未维护可用指针导致重复选择

---

## 可视化完整代码（核心片段）
```javascript
// 自动演示控制
let aPtr = 0, bPtr = 0, totalCost = 0;
function step() {
  if(bPtr >= m) { // 完成
    playSound(880); // 成功音效（A5）
    return;
  }
  
  // 移动A指针寻找匹配
  while(aPtr < n && sortedA[aPtr] < sortedB[bPtr]) {
    drawHighlight(aPtr, 'red'); // 红色高亮不满足的元素
    aPtr++;
  }

  if(aPtr >= n) { // 无解
    playSound(220); // 失败音效（A3）
    showGameOver();
    return;
  }

  // 成功匹配
  totalCost += sortedA[aPtr];
  drawHighlight(aPtr, 'gold'); // 金色高亮选中元素
  playSound(660); // 匹配音效（E5）
  aPtr++;
  bPtr++;
  
  // 更新UI
  updateCostDisplay(totalCost);
  requestAnimationFrame(step);
}
```

---
处理用时：85.83秒