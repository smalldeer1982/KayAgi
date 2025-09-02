# Integral Array

## 题目描述

You are given an array $ a $ of $ n $ positive integers numbered from $ 1 $ to $ n $ . Let's call an array integral if for any two, not necessarily different, numbers $ x $ and $ y $ from this array, $ x \ge y $ , the number $ \left \lfloor \frac{x}{y} \right \rfloor $ ( $ x $ divided by $ y $ with rounding down) is also in this array.

You are guaranteed that all numbers in $ a $ do not exceed $ c $ . Your task is to check whether this array is integral.

## 说明/提示

In the first test case it is easy to see that the array is integral:

- $ \left \lfloor \frac{1}{1} \right \rfloor = 1 $ , $ a_1 = 1 $ , this number occurs in the arry
- $ \left \lfloor \frac{2}{2} \right \rfloor = 1 $
- $ \left \lfloor \frac{5}{5} \right \rfloor = 1 $
- $ \left \lfloor \frac{2}{1} \right \rfloor = 2 $ , $ a_2 = 2 $ , this number occurs in the array
- $ \left \lfloor \frac{5}{1} \right \rfloor = 5 $ , $ a_3 = 5 $ , this number occurs in the array
- $ \left \lfloor \frac{5}{2} \right \rfloor = 2 $ , $ a_2 = 2 $ , this number occurs in the array

Thus, the condition is met and the array is integral.

In the second test case it is enough to see that

 $ \left \lfloor \frac{7}{3} \right \rfloor = \left \lfloor 2\frac{1}{3} \right \rfloor = 2 $ , this number is not in $ a $ , that's why it is not integral.

In the third test case $ \left \lfloor \frac{2}{2} \right \rfloor = 1 $ , but there is only $ 2 $ in the array, that's why it is not integral.

## 样例 #1

### 输入

```
4
3 5
1 2 5
4 10
1 3 3 7
1 2
2
1 1
1```

### 输出

```
Yes
No
No
Yes```

## 样例 #2

### 输入

```
1
1 1000000
1000000```

### 输出

```
No```

# 题解

## 作者：HPXXZYY (赞：3)

$\color{blue}{\texttt{[Solution]}}$

一个很经典的 trick 就是把这种跟因数（除法）有关的问题转化为跟倍数（乘法）有关。

首先，如果 $\left \lfloor \dfrac{x}{y}\right \rfloor=c$，则：

$$cy \leq x \leq (c+1)y-1$$

我们从 $a_{1 \cdots n}$ 中选取两个数 $a_{i},a_{k}$，如果 $a_{1 \cdots n}$ 完整，则按照题目要求：

$$\exists j \in [1,n], \quad \text{s.t.} \quad a_{i}a_{j} \leq a_{k} \leq (a_{i}+1)a_{j}-1$$

改变思路，枚举 $a_{i},a_{j}$，则对于它们两个数而言，$\forall a_{k} \in [a_{i}a_{j},(a_{i}+1)a_{j}-1]$ 都可以出现在 $a_{1 \cdots n}$。我们称为 $a_{i}$ 可以表示出 $a_{k}$。

显然，如果 $a_{k}$ 可以出现在完整的 $a_{1 \cdots n}$ 中，当且经当对于每一个 $a_{i}<a_{k}$，$a_{i}$ 可以表示出 $a_{k}$。

于是我们可以用一个数组 $s_{1 \cdots n}$，其中 $s_{k}$ 表示有多少个 $a_{i}$ 可以表示出 $a_{k}$。因此 $a_{k}$ 可以出现在完整的 $a_{1 \cdots n}$ 中当且仅当 $s_{k}=\text{rank}_{k}-1$，其中 $\text{rank}_{k}$ 表示 $a_{k}$ 是第几小的数字。

显然，我们可以用差分算法维护 $s_{1 \cdots n}$。

时间复杂度 $\mathcal{O}\left (\sum C \ln C\right )$。

具体实现看代码。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=1e6+100;

int pre[N],a[N],n,C,s[N];

