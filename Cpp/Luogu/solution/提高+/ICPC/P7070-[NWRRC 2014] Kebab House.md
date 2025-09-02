# [NWRRC 2014] Kebab House

## 题目描述

年轻人 Vahtang Bumerang 在世界著名的快餐连锁店 Kebab House 制作烤肉串。每个烤肉串包含许多配料。

今天早上，Vahtang 收到了制作 $n$ 个烤肉串的订单。首先，他需要在第一个烤肉串中放入 $q_{1}$ 种配料，然后在第二个烤肉串中放入 $q_{2}$ 种配料，依此类推。Vahtang 花费一秒钟将一种配料放入一个烤肉串中，因此制作第 $i$ 个烤肉串需要 $q_{i}$ 秒。当他完成一个烤肉串后，他会立即开始下一个。

Vahtang 在制作烤肉串时经常梦到他心爱的回旋镖。每个梦恰好持续一秒钟，并且在这一秒钟内 Vahtang 会忘记放入一种配料。幸运的是，他从未在任何连续的 $(t + 1)$ 秒内做过两次梦。

由于梦到回旋镖，一些烤肉串可能会少于所需的配料数量，但如果第 $i$ 个烤肉串至少有 $x_{i}$ 种配料，顾客仍然会感到满意。

Vahtang 想计算在工作期间做梦的秒数有多少种分配方式，同时让所有顾客满意。你能帮他吗？由于真实答案可能非常大，所以你需要计算它对 $10^{9} + 7$ 取模的结果。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 1
4 3
2 2
2 1
```

### 输出

```
15
```

# 题解

## 作者：panyf (赞：11)

DP。

设 $f_{i,j,k,l}$ 表示做第 $i$ 个烤肉串，用了 $j$ 秒，做了 $k$ 次梦，离可以做梦还有 $l$ 秒的方案数。

转移方程（注意 $t=0$ 的情况）：

$$f_{i,j,k,0}=f_{i,j-1,k,1}+f_{i,j-1,k,0}$$

$$f_{i,j,k,t}=f_{i,j-1,k-1,0}$$

$$f_{i,j,k,l}=f_{i,j-1,k,l+1}(0<l<t)$$

时间复杂度 $O(nq^2t)$，不能通过。

注意到 $k\leq\left\lceil\dfrac{q}{t+1}\right\rceil$，缩小枚举上界，时间复杂度优化到 $O(nq^2)$。

前两维可以滚掉，空间复杂度 $O(qt)$。

为了减少边界特判，代码中的 $k$ 表示做了 $k-1$ 次梦。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=1e9+7;
int f[259][109];
int main(){
	int n,m,t,q,x,i,j,k,l;
	scanf("%d%d",&n,&t),f[1][0]=1;
	for(i=1;i<=n;++i){
		scanf("%d%d",&q,&x),m=min(q-x+1,q/(t+1)+2);
		for(j=1;j<=q;++j){
			for(k=m;k;--k){
				if(t)f[k][0]=(f[k][1]+f[k][0])%P;
				else f[k][0]=(f[k][0]+f[k-1][0])%P;
				for(l=1;l<t;++l)f[k][l]=f[k][l+1];
				if(t)f[k][t]=f[k-1][0];
			}
		}
		for(k=2;k<=m;++k)for(l=0;l<=t;++l)f[1][l]=(f[1][l]+f[k][l])%P,f[k][l]=0;
	}
	for(x=l=0;l<=t;++l)x=(x+f[1][l])%P;
	printf("%d",x);
	return 0;
}
```

---

## 作者：JoshAlMan (赞：3)

即选出一个 01 串（$0$ 代表做梦），满足：

* 相邻的 $0$ 之间的 $1$ 的数量 $> t$
* 每段的 $1$ 总和满足限制

不妨按段 $DP$。

维护一个 $f_i$ 表示之前最后一个 $0$ 的位置距离当前第一个位置的距离，前面满足条件的方案数。把 $ > t + 1$ 的方案记录在 $f_{t  +1}$ 上，因为转移的限制相同。

转移时，只需考虑新段最后一个 $0$ 的位置，再枚举前面的 $f$，之后中间的方案数对应的是在连续的一段选 $0$，并且 $0$ 的个数 $\le q-x$ 的一个方案数，乘起来。

考虑预处理出连续的一段选 $0$ 的方案数，可以再设一个 DP，$g_{i,j}$ 表示长度为 $i$，满足限制的情况下选了 $j$ 个 $0$ 的方案数，最后一个位置的 $0$ 为 $i$。这个可以直接 $O(q^3)$ 枚举上一个 $0$，DP 出来。

