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

# 题解

## 作者：LittleAcbg (赞：6)

# 题目大意

**吐槽一下现在的翻译，十分不清晰，只能通过样例理解。**

一个只含大小写字母与空格的句子，进行如下变换：

- 将所有字母替换成小写
- 将每个单词翻转
- 删除所有空格

现在给出句子变换后形成的字符串 $s$ 与可能构成原句的 $m$ 个字符串 $t_i$，要求给出一种可能的原句，每个字符串 $t_i$ 可以多次使用，保证有解。

例如 `Kira is childish and he hates losing` 构成的字符串 $s$ 为 `ariksihsidlihcdnaehsetahgnisol`。

# 题目解法

为了方便计算，将 $s$ 字符串整个进行翻转，此时所有字符串按照：

- 单词顺序与原来相反
- 每个单词都是正序，但全为小写

例如 `Kira is childish and he hates losing` 构成的字符串 $s$ 经过反转后为 `losinghatesheandchildishiskira`。对其进行人为分割可得 `losing hates he and childish is kira`。

以下部分书写 $s$ 默认为已经翻转的 $s$，记号 $s[l..r]$ 表示 $s$ 中下标 $l \sim r$ 的子串。

$f[i]$ 表示 $s[0..i]$ 是否可由若干个 $t_j$ 组成，$ans[i]$ 为 vector，表示构成 $s[0..i]$ 使用的 $t_j$ 编号。

例如 $s$ 为 `youmeettonicehello`，$m=9$，$7$ 个字符串分别为：

- $t_1=$ `HeLLo`
- $t_2=$ `tO`
- $t_3=$ `noise`
- $t_4=$ `I`
- $t_5=$ `You`
- $t_6=$ `u`
- $t_7=$ `NICE`
- $t_8=$ `meat`
- $t_9=$ `mEEt`

注意到 $s$ 有 $18$ 个字符但下标从 $0$ 到 $17$，此时 $ans[17]$ 唯一的一种情况是：$ans[17]=\{5,9,2,7,1\}$。

计算 $f[i]$ 时，暴力找是否存在一个位置 $j < i$ 满足：

- 存在一个 $k \le m$ 使得 $s[j+1..i] = t_k$
- $f[j]$ 为真

如果能找到即 $f[i]$ 为真，并且令 $ans[i]$ 为 $ans[j]$ 并在（$ans[i]$ 的）尾部添加满足要求的 $k$。

输出答案时**倒序**输出 $ans[n-1]$ 即可。

时间复杂度 $\text O(n^3 m)$（注意到暴力找为 $\text O(n^2)$，判断是否存在 $k$ 的时间复杂度为 $\text O(nm)$）

可以考虑使用 `map`，可以将时间复杂度优化到 $\text O(n^3 \log_2 m)$。

# 字典树

字典树的好处在于可以进行**前缀检索**。

每次计算 $f[i]$，按照 $j$ 从大到小的顺序检验，这样就可以快速处理子串。每次只需要在前一个子串结尾处添加一个字符即可。

同样的道理，建立字典树后，在字串后添加一个字符，相当于在字典树上进行一步搜索。每次如果发现该位置存在字符串，就表示存在符合要求的 $k$。

这里有一个细节需要注意。我们是按照字符串 $s$ 倒序在字典树上查找的，由于 $s$ 倒序时每个单词都为倒序，因此在插入时必须按照 $t_i$ 倒序进行插入。

# 路径压缩

每次存储一个 vector 作为 $ans[i]$ 会导致空间使用较大。我们定义新的 $ans[i]$ 表示原 $ans[i]$ 的最后一个值，$nxt[i]$ 表示在推导 $ans[i]$ 时找到的满足要求的 $j$。

此时若 $ans[i]=0$，$f[i]$ 为假；若 $ans[i] \ne 0$，$f[i]$ 为真。因此不需要存储 $f[i]$。

另外由于 $s$ 的下标从 $0$ 开始，所以 $j$ 可能等于 $-1$。若 $nxt[i]=-1$ 代表 $s[0..i]$ 已经是一个完整的单词，无需分割。

进行路径压缩之后，输出答案可以按照下面的伪代码实现：

$pos \leftarrow n-1$

$\text{repeat}$

