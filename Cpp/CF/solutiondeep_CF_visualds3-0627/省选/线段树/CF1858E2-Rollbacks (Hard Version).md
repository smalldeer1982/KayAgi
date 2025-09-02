# 题目信息

# Rollbacks (Hard Version)

## 题目描述

This is a hard version of this problem. The only difference between the versions is that you have to solve the hard version in online mode. You can make hacks only if both versions of the problem are solved.

You have an array $ a $ , which is initially empty. You need to process queries of the following types:

- + $ x $ — add the integer $ x $ to the end of the array $ a $ .
- - $ k $ — remove the last $ k $ numbers from the array $ a $ .
- ! — roll back the last active change (i.e., make the array $ a $ the way it was before the change). In this problem, only queries of the first two types (+ and -) are considered as changes.
- ? — find the number of distinct numbers in the array $ a $ .

## 说明/提示

In the first example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1,2] $ .
3. After the third query, $ a=[1,2,2] $ .
4. At the moment of the fourth query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 2 $ .
5. After the fifth query, $ a=[1,2] $ (rolled back the change + 2).
6. After the sixth query, $ a=[1,2,3] $ .
7. After the seventh query, $ a=[1] $ .
8. At the moment of the eigth query, there is only one $ 1 $ in the array $ a $ .
9. After the ninth query, $ a=[1,1] $ .
10. At the moment of the tenth query, there are only two $ 1 $ in the array $ a $ .

In the second example array $ a $ changes as follows:

1. After the first query, $ a=[1] $ .
2. After the second query, $ a=[1, 1\,000\,000] $ .
3. At the moment of the third query, there are $ 2 $ distinct intergers in the array $ a $ : $ 1 $ and $ 1\,000\,000 $ .
4. After the fourth query, $ a=[1] $ (rolled back the change + 1000000).
5. After the fifth query, $ a=[] $ (rolled back the change + 1).
6. At the moment of the sixth query, there are no integers in the array $ a $ , so the answer to this query is $ 0 $ .

## 样例 #1

### 输入

```
10
+ 1
+ 2
+ 2
?
!
+ 3
- 2
?
+ 1
?```

### 输出

```
2
1
1```

## 样例 #2

### 输入

```
6
+ 1
+ 1000000
?
!
!
?```

### 输出

```
2
0```

# AI分析结果



**唯一算法分类**：栈 + 树状数组/前缀和维护首次出现位置

---

### 题解思路与解决难点

**核心思路**：  
1. 用树状数组维护每个元素**首次出现位置**的标记  
2. 使用栈记录所有操作状态，回滚时逆向执行操作  
3. 通过动态维护数组长度实现"假删除"  

**关键实现**：  
1. 添加元素时：  
   - 维护集合记录该元素所有出现位置  
   - 若新位置是该元素的首次出现，在树状数组中标记  
2. 删除操作时：  
   - 仅修改数组逻辑长度而不实际删除数据  
3. 回滚操作时：  
   - 从栈顶取出历史状态，恢复元素位置集合  
   - 调整树状数组中的标记位  

**解决难点**：  
1. 回滚操作的原子性恢复  
2. 动态维护首次出现位置的正确性  
3. 处理嵌套回滚与操作树的关系  

---

### 题解评分 (≥4星)

1. **CSP_Sept（⭐⭐⭐⭐⭐）**  
   - 使用树状数组+集合维护首次出现位置  
   - 通过存储原值实现高效回滚  
   - 代码结构清晰，操作分类明确  

2. **Eznibuil（⭐⭐⭐⭐⭐）**  
   - 线性时间复杂度实现  
   - 通过前缀和数组替代树状数组  
   - 使用栈直接维护操作树  

3. **Register_int（⭐⭐⭐⭐）**  
   - 简洁的集合+树状数组实现  
   - 通过独立修改记录实现原子回滚  
   - 代码量少但功能完备  

---

### 最优思路与技巧

**关键技巧**：  
1. **假删除**：通过逻辑长度代替物理删除  
2. **首次出现标记**：用集合维护元素位置，树状数组标记最小位置  
3. **操作栈设计**：  
   - 对+操作存储旧值与位置  
   - 对-操作存储删除长度  
4. **线性优化**：  
   - 用数组替代集合存储位置信息  
   - 通过时间戳判断首次出现  

**代码片段**：  
```cpp
// 树状数组维护首次出现标记
void modify(int pos, int val) {
    if(old_val != -1) {
        if(*pos_set[old_val].begin() == pos) { // 清除旧标记
            update(pos, -1);
            pos_set[old_val].erase(pos); 
        }
    }
    pos_set[new_val].insert(pos);
    if(*pos_set[new_val].begin() == pos) { // 更新新标记
        update(pos, 1);
    }
}

// 回滚操作示例
void rollback() {
    auto [op_type, param] = stk.top();
    if(op_type == '+') {
        int pos = current_len;
        modify(pos, prev_val); // 恢复旧值
        current_len--;
    } else {
        current_len += param; // 恢复删除长度
    }
    stk.pop();
}
```

---

### 同类型题与推荐

**通用模式**：  
1. 动态维护集合特征（如首次出现、频次）  
2. 支持操作回滚的版本控制  

**推荐题目**：  
1. **P1972 [SDOI2009] HH的项链**（区间不同数查询）  
2. **CF707D Persistent Bookcase**（可持久化集合操作）  
3. **P4556 雨天的尾巴**（树上操作回滚）  

---

### 可视化设计

**8位像素风格演示**：  
1. **数据结构展示**：  
   - 顶部：当前数组（绿色为有效部分）  
   - 中部：树状数组标记（黄点表示首次出现）  
   - 底部：操作栈（不同颜色区分+/-/!）  

2. **动画流程**：  
   - **+操作**：新方块从右侧滑入，对应位置亮蓝光  
   - **-操作**：红色遮罩覆盖尾部元素  
   - **!操作**：播放倒带音效，栈顶元素弹出  

3. **音效设计**：  
   - 添加/删除：8-bit点击声  
   - 回滚操作：磁带倒带声  
   - 查询成功：金币收集声  

**交互控制**：  
```javascript
// 示例控制逻辑
class Visualizer {
    constructor() {
        this.speed = 1.0;
        this.autoPlay = false;
        this.highlightColor = {
            add: '#00FF88', 
            del: '#FF4444',
            rollback: '#8888FF'
        };
    }
    
    highlight(pos, opType) {
        ctx.fillStyle = this.highlightColor[opType];
        ctx.fillRect(pos*CELL_SIZE, 0, CELL_SIZE, CELL_SIZE);
    }
    
    playSound(soundType) {
        const sfx = new Audio(`sfx/${soundType}.wav`);
        sfx.playbackRate = 2.0 - this.speed;
        sfx.play();
    }
}
```

---

### 总结

该问题的核心在于通过版本控制实现操作回滚，结合集合特征维护与高效查询。树状数组+栈的设计既保证了时间复杂度，又通过逻辑长度实现了空间优化。可视化设计中加入游戏化元素可显著提升算法理解体验。

---
处理用时：71.38秒