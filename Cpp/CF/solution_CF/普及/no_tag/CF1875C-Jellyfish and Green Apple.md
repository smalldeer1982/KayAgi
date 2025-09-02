# Jellyfish and Green Apple

## 题目描述

Jellyfish has $ n $ green apple pieces. Each green apple piece weighs $ 1~\text{kg} $ . Jellyfish wants to divide these green apple pieces equally among $ m $ people.

Jellyfish has a magic knife. Each time Jellyfish can choose one piece of green apple and divide it into two smaller pieces, with each piece having half the weight of the original piece.

Jellyfish wants to know the minimum number of operations needed such that she can divide the green apple pieces such that the total weight of apple pieces received by each person is the same.

## 说明/提示

In the first test case, we do not need to divide the apple pieces. Each person will receive $ 2 $ pieces of $ 1~\text{kg} $ and the total weight of apple pieces received by each person is $ 2~\text{kg} $ .

In the second test case, it is impossible to divide the apple equally using a finite number of operations.

In the third test case, we can divide two of the apple pieces of weight $ 1~\text{kg} $ , getting $ 4 $ apple pieces of weight $ 0.5~\text{kg} $ . Each person will receive $ 1 $ apple piece of weight $ 0.5~\text{kg} $ and $ 2 $ apple pieces of weight $ 1~\text{kg} $ . The total weight of apple pieces received by each person is $ 2.5~\text{kg} $ .

In the fourth test case, we first divide all $ 3 $ of the apple pieces of weight $ 1~\text{kg} $ , getting $ 6 $ pieces of weight $ 0.5~\text{kg} $ . Then, we further divide two of the apple pieces of weight $ 0.5~\text{kg} $ , getting $ 4 $ pieces of weight $ 0.25~\text{kg} $ . Each person will receive $ 1 $ apple piece of weight $ 0.5~\text{kg} $ and $ 1 $ apple piece of weight $ 0.25~\text{kg} $ . The total weight of apples received by each person is $ 0.75~\text{kg} $ .

## 样例 #1

### 输入

```
4
10 5
1 5
10 4
3 4```

### 输出

```
0
-1
2
5```

# 题解

## 作者：One_JuRuo (赞：18)

## 思路

首先我们可以考虑把能分的都先分了，再选择去切剩下的苹果。

那么我们只需要考虑苹果数量少于人数的情况，每个人能分的苹果都必然少于目前的单个苹果，所以每个苹果都必须切一刀，那么答案数就会增加当前的数量，再把能分的都分了，重复这一过程，直到分完为止。这样去切一定是最优的。

那么，什么时候无解呢？

因为如果让苹果数和人数都同时除以某个数时，有没有解应该都一样。

所以可以考虑先除以苹果数和人数的 $\gcd$，那么这时，如果人数不是 $2^k$ 的话，意味着人数拥有某个非二质因子是苹果数没有的，那么无论苹果数怎么平分翻倍，也无法成为人数的倍数，此时无解。

这样的话，对于某个苹果数和人数，人数必然是 $2^k$，那么最多进行 $k$ 次上述操作即可，所以时间复杂度是 $\log m$，完全可以接受。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,m,ans;
inline int lowbit(int x){return x&(-x);}//用于判断是否是二的幂
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		if(lowbit(m/__gcd(n,m))!=m/__gcd(n,m)){printf("-1\n");continue;}//判断无解
		ans=0,n%=m;
		while(n) ans+=n,n*=2,n%=m;//模拟操作
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：cwl769 (赞：6)

首先可以将苹果和人分成若干组，使得每组内苹果数和人数都相同，且每组内苹果数和人数互质。然后考虑单独一组内的情况。

设每组内有 $n_0$ 个苹果和 $m_0$ 个人，那么每个人将分到 $\frac{n_0}{m_0}$ 个苹果。

发现切出的苹果只可能是 $2$ 的非正整数次幂，故若 $m_0$ 不是 $2$ 的非负整数次幂，一定无解。

若有解，考虑将 $n_0$ 二进制分解，即分解为
$$
n_0 = 2^0 \times a_0 + 2^1 \times a_1 + 2^2 \times a_2 + \dots + 2^m \times a_m~(a_i \in \{0, 1\})
$$
那么每人分到的苹果为
$$
\frac{n_0}{m_0} = \sum_{a_i=1}\frac{2^i}{m_0}
$$
对于 $2^i \geq m_0$ 的情况，不需要切。

