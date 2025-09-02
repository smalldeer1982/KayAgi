# The Great Julya Calendar

## 题目描述

## 题目大意

聪明的海狸得到了一个魔数 $n$，现在可以对其进行一种操作：

- 使 $n=n-k$  $(0\le k\le9)$，其中 $k$ 必须在$n$的某一位中出现。

海狸将不断进行这个操作，直至$n=0$。

选择不同的 $k$ 显然会使操作次数不同，海狸希望你能帮他算出他最少需要操作多少次才能使魔数变为$0$。

## 说明/提示

对于输出样例，通过以下操作顺序可以得到最少操作次数：
 $$ 24 \rightarrow 20 \rightarrow 18 \rightarrow 10 \rightarrow 9 \rightarrow 0 $$

## 样例 #1

### 输入

```
24
```

### 输出

```
5```

# 题解

## 作者：HYdroKomide (赞：2)

### 题意：
给定一个整数 $n$，每次减去 $n$ 的任意一个数位的数 $k(0\le k\le 9)$，求多少次减到 $0$。

特别地，$n\le10^{12}$。（后面有用）

### 思路：

由于答案是关于 $n$ 单调的，因此不难证明贪心的正确性。但是显然不能像弱化版 C1 一样直接暴力减 $k$ 处理了。考虑一个类暴力~~优雅~~的复杂度平摊方法。

考虑将 $n$ 的后 $6$ 位提取出来，变成两个数 $n_1$ 和 $n_2$ 分别处理。

对于所有可能的 $n_2$，预处理暴力计算对答案的贡献。但是显然，由于 $n_1$ 的最大位数可能对答案贡献造成影响。（例如，计算 $987123456$ 这个数时，对于其后六位，应当每次减去的数为 $9$，而不是其他的数字）

因此，预处理一些状态，$a(i,j)$，其中 $i$ 代表 $n_2$ 当前的六位数，$j$ 代表 $n_1$ 的最大位数。转移方程为：

$a(i,j)=a(i-\max(maxdig(i),j),j)+1$，其中 $maxdig$ 代表各个数位上的最大值。

以上方程可以循环处理，也可以记忆化搜索处理。

同时，由于前一位数减来的数可能比 $maxdig$ 大，并不一定刚好减到 $0$，所以需要维护另一个数组 $rem_{i,j}$ 表示这个状态下 $i$ 减到小于等于 $0$ 时余下什么数。

因此，便可以进行第二步暴力。枚举 $n_1$ 的值，每次循环对 $n_1$ 减一，答案贡献增加 $a(n_2,maxdig(n_1))$，并更改 $n_2$ 为 $100000+rem_{n_2,maxdig(i)}$。直到 $n_1$ 减为 $0$ 时停止。

复杂度大概是 $O(Blk\times 10+\dfrac{n}{Blk})$，这里 $Blk$ 为 $10^6$。

当然，这题如此设置也是为后面的题目搭台阶，是一个自然的思考过渡过程。继续往下想，不难发现，无论 $n$ 多大都可以进行复杂度的平摊。这是由本题转移的性质所决定的，以达到和数位 dp 等价的效果。

~~所以还是不会数位 dp 和线代导致的~~

其余具体细节详见代码。

