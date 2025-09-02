# Three Religions

## 题目描述

During the archaeological research in the Middle East you found the traces of three ancient religions: First religion, Second religion and Third religion. You compiled the information on the evolution of each of these beliefs, and you now wonder if the followers of each religion could coexist in peace.

The Word of Universe is a long word containing the lowercase English characters only. At each moment of time, each of the religion beliefs could be described by a word consisting of lowercase English characters.

The three religions can coexist in peace if their descriptions form disjoint subsequences of the Word of Universe. More formally, one can paint some of the characters of the Word of Universe in three colors: $ 1 $ , $ 2 $ , $ 3 $ , so that each character is painted in at most one color, and the description of the $ i $ -th religion can be constructed from the Word of Universe by removing all characters that aren't painted in color $ i $ .

The religions however evolve. In the beginning, each religion description is empty. Every once in a while, either a character is appended to the end of the description of a single religion, or the last character is dropped from the description. After each change, determine if the religions could coexist in peace.

## 说明/提示

In the first example, after the 6th evolution the religion descriptions are: ad, bc, and ab. The following figure shows how these descriptions form three disjoint subsequences of the Word of Universe:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1149B/d2161037f06cd41962d7459e510bbcc1eef61be4.png)

## 样例 #1

### 输入

```
6 8
abdabc
+ 1 a
+ 1 d
+ 2 b
+ 2 c
+ 3 a
+ 3 b
+ 1 c
- 2
```

### 输出

```
YES
YES
YES
YES
YES
YES
NO
YES
```

## 样例 #2

### 输入

```
6 8
abbaab
+ 1 a
+ 2 a
+ 3 a
+ 1 b
+ 2 b
+ 3 b
- 1
+ 2 z
```

### 输出

```
YES
YES
YES
YES
YES
NO
YES
NO
```

# 题解

## 作者：yuzhechuan (赞：8)

给出一个更为简洁的代码

---

一道新颖的dp好题

---

### 题解：


设f[i][j][k]表示A串匹配到第i个字符，B串匹配到第j个字符，C串匹配到第k个字符时，在模式串中的最短距离，即最左点（串的下标都从1开始）

预处理出nxt[i][c]，表示模式串中，[i,n]区间内，c字符第一次出现的位置

下面是一张cf官方的解释nxt数组的图，它的下标从0开始，也许可以方便理解

