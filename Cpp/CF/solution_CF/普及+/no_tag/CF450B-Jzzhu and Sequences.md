# Jzzhu and Sequences

## 题目描述

Jzzhu has invented a kind of sequences, they meet the following property:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF450B/24eb04dd3b6c3e1abcf8e078661c78665e8d1d86.png)You are given $ x $ and $ y $ , please calculate $ f_{n} $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample, $ f_{2}=f_{1}+f_{3} $ , $ 3=2+f_{3} $ , $ f_{3}=1 $ .

In the second sample, $ f_{2}=-1 $ ; $ -1 $ modulo $ (10^{9}+7) $ equals $ (10^{9}+6) $ .

## 样例 #1

### 输入

```
2 3
3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
0 -1
2
```

### 输出

```
1000000006
```

# 题解

## 作者：云浅知处 (赞：7)

这题其实很简单啦qwq。

首先题目说 $f(i)=f(i-1)+f(i+1)$，那不就是 $f(i+1)=f(i)-f(i-1)$ 嘛=\_=

所以我们得到了 $f$ 的递推式：$f(n)=f(n-1)-f(n-2)$。

而 $f(1)=x,f(2)=y$，所以有：

$$
\begin{aligned}
f(3)&=&f(2)-f(1)&=y-x\\
f(4)&=&f(3)-f(2)&=(y-x)-y&=&-x&\color{gray}(=&\color{gray}-f(1))\\
f(5)&=&f(4)-f(3)&=-x-(y-x)&=&-y&\color{gray}(=&\color{gray}-f(2))\\
f(6)&=&f(5)-f(4)&=-y-(-x)&=&\ x-y&\color{gray}(=&\color{gray}-f(3))\\
f(7)&=&f(6)-f(5)&=x-y-(-y)&=&\ x&=&f(1)\\
f(8)&=&f(7)-f(6)&=x-(x-y)&=&\ y&=&f(2)
\end{aligned}
$$

我们惊讶地发现，$f(7)=f(1),f(8)=f(2)$！

所以，如果我们继续递推下去，一定会得到循环节为 $6$ 的一个循环数列。

那么只需要判断 $n\bmod6$ 即可。

当然，我们直接以 $3$ 为循环节，多判断一个正负号，也是可以的~

别忘了取模！

```cpp
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>

using namespace std;

int a,b,n;
int f(int x){
	if(x%6==1)return a;
	if(x%6==2)return b;
	if(x%6==3)return b-a;
	if(x%6==4)return -a;
	if(x%6==5)return -b;
	if(x%6==0)return a-b;
}

int main(void){
	
	scanf("%d%d%d",&a,&b,&n);
	printf("%d\n",(f(n)%1000000007+1000000007)%1000000007);
	
	return 0;
}

```

---

## 作者：FQR_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF450B)

观察序列的性质。

由 $f(i)=f(i-1)+f(i+1)$，可得 $f(i)=f(i-1)-f(i-2)$。


## 解法 1：矩阵

首先，我们要求出 $base$ 矩阵。

假设 $base$ 为 $
\begin{bmatrix} 
a&b
\\
c&d
\end{bmatrix}
$，则：

$$
base\times 

\begin{bmatrix} 
f(i-2)
\\
f(i-1)
\end{bmatrix}

=

\begin{bmatrix} 
a&b
\\
c&d
\end{bmatrix}
\times
\begin{bmatrix} 
f(i-2)
\\
f(i-1)
\end{bmatrix}

=

\begin{bmatrix} 
a \cdot f(i-2)+b\cdot f(i-1)
\\
c \cdot f(i-2)+d\cdot f(i-1)
\end{bmatrix}
$$

要使这个结果等于 $
\begin{bmatrix} 
f(i-1)
\\
f(i)
\end{bmatrix}
$，即 $
\begin{bmatrix} 
f(i-1)
\\
f(i-1)-f(i-2)
\end{bmatrix}
$，显然 $a=0,b=1,c=-1,d=1$。