### 程序如下：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e6+5;
long long x,ans,trem;
long long a[N][10],rem[N][10];
int mxdig(long long x){
    int ret=0;
    while(x){
        ret=max(1ll*ret,x%10);
        x/=10;
    }
    return ret;
}
long long brute(int x,int mm){//暴力记忆化搜索
    if(x==0)return 0;
    if(x<10){
        trem=min(0,x-mm);
        return 1;
    }
    if(a[x][mm]!=0){
        trem=rem[x][mm];
        return a[x][mm];
    }
    int mxx=max(mm,mxdig(x));
    return brute(x-mxx,mm)+1;
}
int main(){
    scanf("%lld",&x);
    for(int i=0;i<=999999;i++)
        for(int j=0;j<10;j++){
            a[i][j]=brute(i,j);//初始化
            rem[i][j]=trem;
        }
    long long up=x/1000000,dn=x%1000000;
    while(true){
        long long mx=mxdig(up);
        ans+=a[dn][mx];
        if(!up)break;
        if(rem[dn][mx]==0){//如果余的是0，需要再强制进位
            ans++;
            dn=1000000-mx;
        }
        else dn=1000000+rem[dn][mx];
        up--;
    }
    printf("%lld\n",ans);
    return 0;
}
```

### THE END

---

## 作者：littlebug (赞：1)

线代还是太强大了，第一次看见数位 dp 模拟矩阵快速幂优化 dp 的 /bx /bx

这篇题解主要是详细讲一下大佬 @[Terry2022](https://www.luogu.com.cn/user/202556) 的[线代做法](https://www.luogu.com.cn/article/bbhit84v)。

当然，这里是 C3 做法，不过比 C2 的正常解优美很多，所以来 C2 交一发题解。

## Solution

> 首先证明个东西。
> 
> 考虑最普通的 dp，设 $f_i$ 为从 $0$ 到 $i$ 的最少步骤（就是把题目中的操作倒过来），则 $f_i = \min \limits _{x \in d(i)} \{ f_{i-x} \} + 1$
> 
> 我们发现 $f_i$ 满足单调性！证明考虑归纳法，首先 $f_1 = 1 > f_0 = 0$。那么假设 $\forall 0 \le i < n , f_i \ge f_{i-1}$，又因为显然有 $l=\max\{ d(n-1) \} \ge \max \{ d(n) \}-1$，于是有 $f_n \ge f_{n-1}$。其中 $d(x)$ 表示 $x$ 的所有数位。
>
> 于是转移方程就变成了 $f_i = f_{\max \{ d(i) \}} + 1$！

观察到，$\max \{ d(i) \}$ 的取值集合是固定且很小的，所以考虑用矩阵优化，设 $d'(x)$ 表示 $x$ 是 $(1)$ 否 $(0)$ 等于 $\max \{ d(i+1) \}$，则有：

$$
\begin{bmatrix}
d'(1) & d'(2) & d'(3) & d'(4) & d'(5) & d'(6) & d'(7) & d'(8) & d'(9) & 1 \\
1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 \\
\end{bmatrix}
\times
\begin{bmatrix}
f_i \\
f_{i-1} \\
f_{i-2} \\
f_{i-3} \\
f_{i-4} \\
f_{i-5} \\
f_{i-6} \\
f_{i-7} \\
f_{i-8} \\
1
\end{bmatrix}
=
\begin{bmatrix}
f_{i+1} \\
f_i \\
f_{i-1} \\
f_{i-2} \\
f_{i-3} \\
f_{i-4} \\
f_{i-5} \\
f_{i-6} \\
f_{i-7} \\
1
\end{bmatrix}
$$

~~嗯搬的，懒得打了。~~

然后因为转移矩阵不是固定的，似乎就不可以做了，但是注意到转移矩阵只与 $i+1$ 的最大**数位**有关，于是可以想到数位 dp！

关于正确性，虽然矩阵乘法不满足交换律，但是在数位 dp 的时候可以从低位到高位 dp，那么就满足了从小到大了，不会改变矩阵乘法的顺序。

于是，设 $g_{i,j}$ 为考虑从低到高前 $i$ 位，**第 $i$ 及第 $i$ 位以前的最大位**是 $j$ 时，要求出 $0$ 到当前数位所能表示的最大数的 $f$ 值所需要的**转移矩阵之积**。

那么如何转移呢？因为这是数位 dp，所以考虑在求一个 $g_{i,j}$ 的时候，相当于把可能的所有位数为 $i-1$ 的 $g$ 值乘起来，毕竟人家是转移矩阵嘛，举个例子：

> 若要求 $6737151$ 的 $g$ 值，那么相当于把这些部分的转移矩阵乘起来：
>
> $0 \sim 999999 , 1000000 \sim 1999999 , \dots , 6000000 \sim 6737151$。
>
> 继续，例如在求 $2000000 \sim 2999999$ 的时候，相当于固定一个最高位 $2$（所有的转移都能取 $2$），求 $0 \sim 999999$ 的 $g$ 值，也就对应了 $g_{6,2}$。

于是，这便满足了数位 dp 的常见状态，所以就有转移：

$$
g_{i,j} = \prod _{0 \le k \le lim} g_{i-1,\max(j,k)}
$$

其中，$lim$ 表示数位 $i$ 所能取到的最大值。

然后这样做就可以了，复杂度为 $O(|\Sigma|^3 \times |\Sigma| \times \log(n|\Sigma|)) \approx 6.3 \times 10^5$，其中 $|\Sigma|^3$ 是矩阵乘法，$|\Sigma|$ 是 dp 转移，$\log(n|\Sigma|)$ 是数位 dp 的状态数。

## Code

数位 dp 细节一大坨，调了一下午才调出来 www

```cpp
class matrix ... // 此处省略 6737151 行矩阵类板子

