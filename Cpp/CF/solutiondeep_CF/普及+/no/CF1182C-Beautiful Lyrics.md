# 题目信息

# Beautiful Lyrics

## 题目描述

You are given $ n $ words, each of which consists of lowercase alphabet letters. Each word contains at least one vowel. You are going to choose some of the given words and make as many beautiful lyrics as possible.

Each lyric consists of two lines. Each line consists of two words separated by whitespace.

A lyric is beautiful if and only if it satisfies all conditions below.

- The number of vowels in the first word of the first line is the same as the number of vowels in the first word of the second line.
- The number of vowels in the second word of the first line is the same as the number of vowels in the second word of the second line.
- The last vowel of the first line is the same as the last vowel of the second line. Note that there may be consonants after the vowel.

Also, letters "a", "e", "o", "i", and "u" are vowels. Note that "y" is never vowel.

For example of a beautiful lyric,

 "hello hellooowww" "whatsup yowowowow"

 is a beautiful lyric because there are two vowels each in "hello" and "whatsup", four vowels each in "hellooowww" and "yowowowow" (keep in mind that "y" is not a vowel), and the last vowel of each line is "o".For example of a not beautiful lyric,

 "hey man""iam mcdic"

 is not a beautiful lyric because "hey" and "iam" don't have same number of vowels and the last vowels of two lines are different ("a" in the first and "i" in the second).How many beautiful lyrics can you write from given words? Note that you cannot use a word more times than it is given to you. For example, if a word is given three times, you can use it at most three times.

## 说明/提示

In the first example, those beautiful lyrics are one of the possible answers. Let's look at the first lyric on the sample output of the first example. "about proud hooray round" forms a beautiful lyric because "about" and "hooray" have same number of vowels, "proud" and "round" have same number of vowels, and both lines have same last vowel. On the other hand, you cannot form any beautiful lyric with the word "codeforces".

In the second example, you cannot form any beautiful lyric from given words.

In the third example, you can use the word "same" up to three times.

## 样例 #1

### 输入

```
14
wow
this
is
the
first
mcdics
codeforces
round
hooray
i
am
proud
about
that
```

### 输出

```
3
about proud
hooray round
wow first
this is
i that
mcdics am
```

## 样例 #2

### 输入

```
7
arsijo
suggested
the
idea
for
this
problem
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
same
same
same
differ
```

### 输出

```
1
same differ
same same
```

# AI分析结果

### 题目翻译
# 优美歌词

## 题目描述
给定 $ n $ 个单词，每个单词都由小写字母组成。每个单词至少包含一个元音字母。你需要从这些给定的单词中选择一些，尽可能多地创作优美的歌词。

每首歌词由两行组成，每行由两个用空格分隔的单词组成。

一首歌词被认为是优美的，当且仅当它满足以下所有条件：
- 第一行的第一个单词中的元音字母数量与第二行的第一个单词中的元音字母数量相同。
- 第一行的第二个单词中的元音字母数量与第二行的第二个单词中的元音字母数量相同。
- 第一行的最后一个元音字母与第二行的最后一个元音字母相同。注意，元音字母后面可能有辅音字母。

此外，字母 "a"、"e"、"o"、"i" 和 "u" 是元音字母，注意 "y" 永远不是元音字母。

例如，"hello hellooowww" "whatsup yowowowow" 是一首优美的歌词，因为 "hello" 和 "whatsup" 中各有两个元音字母，"hellooowww" 和 "yowowowow" 中各有四个元音字母（记住 "y" 不是元音字母），并且每行的最后一个元音字母都是 "o"。

例如，"hey man" "iam mcdic" 不是一首优美的歌词，因为 "hey" 和 "iam" 的元音字母数量不同，并且两行的最后一个元音字母也不同（第一行是 "a"，第二行是 "i"）。

你能从给定的单词中写出多少首优美的歌词？注意，你使用每个单词的次数不能超过它的给定次数。例如，如果一个单词出现了三次，你最多只能使用它三次。

## 说明/提示
在第一个样例中，这些优美的歌词是可能的答案之一。让我们看看第一个样例输出中的第一首歌词。"about proud hooray round" 组成了一首优美的歌词，因为 "about" 和 "hooray" 的元音字母数量相同，"proud" 和 "round" 的元音字母数量相同，并且两行的最后一个元音字母也相同。另一方面，你不能用单词 "codeforces" 组成任何优美的歌词。

在第二个样例中，你不能从给定的单词中组成任何优美的歌词。

