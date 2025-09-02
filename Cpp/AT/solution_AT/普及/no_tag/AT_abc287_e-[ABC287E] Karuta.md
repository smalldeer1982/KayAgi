# [ABC287E] Karuta

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc287/tasks/abc287_e

英小文字からなる文字列が $ N $ 個与えられます。$ i\ \,\ (i\ =\ 1,\ 2,\ \dots,\ N) $ 番目のものを $ S_i $ と表します。

二つの文字列 $ x,\ y $ に対し、以下の条件を全て満たす最大の整数 $ n $ を $ \mathrm{LCP}(x,\ y) $ と表します。

- $ x,\ y $ の長さはいずれも $ n $ 以上
- $ 1 $ 以上 $ n $ 以下の全ての整数 $ i $ に対し、$ x $ の $ i $ 文字目と $ y $ の $ i $ 文字目が等しい
 
全ての $ i\ =\ 1,\ 2,\ \dots,\ N $ に対し、以下の値を求めてください。

- $ \displaystyle\ \max_{i\ \neq\ j}\ \mathrm{LCP}(S_i,\ S_j) $

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ N $ は整数
- $ S_i $ は英小文字からなる長さ $ 1 $ 以上の文字列 $ (i\ =\ 1,\ 2,\ \dots,\ N) $
- $ S_i $ の長さの総和は $ 5\ \times\ 10^5 $ 以下
 
### Sample Explanation 1

$ \mathrm{LCP}(S_1,\ S_2)\ =\ 2,\ \mathrm{LCP}(S_1,\ S_3)\ =\ 1,\ \mathrm{LCP}(S_2,\ S_3)\ =\ 1 $ です。

## 样例 #1

### 输入

```
3
abc
abb
aac```

### 输出

```
2
2
1```

## 样例 #2

### 输入

```
11
abracadabra
bracadabra
racadabra
acadabra
cadabra
adabra
dabra
abra
bra
ra
a```

### 输出

```
4
3
2
1
0
1
0
4
3
2
1```

# 题解

## 作者：FFTotoro (赞：7)

本题需要使用**字典树**。

先将所有的字符串存进字典树，用 $t_{p,x}$ 表示连在编号为 $p$ 的结点下方的字符 $x$（这里的 $x$ 并不是指小写字母 $\texttt{x}$，而是一个字符型变量）。每次插入只用不断往下“翻”就可以了。

然后对于每个字符串，忽略字典树里它“独有的”结点，然后看看最深可以匹配到多深——这个深度即为这个字符串的答案。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t[500001][26],w,r[500001];
void insert(string s){
  int p=0;
  for(char i:s){
    int x=i-97;
    if(!t[p][x])t[p][x]=++w;
    else r[t[p][x]]++; // 统计经过每个结点的字符串是否大于一个，如果多于一个那么 r[t[p][x]] 应该是大于 0 的
    p=t[p][x]; // 前往下一个结点，“往下翻”
  }
}
int find(string s){
  int p=0,c=0;
  for(char i:s){
    int x=i-97;
    if(r[t[p][x]])c++; // 如果不止一个，就继续搜下去
    else break; // 否则退出
    p=t[p][x];
  }
  return c;
}
main(){
  ios::sync_with_stdio(false);
  int n,m=0; cin>>n;
  vector<string> a(n);
  for(auto &i:a)cin>>i,insert(i);
  for(auto i:a)cout<<find(i)<<endl;
  return 0;
}
```

---

## 作者：_JF_ (赞：2)

## [ABC287E] Karuta 


[Link](https://www.luogu.com.cn/problem/AT_abc287_e)

字典树典题。

首先建出字典树，然后对于每一个字符串进行检索，注意前缀不能在当前的字符串中，所以我们考虑对字典树上的每一个点打标记，记录出现了多少次。当当前点出现次数大于 $1$，也就是不为其本身的的时候才能进行更新。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
string s[N];
int ch[N][40],pre,cnt[N];
int Getnum(char c){
	return c-'a'+1;
}
void Assert(string k){
	int p=0;
	for(int i=0;i<k.length();i++){
		char now=k[i];
		int S=Getnum(now);
//		cout<<S<<endl;
		if(ch[p][S]==0)	ch[p][S]=++pre;
		p=ch[p][S];
		cnt[p]++;
	}
}
int Getval(string k){
	int p=0,ans=0;
	for(int i=0;i<k.length();i++){
		char now=k[i];
		int S=Getnum(now);
		if(ch[p][S]!=0&&cnt[ch[p][S]]>1)	ans=max(ans,i+1),p=ch[p][S];	
		else return ans;
	}
	return ans;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>s[i];
	for(int i=1;i<=n;i++)	Assert(s[i]);
//	for(int i=1;i<=pre;i++)	cout<<cnt[i]<<endl;
	for(int i=1;i<=n;i++)	cout<<Getval(s[i])<<endl;
	return 0;
}

```


