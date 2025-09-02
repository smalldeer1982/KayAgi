# Vlad and the Nice Paths (easy version)

## 题目描述

This is an easy version of the problem, it differs from the hard one only by constraints on $ n $ and $ k $ .

Vlad found a row of $ n $ tiles and the integer $ k $ . The tiles are indexed from left to right and the $ i $ -th tile has the color $ c_i $ . After a little thought, he decided what to do with it.

You can start from any tile and jump to any number of tiles right, forming the path $ p $ . Let's call the path $ p $ of length $ m $ nice if:

- $ p $ can be divided into blocks of length exactly $ k $ , that is, $ m $ is divisible by $ k $ ;
- $ c_{p_1} = c_{p_2} = \ldots = c_{p_k} $ ;
- $ c_{p_{k+1}} = c_{p_{k+2}} = \ldots = c_{p_{2k}} $ ;
- $ \ldots $
- $ c_{p_{m-k+1}} = c_{p_{m-k+2}} = \ldots = c_{p_{m}} $ ;

Your task is to find the number of nice paths of maximum length. Since this number may be too large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first sample, it is impossible to make a nice path with a length greater than $ 0 $ .

In the second sample, we are interested in the following paths:

- $ 1 \rightarrow 3 \rightarrow 4 \rightarrow 5 $
- $ 2 \rightarrow 4 \rightarrow 5 \rightarrow 7 $
- $ 1 \rightarrow 3 \rightarrow 5 \rightarrow 7 $
- $ 1 \rightarrow 3 \rightarrow 4 \rightarrow 7 $

In the third example, any path of length $ 8 $ is nice.

## 样例 #1

### 输入

```
5
5 2
1 2 3 4 5
7 2
1 3 1 3 3 1 3
11 4
1 1 1 1 1 1 1 1 1 1 1
5 2
1 1 2 2 2
5 1
1 2 3 4 5```

### 输出

```
1
4
165
3
1```

# 题解

## 作者：IGA_Indigo (赞：5)

## 题目大意
一个叫 Vlad 的人找到了 $n$ 块瓦片（也不知道为什么翻译成了跳粉丝这么抽象的设定），这几块瓦片有不同的颜色，要求找到一个好的序列满足题目中所给的颜色要求，问最长的好的序列有几种情况。
## 大体思路
看到这个题先是想到的简单而暴力的 $O(n^3)$ 做法，就是设定 $f[i][j]$ 为处理前 $i$ 个人，选了 $j$ 个人的最大值。

状态转移方程（朴素）：
-  如果 $\tt j\bmod\tt k==1$ ，$\tt f[i][j]=\sum^{i-1}_{k=1}f[i][j-1]$，不要求颜色一致。

- 如果不等于 $\tt 1$，$\tt f[i][j]=\sum^{i-1}_{k=1}f[i][j-1]\times (c[k]==c[i])$.

这种朴素的方法我们就一笔带过了，但这种方法已经足够 A 掉这道题了，但是很明显在累加的时候太费时间了，我们不难想出可以用组合数的方法来优化一下。

首先先用 $zh[i][j]$ 数组存 $C_j^i$ 的组合数，就是一个杨辉三角，然后开始每一组的 DP。
### 状态设置
$f[i]$ 表示以 $i$ 个数的为最后一个数，考虑完前 $i$ 个数的最长长度，他要问的个数我们再定义一个 $fs[i]$ 代表长度为 $f[i]$ 时的可能方案数。
### 状态转移
设第 $j+1$ 个元素前面有 $d$ 个跟 $c[i]$ 相同颜色的瓦片，所以我们得到 $f$ 和 $fs$ 的转移方程：

因为如果 $j+1$ 到 $i$ 和 $c[i]$ 相同的颜色大于 $k$ 就可以转移，所以：

- 如果 $f[j]+k>f[i]$，说明 $f[i]$ 可以更新，我们就能写出：

	$f[i]=f[j]+k$.
    
    $fs[i]=fs[j]\times zh[d-1][k-1]$ .
    
