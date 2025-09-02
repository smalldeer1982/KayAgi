# Fafa and Ancient Mathematics

## 题目描述

Ancient Egyptians are known to have understood difficult concepts in mathematics. The ancient Egyptian mathematician Ahmes liked to write a kind of arithmetic expressions on papyrus paper which he called as Ahmes arithmetic expression.

An Ahmes arithmetic expression can be defined as:

- " $ d $ " is an Ahmes arithmetic expression, where $ d $ is a one-digit positive integer;
- " $ (E_{1}opE_{2}) $ " is an Ahmes arithmetic expression, where $ E_{1} $ and $ E_{2} $ are valid Ahmes arithmetic expressions (without spaces) and $ op $ is either plus $ (+) $ or minus $ (-) $ .

 For example 5, (1-1) and ((1+(2-3))-5) are valid Ahmes arithmetic expressions.On his trip to Egypt, Fafa found a piece of papyrus paper having one of these Ahmes arithmetic expressions written on it. Being very ancient, the papyrus piece was very worn out. As a result, all the operators were erased, keeping only the numbers and the brackets. Since Fafa loves mathematics, he decided to challenge himself with the following task:

Given the number of plus and minus operators in the original expression, find out the maximum possible value for the expression on the papyrus paper after putting the plus and minus operators in the place of the original erased operators.

## 说明/提示

- The first sample will be $ (1+1)=2 $ .
- The second sample will be $ (2+(1-2))=1 $ .
- The third sample will be $ ((1-(5-7))+((6+2)+7))=18 $ .
- The fourth sample will be $ ((1+(5+7))-((6-2)-7))=16 $ .

## 样例 #1

### 输入

```
(1?1)
1 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
(2?(1?2))
1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
((1?(5?7))?((6?2)?7))
3 2
```

### 输出

```
18
```

## 样例 #4

### 输入

```
((1?(5?7))?((6?2)?7))
2 3
```

### 输出

```
16
```

# 题解

## 作者：2huk (赞：1)

- 给出一个算式，由括号和小于 $10$ 的正整数和问号组成。每个问号可以改为加号或减号。

  求如果总共填 $p$ 个加号和 $m$ 个减号，求算式的最大值。

- $n \le 10^4$，$\min(p, m) \le 100$。

---

建表达式树。如 $((1 + 2) - ((3 - 4) + 5))$：

