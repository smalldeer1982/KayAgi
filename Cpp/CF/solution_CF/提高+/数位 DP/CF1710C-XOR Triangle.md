# XOR Triangle

## 题目描述

给你一个数 $n$，问：有多少对数 $0\leq a,b,c \leq n$ 满足 $a \oplus b,b \oplus c,a \oplus c$  。三个数字构成了一个非退化三角形，也就是两条短边之和大于第三边的长度。$\oplus$ 表示二进制下的异或操作。

## 说明/提示

$0 < n < 2^{200000}$。

## 样例 #1

### 输入

```
101```

### 输出

```
12```

## 样例 #2

### 输入

```
1110```

### 输出

```
780```

## 样例 #3

### 输入

```
11011111101010010```

### 输出

```
141427753```

# 题解

## 作者：y0y68 (赞：21)

数位DP入门题，给一种写起来很简洁的做法。

对于三个数 $x,y,z$ ，除了大小限制外，剩余的限制只有 $x⊕y+x⊕z>y⊕z$，$y⊕x+y⊕z>x⊕z$，$z⊕x+z⊕y>x⊕y$。

这三个式子是轮换的，先考虑第二个式子。

设 $x,y,z$ 在某个二进制位上分别是 $a,b,c$，那个只有 $2^3=8$ 种 $a,b,c$ 的组合，我们将 $a,b,c,b⊕a,b⊕c,a⊕c$ 的表给打出来：

| $a$ | $b$ | $c$ | $b⊕a$ | $b⊕c$ | $a⊕c$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $0$ | $0$ | $0$ | $0$ | $0$ | $0$ |
| $0$ | $0$ | $1$ | $0$ | $1$ | $1$ |
| $0$ | $1$ | $0$ | $1$ | $1$ | $0$ |
| $0$ | $1$ | $1$ | $1$ | $0$ | $1$ |
| $1$ | $0$ | $0$ | $1$ | $0$ | $1$ |
| $1$ | $0$ | $1$ | $1$ | $1$ | $0$ |
| $1$ | $1$ | $0$ | $0$ | $1$ | $1$ |
| $1$ | $1$ | $1$ | $0$ | $0$ | $0$ |


我们发现 **$b⊕a+b⊕c$ 总是不小于 $a⊕c$**，那么对于所有数位，只需存在一位是 $b⊕a+b⊕c>a⊕c$ 的情况（当且仅当 $a=0,b=1,c=0$ 或 $a=1,b=0,c=1$），那么我们就能保证 $y⊕x+y⊕z>x⊕z$，对于另外两个限制将这个结论给轮换一下即可。

所以我们可以在 DP 中多记三个量，分别表示目前能否保证$x⊕y+x⊕z>y⊕z$，$y⊕x+y⊕z>x⊕z$，$z⊕x+z⊕y>x⊕y$。

