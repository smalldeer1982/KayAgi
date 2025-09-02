# 题目信息

# Game with string

## 题目描述

Two people are playing a game with a string $ s $ , consisting of lowercase latin letters.

On a player's turn, he should choose two consecutive equal letters in the string and delete them.

For example, if the string is equal to "xaax" than there is only one possible turn: delete "aa", so the string will become "xx". A player not able to make a turn loses.

Your task is to determine which player will win if both play optimally.

## 说明/提示

In the first example the first player is unable to make a turn, so he loses.

In the second example first player turns the string into "q", then second player is unable to move, so he loses.

## 样例 #1

### 输入

```
abacaba
```

### 输出

```
No
```

## 样例 #2

### 输入

```
iiq
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
abba
```

### 输出

```
No
```

# AI分析结果

【题目内容】
# 字符串游戏

## 题目描述

两个人正在玩一个关于由小写拉丁字母组成的字符串 $s$ 的游戏。

在玩家的回合中，他应该选择字符串中两个连续的相等字母并删除它们。

例如，如果字符串是 "xaax"，那么只有一个可能的回合：删除 "aa"，字符串将变成 "xx"。无法进行回合的玩家输掉游戏。

你的任务是确定如果双方都采取最优策略，谁会赢。

## 说明/提示

在第一个例子中，第一个玩家无法进行回合，因此他输掉游戏。

在第二个例子中，第一个玩家将字符串变成 "q"，然后第二个玩家无法进行回合，因此他输掉游戏。

## 样例 #1

### 输入

```
abacaba
```

### 输出

```
No
```

## 样例 #2

### 输入

```
iiq
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
abba
```

### 输出

```
No
```

【算法分类】
字符串、模拟

【题解分析与结论】
该题的核心逻辑是通过模拟删除字符串中连续相同字符的过程，统计删除的次数，并根据删除次数的奇偶性判断谁会赢。所有题解都采用了模拟的思路，主要区别在于实现方式的不同，如使用栈、数组或链表等数据结构来辅助删除操作。

【评分较高的题解】

1. **作者：BINYU (5星)**
   - **关键亮点**：使用栈来模拟删除过程，代码简洁且高效。通过比较当前字符与栈顶字符来决定是否删除，统计删除次数并判断奇偶性。
   - **核心代码**：
     ```cpp
     stack <char> x;
     while(cin>>s) {
         if(x.size() > 0 && s == x.top()) x.pop(), ans++;
         else x.push(s);
     }
     if(ans % 2 == 1) cout<<"Yes";
     else cout<<"No";
     ```

2. **作者：zhanghzqwq (4星)**
   - **关键亮点**：同样使用栈来模拟删除过程，代码清晰易懂。特别强调了在判断字符是否与栈顶相同时，必须先判断栈是否为空，避免运行时错误。
   - **核心代码**：
     ```cpp
     stack<char> s;
     while(cin>>ch) {
         if(!s.empty() && ch == s.top()) s.pop(), cnt++;
         else s.push(ch);
     }
     if(cnt % 2 == 1) cout<<"Yes";
     else cout<<"No";
     ```

3. **作者：李至擎 (4星)**
   - **关键亮点**：采用朴素模拟的方法，通过数组和循环来实现删除操作。虽然效率不如栈，但思路清晰，适合初学者理解。
   - **核心代码**：
     ```cpp
     for(int i=0;i<l-1;i++) {
         if(s[i]==s[i+1]) {
             for(int j=i;j<l-2;j++) s[j]=s[j+2];
             ok=1, l-=2;
             break;
         }
     }
     if(ok) ans=!ans;
     ```

【最优关键思路】
使用栈来模拟删除过程是最优的解决方案，因为栈可以方便地处理字符的匹配和删除操作，且时间复杂度为 $O(n)$，空间复杂度也为 $O(n)$。

【可拓展之处】
类似的问题可以扩展到其他字符串操作，如删除特定模式的子串、统计特定字符的出现次数等。此外，栈在处理括号匹配、表达式求值等问题时也非常有用。

【推荐题目】
1. P1042 字符串匹配
2. P1739 表达式括号匹配
3. P1449 后缀表达式

【个人心得摘录】
- **Reywmp**：基础不好害死人，我竟然不知道EOF,~scanf这些东西exe跑不出来。。。后来绝望了放到ide里面测居然出来答案了。卡了50min啊！！！
  - **总结**：调试时遇到问题不要轻易放弃，尝试不同的工具和方法来解决问题。

---
处理用时：31.26秒