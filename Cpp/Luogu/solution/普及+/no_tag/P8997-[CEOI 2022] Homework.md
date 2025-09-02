# [CEOI 2022] Homework

## 题目描述

这是 Helena 的数学作业中的一道题：

我们定义合法表达式如下：

- `?` 是合法表达式，这表示一个未知数。
- 如果 $A,B$ 均为合法表达式，那么 $\texttt{min(}A\texttt{,}B\texttt{)}$ 和 $\texttt{max(}A\texttt{,}B\texttt{)}$ 均为合法表达式，这分别表示取左右两边的最大值/最小值。

设 `?` 的个数为 $N$，现在给出一个合法表达式，将每一个问号替换为 $1\sim N$ 中的任意一个数并且每一个数不能使用多次，可以得到多少种不同的答案？

可怜的 Helena 并不会做，请你帮帮她。

## 说明/提示

### 样例 1 解释

无论权值如何选择，最后的答案都会是 $\min\{1,2,3,4\}$，也就是 $1$。

### 样例 2 解释

答案为 $4$ 的方案是： `4=max(4,max(3,min(2,1)))`，答案为 $3$ 的方案是 `3=max(3,max(2,min(1,4)))`，可以证明答案不可能为 $1$ 或 $2$。

### 数据规模与约定

对于全部数据，$2\le N\le 10^6$。

| Subtask 编号 |                                   特殊限制                                   | 得分 |
| :----------: | :--------------------------------------------------------------------------: | :--: |
|     $1$      |                                   $N\le 9$                                   | $10$ |
|     $2$      |                                  $N\le 16$                                   | $13$ |
|     $3$      | 对于任意 $\texttt{min(}A\texttt{,}B\texttt{)}$ 与 $\texttt{max(}A\texttt{,}B\texttt{)}$，$A$ 和 $B$ 中有一个为 `?`。 | $13$ |
|     $4$      |                                 $N\le 10^3$                                  | $30$ |
|     $5$      |                                  无特殊限制                                   | $34$ |

## 样例 #1

### 输入

```
min(min(?,?),min(?,?))```

### 输出

```
1```

## 样例 #2

### 输入

```
max(?,max(?,min(?,?)))```

### 输出

```
2```

## 样例 #3

### 输入

```
min(max(?,?),min(?,max(?,?)))```

### 输出

```
3```

# 题解

## 作者：PCCP (赞：7)

## 赛时思路

首先看到题，很容易发现每一步的答案都一定是从两个数转移而来，这两个数要么是上一步的答案，要么是原序列里的数。考虑与区间合并相关的一些算法或数据结构，发现更像是并查集合并，进一步想到克鲁斯卡尔重构树，$ \min $ 与 $ \max $ 的运算使得某一段链上的答案是不减或不增的，似乎有些相像。

但是会发现整个树链上的答案并不一定具有单调性，不过克鲁斯卡尔重构树的结构非常适合我们进行计算或统计，同时也保证我们整个树的节点数始终为 $ 2n-1 $。

带入小数据模拟不难发现，不论我们如何排列这 $ n $ 个数，一次运算取得的值一定是有范围的。比如说第一次合并进行的是 $ \max $ 运算，那么取值范围就是 $ [2,n] $；进行的是 $ \min $ 运算，取值范围则是 $ [1,n-1] $。同时还能发现一连串包含在一起的相同运算可以合并，这样还可以进一步缩小取值范围，因此着手从此方向入手。

不过赛时后面我就想歪了，想到了求某一处的值成为最终答案的取值范围，写了个非常复杂的 $ n\log_2{n} $ 的奇妙做法，不过这个做法只能保证 $ n\le8 $ 时的正确性，不过神奇的是我居然还拿到了一个捆绑点的分，只能说数据太水了。

