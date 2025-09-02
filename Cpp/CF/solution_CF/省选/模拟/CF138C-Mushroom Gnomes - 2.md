# Mushroom Gnomes - 2

## 题目描述

One day Natalia was walking in the woods when she met a little mushroom gnome. The gnome told her the following story:

Everybody knows that the mushroom gnomes' power lies in the magic mushrooms that grow in the native woods of the gnomes. There are $ n $ trees and $ m $ magic mushrooms in the woods: the $ i $ -th tree grows at a point on a straight line with coordinates $ a_{i} $ and has the height of $ h_{i} $ , the $ j $ -th mushroom grows at the point with coordinates $ b_{j} $ and has magical powers $ z_{j} $ .

But one day wild mushroommunchers, the sworn enemies of mushroom gnomes unleashed a terrible storm on their home forest. As a result, some of the trees began to fall and crush the magic mushrooms. The supreme oracle of mushroom gnomes calculated in advance the probability for each tree that it will fall to the left, to the right or will stand on. If the tree with the coordinate $ x $ and height $ h $ falls to the left, then all the mushrooms that belong to the right-open interval $ [x-h,x) $ , are destroyed. If a tree falls to the right, then the mushrooms that belong to the left-open interval $ (x,x+h] $ are destroyed. Only those mushrooms that are not hit by a single tree survive.

Knowing that all the trees fall independently of each other (i.e., all the events are mutually independent, and besides, the trees do not interfere with other trees falling in an arbitrary direction), the supreme oracle was also able to quickly calculate what would be the expectation of the total power of the mushrooms which survived after the storm. His calculations ultimately saved the mushroom gnomes from imminent death.

Natalia, as a good Olympiad programmer, got interested in this story, and she decided to come up with a way to quickly calculate the expectation of the sum of the surviving mushrooms' power.

## 说明/提示

It is believed that the mushroom with the coordinate $ x $ belongs to the right-open interval $ [l,r) $ if and only if $ l<=x&lt;r $ . Similarly, the mushroom with the coordinate $ x $ belongs to the left-open interval $ (l,r] $ if and only if $ l&lt;x<=r $ .

In the first test the mushroom survives with the probability of 50%, depending on where the single tree falls.

In the second test the mushroom survives only if neither of the two trees falls on it. It occurs with the probability of 50% $ × $ 50% = 25%.

Pretest №12 is the large test with $ 10^{5} $ trees and one mushroom.

## 样例 #1

### 输入

```
1 1
2 2 50 50
1 1
```

### 输出

```
0.5000000000
```

## 样例 #2

### 输入

```
2 1
2 2 50 50
4 2 50 50
3 1
```

### 输出

```
0.2500000000
```

# 题解

## 作者：破忆 (赞：5)

### 题目大意
有一排树，每棵树有可能往左倒，有可能往右倒，倒下后会覆盖一些区间，给定一些蘑菇，已知每个蘑菇的价值和位置，求对价值总和的期望


------------

### 分析
转化的一下题目

每棵树的倾倒范围都可以看成2个区间，每个区间内价值的期望都要乘上这棵树倾倒在这个区间的概率，自然而然就想到了**线段树**的区间修改。

同样的，每个蘑菇蘑菇可以看成是一个点，这个点不被砸的概率乘上蘑菇的价值就是这个蘑菇的价值期望，依然可以利用**线段树**的单点查询完成。

但是数据范围达到了10^9，直接套模板不行。继续思考，每棵树形成的2个区间仅仅包括4个顶点，每个蘑菇占1个点。

显然，除了这4*n+m个点，其它点对过程和答案都没有影响，那么，只需对数据进行**离散**就行了。


------------
### 解法
离散+线段树区间修改单点查询