然后整个 DP 大概可以用 $O(ntq)$ 算出来。

可以通过此题。



---

## 作者：CYZZ (赞：2)

## [P7070](https://www.luogu.com.cn/problem/P7070)
### 思路
发现不同的订单之间只有 $t$ 的限制，其他的信息独立。

考虑做 $n$ 遍 dp，然后第 $i$ 次 dp 的初始值由 $i-1$ 次的结果决定。

设 $f_{i,j,k}$ 表示当前在是第 $i$ 秒，做过 $j$ 次梦，上一次做梦在第 $i-k$ 秒。

转移讨论下一秒摸不摸鱼。
$$
f_{i,j,k} \rarr f_{i+1,j,k+1}\\
f_{i,j,k} \rarr f_{i+1,j+1,0},k\ge t
$$
每一位都开 $q$ 的话是 $O(nq^3)$ 的，考虑优化状态。

对于第二维，前 $i$ 秒的做梦次数不超过 $\frac{i-1}{t+1}+1$。所以把第二维缩小到 $\frac{n}{t}$ 规模 。

对于第三维，观察第二个转移，发现 $k>t$ 的情况等价与 $k=t$ 的情况，因为我们只关心当前能不能做梦。于是把第三维缩小到 $t$ 规模。

时间复杂度缩小为是 $O(nq\frac qt t)$，也就是 $O(nq^2)$。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 2005
#define M 305
#define rep(i,x,y) for(int i=x;i<=y;i++)
int n,T,mod;
int a[N],b[N];
int f[2][M][M];
inline void Add(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
void solve()
{
    cin>>n>>T>>mod;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i]>>b[i];
        b[i]=a[i]-b[i];
    }
    f[0][0][T]=1;int o=0;
    for(int id=1;id<=n;id++)
    {
        rep(j,0,b[id-1]) rep(k,0,T)
            f[o^1][j][k]=0;
        rep(j,0,b[id-1]) rep(k,0,T)
        {
            Add(f[o^1][0][k],f[o][j][k]);
            f[o][j][k]=0;
        }
        o^=1;
        for(int i=0;i<a[id];i++,o^=1)
        {
            rep(j,0,min(b[id],i/(T+1)+1))
                rep(k,0,T) f[o^1][j][k]=0;
            rep(j,0,min(b[id],(i-1)/(T+1)+1))
            {
                rep(k,0,T) if(f[o][j][k])
                    Add(f[o^1][j][min(T,k+1)],f[o][j][k]);
                if(j<b[id]) Add(f[o^1][j+1][0],f[o][j][T]);
            }
        }
    }
    int ans=0;
    rep(j,0,b[n]) rep(k,0,T)
        Add(ans,f[o][j][k]);
    cout<<ans<<'\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
}
```

---

## 作者：ZR_BL (赞：2)

**DP**

### 状态：
设 $f_{i,j,k}$ 表示现在是 VB 做的第 $i$ 个烤肉串，是总时间的第$j$秒，在做第$i$个烤肉串的期间做了$k$次梦，当前情况下的方案数。

### 转移（刷表法）：      

- 第 $j$ 秒不做梦，下一秒仍属于做第$i$个肉串的时间：$f_{i,j+1,k}=f_{i,j,k} + f_{i,j+1,k}$。
- 第 $j$ 秒不做梦，下一秒属于做第 $i+1$ 个肉串的时间：$f_{i+1,j+1,0}=f_{i,j,k} + f_{i+1,j+1,0}$。
- 第 $j$ 秒做梦，那么 $j+1$ 到 $j+t$ 秒内都不能再做梦，因此将贡献加到第 $j+t+1$ 秒，若第 $j+t+1$ 秒在做第 $i$ 个肉串的时间内：$f_{i,j+t+1,k+1}=f_{i,j,k} + f_{i,j+t+1,k+1}$。
- 第 $j$ 秒做梦，第 $j+t+1$ 秒不属于做第 $i$ 个肉串的时间：$f_{i\',j+t+1,0}=f_{i,j,k}+f_{i\',j+t+1,0}$。

时间复杂度 $O(nq^2)$，空间复杂度 $O(nq^3)$，无法通过。


### 优化：      

我们发现，只要知道具体时间 $j$ ，就等于知道了 $i$ ，可以省略 $i$ 这一维。

我们同样可以观察到，对于当前时间 $j$，$j-1$ 之前的状态已经毫无用处，$j$ 只会对 $j+1$ 和 $j+t+1$ 有影响，不妨以 $t+2$ 作为滚动周期。

综上，空间复杂度 $O(qt)$，可以通过此题。

注意判边界。

### code：

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int M=2005,p=1e9+7;
int f[M][M];
int n,t,sum,ans,tot;
int a[M],b[M];
inline int get(int x){return x>tot+1?(tot+1)%(t+2):x%(t+2);}//判边界
int main(){
    cin>>n>>t;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        tot+=a[i];
    }
    f[1][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=a[i];j++){
            sum++;
            for(int k=0;k<=a[i]-b[i];k++){
                if(j<a[i])f[get(sum+1)][k]=(f[get(sum+1)][k]+f[get(sum)][k])%p;
                else f[get(sum+1)][0]=(f[get(sum+1)][0]+f[get(sum)][k])%p;
                if(k==a[i]-b[i])goto ed;
                if(j+t+1>a[i])f[get(sum+t+1)][0]=(f[get(sum+t+1)][0]+f[get(sum)][k])%p;
                else f[get(sum+t+1)][k+1]=(f[get(sum+t+1)][k+1]+f[get(sum)][k])%p;
                ed:f[get(sum)][k]=0;
            }
        }
    }
    cout<<f[get(sum+1)][0];
    return 0;
}
```

