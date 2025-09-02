# A Lot of Games

## 题目描述

Andrew, Fedor and Alex are inventive guys. Now they invent the game with strings for two players.

Given a group of $ n $ non-empty strings. During the game two players build the word together, initially the word is empty. The players move in turns. On his step player must add a single letter in the end of the word, the resulting word must be prefix of at least one string from the group. A player loses if he cannot move.

Andrew and Alex decided to play this game $ k $ times. The player who is the loser of the $ i $ -th game makes the first move in the $ (i+1) $ -th game. Guys decided that the winner of all games is the player who wins the last ( $ k $ -th) game. Andrew and Alex already started the game. Fedor wants to know who wins the game if both players will play optimally. Help him.

## 样例 #1

### 输入

```
2 3
a
b
```

### 输出

```
First
```

## 样例 #2

### 输入

```
3 1
a
b
c
```

### 输出

```
First
```

## 样例 #3

### 输入

```
1 2
ab
```

### 输出

```
Second
```

# 题解

## 作者：SuperJvRuo (赞：21)

### 好心机的一道题啊！

WA了两遍之后才突然明白：这两个人是可以故意输的！

如果这棵Trie树的根节点有必胜策略，那么为了让自己获得最后一局的胜利，我们就要在倒数第二局中故意输。

如果**根节点在有必胜策略的同时还有必败策略**，那么我们只要获得倒数第二局的先手，就可以让自己获得最后一局的先手。以此类推，**第一局的先手可以获得最后一局的胜利**，其必胜策略为：一直使用必败策略，直到最后一局时采取必胜策略。

而**如果根节点只有必胜策略，没有必败策略**，那么先手就会在两个人之中交换。因此，**如果总局数k为奇数，先手胜利，否则后手胜利**，必胜策略为：使用必胜策略。

如果**根节点只有必败策略，那么一定是后手胜利**，因为后手在每一局中都是胜者。

因此我们不仅要像一般的DAG上的博弈论一样，求出每个点是否有必胜策略，还要求出是否有必败策略，最后依据根节点是否有必胜策略、必败策略，以及局数的奇偶来判断胜负。

```
#include<cstdio>
#include<iostream>

using namespace std;

//trie树
struct Node
{
	int ch[26];
	int isStr;
	bool haveSon;
}trie[100005];
int size;

string str;

void insert()
{
	cin>>str;
	int len=str.length();
	int now=0;
	for(int i=0;i<len;++i)
	{
		trie[now].haveSon=1;
		if(!trie[now].ch[str[i]-'a'])
		{
			trie[now].ch[str[i]-'a']=++size;
			now=size;
		}
		else
			now=trie[now].ch[str[i]-'a'];
	}
	++trie[now].isStr;
}

bool win[100005];
bool lose[100005];

//求出各节点是否有必胜策略
int dfs1(int root)
{
	//叶子节点必败，递归终止
	if(!trie[root].haveSon)
		return win[root]=0;
	else for(int i=0;i<26;++i)
	{
		//有一个后继节点是必败的，那么这个节点就是必胜的
        if(trie[root].ch[i]&&!dfs1(trie[root].ch[i]))
			return win[root]=1;
	}
	return win[root]=0;
}

//求出各节点是否有必败策略
int dfs2(int root)
{
	//叶子节点仅有必败策略，递归终止
	if(!trie[root].haveSon)
		return lose[root]=1;
	else for(int i=0;i<26;++i)
	{
		//有一个后继节点没有必败策略，那么当前节点就是必败的
        if(trie[root].ch[i]&&!dfs2(trie[root].ch[i]))
			return lose[root]=1;
	}
	return lose[root]=0;
}

int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;++i)
		insert();
	dfs1(0);
	dfs2(0);
	if(win[0]) 
	{
		if(lose[0])
		{
				printf("First"); 
		}
		else
		{
			if(k&1)
			printf("First");
			else
			printf("Second");
		}
	}
	else
	{
		printf("Second");
	}
}
```

---

## 作者：ironmt (赞：6)

这是一个trie上的博弈论  
用4个二进制数来表示当前节点先手的情况  
00表示无法决定胜负  
01表示必胜  
10表示必败  
11表示可以决定胜负  
转移时先将节点或所有子节点再异或3就可以了  
因为最后多异或了一次所以最后根节点为1的异或同时k为奇数就先手能赢，根节点为3的异或时先手必胜

