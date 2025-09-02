# [ABC377G] Edit to Match

## 题目描述

给你 $N$ 个字符串 $S_1,S_2,\ldots,S_N$ 。每个字符串都由小写英文字母组成。

对于每一个 $k=1,2,\ldots,N$，解决下列问题：

一开始将一个字符串 $T$ 赋为 $S_k$。

接下来，你可以在下列操作中二选一，并可以操作无限次。但每一次操作都会花费 $1$ 的代价。

- 当 $T$ 不为空时，删除 $T$ 的最后一个字符。
- 在 $T$ 后面加上一个任意的小写字母。

求使 $T$ 要么为空，要么与 $S_1,S_2,\ldots,S_{k-1}$ 中的一个匹配所需的最小代价。

## 说明/提示

- $1\le N\le 2\times10^5$
- $\sum\limits_{i=1}^N|S_i|\le2\times10^5$

## 样例 #1

### 输入

```
3
snuke
snuki
snuuk```

### 输出

```
5
2
4```

## 样例 #2

### 输入

```
3
abc
arc
agc```

### 输出

```
3
3
3```

## 样例 #3

### 输入

```
8
at
atatat
attat
aatatatt
attattat
ttatta
tta
tt```

### 输出

```
2
4
3
8
3
6
3
1```

# 题解

## 作者：PineappleSummer (赞：7)

