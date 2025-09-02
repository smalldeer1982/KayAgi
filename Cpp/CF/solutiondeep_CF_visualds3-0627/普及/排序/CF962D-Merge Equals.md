# 题目信息

# Merge Equals

## 题目描述

You are given an array of positive integers. While there are at least two equal elements, we will perform the following operation. We choose the smallest value $ x $ that occurs in the array $ 2 $ or more times. Take the first two occurrences of $ x $ in this array (the two leftmost occurrences). Remove the left of these two occurrences, and the right one is replaced by the sum of this two values (that is, $ 2 \cdot x $ ).

Determine how the array will look after described operations are performed.

For example, consider the given array looks like $ [3, 4, 1, 2, 2, 1, 1] $ . It will be changed in the following way: $ [3, 4, 1, 2, 2, 1, 1]~\rightarrow~[3, 4, 2, 2, 2, 1]~\rightarrow~[3, 4, 4, 2, 1]~\rightarrow~[3, 8, 2, 1] $ .

If the given array is look like $ [1, 1, 3, 1, 1] $ it will be changed in the following way: $ [1, 1, 3, 1, 1]~\rightarrow~[2, 3, 1, 1]~\rightarrow~[2, 3, 2]~\rightarrow~[3, 4] $ .

## 说明/提示

The first two examples were considered in the statement.

In the third example all integers in the given array are distinct, so it will not change.

## 样例 #1

### 输入

```
7
3 4 1 2 2 1 1
```

### 输出

```
4
3 8 2 1 
```

## 样例 #2

### 输入

```
5
1 1 3 1 1
```

### 输出

```
2
3 4 
```

## 样例 #3

### 输入

```
5
10 40 20 50 30
```

### 输出

```
5
10 40 20 50 30 
```

# AI分析结果



### **唯一算法分类**  
优先队列（堆）模拟

---

### **综合分析与结论**  

**核心思路**：  
所有题解均围绕优先队列（堆）维护元素值-位置对，每次处理最小的重复值。关键点包括：  
1. **堆的排序规则**：以数值为第一关键字，位置为第二关键字（保证选最左的两个重复值）  
2. **合并逻辑**：取堆顶两个元素，若相同则合并后重新入堆，不同则保留第一个  
3. **结果顺序维护**：最终按原始位置排序输出  

**实现难点**：  
1. 维护合并后的新元素的位置顺序  
2. 处理多次合并后可能产生的更高数值的重复项  
3. 避免整数溢出（需使用long long）  

**可视化设计要点**：  
1. **动画方案**：  
   - 左侧显示优先队列结构，用堆的树状图展示当前元素  
   - 右侧显示数组动态变化过程，高亮当前被取出的两个元素  
   - 合并操作时显示`x → 2x`的放大动画  
2. **复古像素风格**：  
   - 使用8位绿色调色板（类似Game Boy）  
   - 堆元素用16x16像素块表示，数值用8x8点阵字体  
   - 合并时播放FC风格的“升级”音效（持续音阶上升）  
3. **交互功能**：  
   - 步进控制：空格键单步执行  
   - 速度调节：方向键控制动画速度（1x/2x/0.5x）  
   - 显示模式：F1切换传统视图/像素视图  

---

### **题解清单（≥4星）**  

1. **Bitter_Tea（4.5星）**  
   - 亮点：简洁的堆操作+结果二次排序  
   - 核心代码：  
     ```cpp
     priority_queue<D> q; // 自定义排序的堆
     while(q.size()){
         fir = q.top(); q.pop();
         if(q.empty()) break;
         sec = q.top();
         if(fir.a == sec.a){ // 合并逻辑
             q.pop();
             q.push({fir.a*2, sec.id}); // 保留右侧位置
         }
     }
     ```

2. **Milmon（5星）**  
   - 亮点：最简洁的STL应用，双关键字堆排序  
   - 关键优化：直接使用`pair<值,位置>`的堆  
   ```cpp
   priority_queue<int, vector<int>, Cmp> Q; // 自定义比较器
   while(Q.size()>=2){
       int x=Q.top(); Q.pop();
       int y=Q.top(); Q.pop();
       if(a[x]==a[y]) a[y]<<=1, Q.push(y);
       else ans.push(x), Q.push(y);
   }
   ```

3. **chenxia25方法1（4.5星）**  
   - 亮点：分离结果队列，避免最终排序  
   ```cpp
   priority_queue<pair<int,int>, vector<...>, cmp> q; // 主处理堆
   priority_queue<pair<int,int>, vector<...>, cmp0> q0; // 结果堆（按位置排序）
   ```

---

### **最优思路提炼**  

**关键技巧**：  
1. **双关键字堆排序**：  
   ```cpp
   struct Cmp {
       bool operator()(int x, int y) {
           if(a[x] != a[y]) return a[x] > a[y]; // 值升序
           return x > y; // 位置升序（保证取最左）
       }
   };
   ```  
2. **位置继承**：合并后保留右侧元素的位置，维持后续操作的相对顺序  
3. **结果延迟处理**：合并失败的元素直接存入结果队列，避免重复入堆  

---

### **相似题目推荐**  
1. P1090 [NOIP2004]合并果子（优先队列基础）  
2. P1886 滑动窗口（双关键字处理）  
3. CF862B Mahmoud and Ehab and the bipartiteness（贪心+位置维护）

---

### **可视化代码片段**  

```javascript
// 伪代码展示核心动画逻辑
class MergeAnimation {
  constructor(arr) {
    this.heap = new PriorityQueue((a,b) => a.val - b.val || a.pos - b.pos);
    this.heap.elements = arr.map((v,i) => ({val:v, pos:i})); 
  }

  step() {
    const [a, b] = this.heap.popTwo();
    if(a.val === b.val) {
      this.mergeEffect(a, b); // 播放合并动画
      this.heap.push({val:a.val*2, pos:b.pos});
    } else {
      this.result.push(a); // 加入结果数组
      this.heap.push(b);
    }
  }

  mergeEffect(a, b) {
    ctx.fillStyle = "#FF5555"; // 高亮红色
    drawElement(a.pos); 
    animate(b.pos, a.val*2); // 数值放大动画
  }
}
```

---
处理用时：62.00秒