int main(){
	for(int T=1,Q=read();T<=Q;T++){
		n=read();C=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		
		sort(a+1,a+n+1);
		n=unique(a+1,a+n+1)-a-1;
		//去重，这样可以快点吧，毕竟相同的数字是没有任何作用的
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if (1ll*a[i]*a[j]<=C){
					pre[a[i]*a[j]]++;
					if ((a[i]+1)*a[j]<=C)
						pre[(a[i]+1)*a[j]]--;
				}
				else break;//没有这个 O(C ln C) -> O(n^2)
		
		for(int i=1;i<=C;i++)
			s[i]=s[i-1]+pre[i];
		
		bool flag=true;
		for(int i=1;i<=n;i++)
			if (s[a[i]]<i){
				flag=false;break;
			}
		
		if (a[1]!=1) flag=false;
		
		printf("%s\n",flag?"Yes":"No");
		
		for(int i=1;i<=C;i++) pre[i]=s[i]=0;
		//老规矩，CF 上的题目不能使用 memset
	}
	
	return 0;
}
```

---

## 作者：Ezis (赞：3)

**题意:**

若一个数组长度为 $n$ 的数组 $a$，对于它之中任意两个元素 $x$，$y$，在 $a$ 中都存在 $\lfloor \frac{x}{y} \rfloor$，则称 $a$ 为一个 Integral Array。

先给你一个元素都不超过 $c$ 的数组，要判断它是否是 Integral Array。

**思路:**

发现这个 $c$ 很小，只有 $10^6$，所以可以将每个元素是否出现都存起来。

枚举倍数，若 $\lfloor \frac{a}{b} \rfloor = k$，则 $a$ 一定在 $[b \times k , b \times (k+1)-1]$ 这个范围内。

然后对每个元素判断一下数组中是否有在这个区间的就行了。

坑点：
不要把整个数组清空，否则时间会爆炸。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,T,mat[1000005],s[1000005];
bool check(){
	scanf("%d%d",&n,&c);
	for(int i=1;i<=c;i++) mat[i]=s[i]=0;
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		mat[x]=1;
	}
	if(!mat[1]) return false;
	for(int i=1;i<=c;i++) s[i]=s[i-1]+mat[i];
	for(int i=2;i<=c;i++){
		if(!mat[i]) continue;
		for(int j=i;j<=c;j+=i)
			if(s[min(c,j+i-1)]-s[j-1])
				if(!mat[j/i]) return false;
	}
	return true;
} 
int main(){
	scanf("%d",&T);
	while(T--){
		if(check()) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
} 
```


---

## 作者：Alarm5854 (赞：2)

## 题意
给定一个可重集 $S$，如果说这个可重集 $S$ 满足 $\forall x,y\in S,x\ge y$，都有 $\lfloor x/y\rfloor\in S$，那么这个可重集就是封闭的。现在要判断一些可重集是否封闭。
## 解法
可以考虑对于每一个出现的数字 $x$，暴力枚举 $d$，先判断是否有 $y\in S\cap[d\times x,(d+1)\times x-1]$，如果有，再判断是否有 $d\in S$，如果没有，这个集合就是不封闭的。

