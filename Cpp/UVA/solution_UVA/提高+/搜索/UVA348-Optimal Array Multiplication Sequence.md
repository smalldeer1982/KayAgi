# Optimal Array Multiplication Sequence

## 题目描述

对于三个矩阵$A,B,C$，若$C=AB$，则C的计算方式为$C_{i,j}=\sum_k A_{i,k} \times B_{k,j}$。

可见若要计算两个大小分别为$a \times b$和$b \times c$的矩阵的乘积，需要$a \times b \times c$次计算；
对于两个矩阵$A,B$，不满足$A \times B = B \times A$；对于三个矩阵$A,B,C$，满足$(A \times B) \times C = A \times (B \times C)$。

给定$n$个矩阵$A1,A2, \dots ,An$的行列数，现在要算出这些矩阵的积，问如何安排运算顺序可使运算次数最少。

本题包含多组数据。

## 样例 #1

### 输入

```
3
1 5
5 20
20 1
3
5 10
10 20
20 35
6
30 35
35 15
15 5
5 10
10 20
20 25
0```

### 输出

```
Case 1: (A1 x (A2 x A3))
Case 2: ((A1 x A2) x A3)
Case 3: ((A1 x (A2 x A3)) x ((A4 x A5) x A6))```

# 题解

## 作者：YangXiaopei (赞：2)

## Solution:

大家不要被标签误导了！

虽说这题确实需要搜索，但他的本质其实是 **区间DP**。

我们每次可以将两个矩阵合为一个，而且数据保证了肯定可以合，不存在合不了的情况，这不铁定的区间DP吗？

我们设 $dp_{i, j}$ 为将 $[i, j]$ 合并的最小次数。

我们可以再每个区间中找个断点，我们设这个区间为 $[l, r]$，断点为 $i$，所需代价即为两边的代价和加上合并两个区间的代价。也就是 $a_l \times b_i \times b_r + dp_{l, i} + dp_{l + 1, r}$

但为什么又说这题需要搜索呢？

很简单，记忆化搜索比循环算答案好写。

我们只需每次 dfs 遍历 $[l, r)$，取其间最优的的值，记录在 $dp_{i, j}$ 中。

我们会了找答案，那又有什么用呢？

我们记录一个 $p_{i, j}$，在每次 $dp_{i, j}$ 变换答案时把 $p_{i, j}$ 记为答案枚举的断点，这样就能通过 $p_{i, j}$ 找答案了。

注意：答案中的 $\times$ 号用 `x` 表示。

具体实现看代码。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, cnt, a[15], b[15], p[15][15], dp[15][15];
int dfs(int l, int r){//求出p[i][j]和dp[i][j]
	if(l == r){
		dp[l][r] = 0;
		return 0;
	}
	if(dp[l][r]){
		return dp[l][r];
	}
	dp[l][r] = 1e18;
	for(int i = l; i <= r - 1; i++){
		int x = a[l] * b[i] * b[r] + dfs(l, i) + dfs(i + 1, r);
		if(x < dp[l][r]){
			dp[l][r] = x;
			p[l][r] = i;
		}
	}
	return dp[l][r];
}
string get(int l, int r){//通过断点找答案。
	string s;
	if(l == r){
		s = "A" + to_string(l);
		return s;
	}
	s = "(" + get(l, p[l][r]) + " x " + get(p[l][r] + 1, r) + ")";
	return s;
}
signed main(){
	while(cin >> n){//输入&输出
		cnt++;
		if(!n){
			break;
		}
		memset(dp, 0, sizeof(dp));
		for(int i = 1; i <= n; i++){
			cin >> a[i] >> b[i];
		}
		dfs(1, n);
		cout << "Case " << cnt << ": " << get(1, n) << "\n";	
	}
	return 0;
}
```

---

## 作者：xuchuhan (赞：2)

## 思路

观察题目，我们发现，题目让我们合并矩阵，求出最小代价。这不就是区间 DP 吗？

## 实现

$dp_{i,j}$ 表示将区间 $[i,j]$ 的矩阵合并成一个矩阵的最小代价。那么转移就是 $dp_{i,j}=\min_{k=i}^{j-1} dp_{i,k}+dp_{k+1,j}+a_i \times b_k \times b_j$。用 $pos_{i,j}$ 记录使得答案最小的断点，那么在输出时就可以利用 $pos_{i,j}$ 加括号了。

## 代码

注意多测清空。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=15;
int n,tot;
int a[N],b[N];
int dp[N][N],pos[N][N];
string out(int l,int r){
	if(l==r)
		return 'A'+to_string(l);
	string s='('+out(l,pos[l][r])+" x "+out(pos[l][r]+1,r)+')';//递归输出 
	return s;
}
signed main(){
	while(cin>>n){
		memset(dp,0,sizeof(dp));
		memset(pos,0,sizeof(pos));//多测清空 
		if(!n)
			break;
		for(int i=1;i<=n;i++)
			cin>>a[i]>>b[i];
		for(int l=1;l<=n;l++){
			for(int i=1;i+l-1<=n;i++){
				int j=i+l-1;
				if(i==j){//无需合并 
					dp[i][j]=0;
					continue;
				}
				dp[i][j]=1e18;
				for(int k=i;k<j;k++){
					int t=dp[i][k]+dp[k+1][j]+a[i]*b[k]*b[j];//转移 
					if(t<dp[i][j]){
						dp[i][j]=t;
						pos[i][j]=k;
					}
				}
			}
		}
		tot++;
		printf("Case %d: ",tot);
		cout<<out(1,n)<<"\n";
	}
	return 0;
}
```