所以 $base=\begin{bmatrix} 
0&1
\\
-1&1
\end{bmatrix}$。

这样，我们就可以得到答案为 $({\begin{bmatrix} 0&1\\-1&1\end{bmatrix}}^{n-1}\times \begin{bmatrix} x\\y\end{bmatrix})_{1,1}$。

使用矩阵快速幂，时间复杂度 $O(\log n)$。[代码](https://codeforces.com/contest/450/submission/181641378)。

## 解法 2：找规律

$f(1)=x$

$f(2)=y$

$f(3)=f(2)-f(1)=y-x$

$f(4)=f(3)-f(2)=y-x-y=-x$

$f(5)=f(4)-f(3)=-x-y+x=-y$

$f(6)=f(5)-f(4)=x-y$

$f(7)=f(6)-f(5)=x-y+y=x=f(1)$

$f(8)=f(7)-f(6)=y=f(2)$

$f(9)=f(3)$

$f(10)=f(4)$

$\dots$

从上面的式子可以得到，答案以 $6$ 为周期无限循环。

算出 $n \bmod 6$ 的值，输出对应答案即可。

时间复杂度 $O(1)$。[代码](https://codeforces.com/contest/450/submission/181641174)。

---

## 作者：Grisses (赞：2)

就是一个转移式，用矩阵快速幂优化一下。

首先，定义矩阵乘法：

对于一个 $n\times k$ 的矩阵 $A$ 和一个 $k\times m$ 的矩阵 $B$ 还有一个矩阵 $C=A\times B$。那么 $C$ 是一个 $n\times m$ 的矩阵，且 $C_{ij}=\sum\limits_{p=1}^kA_{i,p}\times B_{p,j}(i=\overline{1,2,\cdots,n},j=\overline{1,2,\cdots,m})$。

然后，因为矩阵乘法满足结合律，所以我们有了矩阵快速幂。矩阵快速幂的话就是把快速幂的板子套在矩阵上而已。

已知 $f_1=x,f_2=y,f_i=f_{i-1}+f_{i-2}(i>2)$，求 $f_n$。

- $n=1$，$f_n=x$。
- $n=2$，$f_n=y$。
- $n>2$。

我们可以尝试推一下转移矩阵 $base$：

$$\begin{pmatrix}f_{i-1}+f_{i-2}\\f_{i-1}\end{pmatrix}=\begin{pmatrix}1&1\\1&0\end{pmatrix}\begin{pmatrix}f_{i-1}\\f_{i-2}\end{pmatrix}$$

然后快速幂就好了。

代码：
```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  const int mod=1e9+7;
  int x,y,z;
  struct M{
      int a[2][2];
      M operator*(M t){//乘法
          M res;
          for(int i=0;i<2;i++)for(int j=0;j<2;j++)res.a[i][j]=0;
          for(int i=0;i<2;i++){
              for(int j=0;j<2;j++){
                  for(int k=0;k<2;k++){
                      res.a[i][j]=((res.a[i][j]+a[i][k]*t.a[k][j]%mod+mod)%mod+mod)%mod;
                  }
              }
          }
          return res;
      }
      M operator^(int x){//快速幂
          M res,_=*this;
          for(int i=0;i<2;i++)for(int j=0;j<2;j++)res.a[i][j]=(i==j);
          while(x){
              if(x&1)res=res*_;
              _=_*_;
              x>>=1; 
          }
          return res;
      }
  }ans,base;
  signed main()
  {
      scanf("%lld%lld%lld",&x,&y,&z);
      x=(x%mod+mod)%mod;
      y=(y%mod+mod)%mod;
      if(z==1)printf("%lld",x);
      else if(z==2)printf("%lld",y);
      else{
          ans.a[0][0]=y;ans.a[0][1]=x;
          base.a[0][0]=1;base.a[0][1]=1;
          base.a[1][0]=-1;base.a[1][1]=0;//转移矩阵
          ans=ans*(base^(z-2));
          printf("%lld",(ans.a[0][0]%mod+mod)%mod);
      }
      return 0;
  }
```

---

## 作者：cqbztz2 (赞：1)

# [题目传送门](https://www.luogu.com.cn/problem/CF450B)

# 思路：

首先观察题目规律， $ a[1]=x; a[2]=y;  a[i]=a[i-1]+a[i+1] $，于是便可以推出本题真正的基本规律： $ a[i]=a[i-1]-a[i-2] $，本以为接下来就是类似斐波拉契数列一样的递归，但数据范围提醒了我，这题一定还有其他规律，于是开始推道接下来的序列：

$ a[1]=x; $

$ a[2]=y; $

$ a[3]=a[2]-a[1]=y-x; $

$ a[4]=a[3]-a[2]=(y-x)-y=-x; $

$ a[5]=a[4]-a[3]=-x-(y-x)=-y; $

$ a[6]=a[5]-a[4]=-y-(-x)=x-y; $

$ a[7]=a[6]-a[5]=(x-y)-(-y)=x; $

$ a[8]=a[7]-a[6]=x-(x-y)=y; $

$ a[9]=a[8]-a[7]=y-x; $

$ a[10]=a[9]-a[8]=(y-x)-y=-x; $

 $ ……………………………… $
 
 于是可以发现，每过 6 轮都会进行一次轮回，于是最后求答案是就只需要 $ n\bmod6 $ 就行了。
 
 # 代码：
 
 ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int x,y,n,mod=1e9+7;
  int main(){
      cin>>x>>y>>n;
      if(n%6==0){
          cout<<(((x-y)%mod)+mod)%mod;
      }
      if(n%6==1){
          cout<<(((x)%mod)+mod)%mod;
      }
      if(n%6==2){
          cout<<(((y)%mod)+mod)%mod;
      }
      if(n%6==3){
          cout<<(((y-x)%mod)+mod)%mod;
      }
      if(n%6==4){
          cout<<(((-x)%mod)+mod)%mod;
      }
      if(n%6==5){
          cout<<(((-y)%mod)+mod)%mod;
      }
      return 0;
  } 
```


---

## 作者：a13518354766 (赞：1)

    作为首A的人(?)我来发布下这道大水题的题解了~
    首先题目给出了f[i]=f[i-1]+f[i+1]，我们移下项:
    f[i+1]=f[i]-f[i-1]，所以我们可以知道：第i项等于它前两项之差！即:
    f[i]=f[i-1]-f[i-2],同时,f[i-1]=f[i-2]-f[i-3],代入得：
    f[i]=-f[i-3]=f[i-6],所以我们只需将前6项算出，第n%6项就是答案了，不过值得注意的是，如果n%6==0，我们需要把他变成6，当然，也可以把第6项的值赋给第0项

    至于取模，就不多说了。。。代码如下:

    #include<iostream>
    using namespace std;
    const long long mod=1e9+7;
    long long f[7];//开long long 防爆
    int main(){
        long long n,lo;
        cin>>f[1]>>f[2]>>n;
        f[3]=f[2]-f[1];
        f[4]=-f[1];
        f[5]=-f[2];
        f[6]=-f[3];
        n%=6;
        if(n==0){//如果等于0，把它变成6或者令f[0]=f[6]
            n=6;
        }
        f[n]=(f[n]%mod+mod)%mod;//取模
        cout<<f[n];
        return 0;
    }
    /**
    *　　┏┓　　　┏┓+ +
    *　┏┛┻━━━┛┻┓ + +
    *　┃　　　　　　　┃
    *　┃　　　━　　　┃ ++ + + +
    *  ████━████+
    *  ◥██◤　◥██◤ +
    *　┃　　　┻　　　┃
    *　┃　　　　　　　┃ + +
    *　┗━┓　　　┏━┛
    *　　　┃　　　┃ + + + +Code is far away from 　
    *　　　┃　　　┃ + bug with the animal protecting
    *　　　┃　 　 ┗━━━┓ 神兽保佑,代码无bug　
    *　　　┃ 　　　　　　 ┣┓
    *　　  ┃ 　　　　　 　┏┛
    *　    ┗┓┓┏━┳┓┏┛ + + + +
    *　　　　┃┫┫　┃┫┫
    *　　　　┗┻┛　┗┻┛+ + + +
    */
    
    当然，童鞋们也可以试试模3，不过记得讨论正负哦！


---

## 作者：Milthm (赞：0)

## CF450B 题解

### 题目解法

首先，$f(1)=x,f(2)=y$，式子 $f(n)=f(n-1)+f(n+1)$ 也就等于 $f(n)=f(n-1)-f(n-2)$ 所以我们向后推：

$f(3)=f(2)-f(1)=y-x$

$f(4)=f(3)-f(2)=-x$

$f(5)=f(4)-f(3)=-y$

$f(6)=f(5)-f(4)=x-y$

$f(7)=f(6)-f(5)=x$

发现规律了就好说了，每 $6$ 个一组的规律，一直循环。

那么代码就很简单了！

### AC代码
```cpp
#include<iostream>
#define int long long
using namespace std;
int x,y,n,mod=1e9+7;
signed main(){
	cin>>x>>y>>n;
   //注意取模的时候一定要加上两个mod再取！
	if(n%6==1)cout<<(x+2*mod)%mod;
	if(n%6==2)cout<<(y+2*mod)%mod;
	if(n%6==3)cout<<(y-x+2*mod)%mod;
	if(n%6==4)cout<<(-x+2*mod)%mod;
	if(n%6==5)cout<<(-y+2*mod)%mod;
	if(n%6==0)cout<<(x-y+2*mod)%mod;
	return 0;
} 
```




---

## 作者：_Give_up_ (赞：0)

## 题目大意

给出 $x,y,n$。

已知：

$f_1 = x$

$f_2 = y$

$f_i = f_{i-1} + f_{i+1}$（$i\ge2$）

求 $f_n$ 是多少。

## 题目思路

根据 $f_i = f_{i-1} + f_{i+1}$（$i\ge2$）

得出 $f_i = f_{i-1}-f_{i-2}$（$i\ge3$）

观察样例一，根据公式一直往下推：

$f_1 = 2$

$f_2 = 3$

$f_3 = 1$

$f_4 = -2 = -f_1$

$f_5 = -3 = -f_2$

$f_6 = -1 = -f_3$

$f_7 = 2 = f_1$

$f_8 = 3 = f_2$

……

我们会发现这里有循环节，长度为 $6$。

且，$f_4 = -f_1,f_5 = -f_2,f_6 = -f_3$。

这样我们就能写出代码了。

## 代码

```cpp
#include<bits/stdc++.h>
#define mod 1000000007

using namespace std;

int read()
{
    int x = 0,f = 1;
    char c = getchar();
    while(c<'0' || c>'9')
	{
        if(c=='-') f = -1;
        c = getchar();
    }
    while(c>='0' && c<='9')
	{
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
    return x*f;
}

int a[10];

int main()
{
	a[1]=read(),a[2]=read(),a[3]=a[2]-a[1];
	a[4] = -a[1],a[5] = -a[2],a[0] = -a[3];
	int n=read();
	cout << (a[n%6]%mod+mod)%mod << endl;
	return 0; 
}
```


---

## 作者：信息学carryHarry (赞：0)


我们通过推导式子，发现答案是以 $6$ 个数为一周期的

- 若 $n \bmod 6=1$，答案就是 $x$。
- 若 $n \bmod 6=2$，答案就是 $y$；
- 若 $n \bmod 6=3$，答案就是 $y-x$；
- 若 $n \bmod 6=4$，答案就是 $-x$；
- 若 $n \bmod 6=5$，答案就是 $-y$；
- 若 $n \bmod 6=0$，答案就是 $x-y$；

最后放代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long x,y,n;
long long s[6]={x-y,x,y,y-x,-x,-y};
int main()
{
	cin>>x>>y>>n;
	cout<<(s[n%6]%mod+mod)%mod;
	return 0;
}

```


---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的数列 $\{a_1,a_2,\dots,a_n\}$，满足如下的递推公式：

- $i=1$ 时，$a_1=x$。
- $i=2$ 时，$a_2=y$。
- $i\geqslant 3$ 时，$a_i=a_{i-1}+a_{i+1}$。

求 $a_n\bmod 10^9+7$ 的值。

**数据范围：$1\leqslant n\leqslant 2\times 10^9$，$|x|,|y|\leqslant 10^9$。**
## Solution
对于 $i\geqslant 3$，我么不妨将这个式子移项，得到 $a_{i+1}=a_i-a_{i-1}$。然后先写下如下式子：

$$\begin{aligned}a_3=a_2-a_1&=y-x\\a_4=a_3-a_2&=(y-x)-y=-x\\a_5=a_4-a_3&=-x-(y-x)=-y\\a_6=a_5-a_4&=-y-(-x)=x-y\\a_7=a_6-a_5&=x-y-(-y)=x\color{red}=a_1\\a_8=a_7-a_6&=x-(x-y)=y\color{Red}=a_2\end{aligned}$$

我们发现，当 $i=7$ 的时候，$a_7$ 的值又变回了 $a_1$。因此我们发现了一个长度为 $6$ 的循环节。那么 $a_i$ 也就不难表示出来了：

$$a_i=\begin{cases}x&i\bmod 6=1\\y&i\bmod 6=2\\y-x&i\bmod 6=3\\-x&i\bmod 6=4\\-y&i\bmod 6=5\\x-y&i\bmod 6=0\end{cases}$$

直接根据这个公式计算 $a_n$ 即可，即为 $a_{n\bmod 6}$，注意对负数取模时，先加上模数再去取模。
## Code
```cpp
const int mod = 1e9 + 7;
int f[7];

int main() {
    int x = Rint, y = Rint, n = Rint;
    f[1] = x, f[2] = y, f[3] = y - x, f[4] = -x, f[5] = -y, f[6] = x - y;
    return write((f[(n - 1) % 6 + 1] % mod + mod) % mod), 0;
}
```

---

## 作者：qwq___qaq (赞：0)

### 前置知识

[矩阵乘法](https://baike.baidu.com/item/%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95/5446029)

对于一个 $n\times p$ 的矩阵 $A$ 和一个 $p\times m$ 的矩阵 $B$，它们可以相乘，得到一个 $n\times m$ 的矩阵 $C$。

有：

$C_{a,b}\gets\sum\limits_{i=1}^pA_{a,i}\times B_{i,b}$

***

### 正文

这篇题解使用的是矩阵加速。

矩阵加速的做法是首先使用矩阵乘法表示递推关系，然后再使用矩阵快速幂求解。

由于 $n\le2\times10^9$，不能递推，所以考虑矩阵加速。

首先，移项得 $f_{i+1}=f_i+f_{i-1}$，即 $f_i=f_{i-1}+f_{i-2}$。

因为只跟前两项有关，我们可以设记一个 $2\times2$ 的矩阵 $A$：

那么易得：

$$\left[\begin{matrix} 
a_{1,1}&a_{1,2}\\
a_{2,1}&a_{2,2}\\
\end{matrix}\right]\times\left[\begin{matrix} 
f_{i-2}\\
f_{i-1}\\
\end{matrix}\right]=\left[\begin{matrix} 
a_{1,1}f_{i-2}+a_{1,2}f_{i-1}\\
a_{2,1}f_{i-2}+a_{2,2}f_{i-1}\\
\end{matrix}\right]=\left[\begin{matrix} 
f_{i-1}\\
f_i\\
\end{matrix}\right]$$

即

$$\left[\begin{matrix} 
a_{1,1}f_{i-2}+a_{1,2}f_{i-1}\\
a_{2,1}f_{i-2}+a_{2,2}f_{i-1}\\
\end{matrix}\right]=\left[\begin{matrix} 
f_{i-1}\\
f_i\\
\end{matrix}\right]
$$

$$\because f_i=f_{i-1}-f_{i-2}$$

$$\therefore
\left[\begin{matrix} 
a_{1,1}f_{i-2}+a_{1,2}f_{i-1}\\
a_{2,1}f_{i-2}+a_{2,2}f_{i-1}\\
\end{matrix}\right]=\left[\begin{matrix} 
f_{i-1}\\
-f_{i-2}+f_{i-1}\\
\end{matrix}\right]
$$

因为该式与 $i$ 无关，所以每一项系数相等。
$$\therefore A=\left[\begin{matrix} 
0&1\\
-1&1\\
\end{matrix}\right]$$

因为每乘一次就多递推一次，所以一共需要乘 $A^{n-2}$。

综上，答案为 $(A^{n-2}\times\left[\begin{matrix} 
x\\
y\\
\end{matrix}\right])_{2,1}$

时间复杂度 $O(2^3\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod=1e9+7;
struct M{
	int m[5][5];
	inline void init(){
		memset(m,0,sizeof(m));
	}
	inline M operator *(const M &o) const{
		M p;
		p.init();
		for(int k=1;k<=2;++k)
			for(int i=1;i<=2;++i)
				for(int j=1;j<=2;++j)
					p.m[i][j]=(p.m[i][j]+m[i][k]*o.m[k][j]%mod)%mod;
		return p;
	}
}a,b;
inline M qpow(M x,int y){
	if(y==1)
		return x;
	M k=qpow(x,y>>1);
	if(y&1)
		return k*k*x;
	else
		return k*k;
}
int x,y,n;
int main(){
	cin>>x>>y>>n;
	if(n==1){
		cout<<(x%mod+mod)%mod<<endl;
		return 0;
	}
	if(n==2){
		cout<<(y%mod+mod)%mod<<endl;
		return 0;
	}
	a.m[1][1]=0,a.m[1][2]=1;
	a.m[2][1]=-1,a.m[2][2]=1;
	b.m[1][1]=(x%mod+mod)%mod,b.m[2][1]=(y%mod+mod)%mod;
	cout<<((qpow(a,n-2)*b).m[2][1]%mod+mod)%mod<<endl;
	return 0;
} 
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
有一个数列 $f_i$,给出 $f_1,f_2$，对于 $i>2$，满足 $f_i=f_{i-1}+f_{i+1}$.  
求数列的第 $n$ 项.  
$n\le10^9$
## $\text{Solution}$
移项：
$f_{i+1}=f_{i}-f_{i-1}$.  
矩阵乘法即可.  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
//#define double long double
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1050;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;
struct matrix{
  ll a[3][3];
  int x,y;
  matrix(int xx,int yy):x(xx),y(yy){memset(a,0,sizeof(a));}
  matrix() {memset(a,0,sizeof(a));}
};
matrix mul(matrix u,matrix v){
  matrix res(u.x,v.y);
  for(int k=1;k<=u.y;k++){
    for(int i=1;i<=u.x;i++){
      for(int j=1;j<=v.y;j++) (res.a[i][j]+=u.a[i][k]*v.a[k][j])%=mod;
    }
  }
  return res;
}
matrix ksm(matrix o,int k){
  matrix res(2,2);res.a[1][1]=res.a[2][2]=1;
  while(k){
    if(k&1) res=mul(res,o);
    o=mul(o,o);
    k>>=1;
  }
  return res;
}
matrix tr,ans;
int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  ans.a[1][2]=(read()+mod)%mod;ans.a[1][1]=(read()+mod)%mod;
  ans.x=1;ans.y=2;
  n=read();
  if(n<=2){
    printf("%lld\n",ans.a[1][3-n]);return 0;
  }
  tr.x=tr.y=2;
  tr.a[1][1]=1;tr.a[1][2]=1;tr.a[2][1]=mod-1;tr.a[2][2]=0;
  ans=mul(ans,ksm(tr,n-2));
  printf("%lld\n",ans.a[1][1]);
  return 0;
}
/*
3 3
tsy
*/

```


---