![](https://s2.ax1x.com/2019/11/29/QkcqyV.png)

初始化$f[i][j][k]=n+1,f[0][0][0]=0$，意思是假设怎样都匹配失败，都不去匹配才能成功

转移方程如下：

$\small{f[i][j][k]=\min\left \{nxt[f[i-1][j][k]+1][s[1][i]],nxt[f[i][j-1][k]+1][s[2][j]],nxt[f[i][j][k-1]+1][s[3][k]] \right \}}$

意思是，尝试从A串中加个字符找后续位置，从B串中加个字符找后续位置,从C串中加个字符找后续位置，从这三个位置中的最左边的一个那转移

对于插入操作，注意到新增加的状态只有 新字符与另外两个串的每个位置 这至多250*250种状态，对于这些新状态重新跑一遍dp即可

对于删除操作，直接减小相应串长即可

对于答案ans=f[len[1]][len[2]][len[3]]，意思就是三个串全部匹配完后，在模式串中的最左点
	
当ans<=n时，说明是可以在模式串中被匹配完的，输出YES

否则ans=n+1就输出NO
	

特别注意处理nxt数组时，nxt[n+1][]和nxt[n+2][]都要赋为n+1

---

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return  x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

const int N=1e5+5,M=255;
char p[N];
int s[4][M],nxt[N][28],f[M][M][M],n,q,len[4];
/*预处理出nxt[][]数组*/
void init(){
	for(int i=0;i<26;i++) nxt[n+1][i]=nxt[n+2][i]=n+1; //注意这边的[n+2]
	for(int i=n;i;i--)
		for(int j=0;j<26;j++){
			if(p[i]==j+'a') nxt[i][j]=i;
			else nxt[i][j]=nxt[i+1][j];
		}
}

void doit(){
	char ch;cin>>ch;
	int id;read(id);
	if(ch=='+'){
		cin>>ch;
		s[id][++len[id]]=ch-'a';
		for(int i=(id==1?len[1]:0);i<=len[1];i++) //三目表达式部分意思是，如果是这个串被修改，那它只要计算新的一位，否则就都要从头开始
			for(int j=(id==2?len[2]:0);j<=len[2];j++)
				for(int k=(id==3?len[3]:0);k<=len[3];k++){
					int &now=f[i][j][k];
					now=n+1; //都先假设不可能
					if(i) now=min(now,nxt[f[i-1][j][k]+1][s[1][i]]); //A串转移
					if(j) now=min(now,nxt[f[i][j-1][k]+1][s[2][j]]); //B串转移
					if(k) now=min(now,nxt[f[i][j][k-1]+1][s[3][k]]); //C串转移
				}
	}
	else{
		len[id]--; //直接删长度
	}
	if(f[len[1]][len[2]][len[3]]<=n) puts("YES"); //最左点在n以内就可行
	else puts("NO");
}

signed main(){
	read(n);read(q);
	scanf("%s",p+1);
	init();
	while(q--) doit();
}
```

---

## 作者：allqpsi (赞：4)

### 考试时只骗了 $15$ 分，现在我来打题解了。

### 思路：

我们一步步慢慢来，先假设只对第一个子串作修改，那么这时明显是一个贪心地做法。即我们对每个字符，取母串中在之前的取到的位置后面的这个字符，那尽量在母串上最靠左。取不到，就是不行了。

我们从上面得出启示，我们可以用 $f[i][j][k]$ 来表示第一、二、三个字符分别取到第几位在母串上最靠左的坐标。思路就是动态规划了。我们就可以由$f[i-1][j][k]$ $f[i][j-1][k]$ $f[i][j][k-1]$ 推来。这里我们做一个预处理 $nxt[i][j]$ 指在母串上字符 $j$ 在第 $i$ 位后第一次出现的坐标，如果没有，就为 $n+1$ 。状态转移方程为：

```cpp
if(i)f[i][j][k]=min(f[i][j][k],nxt[f[i-1][j][k]+1][ss[1][i]]);
if(j)f[i][j][k]=min(f[i][j][k],nxt[f[i][j-1][k]+1][ss[2][j]]);
if(k)f[i][j][k]=min(f[i][j][k],nxt[f[i][j][k-1]+1][ss[3][k]]);
```

对插入操作，新的状态只有新的字符与其他子串所有字符的状态。所以我们就对这些新的状态做动态规划。同时维护一下三个子串的长度与字符。

对删除操作，将那个子串的长度减一。

对输出，如果 $f[len[1]][len[2]][len[3]]$ 为 $n+1$ 就不行，否则可以。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,b,nxt[500005][27],f[305][305][305],siz[4],ss[4][305];
char a;
string s;
int main(){
	cin>>n>>q>>s;
	s=' '+s;
	for(int j=0;j<26;j++){
		for(int i=n+2;i>=1;i--){
			nxt[i][j]=n+1;
		}
	}
	for(int i=1;i<=n;i++){
		nxt[i][s[i]-'a']=i;
	}
	for(int j=0;j<26;j++){
		for(int i=n;i>=1;i--){
			nxt[i][j]=min(nxt[i][j],nxt[i+1][j]);
		}
	}
	while(q--){
		cin>>a>>b;
		if(a=='+'){
			cin>>a;
			ss[b][++siz[b]]=a-'a';
			int i=0,j=0,k=0,si=0,sj=0,sk=0;
			if(b==1){
				si=siz[1];
			}
			if(b==2){
				sj=siz[2];
			}
			if(b==3){
				sk=siz[3];
			}
			for(i=si;i<=siz[1];i++){
				for(j=sj;j<=siz[2];j++){
					for(k=sk;k<=siz[3];k++){
						f[i][j][k]=n+1;
						if(i){
							f[i][j][k]=min(f[i][j][k],nxt[f[i-1][j][k]+1][ss[1][i]]);
						}
						if(j){
							f[i][j][k]=min(f[i][j][k],nxt[f[i][j-1][k]+1][ss[2][j]]);
						}
						if(k){
							f[i][j][k]=min(f[i][j][k],nxt[f[i][j][k-1]+1][ss[3][k]]);
						}
					}
				}
			}
		}
		else{
			siz[b]--;
		}
		if(f[siz[1]][siz[2]][siz[3]]<=n){
			cout<<"YES"<<endl;
		}
		else{
			cout<<"NO"<<endl;
		}
	}
}
```

~~写完了，我人生第一篇紫题题解就此结束！~~

---

## 作者：djh123 (赞：2)

考虑dp。

设$f[i][j][k]$表示第一个串匹配到$i$，第二个串匹配到$j$，第三个串匹配到$k$的在原串上的最左端点。

为了转移我们求一个数组$nxt$，$nxt[i][j]$表示在原串上的$i$位置的下一个$j$字符的最左位置。

转移考虑最后一个填哪个，显然有转移：
$f[i][j][k] = min(nxt[f[i-1][j][k]][s1[i]], nxt[f[i][j - 1][k]][ s2[j]], nxt[f[i][j][k - 1]][s3[k]])$

这样有一个$O(q*250^3)$的做法。

考虑每次新加一个字符，发现实际上改变的状态个数只有$O(250^2)$级别的，我们对这部分状态直接暴力修改，删除一个字符就直接回退状态，把无用状态清零，这样复杂度变为$O(q*250^2)$，可过。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef unsigned int uint;
typedef double db;
typedef pair <int, int> pii;
typedef vector <int> vi;

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

#define Fi first
#define Se second
#define pb push_back
#define mp make_pair
#define rep(x, a, b) for(int x = (a); x <= (b); ++ x)
#define per(x, a, b) for(int x = (a); x >= (b); -- x)
#define rop(x, a, b) for(int x = (a); x < (b); ++ x)
#define por(x, a, b) for(int x = (a); x > (b); -- x)
#define forE(x, a) for(int x = head[a]; x; x = nxt[x])

#ifdef DEBUG
#define debug(x) cerr << #x << ": " << x << '\n'
#else
#define debug(x)
#endif

void open(const char *s){
    #ifdef DEBUG
    char str[100];
    sprintf(str,"%s.in",s);
    freopen(str,"r",stdin);
    sprintf(str,"%s.my",s);
    freopen(str,"w",stdout);
    #endif
}

const db eps = 1e-8;
const int inf = 0x3f3f3f3f;
const int Minf = 0x7f7f7f7f;
const LL INF = 0x3f3f3f3f3f3f3f3fll;
const LL MINF = 0x7f7f7f7f7f7f7f7fll;

const int N = 5e5 + 50;

char s[N], p[10], opt[10];
vector <int> S[4];

int nxt[N][26];
int f[255][255][255];


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    cin >> (s + 1);
    rep(i, 0, 25) nxt[n][i] = n + 1, nxt[n + 1][i] = n + 1;
    per(i, n - 1, 0) {
        rep(j, 0, 25) nxt[i][j] = nxt[i + 1][j];
        nxt[i][s[i + 1] - 'a'] = i + 1;
    }
    rep(i, 0, 254) rep(j, 0, 254) rep(k, 0, 254) f[i][j][k] = n + 1;
    int L1 = 0, L2 = 0, L3 = 0;
    f[0][0][0] = 0;
    while(q --) {
        int x; cin >> opt >> x;
        if(opt[0] == '+') {
            cin >> p;
            S[x].push_back(p[0] - 'a');
            if(x == 1) {
                ++ L1;
                int i = L1;
                for(int j = 0; j <= L2; ++ j) {
                    for(int k = 0; k <= L3; ++ k) {
                        if(i > 0) f[i][j][k] = min(f[i][j][k], nxt[f[i - 1][j][k]][S[1][i - 1]]);
                        if(j > 0) f[i][j][k] = min(f[i][j][k], nxt[f[i][j - 1][k]][S[2][j - 1]]);
                        if(k > 0) f[i][j][k] = min(f[i][j][k], nxt[f[i][j][k - 1]][S[3][k - 1]]);
                    }
                }
            }
            else if(x == 2) {
                ++ L2;
                for(int i = 0; i <= L1; ++ i) {
                    int j = L2;
                    for(int k = 0; k <= L3; ++ k) {
                        if(i > 0) f[i][j][k] = min(f[i][j][k], nxt[f[i - 1][j][k]][S[1][i - 1]]);
                        if(j > 0) f[i][j][k] = min(f[i][j][k], nxt[f[i][j - 1][k]][S[2][j - 1]]);
                        if(k > 0) f[i][j][k] = min(f[i][j][k], nxt[f[i][j][k - 1]][S[3][k - 1]]);
                    }
                }
            }
            else {
                ++ L3;
                for(int i = 0; i <= L1; ++ i) {
                    for(int j = 0; j <= L2; ++ j) {
                        int k = L3;
                        if(i > 0) f[i][j][k] = min(f[i][j][k], nxt[f[i - 1][j][k]][S[1][i - 1]]);
                        if(j > 0) f[i][j][k] = min(f[i][j][k], nxt[f[i][j - 1][k]][S[2][j - 1]]);
                        if(k > 0) f[i][j][k] = min(f[i][j][k], nxt[f[i][j][k - 1]][S[3][k - 1]]);
                    }
                }
            }
        }
        else {
            S[x].pop_back();
            if(x == 1) {
                int i = L1; rep(j, 0, L2) rep(k, 0, L3) f[i][j][k] = n + 1;
                -- L1;
            }
            else if(x == 2) {
                int j = L2; rep(i, 0, L1) rep(k, 0, L3) f[i][j][k] = n + 1;
                -- L2;
            }
            else {
                int k = L3; rep(i, 0, L1) rep(j, 0, L2) f[i][j][k] = n + 1;
                -- L3;
            }
        }
        if(f[L1][L2][L3] > n) puts("NO");
        else puts("YES");
    }
    return 0;
}
```

---

## 作者：wrzSama (赞：1)

##  题意

给定一个长度为 $n$ ($1 \le n \le 10^5$) 的字符串 $t$ 和 $q$ ($1 \le q \le 10^3$) 次操作。初始时有 $3$ 个空的字符串 $s_1, s_2, s_3$，每次操作会在 $s_1, s_2, s_3$ 中 $1$ 个字符串的末尾添加或删除 $1$ 个字符，保证它们的长度小于 $250$。在每次操作后，你需要回答能否把字符串 $t$ 分成若干个子序列，使得这些子序列中有 $3$ 个恰好与 $s_1, s_2, s_3$ 分别相等。请注意， $t$ 中的每 $1$ 个字符只能出现在 $1$ 个子序列中。

## 思路

设 $dp_{i,j,k}$ 表示分出 $s_1$ 的前 $i$ 个字符、$s_2$ 的前 $j$ 个字符、$s_3$ 的前 $k$ 个字符需要的最短的 $t$ 的前缀的长度，$nxt_{i,j}$ 表示字符串 $t$ 中第 $i$ 个字符后第一个字符 $j$ 的位置，$len1,len2,len3$ 分别表示 $s_1,s_2,s_3$ 的长度。我们可以先预处理出 $nxt$ 数组的值，如果第 $i$ 个字符后没有字符 $j$，就令 $nxt_{i,j}=n+1$。接下来我们考虑 $dp$ 转移，$dp_{i,j,k}=min(nxt_{dp_{i-1,j,k},s1_i},min(nxt_{dp_{i,j-1,k},s2_j},nxt_{dp_{i,j,k-1},s3_k}))$。对于加入 $1$ 个字符的操作，我们可以通过转移方程在 $O(len^2)$ 内求出新增的 $len^2$ 个 $dp$ 状态的值。对于减去 $1$ 个字符的操作，直接令删除字符的字符串的长度减 $1$。最后在每次操作后判断 $dp_{len1,len2,len3}$ 的值是否不大于 $n$ 即可。总时间复杂度为 $O(26 \times n + q \times len^2)$，可以通过本题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int read_result=0,is_below_0=0;
	char now_ch=0;
	while(!isdigit(now_ch))
	{
		is_below_0|=now_ch=='-';
		now_ch=getchar();
	}
	while(isdigit(now_ch))
	{
		read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);
		now_ch=getchar();
	}
	return is_below_0?-read_result:read_result;
}
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n,q,nxt[100005][26],len[4],dp[255][255][255];
string s;
char str[4][255];
int main()
{
	n=read();
	q=read();
	cin>>s;
	for(int i=0;i<26;++i) nxt[n][i]=n+1;
	for(int i=n-1;i>=0;--i)
	{
		for(int j=0;j<26;++j)
		{
			if(s[i]-'a'==j) nxt[i][j]=i+1;
			else nxt[i][j]=nxt[i+1][j];
		}
	}
	while(q--)
	{
		char op;
		cin>>op;
		int x=read();
		if(op=='+')
		{
			str[x][len[x]++]=getchar();
			for(int i=(x==1?len[1]:0);i<=len[1];++i)
			{
				for(int j=(x==2?len[2]:0);j<=len[2];++j)
				{
					for(int k=(x==3?len[3]:0);k<=len[3];++k)
					{
						dp[i][j][k]=n+1;
						if(i&&dp[i-1][j][k]<n) dp[i][j][k]=min(dp[i][j][k],nxt[dp[i-1][j][k]][str[1][i-1]-'a']);
						if(j&&dp[i][j-1][k]<n) dp[i][j][k]=min(dp[i][j][k],nxt[dp[i][j-1][k]][str[2][j-1]-'a']);
						if(k&&dp[i][j][k-1]<n) dp[i][j][k]=min(dp[i][j][k],nxt[dp[i][j][k-1]][str[3][k-1]-'a']);
					}
				}
			}
		}
		else --len[x];
		if(dp[len[1]][len[2]][len[3]]<=n) puts("YES");
		else puts("NO");
	}
	return 0;
}
```


