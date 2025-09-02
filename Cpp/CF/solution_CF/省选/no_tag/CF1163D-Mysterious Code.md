# Mysterious Code

## 题目描述

在一次普通的森林散步中，Katie 偶然发现了一段神秘的代码！然而，这段神秘代码中有些字符无法辨认。她将这段代码记录为一个字符串 $c$，其中包含小写英文字母和星号（“\*”），每个星号表示一个无法辨认的字符。Katie 对她的发现感到非常兴奋，决定通过将每个星号替换为任意小写英文字母（不同的星号可以替换为不同的字母）来恢复这些无法辨认的字符。

Katie 有一个喜欢的字符串 $s$ 和一个不太喜欢的字符串 $t$。她希望恢复出的神秘代码中，$s$ 出现的次数尽可能多，而 $t$ 出现的次数尽可能少。形式化地，设 $f(x, y)$ 表示字符串 $y$ 在字符串 $x$ 中出现的次数（例如，$f(aababa, ab) = 2$）。Katie 想要恢复出一个符合原始 $c$ 的字符串 $c'$，使得 $f(c', s) - f(c', t)$ 的值最大。但 Katie 并不擅长恢复代码，所以她希望你来帮助她。

## 说明/提示

在第一个样例中，若 $c'$ 为 "katie"，则 $f(c', s) = 1$，$f(c', t) = 0$，因此 $f(c', s) - f(c', t) = 1$，这是最大的可能值。

在第二个样例中，唯一符合给定 $c$ 的 $c'$ 是 "caat"。此时 $f(c', s) - f(c', t) = 1 - 2 = -1$。

在第三个样例中，有多种方式恢复代码使得 $f(c', s) - f(c', t)$ 达到最大，例如 "aaa"、"aac" 或 "zaz"。这些恢复后的代码 $f(c', s) - f(c', t) = 0$。

在第四个样例中，最优的恢复代码 $c'$ 是 "ccc"。此时 $f(c', s) - f(c', t) = 2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
*****
katie
shiro
```

### 输出

```
1
```

## 样例 #2

### 输入

```
caat
caat
a
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
*a*
bba
b
```

### 输出

```
0
```

## 样例 #4

### 输入

```
***
cc
z
```

### 输出

```
2
```

# 题解

## 作者：ln001 (赞：4)

## 闲话和约定
头一次听说 kmp 也有自动机，不过作者菜所以**本题解没有使用** kmp 自动机，而是用普通 kmp 在**较差的复杂度**下通过的。

想学 kmp 自动机的话可以看[这道题](https://www.luogu.com.cn/problem/CF1721E)。

需要注意的是，本题解中的**变量名称**和原题中的不太一样，在题意部分会说明。

字符串的下标默认从 $1$ 开始，两个字符串相加即为字符串拼接。

字符串的 border 为该字符串非本身的极长前缀后缀**的长度**。
## 题意
给定长度不超过 $1000$ 的一个字符串 $s$ 及长度不超过 $50$ 的两个字符串 $t1, t2$，其中 $t1, t2$ 均由小写字母组成，$s$ 由小写字母和星号组成。

记 $f(s, t)$ 表示 $s$ 中 $t$ 的出现次数，例如 $s, t$ 分别为 aaa 和 aa 时，函数值为 $2$。

现在需要找到一种将 $s$ 中的星号全部替换为小写字母的方案，使得 $f(s, t1) - f(s, t2)$ 最大，求最大值。

## 做法
由于是字符串匹配问题，显然需要 kmp。因为 $s$ 不是模式串且需要逐位确定字母，不难想到本题需要利用 $t1,t2$ 的 $next$ 数组。因此第一步是先对 $t1,t2$ 跑 kmp 预处理。

对于最优类问题，显然 dp。三个串的信息都是不可或缺的，因此设三维 $f_{i, j, k}$ 表示串 $s$ 确定完位置 $i$，字符串 $t1 + \text{\#} + s_{1\cdots i}$ 的 border 为 $j$，字符串 $t2 + \text{\#} + s_{1\cdots i}$ 的 border 为 $k$ 的情况下，$f(s_{1\cdots i}, t1) - f(s_{1\cdots i}, t2)$ 的值最大是多少。

转移采取[刷表法](https://www.cnblogs.com/Renyi-Fan/p/7501123.html#:~:text=%E8%A1%A8%E6%B3%95%EF%BC%9A-,%E7%94%B1%E5%BD%93%E5%89%8D%E7%82%B9%E7%9A%84%E7%8A%B6%E6%80%81%EF%BC%8C%E6%9B%B4%E6%96%B0%E5%85%B6%E4%BB%96%E7%82%B9%E7%9A%84%E7%8A%B6%E6%80%81,-%E3%80%82%E9%9C%80%E8%A6%81%E6%B3%A8%E6%84%8F%EF%BC%9A%E5%8F%AA%E7%94%A8)，每次考虑将 $s$ 向外扩一个字符，如果扩到了星号，就**枚举小写字母**然后像扩到了小写字母一样做。

如果扩到了小写字母，对于当前状态对应的两个 border，直接像做普通 kmp 扩新字符一样，找到新对应的两个 border $a, b$，转移取最大值即可。

需要注意两种情况，若 $a$ 为 $t1$ 的长度，即出现了一次匹配成功的情况， $a$ 需要跳回 $t1$ 的 border，为下一次匹配做准备，且新转移的状态的值为当前状态的值加一，毕竟这是题意。

若 $b$ 为 $t2$ 的长度同理。

最终答案为将 $s$ 所有字符考虑进去，即 dp 第一维为 $n$ 时，任意一组 border 的 dp 值的最大值。

[Code](https://vjudge.net/solution/56245583/1EEXdKYzyjqWl1LtVvju)

---

## 作者：SDqwq (赞：4)

## 题意

给一个主串，并把其中每个 `*` 都填成一个小写字母。再给出两个模式串 $s$ 和 $t$，最大化填完每个 `*` 后 $s$ 出现的次数和 $t$ 出现的次数之差并输出。

## 思路

要确定每个 `*` 填的字母自然而然想到 dp。

要匹配 $s$ 和 $t$ 自然能想到 KMP。

但是每个 `*` 的确定会导致当前匹配到的位置不一定，所以我们需要对于 $s$ 和 $t$ 都建出 KMP 自动机，并记录到 dp 状态里，方便我们实时确定当前 $s$ 串和  $t$ 串分别匹配到的位置。

设 $f(i,j,k)$ 表示当前主串已经确定了前 $i$ 位，在 $s$ 串 KMP 自动机上的第 $j$ 个状态，在 $t$ 串 KMP 自动机上的第 $k$ 个状态，所能得到的最大出现次数的差值。

容易有转移：

$$
f(i,j,k)+w\to f(i+1,gos_{j,p},got_{k,p})
$$

其中 $w$ 表示前 $i$ 位加上新来的字符 $p$ 之后匹配次数差值的变化量。分别判断一下新到的自动机状态是不是结尾状态即可。

如果主串的第 $i+1$ 位不是 `*`，那么 $p$ 只能为主串的第 $i+1$ 位。

否则 $p$ 可以取到每一个小写字母。

时间复杂度 $\mathcal{O}(nm^2S)$，其中 $S$ 为字符集大小。

## 代码

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1005, M = 55, S = 26;

char s[N], a[M], b[M];
int n, la, lb, ans = -1e9, nxta[M], nxtb[M], goa[M][S], gob[M][S], f[N][M][M];

void get_nxt(char *s, int *nxt, int go[][S]) {
	int len = strlen(s + 1);
	for (int i = 2, j = 0; i <= len; i++) {
		while (j && s[i] != s[j + 1]) j = nxt[j];
		if (s[i] == s[j + 1]) j++;
		nxt[i] = j;
	}
	for (int i = 0; i <= len; i++)
		for (int j = 0; j < 26; j++) {
			if (s[i + 1] == j + 'a') go[i][j] = i + 1;
			else go[i][j] = go[nxt[i]][j];
		}
}

int main() {
	scanf("%s %s %s", s + 1, a + 1, b + 1);
	n = strlen(s + 1);
	la = strlen(a + 1);
	lb = strlen(b + 1);
	get_nxt(a, nxta, goa);
	get_nxt(b, nxtb, gob);
	memset(f, -0x3f, sizeof(f));
	f[0][0][0] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j <= la; j++)
			for (int k = 0; k <= lb; k++) {
				if (s[i + 1] != '*') {
					int c = s[i + 1] - 'a', w = 0;
					if (goa[j][c] == la) w++;
					if (gob[k][c] == lb) w--;
					f[i + 1][goa[j][c]][gob[k][c]] = max(f[i + 1][goa[j][c]][gob[k][c]], f[i][j][k] + w);
					continue;
				}
				for (int p = 0; p < 26; p++) {
					int w = 0;
					if (goa[j][p] == la) w++;
					if (gob[k][p] == lb) w--;
					f[i + 1][goa[j][p]][gob[k][p]] = max(f[i + 1][goa[j][p]][gob[k][p]], f[i][j][k] + w);
				}
			}
	for (int i = 0; i <= la; i++)
		for (int j = 0; j <= lb; j++) ans = max(ans, f[n][i][j]);
	printf("%d", ans);
	return 0;
}
```

---

## 作者：Purple_wzy (赞：3)

# CF1163&558Div.2D题解
	本蒟蒻第二场cf~
    本题主要考察DP和字符串匹配KMP。
    我们设f[i][j][k]表示，文本串从左到右匹配到第i位，s串匹配到第j
    位，t串匹配到第k位时的最大的f(c,s)−f(c,t)。
    在进行DP之前，先对s串和t串进行一次KMP，得到两个next数组。接下
    来，DP的转移方程可以分两种情况讨论：第i位是不是‘*’。如果是，
    直接暴力枚举‘a’到‘z’，如果不是，就无需枚举。
    然后再枚举j和k，转移方程即为：
###     f[i][p1][p2]=f[i-1][j][k]+W;
	具体实现还是看代码~
   ```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
#define I inline void
#define IN inline int
typedef long long ll;
I read(int &res){
    re g=1;register char ch=getchar();res=0;
    while(!isdigit(ch)){
        if(ch=='-')g=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    res*=g;
}
char c[1010],s[100],t[100];
int n,m,l,pos,nt[100],nxt[100],f[1010][60][60],v[1010][60][60];
int main(){
    scanf("%s %s %s",c+1,s+1,t+1);
    l=strlen(c+1);
    n=strlen(s+1);
    m=strlen(t+1);
    nt[0]=0;pos=0;
    nt[1]=0;
    F(i,2,n){
        while(pos&&s[pos+1]!=s[i])pos=nt[pos];
        if(s[pos+1]==s[i])pos++;
        nt[i]=pos;
    }
    nxt[0]=nxt[1]=0;pos=0;
    F(i,2,m){
        while(pos&&t[pos+1]!=t[i])pos=nxt[pos];
        if(t[pos+1]==t[i])pos++;
        nxt[i]=pos;
    }//分别求出s串和t串的next数组 
    memset(v,0,sizeof(v));
    re p1,p2,W;
    v[0][0][0]=1;//用v数组表示这种状态是否存在 
    F(i,1,l){
        if(c[i]!='*'){
            F(j,0,n-1){
                F(k,0,m-1){
                    if(!v[i-1][j][k])continue;
                    W=0;
                    for(p1=j;p1&&s[p1+1]!=c[i];p1=nt[p1]){
                        
                    } 
                    for(p2=k;p2&&t[p2+1]!=c[i];p2=nxt[p2]){
                        
                    }
                    if(s[p1+1]==c[i])p1++;
                    if(t[p2+1]==c[i])p2++;//分别在s串和t串上匹配 
                    if(p1==n){
                    W++;
                        p1=nt[p1];	
                    }//s串匹配成功，答案W++ 
                    if(p2==m){
                        W--;
                        p2=nxt[p2];
                    } //t串匹配成功，答案W--
					//此外，由于j和k的取值范围为[0,n-1],[0,m-1],匹配成功时需要转到它的next 
                    if(!v[i][p1][p2])f[i][p1][p2]=f[i-1][j][k]+W;
                    else f[i][p1][p2]=max(f[i][p1][p2],f[i-1][j][k]+W);//读者可以自行理解一下，这里为什么要这么做（其实也可以不这么麻烦） 
                    v[i][p1][p2]=1;
                }
            }
        }
        else{
            F(bas,'a','z'){//第i位为'*'时，暴力枚举'a'到'z' 
                c[i]=bas;
                //同上 
                F(j,0,n-1){
                    F(k,0,m-1){
                        if(!v[i-1][j][k])continue;
                        W=0;
                        for(p1=j;p1&&s[p1+1]!=c[i];p1=nt[p1]){
                        
                        }
                        for(p2=k;p2&&t[p2+1]!=c[i];p2=nxt[p2]){
                        
                        }
                        if(s[p1+1]==c[i])p1++;
                        if(t[p2+1]==c[i])p2++;
                        if(p1==n){
                            W++;
                            p1=nt[p1];	
                        }
                        if(p2==m){
                            W--;
                            p2=nxt[p2];
                        }
                        if(!v[i][p1][p2])f[i][p1][p2]=f[i-1][j][k]+W;
                        else f[i][p1][p2]=max(f[i][p1][p2],f[i-1][j][k]+W);
                        v[i][p1][p2]=1;
                    }
                }
            }
            
        }		
    }
    re ans=-20000;//一定要注意，答案可能会是负数，极限情况下，答案将会是-m 
    F(i,0,n-1){
        F(j,0,m-1){
            if(v[l][i][j])ans=max(ans,f[l][i][j]);//更新答案 
        }
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：caidzh (赞：1)

此题也可以使用 AC 自动机解决

首先可以看出是字典树有关的，显然要在字典树上跑 DP

但是如果加上一个不匹配字符就可能跑到另一个节点，这时就可以想到 AC 自动机

在 AC 自动机上每个节点记录这个节点表示的前缀的后缀是否包含串 s 和串 t，记$f_{i,j}$表示填到第$i$个位置，在字典树上第$j$个节点的最优答案，据此 DP 一下就完了
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define db double
#define INF 2147483647
#define LLINF 9223372036854775807
#define LL long long
using namespace std;
int inline read(){
    int num=0,neg=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')neg=-1;c=getchar();}
    while(isdigit(c)){num=(num<<3)+(num<<1)+c-'0';c=getchar();}
    return num*neg;
}
const int maxn=1010;
int n,l1,l2;char str[maxn],s[maxn],t[maxn];
int ch[maxn][26],fail[maxn],sum[maxn],f[maxn][maxn],cnt;
void insert(char *str,int n,int flg){
	int now=0;
	for(int i=1;i<=n;i++){
		if(!ch[now][str[i]-'a'])ch[now][str[i]-'a']=++cnt;
		now=ch[now][str[i]-'a'];
	}sum[now]+=flg;
}queue<int>que;int q[maxn],r;
void bfs(){
	que.push(0);
	while(!que.empty()){
		int x=que.front();q[++r]=x;que.pop();
		if(!x){
			for(int i=0;i<26;i++)
				if(ch[0][i])fail[ch[0][i]]=0,que.push(ch[0][i]);continue;
		}
		for(int i=0;i<26;i++)
			if(ch[x][i]){
				fail[ch[x][i]]=ch[fail[x]][i];que.push(ch[x][i]);
			}else ch[x][i]=ch[fail[x]][i];
	}for(int i=2;i<=r;i++)sum[q[i]]+=sum[fail[q[i]]];
}
int main()
{
	scanf("%s",str+1);n=strlen(str+1);
	scanf("%s",s+1);l1=strlen(s+1);insert(s,l1,1);
	scanf("%s",t+1);l2=strlen(t+1);insert(t,l2,-1);bfs();
	for(int i=0;i<=n;i++)
		for(int j=0;j<=cnt;j++)f[i][j]=-INF/3;f[0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<=cnt;j++){
			if(f[i][j]==-INF/3)continue;
			for(int k=0;k<26;k++){
				if(str[i+1]!=k+'a'&&str[i+1]!='*')continue;int to=ch[j][k];
				f[i+1][to]=max(f[i+1][to],f[i][j]+sum[to]);
			}
		}
	}int ans=-INF;
	for(int i=0;i<=cnt;i++)ans=max(ans,f[n][i]);
	printf("%d",ans);return 0;
}
```


---

## 作者：CQ_Bab (赞：0)

# 前言
~~这题能紫~~？

不知道为什么其他大佬都要用 kmp 或者 AC 自动机，本人用的是暴力。
# 思路
首先可以考虑一个 dp，我们定义 $f_{i,j,k}$ 表示现在放到了 $i$ 能与 $S$ 的前 $j$ 个匹配能与 $T$ 的前 $k$ 个匹配的最大值，然后我们考虑用 $i$ 去推 $i+1$ 我们发现可以枚举当前点填什么然后就只需要更新 $j,k$ 即可，我们发现 $|S|\leq 50$ 考虑用 $nxt_{i,j}$ 表示当 $S$ 中匹配到 $i$ 时再添加一个 $j$ 最多能匹配到哪里，因为 $S$ 的长度很小所以可以直接暴力处理，然后对于 $T$ 也一样处理一个 $nxt$ 即可。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
string s;
string a,b;
const int N=1e3+10,M=55;
int f[N][M][M],nxt[2][M][M];
void init(string s,int opt) {//预处理
	int n=s.size()-1;
	string st=" ";
	nxt[opt][0][s[1]-'a']=1;
	rep(i,1,n) {
		st+=s[i];
		rep(j,0,25) {
			st+=(j+'a');
			int Max=false;
			rep1(k,i+1,1) {
				int f=0;
				int ll=i+1-k+1;
				rep(l,1,k) {
					if(s[l]!=st[ll+l-1]) {
						f=1;
						break;
					}
				}
				if(!f) {
					nxt[opt][i][j]=k;
					break;
				}
			}
			st.pop_back();
		}
	}
}
void solve() {
	cin>>s>>a>>b;
	s=" "+s;
	a=" "+a;
	b=" "+b;
	init(a,0);
	init(b,1);
	int n=s.size()-1,m=a.size()-1,mm=b.size()-1;
	memset(f,-0x3f,sizeof f);
	f[0][0][0]=0;
	rep(i,0,n-1) {
		rep(j,0,m) {
			rep(k,0,mm) {
				rep(l,0,25) {//暴力 dp
					if(s[i+1]!='*'&&s[i+1]!=l+'a') continue;
					int jj=nxt[0][j][l],kk=nxt[1][k][l];
					f[i+1][jj][kk]=max(f[i+1][jj][kk],f[i][j][k]-(kk==mm)+(jj==m));
				}
			}
		}
	}
	int res=-1e18;
	rep(j,0,m) {
		rep(k,0,mm) {
			res=max(res,f[n][j][k]);
		}
	}cout<<res<<endl;
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

---

## 作者：james1BadCreeper (赞：0)

找一个模式串在字符串中的出现次数，而看到可以在 * 上填任意一个字母又是经典 DP 问题。对 $s,t$ 建出 KMP 自动机，设 $f(i,j,k)$ 考虑到 $c$ 的第 $i$ 位，此时在 $s$ 的 KMP 自动机的节点 $j$，$t$ 的 KMP 自动机的节点 $k$ 的最大答案。采用刷表法转移，模式串 $S$ 在转移到节点 $|S|$ 时有贡献。初始 $f(0,0,0)=0$，转移 $f(i+1,trs_{j,c_{i+1}},trt_{k,c_{i+1}})=\max\{f(i,j,k)+w\}$，目标 $\max\{f(n,j,k)\}$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define rep(i, l, r) for (int i = l; i <= r; ++i)

using namespace std;

int n, ls, lt, nxts[55], nxtt[55], trs[55][26], trt[55][26];
char a[1005], s[55], t[55];
int f[1005][55][55];

void KMP(char *s, int len, int *nxt, int tr[][26]) {
    for (int i = 2, p = 0; i <= len; ++i) {
        while (p && s[i] != s[p + 1]) p = nxt[p];
        if (s[i] == s[p + 1]) ++p;
        nxt[i] = p;
    }
    rep(i, 0, len) rep(j, 0, 25) {
        if (i < len && s[i + 1] == j + 'a') tr[i][j] = i + 1; 
        else if (i) tr[i][j] = tr[nxt[i]][j];
    }
}
void ckmax(int &x, int t) { if (x < t) x = t; }

int main(void) {
    scanf("%s%s%s", a + 1, s + 1, t + 1);
    n = strlen(a + 1); ls = strlen(s + 1); lt = strlen(t + 1);
    KMP(s, ls, nxts, trs); KMP(t, lt, nxtt, trt);
    memset(f, 0xbf, sizeof f); f[0][0][0] = 0;
    rep(i, 0, n - 1) rep(j, 0, ls) rep(k, 0, lt) rep(p, 0, 25) if (a[i + 1] == '*' || a[i + 1] == p + 'a') {
        int w = 0;
        if (trs[j][p] == ls) ++w; if (trt[k][p] == lt) --w; 
        ckmax(f[i + 1][trs[j][p]][trt[k][p]], f[i][j][k] + w);
    }
    int ans = -1e9;
    rep(i, 0, ls) rep(j, 0, lt) ans = max(ans, f[n][i][j]);
    return printf("%d\n", ans), 0;
}
```

---

## 作者：EuphoricStar (赞：0)

~~zxx 的题单来的（~~

发一个无脑 kmp 自动机 + dp 做法。

看到题就很 dp，考虑设计状态。显然填字母时要知道当前串与 $s,t$ 的匹配位数，否则就不知道 $s,t$ 是否完整出现。设 $f_{i,j,k}$ 表示填到 $c$ 的第 $i$ 个字符，与 $s$ 匹配 $j$ 位，与 $t$ 匹配 $k$ 位。转移可以枚举下一位填的字母。

发现我们需要求出某个串的前 $i$ 位后接一个字符的匹配位数，这不就是 kmp 自动机干的事情吗。。。于是对 $s,t$ 建 kmp 自动机，转移就很简单了，大概是 $f_{i,j',k'} \gets f_{i,j,k} + [j'=|s|] - [k'=|t|]$。

时间复杂度 $O(26|c||s||t|)$。

[code](https://codeforces.com/contest/1163/submission/187103031)，[双倍经验](https://www.luogu.com.cn/problem/CF808G)

---