---

## 作者：DengDuck (赞：2)

简单题，直接字典树走起。

我们将字符串插入字典树，然后，直接查找最大前缀即可。

具体来说，当前位置的下一个位置，如果其包含的字符串数量为 $1$，那么就只有它本身了，否则，就是还有别的字符串可以跟其匹配，下一位。

时间复杂度 $O(n\log n)$。
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const LL N = 5e5 + 5;
struct node {
    LL son[26], sz;
};
vector<node> t;
LL n, cnt = 1;
string s[N];
void ins(string s) {
    LL x = 1;
    t[x].sz++;
    for (auto i : s) {
        if (t[x].son[i - 'a'] == 0)
            t[x].son[i - 'a'] = ++cnt, t.push_back({ 0, 0 });
        x = t[x].son[i - 'a'];
        t[x].sz++;
    }
}
LL find(string s) {
    LL x = 1, cnt = 0;
    for (auto i : s) {
        LL son = t[x].son[i - 'a'];
        if (t[son].sz > 1)
            x = son, cnt++;
        else
            break;
    }
    return cnt;
}
int main() {
    scanf("%lld", &n);
    t.push_back({ 0, 0 }), t.push_back({ 0, 0 });
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        ins(s[i]);
    }
    for (int i = 1; i <= n; i++) {
        printf("%lld\n", find(s[i]));
    }
}
```

---

## 作者：Fire_flame (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc287_e)

## $\mathtt{Solution}$

根据数据范围和题目，不难想到是用哈希来截取子串，定义哈希数组为 $h$，基底为 $E$。

如果我们想截取 $l,l+1\dots r$ 的字符，那么截取出来的子串的哈希值为 $h[r] - h[l - 1] \times E^{r - l + 1}$，把每个前缀统计出来后用 map 统计答案。

但是注意，每一个字符串的长度可能很长，也可能很短，故用 vector 来存哈希的值。

具体细则见代码。

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
const int MAXN = 5e5 + 5, E = 1023643;//E为基底，如果出现bug可以改成E=10
int n, k;
string s[MAXN];
vector<int> h[MAXN];
map<int, int>mp;
void calc(string ch, int x){
	h[x].push_back(0);
	int res = 0, len = ch.length();
	for(int i = 1;i <= len;i ++){
		res *= E;
		res += ch[i - 1] - 'a' + 1;//哈希数组初始化
		h[x].push_back(res);
	}
}
int fpow(int a, int b){//快速幂
	int res = 1;
	while(b){
		if(b & 1)res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}
int Hash(int x, int l, int r){
	return h[x][r] - h[x][l - 1] * fpow(E, r - l + 1);//截取子串，要用快速幂是因为需要补位
}
signed main(){
	scanf("%lld", &n);
	for(int i = 1;i <= n;i ++){
		cin>>s[i];
		calc(s[i], i);
		int len = s[i].length();
		for(int j = 1;j <= len;j ++)mp[Hash(i, 1, j)] ++;//将每一个截取好的子串放进map里面
	}
	for(int i = 1;i <= n;i ++){
		int cnt = 0, len = s[i].length();
		for(int j = 1;j <= len;j ++){
			if(mp[Hash(i, 1, j)] > 1)cnt = j;//大于1是因为自己不算
			else break;//必须连续的相等才算，所以这里break
		}
		printf("%lld\n", cnt);
	}
	return 0;
}
```

