# [ABC267G] Increasing K Times

## 题目描述

给定一个正整数序列 $A=(a_1,a_2,\ldots,a_n)$，问有多少个 $1\sim n$ 的排列 $P=(p_1,p_2,\ldots,p_n)$ 满足：

- 存在恰好 $k$ 个整数 $i(1\leqslant i\leqslant n-1)$ 满足 $a_{p_i}<a_{p_{i+1}}$

对 $998244353$ 取模。

## 说明/提示

$2\leqslant n\leqslant 5000,0\leqslant k\leqslant n-1,1\leqslant a_i\leqslant n$

**样例解释**

只有四个排列 $P$ 满足条件，分别是 $(1,3,2,4),(1,4,2,3),(2,3,1,4),(2,4,1,3)$。

## 样例 #1

### 输入

```
4 2
1 1 2 2```

### 输出

```
4```

## 样例 #2

### 输入

```
10 3
3 1 4 1 5 9 2 6 5 3```

### 输出

```
697112```

# 题解

## 作者：DengDuck (赞：15)

先给数列从小到大排个序。

接下来设 $f_{i,j}$ 表示前 $i$ 个数的排列形成 $j$ 个上坡的方案数。

接下来考虑转移，分为插入第 $i$ 个数后增加上坡和不增加上坡两种情况。

对于不增加的情况，有三种可能：

- 第 $i$ 个数插入在了数列的最前端，有 $1$ 种方案。
- 第 $i$ 个数插入在了一个上坡的中间，因为上坡中较小的那个数字必定小于第 $i$ 个数，形成一个上坡，较大的那个数字必定小于等于第 $i$ 个数，不形成上坡，而我们拆散了一个上坡，故没有增加，有 $j$ 种方案。
- 第 $i$ 个数插入在了数值相同的数后面，这个记为 $same_i$，有 $same_i$ 种方案。

对于增加的情况，就是减去这三种情况了，不过增加了，就说明原来只有 $j-1$ 个上坡，这里和上面不太一样。

整理式子，得：

$$ 
f_{i,j} = f_{i-1,j-1} \times (i - j - same_i) + f_{i-1,j} \times (1 + j + same_i)
$$

这样就可以 $O(n^2)$ 求得了,可以用滚动数组。



```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, a[5005], f[5005], same[5005], sum;
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        if (a[i] == a[i - 1])
            same[i] = same[i - 1] + 1;
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i - same[i]; j >= 1; j--) {
            f[j] = f[j - 1] * (i - j - same[i]) % 998244353 + f[j] * (1 + j + same[i]) % 998244353;
            f[j] %= 998244353;
        }
        f[0] = f[0] * (1 + same[i]) % 998244353;
    }
    cout << f[k] << endl;
}
```

# After Increasing K Times

过了一段时间重新看了一下这道题，发现有几个优化，也顺便介绍一下。

首先，我们发现 $n$ 很大，但是数值区间很小，所以考虑使用桶排序，因为数字在 $[1,n]$,所以排序复杂度为 $O(n)$。

然后，我们发现枚举区间可以缩小，因为我们并不是全都需要，简单用一个图表示：

