# Nastya and Scoreboard

## 题目描述

Denis, after buying flowers and sweets (you will learn about this story in the next task), went to a date with Nastya to ask her to become a couple. Now, they are sitting in the cafe and finally... Denis asks her to be together, but ... Nastya doesn't give any answer.

The poor boy was very upset because of that. He was so sad that he punched some kind of scoreboard with numbers. The numbers are displayed in the same way as on an electronic clock: each digit position consists of $ 7 $ segments, which can be turned on or off to display different numbers. The picture shows how all $ 10 $ decimal digits are displayed:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1340B/f1bf3e3ee1e01404b7c2f218b7a8b65c071d6967.png)After the punch, some segments stopped working, that is, some segments might stop glowing if they glowed earlier. But Denis remembered how many sticks were glowing and how many are glowing now. Denis broke exactly $ k $ segments and he knows which sticks are working now. Denis came up with the question: what is the maximum possible number that can appear on the board if you turn on exactly $ k $ sticks (which are off now)?

It is allowed that the number includes leading zeros.

## 说明/提示

In the first test, we are obliged to include all $ 7 $ sticks and get one $ 8 $ digit on the scoreboard.

In the second test, we have sticks turned on so that units are formed. For $ 5 $ of additionally included sticks, you can get the numbers $ 07 $ , $ 18 $ , $ 34 $ , $ 43 $ , $ 70 $ , $ 79 $ , $ 81 $ and $ 97 $ , of which we choose the maximum — $ 97 $ .

In the third test, it is impossible to turn on exactly $ 5 $ sticks so that a sequence of numbers appears on the scoreboard.

## 样例 #1

### 输入

```
1 7
0000000```

### 输出

```
8```

## 样例 #2

### 输入

```
2 5
0010010
0010010```

### 输出

```
97```

## 样例 #3

### 输入

```
3 5
0100001
1001001
1010011```

### 输出

```
-1```

# 题解

## 作者：juicyyou (赞：5)

# CF1340B Nastya and Scoreboard
## 解法：
直接 贪心 + DP 即可。

我们令 $dp_{i, j}$ 为从 第 $i$ 个数到第 $n$ 个数，仅打开 $j$ 个荧光棒所能在第 $i$ 上得到的合法数字。(注意，如果是-1，则代表不可能)。那么可以直接写出方程：
$$dp_{i, j} = \max\{s\}\,\, (dp_{i + 1, s} > -1\,\,\land\,\,0 \le s \le 9)$$

