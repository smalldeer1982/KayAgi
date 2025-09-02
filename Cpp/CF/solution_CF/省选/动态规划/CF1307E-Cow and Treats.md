# Cow and Treats

## 题目描述

在成功完成一年的牛奶生产后， FJ 决定用奶牛们最爱的美味青草来犒劳它们！

草地上有一排由 $n$ 个单位组成的青草带，每单位青草的甜度为 $s_i$。 FJ 有 $m$ 头奶牛，每头奶牛有最爱的甜度 $f_i$ 和饥饿值 $h_i$。他计划挑选两个互不相交的奶牛子集，分别排列在青草带的左右两侧。两侧的奶牛数量没有限制。这些奶牛将按照以下规则进食：

- 左右两侧的奶牛将按照 FJ 决定的顺序轮流进食。
- 当一头奶牛进食时，它会沿固定方向（不改变方向）前进，并吃掉甜度为 $f_i$ 的青草，直到吃够 $h_i$ 单位为止。
- 当奶牛吃够 $h_i$ 单位青草时，它会立即在该位置入睡，此后其他奶牛无法从任何方向越过它。
- 如果在前进过程中遇到另一头睡着的奶牛或到达青草带的尽头，这头奶牛就会变得烦躁。 FJ 绝对不希望任何奶牛出现烦躁情绪。

注意青草被吃掉后不会再生。此外，为了避免奶牛烦躁， FJ 可以只选择部分奶牛参与进食。

令人惊讶的是，FJ 发现睡着的奶牛满意度最高。在最优安排下，最多能有多少头奶牛入睡？为了实现这个最大入睡数量， FJ 有多少种选择左右两侧奶牛子集的方式（结果对 $10^9+7$ 取模）？只要不引发奶牛烦躁，奶牛的具体派遣顺序不影响计数。

Translated by DeepSeek.

## 说明/提示

在第一个示例中，FJ 可以通过以下方式排列奶牛，使 $2$ 头奶牛睡着：

- 将奶牛 $1$ 排在左侧，奶牛 $2$ 排在右侧。
- 将奶牛 $2$ 排在左侧，奶牛 $1$ 排在右侧。

在第二个示例中，FJ 可以通过以下方式排列奶牛，使 $1$ 头奶牛睡着：

- 将奶牛 $1$ 排在左侧。
- 将奶牛 $2$ 排在左侧。
- 将奶牛 $1$ 排在右侧。
- 将奶牛 $2$ 排在右侧。

在第三个示例中，FJ 可以通过以下方式排列奶牛，使 $2$ 头奶牛睡着：

- 将奶牛 $1$ 和 $2$ 都排在左侧。
- 将奶牛 $1$ 和 $2$ 都排在右侧。
- 将奶牛 $1$ 排在左侧，奶牛 $2$ 排在右侧。
- 将奶牛 $1$ 排在右侧，奶牛 $2$ 排在左侧。

在第四个示例中，FJ 无法让任何奶牛睡着，因此两侧都不会有奶牛排列。

## 样例 #1

### 输入

```
5 2
1 1 1 1 1
1 2
1 3```

### 输出

```
2 2```

## 样例 #2

### 输入

```
5 2
1 1 1 1 1
1 2
1 4```

### 输出

```
1 4```

## 样例 #3

### 输入

```
3 2
2 3 2
3 1
2 1```

### 输出

```
2 4```

## 样例 #4

### 输入

```
5 1
1 1 1 1 1
2 5```

### 输出

```
0 1```

# 题解

## 作者：xiaolilsq (赞：5)

