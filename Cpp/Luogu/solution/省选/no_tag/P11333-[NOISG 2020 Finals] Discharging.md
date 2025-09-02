# [NOISG 2020 Finals] Discharging

## 题目背景

为了成为最强的电力供应者，Pichuu 这只电鼠开启了一项新业务：使用他最爱的技能 Discharge 为顾客充电。由于业务的高效，Pichuu 每天都有许多顾客排队等待充电。

## 题目描述

在某一天，Pichuu 有 $N$ 名顾客等待充电。Pichuu 可以同时为多部手机充电，每部手机的充电功率相同且恒定。然而，不同型号的手机电池容量不同，因此完全充满所需的时间也不同。第 $i$ 部手机需要 $T_i$ 分钟才能完全充满。

Pichuu 不会停止充电，直到所有手机都充满电。为了避免顾客等待过久，Pichuu 可以将顾客分成若干连续的组，然后按顺序为每组充电。每组中的顾客必须等待前面的组完成充电后，才能开始充电。

对于第 $k$ 组，组内充电所需的时间为该组中 $T_i$ 的最大值（记为 $M_k$）。第 $i$ 名顾客的总等待时间 $W_i$ 是他所在组及其之前所有组的充电时间之和：

$$
W_i = \sum_{n=1}^{G_i} M_n
$$

其中，$G_i$ 表示第 $i$ 名顾客所属的组编号。

Pichuu 希望通过合理分组最小化顾客的总等待时间。你的任务是帮助 Pichuu 计算最小的总等待时间。

## 说明/提示

【样例解释】

对于样例 #1：
- 最优分组为 $(1, 3, 2)$ 和 $(6, 3)$。两组的充电时间分别为 $3$ 和 $6$。  
- 第一组的等待时间为 $3$（每名顾客），第二组的等待时间为 $3 + 6 = 9$（每名顾客）。  
- 总等待时间为 $3 + 3 + 3 + 9 + 9 = 27$。

对于样例 #2：
- 最优分组为一个整体，等待时间为 $2$（每名顾客）。  
- 总等待时间为 $2 + 2 + 2 + 2 + 2 + 2 + 2 = 14$。

【数据范围】

- $1 \leq N \leq 10^6$
- $1 \leq T_i \leq 10^9$

| 子任务编号 | 分值 | 限制条件                     |
|:---:|:---:|:---:|
| $1$ | $9$  | $1 \leq N \leq 3$              |
| $2$ | $13$ | $1 \leq N \leq 1500$ 且 $T_i$ 非递减。 |
| $3$ | $25$ | $T_i$ 非递减。                  |
| $4$ | $11$ | $T_i$ 非递增。                  |
| $5$ | $14$ | $1 \leq N \leq 1500$           |
| $6$ | $28$ | 无额外限制。                    |

## 样例 #1

### 输入

```
5
1 3 2 6 3```

### 输出

```
27```

## 样例 #2

### 输入

```
7
1 1 2 2 2 2 2```

### 输出

```
14```

# 题解

## 作者：Purslane (赞：1)

# Solution

考虑如果某一段 $[l,r]$ 的最大值为 $a_k$，则必定有 $a_{r+1} > k$，否则 $r \leftarrow r+1$ 肯定更优。

因此我们只考虑**前缀最大值之间的转移**，可以令 $a_i \leftarrow \max_{1 \le j \le i} a_j$，答案不变。

这样就有

$$
dp_i = \max_{j < i} dp_j + (n-j) a_i
$$

显然可以斜率优化。

```cpp
#include<bits/stdc++.h>
#define int long long
#define _ ((__int128)1)
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e6+10;
int n,a[MAXN],dp[MAXN],tot,pos=1;
struct Node {int x,y;}st[MAXN];
void insert(int x,int y) {
	while(tot>1&&_*(y-st[tot].y)*(st[tot].x-st[tot-1].x)<_*(st[tot].y-st[tot-1].y)*(x-st[tot].x)) tot--;
	return st[++tot]={x,y},void();	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,n) a[i]=max(a[i],a[i-1]);
	insert(0,0);
	ffor(i,1,n) {
		while(pos<tot&&_*a[i]*(st[pos+1].x-st[pos].x)>st[pos+1].y-st[pos].y) pos++;
		while(pos>1&&_*a[i]*(st[pos].x-st[pos-1].x)<st[pos].y-st[pos-1].y) pos--;
		dp[i]=n*a[i]+st[pos].y-st[pos].x*a[i];
		insert(i,dp[i]),pos=min(pos,tot);
	}
	cout<<dp[n];
	return 0;
}
```

