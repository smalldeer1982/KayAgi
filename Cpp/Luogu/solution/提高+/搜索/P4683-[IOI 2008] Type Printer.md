# [IOI 2008] Type Printer

## 题目描述

你需要利用一台可移动的打印机打印出 $n$ 个单词。这种可移动式打印机是一种老式打印机，它需要你将一些小的金属块（每个包含一个字母）放到打印机上以组成单词。然后将这些小金属块压在一张纸上以打印出这个词。这种打印机允许你进行下列操作： 

- 在打印机当前词的末端（尾部）添加一个字母； 
- 在打印机当前词的尾部删去一个字母（将打印机当前词的最后一个字母删去）。仅当打印机当前至少有一个字母时才允许进行该操作；
- 将打印机上的当前词打印出来。 

初始时打印机为空，或者说它不含任何带字母的金属块。打印结束时，允许有部分字母留在打印机内。同时也允许你按照任意的次序打印单词。

由于每一个操作都需要一定时间，所以需要你尽可能减少所需操作的总数目（将操作的总数最小化）。

你需要编写一个程序，给定所要打印的 $n$ 个单词，找出以任意次序打印所有单词所需操作的最小数目，并输出一种这样的操作序列。

## 说明/提示

对于 $40\%$ 的数据，$n\leq18$；

对于 $100\%$ 的数据，$1\leq n\leq25000$。

## 样例 #1

### 输入

```
3
print
the
poem```

### 输出

```
20
t
h
e
P
-
-
-
p
o
e
m
P
-
-
-
r
i
n
t
P```

# 题解

## 作者：Lovely_Elaina (赞：51)

### 前言

第一眼看到题目，~~活字印刷术？~~

其实就是给你一个~~很恶心的~~打印机，共有三种操作：

1. 在当前词的尾部添加一个字母；
2. 在当前次的尾部减去一个字母（至少有一个字母时）；
3. 打印当前词。

其次，有三个注意点：

1. 添加一个字母，用这个小写字母的自身来表示；
2. 删去一个字母，用减号表示；
3. 打印单词时，用 `P` 表示。

特别的：

1. 所有单词都不相同；
2. 打印结束时，允许有部分字母留在打印机内；
3. 允许按照任意的次序打印单词。

说句题外话：这打印机谁造的。

下面的看懂了题目再来看。

---

### 思路

我们使用字典树来完成。

首先，有一个点大大的降低了题目难度，就是 `打印结束时，允许有部分字母留在打印机内`。

众所周知，字典树很好地利用了字符串的公共前缀，这也就是上一行出现的原因。

如果我们想要操作数尽可能少，那我们的删除数的操作就要尽可能的少。

我们来模拟一下（敲黑板）。

注：为了方便观察，我改了自己造的样例的顺序。

```
输入：
8
abcd
abcdef
dfg
dfgr
dgrt
plwoe
plwpo
plwpoq
```

构建出来的树数这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/2tjvqzkn.png)

~~粉色，够温馨吧。~~

虽然图画的有点丑，将就看吧。

让我们看回到上面那句话：

> 如果我们想要操作数尽可能少，那我们的删除数的操作就要尽可能的少。

怎么样，看出字典树的特征了吧。

先讲怎么遍历。

我们以中间那一坨为例：

- 先遍历 `d`，然后开始搜索所有子树；
- 发现了 `f`，继续往下搜索；
- 遇到了 `g`，发现是一个单词结尾，输出，还有子树，继续往下；
- 遇到了 `r`，发现是一个单词结尾，输出，发现没了，停止。

啧，是回溯。

我们要删到可以继续搜，也就是说我们的 dfs 大概是这样的：

```cpp
for(int i = 0; i < 26; i++){
  if(存在该子节点 && 还有一个，下面会说){
    要输出的字符串 += 该子节点;
    dfs(该子节点);
    要输出的字符串 += '-';
  }
}
```

好耶。

但是这个时候有人要问了，不应该先遍历更短的子树吗？这不是删除数量更少吗？

对，这就是另外一个重点。

在输入时，我们存下最长的字符串，然后给该字符串在树中打标记。

以这个为例，我们可以发现如果想要删得更少，刚刚好 `plwpoe` 这一条不用删。

其余的所有字母都是必删的。

而 `plwpoe` 这一条是输入中最长的。

嘿嘿，懂了吗。

我们在输入的时候记下最长的，事后标记一下，优先遍历没有标记的，这样删的次数最少。

标记的函数也很简单。

```cpp
void mark(string s){
  int p = 0; // 当前遍历的子树的根
  for(int i = 0; s[i]; i++){ //遍历，字符串 s 必存在
    int x = s[i] - 'a';
    tick[p][x] = 1; // 标记
    p = tree[p][x]; // 下一个
  }
}
```

---

### 代码

插入：

```cpp
inline void insert(string s)
{
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int x = s[i] - 'a';
        if (!tree[p][x])
            tree[p][x] = ++ind; // 建点
        le[tree[p][x]] = x + 'a'; // 记录
        p = tree[p][x];
    }
    en[p] = 1; //标记结尾
}
```

标记最长：

```cpp
inline void mark(string s)
{
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int x = s[i] - 'a';
        k[tree[p][x]] = 1;
        p = tree[p][x];
    }
}
```

dfs：

```cpp
inline void dfs(int x)
{
    if (en[x] == 1 && x != 0) {
        ans++;
        output += "P";
    }

    if (ans == n) {
        cout << output.size() << endl;
        for (int i = 0; output[i]; i++)
            cout << output[i] << endl;
        return;
    }

    int reg;
    for (int i = 0; i < 26; i++) {
        reg = tree[x][i];
        if (k[reg] == 0 && reg != 0) {
            output += le[reg];
            dfs(reg);
            output += "-";
        }
    }

    for (int i = 0; i < 26; i++) {
        reg = tree[x][i];
        if (k[reg] && reg) {
            output += le[reg];
            dfs(reg);
            output += "-";
        }
    }
}
```

其实我格式化了代码，但是原码风挺正常的。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;

bool en[N]; // 结尾
bool k[N]; // 标记
char le[N]; // 记录树的几号节点为什么
int tree[N][26];

int n, m, ind, ans;
string s, output, l;

inline void insert(string s)
{
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int x = s[i] - 'a';
        if (!tree[p][x])
            tree[p][x] = ++ind; // 建点
        le[tree[p][x]] = x + 'a'; // 记录
        p = tree[p][x];
    }
    en[p] = 1; //标记结尾
}

inline void mark(string s)
{
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int x = s[i] - 'a';
        k[tree[p][x]] = 1;
        p = tree[p][x];
    }
}

inline void dfs(int x)
{
    if (en[x] == 1 && x != 0) {
        ans++;
        output += "P";
    }

    if (ans == n) {
        cout << output.size() << endl;
        for (int i = 0; output[i]; i++)
            cout << output[i] << endl;
        return;
    }

    int reg;
    for (int i = 0; i < 26; i++) {
        reg = tree[x][i];
        if (k[reg] == 0 && reg != 0) {
            output += le[reg];
            dfs(reg);
            output += "-";
        }
    }

    for (int i = 0; i < 26; i++) {
        reg = tree[x][i];
        if (k[reg] && reg) {
            output += le[reg];
            dfs(reg);
            output += "-";
        }
    }
}

