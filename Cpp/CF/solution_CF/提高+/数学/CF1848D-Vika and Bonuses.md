# Vika and Bonuses

## 题目描述

A new bonus system has been introduced at Vika's favorite cosmetics store, "Golden Pear"!

The system works as follows: suppose a customer has $ b $ bonuses. Before paying for the purchase, the customer can choose one of two options:

- Get a discount equal to the current number of bonuses, while the bonuses are not deducted.
- Accumulate an additional $ x $ bonuses, where $ x $ is the last digit of the number $ b $ . As a result, the customer's account will have $ b+x $ bonuses.

For example, if a customer had $ 24 $ bonuses, he can either get a discount of $ 24 $ or accumulate an additional $ 4 $ bonuses, after which his account will have $ 28 $ bonuses.

At the moment, Vika has already accumulated $ s $ bonuses.

The girl knows that during the remaining time of the bonus system, she will make $ k $ more purchases at the "Golden Pear" store network.

After familiarizing herself with the rules of the bonus system, Vika became interested in the maximum total discount she can get.

Help the girl answer this question.

## 说明/提示

In the first test case, Vika can accumulate bonuses after the first and second purchases, after which she can get a discount of $ 4 $ .

In the second test case, Vika can get a discount of $ 11 $ three times, and the total discount will be $ 33 $ .

In the third example, regardless of Vika's actions, she will always get a total discount of $ 0 $ .

## 样例 #1

### 输入

```
6
1 3
11 3
0 179
5 1000000000
723252212 856168102
728598293 145725253```

### 输出

```
4
33
0
9999999990
1252047198518668448
106175170582793129```

# 题解

## 作者：_sunkuangzheng_ (赞：9)

**【题目分析】**

我们观察每一次增加操作后个位的变化情况：$0 \to 0,1 \to 2,2 \to 4,3 \to 6,4 \to 8,5 \to 0,6 \to 2,7 \to 4,8 \to 6,9 \to 8$。因此发现，在一次操作内个位数要么变成 $0$，否则就会在 $2,4,8,6$ 之间循环。当个位数为 $0$ 时，显然操作再多次也没有意义，直接输出 $s \times k$，个位为 $5$ 时也同理。

接下来讨论个位为偶数的情况。我们发现 $2 \to 4 \to 8 \to 6$ 是一轮循环，且这轮循环后 $s$ 会增加 $20$。因此我们设进行 $x$ 轮循环（特别注意 $x$ 的含义）后答案为 $y$，容易列出表达式：$y=(s + 20x)(k-4x)=-80x^2+(20k-4s)x + sk$。这显然是一个二次函数，且 $s,k$ 都是已知量。由初中知识知，二次函数顶点横坐标为 $x = -\dfrac{b}{2a} = \dfrac{5k-s}{40}$，但是这个值不一定是整数，所以我们要取 $\lfloor \dfrac{5k-s}{40} \rfloor$ 和 $\lceil \dfrac{5k-s}{40} \rceil$ 计算答案并取 $\max$。但是我们这样只能计算单个个位数的情况，因此我们要在计算答案以前，枚举个位数，再对答案取 $\max$。

代码实现有几处小细节注意：

