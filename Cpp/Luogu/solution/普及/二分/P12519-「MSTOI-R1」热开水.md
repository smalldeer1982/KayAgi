# 「MSTOI-R1」热开水

## 题目背景

小 M 最近在玩一款新游戏，$rks$ 是这款游戏中评判玩家实力的数值。$rks$ 分为单曲 $rks$ 和总 $rks$，它们都是两位小数。

游玩一首曲子后，会获得一个评分  $acc$（即准度），以百分比的形式表现。

## 题目描述

每首曲子都有一个难度定数。当一个曲的 $acc\ge 70\%$ 时，这个曲才会计算 $rks$，否则该曲 $rks$ 为 $0$。单曲 $rks=[\frac{(100\times acc-55)}{45}]^2\times$ 难度定数 。

如果一个曲你游玩了多次，那么这个曲的单曲 $rks$ 会保留最高的一次。总 $rks=$ 最大的 $4$ 个单曲 $rks$ 和 $acc$ 为 $100\%$ 的曲里面最大的单曲 $rks$（如果没有 $acc$ 为 $100\%$ 的曲子则将这一项的值视为 $0$）这 $5$ 个单曲 $rks$ 的平均值。

为了方便表示和计算，单曲 $rks$ 和总 $rks$ 都应保留 $2$ 位小数（非四舍五入）。

小 M 有 $n$ 首曲子可以玩，对于第 $i$ 首曲子，难度定数为 $c_i$，小 M 第 $1$ 天玩的 $acc$ 可以达到 $a_i\%$，第 $k$ 天可以达到 $min(100\%,a_i\%+(k-1)\times b_i\%)$。小 M 每天都会游玩这 $n$ 首曲子，请问小 M 最早在第几天总 $rks$ 可以 $\ge m$。

## 说明/提示

数据保证**输入的小数都是两位小数**。注意**计算过程中的所有小数您都应该保留两位小数（非四舍五入）**（例如包括计算单曲 $rks$ 时 $\div 45$ 之后，也要保留 $2$ 位小数再继续计算），否则可能会与答案存在偏差。

建议您使用下面这段代码进行保留两位小数：

```cpp
double retain2(double x)
{
	int y;
	double z;
	x*=100;
	y=x;
	z=y/100.0;
	return z;
}
```

对于 $100\%$ 的数据，$1\le n\le10^5$，$0\le m\le17$，$0\le a_i\le100$，$0.01\le b_i\le100$，$1\le c_i\le17$，$0\le d_i\le17$。

测试点|特殊性质
---|---
$1\sim3$|$n\le100$
$4$|$m=0$
$5$|$d_i=0$
$6\sim10$|$n\le10^3$
$11\sim15$|$n\le10^4$
$16\sim20$|无

## 样例 #1

### 输入

```
3 8.31
70.00 10.00 9.50
60.00 40.00 9.00
50.00 10.00 9.10
8.00 0.00 9.00 8.00 9.00```

### 输出

```
2```

## 样例 #2

### 输入

```
3 11.00
70.00 10.00 9.50
100.00 10.00 9.00
50.00 10.00 9.10
15.10 15.10 15.10 15.10 15.10```

### 输出

```
0```

# 题解

## 作者：Vocaloid世末歌者 (赞：13)

前言：mst 可爱喵/qq

验题人写个题解。

发现有单调性且是经典的“最早在第几天”，于是考虑二分。

`check` 函数按计算方式暴力找出现在的 $rks$ 即可，详见代码。

有个比较奶龙的地方是（不知道你们会不会踩这个坑），要小心精度的问题，要开 `double`，而且计算时要 `(double)` 而不是 `1.0*`。

