# 「EZEC-11」Sequence

## 题目描述

已知数列 $f$ 满足 $f_n=a_nf_{n-1}+b_n\ (n\ge 1)$。

问是否存在非负整数 $f_0$，使得 $\forall 1\le i\le k$，$f_i$ 为**质数** $p_i$ 的倍数。

## 说明/提示

**【样例 1 解释】**

对于第一组测试数据，一个可行的解为 $f_0=1$，此时 $f_1=3,f_2=5,f_3=7$。

对于第二组测试数据，没有满足条件的 $f_0$。

**【数据规模与约定】**

**本题采用捆绑测试。**

-  Subtask 1（10 points）：$k=1$。
-  Subtask 2（20 points）：$k\le 2$。
-  Subtask 3（20 points）：$k\le 5$，$p_i\le 20$。
-  Subtask 4（50 points）：无特殊限制。

对于 $100\%$ 的数据，$1\le T\le 10$，$1\le k\le 10^3$，$0\le a_i,b_i\le 10^9$，$2\le p_i\le 10^9$，**$p$ 为质数**。

## 样例 #1

### 输入

```
2
3
1 1 1
2 2 2
3 5 7
3
1 1 1
2 2 2
3 3 3```

### 输出

```
Yes
No```

# 题解

## 作者：Sky_Maths (赞：10)

Update：2022/7/21 修改了两个错误

