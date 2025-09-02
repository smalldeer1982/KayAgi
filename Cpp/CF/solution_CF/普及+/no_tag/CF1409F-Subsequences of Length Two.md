# Subsequences of Length Two

## 题目描述

你将会得到两个字符串$s$ 和 $t$，并保证其中的字符都是小写拉丁字母。$t$ 的长度是 $2$。

一个操作代表你可以用一个任意的字符代替 $s$ 中任意一个字符（都是小写字母）。

你最多可以进行 $k$ 次操作，也可以不进行。

求进行替换之后最多可以在 $s$ 中出现多少个 $t$ 作为他的子序列。这里的子序列是指去掉原来字符串里的一些字符，不改变相对位置得到的串。

## 样例 #1

### 输入

```
4 2
bbaa
ab```

### 输出

```
3```

## 样例 #2

### 输入

```
7 3
asddsaf
sd```

### 输出

```
10```

## 样例 #3

### 输入

```
15 6
qwertyhgfdsazxc
qa```

### 输出

```
16```

## 样例 #4

### 输入

```
7 2
abacaba
aa```

### 输出

```
15```

# 题解

## 作者：EternalEpic (赞：6)

~~思路参考SSerxhs的题解。~~

设两个字符串为 $s$ 和 $t$

$dp_{i,j,k}$ 表示到第 $i$ 个字符，前面有 $j$ 个字符与 $t_1$ 相同，且运用了 $k$ 次修改。因为这样每次多一个和 $t_2$ 相同的字符好算贡献。

分为几种情况讨论，不改（正常算贡献），改成 $t_1$ (j++,k++)，改成 $t_2$ （答案累加j，k++）。

还有就是要注意两个字符相同，特判一下。

```cpp
int n, m; char s[205], t[5];
int f[205][205][205];

signed main(void) {
//	file("");
	read(n), read(m); int ans = 0;
	readstr(s + 1), readstr(t + 1);
	if (t[1] == t[2]) {
		for (int i = 1; i <= n; i++) if (s[i] == t[1]) ++ans;
		ans = min(ans + m, n); if (ans == 0) puts("0");
		else writeln(ans * (ans - 1) >> 1); return 0;
	}
	
	Ms(f, 0xcf); f[0][0][0] = 0;
	for (int i = 1; i <= n; i++)
	for (int j = 0; j <= i; j++)
	for (int k = 0; k <= min(m, i); k++) {
		if (s[i] == t[1]) {
			if (j) f[i][j][k] = f[i - 1][j - 1][k];
			if (k) chkmax(f[i][j][k], f[i - 1][j][k - 1] + j);
		} else if (s[i] == t[2]) {
			f[i][j][k] = f[i - 1][j][k] + j;
			if (k) chkmax(f[i][j][k], f[i - 1][j - 1][k - 1]);
		} else {
			f[i][j][k] = f[i - 1][j][k];
			if (k) {
				if (j) chkmax(f[i][j][k], f[i - 1][j - 1][k - 1]);
				chkmax(f[i][j][k], f[i - 1][j][k - 1] + j);
			}
		}
	} for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) chkmax(ans, f[n][i][j]);
	writeln(ans);
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}
```


---

## 作者：kradcigam (赞：5)

看一下数据范围发现基本上标算应该是 $O(n^3)$ 了、

我们考虑 $3$ 方的 $dp$。

首先 $\texttt{t}$ 的 $2$ 个字符相等的话，答案为

```cpp
int s=0;
for(int i=1;i<=n;i++)
	if(a[i]==b[1])s++;
s=min(n,s+k);
int x=(s*(s-1)/2);
cout<<x;
```

代码的 $s$ 就是结果 $k$ 次操作，字符串 $\texttt{s}$ 里面最多有 $s$ 个 $\texttt{t}$ 的字符。

我们算一算，发现答案为
$$(s-1)+(s-2)+\cdots+1=\frac{s\times (s-1)}{2}$$
换个角度也可以
$$\begin{pmatrix} s \\ 2 \end{pmatrix} = \frac{s\times (s-1)}{2} $$

那么剩下的情况就是这 $2$ 个字符不同了。

我们想一想，其实，字符串 $\texttt{s}$ 里有多少个字符串 $\texttt{t}$ 就直接看字符串 $\texttt{s}$ 里**每个字符 $\texttt{t}_2$ 前 $\texttt{t}_1$ 的个数。**

举个例子:

```cpp
aababccabb
ab
```

里有多少个子子序列 $\texttt{t}$ 呢

