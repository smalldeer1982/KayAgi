# Candies!

## 题目描述

考虑一个长度为 $2^k$ 的序列 $[a_1,a_2,...,a_{2^k}]\ (0 \leq a_i \leq 9)$ 。我们对这个序列进行下列操作：

每次选中 $(a_{2i+1},a_{2i}) (0\leq i <  2^{k-1})$ ，共$2^{k-1}$对数字，若$a_{2i+1}+a_{2i}\ge 10$，你就能获得一颗糖果！ ，之后将每一个$(a_{2i+1}+a_{2i}) \mod 10$ 按 $i$ 从小到大重新写成一排，形成一个新的序列，长度为$2^{k-1}$

我们不断执行这个操作直到序列的长度变为 $1$ 。我们用$f[a_1,a_2,...,a_k]$表示我们对序列$[a_1,a_2,...,a_k]$不断进行操作，最终一共获得的糖果。

举个栗子：序列为$[8,7,3,1,7,0,9,4]$

第一步之后序列变为$[5,4,7,3]$，因为$8+7\ge 10 ,9+4 \ge 10$ 所以获得 $2$ 颗糖果

第二步之后序列变为$[9,0]$，因为$7+4 \ge 10$ 所以获得 $1$ 颗糖果

第三步之后序列变为$[9]$

所以 $f([8,7,3,1,7,0,9,4]) = 3$，因为我们一共得到 $3$ 颗糖果

所以现在你有一个长度为 $n$ 的序列 $s_1,s_2,...,s_n$ ，给你 $q$ 组询问，每一次询问一个长度为 $2$ 的整数次幂的区间 
$[l_i,r_i]$，请输出 $f([s_{l_i},s_{l_{i+1}},...,s_{r_i}])$


$f([7,3,1,7])=1$，因为

$[7,3,1,7] \rightarrow [0,8] \rightarrow [8]$ ，其中$7 + 3 \ge 10$ 所以只获得 $1$ 个糖果

$f([9])=0$，因为我们不需要进行操作。

## 样例 #1

### 输入

```
8
8 7 3 1 7 0 9 4
3
1 8
2 5
7 7
```

### 输出

```
3
1
0
```

## 样例 #2

### 输入

```
6
0 1 2 3 3 5
3
1 2
1 4
3 6
```

### 输出

```
0
0
1
```

# 题解

## 作者：YLWang (赞：10)

为什么你们发结论题的题解不加证明也能过/kel

简单地观察一下题目，发现是个倍增DP。打打就过了。

后来发现这个题有个神奇的结论。

$ans(l, r) = sum(l, r) / 10$

为什么？

其实非常简单。

考虑每次两个小于$10$的数相加一定小于$20$。

所以一次操作就相当于用区间和减$10$的代价换取一个candy。

然后结论就成立了。

---

## 作者：Zekrom (赞：4)

## 动态规划   
f[i][k] 表示第i个位置长度$2^k$的值   
显然有   
$  f[i][k]=f[i][k-1]+f[i+(1<<(k-1))][k-1]$ +   
前$2^{k-1}sum $%10 和与后$2^{k-1}sum $%10和 是否大于10   
复杂度（$O(nlogn)$）比其他人慢了一些，但思路很简单   
上代码   
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#define inf 0x3f3f3f3f
#define N 100010
using namespace std;
int n,a[N],sum[N],f[N][20],q;
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n+1;i++)sum[i]=sum[i-1]+a[i];
	for(int k=1;k<=log2(n)+1;k++){
		for(int i=1;i+(1<<k)-1<=n;i++){
			f[i][k]=f[i][k-1]+f[i+(1<<(k-1))][k-1]+(((sum[i+(1<<(k-1))-1]-sum[i-1])%10+(sum[i+(1<<k)-1]-sum[i+(1<<(k-1))-1])%10)>=10?1:0);
		}
	}
	q=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		int k=log2(r-l+1);
		printf("%d\n",f[l][k]); 
	}
	return 0;
}

```


---

## 作者：SkyRainWind (赞：3)

现场写了线段树的sb来报道>_<

发现长度为 $2^k$，而两两之间的合并非常像线段树的左右儿子的合并，所以这个问题完美适用于线段树，所以$O(qlogn)$做完了>_<

当然，这题有一个简单做法就是直接前缀和出结果。

~~没有修改，其实也不难写，我只花了10min~~

代码：
```cpp
// by Balloons
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define mpr make_pair
#define debug() puts("okkkkkkkk")
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)

using namespace std;