int main()
{

    cin >> n;
    getchar();
    for (int i = 1; i <= n; i++) {
        cin >> s;
        insert(s);
        if (l.size() < s.size())
            l = s;
    }

    mark(l);
    dfs(0);

    return 0;
}
```

说两句题外话：

1. 我一开始一边插入一边标记；
2. 大写打成了小写。

没人像我这样吧（小声）。

---

## 作者：Rikka__ (赞：32)

~~这题其实就是个Trie树板子题~~（逃

题目大意是给你若干个单词，以及一台打印机= =

你珂以对这个打印机进行3种操作：

①：在打印机末端添加一个字符(输出添加的单词)

 ②：删除打印机末端的单词(输出一个 '**-**' )

③：打印该单词(输出一个**P**）

要求你在**最少**的步骤内打印出所有单词并输出你的操作。

我们可以把这个打印机想象成一个大的字符串, ①操作就是在字符串末尾**添加**一个字符,②操作就是**删去**字符串末尾的一个字符,③操作就是打印当前的字符串。

这样这道题就看起来很简单了（其实代码也很简单0-0）
我们只需要在Trie树上遍历就可以了。但是题目要求的是最少的操作,所以我们要思考一下怎么去减少操作。

显然，所有单词都是要遍历一遍的，我们无法缩减这个次数，所以我们可以思考怎么减少删除次数。

根据题意我们可以知道：我们在打印完最后一个单词时可以直接输出结果结束程序，不用再去将打印机清空。
这样我们就可以想出一种方法：我们只需要将最长的单词放在最后去打印，这样我们就可以尽量减少删除次数了（因为单词最长所以删除次数也就最多）。

这个思路对吗？事实证明是对的。
所以我们只要对这些单词建树，并在输入的过程中找到最长的单词，在插入这个单词时，跑一遍dfs将从根节点（0号节点）到这个单词的末尾之间的路径（后面为了方便我自己称之为最长单词路径）上的节点都打上一个标记，遍历的时候优先去跑没有标记的节点。这样这道题就完成了。

CODE：


Trie建树基本操作：
```cpp
void ins(string a){
	int u=0;//为了方便根节点为0，从0开始插入
	for(int i=0;a[i];i++){//个人习惯这种字符串遍历方法
		int now=a[i]-'a';//根据情况决定减‘0’还是‘a’
		if(tr[u][now]==0) tr[u][now]=++cnt;
		le[tr[u][now]]=now+'a';//反向记录当前节点所存的字母
		u=tr[u][now];//更新当前位置，继续向下插入
	}
	p[u]=1;//打上结尾标记
}
```
建树过程中的dfs：
```cpp
void dfs(string a){
	int u=0;
	for(int i=0;a[i];i++){  // 将从最长单词路径上的节点全都打上标记 
		int now=a[i]-'a';
		k[tr[u][now]]=1;
		u=tr[u][now];
	}
}
```

遍历的话也是比较简单的：
```cpp
void solve(int now){   //now 为当前位置节点编号
	if(p[now]==1){    //如果是单词结尾 
		ans++;		 //已打印的单词数加一 
		ss+="P";	//直接打印，输出P 
	}	
	
	if(ans==n){	  //如果已经全部打印完了 
		cout<<ss.size()<<endl;  //输出操作步数 
		for(int i=0;ss[i];i++){
			cout<<ss[i]<<endl;  //输出操作顺序 
		}
	}
	 
	for(int i=0;i<26;i++){		//枚举26个字母看是否有路径 
		if(k[tr[now][i]]==0&&tr[now][i]!=0){  //如果存在该节点并且不是 最长的单词路径上的节点 
			
		//	system("pause");
			ss+=le[tr[now][i]];		//将当前字母添加入打印机 
			solve(tr[now][i]);		//继续向下遍历 
			ss+="-";				//遍历完后回溯时要将字母删除，所以输出 - 
		}
	}
	
	for(int i=0;i<26;i++){			//将有标记的节点放在最后去跑 
		if(k[tr[now][i]]==1&&tr[now][i]!=0){	//因为没有标记的节点在之前都已经遍历完，所以这里只需要遍历有标记的 
			ss+=le[tr[now][i]];				   //操作同上 
			solve(tr[now][i]);	
			ss+="-";							
		}
	}
	
}
```
这样这道题就算是完事了。


  AC代码：
[戳这里](https://www.luogu.com.cn/paste/7yrajunm)

**结语:**

这道题拿来练Trie挺好的，还有其他几道Trie的练手题：

[P2922](https://www.luogu.com.cn/problem/P2922)

                                              
[UVA11362](https://www.luogu.com.cn/problem/UVA11362)

[P3879](https://www.luogu.com.cn/problem/P3879)

**最后祝大家2020NOIP RP++**









---

## 作者：wasa855 (赞：13)

首先，题目告诉了我们每个单词的长度，而且空间允许，所以明显需要建出字典树。   
``` cpp
void add(string s)
{
	int now=0;
	int n=s.length();
	for(int i=0;i<n;i++)
	{
		if(a[now].nxt[s[i]-'a']==0)
		{
			ss++;
			a[now].nxt[s[i]-'a']=ss;
		}
		now=a[now].nxt[s[i]-'a'];
	}
	a[now].end=true;
}
```   
然后以贪心的思路解题，题目要求操作次数最少，所以要尽可能多利用以前打出的字母，于是就要以最长的单词为基础打字。   
于是考虑在最长单词的所有字母上加上标记，最后走。   
``` cpp
void mark(string s)
{
	int now=0;
	int n=s.length();
	for(int i=0;i<n;i++)
	{
		now=a[now].nxt[s[i]-'a'];
		a[now].use=true;
	}
}
```   
最后明显应对整棵trie进行dfs，dfs序就是操作序列。   
注意：在已经完成打字之后就不需要再进行删字母操作了。   
``` cpp
void dfs(int now)
{
	int mark=-1;
	if(a[now].end==true)
	{
		ans[++sum]='P';
	}
	for(int i=0;i<26;i++)
	{
		if(a[a[now].nxt[i]].use==true)
		{
			mark=i;
		}
		else if(a[now].nxt[i]!=0)
		{
			ans[++sum]=i+'a';
			dfs(a[now].nxt[i]);
		}
	}
	if(mark!=-1)
	{
		ans[++sum]=mark+'a';
		dfs(a[now].nxt[mark]);
	}
	if(mark==-1&&a[now].use==true)
	{
		ok=true;
	}
	if(ok==false)
	{
		ans[++sum]='-';
	}
}
```   
最后输出答案就行了。   
#### 放代码之前，预祝各位OIer NOIP2018 RP++   
最后，附上完整AC的代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;
struct Node
{
	int nxt[26];
	bool use;
	bool end;
};
Node a[500005];
char ans[1000005];
int sum;
int ss;
void add(string s)
{
	int now=0;
	int n=s.length();
	for(int i=0;i<n;i++)
	{
		if(a[now].nxt[s[i]-'a']==0)
		{
			ss++;
			a[now].nxt[s[i]-'a']=ss;
		}
		now=a[now].nxt[s[i]-'a'];
	}
	a[now].end=true;
}
void mark(string s)
{
	int now=0;
	int n=s.length();
	for(int i=0;i<n;i++)
	{
		now=a[now].nxt[s[i]-'a'];
		a[now].use=true;
	}
}
bool ok=false;
void dfs(int now)
{
	int mark=-1;
	if(a[now].end==true)
	{
		ans[++sum]='P';
	}
	for(int i=0;i<26;i++)
	{
		if(a[a[now].nxt[i]].use==true)
		{
			mark=i;
		}
		else if(a[now].nxt[i]!=0)
		{
			ans[++sum]=i+'a';
			dfs(a[now].nxt[i]);
		}
	}
	if(mark!=-1)
	{
		ans[++sum]=mark+'a';
		dfs(a[now].nxt[mark]);
	}
	if(mark==-1&&a[now].use==true)
	{
		ok=true;
	}
	if(ok==false)
	{
		ans[++sum]='-';
	}
}
int main()
{
	int n;
	cin>>n;
	string a;
	string maxn;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		add(a);
		if(a.length()>maxn.length())
		{
			maxn=a;
		}
	}
	mark(maxn);
	dfs(0);
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++)
	{
		printf("%c\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：_LPF_ (赞：4)

# 题意描述

[[IOI2008] Type Printer 打印机](https://www.luogu.com.cn/problem/P4683)

几百年前的 IOI 的题目还是很好的呀。

给你一个 ~~诡异的~~ 打印机，它只能用已有的字符来打印，而且必须每一个都用到。（这岂不是活字印刷术）

你可以对其执行三个操作：

1. 打印，用大写字母 P 表示，输出顺序任意，但仅能且必须用到当前打印机里的每一个字符。
2. 插入，输入一个字符 c，表示在打印机中插入字符 c。（打印机的存储是一个队列）
3. 删除，从队列尾部删除一个字符。

给定 $N$ 个字符串，问当前需要至少多少步才能完成所有打印。

# 算法分析

考虑可爱的 $trie$ 树，先建一棵树，假设当前已经建好了。（如果不会 ~~你做这道题干什么~~ 可以看看[这篇文章](https://www.cnblogs.com/lpf-666/p/12463685.html)）

然后我们发现题目变成了：确定一个 $DFS$ 的顺序，使得树上的每一个点都遍历到，并且结束于某个叶节点。

## 思想一

显然，倘若要求回到根节点，步数永远为 $2\times (N-1)$。（每条边都经过两次）

但是最后一条路径可以不回去，假设最后打印的字符串长度为 $len$，显然最终遍历步数为 $2\times (N-1)-len$。

**注意：这里的遍历步数 $\neq$ 答案步数，因为答案中还有删除操作**。

显然 $ans_{min}=2\times (N-1)-len_{max}$。

## 思想二

既然每一个单词都要输出，打印的操作次数一定 = 总字符串数。

那么关键就是插入与删除次数尽量少，那么显然倘若要求删除次数尽量少，之前插入的字符长度应当尽量小。

所以最长的单词当然要最后打印。

当然以上的证明是不严谨的，但是有助于大家理解。

**所以通过两种方法都可以确定贪心策略：最后走最长的单词，其他随意。**

# 代码实现

其实还挺简单的。

1. 建树。不用讲解吧。
2. 标记。标记一下最长的字符串，也很简单。
3. dfs。最重要的环节了。在 dfs 时主要有三种操作：打印，向下遍历，回溯。

在打印时通过判断当前是否为单词的尾部来进行判断。

向下遍历时特殊处理被标记的节点。

回溯时倘若该点不是被标记的点，就打印 "-"。

看不懂的话看代码吧：

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstring>
#include<string>
#define N 500010//几次空间开小了都 RE，所以索性开大一点，dalao 勿喷。
using namespace std;

int n,trie[N][30],tot=1;
bool sum[N],flag[N],finish=false;
//上面三个分别用来标记：是否是单词结尾（trie 基本操作），是否是最长字符串上的点，是否到了最后一个单词。
string a,jl,ans;

void insert(string a){
	int p=1;
	for(int i=0;i<a.length();i++){
		int ch=a[i]-'a';
		if(!trie[p][ch]) trie[p][ch]=++tot;
		p=trie[p][ch];
	}
	sum[p]=true;
	return;
}
//常规插入操作。
void Mark(string a){
	int p=1;
	for(int i=0;i<a.length();i++){
		int ch=a[i]-'a';
		p=trie[p][ch];
		flag[p]=true;
	}
	return;
}
//标记操作，顺着 trie 走一遍就好了。
void dfs(int now){
	if(sum[now]){
		ans+='P';//打印情况。
        //注意这里一定不要写 return;
        //因为有可能这是一个单词的前缀，这样就少了一个甚至更多的单词。
	}
	int x=-1;
	for(int i=0;i<26;i++){
		int t=trie[now][i];
		if(!t) continue;
		if(flag[t]) x=i;//记录最长串上的点，最后遍历。
		else{
			ans+=(i+'a');
			dfs(t);
		}
	}
	if(x!=-1){
		ans+=(x+'a');
		dfs(trie[now][x]);
	}//最后遍历的最长串。
	if(flag[now] && x==-1)//当遍历到了最长串的最后一个点，就不用再回退（删除）了。
		finish=true;
	if(!finish) ans+='-';//回溯时删除。
	return;
}

int main(){
	scanf("%d",&n);
	memset(flag,false,sizeof(flag));
	memset(sum,false,sizeof(sum));
	memset(trie,0,sizeof(trie));//不必要的初始化。
	for(int i=1;i<=n;i++){
		cin >> a;insert(a);
		if(jl.length()<a.length()) jl=a;
	}//寻找最长串。
	Mark(jl);
	dfs(1);
	printf("%d\n",ans.length());
	for(int i=0;i<ans.length();i++)
		printf("%c\n",ans[i]);
	return 0;
}
```

