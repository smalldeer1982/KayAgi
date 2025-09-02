# 题目信息

# Mark and Professor Koro

## 题目描述

After watching a certain anime before going to sleep, Mark dreams of standing in an old classroom with a blackboard that has a sequence of $ n $ positive integers $ a_1, a_2,\dots,a_n $ on it.

Then, professor Koro comes in. He can perform the following operation:

- select an integer $ x $ that appears at least $ 2 $ times on the board,
- erase those $ 2 $ appearances, and
- write $ x+1 $ on the board.

Professor Koro then asks Mark the question, "what is the maximum possible number that could appear on the board after some operations?"

Mark quickly solves this question, but he is still slower than professor Koro. Thus, professor Koro decides to give Mark additional challenges. He will update the initial sequence of integers $ q $ times. Each time, he will choose positive integers $ k $ and $ l $ , then change $ a_k $ to $ l $ . After each update, he will ask Mark the same question again.

Help Mark answer these questions faster than Professor Koro!

Note that the updates are persistent. Changes made to the sequence $ a $ will apply when processing future updates.

## 说明/提示

In the first example test, the program must proceed through $ 4 $ updates.

The sequence after the first update is $ [2,3,2,4,5] $ . One sequence of operations that achieves the number $ 6 $ the following.

- Initially, the blackboard has numbers $ [2,3,2,4,5] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,5,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [4,5,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [5,\color{red}{5}] $ .
- Erase two copies of $ 5 $ and write $ 6 $ , yielding $ [\color{red}{6}] $ .

Then, in the second update, the array is changed to $ [2,3,2,4,3] $ . This time, Mark cannot achieve $ 6 $ . However, one sequence that Mark can use to achieve $ 5 $ is shown below.

- Initially, the blackboard has $ [2,3,2,4,3] $ .
- Erase two copies of $ 2 $ and write $ 3 $ , yielding $ [3,4,3,\color{red}{3}] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [3,4,\color{red}{4}] $ .
- Erase two copies of $ 4 $ and write $ 5 $ , yielding $ [3,\color{red}{5}] $ .

In the third update, the array is changed to $ [2,3,2,1,3] $ . One way to achieve $ 4 $ is shown below.

- Initially, the blackboard has $ [2,3,2,1,3] $ .
- Erase two copies of $ 3 $ and write $ 4 $ , yielding $ [2,2,1,\color{red}{4}] $ .

## 样例 #1

### 输入

```
5 4
2 2 2 4 5
2 3
5 3
4 1
1 4```

### 输出

```
6
5
4
5```

## 样例 #2

### 输入

```
2 1
200000 1
2 200000```

### 输出

```
200001```

# AI分析结果



# 算法分类  
**二进制进位模拟 + 线段树/珂朵莉树**

---

## 综合分析与结论  
### 核心思路与难点  
将操作视为二进制进位过程：  
1. **合并操作**等价于二进制加法（2^x + 2^x = 2^{x+1}）  
2. **修改操作**等价于先减后加特定二进制位  
3. **最大数**即二进制数的最高有效位  

**核心难点**：  
- **高效处理进位/退位**：连续进位可能导致O(n)时间损耗  
- **动态维护二进制位状态**：需支持快速区间修改与极值查询  

### 关键数据结构对比  
| 方法            | 数据结构   | 时间复杂度  | 实现复杂度 |  
|-----------------|------------|-------------|------------|  
| 线段树          | 线段树     | O(q log M)  | 高         |  
| 珂朵莉树        | set/map    | O(q log M)  | 中         |  
| 暴力模拟        | bitset     | O(q*M/w)    | 低         |  

---

## 题解评分（≥4星）  
### [Chancylaser] 线段树二分（4.5★）  
- **亮点**：  
  - 通过线段树维护**连续1区间**，巧妙处理进位边界  
  - `getpos`函数实现快速区间二分查找  
  - 逻辑模块化（增删分离）  
- **代码**：  
  ```cpp  
  // 线段树维护区间1的个数  
  void copy(int p,int l,int r,int val){  
      if(t[p].l>=l && t[p].r<=r) t[p].fugai(val);  
      else{  
          pushdown(p);  
          if(l<=mid) copy(p<<1,l,r,val);  
          if(r>mid) copy(p<<1|1,l,r,val);  
          pushup(p);  
      }  
  }  
  ```

### [WOL_GO] 珂朵莉树（4.2★）  
- **亮点**：  
  - 用set维护连续1区间，天然适配进位操作  
  - `split`函数实现区间切割，`assign`快速推平  
  - 代码简洁（约50行核心逻辑）  
- **代码**：  
  ```cpp  
  void add(int p){  
      auto itr=split(p+1), itl=split(p);  
      if(itl->v==0) itl->v=1;  
      else{  
          int l=itl->l;  
          for(;itl->v==1;itl++);  
          update(l, itl->l-1, 0);  
          split(itl->l)->v=1;  
      }  
  }  
  ```

### [__stick] 压位高精（4.0★）  
- **亮点**：  
  - __int128压位实现暴力进位  
  - 代码短小适合竞赛快速编码  
- **缺陷**：  
  - 大常数导致部分测试点TLE  

---

## 最优思路提炼  
1. **二进制视角**：将数列视为二进制数，合并即进位  
2. **区间推平**：进位/退位操作本质是区间0/1赋值  
3. **极值查找**：通过二分或线段树特性快速定位首个0/1位  

---

## 同类题目推荐  
1. **CF242E** - 区间异或与求和（线段树位运算）  
2. **P3369** - 动态开点线段树（洛谷模板）  
3. **CF817F** - 区间翻转与极值查询（珂朵莉树经典）  

---

## 可视化设计  
### 算法演示方案  
1. **Canvas动画**：  
   - **数据结构**：网格化显示二进制位，红色表示1，蓝色表示0  
   - **操作高亮**：  
     - 修改位：黄色闪烁  
     - 进位区间：绿色波浪线  
   - **示例流程**：  
     ```  
     初始：2 2 2 4 5 → 二进制位[2:3,4:1,5:1]  
     合并2→3：位2清零，位3置1 → 新位[3:1,4:1,5:1]  
     ```  

2. **复古像素风格**：  
   - **调色板**：8位红/蓝/黄/绿色系  
   - **音效**：  
     - 进位成功：NES风格上升音阶  
     - 区间推平：8位爆炸音效  

3. **交互控制**：  
   ```javascript  
   class Viz {  
       constructor() {  
           this.speed = 1; // 播放速度  
           this.bitGrid = new BitGrid(20, 200); // 20行x200列  
       }  
       highlightBits(start, end, color) {  
           // Canvas绘制高亮区间  
       }  
       playStep(ops) {  
           // 根据操作队列逐步执行动画  
       }  
   }  
   ```

---

## 关键代码（线段树实现）  
```cpp  
int getmax(int p) { // 查询最高有效位  
    if(t[p].l == t[p].r) return t[p].l;  
    pushdown(p);  
    if(t[p<<1|1].sum) return getmax(p<<1|1);  
    else return getmax(p<<1);  
}  

void processUpdate(int old, int newVal) {  
    // 删除旧值  
    if(querySum(old, old) == 1)  
        updateRange(old, old, 0);  
    else {  
        int pos = findNextOne(old);  
        updateRange(old, pos-1, 1);  
        updateRange(pos, pos, 0);  
    }  
    // 添加新值同理  
}  
```

---

通过上述分析与可视化设计，学习者可深入理解二进制进位的本质，并掌握线段树/珂朵莉树在动态区间问题中的核心应用技巧。

---
处理用时：68.84秒