---

## 作者：λᴉʍ (赞：1)

有三个字符串$s_1,s_2,s_3$和一个主串$s$，每次操作改变一个$s_i$（插入或删除字符），每次操作完之后问$s$是否可以分成$3$个子序列正好是$s_1,s_2,s_3$。任意时候$|s_i|\leq 250$。

设$nxt[x][i]$表示主串上字符$i$在$>x$上第一个出现的位置。

设$f[x][y][z]$表示三个串分别匹配到$x,y,z$需要主串的最短长度。

那么这个可以$O(1)$转移，只要枚举拼起来的最后一个字符就行了。

插入最多改变$251^2$个$f$值，每次插入dp一遍多出来的$f$就行了。

https://www.cnblogs.com/xzz_233/p/10798276.html

---

## 作者：Ame_Rain_chan (赞：0)

我们先看简单的情况。

如果我们只修改一个子串，我们就可以贪心的做，即我们对每个字符，取原串在之前取到的位置，如果取不到，就说明没有符合要求的子序列。

现在有三个子串，我们就可以扩展之前的贪心，即我们同时维护三个子串中最靠左的位置。

具体来说，我们设 $f_{i,j,k}$ 为第一个子串长度为 $i$，第二个子串长度为 $j$，第三个子串长度为 $k$ 时，相对应的子序列需要的最短前缀的长度。

