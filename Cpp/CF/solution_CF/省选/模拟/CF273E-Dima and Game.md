# Dima and Game

## 题目描述

Dima and Anya love playing different games. Now Dima has imagined a new game that he wants to play with Anya.

Dima writes $ n $ pairs of integers on a piece of paper $ (l_{i},r_{i}) $ $ (1<=l_{i}&lt;r_{i}<=p) $ . Then players take turns. On his turn the player can do the following actions:

1. choose the number of the pair $ i $ $ (1<=i<=n) $ , such that $ r_{i}-l_{i}&gt;2 $ ;
2. replace pair number $ i $ by pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF273E/9e084f4371b7b137e0f6781dcd5a7dd3aa3d3533.png) or by pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF273E/203e78a07f9b5539eaf775cc2321c9238b008110.png). Notation $ ⌊x⌋ $ means rounding down to the closest integer.

The player who can't make a move loses.

Of course, Dima wants Anya, who will move first, to win. That's why Dima should write out such $ n $ pairs of integers $ (l_{i},r_{i}) $ $ (1<=l_{i}&lt;r_{i}<=p) $ , that if both players play optimally well, the first one wins. Count the number of ways in which Dima can do it. Print the remainder after dividing the answer by number $ 1000000007 (10^{9}+7) $ .

Two ways are considered distinct, if the ordered sequences of the written pairs are distinct.

## 样例 #1

### 输入

```
2 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4 4
```

### 输出

```
520
```

## 样例 #3

### 输入

```
100 1000
```

### 输出

```
269568947
```

# 题解

## 作者：shao0320 (赞：6)

#### CF273E Dima and Game

考虑对于单独一个$(l,r)$，实际上是一个两端往中间并拢的过程。

因此$(l,r)$的先手胜负状态只与$r-l$的大小有关。

设$r-l$的值为$x$，则$x$可以转移到的状态为$\lfloor \frac{x}{3}\rfloor$和$x-\lfloor \frac{x}{3}\rfloor$。

然而这题的$P$开到了$10^9$，因此直接对每个状态求$SG$会歇逼。

手玩即可发现，状态的$SG$呈一段一段的分布，而这个段数并不多，经过打表可以发现，段数的总数，只有$100$段左右。

于是考虑把这些状态和其范围打表记录。

设$f_{i,j}$表示考虑取了$i$个，目前的$SG$状态是$j$的方案数。

转移就枚举第$i$位是$0/1/2$即可，注意因为$2 \otimes 1 =3$,因此第二维需要记录四个状态。

