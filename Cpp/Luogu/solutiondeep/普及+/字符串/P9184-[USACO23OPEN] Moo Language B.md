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
这几道题解的核心思路都是围绕如何根据给定的单词和标点数量，按照特定语法规则构造出单词数最多的句子。
1. **思路**：多数题解先计算可构造的句子总数，优先使用不及物动词构造句子，再用及物动词构造，之后将不及物动词语句替换为及物动词语句，最后添加名词和逗号，并考虑连词的使用。Error_Eric 的题解采用枚举两种句型个数的方式，与其他贪心思路略有不同。
2. **算法要点**：对单词按类型分类存储，通过循环操作各类单词数量来构造句子，同时注意标点符号的使用规则和数量限制。
3. **解决难点**：核心难点在于如何合理分配名词到不同句型中。多数题解通过贪心策略，先尽可能构造简单句型，再进行调整。Error_Eric 通过枚举句型数量来确定合法方案及最优解。

### 所选的题解
- **作者：_LRH_ (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，对各类情况处理细致，直接采用贪心策略解决问题，符合一般解题思维。
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
    - **核心实现思想**：依次按贪心策略，先构造不及物动词语句，再构造及物动词语句，接着将不及物动词语句替换为及物动词语句，最后在及物语句中添加名词和逗号。
- **作者：Error_Eric (4星)**
    - **关键亮点**：通过枚举两种句型个数，验证是否存在合法方案并找出最优解，提供了不同于贪心的另一种解题思路。
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
    - **核心实现思想**：在枚举句型 1 和句型 2 的个数后，通过该函数验证当前句型数量下，句号、连词、名词数量是否满足要求，并计算当前条件下最多的单词数。

### 最优关键思路或技巧
贪心策略是解决本题的有效方法，先从简单句型构造开始，逐步调整优化，合理利用各类单词和标点符号。同时，Error_Eric 的枚举验证思路也提供了一种解决此类复杂分配问题的方向。

### 可拓展之处
同类型题目通常围绕特定规则下的资源分配与组合优化，类似算法套路为贪心策略或枚举验证。例如在资源有限的情况下，按一定规则构造最大价值的组合。

### 相似知识点洛谷题目
1. **P1094 [NOIP2007 普及组] 纪念品分组**：涉及物品分组的贪心策略，与本题单词按规则组合类似。
2. **P1106 删数问题**：通过贪心策略解决数字删除问题，锻炼贪心思维。
3. **P1223 排队接水**：根据接水时间贪心排序，与本题合理分配资源思路相似。 

---
处理用时：37.06秒