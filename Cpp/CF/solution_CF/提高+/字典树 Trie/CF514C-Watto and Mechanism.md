# Watto and Mechanism

## 题目描述

Watto, the owner of a spare parts store, has recently got an order for the mechanism that can process strings in a certain way. Initially the memory of the mechanism is filled with $ n $ strings. Then the mechanism should be able to process queries of the following type: "Given string $ s $ , determine if the memory of the mechanism contains string $ t $ that consists of the same number of characters as $ s $ and differs from $ s $ in exactly one position".

Watto has already compiled the mechanism, all that's left is to write a program for it and check it on the data consisting of $ n $ initial lines and $ m $ queries. He decided to entrust this job to you.

## 样例 #1

### 输入

```
2 3
aaaaa
acacaca
aabaa
ccacacc
caaac
```

### 输出

```
YES
NO
NO
```

# 题解

## 作者：Styx (赞：13)

单模哈希就可以了

这种东西只要不被面向模数hack，随便取一个11-12位大质数应该就能过

具体做法就是把字典串都先hash掉扔到set里  
然后对于输入串，每个串把每一位分别换成另外两个字母，计算新串的hash值并且在set里找是否插入过这个值，这个操作对于每个字母位复杂度是O(logn)的。

大质数就取23333333377之类的意思一下就可以了

代码如下：
```cpp
#include<bits/stdc++.h>
#define mod 23333333377ll
using namespace std;

set<long long> ht;
int n,m;

string tmp;

long long get_hash(string x)
{
	int len=x.length();
	long long hash_val=0;
	for(int i=0;i<len;i++)
	{
		hash_val=(hash_val*4+1ll*(x[i]-'a'))%mod;
	}
	return hash_val;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		cin>>tmp;
		ht.insert(get_hash(tmp));
	}
	for(int i=1;i<=m;i++)
	{
		int flag=0;
		cin>>tmp;
		long long h=get_hash(tmp);
		int len=tmp.size();
		long long base=1;
		for(int j=len-1;j>=0;j--)
		{
			if(flag) break;
			for(int k=0;k<3;k++)
			{
				if(tmp[j]-'a'==k) continue;
				long long res=(h-(tmp[j]-'a')*base%mod+k*base%mod+mod)%mod;
				if(ht.count(res))
				{
					flag=1;
					break;
				}
			}
			base=base*4%mod;
		}
		if(flag) puts("YES");
		else puts("NO");
	}
}
```




---

## 作者：_luanyi_ (赞：12)

涉及此类字符串匹配的问题，可以考虑使用 trie。  
此题插入较为常规，故略过。  
重点在查询。  
由于题目要求恰好一个字符不同，又因为所有字符均为 `a`，`b` 和 `c` 中的一种，种类数小的可怜，直接暴力 dfs。  
考虑构造 `dfs(id, rt, tag)` ，表示现在考虑字符串第 $id$ 位，此时在 trie 中节点 $rt$ 上，且第 $1$ 到 $id-1$ 位中是否已经存在一位不同。按照题意统计答案即可。  
具体的看代码吧。

***

## code

