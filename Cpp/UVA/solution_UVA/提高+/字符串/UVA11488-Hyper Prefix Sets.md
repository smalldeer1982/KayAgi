# Hyper Prefix Sets

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2483

[PDF](https://uva.onlinejudge.org/external/114/p11488.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11488/b054540c80bd466e35ea7b5ef13a250519cecff4.png)

## 样例 #1

### 输入

```
4
4
0000
0001
10101
010
2
01010010101010101010
11010010101010101010
3
010101010101000010001010
010101010101000010001000
010101010101000010001010
5
01010101010100001010010010100101
01010101010100001010011010101010
00001010101010110101
0001010101011010101
00010101010101001```

### 输出

```
6
20
66
44```

# 题解

## 作者：chenxumin1017 (赞：4)

# 题意
给你 $N$ 个串，要你先择一段前缀使得它的长度乘上包含这个前缀的串最大。

# 思路

看到前缀，就让我想到了字典树，再看一下数据范围，发现枚举前缀字符串再求解答案是可行的。

时间复杂度：$O(T \cdot \sum|S|)$

更多细节详见代码！

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 10000005, ROOT = 1;

int n, t, cntr = 2, ans;

string b;

struct Node{
  int son[5], cnt;
}a[MAXN];

void g(string x){ // 建树
  int u = ROOT;
  for(char i : x){
    int v = i - '0';
    if(a[u].son[v] == 0){
      a[u].son[v] = cntr++;
    }
    u = a[u].son[v];
    a[u].cnt++;
  }
}
void dfs(int u, int x){ // 在遍历字典树时，要记录深度。
  if(u == 0){
    return;
  }
  ans = max(ans, a[u].cnt * x);
  dfs(a[u].son[0], x + 1);
  dfs(a[u].son[1], x + 1);
}
signed main(){
  ios::sync_with_stdio(false), cin.tie(0); // 数据规模大，要使用快读。
  cin >> t;
  for(int i = 1; i <= t; i++){
    cin >> n;
    ans = 0;
    a[1].cnt = a[1].son[0] = a[1].son[1] = 0; // 初始化
    for(int j = 1; j <= n; j++){
      cin >> b;
      g(b);
    }
    dfs(1, 0);
    cout << ans << '\n';
  }
  return 0;
}
``````

---

## 作者：ymx2009 (赞：3)

# 题意概述  
有 $n$ 个字符串，求公共子串长度与所选字串个数积的最大值。  
# 前置知识  
字典树，请移步 [P8306](https://www.luogu.com.cn/problem/P8306)。
# Solution  
看到前缀公共长度可以想到用字典树。  
然后考虑怎样取才能使得字符串的公共长度和所选字符串成乘积最大。  
想到从字典树上每个点的贡献值：  
$$
res_i=cnt_i\times dep_i
$$
$dep_i$ 代表当前点在字典树的深度。  
$cnt_i$ 表示以根到 $i$ 为前缀的字符串的个数。  
显然我只需要从根节点从上往下遍历字典树，把每个点的贡献值算出来，维护贡献的最大值即可。

---

## 作者：Motonic_queues (赞：3)

首先这题看到公共前缀就知道要 Trie 树了。

统计方法很简单，给每个节点维护一个“是几个字符串的前缀”，可以树上差分，再乘一下深度取最大值就没问题了。  
一次回答复杂度 $O(N)$，其中 $N$ 是这组数据所有字符串的总长

---

## 作者：Archy_ (赞：1)

## 题目思路：

有 $n$ 个串，选择一段前缀使得它的长度乘上包含这个前缀的串最大，看到前缀想到可以用字典树来解决这个问题。如何处理长度？记录一个 $dep$ 数组来存储每个节点的深度，同时记录 $cnt$ 数组来记录有多少个字符串跑到这个位置，遍历每个节点，$cnt_i \times dep_i$ 就是答案，取最大即可。

## code：

```cpp
#include <iostream>
#include <cstring>
#define fi first
#define se second
using namespace std;

const int N = 1e7 + 10;
int T, n, trie[N][2], tot; 
long long dep[N], cnt[N];
string s; 

void INIT() {
	for(int i = 0; i <= tot; i ++) {
		cnt[i] = 0, dep[i] = 0;
		trie[i][0] = trie[i][1] = 0;
	}
	tot = 0;
}

void insert(string s) {
	int p = 0;
	for(auto &c : s) {
		int num = c - '0';
		if(!trie[p][num]) trie[p][num] = ++ tot;
		dep[trie[p][num]] = dep[p] + 1;
		p = trie[p][num];
		cnt[p] ++;
	}
}

long long solve() {
	long long ans = 0;
	for(int i = 1; i <= tot; i ++) {
		ans = max(ans, cnt[i] * dep[i]);
	}
	return ans;
}

int main() {
	cin >> T;
	while(T --) {
		cin >> n;
		INIT();
		while(n --) {
			cin >> s;
			insert(s);
		}
		cout << solve() << "\n";
	}
	return 0;
}
```

---

## 作者：AlexandreLea (赞：1)

# 题目浓缩大意
给出 $n$ 个 01 串，任选多个，求出这些 01 串的最长公共前缀长度乘以个数的最大值。

# 题目思路
前缀前缀，用 Trie 树没错了。

由于要统计个数，因此在所有节点都统计字符串“经过”的个数。

由于要求最长公共前缀的长度，因此在插入时计算 Trie 树深度即可。

另外，不需要多开函数进行计算，可以在输入时处理数据。

代码见下：

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int size=3e2+10;
int soh[size*size][2]={},cts=1,ctb[size*size]={};
int main(){
    int _;
    cin>>_;
    while(_--){
        memset(soh,0,sizeof(soh)),memset(ctb,0,sizeof(ctb)),cts=1;
        int n,ans=0;
        cin>>n;
        for(int i=1,res=0;i<=n;i++,res=0){
            char str[size]={};
            cin>>str;
            for(int i=0,k=1,d=0;i<=strlen(str);i++,d++){
                if(soh[k][str[i]-'0']==0) soh[k][str[i]-'0']=++cts;
                ctb[k]++,ans=max(ans,d*ctb[k]),k=soh[k][str[i]-'0'];
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

**EOF**

---

## 作者：1234567890sjx (赞：0)

因为是前缀问题，所以肯定要建 Trie 树进行维护。

Trie 树的每一个节点维护一个二元组信息 $(gzq,lbx)$ 表示当前节点的深度为 $gzq$，当前节点的子树中有 $lbx$ 个字符串。

例如：一个节点中，$gzq=6$，$lbx=66$，那么二元组 $(6,66)$ 就是深度为 $6$ 的节点的子树中有 $66$ 个不同的字符串。

然后枚举 Trie 上的每一个节点得到的信息 $(gzq,lbx)$，容易发现这个节点的权值就是 $gzq\times lbx$。

那么枚举每一个节点计算权值即可。

单组数据的时间复杂度 $O(\sum |s|)$，

感觉也没有蓝，大概是绿。

---

## 作者：Fireworks_Rise (赞：0)

# 分析题意

定义 $S$ 表示一个 $01$ 字符串的集合，再定义 $f(S)$ 为 $S$ 内所有字符串的 LCP（最长公共前缀）的长度 $\times S$ 内元素的个数。

求出一个子集 $T$，使得 $f(T)$ 最大。

# 思路

由于是要求字符串的最长公共前缀，所以很容易想到用[字典树]()来解决这个问题。

用字典树来维护 $S$ 内所有字符串的 LCP，问题就转化成了如何求解公共前缀的长度。

最长公共前缀的算法流程是从根开始遍历的，也就是说可以一边记录 LCP 元素个数 $cnt_i$ 的同时，记录当前节点的深度 $dep_i$，问题就迎刃而解了。

最后遍历树上所有节点，每个公共前缀的 $f_i$ 为 $dep_i\times cnt_i$，取其最大值存入 $ans$ 中，输出 $ans$ 即解出答案。

提醒：多组测试数据，别忘了清 $0$ 哦！！！

# Code（字典树）

此处贴上小小蒟蒻的简陋代码...

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int t,n,cnt[N],dep[N];
int f[N][21],idx;
string s;
void reset_() {
	for(int i=0;i<=idx;i++) {
		cnt[i]=0;
		for(int j=0;j<21;j++) 
			f[i][j]=0;
	}
	idx=0;
}
void insert(string s) {
	int p=0;
	for(int i=0;i<s.size();i++) {
		int tmp=s[i]-'0';
		if(!f[p][tmp]) f[p][tmp]=++idx;
		dep[f[p][tmp]]=dep[p]+1;
		p=f[p][tmp];
		cnt[p]++;
	}
}
int qurey() {
	int ans=0;
	for(int i=1;i<=idx;i++)
		ans=max(dep[i]*cnt[i],ans);
	return ans;
}
signed main() {
	scanf("%lld",&t);
	while(t--) {
		scanf("%lld",&n);
		reset_();
		for(int i=1;i<=n;i++) {
			cin>>s;
			insert(s);
		}
		printf("%lld\n",qurey());
	}
	return 0;
}
```


---

## 作者：tbdsh (赞：0)

# 题意简述
[洛谷原题](/problem/uva11488)

[UVA 题面](/remoteJudgeRedirect/uva/11488)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-uva11488)

有 $t$ 组数据。每组数据给出 $n$ 个长度不超过 $200$ 且仅包含 `0`、`1` 的字符串 $S_i$。

定义一个可重字符串集合 $S$ 的价值为这个字符集中所有字符串的最长公共前缀的长度 $lcp$ 与这个集合大小的乘积。例如，集合 $\{\operatorname{000},{001},{0011}\}$ 的价值是 $6$。

现在，请你在 $n$ 个字符串中选出一些字符串，使得这个集合的价值最大。输出这个最大的价值。
# 分析
考虑使用字典树。

对于每个字符串都建一个字典树。因为需要统计最长前缀数量，所以每遍历到一个节点都将其对应的值 $tr_{u, s_i,1}$ 的值更新为 $tr_{u, s_i, 1} + 1$。

然后再从每一个字符串遍历一遍字典树。遍历时不断更新答案 $ans$ 为 $\max(ans,tr_{u,s_i,1}\times lcp)$。最后输出答案即可。

时间复杂度：$O(t\times \sum|S|)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 6e6 + 5, MAXNN = 5e4 + 5;;
int t, n, tr[MAXN][2][2], cnt = 1;
int add(){
  return ++cnt;
}
void insert(string s){
  int u = 1;
  for (auto v : s){
    if (!tr[u][v - '0'][0]){
      tr[u][v - '0'][0] = add();
    }
    tr[u][v - '0'][1]++;
    u = tr[u][v - '0'][0];
  }
}
int find(string s){
  int u = 1, cnt = 0, qwq = 1;;
  for (auto v : s){
    cnt = max(cnt, qwq * tr[u][v - '0'][1]);
    u = tr[u][v - '0'][0];
    qwq++;
  }
  return cnt;
}
void Solve(){
  for (int i = 1; i <= cnt; i++){
    tr[i][0][0] = tr[i][0][0] = tr[i][1][0] = tr[i][1][1] = tr[i][0][1] = tr[i][0][1] = tr[i][1][1] = tr[i][1][1] = 0;//清空。
  }
  cnt = 1;
  cin >> n;
  string tmp[MAXNN];
  for (int i = 1; i <= n; i++){
    cin >> tmp[i];
    insert(tmp[i]);//建树。
  }
  int ans = -1;
  for (int i = 1; i <= n; i++){
    ans = max(ans, find(tmp[i]));//更新答案。
  }
  cout << ans << '\n';
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：__stick (赞：0)

# 题意
给出一个单词的集合，求出一个子集 $S$ ，使得它的 $|lcp|\times |S| $  最大。

# 思路
由于前缀相关，直接往字典树上去想，所以直接去建出字典树然后想想可以怎么瞎搞。

我们会发现一个子集的 $lcp$ 就是它们在字典树上的公共路径，也就是所有单词结尾的 $lca$ ，又因为 $lcp$ 相同的话子集越大越好，所以可以直接枚举 $lcp$ ，求出最大的 $lcp$ 为当前所枚举的子集，怎么求？

因为我们枚举 $lcp$ 就是在枚举字典树上的每个节点，所以以我们枚举的节点为根的子树中的单词所构成的集合就是我们要求的那个最大子集，直接统计即可。

# 代码
用多少清多少可以降低时间复杂度。
暂时的 rank1：
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline void cmax(T& a,const T& b){a<b?a=b:0;}
template<typename T>
inline void cmin(T& a,const T& b){b<a?a=b:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
#define mp make_pair
const int mod=998244353;
const int MAXN=1e7+10;
int tt;
struct node
{
	int son[2];
	int dep,sum;
	inline void clear(){son[0]=son[1]=dep=sum=0;}//用一个清一个效率更高 
}t[MAXN];
char s[2009];
inline void insert(char a[])
{
	int u=1;
	for(int i=0;a[i];i++)
	{
		int ch=a[i]-'0';
		if(!t[u].son[ch])t[u].son[ch]=++tt,t[tt].clear(),t[tt].dep=t[u].dep+1;
		u=t[u].son[ch];
		t[u].sum++;//因为以当前节点为子树中的单词数等价于经过当前节点的单词数，所以可以简化代码 
	}
}
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int T;cin>>T;
	while(T--)
	{
		int n;cin>>n;tt=1;t[tt].clear();//记得清空根节点！！！！ 
		for(int i=1;i<=n;i++)cin>>s,insert(s);
		ll ans=0;
		for(int i=2;i<=tt;i++)cmax(ans,(ll)t[i].dep*t[i].sum);
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：HPXXZYY (赞：0)



$\color{blue}{\texttt{[Problem]}}$

- 记 $S$ 表示一个 $01$ 字符串的集合。
- 记 $f(S)=S$ 内所有字符串的 `LCP`（最长公共前缀）的长度 $\times S$ 内元素的个数。
- 输入 $n$ 个 $01$ 字符串，求出一个子集 $T$，使得 $f(T)$ 最大。输出 $f(T)$ 即可。

------------------------------------

$\color{blue}{\texttt{[Solution]}}$

首先将所有的字符串建立一棵 `Trie树`，我们考虑如何在 `Trie树` 上维护 $f(T)$ 的值。

看一个~~丑陋的~~示意图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/2020081421041255.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1pIVVlJTkdZRV8xMjM0NTY=,size_16,color_FFFFFF,t_70#pic_center)

如果这是一棵 `Trie树`，如何利用它求出最大的 $f(T)$ 呢？

首先，我们求出 `Trie树` 上每个节点的深度 $\texttt{dep}$ 和有多少个节点经过了它（记为 $\texttt{cnt}$），像这样：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200814210752234.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1pIVVlJTkdZRV8xMjM0NTY=,size_16,color_FFFFFF,t_70#pic_center)

我们发现 `Trie树` 上每个节点 $i$ 对答案的贡献就是 $C_i=\texttt{cnt}_{i} \times \texttt{dep}_i$，所以我们在建好 `Trie树` 后只需要对每个节点 $i$ 都求一遍 $C_i$，再在所有的 $C_i$ 中求出一个最大值即可。这样我们就可以获得 `AC` 了。

等等，还有一个问题不知道大家想过没有，题目不是说要 `LCP` 的长度吗？我们好像并不能保证每个节点所代表的前缀字符串都是若干个字符串的 `LCP` 吧 ~~（如果不能理解这句话，那就多读几次吧，是有点拗口）~~，那这样不会求出错误的解从而导致 `WA` 吗？

让我们来想想：什么样的节点不可能成为若干个字符串的 `LCP` 呢？仔细想想可以发现，只有一个儿子的节点不可能成为若干个字符串的 `LCP`，如图（为了节约篇幅，我把竖着的树画横啦）：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200815132512481.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1pIVVlJTkdZRV8xMjM0NTY=,size_16,color_FFFFFF,t_70#pic_center)

我们可不可以保证这些点的贡献不会影响答案呢？其实是可以的。因为它们只有一个儿子，所以它们的儿子一定还是这么多个字符串的前缀（即记该节点为 $u$，其儿子为 $v$，有 $\texttt{cnt}_u=\texttt{cnt}_v$），因为 $\texttt{dep}_v>\texttt{dep}_u$，所以 $C_v>C_u$，因此 $u$ 考虑不考虑都不会影响答案。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=1e7+100;
struct Trie_tree{
	int nxt[N][2],tot,cnt[N],dep[N];
	inline void init_trie(){
		memset(nxt,-1,sizeof(nxt));
		memset(cnt,0,sizeof(cnt));
		memset(dep,0,sizeof(dep));
		tot=0;//清空整一棵Trie树 
	}
	void insert(char s[],int len){
		register int u=0;//当前节点 
		for(int i=1;i<=len;i++){
			register int c=s[i]-'0';
			cnt[u]++;//u节点被经过了一次 
			if (nxt[u][c]==-1){
				nxt[u][c]=++tot;
				dep[nxt[u][c]]=dep[u]+1;
			}//新建一个节点 
			u=nxt[u][c];//建立Trie树 
		}
		cnt[u]++;//注意,最后一个点需要特别处理 
	}
	inline int query(){
		register int ans=0;
		for(int i=1;i<=tot;i++)
			ans=max(ans,dep[i]*cnt[i]);
		return ans;
	}
}Trie;char s[210];
int n,test_number;
int main(){
	scanf("%d",&test_number);
	while (test_number--){
		scanf("%d",&n);
		Trie.init_trie();
		for(int i=1;i<=n;i++){
			scanf("%s",s+1);
			int len=strlen(s+1);
			Trie.insert(s,len);
		}
		printf("%d\n",Trie.query());
	}
	return 0;
}

附：把一个数据结构封装到一个结构体内是一个很好的习惯哦。
```

---