------------
### 代码
```cpp
#include<bits/stdc++.h>
#define DB double
using namespace std;
const int maxn=1e5+5,maxm=1e4+5,maxe=maxn*4+maxm,maxp=4*maxe;
int n,m,b[maxe],id[maxe],tot,cnt,d;
//b数组存所有数据，id记录第i大的数是多少
DB p[maxp],ans;//p是懒标记
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
struct tree{
	int x,h,l,r;
}a[maxn];
//a数组存树
struct mogu{
	int x,v;
}c[maxn];
//c数组存蘑菇
int find(int x){//二分查找x离散之后的结果
	int L=1,R=cnt,mid;
	while(L<=R){
		mid=L+R>>1;
		if(id[mid]==x) return mid;
		id[mid]<x?L=mid+1:R=mid-1; 
	}
}
void build(int l,int r,int k){//建树，初始保留概率为1
	p[k]=1,d++;
	if(l==r) return;
	int mid=l+r>>1;
	build(l,mid,k<<1),build(mid+1,r,k<<1|1); 
}
void change(int L,int R,int k,int l,int r,DB x){//线段树基本操作，区间修改
	if(L>r||R<l) return;//分离直接跳过
	if(l<=L&&R<=r){ p[k]*=x/100.0;return;}//包含关系，直接让懒标记乘上概率
	if(L==R) return;
	int mid=L+R>>1;
	change(L,mid,k<<1,l,r,x),change(mid+1,R,k<<1|1,l,r,x);//继续递归
}
DB ask(int l,int r,int k,int x){//线段树基本操作，单点查询
	if(l==r) return p[k];//找到即停止
	int mid=l+r>>1;
	if(mid>=x) return ask(l,mid,k<<1,x)*p[k];
	else return ask(mid+1,r,k<<1|1,x)*p[k];
    //递归结果乘当前懒标记
}
int main(){
// 	freopen("CF138C.in","r",stdin);
// 	freopen("CF138C.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].h=read(),a[i].l=read(),a[i].r=read();
		b[++tot]=a[i].x-a[i].h,b[++tot]=a[i].x-1,b[++tot]=a[i].x+1,b[++tot]=a[i].x+a[i].h;
        //一棵树形成的顶点分别是xi-hi，xi-1，xi+1，xi+hi
        //先存进b数组
	}
	for(int i=1;i<=m;i++){
		c[i].x=read(),c[i].v=read();
		b[++tot]=c[i].x;
        //把蘑菇也存进去
	}
	sort(b+1,b+1+tot);//由小到大排序
	for(int i=1;i<=tot;i++) if(b[i]!=b[i+1]) id[++cnt]=b[i];//id存第i大的数的数值
	build(1,cnt,1);//建一棵线段树
	for(int i=1;i<=n;i++){
		int L=find(a[i].x-a[i].h),midl=find(a[i].x-1),midr=find(a[i].x+1),R=find(a[i].x+a[i].h);
        //分别用二分查找出离散之后的数值
		change(1,cnt,1,L,midl,(DB)100.0-a[i].l),change(1,cnt,1,midr,R,(DB)100.0-a[i].r);
        //把这些区间都乘上不被砸的概率
	}
	for(int i=1;i<=m;i++){
		int x=find(c[i].x);
		ans+=(DB)ask(1,cnt,1,x)*c[i].v;//不被砸的概率乘价值即期望
	}
	printf("%.10lf\n",ans);
	return 0;
}
```


---

## 作者：xh39 (赞：3)

