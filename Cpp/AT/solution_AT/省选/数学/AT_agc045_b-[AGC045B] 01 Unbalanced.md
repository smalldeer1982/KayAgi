# [AGC045B] 01 Unbalanced

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc045/tasks/agc045_b

文字列 $ S $ が与えられます． $ S $ の各文字は，`0`,`1`,`?` のいずれかです．

$ S $ に含まれる全ての `?` を `0` か `1` に変えて（`?` ごとに変換後の文字を選択できます），文字列 $ S' $ を作ることを考えます． ここで，$ S' $ のアンバランス度を，次のように定義します．

- $ S' $ のアンバランス度 $ =\ \max\ \{\ S' $ の $ l $ 文字目から $ r $ 文字目までに含まれる `0` の個数と `1` の個数の差の絶対値 $ :\ 1\ \leq\ l\ \leq\ r\ \leq\ |S|\} $

$ S' $ のアンバランス度としてありうる最小の値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 10^6 $
- $ S $ の各文字は `0`,`1`,`?` のいずれかである．

### Sample Explanation 1

$ S'= $`010` とすれば，アンバランス度は $ 1 $ になり，これが最小です．

## 样例 #1

### 输入

```
0??```

### 输出

```
1```

## 样例 #2

### 输入

```
0??0```

### 输出

```
2```

## 样例 #3

### 输入

```
??00????0??0????0?0??00??1???11?1?1???1?11?111???1```

### 输出

```
4```

# 题解

## 作者：Tokai__Teio (赞：8)


## [[AGC045B] 01 Unbalanced](https://www.luogu.com.cn/problem/AT_agc045_b)

