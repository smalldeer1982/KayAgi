# [ABC317F] Nim

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc317/tasks/abc317_f

整数 $ N,A_1,A_2,A_3 $ が与えられます。以下の $ 3 $ つの条件を全て満たすような正整数の組 $ (X_1,X_2,X_3) $ の個数を $ 998244353 $ で割ったあまりを求めてください。

- 全ての $ i $ で $ 1\leq\ X_i\ \leq\ N $ である。
- 全ての $ i $ で $ X_i $ は $ A_i $ の倍数である。
- $ (X_1\ \oplus\ X_2)\ \oplus\ X_3\ =\ 0 $ である。ただし、$ \oplus $ はビット単位の xor を表す。

ビット単位 xor とは非負整数 $ A,\ B $ のビット単位 xor 、$ A\ \oplus\ B $ は、以下のように定義されます。 - $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。

例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{18} $
- $ 1\ \leq\ A_i\ \leq\ 10 $
- 入力は全て整数である

### Sample Explanation 1

$ (X_1,X_2,X_3) $ が $ (6,3,5),(6,12,10),(12,6,10),(12,9,5) $ のときの $ 4 $ 通りが条件を満たします。

## 样例 #1

### 输入

```
13 2 3 5```

### 输出

```
4```

## 样例 #2

### 输入

```
1000000000000000000 1 1 1```

### 输出

```
426724011```

## 样例 #3

### 输入

```
31415926535897932 3 8 4```

### 输出

```
759934997```

# 题解

## 作者：ran_qwq (赞：12)

