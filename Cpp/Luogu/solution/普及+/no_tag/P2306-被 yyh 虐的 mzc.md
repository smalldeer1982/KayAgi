# 被 yyh 虐的 mzc

## 题目背景

mzc 与 djn 第三弹。


## 题目描述

mzc 家很有钱（开玩笑），他家有 $n$ 个男家丁（做过前两弹的都知道）。但这些都不足以挽救他被 yyh 虐的命运。于是他向你们发起了求救。

mzc 要派出男家丁与 yyh 大战，但他只能承载质量为 $m$ 的男家丁，现在他想知道她们（你没有看错）的战斗力之和是否打得过 yyh。

## 说明/提示

对于 $20\%$ 的数据，$n \le 1000$。

对于 $100\%$ 的数据，$n,m \le 10^5$，$0\le a_i,b_i \le 10$。

由于 mzc 大大十分着急，所以他只能等待一秒。

## 样例 #1

### 输入

```
3 100 100
7 10
6 1
1 2
```

### 输出

```
no
13
```

# 题解

## 作者：royzhu (赞：11)

**解法一：**

这题的m，n超级大， n,m<=100000

单纯的01背包肯定会TLE但是，ai和bi非常小，只ai,bi<=10
我们要如何利用ai和bi呢？

我们仔细的想一想后会发现：ai和bi一定会重复多次出现

我们可以用一个二维数组t来记录ai和bi的出现次数 

然后利用二进制的思想，把t[ai][bi]个aibi分成1，2，4.....个aibi

（因为这样可以通过相加得到1到t[ai][bi]个ai，bi。但只要log（t[ai][bi]）左右的时间可做到）

例如把20分成 1 2 4 8 5

这样做了之后，我们就可以做01背包了 
 
```cpp
#include<cstdio>
#include<algorithm>//这头文件有max 函数 
using namespace std;
struct lol{int a,c;} d[100010];//d[i].a相当于ai ,d[i].c相当于bi
int f[100010],t[11][11],len=0;
int main()
{
	int n,m,k;scanf("%d %d %d",&n,&m,&k);
	for(int i=1;i<=n;i++)
	{
		int x,y;scanf("%d %d",&x,&y);
		if(t[x][y]==0){d[++len].a=x;d[len].c=y;}//可同下同时删除 
		t[x][y]++;//统计aibi的出现次数 
	}
	for(int x=0;x<=10;x++)
	{
		for(int y=0;y<=10;y++)
		{
			int v=1;
			--t[x][y];//可同上同时删除 
			while(t[x][y]>=v){d[++len].a=x*v;d[len].c=y*v;t[x][y]-=v;v*=2;} 
			//利用二进制思想分 ，len统计个数 
			if(t[x][y]>0){d[++len].a=x*t[x][y];d[len].c=y*t[x][y];t[x][y]=0;}
			//把剩下存进来 
		}
	}
	/////////////////////////01背包 
	for(int i=1;i<=len;i++)
	{
		for(int j=m;j>=d[i].a;j--)
		{
			f[j]=max(f[j],f[j-d[i].a]+d[i].c);
		}
	}
	if(f[m]>=k)printf("yes\n");
	else printf("no\n");
	printf("%d",f[m]);
}
```
解法二：
o3+o2+01背包（黑科技）

---

## 作者：_ANIG_ (赞：5)

第一眼看：01背包的模板题。

但看到数据范围：$m,n≤10^5$。

如果按传统的01背包 $O(mn)$ 肯定TLE。

注意到 $a_i,b_i$ 的范围很小，最多只有 $10×10=100$ 种情况，所以可以直接枚举情况数。显然有重复的，于是这题便转化成了多重背包。

设 $f_{i,j,k}$ 为当前枚举到重量为 $i$ 价值为 $j$ ，总重量为 $k$ 时可以得到的最大价值。

为了操作方便，可以把 $f$ 压到 $2$ 维，第一位压成 $i×11+j$。

$f_{i×11+j,k} = \max\limits\limits_{r=0}^{r×i\le k}f_{i×11+j-1,k-r×i}+r×j$ 。

答案的状态就是 $f_{120,m}$。

如果直接按模板做，复杂度 $O(100nm)$ 连01背包都不如。还好多重背包可以优化。这里讲单调队列优化，使复杂度达到 $O(100m)$,即 $O(m)$，理论上是优于二进制优化的。

~~但双端队列的常数大，可能还没二进制优化快。~~