1. 套用二次函数顶点公式时，注意 $x$ 的取值范围：因为 $k - 4x \ge 0$，所以 $0 \le x \le \lfloor \dfrac{k}{4} \rfloor$。
1. 时刻注意对 $ans$ 取 $\max$，不要错过最优解。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t,s,k;
int solve(int s,int k){  
    int ans = s * k;
    int x = max(min((5 * k - s) / 40,k / 4),0ll);ans = max(ans,-80*x*x+ (20*k-4*s)*x + s*k);
    x = min(x+1,k/4);ans = max(ans,-80*x*x+ (20*k-4*s)*x + s*k);
    return ans;
}
int calc(){
    cin >> s >> k;
    if(s % 10 == 0) return s * k;
    if(s % 10 == 5) return max(s*k,(s+5)*(k-1));
    int ans = s * k;
    if(s % 2) s += s % 10,k --;
    for(int i = 1;i <= 4;i ++){
        if(k <= 0) break;
        ans = max(ans,solve(s,k)),s += s % 10,k --;
    }
    return ans;
}
signed main(){
    cin >> t;
    while(t --) cout << calc() << endl;
    return 0;
}
```


---

## 作者：MaxBlazeResFire (赞：3)

我们先考虑 $s$ 的个位数为 $2$ 的情况。

容易发现，若我们钦定要使优惠自增 $t$ 次，消费 $k-t$ 次，那必然是先自增完后再消费，于是我们得到了最终的收益函数 $C=(k-t)(s+f(t))$.

经过推导我们发现

$\displaystyle f(t)=\begin{cases}20p,t=4p\\
20p+2,t=4p+1\\
20p+6,t=4p+2\\
20p+14,t=4p+3\\
\end{cases}$

我们分四种情况讨论，对于每种情况，我们找出 $k(s+f(t))-st$ 取最大值时 $p$ 的取值。式子展开后都形如有关 $p$ 的一元二次函数的形式。

第一种情况，函数形如 $-80p^2+(20k-4s)p$，极值点 $\displaystyle p=\frac{5k-s}{40}$;

第二种情况，函数形如 $-80p^2+(20k-4s-28)p+R$，极值点 $\displaystyle p=\frac{5k-s-7}{40}$;

第三种情况，函数形如 $-80p^2+(20k-4s-64)p+R$，极值点 $\displaystyle p=\frac{5k-s-16}{40}$;

第四种情况，函数形如 $-80p^2+(20k-4s-116)p+R$，极值点 $\displaystyle p=\frac{5k-s-29}{40}$;

求出极值点后判断 $p$ 对应的 $t$ 是否满足 $t\in[0,k]$. 若不满足则利用二次函数极值点两侧的单调性进行微调即可。

将这四个极值代入原式求出最大值就是答案。复杂度 $O(1)$.

那么个位数不是 $2$ 的情况呢？

如果个位为 $5$ 或者 $0$，那么答案非常简单。

如果个位为其它数，一定能在常数次操作内将其转变为个位数为 $2$ 的形式。将过程中的最大值与上面求得的答案取最大值就好。

因为数据范围较大，于是可以酌情使用 $\rm int128$.

复杂度 $O(T)$.

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int __int128

inline int read(){
	int x = 0; char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();
	while( ch >= '0' && ch <= '9' ) x = x * 10 + ch - 48,ch = getchar();
	return x;
}

void write( int x ){
	if( x >= 10 ) write( x / 10 );
	putchar( x % 10 + 48 );
}

inline int min( int a , int b ){ return a - b > 0 ? b : a; }
inline int max( int a , int b ){ return a - b > 0 ? a : b; }

int k,a;

inline int calc( int K , int A ){
	int c1,c2,c3,c4;
	
	c1 = (int)(long long)( 1.0 * ( 5 * K - A ) / 40.0 + 0.5 );
	if( 4 * c1 > K ) c1 = K / 4 * 4;
	else if( c1 < 0 ) c1 = 0;
	else c1 = c1 * 4;
	
	c2 = (int)(long long)( 1.0 * ( 5 * K - A - 7 ) / 40.0 + 0.5 );
	if( 4 * c2 + 1 > K ) c2 = ( K - 1 ) / 4 * 4 + 1;
	else if( c2 < 0 ) c2 = min( K , 1ll );
	else c2 = c2 * 4 + 1;
	
	c3 = (int)(long long)( 1.0 * ( 5 * K - A - 16 ) / 40.0 + 0.5 );
	if( 4 * c3 + 2 > K ) c3 = ( K - 2 ) / 4 * 4 + 2;
	else if( c3 < 0 ) c3 = min( K , 2ll );
	else c3 = c3 * 4 + 2;
	
	c4 = (int)(long long)( 1.0 * ( 5 * K - A - 29 ) / 40.0 + 0.5 );
	if( 4 * c4 + 3 > K ) c4 = ( K - 3 ) / 4 * 4 + 3;
	else if( c4 < 0 ) c4 = min( K , 3ll );
	else c4 = c4 * 4 + 3;
	
	c1 = ( K - c1 ) * ( a + 5 * c1 );
	c2 = ( K - c2 ) * ( a + 5 * c2 - 3 );
	c3 = ( K - c3 ) * ( a + 5 * c3 - 4 );
	c4 = ( K - c4 ) * ( a + 5 * c4 - 1 );
	
	return max( max( c1 , c2 ) , max( c3 , c4 ) );
}

inline void solve(){
	a = read(),k = read();
	if( a % 10 == 0 ){ write( a * k ); puts(""); return; }
	if( a % 10 == 5 ){ write( max( a * k , ( a + 5 ) * ( k - 1 ) ) ); puts(""); return; }
	int Ans = 0;
	while( k && a % 10 != 2 ){
		Ans = max( Ans , k * a );
		a += a % 10,k --;
	}
	if( !k ){ write( Ans ); puts(""); return; }
	Ans = max( Ans , calc( k , a ));
	write( Ans ); puts("");
}

signed main(){
	int testcase; testcase = read();
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：_HCl_ (赞：1)

为什么感觉 C 题比 D 题还难想到啊。~~是我太菜了~~。

# CF1848D 题解

**题意简述**

给定一个数 $s$，每次可以进行两种操作：

- 将 $s$ 加上其个位数字。
- 将答案加上 $s$。

一共进行 $k$ 次操作，询问答案的最大值。

**思路引导**

首先，不难发现，如果不进行第一种操作，那么答案就是 $s\cdot k$。

再来观察第一种操作，我们可以根据 $s$ 的个位数，分类操作后的结果：

1. 个位是 $0$ 的，操作后不变。
1. 个位是 $5$ 的，操作后变成 $0$。
1. 个位是 $2,4,6,8$ 的，操作会进入 $2\rightarrow 4\rightarrow 8\rightarrow 6$ 的循环。
1. 个位是 $1,3,5,7,9$ 的，操作后会变成 $2,4,6,8$ 和 $0$ 的情况。

对于第一种情况，我们不做处理，$s\cdot k$ 已经是最优。

对于第二种情况，我们可以看看操作一次的结果 $(s+s\bmod 10)(k-1)$ 是否更优。

对于第三种情况，我们重点讨论。

假设我们进行 $p$ 次操作，我们将 $p$ 拆成 $x$ 个循环和 $i$ 次剩下的操作。

由于 $i\leq 4$ 所以可以枚举去做。接下来考虑怎么处理 $x$。不难发现，进行 $x$ 次循环后，答案为 $(s+20x)(k-4x)$。这是一个二次函数，我们就可以求出它的最大值。

对于第四种情况，直接操作一次，转换成第三种去做。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int s,k;
int calc(int s,int k){
	int x=(5*k-s)/40;
	x=min(x,k/4);//注意定义域 
	int ret=s*k;
	if(x>0)ret=max(ret,(s+20*x)*(k-4*x));
	x=min(x+1,k/4);//这里要注意，必须考虑+1的情况，因为离散意义下的最大值分布在连续意义下的最大值的左右两侧 
	if(x>0)ret=max(ret,(s+20*x)*(k-4*x));
	return ret;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		scanf("%lld%lld",&s,&k);
		int ans=s*k;
		if(s%10==5)
			ans=max(ans,(s+5)*(k-1));//个位是 10 的情况 
		else if(s%10>0){
			if(s%2==1)s+=s%10,k--;// 奇数的情况，转换成偶数 
			for(int i=1;i<=4;++i){
				if(k)ans=max(ans,calc(s,k));//计算最大值 
				s+=s%10,k--;//进行独立操作 
			}
		}
		cout<<ans<<"\n";
	}
}
```

