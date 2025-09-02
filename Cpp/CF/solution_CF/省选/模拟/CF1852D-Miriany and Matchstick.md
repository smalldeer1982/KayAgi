# Miriany and Matchstick

## 题目描述

Miriany's matchstick is a $ 2 \times n $ grid that needs to be filled with characters A or B.

He has already filled in the first row of the grid and would like you to fill in the second row. You must do so in a way such that the number of adjacent pairs of cells with different characters $ ^\dagger $ is equal to $ k $ . If it is impossible, report so.

 $ ^\dagger $ An adjacent pair of cells with different characters is a pair of cells $ (r_1, c_1) $ and $ (r_2, c_2) $ ( $ 1 \le r_1, r_2 \le 2 $ , $ 1 \le c_1, c_2 \le n $ ) such that $ |r_1 - r_2| + |c_1 - c_2| = 1 $ and the characters in $ (r_1, c_1) $ and $ (r_2, c_2) $ are different.

## 说明/提示

In the first test case, it can be proved that there exists no possible way to fill in row $ 2 $ of the grid such that $ k = 1 $ .

For the second test case, BABB is one possible answer.

The grid below is the result of filling in BABB as the second row.

 $ \begin{array}{|c|c|} \hline A & A & A & A \cr \hline B & A & B & B \cr \hline \end{array} $ The pairs of different characters are shown below in red:

 $ \begin{array}{|c|c|} \hline \color{red}{A} & A & A & A \cr \hline \color{red}{B} & A & B & B \cr \hline \end{array} $ —————————————————

 $ \begin{array}{|c|c|} \hline A & A & \color{red}{A} & A \cr \hline B & A & \color{red}{B} & B \cr \hline \end{array} $

—————————————————

 $ \begin{array}{|c|c|} \hline A & A & A & \color{red}{A} \cr \hline B & A & B & \color{red}{B} \cr \hline \end{array} $

—————————————————

 $ \begin{array}{|c|c|} \hline A & A & A & A \cr \hline \color{red}{B} & \color{red}{A} & B & B \cr \hline \end{array} $

—————————————————

 $ \begin{array}{|c|c|} \hline A & A & A & A \cr \hline B & \color{red}{A} & \color{red}{B} & B \cr \hline \end{array} $

There are a total of $ 5 $ pairs, which satisfies $ k $ .

## 样例 #1

### 输入

```
4
10 1
ABBAAABBAA
4 5
AAAA
9 17
BAAABBAAB
4 9
ABAB```

### 输出

```
NO
YES
BABB
YES
ABABAABAB
NO```

# 题解

## 作者：Schi2oid (赞：7)

考虑一个朴素 dp，设 $f_{i,0/1}$ 表示考虑到前 $i$ 位，且第 $i$ 位填入 A/B 可能的相邻不同对数构成的集合，朴素转移时间复杂度 $O(n^2)$。试分析 dp 性质，观察发现所有 dp 中得到的集合为区间内抠去至多一个点，下面给出证明。

我们首先来观察转移过程是怎样的。第一种是第二行中 $i-1$ 填入的字母与第一行中 $i$ 填入的字母相同的情况，此时根据我们填入的字母与其相同与否，集合会整体平移 $0$ 或 $2$；第二种是不同的情况，此时无论我们如何填入字母，集合都会整体平移 $1$。由于我们只关心集合的相对位置关系，我们可以将转移视为将 $f_{i-1,0/1}$ 固定不动，将 $f_{i-1,1/0}$ 平移 $1$ 以及 $-1$，分别进行取或操作，得到 $f_{i}$。

首先容易发现，$f_i$ 的两个集合两侧端点的差的绝对值分别不超过 $2$。这是由于这两个集合是由一个固定的集合或上另外一个集合平移 $1/-1$ 得到的。现在，我们可以归纳说明一个更强的结论：$f_i$ 的两个集合中至多存在一个集合中存在且恰存在一个空位。

显然 $1$ 满足条件。假设 $i-1$ 满足此条件。由于区间过小时的情况比较神秘，我们在此只讨论 $r-l+1\ge5$ 的情况。对于区间更小的情况打表可证。在这种情况下，最坏是 $f_{i-1,x}$ 为 $[l,r]$ 抠去 $p(p\in(l,r))$，$f_{i-1,1-x}$ 为 $[l+2,r-2]$。此时，若 $i$ 不满足此条件，则存在一个 $p$ 使得 $[l+2,r-2]$ 无论平移 $1$ 还是 $-1$ 都无法覆盖到，而这显然无解。

