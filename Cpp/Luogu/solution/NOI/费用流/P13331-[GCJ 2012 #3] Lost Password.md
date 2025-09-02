# [GCJ 2012 #3] Lost Password

## 题目描述

Ashish 忘记了自己的密码。他记得自己是用如下算法创建密码的：Ashish 从一段文本中取出最多 $k$ 个连续的单词，然后取每个单词的首字母。接着，他可能将其中一些字母替换为它们的“l33tspeak”变体。具体来说，他可能将 "o" 替换为 "0"，"i" 替换为 "1"，"e" 替换为 "3"，"a" 替换为 "4"，"s" 替换为 "5"，"t" 替换为 "7"，"b" 替换为 "8"，"g" 替换为 "9"。

例如，如果 Ashish 从《魔戒首部曲》（The Fellowship of the Ring）的第一句——"This book is largely concerned with Hobbits, and from its pages a reader may discover much of their character and a little of their history"——中取密码，则他会将其简化为 "tbilcwhafiparmdmotcaaloth"。那么密码可能是 "tbilcwh"、"7b1lcwh4f"、"a"、"4" 或 "4al07h" 等等。

Ashish 的浏览器安装了一个特殊扩展，这个扩展会阻止他的电脑上传任何包含其密码的字符串。为了找出自己密码所取的文本段落，Ashish 创建了一个网页来利用这个扩展。每秒钟，这个网页会让浏览器尝试上传一个该段落的“密码字符串”：这个字符串包含了从该段落可能生成的所有密码。一旦浏览器无法上传这样的字符串，Ashish 就知道密码取自哪里了。

例如，若 $k = 2$，而文本首字母为 "google"，那么该段落的一个密码字符串为 "goo0og00gle9o909l3"。原始字符串的所有长度不超过 $2$ 的子串，以及它们的 l33tspeak 变体，都包含在这个新字符串中。

给定某段文本所有单词的首字母，问该段落的“密码字符串”最少需要多少个字符？

## 说明/提示

**样例说明**

- 在第一个样例中，一个可能的密码字符串是 "0ppop0"。
- 在第二个样例中，一个可能的密码字符串是 "goo0og00gle9o909l3"。

**限制条件**

- $1 \leq T \leq 20$
- $S$ 至少包含 $2 \times k$ 个字符。
- 一定存在长度不超过 $10^{18}$ 的密码字符串。

**测试集 1（7 分，结果可见）**

- $S$ 最多包含 1000 个字符。
- $k = 2$。

**测试集 2（36 分，结果隐藏）**

- $S$ 最多包含 5000 个字符。
- $2 \leq k \leq 500$。

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
4
2
poppop
2
google
2
tbilcwhafiparmdmotcaaloth
10
tbilcwhafiparmdmotcaaloth```

### 输出

```
Case #1: 6
Case #2: 18
Case #3: 53
Case #4: 1136```