分析一下时间复杂度：判断一段区间是否有数可以用前缀和，如果两端前缀和不等，说明这段区间有数，所以是 $O(c)$ 的；暴力枚举 $d$ 至 $x\times d>c$，所以复杂度为 $O(\sum c/i)$，即 $O(c\ln c)$ 的。综上，时间复杂度为 $O(c\ln c)$。
```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1e6+7;
ll read(){
	char c;
	ll x=0,f=1;
	while(!isdigit(c=getchar()))
		f-=2*(c=='-');
	while(isdigit(c)){
		x=x*10+f*(c^48);
		c=getchar();
	}
	return x;
}
int T,n,c,a[N],vis[N],s[N];
void solve(){
	n=read();
	c=read();
	for(int i=1;i<=c;++i){//多测不清空，WA两行泪
		vis[i]=0;
		s[i]=0;
	}
	for(int i=1;i<=n;++i){
		a[i]=read();
		++s[a[i]];
		vis[a[i]]=1;
	}
	for(int i=1;i<=c;++i)//记录前缀和
		s[i]+=s[i-1];
	for(int i=1;i<=c;++i){
		if(!vis[i])
			continue;
		for(int j=1;i*j<=c;++j){
			int l=i*j;
			int r=min(c,i*(j+1)-1);//对c取min，防止出现奇怪的问题
			if(s[r]>s[l-1]){
				if(!vis[j]){//可以直接判断这个集合不封闭
					puts("No");
					return;
				}
			}
		}
	}
	puts("Yes");
}
int main(){
	T=read();
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：Dream__Sky (赞：0)

暴力枚举两个数，复杂度为 $O(n^2)$，显然不能通过此题，我们考虑枚举其它的东西。

令 $m=\lfloor\dfrac{x}{y}\rfloor$。直接暴力枚举行不通，那么就每次枚举 $m$ 与 $y$，根据向下取整的性质，$x$ 需要满足 $m\cdot y\leq x\leq (m+1)\cdot y-1$。由于本题值域较小，可以用桶加前缀和的方式维护。

这个思路很常见，就是把枚举因数，改为枚举倍数。

时间复杂度为 $O(\sum{\dfrac{c}{i}})$，其中 $1\leq i\leq c$，复杂度即 $O(c \ln c)$。

注意别用 `memset`。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace work
{
	const int N=1e6+10;
	int n,c,a[N],s[N];
	bool p[N];
	int main()
	{
		cin>>n>>c;
		for(int i=1;i<=c;++i) s[i]=p[i]=0;
		for(int i=1;i<=n;i++) 
		{
			cin>>a[i];
			p[a[i]]=1,s[a[i]]++;
		}
		for(int i=1;i<=c;i++) s[i]+=s[i-1];
		
		if(!p[1]) {cout<<"No\n";return 0;}
		for(int i=1;i<=c;i++)
		{
			if(!p[i]) continue;
			for(int j=1;i*j<=c;j++)
				if(s[min(c,(j+1)*i-1)]-s[j*i-1]>0&&!p[j]) {cout<<"No\n";return 0;}
		}
		cout<<"Yes\n";
		return 0;
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) work::main();
	return 0;
}

```


---

## 作者：Robin_kool (赞：0)

题意其他题解讲的很清楚，这里不在叙述。

观察数据范围，发现 $O(n^2)$ 的神秘做法肯定会被卡，那么考虑优化题目中给定的柿子。

由于向下取整的定义，令 $l=d \times a_i,r=(d+1)\times a_i-1$，其中 $(d \geq 1)$。那么对于其他的 $a_j$，如果不存在 $x \leq a_j \leq y$，显然是无解的。

可以用前缀和来查询一段区间内是否存在合法的数。

注意多测清零，有些地方的 $c$ 不要写成 $n$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
ll T, n, C, a[N], c[N], p[N];
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	//freopen("1648B.in", "r", stdin);
	//freopen("1648B.out", "w", stdout);
    T = read();
    while(T --){
    	n = read(), C = read();
    	for(int i = 1; i <= C; ++ i){
    		c[i] = p[i] = 0;
		}
		for(int i = 1; i <= n; ++ i){
			a[i] = read();
			++ c[a[i]], p[a[i]] = true;
		}
		bool f = 0;
		for(int i = 1; i <= C; ++ i) c[i] += c[i - 1];
		for(int i = 1; i <= C; ++ i){
			if(!p[i]) continue;
			for(int j = 1; i * j <= C; ++ j){
				int l = i * j, r = min(C, 1ll * i * (j + 1) - 1);
				if(c[r] - c[l - 1] > 0 && !p[j]){
					f = 1;
					break;
				}
			}
			if(f) break;
		}
		puts(f ? "No" : "Yes");
	}
	return 0;
}

