# 题目信息

# Code obfuscation

## 题目描述

Kostya likes Codeforces contests very much. However, he is very disappointed that his solutions are frequently hacked. That's why he decided to obfuscate (intentionally make less readable) his code before upcoming contest.

To obfuscate the code, Kostya first looks at the first variable name used in his program and replaces all its occurrences with a single symbol $ a $ , then he looks at the second variable name that has not been replaced yet, and replaces all its occurrences with $ b $ , and so on. Kostya is well-mannered, so he doesn't use any one-letter names before obfuscation. Moreover, there are at most 26 unique identifiers in his programs.

You are given a list of identifiers of some program with removed spaces and line breaks. Check if this program can be a result of Kostya's obfuscation.

## 说明/提示

In the first sample case, one possible list of identifiers would be "number string number character number string number". Here how Kostya would obfuscate the program:

- replace all occurences of number with a, the result would be "a string a character a string a",
- replace all occurences of string with b, the result would be "a b a character a b a",
- replace all occurences of character with c, the result would be "a b a c a b a",
- all identifiers have been replaced, thus the obfuscation is finished.

## 样例 #1

### 输入

```
abacaba
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
jinotega
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
# 代码混淆

## 题目描述
科斯塔非常喜欢Codeforces竞赛。然而，他对自己的解决方案经常被破解感到非常失望。这就是为什么他决定在即将到来的竞赛之前对自己的代码进行混淆处理（故意使其可读性降低）。

为了混淆代码，科斯塔首先查看程序中使用的第一个变量名，并将其所有出现的地方都替换为单个字符 $a$，然后他查看尚未被替换的第二个变量名，并将其所有出现的地方都替换为 $b$，依此类推。科斯塔很有礼貌，所以在混淆之前他不会使用任何单字母名称。此外，他的程序中最多有26个唯一的标识符。

给定一个去除了空格和换行符的程序标识符列表。检查这个程序是否可能是科斯塔混淆处理的结果。

## 说明/提示
在第一个样例中，一种可能的标识符列表是 "number string number character number string number"。科斯塔将按以下方式混淆该程序：
- 将所有的 "number" 替换为 $a$，结果将是 "a string a character a string a"。
- 将所有的 "string" 替换为 $b$，结果将是 "a b a character a b a"。
- 将所有的 "character" 替换为 $c$，结果将是 "a b a c a b a"。
- 所有标识符都已被替换，因此混淆处理完成。

## 样例 #1
### 输入
```
abacaba
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
jinotega
```
### 输出
```
NO
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是模拟科斯塔混淆代码的过程，判断给定的字符串是否符合混淆规则。具体来说，就是检查每个新出现的字符是否按照字母表顺序依次出现，若出现比当前应出现的最大字符更大的字符，则不符合规则。

各题解的算法要点和难点对比如下：
- **思路**：均是遍历字符串，判断字符出现顺序是否符合规则。
- **算法要点**：都使用了一个变量（如 `cnt`、`maxchar` 等）来记录当前应出现的最大字符，通过比较当前字符与该变量的大小来判断是否合法。
- **解决难点**：关键在于准确判断新字符的出现顺序是否正确，避免出现跳跃的字符。

### 题解评分与选择
- **CQ_Bab**：4星。思路清晰，代码实现简洁，使用 `map` 记录字符是否出现过，逻辑明确。
- **辛丑九月**：4星。分析详细，代码简洁，使用布尔数组 `vis` 标记字符是否出现，易于理解。
- **33aaron**：4星。题目分析准确，代码简洁，直接使用字符变量 `maxchar` 记录最大字符，实现简单。

### 关键思路与技巧
- 使用一个变量记录当前应出现的最大字符，在遍历字符串时，比较当前字符与该变量的大小，判断是否合法。
- 可以使用 `map` 或布尔数组来记录字符是否已经出现过。

### 拓展思路
同类型题目可能会有不同的混淆规则或条件，但核心都是模拟某种转换过程，判断结果是否符合规则。类似的算法套路包括对字符串的遍历、字符的比较和状态的记录。

### 洛谷题目推荐
- P1055 [NOIP2008 普及组] ISBN 号码：对字符串进行处理和判断。
- P1200 [USACO1.1] 你的飞碟在这儿 Your Ride Is Here：对字符串进行字符转换和判断。
- P1308 [NOIP2011 普及组] 统计单词数：对字符串进行单词的查找和统计。

### 重点代码
#### CQ_Bab
```cpp
#include <bits/stdc++.h>
using namespace std ;
string s;
int cnt=1;
int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    map<char,int>mp;
    cin>>s;
    for(int i=0; s[i]; i++) {
        if(!mp[s[i]]&&cnt==s[i]-'a'+1) mp[s[i]]=1,cnt++;//判断出现过吗
        else if(s[i]-'a'+1>cnt) {
            cout<<"NO\n"; //不符合
            return false;
        }
    }
    cout<<"YES\n";
    return false;
}
```
核心思想：使用 `map` 记录字符是否出现过，通过 `cnt` 记录当前应出现的最大字符，遍历字符串进行判断。

#### 辛丑九月
```cpp
# include <bits/stdc++.h>
using namespace std;

int k;
string s;
bool vis[40];

int main () {
    cin >> s;
    for (char i : s)
        if (!vis[i - 'a']) {
            vis[i - 'a'] = true;
            if (i - 'a' != k++) return puts ("NO"), 0;
            // 如果当前出现的个数和 'a' + k 不同就是错的
        }
    return puts ("YES"), 0; // 否则就是对的
}
```
核心思想：使用布尔数组 `vis` 标记字符是否出现，通过 `k` 记录当前应出现的最大字符，遍历字符串进行判断。

#### 33aaron
```cpp
#include <iostream>
#include <string>
using namespace std;
string in;
int maxchar = 'a';
int main() {
    cin >> in;
    for (int i = 0; i < in.size(); ++i)
        if (in[i] > maxchar) return cout << "NO", 0;
        else if (in[i] == maxchar) ++maxchar;
    cout << "YES";
    return 0;
}
```
核心思想：使用 `maxchar` 记录当前应出现的最大字符，遍历字符串进行判断。

---
处理用时：36.54秒