---

## 作者：huangrenheluogu (赞：1)

感觉这个 D 好水啊，这有 2200？

显然可以发现一个循环，个位数：$2\rightarrow4\rightarrow8\rightarrow6\rightarrow2$。

而 $1,3,7,9$ 都是会进入这个循环的。

所以，特判 $5,0$ 的情况。

- 个位是 $0$ 的时候，显然直接算贡献，答案就是 $ks$。

- 个位是 $5$ 的时候，进行一次自增操作之后个位为 $0$，所以答案就是 $\max\{ks,(k-1)(s+5)\}$。

其他情况都可以进入循环，每次判断一下 $ks$，更新最大值。

下面看一下这个循环的部分，当我们进入循环的时候，我们可以判断最后一个数字还是 $s$ 个位数的时候求最大值。（这时需要 $s$ 个位是偶数）。

记多了 $x$ 组。

贡献就是 $(s+20x)(k-4x)$。

剩下就是二次函数了，记为 $f(x)$。

容易得到 $f(x)=-80x^2+(20k-4s)+8k$，是一个开口向下的二次函数。

对称轴 $x=\dfrac{20k-4s}{160}$。

因为要求 $x$ 是整数，那么就是 $\left\lceil x\right\rceil$ 和 $\left\lfloor x\right\rfloor$ 算一下，取 $\max$。