```cpp
#include<stdio.h>
#include<bits/stdc++.h>
#define N 1000010
#define MOD 998244353
#define esp 1e-8
#define INF 999999999999999999
#define LL long long
#define rep(i,a,b,g) for(LL i=a;i<=b;i+=g)
#define rem(i,a,b,g) for(LL i=a;i>=b;i-=g)
#define repn(i,a,b,g) for(LL i=a;i<b;i+=g)
#define remn(i,a,b,g) for(LL i=a;i>b;i-=g)
#define pll pair<LL,LL>
#define mkp(x,y) make_pair(x,y)
#define i128 __int128
#define lowbit(x) ((x)&(-(x)))
#define lc (u<<1)
#define rc (u<<1|1)
using namespace std;
void read(i128 &x)
{
	i128 f=1;
	x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}
void writing(i128 x)
{
	if(x>=10)writing(x/10);
	putchar(x%10+'0');
}
void write(i128 x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	writing(x);
}
LL n;
double m;
struct song
{
	double a,b,c;
}a[100010];
double bl(double x)
{
	LL y;
	double z;
	x*=100;
	y=x;
	z=y/100.0;
	return z;
}
struct son
{
	double rks,acc;
}b[100010];
double d[10],td[10],sum,mc,tt[20];
LL l=-1,r=1000000001,mid;
bool cmp(son x,son y)
{
	return x.rks>y.rks;
}
bool che(LL mid)
{
//	cout<<mid<<"::"<<endl;
	if(mid==0)
	{
		sum=0;
		rep(i,1,5,1)
		{
			sum+=d[i];
			sum=bl(sum);
		}
		sum/=5;
		sum=bl(sum);
		return (sum>=m);
	}
	rep(i,1,5,1)td[i]=d[i];
	mc=0;
	rep(i,1,n,1)
	{
		b[i].acc=min((double)100,bl(a[i].a+bl((double)(mid-1)*a[i].b)));
		b[i].acc=bl(b[i].acc);
		if(b[i].acc>=(double)70)
		{
			b[i].rks=bl(bl(bl((b[i].acc-(double)55)/(double)45)*bl((b[i].acc-(double)55)/(double)45))*a[i].c);
		}
		else b[i].rks=0;
		if(b[i].acc==(double)100)
		{
			mc=max(mc,b[i].rks);
			mc=bl(mc);
		}
//		cout<<i<<':'<<b[i].rks<<' ';
	}
//	cout<<endl;
	sort(b+1,b+n+1,cmp);
	sum=0;
	rep(i,1,4,1)
	{
		tt[i]=td[i];
	}
	rep(i,5,8,1)
	{
		tt[i]=b[i-4].rks;
	}
	sort(tt+1,tt+8+1);
	rem(i,4,1,1)
	{
		td[i]=tt[8-i+1];
	}
	td[5]=max(td[5],mc);
	td[5]=bl(td[5]);
	rep(i,1,5,1)
	{
		sum+=td[i];
		sum=bl(sum);
	}
	sum/=5;
	sum=bl(sum);
//	cout<<mid<<' '<<sum<<endl;
	return (sum>=m);
}
int main()
{
	cin>>n>>m;
	rep(i,1,n,1)
	{
		cin>>a[i].a>>a[i].b>>a[i].c;
	}
	rep(i,1,5,1)cin>>d[i];
	while(l+1<r)
	{
		mid=l+r>>1;
		if(che(mid))r=mid;
		else l=mid;
	}
	if(!che(r))cout<<-1<<endl;
	else cout<<r<<endl;
	return 0;
}
```

---

## 作者：MinimumSpanningTree (赞：9)