```cpp
#include <cstdio>
#include <cstring>

const int maxi = 1e5 + 7;

int sz;
int t[maxi][26];
int n, k;
char str[maxi];

int dfs(int tmp)
{
    int ans = 0;
    int leaf = true; //判断当前节点是不是单词结尾，是的话必胜
    for (int i = 0; i < 26; ++i)
        if (t[tmp][i])
        {
            leaf = false;
            ans |= dfs(t[tmp][i]);
        }
    ans ^= 3;
    if (leaf)
        ans = 1;
    return ans;
}

int main()
{
    scanf("%d %d", &n, &k);
    int now;
    for (int i = 0; i < n; ++i)
    {
        scanf("%s", str);
        now = 0;
        for (int j = 0; j < strlen(str); ++j)
        {
            if (! t[now][str[j] - 'a'])
                t[now][str[j] - 'a'] = ++sz;
            now = t[now][str[j] - 'a'];
        }
    }
    int ans = dfs(0);
    if ((! ans) || ((k & 1) && (ans == 2))) //因为最后转移到根节点时多取了一次异或所以也要用3或者1的异或值来判断
        printf("First\n");
    else
        printf("Second\n");
    return 0;
}

```

---

## 作者：xuyuansu (赞：2)

## 题解
首先可以发现题目就是在trie树上博弈，先把trie树建出来，我们就可以根据它来判断先手必胜还是必败：只要这个节点的儿子全都是先手必败，这个节点就是先手必胜，叶子节点为先手必败。

但是我们很快就会发现这样还是有问题，因为它是有多轮的，现在输了不代表最终会输，可能还有要让自己故意失败来掌控主动权的情况，所以我们还要求出先手能不能让自己故意失败（在后手干扰下），和求必胜差不多，叶子节点设为可以故意失败。

最后考虑先手在什么条件下可以保证最后胜利。由于每一局的初始条件只有先后手不同，所以我们考虑最后一局最开始的先手怎样保证胜利。

首先如果每局可以先手必胜，那么后手肯定会干扰先手获得最后一局的先手，那么此时后手会在第二局开始尝试故意失败保持主动权，最后获得先机，但是先手如果想占据先机也需要这样，所以第一种情况：如果一局先手可以决定自己的胜败，那么最后先手胜利。

如果先手只能保证自己胜利，那么如果局数为奇数先手胜利，否则后手胜利。因为彼此作为后手是都可以决定是否获得下一局主动权，所以由局数决定。

如果先手只能决定失败，后手胜利。因为后手可以让它一直失败，直到结束。

如果先手无法保证自己胜利还是失败，那么后手一定胜利。因为它完全掌握生杀大权，一直保持主动。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,k,cnt,son[N][26];
bool f[N][2];
void add(string s)
{
	int now=0;
	for(int i=0;i<(int)s.size();i++)
	{
		int x=s[i]-'a';
		if(!son[now][x]) son[now][x]=++cnt;
		now=son[now][x];
	}
}
void dfs(int x)
{
	f[x][0]=0;f[x][1]=0;
	int s=0;
	for(int i=0;i<26;i++)
	{
		if(!son[x][i]) continue;
		dfs(son[x][i]);s++;
		if(f[son[x][i]][1]==0) f[x][1]=1;
		if(f[son[x][i]][0]==0) f[x][0]=1;
	}
	if(!s) f[x][0]=1;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		string s;cin>>s;
		add(s);
	}
	dfs(0);
	if(f[0][1] && (f[0][0] || k&1)) cout<<"First"<<endl;
	else cout<<"Second"<<endl;
	return 0;
}

```


---

## 作者：xfrvq (赞：1)

## CF455B

[$\tt Link$](/problem/CF455B)

$\tt^\ast1900$？

---

我们考虑建立 $n$ 个字符串的 $\tt Trie$ 树。  
然后把 $\tt Trie$ 树的每个节点视为博弈时的一个状态。  
考虑使用递推计算一个状态的先手有没有必胜策略。  
但是这样并不够。  
因为如果局数 $\ge2$ 并且先手必胜，  
这时倒数第二局的先手可以选择把胜利让给对手。  
然后下一局自己开局，取得胜利。  
所以还要递推计算一个状态的先手有没有必败策略。

---

然后讨论必胜/必败的递推计算。  
这里默认一个 $\tt Trie$ 节点指 **这个节点对应的字符串前缀已经被放完了，现在的先手需要开始放下一个字符**。  
必胜策略就是：叶子节点无，其余节点如果有儿子不存在先手必胜，那么这个节点必胜。  
必败策略就是：叶子节点有，其余节点如果有儿子不存在先手必败，那么这个节点必败。

---

```cpp
#include<iostream>
using namespace std;