| 字符标号 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 字符 | a | a | b | a | b | c | c | a | b | b |
| 前面 $a$ 的个数 | 0 | 1 | 2 | 2 | 3 | 3 | 3 | 3 | 4 | 4 |
| $ans$ | 0 | 0 | 2 | 2 | 5 | 5 | 5 | 5 | 9 |  13 |

不难发现有 $13$ 个。

我们用 $f_{i,j,k}$ 来 $dp$。

它的意义：
- $i$ 就对应上面的字符编号
- $j$ 指的是前 $i$ 个字符修改了多少个
- $k$ 对应上面的前面 $a$ 的个数

还有一个非常重要的东西，对于一个字符，要么将它修改为 $\texttt{t}_2$、要么将它修改为 $\texttt{t}_1$，要么不修改。

这样我们的状态转移方程就好写了

分别对应不修改

$$f_{i,j,k}=f_{i-1,j,k}$$

修改为 $\texttt{t}_1$
- 如果这个字符本来为 $\texttt{t}_1$，则
	$$f_{i,j,k}=f_{i-1,j,k-1}$$
- 否则
	$$f_{i,j,k}=f_{i-1,j-1,k-1}$$

修改为 $\texttt{t}_2$
- 如果这个字符本来为 $\texttt{t}_2$，则
	$$f_{i,j,k}=f_{i-1,j,k}+k$$
- 否则
	$$f_{i,j,k}=f_{i-1,j-1,k}+k$$

初始化的话先全部赋值为无穷小，再将 $f_{0,i,0}$ 赋值为 $0$（这里 $i\in (1,k)$）

```cpp

// Problem: F. Subsequences of Length Two
// Contest: Codeforces - Codeforces Round #667 (Div. 3)
// URL: https://codeforces.ml/contest/1409/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
int n,k,f[210][210][210];
string a,b;
signed main(){
	memset(f,128,sizeof(f));
	read(n);read(k);
	cin>>a>>b;
	a=' '+a;b=' '+b;
	if(b[1]==b[2]){
		int s=0;
		for(int i=1;i<=n;i++)
			if(a[i]==b[1])s++;
		s=min(n,s+k);
		int x=(s*(s-1)/2);
		cout<<x;
		return 0;
	}
	for(int i=0;i<=k;i++)f[0][i][0]=0;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=k;j++)
			for(int l=0;l<=i;l++){
				f[i][j][l]=f[i-1][j][l];
				if(a[i]==b[1])f[i][j][l]=max(f[i][j][l],f[i-1][j][l-1]);
				else if(j)f[i][j][l]=max(f[i][j][l],f[i-1][j-1][l-1]);
				if(a[i]==b[2])f[i][j][l]=max(f[i][j][l],f[i-1][j][l]+l);
				else if(j)f[i][j][l]=max(f[i][j][l],f[i-1][j-1][l]+l);
			}
	int ans=0;
	for(int i=0;i<=n;i++)ans=max(ans,f[n][k][i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：big_news (赞：3)

[蒟蒻的Div3题解](https://big-news.cn/2020/09/05/%E3%80%8C%E8%A7%A3%E9%A2%98%E6%8A%A5%E5%91%8A%E3%80%8DCodeforces%20Round%20667%20(Div.%203)/)

简单 DP 题。

设 $f[i,j,k]$ 表示考虑 $s[1:i]$ 中，$t[1]$ 出现了 $j$ 次，当前改动了 $k$ 次的方案数，就可以转移了。

具体来讲，考虑 $i\to i+1$，我们有两种选择：
1. 什么都不做，转移到 $f[i+1,c+0/1,k]$；
2. 把这一位改成 $t_1$，转移到 $f[i+1,c+1,k+1]$
3. 把这一位改成 $t_2$，转移到 $f[i+1,c,k+1]+c$

最后特殊考虑一下 $t[1]=t[2]$ 的情况即可，时间复杂度 $O(n^3)$。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

#define int long long
const int CN = 210;

int read(){
    int s = 0,ne = 1; char c = getchar();
    while(c < '0' || c > '9') ne = c == '-' ? -1 : 1, c = getchar();
    while(c >= '0' && c <= '9') s = (s << 1) + (s << 3) + c - '0', c = getchar();
    return s * ne;
}

int n, d, f[CN][CN][CN], ans; char s[CN], c1, c2;

void DP1(){
    memset(f, -0x3f, sizeof(f)), f[0][0][0] = 0; int c = 0; 
    for(int i = 1; i <= n; i++){
        f[i][c + (s[i] == c1)][0] = f[i - 1][c][0];
        c += (s[i] == c1); if(s[i] == c2) f[i][c][0] += c;
    }
    for(int k = 0; k <= d; k++)
      for(int c = 0; c <= n; c++)
        for(int i = 0; i <= n; i++){
          if(s[i + 1] == c2) f[i + 1][c][k] = max(f[i + 1][c][k], f[i][c][k] + c);
          else if(s[i + 1] == c1) f[i + 1][c + 1][k] = max(f[i + 1][c + 1][k], f[i][c][k]);
          else f[i + 1][c][k] = max(f[i + 1][c][k], f[i][c][k]);
          if(s[i + 1] != c1) f[i + 1][c + 1][k + 1] = max(f[i + 1][c + 1][k + 1], f[i][c][k]);
          if(s[i + 1] != c2) f[i + 1][c][k + 1] = max(f[i + 1][c][k + 1], f[i][c][k] + c);
        }
}
void DP2(){
    memset(f, -0x3f, sizeof(f)), f[0][0][0] = 0; int c = 0; 
    for(int i = 1; i <= n; i++){
        f[i][c + (s[i] == c1)][0] = f[i - 1][c][0];
        if(s[i] == c1) c++, f[i][c][0] += c - 1;
    }
    for(int k = 0; k <= d; k++)
      for(int c = 0; c <= n; c++)
        for(int i = 0; i <= n; i++){
          if(s[i + 1] == c1) f[i + 1][c + 1][k] = max(f[i + 1][c + 1][k], f[i][c][k] + c);
          else f[i + 1][c][k] = max(f[i + 1][c][k], f[i][c][k]);
          if(s[i + 1] != c1) f[i + 1][c + 1][k + 1] = max(f[i + 1][c + 1][k + 1], f[i][c][k] + c);
        }
}

signed main(){
    freopen("_in.in", "r", stdin);

    n = read(), d = read(), cin >> (s + 1) >> c1 >> c2;
    
    if(c1 != c2) DP1(); else DP2();
    for(int x = 0; x <= n; x++) 
        for(int k = 0; k <= d; k++)
            ans = max(ans, f[n][x][k]);
    
    printf("%lld", ans);
}
```