最后直接用 $dp_{1, k}$ 一路在一路推回去即可。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#include<set>
#include<cstdlib>
#include<cctype>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 1e5 + 5;
const ll maxm = 2e3 + 5;
template<class T>
inline T qread(T &IEE){
	register T x = 0, f = 1;
	register char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -f;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return IEE = x * f;
}
template<class T>
inline void qwrite(T a){
	if(!a){
		putchar('0');
		return ;
	}
 	if(a < 0){
		putchar('-');
		a = -a;
	}
	if(a > 9) qwrite(a / 10);
	putchar(a % 10 + 48);
	return ;
}
template<class T>
inline T ab(T a){
	return (a > 0) ? a : -a;
}
template<class T>
inline void swa(T &a, T &b){
	a ^= b ^= a ^= b;
	return ;
}
int n, k;
int dp[maxm][maxm];
string s[maxn];
string num[10] = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};
int cal(string s, int c){ // 计算需要打开的数量
	int cnt = 0;
	for(int i = 0;i < 7;i++){
		if(s[i] == '1' && num[c][i] == '0'){
			return -1;
		}
		if(s[i] != num[c][i]){
			cnt++;
		}
	}
	return cnt;
}
int main(){
	qread(n);
	qread(k);
	memset(dp, -1, sizeof(dp));
	for(int i = 1;i <= n;i++){
		cin >> s[i];
	}
	for(int i = n;i >= 1;i--){
		if(i == n){
			for(int j = 0;j < 10;j++){
				int op = cal(s[i], j);
				if(op == -1){
					continue;
				}
				dp[n][op] = max(dp[n][op], j);
			}
		} else {
			for(int j = 0;j < 10;j++){
				int op = cal(s[i], j);
				if(op == -1){
					continue;
				}
				for(int l = op;l <= k;l++){
					if(dp[i + 1][l - op] != -1){
						dp[i][l] = j;
					}
				}
			}
		}
	}
	if(dp[1][k] == -1){
		puts("-1");
	} else {
		int now = k;
		bool f = 0;
		for(int i = 1;i <= n;i++){
			cout << dp[i][now];
			now -= cal(s[i], dp[i][now]);
		}
		puts("");
	}
	return 0;
}
```

上述算法的单次复杂度即为 $\mathcal O(nk)$ ， 可以通过此题。

---

## 作者：ZigZagKmp (赞：2)

本文同步发表于我的[cnblog](https://www.cnblogs.com/ZigZagKmp/p/13749280.html)

本场题解见[此](https://www.luogu.com.cn/blog/ZigZagKmp/codeforces-1340-solution)
## CF1340B
### 题意简述
有 $n$ 个如下图所示的灯组原件，构成了一个计分板。每个灯组原件由 $7$ 个灯管组成，编号如下图所示。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1340B/6c9f45d01bcb06cb8414bdec7143d32cc386df85.png)

现在这 $n$ 个灯组原件中，有一些灯管保持常亮，求再点亮恰好 $k$ 个灯管，能够组成的最大的数是多少。

答案允许有前导零。

$1\le n\le 2000,0\le k\le 2000$。
### 算法标签
贪心 dp
### 算法分析
首先考虑直接从前向后贪心，尽可能选较大的数。

这时我们发现一个问题：这样的贪心可能最后无解。

> 无解？那就不让它无解！

考虑反向dp判断可行性，$dp(i,j)$表示 $i$ 到 $n$ 的灯组再点亮 $j$ 个是否能构成数字。

这是一个比较经典的背包可行性问题，可以以 $O(nk)$ 的时间复杂度求出答案。

这样我们在从前向后的贪心过程中在保证有解的同时让数字尽可能大即可。

总时间复杂度 $O(nk)$ 。
### 代码实现
可以把输入转化为二进制处理较为方便。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 2005
#define maxm 2000005
#define inf 0x3f3f3f3f
#define LL long long
#define mod 1000000007
#define local
void file(string s){freopen((s+".in").c_str(),"r",stdin);freopen((s+".out").c_str(),"w",stdout);}
template <typename Tp>void read(Tp &x){
	x=0;int fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-'){fh=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=fh;
}
int n,m;
int a[maxn];
int nm[]={119,18,93,91,58,107,111,82,127,123};
int cst[maxn][10];
int siz[200];
int dp[maxn][maxn];
signed main(){
	read(n);read(m);
	for(int i=1;i<=127;++i)siz[i]=siz[i-(i&(-i))]+1;
	for(int i=1,x;i<=n;++i){
		for(int j=6;~j;--j){
			scanf("%1d",&x);
			if(x)a[i]|=(1<<j);
		}
		for(int j=0;j<10;++j){
			if((a[i]&nm[j])==a[i]){
				cst[i][j]=siz[nm[j]^a[i]];
			}
			else{
				cst[i][j]=-1;
			}
		}
	}
        //可行性dp
	dp[n+1][0]=1;
	for(int i=n;i;--i){
		for(int j=0;j<=m;++j){
			for(int k=0;k<10;++k){
				if(~cst[i][k]){
					if(j>=cst[i][k])dp[i][j]|=dp[i+1][j-cst[i][k]];
				}
			}
		}
	}
        //贪心
	for(int i=1;i<=n;++i){
		int fl=-1;
		for(int k=9;~k;--k){
			if(cst[i][k]==-1)continue;
			if(dp[i+1][m-cst[i][k]]){
				fl=k;break;
			}
		}
		if(fl==-1){
			puts("-1");
			return 0;
		}
		printf("%d",fl);
		m-=cst[i][fl];
	}
	return 0;
}
```

---

## 作者：Fairicle (赞：1)

