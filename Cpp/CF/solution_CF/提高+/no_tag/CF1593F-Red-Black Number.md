# Red-Black Number

## 题目描述

It is given a non-negative integer $ x $ , the decimal representation of which contains $ n $ digits. You need to color each its digit in red or black, so that the number formed by the red digits is divisible by $ A $ , and the number formed by the black digits is divisible by $ B $ .

At least one digit must be colored in each of two colors. Consider, the count of digits colored in red is $ r $ and the count of digits colored in black is $ b $ . Among all possible colorings of the given number $ x $ , you need to output any such that the value of $ |r - b| $ is the minimum possible.

Note that the number $ x $ and the numbers formed by digits of each color, may contain leading zeros.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1593F/773fc1d6da54f8f63fa04e827efd3f32cdfb91c7.png)Example of painting a number for $ A = 3 $ and $ B = 13 $ The figure above shows an example of painting the number $ x = 02165 $ of $ n = 5 $ digits for $ A = 3 $ and $ B = 13 $ . The red digits form the number $ 015 $ , which is divisible by $ 3 $ , and the black ones — $ 26 $ , which is divisible by $ 13 $ . Note that the absolute value of the difference between the counts of red and black digits is $ 1 $ , it is impossible to achieve a smaller value.

## 说明/提示

The first test case is considered in the statement.

In the second test case, there are no even digits, so it is impossible to form a number from its digits that is divisible by $ 2 $ .

In the third test case, each coloring containing at least one red and one black digit is possible, so you can color $ 4 $ digits in red and $ 4 $ in black ( $ |4 - 4| = 0 $ , it is impossible to improve the result).

In the fourth test case, there is a single desired coloring.

## 样例 #1

### 输入

```
4
5 3 13
02165
4 2 1
1357
8 1 1
12345678
2 7 9
90```

### 输出

```
RBRBR
-1
BBRRRRBB
BR```

# 题解

## 作者：Ryo_Yamada (赞：6)

> 有 $n$ 个数字，你需要将它们每一个都染上红色或黑色（至少要有一个数是红色，黑色同理），使红色的数字从左到右组成的数可以被 $a$ 整除，且黑色的数字从左到右组成的数可以被 $b$ 整除，同时设红色的数字个数为 $A$，黑色的数字个数为 $B$，你需要最小化 $|A-B|$，输出方案或 $-1$ 表示无解。


### 做法 $1$.

场上看到 $n=40$ 就想到折半搜索。实际上又长又难写。

将整个数组分为两半搜索，$v_{0/1,i,j,k}$ 表示数组前一半/后一半，红色组成的数 $\mod a = i$，黑色组成的数 $\mod b = j$，且有 $k$ 个数字被染成红色的方案。

求答案可以枚举前一半 $\mod a$ 和 $\mod b$ 的结果，以及前一半和后一半染成红色的个数。这样可以计算得出后一半 $\mod a$ 和 $\mod b$ 的结果，直接计算答案即可。

时间复杂度 $O(2^{\frac{n}2} + n^2ab)$，直接喜提（目前）最劣解。

$\text{Code}$：

```cpp
int n, a, b;
int x[N];
vector<int> v[2][N][N][N];
int col[N];

void dfs(int f, int st, int ed, int A, int B, int ca) {
	if(st > ed) {
		if(v[f][A][B][ca].size()) return ; 
		if(ed == n) rep(i, n / 2 + 1, n) v[f][A][B][ca].pb(col[i]);
		else rep(i, 1, n / 2) v[f][A][B][ca].pb(col[i]);
		return ;
	}
	col[st] = 1;
	dfs(f, st + 1, ed, (A * 10 + x[st]) % a, B, ca + 1); 
	col[st] = 2;
	dfs(f, st + 1, ed, A, (B * 10 + x[st]) % b, ca); 
	col[st] = 0;
}

int main() {
	int t; cin >> t;
	W(t) {
		cin >> n >> a >> b;
		rep(i, 0, a - 1) rep(j, 0, b - 1) rep(k, 0, 1) rep(l, 0, n) v[k][i][j][l].clear();
		rep(i, 1, n) scanf("%1d", x + i);
		dfs(0, 1, n / 2, 0, 0, 0);
		dfs(1, n / 2 + 1, n, 0, 0, 0);
		int mn = 0x3f3f3f3f, l = n / 2, lst = n - (n / 2);
		rep(i, 0, a - 1) rep(j, 0, b - 1) rep(cca, 0, l) {
			if(!v[0][i][j][cca].size()) continue;
			rep(ca, 0, lst) {
				if(ca + cca == 0 || ca + cca == n) continue;
				int nwa = qpow(ca, 10, a) * i % a, nwb = qpow(lst - ca, 10, b) * j % b;
				int nda = (a - nwa) % a, ndb = (b - nwb) % b;
				if(!v[1][nda][ndb][ca].size()) continue;
				To_min(mn, abs((n - cca - ca) - ca - cca));
			}
		}
//		cout << mn << ' ' << v[0][0][0][0].size() << ' ' << v[1][0][0][1].size() << endl;
		rep(i, 0, a - 1) rep(j, 0, b - 1) rep(cca, 0, l) {
			if(!v[0][i][j][cca].size()) continue;
			rep(ca, 0, lst) {
				if(ca + cca == 0 || ca + cca == n) continue;
				int nwa = qpow(ca, 10, a) * i % a, nwb = qpow(lst -  ca, 10, b) * j % b;
				int nda = (a - nwa) % a, ndb = (b - nwb) % b;
//				if(!i && !j && !cca && ca == 1) cout << nda << ' ' << ndb << endl;
				if(!v[1][nda][ndb][ca].size()) continue;
				if(abs((n - cca - ca) - ca - cca) == mn) {
					for(int co : v[0][i][j][cca]) if(co == 1) pc('R'); else pc('B');
					for(int co : v[1][nda][ndb][ca]) if(co == 1) pc('R'); else pc('B');
					pc('\n');
					goto End;
				}
			}
		}
		puts("-1");
		End:;
	}
	return 0;
}
```

