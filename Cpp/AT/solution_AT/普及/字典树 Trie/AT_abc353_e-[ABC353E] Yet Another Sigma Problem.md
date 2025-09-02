# [ABC353E] Yet Another Sigma Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc353/tasks/abc353_e

文字列 $ x,y $ に対して $ f(x,y) $ を以下で定義します。

- $ x,y $ の最長共通接頭辞の長さを $ f(x,y) $ とする。
 
英小文字からなる $ N $ 個の文字列 $ (S_1,\ldots,S_N) $ が与えられます。次の式の値を求めてください。

$ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ f(S_i,S_j) $

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 3\times\ 10^5 $
- $ S_i $ は英小文字からなる文字列
- $ 1\leq\ |S_i| $
- $ |S_1|+|S_2|+\ldots+|S_N|\leq\ 3\times\ 10^5 $
- 入力される数値は全て整数
 
### Sample Explanation 1

\- $ f(S_1,S_2)=2 $ - $ f(S_1,S_3)=1 $ - $ f(S_2,S_3)=1 $ なので、答えは $ f(S_1,S_2)+f(S_1,S_3)+f(S_2,S_3)\ =\ 4 $ です。

## 样例 #1

### 输入

```
3
ab abc arc```

### 输出

```
4```

## 样例 #2

### 输入

```
11
ab bb aaa bba baba babb aaaba aabbb a a b```

### 输出

```
32```

# 题解

## 作者：YFF1 (赞：4)

