# [ABC272G] Yet Another mod M

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc272/tasks/abc272_g

長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。ここで $ A $ の全ての要素は相異なります。

あなたは $ 3 $ 以上 $ 10^9 $ 以下の正整数 $ M $ を選び、以下の操作を $ 1 $ 回だけ行います。

- $ 1\ \le\ i\ \le\ N $ を満たす整数 $ i $ に対し、$ A_i $ を $ A_i\ \bmod\ M $ で置き換える。

うまく $ M $ を選ぶことで、操作後の $ A $ を以下の条件を満たした状態にすることができますか？ できるのであれば、そのような $ M $ を $ 1 $ 個求めてください。

- ある整数 $ x $ が存在して、$ x $ が $ A $ の過半数を占める。

ここで、整数 $ x $ が $ A $ の過半数を占めるとは、$ A_i\ =\ x $ を満たす整数 $ i $ の個数が $ A_i\ \neq\ x $ を満たす $ i $ の個数より多いことを言います。

## 说明/提示

### 制約

- $ 3\ \le\ N\ \le\ 5000 $
- $ 1\ \le\ A_i\ \le\ 10^9 $
- $ A $ の全ての要素は相異なる
- 入力はすべて整数

### Sample Explanation 1

$ M=7 $ として操作を行うと、$ A=(3,3,1,0,3) $ となり $ 3 $ が $ A $ の過半数を占めるため $ M=7 $ は条件を満たします。

## 样例 #1

### 输入

```
5
3 17 8 14 10```

### 输出

```
7```

## 样例 #2

### 输入

```
10
822848257 553915718 220834133 692082894 567771297 176423255 25919724 849988238 85134228 235637759```

### 输出

```
37```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9 10```

### 输出

```
-1```

# 题解

## 作者：Miraik (赞：8)

第一次赛时秒了G，有点感动兄弟。

考虑如果我一个数 $a_i$ 在答案集合里，且模数为 $m$，那么对于集合里的所有数 $a_j$，均有 $m \mid a_i-a_j$。

由于答案集合的大小超过 $\frac{n}{2}$，因此我们随机 $30$ 次 $a_i$ ~~，错误的概率比你现在一秒后当场暴毙还低~~。

但是现在我们知道了 $a_i$，怎么找到这个 $m$ 呢？很简单，由于答案集合的大小超过 $\frac{n}{2}$，因此我们再随机 $30$ 次 $a_j$，再对 $|a_i-a_j|$ 分解质因数，判断每个质因数能否成为 $m$ 即可。

~~总结：绝对众数 = 随机。~~

总时间复杂度 $O(T^2 n \log V)$，$T$ 为随机次数，我写的取 $T=30$。

代码：

```cpp
mt19937 rnd(10086001);
void solve(int base,int x){
	for(int i=1;i<=n;i++) b[i]=abs(a[i]-base);
	x=b[x];
	for(int i=3;i*i<=x;i++){
		if(x%i==0){
			while(x%i==0) x/=i;
			int ok=0;
			for(int j=1;j<=n;j++)
				ok += (b[j]%i==0);
			if(ok*2>n){
				printf("%d\n",i);
				exit(0);
			}
		}
	}
	if(x>2){
		int ok=0;
		for(int j=1;j<=n;j++)
			ok += (b[j]%x==0);
		if(ok*2>n){
			printf("%d\n",x);
			exit(0);
		}
	}
}
main(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1);
	uniform_int_distribution<int>lim(1,n);
	for(int t1=1;t1<=30;t1++){
		int p = lim(rnd);
		for(int t2=1;t2<=30;t2++) solve(a[p],lim(rnd));
	}
	puts("-1");
}
 
