# Division

## 题目描述

Oleg's favorite subjects are History and Math, and his favorite branch of mathematics is division.

To improve his division skills, Oleg came up with $ t $ pairs of integers $ p_i $ and $ q_i $ and for each pair decided to find the greatest integer $ x_i $ , such that:

- $ p_i $ is divisible by $ x_i $ ;
- $ x_i $ is not divisible by $ q_i $ .

 Oleg is really good at division and managed to find all the answers quickly, how about you?

## 说明/提示

For the first pair, where $ p_1 = 10 $ and $ q_1 = 4 $ , the answer is $ x_1 = 10 $ , since it is the greatest divisor of $ 10 $ and $ 10 $ is not divisible by $ 4 $ .

For the second pair, where $ p_2 = 12 $ and $ q_2 = 6 $ , note that

- $ 12 $ is not a valid $ x_2 $ , since $ 12 $ is divisible by $ q_2 = 6 $ ;
- $ 6 $ is not valid $ x_2 $ as well: $ 6 $ is also divisible by $ q_2 = 6 $ .

 The next available divisor of $ p_2 = 12 $ is $ 4 $ , which is the answer, since $ 4 $ is not divisible by $ 6 $ .

## 样例 #1

### 输入

```
3
10 4
12 6
179 822```

### 输出

```
10
4
179```

# 题解

## 作者：Zesty_Fox (赞：8)