---

## 作者：Theophania (赞：2)

现有的题解已经把问题分析的很清楚了，但是看了看代码还没人写记忆化搜索，所以提供一个记搜的代码。其实原理和DP是一样的，但是个人感觉记搜更好写。

```cpp
int solve(int pos, int dep, int sum)
{
    if (pos == n)
        return 0;
    int &ret = dp[pos][dep][sum];
    if (ret >= 0)
        return ret;
    ret = (s[pos] == t[1]) * sum + solve(pos + 1, dep, sum + (s[pos] == t[0]));
    if (dep > 0)
    {
        ret = max(ret, solve(pos + 1, dep - 1, sum + 1));
        ret = max(ret, sum + solve(pos + 1, dep - 1, sum));
    }
    return ret;
}
```

不要忘记初始化并特判 $t$ 串两个字符相同的情况。

```cpp
int n, k, dp[209][209][209];
string s, t;
signed main()
{
    cin >> n >> k;
    cin >> s >> t;
    if (t[0] == t[1])
    {
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            if (s[i] == t[0])
                cnt++;
        cnt += min(k, n - cnt);
        cout << cnt * (cnt - 1) / 2 << endl;
        return 0;
    }
    memset(dp, -1, sizeof(dp));
    cout << solve(0, k, 0) << endl;
    return 0;
}
```


---

## 作者：SSerxhs (赞：2)

简单 dp 题

设 $f_{i,j,k}$ 表示考虑到第 $i$ 个字符，左侧（含 $i$）有 $j$ 个 $T_1$，用了 $k$ 次修改的最大当前答案，则 dp 方程可见代码（注释为对第 $i$ 个字符的操作）

注意特判 $T_1=T_2$ 情况