---

## 作者：Feyn (赞：1)

大体思路是对于每个串，求出每个前缀求出哈希值并存储下来，显然哈希值的数量是 $O(\sum|S_i|)$ 的，可以暴力求得并存储。

对于每个串求解答案的时候，考虑枚举前缀并查询其哈希值的出现次数，由于这个前缀在预处理的时候被加入了一次哈希表，所以如果当前哈希值出现次数多于两次的话就说明当前前缀在其它串里出现过，那么这个前缀长度就是可以去更新答案的，显然这部分复杂度也是 $O(\sum|S_i|)$ 的。

我图方便直接把所有的哈希值排序了，所以会带个 $\log$，其实是可以优化掉的。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
#define ptt pair<int,int>
#define mp make_pair
using namespace std;
const int A=1e9+7;
const int B=1e9+9;
const int P=1e7;
const int N=500010;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

mt19937 rnd(123);
int m,n,dataa[26];
string w[N];

ptt a[N];

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);int cnt=0;
	for(int i=0;i<26;i++){
		dataa[i]=rnd()%P;
		if(dataa[i]<0)dataa[i]*=-1;
	}
	for(int i=1;i<=m;i++){
		cin>>w[i];n=w[i].size();
		int aa=0,bb=0;
		for(int j=0;j<n;j++){
			aa=(aa*P+dataa[w[i][j]-'a'])%A;
			bb=(bb*P+dataa[w[i][j]-'a'])%B;
			a[++cnt]=mp(aa,bb);
		}
	}
	sort(a+1,a+cnt+1);
	for(int i=1;i<=m;i++){
		int ans=0,aa=0,bb=0;n=w[i].size();
		for(int j=0;j<n;j++){
			aa=(aa*P+dataa[w[i][j]-'a'])%A;
			bb=(bb*P+dataa[w[i][j]-'a'])%B;
			int pl=lower_bound(a+1,a+cnt+1,mp(aa,bb))-a;
			if(a[pl+1]==mp(aa,bb))ans=j+1;
		}
		printf("%lld\n",ans); 
	}
	
	return 0;
}
```

---

## 作者：ruanwentao666 (赞：0)

# [ABC287E] Karuta 题解

[题目面板（洛谷）](https://www.luogu.com.cn/problem/AT_abc287_e)

[题目面板（AtCoder）](https://atcoder.jp/contests/abc287/tasks/abc287_e)

## 暴力查找
暴力查找大家肯定都会，两层循环枚举 $s_i$ 和 $s_j$，再一层循环查找它们的最长公共前缀，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s[500005];
int Sum_Longest_Public_Prefix(string x,string y){
	int i=0;//指针
	while(i<x.size()&&i<y.size()&&x[i]==y[i])i++;
	return i;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	for(int i=1;i<=n;i++){
		int maxn=0;
		for(int j=1;j<=n;j++){
			if(i!=j){
				maxn=max(maxn,Sum_Longest_Public_Prefix(s[i],s[j]));
			}
		}
		cout<<maxn<<endl;
	}
	return 0;
}

```
这种算法的时间复杂度高达 $O(n^2 \times s)$，其中  $s$ 表示字符串的最大长度。不用想，这种算法绝对超时。

## 字典树的引入
我们常常用 Trie（也叫做前缀树）来保存字符串集合。

在程序中，我们将根节点的编号设为 0，然后把其余节点的编号设为从 $1$ 开始的正整数，然后用一个数组来保存每个节点的所有子节点，用下标直接存取。

## 正解
有了字典树，我们就可以把字符串存储到字典树中，然后查找，即可求出答案。

