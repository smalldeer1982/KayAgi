# [CERC2014] Vocabulary

## 题目描述

根据一种流行的说法，计算机程序员喝很多咖啡，并且只知道几个单词。一个典型程序员的词汇量只有三个单词。此外，他很少知道如何拼写它们。为了帮助程序员纠正拼写错误，我们出版了一本名为《每个典型程序员应该知道的三个单词词典》的书。

你得到了一本书的副本，但不久之后，你把咖啡洒在了上面。

现在，你无法阅读其中的一些字符。幸运的是，这三个单词在字典中是不同的，并按字典顺序排列。在你尝试利用这一事实来恢复缺失的字符之前，你想知道有多少种不同的方法可以做到这一点。由于你预计这个数字可能很大，你想知道它对 $10^9 + 9$ 取模的结果。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
?heoret?cal
c?mputer
?cience
jagiellonian
?niversity
kra?ow
?
b
c```

### 输出

```
42562
52
1```

# 题解

## 作者：uibn (赞：4)

三个字符串，设最长的长为 $n$ ，则空格可以看成 $0$ ，$a$ 到 $z$ 分别看成 $1$ 到 $26$ ，$?$ 看成 $-1$ 。

从后到前考虑每一位，符合的有如下四种情况：

$a<b<c$ ，$a<b=c$ ， $a=b<c$ ， $a=b=c$

第一种：答案直接加上 $26$ 的后面 $?$ 个数次方。

第二种、第三种：预处理只有两个字符串时的答案。

第四种：与上一位的答案相同

还要枚举每一位是不是问号，有八种情况。

注意要时刻取模，不然就溢出了。

还有 $26$ 的若干次方提前预处理。

```
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
char ch[1000005];
void Read(int *a,int &n)
{
	scanf("%s",ch+1);
	for (n=1;ch[n]!='\0';n++) ; n--;
	for (int i=1;i<=n;i++) a[i]=(ch[i]=='?')?-1:ch[i]-'a'+1;
	for (int i=1;i<=n;i++) ch[i]='\0';
}
const long long M=1e9+9;
long long Mit[4000001];
long long Mi(long long a,long long b)
{
	if (a==26) return Mit[b];
}
void Calc(long long *f,int n,int *a,int *b)
{
	int ca=0,cb=0;
	if (a[n]!=-1&&b[n]!=-1)
	{
		if (a[n]>=b[n]) f[n]=0;
		else f[n]=1;
	}
	else if (a[n]!=-1) f[n]=26-a[n];
	else if (b[n]!=-1) f[n]=b[n]-1;
	else f[n]=13*25;
	if (a[n]==-1) ca++;
	if (b[n]==-1) cb++;
	for (int i=n-1;i>=1;i--)
	{
		if (a[i]!=-1&&b[i]!=-1)
		{
			if (a[i]>b[i]) f[i]=0;
			else if (a[i]<b[i]) f[i]=Mi(26,ca+cb);//
			else f[i]=f[i+1];
		}
		else if (a[i]!=-1)
		{
			f[i]=1ll*(26-a[i])*Mi(26,ca+cb)%M+f[i+1];
			if (f[i]>=M) f[i]-=M;
		}
		else if (b[i]!=-1)
		{
			f[i]=1ll*(b[i]-1)*Mi(26,ca+cb)%M+f[i+1];
			if (f[i]>=M) f[i]-=M;
		}
		else
		{
			f[i]=13ll*25ll*Mi(26,ca+cb)%M+26ll*f[i+1]%M;
			if (f[i]>=M) f[i]-=M;
		}
		if (a[i]==-1) ca++;
		if (b[i]==-1) cb++;
	}
}
int T,n;
int a[1000005],b[1000005],c[1000005];
int la,lb,lc;
long long g1[1000005],g2[1000005],f[1000005];
int main()
{
	Mit[0]=1ll;
	for (int i=1;i<=3000000;i++) Mit[i]=Mit[i-1]*26ll%M;//预处理26的若干次方结果
	scanf("%d",&T);
	while (T--)
	{
		Read(a,la),Read(b,lb),Read(c,lc);//读入时从字符转为数字
		n=max(la,max(lb,lc));
		Calc(g1,n,a,b);//预处理只考虑a,b的情况
		Calc(g2,n,b,c);//预处理只考虑b,c的情况
//		for (int i=1;i<=n;i++) printf("%d %d %d\n",i,g1[i],g2[i]);
		int ca=0,cb=0,cc=0;//计算问号数目//注意第n位要严格不相等
		if (a[n]!=-1&&b[n]!=-1&&c[n]!=-1)
		{
			if (a[n]<b[n]&&b[n]<c[n]) f[n]=1;
			else f[n]=0;
		}
		else if (a[n]!=-1&&b[n]!=-1)
		{
			if (a[n]<b[n]) f[n]=26-b[n];
			else f[n]=0;
		}
		else if (a[n]!=-1&&c[n]!=-1)
		{
			if (a[n]+1<c[n]) f[n]=c[n]-a[n]-1;
			else f[n]=0;
		}
		else if (b[n]!=-1&&c[n]!=-1)
		{
			if (b[n]<c[n]) f[n]=b[n]-1;
			else f[n]=0;
		}
		else if (a[n]!=-1)
		{
			f[n]=1ll*(26-a[n])*(26-a[n]-1)/2;
		}
		else if (b[n]!=-1)
		{
			f[n]=1ll*(b[n]-1)*(26-b[n]);
		}
		else if (c[n]!=-1)
		{
			f[n]=1ll*(c[n]-1)*(c[n]-2)/2;
		}
		else
		{
			f[n]=1ll*26*25*24/6;
		}
		if (a[n]==-1) ca++;
		if (b[n]==-1) cb++;
		if (c[n]==-1) cc++;
		f[n]%=M;
		for (int i=n-1;i>=1;i--)
		{
			if (a[i]!=-1&&b[i]!=-1&&c[i]!=-1)
			{
				if (a[i]<b[i]&&b[i]<c[i]) f[i]=Mi(26,ca+cb+cc);
				else if (a[i]<b[i]&&b[i]==c[i]) f[i]=Mi(26,ca)*g2[i+1]%M;
				else if (a[i]==b[i]&&b[i]<c[i]) f[i]=Mi(26,cc)*g1[i+1]%M;
				else if (a[i]==b[i]&&b[i]==c[i]) f[i]=f[i+1];
				else f[i]=0;
			}
			else if (a[i]!=-1&&b[i]!=-1)
			{
				if (a[i]<b[i]) f[i]=1ll*(26-b[i])*Mi(26,ca+cb+cc)%M+1ll*Mi(26,ca)*g2[i+1]%M;
				else if (a[i]==b[i]) f[i]=1ll*(26-b[i])*g1[i+1]%M*Mi(26,cc)%M+f[i+1];
				else f[i]=0;
			}
			else if (a[i]!=-1&&c[i]!=-1)
			{
				if (a[i]<c[i]) f[i]=1ll*(c[i]-a[i]-1)*Mi(26,ca+cb+cc)%M+1ll*Mi(26,cc)*g1[i+1]%M+1ll*Mi(26,ca)*g2[i+1]%M;
				else if (a[i]==c[i]) f[i]=f[i+1];
				else f[i]=0;
			}
			else if (b[i]!=-1&&c[i]!=-1)
			{
				if (b[i]<c[i]) f[i]=1ll*(b[i]-1)*Mi(26,ca+cb+cc)%M+1ll*Mi(26,cc)*g1[i+1]%M;
				else if (b[i]==c[i]) f[i]=1ll*(b[i]-1)*g2[i+1]%M*Mi(26,ca)%M+f[i+1];
				else f[i]=0;
			}
			else if (a[i]!=-1)
			{
				f[i]=1ll*(26-a[i])*(26-a[i]-1)/2%M*Mi(26,ca+cb+cc)%M+Mi(26,ca)*g2[i+1]%M*(26-a[i])%M+
				Mi(26,cc)*g1[i+1]%M*(26-a[i])%M+f[i+1];
			}
			else if (b[i]!=-1)
			{
				f[i]=1ll*(b[i]-1)*(26-b[i])%M*Mi(26,ca+cb+cc)%M+Mi(26,ca)*g2[i+1]%M*(b[i]-1)%M+
				Mi(26,cc)*g1[i+1]%M*(26-b[i])%M+f[i+1];
			}
			else if (c[i]!=-1)
			{
				f[i]=1ll*(c[i]-1)*(c[i]-2)/2%M*Mi(26,ca+cb+cc)%M+Mi(26,ca)*g2[i+1]%M*(c[i]-1)%M+
				Mi(26,cc)*g1[i+1]%M*(c[i]-1)%M+f[i+1];
			}
			else
			{
				f[i]=1ll*26*25*24/6*Mi(26,ca+cb+cc)%M+Mi(26,ca)*g2[i+1]%M*13ll*25ll%M+
				Mi(26,cc)*g1[i+1]%M*13*25%M+1ll*26*f[i+1]%M;
			}
			if (a[i]==-1) ca++;
			if (b[i]==-1) cb++;
			if (c[i]==-1) cc++;
			f[i]%=M;
		}
		printf("%lld\n",f[1]);
		for (int i=1;i<=la;i++) a[i]=0;
		for (int i=1;i<=lb;i++) b[i]=0;
		for (int i=1;i<=lc;i++) c[i]=0;
	}
	return 0;
}
```

---

## 作者：TianTian2008 (赞：2)

首先明确字典序的性质：只要出现了一位不同的字符，后面的字符无论如何都不会再影响到字典序。记三个字符串为 $a,b,c$，要求最后满足关系 $a<b<c$，显然过程中合法的关系只有 $a=b=c/a<b=c/a=b<c/a<b<c$，状压为 $0/1/2/3$ 然后DP即可。

具体地，设 $f_{i,0/1/2/3}$ 表示前 $i$ 位满足关系 $0/1/2/3$ 的方案数。根据 $a_i,b_i,c_i$ 就能得出转移，具体见代码。

考虑三个字符串不等长的影响，例如 $|a|\geqslant|b|\geqslant|c|$，那么在 $i\leqslant|c|$ 时就应满足关系 $3$，否则等 $i>|c|$ 时必定会导致 $b>c$，其他情况同理。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define mod 1000000009
using namespace std;
typedef long long ll;
ll t,n1,n2,n3,m,a[27][27][27][4][4],f[2][4];
char s1[1000002],s2[1000002],s3[1000002];
int main() {
	for(int i=0;i<26;++i)
		for(int j=0;j<26;++j)
			for(int k=0;k<26;++k) {
				if(i==j&&j==k) a[i][j][k][0][0]=a[i][j][k][1][1]=a[i][j][k][2][2]=a[i][j][k][3][3]=1;
				if(i==j&&j<k) a[i][j][k][0][2]=a[i][j][k][1][3]=a[i][j][k][2][2]=a[i][j][k][3][3]=1;
				if(i==j&&j>k) a[i][j][k][2][2]=a[i][j][k][3][3]=1;
				if(i<j&&j==k) a[i][j][k][0][1]=a[i][j][k][1][1]=a[i][j][k][2][3]=a[i][j][k][3][3]=1;
				if(i>j&&j==k) a[i][j][k][1][1]=a[i][j][k][3][3]=1;
				if(i<j&&j<k) a[i][j][k][0][3]=a[i][j][k][1][3]=a[i][j][k][2][3]=a[i][j][k][3][3]=1;
				if(i<j&&j>k) a[i][j][k][2][3]=a[i][j][k][3][3]=1;
				if(i>j&&j<k) a[i][j][k][1][3]=a[i][j][k][3][3]=1;
				if(i>j&&j>k) a[i][j][k][3][3]=1;
				for(int x=0;x<4;++x)
					for(int y=0;y<4;++y) {
						a[26][j][k][x][y]+=a[i][j][k][x][y];
						a[i][26][k][x][y]+=a[i][j][k][x][y];
						a[i][j][26][x][y]+=a[i][j][k][x][y];
						a[26][26][k][x][y]+=a[i][j][k][x][y];
						a[i][26][26][x][y]+=a[i][j][k][x][y];
						a[26][j][26][x][y]+=a[i][j][k][x][y];
						a[26][26][26][x][y]+=a[i][j][k][x][y];
					}
			}
	scanf("%lld",&t);
	while(t--) {
		scanf("%s%s%s",s1+1,s2+1,s3+1);
		n1=strlen(s1+1);
		n2=strlen(s2+1);
		n3=strlen(s3+1);
		m=min(n1,min(n2,n3));
		f[0][0]=1;
		f[0][1]=f[0][2]=f[0][3]=0;
		for(int i=1;i<=m;++i) {
			ll x=i&1,y=x^1,c1=((s1[i]=='?')?26:s1[i]-'a'),c2=((s2[i]=='?')?26:s2[i]-'a'),c3=((s3[i]=='?')?26:s3[i]-'a');
			for(int j=0;j<4;++j) {
				f[x][j]=0;
				for(int k=0;k<4;++k) f[x][j]=(f[x][j]+f[y][k]*a[c1][c2][c3][k][j])%mod;
			}
		}
		ll ans=0;
		for(int i=(n1>=n2);i<=1;++i)
			for(int j=(n2>=n3);j<=1;++j) ans+=f[m&1][i|j<<1];
		for(int i=m+1;i<=n1;++i)
			if(s1[i]=='?') ans=ans*26%mod;
		for(int i=m+1;i<=n2;++i)
			if(s2[i]=='?') ans=ans*26%mod;
		for(int i=m+1;i<=n3;++i)
			if(s3[i]=='?') ans=ans*26%mod;
		printf("%lld\n",(ans+mod)%mod);
	}
	return 0; 
}
```