$\text{output}\ t[ans[pos]]$

$pos \leftarrow nxt[pos]$

$\text{until}\ pos<0$

以上为 字典树+DP 做法，时间复杂度 $\text O(n^2+\sum|t_i|)$，能够通过本题。

# Code of C++

更多详细信息参见注释。

建议在已经通读上方内容但仍不理解时查看代码，或在写代码/查错时查看此代码作为参考。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6+9;
int n,m,tot = 1,trie[N][26],reg[N],ans[N],nxt[N];
// 这里采用的是数组（类似于邻接矩阵）形式存储字典树，
// trie[p][work(ch)]表示从p号位置出发，
// 沿着字符ch代表的边到达的位置编号
string s,t[N];

// trie字典树部分
int work(char ch)
{
    return 'A' <= ch && ch <= 'Z' ? ch - 'A' : ch - 'a';
    // 将每个字母转化为数字，
    // a/A -> 0, b/B -> 1, ..., z/Z -> 25
}
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

int main()
{
    cin >> n >> s >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> t[i];
        // 注意此处需要将t反转之后插入
        reverse(t[i].begin(), t[i].end());
        insert(t[i], i);
        reverse(t[i].begin(), t[i].end());
    }
    reverse(s.begin(), s.end());
    for (int i = 0; i < n; ++i)
    {
        int p = 1;
        for (int j = i; j >= 0; --j)
        {
            if (!trie[p][work(s[j])]) break;
            p = trie[p][work(s[j])];
            if (!reg[p]) continue; // 不存在满足要求的k
            if (j != 0 && !ans[j - 1]) continue;
            ans[i] = reg[p];
            nxt[i] = j - 1;
            break;
        }
    }
    // 输出答案，这里使用的是for语句，i代表伪代码中的pos
    for (int i = n - 1; i >= 0; i = nxt[i])
        cout << t[ans[i]] << ' ';
    return 0;
}
```

---

## 作者：nao_nao (赞：5)

## AC自动机解法

#### 题意：
本题说将原串中每一个单词反转然后删去空格得到加密串，因此我们将加密串（也就是主串）反转后就是正序的单词（尽管单词的顺序是相反的）。

#### 题解：

我们考虑，我们将主串反转后，我们可以使用 AC自动机 来在主串上找到所有的给出子串，我们只需要找出一些子串使得它们正好可以拼成主串即可。我们可以进行线性的 DP ，由于我们是将子串倒序匹配，因此我们设 $dp[i]$ 为主串 S 中，从结尾到 i 能否被子串恰好拼好。因此我们可以得到方程：

$$dp[i] |= dp[i+len[s]]$$

其中 s 为主串中以 i 结尾匹配成功的一个子串，len[s] 为子串 s 的长度，如图：

![子串匹配](https://cdn.luogu.com.cn/upload/image_hosting/9amxn2sp.png)

其中 S 为主串， s 为在 i 处匹配成功的给定子串。


 DP 后我们可以得到 $dp[1] = 1$  ~~(废话,肯定有解dp[1]肯定是1)~~。我们考虑一下如何把这个 dp 的方案输出。

有没有回想起来要求输出具体方案的背包问题？我们可以将方程稍微修改一下：

```cpp
if(vis[u]){
	if(dp[i+Len[vis[u]]]) dp[i] = vis[u];
}
```
其中 vis 用于 AC自动机 里记录子串结束点对应的子串编号。

因此，输出时只需要像这样：

```cpp
for(int i = 1;i <= len;i += Len[dp[i]]){
	cout << str[dp[i]] << " ";
}
```
我在此处给出完整代码，部分解释见注释：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <queue>
#define js(c) (c<'a'?(c-'A'+'a'):c)
using namespace std;
const int N=1e6+7;
int n,m,cnt=1,Len[N],vis[N],nxt[N],dp[N];
char S[N],s[N];
int ch[N][28];
string str[N];
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

int find(int u,int a)
{
	if(!u) return 0;
	nxt[u] = find(nxt[u],a);
	if(vis[u]){
		if(dp[a+Len[vis[u]]]) dp[a] = vis[u];//在此处DP 
		return u;//类似于并查集的路径压缩，可以提供优化(大家A过板子的话都懂) 
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
int main()
{
	scanf("%d",&n);
	scanf("%s",S+1);
	scanf("%d",&m);
	for(int i = 1;i <= m;i ++){
		scanf("%s",s+1);
		add(i);
		str[i] = "";
		Len[i] = strlen(s+1);
		for(int j = 1;j <= Len[i];j ++) str[i] += s[j];
		//将字符串转为string格式防止爆空间 
	}
	dp[strlen(S+1)+1] = 1;
	build();work();
	
	int len = strlen(S+1);for(int i = 1;i <= len;i += Len[dp[i]]){
		cout << str[dp[i]] << " ";
	}
	return 0;
}
```