附上 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5*1e5+5;
int n;
int ch[maxn][26],sz=1,u,b[maxn];
string s[maxn];
int idx(char c){
	return c-'a';
}
void insert(string s){
	u=0;
	for(int i=0;i<s.size();i++){
		int j=idx(s[i]);
		if(!ch[u][j]){
			ch[u][j]=sz++;
		}else{
			b[ch[u][j]]++;
		}
		u=ch[u][j];
	}
}
int find(string s){
	u=0;
	int ans=0;
	for(int i=0;i<s.size();i++){
		int j=idx(s[i]);
		if(b[ch[u][j]]){
			ans++;
		}else{
			break;
		}
		u=ch[u][j];
	}
	return ans;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		insert(s[i]);
	}
	for(int i=1;i<=n;i++){
		cout<<find(s[i])<<"\n";
	}
	return 0;
}

```


---

## 作者：aCssen (赞：0)

### Solution
字典树模板题。

首先将 $n$ 个字符串插入字典树，再依次对每个字符串匹配。

对于字符串 $s$ 的匹配，做法显然是顺着 $s$ 中字符的顺序依次往下找，若没有子节点就返回。

但由于我们开始时已经将所有字符串都插入了字典树，其中也包括 $s$，所以一定能匹配到底。

解决办法是，对于每个字典树中的节点 $x$，维护一个值 $cnt_x$，表示经过 $x$ 的字符串数量，则原本的“非空”条件就变为了 $cnt_x$ 的值大于 $1$。

然后这题就做完了。
### 代码
字典树码风有点奇怪，勿喷。
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<vector> 
using namespace std;
const int maxn=5e5+5;
struct node
{
	int son[30];
}trie[maxn];
string s[maxn];
int cnt[maxn*30],tot,n;//cnt应该开到字典树节点总数大小
void insert(string s){
	int x=0;
	for(int i=0;i<s.size();i++){
		int y=s[i]-'a'+1;
		if(!trie[x].son[y]) trie[x].son[y]=++tot;
		x=trie[x].son[y];
		cnt[x]++;//维护cnt
	}
}
int query(string s){
	int x=0;
	for(int i=0;i<s.size();i++){
		int y=s[i]-'a'+1;
		if(cnt[trie[x].son[y]]<=1) return i;//x关于y的子节点的cnt<=1，所以只能匹配到s[i-1]，但string下标从0开始，所以答案是i-1+1=i。
		x=trie[x].son[y];
	}
	return s.size();
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		insert(s[i]);
	}
	for(int i=1;i<=n;i++)
		cout<<query(s[i])<<'\n'; 
	return 0;
}
```

---

## 作者：FReQuenter (赞：0)

要匹配多个字符串的最长公共前缀，这是字典树（trie 树）的经典应用。在本题中，只需要一次把所有字符串加入一棵字典树，随后对于每一个字符串依次检查不包含它自身的最大深度并输出即可。