```
#include <bits/stdc++.h>
using namespace std;
const int N=202,inf=-1e9;
int f[N][N][N],s[N];
int c,n,m,i,j,k=0,ans,cnt;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
int main()
{
	read(n);read(m);c=getchar();
	while ((c<'a')||(c>'z')) c=getchar();
	s[1]=c;
	for (i=2;i<=n;i++) s[i]=getchar();c=getchar();
	while ((c<'a')||(c>'z')) c=getchar();
	i=c;j=getchar();
	if (i==j)
	{
		for (i=1;i<=n;i++) if (s[i]==j) ++k;
		k=min(k+m,n);if (!k) return puts("0"),0;
		return printf("%d",k*(k-1)>>1),0;
	}//特判
	for (k=1;k<=n;k++) if (s[k]==i) s[k]=1; else if (s[k]==j) s[k]=2; else s[k]=0;
	for (i=0;i<=n;i++) for (j=0;j<=n;j++) for (k=0;k<=m;k++) f[i][j][k]=inf;
	f[0][0][0]=0;
	for (i=1;i<=n;i++)
	{
		for (j=0;j<=i;j++) for (k=0;(k<=m)&&(k<=i);k++)
		{
			if (s[i]==1)//1表示T串第1个字符
			{
				if (j) f[i][j][k]=f[i-1][j-1][k];//不改
				if (k) f[i][j][k]=max(f[i][j][k],f[i-1][j][k-1]+j);//改为2
			}
			else if (s[i]==2)//2表示T串第2个字符
			{
				f[i][j][k]=f[i-1][j][k]+j;//不改
				if (j&&k) f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k-1]);//改为1
			} else
			{
				f[i][j][k]=f[i-1][j][k];//不改
				if (k)
				{
					if (j) f[i][j][k]=max(f[i][j][k],f[i-1][j-1][k-1]);//改为1
					f[i][j][k]=max(f[i][j][k],f[i-1][j][k-1]+j);//改为2
				}
			}
		}
	}
	for (j=0;j<=n;j++) for (k=0;k<=m;k++) ans=max(ans,f[n][j][k]);
	printf("%d",ans);
}
```

---

## 作者：Anita_Hailey (赞：2)

# CF1409F Solution

div. 3 的 F 不是很难

考虑 dp，设记状态 $dp[i][j][k]$ 为已经做到了 $i$ 的位置，然后用了 $j$ 个机会，之前有 $k$ 个 `character` 和 $t[0]$ 一样。

那么，我们显然可以得到 dp，方程，这个位置会可以有决策。

```c++
dp[ i + 1 ][ j + 1 ][ l + 1 ] = std::max( dp[ i + 1 ][ j + 1 ][ l + 1 ], dp[ i ][ j ][ l ] + ( t[ 0 ] == t[ 1 ] ) * l );
dp[ i + 1 ][ j + 1 ][ l + ( t[ 0 ] == t[ 1 ] ) ] = std::max( dp[ i + 1 ][ j + 1 ][ l + ( t[ 0 ] == t[ 1 ] ) ], dp[ i ][ j ][ l ] + l );
dp[ i + 1 ][ j ][ l + ( s[ i ] == t[ 0 ] ) ] = std::max( dp[ i + 1 ][ j ][ l + ( s[ i ] == t[ 0 ] ) ], dp[ i ][ j ][ l ] + ( s[ i ] == t[ 1 ] ) * l );
```

- 第一行表示，这个位置改成 $t[0]$
- 第二行表示，这个位置搞成 $t[0]$
- 第三行表示，这个东西如果和 $t[0]$ 或者 $t[1]$ 相等的决策。

好像没什么好说的了。

详细实现看代码

```
#include <bits/stdc++.h>
const int N = 202;
using std::string;
using std::cin;
using std::cout;
string s, t; 
int n, k, ans, dp[ N ][ N ][ N ];
int main( )
{
 memset( dp, -63, sizeof dp );
 cin >> n >> k >> s >> t;
 dp[ 0 ][ 0 ][ 0 ] = 0;
 for( int i = 0; i < n; ++i ) for( int j = 0; j <= k; ++j ) for( int l = 0; l <= i; ++l )
 {
  dp[ i + 1 ][ j + 1 ][ l + 1 ] = std::max( dp[ i + 1 ][ j + 1 ][ l + 1 ], dp[ i ][ j ][ l ] + ( t[ 0 ] == t[ 1 ] ) * l );
  dp[ i + 1 ][ j + 1 ][ l + ( t[ 0 ] == t[ 1 ] ) ] = std::max( dp[ i + 1 ][ j + 1 ][ l + ( t[ 0 ] == t[ 1 ] ) ], dp[ i ][ j ][ l ] + l );
  dp[ i + 1 ][ j ][ l + ( s[ i ] == t[ 0 ] ) ] = std::max( dp[ i + 1 ][ j ][ l + ( s[ i ] == t[ 0 ] ) ], dp[ i ][ j ][ l ] + ( s[ i ] == t[ 1 ] ) * l );
 }
 for( int j = 0; j <= k; ++j ) for( int l = 0; l <= n; ++l )
  ans = std::max( ans, dp[ n ][ j ][ l ] );
 cout << ans;
 return 0;
}
```



---