# 结语

无耻安利 [blog](https://www.cnblogs.com/lpf-666/)。

简单的 $trie + dfs$，感觉挺简单的...。

主要是要有**题目简化**以及**将题目转化为抽象数据结构**的能力。

完结撒花。

---

## 作者：SuperJvRuo (赞：4)

这题怎么没人做呢？NOIP难度的水题

简化一下题意，找一种字典树的DFS序，满足：从根节点开始，经过所有节点，最后到达一个叶节点，且长度最短。

不难发现，只要找出一个最长的字符串，先在其他字符串上走，后走最长的字符串即可。DFS前，在最长的串上一路打标记，在DFS时后走有标记的点，这样可以保证最短。

```
#include<cstdio>
#include<iostream>
#include<string>

struct Node
{
    int next[26];
    bool mark,end;
}trie[25000*20];
int cnt;

using std::string;

string l;

void Insert(string s)
{
    int length=s.length();
    int u=0;
    for(int i=0;i<length;++i)
    {
        if(!trie[u].next[s[i]-'a'])
            trie[u].next[s[i]-'a']=++cnt;
        u=trie[u].next[s[i]-'a'];
    }
    trie[u].end=1;
}

void Mark(string s)
{
    int length=s.length();
    int u=0;
    for(int i=0;i<length;++i)
    {
        u=trie[u].next[s[i]-'a'];
        trie[u].mark=1;
    }
}

char opt[1000000];
int m;
bool finish;

void dfs(int u)
{
    int mark=-1;
    if(trie[u].end)
        opt[++m]='P';
    for(int i=0;i<26;++i)
    {
        if(trie[trie[u].next[i]].mark)
            mark=i;
        else if(trie[u].next[i])
        {
            opt[++m]=i+'a';
            dfs(trie[u].next[i]);
        }
    }
    if(mark!=-1)
    {
        opt[++m]='a'+mark;
        dfs(trie[u].next[mark]);
    }
    if(trie[u].mark&&mark==-1)
        finish=1;
    if(!finish)
        opt[++m]=45;
    return;
}

int main()
{
    int n;
    std::cin>>n;
    string s;
    for(int i=0;i<n;++i)
    {
        std::cin>>s;
        Insert(s);
        if(s.length()>l.length())
            l=s;
    }
    Mark(l);
    dfs(0);
    
    printf("%d\n",m);
    for(int i=1;i<=m;++i)
    {
        printf("%c\n",opt[i]);
    }
    return 0;
}
```

---

## 作者：StudyingFather (赞：4)

首先建出 Trie 树，容易发现我们的目标是确定一种 DFS 序，使得在遍历所有节点的前提下走过的边数尽可能少。

如果走完最后一个节点要返回根节点的话，那么显然每条边至少要走两次（递归的时候走一次，回溯的时候还要走一次）。

在本题中，我们走完最后一个节点后就不需要返回了。这意味着我们可以少走从最后一个点到根的这些边。

怎样让少走的边尽可能多呢？显然只需让最深的节点最后走到即可。

于是我们可以按这样的方式进行 DFS：先找出每个节点深度最深的子树，每次 DFS 先走完其他子树，再遍历最深的子树即可。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int sig=26;
char res[1000005];
int ans;
struct trie
{
 struct node
 {
  int son[sig],end,ls,dep,maxd;
 }tr[500005];
 int cnt;
 void insert(char* s)
 {
  int u=0;
  for(int i=0;s[i];i++)
  {
   int &v=tr[u].son[s[i]-'a'];
   if(!v)v=++cnt;
   u=v;
  }
  tr[u].end=1;
 }
 void dfs1(int u,int fa)
 {
  tr[u].maxd=tr[u].dep=tr[fa].dep+1;
  tr[u].ls=-1;
  for(int i=0;i<sig;i++)
  {
   int v=tr[u].son[i];
   if(v)
   {
    dfs1(v,u);
    if(tr[v].maxd>tr[u].maxd)
    {
     tr[u].maxd=tr[v].maxd;
     tr[u].ls=i;
    }
   }
  }
 }
 void dfs2(int u)
 {
  if(tr[u].end)res[++ans]='P';
  int ls=tr[u].ls;
  for(int i=0;i<sig;i++)
  {
   int v=tr[u].son[i];
   if(v&&i!=ls)
   {
    res[++ans]='a'+i;
    dfs2(v);
   }
  }
  if(ls!=-1)
  {
   res[++ans]='a'+ls;
   dfs2(tr[u].son[ls]);
  }
  res[++ans]='-';
 }
}t;
char s[25];
int main()
{
 int n;
 scanf("%d",&n);
 int maxl=0;
 for(int i=1;i<=n;i++)
 {
  scanf("%s",s);
  maxl=max(maxl,(int)strlen(s));
  t.insert(s);
 }
 t.dfs1(0,0);
 t.dfs2(0);
 ans-=maxl+1;//排除走完最后一个点的回溯过程
 printf("%d\n",ans);
 for(int i=1;i<=ans;i++)
  printf("%c\n",res[i]);
 return 0;
}
```


---

## 作者：creation_hy (赞：3)

## 前言

这题也太毒瘤了吧。。。

如果你被卡 MLE 了三个点，请看一下 [这个帖子](https://www.luogu.com.cn/discuss/546700)。

## 思路

思路还是很好想的。~~真的有紫吗~~

一眼建 Trie，然后 dfs Trie。

本题唯一难点就在打印机最后可以不清空。（如果没有这个条件，估计降蓝了？）

很显然的一个贪心就是，把 Trie 最长的一条链留到最后去搜。

怎么判断哪个最长呢，一个数组记录每条链长度不就行了。

实现：（提示：请先看完整篇文章，否则后果自负）

初始化：

```cpp
inline void insert(string s)
{
    int cur = 0, curlen = s.size();
    for (char c : s)
    {
        len[cur][c] = max(len[cur][c], curlen--);
        if (!t[cur][c])
            t[cur][c] = ++tot;
        cur = t[cur][c];
    }
    tag[cur] = true;
}
```

遍历：

```cpp
inline void dfs(int x, bool islast)
{
    if (!islast)
    {
        if (tag[x])
            ans += 'P', cnt++;
        for (int i = 0; i < 26; i++)
            if (t[x][i])
            {
                ans += char(i + 'a');
                dfs(t[x][i], 0);
                ans += '-';
                cnt += 2;
            }
    }
    else
    {
        if (tag[x])
            ans += 'P', cnt++;
        int mxp = -1, mxlen = 0;
        for (int i = 0; i < 26; i++)
            if (t[x][i] && len[x][i] > mxlen)
            {
                mxlen = len[x][i];
                mxp = i;
            }
        for (int i = 0; i < 26; i++)
            if (t[x][i] && i != mxp)
            {
                ans += char(i + 'a');
                dfs(t[x][i], 0);
                ans += '-';
                cnt += 2;
            }
        if (~mxp)
        {
            ans += char(mxp + 'a');
            dfs(t[x][mxp], 1);
            cnt++;
        }
    }
}
```

于是便有了我的第一次提交：[link](https://www.luogu.com.cn/record/97686473)。

MLE 了三个点……

~~什么**出题人啊~~

实际上，$62.5$ MB 这么小的空间就不是用来开这么大数组的……

考虑把 $len[][]$ 优化掉。

很显然，最长的一条链的本质上其实就是最长的那个字符串。

所以把最长的字符串找出来，把它在 Trie 上的每个位置都打上标记，不就行了吗？

这样就只需要一个 `bool ismax[5e5]` 了。

实现：

打标记：

```cpp
inline void addtag(string s)
{
    int cur = 0;
    for (char c : s)
    {
        cur = t[cur][c];
        ismax[cur] = true;
    }
}
```

遍历：

```cpp
inline void dfs(int x, bool islast)
{
    if (!islast)
    {
        if (tag[x])
            ans += 'P', cnt++;
        for (int i = 0; i < 26; i++)
            if (t[x][i])
            {
                ans += char(i + 'a');
                dfs(t[x][i], 0);
                ans += '-';
                cnt += 2;
            }
    }
    else
    {
        if (tag[x])
            ans += 'P', cnt++;
        for (int i = 0; i < 26; i++)
            if (t[x][i] && !ismax[t[x][i]])
            {
                ans += char(i + 'a');
                dfs(t[x][i], 0);
                ans += '-';
                cnt += 2;
            }
        for (int i = 0; i < 26; i++)
            if (t[x][i] && ismax[t[x][i]])
            {
                ans += char(i + 'a');
                dfs(t[x][i], 1);
                cnt++;
                break;
            }
    }
}
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int n;
int t[N][26], tot, cnt, pos;
bool tag[N], ismax[N];
string ans;
inline void insert(string s)
{
    int cur = 0;
    for (char c : s)
    {
        if (!t[cur][c])
            t[cur][c] = ++tot;
        cur = t[cur][c];
    }
    tag[cur] = true;
}
inline void dfs(int x, bool islast)
{
    if (!islast)
    {
        if (tag[x])
            ans += 'P', cnt++;
        for (int i = 0; i < 26; i++)
            if (t[x][i])
            {
                ans += char(i + 'a');
                dfs(t[x][i], 0);
                ans += '-';
                cnt += 2;
            }
    }
    else
    {
        if (tag[x])
            ans += 'P', cnt++;
        for (int i = 0; i < 26; i++)
            if (t[x][i] && !ismax[t[x][i]])
            {
                ans += char(i + 'a');
                dfs(t[x][i], 0);
                ans += '-';
                cnt += 2;
            }
        for (int i = 0; i < 26; i++)
            if (t[x][i] && ismax[t[x][i]])
            {
                ans += char(i + 'a');
                dfs(t[x][i], 1);
                cnt++;
                break;
            }
    }
}
inline void solve()
{
    dfs(0, 1);
    cout << cnt << '\n';
    for (char c : ans)
        cout << c << '\n';
}
inline void tonum(string &s)
{
    for (int i = 0; i < s.size(); i++)
        s[i] -= 'a';
}
inline void addtag(string s)
{
    int cur = 0;
    for (char c : s)
    {
        cur = t[cur][c];
        ismax[cur] = true;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    string mxs;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        tonum(s);
        if (s.size() > mxs.size())
            mxs = s;
        insert(s);
    }
    addtag(mxs);
    solve();
    return 0;
}
```

---

## 作者：KAMIYA_KINA (赞：3)

## 题面理解

本题题面中对于一个打字机进行了模拟，要求模拟三种操作：

* 在当前单词的情况下，在尾部插入一个字符。

* 在当前单词的情况下，删除尾部的一个字符。

* 打印出当前的单词。

我们需要的就是给出一个方案，使整体的操作次数最少的情况下，打印出所有的单词。

## 思路

很明显，题面就是让我们想出一种 **贪心** 的策略，使整体的操作次数少。

那么本题有一个显然的结论，对于下面两个字符串：

~~~
kamiyasigoyi
kamiyahentai
~~~

我们发现对于前面的 `kamiya` 是可以不用删掉之后再输入的，也就是说，我在把第一个字符串的 `sigoyi` 给弹出之后就可以直接搞第二个字符串当中的 `hentai` ，这就是第一个优化方式。

这个优化我们是可以用 Trie 树来优化的。很明显，在一个 Trie 树中，所有的前缀只会便利一次，所以说根据 Trie 树建图然后 dfs 就可以得到我们所需要的答案了。

**西卡西！** 

这样的代码交上去，你只能得到 36pts 的成绩，所以说我们定然是哪里的方案不够优秀。

那么我们再考虑这样两个串。

~~~
abssabsdfff
abssac
~~~

假如说当前的操作只有这两个串，那么你的操作应该是先把 `abssac` 给输出来，然后 **退格一个** ，再输出第二个，这样的话就不会像先输出 `abssabsdfff` 那样 **退格六个** ，那么证明了这也是一种贪心策略，那么我们只用在一开始的时候将所有的字符串按照长度 **从大到小** 排序就可以了。

然后我们就 AC 了这道十分有意思的 Trie 树板子题……

等等先别捶我，我知道你们什么意思，为什么 **从大到小** 呢？因为我在写代码的时候，用的是链式前向星来存储一个图的，这样子的话就不用便利所有的根节点从而更快而且操作也十分方便。

如果说你不是很会这个操作，那就看我操作。

## CODE

~~~cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 3e4 + 1;
const int S = 21;
vector<char>ans;//记录答案
string str[N];
int n;
int hd[N * S],nxt[(N * S) << 1],to[(N * S) << 1],tot = 0;//链式前向星

inline void add(const int u,const int v) {
	nxt[++tot] = hd[u],to[tot] = v,hd[u] = tot;
}
/*
由于链式前向星是前插的，那么久证明更小的字符串更后面被插入进来，那么就是说我在dfs的时候就可以先行便利更小的字符串再去便利更大的字符串。
例如：（数字表示字符串长度，0表示初始节点，是一个空节点）
0 -> 4
0 -> 3 -> 4
0 -> 1 -> 3 -> 4
最终便利的时候就会由 1,3,4的顺序便利。
*/
int trie[N * S][26],cnt = 1;//Trie树

char ch[N * S];//当前位置的字符
bool book[N * S];//当前位置是否是单词的结尾
bool comp(string a,string b) {
	return a.size() > b.size();
}
inline void input() {
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> str[i],str[i] = '0' + str[i];
	sort(str + 1,str + 1 + n,comp);//从大到小排序
	for(int i = 1; i <= n; i++) {
		int p = 1;
		int len = str[i].size();
		for(int j = 1,tem; j < len; j++,p = trie[p][tem]) {
			tem = str[i][j] - 'a';
			if(!trie[p][tem]) trie[p][tem] = ++cnt,add(p,trie[p][tem]);
			ch[trie[p][tem]] = str[i][j];
		}
		book[p] = true;
	}
	return ;
}
void dfs(const int now) {
	if(book[now]) ans.push_back('P');
	for(int eg = hd[now];eg;eg = nxt[eg]) {
		ans.push_back(ch[to[eg]]);
		dfs(to[eg]);
		ans.push_back('-');
	}
	return ;//由于是一个有向图，所以不需要在for循环内层return
}
inline void work() {
	dfs(1);
	return;
}
inline void print() {
	while((char)ans.back() == '-') ans.pop_back();//我的程序有点锅就是说在搞完之后还会把所有的单词部分删掉，那么实际上这个操作是没有必要的，所以说就直接删掉就可以了。
	int l = ans.size();
	printf("%d\n",l);
	for(int i = 0; i < l; i++) {
		putchar(ans[i]);
		putchar(10);
	}
	return ;
}
int main() {
	input();
	work();
	print();
	return 0;
}
~~~



##  做题小故事

Merry ： 字母表第十六个是啥啊？

KAMIYA ： p。

Merry ： 我这个为什么会错呢？

KAMIYA ： 你不是减 `'a'` 之后从零开始数吗？

Merry ： 但是我全部的都加一了呀。

KAMIYA ： 我刚刚看到你有一个地方没有加一。（顺手一指）

Merry ：哦！

（Merry提交了代码）

（Merry 得了64pts）

KAMIYA ：为啥这个题还会 T ？

Merry ：我也不知道。

KAMIYA ： 你这 `string` 前插不是找死？

Merry ： 哦！

（Merry把 `string` 改成了 `vector` ）

（Merry AC 了）

KAMIYA ：就离谱。

---

## 作者：reyik (赞：3)

这道题是最值：

看一下数据范围：(~~一脸懵逼~~）暴力肯定过不了：

那么就是贪心或者$DP$:

这题会$DP$的都是特别巨的，所以只有贪心了。

看完体面就想到Trie

然后贪心：

先把任意一个最长的字符串打标记，然后DFS，走打标记的点。

~~好像完了~~

代码：

```
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#define Rint register int
using namespace std;
const int N=5e5+10;
struct trie{
	int nxt[26];
	bool done,vis;
}a[N];
char ans[N<<1];
int sum,cnt=0,n;
string d,maxn="";
inline void add(string s) {
	int now=0,len=s.length();
	for (Rint i=0;i<len;++i) {
		if(a[now].nxt[s[i]-'a']==0) {
			++cnt;
			a[now].nxt[s[i]-'a']=cnt;
		}
		now=a[now].nxt[s[i]-'a'];
	}
	a[now].done=true;
}
inline void mark(string s) {
	int len=s.length(),now=0;
	for (Rint i=0;i<len;++i) {
		now=a[now].nxt[s[i]-'a'];
		a[now].vis=true;
	}
}
bool flag=false;
inline void dfs(int now) {
	int res=-1;
	if(a[now].done) {
		ans[++sum]='P';
	}
	for (Rint i=0;i<26;++i) {
		if(a[a[now].nxt[i]].vis) {
			res=i;
		}
		else if(a[now].nxt[i]!=0) {
			ans[++sum]=i+'a';
			dfs(a[now].nxt[i]);
		}
	}
	if(res!=-1) {
		ans[++sum]=res+'a';
		dfs(a[now].nxt[res]);
	}
	if(res==-1&&a[now].vis) {
		flag=true;
	}
	if(!flag) {
		ans[++sum]='-';
	}
}
int main() {
	scanf("%d",&n);
	for (Rint i=1;i<=n;++i) {
		cin>>d;
		add(d);
		if(d.length()>maxn.length()) {
			maxn=d;
		}
	}
	mark(maxn);
	dfs(0);
	printf("%d\n",sum);
	for (Rint i=1;i<=sum;++i) {
		putchar(ans[i]);
		putchar('\n');
	}
}
```

---

## 作者：灼眼的夏娜 (赞：2)

这个题，应该没有到紫题水平吧。。。

很容易看出来，这就是把字符串全插入后$dfs$一遍，然后他又说操作次数

最小，其实很容易想到，最长的那个词最后输就完了，啥？有不懂的吗？

你看，你要是把词全输出来，肯定整棵树都要遍历没得跑，实际上，这样

一来$P$与单词的操作数量就已经确定了，剩下的只有退格，那要想退格次

数最少，是不是要让最长的最后输（因为最后输就不用退格了）

因此我们在插入到时候，找到最长的一个单词，给它打个标记强制让它最

后输出，就完了。

值得一提的是，这个题很卡空间，我机房大dalao都是因为这个s掉了，所

以数组可千万别乱开哦

这里就给个$dfs$的代码吧，反正其他它也就是个套路

## code

```cpp
void dfs(int x) {//f记录打印顺序，v是判断最长单词上的一个值
	int v = -1;
	if(End[x]) f[++ ans] = 'P';//走到末尾要打印‘P’
	for(R int i = 0;i < 26;++ i) {
		if(vis[Trie[x][i]]) v = i;
		else if(Trie[x][i]) {//走不是最长的一个单词
			f[++ ans] = i + 'a';
			dfs(Trie[x][i]);
		}
	}
	if(v != -1) {
		f[++ ans] = v + 'a';
		dfs(Trie[x][v]);
	}
	else if(vis[x]) flag = false;//如果这个词有标记，就不打印‘-’
	if(flag) f[++ ans] = '-';
}
```


---

## 作者：__wfx (赞：2)

### 来一篇指针题解&最快代码(目前)

这题就是把$n$个字符串插入到Tire树中，之后在Tire树上DFS

由于我们可以不用打印最后一个字符串的退格键 所以我们考虑让最长的那个串做最后打印的串

我们在Trie上的每个节点维护这颗子树中最深的链的深度

往下走的时候我们选择任意一个最长的儿子最后遍历即可

不知道为什么这题用指针写普通的Trie树会MLE三个点

但是指针是一种信仰(~~写数组不可能的这辈子都不可能的~~)，我最后想起了孩子兄弟表示法实现的Trie(一共用了15.77MB)

我们在每个节点上储存当前节点是哪个字符和两个指针(一个指向孩子，一个指向兄弟)
具体细节请看代码

于是我用指针A了该题

```cpp
#include<bits/stdc++.h>
typedef long long LL;
const int N = 200000;
const int inf = 2147483647;
char obuf[1 << 23], *O = obuf;
inline void _(char ch){*O++ = ch;} void print(int x) {if(x < 0) _('-'), x = -x; if(x>9) print(x/10);*O++ = x % 10 ^ 48;}
inline LL read(){
	LL res = 0; char ch = getchar(); bool bo = false;
	while(ch < '0' || ch > '9') bo = (ch == '-'), ch = getchar();
	while(ch >= '0' && ch <= '9') res = (res << 1) + (res << 3) + (ch ^ 48), ch = getchar();
	return bo ? -res : res;
}

int n, sum, ans;

struct node {
	int Max;
	char c;//这个节点的字符是。。。
	bool last;//是否是一个串的结尾
	node *ch, *xd;//ch是指向孩子的指针，xd是指向兄弟的指针
	node (int Max = 0, char c = 0) : Max(Max), c(c) { xd = ch = NULL; last = false; }
} *root;

node* find(node *&o, char c) {//注意o加了引用
	o = o->ch; node *lst = o;
	while(o && o->c != c) lst = o, o = o->xd;//o的孩子中是否有c这个字符
	return lst;//返回c的哥哥
}

void insert(char *s) {
	int len = strlen(s + 1); 
	if(root == NULL) root = new node(len);
	node *o = root;
	for(int i = 1; i <= len; ++i) {
		o->Max = std::max(o->Max, len);
		if(o->ch == NULL) o->ch = new node(len, s[i]);
		node *lst = find(o, s[i]);//查找我们是否有了这个节点
		if(o == NULL) o = new node(len, s[i]), lst->xd = o;//没有我们就new一个，让该节点的兄弟指向该节点
	}
	o->last = true;//打上结尾标记
}

void print(node *o) {
	if(o->last) { _('P'), _('\n'), ++sum, ++ans; }//如果该节点已经是一个串的
	node *k = NULL;
	for(node *i = o->ch; i; i = i->xd) {//访问o的所有儿子
		if(k == NULL && i->Max == o->Max) { k = i; continue; } 
		_(i->c), _('\n'); ++ans;//我用了fwrite在最后统一输出，和别人用一个数组存下来输出是一个道理
		print(i);
	}
	if(k) _(k->c), _('\n'), print(k), ++ans;//有的时候o->ch == NULL
	if(sum != n) _('-'), _('\n'), ++ans;//我们是否已经打印了所有的串，打印了就不用打印最后一个串
}

char s[N];

int main() {	
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", s + 1);
		insert(s);
	}
	print(root);
	printf("%d\n", ans);
	fwrite(obuf, O - obuf, 1, stdout);//fwrite最后统一打印所有的操作序列
	return 0;
}
```


---

## 作者：ForgotDream_CHN (赞：0)

# P4683 Type Printer

首先，**这道题没有紫题难度，甚至连蓝题都算不上**，所以那些看到是紫题就来看题解的同学可以好好思考之后再来看。

### 题意

你要打印 $N$ 个字符串，打印机支持三种操作：在字符串尾部删除一个字符、在字符串尾部加入一个字符、打印当前字符串内的字符。你需要求出最小操作次数与与之对应的操作序列。

### 思路

观察到这个打印机相当于一个栈的结构，于是我们自然地联想到与栈有关的思想：DFS。又有不同字符串的相同的前缀只需要打印一次，也就是说可以将不同字符串的相同前缀合并起来，于是我们又联想到一种可以按前缀储存字符串的数据结构：字典树。

那么此时这道题所需的全部工具就齐了。做法就是：建出字典树，然后在字典树上跑一遍 DFS。建树我就不说了，朴素的 DFS 也是很好写的：

```cpp
void dfs(int cur = 0, int ch = 0) {
	if (cur != 0) ansSeq += 'a' + ch, ans++;
	while (trie.nxt[cur][27]--) ansSeq += 'P', all--, ans++; 
	for (int i = 0; i < 26; i++) {
		if (trie.nxt[cur][i]) dfs(trie.nxt[cur][i], i);
	}
	if (all) ansSeq += '-', ans++;
	return;
}
```

其中的 $\textrm{all}$ 是字符串的个数，$\textrm{ansSeq}$ 是答案的操作序列。

但是，这个东西连样例都跑不过去。

原因其实也很简单，就是**最后一个字符串是不用删除的**，要最优化，那么最后一个字符串就要尽量长一些。而如果像上边这样写，最后一个字符串不是最长的字符串，而是字典序最大的字符串。

于是我们考虑在输入字符串时记录下最长的字符串，然后在插入 Trie 时给最长的串上的节点打上标记，在 DFS 时利用类似树链剖分中优先访问重儿子的方法，强制地将带标记的节点放在最后访问就行了。

### 代码

普通的字典树的转移数组只用开到 $|\Sigma|$ 大小，我多开了两个，一个表示是否为字符串终止点，一个表示是否为最长链上节点。
  
当然，也可以把这两个数组单开出来。

这道题的空间限制相当的严格，注意把握数组的大小，避免 MLE，也可以写指针来动态地分配内存，不过感觉并没什么用。

```cpp
/**
 * @file 	P4683 Type Printer.cpp
 * @author 	ForgotDream
 * @brief 	Trie + DFS
 * @date 	2023-02-03
 */

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using i64u = unsigned long long;
using i128 = __int128;
using Edge = pair<int, int>;

