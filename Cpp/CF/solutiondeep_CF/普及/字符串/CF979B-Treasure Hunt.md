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

### 题目内容翻译
# 寻宝游戏

## 题目描述
在盛大的生日派对之后，凯蒂仍希望志郎能玩得更开心。后来，她想出了一个名为寻宝的游戏。当然，她邀请了她最好的朋友库罗和志郎一起玩。

这三个朋友都非常聪明，所以他们很快就通过了所有挑战，最终到达了目的地。但宝藏只能属于一只猫，于是他们开始思考如何决定谁配得上这份宝藏。很快，库罗想出了一个办法，拿出了一些丝带。

每条丝带都随机分配给了一只猫。丝带的每一种颜色都可以用一个大写或小写的拉丁字母表示。我们把丝带中连续的一段颜色序列称为子丝带。丝带的美观度定义为其中某个子丝带在丝带中出现的最大次数。子丝带出现的次数越多，丝带就越美观。例如，丝带 `aaaaaaa` 的美观度为 7，因为它的子丝带 `a` 出现了 7 次；丝带 `abcdabc` 的美观度为 2，因为它的子丝带 `abc` 出现了 2 次。

游戏规则很简单。游戏将进行 `n` 轮。每一轮，每只猫都必须严格地将自己丝带上的一种颜色（在一个位置上）换成与原来不同的任意颜色。例如，丝带 `aaab` 可以在一轮中变成 `acab`。`n` 轮结束后，丝带美观度最高的猫将赢得宝藏。

如果他们都发挥出最佳水平，你能找出谁将成为赢家吗？

## 说明/提示
在第一个示例中，经过 3 轮后，库罗可以将他的丝带变成 `ooooo`，其美观度为 5，而志郎和凯蒂无法达到这样的美观度（志郎和凯蒂最多只能达到 4 的美观度，例如，志郎可以将他的丝带变成 `SSiSS`，凯蒂可以将她的丝带变成 `Kaaaa`）。因此，赢家是库罗。

在第四个示例中，由于每个字符串的长度都是 9，且轮数为 15，每个人都可以通过某种方式将他们的丝带变成 `zzzzzzzzz`，在 9 轮后达到最大美观度 9，然后再将字符串变成 `azzzzzzzz`，然后再变回 `zzzzzzzzz` 三次。因此，游戏以平局结束。

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

### 题解综合分析与结论
- **思路对比**：两位作者都认为最优答案是长度为 1 的子串，解题核心是找出每个字符串中出现次数最多的字符，将其他字符尽可能替换为该字符，根据替换次数 `n` 和字符串长度的关系计算最终美观度，比较三只猫丝带的美观度得出赢家。
- **算法要点对比**：
    - 俺是小程使用 `pair` 存储最大出现次数和对应字符的索引，用数组 `m` 统计字符出现次数。
    - Leaper_lyc 用数组 `t1`、`t2`、`t3` 分别统计三个字符串中字符的出现次数，用变量 `cnta`、`cntb`、`cntc` 记录最大出现次数。
- **解决难点对比**：都注意到了特殊情况，即当字符串全是某个字母且 `n = 1` 时，美观度为字符串长度减 1。

### 所选题解
- **俺是小程（5星）**：
    - **关键亮点**：思路清晰，代码注释详细，对官方题解的翻译和解释有助于理解。
    - **个人心得**：“我打比赛的时候没注意结果没A qwq”，提醒要注意字母有大小写。
- **Leaper_lyc（4星）**：
    - **关键亮点**：代码结构清晰，使用桶来维护字符出现次数，逻辑简洁。

### 重点代码及核心实现思想
#### 俺是小程
```cpp
int solve(string s)
{
    int m['z' - 'A' + 1] = {0};
    for(int i = 0; i < (int) s.size(); i++)
        m[s[i] - 'A']++;
    
    P ans(0, 0);
    for(int i = 0; i < ('z' - 'A' + 1); i++)
        if(m[i] > ans.first) 
            ans.first = m[i], ans.second = i;

    if(N <= (int)s.length() - ans.first) return ans.first + N;
    else 
    {
        if((ans.first == (int) s.length()) && N == 1) return s.length() - 1;
        else return s.length();
    }
}
```
核心思想：统计字符串中每个字符的出现次数，找出出现次数最多的字符及其出现次数。根据替换次数 `N` 和剩余可替换字符数的关系计算最终美观度。

#### Leaper_lyc
```cpp
for (int i = 1; i <= len; i++) {
    t1[a[i]]++;
    t2[b[i]]++;
    t3[c[i]]++;
    cnta = max(cnta, t1[a[i]]);
    cntb = max(cntb, t2[b[i]]);
    cntc = max(cntc, t3[c[i]]);
}
if (cnta + n <= len) ansa = cnta + n;
else {
    if (n == 1 && cnta == len) ansa = len - 1;
    else ansa = len;
}
// 对 cntb 和 cntc 进行类似处理
```
核心思想：使用桶 `t1`、`t2`、`t3` 统计三个字符串中字符的出现次数，记录最大出现次数。根据最大出现次数和替换次数 `n` 计算最终美观度。

### 最优关键思路或技巧
- **思维方式**：通过分析得出最优答案是长度为 1 的子串，简化问题。
- **代码实现技巧**：使用桶来统计字符出现次数，方便快捷。

### 同类型题或类似算法套路拓展
此类题目属于字符串处理和逻辑分析类型。类似的题目可能会改变规则，如改变替换方式、增加限制条件等，但核心思路仍然是分析字符串的特征，根据规则计算最优解。

### 洛谷相似题目推荐
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
2. [P1200 [USACO1.1]你的飞碟在这儿Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)
3. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)

---
处理用时：50.97秒