---

## 作者：VainSylphid (赞：1)

有点好玩但不多的题。

考虑 dp，在确定连续段时计算这一段对它自己以及后面所有人的贡献，这些贡献是与后面怎么分段无关的。容易写出转移方程：

$$f_i\leftarrow \min(f_j+(n-j)\times\max_{j+1\leq p\leq i}T_p)$$

这样就可以 $O(n^2)$ dp 了。

这个 $\max$ 看上去很难处理，我们试着贪心一下把它去掉。你发现，如果说我们分出了一个连续段 $[l,r]$，此时 $M_k=\max_{l\leq p\leq r}T_p$，如果 $T_{r+1}\leq M_k$，那么我们把 $T_{r+1}$ 也分到这一段来，下一段的最大值 $M_{k+1}$ 以及下一段贡献的人数 $(n-r)$ 都只变小不变大。

因此，我们分段的时候，每一段的最后一个人 $T_p$ 一定是整个 $T$ 序列的前缀最大值。我们把所有不是前缀最大值的人，全部绑到它左边的第一个前缀最大值的人身上。那么我们得到了一个新序列，序列中的第 $i$ 个位置代表了 $C_i$ 个人，等待时间为 $M_i$。

记 $S_i=\sum\limits_{p=1}^i{C_i}$，此时我们进行分段，最大值就是每一段的最后一个 $M_i$ 了。我们写出新的转移：

$$f_i\leftarrow \min(f_j+(S_n-S_j)\times M_i)$$

$$f_i\leftarrow \min(f_j-S_j\times M_i)+S_n\times M_i$$

