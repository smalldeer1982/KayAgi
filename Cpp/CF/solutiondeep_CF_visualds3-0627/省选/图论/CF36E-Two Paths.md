# 题目信息

# Two Paths

## 题目背景

注意这题要加上这个：

```
freopen("input.txt","r",stdin);
freopen("output.txt","w",stdout);
```

## 题目描述

Once archaeologists found $ m $ mysterious papers, each of which had a pair of integers written on them. Ancient people were known to like writing down the indexes of the roads they walked along, as « $ a $ $ b $ » or « $ b $ $ a $ », where $ a,b $ are the indexes of two different cities joint by the road . It is also known that the mysterious papers are pages of two travel journals (those days a new journal was written for every new journey).

During one journey the traveler could walk along one and the same road several times in one or several directions but in that case he wrote a new entry for each time in his journal. Besides, the archaeologists think that the direction the traveler took on a road had no effect upon the entry: the entry that looks like « $ a $ $ b $ » could refer to the road from $ a $ to $ b $ as well as to the road from $ b $ to $ a $ .

The archaeologists want to put the pages in the right order and reconstruct the two travel paths but unfortunately, they are bad at programming. That’s where you come in. Go help them!

## 样例 #1

### 输入

```
2
4 5
4 3
```

### 输出

```
1
2 
1
1
```

## 样例 #2

### 输入

```
1
1 2
```

### 输出

```
-1
```

# AI分析结果



# Two Paths 题解分析

**唯一算法分类**: 欧拉路径/回路

---

## 算法核心思路与难点分析

### 核心思路
1. **奇点数量判定**  
   - 整个图的奇点数量只能是 0/2（单路径）或 4（双路径）
   - 连通块数 ≤ 2，否则无解

2. **关键处理场景**  
   - **单连通块**  
     - 0/2 奇点：直接求欧拉路径后拆分为两条
     - 4 奇点：添加虚边构建欧拉回路，再分割路径
   - **双连通块**  
     每个连通块必须是欧拉图或半欧拉图

3. **虚边技巧**  
   当存在4个奇点时，任选两个不相邻的奇点添加虚边，形成可分割的欧拉回路

---

## 题解评分（≥4星）

### 1. chenxia25（⭐⭐⭐⭐⭐）
- **亮点**：  
  - 提出虚拟边思想，将4奇点问题转化为可分割的欧拉回路
  - 深入分析连通性对路径分割的影响
- **代码实现**：  
  使用邻接表存储边，通过DFS找欧拉路径，最后处理虚边分割

### 2. Rainybunny（⭐⭐⭐⭐）
- **亮点**：  
  - 分情况讨论清晰，提供大量Hack测试数据
  - 独立处理每个连通块的欧拉路径
- **代码实现**：  
  采用双栈结构存储路径，通过奇点分布判断分割点

### 3. Chillturtle（⭐⭐⭐⭐）
- **亮点**：  
  - 使用虚拟边法处理4奇点情况
  - 提供可视化示意图辅助理解
- **代码实现**：  
  通过标记数组跟踪已用边，实现路径分离

---

## 最优思路提炼

### 关键技巧
1. **虚边构造法**  
   ```python
   # 伪代码示例
   if 奇点数 == 4:
       add_edge(奇点A, 奇点B)  # 添加虚边
       构建欧拉回路
       在虚边位置分割路径
   ```
2. **路径分割策略**  
   - 单路径拆解：取第一条边为路径1，剩余为路径2
   - 虚边分割：遍历欧拉回路找到虚边位置进行切割

---

## 同类型题目推荐
1. [P1333] 欧拉回路
2. [P2731] 骑马修栅栏
3. [P3520] 最短欧拉路径

---

## 可视化设计

### 核心算法演示
**动画步骤**：
1. **初始状态**  
   - 红色标记奇点（4个）
   - 蓝色显示原始边

2. **添加虚边**  
   - 黄色虚线连接两个奇点
   - 播放"连接音效"（短促电子音）

3. **欧拉回路构建**  
   - 绿色高亮当前遍历边
   - 实时显示路径栈的压入过程

4. **路径分割**  
   - 虚边位置触发红色闪烁
   - 分割为两条紫色和橙色路径

**复古像素风格**：
```javascript
// Canvas绘制示例
ctx.fillStyle = '#8B00FF'; // 紫色路径
ctx.fillRect(x*16, y*16, 16, 16); 
ctx.strokeStyle = '#FFFF00'; // 虚边
ctx.setLineDash([4,4]);
```

**音效设计**：
- 边遍历：8-bit "哔"声（频率随边序号变化）
- 虚边添加：低音鼓点
- 成功分割：胜利小号音效

---

## 核心代码片段

### 虚边处理（Rainybunny版）
```cpp
// 添加虚边
if(奇点数 == 4){
    add_edge(odd[2], odd[3], m+1);
    dfs(odd[0], path);
    // 查找虚边分割点
    for(int i=0; i<path.size(); i++){
        if(path[i] == m+1){
            split_pos = i;
            break;
        }
    }
    // 输出分割后的路径
    print(path.substr(0, split_pos));
    print(path.substr(split_pos+1));
}
```

### 欧拉路径查找（Chillturtle版）
```cpp
void dfs(int u, vector<int>& path){
    for(int &i=head[u]; i; ){
        int v = edges[i].to, id = edges[i].id;
        i = edges[i].next; // 动态删除已访问边
        if(vis[id]) continue;
        vis[id] = true;
        dfs(v, path);
        path.push_back(id);
    }
}
```

---

## 调试经验摘录
> "在菊花图测试用例中发现虚边分割位置错误，最终通过逆序遍历路径栈修正分割逻辑" —— Chillturtle  
> "重边处理必须用邻接表而非邻接矩阵，否则会遗漏多次访问" —— chenxia25

---

通过上述分析，本题的核心在于灵活运用欧拉图性质和虚边技巧，结合清晰的分类讨论思维，即可高效解决复杂路径覆盖问题。

---
处理用时：59.77秒