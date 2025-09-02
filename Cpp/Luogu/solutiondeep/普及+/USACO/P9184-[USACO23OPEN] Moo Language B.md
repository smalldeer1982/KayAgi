# 题目信息

# [USACO23OPEN] Moo Language B

## 题目描述

### 题目背景

FJ 对与奶牛更好地互动感兴趣，所以他决定学习 moo 语言！


moo 语言与英语相似，但更为简单。单词只有四种类型：名词、及物动词、不及物动词和连词，每两个单词之间必须用空格隔开。标点符号仅包含逗号和句号，它会跟在单词后面，若该标点符号后面存在单词，则需要隔一个空格再放单词。

对于每个句子，都需要遵循以下格式中的一条：

1. 名词+不及物动词。
2. 名词+及物动词+名词（可以有多个）。及物动词后面必须有至少一个名词。除及物动词后面的第一个名词外，后面的每个名词前面都必须加一个逗号。

也可以在两个句子之间加一个连词，形成复合句，复合句不能与其他句子用连词连接。每一个句子（包括复合句）都必须以句号结尾。

FJ 的词库中有 $N$ 个单词、$C$ 个逗号和 $P$ 个句号。每个单词的使用次数不能超过这个单词在词库中出现的次数。现在，你要帮他输出几个符合以上要求的句子，使总单词数尽量多。

每个输入文件中共包含 $T$ 组样例。

## 说明/提示

$1 \leq T \leq 100$，$1 \leq P, C \leq N \leq 10^3$。

- 输入 2-6：$N \leq 10$。
- 输入 7-11：$N \leq 100$。
- 输入 12-16：$N \leq 1000$。
- 输入编号除以 5 余 2 的测试点：没有及物动词。
- 输入编号除以 5 余 3 的测试点：没有不及物动词。
- 输入编号除以 5 余 4 的测试点：没有连词。

