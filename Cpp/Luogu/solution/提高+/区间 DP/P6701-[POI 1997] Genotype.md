# [POI 1997] Genotype

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

## 作者：天南地北 (赞：16)

大意：判断一个字符串是否能够通过一个特定的串分裂得到，如果可以的话输出特定的串的长度的最小值，如果不可以的话输出$NIE$。

俗话说得好，正难则反，分裂很难，但是我们可以想：我们可不可以将给定的字符串进行合并得到这个最小特定的串呢？

其实这个问题就像十分朴素的区间$DP$，考虑有一个$dp[l][r]$，我们需要枚举一个中点$k$，计算求它所需要的特定的串的个数$dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);$

当然了，这个特定的串只包含**大写字母S**，其实我们可以通过状态压缩的方式，表示当前区间可以变成的字符有哪些，那么就是要考虑分成的两个部分可以变成的字符以及可以组合成的字符

最后只要$dp[1][stlen]$只要不是极大值，就是有解，解是$dp[1][stlen]$，否则无解。

参考程序

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int maxn=300+10;
int n,k;
int Merge[maxn][maxn],zt[maxn][maxn],dp[maxn][maxn];
int main()
{
  scanf("%d",&n);
  rep(i,1,n)
  {
    string ch;
    cin>>ch;
    Merge[ch[1]-'A'+1][ch[2]-'A'+1]|=1<<(ch[0]-'A'+1);
  }
  scanf("%d",&k);
  while(k--)
  {
    memset(zt,0,sizeof(zt));
    memset(dp,0x3f,sizeof(dp));
    string now;
    cin>>now;
    int stlen=now.size();
    rep(i,0,stlen-1)
    {
      if(now[i]=='S') dp[i+1][i+1]=1;
      zt[i+1][i+1]|=(1<<(now[i]-'A'+1));
    }
    rep(len,0,stlen-1)
    {
      for(int l=1;l+len<=stlen;l++)
      {
        int r=l+len;
        rep(k,l,r-1)
        {
          	dp[l][r]=min(dp[l][r],dp[l][k]+dp[k+1][r]);
          	rep(x,1,26)
         	 	rep(y,1,26)
            		if((zt[l][k]&(1<<(x)))&&(zt[k+1][r]&(1<<(y))))
              			zt[l][r]|=Merge[x][y];
        }
        if(zt[l][r]&(1<<('S'-'A'+1))) dp[l][r]=1;
      }
    }
    if(dp[1][stlen]>=0x3f3f3f3f) printf("NIE\n");
    else printf("%d\n",dp[1][stlen]);
  }
}
```


---

## 作者：ThEskY_B1ackeR (赞：4)

# P6701 [POI1997] Genotype 题解
  区间 （+ 状压） DP
  
刚拿到这个 区间 DP 题没有想法，~~试图用六维状态水过~~

摸索许久，发现了一种比较**新的方法**。
## 思路
### 状态设计
   首先对于原题的分裂操作，我们反其道而行，对于每个 Genotype，我们将它两个字母两个字母地合并成一个只由字母 `S` 组成的字符串。
**我们用 $Merge_{i,j}$ 代表字母 $i$ 和字母 $j$ 能合并成的所有字母状态**（没理解状压别急，请往下看），即
```cpp
cin >> a >> b >> c;
Merge[b - 'A'][c - 'A'] |= 1 << a - 'A';
```
   我们要求的就是原字符串能通过合并得到的最短的只由字母‘_S_’组成的字符串的长度。
   
于是，我们有了第一个状态：$f[l,r]$ 表示 $[l,r]$ 区间所能合并成的最短的只由 `S` 组成的字符串长度

   初始化时，对于长度为 $1$ 的区间 $f[i,i]$，当 $s[i]= ‘S’$ 时，$f[i,i]=1$ 其余状态皆是 INF。
### 状态转移方程
   $f [l, r] = \min(f[l, mid] + f[mid + 1, r]  )$
**但仅是这样，显然不够完善。**\
我们还需要边界条件。
### 边界条件
   于是我们想，当 $[l , mid]$ 和 $[mid + 1, r]$ 两个区间没有一个能合成 `S` 时，就都设为 INF，但一个能合成单个字母 `A`，一个能合成单个字母 `B`，而字符串 `AB` 恰好能合成单个字母 `S` 时， 

$f [l, r] = 1$

   判断一个区间 $[ l , mid ]$ 和另一个区间 $[ mid + 1, r]$ 能否合成一个字母 `S`，那我们就得先考虑 $[l,mid]$ 区间能被合成哪些单个字母，$[mid+1,r]$ 区间能又被合成那些单个字母。
   
  所以我们可以用 26 位二进制数状压维护第二个状态：$dp[l,r]$ 表示 $[l,r]$ 区间能合成哪些单个字母。
  
  例：如果 $dp[l,r]$ 二进制的第 2 位是 $1$ ，则 $[l,r]$ 区间可以合并成字母 `B`，$dp[l,r]$ 二进制的第 18 位是 $0$，则 $[l,r]$ 区间不可以合并成字母 `S`。
  
```cpp
if (dp[l][r] & (1 << 18)) // 判断是否区间 [l ,r] 是否能合并成单个字母‘S’。
```

   在初始化时，每个长度为 $1$ 的区间只能合并成它自己，于是得到  
```cpp
dp[i][i] = 1 << S[i] - 'A';
```
  $dp[l, r]$ 就可以通过访问 $dp[l, mid]$ 和 $dp[mid + 1, r]$ 二进制中的每一位，通过 Merge 获得新的字母，添加到自己的状态里。

```cpp
for (int i = 0; i < 26; i++)
{
    if (dp[l][mid] & 1 << i)
    {
        for (int j = 0; j < 26; j++)
        {
            if (dp[mid + 1][r] & 1 << j)
            {
                dp[l][r] |= Merge[i][j];
            }
        }
    }
}
```
**这样我们就解决了两个 DP 的状态转移。**

 我们通过 $Merge$ 让 $dp[l,r]$ 更好的添加状态，再通过 $dp[l,r]$ 让 $f[l,r]$ 明确什么时候应该取 $1$。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
int Merge[26][26]; // Merge[a][b] 用 26位 状压维护 字母 a 、b 能合成的所有单个字母状态
void solve();

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        char a, b, c;
        cin >> a >> b >> c;
        Merge[b - 'A'][c - 'A'] |= 1 << a - 'A'; // 注意是 “ |= ” 而不是 “ = ”
    }

    cin >> k;

    while (k--)
    {
        solve();
    }

    return 0;
}

void solve()
{
    string s;
    cin >> s;
    n = static_cast<int>(s.size());
    s = " " + s;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1)), f(n + 1, vector<int>(n + 1, 1e9));
/*
 *    dp[i][j] ： 用 26位 状压维护 i ~ j 区间能合成的所有“单个”字母
 *
 *    f[i][j] : i ~ j 区间能合成 ‘S’ 的最短长度
 *
 */
    for (int i = 1; i <= n; i++)
    {
        dp[i][i] |= 1 << s[i] - 'A';  
        if (s[i] == 'S') f[i][i] = 1; 
        /*
         * dp 初始化长度为 1 的区间能合成的字符为它本身
         *
         * 本身是 ‘S’ 的区间， f 初始化长度为 1， 其余为 INF
         * 
         */
    }

    for (int len = 2; len <= n; len++)
    {
        for (int l = 1, r = l + len - 1; r <= n; l++, r++)
        {
            for (int mid = l; mid < r; mid++)
            {
                f[l][r] = min(f[l][r], f[l][mid] + f[mid + 1][r]); // 进行合并
                
                for (int i = 0; i < 26; i++)
                {
                    if (dp[l][mid] & 1 << i)
                    {
                        for (int j = 0; j < 26; j++)
                        {
                            if (dp[mid + 1][r] & 1 << j)
                            {
                                dp[l][r] |= Merge[i][j];
                            }
                        }
                    }
                }

                /*
                 * [l ~ mid] 区间 和 [mid + 1 ~ r] 区间 能合成的单个字符，再合并成 [l ~ r] 区间能合并成的单个字符
                 */
                
            }
            if (dp[l][r] & 1 << 18) // 如果 [l ~ r] 区间 能合成单个字符 ‘S’，那么 f[l][r] = 1
            {
                f[l][r] = 1;
            }
        }
    }

    if (f[1][n] < 1e9)
    {
        cout << f[1][n] << "\n";
    }
    else
    {
        cout << "NIE" << "\n";
    }
}
```
最终总用时 55ms，排在前列。
 > 特别鸣谢 @fhysmile 教练，提供最优解