先看没有优化的代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int a[100005],b[100005];
int p[125];
int f[125][100005];
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;i++)p[a[i]*11+b[i]]++;
	for(int i=0;i<=10;i++){
		for(int j=0;j<=10;j++){
			for(int l=0;l<=m;l++){
				for(int r=0;r<=p[i*11+j];r++){
					if(l<r*i)break;
					f[i*11+j][l]=max(f[i*11+j][l],f[i*11+j-1][l-r*i]+r*j);
				}
			}
		}
	}
	if(f[120][m]<k){
		cout<<"no"<<endl;
	}else cout<<"yes"<<endl;
	cout<<f[120][m];
}
```
看到这么几行代码
```cpp
for(int l=0;l<=m;l++){
	for(int r=0;r<=p[i*11+j];r++){
		if(l<r*i)break;
		f[i*11+j][l]=max(f[i*11+j][l],f[i*11+j-1][l-r*i]+r*j);
	}
}
```
频繁求最大值。可以考虑使用单调队列求区间最大值。

但是要求的最大值并不是连续的整块，而是跳着求的。

可以把第二维分组，每组分别用一个单调队列维护。

由于 $f_{i×11+j,k}$ 用到的状态 $f_{i×11+j-1,t}$ 都满足 $k$ 与 $t$ 除以 $i$ 的余数相同，所以可以根据取模 $i$ 的余数分组。复杂度 $O(m)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int a[100005],b[100005];
int p[125];
int f[125][100005];
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
deque<int>q;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
	for(int i=1;i<=n;i++)p[a[i]*11+b[i]]++;
	int qx=0;
	for(register int j=0;j<=10;j++){
		qx+=p[j]*j;
        for(int r=0;r<=m;r++){
           	f[j][r]=qx;
		}
	}
	for(register int i=0;i<=10;i++){
		for(register int j=0;j<=10;j++){
            for(int l=0;l<i;l++){
            	q.clear();
            	for(int r=l;r<=m;r+=i){
            		while(q.size()&&(r-q.front())/i>p[i*11+j])q.pop_front();
            		while(q.size()&&f[i*11+j-1][q.front()]+(r-q.front())/i*j<=f[i*11+j-1][r])q.pop_back();
            		q.push_back(r);
            		f[i*11+j][r]=f[i*11+j-1][q.front()]+(r-q.front())/i*j;
				}
			}
		}
	}
	if(f[120][m]<k){
		cout<<"no"<<endl;
	}else cout<<"yes"<<endl;
	cout<<f[120][m];
}
```
这里有几个细节：

1. $i$ 为 $0$ 的情况要提前预处理。
2. pop_front的条件是大于，不是大于等于。

---

## 作者：dark_moon (赞：3)

## 题目及算法分析
这题，打开一看，呦，这不 $01$ 背包板子题嘛，几天不见，难度都到绿了！

然而，仔细看这个神奇的数据范围 $n,m \le 10^5 $ ，好家伙，这还真不能用 $O(nm)$ 的01背包了，所以我们考虑其他算法。

想了一圈，这就是个 $01$ 背包问题，于是糊涂地又读了读数据范围，嘿！ $ 0 ≤a_i ,b_i ≤ 10 $ ，我们就可以想到，有很多很多个男仆的属性是一样的，嗯......这不就是多重背包嘛！

想到这里，这道题就变成了一个多重背包的「模板题」而可以轻松解决，那么，如何解决一个多重背包？

有很多多重背包的解决方法，这里我们使用二进制优化的方法，它速度快、好理解且代码量少。

### 具体做法分析
我们可以用一个二维数组 $A_{ij}$ 存储一个质量是 $i$ 且战斗力是 $j$ 的男丁的数量，在之后用一个数组 $a_i$ 作为多重背包的标准数据（ $a_i$ 并不是一个单纯的一维数组，应是一个 $pair$ 或二维等能存下两个数值的数组），可以用 $A_{ij}$ 求出 $a_i$ 的每一个值。注意， $i$ 和 $j$ 的值是从 $0$ 到 $10$ ，一定要防止忽视了质量为 $0$ 的男丁，在循环 $i$ 和 $j$ 时从0开始就可以避免。

