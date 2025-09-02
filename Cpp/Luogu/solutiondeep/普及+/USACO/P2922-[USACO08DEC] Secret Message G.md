# 题目信息

# [USACO08DEC] Secret Message G

## 题目描述

Bessie is leading the cows in an attempt to escape! To do this, the cows are sending secret binary messages to each other.

Ever the clever counterspy, Farmer John has intercepted the first $b_i$ ($1 \le b_i \le 10,000$) bits of each of $M$ ($1 \le M \le 50,000$) of these secret binary messages.

He has compiled a list of $N$ ($1 \le N \le 50,000$) partial codewords that he thinks the cows are using. Sadly, he only knows the first $c_j$ ($1 \le c_j \le 10,000$) bits of codeword $j$.

For each codeword $j$, he wants to know how many of the intercepted messages match that codeword (i.e., for codeword $j$, how many times does a message and the codeword have the same initial bits). Your job is to compute this number.

The total number of bits in the input (i.e., the sum of the $b_i$ and the $c_j$) will not exceed  $500,000$.

贝茜正在领导奶牛们逃跑．为了联络，奶牛们互相发送秘密信息．

信息是二进制的，共有 $M$（$1 \le M \le 50000$）条，反间谍能力很强的约翰已经部分拦截了这些信息，知道了第  $i$ 条二进制信息的前 $b_i$（$1 \le b_i \le 10000$）位，他同时知道，奶牛使用 $N$（$1 \le N \le 50000$）条暗号．但是，他仅仅知道第 $j$ 条暗号的前 $c_j$（$1 \le c_j \le 10000$）位。

对于每条暗号 $j$，他想知道有多少截得的信息能够和它匹配。也就是说，有多少信息和这条暗号有着相同的前缀。当然，这个前缀长度必须等于暗号和那条信息长度的较小者。

在输入文件中，位的总数（即 $\sum b_i + \sum c_i$）不会超过 $500000$。

## 说明/提示

Four messages; five codewords. 

The intercepted messages start with 010, 1, 100, and 110.

The possible codewords start with 0, 1, 01, 01001, and 11.


0 matches only 010: 1 match

1 matches 1, 100, and 110: 3 matches

01 matches only 010: 1 match

01001 matches 010: 1 match

11 matches 1 and 110: 2 matches


## 样例 #1

### 输入

```
4 5 
3 0 1 0 
1 1 
3 1 0 0 
3 1 1 0 
1 0 
1 1 
2 0 1 
5 0 1 0 0 1 
2 1 1 
```

### 输出

```
1 
3 
1 
1 
2 
```

# AI分析结果

### 综合分析与结论
这些题解均围绕字典树（Trie树）来解决问题，核心思路是将已知的二进制信息构建成字典树，再用待查询的密码在字典树上进行匹配，统计匹配的信息数量。各题解在代码实现、变量命名和细节处理上存在差异，但整体思路一致。

### 所选题解
- **作者：户山香澄 (赞：85)，4星**
    - **关键亮点**：思路清晰，对字典树的构建和查询过程解释详细，代码结构简洁，注释丰富，易于理解。
    - **个人心得**：无
- **作者：yue__z (赞：63)，4星**
    - **关键亮点**：对字典树的原理和构建过程有详细的图文解释，有助于新手理解。代码实现规范，逻辑清晰。
    - **个人心得**：无
- **作者：HDWR (赞：1)，4星**
    - **关键亮点**：对查询过程中两种情况的分析详细，通过画图辅助理解，思路清晰。代码实现规范，有注释。
    - **个人心得**：在解释查询时两种情况的处理逻辑时，通过具体例子说明为什么要减去当前节点的`lasts`值，帮助理解。

### 重点代码
#### 户山香澄的题解
```cpp
struct cow{
    int nex[2],sum,end;
}t[500001];
// 建树
for (int i=1;i<=m;i++)
{
    int len;
    len=read();
    for (int j=1;j<=len;j++) a[j]=read();
    int now=1;
    for (int j=1;j<=len;j++) 
    {
        if (t[now].nex[a[j]]!=0) now=t[now].nex[a[j]];
        else
        {
            js++;
            t[now].nex[a[j]]=js;
            t[js].nex[1]=t[js].nex[0]=0;
            now=js;
        }
        t[now].sum++;
    }
    t[now].end++;
}
// 查询
for (int i=1;i<=n;i++)
{
    int len;
    len=read();
    for (int j=1;j<=len;j++) a[j]=read();
    int now=1,ans=0;
    bool flag=true;
    for (int j=1;j<=len;j++)
    {
        if (t[now].nex[a[j]]!=0) now=t[now].nex[a[j]];
        else 
        {
            flag=false;
            break;
        }
        ans+=t[now].end;
    }
    if (!flag) cout<<ans<<endl;
    else cout<<ans+t[now].sum-t[now].end<<endl;
} 
```
**核心实现思想**：使用结构体数组存储字典树节点，`nex`数组存储子节点信息，`sum`记录经过该节点的信息数量，`end`记录以该节点结尾的信息数量。建树时更新`sum`和`end`，查询时累加`end`，根据查询是否结束决定是否加上`sum - end`。