---

## 作者：封禁用户 (赞：0)

首先设三个字符串为 $s_1,s_2,s_3$，三个字符串的长度为 $l_1,l_2,l_3,n=\max(l_1,l_2,l_3)$。

首先我们要用一种字典序比 `a` 还要小的字符来填充第 $s_i(1 \le i \le 3)$ 的 $l_i+1 \thicksim n$ 的位置。

接下来我们用 $0 \thicksim 25$ 依次表示 `a` $\thicksim$ `z` 字符，$26$ 表示那个比 `a` 小的字符，$27$ 表示 `?` 字符。

然后我们考虑 $s_1,s_2,s_3$ 的其中一位：预处理出 $cnt_{i,j,k,a,b}$ 表示原来字符串中 $s_1$ 的这一位为 $i$，$s_2$ 的为 $j$，$s_3$ 的为 $k$，$a$ 代表 $i$ 是否在字典序上小于 $j$，$b$ 代表 $j$ 是否在字典序上小于 $k$ 的填法数量。

然后我们枚举把 $27$ 填成 $0 \thicksim 25$ 之后的结果，也就是 $27^3$ 种情况，设枚举到的字符是 $c$，如果 $c \not= 26$ 那么原字符有可能是 $c$ 或 $27$，如果 $c=26$ 那只可能是 $26$。

