# 题目信息

# Lecture

## 题目描述

你现在有一位新图论教授，你觉得他讲课讲的很好，但他说话实在是太快了，搞得你根本没有时间记笔记。所以呢，你有一个计划来跟上他讲课时的“脚步”，并记下重要的笔记。

你总共会两种语言：A 语言和 B 语言，教授用来讲课的是其中的 A 语言。A 语言和 B 语言有以下共同点：

- 它们都由若干小写字母构成；
- 每个单词里都不包括空格；
- 它们的长度都不超过 10。

另外，可以保证同一种语言中任意两个单词都有不同的拼写，且 A 语言的每一个单词与 B 语言中的每一个单词一一对应。

你的做笔记方式如下：

- 你必须写出写出教授给出的每一个单词；
- 为保证写单词用时最短，你必须要选择两种语言中单词长度更短的一个；
- 如果两个单词的长度一样，为保证讲课的原汁原味，你会选择第一种语言来做笔记。

我们会给你教授的演讲。而你呢，需要编一个程序来写出你的笔记。

## 样例 #1

### 输入

```
4 3
codeforces codesecrof
contest round
letter message
codeforces contest letter contest
```

### 输出

```
codeforces round letter round
```

## 样例 #2

### 输入

```
5 3
joll wuqrd
euzf un
hbnyiyc rsoqqveh
hbnyiyc joll joll euzf joll
```

### 输出

```
hbnyiyc joll joll un joll
```

# AI分析结果

### 题目分类
模拟

### 综合分析与结论
这些题解的核心思路都是根据题目要求，处理两种语言的单词对应关系，在记录教授演讲内容时选择长度更短的单词。大部分题解使用了 `map` 数据结构来存储单词的对应关系，以提高查找效率，时间复杂度为 $O(n + m)$；而 `Suuon_Kanderu` 的题解采用暴力枚举的方式，时间复杂度为 $O(n * m)$，效率较低。

### 所选题解
- **爬行者小郑**：5星。关键亮点在于思路清晰，代码简洁，直接利用 `map` 存储对应关系，避免了不必要的操作，且对 `map` 的使用解释详细。
- **ljm1621**：4星。关键亮点是思路明确，使用 `map` 解决问题，代码简洁易懂，还给出了亲测AC的记录链接。
- **Eason_AC**：4星。关键亮点是对题目分析清晰，使用 `map` 存储映射关系，代码逻辑清晰。

### 重点代码
#### 爬行者小郑
```cpp
map<string,string>ma;
int n,m;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        string a,b;
        cin>>a>>b;
        ma[a]=b;
        ma[b]=a;
    }
    for(int i=1;i<=n;i++)
    {
        string a;
        cin>>a;
        if(ma[a].size()<a.size())cout<<ma[a]<<" ";
        else cout<<a<<" ";
    }
    return 0;
}
```
核心实现思想：先使用 `map` 存储两种语言单词的对应关系，然后遍历教授演讲的单词，比较对应单词的长度，选择较短的单词输出。

#### ljm1621
```cpp
map<string,string> mapp;
int main()
{
    int n,m;
    string a,b;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b;
        mapp[a]=b;
        mapp[b]=a;
    }
    for(int i=1;i<=n;i++)
    {
        string s;
        cin>>s;
        if(mapp[s].length()<s.length())    cout<<mapp[s]<<" ";
        else                    cout<<s<<" ";
    }
    return 0;
}
```
核心实现思想：与爬行者小郑的思路类似，利用 `map` 存储对应关系，遍历演讲单词，根据长度选择输出。

#### Eason_AC
```cpp
int n, m;
string a, b, sp[3007];
map<string, string> mm1;

int main() {
    scanf("%d%d", &n, &m);
    while(m--) {
        cin >> a >> b;
        mm1[a] = b;
    }
    for(int i = 1; i <= n; ++i) {
        cin >> sp[i];
        if(mm1[sp[i]].size() < sp[i].size())	sp[i] = mm1[sp[i]];
    }
    for(int i = 1; i <= n; ++i)	cout << sp[i] << ' ';
}
```
核心实现思想：先将 `A` 语言的单词映射到 `B` 语言，然后遍历演讲单词，若 `B` 语言对应单词更短则替换，最后输出。

### 最优关键思路或技巧
使用 `map` 数据结构来存储两种语言单词的对应关系，利用其快速查找的特性，将查找时间复杂度从暴力枚举的 $O(m)$ 降低到 $O(1)$，提高了程序的效率。

### 拓展思路
同类型题目可能会有更多语言的对应关系，或者增加更多的条件限制，如单词的优先级等。类似的算法套路可以应用在需要处理对应关系的题目中，如翻译系统、同义词替换等。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：涉及模拟和贪心思想。
- [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)：模拟选择过程。
- [P1093 奖学金](https://www.luogu.com.cn/problem/P1093)：模拟排序和选择的过程。

### 个人心得摘录
- **Suuon_Kanderu**：强调了在判断单词长度时要用 `<` 而不是 `<=`，因为要保证讲课的原汁原味，自己就因为这个问题调试了半天。总结：在处理类似比较问题时，要仔细审题，注意比较条件的细节。 

---
处理用时：29.09秒