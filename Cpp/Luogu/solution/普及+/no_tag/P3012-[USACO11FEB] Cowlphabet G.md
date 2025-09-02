# [USACO11FEB] Cowlphabet G

## 题目描述

Like all bovines, Farmer John's cows speak the peculiar 'Cow'

language. Like so many languages, each word in this language comprises a sequence of upper and lowercase letters (A-Z and a-z).  A word is valid if and only if each ordered pair of adjacent letters in the word is a valid pair.

Farmer John, ever worried that his cows are plotting against him, recently tried to eavesdrop on their conversation. He overheard one word before the cows noticed his presence. The Cow language is spoken so quickly, and its sounds are so strange, that all that Farmer John was able to perceive was the total number of uppercase letters, $U$ ($1 \leq U \leq 250$) and the total number of lowercase letters, $L$ ($1 \leq L \leq 250$) in the word. 

Farmer John knows all $P$ ($1 \leq P \leq 200$) valid ordered pairs of adjacent letters.  He wishes to know how many different valid words are consistent with his limited data.  However, since this number may be very large, he only needs the value modulo $97654321$.

约翰家的奶牛用别人听不懂的“牛语”联络。牛语采用英文字母，而且区分大小写。牛语中的语法中，前后字母的衔接非常重要，存在 $P$ 个基本组合，每个字母之后只能接固定的几个字母。约翰担心奶牛正在密谋反对他，于是最近一直在偷听她们的对话。可是牛语太复杂了，他只模模糊糊地听到了一个单词，并确定了这个单词中有 $U$（$1 \leq U \leq 250$）个大写字母，$L$（$1 \leq L \leq 250$）个小写字母。约翰对这个单词很在意，他想知道，有多少牛语词汇拥有 $U$ 个大写字母，$L$ 个小写字母。由于这个数字太大了，你只要输出答案取 $97654321$ 的余数就可以了。

## 说明/提示

The word Farmer John overheard had 2 uppercase and 2 lowercase letters.  The valid pairs of adjacent letters are AB, ab, BA, ba, Aa, Bb and bB.


The possible words are:

AabB
ABba
abBA
BAab
BbBb
bBAa
bBbB

## 样例 #1

### 输入

```
2 2 7 
AB 
ab 
BA 
ba 
Aa 
Bb 
bB 
```

### 输出

```
7 
```

# 题解

## 作者：tXX_F (赞：3)

#  P3012 [USACO11FEB] Cowlphabet G 

## 题解

可以设 $f_{i,j,k}$ 表示总共有 $i$ 个字符，大写字母有 $j$ 个，末尾字母的为 $k$ 的字串的方案数。

可推出转移式子为：

* 若下一个字母为小写：
$f_{i+1,j,k}\gets f_{i+1,j,k}+f_{i,j,w}$

* 若下一个字母为大写：
$f_{i+1,j+1,k}\gets f_{i+1,j+1,k}+f_{i,j,w}$

为了实际处理方便，可以将大小写字母转换为数字，即 $a\sim z$ 用 $1\sim 26$ 表示，$A\sim Z$ 用 $27\sim 52$ 表示。

