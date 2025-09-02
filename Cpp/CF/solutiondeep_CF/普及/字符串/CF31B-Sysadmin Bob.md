# 题目信息

# Sysadmin Bob

## 题目描述

Email address in Berland is a string of the form $ A $ @ $ B $ , where $ A $ and $ B $ are arbitrary strings consisting of small Latin letters.

Bob is a system administrator in «Bersoft» company. He keeps a list of email addresses of the company's staff. This list is as a large string, where all addresses are written in arbitrary order, separated by commas. The same address can be written more than once.

Suddenly, because of unknown reasons, all commas in Bob's list disappeared. Now Bob has a string, where all addresses are written one after another without any separators, and there is impossible to determine, where the boundaries between addresses are. Unfortunately, on the same day his chief asked him to bring the initial list of addresses. Now Bob wants to disjoin addresses in some valid way. Help him to do that.

## 样例 #1

### 输入

```
a@aa@a
```

### 输出

```
a@a,a@a
```

## 样例 #2

### 输入

```
a@a@a
```

### 输出

```
No solution
```

## 样例 #3

### 输入

```
@aa@a
```

### 输出

```
No solution
```

# AI分析结果

### 题目翻译
# 系统管理员鲍勃

## 题目描述
在伯兰，电子邮件地址的形式为 $A$ @ $B$，其中 $A$ 和 $B$ 是由小写拉丁字母组成的任意字符串。

鲍勃是 “Bersoft” 公司的系统管理员。他保存着一份公司员工的电子邮件地址列表。这个列表是一个很长的字符串，所有地址以任意顺序排列，用逗号分隔。同一个地址可能会被多次写入。

突然，由于不明原因，鲍勃列表中的所有逗号都消失了。现在鲍勃得到了一个字符串，所有地址一个接一个地写在一起，没有任何分隔符，因此无法确定地址之间的边界。不幸的是，就在同一天，他的老板要求他提供最初的地址列表。现在鲍勃想以某种有效的方式拆分出这些地址。请帮助他完成这项任务。

## 样例 #1
### 输入
```
a@aa@a
```
### 输出
```
a@a,a@a
```

## 样例 #2
### 输入
```
a@a@a
```
### 输出
```
No solution
```

## 样例 #3
### 输入
```
@aa@a
```
### 输出
```
No solution
```

### 综合分析与结论
这些题解的核心思路都是先判断输入字符串是否能拆分成符合 $A$ @ $B$ 形式的子串，若能则按一定规则拆分并输出，若不能则输出 `No solution`。不同题解在判断不合法情况和拆分字符串的具体实现上有所不同。

### 思路、算法要点及难点对比
| 作者 | 思路 | 算法要点 | 解决难点 |
| --- | --- | --- | --- |
| zheysq_147 | 先判断字符串是否合法，再按规则输出拆分结果 | 定义判断函数 `pd` 检查不合法情况，输出时在特定位置加逗号 | 处理边界情况和最后一个 `@` 后的输出 |
| 皮卡丘最萌 | 考虑多种特殊情况，在合法串之间添加逗号 | 用 `pos` 函数查找 `@` 位置，按规则分割字符串 | 准确判断不合法情况和处理最后一个 `@` |
| Ace_Radom | 运用字符串成员函数，先筛查不合法情况，再分割字符串 | 用 `find` 函数查找 `@` 位置，按规则输出 | 全面考虑不合法情况和处理最后一个 `@` |
| Eason_AC | 从后往前遍历，贪心组合子串 | 用数组记录子串，处理不合法情况 | 处理边界情况和未使用字符 |
| FP·荷兰猪 | 模拟拆分过程，用队列记录 `@` 位置 | 用队列记录 `@` 下标，按规则输出 | 判断不合法情况和处理队列 |
| Lucifer_Bartholomew | 搜索 `@` 位置，特判特殊情况 | 记录 `@` 位置，按规则输出 | 处理边界情况和连续 `@` |
| BotDand | 先判断边界条件，再插入逗号 | 用 `pos` 函数查找 `@` 位置，插入逗号 | 判断不合法情况和插入逗号位置 |

### 评分
| 作者 | 评分 |
| --- | --- |
| zheysq_147 | 4星 |
| 皮卡丘最萌 | 3星 |
| Ace_Radom | 3星 |
| Eason_AC | 3星 |
| FP·荷兰猪 | 3星 |
| Lucifer_Bartholomew | 3星 |
| BotDand | 3星 |

### 所选题解
- **作者：zheysq_147（4星）**
    - **关键亮点**：思路清晰，详细阐述了判断和输出的过程，代码结构清晰，对边界情况处理较为细致。
    - **个人心得**：刚看到题觉得是水题，做题时发现细节很多，3遍才AC，提醒要仔细考虑边界情况。
    - **核心代码**：
```cpp
bool pd()
{
    if(s[1]=='@'||s[n]=='@'||last==-1)
        return 0;
    for(i=2;i<=n-1;++i)
    {
        if(s[i]=='@'&&s[i+1]=='@')
            return 0;
    }
    for(i=2;i<=n-2;++i)
    {
        if(s[i]=='@'&&s[i+2]=='@')
            return 0;
    }
    return 1;
}
void out()
{
    for(i=1;i<=n;++i)
    {
        if(s[i-2]=='@'&&i-2!=last)
            printf(",");
        printf("%c",s[i]);
    }
}
```
**核心实现思想**：`pd` 函数用于判断字符串是否合法，检查边界和连续 `@` 的情况；`out` 函数用于输出拆分结果，在特定位置添加逗号。

### 最优关键思路或技巧
- 全面考虑不合法情况，如字符串首尾为 `@`、没有 `@`、两个 `@` 之间字符过少等。
- 采用统一的拆分规则，如在 `@` 后保留一个字母再分割，或从后往前贪心组合子串。
- 利用字符串处理函数（如 `find`、`pos`）查找 `@` 的位置，简化代码。

### 可拓展之处
同类型题可能会有更复杂的字符串格式要求，或对拆分结果有更多限制条件。类似算法套路可用于处理其他字符串分割、匹配问题，如正则表达式匹配、文本解析等。

### 推荐洛谷题目
- P1055 [ISBN 号码](https://www.luogu.com.cn/problem/P1055)
- P1200 [你的飞碟在这儿](https://www.luogu.com.cn/problem/P1200)
- P1308 [统计单词数](https://www.luogu.com.cn/problem/P1308)

---
处理用时：43.28秒