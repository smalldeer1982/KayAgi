# 题目信息

# Spy Syndrome 2

## 题目描述

After observing the results of Spy Syndrome, Yash realised the errors of his ways. He now believes that a super spy such as Siddhant can't use a cipher as basic and ancient as Caesar cipher. After many weeks of observation of Siddhant’s sentences, Yash determined a new cipher technique.

For a given sentence, the cipher is processed as:

1. Convert all letters of the sentence to lowercase.
2. Reverse each of the words of the sentence individually.
3. Remove all the spaces in the sentence.

For example, when this cipher is applied to the sentence

Kira is childish and he hates losing

the resulting string is

ariksihsidlihcdnaehsetahgnisol

Now Yash is given some ciphered string and a list of words. Help him to find out any original sentence composed using only words from the list. Note, that any of the given words could be used in the sentence multiple times.

## 说明/提示

In sample case 2 there may be multiple accepted outputs, "HI there HeLLo" and "HI there hello" you may output any of them.

## 样例 #1

### 输入

```
30
ariksihsidlihcdnaehsetahgnisol
10
Kira
hates
is
he
losing
death
childish
L
and
Note
```

### 输出

```
Kira is childish and he hates losing 
```

## 样例 #2

### 输入

```
12
iherehtolleh
5
HI
Ho
there
HeLLo
hello
```

### 输出

```
HI there HeLLo 
```

# AI分析结果

### 题目内容
# Spy Syndrome 2

## 题目描述
在观察了间谍综合症的结果后，亚什意识到了自己的错误。他现在认为，像悉达特这样的超级间谍不可能使用像凯撒密码这样基础和古老的密码。经过数周对悉达特句子的观察，亚什确定了一种新的密码技术。

对于给定的句子，密码处理过程如下：
1. 将句子中的所有字母转换为小写。
2. 分别反转句子中每个单词。
3. 删除句子中的所有空格。

例如，当对句子“Kira is childish and he hates losing”应用此密码时，得到的字符串为“ariksihsidlihcdnaehsetahgnisol”。

现在亚什得到了一些加密后的字符串和一个单词列表。帮助他找出任何仅使用列表中的单词组成的原始句子。注意，给定的任何单词都可以在句子中多次使用。

## 说明/提示
在样例2中可能有多个可接受的输出，“HI there HeLLo”和“HI there hello”，你可以输出其中任何一个。

## 样例 #1
### 输入
```
30
ariksihsidlihcdnaehsetahgnisol
10
Kira
hates
is
he
losing
death
childish
L
and
Note
```
### 输出
```
Kira is childish and he hates losing 
```

## 样例 #2
### 输入
```
12
iherehtolleh
5
HI
Ho
there
HeLLo
hello
```
### 输出
```
HI there HeLLo 
```

### 算法分类
字符串、动态规划

### 题解综合分析与结论
这些题解主要围绕如何利用给定的单词列表去匹配经过特定加密变换后的字符串，以还原出原始句子。大多数题解采用动态规划的思路，结合不同的数据结构来优化匹配过程。难点在于高效地在加密字符串中找到由给定单词组成的组合方式。

### 所选的题解
- **作者：LittleAcbg (5星)**
    - **关键亮点**：思路清晰，详细阐述了动态规划的状态定义、转移方程以及时间复杂度分析，并介绍了字典树优化和路径压缩优化。利用字典树进行前缀检索，能快速判断子串是否存在；路径压缩优化空间使用。
    - **个人心得**：吐槽翻译不清晰，需通过样例理解题意。
    - **重点代码 - 字典树插入**：
```cpp
void insert(string s, int id) // 插入模板
{
    int p = 1;
    for (auto c : s)
    {
        if (!trie[p][work(c)])
            trie[p][work(c)] = ++tot;
        p = trie[p][work(c)];
    }
    reg[p] = id;
}
```
核心思想：遍历字符串s，若字典树当前节点不存在对应字符的子节点，则创建，最后在字符串结束节点记录单词编号。
    - **重点代码 - 动态规划及答案输出**：
```cpp
for (int i = 0; i < n; ++i)
{
    int p = 1;
    for (int j = i; j >= 0; --j)
    {
        if (!trie[p][work(s[j])]) break;
        p = trie[p][work(s[j])];
        if (!reg[p]) continue; // 不存在满足要求的k
        if (j!= 0 &&!ans[j - 1]) continue;
        ans[i] = reg[p];
        nxt[i] = j - 1;
        break;
    }
}
// 输出答案，这里使用的是for语句，i代表伪代码中的pos
for (int i = n - 1; i >= 0; i = nxt[i])
    cout << t[ans[i]] << ' ';
```
核心思想：从加密字符串头开始动态规划，利用字典树查找满足条件的子串，更新状态和记录路径，最后根据记录路径倒序输出单词还原句子。
- **作者：nao_nao (4星)**
    - **关键亮点**：采用AC自动机结合动态规划的方法。AC自动机能高效匹配多个子串，通过动态规划记录匹配方案，思路新颖且代码实现清晰。
    - **重点代码 - 字典树构建及AC自动机**：
