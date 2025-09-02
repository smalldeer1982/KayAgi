# The World is a Theatre

## 题目描述

有n个男孩和m个女孩参加了一个戏剧俱乐部，为了上演一场
名叫“生活大爆炸”的戏剧，他们需要选择t人，保证其中至少4个男孩和1个女孩。问有多少种选择方式。

当然，只有选择不同的男生或女生的选择方式才算不同，换句话说，若方案a选了男生1,2,3,4，女生1,2，而方案b选了男生4,3,2,1，女生2,1，这两种情况是**等价**的。

注意，C++开longlong，Delphi和Java开int64。

## 样例 #1

### 输入

```
5 2 5
```

### 输出

```
10
```

## 样例 #2

### 输入

```
4 3 5
```

### 输出

```
3
```

# 题解

## 作者：Max_s_xaM (赞：5)

# CF131C The World is a Theatre 题解

## 思路

依题意，答案为：
$$\sum\limits_{i=\max(1,t-n)}^{\min(t-4,m)}\dbinom{m}{i}\cdot\dbinom{n}{t-i}$$

### 下界：

当 $n<t$ 时，因为男生最多是 $n$ 人，所以女生最少是 $t-n$ 人。

当 $n\ge t$ 时，女生最少是 $1$ 人。

所以下界为 $\max(1,t-n)$ .

### 上界：

因为男生最少是 $4$ 人，所以女生最多为 $t-4$ 人。又因为女生有 $m$ 人，所以上界为 $\min(t-4,m)$ .

**注意：计算组合数要边乘边除，否则会爆 long long .**

## Code

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
long long ans;
inline long long com(int n, int m)
{
	long long res = 1;
	for (register int i = m - n + 1; i <= m; ++i)
		res = res * i / (i - m + n);
	return res;
}
int main()
{
	int n, m, t;
	scanf("%d%d%d", &n, &m, &t);
	for (register int i = max(1, t - n); i <= min(t - 4, m); ++i) 
    	ans += com(i, m) * com(t - i, n);
	printf("%I64d\n", ans);
	return 0;
}

```


---

## 作者：sto__Liyhzh__orz (赞：4)

[传送门](https://www.luogu.com.cn/problem/CF131C)

如果你没学过排列组合，你可以[走了](https://www.luogu.com.cn/)。

其实就是一个数学加模拟啦。~~非常之水~~。

先给结论：

$$ans= \sum_{i=\max(4,t-m)}^{\min(t-1,n)} C_{n}^{i}\times C_{m}^{t-i}$$

分析：这个 $i$ 表示的是男生人数（怎么题解全都是女生人数？），女生就只有 $t-i$ 人，在这种情况下利用排列组合，很容易就能算出方案数是 $C_{n}^{i}\times C_{m}^{t-i}$。

那循环怎么枚举呢？

* **上界**：男生你最多只能选 $n$ 个，但是题目说了女生必须得选择一个，还剩了 $t-1$ 人，如果 $t-1$ 比 $n$ 小，就只能选 $t-1$ 个男生。所以上界就是 $\min(t-1,n)$。
      
* **下界**：男生你最少都得选 $4$ 个，但如果出现女生不够的情况，即 $t-4> m$ 时，就得男生去补，这时男生得有 $t-m$ 个。所以下界就是 $\max(4,t-m)$。

上面有点难理解，自行思考一下。

剩下的就不难了，注意！

1. **不开 `long long` 见祖宗！**

2. **写排列组合函数时，一定要边乘边除！否则会爆 `long long`！**

3. **`max` 函数里两值的类型必须相同！**

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long

LL n,m,t;

LL C(LL a,LL b)
{
    LL sum=1;
    for(int i=1;i<=a;i++) sum=sum*(b-i+1)/i;
    return sum;
}

int main()
{
	cin>>n>>m>>t;
    LL ans=0;
    for(int i=max(4ll,t-m);i<=min(t-1,n);i++)
    {
        ans+=C(i,n)*C(t-i,m);
    }
    cout<<ans<<endl;
	return 0;
}
```

---

## 作者：hjfjwl (赞：3)

[题解传送门](https://www.luogu.com.cn/problem/CF131C)

题目说现在有 $n$ 个男生和 $m$ 个女生，要你在这些人中选出 $t$ 个人，其中一定要有 $4$ 个男生和 $1$ 个女生。问你一共有多少中方案满足题目要求。我们可以枚举出还要加多少为男生，$i$ 从 $0$ 开始枚举到 $\min(t - 5,n - 4)$ 结束。每一次 $ans$ 加上 $\dbinom{n}{4 + i} \times \dbinom{m}{t - 4 - i}$ 就可以了。注意要计算时要变成变除，不然会超 long long。

AC code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//记得开long long
 inline int read()
{
	int x=0,flag=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
          	flag=-flag;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
	}
    return x*flag;
}
inline void write(int x)
{
	if(x<0)
    {
		x=~(x-1);
		putchar('-');
	}
	if(x>9)
      write(x/10);
	putchar(x%10+'0');
}
signed main(){
	int n,m,t;
	n = read();
	m = read();
	t = read();
	int ans = 0;
	for(int i = 0;i <= min(t - 5,n - 4);i++)//枚举男生能加得个数
	{
		int mul = 1ll;
		for(int j = n;j >= n - 3 - i;j--)//等于j >= n - 4 + i
		{
			//write(j);
			mul *= j;
			mul /= (n - j + 1);//一边乘一边除
		}
		int tt = t - 5 - i;
		for(int j = m;j >=m - tt;j--)//等于j >= m - (t - 4 - i) + 1
		{
			mul *= j;
			mul /= (m - j + 1ll);
		}
		ans += mul;
	}
	write(ans);
	putchar('\n');
	return 0;
}

