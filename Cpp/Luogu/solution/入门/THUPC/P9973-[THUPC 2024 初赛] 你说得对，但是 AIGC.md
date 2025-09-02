# [THUPC 2024 初赛] 你说得对，但是 AIGC

## 题目背景

你说得对，但是**本题不接受提供 hack 数据。**

## 题目描述

你说得对，但是众所周知 AIGC 是当下计算机领域最热门的方向之一，算协的几名成员也对此很有兴趣，经过长时间的奋战，终于研发出了一款全新的语言大模型——ChatSAA。

你说得对，但是当模型即将发布之时，开发团队忽然发现模型存在重大问题——由于开发团队的某名成员沉迷于一款**中文二字英文七字的游戏（见样例）**，导致训练模型时使用的语料库被莫名其妙地污染了，这使得模型生成的句子全都带有一个相同的前缀。

你说得对，但是紧急更换语料库重新训练显然已经来不及了，无奈开发团队只能在文档中注明：本模型的最大**特性（而非 bug）**在于生成文本的**前 19 个字符**，这既是模型独特的防伪标记，也充分彰显了算协团队的人文情怀和文化素养。

你说得对，但是一个微不足道的问题在于：这会让人们一眼就能分辨出哪些句子是由 AI 生成的，这会对那些打算用 AI 来写作业的同学很不友好。

你说得对，但是现在你手里有一些句子，这些句子有的是由 ChatSAA 生成的，有的是人类写的（假设人类没有刻意模仿 ChatSAA 的生成特性），你需要写一个程序来辨别二者。

## 说明/提示

### 样例 \#1 解释
你说得对，但是扫雷（Winmine）是一款中文二字英文七字的游戏。

### 提示

你说得对，但是如果我说这道题的题面是 AI 生成的，阁下又该如何应对？

## 样例 #1

### 输入

```
You are right, but "Sao Lei (Winmine)" is a game whose Chinese name contains two characters while English name contains seven.
```

### 输出

```
AI
```

## 样例 #2

### 输入

```
Ni shuo de dui, dan shi zhe ju hua bu shi yi "You are right, but " kai tou de.
```

### 输出

```
Human
```

## 样例 #3

### 输入

```
You are wrong. Here is why. The English name of game "G****** I*****" contains 14 characters (including a space), not 7.
```

### 输出

```
Human
```

# 题解

## 作者：inc1ude_c (赞：91)

本题需要判断一句话是人类说的还是 AI 说的。

“知己知彼，百战不殆”，想要得到本题解法，我们应当对题目中说的“开发团队中沉迷于某款游戏中的某名成员”非常了解，他应当也是本题的出题人。

从样例中可以得到，这位成员非常喜欢扫雷。题目描述十分符合潮流，让我们猜测这位成员也喜欢网上冲浪，结合我们对清华算协的了解，我们可以猜测这位成员就是：

