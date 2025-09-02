# [GCJ 2019 #1A] Alien Rhyme

## 题目描述

在一次外星探索中，你发现了外星诗歌的证据！你的语言学家团队确定，外星语言中的每个单词都有且只有一个字母带有重音；从重音字母开始到单词结尾的部分称为“重音后缀”。如果两个单词的重音后缀相同，则称这两个单词押韵。例如，单词 $\text{PROL}$ 和 $\text{TARPOL}$，如果它们的重音字母都是 $\text{o}$ 或 $\text{L}$，则它们押韵；但如果重音字母分别是 $\text{RS}$，或者 $\text{PROL}$ 的重音字母是 $\text{R}$ 而 $\text{TARPOL}$ 的重音字母是 $\text{P}$，又或者 $\text{PROL}$ 的重音字母是 $\text{O}$ 而 $\text{TARPOL}$ 的重音字母是 $\text{L}$，则它们不押韵。

你找回了一份包含 $N$ 个单词的列表，这些单词可能是外星诗歌的一部分。不幸的是，你并不知道每个单词的重音字母是哪一个。你可以选择丢弃零个或多个单词，对剩下的单词分配重音字母，然后将这些单词两两配对，使得每个单词只与它的配对单词押韵，并且不与其他配对中的单词押韵。

你想知道，最多能有多少个单词可以这样被配对。

## 说明/提示

**样例解释**

在样例 1 中，这两个单词可以通过合适的重音分配使其押韵，因此最大子集就是全部单词。

在样例 2 中，无论如何分配重音，都没有两个单词能押韵，因为任何两个后缀的最后一个字母都不同。因此最大子集为空，大小为 0。

在样例 3 中，如果将 `CODEJAM` 和 `JAM` 的重音都放在 `J` 上，将 `HAM` 和 `NALAM` 的重音都放在最后一个 `A` 上，将 `HUM` 和 `NOLOM` 的重音都放在 `M` 上，则可以使用全部单词。

在样例 4 中，任意两个单词都可以押韵，但总是通过把重音放在 `I` 上实现。因此，如果选取两个配对，来自不同配对的单词也会押韵。因此最多只能选取 2 个单词组成一个配对。

**数据范围**

- $1 \leq T \leq 100$。
- $1 \leq W_i$ 的长度 $\leq 50$。
- $W_i$ 仅包含大写英文字母。
- 对于同一测试用例，$W_i \neq W_j$，即单词不重复。

**测试点 1（10 分，可见）**

- $2 \leq N \leq 6$。

**测试点 2（27 分，隐藏）**

- $2 \leq N \leq 1000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2
TARPOL
PROL
3
TARPOR
PROL
TARPRO
6
CODEJAM
JAM
HAM
NALAM
HUM
NOLOM
4
PI
HI
WI
FI```

### 输出

```
Case #1: 2
Case #2: 0
Case #3: 6
Case #4: 2```

# 题解

## 作者：DevilsFlame (赞：4)

据题目要求，我们的字典树当然是反着建。

之后，我们会得到一棵树，我们拿样例 $3$ 举例：

