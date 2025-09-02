# 题目信息

# Jamie and To-do List

## 题目描述

“为什么我要完成这么多作业？”

Jamie 正忙于他的学校生活。

他开始忘记他必须做的作业。他决定把这些事情写在 To-Do List 上。

他为他的每项任务分配一个价值优先级(较低的价值意味着更重要)，这样他就可以决定他需要花更多的时间在哪个任务上。

几天后，Jamie 发现名单太大了，他甚至不能自己管理名单！由于您是 Jamie 的好朋友，请帮助他编写一个程序来支持待办事项列表中的以下操作:

`set ai xi`：设置任务 $a_i$ 的优先级为 $x_i$，如果该列表中没有出现则加入该任务。

`remove a_i`：删除该任务。

`query a_i`：求优先级比 $a_i$ 小的任务个数，如果该任务已被删除则输出 $-1$。

`undo sum`：删除此次操作之前的 $sum$ 次操作。

在 Day 0，To-Do List 为空，在接下来 $Q$ 个日子内，Jamie 都会在四个操作中任选一个执行。

对于每个询问操作，输出对应的答案。

## 说明/提示

保证输入的字符串由小写字符构成，设其长度为 $len$，则 $1\leq len\leq15$。

$1\le Q\le10^5$，并且保证对于所有的 undo 操作，$sum$ 不超过该天之前的天数。

## 样例 #1

### 输入

```
8
set chemlabreport 1
set physicsexercise 2
set chinesemockexam 3
query physicsexercise
query chinesemockexam
remove physicsexercise
query physicsexercise
query chinesemockexam
```

### 输出

```
1
2
-1
1
```

## 样例 #2

### 输入

```
8
set physicsexercise 2
set chinesemockexam 3
set physicsexercise 1
query physicsexercise
query chinesemockexam
undo 4
query physicsexercise
query chinesemockexam
```

### 输出

```
0
1
0
-1
```

## 样例 #3

### 输入

```
5
query economicsessay
remove economicsessay
query economicsessay
undo 2
query economicsessay
```

### 输出

```
-1
-1
-1
```

## 样例 #4

### 输入

```
5
set economicsessay 1
remove economicsessay
undo 1
undo 1
query economicsessay
```

### 输出

```
-1
```

# AI分析结果



---

## 唯一算法分类  
**可持久化线段树（主席树）**

---

## 综合分析与结论  
### 核心思路与难点  
题目要求维护带撤销操作的任务优先级系统。所有操作需要支持回退到任意历史版本，因此必须使用可持久化数据结构。通过两棵可持久化线段树实现：  
1. **任务优先级树**：维护每个任务当前的优先级（键为任务名哈希后的整数，值为优先级）  
2. **权值树**：维护所有优先级的出现次数，用于快速查询比某优先级小的任务数量  

**撤销操作**通过保存每个操作后的线段树根节点实现版本回退，例如 `undo d` 将当前版本指针设置为 `i-d-1` 对应的根节点。  

**关键难点**在于两棵树的同步更新，例如修改任务优先级时需要先在权值树中删除旧值，再插入新值。  

### 可视化设计要点  
1. **版本树展示**：用时间轴显示操作序列，每次操作生成新版本，撤销时高亮回退的版本  
2. **双树同步**：左右分屏分别展示任务优先级树和权值树，修改时动态显示节点的复制与更新  
3. **像素化动画**：  
   - **操作高亮**：执行 `set/remove` 时，任务节点闪烁红色（删除旧值）和绿色（插入新值）  
   - **权值更新**：权值树的对应区间以黄色脉冲显示计数变化  
   - **撤销特效**：版本回退时屏幕短暂闪烁蓝色边框，并播放复古音效  
4. **音效设计**：  
   - `set` 操作：短促“滴”声  
   - `undo` 操作：类似马里奥吃金币的清脆音效  
   - 查询结果正确时：上升音阶，错误时：低沉蜂鸣  

---

## 题解清单（≥4星）  
1. **Karry5307（5星）**  
   - 双可持久化线段树结构清晰，代码复用高  
   - 使用 `map` 处理字符串哈希，空间控制合理  
   - 特判优先级为1的情况避免死递归  

