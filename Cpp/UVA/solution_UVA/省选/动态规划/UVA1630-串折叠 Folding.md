# 串折叠 Folding

## 题目描述

折叠由大写字母组成的长度为 $n$（$1\leqslant n\leqslant100$）的一个字符串，使得其成为一个尽量短的字符串，例如 `AAAAAA` 变成 `6(A)`。

这个折叠是可以嵌套的，例如 `NEEEEERYESYESYESNEEEEERYESYESYES` 会变成 `2(N5(E)R3(YES))`。

多解时可以输出任意解。

Translated by @_UKE自动机_

## 样例 #1

### 输入

```
AAAAAAAAAABABABCCD
NEERCYESYESYESNEERCYESYESYES```

### 输出

```
9(A)3(AB)CCD
2(NEERC3(YES))```

# 题解

## 作者：HUNGRY123 (赞：9)

**1.贪心？**  

显然 $\tt aa$ 时候折叠为 $\tt 2(a)$，比原串长，故贪心一定不对。

**2.动态规划** 

数据范围是 $n$ 小于等于 $100$，考虑时间复杂度为 $O(n^3)\sim O(n^4)$ 。

这时容易想到区间 dp，事实上这种关于字符串折叠的题，绝大多数都是区间 dp 。

那么考虑一般的思路：
1. 枚举每一段。 
2. 枚举断点。 
3. 考虑是否能够折叠进行转移。
```cpp
bool check(int l,int r,int len){//len是循环节的长度
	for(int i=l;i+len<=r;i++){
		if(ch[i]!=ch[i+len]) return false;
	}
	return true;
}
```


开始推式子：

若没有折叠，则有 `dp[l][r]=min(dp[l][i]+dp[i+1][r]);`。

然后发现折叠由三部分组成： 

1. 前面的数：长度就是这个数的位数。
```cpp
int ws(int n){
	int ans=0;
	while(n) ans++,n/=10;
	return ans; 
}
```
2. 括号：长度就是 $2$。 

3. 中间的字符串：字符串总长度与前面数字的商。 

