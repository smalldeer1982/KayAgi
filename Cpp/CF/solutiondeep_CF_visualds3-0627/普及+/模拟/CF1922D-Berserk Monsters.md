# 题目信息

# Berserk Monsters

## 题目描述

Monocarp is playing a computer game (yet again). Guess what is he doing? That's right, killing monsters.

There are $ n $ monsters in a row, numbered from $ 1 $ to $ n $ . The $ i $ -th monster has two parameters: attack value equal to $ a_i $ and defense value equal to $ d_i $ . In order to kill these monsters, Monocarp put a berserk spell on them, so they're attacking each other instead of Monocarp's character.

The fight consists of $ n $ rounds. Every round, the following happens:

- first, every alive monster $ i $ deals $ a_i $ damage to the closest alive monster to the left (if it exists) and the closest alive monster to the right (if it exists);
- then, every alive monster $ j $ which received more than $ d_j $ damage during this round dies. I. e. the $ j $ -th monster dies if and only if its defense value $ d_j $ is strictly less than the total damage it received this round.

For each round, calculate the number of monsters that will die during that round.

## 说明/提示

Explanation for the first test case of the example:

During the first round, the following happens:

- the monster $ 1 $ deals $ 3 $ damage to the monster $ 2 $ ;
- the monster $ 2 $ deals $ 4 $ damage to the monster $ 1 $ and the monster $ 3 $ ;
- the monster $ 3 $ deals $ 7 $ damage to the monster $ 2 $ and the monster $ 4 $ ;
- the monster $ 4 $ deals $ 5 $ damage to the monster $ 3 $ and the monster $ 5 $ ;
- the monster $ 5 $ deals $ 10 $ damage to the monster $ 4 $ ;
- the monster $ 1 $ does not die, since it received $ 4 $ damage and its defense is $ 4 $ ;
- the monster $ 2 $ dies, since it received $ 10 $ damage and its defense is $ 9 $ ;
- the monster $ 3 $ dies, since it received $ 9 $ damage and its defense is $ 1 $ ;
- the monster $ 4 $ does not die, since it received $ 17 $ damage and its defense is $ 18 $ ;
- the monster $ 5 $ dies, since it received $ 5 $ damage and its defense is $ 1 $ .

After the first round, the monsters $ 1 $ and $ 4 $ stay alive.

During the second round, the following happens:

- the monster $ 1 $ deals $ 3 $ damage to the monster $ 4 $ ;
- the monster $ 4 $ deals $ 5 $ damage to the monster $ 1 $ ;
- the monster $ 1 $ dies, since it received $ 5 $ damage and its defense is $ 4 $ ;
- the monster $ 4 $ does not die, since it received $ 3 $ damage and its defense is $ 18 $ .

During the next three rounds, only the $ 4 $ -th monster is alive, so nothing happens.

## 样例 #1

### 输入

```
3
5
3 4 7 5 10
4 9 1 18 1
2
2 1
1 3
4
1 1 2 4
3 3 4 2```

### 输出

```
3 1 0 0 0 
0 0 
1 1 1 0```

# AI分析结果



---

## 唯一算法分类  
链表、均摊分析  

---

## 综合分析与结论  
**核心思路**：  
- 使用双向链表维护存活怪物的左右邻居关系  
- 每轮仅检查可能受影响的怪物（前一轮死亡怪物的左右邻居）  
- 通过候选集合（可能被删除的怪物集合）实现均摊 O(n) 时间复杂度  

**算法流程**：  
1. **初始化双向链表**，每个怪物的左邻居为 i-1，右邻居为 i+1  
2. **第一轮检查所有怪物**，将死亡的加入删除列表  
3. **后续每轮**：  
   - 遍历候选集合，计算每个怪物的左右攻击总和  
   - 若总伤害超过防御值则标记为死亡  
   - 更新链表，并将新死亡的左右邻居加入下一轮候选集合  

**难点与解决方案**：  
- **维护候选集合**：仅当怪物的左右邻居发生变化时才需检查，避免重复计算  
- **链表更新**：通过删除节点的左右指针调整邻居关系，保证 O(1) 时间完成  
- **均摊复杂度证明**：每个怪物最多被加入候选集合 2 次（左邻居死、右邻居死）  

**可视化设计**：  
- **像素风格 Canvas**：  
  - 每个怪物表示为 32x32 像素方块，存活时绿色，死亡变灰色  
  - 当前轮候选集合的怪物用黄色边框高亮  
  - 攻击线动画：存活怪物向左右发射红色箭头表示攻击  