---

## 作者：Yansuan_HCl (赞：2)

**UPD 24.5.4: Fix LaTeX.**

这里抄一个 $O(nt^2 + \sum q)$ 做法錒。

题意即计数满足以下条件的 $a$ 数列数量：

- 一个 $\texttt {01}$ 序列分成 $n$ 段，每段长为 $q_i$，第 $i$ 段至少有 $x_i$ 个 $\texttt 1$。
- 相邻两个 $\texttt 0$ 之间至少有 $t$ 个 $\texttt 1$。

没有段的限制是容易的。然而需要多段拼在一起。注意不到每段的限制只和上一段的上一个 $0$ 的位置有关——这会对当前段填的第 $1$ 个 $\texttt 0$ 的位置产生限制。

不妨设 $f_i, i\in[0,t]$ 表示填完第 $k$ 段，下一段至少要填 $i$ 个 $\tt 1$ 的方案数。转移则形如 $g_j=\sum a_{i,j}f_i$。

试着对每个第 $k$ 段处理从第 $k-1$ 转移到第 $k$ 段的转移系数 $a$：

令 $Q=q_k$，$X=x_k$。考虑 $a_{i,j}$，则第 $k$ 段前 $i$ 个必然填 $\tt 1$。最后一个 $0$ 的位置被 $j$ 的位置限制：

- 当 $j \gt 0$：最后一个 $\tt 0$ 在 $Q-(t-j)$。此时前 $i$ 与后 $t-j+1$ 个位置已经确定（第 $Q-(t-j)$ 个位置应填 $\tt 0$），枚举中间填了 $h$ 个 $\tt 0$：

$$\begin{aligned}
a_{i,j}&=[i=Q+j]+\sum_{h=0}^{Q-X-1}G(Q-i-(t-j+1),h)
\\
	&=[i-j=Q]+\sum_{h=0}^{Q-X-1}\binom{Q-(i-j)-t-1-th}{h}
\end{aligned}
$$
，其中
$$
G(x,y)=\binom{x-ty}{y}
$$
表示 $x$ 个空位放入 $y$ 个 $\tt 0$ 并满足相邻 $\tt 0$ 限制的方案数。$G$ 即为将每个 $\tt 0$ 与后面的 $t$ 个 $\tt 1$ 捆绑之后插板。转移的第一种情况是末位确实顺次放一个 $\tt 0$ 和 $t-j$ 个 $\tt 1$，此时中间填的 $0$ 不能超过 $Q-X-1$ 个。还有一种情况是 $i$ 过长覆盖了整个 $Q$，此时中间只能填 $\tt 1$，能满足这种转移的条件为 $i=Q+j$。
  

- 当 $j=0$：此时最后一个 $\tt 0$ 的位置 $\le Q-t$。即前 $i$ 和后 $t$ 位置确定放 $\tt 1$，枚举中间填了 $h$ 个 $0$：

$$\begin{aligned}
a_{i,0}&=[i \le Q] + \sum_{h=1}^{Q-X}G(Q-i,h)\\
&=[i\le Q] + \sum_{h=1}^{Q-X }\binom{Q-i-th}{h}
\end{aligned}
$$