然后如何判断是否存在取法就可以了：当 $f_{len_1,len_2,len_3} \le n$ 时，就说明整个前缀能够被原串包含，就有合法的取法。

对于维护这个 $f_{i,j,k}$，我们设 $nxt_{i,j}$ 为位置 $i$ 后第一个字符 $j$ 的位置，如果没有值就为 $n+1$

预处理出 $nxt_{i,j}$，具体就是先将所有 $nxt$ 赋值为 $n+1$（不存在的位置）

再正着遍历原串，赋值 $nxt_{i,s_i}=i$

然后外层循环字母 $j$，内层倒着遍历原串 $i$，更新 $nxt_{i,j}=\min(nxt_{i,j},nxt_{i+1,j})$

> 回顾概念：设 $nxt_{i,j}$ 为位置 $i$ 后第一个字符 $j$ 的位置

$nxt$ 处理完了，现在考虑如何更新（转移）$f_{i,j,k}$。

这是个线性 dp，只需要考虑当前这一位填什么，填到哪里，于是就可以得到转移方程：

$$
f_{i,j,k}=\min(nxt_{[f_{i-1,j,k}+1],s1_i},nxt_{[f_{i,j-1,k}+1],s2_j},nxt_{[f_{i,j,k-1}+1],s3_k})
$$

