# 「DROI」Round 2 构造与取模

## 题目背景

与其编写苍白无力的背景，不如出更有质量的题。



## 题目描述

对于整数 $n,k$，若存在**非负整数** $x$ 与 **正整数** $y$ 满足：

$$x + y = n\ \land\ x \bmod y =k$$

则我们称有序数对 $(x,y)$ 是 $n$ 的一个 **优秀拆分**（其中 $\land$  是**并且**的意思）。

现给定非负整数 $n,k$，请你构造**任意**一组 $n$ 的优秀拆分，并分别输出你构造方案中的 $x$ 和 $y$。特殊地，若不存在这样的拆分，则输出 `-1`。

## 说明/提示

#### 样例解释

对于第一组数据，只存在唯一的构造方式。

对于第二组数据，$(3,10)$ 也是一组合法的构造。

对于第三组数据，可以证明不存在一组合法的构造。

------------

#### 数据范围

**「本题采用捆绑测试」**

- $\operatorname{Subtask} 1(20\%)$：$n \leq 10^6$。

- $\operatorname{Subtask} 2(40\%)$：$n \leq 10^{12}$。

- $\operatorname{Subtask} 3(40\%)$：无特殊限制。

对于 $100\%$ 的数据：$T \leq 5$，$0 \leq n,k \leq 10^{18}$。

## 样例 #1

### 输入

```
3
1 0
13 3
198818800000 122122200000```

### 输出

```
0 1
8 5
-1```

# 题解

## 作者：Demeanor_Roy (赞：9)

- 出题人题解。

------------

第一档暴力枚举，第二档枚举因数，这里就不详细阐述了，下面讲正解。

考虑这样一个结论：


- 对于任意正整数 $x,y$，若 $x \leq y$，则有 $y \bmod x \leq \lfloor \frac{y-1}{2} \rfloor$。

证明的话分两种情况：

1. $x \leq \lfloor \frac{y}{2} \rfloor$，显然答案小于模数，结论成立。

2. $x > \lfloor \frac{y}{2} \rfloor$，不难发现 $y \bmod x \ = \ y-x$，结论也成立。

所以当给定的 $n,k$ 满足 $k > \lfloor \frac{n-1}{2} \rfloor$ 时无解，否则就一定有 $k \leq \lfloor \frac{n-1}{2} \rfloor$，此时输出 $k$ 和 $n-k$ 即可。

至此这道题解决完毕，时间复杂度 $O(T)$。下附代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int T;
long long n,k;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		if(k<=(n-1)>>1)	printf("%lld %lld\n",k,n-k);
		else printf("-1\n");
	}
	return 0;	
} 
```




---

## 作者：Eleveslaine (赞：5)

**结论**：若 $n-k>k$，则一组合法解为 $x=k,y=n-k$，否则无解。

**证明**：显然当 $x=k,y=n-k$ 时满足 $x+y=n$。  
$x \bmod y=k$，即存在非负整数 $m$，使得 $x-my=k$。    
代入得 $k-m(n-k)=k$，令 $m=0$，上式成立。  
（或者也可以把 $x \bmod y$ 当成 $x-y$ 理解）

同时，$x \bmod y=k$，余数一定小于除数，因此 $k<y$，即 $n-k>k$。若不满足此条件则无解。

代码不用给了吧。

---

## 作者：zhlzt (赞：4)

### 做法
为了满足 $x + y = n\ \land\ x \bmod y =k$，必须有 $x\ge k,y>k$，我们分情况讨论（为了方便，将 $x \bmod y =k$ 变为 $x=my+k$）：
- 若 $x<y$，则 $m=0$ 时可行，此时 $x=k,y=n-k$，又因为 $x<y$，所以要满足 $n>2k$。
- 若 $x\ge y$，则 $m>0$ 时可行，此时 $x\ge y+k$（因为 $m$ 至少为 $1$），又有 $y>k$，这样 $x\ge y+k$ 就可化为 $x>2k$，所以要满足 $n>3k+1$。

很明显，$x<y$ 时对 $n$ 的要求更低，那么只需要判断是否满足 $n>2k$ 即可，成立就输出 $k$ 和 $n-k$，否则输出 $-1$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		long long n,k;scanf("%lld%lld",&n,&k);
		if(n>k*2) printf("%lld %lld\n",k,n-k);
		else printf("-1\n");
	}
	return 0;
}
```