### 做法 $2$.

折半写挂还吃了两发罚时，场后一拍脑子，实际上状态只有四维，$vis_{i,j,k,l} = 0/1$ 表示当前到第 $i$ 个数字，染成红色的组成的数 $\mod a = j$，染成黑色的组成的数 $\mod b = k$，染了 $l$ 个红色的数字是否被搜到了。

于是直接 dfs 即可。

时间复杂度 $O(n^2ab)$，跑的飞快。

$\text{Code}$：

```cpp
int n, a, b;
int x[N];
int t[N], col[N];
bool vis[N][N][N][N];
int mn;
 
void dfs(int st, int A, int B, int ca) {
	if(vis[st][A][B][ca]) return ;
	vis[st][A][B][ca] = 1;
	if(st > n) {
		if(!A && !B && abs(n - 2 * ca) < mn) {
			mn = abs(n - 2 * ca);
			rep(i, 1, n) col[i] = t[i];
		}
		return ;
	}
	t[st] = 1;
	dfs(st + 1, (A * 10 + x[st]) % a, B, ca + 1);
	t[st] = 2;
	dfs(st + 1, A, (B * 10 + x[st]) % b, ca);
	t[st] = 0;
}
 
int main() {
	int t; cin >> t;
	W(t) {
		memset(vis, 0, sizeof vis);
		cin >> n >> a >> b;
		mn = n;
		rep(i, 1, n) scanf("%1d", x + i);
		dfs(1, 0, 0, 0);
		if(mn == n) puts("-1");
		else {
			rep(i, 1, n) if(col[i] == 1) pc('R'); else pc('B');
			pc('\n'); 
		}
	}
	return 0;
}
```


---

## 作者：尹昱钦 (赞：4)

## 题意：

给一个序列，将其每一位染成红色或者黑色。

要求红色组成的数字是 A 的倍数，黑色组成的数字是 B 的倍数。

输出满足上述要求时红黑两色数量差最小的染色方案。

## 思路：

首先可以发现，过程中我们**不需要知道当前数字是多少，只要知道当前两个数字的位数和除以 $A/B$ 余数分别是多少**。

所以我们设 $dp[i][j][a][b]$ 表示前 $i$ 位染 $j$ 个黑色，红/黑色组成的数字模 $A/B$ 时的余数分别为 $a/b$ 的方案是否存在。

然后再用 $black[i][j][a][b]$ 和 $red[i][j][a][b]$ 记录一下路径（记录从哪个状态转移过来），最后倒序找路径、正序输出路径即可。

