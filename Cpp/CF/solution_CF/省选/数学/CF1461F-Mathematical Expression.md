# Mathematical Expression

## 题目描述

Barbara was late for her math class so as a punishment the teacher made her solve the task on a sheet of paper. Barbara looked at the sheet of paper and only saw $ n $ numbers $ a_1, a_2, \ldots, a_n $ without any mathematical symbols. The teacher explained to Barbara that she has to place the available symbols between the numbers in a way that would make the resulting expression's value as large as possible. To find out which symbols were available the teacher has given Barbara a string $ s $ which contained that information.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461F/02106beeaef426549ac520f7998d1f0ec360fdcb.png)It's easy to notice that Barbara has to place $ n - 1 $ symbols between numbers in total. The expression must start with a number and all symbols must be allowed (i.e. included in $ s $ ). Note that multiplication takes precedence over addition or subtraction, addition and subtraction have the same priority and performed from left to right. Help Barbara and create the required expression!

## 说明/提示

The following answers also fit the first example: "2+2+0", "2+2-0", "2\*2+0".

## 样例 #1

### 输入

```
3
2 2 0
+-*```

### 输出

```
2*2-0```

## 样例 #2

### 输入

```
4
2 1 1 2
+*```

### 输出

```
2+1+1+2```

# 题解

## 作者：zzzYheng (赞：6)

稍微分讨一下：`+`、`-`、`*`、`+-`、`*-` 都是简单的，这里不再赘述。

`*+` 和 `*+-` 是等价的，因为把所有 `-` 换成 `+` 不会变劣，所以只用考虑 `*+` 的情况。

考虑填完 `*` 和 `+` 后结果是如何计算的，发现就是所有 `*` 连续段每段积的和。

那就是要你把原序列划分成若干个子段，要你最大化每段乘积的和。

`0` 对乘法是特殊的，如果其被包含在 `*` 连续段中必然不优，其一定是单独的一个子段。

所以相邻的两个 `0` 间的符号填写就变成了若干个独立的子问题，并且这些子问题的序列中不存在 `0`。

后文中用 $m$ 表示子问题的大小。

`1` 对于乘法也是较为特殊的，如果没有 `1` 那一定是全部乘起来最大。

有个显然的性质，如果一个连续段中存在 `1` 的前缀或是后缀，那把那个前缀或者后缀单独拉出来变成一个连续段一定更优。

考虑虽然有 `1`，但符号填写大体上还是填 `*` 较优，因此我们考虑把两个相邻的子段合并起来对答案贡献的影响。

假设两个连续段乘积分别为 $a$ 和 $b$，$\Delta=a\cdot b-a-b=(a-1)(b-1)-1$。

显然如果 $a>1$ 且 $b>1$，那把 $a$ 和 $b$ 合并就是不劣的，所以相邻的非 $1$ 子段合并起来一定不劣。

同时显然 `1` 的子段必然单独存在。

那么所有不劣的划分方式一定是：先将所有非 `1` 连续段合并，因为最后它们一定在同一子段内，然后再将这些非 `1` 连续子段拼成若干子段（合并的时候中间可能夹了一些 `1`），然后 `1` 以单独子段的形式夹在非 `1` 子段中间。比如这就是一个例子：`1+1+8*9*1*1*3*2*1*1*7*3+1+1+5*3*1*1*2+1`。

那我们继续考虑将两个中间夹了 $l$ 个 `1` 的非 $1$ 子段合并起来对答案的影响。

这个东西可以看成先有 $a\cdot b-a-b$ 的增量，然后有 $l$ 的减量，注意到如果 $a$ 和 $b$ 的乘积大于 $2m+\Theta(1)$，那无论中间有多少个 $1$，将其合并一定不劣。

更进一步的，我们发现把若干个非 `1` 子段合并一定比两个非 `1` 子段合并对答案的贡献的增量更大（具体为 $\prod a_i-\sum a_i \ge a_1\cdot \prod _{i=2}a_i-a_1-\prod_{i=2}a_i$），而合并之后答案的减量仍然不超过 $m$。

所以如果当前局面上所有非 `1` 子段的乘积大于 $2m+\Theta(1)$，那把它们全部合并一定是不劣。

也就是说，如果初始序列上所有非 `1` 值的乘积大于 $2m+\Theta(1)$，那把它们全部合并到一个子段里一定是最优（不劣）解。

而如果所有非 `1` 值乘积小于 $2m+\Theta(1)$，那它们的个数一定小于 $\log_{2}m+\Theta(1)$。

那非 `1` 子段的拼接直接 $2^{size}$ 暴捜就可以做到时间复杂度 $\Theta(m)$。

所以总时间复杂度 $\Theta(n)$。

---

## 作者：LTb_ (赞：5)

