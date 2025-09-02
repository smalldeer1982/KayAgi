# 『MGOI』Simple Round I | D. 魔法环

## 题目背景

> 最好的武器不一定最适合，最适合的武器才最好。——
殿堂魔法士 W

## 题目描述

小 M 面临着激发自己魂器——魔法环的任务。

魔法环上有 $n$ 个节点，每个节点上都有一个魔法精灵，每个魔法精灵都有一个固定的**魔供值**，这些魔供值形成一个 $0 \sim n-1$ 的排列。

小 M 可以选择激活或不激活一个魔法精灵，但为了激发魔法环，必须**至少**激活 $k(\ge 2)$ 个魔法精灵。

每个魔法精灵无论是否激活都会产生**附魔值**：

- 对于一个被激活的魔法精灵，它产生的附魔值为它的魔供值的**平方**。
- 对于一个未被激活的魔法精灵，它会在环上朝左右看，分别看向两边最近的被激活的魔法精灵。它会选择其中魔供值较大的一个作为「目标精灵」，产生的附魔值为这个「目标精灵」的魔供值与**看向这个「目标精灵」时视线经过的距离**的**乘积**。

作为新手，小 M 希望在激活魔法环的前提下，使得所有魔法精灵的附魔值之和最小，从而更好地控制魔法环的能量。

## 说明/提示

**【样例 1 解释】**

激活魔供值为 $0$ 和 $1$ 的魔法精灵。

- 魔供值为 $3$ 的魔法精灵，选择魔供值为 $1$ 的魔法精灵，产生的附魔值为 $1 \times 3 = 3$。
- 魔供值为 $0$ 的魔法精灵被激活，产生的附魔值为 $0^2=0$。
- 魔供值为 $1$ 的魔法精灵被激活，产生的附魔值为 $1^2=1$。
- 魔供值为 $4$ 的魔法精灵，选择魔供值为 $1$ 的魔法精灵，产生的附魔值为 $1 \times 1 = 1$。
- 魔供值为 $2$ 的魔法精灵，选择魔供值为 $1$ 的魔法精灵，产生的附魔值为 $1 \times 2 = 2$。

总共产生的附魔值为 $7$。
  
**【数据范围】** 

**本题采用 Subtask 捆绑测试。**

对于所有数据，$2\le k \le n \le 3000$，$k \le 100$，每个节点上魔法精灵的魔供值形成一个 $0\sim n-1$ 的排列。 

| Subtask | $n$ | $k\le$ | 分值 |  
| :------------: | :----------: | :----------:|:----------------:|
| $1$ | $10$ | $10$ | $13$ |
| $2$ | $100$ | $100$ | $17$ | 
| $3$ | $300$ | $100$ | $21$ | 
| $4$ | $1000$ | $100$ | $23$ | 
| $5$ | $3000$ | $100$ | $26$ | 

## 样例 #1

### 输入

```
5 2
3 0 1 4 2```

### 输出

```
7```

## 样例 #2

### 输入

```
10 3
2 0 1 5 8 3 4 9 6 7```

### 输出

```
53```

# 题解

## 作者：zhlzt (赞：19)

### DP 做法
这道题可以用 DP 做，也是一类分段问题。

我们知道这道题的元素构成了一个环，没法直接 DP，考虑以魔供值为 $0$ 的精灵为断点，并激活，将环断成链。

为什么可以这么做呢？因为将魔供值为 $0$ 的精灵激活，它周围的未被激活的精灵肯定不会选择它作「目标精灵」，要是选魔供值大于 $0$ 的，魔供值的平方会更大，还有可能会让周围的未被激活的精灵选择它作「目标精灵」，导致答案变大，所以说将魔供值为 $0$ 的精灵激活一定不会劣于其他方案。

那么我们照上述方法将环断成链，设该链上精灵的魔供值从左往右依次为为 $p_1,p_2,\ldots p_n$，其中 $p_1=0$。