```


---

## 作者：Doubeecat (赞：0)


> 给定一个数组 $a $ ,  我们称该数组完整需要满足 ：若数组 $a$ 中存在两数 $x,y $, 使 $y \le x$ ($x,y$ 可以是同一个数) , 则 $\left\lfloor\dfrac{x}{y}\right\rfloor$ 也必须在数组 $\ a$ 中 , 现需要判断数组$\ a$ 是否完整 。
> 
> $T \le 10^4 ,\sum n\le 10^6,\sum c\le 10^6$ ,  其中$\ T$ 为数据组数  ， $\ n$ 为$\ a$ 的元素个数，满足 $a$ 中元素 $\le c$。

## 分析

直接枚举 $x,y$ 的话的时间复杂度是 $\mathcal{O}(n^2)$ 的，显然不行。

所以我们考虑如何优化这个枚举。

> 引理1
> $$
 \forall n \in \mathbb{N}_{+}, \left|\left\{ \lfloor \frac{n}{d} \rfloor \mid d \in \mathbb{N}_{+},d\leq n \right\}\right| \leq \lfloor 2\sqrt{n} \rfloor 
> $$
> 简略证明：
> 
> 对于 $d\leq \left\lfloor\sqrt{n}\right\rfloor$ 来说，$\left\lfloor\frac{n}{d}\right\rfloor$ 有 $\left\lfloor\sqrt{n}\right\rfloor$ 种取值
> 
> 对于 $d> \left\lfloor\sqrt{n}\right\rfloor$ 来说，有 $\left\lfloor\frac{n}{d}\right\rfloor\leq\left\lfloor\sqrt{n}\right\rfloor$ 同样只有 $\left\lfloor\sqrt{n}\right\rfloor$ 种取值
> 
> (from [OI-wiki](https://oi-wiki.org/math/number-theory/sqrt-decomposition/#2))

根据引理 1，我们知道了实际上不同的 $\left\lfloor\frac{x}{y}\right\rfloor$ 的个数为 $2\left\lfloor\sqrt{x}\right\rfloor$，所以我们首先考虑枚举 $\left\lfloor\frac{x}{y}\right\rfloor = k \leq \left\lfloor\sqrt{x}\right\rfloor$ 并且进行判断。

判断的部分，我们可以开一个桶来储存每一个数字的出现个数，对这个桶做前缀和就可以很方便的在 $\mathcal{O}(1)$ 的时间内查询 $[l,r]$ 是否存在一个数。

但是这样的时间复杂度是 $\mathcal{O}(n\sqrt{n})$ 的，还是无法通过本题，如何进一步优化呢？

我们换一种思路考虑，采用一个类似线性筛的思路。同样是枚举 $\left\lfloor\frac{x}{y}\right\rfloor= k\times i$，其中 $x | i$。检查 $[ki,(k+1)i)$（注意是左开右闭）中是否存在数，如果存在，那么 $i$ 一定要存在，否则不满足。

根据调和级数相关有 $\sum\limits_{i = 1}^n = \ln n$，故时间复杂度为 $\mathcal{O}(n\ln n)$ 可以通过本题。

## 代码

```cpp
const int N = 2e6  +10000;

int n,c,a[N],buc[N],pre[N];

void solve() {
    read(n,c);
    for (int i = 1;i <= 2*c;++i) pre[i] = 0,buc[i] = 0;//注意初始化到 2 * c
    for (int i = 1;i <= n;++i) read(a[i]),buc[a[i]]++;
    for (int i = 1;i <= 2*c;++i) pre[i] = pre[i - 1] + buc[i];
    bool flag = 0;
    for (int i = 1;i <= c;++i) {
        if (!buc[i]) continue;
        for (int j = 1;i * j <= c;++j) {
            int l = i * j,r = i * (j + 1) - 1;
            if (!buc[j]) {
                if (pre[r] - pre[l - 1]) {
                    flag = 1;
                    break;
                }
            }
        }
    }
    if (!flag) puts("Yes");
    else puts("No");
}