在求 $a_i$ 时，可以直接把多重背包的优化带上，多重背包的二进制优化请参考 [hnjzsyjyj的多重背包问题（二进制优化）](https://blog.csdn.net/hnjzsyjyj/article/details/109363826)
，主体思路就是将物品的数量分为 $1,2^1,2^2,2^3...sum-2^k$ ，如果大佬您会多重背包，那这道题的难度便会瞬间降低。

### 代码及其分析
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 3e6;
int n, m, k, A[20][20], a[N][3], nn, b, c, d, f[N], ans, ma;
int main(){
	memset(f, -1, sizeof(f));
	f[0] = 0;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i ++){
		int aa, bb;
		scanf("%d%d", &aa, &bb);
		A[aa][bb] ++;
		ma += bb;
	}
	for(int i = 0; i <= 10; i ++){
		for(int j = 1; j <= 10; j ++){
			c = A[i][j];	//c是数量，b是战斗力，d是质量 
			b = j;
			d = i;
			for(int k = 1; 1; k *= 2){
				if(c <= k){
					a[++ nn][1] = c * b;	//1是战斗力，2是质量 
					a[nn][2] = c * d;
					break;
				}
				else{
					a[++ nn][1] = k * b, a[nn][2] = k * d;
					c -= k;
				}
			}
		}
	}
	n = nn;
	for(int i = 1; i <= n; i ++){
		for(int j = m; j >= a[i][2]; j --){
			if(f[j - a[i][2]] != -1)
			f[j] = max(f[j], f[j - a[i][2]] + a[i][1]);
		}
	}
	for(int i = 1; i <= m; i ++){
		if(f[i] != -1)
		ans = max(ans, f[i]);
	}
	if(ans >= k)
	printf("yes\n");
	else
	printf("no\n");
	printf("%d", ans);
	return 0;
}
```
~~此代码仅供参考，因为它仅能供参考~~

忽视作者神奇的码风，此代码还是很好理解的。

---

## 作者：斯德哥尔摩 (赞：3)

楼下一篇 p语言 题解，c++党表示不服，于是发一篇。。。

n,m<=100,000，普通01背包一定只能过20%（数据很强势。。。）

于是，想优化。

注意到 a[i],b[i]<=10，那么我们可以将质量与战斗力相同的男家丁合并，于是成了 多重背包。。。

但是，多重背包还是过不了啊，又于是，我们想到了神奇的 二进制优化。。。

即将每个多重物品拆成 1,2,4,8,...,2^(k-1),2^k 个，做 01背包。

最后将拆完后剩余的物品再做一次 01背包（第一次我被坑的不轻。。。）

1128ms（开了o2）,应该还行吧（当前rank1。。。）

附上代码（不喜缩进勿喷）：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#define MAXN 100010
#define MAXM 135//男家丁的种类
using namespace std;
int n,m,k,d=1,ans=0,v[MAXM],w[MAXM],c[MAXM],dp[MAXN];
struct node{
	int v,w;
}a[MAXN];//方便排序。。。
inline int read(){//读优
	int date=0,w=1;char c=0;
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
	return date*w;
}
bool cmp(const node &x,const node &y){//快排必备！
	if(x.w==y.w)return x.v>y.v;
	return x.w<y.w;
}
int main(){
	int s,t;
	n=read();m=read();k=read();
	for(int i=1;i<=n;i++){a[i].w=read();a[i].v=read();}//读入
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		w[d]=a[i].w;v[d]=a[i].v;c[d]=1;
		while(i<=n&&a[i+1].w==a[i].w&&a[i+1].v==a[i].v){c[d]++;i++;}
		d++;
	}//合并
	s=1;t=d-1;
	while(w[s]==0){//若质量为0，直接加入答案中。。。
		ans+=c[s]*v[s];
		s++;
	}
	for(int i=s;i<=t;i++){//多重背包
		int num=c[i];
		for(int j=1;num-j>0;j*=2){// j 为拆出的物品个数，每次*2
			num-=j;//记得减去 j ！！！
			for(int l=m;l>=j*w[i];l--)//01背包板子。。。
			dp[l]=max(dp[l],dp[l-j*w[i]]+j*v[i]);
		}
		for(int l=m;l>=num*w[i];l--)//重要的事情只说一遍：不要忘记！！！
		dp[l]=max(dp[l],dp[l-num*w[i]]+num*v[i]);
	}
	ans+=dp[m];//累计答案
	if(ans>=k)printf("yes\n");
	else printf("no\n");
	printf("%d\n",ans);//输出
	return 0;
}

```

---

## 作者：姬小路秋子 (赞：3)

终于轮到我第一个发题解了。。

然而还是太弱，这题花了半个小时才调出来。。。

下面给出我的思路:

这题n,m的数据范围是100000，用普通的01背包求肯定不现实（事实证明这题数据很给力，普通nm算法真的只能过2个点）。

正当我苦苦思索时，我突然发现，a,b数组的范围极小，只有0-10！！！

这说明什么？？？（显然了，所有男丁的状态只有11\*11=121中）

