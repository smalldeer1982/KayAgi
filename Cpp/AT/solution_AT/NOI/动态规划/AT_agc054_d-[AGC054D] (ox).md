# [AGC054D] (ox)

## 题目描述

给定一个由 `(`、`)`、`o`、`x` 组成的字符串 $S$。你可以任意次数地交换 $S$ 中相邻的两个字符。请你求出，为了满足下述条件，所需的最小操作次数。

- 将 $S$ 中出现的每个 `o` 替换为 `()`，每个 `x` 替换为 `)(`，从而得到仅由 `(` 和 `)` 组成的新字符串 $S'$。此时，$S'$ 必须是**括号匹配的字符串**。

括号匹配的字符串定义如下：

- 空字符串；
- 存在括号匹配的非空字符串 $s$、$t$，将 $s$ 和 $t$ 按此顺序连接得到的字符串；
- 存在括号匹配的字符串 $s$，将 `(`、$s$、`)` 按此顺序连接得到的字符串。

此外，根据本题的限制条件，目标一定可以实现。

## 说明/提示

### 限制

- $S$ 仅由 `(`、`)`、`o`、`x` 组成。
- $S$ 至少包含一个 `(` 和一个 `)`，且它们的数量相等。
- $|S| \leq 8000$

### 样例解释 1

