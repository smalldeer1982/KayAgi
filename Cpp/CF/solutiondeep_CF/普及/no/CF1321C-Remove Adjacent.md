# 题目信息

# Remove Adjacent

## 题目描述

You are given a string $ s $ consisting of lowercase Latin letters. Let the length of $ s $ be $ |s| $ . You may perform several operations on this string.

In one operation, you can choose some index $ i $ and remove the $ i $ -th character of $ s $ ( $ s_i $ ) if at least one of its adjacent characters is the previous letter in the Latin alphabet for $ s_i $ . For example, the previous letter for b is a, the previous letter for s is r, the letter a has no previous letters. Note that after each removal the length of the string decreases by one. So, the index $ i $ should satisfy the condition $ 1 \le i \le |s| $ during each operation.

For the character $ s_i $ adjacent characters are $ s_{i-1} $ and $ s_{i+1} $ . The first and the last characters of $ s $ both have only one adjacent character (unless $ |s| = 1 $ ).

Consider the following example. Let $ s= $ bacabcab.

1. During the first move, you can remove the first character $ s_1= $ b because $ s_2= $ a. Then the string becomes $ s= $ acabcab.
2. During the second move, you can remove the fifth character $ s_5= $ c because $ s_4= $ b. Then the string becomes $ s= $ acabab.
3. During the third move, you can remove the sixth character $ s_6= $ 'b' because $ s_5= $ a. Then the string becomes $ s= $ acaba.
4. During the fourth move, the only character you can remove is $ s_4= $ b, because $ s_3= $ a (or $ s_5= $ a). The string becomes $ s= $ acaa and you cannot do anything with it.

Your task is to find the maximum possible number of characters you can remove if you choose the sequence of operations optimally.

## 说明/提示

The first example is described in the problem statement. Note that the sequence of moves provided in the statement is not the only, but it can be shown that the maximum possible answer to this test is $ 4 $ .

In the second example, you can remove all but one character of $ s $ . The only possible answer follows.

1. During the first move, remove the third character $ s_3= $ d, $ s $ becomes bca.
2. During the second move, remove the second character $ s_2= $ c, $ s $ becomes ba.
3. And during the third move, remove the first character $ s_1= $ b, $ s $ becomes a.

## 样例 #1

### 输入

```
8
bacabcab```

### 输出

```
4```

## 样例 #2

### 输入

```
4
bcda```

### 输出

```
3```

## 样例 #3

### 输入

```
6
abbbbb```

### 输出

```
5```

# AI分析结果

### 题目内容重写
【题目描述】
给定一个由小写拉丁字母组成的字符串 $s$，长度为 $|s|$。你可以对该字符串进行多次操作。

在一次操作中，你可以选择某个索引 $i$，并删除 $s$ 的第 $i$ 个字符 $s_i$，前提是至少有一个相邻字符是 $s_i$ 在拉丁字母表中的前一个字母。例如，b 的前一个字母是 a，s 的前一个字母是 r，而 a 没有前一个字母。注意，每次删除后字符串的长度减少 1。因此，每次操作时索引 $i$ 应满足 $1 \le i \le |s|$。

对于字符 $s_i$，其相邻字符是 $s_{i-1}$ 和 $s_{i+1}$。字符串的第一个和最后一个字符分别只有一个相邻字符（除非 $|s| = 1$）。

你的任务是找到在最优操作序列下，最多可以删除多少个字符。

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心策略，优先删除较大的字符，因为较大的字符对后续字符的删除操作没有影响。具体来说，从字母 'z' 开始，逐步向下遍历到 'b'，每次遍历时检查字符串中是否存在该字符，并且其相邻字符中至少有一个是其前驱字符。如果满足条件，则删除该字符，并继续检查字符串，直到无法删除为止。

### 所选高分题解
#### 题解1：Blunt_Feeling (赞：7)
**星级：4星**
**关键亮点：**
- 使用贪心策略，从 'z' 到 'b' 遍历字符，确保每次删除的都是当前最大的字符。
- 使用 C++ 的 `erase()` 函数删除字符，代码简洁高效。
- 通过 `j=-1` 重置遍历索引，确保删除后重新检查字符串。

**代码核心实现：**
```cpp
for(int i='z';i>'a';i--)
    for(int j=0;j<s.length();j++)
        if(s[j]==i&&(j>0&&s[j-1]==i-1 || j<s.length()-1&&s[j+1]==i-1))
            s.erase(j,1),j=-1;
```

#### 题解2：xiaomuyun (赞：3)
**星级：4星**
**关键亮点：**
- 同样采用贪心策略，从 'z' 到 'b' 遍历字符。
- 使用 `erase()` 函数删除字符，并通过 `i=-1` 重置遍历索引，确保删除后重新检查字符串。
- 代码简洁，逻辑清晰。

**代码核心实现：**
```cpp
for(auto c:"zyxwvutsrqponmlkjihgfedcb")
    for(int i=0;i<s.length();++i)
        if(s[i]==c&&(i>0&&s[i]==s[i-1]+1||i<s.length()-1&&s[i]==s[i+1]+1))
            s.erase(i,1),++cnt,i=-1;
```

#### 题解3：wind_whisper (赞：0)
**星级：4星**
**关键亮点：**
- 使用优先队列（堆）来维护当前可以删除的字符，确保每次删除的都是最大的字符。
- 使用双向链表来维护字符的相邻关系，删除操作时间复杂度为 $O(1)$。
- 通过 `vis` 数组避免重复入队，确保每个字符只被处理一次。

**代码核心实现：**
```cpp
priority_queue<node>q;
for(int i=1;i<=n;i++)
    if(check(i)) q.push((node){s[i]-'a'+1,i}),vis[i]=1;
while(!q.empty()){
    int pl=q.top().pl;q.pop();
    ++ans;
    l[r[pl]]=l[pl];r[l[pl]]=r[pl];
    if(!vis[l[pl]]&&check(l[pl])) q.push((node){s[l[pl]]-'a'+1,l[pl]}),vis[l[pl]]=1;
    if(!vis[r[pl]]&&check(r[pl])) q.push((node){s[r[pl]]-'a'+1,r[pl]}),vis[r[pl]]=1;
}
```

### 最优关键思路与技巧
1. **贪心策略**：从大到小遍历字符，优先删除较大的字符，确保每次删除操作对后续操作没有影响。
2. **链表优化**：使用双向链表维护字符的相邻关系，删除操作时间复杂度为 $O(1)$，适合频繁删除的场景。
3. **优先队列**：通过优先队列维护当前可以删除的字符，确保每次删除的都是最大的字符。

### 可拓展之处
本题的贪心策略可以推广到其他类似的字符串处理问题，尤其是涉及到字符删除或替换的问题。例如，可以扩展到删除字符的条件更加复杂的情况，或者删除字符后对字符串进行其他操作。

### 推荐题目
1. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)
2. [P1321 单词覆盖](https://www.luogu.com.cn/problem/P1321)
3. [P1045 字符统计](https://www.luogu.com.cn/problem/P1045)

### 个人心得摘录
- **Blunt_Feeling**：通过 `j=-1` 重置遍历索引，确保删除后重新检查字符串，避免了遗漏某些字符的删除机会。
- **wind_whisper**：使用优先队列和双向链表，虽然代码稍复杂，但确保了删除操作的高效性，适合处理较大规模的字符串。

---
处理用时：35.92秒