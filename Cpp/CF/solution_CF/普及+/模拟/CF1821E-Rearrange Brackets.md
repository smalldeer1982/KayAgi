# Rearrange Brackets

## 题目描述

A regular bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example:

- bracket sequences "()()" and "(())" are regular (the resulting expressions are: "(1)+(1)" and "((1+1)+1)");
- bracket sequences ")(", "(" and ")" are not.

You are given a regular bracket sequence. In one move, you can remove a pair of adjacent brackets such that the left one is an opening bracket and the right one is a closing bracket. Then concatenate the resulting parts without changing the order. The cost of this move is the number of brackets to the right of the right bracket of this pair.

The cost of the regular bracket sequence is the smallest total cost of the moves required to make the sequence empty.

Actually, you are not removing any brackets. Instead, you are given a regular bracket sequence and an integer $ k $ . You can perform the following operation at most $ k $ times:

- extract some bracket from the sequence and insert it back at any position (between any two brackets, at the start or at the end; possibly, at the same place it was before).

After all operations are performed, the bracket sequence has to be regular. What is the smallest possible cost of the resulting regular bracket sequence?

## 样例 #1

### 输入

```
7
0
()
0
(())
1
(())
5
()
1
(()()(()))
2
((())()(()())((())))
3
((())()(()())((())))```

### 输出

```
0
1
0
0
1
4
2```

# 题解

## 作者：uid_310801 (赞：5)

评价是比 D 简单。发现每次一定删掉最靠右的 `()`，且一直这样操作总能把所有括号删完。如何计算代价？

发现一对括号删掉时，它右面的右括号数量就是它的深度（定义最外层括号的深度为 $0$），且删掉一对括号时，其它括号的深度不会改变。故我们可以扫一遍，求出每对括号的深度，答案就是每对括号的深度之和。

考虑一次操作我们应该做什么？我们尽量让每对括号的深度之和变得尽量少。分析样例，发现可以每次把一个右括号移动到与它匹配的左括号的右边，这时，答案的减少量就是它们之间的括号对数。

我们将每对括号之间的距离排序，取前 $k$ 大的减去即可。利用桶排可以做到 $O(n)$，但是没写。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define deb(x) cerr<<"Line: "<<__LINE__<<", val= "<<x<<"; \n"
#define pii pair<ll,ll>
#define mp make_pair
#define fi first
#define se second
const ll N=2e5+10;
ll T,n,k,L[N],dep[N];
char c[N];
void work(){
	scanf("%lld",&k);
	scanf("%s",c+1);
	n=strlen(c+1);
	ll de=0,ans=0;
	stack<ll> s;
	vector<pii> v;
	for(ll i=1;i<=n;i++){
		if(c[i]=='('){
			de++;
			s.push(i);
		}
		else{
			de--;
			dep[i]=de;
			ans+=de;
			L[i]=s.top();
			s.pop();
			v.push_back(mp(-i+L[i]-1,i));
		}
	}
	sort(v.begin(),v.end());
	for(int i=0;i<min(ll(v.size()),k);i++){
		ans-=-v[i].fi/2-1;	
	}
	printf("%lld\n",ans);
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：小木虫 (赞：2)

### Preface  
这道题的 $k$ 的数据范围十分具有误导性。  
upd：这题题意真的坑死人，记住，是移动一个括号。
### Problem  
给你一个合法括号序列，允许你做 $k$ 次将某一个括号移动到其它地方的操作，操作结束后必须为合法括号序列，定义一个括号序列的价值为进行如下操作删除改括号序列的最小花费：  
选择一对形如 $\text{()}$ 的括号，移除它，花费在这个右括号后面的所有字符个数的代价。  
问你操作结束后，形成的合法括号序列的最小花费为？  
### Solution  
首先我们将括号树建出来，设 1 节点为虚根，然后你会发现一个括号序列的最小花费就是其括号树的 $\sum_{i=2}^n sz_i-1$。  
这很显然，因为如果我们优先选择在括号序列中最右边的括号（易证这个贪心策略是最优的），那么移除一个括号的花费就是它的嵌套层数，也就是在树上的非根祖先数量，稍加转化就能变为上式。  

然后我们考虑移动操作等价于移植这个节点的儿子给该节点父亲。
你发现，移植操作是无序的，即对于一个点和他的子孙，他们的先后顺序是无意义的。  

显然，一次操作的贡献就是该子树的大小 -1，因为其所有子孙的深度都 -1。  
你将子树大小排序后从大到小进行操作。

那么你发现，这个题就被你解决了。  
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int T,n,k,cnt,fa[N],sz[N];string S;
vector <int> edge[N];
void init(){cnt=0;
	for(int i=0;i<=n;i++)edge[i].clear();
}
void dfs(int u){sz[u]=1;
	for(auto v:edge[u])dfs(v),sz[u]+=sz[v];
}
void solve(){
	cin>>k>>S;n=S.size();S=" "+S;
	int now=cnt=1;
	for(int i=1;i<=n;i++){
		if(S[i]=='('){
			fa[cnt+1]=now;
			edge[now].push_back(cnt+1);
			now=++cnt;
		}else{
			now=fa[now];
		}
	}dfs(1);int res=0;
	for(int i=2;i<=cnt;i++)
		res+=sz[i]-1;
	sort(sz+2,sz+cnt+1,greater<int>());
	for(int i=2;i-1<=k&&i<=cnt;i++)
		res-=sz[i]-1;
	cout<<res<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)init(),solve();
	return 0;
}
```


---

## 作者：guanyf (赞：1)

#### 前情提要：本文语言可能有点繁琐，但是希望你能够认真看完。

### 题意
- 给你一个匹配的括号串 $S$，定义它的权值为：每次删除相邻的左右括号，将权值加上原右括号右边的括号数量，直到 $S$ 为空。其次，你可以进行 $k$ 次操作，每次操作可以把一个括号移到任何位置。求 $k$ 次操作之后，$S$ 最小的权值。

- $1 \le |S| \le 2 \cdot 10^5$

### 思路
为了方便，设 $n$ 为 $S$ 的长度。看过题意，很容易就会想到：求权值一定是从里面向外删。由于权值是加上右括号右边的括号数量，为了让答案最优，我们不妨直接从右往左，从里向外去删，很显然，这样是最优的。~~我们充分发扬人类智慧~~，想一想这个行为是不是很像**括号匹配**，因此我们可以从右往左遍历，当遇到一个右括号时，就把它压到栈里，否则弹出栈顶元素，并把答案加上栈中的元素数量（因为右边的左括号一定与它匹配的右括号一起删除了，剩下的只有未匹配的右括号）。

```
(()(()))

