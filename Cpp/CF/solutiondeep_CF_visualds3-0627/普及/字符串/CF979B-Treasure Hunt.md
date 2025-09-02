# 题目信息

# Treasure Hunt

## 题目描述

After the big birthday party, Katie still wanted Shiro to have some more fun. Later, she came up with a game called treasure hunt. Of course, she invited her best friends Kuro and Shiro to play with her.

The three friends are very smart so they passed all the challenges very quickly and finally reached the destination. But the treasure can only belong to one cat so they started to think of something which can determine who is worthy of the treasure. Instantly, Kuro came up with some ribbons.

A random colorful ribbon is given to each of the cats. Each color of the ribbon can be represented as an uppercase or lowercase Latin letter. Let's call a consecutive subsequence of colors that appears in the ribbon a subribbon. The beauty of a ribbon is defined as the maximum number of times one of its subribbon appears in the ribbon. The more the subribbon appears, the more beautiful is the ribbon. For example, the ribbon aaaaaaa has the beauty of $ 7 $ because its subribbon a appears $ 7 $ times, and the ribbon abcdabc has the beauty of $ 2 $ because its subribbon abc appears twice.

The rules are simple. The game will have $ n $ turns. Every turn, each of the cats must change strictly one color (at one position) in his/her ribbon to an arbitrary color which is different from the unchanged one. For example, a ribbon aaab can be changed into acab in one turn. The one having the most beautiful ribbon after $ n $ turns wins the treasure.

Could you find out who is going to be the winner if they all play optimally?

## 说明/提示

In the first example, after $ 3 $ turns, Kuro can change his ribbon into ooooo, which has the beauty of $ 5 $ , while reaching such beauty for Shiro and Katie is impossible (both Shiro and Katie can reach the beauty of at most $ 4 $ , for example by changing Shiro's ribbon into SSiSS and changing Katie's ribbon into Kaaaa). Therefore, the winner is Kuro.

In the fourth example, since the length of each of the string is $ 9 $ and the number of turn is $ 15 $ , everyone can change their ribbons in some way to reach the maximal beauty of $ 9 $ by changing their strings into zzzzzzzzz after 9 turns, and repeatedly change their strings into azzzzzzzz and then into zzzzzzzzz thrice. Therefore, the game ends in a draw.

## 样例 #1

### 输入

```
3
Kuroo
Shiro
Katie
```

### 输出

```
Kuro
```

## 样例 #2

### 输入

```
7
treasurehunt
threefriends
hiCodeforces
```

### 输出

```
Shiro
```

## 样例 #3

### 输入

```
1
abcabc
cbabac
ababca
```

### 输出

```
Katie
```

## 样例 #4

### 输入

```
15
foPaErcvJ
mZaxowpbt
mkuOlaHRE
```

### 输出

```
Draw
```

# AI分析结果



### 算法分类
贪心算法

---

### 题解思路与算法分析
**核心思路**：  
最优解为长度为1的子串。统计每个字符出现次数，找到最大值 `max_cnt`，分情况计算可能的最大美丽度：  
1. 若 `n ≤ 总长度 - max_cnt` → 结果为 `max_cnt + n`  
2. 否则：  
   - 若原字符串全为同一字符且 `n=1` → 结果为 `len-1`  
   - 否则 → 结果为 `len`（通过交替修改不影响最终次数）

**解决难点**：  
- 正确处理剩余操作次数超过可替换字符数的边界情况  
- 特殊处理全相同字符且 `n=1` 的情况  

---

### 题解评分（4.5星）
1. **小程的题解（4.5星）**  
   - 亮点：  
     - 严格处理字符统计范围（覆盖大小写）  
     - 条件判断清晰，注释提醒注意大小写  
     - 个人心得帮助理解易错点  
   - 改进点：数组初始化可优化  

2. **Leaper_lyc的题解（4.5星）**  
   - 亮点：  
     - 代码简洁，直接使用字符ASCII码统计  
     - 分离统计逻辑，可读性高  
   - 改进点：未处理非字母字符（但题目保证合法输入不影响正确性）  

---

### 最优思路与技巧
**关键步骤**：  
1. **贪心选择最优字符**：统计所有字符出现次数，取最大值  
2. **动态调整策略**：  
   - 操作次数充足时全替换  
   - 剩余次数用交替修改维持最大次数  

**技巧**：  
- 用桶统计字符频率  
- 分情况讨论剩余操作次数的处理  

---

### 同类题型
- **LeetCode 424. Longest Repeating Character Replacement**  
- **Codeforces 1328C - Ternary XOR**  
- **洛谷 P1012 [NOIP1998 提高组] 拼数**  

---

### 个人心得摘录
> “我打比赛的时候没注意结果没A qwq” —— 小程  
> **启示**：注意题目明确条件（如大小写敏感）是AC的关键细节  

---

### 可视化设计
**核心动画方案**：  
1. **像素化彩带**：  
   - 初始彩带用不同颜色方块表示字符  
   - 每次操作高亮修改的方块，目标字符逐渐扩散  
2. **操作剩余次数动态显示**：  
   - 充足时：绿色进度条填充  
   - 剩余次数过多时：红色闪烁提示交替修改  
3. **音效设计**：  
   - 修改字符时播放“滴”声  
   - 达到最大美丽度时播放胜利音效  

**复古风格**：  
- 8-bit字体与色块  
- 背景音乐：FC经典《超级马里奥》地下关BGM  

---

### 核心代码实现
```cpp
int solve(string s) {
    int cnt[256] = {0}; // 统计所有ASCII字符
    for (char c : s) cnt[c]++;
    int max_cnt = *max_element(cnt, cnt+256);
    int len = s.size();

    if (n <= len - max_cnt) return max_cnt + n;
    else {
        if (max_cnt == len && n == 1) return len-1;
        else return len;
    }
}
```

---

### 总结
通过贪心策略与分情况讨论，本题的难点在于剩余操作次数的灵活处理。两位题解均采用高效实现，值得学习其清晰的逻辑划分与边界处理技巧。

---
处理用时：109.94秒