对于 $2^i < m_0$ 的情况，将分数化为 $\frac{1}{2^t}$ 的形式，需要切 $2^t - 1$ 刀。

计算出一组内需要切的刀数后再乘组数即可得到答案。

### Code

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
typedef long long ll;
typedef long long int64;
inline int gcd(int a, int b)
{
    if(b==0)return a;
    return gcd(b, a%b);
}

int main()
{
    int t;scanf("%d", &t);
    for(;t;--t)
    {
        int n, m;scanf("%d%d", &n, &m);
        int d = gcd(n, m);
        n/=d;m/=d;
        if(m!=(m&(-m)))
        {
            printf("-1\n");
            continue;
        }
        int64 ans = 0;
        for(;n;n-=(n&(-n)))
        {
            int x = (n&(-n));
            if(m>x){ans += 1ll * d * (m/x-1) * x;}
        }
        printf("%lld\n", ans);
    }

    return 0;
}
```

---

## 作者：accgj_ (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1875C)



------------
题目大意：给定 $n$ 个苹果，要分给 $m$ 个人，每次可以选择**一块**苹果平均分成两块（切一刀），问，要平均分配最少要切几刀。



------------
首先有一个贪心的想法：先把已经可以平均分的苹果分了，剩下的再切。

这样要分的 $n$ 就比 $m$ 小了，那么下面就用 $n \bmod m$ 代替 $n$。

如果在这 $n$ 块苹果中，有 $k$ 块都切成两半（即切 $k$ 刀，变成 $n+k$ 块），使 $2k$ 等于 $m$，那么显然剩下的还要继续分的部分，即 $n-k$ ，它们各切一刀之后的 $2n-2k$ 必然小于 $m$，所以我们每次切都可以把当前要分的 $n$ 块都各切一刀，然后模 $m$ ,直到 $n=0$。

这个时候我们就很好知道什么时候无解了： $\frac{m}{\gcd(n,m)} \neq 2^k (k\geq0 ,n>0)$。

很好理解，每次 $n$ 都是增加一个质因子 $2$，而 $\frac{m}{\gcd(n,m)}$ 的质因子与 $n$ 完全不同，那么只有当该条件成立时，才能有解。



------------
代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long n,m;
inline long long gcd(long long a,long long b){return (b==0?a:gcd(b,a%b));}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		n=n%m;
		if(n==0)
		{
			cout<<0<<"\n";continue;
		}
		long long x=gcd(n,m);
		n/=x;m/=x;
		long long x1=(m&-m);
		if(x1!=m)
		{
			cout<<-1<<"\n";continue;
		}
		long long ans=0;
		while(n!=0)
		{
			ans+=n*x;n=((n<<1)&(x1-1));
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：w9095 (赞：3)

[CF1875C Jellyfish and Green Apple](https://www.luogu.com.cn/problem/CF1875C)

我们首先把整块的分完，然后处理剩余的分数块数。

由于我们只能劈成两半，所以约分之后分数的分母只能为 $2$ 的幂，不能包含其他质因数。如果包含，直接输出 `-1`。

我们每次把剩下的块全部劈成两半，统计刀数，直到块数足够分给 $m$ 个人。分给那些人后，让块数减去 $m$，在重复这个过程，直到最后只剩 $0$ 块。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,m;
long long gcd(long long x,long long y)
{
	if(y==0)return x;
	else return gcd(y,x%y); 
}

int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld%lld",&n,&m);
	   	long long num=n%m,ans=0,c=m,d=n%m,k=gcd(c,d);
	   	c/=k;
		while(c%2==0)c/=2;
	   	if(c>1&&n%m!=0)
	   	    {
	   	   	printf("-1\n");
	   	   	continue;
			}
		while(num!=0)
		   {
		   	while(num<m)ans+=num,num*=2;
			num-=m;
		   }
		printf("%lld\n",ans);
	   }
    return 0;
}
```

---

## 作者：MA_tian (赞：1)

本蒟蒻的第一篇题解，求过。

## 解题思路

首先把所有的苹果能分的全部分完，此时的苹果数必定小于人数。如果一个苹果都不剩，皆大欢喜，直接输出 $ 0 $ 。若苹果还有剩余，那么每人可分到的苹果数必定小于此时的一份苹果，也就是需要切割。若当前有 $ k $ 个苹果，每切 $ k $ 刀，就变成 $ ( n + k ) $ 个苹果。

重复上述过程，即可成功分配苹果。

