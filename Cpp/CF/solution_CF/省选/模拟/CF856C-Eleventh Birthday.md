# Eleventh Birthday

## 题目描述

It is Borya's eleventh birthday, and he has got a great present: $ n $ cards with numbers. The $ i $ -th card has the number $ a_{i} $ written on it. Borya wants to put his cards in a row to get one greater number. For example, if Borya has cards with numbers $ 1 $ , $ 31 $ , and $ 12 $ , and he puts them in a row in this order, he would get a number $ 13112 $ .

He is only 11, but he already knows that there are $ n! $ ways to put his cards in a row. But today is a special day, so he is only interested in such ways that the resulting big number is divisible by eleven. So, the way from the previous paragraph is good, because $ 13112=1192×11 $ , but if he puts the cards in the following order: $ 31 $ , $ 1 $ , $ 12 $ , he would get a number $ 31112 $ , it is not divisible by $ 11 $ , so this way is not good for Borya. Help Borya to find out how many good ways to put the cards are there.

Borya considers all cards different, even if some of them contain the same number. For example, if Borya has two cards with 1 on it, there are two good ways.

Help Borya, find the number of good ways to put the cards. This number can be large, so output it modulo $ 998244353 $ .

## 样例 #1

### 输入

```
4
2
1 1
3
1 31 12
3
12345 67 84
9
1 2 3 4 5 6 7 8 9
```

### 输出

```
2
2
2
31680
```

# 题解

## 作者：2008verser (赞：14)

> $T$ 组数据，每组数据给出 $n$ 和长为 $n$ 的序列。
>
> 定义一个序列是否是 11 的倍数为这个序列全部数字首尾相接构成的数字是否是 11 的倍数。
>
> 求给出序列的全部排列中是 11 的倍数的排列个数。
>
> $1\leq T\leq 100,1\leq n\leq 2000,1\leq a_i\leq 10^9,\sum n\leq 2000$。

如果一个数是 11 的倍数，当它的**奇数数位上的数字之和**与**偶数位上的数字之和**之差（奇偶差）是 11 的整数倍。

那么我们关注的只是每个数的奇偶差，以及每个数的最高位在序列中算作奇数数位还是偶数数位（记作最高奇偶性）。

奇偶差可以在输入的时候求出。记 $a_i$ 是第 $i$ 个数字奇数位减偶数位的值。

**我们可以根据最高奇偶性和 $a_i$ 算序列的奇偶差。**这是后面的前提。

## 一

我们可以设一个 dp，$f_{i,j}$ 表示在序列前 $i$ 个数构成的全部排列中奇偶差为 $j$ 的排列个数。（如果奇偶差为负就加成正的，方便 dp）

考虑分讨第 $i$ 个数的最高奇偶性转移。

这玩意转移不了。状态是关于前 $i$ 个数的排列，而这个排列毫无规律可言。

那么我们观察一下最终答案的构成。

长度偶数的 $a_i$ 是不影响后面数字最高奇偶性的，奇偶性的变化出现在全部长度为奇数的数字。

每个奇数长度的数字的左边好多的数字跟它最高奇偶性一样，直到另一个奇数长度的数字。（红点是奇数长度，黑点是偶数的）