，实际上可以把整个后 $Q-i$ 个位置都用 $G$ 处理，因为 $G$ 计数的每个 $\tt 0$ 都带有附后的 $t$ 个 $\tt 1$。

这样，$\forall i\ne j$，所有的 $a_{i,j}$ 只和 $i-j$ 有关，于是只要计算 $O(t)$ 种取值；$a_{i,0}$ 也只有 $O(t)$ 种。注意到组合数上指标有一项 $Q-th$，所以计算一个 $a_{i,j}$ 的复杂度为 $O(Q/t)$。每次转移乘上系数的过程复杂度为 $O(t^2)$，故总复杂度为 $O(nt^2+\sum tq/t)=O(nt^2+\sum q)$。

[代码](https://www.luogu.com.cn/paste/devd7hux)见此。

---

## 作者：a___ (赞：2)

首先，发现每一时刻在烤哪个串是固定的，可以先预处理出来，顺便求一个烤当前串的开始时刻 $st_i$。   

设 $f_{i,j}$ 表示时刻 $i$ 恰好是在烤这时的这个串时第 $j$ 次做梦的方案数。    

若时刻 $i-t$ 仍是在烤当前串，则有 $f_{i,j}+=\sum_{x=st_i}^{i-t}f_{x,j-1}$ （在位置 $x$ 烤当前串时休息了第 $j-1$ 次）。     
另外，对于 $f_{i,1}$，有 $f_{i,1}+=\sum_{x=1}^{\min\{i-t,las_i\}}\sum_kf_{x,k}$ （烤非当前串的总休息方案数）。   

我们记 $g_{i,j}=\sum_{x=st_i}^if_{x,j},h_i=\sum_{x=1}^i\sum_kf_{x,k}$，求 $f$ 的时候顺便维护一下，则两个转移分别变为 $g_{i-t,j-1}$ 和 $h_{\min\{i-t,las_i\}}$。于是转移就 $\mathbf O(1)$ 了，总复杂度就 $\mathbf O(nq^2)$ 了。可过。     

```cpp
#include<cstdio>
const int N=1010,M=255,p=1e9+7;
int f[N*M][M],st[N*M],c[N*M];
int n,t,a[N],b[N];
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
int main()
{
	int i,j,k;
	scanf("%d%d",&n,&t);++t;
	for(i=k=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		for(j=1;j<=a[i];j++)
		st[k+j-1]=k,c[k+j-1]=i;
		k+=a[i];b[i]=a[i]-b[i];
	}
	f[0][0]=f[0][1]=1;--k;
	for(i=1;i<=k;i++)
	{
		f[i][1]=f[max(min(i-t,st[i]-1),0)][b[c[max(min(i-t,st[i]-1),0)]]+1];
		if(i-t>=st[i])for(j=1;j<=b[c[i]];j++)
		f[i][j]=(f[i][j]+f[i-t][j-1])%p;
		f[i][b[c[i]]+1]=f[i-1][b[c[i-1]]+1];
		for(j=0;j<=b[c[i]];j++)f[i][b[c[i]]+1]=(f[i][b[c[i]]+1]+f[i][j])%p;
		if(st[i]!=i)for(j=0;j<=b[c[i]];j++)f[i][j]=(f[i][j]+f[i-1][j])%p;
    }
	printf("%d\n",f[k][b[n]+1]);
	return 0;
}
```

---

## 作者：_7thRC_CB_CRP_ (赞：1)

考试水题。。。

我们定义 dp 状态：$f_{i,j,k}$。代表在第 $i$ 个饼中，在总的第 $j$ 时睡觉，并且在此时已经睡了 $k$ 次了。

令 $s_i$ 为第 $i$ 个位置所在的饼。

那么我们就可以这样的转移：

$$f_{i,j,1}=\sum_{k=1}^{k\le j-t-1}\sum_{r=1}^{r\le q_{s_j}-x_{s_j}}f_{s_i,k,r}

\\

f_{i,j,r(2\le r)}=\sum_{k=1}^{k\le j-t-1}[s_k=i]f_{s_i,k,r-1}
$$

显然这个东西是可以前缀和优化的，那么复杂度就是 $nk^2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, t, mod=1000000007;
ll q[2001], x[2001];
ll dp[301][301];
ll r[301][301];
ll tp;
ll sum[602302];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> t;
	t+=1;
	for (ll i = 1; i <= n; i++)
		cin >> q[i] >> x[i];
	for (ll i = 1; i <= n; i++) {
		memset(dp, 0, sizeof dp);
		memset(r, 0, sizeof r);
		if (x[i] != q[i]) {
			for (ll j = 1; j <= q[i]; j++) {
				dp[j][1] += 1;
				if (j + tp > t)
					dp[j][1] += sum[min(j + tp - t, tp)];
			}
		}
		for (ll j = 2; j <= q[i] - x[i]; j++) {
			for (ll k = 1; k <= q[i]; k++)
				r[j - 1][k] = r[j - 1][k - 1] + dp[k][j - 1], r[j - 1][k] %= mod;
			for (ll k = t + 1; k <= q[i]; k++)
				dp[k][j] = r[j - 1][k - t], dp[k][j] %= mod;
		}
		for (ll j = 1; j <= q[i]; j++) {
			ll s = 0;
			for (ll k = 1; k <= q[i] - x[i]; k++)
				s += dp[j][k], s %= mod;
			sum[tp + j] = sum[tp + j - 1] + s;
			sum[tp + j] %= mod;
		}
		tp += q[i];
	}
	cout << (sum[tp] + 1) % mod;
	return 0;
}