所以，我们可以把a[i],b[i]相同的男丁合并到一起，这样就成了一个有限背包问题

普通有限背包问题的时间复杂度为O（n\*m\*背包个数），但是用二进制优化就能把时间复杂度变成O（n\*m\*log（背包个数））。

请注意，n是100000，m是121（极限），log（背包个数）分摊下来也就10，时间勉强能卡过。

但是，这样做我还是超了2个点

所以我想到把a[i]为0的直接加到最终答案里，终于卡过去了。。。

当然，二进制背包利用单调队列优化也是可以的，由于本人懒，就不写了。。

下面给出代码（P）：

```cpp
uses math;
var t,k,n,m,t1,i,j,ans,sum,ii,jj:longint;
    f:Array[0..1000000]of longint;
    a,b:array[0..10,0..10]of longint;
    c:array[0..30,0..10,0..10]of longint;
begin
 read(n,m,t1);
 for i:=1 to n do
  begin
   read(t,k);
   if t=0 then sum:=sum+k;
   inc(a[t,k]);
  end;
 for i:=1 to 10 do
  for j:=1 to 10 do
   begin
    t:=1;
    while a[i,j]-t>=0 do
     begin
      inc(b[i,j]);
      c[i,j,b[i,j]]:=t;
      a[i,j]:=a[i,j]-t;
      t:=t*2;
     end;
    if a[i,j]>0 then
     begin
      inc(b[i,j]);
      c[i,j,b[i,j]]:=a[i,j];
     end;
   end;
 for ii:=1 to 10 do
  for jj:=1 to 10 do
   if b[ii,jj]>0 then
   begin
    for j:=1 to b[ii,jj]do
     for i:=m downto c[ii,jj,j]*ii do
      f[i]:=max(f[i],f[i-c[ii,jj,j]*ii]+c[ii,jj,j]*jj);
   end;
 for i:=0 to m do
  begin
   ans:=max(ans,f[i]);
  end;
 if ans+sum>=t1 then writeln('yes')
  else writeln('no');
 write(ans+sum);
end.
```

---

## 作者：培淇2021 (赞：2)

观察到 $a_i,b_i$ 的值域都比较少，就可以写个桶，再来个 01 背包。但是会超时，所以再写一个二进制拆分即可。

二进制拆分其实就是把多重背包的物品数拆成二的次幂，最后 01 背包。

AC code:

