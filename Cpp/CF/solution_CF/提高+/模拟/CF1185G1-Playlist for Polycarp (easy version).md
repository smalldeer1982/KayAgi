# Playlist for Polycarp (easy version)

## 题目描述

### 题意简述

你现在正在选择歌曲。现在共有 $n$ 首歌，每首歌有一个时长 $t_i$ 和一个编号 $g_i$ 。   
您需要求出有多少种选出若干首歌排成一排的方案，使得任意相邻两首歌的编号不同，且所有歌的时长和恰好为 $T$ 。

## 样例 #1

### 输入

```
3 3
1 1
1 2
1 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 3
1 1
1 1
1 3
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 10
5 3
2 1
3 2
5 1
```

### 输出

```
10
```

# 题解

## 作者：Alex_Wei (赞：8)

> [题面传送门](https://www.luogu.com.cn/problem/CF1185G1)。

> 题意简述：有 $n$ 首歌，每首歌有两个属性：时长 $t_i$ 和编号 $g_i$。请求出有多少种选出若干首歌排成一排的方案，使得相邻两首歌的编号不同且总时长为 $T$。本题是 Easy version。

> Easy version：$n,t_i\leq 15,\ g_i\leq 3,\ T\leq 225$。  
> Hard version：$n,t_i\leq 50,\ g_i\leq 3,\ T\leq 2500$。

题解买一送一，超级加倍：[Hasy version](https://www.luogu.com.cn/blog/AlexWei/solution-cf1185g2)（

一些约定：

- 下文中，设 $buc_i$ 为编号为 $i$ 的歌的个数。
- 歌曲**下标**从 $0$ 开始。

---

- 解法 $1$：
  
  数据范围明示状压 DP。设 $f_{i,p}$ 为选出歌的撞状态为 $i$，且末尾编号为 $p$ 时，有多少方案使得相邻两首歌的编号不同。
  
  初始值：$f_{2^i,g_i}=1$。
  
  考虑一个状态能由那些状态转移过来较为繁琐，反之我们考虑一个状态能向哪些状态转移：
  
  $$f_{i,p}\to f_{i+2^j,g_j}\quad(i\&2^j=0\ \mathrm{and}\ p\neq g_j)$$
  
  枚举 $i,p,j$，时间复杂度 $O(n2^n)$。
  
  ```cpp
   const int N=15+2;
	const int T=225+2;
	const int P=1e9+7;
	
	int n,t,ans,ti[N],gi[N],f[1<<N][4];
	
	void add(int &x,int y){x+=y%P; if(x>=P)x-=P;}
	
	int main(){
		n=read(),t=read();
		for(int i=0;i<n;i++)ti[i]=read(),gi[i]=read(),f[1<<i][gi[i]]=1;
		
		for(int i=1;i<1<<n;i++){
			int s=0;
			for(int j=0;j<n;j++)
				if(!((i>>j)&1)){
					for(int k=1;k<4;k++)
						if(gi[j]!=k)
							add(f[i+(1<<j)][gi[j]],f[i][k]);
				}
				else s+=ti[j];
			if(s==t)add(ans,(f[i][1]+f[i][2])%P+f[i][3]);
		}
		
		cout<<ans<<endl;
		
		return 0;
	}
   ```
---

- 解法 $2$：

  $$\rm{step\ 1}$$
  
  该部分也是 Hard version 的重要部分。

  看到编号最大不超过 $3$，容易想到先预处理出编号为 $1$ 的有 $i$ 个，编号为 $2$ 的有 $j$ 个，编号为 $3$ 的有 $k$ 个时，有多少方案使得相邻两首歌的编号不同，记为 $s_{i,j,k}$。

  但是 $s$ 不方便求出，考虑 DP，设 $g_{i,j,k,p}$ 为编号为 $1$ 的有 $i$ 个，编号为 $2$ 的有 $j$ 个，编号为 $3$ 的有 $k$ 个且末尾（第 $i+j+k$ 位）编号为 $p$ 时，有多少种方案使得相邻的两首歌编号不同。$s_{i,j,k}$ 即为 

  $$(g_{i,j,k,0}+g_{i,j,k,1}+g_{i,j,k,2})\times i!\times j!\times k!$$
  
  初始值：$g_{1,0,0,1}=g_{0,1,0,2}=g_{0,0,1,3}=1$。

  考虑一个状态能由那些状态转移过来较为繁琐，反之我们考虑一个状态能向哪些状态转移：
  
  $$g_{i,j,k,1}\to g_{i,j+1,k,2},g_{i,j,k+1,3}$$
  $$g_{i,j,k,2}\to g_{i+1,j,k,1},g_{i,j,k+1,3}$$
  $$g_{i,j,k,3}\to g_{i+1,j,k,1},g_{i,j+1,k,2}$$
  
  时间复杂度 $O(buc_1\times buc_2\times buc_3)=O(\frac{n}{3}^3)=O(\frac{n^3}{27})$。


  ```cpp
	g[1][0][0][1]=g[0][1][0][2]=g[0][0][1][3]=1;
	for(int i=0;i<=buc[1];i++)
		for(int j=0;j<=buc[2];j++)
			for(int k=0;k<=buc[3];k++){
				add(g[i+1][j][k][1],g[i][j][k][2]+g[i][j][k][3]);
				add(g[i][j+1][k][2],g[i][j][k][1]+g[i][j][k][3]);
				add(g[i][j][k+1][3],g[i][j][k][1]+g[i][j][k][2]);
				int arr=1ll*fc[i]*fc[j]%P*fc[k]%P;
				s[i][j][k]=1ll*((g[i][j][k][1]+g[i][j][k][2])%P+g[i][j][k][3])*arr%P;
			}
  ```

  $$\rm{step\ 2}$$
  
  有了 $s_{i,j,k}$，我们只需枚举所有可能的状态并计算即可，时间复杂度 $O(\frac{n^3}{27}+n2^n)=O(n2^n)$，如果精细实现能达到 $O(2^n)$。[代码链接](https://codeforces.ml/contest/1185/submission/77236411)。

---

追求更快更优秀的解法？点击 [Hard version](https://www.luogu.com.cn/blog/AlexWei/solution-cf1185g2)。

---

## 作者：LTb_ (赞：1)

是道中规中矩的状压dp

我们设$dp_{i,j}$（$i$是表示状态的二进制数）为组成“选了$i$所表示的几首歌，并且以编号为$j$的歌曲结尾的歌单”的方案数。

我们考虑枚举歌单状态$i$和结尾歌曲编号$j$，并枚举新加入歌单，加在歌单结尾，并且不包含在歌单$i$中的歌曲$k$，并设$x$为歌单$i$加入歌曲$k$后的状态表示（既```x=i|(1<<(k-1))```），易得出状态转移：```dp[x][j]+=dp[i][j];```

统计答案的话就是枚举状态，如果歌曲总长度等于$T$的话就累加答案。

代码：

```c++
#include <iostream>
using namespace std;
#define int long long
const int MOD=1e9+7;
int n,T;
int t[20],g[20];
int dp[1<<18][5];
int ans=0;

signed main()

{
	cin>>n>>T;
	for (int i=1;i<=n;i++)
		cin>>t[i]>>g[i];

	dp[0][0]=1;
	for (int i=0;i<(1<<n);i++){
		for (int j=0;j<=3;j++){
			for (int k=1;k<=n;k++){
				if (i&(1<<k-1) || g[k]==j) continue;
				dp[i|(1<<k-1)][g[k]]+=dp[i][j];
				dp[i|(1<<k-1)][g[k]]%=MOD;
			}
		}
	}

    //统计答案
	for (int i=1;i<(1<<n);i++){
		int cnt=0;
		for (int j=1;j<=n;j++)
			if (i&(1<<j-1)) cnt+=t[j];

		if (cnt==T){
			ans+=dp[i][1]+dp[i][2]+dp[i][3];
			ans%=MOD;
		}
	}

	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Enoch006 (赞：0)

同[困难版](https://www.luogu.com.cn/problem/CF1185G2)。

cf duel 到这个题，只能说，2600 虚高了。

考虑把原问题拆成两个问题：

1. 选出一个集合，使集合权值和为 $T$。
2. 对每一个集合计算其排列的方法。

注意到第二个问题只与每个编号的个数有关，因此，我们需要计算**定下每个编号的个数**，集合权值和为 $T$ 的方案数。

直接背包 DP 多记三维表每个编号选了几个即可，时间复杂度 $\mathcal{O}(n^5)$。由于是背包 DP，因此**考虑用 map 存下所有有值的地方**，这样常数很小，空间也不会爆。

第二个问题，已经知道了每个编号的个数，求相邻不能有相同的方案数。对于编号种类为 $1/2$，该问题十分容易，留给读者自己思考。

对于编号种类为 $3$ 种，考虑 DP，设 $g_{i,j,k,1/2/3}$ 表示选了 $i$ 个编号为 $1$，$j$ 个编号为 $2$，$k$ 个编号为 $3$ 的歌曲，最后一个选的是 $1/2/3$ 的方案数。转移也很好转移，**直接枚举上一个选的是什么，那么这一个就不能选他**，时间复杂度 $\mathcal{O(n^3)}$。

合并该问题，假设选了 $i$ 个编号为 $1$，$j$ 个编号为 $2$，$k$ 个编号为 $3$ 的歌曲，那么对于每个编号需要内部定序，因此答案为 $f_{T,i,j,k}\times g_{i,j,k,1/2/3}\times i!j!k!$。对于所有合法 $f_{T,i,j,k}$ 计算即可，时间复杂度 $\mathcal{O(n^3)}$。

代码：


```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 2555
#define maxn 55
#define inf 0x3f3f3f3f3f3f
#define mod 1000000007
#define msk cerr
using namespace std;
int T,n,m,ans;
int a[maxm],fac[maxm];
map<int,int>f[maxn][maxn][maxn];
int g[maxn][maxn][maxn][3];
int Ask(int x1,int x2,int x3){
    if(x1>x2)swap(x1,x2);if(x2>x3)swap(x2,x3);
    if(x1>x2)swap(x1,x2);if(x2>x3)swap(x2,x3);
    if(!x1&&!x2)return x3==1;
    if(!x1){
        int p=x3-x2;
        if(p==1)return 1*fac[x2]%mod*fac[x3]%mod;
        if(p==0)return 2*fac[x2]%mod*fac[x3]%mod;
        return 0;
    }
    int s=x1+x2+x3;
    return (g[x1][x2][x3][0]+g[x1][x2][x3][1]+g[x1][x2][x3][2])%mod*fac[x1]%mod*fac[x2]%mod*fac[x3]%mod;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    fac[0]=1;
    for(int i=1;i<=57;i++)fac[i]=fac[i-1]*i%mod;
    cin>>n>>m;f[0][0][0][0]=1;
    for(int i=1;i<=n;i++){
        int x,op;cin>>x>>op;
        // msk<<i<<"---------\n";
        for(int x1=i;x1>=0;x1--)
            for(int x2=i;x2>=0;x2--)
                for(int x3=i;x3>=0;x3--)
                    for(auto p:f[x1][x2][x3]){
                        // msk<<x1<<" "<<x2<<" "<<x3<<" "<<p.first<<" "<<p.second<<"\n";
                        int j=p.first;
                        if(j+x>m)break;
                        if(op==1)f[x1+1][x2][x3][j+x]=(f[x1+1][x2][x3][j+x]+f[x1][x2][x3][j]%mod)%mod;
                        if(op==2)f[x1][x2+1][x3][j+x]=(f[x1][x2+1][x3][j+x]+f[x1][x2][x3][j]%mod)%mod;
                        if(op==3)f[x1][x2][x3+1][j+x]=(f[x1][x2][x3+1][j+x]+f[x1][x2][x3][j]%mod)%mod;    
                    }
    } 
    g[1][0][0][0]=1;
    g[0][1][0][1]=1;
    g[0][0][1][2]=1;
    for(int i=2;i<=n;i++)
        for(int x=0;x<=i;x++)
            for(int y=0;y<=i;y++){
                int z=i-x-y;if(z<0)continue;
                if(x)g[x][y][z][0]=(g[x][y][z][0]+g[x-1][y][z][1]+g[x-1][y][z][2]%mod)%mod;
                if(y)g[x][y][z][1]=(g[x][y][z][1]+g[x][y-1][z][0]+g[x][y-1][z][2]%mod)%mod;
                if(z)g[x][y][z][2]=(g[x][y][z][2]+g[x][y][z-1][0]+g[x][y][z-1][1]%mod)%mod;
            }
    for(int x1=0;x1<=n;x1++)
        for(int x2=0;x2<=n;x2++)
            for(int x3=0;x3<=n;x3++)
                if(f[x1][x2][x3][m]){
                    // msk<<x1<<" "<<x2<<" "<<x3<<" "<<m<<"\n";
                    ans=(ans+f[x1][x2][x3][m]%mod*Ask(x1,x2,x3))%mod;
                }
    cout<<ans;
    return 0;
}
```

---