---

## 作者：zymooll (赞：4)

### 前言

本题解并非多项式时间复杂度内的正解，意在于一种做题思路，请读者选择性参考！

本人在考场上开题，看到这道题死活想不出正解，于是想到了随机算法.

### 题意简述

给定 $n,k$ 求一组 $x,y$ 满足 $x + y = n \texttt{ and } x \bmod y = k$.

### 思路

我们采用随机算法解决该问题.

首先，我们来解决若一组 $x,y$ 为合法解的条件.

因为，$x+y=n$.

所以，$y=n-x$.

因为，$x \bmod y=k$.

所以，$x \bmod (n-x)=k$.

所以，$(x-k) \bmod (n-x)=0$.

所以，$\Large{\frac{x-k}{n-x}}$ $=a\texttt{ }(a \in \mathbb{N*})$

其次，我们来解决取值范围问题.

因为，$x \in \mathbb{N},y \in \mathbb{N*}$.

所以，$y=n-x \in \mathbb{N*}$.

所以，$0 \le x \le n-1$. (1)

因为，$x \bmod y=k$.

所以，$x \ge k$. (2)

所以，$y \ge k$. (3)

所以，因为(2)，$x=n-y \le n-k$. (4)

所以，因为(2)(3)，$n=x+y \ge 2k$. (5)

所以，当且仅当 $x=y=k$ 时，$n=2k$.

但是在该条件下 $x \bmod y = 0 = k$.

故 $n=2k$ 不成立. (6)

所以，联立(5)(6)，得 $n > 2k$.

因为，$k \ge 1$.

所以，联立(2)(4)，得 $k \le x \le n-k$.