## AC代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string s;
int T,n,A,B,dp[45][45][45][45],black[45][45][45][45],red[45][45][45][45];
inline void print_ans(int ans){//倒序找路径并正序输出
	int anss[50],a=0,b=0;
	for(int i=n;i>=1;i--){
		if(black[i][ans][a][b]!=-1){
			anss[i]=0;
			b=black[i][ans][a][b];
			ans--;
		}else{
			anss[i]=1;
			a=red[i][ans][a][b];
		}
	}
	for(int i=1;i<=n;i++){
		putchar(anss[i]?'R':'B');
	}
	puts("");
}
int main(){
	cin>>T;
	while(T--){
		memset(dp,0,sizeof(dp));
		memset(black,-1,sizeof(black));
		memset(red,-1,sizeof(red));
		cin>>n>>A>>B;
		cin>>s;
		dp[0][0][0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=i;j++){
				for(int a=0;a<A;a++){
					for(int b=0;b<B;b++){
						if(dp[i-1][j][a][b]){//转移并记录路径
							dp[i][j+1][a][(b*10+s[i-1]-'0')%B]=1;
							black[i][j+1][a][(b*10+s[i-1]-'0')%B]=b;
							dp[i][j][(a*10+s[i-1]-'0')%A][b]=1;
							red[i][j][(a*10+s[i-1]-'0')%A][b]=a;
						}
					}
				}
			}
		}
		int ans=50;
		for(int i=1;i<n;i++){
			if(dp[n][i][0][0]){
				if(abs(n-i-i)<abs(n-ans-ans)) ans=i;
			}
		}
		if(ans==50) cout<<-1<<endl;
		else print_ans(ans);
	}
	return 0;
}
```

---

## 作者：CYZZ (赞：1)

# [Red-Black Number](https://www.luogu.com.cn/problem/CF1593F)
## 思路
考虑 dp，设状态 $dp_{i,j,p,q}=0/1$ 为是否存在前 $i$ 个数中，选 $j$ 个红，选 $i-j$ 个黑，红、黑组成的数模 $A/B$ 分别为 $p/q$ 时的选法。

因为当前第 $i$ 个数只能分配到红或者黑，所以分别有两条状态转移方程：若 $dp_{i,j,p,q}=1$，有：

$$dp_{i+1,j,p,q\times 10+a_i}=dp_{i+1,j+1,p\times 10+a_i,q}=1$$

因为 dp 在最后获取答案时需要倒序寻找路径，所以我们不妨把 dp 换成 dfs，这样就可以在相同的复杂度内省去寻找路径这一步（在搜索的时候记录）。

dfs 实现和 dp 大体相同，只是把数组下标换成函数参数罢了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,A,B,maxlen;
bool bk[45][45][45][45];
char ans[45],pat[45],s[45];
void dfs(int dep,int a,int b,int cnt)
{
    bk[dep][a][b][cnt]=1;
    if(dep>n)
    {
        if(a||b||abs(n-cnt-cnt)>=maxlen)
            return ;
        maxlen=abs(n-cnt-cnt);//更新最优答案
        for(int i=1;i<=n;i++)
        {
            ans[i]=pat[i];//更新答案
        }
        return ;
    }
    if(!bk[dep+1][(a*10+s[dep]-'0')%A][b][cnt+1])
    {
        pat[dep]='R';//记录路径
        dfs(dep+1,(a*10+s[dep]-'0')%A,b,cnt+1);//转移
    }
    if(!bk[dep+1][a][(b*10+s[dep]-'0')%B][cnt])
    {
        pat[dep]='B';
        dfs(dep+1,a,(b*10+s[dep]-'0')%B,cnt);
    }
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        memset(bk,0,sizeof bk);//记得清空
        scanf("%d%d%d",&n,&A,&B);
        for(int i=1;i<=n;i++)
        {
            cin >> s[i];
        }
        maxlen=n;
        dfs(1,0,0,0);
        if(maxlen==n)
            printf("-1\n");//无法到达
        else
        {
            for(int i=1;i<=n;i++)
            {
                putchar(ans[i]);
            }
            putchar('\n');
        }
    }
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：__LZH__ (赞：0)

# CF1593F Red-Black Number

## 题意

[题面传送门](https://www.luogu.com.cn/problem/CF1593F)。

## 思路

一道很好的搜索题。

状态：$(x, y, u, v)$ 表示 $x$ 个红色、$y$ 个蓝色、红色组成的数字 $p \equiv u \pmod a$、蓝色组成的数字 $q \equiv v \pmod b$。

转移：$(x, y, u, v) \to (x + 1, y, (u + p) \bmod a, v), (x, y + 1, u, (v + p) \bmod b)$，其中 $p$ 为当前数字。

由于 $n, m, a, b$ 较小，故搜索即可通过。

## 时空复杂度

时间：$O(n ^ 2 ab)$。

空间：$O(n ^ 2 ab)$。

## 代码：

```cpp
#include<bits/stdc++.h>

#define int long long

using namespace std;

int T, n, a, b, vis[45][45][45][45], op;
string s, t, ans;

void dfs(int c1, int c2, int u, int v){
  if(vis[c1][c2][u][v]){
    return ;
  }
  if(c1 + c2 == n){
    if(u == 0 && v == 0 && c1 > 0 && c2 > 0 && op > abs(c1 - c2)){
      ans = t, op = abs(c1 - c2);
    }
    return ;
  }
  vis[c1][c2][u][v] = 1;
  t[c1 + c2] = 'R', dfs(c1 + 1, c2, (u * 10 + s[c1 + c2] - '0') % a, v);
  t[c1 + c2] = 'B', dfs(c1, c2 + 1, u, (v * 10 + s[c1 + c2] - '0') % b);
}

