# Integer Points

## 题目描述

DLS and JLS are bored with a Math lesson. In order to entertain themselves, DLS took a sheet of paper and drew $ n $ distinct lines, given by equations $ y = x + p_i $ for some distinct $ p_1, p_2, \ldots, p_n $ .

Then JLS drew on the same paper sheet $ m $ distinct lines given by equations $ y = -x + q_i $ for some distinct $ q_1, q_2, \ldots, q_m $ .

DLS and JLS are interested in counting how many line pairs have integer intersection points, i.e. points with both coordinates that are integers. Unfortunately, the lesson will end up soon, so DLS and JLS are asking for your help.

## 说明/提示

The picture shows the lines from the first test case of the example. Black circles denote intersection points with integer coordinates.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1248A/8a7326901424797e600db27d56ff13441fc9fe8a.png)

## 样例 #1

### 输入

```
3
3
1 3 2
2
0 3
1
1
1
1
1
2
1
1
```

### 输出

```
3
1
0
```

# 题解

## 作者：jiangXxin (赞：6)

一道超简单的题，结果我几次才过，还是我太菜了.

首先，我们通过题目知道，我们要求的是y=x+a和y=-x+b的交点个数，y=x+a肯定是不会产生交点的，我们把y=x+a和y=-x+b联立起来，可以得到**2x=b-a**,因为要保证为整数交点，那么一定有b-a被2整除，通过小学的知识我们可以知道：

**1：奇数相加减，为偶数.**

**2：偶数相加减，为偶数.**

根据这个，我们就可以分别记录题目中长为n和m序列中的奇数和偶数的个数，根据计数原理，最终答案就是**n中偶数个数乘以m中偶数个数+n中奇数个数乘以m中奇数个数**

code:

```cpp
/**
*    author:  a2954898606
*    created: 2019/10/21 21:07:51
**/
#include<bits/stdc++.h>
#define REP(A,B,I) for(int I=(A);I<=(B);I++)
#define PER(A,B,I) for(int I=(A);I>=(B);I--)
#define LL long long
#define N 1000010
#define M 100
using namespace std;
const long long mod=1e9+7;
long long quickmul(long long a,long long b){
    a%=mod;b%=mod;
    long long c=(long long)a*b/mod;
    long long ans=a*b-c*mod;
    if(ans<0)ans+=mod;
    else if(ans>=mod)ans-=mod;
}
long long quickpow(long long a,long long b){
    long long ret=1;
    while(b){
        if(b&1)ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}
long long a[N],b[N],m,n,t;
int main(){
    //read(1)
    //write(1)
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin>>t;
    long long  ans=0;
    REP(1,t,tt){
        long long al=0,bl=0,ar=0,br=0;
        cin>>n;
        REP(1,n,i){
            cin>>a[i];
            if(a[i]&1)al++;
            else ar++;
        }
        cin>>m;
        REP(1,m,i){
            cin>>b[i];
            if(b[i]&1)bl++;
            else br++;
        }
        ans=al*bl+ar*br;
        cout<<ans<<endl;
    }
    return 0;
}


```


---

## 作者：chenyuchenghsefz (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1248A)

所有的 $x+p_i$ 互相平行。所有的 $-x+q_i$ 互相平行。若 $x+p$ 与 $-x+q$ 相交于整点，则 $x+p=-x+q$，$x\in \mathbb{Z}$。即 $2\,|\,(p-q)$，所以 $p$，$q$ 同奇偶。

那就只需要统计出有一个 $p$ 是奇数，有几个是偶数，再和所有的 $q$ 的奇偶性对比，最后再加起来就行了。

