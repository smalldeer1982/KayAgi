# [ARC058D] いろはちゃんとマス目

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc058/tasks/arc058_b

縦 $ H $ マス、横 $ W $ マスのマス目があります。 いろはちゃんは、今一番左上のマス目にいます。 そして、右か下に1マス移動することを繰り返し、一番右下のマス目へと移動します。 ただし、下から $ A $ 個以内、かつ左から $ B $ 個以内のマス目へは移動することは出来ません。

移動する方法は何通りあるか求めてください。

なお、答えは非常に大きくなることがあるので、答えは $ 10^9+7 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 1\ ≦\ H,\ W\ ≦\ 100,000 $
- $ 1\ ≦\ A\ <\ H $
- $ 1\ ≦\ B\ <\ W $

### Sample Explanation 1

$ 2×3 $ マスありますが、左下の $ 1 $ マスには移動することができません。「右右下」、「右下右」という $ 2 $ つの移動の仕方があります。

### Sample Explanation 2

移動できないマスが $ 12 $ マスあります。

## 样例 #1

### 输入

```
2 3 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
10 7 3 4```

### 输出

```
3570```

## 样例 #3

### 输入

```
100000 100000 99999 99999```

### 输出

```
1```

## 样例 #4

### 输入

```
100000 100000 44444 55555```

### 输出

```
738162020```

# 题解

## 作者：Styx (赞：6)

首先这个题如果不去格子的话就是一个最基础的Schroder数

根据Schroder数的公式我们可以知道从(x1,y1)到(x2,y2)的路径数有
$ C^{x2-x1}_{x2-x1+y2-y1} $ 条

数据范围是100000,模数为质数且固定，可以考虑用线性的求法，O(1)查询组合数。

然后就到了去掉一个矩形的情况了，去掉一个矩形无非相当于把原来的矩形分成两个完整的矩形，然后从左矩形转移到右矩形的计算就是(1,1)->(i,b)*(i,b)->(n,m){i<=n-a}的和