在[这里](https://www.luogu.com.cn/training/16003)更新。有不懂的可以在评论区提出,我将会私信回答。~~(在我没退役之前)~~

# 题目
(读了翻译发现没看懂,最后看了英语原文+请教教练才看懂,所以给大家解释一下题目大意(不逐字对应,只解释大意))
## 题目大意
一条直线上有n棵树和m个蘑菇。第i棵树所在位置为a[i]有l[i]的概率往左倒,r[i]的概率往右倒,也可以不倒,倒地可以摧毁h[i]长度的地面(往左倒可以摧毁$a[i]-h[i]<=x<a[i]$的地面,往右倒可摧毁$a[i]<x<=a[i]+h$的地面,**a[i]不会被摧毁**)。如果蘑菇所在的地面被摧毁那么蘑菇也没了。 $\color{red}\text{注意不等式的符号有没有取到等号。}$

第i个蘑菇的位置位于b[i],权值为z[i],求摧毁后剩下的蘑菇的期望权值和。

## 输入

第1行1个整数n,m,分别表示树和蘑菇的个数。

接下来n行,每行4个整数,a[i],h[i],l[i],r[i],分别表示位置,摧毁的长度,往左和右倒的概率**百分比**(50表示50%即0.5) $\color{red}\text{注意概率是百分比!}$

## 输出

一个小(分)数,代表期望权值和。要求误差(即答案与输出差的绝对值)<=0.0001。

## 样例解释即说明

### \#1

第1棵树有50%的概率往左倒(即覆盖0<=x<2的区间),蘑菇在位置1,权值为1。所以期望权值和为1×0.5=0.5。

### \#2

第1棵树有50%的概率往右倒,第2棵有50%的概率往左倒,所以概率为1×0.5×0.5=0.25。

### 说明

测试点#12是一个有$10^{5}$棵树,1个蘑菇的大测试点。

注:所有变量和数组均与原题规定得一样,数据范围自行看原题。

# 暴力

枚举每棵树,计算每个点不被摧毁的概率。

对于每棵树,我们分别处理往左倒和往右倒,这样就拆成了2个区间分别处理。

概率计算方法为在所有树倒下时,不被摧毁的概率积。暴力把每个点都×l[i]或r[i],最后将sum加上所有蘑菇所在的点的概率×权值。

如果对计算方法有疑问,可以看样例解释。

时间复杂度为$O(sum{h[i]×2}),-10^{9}<=h[i]<=10^{9},n<=10^{5}$,所以最坏复杂度约$2×10^{14}$。

# 优化1

由于我们是区间修改,修改完之后全部求,所以可以利用前缀和的思想。(当然这里是求积)

设一个s数组,对于左端点,标记×l[i],(右端点+1)标记为÷l[i],最后跑一边前缀和(即```s[i]*=s[i-1]```)然后就可以求出每个点的概率,最后在枚举蘑菇求答案。

时间复杂度为O(max{h[i]}-min{h[i]}),最坏情况有$2\times 10^{9}$。

# 优化2(正解)

观察优化1的过程,我们发现当h差别很大时,中间有一堆元素的值时一样的,所以对这些一样的元素进行操作,完全是浪费时间和空间。我们怎么样避免操作重复的元素呢?

什么元素才会有一段重复?

在两个端点之间,不会有任何的标记,这两个端点之间的值肯定是一样的。

怎么办?

那我们可以将左端点右端点都放入一个数组中,排一遍序,然后端点中间的就可以不管它了。

时间复杂度$O(4n\times log_{2}(4n)+2n+n+m)$ (加号4边分别为排序,标记,前缀和的时间)

但是此时空间复杂度还是没有优化,所以就算不tle,空间也会让你mle或ce(不能开那么大的数组)。

我们优化了时间,就有中间的一大段空间空在那里,我们可以省去中间的空间,可以理解为把数组下标重新编号,使其跳过中间空着的空间,只管端点。

此时我们把数组重新编号了,蘑菇就不好找了,所以我们要把蘑菇也放入数组排序。

有点类似于离散化,不同的是不用把数组里的元素重新改,仅把s数组重新编号。

# 算法示例

讲了这么多,感觉自己讲得不好,大家可能没听懂,那就拿一个数据来演示优化2。

```
2 1
200 200 50 50
400 200 50 50
300 100
```

为方便,用a~b表示a<=x<=b

有4个区间:0~100,300~400,200~300,500~600

将所以数放入一个数组排序。排序完的结果:0,100,100,200,300,300,400,500,600

然后放入s数组并跑前缀和:
|  |0|1|2|3|4|5|6|7|8|9|10|  |  |  |
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
|数组里的数|0|100|100|200|300|300|400|500|600|  |  |  |  ||
|标记|×0.5||÷0.5|×0.5|×0.5||÷0.5|÷0.5×0.5||÷0.5||  |  |  |

## 细节
讲解一些我wa过的点为什么WA。

\#3:必须用(1-输入÷100)才是不被摧毁的概率。

\#5:特判除数为0的情况。

\#6:排序数值一样时的顺序问题,在代码里讲解。

\#9:第一个是蘑菇时没有计算。

\#12:

精度问题。double只能存小数300多位。所以如果有数据让你前面一直÷,就会爆精度。提供一个数据让你爆精度。(太大了,用c++程序生成,在iakioi.in中打开)

```cpp
#include<iostream>
using namespace std;
int main(){
	freopen("iakioi.in","w",stdout);
	int i;
	cout<<"100000 1"<<endl;
	for(i=0;i<100000;i++){
		cout<<0<<" "<<i<<" "<<100<<" "<<0<<endl;
	}
	cout<<"0 1";
	return 0;
}
```
所以要溢出时×一个数,让它恢复成接近1。当然要记录溢出了几次。因为在向上÷的时候可能会向上溢出,所以这时把溢出的次数-1(相当于反溢出一次)。设这个数是c,eps=$10^{-250}$最后答案就是$ans \times eps^c$

\#12:

但是tle了,所以要卡常,就把cin改为scanf就AC了。

# 代码
```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
long long a[1000005],h[1000005];
double l[1000005],r[1000005];
long long b[1000005],w[1000005];
struct xyq{ //注:id好像没用,懒得删了。
	long long a,id,left; //left表示是哪一种1左端点3右端点2蘑菇。这么编号的原因是排序时数值一样按left的编号排序,先1再2后3,为什么要怎么做,建议自己打一下草稿模拟一下就知道了。我也解释不清。
	double ykb; //ykb表示概率(left=1,3)或权值(left=2)
}_[1000005];
struct rule{
	bool operator()(const xyq &s1,const xyq &s2){
		return s1.a<s2.a||(s1.a==s2.a&&s1.left<s2.left);
	}
};
double s[1000005];
#define eps 0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001 //大约有250位小数,double最多可以存300多位。
int main(){
	long long n,m,i,N,tot=0,kkksc03=0;
	double sum=0;
	cin>>n>>m;
	for(i=0;i<n;i++){
		scanf("%lld %lld %lf %lf",a+i,h+i,l+i,r+i);
		_[i<<2].a=a[i]-h[i];
		_[i<<2].id=(i<<1);
		_[i<<2].left=1; 
		_[i<<2].ykb=1.0-l[i]/100.0;
		_[i<<2|1].a=a[i]-1;
		_[i<<2|1].id=(i<<1);
		_[i<<2|1].left=3;
		_[i<<2|1].ykb=1.0-l[i]/100.0;
		_[i<<2|2].a=a[i]+1;
		_[i<<2|2].id=(i<<1|1);
		_[i<<2|2].left=1;
		_[i<<2|2].ykb=1.0-r[i]/100.0;
		_[i<<2|3].a=a[i]+h[i];
		_[i<<2|3].id=(i<<1|1);
		_[i<<2|3].left=3;
		_[i<<2|3].ykb=1.0-r[i]/100.0;
	}
	for(i=0;i<m;i++){
		scanf("%lld %lld",b+i,w+i);
		_[(n<<2)+i].a=b[i];
		_[(n<<2)+i].id=i;
		_[(n<<2)+i].left=2;
		_[(n<<2)+i].ykb=w[i];
	}
	N=(n<<2)+m; //更新数组大小。这样不要没用一次都要计算。
	sort(_,_+N,rule());
	for(i=0;i<N;i++){
		s[i]=1; //初始值是什么都不做。一定是1,因为×1才等于原来的数。
	}
	for(i=0;i<N;i++){
		if(_[i].ykb==0){
			_[i].ykb=0.00001; //误差在0.0001之内。这样避免除数为0。
		}
		if(_[i].left==1){
			s[i]*=_[i].ykb;
		}
		if(_[i].left==3){
			s[i+1]/=_[i].ykb;
		}
	}
	for(i=1;i<N;i++){
		s[i]*=s[i-1];
		if(s[i]<eps){
			s[i]*=(1.0/eps); //恢复成1左右。
			kkksc03++;
		}
		if(s[i]>(1.0/eps)){
			s[i]*=eps; //反恢复。
			kkksc03--;
		}
		if(_[i].left==2){
			sum+=_[i].ykb*s[i]*pow(eps,kkksc03);
		}
	}
	printf("%.10f",sum+_[0].ykb*s[0]*(_[0].left==2));  //计算第1个蘑菇,因为我数组下标喜欢从0开始,第1个没有循环到。
	return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

对于每一个位置，去计算未被覆盖到的概率，往左边对应区间乘上 $l_i$，右边乘 $r_i$，最后直接把期望加起来。

懒，不想打线段树。

也不用在线查询，想法是离散化后商分，最后前缀积。

然后炸精度了。

想到伟大的数学老师，他告诉我们对数可以化乘法为加法！

所以把商分变成差分，最后前缀和！也就是先取 $\ln$ 然后 $\exp$ 回去，这样 `double` 只是做加减法，精度掉的不厉害，可以接受。

唐，$\ln 0$ 不存在，还要多打一个差分来考虑概率为 $0$ 的区间。

# Code

```cpp
#include<bits/stdc++.h>
struct tree{
	int x,h;
	double p,q;
}a[100005];
struct mushroom{
	int x,v;
}b[10005];
std::vector<int>lsh;
double val[500005];
int tag[500005];
int n,m;
double ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d%d%lf%lf",&a[i].x,&a[i].h,&a[i].p,&a[i].q);
		a[i].p/=100;a[i].q/=100;
		lsh.push_back(a[i].x-a[i].h);
		lsh.push_back(a[i].x);
		lsh.push_back(a[i].x+1);
		lsh.push_back(a[i].x+a[i].h+1);
	}
	for(int i=1;i<=m;++i){
		scanf("%d%d",&b[i].x,&b[i].v);
		lsh.push_back(b[i].x);
	}
	std::stable_sort(lsh.begin(),lsh.end());
	lsh.erase(std::unique(lsh.begin(),lsh.end()),lsh.end());
	for(int i=1,l,r;i<=n;++i){
		l=std::lower_bound(lsh.begin(),lsh.end(),a[i].x-a[i].h)-lsh.begin()+1;
		r=std::lower_bound(lsh.begin(),lsh.end(),a[i].x)-lsh.begin()+1;
		if(a[i].p!=1)val[l]+=log(1-a[i].p),val[r]-=log(1-a[i].p);
		else ++tag[l],--tag[r];
		l=std::lower_bound(lsh.begin(),lsh.end(),a[i].x+1)-lsh.begin()+1;
		r=std::lower_bound(lsh.begin(),lsh.end(),a[i].x+a[i].h+1)-lsh.begin()+1;
		if(a[i].q!=1)val[l]+=log(1-a[i].q),val[r]-=log(1-a[i].q);
		else ++tag[l],--tag[r];
	}
	for(int i=1;i<=lsh.size();++i)
		tag[i]+=tag[i-1],val[i]+=val[i-1];
	for(int i=1;i<=m;++i){
		b[i].x=std::lower_bound(lsh.begin(),lsh.end(),b[i].x)-lsh.begin()+1;
		if(!tag[b[i].x])
			ans+=b[i].v*exp(val[b[i].x]);
	}
	printf("%.4lf",ans);
	return 0;
}
```

---

## 作者：Hoks (赞：0)

## 前言
比较简单的题，评紫可能有点高了？

翻译有误是真烦啊。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
期望，即为概率乘上权重，考虑直接用此定义式拆开。

每个蘑菇的期望已经有了，接着就要求出他不被树砸的概率。

再观察下题目发现被砸是覆盖的关系，那么不被砸的概率就应该为相乘。

具体的，若一棵树向左倒会砸到这个蘑菇，概率为 $l_i$，那么这个蘑菇不会被砸到的概率即为 $1-l_i$。

对于多棵树，把概率乘在一起即可。

接着考虑怎么维护这个东西。

因为只要是在被砸的区间中的蘑菇的价值都要乘上这个概率，所以就相当于是区间乘。

而蘑菇的概率值即为单点查。

实现上考虑使用标记永久化方便实现。

但是接着就发现了值域非常大。

考虑离散化，这样值域就来到了和 $n$ 同阶，按上述方法做即可。
## 代码
```cpp
#include <bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define get(x) (lower_bound(b+1,b+1+tot,x)-b)
#define int long long
using namespace std;
const int N=1.2e5+10,mod=1e9+7,V=1e9,INF=0x3f3f3f3f3f3f3f3f;
int n,m,tot,b[N<<2],a[N],h[N],l[N],r[N],x[N],w[N];double t[N<<4],ans;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='<'||c=='>'||c=='#'||c=='^'||c=='v'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void modify(int p,int l,int r,int s,int e,int x)
{
    if(l>=s&&r<=e) return t[p]*=x*1.0/100,void();
    if(mid>=s) modify(ls,l,mid,s,e,x);if(mid<e) modify(rs,mid+1,r,s,e,x);
}
inline double query(int p,int l,int r,int x){if(l==r) return t[p];return ((mid>=x)?query(ls,l,mid,x):query(rs,mid+1,r,x))*t[p];}
signed main()
{
    n=read(),m=read();for(int i=1;i<=n;i++) a[i]=read(),h[i]=read(),l[i]=read(),r[i]=read();
    for(int i=1;i<=n;i++) b[++tot]=a[i]-h[i],b[++tot]=a[i]-1,b[++tot]=a[i]+1,b[++tot]=a[i]+h[i];
    for(int i=1;i<=m;i++) x[i]=read(),w[i]=read(),b[++tot]=x[i];
    sort(b+1,b+1+tot);tot=unique(b+1,b+1+tot)-b-1;for(int i=1;i<=(tot<<2);i++) t[i]=1;
    for(int i=1;i<=n;i++) modify(1,1,tot,get(a[i]-h[i]),get(a[i]-1),100-l[i]),modify(1,1,tot,get(a[i]+1),get(a[i]+h[i]),100-r[i]);
    for(int i=1;i<=m;i++) ans+=query(1,1,tot,get(x[i]))*w[i];printf("%.9lf",ans);
    genshin:;flush();return 0;
}
```

---

## 作者：黑影洞人 (赞：0)

题目中的蘑菇，第一个是位置，第二个是权值，翻译中并没有提到。

离散化？不存在的！！！

提供一种不用离散化的懒人写法。

动态开点线段树做这道题简直不要太 nice。

题目让我们求蘑菇的期望，我们只需要用一个动态开点线段树维护每个点被覆盖的概率，正常的做法是离散化之后进行线段树操作，我们直接上动态开点线段树，这样子就不用离散化了。

```cpp
struct Segment_tree{
	int lson[N],rson[N],cnt;
	double val[N],tag[N];
	#define lc lson[p]
	#define rc rson[p]
	#define mid (sl+sr)/2
	void csh(){for(int i=0;i<N;i++)val[i]=1.0,tag[i]=1.0;}
	void mul(int p,double v){tag[p]*=v;val[p]*=v;}
	void pushdown(int p){
		if(tag[p]!=1){
			if(!lc)lc=++cnt;
			mul(lc,tag[p]);
			if(!rc)rc=++cnt;
			mul(rc,tag[p]);
		}
		tag[p]=1;
	}
	void add(int &p,int sl,int sr,int l,int r,double v){
		if(!p)p=++cnt;
		if(sl>=l&&sr<=r){mul(p,v);return;}
		pushdown(p);
		if(mid>=l)add(lc,sl,mid,l,r,v);
		if(mid<r)add(rc,mid+1,sr,l,r,v);
	}
	double query(int p,int sl,int sr,int x){
		if(sl==sr)return val[p];
		pushdown(p);
		if(mid>=x)return query(lc,sl,mid,x);
		else return query(rc,mid+1,sr,x);
	}
}t;
```
有一些地方要注意，`pushdown` 里面的左右儿子可能没有赋值，于是如果是空节点要赋值。

当然，不建议在考场这么写，因为动态开点线段树的空间复杂度是 $O(n \log n)$ 的十分容易 MLE。

上完整代码：
```cpp
#include<cstdio>
#include<algorithm>
#define N 7919810
#define int long long
#define len 8000000000
using namespace std;
int n,m,rt;
double ans;
struct Segment_tree{
	int lson[N],rson[N],cnt;
	double val[N],tag[N];
	#define lc lson[p]
	#define rc rson[p]
	#define mid (sl+sr)/2
	void csh(){for(int i=0;i<N;i++)val[i]=1.0,tag[i]=1.0;}
	void mul(int p,double v){tag[p]*=v;val[p]*=v;}
	void pushdown(int p){
		if(tag[p]!=1){
			if(!lc)lc=++cnt;
			mul(lc,tag[p]);
			if(!rc)rc=++cnt;
			mul(rc,tag[p]);
		}
		tag[p]=1;
	}
	void add(int &p,int sl,int sr,int l,int r,double v){
		if(!p)p=++cnt;
		if(sl>=l&&sr<=r){mul(p,v);return;}
		pushdown(p);
		if(mid>=l)add(lc,sl,mid,l,r,v);
		if(mid<r)add(rc,mid+1,sr,l,r,v);
	}
	double query(int p,int sl,int sr,int x){
		if(sl==sr)return val[p];
		pushdown(p);
		if(mid>=x)return query(lc,sl,mid,x);
		else return query(rc,mid+1,sr,x);
	}
}t;
signed main(){
	t.csh();
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++){
		int o,h,pl,pr;
		scanf("%lld%lld%lld%lld",&o,&h,&pl,&pr);
		o+=1e9;
		t.add(rt,1,len,o-h,o-1,1.00-pl*0.01);
		t.add(rt,1,len,o+1,o+h,1.00-pr*0.01);
	}
	for(int i=1;i<=m;i++){
		int b,z;
		scanf("%lld%lld",&b,&z);
		b+=1e9;
		ans+=1.0*z*t.query(rt,1,len,b);
	}
	printf("%lf",ans);
	return 0;
}
```

---

## 作者：丛雨 (赞：0)

## CF138C Mushroom Gnomes - 2

先吐槽两句，翻译有误，不应该是闭区间，而是半开区间

其实本题可以不用线段树，这里给一个只用优先队列(堆)的做法

由于是计算期望，所以我们可以对每个蘑菇分别算期望再求和

我们对于每个蘑菇分别考虑求出左右边的树均不砸中它的概率

先考虑左边的树

这时就先将蘑菇和树按x轴排序，每次将一个蘑菇前的树不倒向右(立着或向左)的概率乘起来，再用优先队列按树向右倒的右端点排序，每次将不可能砸中蘑菇的树除去，类似于$\tt two-point$.右边的情况一样

如果直接乘和除铁定出问题，哪怕考虑了0的情况，如果一直$*1\%*1\%...$ 再$\div1\%\div1\%...$,这样精度就爆了(WA在test21)，所以我们考虑直接将每个要乘的数存下，在数组内加加减减即可，要求值得时候再现算即可

由于概率为百分数，所以不会超过101种情况

时间复杂度$O(100m\log n+n\log n)$，空间复杂度$O(n+m)$，765ms,最慢的一组93ms目前全洛谷rk1(我也不知道为什么跑这么快，是因为优先队列常数小？)

```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
double a[100005];
int s,m;
pair<int,int>w[100005];
priority_queue<pair<int,int> >q;
struct A{int x,h;double l,r;bool operator <(const A &b)const{return x<b.x;};}x[100005];
int T;
map<double,int>ma;
void mul(double v){++ma[v];}
void div(double v){--ma[v];}
double qkpow(double n,int m){
	double w=1;
	for(;m;m>>=1,n*=n)
		if(m&1)w*=n;
	return w;
}
int main(){
	s=read;m=read;
	for(int i=1;i<=s;++i)x[i].x=read,x[i].h=read,x[i].l=read/100.0,x[i].r=read/100.0;
	for(int i=1;i<=m;++i)a[i]=1,w[i].first=read,w[i].second=read;
	sort(x+1,x+s+1);sort(w+1,w+m+1);
	double t=1;
	for(int i=1,j=1;i<=m;++i){
		while(j<=s&&x[j].x<w[i].first)mul(1-x[j].r),q.push(make_pair(-x[j].x-x[j].h,j)),++j;
		while(q.size()&&-q.top().first<w[i].first)div(1-x[q.top().second].r),q.pop();
		if(ma[0])a[i]=0;
		else for(auto v:ma)a[i]*=qkpow(v.first,v.second);
	}while(q.size())q.pop();ma.clear();
	for(int i=m,j=s;i;--i){
		while(j&&x[j].x>w[i].first)mul(1-x[j].l),q.push(make_pair(x[j].x-x[j].h,j)),--j;
		while(q.size()&&q.top().first>w[i].first)div(1-x[q.top().second].l),q.pop();
		if(a[i]==0||ma[0])a[i]=0;
		else for(auto v:ma)a[i]*=qkpow(v.first,v.second);
	}double ans=0;
	for(int i=1;i<=m;++i)ans+=a[i]*w[i].second;
	printf("%.5f",ans);
	return 0;
}