题目传送门：[P8178 「EZEC-11」Sequence](https://www.luogu.com.cn/problem/P8178)
## 【题意】
- 已知数列 $f$ 满足 $f_i=a_i\cdot f_{i-1}+b_i(i\ge1)$ ，

- 问是否存在非负整数 $f_0$ ，使得 $f_i$ 为 **质数** $p_i$（ $1\le i \le n$ ）的倍数。

- **本题有多组测试数据**，若存在满足条件的 $f_0$ 则输出```Yes```，否则输出```No```。

- 对于 $100\%$ 的数据，$1\le T\le10$ ， $1\le n\le10^3$ ， $0\le a_i,b_i\le 10^9$ ， $2\le p_i\le 10^9$ ， $p$ 为**质数**。

## 【分析】
- 前置条件：看懂题目，已经会打暴力。
- 最先想到的肯定是枚举 $f_0$ ，若有满足的则输出```Yes```,否则输出```No```，但这样的时间复杂度为$O ( \max(f_0,lcm(p_{1,2,\ldots,n}))\cdot n^2 )$。
- 代码类似这样:
```cpp
	while(f[0]<lcm(all:p[1-n]))
	{
		int flag=0;
		for(int i=1;i<=n;i++)
		{
			f[i]=a[i]*f[i-1]+b[i];
			if(f[i]%p[i])
			{
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			printf("%d",f[0]);
		}
		++f[0];
	}
```
- 看到 $n^2\le10^6$ 和输出```Yes```或```No```想到这是一道~~数学~~结论题，考虑去掉 $\max(f_0,lcm(p_{1,2,\ldots,n}))$ 。
- 想到可以将 $f_i$ 用 $c_i \cdot f_0+d_i$ 表示，改变 $f_0$ 后可以用$O(1)$的时间复杂度直接求出 $f_i$ 。
- 先不考虑 $p_i$ ，看一下数组$c$与数组 $d$ 的规律：

| $i$ | $c$ | $d$ |
| :-----------: | :-----------: | :-----------: |
| 0 | 0 | 0 |
| 1 | $a_1$ | $b_1$ |
| 2 | $a_1 \cdot a_2$ | $(b_1) \cdot a_2+b_2$ 
| 3 | $a_1 \cdot a_2 \cdot a_3$ | $(b_1 \cdot a_1+b_2) \cdot a_3+b_3$ |
| 4 | $a_1 \cdot a_2 \cdot a_3 \cdot a_4$ | $((b_1 \cdot a_1+b_2) \cdot a_3+b_3) \cdot a_4+b_4$ |

- 眼尖的同学应该已经发现了 $c,d$ 数组的规律：
- $c_i=c_{i-1}\cdot a_i$。
- $d_i=d_{i-1}\cdot a_i + b_i$。
- 于是代码变成了这样：
```cpp
	c[0]=1;
	for(int i=1; i<=n; i++) {
		c[i]=c[i]*a[j];
		d[i]=d[i]*a[j]+b[j];
	}
```
- 很短吧~
- 但是! $c_i,d_i$ 可能变得很大很大，所以需要当场 $\bmod p_i$。
- $c_i \cdot f_0+d_i\equiv c_i\bmod p_i\cdot f_0+d_i\bmod p_i(\bmod p_i)$
- 考虑 $p_i$，$f_i$ 为 $p_i$ 的倍数,即 $f_i\bmod p_i=0$ ，使 $c_i=c_i \bmod p_i$ ， $d_i=d_i \bmod p_i$。
- 但是， $p_i$ 不一定相同！所以针对每个$p_i$用一个$O( n )$的循环求出 $c_i,d_i$ 。
- 于是用$O( n^2 )$的预处理将这题转变成了另一个问题。

### 【简要题意】
给出 $n$ 个 $c_i$ , $d_i$ , $p_i$ ,求是否有满足所有公式 $c_i\cdot x+d_i\equiv 0(\bmod p_i)$ 的通项 $x$ 。
- ~~很容易~~想到应该将 $x$ 的系数化为1。
- 但是！若 $c_i=0$ ，就无法将 $x$ 的系数化为1，但是！我们可以直接判断是否存在解了！
- 考虑如何判断（~~这个应该比较简单~~），直接判断 $d_i\bmod p_i$ 是否等于0，若不等于，则可以判断绝对是不存在解的，若等于则可以不考虑 $i$ ，因为无论 $x$ 等于几都必定有解。
- 那么若 $c_i$ 不等于0，则将 $d_i$ 除上一个 $c_i$ ，但我们已将 $c_i,d_i\bmod p_i$ ，那么考虑求 $p_i$ 的[逆](https://www.luogu.com.cn/blog/zyxxs/post-xiao-yi-jiang-tan-qian-tan-sheng-fa-ni-yuan)[元](https://www.luogu.com.cn/blog/1239004072Angel/post-shuo-xue-sheng-fa-ni-yuan)为 $px_i$ ，这里就不做赘述。
- 将 $d_i=d_i\cdot px_i\bmod p_i$
- 于是用$O( n\log n )$的预处理又将这题转变成了另一个问题。

#### 【简要题意】
给出 $n$ 个 $d_i$ , $p_i$ ,求是否有满足所有公式 $(x+d_i)\bmod p_i=0(d_i\ge 0)$ 的通项 $x$。
#### 【分析】
- 公式 $(x+d_i)\bmod p_i=0$ 即 $x+d_i$ 为 $p_i$ 的倍数。
- 所以化为 $x=-d_i=f_i$，
- 令 $f(i)=(i\bmod p_i+p_i)\bmod p_i$ ，
- 使 $f_i=f(d_i)$ ，
- 而保证 $p_i$ 为质数，若 $p_i$ 不同则一定有解，若 $p_i=p_j$ 且 $f_i$ 不等于 $f_j$ ,则必定无解,否则有解。
### 【总结】
- 以上全部判断完后若还全部满足则可以输出```Yes```了。
### 【代码】
```cpp
#include<cstdio>
#include<unordered_map>
#define N 1009
#define int long long
using namespace std;
unordered_map<int,int>ma;
int t,n,flag;
int a[N],b[N],c[N],d[N],p[N];
int exgcd(int a, int b, int &x, int &y) { 
	if (!b) {
		x=1;y=0;
		return a;
	}
	int q=a/b,r=a%b,ex;
	ex=exgcd(b,r,y,x);
	y-=q*x;
	return ex;
}
main() {
	scanf("%lld",&t);
	while(t--) {
		flag=0;
		scanf("%lld",&n);
		for(int i=1; i<=n; i++)
			scanf("%lld",&a[i]);
		for(int i=1; i<=n; i++)
			scanf("%lld",&b[i]);
		for(int i=1; i<=n; i++)
			scanf("%lld",&p[i]);
		for(int i=1; i<=n; i++) {
			c[i]=1;
			d[i]=0;
			for(int j=1; j<=i; j++) {
				c[i]=c[i]*a[j]%p[i];
				d[i]=(d[i]*a[j]+b[j])%p[i];
			}
/*求c[i]与d[i]，因为p[i]不同，所以针对每个p[i]都1~i枚举一遍
虽然时间复杂度变为了O(n^2)，但没有超时~~~
而且不需要打高精了*/ 
			if(!c[i]&&d[i]) {
				puts("No");
				flag=1;
				break;
			}
			if(!c[i]) {
				p[i]=1e9;
//用一个非质数来代替p[i]防止与真正的p[i]重复
				d[i]=1e9;
				continue;
			}
			int t;
			exgcd(c[i],p[i],c[i],t);
			d[i]=(((-d[i])%p[i]+p[i])%p[i])*c[i]%p[i];
			d[i]=(d[i]+p[i])%p[i];
//将x的系数化为1 
		}
		if(!flag) {
			for(int i=1; i<=n; i++) {
				if(ma[p[i]]&&ma[p[i]]!=d[i]+1) {
					puts("No");
					break;
				} else {
					ma[p[i]]=d[i]+1;
//+1是为了防止d[i]为0误判为没有存过
				}
				if(i==n) {
					puts("Yes");
				}
			}
		}
		ma.clear();
	}
	return 0;
}
```
- 返回题目：[P8178 「EZEC-11」Sequence](https://www.luogu.com.cn/problem/P8178)

---

## 作者：BqtMtsZDnlpsT (赞：3)

$\large\text{solution}$

$f_n=a_nf_{n-1}+b_n$ 其实就是：

$f_1=a_1f_0+b_1$

$f_2=a_1a_2f_0+b_1a_2+b_2$

$f_3=a_1a_2a_3f_0+b_1a_2a_3+b_2a_3+b_3$

可以发现 $f_0$ 的系数，和后面的都是常数，考虑把题面的条件变成这样：

$\begin{cases}
A_1f_0+B_1\equiv 0\pmod {p_1}\\
A_2f_0+B_2\equiv 0\pmod {p_2}\\
\ldots\\
A_kf_0+B_k\equiv 0\pmod {p_k}
\end{cases}$

其中 $A_i=\prod\limits_{j=1}^ia_j $，$B_i=\sum\limits_{j=1}^ib_j\prod\limits_{l=j+1}^i a_l$。

注意到 $k$ 比较小，而且 $A_i,B_i$ 都可以直接对 $p_i$ 取模，所以可以对于每个 $p_i$ 直接维护 $A_i,B_i$。

具体的：

$A_i=\prod\limits_{j=1}^ia_j=a_i\prod\limits_{j=1}^{i-1}a_j=a_iA_{i-1}$

$B_i=\sum\limits_{j=1}^ib_j\prod\limits_{l=j+1}^i a_l=\sum\limits_{j=1}^{i-1}b_ja_i\prod\limits_{l=j+1}^{i-1} a_l+b_i=a_iB_{i-1}+b_i$

算出系数之后，让我们考虑在什么条件下方程组无解：
1. 发现这些方程都是在模意义下的一元一次方程，在模意义下都只有一个解。

	当两模数不同时，他们必定互质，根据中国剩余定理的构造方法定能构造出解。
    
    所以只考虑模数相同时，若有两个模数相同的一元一次方程解出来的解模意义下不同，那么无解。

1. 一个注意点：$0$ 没有逆元，当$A_i=0,B_i\neq0$ 时显然无解，当 $A_i=0,B_i=0$ 时，有无数解（这时应该直接跳过这个方程）

代码：

```cpp
int n,a[1005],b[1005],p[1005],q[1005],s1[1005],s2[1005];
int qp(int a,int m,int p){//快速幂
	int ans=1;a%=p;
	if(!a)return 0;
	while(m){
		if(m&1)ans=1ll*ans*a%p;
		a=1ll*a*a%p;m>>=1;
	}
	return ans;
}
vector<int>P[1005];
signed main(){
	for(int T=read();T;T--){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++)b[i]=read();
		for(int i=1;i<=n;i++)p[i]=q[i]=read();//读入
		sort(q+1,q+1+n);int l=unique(q+1,q+1+n)-q-1;
		//把所有质数离散化下来，方便统计模数相同的方程

		for(int i=1;i<=l;i++)s1[i]=a[1]%q[i],s2[i]=b[1]%q[i];
		//第一个方程（代码中 s1[i] 表示上文 A_i,s2[i] 表示 B_i）

		bool fl=0;
		for(int i=1;i<=n;i++){
			int pp=lower_bound(q+1,q+1+l,p[i])-q;
			//pp 是当前质数离散化之后的编号
			if(!s1[pp]&&s2[pp])fl=1;//无解情况 2
			if(!s2[pp]&&!s1[pp]){//无数解就跳过
				for(int j=1;j<=l;j++)s1[j]=1ll*s1[j]*a[i+1]%q[j],s2[j]=(1ll*s2[j]*a[i+1]+b[i+1])%q[j];
				//continue 前别忘了更新，赛时因为这个 wa 了一发
				continue;
			}
			P[pp].push_back(1ll*((p[i]-s2[pp])%p[i])*qp(s1[pp],p[i]-2,p[i])%p[i]);
			//这里是直接把方程变成了 f0 恒等于 t(mod p)
			//t 是通过移项来得到 (t=-B_i/A_i)，p[i]-s2[pp] 就是 -B_i 在模 p_i 意义下的值,乘的就是 A_i 模 p_i 意义下的逆元

			for(int j=1;j<=l;j++)s1[j]=1ll*s1[j]*a[i+1]%q[j],s2[j]=(1ll*s2[j]*a[i+1]+b[i+1])%q[j];//更新
		}
		for(int i=1;i<=l;i++){
			for(int j=1;j<(int)P[i].size();j++)
				if(P[i][j]!=P[i][j-1])fl=1;
				//如果模同一个质数得到的解不同，那就无解
			P[i].clear();
		}
		puts(!fl?"Yes":"No");//输出
	}
}
```

---

## 作者：培淇2021 (赞：2)

~~咕咕咕~~

大家好，由于我是暴力选手，我就用了 $O(Tk^2\log 10^9)$ 的时间复杂度过了这道题。

前置知识：同余方程组。

首先看到这道题，一般都会想起递推数列，但是一般递推数列根据题目可以改成 $f_n=af_{n-1}+b$ 的形式，但是这道题每一项对应的不一样，放弃这种想法。

那么我们发现，既然 $k$ 的范围这么小，那么我们就把每一项都枚举出来。

可是？可是我们第一项 是 个 未 知 数，所以~~也放弃这种想法~~我们思考怎么把第一项的系数和常数，放到最终的方程中。

这步操作怎么做呢？一般来讲，我会先想一重循环，类似递推怎么做。

结果？结果我看到了数据范围：$10^9$。

这个数据范围，系数的临界最大值是 $(10^9)^{1000}=10^{9000}$，当然你写个高精也是没问题的，只不过常数的干扰会使得程序减慢，很大程度上会超时。

所以？所以我们要使用~~像这三段一样的对仗~~$k^2$ 算法，对每一个数都算一遍。

我们发现最终是这样这样的倍数，所以我们直接对每一个取模就行了。

然后？然后递推式就出来了，这里的 $u,v$ 表示 $f_i=uf_0+v$：

$u=u\times a_i$

$v=v\times a_i+b_i$

这部分代码：

```cpp
	for(int i=1;i<=n;i++)
        {
            int u=1,v=0;
            for(int j=1;j<=i;j++)
            {
                u=u*a[j]%p[i];
                v=(v*a[j]%p[i]+b[j])%p[i];
            }
            x[i]=u,y[i]=(p[i]-v)%p[i];//x=u,y=v
        }
```

注意取模，我们发现后面的任务等价于判断一个线性同余方程组是否有解。

所以怎么判断？我学同余方程组时会学一个比较奇怪的结论，现在，我找到了[它](http://www.doc88.com/p-5901282494757.html)。

根据这个文章里的方法，我们需要判断单个同余方程有没有解，再判断两两之间的关系。

于是，我们的这部分代码就能写出来了。

```cpp
	for(int i=1;i<=n;i++)
                for(int j=1;j<i;j++)
                        if((y[i]*x[j]-y[j]*x[i])%gcd(p[i]*x[j],p[j]*x[i])!=0)
                        {
                            flag=true;
                            break;
                        }
```

大家肯定发现，我没有写判断单个有没有解的代码，因为经过我的测试，这段代码删了也没有影响，优化常数把它删了。

经过这样的调整，你成功得出了一个~~AC~~ $50$ 分代码。

```cpp
#include<bits/stdc++.h>
#define int long long//开 long long
using namespace std;
int t,n,a[1005],b[1005],p[1005],x[1005],y[1005];
signed main()
{
	cin>>t;
    while(t--)
    {
        cin>>n;//这里表示 k
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++)
            cin>>b[i];
        for(int i=1;i<=n;i++)
            cin>>p[i];
        for(int i=1;i<=n;i++)
        {
            int u=1,v=0;
            for(int j=1;j<=i;j++)
            {
                u=u*a[j]%p[i];
                v=(v*a[j]%p[i]+b[j])%p[i];
            }
            x[i]=u,y[i]=(p[i]-v)%p[i];
        }
        bool flag=false;
        for(int i=1;i<=n;i++)
            if(y[i]%__gcd(x[i],p[i])!=0||(x[i]==0&&y[i]!=0))//这里是特判，后来删了
            {
                flag=true;
                break;
            }
        if(flag)
        {
            cout<<"No"<<endl;
            continue;
        }
        for(int i=1;i<=n;i++)
        {
            if(x[i]!=0)//否则会 re，gcd(0,0)=0
            {
                for(int j=1;j<=n;j++)
                {
                    if(x[j]!=0)
                    {
                        if((y[i]*x[j]-y[j]*x[i])%__gcd(p[i]*x[j],p[j]*x[i])!=0)
                        {
                            flag=true;
                            break;
                        }
                    }
                }
            }
        }
        if(flag)
            cout<<"No"<<endl;
        else
            cout<<"Yes"<<endl;
    }
	return 0;
}
```

然后你就需要调整一点点细节：

首先，不要 `#define int long long`，用 `1ll*` 代替。

然后是细节的卡常：

1. `ios::sync_with_stdio(false);cin.tie(0);` 也是很有用的。
2. 全加上 `register`，玄学优化，在 `C++` 语言里好用。
3. 运行 `C++20`。
4. `x[i]==0&&y[i]!=0` 的特判不用单独加，单个方程特判可以省略。
5. `44` 行处应该改成 `j<i`，常数 `/2`。
6. 没 啦

最后，你得到了一个最高点运行时间在 `953ms`，春色满园关不住，没有红杏出墙来的代码，而且时间 $O(Tk^2\log)$。

我不清楚有没有这样写的（（（

upd：已经交了。

---

## 作者：Jairon314 (赞：2)

> [题目链接](https://www.luogu.com.cn/problem/P8178)

$$ Solution $$

------------

由于本人太菜了, 又晚了 2h 才开题, 比赛的时候代码写的很乱, 请见谅。由于瞎写写就过了不知道有没有假。

首先，我们考虑把 $f_0$ 看作 $x$ , 这样我们就可以递推得到 $n$ 个同余方程。第 $i$ 个同余方程的系数 $g[i].k=g[i-1].k \times a[i]$ , 常数 $g[i].b=g[i-1].b \times a[i]+b[i]$

$O(k^2)$ 考虑每个同余方程 $\pmod {p_i}$ 意义下的系数与常数, 即 $g[i].k \times x +g[i].b \equiv 0 \pmod {p_i} $, 通过数论的知识我们可以通过是否 $\gcd(g[i].k,p_i)|g[i].b$ 来判断该方程有没有解。

如果上面的过程进行完了就结束了吗？不是的。题目中说 $p_i$ 都为质数，却没有说 $p_i$ 两两互质。根据中国剩余定理，我们可以判断对于所有的 $i \ne j, \gcd(p_i,p_j) \ne 1$ , 是否有第 $i$ 个方程和第 $j$ 个方程等价。如果不等价即为无解。

代码如下：

```cpp
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#include <map>
using namespace std;

#define int long long
#define lint long long

/***** Fast_IO *****/

using vii = vector<int> ;
using pii = pair<int,int> ;

namespace IO{
	char buf[(1<<21)],*p1=buf,*p2=buf,buf1[(1<<21)]; int _=0;

	#define gc getchar
	#define pc putchar

	template<class I>
	inline I read(I &x){
		x=0; I f=1; char c=gc(); if(c==EOF){ return -1; }
		while(c<'0'||c>'9'){ if(c=='-'){ f=f*(-1); } c=gc(); }
		while(c>='0'&&c<='9'){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
		return x=x*f;
	}

	template<typename I,typename ...Args>
	inline void read(I &a, Args &...args){
		read(a),read(args...);
	}

	template<class I>
	inline void write(I x){
		if(x==0){ pc('0'); return; }
		I tmp=x>0?x:(-x),cnt=0;
		if(x<0){ pc('-'); }
		while(tmp){ buf[cnt++]=(tmp%10)+'0'; tmp/=10; }
		while(cnt){ pc(buf[--cnt]); }
		return;
	}

	template<class I>
	inline void chmax(I &x,I y){ return x=max(x,y),void(); }

	template<class I>
	inline void chmin(I &x,I y){ return x=min(x,y),void(); }
	
	template<int a,class I>
	inline int in(I x,I y){ return a>x&&a<y; }

	#define out(x) write(x),pc(' ')
	#define outn(x) write(x),pc('\n')
	#define assi() pc('\t')
	#define FOR(i,a,b) for(int i(a);i<=(b);++i)
	#define ROF(i,a,b) for(int i(a);i>=(b);--i)
	#define FORs(i,a,b,s) for(int i(a);i<=(b);i+=(s))
	#define ROFs(i,a,b,s) for(int i(a);i>=(b);i-=(s))
	#define next(i,now) for(int i(link[now]);i;i=edge[i].nexty)
	#define umap unordered_map 
	#define each(i,v) for(auto &i:v)
	#define all(v) v.begin(),v.end()
	#define sqr(k) ((k)*(k))
	#define inf 0x3f3f3f3f
	#define pb push_back
	#define mp make_pair
	#define DB double
	#define fir first
	#define sec second
}using namespace IO;

/***** Fast_IO *****/

#define maxn 1000010
#define SIZE 5010

int T,k;
int a[maxn];
int b[maxn];
int p[maxn];

struct Func{
	int k,b;
 
	Func(){}
	Func(int k_,int b_):k(k_),b(b_){}
	Func operator +(Func p){ k+=p.k,b+=p.b; return (*this); }
	Func operator *(int p){ k*=p,b*=p; return (*this); }
	int get_val(int x){ return k*x+b; }
}g[maxn];

int gcd(int a,int b){ return b?gcd(b,a%b):a; }

int exgcd(int a,int b,int &x,int &y){
	if(b==0){x=1,y=0;return a;}
	int gc=exgcd(b,a%b,x,y);
	int res=x;
	x=y;
	y=res-(a/b)*y;
	return gc;
}

int Array[maxn],Brray[maxn];

int qpow(int a,int b,int mod){
	int res=1,tmp=a;
	while(b){ if(b&1){ res=(1ll*res*tmp)%mod; } tmp=(1ll*tmp*tmp)%mod; b>>=1; }
	return res;
}

int inv(int k,int mod){ return qpow(k,mod-2,mod); }

#include <cassert>

signed main(){
	read(T);
	while(T--){
		bool flag=true;
		bool flag2=true;
		read(k); g[0].k=1;
		FOR(i,1,k){ g[i].k=g[i].b=0; }
		FOR(i,1,k){ read(a[i]); g[i].k=g[i-1].k*a[i]; }
		FOR(i,1,k){ read(b[i]); g[i].b=g[i-1].b*a[i]+b[i]; }
		FOR(i,1,k){ read(p[i]); }
		FOR(i,1,k){
			FOR(j,1,i){
				g[j].k=g[j-1].k*a[j]%p[i];
				g[j].b=(g[j-1].b*a[j]+b[j])%p[i];
			} if(g[i].b%gcd(g[i].k,p[i])!=0){ flag=false; }
			Array[i]=(p[i]*g[i].b-g[i].b)%p[i]*inv(g[i].k,p[i]);
		} if(flag==false){ puts("No"); continue; }
		FOR(i,1,k){
			if(Array[i]==0){ continue; }
			FOR(j,1,i-1){
				if(Array[j]==0){ continue; }
				if(p[i]%p[j]==0){
					if(Array[i]%p[i]!=Array[j]%p[j]){
						flag2=false;
						goto ending;
					}
				}
			}
		} ending:{ puts(flag2?"Yes":"No"); }
	}
	return 0;
}
```


---

## 作者：VinstaG173 (赞：2)

CRTyyds.

显然对于模不同的素数的同余方程我们可以用中国剩余定理合并。（但是用到这个性质放 B 一定偏难吧？）

因此我们只要考虑对于每个不同的素数是否存在相应的 $f_0$ 然后 CRT 合并答案即可。

接下来对于给定的素数 $p$， 我们标记出每个 $p_i=p$ 的位置 $i_1,i_2,\dots,i_k$。首先处理 $f_{i_1}$，若 $a_1,\dots,a_{i_1}$ 中有 $p$ 的倍数则从最后一个 $p$ 的倍数开始计算 $f_{i_1} \bmod{p}$（此时这个值是确定的），否则直接令 $p \mid f_{i_1}$（显然可以解出对应的 $f_0$）。然后此时后面所有 $f_{i_t} \bmod{p}$ 的值都是确定的了，只要暴力计算就行了。只要有一个地方计算得到的不是 $0$ 答案就是 `No`，否则就是 `Yes`。

时间复杂度 $O(n^2)$。~~网太卡了找不到代码，就不放了。~~

---

## 作者：2huk (赞：1)

不难发现：

$$
f_i = A_if_0 + B_i
$$

其中 $A_i = \prod_{j = 1}^i a_j, B_i = \sum_{j=1}^i b_j \times \prod_{k=j+1}^i a_k$。是关于 $i$ 的常数。

那么条件就变成了：

$$
\left\{
\begin{matrix}
A_1f_0 + B_1 \equiv 0 \pmod {p_1} \\
A_2f_0 + B_2 \equiv 0 \pmod {p_2} \\
\vdots \\
A_if_0 + B_i \equiv 0 \pmod {p_i} \\
\vdots \\
A_nf_0 + B_n \equiv 0 \pmod {p_n} \\
\end{matrix}
\right.
$$

当 $A_i = 0$ 时，如果 $B_i \not \equiv 0 \pmod {p_i}$ 则无解，否则如果 $B_i \equiv 0 \pmod {p_i}$ 则无需考虑这个方程。

当 $A_i \ne 0$ 时，将方程变形：

$$
f_0 \equiv \dfrac{-B_i}{A_i} \pmod {p_i}
$$

因为 $p_i$ 是质数，方程右边是能用费马小定理算的。所以我们可以求出 $f_0$ 在模 $p_i$ 意义下的值。

若存在 $f_0$ 在同一个模数下的值不同，则无解。否则对于两个不同的模数，一定可以通过中国剩余定理的方式得到解。

```cpp
int n, a[N], b[N], p[N], A[N], B[N];

int fpm(int a, int b, int p) {
	int res = 1;
	while (b) {
		if (b & 1) res = res * a % p;
		b >>= 1, a = a * a % p;
	}
	return res;
}

bool solve() {
	cin >> n;
	
	for (int i = 1; i <= n; ++ i ) cin >> a[i];
	for (int i = 1; i <= n; ++ i ) cin >> b[i];
	for (int i = 1; i <= n; ++ i ) cin >> p[i];
	
	map<int, int> mp;
	for (int i = 1; i <= n; ++ i ) {
		A[0] = 1;
		for (int j = 1; j <= n; ++ j ) {
			A[j] = A[j - 1] * a[j] % p[i];
			B[j] = (a[j] * B[j - 1] % p[i] + b[j]) % p[i];
		}
		
		if (A[i] == 0) {
			if (B[i]) return false;
		}
		else {
			int y = (p[i] - B[i]) * fpm(A[i], p[i] - 2, p[i]) % p[i];
			if (mp.count(p[i]) && mp[p[i]] != y) return false;
			mp[p[i]] = y;
		}
	}
	
	return true;
}
```

---

## 作者：by_chance (赞：1)

[P8178 「EZEC-11」Sequence](https://www.luogu.com.cn/problem/P8178)

好像是一道挺好想的数论题。

首先考虑 $ k = 1 $ 的情况。以下省略下标 $ 1 $ 。

若 $ p \bmod a = 0 $，则当 $ p \bmod b =0 $ 时有解，反之无解。

否则，若 $ p \bmod a \ne 0 $，则一定有解。取 $ f_0 = b \times a^{-1} $ 即可，这里 $ a^{-1} $ 表示 $ a $ 模 $ p $ 的乘法逆元。

考虑如何将其推广到 $ k $ 个数的情况。

首先有一个显然的事情：对于任意 $ n $，都有整数 $ A $，$ B $ 使得 $f_n=A \times f_0 + B $。

这个时候，只判断有解性是不够的，我们需要找出这个解。

（下面 $ p $ 代表 $ p_n $）

若 $ p \bmod A = 0 $，则当 $ p \bmod B =0 $ 时有解，$ f_0 \bmod p $ 可以为任意值；反之无解。

否则，若 $ p \bmod A \ne 0 $，则一定有解。必须有 $ f_0 \bmod p = ( B \bmod p ) \times A^{-1} $ 即可，这里 $ A^{-1} $ 表示 $ A $ 模 $ p $ 的乘法逆元。

如果存在一个 $ p $，使得 $ f_0 \bmod p $ 有两个值，则无解；否则，由中国剩余定理，知一定有解。

代码实现时，每一次的 $ A $，$ B $ 需要 $ O(k) $ 求，边求边取模；用费马小定理求逆元；用 map 保存余数。

细节见代码。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
int T,n,a[N],b[N],p[N],A,B,f;
map<int,int> M;
int power(int a,int b,int p){
	int c=1;
	for(;b;b>>=1){
		if(b&1)c=1ll*c*a%p;
		a=1ll*a*a%p;
	}
	return c;
}
int main(){
	scanf("%d",&T);
	while(T--){
		f=1;M.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",a+i);
		for(int i=1;i<=n;i++)scanf("%d",b+i);
		for(int i=1;i<=n;i++)scanf("%d",p+i);
		for(int i=1;i<=n;i++){
			A=1;B=0;
			for(int j=1;j<=i;j++){
				A=1ll*A*a[j]%p[i];
				B=(1ll*a[j]*B+b[j])%p[i];
			}//求A,B
			if(A%p[i]==0&&B%p[i]!=0)f=0;
			else if(A%p[i]==0&&B%p[i]==0)continue;
			else{
				B=p[i]-B%p[i];
				int x=1ll*B*power(A,p[i]-2,p[i])%p[i];
				if(M.find(p[i])==M.end())M[p[i]]=x;
				else if(M[p[i]]!=x)f=0;
			}
		}
		printf(f?"Yes\n":"No\n");
	}
	return 0;
}
```

Upd：修改了LaTeX。

---

## 作者：MarSer020 (赞：0)

### 题外话

~~水一发月赛题解（~~

听说这道题劝退了不少人，但 也不是那么难 吧（？）

### 进入正题：

首先看到第一行的式子，很容易推出通项式子：

$$tmpa = \prod\limits_{i=1}^n a_i$$
$$tmpb = \sum\limits_{i=1}^n \left(b_i \times \prod\limits_{j=i+1}^n a_i\right)$$
$$f_n = tmpa \times f_0 + tmpb$$

（写的不好，见谅）

然后继续往下读，我们就发现可以用这个通项公式来算出每个 $f_0 \bmod p_i$ 的值，从而判断是否存在满足条件的 $f_0$ 。

我们将 $f_0 \bmod p_i$ 数列记为 $c_i$ 。

那么，我们由[中国剩余定理](https://oi-wiki.org/math/number-theory/crt/)可知，只要不存在 $i,j$ 使得 $p_i=p_j$ 且 $c_i \ne c_j$ ，则存在此 $f_0$ 。

现在我们就只需要求出 $c$ 数列的值，再进行判断就可以了。

要求出 $c$ 数列的值，我们可以先求出每个 $tmpa$ 和 $tmpb$ 在 $\bmod \ p_i$ 下的值，记为 $tmpa'$ 和 $tmpb'$ 。

然后我们就有了一个式子：

$$f_i \equiv tmpa' \times f_0 + tmpb' \equiv 0 \pmod{p_i}$$

这样我们就可以进一步推导为：

$$tmpa' \times f_0 \equiv p_i - tmpb' \pmod{p_i}$$

我们对 $tmpa'$ 求 $\bmod \, p_i$ 意义下的逆元，记为 $\operatorname{inv} \left(tmpa' \right)$ ，则：

$$f_0 \equiv \operatorname{inv} \left(tmpa' \right) \times \left(p_i - tmpb' \right) \pmod{p_i}$$

即：

$$c_i = \operatorname{inv} \left(tmpa' \right) \times \left(p_i - tmpb' \right)$$

所以，我们可以用 $O\left(n \right)$ 的时间复杂度求出一对 $tmpa'$ 和 $tmpb'$ ，用 $O\left(n^2 \right)$ 的时间复杂度求出 $c$ 数列，总时间复杂度 $O\left(Tn^2\right)$ 。

当然，要注意判断 $tmpa'=0$ 的情况。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[1005],b[1005],p[1005];
map<int,bool>gt;//用来存每一个模数有没有在之前被记录过 
map<int,int>qwq;//用来存每个模数下的 c 
int qpow(int b,int m,int s){
	int ans=1;
	while(m){
		if(m&1)
			ans=ans*b%s;
		b=b*b%s,m>>=1;
	}
	return ans;
}//快速幂，用来求逆元 
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		gt.clear();
		qwq.clear();
		bool f=1;//代表有没有合法的 f0 
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		for(int i=1;i<=n;i++){
			cin>>p[i];
			gt[p[i]]=0;
			qwq[p[i]]=p[i];
		}
		for(int i=1;i<=n;i++){
			int tmpa=1,tmpb=0,cur;
			for(int j=1;j<=i;j++)
				tmpa=tmpa*a[j]%p[i],tmpb=(tmpb*a[j]%p[i]+b[j]%p[i]+p[i])%p[i];
			if((!tmpa)&&tmpb){//特判 0 
				cout<<"No"<<endl;
				f=0;
				break;
			}
			if(!tmpa)//特判 0 
				continue;
			tmpb=p[i]-tmpb,cur=qpow(tmpa,p[i]-2,p[i])*tmpb%p[i];//cur 是 tmpa' 的逆元 
			if(gt[p[i]]&&qwq[p[i]]!=cur){//如果产生冲突 
				cout<<"No"<<endl;
				f=0;
				break;
			}
			gt[p[i]]=1,qwq[p[i]]=cur;//记录 
		}
		if(f)
			cout<<"Yes"<<endl;
	}
	return 0;
}
```

### 总结：

这道题作为月赛 T2 ，~~难度还是有的~~。

希望洛谷月赛越办越好（

---

## 作者：3a51_ (赞：0)

发现对于任意的 $f_i$ 满足 $f_i=f_{i-1} \times a_i+b_i$，再将 $f_{i-1}$ 展开得到 $f_i=(f_{i-2} \times a_{i-1}+b_{i-1}) \times a_i + b_i$。

去括号得到 $a_i=a_{i-1} \times a_i \times f_{i-2} + b_{i-1} \times a_i+b_i=x \times f_{i-2} + y$，然后再次展开，直到原式变为 $r \times f_0+q$ 为止。

接下来对于每一次询问把 $f_i$ 写为 $r_i \times f_0 +q_i$ 的形式，然后求一下 $f_0 \! \mod p_i$ 的值，如果与已有结果重复，但是结果不同，那么就直接输出```No```，否则输出```Yes```。

---

