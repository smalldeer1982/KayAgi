# Bear and Tower of Cubes

## 题目描述

Limak是一只可爱的北极熊。他正在用一堆木块搭塔。每一个木块都是一个有着正整数边长的正方体。Limak有无数块木块。显然的，每一块边长为$a$  的木块的体积为$a^3$  ，而一个塔的体积为组成这个塔的所有木块的体积和。**这里，我们定义一个塔的高度是组成这个塔的木块数量。**

Limak现在要搭建一个塔。首先，他让你告诉他一个正整数$X$  ，表示这个塔的总体积。然后，他将会贪心地搭建这个塔（每次总是尽可能地添加最大的木块，即先选一个体积最大的正方体作为第一层，第一层的体积满足体积不超过$X$  。然后选一个最大的正方体做第二层，使得前两层的体积和满足不超过$X$  。然后再选一个最大的正方体做第三层，使得前三层的体积和满足不超过$X$  。依次类推，直到建好一座体积为$X$  的塔）。

Limak想让你在$1$  - $m$  之间选择一个$X$  ，使他能够搭建的塔的总高度$h$  最高。同时，在总高度最高的情况下，让塔的总体积$X$  最大。

（实在没看懂题意可以看看样例解释）

## 说明/提示

对于样例1，当$X=23$  或$X=42$  时$h$  有最大值为9。因为Limak想让你最大化塔的体积，所以应该选择42。

在选择$X=42$  之后，具体的建塔过程为：

> - 首先，Limak选择一块边长为3的木块，因为这是体积不超过42的最大木块。剩下的体积为$42-27=15$  。 
> - 然后，同样的，Limak会选择边长为2的木块，所以剩下的体积为$15-8=7$  。 
> - 最后，Limak放上7块边长为1的木块。  

所以，这座塔的高度为9，总体积为$3^3+2^3+7*1^3=27+8+7=42$  。

感谢@星烁晶熠辉 提供的翻译

## 样例 #1

### 输入

```
48
```

### 输出

```
9 42
```

## 样例 #2

### 输入

```
6
```

### 输出

```
6 6
```

# 题解

## 作者：快斗游鹿 (赞：2)

## 思路

如果我们当前选了边长为 $a$ 的正方体，那么 $X$ 最大也只能是 $(a+1)^3-1$。否则我们就必须取边长为 $a+1$ 的正方体了。从而得出，用完这个正方体后最多还可以用体积为 $\min(m-a^3,(a+1)^3-1-a^3)$ 的正方体。接下来一个个考虑：

如果接下来选择用边长为 $a$ 的正方体，那么还剩 $m-a^3$ 的体积可用。

如果接下来选择用边长为 $a-1$ 的正方体，那么还剩 $\min(m-(a-1)^3,a^3-1-(a-1)^3)$ 的体积可用。

如果接下来选择用边长为 $a-2$ 的正方体，那么还剩 $\min(m-(a-2)^3,(a-1)^3-1-(a-2)^3)$ 的体积可用。

如果选择了边长为 $a-n(n\le a)$ 的正方体，那么还剩 $\min(m-(a-n)^3,(a-n+1)^3-1-(a-n)^3)$ 的体积可用。

因为 $m\ge a^3$，所以 $n>0$ 时，最小值一定是 $(a-n+1)^3-1-(a-n)^3$。那么随着 $n$ 增大，可用体积也会减小，这是没有意义的。所以接下来的边长不是 $a$ 就是 $a-1$，再小并不会更优秀。

接下来因为答案很小，直接搜索即可。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int m,f[N],ansa,ansb;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int lf(int x){
	return x*x*x;
}
void dfs(int m,int s,int t){//搜索
	if(!m){
		if(s>ansa||(s==ansa&&t>ansb)){//更新答案
			ansa=s;ansb=t;
		}
		return;
	}
	int x=1;
	while(lf(x+1)<=m)x++;
	dfs(m-lf(x),s+1,t+lf(x));//取a
	if(x>=1)dfs(lf(x)-1-lf(x-1),s+1,t+lf(x-1));//取a-1
}
signed main(){
	m=read();
	dfs(m,0,0);
	cout<<ansa<<" "<<ansb; 
}