若该情况无解，则 $ n $ 分之 $ m $ 经过约分后的分母必定不等于 $ 2 $ 的幂，直接输出 $ -1 $ 。对于这种情境下的求解就可以用到 $ \operatorname{gcd} $ 函数求最大公因数了。

如此，本题就完结撒花了。

## AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,ans;
int f(int x){
	return x&(-x);
}
int main(){
	cin>>t;
	while(t--){
		ans=0;
		cin>>n>>m;
		if(f(m/__gcd(n,m))!=m/__gcd(n,m)){
			cout<<-1<<endl;
			continue;
		}
		n%=m;
		while(n){
			ans+=n;
			n*=2;
			n%=m;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：BugGod (赞：1)

思路很简单，考虑贪心。

首先我们先把可以整块分的分完，这时候把 $n$ 当成 $n\bmod m$（剩下的）。

接着，我们发现我们只能切两半，所以，我们可以先除以 $n$ 和 $m$ 的 $\gcd$，然后如果这时 $m$ 不为 $2^k$ 的话，无解。

这时，我们只需要模拟即可。如果苹果块数等于人数，就停止。如果小于，就切开。如果大于，就减去人数。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//
int t,n,m,ans;
int check(int x)
{
	return (x&(-x))==x;
}
int gcd(int x,int y)
{
	return y?gcd(y,x%y):x;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		ans=0;
		cin>>n>>m;
		if(!check(m/gcd(n,m)))
		{
			cout<<-1<<endl;
			continue;
		}
		n%=m;
		for(;n;ans+=n,n=(n<<1)%m);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：DerrickLo (赞：1)

首先可以将 $n$ 变成 $n\bmod m$，与原答案相同。

其次我们可以把 $\frac{n}{m}$ 化成一个最简分数，我们容易知道如果化简后的 $\frac{n}{m}$ 是一个无限不循环小数的话那是一定不行的。

而我们又发现 $\frac{1}{5}=0.2$ 转换成 $2$ 进制后是一个无限不循环小数，那么当化到 $(n,m)=1$ 时，$m$ 必须为 $2$ 的正整数次幂。

接着我们可以模拟切的过程，维护一个变量 $num$ 表示剩余饼的数量，从 $n$ 二进制下的高位到低位枚举，对于每一位，如果是 $1$，那么把每块饼切成了两分后取出 $m$ 分给客人们，即 $num\leftarrow num\times 2-m$；如果是 $0$，那么只需要把每块饼切成两分，即 $num\leftarrow num\times 2$，在这个过程中如果 $num\le0$ 那么就表示不能分配，可以在模拟过程中算出答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		n%=m;
		if(n==0){
			cout<<"0\n";
			continue;
		}
		int ans=__gcd(n,m),cnt2=0,cnt5=0,anss=0;
		n/=ans,m/=ans;
		int numm=n;
		while(m%2==0)m/=2,cnt2++;
		while(m%5==0)m/=5,cnt5++;
		if(m!=1){
			cout<<"-1\n";
			continue;
		}
		if(cnt5){
			cout<<"-1\n";
			continue;
		}
		int he=log2(max(n-1,ksm(2,cnt2)-1))+1,flag=1;
		for(int i=he;i;i--){
			if(numm<=0){
				cout<<"-1\n";
				flag=0;
				break;
			}
			if(n&(1<<(i-1))){
				anss+=numm;
				numm=numm*2-ksm(2,cnt2);
			}
			else anss+=numm,numm*=2;
		}
		if(flag)cout<<anss*ans<<"\n";
	}
	return 0;
}

```

---

## 作者：lijianACE (赞：0)

## Jellyfish and Green Apple 题解  

通过证明：  
![](https://cdn.luogu.com.cn/upload/image_hosting/h1bqg9db.png)   

[洛谷传送门](https://www.luogu.com.cn/problem/CF1875C)  

[CF传送门](https://codeforces.com/problemset/problem/1875/C)  

题目解析：给定一个 $n$ 和 $m$，让你用上面给的方式分完并输出最小需用的刀数，不能分完输出 $-1$。  

题意看起来有点复杂，毕竟要输出最小方案。但其实你只需看一眼难度：  
> 普及/提高-  

这么低难度，贪心无疑。 

思考下就会发现，如果现有苹果分完了，那可太棒了，不用切了，直接输出。  

如果有剩余呢？可以先把手上的苹果能分的分完，剩下的每个苹果切一半，这样就省去了不必要的刀数。  

接下来是本问题的核心：如何判定有无解？  

若你仔细思考，就会发现：每次苹果的份数都会少一半，即乘以 $ \frac{1}{2} $，最后每个人的份数的分母肯定是 $2^k$ 的，即 $ \frac{n}{m} $ 约分后的分母为 $2^k$，也就是 $ \frac{m}{\gcd(m,n}=2^k $，所以只需判断是否是 $2$ 的次幂就行了，加上程序用的是二进制，判断更容易。  

复杂度分析：分苹果时设 $\frac{m}{\gcd(m,n}=2^k$，即进行 $k$ 次操作，复杂度 $O( \log_{2}{m})$。这复杂度哪里大了，这复杂度可太棒了

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
ll t,n,m;
ll lowbit(ll a){return a & (-a) ;}//用二进制的方式巧妙的避免了计算次幂
int main(){
    scanf("%lld",&t);
    while (t--){
        scanf("%lld%lld",&n,&m);
        if(m/__gcd(m,n)!=lowbit(m/__gcd(m,n))) printf("-1\n");
        else{
            ll ans=0;
            n=n%m;
            while (n){
                ans+=n;
                n=n*2;
                n=n%m;
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}
```
题解写的不是很好，望谅解！  

如果有误，敬请指导。  

QWQ

---

## 作者：qusia_MC (赞：0)

**很简单。**
# 分析
有 $n$ 个苹果要**平均**分给 $m$ 个人，每次可以选择一个苹果切一刀（切成两块）求平均分要切几刀。
# 思路
首先，看见分析里加点的字了吗？既然是平均，那么很容易想到几点：

- 考虑贪心，就是能分的话就尽量把能分的都分了（不能让他们饿到）。

- 如果要切，则所有苹果都要切一刀。如果不切，则所有苹果都不切。（这样才能保障每个人分的一样多）。

接下来判断无解的情况。

首先先把整个的能分都分了。然后把 $n,m$ 通分，接着看看如果苹果数不是 $2^k(k\in \mathbb{N^+})$ 也就是 $2$ 的整数幂，通俗的表达，若存在任意一个 $k$ 使得 $2^t\times k=m$ 且 $k≠1$。$n$ 个苹果切后只能是每一个“分裂”成两个，利用运算律我们简化成了，每一次切都能让苹果的总数 $\times 2$。

所以无论怎么切都只能是 $2$ 的整数幂个苹果，如果 $m≠2^k$，则无解。

接下来直接模拟就能过。
# code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long//10年OI一场空，不开ll见祖宗！！！
signed main()
{
	int T,n,m,gcd;
	cin>>T;//数据组数
	while(T--)
	{
		cin>>n>>m;
		
		if(n>=m)n%=m;//能分就分
		gcd=__gcd(n,m);//STL库函数。
        int ans=0,n2=m/gcd;//建一个替身，由于只需要判断m和n没关系。
        while(n2%2==0)n2/=2;//除2
        if(n2!=1)cout<<"-1"<<'\n';//不是1，还有其他因数
        else
        {
            while(n)//还没分完
		    {
                ans+=n;//每个苹果都要切1刀！！！！
		    	n*=2;//切完了
		    	n%=m;//分
		    }
		cout<<ans<<'\n';//'\n'比printf("\n")快很多
        }
	}
	return 0;
}
```

---

## 作者：fchwpo (赞：0)

很显然可以想到，每个人分到的苹果要么是整数要么是 $\frac{x}{2^{y-1}}$ 的模式所以无解应该很好判断，然后我们在考虑如何计算答案，由于已经知道有多少个苹果了所以只要苹果能分的话我们就分给每个人，否则的话我们就给所有苹果切一刀，然后再分，证明一下，这其实就相当于给分数形式分子分母都放大了，如果每个人都收到了等量的 $\frac{1}{2^{y-1}}$ 这样就保证了正确性，最优的话因为每个人都收到一样的份数，所以当你要切时必然不可能只切一部分否则就证明上回切少了对吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
map<int,int>mp;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int i=0;i<=30;i++) mp[1<<i]=1;
	int t;
	cin >>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		int nn=n,mm=m;
		int now=__gcd(n,m);
		if(!mp[m/now]){
			cout<<"-1"<<'\n';
			continue;
		}
		int ans=0;
		nn%=m;
		while(nn){
			ans+=nn;
			nn*=2;
			if(nn>=m) nn%=m;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