![](https://cdn.luogu.com.cn/upload/image_hosting/ofyx0ekk.png)

那么我们可以先求出全部奇数长度的数字构成的序列的满足某一奇偶差的排列数量，然后把偶数长度的数字一个个加上去。

## 二

设 $f_{i,j}$ 表示前 $i$ 个奇数长度数字构成的序列，奇偶差为 $j$ 的排列数。还是缺乏信息不好转移。

再观察一下这一问题的答案构成。设有 $n1$ 个奇数长度数字。

这些数字里面，第一个最高奇偶性为奇、第二个为偶、第三个为奇……

有 $\lceil \frac{n1}{2}\rceil$ 个最高奇偶性为奇，$\lfloor \frac{n1}{2}\rfloor$ 个偶。记为 $qwq,ovo$。

像下边这张图，这是 $n1$ 个奇数长度的数字，红色最高奇偶性是奇，黑色是偶。

![](https://cdn.luogu.com.cn/upload/image_hosting/zze43yzt.png)

原本这个转移不了的 dp 蠢死了！

我们现在就是要让 $n1$ 个数填进这些空里！上一个 dp 中每次我们只关注前 $i$ 个空。此时我们不妨直接考虑全部空。

设 $f_{i,j,k}$ 表示考虑到 $n1$ 个数的前 $i$ 个，填了 $j$ 个红色（最高奇偶性为奇）（黑色就是 $i-j$ 个咯），奇偶差为 $k$ 的排列个数。

这下子就好转移了，分为 $i$ 填红还是黑。然后乘上选这第 $i$ 个的方法数。

如果当前填红色（最高奇偶性为奇），上一步应当填了 $j-1$ 个红色，这一步有 $qwq-(j-1)$ 个红色可选。

上一步奇偶差加上 $a_i$ 等于 $k$，上一步奇偶差为 $k-a_i$。

黑色类似。
$$
f_{i,j,k}=
\begin{cases}
f_{i-1,j-1,k-a_i}\times(qwq-(j-1))+\\
f_{i-1,j,k+a_i}\times(ovo-(i-j)+1)
\end{cases}
$$

## 三

接着我们将 $n2$ 个偶数长度的数字**加上去**。

考虑第一张图，偶数长度的数字跟右边第一个奇数长度的数字最高奇偶性一致。

- 我们可以把第 $i$ 个加到一个奇数长度的数字之前，$i$ 的最高奇偶性与这个数字一致。

- 也可以加到一个已加入的偶数长度的数字之前，$i$ 的最高奇偶性和这个偶数长度的数字一致。

- 特别地，它可以加到最末尾。

设 $g_{i,j,k}$ 表示前 $i$ 个加进去，有 $j$ 个最高奇偶性为奇，奇偶差为 $k$ 的方案数。
$$
g_{0,0,i}=f_{n1,qwq,i}
$$
分讨第 $i$ 个的奇偶性转移。

以奇为例，对应上面三点：

- 这个奇数长度的数字有 $qwq$ 种可选。
- 已加入的、为正的数字有 $j-1$ 个。（算上 $i$ 共 $j$ 个）
- 若奇数长度数字是偶数个。

偶类似。
$$
g_{i,j,k}=
\begin{cases}
g_{i-1,j-1,k-b_i}\times(j-1+qwq+[n1\bmod2==0])+\\
g_{i-1,j,k+b_i}\times(i-1-j+ovo+[n1\bmod 2==1])
\end{cases}
$$
答案即
$$
\sum_{i=0}^{n2} g_{n2,i,0}
$$

```c++
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define rg register
#define ld long double
#define ull unsigned long long
#define epb emplace_back
#define getc getchar
#define ptc putchar
using namespace std;
inline int re() {
	rg int x=0;rg char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while('0'<=c&&c<='9') (x*=10)+=c-48,c=getchar();
	return x;
}
inline void wt(rg int x) { if(x>9) wt(x/10);ptc(x%10+48); }

const int N=2005;
const ll mod=998244353;
int T,n,a[N],b[N];
ll f[N][N>>1][11],g[N][N][11];
int i11(int x) {
	return ((x%11)+11)%11;
}
void ADD(ll&a,ll b) {
	(a+=b)%=mod;
}

int main() {
	T=re();
	while(T--) {
		int n1=0,n2=0;
		n=re();
		for(int i=1;i<=n;i++) {
			int s=0,ty=1;
			char c=getc();
			while(c<'0'||c>'9') c=getc();
			while(c>='0'&&c<='9') {
				s=i11(s+(c-48)*ty);
				ty=-ty;
				c=getc();
			}
			if(ty==1) b[++n2]=s;
			else a[++n1]=s;
		}
		
		int qwq=n1/2+n1%2,ovo=n1/2;
		f[0][0][0]=1;
		for(int i=1;i<=n1;i++) {
			int jmax=min(qwq,i);
			for(int j=0;j<=jmax;j++) {
				for(int k=0;k<11;k++) {
					if(j) ADD(f[i][j][k],f[i-1][j-1][i11(k-a[i])]*(qwq-(j-1))%mod);
					ADD(f[i][j][k],f[i-1][j][i11(k+a[i])]*(ovo-(i-j)+1)%mod);
				}
			}
		}
		for(int i=0;i<11;i++) g[0][0][i]=f[n1][qwq][i];
		for(int i=1;i<=n2;i++) {
			for(int j=0;j<=i;j++) {
				for(int k=0;k<11;k++) {
					if(j) ADD(g[i][j][k],g[i-1][j-1][i11(k-b[i])]*(j-1+qwq+(!(n1&1)))%mod);
					ADD(g[i][j][k],g[i-1][j][i11(k+b[i])]*(i-1-j+ovo+(n1&1))%mod);
				}
			}
		}
		ll ans=0;
		for(int i=0;i<=n2;i++) ADD(ans,g[n2][i][0]);
		printf("%lld\n",ans);
		
		for(int i=1;i<=n1;i++) {
			int jmax=min(qwq,i);
			for(int j=0;j<=jmax;j++) for(int k=0;k<11;k++) f[i][j][k]=0;
		}
		for(int i=1;i<=n2;i++) for(int j=0;j<=i;j++) for(int k=0;k<11;k++) g[i][j][k]=0;
	}
	
}
```

---

## 作者：lahlah (赞：7)


 [在blog里体验更好哦QWQ](https://blog.csdn.net/qq_38944163/article/details/100804933)

____
 题目大意
 

就是给你n个数，然后求按任意顺序摆放形成的数中， 可以被11整除的有多少个

___

 题解
 


~~有一点小学奥数基础的~~可以很容易发现

       
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20190913160057188.)
  
  即一个数如果可以被11整除，那他的奇数位和偶数位之和是相等的
  
  举几个个简单的例子
  
$121 = 11 * 11$ 奇数位之和位$1 + 1 = 2$， 偶数位之和位$2$，相等，所以这个数可以被$11$整除
        
$13112 = 1192 * 11$  奇数位之和位$1 + 1 + 2= 4$，偶数位之和位$3 + 1 = 4$，相等，所以这个数可以被$11$整除

   反之如果和不相等即不能被11整除
   
   可以把问题转换为，奇数位的数字贡献位正的，偶数的贡献位负，然后加起来为0的即是11的倍数
   
   然后我们可以把所有的数按照 *奇数位数* 的和 *偶数位数* 的分类
   
   发现可以分开考虑，因为偶数位的插在两个奇数位中间不会影响到答案，前后的奇偶性还是没有变

然后设位数位奇数位的数的贡献为$a[1...n1]$,位数为偶数位的数的贡献为$b[1...n2]$

先处理位数为奇数位的情况

假设第一位是奇数位,奇数位开始的贡献为正，偶数位开始的贡献为负




  设$f[i][j][k]$表示前i个位数为奇数位的数，有j个数的开头是偶数位，贡献为k的个数



 易得$f[i][j][k] = f[i-1][j][k-a[i]] + f[i-1][j-1][k+a[i]]$
 

 
位数为偶数的同理，


 $g[i][j][k] = g[i-1][j][k-b[i]] + g[i-1][j-1][k+b[i]]$
 


然后就到了最恶心的合并



 发现位数为奇数的只有$f[n1][n1/2][0...10]$
 

这个应该很容易证明吧

 首先枚举位数为偶数的开头是偶数位的个数i,贡献为j
 

 $g[n2][i][j] * f[n1][n1/2][(11 - j) \mod 11]$
 

 奇偶性相同的数可以按照开头的位数是奇数还是偶数来互相交换，其他数的位数奇偶性不受影响
 

 即$(n1/2)! * (n1 - n1/2)! * i! * (n2 - i!)$
 

 最后考虑怎么把位数为偶数的插进去
 

 贡献为正的$n2 - i$个只能插在$n1/2$个之后，或再第一个之前，即有$n1/2 + 1$个位置可以插
 

 即把$n2-i$个球放在$n1/2 + 1$个盒子里，盒子可以空着
 


 设 $p = n2 - i,  q = n1/2 + 1$ 即 $C[p+q][q - 1]$(C表示组合数)
 

 偶数同理
 

 然后把这一大坨东西乘起来求个和就行了
 


看代码吧

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 2005
#define mod 998244353
using namespace std;
int n, a[N], b[N], n1, n2, f[2][N][13], g[2][N][13], c[N][N], pw[N], t;
int calc(int n, int m){
	if(m == 0) return (n == 0);//注意边界
	return pw[n] * c[n + m - 1][m - 1] % mod;
}
signed main(){
	pw[0] = 1; c[0][0] = 1;
	for(int i = 1; i <= 2000; i ++) pw[i] = pw[i - 1] * i % mod, c[i][0] = 1;//预处理阶乘和组合数
	for(int i = 1; i <= 2000; i ++)
		for(int j = 1; j <= 2000; j ++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
	scanf("%lld", &t);
	while(t --){
		scanf("%lld", &n);
		n1 = n2 = 0;
		for(int i = 1; i <= n; i ++){
			int x, p = 0;
			scanf("%lld", &x);
			for(int j = x; j; j /= 10) p ^= 1;
			if(p) a[++ n1] = x % 11; else b[++ n2] = x % 11;//a表示位数为奇数的，b表示位数为偶数的，把它们的贡献处理出来
		}
		memset(f, 0, sizeof f), memset(g, 0, sizeof g);
		f[0][0][0] = g[0][0][0] = 1;
		for(int i = 1; i <= n1; i ++){//dp位数为奇数的情况
			memset(f[i&1], 0, sizeof f[i&1]);
			for(int j = 0; j <= i; j ++)
				for(int k = 0; k < 11; k ++){
					int p = (k - a[i] + 11) % 11, q = (k + a[i]) % 11;
					f[i&1][j][k] = (f[i&1][j][k] + f[(i - 1)&1][j][p]) % mod;
					if(j) f[i&1][j][k] = (f[i&1][j][k] + f[(i - 1)&1][j - 1][q]) % mod;
				}
		}
			
		for(int i = 1; i <= n2; i ++){//dp位数为偶数的情况
			memset(g[i&1], 0, sizeof g[i&1]);
			for(int j = 0; j <= i; j ++)
				for(int k = 0; k < 11; k ++){
					int p = (k - b[i] + 11) % 11, q = (k + b[i]) % 11;
					g[i&1][j][k] = (g[i&1][j][k] + g[(i - 1)&1][j][p]) % mod;
					if(j) g[i&1][j][k] = (g[i&1][j][k] + g[(i - 1)&1][j - 1][q]) % mod;
				}
		}
		int ans = 0;
		for(int i = 0; i <= n2; i ++)
			for(int j = 0; j < 11; j ++){
				ans = (ans + g[n2&1][i][j] * f[n1&1][n1 / 2][(11 - j) % 11] % mod * pw[n1 / 2] % mod * pw[n1 - n1 / 2] % mod * calc(i, n1 - n1 / 2) % mod * calc(n2 - i, n1 / 2 + 1) % mod) % mod;//算贡献，上面写的
			}
		printf("%lld\n", ans);	
	}
	
	return 0;
}

```
啊


坑点


要注意内存，需要滚掉一维



---

## 作者：Yyxxxxx (赞：4)

模拟赛好duliu，出了这道题。   
## 题意
有几个数字，把他们拼起来，求能被 $11$ 整除的个数。
## $Solution$
我们在小学二年级就知道：一个数能被 $11$ 整除，当且仅当其奇偶位上的数字和相同。   
我们可以看做奇数贡献为正，偶数贡献为负，   
我们首先可以把每个数字都先 $\mod 11$ ，将所得结果拼成一个 $11$ 进制的数。   
最后各位相加是被 $11$ 整除的  

然后我们考虑原数数位：
- 如果原数是一个奇数位数的数字，那么合并之后就会使之后的位数奇偶互换
- 如果原数是一个偶数位数的数字，那么合并之后之后数字不回收到影响。  

于是我们分开考虑。  
奇数数位对 $11$ 取模的结果我们用数组 $A$ 来表示；  
偶数数位对 $11$ 取模的结果我们用数组 $B$ 来表示；  
有两个 $dp$ 数组 $f_{i,j,k},g_{i,j,k} $
$f$ 为奇数，$g$ 为偶数，均表示前 $i$ 个数字， $j$ 个贡献为负，结果对 $11$ 取模的结果为 $k$ ， $dp$ 方程为:
$$f[i][j][k]=f[i-1][j][k-A_i]+f[i-1][j-1][k+A_i]$$
即如果前 $i-1$ 个数已经把负个数用完了，那么第 $i$ 位贡献是正的，所以前 $i-1$ 位的结果是 $11-A_i$ ；而反之，第 $i$ 位贡献是负的，前 $i-1$ 位的结果是 $11+A_i$ 。显然，第 $i$ 种情况我们只能从第 $i-1$ 种情况推得。为了节省空间，我们使用滚动数组。   
这边给出数组 $f$ 的代码
### $code$
```
f[0][0][0]=1;
for(int i=1; i<=lena; i++) {//lena是数位奇数的个数
		memset(f[i&1],0,sizeof(f[i&1]));
		for(int j=0; j<=i; j++)
			for(int k=0; k<11; k++) {
				int x=(k-a[i]+11)%11;
				int y=(k+a[i]+11)%11;
				f[i&1][j][k]=(f[i&1][j][k]+f[(i-1)&1][j][x])%mod;
				if(j!=0)f[i&1][j][k]=(f[i&1][j][k]+f[(i-1)&1][j-1][y])%mod;
			}
	}
```
那么答案是如何统计呢？    
显然有对于原数数位是奇数的 $I$ 个数要有 $\lfloor\dfrac{I}{2}\rfloor$    
我们枚举原数数位是偶数的个数，   
由于没有顺序，我们还要全排列，然后奇数放在偶数之间用插板。于是我们就可以得到这个式子：     
$$A=g[lenb][i][j]\times f[lena][\dfrac{lena}{2}][j]$$
$$B=\dfrac{lena}{2}!\times (lena-\dfrac{lena}{2})!\times i! \times (lena-b)!$$
$$C=\dbinom{i+lena-\dfrac{lena}{2}-1}{lena-\dfrac{lena}{2}-1}\times \dbinom{lenb-i+\dfrac{lena}{2}}{\dfrac{lena}{2}}$$
$$Ans=\sum\limits_{i=0}^{lenb}\sum\limits_{j=0}^{10} A\times B\times C$$
以上 $\dfrac{a}{b}$ 均表示 $\lfloor\dfrac{a}{b}\rfloor$

~~式子真长。。。~~
### $code$
```
int ans=0;
	for(int i=0; i<=lenb; i++)
		for(int j=0; j<11; j++) {
			int a=g[lenb&1][i][j]*f[lena&1][lena/2][(11-j)%11]%mod;
			int b=pw[lena/2]*pw[lena-lena/2]%mod;
			int c=calc(i,lena-lena/2)*calc(lenb-i,lena/2+1)%mod;
			ans=(ans+a*b%mod*c%mod)%mod;
		}
	printf("%lld\n",ans);
```
不给出完整代码~~因为都是复读机~~请大家自己思考





---

## 作者：Fading (赞：2)

讲真的，这题挺难，我想了很久，突发奇想才想出来（好像比其他人的要简单一些？不用这么麻烦）

首先，关于$11$整除有什么性质？就是奇数位的和与偶数位的和$\bmod\ 11$同余。

然后怎么做呢？发现这没法直接组合，于是我们采用 dp 。怎么 dp 呢？

一个很简单的想法就是设$f_{i,j}$表示前$i$个数，奇数偶数的差$\bmod\ 11$的值。

但是这并不好转移，因为你不知道插入某一位的时候，奇偶位变化的情况。怎么用状态表示出答案是一个关键问题？状压？不可取。

我们发现刚才的 dp 是关于前$i$个数的，而且这前$i$个数居然毫无规律可言，随便排布，这不太行。然后我们就能想到，先插入奇长度，再插入偶长度，这样插入一个偶长度的数对下一个偶长度的数插入没有影响。

先考虑插入奇长度。设$g_{i,k}$表示前$i$个数，奇偶同余值为$k$的排列数。怎么还是无法转移？怎么办？

~~注意到数据范围只有2000~~ 发现奇数位个数-偶数位个数的绝对值相差$1$，而且都是 奇偶奇偶... 这样的，所以我们换个角度：

我们可以在插入的时候给这个数提前标上一个正负号，表示这一个数对答案的贡献是否要取反（即在这个排列里，最低位是奇贡献还是偶贡献）。

然后，设$g_{i,j,k}$表示前$i$个数，正负个数差为$j$，奇偶同余值为$k$的排列数，就可以转移了。转移时考虑当前这个数标正还是标负。

最后再用组合数学处理一下，就可以得到只考虑奇位数，奇偶同余为$k$的方案数了。

接下来插入偶长度。有了上面的经验，这个就显得非常简单。设$f_{i,j,k}$表示前$i$个数，有多少个"空"是偶数位（相当于再中间插空，对原来的空也没有影响），奇偶同余值为$k$的排列数，就可以转移了。

这时候转移也需要分类讨论，这个数贡献到奇位还是偶位。

那么这题就做完了。是一道很好的数数题，~~不过还跑得挺慢的？~~

代码如下：~~为了膜拜 ljc，我把 11 设成了 ijc~~

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
#define ijc 11
ll fac[2101],n,m;
struct node{
	int len,x;
	inline void get(){
		x=len=0;
		ll xx=read(),op=1;
		while (xx){
			x+=xx%10*op+ijc;x%=ijc;
			xx/=10;len++;op*=-1;
		}
	}
}a[2101];
inline bool cmp(node a,node b){
	return ((a.len%2)>(b.len%2));
}
ll g[2][4120][11],f[2][2020][11];
int main(){
	fac[0]=1;
	for (ll i=1;i<=2000;i++) fac[i]=fac[i-1]*i%ljc;
	int T=read();
	while (T--){
		n=read();
		for (int i=1;i<=n;i++){
			a[i].get();
		}
		bool cur=0;
		memset(g,0,sizeof g);
		memset(f,0,sizeof f);
		sort(a+1,a+1+n,cmp);
		register int i,ZERO=n+2;
		g[cur][ZERO][0]=1;
		for (i=1;i<=n;i++){
			if (a[i].len%2==0) break;
			cur^=1;
			memset(g[cur],0,sizeof g[cur]);
			for (int j=ZERO-i;j<=ZERO+i;j++){
				for (int k=0;k<11;k++){
					g[cur][j][k]=(g[cur][j][k]+g[cur^1][j+1][(k-a[i].x+ijc)%ijc])%ljc;
					g[cur][j][k]=(g[cur][j][k]+g[cur^1][j-1][(k+a[i].x+ijc)%ijc])%ljc;
				}
			}			
		}
		i--;
		for (int k=0;k<11;k++){
			int op=((i%2==1)?i/2+1:i/2);
			f[cur][op][k]=g[cur][op-i/2+ZERO][k]*fac[op]%ljc*fac[i/2]%ljc;
		}
		i++;
		for (;i<=n;i++){
			cur^=1;
			memset(f[cur],0,sizeof f[cur]);
			for (int j=0;j<=i;j++){
				for (int k=0;k<11;k++){
					ll eve=j,od=i-j;
					f[cur][j][(k-a[i].x+ijc)%ijc]=(f[cur][j][(k-a[i].x+ijc)%ijc]+f[cur^1][j][k]*1ll*od%ljc)%ljc; 
					f[cur][j+1][(k+a[i].x+ijc)%ijc]=(f[cur][j+1][(k+a[i].x+ijc)%ijc]+f[cur^1][j][k]*1ll*eve%ljc)%ljc;
				}
			}
		}
		ll ans=0;
		for (int i=0;i<=n;i++) ans=(ans+f[cur][i][0])%ljc;
		cout<<(ans%ljc+ljc)%ljc<<endl;
	}
	return 0;
}
```



---

## 作者：Jordan_Pan (赞：1)

## 0

原题链接：[luogu](https://www.luogu.com.cn/problem/CF856C) & [CF](https://codeforces.com/problemset/problem/856/C)

在任务清单里放了半年，今天终于做出来了 qwq，不得不写题解了。

## 1

能被 $11$ 整除的数长什么样子？它的奇数位之和与偶数位之和应当模 $11$ 同余。

我们不妨把一个数的价值定为从前往后奇数位之和减去偶数位之和模 $11$ 的值。例如，我们把 114514 的值赋为 $(1+4+1)-(1+5+4)=7$。

整个序列大概是这样的（画的好丑啊，不想改了）：

https://img2024.cnblogs.com/blog/3502765/202502/3502765-20250201212833578-166982961.png

~~洛谷怎么显示不了，这么坏。~~

一个数的价值对于整个序列拼成的数的价值会有什么贡献呢？可能为 $+x$，也可能为 $-x$，这取决于这个数在序列中的起始位置的奇偶性。比如图中起始下标为 $1,3,9$ 的数 $76,5,9$ 产生了正贡献。

为了方便，我们称奇位的数为“奇数”（如 $5,233,1234567$ 等，图中标蓝），偶位的数为“偶数”。容易发现，如果这个数是“奇数”，排在他之后的元素正负性要反转一下，如果是“偶数”则不变。于是我们先填“奇数”，把“偶数”填在空位里就好。

后面就是计算了。产生正贡献的“奇数”数量是一定的（这应该挺显然的，等于“奇数”数量除以二向上取整），“偶数”则不一定。为了让价值加起来的结果为 $0$（这样才能被 $11$ 整除），我们考虑对两者分别 dp。

记 $f_{i,j,k}$ 表示前 $i$ 个“奇数”，其中选了 $j$ 个产生正贡献（相应地有 $i-j$ 个产生负贡献），目前的总价值 $\bmod 11 =k$，这样的排列数有多少个。分这个数选正还是选负转移即可，从 $i-1$ 转移到 $i$ 时，空位数就是填正空位的 $j$ 或者填负空位的 $i-j$。

接下来是对“偶数”的 dp，记 $g_{i,j,k}$ 意义同上。这里需要提前计算空位数量，填完“奇数”后排列就形成了一个“框架”，其中空位数为“奇数”数量加一，产生正贡献的空位和负贡献的空位交错排列。之后每在正空位填一个“偶数”，正空位数就会多一个（可以填在这个“偶数”的左边和右边）。同样的，填入“偶数”的数量我们已经记在状态里了，就是 $j$。负空位反之。

最后我们统计答案，如果有 $x$ 个奇数，$y$ 个偶数，枚举 $f_{x,\lceil \frac{x}{2} \rceil,k1}$ 中的 $k1$，$g_{y,j,k2}$ 中的 $j$ 和 $k2$，如果 $k_1+k2+2 \bmod 11 =0$，就能对答案产生二者相乘的贡献。

然后我们就做完了。

## 2

代码~~感觉完全看不了啊~~。dp 数组大小有点危险，滚了一下。

```cpp
constexpr int _=2005,B=10,M=11,mod=998244353;
void P(int&x,int y){if((x+=y)>=mod)x-=mod;}
int n;
std::vector<int>a,b;
int jishugeshu,oushugeshu,zhengshuliang,fushuliang,zhengkongwei,fukongwei;
int f[2][_][11],cf,g[2][_][11],cg,ans;
void solve(){
	rd(n);a.clear();b.clear();
	for(int i=1,x;i<=n;i++){
		rd(x);int val=0,j;
		for(j=1;x;j++,x/=B){
			if(j&1)val+=x%B;
			else val-=x%B;
		}
		val%=M;
		if(val<0)val+=M;
		if(j&1)b.push_back(M-val);
		else a.push_back(val);
	}
	jishugeshu=a.size();oushugeshu=b.size();
	cf=0;
	memset(f[cf],0,sizeof f[cf]);
	f[cf][0][0]=1;
	for(int i=1,v;i<=jishugeshu;i++){
		cf^=1;v=a[i-1];
		memset(f[cf],0,sizeof f[cf]);
		for(int j=1;j<=i;j++)
			for(int k=0;k<M;k++)
				P(f[cf][j][(k+v)%M],f[cf^1][j-1][k]);
		for(int j=0;j<i;j++)
			for(int k=0;k<M;k++)
				P(f[cf][j][k],f[cf^1][j][(k+v)%M]);
	}//这里的转移没有计算填了哪一个位置，提到外面去了 
	zhengkongwei=jishugeshu/2+1;
	fukongwei=jishugeshu+1-zhengkongwei;
	cg=0;
	memset(g[cg],0,sizeof g[cg]);
	g[cg][0][0]=1;
	for(int i=1,v;i<=oushugeshu;i++){
		cg^=1;v=b[i-1];
		memset(g[cg],0,sizeof g[cg]);
		for(int j=1;j<=i;j++)
			for(int k=0;k<M;k++)
				P(g[cg][j][(k+v)%M],1ll*g[cg^1][j-1][k]*(zhengkongwei+j-1)%mod);
		for(int j=0;j<i;j++)
			for(int k=0;k<M;k++)
				P(g[cg][j][k],1ll*g[cg^1][j][(k+v)%M]*(fukongwei+i-1-j)%mod);
	}
	fushuliang=jishugeshu/2;
	zhengshuliang=jishugeshu-fushuliang;
	ans=0;
	for(int i=0;i<=oushugeshu;i++){
		P(ans,1ll*f[cf][zhengshuliang][0]*g[cg][i][0]%mod);
		for(int j=1;j<M;j++)
			P(ans,1ll*f[cf][zhengshuliang][j]*g[cg][i][M-j]%mod);
	}
	for(int i=1;i<=zhengshuliang;i++)
		ans=1ll*ans*i%mod;
	for(int i=1;i<=fushuliang;i++)
		ans=1ll*ans*i%mod;
	//这里因为奇数的正负数量已经确定了，枚举排列就放到这里了 
	printf("%d\n",ans);
}
int main(){
	int T;rd(T);
	for(;T;T--)solve();
}
```

---

## 作者：Kreado (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF856C)。

本文所有浮点运算均向下取整。

## 思路

根据小学奥数知识，假如一个数能被 $11$ 整除，当且仅当这个数的**奇数位和偶数位数位上的数字之和的差为 $11$ 的倍数**。

比如 $121$，奇数位上的数字之和为 $1+1$，偶数位上的数字之和为 $2$，$2-(1+1)=0$，所以它能被 $11$ 整除。

Proof：

将奇数和偶数位分离开得到数 $x=\displaystyle \sum_{i=1}^n 10^{2i-2}a_{2i-1}+\sum_{i=1}^n 10^{2i-1}a_{2i}$，$a_i$ 表示数 $x$ 第 $i$ 位上的数字，位数不足用 $0$ 补充。

从中抽离出奇数位和偶数位，也就是 $x_1=\displaystyle\sum_{i=1}^n a_{2i-1}(10^{2i-2}-1)+\sum_{i=1}^n a_{2i},x_2=\sum_{i=1}^n a_{2i}(10^{2i-1}+1)-\sum_{i=1}^na_{2i-1}$。

有 $n=x_1+x_2$，因为 $10^n\equiv (-1)^n\pmod {11}$。

当 $n$ 是偶数时有 $10^n\equiv 1\pmod {11}$。

当 $n$ 是奇数时有 $10^n\equiv -1\pmod {11}$。

所以有 $\displaystyle\sum_{i=1}^n a_{2i-1}(10^{2i-2}-1)\equiv 0\pmod {11},\sum_{i=1}^n a_{2i}(10^{2i-1}+1)\equiv 0\pmod {11}$。

那么有 $x_1+x_2=x\equiv \displaystyle\sum_{i=1}^n a_{2i}-a_{2i-1}\pmod {11}$，所以数 $x$ 能被 $11$ 整除当且仅当它奇数位和偶数位数位上的数字之和的差为 $11$ 的倍数。

Q.E.D.

有了这个定理，那么我们可以设计 dp 状态。

不妨将奇数看做**正贡献**，偶数看做**负贡献**，

考虑原数**数位**，分奇偶性讨论。

- 若原数是一个奇数位数的数字，那么合并之后就会使位数奇偶互换
- 若原数是一个偶数位数的数字，那么合并之后位数奇偶性不会受到影响。

奇数数位的数对 $11$ 取模的结果我们存放到 $A$ 数组，令其长度为 $|A|$。

偶数数位的数对 $11$ 取模的结果我们存放到 $B$ 数组，令其长度为 $|B|$。

设计状态 $f_{i,j,k}$ 表示在奇数数位的数中，遍历到前 $i$ 个数字，有 $j$ 个数字开头是**偶数位**，最终得到贡献模 $11$ 的结果为 $k$ 的方案数。

当然还有偶数 $g_{i,j,k}$ 表示在偶数数位的数中，遍历到前 $i$ 个数字，有 $j$ 个数字开头是**偶数位**，最终得到贡献模 $11$ 的结果为 $k$ 的方案数。

有状态转移：

$$f_{i,j,k}=f_{i-1,j,k-A_i}+f_{i-1,j-1,k+A_i}$$

$$g_{i,j,k}=g_{i-1,j,k-A_i}+g_{i-1,j-1,k+A_i}$$

注意，$11n^2$ 的数组开不下，所以我们要滚动数组。

接下来考虑如何合并 $f,g$ 数组得到最终的答案。

首先枚举偶数位数且有 $i$ 个数开头是偶数位，其贡献为 $j$。

那么贡献为 $g_{|B|,i,j}\times f_{|A|,|A|/2,(11-j)\bmod 11}$。

当然，我们可以随便排，因此我们需要乘上排列数 $(|A|/2)!\times (|A|-|A|/2)!\times i!\times (|B|-i)!$，最后考虑插入位数位偶数的数，即将 $(|B|-i)!$ 个数插入 $|A|/2$ 个数的方案数，为 $\dbinom{|B|-i+|A|/2}{|A|/2}$，同理可得 $\dbinom{i+|A|-|A|/2-1}{|A|-|A|/2-1}$。

因此最终答案就是：

$$\sum_{i=0}^{|B|}\sum_{j=0}^{10}g_{|B|,i,j}\times f_{|A|,|A|/2,(11-j)\bmod 11}\times (|A|/2)!\times (|A|-|A|/2)\times i!\times (|B|-i)!\times \dbinom{|B|-i+|A|/2}{|A|/2}\times \dbinom{i+|A|-|A|/2-1}{|A|-|A|/2-1}$$

其实就是将上面得到的结果乘起来。



---

## 作者：qczrz6v4nhp6u (赞：0)

### Solution

注意到 $10\equiv -1\pmod{11}$，这说明一个数对整个序列的贡献只与其位置的奇偶性有关。

考虑直接 DP。设 $f_{i,j,k}$ 表示已经填了 $i$ 个数，有 $j$ 个可插入的奇数位置，当前序列对 $11$ 取模结果为 $k$ 的答案。但是发现在一个位置插入数后可能会高位的奇偶性，无法转移。

思考什么时候会影响高位的奇偶性。不难发现只有当前数的位数是奇数时会影响。于是考虑先做位数为奇数的，再做位数为偶数的。

但是对于奇数位数的数，此时仍然需要考虑高位奇偶性改变的情况。考虑不使用“插入”来刻画，而是在一开始就钦定好它填在哪个位置。发现此时是容易转移的。

于是就做完了。时间复杂度 $O(\sum n^2)$，带 $11$ 倍常数。[submission](https://codeforces.com/contest/856/submission/287517981)。

---