```

---

## 作者：Kreado (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF138C)。

## 题目大意

给定 $n$ 个树，第 $i$ 个树在位置 $a_i$，高度为 $h_i$，它有 $l_i\%$ 的概率向左倾倒，有 $r_i\%$ 的概率向右倾倒，现在有 $m$ 个蘑菇，第 $i$ 个蘑菇在位置 $b_i$，它的美观度为 $z_i$，如果一个蘑菇被一个或多个倾倒的树覆盖，那么，它的美观度就会变化为 $0$，求最终蘑菇美观度的期望值。

## 思路

考虑求出每个位置不被树树覆盖的概率，然后将每个位置的概率乘上该位置的贡献即可。

向左倾倒其实就是区间 $[a_i-h_i,a_i)$ 乘上 $\dfrac{100-l_i}{100}$，右倾 $(a_i,a_i+h_i]$ 乘上 $\dfrac{100-r_i}{100}$，初始所有位置概率为 $100\%$，然后在单点查询蘑菇这个位置的概率统计答案即可。

我们知道浮点乘法很容易丢失精度，所以先取 $\ln$，查询时 $\exp$ 一下就行了。

由于 $a_i$ 值域很大，所以要离散化。

```cpp
#include <bits/stdc++.h>

#define ll long long
#define db double 
#define ldb long db

