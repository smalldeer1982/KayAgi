# [ABC097C] K-th Substring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc097/tasks/arc097_a

文字列 $ s $ が与えられます。 $ s $ の**異なる** substring のうち、辞書順で $ K $ 番目に小さいものを出力してください。

ただし、$ s $ の substring とは、 $ s $ の空でない連続した部分を取り出してできる文字列とします。 例えば、 $ s $ $ = $ `ababc` とすると、 `a`, `bab`, `ababc` は $ s $ の substring ですが、 `ac`, `z`, 空文字列 は $ s $ の substring ではありません。 また、substring が異なるとは、文字列として異なることを指します。

なお、$ X\ =\ x_{1}x_{2}...x_{n}, $ $ Y\ =\ y_{1}y_{2}...y_{m} $ を二つの異なる文字列とするとき、$ Y $ が $ X $ の接頭辞であるか、$ j $ を $ x_{j}\ \neq\ y_{j} $ であるような最小の整数として $ x_{j}\ >\ y_{j} $ である場合、そしてその場合に限って $ X $ は $ Y $ より辞書順で大きいといいます。

## 说明/提示

### 制約

- $ 1 $ $ <\ = $ $ |s| $ $ <\ = $ $ 5000 $
- $ s $ は英小文字からなる
- $ 1 $ $ <\ = $ $ K $ $ <\ = $ $ 5 $
- $ s $ は異なる substring を $ K $ 個以上持つ

### 部分点

- $ |s| $ $ <\ = $ $ 50 $ を満たすデータセットに正解した場合は、部分点として $ 200 $ 点が与えられる。

### Sample Explanation 1

$ s $ の substring は `a`, `b`, `ab`, `ba`, `aba` の $ 5 $ つです。 このうち $ 4 $ 番目に小さい `b` を出力してください。 `a` を $ 2 $ 回カウントしないことに注意してください。

## 样例 #1

### 输入

```
aba
4```

### 输出

```
b```

## 样例 #2

### 输入

```
atcoderandatcodeer
5```

### 输出

```
andat```

## 样例 #3

### 输入

```
z
1```

### 输出

```
z```

# 题解