```cpp
#include <bits/stdc++.h>
#define fq(i,a,b) for (int i = (a); i <= (b); i++)
#define fnq(i,a,b) for (int i = (a); i < (b); i++)
#define nfq(i,a,b) for (int i = (a); i >= (b); i--)
#define nfnq(i,a,b) for (int i = (a); i > (b); i--)
#define fqs(i,a,b,c) for (int i = (a); i <= (b); i += (c))
#define fnqs(i,a,b,c) for (int i = (a); i < (b); i += (c))
#define nfqs(i,a,b,c) for (int i = (a); i >= (b); i -= (c))
#define nfnqs(i,a,b,c) for (int i = (a); i > (b); i -= (c))
#define elif else if
using namespace std;

//#define int long long

//#define GRAPH
//const int EDGES = -1;
//const int VERTEXES = -1;
////# define EDGE_W
////typedef int W_TYPE;

//#define COMPLEX

inline int rd () {
	int f = 1;
	char ch = getchar ();
	while (!isdigit (ch)) (ch == '-' ? (f = -1) : 0), ch = getchar ();
	int num = 0;
	while (isdigit (ch)) num = num * 10 + ch - '0', ch = getchar ();
	return num * f;
}
#define d rd ()

inline int rd (const int modp) {
	int f = 1;
	char ch = getchar ();
	while (!isdigit (ch)) (ch == '-' ? (f = -1) : 0), ch = getchar ();
	int num = 0;
	while (isdigit (ch)) num = (num * 10 + ch - '0') % modp, ch = getchar ();
	return (num * f % modp + modp) % modp;
}

#ifdef GRAPH
struct Edge {
	int v, nxt;
# ifdef EDGE_W
	W_TYPE w;
# endif
	Edge () {}
# ifdef EDGE_W
	Edge (int _v, W_TYPE _w, int _nxt) {v = _v, w = _w, nxt = _nxt;}
# else
	Edge (int _v, int _nxt) {v = _v, nxt = _nxt;}
# endif
} edge[EDGES];
int head[VERTEXES], ecnt;
# ifdef EDGE_W
void addedge (int u, int v, W_TYPE w) {edge[++ecnt] = Edge (v, w, head[u]); head[u] = ecnt;}
#  define fe(u) for (int i = head[u], v, w; v = edge[i].v, w = edge[i].w, i; i = edge[i].nxt)
# else
void addedge (int u, int v) {edge[++ecnt] = Edge (v, head[u]); head[u] = ecnt;}
#  define fe(u) for (int i = head[u], v; v = edge[i].v, i; i = edge[i].nxt)
# endif
void init () {memset (head, 0, sizeof head); ecnt = 0;}
#endif

#ifdef COMPLEX
struct cpx {
	double a, b;
	cpx () {a = 0, b = 0;}
	cpx (double _a) {a = _a, b = 0;}
	cpx (double _a, double _b) {a = _a, b = _b;}
	friend cpx operator + (cpx a, cpx b) {return cpx (a.a + b.a, a.b + b.b);}
	friend cpx operator - (cpx a, cpx b) {return cpx (a.a - b.a, a.b - b.b);}
	friend cpx operator * (cpx a, cpx b) {return cpx (a.a * b.a - a.b * b.b, a.b * b.a + a.a * b.b);}
	friend cpx operator / (cpx a, cpx b) {return cpx ((a.a * b.a + a.b * b.b) / (b.b * b.b + b.a * b.a), (a.b * b.a - a.a * b.b) / (b.b * b.b + b.a * b.a));}
	friend cpx operator += (cpx &a, cpx b) {return a = a + b;}
	friend cpx operator -= (cpx &a, cpx b) {return a = a - b;}
	friend cpx operator *= (cpx &a, cpx b) {return a = a * b;}
	friend cpx operator /= (cpx &a, cpx b) {return a = a / b;}
};
#endif
const int maxn = 1005000;
int ch[maxn][3], tag[maxn], cnt;
char s[maxn];
void insert () {
	int p = 0, l = strlen (s + 1);
	fq (i, 1, l) { int c = s[i];
		if (!ch[p][c - 'a']) ch[p][c - 'a'] = ++cnt;
		p = ch[p][c - 'a'];
	} tag[p] = 1;
}
int len;
bool dfs (int i, int p, int tg) {
	if (i == len + 1) return !tg && tag[p];//查到末尾，判断是否满足题意，该位置是否为一个字符串的结尾
	int c = s[i] - 'a';
	if (ch[p][c] && dfs (i + 1, ch[p][c], tg)) return 1;//该位不改变
	if (!tg) return 0;//之前变过了，这一位变不了，失败返回0
	fq (j, 0, 2) if (c != j && ch[p][j] && dfs (i + 1, ch[p][j], 0)) return 1;//这一位改变，成功则返回1
    return 0;//都不成功，返回0
}
signed main () {
	int n = d, m = d; while (n--) {scanf ("%s", s + 1); insert ();}
	while (m--) {
		scanf ("%s", s + 1); len = strlen (s + 1);
		puts (dfs (1, 0, 1) ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：serverkiller (赞：9)

trie树和dfs

很简单对吧，都是常规操作

~~当时wa了很多次~~


```cpp
#include <bits/stdc++.h>
using namespace std;

char s[600010];
int trie[400001][26],val[400001],cnt = 0;

void insert()//建树
{
    int u = 0,v,len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        v = s[i] - 'a' +1;
        if (!trie[u][v])
        {
        	trie[u][v] = ++cnt;
        	memset(trie[cnt],0,sizeof(trie[cnt]));
        }
        u = trie[u][v];
        if (i == len-1) val[u] = 1;
    }
}