![](https://cdn.luogu.com.cn/upload/pic/18841.png)

代码如下：
```cpp
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define p 1000000007
using namespace std;

long long fac[200010],inv[200010],n,m,aa,bb,ans;

long long kasumi(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b&1)
		{
			ans=(ans*a)%p;
		}
		a=(a*a)%p;
		b>>=1;
	}
	return ans;
}

long long cc(int a,int b)
{
	if(a==b||b==0)
	{
		return 1;
	}
	return ((fac[a]*inv[b])%p*inv[a-b]%p);
}

long long get_(int x1,int y1,int x2,int y2)
{
	return cc(x2-x1+y2-y1,x2-x1);
}

int main()
{
    fac[1]=1;
    for(int i=2;i<=200000;i++)
    {
    	fac[i]=(fac[i-1]*i)%p;
	}
	inv[200000]=kasumi(fac[200000],p-2);
	for(int i=199999;i>=1;i--)
	{
		inv[i]=(inv[i+1]*(i+1))%p;
	}
    scanf("%d%d%d%d",&n,&m,&aa,&bb);
    
    for(int i=1;i<=n-aa;i++)
    {
    	ans+=(get_(1,1,i,bb)*get_(i,bb+1,n,m))%p;
    	ans%=p;
	}
	
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Pengzt (赞：4)

[ARC058D](https://www.luogu.com.cn/problem/AT_arc058_b)

简单组合计数。

可以先把矩形旋转一下，变为求从 $(1,1)$ 走到 $(n,m)$，只能向上或向右移动。且不经过左上角的 $A\times B$ 的禁区的方案数，对 $10^9 + 7$ 取模。

假如没有 $A\times B$ 的禁区的话，那么方案数为 $C_{n+m-2}^{n-1}$。

就是一共要走 $n + m - 2$ 步，其中向右走 $n - 1$ 步，向左走 $m - 1$ 步，因为随时都能向右走，故方案数为 $C_{n+m-2}^{n-1}$ 或 $C_{n+m-2}^{m-1}$。

考虑禁区时，整个图形可沿 $x$ 轴或 $y$ 轴平行的方向切割为两个不包含禁区的矩形。

比如按 $x = b$ 切割，就可以先算 $(1, 1)$ 到 $(b, y), y\leqslant n - a$ 的方案数，然后再算 $(b, y)$ 到 $(n, m)$ 的方案数，将两个相乘的到的数就是从 $(1, 1)$ 到 $(n,m)$ 且经过 $(b, y)$ 而不经过禁区的方案数。

枚举 $y$ 即可。

组合数可以提前预处理出阶乘逆元，$\mathcal{O}(1)$ 计算。

注意：预处理阶乘的逆元时，要处理到 $n + m$。

时间复杂度：$\mathcal{O}(n + m)$

[评测记录](https://atcoder.jp/contests/arc058/submissions/37992282)

---

## 作者：_zzzzzzy_ (赞：2)

# 思路

我们分析一下题目，说左下角有一部分不能走，我们可以用类似下面这张图的方法把这个过程分成两段分别求解。

![](https://cdn.luogu.com.cn/upload/image_hosting/tf1qqias.png)

相当于从坐标 $(1,1)$ 走到红线上的一个点，然后再走到右下角 $(1,1)\rightarrow(k,b)\rightarrow(n,m)$，最后把这两段的方案乘起来就行了。

最后说一下怎么用组合数求两点之间的路径的走法。

显然要想从 $(x1,y1)$ 走向 $(x2,y2)$，那么一定要横着走 $|x2-x1|$ 步，竖着走 $|y2-y1|$ 步，总步数是 $|x2-x1|+|y2-y1|$ 步，方案数就是总步数中走 $|x2-x1|$ 次横步的方案数，也就是 $\binom{|x2-x1|+|y2-y1|}{|x2-x1|}$。
# 代码
```cpp
Z cc(int x1,int y1,int x2,int y2){
	return comb.C(x2-x1+y2-y1,x2-x1);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n,m,a,b;
	Z ans=0;
	cin>>n>>m>>a>>b;
	for(int i=1;i<=n-a;i++){
		ans+=cc(1,1,i,b)*cc(i,b+1,n,m);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Clover_BY (赞：2)

# [ARC058D  いろはちゃんとマス目](https://www.luogu.com.cn/problem/AT_arc058_b)  
提供一种反向的思考方式。
## 题目描述
给定一个 $h\times w$ 的网格，其中左下方 $x\times y$ 的区域为禁区。求从网格左上角走到右下角的方案数。 

数据范围：$h, w\leq 10^5, 1\leq x < n, 1\leq y < m$。
## 题目分析
$O(hw)$ 的递推显然会爆炸，考虑利用组合数计数。  

看到题目后第一眼并没有想到如何直接计算规避掉禁区的路径计算方式，因而运用正难则反的思想，合法路径数即为忽略掉禁区的全部路径数减去途中经过禁区的方案数。

先来改一些定义，让计算变得方便些。  
设 $n$ 和 $m$ 为只向右走到达右边界的步数和只向下走到达下边界的步数，$a$ 为只向下走到达禁区的最少步数，$b$ 为只向右走到达禁区右边界的步数。  
亦即：$n = h - 1, m = w - 1, a = n - x + 1, b = y - 1$。

这样的话，一条合法的路径长度即为 $n + m$，而一条路径是否进入禁区只需在前 $a + b$ 步中判断。  
先考虑计算忽略禁区的全部路径数。问题相当于在 $n + m$ 步中选择 $n$ 次向右走（或选择 $m$ 次向下走），结果显然是 $ans_1 = C_{n + m}^{n}$。  
再考虑途径禁区的路径条数。问题相当于询问在前 $a + b$ 步中，向右走的次数不超过 $b$ 的路径条数。不难发现，在 $a + b$ 一定时，若其中向右走的步数一定，走完 $a + b$ 步后所在的位置也就确定了。故我们可以考虑枚举每个 $i ∈ [0, b]$，前 $a + b$ 步的方案为 $C_{a + b}^{i}$，由走完这些步数到达的位置再走到右下角的方案为 $C_{n + m - a - b}^{m - i}$，于是 $ans_2 = \sum C_{a + b}^{i} C_{n + m - a - b}^{m - i}$ 即为所求。  
两部分计算完毕，$ans_1 - ans_2$ 即为最终答案。

## Code
```cpp
inline int qpow(int a, int b)
{
	int res = 1;
	for(register int i = b; i; i >>= 1)
	{
		if(i & 1) res = (long long)res * a % mod;
		a = (long long)a * a % mod;
	}
	return res;
}
inline int c(int n, int m)
{
	if(n < m) return 0;
	if(n == m || m == 0) return 1;
	return (long long)jc[n] * inv[m] % mod * inv[n - m] % mod;
}

int main()
{
	n = read() - 1; m = read() - 1;
	a = n - read() + 1; b = read() - 1;
	jc[0] = inv[0] = 1; k = n + m + 1;
	for(register int i = 1; i <= k; ++i)
		jc[i] = (long long)jc[i - 1] * i % mod;
	inv[k] = qpow(jc[k], mod - 2);
	for(register int i = k - 1; i; --i)
		inv[i] = (long long)inv[i + 1] * (i + 1) % mod;
	ans = c(n + m, n);
	for(register int i = 0; i <= b; ++i)
		ans = (ans - (long long)c(a + b, i) * c(n + m - a - b, m - i) % mod * now + mod) % mod;
	write(ans); return 0;
}
```

---

## 作者：Starlight_Glimmer (赞：2)


[博客食用效果更佳~~](https://blog.csdn.net/CQBZLYTina/article/details/81945525)


### 题意简述：

有一个 H 行 W 列的网格。

Iroha 现在站在左上角 (1, 1)。 她每次会向右或向下走，直到走到右下角 (H, W)。

唯一的限制是，她不能走到左下方的 A 行 B 列。

求行走的方案数对 1e9 + 7 取模

数据范围：

 - 1 ≦ H, W ≦ 100,000
 - 1 ≦ A < H
 - 1 ≦ B < W 
 
### 思路分析：
#### 组合计数
 首先简化问题，我们先计算一个矩形，从左上角走到右下角的路径数。

 //手动忽略渣图，灵魂小画手qwq
 
 从左上角走到右下角一共需要走H-1+W-1=H+W-2步，这其中，要选H-1步往下走，W-1步往右走。
 
 所以组合数就是C(H+W-2,H-1)=C(H+W-2,W-1)
 
![](https://img-blog.csdn.net/20180822120501994?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NRQlpMWVRpbmE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

----------


 可是这道题有一部分是“禁区”，怎么办呢？
 有两种解决办法


##### 法1

我们可以先计算出整个矩形的方案数，再减去不合法的方案数。
不合法的方案数怎么找呢？
只要进入了“禁区”，方案就不合法（~~废话！~~）
而因为只能向右或向下，所以要进入“禁区”的方案都经过了“禁区”的最上面一排。所以我们我们在到达边界的时候就要亮起红灯（嘀嘀嘀）枚举边界上那一排点，把经过了它们的方案数全部剔掉。


Like this:（有颜色的部分是“禁区”）
![](https://img-blog.csdn.net/20180822150618477?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NRQlpMWVRpbmE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
如图，从红点到绿点，到黄点再到蓝点的方案数必须剔掉。
注意了，每个绿点只能走它下面的那个黄点。为什么？
如果不走下面，它就不会到达“禁区”。

那为什么要用两排点？
看下面（这是我无数次不得其解的血泪史qwq）：


**Notice:下面这张图是不合法的！！！**
**必须要走到上一行再走它的下一行，直接这样会导致重复！！！（啊啊啊，我再这里卡了很久啊）**

**举个栗子，如果像下图那样计算，从红点到绿点1，再从绿点1到蓝点时，会有一些方案是从绿点1经过绿点2的；然后后面来计算红点到绿点2，再从绿点2到蓝点时，就会重复！！！（红点到绿点2的路径也可以经过绿点1）**
![](https://img-blog.csdn.net/2018082214311912?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NRQlpMWVRpbmE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

所有从红点走到绿点，再从绿点走到蓝点的方案都不合法

那如果在这个图下面加一排黄点呢？干嘛非要让绿点在H-A排？就像现在这样在H-A+1排也可以吧？~~（啊喂你是十万个为什么吗）~~

答案是不行！

如果那样的话，会少一些情况：就是只经过了第一排“禁区”的情况。
比如说这个：
![](https://img-blog.csdn.net/20180822153347264?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NRQlpMWVRpbmE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)


那搞定了所有的“十万个为什么”之后，下面来计算一下方案数：
上面的那个矩形一共走H-A+i-2，向下走，下面的那个矩形一共走A-1+W-i，向下走A-1
所以就是：

```
ans-=C(H-A+i-2,H-A-1)*C(A-1+W-i,A-1)
```


##### 法2
 我们可以把这个矩形进行拆分，把它变成两个矩形，把“禁区”排斥在外，将2个小矩形的方案数相乘。拆分时枚举“断点”
 Like this:
![](https://img-blog.csdn.net/20180822153846131?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0NRQlpMWVRpbmE=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

其它的都跟上面那一种是一样的。
这两种思维模式的不同在于：一个是求出所有方案数，减去不合法的（有点容斥的意味），另一个是直接求合法方案，把不合法的摒除在外。




那这一部分的**方案数的计算**：
上面的小矩形，总步数是H-A+i-2，向右走i-1，下面的小矩形，总步数是A+W-i-1，向下走A-1步。



最后就是代码君啦：
#### code view

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define MOD 1000000007
#define MAXN 200005
#define LL long long
LL inv[MAXN],s[MAXN];
int N;
int H,W,A,B;
LL Pow(LL a,int b) 
{
    LL ans=1;
    while(b) 
	{
        if(b&1) ans=ans*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ans;
}
void Pre() 
{
    s[0]=1;
    for(int i=1; i<=N; i++)
        s[i]=s[i-1]*i%MOD;
    inv[0]=1;
    inv[N]=Pow(s[N],MOD-2);
    for(int i=N-1; i>0; i--)
        inv[i]=inv[i+1]*(i+1)%MOD;
}
LL C(int a,int b) 
{
    if(a<0||b<0) return 1;
    return s[a]*inv[b]%MOD*inv[a-b]%MOD;
}
int main() 
{
    scanf("%d %d %d %d",&H,&W,&A,&B);
	N=H+W-2;
	Pre();
	LL ans=C(H+W-2,H-1);
	for(int i=1;i<=B;i++)
	{
		ans-=C(H-A+i-2,H-A-1)*C(A-1+W-i,A-1)%MOD;
		ans=(ans%MOD+MOD)%MOD;
	}
    printf("%lld\n",ans);
}
```

另一种写法

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 200005
#define MOD 1000000007
#define LL long long
int H,W,A,B,N;
int a[MAXN];
LL s[MAXN],inv[MAXN];
LL Pow(LL a,int b)//快速幂
{
	LL ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return ans;
}

void Pre()
{
	s[0]=1;
	for(int i=1;i<=N;i++)
		s[i]=s[i-1]*i%MOD;   //阶乘
	inv[0]=1;
	inv[N]=Pow(s[N],MOD-2);
	for(int i=N-1;i>0;i--)
		inv[i]=inv[i+1]*(i+1)%MOD;
}

LL C(int a,int b)
{
	if(a<0||b<0) return 1;
	return s[a]*inv[b]%MOD*inv[a-b]%MOD;
}
int main()
{
	scanf("%d %d %d %d",&H,&W,&A,&B);
	N=H+W-2;
	Pre();
	LL ans=0;
	for(int i=B+1;i<=W;i++)
	{
		ans+=C(H-A+i-2,i-1)*C(A+W-i-1,A-1)%MOD;
		ans=(ans%MOD+MOD)%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Zhao_daodao (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_arc058_b) 
## [原题](https://atcoder.jp/contests/arc058/tasks/arc058_b)
# 题目描述
给你一个 $H \times W$ 的矩阵，但是左下角的 $A\times B$ 的矩阵不能走，问有多少种方法能从 $(1,1)$ 走到 $(H,W)$。
## 简化
先不考虑不能走的地方。

对于一个 $X\times Y$ 的矩阵，从 $(1,1)$ 走到 $(X,Y)$。

其中一共要向下走 $X-1$ 步，向右走 $Y-1$ 步。

即一共走 $X+Y-2$ 步，选出 $X-1$ 步向下走，剩下的就向右走。

即一共走 $\binom{n+m-2}{n-1}$ 步。

## 回到原题

对于一个被切割的矩阵，可以将它分成两个矩阵。

即分为 $(1,1)$ 到 $(h-a,b)$ 的一个矩阵，

和 $(1,b+1)$ 到 $(H,W)$ 的一个矩阵。

枚举两个连续的点 $(i,b),(i,b+1) (i\in [1,h-a])$。

其实就是在第一个矩阵的右边界上的点。

对于这 $h-a$ 个连续的点，**所有走法都必恰好经过一次这些点**。

所以只用统计从 $(1,1)$ 到 $(i,b)$ 和 $(i,b+1)$ 到 $(H,W)$ 的走法的乘积，
将所有的乘积加起来就可以了。

形式化的表达：

$ans=\sum\limits_{i=1}^{h-a}\binom{i+b-2}{i-1}\binom{h-i+w-b-1}{h-i}  $

## 注意
在统计组合数时，因为要把矩阵的长和宽求和，**数组记得开两倍**，也就是 $2\times 10^5$。

## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5;
const int mod=1e9+7;
int pre[MAXN];
int inv[MAXN];
int ksm(int a,int b){
    int cnt=1;
    while(b){
        if(b%2)cnt=cnt*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return cnt%mod;
}
void init(int n){
    pre[0]=1;
    for(int i=1;i<=n;i++)
        pre[i]=pre[i-1]*i%mod;
    inv[0]=1;
    for(int i=1;i<=n;i++)
        inv[i]=inv[i-1]*ksm(i,mod-2)%mod;
}
int C(int n,int m){
    if(n<m)return 0;
    return ((pre[n]*inv[m])%mod)*inv[n-m]%mod;
}
int ju(int a,int b){return C(a+b-2,b-1);}
int h,w,a,b;
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>h>>w>>a>>b;//7 8 5 3
    init(h+w);
    int ans=0;
    for(int i=1;i<=h-a;i++)
        ans=(ans+(ju(b,i)*ju(h-i+1,w-b))%mod)%mod;
    cout<<ans;
}
```

---

## 作者：Lyrella (赞：0)

# 题意
你有一个 $H\times W$ 的格子，左下角 $A\times B$ 个格子不能走，求从 $(1,1)$ 到 $(H,W)$ 的路径数量。

# 思路
首先我们要会线性求从 $(x,y)$ 到 $(X,Y)$ 的最短路径数，假设 $x\le X,y\le Y$。
### 从 $(x,y)$ 到 $(X,Y)$
因为从 $(x,y)$ 到 $(X,Y)$ 一共走 $X-x+Y-y$ 步，有 $X-x$ 步向下，$Y-y$ 步向右，就相当于从 $X-x+Y-y$ 个数中选 $X-x$ 个数，不考虑选择顺序。所以选择方案 $=$ 从 $(x,y)$ 到 $(X,Y)$ 的最短路径数 $=C_{X-x+Y-y}^{X-x}$。

之后我们要把问题转换成求从 $(x,y)$ 到 $(X,Y)$ 的最短路径，就可以把这个 $H\times W$ 的网格转化成 $(H-A)\times B$ 和 $H\times(W-B)$ 的网格。（如图）

![](https://cdn.luogu.com.cn/upload/image_hosting/3988un5v.png)

图片中橙色的线段就是我们的**分界线**，每一条从 $(1,1)$ 到 $(H,W)$ 的最短路径**都会**经过这条线。所以我们可以**枚举这条线段**上的每一个点 $(i,B)$。这样就将问题**转化**成了从 $(1,1)$ 到 $(H,W)$ 且**必须**经过 $(i,B)$。

之后问题就得到了简化！我们可以把前一个矩形和后一个矩形的最短路径数求出再乘起来（因为这里显然是**乘法原理**）

具体的，我们可以**枚举** $i$，因为 $1\le i<10^5$。对于每一个 $i$，我们先求出从 $(1,1)$ 到 $(i,B)$ 的最短路径数和从 $(i,B+1)$ 到 $(H,W)$ 的最短路径数，最后再乘起来。

所以最后答案就为
$$\sum_{i=1}^{H-A}(C_{i+B-2}^{i-1}\times C_{H+W-i-B}^{H-i})$$

# 注意
- 开 $\text{long long}$
- 取模
- $\text{fac}$ 和 $\text{inv}$ 数组范围是两倍
- ~~输出~~
# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define Fl(i, a, b) for(int i = a; i <= b; i++)
#define Fr(i, a, b) for(int i = a; i >= b; i--)
#define p 1000000007
#define N 200005
using namespace std;
int fac[N], inv[N];
int qmi(int x, int y){
	int res = 1ll;
	for(; y; y >>= 1){
		if(y & 1)res = res * x % p;
		x = x * x % p;
	}
	return res;
}
int C(int x, int y){
	if(x == y or y == 0)return 1ll;
	return fac[x] * inv[y] % p * inv[x - y] % p;
}
int SUM(int x1, int y1, int x2, int y2, int x3, int y3){
	return C(x2 + y2 - x1 - y1, x2 - x1) * C(x3 + y3 - x2 - y2 - 1, x3 - x2) % p;
}
void solve(){
	int H, W, A, B, ans = 0;
	cin >> H >> W >> A >> B;

	fac[1] = 1;
	Fl(i, 2, N - 5)fac[i] = fac[i - 1] * i % p;
	inv[0] = 1;inv[N - 5] = qmi(fac[N - 5], p - 2);
	Fr(i, N - 6, 1)inv[i] = inv[i + 1] * (i + 1) % p;

	Fl(i, 1, H - A){
		ans += SUM(1, 1, i, B, H, W);
		ans %= p;
	}
	
	cout << ans;
}
signed main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	solve(); return 0;
}
```

---

## 作者：Blancа (赞：0)

### 题意：
给出一个$H \times W$的矩阵，将左下角挖去一个$A \times B$的小矩阵，求从左上角走到右下角的方案数。  
首先看好边界问题，实际上只走了$H + W - 2$步。
### 思路：
这道题第一眼看上去有点容斥的意思，考虑怎么求答案  
如果没有小矩阵，那么方案数很显然是 $C_{H + W - 2}^{H - 1}$，但是有了小矩阵，那么只需要把经过小矩阵的答案的贡献减去就好了。  
再考虑怎么算经过小矩阵的方案数，首先暴力枚举一个位置$i$（小矩阵的上沿），即这条路线在该位置第一次经过小矩阵，此时一定是不合法的方案了，剩下的步数为$W - i + A - 1$ 步（已经走了$H - A + i - 1$步）但是如果在走到$i$位置的时候如果继续向右走，答案就会和$i + 1$的位置重复，所以我们强制要求到达$i$位置之后向下走一步，然后继续走，当$i$为B的时候就不存在和$i + 1$重复的可能了，因此第$B$位置特殊处理，这样就可以得到答案:  
$C_{H + W - 2}^{H - 1} - \sum\limits_{i = 1}^{B - 1} C_{H - A + i - 1}^{H - A}  \times C_{W - i + A - 2}^{W - i} - C_{H - A + B - 1}^{H - A}  \times C_{W - B + A - 1}^{W - B}$  
代码实现：
```c++
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int maxn = 2e6 + 50, mod = 1e9 + 7;
long long H, W, A, B;
long long jc[maxn], ny[maxn], jcny[maxn];
void init () {
	jc[1] = ny[1] = jcny[1] = jcny[0] = 1;
	long long a, b;
	for (register long long i = 2; i <= maxn - 5; ++i) {
		jc[i] = jc[i - 1] * i % mod;
		a = mod / i, b = mod % i;
		ny[i] = (-a * ny[b] % mod + mod) % mod;
		jcny[i] = jcny[i - 1] * ny[i] % mod;
	}
}
inline long long C (int a, int b) {
	if (a == 0 || b == 0 || a == b) return 1;
	return jc[a] * jcny[b] % mod * jcny[a - b] % mod;
}
long long ans;
signed main () {
	init();
	scanf ("%lld%lld%lld%lld", &H, &W, &A, &B);
	ans = C(H + W - 2, H - 1);
	for (register int i = 1; i < B; i++) {
		ans = ((ans - (C(H - A + i - 1, H - A) * C(W - i + A - 2, W - i) % mod)) % mod + mod) % mod;
	}
	ans = ans = ((ans - (C(H - A + B - 1, H - A) * C(W- B + A - 1, W - B) % mod)) % mod + mod) % mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：NBest (赞：0)

不难发现，从 $(a,b)\to(c,d)$，我们一定会向右走 $c-a$ 步，向下走 $d-b$ 步，只不过是顺序的差别，方案数显然为 $\binom{(c-a)+(d-b)}{c-a}$。

然后看这题，左下角都是禁区，那么我们可以先到禁区上面最右侧的部分，再到终点，为了防止重复计算，我们先从 $(1,1)\to(i,B)$（$1\le i\le H-A$），再让 $(i,B)\to(i,B+1)$，最后乘上 $(i,B+1)\to(n,m)$ 的方案数即可。具体的，我们令 $f_{i,j,x,y}$ 表示从 $(i,j)\to(x,y)$ 的方案数，那么答案为：

$$\sum_{i=1}^{H-A}f_{1,1,i,B}\times f_{i,B+1,n,m}$$

## $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int n,m,h,w;
ll fac[200005],ifac[200004],ans;
ll qpow(ll x,ll w){
    ll res=1;
    for(;w;w>>=1,x=x*x%mod)if(w&1)res=res*x%mod;
    return res;
}
void init(int N){
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=fac[i-1]*i%mod;
    ifac[N]=qpow(fac[N],mod-2);
    for(int i=N-1;~i;--i)
        ifac[i]=ifac[i+1]*(i+1)%mod;
}
ll C(int x,int y){
    if(y<0)return 0;
    return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}
int main(){
    cin>>n>>m>>h>>w;
    init(n+m);
    for(int i=1;i<=n-h;i++)
        (ans+=C(i+w-2,i-1)%mod*C(n-i+m-w-1,n-i)%mod)%=mod;
    cout<<ans;
    return 0;
}
```

---