using namespace std;

const ll Maxn=1e6+7;
template<typename T>
class BIT{
	#define lowbit(x) (x&-x)
	public:
		inline void init(ll N){sz=N;}
		inline void add(ll x,T val){while(x<=sz){tr[x]+=val;x+=lowbit(x);}}
		inline void add(ll l,ll r,T val){add(l,val);add(r+1,-val);}
		inline T query(ll x){T res=0;while(x){res+=tr[x];x-=lowbit(x);}return res;}
	private:
		ll sz;
		T tr[Maxn];
};

BIT<ldb>tree2;
BIT<ll>tree1;

ll n,m;
ll a[Maxn],h[Maxn],l[Maxn],r[Maxn],b[Maxn],z[Maxn];
ll vec[Maxn],cnt; 
ldb ans;

int main(){
	scanf("%lld%lld",&n,&m);
	tree2.init(1e6);
	tree1.init(1e6);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld%lld",&a[i],&h[i],&l[i],&r[i]);
		vec[++cnt]=a[i]+h[i],vec[++cnt]=a[i],vec[++cnt]=a[i]-h[i];
	}
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&b[i],&z[i]);
		vec[++cnt]=b[i];
	}
	sort(vec+1,vec+cnt+1);
	ll nw=unique(vec+1,vec+cnt+1)-vec-1;
	
	for(int i=1;i<=n;i++){
		ll L=lower_bound(vec+1,vec+nw+1,a[i]-h[i])-vec;
		ll mid=lower_bound(vec+1,vec+nw+1,a[i])-vec;
		ll R=lower_bound(vec+1,vec+nw+1,a[i]+h[i])-vec;
		if(!l[i]);else if(l[i]==100) tree1.add(L,mid-1,1);
		else {
			const ldb lv=log(1-l[i]*1./100);
			tree2.add(L,mid-1,lv);
		}
		if(!r[i]);else if(r[i]==100) tree1.add(mid+1,R,1);
		else {
			const ldb rv=log(1-r[i]*1./100);
			tree2.add(mid+1,R,rv);
		}
	}
	
	for(int i=1;i<=m;i++){
		ll B=lower_bound(vec+1,vec+nw+1,b[i])-vec;
		if(tree1.query(B)>0) continue;
		ans+=exp(tree2.query(B))*z[i];
	
	}
	printf("%.8Lf",ans);
	return 0;
}