```


---

## 作者：xukuan (赞：2)

二分查找（STL之upper_bound）

时间复杂度：O(n log n)其中n^3==m


注意：

1.long long可以存下10^15，不用string

### 2.用scanf和print时注意是"%lld"还是"%d"

3.最后比较大小时可以用pair<long long,long long>

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#define ll long long
using namespace std;

ll n,m,v,h,maxh,maxv;

ll three[100010];
pair<ll,ll> ans;//结果

void dfs(ll m,ll t,ll r){
//m代表剩余高度，t代表高度，r代表体积
    if(m==0){//剩余高度为0
        ans=max(ans,make_pair(t,r));//取最大值
        return;//返回
    }
    
    ll Do=upper_bound(three+1,three+100002,m)-three;//二分查找接下来用哪个木头
    Do--;//upper_bound的返回值大于m所以值要-1
    dfs(m-three[Do],t+1,r+three[Do]);//取这个木头
    if(Do>1) dfs(three[Do]-1-three[Do-1],t+1,r+three[Do-1]);//取下一个
}

int main() {
    cin>>m;
    for(ll i=1; i<=100001; i++) {
        three[i]=i*i*i;
    }//算出1到100001的三次方

    dfs(m,0,0);//深搜
    
    printf("%lld %lld\n",ans.first,ans.second);//输出

    return 0;
}
```

---

## 作者：Siteyava_145 (赞：1)

运行时间：$60ms$。

### 题意（自己的理解）：

首先，有一个正整数 $X \in [1,m]$ ，表示这个塔的总体积。然后，他每次总是尽可能地添加最大的木块，也就是第一层要放体积最大不超过 $X$ 的正方体。然后再选一个当前最大的正方体做第二层，也就是这个正方体的体积不超过 $(X-$ 第一层的体积 $)$。然后再选一个当前最大的正方体做第三层，也就是这个正方体的体积不超过 $(X-$ 第一，二层的总体积 $)$。

你所做的，是要使块的个数尽可能多，在这个条件下，$X$ 尽量大。

---

这道题可以对操作进行枚举，来求出最大的 $h$，和与其对应的最大的 $X$。

我们定义剩余体积为 $X$ 减去已搭建的正方体的总体积。

1. 每次搭正方体可以用一个当前最大的正方体，设此边长为 $L$。
2. 另外一种是：将剩余体积变为 $L^3-1$，再用一个边长是 $L-1$ 的正方体（当前最大的正方体）。原理：它要求总块数最多，所以我们可以尽可能放小正方体，使得体积分配更多，块数也更多。
3. 如果将剩余体积变得更小，用一个边长是 $L-2$ 的正方体，那样就会浪费很多的体积，使得块数变少。所以这种方法不可行。
4. 因为只有两种操作方案，所以可以dfs搜索，每次更新答案（$24-31$ 行，详见注释）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long m;
long long h,v;
long long fp(long long a,long long b){//快速幂
	long long ans=1;
	while(b>0){
		if(b&1){
			ans=ans*a;
		}
		a=a*a;
		b>>=1;
	}
	return ans;
}
void dfs(long long a/*剩余体积*/,long long nh/*当前高度（块数）*/,long long nv/*已搭建的正方体的总体积*/){
    if(a<=0){//如果剩余体积<=0,那么说明搭建完成。
        if(nh>h){h=nh;v=nv;}
        else if(nh==h){
            if(nv>v){v=nv;}
        }
        //(更新数据)
        return;
    }
    long long l=1,r=100001;//cbrt(10^15)=100000 二分查找当前体积下最大可用的边长。
    while(l<=r){
        long long mid=l+r>>1;
        if(fp(mid,3)<=a)l=mid+1;
        else r=mid-1;
    }
    long long L=l-1;//二分答案-1
    
    ////1.搭建一个最大正方体：
    
    dfs(a-fp(L,3),nh+1,nv+fp(L,3));
    //剩余体积：原剩余体积-L^3
    //高度：原高度+1
    //总体积：原体积+L^3
    
    ////2.搭建一个边长为L-1的正方体
    if(!(L<=1)){//L==1时，正方体边长为0，不计算。
        dfs(fp(L,3)-1-fp(L-1,3),nh+1,nv+fp(L-1,3));
        //剩余体积：最大的剩余体积必须小于L^3,不然上面这一种方法更优，
        //为了总体积更大，剩余体积应等于L^3-1。
        //再减去这个边长为（L-1)^3的正方体，得到剩余体积=fp(L,3)-1-fp(L-1,3)。
        //高度：原高度+1
    	  //总体积：原体积+(L-1)^3
    }
}
int main(){
    cin>>m;
    dfs(m,0,0);//搜索，m为剩余体积，0为块数，第二个0为已搭建的体积
    cout<<h<<' '<<v<<endl;
}
```


---

## 作者：Querainy (赞：1)

容易想到贪心，但是贪心求出的 $x$ 并不是最大的。不过我们输入 $10^{15}$ 可以知道答案最大也只有 $18$。

打表也许可以发现一个牛逼结论，我们选择的最大的数要么是 $a=\lfloor\sqrt[3]{m}\rfloor$，要么是 $a-1$。如何证明?

考虑如果选了 $t$，那么 $x$ 最多是 $(t+1)^3-1$，于是最多只剩下 $\min(m-t^3,(t+1)^3-t^3-1)$ 还可以用。

如果我们选了 $a$，那么剩下 $m-a^3$。

如果我们选了 $a-1$，那么剩下 $\min(m-(a-1)^3,a^3-(a-1)^3-1)$。

如果我们选了 $a-2$，那么剩下 $\min(m-(a-2)^3,(a-1)^3-(a-2)^3-1)$。

注意到 $m\geq a^3$，于是对于后两个，$\min$ 总是在后者取得。所以如果选了 $a-2$，得到的少，剩下的也少，所以选 $<a-1$ 的必然不优。于是由于答案不超过 $18$，直接搜就行了。

呃这个也可以分析复杂度。注意到 $m-(\lfloor\sqrt[3]{m}\rfloor-1)^3$ 看起来很小，胡乱估计一下它不超过 $6m^{\frac{2}{3}}+1$，于是递归层数是 $O(\log\log m)=\lg O(\log^c m)$ 级别，其中常数 $c>1$ 但是具体是多少我有点懒得算，总之我们的复杂度就是 $O(\log^c m)$。

```cpp
#include<stdio.h>
#include<math.h>