`)x(` → `x)(` → `x()` → `(x)`，这样操作即可。此时 $S' = ()()`，它是一个括号匹配的字符串。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
)x(```

### 输出

```
3```

## 样例 #2

### 输入

```
()ox```

### 输出

```
2```

## 样例 #3

### 输入

```
()oxo(xxx))))oox((oooxxoxo)oxo)ooo(xxx(oox(x)(x()x```

### 输出

```
68```

# 题解

## 作者：star_field (赞：11)

## 思路
对于 `o`，因为要替换为 `()`，不会对结果造成影响，这样可以将 `o` 看做占位符。对于 `x`，它必须放在 `(` 的右边，因为它要变成 `)(`。这样我们可以记录下 `(`，`)` 和 `o`，`x` 的位置，然后首先开一个前缀和数组 $pre$，$pre_i$ 表示从 $1$ 到 $i$ 的序列是否合法。如果 $s_i=$`(` 则 $pre_i=pre_{i-1}+1$，如果 $s_i=$`)` 则 $pre_i=pre_{i-1}-1$。如果 $pre_i<0$，证明 `)` 多了，这时把右边最近的 `(` 提过来，这一部分的步数设为 $ans_1$。然后我们处理 `o` 和 `x`，这一部分可以用二维 $dp$，$dp_{i,j}$ 表示处理完前 $i$ 个括号和前 $j$ 个 `o` 和 `x` 所需的最小代价。得出最小步数 $ans_2$。最后 $ans_1+ans_2$ 就是最小步数。

整个算法时间复杂度为 $O(n^2)$，可以通过本题。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=8009,INF=0x3f3f3f3f;
int n,cnt1,cnt2,a[N],b[N],pre[N],r1[N],r2[N],ans1,s1[N][N],s2[N][N],dp[N][N];
char s[N];
int main(){
	scanf("%s",s+1); 
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='('||s[i]==')') a[++cnt1]=i;
		else b[++cnt2]=i;
	}
	for(int i=1;i<=cnt1;i++){
		pre[i]=pre[i-1]+(s[a[i]]=='('?1:-1); //前缀和
		if(pre[i]<0){
			for(int j=i+1;j<=cnt1;j++) if(s[a[j]]=='('){
				int t=a[j];
				for(int k=j;k>i;k--) a[k]=a[k-1];
				a[i]=t;
				ans1+=j-i; //把后面的右括号提前
				pre[i]+=2; //成功配对
				break;
			}
		}
	}
	for(int i=1;i<=cnt1;i++) 
		for(int j=1;j<=cnt2;j++){
			s1[i][j]=s1[i][j-1]+(a[i]<b[j]); //统计前 j 个 "o","x" 中有多少个位置在括号 a[i] 之前，用于计算将非括号字符插入到括号后的代价
			s2[i][j]=s2[i-1][j]+(b[j]<a[i]); //统计前 i 个 "o","x" 括号中有多少个位置在非括号字符（o,x） b[j] 之后，用于计算将括号插入到 "o","x" 后的代价
		}
	for(int i=0;i<=cnt1;i++) 
		for(int j=0;j<=cnt2;j++){
			if(!j) 
				continue;
			if(!i) 
				dp[i][j]=INF*(dp[i][j-1]||s[b[j]]=='x');  //不可行情况
			else{
				dp[i][j]=dp[i-1][j]+s1[i][j];
				if(pre[i]>0||s[b[j]]=='o') 
					dp[i][j]=min(dp[i][j],dp[i][j-1]+s2[i][j]); //最小移动
			}
		}
	printf("%d\n",ans1+dp[cnt1][cnt2]);
	return 0;
}

```

---

## 作者：iyaang (赞：4)

[心动的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17455722.html)

[题目链接](https://www.luogu.com.cn/problem/AT_agc054_d)

[Larry76](https://www.luogu.com.cn/user/254315) 牛牛 ![/qq](https://cdn.luogu.com.cn/upload/pic/62224.png)

首先考虑没有 ox 怎么做，就是将括号序列调成合法。$|S|$ 不大直接模拟一遍，记录 $now$ 表示一个前缀权值，当遇到一个 `(` 时 $+1$，遇到一个 `)` 时 $-1$，当 $now < 0$ 的时候说明序列不合法即 `)` 多了，暴力向后找到第一个 `(` 交换到当前的 `)` 前面。这样我们迫不得已时才移动，能够证明得出来的最终括号序列是惟一的。

考虑加入 ox 会造成什么影响。我们先忽略移动 ox 所带来的的影响，假设没有中间间隔的 ox，提出所有的左右括号然后按照上面的方式得到一个合法的括号序列，记这个步数为 rop。注意到我们这样移动即使中间隔着 ox，也不会造成初始 ox 顺序的改变。接下来加入 ox，把先前忽略掉的步数补回来。设 $f_{i,j}$ 表示当前填入了 $i$ 个括号和 $j$ 个 ox，可以发现这个的交换次数贡献为括号和 ox 在原序列上位置的逆序对个数，直接枚举当前填入什么东西。需要特别注意的是记最终括号序列的前缀权值和为 pre，o 可以随意填，但是 x 不能放在两个合法的括号序列之间，即 $pre_i = 0$ 的位置。

于是代码流程变得十分清晰了：先将左右括号和 ox 分别提出来，记录下它们的初始位置和总个数，设有 $n$ 个左右括号和 $m$ 个 ox；然后求纯括号序列的交换次数，并预处理出 pre 数组；最后进行 DP，补偿回算上 ox 的交换次数。最后的答案即为 $f_{n,m} + rop$。时间复杂度是 $\mathcal O(|S|^2)$ 的。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd(x,y))
#define lcm(x,y) (x*y/gcd(x,y))
#define lg(x,y)  (__lg(x,y))
using namespace std;

namespace FastIO
{
	template<typename T=int> inline T read()
	{
	    T s=0,w=1; char c=getchar();
	    while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
	    while(isdigit(c)) s=(s<<1)+(s<<3)+(c^48),c=getchar();
	    return s*w;
	}
	template<typename T> inline void read(T &s)
	{
		s=0; int w=1; char c=getchar();
		while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
	    while(isdigit(c)) s=(s<<1)+(s<<3)+(c^48),c=getchar();
	    s=s*w;
	}
	template<typename T,typename... Args> inline void read(T &x,Args &...args)
	{
		read(x),read(args...);
	}
	template<typename T> inline void write(T x,char ch)
	{
	    if(x<0) x=-x,putchar('-');
	    static char stk[25]; int top=0;
	    do {stk[top++]=x%10+'0',x/=10;} while(x);
	    while(top) putchar(stk[--top]);
	    putchar(ch);
	    return;
	}
}
using namespace FastIO;

namespace MTool
{
    static const int Mod=998244353;
    template<typename T> inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    template<typename T> inline void cmax(T &a,T b) {a=a>b?a:b;}
    template<typename T> inline void cmin(T &a,T b) {a=a<b?a:b;}
    template<typename T> inline void Madd(T &a,T b) {a=a+b>Mod?a+b-Mod:a+b;}
    template<typename T> inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    template<typename T> inline void Mmul(T &a,T b) {a=a*b%Mod;}
    template<typename T> inline void Mmod(T &a)     {a=(a%Mod+Mod)%Mod;}
    template<typename T> inline T    Cadd(T a,T b)  {return a+b>=Mod?a+b-Mod:a+b;}
    template<typename T> inline T    Cdel(T a,T b)  {return a-b<0?a-b+Mod:a-b;}
    template<typename T> inline T    Cmul(T a,T b)  {return a*b%Mod;}
    template<typename T> inline T    Cmod(T a)      {return (a%Mod+Mod)%Mod;}
    inline int qpow(int a,int b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    inline int qmul(int a,int b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    inline int Qpow(int a,int b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;} 
}
using namespace MTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=8010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
	
	char s[MAX];
	int n,a[MAX],num,rop,pre[MAX];
	int bck[MAX],cnt,box[MAX],con;
	int f[MAX][MAX],sub1[MAX],sub2[MAX];
	
    inline void mian()
    {
    	scanf("%s",s+1); n=strlen(s+1);
    	for(int i=1;i<=n;++i) 
	    	if(s[i]=='('||s[i]==')') bck[++cnt]=i,a[cnt]=(s[i]=='(')?1:-1;
	    	else box[++con]=i;
	    for(int now=1;now<=cnt;++now)
	    {
	    	if(a[now]&&!num) 
	    	{
	    		int to=now;
	    		while(a[to]!=1) ++to;
	    		rop+=to-now;
	    		while(to>now) Swp(bck[to],bck[to-1]),Swp(a[to],a[to-1]),--to;
			}
			num+=a[now],pre[now]=num;
		}
		memset(f,0x3f,sizeof f),f[0][0]=0;
		for(int i=0;i<=cnt;++i) for(int j=0;j<=con;++j)
		{
			if(i!=cnt&&j) sub1[i]+=box[j]>bck[i+1];
			if(i!=cnt)    cmin(f[i+1][j],f[i][j]+sub1[i]);
			if(j!=con&&i) sub2[j]+=bck[i]>box[j+1];
			if(j!=con&&(pre[i]>0||s[box[j+1]]=='o')) cmin(f[i][j+1],f[i][j]+sub2[j]);
		}
		write(f[cnt][con]+rop,'\n');
    	return;
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::mian();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：Larry76 (赞：3)

## 前言

更好的阅读体验：[隙间传送](https://www.cnblogs.com/larry76/p/17602444.html)。

因为本人尚菜，所以本篇文章没有什么数学符号，请大家放心食用。

## 题目分析

先吐槽一嘴，这个 `o` 表示 `()`，这个 `x` 表示 `)(`，十分形象。

好，我们先观察原序列，容易得出第一条性质：

> `ox` 的加入不会让我们不合法的序列变合法，相反，它会让我们合法的序列变不合法。

于是可以得出，无论如何，只要我们想要得到合法的序列，我们肯定都要先将去除 `ox` 的括号序列变得合法。

那么惯性的思考下去，也就是我们可以将贡献拆开算，分别是**忽略  `ox` 后的括号序列变合法的最小步数**和 **`ox` 步数的平衡**。

这个时候可能会晕的一点是，为什么可以这么拆，或者说，为什么计算最小步数的时候可以忽略中间的 `ox`。其实，我们并没有忽略掉我们的 `ox`，只不过我们运用了两个视角来计算同一件事请而已，我们先忽略 `ox` 从纯括号中观察得到纯括号序列的移动步数，然后再从 `ox` 的角度观察序列的变化。此时不但得出，对于 `ox` 来说，我们的变化就是原序列经过变换后的逆序对数。

然后最后一步进行 `dp` 就是比较朴素的，设 $dp_{i,j}$ 为已经观察了 $i$ 个括号和 $j$ 个序列后，我们观察出的最小步数。

然后需要特殊考虑一下 `x` 的位置，不难看出，`x` 只能在 `(` 的后面。所以转移的时候需要特判。

## 代码实现

这里只给出了代码的关键部分，其余部分还恳请读者自行实现。

```cpp
char s[MAX_SIZE];
int posb[MAX_SIZE];
int bl[MAX_SIZE];
int posv[MAX_SIZE];
int presum[MAX_SIZE];
int n;
int m;
int k;
int dp[MAX_SIZE][MAX_SIZE];
int t1[MAX_SIZE];
int t2[MAX_SIZE];

void main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i] == '('){
			posb[++m] = i;
			bl[m] = 0;
		} else if(s[i] == ')'){
			posb[++m] = i;
			bl[m] = 1;
		} else {
			posv[++k] = i;
		}
	}
	int now = 0;
	int ans1 = 0;
	for(int i=1;i<=m;i++){
		if(bl[i] && !now){
			int j=i;
			while(bl[j]){
				++j;
			}
			ans1 += j-i;
			while(j>i){
				swap(bl[j],bl[j-1]);
				swap(posb[j],posb[j-1]);
				--j;
			}
		}
		now += (bl[i] ? -1 : 1);
		presum[i] = now;
	}
	memset(dp,0x7f,sizeof(dp));
	dp[0][0] = 0;
	for(int i=0;i<=m;i++){
		for(int j=0;j<=k;j++){
			if(i<m){
				if(j){
					t1[i] += (posv[j] > posb[i+1]);
				}
				dp[i+1][j] = min(dp[i+1][j],dp[i][j] + t1[i]);
			}
			if(j<k){
				if(i){
					t2[j] += (posb[i] > posv[j+1]);
				}
				if(presum[i]>0 || s[posv[j+1]]=='o'){
					dp[i][j+1] = min(dp[i][j+1],dp[i][j] + t2[j]);
				}
			}
		}
	}
	printf("%lld\n",dp[m][k]+ans1);
    return void();
}
```

---

## 作者：konyakest (赞：1)

# [[AGC054D] (ox)](https://www.luogu.com.cn/problem/AT_agc054_d)

## 题意

> 给定一个串 $S$ 包含 ``(, ), o, x``。
>
> 求最小的交换次数使得交换后的串将 ``o`` 替换为 ``()``， ``x`` 替换为 ``)(`` 后，是一个合法括号序列。

## 分析

看到“交换相邻两项的最小交换次数”，可以想到答案为：将原序列排成一个合法的序列，在此意义下的逆序对数。

不难发现，同样的字符会保留相同的顺序（考虑交换的过程，我们花费代价交换两个相同的元素显然不优）。

这样，我们就可以发现最终的序列是：提取出 ``(,),o,x`` 四个序列，按照一定顺序归并得到的序列。

我们此时可以得到该问题的多项式复杂度做法：使用 dp 记录四个序列各自选了多少个，每次加入的时候统计逆序对的变化。

观察数据范围，我们需要 $O(n^2)$ 的算法。

再结合“归并操作有结合律”这个性质，我们可以猜到是要执行三次归并，每次归并两个数组。归并仍然使用上面的 dp 描述。

可以想到，先归并 ``(`` 和 ``)``，``o`` 和 ``x``，最后再进行一次归并得到答案。

我们发现 ``o`` 不会对括号串有任何影响，所以它和任意东西归并都应该保持其原来的顺序。

考虑 ``(`` 和 ``)`` 是怎样归并的：将最终的括号串中提取 ``(`` 和 ``)``，则其仍然构成括号串：

![](https://s2.loli.net/2025/02/05/UDqfELodyQR465r.jpg)

（只保留红色，依次拼接起来仍然是括号串）

所以我们大胆猜测 ``(`` 和 ``)`` 的归并为：进行最少步数的交换使得其为合法括号串。

这里我们可以不跑那个算法，可以考虑这样一个贪心：

- 当栈空了且遇到一个 ``)`` 时，我们找到当前位置之后最靠前的一个 ``(`` 换过来使其合法。

仔细想想确实是对的，因为 ``x`` 只是要求当前栈中有元素，如果我们花费额外代价将 ``)(`` 变为 ``()``，至多只能使得其与 ``x`` 合并时减少一个逆序对，并不能使得答案更优。

于是我们就解决了这个问题。

代码：

```cpp

const int maxn=8005;

pair<char,int> a1[maxn],a2[maxn];
int tot1,tot2;

void adjust(vector<pair<char,int>> v){
	int cnt=0;
	rep(i,0,v.size()-1){
		if(v[i].x=='(') cnt++;
		else{
			if(!cnt){
				cnt++;
				auto it=find_if(v.begin()+i,v.end(),lambda(auto x){return x.x=='(';});
				rotate(v.begin()+i,it,it+1);
			}
			else cnt--;
		}
	}
	for(auto i:v) a1[++tot1]=i;
}

int n;
int le1[maxn][maxn],le2[maxn][maxn];
int dp[maxn][maxn],stk[maxn][maxn];

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	memset(dp,0x3f,sizeof dp);
	string s;
	cin>>s;
	vector<pair<char,int>> v;
	rep(i,0,s.size()-1){
		if(s[i]=='x'||s[i]=='o') a2[++tot2]={s[i],i+1};
		else v.pb({s[i],i+1});
	}
	adjust(v);
	rep(i,1,tot1) rep(j,1,s.size()) le1[i][j]=le1[i-1][j]+(a1[i].y<=j);
	rep(i,1,tot2) rep(j,1,s.size()) le2[i][j]=le2[i-1][j]+(a2[i].y<=j);
	dp[0][0]=0;
	rep(i,0,tot1) rep(j,0,tot2){
		if(a1[i+1].x=='(') stk[i+1][j]=stk[i][j]+1,ckmin(dp[i+1][j],dp[i][j]+i+j-le1[i][a1[i+1].y]-le2[j][a1[i+1].y]);
		else if(stk[i][j]) stk[i+1][j]=stk[i][j]-1,ckmin(dp[i+1][j],dp[i][j]+i+j-le1[i][a1[i+1].y]-le2[j][a1[i+1].y]);

		if(a2[j+1].x=='o') stk[i][j+1]=stk[i][j],ckmin(dp[i][j+1],dp[i][j]+i+j-le1[i][a2[j+1].y]-le2[j][a2[j+1].y]);
		else if(stk[i][j]) stk[i][j+1]=stk[i][j],ckmin(dp[i][j+1],dp[i][j]+i+j-le1[i][a2[j+1].y]-le2[j][a2[j+1].y]);
	}
	cout<<dp[tot1][tot2]<<endl;
}

```

---

## 作者：while_0 (赞：1)

题目链接：[洛谷](https://www.luogu.com.cn/problem/AT_agc054_d) [Atcoder](https://atcoder.jp/contests/agc054/tasks/agc054_d)

对于交换相邻两项，最小化操作次数的题，有结论：设 $p_i$ 是操作结束后原本序列第 $i$ 项交换后的位置，答案为 $p$ 的逆序对数。证明：容易看出每次交换最多减少一个逆序对，且有逆序对的情况下一定能减少一个。

有了这个结论，我们就考虑使用 dp 最小化 $p$ 的逆序对数。

容易发现相同字符相对位置不会变化。因此我们考虑做一个四路归并。

已保证左右括号个数相等，故括号序列合法等价于任意前缀中左括号的个数不少于右括号的个数。

对于左右括号，有贪心：若当前放下的左括号多于右括号，则放下相对位置的下一个；否则放下下一个左括号。时间复杂度 $O(|S|log|S|)$（没精细实现，用了二分）

对于 $\texttt{o}$ 和 $\texttt{x}$，可以证明不改变相对位置是最优的。这在下面的 dp 中会证明。

$\texttt{o}$ 没有放下的条件，$\texttt{x}$ 放下的条件为当前放下的左括号多于右括号。

最后归并上述两点：设 $f_{i,j}$ 为放下了 $i$ 个括号、$j$ 个字母的最小的括号与字母之间的逆序对数。转移时对每个放下的括号统计其对逆序对数的贡献。细节见代码。

对于字母不用改变顺序的证明：若满足 $\texttt{x}$ 的放下条件，原本就不用调整。若不满足：用 $\texttt{[o]}$ 代表非负整数个 $\texttt{o}$，$\texttt{...}$ 代表任意串，则该串形如 $\texttt{...)[o]x...}$ 或 $\texttt{[o]x[o](...}$，将 $\texttt{x}$ 单独提前/放后可以改为连带着跨过的 $\texttt{o}$ 一起交换，代价相等。故字母间不用改顺序。

最后将括号归并与括号-字母归并的结果相加即为答案。

时间复杂度 $O(|S|^2)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[8080];
int h[8080];int co[8080];
int c[8080];
int as[8080],ac,bs[8080],bc;
int f[8080][8080];
bool ok[8080];
signed main()
{
	scanf("%s",s);
	int n=strlen(s);
	int ans=0;
	int cnt=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='o'||s[i]=='x')cnt++,ok[cnt]=s[i]=='o';
		co[i]=cnt;
		if(s[i]=='(')as[ac++]=i;
		if(s[i]==')')bs[bc++]=i;
	}
	int m=ac;
	int p1=0,p2=0;int lh=0;
	int q=0;
	while(p1<m||p2<m)
	{
		if(lh==0)ans+=lower_bound(bs,bs+m,as[p1])-bs-p2;
		if(lh==0||p2==m||(p1!=m&&as[p1]<bs[p2]))h[++q]=++lh,c[q]=co[as[p1++]];
		else h[++q]=--lh,c[q]=co[bs[p2++]];
	}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=0;i<=q;i++)
	{
		for(int j=!i;j<=cnt;j++)
		{
			f[i][j]=1e9;
			if(i)f[i][j]=f[i-1][j]+abs(j-c[i]);
			if(j&&(ok[j]||h[i]))f[i][j]=min(f[i][j],f[i][j-1]);
		}
	}
	printf("%d\n",f[q][cnt]+ans);
}
```

---

## 作者：xcyyyyyy (赞：1)

$o$ 为占位符。

$x$ 需要保证在一个括号内。

构造合法的方案必然是简单的，我们的问题是最小化邻项交换次数。

对于交换次数我只能想到逆序对，我们需要给这些符号分配标号使得按照标号排序合法且逆序对最小。

对于同一个类字符的标号必然是从小到大......然后就没有然后了。

---

首先有一点是，去掉 `o` 和 `x` 后，原串是一个合法括号序。

但是有很多种可选合法括号序，我们一定只会选择移动次数最少的（以下称为最小括号序）。

考虑在最小括号序的基础上交换若干项得到的其他括号序列。如果交换 `()`，能放 `x` 的位置只有可能变小，一定是不优的；对于交换 `)(` 的情况，只能使得这一对中间的 `x` 合法，但是交换这两个 `)(` 不如直接将中间的 `x` 调整到两边，所以我们一定只会选择最小括号序。

所以我们把答案分成三部分：括号序之间的逆序对，`ox` 之间的逆序对，`()` 和 `ox` 之间的逆序对。

**`ox` 之间的逆序对**一定为 $0$，也就是我们一定不会交换 `o` 和 `x`，由于一旦交换这两个一定的目的一定是为了将 `x` 移动到某一个括号内，但是与其如此不如直接将对应的 `)` 或 `(` 移动过来。

那么只剩下 **`()` 和 `ox` 之间的逆序对**了，直接设 $f_{i,j}$ 表示考虑了括号序前 $i$ 个，没有放入的 `ox` 的第 $j$ 个，最小的逆序对数，直接转移即可。

至于**括号序之间的逆序对**，从左往右遍历括号，如果当前遇到了无法匹配的 `)`，一定是将后面最近的一个 `(` 移动到前面来，随便怎么搞搞就行了。

```c++
#include<bits/stdc++.h>
using namespace std;
#define N 8005
int n,m,len,a[N],b[N],pr[N],f[N][N],i1[N][N],i2[N][N],ans;
char s[N];
int main(){
	scanf("%s",s+1);len=strlen(s+1);
	for(int i=1;i<=len;i++)
		if(s[i]=='('||s[i]==')')a[++n]=i;
		else b[++m]=i;
	for(int i=1,l=0;i<=n;i++){
		if(!l&&s[a[i]]==')'){for(int j=i+1;1;j++)if(s[a[j]]=='('){for(int k=j;k>i;k--)swap(a[k],a[k-1]);break;}}
		if(s[a[i]]=='(')++l;
		else --l;
		pr[i]=l;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)ans+=a[i]<a[j];
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)i1[i][j]=i1[i][j-1]+(a[i]<b[j]);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)i2[i][j]=i2[i-1][j]+(b[j]<a[i]);
	memset(f,0x3f,sizeof(f));f[0][0]=0;
	for(int i=0;i<=n;i++)for(int j=0;j<=m;j++){
		f[i+1][j]=min(f[i+1][j],f[i][j]+i1[i+1][j]);
		if(pr[i]||s[b[j+1]]=='o')f[i][j+1]=min(f[i][j+1],f[i][j]+i2[i][j+1]);
	}
	printf("%d",f[n][m]+ans);
}
```

---

## 作者：kyEEcccccc (赞：1)

有点厉害题。对于括号序列和序列上邻项交换的问题的处理有一些启发。

首先考虑如果没有 `ox` 怎么样。容易发现，我们从前往后记录左括号与右括号的个数差，这个差值一旦为负就立刻从后面提一个右括号过来（一路交换过来），这个做法一定是最优的，并且是唯一最优的操作方法。这样理解比较感性，实际上我们可以对每个分界点计算贡献：如果一个分界点左侧的左括号个数减右括号个数为 $x < 0$，则一定恰好从右边往左边扔 $x$ 个左括号，所以在这个分界点进行的交换次数恰好是 $x$，于是就算出了每个分界点的贡献。代入上面说的策略，会发现每个分界点的交换次数都达到了最优，于是得证。

下面考虑加入 `o` 和 `x`。容易发现如果只有 `o` 是容易的，考虑每个 `o` 左侧的左右括号个数就能知道有多少左括号和这个 `o` 发生交换。然而接下来，当加入 `x` 时，事情变得棘手起来。由于 `x` 不能放置在左侧左右括号数目相等的地方，这个限制不能简单转化为某种贡献来计算（`x` 的位置还会限制它前后的 `o` 位置，从而改变许多字符被交换的次数）。

首先得出两个结论：首先，在最优解中，把所有左右括号提出来，得到的序列就是它们按照贪心策略得出的最优解。这是因为为了使 `x` 合法，不会产生额外的 `()` 间交换，这种交换直接去掉一定不劣。其次，不会有 `ox` 间交换。这是因为如果为了让 `x` 合法而把它往前后移动，这个操作可以等价地改为移动一个前面的一个右括号或后面的一个左括号过来，达到同样效果。

有了这两个结论，我们考虑首先预处理出 `()` 构成的序列，计算它经过一系列交换以后形成的序列，每个位置分别来自原序列的哪个位置。接着进行 DP，设 $F_{i, j}$ 表示第 $i$ 个 `ox`，前面放了 $j$ 个 `()`，产生的最小贡献。其中一个 `o` 或 `x` 的贡献是这样计算的：考虑它前面有多少个元素原本在它后面以及后面有多少元素原本在它前面。由于上述两个结论，这个贡献非常容易通过前后缀和预处理计算，时间复杂度为 $\mathrm O(n^2)$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc054_d)

**题目大意**

> 给定长度为 $n$ 的字符串 $S$，包含 `(,),x,o` 四种字符，交换若干对相邻元素后，把 `o` 换成 `()`，把 `x` 换成 `)(`，最小化交换次数使得得到的串是合法括号序列。
>
> 数据范围：$n\le 8000$。

**思路分析**

我们只要求出最终的 $S_i$ 来自哪里，得到一个排列，最小化该排列的逆序对数即可。

考虑 $S$ 中不包含 `x,o` 的情况，那么对于一个分界点 $(i,i+1)$，如果 $S[1,i]$ 中右括号比左括号多 $x$ 个，我们就要在 $S[i+1,n]$ 中选至少 $x$ 个右括号放到 $S[1,i]$ 中，产生 $x$ 的贡献。

这个下界是可以取到的，按如下方式构造：从左到右依次加入字符，如果右括号多于左括号，就把当前的右括号和后面最近的一个左括号交换。

不难证明如下方式构造出来的排列逆序对数恰好取到下界。

回到原题，我们发现 `o` 可以放在任何位置，而 `x` 至少要被一对括号包住。

那么为了使一对 `x` 合法，交换一对已匹配的括号 `(,)` 是完全没有意义的。

并且我们只要把 `x` 放进括号中间，那么通过交换 `o,x` 把 `x` 放进去不优于把括号给交换出来。

因此 `(,)` 和 `o,x` 内部都不会产生交换，预处理出 `(,)` 的最优排列，然后维护 dp，设 $f_{i,j}$ 表示当前填了 $i$ 个 `(,)` 和 $j$ 个 `o,x` 的最小代价，转移前预处理一些逆序对数即可。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=8005;
char s[MAXN];
int n,m,sz,a[MAXN],b[MAXN],w[MAXN],dp[MAXN][MAXN],fa[MAXN][MAXN],fb[MAXN][MAXN];
inline void chkmin(int &x,const int &y) { x=x<y?x:y; }
signed main() {
	scanf("%s",s+1),sz=strlen(s+1);
	for(int i=1;i<=sz;++i) {
		if(s[i]=='('||s[i]==')') a[++n]=i;
		else b[++m]=i;
	}
	for(int i=1;i<=n;++i) {
		w[i]=w[i-1]+(s[a[i]]=='('?1:-1);
		if(w[i]<0) {
			for(int j=i+1;;++j) if(s[a[j]]=='(') {
				rotate(a+i,a+j,a+j+1); break;
			}
			w[i]+=2;
		}
	}
	memset(dp,0x3f,sizeof(dp)),dp[0][0]=0;
	for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j) dp[0][0]+=a[j]<a[i];
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) {
		fa[i][j]=fa[i][j-1]+(a[i]<b[j]);
		fb[i][j]=fb[i-1][j]+(b[j]<a[i]);
	}
	for(int i=0;i<=n;++i) for(int j=0;j<=m;++j) {
		if(i<=n) chkmin(dp[i+1][j],dp[i][j]+fa[i+1][j]);
		if(j<=m&&(w[i]||s[b[j+1]]=='o')) chkmin(dp[i][j+1],dp[i][j]+fb[i][j+1]);
	}
	printf("%d\n",dp[n][m]);
	return 0;
}
```

---

## 作者：win114514 (赞：0)

感觉看到交换就应该要想到逆序对。

### 思路

一个前置小知识，我们把一个排列用相邻交换复原的最小次数是逆序对数量。

考虑没有 `ox` 的情况。

我们顺着扫一遍字符串。

把左括号正一，右括号看作负一，当前缀和小于零以后，我们把后面最近的左括号提过来，这样可以构造出交换次数最少的合法括号串。

假如有了 `ox` 怎么办。

我们可以现忽略 `ox` 用上面的部分求出交换次数。

考虑剩下的两种次数：

1. `o` 与 `x`。

     我们发现我们永远不会交换 `o` 和 `x`，因为这样没有意义，当我们把一个 `x` 移到括号中间时，如果要交换 `o` 和 `x`，那这样不如把括号移过来。

2. `ox` 与括号。

     这一部分我们可以使用动态规划直接求出最优的方案。注意 `x` 一定得在一对括号中间。

时间复杂度：$O(|S|^2)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int ans;
int d[8080];
int f[8080][8080];
int v1[8080][8080];
int v2[8080][8080];
string s, t;

int main() {
  cin >> s, t = s;
  int num = 0;
  for (int i = 0; i < s.length(); i++) d[i] = i;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == ')') num--;
    if (s[i] == '(') num++;
    if (num < 0) {
      if (s[i] == ')') num++;
      if (s[i] == '(') num--;
      int k = 0;
      for (int j = i; j < s.length(); j++) {
        if (s[j] == '(') { k = j; break; }
      }
      for (int j = k; j > i; j--) {
        if (s[j - 1] == '(') ans++;
        if (s[j - 1] == ')') ans++;
        swap(s[j], s[j - 1]);
        swap(d[j], d[j - 1]);
      }
      if (s[i] == ')') num--;
      if (s[i] == '(') num++;
    }
  }
  vector<int> a;
  vector<int> b;
  vector<int> c;
  num = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == ')') num--, a.push_back(d[i]), c.push_back(num);
    if (s[i] == '(') num++, a.push_back(d[i]), c.push_back(num);
    if (s[i] == 'o') b.push_back(d[i]);
    if (s[i] == 'x') b.push_back(d[i]);
  }
  for (int j = 0; j < b.size(); j++) {
    v1[j][0] = 0;
    for (int i = 1; i <= a.size(); i++) {
      v1[j][i] = (b[j] < a[i - 1]) + v1[j][i - 1];
    }
  }
  for (int j = 0; j < a.size(); j++) {
    v2[j][0] = 0;
    for (int i = 1; i <= b.size(); i++) {
      v2[j][i] = (a[j] < b[i - 1]) + v2[j][i - 1];
    }
  }
  for (int i = 0; i <= a.size(); i++)
    for (int j = 0; j <= b.size(); j++)
      f[i][j] = 1e9;
  f[0][0] = 0;
  for (int i = 0; i <= a.size(); i++) {
    for (int j = 0; j <= b.size(); j++) {
      if (i < a.size()) f[i + 1][j] = min(f[i + 1][j], f[i][j] + v2[i][j]);
      if (j < b.size()) {
        if (t[b[j]] == 'o')
          f[i][j + 1] = min(f[i][j + 1], f[i][j] + v1[j][i]);
        if (t[b[j]] == 'x' && (i && c[i - 1]))
          f[i][j + 1] = min(f[i][j + 1], f[i][j] + v1[j][i]);
      }
    }
  }
  cout << ans + f[a.size()][b.size()] << "\n";
}
```

---

