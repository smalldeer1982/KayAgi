# Plant

## 题目描述

Dwarfs 种了一株非常有意思的植物，这株植物像一个方向向上的三角形。它有一个迷人的特点，那就是在一年后一株方向向上的三角形的植物就会被分成 4 株三角形的植物：它们当中的三株方向是向上的，一株方向是向下的。
又一年之后，每株植物都会分成四个，规则如上。之后的每年都会重复这一过程。下面的图说明了这一发展过程。
![图](https://cdn.luogu.org/upload/vjudge_pic/CF185A/06a04cdb90280e6ac952fa1883923dcff872c965.png)
请帮助 Dwarfs 算出 $n$ 年后将会有多少个方向向上的三角形。

## 样例 #1

### 输入

```
1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
```

### 输出

```
10
```

# 题解

## 作者：Kevin_Wa (赞：14)

 本题的意思是有一株植物，刚种下原来有1片叶子，每年都能从原来的叶子上再长出3片。

要求第$n$年向上的叶子。

首先明确，每年会在原先向上的叶子上长出$3$片向上的叶子。

原先向下的叶子上长出$1$片向上的叶子。 

所以设$a$[$0$]=$1$;$b$[$0$]=$0$;

$a$为向上的叶子数；$b$为向下的叶子数。
 
则递推转移方程为

$a$[$i$]=$a$[$i$-$1$]*$3$+$b$[$i$-$1$];

$b$[$i$]=$b$[$i$-$1$]*$3$+$a$[i-$1$]; 

而$n$的范围太大所以要想办法。

我们把递推转移方程做差得到$a$[$i$]-$b$[$i$] = $2$*($a$[$i$]-$1$-$b$[$i$]-$1$)，可得到

第i年两者之差的公式，又可知每年有$4^i$个三角，即 $a$[$i$]+$b$[$i$]=$4^i$, $a$[$i$]-$b$[$i$]=$2^n$ 两者作和

除2即为答案，快速幂即可解决。

即$a$[$n$]=$2^{n*2-1}$+$2^{n-1}$;

快速幂

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
ll n;
ll p(ll a, ll k)
{
    a %= mod;
    ll ans = 1;
    while(k)
    {
        if(k&1) ans = ans*a%mod;
        a = a*a%mod;
        k /= 2;
    }
    return ans;
}
int main(void)
{
    while(cin >> n)
    {
        if(!n) puts("1");
        else printf("%I64d\n", (p(2, n-1)+p(2, 2*n-1))%mod);
    }
    return 0;
}
```



---

## 作者：EuphoricStar (赞：5)

## 思路

矩阵加速线性递推。

设 $f_{i,0}$ 为 $i$ 年后向上的三角形的个数，$f_{i,1}$ 为 $i$ 年后向下的三角形的个数，则我们可以得到以下的递推式：

$$f_{i,0} = f_{i-1,0} \times 3 + f_{i-1,1}$$

$$f_{i,1} = f_{i-1,1} \times 3 + f_{i-1,0}$$

初始为 $f_{0,0} = 1$，$f_{0,1} = 0$。

然后我们会发现，因为 $n \le 10^{18}$，所以裸的递推过不去。

这时候矩阵就派上用场了。

根据刚才推出来的递推式，我们可以得到：

$$\begin{bmatrix}f_{i-1,0}&f_{i-1,1}\end{bmatrix}\begin{bmatrix}3&1\\1&3\end{bmatrix} = \begin{bmatrix}f_{i,0}&f_{i,1}\end{bmatrix}$$

于是就可以愉快地用矩阵快速幂求解了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = 1000000007;

ll n;
struct matrix {
    int n;
    ll a[110][110];
} a;

matrix mul(matrix &a, matrix &b) {
    matrix res;
    res.n = a.n;
    memset(res.a, 0, sizeof(res.a));
    for (int i = 1; i <= res.n; ++i) {
        for (int j = 1; j <= res.n; ++j) {
            for (int k = 1; k <= res.n; ++k) {
                res.a[i][j] = (res.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
            }
        }
    }
    return res;
}

matrix qpow(matrix a, ll p) {
    matrix res;
    res.n = a.n;
    memset(res.a, 0, sizeof(res.a));
    res.a[1][1] = 1;
    while (p) {
        if (p & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        p >>= 1;
    }
    return res;
}

int main() {
    scanf("%lld", &n);
    a.n = 2;
    a.a[1][1] = a.a[2][2] = 3;
    a.a[1][2] = a.a[2][1] = 1;
    matrix ans = qpow(a, n);
    printf("%lld", ans.a[1][1]);
    return 0;
}
```


---

## 作者：QTcyy (赞：3)

## 本题可用两种方法求解
#### 常规方法相信其他题解已经很清楚了
我们只要设两个函数$f_n$和$g_n$分别表示第$n$次变化时**向上**的三角形个数和**向下**的三角形个数

本题的变换其实就是把所有的小三角形的三条边中点连在一起出现三个全等的小小三角形

### 那这个小小三角形在第$n$次变换的时候会有几个呢？

我们发现，每个小三角形在变换一次后会**变出4个小小三角形**。其中，如果小三角形的方向是**向上**的，那么**三条中线**连接形成的那个小小三角形的方向是**向下**的，而其他三个小小三角形是**向上**的；相反的，如果小三角形的方向是**向下**的，那么变换一次后会**出现1个向上**的小小三角形，**3个向下**的小小三角形。

同时，第$n$次变换出现的总三角形数是$4^n$，应为每次每个小三角形都会变出4个小小三角形；第$n$次变换时向上的三角形数减去向下的三角形数为$2^n$

#### 根据这个结论，我们就可以列出两个递推式
1. $$f_n=f_{n-1}*3+g_{n-1}$$
2. $$g_n=g_{n-1}*3+f_{n-1}$$

#### 用加减消元法可以推出

3. $$f_n-g_n=2*(f_{n-1}-g_{n-1})=2*2^{n-1}=2^n$$

4. $$f_n+g_n=4(f_{n-1}+g_{n-1})=4*4^{n-1}=4^n$$

#### 接着算出$f_n$

$$(3)+(4)=2*f_n=(2^n+4^n)/2$$

### 所以直接用快速幂求解即可

### 可参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL MOD = 1e9+7;

LL n;

inline LL qpow(LL a,LL b){
    a%=MOD;
    LL res=1;
    while (b){
        if (b&1)
            res=(res*a)%MOD;
        a=(a*a)%MOD;
        b>>=1;
    }
    return res%MOD;
}

int main(void){
    cin>>n;
    if (n==0){
        printf("1\n");
        return 0;
    }
    LL ans=qpow(2,n-1)+qpow(2,2*n-1);
    cout<<ans%MOD<<endl;

    return 0;
}
```


------------
------------
### 本题还有一种矩阵快速幂的做法

没学过矩阵乘法的可以先学了再来看qwq

根据刚才推出来的公式，我们可以得到这样一个矩阵

$$
\left[ \begin{matrix} f_n\\ g_n \end{matrix}\right]=
\left[ \begin{matrix} 3 & 1\\ 1 & 3 \end{matrix}\right]
\left[ \begin{matrix} f_{n-1}\\ g_{n-1} \end{matrix}\right]
$$

所以我们就可以得到一个矩阵快速幂的通项公式

$$
\left[ \begin{matrix} f_n\\ g_n \end{matrix}\right]=
\left[ \begin{matrix} 3 & 1\\ 1 & 3 \end{matrix}\right]^{n}
\left[ \begin{matrix} f_{1}\\ g_{1} \end{matrix}\right]
$$

所以就可以进行矩阵快速幂运算了

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N = 4;
const LL MOD = 1e9+7;

struct mat{
    LL a[N][N];
    mat(){
        memset(a,0,sizeof(a));
    }
    mat operator*(const mat T)const{
        mat res;
        for (register int i=0;i<2;i++)
            for (register int j=0;j<2;j++)
                for (register int k=0;k<2;k++)
                    res.a[i][j]=(res.a[i][j]+a[i][k]*T.a[k][j])%MOD;
        return res;
    }
    mat operator^(LL now)const{
        mat res,x=*this;
        for (register int i=0;i<2;i++)
            res.a[i][i]=1;
        while (now){
            if (now&1)
                res=res*x;
            x=x*x;
            now>>=1;
        }
        return res;
    }
};

LL n;

int main(void){
    cin>>n;
    if (!n){
        printf("1\n");
        return 0;
    }
    int std1[2][2]={
        {3,1},
        {1,3},
    };
    mat num,num2;
    for (register int i=0;i<2;i++)
        for (register int j=0;j<2;j++)
            num.a[i][j]=std1[i][j];
    num2.a[0][0]=1;num2.a[1][0]=0;
    mat num3=num^(n);
    mat ans=num2*num3;
    cout<<ans.a[0][0]%MOD<<endl;

    return 0;
}
```


---

## 作者：XL4453 (赞：1)

### 解题思路：

~~蓝题就这？~~

设 $f_{i,0}$ 表示第 $i$ 年向上的三角形个数，$f_{i,1}$ 为第 $i$ 年向下的三角形个数。

那么就有：$f_{1,0}=1$ 以及 $f_{1,1}=0$。

考虑推导，每一个向上的三角变成三个向上的和一个向下的，每一个向下的变成一个向上的和三个向下的，形式化的，有 $f_{i+1,0}=3\times f_{i+1,0}+f_{i,1}$ 以及 $f_{i,1}=3\times f_{i,1}+f_{i,0}$。

---

直接求解显然超时，考虑用矩阵优化一下。

$\begin{vmatrix}f_{i,0}&f_{i,1}\end{vmatrix} \times \begin{vmatrix}3&1\\1&3\end{vmatrix}$

$=\begin{vmatrix}f_{i,0}\times 3+f_{i,1}&f_{i,1}\times 3+f_{i,0}\end{vmatrix}$

$=\begin{vmatrix}f_{i+1,0}&f_{i+1,1}\end{vmatrix}$

然后对于那个 $\begin{vmatrix}3&1\\1&3\end{vmatrix}$ 求一下快速幂就行了。

---
### 代码：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const long long MOD=1000000007;
struct str{
	long long sq[10][10];
	int n,m;
	void clear(){
		memset(sq,0,sizeof(sq));
		n=m=0;
	}
	str operator*(str b){
		str c;
		c.clear();
		for(int i=1;i<=n;i++)
		for(int j=1;j<=b.m;j++)
		for(int k=1;k<=m;k++)
		c.sq[i][j]=(c.sq[i][j]+(sq[i][k]*b.sq[k][j])%MOD)%MOD;
		c.n=n;
		c.m=b.m;
		return c;
	}
};
str pow(str a,long long n){
	str ans;
	ans.clear();
	ans.sq[1][1]=1;
	ans.n=1;ans.m=2;
	while(n){
		if(n&1)ans=ans*a;
		a=a*a;
		n=n>>1;
	}
	return ans;
}
long long n;
str a,ans;
int main(){
	scanf("%I64d",&n);
	a.clear();
	a.sq[1][1]=3;a.sq[2][1]=1;
	a.sq[1][2]=1;a.sq[2][2]=3;
	a.m=a.n=2;
	ans=pow(a,n);
	printf("%I64d\n",ans.sq[1][1]);
	return 0;
}
```



---

## 作者：1lgorithm (赞：1)

## 意思其它题解已经解释清楚了，那么我就来说说一种简单的写法吧。
这道题是求这株植物向上的叶子的个数。

我们可以发现第n个图里最下面朝上的三角形为2^n个，再往上是2^n-1个，以此类推。所以我们就推出的这个题的答案:

#### 2^n*(2^n+1)/2.

2^n次方可以用快速幂，那么这道题就解出来了。

代码：
```cpp
#include<iostream>
using namespace std;
#define ll long long
const int mod=1e9+7;
long long qpmod(long long a,long long b,long long p){
    long long ans=1;
    while(b){
    if(b&1){
        ans=ans*a%p;
    }
    a=a*a%p;
    b>>=1;
    }
    return ans;
}
int main(){
    ll a;
    cin>>a;
    ll x=qpmod(2,a,mod);
    cout<<x*(x+1)/2%mod;
}
```


### 彩蛋：优化方法。

费马小定理:

如果p是质数，且a,p互质，则a^(p-1)%p=1.

在这道题里，2^(1e9+6)%(1e9+7)=1.

所以答案就转化为2^x*(2^x+1)/2,

其中x=a%(1e9+6).

代码：只需要在把x变成qpmod(2,a%(mod-1),mod)即可。



---

## 作者：lamboo (赞：1)

没头绪？？？打表找规律大法

发现第i个图形与第i-1个图形有关

轻而易举的写出了递推方程
```cpp
up[i]=3*up[i-1]+down[i-1];
down[i]=3*down[i-1]+up[i-1];  //不用数组也没关系
```
输出：

|n | 1 | 2 | 3 | 4 |
| :----------- | :----------- | :----------- | :----------- | :----------- |
|ans | 3 | 10 | 36 | 136 |

大家有没有发现什么？？？

可能发现不了······

呃···分解因数看一看

|n | 1 | 2 | 3 | 4 |
| :----------- | :----------- | :----------- | :----------- | :----------- |
|ans | 3=1×3 | 10=2×5 | 36=4×9 | 136=8×17 |

现在应该发现了吧······

ans=2^(n-1)×(2^n+1)

为什么会这样呢？？？

我们感性地理解一下

向上的三角形从底层向上递减，且每次减1

最底层的三角形每次分裂1倍，所以最底层共有2^n个向上的三角形

与上面的三角形形成了公差为1的等差数列，且首项为1，末项为2^n

利用等差数列求和公式 ans=(2^n+1)×2^n/2

化简一下  ans=2^(2n-1)+2^(n-1)

注意到2^(2n-1)可以用2^(n-1)表示

我们令w=2^(n-1)，则ans=w+2*w*w

由于n很大，所以使用快速幂加速（好像还能用矩阵优化，我太弱了）

快速幂不讲了，不会的点这里：[传送门](https://www.luogu.org/blog/Sleep-in-the-ground/kuai-su-mi)

代码很简单，注意取模就行了

完整代码
```cpp
#include<iostream>
#define MOD 1000000007
using namespace std;
long long mul(long long x,long long p)
{
    long long ans=1;
    while (p)
    {
        if (p&1) ans=ans*x%MOD;
        x=x*x%MOD;
        p=p>>1;
    }
    return ans;
}
int main()
{
    long long n;
    cin>>n;
    if (n)
    {
    	long long w=mul(2,n-1);
    	cout<<(w+2*w*w%MOD)%MOD<<endl;
	}
    else cout<<1<<endl;
    return 0;
}
```

---

## 作者：JiaY19 (赞：0)

一道大海颜色的蓝题。

简单的就是：快速幂 + 推式子

## 推式子：
令$~up~$为今年向上的三角形个数，$down~$为向下，$a~$为去年向上
，$b~$为去年向下，$n~$为今年。

由于每个去年向上的会变成3个新的向上的，向下的只有一个向上的（这里各位可以自己画一下），所以今年向上的也能表示出来。

$$up ~=~ (3a+b) ~\bmod~ p$$

同理，向下的也能表示出来。

$$down ~=~ (3b+a) ~\bmod~ p$$

考虑到直接枚举复杂度会炸，所以不妨求出它们的和和差。

$$up-down ~=~ (2a-2b) ~\bmod~ p$$

$$up+down~=~(4a+4b) ~\bmod~ p$$

其中，易知：

$$a-b ~=~2 ^ i$$

这里配一张图来理解这个式子。

![](https://cdn.luogu.com.cn/upload/image_hosting/v7n1xeko.png)

每张图最右边的一行就是它们的差。

又可知，三角形的数量:

$$a+b ~=~ 4 ^ i$$

所以：

$$up ~=~ (2^n+4^n)/2~=~2^{(n - 1)}+2^{(2\times n-1)}$$

## 快速幂

这个就可以直接填一个模板了

```c
int power(int a , int b , int p)
{
    int ans = 1 % p;
    for(;b;b >>= 1)
    {
        if(b & 1) ans = (long long)ans * a % p;
        a = (long long)a * a % p;
    }
    return ans;
} 
```
附上AC代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1000000007;
int n , up , down;
int power(int a , int b , int p)
{
    int ans = 1 % p;
    for(;b;b >>= 1)
    {
        if(b & 1) ans = (long long)ans * a % p;
        a = (long long)a * a % p;
    }
    return ans;
} 
signed main()
{   
    cin >> n;
    if(!n) puts("1");
    else cout << (power(2 , n - 1 , mod) + power(2 , 2 * n - 1 , mod)) % mod;
    return 0;
}
```


---

## 作者：MuYC (赞：0)

### 这一道题目的考点为:快速幂以及乘法逆元

我通过暴力O(n)找规律发现其实第$n$年的答案就是$4^n + 2^n / 2$,这个式子好像跟现有题解不大一样，因为有取模运算，所以除法是肯定不行的，因此我们要求乘法逆元。这道题有恶意评分的嫌疑，顶多算是黄题，希望管理大大仔细审核一下此题难度

乘法逆元的求法:
ＥＸｇｃｄ或者是利用费马小定理加快速幂完成

想看第一种的可以戳我的博客:[Exgcd以及乘法逆元](https://www.cnblogs.com/MYCui/p/13553855.html)
着重介绍第二种:

首先根据费马小定理我们知道$a^{p-1}$ $\equiv$ $1$ $mod$ $p$

(ｐ和ａ互质)

对于$a/b$在$mod$ $p$的意义下$a$ = $a$ * $b^{p-1}$ , 那么$a/b$就会等于　$a * b^{p-2}$($mod$ $p$意义下)

所以，这道题就解决了呀!

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int Mod = 1000000007;
int n;
int quick_power(int x,int y)
{
	int ans = 1,op = x;
	if(y == 2)return x*x % Mod;
	if(y == 0)return 1;
	while(y)
	{
		if(y % 2 == 1)ans *= op , ans %= Mod;
		op *= op , op %= Mod;
		y = y >> 1;
	}
	return ans % Mod;//快速幂
}
signed main()
{
	cin >> n;
	cout <<( quick_power(4,n)% Mod+ quick_power(2,n) % Mod ) * quick_power(2,Mod-2) % Mod;
	return 0;//上文提到的式子&&求逆元
}
```


---

## 作者：Arghariza (赞：0)

根据样例，不难计算（或找规律）出：

$$up_i=\begin{cases}1\qquad \qquad \qquad \qquad \;\;\;\;\;\ i=0\\up_{i-1} · 3 + down_{i - 1}\qquad i ≠0\end{cases}$$

$$down_i=\begin{cases}0\qquad \qquad \qquad \qquad \;\;\;\;\;\ i=0\\down_{i-1} · 3 + up_{i - 1}\qquad i ≠0\end{cases}$$


但是不能使用数组，否则空间会爆掉（（

**不过，我们可以用上述公式推出另一种解法**

n|ans|
--|:--:
1|3
2|10
3|36
4|136

找规律，看出什么了吗？

如果没有的话没关系，我们推一下上面的公式：

两式做差，得：

$$up_i-down_i=(up_{i-1} · 3 + down_{i - 1})-(down_{i-1} · 3 + up_{i - 1})=2(up_{i-1}-down_{i-1}-1)=2^i$$

又$∵sum_i=4^i$

故$\begin{cases}up_i+down_i=4^i\\up_i-down_i=2^i\end{cases}$

两者求和提取公因式可得$up_i=2^{n-1}(2^n+1)$

得到答案

```
#include <bits/stdc++.h>//万能头
#define mod 1000000007//模数
#define ll long long//宏定义ll
using namespace std;//命名空间

ll n;

ll ksm(ll x, ll p) {//快速幂（优化）
	ll ans = 1;
	while (p != 0) {
		if (p & 1) ans = ans * (x % mod) % mod;
        x = x * (x % mod) % mod;
        p /= 2;
	}
	return ans % mod;//记得取膜啊啊啊
}

int main() {
	scanf("%lld", &n);//输入
	printf("%lld", n ? (ksm(2, n - 1) % mod) * ((ksm(2, n) + 1) % mod) % mod : 1);//输出，注意特判
	return 0;
}
```

---

## 作者：lhjy666 (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;
long long pow_mod (long long b)
{
    unsigned long long r=1,a=2;
    while(b>0)
    {
        if(b%2==1)
        {
            r=1LL*r*a%1000000007;
        }
        b=b/2;
        a=1LL*a*a%1000000007;
    }
    return r%1000000007;
}
int main()
{
    unsigned long long n,z=0;
    scanf("%lld",&n);
    if(n==0)
    {
        printf("1");
        return 0;
    }
    if(n==1)
    {
        printf("3");
        return 0;
    }
    if(n==2)
    {
        printf("10");
        return 0;
    }
    if(n!=1&&n!=2)
    {
        z=z+pow_mod(n*2-1);
        z=z+pow_mod(n-1);
    }
    printf("%lld",z%1000000007);
}
```

---