这个 dp 显然可以直接斜率优化，[你还没学过的话](https://oi-wiki.org/dp/opt/slope/)，先做[模板题](https://www.luogu.com.cn/problem/P3195)吧。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
ll n,t[1000005],pos,s[1000005],m[1000005],Q[1000005],dp[1000005];
ll Y(ll i)
{
	return dp[i];
}
ll X(ll i)
{
	return s[i];
}
ll slope(ll i,ll j)
{
	return (ld)(Y(j) - Y(i)) / (X(j) - X(i));
}
int main()
{
	scanf("%lld",&n);
	for(ll i = 1;i <= n;i++)
	{
		scanf("%lld",&t[i]);
		if(t[i] > m[pos])
			pos++,s[pos] = s[pos - 1] + 1,m[pos] = t[i];
		else
			s[pos]++;
	}
	ll ql = 1,qr = 1;
	for(ll i = 1;i <= pos;i++)
	{
		while(ql < qr && slope(Q[ql],Q[ql + 1]) < m[i])
			ql++;
		dp[i] = dp[Q[ql]] + m[i] * (s[pos] - s[Q[ql]]);
		while(ql < qr && slope(Q[qr - 1],Q[qr]) > slope(Q[qr - 1],i))
			qr--;
		Q[++qr] = i;
	}
	printf("%lld\n",dp[pos]);
	return 0;
}
```

---

## 作者：qnqfff (赞：0)

### 思路

$O(n^2)$ 的 dp 是简单的，$dp_i=\min(dp_j+(n-j)\cdot\max\limits_{k=j+1}^{i}T_k)$。

这个 $\max$ 很烦，想办法把它去掉，容易发现如果 $\max\limits_{k=j+1}^{i}T_k\ge T_{i+1}$ 把 $i+1$ 加入这一段一定不劣，于是有用的点只有前缀 $\max$，把这些点拉出来重新标号，并设 $cnt_i$ 表示原本序列中 $T_i$ 后面有几个小于等于它的数，在对 $cnt$ 做边前缀和可得到转移方程 $dp_i=\min(dp_j+(sum_n-sum_j)\cdot T_i$，这个东西显然可以斜率优化，然后做完了。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){char c=getchar();int p=0,flg=1;while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n,a[1000010],sum[1000010],mx[1000010],dp[1000010],q[1000010];
int X(int i){return sum[i];}int Y(int i){return dp[i];}
double slope(int i,int j){return 1.*(Y(i)-Y(j))/(X(i)-X(j));}
signed main(){
	n=read();for(int i=1;i<=n;i++) a[i]=read();int cnt=0;for(int i=1;i<=n;i++){if(a[i]>mx[cnt]) mx[++cnt]=a[i],sum[cnt]=sum[cnt-1]+1;else sum[cnt]++;}
	for(int i=1,l=1,r=1;i<=cnt;i++){
		while(l<r&&slope(q[l],q[l+1])<mx[i]) l++;dp[i]=dp[q[l]]+(sum[cnt]-sum[q[l]])*mx[i];
		while(l<r&&slope(q[r-1],q[r])>slope(q[r],i)) r--;q[++r]=i;
	}cout<<dp[cnt];
	return 0;
}
```

---

## 作者：zhuweiqi (赞：0)

NOIP 前来写篇题解积累 RP。

考虑朴素 dp：

设 $f_i$ 为前 $i$ 个人手机充完电后他们的总排队时间与后 $n-i$ 个人到目前的排队时间之和，这么定义是除去后效性，记 $f_0=0$，显然有个至少 $O(n^2)$ 的 dp：$f_i=\min_{j=0}^{i-1} f_j+(n-j)\times\max_{k=j+1}^{i}t_k$。这坨玩意儿我可不想处理。。。

我们可以考虑贪心先把那个 $\max$ 优化掉。先观察 $t$ 数组中两个相邻元素的关系，注意到如果 $t_i>t_{i+1}$，那么 $t_i$ 和 $t_{i+1}$ 必定被分配到同一组，这个很显然。然后，重复以上过程，我们就可以将原数组缩成一个**递增序列**，当然新的 $t$ 数组就要有对应的人数了，记为 $c$。例如对于原序列 $[2,1,5,3,4]$ 而言，缩完后的 $t$ 数组为 $[2,5]$，$c$ 数组为 $[2,3]$。

记 $sc$ 数组为 $c$ 数组的前缀和数组，现在我们可以得到一个略微简短一些的动态转移方程式：$f_i=\min_{j=0}^{i-1} f_j+(sc_n-sc_j)\times t_i$，将含未知量 $j$ 的单项式分离可得：$f_i=\min_{j=0}^{i-1} f_j+sc_n\times t_i-sc_j\times t_i$，显然斜率优化 dp。~~为了切这道题我还专门花一小时去学了斜率优化 dp。~~

综上，时间复杂度 $O(n)$，代码也极短：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+2;
ll t[N],c[N],f[N],sc[N];
int q[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>t[i];
	t[1]=t[1],c[1]=1,m=1;
	for(int i=2;i<=n;i++){
		if(t[m]>=t[i]) c[m]++;
		else {
			t[++m]=t[i];
			c[m]=1;
		}
	}
	n=m;
	for(int i=1;i<=n;i++) sc[i]=sc[i-1]+c[i];
	int head=1,tail=1;
	f[0]=sc[0]=0;
	for(int i=1;i<=n;i++){
		int k=t[i];
		while(head<tail && (f[q[head+1]]-f[q[head]])<k*(sc[q[head+1]]-sc[q[head]])) head++;
		f[i]=-sc[q[head]]*t[i]+f[q[head]]+sc[n]*t[i];
		while(head<tail && (f[q[tail]]-f[q[tail-1]])*(sc[i]-sc[q[tail]])>(f[i]-f[q[tail]])*(sc[q[tail]]-sc[q[tail-1]])) tail--;
		q[++tail]=i;
	}
	cout<<f[n];
	return 0;
}
```

---

