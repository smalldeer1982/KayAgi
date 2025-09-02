# 题目信息

# Dima and Text Messages

## 题目描述

Seryozha has a very changeable character. This time he refused to leave the room to Dima and his girlfriend (her hame is Inna, by the way). However, the two lovebirds can always find a way to communicate. Today they are writing text messages to each other.

Dima and Inna are using a secret code in their text messages. When Dima wants to send Inna some sentence, he writes out all words, inserting a heart before each word and after the last word. A heart is a sequence of two characters: the "less" characters (<) and the digit three (3). After applying the code, a test message looks like that: <3 $ word_{1} $ <3 $ word_{2} $ <3 ... $ word_{n} $ <3.

Encoding doesn't end here. Then Dima inserts a random number of small English characters, digits, signs "more" and "less" into any places of the message.

Inna knows Dima perfectly well, so she knows what phrase Dima is going to send her beforehand. Inna has just got a text message. Help her find out if Dima encoded the message correctly. In other words, find out if a text message could have been received by encoding in the manner that is described above.

## 说明/提示

Please note that Dima got a good old kick in the pants for the second sample from the statement.

## 样例 #1

### 输入

```
3
i
love
you
<3i<3love<23you<3
```

### 输出

```
yes
```

## 样例 #2

### 输入

```
7
i
am
not
main
in
the
family
<3i<>3am<3the<3<main<3in<3the<3><3family<3
```

### 输出

```
no
```

# AI分析结果



【中文重写题目】
# Dima和短信

## 题目描述

Seryozha的性格变化无常。这次他拒绝离开房间让Dima和他的女友（顺便说一句，她叫Inna）独处。然而这对恋人总能找到沟通方式。今天他们正在互发短信。

Dima和Inna在他们的短信中使用了一种密码。当Dima想发送一句话时，他会写出所有单词，并在每个单词前以及最后一个单词后插入心形符号。心形符号由两个字符组成："<"和"3"。应用编码后的短信格式为：<3 $ word₁ $ <3 $ word₂ $ <3 ... $ wordₙ $ <3。

编码并未就此结束。之后Dima会在消息的任何位置插入任意数量的小写英文字母、数字、">"或"<"符号。

Inna非常了解Dima，所以她能提前知道Dima要发送的短语。现在Inna收到了一条短信，请帮她判断这条短信是否符合上述编码规则。

## 输入输出样例

样例1：
输入：
3
i
love
you
<3i<3love<23you<3

输出：
yes

样例2：
输入：
7
i
am
not
main
in
the
family
<3i<>3am<3the<3<main<3in<3the<3><3family<3

输出：
no

【算法分类】
字符串

【题解对比与结论】
各题解均采用以下核心思路：
1. 构造标准模式字符串：首尾各加<3，每个单词间加<3
2. 判断输入字符串是否包含该模式作为子序列

解决难点：
- 正确构造模式字符串（首尾都要有<3）
- 处理插入的随机字符不影响子序列判断
- 需要线性时间复杂度完成子序列验证

【高星题解推荐】
1. 作者：xzz_0611（★★★★☆）
   关键亮点：
   - 代码简洁，使用标准string操作
   - 明确说明子序列验证的核心逻辑
   - 包含完整的输入处理流程

2. 作者：InversionShadow（★★★★☆）
   关键亮点：
   - 最简洁的实现（仅15行核心代码）
   - 直接使用字符串拼接
   - 清晰的变量命名增强可读性

3. 作者：ZQIN_P（★★★★☆）
   关键亮点：
   - 包含完整的过程模拟说明
   - 独立封装比较函数增强可维护性
   - 提前处理长度不足的情况优化性能

【核心代码实现】
以InversionShadow的代码为例：
```cpp
int main() {
    int n;
    cin >> n;
    string ans = "<3", s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        ans += s + "<3";
    }
    string t;
    cin >> t;
    int cnt = 0;
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] == ans[cnt]) cnt++;
    }
    cout << (cnt == ans.size() ? "yes" : "no");
}
```
实现思想：
1. 构建目标模式字符串ans：初始为<3，每个单词后追加<3
2. 双指针遍历输入字符串，验证ans是否为其子序列

【拓展建议】
类似题目可练习：
1. P1039 字符串的展开 - 字符串构造与处理
2. P1308 统计单词数 - 子序列匹配变种
3. CF488B 子序列判断（Codeforces 488B）

【题解心得摘录】
1. Withershine："样例2错误原因是缺少单词而非多余字符，插入不影响判断"
   → 强调子序列验证的关键在于必须包含所有必要字符
2. ZQIN_P："提前处理长度不足情况优化性能"
   → 展示性能优化思路
3. WinterRain208："执行第三步前的字符串必须作为子序列存在"
   → 点明问题转化为子序列验证的核心思想

---
处理用时：52.89秒