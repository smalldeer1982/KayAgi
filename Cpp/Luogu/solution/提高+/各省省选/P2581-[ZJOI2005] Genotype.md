# [ZJOI2005] Genotype

## 题目背景

Genotype 是一个独特的基因串。

## 题目描述

我们可以用大写英文字母 $A-Z$ 来描述 Genotype，每个字母就代表一个基因。

规定一种「分裂」规则，由三个大写字母 $A_1A_2A_3$ 组成，代表 $A_1$ 可以「分裂」为 $A_2A_3$。

现在给定 $n$ 个「分裂」规则和 $k$ 个 Genotype，判断这些 Genotype 是否能从一个特定的 **只包含大写字母 $S$ 的** 串通过「分裂」规则得到，如果可以的话输出特定的串的长度的最小值，如果不可以的话输出 `NIE`。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le n,k \le 2000$，Genotype 的长度最大为 $100$。

## 样例 #1

### 输入

```
6
SAB
SBC
SAA
ACA
BCC
CBC
3
ABBCAAABCA
CCC
BA```

### 输出

```
3
1
NIE```

# 题解

## 作者：hewo (赞：2)

本题题目、样例有误。

正确的题面：

[洛谷P6701](https://www.luogu.com.cn/problem/P6701)

[LOJ](https://loj.ac/problem/2889) (数据水一点)


使用区间DP+状压：

转化为将给定的字符串能压缩成的**只含有 S 的最短字符串**。  

对于给定的分裂（合并）规则，也就是两个字符合并为一个字符，我们用状压思想，以二进制来存储这两种字符可以合并为那些种类的字符，也就是:

```cpp
c[get(ins[1])][get(ins[2])]|=(1<<(get(ins[0])));
```

再考虑如何DP。

设 $dp_{i,j}$ 表示区间 $[i,j]$ 中的答案，$git_{i,j}$ 表示区间 $[i,j]$ 可以合并成为那些字符。

在进行区间DP的同时，更新 $git_{i,j}$，如果合并出了 S，则 $dp_{i,j}=1$。

我们还可以进行一些优化：

1. 开小数组。
2. 很多大佬采用的是枚举每个字符，其实可以直接存每一种合并，再来枚举，这样会快一些。

具体看代码吧，还是比较好理解的。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MX=105;
#define LL long long
#define inf 0x3f3f3f3f

#define modn 10000

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}

int m;//规则数

char ins[10];
int c[30][30];//合并用

int git[MX][MX];

char s[MX];
int n;

inline int get(char x)
{
	return x-'A'+1;//1~26
}

int dp[MX][MX];

inline void csh()
{
	memset(dp,0x3f,sizeof(dp));
	memset(git,0,sizeof(git));
}

struct tCod
{
	int x,y;
}cod[800];
int idx=0;

int main(int argc, char const *argv[])
{
	m=read();
	for(int i=1;i<=m;i++)
	{
		scanf("%s",ins);
		if(c[get(ins[1])][get(ins[2])]==0)
		{
			cod[++idx]=tCod{get(ins[1]),get(ins[2])};
		}
		c[get(ins[1])][get(ins[2])]|=(1<<(get(ins[0])));

	}
	int T;
	T=read();
	while(T--)
	{
		csh();
		scanf("%s",s+1);
		n=strlen(s+1);
		for(int i=1;i<=n;i++)
		{
			if(s[i]=='S')
			{
				dp[i][i]=1;
			}
			git[i][i]|=(1<<(get(s[i])));
		}
		for(int len=0;len<n;len++)
		{
			for(int l=1;l+len<=n;l++)
			{
				int r=l+len;
				//l~k k+1~r
				for(int k=l;k<=r-1;k++)
				{
					dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
					for(int q=1;q<=idx;q++)
					{
						int x=cod[q].x,y=cod[q].y;
						if(c[x][y])//如果这两个字符能合并
						{
							//git是放单字符的多情况的，如果能合并的话就合并，一个区间合并成一个字符，然后记录这一个字符有多少种情况
							if((git[l][k]&(1<<(x)))&&((git[k+1][r])&(1<<(y))))
							{
								git[l][r]|=c[x][y];
								//printf("%d %d %d %d\n",l,k,r,c[x][y]);
							}
						}
					}	
					if((git[l][r]&(1<<(get('S')))))
					{
						dp[l][r]=1;//如果合并出S了，就直接变成1
					}
				}
			}
		}
		if(dp[1][n]==inf) printf("NIE\n");
		else printf("%d\n",dp[1][n]);
	}
	return 0;
}
```

---

## 作者：Para (赞：2)

## [正确题面](https://loj.ac/problem/2889)

## 大致思路

 $\ \ \ \ \ $ 这是一道很棒的区间 $DP$
 
 
 $\ \ \ \ \ $ 题目要求该字符串最少由多少个 $S$ 组成，我们可以将每个 $S$ 分开讨论。
 
 
 $\ \ \ \ \ $ 定义 $dp_i$ 为前 $i$ 个字符最少由多少个 $S$ 组成，则答案为  $dp_t$ ($t$ 表示每个字符串的长度)
 
 
 $\ \ \ \ \ $考虑转移方程，当区间 $[j + 1, i]$ 可以通过某种装换变到 $S$ 时，易得转移方程
$dp_i = min (dp_i, dp_j + 1)$


 $\ \ \ \ \ $接下来，我们只需要考虑如何判断在 $[l, r]$ 的区间内可否转换为一个字符 $x$ ($x$ 不一定为 $S$)
 
 
 $\ \ \ \ \ $定义 $vis[x][l][r] == 1/0$为在区间 $[l, r]$ 中 可以/不可以 造出字符 $x$
 
 
 $\ \ \ \ \ $方程 : $vis[x][l][r] = max (vis[x][l][r], vis[y1][l][k] * vis[y2][k+1][r])$ 
 
  
 $\ \ \ \ \ $(其中字符 $x$ 可以变为 $y1$ 与 $y2,i <= k < j$)
 
## 代码：
```cpp
#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
char ch[105];
int dp[105];
vector <pair <int, int> > G[10005];
int vis[105][105][105];
int find_ans (int s, int l, int r) {//记忆化搜索寻找答案
	if (vis[s][l][r] != -1) return vis[s][l][r];
	if (l == r && s == ch[l]) return vis[s][l][r] = 1;
	for (int i = l; i <= r - 1; i++) {
		for (int w = 0; w < G[s].size(); w++) {
			int x = G[s][w].first, y = G[s][w].second;
			if (find_ans (x, l, i) == 1 && find_ans (y, i + 1, r) == 1) return vis[s][l][r] = 1;
		}
	}
	return vis[s][l][r] = 0;
}
int main () {
	int n;
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++) {
		char ch1, ch2, ch3;
		cin >> ch1 >> ch2 >> ch3;
		G[ch1].push_back(make_pair(ch2, ch3));//用 pair 存储更方便
	}
	int T;//注意：多组输入
	scanf ("%d", &T);
	while (T--) {
		memset (dp, 0x3f, sizeof dp);
		memset (vis, -1, sizeof vis);
		scanf ("%s", ch + 1);
		int len = strlen(ch + 1);//数组下表从 1 开始
		dp[0] = 0;
		for (int i = 1; i <= len; i++) {
			for (int j = 0; j < i; j++) {
				if (dp[j] + 1 < dp[i] && find_ans ('S', j + 1, i)) {
					dp[i] = dp[j] + 1;//答案要求最小，所以取min
				}
			}
		}
		if (dp[len] > 999999999) printf ("NIE\n");
		else printf ("%d\n", dp[len]);
	}
	return 0;
}
```

---

## 作者：GFyyx (赞：0)

## 题目大意
给定 $n$ 个分裂方式，以及 $t$ 个询问。

对于每个询问，求是否能用仅包含大写字母 ```S``` 的字符串分裂成目标字符串 $str$。

如果可以，输出特定字符串长度的最小值，否则输出 ```NIE```。

## 解题思路
如果顺着搜索特定字符串的分裂方式，搜索的深度和广度都很奆。

正难则反，我们考虑将目标字符串合并成仅含有 ```S``` 的特定字符串。

题目给定的目标字符串只含有 26 个大写字母，而整型变量有 32 位，这让我们想到了状态压缩。

用 $f_{i,j}$ 表示区间 $[i,j]$ 可以变成的字符有哪些，这实际就考虑分成的两半可以变成的字符可以组合成的字符。

那么我们再结合区间 DP 的思路，用一个 $dp$ 数组表示一个区间可以变成的最小的只有 ```S``` 组成的串。

我们枚举区间断点，如果两边的都可以变成只有 ```S``` 组成的串，那么这个区间也可以变成只有 ```S``` 组成的串。

显然的，状转也就出来了。
```cpp
dp[s][e]=min(dp[s][e],dp[s][k]+dp[k+1][e]);
```

## AC 代码（附有详细注释）
```cpp
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
int trans[200][200],f[200][200],dp[201][201];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	int n,t;cin >> n;
	string str;
	for(register int i=1; i<=n; i++){
		cin >> str;
		trans[str[1]-'A'+1][str[2]-'A'+1]|=1<<str[0]-'A'+1;
	}//处理trans数组，trans[i][j]表示第i和j个字母可以合成的字母集 
	cin >> t;
	while(t--){
		cin >> str;
		memset(f,0,sizeof f);
		memset(dp,0x3f,sizeof dp);
		int len=str.size();
		for(register int i=0; i<len; i++){
    		if(str[i]=='S') dp[i+1][i+1]=1;
    		f[i+1][i+1]|=1<<(str[i]-'A'+1);
    	}//初始化
		for(register int l=1; l<=len; l++){//枚举区间长度 
			for(register int s=1; s+l<=len; s++){//枚举起点 
				int e=s+l;
				for(register int k=s; k<e; k++){//枚举断点 
					dp[s][e]=min(dp[s][e],dp[s][k]+dp[k+1][e]);//状态转移方程 
					for(register int u=1; u<=26; u++)
					for(register int v=1; v<=26; v++)
					if((f[s][k]>>u)&(f[k+1][e]>>v)&1) f[s][e]|=trans[u][v];
				}//处理f数组 
				if(f[s][e]&(1<<19)) dp[s][e]=1;//特判区间[s,e]能变为'S'的情况 
			}
		}
		if(dp[1][len]>114514.1919810) cout << "NIE\n";//dp[1][len]位极大值，无解 
		else cout << dp[1][len] << endl;//输出答案 
	}
	return 0;
}
```


---

## 作者：Fracture_Dream (赞：0)

大意：判断一个字符串是否能够通过一个特定的串分裂得到，如果可以的话输出特定的串的长度的最小值，如果不可以的话输出 NIE。

俗话说得好，正难则反，分裂很难，但是我们可以想：我们可不可以将给定的字符串进行**合并**得到这个最小特定的串呢？

于是我们可以定义一个三维的区间 $dp[i][j][s]$ 表示区间 $[i,j]$ 能否合成为字符 $s$。然后依次去枚举左端点和区间长度，再在这个枚举到的这个区间里枚举中间点 $k$ 并更新该区间能合成的字符！

那最后的答案存在哪呢？大多数人第一反应是 $dp[l][r][19]$。实则不然，因为字符串可能是由多个 $S$ 分裂而成，所以我们还需定义一个 $dp2[i]$  表示前 $i$ 个字符所需最少 $S$ 数量。  
最后答案即是 $dp2[n]$。  
 $n$ 为字符串长度。


------------

代码如下：
```c
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e2 + 5;
int n , k , dp[MAXN][MAXN][27] , a[2005][27] , dp2[MAXN];//dp状态已解释，不过多赘述 
char a2 , b , c , s[MAXN];
int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);//玄学优化 
	cin >> n;
	for (int i = 1 ; i <= n ; i ++) {
		cin >> a2 >> b >> c;
		a[i][0] = a2 - 'A' + 1;
		a[i][1] = b - 'A' + 1;
		a[i][2] = c - 'A' + 1;//用a数组保存b字符与c字符可合成a字符 
	}
	cin >> k;//样例组数 
	while(k --) {
		cin >> s + 1;
		int m = strlen(s + 1);
		for (int i = 1 ; i <= m ; i ++) dp2[i] = 0x3f3f3f3f;//用来比最小值 
		for (int i = 1 ; i <= m ; i ++) {
			for (int j = i ; j <= m ; j ++) {
				for (int k = 1 ; k <= 26 ; k ++) {
					dp[i][j][k] = 0;//初始化 
				}
			}
		}
		dp[0][0][19] = 1;//初始化，无过多实际意义 
		for (int i = 1 ; i <= m ; i ++) {
			dp[i][i][s[i] - 'A' + 1] = 1;//自己合成自己肯定可以 
		}
		for (int i = 2 ; i <= m ; i ++) {//枚举区间长度 
			for (int j = 1 ; j <= m - i + 1 ; j ++) {//枚举左端点 
				int p = j + i - 1;//右端点 
				for (int q = j ; q < p ; q ++) {//枚举中间点 
					for (int x = 1 ; x <= n ; x ++) {//一共有x种合成方式 
						if (dp[j][q][a[x][1]] && dp[q + 1][p][a[x][2]]) {//若左区间可以合成a[x][1]，右区间可以合成啊a[x][2]，那么j-p就可以合成a[x][0] 
							dp[j][p][a[x][0]] = 1;
						}
					}
				}
			}
		}
		for (int i = 1 ; i <= m ; i ++) {
			for (int j = 0 ; j < i ; j ++) {
				if (dp[j + 1][i][19]) {//j+1到i可以合成字符S 
					dp2[i] = min(dp2[i] , dp2[j] + 1);// 那么1到j最小的S数量加上j+1到i的这个S便是一组解，与原答案比min 
				}
			}
		}
		if (dp2[m] == 0x3f3f3f3f) puts("NIE");//若没有更新1到m的值，即无解 
		else printf("%d\n", dp2[m]);//否则输出 
	}
	return 0;
} 
```
 





---

## 作者：_Fontainebleau_ (赞：0)

### 题意

- 给定 $n$ 个转化规则，形如「$A_1A_2A_3$」，表示 $A_2A_3$ 可以转化成 $A_1$。
- 给定 $m$ 个只含大小写字母的字符串，求能否将其转化成只有 $\texttt S$ 的序列。若可以，输出转化后序列的最小长度。否则输出 $\texttt{NIE}$。
- $1\le n\le 10^4,1\le k\le  2000$。字符串长度小于等于 $100$。

### 做法

考虑区间 DP+状压。因为 $\texttt A \sim \texttt  Z$ 共 $26$ 个，所以直接开 int 即可。

用 $f_{l,r}$ 表示区间 $[l,r]$ 中可以合并成的字母。转移方程是：

$$f_{l,r}=\operatorname{calc}(f_{l,k},f_{k+1,r})$$

$\operatorname{calc}(x,y)$ 表示两个字符集可以转化成的新的字符集。

若 $f_{l,r}$ 包含 $\texttt S$，则区间 $[l,r]$ 可以被转化成 $\texttt S$。

这是一个 dp。

最后再搞一个 dp。

用 $g_i$ 表示区间 $[1,i]$ 位置可以转化成的全 $\texttt S$ 序列的最小长度。转移方程为：

$$g_i=\min _{j=0}^{i-1} g_j+1$$

然后就结束了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[102][102];
int f[102][102];
int g[102],n;
inline void calc(int u,int v,int &x)
{
	for(int i=0;i<=25;i++)
		for(int j=0;j<=25;j++)
			if((u>>i)&(v>>j)&1)	x|=c[i][j];
}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	n=read();
	char s[202];
	while(n--)
	{
		cin>>s;
		c[s[1]-'A'][s[2]-'A']|=1<<(s[0]-'A');
	}
	n=read();
	while(n--)
	{
		cin>>s+1;
		int m=strlen(s+1);
		memset(f,0,sizeof(f)),memset(g,0x3f,sizeof(g));
		for(int i=1;i<=m;i++)	f[i][i]=1<<(s[i]-'A');
		for(int i=m;i>=1;i--)
			for(int j=i+1;j<=m;j++)
				for(int k=i;k<j;k++)
					calc(f[i][k],f[k+1][j],f[i][j]);
		g[0]=0;
		for(int i=1;i<=m;i++)
			for(int j=0;j<i;j++)
				if(1&(f[j+1][i]>>18))	g[i]=min(g[i],g[j]+1);
		if(g[m]==0x3f3f3f3f)	puts("NIE");
		else	printf("%d\n",g[m]);
	}
	return 0;
}

```


---