---

## 作者：Zekrom (赞：2)

~~终于搞定了QAQ~~      
# Hash+dp   
1.记$f[i]$表示目标子串第i个位置以$f[i]$为$Hash$值的子串的Hash值（好拗口，还是看代码好了）     
2.逆推 $f[i]=Hash[ch]$ $if$($ch$存在且子串$Hash[a[j]-a[i]]$$==$$Hash[ch]$)   
3.用map保存ch的Hash值   
4.$map.count(Hash)$返回是否某Hash值的子串      
上代码   

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<queue>
#include<map> 
#define inf 0x3f3f3f3f
#define N 10010
#define ll unsigned long long
#define Hi 233
using namespace std;
ll f[N],n,m;
map<ll ,string>mp;
char a[N];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
int main(){
	n=read();
	scanf("%s",a+1);
	m=read();
	for(int i=1;i<=m;i++){
		char ch[1010];scanf("%s",ch+1);
		int len=strlen(ch+1);string tmp="";
		for(int j=1;j<=len;j++)tmp+=ch[j]; 
		ll tmphash=0; 
		for(int j=len;j>0;j--){
			tmphash=tmphash*Hi+tolower(ch[j])-'a'+1;  //Hi为Hash值随便取
		}
		mp[tmphash]=tmp;
	}
	f[n+1]=1;
	for(int i=n;i>=1;i--){
		ll tmp=0;
		for(int j=1;j<=1000&&i+j-1<=n;j++){         //因为子串长度<1000,枚举长度即可
			tmp=tmp*Hi+a[i+j-1]-'a'+1; 
			if(mp.count(tmp)&&f[i+j]){
				f[i]=tmp;
				break; 
			} 
		}
	}
	for(int i=1;i<=n;i+=mp[f[i]].length()){
		cout<<mp[f[i]]<<' ';
	}cout<<endl;
	return 0;
}

```


---

## 作者：灵茶山艾府 (赞：1)

trie 树 + 记忆化搜索

首先把所有单词的小写形式插入一颗 trie 树，末尾节点记录原始单词。

然后定义 $dp[i]$ 表示前缀 $s[0..i]$ 能否拆分成若干个单词，从 $s$ 的末尾往前记忆化搜索即可得到答案，具体细节见下面 Go 代码。

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

type node struct {
	son [26]*node
	s   string
}

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
		if *dv != 0 {
			return *dv
		}
		defer func() { *dv = res }()
		o := root
		for i := p; i >= 0; i-- {
			o = o.son[s[i]-'a']
			if o == nil {
				return -1 
			}
			if o.s != "" && f(i-1) == 1 {
				Fprint(out, o.s, " ") // 找到合理拆分，直接打印
				return 1
			}
		}
		return -1
	}
	f(n - 1)
}
```

---

## 作者：CRTL_xzh2009 (赞：0)

可以考虑将输入的那 $m$ 个字符串反转去密文 $s$ 中匹配，注意保留原串，以备输出时找到原串。

找到匹配方案，需要借助于**字典树**算法。

具体细节就是设 `dp[i]` 表示从第 $1$ 位到第 $i$ 位是否存在一种字符串组合方式可以没有重叠和空白地组成 $s_{1} \sim s_{i}$。

然后用 ans 数组记录每一个 dp 值为 $1$ 的位置中上一个字符串结尾的位置和当前这个字符串在那 $m$ 个字符串中的编号。

字典树的用法就是帮助查看到哪一位会出现字符串的结尾，以确定整个单词。