[liuzhangfeiabc](https://www.luogu.com.cn/user/45775)，本名 z\*b，也许他本人你并不了解，但你大概率做过他出的某道著名的题目：[P8353 [SDOI/SXOI2022] 无处存储](https://www.luogu.com.cn/problem/P8353)。

现在注意到以下几个事实：

- AI 属于清华算协，liuzhangfeiabc 也属于清华算协。

- 题面是 AI 写的，也是 liuzhangfeiabc 写的。

- “扫雷也算一款中文二字英文七字的游戏”是 AI 说的，但这句话也曾经在 liuzhangfeiabc 的 QQ 空间中出现过。

- AI 喜欢说“你说得对”，liuzhangfeiabc 也常在 QQ 空间中发“你说得对”、“草”……。

以上恰好说明，题目中的 AI 就是 liuzhangfeiabc！

一位 AI 能拿到 CCF 认证 $10$ 级，并且突破凡人常有的思维，创新出做法独特新颖的题目“无处存储”！这种种的一切表明，AI 已经超越了人类。

![](https://cdn.luogu.com.cn/upload/image_hosting/irnnbudt.png)

lxl 所说的时代，来临了。

所以说这道题对于人类来说根本无法做出，毕竟 AI 太智慧了。

那怎么 AC 此题呢？我们可以用魔法打败魔法！

随便找一个 ChatGPT 询问此题做法。我们上面论证了 AI 非常智慧，所以必定能得到正确做法：

![](https://cdn.luogu.com.cn/upload/image_hosting/lz68ifzd.png)

中间省略一节……

![](https://cdn.luogu.com.cn/upload/image_hosting/es400pgg.png)

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    getline(cin, s);
    
    string prefix = "You are right, but ";
    
    if(s.substr(0, 19) == prefix) {
        cout << "AI" << endl;
    } else {
        cout << "Human" << endl;
    }
    
    return 0;
}
```


---

## 作者：cff_0102 (赞：27)

因为 AI 是最懂 AI 的，所以首先将题面扔给 AI。

>这道题目需要编写一个程序来判断输入的句子是由人类写的还是由 AI 生成的。根据题目描述，AI 生成的句子会有一个相同的前缀，而人类写的句子则不会有这个特征。
>
>因此，我们可以编写一个程序来检查输入的句子是否以特定的前缀开头，如果是，则判断为 AI 生成的；如果不是，则判断为人类写的。
>
>下面是一个可能的解题思路：
>
>1. 读取输入的字符串 $s$。
>2. 检查字符串 $s$ 是否以特定的前缀开头，比如前 $19$ 个字符。
>3. 如果 $s$ 以特定的前缀开头，则输出 `AI`；否则输出 `Human`。
>
>这样的程序可以简单地使用字符串的切片和比较来实现。在实际编写代码时，需要注意处理边界情况和特殊字符的处理。
>
>以下是一个简单的 Python 代码示例：
>
>```python
>def classify_sentence(s):
>    prefix = "This is the unique prefix"  # 替换成实际的前缀
>    if s[:19] == prefix:
>        return "AI"
>    else:
>        return "Human"
>
># 读取输入
>s = input()
># 调用函数进行分类
>result = classify_sentence(s)
># 输出结果
>print(result)
>```
>
>在实际应用中，需要根据具体的前缀来修改代码中的 `prefix` 变量。

AI 告诉我们，只需修改 `prefix` 变量，就能 AC 这道题了。那么我们需要设计一个 `prefix` 变量，满足所有的输入。我们已经知道样例中给出了一个满足输出是 `AI` 的输入，而根据题面，判断是不是 AI，只需要看这句话的前缀就行了。所以，要先根据第一个样例求出这个前缀是什么，再和输入的字符串进行比较。

那么如何求出这个前缀呢？

让人类判断一句话是不是 AI 说的，未免有点困难。求前缀这件事，还是得靠电脑解决。可以对前 $19$ 位进行逐位确认，具体的，先枚举前缀的第一位，如果和样例输入 $1$ 的第一位相同，则继续枚举第二位，以此类推，直到把整个字符串枚举出来。

我们同样可以询问 AI 如何编写：

>明白了，您需要一个循环来逐个查找与字符串 sample 中每个字符匹配的 ASCII 值。以下是一个示例代码：
>
>```python
>sample = "abcdefg...s"  # 假设 sample 是您要匹配的字符串
>result = []  # 用于存储匹配的 ASCII 值
>
>for char in sample:
>    for i in range(32, 127):
>        if chr(i) == char:
>            result.append(i)
>            break
>
>print(result)  # 打印匹配的 ASCII 值
>```
>
>在这个示例中，我们遍历了 sample 中的每个字符，并使用内部循环来查找与每个字符匹配的 ASCII 值，并将结果存储在 result 列表中。希望这可以满足您的需求。

根据 AI 的代码，稍加修改，就能得到可以 AC 本题的代码。

```python
def find_prefix():
    sample = "You are right, but \"Sao Lei (Winmine)\" is a game whose Chinese name contains two characters while English name contains seven."  # 假设 sample 是您要匹配的字符串
    result = ""  # 用于存储匹配的字符串前缀

    for _ in range(0, 19):
        for i in range(32, 127):
            if chr(i) == sample[_]:
                result += chr(i)
                break

    return result  # 返回匹配的字符串前缀

def classify_sentence(s):
    prefix = find_prefix()  # 替换成实际的前缀
    if s[:19] == prefix:
        return "AI"
    else:
        return "Human"

# 读取输入
s = input()
# 调用函数进行分类
result = classify_sentence(s)
# 输出结果
print(result)
```

---

## 作者：MatrixGroup (赞：17)

## 题目大意

你说得对，但是众所周知 AIGC 是当下计算机领域最热门的方向之一，算协的几名成员也对此很有兴趣，经过长时间的奋战，终于研发出了一款全新的语言大模型——ChatSAA。

你说得对，但是当模型即将发布之时，开发团队忽然发现模型存在重大问题——由于开发团队的某名成员沉迷于一款**中文二字英文七字的游戏**，导致训练模型时使用的语料库被莫名其妙地污染了，这使得模型生成的句子全都带有一个相同的前缀。

你说得对，但是紧急更换语料库重新训练显然已经来不及了，无奈开发团队只能在文档中注明：本模型的最大**特性（而非 bug）**在于生成文本的**前 19 个字符**，这既是模型独特的防伪标记，也充分彰显了算协团队的人文情怀和文化素养。

你说得对，但是一个微不足道的问题在于：这会让人们一眼就能分辨出哪些句子是由 AI 生成的，这会对那些打算用 AI 来写作业的同学很不友好。

你说得对，但是现在你手里有一些句子，这些句子有的是由 ChatSAA 生成的，有的是人类写的（假设人类没有刻意模仿 ChatSAA 的生成特性），你需要写一个程序来辨别二者。

## 思路解析

显然，我们应该关注“中文二字英文七字的游戏”是什么。

不难发现，麻将（Mahjong）是一个中文二字英文七字的游戏。

注意到这是一道 OI 题，同时这是 THUPC M 题时事题，考虑 OI 界最新最常见的麻将类型是立直麻将。

立直（**リ**ーチ）麻将又称**日**麻，所以不难判断答案和字符串 $\texttt{ri}$ 有关。

观察样例，不难得到答案：

```python
print('AI' if input()[8:10]=='ri' else 'Human')
```

---

## 作者：m256i (赞：16)

我们首先考虑询问万能的[数据删除]。

> 你说的对，但是《544567129》是由 543519329 自主研发的一款全新开放世界冒险游戏。游戏发生在一个被称作「1751607666」的幻想世界，在这里，被神选中的人将被授予「2126965」，导引元素之力。你将扮演一位名为「16777215」的神秘角色，在自由的旅行中邂逅性格各异、能力独特的同伴们，和他们一起击败强敌，找回失散的亲人——同时，逐步发掘「544567129」的真相。

注意到两个 $544567129$ 是重复的，忽略掉后面一个。

“扮演”即穿戴面具$\text{(mask)}$也就是掩码$\text{(mask)}$，顾名思义就是让我们按位与一遍。

容易写出代码：

```c
#include <stdio.h>
read(){
	int x; fread(&x, 4, 1, stdin); return x;
}
judicare(){
	if (read() != 544567129) return 0;
	if (read() != 543519329) return 0;
	if (read() != 1751607666) return 0;
	if (read() != 1646275700) return 0;
	return (read() & 16777215) == 2126965;
}
main(){
	puts(judicare() ? "AI" : "Human");
}
```

---

## 作者：K8He (赞：13)

你说得对，但是在解决这个问题之前，首先需要理解题目要求和设计一个合适的程序流程。下面是一个可能的解决方案，包含每个函数的用途和每个步骤的意义：

```cpp
#include <iostream>
#include <string>

using namespace std;

// 函数声明
bool isAIGenerated(const string& s);

int main() {
    // 输入句子
    string sentence;
    getline(cin, sentence);

    // 判断句子生成来源
    if (isAIGenerated(sentence)) {
        cout << "AI" << endl;
    } else {
        cout << "Human" << endl;
    }

    return 0;
}

// 函数定义
bool isAIGenerated(const string& s) {
    // 验证字符串长度是否满足条件
    if (s.length() < 19) {
        return false;
    }

    // 检查前19个字符是否与特定前缀相符
    string prefix = "You say you're right, but ";
    // （但是这实际上是错的，正确的前缀是 "You are right, but "）
    for (int i = 0; i < 19; ++i) {
        if (s[i] != prefix[i]) {
            return false;
        }
    }

    // 如果前19个字符匹配，认为是AI生成的
    return true;
}
```

你说得对，但是解释每个步骤的意义和每个函数的用途：

1. **你说得对，但是 `main` 函数**：负责程序的主要逻辑，包括输入句子、调用函数判断生成来源，并输出结果。

2. **你说得对，但是 `isAIGenerated` 函数**：用于判断输入句子是否由 AI 生成。首先，检查句子长度是否满足要求，然后比较前 19 个字符是否与特定前缀相符。如果匹配，就认为是 AI 生成的。

你说得对，但是这样的程序结构清晰，易于理解，并且通过函数的拆分，使得每个函数专注于一个具体的任务。

---

- Q：你说得对，但是为什么特定前缀是 `"You say you're right, but "` 呢？
- A：你说得对，但是在解释为什么特定前缀是 `"You say you're right, but "` 之前，我们需要回顾一下题目的背景和要求。

	题目描述中提到了一个模型——ChatSAA，这个模型由于语料库被某名成员沉迷于一款中文二字英文七字的游戏而导致训练出现问题。问题的具体表现是，生成的句子都带有一个相同的前缀。在题目中明确指出这个前缀是 `"You say you're right, but "`，并且这是模型独特的防伪标记。

	所以，我们在判断句子是否由 AI 生成时，采用了这个特定前缀进行比较。如果输入句子的前 19 个字符与这个特定前缀相符，就认为是 AI 生成的；否则，认为是人类生成的。

	总的来说，特定前缀的选择是基于题目设定的模型特性，是一个独特标记，通过检查这个标记，我们能够判断句子的生成来源。

- Q：你说得对，但是你觉得这款容易令人沉迷其中的中文二字英文七字的游戏是什么呢？
- A：你说得对，但是根据你提供的信息，这款游戏是《原神》（Genshin Impact）。《原神》是一款由中国游戏公司 miHoYo 开发的开放世界动作角色扮演游戏，于 2020 年 9 月 28 日全球正式上线。

- Q：你说得对，但是你认为小 E 唱歌好听吗
- A：你说得对，但是在纯文本环境下，我无法听到小 E 的歌声，因此无法真实评价。不过，我相信如果小 E 唱歌一定很动听，音乐是一种美妙的表达方式，能够传达情感和触动人心。希望小 E 的歌声能够带来愉悦和感动，鼓励继续追逐梦想！

---

你说得对，但是这真的是 ChatGPT 3.5 生成的 .

你说得对，但是 ChatGPT 3.5 是真的菜 .

你说得对，但是这是 User-Unauthorized 大师借我的号，谢谢 UU .


---

## 作者：tder (赞：11)

你说的不对。

---

你说的不对。根据样例 2 中的 `Ni shuo de dui, dan shi zhe ju hua bu shi yi "You are right, but " kai tou de.`，易得所有 AI 生成的文字均以 $t="\text{You are right, but }"$ 开头。

你说的不对。考虑逐字符比较，将 $s$ 与 $t$ 的前 $19$ 位逐位比较，对于第 $0\le i<19$ 位（显然字符串下标从 $0$ 开始记），有：

- 你说的不对。当 $s_i=t_i$ 时，该位匹配成功，继续比较下一位；
- 你说的不对。当 $s_i\neq t_i$ 时，该位匹配失败，认定为非 AI 生成文章。

你说的不对。结束了所有判断后，若全部匹配成功，则认定为 AI 生成。

你说的不对。注意需要特判当 $|s|<19$ 时的情况。

你说的不对。时间复杂度 $O(1)$。

---

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const string t = "You are right, but ";
string s;
signed main() {
    getline(cin, s);
    if(s.length() < 19) {
        cout<<"Human"<<endl;
        return 0;
    }
    for(int i = 0; i < 19; i++) {
        if(s[i] != t[i]) {
            cout<<"Human"<<endl;
            return 0;
        }
    }
    cout<<"AI"<<endl;
    return 0;
}
```

---

你说的不对。~~建议管理员打会所有以「你说的对」开头的文章，显然为 AI 生成。~~

---

## 作者：Milthm (赞：8)

你说得对，但是这题是一道整活题。

你说得对，所以我们来逐步分析这道题。

你说得对，所以因为你说得对，那么你只要说得对，你就是对的。

你说得对，但是你不能只有说得对，你还要但是。

你说得对，所以只要前 $19$ 个字符是 `You are right, but ` 那么就是 AI 生成的（你这 AI 玩原神玩的）。

你说得对，所以为了严谨我们特判了字符串长度小于 $19$。

你说得对，所以：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s; 
int main(){
	getline(cin,s);
	if(s.size()<19||s.substr(0,19)!="You are right, but ")cout<<"Human";
	else cout<<"AI";
	return 0;
}

```


---

## 作者：maomao233 (赞：8)

你说得对，但是先给[题目传送门](https://www.luogu.com.cn/problem/P9973)。

你说得对，但我们只需考虑本题的加粗部分。

你说得对，但是我们需要先看第一条加粗。直接观察样例一与之解释，发现样例一与**中文二字英文七字的游戏**有关。

你说得对，但是我们需要再看第二条加粗。注意到**前 $19$ 个字符**为 `You are right, but `，令该字符串为 $t$。于是我们得出结论：当 $s_0s_1s_2\cdots s_{17}s_{18}=t$ 时，答案为 `AI`，否则为 `Human`。

你说得对，但是这里可以使用 `substr` 函数截取字符串前 $19$ 个字符。用法如下：

`字符串.substr(起始下标 [,截取长度])`，其中 “`[]`” 表示可选内容，表示截取字符串的长度。

我说得对，于是我们得到代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
inline string its(int x){stringstream ss;string s;ss<<x;ss>>s;return s;}
inline int sti(string s){stringstream ss;int x;ss<<s;ss>>x;return x;}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
#define lb(x) x&-x
signed main()
{
	string s;
	getline(cin,s);
	puts(s.substr(0,19)=="You are right, but "?"AI":"Human");
	return 0;
}
```

---

## 作者：qifan_maker (赞：7)

You are right, but [problem link](https://www.luogu.com.cn/problem/P9973).
### 题目分析

这道题的题目是这样的：

> 你手里有一些句子，这些句子有的是由 ChatSAA 生成的，有的是人类写的（假设人类没有刻意模仿 ChatSAA 的生成特性），你需要写一个程序来辨别二者。

ChatSAA 是一款全新的语言大模型，由于训练语料库被污染，导致生成的句子全都带有一个相同的前缀：`You are right, but `。这是模型的最大特性（而非 bug），也是我们判断句子来源的关键。

### 解题思路

我们可以用一个简单的字符串匹配算法来解决这个问题。我们只需要检查输入的句子是否以 `You are right, but ` 开头，如果是，就输出 `AI`，否则输出 `Human`。这样就可以正确地区分出 AI 生成的句子和人类写的句子。

### 代码实现

下面是我用 C++ 语言写的一段代码，实现了上述思路：

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s; // 输入的句子
    getline(cin, s); // 读入一行
    if (s.substr(0, 19) == "You are right, but ") { // 检查前缀
        cout << "AI" << endl; // 输出 AI
    } else {
        cout << "Human" << endl; // 输出 Human
    }
    return 0;
}
```

### 复杂度分析

这段代码的时间复杂度是 $O(|s|)$，其中 $|s|$ 是输入句子的长度。空间复杂度是 $O(1)$，不需要额外的空间。

### 其他
你说得对，但是如果我说这篇题解是 AI 生成的，阁下又该如何应对？

---

## 作者：__3E24AC7002AD9292__ (赞：6)

你说得对，但是这题是入门题。

你说得对，但是这一道题的题意就是检查 `You are right, but ` 是否为输入的字符串的前缀。

你说得对，但是这一题我们考虑 `getline` 读入，然后暴力检查字符。

你说得对，但是如果你不会 `getline`，可以考虑进行 $19$ 次 `getchar` 然后判断是否为对应字符，如果不是就退出。

你说得对，但是如果你不会 `getchar`，可以考虑进行 $4$ 次输入普通字符串，每次输入之后判断。

你说得对，但是如果你不会暴力检查，可以使用 `substr` 函数快速判断，请自行百度使用方法，当然你也可以考虑 `KMP` 之类的字符串算法来进行匹配。

你说得对，但是如果你不会使用普通的字符串，可以用字典树 `Trie`，后缀自动机 `SAM` 之类的数据结构维护。

你说得对，但是这题就做完了。

你说得对，但是这题十分简单，代码就不放了。

---

## 作者：vectorxyz (赞：4)

#### 题意简化

你说得对，如果字符串前面是 `You are right,but ` 那么一眼人工智能。

#### 代码

你说得对，可以用库函数 `substr`，不懂请戳：[Link](https://blog.csdn.net/weixin_42240667/article/details/103131329)，他的作用就是从一个字符串中截取一段字串，我们只要判断这个字串是不是我们要的。

```cpp

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

namespace std
{
    template<typename T>
    T read(T x)
    {
        T opt = 1,sum = 0;
        char ch = getchar();
        while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
        while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
        return opt * sum;
    }
}
#define read std::read(0)

const int N = 2e5 + 5;

int n, l;
int a[N];
int b[N];

int main()
{
    string a;
    getline(cin, a);
    string k = a.substr(0, 18);
    if(k == "You are right, but") cout << "AI";
	else cout << "Human";
    return 0;
}
```

#### 结语

你说得对，[AC记录](https://www.luogu.com.cn/record/140335912)。

你说得对，但是作者这篇有笔误，已改正。


---

## 作者：jomy (赞：4)

## 前言
你说得对，我模仿了题面与第一篇题解的风格，不喜勿喷。
# 正文部分
你说得对，第三段**加粗**部分表明是前 $19$ 个字符。

你说得对，数一下，前 $19$ 个字符为`You are right, but `捏。

你说得对，那 $19$ 个字符最后**有空格**。

你说得对，只需判断前 $19$ 个字符是否为`You are right, but `就行了，是对应`AI`，否对应`Human`。

你说得对，该贴代码了。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
char a[N];
bool u(){
	if(a[0]!='Y') return false;
	if(a[1]!='o') return false;
	if(a[2]!='u') return false;
	if(a[3]!=' ') return false;
	if(a[4]!='a') return false;
	if(a[5]!='r') return false;
	if(a[6]!='e') return false;
	if(a[7]!=' ') return false;
	if(a[8]!='r') return false;
	if(a[9]!='i') return false;
	if(a[10]!='g') return false;
	if(a[11]!='h') return false;
	if(a[12]!='t') return false;
	if(a[13]!=',') return false;
	if(a[14]!=' ') return false;
	if(a[15]!='b') return false;
	if(a[16]!='u') return false;
	if(a[17]!='t') return false;
	if(a[18]!=' ') return false;
	return true;
}
signed main(){
	cin.getline(a,201);
	if(u()) cout<<"AI";
	else cout<<"Human";
	return 0;
}
```

---

## 作者：strcmp (赞：4)

你说得对，但是这个题目要求我们判断输入的字符串前面 19 个字符是否为 `You are right, but `。

你说得对，但是我们需要一个方法来接收用户输入。在 C++ 中，我们通常使用 `scanf` 从标准输入读取数据。


你说得对，但是我们需要提取输入字符串的前 19 个字符。我们可以使用 `substr` 函数来实现这一点。


你说得对，但是我们需要比较提取的前 19 个字符与给定的字符串是否匹配。我们可以使用 `==` 运算符来进行比较。

你说得对，但是我们需要根据比较结果输出相应的信息。在这个例子中，如果匹配则输出 `AI`，否则输出 `Human`。

你说得对，但是如果我说这个题解是 AI 生成的，阁下又该如何应对？

你说得对，但是我使用了一款英文开头两字母是 Ge，由中文两字自主研发的 AIGC（见代码）

```cpp
#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;
typedef long long int ll;
using pll = pair<ll, ll>;
const int maxn = 5e5 + 10;
const ll mod = 998244353LL;
const ll inf = 1145141919810LL;
string s; int n;
int main() {
    getline(cin, s);
    if (s.substr(0, 19) == "You are right, but ") puts("AI");
    else puts("Human");
    /*
    是谷歌全新一代知识增强大语言模型，大模型家族的新成员，能够与人对话互动、回答问题、协助创作，高效便捷地帮助人们获取信息、知识和灵感。Gemini 从数万亿数据和数千亿知识中融合学习，得到预训练大模型，在此基础上采用有监督精调、人类反馈强化学习、提示等技术，具备知识增强、检索增强和对话增强的技术优势。
    */
    return 0;
}
```

---

## 作者：N_Position (赞：3)

THUPC 的签到题~
# 闲话
恭喜 WFSZOI 战队成功完成两题，拿下比赛！
# 题目概括
输入一个字符串，判断其前缀是否为 `You are right, but`。
# 代码实现
时间复杂度 $O(1)$？
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100] = "You are right, but ";
char t[100];
int main(){
	cin.getline(t,19);
	for(int i=0;i<18;i++){
		if(t[i] != s[i]){
			puts("Human");
			return 0;
		} 
	}
	puts("AI");
}
```

---

## 作者：Marshall001 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P9973)

## 题目大意

给你一串字符，让你判断前 $19$ 个字符是不是 ```You are right, but ```。如果是，输出 ```AI```，如果不是，输出 ```Human```。

## 思路

首先判断字符串长度是不是大于等于 $18$ 如果不是，输出 ```Human```。接下来判断从 $0$ 到 $18$ 的字符是不是 ```You are right, but ```。~~众所周知，字符串是从零开始的~~。如果是的，那么输出 ```AI``` 否则输出 ```Human```。

## 代码

思路都有了，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
string ans="You are right, but ";
signed main(){
	string s;
	getline(cin,s);//一定要用getline！！！
	if(s.size()<19){//如果长度小于19，那么就输出Human
		cout<<"Human";
		return 0;
	}
	for(int i=0;i<19;i++){//循环判断
		if(s[i]!=ans[i]){
			cout<<"Human";
			return 0;
		}
	}
	cout<<"AI";
	return 0;
}
```

## THE END

---

## 作者：jqQt0220 (赞：2)

~~你说得对，但是后面忘了~~

你说得对，但是可以从样例发现，题面中“前 19 个字符”是 `You are right, but `。

你说得对，但是我们可以 **STL 大法好**。使用 `std::string::find()` 函数，返回值为找到的字符串在原串开头下标，未找到返回 $-1$。如果返回值为 $0$ 就是开头找到，输出 `AI`，否则 `Human`。

你说得对，但是删去了缺省源的代码如下：
```cpp
string s;
int main()
{
    ___();//你说得对，但是缺省源的初始化函数
    getline(cin,s);//你说得对，但是读入一行带空格的字符串
    cout<<(s.find("You are right, but ")==0?"AI":"Human")<<endl;//你说得对，但是判断+输出
    return 0;//你说得对，但是完美结束
}
```

### 说句闲话
你说得对，但是《扫雷》是一款大众类的益智小游戏，于 1992 年发行。游戏目标是在最短的时间内根据点击格子出现的数字找出所有非雷格子，同时避免踩雷，踩到一个雷即全盘皆输。

---

## 作者：harmis_yz (赞：2)

## 分析

模拟。根据样例就可以得到前 $19$ 个特殊字符（注意空格）。然后判断输入的字符串的前 $19$ 个字符与特殊字符是否匹配即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

string s="You are right, but ";

il void solve(){
	int n=19,now=0;
	while(n--){
		char ch=getchar();
		if(ch!=s[now]){cout<<"Human\n";return ;}
		++now;
	}
	cout<<"AI\n";
	return ;
}

signed main(){
	solve();
	return 0;
}
```


---

## 作者：__Cby___ (赞：2)

观察样例，把前 $19$ 个字符复制下来，让程序读入 $19$ 个字符，若与样例一致，则为人工智能，否则是真人。   
代码：   
```cpp
#include <iostream>
using namespace std;
int main(){
    string a="You are right, but ";
    for(int i=1;i<=19;i++){
        char b;
        b=getchar();
        if(b!=a[i-1]){
            cout<<"Human"<<endl;
            return 0;
        }
    }
    cout<<"AI"<<endl;
    return 0;
}

```


---