![](https://cdn.luogu.com.cn/upload/image_hosting/64a9ufvc.png)

然后设 DP 状态 $f_{u, k}$ 和 $g_{u, k}$ 分别表示以 $u$ 为根的子树中，如果用 $k$ 个加号/减号，代数式的最大值是多少。具体是加号/减号可以看 $p, m$ 谁更小，因为题目保证 $\min(p, m) \le 100$ 所以这样设状态是可行的。

转移时枚举 $u$ 选择加号/减号，左子树用了几个加号/减号，那么右子树的加号/减号数量是可以被计算的。然后转移即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 20010;

char s[N];
int n, a, b;

struct Tree {
	int l, r, v;
}tr[N];

int idx;
int l[N], r[N];

long long f[N][110], g[N][110];
// f[u][k] 在以 u 为根的子树，用了 k 个加号，代数式最大值 
// g[u][k] 在以 u 为根的子树，用了 k 个加号，代数式最小值
map<int, vector<int> > pos; 
int sum[N];
int que[N];

inline int build(const int ll, const int rr) {
	const int u = ++ idx;
	tr[u] = {ll, rr};
	
	if (ll == rr) f[u][0] = g[u][0] = s[ll] - '0';
	else {
		register int x = *lower_bound(pos[sum[ll - 1] + 1].begin(), pos[sum[ll - 1] + 1].end(), ll);
		tr[u].v = que[rr] - que[ll - 1];
		l[u] = build(ll + 1, x - 1);
		r[u] = build(x + 1, rr - 1);
	}
	
	return u;
}

inline void dfsa(const int u) {
	if (tr[u].l == tr[u].r) return;
	
	dfsa(l[u]), dfsa(r[u]);
	for (register int i = 0; i <= tr[u].v; ++ i )
		for (register int j = 0; j <= tr[l[u]].v; ++ j ) {
			if (i - j - 1 <= tr[r[u]].v && i - j - 1 >= 0)
				f[u][i] = max(f[u][i], f[l[u]][j] + f[r[u]][i - j - 1]),
				g[u][i] = min(g[u][i], g[l[u]][j] + g[r[u]][i - j - 1]);
			
			if (i - j <= tr[r[u]].v && i - j >= 0)
				f[u][i] = max(f[u][i], f[l[u]][j] - g[r[u]][i - j]),
				g[u][i] = min(g[u][i], g[l[u]][j] - f[r[u]][i - j]);
		}
	
	return;
}

inline void dfsb(const int u) {
	if (tr[u].l == tr[u].r) return;
	
	dfsb(l[u]), dfsb(r[u]);
	for (register int i = 0; i <= tr[u].v; ++ i )
		for (register int j = 0; j <= tr[l[u]].v; ++ j ) {
			if (i - j - 1 <= tr[r[u]].v && i - j - 1 >= 0)
				f[u][i] = max(f[u][i], f[l[u]][j] - g[r[u]][i - j - 1]),
				g[u][i] = min(g[u][i], g[l[u]][j] - f[r[u]][i - j - 1]);
			
			if (i - j <= tr[r[u]].v && i - j >= 0)
				f[u][i] = max(f[u][i], f[l[u]][j] + f[r[u]][i - j]),
				g[u][i] = min(g[u][i], g[l[u]][j] + g[r[u]][i - j]);
		}
	
	return;
}

signed main() {
	memset(f, -0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	scanf("%s%d%d", s + 1, &a, &b);
	n = strlen(s + 1);
	
	pos[0].push_back(0); 
	for (int i = 1; i <= n; ++ i ) {
		sum[i] = sum[i - 1];
		sum[i] += s[i] == '(';
		sum[i] -= s[i] == ')';
		if (s[i] == '?') pos[sum[i]].push_back(i);
		que[i] = que[i - 1] + (s[i] == '?');
	}
	
	build(1, n);
	if (a <= b) {
		dfsa(1);
		printf("%lld\n", f[1][a]);
	}
	else {
		dfsb(1);
		printf("%lld\n", f[1][b]);
	}
	
	return 0;
}
```

---

## 作者：Chen_Johnny (赞：0)

# CF935E Fafa and Ancient Mathematics
## 题意理解和转化
先说一下这道题的意思，很多人可能都不理解：

给定一个式子，其中有很多加减号不知道是加还是减。

那么，这道题我们发现只有加减号，所以不需要考虑任何计算顺序，所以可以使用一棵小学的运算数来表示。

例如，$[(2 + 2) - 1]$ 可以表示为：

![](https://cdn.luogu.com.cn/upload/image_hosting/6luk2wa3.png?x-oss-process=image/resize,m_lfit,h_500,w_1225)

当然，这道题目中没有加减号，我们只能用“?”代替加减号。
## 题目的思路
这道题已经被我们转化为了一课树，而某些节点不知道单只有两种取法。那我们很容易想起树形 DP。

于是，我们开始设计状态：

$dp_{i,j,k,m}$ 代表第 $i$ 个点，已经用了 $j$ 个加号，$k$ 个减号，最多可以得到的最大值或最小值（$m = 0$ 是最大值，$m = 1$ 是最小值）。

但是，显然这个空间复杂度是不足够的，我们再次回到题目，注意到关于加号减号的事情中：$0\leqslant \min(P,M) \leqslant100$。

因为这道题只有两个状态，如果不是这个状态，就是另一个。因此，我们可以只记录一个状态，另外一个随它去，当然是选择记录小的那个就符合复杂度了。

## 总结
说了上面一堆，我们总结一下：

  1. 用树形 DP 来做。
  2. 先枚举左右子树。
  3. 循环加号和减号的数量进行最大值与最小值的计算。
## 代码

```cpp
#include <bits/stdc++.h>
#define ls son [v] [0]
#define rs son [v] [1]
#define smaller i + j + (add < sub)
#define bigger i + j + (add >= sub)
using namespace std;
const int M = 1e4 + 5;
int add, sub, len, minn, tot = 1, pre = 1;
int son [M] [2] , dad [M], dp [M] [105] [2];
char ch[M];
void build () {
    len = strlen (ch + 1); minn = min (add, sub);
    for (int i = 1; i < M; i ++)
        for (int j = 0; j <= minn; j ++) {
            dp [i] [j] [0] = -1e9;
            dp [i] [j] [1] = 1e9;
        }
    for (int i = 1; i <= len; i ++)
        if (ch [i] == '(' || ch [i] == '?') {
            son [pre] [son [pre] [0] ? 1 : 0] = ++ tot;
            dad [tot] = pre; pre = tot;
        } else if (ch [i] == ')') pre = dad [pre];
        else {
            dp [tot] [0] [0] = dp [tot] [0] [1] = ch [i] - '0'; 
            pre = dad [pre];
        }
}
void dfs (int v) {
    if (!ls) return;
    dfs (ls); dfs (rs);
    for (int i = 0; i <= minn; i ++)
        for (int j = 0; i + j <= minn; j ++) {
            dp [v] [smaller] [0] = max(dp [v] [smaller] [0], dp [ls] [i] [0] + dp [rs] [j] [0]);
            dp [v] [bigger] [0] = max (dp [v] [bigger] [0], dp [ls] [i] [0] - dp [rs] [j] [1]);
            dp [v] [smaller] [1] = min (dp [v] [smaller] [1], dp [ls] [i] [1] + dp [rs] [j] [1]);
            dp [v] [bigger] [1] = min (dp [v] [bigger] [1], dp [ls] [i] [1] - dp [rs] [j] [0]);
        }
}
int main () {
    scanf ("%s %d %d", ch + 1, &add, &sub);
    build (); dfs (1);
    printf ("%d", dp [1] [minn] [0]);
}
```

---

## 作者：鲤鱼江 (赞：0)

不知为啥跑得比较快。

这个经典的形式几乎是明示表达树上 DP，我们来考虑需要存哪些东西。

首先你把加号和减号都存下来肯定是死路一条，但是如果你知道有多少个加号，那么减号有多少个你肯定也是知道的，所以只用存其中一个。发现数据范围是很烦的 $\min(P,M)$，而空间又只给了 $250MB$ 所以你肯定只能哪个小存哪个。

状态有了，具体的 DP 就很好想了，设 $dp_{i,j,0/1}$ 表示 $i$ 子树内填 $j$ 个加（或减）号，能得到的最大（最小）值。到时候直接 DP 转移，边界情况要处理好。

至于表达式树的建法，你可以选择先把无意义括号过滤，再每一次从左边扣下一个表达式作为左儿子，剩下的作为右儿子递归下去，可以发现只有叶子节点是数字，具体见代码。

代码有点长，复制粘贴导致的。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Fread {
	const int SIZE=1<<21;char buf[SIZE],*S,*T;
	inline char getchar() {if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return '\n';}return *S++;}
}
namespace Fwrite {
	const int SIZE=1<<21;
	char buf[SIZE],*S=buf,*T=buf+SIZE;
	inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}
	inline void putchar(char c){*S++=c;if(S==T)flush();}
	struct POPOSSIBLE{~POPOSSIBLE(){flush();}}ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio{
	struct Reader{
	    template<typename T>
    	Reader& operator >> (T& x) {
        	char c=getchar();T f=1;
        	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;
        	while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;
	        return *this;
    	}
	    Reader& operator >> (char& c) {c=getchar();while(c==' '||c=='\n')c=getchar();return *this;}
	    Reader& operator >> (char* str) {
	        int len=0;
	        char c=getchar();
	        while(c==' '||c=='\n')c=getchar();
	        while(c!=' '&&c!='\n'&&c!='\r'){str[len++]=c;c=getchar();}
			str[len]='\0';return *this;
	    }
	    Reader(){}
	}cin;
	struct Writer{
	    template<typename T>
	    Writer& operator << (T x) {
	        if(x==0){putchar('0');return *this;}
	        if(x<0){putchar('-');x=-x;}
	        static int sta[45];int top=0;
	        while(x){sta[++top]=x%10;x/=10;}
	        while(top){putchar(sta[top]+'0');--top;}
	        return *this;
    	}
    	Writer& operator << (char c) {putchar(c);return *this;}
    	Writer(){}
	}cout;
}
#define endl '\n'
//#define cin Fastio :: cin
//#define cout Fastio :: cout

/*
	考虑表达式树上DP
	暴力做 O(nk)。（k为加号个数） 
	手段是：每次拿出一个表达式，打为左儿子 ，把右儿子递归下去。
	到时候 dp[i][j][0/1]:表示i子树内用j次加/减法得最大（最小值）。
	记得过滤左右的括号，最开始需要先跑一遍括号匹配。
	有点细节，自己胡的。 
*/

const int N=10010;
const int Max=210;
int dp[N][Max][2],n,to[N],X,Y,top,stk[N],tot,ls[N],rs[N],val[N],siz[N],op;
char a[N];

int build(int l,int r){
	int now=++tot;
	while(to[l]==r) ++l,--r;
	if(l==r) {
		val[now]=(a[l]-'0');
		dp[now][0][0]=dp[now][0][1]=val[now];
	}else {
		if(to[l]){
			if(a[to[l]+1]!='?') exit(1);
			ls[now]=build(l+1,to[l]-1);
			rs[now]=build(to[l]+2,r);
		}else {
			if(a[l+1]!='?') exit(2);
			ls[now]=build(l,l);
			rs[now]=build(l+2,r);
		}
	}
	return now;
}

void DP(int x){
	if(!ls[x]) return ;
	DP(ls[x]);DP(rs[x]);
	siz[x]=1;siz[x]+=siz[ls[x]]+siz[rs[x]];
	for(int i=0;i<=min(siz[ls[x]],X);++i){
		for(int j=0;j<=min(X-i,siz[rs[x]]);++j){
			if(dp[ls[x]][i][1]!=-1e9){
				if(i+j<X&&dp[rs[x]][j][1]!=-1e9) dp[x][i+j+1][1]=max(dp[x][i+j+1][1],dp[ls[x]][i][1]+dp[rs[x]][j][1]);
				if(dp[rs[x]][j][0]!=1e9) dp[x][i+j][1]=max(dp[x][i+j][1],dp[ls[x]][i][1]-dp[rs[x]][j][0]);
			}
			if(dp[ls[x]][i][0]!=1e9){
				if(i+j<X&&dp[rs[x]][j][0]!=1e9) dp[x][i+j+1][0]=min(dp[x][i+j+1][0],dp[ls[x]][i][0]+dp[rs[x]][j][0]);
				if(dp[rs[x]][j][1]!=-1e9) dp[x][i+j][0]=min(dp[x][i+j][0],dp[ls[x]][i][0]-dp[rs[x]][j][1]);
			}
		}
	}
}

void DP2(int x){
	if(!ls[x]) return ;
	DP2(ls[x]);DP2(rs[x]);
	siz[x]=1;siz[x]+=siz[ls[x]]+siz[rs[x]];
	for(int i=0;i<=min(siz[ls[x]],Y);++i){
		for(int j=0;j<=min(Y-i,siz[rs[x]]);++j){
			if(dp[ls[x]][i][1]!=-1e9){
				if(i+j<Y&&dp[rs[x]][j][0]!=1e9) dp[x][i+j+1][1]=max(dp[x][i+j+1][1],dp[ls[x]][i][1]-dp[rs[x]][j][0]);
				if(dp[rs[x]][j][1]!=-1e9) dp[x][i+j][1]=max(dp[x][i+j][1],dp[ls[x]][i][1]+dp[rs[x]][j][1]);
			}
			if(dp[ls[x]][i][0]!=1e9){
				if(i+j<Y&&dp[rs[x]][j][1]!=-1e9) dp[x][i+j+1][0]=min(dp[x][i+j+1][0],dp[ls[x]][i][0]-dp[rs[x]][j][1]);
				if(dp[rs[x]][j][0]!=1e9) dp[x][i+j][0]=min(dp[x][i+j][0],dp[ls[x]][i][0]+dp[rs[x]][j][0]);
			}
		}
	}
}

int main(){
	cin>>a>>X>>Y;n=strlen(a);for(int i=n;i;--i) a[i]=a[i-1];
	for(int i=1;i<=n;++i){
		if(top&&a[stk[top]]=='('&&a[i]==')') to[stk[top--]]=i;
		else if(a[i]=='('||a[i]==')') stk[++top]=i;
	}
	if(X<Y){
		for(int i=1;i<=n;++i) for(int j=0;j<=X;++j) dp[i][j][0]=1e9,dp[i][j][1]=-1e9;
		build(1,n);DP(1);cout<<dp[1][X][1]<<endl;
	}else {
		for(int i=1;i<=n;++i) for(int j=0;j<=Y;++j) dp[i][j][0]=1e9,dp[i][j][1]=-1e9;
		build(1,n);DP2(1);cout<<dp[1][Y][1]<<endl;		
	}
	return 0;
}
```

---

## 作者：Provicy (赞：0)

前言：~~发现最近越来越看不懂 cf 评分了~~

$\text{Problem}$：[题目链接](https://codeforces.com/problemset/problem/935/E)

$\text{Solution}$：

此题难点其实在于建树。

直接建立表达式树即可。具体的方法是，对于某个 $?$，将它的左边以 $($ 和 $number$ 的情况分别讨论，右边也同理。注意到最右边的右括号需要特判后跳出，否则将会建一个根节点的右端点的编号等于本身的树，导致死循环。建成的二叉树具有良好的性质：所有的叶子节点上都有一个值；所有的非叶子节点上都是一个 $?$；对于每一个非叶子结点，它的贡献只由它的左子树和右子树的贡献转移而来。

考虑在这棵二叉树上 $dp$。发现 $min\{P,M\}$ 非常小，考虑对于 $P<M$ 和 $M\leq P$ 的情况分开讨论，此处以 $P<M$ 为例，设 $F_{x,i}$ 表示编号为 $x$ 的节点选了 $i$ 个 $+$ 号时的最大贡献，$G_{x,i}$ 表示编号为 $x$ 的节点选了 $i$ 个 $+$ 号时的最小贡献，则易得（记 $lc,rc$ 分别为 $x$ 的左孩子，右孩子）：

$$F_{x,i}=max\{F_{lc,j}+F_{rc,i-j-1},F_{lc,k}-G_{rc,i-k}\}$$

$$G_{x,i}=min\{G_{lc,j}+G_{rc,i-j-1},G_{lc,k}-F_{rc,i-k}\}$$

边界条件即 $j,k$ 取值范围根据定义可以得出。最后的答案为 $F_{root,P}$。

对于 $M\leq P$ 的情况同理。时间复杂度为 $O(n\times min(P,M)^{2})$，可过。

$\text{Code}$：

```cpp
//hoho! xtwakioi! xtwddYnoi(双重含义)!
#include <bits/stdc++.h>
#define ri register
//#define int long long
#define E (100001)
#define mk make_pair
using namespace std; const int N=10010, M=105;
inline int read()
{
    int s=0, w=1; ri char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
    return s*w;
}
int Len,cnt,root,now=1,ch[N][2],a[N],res=-2e9;
char s[N];
int F[N][M],G[N][M],p,m;
int Get();
int DFS();
int Get()
{
    int x=cnt;
    if(isdigit(s[now]))
    {
        int ans=0;
        for(;isdigit(s[now]);now++) ans=ans*10+s[now]-'0';
        a[++cnt]=ans, x=cnt;
    }
    else if(s[now]=='(') now++, x=DFS(), now++;
    return x;
}
int DFS()
{
    int L=Get();
    if(now>Len)
    {
        return L;
    }
    int x=++cnt;
    now++;
    ch[x][0]=L, ch[x][1]=Get();
    return x;
}
void Poit(int x)
{
    if(!x) return;
    if(!ch[x][0] && !ch[x][1])
    {
        F[x][0]=G[x][0]=a[x];
        return;
    }
    Poit(ch[x][0]), Poit(ch[x][1]);
    for(ri int i=0;i<=p;i++)
    {
        if(i)
        {
            for(ri int j=0;j<i;j++)
            F[x][i]=max(F[x][i],F[ch[x][0]][j]+F[ch[x][1]][i-1-j]),
            G[x][i]=min(G[x][i],G[ch[x][0]][j]+G[ch[x][1]][i-1-j]);
        }
        for(ri int j=0;j<=i;j++)
        F[x][i]=max(F[x][i],F[ch[x][0]][j]-G[ch[x][1]][i-j]),
        G[x][i]=min(G[x][i],G[ch[x][0]][j]-F[ch[x][1]][i-j]);
    }
}
void Moit(int x)
{
    if(!x) return;
    if(!ch[x][0] && !ch[x][1])
    {
        F[x][0]=G[x][0]=a[x];
        return;
    }
    Moit(ch[x][0]), Moit(ch[x][1]);
    for(ri int i=0;i<=m;i++)
    {
        if(i)
        {
            for(ri int j=0;j<i;j++)
            F[x][i]=max(F[x][i],F[ch[x][0]][j]-G[ch[x][1]][i-j-1]),
            G[x][i]=min(G[x][i],G[ch[x][0]][j]-F[ch[x][1]][i-j-1]);
        }
        for(ri int j=0;j<=i;j++)
        F[x][i]=max(F[x][i],F[ch[x][0]][j]+F[ch[x][1]][i-j]),
        G[x][i]=min(G[x][i],G[ch[x][0]][j]+G[ch[x][1]][i-j]);
    }
}
signed main()
{
    scanf("%s",s+1);
    Len=strlen(s+1);
    root=DFS();
    p=read(), m=read();
    memset(F,-0x3f,sizeof(F)), memset(G,0x3f,sizeof(G));
    if(p<m) Poit(root), res=F[root][p];
    else Moit(root), res=F[root][m];
    printf("%d\n",res);
    return 0;
}
```


---