const int N = 1e5 + 5;

int c[N][26],tot = 0,n,k,p[N];
string s;

bool dfs1(int u){
	bool sta = false,son = false;
	for(int i = 0;i < 26;++i) if(c[u][i])
		son = true,sta |= !dfs1(c[u][i]);
	return son ? sta : false;
}

bool dfs2(int u){
	bool sta = false,son = false;
	for(int i = 0;i < 26;++i) if(c[u][i])
		son = true,sta |= !dfs2(c[u][i]);
	return son ? sta : true;
}

int main(){
	cin >> n >> k;
	for(int i = 1;i <= n;++i){
		cin >> s;
		int p = 0;
		for(char d : s){
			int &x = c[p][d - 'a'];
			p = x ? x : (x = ++tot);
		}
	}
	bool f = dfs1(0),g = dfs2(0);
	string s[2] = {"First","Second"};
	cout << s[f ? g ? 0 : !(k & 1) : 1] << endl;
	return 0;
}
```

---

## 作者：Azazеl (赞：1)

$~~~~$ ~~我好不容易会判一次先手必胜，你却让我输得那么彻底，焯~~

#### 题意

> $~~~~$ 给出一颗$n$ 个结点的 Trie 树，每轮游戏两名玩家轮流移动当前结点到其某个子结点，不能移动者输。现进行 $k$ 轮游戏，从第二轮游戏及以后都由上轮游戏败者先手，以最后一轮游戏的结果作为最终结果，求第一轮的先手是否必胜。
>
> $~~~~$ $1\leq n\leq 10^5,1\leq k\leq 10^9$ 。

#### 题解

$~~~~$ 以下的先手和后手既可能指**该轮游戏**的先后手，也有可能指**整个游戏**的先后手，请根据语境区分。

$~~~~$ 先考虑 $k=1$ 的时候能不能判，那么由博弈基本常识：**能一步移动到必败态为必胜态，只能一步移动到必胜态为必败态** ，将所有叶子结点置为必败，然后往上推就可以确定某轮游戏先手是否必胜。

$~~~~$ 然而当 $k>1$ 时事情似乎不妙，比如 $k=2$ 且先手是有必胜策略的，即使如此第一轮的先手也一定不想在第一轮赢，否则第二轮的先手就是对方，然而对方此时有必胜策略，从而他输掉了整个游戏。

$~~~~$ 这就启示我们除了判断是否有必胜策略外还应判断有无**必败策略**，具体的判法只要把“失败”看作胜利，也即把叶子结点置为必胜态后往上推。

$~~~~$ 那么最后整棵树其实就只会有以下几种情况：

- 先手**有**必胜策略 **有**必败策略：那么先手只需要在前 $k-1$ 回故意输掉，最后一回合赢即可获胜。
- 先手**有**必胜策略 **无**必败策略：那每回合的先手只能赢，因此回合的先后手就会在两人中间轮流交换，那么当 $k$ 为奇数时全局先手必胜，否则全局先手必败。
- 先手**无**必胜策略，**有**必败策略：那每回合的先手只能输，然后下回合的先手依然是他，所以先手就~~输麻了~~从头到尾都在输，也就自然全局必败。
- 先手**无**必胜策略，**无**必败策略：那往下推一层，后手有必胜策略也有必败策略，那这不就相当于是后手得到了第一种情况吗？所以这个时候先手依然必败。

$~~~~$ 综上，只需要判断一下整棵树的情况，然后再分讨一下就可以得到整个问题的答案了。

#### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int CanWin,CanLose;
struct Trie{
	int tot,ch[500005][26],f[500005],Child[500005];
	void Insert(char S[])
	{
		int len=strlen(S+1),now=1;
		for(int i=1;i<=len;i++)
		{
			if(!ch[now][S[i]-'a']) ch[now][S[i]-'a']=++tot,Child[now]++;
			now=ch[now][S[i]-'a'];
		}
	}
	void Dfs1(int u)
	{
		f[u]=-1; 
		for(int i=0;i<26;i++)
		{
			if(!ch[u][i]) continue;
			if(ch[u][i]) Dfs1(ch[u][i]);
			if(f[ch[u][i]]==-1) f[u]=1;
		}
		if(u==1&&f[u]==1) CanWin=true;
	}
	void Dfs2(int u)
	{
		f[u]=-1;
		if(!Child[u]) f[u]=1;
		for(int i=0;i<26;i++)
		{
			if(!ch[u][i]) continue;
			if(ch[u][i]) Dfs2(ch[u][i]);
			if(f[ch[u][i]]==-1) f[u]=1;
		}
		if(u==1&&f[u]==1) CanLose=true;
	}
}Trie;
char S[100005];
int main() {
	int n,k;
	scanf("%d %d",&n,&k);
	Trie.tot=1;
	for(int i=1;i<=n;i++) scanf("%s",S+1),Trie.Insert(S);
	Trie.Dfs1(1); Trie.Dfs2(1);
	if(CanWin&&CanLose) puts("First");
	if(CanWin&&!CanLose)
	{
		if(k&1) puts("First");
		else puts("Second");
	}
	if(!CanWin&&CanLose) puts("Second");
	if(!CanWin&&!CanLose) puts("Second");
	return 0;
}
```