根据$SG$函数的定义，$f_{n,1}+f_{n,2}+f_{n,3}$即为答案。



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1200005
#define int long long
#define mod 1000000007 
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int pos[110]={1,3,4,5,7,9,13,15,19,27,39,40,57,58,81,85,120,121,174,179,255,260,363,382,537,544,780,805,1146,1169,1632,1718,2415,2447,3507,3622,5154,5260,7341,7730,10866,11011,15780,16298,23190,23669,33033,34784,48894,49549,71007,73340,104352,106510,148647,156527,220020,222970,319530,330029,469581,479294,668910,704371,990087,1003364,1437882,1485130,2113113,2156822,3010092,3169669,4455390,4515137,6470466,6683084,9509007,9705698,13545411,14263510,20049252,20318116,29117094,30073877,42790530,43675640,60954348,64185794,90221631,91431521,131026920,135332446,192557382,196540379,274294563,288836072,405997338,411441844,589621137,608996006,866508216,884431705,1000000001};
int sg[110]={0,1,2,1,2,0,1,2,0,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1};
int n,p,g[N],f[N][4];
int query(int l,int r)
{
	l=p-l;r=p-r;
	return (l+r)*(l-r+1)/2%mod; 
}
signed main()
{
	n=read();p=read();
	for(int i=0;i<102;i++)
	{
		if(pos[i]>p)break;
		int l=pos[i],r=min(p,pos[i+1]-1);
		g[sg[i]]+=query(l,r);
		g[sg[i]]%=mod;
	}
	f[0][0]=1; 
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<=2;k++)
			{
				f[i][j^k]+=f[i-1][j]*g[k]%mod;
				f[i][j^k]%=mod;
			}
		}
	}
	printf("%lld\n",(f[n][1]+f[n][2]+f[n][3])%mod);
	return 0;
}
```



---

## 作者：chenzida (赞：3)

这题需要打表，否则会**非常非常难写**！！！

至于表的话可以 $copy$ 我的表，这个表是一个前缀和形式的。

这题因为有两个转移的状态可能，所以 $sg$ 函数的最大值为 $2$，然后我们可以把每一个 $l,r$ 的距离的 $sg$ 是 $0,1,2$ 的都打表出来。那我们求一个 $1-p$ 的 $l,r$ 的取值的时候，枚举中间的差，然后随便搞搞就出来了。

关于打表的说明：

我们可以发现，每一个 $(l,r)$ 状态只和 $r-l$ 的差有关，而且两次操作分别可以把一个差为 $x$ 的数变成 $\frac{x}{3}$ 或 $x-\frac{x}{3}$，然后我们针对这个打一下 $0,1,2$ 的表即可。

之后我们有了这个表之后我们做一遍 $dp$ 即可。用 $dp[i][j]$ 表示前 $i$ 个位置中，$xor$ 和为 $j$ 的方案数（注意，$j$ 的取值范围是 $0-3$），因为有 $xor$，$1\ xor\ 2=3$。

然后就枚举这个位置是 $0,1,2$ 然后转移即可。

代码如下：

```
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<iostream>
#define int long long
using namespace std;
const int NR=1005;
const int mod=1e9+7;
int n,p,sum,bs,bs2,ans;
int tot=0;
int cnt=500;
int a[1005]={0,1,3,4,5,7,9,13,15,19,27,39,40,57,58,81,85,120,121,174,179,255,260,363,382,537,544,780,805,1146,1169,1632,1718,2415,2447,3507,3622,5154,5260,7341,7730,10866,11011,15780,16298,23190,23669,33033,34784,48894,49549,71007,73340,104352,106510,148647,156527,220020,222970,319530,330029,469581,479294,668910,704371,990087,1003364,1437882,1485130,2113113,2156822,3010092,3169669,4455390,4515137,6470466,6683084,9509007,9705698,13545411,14263510,20049252,20318116,29117094,30073877,42790530,43675640,60954348,64185794,90221631,91431521,131026920,135332446,192557382,196540379,274294563,288836072,405997338,411441844,589621137,608996006,866508216,884431705,1000000001};
int b[1005]={0,0,1,2,1,2,0,1,2,0,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1};
int dp[NR][NR];
int getsum(int l,int r){l=p+1-l,r=p+1-r;return ((l+r)*(l-r+1)/2)%mod;}
int jc[NR];
int ksm(int a,int b)
{
	a%=mod;int res=1;
	while(b)
	{
		if(b&1)res=res*a%mod;
		a=a*a%mod;b>>=1;
	}
	return res;
}
int hf[NR],bhf[NR];
int ny(int a){return ksm(a,mod-2);}
int C(int a,int b){return jc[b]*ny(jc[a])%mod*ny(jc[b-a])%mod;}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),p=read();p-=1;
	for(int i=1;i<=cnt;i++)
	{
		if(b[i]==0){if(a[i]>p)break;continue;}
		if(b[i]==2)
		{
			
			if(a[i]>p)break;
			bs2+=getsum(a[i],min(a[i+1]-1,p));bs2%=mod;
			continue;
		}
		if(a[i]>p)break;
		bs+=getsum(a[i],min(a[i+1]-1,p));bs%=mod;
	}
	int all=getsum(1,p);dp[0][0]=1;
	for(int i=0;i<=n;i++)for(int j=0;j<=3;j++)
	{
		dp[i+1][j]+=dp[i][j]*(all-bs-bs2);dp[i+1][j]%mod;
		dp[i+1][j]+=dp[i][j^1]*bs;dp[i+1][j]%=mod;
		dp[i+1][j]+=dp[i][j^2]*bs2;dp[i+1][j]%=mod;
	}
	int ans=0;for(int i=1;i<=3;i++)ans+=dp[n][i];
	printf("%lld\n",(ans%mod+mod)%mod);
	return 0;
}

---

## 作者：Hoks (赞：0)

## 前言
SG 函数康复训练。