然后就写完了，时间复杂度 $O(2^9n)$，十分合理：

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
const int mod=998244353;
char a[N];
int n,dp[N][2][2][2][2][2][2];
inline int dfs(int k,bool l1,bool l2,bool l3,bool _x,bool _y,bool _z){
	if(k>n)return _x&&_y&&_z;
	if(dp[k][l1][l2][l3][_x][_y][_z]!=-1)return dp[k][l1][l2][l3][_x][_y][_z];
	int res=0;
	for(int x=0;x<=(l1?a[k]-'0':1);x++)for(int y=0;y<=(l2?a[k]-'0':1);y++)for(int z=0;z<=(l3?a[k]-'0':1);z++)
		res=(res+dfs(k+1,l1&(x==a[k]-'0'),l2&(y==a[k]-'0'),l3&(z==a[k]-'0'),_x|(x==0&&y==1&&z==1)|(x==1&&y==0&&z==0),_y|(y==0&&x==1&&z==1)|(y==1&&x==0&&z==0),_z|(z==0&&x==1&&y==1)|(z==1&&x==0&&y==0)))%mod;
	return dp[k][l1][l2][l3][_x][_y][_z]=res;
}
int main(){
	scanf("%s",a+1);
	n=strlen(a+1);
	memset(dp,-1,sizeof dp);
	printf("%d\n",dfs(1,1,1,1,0,0,0));
	return 0;
}
```

---

## 作者：Little09 (赞：8)

我们令 $x=a\ \text{xor}\ b$，$y=b\ \text{xor}\ c$，$z=c\ \text{xor}\ a$。容易发现 $x,y,z$ 满足 $x\ \text{xor}\ y\ \text{xor}\ z=0$。我们考虑他们什么时候可以构成三角形。结论是：当且仅当存在其中两个数 $x,y$ 满足 $x\ \text{and}\ y=0$，不满足构成三角形。下面简单说明一下。

- 充分：当 $x\ \text{and}\ y=0$ 时，$x$ 与 $y$ 不会同时有一位是 $1$。所以 $x\ \text{xor}\ y=x+y=z$，因此不满足。
- 必要：任意两个数的与都不等于 $0$，我们不妨三个数大小顺序 $x>y>z$。由于 $y\ \text{and}\ z>0$，那么 $y,z$ 至少有一位同时是 $1$，所以 $x=y\ \text{xor}\ z<y+z$。也就满足构成三角形。

于是我们考虑数位 DP。从高位到低位做，记三个变量表示当前 $a,b,c$ 是否满足已填的位都与 $n$ 相同的限制，再记三个变量分别表示 $x\ \text{and}\ y$，$y\ \text{and}\ z$，$z\ \text{and}\ x$ 是否仍为 $0$。转移是平凡的，枚举 $a,b,c$ 这一位填了什么，更新上述六个变量即可。

这样做的复杂度是 $O(2^9n)$。

```cpp
const int N=200005;
int n,m; 
char s[N];
ll dp[N][2][2][2][2][2][2];

ll dfs(int u,bool a,bool b,bool c,bool x,bool y,bool z)
{
	if (u==n+1)
	{
		if (x&&y&&z) return 1;
		return 0;
	}
	if (dp[u][a][b][c][x][y][z]!=-1) return dp[u][a][b][c][x][y][z];
	ll res=0;
	for (int i=0;i<=1;i++)
	{
		if (a&&i>s[u]-'0') continue;
		for (int j=0;j<=1;j++)
		{
			if (b&&j>s[u]-'0') continue;
			for (int k=0;k<=1;k++)
			{
				if (c&&k>s[u]-'0') continue;
				res=(res+dfs(u+1,a&(s[u]-'0'==i),b&(s[u]-'0'==j),c&(s[u]-'0'==k),x|((i^j)&(j^k)),y|((i^k)&(j^k)),z|((i^k)&(j^i))))%mod;
			}
		}
	}
	dp[u][a][b][c][x][y][z]=res;
	return res;
}

int main()
{
	cin >> (s+1);
	n=strlen(s+1);
	memset(dp,-1,sizeof(dp));
	cout << dfs(1,1,1,1,0,0,0);
	return 0;
}

