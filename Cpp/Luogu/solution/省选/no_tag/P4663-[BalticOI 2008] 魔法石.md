# [BalticOI 2008] 魔法石

## 题目描述

知名的石头 $\text{Xi-n-k}$ 只能在 Wonderland 中找到，这样的石头只是一种碑文只有字母 ``X`` 和 ``I`` 的花岗岩板。每个石板包含 $n$ 个字母。每个石板上有不超过 $k$ 个位置 ``X`` 和 ``I`` 相邻。

石板的顶部和底部不是固定的，所以石头可以旋转，变为倒立状态。例如下面这两个图片描述的是一样的石头。 

![0](https://i.loli.net/2018/02/20/5a8ba0ad731f2.png)

(看同样石头的两种方式。这种石头的种类是 $\text{Xi-8-3}$，也是 $\text{Xi-8-4}$（当然也可以是 $\text{Xi-8-}k$，$k \ge 3$））。

现在 Wonderland 中任意两块魔法石都不是一样的，即两块石头都没有相同的碑文（注意旋转 $180^\circ$​​ 是允许的）。

如果可以以两种不同方式（用旋转 $180^\circ$​​ 的方式）读一块石头的碑文，那么对于这块石头，碑文的正规阅读方式被定义为两种阅读方式字典序小的那种。

如果一块石头的碑文是对称的，即旋转 $180^\circ$​​ 并不改变碑文，那么对于这块石头，碑文的的正规阅读方式被定义为这种独一无二的阅读方式。

例如：有六种 $\text{Xi-3-2}$ 魔法石，它们的正规阅读方式以字典序写出为：``III``，``IIX``，``IXI``，``IXX``，``XIX`` 和 ``XXX``。

Alice 是一个研究 Wonderland 的魔法石的专家。她想要创建一个 $\text{Xi-n-k}$ 魔法石的正规阅读方式字典（对于一些特定的 $n$ 和 $k$）。对于给出的 $i$，在字典中第 $i$ 个位置应该是什么碑文呢？

#任务

写一个程序能够：

-    从标准输入中读取数字 $n$，$k$，$i$
-    判定对于 $\text{Xi-n-k}$ 魔法石，第 $i$ 个正规阅读方式（按字典序）
-    输出结果到标准输出


## 说明/提示

**数据范围与提示**

对于全部数据，$0\le k<n\le 60,0<i<10^{18}$​​。

注：我们说 $\text{A}$ 的碑文字典序比 $\text{B}$ 小（假设 $\text{A}$ 和 $\text{B}$ 的碑文长度相同），当且仅当在第一个碑文不同的位置 $\text{A}$ 包含 ``I`` 且 $\text{B}$ 包含 ``X`` 。


## 样例 #1

### 输入

```
3 2 5```

### 输出

```
XIX```

## 样例 #2

### 输入

```
3 2 7```

### 输出

```
NO SUCH STONE```

# 题解

## 作者：kouylan (赞：4)

首先，我们先把 $I$ 当成 $0$，$X$ 当成 $1$，一个石头就变成了一个二进制数。

然后一看就可以二分答案。我们二分一个 mid，那之后的问题就变成求在 mid 以内有多少符合要求的二进制数，用类似数位 dp 的方法即可。

设 dp 状态为 $f(x,j,a,b,lim,c)$ 表示

$x,j$：填了前 $x$ 位和后 $x$ 位的数字，用了 $j$ 次相邻不同数位

$a,b$ :（都是 $0/1$）正数第 $x$ 位是 $a$，倒数第 $x$ 位是 $b$

$lim$ :（是 $0/1/2$）当前数在上限内 / 恰好压着上限 / 超过了上限（显然，最后一种情况想要合法，就只能是后 $x$ 位超上限）

$c$ :（是 $0/1$）当前填进去的串从前往后读和从后往前读 小于 / 相等（如果大于就不合法，所以不记录）

这些之后可以填数字的方案数。每次 $x$ 扫到超过一半就停止，最终总个数就是 $f(n,0,0,0,1,1)$。

转移采用记忆化搜索，每次枚举当前状态下，前后两位要天的数，记为 $a1,b1$。那新的 $j$ 和 $c$ 就很好算了，所以主要讲新的 $lim$（记为 $lim1$）的计算方式。

如果 $a1$ 大于当前位上限，那转移过来的 $lim$ 就必须等于 $0$。

如果 $a1$ 小于当前位上限，那 $lim1$ 就直接等于 $0$。

否则 $a1$ 等于当前位上限，如果 $b1$ 大于当前位上限，$lim1=2$（后面超了），如果 $b1$ 小于当前位上限，$lim1=1$（把后面超的消掉了，但依然要保证前面的不能超上限）。

这样转移就做完了，二分复杂度 $O(n)$，dp 复杂度 $O(24nk)$，总复杂度 $O(24n^2k)$，是 $O(n^3)$ 级的，虽然能过，但依然可以不用二分优化到 $O(n^2)$ 级。

下面是 AC 代码
```cpp
/*
luogu P4663
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n,m,rk,ans,f[65][65][2][2][3][2];
int dig[65],num;

int dp(int x,int j,int a,int b,int lim,int c)
{
	if(j>m)
		return 0;
	if(x==(n+1)/2)
	{
		if(n%2==0)
		{
			if(lim==2)
				return 0;
			j += (a!=b);
			return j<=m ? 1 : 0;
		}
		if(n%2==1)
		{
			int res=0;
			for(int d=0;d<=1;d++)
			{
				if(lim==2 && d>=dig[n/2+1])
					break;
				if(lim==1 && d>dig[n/2+1])
					break;
				int t=(d!=a)+(d!=b);
				if(j+t<=m)
				res++;
			}
			return res;
		}
	}
	if(f[x][j][a][b][lim][c]>=0)
		return f[x][j][a][b][lim][c];
	int res=0;
	for(int a1=0;a1<=1;a1++)
	for(int b1=0;b1<=1;b1++)
	{
		if(lim>=1 && a1>dig[x])
			break;
		int t=0,c1=c;
		if(x<n)
		{
			if(a!=a1)
				t++;
			if(b!=b1)
				t++;
		}
		if(a1>b1 && c==1)
			continue;
		if(a1==b1)
			c1 = c;
		if(a1<b1)
			c1 = 0;
		if(lim==0)
			res += dp(x-1,j+t,a1,b1,lim,c1);
		else
		{
			int lim1=lim;
			if(a1<dig[x])
				lim1 = 0;
			else if(b1>dig[n-x+1])
				lim1 = 2;
			else if(b1<dig[n-x+1])
				lim1 = 1;
			res += dp(x-1,j+t,a1,b1,lim1,c1);
		}
	}
	return f[x][j][a][b][lim][c] = res;
}

int calc(int x)
{
	num = x;
	memset(dig,0,sizeof(dig));
	memset(f,-1,sizeof(f));
	int tmp=x;
	for(int i=1;i<=n;i++)
		dig[i] = tmp%2, tmp /= 2;
	return dp(n,0,0,0,1,1);
}

signed main()
{
	cin>>n>>m>>rk;
	int l=0,r=(1ll<<n)-1;
	while(l<=r)
	{
		int mid=l+r>>1;
		int res=calc(mid);
		if(res>=rk)
			ans = mid, r = mid-1;
		else
			l = mid+1;
	}
	if(calc(ans)<rk)
		return puts("NO SUCH STONE"), 0;
	for(int i=n;i>=1;i--)
		if(ans>>i-1&1)
			cout<<'X';
		else
			cout<<'I';
	
	return puts(""), 0;
}
```

祝大家 AC 愉快！

---

## 作者：tzc_wk (赞：2)

[题面传送门](https://www.luogu.com.cn/problem/P4663)

> ~~A：我该是有多无聊来写这种题的题解啊~~
>
> ~~B：大概是因为这题题解区里没有题解所以我来写一篇了，说明我有高尚的济世情怀（大雾~~

~~跑题了跑题了~~

首先看到字典序第 $i$ 小小可以自然地想到**按位决策**，也就是说从高位到低位枚举，对于每一位我们强制令它为 `I`，看看有多少个符合要求的字符串，如果小于 $i$ 就将这位改为 $1$ 并继续往下枚举。

那么怎么求有多少个符合要求的字符串呢？这时候就要用到 DP 了。显然一个字符串可以成为某个字符串的正规读法当且仅当它的字典序 $\le$ 反串的字典序，因此我们很容易设计出一个 $dp$ 状态：$dp_{i,j,o,x,y}$ 表示当前决策了字符串的前 $i$ 位和后 $i$ 位，有 $j$ 对 `XI` 相邻，$o$ 表示反串字典序是否等于原串字典序，从前往后数第 $i$ 位为 $x$，从后往前数第 $i$ 位为 $y$ 的方案数。转移就枚举第 $i+1$ 位填的数 $u$ 和第 $n-i$ 位填的数 $v$，如果 $o=1$ 且 $u>v$ 就会导致原串字典序 $>$ 反串字典序，不合法。否则显然有如下转移方程式子：

- $dp_{i+1,j+[u\ne x]+[v\ne y],o\land[u==v],u,v}\leftarrow dp_{i,j,o,x,y}$

注意特判 $i+1=n-i$ 的情况和 $i+2=n-i$ 的情况，对于前者而言必须有 $u=v$，因为它俩是同一位，对于后者而言转移的第二维还需额外加上 $[u\ne v]$。

时间复杂度 $32n^3$，跑得飞快（

```cpp
const int MAXN=60;
const char str[3]="IX";
int n,k;ll m,dp[MAXN+5][MAXN+5][2][2][2];
int lim[MAXN+5];
ll calc(){
	memset(dp,0,sizeof(dp));
	for(int a=0;a<2;a++) for(int b=a;b<2;b++){
		if(~lim[1]&&(lim[1]^a)) continue;
		if(~lim[n]&&(lim[n]^b)) continue;
		dp[1][0][a==b][a][b]=1;
	} ll ans=0;
	for(int i=1;(i<<1|1)<=n;i++) for(int j=0;j<=k;j++)
		for(int o=0;o<2;o++) for(int x=0;x<2;x++) for(int y=0;y<2;y++){
			if(!dp[i][j][o][x][y]) continue;
			if((i<<1|1)==n){
				for(int u=0;u<2;u++){
					if(~lim[i+1]&&(lim[i+1]^u)) continue;
					if(j+(u^x)+(u^y)<=k) ans+=dp[i][j][o][x][y];
				}
			} else{
				for(int u=0;u<2;u++) for(int v=0;v<2;v++){
					if(~lim[i+1]&&(lim[i+1]^u)) continue;
					if(~lim[n-i]&&(lim[n-i]^v)) continue;
					if(o&&u>v) continue;
					if((i+1<<1)==n){
						if(j+(u^x)+(u^v)+(v^y)<=k) ans+=dp[i][j][o][x][y];
					} else dp[i+1][j+(u^x)+(v^y)][o&&u==v][u][v]+=dp[i][j][o][x][y];
				}
			}
		}
	return ans;
}
int main(){
	scanf("%d%d%lld",&n,&k,&m);
	if(n==1) return ((m>2)?puts("NO SUCH STONE"):(putchar(str[m-1]))),0;
	if(n==2){
		if(k==0) return ((m>2)?puts("NO SUCH STONE"):(putchar(str[m-1]),putchar(str[m-1]))),0;
		else return ((m>3)?puts("NO SUCH STONE"):((m&1)?(putchar(str[m>>1]),putchar(str[m>>1])):puts("IX"))),0;
	} memset(lim,-1,sizeof(lim));
	if(m>calc()) return puts("NO SUCH STONE")&0;
	for(int i=1;i<=n;i++){
		lim[i]=0;ll sum=calc();
		if(m>sum) m-=sum,lim[i]=1;
	}
	for(int i=1;i<=n;i++) putchar(str[lim[i]]);
	return 0;
}
```



---

## 作者：masonpop (赞：0)

首先一个满足要求的数 $(n,k)$ 一定满足下列条件：若将其写成一个 $n$ 位二进制串，则其一定满足有至多 $k$ 处相邻位置不同，且其字典序小于其反串字典序。

像这种问排名为 $k$ 的数的形式的问题都可以试试二分答案。此时问题转化为，问有多少个这样的数 $\le x$。

一眼数位 DP。设 $f_{i,cnt,c_1,c_2,0/1/2,0/1/2,0/1}$ 表示当前考虑到第 $i$ 位和第 $n-1-i$ 位（显然应该首尾交替填方便转移），首尾两端的数为 $c_1,c_2$，只考虑这一部分的数与上界的大小关系（$3$ 种），以及头部和尾部字典序的大小关系。

转移直接枚举当前两位填什么，然后大力分讨即可。有巨大多细节。

复杂度应该是 $O(n^3)$ 的。[代码](https://www.luogu.com.cn/paste/wrv4ve29)。

---