[题目链接](https://www.luogu.com.cn/problem/CF1307E)

由于网上的题解看了好久才懂，所以我打算将详细点并且分析一下代码。

首先要知道，每种甜味的草最多会被两头奶牛吃，从左边过去吃一次，从右边过去吃一次。

由于每个位置只有一种甜味的草，所以每个位置最多只会被一头牛占领，并且这头牛吃的甜味一定是这个位置草的甜味，因此，我们可以单个颜色地处理，最后按照草排列的顺序安排奶牛进入的顺序。

在这$n$个单位的草内，必然会存在一个点$i$，使得从左边进入的牛恰好走到第$i$个位置，从右边进入的牛最多走到$i+1$的位置，因此我们可以枚举这个位置$i$，然后处理每一种颜色，求出从左边恰好走到$i$点的最优方案数，这样就不会有重复。

具体如何操作：

设$slm_s$表示从左边到当前枚举点$i$的甜味为$s$的草的个数，$srm_s$表示从右边到$i+1$的甜味为$s$的草的个数，$num[f][h]$表示要吃不多于$h$个单位甜味为$f$的草的牛的个数。

首先考虑甜味为$s_i$的草，设$x=s_i$，从左边走满足要求有$num[x][slm_x]-num[x][slm_x-1]$头奶牛，从右边走满足要求的有$num[x][srm_x]$头奶牛，因为左边必须要有一头牛，所以如果$slm_x<srm_x$，右边满足要求的牛要少一头安排到左边去。

设左边满足要求的牛数量为$sl$，右边为$sr$，如果$sl=0$即左边没有满足要求的牛，直接跳过，如果$sr=0$即右边没有满足要求的牛，说明这种颜色只能贡献一头牛，方案数贡献乘上$sl$，否则说明左右都有满足要求的牛，这种颜色可以贡献两头牛，方案数贡献乘上$sl\times sr$。

考虑甜味为$s_i$的草的代码：

```cpp
ll testsum=1,testnum=0;int sl,sr;
if(i){
	sl=slm[s[i]],sr=srm[s[i]];
	sr=num[s[i]][sr]-(sr>=sl);
	sl=num[s[i]][sl]-num[s[i]][sl-1];
	if(!sl)continue;
	if(sr)testsum=testsum*sl*sr%mod,testnum+=2;
	else testsum=testsum*sl%mod,testnum++;
}
```

接下来考虑其他甜味的草，同样的，对于颜色$j$，从左边走满足要求的有$num[j][slm_j]$头，从右边走有$num[j][srm_j]$头。

设$sl$为左边满足要求的数量，$sr$为右边的，当$sl=sr=0$时，直接跳过这种甜味；当$sl=sr=1$时，说明左右两边都只有唯一一头满足条件的牛，并且肯定是同一头牛，所以这头牛可以从左边走，也可以从右边走，方案数乘$2$，贡献加上一头牛；否则由于左右两边不能选同一头牛，方案数乘$sl\times sr-\min(sl,sr)$，贡献两头牛。

来段代码压压惊：

```cpp
for(int j=1;j<=n;++j){
	if(j==s[i])continue;
	sl=slm[j],sr=srm[j];
	sr=num[j][sr],sl=num[j][sl];
	if(!sl&&!sr)continue;
	if(!sl||!sr)testsum=testsum*(sl+sr)%mod,testnum++;
	else if(sr==1&&sl==1)
		testsum=testsum*2%mod,testnum++;
	else testsum=testsum*(sl*sr-min(sl,sr))%mod,testnum+=2;
}
```

最后献上$\texttt{AC}$代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
typedef long long ll;
using namespace std;
template<typename T>void read(T &x){
	x=0;int f(1);char c(getchar());
	for(;!isdigit(c);c=getchar())if(c=='-')f=-f;
	for(; isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c-'0');
	x*=f;
}
template<typename T>void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x/10)write(x/10),x%=10;
	putchar(x+'0');
}
const ll mod=1000000007;
ll mo(ll a){
	return a>=mod?a-mod:a;
}
const int maxn=5005;
int num[maxn][maxn],slm[maxn],srm[maxn],s[maxn];
int main(){
	int n,m;
	read(n),read(m);
	for(int i=1;i<=n;++i)
		read(s[i]),++srm[s[i]];
	for(int i=1;i<=m;++i){
		int f,h;
		read(f),read(h);
		++num[f][h];
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			num[i][j]+=num[i][j-1];
	ll anssum=1,ansnum=0;
	for(int i=0;i<=n;++i){
		if(i)++slm[s[i]],--srm[s[i]];
		ll testsum=1,testnum=0;int sl,sr;
		if(i){
			sl=slm[s[i]],sr=srm[s[i]];
			sr=num[s[i]][sr]-(sr>=sl);
			sl=num[s[i]][sl]-num[s[i]][sl-1];
			if(!sl)continue;
			if(sr)testsum=testsum*sl*sr%mod,testnum+=2;
			else testsum=testsum*sl%mod,testnum++;
		}
		for(int j=1;j<=n;++j){
			if(j==s[i])continue;
			sl=slm[j],sr=srm[j];
			sr=num[j][sr],sl=num[j][sl];
			if(!sl&&!sr)continue;
			if(!sl||!sr)testsum=testsum*(sl+sr)%mod,testnum++;
			else if(sr==1&&sl==1)
				testsum=testsum*2%mod,testnum++;
			else testsum=testsum*(sl*sr-min(sl,sr))%mod,testnum+=2;
		}
		if(testnum>ansnum)
			ansnum=testnum,anssum=testsum;
		else if(testnum==ansnum)
			anssum=mo(anssum+testsum)%mod;
	}
	write(ansnum),putchar(' ');
	if(ansnum)write(anssum),putchar('\n');
	else puts("1");
	return 0;
}
```

感觉自己已经讲得够详细了，如果还有什么问题可以在评论区提出来。

---

## 作者：Lynkcat (赞：4)

考虑枚举 $i$ 是左边走的最远的那个人走到的位置，$j$ 是右边走的最远的人走到的位置。然后考虑维护颜色为 $k$ 的人能放到左边的有 $x_k$ 个，右边的有 $y_k$ 个，都能放的有 $z_k$ 个。那么这个颜色能放两个的方案数是 $x_k\times y_k-z_k$。能放一个的方案数是 $x_k+y_k$。这样就能枚举 $[l,r]$ 求出 $i\leq l,r\leq j$ 的方案，二维差分一下是 $O(n^2)$ 的。

但是上述做法貌似并不能通过。因为要求逆元，第一个可以注意到要求逆元的数在 $n^2$ 级别，所以可以线性求逆元。但是貌似线性求逆元会 TLE？？？我流汗了。

然后就是发现枚举 $j$ 没有用，直接钦定一个一定在 $i$ 上就行了，这样逆元也可以直接快速幂了，时间复杂度 $O(n\log n)$。

所以我不能理解啊，出题人为啥不直接 $n$ 开大点，$n$ 开 $5000$ 是什么操作，用来误导选手然后发现自己做法常数过大吗。

[代码](https://codeforces.com/contest/1307/submission/187864681)，这里实现是维护了一个 $cnt_{k,0/1/2/3}$ 表示颜色为 $k$ 的 $4$ 种状态分别有多少个。大同小异。

---

## 作者：DJRzjl (赞：3)

先预处理每头牛从左边、右边走将停留在哪个位置，记做 $l_i,r_i$。

这里将牛喜欢的草味记做牛的颜色 $c_i$，将牛按颜色分类。

显然，每种颜色的牛只能满足不超过两只，且它们的方向相反。

考虑枚举第一头从左边走的牛 $p$，它将把序列分作 $[1,l_p)$ 与 $(l_p,n]$ 两个部分。

之后与 $p$ 同颜色的其他牛只能从右往左走且不能超过 $l_p$，不同色的中从左走的牛的 $l$ 不能超过 $l_p$，从右走的同理。

将不同颜色的牛分开看，因为他们走的顺序无关紧要，所以一定互不影响。

对于颜色 $i(i\not=c_p)$，我们希望能尽量满足 $2$ 头这种牛。

不妨再枚举这里面所有的牛 $x$，记下三个变量：

- $S$ 表示满足 $l_x<l_p$，$r_x>r_p$ 的 $x$ 的数量，这样的牛可以任从两边走；
- $Sl$ 表示满足 $l_x<l_p$，$r_x\le r_p$ 的 $x$ 的数量，这样的牛可以从左边走；
- $Sr$ 表示满足 $l_x\ge l_p$，$r_x>r_p$ 的 $x$ 的数量，这样的牛可以从右边走。

不难发现这三个变量所统计的集合互不相交，事实上 $Sl,Sr$ 不会都有值。（因为对于同颜色的牛 $i,j$，若有 $l_i<l_j$，当且仅当 $r_i>r_j$）。

那么有：

- 当 $S\ge2$ 或者当 $S=1$ 且 $Sl,Sr$ 不都为 $0$ 时，我们可以满足两只牛，方案数为 $S\times(S-1+Sl+Sr)$。
- 否则，当 $S,Sl,Sr$ 有一者不为 $0$，可以满足一只，方案数为 $2S+Sl+Sr$。

对于颜色 $i=c_i$ 也差不多，不再赘述。

对每个 $p$ 把这些颜色的贡献合一起就行，统计出此时最多能选的牛数以及对应方案数。

至此 $O(n^2)$ 解决了问题，已经足已通过，但通过一些预处理以及二分算 $S,Sl,Sr$ 可以优化到 $O(n\log n)$。


---
Code(比较懒只写了 $O(n^2)$)
```cpp
#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
const int N=5e3+10,mod=1e9+7;

int n,m,c[N],a[N],l[N],r[N],tot[N];
vector<int>cp[N],gp[N];

int calc(int x,int p){
	int now=1,sum=(x>0);
	for(int i=1;i<=n;i++){
		int s=0,sl=0,sr=0;
		for(auto v:gp[i]){
			if(v==x) continue;
			if(l[v]<p&&r[v]>p) s++;
			else if(l[v]<p) sl++;
			else if(r[v]>p) sr++;
		}
		if(i==a[x]){
			if(s+sr>0) sum++,now=1ll*now*(s+sr)%mod;
		}else if(s+(sl>0||sr>0)>=2) sum+=2,now=1ll*now*s*(s-1+sl+sr)%mod;
		else if(s+sl+sr) sum++,now=1ll*now*(s*2+sl+sr)%mod;
	}
	(tot[sum]+=now)%=mod;
	return sum;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",c+i),cp[c[i]].pb(i);
	for(int i=1,s;i<=m;i++){
		scanf("%d%d",a+i,&s);
		if(s>cp[a[i]].size()) continue;
		l[i]=cp[a[i]][s-1];
		r[i]=cp[a[i]][cp[a[i]].size()-s];
		gp[a[i]].pb(i);
	}
	int ans=calc(0,0);
	for(int i=1;i<=n;i++)
		for(auto v:gp[i]) ans=max(ans,calc(v,l[v]));
	printf("%d %d\n",ans,tot[ans]);
	return 0;
}
```


---

## 作者：SFlyer (赞：0)

首先同一种颜色的牛最多会满足两只。我们可以很简单的求出，一头牛从右边/左边走到达的地方。

这个题要求出一个不算重的方法啊，否则去重太麻烦了。那么我们发现被吃掉的草是一定是先被左边的牛吃，一个分界点后被右边的牛吃。可以枚举这个分界点。然后就不会算重了。

枚举了分界点（第一个左边的牛），首先保证答案最大。发现我们决定了左右以后，我么按照离分界点距离排序了以后一定是可行的，因为有“都不完全相同”这个条件。特别的，不同喜好的牛可以分开考虑。那么，求出左右两边都可以的，只能左边的，只能右边的。计算答案是 trivial 的。

特殊的，有可能一个左边的也没有。

---