~~先推一手广告~~，[更好的阅读体验](https://undead-fire-ace.github.io/2023/08/22/unbalanced/)。

### 题意：

给定一个字符串，其中 $\texttt{?}$ 可以替换成 $0$ 或 $1$。让最小化 $0$ 和 $1$ 的数量差。

### 分析：

一般对于最小化最大值的题，往往都可以用二分去做，（~~但是这道题的二分的 check 函数我不会写~~），那么就想一想有没有什么平替，我们可以想到贪心和 dp 也是可以解决类似的问题的，我们可以考虑因为是跟个数有关且只有两个不同的数，那么我们就可以将 $0$ 看成是 $-1$，$1$ 是 $+1$，然后就转换成了最小化最大的累积和与最小的累积和的差值。先可以设，在累计和最大值不超过 $limit$ 时，$f_{limit}$ 为最大累计和的最小值，$g$ 为最小累计和的最大值，那么我们的答案就是求 $\min \left\{limit - f_{limit}\right\}(g\leq limit)$。

然后我们需要去求 $g$，对于求 $g$，我们可以贪心的去求解，在一开始我们先将所以的问号都设置成 $-1$，然后在检查一遍，如果累计和不超过我们的 $limit$ 的话，就将 $-1$ 变成 $1$。

那么这样贪心为什么是正确的呢？

当 $limit$ 增加 $2$ 时，最多只有一个 $\texttt{?}$ 发生变换，所以 $f_{limit+2}\leq f_{limit}+2$，那么 $limit-f_{limit+2}\leq (limit+2)-(f_{limit}+2)$，那么我们最终的答案为 $\min \left\{limit-f_{limit} \right\} \leq \min \left\{ (limit+2)-f_{limit+2} \right\}$。

那么正确性保证了，最后的答案也就是 $\min(g-f_{g},(g+1)-f_{g+1})$。

代码实现起来也是比较容易的，一些细节也在代码中标注了。

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>

namespace read_write   //快读快写可以忽略
{
    template <typename T>
    inline void read(T &x)
    {
        x = 0;
        T f = 1;
        char ch = getchar();
        while (ch > '9' || ch < '0')
        {
            if (ch == '-')
                f = -1;
            ch = getchar();
        }
            while (ch >= '0' && ch <= '9')
                x = x * 10 + ch - '0', ch = getchar();
        x *= f;
        return;
    }

    template <typename T>
    inline void write(T x)
    {
        if (x < 0)
        {
            x = -x;
            putchar('-');
        }
        if (x > 9)
            write(x / 10);
        putchar(x % 10 + '0');
    }

    template <typename T>
    T max(T x, T y)
    {
        return x > y ? x : y;
    }

    template <typename T>
    T min(T x, T y)
    {
        return x > y ? y : x;
    }

    template <typename T>
    void swap(T &a, T &b)
    {
        T tem = b;
        b = a;
        a = tem;
    }
}

namespace Solve
{
    using namespace read_write;

    const int N = 1e6 + 10;

    std::string a;
    int sum[N];   //记录后缀中1的个数(与0抵消之后的个数)
    int len;

    int calc(int limit)
    {
        int cnt, mn;
        cnt = mn = 0;

        for(int i = 1 ; i <= len ; ++ i)
        {
            if(a[i] == '0')
                cnt --;
            else if(a[i] == '1')
                cnt ++ ;
            else 
            {
                if(cnt + sum[i + 1] + 1 <= limit)
                    cnt ++;
                else 
                    cnt --;
            }

            mn = min(mn, cnt);    //计算f[g]
        }

        return limit - mn;
    }

    void solve()
    {
        std::cin >> a;
        len = a.size();
        a = ' ' + a;   //在字符串前加个空格，调整下标（个人习惯

        for(int i = len ; i >= 1 ; -- i)
            sum[i] = max(0, sum[i + 1] + (a[i] == '1' ? 1 : -1));   //在计算1的个数时也将 '?' 看成是0
        write(min(calc(sum[1]), calc(sum[1] + 1)));   //分别计算0多和1多的情况
    }
}

int main()
{
    Solve::solve();

    return 0;
}
```


---

## 作者：Vasily0959 (赞：5)

超级大典题，从头到尾几乎每一步都是经典套路。

**我们把 $0$ 变成 $-1$，这样不平衡度就变成了新序列前缀和的极差。（经典套路：区间计数类限制转前缀和）**

**先尝试固定最大值（经典套路：固定一端考虑另一端）**，思考如何让最小值最大。

**尝试调整，先把所有的 ? 都设为 $-1$（经典套路：先构造一个初始状态再尝试贪心优化）**，先做一遍前缀和，求出后缀 $max$，之后遇到有抬升空间的 $-1$ 都抬升成 $1$ (调整法易证这一定不劣)。

这样对于每个最大值 $m$ 我们都能构造出最优的最小值，设为 $f(m)$。

现在我们有了一个 $O(n^2)$ 的做法，我们尝试把枚举最大值这一步干掉。

此处应该先**打个表找找规律（经典套路：打表）**，不难看出 $f$ 似乎是单增的。考场上肯定大胆猜想不用求证，有啥问题拍就完了 **（经典套路：少证一点，你在打比赛）**

但我们这里尝试刻画这个东西，发现对于 $m$ 和 $m+2$，构造方案的区别就是前者的第一个 $-1$ 变成了 $1$，所以 $f(m+2) \leq f(m)+2$，所以奇偶性相同的里选小的 $m$ 一定是不劣的。（当然打表仔细观察应该也能猜出来）

最小的 $m$ 在调整的初始状态处取到，然后我们只要枚举两个情况看答案就解决了这题。

参考代码：
```cpp
# include <bits/stdc++.h>
# define ll long long 
const int MAX=1e6+9,inf=0x3f3f3f3f;
char s[MAX];
int n,m;
int pr[MAX],mx[MAX];
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
void cmin(int &a,int b){a>b?a=b:0;}
int getval(int now){
	int i,delta=0,ans=0;
	for(i = 1;i <= n;i++)cmin(ans,pr[i]+((s[i]=='?'&&mx[i]+delta+2<=now)?delta+=2:delta));
	return ans;
}
int main() {

	scanf("%s",s+1);
	n=strlen(s+1);
	int i;
	for(i = 1;i <= n;i++)pr[i]=pr[i-1]+(s[i]=='1'?1:-1);
	mx[n]=pr[n];
	for(i = n-1;i >= 1;i--)mx[i]=max(mx[i+1],pr[i]);
	m=max(mx[1],0);
	printf("%d\n",min(m-getval(m),m+1-getval(m+1)));

	return 0;
}
```

---

## 作者：Jeefy (赞：3)


其实看到这道题的第一眼就应该想到二分，但是这个 `check` 比较麻烦。

将 $01$ 看作网格在上下，我们手模一下可能的路径，发现一定是一个区间的奇数或者偶数位置。

![](https://gitlab.com/jeefies/image-repo/uploads/ee13a5b5ae7bcfdbb8855fc05202ea54/202401032128733.png)

> 这是样例 `0??0` 的图。

现在我们需要将路径限制在一个大小为 $mid$ 的区间内，看是否有合法路径，这很抽象，因为上下限会随着路径而改变。但是有个十分新奇的思路，我们设置 $mid$ 个起点，限制在一个 $mid$ 的长条内。

这是当 $mid = 3$ 时的三条路径。

![](https://gitlab.com/jeefies/image-repo/uploads/149a766cb9b574b575f3d2bbe5a9b4e2/202401032141625.png)

如果将三者重叠，我们会发现每一列的合法位置是一个区间：

![](https://gitlab.com/jeefies/image-repo/uploads/72e720044ab7e6e6a5a649fd2e0293a2/202401032143941.png)

那么我们二分的时候维护这个区间即可，但是此时我们发现样例过不去。

对于 `0??0` 在 $k = 1$ 时，如果单纯的维护上下界会存在如下情况：

![](https://gitlab.com/jeefies/image-repo/uploads/8725339d80af84b64113feafb9391436/202401032148153.png)

红色为实际的合法路径，但是我们会将黑色的两个点都算为合法进去。

这是因为在第一次加入 `?` 时我们单纯的扩展了上下界，并且将溢出下界的去掉，但是忽略了恰好在下界位置的那个点没有办法取到。导致算重。

回顾 `可能的路径，发现一定是一个区间的奇数或者偶数位置`，那么我们可以将奇偶位置分开考虑，维护合法的区间，这样如果越过边界，那么利用 $\pm 2$ 来修正即可。

代码非常简单：<https://atcoder.jp/contests/agc045/submissions/49005863>

---

## 作者：未来姚班zyl (赞：2)

## 题目大意

给你一个长度为 $n$ 的 $01$ 序列，有些位置未知。请你填满这些位置，最小化这个序列的权值。

这个序列的权值是其所有子区间中 $01$ 数量之差的最大值。

## 题目分析

考察对基本的套路的掌握。

类似子区间的问题可以考虑转换为前缀和。比如这题，设 $1$ 的权值是 $1$，$0$ 的权值是 $-1$，区间的权值就能变成两段前缀和之差的绝对值，这样问题就变成了最小化极差。

而最小化极差可以通过固定上界来求最大下界来做。在这题中，我们就可以枚举前缀和的最高点 $x$，考虑如何贪心求得最高的最低点（这一步建议自己画图辅助理解，不然下面可能看不懂）。

我们先把所有问号填上 $0$，然后从左往右扫，将能改成 $1$ 的改成 $1$，显然我们记录一个后缀的最高点（假设这个后缀的值是从 $0$ 开始的）就行，如果后缀最高点加上 $1$ 不会超过固定的最大值就可以将当前改成 $1$。

这样我们枚举所有上界求出答案就能 $O(n^2)$ 了。

但明显没必要，因为当上界抬升了 $2$ 时，我们最多在原有的基础上再将一个 $0$ 改成 $1$，这样下界也最多抬升 $2$，不会更优。

所以我们只需要检验最低的上界和最低的上界加上 $1$ 对应的答案就行了，复杂度 $O(n)$。

```cpp
//代码已删火车头
#include<bits/stdc++.h>
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =1e6+5,M=1e6+5,inf=(1LL<<31)-1,mod=23333333;
const ll llf=1e18;
using namespace std;
string c;
int n,s[N];
inline int solve(int mx){
	int nw=0,mn=0;
	repn(i){
		if(c[i]=='0')nw--;
		else if(c[i]=='1')nw++;
		else if(nw+s[i+1]+1<=mx)nw++;
		else nw--;
		mn=min(mn,nw);
	}
	return mx-mn;
}
signed main(){
	cin >>c,n=c.length();
	c=' '+c;
	int mx=0,nw=0;
	per(i,n,1)s[i]=max(0,s[i+1]+(c[i]=='1'?1:-1));
	cout <<min(solve(s[1]),solve(s[1]+1));
	return 0;
}
```

---

## 作者：wosile (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_agc045_b)。

我们先把 $0$ 看成 $-1$，这样一个串的不平衡度实际上就是他的前缀和 $p_i=\sum\limits_{j=1}^i a_j$ 的极差（注意要算上 $p_0$）。

按照经典套路画出这个串的折线图（即 $1$ 为往右上走，$-1$ 为往右下走），这样考虑起来清楚一点。

根据极差的定义，我们可以枚举前缀和的最小值，然后强制所有的前缀和不能低于这个最小值，然后我们要让所有的前缀和尽可能的小。

具体来讲，我们可以递推求出 $f_i$ 表示 $i$ 开始的这个后缀的最小前缀和最大是多少，即假如我们把所有的 $?$ 都看成 $1$，这个后缀的最小前缀和。

$$f_i=\min(0,f_{i+1}+S_i)$$

然后，我们从左到右贪心，每次到一个问号就判断一下我们能不能在这个位置填 $-1$，能填就填。具体的判断方法就是我们看看填完这个 $-1$ 之后后面是否还有符合最小值限制的可能。

直接枚举这个最小值限制可以做到 $O(n^2)$。

感性理解一下，我们先假装对于一个问号，我们可以决定其值是 $[-1,1]$ 中的任意值，而不是只能选择 $-1$ 还是 $1$。然后可以发现，在这种情况下，我们每将最小值限制减少 $1$，整个序列的前缀和最大值至多减少 $1$。也就是说，我们选一个尽量大的最小值限制（也就是 $f_0$）即可。

然后把这个东西提交上去你会发现 WA 了八个点。原因是我们不能单取 $f_0$ 作为最小值，在 `?1` 这个串中，$f_0=0$，但是只有填 $-1$ 才是最优解。

要解决这个问题也很简单，我们把 $f_0$ 和 $f_0-1$ 两种最小值限制都试一遍即可。至于这为什么对我也不知道。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
char s[N];
int a[N],n;
int suf[N];
int solve(int lim){
    int cur=0,mx=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='0')cur--;
        else if(s[i]=='1')mx=max(mx,++cur);
        else{
            if(cur-1+suf[i+1]>=lim)cur--;
            else mx=max(mx,++cur);
        }
    }
    return mx-lim;
}
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)a[i]=(s[i]=='0'?-1:1);
    for(int i=n;i>=1;i--){
        suf[i]=min(0,a[i]+suf[i+1]);
    }
    printf("%d\n",min(solve(suf[1]),solve(suf[1]-1)));
    return 0;
}
```

---

## 作者：masonpop (赞：1)

先设 $0,1$ 分别为 $-1,1$，则问题转化为最小化区间和的绝对值。

设前缀和 $S_i=\sum\limits_{i=1}^ia_i$。则问题进一步转化为最小化 $\max\limits_{0\le l<r\le n}\{|s_r-s_l|\}$，即前缀和的极差。

考虑如何求 $\max\limits_{0\le i\le n}\{S_i\}-\min\limits_{0\le i\le n}\{S_i\}$。枚举最大值 $\le M$，这时就要求在这个前提下前提下最小值的最大值。设这个值为 $f(M)$。则答案为 $\min\limits_{\lim\le i}\{M-f(M)\}$，$\lim$ 为能取到的最小的 $M$，即所有 `?` 均为 $-1$ 时的 $M$。

高效求单个 $f(M)$ 很简单，先全部选 $-1$，再在不超过 $M$ 的前提下尽量多改成 $1$ 即可。

但是这样对每个 $M$ 求一遍太慢了啊。你注意到按照这种方法做，有 $f(M+2)\le f(M)+2$。因此只需求 $f(\lim)$ 和 $f(\lim+1)$ 即可。[代码](https://www.luogu.com.cn/record/140189150)。



---

## 作者：skyskyCCC (赞：0)

## 前言。
好题！显然的贪心。但是题目中填充的 $0$ 和 $1$ 有些稍微难写，所以我们不妨将他们看做两个互不联系的数，所以赋上权值，即把 $0$ 看做 $-1$ 吧。
## 分析。
考虑一个区间内的个数差的绝对值，显然我们需要先处理出来。前缀和处理即可。我们设 $sum_i$ 表示在区间 $\left[1,i\right]$ 的前缀和。既然让最小化最大的平衡度，那么我们要最小化的就是：在区间 $\left[l,r\right]$ 中，其 $sum_r-sum_{l-1}$ 的绝对值中的最大值。而这个式子可以化简为整个前缀和数组的最大值减去最小值。我们发现，在一个区间内，对整个答案产生影响的，也无非就是上面的两个最大值和最小值。

下一步我们设 $f_i$ 表示当这个前缀和数组中的最大值 $\leq i$ 时，这个前缀和数组中的最小值是多少。换言之，我们需要求出的答案就是 $i-f_i$ 满足前提条件时的最小值。

这样我们就将动态规划转换成了求前缀和中的最大值。这里我们可以贪心地考虑，将所有 ```?``` 全部换成 $0$ 即可，所以我们直接开始动态转移。那么我们贪心地将所有数据填满，但是这不一定是最优解，所以我们从这个用 $0$ 填满的字符串中从前往后再分别考虑。对于一个 ```?``` 的位置，我们可以进行一个简单的判断，如果将它换成 $1$ 后我们再计算一遍前缀和，如果在整个前缀和中不会有 $sum_i$ 超过 $i$ 则直接将其修改为 $1$ 即可。这样我们一遍遍贪心地考虑，就可以直接求出 $f_i$ 的值了。这样我们在两个区间内，即 $i$ 和 $i+2$ 之间，因为最多改两个数据，所以 $f_i$ 和 $f_{i+2}$ 之间的最大差值就是 $2$。 

那么就有：
$$f_i+2\geq f_{i+2}$$
同时加上 $i$ 并移项可得：
$$i+2-f_{i+2}\geq i-f_i$$
那么我们显然只需要求出上面需要的两个式子即可。我们设前缀和数组中的合法的可能较大数中的最小值为 $k$ 则我们只需要求出 $k-f_k$ 和 $k+1-f_{k+1}$ 即可。

代码如下，仅供参考：
```
#include<algorithm>
#include<cmath>
#include<cstring>
#include<iostream>
using namespace std;
int n;
char s[1000005];
int sum[1000005],ans[1000005],t[1000005];
int change_s[1000005];
int f(int num){
	change_s[0]=0;
	int tot=0;
	for(int i=1;i<=n;i++){
		if(t[i]){
			if(ans[i]+2*(tot+1)<=num){
			    change_s[i]=1;
				tot++;
			}
			else change_s[i]=-1;
		}
		else{
			if(s[i]=='0'){
				change_s[i]=-1;
			}
			else change_s[i]=1;
		}//赋上权值。 
	}
	for(int i=1;i<=n;i++){
	    change_s[i]+=change_s[i-1];
	}
	return *min_element(change_s,change_s+n+1);
}
int main(){
	cin>>s+1;
	n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='?'){
		    t[i]=1;
		}
		if(s[i]=='1'){
		    sum[i]=sum[i-1]+1;
		}
		else sum[i]=sum[i-1]-1;
	}
	for(int i=n;i>=0;i--){
		ans[i]=sum[i];
		if(i!=n){
			if(ans[i]<ans[i+1]){
				ans[i]=ans[i+1];
			}
		}
	}
	cout<<min(ans[0]-f(ans[0]),(ans[0]+1)-f(ans[0]+1))<<"\n";
	//这里的 ans[0] 就是分析中的 k。 
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：羊羊君的幻想 (赞：0)

### Link

[题面 Link](https://www.luogu.com.cn/problem/AT_agc045_b)

[官方题解 Link](https://img.atcoder.jp/agc045/editorial.pdf)


------------


### 题意

给你一个 $01$ 字符串，其中有些已知，有些未知，未知的你可以随便填上 $0$ 或 $1$，使所有子区间的 $0$ 和 $1$ 数量的极差的最大值最小。



------------


### 题解

看到题意，发现很不好处理。想到只有 $0$ 或 $1$，我们便可以利用一个经典的套路，把 $0$ 视为 $-1$，把 $1$ 视为 $1$。

这样处理过后，假如我们现在已经知道了这个字符串，那么，计算一下处理过后的序列的前缀和 $sum$，对于区间 $[L,R]$，$0$ 和 $1$ 的数量的极差便可以表示为 $\left|sum_R-sum_{L-1}\right|$。

于是，我们把题意转化成了求上面那坨式子的最小值。

考虑到带上了绝对值不太好处理，根据绝对值的定义，不难发现：

$\begin{aligned}\max_{i=1}^{n}sum_i \space - \space \min_{i=1}^n sum_i \end{aligned}$ 就是我们的最终答案。

我们不妨设：

$\begin{aligned}A=\max_{i=1}^{n} sum_i\end{aligned}$；

$\begin{aligned}B=\min_{i=1}^{n} sum_i\end{aligned} $。

现在，我们的目标越来越清晰，即，我们要通过赋值操作，最小化 $A-B$。

考虑贪心。不难发现，在让 $A$ 变小的同时，我们也有可能让 $B$ 变小，这两个互相牵制。

这两个东西的制约关系不好处理，所以，我们可以先让 $A$ 开局就最小，然后慢慢调整到最优解。 

怎么让 $A$ 开局就最小？把 $?$ 都看为 $0$ 就可以了，此时得出的 $A$ 不可能更小了。

然后挖掘一下 $A$ 和 $B$ 的关系，为了防止混淆，我们设，最大前缀和为 $m$ 时，对应的最小前缀和为 $f_m$（显然 $B=f_A$，并且 $ans=m-f_m$）。当 $m$ 增加 $2$ 时，最多只有一个 $?$ 从 $0$ 变成了 $1$，所以 $f_m$ 最多也只会增加 $2$，整体算下来，一定不会使答案更优秀，综上：

$$m-f_m \leq (m+2)-f_{m+2}$$

把 $m$ 推广到 $A$，现在 $A$ 开局就已经最小了，所以我们就只需要求一下 $A-f_A$ 和 $(A+1) - f_{A+1}$ 取最小值就可以了，反正 $m\geq A+2$ 的答案毫无意义。

问题只剩一个了，怎么求 $B$？我们先固定住 $A$ 不动，从前到后扫一遍，遇到能替换的 $0$（就是 $?$），考虑能不能换成 $1$，只要能不影响 $A$ 就换，反正 $B$ 不会变小。

$A$ 会了，$A+1$ 就是套个模板再跑一遍的问题，令 $A \gets A+1$，然后重复上述过程取 $\min$ 即可。

时间复杂度 $O(n)$。

---