[[ABC377G] Edit to Match](https://www.luogu.com.cn/problem/AT_abc377_g)

赛时没打，VP 了一把，不会 E，寄完了。

将 $s_i$ 删空的代价为 $s_i$ 的长度。

如果想要将 $s_i$ 删掉末尾几个字符，再在末尾添上几个字符以达到和 $s_1\sim s_{i-1}$ 中的一个相同，那么删掉末尾几个字符时一定成为 $s_1\sim s_{i-1}$ 中的一个字符串的前缀。

设 $f_t$ 为前缀 $t$ 需要在末尾添上几个字符变成一个出现过的字符串的最小代价。对于每个字符串 $s_i$，枚举前缀，更新一下 $f_t$。

对于 $s_i$ 的每个前缀 $t$，将 $s_i$ 删为 $t$ 的代价为 $|s_i|-|t|$，然后将 $t$ 补全为 $s_1\sim s_{i-1}$ 中的一个字符串的代价为 $f_t$。答案对 $|s_i|-|t|+f_t$ 取最小值即可。

对于 $f_t$，$t$ 可以使用字符串哈希，然后用 `unordered_map` 存一下。

[参考代码](https://atcoder.jp/contests/abc377/submissions/59264211)

---

## 作者：Redamancy_Lydic (赞：5)

退役前最后一篇题解了。

题目中匹配的意思就是相等。也就是说，我们对于当前的字符串 $s_k$，操作等价于删除它的一个后缀并且补上一个新后缀。

那我们不妨枚举该字符串保留的前缀，对于每个前缀找到在只保留该前缀的情况下至少需要添加多长的后缀才能满足要求。

不难想到，我们对于当前所有的候选前缀，都求出来该前缀至少还需要添加多少个字符才能成为 $s_1\sim s_{k-1}$ 中的一个。这一点我们可以对于所有候选字符串，把他们每一个前缀都以该前缀为第一关键字，保留该前缀后所需要添加的字符为第二个关键字插到一个 `unordered_map` 容器里，对于该容器中的每一个第一个关键字，对第二关键字进行比较保留最小值。这样我们就可以快速求出每个前缀所需要添加的最少字符数，加上保留该前缀所需要删除的字符数就是该前缀的答案。最后对于每一个前缀的答案取 `min` 即可。

使用 `string` 类型作为  `unordered_map` 容器的第一关键字会超时，所以我们需要对字符串进行哈希处理，用 `unsigned long long` 类作为第一关键字，可以通过本题。

[提交记录](https://atcoder.jp/contests/abc377/submissions/59263733)

---

## 作者：No_commander (赞：5)

先建出字典树，记 $cnt_p$ 表示匹配到 $p$ 这个位置后至少需要在成功匹配多少个字符可以得到之前的任意一个串，每新来一个串匹配时，有两种方式合法：

1. 先删掉末尾的一段连续子串，再在末尾加上一个等长的字符串拼成前面出现过的字符串。
  
2. 删空。

记第一种的答案为 $ans_1$，第二种的答案为 $ans_2$。

明显 $ans_2$ 是字符串长度；设当前已经匹配了第 $i$ 位，位置为 $p$，则 $ans_1 = \min\{cnt_p - i\}$。两种情况取 $\min$ 即可。

---

## 作者：Heldivis (赞：2)

## [ABC377G] Edit to Match

用 $s[l:r]$ 表示 $s$ 中 $l\sim r$ 位置的子串。

对于一个长度为 $n$ 的字符串 $s$，考虑使它变成之前的某个字符串，一定是保留前一部分、删去后一部分、然后在最后添加若干字符成为某个已知字符串。

考虑枚举端点 $k$，令 $s[1:k]$ 保存不变，$s[k+1:n]$ 删去，然后加上若干字符。

删去的代价是 $n - k$ 好计算，考虑删除后的字符串，一定是通过添加得到的字符串的一个前缀。用 $f(x)$ 表示前缀为 $x$ 的字符串，最少添加 $f(x)$ 个字符可以变成之前的字符串。

那么每次询问的答案就是:

$$
\min\{n,\min_{k=1}^{n}\{n-k+f(s[1:k])\}\}
$$

$f(x)$ 的转移为：

$$
f[s[1:k]]\gets\min\{f[s[1:k]], n - k\}
$$

代码：

```cpp
for (scanf("%d", &n); n; --n) {
  scanf("%s", s + 1);
  int len = strlen(s + 1), res = len;
  ull hsh = 0;
  for (int i = 1; i <= len; ++i) {
    hsh = hsh * 13331 + s[i];
    if (f.count(hsh))
      res = min(res, f[hsh] + len - i), f[hsh] = min(f[hsh], len - i);
    else
      f[hsh] = len - i;
  }
  printf("%d\n", res);
}
```

---

## 作者：bryce (赞：2)

## [[ABC377G] Edit to Match](https://www.luogu.com.cn/problem/AT_abc377_g)
### 思路
考虑建一颗 trie 树，每次插入一个字符串，求其末尾到其他字符串末尾的最小长度，设 $f_i$ 表示 trie 树上第 $i$ 个节点，到其最近的字符串结尾的节点的路径长度，于是，对于每个字符，从上到下查询一遍并更新路径上的节点 $f_i=\min(f_i, f_{fa_i} + 1)$，再从下到上更新一遍 $f_i=\min(f_i, f_{son_i} + 1)$。
### 代码
```cpp
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 2e5 + 10, M = 27;
int n, tot;
char c[N];
int trie[N][M], f[N * M], res[N * M];
int insert(char c[]){
    int m = strlen(c), now = 0, p = 0, ans;
    for (int i = 0; i < m; i++){
        int &to = trie[now][c[i] - 'a'];
        if (!to) to = ++tot, f[tot] = 0x7fffffff;
        f[to] = min(f[to], f[now] + 1);
        now = to;
        res[++p] = now;
    }
    ans = f[now];
    f[now] = 0;
    for (int i = p - 1; i >= 1; i--) f[res[i]] = min(f[res[i]], f[res[i + 1]] + 1);
    return ans;
}

int main(){
    n = read();
    for (int i = 1; i <= n; i++){
        cin >> c;
        cout << insert(c) << '\n';
    }
    return 0;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：2)

比 E 还简单的 G 这辈子不多了。
## 题解
将每个数插入到类似于 ``trie`` 树的东西上，再用 $en_i$ 数组记录离这个节点最近的结尾字符，代价即为：$en_p+n-i+1$，取最小值即可。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,en[500005],tr[500005][30],idx=1;
void insert()
{
	int p=0,n=s.length(),c,ans=n;
	for(int i=0;i<n;i++)
	{
		c=s[i]-'a';
		if(tr[p][c]==0)
		{
			tr[p][c]=idx;
			idx++;
		}
		p=tr[p][c];
		ans=min(ans,en[p]+n-i-1);
		en[p]=min(en[p],n-i-1);
	}
	cout<<ans<<endl;
}
int main()
{
	memset(en,0x3f,sizeof(en));
	en[0]=0;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>s;
		insert();
	}
}
```

---

## 作者：zyn0309 (赞：1)

# [ABC377G] Edit to Match
[题目传送门](https://www.luogu.com.cn/problem/AT_abc377_g)
## 思路
对字符串 $S_i$ 的每一个前缀哈希，用 map 存包含每一个前缀的最小原串长度，然后在每一个出现过的前缀处统计答案取最小值即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,aa=5393,mod=1e9+7,mod2=1e9+9,ha[N],ha2[N];
string s;
map<pair<int,int>,int>mp;
signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;++i){
	  cin>>s;
	  int len=s.size();
	  int ans=len;
	  for(int j=0;j<len;++j){
	    ha[j+1]=(ha[j]*aa%mod+s[j])%mod;
	    ha2[j+1]=(ha2[j]*aa%mod2+s[j])%mod2;
	  }
	  for(int j=0;j<len;++j){
	  	pair<int,int>p(ha[j+1],ha2[j+1]);
	  	if(!mp[p])continue;
	  	ans=min(mp[p]-j-1+len-j-1,ans);
	  }
	  for(int j=0;j<len;++j){
	  	pair<int,int>p(ha[j+1],ha2[j+1]);
	  	if(!mp[p])mp[p]=len;
	  	else mp[p]=min(mp[p],len);
	  }
	  cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：__Floze3__ (赞：1)

## 思路

看到限制是字符串的长度和，以及只要统计一个字符串转变为它之前的字符串的最小代价，不难想到 Trie。具体的，我们在 Trie 上每个节点存储一个值 $d$，表示从当前节点走到某个字符串的结尾，最少还需要走几个节点，那么我们在插入每一个字符串之前可以先在 Trie 上查询，设当前走到的节点为 $u$，字符串剩余的长度为 $len$，那么答案即为 $\min(res_u + len)$。总的时间复杂度为 $O(\sum|S|)$。

## 代码

[提交记录](https://atcoder.jp/contests/abc377/submissions/59220452)

---

## 作者：Forg1weN (赞：0)

## [[ABC377G] Edit to Match](www.luogu.com.cn/problem/AT_abc377_g)

比较一眼的题目。

考虑限制相当于是找到已存在两个串的最大公共长度，所以使用字典树去维护，对于每个插入，预处理出一个节点的子树内最短的串是什么，对于每个询问，相当于就是询问子树内最近的一个点到当前节点的距离和询问字符串到当前节点的距离，可以类比求树上公共祖先。时间复杂度 $O(n)$。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+10;

int n,tot=1,ans;
int ch[maxn][26],dep[maxn*26];
char s[maxn];
void insert(int p,int len) {
	for(int i=1;i<=len;i++) {
		int t=s[i]-'a';
		if(!ch[p][t])ch[p][t]=++tot;
		p=ch[p][t];
		if(!dep[p])dep[p]=len;
		else dep[p]=min(dep[p],len);
	}
}
void query(int p,int len) {
	for(int i=1;i<=len;i++) {
		int t=s[i]-'a';
		if(!ch[p][t])return;
		p=ch[p][t];
		ans=min(ans,len-i+dep[p]-i);
	}
}
int main() {
 	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%s",s+1);
		int len=strlen(s+1);
		ans=len;
		query(1,len);
		printf("%d\n",ans);
		insert(1,len);
	}
	return 0; 
}
```

---

## 作者：whrwlx (赞：0)

~~水。~~

发现成本最小一定是先删一段后缀然后再加一段后缀。

那么很容易想到一个 DP：

设 $f_s$ 表示前缀为 $s$，需要添加一段后缀变成一个出现过的字符串的最小成本。

那么答案就是：

$$
\min_{s \subseteq S_i}\{ f_s+|S_i| - |s|\}
$$

另外，我们在计算答案时可以直接对 $f_s$ 进行更新：

$$
f_s=\min \{ f_s,|S_i| - |s| \}
$$

对于 $s \subseteq S_i$，我们对 $s$ 哈希即可。

**注意**：不能在计算答案之前更新 $f_s$，否则会输出 $0$（即每个字符串自己匹配自己）。

[提交记录](https://atcoder.jp/contests/abc377/submissions/59209071)

---

## 作者：ran_qwq (赞：0)

简单题。

题意可以转化成动态维护[字典树](https://www.luogu.com.cn/problem/P8306)，求字典树上一点到以前某个叶子节点或根的距离最小值。

维护字典树每个节点的子树内最近叶子距离 $md_u$（若没有为无穷大）。枚举两点的 LCA $p$，这部分的答案为 $\operatorname{dis}(u,p)+md_p$。取最小值即可。

```cpp
int n;
struct TRIE {
	int idx,md[N],tr[N][M];
	void init() {mst(md,0x3f),md[0]=0;}
	int qry(string s) {
		int rs=INF,l=s.size(); s+=" ";
		for(int i=0,p=0,c;i<s.size();i++) {
			cmin(rs,l-i+md[p]),cmin(md[p],l-i); if(s[i]==' ') break;
			!tr[p][c=s[i]-'a']&&(tr[p][c]=++idx),p=tr[p][c];
		}
		return rs;
	}
} tr;
void QwQ() {
	n=rd(),tr.init();
	for(int i=1;i<=n;i++) {string s; cin>>s,wr(tr.qry(s),"\n");}
}
```

---

## 作者：CJ_Fu (赞：0)

## [ABC377G Edit to Match](https://atcoder.jp/contests/abc377/tasks/abc377_g)

给你 $n$ 个字符串，记 $s_0$ 为空，对于每个字符串 $i\in[1,n]$，求通过删除/添加后缀字母的操作，最少需要操作多少次使得 $s_i=s_k,k\in[0,i-1]$。

$\sum |s_i|\le 2\times 10^5$

考虑建 trie 树的过程，实质是每次新建一条链。而我们要求的就是当前字符串 $s_i$ 末节点到 $s_k(k\in[0,i-1])$ 末节点的最短距离。于是对于 trie 树上的每个节点记一个 $f_u$ 表示距离前面的字符串末节点的最短距离，则每次加入字符串 $s_i$ 时就更新链上每个节点的 $f_u=\min(f_u,f_{fa_u}+1)$。答案即为 $s_i$ 末节点的 $f_{e_i}$。然后把字符串 $s_i$ 的末节点计入，即 $f_{e_i}=0$，自下而上再更新 $f_{fa_u}=\min(f_{fa_u},f_u+1)$。时间复杂度 $O(\sum |s_i|)$，空间复杂度 $O(|\Sigma|\sum |s_i|)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+7;
char s[maxn];
int n,trie[maxn][26],val[maxn],id[maxn],node,fa[maxn*26];
int ins(){
    int lens=strlen(s);
    int u=0,res=0;
    for(int i=0;i<lens;i++){
        if(trie[u][s[i]-'a']==-1)
            trie[u][s[i]-'a']=++node;
        fa[trie[u][s[i]-'a']]=u,u=trie[u][s[i]-'a'];
        val[u]=min(val[u],val[fa[u]]+1);
    }
    res=val[u];
    val[u]=0;
    for(;fa[u];u=fa[u])
        val[fa[u]]=min(val[fa[u]],val[u]+1);
    return res;
}
signed main(){
    cin>>n;
    memset(val,0x3f,sizeof val);
    memset(trie,-1,sizeof trie);
    val[0]=0;
    for(int i=1;i<=n;i++){
        cin>>s;
        cout<<ins()<<'\n';
    }
    return 0;
}
```

---

