# Triangles

## 题目描述

给定一个有规律的金字塔形的图形，其中一部分三角形是黑色的（见图）。 要求统计所有从最顶端出发，沿着黑线走了一条闭合简单路径又回到最顶端，且没有任何黑色三角形在闭合简单路径内部的路径条数

## 样例 #1

### 输入

```
2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
4
```

### 输出

```
74
```

# 题解

## 作者：0逝者如斯夫0 (赞：7)

~~三角形真的是太美妙了~~

这道题一开始yy了好久，自以为搞出正解才发现是n<=4……
    
   首先要计算答案，可以观察到几个性质
    
   ①左右是有明显的对称性的，如果要计算路线个数（这里指强制其路线经过第一个黑三角的顶点的路线），只需要求出一边的可能情况cnt1然后根据乘法原理，答案就是cnt1^2×2+2（路线反向又一遍所以*2，还要加上n=1的那个三角形）
    
   ②两个黑三角形之间只夹了一行，我们可以求出从上面点进下面点出的路径个数cnt2，通过递推的想法可以得出，每加深一层cnt2=cnt2'*2+3（可以考虑是在上一深度的cnt2下再加多了一层，因为强制经过上一层上下两点的有两条路，不经过的有三条路，所以是cnt2*2+3）
   
   如图，这里cnt2求的就是强制从这两个红点经过的路线个数，这里cnt2=5（很容易就可以输出来）
   
   ![](https://cdn.luogu.com.cn/upload/pic/44218.png )
    
   ⑨一个核心思想：不妨考虑走左边，那么因为题目要求不可以经过重复的点，显然的在最左边的这一列，一定会选择一条“拐弯的边”，这里考虑从靠里面拐向外面，那么对于最左列中的一条“拐弯”边，它的贡献就是右边那些~~花里胡哨的~~拐进去的三角形提供的可能个数，  _这个右边三角形的可能个数cnt3就等于前面所有cnt2的乘积（乘法原理）_  
   
   这样问题就转化为每条“拐弯”边的贡献之和了
   
   ![](https://cdn.luogu.com.cn/upload/pic/44219.png)
   由图不难可以看出这个红点会影响到图中的四条绿边，对于上边的边是不会有贡献的了，这样子我们两层两层来考虑会方便很多（因为单层考虑会统计不会考虑到里面的三角形凸下去再回来的情况）
   
   于是最终解题的步骤就如下：
   
   两层两层跳，分别推出cnt1 cnt2 cnt3
   
   特别的，如果最后n&1==1多出一行白三角形怎么办，其实也可以把这最后一行
   看做一层cnt2，cnt2=（n-2）（显然），然后也算出cnt3，这里剩下的就是两条边所作出的贡献了，加进cnt1
   ![](https://cdn.luogu.com.cn/upload/pic/44220.png )
  最后的最后就用cnt1^2×2+2得出答案
  
  记住取膜……完事

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2600}$
---
### 解题思路：

整个图像是对称的，先考虑考虑路径，只向左边的方案数和只向右边的方案数一样，所以只需要计算出左边的方案数 $ans$ 就行了。

所以问题就是如何计算左边的方案数。发现最左边一列的情况是很简单的，因为仅能够线性延伸，关键就在于如何计算右边折进去的部分。

将这一块单独拿出来分析，可以发现其实是一个单元的重复，对于这个单元，一定要从左上走到右下以和外面链接起来，一共有 $5$ 中走法，其中有两种是可以延伸至下一个单元的，剩下三个就相当于断开了，所以不妨设内部当前方案数为 $cnt_2$，内部可延伸的方案数为 $cnt_3$，每一次拓展都是由之前的 $cnt_2'$ 和 $cnt_3'$ 经过 $cnt_2=cnt_2'+4cnt_3'$，和 $cnt_3'=2cnt_3'$，并有一开始的时候：$cnt_2=1$ 且 $cnt_3=1$。其实这样式子也就清晰了，$cnt_1=4(\sum_{i=1}^n 2^i)+1=2^{n+2}-3$。

然后转化到外面，按照类似的思路，记录下可拓展的方案数 $cnt $ 和总方案数 $ans$，只不过这一次乘的是 $cnt1$，也就是在每一个位置 $ans=ans'+4\times cnt_1\times cnt'$，且 $cnt=cnt_1\times cnt'$。

---

此时算出来的是从最上方的黑色三角形左边走下去的方案数，实际上的总方案数应该是只在上边绕的和只走一边（只要经过左边两个点就算）的以及两边都走的方案总和，最后还要乘以 $2$ 也就是 $10+8ans+2ans^2$。

注意随时取模。

---
### 代码：

因为懒，多了一个 $\log$，不过问题不大。
```cpp
#include<cstdio>
using namespace std;
#define int long long
const int MOD=1000000009;
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
int n,ans,cnt,now;
signed main(){
	scanf("%I64d",&n);n/=2;
	ans=0;cnt=1;
	for(int i=2;i<=n;i++){
		now=pow(2,i);
		now=(now-3+MOD)%MOD;
		ans=(ans+4*now*cnt)%MOD;
		cnt=(cnt*now)%MOD;
	}
	printf("%I64d\n",(10+8*ans%MOD+2*ans%MOD*ans%MOD)%MOD);
	return 0;
}
```



---

## 作者：滑蒻稽 (赞：2)

## Des

[CF15E Triangles](https://www.luogu.com.cn/problem/CF15E)

## Sol

提供一个比较简洁的思路。

答案是不含黑色三角形的三角形连通块的个数乘 $2$，因为每一个连通块都对应一条顺时针、一条逆时针的路线。并且每条合法的路线都能围一个连通块出来。

并且这里的连通指必须有边连通（下图左边的连法就不行）：

![](https://gitee.com/huaruoji/images/raw/master/img/20220308134856.png)

然后考虑给连通块计数。由于左右两边是对称的，所以只用考虑一边的情况，然后用乘起来。

一边由一条下去的路（红色）和支出去的绿色部分构成。考虑递推，固定红色的长度，然后算绿色的个数。

就以下图 $n=8$ 为例，要使得两个绿色都能接上，红色的必须接到第 7 层，也就有 4 种方案。而绿色的方案数是两块的方案数乘起来。

![](https://gitee.com/huaruoji/images/raw/master/img/20220308135105.png)

考虑绿色部分怎么计数。

仍然用一种类似的思路，固定下图中红色部分后把绿色接上。

![](https://gitee.com/huaruoji/images/raw/master/img/20220308135353.png)

推一下就能发现对于 $i=n/2-2$ 来讲，绿色部分方案数是 $2(2+2^2+\dots +2^i)+1$。

然后把之前所有绿色块的方案数和算出来的方案乘起来，就是固定好红色条的方案数。

再把固定好红色条的方案数和之前所有的方案加起来，就能得到一边连通块的方案数。设这个方案数为 $c$，那么答案为 $2(c^2+1)$，因为最顶上一个小三角形可以单独作为一个方案。

## My Code

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int D = 1e9 + 9;
inline void Add(int &a, ll b) { a = (a + b) % D; }
inline void Mul(int &a, int b) { a = (ll)a * b % D; }

int main() {
	int n, cnt = 2, s = 0, p2 = 1, prod = 1;
	cin >> n;
	n /= 2;
	for(int i = 2; i <= n; i++) {
		Mul(prod, (2 * s + 1) % D);
		Add(cnt, (ll)4 * prod);
		p2 = p2 * 2 % D;
		Add(s, p2);
	}
	cout << ((ll)cnt * cnt + 1) * 2 % D << '\n';

	return 0;
}
```

---

## 作者：Tenderfoot (赞：2)

我们先观察小三角形

![](https://cdn.luogu.com.cn/upload/image_hosting/wrut5030.png)

从顶点 A 出发并回到顶点 A，有以下逆时针路径：

1. $A\rightarrow B\rightarrow C$
2. $A\rightarrow D\rightarrow F\rightarrow A$
3. $A\rightarrow B\rightarrow E\rightarrow C\rightarrow A$
4. $A\rightarrow D\rightarrow E\rightarrow C\rightarrow A$
5. $A\rightarrow B\rightarrow E\rightarrow F\rightarrow A$

共 $5$ 条路径。因此加上顺时针路径，我们共 $10$ 条路径可以选择。

我们令 $Ans$ 为从点 $u$ 向下走，再从点 $v$ 返回上来的方案数。对于上图来说，我们可以分为以下几种来进行讨论：

1. 从边下到底再从中间上来，如方案 $2,4$ 所述。则此时逆时针路径的贡献为 $Ans$。
2. 从中间下去，从边上回来，如方案 $2,5$ 所述。此时逆时针路径的贡献为 $Ans$。
3. 从边上下去，从边上返回。如方案 $2$ 所述。此时逆时针路径贡献为 $Ans$。

对于情况 $1,2$，由于顺时针和逆时针相互对称，因此可以得到贡献为 $8\times Ans$，对于情况 $3$，同样的，我们有贡献为 $2\times Ans^2$。因此总贡献为

$$8\times Ans+2\times Ans^2$$

观察题目中所给的图形，因为不能经过黑色区域，所以对于第 $i$ 层，我们最多从边上向中间行进 $i-2$ 个点。不难发现，如果我们向中间前进 $i$ 个点，那么就有 $2^{i+1}$ 种方案。

以此类推，经过 $k$ 层时，我们有方案数 $2^k-3$。

最后加上返回操作。其情况类似于上面的分类讨论，不过多叙述。我们有总方案数 

$$Ans=4\sum_{i=2}^{k}\sum_{j=2}^{i}(2^j-3)$$

代码
```cpp
#include<bits/stdc++.h>

#define Mod 1000000009
#define int long long
#define MAXN 1000010
#define Enter puts("")
#define Space putchar(' ')
#define Test_Begin Enter , puts("Test--------------")
#define Test_End Enter , puts("--------------------")

using namespace std;

constexpr int INF = 2147483647;

static inline int Read()
{
	int Ans = 0;
	char Ch = getchar(), Las = ' ';
	while (!isdigit(Ch))
	{
		if (Ch == '-')
			Las = '-';
		Ch = getchar();
	}
	while (isdigit(Ch))
	{
		Ans = Ans * 10 + Ch - '0';
		Ch = getchar();
	}
	if (Las == '-')
		Ans = -Ans;
	return Ans;
}

static inline void Write(int x)
{
	if (x < 0)
	{
		x = -x;
		putchar('-');
	}
	if (x >= 10)
		Write(x / 10);
	putchar(x % 10 + '0');
}

int Res[MAXN] , Pow[MAXN];
int Ans;

signed main()
{
    int n = Read();
    n >>= 1;
    Res[1] = Pow[0] = 1;
    for(register int i = 1; i <= n; i++)
        Pow[i] = Pow[i - 1] * 2 % Mod;
    for(register int i = 2; i <= n; i++)
        Res[i] = Res[i - 1] * (Pow[i] - 3) % Mod;
    for(register int i = 2; i <= n; i++)
        Ans = (Ans + 4 * Res[i]) % Mod;
    int _Ans(10 + 8 * Ans % Mod + 2 * Ans * Ans % Mod);
    Write(_Ans % Mod);
    return 0;
}
```


---

## 作者：lfxxx (赞：0)

首先给出关键结论，只要路线没有切割任意黑色三角形，那么就不会包含任意三角形，感受一下容易发现这是对的。

然后计算答案的关键就变成计算从最左边的线段下去向右走一段再上来的方案。

你发现一定是先走到一个点，向右边或者右下走一段再上来，只有可能在走上来的时候产生不同方案，你发现不同方案一定形如将向上走的一段换成在两个三角形中间的部分走，这个部分也形如向右走一段上去再走回来，容易递推 $O(n)$ 计算。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+114;
const int mod = 1e9+9;
int f[maxn];//f[i] i 个三角形构成的缺口
int pre[maxn];//从第 i 个位置回去的方案
int _pow[maxn];
int n;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    _pow[0]=1;
    for(int i=1;i<maxn;i++) _pow[i]=_pow[i-1]*2%mod;
    f[0]=1;
    for(int i=1;i<maxn;i++){
        f[i]=f[i-1];
        f[i]=(f[i]+_pow[i]*2%mod)%mod;
    }
    cin>>n;
    if(n==1){
        cout<<1<<'\n';
    }else if(n==2){
        cout<<10<<'\n';
    }else{
        int ans=0;
        pre[1]=pre[2]=pre[3]=1;
        for(int i=4;i<maxn;i++){
            if(i%2==0){
                pre[i]=pre[i-1]*f[i/2-1]%mod;
            }else pre[i]=pre[i-1];
        }
        for(int i=3;i<n;i++){
            //平 或者 斜下
            ans=(ans+pre[i-1]+pre[i])%mod;
        }
        //平
        ans=(ans+pre[n-1])%mod;
        ans=(ans+1)%mod;
        ans=(ans*8%mod+ans*ans%mod*2%mod)%mod;
        cout<<(ans+10)%mod;
    }
    return 0;
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

## 题意

给一个有规律的三角形，其中有一部分是黑的。然后让你统计从顶点出发，沿着黑线走了一条闭合简单路径又回到顶点，且没有任何一个黑色三角形在闭合简单路径内部的路径条数。

## 分析

分析可行路径的形式，然后得出亿些有用的性质。

通过仔细观察我们可以发现，金字塔被中间一列的黑色三角形分成左右两部分，于是路径只有三种形式：

没有进入左边也没进入右边，这类很少直接用手算就行。

只进了左边或右边，因为这个三角形是对称的，所以左边和右边路径相等，设为 $x$。

先进入左边，然后回来到左右两边的交汇点，然后进入右边，再回来。或者是先进入右边，然后回来到左右两边的交汇点，然后进入左边，再回来。因为左右对称，所以得出这种路径有 $2 \times x^2$ 条。

我们只要统计从出发点到左边再回来交汇点的方案数。

这些路径的特性：

一定有一个达到最深层数。

从出发点每向下走一层都有一个“兜”的结构，进去不进去都行。

到达最深层后回去的路径唯一。

然后只要计算每层的“兜”进去再回来的路径数，第 $i$ 层的方案数是 $f(i)=2^i-3$ 种。

用乘法原理算出某个给定最深层的方数 $g(i)=f(1) \times f(2)...\times f(i)$。最终答案是 $g(n) \times g(n) \times 2 + g(n) \times 2 + k$。

最后提醒：$k$ 需要用手算。

~~用手做就行。~~

---

