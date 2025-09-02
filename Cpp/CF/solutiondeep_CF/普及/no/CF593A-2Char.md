# 题目信息

# 2Char

## 题目描述

Andrew often reads articles in his favorite magazine 2Char. The main feature of these articles is that each of them uses at most two distinct letters. Andrew decided to send an article to the magazine, but as he hasn't written any article, he just decided to take a random one from magazine 26Char. However, before sending it to the magazine 2Char, he needs to adapt the text to the format of the journal. To do so, he removes some words from the chosen article, in such a way that the remaining text can be written using no more than two distinct letters.

Since the payment depends from the number of non-space characters in the article, Andrew wants to keep the words with the maximum total length.

## 说明/提示

In the first sample the optimal way to choose words is {'abb', 'aaa', 'bbb'}.

In the second sample the word 'cdecdecdecdecdecde' consists of three distinct letters, and thus cannot be used in the article. The optimal answer is {'a', 'a', 'aaaa'}.

## 样例 #1

### 输入

```
4
abb
cacc
aaa
bbb
```

### 输出

```
9```

## 样例 #2

### 输入

```
5
a
a
bcbcb
cdecdecdecdecdecde
aaaa
```

### 输出

```
6```

# AI分析结果



# 2Char

## 题目描述

Andrew 经常阅读他最喜欢的杂志 2Char 中的文章。这些文章的主要特点是每篇文章最多使用两个不同的字母。Andrew 决定向该杂志投稿一篇文章，但他没有写过任何文章，于是从杂志 26Char 中随机选择了一篇文章。在投稿到 2Char 之前，他需要通过删除部分单词来调整文本格式，使得剩余文本可以用不超过两个不同的字母书写。稿费取决于文章中非空格字符的数量，因此 Andrew 希望保留总长度最大的单词集合。

## 说明/提示

第一个样例中，最优选择是 {'abb', 'aaa', 'bbb'}。

第二个样例中，单词 'cdecdecdecdecdecde' 包含三个不同字母，无法使用。最优解是 {'a', 'a', 'aaaa'}。

## 样例 #1

### 输入

```
4
abb
cacc
aaa
bbb
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5
a
a
bcbcb
cdecdecdecdecdecde
aaaa
```

### 输出

```
6
```

---

**算法分类**：枚举

---

### 题解分析与结论

所有题解均采用暴力枚举两个字母组合的思路，差异主要在于预处理优化方式。核心思路为：
1. 枚举所有可能的两个字母组合（共 C(26,2) 种）
2. 统计所有仅由这两个字母构成的单词总长度
3. 取所有情况的最大值

---

### 高星题解推荐

#### 题解作者：Ninelife_Cat（★★★★☆）
**关键亮点**：代码简洁直观，直接枚举字母对并遍历单词检查字符合法性。  
**核心代码**：
```cpp
for(char i='a';i<='z';i++)
    for(char j=i+1;j<='z';j++) {
        int sum=0;
        for(int k=1;k<=n;k++) {
            bool f=false;
            for(char c : a[k]) 
                if(c!=i && c!=j) {f=true; break;}
            if(!f) sum += a[k].length();
        }
        ans = max(ans, sum);
    }
```
**实现思想**：三重循环分别枚举字母对、遍历单词、检查字符是否合法。时间复杂度 O(26²nL)，L为单词平均长度。

#### 题解作者：MuYC（★★★★☆）
**关键亮点**：预处理字符出现情况优化判断效率，使用二维数组存储每个单词的字符分布。  
**核心代码**：
```cpp
for(int i=1;i<=26;i++)
    for(int j=i+1;j<=26;j++) {
        int ans=0;
        for(int k=1;k<=n;k++) {
            int flag=1;
            for(int l=1;l<=26;l++)
                if(l!=i && l!=j && book[k][l]) flag=0;
            ans += flag * strlen(a[k]);
        }
        Maxlen = max(Maxlen, ans);
    }
```
**实现思想**：预处理每个单词的字符出现情况到`book`数组，将单词合法性判断优化为 O(26) 次查表操作。

---

### 最优思路总结
**关键优化技巧**：预处理单词字符集合，将单次字符检查复杂度从 O(L) 降为 O(1)。例如通过桶标记或集合存储每个单词的字符种类，枚举字母对时只需判断该集合是否为枚举字母的子集。

**思维模式**：在小数据范围（n≤100）下，优先选择代码复杂度低的暴力法。预处理技巧可有效减少重复计算，适用于多次查询的场景。

---

### 同类题目推荐
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102) - 枚举差值组合
2. [P3391 字符串哈希](https://www.luogu.com.cn/problem/P3391) - 字符集预处理技巧
3. [P2925 干草出售](https://www.luogu.com.cn/problem/P2925) - 有限集合枚举优化

---
处理用时：64.40秒