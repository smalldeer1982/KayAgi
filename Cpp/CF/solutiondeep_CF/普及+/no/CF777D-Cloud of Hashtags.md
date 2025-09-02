# 题目信息

# Cloud of Hashtags

## 题目描述

Vasya is an administrator of a public page of organization "Mouse and keyboard" and his everyday duty is to publish news from the world of competitive programming. For each news he also creates a list of hashtags to make searching for a particular topic more comfortable. For the purpose of this problem we define hashtag as a string consisting of lowercase English letters and exactly one symbol '\#' located at the beginning of the string. The length of the hashtag is defined as the number of symbols in it without the symbol '\#'.

The head administrator of the page told Vasya that hashtags should go in lexicographical order (take a look at the notes section for the definition).

Vasya is lazy so he doesn't want to actually change the order of hashtags in already published news. Instead, he decided to delete some suffixes (consecutive characters at the end of the string) of some of the hashtags. He is allowed to delete any number of characters, even the whole string except for the symbol '\#'. Vasya wants to pick such a way to delete suffixes that the total number of deleted symbols is minimum possible. If there are several optimal solutions, he is fine with any of them.

## 说明/提示

Word $ a_{1},a_{2},...,a_{m} $ of length $ m $ is lexicographically not greater than word $ b_{1},b_{2},...,b_{k} $ of length $ k $ , if one of two conditions hold:

- at first position $ i $ , such that $ a_{i}≠b_{i} $ , the character $ a_{i} $ goes earlier in the alphabet than character $ b_{i} $ , i.e. $ a $ has smaller character than $ b $ in the first position where they differ;
- if there is no such position $ i $ and $ m<=k $ , i.e. the first word is a prefix of the second or two words are equal.

The sequence of words is said to be sorted in lexicographical order if each word (except the last one) is lexicographically not greater than the next word.

For the words consisting of lowercase English letters the lexicographical order coincides with the alphabet word order in the dictionary.

According to the above definition, if a hashtag consisting of one character '\#' it is lexicographically not greater than any other valid hashtag. That's why in the third sample we can't keep first two hashtags unchanged and shorten the other two.

## 样例 #1

### 输入

```
3
#book
#bigtown
#big
```

### 输出

```
#b
#big
#big
```

## 样例 #2

### 输入

```
3
#book
#cool
#cold
```

### 输出

```
#book
#co
#cold
```

## 样例 #3

### 输入

```
4
#car
#cart
#art
#at
```

### 输出

```
#
#
#art
#at
```

## 样例 #4

### 输入

```
3
#apple
#apple
#fruit
```

### 输出

```
#apple
#apple
#fruit
```

# AI分析结果

### 题目内容
# 话题标签云

## 题目描述
瓦夏是“鼠标与键盘”组织公共页面的管理员，他日常职责是发布竞技编程领域的新闻。对于每一条新闻，他还会创建一个话题标签列表，以便更方便地搜索特定主题。在本题中，我们将话题标签定义为一个字符串，该字符串由小写英文字母组成，且恰好以符号'#'开头。话题标签的长度定义为不包含'#'符号的字符数量。

页面的总管理员告诉瓦夏，话题标签应该按字典序排列（查看注释部分了解定义）。

瓦夏很懒，所以他不想实际改变已发布新闻中话题标签的顺序。相反，他决定删除一些话题标签的后缀（字符串末尾的连续字符）。他可以删除任意数量的字符，甚至可以删除整个字符串，只保留'#'符号。瓦夏希望选择一种删除后缀的方式，使得删除的字符总数尽可能少。如果有多个最优解，他对其中任何一个都能接受。

## 说明/提示
长度为m的单词$a_{1},a_{2},...,a_{m}$在字典序上不大于长度为k的单词$b_{1},b_{2},...,b_{k}$，如果满足以下两个条件之一：
 - 在第一个位置$i$，使得$a_{i}≠b_{i}$，字符$a_{i}$在字母表中比字符$b_{i}$靠前，即在它们不同的第一个位置上，$a$的字符比$b$的字符小；
 - 如果不存在这样的位置$i$且$m<=k$，即第一个单词是第二个单词的前缀，或者两个单词相等。

如果一个单词序列中每个单词（除了最后一个）在字典序上都不大于下一个单词，则称该单词序列按字典序排序。

对于由小写英文字母组成的单词，字典序与字典中的字母顺序一致。