static const int N = 1e5 + 50;
int all, ans;
struct Trie {
	int cnt;
	int nxt[5 * N][28];

	void insert(string s, bool isLongest = false) {
		// isLongest 是最长串标记
		int cur = 0;
		for (int i = 0; i < s.length(); i++) {
			if (!nxt[cur][s[i] - 'a']) {
				nxt[cur][s[i] - 'a'] = ++cnt;
			}
			cur = nxt[cur][s[i] - 'a'], nxt[cur][26] = nxt[cur][26] | isLongest;
 		}
		nxt[cur][27]++, all++;
		return;
	}
} trie;
int n, pivot;
string ansSeq, in[N];

void dfs(int cur = 0, int ch = 0) {
	// pivot 是最长串标记所对应的字符
	int pivot = -1;
	if (cur != 0) ansSeq += 'a' + ch, ans++;
	while (trie.nxt[cur][27]--) ansSeq += 'P', all--, ans++; 
	for (int i = 0; i < 26; i++) {
		if (trie.nxt[cur][i] && trie.nxt[trie.nxt[cur][i]][26]) {
			pivot = i;
			continue;
		}
		if (trie.nxt[cur][i]) dfs(trie.nxt[cur][i], i);
	}
	// 强制地把 pivot 放在最后访问
	if (~pivot) dfs(trie.nxt[cur][pivot], pivot);
	if (all) ansSeq += '-', ans++;
	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> in[i];
		if (i == 1) pivot = 1;
		else if (in[pivot].length() < in[i].length()) pivot = i;
	}

	for (int i = 1; i <= n; i++) trie.insert(in[i], pivot == i);

	dfs();
	
	cout << ans << '\n';
	for (char c : ansSeq) cout << c << '\n';
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

