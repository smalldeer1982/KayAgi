# Nastya Studies Informatics

## 题目描述

$Nastya$  了解到  $GCD(a,\ b)$  用于表示  $a$  和  $b$  的最大公约数， $LCM(a,\ b)$  用于表示  $a$  和  $b$  的最小公倍数。

给出整数  $x$  和  $y$ ，请你帮她求出当  $l \leqslant a,\ b \leqslant r$  时，有多少对  $(a,\ b)$  能同时满足  $GCD(a,\ b) = x$  且  $LCM(a,\ b) = y$ 。注意，当  $a \neq b$  时， $(a,\ b)$  和  $(b,\ a)$  是不一样的。

## 说明/提示

- 第  $1$  组样例的解释：

满足要求的  $(a,\ b)$  有  $(1,\ 2)$  和  $(2,\ 1)$ 。

- 第  $2$  组样例的解释：

满足要求的  $(a,\ b)$  有  $(1,\ 12)$ ， $(12,\ 1)$ ， $(3,\ 4)$ ， $(4,\ 3)$ 。

- 第  $3$  组样例的解释：

没有满足要求的  $(a,\ b)$ 。虽然  $(3,\ 30)$  满足  $GCD(3,\ 30) = x$  和  $LCM(3,\ 30) = y$ ，但它们都不在指定范围内。

感谢@Sooke 提供翻译

## 样例 #1

### 输入

```
1 2 1 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 12 1 12
```

### 输出

```
4
```

## 样例 #3

### 输入

```
50 100 3 30
```

### 输出

```
0
```

# 题解

## 作者：封禁用户 (赞：3)

## 题解：CF992B Nastya Studies Informatics

### 解题思路