1. (()(())) i = 8, stack = {8}, ans = 0
          ^
2. (()(())) i = 7, stack = {8, 7}, ans = 0
         ^
3. (()(())) i = 6, stack = {8, 7, 6}, ans = 0
        ^
4. (()(())) i = 5, stack = {8, 7}, ans = 2
       ^
5. (()(())) i = 4, stack = {8}, ans = 3
      ^
6. (()(())) i = 3, stack = {8, 3}, ans = 3
     ^
7. (()(())) i = 2, stack = {8}, ans = 4
    ^
8. (()(())) i = 1, stack = {}, ans = 4
   ^

```

接着就是思考如何操作了。显然移动是不能乱移的，左括号只能移到与它匹配的右括号左边，否则整个括号序列就会不匹配。同理，右括号只能移动到与它匹配的左括号右边。**对于每个右括号，无论怎么移动，都没有左括号更优**（*希望这里读者能够仔细想想为什么*）。对于左括号而言，只有移动到与它匹配的右括号左边一位，才可以保证移动后的括号序列**能够匹配**并且**并且使答案尽可能更优**。而减少的值其实就是原来左右括号之间的**左右括号的数量**（因为在这段区间内的左右括号，权值实际上是加上了原来的右括号。但是当移动之后，这个右括号就被左括号消掉了）。因此我们可以记录出每个左括号移动之后减少的权值，并且从大到小排序，减去前 $k$ 值就可以了。

时间复杂度：$\operatorname{O}(n\log n)$。

#### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 5;
int T, n, k, tot, ans, m, a[MAXN], st[MAXN];
string s;
void solve() {
  cin >> k >> s, n = s.size(), s = ' ' + s;
  tot = ans = m = 0;
  for (int i = n; i >= 1; i--) {
    if (s[i] == '(') {
      a[++m] = (st[tot] - i) / 2, ans += --tot;
    } else {
      st[++tot] = i;
    }
  }
  sort(a + 1, a + 1 + m, greater<int>());
  for (int i = 1; i <= min(m, k); i++) ans -= a[i];
  cout << ans << '\n';
}
signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    solve();
  }
  return 0;
}
```


---

## 作者：Hisaishi_Kanade (赞：1)

挺简单的题啊，怎么 $2100$ 的。

首先一个非常自然的贪心是如果能删只会删最右边的 `()`。证明显然。