设 $dp_{i,j}$ 表示将第 $i$ 个精灵激活，前 $i$ 个精灵中激活 $j$ 个精灵产生的附魔值之和的最小值，那么不难得出以下状态转移方程：
$$dp_{i,j}=\min_{k=1}^{i-1}dp_{k,j-1}+val(k,i)~(1\le j\le i\le n,j\le m)$$
其中 $val(k,i)$ 表示第 $i$ 和 $k$ 个精灵已被激活，中间未被激活的精灵与第 $i$ 个精灵的附魔值之和，计算方式为：
$$val(k,i)=\max(p_k,p_i)\times\dfrac{(i-k-1)(i-k)}{2}+{p_i}^2$$

不过题目中说的是至少选 $m$ 个精灵激活，为了节省时空复杂度，我们将 $dp_{i,m}$ 的定义改为将第 $i$ 个精灵激活，前 $i$ 个精灵中激活 **至少** $m$ 个精灵产生的附魔值之和的最小值，那么需要给 $dp_{i,m}$ 附加一个状态转移方程：
$$dp_{i,m}=\min_{k=1}^{i-1}dp_{k,m}+val(k,i)~(1\le m\le i\le n)$$

不过千万别忘了赋初始值，首先，将所有 $dp_{i,j}$ 置为 $+\infty$，之后，将 $dp_{1,1}$ 置 $0$，因为断成链后第 $1$ 个精灵魔供值就为 $0$，正是我们必定激活的那个，$dp_{1,1}$ 的值又全由它决定，所以 $dp_{1,1}={p_1}^2=0^2=0$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3010,M=105;
int p[N],q[N]; long long dp[N][M];
inline long long val(int pl,int pr){
// 不用 inline 连吸氧都卡不过
	int cnt=(pr-pl-1)*(pr-pl)>>1;
	return 1ll*max(p[pl],p[pr])*cnt+p[pr]*p[pr];
}
int main(){
	int n,m,pos;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&q[i]);
	for(int i=1;i<=n;i++) if(!q[i]) pos=i;
	for(int i=1;i<=n;i++) p[i]=q[(i+pos-1-1)%n+1];
	memset(dp,127,sizeof(dp)); dp[1][1]=0;
	for(int i=1;i<=n;i++){
		for(int j=2;j<=min(i,m);j++){
			for(int k=1;k<i;k++){
				dp[i][j]=min(dp[i][j],dp[k][j-1]+val(k,i));
				if(j==m) dp[i][j]=min(dp[i][j],dp[k][j]+val(k,i));
			}
		}
	} 
	long long ans=LLONG_MAX;
	for(int i=1;i<=n;i++) ans=min(ans,dp[i][m]+val(i,n+1));
	printf("%lld",ans);   return 0;
}
```

---

## 作者：CSP_Sept (赞：9)

这是下派验题人题解。前往 [T3 题解](https://www.luogu.com.cn/blog/supervise/solution-lgr148-c)。

## 解法

先提一下显然的 $O(n^3k)$ 做法。

钦定 $0\sim n-1$ 中的一个为初始激活点。然后断环为链，后面接一个初始点形成长度为 $n+1$ 的序列。

设 $dp_{i,j}$ 表示考虑到 $i$ 点且已经激活 $j$ 个点时的最小贡献。我们有转移

$$
dp_{i,j+1}=\min\limits_{p=1}^{n-1}\{dp_{p,j}+val(p,i)\}.
$$

上面只是 $j< k$ 的情况，为使其满足**至少** $k$ 个的条件。还应有

$$
dp_{i,k}=\min\limits_{p=1}^{n-1}\{dp_{p,k}+val(p,i)\}.
$$

这里的贡献函数 $val$ 可以 $O(1)$ 计算，不在优化范畴内。

枚举 $i,j,p$，转移即可。但这并不能通过本题。考虑优化。

我们先来考虑一个结论：**选 $\boldsymbol{0}$ 一定不劣**。

证明一下，对于一个没有选 $0$ 的状态，加上 $0$ 后，$0$ 的贡献从初始某值变为了 $0^2=0$ **而不会改变其他结点的贡献**，这是容易证明的。所以选 $0$ 一定不劣。

那么我们在「钦定」这一步直接钦定 $0$ 开始激活不就好了吗！因为 $0$ 是必选的。

所以将复杂度降到了 $O(n^2k)$，可以通过。

## Bonus

初始的题意是「选定**恰好** $k$ 个点激活」，但难以证明在这种情况下选 $0$ 不劣。出题组和我都不太会！欢迎提供证明/证伪。

---

## 作者：Register_int (赞：7)

真的绷不住了。

是个环，所以要破个环。设 $dp_{i,j}$ 表示前 $i$ 个点了 $j$ 个的最小值，有转移：

$$dp_{i,j}=\min_{1\le k<i}dp_{k,j-1}+a_i^2+\dfrac{(i-k)(i-k-1)}2\times\max(a_i,a_k)$$

然后枚举最后一个被点的连到环头算贡献。

直接做是 $O(n^4)$，很难绷。发现转移跟 $j$ 一点关系都没有，所以 $j\ge k$ 的时候我们假装把这点了就行。复杂度 $O(n^3k)$。

假设当前有个精 $0$ 被两个精灵两面包夹芝士，那么你把这个精 $0$ 点了，较小那一侧的精灵会全部扭过去找权值小的，一定不比原来劣，所以 $0$ 是必点的。那我们直接点了 $0$ 再做 dp，可以省去断环的一个 $n$。时间复杂度 $O(n^2k)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e3 + 10;
const int MAXM = 1e2 + 10;

int n, m, t[MAXN], a[MAXN], p;

inline 
ll num(int n) {
	return (ll)n * (n + 1) >> 1;
}

inline 
ll calc(int l, int r) {
	return num(r - l - 1) * max(a[l], a[r]) + a[r] * a[r];
}

ll dp[MAXN][MAXM], ans;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &t[i]), t[i] || (p = i);
	for (int i = 0; i < n; i++) a[i + 1] = t[(i + p) % n];
	memset(dp, 0x3f, sizeof dp), dp[1][1] = 0, ans = LLONG_MAX;
	for (int i = 1; i <= n; i++) {
		for (int j = 2; j <= i && j <= m; j++) {
			for (int k = 1; k < i; k++) {
				dp[i][j] = min(dp[i][j], dp[k][j - 1] + calc(k, i));
				if (j == m) dp[i][j] = min(dp[i][j], dp[k][j] + calc(k, i));
			}
		}
	}
	for (int i = 1; i <= n; i++) ans = min(ans, dp[i][m] + calc(i, n + 1));
	printf("%lld", ans);
}
```