```


---

## 作者：Caiest_Oier (赞：4)

# [AT_abc272_g](https://www.luogu.com.cn/problem/AT_abc272_g)    

很容易发现，如果 $A_i\bmod X=A_j\bmod X$，则 $(A_i-A_j)\bmod X=0$，并且因为答案集合大于一半，所以随机若干对 $i$ 和 $j$，取差，答案模数在因数中期望出现次数大于 $\frac{1}{4}$ 倍次数，所以随机 $200$ 组 $i$ 和 $j$，统计每个数出现次数，对出现次数大于 $40$ 次的 check 即可。另外，如果随机到两个数相等，需要全局 $+1$。  

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[500003];
int stk[7000003],tot,k1,k2,k3,sum;
map<int,int>mp;
map<int,int>mp2;
bool chk(int X){
	mp2.clear();
	for(int i=1;i<=n;i++)mp2[a[i]%X]++;
	for(int i=1;i<=n;i++){
		if(mp2[a[i]%X]*2>n)return true;
	}
	return false;
}
int main(){
	srand(time(0));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=200;i++){
		do{
			k1=(rand()%n)+1;
			k2=(rand()%n)+1;
		}while(k1==k2);
		k3=abs(a[k1]-a[k2]);
		if(k3==0)sum++;
		for(int j=1;j*j<=k3;j++){
			if(k3%j==0){
				mp[j]++;
				stk[++tot]=j;
				if(j*j!=k3){
					mp[k3/j]++;
					stk[++tot]=k3/j;
				}
			}
		}
	}
	for(int i=1;i<=tot;i++){
		if(stk[i]<3)continue;
		if(mp[stk[i]]+sum<40)continue;
		mp[stk[i]]=-2147483;
		if(chk(stk[i])){
			printf("%d",stk[i]);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
```
upd：似乎取两百个不太够，有一定的概率错，本人用 RMJ 交了一下出了个 WA：[link](https://atcoder.jp/contests/abc272/submissions/45019859)

---

## 作者：Rubidium_Chloride (赞：4)

vp 的时候做这个题。

做完以后发现做法和 User's Editorial 重了！！

来这里介绍一下做法。

以下称原数为 $w_i$。

首先我们考虑一种特殊情况，$n\equiv 1\pmod 2$，我们可以选取 $1,3,5\dots n$ 这些位置。

这个时候只要判断 $\gcd(w_3-w_1,w_5-w_3,\dots w_n-w_{n-2})$ 是否为满足条件的 $m$ 就可以了。

然后除了这种情况可以保证**最后选取的大部分数中有两个相邻**。

所以我们枚举这个相邻的数对 $(w_i,w_{i+1})$，可以知道选取的 $m$ 为 $w_{i+1}-w_{i}$ 的约数。

然后再发现一部如果一个 $m$ 满足那么他比 $2$ 大的约数也满足。

所以我们可以只考虑所有素因子。

但是注意 $m\equiv 0\pmod 2$ 的时候我们不能选取 $2$ 而是要判断 $4$ 是否整除 $m$。如果成立，选取 $4$。

然后检查的过程是可以用 $\mathcal{O}(n)$ 的时间完成的。

实现的比较烂，总复杂度就是 $\mathcal{O}(\sqrt{V}+n(\sqrt{V}+\omega n))$。

$V$ 是值域 $\omega$ 是值域内含有最多的素因子数，大概是 $8$ 或者 $9$。

代码实现：

```
#include<bits/stdc++.h>
#define N 100009
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef long long ll;
inline ll read() {
    ll x=0,f=1;int c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
ll n,m,w[N],cnt,pr[N],vst[N],tot;
vector<ll> fac;
void init(ll n){
    for(int i=2;i<=n;i++){
		if(!vst[i]) pr[++cnt]=i;
		for(int j=1;j<=cnt&&i*pr[j]<=n;j++){
            vst[i*pr[j]]=1;
            if(i%pr[j]==0) break;
        }
	}
}
ll gcd(ll x,ll y){if(x<0) x=-x;if(y<0) y=-y;return (y==0)?x:gcd(y,x%y);}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=read(),init(100000);for(int i=1;i<=n;i++) w[i]=read();
    if(n&1){
        m=w[3]-w[1];
        for(int i=3;i<n;i+=2) m=gcd(m,w[i+2]-w[i]);
        if(m>=3){printf("%lld\n",m);return 0;}
    }
    for(int i=1;i<n;i++){
        ll x=w[i+1]-w[i];
        fac.clear();
        for(int j=1;j<=cnt;j++){
            if(!(x%pr[j])){
                if(pr[j]==2){if(!(x%4)) fac.push_back(4);}
                else fac.push_back(pr[j]);
            }
            while(!(x%pr[j])) x/=pr[j];
        }
        if(x>1) fac.push_back(x);
        for(int j=0;j<fac.size();j++){
            m=fac[j],tot=0;
            for(int p=1;p<=n;p++) tot+=((w[p]%m)==(w[i]%m));
            if(tot*2>n){printf("%lld\n",m);return 0;}
        }
    }
    printf("-1\n");
    return 0;
}
```

---

## 作者：翼德天尊 (赞：3)

一看有取模又想到了根号分治（md 这人魔怔了），但事实上没有什么性质可以让我们这么干。

那这题都有什么性质呢？

1. $a_i\bmod M=a_j\bmod M\Rightarrow a_i\equiv a_j\Rightarrow (a_i-a_j)\ |\ M$

2. 对于一个合法的 $M$，有超过一半的数同余 $\Rightarrow$ 我们任意选择两个数，有至少 $\frac{1}{4}$ 的概率同余。

3. 对于一个大于 $2$ 的质数 $p_i$ 和一个合数 $p_is$，如果模数 $p_is$ 能够满足条件，则 $p_i$ 也一定可以。

结合这些优良的性质，我们便首先可以设计出一个随机化算法。对于每次随机，我们可以随机两个下标 $i,j$，将 $|a_i-a_j|$ 求出后找到它的所有质因数，对于每个质因数 check 一遍整个数组，那么单次随机的时间复杂度就是 $O(n\sqrt{A})$，其中 check 部分可以 $O(n)$ 解决（可以先 $O(n)$ 找到一个满足必要性的余数，再 $O(n)$ 判断该余数的充分性）。随机十次正确率便有 $95\%$ 左右了。

但是这毕竟是个随机化算法，有没有什么正经的算法呢？

我们还可以注意到一个性质：

4. 对于长度为偶数的数组，如果存在模数解 $M$，则一定存在两个相邻的 $a$ 在模 $M$ 意义下同余；对于长度为奇数的数组，则另存在一种只选奇数位置上的数的情况。

对于后者我们可以进行特殊判断，找到所有奇数位置上的相邻两个数之差的最大公因数，如果大于等于 $3$ 则有解。

对于前者，我们可以处理出 $\forall i\in [1,n-1),|a_i-a_{i+1}|$ 的所有不同的质因数。又由于 $1e9$ 以内的数最多有 $10$ 个左右不同的质因子，所以总质因子个数是 $O(n)$ 级别的。处理完之后再将每个质因子 check 一遍即可，时间复杂度 $O(n^2)$，有一个 $10$ 左右的常数。（注意特殊处理 $2$，可以将 $2$ 变成 $4$）

还是有些妙的。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
#define st set<int>::iterator
const int N=5005;
int n,a[N];
set<int> h;
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
bool check(int x){
	int cnt=0,now=0;
	for (int i=1;i<=n;i++){
		if (cnt==0) now=a[i]%x,++cnt;
		else if (a[i]%x!=now) --cnt;
		else ++cnt;
	}
	if (cnt){
		cnt=0;
		for (int i=1;i<=n;i++)
			if (a[i]%x==now) ++cnt;
		if (cnt>n/2) return 1; 
	}
	return 0;
}
int gcd(int x,int y){
	if (y==0) return x;
	return gcd(y,x%y);
}
signed main(){
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	if (n&1){
		int now=abs(a[3]-a[1]);
		for (int i=5;i<=n;i+=2)
			now=gcd(now,a[i]-a[i-2]);
		if (now>=3){
			cout<<now<<'\n';
			return 0;
		}
	}
	for (int i=1;i<n;i++){
		int x=abs(a[i]-a[i+1]);
		if (x%4==0) h.insert(4);
		for (int j=2;j*j<=x;j++){
			if (x%j==0){
				if (j>2) h.insert(j);
				while (x%j==0) x/=j;
			}
			if (x!=1) h.insert(x);
		}
	}
	for (st it=h.begin();it!=h.end();it++)
		if (check(*it)){
			cout<<*it<<'\n';
			return 0;
		}
	puts("-1");
	return 0;
}
```

---

## 作者：Mine_King (赞：3)

[在我的博客获得更好的阅读体验](https://www.cnblogs.com/mk-oi/p/abc272g.html)

## Problem

[ABC272G Yet Another mod M](https://www.luogu.com.cn/problem/AT_abc272_g)

**题目大意：**

给出一个长度 $N$ 的序列 $A$，其中 $A_i$ 均为正整数且互不相同。

你需要选择一个范围在 $[3,10^9]$ 的正整数 $M$，并执行一次下列操作：

- 将序列上的所有数替换为 $A_i \bmod M$。

若能找到一个数 $M$ 使得序列中存在一个数 $x$，且满足 $A_i=x$ 的数量大于 $A_i \not= x$ 的数量，输出这个 $M$。

## Solution

人类智慧题。

随机选择两个数，钦定他们 $\bmod M$ 后相等，则 $M$ 为这两个数的差的因数。枚举 $M$ 然后判断是否合法。

看着很不对劲？尝试求每次随机得到符合要求的 $M$ 的概率。

因为 $A_i=x$ 的数的数量严格大于二分之一，所以第一次随到 $A_i=x$ 的 $i$ 的概率是 $\dfrac{1}{2}$，第二次也是 $\dfrac{1}{2}$，所以每次随机能随到正确答案的概率为 $\dfrac{1}{4}$。

所以只需要随机很少次就可以得到正确答案。保险起见可以随机 $200$ 次，复杂度为 $O(\sqrt{A}\cdot n)$。

## Code

```cpp
//Think twice,code once.
#include<map>
#include<ctime>
#include<cmath>
#include<random>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[5005],b[5005];
mt19937 gen(time(0));
int check(int x)
{
	int num=0;
	for(int i=1;i<=n;i++) num+=(b[i]%x==0);
	return num>n/2;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int Case=1;Case<=200;Case++)
	{
		int p1=gen()%n+1,p2;
		for(int i=1;i<=n;i++) b[i]=abs(a[p1]-a[i]);
        //随机第一个数并求他和所有数的差，求差之后判断是否符合要求只需要看差 mod M 是否等于 0 即可。
		do p2=gen()%n+1;
		while(p1==p2);//随机第二个数
		for(int j=1;j*j<=b[p2];j++)
			if(b[p2]%j==0)//枚举差的因数
			{
				if(j>2&&check(j)){printf("%d\n",j);return 0;}
				if(b[p2]/j>2&&check(b[p2]/j)){printf("%d\n",b[p2]/j);return 0;}
			}
	}
	puts("-1");
	return 0;
}
```



---

## 作者：CZH_63_HR (赞：1)

# G-Yet Another mod M

OK，这是我做过的第一个和随机数有关的题目，但目前我只会官方题解的做法

题目描述：给你一个长度为 $N \in [3,5000] $ 的序列 $a$，让你选择一个数 $M \in [3,10^9]$，使 $a$ 中的每个数去分别被取模，得到另一个数组 $b$，使里面有一个绝对众数。(感觉讲得好含糊)

### 做法:

既然是绝对众数，那么在数组中选的任意一个数会在最终的众数里面的概率都至少是 $\frac{1}{2}$，选两个在里面的概率则至少是 $\frac{1}{4}$。所以我们可以随机选两个数很多次，这个很多次可以看具体情况而定，比如 $100$ 次循环。每次选错的概率为 $ \frac{3}{4} $，$100$ 次就是 ${\frac{3}{4}}^{100}$ ，用计算器算出来概率大约是 $ 10^{-13} $，几乎为零，因此算法可行性是有的。

在选好两个随机数后，我们就需要判断是否合法。因为选出的两个数的余数是相同的，即 $ x \equiv y \pmod M $，因此可以得到 $ | x - y | \bmod M = 0 $。所以我们只需要 $ O(\sqrt{| x - y |}) $ 的时间枚举 $ | x - y | $ 的因数。但是注意题目中的 $ M \ge 3 $，因此小于 $3$ 因数的要排除。

然后我们把这个因数放到 $ a $ 数组里面去一个一个模，把模出来的数字记录下来，比如用 `map` ，假如有一个数字的个数大于 $n/2$ 那么就是合法的，直接输出；如果循环完一百次后还没有合法的数那么就输出 $-1$。

总共的复杂度是 $ O(N \log{N} \sqrt{x} \times 100) $，但是因为一个数的因数不会超过 $ \ln{x} $，因此复杂度就成了 $ O(N \log{N} \ln{x} \times 100) $，完全可以过。

~~几乎把官方题解翻译了一遍~~

代码如下：
```c++
#include <bits/stdc++.h>
using namespace std;
const int N=5005;
int n,a[N];
map <int,int> mp;
int main()
{
	srand(time(NULL));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int o=1;o<=50;o++)
	{
		int x=1ll*rand()*rand()%n+1,y=1ll*rand()*rand()%n+1;
		while(x==y) y=1ll*rand()*rand()%n+1;
		int d=abs(a[x]-a[y]); int sd=sqrt(d);
		for(int i=1;i<=sd;i++)
		{
			if(d%i==0)
			{
				if(i>2)
				{
					for(int j=1;j<=n;j++)
						mp[a[j]%i]++;
					for(auto j:mp)
						if(j.second>n/2)
							return printf("%d\n",i),0;
					mp.clear();
				}
				if(d/i>2)
				{
					for(int j=1;j<=n;j++)
						mp[a[j]%(d/i)]++;
					for(auto j:mp)
						if(j.second>n/2)
							return printf("%d\n",d/i),0;
					mp.clear();
				}
			}
		}
	}
	puts("-1");
	return 0;
}

