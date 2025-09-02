# Bit Game (Hard Version)

## 题目描述

这是该问题的困难版本。唯一的区别在于，在本版本中你需要输出 Bob 获胜的游戏方案数，其中每堆石子的数量并不是固定的。你必须同时解决两个版本才能进行 hack。

Alice 和 Bob 正在玩一个熟悉的游戏，他们轮流从 $n$ 堆石子中取石子。最初，第 $i$ 堆有 $x_i$ 个石子，并且该堆有一个对应的值 $a_i$。一名玩家可以从第 $i$ 堆中取走 $d$ 个石子，当且仅当满足以下两个条件：

- $1 \le d \le a_i$，且
- $x \,\&\, d = d$，其中 $x$ 是当前第 $i$ 堆的石子数，$\&$ 表示[按位与运算](https://en.wikipedia.org/wiki/Bitwise_operation#AND)。

无法进行操作的玩家判负，Alice 先手。

你已知每堆的 $a_i$，但每堆的石子数 $x_i$ 尚未确定。对于第 $i$ 堆，$x_i$ 可以是 $1$ 到 $b_i$ 之间的任意整数（包含两端）。也就是说，你可以选择一个数组 $x_1, x_2, \ldots, x_n$，使得对所有堆都满足 $1 \le x_i \le b_i$。

你的任务是统计在双方都采取最优策略的情况下，Bob 获胜的游戏方案数。若任意一堆的石子数不同，则认为是不同的游戏方案，即 $x$ 数组中至少有一个位置不同。

由于答案可能非常大，请输出结果对 $10^9 + 7$ 取模。

## 说明/提示

在第一个测试用例中，无论 $x_2$ 和 $x_3$ 取什么值，第二堆和第三堆都只能被操作一次，然后就无法再取石子了。如果 $x_1 = 2$，那么无法从该堆取石子，因此最后一步由 Bob 完成。如果 $x_1 = 1$ 或 $x_1 = 3$，则该堆可以被操作一次，因此最后一步由 Alice 完成。所以当 $x = [2, 1, 1]$、$x = [2, 1, 2]$、$x = [2, 2, 1]$ 或 $x = [2, 2, 2]$ 时，Bob 获胜。

在第二个测试用例中，当 $x_1 = 14$ 或 $x_1 = 30$ 时，Bob 可以通过取走 $14 - k$ 个石子获胜，其中 $k$ 是 Alice 在她回合取走的石子数。当 $x_1 = 16$ 或 $x_1 = 32$ 时，Alice 一开始就无法进行操作，因此 Bob 获胜。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
3
1 2 3
3 2 2
1
13
45
5
5 4 7 8 6
4 4 5 5 5
4
6 4 8 8
12 13 14 12
3
92856133 46637598 12345678
29384774 73775896 87654321
2
65 12
110 31
4
677810235 275091182 428565855 720629731
74522416 889934149 3394714 230851724```

### 输出

```
4
4
0
6552
722019507
541
665443265```

# 题解

## 作者：ForgotMe (赞：3)

难点在于会做 E1。

建议先阅读 E1 的题解：https://www.luogu.com.cn/article/nmcf3zw3

显然的数位 dp 题。首先根据 E1 的结论，容易看出 SG 函数的值域大小是 $\log V$ 级别的。只要能对于每一堆石子求出对于 $\forall 0\le k\le \log V$，有多少个 $x$ 满足 $1\le x\le b_i,\operatorname{SG}(a,x)=k$，最后做一个异或意义下的背包即可求出答案。

唯一的一个可能算难点的地方在于如何刻画新的 $a_2$。根据 E1 的调整方式，肯定是从高往低 dp，且一旦出现 $a$ 的第 $i$ 位是 $1$，$x$ 的第 $i$ 位是 $0$，那么后面 $a_2$ 的所有位都变成 $1$，这个可以通过记录一个 tag 放在 dp 状态里。

- $g(2^k-2)=0$，要求 $k\ge 1$。
- $g(2^k-1)=k$。
- $g(2^k)=k\oplus 1$。
- $g(2^k+1)=g(2^k+2)=...=g(2^{k+1}-3)=k+1$，要求 $k\ge 2$。

下一个就是如何快速得到 $g(a_2)$，观察这个 $g$，并不需要知道 $a_2$ 具体的值，只需要知道其最高位的 $1$ 的位置就可以得到其 $g$ 值。由于有前三种特殊情况，为了实现不那么答辩，设 $dp_{i,j,k,l,lim,w}$ 表示取到了第 $i$ 位，当前 $a_2$ 中有 $j$ 个 $1$，最高位的 $1$ 的位置在 $k$，$l$ 表示是否让后面 $a$ 的所有位都变成 $1$，$lim$ 表示 $x$ 当前位的取值限制（即要求其 $\le b_i$），$w$ 表示当前 $a_2$ 的最低位是 0/1。转移是简单的，模拟调整的过程即可。

最后如果 $j=1$ 说明是第三种情况，$j=k$ 说明是第二种情况，$j=k-1$ 且 $w=0$ 说明是第一种情况，否则是最后一种情况。

这个做法是 $\mathcal{O}(n\log^3 V)$ 的，显然有 2log 的做法，即不需要记录 $1$ 的个数，而是多加一个 tag 记录从 $a_2$ 的最高位开始当现在是否一直都是 $1$。但是其实现可能更加痛苦，所以我选择多记录一个信息。

扔个代码：
```cpp
const int mod=1e9+7;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
	return 1ll*x*y%mod;
}
inline int qkpow(int a,int b){
	if(b<0)return 0;
	int ans=1,base=a%mod;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[2000005],inv[2000005],Invn[600005];
inline int binom(int n,int m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[n]=qkpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
//	Invn[0]=Invn[1]=1;
//	for(int i=1;i<=200000;i++)Invn[i]=(LL)(mod-mod/i)*Invn[mod%i]%mod;
}
int t,n,A[10005],X[10005],dp[33][32][32][2][2][2],dp2[35],f[35],tmp[35];
inline void sg(int x,int d){
	memset(f,0,sizeof f);
	dp[31][0][0][0][1][0]=1;
	for(int i=31;i>=1;i--){
		for(int j=0;j<=30;j++){
			for(int k=j;k<=30;k++){
				for(int l=0;l<=1;l++){
					for(int lim=0;lim<=1;lim++){
						for(int l2=0;l2<=1;l2++){
							int v=dp[i][j][k][l][lim][l2];
							if(v){
								int x1=(x>>(i-1))&1,x2=(d>>(i-1))&1;
								int up=lim?x1:1;
								for(int nw=0;nw<=up;nw++){
									int nlim=lim&(nw==up);
									if(nw==0){
										if(x2){
											//0 1 
											dp[i-1][j][k][l|1][nlim][l2]=add(dp[i-1][j][k][l|1][nlim][l2],v);
										}else{
											//0 0
											dp[i-1][j][k][l][nlim][l2]=add(dp[i-1][j][k][l][nlim][l2],v);
										}
									}else{
										if(x2){
											//1 1
											dp[i-1][j+1][k+1][l][nlim][1]=add(dp[i-1][j+1][k+1][l][nlim][1],v);
										}else{
											//1 0
											if(l){
												//1 0 -->1 1
												dp[i-1][j+1][k+1][l][nlim][1]=add(dp[i-1][j+1][k+1][l][nlim][1],v);
											}else{
												//1 0 -->1 0
												if(!j){
													if(!k)dp[i-1][0][0][l][nlim][0]=add(dp[i-1][0][0][l][nlim][0],v);
												}
												else dp[i-1][j][k+1][l][nlim][0]=add(dp[i-1][j][k+1][l][nlim][0],v);
											}
										}
									}
								}
							} 
							dp[i][j][k][l][lim][l2]=0;
						}
					}
				}
			}
		}
	}
	for(int i=0;i<=30;i++){
		for(int j=0;j<=30;j++){
			for(int k=0;k<=1;k++){
				for(int lim=0;lim<=1;lim++){
					for(int w=0;w<=1;w++){
						int v=dp[0][i][j][k][lim][w];
						if(v){
							if(!i&&!j)f[0]=add(f[0],v);
							else{
								if(i==1)f[(j-1)^1]=add(f[(j-1)^1],v);
								else {
									if(i==j)f[j]=add(f[j],v);
									else if(i+1==j&&w==0)f[0]=add(f[0],v);
									else f[j]=add(f[j],v);
								}
							}
						}
						dp[0][i][j][k][lim][w]=0;
					}
				}
			}
		}
	}
	f[0]=dec(f[0],1);
	memset(tmp,0,sizeof tmp);
	for(int i=0;i<=31;i++){
		for(int j=0;j<=31;j++){
			tmp[i^j]=add(tmp[i^j],1ll*dp2[i]*f[j]%mod);
		}
	}
	for(int i=0;i<=31;i++)dp2[i]=tmp[i];
}
inline void solve(){
	memset(dp2,0,sizeof dp2);
	gi(n);
	for(int i=1;i<=n;i++)gi(A[i]);
	for(int i=1;i<=n;i++)gi(X[i]);
	dp2[0]=1;
	for(int i=1;i<=n;i++)sg(X[i],A[i]);
	pi(dp2[0]);
}
signed main(){
	srand(time(0));
	gi(t);
	while(t--)solve();
	return 0;
} 
```

---

## 作者：vegetable_king (赞：2)

[可能更好的阅读体验](https://yjh965.github.io/post/wei-liao-quan-wen-di-yi-duan-hua-xie-liao-pian-ti-jie/)

我寻思这种“一正常题非要爆改计数嗯堆难度结果整出一托答辩”不应该是模拟赛恰烂钱才能干的事吗，怎么扔 CF 了。真不如来做我们 [P11269 爆改版](https://www.luogu.com.cn/problem/T524402)。

考虑 E1 咋做。先考虑快速算出 $\textrm{SG}(a, x)$。如果直接打表你会寄。所以在函数的原本意义上先做一些操作。可以发现，我们只需要保留 $a$ 中 $x$ 上为 $1$ 的那些位，其他位的信息我们可以移动到那些位上。

假如 $a$ 中有一位为 $1$ 且 $x$ 中那一位为 $0$，那么我们可以将这位扔掉，并将 $a$ 在 $x$ 中更低的 $1$ 位上都赋为 $1$。那么 $a$ 只在 $x$ 中有值的位上有值，并且我们并不关心 $x$ 中有值的位具体是哪些，所以我们可以将其平移到最前面，那么 $x$ 就变为了 $2^k - 1$ 这样的数。更进一步的，我们可以将 $a$ 最高位之后的位都扔掉，那么新的 $x$ 最高位和 $a$ 的最高位相等，于是 $\textrm{SG}(a, x)$ 一定能被转化成 $\textrm{SG}(a', 2^k - 1)$，其中 $k$ 为 $a'$ 最高位，设其为 $G(a')$。

那么我们对 $G$ 打表，规律就显而易见了：我们有：

$$
G(n) = \begin{cases}
0 & n = 2^k - 2 \ (k > 0)\\
k \oplus 1 & n = 2^k\\
\lceil\log_2 n\rceil & \mathrm{otherwise}\\
\end{cases}
$$

那么我们就以 $O(n \log_2 v)$ 解决了 E1。

考虑解决 E2。由于上述结论，$\mathrm{SG}$ 值显然是 $O(\log_2 v)$ 的，那么我们只要算出每堆石子取到每种 $\mathrm{SG}$ 值的方案数，那么就能 $O(n \log_2^2 v)$ 合并出最终的答案。

观察计算 $\mathrm{SG}$ 值的代码：

```cpp
inline int SG(int a, int x){bool flg = 0;int s = 0;
	for (int i = 29;i >= 0;i --){
		int aa = a >> i & 1, xx = x >> i & 1;
		if (!xx) flg |= aa;
		else aa |= flg, s <<= 1, s |= aa;
	}
	if ((s + 2 & s + 1) == 0) return 0;
	if ((s & s - 1) == 0) return __lg(s) ^ 1;
	return __lg(s) + 1;
}
```

我们发现，我们只关注 $flg, \log_2 s$ 以及 $s$ 是否为 $2^k - 2, 2^k$ 形式，并且我们所做的操作就是根据 $aa, xx$ 的取值来往 $s$ 的后面加一位。

那么我们考虑建出一个识别 $01$ 串的自动机，只需要识别 $1000\cdots0$ 以及 $111\cdots10$ 两类串，显然这个自动机只有常数个节点。

这样就可以数位 DP 了：从高到低考虑 $x$ 的每一位，那么我们需要记录；

- 当前考虑到哪一位；
- 是否顶到 $b$ 的上界；
- $flg$ 的值；
- 走到了自动机的哪个节点；
- 串中第一个 $1$ 与串尾的距离。

显然可以枚举这位选 $0$ 还是 $1$ 来做到 $O(1)$ 转移。对于单个数求方案数就是 $O(\log_2^2 v)$ 的。那么总时间复杂度就是 $O(n \log_2^2 v)$。代码非常好写，E2 喜提 CF 最短解。

[E1 代码](https://codeforces.com/contest/2027/problem/E1)，[E2 代码](https://codeforces.com/contest/2027/submission/303354193)。

---