```


---

## 作者：Blunt_Feeling (赞：6)

## CF1710C XOR Triangle 题解

最近复习了数位 DP，又恰好做到了这题，顺便写篇题解。题意很简单，给出一个二进制大数 $n$，求满足 $0\le a,b,c\le n$ 且 $a\oplus b$，$b\oplus c$，$a\oplus c$ 可围成三角形的方案数。

考虑枚举 $n$ 的每一位，回想一下正常的数位 DP，我们枚举这一位可以填的数字，外加判断需要满足的条件。在这题中，我们需要一次性决定 $a_i,b_i,c_i$ 这 $3$ 个数的值，并且考虑这三个数互相的限制条件。不妨设 $a_i,b_i,c_i$ 两两异或的结果为 $f,g,h$，容易证明，当且仅当 $f=g=1,h=0$ 时，有 $f+g>h$（因为不可能出现 $f=g=h=1$ 的情况），即 $a_i,b_i,c_i$ 中只有 $1$ 个 $1$ 或者只有 $1$ 个 $0$ 的情况。具体地，当且仅当只有 $a_i=0$ 或只有 $a_i=1$ 时，$a_i\oplus b_i+a_i\oplus c_i>b_i\oplus c_i$，$b_i,c_i$ 同理。于是限制条件有了，可以开始记忆化搜索来数位 DP 了。

### Code

~~因为码风太毒瘤~~，代码请[戳这里](https://codeforces.com/problemset/submission/1710/166201212)。

---

## 作者：Qzong (赞：4)

一个常数更小的做法。

对于 $a \oplus b + b \oplus c = a \oplus c$令 $A = a \oplus b$，$B = b \oplus c$，则 $a \oplus c = A \oplus B$。

显然有 $A \oplus B \leq A + B$。 

则需要满足题意，只需扣除存在 $a \oplus b + b\oplus c = a \oplus c$ 或与其等价式子的三元组即可。

现在我们通过数位 $dp$ 求解 $a \oplus b + b\oplus c = a \oplus c$ 的三元组个数。

记 $f_{i,0/1,0/1,0/1}$ 表示完成了前 $i$ 个字符，$n$ 为给定的字符串，$a,b,c$ 是否与 $n$ 全部相等的个数。

根据上述条件，每一个二进制位都要满足 $a \oplus b + b \oplus c = a \oplus c$。

这样的 $(a,b,c)$ 有 $6$ 种。

有 $(0,0,0),(0,0,1),(0,1,1),(1,0,0),(1,1,0),(1,1,1)$ 共 $6$ 种。

根据数位 $dp$ 的操作转移即可。

具体转移式子可以参考代码。

最后通过容斥将重复算的减去即可。

有两个以上等式的三元组都很容易计算。

```cpp

#include<cstdio>
const int N=20000020;
const unsigned int mod=998244353;
unsigned long long f[2][2][2][2],now,res,ans;
char s[N];
int main(){
	int i,n=0,o=0;
	scanf("%s",s),f[0][0][0][0]=1;
	for(i=0;s[i];i++,n++)now=now*2%mod,now+=s[i]-'0';
	for(i=0;i<n;i++,o^=1){
		if(s[i]=='0') {
			f[o^1][0][0][0]=f[o][0][0][0];
			f[o^1][1][0][0]=f[o][1][0][0]*2%mod;
			f[o^1][0][0][1]=f[o][0][0][1]*2%mod;
			f[o^1][0][1][1]=f[o][0][1][1]*3%mod;
			f[o^1][1][0][1]=f[o][1][0][1]*3%mod;
			f[o^1][1][1][0]=f[o][1][1][0]*3%mod;
			f[o^1][1][1][1]=f[o][1][1][1]*6%mod; 
		}
		else {
			f[o^1][0][0][0]=f[o][0][0][0];
			f[o^1][1][0][0]=(f[o][1][0][0]*2+f[o][0][0][0])%mod;
			f[o^1][0][0][1]=(f[o][0][0][1]*2+f[o][0][0][0])%mod;
			f[o^1][0][1][1]=(f[o][0][1][1]*3+f[o][0][0][1]+f[o][0][1][0]*2+f[o][0][0][0])%mod;
			f[o^1][1][0][1]=(f[o][1][0][1]*3+f[o][0][0][1]+f[o][1][0][0])%mod;
			f[o^1][1][1][0]=(f[o][1][1][0]*3+f[o][1][0][0]+f[o][0][1][0]*2+f[o][0][0][0])%mod;
			f[o^1][1][1][1]=(f[o][1][1][1]*6+f[o][0][1][1]*3+f[o][1][0][1]*3+f[o][1][1][0]*3+f[o][0][0][1]*2+f[o][1][0][0]*2+f[o][0][0][0])%mod;
		}
	}
	for(i=0;i<8;i++)res=(res+f[o][i&1][(i>>1)&1][(i>>2)&1])%mod;
	now=(now+1)%mod,ans=(1llu*4*mod+now*now%mod*now+3*now%mod*now-now-3*res)%mod;
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}
```

把第一维彻底压去。

```cpp
#include<cstdio>
const int N=20000020;
const unsigned int mod=998244353;
unsigned long long f[2][2][2],now,res,ans;
char s[N];
int main(){
	int i,n=0,o=0;
	fread(s,1,N,stdin);
	for(i=0;s[i]>='0'&&s[i]<='1';i++,n++)now=now*2%mod,now+=s[i]-'0';
	for(i=0;i<n;i++,o^=1){
		if(s[i]=='0') {
			f[1][0][0]=f[1][0][0]*2%mod;
			f[0][0][1]=f[0][0][1]*2%mod;
			f[0][1][1]=f[0][1][1]*3%mod;
			f[1][0][1]=f[1][0][1]*3%mod;
			f[1][1][0]=f[1][1][0]*3%mod;
			f[1][1][1]=f[1][1][1]*6%mod; 
		}
		else {
			f[1][1][1]=(f[1][1][1]*6+f[0][1][1]*3+f[1][0][1]*3+f[1][1][0]*3+f[0][0][1]*2+f[1][0][0]*2+1)%mod;
			f[0][1][1]=(f[0][1][1]*3+f[0][0][1]+f[0][1][0]*2+1)%mod;
			f[1][0][1]=(f[1][0][1]*3+f[0][0][1]+f[1][0][0])%mod;
			f[1][1][0]=(f[1][1][0]*3+f[1][0][0]+f[0][1][0]*2+1)%mod;
			f[1][0][0]=(f[1][0][0]*2+1)%mod;
			f[0][0][1]=(f[0][0][1]*2+1)%mod;
		}
	}
	for(i=1;i<8;i++)res=(res+f[i&1][(i>>1)&1][(i>>2)&1])%mod;res=res+1;
	now=(now+1)%mod,ans=(1llu*4*mod+now*now%mod*now+3*now%mod*now-now-3*res)%mod;
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}