## 前言：
本代码不使用任何哈希表或字典树，可供刚学习字符串的萌新使用。
## 思路（极为奇葩）：
注意到，将字符串排序后，每个字符串对答案的贡献就是它与上一个字符串最长连续前缀的长度，因此可以将每个字符串的最长公共连续前缀拆分成一个个字符，然后统计并累加。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
string s[300005];
char c[300005];
long long n,mp[300005][30],sum,ans;
int main () {
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i];
	sort(s+1,s+1+n);
	for(int i=1;i<=n;i++){
		for(int j=0;j<s[i].size();j++){
			int pos=int(s[i][j]-96);
			if((i==1||j+1<=s[i-1].size())&&s[i-1][j]==s[i][j])mp[j][pos]++;//用于判断该字符与上一个字符串上该位置的字符是否相同 
			else{ //若有不同，说明这个字符串与上一个字符串的最大公共前缀到此为止了 
				for(int k=j;k<s[i].size();k++){
					if(c[k]>='a'&&c[k]<='z'){
						int pos2=int(c[k])-96;
						ans+=mp[k][pos2]*(mp[k][pos2]-1)/2;
						mp[k][pos2]=0;//将这之后所有的累计数组归零，因为要求的是前缀连续相同的长度
					}
					c[k]=s[i][k];
					mp[k][int(s[i][k])-96]=1;
				}
				break;
			}
		}
	}
	for(int i=0;i<=300000;i++){
		if(c[i]>='a'&&c[i]<='z'){
			int pos3=int(c[i])-96;
			ans+=mp[i][pos3]*(mp[i][pos3]-1)/2;//最后还要再补一次计算 
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：maokaiyu (赞：4)

~~竟然没人抢题解~~  
[题目传送门](https://www.luogu.com.cn/problem/AT_abc353_e)
## 思路
一道很典的字典树题目。在加入字符串的过程中，如果当前字符存在的话，答案就加上它的存在次数，然后将次数加一。
## 做法
维护一个字典树，按照上文进行操作，注释有详细说明。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef int I;
const I maxn = 300010;
const I charsize = 30;
I n,cnt;
LL a,l,ans;
struct TreeNode{//字典树的节点 
	I nxt[charsize];
	LL times;
	bool isend = false;//是否是一个字符串的结束，这题用不到 
}tree[maxn + 1];
void insert(char s[],I len){
	I now = 0;
	for(I i = 1;i <= len;i++){//按照字符串加入到树中 
		I x = s[i] - 'a';
		if(!tree[now].nxt[x]){//无法往下了 
			++cnt;//加入新节点 
			tree[now].nxt[x] = cnt;//存好儿子 
		}else{
			ans += tree[tree[now].nxt[x]].times;//对答案的贡献是当前字符的访问数 
			//printf("%lld %d %d\n",tree[tree[now].nxt[x]].times,i,x);/*调试代码*/
		}
		tree[tree[now].nxt[x]].times++;//增加访问数 
		now = tree[now].nxt[x];
	}
	tree[now].isend = 1;
}
I main(){
	scanf("%d",&n);
	for(I i = 1;i <= n;i++){
		char s[300010];
		scanf("%s",s + 1);
		insert(s,(I)strlen(s + 1));//插入字符，并更新答案 
		//printf("%lld %lld\n",a,l);/*调试代码*/
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：2huk (赞：3)

## E - Yet Another Sigma Problem

> - 给定 $n$ 个字符串 $s_i$，求 $\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n \operatorname{lcp}(a_i, a_j)$。
>
> - $n \le 3 \times 10^5$，$\sum |s_i| \le 3 \times 10^5$。

一种神奇的方式。

我们考虑计算 $f(k)$ 表示有多少对字符串的 $\operatorname{lcp}$ 为 $k$，那么答案即 $\sum f(k) \times k$。

发现 $f(k)$ 是没法直接求的，考虑设计 $g(k)$ 表示有多少对字符串的 $\operatorname{lcp}$ 不小于 $k$，那么有 $f(k) = g(k) - g(k + 1)$。

接下来我们的任务是求解所有的 $g(k)$。

又观察发现只要满足 $s_i$ 和 $s_j$ 的前 $k$ 个字符完全相同，不考虑后面的字符，那么 $(i, j)$ 一定会被贡献到 $g(k)$ 的计算中。所以第一步是预处理每个字符串的前缀哈希值。在哈希值上处理显然要比在字符串上处理方便得多。

进一步地，我们首先找出所有长度 $\ge k$ 的字符串，并将它们的前 $k$ 个字符的哈希值存入 map。此时我们需要将所有的前 $k$ 个字符的哈希值相同的字符串配对，那么方案数即每个哈希值的出现次数中选 $2$ 的组合方案数。这是极易求解的。

~~太晦涩了，胡个代码：~~

```cpp
int g[N];

for (int k = 1; k <= mx_len; ++ k ) {
	// 求解 g[k]
	map<int, int> mp;
	for (int i = 1; i <= n; ++ i )
		if (s[i].size() >= k)
			++ mp[hash_value[i][k]];
	
	for (auto t : mp) g[k] += t.second * (t.second - 1) / 2;
}

for (int i = 1; i <= mx_len; ++ i ) {
	res += i * (g[i] - g[i + 1]);
}
```

此时的复杂度是 $\Theta (nm)$ 的，其中 $m$ 表示最长的字符串的长度。显然无法通过。

考虑复杂度的瓶颈在于内层循环 $i$ 时会经常访问到长度 $< k$ 的字符串，若我们可以规避这些无效枚举，复杂度就会被降为 $\Theta(\sum |s_i|)$。原因显然。

随着 $k$ 的增大，长度 $\ge k$ 的字符串数量一定不降。这启发我们可以用某种支持插入、删除、遍历的数据结构，维护当前哪些字符串的长度仍 $\ge k$，并在每次循环结束时将字符串长度等于 $k$ 的删掉。set 是最合适的。

```cpp
int g[N];
set<int> S;

for (int i = 1; i <= n; ++ i ) S.insert(i);

for (int k = 1; k <= mx_len; ++ k ) {
	// 求解 g[k]
	map<int, int> mp;
	for (int i : S)
		++ mp[hash_value[i][k]];
	
	for (auto t : mp) g[k] += t.second * (t.second - 1) / 2;
	
	vector<int> era;
	for (int i : S)
		if (s[i].size() == k) era.push_back(i);
	
	for (int i : era) S.erase(i);
}

for (int i = 1; i <= mx_len; ++ i ) {
	res += i * (g[i] - g[i + 1]);
}
```

---

## 作者：linjunye (赞：3)

### 视频讲解：
![](bilibili:BV1zS411F7Po?page=4&t=840)
### 代码：
~~一个不正常的字典树……~~
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e6+10;
int tree[N][30],pre[N],ans; 
int n,len,cnt,p;
string s;
void insert_and_cal(int dep,int w,int root){//用dfs实现字典树与计算 
	if(w==len)return;//w表示已经遍历完了w位，那么遍历好了len位，就return 
	int x=s[w+1]-'a';
	if(!tree[root][x])
		tree[root][x]=++cnt;//字典树常规操作 
	insert_and_cal(dep+1,w+1,tree[root][x]);//向下搜 
	root=tree[root][x];
	dep++;
	ans+=dep*(pre[root]-p);//下一个更新上一个（视频中有讲） 
	p=pre[root];//往上回溯，所以现在的这个点=上一个点的下一个点 
	pre[root]++;//计数（视频中有讲） 
	return;
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		p=0;
		cin>>s;
		s=" "+s;//我喜欢下标从1开始 
		len=s.size()-1;
		insert_and_cal(0,0,0);//树的深度、位置、根节点编号 
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：2)

首先需要理解一个概念：两个字符串的最长公共前缀长度其实等于这两个字符串的公共前缀数量。

这很好理解：对于这两个字符串的最长公共前缀，以该前缀的开头到每一个位置结尾的区间都是这两个字符串的公共前缀。显然那个最长前缀有几位，就有多少个公共前缀。

懂了这个转换，这道题就比较好做了。我们可以枚举并从头到尾遍历每个字符串，对于一个字符串的每一个前缀，它在前面所有字符串的前缀中共出现了几次，就将答案加上几。计算完一个前缀的答案后要把该前缀的出现次数加一。

另外此题如果直接按上述方法用字符串模拟的话会 TLE 和 MLE，所以需要对字符串进行 hash 处理。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M1=998244353,M2=1e9+7;
int n;
long long sum;
string s;
map<pair<int,int>,int> ma;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		long long c1=0,c2=0;
		for(int j=0;j<s.size();j++){
			c1=(c1*233+s[j])%M1;
			c2=(c2*233+s[j])%M2;//这里是一边动态hash s的前缀一边计算答案和存储
			sum+=ma[{c1,c2}],ma[{c1,c2}]++;
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：littlebug (赞：1)

## Solution

看到字符串最大前缀，立马想到用字典树，于是问题就转化为如何在字典树上统计所有 $s_i$ 和 $s_j$ 的最长前缀了。

考虑树形 dp。

对于字典树上的每个节点 $u$，考虑计算 $u$ 对答案产生的贡献。我们可以发现，如果在以 $u$ 为根的子树中有两个节点有**标记**（即在字典树中标记为一个字符串），那么 $u$ 一定是这两个节点的前缀字符之一，所以会对答案产生 $1$ 的贡献。再次扩展，如果以 $u$ 为根的子树中有 $k$ 个节点有标记，那么两两配对，总共会产生 $\displaystyle \frac{k \times (k-1)}{2}$ 的贡献。于是，我们可以通过树形 dp 求出以 $u$ 为根的子树中的标记个数（**包括**节点 $u$），再分别求其对答案的贡献并求和，即为答案。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#define il inline
#define ll long long
using namespace std;
const int MAXN=3e5+5;
struct node
{
	int hv=0;
	int son[26]={};
};
const node emp;
int n;
vector <node> tr;
int cnt=0;
vector <ll> sum;
il int query(string s)
{
	int sz=s.size();
	int now=0;
	for(int i=0;i<sz;++i)
	{
		if(!tr[now].son[s[i]-'a'])
			return 0;
		now=tr[now].son[s[i]-'a'];
	}
	if(tr[now].hv)
		return now;
	return 0;
}
il void insert(string s)
{
	int sz=s.size();
	int _q=query(s);
	if(_q)
	{
		++tr[_q].hv;
		return;
	}
	int now=0;
	for(int i=0;i<sz;++i)
	{
		if(!tr[now].son[s[i]-'a'])
		{
			tr[now].son[s[i]-'a']=++cnt;
			tr.push_back(emp);
		}
		now=tr[now].son[s[i]-'a'];
	}
	tr[now].hv=1;
	return;
}
il ll dfs(int u)
{
	sum.emplace_back(1ll*tr[u].hv);
	int id=sum.size()-1;
	ll now;
	for(int i=0;i<26;++i)
	{
		if(tr[u].son[i])
		{
			now=dfs(tr[u].son[i]);
			sum[id]+=now;
		}
	}
	return sum[id];
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	tr.push_back(emp);
	string s;
	for(int i=1;i<=n;++i)
	{
		cin>>s;
		insert(s);
	}
	dfs(0);
	ll ans=0;
	for(int i=1;i<sum.size();++i)
		ans+=max(0ll,sum[i]*(sum[i]-1)/2);
	cout<<ans;
	return 0;
}
```

---

## 作者：haokee (赞：1)

看到字符串的前缀累加和，果断写字典树。字典树，就是第 $i$ 层结点代表第 $i$ 个字符，而每个结点的父亲就是上一个字符，儿子就是下一个父亲的所有可能。

拿样例来举例。首先，我们的第一个字符有多种不同的可能，我们当然不能开 $26$ 棵字典树，而是拿额外一个没有用的结点来充当树根。注意我们的字典树需要记录每个点的点权，用来统计答案。然后我们加入 $\texttt{ab}$，那么首先第一个字符 $\texttt{a}$ 不存在，那么我们就额外新建一个结点；第二个字符 $b$ 也不存在，就再新建一个结点。将路上的每一个结点权值都加 $1$。

然后是第二个字符串 $\texttt{abc}$，由于 $\texttt{ab}$ 已经是第一个串的前缀，那么答案就需要加 $2$。最后一个字符 $\texttt{c}$ 在 $\texttt{ab}$ 的后面不存在，那么我们就新建一个结点。将路上的每一个结点权值都加 $1$。

最后是 $\texttt{arc}$。$\texttt{a}$ 这个前缀在之前出现了 $2$ 次，那么答案就需要加 $2$。然后 $\texttt{r}$ 和 $\texttt{c}$ 都不存在，那么就需要新建结点。将路上的每一个结点权值都加 $1$。

答案：$2+2=4$。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const LL kMaxN = 3e5 + 5;

LL tr[kMaxN], nxt[kMaxN][26], n, cnt = 1, ans;  // cnt 初始化为 1，因为需要一个额外的根
string s;

void add(const string &s) {                     // 加入字符串 s
  LL p = 1;
  for (char c : s) {                            // 遍历每一个字符
    if (!nxt[p][c - 'a']) {                     // 如果不存在
      p = nxt[p][c - 'a'] = ++cnt;              // 新申请一个儿子
    } else {                                    // 已经存在
      p = nxt[p][c - 'a'];                      // 直接跳过去
    }
    ans += tr[p];                               // 累加答案
    tr[p]++;                                    // 路径上的数加一
  }
}

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> s;
    add(s);
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：WorldMachine (赞：1)

## ABC353E 题解

~~边听六兆年边打 ABC~~

### 题目大意

有 $n$ 个字符串 $S_i$，定义 $f(s,t)$ 为 $s$ 与 $t$ 的最长公共前缀长度，求：
$$
\sum_{i=1}^{n-1}\sum_{j=i+1}^nf(S_i,S_j)
$$

### Solution

计算每个字符串对所有其它字符串的贡献，答案最后除以 $2$ 即可。

用所有字符串建立一棵 Trie，记录每个结点的出现次数 $\text{cnt}$。

Trie 建好之后，对每个字符串 $S_i$，在 Trie 上遍历，将经过的所有结点的 $\text{cnt}$ 累加，再减去 $S_i$ 的长度（$S_i$ 也在 Trie 当中），就是 $S_i$ 对答案的贡献。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 300005;
int n, tot, ch[N][26], cnt[N];
string s[N];
ll ans;
void insert(string &s) {
	int len = s.length(), p = 0;
	for (int i = 0; i < len; i++) {
		if (!ch[p][s[i] - 'a']) ch[p][s[i] - 'a'] = ++tot;
		p = ch[p][s[i] - 'a'];
		cnt[p]++;
	}
}
ll query(string &s) {
	int len = s.length(), p = 0;
	ll sum = 0;
	for (int i = 0; i < len; i++) {
		sum += cnt[p];
		if (!ch[p][s[i] - 'a']) return sum;
		p = ch[p][s[i] - 'a'];
	}
	sum += cnt[p];
	return sum;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> s[i], insert(s[i]);
	for (int i = 1; i <= n; i++) ans += query(s[i]) - s[i].length();
	printf("%lld", ans / 2);
}
```

---

## 作者：g1ove (赞：1)

看到题目让我们求任意两个串的 $\text{lcp}$，一眼顶针，不难想到使用 SA 求解。

直接使用 SA 题通用套路，把所有长串加上分隔符求解 `height` 数组，然后搞个 RMQ 用于快速求解任意两个串之间的 $\text{lcp}$。

然后我们把原串对应的位置的排名拿出来，相邻两个排名我们求解它们的 $\text{lcp}$ 并且放入到一个数组里。这样会形成一个长度为 $n-1$ 的数组。

然后的话你可以右转 [P4248 [AHOI2013] 差异](https://www.luogu.com.cn/problem/P4248) 了。这样就变成求数组中所有区间的最小值的和。单调栈即可解决。

计 $|S|=\sum\limits_{i=1}^n|S_i|$，则时间、空间复杂度均为 $O(|S|\log |S|)$。

```cpp
#include<bits/stdc++.h>
#define N 600005
#define ll long long
using namespace std;
int n,m=130;
int s[N];
char t[N];
int rk[N*2],sa[N],lsa[N],lrk[N*2],cnt[N];
void Qsort(int k)
{
	int p=0;
	for(int i=n-k+1;i<=n;i++) lsa[++p]=i;
	for(int i=1;i<=n;i++) if(sa[i]>k) lsa[++p]=sa[i]-k;  
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++) cnt[rk[i]]++;
	for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--) sa[cnt[rk[lsa[i]]]--]=lsa[i]; 
}
void getsa()
{
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++) rk[i]=s[i];
	for(int i=1;i<=n;i++) cnt[rk[i]]++;
	for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		Qsort(k);
		int p=0;
		memcpy(lrk,rk,sizeof rk);
		for(int i=1;i<=n;i++)
			if(lrk[sa[i]]==lrk[sa[i-1]]&&lrk[sa[i]+k]==lrk[sa[i-1]+k])
				rk[sa[i]]=p;
			else rk[sa[i]]=++p;
		m=p;
	}
}
int g;
int pos[N];
int hei[N];
int lg[N],f[N][20];
void gethei()
{
	int p=0;
	for(int i=1;i<=n;i++)
	{
		if(p) --p;
		while(s[i+p]==s[sa[rk[i]-1]+p]) ++p;
		hei[rk[i]]=p;
	}
	lg[0]=-1;
	for(int i=1;i<=n;i++) lg[i]=lg[i>>1]+1,f[i][0]=hei[i];
	for(int i=n;i>=1;i--)
		for(int j=1;j<=lg[n-i+1];j++)
			f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
}
int ask(int l,int r)
{
	++l;
	int len=lg[r-l+1];
	return min(f[l][len],f[r-(1<<len)+1][len]);
}
int a[N];
int d[N];
int l[N],r[N];
int stk[N],top;
ll ans;
int main()
{
	scanf("%d",&g);
	for(int i=1;i<=g;i++)
	{
		scanf("%s",t+1);
		pos[i]=n+1;
		int len=strlen(t+1);
		for(int j=1;j<=len;j++)
			s[++n]=t[j];
		s[++n]=++m;
	}
	getsa();
	gethei();
	for(int i=1;i<=g;i++) a[i]=rk[pos[i]];
	sort(a+1,a+1+g);
	for(int i=1;i<g;i++)
		d[i]=ask(a[i],a[i+1]);
	--g;
	for(int i=1;i<=g;i++)
	{
		r[i]=g+1;
		while(top&&d[i]<d[stk[top]]) r[stk[top--]]=i;
		stk[++top]=i;
	}
	top=0;
	for(int i=g;i>=1;i--)
	{
		l[i]=0;
		while(top&&d[i]<=d[stk[top]]) l[stk[top--]]=i;	
		stk[++top]=i;
	}
	for(int i=1;i<=g;i++)
		ans+=1ll*d[i]*(i-l[i])*(r[i]-i);
	printf("%lld",ans);
	return 0;
}
```
[Submission.](https://atcoder.jp/contests/abc353/submissions/53351648)

+ 后记

这问题都写 SA 了，我脑袋可能废了。

---

## 作者：xiaofu15191 (赞：0)

首先对 $(S_1, \ldots, S_N)$ 排序。

对于一个字符串 $S_i$，考虑从 $1$ 至 $len_{S_i}$ 枚举 $j$。在 $i+1$ 至 $lastpos$ 中二分，其中 $lastpos$ 的含义稍后再讲。

二分找到第 $j$ 个字符相同且**最靠后**的 $S_k$，随后将 $k$ 赋给 $lastpos$。

现在 $lastpos$ 的含义就很明朗了：因为只有前 $j-1$ 个字符相同作为公共前缀，第 $j$ 个字符才可能继续更新公共前缀的长度。所以我们将上一次的 $k$ 记录下来，缩小下一次的二分范围。

对于每一个 $j$，记录下对应的 $k$ 加入 $pos$ 数组中。注意最后要在 $pos$ 数组中加入 $i$。那么对于一个 $S_i$ ，我们就能计算其对答案的贡献 $W_i$：

$$
W_i=\sum_{j=1}^{len_{pos}-1}{(pos_j-pos_{j+1})\times(j+1)}.
$$

最后将 $W_i$ 相加即可。

```cpp
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
int n;
string s[300010];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	sort(s+1,s+n+1);
	long long ans=0;
	for(int i=1;i<n;i++)
	{
		int lastpos=n;
		vector<int>pos;
		for(int j=0;j<s[i].size();j++)
		{
			int l=i+1,r=lastpos;
			lastpos=0;
			while(l<=r)
			{
				int mid=(l+r)>>1;
				if(s[mid][j]<=s[i][j])
				{
					l=mid+1;
					if(s[mid][j]==s[i][j]) lastpos=max(lastpos,mid);
				}
				else r=mid-1;
			}
			if(lastpos==0) break;
			pos.push_back(lastpos);
		}
		pos.push_back(i);
		for(int j=0;j<pos.size()-1;j++) ans+=(pos[j]-pos[j+1])*(j+1);
	}
	printf("%lld\n",ans);
}
```

---

## 作者：zzhbpyy (赞：0)

## 思路

这是一道 trie 树板子题。将所有字符串插入 trie 树，并统计每个节点出现字符的次数。对节点编号 $i$，记这一出现次数为 $si_i$，记节点个数为 $cnt$。由于最后答案统计每两个字串的前缀长度，不难得出答案为 $\sum\limits_{i=1}^{cnt}si_i$。

## 完整代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,ct=1,tr[300005][30],dep[300005],si[300005];
string a[300005];
void insert(string a){
	int p=1;
	for(int i=0;i<a.length();i++){
		if(tr[p][a[i]-'a'])dep[tr[p][a[i]-'a']]=dep[p]+1;
		else tr[p][a[i]-'a']=++ct,dep[ct]=dep[p]+1;
		p=tr[p][a[i]-'a'];
		si[p]++;
	}
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],insert(a[i]);
	for(int i=1;i<=300000;i++)if(si[i])ans+=(si[i]-1)*si[i];
	cout<<ans/2<<'\n';
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

求任意两个字符串的最长前缀的长度的和，Trie 树启动！

对于每一个 $i$，考虑将 $1\sim i-1$ 全部插入到 Trie 中，然后对于 $s_i$ 在 Trie 上走一遍：若上一个节点为 $p$，下一个节点为 $q$，当前的长度为 $i$，则产生了 $(c_p-c_q)\times (i-1)$ 的贡献，其中 $c_i$ 表示当前有多少个字符串经过了这个节点。

时间复杂度为 $O(\sum |s|)$。

```cpp
const int N=500100;
string a[N];
namespace Trie{
    struct Node{
        int nxt[26],cnt;
        Node(){memset(nxt,0,sizeof nxt),cnt=0;}
    }z[N];int idx=0;
    void ins(string s){
        int rt=0;z[rt].cnt++;
        for(auto&i:s){
            if(!z[rt].nxt[i-'a'])z[rt].nxt[i-'a']=++idx;
            rt=z[rt].nxt[i-'a'],z[rt].cnt++;
        }
    }
    int query(string s){
        int cnt=0,rt=0,idx=0,pre;
        for(auto&i:s){
            pre=rt;
            if(z[rt].nxt[i-'a'])rt=z[rt].nxt[i-'a'];
            else{cnt+=z[rt].cnt*idx;rt=N-1;break;}
            cnt+=idx*(z[pre].cnt-z[rt].cnt);
            idx++;
            // cout<<idx<<": "<<i<<' '<<z[pre].cnt<<' '<<z[rt].cnt<<'\n';
        }
        return cnt+idx*z[rt].cnt;
    }
}
using namespace Trie;
auto main()[[O3]]->signed{
    PRESOLVE 
    int n;cin>>n;F(i,1,n)cin>>a[i];int s=0;
    F(i,1,n){
        s+=query(a[i]);
        // cout<<"i="<<i<<" and query:"<<query(a[i])<<'\n';
        ins(a[i]);
    }
    cout<<s<<'\n';
}
```

---

## 作者：Autumn_Rain (赞：0)

### 题目描述

为字符串 $x,y$ 定义 $f(x,y)$。$x,y$ 的最长公共前缀长度为 $f(x,y)$。
 
给定 $N$ 个字符串 $(S_1,\ldots,S_N)$，每个字符串由字母小写组成。请计算以下表达式的值。

$$ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ f(S_i,S_j) $$

### 思路

- 考虑使用字典树，最大公共前缀其实就是两个单词结尾那两个节点的最大公共祖先。

- 插入一个单词时用一个数组从开始一直往下记录，经过的每个节点都加一下这个单词，代表这个单词到过这里。这里不要忘了单词的结尾处的节点也要加一。

- 最后遍历每个节点，计算每个节点位于多少个最大公共前缀里面，全部加起来就是最大公共前缀总长（类似握手问题）。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
#define ll long long
int n,tot;
char s[N];
int trie[N][50];
ll ans,word[N];
void insert(char c[]){
	int u=0;
	int len=strlen(c);
	for(int i=0;i<len;i++){
		word[u]++;
		int a=c[i]-'a';
		if(trie[u][a]==0){
			trie[u][a]=++tot;
		}
		u=trie[u][a];
	}
	word[u]++;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		insert(s);
	}
	for(int i=1;i<=tot;i++){
		ans+=word[i]*(word[i]-1)/2;
	}
	cout<<ans;
	return 0;
}


```

---

## 作者：卡卡卡卡卡卡 (赞：0)

## 题解
将字符串插入进字典树，$cnt_i$ 数组记录每个节点 $i$ 被查询到的次数。

发现针对每个位置上点 $i$ 的贡献即为 $cnt_i \times (cnt_i-1)/2$。

在每次查找时加上 $cnt_i$ 的值就行了。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,q,n,t[5000005][30],cnt[5000005],idx,ans;
char s[5000005];
void insert(char str[])
{
    long long p=0,len=strlen(str);
    for(long long i=0;i<len;i++)
	{
        long long c=int (str[i]-'A');
        if(!t[p][c])t[p][c]=++idx;
        p=t[p][c];
		ans+=cnt[p];
        cnt[p]++;
    }
}
int main()
{
    cin>>n>>q;
    for(long long i=1;i<=n;i++)
	{
        scanf("%s",s);
        insert(s);
    }
    cout<<ans;
}
```

---

## 作者：_Weslie_ (赞：0)

字典树模板题。

## Code

先贴上[字典树板子](https://www.luogu.com.cn/problem/P8306)的代码。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,q,tree[3000010][71],cnt[3000010],c;
char s[3000010];
int num(char x){
	if(x>='A'&&x<='Z')return x-'A';
	if(x>='a'&&x<='z')return x-'a'+26;
	if(x>='0'&&x<='9')return x-'0'+52;
}
void insert(char str[]){
	int now=0,len=strlen(str);
	for(int i=0;i<len;i++){
		int numer=num(str[i]);
		if(!tree[now][numer])tree[now][numer]=++c;
		now=tree[now][numer];
		cnt[now]++;
	}
}
int finding(char str[]){
	int now=0,len=strlen(str);
	for(int i=0;i<len;i++){
		int numer=num(str[i]);
		if(!tree[now][numer])return 0;
		now=tree[now][numer];
	}
	return cnt[now];
}
int main(){
	cin>>t;
	while(t--){
		for(int i=0;i<=c;i++){
			for(int j=0;j<=70;j++){
				tree[i][j]=0;
			}
		}
		for(int i=0;i<=c;i++)cnt[i]=0;
		c=0;
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>s;
			insert(s);
		}
		for(int i=1;i<=q;i++){
			cin>>s;
			cout<<finding(s)<<endl;
		}
	}
	return 0;
}
```

不难发现，我们为了找出有多少个 $s$ 前缀包含 $t$，使用了 $cnt$ 数组。

本题其实也差不多。

先附上代码。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,q,tree[3000010][71],cnt[3000010],c;
char s[3000010];
int num(char x) {
	if(x>='A'&&x<='Z')return x-'A';
	if(x>='a'&&x<='z')return x-'a'+26;
	if(x>='0'&&x<='9')return x-'0'+52;
}
void insert(char str[]) {
	int now=0,len=strlen(str);
	for(int i=0; i<len; i++) {
		int numer=num(str[i]);
		if(!tree[now][numer])tree[now][numer]=++c;
		now=tree[now][numer];
		cnt[now]++;
	}
}
int main() {
	for(int i=0; i<=c; i++) {
		for(int j=0; j<=70; j++) {
			tree[i][j]=0;
		}
	}
	for(int i=0; i<=c; i++)cnt[i]=0;
	c=0;
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>s;
		insert(s);
	}
	long long ans=0;
	for(int i=1;i<=c;i++){
		ans+=1ll*cnt[i]*(cnt[i]-1)/2;
	}
	cout<<ans;
	return 0;
}
```

## Idea

对于样例

```
3
abc ard are
```

可以建字典树如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/0puqu7jh.png)

首先我们对于 `a` 点，有 $3$ 个字符串共同经过这个点，所以会有 $3$ 组字符串组对这个 `a` 产生贡献（让答案加 $1$）。

再看 `r` 点，有 $2$ 个字符串共同经过这个点，所以会有 $1$ 组字符串组对这个 `r` 产生贡献。

再手搓几组样例，推广一下结论：有 $n$ 个字符串共同经过一个点，则就有 $\dfrac{n(n-1)}{2}$ 的字符串组对它产生贡献。

所以我们只需要建树求出 $cnt$ 数组（即每个点经过字符串的数量），就可 $\operatorname{O}(n)$ 地求出答案了。

代码见上。

## Tips

- 本题答案也可能爆 ```int```。
- 如果要实现 `int` 整数与 `int` 整数相乘得到 `long long` 整数，需要乘 `1ll`（即 `long long` 类型下的 $1$），否则系统仍会按照 `int` 型计算而导致爆 `int`。

---

## 作者：I_AK_CTS (赞：0)

# 正解
这个题是个字典树。\
遍历这一棵字典树，统计每一层的贡献，每一层即代表一个前缀的长度。\
统计子节点之间能够形成这个前缀的数目，这个题就切了……
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 130, M = 3e5 + 5;
int cnt = 0;
int n, ans;
struct node {
	int son[N];
	int sum, e;
	vector<char> Adj;
	int num[N], tot;
	void clear() {
		memset(son, 0, sizeof(son));
		memset(num, 0, sizeof(num));
		sum = e = 0;
		Adj = vector<char>();
	}
} trie[M];
int root = 0;
void insert(string s, int len) {
	int now = root;
	for (int i = 0; i < len; i++) {
		int ch = s[i];
		if (trie[now].son[ch] == 0) {
			++cnt;
			trie[now].son[ch] = cnt;
			trie[now].Adj.push_back(ch);
		}
		trie[now].num[ch]++, trie[now].tot++;
		now = trie[now].son[ch];
		trie[now].sum++;
	}
	trie[now].e++;
}
void dfs(int x, int dep) {
	int now = x;
	int num = 0, Num = 0;
	for (auto ch : trie[now].Adj) {
		num = num + trie[now].num[ch] * trie[now].e;
		Num = Num + trie[now].num[ch] * (trie[now].tot - trie[now].num[ch]);
	}
	Num >>= 1;
	num += trie[now].e * (trie[now].e - 1) / 2 + Num;
	ans += num * dep;
	for (auto ch : trie[now].Adj) dfs(trie[now].son[ch], dep + 1);
}
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string s;
		cin >> s;
		insert(s, s.size());
	}
	dfs(root, 0);
	cout << ans << endl;
	return 0;
}
```
~~为什么我写的和我的思路看上去差异很大，其实是为了防作弊哦……~~

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑建立 `Trie` 树，先将 $n$ 个字符串插入进去，对于每一个前缀记录一下有多少个字符串的某个前缀是这个前缀。

然后对于每个字符串，在 `Trie` 树上遍历一遍，设以当前位置为前缀的字符串数量为 $x$，扫描到第 $i$ 个字符。

因为是求两个字符串的最大前缀，所以要先减去 $(i-1) \times x$，然后加上 $i \times x$。

时间复杂度为 $O(\sum |S_i|)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=3e5+10,M=27;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,ans,cnt;
ll A[N][M],B[N][M];
string s[N];
void insert(ll x){
    ll p=0;
    for(int i=0;i<s[x].size();i++){
        ll c=s[x][i]-'a';
        if(!A[p][c])
          A[p][c]=++cnt;
        B[p][c]++;
        p=A[p][c];
    }
}
void Find(ll x){
    ll p=0;
    for(int i=0;i<s[x].size();i++){
        ll c=s[x][i]-'a';
        ans-=i*B[p][c];
        ans+=(i+1)*B[p][c];
        p=A[p][c];
    }
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		cin>>s[i];
		insert(i);
		ans-=s[i].size();
	}
	for(int i=1;i<=n;i++)
	  Find(i);
	write(ans/2);
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

说实话，这次 ABC 挺水的。   
[传送门](https://www.luogu.com.cn/problem/AT_abc353_e)    
## 题意
设 $\operatorname{f}(a,b)$ 为 $a,b$ 两字符串的最长公共前缀长度。   
求 $\sum\limits^{n-1}_{i=1}\sum\limits^n_{j=i+1}\operatorname{f}(s_i,s_j)$.    
## 解法
看到最长公共前缀，想到 Trie。   
所以说我们只需要建出 Trie，然后对每个 $i$ 先删除自己的贡献，再跑一次 dfs 统计所有公共前缀即可。   
可以说这个题比板子还板子。   
CODE：   
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst int N=3e5,base=26;
int tot=1,n,trie[N+10][base+2],siz[N*base+10];
string s[N+10];
ll ans;
il void Insert(string s,int z){
	int n=s.length();
	int u=1,c=0;
	for(int i=0;i<n;i++){
		c=s[i]-'a';
		if(!trie[u][c]){
			trie[u][c]=++tot;
		}
		u=trie[u][c];
		siz[u]+=z;
	}
}
il ll solve(string s){
	int n=s.length(),u=1,c;
	ll ans=0;
	for(int i=0;i<n;i++){
		c=s[i]-'a';
		u=trie[u][c];
		ans+=siz[u];
	}
	ret ans;
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		Insert(s[i],1);
	}
	for(int i=1;i<=n;i++){
		Insert(s[i],-1);
		ans+=solve(s[i]);
	}
	write(ans);
	ret 0;
}
```

---

## 作者：CheZiHe929 (赞：0)

### 简要题意

给定 $n$ 个字符串 $s$，定义 $f(x,y)$ 为字符串 $x,y$ 的最长公共前缀的长度，求 $\sum\limits_{i=1}^{n-1} \sum\limits_{j=i+1}^{n} f(s_i,s_j)$ 的值。

### 简要思路

哈希，并用一个 `map` 维护每个字符串在之前出现过的次数，对于每一个字符串，都枚举其所有的前缀，并更新答案。

注意此题卡了 $998244353,1000000007$ 等常见的模数。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug puts("#CheZiHe929")
#define Yes puts("Yes")
#define No puts("No")
const int MAXN=3e5+5;
const int p=1222827239;

inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
inline void print(int x){char st[105];int top=0;if(x==0)putchar('0');if(x<0)putchar('-');while(x){if(x>0)st[++top]=x%10+48;else st[++top]=-(x%10)+48;x/=10;}while(top)putchar(st[top--]);}
inline void println(int x){print(x);putchar('\n');}
inline void printsp(int x){print(x);putchar(' ');}
inline void put(int x,int i,int n){i==n?println(x):printsp(x);}

std::map<int,int> m;//m[i] 表示 hash 值为 i 的字符串出现的次数 
char s[MAXN];

signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	int n=read(),ans=0;
	for(int i=1;i<=n;i++){
		std::cin>>s+1;
		int len=strlen(s+1),x=0;
		for(int j=1;j<=len;j++){//枚举所有前缀 
			x=x*131+s[j]-'a'+1;//hash
			ans+=m[x]++;//更新答案 
		}
	}
	println(ans);

	return 0;
}

```

---

## 作者：Vitamin_B (赞：0)

# 思路
字典树板子题。如果你不会字典树，请右转其它题解。

我们用 $tr_{i,j}$ 表示从 $i$ 号节点转移过来且以字母 $j$ 结尾的节点编号，$s_{i,j}$ 表示这种前缀字符串（从 $i$ 号节点转移过来且以字母 $j$ 结尾）的个数，我们不管前缀有多长，只需要计算 $\sum C_{s_{i,j}}^2$ 即可，因为最长前缀会在递归遍历时被逐层计算。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, tot;
ll sum;
string a;
pii tr[300005][30];
void add () {
	int now = 0;
	for (char& i : a) {
		if (! tr[now][i - 'a'].second)
			tr[now][i - 'a'].second = ++ tot;
		++ tr[now][i - 'a'].first;
		now = tr[now][i - 'a'].second;
	}
	return ;
}
void find (int now) {
	for (int i = 0; i < 26; ++ i)
		if (tr[now][i].second)
			sum += tr[now][i].first * (tr[now][i].first - 1ll) / 2, find (tr[now][i].second);
	return ;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 0; i < n; ++ i)
		cin >> a, add ();
	find (0);
	cout << sum;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 解法
### 字符串哈希
这个题最常见的做法是字典树，玄学一点可以写单调栈。但针对本体而言，字符串哈希是个好想的、代码量小的做法。

[字符串哈希](https://www.cnblogs.com/r1-12king/p/15726654.html)原理可以自行参考。

针对本题，用 $\operatorname{map}$ 来储存最长公共前缀的个数，当哈希值符合要求时，用 $ans$ 将哈希值累加，并将该最长公共前缀长度加 $1$。

注意：用双哈希，以避免哈希值冲突。
### code
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
ull n,h1,h2,ans;
string s;
map<pair<ull,ull>,ull> mp;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(ull i=1;i<=n;i++){
		cin>>s;
		ull l=s.size();
		h1=h2=1;
		for(ull j=0;j<l;j++){
			h1=h1*131+s[j]-'a';
			h2=h2*1331+s[j]-'a';
			ans+=mp[{h1,h2}];
			mp[{h1,h2}]++;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Liyunze123 (赞：0)

# 题意
给定 $n$ 个字符串，$f(i,j)$ 表示 $s_i$ 和 $s_j$ 的最长前缀长度。求 $f(i,j)$ 之和。
# 题解
用 Trie 树解。

对 Trie 树不懂的请看[这里](https://www.luogu.com.cn/problem/solution/P8306)。

接下来就只要统计有 $k$ 个字符串刚刚好与 $s_i$ 匹配到第 $j$ 个字符，答案就加 $j \times k$。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,idx;
string c[300010];
long long ans;
struct tree{
	int size,son[27],have_son[27];
}tr[300010];
void dfs(string c){
	int u=0;
	for(int w=0;c[w];w++){
		if(tr[u].have_son[c[w]-'a'+1])u=tr[u].son[c[w]-'a'+1];
		else break;
		ans+=(long long)(tr[u].size-tr[tr[u].son[max(c[w+1]-'a'+1,0)]].size)*(w+1);
	}
}
void add(string c){
	int u=0;
	for(int w=0;c[w];w++){
		if(!tr[u].have_son[c[w]-'a'+1])tr[u].son[c[w]-'a'+1]=++idx,tr[u].have_son[c[w]-'a'+1]=1,tr[tr[u].son[c[w]-'a'+1]].size=1;
		else tr[tr[u].son[c[w]-'a'+1]].size++;
		u=tr[u].son[c[w]-'a'+1];
	}
}
int main(){
	scanf("%d",&n);
	for(int w=1;w<=n;w++)cin>>c[w];
	for(int w=n;w;w--)dfs(c[w]),add(c[w]);
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：KSCD_ (赞：0)

### 题意
给出 $n$ 个字符串，求这些字符串两两之间最长公共前缀长度的和。
### 思路
暴力地两两计算显然会超时，需要优化。

考虑按位求解。按照**当前位之前的位全部一致**的要求分组。因此在每一组中，若当前位某一字母有 $k$ 个且 $k>1$，则会产生 $\frac{k(k-1)}{2}$ 的贡献。

为了接着处理后面的位，要在处理时把**还没处理完的字符串**按照这一位的值分组，处理完这一位后再分组处理下一位。

如此，若设字符串总长度为 $S$，由于每一位只会被处理一次，时间复杂度为 $O(S)$。

具体看代码实现。
### 代码
```cpp
#include<iostream>
#include<vector>
#define int long long
using namespace std;
const int N=3e5+10;
int n,ans;
string s[N];
vector <int> st;//初始的组，包含所有字符串 
void sol(vector <int> &sg,int pos)
{
	vector <int> ts[27];
	int c[27];
	for(int i=0;i<26;i++) c[i]=0;
	for(int k:sg)
	{
		int id=s[k][pos]-'a';
		c[id]++;
		if(s[k].size()>pos+1) ts[id].push_back(k);//只有这一位相同，才可能继续在同一组 
	}//处理这一组中的所有字符串 
	for(int i=0;i<26;i++) if(c[i]>1)
	{
		ans+=c[i]*(c[i]-1)/2;//处理贡献 
		if(ts[i].size()>1) sol(ts[i],pos+1);//继续处理下一位 
	} 
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i],st.push_back(i); 
	sol(st,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：__Floze3__ (赞：0)

## 思路简介

~~AT 不会出题可以不出，还放个板子什么意思？~~

看到这题我们不难想到使用字典树进行求解。我们使用一个 cnt 数组总计有多少个字符串经过当前节点，那么统计答案变得异常简单：我们在向字典树插入字符串时，可以先加上当前节点的 cnt 数量，再使得当前节点的 cnt 值加一。我们只要再字典树的模板上稍作修改即可。

## 代码

[赛时提交链接](https://atcoder.jp/contests/abc353/submissions/53345974)

---

## 作者：PDAST (赞：0)

## 题意
给你 $n$ 个字符串，命名为 $s_{1},s_{2},\dots,s_{n}$，求他们所有字符串两两之间前缀相同长度之和。即令`f(s1,s2)`为字符串 $s_{1}$ 与 $s_{2}$ 的最长公共前缀长度，求下列公式的值：
$$
\small\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}f(s_{i},s_{j})
$$
## 思路
将每个前缀做一个哈希，存进映射表里，不会的请移步[这里](https://www.luogu.com.cn/article/fy7sx50i)，每存一个字符累加器便加上这个与字符串哈希值相同的的字符串的数量，相应的，此哈希值代表的字符前缀的数量加一，最后输出累加器就行了。
## 代码
~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,sum;
map<int,int>mp;
string st;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>st;
		int x=1;
		for(char j:st){
			x=(x*903+j)%1000000003838347;
			sum+=mp[x];
			mp[x]++;
		}
	}
	cout<<sum;
	return 0;
} 
~~~

---