字典树可以学习 [这篇博客](https://blog.csdn.net/zgdlxs/article/details/122648103)，并以本题作为模板是非常合适的。

时间和空间复杂度均为线性。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt=1,cntt[500005],c[500005][26];
string s[500005];
void insert(string s){
	int pos=1;cntt[pos]++;
	for(int i=0;i<s.length();i++){
		if(!c[pos][s[i]-'a']) pos=c[pos][s[i]-'a']=++cnt;
		else pos=c[pos][s[i]-'a'];
		cntt[pos]++;
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++) insert(s[i]);
	for(int i=1;i<=n;i++){
		int pos=1,ans=0;
		for(int j=0;j<s[i].length();j++){
			pos=c[pos][s[i][j]-'a'];
			if(cntt[pos]>=2) ans=max(ans,j+1);
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：ttq012 (赞：0)

考虑建立一棵 Trie 树。

将所有的字符串插入到这个树里。

然后在插入的时候每一个地方都记录一个 $cnt_i$ 表示有多少个字符串存在这个前缀。

询问的时候可以一直沿着这个字符串走，然后如果这个字符串走完了那么 $\text{LCP}$ 就是这个字符串的长度，如果走到一个地方的时候 $cnt_i=1$ 说明没有别的字符串有这个前缀，答案就是当前走的字符的数量 $-1$。

时间复杂度 $O(\sum |s|)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;
struct _2772eat5135_
{
  int next[26];
} z[N];
int cnt[N], c;
string s[N];

void insert(const char *s)
{
  int p = 0;
  for (int i = 0; s[i]; i ++)
  {
    int j = s[i] - 'a';
    if (!z[p].next[j])
      z[p].next[j] = ++ c;
    p = z[p].next[j];
    cnt[p] ++;
  }
}

int query(const char *s)
{
  int p = 0, ans = 0;
  for (int i = 0; s[i]; i ++)
  {
    int j = s[i] - 'a';
    p = z[p].next[j];
    if (cnt[p] == 1)
      return ans;
    ans ++;
  }
  return ans;
}

signed main()
{
  int n;
  cin >> n;
  for (int i = 1; i <= n; i ++)
  {
    cin >> s[i];
    insert(s[i].c_str());
  }
  for (int i = 1; i <= n; i ++)
    cout << query(s[i].c_str()) << '\n';
  return 0;
}

```



---

## 作者：CarroT1212 (赞：0)

### 题目大意

给定 $N$ 个仅含小写字母的字符串 $S_1,S_2,\cdots,S_N$。定义 $\operatorname{LCP}(x,y)$ 为满足以下条件的最大整数 $n$，其中 $x,y$ 都为字符串：

+ $|x|,|y| \ge n$。
+ 对于每个整数 $i\,(1 \le i \le n)$，$x_i=y_i$。

现在你需要对于每个整数 $i \,(1 \le i \le N)$，求出 $\max\limits_{i\neq j}\operatorname{LCP}(S_i,S_j)$。

数据范围：$1 \le N \le 5\times 10^5$，所有 $S_i$ 长度之和不超过 $5 \times 10^5$。

------------

### 解法分析

赛时没发现有排序解法，于是就无脑码了个哈希。

记录这 $N$ 个字符串的所有前缀子串出现的次数，为了后面处理方便可以把空串也算上。比如当 $S=\{\texttt{abc},\texttt{abb},\texttt{aac}\}$ 时，空串和 $\texttt{a}$ 出现了 $3$ 次，$\texttt{ab}$ 出现了 $2$ 次，$\texttt{aa},\texttt{abc},\texttt{abb},\texttt{aac}$ 出现了 $1$ 次。这里直接把这么多字符串存进 map 显然不现实，所以需要存哈希值，这样这一部分不考虑 map 存储的时间的话就是 $O(\sum |S_i|)$。

接下来对于每一个 $i$，令 $x=\max\limits_{i\neq j}\operatorname{LCP}(S_i,S_j)$，则 $x$ 就是满足“$S_i$ 中长度为 $y$ 的前缀子串在之前记录的字符串中总共出现了至少两次”的条件的最大 $y$，其中 $y\,(0 \le y \le |S_i|)$ 为一个整数，长度为 $0$ 的是空串。至于为什么是两次而不是一次：有一次是 $S_i$ 里的，不算。这里可以直接枚举，不过由于显然 $x$ 和对应子串出现次数满足单调性，所以 $x$ 还可以通过二分得到。用了二分之后，这整个过程依然可以通过哈希做到不考虑 map 时每次 $O(\log |S_i|)$，带上 map 加起来也不会超时。最后输出它即可。

~~关于我为什么赛时不直接枚举：复杂度算错了。~~

不过好像单模数哈希被卡了（不要问我怎么知道的），所以我码了个双底数的。事实证明绝对不要在 Atcoder 比赛中写哈希时用单模数。

------------

### 代码

二分的。

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define pii pair<int,int>
using namespace std;
const ll N=5e5+7,MOD=1e9+7;
ll n,len[N];
char inp[N];
vector <ll> v1[N],v2[N];
map <ll,map<ll,ll> > mp;
int main() {
	scanf("%lld",&n);
	mp[0][0]=n;
	for (ll i=1,h1,h2;i<=n;i++) {
		scanf("%s",inp+1),v1[i].pb(0),v2[i].pb(0),len[i]=strlen(inp+1),h1=h2=0;
		for (int j=1;j<=len[i];j++)
			h1=(h1*131+inp[j])%MOD,h2=(h2*133+inp[j])%MOD,
			v1[i].pb(h1),v2[i].pb(h2),mp[h1][h2]++;
	}
	for (ll i=1;i<=n;i++) {
		ll l=0,r=len[i],mid,ans=0;
		while (l<=r) {
			mid=l+r>>1;
			if (mp[v1[i][mid]][v2[i][mid]]>=2) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

考虑二分 LCP，显然 LCP 是有单调性的。

然后维护一下哈希，用 `multiset` 判断存在性，就可以做到两只 $\log$。

ABC 还卡了 $10^9+7$ 的单模哈希，所以赛时用了双模。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
using namespace std;

#define ll long long

const int N = 5e5 + 5, INF = 2e9, MOD = 1e9 + 7, MOD2 = 998244353;

inline int read()
{
	int op = 1, x = 0;
	char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
	while (ch == '-')
	{
		op = -op;
		ch = getchar();
	}
	while (ch >= '0' and ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * op;
}

inline void write(int x)
{
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, t, maxn = 0;
string s[N];
multiset<pair<long long, long long> > st;
vector<pair<long long, long long> > hs[N];

long long qpow(long long a, long long b)
{
	long long res = 1, base = a;
	while (b)
	{
		if (b & 1)
		{
			res = res * base;
			res %= MOD;
		}
		base *= base;
		base %= MOD;
		b >>= 1;
	}
	return res;
}

long long qpow2(long long a, long long b)
{
	long long res = 1, base = a;
	while (b)
	{
		if (b & 1)
		{
			res = res * base;
			res %= MOD2;
		}
		base *= base;
		base %= MOD2;
		b >>= 1;
	}
	return res;
}

int main()
{
	// freopen("*.in", "r", stdin);
	// freopen("*.out", "w", stdout);
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
		long long ph = 0, ph2 = 0;
		for (int j = 0; j < s[i].size(); j++)
		{
			ph += s[i][j] * qpow(26, j * 1LL) % MOD;
			ph %= MOD;
			ph2 += s[i][j] * qpow2(26, j * 1LL) % MOD2;
			ph2 %= MOD2;
			hs[i].emplace_back(make_pair(ph, ph2));
			st.insert(make_pair(ph, ph2));
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (auto j : hs[i])
		{
			st.erase(st.find(j));
		}
		maxn = 0;
		int l = 1, r = s[i].size();
		while (l <= r)
		{
			int mid = l + r >> 1;
			auto g = hs[i][mid - 1];
			if (st.find(g) != st.end())
			{
				maxn = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		for (auto j : hs[i])
		{
			st.insert(j);
		}
		cout << maxn << "\n";
	}
	return 0;
}
```


---

## 作者：CodingShark (赞：0)

本题可以作为字典树的板子练手。

在插入字符串时记录字典树上每个节点被经过的次数，查询的时候如果字符串对应路径上的点次数 $\ge 2$ 就用当前点深度更新答案。

时间复杂度 $O(\sum |S_i|)$。

评价：好写，而且快。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, pos, t[500005][26], cnt[500005];
vector<string> vec;
char str[500005];
 
void insert(string str)
{
  int p = 0;
  for (int i = 0; i < str.size(); i++)
  {
    int c = str[i] - 'a';
    if (!t[p][c])
      t[p][c] = ++pos;
    p = t[p][c];
    cnt[p]++; // 记录经过次数
  }
}
 
int find(string str)
{
  int p = 0, res = 0;
  for (int i = 0; i < str.size(); i++)
  {
    int c = str[i] - 'a';
    if (!t[p][c])
      t[p][c] = ++pos;
    p = t[p][c];
    if (cnt[p] > 1)
      res = i + 1; // 直接更新答案
  }
  return res;
}
 
int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    scanf("%s", str);
    insert(str);
    vec.push_back(str);
  }
  for (int i = 0; i < n; i++)
    printf("%d\n", find(vec[i]));
  return 0;
}
```

---