[AC 记录](https://www.luogu.com.cn/record/104089970)

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        long long n,m,p,s1=0,s2=0,s=0; //统计奇数和偶数个数，s1是奇数，s2是偶数 
        cin>>n;
        for(int j=1;j<=n;j++)
        {
            cin>>p;
            if(p%2==1)
            s1++;
            else
            s2++;
        }
        cin>>m;
        for(int j=1;j<=m;j++)
        {
            cin>>p;
            if(p%2==1)
            s+=s1;
            else
            s+=s2;
        }
        cout<<s<<endl;
    }
    return 0;
}
```


---

## 作者：夙愿扬 (赞：1)

### CF1248A

有一个长度为$n$的序列$p_1$，$p_2$...$p_n$，代表$n$条直线 $y=x+p_i$

有一个长度为$m$的序列$q_1$，$q_2$...$q_m$，代表$m$条直线 $y=x+q_i$

问这$n+m$条直线之间有多少个整数交点。

这道题需要引入一点点数学知识：

首先先说显然的东西：

- 在$n$序列里的直线平行，永不相交
- 同理，在$m$序列里的直线平行，永不相交
- 所以相交的两条直线只能是一条在$n$中，一条在$m$中

其次判断整点：

- 当$|p_i+q_i|$为偶数时，交点为整点 ~~易证~~

代码如何实现：

- 遍历$(n*m)$? ~~T飞~~
- 奇偶性判断：只需要判$n$和$m$中奇数和偶数的个数，然后根据：
- 奇$+$奇$=$偶
- 偶$+$偶$=$偶
- 最后输出$n_{ji}*m_{ji}+n_{ou}*m_{ou}$

### 最重要的一点！

#### 一定要开long long

~~不开long long见祖宗~~
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//一开始没开long long
signed main ()
{
    int t,n,m,a1,a2,b1,b2,p;
    scanf("%lld",&t);
    for(int i=1;i<=t;i++)
    {
        a1=0;
        a2=0;
        b1=0;
        b2=0;
        scanf("%lld",&n);
        for(int j=1;j<=n;j++)
        {
            scanf("%lld",&p);
            if(p&1)
            a1++;
            else
            a2++;
        }
        scanf("%lld",&m);
        for(int j=1;j<=m;j++)
        {
            scanf("%lld",&p);
            if(p&1)
            b1++;
            else
            b2++;
        }
        // cout<<a1<<" "<<a2<<" "<<b1<<" "<<b2<<endl;
        printf("%lld\n",a1*b1+a2*b2);
    }
    return 0;
}
```
##### The End--2019/10/21 21:36

---

## 作者：20120511qhc (赞：0)

# 题意

给你 $n$ 个函数 $x+p_1,x+p_2,x+p_3,\dots,x+p_n$ 与 $m$ 个函数 $-x+q_1,-x+q_2,-x+q_3,\dots,-x+q_m$。求这 $n+m$ 个函数共会产生几个交点？

# 思路

显然，$n$ 个函数之间不会产生交点，$m$ 个函数之间也不会产生交点，所以，就变成了解方程：$x+p_i=-x+q_j$

化简得：$2x=q_j-p_i$。

所以：$q_j \equiv p_i \pmod 2$

最终答案为：$p$ 中的奇数个数 $\times$ $q$ 中的奇数个数 $\times$ $p$ 中的偶数个数 $+$ $q$ 中的偶数个数。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, m, p[100005], q[100005], f[2][2];
signed main(){
  for(cin >> t; t; t--){
    memset(f, 0, sizeof(f));
    cin >> n;
    for(int i = 1; i <= n; i++){
      cin >> p[i];
    }
    cin >> m;
    for(int i = 1; i <= m; i++){
      cin >> q[i];
    }
    for(int i = 1; i <= n; i++){
      f[0][p[i] % 2]++;
    }
    for(int i = 1; i <= m; i++){
      f[1][q[i] % 2]++;
    }
    cout << f[0][0] * f[1][0] + f[1][1] * f[0][1] << "\n"; 
  }
  return 0;
}
```


---

## 作者：lemon_qwq (赞：0)

一道简单的数学题。

因为两直线平行，永不相交，所以有交点的线一定是一条 $n$ 集合里的，一条 $m$ 集合里的。

那怎么判断交点是否是整点呢？

明显，$|p_i+q_i|$ 为偶数时，它们的交点一定是整点。

直接暴力枚举肯定不行，我们可以建四个变量，统计两个集合里奇数和偶数的个数。

为了方便贴公式，我们把 $n$ 集合偶数变量称作 $n1$，奇数变量称作 $n2$。

$m$ 集合偶数变量称作 $m1$，奇数变量称作 $m2$。

根据我们小学学过的奇数偶数的性质：

1. 奇数加减奇数等于偶数。

2. 偶数加减偶数等于偶数。

可以得出最终答案便是 $n1\times m1+n2\times m2$。

完结撒花！

---

## 作者：ytcccf (赞：0)

## CF1248A Integer Points 题解

### 题意简述

给定 $n$ 条斜率为 $1$ 的直线、$m$ 条斜率为 $-1$ 的直线，求满足  $x\in \mathbb{Z}$ , $y\in \mathbb{Z}$ 的交点 $(x,y)$ 的个数。

### 题目分析

题目难度：普及-

AC code 时间复杂度为 $\Theta(T(n+m))$

### 解题思路 

题中要求求出交点是整点的数量，若想要交点为整点则需要两条直线后面加上的常数奇偶性相同，否则交点会是形如 $(x+\frac{1}{2},y+\frac{1}{2})(x\in \mathbb{Z},y\in \mathbb{Z})$ 的，所以只需要把两组支线按照常数的奇偶性分别计数，最后将奇数乘奇数、偶数乘偶数再相加岂可得到答案。

注意：不开 `long long` 见祖宗！！！！！

### AC code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	ios::sync_with_stdio(false);
	int t,n,m,x;
	cin>>t;//多测 
	while(t--)
	{
		cin>>n;
		int a1=0,a2=0;
		for(int i=1;i<=n;i++)
		{
			cin>>x;
			if(x%2==0) a2++;//偶数 
			else a1++;//奇数 
		}
		cin>>m;
		int b1=0,b2=0;
		for(int i=1;i<=m;i++)
		{
			cin>>x;
			if(x%2==0) b2++;//偶数 
			else b1++;//奇数 
		}
		cout<<a1*b1+a2*b2<<endl;//奇乘奇+偶乘偶 
	}
	return 0; 
}
```