/*
2 2
-8 4 66 9
-2 3 55 43
3 8
7 9

*/
```


---

## 作者：HyperSQ (赞：0)

[题面](https://www.luogu.com.cn/problem/CF138C)

~~调了很久发现是愚蠢的错误，麻了。~~

价值总和期望，考虑每一个蘑菇对答案的贡献。

单一蘑菇对答案的贡献为
$$
z_i\prod(1-p_j)
$$
其中 $p_j$ 表示能砸到该蘑菇的树的倒下概率。

可以将蘑菇的位置离散化后，用数据结构进行区间乘 $1-p_j$，在统计蘑菇价值时使用单点查询。

可以用线段树。

但树状数组其实也可以，我的老师提供了一个方案，考虑将概率换算为自然对数值，这样区间乘法就变成加法了，不怕精度问题。概率为 $0$ 时特判一下，把区间标记为非法。很妙。

Code:

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=1e5+5;
int n,m,p;
ll vec[maxn*6],cnt,val[maxn*6];
ll a[maxn],b[maxn],l[maxn],r[maxn],h[maxn],z[maxn];
long double C[maxn*6];ll A[maxn*6];

void add(int x,int k){
	while(x<=p){
		A[x]+=k;
		x+=-x&x;
	}
}
void update(int x,long double k){
	while(x<=p){
		C[x]+=k;
		x+=x&-x;
	}
}
long double query(int x){
	long double ret=0.0;
	while(x){
		ret+=C[x];
		x-=x&-x;
	}
	return ret;
}
bool check(int x){
	ll ret=0;
	while(x){
		ret+=A[x];
		x-=x&-x;
	}
	return ret>0;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld%lld%lld",&a[i],&h[i],&l[i],&r[i]);
		vec[++cnt]=a[i]-h[i];
		vec[++cnt]=a[i];
		vec[++cnt]=a[i]+h[i];
	}
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&b[i],&z[i]);
		vec[++cnt]=b[i];
	}
	for(int i=1;i<=cnt;i++){
		val[i]=vec[i];
	}
	sort(val+1,val+cnt+1);
	p=unique(val+1,val+cnt+1)-val-1;
	for(int i=1;i<=n;i++){
		int L=lower_bound(val+1,val+p+1,a[i]-h[i])-val;
		int mid=lower_bound(val+1,val+p+1,a[i])-val;
		int R=lower_bound(val+1,val+p+1,a[i]+h[i])-val;
		if(!l[i]);
		else if(100-l[i]) update(L,log(1.00-l[i]/100.0)),update(mid,-log(1.00-l[i]/100.0));
		else add(L,1LL),add(mid,-1LL);
		if(!r[i]);
		else if(100-r[i]) update(mid+1,log(1.00-r[i]/100.0)),update(R+1,-log(1.00-r[i]/100.0));
		else add(mid+1,1LL),add(R+1,-1LL);
	}
	long double ans=0.0;
	for(int i=1;i<=m;i++){
		int x=lower_bound(val+1,val+p+1,b[i])-val;
		if(check(x)||!z[i]) continue;
		ans+=exp(query(x))*z[i];
	}
	cout<<fixed<<setprecision(10)<<ans<<endl;
}
```



---