综上所述，有 $\left\{\begin{matrix} 
  			n > 2k \\  
  			k \le x \le n-k
			\end{matrix}\right. $

所以我们可以发现，不成立的情况为 $n \le 2k$.

考虑完不成立的情况，我们就可以开始随机枚举 $x$ 了.

我们可以发现，我们每枚举一次 $x$，必定可以得到一个实数 $\Large{\frac{x-k}{n-x}}$，又因为根据我们对于有解的推断，当且仅当 $\Large{\frac{x-k}{n-x}}$ $\in \mathbb{N*}$ 时，我们就得到了一个解.

所以，可以考虑记录每次随机出来的 $\Large{\frac{x-k}{n-x}}$ 的值，记录其最大值 $max$ 和最小值 $min$.

可以发现，当 $\lceil min \rceil \le \lfloor max \rfloor$ 时，我们就找到了 $\lfloor max \rfloor - \lceil min \rceil + 1$ 组解.

在区间内，我们任取一个正整数 $a$ 作为 $\Large{\frac{x-k}{n-x}}$ 的值.

这样我们可以得到题目的一组解 $\left\{\begin{matrix} 
  			x=\Large{\frac{a \cdot n+k}{a+1}} \\  
  			y=n-x
			\end{matrix}\right. $

### 代码

根据上述思路，我们可以很方便的得到代码.

这里给出参考代码，其中 $a$ 取 $\lceil min \rceil$.

```cpp
// Author:zymooll

#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,k;
signed main(){
    random_device rd;
    srand(rd());
	T=read();
    while(T--){
        n=read(),k=read();
        if(2*k>=n){
            puts("-1");
            continue;
        }
        long double maxn=LONG_LONG_MIN,minn=LONG_LONG_MAX;
        while(1){
            int x=k+rand()*rand()%(n-2*k);
            long double pp=(x-k)*1.0/(n-x);
            maxn=max(maxn,pp);
            minn=min(minn,pp);
            if(ceill(minn)<=floorl(maxn)){
                int ls=ceill(minn);
                int x=(ls*n+k)/(ls+1);
                int y=n-x;
                print(x),putchar(' '),print(y),putchar('\n');
                break;
            }
        }
    }
	return 0;
}
```

注：为美观，略去了快读快写，请读者自行补全.

### 后记

说实话，考场上真的没想到做法，于是想到了这么个歪门邪道，这种做法也可以给各位做个参考吧.

关于时间复杂度：看脸，不过随机数均匀的话，应该还是挺快的（别像我一样用 ```rand()*rand()```，这玩意生成的随机数不均匀的）

感谢您耐心的阅读！

---

## 作者：___w (赞：4)

### [P9373 「DROI」Round 2 构造与取模](https://www.luogu.com.cn/problem/P9373)

#### 题意简述
- 给定非负整数 $n,k$。
- 构造非负整数 $x$ 与正整数 $y$ 满足  $\begin{cases}x+y=n\\x\bmod y=k\end{cases}$

#### 题目分析
这是一道数论题。

由 $x+y=n$ 得 $x=n-y$。将 $x=n-y$ 代入 $x\bmod y=k$，得 $(n-y)\bmod y=k$。

设 $n-y=qy+k$，其中 $q$ 为非负整数。整理可得 $y=\frac{n-k}{q+1}$，所以当 $q=0$ 时 $y$ 一定有解，此时 $x=k$，$y=n-k$。所以 $x\bmod y=k\bmod(n-k)=k$ 成立且仅当 $k<(n-k)$，也就是 $2k<n$ 时，一定存在一组构造方案为 $(k,n-k)$，否则就无解，应当输出 $-1$。

注意 $(k, n-k)$ 仅仅只为其中的一种情况，其他情况取决于 $q$ 的取值以及 $x\bmod y=k$ 的约束情况，这里为了写代码方便就只构造了 $(k, n-k)$ 这一种情况，其他的情况可以通过枚举 $n-k$ 的约数来求得。

#### 代码
有了结论代码就不难写了。
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, n, k;
int main() {
	cin >> t;
	while (t--) {
		cin >> n >> k;
		if (2*k < n) cout << k << ' ' << n-k << '\n';
		else cout << -1 << '\n';
	}
	return 0;
}
```

---

## 作者：Loser_Syx (赞：3)

## 思路

既然题目要求构造出一组 $(x,y)$，使得 $x + y = n$ 且 $x \bmod y = k$，那么最简单粗暴的方法就是令 $x = k$，同时将 $y$ 设置成一个比 $k$ 大的数，同时使 $x + y = n$。

此时 $y$ 需要等于 $n - x$，如果当 $y \leq k$ 时，除数没有比余数大，那么无法构造了。

## 代码

```cpp
#include <iostream>
using namespace std;
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        long long n, m;
        scanf("%lld%lld",&n,&m);
        if(m + m >= n) puts("-1");
        else printf("%lld %lld\n", m, n-m);
    }
    return 0;
}
```

---

## 作者：Aisaka_Taiga (赞：1)

考试的时候打了个比较麻烦的做法。

首先看到 $k=0$ 的时候直接输出 $0，n$ 即可，如果要是 $k>n$ 的时候说明我们是构造不出这样的 $x,y$ 的，因为 $x$ 最大就是 $n$，没法得到 $k$，如果要是 $k=n$ 的话，我们同样无法得到答案，因为除数不能为 $0$。

然后就是看看题目里的式子了。

由 $x+y=n$ 能推出 $x=n-y$，然后带到二式里 $(n-y) \bmod y=k$，我们设 $n-y=\lambda k+y$，移项得到 $y=\frac{n-\lambda k}{2}$，所以我们可以直接枚举 $\lambda$。

但是我们还需要考虑有一种情况就是 $k$ 很小，比如 $1，2$ 这种的。

那我们枚举 $\lambda$ 的复杂度就退化到 $O(n)$ 了。

所以我们打个暴力，我们发现，如果要是 $k\bmod (n-k)=k$ 那我们就可以直接输出了，而且这个情况可以帮我们过滤掉 $k$ 或者是 $n$ 特别大的情况。

然后注意几个小细节比如零不能当除数啊，$y$ 求出来不能是小数之类的。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 1000100
using namespace std;
int t,n,k;
signed main()
{
	cin>>t;
	while(t--)
	{
		int flag=1;
		cin>>n>>k;
		if(k==0){cout<<"0 "<<n<<endl;continue;}
		if(k>=n){puts("-1");continue;}
		if(k%(n-k)==k){cout<<k<<' '<<(n-k)<<endl;continue;}
		if(k==1)
		{
			if(n%2==0)puts("-1");
			else cout<<(n/2+1)<<" "<<(n/2)<<endl;
			continue;
		}
		for(int i=0;n-i*k>0;i++)
		{
			if((n-i*k)%2==1)continue;
			int y=(n-i*k)/2;
			if(y==0)continue;
			int x=n-y;
			if(y<=k)break;
			if(x%y!=k)continue;
			if(x+y!=n)continue;
			cout<<x<<" "<<y<<endl;
			flag=0;
			break;
		}
		if(flag)puts("-1");
	}
	return 0;
}
```