translated by [liyuanchen2021](https://www.luogu.com.cn/user/557680)

## 样例 #1

### 输入

```
3
1 1 1
bessie noun
10 5 4
bessie noun
taught transitive-verb
flew intransitive-verb
elsie noun
farmer noun
john noun
and conjunction
and conjunction
nhoj noun
mooed intransitive-verb
24 5 4
but conjunction
bessie noun
taught transitive-verb
flew intransitive-verb
elsie noun
farmer noun
john noun
and conjunction
and conjunction
nhoj noun
mooed intransitive-verb
bob noun
impressed transitive-verb
cow noun
impressed transitive-verb
leaped intransitive-verb
elsie noun
bella noun
buttercup noun
pushed transitive-verb
mooed intransitive-verb
envy noun
john noun
nhoj noun
```

### 输出

```
0

9
nhoj mooed. farmer taught elsie, bessie and john flew.
23
nhoj mooed. nhoj impressed john, farmer, elsie, bessie and cow impressed bob. bella pushed elsie and buttercup flew. envy mooed but john leaped.```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是围绕构造符合规则的句子，使总单词数尽量多。主要步骤包括计算句子总数、优先使用不及物动词构造句子、再使用及物动词构造句子、将不及物动词句子替换为及物动词句子、添加多余名词和逗号，最后使用连词连接句子。不同题解在实现细节和代码风格上有所差异，但整体思路一致。

### 所选题解
- **作者：_LRH_ (赞：5)，4星**
    - **关键亮点**：思路清晰，代码结构简洁，按照常规步骤实现了题目的要求，注释详细，易于理解。
- **作者：foryou_ (赞：2)，4星**
    - **关键亮点**：对构造语句和输出部分的思路阐述清晰，代码简洁明了，实现了贪心策略。
- **作者：raozf (赞：0)，4星**
    - **关键亮点**：对语法规则分析详细，思路步骤清晰，复杂度分析合理，代码实现规范。

### 重点代码及核心实现思想
#### 作者：_LRH_
```cpp
for (; a[0].size() && a[3].size() && h < p; sum += 2) {  
  ans[++h] = a[4];
  ans[h].push_back(a[0].back()), ans[h].push_back(a[3].back());
  a[3].pop_back(), a[0].pop_back();
} // 尽量多的不及物语句
for (l = h; a[0].size() >= 2 && a[2].size() && h < p; sum += 3) { 
  ans[++h] = a[4];
  ans[h].push_back(a[0].back()), ans[h].push_back(a[2].back());
  a[2].pop_back(), a[0].pop_back();
  ans[h].push_back(a[0].back()), a[0].pop_back();
} // 尽量多的及物语句
for (; l && a[0].size() && a[2].size(); l--, sum++) {
  ans[l].pop_back();
  ans[l].push_back(a[2].back()), ans[l].push_back(a[0].back());
  a[0].pop_back(), a[2].pop_back();
} // 尽量将不及物语句替换成及物语句
for (; l != h && a[0].size() && c; c--, sum++) {
  ans[h].push_back(a[0].back()), a[0].pop_back();
} // 在及物语句乃加入尽可能多的名词及逗号
```
核心思想：先构造不及物语句，再构造及物语句，然后将不及物语句替换为及物语句，最后在及物语句中添加多余名词和逗号。

#### 作者：foryou_
```cpp
for(;a[0].size()&&a[2].size()&&tot<p;sum+=2){ //使用不及物语句
  ans[++tot]=a[4];
  ans[tot].push_back(a[0].back()),ans[tot].push_back(a[2].back());
  a[0].pop_back(),a[2].pop_back();
}
for(ttot=tot;a[0].size()>=2&&a[1].size()&&tot<p;sum+=3){ //使用及物语句
  ans[++tot]=a[4];
  ans[tot].push_back(a[0].back()),ans[tot].push_back(a[1].back());
  a[0].pop_back(),a[1].pop_back();
  ans[tot].push_back(a[0].back());
  a[0].pop_back();
}
for(;ttot&&a[0].size()&&a[1].size();ttot--,sum++){  //尽量用及物语句替代不及物语句
  ans[ttot].pop_back();
  ans[ttot].push_back(a[1].back()),ans[ttot].push_back(a[0].back());
  a[0].pop_back(),a[1].pop_back();
}
for(;ttot!=tot&&a[0].size()&&c;c--,sum++) //添加名词和逗号
  ans[tot].push_back(a[0].back()),a[0].pop_back();
```
核心思想：与 _LRH_ 的思路一致，先构造不及物语句，再构造及物语句，然后替换语句，最后添加名词和逗号。

#### 作者：raozf
```cpp
for (; w[0].size() && w[3].size() && m < p; s += 2) {  // 使用不及物动词构造新句
  a[++m] = w[4];                                       // 创建新句
  a[m].push_back(w[0].back()), w[0].pop_back();        // 加入名词
  a[m].push_back(w[3].back()), w[3].pop_back();        // 加入不及物动词
}
for (l = m; w[0].size() >= 2 && w[2].size() && m < p; s += 3) {  // 使用及物动词构造新句
  a[++m] = w[4];                                                 // 创建新句
  a[m].push_back(w[0].back()), w[0].pop_back();                  // 加入名词
  a[m].push_back(w[2].back()), w[2].pop_back();                  // 加入及物动词
  a[m].push_back(w[0].back()), w[0].pop_back();                  // 加入名词
}
for (; l && w[0].size() && w[2].size(); l--, s++) {  // 将不及物动词句改造成及物动词句
  a[l].pop_back();                                   // 去掉不及物动词
  a[l].push_back(w[2].back()), w[2].pop_back();      // 加入及物动词
  a[l].push_back(w[0].back()), w[0].pop_back();      // 加入名词
}
for (; l != m && w[0].size() && c; c--, s++) {   // 加入多余的名词和逗号
  a[m].push_back(w[0].back()), w[0].pop_back();  // 加入名词
}
```
核心思想：同样是先构造不及物语句，再构造及物语句，然后替换语句，最后添加名词和逗号。

### 最优关键思路或技巧
- **贪心策略**：优先使用不及物动词构造句子，再使用及物动词构造句子，将不及物动词句子替换为及物动词句子，以增加单词数量。
- **分类存储**：使用数组或向量将不同类型的单词分类存储，方便后续操作。

### 可拓展之处
同类型题或类似算法套路：
- 字符串模拟题：给定一些规则，构造符合规则的字符串，如构造合法的表达式、密码等。
- 贪心算法题：在满足一定条件下，求最优解，如分配资源、安排任务等。

### 推荐题目
- P1047 [NOIP2005 普及组] 校门外的树
- P1223 排队接水
- P1090 [NOIP2004 提高组] 合并果子

### 个人心得
题解中未包含个人心得。

---
处理用时：45.13秒