#### yue__z的题解
```cpp
int ch[500001][3],tot=1,bo[500001],sum[500001],x;
bool p[500001];
void add(bool p[]) {//插入字符串
    int u=1;
    for(int i=1; i<=k; i++) {
        int c=p[i];
        if(ch[u][c]==-1)ch[u][c]=++tot;
        u=ch[u][c];///它指向它的子节点
        sum[u]++;///经过该节点字符串个数
    }
    bo[u]++;///该字符串以u结尾
}
int find(bool p[]) {
    int u=1;
    int res=0;
    for(int i=1; i<=k; i++) {
        int c=p[i];
        if(ch[u][c]==-1)return res;
        u=ch[u][c];
        res+=bo[u];///加上与当前节点为结束的个数
    }
    return res-bo[u]+sum[u];//加上前缀相同且长度比它长的字符串个数
}
```
**核心实现思想**：使用二维数组`ch`存储字典树，`sum`记录经过该节点的字符串数量，`bo`记录以该节点结尾的字符串数量。插入时更新`sum`和`bo`，查询时累加`bo`，最后加上`sum - bo`。

#### HDWR的题解
```cpp
struct Trie {
    struct Node {
        int pass, lasts;
        int next[2 + 1];
        
        Node() {
            pass = lasts = 0;
            memset(next, 0, sizeof next);
        }
    } node[MAXN];
    
    int cnt;
    
    Trie() {
        cnt = 0;
    }
    
    void SwitchTo(int &now, bool data) {
        if (node[now].next[data] == 0) {
            node[now].next[data] = ++cnt;
        }
        now = node[now].next[data];
    }
    bool switchTo(int &now, bool data) {
        if (node[now].next[data] == 0) return false;
        now = node[now].next[data];
        return true;
    }
} t;
// 插入
for (int i = 1; i <= m; ++i) {
    int f = 0, pos = 0;
    cin >> f;
    for (int j = 1; j <= f; ++j) {
        int nf = 0;
        cin >> nf;
        t.SwitchTo(pos, nf);
        ++t.node[pos].pass;
    }
    ++t.node[pos].lasts;
}
// 查询
for (int i = 1; i <= n; ++i) {
    int f = 0, pos = 0, ans = 0;
    cin >> f;
    bool cont = true;
    for (int i = 1; i <= f; ++i) {
        int nf = 0;
        cin >> nf;
        if (cont && t.switchTo(pos, nf)) {
            ans += t.node[pos].lasts; // 沿途记录lasts的和
        } else cont = false; // 判断当前查询信息是否断掉了
    }
    if (cont) ans = ans - t.node[pos].lasts + t.node[pos].pass;
    cout << ans << endl;
}
```
**核心实现思想**：使用结构体嵌套存储字典树节点，`pass`记录经过该节点的信息数量，`lasts`记录以该节点结尾的信息数量。插入时更新`pass`和`lasts`，查询时累加`lasts`，根据查询是否结束决定是否减去`lasts`并加上`pass`。

### 最优关键思路或技巧
- **数据结构**：使用字典树（Trie树）来高效处理字符串前缀匹配问题，利用树的结构存储二进制信息，减少查询时间复杂度。
- **节点信息记录**：在字典树的每个节点记录经过该节点的信息数量和以该节点结尾的信息数量，方便统计匹配的信息数量。
- **查询逻辑处理**：在查询时，根据查询是否结束分为两种情况处理，避免重复计算。

### 可拓展之处
同类型题或类似算法套路：
- **多字符集字典树**：本题是二进制字典树，可拓展到多字符集的字典树，如26个英文字母的字典树。
- **AC自动机**：在处理多模式串匹配问题时，可使用AC自动机，它是在字典树的基础上结合KMP算法，能更高效地处理字符串匹配。

### 推荐题目
- [P2580 于是他错误的点名开始了](https://www.luogu.com.cn/problem/P2580)：基础的字典树应用，判断字符串是否存在。
- [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)：利用字典树求解异或问题。
- [P3879 阅读理解](https://www.luogu.com.cn/problem/P3879)：使用字典树进行单词查询。

### 个人心得摘录与总结
- **the_same_prayers**：提到用`gets()`在洛谷AC的经历，提醒注意输入函数的使用，不同输入函数可能存在兼容性问题。
- **HDWR**：通过具体例子和画图解释查询时两种情况的处理逻辑，强调画图辅助理解复杂问题的重要性。

---
处理用时：62.79秒