[题目链接](https://www.luogu.com.cn/problem/P12519)

2025.6.27 upd：修改了一个小问题。

因为玩的天数越多 rks 也会越多或不变，所以答案是具有单调性的，故考虑二分答案。

接下来思考在已知天数的情况下求 rks。可以用优先队列维护最高的 $5$ 首单曲 rks，变量维护最大 $acc=100\%$ 曲的 rks。枚举每一首曲计算出新的 rks，分类讨论，$<70\%$ 的直接不要，否则加入优先队列，如果 $=100\%$ 再取最大值。最后取出队头的 $5$ 首就可以计算总 rks。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
const int N=1e5+100;
int l=-1,r=10002,mid,n;
double m,a[N],b[N],c[N],st[N];
double retain2(double x)
{
	int y;
	double z;
	x*=100;
	y=x;
	z=y/100.0;
	return z;
}
bool check(int x)
{
	priority_queue<double> pq;
	double acc,rks,sum,ma=st[5];
	for(int i=1;i<=4;i++) pq.push(st[i]);
	for(int i=1;i<=n;i++)
	{
		acc=min(100.0,retain2(a[i]+retain2((x-1)*b[i])));
		if(acc>=70) rks=retain2(retain2(retain2((acc-55)/45.0)*retain2((acc-55)/45.0))*c[i]);
		else rks=0;
		if(acc==100) ma=max(ma,rks);
		if(x>0) pq.push(rks);
	}
	sum=ma;
	for(int i=1;i<=4;i++)
	{
		sum+=pq.top();
		pq.pop();
	}
	sum=retain2(sum/5.0);
	return sum>=m;
}
int main()
{
	scanf("%d%lf",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lf%lf%lf",&a[i],&b[i],&c[i]);
	for(int i=1;i<=5;i++) scanf("%lf",&st[i]);
	while(l+1<r)
	{
		mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid;
	}
	if(r==10002) r=-1;
	printf("%d",r);
	return 0;
}
```

---

## 作者：chenzefan (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P12519)
## 前言
看是道黄题，来写篇题解。

阅读理解题。
## 涉及知识
- 二分算法。
## 思路
如果读完题目没有思路，看到这句话“如果不能做到，请输出 `-1`”。这句话，你应该知道，这题可以骗分。

输出 `-1`，有 $5$pts。毕竟蚊子再小也是肉，有分总比没分好。

### 骗分代码
非常简单的喵。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    printf("-1");
    return 0;
}
```
正解：二分。

check 函数用来计算现在的 $rks$。

题目也提醒了，要注意保留小数问题，我们使用题目给的函数。
```cpp
double retain2(double x)
{
	int y;
	double z;
	x*=100;
	y=x;
	z=y/100.0;
	return z;
}
```
然后，check 函数按照题目所说模拟即可。

- 时刻保留两位小数！注意类型是 `double`。
- 当一个曲的 $acc \ge 70 \%$ 时，这个曲才会计算 $rks$，否则该曲 $rks$ 为 $0$。

整理一下题目给的公式：

- 公式一：单曲 $rks=[\frac{100×acc−55}{45}]^2 \times$ 难度定数。
- 公式二：总 $rks=$ 最大的 $4$ 个单曲 $rks$ 和 $acc$ 为 $100%$ 的曲里面最大的单曲 $rks$（如果没有 $acc$ 为 $100%$ 的曲子则将这一项的值视为 $0$）这 $5$ 个单曲 $rks$ 的平均值。
- 公式三：小 M 第 $1$ 天玩的 $acc$ 可以达到 $a_i \%$，第 $k$ 天可以达到 $\min(100 \%，a_i \% +(k-1) \times b_i \%)$。

代码来了 **↓**。时间复杂度 $O(n \times \log(n))$。变量的类型要看清楚。
## 代码(含注释)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n;
double m,d[10],d1[10];
struct node{
	double a,b,c,rks;
}a[N];
double retain2(double x){//保留两位小数 
	int y;double z;
	x*=100;y=x;
	z=y/100.0;
	return z;
}
bool check(int mid){//最关键的一步 
	memcpy(d1,d,sizeof(d1));//神奇的函数，仅用于复制 
	for(int i=1;i<=n;i++){
		double acc=min(100.0,a[i].a+(mid-1)*a[i].b);//求难度定数 acc（公式三） 
		//求 rks （公式一） 
		if(acc<=70) a[i].rks=0;
		else a[i].rks=retain2(retain2((acc-55.0)/45.0)*retain2((acc-55.0)/45.0)*a[i].c);
		if(a[i].rks>d1[1]) d1[1]=a[i].rks;//更换，保证最大 
		if(acc==100) d1[5]=max(d1[5],a[i].rks);
		double zong_rks=retain2((d1[1]+d1[2]+d1[3]+d1[4]+d1[5])/5.0);//求平均值（公式二） 
		if(zong_rks>=m) return 1;
		for(int j=1;j<=3;j++){//枚举 d 数组 
			if(d1[j]>d1[j+1]) swap(d1[j],d1[j+1]);
			else break;
		}
	}return 0; 
}
int main(){
    scanf("%d%lf",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lf%lf%lf",&a[i].a,&a[i].b,&a[i].c);//题目的 a[i]、b[i] 和 c[i] 
    for(int i=1;i<=5;i++) scanf("%lf",d+i);
    sort(d+1,d+4);//只要排序前 4 个 
    int l=0,r=10000,ans=-1;//给 ans 初始值赋 -1，输出就不用特判了 
	while(l<=r){//二分模板 
		int mid=l+r>>1;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}printf("%d",ans);
	return 0;
}

```
祝各位 OIer 都可以愉快地切了这题！

---

## 作者：linyuhang0927 (赞：1)

###  [题目传送门](https://www.luogu.com.cn/problem/P12519)

## 前言

第一次写题解，大佬勿喷。

### 大概思路

因为 $acc$ 会随着天数而增加，$rks$ 也会不断的增加。$acc$ 和 $rks$ 都是增加或不变，有单调性。于是考虑使用二分来做。

### 下面是代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m;
int l = -1, r = 1005, mid;
double a[N], b[N], c[N];
double z[N];

double retain2(double x) {
    int y;
    double z; 
    x *= 100;
    y = x;
    z = y / 100.0;
    return z;
}

bool check(double x) {// 判断函数，用于二分查找
    priority_queue<double>q;  // 优先队列，用于存储最大的4个值
    double acc, rks, sum, MAX = z[5];  // 计算中间变量和最大值
    for (int i = 1; i <= 4; i++) {// 初始化优先队列
        q.push(z[i]);
    }
    for (int i = 1; i <= n; i++) { // 处理每组数据
        acc = min(100.0, retain2(a[i] + retain2((x - 1) * b[i])));// 计算acc值，限制不超过100
        if (acc > 70) {// 根据acc值计算rks
            rks = retain2(retain2(retain2((acc - 55) / 45.0) * retain2((acc - 55) / 45.0)) * c[i]);
        } else {
            rks = 0;
        }
        if (acc == 100) {// 更新最大值
            MAX = max(MAX, rks);
        }
        if (x > 0) {// 将rks加入优先队列
            q.push(rks);
        }
    }
    sum = MAX;// 计算总和
    for (int i = 1; i <= 4; i++) {
        sum += q.top();  // 取最大值
        q.pop();  // 弹出最大值
    }
    sum = retain2(sum / 5.0); // 计算平均值并保留两位小数
    return sum >= m;  // 返回是否达到目标值
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    for (int i = 1; i <= 5; i++) {
        cin >> z[i];
    }
    while (l + 1 < r) {// 二分查找
        double mid = (l + r) / 2;
        if (check(mid)) {  // 如果满足条件，缩小右边界
            r = mid;
        } else {  // 否则缩小左边界
            l = mid;
        }
    }
    if (r == 1005) {// 处理特殊情况
        r = -1;
    }
    cout << r;// 输出结果
    return 0;
}

```
### 注意事项
- 注意保留两位小数。
- 注意特判输出 $-1$，不然只能得 $95$ 分。

---

## 作者：wzy0 (赞：1)

作者：rks 只有 4.7 的 phigros 玩家路过。 \
讲个笑话，因为在程序中使用 `long double` 导致精度问题，喜提 [95](https://www.luogu.com.cn/record/218127914)。

读题，发现是问**最早**的满足条件的时间。 \
又因为对于同一曲目 $acc$ 具有单调性，所以单曲 $rks$ 具有单调性。 \
这十分经典，于是我们考虑二分答案，直接暴力模拟计算总 $rks$。

总时间复杂度 $O(n \log r)$，$r$ 是 $\max{ \lceil \frac{100}{B_i} \rceil }$。 \
为了方便，我们将 $r$ 设为定值。 \
官方题解中 $r$ 开到了 $10^9 +1$。经过数据分析，开到 $10^4 +1$ 即可。

### 细节问题
>- 因为需要求前 4 个最大值，还需要一个堆来维护答案。
>- 注意精度问题，**使用 double**。每次运算结果只保留两位小数，建议直接复制题目给的函数使用。
>- 注意一个曲目的 $acc < 70\% $ 时，$rks$ 应为 $0$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,l,r,id;
double m,a[100005],b[100005],c[100005],d[10],f[10],h,t;

double qz(double i){
	long long j;double k;
	i*=100;
	j=i;
	k=j/100.0;
	return k;
}

long long jh(long long i,long long j){//堆的模板 可以跳过不读
	double k=f[i];
	f[i]=f[j];f[j]=k;
	return 0;
}
long long sy(long long i){
	while(i>1){
		if(f[i/2]>f[i]){
			jh(i/2,i),i/=2;
		}else break;
	}
	return 0;
}
long long xy(long long i){
	while(i*2<5){
		if(i*2+1<5){
			if(f[i]>f[i*2] || f[i]>f[i*2+1]){
				if(f[i*2]>f[i*2+1]){
					jh(i,i*2+1);
					i*=2;i++;
				}else{
					jh(i,i*2);i*=2;
				}
			}else break;
		}else{
			if(f[i]>f[i*2]){
				jh(i,i*2);
			}
			break;
		}
	}
	return 0;
}

long long sz(long long k){//计算 总rks 
	for(int i=1;i<5;i++)f[i]=d[i],sy(i);f[5]=d[5];//初始化 
	for(int i=1;i<=n;i++){
		t=min((double)100,qz(a[i]+qz((double)k*b[i]-b[i])));t=qz(t);//acc 
		if(t>=(double)70){
			h=qz((t-(double)55.0)/45.0);h=qz(h*h);h=qz(h*c[i]);//rks 
			if(h>f[1])f[1]=h,xy(1);
			if(t>=(double)100){
				f[5]=max(f[5],h);f[5]=qz(f[5]);
			}
		}
	}
	h=0;
	for(int i=1;i<=5;i++){
		h+=f[i];h=qz(h);
	}
	if(qz(h/5)>=m)return 1;
	else return 0;
	return -1;
}

int main(){
	ios::sync_with_stdio(0);cin.tie();cout.tie();
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>c[i];
	}
	for(int i=1;i<=5;i++)cin>>d[i],t+=d[i];
	if(qz(t/5)>=m){//初始成绩已满足 
		cout<<0;
	}else{
		l=0,r=10004;
		while(l<=r){//二分答案 
			id=(l+r)/2;
			if(sz(id)==1)r=id-1;
			else l=id+1;
		}
		if(r==10004){
			cout<<-1;
		}else{
			cout<<r+1;
		}
	}
	return 0;
}
```

---

## 作者：Cipher0128 (赞：1)

随着天数增加，$acc$ 会增加，从而 $rks$ 增加，就更可能满足限制。

由于具有单调性，可以考虑二分。

二分天数，然后判断此时是否满足限制，找到最小的满足限制的天数就是答案。

注意特判 $0$ 天。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define for_(a,b,c) for(int a=b;a<=c;++a)
#define For_(a,b,c) for(int a=b;a>=c;--a)
using namespace std;
int n;
double m;
const int N=1e5+10;
double a[N],b[N],c[N],acc[N],rks[N];
double d[6],dd[6];
void f(double &x){ 
	ll y;double z;
	y=x*100;
	z=y/100.0;
	x=z;
}
bool check(int mid){
	for_(i,1,5)dd[i]=d[i];
	for_(i,1,n){
		acc[i]=(mid-1)*b[i]+a[i];f(acc[i]); 
		acc[i]=min(acc[i],100.00);
		if(acc[i]>=70.00){
			double res=acc[i]-55;f(res);
			res/=45.00;f(res);
			rks[i]=res*res;f(rks[i]);
			rks[i]*=c[i];f(rks[i]);
		}
		else rks[i]=0;
		if(acc[i]==100.00)dd[5]=max(dd[5],rks[i]);
	}
	for_(i,n+1,n+4)rks[i]=dd[i-n];
	sort(rks+1,rks+1+n+4);
	double s=dd[5];
	For_(i,n+4,n+1)s+=rks[i],f(s);
	s/=5.0;f(s);
	return s>=m;
}
int main(){
	cin>>n>>m;
	for_(i,1,n)cin>>a[i]>>b[i]>>c[i];
	double s0=0;
	for_(i,1,5){
		cin>>d[i];
		s0+=d[i];
	}
	if(s0>=m*5.0){
		cout<<0;return 0;
	}
	int l=1,r=1e9;
	int ans=-1;
	while(l<r){
		int mid=l+r>>1;
		if(check(mid))ans=mid,r=mid;
		else l=mid+1;
	}
	cout<<ans;  
	return 0;
}
```

---

## 作者：c_y_y (赞：1)

# [P12519 「MSTOI-R1」热开水 题解](https://www.luogu.com.cn/problem/P12519) 

题面的一切指向了某 P 开头的音游~

注意到 $b_i$ 是个正数，

因此第二天一个曲目的 $rks$ 一定不小于第一天。因此发现总 $rks$ 随天数增加而单调不降。**本题具有单调性，考虑二分。**

如何实现 `check()` 函数呢？按题意模拟就好了~

但是有以下几个细节：

- 一个曲目的 $acc \le 70\%$ 时，该区 $rks$ 应为 $0$。
- 对于所有的计算结果后，都应保留两位小数。
- 记得初始化！！！

同时对于本题，笔者有以下的小优化可以使实现更简单：

- 记 $b_0$ 为所有 $acc = 100\%$ 的曲目中 $rks$ 的最大值，$b_i (1 \le i \le 4)$ 为最大的四个 $rks$。  
  先将 $b_i (1 \le i \le 4)$ 升序排列。当我们计算出一个新的 $rks$ 时，如果其 $rks > b_1$ 就将其替换，并在最后像插入排序一样保持 $b$ 数组升序。注意 $b_0$ 不参与排序。
  
- 由于 $b$ 的长度很小，因此计算总 $rks$ 时，可直接暴力求解；

## Code
```cpp
const int N = 1e5 + 10, mod = 998244353;
double rt2(double x) {
	int y;
	double z;
	x *= 100, y = x;
	z = y / 100.0;
	return z;
}
struct node {
	double a, b, c, rks;
}a[N];
double b[6], tb[6], m;
int n;
bool check(int k) {
	double rks = 0;
	memcpy(b, tb, sizeof tb);
	for (int i = 1; i <= n; i++) {
		double acc = min(100.0, a[i].a + (k-1) * a[i].b);
		if(acc <= 70) a[i].rks = 0;
		else {
			a[i].rks = rt2((acc-55.0) / 45.0);
			a[i].rks = rt2(a[i].rks * a[i].rks * a[i].c);
		}
		if(a[i].rks > b[1]) b[1] = a[i].rks;
		
		if(acc == 100.0) b[0] = max(b[0], a[i].rks);
		double rks = rt2((b[0] + b[1] + b[2] + b[3] + b[4]) / 5.0);
		if(rks >= m) return true;
		for (int j = 1; j <= 3; j++) {
			if(b[j] > b[j + 1]) swap(b[j], b[j + 1]);
			else break;
		}
	}
	return false;
}
int main() {
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].a >> a[i].b >> a[i].c;
	}
	cin >> b[1] >> b[2] >> b[3] >> b[4] >> b[0];
	sort(b + 1, b + 5);
	for (int i = 0; i <= 4; i++) tb[i] = b[i];
	
	int l = 0, r = 10010, ans = -1;
	while(l <= r) {
		int mid = l + r >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	cout << ans << endl;
	return 0;
}
```

## Others
本题暴力有 $95$ 分。

Phi 好玩，都给我去打 Phi！

---

## 作者：prh_rpjiajia (赞：0)

关注到随着游戏天数的增加，玩家的各项分数（$acc$ 和 $rks$）只会保持不变或提升，因此总 $rks$ 具有单调不减的性质，因此考虑二分，二分最小天数。

`check` 函数的话，就是先算一下 $rks$，然后二分的同时维护前四大 $rks$ 即可。

这里我为了避免精度问题，是直接给百分数乘了个 $100$，用整数存，会稳妥一点。

```cpp
#include<bits/stdc++.h>
int n;
int A[100005],B[100005];
double Cc[100005],t40[4],pf0,m;
double r2(double x){int y;x*=100;y=x;return y/100.0;}// 保留两位小数（非四舍五入）
bool chk(int mid){// 检查mid天后是否满足条件
    double t0=t40[0],t1=t40[1],t2=t40[2],t3=t40[3],pf=pf0;// 复制当前最高分数和附加分数
    for(int i=0;i<n;i++){
        // 计算mid天后的acc（以整数形式存储，单位0.01%）
        long long ai=A[i]+(long long)(mid-1)*B[i];
        if(ai>10000) ai=10000; // 上限100%
        if(ai<7000) continue;// acc<70%不计
        // 计算单曲rks
        double acc=r2(ai/100.0);
        double x2=r2((acc-55.0)/45.0);
        double x3=r2(x2*x2);
        double rks=r2(x3*Cc[i]);
        if(ai==10000&&rks>pf) pf=rks;
        if(rks>t0){
            double a=t1,b=t2,c=t3;
            if(rks>=c){
                t0=a; t1=b; t2=c; t3=rks;
            }else if(rks>=b){
                t0=a; t1=b; t2=rks; t3=c;
            }else if(rks>=a){
                t0=a; t1=rks; t2=b; t3=c;
            }else{
                t0=rks; t1=a; t2=b; t3=c;
            }
        }
    }
    // 计算总rks
    double s=t0+t1+t2+t3+pf,avg=r2(s/5.0);
    return avg+1e-8>=m;// 处理浮点精度问题
}
int main(){
    scanf("%d%lf",&n,&m);
    double ai,bi,ci;
    for(int i=0;i<n;i++){
        scanf("%lf%lf%lf",&ai,&bi,&ci);
        A[i]=(int)(ai*100+0.5);
        B[i]=(int)(bi*100+0.5);
        Cc[i]=ci;
    }
    for(int i=0;i<4;i++) scanf("%lf",&t40[i]);
    scanf("%lf",&pf0);
    for(int i=0;i<3;i++)for(int j=i+1;j<4;j++)
        if(t40[i]>t40[j]){double u=t40[i];t40[i]=t40[j];t40[j]=u;}
    double s0=t40[0]+t40[1]+t40[2]+t40[3]+pf0;
    if(r2(s0/5.0)+1e-8>=m){
        printf("0");return 0;
    }
    int K=1;
    for(int i=0;i<n;i++){
        int D=10000-A[i];
        int d= D<=0?1:1+(D+B[i]-1)/B[i];
        if(d>K) K=d;
    }
    int l=1,r=K,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(chk(mid)){ans=mid;r=mid-1;}
        else l=mid+1;
    }
    if(ans<0) printf("-1"); else printf("%d",ans);
    return 0;
}
```

---