```

---

## 作者：zdd0342 (赞：0)

# [NWRRC2014] Kebab House

## Description

你有 $n$ 个区间。每一个区间顺次相连。

第 $i$ 个区间长度为 $q_i$，在这个区间中，每一个时刻你可以选择两个状态：清醒和做梦。

你有两个限制：

- 在第 $i$ 个区间中，你至少要有 $x_i$ 个时刻是清醒的。
- 两个做梦的时刻至少相差 $t$ 秒，也就是说，任意连续的 $t+1$ 秒，你至多只能做一次梦。这个限制可以跨过区间，就是说，两个不同区间之间的做梦，也要至少相差 $t$ 秒。

问你有多少个做梦方法，对 $10^9+7$ 取模。

## Solution

提供一个不一样的 `dp` 做法。

设计 `dp` 数组 $dp_{i,j}$ 表示：当前考虑到第 $i$ 个区间，**最后一次做梦**的时刻，相对于区间开始的位置在 $j$。

其中 $j$ 的范围是 $[-t,q_i]$。

对于每一个区间，如果上一次睡觉在区间开始之前 $t$ 秒之前，就对于这个区间一点作用都没有。此时你在这个区间第一次做梦的时间就没有限制了，所以无需记录。

也就是说，$dp_{i,-t}$ 表示，上一次做梦时间在区间开始时的 $t$ 秒之前，其他 $dp_{i,j}$ 表示最后一次做梦的时间**恰好**是 $j$。

---

转移相对于状态就简单多了。~~好像也没有简单多少。~~
$$
dp_{i,j}=
\left\{\begin{matrix} 
  \sum\limits_{k=-t}^{-t+p_{i-1}}dp_{i-1,k} & j=-t \\  
  dp_{i-1,j+p_{i-1}} & j\in (-t,0]\\
\sum\limits_{k=-t}^{p_{i-1}}dp_{i-1,k}\times S_{len,p_i-s_i} & j\in[1,p_i] 
\end{matrix}\right.
$$
其中，$len=j-\max(k-p_{i-1},1)+1$，表示从 $k$ 到 $j$，在时间轴上真正经过的时刻。

$S_{i,j}$ 表示从第一个时刻开始，钦定第 $i$ 个时刻一定做梦，一共至少做梦 $j$ 次，满足条件的方案数。

先预处理出 $S_{i,j}$，然后直接转移 $dp$ 数组。最后，$ans=\sum\limits_{j=-t}^{p_n}f_{n,j}$。

复杂度 $O(nt^2)$。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2000+5;
const int MAXQ=300+5,Q=300;
int n,T,mod;
int p[MAXN],x[MAXN];
int dp[MAXN][MAXQ<<1];
int s[MAXQ<<1][MAXQ<<1];
inline void add(int& x,int y){x+=y;(x>=mod)&&(x-=mod);}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
	cin>>n>>T>>mod;
	for(int i=1;i<=n;i++)cin>>p[i]>>x[i];
	s[0][0]=1;
	for(int i=1;i<=Q*2;i++){
		for(int j=0;j<i-T;j++){
			for(int k=1;k<=i;k++)
			add(s[i][k],s[j][k-1]);
		}
	}
	for(int i=1;i<=Q*2;i++){
		for(int k=1;k<=i;k++)
			add(s[i][k],s[i][k-1]);
	}
	dp[0][0]=1;int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=-T;j<=p[i];j++){
			if(j<=0){
				if(j==-T){
					for(int k=-T;k<=j+p[i-1];k++)
						add(dp[i][j+T],dp[i-1][k+T]);
				}else dp[i][j+T]=dp[i-1][j+T+p[i-1]];
			}
			else{
				for(int k=-T;k<=p[i-1];k++){
					int now=j,lst=max(k-p[i-1]+1,1-T);
					add(dp[i][j+T],(ll)s[now-lst+1][min(now-lst+1,p[i]-x[i])]*dp[i-1][k+T]%mod);
				}
			}
			if(i==n)add(ans,dp[i][j+T]);
		}
	}
	cout<<ans<<"\n";
}
```