void solve(){
  for(int i = 0; i <= n; i++){
    for(int j = 0; j <= n; j++){
      for(int k = 0; k < a; k++){
        for(int l = 0; l < b; l++){
          vis[i][j][k][l] = 0;
        }
      }
    }
  }
  cin >> n >> a >> b >> s;
  ans = "-1", op = 1e9, t = s;
  dfs(0, 0, 0, 0);
  cout << ans << '\n';
}

signed main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--){
    solve();
  }
  return 0;
}

```

---

## 作者：Resolute_Faith (赞：0)

一道思维难度很低的题目。

我们不妨先设 $dp_{i,j,k,l}$ 表示我们处理到第 $i$ 位，红色的余数为 $j$，黑色的余数为 $k$，且我们已经选择了 $l$ 个红色的方案是否存在（本来是想记 $l$ 为个数差的，但我可能有点蠢）。

状态转移方程十分简单，直接考虑第 $i$ 为是红色还是黑色即可。但是考虑到我们要输出方案，则额外再开一点数组记录每一个转移的决策即可。输出时我们显然要按照 $l$ 进行选择，但是 $l$ 最小并不代表差值最小，我们考虑解一个二元一次方程：

$$
\begin{cases}
x+y=n\\
x-y=i
\end{cases}
$$

其中 $i$ 是我们枚举的差值，这个差值是 $-n$ 到 $n-2$ 中以 $2$ 为公差的数（稍微想一想就知道了）。其中 $x,y$ 分别是一个差值对应的红色个数取值。

时间复杂度 $\mathcal{O}(Tn^2ab)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=42;
inline int read(){
	char op=getchar();
	int w=0,s=1;
	while(op<'0'||op>'9'){
		if(op=='-') s=-1;
		op=getchar();
	}
	while(op>='0'&&op<='9'){
		w=(w<<1)+(w<<3)+op-'0';
		op=getchar();
	}
	return w*s;
}
int a[N],dp[N][N][N][N],y[N][N][N][N];
char x[N][N][N][N];
signed main(){
	int T=read();
	while(T--){
		int n=read(),A=read(),B=read();
		for(register int i=1;i<=n;i++){
			char op=getchar();
			while(op<'0'||op>'9') op=getchar();
			a[i]=op-'0';
		}
		dp[1][a[1]%A][0][1]=1;
		dp[1][0][a[1]%B][0]=1;
		x[1][a[1]%A][0][1]='R';
		x[1][0][a[1]%B][0]='B';
		for(register int i=2;i<=n;i++){
			for(register int j=0;j<A;j++){
				for(register int k=0;k<B;k++){
					for(register int l=0;l<i;l++){
						dp[i][(j*10+a[i])%A][k][l+1]|=dp[i-1][j][k][l];
						dp[i][j][(k*10+a[i])%B][l]|=dp[i-1][j][k][l];
						if(dp[i-1][j][k][l]){
							x[i][(j*10+a[i])%A][k][l+1]='R';
							y[i][(j*10+a[i])%A][k][l+1]=j;
							x[i][j][(k*10+a[i])%B][l]='B';
							y[i][j][(k*10+a[i])%B][l]=k;
						}
					}
				}
			}
		}
		bool op=false;
		char s[45];
		for(register int i=0;i<=44;i++) s[i]=0;
		for(register int i=(n%2);i<=n-2;i+=2){
			if(dp[n][0][0][(n+i)/2]==1){//red most
				int now=n,p=0,q=0,r=(n+i)/2;
				s[n+1]=0;
				while(now!=0){
					s[now]=x[now][p][q][r];
					if(s[now]=='R') p=y[now][p][q][r],r--;
					else q=y[now][p][q][r];
					now--;
				}
				printf("%s\n",s+1);
				op=true;
				break;
			}
			if(dp[n][0][0][(n-i)/2]==1){
				int now=n,p=0,q=0,r=(n-i)/2;
				s[n+1]=0;
				while(now!=0){
					s[now]=x[now][p][q][r];
					if(s[now]=='R') p=y[now][p][q][r],r--;
					else q=y[now][p][q][r];
					now--;
				}
				printf("%s\n",s+1);
				op=true;
				break;
			}
		}
		if(!op) printf("-1\n");
		memset(dp,0,sizeof(dp));
		memset(x,0,sizeof(x));
		memset(y,0,sizeof(y));
	}
}
/*
4
5 3 13
02165
4 2 1
1357
8 1 1
12345678
2 7 9
90
*/
```

---