---

## 作者：Daidly (赞：4)

一眼 dp，考虑断环为链。

在题目要求的是至少 $k$ 个的情况下，发现无论怎么选，若最后没有 $0$，加上 $0$ 肯定不劣。

不妨将 $0$ 作为链的起点和终点。

记 $dp_{i,j}$ 表示第 $j$ 个激活的是 $i$，转移如下：
 
$$

dp_{i,j}=\min_{l<i}\{dp_{l,j-1}+calc(l,i)\}

$$

其中 $calc(l,r)=a_r^2+\frac{1}{2}(r-l)(r-l-1)$，你发现这是 $O(n^3)$ 的。

$k$ 较小，考虑将 $n$ 换成个 $k$。固定 $l$ 时，对于 $j\ge k$ 我们并不关心 $j$ 的具体值，而只想知道他们所有的最小值，那么将 $k\sim n$ 一维压缩成 $k$ 一个，而 $j\ge k$ 时的一车转移方程也优化成 $dp_{i,k}=\min\{dp_{i,k},dp_{l,k}+calc(l,i)\}$ 一个。

复杂度降低到 $O(n^2k)$，代码稍微卡卡就能过。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c<='9'&&c>='0'){x=(x<<1)+(x<<3)+(c^48),c=getchar();}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=3e3+5,K=105;
int n,k,b[N<<1],a[N],dp[N][K];

inline int calc(int l,int r){
	return a[r]*a[r]+max(a[l],a[r])*(r-l)*(r-l-1)/2;
}

signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i)b[i]=b[i+n]=read();
	for(int i=1;i<=n;++i){
		if(!b[i]){
			for(int j=i+1;j<=i+n;++j)a[j-i]=b[j];
			break;
		}
	}
	memset(dp,0x7f,sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=min(i,k);++j){
			for(int l=0;l<i;++l){
				dp[i][j]=min(dp[i][j],dp[l][j-1]+calc(l,i));
			}
		}
		for(int l=0;l<i;++l)dp[i][k]=min(dp[i][k],dp[l][k]+calc(l,i));
	}
	print(dp[n][k]);
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：1)