摘自[交互、构造、博弈](https://www.luogu.com.cn/training/676672)。
## 思路分析
$n$ 对也太 hard 了，优先来考虑只有一对数的情况。

注意到最后不能操作是和区间长度有关的，而每次操作减掉的长度也是只和区间长度有关的。

所以这个左右端点我们是并不在意的，唯一需要注意的就是区间长度 $len$。

转化过来操作和判定就变成了：
1. $len$ 小于 $3$ 则输。
2. 将 $len$ 变为 $\lfloor\frac{len}{3}\rfloor$。
3. 将 $len$ 变为 $len-\lfloor\frac{len}{3}\rfloor$。

这很 SG 函数。

边界就是 $sg_1=sg_2=1$，然后对于 $sg_i=\text{mex}(sg_{\lfloor\frac{i}{3}\rfloor},sg_{i-\lfloor\frac{i}{3}\rfloor})$。

比较容易发现 SG 函数值只可能取到 $0,1,2$，所以异或出来最大也只有 $3$。

而且 SG 函数值相同的数对局面的影响是相同的。

那么我们先数出来值为 $0,1,2$ 的数对分别有 $cnt_0,cnt_1,cnt_2$ 对，直接大力定义 $f_{i,j}$ 表示 $i$ 个数对异或值为 $j$ 的方案数。

然后暴力转移就可以了。

现在唯一的问题就变成了怎样求出在 $0\sim p$ 范围内，SG 函数值为 $0,1,2$ 的数对有多少种。

$p$ 的范围有点太大了，那也就直接找规律了。

先暴力打个表：

```cpp
n=100;
for(int i=3,l,r;i<=n;i++)
{
    l=i/3,r=i-l;
    if(a[l]==0||a[r]==0) a[i]++;
    else continue;
    if(a[l]==1||a[r]==1) a[i]++;
}
for(int i=1;i<=n;i++) cout<<a[i]<<" ";
```
跑下前 $100$ 个可以得到：

```cpp
0 0 1 2 1 1 2 2 0 0 0 0 1 1 2 2 2 2 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

貌似看不出什么循环节？

那就大胆猜测段数不会太多。

感性理解一下：

当 $len$ 不断增大时，是 $len-\lfloor\frac{len}{3}\rfloor$ 右移两位然后 $\lfloor\frac{len}{3}\rfloor$ 右移一位。

假设这两个处在的连续段长度分别为 $x,y$，那么产生的 $len$ 的新的连续段长度就大于 $\min(3y,\frac{3}{2}x)$。

况且还有 $0,2$ 和 $0,0$ 得到的 $\text{mex}$ 都是 $1$ 的情况。

所以连续段长度是指数级增长的，总段数大概也就在 $O(\log V)$ 的级别。

然后我们来考虑怎么得到连续段。

考虑上面的那个右移 $len-\lfloor\frac{len}{3}\rfloor$ 和 $\lfloor\frac{len}{3}\rfloor$ 的方法。

快速右移他们直到移出连续段，然后记录一下断点，重复操作。

具体实现的时候，我们可以考虑记录目前的 $len-\lfloor\frac{len}{3}\rfloor$ 和 $\lfloor\frac{len}{3}\rfloor$ 处于哪个连续段，哪个位置，目前的 $len$ 值。

先暴力做两步，然后开始做 $len-\lfloor\frac{len}{3}\rfloor$ 右移两位 $\lfloor\frac{len}{3}\rfloor$ 右移一位的循环节。

算一下跳出去的时候一键移过来再暴力移两步移出去记录下来就好了。

（如果想要表的见下面的代码，记录了连续段的数字和右端点。）

还有一个小问题是怎么数出现次数。

考虑到 $[0,m]$ 区间中选择出 $l,r$ 满足 $r-l=len$ 的个数为 $m-len$。

然后因为对一个数字贡献的 $len$ 是一个区间为 $[L,R]$ 的连续段，所以贡献就是 $\sum\limits_{len=L}^R m-len$，等差数列求和即可。
## 代码
顺手给 dp 数组滚了一下。

**请注意，打表初始化的数组不要开太大，不然会编译器塞不下 CE。**

```cpp
#include<bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define ls (p<<1)
#define rs (ls|1)
using namespace std;
const int N=5e5+10,M=5e3+10,V=5e5,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int r[M]={0,2,3,4,6,8,12,14,18,26,38,39,56,57,80,84,119,120,173,178,254,259,362,381,536,543,779,804,1145,1168,1631,1717,2414,2446,3506,3621,5153,5259,7340,7729,10865,11010,15779,16297,23189,23668,33032,34783,48893,49548,71006,73339,104351,106509,148646,156526,220019,222969,319529,330028,469580,479293,668909,704370,990086,1003363,1437881,1485129,2113112,2156821,3010091,3169668,4455389,4515136,6470465,6683083,9509006,9705697,13545410,14263509,20049251,20318115,29117093,30073876,42790529,43675639,60954347,64185793,90221630,91431520,131026919,135332445,192557381,196540378,274294562,288836071,405997337,411441843,589621136,608996005,866508215,884431704,1000000000};
int a[M]={0,0,1,2,1,2,0,1,2,0,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1,2,0,2,1};
int n,m,f[2][4],cnt[N];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c=='#'||c=='.'||c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int get(int l,int r)
{
	int len=r-l+1;
	return (m*len-((l+r)*len>>1))%mod;
}
inline void solve()
{
	n=read(),m=read();
	for(int i=1;;i++)
	{
		cnt[a[i]]=(cnt[a[i]]+get(r[i-1]+1,min(r[i],m)))%mod;
		if(r[i]>=m) break;
	}f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<3;j++) for(int k=0;k<4;k++)
			f[i&1][k^j]=(f[i&1][k^j]+f[i&1^1][k]*cnt[j]%mod)%mod;
		memset(f[i&1^1],0,sizeof f[i&1^1]);
	}print((f[n&1][1]+f[n&1][2]+f[n&1][3])%mod);put('\n');
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Zi_Gao (赞：0)