[更好的阅读体验](http://lycltb.top/post/solution-cf1461f/)

大力分类讨论：

- 没有 $\texttt{*}$
  - 显然
- 有 $\texttt{*}$：
  - 没有 $\texttt{+}$
    - 没有 $\texttt{-}$：显然
    - 有 $\texttt{-}$：找到第一个 $0$（如果存在的话）并在这个 $0$ 前面一个位置填上 $\texttt{-}$，其他全部填 $\texttt{*}$。
  - 有 $\texttt{+}$ 的情况是接下来的讨论重点是



首先注意到如果有 $\texttt{+}$，则 $\texttt{-}$ 根本不可能被用到（因为 $0 \le a_i \le 9$）

一个很自然的想法是把整个序列以 $0$ 为分割点，分成几段分别处理。

对于每一段，有一个非常 naive 的 $n^2$ $dp$：设 $dp_i$ 为前 $i$ 个字符能构成的最大值，每次枚举 $j$，从 $dp_i$ 转移到 $dp_j$ 表示把 $[i,j]$ 中的数乘起来。显然无法通过：不仅会 TLE，数的乘积也会爆 $\texttt{long long}$。

考虑几个优化：如果某一段 $[l,r]$ 的乘积大于一个常数 $P$，则我们直接把 $[l,r]$ 中所有数乘起来。

这个优化可以被形如 $9,9,9 \cdots 9,1$ 的数据卡掉（最后一个 $1$ 前面应为 $\texttt{+}$），所以在处理之前需要特判掉首尾的所有 $1$。

官方题解中取 $P=10^{16}$，实际上 $P$ 的（并不精确的）下界非常小，只需要确保 $P \ge 2n$ 即可。详细证明可以参考 [arvindr9](https://codeforces.com/profile/arvindr9) 的 [comment](https://codeforces.com/blog/entry/85491?#comment-732087)（文末附有这段证明的翻译（这么良心的题解不点个赞吗（（

第二个优化是对于 $dp$ 的：预处理 $\texttt{next}_i$，表示 $i$ 之后第一个不是 $1$ 的数的位置。在 $dp$ 中枚举 $j$ 时可以直接从 $j$ 跳到 $\texttt{next}_j$ 而不是 $j+1$。于是这个 $dp$ 的复杂度变成了 $\mathcal{O(len \cdot x)}$，其中 $x$ 表示一段中不为 $1$ 的数的个数。而上一个优化确保了 $x \le \log_2 P$，故复杂度正确。

简洁起见，代码删去了[缺省源](https://www.luogu.com.cn/paste/cmtmxcj4)

```c++
// 2020.12.13
// Code by LTb
// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define debug puts("QwQ");

const int MAXN=100005;
int n;
int a[MAXN];
bool Plus,Minus,Multiple;
int dp[MAXN],bel[MAXN];
char ans[MAXN];
int nex[MAXN];
int P=1e7;

void sol1(){
	for (int i=2;i<=n;i++)
		if (Plus) ans[i]='+';
		else ans[i]='-';
}

void sol2(){
	for (int i=2;i<=n;i++)
		ans[i]='*';
}

void sol3(){
	int pos=0;
	for (int i=1;i<=n;i++)
		if (!pos && a[i]==0) pos=i;

	for (int i=2;i<=n;i++){
		if (i==pos) ans[i]='-';
		else ans[i]='*';
	}
}

void init(){
	int cur=0;
	for (int i=n;i>=1;i--){
		nex[i]=cur;
		if (a[i]!=1) cur=i;
	}
}

void foo(int l,int r){
	int cnt=1;
	dp[l-1]=0;
	for (int i=l;i<=r;i++){
		if (cnt<P) cnt*=a[i];
		dp[i]=bel[i]=0;
	}

	if (cnt>=P){
		for (int i=l+1;i<=r;i++)
			ans[i]='*';
		return ;
	}

	for (int i=l;i<=r;i++){
		cnt=1;
		for (int j=i;j<=r && j;j=nex[j]){
			cnt*=a[j];
			if (dp[i-1]+cnt>dp[j]){
				dp[j]=dp[i-1]+cnt;
				bel[j]=i-1;
			}
		}
	}

	int cur=r;
	while (cur>=l){
		int tmp=bel[cur];
		ans[tmp+1]='+';
		for (int i=tmp+2;i<=cur;i++)
			ans[i]='*';

		cur=tmp;
	}
}

void sol4(){
	init();
	for (int i=1;i<=n;i++){
		if (a[i]==0){
			ans[i+1]=ans[i]='+';
			continue;
		}

		int cur=i;
		while (cur<n && a[cur+1]!=0) cur++;

		int l=i,r=cur;
		while (l<=r && a[l]==1) ans[++l]='+';
		while (l<=r && a[r]==1) ans[r--]='+';
		if (l<=r) foo(l,r);
		i=cur;
	}
}

void print(){
	cout<<a[1];
	for (int i=2;i<=n;i++)
		cout<<ans[i]<<a[i];
	cout<<endl;
}

signed main()

{
	n=read();P=2*n;
	for (int i=1;i<=n;i++)
		a[i]=read();

	string allowed=readstr();
	for (auto i:allowed){
		if (i=='+') Plus=true;
		else if (i=='-') Minus=true;
		else Multiple=true;
	}

	if (!Multiple) sol1();
	else{
		if (!Plus && !Minus) sol2();
		else if (!Plus) sol3();
		else sol4();
	}

	print();
	return 0;
}
```

*Proof :*

考虑这个数组（这一段）的最佳分配符号方案。设它的长度为 $n$，则它可以被表示为如下形式：
$$
(d_{1_1} \cdot d_{1_2} \cdot d_{1_3} \dots ) + 1 + 1 + \dots 1 + (d_{2_1} \cdot d_{2_2} \dots ) + 1 + 1 +\dots  + (d_{k_1} \cdot d_{k_2} \dots )
$$
其中，每一块（即乘起来的一段连续的数）的首尾元素都大于 $1$。设 $a_i = \prod\limits_j d_{i_j}$。于是，这个数组所有数的乘积为 $\prod\limits_{i=1}^k a_i$，我们设这个乘积为 $P$。不妨假设 $k\ge 2$。

我们首先想要证明
$$
\sum\limits_{i=1}^k a_i \leq 2 + \frac{P}{2}
$$
若 $k=2$，则有
$$
a_1 + a_2 = a_1 + \frac{P}{a_1} \le 2 + \frac{P}{2}
$$
若 $k>2$，则有
$$
\sum\limits_{i=1}^k a_i \le (\sum\limits_{i=1}^{k-2}a_i) + a_{k-1} \cdot a_{k}
$$
于是我们可以归纳地证明该结论。

于是对于我们当前方案的贡献 $W$，有
$$
W \le \sum\limits_{i = 1}^k a_i + \text{1的个数} \le 2 + \frac{P}{2} + n - k \le \frac{P}{2} + n
$$
要使 $W \le P$ 即 $\frac{P}{2} + n \le P$，显然只要满足 $P \ge 2n$ 即可。

---

## 作者：syta (赞：4)

转化成在 $m$ 个不存在 $0$ 的连续段中填入 `+*`，最大化段表达式和，其余形式分讨一下，容易发现均平凡。

其中 $\sum m$ 数量级为 $10^5$。

容易发现一段中如果不存在 $1$，则一定是全乘起来最优，如果存在 $1$，先剥掉前后两侧。

现在有 $1$ 分隔开若干非 $1$ 段，首先一个非 $1$ 段内部一定使用 `*`，因为如果现在有两个相邻非 $1$ 数 $a,b$，满足 $a\cdot b=P\ge 4$，则一定有 $P\ge 2+\frac{P}{2}\ge a+\frac{P}{a}$。

于是推广到若干非 $1$ 合成段，现在的段一定形如开头和结尾均为非 $1$ 合成段，每个非 $1$ 合成段之间有若干个 $1$。

直观上告诉我们如果所有非 $1$ 段乘积比较大的时候，一定全选 `*`，所以现在只需要得到**至少**添加一个 `+` （全乘起来非最优）时的上界。

于是情况被分成两种：

- 全部填 `*`，乘积为 $P$。

- 至少划分一次，段中间至少一个 $1$，称这种情况下的答案为 $S$，容易把 $S$ 写成 $\sum p+k$ 的形式，其中 $k$ 为零散 $1$ 的个数。

现在只需要求出情况 2 更优的时候 $P$ 的取值范围。

首先通过归纳可以得到 $\sum p$ 随着分段变多而减小，因为每次拆开一段，必将产生 $P\rightarrow a+\frac{P}{a}$ 的变化。

所以 $\sum p$ 在至少划分一次的前提下，取**只**划分一次是最大的。

于是分成 $a,b$ 两段，又有 $a+\frac{P}{a}\le 2+\frac{P}{2}$。

故有 $\sum p\le a+\frac{P}{a}\le 2+\frac{P}{2}$。

再看 $k$ 的取值范围，显然不会超过段长 $m$。

有 $S=\sum p+ k \le 2+\frac{P}{2}+m$。

在 2 更优时 $S>P$，于是 $2+\frac{P}{2}+m>P$，解得 $P<4+2m$。

所以 $P<4+2m$ 时添加至少一个 `+` 可能会更优，此时非 $1$ 段个数不会超过 $\log_2(4+2m)\le 20$。

对于这样的段我们直接暴力 dp，记 $dp_i$ 表示前 $i$ 个非 $1$ 段划分最大和，每次枚举上一个 `+` 的断开位置即可。

对于一个长为 $m$ 的段做 dp 的复杂度为 $O(m^2)$，总共最多只有 $\frac{n}{m}$ 个段，所以总时间复杂度 $O(nm)=O(n\log n)$。

不想写，如果 noip 没退役的话第二天就写。

---

## 作者：tzc_wk (赞：4)

现场 1 小时 44 分钟过掉此题，祭之

![](https://cdn.luogu.com.cn/upload/image_hosting/ia1ukklw.png)

大力分类讨论。

如果 $|s|=1$，那么显然所有位置都只能填上这个字符，因为你只能这么填。

```cpp
scanf("%d",&n);mmp['+']=0;mmp['-']=1;mmp['*']=2;
for(int i=1;i<=n;i++) scanf("%d",&a[i]);
char opt[4];scanf("%s",opt+1);int len=strlen(opt+1);
int msk=0;for(int i=1;i<=len;i++) msk|=1<<mmp[opt[i]];
if(msk==1||msk==2||msk==4){
	for(int i=1;i<=n;i++){
		printf("%d",a[i]);if(i!=n) printf("%s",opt+1);
	}
}
```

如果 $s$ 只包含加和减，那么是个人都会全填加号。

```cpp
else if(msk==3){
	for(int i=1;i<=n;i++){
		printf("%d",a[i]);if(i!=n) putchar('+');
	}
}
```

如果 $s$ 中只包含乘和减，假设 $a_i$ 中第一个非零的位置为那么肯定只有最开头一段非零的数的贡献非零。剩下的贡献都为要么为零，要么为负。此时我们选择在最开头一段非零的数之间填 ```*```，接下来填一个减号，后面全填乘号。由于后面的数中肯定存在一个 $0$，所以减号后面的那坨东西肯定为 $0$，而我们的填法又保证了减号前面的东西尽可能大。所以这样可以取到最大值。

```cpp
else if(msk==6){
	bool hav=0;printf("%d",a[1]);
	for(int i=2;i<=n;i++){
		if(!a[i]&&!hav) hav=1,putchar('-');
		else putchar('*');
		printf("%d",a[i]);
	}
}
```

重头戏是 $s$ 中既包含 ```+``` 又包含 ```*``` 的情况。

注意此时 $s$ 中有没有 ```-``` 对我们的结果不会有影响。因为减号完全可以被加号代替并且结果不会更差。

显然 $0$ 旁边只能填加号。假设 $0$ 把原序列分成 $l$ 段，我们可以对这 $l$ 段**分别计算贡献**，再将它们相加，**各自的贡献独立。**

现在我们的目标就是在一段非零段之间填上 ```+``` 或 ```*``` 使结果最大。

注意到如果这一段中不包含 $1$ 那肯定全填乘号最优。唯一会影响我们判断结果的就是 $1$。

我们可以再用 $1$ 把这个非 $0$ 大段分成若干个“非 $1$ 小段”，显然这些非 $1$ 段之间全填 ```*```。而相邻的 $1$ 之间要么全填 ```+``` 要么全填 ```*```。

分析到这里，我们不妨把我们的发现用字母表示出来。假设我们在处理 $[L,R]$ 这个“非零大段”，共有 $[l_1,r_1],[l_2,r_2],\dots,[l_m,r_m]$ 这 $m$ 个 “非 $1$ 小段”。由于这 $m$ 个“非 $1$ 小段”之间都填 ```*```，可以假设这 $m$ 个“非 $1$ 小段”中间所有数的乘积为 $b_1,b_2,\dots,b_m$。

首先可以肯定的一点是，$[L,l_1),(r_m,R]$ 之间所有数都为 $1$，它们之间肯定只能填加号。

关键在于中间部分怎么填。不难看出这是一个基于段的划分，相邻段之间要么 ```+``` 要么 ```*```。于是就有一个 $m^2$ 的 $dp$，$dp_i$ 表示前 $i$ 段，第 $i$ 段与 $i+1$ 段之间全 ```+``` 的最大值，枚举上 ```+``` 的位置转移即可。

然后我就想着用玄学乱搞优化这个 $dp$，大概没啥思路，还要写高精。众所周知，CF 几乎不涉及高精，如果碰到道高精的题那大概率是你想偏了。

于是开始挖掘性质。我们可以发现，如果 $b_i$ 的乘积大于 $10^9$，那中间全 ```*``` 肯定是最优的。因为，假设最你在第 $i$ 段与第 $i+1$ 段之间填了 ```+```，那么这样就算中间全是 $1$，那最大也不过 $5\times 10^8+2+10^5=500100002$，小于全填乘号的 $10^9$。

排除掉这种情况之后，$m$ 最大也不过 $\log_2(10^9)$，直接 $m^2$ $dp$ 是完全没问题的，这样可以通过此题。

考场上的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
template<typename T>
void read(T &x){
	char c=getchar();T neg=1;
	while(!isdigit(c)){
		if(c=='-') neg=-1;
		c=getchar();
	}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1e5;
int n,a[MAXN+5];
map<char,int> mmp;
bool sgn[MAXN+5];
int pl[MAXN+5],pr[MAXN+5],pc=0;
ll pm[MAXN+5],dp[MAXN+5];int pre[MAXN+5];
void solve(int l,int r){
	if(l>r) return;
	pc=0;int lst=l-1;ll mul=1;
	for(int i=l;i<=r;i++){
		if(a[i]==1){
			if(lst+1<=i-1) pl[++pc]=lst+1,pr[pc]=i-1,pm[pc]=mul;
			mul=1;lst=i;
		} else {
			mul*=a[i];if(mul>1e9) mul=1e9;
		}
	}
	if(lst!=r) pl[++pc]=lst+1,pr[pc]=r,pm[pc]=mul;
//	for(int i=1;i<=pc;i++) printf("%d %d %d\n",pl[i],pr[i],pm[i]);
	pr[0]=l-1;for(int i=1;i<=pc;i++) dp[i]=0;
	mul=1;
	for(int i=1;i<=pc;i++){
		mul*=pm[i];if(mul>1e9) mul=1e9;
	}
	if(mul==1e9){
		pre[pc]=1;
	}
	else{
		for(int i=1;i<=pc;i++){
			mul=1;
			for(int j=i;j>=1;j--){
				mul*=pm[j];
				if(dp[i]<dp[j-1]+pl[j]-pr[j-1]-1+mul){
					dp[i]=dp[j-1]+pl[j]-pr[j-1]-1+mul;
					pre[i]=j;
				}
			}
//			printf("%d %lld %d\n",i,dp[i],pre[i]);
		}
	}
	for(int i=l;i<pl[1];i++) sgn[i]=1;
	for(int i=pr[pc];i<r;i++) sgn[i]=1;
	int cur=pc;
	while(cur){
		int t=pre[cur];//printf("%d\n",t);
		for(int i=pr[t-1];i<pl[t];i++) sgn[i]=1;cur=t-1;
	}
}
int main(){
//	freopen("in.txt","r",stdin);
	scanf("%d",&n);mmp['+']=0;mmp['-']=1;mmp['*']=2;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	char opt[4];scanf("%s",opt+1);int len=strlen(opt+1);
	int msk=0;for(int i=1;i<=len;i++) msk|=1<<mmp[opt[i]];
	if(msk==1||msk==2||msk==4){
		for(int i=1;i<=n;i++){
			printf("%d",a[i]);if(i!=n) printf("%s",opt+1);
		}
	} else if(msk==3){
		for(int i=1;i<=n;i++){
			printf("%d",a[i]);if(i!=n) putchar('+');
		}
	} else if(msk==6){
		bool hav=0;printf("%d",a[1]);
		for(int i=2;i<=n;i++){
			if(!a[i]&&!hav) hav=1,putchar('-');
			else putchar('*');
			printf("%d",a[i]);
		}
	} else {
		for(int i=1;i<=n;i++){
			if(!a[i]){
				if(i!=1) sgn[i-1]=1;
				if(i!=n) sgn[i]=1;
			}
		}
		int pre=0;
		for(int i=1;i<=n;i++){
			if(!a[i]) solve(pre+1,i-1),pre=i;
		}
		solve(pre+1,n);
		for(int i=1;i<n;i++){
			printf("%d",a[i]);
			if(sgn[i]) putchar('+');
			else putchar('*');
		} printf("%d",a[n]);
	}
	return 0;
}
/*
12
1 1 2 3 1 3 1 1 1 0 1 1
+*

18
1 2 3 1 1 2 1 1 1 1 1 1 1 1 1 1 1 2
+*
*/
```

---

## 作者：xtx1092515503 (赞：4)

大力分类讨论的题解。

首先，假如只能用一个字符，操作显然。

```cpp
void singlesolution(){
	for(int i=1;i<n;i++)printf("%d%c",a[i],s[0]);
	printf("%d\n",a[n]);
	exit(0);
}
```

然后，如果只能用 `+` 和 `-`，全部用 `+` 显然是最优的。

```cpp
void minusplussolution(){
	for(int i=1;i<n;i++)printf("%d%c",a[i],'+');
	printf("%d\n",a[n]);
	exit(0);
}
```

再后，如果只能用 `*` 和 `-`，明显除了最开头一个乘积的贡献为正以外，其它数的贡献全部为负；则我们首先把开头若干个非零数乘在一起，然后把剩下的所有数乘在一起减掉。因为我们是把非零数乘在一起，所以剩余的数中必然有一个 `0`，故该乘积为 `0`。可以发现这一定最优。

```cpp
void minustimessolution(){
	int i=1;
	for(;i<n;i++)if((a[i]>=1)&&(a[i+1]>=1))printf("%d%c",a[i],'*');else{
		if(i==1&&(a[i]==0))printf("%d%c",a[i],'*');
		else printf("%d%c",a[i],'-');
		i++;
		break;
	}
	for(;i<n;i++)printf("%d%c",a[i],'*');
	printf("%d\n",a[i]);
	exit(0);
}
```
最后，三个符号全能用（显然此时理智正常的人都不可能用 `-` 的），或者 `+` 和 `*` 同时能用。

首先先尝试把问题抽象一下。我们可以确定的一些操作有：

1. 对于序列中的 `0`，明显其两侧应都是 `+`；

于是我们便把序列按照所有 `0` 的位置断成了众多互不影响的小段。

2. 对于序列中一段连续的大于 `1` 的数，明显它们无论如何都会被乘在一起。那就乘在一起罢（先不管结果会不会非常大）。

3. 对于序列中一段连续的 `1`，明显它们要么全部被 `+` 连接，要么全部被 `*` 连接（此时其就联通了两边的大于 `1` 的段）。于是我们把它压缩成一段，记录此段的长度即可。

一番操作之后，我们发现原串被我们处理成了众多由 `0` 分成的大段，其中每一段中 `1` 段和非 `1` 段交替出现。

我们再来优化一下，发现每一大段两侧的 `1` 小段不会起到任何联通效果，故只能全部用 `+` 连接。

于是现在我们的大段的两侧就已经全部变成非 `1` 段了。

然后，上述问题就可以被抽象为：

给你 $m$ 个数 $b_1,\dots,b_m$，在某两个数 $i,i+1$ 间切一刀可以得到 $c_i$ 的贡献，切割完成后总贡献即为每一段中 $b_i$ 的乘积之和，再加上断点处的 $c_i$。求最大贡献。

我们先来考虑一个 `simple` 的场景：$m=2$。明显此时要么是 $b_1\times b_2$，要么是 $b_1+c_1+b_2$。但是，因为 $b_1,b_2$ 必定都大于 $1$（它们的定义是一段非 `1` 段中所有数之积），所以当其中至少有一个数大到某一量级的时候，无论 $c_1$ 是多少都不可能用 `+` 连接。因为 $\sum c$ 的量级是 $n=10^5$ 级别的，所以这个量级取 $2\times10^5$ 往上都可以，这里为了避免边界错误之类直接取了 $10^9$（这样也就解答了之前我们“连续的一段数的乘积很大”的问题）

于是我们先考虑 $\prod b$。假如其已经越过了上述量级，明显肯定会用 `*` 连接，那么直接连接即可。否则，则必有 $\prod b<10^9$；而又有 $b_i>1$，所以该序列的项数 $m$ 一共只会到 $\log10^9\approx32$ 的大小。$m$ 就这么点，直接 $m^2$ 暴力DP过去即可。

则时间复杂度 $O(n\log n)$。

```cpp
int f[1010],g[1010],b[1010],c[1010],p,pro[1010];
char t[100100];
const int inf=0x3f3f3f3f;
struct node{
	int st,ed,val;
	bool tp;
	node(int x,int y,int z,int w){st=x,ed=y,val=z,tp=w;} 
};
vector<node>v;
void plustimessolution(){
	for(int i=1,j=1;i<=n;i=j){
		if(!a[i]){t[i]='+',j++;continue;}
		if(a[i]==1){
			while(j<=n&&a[j]==1)j++;
			if(j<=n&&!a[j])t[j-1]='+';
			v.push_back(node(i,j,j-i,1));
			continue;
		}
		while(j<=n&&a[j]>1)j++;
		if(j<=n&&!a[j])t[j-1]='+';
		int val=1;
		for(int k=i;k<j;k++)val=min(1ll*inf,1ll*val*a[k]);
		v.push_back(node(i,j,val,0));
	}
//	for(int i=1;i<n;i++)printf("%d%c",a[i],t[i]);printf("%d\n",a[n]); 
//	for(auto i:v)printf("%d %d %d %d\n",i.st,i.ed,i.val,i.tp);
	for(int i=0,j=0;i<v.size();i=j){
		if(v[i].tp){
			for(int k=v[i].st;k<=v[i].ed;k++)t[k-1]='+';
			j++;continue;
		}
		j++;
		while(j<v.size()&&v[j-1].ed==v[j].st)j++;
		int delta=0;
		if(v[j-1].tp){
			j--;
			for(int k=v[j].st;k<=v[j].ed;k++)t[k-1]='+';
		}
		int all=1;
		for(int k=i;k<j;k++)if(!v[k].tp)all=min(1ll*inf,1ll*all*v[k].val);
		if(all==inf)for(int k=v[i].st;k+1<v[j-1].ed;k++)t[k]='*';
		else{
			p=0;
			for(int k=i;k<j;k++){
				if((k&1)==(i&1))b[++p]=v[k].val;
				else c[p]=v[k].val;
			}
//			for(int k=1;k<=p;k++)printf("%d ",b[k]);puts("");
//			for(int k=1;k<p;k++)printf("%d ",c[k]);puts("");puts("");
			pro[0]=1;
			for(int k=1;k<=p;k++)pro[k]=pro[k-1]*b[k];
			for(int r=1;r<=p;r++){
				f[r]=pro[r],g[r]=0;
				for(int l=1;l<r;l++)if(f[l]+pro[r]/pro[l]+c[l]>f[r])f[r]=f[l]+pro[r]/pro[l]+c[l],g[r]=l;
			}
			for(int k=p;k;k=g[k]){
				for(int l=v[i+g[k]*2].st;l+1<v[i+(k-1)*2].ed;l++)t[l]='*';
				if(g[k])for(int l=v[i+g[k]*2-1].st;l<=v[i+g[k]*2-1].ed;l++)t[l-1]='+';
			}
		}
		j+=delta;
	}
	for(int i=1;i<n;i++)printf("%d%c",a[i],t[i]);printf("%d\n",a[n]); 
}
```

---

## 作者：Tyyyyyy (赞：3)

## Tags:分类讨论/DP/数学
[原题](https://codeforces.com/contest/1461/problem/F)
#### 题目大意
给出一个长度为 $n$ 的数组 $a$，给出一个只包含 $+,-,\times$ 三种字符的字符串 $S$。对于 $\forall a_i(1 \leq i \leq n-1)$ ，你要在 $a_i$ 和 $a_{i+1}$ 中加上一个 $S$ 中出现过的符号，使运算结果最大（乘法优先）。输出方案即可。

数据范围：
$1 \leq n \leq 10^5 , 0 \leq a_i \leq 9 , 1 \leq \left|S\right| \leq 3$

#### 分析
我们先来考虑一些简单的情况（只有一种符号略过不提）。

首先只有加减的情况下，全放加一定是最优的。

如果只有减号和乘号，正常情况下我们肯定不会放减号。不过如果中间有 $0$ ，此时我们放乘号会直接让答案变成 $0$。那么这种情况下就要在 $0$ 前面放减号，之后都放乘号。

接下来我们来解决最难的情况：有加号和乘号。

这种情况下减号显然无用，可以忽略。

很容易想到的是：为了避免乘上 $0$ 对答案的影响，我们用 $a_i=0$ 的连续段来把 $a$ 数组分成若干“有效段”，“有效段”之间两两相加。

接下来我们来处理“有效段”之内，也就是不含 $0$ 的情况。

这时影响我们判断的就只有 $1$ 了。对于每个有效段前、后的连续 $1$，显然加比乘优。因此我们可以将有效段进一步缩小到这样的问题：

对于满足 $a_l>1,a_r>1$ 且 $\forall a_i>0,l\leq i \leq r$ 的区间 $[l,r]$ ，在其中添加加号和乘号使结果最大。

简单分析可得：必存在一个数 $lim$，使得若区间 $[l,r]$ 满足 $\prod_{i=l}^r a_i > lim$，则该区间内全加乘号为最优解。$lim$ 是一个较大的整数，这里取 $10^7$ 即可。

接下来讨论 $\prod_{i=l}^r a_i < lim$ 的情况。

考虑 dp，按区间内的 $1$ 连续段把区间分为若干个小区间 $intervals_1 \dots intervals_{size}$。定义 $dp_i$ 表示考虑了前 $i$ 个区间，在第 $i$ 和 $i+1$ 段之间放加号的最大值，枚举上一个加号的位置进行转移即可。这样的 $dp$ 复杂度是 $O(size^2)$ ，但是因为我们增加了 $lim$ 的限制，$size$ 不会超过 $\operatorname{log}lim$，因此 $O(size^2)$ 的复杂度是可行的。分类讨论进行 dp 即可通过本题。

代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll Lim=1e7;
int n,a[100010],pre[100];
char s[5];
bool op[3];
char ans[100010];
ll dp[100];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	cin>>s;
	for(int i=0;i<strlen(s);i++)
	{
		if(s[i]=='+')op[0]=1;
		if(s[i]=='-')op[1]=1;
		if(s[i]=='*')op[2]=1;
	}
	if(!op[2])
	{
		if(op[0])
		{
			for(int i=1;i<n;i++)printf("%d+",a[i]);
			printf("%d",a[n]);
		}
		else
		{
			for(int i=1;i<n;i++)printf("%d-",a[i]);
			printf("%d",a[n]);
		}
		return 0;
	}
	else
	{
		if(op[0])
		{
			for(int i=1;i<=n;i++)ans[i]='+';
			int pos=1;
			while(pos<=n)
			{
				while(pos<=n&&a[pos]==0)pos++;
				if(pos==n+1)break;
				int L=pos;
				while(pos<=n&&a[pos])pos++;
				int R=pos-1;
				while(L<=R&&a[L]==1)L++;
				while(L<=R&&a[R]==1)R--;
				if(L>R)continue;
				ll t=1;
				for(int i=L;i<=R;i++)
					t=min(t*a[i],Lim);
				if(t==Lim)
				{
					for(int i=L+1;i<=R;i++)ans[i]='*';
					continue;
				}
				int r=L;
				vector<pair<ll,pair<ll,ll> > >intervals;
				while(r<=R)
				{
					int l=r;
					t=1;
					if(a[l]==1)
					{
						while(r<=R&&a[r]==1)r++;
						t=r-l;
					}
					else
					{
						while(r<=R&&a[r]>1)
						{
							if(r!=l)ans[r]='*';
							t=min(t*a[r],Lim);
							r++;
						} 
					}
					intervals.push_back(make_pair(t,make_pair(l,r-1)));
				}
				int siz=intervals.size();
				memset(dp,~0x7f,sizeof(dp));
				dp[0]=0;
				for(int i=1;i<=siz;i++)
				{
					if(dp[i]<dp[i-1]+intervals[i-1].first)
					{
						pre[i]=i-1;
						dp[i]=dp[i-1]+intervals[i-1].first;
					}
					if(i%2==1)
					{
						ll tmp=1;
						for(int j=i;j<=siz;j++)
						{
							if((j-i)%2==0)tmp*=intervals[j-1].first;
							if((j-i)%2==0&&dp[j]<dp[i-1]+tmp)
							{
								pre[j]=i-1;
								dp[j]=dp[i-1]+tmp;
							}
						}
					}
				}
				int tmp=siz;
				while(tmp)
				{
					int lst=pre[tmp]+1,now=tmp;
					tmp=pre[tmp];
					if(lst<now)
					{
						for(int i=intervals[lst-1].second.first+1;i<=intervals[now-1].second.second;i++)
							ans[i]='*';
					}
				}
			}
			printf("%d",a[1]);
			for(int i=2;i<=n;i++)
			{
				putchar(ans[i]);
				printf("%d",a[i]);
			}
		}
		else if(op[1])
		{
			printf("%d",a[1]);
			for(int i=2;i<=n;i++)
			{
				if(a[i]==0)printf("-");
				else printf("*");
				printf("%d",a[i]);
			}
		} 
		else
		{
			printf("%d",a[1]);
			for(int i=2;i<=n;i++)printf("*%d",a[i]);
		}
	}
	return 0;
}
```

---

## 作者：forest114514 (赞：2)

### CF1461F Mathematical Expression

简单分类讨论题，一共 $2^3-1=7$ 种情况。

1. 首先只有 1 个符号是容易的，不阐述；同理 `+-` 也是容易的，也不阐述。 

2. `*-` 也不难做，首先考虑 `*` 的作用无非是让一段的积 < 小于一段的和，这个比 > 好想多了。

   此时有 0 就全部填乘号，一段 1 就向某个方向合并，否则全部填减号。

3. 然后  `*+`  和  `*+-`  是等价的，但是不太好做，这里我们仔细讲讲。

   首先 0 的周围填加号变成若干子问题即可，这很显然。

   对于 1 这是考虑的重点，毕竟有时 1 单独加，有时我们要合并 1 周围的两段乘积。

   对于每一段，现在是 **若干非 1 数相乘** 和 **一段连续的 1** 交替排列，现在我们考虑怎么合并，注意左端和右端的 1 直接填 `+` 就行了。

   > Lemma：合并 **若干非 1 数相乘** 的段答案增长是指数级别的。
   >
   > 考虑合并积为 $A$ 和 $B$ 的段，此时 $\Delta =A\times B-A-B-O(1)=(A-1)(B-1)+1-O(1)$，注意到在 $A> 1$ 或 $B > 1$ 的时候我们认为增长是 $O(AB)$ 级别的，而且合并多段时 $O(1)$ 这个 1 的数量的常数是最后减的，所以多段相乘的增长是指数级别的，此时两个连续非 1 数我们也可以看做两段，增长至少就是 $O(w^\text{非1数的个数}),w\geq 2$ 级别的。

   考虑一个分界点 $B$，如果这些数的个数 $> B$ 的话肯定直接全部填  `*`  否则段数不多直接暴力 DP 就可以了。这里 $B$ 可以稍微大一点防止只取一部分，这里取 $B=2\left\lceil\log 10^5\right\rceil=34$ 是绝对没有问题的。

   暴力 DP 说一下：设 $f_{i}$  表示以第 $i$ 个为一段连乘的结尾的最大和，$val_{i}$ 为第 $i$ 段的乘积，$c_{i}$ 为第 $i$ 段前面 $1$ 的个数，每次枚举连乘的区间转移即可。

 	$$
 		f_{i}=\max\limits_{1\leq j\leq i} \left(f_{j-1}+\prod\limits_{k=1}^{i} val_{i}-\sum\limits_{k=j+1}^{i}c_{k}+c_{j} \right)
 	$$
    

 	 这里的 DP 是 $O(B^2)$ 的，反正最后的时间复杂度不会超过 $O(\frac{N}{B}\times B^2)=O(NB)=O(N\log N)$ 就是了。

综上就是 $O(N\log N)$ 解决，而且基本跑不满啊。

因为不太想写就不放代码了。

---

## 作者：daniEl_lElE (赞：1)

只有一种符号是容易的。

有 `+-` 两种符号显然全部放 `+` 最优。

有 `*-` 两种符号的情况下，容易发现第一个 $a_i=0$ 以后的位置要么不产生贡献，要么产生负贡献。所以在所有 $a_i=0$ 的前面放上 `-`，其他都放 `*` 是最优方案。

不难发现有 `+-*` 的情况和有 `+*` 的情况是等价的，因为`-` 只能不产生贡献或者产生负贡献。

首先，在 $a_i=0$ 的两边一定放加号。取出不同的段。

我们发现对于任意一段，全部放加号最多达到 $10^6$，于是乘积大于 $10^6$ 的段直接全部放 `*` 即可。

否则，我们发现 $a_i\neq 1$ 的位置会很少。贪心地想，我们将所有连续的 $a_i=1$ 看成一个小段，所有 $a_i\neq1$ 单独看成一段。容易发现每一段内要么全是 `*`，要么全是 `+`。考虑 $dp_{i}$ 表示看到前 $i$ 段乘积最大是多少。记录转移情况即可构造。

设小段数为 $m$，则复杂度为 $O(m^2)$。小段数显然不会超过 $50$.故总复杂度为 $O(\frac{n}{m}\times m^2)=O(nm)$，其中 $m=50$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int a[100005],ans[100005],pos[100005],top,dp[55],frm[55],ft[55];
int tp;
signed main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	string s; cin>>s;
	for(int j=0;j<s.size();j++){
		if(s[j]=='-'){
			tp+=1;
		} 
		if(s[j]=='+'){
			tp+=2;
		}
		if(s[j]=='*'){
			tp+=4;
		}
	}
	if(tp==1){
		for(int i=1;i<=n;i++){
			cout<<a[i];
			if(i!=n) cout<<"-";
		}
	}
	else if(tp==2||tp==3){
		for(int i=1;i<=n;i++){
			cout<<a[i];
			if(i!=n) cout<<"+";
		}
	}
	else if(tp==4){
		for(int i=1;i<=n;i++){
			cout<<a[i];
			if(i!=n) cout<<"*";
		}
	}
	else if(tp==5){
		for(int i=1;i<n;i++){
			if(a[i+1]==0){
				cout<<a[i]<<"-";
			}
			else{
				cout<<a[i]<<"*";
			}
		}
		cout<<a[n];
	}
	else{
		for(int j=1;j<n;j++) ans[j]=1;
		for(int j=1;j<n;j++){
			if((a[j]==0)||(a[j+1]==0)) ans[j]=1;
		}
		pos[0]=0;
		for(int j=1;j<=n;j++){
			if(a[j]==0) pos[++top]=j;
		}
		pos[++top]=n+1;
		for(int i=0;i<top;i++){
			if(pos[i+1]==pos[i]+1) continue;
			int l=pos[i]+1,r=pos[i+1]-1;
			while(l<=r&&a[l]==1) ans[l]=1,l++;
			while(r>=l&&a[r]==1) ans[r-1]=1,r--;
			if(l>r) continue;
			int tot=1;
			for(int j=l;j<=r;j++){
				tot=min((int)1e9,tot*a[j]);
			}
			if(tot>=1e6){
				for(int j=l;j<r;j++) ans[j]=2;
			}
			else{
				int sum[55],mul[55],pt[55],tot=0;
				memset(sum,0,sizeof(sum));
				memset(mul,0,sizeof(mul));
				for(int j=l;j<=r;j++){
					if(a[j]!=a[j-1]) tot++,mul[tot]=1,pt[tot]=j;
					sum[tot]+=a[j];
					mul[tot]*=a[j];
				}
				pt[tot+1]=r+1;
				memset(dp,0,sizeof(dp));
				memset(frm,0,sizeof(frm));
				memset(ft,0,sizeof(ft));
				for(int j=0;j<=tot;j++){
					int sumn=0,muln=1;
					for(int k=j+1;k<=tot;k++){
						sumn+=sum[k];
						muln*=mul[k];
						if(dp[j]+sumn>dp[k]){
							dp[k]=dp[j]+sumn;
							frm[k]=j;
							ft[k]=1;
						}
						if(dp[j]+muln>dp[k]){
							dp[k]=dp[j]+muln;
							frm[k]=j;
							ft[k]=2;
						}
					}
				}
				int now=tot;
				while(now){
					int lst=frm[now];
					for(int j=pt[lst+1];j<pt[now+1]-1;j++) ans[j]=ft[now];
					now=lst;
				}
			}
		}
		for(int i=1;i<n;i++) cout<<a[i]<<((ans[i]==1)?"+":"*");
		cout<<a[n];
	}
	return 0;
}
```

---

## 作者：chenxia25 (赞：1)

先大力分类讨论：

- 有 $\texttt +$，此时如果有 $\texttt-$ 它也没有用，被 $\texttt+$ 代替会更优。
   - 有 $\texttt*$，这是接下来讲的重点；
   - 无，那就全部 $\texttt+$；
- 无，此时有 $\texttt-$ 的话就有用了。
   - 有 $\texttt-$。
      - 有 $\texttt*$，这个还稍微有点东西，但也非常简单。如果没有 $0$ 那显然全 $\texttt*$，否则答案下限是 $0$，然后考虑有 $\texttt-$ 的情况。那就分成至少两段，第一段的贡献是正的，后面都是负的。那么显然找到第一个 $0$ 前面都是 $\texttt*$，然后 $\texttt-$ 一下后面都是 $\texttt*$ 是最优的，因为最大化了第一段也最小化了后面；
      - 无，那就全 $\texttt-$；
   - 无，那就全 $\texttt*$。

下面重点讨论上述重点。

我们显然有一个平方的 DP，就是考虑对这个 $\texttt*$ 段 DP，每次用前缀积 $\mathrm O(n)$ 转移。然后也一脸优化不了。于是我们来找性质。

显然所有 $0$ 两边都必须是 $\texttt+$，如果是 $\texttt*$ 的话改成 $\texttt+$ 显然更优。也就是 $0$ 们把整个数列分成了独立的好几段，考虑对每段分别考虑。

然后如果全部 $>1$ 的话，显然是全 $\texttt*$ 最好。但关键有 $1$ 存在，可以弱化成这样一个结论：相邻两个 $>1$ 之间必须是 $\texttt*$，也容易反证。于是我们把它们缩起来。

那么 $1$ 可以看作浓缩饼干之间的桥梁。如果想要把两边断开的话，那就全 $\texttt+$ 最好，否则只能全 $\texttt*$ 才能连上。于是就变成了对 $1$ 段们的决策问题，似乎还是需要类似一开始的平方 DP。

但这时候有个好性质：一旦如果全 $\texttt*$ 能够非常大的话（我取的是 $10^9$），那就所有桥梁必须连起来，否则单凭加法的力量是完全被降维打击的。只有两端的 $1$ 段能够 $\texttt+$。然后又因为每段浓缩饼干都 $\geq2$，所以这时候段数是 $\log$ 级的，那怎么乱搞都可以了吧。我们依然考虑上述 DP，前缀积优化转移，记录路径，总复杂度 $\mathrm O\!\left(n\log^2\right)$。

**_[code](https://www.luogu.com.cn/paste/na5zmbcn)_**

---

## 作者：int08 (赞：0)

## 前言
构造练习 vol.2。

# Solution

先考虑一些看起来就比较简单的情况：

单种符号显然是全用这一种，`+-` 显然全用 `+`，`+-*` 和 `+*` 等价。

如果是 `-*`，似乎全部乘起来最优（因为没有减少的部分），但是发现有 $0$ 的时候用减号隔开 $0$ 更优（这样答案大于 $0$）。

主要情况是 `+*`。

首先如果有 $0$，两侧肯定是 `+`，接下来只需要考虑非零连续段。

发现相邻两个如果非 $1$，乘起来一定不劣。

现在问题就变成了：许多大数被许多 $1$ 段隔开（两侧的 $1$ 段肯定是填 `+`，加上就好了），对于每一个 $1$ 段，既可以选择全填 `+` 吃到等于其长度的贡献，也可以全填 `*` 放弃这个贡献但是将两边大数乘起来。

发现填 `+` 效率是很低的，只要大数的数量超过 $18$，全部乘起来最优，因为仅仅最后一次填 `*` 就有至少 $2^{17}$ 的收益，已经超过了 $1$ 的数量。

当小于 $18$ 的时候直接枚举每一个 $1$ 段如何选择，看起来复杂度很对了，事实上如果每一个连续段都形如 `2121212121` 这样，复杂度是 $O(\frac{n}{\log n}\cdot 2^{\log n}\cdot\log n)=O(n^2)$ 的。

考虑再次优化：设每一个非 $0$ 连续段所有大数乘积为 $x$，如果全部乘起来，最后一步至少有 $\frac{x}{2}$ 的贡献，如果这个数比连续段里 $1$ 的总数加一个小常数还要大，就可以认定直接全部乘起来最优。

现在再分析复杂度，发现它是 $O(n\log n)$ 的，读者自证不难。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,i,a[114514],col[114514];
bool is[128];
string s;
char ans[114514];
int t[32],p[32];
void solve(int l,int r)
{
	if(l>=r) return;
	if(a[l]==1)
	{
		ans[l]='+';
		solve(l+1,r);
		return;
	}
	if(a[r]==1)
	{
		ans[r-1]='+';
		solve(l,r-1);
		return;
	}
	int ti=1,oc=0;
	for(int i=l;i<=r;i++) ti=ti*a[i],ti=ti>1000000?1000000:ti,oc+=(a[i]==1);
	for(int i=l;i<r;i++) ans[i]='*';
	if(oc<ti/2-10) return;
	int cnt=0;
	for(int i=l;i<=r;i++)
	{
		if(i==l||a[i]>1&&a[i-1]==1) cnt++,t[cnt]=1,p[cnt]=0;
		if(a[i]>1) t[cnt]*=a[i];
		else p[cnt]++,col[i]=cnt;
	}
	cnt--;
	if(!cnt) return;
	int an=0,ani=0;
	for(int i=0;i<(1<<cnt);i++)
	{
		int now=t[1],res=0;
		for(int j=1;j<=cnt;j++)
		{
			if(i&(1<<j-1)) now*=t[j+1];
			else res+=now+p[j],now=t[j+1];
		}
		res+=now;
		if(res>an) an=res,ani=i;
	}
	for(i=l;i<=r;i++) if(a[i]==1&&!(ani&(1<<col[i]-1))) ans[i-1]=ans[i]='+';
}
int main()
{
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	cin>>s;
	for(auto x:s) is[x]=1;
	if(s.length()==1)
	{
		for(i=1;i<n;i++) cout<<a[i]<<s;
		cout<<a[n];
		return 0;
	}
	if(!is['*'])
	{
		for(i=1;i<n;i++) cout<<a[i]<<'+';
		cout<<a[n];
		return 0;
	}
	if(!is['+'])
	{
		cout<<a[1];
		for(i=2;i<=n;i++) cout<<(a[i]==0?'-':'*')<<a[i];
		return 0;
	}
	int last=1;
	for(i=1;i<=n;i++)
		if(!a[i])
		{
			ans[i]=ans[i-1]='+';
			solve(last,i-1);
			last=i+1;
		}
	solve(last,n);
	for(i=1;i<n;i++) cout<<a[i]<<ans[i];
	cout<<a[n];
}
```
# The End.

---

## 作者：Cure_Wing (赞：0)

[CF1461F Mathematical Expression](https://www.luogu.com.cn/problem/CF1461F)

### 思路

前面分类讨论差不多，这里简单提一嘴。

如果没有乘号，那么有加号一定全填加号，否则全填减号。因为数全为正。

如果只有乘号，那么全填乘号。

如果只有乘号和减号，那么 $0$ 前面填减号，其余填乘号。因为但凡中间出了个 $0$，后方填负号一定会是乘积为负更差，不如填乘号使其为 $0$。

如果同时含有加号和乘号，那么我们一定不会去选贡献为负的负号。而对于 $0$，两端填乘号贡献一定为 $0$，不如填加号贡献可能为正。而对于 $1$，当两端乘起来贡献大于这一段加起来的时候，我们填乘号，否则填加号。具体的，由于 $0$ 两端已经填了加号，我们以 $0$ 为界把数列分成几段分开做。把全 $1$ 和全非 $1$ 合并，全 $1$ 段统计含有 $1$ 的个数，因为它们加起来不比乘起来小；非全 $1$ 段统计其乘积，因为它们乘起来一定不比加起来小。而如果暴力枚举全 $1$ 段两端的符号，时间复杂度最坏 $O(2^n)$，直接起飞。而我们发现当全非 $0$ 区间的乘积大于 $10^9$ 的话，用加号连接全 $1$ 和全非 $1$ 段一定不可能超过这个值。所以我们判断区间乘积超过 $10^9$ 的话，直接全填乘号即可。对于剩余的情况，我们采用暴力的思路。分析一下，最坏情况是数列只含有 $0,1,2$，时间复杂度为 $O(2^{\log n})=O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=100005,inf=1e9;
int n,a[N],c[N],m,tag[N],l[N],nxt[N],val[N],now;
std::string s;
char ans[N],get[N];
bool vis[3];
inline void dfs(int l,int r,int sum,int mul,int x){
    if(nxt[l]>r){
        if(sum+mul>now){
            for(int i=x;i<r;i=nxt[nxt[i]]){
                for(int j=i;j<nxt[i]-1;++j) ans[j]='*';
                if(nxt[i]>r) break;
                for(int j=nxt[i]-1;j<nxt[nxt[i]];++j) ans[j]=get[i];
            }
            now=sum+mul;
        }
        return ;
    }
    get[l]='*';dfs(nxt[nxt[l]],r,sum,mul*val[nxt[nxt[l]]],x);
    get[l]='+';dfs(nxt[nxt[l]],r,sum+mul+val[nxt[l]],val[nxt[nxt[l]]],x);
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    cin>>s;
    for(int i=0;i<s.size();++i)
        if(s[i]=='+') vis[0]=1;
        else if(s[i]=='-') vis[1]=1;
        else if(s[i]=='*') vis[2]=1;
    if(!vis[2]){
        for(int i=1;i<n;++i) cout<<a[i]<<(vis[0]?'+':'-');
        cout<<a[n];
        return 0;
    }
    if(vis[2]&&!vis[0]&&!vis[1]){
        for(int i=1;i<n;++i) cout<<a[i]<<'*';
        cout<<a[n];
        return 0;
    }
    if(vis[2]&&!vis[0]){
        for(int i=1;i<n;++i){
            cout<<a[i];
            if(a[i+1]==0) cout<<'-';
            else cout<<'*';
        }
        cout<<a[n];
        return 0;
    }
    for(int i=1;i<=n;++i){
        if(a[i]==0){ans[i-1]=ans[i]='+';continue;}
        int j=i;
        for(;j<n&&a[j+1];++j);
        int l=i,r=j;
        for(;l<=r&&a[l]==1;++l) ans[l-1]=ans[l]='+';
        for(;l<=r&&a[r]==1;--r) ans[r-1]=ans[r]='+';
        if(l>r) continue;
        int mul=1;
        for(int j=l;j<=r;++j) mul=std::min(1ll*inf,1ll*a[j]*mul);
        if(mul>=inf) for(int j=l;j<r;++j) ans[j]='*';
        else{
            int last=l;val[l]=a[l];nxt[l]=l+1;
            for(int j=l+1;j<=r;++j){
                if(a[j]==1&&a[j-1]==1) ++val[last];
                else if(a[j]>1&&a[j-1]>1) val[last]*=a[j];
                else val[last=j]=a[j];
                nxt[last]=j+1;
            }
            now=0;dfs(l,r,0,val[l],l);
        }
        i=j;
    }
    for(int i=1;i<n;++i) cout<<a[i]<<ans[i];
    cout<<a[n];
    return 0;
}
```

---

## 作者：紊莫 (赞：0)

分类讨论题，vp 时想歪了不会。

## 只有一个运算符

略。

## 只有两个运算符

首先 ``+-`` 的情况略。然后看一下 ``-*`` 的情况，最优策略是在每个 $0$ 之前放一个减号，其余全是乘号，这样的话可以让减号造成的负贡献最小，实际上总贡献就是一端极长非 $0$ 前缀积。

**重点**是 ``+*`` 的情况。

首先，我们要知道乘号一定不能跨越 $0$，否则显然不优。
那么对于一个极长的非 $0$ 串，我们考虑取出左右的极长连续 $1$ 串，这些地方一定是用加号连接的，因为乘起来不会造成更多贡献。

那么对于中间的串，我们就变成了放加号和乘号让值最大，那么进行一个 DP，同时记录方案转移路径，即为答案。

但是，乘积有可能远大于 ``long long`` 能表示的范围，这时候，我们考虑当乘积大于某个值时，此时全选乘法一定更优，证明可见其他题解。

## 只有三个运算符

和 ``+*`` 的情况相同，减法不会造成贡献。

[示例代码。](https://codeforces.com/problemset/submission/1461/244500669)



---