本题让我们维护一个打字机，模拟三种操作：

1. 将当前单词的尾部插入一个字符。

1. 将当前单词的尾部删除一个字符。

1. 打印当前单词。

使给出一种方案，使整体操作最少的情况下打印出所有单词。

我们想到是最少有几次，于是我们能想到贪心算法，于是就能想到 Trie 树。

所以，题目就变成了：确定一个 dfs 的顺序使得树上的所有节点都能访问到，并且都约束于某一个叶子节点。

其实我们能发现，我们找到一个最长字符串，然后先遍历其他单词，最后在进行插入和删除操作，而且要在 dfs 前在最长字符串做标记， dfs 的时候尽量走做过标记的点，这样就能保证次数最短。

 dfs 时，如果这个点不是被标记过的点，就要打印-。

## AC 代码

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long LL;
const int MAXN = 1e6 + 10;
const int INF = 0x3f;
struct node{
	int ne[27];
	bool used;
	bool f;
}head[MAXN];
string l;
int id;
void add(string s){
	int num = 0;
	for(int i = 0;i < s.size(); i++){
		int now = s[i] - 'a';
		if(!head[num].ne[now])head[num].ne[now] = ++id;
		num = head[num].ne[now];
	}
	head[num].f = 1;
} 
void find(string s){
	int num = 0;
	for(int i = 0;i < s.size(); i++){
		int now = s[i] - 'a';
		num = head[num].ne[now];
		head[num].used = true;
	}
}
string x = "";
int m;
bool flag;
#define addP (x += "P")
void dfs(int u){
	int num = -1;
	if(head[u].f)addP;
	for(int i = 0;i < 26; i++){
		if(head[head[u].ne[i]].used)num = i;
		else if(head[u].ne[i]){
			x += (i + 'a');
			dfs(head[u].ne[i]);
		}
	}
	if(num != -1){
		x += (num + 'a');
		dfs(head[u].ne[num]);
	}
	if(head[u].used && num == -1)flag = 1;
	if(!flag)x += "-";
	return ;
}
int main()
{
	int n;
	cin >> n;
	string a;
	for(int i = 0;i < n; i++){
		cin >> a; 
		add(a);
		if(a.size() > l.size())l = a;
	}
	find(l);
	dfs(0);
	cout << x.size() << endl;
	for(int i =0;i < x.size(); i++)cout << x[i] << endl;
    return 0;
}