signed main() {
    int T;read(T);
    while (T--) solve();
	return 0;
}
```

---

## 作者：Deuteron (赞：0)

### 题意：
给定一个数组 $a$ ，如果对于任意的 $x,y$ 在数组 $a$ 中使 $y\le x$ ( $x,y$ 可以是同一个数) , $\lfloor{ \frac{x}{y}}\rfloor$ 也在数组 $a$ 中 , 我们就称数组 $a$ 完整。 现需要判断数组$a$是否完整。多组测试数据。

## solution

枚举 $x,y$ ，时间复杂度 $O(n^2)$，妥妥 TLE。

我们考虑枚举 $\lfloor{ \frac{x}{y}}\rfloor$ 的值，不妨设为  $t$ ，则若有一个不在 $a$ 中的 $t$ 使得存在一组 $x , y$ ，$\lfloor{ \frac{x}{y}}\rfloor=t$ 则这个数组必定不是完整的。

我们继续枚举 $y$ ，显然 $ty\le c$ 

问题转化为了在区间 $[ty,ty+y-1]$ 上寻找 $x$ 

这可以用前缀和维护。

于是时间复杂度为 

$\sum_{i=1}^{c} \frac{c}{i}=c \ln{c}$ 可以通过本题。

注意：当取 $x=y$ 时，取值为 $\lfloor{ \frac{x}{x}}\rfloor$ 恒等于 $1$ ，所以若原数组中没有 $1$ ，直接判掉即可。

## Code：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N];
int s[N];
int ss[N];
int t,n,c;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>c;
		for(int i=1;i<=c;i++) s[i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s[a[i]]=1;//标记
		}
		for(int i=1;i<=c;i++) ss[i]=ss[i-1]+s[i];//计算前缀和
		if(!s[1]){//若数组中不含有1，则必定不完整
			cout<<"No"<<endl;
			continue;
		}
		int fl=1;
		for(int i=1;i<=c;i++){
			if(s[i]||(i==1)) continue;
			if(!fl) break;
			for(int j=1;j<=c/i;j++){
				if(!fl) break;
				if(!s[j]) continue;
				int l=i*j;
				int r=min(i*j+j-1,c);//x的范围
				if(ss[r]-ss[l-1]>0){
					cout<<"No"<<endl;//存在x
					fl=0;
				}
			}
		}
		if(fl) cout<<"Yes"<<endl;//不存在x
	} 
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1800}$
---
### 解题思路：

枚举因子转化为枚举倍数的 $\text{trick}$ 老容易忘掉。

原问题就是对于每一个存在的数 $x$ 枚举其存在的因子 $i$，然后检验 $\left\lfloor\dfrac{x}{i}\right\rfloor$ 是否存在，如果使用单个的数的话处理起来会比较麻烦，不妨用一个桶记录下某一个数值是否存在。然后复杂度能做到 $O(n\sqrt{n})$。

那么转换为枚举倍数，对于一个存在的数 $i$，枚举所有的可能的倍数 $j$，若 $[i\times j,i\times(j+1))$ 中有数存在，则 $j$ 一定要存在，否则 $\left\lfloor\dfrac{x}{i}\right\rfloor=j$，其中 $x\in[i\times j,i\times(j+1))$ 一定不满足。

然后这里需要用前缀和来代替枚举 $[i\times j,i\times(j+1))$，总复杂度为 $O(n\log n)$。

---
### 代码：
```cpp
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
int T,n,c,x,flag,sq[1000005];
int a[1000005];
int read(){
	int num=0;
	char c=getchar();
	for(;c<'0'||c>'9';c=getchar());
	for(;c<='9'&&c>='0';c=getchar())num=num*10+c-'0';
	return num;
}
int find(int l,int r){
	return a[min(c,r)]-a[max(0,l-1)];
}
int main(){
	T=read();
	while(T--){
		n=read();c=read();
		for(int i=1;i<=c;i++)a[i]=0;
		for(int i=1;i<=n;i++)x=read(),a[x]=1;
		for(int i=1;i<=c;i++)a[i]+=a[i-1];
		flag=1;
		for(int i=1;i<=c;i++){
			if(find(i,i)==0)continue;
			for(int j=1;j<=c/i;j++){
				if(find(i*j,i*(j+1)-1)!=0&&find(j,j)==0){
					flag=0;
					break;
				}
			}
			if(flag==0)break;
		}
		if(flag)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：I_am_Accepted (赞：0)

### Preface

又是一道**枚举因数转化为枚举倍数**的好题。

### Analysis

若判断没有 $a_i=1$，直接 NO。

我们将 $\{a\}$ 去重，设为 $\{b\}$，并将 $\{b\}$ 入桶 $T$。

此时桶 $T$ **作前缀和**，以便于区间询问。

对于每一个 $b_i$，判断是否能成为 $\lfloor\frac{x}{y}\rfloor$ 中的 $y$ 使得 $\lfloor\frac{x}{y}\rfloor$ 不在 $\{b\}$ 中。

将 $>b_i$ 的数（桶中）划分成多个段，使得每个段中数 $\lfloor\frac{x}{b_i}\rfloor$ 的值相同。

若某一段中有值（区间询问），则判断是否有 $\lfloor\frac{x}{b_i}\rfloor$ 即可。

时间 $O(c\ln c)$，因为

$$\lim_{n\to\infty}\sum_{i=1}^{n}\frac{1}{i}=\ln n+\gamma$$

### Code

[Link](https://codeforces.com/contest/1648/submission/149199285)

---

## 作者：include_BM (赞：0)

题意：给定一个序列 $\{a\}$，是否满足若 $x\in\{a\},y\in\{a\},x\ge y$，那么 $\left\lfloor\frac{x}{y}\right\rfloor\in\{a\}$。

假设 $x\in[i\times j,i\times j+i)$，那么 $\left\lfloor\frac{x}{i}\right\rfloor=j$，此时若有 $x\in\{a\},i\in\{a\},j\not\in\{a\}$，那么显然这个序列就是不满足要求的。

所以可以考虑直接枚举 $i,j$，若存在上述情况判断该序列不满足要求并输出 `No`。

若该序列中有两个相同的元素，显然去掉其中一个并不会影响到答案，所以我们先对序列去重。

对于每个 $i$，可能的 $j$ 有 $\left\lfloor\frac{c}{i}\right\rfloor$ 种，那么 $\sum j=\sum \left\lfloor\frac{c}{i}\right\rfloor$，又因为每个 $i$ 都不同且数量 $\le c$，故 $\sum \left\lfloor\frac{c}{i}\right\rfloor<\sum_{k=1}^c \frac{c}{k}$。

当 $c$ 不断增大时 $\sum_{k=1}^c \frac{c}{k}$ 会接近 $c\ln c$（详见 [调和级数 - 百度百科](https://baike.baidu.com/item/%E8%B0%83%E5%92%8C%E7%BA%A7%E6%95%B0/8019971)），故总复杂度为 $O(n\log n)$（$n,c$ 同阶）。

```cpp
const int N=1e6+10;
int n,c,a[N],b[N],ok;
inline int sum(int l,int r){
    return b[min(r,c)]-b[l-1];
}//若 sum(l,r)>0 说明存在序列中存在 [l,r] 范围内的数。
signed main(){
    for(int T=read();T;--T){
        n=read(),c=read(),ok=1;
        for(int i=1;i<=c;++i) b[i]=0;
        for(int i=1;i<=n;++i) a[i]=read(),++b[a[i]];
        sort(a+1,a+n+1),n=unique(a+1,a+n+1)-a-1;//去重。
        for(int i=1;i<=c;++i) b[i]+=b[i-1];
        for(int i=1;i<=n&&ok;++i)//枚举 a[i]（上文中的 i）和 j。
            for(int j=1;a[i]*j<=c&&ok;++j)
                if(!sum(j,j)&&sum(a[i]*j,a[i]*j+a[i]-1)) ok=0;
        ok?puts("Yes"):puts("No");
    }
    return 0;
}
```

---