## 题目大意
在一个有 $n$ 个数（这 $n$ 个数组成 $0\sim n-1$ 的排列，且相邻两数在环上的距离为 $1$）的环中，你需要标记至少 $k$ 个数，对于每一个数，如果被标记，则产生其值的平方的代价，否则，产生两边离其最近的被标记的两个数中较大的数的值乘上这个数与较大数在环上的距离的代价。最小化这个代价。

## 题目分析

首先，可以很容易想到一个比较麻烦的断环为链的 $O(n^4)$ 方的暴力 $dp$，肯定是不想去考虑的。

不过，我们标记一个数的代价无法通过单调性解决是因为其会因为被标记产生代价，而对其它数的代价的影响又很不确定。但发现题目中说是 $0\sim n-1$ 的排列，就能注意到出题人特意把 $0$ 给加入，那说明 $0$ 很有可能有特殊性质。

思考一下，$0$ 不会比其它数大，而且被标记不会产生代价，所以标记 $0$ 后不会增加任何数的代价，甚至还能减少代价（至少会减少自己的代价）。所以，选 $0$ 是一定更优的。

这样我们就可以直接以 $0$ 为左端点断环为链，再 $dp$。不仅复杂度变为 $O(n^3)$，转移也变得很简单。

不过，标记了 $k$ 个以上的数后我们就不用关心一共选了多少个，所以转移时可以把标记数量大于等于 $k$ 的缩成一个状态，复杂度 $O(n^2k)$。