![](https://cdn.luogu.com.cn/upload/image_hosting/lb96he7c.png)

标红的就是一个结尾。

我们要使得每个单词只与它的配对单词押韵，并且不与其他配对中的单词押韵。就是在原有的字符串选择一段后缀，使得有且只有唯一一个字符串所选出的后缀与之相同。  
不难想到贪心策略：让后缀越长越好。因为后缀越短，越有相同的可能。

```cpp
int dfs(int x) {
    int res = g[x];
    for(int i = 0;i < 26;i ++) if(t[x][i]) res += dfs(t[x][i]);
    if(res > 1) ans += 2,res -= 2;//满足已有两个字符串此时后缀相同，加入答案
    return res;//多余的留到之后计算答案
}
```
有一细节，后缀不能为空串，不需要我多说。注意多组数据要清空。

```cpp
        for(int i = 1;i <= n;i ++) {
            string a;
            cin >> a;
            add(a);
        }
        for(int i = 0;i < 26;i ++) if(t[0][i]) n = dfs(t[0][i]);//这里n的赋值没有意义，只是满足int类型函数返回值
        cout << "Case #" << tt << ": " << ans << '\n';
```

---

## 作者：ggpw_XNW (赞：3)

居然还没有题解，赶紧来一发。  
其实和正常字典树没什么区别，只是这里要求后缀，所以我们把字符串倒过来加入字典树。  
如何得出答案？  
其实也不难。后续遍历整棵字典树，如果能匹配就答案 $+2$，然后这个节点的父节点的计数数组要全部 $-2$，也就是减去以这个节点为根节点的子树的答案。  
至于为什么要后续遍历，样例的第 $3$ 个小数据就给出答案了。  
因为每个重音后缀只能匹配两个字符，而先序遍历可能会找到多个有相同的重音后缀的字符。虽然稍微处理一下也可以过，但是后序遍历更简单。
### code
```cpp
#include<iostream>
using namespace std;
int trie[5005][60] , len , cnt[5005] , n;
void insert(string s){
	int p = 0;
	for(int i=s.size()-1;i>=0;i--){
		int x = s[i] - 'A';
		if(trie[p][x]==0)trie[p][x] = ++len;
		p = trie[p][x] , cnt[p]++;
	}
}
int solve(int i){
    int res = 0;
    int tmp = 0;
    for(int c=0;c<26;c++){
        if(trie[i][c]){
            res += solve(trie[i][c]);
            tmp += cnt[trie[i][c]] - res;
        }
    }
    if(i!=0&&cnt[i]-res>=2)res += 2;
    return res;
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int T;cin >> T;
	for(int x=1;x<=T;x++){
		for(int i=0;i<=len;i++)for(int j=0;j<26;j++)trie[i][j] = 0 , cnt[i] = 0;
		len = 0;
		cin >> n;
		for(int i=1;i<=n;i++){
			string s;cin >> s;
			insert(s);
		}
		cout << "Case #" << x << ": " << solve(0) << "\n";
	}
	return 0;
}
```
~~话说为什么时限20s~~

---

## 作者：chinazhanghaoxun (赞：1)

# P13108 Alien Rhyme - Solution

## Problem Statement

给定 $N$ 个不同的字符串，求出满足以下配对方案的字符串个数：

- 每个单词与它的配对单词有共同的后缀
- 这个后缀不与其他配对中的单词后缀相同

## Analysis

看到要求后缀有关问题，想到字典树算法，只是这里需要从后向前遍历字符串构建字典树。

维护一个数组记录通过每个字符的字符串个数，在查询时从根开始向下贪心找可以使用的字符串即可。

## Approach

使用 $f$ 数组记录经过这个点的字符串个数，每次经过时 $f[now]\gets f[now]+1$ 就可以记录。

查询时，从根节点向下进行 $\text {DFS}$ 操作，向下过程中使用 $used$ 先记录当前使用过多少次，回溯到 $u$ 结点时判断 $f[u]-used \ge 2$。如果是，说明还有后缀未被占用过，$used\gets used+2$，继续向上。

最后输出 $used$ 就得到了所求答案。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=50005;
int tr[N][26],f[N],cnt;
string s;

int getnum(char x){
	return x-'A'+1;
}

void make_trie(){
    int now=1;
    cnt=1; 
    for(int i=s.size()-1;i>=0;i--){ //枚举后缀 
        int z=getnum(s[i]);
        if(!tr[now][z])
			tr[now][z]=++cnt;
        now=tr[now][z];
        f[now]++; //记录经过过这个点的字符串 
    }
}

int dfs(int u){
    int used=0;
    for(int i=1;i<=26;i++)
		if(tr[u][i])
      	  used+=dfs(tr[u][i]); //使用过的个数 
    if(u!=1 && f[u]-used>=2)
		used+=2; //匹配一对
    return used;
}

int main(){
    int T;
	cin>>T;
	int cases=1;
    while(T--){
        for(int i=1;i<=cnt;i++){ //初始化 
            fill(tr[i]+1,tr[i]+27,0); 
            f[i]=0;
        }
	    int n;
		cin>>n;
	    for(int i=1;i<=n;i++){
	        cin>>s;
	        make_trie(); //生成Trie树 
	    }
	    cout<<"Case #"<<cases<<": "<<dfs(1)<<"\n";
	    cases++;
    }
    return 0;
}
```

---

## 作者：Liliangxi (赞：1)

# [P13108 [GCJ 2019 #1A] Alien Rhyme](https://www.luogu.com.cn/problem/P13108)

## 前面的话

本人语言表达能力比较差，读者有不懂的地方可以仔细看看图理解一下。

# 题意

给出 $n$ 个单词，对于两个不同的单词，当有一个字母相同，且这个字母后面的一段后缀相同（可以为空），那么称这两个单词为互相押韵的，这个字母称之为重音字母，求最多有多少个配对单词。

需要注意的是，每个配对单词只与它的配对单词押韵，且一个单词中只有一个重音字母。

多组数据。

# solution

首先反着建字典树，这可以通过~~标签~~观察题意比容易的发现。

图比较丑，但能看，紫色是一个单词的结尾（~~或者应该叫原单词的开头~~）。

先看样例三：

![1](https://cdn.luogu.com.cn/upload/image_hosting/2n4ne6c4.png)

首先比较容易发现，如果**两个单词在字典树上构成一条链**，那么肯定这**两个单词可以配对且这样配对最优**，那如果有三个单词在同一条链上呢，那么我们就取较为下面的两个单词配对，这个是较容易能想到的，那四个单词呢，那么深度更深的两个单词配对，深度较浅的两个单词配对，由此，我们想出来了一个贪心：

- 如果完整的字典树是一条链，那么肯定从深度深的开始取，这是一定最优的。

但是构建出来的字典树基本上不会是一条链，那么考虑扩展这个贪心，观察上图，发现我们总结出的贪心适用于 `MAJEDOC` 这一条链，那么对于另外的两条链（比较靠近的）`MAH` 和 `MALAN`也能组成一组配对单词，且已经是最优了，可以尝试手模一下。而另外的两条 `MUH` 和 `MOLON` 也能组成一对，且最优。

至此，我们已经可以发现一些规律了：

- 对于任意两个单词结束的位置（当然不能完全没有公共后缀），要使得他们的 LCA 深度最浅便是最优的。

我们现在想出来了贪心，但似乎没法确定如何最优的去选两个结束位置，总不能暴力的去枚举吧。

这个时候我们注意到题目只要求求多少个配对单词，那么我们尝试考虑对于一棵树如何求，首先考虑 dfs，如上图中的 `MAJEDOC` 这一条链，我们发现当回溯到 `J` 这一个点的时候可以完成配对，此时这个节点（包括自己在内）的子树上有两个结束点（就这样叫吧），再根据我们发现的贪心规律，可以知道此时这两个结束点配对一定是最优的，那么我们直接计入答案即可，从此处也可以发现确实是使用 dfs 遍历树，那么记完答案之后，那个存储结束点的变量也要减去。

那么这样就对了吗，统计一颗子树内的结束点，减去小于结束点数量的最大的偶数，并在记录变量减去，但是我们接着发现，如果这样操作，那好像只用判断单词数的奇偶就好了，这显然是不对的，那来看看样例四：

![1](https://cdn.luogu.com.cn/upload/image_hosting/3elyar7n.png)

对于 `P`、`H`、`W`、`F` 这四个结束点为根的树中结束点数都小于二，于是向上传递，此时以节点 `I` 为根的树的结束点数量是 $4$，显然不能都加上，否则就违反了题目：

> 需要注意的是，每个配对单词只与它的配对单词押韵，且一个单词中只有一个重音字母。

所以我们只能将答案加上 $2$，记录节点数的变量减去 $2$，由此，我们发现对于一棵树的根节点，再遍历完其所有子孙节点后，若结束点数量小于 $2$，就直接向上传递结束点数量，否则哪怕有 $114514$ 个结束点数，答案和记录变量也只能改变 $2$ 之后向上传递，否则就违反了题意。

至此，便可以完成这道题目，注意后缀不能为空和其他的一些小细节。

## Code

纯净无毒，但码风不好看，细节注释里大部分有。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lll unsigned long long
#define dou long double
#define St string
#define pi pair<int, int>
#define mkp make_pair
#define PI acos(-1)
#define eps 1e-10
#define endl "\n"
#define INF 2147483647
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1011;

int T, n, ans;
char s[51];
struct trie
{
    struct unit             //比较丑陋的写法
    {
        int a[31], val;
    }ch[N * 31 * 50];
    int top;

    void init()
    {
        for (int i = 0; i <= top; i++)          //这样比 memset 快很多
        {
            for (int j = 1; j <= 26; j++)
            {
                ch[i].a[j] = 0;
                ch[i].val = 0;
            }
        }
        top = 0;
    }

    void insert(char s[], int len)
    {
        int pos = 0;
        for (int i = len; i >= 1; i--)      //倒序
        {
            int opt = s[i] - 'A' + 1;
            if(!ch[pos].a[opt]) ch[pos].a[opt] = ++top;
            pos = ch[pos].a[opt];
        }
        ch[pos].val++;                  //结束点标记
    }

    int dfs(int step)
    {
        int x = ch[step].val;       //别忘了自己
        for (int i = 1; i <= 26; i++)
        {
            if(ch[step].a[i]) x += dfs(ch[step].a[i]);      //子树结束点
        }
        if(x >= 2)      //哪怕有 114514 个，也只能答案加上 2
        {
            ans += 2;
            x -= 2;
        }
        return x;
    }
}t;


signed main()
{
    IOS;
    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        ans = 0;
        t.init();       //多测不清空,就要见祖宗
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> (s + 1);
            t.insert(s, strlen(s + 1));
        }
        for (int i = 1; i <= 26; i++)           //不能没有重音字母，但是公共后缀可以为空
        {
            if(t.ch[0].a[i]) t.dfs(t.ch[0].a[i]);
        }
        cout << "Case #" << k << ": " << ans << endl;
    }
    return 0;
}
```

---

