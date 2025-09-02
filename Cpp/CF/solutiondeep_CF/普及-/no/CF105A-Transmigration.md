# 题目信息

# Transmigration

## 题目描述

In Disgaea as in most role-playing games, characters have skills that determine the character's ability to use certain weapons or spells. If the character does not have the necessary skill, he cannot use it. The skill level is represented as an integer that increases when you use this skill. Different character classes are characterized by different skills.

Unfortunately, the skills that are uncommon for the given character's class are quite difficult to obtain. To avoid this limitation, there is the so-called transmigration.

Transmigration is reincarnation of the character in a new creature. His soul shifts to a new body and retains part of his experience from the previous life.

As a result of transmigration the new character gets all the skills of the old character and the skill levels are reduced according to the $ k $ coefficient (if the skill level was equal to $ x $ , then after transmigration it becomes equal to $ [kx] $ , where $ [y] $ is the integral part of $ y $ ). If some skill's levels are strictly less than $ 100 $ , these skills are forgotten (the character does not have them any more). After that the new character also gains the skills that are specific for his class, but are new to him. The levels of those additional skills are set to $ 0 $ .

Thus, one can create a character with skills specific for completely different character classes via transmigrations. For example, creating a mage archer or a thief warrior is possible.

You are suggested to solve the following problem: what skills will the character have after transmigration and what will the levels of those skills be?

## 样例 #1

### 输入

```
5 4 0.75
axe 350
impaler 300
ionize 80
megafire 120
magicboost 220
heal
megafire
shield
magicboost
```

### 输出

```
6
axe 262
heal 0
impaler 225
magicboost 165
megafire 0
shield 0
```

# AI分析结果



# 题目中文翻译

## 题目描述

在《魔界战记》及大多数角色扮演游戏中，角色拥有决定其使用特定武器或法术能力的技能。若角色不具备必要技能，则无法使用。技能等级以整数表示，使用技能时会提升。不同职业以不同技能为特色。

通过转生系统（transmigration），角色可将灵魂转移到新躯体，保留部分前世经验。转生后新角色继承所有旧技能，技能等级按系数k取整下降（原等级x变为⌊kx⌋）。若某技能等级严格小于100，则被遗忘。之后新角色会获得本职业新增但未掌握的技能，这些技能初始等级为0。

要求确定转生后角色拥有的技能及其等级。

## 输入输出样例

见原题

---

## 算法分类
模拟

---

## 题解对比与结论

### 共性要点
1. **精度处理**：所有题解都注意到浮点运算精度问题，通过添加微小量（如1e-6）修正取整误差
2. **技能去重**：需处理新技能与继承技能的重名情况，保留高等级技能
3. **数据结构**：主流解法使用`map`或结构体数组管理技能集合

### 最优题解推荐

#### 1. nanatsuhi（五星）
**亮点**：
- 使用`map`简化技能管理，自动处理重复技能
- 代码简洁（仅20行），逻辑清晰
- 通过`int(x+1e-6)`解决浮点精度问题
**核心代码**：
```cpp
map<string,int> mp;
for(/*处理旧技能*/){
    x *= k;
    if(x >= 100) mp[s] = int(x + 1e-6); 
}
for(/*处理新技能*/){
    if(!mp[s]) mp[s] = 0; 
}
```

#### 2. jxbe6666（四星） 
**亮点**：
- 完整处理了新旧技能的五种情况
- 使用`floor(k*x)`保证向下取整正确性
**关键实现**：
```cpp
if(k * x >= 100)
    _m[s1] = int(k * x + 1e-7);
```

#### 3. 谦谦君子（四星）
**亮点**：
- 提出`map`标记法的核心思路
- 强调精度问题的普遍性

---

## 关键技巧总结
1. **浮点精度处理**：计算后添加微小量再取整（如`x + 1e-6`）
2. **数据结构选择**：使用`map`自动处理技能重名，O(1)时间查询存在性
3. **合并策略**：新技能若已存在且有效则不覆盖，否则初始化为0

---

## 类似题目推荐
1. [P1309 瑞士轮](https://www.luogu.com.cn/problem/P1309) - 模拟+归并排序
2. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056) - 模拟+贪心排序
3. [P1603 斯诺登的密码](https://www.luogu.com.cn/problem/P1603) - 字符串处理与模拟

---

## 题解心得摘录
"计算8700*0.94时C++得到8177.999999999999，添加fix_tool=0.000000000001后解决" —— wangjiayu19  
（启示：浮点运算需考虑机器精度误差，添加保护性微小量是通用解决方案）  

"map的自动去重特性让代码简洁度提升一个量级" —— 谦谦君子的题解评论  
（体现了选择合适数据结构对简化问题的重要性）

---
处理用时：44.09秒