---

## 作者：mydcwfy (赞：0)

## 1. 题意

两人交替在开始为空字符串的后面加入字符，要求必须随时为给定的字符串集的某一个串的前缀。将会进行 $k$ 次游戏，上一局输的人作为下一局的先手，最后一局胜利的人获得最终的胜利。在足够聪明的情况下，问第一局的先手是否会赢。

字符串的总个数 $\leq10^5$，字符串的总字符数 $\leq10^5$，$k\leq10^9$。

## 2. 思路

首先，我们可以转化为一个在 Trie 上走，不能走者输的情况。

考虑 $k=1$ 的情况：这不就是一个 SG 函数的应用吗？

遍历一遍 Trie，叶节点为先手必败，如果一个节点的某个儿子是先手必败，那么该节点先手必胜，否则先手必败。

那么，我们可以简单的写出代码：

```cpp
void get_trie(int u)
{
	bool has_son = 0;
	for (int i = 0; i < 26; ++ i)
		if (son[u][i]) has_son = 1, get_trie(son[u][i]);
	if (!has_son){
		sg[u] = 0;
		return;
	}
	for (int i = 0; i < 26; ++ i)
		if (son[u][i] && !sg[son[u][i]])
		{
			sg[u] = true;
			return;
		}
	sg[u] = false;
	return;
}
```

接着，我们考虑 $k=2$ 的情况。

如果先手 $k=1$ 是一定会胜而不可能输的（注意，这里指即使先手想输也不可能），那么，先手一定会在前一局的时候尽一切可能去输（感觉有点不合常理），这样他就会获得下一局的先手，而获得最后的胜利。

所以，我们在 $k>1$ 的时候，不仅要考虑先手能否可以胜利，还要考虑先手能否失败。

怎样计算先手能否失败呢？我们将前面叶节点的时候设为必胜（是指一定可以输掉游戏，不是原来的游戏的必胜），那么如果最后根节点是必胜的话，那么他一定可以在走到叶节点为必胜状态，也就是可以输掉。

接着，我们发现先手有四种情况了：可胜可败，只能胜，只能败，不能胜也不能败（由后手控制力）。

1. 可胜可败：发现先手可以操控答案的走向，一定是可以赢的。

2. 只能胜：最开始的先手和后手会交替先走，所以现在要看 $k$ 的奇偶，奇就是先手胜，偶就是后者胜。
3. 只能败：先手每次都会败，也因为每次都败，每次都是先手，所以最后先手败。
4. 不能胜也不能败：后手操控答案的走向，所以一定是输的。

那么，我们就可以写出了最后的判断代码：

```cpp
if ((able_win && able_lose)) puts("First");
else if (able_win) puts(k & 1 ? "First" : "Second");
else if (able_lose) puts("Second");
else puts("Second");
```

## 3. Code