在第三个样例中，你最多可以使用单词 "same" 三次。

## 样例 #1
### 输入
```
14
wow
this
is
the
first
mcdics
codeforces
round
hooray
i
am
proud
about
that
```
### 输出
```
3
about proud
hooray round
wow first
this is
i that
mcdics am
```

## 样例 #2
### 输入
```
7
arsijo
suggested
the
idea
for
this
problem
```
### 输出
```
0
```

## 样例 #3
### 输入
```
4
same
same
same
differ
```
### 输出
```
1
same differ
same same
```

### 算法分类
排序、贪心

### 综合分析与结论
- **思路对比**：两位作者的思路整体相似，都是先对单词按照元音字母个数和最后一个元音字母进行排序，然后将符合条件的单词进行配对。redegg 使用队列存储配对信息，而 fly20040720 使用向量存储。
- **算法要点**：都需要统计每个单词的元音字母个数和最后一个元音字母，然后排序，再进行配对操作。
- **解决难点**：关键在于如何正确地对单词进行分类和配对，以满足优美歌词的条件。同时，要注意单词的使用次数不能超过给定次数。

### 题解评分
- **redegg**：3星。思路较清晰，但代码可读性一般，存在较多重复的代码逻辑。
- **fly20040720**：3星。思路清晰，代码结构相对较好，但在处理配对逻辑时，代码稍显复杂。

由于所有题解均不足4星，以下给出通用建议与扩展思路：
- **通用建议**：在处理这类字符串匹配问题时，要清晰地定义数据结构来存储关键信息，如元音字母个数和最后一个元音字母。排序是一种有效的预处理方法，可以方便后续的配对操作。在编写代码时，要注意代码的可读性和可维护性，避免过多的重复代码。
- **扩展思路**：可以考虑使用更高效的数据结构，如哈希表，来存储和查找符合条件的单词，以提高算法的效率。对于类似的字符串匹配问题，都可以先对字符串进行特征提取，然后根据特征进行分类和匹配。

### 重点代码
#### redegg 的核心代码
```cpp
// 统计每个单词的元音字母个数和最后一个元音字母
for(int i=1;i<=n;i++)
{
    cin>>in[i];
    a[i].id=i;
    int l=in[i].size();
    a[i].len=0;
    for(int j=0;j<l;j++)
    {
        if(in[i][j]=='a'||in[i][j]=='e'||in[i][j]=='i'||in[i][j]=='o'||in[i][j]=='u')
        {
            a[i].len++;
            a[i].last=in[i][j]-'a';
        }
    }
}
sort(a+1,a+1+n,cmp); // 排序
// 配对操作
for(int i=1;i<=n;i++)
{
    if(a[i].len==a[i+1].len&&a[i].last==a[i+1].last)
    {
        lq.push(a[i].id);
        lq.push(a[i+1].id);
        i++;
        continue;
    }
    lins.push(a[i].id);
    linsl.push(a[i].len);
}
```
核心实现思想：先统计每个单词的元音字母个数和最后一个元音字母，然后按照元音字母个数和最后一个元音字母排序，最后进行配对，将满足不同条件的单词对分别存储在不同的队列中。

#### fly20040720 的核心代码
```cpp
// 统计每个单词的元音字母个数和最后一个元音字母
REP (i, N)
{
    scanf("%s", buf);
    int len = strlen(buf);
    int cnt = 0;
    char last = 0;
    REP (j, len)
    {
        switch (buf[j])
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                cnt++;
                last = buf[j];
                break;
        }
    }
    v.push_back((Data){cnt, last, buf});
}
sort(v.begin(), v.end()); // 排序
// 配对操作
REP (i, v.size())
{
    if (i + 1 < (int)v.size() && v[i].cnt == v[i+1].cnt && v[i].last == v[i+1].last)
    {
        w.push_back(v[i]);
        w.push_back(v[i+1]);
        i++;
    }
    else
    {
        x.push_back(v[i]);
    }
}
```
核心实现思想：同样先统计每个单词的元音字母个数和最后一个元音字母，然后排序，再将满足不同条件的单词对分别存储在不同的向量中。

### 推荐洛谷题目
1. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：考察排序和去重。
2. [P1177 【模板】快速排序](https://www.luogu.com.cn/problem/P1177)：考察快速排序算法。
3. [P1271 【深基9.例1】选举学生会](https://www.luogu.com.cn/problem/P1271)：考察排序和统计。

### 个人心得
两位作者均未在题解中包含个人心得。

---
处理用时：47.16秒