# 题目信息

# African Crossword

## 题目描述

An African crossword is a rectangular table $ n×m $ in size. Each cell of the table contains exactly one letter. This table (it is also referred to as grid) contains some encrypted word that needs to be decoded.

To solve the crossword you should cross out all repeated letters in rows and columns. In other words, a letter should only be crossed out if and only if the corresponding column or row contains at least one more letter that is exactly the same. Besides, all such letters are crossed out simultaneously.

When all repeated letters have been crossed out, we should write the remaining letters in a string. The letters that occupy a higher position follow before the letters that occupy a lower position. If the letters are located in one row, then the letter to the left goes first. The resulting word is the answer to the problem.

You are suggested to solve an African crossword and print the word encrypted there.

## 样例 #1

### 输入

```
3 3
cba
bcd
cbc
```

### 输出

```
abcd```

## 样例 #2

### 输入

```
5 5
fcofd
ooedo
afaoa
rdcdf
eofsf
```

### 输出

```
codeforces```

# AI分析结果

### 题目翻译
## 非洲 crossword

### 题目描述
一个非洲 crossword 是一个 $n×m$ 的矩形表格。表格的每个单元格中恰好包含一个字母。这个表格（也称为网格）包含一些需要解码的加密单词。

要解决这个 crossword，你应该划掉每行和每列中所有重复的字母。换句话说，当且仅当对应的列或行中至少还有一个完全相同的字母时，才应该划掉该字母。此外，所有这些重复的字母会同时被划掉。

当所有重复的字母都被划掉后，我们应该将剩下的字母写成一个字符串。位置较高的字母排在位置较低的字母之前。如果字母位于同一行，则左边的字母排在前面。得到的单词就是该问题的答案。

你需要解决这个非洲 crossword 并打印出其中加密的单词。

### 样例 #1
#### 输入
```
3 3
cba
bcd
cbc
```
#### 输出
```
abcd
```

### 样例 #2
#### 输入
```
5 5
fcofd
ooedo
afaoa
rdcdf
eofsf
```
#### 输出
```
codeforces
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是对字符矩阵进行遍历，判断每个字符在其所在行和列中是否有重复，若有重复则标记该字符，最后输出未被标记的字符。各题解的主要区别在于实现方式和细节处理。
- **思路对比**：多数题解采用暴力枚举的方法，对矩阵中的每个字符检查其所在行和列是否有重复字符；部分题解使用数组记录字符是否重复，避免直接修改原矩阵；还有题解使用 `map` 来统计字符出现的次数。
- **算法要点**：主要是通过多层循环遍历矩阵，对每个字符进行重复检查。
- **解决难点**：关键在于避免直接修改原矩阵，因为直接删除重复字符可能会影响后续判断，导致结果错误。

### 所选题解
- **Zachary_Cloud（4星）**
  - **关键亮点**：思路清晰，代码简洁，使用 `check` 函数判断字符是否重复，并且给出了避免直接修改原矩阵的提示。
  - **个人心得**：提醒不要直接修改原矩阵，否则会导致 `WA`，应使用检查的方法。
- **ZolaWatle（4星）**
  - **关键亮点**：详细解释了题目翻译的问题，使用 `opt` 数组标记重复字符，思路清晰，还提出了一个关于优化的思考问题。
  - **个人心得**：指出题目翻译中“或”的错误，实际应为“和”，并建议修改翻译。
- **伟大的王夫子（4星）**
  - **关键亮点**：分别处理行和列，通过统计字符出现次数来判断是否重复，代码逻辑清晰，适合新手练习。

### 重点代码
#### Zachary_Cloud 的 `check` 函数
```cpp
bool check(int x, int y) {
    for (int i = 1; i <= n; ++i) //判断同一列中是否有相同字符
        if (i == x) continue; //同一个字符当然不能判断
        else if (a[i][y] == a[x][y]) return 0; //返回 false
    for (int i = 1; i <= m; ++i) //判断同一行中是否有相同字符
        if (i == y) continue;
        else if (a[x][i] == a[x][y]) return 0;
    return 1; //返回 true
}
```
**核心实现思想**：遍历当前字符所在的行和列，检查是否有相同字符，若有则返回 `false`，否则返回 `true`。

#### ZolaWatle 的标记重复字符部分
```cpp
for(re i=1;i<=n;i++)
    for(re j=1;j<=m;j++)
    {
        for(re k=i+1;k<=n;k++)  //注意是从i+1开始，自己跟自己总不能算重复吧？ 
            if(a[k][j]==a[i][j])
                opt[i][j]=opt[k][j]=1;  //枚举当前行 
        for(re k=j+1;k<=m;k++)
            if(a[i][k]==a[i][j])
                opt[i][j]=opt[i][k]=1;  //枚举当前列 
    }
```
**核心实现思想**：通过三层循环遍历矩阵，对每个字符检查其所在行和列是否有重复字符，若有则将对应的 `opt` 数组元素置为 `1`。

#### 伟大的王夫子的处理行和列部分
```cpp
for (register int i = 1; i <= n; ++i) {
    int c[210];
    memset(c, 0, sizeof c);
    for (register int j = 1; j <= m; ++j) c[a[i][j]]++;
    for (register int j = 1; j <= m; ++j) 
        if (c[a[i][j]] >= 2) v[i][j] = 1;
}
for (register int j = 1; j <= m; ++j) {
    int c[210];
    memset(c, 0, sizeof c);
    for (register int i = 1; i <= n; ++i) c[a[i][j]]++;
    for (register int i = 1; i <= n; ++i) if (c[a[i][j]] >= 2) v[i][j] = 1;
}
```
**核心实现思想**：分别处理行和列，对于每行和每列，统计每个字符出现的次数，若出现次数大于等于 2，则标记该字符为重复。

### 扩展思路
同类型题通常是对矩阵或数组进行遍历和处理，判断元素是否满足某种条件。类似算法套路包括暴力枚举、标记法等。

### 推荐题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)：通过标记法判断哪些树被移走，与本题标记重复字符的思路类似。
- [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)：对矩阵进行遍历和处理，根据条件选择合适的排和列，与本题对矩阵的处理方式相似。
- [P1427 小鱼的数字游戏](https://www.luogu.com.cn/problem/P1427)：对数组进行遍历和操作，与本题对矩阵的遍历操作有一定的相似性。

---
处理用时：42.03秒