---

## 作者：Eason_cyx (赞：1)

upd on $2023.5.30$：被喷了，重新修改。

数学题。（这个蒟蒻赛时想了 2.27h 才过 QwQ）

给个结论：当 $x < y$ 时，$x = k$。此时 $y$ 应该大于 $k$才能成立，也就是说 $n$ 应该大于 $2k$，答案就等于 $k$ 和 $n-k$，否则无解。



有了结论，代码就好写了。

警钟撅烂：不开 long long 见祖宗哦。
```cpp
#include <iostream>
using namespace std;
int main() {
    int T; cin >> T;
    while(T--) {
        long long n,k; cin >> n >> k;
        if(k * 2 >= n) {
            cout << -1 << endl;
        } 
        else if(k * 2 < n) {
            cout << k << ' ' << n-k << endl;
        }
    }
    return 0;
}
```

---

## 作者：Vct14 (赞：0)

我们可以从满足 $x \bmod y =k$ 的 $x$ 和 $y$ 中选出符合 $x+y=n$ 的一组。

设 $u=\dfrac{x-k}{y}$，即 $x=uy+k$，则 $n=x+y=uy+k+y=(u+1)y+k$。所以 $y=\dfrac{n-k}{u+1}$。

注意因为 $y$ 是除数，$k$ 是余数，所以 $y>k$。若当 $y$ 取到最大值时，还有 $y\le k$，则无解。因此只用判断 $y$ 的最大值是否小于等于 $k$。

$u=0$ 时，$y=\dfrac{n-k}{u+1}=n-k$ 可以取到最大值，因此只用判断 $n-k$ 是否小于等于 $ k$。若小于等于，则无解，输出 $-1$。

若有解，则 $y=n-k$，$x=uy+k=k$。输出 $k$ 和 $n-k$ 即可。

注意，本题有多组测试数据，且需要开 `long long`。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int T;
	cin>>T;
	while(T--){
		long long n,k;
		cin>>n>>k;
		if(n-k>k) cout<<k<<" "<<n-k;
		else cout<<"-1";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送](https://www.luogu.com.cn/problem/P9373)

很明显这道题 $n$ 的范围再加上多测是无法暴力通过的，考虑 $O(T)$ 的**构造**做法。

我们不妨令 $y \times 0+k=x$，由于 $y$ 是除数，所以肯定比 $k$ 大，所以 $x$ 最小为 $k$ 本身，$y$ 最小为 $k+1$，$x+y$ 的最小值就是 $2k+1$。

显然当 $n \le 2k$ 时，无解，输出 $-1$ 即可。

否则就输出 $k$ 和 $n-k$。

上 AC 代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long n,k,t;
int main(){
	cin>>t;
	while(t--)
	{
		bool f=0;
		cin>>n>>k;
		if(2*k+1>n)
		{
			cout<<-1<<endl;
			continue;
		}
		cout<<k<<" "<<n-k<<endl;
	}
	return 0;
} 
```



---

## 作者：SamHJD (赞：0)

[P9373 「DROI」 Round 2 构造和取模](https://www.luogu.com.cn/problem/P9373)

首先根据样例解释中第二个的提示，我们可以考虑 $x=k$，这样如果 $y>x$，那么 $x\equiv k\pmod{y}$。换句话说，若 $x<y$ 并且 $x\equiv k\pmod{y}$，那么一定 $x=k$。

所以每次判断 $n-k>k$ 是否成立即可，若是则输出 $k,n-k$。

---

下面证明：若 $n\le2k$，则不存在非负整数 $x$、正整数 $y$ 使 $x+y=n,x\equiv k\pmod{y}$。

首先若 $x=k$ 则不满足 $y>x$，因此无法按照上面的输出。所以 $x>y$。

因为 $x>y$，所以 $x>\dfrac{n}{2},y<\dfrac{n}{2}$。因为 $k\ge\dfrac{n}{2}$，所以不存在**正整数** $y$ 使 $y+k<x$。

---

**代码：**

```
#include<bits/stdc++.h>
using namespace std;
long long n,k;//ll别忘了
int t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&n,&k);
		(k*2<n)?printf("%lld %lld\n",k,n-k):printf("-1\n");
	}
	return 0;
}
```


---