```

---

## 作者：midsummer_zyl (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF131C)

## 题目描述：

剧团里有 $n$ 个男生和 $m$ 个女生。 现在要排一部新的话剧，需要 $t$ 个人，那么将要从剧团里选出 $t$ 个人，已知选出的人里面至少有 $4$ 个男生和 $1$ 个女生。请问一共有多少种不同的选法。

## SOLVE:

定义女生的最大值与最小值，循环求解 $C^i_m \times C^{t-i}_n$
左边代表选 $i$ 个女生的方案数，右边代表     $t-i$ 个男生的方案数。乘起来再求和即可。

## [AC 代码](https://www.luogu.com.cn/record/138690753)

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
LL C(LL x, LL y) {
	LL s = 1;
	for (int i = y, j = 1; i >= y - x + 1 && j <= x; i--, j++)
		s *= i, s /= j;
	return s;
}
int main() {
	LL n, m, t;
	cin >> n >> m >> t;
	LL a = max(1ll, t - n);
	LL b = min(m, t - 4);
	LL ans = 0;
	for (int i = a; i <= b; i++)
		ans += C(i, m) * C(t - i, n);
	cout << ans;
	return 0;
}
```


---

## 作者：Coros_Trusds (赞：1)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15431338.html)

# 题目大意

给定 $n,m,t$，表示有 $n$ 个男孩，$m$ 个女孩，现在要选出 $t$ 人。

并且保证至少有 $4$ 个男孩， $1$ 个女孩。

问有多少种选择方法。

# 题目分析

答案为 

$$\sum\limits^{\min\{m,t-4\}}_{i=\max\{1,t-n\}} C_{m}^{i}\times C_{n}^{t-i}$$

---
下面来讲一下这个式子的来源。

来看一下这个式子。

我们枚举 $i$，下界是 $\max\{1,t-n\}$，表示从 $t$ 个人中减去 $n$ 个男生的数量，剩下的就是**女生最少需要的数量**。

上界是 $\min\{m,t-4\}$，表示从 $t$ 个人中，减去男生至少需要的人数，剩下的就是**女生最多需要的数量。**

故 $C_{m}^i$ 表示女生的方案数，$C^{t-i}_n$ 表示男生的方案数。

根据乘法原理，相乘取和即是最终答案。

-----
一些注意事项：

1. 开 $\rm long~long$。

2. 求组合数时，应运用公式 $C_{n}^m=C_{n-1}^m+C_{n-1}^{m-1}$。

# 代码

```cpp
#define int long long

const int ma=35;

int C[ma][ma];

int n,m,t;

inline void init()
{
	for(register int i=0;i<=31;i++)
	{
		C[i][0]=1;
	}
	
	for(register int i=1;i<=31;i++)
	{
		for(register int j=1;j<=i;j++)
		{
			C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}
} 

#undef int

int main(void)
{
	#define int long long
	
	n=read(),m=read(),t=read();
	
	init(); 
	
	int ans=0;
	
	for(register int i=max(1ll,t-n);i<=min(t-4,m);i++)
	{
		ans+=C[m][i]*C[n][t-i];
	}
	
	printf("%lld\n",ans);
	
	return 0;
} 
```

---

## 作者：谦谦君子 (赞：1)

这是一道比较~~简单~~的组合数问题（逃）

## 题目大意：
从n个男孩m个女孩中选出t个人，要求男孩数量不小于4女孩数量不小于1，求方案数

直接看代码，组合推导过程就不详述了，结论看代码