inline long long min(long long x,long long y){ return x<y?x:y; }

long long m;

inline long long cb(long long x){ return x*x*x; }
struct Pair{ int ans;long long c; };

Pair dfs(long long m)
{
    if(m<=0) return {0,0};
    int a=cbrt(m);
    Pair temp1=dfs(m-cb(a)),temp2=dfs(cb(a)-cb(a-1)-1);
    temp1.c+=cb(a),temp2.c+=cb(a-1),temp1.ans++,temp2.ans++;
    return temp1.ans==temp2.ans?temp1.c>temp2.c?temp1:temp2:temp1.ans>temp2.ans?temp1:temp2;
}

int main()
{
    scanf("%I64d",&m);
    Pair temp=dfs(m);
    printf("%d %I64d",temp.ans,temp.c);
    return 0;
}
```

---

## 作者：洛谷の老豆 (赞：0)

### 题意
对于一个数 $x$，每次贪心地找到不小于剩下的数的最大的正整数的立方，减去这个数，并重复直至变成 $0$，操作次数即为 $x$ 的贡献。
在 $[1,m]$ 中找到最大的贡献及对应的数最大值。
### 思路
其他题解给出了二分/ dfs 的做法，这里给出一种 DP 的做法。

将 $m$ 分解为 $\sum{a_k^{3}t_k}$，其实总共分解出来的数不多，考虑可以通过以下方式计算答案：枚举 $k$，选取 $a_k^3$ 的最后一个，不小于 $a_k^3$ 的都保留，小于的都忽视，将 $a_k^3$ 其拆开成最优的方案，与不小于 $a_k^3$ 的贡献合起来。

接下来就考虑 $x^3$ 的贡献：将 $x^3-1$ 分解，按照上面的方法计算，最后考虑 $x^3$ 本身。

时间复杂度为 $O(\sqrt[3]{m})$，答案最大也只有 $18$，常数可以接受。

### Code

```cpp
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define hehe pair<long long,long long>
#define fir first
#define sec second
#define pb push_back
#define inf 1000000007
#define N 100005
using namespace std;
long long read()
{
	long long x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1ll)+(x<<3ll)+ch-48,ch=getchar();
	return x*f;
}
void write(long long x)
{
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
long long n,cb[N],lim;
vector<hehe>v;
hehe ans,f[N];
long long cube(long long x)
{
	return x*x*x;
}
long long ncb(long long x)
{
	return (long long)pow((double)x,(double)1/(double)3);
}
void solve(long long x)
{
	v.clear();
	for(long long t,d;x;)
	{
		t=ncb(x);
		while(cb[t]>x)t--;
		while(t<lim&&cb[t+1]<=x)t++;
		d=x/cb[t];
		v.pb({t,d});
		x-=d*cb[t];
	}
}
hehe dp(long long x)
{
	long long sum=0,total=0;
	hehe ans={0,0};
	for(auto &aut:v)
	{
		long long t=aut.fir,d=aut.sec;
		long long temp=sum+(d-1)+f[t].fir,size=total+cb[t]*(d-1)+f[t].sec;
		if(temp>ans.fir||(temp==ans.fir&&size>ans.sec))ans.fir=temp,ans.sec=size;
		sum+=d;
		total+=d*cb[t];
	}
	return ans;
}
int main()
{
	n=read();
	lim=ncb(n)+2;
	for(long long i=1;i<=lim;i++)
	{
		cb[i]=cube(i);
	}
	for(long long i=1;i<=lim;i++)
	{
		long long temp=cb[i]-1;
		solve(temp);
		f[i]=dp(temp);
		if(!f[i].fir)f[i].fir=i,f[i].sec=cb[i];
	}
	solve(n);
	ans=dp(n);
	printf("%lld %lld\n",ans.fir,ans.sec);
	return 0;
}

```


---