```
~~跪求管理员通过~~

---

## 作者：eastcloud (赞：0)

## P4683 [ IOI2008 ] Type Printer 题解

### 题意简述

一个打印机支持删除，添加字符和打印三种操作，求打印出所有的字符串需要的最小操作次数。

### 分析

依照样例数据，假设我们将字符串一个一个打印并删除，那么会发现在这过程中，我们删去并添加了一些相同的字符，通过观察可以发现，删除的这些字符为**两个字符串相同的前缀**。

思考如何优化这些前缀，可以自然地想到 trie 树实现时会将两个字符串的相同前缀合并，于是可将所有字符串插入一个 trie 树，使用深搜搜索这棵树，并将操作序列输出。

需要注意的是，最后一个打印的字符串不需要将剩余的字符删除，所以我们需要将最长的字符串放到最后处理，减少删除的长度，使结果最优。

### 代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char tmp[21],way[5005000];
int maxlen,ti,tot=1,trie[500500][27],ans,all,n;
int en[500500],lar[500500];
void dfs(int x){
	int tmp=0;
	if(lar[x]==ti && en[x]==1 && all==n-1){
		way[++ans]='P';//如果是最后一个需要打印的字符串且最长那么不需要删除，直接返回
		return;
	}
	if(en[x]==1){
		way[++ans]='P';
		all++;//已打印++
	}
	for(int i=1;i<=26;i++){
		if(trie[x][i] && lar[trie[x][i]]!=ti){//不是最长的则深搜
			way[++ans]=char('a'+i-1);
			dfs(trie[x][i]);
			way[++ans]='-';
		}
		else if(trie[x][i]) tmp=i;//是则标记
	}
	if(tmp){
		way[++ans]=char('a'+tmp-1);//如果被标记则不删除直接深搜（最后处理）
		dfs(trie[x][tmp]);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>(tmp+1);
		int p=1,len=strlen(tmp+1),flag=0;
		if(len>maxlen){//查找最大的字符串并标记
			maxlen=len;
			ti++;//累加版本，判断时若为最新版则为最长字符串
			flag=1;
		}
		for(int j=1;j<=len;j++){
			int num=tmp[j]-'a'+1;
			if(trie[p][num]==0)trie[p][num]=++tot;
			p=trie[p][num];
			if(flag)lar[p]=ti;//记录版本号
			if(j==len) en[p]=1;
		}// trie 树插入操作
		memset(tmp,0,sizeof(tmp));
	}
	dfs(1);//起点为根节点
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)cout<<way[i]<<endl;
}
```


