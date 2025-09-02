# [ABC147D] Xor Sum 4

## 题目描述

给出 $n$ 个整数 $a_i$，请求出 $\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}(a_i \operatorname{xor}a_j)$ 对 $10^9 + 7$ 取模的值。

## 说明/提示

$2 \le n \le 3 \times 10 ^ 5, 0 \le a_i \le 2^{60}$。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
6```

## 样例 #2

### 输入

```
10
3 1 4 1 5 9 2 6 5 3```

### 输出

```
237```

## 样例 #3

### 输入

```
10
3 14 159 2653 58979 323846 2643383 27950288 419716939 9375105820```

### 输出

```
103715602```

# 题解

## 作者：洛璟 (赞：8)

## Solution:

难度可能是绿题的难度，有一定思维难度。

我们根据异或的特点，即相同得0，不同得1来思考。

首先，异或是在二进制下的运算，因此我们可以先统计出各个位数上的1的个数。而根据异或的特点，我们不难发现，在每一位上只有1与0进行按位异或之后才会对答案产生贡献。

因此，我们只需要统计出各个位数上的1的个数，同时计算出0的个数，根据乘法原理来计算出这些1的对于答案的贡献是多少（每一个1与每一个0配对都会对答案产生贡献），值得注意的是，不同位数上的1对于十进制答案的贡献不同，因此我们需要将二进制转换为十进制，方式与手转方式一样。

剩下的细节详见代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, f[70], ans;
inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
signed main() {
    n = read();
    for (register int i = 1; i <= n; i++) {
        int a = read();
        int j = 1;
        while (a > 0) {
            f[j++] += a & 1;//按位与运算，得出此位上是否为1
            a = a >> 1;//右移，将判断过的位扔掉
        }
    }
    for (int i = 1, j = 1; i <= 60; i++, j = (j << 1) % 1000000007)//j即为不同位数的乘数，用于二进制转十进制，i用于枚举不同位数，最高为60次。
    {
        ans = (ans + f[i] % 1000000007 * (n - f[i]) % 1000000007 * j % 1000000007) % 1000000007;
        //f[i]为1的个数，（n-f[i]）为0的个数。
        //因为一个数位上非1即0，减去1的个数就是0的个数。
        //j用于进制转换
        //三个相乘即为这个数位上的1对答案的贡献
    }
    printf("%lld", ans);
    return 0;
}
```


---

## 作者：RainFestival (赞：6)

这道题我们对于每一位进行处理

答案是 $ans=\sum\limits_{0}^{60} 2^i\times cnt_i$

$cnt_i$ 是 $2^i$ 这一位的答案

对于 $cnt_i$，我们这么处理

我们处理一个删除一个

```cpp
int x=0,y=0,cnt=0;
for (int i=1;i<=n;i++) if (f[i]&(1ll<<k)) ++x;else ++y;
for (int i=1;i<=n;i++) if (f[i]&(1ll<<k)) cnt=(cnt+y)%mod,--x;else cnt=(cnt+x)%mod,--y;
```
$x,y$ 为剩余的该位 $1,0$ 的个数

代码：

```cpp
#include<cstdio>
#define mod 1000000007
int n;
long long f[300005],ans=0;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&f[i]);
	for (int k=0;k<=60;k++)
	{
		int x=0,y=0,cnt=0;
		for (int i=1;i<=n;i++) if (f[i]&(1ll<<k)) ++x;else ++y;
		for (int i=1;i<=n;i++) if (f[i]&(1ll<<k)) cnt=(cnt+y)%mod,--x;else cnt=(cnt+x)%mod,--y;
		ans=(ans+(1ll<<k)%mod*cnt%mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```

然后就AC了

QAQ

---

## 作者：Symbolize (赞：6)

# 思路
异或运算需要在二进制下运行，所以我们要先定义一个函数来转换二进制，用一个数组记下来。
```cpp
int zh(int x)
{
	int i=0;
	while(x>0) 
	{
        f[++i]+=x&1;
        x/=2;
    }
}
```
 
然后我们在循环中多加一个参数 $j$，用来记录对答案的贡献的系数。

最后只需要执行 $ans \gets ans+f_i \times (n-f_i) \times j$ 就得出答案了。

下面附上完整 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1e2+10;
const int mod=1e9+7;//提前定义，方便
using namespace std;
int n,ans,x,f[N];
int zh(int x)//转换函数
{
	int i=0;
	while(x>0) 
	{
        f[++i]+=x&1;
        x/=2;
    }
}
signed main() 
{
    cin>>n;
    for(int i=1;i<=n;i++) 
	{
        cin>>x;
        zh(x);//转二进制
    }
    for(int i=1,j=1;i<=60;i++,j=j*2%mod) ans=(ans+f[i]%mod*(n-f[i])%mod*j%mod)%mod;
    cout<<ans<<endl;//累加过程
    return 0;//收场
}
```

---

## 作者：极寒神冰 (赞：0)

假设已经求出$n$个数字二进制下各位$1$的数量$B_0,B_1...B_{60}$。

枚举$a_i$，因为$a_i$的二进制下每一位$1$不能对自己产生贡献,所以应先从$B_0,B_1...B_{60}$取出。

若$a_i$二进制下若当前位$j$为$1$，则$xor$另一个$0$后产生贡献为$2^j$,而剩下$n-i$个数中剩余的$0$的数量为$n-i-B_j$，总贡献为$2^j \times (n-i-B_j)$

若$a_i$二进制下若当前位$j$为$0$同理.

```
signed main()
{
	n=read();
	R(i,1,n) a[i]=read();
	R(i,1,n) R(j,0,61) if(a[i]&(1ll<<j)) BT[j]++;
	int res=0;
	R(i,1,n)
	{ 
		R(j,0,61) if(a[i]&(1ll<<j)) BT[j]--;
		R(j,0,61) if(a[i]&(1ll<<j)) res+=(1ll<<j)%mod*(n-i-BT[j])%mod,res%=mod; else res+=(1LL<<j)%mod*BT[j]%mod,res%=mod;
	}
	printf("%lld\n",res);
}

```






---