最终答案就为：$\sum_{i=1}^{52}f_{U+L,U,i}$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Mod=97654321,Maxn=250+5;;
int U,L,P;
vector<int>Vec_S[57];
int F[Maxn<<1][Maxn][57];
int Answer;
inline int Get(char c){
	return c>='a'&&c<='z'?c-'a'+1:c-'A'+1+26;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>U>>L>>P;
	char s_1,s_2;
	for(register int i=1;i<=P;++i){
		cin>>s_1>>s_2;
		Vec_S[Get(s_1)].push_back(Get(s_2));
	}
	for(register int i=1;i<=26;++i){
		F[1][0][i]=1;
		F[1][1][i+26]=1;
	}
	int len;
	for(register int i=1;i<=U+L;++i)
		for(register int j=0;j<=U;++j)
			for(register int k=1;k<=52;++k){
				len=Vec_S[k].size();
				for(register int p=0;p<len;++p){
					if(Vec_S[k][p]<=26)
						(F[i+1][j][Vec_S[k][p]]+=F[i][j][k])%=Mod;
					else
						(F[i+1][j+1][Vec_S[k][p]]+=F[i][j][k])%=Mod;
				}
			}
	for(register int i=1;i<=52;++i)
		(Answer+=F[U+L][U][i])%=Mod;
	cout<<Answer<<endl;
	return 0;
}
```

---

## 作者：Usada_Pekora (赞：3)

用 $f[i][j][k]$ 表示末尾字母的 ascii 码为 $i$ ，大写字母有 $j$ 个，小写字母有 $k$ 个的字串的方案数。

则：

$ f[t][j+1][k]+=f[i][j][k]$ (下一个字母为大写)。

$ f[t][j][k+1]+=f[i][j][k] $ (下一个字母为小写)。

(其中 $t$ 代表可以接在 $i$ 后面的下一个字母)。

```cpp
#include<cstdio>
#define mod 97654321
int u,l,n,ans=0;
int ch[130][260];
int v[130];
bool vis[130];
int f[130][300][300];
char c[2];
int main(){
	scanf("%d%d%d",&u,&l,&n);
	gets(c);
	for(int i=1;i<=n;i++){
		gets(c);
		char a=c[0],b=c[1];
		ch[a][++ch[a][0]]=b;
		if(!vis[a]) {vis[a]=1;v[++v[0]]=a;}
		if(!vis[b]) {vis[b]=1;v[++v[0]]=b;}
	}
	for(int i=1;i<=v[0];i++) {
		if(v[i]<97) f[v[i]][1][0]=1;
		else f[v[i]][0][1]=1;
	}
	for(int i=0;i<=u;i++)
	    for(int j=0;j<=l;j++)
	        for(int k=1;k<=v[0];k++){
	        	if(f[v[k]][i][j]) 
	        	for(int t=1;t<=ch[v[k]][0];t++){
				    int tmp=ch[v[k]][t];
				    if(tmp<97) f[tmp][i+1][j]=(f[tmp][i+1][j]+f[v[k]][i][j])%mod;
				    else f[tmp][i][j+1]=(f[tmp][i][j+1]+f[v[k]][i][j])%mod;
	            }
			}
	for(int i=1;i<=v[0];i++)  ans=(ans+f[v[i]][u][l])%mod;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：xu222ux (赞：2)

## [P3012 [USACO11FEB] Cowlphabet G](https://www.luogu.com.cn/problem/P3012)

## 思路

这不是妥妥的 DP 吗？

设 $f_{i,j,k}$ 为到 $i$ 为止，有 $j$ 个大写字母，最后一个字母是 $k$。

递推关系为：

如果 $k$ 是大写字母：$f_{i+1,j+1,k}=f_{i,j,w}$。

如果 $k$ 是小写字母：$f_{i+1,j,k}=f_{i,j,w}$。

答案就是 $\sum\limits_{i=a}^{z}f_{U+L,U,i}$。

如果还不明白，详见代码。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=97654321;
int x,y,n;
vector<int>v[56];
int f[502][252][56];
int ctoi(char a){//给字母编号
	if(a>='A'&&a<='Z')return a-'A'+1+26;
	return a-'a'+1;
}
int main(){
	cin>>x>>y>>n;
	for(int i=1;i<=n;i++){
		char a,b;cin>>a>>b;
		v[ctoi(a)].push_back(ctoi(b));
	}
	for(int i=1;i<=26;i++)f[1][0][i]=1;//初始化
	for(int i=27;i<=52;i++)f[1][1][i]=1;//初始化
	for(int i=1;i<x+y;i++){
		for(int j=min(i,x);j>=max(0,i-y);j--){//Big
			for(int w=1;w<=52;w++){
				for(int o=0;o<v[w].size();o++){
					int q=v[w][o];
					if(q<=26){//小写字母
						f[i+1][j][q]+=f[i][j][w];//转移
						f[i+1][j][q]%=mod;
					}else if(j!=x){//大写字母
						f[i+1][j+1][q]+=f[i][j][w];//转移
						f[i+1][j+1][q]%=mod;
					}
				}
			}
		}
	}
	int ans=0;
	for(int i=1;i<=52;i++){
		ans+=f[x+y][x][i];//答案
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：何卓然 (赞：2)

还没有 C++ 题解，这里写一份帮助新手。


这道题看起来好像是一道字符串的问题，然而其实本题大概是采取的动态规划的思想来完成的。

我们看到，每一个字符后面跟着的字符有一些限定，然而，一个字符串（下标 1 -- n）是由


（1 - ( n - 1) ） 的子串来构成的，如果我们确定了一个字符串，那么由这个字符串为前缀，往后

再构成的串就可以通过题目给的规则来进行构造。


我们设计一个状态来表示:

构造一个长度为 i 的串，包含 j 个大写（可以由此推出这个串 i - j 小写字母），最后一个字母是 k，有多少种不同的方案。


我们得到了状态转移方程：

dp[i+1][j+1][l] = dp[i+1][j+1][l] + dp[i][j][k] ( l 是大写，kl 是一个合法的词）

dp[i+1][j][l] = dp[i+1][j][l] + dp[i][j][k] ( l 是小写， kl 是一个合法的词）


我们要求的答案就是 ∑(dp[u+l][u][i)     ( i 是一个英文字母，可以大写可以小写）


记得要边加边模。




Code









    




```cpp
#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MOD 97654321
using namespace std;
vector< vector<int> > edges(300);
int u,l,p,tot = 0;
int dp[551][255][130];
int main()
{
    memset(dp,0,sizeof dp);
    scanf("%d%d%d",&u,&l,&p);
    for (int i=0;i<p;i++)
    {
        char c,h;
        cin >> c >> h;
        edges[int(c)].push_back(int(h));
    }
    for (int i=65;i<=90;i++) dp[1][1][i] = 1; /// 大写
    for (int i=97;i<=122;i++) dp[1][0][i] = 1;
    for (int i=1;i<u+l;i++)
    {
        for (int j=0;j<=i;j++)
        {
            for (int k=65;k<=90;k++)
            {
                for (int d=0;d<edges[k].size();d++)
                {
                    if (edges[k][d] > 90)
                        dp[i+1][j][edges[k][d]] = (dp[i+1][j][edges[k][d]] + dp[i][j][k]) % MOD; // 小写
                    else
                        dp[i+1][j+1][edges[k][d]] = (dp[i+1][j+1][edges[k][d]] + dp[i][j][k]) % MOD;
                }
            }
            for (int k=97;k<=122;k++)
            {
                for (int d=0;d<edges[k].size();d++)
                {
                    if (edges[k][d] > 90)
                        dp[i+1][j][edges[k][d]] = (dp[i+1][j][edges[k][d]] + dp[i][j][k]) % MOD; // 小写
                    else
                        dp[i+1][j+1][edges[k][d]] = (dp[i+1][j+1][edges[k][d]] + dp[i][j][k]) % MOD;
                }
            }
        }
    }
    for (int i=65;i<=90;i++) tot = (tot + dp[u+l][u][i]) % MOD;
    for (int i=97;i<=122;i++) tot = (tot + dp[u+l][u][i]) % MOD;
    printf("%d",tot);
    return 0;
}

```

---

## 作者：_H17_ (赞：1)

## 题目分析

看到这道题中的

>  $A_i$ 后可以接 $B_i$。

直接想到了 DP。

### 状态

那就把出了答案以外的限制信息全当做状态 $f_{i,j,k}$ 表示 $i$ 个大写、$j$ 个小写字母，以 $k$ 结尾时的答案。

### 转移

如果 $b$ 为大写：

则 $f_{i+1,j,b}=\sum f_{i,j,a_k}$

这里的 $a_k$ 指所有可以再 $b$ 前面的字符，小写类似。

### 初始状态

对于所有在 $P$ 对字母中出现的字母 $t$，$f_{1,0,t}=1$（假设大写，小写类似）。

### 答案

对于所有在 $P$ 对字母中出现的字母 $t$，$\sum f_{U,L,t}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=256,mod=97654321;
vector<int>vec[N],v;
bool vis[N];
int f[N][N][N],u,l,p,ans;
char a,b;
int main(){
    cin>>u>>l>>p;
    for(int i=1;i<=p;i++){
        cin>>a>>b;
        vec[a].push_back(b);//所有a后的字母 
        if(!vis[a]){
            vis[a]=1;
            v.push_back(a);
        }
        if(!vis[b]){
            vis[b]=1;
            v.push_back(b);
        }//出现过 
    }
    for(int q:v){
		if('A'<=q&&q<='Z')
            f[q][1][0]=1;
		else
            f[q][0][1]=1;//初始状态 
	}
    for(int i=0;i<=u;i++){
        for(int j=0;j<=l;j++){
            for(int k:v){//出现过就 DP 
                if(!f[k][i][j])
                    continue;
                for(int t:vec[k]){//所有后面的都更新 
                    if('A'<=t&&t<='Z')
                        f[t][i+1][j]=(f[t][i+1][j]+f[k][i][j])%mod;
                    else
                        f[t][i][j+1]=(f[t][i][j+1]+f[k][i][j])%mod;//大小写转移 
                }
            }
        }
    }
    for(int q:v)
        ans=(ans+f[q][u][l])%mod;//答案 
    cout<<ans;
    return 0;
}
```

[双倍经验。](/problem/SP17539)

---

## 作者：whc2020 (赞：1)

题意：求使得字符串中每一个字母后面的字母都能够与其配对，且大写字母有u个、小写字母为l个的字符串个数。

思路：动态规划。

动规的方程：设f[j][i][k]为以字母j为开头，有i个字母，k个大写字母（其实从中已经知道有i - k个小写字母）的字符串。

f[j][i + 1][k + (j <= 26)] = (f[j][i + 1][k + (j <= 26)] + f[o][i][k]) （o和j是匹配的）

优化：

1.使用vector来减少内存的使用。

代码如下：
```cpp
#include<bits/stdc++.h>
#define mod 97654321
using namespace std;

vector < int > vec[53];

int u , l , n , ans;
int f[53][501][251];
string s;
char t1 , t2;

int function (char c) {
	if (c >= 'a' && c <= 'z') {
		return c - 'a' + 1;
	} else {
		return c - 'A' + 27;
	}
}

int main() {
	cin >> u >> l >> n;
	for (int i = 1 ; i <= n ; i++) {
		cin >> t1 >> t2;
		vec[function (t1)].push_back (function (t2));
	}
	for (int i = 1 ; i <= 26 ; i++) {
		f[i][1][0] = 1;
	}
	for (int i = 27 ; i <= 52 ; i++) {
		f[i][1][1] = 1;
	} 
	for (int i = 1 ; i < u + l ; i++) {
		for (int j = 1 ; j <= 26 ; j++) {
			for (int k = 0 ; k <= min (u , i) ; k++) {
				for (int o = 0 ; o < vec[j].size () ; o++) {
					f[j][i + 1][k] = (f[j][i + 1][k] + f[vec[j][o]][i][k]) % mod;
				}
			}
		}
		for (int j = 27 ; j <= 52 ; j++) {
			for (int k = 0 ; k <= min (u , i) ; k++) {
				for (int o = 0 ; o < vec[j].size () ; o++) {
					f[j][i + 1][k + 1] = (f[j][i + 1][k + 1] + f[vec[j][o]][i][k]) % mod;
				}
			}
		}
	}
	for (int j = 1 ; j <= 52 ; j++) {
		ans = (ans + f[j][l + u][u]) % mod;
	}
	printf ("%d" , ans);
	return 0;
}
```


---

## 作者：Anins (赞：0)

## [[USACO11FEB] Cowlphabet G](https://www.luogu.com.cn/problem/P3012)

### 题意

有 $P$ 种拼接方式，问由 $U$ 个大写字母和 $L$ 个小写字母合法组合的方案数。

输出方案数对 $97654321$ 取模的值。

### 思路

动态规划，还没有人写逆推方法，刚好我做的逆推。

设 $f[i][j][z]$ 表示一共有 $i$ 个字母，其中 $j$ 个为小写字母，最后一个字母为 $z$ 的方案数。

那么 $f[i][j][z]$ 的值为长度为 $i-1$ 且最后一个字母能和 $z$ 合法拼接的方案数之和。

设 $la$ 为能在 $z$ 前面和 $z$ 合法组合的字母。

考虑 $z$ 是大写还是小写：

- 若 $z$ 是大写，那么应由所有 $f[i-1][j][la]$ 转移过来。
- 否则应由所有 $f[i-1][j-1][la]$ 转移过来。

最后枚举最后一位是什么字母累加统计答案即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=97654321;
ll U, L, P;
ll f[502][251][54]; //f[i][j][z]表示一共有i个字母，其中有j个小写字母，最后一个字母为z的方案数 
vector <int> can[54];
int get(char c) {
	if(c>='a'&&c<='z') return c-'a'+1;
	return c-'A'+27;
}
int main() {
	cin >> U >> L >> P;
	char c1, c2;
	for(int i=1; i<=P; i++) {
		cin >> c1 >> c2;
		can[get(c2)].push_back(get(c1)); //因为是枚举上一位所以要反向统计 
	}
	for(int i=1; i<=26; i++) f[1][1][i]=1;
	for(int i=27; i<=52; i++) f[1][0][i]=1;
	for(int i=2; i<=U+L; i++) {
		for(int j=0; j<=L; j++) {
			for(int z=1; z<=52; z++) {
				for(int la:can[z]) {
					if(z<=26&&j) f[i][j][z]=(f[i][j][z]+f[i-1][j-1][la])%mod;
					else if(z>26) f[i][j][z]=(f[i][j][z]+f[i-1][j][la])%mod;
				}
			}
		}
	}
	ll ans=0;
	for(int i=1; i<=52; i++) ans=(ans+f[U+L][L][i])%mod;
	cout << ans; 
	return 0;
}
```

---

## 作者：_Day_Tao_ (赞：0)

模拟赛题。

看到题干中这样的形式感觉就很图论，就是前一个字母向后一个字母连边，这样就转化成了图中求有多少条路径满足长度为 $U+L$，并且要经过 $U$ 个大写字母，$L$ 个小写字母。考虑到方案数很大，并且似乎存在转移的性质，所以考虑 DP。设 $f_{i,x,y}$ 表示到了节点 $i$ 有 $x$ 个大写，$y$ 个小写的方案数，$u,v$ 为连边的两点，$[1,26]$ 为大写，$[27,52]$ 为小写。那么转移就是：

$$f_{v,x,y}=f_{v,x,y}+\left\{\begin{array}{rcl} f_{u,x-1,y} & v\in[1,26] \\ f_{u,x,y-1} & v\in [27,52]\end{array}\right.$$

初始化为 $\left\{\begin{array}{rcl} f_{i,1,0}=1 & i\in[1,26] \\ f_{i,0,1}=1 & i\in [27,52]\end{array}\right.$

答案就是 $\sum\limits_{i=1}^{52} f_{i,U,L}$。

最外层枚举转移次数，除初始化共 $U+L-1$ 次。

复杂度为 $O((U+L)^2P)$。代码中优化了一下跑不满。

**Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int,int>
#define ls root << 1
#define rs root << 1 | 1
#define mid ((l + r) >> 1)
const int MAX = 2e5 + 5;
const int mod = 97654321;
const int INF = 0x7fffffff;
inline int read(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
int U,L,p;
vector<char>e[55];
char c1,c2;
int f[55][255][255];
inline int get(char c)
{
	if(c>='A'&&c<='Z') return c-'A'+1;
	return c-'a'+27;
}
signed main()
{
	U=read(),L=read(),p=read();
	for(int i=1;i<=p;++i) cin>>c1>>c2,e[get(c1)].push_back(get(c2)); // 连边 
	for(int i=1;i<=26;i++) f[i][1][0]=1;
	for(int i=27;i<=52;i++) f[i][0][1]=1; // 初始化 
	for(int i=1;i<U+L;i++) for(int u=1;u<=52;u++) for(int v:e[u])
		for(int x=max(0ll,i-L);x<=min(i,U)+1;x++) // 确保每次转移都是有效的，即保证每次的 x<=U,y<=L 
		{
			int y=i-x;
			if(v<=26) f[v][x+1][y]+=f[u][x][y],f[v][x+1][y]%=mod;
			else f[v][x][y+1]+=f[u][x][y],f[v][x][y+1]%=mod;
		}
	int ans=0;
	for(int i=1;i<=52;i++) ans+=f[i][U][L],ans%=mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：lqsy002 (赞：0)

## 题目大意

[题目链接](https://www.luogu.com.cn/problem/P3012)。

## 解题思路

动态规划。

初始化：对于所有在 $P$ 中出现的字母 $t$，$f_{1,0,t}=1$（假设忽略大小写）。

用 $f_{i,j,k}$ 表示使用 $i$ 个大写字母，$j$ 个小写字母，最后一个字母是 $k$ 的情况数。

注意边加边取模。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=97654321;
int u,l,p,ans,x[300],y[300],f[300][300][100];
char s[10];
int get(char ch){
    return ch>='A'&&ch<='Z'?ch-'A':ch-'a'+26;
}
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>u>>l>>p;
    for(int i=1;i<=p;++i){
        cin>>s;
        x[i]=get(s[0]);
        y[i]=get(s[1]);
    }
    for(int i=0;i<26;++i) 
        f[1][0][i]=1;
    for(int i=26;i<52;++i) 
        f[0][1][i]=1;
    for(int i=2;i<=u+l;++i)
        for(int j=0;j<=i&&j<=u;++j)
            for(int k=1;k<=p;++k){
                if(y[k]<26&&j!=0)
                    f[j][i-j][y[k]]=(f[j][i-j][y[k]]+f[j-1][i-j][x[k]])%mod;
                if(y[k]>=26&&i!=j)
                    f[j][i-j][y[k]]=(f[j][i-j][y[k]]+f[j][i-j-1][x[k]])%mod;
            }
    for(int i=0;i<52;++i)
        ans=(ans+f[u][l][i])%mod;
    cout<<ans;
    return 0;
}
```

---