前面基本已经展示了，这里给一个完整代码。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;
int son[N][26], rt = 1, tot = 1;
int id[N], n, k, flag, sg[N], able_lose, able_win;
char str[N];

void insert(int i, char *s)
{
	int u = rt;
	for (int i = 1; s[i]; ++ i)
	{
		if (!son[u][s[i] - 'a']) son[u][s[i] - 'a'] = ++ tot;
		u = son[u][s[i] - 'a'];
	}
	id[i] = u;
}

void get_trie(int u)
{
	bool has_son = 0;
	for (int i = 0; i < 26; ++ i)
		if (son[u][i]) has_son = 1, get_trie(son[u][i]);
	if (!has_son){
		sg[u] = flag;
		return;
	}
	for (int i = 0; i < 26; ++ i)
		if (son[u][i] && !sg[son[u][i]])
		{
			sg[u] = true;
			return;
		}
	sg[u] = false;
	return;
}

int main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; ++ i)
	{
		scanf("%s", str + 1);
		insert(i, str);
	}
	flag = 1, get_trie(1);//flag 是指叶节点是胜还是败
	able_lose = sg[1];
	flag = 0, get_trie(1);
	able_win = sg[1];
	if ((able_win && able_lose)) puts("First");
	else if (able_win) puts(k & 1 ? "First" : "Second");
	else if (able_lose) puts("Second");
	else puts("Second");
	return 0;
}
```

---

## 作者：极寒神冰 (赞：0)

先建立字典树

然后考虑三种情况：

$1.$后手能必胜，那么后手如果一直赢就赢了。

$2.$先手能必胜，且可以必输，那么先手如果一直输到最后一次赢就可以了。

$3.$先手必胜但不能保证必输，那么每次都赢然后交换位置。$k$为奇数时先手赢，反之后手赢。



```
//#pragma GCC optimize(2)
//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define Max(a,b) (a>b)? a : b
using namespace std;

inline char gc(){
    static char In[MAXN],*at=In,*en=In;
    return at==en&&(en=(at=In)+fread(In,1,MAXN,stdin)),at==en?EOF:*at++;
}
template<class tp>
void read(tp &x){
    x=0;
    char c=gc();
    bool sgn=0;
    while((c<'0'||c>'9')&&c!='-')c=gc();
    if(c=='-')sgn=1,c=gc();
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^'0'),c=gc();
    if(sgn)x=-x;
}
char _In[MAXN],*_at=_In;
inline void flush(){fwrite(_In,1,_at-_In,stdout),_at=_In;}
struct _init{~_init(){flush();}}__init;
inline void pc(char c){if(_at==_In+MAXN)flush();*_at++=c;}
template<class tp>
void write(tp x){
    if(!x){pc('0');return;}
    static char buf[43],*at;
    at=buf;
    if(x<0)pc('-'),x=-x;
    while(x)*at++=x%10+'0',x/=10;
    do pc(*--at); while(at!=buf);
}
/*
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
*/
const int N=2e5+10;
int ch[N][26];
int sz;
int n,k;
void insert(char *s)//建立字典树
{
    int p=0;
    for(;*s;s++)
    {
        int id=*s-'a';
        if(!ch[p][id])
        {
            ch[p][id]=++sz;
        }
        p=ch[p][id];
    }
}
int dfs1(int u)//求到叶子节点是否能保证后手必胜
{
    for(int i=0;i<26;i++)
    {
        if(ch[u][i]&&dfs1(ch[u][i])==0)
        {
            return 1;
        }
    }
    return 0;
}
int dfs2(int u)//求先手是否能必输
{
    int have_son=0;
    for(int i=0;i<26;i++)
    {
        if(ch[u][i])
        {
            have_son=1;
            if(dfs2(ch[u][i])==0)  return 1;
        }
    }
    if(have_son==0) return 1;
    return 0;
}
signed main()
{
    read(n),read(k);
    for(int i=1;i<=n;i++)
    {
        char s[N];
        scanf("%s",s);
        insert(s);
    }
    int ok1=dfs1(0),ok2=dfs2(0);
    if(!ok1)
    {
        puts("Second");
    }
    else if(ok1+ok2==2)
    {
        puts("First");
    }
    else
    {
        if(k&1) puts("First");
        else puts("Second");
    }
}
```


---