```

OK，就做完了~

---

## 作者：Polarisx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc272_g)。

[双倍经验](https://www.luogu.com.cn/problem/P6817)。

不难发现在序列里随机一个数，它在答案集合中的概率大于 $\frac{1}{2}$，我们不妨随机 $t=20$ 次，假设位置为 $i$，若 $i,j$ 均在答案集合中，那么有 $M\mid |A_i-A_j|$，对于每个 $j$，分解质因子 $|A_i-A_j|$，最后查找哪个质因子出现次数最多（除去 $2$），注意特判 $4$ 的情况。

时间复杂度 $\mathcal O (\frac{tn\sqrt V}{\ln V})$。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn=1e5+6,N=1e5;
int n,a[Maxn];

bitset<Maxn>isp;
vector<int>prm;

void work(){
    map<int,int>mp1,mp2;
    int x=rand()%n+1;
    int g=0;
    for(int i=1;i<=n;i++){
        int y=abs(a[i]-a[x]);
        if(!y){g++;continue;}
        if(y%4==0) mp2[4]++;
        while(!(y&1)) y/=2;mp1.clear();
        for(auto j:prm){
            if(1ll*j*j>y) break;
            if(!(y%j)) mp1[j]=1;
            while(!(y%j)) y/=j;
        }
        if(y>2) mp1[y]=1; 
        for(auto j:mp1) mp2[j.first]++;
    }
    for(auto j:mp2) if(j.second+g>n/2){printf("%d",j.first);exit(0);}
}

int main(){
    srand(19260817);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);

    for(int i=2;i<=N;i++)
        if(!isp.test(i)){
            prm.emplace_back(i);
            for(int j=i+i;j<=N;j+=i) isp.set(j);
        }
    for(int t=1;t<=20;t++) work();
    puts("-1");

    system("pause");
    return 0;
}
```

