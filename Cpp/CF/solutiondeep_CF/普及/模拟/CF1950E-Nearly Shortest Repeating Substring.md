# 题目信息

# Nearly Shortest Repeating Substring

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase Latin characters. Find the length of the shortest string $ k $ such that several (possibly one) copies of $ k $ can be concatenated together to form a string with the same length as $ s $ and, at most, one different character.

More formally, find the length of the shortest string $ k $ such that $ c = \underbrace{k + \cdots + k}_{x\rm\ \text{times}} $ for some positive integer $ x $ , strings $ s $ and $ c $ has the same length and $ c_i \neq s_i $ for at most one $ i $ (i.e. there exist $ 0 $ or $ 1 $ such positions).

## 说明/提示

In the first test case, you can select $ k = \texttt{a} $ and $ k+k+k+k = \texttt{aaaa} $ , which only differs from $ s $ in the second position.

In the second test case, you cannot select $ k $ of length one or two. We can have $ k = \texttt{abba} $ , which is equal to $ s $ .

## 样例 #1

### 输入

```
5
4
abaa
4
abba
13
slavicgslavic
8
hshahaha
20
stormflamestornflame```

### 输出

```
1
4
13
2
10```

# AI分析结果

### 题目中文重写
## 几乎最短重复子串

### 题目描述
给定一个长度为 $n$ 的由小写拉丁字符组成的字符串 $s$。找出最短字符串 $k$ 的长度，使得将 $k$ 进行若干次（可能为一次）拼接后形成的字符串与 $s$ 长度相同，且最多只有一个字符不同。

更正式地说，找出最短字符串 $k$ 的长度，使得对于某个正整数 $x$，有 $c = \underbrace{k + \cdots + k}_{x\text{ 次}}$，字符串 $s$ 和 $c$ 长度相同，并且 $c_i \neq s_i$ 的 $i$ 最多有一个（即存在 $0$ 个或 $1$ 个这样的位置）。

### 说明/提示
在第一个测试用例中，你可以选择 $k = \texttt{a}$，那么 $k + k + k + k = \texttt{aaaa}$，它与 $s$ 仅在第二个位置不同。

在第二个测试用例中，你不能选择长度为 $1$ 或 $2$ 的 $k$。我们可以取 $k = \texttt{abba}$，它与 $s$ 相等。

### 样例 #1
#### 输入
```
5
4
abaa
4
abba
13
slavicgslavic
8
hshahaha
20
stormflamestornflame
```
#### 输出
```
1
4
13
2
10
```

### 综合分析与结论
这些题解的核心思路都是枚举可能的子串长度（该长度为原字符串长度的因数），然后检查由该子串重复拼接得到的字符串与原字符串的差异是否满足最多一个字符不同的条件。不同题解在具体实现方式上有所差异：
- **枚举方式**：部分题解枚举所有因数，部分只枚举到 $\sqrt{n}$ 再通过除法得到其他因数。
- **子串选择**：有的题解选择从前往后和从后往前截取子串，有的选择前两个子串。
- **检查方法**：有的通过拼接子串再比较，有的直接在原字符串上比较。

### 所选题解
- **作者：Infinite_Loop（5星）**
    - **关键亮点**：思路清晰，详细分析了错误原因并给出修正方法，代码可读性高。
    - **个人心得**：在最初实现时样例过不了，通过分析第四组样例发现需要从后往前再进行一次检查。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++){
    if(n%i!=0)continue;
    string s2=s.substr(0,i);
    int sum=0;
    for(int j=0,k=0;j<n;j++){
        if(s[j]!=s2[k++])sum++;
        if(k>=i)k=0;
        if(sum>1)break;
    }
    if(sum<=1)ans=min(ans,i);
    s2=s.substr(n-i,i),sum=0;
    for(int j=0,k=0;j<n;j++){
        if(s[j]!=s2[k++])sum++;
        if(k>=i)k=0;
        if(sum>1)break;
    }
    if(sum<=1)ans=min(ans,i);
}
```
核心实现思想：枚举所有可能的子串长度 $i$，先从前往后截取子串 $s2$ 进行拼接比较，再从后往前截取子串 $s2$ 进行拼接比较，记录不同字符的数量 $sum$，若 $sum$ 小于等于 $1$，则更新最小长度 $ans$。

- **作者：fujiayu（4星）**
    - **关键亮点**：思路简洁，对时间复杂度进行了分析，代码结构清晰。
    - **核心代码**：
```cpp
for(int i=1; i<=n; i++)
{
    if(n % i) continue;
    string a = s.substr(0, i);
    string b = s.substr(i, i);
    int fa=0, fb=0;
    for(int j=0; j*i<n; j++)
    {
        string t = s.substr(j*i, i);
        for(int k=0; k<t.length(); k++)
        {
            fa += (a[k]!= t[k]);
            fb += (b[k]!= t[k]);
        }
    }
    if(fa <= 1 || fb <= 1)
    {
        cout << i << '\n';
        break;
    }
}
```
核心实现思想：枚举所有可能的子串长度 $i$，取前两个子串 $a$ 和 $b$，分别与后续子串比较，记录不同字符的数量 $fa$ 和 $fb$，若 $fa$ 或 $fb$ 小于等于 $1$，则输出 $i$。

- **作者：spire001（4星）**
    - **关键亮点**：复杂度分析清晰，通过枚举 $\sqrt{n}$ 内的因数减少枚举量。
    - **核心代码**：
```cpp
bool check(int x)
{
    string tmp = a.substr(0, x);
    b.clear();
    for(int i = 1; i <= n / x; i++) b += tmp;
    int cnt = 0;
    for(int i = 0; i!= n; i++) cnt += a[i]!= b[i];
    if(cnt <= 1) return true;
    cnt = 0; tmp = a.substr(x, x);
    b.clear();
    for(int i = 1; i <= n / x; i++) b += tmp;
    for(int i = 0; i!= n; i++) cnt += a[i]!= b[i];
    if(cnt <= 1) return true;
    else return false;
}

for(int i = 1; i * i <= n; i++)
{
    if(n % i == 0)
    {
        if(check(i)) ans = min(ans, i);
        if(check(n / i)) ans = min(ans, n / i);
    }
}
```
核心实现思想：定义 `check` 函数检查子串长度 $x$ 是否满足条件，通过枚举 $\sqrt{n}$ 内的因数 $i$，调用 `check` 函数检查 $i$ 和 $n / i$，更新最小长度 $ans$。

### 最优关键思路或技巧
- 利用子串长度是原字符串长度因数的性质，减少枚举量。
- 取前两个子串进行比较，避免遗漏情况。
- 枚举 $\sqrt{n}$ 内的因数，通过除法得到其他因数，进一步优化枚举效率。

### 拓展思路
同类型题可能会改变条件，如允许不同字符的数量增加，或者要求子串必须满足某种特定规则。解题思路仍然是枚举可能的子串长度，然后检查是否满足条件。

### 洛谷推荐题目
- P1368 工艺：求一个字符串的最小表示法，与本题都涉及字符串的重复和比较。
- P3375 【模板】KMP字符串匹配：考察字符串匹配算法，可用于判断子串是否重复出现。
- P5410 【模板】扩展 KMP（Z 函数）：同样是字符串匹配相关题目，可加深对字符串处理的理解。

---
处理用时：40.49秒