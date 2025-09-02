# Maxim and Restaurant

## 题目描述

Maxim has opened his own restaurant! The restaurant has got a huge table, the table's length is $ p $ meters.

Maxim has got a dinner party tonight, $ n $ guests will come to him. Let's index the guests of Maxim's restaurant from 1 to $ n $ . Maxim knows the sizes of all guests that are going to come to him. The $ i $ -th guest's size ( $ a_{i} $ ) represents the number of meters the guest is going to take up if he sits at the restaurant table.

Long before the dinner, the guests line up in a queue in front of the restaurant in some order. Then Maxim lets the guests in, one by one. Maxim stops letting the guests in when there is no place at the restaurant table for another guest in the queue. There is no place at the restaurant table for another guest in the queue, if the sum of sizes of all guests in the restaurant plus the size of this guest from the queue is larger than $ p $ . In this case, not to offend the guest who has no place at the table, Maxim doesn't let any other guest in the restaurant, even if one of the following guests in the queue would have fit in at the table.

Maxim is now wondering, what is the average number of visitors who have come to the restaurant for all possible $ n! $ orders of guests in the queue. Help Maxim, calculate this number.

## 说明/提示

In the first sample the people will come in the following orders:

- $ (1,2,3) $ — there will be two people in the restaurant;
- $ (1,3,2) $ — there will be one person in the restaurant;
- $ (2,1,3) $ — there will be two people in the restaurant;
- $ (2,3,1) $ — there will be one person in the restaurant;
- $ (3,1,2) $ — there will be one person in the restaurant;
- $ (3,2,1) $ — there will be one person in the restaurant.

In total we get $ (2+1+2+1+1+1)/6 $ = $ 8/6 $ = $ 1.(3) $ .

## 样例 #1

### 输入

```
3
1 2 3
3
```

### 输出

```
1.3333333333
```

# 题解

## 作者：Stream月 (赞：5)

**背包+期望+组合数**

首先观察数据范围$n \leq 50,$ 确定这是一道 $O(n^4)$的题。

其次，这题具有非常明显的背包模型，不难想到状态表示$f[i][j][k]$ 前$i$个人选$j$ 个人进去体积为$k$的方案数，至此背包复杂度$O(n^3)$。

不难发现，当一个人进不去的时候和前面进了哪些人和进去的人的顺序是没有关系的，故考虑枚举第一个不能进去的人，然后统计方案数，时间复杂度$O(n ^ 4)$

方案数统计
$$
	\sum_{x = 1}^{n}\sum_{j=1}^{n -1}\sum_{k = max(0,p - a[x] +1)}^{p} j * j ! * (n - j - 1)!*f[n][j][k]
$$

枚举不能进去的人$x$,他进不去的条件是此时选中的$j$个人的体积$k$满足 $p - k < a[x]$,在$x$之前进去的人可以任意排列，在$x$之后进去的人亦可以任意排列,所以乘上排列数与方案数，在乘上对答案的贡献（即进去的人数$j$）

最后除以总方案数$n!$，得到期望

还有一些细节看代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;

using namespace std;
#define $(i,a,n) for(int i = a; i <= n; ++i)

inline ll read() {
	   ll ans = 0;
	   char last = ' ',ch = getchar();
	   while(ch < '0' || ch > '9') last = ch, ch = getchar();
	   while(ch >= '0' && ch <= '9') ans = (ans << 3) + (ans << 1) + ch - '0', ch = getchar();
	   if(last == '-') ans = -ans;
	   return ans;
}

const int INF = 0x3f3f3f3f;

const int N = 60;

double fac[N];
int a[N];
ll f[N][N][N];
int n, p;
void pre() {	//计算阶乘
	fac[0] = 1;
	for(int i = 1; i <= n; ++i) {
		fac[i] = 1.0 * i * fac[i - 1];
	}
}
double ans =0;
int sum = 0;
int main(){
	//freopen("testdata.in", "r", stdin);
	//freopen("ans.out", "w", stdout);
	n = read();
	$(i, 1, n) a[i] = read(), sum += a[i];
	p = read();
	if(sum <= p) {	//这种情况需要特判一下，所有人都可以进去
		printf("%.6lf\n", 1.0 * n);
		return 0;
	} 
	pre();
	for(int x = 1; x <= n; ++x) {
		memset(f, 0, sizeof f);
		f[0][0][0] = 1;
		for(int i = 1; i <= n; ++i) {
			for(int j = 0; j <= i; ++j) {
				for(int k = 0; k <= p; ++k) {
					if(i == x) {	//当前第x个人无法进入，所以直接跳过x
						f[i][j][k] = f[i - 1][j][k]; continue;
					}
					f[i][j][k] = f[i - 1][j][k];
					if(k >= a[i] && j > 0) f[i][j][k] += f[i - 1][j - 1][k - a[i]];
				}
			}
		}
		for(int j = 1; j < n; ++j) {
			for(int k = max(0, p - a[x] + 1); k <= p; ++k) {
				ans += j * fac[j] * fac[n - j - 1] * f[n][j][k];
			}
		}
	}
	printf("%.6lf\n", ans/fac[n]);
	return 0;
}