阅读体验更佳：[点这里](https://www.cnblogs.com/acceptedzhs/p/13912693.html)

题意：求最大的正整数 $x$ ，使 $x \mid p$ 且 $q \nmid x$ 。

首先，当 $q \nmid p$ ，显然取 $x=p$ 是最优解。

现在，我们考虑 $q \mid p$ 的情况。

考虑对 $q$ 分解质因数，设 $q=p_1^{a_1} \times p_2^{a_2}\times \cdots \times p_n^{a_n}$ 。

那么，$x$ 不为 $q$ 的倍数，当且仅当 $\exists i$，使得 $x$ 分解质因数后 $p_i$ 的次数 $< a_i$ 。

我们可以枚举每个 $p_i$ ，使 $x$ 分解质因数后 $p_i$ 的次数为 $a_i-1$ ，其他全部拉满即可。

也就是说，设 $t$ 是 $p$ 被 $p_i$ 除尽后剩下的数，则最优解是 $p_i^{a_i-1} \times t$ 。

最后在这些备选最优解中取 $\max$ 即可。

Code:

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const int N=100010;
ll T,p,q,pr[N],cnt,vis[N];
void pre(int lim){
    for(int i=2;i<=lim;i++){
        if(!vis[i]){
            vis[i]=1;pr[++cnt]=i;
            for(int j=i;j<=lim/i;j++) vis[i*j]=1;
        }   
    }
}
 
int main(){
    scanf("%d",&T);pre(N-1);
    while(T--){
        scanf("%lld%lld",&p,&q);
        if(p%q!=0) cout<<p<<endl;
        else{
            ll ans=1,tmp=q;
            for(int i=1;i<=cnt;i++){
                ll cs=0,res=1;
                while(tmp%pr[i]==0) tmp/=pr[i],cs++,res*=pr[i];
                if(!cs) continue;//cs即为上文提到的a_i
                res/=pr[i];//res=pr[i]^(a_i-1)
                if(p%res==0){
                    ll tmp1=p;while(tmp1%pr[i]==0) tmp1/=pr[i];
                    ans=max(ans,res*tmp1);
                }   
            }
            if(tmp>1){//如果tmp还有残余，说明tmp本身是个质数
                ll res=1;
                //res肯定为1，不用算了
                if(p%res==0){
                    ll tmp1=p;while(tmp1%tmp==0) tmp1/=tmp;
                    ans=max(ans,res*tmp1);
                }
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}
```


---

## 作者：AsunderSquall (赞：7)

update：远古题解一大堆格式错误，试图一个个修复。

update:题意描述出了小偏差，已修正

题意：给你两个数 $ p,q $，求出最大的数 $ x $，使得 $ x\  |\ p,q\not |\  x $。 

首先，显然，当 $ q \not | p $  时，直接输出 $ p $ 即可。  
然后考虑当 $ q \ | \ p $ 的时候，$ q $ 的所有质因子一定都包含在 $ p $ 里面，且数量一定不比 $ p $ 多。  
那么我们就先把 $ q $ 分解掉。  
这里需要记录 $ q $ 的每一个素因子是什么以及个数。  
注意到 $ q \leq 10^9 $，那么 $ q $ 一定最多只有一个 $ >4\times 10^4 $ 的因子。  
所以我们筛 $ 4\times10^4 $ 以内的所有质因子，然后把 $ q $ 所有 $ 4\times 10^4 $ 以内的质因子全部记录然后除掉。  
如果剩下的数不是 $ 1 $，那么说明剩下的数就是 $ q $ 那个 $ >4\times 10^4 $ 的因子，个数为 $ 1 $ 。  
然后考虑分解完 $ q $ 后怎么办。  
显然，要使 $ x \not | \ q $，那么一定存在一个素数，使得它在 $ x $ 中的次数比 $ q $ 中的少。  
那么我们枚举 $ q $ 的 $ P $，然后计算 $ p $ 有多少个 $ P $，然后 $ x $ 就等于 $ p $ 除以一定数量的 $ P $，最后对于不同的 $ P $ 取 $ x $ 的最大值就行了。  
代码（各个变量和题解中描述的不一样，关系应该不大）  
```cpp

#include<bits/stdc++.h>
#define int long long
#define rd(x) x=read()
using namespace std;
const int N=3e5+5;
const int M=2005;
inline int read(){int x=0,f=1;char ch=getchar();while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int ksm(int x,int y,int z){int ret=1;while (y){if (y&1) ret=(ret*x)%z;x=(x*x)%z;y>>=1;}return ret;}
int p,q,ans;
int prim[N],vis[N],cnt;
int num[N],CNT[N],Cnt;
void init()
{
    for (int i=2;i<N;i++)
    {
        if (!vis[i]) prim[++cnt]=i;
        for (int j=1;j<=cnt;j++)
        {
            if (prim[j]*i>=N) break;
            vis[prim[j]*i]=1;
            if (i%prim[j]==0) break;
        }
    }
}
signed main()
{
    init();
    int T;
    cin>>T;
    while (T--)
    {
        cin>>p>>q;
        int x=p;
        if (p%q==0)
        {
            {
                //先把q分解了
                Cnt=0;
                for (int i=1;i<=cnt;i++)
                {
                    if (q%prim[i]==0)
                    {
                        num[++Cnt]=prim[i];
                        CNT[Cnt]=0;
                        while (q%prim[i]==0)
                        {
                            CNT[Cnt]++;
                            q/=prim[i];
                        }
                    }
                }
                if (q!=1) num[++Cnt]=q,CNT[Cnt]=1;
                //首先，q的所有素因子一定都在p里面
                //然后我们需要把其中一个素因子的个数改得比q小
                //枚举算出来
                int chushu=p;
                for (int i=1;i<=Cnt;i++)
                {
                    x=p;
                    int TMP=0;
                    while (x%num[i]==0)
                    {
                        x/=num[i];
                        TMP++;
                    }
                    //就是说p有TMP个num[i]
                    chushu=min(chushu,ksm(num[i],TMP-CNT[i]+1,0x3f3f3f3f3f3f3f3f));
                }
                cout<<p/chushu<<endl;
                for (int i=1;i<=Cnt;i++) num[i]=CNT[i]=0;
                Cnt=0;
            }
        }
        else cout<<x<<endl;
    }    
}
```

---

## 作者：灵茶山艾府 (赞：3)

若 $Q\nmid P$，则答案就是 $P$。

否则，将 $Q$ 分解成 $p_1^{e_1}p_2^{e_2}\dots p_k^{e_k}$，则 $P$ 也可以分解出同样的质数且对应幂次 $e_i' \ge e_i$。

要使 $Q\nmid x$，可以将 $P$ 中的某个质数的幂次降低到 $e_i$ 以下。题目要求最大的 $x$，则需要枚举每个 $p_i$，将 $P$ 中的对应幂次降低到 $e_i-1$，求出最大的值即为答案。

AC 代码：(Golang)

```go
package main
import . "fmt"

func main() {
	var T, p, q int64
	for Scan(&T); T > 0; T-- {
		Scan(&p, &q)
		if p%q > 0 {
			Println(p)
			continue
		}
		ans := int64(0)
		for i := int64(2); i*i <= q; i++ {
			e := 0
			for ; q%i == 0; q /= i {
				e++
			}
			if e > 0 {
				c := 0
				for v := p; v%i == 0; v /= i {
					c++
				}
				v := p
				for ; c >= e; c-- {
					v /= i
				}
				ans = max(ans, v)
			}
		}
		if q > 1 {
			for ; p%q == 0; p /= q {
			}
			ans = max(ans, p)
		}
		Println(ans)
	}
}

func max(a, b int64) int64 {
	if a > b {
		return a
	}
	return b
}
```



---

## 作者：One_JuRuo (赞：2)

## 思路

首先特判特殊情况，若 $p_i$ 本身不可被 $q_i$ 整除，那么 $x_i$ 就直接取 $p_i$ 最大。

否则的话，$p_i=q_i\times k$。所以 $q$ 的质因数，$p$ 都有，并且数量一定大于等于 $q$ 的这个质因数的数量。

那么如果 $x_i$ 的某个质因数个数小于 $q_i$ 的话，$x_i$ 就不能被 $q_i$ 整除。

其他的质因数个数就可以取 $p_i$ 的。

所以我们先记录 $p_i$ 到 $a$，然后直接枚举 $q_i$ 的质因数，再然后除以 $p_i$ 所有的这个质因数的积，再乘以 $q_i$ 所有的这个质因数的积，再除以这个质因数，这样就得到了一个解，最后取所有解的最大值即可。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
long long a,b,ans,aa;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%lld",&a,&b),ans=0,aa=a;
		if(a%b){printf("%lld\n",a);continue;}
		for(long long i=2;i*i<=b;++i)
		{
			if(b%i==0)
			{
				long long t2=1;
				while(a%i==0) a/=i,t2*=i;
				while(b%i==0) b/=i,t2/=i;
				ans=max(ans,aa/t2/i);
			}
		}
		if(b>1)
		{
			long long t2=1;
			while(a%b==0) a/=b,t2*=b;
			ans=max(ans,aa/t2);
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：zztqwq (赞：1)

# Codeforces 1444A

## Solution

考虑什么情况下 $x$ 能够满足 $x$ 不是 $q$ 的倍数。显然，若将他们分解成 $\prod_{i=1}^m p_i^{c_i}$ 的质因数分解形式，则 $x$ 的某一个 $c_i$ 一定小于 $q$ 的 $c_i$，为了使 $x$ 最大，它的 $c_i$ 等于 $q$ 的 $c_i-1$，其他质因数及其指数和 $p$ 一样。枚举这个 $c_i$，统计哪个 $c_i$ 能使 $x$ 最大即可。

## Code

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long
int p;int q;
int qpow(int a,int n)
{
	int ans=1;
	while(n)
	{
		if(n&1) ans*=a;
		a*=a;
		n>>=1;
	}
	return ans;
}
int init()
{
	int ans=0x3f3f3f3f3f3f3f3f;
	for(int i=2;i*i<=q;i++)
	{
		if(q%i) continue;
		int c1=0,c2=0;
		while(q%i==0)
		{
			c1++;
			q/=i;
		}
		while(p%i==0)
		{
			c2++;
			p/=i;
		} 
		ans=min(ans,qpow(i,c2-c1+1)); 
	}
	if(q>1)
	{
		int i=q;
		int c1=0,c2=0;
		while(q%i==0)
		{
			c1++;
			q/=i;
		}
		while(p%i==0)
		{
			c2++;
			p/=i;
		} 
		ans=min(ans,qpow(i,c2-c1+1)); 
	}
	return ans;
} 
void read(int &x)
{
	x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x*=f;
}
void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)write(x/10);
	putchar(x%10^48);
}
signed main()
{
	int T;
	read(T);
	while(T--)
	{
		read(p);read(q);
		if(p%q)
		{
			write(p);
			putchar('\n');
		}
		else
		{
			write(p/init());
			putchar('\n');
		}
	}
	return 0;
}
```



---

## 作者：ql12345 (赞：1)

## 将思路理清

#### 前言：

打CF的时候，思路清晰，出解法就很快了，正确性证明也会很简单

#### Solution：

题中让我们求一个数x是p的因数，但不是q的倍数

一个**套路**的第一反应：**分类讨论**

- 如果p不是q的倍数，p合法，且p是p中最大的因数，答案为p，特判掉即可

- 如果p是q的倍数，**转化题意**，p中删去最小的一些因数，使得p不再是q的倍数

对于这个新的题意，我们的思路肯定是什么筛质因子，判断个数之类的，但都太复杂了，不如再**观察下题面**，看看有没有其他**性质**

不是q的倍数，一定存在一个q的约数，p中“不包含”

枚举这个约数即可，别着急，看一个例子：$p=24, q=4$答案为6，但6包含2这个4的因子，所以实际上是用这个约数缩小p的范围，知道p不是q的倍数为止

容易发现这个约数不能取1，但要注意判这个约数为q的情况（因为这个WA了两回），一个例子$p=12, q=2$

总时间复杂度：$O(T\sqrt{q})$

#### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int gcd(int x, int y)
{
	return ! y ? x : gcd(y, x%y);
}

signed main()
{
	int t;
	cin>>t;
	while(t --)
	{
		int p,q;
		cin>>p>>q;
		if(p==1)
		{
			cout<<1<<endl;
			continue;
		}
		int d=gcd(p,q);
		if(d!=q)
		{
			cout<<p<<endl;
			continue;
		}

		d=2e18;
		for(int i=2;i*i<=q;++i)if(q%i==0){ //找到一个数，把它完全删去的代价 
			int dd=1,k=p;
			while(k%q==0) dd*=i,k/=i;
			d=min(d, dd);
			int j=q/i;
			dd=1,k=p;
			while(k%q==0) dd*=j,k/=j;
			d=min(d, dd);
		}
		int dd=1,k=p;
		while(k%q==0) dd*=q,k/=q;
		d=min(d, dd);

		cout<<p/d<<endl;
	}
	
	return 0;
}
```

养成好习惯：

- 多加一些特判，即使可能没必要

- 自己手写C++11才有的函数

- 分解完因数记得判断1和q也是因数

---

## 作者：Zxsoul (赞：1)

## 题面
- t  组数据。

- 给定参数 p,q，求一个最大的 x，满足 $(x|p)∧(q∤x)$。

- $ 1\le $t$ \le500$，$1\le $p$ \le10^{18}$，$2\le q\le10^9$,
- $1S$，$512MB$。

## 思路

- 当 $p < q$ 时 或 $q∤p$,答案显然是 $p$，直接输出即可

- 当 $q | p$，即 $q$ 是 $p$ 的因子时

- 我们可以将 $p$ , $q$ 质因数分解，让 $p$ 去除以 $q$的质因子，直到 $p$ 不能被 $q$ 整除，

- $p$ 中比 $q$ 大的质因子是对上面没有影响的，因此仅考虑$q$ 的质因子

- 相比于删除多种质因子，只删一种的方案更优

- 穷举删除，找到最大值即可

- 复杂度$O$ ($t$  $ \sqrt{q} $) 

---

## 推论
- 分解质因数 $p,q,x$

   $$p=\prod a_i^{b_1}$$
  
   $$q=\prod a_i^{b_2}$$
  
   $$x=\prod a_i^{b_3}$$
  
- 因为条件是 $(x|p)∧(q∤x)$ 即:

   $$p = k \times x =k\times \prod a_i^{b_3}(k\in N^*) $$
  
   $$∃a_i|q,b_3<b_2$$
  
- 换句话说, $x$ 中的包含 $q$ 中的质因子，且质因子数量 $<q$,可以为 $0$

- 因此要找的 $x$ 就是 $p$ 中删除部分质因子后的数，使得达到上述条件

- 相比删除多种，只需使一种质因子数量不满足上述条件即可，即只删一种

- 枚举 $q$ 的所有质因子计算即可

## Code
```cpp
#include <iostream>//声明：luckyblock的思路 
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#define int long long //我用 int 来代替 long long  
using namespace std;


const int manx=1e6+10;
const int mamx = 1e6 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar(); int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

signed main(){
	int t = read();
	while(t--){
		int ans = 1;
		int  p = read(),q = read();//看清上边备注，和数据范围 
		int s = p;
		if(p < q){cout<<p<<endl;continue;}
		if(p % q != 0){cout<<p<<endl;continue;}
		for(int i = 2;i*i <= q; i++){//枚举q中每一个“因子” 
			if(q%i == 0){
				int jsq = 0,jsp = 0;
				while(q % i == 0ll){ // 取模最好类型相同 
					q = q / i;
					jsq ++;
				}
				while(p % i == 0ll){
					p /= i;
					jsp ++;
				}
				if(jsp < jsq) continue;//说明该 “因子 ”非 “质因子 ” 
				int jj =  s;//因为 q p 时刻都在更新，所以预处理 用其他变量代替。 
				for(int k = 1; k <=jsp - jsq + 1;k++){
					jj /= i;
				}
				ans = max(jj,ans);
			}
		} 
		if(q != 1){//比q大的质因子，注：此时的p q 以被更新，所存的数中不存在共同的质因子 
			int jsp = 0;
			while(p % q == 0){
				p /= q;
				jsp++;
			} 
			int jj = s;
			for(int i = 1; i <= jsp;i ++){
				jj /= q;
			}
			//cout<<jj<<endl;
			ans = max(jj,ans);
		}
		cout<<ans<<endl;
	}
	return 0;
}


```



---

## 作者：Durancer (赞：1)

#### 思路解析

1、这个题目我们可以用分解质因数的方式进行求解

众所周知，当一个数p可以被q整除时，那么组成q的每一类因子数量一定≤组成p的该种类因子的数量，即

$$q_i≤p_i(i≤\sqrt{q})$$

##### 举个例子：$p=24,q=4$

分解p：$24=2×2×2×3$

分解q：$4=2×2$

显而易见的是，$p_2>q_2\   $ $p_3>q_3$

那么当我们将24的因子$2$除去$p_2-q_2+1$即除以$2*2$时

$24$就变成了$6=2×3$

那么这个时候，$24—>6$转换后就不会被4整除了

这也是这个题目的思路，将$[2,\sqrt{q}]$中的所有数都出枚举除一遍，然后在根据上面的例子中的方法进行处理，得出一个十分优的答案。

最后的时候，如果当经过处理的$q$还不为0的时候，那么我们在进行一个操作，用当前处理过的$q$继续整除处理过的的$p$，因为此时p中还含有因子，所以我们还要枚举一遍进行查找，然后我们在将整除下来的因子数量，除到原先的$p$上去，看是否可以的到一个更优秀的答案

2、特别判断 共分为两种情况，可以优化时间复杂度

$(1)$ 当$p<q$的时候，这个时候$q$肯定不能整除q，所以我们就可以直接把$p$当做一个最优的答案输出然后进行下一组数据的操作

$(2)$ 当$p%q≠0$的时候，这个时候也满足题目的条件，那么我们直接输出$p$就可以了

#### 代码实现

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<map>
#define int long long
using namespace std;
int T;

signed main()
{
	cin>>T;
	while(T--)
	{
		int ans=1;
		int p,q;
		cin>>p>>q;
		int kap=p;
		if(p<q) 
		{
			cout<<p<<endl;
			continue;
		}
		if(p%q!=0)
		{
			cout<<p<<endl;
			continue;
		}
		int cun=q;
		for(int i=2;i*i<=cun;i++)
		{
			if(q%i==0ll)
			{
				int cntq=0;
				int cntp=0;
				while(q%i==0ll)
				{
					q/=i;
					cntq++;
				}
				while(p%i==0ll)
				{
					p/=i;
					cntp++;
				}
				if(cntp<cntq) continue;
				int maxn=kap;
				for(int k=cntp-cntq+1;k;k--)
				{
					maxn/=i;
				}
				if(maxn>ans)
				{
					ans=maxn;
				}
			}
		}
		if(q!=1)
		{
			int cntp_=0;
			while(p%q==0ll)
			{
				p/=q;
				cntp_++;
			}
			int pd=kap;
			for(int k=cntp_;k;k--)
			{
				pd/=q;
			}
			if(pd>ans) ans=pd;
		}
		cout<<ans<<endl;
	}
} 
```




---

## 作者：loser_seele (赞：0)

喜提本题第 999 份代码提交及最劣解。

首先不难发现 $ p \bmod q $ 不为 $ 0 $ 的情况下直接选 $ p $ 显然最优。

否则应该选取 $ p $ 的一个因子，这是显然的。

由唯一分解可得 $ q=\prod\limits_{i=1}^n{p_i}^{a_i} $，那么把 $ q=\prod\limits_{i=1}^m{p_i}^{b_i} $ 也质因子分解后构造出的答案肯定至少存在一个 $ b_i < a_i $，否则可以整除，不满足条件。

于是把 $ p,q $ 暴力质因子分解，然后逐个枚举符合条件的质因子暴力修改为 $ b_i=a_i-1 $，取最大值即可。

但是 $ p \leq 10^{18} $，考虑直接 Pollard-rho 分解质因子即可。注意不能直接快速乘，否则前面的点因为常数过大也过不去，而应该采用类似代码的 $ \mathcal{O}(1) $ 实现。

问题来了，我们发现直接实现会有一个点 TLE 掉，观察这个数据，发现这个数据的 $ p $ 完全相同，于是记录下每次分解的时候的数组，免得重复分解浪费时间。最后压线跑进时限。

这份代码应该是能 hack 的，但是最后能通过原题数据。

总时间复杂度 $ \mathcal{O}(Tp^\frac{1}{4}) $，可以通过。

代码：

```cpp
#pragma GCC Ofast
#include <bits/stdc++.h>
using namespace std;
#define gc c=getchar()
#define r(x) read(x)
#define ll long long
#define int long long
template<typename T>
inline void read(T&x)
{
    x=0;T k=1;char gc;
    while(!isdigit(c)){if(c=='-')k=-1;gc;}
    while(isdigit(c)){x=x*10+c-'0';gc;}x*=k;
}
#define li inline
#define re register
inline int add(int a,int b,int p)
{
    a+=b;
    if(a>=p)
    a-=p;
    return a;
}
inline int mul(int a,int b,int mod)
{
return (a*b-(int)((long double)a/mod*b)*mod+mod)%mod;
}
ll pow(ll a, ll b, ll m) 
{
  ll ans = 1;
  for (a %= m; b; b >>= 1, a = mul(a, a, m))
    if (b & 1) 
    ans = mul(ans, a, m);
  return ans;
}
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}
ll lcm(ll a,ll b)
{
    return a/gcd(a,b)*b;
}
bool MR_check(ll a, ll p, ll s, int d) 
{
  ll k = pow(a, s, p);
  if (k == 1) return true;
  for (; d; --d, k = mul(k, k, p)) 
  {
    if (k == p - 1) 
    return true;
    if (k == 1) 
    return false;
  }
  return k == 1;
}
bool MR(ll x) 
{
  static const int cnt = 12;
  static const int p[cnt] = { 2, 3, 5, 7, 11, 13, 17, 19, 61, 2333, 4567, 24251 };
  if (x == 1) 
  return false;
  ll s = x - 1; 
  int d = 0;
  while (!(s & 1)) 
  ++d, s >>= 1;
  for (int i = 0; i < cnt; ++i) 
  {
    if (x % p[i] == 0) 
    return x == p[i];
    if (!MR_check(p[i], x, s, d)) 
    return false;
  }
  return true;
}
namespace Pollard_Rho 
{
ll PR_check(ll c, ll p) 
{
  ll y = rand() % p, z = y;
  int k = 1, j = 0;
  while(1145141919810) 
  {
    z = (mul(z, z, p) + c) % p;
    ll t = gcd(p, std::abs(z - y));
    if (t > 1) 
    return t;
    if (++j == k) 
    y = z, k <<= 1;
  }
}
void factor_(ll x, std::vector<ll> &v) 
{
  if (x == 1) return;
  if (MR(x)) { v.push_back(x); return; }
  ll y = x;
  while (y == x) y = PR_check(rand() % x, x);
  factor_(y, v);
  factor_(x / y, v);
}
void factor(ll x, std::vector<ll> &v) 
{
  v.clear();
  factor_(x, v);
  std::sort(v.begin(), v.end());
}
}
using Pollard_Rho::factor;
unordered_map<int,int>p1,p2;
unordered_map<int,vector<int> >pr;
signed main()
{
    int T;
    for(r(T);T;--T)
    {
        int p,q;
        r(p),r(q);
        if(p%q)
        cout<<p<<'\n';
        else
        {
        p1.clear(),p2.clear();
        vector<int>d;
        if(pr[p].size())
        d=pr[p];
        else
        factor(p,d),pr[p]=d;
        for(auto x:d)
        p1[x]++;
        vector<int>f;
        if(pr[q].size())
        f=pr[q];
        else
        factor(q,f),pr[q]=f;
        for(auto x:f)
        p2[x]++;
        int maxn=0,now=p;
        for(auto x:p2)
        {
        int tmp=now,div=x.first;
        while(p1[div]>=p2[div])
        p1[div]--,tmp/=div;
        maxn=max(maxn,tmp);
        }
        printf("%lld\n",maxn);
        }
    }
}
```


---

## 作者：EDqwq (赞：0)

### 思路：

如果 $a$ 不是 $b$ 的倍数，显然答案为 $a$ 。

否则，我们可以发现， $a$ 的所有质因子的次数，都是比 $b$ 大的。

我们需要构造一个尽量大的数，它是 $a$ 的因数，而不是 $b$ 的倍数，可以发现，如果这个数的一个质因子的次数比 $b$ 的这个质因子的次数小，那么这个数绝不可能是 $b$ 的倍数。

所以我们有了一个朴素的思路，枚举 $a$ 的因子，然后选择任意一个变得比 $b$ 的相应的质因子小，复杂度 $\sqrt{a}$ 显然不行。

由于 $a$ 的质因子次数都比 $b$ 大，所以显然，我们可以直接枚举 $b$ 的质因子，然后判一下 $b$ 次数减一和 $a$ 的这个数的次数的更小值即可。

***

### 代码：

```
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int t;
int a,b;
int cnt;
int num[100010];
int times[100010];
int ans;

int poww(int x,int y){
	if(y == 0)return 1;
	int s = 1;
	for(;y;y /= 2,x = (x * x * 1ll))if(y % 2 == 1)s = (s * x * 1ll);
	return s;
}

signed main(){
	cin>>t;
	while(t --){
		ans = -1;
		int lst = -1;
		a = read(),b = read();
		mem(times,0);
		cnt = 0;
		if(a % b != 0){
			cout<<a<<endl;
			continue;
		}
		for(int i = 2;i * i <= b;i ++){
			if(b % i == 0){
				lst = i;
				num[++ cnt] = i;
				while(b % i == 0){
					b /= i;
					times[cnt] ++;
				}
			}
		}
		if(b != 1){
			if(b != lst)num[++ cnt] = b,times[cnt] = 1;
			else times[cnt] ++;
		}
		for(int i = 1;i <= cnt;i ++){
			int tmp = a;
			int tot = 0;
			while(tmp % num[i] == 0){
				tmp /= num[i];
				tot ++;
			}
			ans = max(ans,tmp * poww(num[i],min(tot,times[i] - 1)));
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：傅天宇 (赞：0)

[luogu's link](https://www.luogu.com.cn/problem/CF1444A)

[CF's link](https://codeforces.com/problemset/problem/1444/A)

#### 题意:

给定 $t$ 组询问，每组给两个数 $p_{i}$ 和 $q_{i}$，找出最大的整数 $x_{i}$，要求 $p_{i}$ 可被 $x_{i}$ 整除，且 $x_{i}$ 不可被 $p_{i}$ 整除。


#### Solution：

先特判 $p_{i}$ 不是 $q_{1}$ 倍数。

分解质因数，首先我们可以知道，$q_{i}$ 的所有因数一定都在 $p_{i}$ 里面，然后我们需要把其中一个素因子的个数改得比 $q_{i}$ 小，枚举即可。

#### Code：

```cpp
/*
 * @Author: FuTianyu 
 * @Date: 2020-11-02 07:25:12 
 * @Last Modified by: FuTianyu
 * @Last Modified time: 2020-11-02 07:38:43
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define REP(i,a,b) for(int i=a;i>=b;i--)
 
const int N=1e6+5;
 
int a,b,prime[N],sum[N],tot;
 
int ksm(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x;
        y>>=1;
        x=x*x;
    }
    return res;
}
 
signed main(){
    // freopen("CF1445C.in","r",stdin);
    // freopen("CF1445C.out","w",stdout);
    int T;
    scanf("%lld",&T);
    while(T-->0){
        tot=0;
        memset(prime,0,sizeof prime);
        memset(sum,0,sizeof sum);
        scanf("%lld%lld",&a,&b);
        if(a%b!=0){
            printf("%lld\n",a);
            continue;
        }
        int x=sqrt(b);
        FOR(i,2,x){
            if(b%i==0){
                prime[++tot]=i;
                while(b%i==0){
                    sum[tot]++;
                    b=b/i;
                }
            }
        }
        if(b!=1){
            prime[++tot]=b;
            sum[tot]++;
        }
        int Ans=0;
        FOR(i,1,tot){
            int tot2=0;
            x=a;
            while(x%prime[i]==0){
                tot2++;
                x=x/prime[i];
            }
            Ans=max(Ans,ksm(prime[i],min(tot2,sum[i]-1))*x);
        }
        printf("%lld\n",Ans);
    }
    return 0;
}
```

---

## 作者：EricQian (赞：0)

[CF1444A Division](https://www.luogu.com.cn/problem/CF1444A)

### 题意：

给定 $t$ 组询问，每组给两个数 $p_i$ 和 $q_i$ ，找出最大的整数 $x_i$ ，要求 $p_i$ 可被 $x_i$ 整除，且 $x_i$ 不可被 $q_i$ 整除 。

### 题解：

呜呜呜这道题总共算下来我爆了 $15$ 发 $\dots$ 妥妥掉分

+ $p\nmid q$ ：显然答案为 $p$ 。

+ $p\mid q$ ：枚举每个 $q$ 的因子 $d$ ，将 $p$ 一直除 $d$ 直到不能被 $q$ 整除为止，余数就是对应的答案 。最终答案就是所有余数中算出来的答案取 $\max$ 。

	为什么这是正确的：因为使劲除完 $d$ 以后的余数一定是 $p$ 的因子，且一定不被 $q$ 整除 。
    
代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Maxn 105
typedef long long ll;
ll maxll(ll x,ll y){ return x>y?x:y; }
ll t,p,q,ans;
ll cnt(ll x)
{
	 ll tmp=p;
	 while(tmp%q==0) tmp/=x;
	 return tmp;
}
int main()
{
     //freopen(".in","r",stdin);
     //freopen(".out","w",stdout);
	 scanf("%lld",&t);
	 while(t--)
	 {
	 	 scanf("%lld%lld",&p,&q),ans=1;
	 	 if(p%q) printf("%lld\n",p);
	 	 else
	 	 {
	 	 	 for(ll i=2;i*i<=q;i++) if(q%i==0)
	 	 	 	 ans=maxll(ans,cnt(i)),ans=maxll(ans,cnt(q/i));
	 	 	 ans=maxll(ans,cnt(q));
	 	 	 printf("%lld\n",ans);
		 }
	 }
     //fclose(stdin);
     //fclose(stdout);
     return 0;
}
```

[$\leftarrow$ 杂题](https://www.luogu.com.cn/blog/EricQian/za-ti) （这是为了连接跳转方便，读者可以视而不见）


---

## 作者：Midoria7 (赞：0)

若 $q\not|p$ ，显然 $x$ 可以取到最大值 $p$，所以我们只需要考虑 $q|p$ 的情况。因为 $p$ 是 $q$ 的倍数，所以若将 $q$ 按照唯一分解定理分解，对于每一个 $p_i^{c_i}$，都有 $p:c_i\geq q:c_i$。而我们要让他不整除就只需要枚举每一个 $c_i$，让最后的答案的 $c_i$ 正好是对应 $q$ 的 $c_i-1$即可。其他我们都可以取到最大值。

因此我们枚举每一个 $c_i$，先让 $p$ 除尽它，再乘上 $c_i-1$ 次方即可。然后我们对所有的答案取一个 $\max$。

## 代码

多测不清空 爆零两行泪

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=4e4+10;
long long p,q,ans;

long long v[maxn],c[maxn];
inline void Div(long long x){
    v[0]=c[0]=0;
    long long temp=x;
    for(int i=2;i*i<=x;i++){
        if(temp%i)continue;
        v[++v[0]]=i;c[v[0]]=0;
        while(temp%i==0){
            temp/=i;c[v[0]]++;
        }
    }
    if(temp!=1){
        v[++v[0]]=temp;c[v[0]]=1;
    }
}

inline long long qpow(long long x,long long b){
    long long ans=1,base=x;
    while(b){
        if(b&1)ans=ans*base;
        base=base*base;
        b>>=1;
    }
    return ans;
}

int main(){
    int T;scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%lld%lld",&p,&q);
        if(p%q!=0){
            printf("%lld\n",p);
            continue;
        }
        Div(q);
        for(int i=1;i<=v[0];i++){
            long long temp=p;
            while(temp%v[i]==0)temp/=v[i];
            ans=max(ans,temp*qpow(v[i],c[i]-1));
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：gyh20 (赞：0)

我们发现，我们找的是一个 $p$ 的因数，使得它不是 $q$ 的倍数。

我们发现，这个数 $x$ 不是 $q$ 的倍数当且仅当存在一个质因子 $s$ 使得 $s$ 的幂次在 $q$ 中比在 $x$ 中低。

发现 $q$ 只有 $10^9$，可以枚举每一个质因子暴力检测需要除多少次即可。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
inline int gcd(re int x,re int y){
	return y?gcd(y,x%y):x;
}
int n,m,a,b;
inline int check(re int x){
	re int xx=a;
	while(xx%x==0){xx/=x;
	}
	return xx; 
}
signed main(){
	re int t=read();
	while(t--){
		a=read(),b=read();re int ans=0;
		if(a%b!=0)printf("%lld\n",a);
		else {
			re int x=sqrt(b);
			for(re int i=2;i<=x;++i){
				if(b%i==0){
					re int num=1,ss=a;
					while(b%i==0)b/=i,num*=i;
					ans=max(ans,check(i)*num/i);
				}
			}
			if(b^1)ans=max(ans,check(b));
			printf("%lld\n",ans);
		}
	}
}
```


---

## 作者：275307894a (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF1444A)

题意简述:给出$a$与$b$，找到一个最大的数$x$，使得$a\bmod x=0$且$x\bmod b≠0$

这样的题目考虑质因数分解。

因为$b$分解是在可以接受的范围内，所以分解$b$。

设$b=a_1^{p_1}\times a_2^{p_2}\times...\times a_n^{p_n}$

然后将$a$分解得$a_1^{k_1}\times a_2^{k_2}\times...\times a_n^{k_n}\times last$

使得分解后的$x\bmod b≠0$的条件是任意一个$k_i<p_i$

那么从这之中取最小值即可。

代码实现:

```cpp
#include<cstdio>
#include<cmath>
#include<map>
#define min(a,b) ((a)<(b)?(a):(b))
using namespace std;
int n,m,k,z,f[100039],s[100039],d[100039],head,dh,t,sh;
map<long long,int> q;
long long x,y,now,tot,pus,ans,flag;
int main(){
//	freopen("1.in","r",stdin);
	register int i,j;
	for(i=2; i*i<=1e9; i++) {
		if(!f[i]) s[++head]=i;
		for(j=1; j<=head&&i*s[j]<=100000; j++) {
			f[i*s[j]]=1;
			if(i%s[j]==0) break;
		}
	}
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&x,&y);now=y;
		dh=sh=0;pus=1e18;
		for(i=1;s[i]*s[i]<=y&&i<=head;i++){
			if(now%s[i]==0){
				d[++dh]=s[i];
				while(now%s[i]==0)q[s[i]]++,now/=s[i],sh++;
			}
		} 
		if(now!=1)q[now]++,d[++dh]=now,sh++;
		now=x;
		for(i=1;i<=dh;i++){
			if(x%d[i]==0){
				ans=0;
				while(x%d[i]==0) x/=d[i],ans++;
				if(ans>=q[d[i]]){
					tot=1;
					for(j=1;j<=ans-q[d[i]]+1;j++) tot*=d[i];
					pus=min(pus,tot);
				}
				sh-=min(q[d[i]],ans);
			}
		}
		if(sh)printf("%lld\n",now);
		else printf("%lld\n",now/pus);
		q.clear();
	}
}
```





---

## 作者：KSToki (赞：0)

首先显然如果 $q \nmid p$，答案肯定为 $p$，否则将 $q$ 分解质因数，设当前计算的质因数为 $prime_i$，计算出 $prime_i^k \mid q$ 最大的 $k$，将 $p$ 中 $prime_i$ 的个数除到 $k-1$ 个与答案比较即可。

为了将复杂度，算一半即可，要注意此过程中的特判，~~不然就像我一样自己哪里写爆了都不知道~~。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,prime[32001],tot;
bool vis[32001];
ll p,q;
bool check(int x)
{
	if(x==2)
		return 1;
	
}
int main()
{
    for(register int i=2;i<=32000;++i)
    	if(!vis[i])
    	{
    		prime[++tot]=i;
    		for(register int j=1;j*i<=32000;++j)
    			vis[i*j]=1;
		}
	cin>>T;
    while(T--)
    {
    	cin>>p>>q;
    	if(p%q!=0)
    		cout<<p<<endl;
    	else
    	{
    		ll ans=1;
			for(register int i=1;i<=tot;++i)
    			if(q%prime[i]==0)
    			{
    				ll pr=1,cnt=0,tq=q;
    				while(tq%prime[i]==0)
    				{
    					tq/=prime[i];
    					pr*=prime[i];
					}
					if(pr!=q)
					{
						ll tp=p;
						while(tp%prime[i]==0)
							tp/=prime[i];
						ans=max(ans,p/tp);
					}
					pr/=prime[i];
					ll tmp=p;
					tmp/=pr;
    				while(tmp%prime[i]==0)
    					tmp/=prime[i];
					ans=max(ans,tmp*pr);
				}
			if(ans==1)
			{
				ans=p;
				while(ans%q==0)
					ans/=q;
			}
			cout<<ans<<endl;
		}
	}
    return 0;
}
```


---

## 作者：infinities (赞：0)

给出 $p_i,q_i$，要求找出一个数 $x_i$ 使得 $p_i$ 是 $x_i$ 的倍数，且 $x_i$ 不是 $q_i$ 的倍数，求最大的 $x_i$。

$x_i$ 可以看做从 $p_i$ 的质因数中选出一些。所以若要使 $x_i$ 不是 $q_i$ 的倍数，显然选出一个二者皆有的质因数，然后将 $p_i$ 的这一项因数的次数换成 $q_i$ 的次数减一，其他质因数照搬是最优的。

于是枚举每一个质因数，答案取个 $\max$ 即可。

注意多测清零+不是倍数直接输出 $p_i$ 即可。

code:

```cpp
#include<bits/stdc++.h>
#define int long long
#define rint regester int
const int maxn = 1e6 + 10;
const int INF = 1e9;
using std::ios;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::unique;
using std::lower_bound;
using std::swap;
using std::abs;
using std::acos;
using std::queue;
using std::map;
using std::string;
int read(){int x = 0,f = 1; char ch = getchar(); while(ch < '0' || ch > '9'){if(ch == '-')f = -1; ch = getchar();}while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();} return x * f;}
int t, p, q, ys[maxn], cnt, con[maxn], ans, cn[maxn];
int gcd(int a, int b){
	if(a == 0)return b;
	return gcd(b % a, a);
}
signed main(){
	t = read();
	while(t--){
		int cnt = 0, ans = 0;
		p = read(), q = read();
		int oo = p;
		int g = gcd(p, q);
		if(g != q){
			cout << p << "\n";
			continue;
		}
		for(int i = 2; i * i <= g; i++){
			if(g % i == 0)ys[++cnt] = i;
			while(g % i == 0){g /= i, ++con[cnt];}
		}//算q的质因数
		if(g > 1)ys[++cnt] = g, con[cnt] = 1;//可能剩一个
		for(int i = 1; i <= cnt; i++){
			while(p % ys[i] == 0){
				p /= ys[i], ++cn[i];
			}
		}//计算p对应的质因数
		for(int i = 1; i <= cnt; i++){
			int a = cn[i] - con[i] + 1, pup = 1;
			for(int j = 1; j <= a; j++)pup *= ys[i];
			ans = max(ans, oo / pup);
		}//取max
		cout << ans << "\n";
		for(int i = 1; i <= cnt; i++){
			cn[i] = 0, con[i] = 0;
		}//清零
	}
}

```

---