挂一下[博客链接](https://www.luogu.com.cn/blog/Fairicle/solution-cf1340b)

对于每一位数字单独考虑，可以预处理出题目给定的 01 串能够转化成的数字，那就是一个典型的背包。

重量 $w$ 为需要点亮的数目，价值 $v$ 就是转变成的数字（但是这里需要考虑位数）。我们对每个位置开 vector 记录能转化的数字及需要点亮的数目，用一个 pair 存储。

这题存在无解情况，所以我们需要判断可行性。

设 $f_{i,j}$ 表示在目前处理到第 $i$ 位，总共点亮了 $j$ 次的可行性（1 代表可以，0 代表不行）

初始化 $f_{n+1,0}=1$

转移方程 $f_{i,j} = f_{i,j}\ | \ f_{i+1,j-w}$

如果最后 $f_{1,k}=1$ 代表可行，接下来计算答案，如果等于 0，就直接输出 -1。

计算答案我们可以考虑贪心的做，从高位向低位进行选择，对于每一位从 9 到 0 进行选择。则选择第一个可行的数必定能使答案最大。

假设在选择第 $i$ 位，剩余可用的点亮次数为 $res$，这个数需要点亮 $w$ 个，则可以选择的条件为 $f_{i+1,res-w}=1$ 。

具体见代码，里面有解释：
```cpp
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ul unsigned long long
#define ui unsigned int
#define ri register int
#define pb push_back
string p[15]={"1110111","0010010","1011101","1011011","0111010","1101011","1101111","1010010","1111111","1111011"};
inline int rd(){
	int x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
#define N 2010
int n,k,f[N][N];
char ch[N];
typedef pair<int,int>pp;
vector<pp>a[N];
int main()
{
	ios::sync_with_stdio(false);
	n=rd(),k=rd();
	for(ri i=1;i<=n;++i){
		scanf("%s",ch);
		for(ri j=9;j>=0;--j){
			int cnt=0,flg=0;
			for(ri k=0;k<7;++k){
				if(ch[k]==p[j][k]) continue;
				if(ch[k]=='1'){
					flg=1;
					break;
				}
				cnt++;
			}
			if(flg) continue;
			a[i].pb(make_pair(cnt,j));
		}
	}//预处理
	f[n+1][0]=1;
	for(ri i=n;i>=1;--i){
		for(ri l=0;l<a[i].size();++l){
		    for(int j=a[i][l].first;j<=k;j++){
				int w=a[i][l].first;
				f[i][j]|=f[i+1][j-w];
			}
		}
	}//合法性判断
	if(!f[1][k]){
		cout<<-1;
		return 0;
	}
	string ans="";
	int cnt=k;
	for(ri i=1;i<=n;++i){
		for(ri j=0;j<a[i].size();++j){
			int w=a[i][j].first;
			if(cnt<w) continue;
			if(f[i+1][cnt-w]){
				char ch=a[i][j].second+'0';
				ans=ans+ch;
				cnt-=w;
				break;
			}
		}
	}//答案计算
	cout<<ans;
    return 0;
}
```


---

## 作者：YNH_QAQ (赞：0)

# CF1340B Nastya and Scoreboard 题解
## 题目大意
（具体见题目翻译）

一个灯组原件，$7$ 条线：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1340B/6c9f45d01bcb06cb8414bdec7143d32cc386df85.png)

目标：$n$ 个灯组原件，有若干个一直亮着，求出再点亮 $k$ 个灯管能组成的最大数字。

### 输入
第一行 $n$ 和 $k$，后面 $n$ 行是按照上图顺序的 $7$ 个数字，可能是：
- $0$（不常亮）
- $1$（常亮）

### 输出
求出再点亮 $k$ 个灯管能组成的最大数字。

## 分析
算法：贪心+动态规划。

### dp
状态：二维布尔动态规划，$dp_{i,j}$ 表示从 $i$ 到 $n$，只打开 $j$ 个位置的灯能否构成数字

答案：利用贪心，按照高低位倒着选择（$9$ 到 $0$），选择第一个可行的，答案一定最大，前提是 $dp_{1,k}$ 为真，否则直接 $-1$。

转移：不难写出类似背包的转移。

$$dp_{i,j}=dp_{i,j} \mid dp_{i+1,j-w}$$

初始状态：$dp_{n+1,0}$ 全部赋值为 $1$。

时间复杂度：$O(nk)$。

## 核心代码
```cpp
dp[n+1][0]=true;
for(int i=n;i>=1;i--)
  	for(int j=0;j<=k;j++)
      		for(int k=0;k<=9;k++){ //遍历高低位
  
              int w =  op[i][k];
              if(~w && j>=w)
                      		dp[i][j]=dp[i][j]|dp[i+1][j-w];
            }
//求解
for(int i=1;i<=n;++i){
		int tmp=-1;
		for(int j=9;j>=0;j--){
			if(op[i][j]==-1)continue;
			if(dp[i+1][k-op[i][j]]){
				tmp=j;
              break;
			}
		}
		if(tmp==-1){
			cout<<-1;
			return 0;
		}
  cout<<tmp<<endl;
  	k-=op[i][tmp];
	}
```

---