[题目传送门](https://atcoder.jp/contests/abc317/tasks/abc317_f)

第一次做出 F。

---
给定 $N,X,Y,Z(N\le10^{18},1\le X,Y,Z\le10)$，求满足以下条件的三元组 $(a,b,c)$ 的数量模 $998244353$ 的值：

- $1\le a,b,c\le N$。

- $X\mid a,Y\mid b,Z\mid c$。

- $(a\bigoplus b)\bigoplus c=0$。

---
注意到 $X,Y,Z$ 很小，考虑数位 dp。

设 $dp_{k,x,y,z,0/1,0/1,0/1,0/1,0/1,0/1}$ 为处理到二进制的第 $k$ 位，当前 $a$ 模 $X$ 余 $x$，$b$ 模 $Y$ 余 $y$，$c$ 模 $Z$ 余 $z$，当前 $a,b,c$ 没取到或取到最大值，$a,b,c$ 为或不为 $0$ 的方案数。

不难看出，对于一位，如果 $a,b,c$ 全取 $0$ 或恰有两个取 $1$ 时，$a,b,c$ 异或和这一位为 $0$。如果所有位都是这样，$a,b,c$ 的异或和就是 $0$。

所以一个位的取值有 $a,b,c$ 全取 $0$、$a,b$ 取 $1$、$a,c$ 取 $1$、$b,c$ 取 $1$ 这四种情况。方案数相加就是当前状态的方案数。

[AT 提交记录](https://atcoder.jp/contests/abc317/submissions/44976744)

---

## 作者：lottle1212 (赞：10)

# [[ABC317F] Nim](https://www.luogu.com.cn/problem/AT_abc317_f) 题解

## 题目大意

给出四个正整数 $N, A_1, A_2, A_3$，满足 $1 \leq N \leq 10 ^ {18}, 1 \leq A_i \leq 10$。

设有三元组 $X_1, X_2, X_3$，且 $1 \leq X_i \leq N$，求出满足对于 $i = 1, 2, 3$ 时 $X_i$ 为 $A_i$ 的倍数，且 $X_1 \oplus X_2 \oplus X_3 = 0$ 的三元组个数。

## 解题思路

不难想到 $O(N ^ 3)$ 的暴力枚举做法，以及在其之上稍作优化的 $O(N ^2)$ 做法。由于 $N$ 极大，这两种方法都无法在限定时间内完成任务。而 $A_i \leq 10$，这启发我们可以在 $A_i$ 上做功夫。

众所周知，一个数为另一个数的倍数可以表示为一个数对另一个数取模余数为 $0$。在这里 $A_i \leq 10$，则余数只有 $10$ 种状态，这就让我们想到了数位 DP。

首先，我们将 $N$ 转换成二进制数。在数位 DP 中由高到低对二进制下的 $X_1, X_2$ 分别枚举每一位，并通过 $X_1, X_2$ 的值求出 $X_3$。在 DP 过程中，我们要实时记录 $X_1, X_2, X_3$ 的值对 $A_1, A_2, A_3$ 取模的结果，最终判断三者是否都为 $0$。

还有一点需要注意，由于 $X_i$ 必须是正整数，因此，我们在计算时需要排除有 $X_i$ 为 $0$ 的情况。这一部分可以用容斥来解决，不过我在赛时选择了再增加三维状态，来表示 $X_1, X_2, X_3$ 是否大于 $0$。

于是一份毒瘤的十维数位 DP 代码就诞生了 QwQ。

注：此份代码使用了记忆化搜索的写法来进行数位 DP。

## 代码实现

```cpp
#include <iostream>
#include <string.h>
#define int long long //不开 long long 见祖宗！
using namespace std;
const int N = 64, mod = 998244353;
int dp[N][10][10][10][2][2][2][2][2][2], n, a1, a2, a3, a[N];
// dp 数组第一维表示做到的位置，二至四维表示余数，五至七维表示现在的数是否撑满，八至十维表示现在的数是否大于0。
// a 数组为转换成二进制后的 n。
int rd() {
	int res = 0; bool f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
	while (ch >= '0' && ch <= '9') res = (res << 1) + (res << 3) + (ch ^ 48), ch = getchar();
	return f ? -res : res;
}
int dfs(int pos, int p1, int p2, int p3, bool u1, bool u2, bool u3, bool x1, bool x2, bool x3) {
	if (pos < 0) { return (! p1) && (! p2) && (! p3) && x1 && x2 && x3; }
	if (dp[pos][p1][p2][p3][u1][u2][u3][x1][x2][x3] != -1) return dp[pos][p1][p2][p3][u1][u2][u3][x1][x2][x3];
	dp[pos][p1][p2][p3][u1][u2][u3][x1][x2][x3] = 0;
	for (int i = 0; i <= (u1 ? a[pos] : 1); ++ i)
		for (int j = 0; j <= (u2 ? a[pos] : 1); ++ j)
			if ((i ^ j) <= (u3 ? a[pos] : 1)) {
				dp[pos][p1][p2][p3][u1][u2][u3][x1][x2][x3] += dfs(pos - 1, ((p1 << 1) + i) % a1, ((p2 << 1) + j) % a2, ((p3 << 1) + (i ^ j)) % a3, u1 && i == a[pos], u2 && j == a[pos], u3 && (i ^ j) == a[pos], x1 || i, x2 || j, x3 || (i ^ j)),
				dp[pos][p1][p2][p3][u1][u2][u3][x1][x2][x3] %= mod;
			}
	return dp[pos][p1][p2][p3][u1][u2][u3][x1][x2][x3];
} // 数位 DP
signed main() {
	n = rd(), a1 = rd(), a2 = rd(), a3 = rd();
	memset(dp, -1, sizeof (dp)); // 初始化
	for (int i = 0; i <= 62; ++ i) a[i] = (n >> i) & 1; // 转换成二进制
	printf("%lld\n", dfs(62, 0, 0, 0, 1, 1, 1, 0, 0, 0));
	return 0;
}
```


---

## 作者：_sunkuangzheng_ (赞：5)

纪念第一次赛场切 F。

**【题目分析】**

很明显的数位 dp。

注意到 $1 \le A_i \le 10$，所以我们可以把 $X_i$ 是 $A_i$ 的倍数这一条件转化为枚举 $X_i \bmod A_i = 0$ 并放在 dp 状态中。

设 $f_{pos,a_1,a_2,a_3,l_1,l_2,l_3,p_1,p_2,p_3}$ 表示当前枚举到了从高到低的第 $pos$ 位，$X_i \bmod A_i = a_i$，$X_i$ 是否顶住上界的状态是 $l_i$，$X_i$ 是否全填 $0$ 的状态为 $p_i$ 的方案数，可以在 dfs 时转移。

枚举每一位时，枚举 $i,j,k$ 表示 $X_1,X_2,X_3$ 这一位的数字，显然如果任意一位上 $i \oplus j \oplus k \ne 0$ 那么这个数字是不合法的。然后就是常规的数位 dp 写法了。

**【代码】**

由于一开始读错题导致误认为 $X_i$ 的上界不一样所以采用了三个数组 $n_1,n_2,n_3$，这三者没有区别。
 
`q1 = (i == 0 && p1)` 的意思是如果当前数字全都是 $0$，且这一位还填 $0$，那么这个数字仍然是 $0$。

`(l1 && i == u1)` 的意思是如果当前数字顶上界，且这一位还与上界相同，那么这个数字仍顶上界。

最终答案合法的条件是 $a_i = 0(1 \le i \le 3)$ 且 $p_i = 0(1 \le i \le 3)$。
 
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
int f[75][12][12][12][2][2][2][2][2][2],n,n1[75],n2[75],n3[75],c1,c2,c3;
int dfs(int pos,int a1,int a2,int a3,int l1,int l2,int l3,int p1,int p2,int p3){
    if(pos == -1) return (!a1 && !a2 && !a3) && !(p1 || p2 || p3);
    if(f[pos][a1][a2][a3][l1][l2][l3][p1][p2][p3] != -1) return f[pos][a1][a2][a3][l1][l2][l3][p1][p2][p3];
    int ans = 0;
    int u1 = (l1 ? n1[pos] : 1),u2 = (l2 ? n2[pos] : 1) ,u3 = (l3 ? n3[pos] : 1);
    for(int i = 0;i <= u1;i ++){
        for(int j = 0;j <= u2;j ++){
            for(int k = 0;k <= u3;k ++){
                int q1 = (i == 0 && p1),q2 = (j == 0 && p2),q3 = (k == 0 && p3);
                if((i ^ j ^ k)) continue;
                int b1 = (a1 + (1ll << pos)*i) % c1,b2 = (a2 + (1ll << pos)*j) % c2,b3 = (a3 + (1ll << pos)*k) % c3;  
                ans = (ans + dfs(pos-1,b1,b2,b3,(l1 && i == u1),(l2 && j == u2),(l3 && k == u3),q1,q2,q3)) % mod;
            }
        }
    }return f[pos][a1][a2][a3][l1][l2][l3][p1][p2][p3] = ans;
}
signed main(){
    cin >> n >> c1 >> c2 >> c3;memset(f,-1,sizeof(f));
    for(int i = 62;i >= 0;i --) n1[i] = n2[i] = n3[i] = ((n >> i) & 1);
    cout << dfs(62,0,0,0,1,1,1,1,1,1) << "\n";
}
```

---

## 作者：lfxxx (赞：4)

调了一小时结果发现爆 long long 了。

考虑数位 dp，具体来说，设计状态 $dp_{i,r_1,r_2,r_3,mx_1,mx_2,mx3_,c_1,c_2,c_3}$ 表示当前考虑到第 $i$ 位，$x_1,x_2,x_3$ 模 $a_1,a_2,a_3$ 等于 $r_1,r_2,r_3$ 三个数是否达到 $n$ 的上界以及是否全部是 $0$。

然后从高到低枚举三个数这一位填什么（满足异或为 $0$ 一限制）往下转移即可。

为了写起来方便这里写的是记忆化搜索。

```cpp
#include<bits/stdc++.h>
#define int long long
//#define lowbit(x) (x&-(x))
using namespace std;
//const int maxn =
const int mod = 998244353;
vector<int> dight;
int dp[65][10][10][10][2][2][2][2][2][2];
int a1,a2,a3;
int solve(int p,int r1,int r2,int r3,bool mx1,bool mx2,bool mx3,bool c1,bool c2,bool c3){//当前考虑到第 p 位且 x1,x2,x3 模 a1,a2,a3 为 r1,r2,r3 是否到达上界 是否全部填 0
    if(dp[p][r1][r2][r3][mx1][mx2][mx3][c1][c2][c3]!=-1) return dp[p][r1][r2][r3][mx1][mx2][mx3][c1][c2][c3];
    if(p==0){ 
        if(r1==0&&r2==0&&r3==0&&c1==false&&c2==false&&c3==false){
            return dp[p][r1][r2][r3][mx1][mx2][mx3][c1][c2][c3]=1;
        }
        else{
            return dp[p][r1][r2][r3][mx1][mx2][mx3][c1][c2][c3]=0;
        }
    }
    int res=0;
    for(int i=0;i<=(mx1==true?dight[p-1]:1);i++){
        for(int j=0;j<=(mx2==true?dight[p-1]:1);j++){
            for(int k=0;k<=(mx3==true?dight[p-1]:1);k++){
                if((i^j)^k==0){
                    res+=solve(p-1,(a1+r1+((1ll<<(p-1))*i)%a1)%a1,(a2+r2+((1ll<<(p-1))*j)%a2)%a2,(a3+r3+((1ll<<(p-1))*k)%a3)%a3,mx1&(i==dight[p-1]),mx2&(j==dight[p-1]),mx3&(k==dight[p-1]),c1&&(i==0),c2&&(j==0),c3&&(k==0));
                    res%=mod;
                }
            }
        }
    }
    return dp[p][r1][r2][r3][mx1][mx2][mx3][c1][c2][c3]=res;
}
int n;       
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(int i=0;i<65;i++)
        for(int r1=0;r1<10;r1++)
            for(int r2=0;r2<10;r2++)
                for(int r3=0;r3<10;r3++)
                    for(int mx1=0;mx1<2;mx1++)
                        for(int mx2=0;mx2<2;mx2++)
                            for(int mx3=0;mx3<2;mx3++) 
                                for(int c1=0;c1<2;c1++)
                                    for(int c2=0;c2<2;c2++)
                                        for(int c3=0;c3<2;c3++) dp[i][r1][r2][r3][mx1][mx2][mx3][c1][c2][c3]=-1;
    cin>>n;
    cin>>a1>>a2>>a3;
    while(n>0) dight.push_back(n%2),n/=2;
    cout<<solve(dight.size(),0,0,0,true,true,true,true,true,true)<<'\n';
    return 0;
}
```


---

## 作者：ShanQing (赞：4)

### 前言

很遗憾没能 场切6题 。但是个人认为这题不适合放 ABC 的 F。

这个题解基本是按照代码来讲的，所以只能凑合看。且本文的 DP 是按照记忆化搜索的形式写的。

有不理解的或者有笔误可以评论或私信。

### 正文

让人头大的数位 DP。建议评蓝。

将三个数二进制拆分，使三个数异或为 $0$ 相当于每个二进制位三个数中有 $0$ 或 $2$ 个是 $1$。  

所以考虑数位 DP，设 $dp_{i,m_1,m_2,m_3,lim_1,lim_2,lim_3}$ 为第 $i$ 位，三个数模 $A_1$，$A_2$，$A_3$ 分别是 $m_1$，$m_2$，$m_3$，以及三个数有没有最高位限制。

这道题比较特殊。仔细想想可以发现这道题最高位限制 **必须放状态里**。不然 TLE。

接下来是DP的转移。会的跳过捏。

下文设 $S_i$ 为 $N$ 的第 $i$ 位二进制。

马上烧脑起来了。可以结合代码理解。公式比较乱请谅解。

一个状态 $dp_{i,m_1,m_2,m_3,lim_1,lim_2,lim_3}$ 可以如此转移过来：

首先，讨论 **三个数的第 $i$ 位全部为 $0$** 的情况。

**若 $S_i=1$，** 则 $dp_{i-1,m_1,m_2,m_3,0,0,0}$ 可以对状态产生贡献。  

**若 $S_i=0$，** 则 $dp_{i-1,m_1,m_2,m_3,lim_1,lim_2,lim_3}$ 可以对状态产生贡献。

其实就是最高位限制的不同。

然后考虑 **有两个是 $1$** 的情况。

有三种情况，这里以 $X_1$ 和 $X_2$ 的第 $i$ 位为 $1$ 为例。

**若 $S_i=1 \vee (lim_1=0 \wedge lim_2=0)$** ：

则 $dp_{i-1,(m_1+2^i)\bmod A_1,(m_2+2^i)\bmod A_2,m_3,lim_1\wedge S_i=0,lim_2,lim_3}$ 可以贡献。~~此处看不清的话去看代码罢~~ 

可以想想为什么是这样。另外两个情况，同理。

最核心的 DP 转移到这里就完了。还没完，我们又发现我们还要 **减去三个数中有数为 $0$** 的情况。

为此还要再跑一次数位 DP 专门处理。枚举 $X_1$，$X_2$，$X_3$ 为 $0$ 的情况。

举个例子，现在考虑的是 $X_3$ 为 $0$，那么就设 $dp2_{i,m1,m2}$ 为第 $i$ 位，$X_1$，$X_2$ 模 $A_1$，$A_2$ 为 $m_1$，$m_2$ 的情况。

这个 DP 很简单，并没有分类讨论。

 $dp2_{i,m_1,m_2}=dp2_{i-1,m_1,m_2}+dp2_{i-1,(m_1+2^i)\bmod A1,(m_2+2^i)\bmod A_2}$
 
如果考虑的是 $X_1$ 或者 $X_2$ 为 $0$，还是同理 DP 即可。
 
像这样跑三次就可以求出三个数中有数为 $0$ 的不合法贡献。

最后还有一个细节就是这样会把 **三个数全 $0$** 的情况减三次，加回去 $2$ 即可。

## code

希望各位看得来。

```cpp
//writer:Oier_szc

#include <bits/stdc++.h>
#define TS puts("I AK IOI");
#define int long long
using namespace std;
const int N=2005,mod=998244353;
int n,a1,a2,a3,ans=0;
int dp[70][15][15][15][2][2][2];
int S[70],yes[70],len=-1;
int dfs(int deep,int m1,int m2,int m3,bool lim1,bool lim2,bool lim3)
{
	if(deep==-1) return m1==0&&m2==0&&m3==0;
	if(dp[deep][m1][m2][m3][lim1][lim2][lim3]!=-1) return dp[deep][m1][m2][m3][lim1][lim2][lim3];
	int res=0;
	if(S[deep]) res=(res+dfs(deep-1,m1,m2,m3,0,0,0))%mod;
	else res=(res+dfs(deep-1,m1,m2,m3,lim1,lim2,lim3))%mod;
	if(S[deep]||(!lim2&&!lim3)) res=(res+dfs(deep-1,m1,(m2+(1ll<<deep))%a2,(m3+(1ll<<deep))%a3,lim1&&!S[deep],lim2,lim3))%mod;
	if(S[deep]||(!lim1&&!lim3)) res=(res+dfs(deep-1,(m1+(1ll<<deep))%a1,m2,(m3+(1ll<<deep))%a3,lim1,lim2&&!S[deep],lim3))%mod;
	if(S[deep]||(!lim1&&!lim2)) res=(res+dfs(deep-1,(m1+(1ll<<deep))%a1,(m2+(1ll<<deep))%a2,m3,lim1,lim2,lim3&&!S[deep]))%mod;
	dp[deep][m1][m2][m3][lim1][lim2][lim3]=res;
	return res;
}
int dp2[70][15][15],M1,M2;
int dfs2(int deep,int m1,int m2,int lim)
{
	if(deep==-1) return m1==0&&m2==0;
	if(dp2[deep][m1][m2]!=-1&&!lim) return dp2[deep][m1][m2];
	int up=lim?S[deep]:1ll,res=0;
	for(int i=0;i<=up;++i)
	{
		res+=dfs2(deep-1,(m1+(i<<deep))%M1,(m2+(i<<deep))%M2,lim&&i==up);
	}
	if(!lim) dp2[deep][m1][m2]=res;
	return res;
}
signed main()
{
	scanf("%lld%lld%lld%lld",&n,&a1,&a2,&a3);
	while(n)
	{
		S[++len]=n%2;
		n/=2;
	}
	int cnt_0=-2;
	M1=a1,M2=a2;
	memset(dp2,-1,sizeof(dp2));
	cnt_0=(cnt_0+dfs2(len,0,0,1))%mod;
	M1=a1,M2=a3;
	memset(dp2,-1,sizeof(dp2));
	cnt_0=(cnt_0+dfs2(len,0,0,1))%mod;
	M1=a2,M2=a3;
	memset(dp2,-1,sizeof(dp2));
	cnt_0=(cnt_0+dfs2(len,0,0,1))%mod;
	memset(dp,-1,sizeof(dp));
	printf("%lld\n",(dfs(len,0,0,0,1,1,1)-cnt_0+mod)%mod);
	return 0;
}
```

---

## 作者：Hellsing_Alucard (赞：3)

因为这道题要求三个数的异或和为 $0$。

所以可以对每一位进行考虑，每一位的异或都为 $0$。

又因为要求是 $x_1,x_2,x_3$ 的倍数，且 $x_1,x_2,x_3\le10$。

很容易联想到数位 DP。

可以另 $f_{pos,re_1,re_2,re_3,lead_1,lead_2,lead_3,limit_1,limit_2,limit_3}$ 表示到了第 $pos$ 位，第一个数的余数是 $re_1$，第二个数的余数是 $re_2$，第三个数的余数是 $re_3$。

$lead_1,lead_2,lead_3$ 判断是否有数为 $0$。

套上数位 DP 的模板就可以了。

```cpp
int n,x1,x2,x3;
int f[64][11][11][11][2][2][2][2][2][2];
inline int dfs(int pos,int re1,int re2,int re3,int lead1,int lead2,int lead3,int limit1,int limit2,int limit3){
	if(pos==-1)return !re1&&!re2&&!re3&&!lead1&&!lead2&&!lead3;
	int&res=f[pos][re1][re2][re3][lead1][lead2][lead3][limit1][limit2][limit3];
	if(res!=-1)return res;
	res=0;
	int lim=(n>>pos)&1;
	up(i1,0,1){
		up(i2,0,1){
			up(i3,0,1){
				if(!lim){
					if(limit1&&i1)continue;
					if(limit2&&i2)continue;
					if(limit3&&i3)continue;
				}
				if(i1^i2^i3!=0)continue;
				res=(dfs(pos-1,(re1+(i1<<pos))%x1,(re2+(i2<<pos))%x2,(re3+(i3<<pos))%x3,
				lead1&&!i1,lead2&&!i2,lead3&&!i3,limit1&&i1==lim,limit2&&i2==lim,limit3&&i3==lim)+res)%mod;
			}
		}
	}
	return res;
}
signed main(){
	n=read();
	x1=read();x2=read();x3=read();
	memset(f,-1,sizeof f);
	cout<<dfs(59,0,0,0,1,1,1,1,1,1);
	return 0;
}
```

---

## 作者：mRXxy0o0 (赞：1)

# 题意

给出 $N,A_1,A_2,A_3$，求满足题目条件的三元组 $(X_1,X_2,X_3)$ 的个数。

# 分析

由于题目要求 $X_1\oplus X_2\oplus X_3=0$，所以我们不能分开求每一个的个数再乘起来。

考虑三个数一起讨论。

发现 $A$ 很小，就考虑二进制下的数位 DP，记录一下余数、前导零、高位限制。简单计算一下复杂度发现不会超时，于是它就变成了一道数位 DP 板子题了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=62,mod=998244353;
ll n,f[N][10][10][10][2][2][2][2][2][2];
int a1,a2,a3,num[N];
inline ll dfs(int x,int r1,int r2,int r3,bool lm1,bool lm2,bool lm3,bool ld1,bool ld2,bool ld3){
	if(!x) return !r1&&!r2&&!r3&&!ld1&&!ld2&&!ld3;
	ll &v=f[x][r1][r2][r3][lm1][lm2][lm3][ld1][ld2][ld3];
	if(~v) return v;
	int up1=lm1?num[x]:1,up2=lm2?num[x]:1,up3=lm3?num[x]:1;
	v=0;
	for(int i=0;i<=up1;++i){
		for(int j=0;j<=up2;++j){
			for(int k=0;k<=up3;++k){
				if(i^j^k==0) v=(v+dfs(x-1,(r1*2+i)%a1,(r2*2+j)%a2,(r3*2+k)%a3,lm1&&i==up1,lm2&&j==up2,lm3&&k==up3,ld1&&!i,ld2&&!j,ld3&&!k))%mod;
			}
		}
	}
	return v;
}
inline ll solve(ll x){
	int cnt=0;
	while(x) num[++cnt]=x&1,x>>=1;
	return dfs(cnt,0,0,0,1,1,1,1,1,1);
}
int main(){
	memset(f,-1,sizeof f);
	scanf("%lld%d%d%d",&n,&a1,&a2,&a3);
	printf("%lld",solve(n));
	return 0;
}
```


---