---

## 作者：karma (赞：2)

此题为一道$dp$好题,背景很简单:矩阵链乘,但是输出方案非常~~毒瘤~~简单.

具体思路:

- 采用记忆化搜索形式.进行$dp$

- 在记忆化搜索的同时记录状态来源,$g[l][r]$表示$[l,r]$这个区间从$g[l][r]$处断开.

- 对于输出括号,可以发现:每次对于划分区间的两端加上括号就行了.代码中$zk$表示该处的左括号数量,$yk$表示右括号数量.

- 注意乘号的输出位置,且此题中乘号为**小写x**

```cpp
#include<cstdio>
#include<cstring>
#define maxn 15
int n,f[maxn][maxn],g[maxn][maxn],cnt;
struct node{
	int al,ar,yk,zk;
}a[maxn];
inline int Min(int x,int y){return x<y?x:y;}
void init(){
	memset(a,0,sizeof(a));
	memset(g,0,sizeof(g));
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;++i)scanf("%d %d",&a[i].al,&a[i].ar);
}
int solve(int l,int r){
	if(f[l][r]!=0x3f3f3f3f)return f[l][r];
	if(l>=r)return f[l][r]=0;
	int pos=0;
	for(int k=l;k<r;++k){
		int temp=solve(l,k)+solve(k+1,r)+a[l].al*a[k].ar*a[r].ar;
		if(temp<f[l][r])pos=k,f[l][r]=temp;
	}
	g[l][r]=pos;
	return f[l][r];
}
void dfs(int l,int r){
	if(l==r)return ;
	a[l].zk++,a[r].yk++;
	dfs(l,g[l][r]),dfs(g[l][r]+1,r);
}
void out(){
	printf("Case %d: ",++cnt);
	for(int i=1;i<=n;++i){
		if(i!=1)printf(" x ");
		while(a[i].zk)putchar('('),a[i].zk--;
		printf("A%d",i);
		while(a[i].yk)putchar(')'),a[i].yk--;
	}
	putchar('\n');
}
int main(){
	while(scanf("%d",&n)&&n){
		init();
		solve(1,n);
		dfs(1,n);
		out();
	}
	return 0;
}
```

---

## 作者：feizhu_QWQ (赞：0)