考虑一个 dp，设 $f_{i,0/1,0/1}$ 表示现在考虑到第 $i$ 位，第二维表示 $s_1$ 是否小于 $s_2$，第三维表示 $s_2$ 是否小于 $s_3$，这样 dp 过去，转移的时候 $
s_{1,i},s_{2,i},s_{3,i}$ 已经定了，我们枚举 $a,b$（预处理部分的字母），除掉不合法的情况（就是现在 $s_1$ 还没有小于 $s_2$ 就填了个 $s_{1,i}>s_{2,i}$），然后直接乘上转移即可。如果原来第二维（第三维同理）是 $0$ 枚举到 $0$ 那么转移后还是 $0$，如果遇到了 $1$ 那么就是 $1$，如果原来就是 $1$ 那么不会改变字典序关系，还是 $1$。（建议配合代码理解）

总时间复杂度 $O(k^3+n)$。

代码：
```cpp
#include <bits/stdc++.h>
template < typename T > inline void read (T &x) {
  x = 0;
  bool f = false;
  char c = std :: getchar ();
  for ( ; c < '0' || c > '9' ; c = std :: getchar ()) f |= (c == '-');
  for ( ; c >= '0' && c <= '9' ; c = std :: getchar ()) x = (x << 1) + (x << 3) + (c & 15);
  x = f ? -x : x;
  return ;
}
#define debug(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
using i64 = long long;
const i64 mod = static_cast < i64 > (1e9) + 9;
const int N = static_cast < int > (1e6) + 25;
char s[3][N];
int n;
i64 f[N][2][2], cnt[28][28][28][3][3];
/*
0 ~ 25: a ~ z
26: empty
27: ?
*/
int cmp (int i, int j) {
  if (i == j) return 1;
  if (i == 26) return 0;
  if (j == 26) return 2;
  return (i < j) ? 0 : 2;
}
void init () {
  for (int i = 0;i <= 26; ++ i) {
    for (int j = 0;j <= 26; ++ j) {
      for (int k = 0;k <= 26; ++ k) {
        int a = cmp (i, j);
        int b = cmp (j, k);
        std :: vector < int > st[3];
        if (i < 26) st[0] = {i, 27};
        else st[0] = {26};
        if (j < 26) st[1] = {j, 27};
        else st[1] = {26};
        if (k < 26) st[2] = {k, 27};
        else st[2] = {26};
        for (auto A : st[0]) {
          for (auto B : st[1]) {
            for (auto C : st[2]) {
              cnt[A][B][C][a][b] ++;
            }
          }
        }
      }
    }
  }
  return ;
}
int zip (char ch) {
  if (ch >= 'a' && ch <= 'z') return ch - 'a';
  else if (ch == '?') return 27;
  else return 26;
}
void solve () {
  for (int i = 0;i <= n; ++ i) {
    for (int j = 0;j < 2; ++ j) {
      for (int k = 0;k < 2; ++ k) {
        f[i][j][k] = 0;
      }
    }
  }
  f[0][0][0] = 1;
  for (int i = 0;i < n; ++ i) {
    int A = zip (s[0][i + 1]);
    int B = zip (s[1][i + 1]);
    int C = zip (s[2][i + 1]);
    for (int j = 0;j < 2; ++ j) {
      for (int k = 0;k < 2; ++ k) {
        for (int n_j = 0;n_j < 3; ++ n_j) {
          for (int n_k = 0;n_k < 3; ++ n_k) {
            int j_ = j, k_ = k;
            if (!j_ && n_j == 2) continue;
            if (!k_ && n_k == 2) continue;
            if (n_j == 0) j_ = 1;
            if (n_k == 0) k_ = 1;
            f[i + 1][j_][k_] = (f[i + 1][j_][k_] + f[i][j][k] * cnt[A][B][C][n_j][n_k]) % mod;
          }
        }
      }
    }
  }
  return ;
}
signed main () {
  init ();
  int _;
  read (_);
  while (_ --) {
    scanf ("%s", s[0] + 1);
    scanf ("%s", s[1] + 1);
    scanf ("%s", s[2] + 1);
    n = 0;
    int len[3] = {0, 0, 0};
    for (int i = 0;i <= 2; ++ i) len[i] = std :: strlen (s[i] + 1), n = std :: max (n, len[i]);
    for (int i = len[0] + 1;i <= n; ++ i) s[0][i] = 'a' - 1;
    for (int i = len[1] + 1;i <= n; ++ i) s[1][i] = 'a' - 1;
    for (int i = len[2] + 1;i <= n; ++ i) s[2][i] = 'a' - 1;
    solve ();
    printf ("%lld\n", f[n][1][1]);
  }
  return 0;
}
```

---