int n;
matrix <int> g[20][10],tmp[20][10];
bitset <10> vis[20];
int a[20],len;

il matrix <int> dp(int i,int j,bool op,bool zr)
{
	if(!op && vis[i][j]) return g[i][j];
	!op && (vis[i][j]=1);
	
	matrix <int> &t=op?tmp[i][j]:g[i][j];
	
	if(!i)
	{
		t=matrix<int>();
		t[0][j-1]=t[0][9]=t[9][9]=1;
		rep(x,1,8) t[x][x-1]=1;
		return t;
	}
	
	if(i==1 && zr) return t=matrix<int>(10,10,1);
	
	t=matrix<int>(10,10,1);
	int mx=op?a[i]:9;
	rep(x,0,mx) t=dp(i-1,max(j,x),op && x==mx,zr && !x)*t;
	
	return t;
}

signed main()
{
	read(n);
	if(n<=9) return cout<<(n!=0),0;
	len=0; int _n=n; while(_n) a[++len]=_n%10,_n/=10;
	
	matrix <int> t=dp(len,0,1,1);
	matrix <int> p(10,1);
	rep(i,0,9) p[i][0]=1;
	t*=p;
	
	write(t[0][0]);
	
	return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意
输入正整数 $n$，求每次减去一个数位上的数字，最少几次可以把 $n$ 减成 $0$。
## 分析
一定要按照数位讨论，但是取法都不知道怎么按数位看？因此考虑贪心首先这里有个有趣的结论，最优解法一定是每次减去尽可能大的数字。

考虑如果 $i$ 能剪掉的数字比 $i-1$ 大，那么也最多只能大 $1$，可以得，即 $f(n)$ 是单调不递减的，也就是说更小的 $n$ 一定对应相同或更小的步数，故对于已知的 $n$ 要减去尽量大的数字。

知道这个结论以后就可以按数位进行 DP 了。

还要考虑后 $n$ 位，前面最大数字是 $h$，后 $n$ 位组成数字是 $x$ 时，将 $x$ 减到再减一次就需要向第 $n+1$ 位借位时，所需的步数和减到的值。

这时只需再减一次 $h$ 就可以借位，使后 $n$ 位变成 $999\cdots9$ 这种数。

考虑总状态数，$h$ 取 $0$ 到 $9$，$n$ 取 $1$ 到 $18$，但是 $x$ 的取值范围特大。

其实，在 $n$ 已知的情况下，$x$ 仅可能取原数的一个后缀或者 $999\cdots9$ 加上一个数字，因此只有 $11$ 种取值。

这样之后，状态转移就很好写出了。
## 代码

```cpp
#include <bits/stdc++.h>
#define long long long
using namespace std;
long tp[20];
struct ans{
    long step;
    long rem;
    ans(){step=-1ll;}
    ans(long s,long r):step(s),rem(r){}
};
ans f[10][20][11];
ans query(int h,int n,long x){
    int xx=(x/10==tp[n-1]-1)?x%10:10;
    ans &key=f[h][n][xx];
    if(~key.step) return key;
    if(n==1){
        if (x>=h) return key=ans(1,0);
        else return key=ans(0,x); 
    }
    long cnt=0,cur=x%tp[n-1];
    int t=x/tp[n-1];
    while(t>=0){
        ans tmp=query(max(h,t),n-1,cur);
        cnt+=tmp.step;
        cur=tmp.rem;
        if(t){
            cur=cur+tp[n-1]-max(h,t);
            cnt++;
        }
        t--;
    }
    return key=ans(cnt,cur);
}
int main(){
    tp[0]=1ll;
    for(int i=1;i<=18;i++) tp[i]=tp[i-1]*10ll;
    tp[19]=9000000000000000000ll;
    long n;
    int p=0;
    scanf("%I64d",&n);
    if(n==0){
        printf("0");
        return 0;
    }
    while(tp[p]<=n) p++;
    ans tmp=query(0,p,n);
    printf("%I64d",tmp.step);
}
```

---

