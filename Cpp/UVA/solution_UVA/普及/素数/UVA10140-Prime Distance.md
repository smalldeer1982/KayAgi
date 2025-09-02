# Prime Distance

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1081

[PDF](https://uva.onlinejudge.org/external/101/p10140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/7fac8d7bdf18ec6e0fd2914c1623eee77be89ef3.png)

## 样例 #1

### 输入

```
2 17
14 17```

### 输出

```
2,3 are closest, 7,11 are most distant.
There are no adjacent primes.```

# 题解

## 作者：Siyuan (赞：23)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[UVa 10140](https://www.luogu.org/problemnew/show/UVA10140)

给定区间 $[L,R]$，求这个区间中相邻的两个质数的差的最小值和最大是分别是多少，并输出对应的 $2$ 个质数（多组数据）；如果没有则输出 `There are no adjacent primes.`。

数据范围：$1\le L<R<2^{31}$，$R-L\le 10^6$

------

## Solution

首先我们发现：$R-L$ 的范围很小，我们应该要能够快速求出 $L\sim R$ 之间的质数。

显然有推论：任意一个合数 $x$ 必定包含一个不超过 $\sqrt x$ 的质因子。

所以我们可以筛出 $[1,\sqrt R]$  之间的所有质数，对于每个质数 $p$，把 $[L,R]$ 中能被 $p$ 整除的数标记为合数。最终没有被标记的数就是质数，对相邻的质数两两比较，找出差值最小和最大的即可。

**时间复杂度**：$O(\sum_{p\le \sqrt R}\frac{R-L}{p})=O(\sqrt R\log^2\sqrt R+(R-L)\log^2 R)$（该复杂度摘自：李煜东《算法进阶指南》）

------

## Code

```cpp
#include <cstdio>
#include <cstring>

const int N=1e6+5;
int tot,p[N];
bool flg[N],vis[N];

void init() {
    for(int i=2;i<N;++i) {
        if(!flg[i]) p[++tot]=i;
        for(int j=1;j<=tot&&i*p[j]<N;++j) {
            flg[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
}
void chkmin(long long &x,long long a,long long b,long long &p1,long long &p2) {
    if(x>b-a) x=b-a,p1=a,p2=b;
}
void chkmax(long long &x,long long a,long long b,long long &p1,long long &p2) {
    if(x<b-a) x=b-a,p1=a,p2=b;
}
int main() {
    init();
    long long l,r;
    while(~scanf("%lld%lld",&l,&r)) {
        memset(vis,1,sizeof(vis));
        if(l==1) vis[0]=0;
        for(int i=1;i<=tot;++i) {
            for(long long j=l/p[i];j*p[i]<=r;++j) {
                long long x=p[i]*j;
                if(j>1&&x>=l) vis[x-l]=0;
            }
        }
        long long p=0,p1,p2,p3,p4,mn=1LL<<60,mx=0;
        for(long long i=l;i<=r;++i) {
            if(!vis[i-l]) continue;
            if(p) chkmin(mn,p,i,p1,p2),chkmax(mx,p,i,p3,p4);
            p=i;
        }
        if(!mx) puts("There are no adjacent primes.");
        else printf("%lld,%lld are closest, %lld,%lld are most distant.\n",p1,p2,p3,p4);
    }
    return 0;
}
```



---

## 作者：aha浮云 (赞：20)

用了个较慢的方法
可以线性直接筛到O(sqrt（n））
不过当时没想到
Miller Rabin 算法
不知道的可以去百度一下
理论差一个数是否是素数用时是log级别的
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long tryit( int a, int b, int c){return 	( (long long)( a % c) * ( b % c))%c;} 
bool vis[10000005]; // 用来标记是否为质数
int F[1000005];//用来查找差最小的和最大的
int fast_pow(int a,int b,int c) //快速幂....
{
    int ans = 1 % c;
    for(;b;b>>=1) 
    {
        if(b&1) ans = (long long) ans * a % c;
        a=(long long) a * a % c;
    }
    return ans;
}
bool check (int cur)  //***Miller Rabin算法 不知道的最好去百度一下
{
    if( cur == 2)
    return true;
    long long sum=1,cnt=0;
    if( cur < 2|| !(n&1)) return false; 
    int temp = cur - 1;
    int part = cur - 1;
    while( part % 2 == 0){
        part /= 2; 
        cnt++;
    }
    for(int i = 1; i <= 10; i++)
    {
        int a= rand() % (n-1) + 1; 
        int x=fast_pow(a,part,n);
        for(int j = 1; j <= cnt; j++)
        {
            long  long y = tryit(x,x,n);
            if( y == 1 && x != 1 && x != n-1)
            return false;
            x=y;
        }
        if(x!=1) return false;
    }
    return true;
}
int main()
{
    /*cin>>n;
    if(check(n)) printf("YES\n");
    else printf("NO\n");
    */
    int L,R;
    while(~scanf("%d%d",&L,&R))
    {
    	memset(vis,0,sizeof(vis));
    	int ans=0;
    	for(long long i = L ;i <= R; i++)
    	{
    		n=i;
    		if( vis[i-L] == true) continue; 
    		if( check(i) )
            {
                long long l = i + i;
                while(l<=R)
                {
                    vis[l-L] = true;//对其倍数标记
                    l+= (long long) i;
                }
        	}
        	else vis[i-L] = true;
    	} // 查是否是素数
    	int top=0;
    	for(int i=0 ; i <= R-L ; i++)
    	if( !vis[i] ) 
    	F[++top] = i+L ;
    	int flag=1;
    	long long  Min = 1e8,num=0,num1=0,Max = 0;
    	for(int i=2 ;i <= top; i++)
    	{
    		if( F[i] - F[i-1] < Min) 
            {
                flag=0;
                num = i;
                Min = F[i] - F[i-1];
    		}
    		if( F[i] - F[i-1] > Max)
    		{
    			flag=0;
    			num1 = i;
                Max = F[i] - F[i-1]; 
    		}
    	}//差最小的和差最大的
    	if(!flag) // flag用来判断是否存在
        printf("%d,%d are closest, %d,%d are most distant.\n", F[num-1] , F[num] , F[num1-1] , F[num1] );
        else printf("There are no adjacent primes.\n");
    }
    return 0;
}
```

---

## 作者：AcRapper (赞：13)

### 思路：筛出整数范围的素数，然后对于区间[l,r]，枚举范围合法的素数，标记出他们的整数倍。显然，被标记出的就是区间[l,r]中的合数。再暴力枚举剩下的素数，即可得出答案。

~~我是不会告诉你们这个题线性筛跑的比埃氏筛要慢的~~
********
上代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define ll long long
#include<map>
using namespace std;
const int maxn=10000005;
bool p[maxn];
long long v[maxn],prime[maxn],l,r,m,a[maxn];
void pri(int n)//线性筛
{
	memset(v,0,sizeof(v));
	 m=0;
	for(int i=2;i<=n;i++)
	{
		if(v[i]==0)
		{
			v[i]=i;
			prime[++m]=i;		}
		for(int j=1;j<=m;j++)
		{
			if(prime[j]>v[i]||prime[j]>n/i)break;
			v[i*prime[j]]=prime[j];
		}
	}
}
int main()
{ 
	pri(5e4+10);//求出int范围内的素数（可能是int范围吧）
	while(cin>>l>>r ){
	memset(p,0,sizeof(p));//一定要记得每次操作前memset，蒟蒻因为这个wa了一晚上（感觉蠢炸）
	if(l==1)l=2;
	for(ll j=1;j<=m;j++)
	{
		for(ll i=l/prime[j];i<=r/prime[j];i++)//
		{
			while(i<=1)i++;//处理i<1的情况防止乘以0
			if(prime[j]*i<l||prime[j]*i>r)continue;
			p[prime[j]*i-l]=1;//标记合数，后面会把l加回来，这样操作可以保证数组够用（或者你也可以map<int,int>）
		}		
	}
	ll cnt=0,min1,min2,max1,max2,minn=0x3f3f3f3f,maxx=-0x3f3f3f3f;
	for(ll i=l;i<=r;i++)
		if(p[i-l]==0)//如果不是合数
			a[++cnt]=i;//记录下来
	if(cnt<=1){cout<<"There are no adjacent primes."<<endl;continue;}//素数<=1（不成对）
	for(ll i=1;i<=cnt-1;i++)//暴力枚举
	{
		if(a[i+1]-a[i]<minn)minn=a[i+1]-a[i],min1=a[i],min2=a[i+1];
		if(a[i+1]-a[i]>maxx)maxx=a[i+1]-a[i],max1=a[i],max2=a[i+1];
	}
	cout<<min1<<","<<min2<<" "<<"are closest,"<<" "<<max1<<","<<max2<<" are most distant."<<endl;
}
return 0;
}
```
### 总结，这是一道求区间内素数的模板题，能够加深对于筛法求素数算法的理解。


---

## 作者：WLR__jr (赞：7)

******L,R的范围很大，但是R-L的值很小。
                                                  
    所以只需要用筛法求出2~根号R之间的所有质数。对于每个质数p，把[L,R]中能被p整除的数标记为合数

-----华丽丽的分鸽线（鸽子：喵喵喵？？）-------

最终所有未被标记的数就是[L,R]中的质数，相邻的质数两两比较，找出最大的差即可。
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool v[1000001];
long long b[1000001],a[1000001],n;
int main()
{
	n=0;
	memset(v,true,sizeof(v));
	for(long long i=2;i<=50000;i++)
	{
		if(v[i])a[++n]=i;
		for(long long j=1;j<=n&&i*a[j]<50000;j++)
		{
			v[i*a[j]]=false;
			if(i%a[j]==0)break;
		}
	}
	long long l,r;
	while(scanf("%lld%lld",&l,&r)!=EOF)
	{
		memset(v,true,sizeof(v));
		if(l==1)v[0]=false;
		for(long long i=1;i<=n;i++)
		{
			for(long long j=l/a[i];j<=r/a[i];j++)
			{
				if(j>1)v[a[i]*j-l]=false;
			}
		}
		long long m=0;
		for(long long i=l;i<=r;i++)if(v[i-l])b[++m]=i;
		long long minn=2147483647,maxn=0;
		long long x1,y1,x2,y2;
		for(long long i=1;i<m;i++)
		{
			long long tmp=b[i+1]-b[i];
			if(tmp<minn){minn=tmp;x1=b[i];y1=b[i+1];}
			if(tmp>maxn){maxn=tmp;x2=b[i];y2=b[i+1];}
		}
		if(!maxn)printf("There are no adjacent primes.\n");
		else printf("%lld,%lld are closest, %lld,%lld are most distant.\n",x1,y1,x2,y2);
	}
	return 0;
}
```

---

## 作者：冒泡ioa (赞：7)

部分内容来自李煜东所著《算法进阶指南》  

部分复杂LaTeX可能会炸，大家可以来我的[个人博客](https://bubbleioa.github.io/2018/08/15/[UVA10140]Prime%20Distance/#more)

暴力是不可能的，R的范围太大了。  
但是我们发现，R-L的范围很小，有什么办法可以求出R-L之间的质数呢？  
显然：  
>定理：如果n是一个合数， 那么n一定有一个不超过$\sqrt{n}$的素数因子  
>推论：任意一个合数n必定包含一个不超过$\sqrt{n}$的质因子

用质因数分解定理可以简单证明。  
所以，我们只要用筛法求出$2$~$\sqrt{R}$之间所有的质数，对于每个质数p，把$[L,R]$中能被p整除的数标记，即标记$i*p\left(\Big\lceil\dfrac{L}{P}\Big\rceil\le\Big\lceil\dfrac{R}{P}\Big\rceil\right)$为合数。  
最终所有还没有被标记的数就是$\left[L,R\right]$中的质数。对相邻质数两两比较，找出差最大的即可。  
时间复杂度为![](https://s1.ax1x.com/2018/08/16/PWSPmR.png)
## 代码
```c++
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN = 46345;
typedef long long ll;
int p[MAXN],cnt,l,r,m;
bool v[1000001];
int b[1000001];

void prime() {
	memset(v, 1, sizeof(v));
	for (int i = 2; i <= MAXN; i++)
		if (v[i]){
			p[++cnt] = i;
			for (int j = 2; j <= 46340 / i; j++) v[i*j] = false;
		}
}

int main() {
	prime();
	while (cin >> l >> r) {
		memset(v, 1, sizeof(v));
		if (l == 1) v[0] = false;
		for (ll i = 1; i <= cnt; i++)
			for (ll j = l / p[i]; j <= r / p[i]; j++) {
				if (p[i] * j - l < 0)continue;//这里不加，poj过不了
				if (j > 1) v[p[i] * j - l] = false;
			}
		m = 0;
		for (ll i = l; i <= r; i++){//这里一定要开ll的i，要不然溢出了就会死循环
			if (v[i - l]) b[++m] = i;
		}
		ll t1 = 2147483647; ll t2 = 0;
		ll x1, x2, y1, y2;
		for (ll i = 1; i<m; i++){
			ll cha = b[i + 1] - b[i];
			if (cha<t1) { t1 = cha; x1 = b[i]; y1 = b[i + 1]; }
			if (cha>t2) { t2 = cha; x2 = b[i]; y2 = b[i + 1]; }
		}
		if (!t2) cout << "There are no adjacent primes.\n";
		else cout << x1 << ',' << y1 << " are closest, " << x2 << ',' << y2 << " are most distant.\n";
	}
	return 0;
}
```

---

## 作者：斗神_君莫笑 (赞：4)

根据数据范围猜算法  
看到只有lr之间的1e6是可以承受的复杂度  
因此我们的思路围绕它展开  

考虑如果k不是素数，那么它一定能被$\sqrt{k}$整除  
于是我们想到筛出一个1e5的素数表  
对于每次询问，直接用这个素数表筛出该区间的素数  
好在本题不卡常，仅仅需要注意筛时的边界条件即可  
感谢[冒泡ioa](https://www.luogu.org/space/show?uid=61150)的友情提示
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int is_prime[1000010],prime[1000010],num;
int a[1000010];
signed main(){
	prime[++num]=2;
	is_prime[1]=1;
	for(int i=4;i<=100000;i+=2)
		is_prime[i]=1;
	for(int i=3;i<=100000;i+=2)
		if(!is_prime[i]){
			prime[++num]=i;
			for(int j=2*i;j<=100000;j+=i)
				is_prime[j]=1;
		}
	int l,r;
	while(~scanf("%lld%lld",&l,&r)){
		memset(is_prime,0,sizeof(is_prime));
		if(l==1)is_prime[0]=1;
		for(int i=1;i<=num;++i)
			for(int j=l/prime[i];j*prime[i]<=r;++j){
				if(prime[i]*j-l<0)continue;
				if(j>1)is_prime[prime[i]*j-l]=1;
			}
		memset(a,0,sizeof(a));
		int siz=0;
		for(int i=l;i<=r;++i)
			if(!is_prime[i-l])
				a[++siz]=i;
		if(siz<=1){
			printf("There are no adjacent primes.\n");continue;
		}
		int minn=0x7fffffff,minl,minr,maxx=0,maxl,maxr;
		for(int i=2;i<=siz;++i){
			if(a[i]-a[i-1]<minn){
				minn=a[i]-a[i-1];
				minl=a[i-1],minr=a[i];
			}
			if(a[i]-a[i-1]>maxx){
				maxx=a[i]-a[i-1];
				maxl=a[i-1],maxr=a[i];
			}
		}
		printf("%lld,%lld are closest, %lld,%lld are most distant.\n",minl,minr,maxl,maxr);
	}
	return 0;
}
```


---

## 作者：谁是鸽王 (赞：3)

## 【题解】UVA10140 [Prime Distance](https://www.luogu.org/problemnew/show/UVA10140)

哈哈哈哈$miller-rabbin$水过去了哈哈哈

还能怎么办呢？$miller-rabbin$直接搞。枚举即可，还跑得飞快。

![](http://images.cnblogs.com/cnblogs_com/winlere/1392450/o_2019-03-09%2015-20-43%20%E7%9A%84%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE.png)

当然此题由于$20000^2 >2^{31}$，直接预处理$20000$内的质数就好了

放mr的代码

```cpp
#include<bits/stdc++.h>

using namespace std;typedef long long ll;
#define DRP(t,a,b) for(register int t=(a),edd=(b);t>=edd;--t)
#define RP(t,a,b)  for(register int t=(a),edd=(b);t<=edd;++t)
#define ERP(t,a)   for(register int t=head[a];t;t=e[t].nx)
#define midd register int mid=(l+r)>>1
#define TMP template < class ccf >
#define lef l,mid,pos<<1
#define rgt mid+1,r,pos<<1|1
#define pushup(pos) (seg[pos]=seg[pos<<1]+seg[pos<<1|1])
TMP inline ccf qr(ccf b){
    register char c=getchar();register int q=1;register ccf x=0;
    while(c<48||c>57)q=c==45?-1:q,c=getchar();
    while(c>=48&&c<=57)x=x*10+c-48,c=getchar();
    return q==-1?-x:x;}
TMP inline ccf Max(ccf a,ccf b){return a<b?b:a;}
TMP inline ccf Min(ccf a,ccf b){return a<b?a:b;}
TMP inline ccf Max(ccf a,ccf b,ccf c){return Max(a,Max(b,c));}
TMP inline ccf Min(ccf a,ccf b,ccf c){return Min(a,Min(b,c));}
TMP inline ccf READ(ccf* _arr,int _n){RP(t,1,_n)_arr[t]=qr((ccf)1);}
//----------------------template&IO---------------------------
#define int long long
inline int ksm(ll base,ll p,ll mod){register int ret=1;base%=mod;
    for(register ll t=p;t;t>>=1,(base*=base)%=mod) if(t&1) (ret*=base)%=mod;
    return ret%mod;
}

inline bool T(int base,int p){
    for(register int t=p-1,sav;t;t>>=1){
	sav=ksm(base,t,p);
	if(sav!=1&&sav!=p-1) return 0;
	if((t&1)||sav==p-1) return 1;
    }return 1;
}

inline bool mb(int x){
    if(x==2||x==3||x==13||x==17) return 1;
    if(x==1) return 0;
    return  T(2,x)&&T(3,x)&&T(13,x)&&T(17,x);
}

int L,R,last,Mx,Mn,ans1,ans2,ans3,ans4;
main(){
    while(cin>>L>>R){
	Mx=0;
	Mn=R-L+2;last=R+1;
	RP(t,L,R) if(mb(t)){ last=t; break;}
	if(last==R+1) {printf("There are no adjacent primes\n"); continue;}
	RP(t,last+1,R){
	    if(mb(t)){
		if(t-last>Mx) Mx=t-last,ans3=last,ans4=t;
		if(t-last<Mn) Mn=t-last,ans1=last,ans2=t;
		last=t;
	    }
	}
	if(Mx==0||Mn==R-L+2) printf("There are no adjacent primes.\n");
	else printf("%d,%d are closest, %d,%d are most distant.\n",ans1,ans2,ans3,ans4);
    }
    return 0;
}
```



---

## 作者：四氧化二磷 (赞：2)

【题目描述】

　　给定两个整数L,R，求闭区间 [L,R] 中相邻两个质数差值最小的数对与差值最大的数对。当存在多个时，输出靠前的素数对。
  
  　

　　输入样例#1:　　　　　　　　　　　　　　输出样例#1:
  
　　2 17　　　　　　　　　　　　　　　　　　2,3 are closest, 7,11 are most distant.
  
　　14 17 　　　　　　　　　　　　　　　　　 There are no adjacent primes.
  
  　
   
------------

　
 
　　算法：数论
  
　　首先，**若一个数为合数，则必定可以写成 x=a×b (a,b≠1,a,b≠x) 的形式**.可以知道a,b成反比例，则必定一个大于sqrt(x),一个小于sqrt(x).特别的,当a=b=sqrt(x)时，min{a,b}=sqrt(x).也就是说任何数的因数都是成倍出现的，且**min{a,b}≤sqrt(x)**.
  
　　由于L,R的值都很大，不能直接用数组筛[L,R]中的素数，那么**我们就考虑把[L,R]中的所有合数标记**.有了上面的推论，那么**只要求出[1,sqrt(max{R})]中的所有素数，便可以表示[1,max{R}]当中任何一个合数较小的那个因数**.
  
　　有了这些素数，要做的就只是求出[L,R]中的各个合数了（就是枚举另一个因数K）。因为区间里的数有上下限（即L,R）,所以**K也有一个上下界（L/prim[],R/prim[]）**.我们用一层i循环来枚举prime[i],再用j循环来控制 **j from max(L/prim[i],(long long)2) to R/prim[i] do** 即可.(**必须在L/prim[i]与2中取最大值，不然会出BUG！**)
  
　　最后按次序暴力枚举每一个数看看有没有被标记即可（逃
  
　　Tips: 
  
　　1.**L=1时会爆炸**，因为[1,sqrt(max{R})]中没有一个素数能完美整除一。
  
　　2.**不要用当前数当下标标记，除非您的语言支持 pow(2,31) 大小的bool数组**。（我们可以将每一个数的下标向前偏移L位）
  
　　3.**注意数组大小**
  
　　4.下面代码中似乎不将（memset(bk)）从注释位置移到当前位置会炸...
  
Code:
  ```
#include<bits/stdc++.h>
#define maaax 5e4+10
using namespace std;
long long l,r,as;
long long prim[50001000];
bool b[50001000],bk[50001000];
long long nxt[50001000];
long long tot,t2,maxx,minn,in1,in2,ax1,ax2;
inline void doit(){
	l=l==1?l+1:l;
	tot=0;t2=0;
	maxx=0;minn=0x7fffffff;
	in1=0;in2=0;ax1=0;ax2=0;
	memset(b,0,sizeof(b));
//	memset(bk,0,sizeof(bk));
	memset(prim,0,sizeof(prim));
	for(int i=2;i<=1<<19;i++){
		if(b[i])continue;
		prim[++tot]=i;
		for(int j=i*2;j<=1<<19;j+=i)b[j]=1;
	}
	memset(bk,0,sizeof(bk));
	for(long long j=1;j<=tot;j++) 
	for(long long i=max((long long)2,l/prim[j]);i<=r/prim[j];i++) 
	if(i*prim[j]>=l) bk[i*prim[j]-l]=1;
	for(long long i=0;i<=r-l;i++)if(!bk[i])nxt[++t2]=i+l;
	for(int i=1;i<t2;i++){
		if(maxx<nxt[i+1]-nxt[i])maxx=nxt[i+1]-nxt[i],ax1=nxt[i],ax2=nxt[i+1];
		if(minn>nxt[i+1]-nxt[i])minn=nxt[i+1]-nxt[i],in1=nxt[i],in2=nxt[i+1];
	}
	if(!maxx){puts("There are no adjacent primes.");return;}
	printf("%lld,%lld are closest, %lld,%lld are most distant.\n",in1,in2,ax1,ax2);
	return;
}
inline long long read(){
	long long a=getchar(),b=1,c=0;
	while(!isdigit(a)){if(a=='-')b=-b;a=getchar();}
	while(isdigit(a)){c=c*10+a-'0';a=getchar();}
	return b*c;
}
int main(){
	while(~scanf("%lld %lld",&l,&r))doit();
	return 0;
}
```

---

## 作者：SymphonyOfEuler (赞：1)

$update\  on\ 7/15/2020 \ :$ 补充代码


这题是一道质数筛题。

我们看，用普通筛，需要存一个表，但是这个需要开到$10^9$，所以会超内存。但是我们这道题的任务就是想要找到$[l,r]$区间的差的最小值和最大值，所以没必要把$1$到$10^9$的数都存了，而又发现他们中间只有$10^6$（$r-l<= 10^6$），不算多，所以我们发现那样太费时间和空间了。我们想想，$[l,r]$区间的因子都会在$[sqrt(l),sqrt(r)]$的范围内，因此我们剩了很多的空间，最多存到$1,sqrt(10^9)$。

```
for (register ll i = 2; i <= 1000000; ++i) {//欧氏筛
        a[i] = true;
    }
    for (register ll i = 2; i <= 1000000; ++i) {
        if (a[i]) {
            primes[Pcnt++] = i;
        }
        for (register ll j = 0; j < Pcnt && primes[j] * i <= n; ++j) {
            a[primes[j] * i] = false;
            if (i % primes[j] == 0) break;
        }
    }
```

接下来求答案即可。


code：

```
//Code by Jeff Song

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MAXN = 100005;

ll sieve[MAXN], prime[MAXN];

ll a[1000005];

ll Pcnt, l, r;

void euro_sieve() {
    memset(sieve, 1, sizeof(sieve));
    for (ll i = 2; i < MAXN; ++i) {
        if (sieve[i]) {
            prime[Pcnt++] = i;
        }
        for (ll j = 0; j < Pcnt && i * prime[j] < MAXN; ++j) {
            sieve[prime[j] * i] = 0;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    euro_sieve();
    while (cin >> l >> r) {
        for (ll i = l; i <= r; ++i) {
            a[i - l] = 1;
        }
        if (l == 1) a[0] = 0;
        for (ll i = 0; i < Pcnt && prime[i] <= r; ++i) {
            ll p = prime[i];
            ll start = l / p * p;
            if (l % p != 0) start += p;
            if (start == p) start += p;
            for (ll j = start; j <= r; j += p) {
                a[j - l] = 0;
            }
        }
        ll mi = 1000005, ma = 0, old = -1, found = 0;
        ll miStart, miEnd, maStart, maEnd;
        for (ll i = l; i <= r; ++i) {
            if (a[i - l] == 1) {
                if (old == -1) {
                    old = i;
                } else {
                    found = 1;
                    if (i - old < mi) {
                        mi = i - old;
                        miStart = old;
                        miEnd = i;
                    }
                    if (i - old > ma) {
                        ma = i - old;
                        maStart = old;
                        maEnd = i;
                    }
                    old = i;
                }
            }
        }
        if (found == 0) {
            cout << "There are no adjacent primes.\n";
        } else {
            cout << miStart << "," << miEnd << " are closest, " << maStart << "," << maEnd << " are most distant.\n";
        }
    }
    return 0;
}
```



---

## 作者：fly_me_2_the_moon (赞：1)

我很弱

在一个诡异的题库上 时限1s 我一直卡在1056ms

万念俱灰 那就来交一篇题解吧

有一个神奇的算法

他叫Miller rabin

不会的同学这里请

[Miller rabin](https://www.cnblogs.com/LinearODE/p/10543412.html)

来 上代码


```c
#include<bits/stdc++.h>
#define ll long long
#pragma GCC optimize (2)
#pragma GCC optimize ("Ofast")
using namespace std;
ll l,r,sum,ans,a1,a2,a3,a4,ans1;
ll pri[1000001];
inline ll gcd(ll a,ll b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}
inline ll ksm(ll a,ll b,ll p)
{
	ll ans=1;
	while(b)
	{
		if(b%2==1)
		ans=ans*a%p;
		a=a*a%p;
		b=b/2;
	}
	return ans;
}
inline bool mr(ll x,ll b)
{
	ll k=x-1;
    while(k)
    {
        ll cur=ksm(b,k,x);
        if(cur!=1 && cur!=x-1)
            return false;
        if((k&1)==1 || cur==x-1)
            return true;
        k>>=1;
    }
    return true;
}
inline bool mr2(ll x)
{
	if(x==46856248255981ll|| x<2||!x%2||!x%3)
        return false;
	if(x==2||x==3||x==7||x==61||x==24251)
		return true;
	return mr(x,2)&mr(x,61);
}
inline void shai()
{
	for(ll i=l;i<=r;i++)
	if(mr2(i))
	pri[++sum]=i;
}
int main()
{
	while(scanf("%lld%lld",&l,&r)==2)
	{
		ans=INT_MAX;
		ans1=-INT_MAX;
		a1=a2=a3=a4=0;
		sum=0;
		shai();
		for(ll i=2;i<=sum;i++)
		{
			if(pri[i]-pri[i-1]<ans)
			{
				ans=pri[i]-pri[i-1];
				a1=pri[i-1],a2=pri[i];
			}
			if(pri[i]-pri[i-1]>ans1)
			{
				ans1=pri[i]-pri[i-1];
				a3=pri[i-1],a4=pri[i];
			}
		}
		if(a1)
		printf("%lld,%lld are closest, %lld,%lld are most distant.\n",a1,a2,a3,a4);
		else
		printf("There are no adjacent primes.\n");
	}
	return 0;
}
```


---

## 作者：Object_ (赞：1)

**毒瘤点：**

- primeCnt必须放到一个玄学的位置。如果放到下面，评测的时候就会报错.（poj就要放到上面）

**易错点：**

- INF必须开到2147483647而不是1<<30.
- 需要对质数判定有着纵深的理解.

------------
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN=1000001,INF=2147483647;
int primes[MAXN];
int primeCnt=0;
bool notPrime[MAXN];
void initPrime(){
	for(int i=2;i<=sqrt(INF);i++){
		if(notPrime[i])continue;
		primes[++primeCnt]=i;
		for(int j=2;j<=sqrt(INF)/i;j++){
			notPrime[i*j]=1;
		}		
	}
}
int newPrimes[MAXN];
int main(){
	initPrime();
	int l,r;
	while(cin>>l>>r){
		memset(notPrime,0,sizeof(notPrime));
		if(l==1)notPrime[0]=1;
		for(int i=1;i<=primeCnt;i++){
			for(int j=l/primes[i];j<=r/primes[i];j++){
				if(j>1)notPrime[primes[i]*j-l]=1;
			}
		}
		int newPrimeCnt=0;
		for(int i=l;i<=r;i++){
			if(!notPrime[i-l])newPrimes[++newPrimeCnt]=i;
			if(i==r)break;
		}
		int minDelta=INF,maxDelta=0;
		int minX1,minX2,maxX1,maxX2;
		for(int i=1;i<newPrimeCnt;i++){
			int nowDelta=newPrimes[i+1]-newPrimes[i];
			if(nowDelta<minDelta){
				minDelta=nowDelta;
				minX1=newPrimes[i],minX2=newPrimes[i+1];
			}
			if(nowDelta>maxDelta){
				maxDelta=nowDelta;
				maxX1=newPrimes[i],maxX2=newPrimes[i+1];
			}
		}
		if(minDelta==INF)printf("There are no adjacent primes.\n");//
		else printf("%d,%d are closest, %d,%d are most distant.\n",minX1,minX2,maxX1,maxX2);
	}
	return 0;
}
```


---

## 作者：qianfujia (赞：1)

### Prime Distance
先求出$1-100000$的素数集合$\{S\}(Because\ 100000^2 > 2^{31}-1)$

对于每对$(L, R)$求出区间内素数$(Use \ \{S\})$

最后一波暴力扫描
### Code:
```cpp
/*
Code By Dijstra
2018/5/9 22:00
In Luogu OnlineJudge
*/
#include<cstdio>
#include<cstring>
#include<iostream>
#define N 100010
#define X 2147483647
#define ll long long 
using namespace std;
bool Check[N * 10];
ll prime[N], k = 0;
ll prime2[N * 10], top = 0;
int main()
{
	for(ll i = 2; i < N; ++ i)
	{
		if(! Check[i])
			prime[++ k] = i;
		for(int j = i * 2; j < N; j += i)
			Check[j] = true;
	}
	ll L, R;
	while(scanf("%lld%lld", &L, &R) != EOF)
	{
		L = max(L, 2ll);
		top = 0;
		memset(Check, 0, sizeof(Check));
		for(ll i = 1; prime[i] * prime[i] <= R && i <= k; ++ i)
		{
			int s = L / prime[i] + (L % prime[i] > 0);
			if(s == 1)
				s = 2;
			for(ll j = prime[i] * s; j <= R; j += prime[i])
					Check[j - L] = true;
		}
		for(ll i = 0; i <= R - L; ++ i)
			if(! Check[i])
				prime2[++ top] = i + L;
		ll Min = X, a = 0;
		ll Max = 0, b = 0;
		for(ll i = 1; i < top; ++ i)
		{
			if(prime2[i + 1] - prime2[i] < Min)
			{
				Min = prime2[i + 1] - prime2[i];
				a = i;
			}
			if(prime2[i + 1] - prime2[i] > Max)
			{
				Max = prime2[i + 1] - prime2[i];
				b = i;
			}
		}
		if(top < 2)
			puts("There are no adjacent primes.");
		else
			printf("%lld,%lld are closest, %lld,%lld are most distant.\n", prime2[a], prime2[a + 1], prime2[b], prime2[b + 1]);
	}
	return 0;
} 
```

---