以及，当我们遇到插入操作时，我们就把对应的子串长度 ++，

这样，我们可以得到一个 $len^3$ 的朴素 dp，无法通过。

考虑优化掉无用转移：

在 dp 过程中，新增的状态只有 $len^2$ 种：

> 因为每次插入只会新加一个字符，当前插入的子串之前的部分相对应的状态不会被影响，这部分就不需要更新了

也就是说，对于插入的子串，我们在遍历（转移）时直接跳过前缀部分。

这样，我们的 dp 时间复杂度优化到了 $len^2$，可以通过。

对于删除操作，我们直接把对应的子串长度 - 1 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
#define fo(i, a, b) for (int i = a; i <= b; i++)
inline char read()
{
    char x = getchar();
    while (x != '+' && x != '-' && (x < 'a' || x > 'z'))
        x = getchar();
    return x;
}
char s[N];
int len[4], n, q;
int f[260][260][260];
int nxt[N][30];
inline void init(char s[])
{
    fo(j, 0, 25)
    {
        fo(i, 1, n + 2)
        {
            nxt[i][j] = n + 1;
        }
    }
    for (int i = 1; i <= n; i++)
        nxt[i][s[i] - 'a'] = i;
    for (int j = 0; j < 26; j++) {
        for (int i = n; i >= 1; i--) {
            nxt[i][j] = min(nxt[i][j], nxt[i + 1][j]);
        }
    }
}
int ss[N][300];
int main()
{
    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);
    init(s);
    while (q--) {
        char op;
        int p;
        op = read();
        scanf("%d", &p);
        if (op == '+') {
            char x;
            x = read();
            int si = 0, sj = 0, sk = 0;
            ss[p][++len[p]] = x - 'a';
            if (p == 1)
                si = len[1];
            else if (p == 2)
                sj = len[2];
            else
                sk = len[3];
            fo(i, si, len[1])
            {
                fo(j, sj, len[2])
                {
                    fo(k, sk, len[3])
                    {
                        f[i][j][k] = n + 1;
                        if (i)
                            f[i][j][k] = min(f[i][j][k], nxt[f[i - 1][j][k] + 1][ss[1][i]]);
                        if (j)
                            f[i][j][k] = min(f[i][j][k], nxt[f[i][j - 1][k] + 1][ss[2][j]]);
                        if (k)
                            f[i][j][k] = min(f[i][j][k], nxt[f[i][j][k - 1] + 1][ss[3][k]]);
                    }
                }
            }
        } else
            len[p]--;
        if (f[len[1]][len[2]][len[3]] <= n)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
/*
sasakure.UK is the only god.
*/
```

---

