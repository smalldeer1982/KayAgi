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
这几道题解的核心思路都是围绕如何根据给定的单词和标点数量，构造出符合语法规则且单词数最多的句子。主要差异在于解决名词分配到不同句型这一难点的方式。有的题解采用贪心策略直接构造句子，有的则通过枚举句型数量来验证答案。

### 所选的题解
- **作者：_LRH_ (5星)**
    - **关键亮点**：思路清晰，利用贪心策略，先计算句子总数，优先使用不及物动词，再用及物动词，且尽量将不及物动词语句替换成及物动词的句子，最后添加名词和逗号，代码实现简洁明了。
    - **重点代码**：
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
for (; l!= h && a[0].size() && c; c--, sum++) {
    ans[h].push_back(a[0].back()), a[0].pop_back();
} // 在及物语句乃加入尽可能多的名词及逗号
```
    - **核心实现思想**：按顺序贪心构造不同类型句子，先构造不及物动词语句，再构造及物动词语句，之后将不及物动词语句替换为及物动词语句以增加单词数，最后在及物语句中添加名词和逗号。
- **作者：Error_Eric (4星)**
    - **关键亮点**：通过枚举句型1和句型2的个数，验证是否存在合法方案并计算最多单词数，思路独特，对难点的处理较为巧妙。
    - **重点代码**：
```cpp
void test(int s1,int s2){
    if(p*2<s1+s2||p+cj.size()<s1+s2) return; // 确保句号+连词够用，注意句号至少要占一半。
    int rn= nn.size()-s1-s2-s2, // 剩余的名词个数，<0表示当前尝试非法。
    uc= min((int)cj.size(),(s1+s2)/2), // 最多可以使用多少个连词
    nc= min({c,rn,(s2>0?inf:0)}), // n.s after comma
    res=s1*2+s2*3+nc+uc;
    if(/*rn>=0 && */nc>=0 && res > ans) 
        ans=res,ax=s1,ay=s2;
    return;
}
```
    - **核心实现思想**：枚举两种句型数量，根据现有单词和标点数量判断是否合法，计算当前条件下最多单词数并更新答案。
- **作者：raozf (4星)**
    - **关键亮点**：对语法规则分析透彻，采用由简至繁的构造策略，先计算句子总数，再依次构造不同类型句子，最后添加名词和逗号并计算连词数量，逻辑清晰。
    - **重点代码**：
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
```
    - **核心实现思想**：类似贪心构造，先构造不及物动词语句，再构造及物动词语句，然后将不及物动词语句转换为及物动词语句，以达到单词数最多。

### 最优关键思路或技巧
贪心策略在解决此类问题时较为有效，优先使用能消耗更多单词的句型，并根据单词和标点数量合理调整句子构造。如优先使用不及物动词构造句子，再用及物动词替换部分不及物动词语句，最后在及物语句中添加名词和逗号。枚举句型数量并验证答案的方法也为解决此类复杂分配问题提供了一种思路。

### 可拓展之处
同类型题通常围绕特定规则下的资源分配与组合优化，类似算法套路可应用于其他具有明确规则和资源限制的构造类问题，例如某些字符串构造、任务分配问题等。

### 相似知识点洛谷题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：贪心策略的应用，根据给定条件对物品进行分组。
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：涉及策略选择与资源分配，与本题思路有相似之处。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过贪心算法解决排队问题，与本题在利用规则优化结果上有相似性。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：48.60秒