typedef long long LL;

const int inf = 1 << 30;
const int maxn=1e5+5;

int n;
int a[maxn];
struct segm{
	int l,r,v;
	int sum;
	LL cd;
}se[maxn<<2];

void build(int x,int y,int num){
	if(x==y){
		se[num].sum=a[x];
		se[num].cd=0;
		return ;
	}
	int mid=x+y>>1;
	build(x,mid,num<<1);build(mid+1,y,num<<1|1);
	se[num].sum=(se[num<<1].sum+se[num<<1|1].sum)%10;

	se[num].cd=se[num<<1].cd+se[num<<1|1].cd;
	se[num].cd+=(se[num<<1].sum+se[num<<1|1].sum)/10;
}

pair<int,LL> query(int l,int r,int x,int y,int num){
	if(l<=x && y<=r){
		return mpr(se[num].sum,se[num].cd);
	}
	pair<int,LL>cur;
	int mid=x+y>>1;
	if(r<=mid)cur=query(l,r,x,mid,num<<1);
	else if(l>mid)cur=query(l,r,mid+1,y,num<<1|1);
	else{
		cur=query(l,r,x,mid,num<<1);
		pair<int,LL>cur2=query(l,r,mid+1,y,num<<1|1);
		cur.first+=cur2.first;cur.second+=cur2.second;
		cur.second+=cur.first/10;cur.first%=10;
	}
	return cur;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	build(1,n,1);
	
	int qu;scanf("%d",&qu);
	while(qu--){
		int l,r;scanf("%d%d",&l,&r);
		printf("%I64d\n",query(l,r,1,n,1).second);
	}

	return 0;
}

```

---

## 作者：AC_Dolphin (赞：3)

复杂度比上一篇题解低。

看到大量的区间求和时首先想到了前缀和，记$c$为前缀和数组，即$c_i=c_{i-1}+a_i$。然后我们~~经试验~~知$ans$即为区间$[l,r]$的和$/10$，即$ans=(c_r-c_{l-1})/10$。

总时间复杂度$O(n)$.

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 100010
int a[MAXN],n,cnt,m,q,l,r,c[MAXN];
template<typename T>
inline void read(T& x){
    x=0;
    int f(1);
    char ch(getchar());
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    x=f*x;
}
int main(){
    read(n);
    for(register int i(1);i<=n;++i) {read(a[i]);c[i]=c[i-1]+a[i];}
    read(q);
    while(q--){
        read(l);read(r);
        int sum=c[r]-c[l-1];
        cout<<sum/10<<endl;
    }
    return 0;
}
```

---

## 作者：开始新的记忆 (赞：1)

想了半天也没有想出其他写题解的大佬是怎么写出DP的？？
我一个蒟蒻动用了秘术·玄学（咳咳咳跑偏了）（接下来开始概率论）因为每次都要使a2i和a2i+1加起来，看是否大于10，如果大于则a2i+a2i+1%10很可能小于4，同理则如果小于10那么和很可能是大于6的（其中概率占了大概75%）而0--6和14-19之中概率是相等的，所以只需前缀和一波然后看着一段的和并/10即可


```cpp
#include<iostream>
using namespace std;
int main()
{   int n,q,a[100010],ans[100010];
    cin>>n;
    ans[0]=0;
    for(int i=1;i<=n;++i)
    {
        cin>>a[i];
        ans[i]=ans[i-1]+a[i];
    }
    cin>>q;
    while(q--)
    {
        int x,y;
        cin>>x>>y;
        cout<<(ans[y]-ans[x-1])/10<<endl; 
    }
    return 0;
}
```


---

## 作者：万弘 (赞：1)