```
祝大家CSP 2019 rp++

---

## 作者：QwQ蒟蒻wjr (赞：2)

[我的blog](https://www.cnblogs.com/wangjunrui/p/12512412.html)
> > 题目链接：[CF261B Maxim and Restaurant](https://www.luogu.com.cn/problem/CF261B)

$$preface$$

背包DP+期望的一道题

$$description$$

题目翻译有QwQ

$$solution$$


我们要分两种情况讨论：
- $$\sum_{i=1}^{n}a[i]\leq p$$
- $$\sum_{i=1}^{n}a[i]> p$$

对于情况$1$，显然就是n个人都可以坐，那么直接输出$n$即可。

对于请款$2$，

设$f(i,j,k)$表示表示已经处理完前i个人选了j个人占了k这么长的方案数，那么答案显然是：
$$ans=\dfrac{\sum f(n,i,j)\times i!\times (n-i)!}{n!}$$

对于$f(i,j,k)$我们有两个策略，一个是选，一个是不选，得出：
$$f(i,j,k)=f(i-1,j-1,k-a[i])+f(i-1,j,k)$$
我们发现DP可以省掉一维

$$code$$
```
#include <cstdio>
#include <algorithm>
#define ll long long
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=55;
int n,p,a[N],sum;
long long dp[N][N];
double fac[N]= {1.0},ans;
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		sum+=a[i];
		fac[i]=fac[i-1]*i;
	}
	read(p);
	if(sum<=p)
	{
		printf("%lf\n",(double)n);
		return 0;
	}
	dp[0][0]=1;
	for(re int i=1; i<=n; ++i)
		for(re int j=i; j>=1; --j)
			for(re int k=p; k>=a[i]; --k)
				dp[j][k]+=dp[j-1][k-a[i]];
	for(re int i=1; i<=n; ++i)
	{
		for(re int j=0; j<=p; ++j)
			printf("%lld ",dp[i][j]);
		putchar('\n');
	}
	for(re int i=1; i<=n; ++i)
		for(re int j=0; j<=p; ++j)
			ans+=(double)dp[i][j]*fac[i]*fac[n-i];
	printf("%lf\n",ans/fac[n]);
	return 0;
}
```

---

## 作者：RyexAwl (赞：1)

考虑答案中每个前缀长度出现的次数。

设前缀长度$i$在答案中出现$g[i]$次，显然有：
$$
\sum_{i=0}^ng[i]=n!
$$
即每个前缀$i$所对的排列集两两不相交。
那么答案即：
$$
\sum_{i=1}^ng[i]\times i
$$
考虑计算出$g[i]$：

按第$i+1$个元素是什么分类：

第$i+1$个元素不同的两个排列，显然不同，因此这样的划分是满足不重不漏的。

而对于所有确定第$i+1$个元素的排列而言，我们可以将其分为两段：即$1\sim i$与$i+2 \sim n$。

而前面一段显然要满足：
$$
p-a[i+1]<\sum_{j=1}^ia[j]\le p
$$

显然我们可以在去除掉$a[i+1]$的序列中做一次背包求出其方案数。

具体地：
令$f[i][j][k_1][k_2]$为除了$a[i]$的序列中只考虑前$j$个元素，长度恰好为$k_1$和小于等于$k_2$的方案数。
有状态转移方程：
$$
f[i][j][k_1][k_2]=f[i][j-1][k_1][k_2]+f[i][j-1][k_1-1][k_2-a[j]]
$$
那么有：
$$
g[i]=i!(n-i-1)!\sum_{1\le j\le n}f[j][n][i][p]-f[j][n][i][p-a[j]]
$$
对于
$$
\sum_{i=1}^na[i]\le p
$$
特判一下即可。

时间复杂度$O(n^4)$

```cpp
#include <iostream>

namespace wxy{
    const int N = 55;
    double fac[N],g[N],f[N][N][N][N];
    int n,p,a[N];
    void main(){
        fac[0] = 1;for (int i = 1; i <= 50; i++) fac[i] = fac[i - 1] * i;
        std::cin >> n;
        for (int i = 1; i <= n; i++) std::cin >> a[i];
        std::cin >> p;
        int sum = 0;
        for (int i = 1; i <= n; i++) sum += a[i];
        if (sum <= p){std::cout << n;return;}
        for (int i = 1; i <= n; i++){
            f[i][0][0][0] = 1;
            for (int j = 1; j <= n; j++){
                f[i][j][0][0] = 1;
                for (int k1 = 1; k1 <= j; k1++){
                    for (int k2 = 1; k2 <= 50; k2++){
                        f[i][j][k1][k2] = f[i][j - 1][k1][k2];
                        if (j == i) continue;
                        if (k2 >= a[j]) f[i][j][k1][k2] += f[i][j - 1][k1 - 1][k2 - a[j]];
                    }
                }
            }
        }
        for (int i = 1;i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k1 = 1; k1 <= j; k1++)
                    for (int k2 = 1; k2 <= 50; k2++)
                        f[i][j][k1][k2] += f[i][j][k1][k2 - 1];
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                g[i] += f[j][n][i][p];
                if (a[j] > p) continue;
                g[i] -= f[j][n][i][p - a[j]];
            }
            g[i] = 1ull * g[i] * fac[n - i - 1] * fac[i];
        }
        long double ans = 0;
        for (int i = 1; i <= n; i++) ans += g[i] * i;
        ans /= fac[n];
        std::cout << ans;
    }
}signed main(){wxy::main();return 0;}
```


---

## 作者：spli (赞：0)

考虑每个i对答案的贡献

​	设$f[i][j][k]$表示前i个数，选出j个，S=k的方案数，按照背包转移
$$f[i][j][k]+=f[i-1][j][k]+[k\geq a[i]]\cdot f[i-1][j-1][k-a[i]]$$
​	然后需要乘一个排列数，即前j个数的全排列和后n-j个数的全排列

​	最后除以$n!$

​	注意求$f$的时候,$f[0 \cdots n][0][0]=1$

---