---

## 作者：Leasier (赞：2)

前置芝士：[数位 dp](https://oi-wiki.org/dp/number/)

考虑异或的性质，注意到 $a + b = (a \operatorname{xor} b) + 2(a \operatorname{and} b)$。

对于 $a \operatorname{xor} b, a \operatorname{xor} c, b \operatorname{xor} c$，注意到 $(a \operatorname{xor} b) \operatorname{xor} (a \operatorname{xor} c) = b \operatorname{xor} c$（另外两个等式同理），则只要 $(a \operatorname{xor} b) \operatorname{and} (a \operatorname{xor} c) > 0$ 成立时 $(a \operatorname{xor} b) + (a \operatorname{xor} c) > b \operatorname{xor} c$ 成立（另外两个不等式同理）。

设 $dp_{i, j, k, l, x, y, z, p, q, r}$ 表示现在考虑从高到低第 $i$ 位，$j = 0/1$ 表示当前 $a \operatorname{xor} b$ 是否有非 $0$ 项，$k, l$ 表示另外两项，$x = 0/1$ 表示当前 $a$ 是否受 $n$ 的当前位的限制，$y, z$ 表示另外两项，$p = 0/1$ 表示 $(a \operatorname{xor} b) \operatorname{and} (a \operatorname{xor} c) > 0$ 是否已经成立，$q, r$ 表示另外两项。

初值：$dp_{0, 0, 0, 0, 0, 0, 0, 0, 0, 0} = 1$。

转移：$dp_{i + 1, j \operatorname{or} (a \operatorname{xor} b), k \operatorname{or} (a \operatorname{xor} c), l \operatorname{or} (b \operatorname{xor} c), x \operatorname{and} [a = n_{i + 1}], y \operatorname{and} [b = n_{i + 1}], z \operatorname{and} [c = n_{i + 1}], p \operatorname{or} ((a \operatorname{xor} b) \operatorname{xor} (a \operatorname{xor} c)), q \operatorname{or} ((a \operatorname{xor} b) \operatorname{xor} (b \operatorname{xor} c)), r \operatorname{or} ((a \operatorname{xor} c) \operatorname{xor} (b \operatorname{xor} c))} \leftarrow dp_{i + 1, j \operatorname{or} (a \operatorname{xor} b), k \operatorname{or} (a \operatorname{xor} c), l \operatorname{or} (b \operatorname{xor} c), x \operatorname{and} [a = n_{i + 1}], y \operatorname{and} [b = n_{i + 1}], z \operatorname{and} [c = n_{i + 1}], p \operatorname{or} ((a \operatorname{xor} b) \operatorname{xor} (a \operatorname{xor} c)), q \operatorname{or} ((a \operatorname{xor} b) \operatorname{xor} (b \operatorname{xor} c)), r \operatorname{or} ((a \operatorname{xor} c) \operatorname{xor} (b \operatorname{xor} c))} + dp_{i, j, k, l, x, y, z, p, q, r}$，其中 $a, b, c$ 的范围由 $x, y, z$ 限制，表示我们枚举的当前的 $a, b, c$。

答案：$\displaystyle\sum_{i = 0}^1 \sum_{j = 0}^1 \sum_{k = 0}^1 dp_{\lfloor \log_2 n \rfloor + 1, 1, 1, 1, i, j, k, 1, 1, 1}$。

令 $M = 2^{13}$，则时间复杂度为 $O(M \log n)$，在 CF 上要跑 5.5s 左右，不能通过。

考虑把空状态拿去转移，你会发现这样剪枝后跑得飞快，在 CF 上只跑了 500ms 左右。

~~u1s1，10 维 dp 是不是离谱了点。~~

代码：
```cpp
#include <stdio.h>
#include <string.h>

const int mod = 998244353;
int n[200007], dp[2][2][2][2][2][2][2][2][2][2];
char n_[200007];

int main(){
	int m, lst, ans = 0;
	scanf("%s", &n_[1]);
	m = strlen(&n_[1]);
	lst = m & 1;
	for (int i = 1; i <= m; i++){
		n[i] = n_[i] - '0';
	}
	dp[0][0][0][0][1][1][1][0][0][0] = 1;
	for (int i = 0; i < m; i++){
		int pre = i & 1, cur = pre ^ 1, ii = i + 1;
		for (int j = 0; j <= 1; j++){
			for (int k = 0; k <= 1; k++){
				for (int l = 0; l <= 1; l++){
					for (int x = 0; x <= 1; x++){
						for (int y = 0; y <= 1; y++){
							for (int z = 0; z <= 1; z++){
								for (int p = 0; p <= 1; p++){
									for (int q = 0; q <= 1; q++){
										for (int r = 0; r <= 1; r++){
											dp[cur][j][k][l][x][y][z][p][q][r] = 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		for (int j = 0; j <= 1; j++){
			for (int k = 0; k <= 1; k++){
				for (int l = 0; l <= 1; l++){
					for (int x = 0; x <= 1; x++){
						int upa = x == 0 ? 1 : n[ii];
						for (int y = 0; y <= 1; y++){
							int upb = y == 0 ? 1 : n[ii];
							for (int z = 0; z <= 1; z++){
								int upc = z == 0 ? 1 : n[ii];
								for (int p = 0; p <= 1; p++){
									for (int q = 0; q <= 1; q++){
										for (int r = 0; r <= 1; r++){
											if (dp[pre][j][k][l][x][y][z][p][q][r] != 0){
												for (int s = 0; s <= upa; s++){
													int t = x & (s == n[ii]);
													for (int u = 0; u <= upb; u++){
														int v = j | (s ^ u), w = y & (u == n[ii]);
														for (int a = 0; a <= upc; a++){
															int b = k | (s ^ a), c = l | (u ^ a), d = z & (a == n[ii]), e = p | ((s ^ u) & (s ^ a)), f = q | ((s ^ u) & (u ^ a)), g = r | ((s ^ a) & (u ^ a));
															dp[cur][v][b][c][t][w][d][e][f][g] = (dp[cur][v][b][c][t][w][d][e][f][g] + dp[pre][j][k][l][x][y][z][p][q][r]) % mod;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i <= 1; i++){
		for (int j = 0; j <= 1; j++){
			for (int k = 0; k <= 1; k++){
				ans = (ans + dp[lst][1][1][1][i][j][k][1][1][1]) % mod;
			}
		}
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：do_while_true (赞：2)

$x=a\operatorname{xor} b,y=b\operatorname{xor} c,z=a\operatorname{xor} c$，则 $x\operatorname{xor} y\operatorname{xor} z=0$．

即有 $x\operatorname{xor} y=z$，考虑异或是在做不进位加法，则有 $x+y>z=x\operatorname{xor} y\Leftrightarrow x\operatorname{and} y\neq 0$．

故数位 dp 记 $f_{i,0/1,0/1,0/1,0/1,0/1,0/1}$ 表示从高到低填到第 $i$ 位，$a,b,c$ 有没有顶到上界（前 $(i-1)$ 位和 $n$ 一样，以及 $x\operatorname{and} y,y\operatorname{and}z,x\operatorname{and}z$ 是不是非 $0$）．

记忆化搜索，很好写。

```cpp
int solve(int pos,int s1,int s2,int s3,int t1,int t2,int t3){
	if(pos==n+1)
		return t1&&t2&&t3;
	if(vis[pos][s1][s2][s3][t1][t2][t3])
		return f[pos][s1][s2][s3][t1][t2][t3];
	int &now=f[pos][s1][s2][s3][t1][t2][t3];
	vis[pos][s1][s2][s3][t1][t2][t3]=1;
	for(int a=0;a<=min(v[pos]+s1,1);a++)
		for(int b=0;b<=min(v[pos]+s2,1);b++)
			for(int c=0;c<=min(v[pos]+s3,1);c++){
				int p1=s1|(a<v[pos]),p2=s2|(b<v[pos]),p3=s3|(c<v[pos]);
				int x=a^b,y=b^c,z=a^c;
				int q1=t1|(x&&y),q2=t2|(y&&z),q3=t3|(x&&z);
				cadd(now,solve(pos+1,p1,p2,p3,q1,q2,q3));
			}
	return now;
}
```

---

## 作者：TLEWA (赞：1)

看到 $n$ 的范围（$ 0 < n < 2^{200\,000} $），果断开始考虑数位 dp。

发现 $a,b,c$ 的每一个位总共只有八种不同的取值组合，我们可以将每种情况一一列举找规律，打表代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

int main() {
	for(int a=0;a<=1;++a) {
		for(int b=0;b<=1;++b) {
			for(int c=0;c<=1;++c) {
				cout << a << ' ' << b << ' ' << c << ' ' << (a^b) << ' ' << (b^c) << ' ' << (a^c) << endl;
			}
		}
	}
	return 0;
}
```

发现一个很重要的性质：

设 ${a_i}\oplus{b_i},{b_i}\oplus{c_i},{a_i}\oplus{c_i}$ 这三个值分别为 $x,y,z$，对于每一位上的 $x,y,z$，观察发现其中任意两个值的和必然**大于等于**第三个值。

在每一位都遵循上述规律的情况下，显然 $a\oplus b,b\oplus c,a\oplus c$ 中的任意两个值之和也**大于等于**第三个值。在这种情况下，只要有一位的 $x,y,z$ 组合中存在任意两值**大于**第三值，那么对于 $a,b,c$，这个数量关系也可以对应。

于是我们就可以设计出 dp 数组了，从高往低 dp，分别记录 $a,b,c$ 已填位是否都与 $n$ 相同，再记录 $x+y>z,x+z>y,y+z>x$ 是否已经成立，最后我们统计全部三个条件成立的数量，总时间复杂度 $O(2^9n)$。

AC 代码：
```cpp
#include<bits/stdc++.h>
#define LL long long

using namespace std;

const int N=200005;

/*
设 dp[i][a1][b1][c1][X1][X2][X3] 表示当前考虑到第 i 位，a b c 是否都符合限制上限，三个要求是否满足 
*/

const LL mod=998244353;

string n;
int siz;
LL dp[N][2][2][2][2][2][2];

LL dfs(int now,bool amax,bool bmax,bool cmax,bool X1,bool X2,bool X3) {
	if(now>siz) return (X1&&X2&&X3);
	if(dp[now][amax][bmax][cmax][X1][X2][X3]) return dp[now][amax][bmax][cmax][X1][X2][X3];
	
	int nown=n[now]-'0';
	
	int ab,bc,ac;
	bool newX1,newX2,newX3;
	for(int a=0;a<=1;++a) {
		for(int b=0;b<=1;++b) {
			for(int c=0;c<=1;++c) {
				if( (amax&&(a>nown)) || (bmax&&(b>nown)) || (cmax&&(c>nown)) ) continue;
				ab=(bool)(a^b),bc=(bool)(b^c),ac=(bool)(a^c);
				newX1=(ab+bc)>ac,newX2=(ab+ac)>bc,newX3=(bc+ac)>ab;
				dp[now][amax][bmax][cmax][X1][X2][X3]+=dfs(now+1,amax&&(a==nown),bmax&&(b==nown),cmax&&(c==nown),X1||newX1,X2||newX2,X3||newX3);
				dp[now][amax][bmax][cmax][X1][X2][X3]%=mod;
			}
		}
	}
	
	return dp[now][amax][bmax][cmax][X1][X2][X3];
}

int main() {
	cin >> n;
	siz=n.size();
	n=' '+n;
	
	LL ans=0;
	int ab,bc,ac;
	bool X1,X2,X3;
	for(int a=0;a<=1;++a) {
		for(int b=0;b<=1;++b) {
			for(int c=0;c<=1;++c) {
				ab=(bool)(a^b),bc=(bool)(b^c),ac=(bool)(a^c);
				X1=(ab+bc)>ac,X2=(ab+ac)>bc,X3=(bc+ac)>ab;
				ans+=dfs(2,a,b,c,X1,X2,X3);
				ans%=mod;
			}
		}
	}
	
	cout << ans;
	return 0;
}

```

---

## 作者：HyperSQ (赞：1)

首先考虑到一个性质：$a \oplus b\leq a+b$ 当且仅当 $a\operatorname{and}b=0$。

因此考虑一对 $(a,c)$，有多少个 $b$ 能够满足 $a\oplus b+b\oplus c>a\oplus c$。

也就是：$(a\oplus b)\operatorname{and}(b\oplus c)\not=0$

因此考虑这个条件的话，$abc$ 一定存在某一个数位依次为 010 和 101。（这是因为如果这一位异或 $b$  的这一位都为 $1$，那么 $a,c$ 的这一位应该相同）

这是其中一个条件。对于另外两个同理，可以得到三个条件，每个条件可以由两个情况满足。

于是我们可以数位+状压DP，其中用一个三维的状态表示当前已经满足了哪些条件，$O(2^3)$ 枚举转移。

[Code](https://www.luogu.com.cn/paste/0pmv56xs)

---

## 作者：xiaofu15191 (赞：0)

今天正好 VP 到的数位 DP 好题。

考虑我现在要选择 $a,b,c$ 从高到低的第 $now$ 位。此时令 $x=a \oplus b,y=a \oplus c,z=b \oplus c$。

思考当前做到第 $now$ 位时，满足了什么条件，$x,y,z$ 才能构成三角形。

让我们观察 $x+y>z$ 的情况。此时把式子化开即为 $(a \oplus b) + (a \oplus c)>(b \oplus c)$。发现对于当前的第 $now$ 位来说，一定有 $x+y \ge z$。证明如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7aj64vgm.png)

因此，我们可以用 $limit_{a,b,c}=1/0$ 表示当前的 $a/b/c$ 是否小于等于 $n$，$b1,b2,b3$ 分别表示 $x+y>z,x+z>y,y+z>x$ 三个条件是否满足。

```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const long long mod=998244353;
string str;
long long n,f[200010][2][2][2][2][2][2],origin[200010];
long long dp(long long now,bool limit_a,bool limit_b,bool limit_c,bool b1,bool b2,bool b3)
{
	if(now>n) return b1&&b2&&b3;
	if(f[now][limit_a][limit_b][limit_c][b1][b2][b3]!=-1) return f[now][limit_a][limit_b][limit_c][b1][b2][b3];
	long long ans=0;
	for(long long i=0;i<=1;i++)
	{
		if((limit_a&&i)>origin[now]) continue;
		for(long long j=0;j<=1;j++)
		{
			if((limit_b&&j)>origin[now]) continue;
			for(long long k=0;k<=1;k++)
			{
				if((limit_c&&k)>origin[now]) continue;
				ans=(ans+dp(now+1,limit_a&&(i==origin[now]),limit_b&&(j==origin[now]),limit_c&&(k==origin[now]),b1|((i^j)&(i^k)),b2|((i^j)&(j^k)),b3|((i^k)&(j^k)))%mod)%mod;
			}
		}
	}
	f[now][limit_a][limit_b][limit_c][b1][b2][b3]=ans;
	return ans;
}
int main()
{
	cin>>str;
	memset(f,-1,sizeof(f));
	n=str.size();
	for(long long i=0;i<n;i++) origin[i+1]=str[i]-'0';
	cout<<dp(1,1,1,1,0,0,0)<<endl;
}
```

---

## 作者：ax_by_c (赞：0)

首先观察 $a\oplus b,a\oplus c,b\oplus c$ 这三个数（下文称其为 $x,y,z$），发现 $x\oplus y=z,x\oplus z=y,y\oplus z=x$，而题目要求 $x+y>z,x+z>y,y+z>x$。

看着这些条件不难想到 $a+b=a\oplus b+2(a\operatorname{and}b)$。

于是可得 $a+b\ge a\oplus b$，当 $a\operatorname{and}b=0$ 时取等号。

所以限制就是 $x\operatorname{and}y\neq0,x\operatorname{and}z\neq0,y\operatorname{and}z\neq0$。

于是考虑数位 DP，记录 $a,b,c$ 是否顶到上界以及 $x\operatorname{and}y,x\operatorname{and}z,y\operatorname{and}z$ 是否不等零即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
const int mod=998244353;
const int N=2e5+5;
char s[N];
int n,vis[N][2][2][2][2][2][2];
int dfs(int u,bool la,bool lb,bool lc,bool abbc,bool abac,bool bcac){
	if(u==n+1)return abbc&&abac&&bcac;
	if(vis[u][la][lb][lc][abbc][abac][bcac]!=-1)return vis[u][la][lb][lc][abbc][abac][bcac];
	int lima=1,limb=1,limc=1;
	if(la)lima=s[u]-48;
	if(lb)limb=s[u]-48;
	if(lc)limc=s[u]-48;
	vis[u][la][lb][lc][abbc][abac][bcac]=0;
	for(int a=0;a<=lima;a++){
		for(int b=0;b<=limb;b++){
			for(int c=0;c<=limc;c++){
				vis[u][la][lb][lc][abbc][abac][bcac]=(vis[u][la][lb][lc][abbc][abac][bcac]+dfs(u+1,la&&(a==lima),lb&&(b==limb),lc&&(c==limc),abbc||(a^b)&&(b^c),abac||(a^b)&&(a^c),bcac||(b^c)&&(a^c)))%mod;
			}
		}
	}
	return vis[u][la][lb][lc][abbc][abac][bcac];
}
void main(){
	scanf("%s",s+1);
	for(int i=1;s[i];i++)n=i;
	for(int i=1;i<=n;i++){
		for(int a1=0;a1<=1;a1++)
		for(int a2=0;a2<=1;a2++)
		for(int a3=0;a3<=1;a3++)
		for(int a4=0;a4<=1;a4++)
		for(int a5=0;a5<=1;a5++)
		for(int a6=0;a6<=1;a6++)
		vis[i][a1][a2][a3][a4][a5][a6]=-1;
	}
	printf("%d\n",dfs(1,1,1,1,0,0,0));
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