[CF1189(Div.2)题解(全)](https://blog.csdn.net/whsstory/article/details/95317811)

## C. Candies!

题意:对于一个序列$a_1,a_2,a_3...a_{2^k}$,将$(a_{2i},a_{2i+1})$替换为$(a_{2i}+a_{2i+1})mod\ 10$,并得到$\lfloor \frac{a_{2i}+a_{2i+1}}{10}\rfloor$颗糖果.显然,通过这样的一次操作,序列长度由$2^k$变为$2^{k-1}$.  
给出一个长为$n (1≤n≤10^5)$的序列,你要回答$(1≤q≤10^5)$个查询.每次查询给出$l,r$,求区间$[l,r]$通过上述操作可得到多少糖果(保证$r-l+1$是2的整数次幂)

题解:`设[l,r]可得到的糖果个数为f(l,r)`,则有$$f(l,r)=\lfloor \frac{(\sum _{i=l}^r a_i)}{10}\rfloor$$  
(证明请见下方"证明"部分)  
只要$O(n)$预处理出前缀和$s$,则有$$f(l,r)=\lfloor \frac{s_r-s_{l-1}}{10}\rfloor$$  
时间显然$O(n+q)$.(还有倍增的写法,但在此不赘述)

证明:(我的证明可能比较奇特)  
考虑模的性质,$$(a+b)mod\ p=(a\ mod\ p+b\ mod\ p)mod\ p$$
所以直接把区间$[l,r]$的和模10的余等于题述那样老实算得到的余数  
而区间$[l,r]$的和是一定的.`设区间[l,r]的和为k,最后得到的糖果数为t`,则有  
$$rest=k\%10,\quad k=10t+rest$$
所以其实t就是k除以10的商(~~小学数学么~~) .而两种方法的k与r都一样,t也就一样了.
```cpp
/**********/
#define MAXN 200011
ll s[MAXN];
ll calc(ll l,ll r)
{
	return s[r]-s[l-1];
}
int main()
{
	ll n=read();//快读已省略
	s[0]=0;
	for(ll i=1;i<=n;++i)s[i]=s[i-1]+read();
	ll q=read();
	while(q--)
	{
		ll l=read(),r=read();
		std::cout<<calc(l,r)/10<<std::endl;
	}
	return 0;
}
```

---

## 作者：览遍千秋 (赞：1)

每次合并的情况可以分两类讨论：

 - 可以获得糖果

 - 不可以获得糖果

---

## 可以获得糖果

此时，$a+b>=10$，合并的结果是$a+b-10$，获得的价值为1.

## 不可以获得糖果

此时，$a+b<10$，合并的结果是$a+b$，获得的价值为0.

---

可以发现，合并区间$[l,r]$，直接求这个区间的所有权值和$s$，$ans=s/10$（下取整）。

那么求区间和，用前缀和就行了。

这样的话时间复杂度是$O(n)$的。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define maxn 100005

int n,q,x,y;
long long a[maxn],s[maxn];

template <typename Tp>
void read(Tp &x){
    x=0;char ch=1;int fh;
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-'){
        fh=-1;ch=getchar();
    }
    else fh=1;
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    x*=fh;
}


int main(){
    read(n);
    for(register int i=1;i<=n;i++){
        read(a[i]);s[i]=s[i-1]+a[i];
    }  
    read(q);
    while(q--){
        read(x);read(y);
        printf("%I64d\n",(s[y]-s[x-1])/10);
    }
    return 0;
}
```

---

## 作者：Imakf (赞：1)

你发现你要处理的区间长度正好是 $2$ 的整数次幂

其中长度为 $2^k$ 的区间的贡献可以由两个长度为 $2^{k-1}$ 的区间得到

线段树？

倍增啊兄弟，预处理复杂度 $O(n \log n)$

```
sum[j][i] 表示 左端点为 j 向右长度为 2^i 的区间和 mod 10
就是对这个区间进行很多次操作，最后剩下来的那个数

candy[j][i] 表示 左端点为 j 向右长度为 2^i 的区间进行很多次操作获得的糖果数量

for(rg int i = 1 ; i <= log2(MX) + 1 ; ++i){
	for(rg int j = 1 ; j + (1 << (i)) - 1 <= n ; ++j){
   		 sum[j][i] = sum[j][i - 1] + sum[j + (1 << (i - 1))][i - 1] % 10;
   		 candy[j][i] = (sum[j][i - 1] + sum[j + (1 << (i - 1))][i - 1]) / 10;
   		 candy[j][i] += candy[j][i - 1] + candy[j + (1 << (i - 1))][i - 1];
	}
}
```

最后查询的时候对区间长度取 log2 直接 $O(1)$ 查询

总复杂度 $O(n \log n)$

记得倍增循环的顺序别搞错了

```cpp
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<cmath>
 
#define rg register
#define il inline
#define MX (100000 + 5)
 
int n;
int A[MX];
int candy[MX][25];
int sum[MX][25];
 