---

## 作者：7KByte (赞：3)

书虫供的题/se

还没人写题解。


题意是给一些操作，每次可以把两个字符缩成一个字符。问最后能缩成多少个```'S'```，要使```'S'```个数最少。


很套路的区间$\texttt{DP}$，我们用$f_{l,r}$表示区间$[l,r]$之间的字符能够缩成哪些字符。因为字符集大小为$26$，所以我们直接用一个```int```状态压缩一下即可。

$f_{l,r}=calc(f_{l,k},f_{k+1,r})$。这里的$calc$是根据给定的规则计算两个字符集合成的新的字符集。

如果$f_{l,r}$包含$2^{18}$，即```'S'```的状态表示，说明区间$[l,r]$可以缩成一个```'S'```。

然后$g_i$表示区间$[1,i]$能缩成的最少长度。

$g_i=\min\{g_j+1\}$，显然要满足区间$[j+1,i]$能缩成一个```'S'```。


然后这道题就写完了OoO。时间复杂度$\operatorname{O(26^2Len^3)}$。这里常数不小所以保留了。


```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 10005
using namespace std;
int n,f[105][105],c[27][27],g[105];
void calc(int u,int v,int &x){rep(i,0,25)rep(j,0,25)if((u>>i)&(v>>j)&1)x|=c[i][j];}
int main(){
	scanf("%d",&n);char s[105];
	rep(i,1,n)scanf("%s",s),c[s[1]-'A'][s[2]-'A']|=1<<(s[0]-'A');
	scanf("%d",&n);while(n--){
		scanf("%s",s+1);int m=strlen(s+1);
		memset(f,0,sizeof(f));memset(g,0x3f,sizeof(g));
		rep(i,1,m)f[i][i]=1<<(s[i]-'A');
		pre(l,m,1)rep(r,l+1,m)rep(k,l,r-1)calc(f[l][k],f[k+1][r],f[l][r]);
		g[0]=0;rep(i,1,m)rep(j,0,i-1)if(1&(f[j+1][i]>>('S'-'A')))g[i]=min(g[i],g[j]+1);
		if(g[m]^0x3f3f3f3f)printf("%d\n",g[m]);else puts("NIE");
	}
	return 0;
}
```

---

## 作者：zzqDeco (赞：3)

~~我交了那么多次的痛苦你懂吗~~