![](https://cdn.luogu.com.cn/upload/image_hosting/8atzkj69.png)

左边是我们需要的值，右边是不需要的。

那么，有用的状态的区间边界很好推算，是 $[k+n-i+1,k]$，这个优化可以减少接近一半的时间。

以上优化让代码大大提速，获得了洛谷最优解，在 AtCoder 排名第二（截至2022.11.23）。

第一名本人丧心病狂卡常也卡不过，快了 4ms，但是本代码很短，最快代码使用了 IDFT。

```cpp
#include <stdio.h>
inline int read() {
    char c = getchar();
    int sum = 0;
    while (c < '0' || c > '9') c = getchar();
    do {
        sum = (sum << 3) + (sum << 1) + c - '0';
        c = getchar();
    } while (c >= '0' && c <= '9');
    return sum ;
}
int n, k,s[5005],b[5005],t=1;
long long f[5005];
int main() {
    n=read(),k=read();
    for (int i = 1; i <= n; i++)b[read()]++;
    for(int i=1;i<=n&&t<=n;i++)
    {
    	if(b[i])b[i]--,t++;
    	while(b[i])b[i]--,s[t] = s[t - 1] + 1,t++;
	} 
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
		int r=(k>i-s[i])?(i-s[i]):k,l=(k-n+i-1>1)?(k-n+i-1):1;
        for (int j = r; j >= l; j--) {
            f[j] = f[j] * (j + s[i] + 1) + f[j - 1] * (i - j - s[i]) ;
            f[j] %= 998244353;
        }
        f[0] = f[0] * (s[i] + 1) % 998244353;
    }
    printf("%lld\n",f[k]);
    return 0;
}
```

---

## 作者：Expert_Dream (赞：14)

[博客园](https://www.cnblogs.com/gsczl71/p/17880643.html)。
### 题目描述

给定一个正整数序列 $A=(a_1,a_2,\ldots,a_n)$，问有多少个 $1\sim n$ 的排列 $P=(p_1,p_2,\ldots,p_n)$ 满足：

- 存在恰好 $k$ 个整数 $i(1\leqslant i\leqslant n-1)$ 满足 $a_{p_i}<a_{p_{i+1}}$。

### 思路

有那么一点点抽象，但是还是可以理解的。

我们不妨将问题转化一下：将 $a$ 数组重排变成 $b$，然后 $b$ 上有 $k+1$ 个连续的不上升序列（递减）。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ngp28qnb.png)

这一张图片中黑色点代表着每一个 $a_i$ 的值，然后蓝色的线段代表着每一对 $a_{p_i}<a_{p_{i+1}}$，红色的线段则是**连续的不上升序列**，然后第 $i$ 个连续的不上升序列的开头和第 $i-1$ 个连续的不上升序列的结尾可以形成一对（$a_{p_i}<a_{p_{i+1}}$）。相当于要 $k+1$ 个连续的不上升序列。

因为 $a$ 的顺序不重要，不妨先**排序**。

我们可以理解，每一次加入的 $a_i$ 有两种情况：

- 第一种 $a_i$ 加在所有数之前。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/3alt42my.png)

图中绿色点为新加入的点，由于这个点肯定是目前最大（大于等于其他点）。肯定能与目前的第一个点的红色线段连在一起（即蓝色线段），换句话说，就是这种情况连续的不上升序列是**不变**的。

- 第二种 $a_i$ 加在中间。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/lx9t7451.png)

图中蓝色的点加入使得一个红色的线段变成了两个独立的线段，所以说连续的不上升序列加一。

但是，聪明的你会发现：如果有重复怎么办？

![](https://cdn.luogu.com.cn/upload/image_hosting/3yc4n9b5.png)

例如，这个是第一种情况，如果有相等的点那么我们可以有多种可能，图中的绿色点都是合法的方案。假设之前已经有 $vis_x$ 个点等于 $x$，那么此时必将是可以放在 $vis_x+1$ 个位置上，$1$ 是之前的连续不上升序列的个数。所以，我们只需要实时维护 $vis$ 即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/cib01yxr.png)

这是第二种情况。从图中可知这个点只能放在绿色位置，不能放在橙色位置，为啥呢，因为它等于了，所以没办法多造一个连续的不上升序列了。那么方案数就是 $i-j+1-vis_x$，$i-j+1$ 就是正常的空位的个数，然而 $vis_x$ 个数挡住了，于是就减掉。

这样我们就可以得到状态转移方程了，使用 DP 进行状态转移，时间复杂度 $O(nk)$。通过咯。

