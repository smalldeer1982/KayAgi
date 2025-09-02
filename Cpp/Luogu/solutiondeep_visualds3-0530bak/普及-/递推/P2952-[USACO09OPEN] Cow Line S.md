# 题目信息

# [USACO09OPEN] Cow Line S

## 题目描述

Farmer John（以下简称 FJ）的 $N$ 头奶牛（用 $1 \dots N$ 编号）在直线上排队。一开始，这条线上没有任何奶牛，随着时间的推移，奶牛们会一个接一个地站到队伍的左边或右边。又过了一会儿，某些奶牛会从队伍里离开，去吃自己最喜欢的草料。

FJ 无法跟踪每一头奶牛，于是，他想让你来帮助他。

奶牛以 $1 \dots N$ 的顺序排队，并且离开的奶牛不会再次回来。数据将会给出 $S$（$1 \le S \le 100000$） 条指令，各占一行，分两种：

- $A$ 头奶牛加入了队列（还有一个参数，表示从左加入还是从右加入）；
- $K$ 头奶牛从左边或者右边离开了队列（还有两个参数，分别表示从左离开还是从右离开和离开多少头奶牛）。

输入的命令一定是可以执行的。

所有的操作结束后，你的程序应该以从左到右的顺序输出这个奶牛队列。数据保证最后的队列不空。

## 样例 #1

### 输入

```
10 
A L 
A L 
A R 
A L 
D R 2 
A R 
A R 
D L 1 
A L 
A R 
```

### 输出

```
7 
2 
5 
6 
8 
```

# AI分析结果



# 算法分类  
**双端队列 (Deque)**

---

# 题解思路与核心难点  

## **核心逻辑**  
所有操作均在队列两端进行：  
- **插入操作**：从左/右插入递增的编号  
- **删除操作**：从左/右删除指定数量元素  

## **关键实现对比**  
| 方法        | 数据结构       | 时间复杂度 | 空间复杂度 | 实现难度 |  
|------------|---------------|----------|----------|---------|  
| STL Deque  | 双端队列       | O(S)     | O(N)     | ⭐       |  
| 数组模拟   | 大数组 + 指针 | O(S)     | O(M)     | ⭐⭐      |  
| 双向链表   | 链表节点       | O(S)     | O(N)     | ⭐⭐⭐     |  

**核心难点**：  
1. **高效处理两端操作**：需避免中间元素的频繁移动  
2. **动态维护队列范围**：删除操作需快速更新队列边界  

---

# 题解评分 (≥4星)  

| 作者       | 评分 | 核心亮点 |  
|------------|------|----------|  
| Sooke      | ⭐⭐⭐⭐⭐ | 极简代码，STL Deque 完美匹配需求 |  
| mahao2002  | ⭐⭐⭐⭐  | 数组模拟高效，无需动态内存管理 |  
| Porsche    | ⭐⭐⭐⭐  | 大数组中间初始化避免越界，指针操作直观 |  

---

# 最优思路提炼  

## **关键技巧**  
1. **STL Deque 模板化操作**  
   ```cpp  
   deque<int> Q;  
   Q.push_front(c++);  // 左端插入  
   Q.pop_back();       // 右端删除  
   ```  
2. **数组模拟滑动窗口**  
   ```cpp  
   int a[200000], l=100000, r=99999;  
   a[--l] = val;  // 左插  
   r -= k;        // 右删k元素  
   ```  

---

# 类似题目推荐  
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886) - 双端队列维护极值  
2. [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440) - 队列头尾动态更新  
3. [P2627 修剪草坪](https://www.luogu.com.cn/problem/P2627) - 前缀和+单调队列优化  

---

# 可视化算法演示  

## **动画设计**  
![Deque操作动画](https://i.imgur.com/1JjKZ7c.gif)  
1. **像素风格**：  
   - 队列元素显示为16x16像素方块（红→蓝渐变表示插入顺序）  
   - 操作方向用箭头高亮（左插黄色箭头，右删红色箭头）  
2. **关键帧触发**：  
   ```javascript  
   // 伪代码示例  
   function animatePushFront(val) {  
     ctx.fillStyle = "#FFD700"; // 金色高亮  
     drawArrow(leftEdgeX, "left");  
     playSound("blip.wav");  
     addBlock(val, "left");  
   }  
   ```  
3. **音效设计**：  
   - 插入操作：8-bit "blip" 音效  
   - 删除操作：短促 "pop" 音效  

---

# 核心代码实现  

## **STL Deque版**  
```cpp  
#include <deque>  
using namespace std;  

deque<int> q;  
int main() {  
    int S, c=1;  
    cin >> S;  
    while(S--){  
        char op, dir;  
        cin >> op >> dir;  
        if(op=='A'){  
            dir=='L' ? q.push_front(c++) : q.push_back(c++);  
        } else {  
            int k; cin >> k;  
            dir=='L' ? q.erase(q.begin(), q.begin()+k)  
                     : q.erase(q.end()-k, q.end());  
        }  
    }  
    for(int x:q) cout << x << "\n";  
}  
```  

## **数组模拟版**  
```cpp  
int a[200001], l=100000, r=100000;  
int main() {  
    int S, cnt=1;  
    cin >> S;  
    while(S--){  
        char op, dir;  
        cin >> op >> dir;  
        if(op=='A'){  
            if(dir=='L') a[--l] = cnt++;  
            else a[r++] = cnt++;  
        } else {  
            int k; cin >> k;  
            dir=='L' ? l += k : r -= k;  
        }  
    }  
    for(int i=l; i<r; i++) cout << a[i] << "\n";  
}  
```  

---

# 调试与优化技巧  
1. **边界测试**：连续删除全部元素后再插入  
2. **内存预分配**：数组模拟时初始位置设在中间避免越界  
3. **迭代器失效**：STL版本避免在循环中直接使用`erase(q.begin()+i)`

---
处理用时：73.57秒