```cpp
void add(int a)//建字典树，注意，要将所有大写字母转化为小写 
{
    int len = strlen(s+1),u = 1;
    for(int i = 1;i <= len;i ++){
        if(!ch[u][js(s[i])-'a']) ch[u][js(s[i])-'a'] = ++cnt;
        u = ch[u][js(s[i])-'a'];
    }
    vis[u] = a;
}

void build()//AC自动机，相信大家都懂 
{
    for(int i = 0;i < 26;i ++) ch[0][i] = 1;
    queue<int>q;
    q.push(1);
    while(!q.empty()){
        int u = q.front();q.pop();
        for(int i = 0;i < 26;i ++){
            if(!ch[u][i]){
                ch[u][i] = ch[nxt[u]][i];
            } else {
                nxt[ch[u][i]] = ch[nxt[u]][i];
                q.push(ch[u][i]);
            }
        }
    }
}
```
核心思想：add函数将单词插入字典树，记录单词编号；build函数构建AC自动机，设置失败指针。
    - **重点代码 - 动态规划及答案输出**：
```cpp
int find(int u,int a)
{
    if(!u) return 0;
    nxt[u] = find(nxt[u],a);
    if(vis[u]){
        if(dp[a+Len[vis[u]]]) dp[a] = vis[u];//在此处DP 
        return u;
    }
    return nxt[u];
}

void work()
{
    int u = 1;
    for(int i = strlen(S+1);i >= 1;i --){//倒序匹配，将主串中的单词全都正过来 
        u = ch[u][js(S[i])-'a'];
        find(u,i);
    }
}
//...
int len = strlen(S+1);for(int i = 1;i <= len;i += Len[dp[i]]){
    cout << str[dp[i]] << " ";
}
```
核心思想：work函数从加密字符串尾开始倒序匹配，find函数在匹配到单词结束节点时更新动态规划状态，最后根据动态规划结果输出还原句子。
- **作者：灵茶山艾府 (4星)**
    - **关键亮点**：使用trie树 + 记忆化搜索的方法，代码简洁明了。利用trie树存储单词，通过记忆化搜索减少重复计算，快速判断前缀能否拆分成单词。
    - **重点代码 - trie树插入及记忆化搜索**：
```go
func main() {
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()

    var n, m int
    var s, w string
    root := &node{} // 初始化 trie 树
    for Fscan(in, &n, &s, &m); m > 0; m-- {
        Fscan(in, &w)
        // 将单词的小写形式插入 trie 树
        o := root
        for _, c := range w {
            if c < 'a' {
                c += 32
            }
            c -= 'a'
            if o.son[c] == nil {
                o.son[c] = &node{}
            }
            o = o.son[c]
        }
        o.s = w // 末尾节点记录原单词
    }

    // 倒着记忆化搜索，dp[i] = 1 表示 s[0..i] 可以拆分成若干个单词，无法拆分则返回 -1
    dp := make([]int8, n)
    var f func(int) int8
    f = func(p int) (res int8) {
        if p < 0 {
            return 1
        }
        dv := &dp[p]
        if *dv!= 0 {
            return *dv
        }
        defer func() { *dv = res }()
        o := root
        for i := p; i >= 0; i-- {
            o = o.son[s[i]-'a']
            if o == nil {
                return -1 
            }
            if o.s!= "" && f(i-1) == 1 {
                Fprint(out, o.s, " ") // 找到合理拆分，直接打印
                return 1
            }
        }
        return -1
    }
    f(n - 1)
}
```
核心思想：先将单词插入trie树，记忆化搜索函数f从字符串末尾往前判断前缀能否拆分，若能拆分则输出单词，利用dp数组记录结果避免重复计算。

### 最优关键思路或技巧
1. **数据结构选择**：使用字典树（trie树）或AC自动机来存储单词列表，利用其前缀检索的特性，快速判断加密字符串中的子串是否为给定单词，从而优化匹配过程。
2. **动态规划**：定义合适的状态（如 `dp[i]` 表示前缀能否由给定单词组成），通过状态转移方程来记录和更新匹配方案，有效解决问题。
3. **记忆化搜索**：在搜索过程中记录已经计算过的状态，避免重复计算，提高算法效率。

### 同类型题或类似算法套路拓展
此类题目属于字符串匹配与组合问题，常见套路是结合动态规划与高效的数据结构（如字典树、AC自动机）来处理多个子串在主串中的匹配。类似题目通常会对字符串进行一些变换，然后要求还原或找出符合条件的组合。

### 洛谷相似题目推荐
1. **P3808 【模板】AC自动机（简单版）**：经典的AC自动机模板题，用于熟悉AC自动机的基本实现和应用。
2. **P2414 [NOI2011] 阿狸的打字机**：结合trie树和AC自动机，通过建立fail树解决复杂的字符串匹配计数问题。
3. **P5357 【模板】AC自动机（二次加强版）**：在基础AC自动机上增加了更多限制和要求，进一步提升对AC自动机应用的理解。 

---
处理用时：87.84秒