```cpp
//-------------------------------------------------

//缺省源
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define il inline
//#define outwo

#ifndef outwo
#define reg register
#endif

using namespace std;
int n,m,k,aaa,bbb,tong[15][15],v[100005],c[100005],cnt,f[100005];
template <typename leixingming>
il void read(leixingming &x)
{
    reg leixingming temppmet=0;
    reg char chchch=getchar()；
    while(!isdigit(chchch))
		chchch=getchar();
    while(isdigit(chchch))
   	{
	    temppmet=temppmet*10+(chchch^48);
	    chchch=getchar();
	}
	x=temppmet;
}
template <typename leixingming,typename ...Args>
il void read(leixingming &a,Args &...args)
{
       read(a);
       read(args...);
}
template <typename leixingming>
il void print(leixingming x)
{
   	if(x<0)
    {
    	putchar('-');
        x=-x;
    }
    if(x>9)
		print(x/10);
    putchar(x%10+'0');
}
//-------------------------------------------------
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>aaa>>bbb;
		tong[aaa][bbb]++;
	}
	for(int i=0;i<=10;i++)
	{
		for(int j=0;j<=10;j++)
		{
			if(tong[i][j]==0)
				continue;
        //二进制拆分
			int len=tong[i][j],val=tong[i][j],tem;
			for(tem=1;tem<=val;tem*=2)
			{
				v[++cnt]=tem*i;
				c[cnt]=tem*j;
				//cout<<tem<<" "<<i<<" "<<j<<endl;
				val-=tem;
			}
			if(0!=val)
			{
				v[++cnt]=val*i;
				c[cnt]=val*j;
			}
		}
	}
	
	/*cout<<endl;
	
	for(int i=1;i<=cnt;i++)
		cout<<v[i]<<" "<<c[i]<<endl;
	cout<<endl;*/
	for(int i=1;i<=cnt;i++)
	{
		for(int j=m;j>=v[i];j--)
		{
			f[j]=max(f[j],f[j-v[i]]+c[i]);
		}
	}
	if(f[m]>=k) 
		cout<<"yes";
	else
		cout<<"no";
	cout<<endl<<f[m];
	return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：1)

本题解做法和其余题解相似，主要补充了复杂度的证明。

首先上来看到 $0\leq a_i,b_i\leq 10$，显然最多只有 $11\times 11=121$ 种可能。

而在 $n$ 的最大值 $10^5$ 当中一定会有重复。

于是想到记录 $a_i,b_i$ 出现的个数，并跑多重背包。

则时间复杂度是 $O(nm)$（注意这个复杂度看起来一样，但其实比暴力 $01$ 背包要小的多），依然超时。

然后就想到了一个很经典的优化：二进制优化。

将其拆分为 $1,2,4,\cdots$ 的物品，可以通过跑 $01$ 背包的组合来实现组合出多重背包物品个数。

加了优化后，时间复杂度为 $O(m\log(n))$，不超时。

给出证明：

对于 $\log(n)$，实际上为一个近似。

设 $f(x)$ 表示 $x$ 的出现次数，则实际上 $\log(n)$ 的真实值为：

$$
\sum_{i=0}^{1111} \log(f(a_i\times 100+b_i))
$$

我们上面说过最大有 $121$ 种可能，又因为 $\log(a)\leq \log(a-b)+\log(b)$，可推导出上式最大值为 $121\times \log(\dfrac{n}{121})$。

又因为 $n\leq 10^5$，即最大执行次数的 $m\log(n)$ 的近似实际上最大值为 $10^5\times 121\times \lceil\log(\dfrac{10^5}{121})\rceil=1.21\times 10^8$。

大致上是能过的，因为数据卡的不会这么死。

不过最慢的点依然跑了 $89$ 毫秒，可能是数据水了。

贴代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005];
int b[100005];
int cnt[15][15];
int w[100005];
int c[100005];
int dp[100005];
int p;
signed main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		cnt[a[i]][b[i]]++;
	}
	for(int i=0;i<=10;i++){
		for(int j=0;j<=10;j++){
			int s=1;
			while(cnt[i][j]>=s){
				w[++p]=s*i;
				c[p]=s*j;
				cnt[i][j]-=s;
				s*=2;
			}
			if(cnt[i][j]!=0){
				w[++p]=cnt[i][j]*i;
				c[p]=cnt[i][j]*j;
			}
		}
	}
	for(int i=1;i<=p;i++){
		for(int j=m;j>=w[i];j--){
			dp[j]=max(dp[j],dp[j-w[i]]+c[i]);
		}
	}
	cout<<(dp[m]>=k?"yes":"no");
	cout<<endl<<dp[m];
	return 0;
}
```

---

## 作者：QCurium (赞：1)