---

## 作者：water_tomato (赞：0)

本文同步发表于个人博客：[Link](https://www.watertomato.com/p4683-ioi2008-type-printer-%e6%89%93%e5%8d%b0%e6%9c%ba-%e9%a2%98%e8%a7%a3/)。

一段时间没打字符串相关的题了，找道简单的 Trie 练练手。

## 题意

[题目链接](https://www.luogu.com.cn/problem/P4683)。

维护一个复古打印机，支持添加字母，删除字母，打印字母。求用最小步骤打印出所需的所有单词。

## 解析

首先容易想到建 Trie，然后在 Trie 上进行 dfs，每次走到一个结点就添加这个结点对应的字母，若走到了一个单词的结尾就打印，然后在每层 dfs 返回之前删除当前字母。

但是这并不能满足最小步骤。先说结论：**最长的单词最后打印**。

思路及证明如下：

我们考虑最终操作序列中三种操作所占的数量。容易发现添加字母的操作是一定的（一定为结点数），同时打印操作也是一定的（一定为单词数）。我们考虑**最小化删除操作的数量**。

容易发现，**最后**打印的那个单词在 Trie 树上的**一整条链是不用删除**的。而删除操作的数量即为结点数减去这条链的长度，因此只需要这条链最长，即最后打印的单词最长即可，容易维护（详见下方代码）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=25005;
int n,tree[N<<5][26];
int tot,cnt,Ans,maxx;
bool p[N<<5],tag[N<<5];
char s[50],ans[N<<7];
char S[50];
inline void insert(){
	scanf("%s",s);
	int len=strlen(s);
	int u=0;
	if(len>maxx){//记录最长单词
		maxx=len;
		for(int i=0;i<len;i++){
			S[i]=s[i];
		}
	} 
	for(int i=0;i<len;i++){
		int c=s[i]-'a';
		if(!tree[u][c]) tree[u][c]=++tot;
		u=tree[u][c];
	}
	p[u]=1;
}
inline void pre(){//预处理最长单词所在链
	int len=maxx;
	int u=0;
	for(int i=0;i<len;i++){
		int c=S[i]-'a';
		tag[tree[u][c]]=1;//tag 记录是否为最长单词所在链
		u=tree[u][c];
	}
}
inline void print(){
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%c\n",ans[i]);
}
inline void dfs(int u){
	if(p[u]){//打印
		Ans++;
		ans[++cnt]='P';
		if(Ans==n) print();//为了防止进行多余的删除操作，在这里输出
	}
	for(int i=0;i<26;i++){
		if(tree[u][i]&&!tag[tree[u][i]]){
			ans[++cnt]='a'+i;
			dfs(tree[u][i]);
		}
	}
	for(int i=0;i<26;i++){
		if(tree[u][i]&&tag[tree[u][i]]){
			ans[++cnt]='a'+i;
			dfs(tree[u][i]);
		}
	}//先走其他的，最后走最长单词所在链
	if(u!=0) ans[++cnt]='-';
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) insert();
	pre();
	dfs(0);
	return 0;
}
```

---

## 作者：whyl (赞：0)

发我的第一篇IOI的题解

本题容易想到最后保留的肯定是一条链

并且能够print的，能早print一定比晚print要优

所以只用一遍dfs先dfs不是最长链上的

边做边输出即可

```
//code by luotc
#include<bits/stdc++.h>

using namespace std;

const int maxn=500005;

int n,ed[maxn],lenth[25005],td,mx,tot,ans,last;
int ch[500005][26],belong[maxn];
string s[25005];

inline void insert(string s){
	int len=s.length(),now=0;
	for(int i=0;i<len;i++){
		int t=s[i]-'a';
		if(!ch[now][t]) ch[now][t]=++tot;
		now=ch[now][t];
	}
	ed[now]=1;
}

inline void modify(string s){
	int len=s.length(),now=0;
	for(int i=0;i<len;i++){
		int t=s[i]-'a';
		if(!ch[now][t]) ch[now][t]=++tot;
		now=ch[now][t];
		belong[now]=1;
	}
	ed[now]=1;
	last=now;
}

inline void dfs(int x){
	if(ed[x]) printf("P\n");
	if(x==last) return;
	for(int i=0;i<=25;i++){
		if(ch[x][i]){
			if(belong[ch[x][i]]) continue;
			printf("%c\n",i+'a');
			dfs(ch[x][i]);
			printf("-\n");
		}
	}
	for(int i=0;i<=25;i++){
		if(belong[ch[x][i]]){
			printf("%c\n",i+'a');
			dfs(ch[x][i]);
		}
	}
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		lenth[i]=s[i].length();
		if(mx<lenth[i]){
			td=i;
			mx=lenth[i];
		}
	}
	for(int i=1;i<=n;i++){
		if(i==td){
			modify(s[i]);
			continue;
		}
		insert(s[i]);
	}
	cout<<tot*2+n-mx<<endl;
	dfs(0);
	return 0;
}
```
求管理大大放过。。。。

---

## 作者：cold_cold (赞：0)

 [安利一波博客](https://www.cnblogs.com/cold-cold/p/10226718.html)


我们考虑如果打印结束时，不允许有部分字母留在打印机内。

这题应该怎么做

显然我们将所有要打印的字符串放入一棵Trie树

那么答案就是Trie树的节点数乘2+m

打印顺序只要沿树走即可

现在我们再来考虑打印结束时，允许有部分字母留在打印机内的情况

我们发现其实就是最后一个单词不用删除

那么我们让最长的一个单词最后输出即可

实现方式为，记录下最长的串后，在Trie树上打上标记

遍历Trie树时，碰到标记就最后访问

此处实现细节较多，要小心谨慎

总体实现如下：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
inline int read()
{
    register int p(1),a(0);register char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') p=-1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return a*p;
}
const int N=500010;
int n,tot=0,root,all=0,finish;
char du[N],ji[N],ans[1001000];
struct Trie
{
    int nxt[26];
    bool end,mark;
}tree[N];
int newnode()
{
    ++tot;
    memset(tree[tot].nxt,-1,sizeof(tree[tot].nxt));
    return tot;
}
void insert(char *a)
{
    int cur=root,len=strlen(a+1),idx;
    for(int i=1;i<=len;i++)
    {
        idx=a[i]-'a';
        if(tree[cur].nxt[idx]==-1)
            tree[cur].nxt[idx]=newnode();
        cur=tree[cur].nxt[idx];
    }
    tree[cur].end=1;            
}
void biao(char *a)
{
    int cur=root,len=strlen(a+1),idx;
    for(int i=1;i<=len;i++)
    {
        idx=a[i]-'a';
        cur=tree[cur].nxt[idx];
        tree[cur].mark=1;
    }            
}
void DFS(int xx)
{
    if(tree[xx].end) ans[++all]='P';
    int temp=-1,cur;
    for(int i=0;i<26;i++) if(tree[xx].nxt[i]!=-1)
    {
        cur=tree[xx].nxt[i];
        if(!tree[cur].mark)
        {
            ans[++all]=i+'a';
            DFS(tree[xx].nxt[i]);
        }
        else temp=i;
    }
    if(temp!=-1) ans[++all]=temp+'a',DFS(tree[xx].nxt[temp]);
    if(temp==-1&&tree[xx].mark) finish=1;
    if(!finish) ans[++all]='-';
}
int main()
{
    // freopen("input","r",stdin);
    // freopen("output","w",stdout);
    n=read();
    root=newnode();
    for(int i=1;i<=n;i++)
    {
        scanf("%s",du+1);insert(du);
        if(i==1||strlen(du+1)>strlen(ji+1)) strcpy(ji+1,du+1);        
    }
    biao(ji);
    DFS(root);
    printf("%d\n",all);
    for(int i=1;i<=all;i++) printf("%c\n",ans[i]);
    return 0;
}
```

---