2. **chenzida（4星）**  
   - 代码简洁，动态开点处理高效  
   - 注释明确，直接维护两棵树的根节点  

3. **xunzhen（4星）**  
   - 结构体封装线段树，可读性强  
   - 处理删除操作时显式覆盖旧版本  

---

## 最优思路与代码实现  
### 双树同步更新逻辑  
```cpp  
// 设置操作核心代码  
if (op == "set") {  
    int old_priority = query_priority_tree(current_version, task_id);  
    if (old_priority != 0) {  
        // 在权值树中删除旧值  
        new_value_tree = update_value_tree(old_version, old_priority, -1);  
    }  
    // 在权值树中插入新值  
    new_value_tree = update_value_tree(new_value_tree, new_priority, +1);  
    // 更新任务优先级树  
    new_priority_tree = update_priority_tree(old_priority_version, task_id, new_priority);  
}  
```  

### 完整代码（Karry5307精简版）  
```cpp  
#include<bits/stdc++.h>  
using namespace std;  
const int MAXN=2e5+51;  
map<string,int> mp;  
int rt1[MAXN],rt2[MAXN],cnt; // 两棵线段树的根数组  

struct Node { int lc,rc,sum; } tree[MAXN*40];  

void update(int &now,int l,int r,int pos,int val) {  
    tree[++cnt] = tree[now]; now = cnt;  
    if(l == r) { tree[now].sum += val; return; }  
    int mid = (l+r)>>1;  
    if(pos <= mid) update(tree[now].lc,l,mid,pos,val);  
    else update(tree[now].rc,mid+1,r,pos,val);  
    tree[now].sum = tree[tree[now].lc].sum + tree[tree[now].rc].sum;  
}  

int query(int now,int l,int r,int ql,int qr) {  
    if(!now || qr<l || ql>r) return 0;  
    if(ql<=l && r<=qr) return tree[now].sum;  
    int mid = (l+r)>>1;  
    return query(tree[now].lc,l,mid,ql,qr) +  
           query(tree[now].rc,mid+1,r,ql,qr);  
}  

int main() {  
    int Q; cin >> Q;  
    for(int i=1; i<=Q; i++) {  
        string op,s; int x;  
        cin >> op;  
        if(op == "set") {  
            cin >> s >> x;  
            int id = mp[s] ?: (mp[s]=mp.size());  
            int old = query(rt1[i-1],1,1e9,id,id);  
            if(old) update(rt2[i],1,1e9,old,-1);  
            update(rt2[i],1,1e9,x,1);  
            update(rt1[i],1,1e9,id,x - old);  
        }  
        // 其余操作类似处理  
    }  
}  
```  

---

## 同类型题与拓展  
1. **P3919**：可持久化数组模板，适合练习版本回退  
2. **P3834**：区间第K小，权值线段树经典应用  
3. **CF813E**：可持久化线段树处理区间频次  

---

## 个人心得摘录  
- **Karry5307**：动态开点线段树需预先估算最大节点数，避免MLE  
- **chenzida**：特判优先级为1的情况是避免线段树查询越界的关键  
- **xunzhen**：删除操作后需显式覆盖旧版本，防止隐式引用错误  

---

## 复古游戏化演示（伪代码）  
```javascript  
// Canvas绘制权值树  
function drawTree(node, x, y) {  
    if(node.lc) {  
        ctx.fillStyle = "#FF0000"; // 左子节点红色  
        drawTree(node.lc, x-50, y+50);  
    }  
    if(node.rc) {  
        ctx.fillStyle = "#00FF00"; // 右子节点绿色  
        drawTree(node.rc, x+50, y+50);  
    }  
    ctx.fillRect(x, y, 20, 20); // 当前节点  
}  

// 音效触发  
function playSound(effect) {  
    const sfx = {  
        set: new Audio("data:audio/wav;base64,UklGRl9..."),  
        undo: new Audio("data:audio/wav;base64,UklGRk9...")  
    };  
    sfx[effect].play();  
}  
```  

---

通过上述设计，学习者可在交互式动画中直观理解可持久化线段树的版本更新机制，同时通过复古音效和像素风格增强学习趣味性。

---
处理用时：97.45秒