这道题我们先仔细分析，交换运算顺序是会导致计算次数不一样的，比如我们画个图：\
![](https://cdn.luogu.com.cn/upload/image_hosting/zyu2ro6s.png)\
两种情况，如果我们先把前两个矩阵相乘，那么我们的次数应该是 $3\times3\times2+3\times2\times1=24$。\
如果我们先把后两个矩阵相乘，那我们的次数应该是 $3\times2\times1+3\times3\times1=15$。\
我们可以发现，只要相邻两个矩阵的 $m$ 和 $n$ 相等，那么无论如何改变计算顺序，都能成功得出答案。\
可行性不用考虑了，我们现在来考虑怎么解决这个问题。\
这里贪心是不可能的，因为我们无法确定下一步怎么走。\
欸，数据不大，好像够 $n^3$ 的时间复杂度哦？\
而且我们每次把两个矩阵相乘就相当于合并两个区间。\
那么直接确诊区间 DP！\
这里我们每次区间 DP 的总次数就等于 $dp_{i,k}+dp_{k+1,j}+x_i\times y_k \times y_j$。\
后面的那一长串乘法代表我们计算两个矩阵相乘的次数，应该是 $n \times m \times k$。

解决完了计算过程，怎么输出呢？\
学过二叉树的初赛小竹子们都知道，有种遍历方式叫做中序遍历，和这里很像，所以我们在计算的时候顺便储存一下这个区间的分割点是哪一个就行了，然后中序遍历，先输出左括号，然后是数字和乘号，最后右括号。\
看起来处理很麻烦，其实二叉树可以解决一切问题。\
参考代码（勿抄袭）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int x[15],y[15];
int n,cnt=0;
int dp[15][15],ans[15][15];
void print(int l,int r)
{
	if(l==r)
	{
		cout<<"A"<<l;
		return;
	}
	cout<<"(";
	print(l,ans[l][r]);
	cout<<" x ";
	print(ans[l][r]+1,r);
	cout<<")";//中序遍历的处理
	return;
}
signed main()
{
	while(cin>>n)
	{
		if(n==0) break;
		cnt++;
		for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++) dp[i][j]=1e18;//初始化
			dp[i][i]=0;
		}
		for(int len=2;len<=n;len++)
		{
			for(int i=1;i<=n-len+1;i++)
			{
				int j=i+len-1;
				for(int k=i;k<j;k++)
				{
					if(dp[i][k]+dp[k+1][j]+x[i]*y[j]*y[k]<dp[i][j])
					{
						dp[i][j]=dp[i][k]+dp[k+1][j]+x[i]*y[k]*y[j];//计算乘法次数
						ans[i][j]=k;//存储分割点
					}
				}
			}
		}
		cout<<"Case "<<cnt<<": ";
		print(1,n);//中序遍历输出
		cout<<endl;
	}
	return 0;
} 
```

收工！

---

## 作者：InversionShadow (赞：0)

典中典。

易知两个矩阵 $a,b$，$a$ 的长为 $x$，宽为 $y$，$b$ 的长为 $y$，宽为 $z$，那么乘起来的贡献就是 $x\times y\times z$。

设 $f_{i,j}$ 表示 $i\sim j$ 的最小方案数，显然有：

$f_{i,j}=\begin{cases}0&i=j\\ \max\limits_{k=i}^{j-1}\{f_{i,k}+f_{k+1,j}+a_{l}\times b_{k}\times b
_{r}\}&i\neq j\end{cases}$

但是 UVA 输出格式毒瘤，在直接转移的时候很难记录，所以我们采用区间 dp 的另一种实现方法：记忆化搜索。

在记忆化搜索的时候记录一下断点 $k$，最后递归输出即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 30;

int n, dp[N][N], p[N][N], t, a[N], b[N], inf;

int DP(int l, int r) {
  if (l == r) {
    dp[l][r] = 0;
    return 0;
  }
  if (dp[l][r] != inf) {
    return dp[l][r];
  }
  for (int k = l; k < r; k++) {
    if (dp[l][r] > DP(l, k) + DP(k + 1, r) + a[l] * b[k] * b[r]) {
      dp[l][r] = DP(l, k) + DP(k + 1, r) + a[l] * b[k] * b[r];
      p[l][r] = k;
    }
  }
  return dp[l][r];
}

void solve(int l, int r) {
  if (l == r) {
    cout << "A" << r;
    return ;
  }
  cout << "(";
  solve(l, p[l][r]);
  cout << " x ";
  solve(p[l][r] + 1, r);
  cout << ")";
}

int main() {
  while (cin >> n && n) {
    memset(p, 0, sizeof(p));
    memset(dp, 63, sizeof(dp));
    inf = dp[1][1];
    for (int i = 1; i <= n; i++) {
      cin >> a[i] >> b[i];
    }
    DP(1, n);
    cout << "Case " << ++t << ": "; 
    solve(1, n);
    cout << '\n';
  }
  return 0;
}
```

---

## 作者：AlexandreLea (赞：0)

## 题目大意
给出 $n$ 个矩阵 $A_1,A_2,\cdots,A_n$ 的大小 $r_i\times c_i$，现在要将求 $A_1A_2\cdots A_n$，已知 $c_i=r_{i+1}$，并且每次乘法次数是 $r_ic_{i+1}r_{i+1}$，求怎样乘法可以使得乘法次数最小。

## 题目思路
一道经典的区间型动态规划（即区间 dp），我们可以设 $f_{i,j}$ 代表 $i\sim j$ 的最小乘法次数。

现在考虑乘法的位置，也即括号的分界点 $k$，该分界点 $k$ 将 $i\sim j$ 分成两部分 $i\sim k$ 和 $k+1\sim j$。另外，我们设 $s_{i-1}$ 为某矩阵的长，$s_i$ 为某矩阵的宽，我们就可以得到下列的式子：

$$f_{i,j}=\begin{cases}0&i=j\\\max_{k=i}^{j-1}f_{i,k}+f_{k+1,j}+s_{i-1}s_ks_j\end{cases}$$

这便是状态转移方程了。至于方案的输出，记录分界点 $k$ 即可。

代码如下：

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int n,s[15],f[15][15]={},p[15][15]={};
void out(int x,int y){
    if(x==y) cout<<"A"<<x;
    else{
        cout<<"(";
        out(x,p[x][y]);
        cout<<" x ";
        out(p[x][y]+1,y);
        cout<<")";
    }
}
int dp(int i,int j){
    if(~f[i][j]) return f[i][j];
    f[i][j]=0x3f3f3f3f;
    if(i==j) f[i][j]=0;
    else{
        for(int k=i;k<j;k++){
            if(f[i][j]>dp(i,k)+dp(k+1,j)+s[i-1]*s[k]*s[j]){
                f[i][j]=dp(i,k)+dp(k+1,j)+s[i-1]*s[k]*s[j];
                p[i][j]=k;
            }
        }
    }
    return f[i][j];
}
int main(){
    int _=0;
    while(cin>>n&&n!=0){
        memset(f,0xff,sizeof f);
        memset(p,0,sizeof p);
        for(int i=1;i<=n;i++) cin>>s[i-1]>>s[i];
        dp(1,n);
        cout<<"Case "<<(++_)<<": ";
        out(1,n);
        cout<<endl;
    }
    return 0;
}
```
**EOF**

---