首先感觉数据范围有问题，我算下来我的程序的规模是这样的：
$$
26   ×   26   ×   100   ×   100   ×   100   ×   2000 = 1,352,000,000,000
$$

我不行这个能 **1s** 过

我们考虑到这个题的分裂可以反过来变成合并，其实就转化成了问你一个串能不能合并成一个只有 `S` 组成的串

那么我们考虑朴素的区间 dp 的思路，用一个 `ans` 数组表示一个区间可以变成的最小的只有 `S` 组成的串。我们如果枚举中点，两边的都可以变成只有 `S` 组成的串，那么这个区间也可以变成只有 `S` 组成的串

同时为了维护一下我们是否可以变成只有 `S` 组成的串，考虑用状压的思路，用 `sign` 数组表示当前区间可以变成的字符有哪些，这实际就考虑分成的两半可以变成的字符可以组合成的字符

我们这个可以用 `to` 数组存下来，很显然，由于可以不止一种变换方法，我们也要状压

最后我们判断一下全区间的 `ans` 是不是 `inf`，如果是显然无解（就相当于没有发生变化，其实如果一开始就是符合要求的，我这个程序还需要特判，可惜出题人没有整活），否则我们直接输出 `ans`

总复杂度：$O(n \times w^2+q \times w^2 \times l^3)$

其中 $w$ 为字集大小

```cpp
#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

int n,q;

int to[300][300],sign[300][300],ans[300][300];

int main()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {
    string s;
    cin>>s;
    to[s[1]-'A'+1][s[2]-'A'+1]|=1<<(s[0]-'A'+1);
  }
  scanf("%d",&q);
  while(q--)
  {
    memset(sign,0,sizeof(sign));
    memset(ans,0x3f,sizeof(ans));
    string now;
    cin>>now;
    for(int i=0;i<now.size();i++)
    {
      if(now[i]=='S') ans[i+1][i+1]=1;
      sign[i+1][i+1]|=(1<<(now[i]-'A'+1));
    }
    for(int len=1;len<=now.size();len++)
    {
      for(int l=1;l+len<=now.size();l++)
      {
        int r=l+len;
        for(int k=l;k<r;k++)
        {
          ans[l][r]=min(ans[l][r],ans[l][k]+ans[k+1][r]);
          for(int x=1;x<=26;x++)
          for(int y=1;y<=26;y++)
            if((sign[l][k]&(1<<(x)))&&(sign[k+1][r]&(1<<(y))))
              sign[l][r]|=to[x][y];
        }
        if(sign[l][r]&(1<<('S'-'A'+1))) ans[l][r]=1;
      }
    }
    if(ans[1][now.size()]>=0x3f3f3f3f) printf("NIE\n");
    else printf("%d\n",ans[1][now.size()]);
  }
}
```

---

## 作者：hewo (赞：2)

~~**有毒的数据范围**~~

使用区间 DP + 状压：

转化为将给定的字符串能压缩成的 只含有 S 的最短字符串。  

对于给定的分裂（合并）规则，也就是两个字符合并为一个字符，我们用状压思想，以二进制来存储这两种字符可以合并为那些种类的字符，也就是:

```cpp
c[get(ins[1])][get(ins[2])]|=(1<<(get(ins[0])));
```

再考虑如何 DP。

设 $dp_{i,j}$ 表示区间 $[i,j]$ 中的答案，$git_{i,j}$ 表示区间 $[i,j]$ 可以合并成为那些字符。

在进行区间 DP 的同时，更新 $git_{i,j}$，如果合并出了 S，则 $dp_{i,j}=1$。

大体的思路就是这样，不知道为什么，我实现的代码在超时的边缘反复横跳，在进行以下修改后才跑过 ~~（结果跑到了第3）~~ 。（orz 31ms 巨佬）

1. 开小数组，实测对此题优化明显。
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

## 作者：Dr_Gilbert (赞：2)

# P6701 [POI1997] Genotype

#### 【题目大意】

我们可以用大写英文字母 $A-Z$ 来描述 Genotype，每个字母就代表一个基因。规定一种「分裂」规则，由三个大写字母 $A_1A_2A_3$ 组成，代表 $A_1$ 可以「分裂」为 $A_2A_3$。现在给定 $n$ 个「分裂」规则和 $k$ 个 Genotype，判断这些 Genotype 是否能从一个特定的 **只包含大写字母 $S$ 的** 串通过「分裂」规则得到，如果可以的话输出特定的串的长度的最小值，如果不可以的话输出 `NIE`。