那么 $k=0$ 的计数是简单的，每对括号的价值最小化是有多少对括号包括了它，等价于在匹配这对的右括号时有多少左括号还没有完成匹配。这个可以跑一遍匹配求出。

然后我们考虑如何进行 $k$ 次操作。

对于一次操作，一种策略是将某个 `A(B)C` 的子串（这两个括号匹配）移成 `AB()C`，当处理好 `C` 之后就能直接消除 `()`。考虑这样操作能减少多少代价。首先 `C` 的代价不变，因为括号一直在它的左边。然后对于 `A`，不管是否操作，处理 `A` 时 `B`、`C` 和 `()` 都是消除过的。所以价值也不变。

但是对于 `B` 则不同，`B` 原本的删除要在 `()` 之前，每次删除都会碰到这个右括号，所以价值会比操作后多 `B` 中匹配括号的对数。

这么，答案就显然了。我们计算每一对匹配括号间字符的个数，挑最大的前 $k$ 减掉即可。

复杂度 $O(n)$。

```cpp 
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std; using ll=long long;
int n, k, i, tot, T; const int N=2e5+5, K=7; ll res;
int q[N], t[N]; char str[N];
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		res=0;
		scanf("%d %s", &k, str+1); n=strlen(str+1);
		rep(i, 1, n)
		{
			if(str[i]=='(') q[++tot]=i;
			else
			{
				res+=tot-1;
				++t[i-q[tot]-1>>1];
				--tot;
			}
		}
		req(i, n, 1)
		{
			while(k && t[i]) --k, --t[i], res-=i;// printf("del %d\n", i);
			if(!k) break;
		}
		rep(i, 1, n) t[i]=0;
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：Zimo_666 (赞：0)

## E. Rearrange Brackets

### Statement

- **本题一个测试点内有多组测试数据**。
- 对于一个匹配的括号串，定义它的权值为进行以下操作多次将它清空的最小总代价：
  - 选取两个相邻的左右括号删除，并将代价加上原右括号右边的括号数量。
- 你可以进行 **不超过 $k$ 次** 以下操作，将给定的匹配括号串 $S$ 变为另一个匹配括号串：
  - 选取 **一个** 括号，将它移动到串的任意位置。
- 求最终括号串的权值最小值。
- $1\leq |S|,\sum |S|\leq2\times10^5$，$0\leq k\leq5$。

### Solution

先考虑没有 $k$ 的限制的情况。

显然尽可能从右往左删掉匹配括号是比较合理的。

然后我们考虑设 $dep_i$ 表示右括号处在 $i$ 的括号对的贡献。

再考虑对于有 $k$ 的情况下，对于每次移动，答案会减少多少。

显然会减少中间括号对数个。我们维护他俩之间的距离然后排序选出前 $k$ 大。答案减掉这些就行了。

直接排序复杂度 $O(n\log n)$，你也可以使用其他的方法优化到 $O(n)$，不过看起来没什么必要。

[Code](https://codeforces.com/contest/1821/submission/229538923)

---

## 作者：yuanruiqi (赞：0)

## 题意简述

定义括号序列的一种权值，即每次选择相邻的 `()` 删除，删除的代价为这两个括号右边的右括号数量（已经删去的不算），删除的总代价的最小值。

给定一个括号序列，最多更改 $k$ 个括号的位置。求定义的权值的最小值。

## 题目分析

先考虑怎么计算权值，不难发现最优解一定是每次先删除最靠右的 `()`。所以可以从右往左扫一遍序列，定义一个变量 $x$，遇到右括号 $x$ 加一，遇到左括号时减一，并同时给权值累加 $x$。（如果模拟最优修改操作，那么删去这个括号时，右边的右括号数量一定是 $x$）

因为 $k$ 很小，所以可以考虑暴力每一次更改。回看以上的计算权值操作。我们可以发现可以对每一丛括号，比如 `(())`，`(()())`。累计其中左括号数量。如果修改的括号在这一丛，那么以上的两丛一定会修改成如下这样。`()()`，`()()()`。也就是把最外面的括号移走，这样是最优的，可以将答案减小丛中的左括号数量（以上分别是 $1$ 和 $2$）。那么每一次修改操作，统计序列中每一丛括号的贡献，并真实操作贡献最大的那一个。可以参考代码。

## 代码

```cpp
void solve()
{
    int k;
    cin >> k;
    string s;
    cin >> s;
    for (int i=0;i<k;++i)
    {
        while (s.size() && s[s.size() - 2] == '(') s.pop_back(), s.pop_back();
        int x = 0, mx = 0, mxidx = 0, mxtop = 0, top = s.size(), cnt = 0;
        for (int i=s.size()-1;i>=0;--i)
        {
            if (s[i] == ')') ++x;
            else --x;
            if (s[i] == '(') ++cnt;
            if (x == 0)
            {
                if (cnt > mx) mx = cnt, mxidx = i, mxtop = top;
                top = i;
                cnt = 0;
            }
        }
        if (s.size())
        {
            for (int j=mxidx;j<s.size()-1;++j)
                s[j] = s[j+1];
            for (int j=mxtop-2;j<s.size()-1;++j)
                s[j] = s[j+1];
            s.pop_back();
            s.pop_back();
        }
    }
    while (s.size() && s[s.size() - 2] == '(') s.pop_back(), s.pop_back();
    int x = 0;
    long long ans = 0;
    for (int i=s.size()-1;i>=0;--i)
    {
        if (s[i] == ')') ++x;
        else --x;
        if (s[i] == '(') ans += x;
    }
    cout << ans << '\n';
}
```


---

## 作者：falling_cloud (赞：0)

注意到题目条件中的 $0\leq k \leq 5$，那么猜测复杂度是 $\Theta(kn)$ 或 $\Theta(kn\log n)$，考虑先解决 $k=0$ 时的计数问题。

可以发现的是，对于两个规则括号序列（regular bracket sequence）并列的情况，肯定是先拆右边的括号再拆左边的括号更优，总代价就是分别拆开这两个括号序列的代价和，所以现在的问题就是，如何划分出规则括号序列和如何计算一个规则括号序列拆开的代价。

设左括号的前缀和是 $l$，右括号的前缀和是 $r$，在某个位置上 $l=r$ 时说明前面的括号已经匹配完毕，那么也就说明前面的部分是由若干个规则括号序列并列而成，这样就解决了划分问题。再考虑单个计数，每次拆分的策略一定是选择最右边的一组相邻括号 `()` 把它拆掉，因为左边的相邻括号不会影响到右边拆分的代价，而右边的括号拆掉之后会降低左边括号拆分的代价。所以在拆掉某个括号时，其右侧应该都为右括号 `)`，因此拆掉这个括号的代价也就是左侧还未匹配成功的 `(` 的数量，也就是右括号处的 $r-l$。自此，我们以 $\Theta(n)$ 的时间复杂度算出了拆括号的最小代价。

这个时候考虑怎样移括号是最优的，由于单独的一个相邻的 `()` 作为规则括号序列和其他并列时代价为 $0$，并且每次操作移动一个括号的情况下只会有一组括号受到影响，这一部分的决策也就可以由手玩得出：每次找出一个最长的规则括号序列，然后把最左边的 `(` 移至最右边的 `)` 处进行匹配。

这样在这一个**原来的**规则括号序列中的每个括号拆分代价会减少 $1$，因此这个操作相当于找出最长的规则括号序列并将其首尾删除。进行 $k$ 次删除后直接计算代价即可。

注意到最差情况下的代价为 $\displaystyle\sum_{i=1}^{\frac{n}{2}} (\frac{n}{2}-i)$，在 $n=2\times 10^5$ 的情况下答案为 $4999950000$，注意在统计答案时使用 `long long`。

时间复杂度 $\Theta(kn)$。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define PD if(flag)	cout<<"Yes"<<endl;  else cout<<"No"<<endl
using namespace std; 
const int N = 2e5 + 5; 
const int M = 1e9 + 7;
int a[N],b[N];
priority_queue <int,vector<int>,less<int>> q; 
string s;
void solve()
{
	int i,j,n,m,k,l,r,x,y,w,sum=0,ans=0,Max=0,Min=1e9+5,key=0;
	bool flag=true;
	while(!q.empty())	q.pop();
	cin>>k;
	cin>>s;	s='0'+s;
	n=s.length();
	for(i=1;i<=k;i++) 
	{
		l=1,r=0;	Max=0;
		for(j=1;j<=n;j++)
		{
			if(s[j]=='(')		sum++;
			else if(s[j]==')')	sum--;
			if(sum==0)		
			{
				r=j;
				if(r-l+1>Max)	
					Max=r-l+1,x=l,y=r;	
				l=j+1;
			}			
		}
		if(Max>2)	s[x]='.',s[y]='.';
	}sum=0;
	for(i=1;i<=n;i++)
	{
		if(s[i]=='(')				sum++;
		else if(s[i]==')')			sum--,ans+=sum;
	}
	cout<<ans<<endl;
} 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int Ti;
	for(cin>>Ti;Ti;Ti--)
		solve();
	return 0;
}
```

---