---

## 作者：Raisetsu41 (赞：0)

考虑从集合里面抽出来两个元素，则他们两个差有一定概率是这个 $M$ ，这取决于这两个数是不是在这个模意义下相同的集合，很明显，如果 $M$ 满足条件，则 $M$ 的因数也满足，那么就用这个差值和这两个数去掉余数之后的值做差就可以了。   
如果全部枚举则检验复杂度是 $\Theta(n^3)$ 的，因为这个东西性质很强，我们每次抽取两个元素，都在满足要求的集合里面的概率最小是 $\frac{1}{4}$ ，那么多随几次就行了。

---

## 作者：TernaryTree (赞：0)

考虑枚举数列中的两个数 $A_i,A_j$，钦定他们模 $M$ 同余，那么有

$$|A_i-A_j|\equiv 0\pmod M$$

则 $M$ 是 $|A_i-A_j|$ 的 $\ge 3$ 的一个因子。枚举因子，然后暴力扫一遍看看符不符合条件。但是这样时间复杂度是 $\Theta(n^3\log n)$ 的。

怎么优化呢？一个数在答案众数里面的概率大约是 $\dfrac12$。两个数都在的概率是 $\dfrac14$。也就是说，出错的概率是 $\dfrac34$。如果枚举了 $100$ 组，那么错误率为 $\left(\dfrac34\right)^{100}\approx3.2\times 10^{-13}$，这个概率非常小，所以我们枚举 $100$ 组就行了。怎么枚举呢，随机找。时间复杂度 $\Theta(tn\log n)$，其中 $t$ 是枚举组数，此处取 $100$，显然可以过。算上 `map` 的复杂度也没事。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 5e3 + 1;
const int mod = 19260817;
typedef map<int, int> mp;

int n;
int a[maxn];
mp cnt;

void ins(int x) {
	if (cnt.find(x) == cnt.end()) cnt[x] = 1;
	else cnt[x]++;
}

bool check(int m) {
	cnt.clear();
	for (int i = 1; i <= n; i++) {
		ins(a[i] % m);
	}
	for (mp::iterator i = cnt.begin(); i != cnt.end(); ++i) {
		if (i->second * 2 > n) return true;
	}
	return false;
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> range(1, n);
	int loop = 0;
	while (loop <= 100) {
		int x = range(rnd), y = range(rnd), d;
		if (x == y) continue;
		d = fabs(a[y] - a[x]);
		for (int i = 1; i * i <= d; i++) {
			if (d % i == 0) {
				if (check(i) && i >= 3) {
					cout << i << " ";
					return 0;
				}
				if (check(d / i) && d / i >= 3) {
					cout << d / i << " ";
					return 0;
				}
			}
		}
		++loop;
	}
	puts("-1");
	return 0;
}

---