这是我的赛时代码：[here](https://www.luogu.com.cn/paste/k58l5ju1)

## 正解

其实会发现不仅相同运算合并可以缩小取值范围，不同的也可以。但是问题在于如何合并取值范围才是正确的，我的赛时代码就不止一次写错，尽管我赛时思路是有问题的。

其实简单模拟一下即可得出规律：

设 $ le_i $ 为小于取值范围的数的个数，$ ge_i $ 为大于取值范围的数的个数。若操作为 $ \min $，$ op_i=0 $；若操作为 $ \max $，$ op_i=1 $。~~（不要说为什么和其他题解一样，因为我赛时就是这样想的，详见我赛时代码）~~

$$ le_i= \begin{cases}
\min(le_{l_i},le_{r_i}) &\text{if } op_i=0
\\
le_{l_i}+le_{r_i}+1 &\text{if } op_i=1
\end{cases} $$

$$ ge_i= \begin{cases}
\min(ge_{l_i},ge_{r_i}) &\text{if } op_i=1
\\
ge_{l_i}+ge_{r_i}+1 &\text{if } op_i=0
\end{cases} $$

要证明其正确性，我想了很久，找到如下的解释：

关于取最小值的部分，大家应该都非常明白。关键是相加为什么是对的。模拟这种情况：四个数，取前两个最小值，再取后两个最小值，最后取两个结果的最小值。最后的最小值只能是 $ 1 $，如果简单把上界也取最小的话，范围就变成 $ [1,3] $ 了，但是事实并非如此，为什么呢？因为通过前面两次运算一定会有两个数被排除掉，被排掉的数不可能再参与运算，所以两个上界要相加。那为什么还要在后面加上一呢？还是前面那个例子，最后一次运算，取最小，也就是说还有一个数比他大；那取最大的也是同理。

虽然非常口语化，但是我觉得还是比较好理解的。

## 实现细节

读入建树的话，有写过括号题的朋友就知道要用栈，碰到左括号和逗号就新建节点，由于数据范围很大，所以在本地跑是要开大系统栈的。

至于建树，图论的建图方法都可以，不过由于克鲁斯卡尔重构树是二叉树，二叉树的建图方法会更合适些。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
using namespace std;
typedef pair<int,int> PII;
const int N=2e6+10;
int n,tot=1;
struct node{
	int l,r,le,ge,kind;
}tr[N];
string s;
stack<int> qi;
void dfs1(int x){
	if(tr[x].l){
		dfs1(tr[x].l);
	}
	if(tr[x].r){
		dfs1(tr[x].r);
	}
	if(!tr[x].kind){
		tr[x].ge=tr[tr[x].l].ge+tr[tr[x].r].ge+1;
		tr[x].le=min(tr[tr[x].l].le,tr[tr[x].r].le);
	}
	else if(tr[x].kind&1){
		tr[x].le=tr[tr[x].l].le+tr[tr[x].r].le+1;
		tr[x].ge=min(tr[tr[x].l].ge,tr[tr[x].r].ge);
	}
}
main(){
	cin>>s;
	int leng=s.length();
	qi.push(1);
	for(int i=0;i<leng;i++){
		if(s[i]=='('){
			tr[qi.top()].l=++tot;
			tr[qi.top()].kind=s[i-1]=='n'?0:1;
			if(s[i+1]=='?'){
				tr[tot].kind=2;
				n++;
			}
			else{
				qi.push(tot);
			}
		}
		else if(s[i]==','){
			tr[qi.top()].r=++tot;
			if(s[i+1]=='?'){
				tr[tot].kind=2;
				n++;
			}
			else{
				qi.push(tot);
			}
		}
		else if(s[i]==')'){
			qi.pop();
		}
	}
	dfs1(1);
	printf("%d\n",n-tr[1].le-tr[1].ge);
}
```


---

## 作者：Bitaro (赞：6)

哥几个又来体验欧洲风味了。给大家提供一种不用脑子的想法，适合和我一样的青春哥。

这个表达式很神秘，所以我们把这个结构变成一棵二叉树的样子。问号为叶子节点，除了叶子节点以外的每个节点都有属性 $opt$ 代表这个节点代表的运算是 $\min$ 还是 $\max$。

如果要枚举每个排列然后去重显然不现实，但是发现可能答案只有 $n$ 个，我们只要判断每个答案合不合法就行。

思考答案怎么来的：一个值为答案(题目保证了每个值只有一个)的叶子往上跳，一路过关斩将到了根节点，然后成为答案。

它是怎么过关斩将的呢？设这个值为 $u$，当跳到一个祖先时，如果祖先的运算为 $\max$，那它要比另一个儿子大，否则要比另一个儿子小。

现在我们看看它什么时候不合法。对于每个祖先都有一个限制，类似于它必须比另一个儿子大，或者它必须比另一个儿子小。这实际上都是对另一个儿子的值提出了限制。想要满足限制，就必须对儿子子树中的问号的值也提出限制。

限制是啥？实际上我们只关心值是大于 $u$ 还是小于 $u$。如果小于 $u$ 的数大于 $u-1$，就必然有限制不能被满足。于是就不合法了。同理，对于大于 $u$ 的数，如果限制大于 $n-u$ 项，也不合法。

于是我们有 $f_{i,0/1,0/1}$ 表示这个点的值比答案小或者大时，小于或者大于的数有多少个，转移很简单，这里以运算为 $\max$ 为例：

$$f[u][0][0]\leftarrow f[ls][0][0]+f[rs][0][0]$$

$$f[u][0][1]\leftarrow f[ls][0][1]+f[rs][0][1]$$

$$f[u][1][0]\leftarrow \min({f[ls][1][0]+f[rs][1][0],f[ls][0][0]+f[rs][1][0],f[ls][1][0]+f[rs][0][0]})$$

$$f[u][1][1]\leftarrow \min({f[ls][1][1]+f[rs][1][1],f[ls][0][1]+f[rs][1][1],f[ls][1][1]+f[rs][0][1]})$$

对于小于答案的情况，必须两个儿子都小于答案，对于答案大于答案的情况，只要有一个儿子大于答案就行。

求出了这个之后，我们就能一边遍历找出每个点作为答案时的最小的小于它的限制条数 $mzero$ 与最小的大于它的限制条数 $mone$。根据前文，如果这个节点作为答案 $u$ 且 $u-1<mzero$ 或者 $n-u<mone$，那么就是不合法的。我们可以求出合法区间 $[1+mzero,n-mone]$。也就是说这个区间可以作为答案。

我们把所有能作为答案的区间取并就是最终的答案了。可以看到其他题解都要用到好多性质，我们的题解只要用到简单的动态规划。实在是青春至极。

```cpp
/*
slow is fast
*/
#include<bits/stdc++.h>
#define pre(i,a,b) for(int i=a;i<=b;++i)
#define suf(i,a,b) for(int i=a;i>=b;--i)
#define ll long long
#define pii pair<int,int>
using namespace std;
const int N=2e6+6,p=1e9+7;
namespace Y {
string s;
int n,cnt=1,opt[N];
vector<int> e[N];
//1:max,-1:min
//0:< 1:>
#define leaf(u) if(e[u].size()==0)
int f[N][2][2];
void dfs(int u) {
  for(auto v:e[u]) dfs(v);
  leaf(u) {
    f[u][0][0]=1;
    f[u][1][1]=1;
  } else {
    int ls=e[u][0],rs=e[u][1];
    if(opt[u]==1) {
      f[u][0][0]=f[ls][0][0]+f[rs][0][0];
      f[u][0][1]=f[ls][0][1]+f[rs][0][1];
      f[u][1][0]=min({f[ls][1][0]+f[rs][1][0],f[ls][0][0]+f[rs][1][0],f[ls][1][0]+f[rs][0][0]});
      f[u][1][1]=min({f[ls][1][1]+f[rs][1][1],f[ls][0][1]+f[rs][1][1],f[ls][1][1]+f[rs][0][1]});
    } else {
      f[u][0][0]=min({f[ls][0][0]+f[rs][0][0],f[ls][0][0]+f[rs][1][0],f[ls][1][0]+f[rs][0][0]});
      f[u][0][1]=min({f[ls][0][1]+f[rs][0][1],f[ls][0][1]+f[rs][1][1],f[ls][1][1]+f[rs][0][1]});
      f[u][1][0]=f[ls][1][0]+f[rs][1][0];
      f[u][1][1]=f[ls][1][1]+f[rs][1][1];
    }
  }
}
int c[N];
void add(int l,int r) { c[l]++,c[r+1]--; }
void findans(int u,int m0=0,int m1=0) {
  leaf(u) {
    add(1+m0,n-m1);
    return ;
  }
  int ls=e[u][0],rs=e[u][1];
  if(opt[u]==1) {
    findans(ls,m0+f[rs][0][0],m1+f[rs][0][1]);
    findans(rs,m0+f[ls][0][0],m1+f[ls][0][1]);
  } else {
    findans(ls,m0+f[rs][1][0],m1+f[rs][1][1]);
    findans(rs,m0+f[ls][1][0],m1+f[ls][1][1]);
  }
}
void MAIN() {
  cin>>s;
  int u=1;
  stack<int> sta;
  for(int i=0;i<s.size();++i) {
    if(s[i]=='?') { ++n;continue; }
    if(s[i]==')') continue;
    if(s[i]=='m') {
      sta.push(cnt+2);
      e[u].push_back(cnt+1);
      e[u].push_back(cnt+2);
      if(s[i+1]=='a') opt[u]=1;
      else opt[u]=-1;
      u=cnt+1;
      cnt+=2;
      i+=3;
    }
    if(s[i]==',') u=sta.top(),sta.pop();
  }
  dfs(1);
  findans(1);
  int now=0,ans=0;
  pre(i,1,n) {
    now+=c[i];
    if(now) ++ans;
  }
  cout<<ans<<endl;
}
};//namespace Y
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T=1;
	while(T--) Y::MAIN();
	return 0;
}
```


---

## 作者：LJ07 (赞：4)

建表达式二叉树。发现能划分成子问题然后合并。

如果令 ```X``` 表示不能取到，```O``` 表示可以取到，那么对于一个子树这个子问题的取值的 ```XO``` 串一定形如 ```XX..XOO..OXX..X```。(从左往右第 $i$ 个表示值为 $i$)。

怎么合并？分情况讨论。

---
为帮助理解，以 max 为例。如果是 ```XXOX``` 和 ```XOX``` 合并，那么最左边的 ```O``` 一定得在所有 ```X``` 的左边。最右边的 ```O``` 右边的 ```X``` 数只要满足不小于两个串最右边的 ```X``` 数最小的那个即可。
这样得到的是 ```XXXOOOX```，又因为是 max，所以最左边的那个 ```O``` 也取不到。最终得到的是 ```XXXOOXX```。

---

令 $l_i$ 表示以 $i$ 为根的子树的 ```XO``` 串最左边有几个 ```X```，$r_i$ 表示最右边有几个 ```X```。

若操作为 max，转移为 $l_i=\sum l+1,r_{i}=\min r$。

若操作为 min，转移为 $r_i=\sum r+1,l_i=\min l$。

```cpp
char s[N + 5];
int p, rt, cnt, lc[N + 5], rc[N + 5], o[N + 5], ct;
int dfs()
{
	int x = ++cnt;
	if (s[p] == '?') {
		++p;
		++ct;
		return x;
	}
	if (s[++p] == 'i') {
		o[x] = 1;
	}
	p += 3;
	lc[x] = dfs();
	++p;
	rc[x] = dfs();
	++p;
	return x;
}
pii f[N + 5];
void slv(int u)
{
	if (!lc[u] && !rc[u]) {
		f[u] = mk(0, 0);
		return ;
	}
	slv(lc[u]);
	slv(rc[u]);
	auto [l1, r1] = f[lc[u]];
	auto [l2, r2] = f[rc[u]];
	if (o[u]) {
		f[u] = mk(min(l1, l2), r1 + r2 + 1);
	}else {
		f[u] = mk(l1 + l2 + 1, min(r1, r2));
	}
}