输出答案时从第 $n-1$ 位开始往前跳转即可。

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1000100;
int n, m, tot, p, cnt;
int tre[N][30], ep[N], dp[N];
char n1;
string s;
string t[N];
pair<int, int> ans[N];
int ans1[N];
void insert(string x, int pos){
    p = 0;
    for (int i = x.length()-1; i >= 0; i--){
        n1 = x[i];
        if (n1 >= 'A' && n1 <= 'Z') n1 += 32;
        if (!tre[p][n1 - 'a']) tre[p][n1 - 'a'] = ++tot;
        p = tre[p][n1 - 'a'];
    }
    ep[p] = pos;
}
int main(){
    cin >> n >> s >> m;
    for (int i = 1; i <= m; i++){
        cin >> t[i];
        insert(t[i], i);
    }
    for (int i = 0; i < n; i++){
        if (i == 0 || dp[i-1]){
            p = 0;
            for (int j = i; j < n; j++){
                n1 = s[j];
                if (!tre[p][n1 - 'a']) break;
                p = tre[p][n1 - 'a'];
                if (ep[p]){
                    dp[j]+=i?dp[i-1]:1;	//dp[j] = 1;
                    ans[j] = make_pair(i-1, ep[p]);
                }
            }
        }
    }
    p = n-1;
    while (p >= 0){
        ans1[++cnt] = ans[p].second;
        p = ans[p].first;
    }
    for (int i = cnt; i >= 1; i--) cout << t[ans1[i]] << " \n"[i==1];
    return 0;
}

```


---

## 作者：寒鸽儿 (赞：0)

[博客食用效果更佳](https://www.luogu.org/blog/oldherd/solution-CF663C)  
字符串hash+线性dp  
首先字符串和主串的匹配是可以用dp来解决的。但是太长了会超时。于是考虑用字符串hash来解决。  
我们采用BKDR(边乘边模)来将其转化成p进制下的hash，用自然溢出来实现取模(对于long long应该是2^63)。这样处理出来的hash值冲突的概率很小。  
我们用mns函数进行字符串hash相减得到子串的hash值，减去的是前缀，这个可以手推一下。变形一下还可以实现减去后缀。建议手推一下。  
AC代码：
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> vl[1010], ans;
const int p = 13331;
int f[10010];
string s[100010];
char mn[10010];

struct str{
	long long dat;
	int len;
	bool operator == (const str& o) { return len == o.len && dat == o.dat; }
};

str hs[100010], hm[10010];

inline int num(char ch) {
	return ch > 'Z' ? ch - 'a' : ch - 'A';
}

inline str geth(const char *s, int len) {
	str res;
	res.len = len; res.dat = 0;
	for(int i = 0; i < len; i++)
		res.dat = res.dat * p + num(s[i]);
	return res;
}

inline long long qp(long long a, int k) {
	long long ans = 1;
	for(;k;k>>=1) {
		if(k & 1) ans *= a;
		a *= a;
	}
	return ans;
}

inline str mns(str h1, str h2) {
	str	res;
	res.len = h1.len - h2.len;
	res.dat = h1.dat - h2.dat * qp(p, res.len);
	return res;
}

int main() {
	int n, m;
	scanf("%d", &n);
	scanf("%s", mn);
	reverse(mn, mn+n);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++) cin>>s[i];
	hm[0].dat = 0; hm[1].dat = num(mn[0]); hm[1].len = 1;
	for(int i = 1; i < n; i++) hm[i+1].dat = hm[i].dat * (long long)p + (long long)num(mn[i]), hm[i + 1].len = i + 1;
	for(int i = 1; i <= m; i++)
		hs[i] = geth(s[i].data(), s[i].length()), vl[hs[i].len].push_back(i);
	f[0] = 1;
	for(int i = 1; i <= n; i++) {
		bool flag = false;
		for(int len = 1; len <= i && len <= 1000; len++) {
			if(!f[i-len]) continue;
			for(vector<int>::iterator it = vl[len].begin(); it != vl[len].end(); it++)
				if(hs[*it] == mns(hm[i], hm[i-len])) {
					f[i] = *it;
					flag = true;
					break;
				}
			if(flag) break;
		}
	}
	for(int i = n; i; i -= hs[f[i]].len)
		cout<<s[f[i]]<<" ";
	printf("\n");
	return 0;
}
```
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后再次安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)  

---