然后就有了这一堆 dp 转移方程:
```cpp
for(int len=1;len<=a;len++){
	for(int l=1;l+len-1<=a;l++){
		int r=l+len-1;
		dp[l][r]=len;
		for(int i=l;i<=r;i++){
			if(dp[l][r]>dp[l][i]+dp[i+1][r]){
				k[l][r]=0;
				dp[l][r]=dp[l][i]+dp[i+1][r];
				cut[l][r]=i+1;
			}
			int llen=i-l+1;
			for(int ys=1;ys<=sqrt(llen);ys++){
				if(llen%ys) continue;
				if(check(l,i,ys)){//如果可以转移的话 
					if(dp[l][r]>ws(llen/ys)+2+dp[l][l+ys-1]+dp[i+1][r]){
						k[l][r]=llen/ys,cut[l][r]=l+llen/ys;
						dp[l][r]=ws(llen/ys)+2+dp[l][l+ys-1]+dp[i+1][r];
					}
				} 
				if(check(l,i,llen/ys)){//加上这个就可以在根号时间内完成转移 
					if(dp[l][r]>ws(ys)+2+dp[l][l+llen/ys-1]+dp[i+1][r]){
						k[l][r]=ys,cut[l][r]=l+llen/ys;
						dp[l][r]=ws(ys)+2+dp[l][l+llen/ys-1]+dp[i+1][r];
					}
				}
			}
		}
	}		
}
```
于是，[[SCOI2003]字符串折叠](https://www.luogu.com.cn/problem/P4302),这道题就能过掉了。 

本题还要输出答案，考虑递归输出。 

记录每个 `dp[l][r]` 转移点，如果它的前面是有倍数的话再记录这个倍数。 

搜到一个串 $l\sim r$ 时，先考虑这个字符串是否有折叠，若有折叠先搜索折叠的，然后再对剩余串进行操作。 

具体看代码：
```cpp
void dfs(int l,int r){
	if(k[l][r]){//如果有一个倍数 
		cout<<k[l][r]<<"(";//先输出倍数和一半括号 
		int rr=l+(r-l+1)/k[l][r]-1;
		dfs(l,rr);//只用递归它的循环节 
		cout<<")";//输出另外一半括号 
		return ;
	}
	if(!k[l][r]&&!cut[l][r]){//既没有断点又没有倍数，要直接输出 
		for(int i=l;i<=r;i++) cout<<ch[i];
		return ;
	}
	dfs(l,cut[l][r]-1);//其他一半一半继续 
	dfs(cut[l][r],r);
	return ;
}
```
这样这道题就做完了。 


还是再粘贴一下完整代码吧。（有函数后置的吗来报个道哈哈哈哈哈哈哈哈哈哈哈）
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[110];
int dp[110][110],a,b,k[110][110],cut[110][110];
bool check(int l,int r,int len);
int ws(int n);
void dfs(int l,int r);
int main(){

	while(scanf("%s",ch+1)!=EOF){
		a=strlen(ch+1);
		memset(dp,0,sizeof(dp));
		memset(k,0,sizeof(k));
		memset(cut,0,sizeof(cut));
		for(int len=1;len<=a;len++){
			for(int l=1;l+len-1<=a;l++){
				int r=l+len-1;
				dp[l][r]=len;
				for(int i=l;i<=r;i++){
					if(dp[l][r]>dp[l][i]+dp[i+1][r]){
						k[l][r]=0;
						dp[l][r]=dp[l][i]+dp[i+1][r];
						cut[l][r]=i+1;
					}
					int llen=i-l+1;
					for(int ys=1;ys<=sqrt(llen);ys++){
						if(llen%ys) continue;
						if(check(l,i,ys)){
							if(dp[l][r]>ws(llen/ys)+2+dp[l][l+ys-1]+dp[i+1][r]){
								k[l][r]=llen/ys,cut[l][r]=l+llen/ys;
								dp[l][r]=ws(llen/ys)+2+dp[l][l+ys-1]+dp[i+1][r];
							}
						} 
						if(check(l,i,llen/ys)){
							if(dp[l][r]>ws(ys)+2+dp[l][l+llen/ys-1]+dp[i+1][r]){
								k[l][r]=ys,cut[l][r]=l+llen/ys;
								dp[l][r]=ws(ys)+2+dp[l][l+llen/ys-1]+dp[i+1][r];
							}
						}
					}
				}
			}
		}
		dfs(1,a);
		putchar('\n');
	}
	return 0;
}
bool check(int l,int r,int len){
	for(int i=l;i+len<=r;i++){
		if(ch[i]!=ch[i+len]) return false;
	}
	return true;
}
int ws(int n){
	int ans=0;
	while(n) ans++,n/=10;
	return ans; 
}
void dfs(int l,int r){
	if(k[l][r]){//如果有一个倍数 
		cout<<k[l][r]<<"(";//先输出倍数和一半括号 
		int rr=l+(r-l+1)/k[l][r]-1;
		dfs(l,rr);//只用递归它的循环节 
		cout<<")";//输出另外一半括号 
		return ;
	}
	if(!k[l][r]&&!cut[l][r]){//既没有断点又没有倍数，要直接输出 
		for(int i=l;i<=r;i++) cout<<ch[i];
		return ;
	}
	dfs(l,cut[l][r]-1);//其他一半一半继续 
	dfs(cut[l][r],r);
	return ;
}
```



---

## 作者：SUNCHAOYI (赞：6)

本题是 [P4302 [SCOI2003]字符串折叠](https://www.luogu.com.cn/problem/P4302) 的强化版。

不难看出这是一个区间 dp，令 `dp[i][j]` 表示区间 $[l,r]$ 的最小长度。考虑两种操作：

- 合并两个小区间后变为一个大区间

- 将某个区间进行折叠

第一个操作，显然就是区间 dp 的套路方法，即：

```cpp
for (int k = l;k < r;++k)
    dp[l][r] = min (dp[l][r],dp[l][k] + dp[k + 1][r]);
```

第二个操作，对于一个 $[l,r]$ 的字符串，若要被折叠成长度为 $k$ 的字符串，在执行的时候需要满足 $1 \le k \le r - l + 1$ 且 $k \mid r - l +1$ 且 $\forall i \in [l,r - k]\ str[i] = str[i + k]$。符合要求，则可以转移 `dp[l][r] = min (dp[l][r],2 + calc ((r - l + 1) / k) + dp[l][l + k - 1])`。其中的 $2$ 即两个括号的长度，`calc (x)` 计算的是重复次数表示成字符串时的位数，`dp[l][l + k - 1]` 即循环节。

在得到最小长度后，由于需要输出合法的方案，所以我们在此基础上还要记录一些断点的信息，从而进行搜索。用两个数组分别记录第一和第二种的操作的断点，第一种操作记录断点的编号，第二种操作记录循环节的长度。由于一个区间的处理只进行一种操作，所以在标记时要把另外一种操作的断点设为 $0$。

在递归时，对于一个区间若两种断点均不存在，则直接输出这段区间；若是第一种操作的断点 $k$，则分别递归区间 $[l,k]$ 和 $[k + 1,r]$；若是第二种，则先输出左括号和重复的次数，递归循环节的区间，在输出右括号即可。

完整代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x,y) memset (x,y,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 105;
const int MOD = 1e9 + 7;
char str[MAX];
int n,dp[MAX][MAX],cut[MAX][MAX],fold[MAX][MAX];
void check (int l,int r,int k);
int calc (int num);
void dfs (int l,int r);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	while (scanf ("%s",str + 1) != EOF)
	{
		n = strlen (str + 1);
		init (dp,INF);init (cut,0);init (fold,0);//多测清空！
		for (int i = 1;i <= n;++i) dp[1][i] = i,dp[i][i] = 1;//初始化
		for (int i = 1;i <= n;++i)
		{
			for (int l = 1;l <= n;++l)
			{	
				int r = i + l;
				if (r > n) break;
				for (int k = 1;k <= (r - l + 1) / 2;++k) check (l,r,k);
				for (int k = l;k < r;++k)
				{
					if (dp[l][k] + dp[k + 1][r] < dp[l][r])//区间合并
					{
						dp[l][r] = dp[l][k] + dp[k + 1][r];
						cut[l][r] = k;
						fold[l][r] = 0;
					}
				}
			}
		}
		//printf ("%d\n",dp[1][n]);// 最小操作次数
		dfs (1,n);
		puts ("");
	} 
	return 0;
}
void check (int l,int r,int k)
{
	if ((r - l + 1) % k) return ;
	for (int i = l;i <= r - k;++i)
		if (str[i] != str[i + k]) return ;//不合法
	int s = 2 + calc ((r - l + 1) / k) + dp[l][l + k - 1];
	if (s < dp[l][r])
	{
		dp[l][r] = s;
		cut[l][r] = 0;
		fold[l][r] = k;//循环次数的记录
	}
}
int calc (int num)
{
	int cnt = 0;
	while (num) num /= 10,++cnt;
	return cnt;
}
void dfs (int l,int r)
{
	if (!cut[l][r] && !fold[l][r]) for (int i = l;i <= r;++i) printf ("%c",str[i]);//直接输出即可
	else if (cut[l][r]) dfs (l,cut[l][r]),dfs (cut[l][r] + 1,r);//分别递归两个区间
	else
	{
		printf ("%d(",(r - l + 1) / fold[l][r]);
		dfs (l,l + fold[l][r] - 1);//继续递归循环节
		printf (")");
	}
}
```

---

## 作者：星星之火 (赞：6)

这是DP，怎么转移请参考字符串折叠这题

当然这题的区别是要输出折叠之后的结果

经过本校Rye_Catcher大佬深入浅出的讲解，我们知道可以用string类型完美地解决这道题目

具体操作就是DP转移的时候对每一个状态再记录当前的字符串，用stringstream把数字转化成字符串，直接“加”起来就好

```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<sstream>
using namespace std;

const int N=100+15;
string s;
int n;
int f[N][N];
string q[N][N];
int check(int l,int m,int r)
{
	int len2=r-l+1,len1=m-l+1;
	if (len2%len1) return -1;
	int x=len2/len1;
	for (int i=1;i<=x;i++)
	{
		int tt=l+(i-1)*len1;
		for (int j=0;j<len1;j++)
		{
			if (s[l+j-1]!=s[tt+j-1]) return -1;
		}
	}
	return x;
}
int main()
{
	while (cin>>s)
	{
	memset(f,0x3f3f,sizeof(f));
	
	n=s.size();
	for (int i=1;i<=n;i++) 
	{
		f[i][i]=1;
		q[i][i]=s[i-1];
	}
	for (int len=2;len<=n;len++)
		for (int l=1;l<=n-len+1;l++)
		{
			int r=l+len-1;
			f[l][r]=len;
			q[l][r]=s.substr(l-1,len);
			//printf("%d %d ",l,r);
			//cout<<q[l][r]<<endl;
			for (int k=l;k<r;k++)
			{
				//f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
				if (f[l][k]+f[k+1][r]<f[l][r])
				{
					f[l][r]=f[l][k]+f[k+1][r];
					q[l][r]=q[l][k]+q[k+1][r];
				}
				int x=check(l,k,r);
				if (x!=-1)
				{
					int y=x,cnt=0;
					while (y) y/=10,cnt++;
					if (cnt+2+f[l][k]<f[l][r])
					{
						f[l][r]=cnt+2+f[l][k];
						stringstream op;
						op<<x;
						string pp;
						op>>pp;
						q[l][r]=pp+'('+q[l][k]+')'; 
					}
				}
			}
		}
	//printf("%d\n",f[1][n]);
	cout<<q[1][n]<<endl;
	}
	return 0;
}
```

---

## 作者：YCSluogu (赞：3)

## UVA 1630 题解

### 前言

不知道有多少人和我一样是从紫书上刷过来看到这道题的。

第一眼：这不就是[P4302](https://www.luogu.com.cn/problem/P4302)吗！！！高高兴兴领上双倍经验……

啧……好像和……那道……有那么亿点点不同？要输出方案？！还要记录转移、字符串重复的数量、记录各种乱七八糟的东西最后再来一个深搜来输出方案……看了看题解一个个近百行的代码……烦死了QAQ ~~我恨记录方案~~

### 分析

好吧其实是我们的惯性思维把这道题给想复杂了，其实没必要记录状态转移的。即使是我那种空行不要钱的码风都可以在50行就可以把题写出来。

如果有一定的区间DP的经验，其实可以很快分析出状态设计 $f_{l,r}$ 表示字符串 $str[l...r]$ 按照题意压缩后的字符串最短长度。对于状态 $f_{l, r}$，可以得到最简单的一个转移方程：$f_{l, r} = \underset{l \le k \le r}{min}\{ f_{l, k} + f_{k + 1, r} \}$。~~可是如果你没有压缩那转移的就是一个空气啊喂！~~ 至于压缩的转移，那就更简单了，只需要枚举子串 $str[l...k](l \le k \le r)$，然后暴力判断是否可以通过重复这个子串来得到 $str[l...r]$ 就可以了。

以上分析其实都很容易得到并且在 [P4302的题解区](https://www.luogu.com.cn/problem/solution/P4302) 有更详细的讨论。但是很多人到这一步的想法就是：记录状态转移。这样会让代码特别难看而且特别长。其实我们只需要更改一下状态 $f_{l, r}$ 从 `压缩后的字符串最短长度` 更改为 `压缩后最短的字符串`。这样在状态转移时就顺便把方案给记下来了、不需要额外记录状态转移。

### 代码

``` cpp
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;

std::string str;
const int kMaxN = 120;

std::string ans[kMaxN][kMaxN];

bool check(int l, int r, int len) {
  if ((r - l + 1) % len) return false;
  for (int i = l; i <= r; i++) {
    if (str[i] != str[(i - l) % len + l]) return false;
  }
  return true;
}

void solve() {
  int n = str.size();
  str = '#' + str;
  for (int len = 1; len <= n; len++) {
    for (int l = 1, r = len; r <= n; l++, r++) {
      ans[l][r] = str.substr(l, len);
      for (int k = l; k < r; k++) {
        int len = k - l + 1;
        // 判断左右两个字符串凭借后是否会梗短
        if (ans[l][k].size() + ans[k + 1][r].size() < ans[l][r].size()) {
          ans[l][r] = ans[l][k] + ans[k + 1][r];
        }
        // 判断是否可以压缩
        if (check(l, r, len)) {
          int word = (r - l + 1) / len;
          std::string temp = std::to_string(word) + "(" + ans[l][k] + ")";
          if (temp.size() < ans[l][r].size()) {
            ans[l][r] = temp;
          }
        }
      }
    }
  }
  cout << ans[1][n] << endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  while (cin >> str) { solve(); }
  return 0;
}
```

---

## 作者：_cmh (赞：3)

[原题传送门](https://www.luogu.com.cn/problem/UVA1630)

[双倍经验（比这题简单）](https://www.luogu.com.cn/problem/P4302)

## $\texttt{Description}$

折叠由大写字母组成的长度为 $n$ 的一个字符串，使得其成为一个尽量短的字符串，例如 `AAAAAA` 变成 `6(A)`。

这个折叠是可以嵌套的，例如 `NEEEEERYESYESYESNEEEEERYESYESYES` 会变成 `2(N5(E)R3(YES))`。

## $\texttt{Solution}$

看到字符串的**区间**压缩，易想到 **区间 DP**。

我们设 $dp_{i,j}$ 为字符串的 $i\sim j$ 折叠后的长度，$ans_{i,j}$ 用来记录答案（`string` 类型）。

初始化，将 $dp_{i,i}$ 赋值为 $1$，$ans_{i,i}$ 为 $s_i$。

容易写出 区间 DP 的基本状态转移方程：

$$dp_{i,j}=\min\left(dp_{i,j},dp_{i,k}+dp_{k+1,j}\right)$$

$ans_{i,j}$ 跟随 $dp$ 数组进行更新。

然后我们来处理压缩的问题。

首先写一个函数 `check`，判断该区间是否能够被折叠。令该区间长度为 $d$ ，折叠部分的长度为 $len$，判断数字长度的函数为 `num` ，则可以写出状态转移方程 2：

$$dp_{i,j}=\min\left(dp_{i,j},dp_{i,k}+num(d\div len)+2\right)$$

其中 `+2` 是加上两个括号的长度。

注意更新 $ans$ 的时候，将 $d\div len$ 通过 `stringstream` 转化成字符串放入答案中。

最后输出 $ans_{1,n}$ 即为答案。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int dp[N][N];
string ans[N][N];
bool judge(string s,int l,int r,int mod){
	for(int i=l;i<=r;i++)
		if(s[l+(i-l)%mod]!=s[i])
			return false;
	return true;
}
void real_main(string s){
	s=' '+s;
	int n=s.length()-1;
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;i++){
		dp[i][i]=1; 
		ans[i][i]=s[i];
	}
	for(int d=1;d<=n;d++)
		for(int i=1;i<=n-d+1;i++){
			int j=i+d-1;
			dp[i][j]=d;
			ans[i][j]=s.substr(i,d);
			for(int k=i;k<j;k++){
				int now=dp[i][k]+2+(d/(k-i+1)==100?3:(d/(k-i+1)>=10?2:1));
				if(judge(s,i,j,k-i+1)&&d%(k-i+1)==0&&now<dp[i][j]){
					dp[i][j]=now;
					int zh=d/(k-i+1);
					stringstream stm;
					stm<<zh;
					string zhh;
					stm>>zhh;
					ans[i][j]=zhh+'('+ans[i][k]+')';
				}
				if(dp[i][k]+dp[k+1][j]<dp[i][j]){
					dp[i][j]=dp[i][k]+dp[k+1][j];
					ans[i][j]=ans[i][k]+ans[k+1][j];
				}
			}
		}
	cout<<ans[1][n]<<endl;
} 
int main(){
	string s;
	while(cin>>s)
		real_main(s);
    return 0;
}
```

感谢观看。

---

## 作者：Lily_White (赞：2)

TLDR: 区间 DP

定义 $f(l,r)$ 为区间 $[l,r]$ 内字符串 $s$ 的最佳折叠。定义 $R(l,r)$ 为 $[l, r]$ 区间内最短的循环节长度。

这里可以直接按照最短的循环节计算，因为即使选择更长的循环节来减少前面的数字也一定不会让结果更优。

转移如下

$$
f(l,r)=\min^{r}_{k=l}\{f(l, k)+f(k+1,r), R(l,r)+\texttt{( } + f(l, l +R(l,r)-1)+\texttt{)}\}
$$

实现时，选用迭代式 DP 更容易。可以直接把字符串存到 DP 数组里面去。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define y1 y114514
#define elif else if
#define VPII vector <PII>
#define y2 y1919810
typedef pair <int, int> PII;
typedef vector <int> VI;
//#define int long long
#define all(x) x.begin(),  x.end()
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int i = 1; i <= (int)n; i++)
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define range(i, s, t)  for (int i = s; i <= (int)t; i++)
#define il inline
#define RESET(x) memset((x), 0, sizeof(x))


const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
string s;
LL qread() {
    char c = getchar();
    int neg = 1;
    LL val = 0;
    while (c != '-' && !isdigit(c)) c = getchar();
    if (c == '-') {
        c = getchar(); 
        neg = -1;
    }
    while (isdigit(c)) {
        val = (val << 3) + (val << 1) + c - '0';
        c = getchar();
    }
    return neg * val;
}
int getRepl(int l, int r) {
    int len = r - l + 1;
    int ans = 0;
    repn(repl, len / 2) {
        if (len % repl) continue;   
        bool good = true;
        range(i, l, r - repl) {
            if (s[i] != s[i + repl]) {
                good = false;
                break;
            }
        }
        if (good) {
            ans = repl;
            break;
        }
    }

    return ans;
}
int getLength(int x) {
    int res = 0;
    while (x) {
        x /= 10;
        res++;
    }
    return res;
}
string dp[102][102];
void DP(int l, int r) {
    int bestk = -1, best = INF;
    for (int k = l; k < r; k++)
        if (best > dp[l][k].size() + dp[k + 1][r].size()) {
            best = dp[l][k].size() + dp[k + 1][r].size();
            bestk = k;
        }
    int k = bestk;
    dp[l][r] = dp[l][k] + dp[k + 1][r];
    int repl = getRepl(l, r);
    if (repl) {
        stringstream ss;
        string tmp; string tnum;
        ss << (r - l + 1) / repl;
        ss >> tnum;
        tmp = tnum + "(" + dp[l][l + repl - 1] + ")";
        if (best > tmp.length()) dp[l][r] = tmp; 
    }
}
void solve() {
    rep(i, 101) rep(j, 101) dp[i][j].clear();
    int n = s.length();
    rep(i, n) dp[i][i] = s[i];
//    for (int l = 0; l < n; l++)
    for (int l = n - 2; l >= 0; l--)
        for (int r = l + 1; r < n; r++)
            DP(l, r);
    cout << dp[0][n - 1] << endl;
}
signed main() {
    while (cin >> s && s.length()) 
        solve();
    return 0;
}
```

---

## 作者：__Remake__ (赞：1)

蒟蒻的第一篇题解 OvO

定义 $dp_x$ 表示字符串 $x$ 能够被压缩到的最短长度， $len(x)$ 表示 $x$ 的长度， $g_x$ 表示字符串 $x$ 被压缩到最短长度时的压缩方案。

对于 $x$ ，我们可以进行以下两种操作：
+ 直接将 $x$ 压缩。
+ 将 $x$ 分成两份分别操作后合并。

对于操作一，假设 $x$ 可以被压缩成 $x'$ ，则 $dp_x = \min(dp_x,dp_{x'})$ ， $g_x = g_{x'}(dp_{x'} < dp_x)$

对于操作二，将 $x$ 从中间断开，分成两个子串 $x_1$ 和 $x_2$ ，则 $dp_x = \min(dp_x,dp_{x_1} + dp_{x_2})$ ， $g_x = g_{x_1} + g_{x_2}(dp_{x_1} + dp_{x_2} < dp_x)$

同时，对于任意一个 $x$ ，对它不进行任何操作一定是合法的（但不一定最优），所以我们可以对 $dp_x$ 赋初值 $len(x)$ ，对 $g_x$ 赋初值 $x$ 。

最后用 $map$ 存 $dp_x$ 和 $g_x$ ，用记搜实现即可。

关于实现的一些细节：
+ 如果字符串 $x$ 以 $l$ 为循环节循环，令 $x_i$ 表示 $x$ 中第 $i$ 个字符，则有 $x_i = x_{i\ mod\ l}$ ，所以扫一遍 $x$ 并判断 $x_i = x_{i\ mod\ l}$ 是否都成立即可判断 $x$ 是否以 $l$ 为循环节循环。
+ 压缩后的 $x'$ 是一个形如 $N(...)$ 的字符串，$N$有可能是两位及以上的数，需要注意一下。

最后给出代码。

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <map>

#define INF 0x3f3f3f3f
#define min(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

string s, ans;

map <string, int> dp;

map <string, string> g;

inline bool checker(string pd, int loop) {
	int lg = pd.size();
	if(lg % loop != 0 || loop == lg)
		return false;
	for(int i = 0; i < lg; i++)
		if(pd[i] != pd[i % loop]) {
			return false;
		}
	return true;
}

inline string getn(int x) {
	string ret;
	int tmp[4] = {0, 0, 0, 0};
	int cnt = 0;
	while(x > 0) {
		tmp[++cnt] = x % 10;
		x /= 10;
	}
	for(int i = cnt; i >= 1; i--)
		ret += char(tmp[i] + '0');
	return ret;
}

void dfs(string x) {
	if(dp[x] != 0)
		return ;
	int lg = x.size();
	dp[x] = lg;
	g[x] = x;
	if(lg == 1)
		return ;
	for(int i = 1; i * i <= lg; i++) {
		int lgt1 = i, lgt2 = lg / i;
		if(lg % i != 0)
			continue;
		if(checker(x, lgt1)) {
			int nt = lg / lgt1;
			string nxt;
			nxt += getn(nt);
			nxt += '(';
			nxt += x.substr(0, lgt1);
			nxt += ')';
			dfs(nxt);
			if(dp[nxt] < dp[x])
				g[x] = g[nxt];
			dp[x] = min(dp[x], dp[nxt]);
		}
		if(checker(x, lgt2)) {
			int nt = lg / lgt2;
			string nxt;
			nxt += getn(nt);
			nxt += '(';
			nxt += x.substr(0, lgt2);
			nxt += ')';
			dfs(nxt);
			if(dp[nxt] < dp[x])
				g[x] = g[nxt];
			dp[x] = min(dp[x], dp[nxt]);
		}
	}
	for(int i = 0; i < lg - 1; i++) {
		string lft = x.substr(0, i + 1);
		string rgt = x.substr(i + 1, lg - i - 1);
		dfs(lft); dfs(rgt);
		if(dp[x] > dp[lft] + dp[rgt])
			g[x] = g[lft] + g[rgt];
		dp[x] = min(dp[x], dp[lft] + dp[rgt]);
	}
	return ;
}

int main() {
	while(cin >> s) {
		dfs(s);
		cout << g[s] << endl;
	}
	return 0;
}

```

---

## 作者：wcyQwQ (赞：1)



[题目传送门](https://www.luogu.com.cn/problem/UVA1630)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/05/04/UVA1630%20Folding/)

## 前言

[双倍经验](https://www.luogu.com.cn/problem/P4302)

### 前置芝士

区间DP

## 分析

这是一道 DP 输出方案的题目，遇到这种题目不要慌，DP 输出方案大致分为两个步骤: 1.找答案 2. 记录步骤。

题目要求我们求字符串的最短折叠，那我们不妨把字符串的最短折叠长度求出来。

我们用 $f[l][r]$ 表示字符串 $[l, r]$ 这一段最短折叠的长度，用 $num[i]$ 表示数字 $i$ 的长度(如 $num[10]=2$ )，然后我们可以得出方程。

1. 如果我们不折叠，那么我们有 $f[l][r] = \min(f[l][r] + f[l][k] + f[k + 1][r]) (l \le k <r)$ 
2. 如果我们折叠，我们设折叠的一段为 $[l, k]$ , 然后我们判断一下 $[l, r]$ 能否由 $[l,k]$ 折叠得到，如果可以，我们有 $f[l][r] = \min(f[l][r], f[l][k] +num[(r - l +1) / (r - k +1)] + 2)$ 最后加的 $2$  表示一对括号的长度。

因为我们要输出方案，所以我们在 DP 的过程中记录一下取到 $f[l][r]$ 最小值的中转点 $k$，并用 $p[l][r]$ 表示，并用 $fold[l][r]$ 表示 $[l, r]$ 是否折叠。

然后我们递归输出最短折叠，用 `print(l, r)` 来输出 $[l, r]$ 的最短折叠，下面我们来分类讨论一下。

1. 如果 `l == r` 那么我们直接输出 $a[l]$ ( $a$ 表示原字符串)
2. 如果 `fold[l][r] == 0` 那么说明这一段没有折叠，直接执行 `print(l, p[l][r])` 和 `print(p[l][r] + 1, r)`
3. 如果 `fold[l][r] == 1` 那么说明这一段有折叠，我们先把左括号和折叠次数打出来，然后把折叠的一段输出出来，也就是 `print(l, p[l][r])`, 最后再把右括号打印出来。

注意我们是多组数据，所以在输出完毕后要加一个换行符。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 110;
char a[N];
int num[N];
int f[N][N];
int p[N][N];
bool fold[N][N];

inline bool check(int l, int r, int len) // 判断 [l,r] 能否折成每段 len 个字符
{
    for (int i = l; i <= r - len; i++)
        if (a[i] != a[i + len]) return false;
    return true;
}

inline void print(int l, int r)
{
    if (l == r)
    {
        putchar(a[l]);
        return;
    }
    if (!fold[l][r])
    {
        print(l, p[l][r]);
        print(p[l][r] + 1, r);
        return;
    }
    else
    {
        printf("%d(", (r - l + 1) / (p[l][r] - l + 1));
        print(l, p[l][r]);
        putchar(')');
        return;
    }
}

int main()
{
    for (int i = 1; i <= 100; i++)
        num[i] = num[i / 10] + 1; // 预处理num[i]
    while (cin >> a + 1)
    {
        int n = strlen(a + 1);
        memset(f, 0x3f, sizeof f);
        memset(p, 0, sizeof p);
        memset(fold, 0, sizeof fold);
        for (int i = 1; i <= n; i++)
            f[i][i] = 1;
        for (int len = 2; len <= n; len++)
            for (int l = 1; l + len - 1 <= n; l++)
            {
                int r = l + len - 1;
                for (int k = l; k < r; k++)
                {
                    if (f[l][r] > f[l][k] + f[k + 1][r])
                    {
                        f[l][r] = f[l][k] + f[k + 1][r];
                        p[l][r] = k;
                    }
                }
                for (int k = l; k < r; k++)
                {
                    int a = k - l + 1;
                    if (len % a) continue;
                    if (check(l, r, a) && f[l][r] > f[l][k] + num[len / a] + 2)
                    {
                        f[l][r] = f[l][k] + num[len / a] + 2;
                        fold[l][r] = true;
                        p[l][r] = k;
                    }
                }
            }
        print(1, n);
        puts("");
    }
    return 0;
}
```





---

## 作者：BzhH (赞：1)

看完题目和数据范围，很容易想到这是一道区间DP，即设$f[i][j]$表示合并字符串第$i$位到第$j$位过后的最小长度,那么该如何转移这个状态?

首先讲一下我最开始的思路:用一个数组$minn[i][j]$把每一个状态得到的字符串分别存起来,然后在暴力枚举区间判断是否相等,但是这种做法会非常麻烦,并且还会超时,因为我们存的是每一个状态的字符串,不好判断两个区间的循环节是否相等,所以明显不行,那么就再考虑用一个数组$m[i][j]$把每一种状态的循环节也存下来同时用一个数组$cir[i][j]$把每个循环节前的系数存下来,这样就可以省去一层判断循环节是否相等的循环.

那么就可以得出状态转移方程
$\begin{cases}f_{i,j}=\min(f_{i,k}+2+fws(cir_{i,k})),l \le k < r,m_{i,k}=m_{k+1,r}\\f_{i,j}=\min(f_{i,k}+f_{k+1,r}),l\le k<r,m_{i,k}\ne m_{k+1,r}\end{cases}$

这里的$fws$表示求一个数的位数,得出状态转移方程,但这个题要我们输出序列,其实就是$minn$,这个数组可以同$f$一起更新,其余细节代码里将给出注释

代码如下

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;

int f[205][205];
string m[205][205];
string minn[205][205];
int cir[205][205];

int fws(int a)//得出a的位数
{
	if(a == 1)
		return 0;
    int res = 0;
    while(a)
    {
        res++;
        a /= 10;
    }
    return res;
}

string cov(int n)//将一个数变为字符串
{
	string res = "";
	if(n == 1)
		return res;
	while(n)
	{
		res += n % 10 + '0';
		n /= 10;
	}
	reverse(res.begin(), res.end());
	return res + "(";
}

void work(int l,int k,int r)
{
	if(m[l][k] == m[k + 1][r])//判断循环节是否相等
    {	
        int num = fws(cir1[l][k] + cir[k + 1][r]);//得出新的循环次数的位数
		m[l][r] = m[l][k];//更新循环节
		cir[l][r] = cir[l][k] + cir[k + 1][r];//更新循环次数
		if(num + 2 + m[l][k].length() < f[l][r])//转移状态
		{
	        f[l][r] = num + 2 + m[l][k].length();  
			minn[l][r] = cov(cir[l][r]) + m[l][r] + (cir[l][r] == 1 ? "" : ")");//更新序列,如果循环次数为一,那么就不用加括号.
		}
    }
	string temp = minn[l][k] + minn[k + 1][r];//另一种情况
	if(temp.length() < m[l][r].length() || m[l][r] == "")
	{
		m[l][r] = temp;
		cir1[l][r] = 1;
	}//直接合并得到的循环节更优
    if(temp.length() < f[l][r])//转移状态
    {         
		f[l][r] = temp.length();
		minn[l][r] = temp;
    }    
}

int main()
{
	string s;
	while(cin >> s)
	{
		for(int i = 0; i <= 100; i++)
			m[i].clear(), minn[i].clear();
		memset(cir1, 0, sizeof(cir1));
		memset(f, 0x3f, sizeof(f));
		int n = s.length();
	    for (int i = 1; i <= n;i++)
	    {
	        f[i][i] = 1;
	        minn[i][i] = s[i - 1];
	        m[i][i] = s[i - 1];
	        cir[i][i] = 1;
	    }//以上为初始化
	    for (int len = 2; len <= n;len++)
	    {
	        for (int l = 1; l <= n - len + 1;l++)
	        {
	            int r = l + len - 1;
	            for (int k = l; k < r; k++)
	                work(l, k, r);//枚举区间左端点,右端点以及分割点
	        }
	    }
	    cout << minn[1][n] << endl;	//输出答案	
	}
	return 0;
}
```



---

## 作者：Coros_Trusds (赞：0)

# 题目大意

折叠由大写字母组成的长度为 $n$（$1\leqslant n\leqslant100$）的一个字符串，使得其成为一个尽量短的字符串，例如 `AAAAAA` 变成 `6(A)`。

这个折叠是可以嵌套的，例如 `NEEEEERYESYESYESNEEEEERYESYESYES` 会变成 `2(N5(E)R3(YES))`。

多解时可以输出任意解。

# 题目分析

先来考虑一下该题的简单版：[$\texttt{\color{black}字符串折叠}$](https://www.luogu.com.cn/problem/P4302)（双倍经验

令 $dp[l][r]$ 表示区间 $l\sim r$ 内折叠后的长度。

显然的，我们枚举断点 $k(l\le k\lt r)$，有 

$$dp[l][r]=\min(dp[l][r],dp[l][k]+dp[k+1][r])$$

然后考虑折叠。

判断折叠的函数：

```cpp
inline bool mat(int l,int r,int len)
{
	for(register int i=l;i<=r;i++)
	{
		if(str[i]!=str[(i-l)%len+l])
		{
			return false;
		}
	}
	
	return true;
} 
```
-----

折叠由三部分组成：

+ 前面的数字。

这里就是这个数的位数，因此我们可以先预处理出 $0\sim 100$ 的位数。

具体地，令 $tmp[i]$ 表示 $i$ 的位数。

+ 括号，长度为 $2$。

+ 里面的字符串。

再次枚举断点 $k(l\le k\lt r)$。

此时，长度为 $dp[l][r]=\min(dp[l][r],dp[l][k]+2+tmp[len/(k-l+1))$。

并且应当满足 $len$ 为 $k-l+1$ 的倍数，且 `mat(l,r,k-l+1)==true`。

最后答案就是 $dp[1][n]$。

------
本题要求输出方案，于是用 $ans[i][j]$ 记录答案，$\verb!DP!$ 时转移即可。

---

## 作者：raincity (赞：0)

## 题意

定义：$n(str)$表示$n$个$str$相连接构成的字符串，其中$n\in Z^+$，$str$是一个字符串。当$n=1$，应该直接写成$str$。

给定一个字符串，要求用上面的方法最短地表示这个字符串，求这个最短长度和表示方法。原字符串长度$\le 100$。

## 分析

首先发现这个字符串好短，考虑区间DP~~明明就是因为教练把这道题放在了区间DP练习题~~。

不会的可以先看一看经典题：[石子合并](https://www.luogu.com.cn/problem/P1880)。

这里不再介绍区间DP~~套路~~框架，只介绍如何转移和输出。

### 转移

$dp_{i,j}$表示表示从$i$到$j$的子串所需要的最短长度。

1. 直接从中间分开，分别表示两边。$dp_{i,j} = \min {dp_{i,k}+dp_{k+1,j}}, i \le k < j$。

2. 进行折叠。枚举折叠长度$k|(j-i+1)$，判断是否能够折叠，如果能够折叠，$dp_{i,j}$还需要和$o_{\frac{(j-i+1)}{k}}+dp_{i,i+k-1}+2$取$\min$,其中$o$表示位数。

**注意：**$dp_{i,i+k-1}$不能写成$k$，不然会 WA （我就死在这里。。。）

这里感谢 metaphysis 的 hack 数据：

`UUUUUUUGLUUUUUUUGLZ`

正确输出：`2(7(U)GL)Z`

### 输出

定义递归输出函数`output_string(i,j)`表示从$i$到$j$的子串最短的折叠。

DP 时记录前缀$pre$，如果使用第一种方式转移$pre_{i,j}=k$，否则$pre_{i,j}=-k$。

对于`output_string(i,j)`:

若$pre_{i,j}>0$，返回`output_string(l, pre[l][r]) + output_string(pre[l][r] + 1, r)`。

否则返回`tostring(-(r - l + 1) / pre[l][r]) + "(" + output_string(l, l - pre[l][r] - 1) + ")"`

（这里使用C++语法）

`tostring`是什么意思呢？`tostring(x)`表示把整形$x$转成字符串（C++需要，说不定某一些别的语言不需要）。

我们可以运用语言特性：`streamstring`大法！

不会的请自行 bdfs。

这里放上C++代码：

```cpp
string tostring(int x) {
    stringstream st;
    st << x;
    string res;
    st >> res;
    return res;
}
```

## 解答

放上代码：

```cpp
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

const int N = 105;
string s;
int dp[N][N], pre[N][N], o[N], n;

string tostring(int x) {
    stringstream st;
    st << x;
    string res;
    st >> res;
    return res;
}

string output_string(int l, int r) {
    if (l > r)
        return "";
    if (l == r)
        return s.substr(l, 1);
    if (pre[l][r] < 0)
        return tostring(-(r - l + 1) / pre[l][r]) + "(" + output_string(l, l - pre[l][r] - 1) + ")";
    return output_string(l, pre[l][r]) + output_string(pre[l][r] + 1, r);
}

bool canfold(int l, int r, int x) {
    for (int i = l + x; i <= r; i += x)
        if (s.substr(l, x) != s.substr(i, x))
            return false;
    return true;
}

void DP() {
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) dp[i][i] = 1;
    for (int len = 2; len <= n; len++)
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            for (int k = i; k < j; k++)
                if (dp[i][k] + dp[k + 1][j] < dp[i][j])
                    dp[i][j] = dp[i][k] + dp[k + 1][j], pre[i][j] = k;
            for (int k = 1; k <= len; k++) {
                if (len % k)
                    continue;
                if (canfold(i, j, k) && 2 + dp[i][i + k - 1] + o[len / k] < dp[i][j])
                    dp[i][j] = 2 + dp[i][i + k - 1] + o[len / k], pre[i][j] = -k;
            }
        }
}

int main() {
    for (int i = 0; i <= 100; i++) {
        if (i < 10) o[i] = 1;
        else if (i < 100) o[i] = 2;
        else o[i] = 3;
    }
    while (cin >> s) {
        n = s.size();
        s = ' ' + s;
        DP();
        cout << output_string(1, n) << endl;
    }
    return 0;
}
```

#### The End


---