[原题链接](https://www.luogu.com.cn/problem/P2306)

[视频讲解（顺便点个赞吧](https://www.bilibili.com/video/BV1wN411n7Vd/?vd_source=a8f2ca9bd086cb49d933fb93cb7409c0)

## 前置知识

[多重背包](https://www.luogu.com.cn/blog/qcm-home/bei-bao-dp)，蒟蒻自己写的，如果有写错的地方，求指出。

## 题意

给你 $n$ 个物品，体积是 $a_i$，价值是 $b_i$，你的背包容量为 $m$，求你背包能装下的物品的最大价值有没有 $k$ 大，是多少。

## 题目分析

一看题，这不就是简单的 01 背包吗？一看数据范围，那没事了。

我们来看数据范围，$n,m \le 10^5$，$0\le a_i,b_i \le 10$，$n$ 那么大，但 $a$ 和 $b$ 最大是 $10$，这肯定有大量的数据是重复的，我们可以将他们统计在一起，就变成了多重背包，这样，这道题就好做了。

因为多重背包在优化完后，就变成了 01 背包，所以我直接写一维数组的了。

多重背包详细讲解在[这里](https://www.luogu.com.cn/blog/qcm-home/bei-bao-dp)。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,k,tj[15][15],a[N],b[N],cnt=0,f[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		int aa,bb;
		cin>>aa>>bb;
		tj[aa][bb]++;
	}
	for(int i=0;i<=10;i++){
		for(int j=0;j<=10;j++){
			if(!tj[i][j])
				continue;
			int asd=1;
			while(tj[i][j]>=asd){
				cnt++;
				a[cnt]=asd*i;
				b[cnt]=asd*j;
				tj[i][j]-=asd;
				asd*=2;
			}
			if(tj[i][j]){
				cnt++;
				a[cnt]=tj[i][j]*i;
				b[cnt]=tj[i][j]*j;
				tj[i][j]=0;
			}
		}
	}
	for(int i=1;i<=cnt;i++){
        for(int j=m;j>=a[i];j--)
            f[j]=max(f[j],f[j-a[i]]+b[i]);
    }
    int ans=-1;
    for(int i=1;i<=m;i++)
    	ans=max(ans,f[i]);
    if(ans>=k)
    	cout<<"yes"<<'\n';
    else
    	cout<<"no"<<'\n';
    cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/126158432)

---

## 作者：Ryo_Yamada (赞：1)

刚看到的时候感觉是 01 背包裸题，然后一看数据范围发现不对……

因为 $n,\,m \leq 10^5$，裸的 01 背包 $O(nm)$ 显然无法通过，于是思考其它办法。可以观察到数据范围 $a_i,\,b_i \leq 10$ 很小，也就是说每个物品只有 $121$ 种可能。考虑记录每种物品出现的次数，题目就变成了多重背包，然而复杂度依然无法通过。

考虑多重背包的二进制优化，也就是将每个物品的出现次数 $K$ 以 $2^0 + 2^1 + \ldots + 2^x + y$ 的形式展现出来（$y$ 可能为 $0$）。一个数一定可以用 $2$ 的幂次方的和表示出来（即它的二进制方式），例如 $11$ 转化为二进制是 $1011$，所以可以表示为 $8+2+1$。所以这样拆分便可以将 $\leq K$ 的所有数表示出来，直接跑 01 背包即可，时间复杂度 $O(m \log \sum a_i)$。

Code：

```cpp
def(N, int, 1e5 + 5)

int n, m, k, cnt;
int a[N], b[N];
int cn[11][11];
int v[N], w[N];
int dp[N * 10];

int main() {
	qread(n, m, k);
	rep(i, 1, n) qread(a[i], b[i]), ++cn[a[i]][b[i]];
	rep(i, 1, 10) rep(j, 1, 10) {
		for(int K = 1; cn[i][j] >= K; K <<= 1) {
			v[++cnt] = i * K;
			w[cnt] = j * K;
			cn[i][j] -= K;
		}
		if(cn[i][j]) {
			v[++cnt] = i * cn[i][j];
			w[cnt] = j * cn[i][j];
		}
	}
	rep(i, 1, cnt) per(j, m, v[i]) To_max(dp[j], dp[j - v[i]] + w[i]);
	int ans = 0;
	rep(i, 1, 10) ans += i * cn[0][i];
	ans += dp[m];
	ans >= k ? puts("yes") : puts("no");
	printf("%d\n", ans);
 	return 0;
}
```


---

## 作者：lqsy002 (赞：0)

## 题目大意

[题目链接](https://www.luogu.com.cn/problem/P2306)。

## 解题思路

看第一眼是 $01$ 背包，但是根据数据范围肯定超时。

所以将质量与战斗力相同的男家丁合并，于是成了多重背包，记得二进制优化。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010,maxm=150;
int n,m,k,d,s=1,ans,v[maxm],w[maxm],c[maxm],dp[maxn];
struct node{
	int v;
	int w;
	bool operator<(const node &x)const{
		if(w==x.w)
			return v>x.v;
		return w<x.w;
	}
}a[maxn];
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=n;++i)
		cin>>a[i].w>>a[i].v;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i){
		w[++d]=a[i].w;
		v[d]=a[i].v;
		c[d]=1;
		while(i<=n&&a[i+1].w==a[i].w&&a[i+1].v==a[i].v){
			++c[d];
			++i;
		}
	}
	while(w[s]==0){
		ans+=c[s]*v[s];
		++s;
	}
	for(int i=s;i<=d;++i){
		for(int j=1;j<c[i];j*=2){
			c[i]-=j;
			for(int k=m;k>=j*w[i];--k)
				dp[k]=max(dp[k],dp[k-j*w[i]]+j*v[i]);
		}
		for(int j=m;j>=c[i]*w[i];--j)
			dp[j]=max(dp[j],dp[j-c[i]*w[i]]+c[i]*v[i]);
	}
	ans+=dp[m];
	if(ans>=k)
		cout<<"yes\n";
	else 
		cout<<"no\n";
	cout<<ans;
	return 0;
}
```

---

## 作者：keepwatcher_kensap (赞：0)

## Part 1 题意

有 $n$ 个物品，每个物品的重量和价值分别是 $a_i,b_i$。求在总重量不超过 $m$ 的时候，是否可以拥有不小于 $k$ 的总价值。

## Part 2 思路

很明显，我们可以使用 **01 背包**的方式来求答案。定义 $f_{i,j}$ 为只考虑前 $i$ 个物品，总重量不超过 $j$ 的情况下的最大价值。状态转移方程为：

$f_{i,j}=\max(f_{i,j},f_{i-1,j-a_i}+b_i)$。

## Part 3 优化

01 背包的时间复杂度为 $O(nm)$，题目中 $n,m \leq 10^5$，必然超时。我们发现 $0 \leq a_i,b_i \leq 10$。因此物品最多只有 $11^2$ 种类型。而至多又会有 $10^5$ 个物品，说明**会有多个同种的物品重复**，因此，我们可以用**二进制优化**的方式进行优化，详见代码。

## Part 4 代码

```
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,k,a[maxn],b[maxn],c[15][15];
int now,v[maxn],w[maxn],f[maxn];
inline void build(int x,int y)
{
	int sum=1;
	while (c[x][y]>=sum)
	{
		c[x][y]-=sum;
		now++,v[now]=sum*x,w[now]=sum*y;
		sum*=2;
	}
	if (c[x][y]!=0)
	{
		now++,v[now]=c[x][y]*x,w[now]=c[x][y]*y;
	}
	return ;
}
int main()
{
	cin>>n>>m>>k;
	for (int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];c[a[i]][b[i]]++;
	}
	for (int i=0;i<=10;i++)
	{
		for (int j=0;j<=10;j++)
		{
			if (c[i][j]!=0) build(i,j);
		}
	}
	for (int i=1;i<=now;i++)
	{
		for (int j=m;j>=v[i];j--)
		{
			f[j]=max(f[j],f[j-v[i]]+w[i]);
		}
	}
	int result=0;
	for (int i=0;i<=m;i++)
	{
		result=max(result,f[i]);
	}
	if (result>=k) cout<<"yes"<<endl;
	else cout<<"no"<<endl;
	cout<<result;
	return 0;
}
```

---

## 作者：sxq9 (赞：0)

由于 $n,m\leq10^5$ 的范围，我们不能用普通做法。然而 $0\leq a_i,b_i\leq 10$ 的范围下，就会有重复的人了，考虑多重背包。

我们可以使用二进制优化。

AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010],c[100010],d[100010],dp[100010];
int s[110][110];
int main(){
	int n,m,nl;
	cin>>n>>m>>nl;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		s[a[i]][b[i]]++;
	}
	int cnt=0;
   //二进制拆分 
	for(int i=0;i<=10;i++){
		for(int j=0;j<=10;j++){
			for(int k=1;s[i][j]!=0;k*=2){
				if(k>=s[i][j]){
					c[++cnt]=s[i][j]*i;
					d[cnt]=s[i][j]*j;
					break;
				}
				c[++cnt]=k*i;d[cnt]=k*j;
				s[i][j]-=k;
			}
		}
	}
   //01背包模板 
	for(int i=1;i<=cnt;i++){
		for(int j=m;j>=c[i];j--){
			dp[j]=max(dp[j],dp[j-c[i]]+d[i]);
		}
	}
	if(dp[m]>=nl)cout<<"yes\n"<<dp[m];
	else cout<<"no\n"<<dp[m];
	return 0;
}
```