---

## 作者：nullqtr_pwp (赞：0)

原题的 $t$ 在下文是 $k$，原题的 $q_i$ 在下文是 $a_i$，下文的 $b_i$ 指代原题的 $q_i-x_i$。

称呼做梦为染黑，那么就要求两次染黑的间隔 $\ge k$，且划分的 $n$ 段中每段有各自限制的染黑数量。

如果我们按段 DP，就会有 $f_{i,j}$ 表示前 $i$ 段，最后一次染黑到结尾的白色段长度为 $j$ 的方案数，其中 $\ge k$ 我们认为与 $=k$ 是等价的，初始有 $f_{0,k}=1$。具体转移我们需要枚举第 $i$ 段开始的白色连续段长 $st$ 与结尾白色段长 $ed$，可以直接特判该段没有任何一个格子染黑的情况，直接有 $f_{i-1,j}\to f_{i,\min(j+q_i,k)}$。难点在于给定 $st,ed$ 以较快的时间计算方案数。

但其实我们显然只关心 $len=st+ed$ 的值，并且可以枚举染了 $i$ 个黑，染了一个黑色是平凡的，染了两个及以上黑时，考虑两端强制染上，此时段长不是 $a_i$，而是 $a_i-len-2$，$-2$ 是因为两端已有的黑色，那么我们还需要在中间放 $i-2$ 个黑。此时方案数可以视为形如求解：$x_1+x_2+\cdots+x_t=P,\forall x_i\ge k$ 的非负整数解组数，其中 $x_i$ 的意义代表相邻两个黑色的距离，这个可以预处理组合数 $O(1)$ 插板法求解。对于 $a_i$ 相同的，这一部分的系数也是完全一样的，可以放在一开始对所有 $1\to \max(a_i)$ 进行预处理。那么 $coef_{i,j,k}$ 就代表分段长度为 $i$，$st+ed=j$，一共 $k$ 个染黑的合法方案数。这里不考虑 $st,ed$ 的具体值。

考虑 $b_i$ 在每一段的作用只是让你对于 $coef$ 在 $k$ 做一段前缀和，我们不关心染了具体多少个黑。

回到转移，我们必然需要枚举 $st,ed$，而上一段符合条件的是一段 $f_{i-1,*}$ 的后缀和，乘上这一段的系数，会转移到 $f_{i,ed}$ 上。

时间复杂度大概 $O(A^3+nA^2+nAt)$。


```cpp
void calc(int m,int len){
	if(len+k+2>m)return coef[m][len][1]=(len+1==m),void();
	const int mx=(m-len-2-k)/(k+1);
	F(i,0,mx)coef[m][len][i+2]=C(m-len-2-i-(k-1)*(i+1)-1,i);
}
void solve(){
	n=read(),k=read();
	F(i,1,250)F(j,0,i-1)calc(i,j);
	F(i,1,n)a[i]=read(),b[i]=read();
	f[0][k]=1;
	F(i,1,n){
		const int lim=a[i]-b[i];
		F(j,0,k)inc(f[i][min(k,j+a[i])],f[i-1][j]);
		F(j,0,a[i])pre[j]=0;
		F(j,0,a[i])F(l,1,lim)inc(pre[j],coef[a[i]][j][l]);
		dF(j,k,0)suf[j]=add((j==k)?0:suf[j+1],f[i-1][j]);
		F(l,0,a[i]-1)F(p,0,l){
			const int q=l-p;
			int val=1ll*suf[max(0,k-p)]*pre[l]%mod;
			inc(f[i][min(k,q)],val);
		}
	}
	int ans=0;
	F(i,0,k)inc(ans,f[n][i]);
	printf("%d",ans);
}
```

---