---

## 作者：stntn (赞：0)

## 简要题意

在平面直角坐标系上给你若干 $k=\pm 1$ 的直线，求这些直线的整数交点。

## 分析

枚举每对直线，求交点，判断，复杂度 $O(nm)$，显然过不了。

考虑不枚举，仔细观察图片可知：

当 $b=1$ 时，与它有整数交点的直线有 $b=3$、$b=1$、$b=-1$ 等等。

当 $b=2$ 时，与它有整数交点的直线有 $b=0$、$b=2$、$b=4$ 等等。

由此，我们猜测能对一条直线的答案做出贡献的直线满足两个条件：

- $k_i \ne k_j$。
- $b_i$ 与 $b_j$ 奇偶性相同。

易证上述结论成立。

因此我们开一个统计数组，统计 $k=-1$ 的直线中 $b$ 为奇数/偶数的数量，然后枚举 $k=1$ 中直线，统计奇偶性相同的数量即可。复杂度 $O(n)$。

另外我去了一下重（不知道是否必要，保险起见还是写了）。复杂度 $O(n \log n)$。

## Code

```cpp
#include<bits/stdc++.h>
#define N 100010
#define int long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define tep(i,u) for(int i=head[u];~i;i=E[i].nxt)
#define INF 0x3f3f3f3f
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int T,n,m,ans,a[N],b[N],cnt[2];
signed main()
{
	read(T);
	while(T--)
	{
		cnt[1]=cnt[0]=ans=0;
		read(n);rep(i,1,n) read(a[i]);
		read(m);rep(i,1,m) read(b[i]);
		//下面两行是去重代码 
		sort(a+1,a+1+n);n=unique(a+1,a+1+n)-a-1;
		sort(b+1,b+1+m);m=unique(b+1,b+1+m)-b-1;
		
		rep(i,1,n) cnt[(bool)(abs(a[i])&1)]++;
		rep(i,1,m) ans+=cnt[(bool)(abs(b[i])&1)];
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：苏黎世 (赞：0)

### 标签：数论

读完题，我们发现题意：求所有支线相交的交点个数。

另外，直线比较特殊，斜率（就是k）只是±1。

以此，思路：

首先，若两个一次函数的k值相同，那么这两个函数永远不可能相交，因为他们是平行的。

#### 所以说，只有一个k是1，另一个k是-1时才会有交点。

#### 再看交点的要求：整数交点。

如果此时还是没有思路，我们带一组函数：

由图可知，y=x+1和y=-x+3有交点。而交点的x，y值是相等的。

所以：x+1=-x+3。

#### 下一步：2x=4。

结果：x=1。

#### 所以我们发现：当求出的x是整数，y才是整数。

又因为“下一步”中x的系数总是2，所以我们知道了：

#### 当两个函数的b值相加为偶数，才是整点。

于是，我们信心满满打了一个代码（暴力）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int n, m, a[maxn];

void cini()
{
	scanf("%d", &n);
	for(int i = 1;i <= n; ++i)
	  scanf("%d", &a[i]);
	scanf("%d", &m);
}

void work()
{
	int sum = 0, p;
	for(int i = 1;i <= m; ++i)
	{
		scanf("%d", &p);
		for(int j = 1;j <= n; ++j)
		  if((a[j] + p )% 2 == 0)
		    ++sum;
	}
	printf("%d\n", sum);
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		cini();
		work();
	}
	return 0;
}
```
然而发现，TLE了。

