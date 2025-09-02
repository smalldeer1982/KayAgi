# 题目信息

# From S To T

## 题目描述

你将会得到三个由小写拉丁字符组成的字符串 $s, t, p$

每一次操作中，你可以在 $p$ 中任意选出一个字符删去并插入在 $s$ 中的任意一个位置

例如当 $p$ 为 $\text{aba}$，$s$ 为 $\text{de}$，则以下操作都是合法的

$\text{aba} \rightarrow \text{ba}, \text{de} \rightarrow \text{ade}$

$\text{aba} \rightarrow \text{ba}, \text{de} \rightarrow \text{dae}$

$\text{aba} \rightarrow \text{ba}, \text{de} \rightarrow \text{dea}$

$\text{aba} \rightarrow \text{aa}, \text{de} \rightarrow \text{bde}$

$\text{aba} \rightarrow \text{aa}, \text{de} \rightarrow \text{dbe}$

$\text{aba} \rightarrow \text{aa}, \text{de} \rightarrow \text{deb}$

$\text{aba} \rightarrow \text{ab}, \text{de} \rightarrow \text{ade}$

$\text{aba} \rightarrow \text{ab}, \text{de} \rightarrow \text{dae}$

$\text{aba} \rightarrow \text{ab}, \text{de} \rightarrow \text{dea}$

你的任务是检验是否能经过若干次操作（可能零次），将 $s$ 变为 $t$

## 样例 #1

### 输入

```
4
ab
acxb
cax
a
aaaa
aaabbcc
a
aaaa
aabbcc
ab
baaa
aaaaa
```

### 输出

```
YES
YES
NO
NO
```

# AI分析结果

### 题目内容重写
你将会得到三个由小写拉丁字符组成的字符串 $s, t, p$。每一次操作中，你可以在 $p$ 中任意选出一个字符删去并插入在 $s$ 中的任意一个位置。你的任务是检验是否能经过若干次操作（可能零次），将 $s$ 变为 $t$。

### 算法分类
字符串、模拟

### 题解分析与结论
各题解的思路基本一致，主要分为以下几个步骤：
1. **判断 $s$ 是否为 $t$ 的子序列**：如果不是，直接输出 `NO`。
2. **统计字符数量**：统计 $s$ 和 $p$ 中每个字符的数量，确保 $s$ 和 $p$ 中的字符数量之和大于等于 $t$ 中的字符数量。
3. **模拟插入操作**：通过遍历 $t$ 和 $s$，模拟从 $p$ 中插入字符的过程。

### 所选高分题解
#### 题解1：作者：wen_chang (赞：3)
**星级：4**
**关键亮点**：
- 详细解释了题目的三个判断条件，逻辑清晰。
- 代码结构简洁，易于理解。
**核心代码**：
```cpp
for(i=0;i<t[q].size();i++)
{
    if(t[q][i]==s[q][faq])faq++;
    if(faq==s[q].size())
    {
        cout<<"YES"<<endl;
        break;
    }
}
if(faq<s[q].size())cout<<"NO"<<endl;
```
**核心思想**：通过遍历 $t$ 和 $s$，检查 $s$ 是否为 $t$ 的子序列。

#### 题解2：作者：yanghanyv (赞：1)
**星级：4**
**关键亮点**：
- 使用了贪心算法，思路明确。
- 代码中使用了 `vis` 数组标记已匹配的字符，优化了匹配过程。
**核心代码**：
```cpp
for(int i=0;i<t.size();i++){
    if(s[pos]==t[i]){
        vis[i]=1;
        if(++pos==s.size()){
            break;
        }
    }
}
```
**核心思想**：通过双指针遍历 $t$ 和 $s$，标记匹配的字符，确保 $s$ 是 $t$ 的子序列。

#### 题解3：作者：逃课小姐MS (赞：1)
**星级：4**
**关键亮点**：
- 使用了 `cnt` 指针和 `c` 数组，逻辑清晰。
- 代码简洁，易于理解。
**核心代码**：
```cpp
for(int i=0;i<lent;i++){
    if(t[i]==s[cnt]) cnt++;
    else if(c[(int)(t[i]-'a'+1)]!=0) c[(int)(t[i]-'a'+1)]--;
    else flag=0;
}
```
**核心思想**：通过遍历 $t$ 和 $s$，使用 `c` 数组记录 $p$ 中的字符，确保 $s$ 可以通过插入 $p$ 中的字符变为 $t$。

### 最优关键思路
1. **子序列判断**：首先确保 $s$ 是 $t$ 的子序列，这是所有操作的基础。
2. **字符统计**：通过统计 $s$ 和 $p$ 中的字符数量，确保 $t$ 中的每个字符都能被覆盖。
3. **模拟插入**：通过遍历和指针操作，模拟从 $p$ 中插入字符的过程。

### 拓展思路
类似题目可以考察字符串匹配、字符统计和贪心算法的应用。例如，可以扩展到多个字符串的匹配问题，或者考虑字符插入的顺序和位置对结果的影响。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)
3. [P1030 求先序排列](https://www.luogu.com.cn/problem/P1030)

### 个人心得
- **调试经历**：在判断子序列时，注意指针的移动和边界条件的处理，避免越界或漏判。
- **踩坑教训**：字符统计时，确保所有字符都被正确统计，避免遗漏或重复计数。

---
处理用时：27.53秒