根据上述定义，如果一个话题标签仅由一个字符'#'组成，那么它在字典序上不大于任何其他有效的话题标签。这就是为什么在第三个样例中，我们不能保持前两个话题标签不变，而缩短另外两个。

## 样例 #1
### 输入
```
3
#book
#bigtown
#big
```
### 输出
```
#b
#big
#big
```

## 样例 #2
### 输入
```
3
#book
#cool
#cold
```
### 输出
```
#book
#co
#cold
```

## 样例 #3
### 输入
```
4
#car
#cart
#art
#at
```
### 输出
```
#
#
#art
#at
```

## 样例 #4
### 输入
```
3
#apple
#apple
#fruit
```
### 输出
```
#apple
#apple
#fruit
```

### 算法分类
贪心

### 题解综合分析与结论
所有题解都采用从后往前处理的贪心策略，即固定最后一个字符串，通过调整前面字符串的后缀，使整个序列满足字典序。各题解在实现细节上有所不同，部分题解利用STL函数如`substr`、`erase`，部分题解通过直接模拟比较过程来确定删除位置。

### 所选的题解
 - **作者：奥特战士 (5星)**
    - **关键亮点**：思路清晰，详细分析了两种实现方法及其效率差异。先介绍从后往前遍历并使用`substr`截取子串的方法，指出其效率问题，又提出从前往后比较并使用`erase`删除子串的优化方法，代码可读性高。
    - **核心代码实现思想**：法二通过从前往后比较相邻字符串，找到第一个不满足字典序的位置，删除该位置及之后的字符。
```cpp
for(int i=n;i>1;i--){
    int len=s[i-1].size();
    int j;
    bool f=0;
    for(j=0;j<len;j++){
        if(s[i][j]!=s[i-1][j]){
            if(s[i][j]>s[i-1][j])f=1;
            break;
        }
    }
    if(f)continue;
    if(j!=len)s[i-1].erase(j,len-j);
}
```
 - **作者：Zzzzzzzm (4星)**
    - **关键亮点**：采用从后往前模拟的思路，通过记录每个字符串的最优长度来确定最终输出。逻辑清晰，代码实现较为直接。
    - **核心代码实现思想**：从后往前比较相邻字符串，根据字符大小关系确定当前字符串的最优长度。
```cpp
for(int i = n; i > 1; i--){
    if(lenth[i] < lenth[i-1]){
        int flag = 0;
        for(int j = 1; j < lenth[i]; j++){
            if(s[i][j] > s[i-1][j]){
                flag = 1;
                break;
            }
            if(s[i][j] < s[i-1][j]){
                flag = 1;
                lenth[i-1] = j;
                break;
            }
        }
        if(!flag)
            lenth[i-1] = lenth[i];
        continue;
    }
    if(lenth[i] >= lenth[i-1]){
        for(int j = 1; j < lenth[i-1]; j++){
            if(s[i][j] > s[i-1][j]){
                break;
            }
            if(s[i][j] < s[i-1][j]){
                lenth[i-1] = j;
                break;
            }
        }
    }
}
```
 - **作者：ttq012 (4星)**
    - **关键亮点**：代码简洁明了，直接采用倒着贪心的策略，不断删除前一个字符串的最后一个字符，直到满足字典序关系。
    - **核心代码实现思想**：从后往前遍历，对每个字符串，当它大于后一个字符串时，不断删除自身最后一个字符。
```cpp
G(i, n - 1, 1) {
    while (s[i] > s[i + 1]) {
        s[i].pop_back();
    }
}
```

### 最优关键思路或技巧
采用从后往前的贪心策略，固定最后一个字符串，通过比较相邻字符串，确定每个字符串需要删除的后缀，以满足字典序要求。在实现上，可以利用STL函数简化操作，也可直接模拟比较过程，关键在于高效地确定删除位置。

### 可拓展之处
此类题目属于字符串贪心类型，常见套路是通过局部最优决策达到全局最优。类似题目通常会在字符串比较规则或限制条件上有所变化，解题时需把握贪心的核心思想，根据具体条件灵活调整策略。

### 相似知识点洛谷题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
 - [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)

### 个人心得摘录与总结
奥特战士提到`substr`函数在遍历过程中频繁调用效率不高，而`erase`函数可以优化这一过程，体现了对STL函数性能的思考。这提示在解题时不仅要实现功能，还需关注代码效率，合理选择数据结构和函数。 

---
处理用时：63.71秒