## 作者：zzy_zzy (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc097_a)
### 要知道的
[substr](https://blog.csdn.net/azw66666/article/details/121302568) 函数求子串。

[unique](https://www.cnblogs.com/wangkundentisy/p/9033782.html) 函数去重。
### 思路
由于我们发现题目给的 $k$ 很小，所以可以直接暴力。

我们用 $a$ 数组来存 $S$ 的每一个子串。由于一个长度大于 $k$ 的字串的字典序肯定不在前 $k$ 位，所以可以直接不考虑。最后输出时需要排序和去重。

**AC code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
string a[5000010];
int main(){
	string s;
	int k,cnt=0;
	cin>>s>>k;
	int lens=s.size();
	for(int i=0;i<lens;i++){	//枚举左端点
		for(int j=1;j<=k;j++){	//枚举长度
			a[++cnt]=s.substr(i,j);
		}
	}
	sort(a,a+cnt);
	cnt=unique(a,a+cnt)-a-1;
	cout<<a[k];
	return 0;
}
```


---

## 作者：stntn (赞：3)

## SAM 求字典序第 $k$ 小子串

首先要知道 SAM 上每条从源点开始的路径都是原串的一个不同字串，所以字典序第 $k$ 小路径就是题目所求。

所以建出 SAM，求出 SAM 上每个点能到达的状态数（因为是 DAG 所以记搜一下或者建反图跑拓扑排序），SAM 最后按字典序跑第 $k$ 小路径，沿路输出就行了。

这里用的是记搜。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 10010
#define LL long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define tep(i,u) for(int i=head[u];~i;i=e[i].nxt)
#define INF 0x3f3f3f3f3f3f3f
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=a*10+ch-'0';ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline void read(T &x,Args &...args){read(x);read(args...);}
int num[N],n,k,siz[N],len;
char s[N],ans[N];
struct SAM
{
	int len[N<<1],link[N<<1],ch[N<<1][27],last,cc;
	inline void init(){len[0]=0;link[0]=-1;last=cc=0;}
	inline void insert(char x)
	{
		int cur=++cc,c=x-'a';
		len[cur]=len[last]+1;
		int p=last;num[cur]=1;
		while(p!=-1&&!ch[p][c])
		{
			ch[p][c]=cur;
			p=link[p];
		}
		if(p==-1) link[cur]=0;
		else
		{
			int q=ch[p][c];
			if(len[q]==len[p]+1) link[cur]=q;
			else
			{
				int clone=++cc;
				memcpy(ch[clone],ch[q],sizeof(ch[q]));
				len[clone]=len[p]+1;
				link[clone]=link[q];
				while(p!=-1&&ch[p][c]==q)
				{
					ch[p][c]=clone;
					p=link[p];
				}
				link[q]=link[cur]=clone;
			}
		}
		last=cur;
	}
}t;
inline int dfs(int u)
{
	if(~siz[u]) return siz[u];siz[u]=1;
	rep(i,0,25)
	{
		int v=t.ch[u][i];if(!v) continue;
		siz[u]+=dfs(v);
	}
	return siz[u];
}
inline void getans(int u)
{
	if(!k) return;
	rep(i,0,25)
	{
		int v=t.ch[u][i];if(!v) continue;
		if(siz[v]<k) k-=siz[v];
		else{printf("%c",i+'a');k--;getans(v);return;}
	}
}
signed main()
{
	memset(siz,-1,sizeof(siz));
	scanf("%s",s+1);read(k);
	n=strlen(s+1);t.init();
	rep(i,1,n) t.insert(s[i]);
	dfs(0);getans(0);
	return 0;
}
```

---

## 作者：火车司机 (赞：1)

## 简要分析

意外又发现这道题，这里再介绍一种比之前写的那篇更好写的做法

看到子串问题非常容易想到可以用 SAM 来做

于是就变成了 SAM 求本质不同第 K 小子串板子题，不会的同学这里指路 [OIwiki](https://oi-wiki.org/string/sam/#k)

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define N 10005
using namespace std;
int n, k;
char s[N];
struct SAM
{
	int n, lst, d[N];
	struct S
	{
		int len, link, nxt[26];
	} s[N];
	inline SAM()
	{
		s[0].link = -1;
	}
	inline void insert(int c)
	{
		ri t = ++n, p = lst;
		for (s[t].len = s[p].len + 1, lst = t; ~p && !s[p].nxt[c]; p = s[p].link)
			s[p].nxt[c] = t;
		if (~p)
		{
			ri q = s[p].nxt[c], x;
			if (s[q].len == s[p].len + 1)
				s[t].link = q;
			else
				for (s[x = ++n] = s[q], s[x].len = s[p].len + 1, s[t].link = s[q].link = x; ~p && s[p].nxt[c] == q; p = s[p].link)
					s[p].nxt[c] = x;
		}
		else
			s[t].link = 0;
	}
	inline void dfs(int x)
	{
		d[x] = 1;
		for (ri i = 0; i < 26; ++i)
			if (s[x].nxt[i] && !d[s[x].nxt[i]])
				dfs(s[x].nxt[i]), d[x] += d[s[x].nxt[i]];
			else if (s[x].nxt[i])
				d[x] += d[s[x].nxt[i]];
	}
	inline void query(int x, int k)
	{
		if (!k)
			return;
		for (ri i = 0; i < 26; ++i)
		{
			if (!s[x].nxt[i])
				continue;
			if (d[s[x].nxt[i]] >= k)
				return (void)(putchar(i + 'a'), query(s[x].nxt[i], k - 1));
			else
				k -= d[s[x].nxt[i]];
		}
	}
} SAM;
signed main()
{
	scanf("%s%lld", s, &k), n = strlen(s);
	for (ri i = 0; i < n; ++i)
		SAM.insert(s[i] - 'a');
	SAM.dfs(0), SAM.query(0, k);
	return 0;
}
```


---

## 作者：火车司机 (赞：1)

## 简要分析

本人太菜只会一种乱搞做法

发现 $K \in [1,5]$ 很小，于是考虑直接找出一些字典序最小的子串使它们去重后至少有 $K$ 个

要使字典序最小显然首字母需要最小，于是直接遍历整个字符串找出最小字母出现的所有位置

然后我们将所有**以最小字母开头并且长度小于等于 $K$ 的子串**全部提取出来排序去重，然后输出第 $K$ 大的

为什么是这些子串呢？

因为长度不同字典序必然不同，所以这些字串去重后也至少有 $K$ 个

但是，上面的思路并不完善，连样例 $1$ 都通不过

因为在样例 $1$ 中，以最小字母开头的子串最长长度小于 $K$

那我们可以再以次小字母为开头，重复上述过程，以此类推，直到出现过 $K$ 个不同的子串

虽然看起来很暴力，但是 $K$ 和 $|S|$ 都很小，同时复杂度也卡不满，所以可以很轻松地通过此题

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define N 250005
using namespace std;
int n, k, mn, mx, tot, cnt, a[N];
string s, str[N];
signed main()
{
	ios::sync_with_stdio(0);
	for (cin >> s >> k, n = s.length();;)
	{
		mx = 1e18, cnt = tot = 0;
		for (ri i = 0; i < n; ++i)
			if (mn < s[i] && s[i] < mx)
				mx = s[i], a[cnt = 1] = i;
			else if (s[i] == mx)
				a[++cnt] = i;
		for (ri i = 1; i <= cnt; ++i)
		{
			string t = "";
			for (ri j = 0; j < k && a[i] + j < n; ++j)
				t += s[a[i] + j], str[++tot] = t;
		}
		sort(str + 1, str + 1 + tot), tot = unique(str + 1, str + 1 + tot) - str - 1;
		if (k <= tot)
		{
			cout << str[k];
			return 0;
		}
		k -= tot, mn = mx;
	}
	return 0;
}
```


---