int main(){
	int n;
	scanf("%d" ,&n);
	for(rg int i = 1 ; i <= n ; ++i)
		scanf("%d" ,&sum[i][0]);
	for(rg int i = 1 ; i < 25 ; ++i){
		for(rg int j = 1 ; j <= n && (j + (1 << i) - 1 <= n); ++j){
			sum[j][i] = (sum[j][i - 1] + sum[j + (1 << (i - 1))][i - 1]) % 10;
			candy[j][i] = (sum[j][i - 1] + sum[j + (1 << (i - 1))][i - 1]) / 10;
			candy[j][i] += candy[j][i - 1] + candy[j + (1 << (i - 1))][i - 1];
		}
	}
	int t;
	scanf("%d" ,&t);
	for(rg int i = 1 ,l ,r ; i <= t ; ++i){
		scanf("%d%d" ,&l ,&r);
		int k = log2(r - l + 1);
		printf("%d \n" ,candy[l][k]);
	}
	return 0;
}
```


---

## 作者：cz666 (赞：0)

## 题意简述：

### 众所周知题面写得长多半是在考语文题！

这道题的意思就是给定一个数列，这个数列每个位置上的数字都小于十 ，然后会有好多个小朋友来拿这些数字，每个小朋友能拿 $l$ 到 $r$ 的所有数字，他们会去换糖吃，他们拿的糖的数量就是他们拿的数字序列中相邻之和大于十的数对对数，求每个小朋友能拿到多少糖。

## 具体思路：

既然是相邻大于10就能有一个糖，而每个数都是小于十的，也就是说每相邻两个数之和一定小于 $20$ ，所以也就是说加起来去除以十最多一次也是只能获得一颗糖。

这个小小的（规律？）启发了我们，所以就有了下面的方法：

可以先对这个数列做一遍前缀和，记录的是糖果数量的前缀和，然后对于每个小朋友而言，直接做 $(sum[r]-sum[l-1])/10$ ，这个就是这个小朋友能获得的糖果数，正确性因为上面的（规律？）显然。

## AC代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define dd c=getchar()
inline int read(){int s=0,w=1;char c;while (dd,c>'9' || c<'0') if (c=='-') w=-1;while (c>='0' && c<='9') s=s*10+c-'0',dd;return s*w;}
inline void write(int x){if (x<0) putchar('-'),x=-x;if (x>=10) write(x/10);putchar(x%10|'0');}
inline void wln(int x){write(x);puts("");}
inline void wlk(int x){write(x);printf(" ");}
#undef dd
int a[100003];
signed main(){
	int n=read();
	for (register int i=1;i<=n;++i) a[i]=a[i-1]+read();
	int q=read();
	for (register int i=1;i<=q;++i){
		int l=read(),r=read();
		wln((a[r]-a[l-1])/10);
	}
	return 0;
}
```



---

## 作者：wxy_god (赞：0)

别人都是数论推出来的，我是找规律找出来的（这不是笑话）  
我手里没有其他数据，那么我就开始观察样例  
第一个数列：  
$8\ 7\ 3\ 1\ 7\ 0\ 9\ 4$  
第一个$query$的范围是$[1,8]$，就是整个数列$8\ 7\ 3\ 1\ 7\ 0\ 9\ 4$，答案是$3$；  
第二个$query$的范围是$[2,5]$，查询数列是$7\ 3\ 1\ 7$，答案是$1$；  
第三个$query$的范围是$[7,7]$，查询数列是$9$，答案是$0$。  
这似乎没有什么规律（我一开始也是这么想的）  
一般来说，这种题只跟和或者乘积有关，我就先想到用和找规律（因为整个操作没有啥是关于乘法的）  
接着，我受到题目中$mod\ 10$的启发，想到，会不会跟$10$的商或者余数有关呢？  
先看余数。第一个数列和处以$10$的余数是$9$，第二个是$8$，第三个是$9$。  
跟答案好像没有啥关系。（如果您找到规律了私信告诉我）  
接着看商。第一个的商是$3$，第二个的商是$1$，第三个的商是$0$，跟答案一模一样。  
此方法同样使用在样例$2$。  
所以我们维护一个前缀和，每次查询时，算出$[l,r]$的和，用它除以$10$即可。

---

## 作者：世末OIer (赞：0)

额，有一种简单的方法，比赛的时候没有想到，只用了倍增。

现在介绍一种简单的方法。

---

对于这道题目。如果我们直到最后再一起取糖果，就会发现，其实就是sum[l,r]/10下取整吗！

现在只需要一个前缀和就可以搞定了qwq

```cpp
int main(){
    read(n);
    for(register int i(1);i<=n;++i) {read(a[i]);c[i]=c[i-1]+a[i];} //预处理前缀和
    read(q);
    while(q--){
        read(l);read(r);
        int sum=c[r]-c[l-1]; //取出前缀和
        cout<<sum/10<<endl;
    }
    return 0;
}
```

---

