# 题目信息

# yyy loves Easter_Egg I

## 题目背景

Soha 的出题效率着实让人大吃一惊。OI，数学，化学的题目都出好了，物理的题还没有一道。于是，Huntfire，absi2011，redbag 对 soha 进行轮番炸，准备炸到 soha 出来，不料，人群中冲出了个 kkksc03……

## 题目描述

![](https://cdn.luogu.com.cn/upload/pic/1456.png)

![](https://cdn.luogu.com.cn/upload/pic/1455.png)

yyy loves OI（Huntfire），yyy loves Maths（redbag），yyy loves Chemistry（absi2011）对 yyy loves Physics（soha）进行轮番炸，轰炸按照顺序进行，顺序为 Huntfire，redbag，absi2011。

现在这一题中，我们不考虑太复杂的队形形式。我们认为只要这一句内含有且恰好含有一次@，@的人和上一句话一样就算为队形。

比如以下也视为队形：

- `yyy loves OI : @yyy loves Microelectronic`
- `yyy loves Maths : @yyy loves Microelectronic 我佩服soha的出题效率`
- `yyy loves OI : @yyy loves Microelectronic +1`
- `yyy loves Chemistry : +1 @yyy loves Microelectronic`

若 @ 的人与第一个人不同，就算队形被打破。若这个人在队形被打破之前出来发言了，或者就是他打破队形了，就算（油）炸成功了。

若（油）炸成功，输出 `Successful @某某某 attempt`，若队形被破坏先输出 `Unsuccessful @某某某 attempt`，再输出队形第一次被破坏的行数与第一次破坏队形的人的 $\text{id}$。

如果队形一直没被打破，就先输出 `Unsuccessful @某某某 attempt`，再输出队形的长度，最后输出 `Good Queue Shape`。

~~p.s.yyy loves Microelectronic 是 kkksc03~~



## 说明/提示

**@yyy loves Physics 我佩服你的出题效率**

此题仅吐槽 soha，纪念出题者的队形，此队形长达 $91$ 行。

对于 $100\%$ 的数据,每行消息长度 $\le$ $10^3$。 

- 保证行数不超过 $5\times 10^4$；
- 保证输入文件大小不超过 $4\text{MB}$；
- 保证第一个说话的一定在 @ 某人；
- 保证大家的名字都是 $\text{yyy loves ***}$ 的格式；
- 保证每个人说的话中没有 `:`；
- 保证第一个说话的一定艾特了一个人且只 @ 了一个人；
- 保证第一个说话的一定不会艾特自己；
- 保证文件结束一定有一行空行，方便你判定文件结束；
- 并不保证后面说话的艾特了几个人 然而艾特人数不为一个人视为破坏队形；
- 并不保证后面说话是否会反复艾特同一个人；
- 并不保证被炸的人一定破坏队形；
- 并不保证这一题是或不是压轴题；
- 并不保证这一套比赛存在压轴题；
- 并不保证下一套比赛和这一套比赛一样水；
- 并不保证群里除了这 $4$ 个人和 kkksc03 以外没有别人了；
- 并不保证你没 AC 这题的情况下吐槽 soha 不会出事儿；
- AC 了可以吐槽 soha 一句，soha 不会介意。

## 样例 #1

### 输入

```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Microelectronic : ni men wu liao me 
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv

```

### 输出

```
Unsuccessful @yyy loves Physics attempt
4
yyy loves Microelectronic
```

## 样例 #2

### 输入

```
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves OI : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Maths : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Chemistry : @yyy loves Physics wo pei fu ni de chu ti xiao lv
yyy loves Physics : ni men gou le 

```

### 输出

```
Successful @yyy loves Physics attempt
```

# AI分析结果



### 算法分类
无算法分类（字符串处理 + 模拟）

---

### 题解思路与解决难点
#### 核心逻辑
1. **提取发言人与被@者**  
   每条消息格式为 `yyy loves XXX : ...`，用字符串分割或 `sscanf` 提取发言人（XXX）。用 `@yyy loves YYY` 定位被@者。
2. **验证队形条件**  
   - 每个发言必须包含且仅含有一个 `@`
   - 被@者必须与初始目标一致
3. **终止条件**  
   - 目标人发言 → 成功
   - 队形破坏 → 输出破坏行号
   - 输入结束 → 输出未打破队形

#### 解决难点
1. **名字提取边界处理**  
   - 使用 `sscanf` 或自定义函数处理 `yyy loves XXX` 格式，确保提取完整名字。
2. **多@检测**  
   遍历字符串统计 `@` 数量，若 ≠1 则破坏队形。
3. **换行符处理**  
   部分题解需处理 `\r` 或 `\n` 残留字符。

---

### 题解评分（≥4星）
1. **ironwheel（5星）**  
   - 亮点：模块化设计（多个辅助函数），边界处理全面（换行符检测）
2. **Deny_小田（4星）**  
   - 亮点：简洁的 `sscanf` 解析，高效处理名字提取
3. **jyz666（4星）**  
   - 亮点：极简代码（仅 34 行），利用 `count` 统计@数量

---

### 最优思路提炼
1. **字符串快速解析**  
   使用 `sscanf("yyy loves %[^: ]", name)` 直接提取发言人。
2. **@位置定位**  
   `strstr` 或循环遍历定位 `@`，再用 `sscanf` 提取被@者。
3. **统一判定逻辑**  
   ```cpp
   if (发言人 == 目标) → 成功
   else if (@次数≠1 || 被@者≠目标) → 破坏队形
   ```

---

### 类似题目推荐
1. **P1308 [统计单词数]**（字符串匹配）
2. **P1598 [垂直柱状图]**（字符统计）
3. **P1071 [潜伏者]**（字符串替换逻辑）

---

### 核心代码片段（Deny_小田题解）
```cpp
sscanf(strstr(s, "@"), "@yyy loves %s", name);  // 提取被@者
if (count(s, s+len, '@') != 1) // 检测@数量
```

---

### 可视化设计
#### 动画方案
1. **像素风格显示**  
   - **发言人**：绿色像素块，**被@者**：蓝色，**目标**：金色闪烁。
2. **步进流程**  
   - 每条消息按序显示，高亮关键字段（@部分）。
   - 破坏时红色闪烁，成功时烟花特效。
3. **控制面板**  
   - 暂停/继续按钮，速度滑动条（1x~5x）。
4. **音效**  
   - 正确：8-bit 成功音效，错误：短促“哔”声。

#### 关键步骤演示
```javascript
// 伪代码：Canvas 绘制发言人
ctx.fillStyle = "#00FF00"; // 绿色
ctx.fillRect(x, y, 30, 30); // 发言人方块
ctx.fillText("yyy loves " + name, x+40, y+20);
```

---

### 个人心得摘录
- **ironwheel**：换行符导致 WA，需特判 ASCII 13（`\r`）。
- **クリオネ**：`char` 无法存储 `EOF`，改用 `int` 读字符。

---
处理用时：69.64秒