于是，我们又思考:

#### 若结果为偶数，那么要么是奇数加奇数，要么是偶数，加偶数。

所以优化就是：

把所有的奇数和偶数的个数存起来，最后统计结果直接相加对应即可。

那么，代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, ji, ou;
void cini()
{
	ji = 0;ou = 0;
	cin >> n;
	int x;
	for(int i = 1;i <= n; ++i)
	{
		cin >> x;
		if(x % 2 == 0)
		  ou++;//偶数
		else
		  ji++;//奇数
	}
	cin >> m;
}

void work()
{
	long long sum = 0;
	int p;
	for(int i = 1;i <= m; ++i)
	{
		cin >> p;
		if(p % 2 == 1)//奇数加奇数
		  sum += ji;//当前输入的函数与之前所有b值为奇数的函数都会有交点
		else//偶数加偶数
		  sum += ou;//同上
	}
	printf("%lld\n", sum);
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cini();//个人习惯
		work();
	}
	return 0;
}
```


---

## 作者：Tommy_clas (赞：0)

[传送门](https://www.luogu.org/problem/CF1248A)

题目大意：给定$n$条斜率为$1$的直线，$m$条斜率为$-1$的直线，求所有直线的整数交点的个数。即求所有满足$x∈Z,y∈Z$的交点$(x,y)$的个数。

平行的直线互不相交，因此我们只需要考虑斜率不同的直线的交点。

根据函数图像的交点列出方程：$x+a_i=-x+b_j$。

即：$x=\frac{a_i+b_j}{2}$。

若$x$为整数，则$y$也一定为整数。

所以当$a_i+b_j$为偶数时，两条直线的交点是整数点。因此只要统计$a_i+b_j$为偶数的$(a_i,b_i)$对数即可。

然后我们就得到了如下做法。

对于前$n$条直线，统计截距分别为奇数或偶数的直线的数量。

对于后$m$条直线，统计答案，若截距为奇数，则加上截距大小是奇数的直线的个数，若截距为偶数，则同理。

上代码：
```cpp
#include<cstdio>
#define ll long long
using namespace std;
int T,sum[2],n,m;
ll ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=sum[0]=sum[1]=0;
		scanf("%d",&n);
		for(int i=1,x;i<=n;i++)
			scanf("%d",&x),sum[x&1]++;
		scanf("%d",&m);
		for(int i=1,x;i<=m;i++)
			scanf("%d",&x),ans+=(ll)sum[x&1];
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：big_news (赞：0)

不难发现只有形如$y=x+b_1$和$y=-x+b_2$的函数会有交点。

联立$x+b_1 = -x+b_2$,有$x = (b_2-b_1)/2$。这个东西为整数，当且仅当$b_2-b_1$为偶数。也就是说现在我们要统计$\forall i\in [1,n],j\in[1,m] ,(b_j-b_i) \equiv 0 (\text{mod 2})$的数量。

我们发现我们关注的只是$(b_j-b_i)$的奇偶性，而并不是这个式子具体的值。考虑什么情况下两数相减会出现偶数：偶-偶 或 奇-奇 。

考虑用乘法解决这个问题，那我们设$c_1$表示$b_i(i\in[1,n])$中奇数的数量，$c_2$表示$b_j(j\in[1,m])$中奇数的数量，那么答案显然就是
$c_1\times c_2 + (n-c_1)\times(m-c_2)$。

于是做完了。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstring>
using namespace std;

#define LL long long

const int CN = 1e5+5;

LL read(){
    LL s = 0,ne = 1; char c = getchar();
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') ne = -1;
    for(;c>='0'&&c<='9';c=getchar()) s=(s<<1)+(s<<3)+c-'0';
    return s*ne;
}

LL t,n,m;

int main()
{
    //freopen("a.in","r",stdin);

    t = read();
    while(t--){
        LL cnt1 = 0,cnt2 = 0,ans;

        n = read();
        for(int i=1;i<=n;i++){
            int pi = read();
            if(pi % 2) cnt1++;
        }
        m = read();
        for(int i=1;i<=m;i++){
            int qi = read();
            if(qi % 2) cnt2++;
        }

        ans = cnt1 * cnt2 + (n-cnt1) * (m-cnt2);       
        
        printf("%I64d\n",ans);
    }

    return 0;
}
```

---