- 如果 $f[j]+k==f[i]$，说明情况是一样的，他们可以加在一起，就有：

   $fs[i]=fs[i]+fs[j]\times zh[d-1][k-1]$.
### 答案输出
枚举每个 $f[i]$，求出最大的 $f[i]$，然后存他的方案数 $g[i]$，最后输出就行。
### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[5005],fs[5005];
long long c[5005];//输入的粉丝颜色 
long long zh[5005][5005];//C(i,j)组合数预处理 
int main(){
	int t;
	cin>>t;
	zh[0][0]=1;
	for(int i=1;i<=5000;i++){
		zh[i][0]=1;
		for(int j=1;j<=i;j++){
			zh[i][j]=(zh[i-1][j]+zh[i-1][j-1])%1000000007;//C(n,m)=C(n-1,m-1)+C(n,m-1) 
		}
	}//将组合数预处理出来 
	while(t--){
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			f[i]=0;
			fs[i]=0;
		}//清零数组
		for(int i=1;i<=n;i++){
			cin>>c[i];
		}
		fs[0]=1;//初始化 
		for(int i=1;i<=n;i++){
			int d=1;//和i一个颜色的有几个
			for(int j=i-1;j>=0;j--){
				if(j!=i-1&&c[j+1]==c[i]){//因为每一个f[i]和g[i]都是求j+1~i之间至少有k个颜色c[i]，所以就有了这里的抽象代码 
					d++;//如果和c[i]相等就++ 
				}
				if(d<k){
					continue ;
				}//不行就换一个 
				if(f[j]+k>f[i]){
					f[i]=(f[j]+k)%1000000007;
					fs[i]=(fs[j]*zh[d-1][k-1])%1000000007;
				}//比f[i]大，可以更新的情况，就更新一下 
				else if(f[j]+k==f[i]){
					fs[i]=(fs[i]+fs[j]*zh[d-1][k-1])%1000000007;
				}//如果正好是f[i]，那就加上就行了 
			}
		}
		long long maxx=0,ans=0;
		for(int i=0;i<=n;i++){
			if(f[i]>maxx){
				maxx=f[i];
				ans=fs[i];
			}
			else if(f[i]==maxx){
				ans=(ans+fs[i])%1000000007;
			}
		}//找出最大的，最后输出他的方案数 
		cout<<ans%1000000007<<'\n';
	}
	return 0;
}
```

---

## 作者：FReQuenter (赞：2)

考虑 DP。

设 $f_{i,j}$ 表示在前 $i$ 个数中选择了 $j$ 个数的最大方案数。

转移可以考虑枚举分段点 $k$，分两种情况考虑：

1. $i\text{ mod }K=1$ 时，到了新的一个阶段，则 $1$～$k$ 所有的 $f_{k,j-1}$ 都可以产生贡献；

2. 否则，只有 $a_i=a_k$ 时，$f_{k,j-1}$ 可以产生贡献。

初值就是 $f$ 全为 $0$，除 $f_{0,0}=1$ 以外。

代码中注意 DP 枚举的范围和答案统计：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
#define MAXN 105
using namespace std;
int t,n,m,ans,a[MAXN],f[MAXN][MAXN];
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i]; 
			for(int j=0;j<=n;j++) f[i][j]=0;
		}
		f[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				for(int k=0;k<i;k++){
					if(j%m==1) f[i][j]+=f[k][j-1],f[i][j]%=mod;
					else if(k) f[i][j]+=(a[i]==a[k])*f[k][j-1],f[i][j]%=mod;
				}
			}
		}
//		for(int i=1;i<=n;i++){
//			for(int j=1;j<=i;j++) cout<<f[i][j]<<' ';
//			cout<<endl;
//		}
		for(int i=n;i>=1;i--){
			if(i%m==0){
				ans=0;
				for(int j=1;j<=n;j++) ans+=f[j][i],ans%=mod;
				if(ans){
					cout<<ans<<'\n';
					goto nt; 
				} 
			}
		}
		cout<<1<<'\n';
		nt:;
	}
}
```