如果你做过 [P4290](https://www.luogu.com.cn/problem/P4290)，那么可以想到这可能是一道区间DP的题目。但是发现数据范围似乎有点大，可能并不能用区间DP去做。但事实上数据范围不太对，写正常的区间DP都可以过。

按照区间DP的基本想法设计一下状态。不妨把所谓的“分裂”成两个串看成两个串合并为一个串。首先题目问整个串能否合并为全为字母 $S$ 的串，如果可以，问这个全 $S$ 串的最小长度。由于有若干合并规则，那么显然不能只考虑字母 $S$。所以可以设计一个比较直接的状态：$dp[i][j][x]$ 表示区间 $[i,j]$ 中，将其合并为全是字母 $x$ 的串，这个串的最小长度。这样就不难得到如下转移：

1. 若 $\exist\ k\in[i,j)$，使得 $dp[i][k][y]=1$ 且 $dp[k+1][j][z]=$1 成立，且字母 $x$ 可以分裂成 $y,z$，则 $dp[i][j][x]=1$。
2. $dp[i][j][x]=\min(dp[i][j][x],dp[i][k][x]+dp[k+1][j][x])$。

对于DP数组的初值，首先应全部赋成 $\inf$，然后对于字符串中第 $i$ 个字符 $x$，有 $dp[i][i][x]=1$。对于判断是否可以分裂，由于题目没有给出任何保证，所以我采用一个三维数组 $trans[x][y][z]$，记录 $x$ 是否能分裂为 $y,z$。总时间复杂度 $O(26^3len^3)$。好像比其他题解多了个 $26$，不过自认为思路更简单。

参考代码实现：

```cpp
#include <bits/stdc++.h>
#define endl '\n'
const int inf=0x3f3f3f3f;
using namespace std;
int trans[30][30][30];
int dp[110][110][30];
inline int min(int a, int b){return a<b?a:b;}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);cout.tie(nullptr);
	int N,K;cin>>N;
	for (int i=1;i<=N;i++){
		string s;cin>>s;
		trans[s[0]-'A'][s[1]-'A'][s[2]-'A']=1;
	}
	cin>>K;
	while (K--){
		string s;cin>>s;
		int n=s.length();
		memset(dp,0x3f,sizeof(dp));
		for (int i=1;i<=n;i++){
			dp[i][i][s[i-1]-'A']=1;
		}
		for (int len=2;len<=n;len++){
			for (int i=1;i+len-1<=n;i++){
				int j=i+len-1;
				for (int k=i;k<j;k++){
					for (int a=0;a<26;a++){
						if (dp[i][k][a]==inf) continue;
						for (int b=0;b<26;b++){
							if (dp[k+1][j][b]==inf) continue;
							if (a==b){
								dp[i][j][a]=min(dp[i][k][a]+dp[k+1][j][b],dp[i][j][a]);
							}
							for (int c=0;c<26;c++){
								if (trans[c][a][b]){
									if (dp[i][k][a]==dp[k+1][j][b]&&dp[i][k][a]==1)
										dp[i][j][c]=1;
								}
							}
						}
					}
				}
			}
		}
		if (dp[1][n]['S'-'A']>=inf) cout<<"NIE"<<endl;
		else cout<<dp[1][n]['S'-'A']<<endl;
	}
	return 0;
} 
```







---

## 作者：StupidSeven (赞：2)

## Subject 
[题目传送门](https://www.luogu.com.cn/problem/P6701)

## Analysis
注意到基因的长度，且所有串只包含大写字母。发现它满足一个从小区间的答案推出大区间答案的性质，考虑使用区间 dp 解决。

设 $dp[L][R][s]$ 表示区间 $[L,R]$ 能否合成字母 $s$ ，然后枚举断点，用已知的分裂规则，来判断是否可以合并回去。

详细代码如下：
```cpp
for(int len=2;len<=m;len++){
    for(int L=1;L+len-1<=m;L++){
        int R=L+len-1;
        for(int k=L;k<R;k++){
            for(int x=1;x<=n;x++){
                dp[L][R][a[x][0]]|=dp[L][k][a[x][1]]&dp[k+1][R][a[x][2]];
            }
        }
     }
}
```

然后记 $g_i$ 表示区间 $[1,i]$ 全部只包含字母 S 的最小长度，显然有
$$g[i]=\min\limits_{0\leq j<i}  (g[i],g[j]+1) $$ 
可以枚举所有以 $i$ 为右端点的区间。转移的条件是 $dp[j+1][i]['S']$ 为真。

记原基因的长度为 $m$ ,则时间复杂度为 $O(nm^3k)$ ，可以通过本题。

## Code
```cpp
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int S='S'-'A'+1;
const int M=2e3+10;
const int Mod=1e5+3;
const int inf=0x3f3f3f3f;
const double eps=1e-5;
inline int Read(void){
    int s=0,f=1;char v=getchar();
    while(!isdigit(v)){if(v=='-')f=-1;v=getchar();}
    while(isdigit(v)){s=s*10+v-48;v=getchar();}
    return s*f;
}
char s[110];
int n,m,t,a[M][3],g[110];
bool dp[110][110][30];
signed main(void){
    n=Read();
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        for(int x=0;x<3;x++){
            a[i][x]=s[x]-'A'+1;
        }
    }
    t=Read();
    while(t--){
        scanf("%s",s+1);
        m=strlen(s+1);
        memset(dp,false,sizeof dp);
        for(int i=1;i<=m;i++){
            dp[i][i][s[i]-'A'+1]=true;
        }
        for(int len=2;len<=m;len++){
            for(int L=1;L+len-1<=m;L++){
                int R=L+len-1;
                for(int k=L;k<R;k++){
                    for(int x=1;x<=n;x++){
                        dp[L][R][a[x][0]]|=dp[L][k][a[x][1]]&dp[k+1][R][a[x][2]];
                    }
                }
            }
        }
        dp[0][0][S]=true;
        g[0]=0;
        for(int i=1;i<=m;i++){
            g[i]=inf;
            for(int j=0;j<i;j++){
               if(dp[j+1][i][S]){
                   g[i]=min(g[i],g[j]+1);
               }
            }
        }
        if(g[m]==inf) printf("NIE\n");
        else printf("%d\n",g[m]);
    }
    return 0;
}
```

---

## 作者：Nuyoah_awa (赞：1)

### 题目大意

给定 $n$ 中分裂方式，一个字母 $A_1$ 可以分裂为两个字母 $A_2A_3$。

问是否可以通过只包含大写字母 $S$ 的串通过分裂得到目标串，求初始串长度的最小值。

### 题目分析

看完题面发现字符串的长度不大，可以考虑在这上面做文章。

很容易想到区间 dp。（校内模拟赛的时候死磕另外一题都没看这题）

我们可以定义 $f_{l,r,c}$ 表示目标串的 $S_l \sim S_r$ 是否可以通过一个字符 $c$ 分裂得来。

然后考虑怎么转移，我们枚举一个中点，将 $S_{l\sim r}$ 视为是两段拼接起来的，然后再枚举通过中点分开的两段是否可以通过两个字母得来，这两个字母是否可以通过 $c$ 分裂一次得来。

转移方程为：

$$f_{l,r,c} = \mathbin{\mathrm{or}}_{mid = l}^{mid\le r} \{f_{l,mid,a} \mathbin{\mathrm{and}} f_{mid+1,r,b} \}$$

形象的来讲我们可以把分裂过程看成：

$$c \Rightarrow \begin{cases}a \Rightarrow \dots \Rightarrow S_{l\sim mid} \\ b \Rightarrow \dots \Rightarrow S_{mid+1\sim r}\end{cases}$$

最终答案我们也可以用 dp 的方式求出。

我们用 $g_i$ 表示 $S_{1\sim i}$ 最少可以用几个 $S$ 分裂来。对于转移，我们可以像类似 $\operatorname{LIS}$ 一样转移，我们同样把 $S_{1\sim i}$ 分成两段，一段由多个 $S$（也可以是 $0$ 个）分裂得来，另一段由一个 $S$ 分裂得来。

即：

$$g_i = \max\limits_{j = 0}^{j < i } g_j + 1$$

核心思路，我们需要枚举左右界、中点、分裂方式，最后总的时间复杂度是 $\mathcal O(T \times |s|^3 \times n)$ 的。

PS：当我们无法通过若干 $S$ 分裂得到目标串时，也就是所有 $f_{1,j,s} \& f_{j+1,n,s}$ 都为否时，输出 `NIE`。

Q.E.D.

### code
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <math.h>
#include <cstring>
using namespace std;
const int N = 1e2 + 5, INF = 1e9;
int n, k, f[N][N][30], g[N];
vector <pair<int, int> > e[30];
string s;
int ch(char c)
{
	return c - 'A' + 1;
}
signed main()
{
	scanf("%d", &n);
	for(int i = 1;i <= n;i++)
	{
		cin >> s;
		e[ch(s[0])].push_back(make_pair(ch(s[1]), ch(s[2])));
	}
	scanf("%d", &k);
	while(k--)
	{
		cin >> s;
		s = "#" + s;
		memset(f, false, sizeof(f));
		for(int i = 1;i < s.size();i++)
			f[i][i][ch(s[i])] = true;
		for(int len = 0;len < s.size();len++)
		{
			for(int l = 1;l + len < s.size();l++)
			{
				int r = l + len;
				for(int mid = l;mid <= r;mid++)
					for(int c = ch('A');c <= ch('Z');c++)
						for(int i = 0;i < e[c].size();i++)
							f[l][r][c] |= (f[l][mid][e[c][i].first] && f[mid+1][r][e[c][i].second]);
			}
		}
		g[0] = 0;
		for(int i = 1;i < s.size();i++)
		{
			g[i] = INF;
			for(int j = 0;j < i;j++)
				f[j + 1][i][ch('S')] ? g[i] = min(g[i], g[j] + 1) : 0;
		}
		g[s.size() - 1] == INF ? printf("NIE\n") : printf("%d\n", g[s.size() - 1]);
	}
	return 0;
}
```

---

## 作者：船酱魔王 (赞：1)

# P6701 [POI1997] Genotype 题解

## 题意回顾

$ 26 $ 个大写字母代表基因，有若干个形如一个基因可以裂解成另外两个基因的裂解规则，你要求出给定的基因串可否由全 $ \text{S} $ 串裂解而成，如果可以求出全 $ \text{S} $ 串最小长度。

基因串最长为 $ 100 $。

## 分析

字符裂解的情况多，不好想。我们考虑以结果串为终点，沿着规则倒着走，即合并字符。

我们发现原来连续的字符再合并后仍然连续，而每次合成两个字符为一个，因此我们定义 $ dp_{i,j} $ 表示 $ i \sim j $ 合成的字母情况（能合成哪些字母）。

我们从短到长枚举每个区间，枚举区间分割线，枚举两个子区间的所有可合成单字母可否再合并成单个字母，然后我们记录这个区间可合成的所有字母，转移方程形如（$ dp_{i,j,p} $ 表示 $ i \sim j $ 可否合成字符 $ p $）：

$$ dp_{i,j,p}=\operatorname{OR}_{i \le k < j}\{dp_{i,k,q} \operatorname{AND} dp_{k+1,j,r}\}((q,r) \to p) $$

我们定义 $ ans_i $ 为前 $ i $ 个字符由全 $ \text{S} $ 串合并而来是否可行（不可行值为极大值），可行的话为全 $ \text{S} $ 串最小长度，前文预处理可以得到 $ d_{i,j} $ 代表 $ i \sim j $ 可否合成一个 $ \text{S} $（为 $ 1 $ 可以），因此我们转移方程为：

$$ ans_{i}=\min\{ans_j\}(d_{j+1,i}=1)+1 $$

本题时间复杂度看起来比较离谱，但是其实跑不满，内层枚举（即对于左右两部分区间合并可行性情况的合并）优化得当的话远远达不到上界，可以比较稳的跑过去。

## AC 代码


```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 105;
int n;
int T;
struct node {
	char wt;
	char vl;
};
node make(char p1, char p2) {
	node res;
	res.wt = p1;
	res.vl = p2;
	return res;
}
vector<node> g[26];
string s;
bool dp[N][N][26];
int ans[N];
int main() {
	cin >> n;
	char c1, c2, c3;
	for(int i = 1; i <= n; i++) {
		cin >> c1 >> c2 >> c3;
		g[c2 - 'A'].push_back(make(c3, c1));
	}
	cin >> T;
	for(int ti = 1; ti <= T; ti++) {
		cin >> s;
		int ln = s.size();
		for(int i = 1; i <= ln; i++) {
			for(int j = i; j <= ln; j++) {
				for(int k = 0; k < 26; k++) {
					dp[i][j][k] = 0;
				}
			}
		}
		for(int i = 1; i <= ln; i++) {
			dp[i][i][s[i - 1] - 'A'] = 1;
		}
		for(int len = 2; len <= ln; len++) {
			for(int i = 1; i + len - 1 <= ln; i++) {
				int j = i + len - 1;
				for(int k = i; k < j; k++) {
					for(int p = 0; p < 26; p++) {
						if(!dp[i][k][p]) {
							continue;
						}
						for(int l = 0; l < g[p].size(); l++) {
							if(dp[k + 1][j][g[p][l].wt - 'A']) {
								dp[i][j][g[p][l].vl - 'A'] = 1; 
							}
						}
					}
				}
			}
		}
		ans[0] = 0;
		for(int i = 1; i <= ln; i++) {
			ans[i] = 114514;
			for(int j = 0; j < i; j++) {
				if(dp[j + 1][i]['S' - 'A']) {
					ans[i] = min(ans[i], ans[j] + 1);
				}
			}
		}
		if(ans[ln] == 114514) {
			cout << "NIE" << endl;
		} else {
			cout << ans[ln] << endl;
		}
	} 
	return 0;
}
```

## 总结与评价

校内阶段检测第三题，场上切了，感觉这题是一道很基础的区间 DP 题，时间复杂度比较玄学，需要一定的小优化。

---

## 作者：GFyyx (赞：1)

## 题目大意
给定 $n$ 个分裂方式，以及 $t$ 个询问。

对于每个询问，求是否能用仅包含大写字母 ```S``` 的字符串分裂成目标字符串 $str$。

如果可以，输出特定字符串长度的最小值，否则输出 ```NIE```。

## 解题思路
如果顺着搜索特定字符串的分裂方式，搜索的深度和广度都很奆。

正难则反，我们考虑将目标字符串合并成仅含有 ```S``` 的特定字符串。

题目给定的目标字符串只含有 26 个大写字母，而整型变量有 32 位，这让我们想到了状态压缩。

用 $f_{i,j}$ 表示区间 $[i,j]$ 可以变成的字符有哪些，这实际就考虑分成的两半可以变成的字符可以组合成的字符。

我们再结合区间 DP 的思路，用一个 $dp$ 数组表示一个区间可以变成的最小的只有 ```S``` 组成的串。

我们枚举区间断点，如果两边的都可以变成只有 ```S``` 组成的串，那么这个区间也可以变成只有 ```S``` 组成的串。

显然的，状转也就出来了（其实就是标准的区间 DP）。
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

## 作者：orpg (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P6701)
### 题目描述
题目给定一 $n$ 个规定 $A_1$，$A_2$，$A_3$。$A_1$ 可以分裂成 $A_2 A_3$。题目问我们最少要多少个用 $S$ 构成的字符串能分裂成给定字符串。
### 题目分析
我们发现，题目给的「分裂」操作，其实相当于合并操作，就是将 $A_2 A_3$ 合并成 $A_1$。

所以，对于一个给定字符串 $st$ 我们可以先维护一个 $f[n][m]$ 数组，用区间 $dp$ 记录从 $n$ 到 $m$ 的所有可以合并成的字符。

接下来我们再使用 $dp[n]$ 来维护从 $1$~$n$ 的最少的 $S$ 构成的字符串就行了。
### 上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100+5;
int n,m;
int f[maxn][maxn];
int trans[maxn][maxn];
int dp[maxn];
void init(){
	memset(dp,0x3f,sizeof dp);
	memset(f,0,sizeof f);
}
void solve(string s,int len){
	len--;
	for(int i=1;i<=len;i++) f[i][i]=1<<(s[i]-'A');
	for(int i=2;i<=len;i++){//长度 
		for(int l=1;l+i-1<=len;l++){//left 
			int r=l+i-1;//right
			for(int j=l;j<r;j++){//段点 
				for(int s2=0;s2<26;s2++)//字母0~25 
					for(int s1=0;s1<26;s1++)//字母0~25 
						if((f[l][j]>>s2)&(f[j+1][r]>>s1)&1)
							f[l][r]|=trans[s2][s1]; 
			}
		}
	}
	dp[0]=0;
	for(int i=1;i<=len;i++){
		for(int j=0;j<i;j++){
			if(1&(f[j+1][i]>>('S'-'A')))
			dp[i]=min(dp[i],dp[j]+1); 
		}
	}
	if(dp[len]==dp[len+1]) cout<<"NIE\n";
	else cout<<dp[len]<<'\n'; 
}
main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		trans[s[1]-'A'][s[2]-'A']|=1<<(s[0]-'A');
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		init();
		string s;
		cin>>s;
		s=" "+s;
		solve(s,s.length());
	}
}
```


---

## 作者：Yansuan_HCl (赞：1)

看到题目之后最自然的思路就是考虑区间 $[l, r]$ 能不能被合并成某个字母 $C$.

记每个 Genotype 为 $T$，$f_{l,r,C}$ 为区间 $[l, r]$ 能否被合并成单个字母 $C$. 显然，初始值为 $f_{i,i,T_i}=1$，即单个字母本身。之后按照区间 dp 的传统思路，先枚举区间长度，再枚举分割点 $k$，最后枚举 $n$ 个分裂规则，尝试用每个规则合并左区间和右区间。

核心代码：
```cpp
for (int i = 1; i <= n; ++i) f[i][i][s[i]] = 1;
for (int len = 2; len <= n; ++len)
    for (int i = 1, j = i + len - 1; j <= n; ++i, ++j) 
        for (int k = i; k < j; ++k)
            for (int x = 1; x <= m; ++x)
                f[i][j][a[x][1]] |= f[i][k][a[x][2]] && f[k + 1][j][a[x][3]];
                // 如果 S[i,k] 能被合成 a[x][2], S[k + 1, j] 能被合成 a[x][3], 那么根据规则 x, S[i,j] 能被合成 a[x][1].
```

得到每个区间能否被合成某个字母的所有情况之后，我们可以求出 $g_i$ 表示 $T[1,i]$ 被合成**只包含大写字母 $S$ 的串**的最小长度。可以枚举所有右端点为 $i$ 的区间，$g_i = min\{g_{j}+1\}(0\leq j \lt i, f_{i,j,'S'}=1)$。

核心代码：
```cpp
f[0][0][S] = 1;
g[0] = 0;
for (int i = 1; i <= n; ++i)
    for (int j = 0; j < i; ++j)
        if (f[j + 1][i][S]) // 区间[j+1, i]能被合成 'S'
            g[i] = min(g[i], g[j] + 1);
```

完整代码见[云剪贴板](https://www.luogu.com.cn/paste/anpbfeog)。

---

## 作者：EllinY (赞：0)

# 思路
手搓样例，发现用分裂根本不符合人类认知规律，遂使用合并。一秒想到区间 dp，用 $dp_{i,j}$ 表示 $i,j$ 之间的字母合并后可以得到多长的只包含 `S` 的字符串（记录最短长度）。可是要是先把 $i,k$ 之间的合并得到 `A`，再把 $k+1,j$ 之间的合并得到 `B`，最后把 `A` 和 `B` 合并得到 `S`，该怎么表示？$\\$ 首先，当一段字母合并后得到了一个不是 `S` 的字母时，就必须要再和左右两边的字母合并，最终得到 `S`。其次，如果得到了 `S`，就可以选择继续合并或者把几个合并得到的 `S` 拼起来（我们默认初始的每个字母是由这个字母本身合并得到的）。所以可以先用 $mg_{i,j}$ 进行 $\lceil$ 合并成一个字母 $\rfloor$ 的操作，然后用 $dp_{i,j}$ 进一步实现 $\lceil$ 把几个 `S` 拼起来 $\rfloor$ 的操作。$\\$ 由于合并得到的是单个字母，可以用状态压缩进行表示，$mg_{i,j}$ 在二进制下从低到高第 $k$ 位如果是 $1$，表示可以用 $i,j$ 之间的字母合并得到 `char('A'+k)`。$dp$ 和 $mg$ 都采取枚举断点 $k$ 的方法计算。$dp_{i,j}$ 的边界情况是：
1. $i=j$ 时，若 $s_i$ 是 `S`，那么 $dp_{i,j}=1$，否则是 INF。
2. $i<j$ 时，若 $i,j$ 之间的字母可以合并得到一个 `S`，即 `mg[i][j]&(1<<'S'-'A')`，那么 $dp_{i,j}=1$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int can[26][26],n,kk;
int dp[105][105],mg[105][105];
string s;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		can[s[1]-'A'][s[2]-'A']|=1<<s[0]-'A';
	}
	cin>>kk;
	for(int i=1;i<=kk;i++){
		cin>>s;
		int si=s.size();
		s=' '+s;
		memset(mg,0,sizeof(mg));
		for(int l=1;l<=si;l++) mg[l][l]=1<<s[l]-'A';
		for(int j=2;j<=si;j++)
			for(int l=1;l+j-1<=si;l++){
				int k=l+j-1;
				for(int mid=l;mid<k;mid++)
					for(int a=0;a<26;a++)
					if(mg[l][mid]&(1<<a))
						for(int b=0;b<26;b++)
						if(mg[mid+1][k]&(1<<b))
							mg[l][k]|=can[a][b];
			}
		memset(dp,0x3f,sizeof(dp));
		for(int j=1;j<=si;j++)
			for(int l=1;l+j-1<=si;l++){
				int k=l+j-1;
				if(mg[l][k]&(1<<'S'-'A')){
					dp[l][k]=1;
					continue;
				}
				for(int mid=l;mid<k;mid++)
					dp[l][k]=min(dp[l][k],dp[l][mid]+dp[mid+1][k]);
			}
		if(dp[1][si]<0x3f3f3f3f) cout<<dp[1][si]<<endl;
		else cout<<"NIE\n";
	}
	return 0;
}
```

---

## 作者：Compound_Interest (赞：0)

# 题目描述

[题面传输门](https://www.luogu.com.cn/problem/P6701)

大意：一些三元组 $ABC$ （$ABC$ 都是字符），表示 $A$ 可以分裂成 $BC$，然后给定多个字符串，问这些字符串最少用几个只有 $S$ 字符的字符串分裂得到的。

# 解法

**这是一个非状压个人觉得比较好理解的解法**

这题很符合区间 dp 的特征，多个区间可以两两分解、合并是区间 dp 的一大特征，可以往区间 dp 上想一想。

但是这题数据范围好像有误，容易把人带偏。

一上来的最优化问题我们不好解决不如试着把他转换为判定性问题，之后再通过判定性问题的解构造原来的最优性问题。

所谓判定性问题，就是一个大区间是否能由某个字符分裂得出。

这个判定性问题容易让人联想到一个区间 dp 的比较经典的问题[玩具取名](https://www.luogu.com.cn/problem/P4290)。

当然没做过也没关系，下面我来分析。

## 判定性问题的解法

定义  $\mathit{dp}_{i,j,k}$  表示区间  $[i,j]$  是否能被字符 $k$ 分裂得到。

为了方便处理我们统一将字符转换成数字。

状态定义是一个动态规划问题的关键，蒟蒻对动态规划的比较浅显的理解就是我们先根据题目定义一个状态， 假设比较小的状态已经求解好了，那么如果我们可以通过小问题的状态构成大问题的状态（这之间需要一些分类讨论），那么我们的状态转移方程就能列出来了，问题就解决的差不多了，否则我们要根据题目信息调整状态，例如 **增减维度** 等等。

状态转移方程在代码里，代码写了注释比较清晰。


**trick:在列状态转移方程的时候我们只需要假设小规模的问题我们已经知道答案了，只需要考虑大的问题的最后一步有哪些情况分类讨论即可。**

## 构造原最优性问题的解

所谓最优性问题的解就是题目求的最少需要几个 $S$ 组成的串分裂得到。

我们可以在做判定性问题的时候用一个数组记下有哪些区间可以由一个 $S$ 分裂得到（细节代码里有）。

现在问题变成了，给定一些区间，问最少用几个不重复的区间覆盖整个大的区间。

这是一个非常基础的线性 dp 问题。

定义  $f_{i}$  表示覆盖从 $1$ 到 $i$ 最少用几个小区间。

~~不难想到状态转移方程~~

$\mathit{f}_{r}=\max(\mathit{f}_{l}+1,\mathit{f}_{r})$

其中  $l,r$  是某个小区间的左右端点。

为了保证这个dp无后效性，我们可以先将右端点排序。

至此问题解决了。

时间复杂度 $O(nklen^3)$ 有点吓人不过这题数据比较水，不开 $O2$ 可以跑过[开O2 500多ms可以接受](https://www.luogu.com.cn/record/84913710)。

# Code

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int maxn=110;
int dp[maxn][maxn][30],n,l[2010][3],f[maxn];
char str[110];
vector<int> v[maxn],vv;//vv数组存右端点，v[k]存右端点k所有的左端点，最后dp的时候用 
bool vis[maxn];//一个右端点有没有存过，避免冗余的信息存进vv数组中导致常数变大 
int main(){
	scanf("%d",&n);
	for(register int i=1;i<=n;i++){
		char a[5];
		scanf("%s",a); 
		l[i][0]=a[0]-'A',l[i][1]=a[1]-'A',l[i][2]=a[2]-'A';//小技巧，只有满足给定n个可以分裂的方案才用于转移，避免了多余的时间花费
		//l[i][0]可以分裂成l[i][1]和l[i][2] 
	}
	register int T;
	scanf("%d",&T);
	while(T--){
		memset(dp,0,sizeof(dp));
		for(int i=0;i<vv.size();i++) v[vv[i]].clear();
		vv.clear();//多组数据，记得清空数组 
		scanf("%s",str+1);
		int len=strlen(str+1);
		for(register int i=1;i<=len;i++) dp[i][i][str[i]-'A']=1,f[i]=0x3f3f3f3f,vis[i]=0;//初始化dp数组，一个字符一定可以直接分裂成自己 
		for(register int d=2;d<=len;d++)
			for(register int i=1;i<=len-d+1;i++){
				int j=i+d-1;//新手比较不容易错的区间dp写法，先枚举区间长度再枚举左端点，算右端点，枚举两个端点的时间花销还是O(n^2) 
				for(register int k=i;k<j;k++)
					for(register int t=1;t<=n;t++){//这里转移要花O(n*len)的时间 
						bool flag=0;
						if(dp[i][j][l[t][0]]==0&&l[t][0]=='S'-'A') flag=1;//第一次更新才把这个右端点和其对应的左端点 
						dp[i][j][l[t][0]]|=dp[i][k][l[t][1]]&&dp[k+1][j][l[t][2]];//核心，如果两个小的区间能分别合成l[t][1]和l[t][2]则他们组合成的大区间能合成l[t][0] 
						if(flag&&dp[i][j][l[t][0]]){
							v[j].push_back(i);
							if(!vis[j]) vis[j]=1,vv.push_back(j);//将右端点加入vector，最后算答案的时候dp用 
						} 
					}
			}
		sort(vv.begin(),vv.end());
		for(register int i=0;i<vv.size();i++)
			for(register int j=0;j<v[vv[i]].size();j++)
				f[vv[i]]=min(f[vv[i]],f[v[vv[i]][j]-1]+1);//一个很基础的dp问题，给定一些区间，问这些区间中最少用几个区间不想交的覆盖整个大的区间 
		if(f[len]==0x3f3f3f3f) printf("NIE\n");
		else printf("%d\n",f[len]);
	}
	return 0;
}
```



---