---

## 作者：caibet (赞：0)

### 题意：

给你 $n$ 个物品，质量和价值分别为 $a_i,b_i$，求大小为 $m$ 的背包能承载的物品最大总价值能否超过 $k$，并输出总价值。

$1\le n,m\le 10^5,0\le a_i,b_i\le10$。

### 解法：

- **第一部分：直觉**

  一眼看过去，这是一个比较普通的背包问题。
  
  我们可以按照一般的思路，开一个动态规划数组，通过 $\mathcal O(nm)$ 时间复杂度求出每个背包质量对应的最大价值。
  
  最后便可求出求大小为 $m$ 的背包能承载的物品最大总价值。这里不再过多赘述。
  
  于是，高高兴兴提交去，惶惶恐恐 TLE 来。
  
  ![](https://s4.ax1x.com/2021/12/25/TUNEJH.gif)
  
- **第二部分：三思**

  TLE 之后的我完全不知道为什么，直到我翻到数据范围：$1\le n,m\le 10^5$。显然，$\mathcal O(nm)$ 算法会被卡出加了 `Sleep` 之感。
  
  不过，我们发现 $a_i$ 和 $b_i$ 都很小，这可能成为我们的突破点。
  
  考虑开一个桶，`b[x][y]` 记录质量为 $x$，价值 $y$ 的数量。这样我们要做的由 01 背包变为多重背包。
  
  哎，多重背包可以二进制优化（即将 $x$ 个物品拆成 $\log x+1$ 个，使这些物品能够拼凑成 $1\sim m$ 个原物品的质量和价值，详见代码）。于是物品数量由 $n$ 变为 $\log n$ 多一点。
  
  由此，时间复杂度变为 $\mathcal O(m\log n)$，可以通过本题。
  
  ```cpp
  namespace{
	  const int lim=1e5+2;
	  int n,m,k,cnt[11][11],ans,f[lim];
	  struct node{
		  int a,b;
	  };
	  vector<node> b;
	  void work(){
		  n=read();m=read();k=read();
		  F(i,1,<=n){
			  Int x=read(),y=read();
			  ++cnt[x][y];//记录质量为 x，价值为 y 的物品个数
		  }
		  F(i,0,<=10){//如果质量为 0，血赚
			  F(j,1,<=10){//如果价值为 0，加进背包也没用，直接不枚举
				  if(!cnt[i][j]) continue;
				  Int s=1;
				  while(s<cnt[i][j]){
					  b.push_back({s*i,s*j});//加入一个物品
					  cnt[i][j]-=s;//减少物品数量
					  s<<=1;//拆成 2 的整数次幂
				  }
				  b.push_back({i*cnt[i][j],j*cnt[i][j]});//最后剩下的独立成为一个物品
			  }
		  }
		  F(i,0,<b.size()){//经典 01 背包
			  R(j,m,>=b[i].a){
				  f[j]=max(f[j],f[j-b[i].a]+b[i].b);
			  }
		  }
		  puts(f[m]>=k?"yes":"no");
		  put("%d",f[m]);
	  }
  }
```

---

## 作者：破忆 (赞：0)

## 再次看一遍题面

### 题目描述
mzc家很有钱（开玩笑），他家有ｎ个男家丁（做过前两弹的都知道）。但这些都不足以挽救他被yyh虐的命运。于是他向你们发起了求救。

mzc要派出男家丁与yyh大战，但他只能承载质量为Ｍ的男家丁，现在他想知道她们（你没有看错）的战斗力之和是否打得过yyh。

### 输入输出格式
第一行有三个数n,m,k，n表示有n个男家丁，m表示能承载m表的质量，k表示yyh表的战斗力。

之后n行，每行两个数ai,bi，分别表示第i个男家丁的质量和战斗力。

### 输出格式：
两行，若打得过（大于等于）：输出“yes”；

若打不过：输出“no”。

第二行输出最高战斗力.

#### 没错这道题的核心就是01背包

### 解法一:
直接用普通背包,预计复杂度 O(n*m)

但是请看数据  n,m<=100000
大概10^10。明显超时

### 解法二：
还是背包，但注意到ai,bi<=10
，就会发现有很多一模一样的家丁。可以想到对所有种类的家丁进行哈希。然后枚举家丁种类和每种的个数

这样随机化的数据是能应付了，但遇到极端数据（例如所有的一样），还是有超时的风险

### 解法三：
假设某种家丁个数为S，如何把他拆成一些数，是这些数能拼凑出1~S的所有数？

自然而然地就想到了二进制拆分，拆成1,2,4,8...，再加上一点零头。

这样极端数据下的复杂度，仅为O（n logm）

具体详见代码
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=12,maxm=100005;
int n,m,k,a[25],b[25];
int hsh[maxn][maxn],f[maxm];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
	freopen("P2306.in","r",stdin);
	freopen("P2306.out","w",stdout);
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++) hsh[read][read]++;  //哈希 
	for(int i=0;i<=10;i++)
	for(int j=0;j<=10;j++){   //枚举每种家丁 
		if(!hsh[i][j]) continue;
		int cnt=0,s=1;
		while(hsh[i][j]>=s) a[++cnt]=i*s,b[cnt]=j*s,hsh[i][j]-=s,s<<=1; 
		//s为2的非负整数次幂，hsh[i][j]每次减掉s,并且s每次扩大2倍 
		if(hsh[i][j]) a[++cnt]=i*hsh[i][j],b[cnt]=j*hsh[i][j];  //剩余的零头 
//		for(int k=1;k<=cnt;k++) printf("%d ",a[k],b[k]);
//		putchar(10);
		for(int k=1;k<=cnt;k++)
		for(int t=m;t>=a[k];t--) f[t]=max(f[t],f[t-a[k]]+b[k]); //正常背包 
	}
	for(int i=1;i<=m;i++) f[i]=max(f[i],f[i-1]);
	printf("%s\n%d\n",f[m]>=k?"yes":"no",f[m]);
	return 0;
}
```


---