首先看数据范围，$10^9$，明显要用低于 $O(n)$ 的算法来做。因为 $\gcd(p , q) \times \operatorname{lcm}(p , q) = p \times q$，所以，我们可以枚举所有 $p \times q$ 的因数，逐一检查，复杂度 $O(\sqrt{x \times y})$。此时进行优化，因为 $p , q \le \operatorname{lcm}(p , q)$，所以只要枚举到 $\sqrt{y}$ 就能找出所有可能的解，减少了不必要的时间浪费，最后 $O(\sqrt{y})$ AC 此题。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
long long l , r , x , y , ans;
bool range(long long p , int q)
{
	return p >= l && p <= r && q >= l && q <= r;
}
void check(long long p)
{
	if(__gcd(p , x * y / p) == x && range(p , x * y / p))
	{
		ans++;
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> l >> r >> x >> y;
	if(y % x || r < x || l > y)
	{
		cout << '0';
		return 0;
	}
	if(x == y)
	{
		cout << '1';
		return 0;
	}
	for(long long i = 1 ; i * i <= y ; i++)
	{
		if(y % i)
		{
			continue;
		}
		check(i);
		if(i * i != y)
		{
			check(y / i);
		}
	}
	cout << ans;
	return 0;
}
```

[AC 记录](https://codeforces.com/problemset/submission/992/276737031)。RMJ 爆炸时期，直接引用 CF 的记录。

---

## 作者：MoyunAllgorithm (赞：3)

## 题目大意
对于数 $a$ 和 $b$，已知他们的最小公倍数 $x$ 和最大公约数 $y$ 的值以及 $a$ 和 $b$ 的取值范围，求有序数对 $(a,b)$ 的个数。
## 分析：
根据最小公倍数和最大公约数的性质，显然有 $ab=xy$。
但是，如果我们立刻进行暴力枚举 $a$，可能会超时。

这时，我们不妨设 $ a=nx $，$b=mx$，则可得 $y=nmx$。

可得 $ \dfrac{y}{x} = nm$。


这时，对 $n$ 进行枚举即可。
需要注意的是：在枚举的时候，对于每一个 $n$，如果 $\gcd(n,m)>1$，那么 $\gcd(a,b)>x$，不符合题意。

不要抄代码哦，挖坑了！
## CODE
```c
#include <bits/stdc++.h>
using namespace std;
int L,R;
int x,y;
int ans=0;
int gcd(int x,int y)
{
	if(y==0) return x;
	return gcd(y,x%y)；
}
int main()
 
{
	scanf("%d %d %d %d",&L,&R,&x,&y);
	//a=nx b=mx ab=xy y=nmx y/x=nm
	if(y%x!=0) 
	{
		puts("0");
		return 0;
	}
	int f=y/x;//在这里，f=nm
	for(int i=1;i*i<=f;i++)//n
	{
		if(f%i!=0) continue;
		int j=f/i;//m
		if(gcd(i,j)==1&&i*x>=L&&j*x>=L&&i*x<=R&&j*x<=R) 
        //因为x是n和m的GCD，所以GCD(n,m)必须为1；
        //后面四个判定是因为L<=a,b<=R,即L<=ix,jx<=R.
		{
			ans+=2;
			if(i==j) ans--;
			//cout<<i<<' '<<j<<endl;
		}
	}
	printf("%d\n',ans);
	return 0;
}
```


---

## 作者：AK_400 (赞：1)

记 $a=nx,b=mx(\gcd(n,m)=1)$，则
$$
  nmx=y\\
  \therefore nm=\frac{y}{x}
$$
于是我们枚举一下 $\frac{y}{x}$ 的因数并判断是否满足 $l\le nx,mx\le r$ 和 $\gcd(n,m)=1$，然后扔到 `set` 里面去下重即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r,x,y;
set<pair<int,int>>s;
int gcd(int x,int y){
    return (y?gcd(y,x%y):x);
}
void slv(){
    cin>>l>>r>>x>>y;
    if(y%x!=0){
        cout<<0;
        return ;
    }
    y/=x;
    for(int i=1;i*i<=y;i++){
        if(y%i==0&&y/i*x>=l&&y/i*x<=r&&gcd(i,y/i)==1&&i*x>=l&&i*x<=r){
            s.insert({i,y/i});
            s.insert({y/i,i});
        }
    }
    cout<<s.size();
    return;
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：heyZZZ (赞：1)

首先，我们知道 $\operatorname{lcm}(x,y) \times \gcd(x,y)=a \times b$。

之后，就可以构造了：

因为 $a$ 一定要整除 $\operatorname{lcm}(a,b)$。

再枚举 $\operatorname{lcm}(a,b)$ 的因数。

每个因数就判断一下，加入答案。

判断的代码：

```cpp
bool check(int a){
	int b=x*y/a;
    return !(a<l||a>r||b<l||b>r||__gcd(a,b)!=x);
}
```

代码楼上楼下都已经写的很明白了，我就不在赘述了。

---

## 作者：zhangqiuyanAFOon2024 (赞：1)

$\operatorname{lcm}(a,b)\times\gcd(a,b)=a \times b$

知道这个性质，我们就可以改造了。

因为 $a$ 一定要整除 $\operatorname{lcm}(a,b)$。

所以我们只需要枚举 $\operatorname{lcm}(a,b)$ 的因子就行了。

枚举之后判断一下，如果是的，则进入答案。

下面是代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r,x,y,ans=0;// ans 是答案
void check(int a){//判断是否可行
	int b=x*y/a;
	if(a<l||a>r) return;
	if(b<l||b>r) return;//越界判断
	if(__gcd(a,b)!=x) return;//最大公约数判断
	ans++;
}
signed main(){
	cin>>l>>r>>x>>y;
	for(int i=1;i*i<=y;i++){
		if(y%i==0){//最大公约数的因子
			int p=y/i;
			check(i);
			if(p!=i) check(p);//判断
		}
	}
	cout<<ans;//输出
	return 0;
}
```
是不是很水？

---

## 作者：_byta (赞：1)

发一篇清晰易懂的题解。

因为 $y = lcm(a, b)$，所以 $a,b$ 都是 $y$ 的因数，所以我们可以 $sqrt(y)$ 枚举 $y$ 的因数，判断两个因数是否越界，以及 $gcd(a, b)$ 是否等于 $x$ 即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 100002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[N], c[N], L, R;
inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9')
	{
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : x;
}
void pink(int x)
{
	int z = n * m / x;
	if(x >= L && x <= R && z>= L && z <= R && gcd(x, z) == n) ans++;
}
signed main()
{
	L = read(); R = read(); n = read(); m = read();
	for (int i = 1; i * i <= m; i++)
	{
		if(m % i == 0)
		{
			int y = m / i;
			pink(i);
			if(y != i) pink(y);
		}
	}
	cout << ans << endl;
	return 0;
}

```


---

## 作者：追风少年σχ (赞：1)

## 前排第一篇

##### 一.问题
   给定正整数L,R,x,y,求正整数对(a,b)的个数使得 $a,b\in [L,R]$且gcd(a,b)=x,lcm(a,b)=y.
  
##### 二.算法
  1.首先显然有公式(初中就会的公式)：
  $$ ab=xy $$
  所以我们的算法一就是暴力枚举a,由公式得出b,检验(a,b)是否合法，复杂度O(R-L),超时
  
  2.由gcd(a,b)=x可设
   $$a=xi,b=xj,(i,j\in N_+,gcd(i,j)=gcd(\frac{a}{x},\frac{b}{x})=1 ) $$
   此时
   $$ ij=\frac{y}{x}$$
   且有
   $$ i,j\in [\lceil \frac{L}{x} \rceil,\lfloor \frac{R}{x} \rfloor ] $$
   由以上性质可枚举i,算出j并检验是否合法，虽然有了不少优化，但在x=1时复杂度仍然是O(R-L),还是超时
   
  3.正解：
  
  继续对算法2进行优化，从 $ij=\frac{y}{x}$ 切入，令$k=\frac{y}{x}$,则$ij=k$,因为i和j和k都是正整数，那么就可以枚举i为k的约数，算出此时的j。这样只要枚举 $i\in[\lceil \frac{L}{x} \rceil,min\{\sqrt{k},\lfloor \frac{R}{x} \rfloor \}]$，算出j并检验答案(i!=j时答案加两次((i,j)和(j,i)))即可。复杂度$O( \sqrt{\frac{y}{x}} )$,AC！

##### 三.代码

```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
int x,y,k,ans,L,R;//变量名完全按题解中来
int gcd(int p,int q){//求gcd
    if(q==0)return p;
    else return gcd(q,p%q);
}
int main(){
    cin>>L>>R>>x>>y;
    k=y/x;
    for(int i=ceil(L*1.0/x);i*x<=R&&i*i<=k;i++){//枚举i,都见上面题解
        if(k%i!=0)continue;
        int j=k/i;
        if(gcd(i,j)==1&&j*x>=L&&j*x<=R){//检验答案是否合法
           ans++;
           if(i!=j)ans++;
        }
    }
    if(y%x!=0)ans=0;//特判很重要啊！显然的道理。
    cout<<ans;
    return 0;
}
```
~~蒟蒻题解求过~~

---

## 作者：Piwry (赞：0)

给出一个能跑 10e18 的解法

## 解析

考虑构造出满足要求的 $a, b$

首先 $x, y$ 应当满足 $y$ 为 $x$ 倍数

可以发现，$a, b$ 都至少为 $x$（$\gcd$）。接着我们需要把 $\frac y x$（$\frac {\text{lcm}} {\gcd}$）的质因子 “分” 给 $a, b$，并且不能使 $\gcd$ 增大

其实差不多就是这样：

![gcd_lcm](https://cdn.luogu.com.cn/upload/image_hosting/0z82eroc.png)

（即将 $\frac y x$ 的质因子全部分给 $a, b$，且要求 $a, b$ 分到的质因子不能有交集；意会下X，也可参考代码）

设 $\frac y x$ 的不同质因子个数为 $\texttt{cnt}$，那么该算法复杂度即为 $O(2^{\texttt{cnt}})$。可以发现 $\texttt{cnt}$ 的增长其实比阶乘的反函数的还慢...；事实上 $10^{18}$ 内 $\texttt{cnt}$ 仅在 $15$ 左右

于是该算法的瓶颈在于分解 $\frac y x$ 的质因数（naive 的写法是直接筛出 $\sqrt n$ 内的质数）；这部分其实可以用 Pollard Rho 解决

## CODE

Pollard Rho 有点长...这里是直接筛质数分解 $\frac y x$ 的

```cpp
#include <cstdio>
#include <cmath>

const int MAXV =4e4;

bool np[MAXV];
int prim[MAXV], totp;

void pre_math(){
	for(int i =2; i < MAXV; ++i){
		if(!np[i])
			prim[totp++] =i;
		for(int j =0; 1ll*i*prim[j] < MAXV; ++j){
			np[i*prim[j]] =1;
			if(i%prim[j] == 0)
				break;
		}
	}
}

int val[10], tot;

int dfs(const int &x, const int &L, const int &R, const int &m, int nw, const int &i){
	int Ans =0;
	if(i == tot){
		int nw2 =m/nw;
		if(nw*x >= L && nw*x <= R && nw2*x >= L && nw2*x <= R)
			++Ans;
	}
	else{
		Ans +=dfs(x, L, R, m, nw, i+1);
		Ans +=dfs(x, L, R, m, nw*val[i], i+1);
	}
	return Ans;
}

int main(){
	pre_math();
	int L, R, x, y;
	scanf("%d%d%d%d", &L, &R, &x, &y);
	if(y%x != 0)
		puts("0");
	else{
		int m =y/x;
		for(int j =0; j < totp && m > 1; ++j)
			if(m%prim[j] == 0){
				val[tot] =1;
				while(m%prim[j] == 0)
					m /=prim[j], val[tot] *=prim[j];
				++tot;
			}
		if(m > 1)
			val[tot++] =m;
		printf("%d", dfs(x, L, R, y/x, 1, 0));
	}
}
```

---