**注意：一定要开long long!**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long combination(int n,int m)
{
    long long fac=1;
    for (int i=1;i<=m;i++)
    {
        fac=fac*(n-m+i)/i;
    }
    return fac;
}
int main()
{
    int n,m,t;
    while (~scanf("%d%d%d",&n,&m,&t))
    {
        long long sum=0;
        for (int i=4;i<=n;i++)
        {
            if (i<t&&t-i<=m)
            {
                sum+=combination(n,i)*combination(m,t-i);
            }
        }
        cout<<sum<<endl;
    }
    return 0;
}
```



---

## 作者：linxuanrui (赞：0)

### 思路

首先，选 $x$ 个男生的方法数是 $\dbinom{n}{x}\times\dbinom{m}{t-x}$。

接下来，可以枚举男生的个数：

1. 上界

男生一共只有 $n$ 个，所以不能选超过 $n$ 个男生。同时，女生的人数又要至少有 $1$ 个，因此不能选超过 $t-1$ 个男生。综上，男生的人数上界为 $\min(n,t-1)$。

2. 下界

题目要求至少选 $4$ 个男生，于此同时，女生最多选 $m$ 人，因此男生人数至少得是 $\max(4,t-m)$。

处理好上界和下界，就可以推出最后的答案是：$\sum\limits_{i=\max(4,t-m)}^{\min(n,t-1)}\dbinom{n}{i}\times\dbinom{m}{t-x}$。

此时，我们可以用组合数的递推公式 $\dbinom{a}{b}=\dbinom{a-1}{b-1}+\dbinom{a-1}{b}$ 来预处理。

### 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
ll n,m,t,a[35][35],ans; 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> t;
	for(int i = 1;i <= max(n,m) + 1;i++){
		for(int j = 1;j <= i;j++)a[i][j] = (j == 1 || j == i ? 1 : a[i - 1][j] + a[i - 1][j - 1]);
	}
	for(int i = max(t - m,4ll);i <= min(n,t - 1);i++)ans += a[n + 1][i + 1] * a[m + 1][t - i + 1];
	cout << ans;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF131C)

## 思路

要推一个式子。

考虑从男生下界 $\max(t-m,4)$ 枚举到男生上界 $\min(t-1,n)$。

- 男生下界中 $4$ 的由来： 男生至少选择 $4$ 人，但如果全选女生后，剩下的人数比 $4$ 还多，那么男生人数必须大于 $4$。

---

选择方案总数为：
$$\large\sum_{i=\max(t-m,4)}^{\min(t-1,n)}C_m^i\times C_n^{t-i}$$

- 注意输出使用 ``%I64d``。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long ans;
int a,b,t;
long long c(int n,int m){//计算组合数。
	long long res=1;//不开 long long 见祖宗。
	for(int i=m-n+1;i<=m;++i){
		res*=i;
		res/=i-m+n;
	}
	return res;
}
int main(){
	cin>>a>>b>>t;
	for(int i=max(t-b,4);i<=min(t-1,a);++i)ans+=c(i,a)*c(t-i,b);
	printf("%I64d\n",ans);
    return 0;
}
~~~

---

## 作者：Chang_Pei (赞：0)

### 思路：

组合计数问题，要求我们从 $n$ 个男生中选出 $x$ 个，$m$ 个女生中选出 $y$ 个，且 $x + y = t$。并且 $x \ge 4 $，$ y \ge 1$。

我们直接枚举所有情况，然后加起来即可。

$$ans \gets ans + C_{ n }^{x} \times C_{m}^{y}$$

其中由于组合数的计算过程如果先把阶乘算完再去除会爆 `long long`，我们利用组合数的原理，类下：

$$C_{10}^{3} = C_{10}^{2} \times 8 \div 3$$

一步步把对应的组合数求出来，这样就不会爆 `long long`。

$$C_{n}^{x} = C_{n}^{x-1} \times ( n - x + 1 ) \div x$$

### 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll ans=0;
int boy,girl,all;

inline ll work(int a,int b){
  ll answork=1;
  
  for(int i=b-a+1;i<=b;i++){  //数学计数
    answork*=i;
    answork/=i-b+a;           //组合数的原理
  }
  
  return answork;
}

int main(){
  cin>>boy>>girl>>all;
  
  for(int i=max(all-girl,4);i<=min(all-1,boy);i++){
    ans+=work(i,boy)*work(all-i,girl);          //枚举所有情况
  }
  
  cout<<ans;
  return 0;
}
```

---

## 作者：Arghariza (赞：0)

因为那个柿子出了点微妙的问题，索性删掉重写了。

以女生的取值范围观察：

1. 若男生没有 $t$ 人，女生需要补足他们，也就是需要至少 $t-n$ 人。
2. 若男生有或者超过 $t$ 人，也就是说女生取 $1$ 个都可以满足条件，那就至少 $1$ 个
3. 因为诡异的题目要求男生至少 $4$ 人，也就是说女生最多 $t-4$ 人。
4. 同时题目说女生最多 $m$ 人。

所以女生人数 $i\in [\max\{1,t-n\},\min\{t-4,m\}]\cup \mathbb{Z}$ 。

对于每个 $i$ ，组合方式有 $\large{\begin{pmatrix}^{m}_{\ i}\end{pmatrix}\begin{pmatrix}^{\ \ n}_{t-i}\end{pmatrix}}$ 种。

所以最后的柿子就是：

$$ans=\large\sum\limits_{\max\{1,t-n\}}^{\min\{t-4,m\}}\begin{pmatrix}^{m}_{\ i}\end{pmatrix}\begin{pmatrix}^{\ \ n}_{t-i}\end{pmatrix}$$

为了节省时间可以先把 $i$ 的域处理出来。

[$\mathtt{\color{lightgreen}{AC\ Code}}$](https://www.luogu.com.cn/paste/m0q4lqwc)

---