---

## 作者：ifffer_2137 (赞：1)

easy version 比较水，~~于是只做了 easy version~~。
### 题意
Ly 有 $n$ 个粉丝，和一个整数 $k$，第 $i$ 个粉丝的颜色是 $c_i$。

Ly 想观看他的粉丝对他的膜拜程度，他会从任意一个粉丝开始，每次向后跳到任意一个粉丝，并且随时可以终止，这样形成了一个路径。

我们定义一个长度为 $m$ 的路径 $p$ 是好的路径，有以下条件：

- $m$ 是 $k$ 的倍数。
- $c_{p_1}=c_{p_2}=\ldots=c_{p_k}$
- $c_{p_{k+1}}=c_{p_{k+2}}=\ldots=c_{p_{2k}}$
- $\ldots$
- $c_{p_{m-k+1}}=c_{p_{m-k+2}}=\ldots=c_{p_m}$

你的任务是找出最长的好路径的数量,答案对 $10^9+7$ 取模。
### 分析
看到可以 $\mathcal O(n^3)$ 的数据范围，基本可以暴力 DP 随便做了。

显然从前往后跳，需要我们从后往前转移。这题的 DP 状态容易想到，定义状态：$f_{i,j}$ 表示第 $i$ 个位置往后走 $j\times k$ 步的合法方案数。

然后转移也就简单了：
$$f_{i,j}=\sum_{i \leq p \leq n} \dbinom{cnt(i,p)-1}{k-1}f_{p+1,j-1}$$

其中 $cnt(i,p)$ 表示第 $i$ 位到第 $p$ 位出现多少次 $c_i$ 这个颜色。

预处理一下组合数，做到 $\mathcal O(n^3)$ 了。