$9\times 10^8$ 居然能过 $1s$，震撼世界观~~

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned long long
#define e(x) for(int i=h[x];i;i=nxt[i])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =3e3+5,M=1e5+5,inf=2147000000;
const ll mod=998244353;
using namespace std;
int n,k,p[N],s,a[N];
int dp[105][N],ans=inf;
signed main(){
	n=read(),k=read();
	rep(i,1,n)p[i]=read(),s=max(s,(p[i]==0)*i);
	rep(i,1,k)rep(j,1,n)dp[i][j]=1000000000000000;
	rep(i,s,n)a[i-s+1]=p[i];
	rep(i,1,s-1)a[n-s+1+i]=p[i];
	dp[1][1]=0;
	rep(i,2,n){
		int mx=min(i,k);
		rep(j,2,mx)rep(l,j-1,i-1){
			int nw=dp[j-1][l]+a[i]*a[i];
			if(a[l]<a[i])nw+=(a[i]-a[l])*(i-l)*(i-l-1)/2;
			dp[j][i]=min(dp[j][i],nw);
		}	
		if(i>k){rep(j,k,i-1){
			int nw=dp[k][j]+a[i]*a[i];
			if(a[j]<a[i])nw+=(a[i]-a[j])*(i-j)*(i-j-1)/2;
			dp[k][i]=min(dp[k][i],nw);
		}}
		mx=min(k,i-1);
		rep(j,1,mx)rep(l,j,i-1)dp[j][l]+=a[l]*(i-l);
	}
	rep(i,k,n)ans=min(ans,dp[k][i]);
	cout <<ans;
	return 0;
}
```


---

## 作者：InversionShadow (赞：0)

首先断环为链，然后 dp。但是我们先钦定值为 $0$ 这个位置激活，为什么呢？

考虑 $0$ 的贡献，前后变化了 $0^2=0$，而题目所说为排列，所以一个未被激活的点一定可以看到大于 $0$ 的已被激活的点。换句话说激活 $0$ 对答案没有影响，所以一定不劣。

我们设 $f_{i,j}$ 表示前 $i$ 个激活 $j$ 个的最小值，枚举前一个激活的：

$$f_{i,j}=\min\limits_{l=1}^{i-1}(f_{l,j-1}+val(l,i))$$

其中 $val(l,i)$，代表贡献，可以 $\mathcal{O}(1)$ 得出。

然后发现与 $j$ 无关，所以当 $j\ge k$ 时，$dp_{i,k}$ 直接转移即可，时间复杂度 $\mathcal{O}(n^2k)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e4 + 100, M = 105;

int n, k, a[N], b[N], dp[N][M], id;

inline int val(int l, int r) {
  return b[r] * b[r] + max(b[l], b[r]) * (r - l) * (r - l - 1) / 2;
}

signed main() {
  memset(dp, 63, sizeof(dp));
  dp[0][0] = 0;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i + n] = a[i];
    if (a[i] == 0) {
      id = i;
    }
  }
  for (int j = id + 1, k = 1; k <= n; j++, k++) {
    b[j - id] = a[j];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= min(i, k); j++) {
      for (int l = j - 1; l < i; l++) {
        dp[i][j] = min(dp[i][j], dp[l][j - 1] + val(l, i));
      }
    }
    for (int l = 0; l < i; l++) {
      dp[i][k] = min(dp[i][k], dp[l][k] + val(l, i));
    }
  }
  cout << dp[n][k];
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

因为问题在环上，首先考虑破环，先钦定一个点为起点，设 $f_{i, j}$ 表示在前 $i$ 个点中激活了 $j$ 个时的附魔值最小值。转移时考虑枚举上一个激活的点，可以得到转移方程

$$f_{i, j} = \min\limits_{k = 1}^{i - 1}{f_{k, j - 1} + val(k, i)}$$

其中 $val(l, r)$ 表示当前激活了点 $r$，上一个激活的点是 $l$ 区间 $\left(l,r\right]$ 对答案产生的贡献，观察性质可得

$$val(l, r) = \dfrac{\left(r - l\right) \left(r - l + 1\right)}{2} \times \max\left(a_l, a_r\right) + a_r^2$$

这样处理的话复杂度为 $\mathcal{O}(n^4)$，观察转移方程可以发现其与 $j$ 也就是已激活点数无关，所以当 $j \ge K$ 时可以直接从 $dp_{k, j}$ 转移，这样复杂度可以优化至 $\mathcal{O}(n^3 K)$。

**本题还有一个结论：激活点 $0$ 一定不劣。**

证明可以考虑从没有激活 $0$ 到激活 $0$ 的状态的贡献变化。首先考虑点 $0$ 自身的贡献为 $0^2 = 0$，对于其他未激活的点，一定可以观望到一个大于 $0$ 的点，也就是点 $0$ 不产生贡献。

所以我们在处理环的过程中可以直接钦定点 $0$ 为起点即可，总复杂度 $\mathcal{O}(n^2 K)$，可以通过本题。

## Code
```cpp
//D
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MAX = LONG_LONG_MAX >> 1;

int main() {
    std::ios::sync_with_stdio(false);

    valueType N, K, zeroPos;

    std::cin >> N >> K;

    ValueVector source(N);
    ValueMatrix dp(N + 1, ValueVector(K + 1, MAX));

    for (valueType i = 0; i < N; ++i) {
        std::cin >> source[i];

        if (source[i] == 0)
            zeroPos = i;
    }

    ValueVector value(N + 10);
    for (valueType i = 0; i < N; ++i)
        value[i + 1] = source[(i + zeroPos) % N];

    typedef std::function<valueType(valueType, valueType)> CalcFunction;

    dp[1][1] = 0;
    for (valueType i = 1; i <= N; ++i) {
        for (valueType j = 2; j <= std::min(i, K); ++j) {
            for (valueType k = 1; k < i; ++k) {
                dp[i][j] = std::min(dp[i][j], dp[k][j - 1] + (i - k) * (i - k - 1) / 2 * std::max(value[k], value[i]) + value[i] * value[i]);
                
                if (j == K)
                    dp[i][j] = std::min(dp[i][j],
                                        dp[k][j] + (i - k) * (i - k - 1) / 2 * std::max(value[k], value[i]) + value[i] * value[i]);
            }
        }
    }

    valueType ans = MAX;

    for (valueType i = 1; i <= N; ++i)
        ans = std::min(ans, dp[i][K] + (N - i) * (N - i + 1) / 2 * std::max(value[i], value[N + 1]));

    std::cout << ans << std::endl;

    return 0;
}
```

---

