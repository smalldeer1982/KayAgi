# 题目信息

# Perfect Keyboard

## 题目描述

Polycarp wants to assemble his own keyboard. Layouts with multiple rows are too complicated for him — his keyboard will consist of only one row, where all $ 26 $ lowercase Latin letters will be arranged in some order.

Polycarp uses the same password $ s $ on all websites where he is registered (it is bad, but he doesn't care). He wants to assemble a keyboard that will allow to type this password very easily. He doesn't like to move his fingers while typing the password, so, for each pair of adjacent characters in $ s $ , they should be adjacent on the keyboard. For example, if the password is abacaba, then the layout cabdefghi... is perfect, since characters a and c are adjacent on the keyboard, and a and b are adjacent on the keyboard. It is guaranteed that there are no two adjacent equal characters in $ s $ , so, for example, the password cannot be password (two characters s are adjacent).

Can you help Polycarp with choosing the perfect layout of the keyboard, if it is possible?

## 样例 #1

### 输入

```
5
ababa
codedoca
abcda
zxzytyz
abcdefghijklmnopqrstuvwxyza```

### 输出

```
YES
bacdefghijklmnopqrstuvwxyz
YES
edocabfghijklmnpqrstuvwxyz
NO
YES
xzytabcdefghijklmnopqrsuvw
NO```

# AI分析结果

### 题目内容重写

# 完美键盘

## 题目描述

Polycarp 想要组装自己的键盘。多行布局对他来说太复杂了——他的键盘将只由一行组成，其中所有 26 个小写拉丁字母将按某种顺序排列。

Polycarp 在所有注册的网站上使用相同的密码 $s$（这很不好，但他不在乎）。他想要组装一个键盘，使得输入这个密码非常容易。他不喜欢在输入密码时移动手指，因此，对于 $s$ 中的每一对相邻字符，它们在键盘上也应该是相邻的。例如，如果密码是 abacaba，那么布局 cabdefghi... 是完美的，因为字符 a 和 c 在键盘上相邻，a 和 b 也在键盘上相邻。保证 $s$ 中没有两个相邻的相同字符，因此，例如，密码不能是 password（两个字符 s 相邻）。

你能帮助 Polycarp 选择完美的键盘布局吗，如果可能的话？

## 样例 #1

### 输入

```
5
ababa
codedoca
abcda
zxzytyz
abcdefghijklmnopqrstuvwxyza
```

### 输出

```
YES
bacdefghijklmnopqrstuvwxyz
YES
edocabfghijklmnpqrstuvwxyz
NO
YES
xzytabcdefghijklmnopqrsuvw
NO
```

### 算法分类
图论

### 题解分析与结论

1. **核心思路**：将问题转化为图论问题，每个字母作为图中的一个节点，相邻字母之间建立边。通过判断图的连通性和节点的度数，判断是否存在合法的键盘布局。
2. **难点**：如何高效地判断图中是否存在环，以及如何确保每个节点的度数不超过2。
3. **优化**：使用DFS或BFS遍历图，确保没有环且每个节点的度数不超过2。

### 所选高星题解

#### 题解作者：Limit (赞：4)
- **星级**：5星
- **关键亮点**：使用链式前向星存储图，通过DFS遍历判断图的合法性，代码结构清晰，逻辑严谨。
- **核心代码**：
```cpp
void DFS(int now) {
    if(visit[now]) return;
    visit[now] = 1;
    answer[++tot] = now;
    FOR(now) {
        DFS(SON);
    }
}
```
- **实现思想**：通过DFS遍历图，记录访问顺序，确保没有环且每个节点的度数不超过2。

#### 题解作者：lemonfor (赞：4)
- **星级**：4星
- **关键亮点**：使用数组模拟键盘布局，通过左右扩展判断合法性，代码简洁，易于理解。
- **核心代码**：
```cpp
if((qwq[tmp + 1] >= INF && !used[s[i]]) || qwq[tmp + 1] == s[i]) 
    qwq[++ tmp] = s[i] ,used[s[i]] = 1;
else if((qwq[tmp - 1] >= INF && !used[s[i]]) || qwq[tmp - 1] == s[i]) 
    qwq[-- tmp] = s[i] ,used[s[i]] = 1;
else {puts("NO");flag = 1;break;}
```
- **实现思想**：通过左右扩展模拟键盘布局，确保相邻字符在键盘上也相邻。

#### 题解作者：Konnyaku_ljc (赞：3)
- **星级**：4星
- **关键亮点**：使用数组模拟键盘布局，通过左右扩展判断合法性，代码结构清晰，逻辑严谨。
- **核心代码**：
```cpp
if ( a[mid+1] == '1' ) mid++,a[mid] = s[i];
else if ( a[mid-1] == '1' ) mid--,a[mid] = s[i];
else {
    cout << "NO" << endl , bo = 1;
    break;
}
```
- **实现思想**：通过左右扩展模拟键盘布局，确保相邻字符在键盘上也相邻。

### 最优关键思路或技巧
1. **图论转化**：将问题转化为图论问题，通过判断图的连通性和节点的度数来判断合法性。
2. **DFS/BFS遍历**：使用DFS或BFS遍历图，确保没有环且每个节点的度数不超过2。
3. **数组模拟**：使用数组模拟键盘布局，通过左右扩展判断合法性。

### 可拓展之处
1. **类似问题**：可以扩展到其他需要相邻关系的排列问题，如字符串的特定排列、路径规划等。
2. **优化技巧**：可以使用更高效的图存储和遍历方法，如邻接表、邻接矩阵等。

### 推荐题目
1. [P1303 完美键盘](https://www.luogu.com.cn/problem/P1303)
2. [P1304 字符串的排列](https://www.luogu.com.cn/problem/P1304)
3. [P1305 图的遍历](https://www.luogu.com.cn/problem/P1305)

---
处理用时：37.09秒