最后统计答案的时候加一下就行，不理解的看代码吧。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=1e2+5;
const int mod=1e9+7;
int T;
int n,k;
int ans;
int a[maxn];
int f[maxn][maxn];
int fac[maxn],inv[maxn];
int pw(int a,int x){
	int s=1;
	while(x){
		if(x&1) s=s*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return s%mod;
}
void init(){
	fac[0]=1;
	for(int i=1;i<maxn;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[maxn-1]=pw(fac[maxn-1],mod-2);
	for(int i=maxn-2;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}
int C(int n,int m){
	if(n<m) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
	cin.tie(0),cout.tie(0);
	init();
	T=read();
	while(T--){
		for(int i=0;i<=n;i++){
			for(int j=0;j<=n;j++){
				f[i][j]=0;
			}
		}
		n=read(),k=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		for(int i=1;i<=n;i++){
			int cnt=0;
			for(int j=i+1;j<=n;j++) if(a[j]==a[i]) cnt++;
			f[i][1]=C(cnt,k-1);
		}
		for(int i=n;i>=1;i--){
			for(int j=2;i+j*k-1<=n;j++){
				int cnt=0;
				for(int p=i;p+(j-1)*k-1<=n;p++){
					if(a[p]==a[i]) cnt++;
					if(cnt>=k) f[i][j]=(f[i][j]+C(cnt-1,k-1)*f[p+1][j-1]%mod)%mod;
				}
			}
		}
		ans=1;
		for(int i=1;i*k<=n;i++){
			int res=0;
			for(int j=1;j<=n;j++){
				res=(res+f[j][i])%mod;
			}
			if(res) ans=res;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Gordon_Song (赞：1)

## 前置知识

简单 dp

## 思路


dp 典题。设 $dp_{i,j}$ 表示最后一个数在 $i$，数列长度为 $j$ 的方案数。

很容易推出转移方程：$dp_{i,j} = \begin{cases} \sum_{0 \leq k \leq i-1} dp_{k,j-1} & j \equiv 1 \pmod m\\ \sum_{0 \leq k \leq i-1 \land a_k=a_i} dp_{k,j-1} &otherwise \end{cases}$

这样答案就容易统计了。

## 代码

```cpp
int T;
int n,m;
int ans;
int dp[1001][1001];
int a[1001];
const int mod=1e9+7;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			for(int j=0;j<=n;j++)dp[i][j]=0;
		}
		dp[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				for(int k=0;k<i;k++){
					if(j%m==1){
						dp[i][j]+=dp[k][j-1];dp[i][j]%=mod;
					}else{
						if(k>0&&a[k]==a[i]){
							dp[i][j]+=dp[k][j-1];
							dp[i][j]%=mod;
						}
					}
				}
			}
		}
		bool fl=true;
		for(int j=n/m*m;j>=m;j-=m){
			int ans=0;
			for(int i=1;i<=n;i++){
				ans+=dp[i][j];ans%=mod;
			}
			if(ans>0){
				printf("%d\n",ans);
				fl=false;break;
			}
		}
		if(!fl)continue;
		printf("1\n");
	}
}
```


---

## 作者：SegTree (赞：1)

朴素。考虑 $dp_{i,j}$ 表示以第 $i$ 个数结尾，其中第 $i$ 个数在它的所属块（$k$ 个分割成的块）内的第 $j$ 个的最长长度。$dp2_{i,j}$ 表示方案数。

对于 $j\ne 1$ 有 $dp_{i,j}=\max_{l<i,c_l=c_i} dp_{l,j-1}+1$，$dp2_{i,j}=\sum_{l<i,c_l=c_i}[dp_{l,j-1}=dp_{i,j}-1]\cdot dp2_{l,j-1}$。

对于 $j=1$ 有 $dp_{i,1}=\max_{l<i}dp_{l,k}+1$，$dp2_{i,j}=\sum_{l<i}[dp_{l,k}=dp_{i,1}-1]\cdot dp2_{l,k}$。

直接 $\mathcal{O}(n^3)$ 暴力转移即可。

[Record](https://codeforces.com/contest/1811/submission/228398543)。

---

## 作者：sunkuangzheng (赞：1)

**【题目分析】**

最优方案计数题，我们得先知道最优方案的大小。设 $f_i$ 表示只考虑前 $i$ 个颜色**且强制以 $i$ 结尾**的最长长度，显然有转移方程：$f_i = \max\limits_{j=1}^i\{f_j + k\}$，其中 $j$ 需要满足的条件是 $j+1 \sim i$ 之间至少有 $k$ 个颜色 $c_i$。

考虑如何统计方案数量。设 $g_i$ 表示只考虑前 $i$ 个颜色且强制以 $i$ 结尾的最长长度数量，枚举 $j$。设当前 $j+1 \sim i$ 之间有 $p$ 个 $c_i$ 颜色。

- 如果当前的 $j$ 能够更新 $f_i$，即 $f_j + k > f_i$，那么我们需要从 $1 \sim j$ 中找出长度为 $f_j$ 的序列，这一步有 $g_j$ 种方法；还需要从 $j+1 \sim n$ 种找出 $k$ 个颜色为 $c_i$ 的数字，**注意 $i$ 位置是钦定要选的**，所以我们的方案数是 $\dbinom{p-1}{k-1}$，所以 $g_i = \dbinom{p-1}{k-1}g_j $。

- 如果当前的 $j$ 得到的答案恰好是 $f_i$，那么我们需要让 $f_i$ 加上 $j$ 的贡献。类似的，这里 $g_i \gets g_i + \dbinom{p-1}{k-1}g_j$。

我们先预处理组合数，然后枚举 $i,j$ 进行转移。两部分的时间复杂度都是 $\mathcal O(n^2)$，可以通过本题和 G2。

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e3+5,mod = 1e9+7;
int t,n,f[maxn],g[maxn],c[maxn],k,h[maxn][maxn];
signed main(){
    cin >> t,h[0][0] = 1;
    for(int i = 1,j;i <= 5000;i ++)
        for(j = h[i][0] = 1;j <= i;j ++) h[i][j] = (h[i-1][j] + h[i-1][j-1]) % mod;
    while(t --){
        cin >> n >> k,g[0] = 1;
        for(int i = 1;i <= n;i ++){
            cin >> c[i],f[i] = 0,g[i] = 0;
            if(k == 1) f[i] = 1;
            for(int j = i-1,tp = 1;j >= 0;tp += (c[j --] == c[i])){
                if(tp < k) continue;int d = j;
                if(f[d] + k > f[i]) f[i] = f[d] + k,g[i] = g[d] * h[tp-1][k-1] % mod;
                else if(f[d] + k == f[i]) g[i] = (g[i] + g[d] * h[tp-1][k-1]) % mod;
            }
        }int mx = 0,ans = 0; 
        for(int i = 0;i <= n;i ++) if(f[i] > mx) mx = f[i],ans = g[i]; else if(f[i] == mx) ans = (ans + g[i]) % mod;
        cout << ans << "\n"; 
    }
}
```

---

## 作者：N1K_J (赞：0)

不妨设 $dp_i$ 是前 $i$ 个最长能多长，$sum_i$ 是方案数。

我们考虑从 $dp_{j < i}$ 转移到 $dp_i$。

注意到能转移相当于 $c_{j+1},c_{j+2},\cdots,c_i$ 中有 $D \ge k$ 个和 $c_i$ 相同的数，此时 $dp_i$ 可以为 $dp_j+k$。

如果 $dp_i < dp_j$，令 $dp_i \leftarrow dp_j$，$sum_i \leftarrow sum_j \cdot C_{D-1}^{k-1}$，即在除了 $c_i$ 之外的 $D-1$ 个与其相等的中选 $k-1$ 个来构成这 $k$ 个相同的。

如果 $dp_i = dp_j$，令 $dp_i \leftarrow dp_i+dp_j$，$sum_i \leftarrow sum_i+sum_j \cdot C_{D-1}^{k-1}$，理由同上。

若均不满足，不用更新。

整体复杂度 $O(n^2)$。

[Code](https://codeforces.com/contest/1811/submission/280053902)

---

## 作者：729hao (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1811G1)

比赛中教练选用的是[困难版](https://www.luogu.com.cn/problem/CF1811G2)，但本蒟蒻只会 $O(N^3)$ 做法


------------
## 判断无解
通过分析样例可知，无解时输出 $1$。

判断无解的方法也很简单，只要没有任意颜色的个数不小于 $k$ 即为无解。

------------
## 思路
当看到
> It is guaranteed that the sum of $n^3$ over all test cases does not exceed $5⋅10^6$ .

$\text{\footnotesize{（翻译：保证所有测试用例的}}$ $\footnotesize n^3$ $\text{\footnotesize{之和不超过}}$ $\footnotesize 5⋅10^6$ $\text{\footnotesize{。）}}$

时，可知这道题 $O(N^3)$ 做法能过。

------------
我们可以把 $f_{i,l}$ 定义为前 $i$ 个数中已配对了 $l$ 组相同的 $c$，那么对于每一个大于 $i$ 的数 $j$，如果 $i$ 到 $j$ 之间有 $s$ 个数为 $c_j$，且 $s \ge k$，都有状转方程：
$$
f_{i,l}= \sum_{j = i+1}^{n} (f_{j,l-1}\times C_s^{k-1})
$$
其中 $C_n^m$ 为组合数，表示从 $n$ 个物品中选出 $m$ 个物品放一起的方案数。

$s$ 的求法很简单，维护每个颜色的前缀和即可。

这个时候就有人要问了：组合数怎么求？

------------
## 杨辉三角
杨辉三角是一个有规律的数字三角形，它的第 $i$ 行有 $i$ 个数，这些数满足下规律：
$$
f_{i,j}=\begin{cases}
1&j=1\lor j=i\\
f_{i-1,j}+f_{i-1,j+1}&j\ne 1\land j\ne i
\end{cases}
$$
其中 $f_{i,j}$ 表示第 $i$ 行第 $j$ 的数。

这个时候就又有人要问了：这个东西跟组合数有什么关系？

$\text{\textbf {杨辉三角与组合数一一对应：}}$
$\color{red}C_{n,m}=f_{n+1,m+1}$

那么，我们就可以预处理出所有的组合数了。
```cpp
void Yang(){
	for(int i=0;i<=100;i++){
		for(int j=0;j<=i;j++){
			if(j==0||j==i)C[i][j]=1ll;
			else{
				C[i][j]=C[i-1][j-1]+C[i-1][j];
				C[i][j]%=Mod;
			}
		}
	}
}
```

------------
## 最长路径长
接下来，还有一个问题，如何求最长路径的长度？

贪心：$c_{p_k},c_{p_{2k}},\cdots,c_{p_m}$ 越小越好。

~~不严谨的~~$\textup{\textbf{证明}}$：  
设存在满足要求的序列 $c1$，其中有 $c1_{p_{tk}}>c_{p_{tk}}$。  
如果 $c1_{p_{tk}}\le c_{p_{(t+1)k}}$，则 $c1$ 与 $c$ 结果一样；  
如果 $c1_{p_{tk}}> c_{p_{(t+1)k}}$，显然 $c1$ 不如 $c$ 更优。

我们可以在计算前缀和时顺便计算最长路径长。
```cpp
for(int i=1;i<=n;i++){
	scanf("%d",&c[i]);
	for(int j=1;j<=n;j++){//计算前缀和 
		if(c[i]==j)ps[i][j]=ps[i-1][j]+1;
		else ps[i][j]=ps[i-1][j];
	}
	if(ps[i][c[i]]-ps[Line][c[i]]==k){//如果在Line~i的范围中有刚好k个c[i] 
		Line=i;
		p[++P]=i;
		//P表示最长的长度为P*k 
		//p[i]=j表示从j开始往后的数才有可能成为c[p[t*k]] 
	}
}
```

于是这道题就做完啦！
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Mod=1000000007;
int T,n,k,c[102],ps[102][102],P,p[102];
long long f[102][102],C[102][102],ans;
void Yang(){
	for(int i=0;i<=100;i++){
		for(int j=0;j<=i;j++){
			if(j==0||j==i)C[i][j]=1ll;
			else{
				C[i][j]=C[i-1][j-1]+C[i-1][j];
				C[i][j]%=Mod;
			}
		}
	}
}
int main(){
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
	scanf("%d",&T);
	Yang();
	f[0][0]=1;
	int Line;
	while(T--){
		scanf("%d %d",&n,&k);
		Line=P=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&c[i]);
			for(int j=1;j<=n;j++){
				if(c[i]==j)ps[i][j]=ps[i-1][j]+1;
				else ps[i][j]=ps[i-1][j];
			}
			if(ps[i][c[i]]-ps[Line][c[i]]==k){
				Line=i;
				p[++P]=i;
			}
		}
		if(P==0){//P等于0时，说明没有任意一种颜色总和不小于k 
			printf("1\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=P;j++){
				f[i][j]=0;
			}
		}
		ans=0ll;
		for(int l=1;l<=P;l++){
			for(int i=p[l];i<=n;i++){
				for(int j=p[l-1];j<=i-k;j++){
					if(ps[i][c[i]]-ps[j][c[i]]>=k){
						f[i][l]=(f[i][l]+f[j][l-1]*C[ps[i-1][c[i]]-ps[j][c[i]]][k-1]%Mod)%Mod;
					}
				}
			}
		}
		for(int i=p[P];i<=n;i++){//统计答案
			ans+=f[i][P];
			ans%=Mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
} 

```

---

## 作者：FireRain (赞：0)

# 思路

经典 DP。

定义 $dp_{i,j}$ 表示在前 $i$ 个瓷砖中选出 $j$ 个，且最后一个选出的位置是 $i$ 的方案数。

当考虑 $i$ 时，如果 $j \bmod k = 1$，说明 $i$ 是一段的起点，可以不受任何限制；否则上一个被选的颜色一定是与 $i$ 相同的。因此得到状态转移方程：

$$
dp_{i,j} = \left\{\begin{matrix}
\sum_{p = 1}^{p < i}{dp_{p,j - 1}} & (j \bmod k = 1)\\
\sum_{p = 1}^{p < i \wedge c_p = c_i}{dp_{p,j - 1}} & (\operatorname{otherwise})
\end{matrix}\right.
$$

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define Add(a,b) (((a) + (b)) % mod)

using namespace std;

const int N = 110,mod = 1e9 + 7;
int n,k;
int arr[N],dp[N][N],f[N][N],s[N][N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

inline void solve(){
    dp[0][0] = s[0][0] = 1;
    n = read();
    k = read();
    for (re int i = 1;i <= n;i++) arr[i] = read();
    for (re int i = 1;i <= n;i++){
        for (re int j = 0;j <= n;j++) dp[i][j] = s[i][j] = 0;
    }
    for (re int i = 1;i <= n;i++){
        for (re int j = 0;j <= i;j++){
            if (j % k == 1) dp[i][j] = Add(dp[i][j],s[i - 1][j - 1]);
            else if (j){
                for (re int p = 1;p < i;p++){
                    if (arr[p] == arr[i]) dp[i][j] = Add(dp[i][j],dp[p][j - 1]);
                }
            }
            s[i][j] = Add(s[i - 1][j],dp[i][j]);
        }
    }
    for (re int j = n;j;j--){
        if (j % k == 0){
            int ans = 0;
            for (re int i = 1;i <= n;i++) ans = Add(ans,dp[i][j]);
            if (ans){
                printf("%d\n",ans);
                return;
            }
        }
    }
    puts("1");
}

int main(){
    int T;
    T = read();
    while (T--) solve();
    return 0;
}
```

---

## 作者：ncwzdlsd (赞：0)

序列问题，考虑 DP。

设计状态 $f(i,j)$ 表示当前选了 $i$ 个点，最后一个点颜色为 $j$ 的方案数。

当 $a_i\bmod k=1$ 时，该点的颜色可以任意选择，否则必须跟上一个点颜色相同。对于每个点，我们考虑它的不同颜色转移即可。

注意到对于 $a_i\bmod k=1$ 的点，它的转移会退化成 $O(n^3)$ 的。我们用 $g_i$ 记录第 $i$ 个完整的段的方案数即可优化转移。

注意转移时要从大到小枚举子序列长度，否则可能会出现小长度的答案重复更新大长度答案的情况。

维护两个标记：

- $c1_i$ 表示编号为 $i$ 的一个长度为 $k$ 的子序列是否统计完毕。

- $c2$ 维护当前子序列的颜色。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod=1e9+7,maxn=5005;
int c[maxn],g[maxn],f[maxn][maxn];
bool c2[maxn][maxn],c1[maxn];

void solve()
{
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>c[i],g[i]=0,c1[i]=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=0,c2[i][j]=0;
    f[0][0]=1,g[0]=1,c2[0][0]=1,c1[0]=1;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j;j--)
        {
            if(j%k==1)
            {
                if(c1[j/k]) c2[j][c[i]]=1,f[j][c[i]]+=g[j/k],f[j][c[i]]%=mod;
            }
            else if(c2[j-1][c[i]]) c2[j][c[i]]=1,f[j][c[i]]+=f[j-1][c[i]],f[j][c[i]]%=mod;
            if(!(j%k)&&c2[j][c[i]]) c1[j/k]=1,g[j/k]+=f[j-1][c[i]],g[j/k]%=mod;
        }
    for(int i=n/k;i>=0;i--) if(c1[i]) {cout<<g[i]<<'\n';break;}
}

signed main()
{
    int t;cin>>t;
    while(t--) solve();
	return 0;
}
```

---

## 作者：__vector__ (赞：0)

纪念一下第一次不看题解，不看算法标签做出 CF 评分 2200。   
虽然实际上最多提高组 T1。  
## G1 做法  
G2 做法只需要在 G1 基础上稍微修改。  

很自然想到设 $dp_{i,j}$ 表示第 $i$ 位是路径的第 $j$ 个点的方案数。  

想一下如何转移，对于 $i = 1$，显然方案数是 $1$。  
对于 $i \ge  2$，分一下类：  
1. 若 $i \equiv 1 \pmod k$，那么对于所有 $j \le i-1$，从 $dp_{j,i-1}$ 转移，颜色不用管。   
2. 否则，还要在情况 1 的基础上加上一条限制：第 $i$ 个点与 $j$ 点颜色相同。  

主要思想就是这个。  

关于怎么统计之前符合某些条件的状态答案综合，这个开个数组记一下就行了，都把 dp 设计出来了，这么简单的想必都会。  

剩下的就是从大到小枚举 $m$，每次跑一遍 dp，找到答案就终止。  

dp 复杂度 $O(n^2)$。  

枚举最劣复杂度 $O(n)$。 

总复杂度 $O(n^3)$。  
 

## Code  
```cpp
// LUOGU_RID: 107120197
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define REP(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back()
#define mkpr make_pair
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int maxn = 5005;
typedef long long ll;
const ll mod = 1e9 + 7;
int t;
int n, k;
int c[maxn];
ll dp[maxn][maxn];  // 第 i 位状态为 j
ll sum[maxn][maxn]; // 颜色为 i，状态为 j，dp 值和
ll sum2[maxn];      // 状态为 i dp 总和
bool dp2[maxn][maxn],sum21[maxn][maxn],sum22[maxn];
inline int turn(int status)
{
    if (status % k == 0)
        return k;
    return status % k;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &k);
        FOR(i, 1, n)
        {
            scanf("%d", &c[i]);
        }
        ll ans = 0;
        FOR(i, 1, n)
        {
            dp2[i][1]=1;
            FOR(j, 2, n)
            {
                if (turn(j) == 1)
                {
                    dp2[i][j]|=sum22[j-1];
                }
                else
                {
                    dp2[i][j]|=sum21[c[i]][j-1];
                }
            }
            FOR(j, 1, n)
            {
                sum22[j] |= dp2[i][j];
                sum21[c[i]][j] |= dp2[i][j];
            }
        }
        int blocks = n / k;
        bool isansoutputed=0;
        for (int m = blocks * k; m > 0; m -= k)
        {
            bool flag = 0;
            FOR(i, 1, n)
            {
                if (dp2[i][m])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
             //   printf("m = %d\n", m);
                FOR(i, 1, n)
                {
                    dp[i][1] = 1;
                    FOR(j, 2, m)
                    {
                        if (turn(j) == 1)
                        {
                            dp[i][j] += sum2[j - 1];
                        }
                        else
                        {
                            dp[i][j] += sum[c[i]][j - 1];
                        }
                        dp[i][j] %= mod;
                    }
                    FOR(j, 1, m)
                    {
                        sum2[j] += dp[i][j];
                        sum2[j]%=mod;
                        sum[c[i]][j] += dp[i][j];
                        sum[c[i]][j] %= mod;
                    }
                }
                FOR(i, 1, n)
                {
                    ans += dp[i][m];
                    ans%=mod;
                    FOR(j, 1, n)
                    {
                        //    printf("dp[%d][%d] = %d\n",i,j,dp[i][j]);
                        dp[i][j] = 0;
                        sum[i][j] = 0;
                    }
                    sum2[i] = 0;
                }
                isansoutputed=1;
                break;
            }
        }
        if (!isansoutputed)
            ans++;
        printf("%lld\n", ans % mod);
        FOR(i, 1, n)
        {
            sum2[i] = sum22[i]=0;
            FOR(j, 1, n)
            {
                dp[i][j] = dp2[i][j]=0;
                sum[i][j] = sum21[i][j]=0;
            }
        }
    }
    return 0;
}
```


---

