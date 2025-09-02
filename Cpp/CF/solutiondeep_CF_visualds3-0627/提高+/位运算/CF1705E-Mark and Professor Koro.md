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



**唯一算法分类**: 线段树二分 / 珂朵莉树区间维护

---

### 题解思路与算法要点

#### 核心思路
将原问题转化为二进制数的进位问题：
- 每个数$a_i$对应二进制数的第$a_i$位加1
- 合并操作等价于二进制进位（2个1进位为高位1）
- 修改操作对应二进制数的加减运算

#### 解决难点
1. **高效处理连续进位/退位**：
   - 加法时需找到当前位后的第一个0，将该位设为1，中间位全置0
   - 减法时需找到当前位后的第一个1，将该位设为0，中间位全置1
2. **维护最大值的快速查询**：
   - 每次操作后需快速找到最高位的1

---

### 题解对比与评分

#### 评分 ≥4星题解：
1. **Chancylaser（线段树二分）** ★★★★★
   - 亮点：采用线段树二分，时间复杂度最优（O(q log M)）
   - 关键代码：
     ```cpp
     // 线段树维护二进制位
     void copy(int p,int l,int r,int val){
         if(t[p].l>=l && t[p].r<=r){
             t[p].fugai(val); return;
         }
         pushdown(p);
         if(l<=mid) copy(p<<1,l,r,val);
         if(r>mid) copy(p<<1|1,l,r,val);
         pushup(p);
     }
     ```

2. **WOL_GO（珂朵莉树）** ★★★★☆
   - 亮点：利用区间推平特性，代码简洁
   - 关键代码：
     ```cpp
     void update(int l,int r,int x){
         ite itr=split(r+1),itl=split(l);
         q.erase(itl,itr);
         q.emplace(l,r,x);
     }
     ```

3. **_cyle_King（线段树维护二进制位）** ★★★★☆
   - 亮点：完整演示线段树维护二进制过程
   - 关键代码：
     ```cpp
     void add(int p,int x){
         if(tr[p].l==tr[p].r){ tr[p].v=1; return; }
         if(x<=mid) add(p<<1,x);
         else add(p<<1|1,x);
         pushup(p);
     }
     ```

---

### 最优思路提炼
1. **二进制建模**：将合并操作转化为二进制进位
2. **区间推平优化**：用线段树/珂朵莉树处理连续位修改
3. **二分加速查找**：快速定位进位边界位置

---

### 同类型题推荐
1. P1177（快速排序） - 类似分治思想
2. P3384（线段树模板） - 区间操作基础
3. P3372（树状数组区间修改） - 高效维护前缀和

---

### 可视化算法演示方案

#### 核心动画设计
1. **二进制位展示**：
   - 用像素方块表示二进制位（1=红色，0=蓝色）
   - ![二进制位示例](https://via.placeholder.com/20x20/FF0000/0000FF?text=1)

2. **进位过程高亮**：
   - 当前操作位闪烁黄光
   - 进位路径用绿色箭头动态连接

3. **复古风格实现**：
   ```javascript
   // Canvas绘制示例
   ctx.fillStyle = '#FF0000'; // 红色方块
   ctx.fillRect(x*30, y*30, 25, 25); 
   ```

#### 交互功能
- **步进控制**：按钮控制执行单步操作
- **音效提示**：
  ```javascript
   function playBeep() {
     const osc = audioCtx.createOscillator();
     osc.frequency.value = 800; // 800Hz提示音
     osc.connect(audioCtx.destination);
     osc.start(); osc.stop(0.1);
   }
   ```

---

### 核心代码实现（线段树二分）
```cpp
struct Node {
    int l, r, sum, tag; // sum:1的数量 tag:推平标记
    bool operator[](int x) { return query(l,r,x); }
} tr[N<<2];

int find_zero(int x) { // 找x后的第一个0
    int l=x, r=MAXN, res=-1;
    while(l<=r) {
        int mid=(l+r)/2;
        if(tr.query(x,mid)==mid-x+1) l=mid+1;
        else res=mid, r=mid-1;
    }
    return res;
}

void add(int x) {
    if(tr[x]==0) tr.set(x,1);
    else {
        int pos = find_zero(x);
        tr.set(x, pos-1, 0);
        tr.set(pos,1);
    }
}
```

---

### 总结
本题解通过将问题转化为二进制模型，利用线段树二分或珂朵莉树高效处理连续区间的进位/退位操作。其中线段树实现的时间复杂度最优，而珂朵莉树代码更简洁。推荐结合复古像素动画演示进位过程，帮助理解算法核心流程。

---
处理用时：68.58秒