如果遇到循环节，说明算过了，就退出好了。

[code](https://codeforces.com/contest/1848/submission/239455637)

---

## 作者：Reunite (赞：1)

首先显然，一定是**先连续自增**（也可以不增）再**一直累积**，这是显然的。

当 $n\equiv5 \pmod{10}$ 或 $n\equiv0 \pmod{10}$ 时，简单分讨。

剩下的情况，稍微算算，个位数将会极快第进入 $2,4,8,6,2,4,8,6$ 的循环。为了方便，当 $k\le20$ 的时候我们直接暴力，剩下的暴力跳 $n$，使其达到 $n\equiv2 \pmod{10}$ 的一般情况。

每次循环后，$n$ 会增加 $20$ 这一定值，分讨，设循环了整 $i$ 次，则有：
 $$ans=(n+20i)(k-4i)$$
展开
$$ans=-80i^2+(20k-4n)i+nk$$

上式是一个关于 $i$ 的开口向下的抛物线解析式，直接取其对称轴 $i=\frac{20k-4n}{160}$，注意到除法可能有误差，再上下浮动算几个即可。

这样我们就算出了所有 $n\equiv2 \pmod{10}$ 的最大值，再让 $n$ 自增一次算 $n\equiv4 \pmod{10}$ 的情况，然后是 $8,6$。这样就做完了。

----
### Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

int t;
ll s,k;

inline void in(ll &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline ll change(ll n,ll k){
	while(k--){
		n+=n%10;
		if(n%10==2) break;
	}
	ll ss=20ll*(k/4);
	k%=4;
	if(k==1) ss+=2;
	if(k==2) ss+=6;
	if(k==3) ss+=14;
	return n+ss;
}

int main(){
	scanf("%d",&t);
	while(t--){
		in(s),in(k);
		if(s%10==0){
			printf("%lld\n",s*k);
			continue;
		}
		if(s%10==5){
			printf("%lld\n",max(s*k,(s+5)*(k-1)));
			continue;
		}
		if(k<=50){
			ll ans=0;
			for(int i=0;i<=k;i++)
				ans=max(ans,change(s,i)*(k-i));
			printf("%lld\n",ans);
			continue;
		}
		ll ans=0;
		ll tt=0,n=s;
		while(n%10!=2){
			ans=max(ans,n*k);
			n+=n%10;
			k--;
		}
		ans=max(ans,n*k);
		ll pos=(20*k-4*n)/160;
		for(ll i=max(0ll,pos-1);i<=min(k,pos+1);i++)
			ans=max(ans,(n+i*20ll)*(k-4ll*i));
		n+=n%10;
		k--;
		pos=(20*k-4*n)/160;
		for(ll i=max(0ll,pos-1);i<=min(k,pos+1);i++)
			ans=max(ans,(n+i*20ll)*(k-4ll*i));
		n+=n%10;
		k--;
		pos=(20*k-4*n)/160;
		for(ll i=max(0ll,pos-1);i<=min(k,pos+1);i++)
			ans=max(ans,(n+i*20ll)*(k-4ll*i));
		n+=n%10;
		k--;
		pos=(20*k-4*n)/160;
		for(ll i=max(0ll,pos-1);i<=min(k,pos+1);i++)
			ans=max(ans,(n+i*20ll)*(k-4ll*i));
		n+=n%10;
		k--;
		printf("%lld\n",ans);
	}
	
	return 0;
} 

```

---

## 作者：引领天下 (赞：0)

首先，只考虑个位，那么不断自己加自己的个位的操作其实是等同于 $\times2$ 的。

而根据熟悉的小学知识容易知道，一个数不断 $\times2$ 的时候其个位是每 $4$ 次一循环的。

那么我们就可以直接在 $O(1)$ 的复杂度内得到 $s$ 连续进行 $t$ 次操作 $2$ 后的结果。

于是剩下的就简单了，变成尝试对所有不同的 $t$ 找出 $(k-t)\times(s+q)$，其中 $q$ 是 $s$ 进行 $t$ 次操作 $2$ 后总共加的数。

赛时根本就没注意到这玩意是分段的二次函数，所以直接写了一个三分，但是怎么也过不去，赛后发现处理 $s$ 进行 $t$ 次操作 $2$ 的部分假了，寄。

假的原因其实很简单，只有个位是偶数的情况才会直接进入循环，奇数会在乘了一次 $2$ 之后才进入循环。另外，对于个位是 $5$ 或 $0$ 的情况要单独判断。

修好了这个锅之后我的三分还是寄了，于是推测并非单峰。（事实上是分段的二次函数，确实不单峰）

最后写了个退火，调参调了半天调过去了。

![](https://cdn.luogu.com.cn/upload/image_hosting/5oybywqg.png)

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,s,k;
const double eps=1e-3;
inline int work(int x,int t){
    x%=10;
    int q=x;
    t--;(x*=2)%=10;int z=t/4;//为了将奇数和偶数的情况统一，这里选择第一次乘二单独处理。
    switch(t%4){
        case 0:return q+x*z+(x*2)%10*z+(x*4)%10*z+(x*8)%10*z;
        case 1:return q+x*(z+1)+(x*2)%10*z+(x*4)%10*z+(x*8)%10*z;
        case 2:return q+x*(z+1)+(x*2)%10*(z+1)+(x*4)%10*z+(x*8)%10*z;
        case 3:return q+x*(z+1)+(x*2)%10*(z+1)+(x*4)%10*(z+1)+(x*8)%10*z;
        default:return 0;
    }
}
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>s>>k;
        if(s%10==0){cout<<k*s<<endl;continue;}//如果 s 的个位是 0 那么无论多少次操作 2 都不会有任何变化，显然只进行操作 1。
        if(s%10==5){cout<<max(k*s,(k-1)*(s+5))<<endl;continue;}//如果 s 的个位是 5，进行一次操作 2 之后就会变成 0，所以最多进行一次操作 2，直接判断。
        double T=20000;//退火！
        int asx=k/2;
        while(T>eps){
            int x=asx+(rand()*2-RAND_MAX)*T;
            T*=0.981;
            x=max(0ll,x);x=min(x,k);
            int qxe=(k-x)*(s+work(s,x))-(k-asx)*(s+work(s,asx));
            if(qxe>0){asx=x;continue;}
        }
        int ans=0;
        for(int i=max(0ll,asx-100);i<=min(k,asx+100);i++)ans=max(ans,(k-i)*(s+work(s,i)));//退火的精度不够，我们选择加上左右枚举来保证答案一定出现。
        cout<<ans<<endl;
    }
    return 0;
}
```

---