int main()
{
	scanf("%s", s);
	slv(rt = dfs());
	printf("%d\n", ct - f[rt].second - f[rt].first);
    return 0;
}
```

---

## 作者：gdf_yhm (赞：0)

### [P8997](https://www.luogu.com.cn/problem/P8997)

### 题解

按题意模拟，用栈建出二叉树，叶子节点是要填的值，非叶子是运算符。

判断一个叶子能贡献能填哪些数并最终成为答案，即 dp 计算要使该叶子的值 $ans$ 成为答案最少要填 $num0$ 个 $\le ans$ 和 $num1$ 个 $>ans$ 的数。发现 dp 只与 $\le ans$ 和 $>ans$ 的数的个数有关，可以统一计算。

设 $dp_{u,0/1,0/1}$ 表示 $u$ 子树内，$u$ 处的值 $\le ans$ 或 $>ans$，$num0$ 或 $num1$ 最少为多少。根据 $u$ 处的运算符分类讨论转移。如果 $u$ 处运算符为 $<$，如果 $u$ 的值 $\le ans$，那 $ls$ 和 $rs$ 的值有一个 $\le ans$ 即可；否则两个都有 $>ans$。运算符为 $>$ 同理。

对于每个叶子算限制，只与从根到 $u$ 的 dp 值有关。因为叶子的值为 $ans$，所以在路径上如果 $u$ 点运算符为 $<$，要进入左儿子，那么右儿子的值 $>ans$，左儿子的值 $\le ans$，$num0$ 加上 $dp_{rs,1,0}$，$num1$ 加上 $dp_{rs,1,1}$。其他同理。

可以发现放在一个叶子的答案是一个区间 $[num0+1,n-num1]$，差分维护区间加，最后计算大于 $0$ 的位置数。

### code

```cpp
int n,m,ans;
char s[maxn<<2];
int st[maxn],tp;
int ls[maxn],rs[maxn],op[maxn],dp[maxn][2][2],idx;
void dfs(int u){
	if(op[u]==3){
		dp[u][0][0]=1,dp[u][1][1]=1;
		return ;
	}
	dfs(ls[u]),dfs(rs[u]);
	if(op[u]==1){
		dp[u][0][0]=min({dp[ls[u]][0][0]+dp[rs[u]][0][0],dp[ls[u]][0][0]+dp[rs[u]][1][0],dp[ls[u]][1][0]+dp[rs[u]][0][0]});
		dp[u][0][1]=min({dp[ls[u]][0][1]+dp[rs[u]][0][1],dp[ls[u]][0][1]+dp[rs[u]][1][1],dp[ls[u]][1][1]+dp[rs[u]][0][1]});
		dp[u][1][0]=dp[ls[u]][1][0]+dp[rs[u]][1][0];
		dp[u][1][1]=dp[ls[u]][1][1]+dp[rs[u]][1][1];
	}
	else{
		dp[u][0][0]=dp[ls[u]][0][0]+dp[rs[u]][0][0];
		dp[u][0][1]=dp[ls[u]][0][1]+dp[rs[u]][0][1];
		dp[u][1][0]=min({dp[ls[u]][1][0]+dp[rs[u]][1][0],dp[ls[u]][1][0]+dp[rs[u]][0][0],dp[ls[u]][0][0]+dp[rs[u]][1][0]});
		dp[u][1][1]=min({dp[ls[u]][1][1]+dp[rs[u]][1][1],dp[ls[u]][1][1]+dp[rs[u]][0][1],dp[ls[u]][0][1]+dp[rs[u]][1][1]});
	}
}
int f[maxn];
void calc(int u,int l,int r){
	if(op[u]==3){
		f[l+1]++,f[m-r+1]--;
		return ;
	}
	if(op[u]==1){
		calc(ls[u],l+dp[rs[u]][1][0],r+dp[rs[u]][1][1]),calc(rs[u],l+dp[ls[u]][1][0],r+dp[ls[u]][1][1]);
	}
	else{
		calc(ls[u],l+dp[rs[u]][0][0],r+dp[rs[u]][0][1]),calc(rs[u],l+dp[ls[u]][0][0],r+dp[ls[u]][0][1]);
	}
}
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='m'){
			if(s[i+1]=='i')st[++tp]=++idx,op[idx]=1;
			else st[++tp]=++idx,op[idx]=2;
			if(s[i-1]=='(')ls[st[tp-1]]=st[tp];
			if(s[i-1]==',')rs[st[tp-1]]=st[tp];
		}
		if(s[i]=='?'){
			op[++idx]=3;++m;
			if(s[i-1]=='(')ls[st[tp]]=idx;
			if(s[i-1]==',')rs[st[tp]]=idx;			
		}
		if(s[i]==')')tp--;
	}
	dfs(1);calc(1,0,0);
	for(int i=1;i<=m;i++)f[i]+=f[i-1],ans+=f[i]>0;
	printf("%lld\n",ans);
}
```

---