bool dfs(int r,int u,int num) 
{
    if (s[r]) 
    {
    	int v = s[r] - 'a' + 1;
    	if (trie[u][v])
        {
            if (dfs(r+1,trie[u][v],num)) return true;
        }
        if (!num)
        {
            for(int i = 1; i <= 3; i++)
            {
                if (i != v && trie[u][i])
                    if (dfs(r+1,trie[u][i],num+1)) return true;
            }
        }
    }
    else if (num && val[u]) return true;
    return false;
}

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    memset(val,0,sizeof(val));
    for (int i = 0; i < n; i++)
    {
        scanf("%s",s);
        insert();
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%s",s);
        if (dfs(0,0,0)) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```


---

## 作者：M_CI (赞：6)

比较好的 Trie 树练手题。

### 思路

首先，Trie 树有 insert 和 find 两个函数。

insert 使用遍历，在遍历原字符串时，如果未找到这个字符对应的节点，则增添该节点，然后将当前遍历到的节点更新，遍历完整个字符串后标记遍历到的最后一个节点。

```cpp
void insert (string s) {
	int len=str.size (),root=0;//len 为字符串长度，root 为当前遍历到的节点
	for (int i=0;i<len;i++) {
		int c=str[i]-'a';//当前字符
		if (!trie[root][c])//如果没有该节点
			trie[root][c]=++tot;//增加该节点
		root=trie[root][c];//更新当前遍历点
	}
	flag[root]=1;//标记最后节点
}
```

find 使用深搜，在递归搜索目标字符串时，如果当前递归到的位置超过字符串总长，则判断是否恰好有一个字符与原字符串不同，且最后一个节点被标记，是则返回 true，否则返回 false。然后判断如果当前已修改超过一次，返回 false。最后判断如果可以更改且改完后符合条件，返回 true。若都不行则返回 false。

```cpp
bool find (int pos,int len,int root,bool tag) {
	if (pos>len) return !tag&&flag[root];//递归完字符串，判断是否符合条件
	int c=str[pos]-'a';//当前字符
	if (trie[root][c]&&find (pos+1,len,trie[root][c],tag)) return true;
	if (!tag) return false;//如果改过了又要改，返回 false
	for (int j=0;j<3;j++)
		if (c!=j&&trie[root][j]&&find (pos+1,len,trie[root][j],!tag))
			return true;//如何改这一个字符可行，返回 true
	return false;//都不行，返回 false
}
```

完整代码就不贴了。

---

## 作者：Juanzhang (赞：2)

**思路：**

- **hash** ： 读入时将所有满足题意的字符串$hash$放入$set$

@ZJQ90202 巨佬已经说得很清楚了，此题可以用$Trie$。就让我来发一个$hash$的题解吧。

$CF$的$hack$机制挺有用~~有毒~~的，**可以面向对方$hash$函数$hack$**

可以看看评测记录，五次提交，尝试了四种方法

**一、** $hash + unsigned$ $long$ $long$ 自然溢出

- $WA$ $on$ $test$ $26$

> ~~当时以为能过~~

**二、** 双$hash + unsigned$ $long$ $long + unsigned$ $int$ 自然溢出

- $WA$ $on$ $test$ $27$

>  悲剧，就只多过了一个测试点

**三、** $hash + 10^9+7$ 大质数取模

- $WA$ $on$ $test$ $16$

> 没有料到$emm$，此题数据真的毒瘤

**四、** $hash + 10^9+7$ $+ 10^9+9$ 孪生质数、大质数取模

- $AC$

> ~~终于过了emm~~

~~AC苦旅~~

我这只小蒟蒻已经卒了

**代码**

- 双$hash + unsigned$ $long$ $long + unsigned$ $int$ 自然溢出

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair <ui, ull> puu;
const int maxn = 6e5 + 10;
int n, m;
ui pow1[maxn];
ull pow2[maxn];
char str[maxn];

set <puu> s;

ui hash1(char* str) {
	ui res = 0;
	for (int i = 0; i < strlen(str); i++) {
		res = (res << 1) + res + (str[i] - 'a');
	}
	return res;
}

ull hash2(char* str) {
	ull res = 0;
	for (int i = 0; i < strlen(str); i++) {
		res = (res << 1) + res + (str[i] - 'a');
	}
	return res;
}

int main() {
	pow1[0] = pow2[0] = 1;
	for (int i = 1; i <= 6e5; i++) {
		pow1[i] = (pow1[i - 1] << 1) + pow1[i - 1];
		pow2[i] = (pow2[i - 1] << 1) + pow2[i - 1];
	}
	scanf("%d %d", &n, &m);
	gets(str);
	for (int i = 1; i <= n; i++) {
		gets(str);
		ui t1 = hash1(str);
		ull t2 = hash2(str);
		int len = strlen(str);
		for (int j = 0; j < len; j++) {
			for (int k = 0; k < 3; k++) {
				if (k != str[j] - 'a') {
					s.insert(make_pair(t1 - (pow1[len - j - 1] * (str[j] - 'a')) + (pow1[len - j - 1] * k), t2 - (pow2[len - j - 1] * (str[j] - 'a')) + (pow2[len - j - 1] * k)));
				}
			}
		}
	}
	for (; m--; ) {
		gets(str);
		puts(s.count(make_pair(hash1(str), hash2(str))) ? "YES" : "NO");
	}
	return 0;
}
```

- $hash + 10^9+7$ $+ 10^9+9$ 孪生质数、大质数取模

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <ll, ll> pll;
const ll mod1 = 1e9 + 7;
const ll mod2 = 1e9 + 9;
const int maxn = 6e5 + 10;
int n, m;
char str[maxn];
ll pow1[maxn], pow2[maxn];

set <pll> s;

ll hash1(char* str) {
	ll res = 0;
	for (int i = 0; i < strlen(str); i++) {
		res = ((res << 1) + res + str[i] - 'a') % mod1;
	}
	return res;
}

ll hash2(char* str) {
	ll res = 0;
	for (int i = 0; i < strlen(str); i++) {
		res = ((res << 1) + res + str[i] - 'a') % mod2;
	}
	return res;
}

int main() {
	pow1[0] = pow2[0] = 1;
	for (int i = 1; i <= 6e5; i++) {
		pow1[i] = ((pow1[i - 1] << 1) + pow1[i - 1]) % mod1;
		pow2[i] = ((pow2[i - 1] << 1) + pow2[i - 1]) % mod2;
	}
	scanf("%d %d", &n, &m);
	gets(str);
	for (int i = 1; i <= n; i++) {
		gets(str);
		int len = strlen(str);
		ll t1 = hash1(str), t2 = hash2(str);
		for (int j = 0; j < len; j++) {
			for (int k = 'a'; k <= 'c'; k++) {
				if (k != str[j]) {
					s.insert(make_pair((t1 + (pow1[len - j - 1] * (k - str[j])) + (mod1 << 1) + mod1) % mod1, (t2 + (pow2[len - j - 1] * (k - str[j])) + (mod2 << 1) + mod2) % mod2));
				}
			}
		}
	}
	for (; m--; ) {
		gets(str);
		puts(s.count(make_pair(hash1(str), hash2(str))) ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：Jμdge (赞：2)

## 首先先介绍一下题意（管管可视为翻译）：

给出n个字符串（建立trie树）,然后再给出m个字符串,
让你判断在原给定的n个字符串中是否出现过出现过与这m个字符串互异的字符数恰好为1的字符串
###### （即字符串长度相同,并且 有且仅有一个字符不同,不过原题中的意思好像是字符串差异为1啊,没说完全相同的字符串不算满足要求,但是事实上给出的数据就是严格要求字符串之间有一个字符不同的= =|||）,
如果有则输出YES,没有则输出NO,依次输出答案。
然后字符串总数不超过6e5,字符总数也不超过6e5（应该吧...）


题目分析：trie树+深搜（可以算是水题但是也不算太太太水）
```
解题步骤：
1.建trie树,对于每个字符串结尾的节点标记true
（但是这里有一个多出来的操作,用于深搜时的剪枝,不过效率有没有提高我也没测,有兴趣的童鞋可以测一下）
2.依次读入m个字符串并在trie树中深搜查找是否有满足条件的字符串
3.输出答案return 0
```

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define ll long long
using namespace std;
const int M=7e5+100;
const int inf=1e9;
int n,m,len,cnt,now;
int to[M][3],lt[M];
bool is[M],flag;
string s;
bool dfs(int at,int now) {
	if(at==len){ //搜索到尾了
		if(is[now] && !flag) //当前节点有标记且flag已被标记为0
			return true;
		return false; //任一条件不满足都返回false
	}
	int tmp=s[at]-'a';
	if(lt[now]<len) //剪枝操作,同上,效率有没有提高是不清楚的不过能过
		return false;
	for(int i=0; i<3; ++i)
	if(to[now][i]){
		if(i==tmp){ //与当前的字符相同
			if(dfs(at+1,to[now][i]))
				return true;
		}
		else if(flag){ //与当前的字符不同
			flag=0;
			if(dfs(at+1,to[now][i]))
				return true;
			flag=1;
		}
	}
	return false;
}
int main() {
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1; i<=n; ++i) { //读入n个字符串并建trie树
		cin>>s, len=s.length();
		lt[0]=max(lt[0],len), //这里就是剪枝,lt数组记录当前节点以下的最长字符串长度,深搜时若搜到了长度小于当前字符串的枝条则剪枝
        now=0;
		for(int j=0; j<len; ++j) {
			int tmp=s[j]-'a';
			if(!to[now][tmp])
				to[now][tmp]=++cnt;
			now=to[now][tmp];
			lt[now]=max(lt[now],len);
		}
		is[now]=1;
	}
	while(m--) { //深搜查询m个字符串
		cin>>s, len=s.length(), flag=1;
		if(dfs(0,0)) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```




然后第二种算法是Hash（想看的童鞋可以看一看,很短的）
```
#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
#define ll unsigned long long
#define P make_pair
using namespace std;
const int M=6e5+100;
const ll mod=99991;
int n,m; string s;
set< pair<int,ll> > st; ll f[M]={1,1};  //make_pair了之后貌似是快了一点
ll Hash() {
	int len=s.length();
	ll tmp=0;
	for(int i=0; i<len; ++i)
		tmp=tmp*mod+s[i];
	return tmp;
}
bool check() {
	int len=s.length();
	ll h=Hash();
	for(int i=0; i<len; ++i) for(char c='a'; c<='c'; ++c)
		if(c!=s[i] && st.find(P(len,h-s[i]*f[len-i]+c*f[len-i]))!=st.end())
			return true;
	return false;
}
int main() {
	ios::sync_with_stdio(false);
	for(int i=2; i<M; ++i)
	f[i]=f[i-1]*mod;
	cin>>n>>m;
	for(int i=1; i<=n; ++i)
		cin>>s, st.insert(P(s.length(),Hash()));
	while(m--) {
		cin>>s;
		if(check()) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```

但是这个代码WA在了第27个点上,表示很难受,改了很久,一直以为是mod的值的问题,想想数据可能精心构造过,但是别人的Hash就过了：


```
#include <cstdio>
#include <iostream>
#include <cstring>
#include <set>
using namespace std;
typedef long long ll;
const int MAX = 1e6 + 10;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int KEY = 257;//ORZ
int n, m;
ll f[MAX];
set <ll> s;
char s1[MAX];
char s2[MAX];
void inti() {
    f[0] = 1;
    for(int i = 1; i <= MAX; i++){
        f[i] = f[i-1] * KEY % MOD;
    }
}
ll Hash(char *s1) {
    int len = strlen(s1);
    ll tmp = 0;
    for(int i = 0 ; i < len; i++){
        tmp = (tmp * KEY + s1[i]) % MOD;
    }
    return tmp;
}
bool check(char *s2) {
    int len = strlen(s2);
    ll h = Hash(s2);
    for(int i = 0 ; i < len; i++){
        for(ll ch = 'a'; ch <= 'c'; ch++){
            if(ch == s2[i]) continue;
            if(s.find((((ch - s2[i]) * f[len - i - 1] + h)%MOD + MOD)%MOD) != s.end())
                return true;
        }
    }
    return false;
}
int main() {
    inti();
    while(~scanf("%d%d", &n, &m)){
        for(int i = 1; i <= n; i++)
            scanf("%s", s1),
            s.insert(Hash(s1));
        for(int i = 1; i <= m; i++)
            scanf("%s", s2),
            puts(check(s2) ? "YES" : "NO");
    }
    return 0;
}
```

很奇怪...
如果有童鞋看出来什么了可以评论一下,我也是有点无能为了了

---

## 作者：liu_yi (赞：1)

## 题目大意

给定 $n$ 个字符串，一共有 $m$ 次询问，每次询问给你一个字符串，问你给定字符串是否有一个满足恰好有一个字符不同于询问的字符，有就输出 ```YES```，没有就输出 ```NO```，字符串中只包括 ```a```，```b```，```c``` 三种字符。

## 解题思路
由于是匹配字符串，所以考虑使用 trie 树求解，插入操作很常规，不再赘述，主要讲一下怎样查询。

由于字符种类很少，只有三种，考虑直接在 trie 树上搜索，每次枚举三种字符，若目前的字符串不在 trie 树内，直接跳过；若在，看与当前查询的字符串上的字符相不相等，如果相等，就把修改次数加一，最后匹配结束时判一下字符串存不存在，修改次数是否等于一。

还有两个小剪枝，如果修改操作已经大于一了，或已经找到答案了，就回溯。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,trie[600010][4],cnt,p,c;
bool end_[600010],flag;
string s;
inline int read(){
	register int step=1,s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
	    if(ch=='-')step=-1;
	    ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
	    s=(s<<1)+(s<<3)+ch-'0';
	    ch=getchar();
	}
	return step*s;
}
inline void insert(string s){
    p=0;
    for(register int i=0;i<s.size();i++){
        c=s[i]-'a';
        if(!trie[p][c])trie[p][c]=++cnt;
        p=trie[p][c];
    }
    end_[p]=1;
}
inline void find(register int dep,register int pos,register int cnt){
    if(cnt>=2||flag)return ;
    if(dep==s.size()){
        if(end_[pos]&&cnt==1)flag=1;
        return ;
    }
    for(register int i=0;i<=2;i++){
        if(!trie[pos][i])continue;
        if(s[dep]-'a'==i)find(dep+1,trie[pos][i],cnt);
        else find(dep+1,trie[pos][i],cnt+1);
    }
}
int main(){
    n=read(),m=read();
    for(register int i=1;i<=n;i++){
        cin>>s;
        insert(s);
    }
    while(m--){
        cin>>s;
        flag=0;
        find(0,0,0);
        if(flag)puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：Computer1828 (赞：1)

Trie 树 + BFS 跑到最优解了……

------------

考虑建出 Trie 树，记录每个文本串最后在树上终止的节点位置。

然后对于模式串在树上 BFS，注意下一个节点加进队列需要分情况讨论：

如果此前还没有修改过，那么此时可以修改，去到一个树上有标号且不是下一个字符的节点；或者不修改，但是要保证下一个字符可以在树上匹配。

如果此前修改过，那么仅当下一个字符可以在树上匹配才能加入队列。

代码：

```cpp
#define N 600005
int ch[N][3];//Trie 树
bool vis[N];//u 这个节点是否为某个文本串结尾
struct node{int u,dep,usd;}que[N*3];
bool bfs(char *str){
	int hd = 1,tl = 0,len = strlen(str);
	que[++tl] = (node){0,0,0};
	while(hd <= tl){
		node np = que[hd++];
		int u = np.u,dep = np.dep,usd = np.usd;
		if(dep == len){
			if(usd && vis[u]) return true;
			else continue;
		}
		int typ = str[dep]-'a';
		if(usd == 0){
			if(ch[u][typ]) que[++tl] = (node){ch[u][typ],dep+1,0};
			for(int i = 0;i<=2;++i){
				if(typ == i || ch[u][i] == 0) continue;
				que[++tl] = (node){ch[u][i],dep+1,1};
			}	
		}else if(ch[u][typ]){
			que[++tl] = (node){ch[u][typ],dep+1,1};
		}
	}
	return false;
}
```

---

## 作者：chlchl (赞：1)

这个题蛮简单的，为什么是紫题呢？

## 题意简述
给定 $n$ 个文本串和 $m$ 个模式串，问对于每个模式串，是否存在与其**刚好有一个**字符不相同的文本串。

## Solution
本题做法颇多，~~有跑了 10.02s 的哈希~~，也有跑了 732ms 的神奇做法（严重怀疑这位仁兄用的 SAM，快到离谱）。

注意到字符串只包含 $a,b,c$，且范围不太大，所以考虑 Trie 树 + bfs。

首先对于文本串建出 Trie 树，这个非常[模板](https://www.luogu.com.cn/problem/P8306)，这里不再赘述。

然后开队列存下当前字符对应 Trie 的节点、原串下标和是否已经走过不相同的字符。

考虑当前这个位置的状态：
- 如果还没有经过任何一个不相同的字符，则该节点所有出边都可以走。注意如果走到不一样的字符，``push`` 新元素的时候要把标记变为 $1$。
- 如果已经经过了不相同的字符，只能顺着跟当前字符一样的那条边走，标记仍然为 $1$。

剩下边界和枚举等，自己看代码吧，有注释的。

## 代码
为了拼最优解，我用了手写队列。

[AC 的可以看看我的 STL 版（没开 O2 就是慢）](https://www.luogu.com.cn/record/83161494)。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M = 6e5 + 10;
int n, m, len;
int tot, cnt[M], isend[M], son[M][5];
char s[M];
struct zm{int u, p, tag;} q[M];

void insert(char *s){
	int u = 0, k = strlen(s + 1); 
	for(int i=1;i<=k;i++){
		int x = s[i] - 'a';
		if(!son[u][x])	son[u][x] = ++tot;
		u = son[u][x];
	}
	isend[u] = 1;
}//基础的插入

bool query(char *s){
	int l = 1, r = 0;
	q[++r] = (zm){0, 1, 0};//插入初始节点
	while(l <= r){
		zm u = q[l++];
		if(u.p == len + 1){//这与 dfs 的边界一样的，整个字符串都遍历完了
			if(u.tag && isend[u.u])	return 1;//不加isend的判断居然也能过，但是不要省
			continue;
		}
		int x = s[u.p] - 'a';
		if(!u.tag){//如果没有经过不相同的字符，所有出边都枚举一下
			for(int i=0;i<3;i++){
				if(!son[u.u][i])	continue;
				q[++r] = (zm){son[u.u][i], u.p + 1, (i != x)};//注意tag的细节
			}
		}else if(son[u.u][x])	q[++r] = (zm){son[u.u][x], u.p + 1, 1};
        //已经走过了，还要判断当前的u有没有这个儿子！
	}
	return 0;
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++){
		scanf("%s", s + 1);
		insert(s);
	}
	while(m--){
		scanf("%s", s + 1);
		len = strlen(s + 1);
		printf(query(s) ? "YES\n" : "NO\n");
	}
	return 0;
}
```

开 O2 之后的测评记录：[link](https://www.luogu.com.cn/record/83164816)，也是成功跑到最优解第一页前部。



---

## 作者：20111019Yu (赞：1)

一道简简单单的 Trie。~~虽然本人本来也不会写，但是在网上学了一分钟就会了~~。


------------
# 思路
因为标签说了要用 Trie，所以我们知道这一题要用 Trie。[算法传送门](https://oi-wiki.org/string/trie/)

1. 为了给后面的查找做准备，我们可以先用 nxt 来记录某个节点的下一个节点。

1. 为了避免 find 函数从字符串中截取一段然后用这段和询问的字符串作比较，我们再用 quit 来记录这个节点是否为某字符串结尾。

1. 用 find 查找是否存在，最后输出答案

# 易错

1. 没判如果 cnt 大于等于 $2$ 立刻返回。~~爆时间~~

1. 不写 scanf ，快读或不解绑。~~爆时间~~

1.  find 函数加一个 string 类型的自定义函数。~~爆空间，错了好久~~
# code

```cpp
#include <iostream>//养成好习惯
using namespace std;
int n, m, cnt, nxt[600005][3];//指针
string s, str;
bool opt, quit[600005];

void update(string s){
    int k = s.size(), pos = 0;//pos为当前节点编号
    for( int i = 0; i < k; i++ ){
        int init = s[i] - 'a';
        if(!nxt[pos][init]) nxt[pos][init] = ++cnt;//如果没有，则增添一个
        pos = nxt[pos][init];//实时更新当前节点
    }
    quit[pos] = 1;
}
void find(int step, int pos, int cnt){//step为查询的字符串的字符位置
    if(opt || cnt >= 2) return;//不符合或已找到就返回
    if(step == str.size()){
        if(quit[pos] && cnt == 1) opt = 1;//找到直接返回，直到退出
        return;
    }
    for( int i = 0; i < 3; i++ ){
        if(!nxt[pos][i]) continue;//没有就跳过
        if(str[step] - 'a' == i) find(step + 1, nxt[pos][i], cnt);
        else find(step + 1, nxt[pos][i], cnt + 1);//正常深搜
    }
}

int main(){
    ios::sync_with_stdio(0);//解绑，此题卡输入
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for( int i = 1; i <= n; i++ ){
        cin >> s;
        update(s);//加入节点
    }
    while(m--){
        cin >> str;
        opt = 0;//记得清零
        find(0, 0, 0);
        if(opt) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;//养成好习惯2
}
```

因本人对码风有严格的奇怪要求，若导致看不懂，勿喷。

---

## 作者：OIer_ACMer (赞：0)

~~为啥一个字典树和深搜的组合也能撑到蓝题？？？~~


------------
## 大致思路：
思路就是 Trie 和树上 dfs 的组合，我大致讲一下：

1. 首先，我们先用 $son$ 数组来存储字典树中的每个字符底下的儿子是什么，为后面的深搜做准备。

2. 接着，我们就要用 $\operatorname{find}$ 函数从第一层（记住，第一层是**不存字符**的，这时 Trie 树的性质）开始搜索，每到一层我们就判断每个字符是否经过，因为递归是要回溯的，所以必须要做这一步。

3. 在判断的同时，我们还要定义一个 $flag$ 函数，初始化为 $1$，在判断**字符有不相符的**同时，我们还要取反 $flag$，当为 $1$ 的时候，就说明有一个不同，当**再次**为 $0$ 时，说明遇到了第二个，不符合题目要求，就直接返回 ``false``。至于怎样才能**防止在一开始向下搜索时就发现 $flag$ 为 $0$ 而退出递归呢**？很简单，将取反 $flag$ 的部分放在下面（就是在发现无法配对时的继续操作）。

4. 根据 $\operatorname{find}$ 函数的结果输出结果就可以了。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 6 * 1e5 + 10;
int son[N][3];
bool vis[N];
string s;
int len, n, m, sum;
bool find(int k, int dep, int flag)
{
    if (dep == len && flag && vis[k])
    {
        return true;
    }
    if (dep > len)
    {
        return false;
    }
    int ch = s[dep] - 'a';
    if (son[k][ch])
    {
        if (find(son[k][ch], dep + 1, flag))
        {
            return true;
        }
    }
    if (flag)
    {
        return false;
    }
    for (int i = 0; i < 3; i++)
    {
        if (ch == i)
        {
            continue;
        }
        if (son[k][i])
        {
            if (find(son[k][i], dep + 1, flag ^ 1))
            {
                return true;
            }
        }
    }
    return false;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        int now = 0;
        for (int j = 0; j < s.length(); j++)
        {
            int v = s[j] - 'a';
            if (!son[now][v])
            {
                son[now][v] = ++sum;
            }
            now = son[now][v];
        }
        vis[now] = 1;
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> s;
        len = (int)s.length();
        if (find(0, 0, 0))
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/125980204)

---

## 作者：happybob (赞：0)

考虑字典树上深搜。

由于字符集只有 $\texttt{abc}$，所以深搜是可过的。

建立完字典树后，从根开始，维护现在是否有存在一个不同的字符，如果有，那么下一个字符肯定和询问的串相同，如果没有不同，那么下一个可以选择相同也可以选择不同的。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
using namespace std;

const int N = 1e6 + 5;

string s, p;
int n, m;

class Trie
{
public:
	int son[N][4], idx, rt;
	void insert(string x)
	{
		int u = rt;
		for (auto c : x)
		{
			int p = c - 'a';
			if (!son[u][p]) son[u][p] = ++idx;
			u = son[u][p];
		}
	}
	bool dfs(int x, int u, bool g)
	{
		if (!u && x != 0) return 0;
		if (x == p.size() && g) return 1;
		if (g)
		{
			return dfs(x + 1, son[u][p[x] - 'a'], g);
		}
		else
		{
			for (int j = 0; j <= 2; j++)
			{
				if (p[x] - 'a' == j)
				{
					if (dfs(x + 1, son[u][j], 0)) return 1;
				}
				else
				{
					if (dfs(x + 1, son[u][j], 1)) return 1;
				}
			}
			return 0;
		}
	}
}t;

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> s;
		t.insert(s);
	}
	while (m--)
	{
		cin >> p;
		cout << (t.dfs(0, t.rt, 0) ? "YES" : "NO") << "\n";
	}
	return 0;
}
```


---