- **音效设计**：  
  - 怪物死亡时播放 8-bit "爆炸" 音效  
  - 链表更新时触发短促 "点击" 音效  
- **AI 自动演示**：  
  - 每步延迟 500ms，通过 `requestAnimationFrame` 驱动动画  
  - 可暂停/继续，支持拖拽进度条查看特定轮次  

---

## 题解清单 (≥4星)  
1. **Eraine（★★★★★）**  
   - 亮点：线性时间复杂度，清晰的双列表维护（候选列表 + 删除列表）  
   - 代码可读性高，注释完整，适合教学  

2. **zjinze（★★★★☆）**  
   - 使用 set 维护候选集合，逻辑简洁  
   - 通过集合去重避免重复计算，但 set 操作稍慢  

3. **joe_zxq（★★★★☆）**  
   - 结构体存储链表，代码模块化程度高  
   - 使用 `set` 自动排序，便于调试  

---

## 核心代码实现  
**Eraine 的删除逻辑**：  
```cpp  
void del(int u) {
    R[L[u]] = R[u];
    L[R[u]] = L[u];
    add(L[u]); // 将左右邻居加入候选集合
    add(R[u]);
}

void solve() {
    // 初始化链表
    for(int i=1; i<=n+1; i++) {
        L[i] = i-1;
        R[i-1] = i;
    }
    // 处理每轮删除
    for(int i=1; i<=n; i++) {
        for(int j : islst) {
            if(d[j] < a[L[j]] + a[R[j]]) 
                dellst.push_back(j);
        }
        for(int j : dellst) del(j);
    }
}
```  

**复古动画核心 JS 片段**：  
```javascript  
class MonsterAnim {
    constructor(canvas) {
        this.ctx = canvas.getContext('2d');
        this.monsters = []; // 存储怪物位置和状态
        this.playSound = (type) => { /* Web Audio 音效 */ };
    }

    drawRound(round) {
        this.ctx.clearRect(0, 0, W, H);
        this.monsters.forEach((m, i) => {
            // 绘制像素风格怪物
            this.ctx.fillStyle = m.dead ? '#666' : '#0f0';
            this.ctx.fillRect(i*32, 0, 30, 30);
            // 绘制攻击箭头
            if(!m.dead) {
                this.drawArrow(i*32-16, 15, 'left', m.leftAtk);
                this.drawArrow(i*32+32, 15, 'right', m.rightAtk);
            }
        });
    }

    async animateDeaths(deathList) {
        deathList.forEach(i => {
            this.monsters[i].dead = true;
            this.playSound('explode');
        });
        await delay(500); // 每步暂停
    }
}
```  

---

## 类似题目推荐  
1. **P7912 [CSP-J 2021] 小熊的果篮**  
   - 同样需要维护元素间的相邻关系  
2. **P1160 队列安排**  
   - 双向链表的动态插入/删除操作  
3. **P1449 约瑟夫问题**  
   - 环形链表的经典应用  

---

## 个人心得摘录  
- **Eraine**：  
  > "注意不能直接删除，因为判断语句中的 L[x] 和 R[x] 可能已经被修改，需要先收集所有待删除元素再批量处理。"  
  - 关键点：删除操作的原子性  

- **huangrenheluogu**：  
  > "多测不清空，爆零两行泪；清空用 memset，TLE 两行泪。"  
  - 教训：静态数组的初始化方式影响效率  

---

## 可视化算法演示  
**动画流程**：  
1. **初始化阶段**：  
   - 所有怪物排成一排，显示攻击力/防御力数值  
   - 双向链表指针以蓝色线条连接  

2. **攻击阶段**：  
   - 存活怪物向左右发射红色箭头，箭头粗细表示攻击力大小  
   - 总伤害显示在怪物头顶（如：`3+5=8`）  

3. **死亡判定**：  
   - 防御力低于总伤害的怪物闪烁三次后变灰  
   - 播放爆炸音效，链表指针自动重组  

4. **候选集合更新**：  
   - 新加入候选的怪物显示黄色脉冲边框  
   - 未被检查的怪物变为半透明  

**交互功能**：  
- 速度滑块：0.5x 至 3x 倍速  
- 单步执行按钮：按轮次逐步执行  
- 鼠标悬停显示怪物属性  

**8-bit 风格设计**：  
- 调色板：NES 经典 16 色  
- 音效：ChipTone 生成的 8-bit 音效  
- 怪物死亡特效：像素粒子爆炸动画  

--- 

通过此设计，学习者可直观观察链表更新过程，理解均摊复杂度的优化原理，同时通过游戏化元素提升学习兴趣。

---
处理用时：79.09秒