[link](https://atcoder.jp/contests/abc267/submissions/48884763)。

---

## 作者：EricWan (赞：8)

神仙题目，通过 [Expert_Dream](https://www.luogu.com.cn/user/768530) 的[题解](https://www.luogu.com.cn/article/bcrvd09e)和 [DaiRuiChen007](https://www.luogu.com.cn/user/539618) 的[题解](https://www.luogu.com.cn/article/7cy7any3)学明白了这道题。

---

设数组 $b$ 满足 $b_i=a_{p_i}$。

我们发现，$a$ 的顺序对答案无影响，这是显然的。

对 $a$ 进行排序，通过~~题解~~数据范围，我们可以使用 DP，其中 $dp_{i,j}$ 代表已经分配完成排完序后的 $a_{1\dots i}$，形成了 $j$ 段极大不升子段。答案就是 $dp_{n,k+1}$，因为 $b$ 会出现上升当且仅当这个位置是两个极大不上升子段的分界。

我们再定义 $s_i$ 为排完序后的 $a$ 中 $a_{1\dots i-1}$ 中与 $a_i$ 相等的数的数量，后面会用。

这里我们考虑主动转移（我做插入 DP 喜欢写主动转移）。

### 先不考虑出现相等的数的情况

将 $b$ 画出来。这 $j$ 段极大不上升子段差不多长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/9vqobjfz.png)

观察发现，一共有四种可能的插入新点的类型

![](https://cdn.luogu.com.cn/upload/image_hosting/9ap15k8f.png)

橙色：最前边，因为它是最大的，所以对 $j$ 无影响，转移系数（方案数）是 $1$。

黄色：一个段的中间，因为它很大，所以会将当前段割开，$j\leftarrow j+1$，转移系数是段内的空位数。

绿色：一个段的前面，和黄色差不多，又因为在前面的一个数一定小于新加入的数，$j$ 不变，转移系数为 $j-1$。（后面会将橙色与绿色合并，统一叫做绿色）

蓝色：在最后加一段，$j\leftarrow j+1$，转移系数是 $1$。

于是我们就可以快快乐乐的写出过不了样例的代码了。

### 考虑重复数的情况

当前这批数会在每一段前面形成一段平台。像这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/2hpink48.png)

重新看我们刚才的分类

黄色：如果每一段还是单调下降的，我们可以在段内部的任意一个地方撕裂一段，但是对于有 $pre$ 个 $a_{i+1}$ 作为前缀的段，我们就不能在那些 $a_{i+1}$ 后撕裂当前段。但是对于全都是 $a_{i+1}$ 的段而且是最后一个段，我们希望可以裂开的地方有 $pre-1$ 个，但是其中有 $pre$ 个地方不能裂开，所以我们实际可以裂开的地方有 $-1$ 个（？），先留着这个 BUG 后面再说。

绿色：完全相同。

蓝色：如果最后一个段不全是 $a_{i+1}$，完全相同，转移系数是 $1$；如果最后一段是一坨 $a_{i+1}$，我们就不能在序列最后生出一个新的极大不上升子段，转移系数在这种情况下需要减一，这种情况就刚好对应了上面（黄色）的 BUG，我们还是转移 $1$ 就可以，神仙！

### 转移系数分析

绿色情况：$dp_{i,j}$ 向 $dp_{i+1,j}$ 转移 $j$。

黄色情况：撕不开，$dp_{i,j}$ 向 $dp_{i+1,j}$ 转移 $\sum pre=s_{i+1}$；撕得开，向 $dp_{i+1,j+1}$ 转移 $i-j-s_{i+1}$。

蓝色情况：$dp_{i,j}$ 向 $dp_{i+1,j+1}$ 转移 $1$。

最后我们才可以快快乐乐地写出过的了数据的代码。

[代码](https://atcoder.jp/contests/abc267/submissions/64457254)非常优雅，不到一个 KB。

---

## 作者：LinkWish (赞：4)

刚学完二项式反演，新题做不动了回来补计数dp，结果发现这题不是二项式反演板子题吗？

先将 $a$ 排序，考虑将 $a$ 中元素升序插入排列中，的设 $dp_{i,j}$ 为插入了 $i$ 个数后至少有 $j$ 个满足 $a_{p_i}<a_{p_{i+1}}$ 的排列的方案数（先不考虑其他元素）。设当前元素为 $i$，有 $x$ 个元素严格小于 $a_i$，则转移方程则为 $dp_{i,j}=dp_{i,j-1}+(x-j+1)\times dp_{i-1,j-1}$。

因为刚刚没有考虑没有被选中的其他元素，所以为了考虑进去其他元素，现在设 $f(i)=(n-i)!\times f_{n,i}$。

设 $g(i)$ 为满足 $(\sum\limits^{n-1}_{j=1} [a_{p_j}<a_{p_{j+1}}])=i$ 的排列的方案数，显然 $f(i)=\sum\limits^n_{j=i}\binom{j}{i}g(i)$，由二项式反演可知 $g(i)=\sum\limits^{n}_{j=i}(-1)^{j-i}\binom{j}{i}f(i)$。答案即为 $g(k)$，时间复杂度为 $\Theta(n^2)$。

程序只给出主体部分，主要是前面一部分的模板有一些影响观感，而且给出主体已经能够辅助理解。

```cpp
//Linkwish's code
const int N=5005,jqh=998244353;
int n,m;
int a[N];
int f[N][N];
inline int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=x*res%jqh;
		x=x*x%jqh;
		y>>=1;
	}
	return res;
}
int p[N],inv[N];
inline void init(){
	p[0]=1;
	for(int i=1;i<=n;i++)p[i]=p[i-1]*i%jqh;
	inv[n]=qpow(p[n],jqh-2);
	for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1)%jqh;
}
inline int c(int x,int y){
	return p[x]*inv[y]%jqh*inv[x-y]%jqh;
}
signed main(){
	read(n),read(m);
	init();
	for(int i=1;i<=n;i++)read(a[i]);
	sort(a+1,a+1+n);
	int now=0;
	for(int i=1;i<=n;i++){
		while(a[now+1]<a[i])now++;
		f[i][0]=1;
		for(int j=1;j<=now;j++)
			f[i][j]=(f[i-1][j]+f[i-1][j-1]*(now-j+1)%jqh)%jqh;
	}
	for(int i=0;i<=n;i++)f[n][i]=f[n][i]*p[n-i]%jqh;
	int ans=0;
	for(int i=m;i<=n;i++){
		if((i-m)&1)ans=(ans-c(i,m)*f[n][i]%jqh+jqh)%jqh;
		else ans=(ans+c(i,m)*f[n][i]%jqh)%jqh;
	}
	writeln(ans);
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：3)

# ABC267G 题解

## 思路分析

考虑转化原操作成：在一个空序列中顺次插入 $a_1\sim a_n$，注意到 $a_1\sim a_n$ 的顺序不影响答案，故设 $a_1\sim a_n$ **单调不降**

此时设 $dp_{i,j}$ 表示插入 $a_1\sim a_i$，其中有 $j$ 对 $a_{k-1}<a_k$ 的方案数，记 $cnt_k$ 表示 $a_1\sim a_i$ 中有几个个值为 $k$ 的数

考虑插入 $a_{i+1}$ 的时候，什么时候不改变 $a_{k-1}<a_k$ 的数对的数量

1. 插入了一个值与 $a_{i+1}$ 相同的数的后面，有 $cnt_{a_{i+1}}$ 种情况
2. 插入了一对 $a_{k-1}<a_k$ 的中间，变成 $a_{k-1}<a_i\ge a_k$，显然增加一对减少一对，不改变总数，有 $j$ 种情况
3. 插入最前面，有 $1$ 种情况

共有 $cnt_{a_{i+1}}+k+1$ 种情况

注意到插入 $a_{i+1}$ 总共有 $i+1$  种情况，相减可得：插入 $a_{i+1}$ 后增加一对 $a_{k-1}<a_k$ 的方案数有 $i-cnt_{a_{i+1}}-k$ 种

因此直接刷表转移即可，边界条件 $dp_{0,0}=1$

可以用滚动数组优化掉第一维，空间复杂度 $\Theta(n)$

时间复杂度 $\Theta(nk)$

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=5005,MOD=998244353;
int a[MAXN],dp[MAXN][MAXN],cnt[MAXN];
signed main() {
	int n,k;
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	dp[0][0]=1;
	for(int i=0;i<n;++i) {
		int cur=i&1,nxt=cur^1;
		memset(dp[nxt],0,sizeof(dp[nxt]));
		for(int j=0;j<=k;++j) {
			dp[nxt][j]=(dp[nxt][j]+dp[cur][j]*(j+cnt[a[i+1]]+1)%MOD)%MOD;
			dp[nxt][j+1]=(dp[nxt][j+1]+dp[cur][j]*(i-j-cnt[a[i+1]])%MOD)%MOD;
		}
		++cnt[a[i+1]];
	}
	printf("%lld\n",dp[n&1][k]);
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc267_g)

## 思路

很傻逼的 $\rm G$，当时我不会，补题的时候秒了。

转换题意为将序列 $a$ 重排，不妨设 $b$ 为重排后的 $a$ 序列，现在将 $b$ 划分成若干不上升连续段，求段数恰好为 $k+1$ 的方案数。

容易发现此时序列 $a$ 的顺序没有任何用，我们直接 $\rm sort$ 一下，变成从小往大加数。

此时我们分两种情况讨论：

+ $a_i$ 加到了某一段段头的左边，此时段数不会增加。

+ $a_i$ 加到了某一段中间，此时会新增一段。

注意会出现 $a_i$ 有相同的情况，此时 $a_i$ 加到前面与 $a_i$ 相同的那些段段头右边段数也不会增加，稍微搞一搞就好了。

然后就结束了，非常简单，时间复杂度 $\mathcal O(nk)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=5e3+10;
int const mod=998244353;
int a[N],f[N][N],vis[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,k;cin>>n>>k;++k;
	for (int i=1;i<=n;++i) cin>>a[i];
	sort(a+1,a+n+1);f[0][0]=1;
	for (int i=1;i<=n;++i){
		for (int j=0;j<=min(i,k);++j)
			f[i][j]+=f[i-1][j]*(j+vis[a[i]])%mod,f[i][j]%=mod;
		for (int j=1;j<=min(i,k);++j)
			f[i][j]+=f[i-1][j-1]*(i-(j-1)-vis[a[i]])%mod,f[i][j]%=mod;
		++vis[a[i]];
	}
	cout<<f[n][k]<<'\n';
	return 0;
}
```

---

## 作者：Silviasylvia (赞：3)

一个几乎不需要思考的做法，就是单纯的按照题意硬做。

按照套路，我们从小到大放数。为了方便，我们称一个 $b_i<b_{i+1}$ 为山峰。先考虑所有数都不同的情况下，$dp_{i,j}$ 表示放了前 $i$ 个数，当前有 $j$ 个山峰的方案数。我们发现这样非常好转移。我们考虑当前用 $dp_{i-1,j}$ 转移，那么转移的时候，你有 $j+1$ 个位置可以让山峰不变（插第一个或者某一个山峰中间），$i-j-1$ 个位置可以让山峰 $+1$。直接 $n^2 \ \ \ dp $ 就可以了。

然后考虑推广到有重复数的情况，设 $dp_{i,j}$ 表示前 $i$ 种数有 $j$ 个山峰的方案数。你考虑转移的时候枚举一个 $t$，表示 $i$ 这种数会使得数列增加 $t$ 个山峰，考虑到 $\sum t=n$，因此如果可以 $O(1)$ 转移还是不会出问题。实际上转移就是 $dp_{i-1,j}\to dp_{i,j+t}*y$，$y$ 表示转移系数，我们只考虑求转移系数即可。

再定义 $num_i$ 表示第 $i$ 种数的个数，$sum_i$ 表示前 $i$ 种数的个数和。你考虑这个转移系数就是必须选择 $t$ 个可以使得山峰 $+1$ 的位置，$num_i-t$ 个可以使得山峰不变的位置去插入。

首先把所有 $i$ 的数都看做相同的，答案最后乘以一个 $(num_i)!$ 即可。观察再发现，你在每一个位置的后面如果插入了 $k$ 个数（$k>1$)，等价于只插入 $1$ 个。那么你可以把当前状态（$dp_{i-1,?}$ 的状态）中的**每一个空位外加第一个前面**都看做一个盒子。于是这个转移系数就转化成了你需要把 $num_i$ 个相同的球放入 $sum_{i-1}+1$ 个不同的盒子，这其中有 $sum_{i-1}-j$ 个特殊盒子，你必须保证放完球后**恰好** $t$ 个特殊盒子非空的方案数。

考虑直接列出式子，特殊盒子恰好 $t$ 个我们考虑直接钦定，方案数是 $\binom{num_{i-1}-j}{t}$，然后我们考虑枚举有 $q$ 个**非空非特殊盒子**，然后再放球，那么方案数就是 $\sum_{q}\binom{j+1}{q}\binom{num_{i}-1}{t+q-1}$，这式子的意义就是，前者是选 $q$ 个盒子的方案数，后者就是放球问题的方案数。

然后发现后面这个东西可以范德蒙德卷积一下，就做完了。转移系数就是 $(num_i!)\binom{sum_{i-1}-j}{t}\binom{num_i+j}{t+j}$。

复杂度 $O(n^2)$。

不怎么好看的代码：

```cpp
signed main()
{
	int T=1;
	pre();
	while(T--)
	{
		rdn;rdk;upn rd(a[i]);sort(a+1,a+n+1);
		dp[0][0]=1;
		int tot=1;
		up(i,2,n)
		{
			if(a[i]!=a[i-1])
			{
				c[++m]=tot;tot=0;
			}
			tot++;
		}
		c[++m]=tot;
		int sm=0;
		up(i,1,m)
		{
			//前i段
			up(j,0,n)
			{
				if(!dp[i-1][j])continue;
				int w1=j+1;
				int w2=sm-j;
				up(t,0,min(c[i],w2))
				{
					int w3=c[i]-t;
					int res=0;
					int q=C(w2,t);
					int rw=min(w3,w1);
					res+=C(w1+c[i]-1,w1+t-1);res+=mod;res%=mod;
					Add(dp[i][j+t],res*fac[c[i]]%mod*dp[i-1][j]%mod*q%mod);
				}
			}
			sm+=c[i];
		}
		cout<<dp[m][k];
	}
}
```

---

## 作者：冷却心 (赞：1)

容易发现这个数数和原数组顺序无关，首先对原数组排序，从小往大插入数。

我们记 $f_{i,j}$ 表示插入了前 $i$ 个数，有 $k$ 个位置满足小于的关系。然后考虑转移。我们后面插入一个数，注意到要么使得满足小于的位置数不变，要么加一。我们记 $c$ 表示前 $i$ 个数中等于第 $i$ 个数的数的个数，有转移：

- $f_{i-1,j}\times(j+c)\rightarrow f_{i,j}$，因为把当前这个数填在这 $j$ 个满足小于的位置之后能发现满足的位置个数仍然不变，或者把当前数填在和他相同的 $c-1$ 个数之后，或者序列开头，也不变，一共 $(j+c)$ 中填法。
- $f_{i-1,j}\times(i-j-c)\rightarrow f_{i,j+1}$，除去上一种情况的位置都会使得合法位置加一。

初始值 $f_{1,0}=1$，最后答案就是 $f_{n,k}$。于是做完了。代码很简单。

*锐评一下你谷评级，紫也是神人了，感觉只有蓝啊，都能被我做出来。*

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const LL MOD = 998244353;
const int N = 5e3 + 10;
int n, K, A[N]; LL DP[N][N];

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> K;
	for (int i = 1; i <= n; i ++) cin >> A[i];
	sort(A + 1, A + 1 + n); DP[1][0] = 1;
	for (int i = 1, c = 1; i < n; i ++) {
		if (A[i] != A[i + 1]) c = 1;
		else ++ c;
		for (int j = 0; j < i; j ++) {
			(DP[i + 1][j] += DP[i][j] * (c + j) % MOD) %= MOD;
			(DP[i + 1][j + 1] += DP[i][j] * (i + 1 - c - j) % MOD) %= MOD;
		}
	} cout << DP[n][K] << "\n";
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

其实是想求：将原序列任意打乱，然后在序列的每两个数之间根据他们的大小关系插入 `>=` 和 `<`，问有多少种打乱方式使得恰好有 $k$ 个 `<`。

首先你要会 [P2401](https://www.luogu.com.cn/problem/P2401)。（划掉

考虑从小到大进行插入元素。

设 $dp_{i,j}$ 表示前 $i$ 个数有 $j$ 个 `<` 的方案。

当前数插入后最多产生一个 `<`，就是说将会从 $dp_{i-1,j-1}$ 与 $dp_{i-1,j}$ 转移而来。现在主要关心转移的系数是多少。

如果插在某个 `<` 之前或最前面，因为现在这个数是最大的，只会出现 `>=`，那 `<` 个数不变，即 $(1+j)dp_{i-1,j}$。设前面与当前数相等的个数为 $c$，插在这些位置也是一样的，贡献为 $c\cdot dp_{i-1,j}$。那除开这些位置，剩下的 $i-j-c$ 个位置插入就会多出来一个 `<`，也即贡献为 $(i-j-c)dp_{i-1,j-1}$。

所以转移方程为：$dp_{i,j}=(j+1+c)dp_{i-1,j}+(i-j-c)dp_{i-1,j-1}$。

做完了。初始化 $dp_{0,0}=1$，答案为 $dp_{n,m}$。

# Code

```cpp
#include<bits/stdc++.h>
const int mod=998244353;
int dp[5005];
int a[5005];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;scanf("%d",&a[i++]));
	std::sort(a+1,a+n+1);
	dp[0]=1;
	for(int i=1,c;i<=n;++i){
		if(a[i]!=a[i-1])c=-1;++c;
		for(int j=m;j;--j)
			dp[j]=(dp[j]*(j+1ll+c)+1ll*dp[j-1]*(i-j-c))%mod;
		dp[0]=(dp[0]*(1ll+c))%mod;
	}
	printf("%d",dp[m]);
	return 0;
}
```

---

## 作者：CrTsIr400 (赞：0)

[[ABC267G] Increasing K Times](https://www.luogu.com.cn/problem/AT_abc267_g) 

显然可以给 $A$ 排序，这样很方便计算，然后问题就类似 P2401，但是我们需要判重。

回忆一下 P2401，设 $f_{i,j}$ 为插入了 $i$ 个数，且小于号出现 $j$ 次的方案数。

考虑到什么情况下**会**新增小于号：

+ 插入在某个**大于等于符号**的后面。此时方案数为 $(i-1)-(j-1)-1=i-j-1$。
+ 插入在**整个序列**的最后面。此时方案数为 $1$。
+ 前两个方案没有判等，所以会有等于符号的出现，要剔除一些。
+ 所以我们维护：序列中前 $(i-1)$ 个数有 $same_i$ 个 $A_i$，那么上述的方案数还要减去 $same_i$。
+ 于是这里的转移就是 $f_{i,j}=(i-j-same_i)\times f_{i-1,j-1}$。

不会新增小于号的同理，这里不再赘述。代码就很容易写出来了。

```cpp
#include<bits/stdc++.h>
#include<atcoder/modint>
#define fo(i,a,b) for(I i(a),_ed(b);i<=_ed;++i)
using namespace std;using I=int;using LL=long long;using V=void;
const I N=5005;
atcoder::modint998244353 f[2][N];
I n,k,a[N],same[N];
I main(){ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	fo(i,1,n)cin>>a[i];
	sort(a+1,a+n+1);
	f[0][0]=1;
	fo(i,1,n){
		I cur=i&1,las=cur^1;
		same[i]=(a[i]==a[i-1])?same[i-1]+1:0;
		fo(j,0,i-same[i]){
			if(j)f[cur][j]=f[las][j-1]*(i-j-same[i]);else f[cur][j]=0;
			f[cur][j]+=f[las][j]*(1+j+same[i]);
		}
	}printf("%d\n",f[n&1][k].val());
	return 0;}
```



---