大家都是打表做的，但是没人说怎么打表。

首先肯定是要算出 sg 值的，然后发现 $sg$ 值只和 $r-l$ 有关，令 $x=r-l$ 则两种操作分别是把 $x$ 变成 $\lfloor\frac{x}{3}\rfloor,x-\lfloor\frac{x}{3}\rfloor$，先随便打个表，猜测最终 sg 是一段一段的，并且段数很少。于是换个打表方式记 $pos_i$ 表示第 $i$ 段结束位置，$sg_i$ 表示第 $i$ 段的 sg 值。由于对于一个 $x$ 会有一段取值的 $y$ 使得 $\lfloor\frac{y}{3}\rfloor=x$ 同样有一段取值的 $y$ 使得 $y-\lfloor\frac{y}{3}\rfloor=x$。那么用两个 $u,v$ 表示当前考虑一段 $x$ 的取值使 $\lfloor\frac{x}{3}\rfloor=pos_u,x-\lfloor\frac{x}{3}\rfloor=pos_v$，算出最大的 $x$ 满足条件，并作为新的一段 sg 值加入数组，然后挪动成为上界指针即可。同样也可以以此证明，sg 值段数只有 $\mathcal{O}\left(\log V\right)$ 级别。

剩下的随便 dp 一下就可以了。

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
inline __attribute((always_inline)) INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

const long long mod=1000000007;

int pos[1000],sg[1000];
long long cntSg[4],f[1010][4],p;

long long getSum(long long l,long long r){
    l=p-l,r=p-r;
    return (l+r)*(l-r+1)/2%mod;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,j,k,cnt=0,u=1,v=1,n;
    register long long uMax,vMax;
    n=read();p=read();

    pos[++cnt]=2;
    while(pos[cnt]<p){
        uMax=pos[u]*3+2;
        if(pos[v]&1) vMax=(pos[v]-1)/2*3+1;
        else vMax=pos[v]/2*3;
        for(i=0;i<2;++i)
            if(sg[u]!=i&&sg[v]!=i)
                break;
        if(i!=sg[cnt]) sg[++cnt]=i;
        pos[cnt]=std::min(uMax,vMax);
        if(uMax==pos[cnt]) ++u;
        if(vMax==pos[cnt]) ++v;
    }
    for(i=1;i<=cnt;++i)
        (cntSg[sg[i]]+=getSum(pos[i-1]+1,std::min(pos[i],(int)p)))%=mod;

    f[0][0]=1;
    for(i=1;i<=n;++i)
        for(j=0;j<4;++j)
            for(k=0;k<4;++k)
                (f[i][j^k]+=cntSg[j]*f[i-1][k])%=mod;

    print((f[n][1]+f[n][2]+f[n][3])%mod);

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