故证毕。证得比原结论更强的结论，故原结论也证毕。

时间复杂度 $O(n)$。



---

## 作者：Otomachi_Una_ (赞：4)

**【题目简述】**

对一个 $2\times n$ 的表格，第一行已经填入 $\tt 01$，你需要填入第二行使得相邻不同的方格对数量为 $k$。

$n\leq 2\times 10^5$。

**【解题思路】**

考虑直接 dfs，那么我们只需要快速判断填入一个前缀之后能不能填完剩余的后缀使其合法。

有个简单的判断方式，我们算出每个后缀经过合理填数之后能获得的最大/最小相邻不同字符对数量（这里可以 dp），我们只需要判断我们对剩余的目标是否在这个区间当中即可。

这样便对吗？很显然有点小问题，但是显然问题很小，我们只需要在发现当前矛盾时候回撤就行。

**【参考代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN=2e5+5;
int n,k,cnt;bool flag;int f[MAXN][2],g[MAXN][2];// 最大，最小
char c[2][MAXN];
void dfs(int u,char ch,int gl){
	if(flag||cnt>=100*n||gl>f[u][ch-'A']||gl<g[u][ch-'A']) return;
	gl-=((c[1][u]=ch)!=c[0][u]);cnt++;
	// for(int i=1;i<=n;i++) cout<<c[1][i];cout<<'\n';
	if(u==1&&gl==0){
		cout<<"YES\n";
		flag=true;
		for(int i=1;i<=n;i++) cout<<c[1][i];cout<<'\n';
		return;
	}
	for(char o:{'A','B'}) dfs(u-1,o,gl-(o!=ch));
}
void solve(){
	cin>>n>>k>>(c[0]+1);
	f[1][0]=g[1][0]=(c[0][1]=='B');
	f[1][1]=g[1][1]=(c[0][1]=='A');
	for(int i=2;i<=n;i++){
		f[i][0]=max(f[i-1][0],f[i-1][1]+1)+(c[0][i]!='A');
		f[i][1]=max(f[i-1][0]+1,f[i-1][1])+(c[0][i]!='B');
		g[i][0]=min(g[i-1][0],g[i-1][1]+1)+(c[0][i]!='A');
		g[i][1]=min(g[i-1][0]+1,g[i-1][1])+(c[0][i]!='B');
	}
	for(int i=1;i<n;i++) k-=(c[0][i]!=c[0][i+1]);
	flag=false;cnt=0;
	dfs(n,'A',k);dfs(n,'B',k);
	if(!flag) cout<<"NO\n";
}
int main(){
	ios::sync_with_stdio(false);
	// freopen("Otomachi_Una.in","r",stdin);
	// freopen("Otomachi_Una.out","w",stdout);
	int _;cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：ducati (赞：4)

## Description

[传送门](https://www.luogu.com.cn/problem/CF1852D)

## Solution

晚上脑子很混乱，结果 VP 的时候在**赛后十秒**过了这题，被创死了。

考虑 dp，令 $f_{i,c,j}$ 表示，填了第二行的前 $i$ 个位置，$i$ 处的字符是 `A` / `B`，填有不同字符的相邻位置是否能有 $j$ 对。转移是平凡的，时间复杂度 $O(n^2)$ 或 $O(\frac {n^2} {w})$。

打个表，发现 $\forall i \in [1,n], c \in \{0,1\}$，满足 $f_{i,c,0},f_{i,c,1},\cdots$ 构成的 $01$ 串中，所有 $1$ 几乎构成一个连续段，中间缺至多一个位置（比如 $000101110$），那么三元组 $(p,l,r)$ 即可表示一个状态。其中 $p$ 表示缺的位置（特别的，若不缺则 $p = -1$），$[l,r]$ 表示最左 / 最右侧 $1$ 的位置。

转移需要分讨四种情况，时间复杂度线性。

## Code（正解）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;

int read(){
	int s=0,w=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if(ch=='-')w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9') {s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int n,k,a[N],b[N]; char s[N];
struct node{
	int p,l,r;
	inline bool Contain(int x) const{return l<=x&&x<=r&&x!=p;}
	inline node Shift(int d) const{return node{((~p)?(p+d):-1),l+d,r+d};}
	inline node operator + (const node &A) const{
		int L=min(l,A.l),R=max(r,A.r);
		if (L<=p&&p<=R&&!A.Contain(p))  return node{p,L,R};
		if (L<=A.p&&A.p<=R&&!Contain(A.p))  return node{A.p,L,R};
		if (r+2==A.l)  return node{r+1,L,R};
		if (A.r+2==l)  return node{A.r+1,L,R};
		return node{-1,L,R};
	};
}f[N][2];
bool solve(){
	n=read(),k=read(),scanf("%s",s+1);
	for (int i=1;i<=n;i++)  a[i]=(s[i]=='B');
	for (int i=1;i<n;i++){
		if (a[i]^a[i+1])  k--;
	}
	if (k<0)  return false;

	f[1][0]=node{-1,0,0},f[1][1]=node{-1,1,1};
	for (int i=2;i<=n;i++){
		if (a[i-1]==a[i]){
			f[i][0]=f[i-1][1].Shift(1)+f[i-1][0];
			f[i][1]=f[i-1][0].Shift(2)+f[i-1][1].Shift(1);
		}
		else{
			f[i][0]=f[i-1][0].Shift(1)+f[i-1][1];
			f[i][1]=f[i-1][1].Shift(2)+f[i-1][0].Shift(1);
		}
	}
	int t=-1,p=k;
	if (f[n][0].Contain(k))  t=0;
	else if (f[n][1].Contain(k))  t=1;
	else return false;
	for (int i=n;i;i--){
		b[i]=(a[i]^t);
		if (i==1)  break;
		if (a[i-1]==a[i]){
			if (!t){
				if (f[i-1][1].Contain(p-1))  p--,t=1;
			}
			else{
				if (f[i-1][0].Contain(p-2))  p-=2,t=0;
				else p--;
			}
		}
		else{
			if (!t){
				if (f[i-1][0].Contain(p-1))  p--;
				else t=1;
			}
			else{
				if (f[i-1][1].Contain(p-2))  p-=2;
				else p--,t=0;
			}
		}
	}
	puts("YES");
	for (int i=1;i<=n;i++)  putchar(b[i]?'B':'A');
	return puts(""),true;
}
signed main(){
	int T=read();
	while (T--){
		if (!solve())  puts("NO");
	}
	return 0;
}
```

## Code（打表程序）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1005;

int read(){
	int s=0,w=1; char ch=getchar();
	while (ch<'0'||ch>'9') {if(ch=='-')w=-w;ch=getchar();}
	while (ch>='0'&&ch<='9') {s=(s<<1)+(s<<3)+(ch^'0');ch=getchar();}
	return s*w;
}
int n,k,a[N],b[N]; bitset<N> f[N][2]; char s[N];
bool solve(){
	n=read(),k=read(),scanf("%s",s+1);
	for (int i=1;i<=n;i++)  a[i]=(s[i]=='B');
	for (int i=1;i<n;i++){
		if (a[i]^a[i+1])  k--;
	}
	if (k<0)  return false;

	f[1][0].set(0),f[1][1].set(1);
	for (int i=2;i<=n;i++){
		if (a[i-1]==a[i]){
			f[i][0]=(f[i-1][1]<<1)|f[i-1][0];
			f[i][1]=(f[i-1][0]<<2)|(f[i-1][1]<<1);
		}
		else{
			f[i][0]=(f[i-1][0]<<1)|f[i-1][1];
			f[i][1]=(f[i-1][0]<<1)|(f[i-1][1]<<2);
		}
		for (int d=0;d<=(n<<1);d++)  cout<<f[i][0][d]; cout<<endl;
		for (int d=0;d<=(n<<1);d++)  cout<<f[i][1][d]; cout<<endl;
		cout<<endl;
	}
	return true;
}
signed main(){
	int T=read();
	while (T--){
		if (!solve())  puts("NO");
	}
	return 0;
}
```



---

## 作者：R_shuffle (赞：1)

可以先考虑暴力做法，然后就可以做到 $2^n$。

接着再考虑 dp 做法，不妨设 $f_{i,j,0/1}$ 表示填字母到 $i$ 的位置，已经有了 $j$ 分，上一个位置填的是 $A/B$，是否可行。然后就可以得到一个 $n^2$ 的做法。

然后发现实际上 dp 做法的很多状态是没有用的，可以考虑记忆化一下，但是实际上还是可以卡到 $n^2$ 的。

所以不妨考虑把暴力和 dp 结合一下，用 dp 优化暴力。

具体的，考虑可行性剪枝，由于一个位置的贡献只与周围的三个位置有关，所以实际上可以参考类似 meet in the middle 的东西，以一个位置把前后分开，暴力搜索前面的位置，然后用 dp 来求出后面的位置的答案的范围，显然超过范围了就是不可行的。所以就可以做到大幅度的剪枝，我不会证明复杂度，但是复杂度应该是与填的方案数有关，大概就是填的方案数这个级别的，然后由于我们找到一个解就会跳，所以不难感性理解出复杂度是 $O(n)$ 级别的。

---

## 作者：happybob (赞：0)

不妨假设我们要求字典序最小的符合条件的构造。

一个想法是每次能填 A 就填 A，不然填 B。用 DP 记录一段后缀所有能取到的结果。复杂度 $O(n^2)$。

一个猜测是如果后缀能取到的最小值是 $l$，最大值是 $r$，那么 $[l,r]$ 都能取到。但是很遗憾这个是假的，考虑第一行为 AAA，对第二行构造，至少结果为 $0$，至多为 $4$。但是无论如何 $1$ 都构造不出来。

于是猜测另一个结论，对于 $[l,r]$ 来说，只有 $l+1$ 和 $r-1$ 可能取不到。手玩若干个发现很对。然后写一个基于这个结论的 DP 就可以通过此题。复杂度线性。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=2e5+5;

int t,n,k;
string s;
set<int> st[N][2];

inline bool check(string t)
{
	int res=0;
	for(int i=1;i<n;i++) res+=(t[i]!=t[i+1]);
	for(int i=1;i<n;i++) res+=(s[i]!=s[i+1])+(s[i]!=t[i]);
	res+=(s[n]!=t[n]);
	return (res==k);
}

int main()
{
	//freopen("fill.in","r",stdin);
	//freopen("fill.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		cin>>s;
		s=" "+s;
		int cnt=0;
		for(int i=1;i<n;i++) cnt+=(s[i]!=s[i+1]);
		if(cnt>k)
		{
			cout<<"NO\n";
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			st[i][0].clear(),st[i][1].clear();
		}
		st[n][0].insert(s[n]!='A');
		st[n][1].insert(s[n]!='B');
		for(int i=n-1;i>=1;i--)
		{
			for(auto&j:st[i+1][0])
			{
				st[i][0].insert(j+(s[i]!=s[i+1])+(s[i]!='A'));
				st[i][1].insert(j+(s[i]!=s[i+1])+1+(s[i]!='B'));
			}
			for(auto&j:st[i+1][1])
			{
				st[i][0].insert(j+(s[i]!=s[i+1])+1+(s[i]!='A'));
				st[i][1].insert(j+(s[i]!=s[i+1])+(s[i]!='B'));
			}
			set<int> rs=st[i][0],rs2=st[i][1];
			st[i][0].clear(),st[i][1].clear();
			if(rs.size()>=1) st[i][0].insert(*rs.begin()),st[i][0].insert(*rs.rbegin());
			if(rs.size()>=2) st[i][0].insert(*(next(rs.begin()))),st[i][0].insert(*(prev(prev(rs.end()))));
			if(rs2.size()>=1) st[i][1].insert(*rs2.begin()),st[i][1].insert(*rs2.rbegin());
			if(rs2.size()>=2) st[i][1].insert(*(next(rs2.begin()))),st[i][1].insert(*(prev(prev(rs2.end()))));
		}
		int x=0;
		string ans=" ";
		for(int i=1;i<n;i++)
		{
			if(i>1) x+=(s[i]!=s[i-1])+(ans[i-1]!=s[i-1]);
			if(i>2) x+=(ans[i-1]!=ans[i-2]);
			int nv=k-x-(i==1?0:(ans[i-1]=='B'));
			// check if can be a
			int l=*st[i][0].begin(),r=*st[i][0].rbegin();
			if((nv>l+1&&nv<r-1)||(st[i][0].count(nv)))
			{
				ans+="A";
			}
			else ans+="B";
		}
		if(check(ans+"A")) 
		{
			cout<<"YES\n";
			string res=ans+"A";
			cout<<res.substr(1)<<"\n";
		}
		else if(check(ans+"B"))
		{
			cout<<"YES\n";
			string res=ans+"B";
			cout<<res.substr(1)<<"\n";
		}
		else cout<<"NO\n";
	}
	return 0;
}
```

---

