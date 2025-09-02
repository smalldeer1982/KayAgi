# 题目信息

# Make It Ugly

## 题目描述

Let's call an array $ a $ beautiful if you can make all its elements the same by using the following operation an arbitrary number of times (possibly, zero):

- choose an index $ i $ ( $ 2 \le i \le |a| - 1 $ ) such that $ a_{i - 1} = a_{i + 1} $ , and replace $ a_i $ with $ a_{i - 1} $ .

You are given a beautiful array $ a_1, a_2, \dots, a_n $ . What is the minimum number of elements you have to remove from it in order for it to stop being beautiful? Swapping elements is prohibited. If it is impossible to do so, then output -1.

## 说明/提示

In the first testcase, it is impossible to modify the array in such a way that it stops being beautiful. An array consisting of identical numbers will remain beautiful no matter how many numbers we remove from it.

In the second testcase, you can remove the number at the index $ 5 $ , for example.

The resulting array will be $ [1, 2, 1, 2] $ . Let's check if it is beautiful. Two operations are available:

- Choose $ i = 2 $ : the array becomes $ [1, 1, 1, 2] $ . No more operations can be applied to it, and the numbers are not all the same.
- Choose $ i = 3 $ instead: the array becomes $ [1, 2, 2, 2] $ . No more operations can be applied to it either, and the numbers are still not all the same.

Thus, the array $ [1, 2, 1, 2] $ is not beautiful.

In the fourth testcase, you can remove the first three elements, for example. The resulting array $ [5, 3, 3, 3] $ is not beautiful.

## 样例 #1

### 输入

```
4
3
2 2 2
5
1 2 1 2 1
1
1
7
3 3 3 5 3 3 3```

### 输出

```
-1
1
-1
3```

# AI分析结果



**唯一算法分类**  
组合数学

---

### **题解思路、算法要点与解决难点**  
**核心思路**：破坏数组的「美丽」性质需使操作无法全相同。关键在首尾相等且中间非首元素必须孤立。  
**数学推导**：  
- 若存在两个连续的非首元素，则无法通过操作全相同。  
- 统计连续首元素的最小段长，删除该段可使相邻非首元素出现。  

**解决难点**：  
1. **边界处理**：首尾必须相等，若全相同则无解。  
2. **最优删除策略**：寻找最短连续首元素段，确保删除后形成非首元素相邻。  

**算法步骤**：  
1. 特判全相同情况，返回-1。  
2. 遍历数组，统计连续首元素段长，记录最小值。  
3. 结果即为最小段长（若存在）。  

---

### **题解评分 (≥4星)**  
1. **xhhhh36 (5星)**  
   - **亮点**：简洁高效，直接统计连续段，时间复杂度O(n)。  
   - **代码**：遍历时维护当前段长，实时更新最小值。  

2. **_ckx_ (4星)**  
   - **亮点**：存储非首元素位置，计算相邻间隔，处理首尾边界。  
   - **代码**：用vector存储非首元素索引，计算间隔取最小值。  

3. **littlebug (4星)**  
   - **亮点**：逻辑清晰，详细推导美丽条件，统计最小连续段。  
   - **代码**：遍历统计段长，特判全相同情况。  

---

### **最优思路或技巧提炼**  
1. **核心观察**：非首元素必须孤立，删除最短连续首元素段可构造相邻非首元素。  
2. **极值优化**：将问题转化为寻找连续首元素段的最小长度，时间复杂度O(n)。  
3. **边界处理**：首尾特判，全相同直接返回-1。  

---

### **同类型题或算法套路**  
1. **连续子数组极值问题**：如寻找最长/最短连续相同元素段。  
2. **模式破坏问题**：通过删除元素打破特定序列模式（如交替、递增）。  
3. **组合优化**：贪心策略选取最小操作数达成目标。  

**推荐题目**：  
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)（极值+贪心）  
3. [P3143 钻石收藏家](https://www.luogu.com.cn/problem/P3143)（连续子数组处理）  

---

### **个人心得摘录**  
- **调试踩坑**：需注意全相同数组的特判，否则会错误返回最小值0。  
- **顿悟时刻**：意识到非首元素必须孤立，转化为统计连续首元素段长。  

---

### **可视化与算法演示**  
**动画设计**：  
1. **像素风格**：用8位色块表示元素，首元素（绿色）、非首元素（红色）。  
2. **步进演示**：  
   - 高亮当前统计的连续首元素段。  
   - 显示当前最小段长，删除时播放“切割”音效。  
   - 最终展示删除段后的数组，红块相邻则播放成功音效。  
3. **交互面板**：  
   - 速度调节：控制遍历速度。  
   - 单步执行：观察每段统计过程。  

**代码片段（JS Canvas）**：  
```javascript
function drawArray(ctx, arr, minIdx) {
  arr.forEach((val, i) => {
    ctx.fillStyle = val === arr[0] ? '#00FF00' : '#FF0000';
    if (i >= minIdx.start && i <= minIdx.end) ctx.fillStyle = '#FFFF00'; // 高亮删除段
    ctx.fillRect(i * 20, 50, 18, 18);
  });
}
```

---

### **代码实现（核心逻辑）**  
```cpp
int main() {
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    
    // 特判全相同
    if (count(a.begin(), a.end(), a[0]) == n) {
      cout << -1 << endl;
      continue;
    }
    
    int ans = INT_MAX, cnt = 0;
    for (int x : a) {
      if (x == a[0]) cnt++;
      else {
        if (cnt) ans = min(ans, cnt);
        cnt = 0;
      }
    }
    if (cnt) ans = min(ans, cnt);
    cout << ans << endl;
  }
}
```

---
处理用时：69.26秒