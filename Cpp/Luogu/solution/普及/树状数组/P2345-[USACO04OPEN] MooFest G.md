# [USACO04OPEN] MooFest G

## 题目背景

[P5094 [USACO04OPEN] MooFest G 加强版](https://www.luogu.com.cn/problem/P5094)


## 题目描述

约翰的 $n$ 头奶牛每年都会参加“哞哞大会”。

哞哞大会是奶牛界的盛事。集会上的活动很多，比如堆干草，跨栅栏，摸牛仔的屁股等等。

它们参加活动时会聚在一起，第 $i$ 头奶牛的坐标为 $x_i$，没有两头奶牛的坐标是相同的。

奶牛们的叫声很大，第 $i$ 头和第 $j$ 头奶牛交流，会发出
$\max\{v_i,v_j\}\times |x_i − x_j |$ 
的音量，其中 $v_i$ 和 $v_j$ 分别是第 $i$ 头和第 $j$ 头奶牛的听力。

假设每对奶牛之间同时都在说话，请计算所有奶牛产生的音量之和是多少。

## 样例 #1

### 输入

```
4
3 1
2 5
2 6
4 3```

### 输出

```
57```

# 题解

## 作者：龙·海流 (赞：78)

由于不会用洛谷的表格，所以之前写的题解看起来比较呲毛，在即将退役之际，用图床优化了一下外观。。。~~（真的退役了，闭关虽云乐，不如早早滚回去学文化课。。。）~~

这道题，如果考虑暴力的话，肯定会炸...

只能对公式**max{Vi; Vj}×|Xi − Xj |**进行优化

对于max，很容易想到sort将vi从小到大排序。。。

然后，优化绝对值的漫漫征程就此开始...

先研究一下样例 （sort后）

![](https://cdn.luogu.com.cn/upload/image_hosting/cuhhncip.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们建立一个坐标轴，安置一下各位奶牛

![](https://cdn.luogu.com.cn/upload/image_hosting/jkni8wbp.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

先把第一头放进去

![](https://cdn.luogu.com.cn/upload/image_hosting/2qwbozd6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

此时他周围没有牛，不发声

接着是第二头

![](https://cdn.luogu.com.cn/upload/image_hosting/k89427qp.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

2号牛前面有一头牛，于是发出声音2*（6-5）

然后是第三头...

![](https://cdn.luogu.com.cn/upload/image_hosting/r851jxtb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

在3号后面有两头牛，发出声音3*（5-1+6-1）也就是3*（5+6-1*2）（但愿你会想到什么）

最后是第四头

![](https://cdn.luogu.com.cn/upload/image_hosting/l57wngsb.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

4号前有一头牛，后有两头牛，于是发出声音3*（3-1）+3*（5+6-3*2）

样例讲完了...

这时思路就出来了，我们把牛一头又一头地放入坐标系，每次放进去都算一次他与其他所有放进去的牛的声音，最后把每次放入求出的值加起来就是答案

或许你会发现，第i头牛和其他的牛发出的声音就等于=第i头牛的vi*（它之前牛的数目*它的坐标-它之前所有牛的坐标和）+vi*（它之后所有牛的坐标和-它之后牛的数目*他的坐标），对于牛的数目和牛的坐标，我们都可以用树状数组来维护一下...

如果你不明白为什么树状数组能维护，那我就拿牛的坐标来举一个例子...
   
以样例为例，开一个和坐标轴等长的树状数组，加入1号（**插入位置为1号的横坐标，值为1**），此时sum[maxx]=1,加入2号，sum[maxx]=2,二号之前于是有sum[5]头牛，之后有sum[maxx]-sum[6]头牛，加入三号，它之前有sun[0]头牛，之后有sum[maxx]-sum[1]头牛，以此类推...

一定开long long ！！！

切记切记

代码如下


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long wz[20010],yy[20010],n,mn=20000;
long long ans;
long long read()
{	
    long long xx=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9')
    {
     	xx=xx*10+ch-'0';
     	ch=getchar();
    }
    return xx;
}
struct node{
    long long xi;
    long long vi;
}a[20010];
bool cmp(node x,node y)
{
   	return x.vi<y.vi;
}
int lobit(int x) {	return x&(-x);}
void crwz(int x) { for(;x<=mn;x+=lobit(x)) wz[x]++;}
int z(int x)
{
    int sum=0;
    for(;x>=1;x-=lobit(x)) sum+=wz[x];
    return sum;
}
void cryy(int x,int v) { for(;x<=mn;x+=lobit(x)) yy[x]+=v;}
int y(int x)
{
    int sum=0;
    for(;x>=1;x-=lobit(x)) sum+=yy[x];
    return sum;
}
int jdz(int x)
{
    if(x<0) return -x;
    else return x;
}
int main()
{
    n=read();
    for(int i=1;i<=n;++i) a[i].vi=read(),a[i].xi=read();
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;++i)
    {
        int j=a[i].xi;
        ans+=a[i].vi*(z(j-1)*j-y(j-1)+y(mn)-y(j)-(z(mn)-z(j))*j);
        crwz(a[i].xi);
        cryy(j,a[i].xi);
    }
    printf("%lld",ans);
    return 0;
}
```
谢谢观看！！！

---

## 作者：双管荧光灯 (赞：55)

这题其实可以什么数据结构都不用，分治

将数组先按v值排序

然后找到中点mid，左右递归处理

因为v值排过序，所以右边的v值一定大于左边v值

就剩x不好算了

看到绝对值，最简单的方法就是去绝对值符号

所以我们应该枚举右边mid+1到r的区间，找到有哪些x值比当前小，哪些比它大

右边的v值一定大于左边v值，求和乘a[i].v就行了

但是，这又该怎么做呢？

也许左右x值为升序就好做了，这就像求逆序对一样

因此我们再对序列进行归并排序

尽管这会对v值的升序进行破环，但由于中间的划分，所以左右不会混合，前面那个 性质还能保证

code：

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <algorithm>
using namespace std;
int n,i;
long long ans;
struct str{
    int x,v;
}a[100005],tmp[100005];
bool cmp(str x,str y)
{
    return x.v<y.v;
}
void cdqdfs(int l,int r)
{
    if(l>=r)
        return;
    int mid=(l+r)/2,ll=l,i;
    long long s1=0,s2=0;
    cdqdfs(l,mid);
    cdqdfs(mid+1,r);
    for(i=l;i<=mid;i++)
        s1+=a[i].x;
    for(i=mid+1;i<=r;i++)
    {
        while(ll<=mid&&a[ll].x<a[i].x)//ll为划分的中点，其左边都小于a[i].x，右边都大于或等于a[i].x
        {
            s2+=a[ll].x;
            s1-=a[ll].x;
            ll++;
        }
        ans+=(1ll*a[i].x*(ll-l)-s2-1ll*a[i].x*(mid-ll+1)+s1)*a[i].v;
    }
    int l1=l,l2=mid+1,k=l-1;
    while(l1<=mid||l2<=r)//归并排序
    {
        if((a[l1].x>a[l2].x||l1>mid)&&l2<=r)
        {
            tmp[++k]=a[l2];
            l2++;
        }
        else
        {
            tmp[++k]=a[l1];
            l1++;
        }
    }
    for(i=l;i<=r;i++)
        a[i]=tmp[i];
}
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d %d",&a[i].v,&a[i].x);
    sort(a+1,a+1+n,cmp);
    cdqdfs(1,n);
    cout<<ans;
}

```

---

## 作者：King丨帝御威 (赞：54)

有没有搞错呀？？？这题为什么要用树状数组啊？？难道不应该是枚举么……为什么标签没有啊……可能是我太弱了吧，只会枚举……
对于这个题，就直接n方暴力枚举就可以了，排序什么的，根本不需要……
emmmmmm，于是，本题最短代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 100001
using namespace std;
int n,m;
long long ans;
struct node             //结构体存储。
{
	int v,x;
}e[100001];
int main() 
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d",&e[i].v,&e[i].x);
	for(int i=1;i<=n;++i) 
	for(int j=i+1;j<=n;++j)         //n方枚举累加。
	ans+=max(e[i].v,e[j].v)*abs(e[i].x-e[j].x);
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：UltiMadow (赞：18)

这两天在学cdq分治，于是用cdq分治A了这道题

看到题解区里有用归并ac这道题的，于是我来贡献一个不太正常的cdq分治 ~~（写起来不知道比归并好写到哪里去了）~~

cdq分治就是通过前一半的数据去计算前一半对后一半的影响（或者说贡献）

首先，我们还是先对$v$排序（当然是升序啦）

这样，我们后面计算的时候就只要考虑$x$了（因为是$max(v_i,v_j)$，排完序之后$v_j>v_i(i<j)$，所以直接乘后面那个的$v$就好了）

接下来我们就要考虑一下$x$的事情了

我们来看看与$x$有关的式子：
$$
|x_i-x_j|
$$
看起来我们可以去掉绝对值呢

去掉再来看看：
$$
x_i-x_j(x_i>x_j)
$$
$$
x_j-x_i(x_i<x_j)
$$
在我们计算前一半对后一半的贡献时，我们要枚举后一半区间里的每一个点，计算前一半区间里的所有点到这个点的距离和

那么，这些点到一个点的距离和如何求呢

我们得到这样一个式子：
$$
sum=cnt1\times x_i-\sum_{x_i>x_j} x_j+\sum_{x_i<x_j}x_j-cnt2\times x_i
$$
其中，$sum$为距离和，$i$为当前点，$cnt1$为前一半区间内坐标小于（等于）当前点坐标的点的数量，$cnt2$就是前一半区间内坐标大于当前点坐标的点的数量（应该比较好理解）

显然，这个式子可以在$O(n^2)$的时间内做完

那么把这个$x$进行排序了以后就可以在之后的循环里面$O(n)$解决了（此处感觉表达不清楚，如果不理解就看代码吧qaq）

总时间复杂度为$O(nlogn)$

代码：
```cpp
#include<bits/stdc++.h>
#define MAXN 20010
#define int long long//本题要用long long
using namespace std;
int n;
struct Node
{
	int v,x;
}cow[MAXN];
bool cmp1(Node x,Node y)//以v为第一关键字排序
{
	if(x.v!=y.v)return x.v<y.v;
	return x.x<y.x;
}
bool cmp2(Node x,Node y)//以x为第一关键字排序（其实这个排序不需要第二关键字）
{
	if(x.x!=y.x)return x.x<y.x;
	return x.v<y.v;//即这一行可以省去不写
}
int ans;
void cdq(int l,int r)
{
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid);cdq(mid+1,r);//标准cdq分治
	sort(cow+l,cow+mid+1,cmp2);sort(cow+mid+1,cow+r+1,cmp2);//两个sort，保证左右区间内部的x坐标都是有序的
	//这两个sort就替代了之前题解里面的归并排序，更好写但是耗时更多
	int sum1=0,sum2=0;
	//sum2统计在左区间中坐标小于当前坐标的坐标和，sum1统计在左区间中坐标大于当前坐标的坐标和
	for(int i=l;i<=mid;i++)
		sum1+=cow[i].x;//先求和，再在循环过程中更新
	for(int i=mid+1,j=l;i<=r;i++)
	{
		while(j<=mid&&cow[j].x<cow[i].x)
			sum1-=cow[j].x,sum2+=cow[j].x,j++;
   		//如果遇到坐标比当前坐标小的，在小于当前坐标的坐标和上累加，在大于当前坐标的坐标和中减去
		int cnt1=j-l,cnt2=mid-j+1;//通过j来计算小于和大于当前坐标的个数
		ans+=cow[i].v*(cnt1*cow[i].x-sum2+sum1-cnt2*cow[i].x);
		//这就是上面所说的式子
		//由于现在的左区间和右区间都是有序的了，所以右区间内后面的坐标比前面的坐标大
		//所以能保证之前加入sum2的点不会再次更改，所以这么做是正确的
	}
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld%lld",&cow[i].v,&cow[i].x);
	sort(cow+1,cow+n+1,cmp1);//以v为第一关键字排序
	cdq(1,n);printf("%lld\n",ans); 
	return 0;
}
```
接下来，我再来对这个程序做一些小小的解释：

1.我们在cdq分治中不断地对每个区间内的信息重新按照$x$来排序，但是这样排序会不会影响第一次以$v$排序需要维护的结果呢？

肯定不会

因为第一次排序只是为了在分治中二分时在后面统计答案的时候直接拿右区间内的$v$去乘就好了，而在区间与区间内部排序，在最后统计答案的时候的右区间内的$v$是一定大于（或者等于）左区间内的$v$的

这个应该很好理解，因为毕竟没有让左区间和右区间混在一起排序嘛

2.我再做完这道题了以后，又去翻了翻题解，看到了里面的归并排序的写法，是放在cdq分治的最后的，我自己想了想，其实只要让我们在统计答案的时候的$x$值是有序的就可以了，而写在前面和写在后面其实是等价的（不理解可以自己在草稿纸上画画）

也就是说，上面的那段cdq分治的代码也可以这么写：
```cpp
void cdq(int l,int r)
{
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid);cdq(mid+1,r);
	int sum1=0,sum2=0;
	for(int i=l;i<=mid;i++)
		sum1+=cow[i].x;
	for(int i=mid+1,j=l;i<=r;i++)
	{
		while(j<=mid&&cow[j].x<cow[i].x)
			sum1-=cow[j].x,sum2+=cow[j].x,j++;
		int cnt1=j-l,cnt2=mid-j+1;
		ans+=cow[i].v*(cnt1*cow[i].x-sum2+sum1-cnt2*cow[i].x);
	}
	sort(cow+l,cow+r+1,cmp2);//变化在这里
}
```
用这个代码交上去是可以ac的 ~~（代码又短了呢）~~

不知道写前面和写后面在时间上面有没有什么变化（我指的是常数上面有没有变化），请求大佬解答qaq

那么，同样的道理，题解中的归并排序也可以提到统计答案之前，但是要写两遍qaq

---

## 作者：Limerick (赞：13)

老样子，感谢大神yg对我的指导@sgygd2004

首先发一波闲扯（如果你不想看的话，也可以跳过，直接看正题部分）：没想到yd大神居然还用的是分治！！！，我这个蒟蒻表示一脸懵逼（而且我还听了现场演说，看来不得不承认神犇和蒟蒻之间天大的差距啊！！！）

好了，闲扯结束，接下来进入正题。首先说明一下题意：

有n个人，每个人都有一部手机，每部手机都有一个信号强度V[i]，每个人有一个位置X[i]，如果位置在x[i]的人要和位置在xj的人聊天，那么这两人组成的一对的信号发射强度就是abs(x[i]-x[j])\*max(v[i],v[j])，求信号发射总强度。

首先撇开yg大神的分治，说一说自己的思路：

开两个树状数组num和sum，num(i)表示坐标1……i范围内的人数,sum(i)表示坐标在1……i范围内的人坐标之和。

首先将人按坐标大小升序排序（这样可以消去max函数），顺序统计人i与之前的i-1个人构成的i-1的一对信号强度对答案的贡献之和：

那么ans=v(i)\*(xi\*num(xi)-sum(xi)+当前统计到的答案-sum(xi)-xi\*(i-num(xi)))

闲话少叙,贴上ac代码:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<ctime>
using namespace std;
```
/\*
P2657低头一族 题解

\*/
```cpp
const int N=10000005;
long long ans,n,num[N],sum[N],i;
struct node{
    int x,v;
}stu[N];//结构体
//以下是树状数组模板
long long lowbit(long long x){
    return x&(-x);
```
}//通用lowbit
/\*
第一个树状数组sum

\*/
```cpp
void tree1(long long x,long long p){
    while(x<=20000){
        sum[x]+=p;
        x+=lowbit(x);
    }
    return;
}
long long sum1(long long k){
    long long tmp=0;
    while(k>0){
        tmp+=sum[k];
        k-=lowbit(k);
    }
    return tmp;
}
```
/\*
第二个树状数组num

\*/
```cpp
void tree2(long long x,long long p){
    while(x<=20000){
        num[x]+=p;
        x+=lowbit(x);
    }
    return;
}
long long sum2(long long k){
    long long tmp=0;
    while(k>0){
        tmp+=num[k];
        k-=lowbit(k);
    }
    return tmp;
}
//好了,模板到此结束
bool cmp(node p,node q){//排序
    if(p.v!=q.v){//如果信号强度不同(题意中已说明有可能会有两个人信号强度相同)
        return p.v<q.v;//按信号强度升序排列
    }
    return p.x<q.x;//如果信号强度相同,按所在位置升序排列
}
int main(){
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>stu[i].v>>stu[i].x;
```
}//读入
```cpp
    sort(stu+1,stu+1+n,cmp);
    for(i=1;i<=n;i++){
        tree1(stu[i].x,stu[i].x);//坐标1……i范围内的坐标
        tree2(stu[i].x,1);//坐标在1……i范围内的人数
        ans+=((sum2(stu[i].x))*stu[i].x-sum1(stu[i].x)+sum1(20000)-sum1(stu[i].x)-(i-sum2(stu[i].x))*stu[i].x)*stu[i].v;
```
/\*
(sum2(stu[i].x))\*stu[i].x相当于xi\*num(xi),即x[i]前面的人数\*xi

sum1(stu[i].x)相当于sum(xi),即x[i]前面人的坐标之和

sum1(20000)相当于allsum,即当前统计到的答案

sum1(stu[i].x)相当于sum(xi),即x[i]后面人的坐标之和

(i-sum2(stu[i].x))\*stu[i].x相当于(i-num(xi)),即x[i]后面的人数\*x[i]

\*/
```cpp
    }
    cout<<ans<<endl;//输出ans
    //while(1);
    exit(0);
}
```
好了，自己的思路讲完了，接下来我们来叙一叙yg大神的分治，说实话刚听到可以用分治做我是懵逼的(听了两遍才听懂)。
分治：首先找出一个中点mid，然后向左向右延伸，因为V[i]已经排好序,所以可以保证前面所有处理过的数v[i]比当前处理的小，后面所有处理过的数v[i]比当前处理的大。

因为右边的V[i]一定大于左边的V[i],所以我们应该枚举[mid+1,r]的区间,找有多少X比当前状态小，有多少X比当前状态大（也就是yg大神所说的求有多少对逆序对，这里需要用到一个特殊知识：归并排序求逆序对（听说树状数组好像也行，不过本蒟蒻用的一直是归并））

归并排序求逆序对代码如下：

```cpp
void gb(int l,int r){
    if(l==r)
        return;
    int mid=l+r>>1;
    i=l;j=mid+1;k=0;
    while(i<=mid&&j<=r){
        if(c[i]<c[j])
            d[++k]=c[i++];
        else{
            d[++k]=c[j++];
            ans+=mid-i+1;
        }
    }
    while(i<=mid)
        d[++k]=c[i++];
    while(j<=r)
        d[++k]=c[j++];
    for(i=l;i<=r;i++)
        c[i]=d[i];
    return;
}
```
归并排序是将数列a[l,h]分成两半a[l,mid]和a[mid+1,h]分别进行归并排序，然后再将这两半合并起来。
在合并的过程中（设l<=i<=mid，mid+1<=j<=h），当a[i]<=a[j]时，并不产生逆序数；当a[i]>a[j]时，在

前半部分中比a[i]大的数都比a[j]大，将a[j]放在a[i]前面的话，逆序数要加上mid+1-i。因此，可以在归并

排序中的合并过程中计算逆序对.

参考网址：http://blog.csdn.net/acdreamers/article/details/16849761

然后求和\*V[i]就行了

OK,分治详情代码请见楼下


---

## 作者：歌吟入梦 (赞：12)

看了楼下讲CDQ分治的主要讲的是CDQ分治的板子，但是对于拆绝对值得出那个式子没怎么讲，我就来说一下：

（默认您已经会CDQ分治了，如果还不会，建议坐一坐“陌上花开”这道题）

如果目前需要知道区间的第$i$头牛（第$i$头牛在左边，且右边有k头牛）的$\Sigma_{l=1}^{k}{max\{v_i,v_l\}\times|x_i-x_l|}$，而有$j$头在右边的牛的$x$值小于等于$x_i$（然而因为个人码风问题，在代码中是$j-1$头，这种细节问题注意一下即可）

然后就开始颓柿子了：

$\Sigma_{l=1}^{k}{max\{v_i,v_l\}\times|x_i-x_l|}$

$=\Sigma_{l=1}^{k}v_l\times|x_i-x_l|$

$=(\Sigma_{l=1}^{j}v_l\times(x_i-x_l))+(\Sigma_{l=j+1}^{k}v_l\times(x_l-x_i))$

$=x_i\times((\Sigma_{l=1}^{j}v_l)-(\Sigma_{l=j+1}^{k}v_l))+((\Sigma_{l=j+1}^{k}v_l\times x_l)-(\Sigma_{l=1}^{j}v_l\times x_l))$

$=x_i\times((2\Sigma_{l=1}^{j}v_l)-(\Sigma_{l=1}^{k}v_l))+((\Sigma_{l=1}^{k}v_l\times x_l)-(2\Sigma_{l=1}^{j}v_l\times x_l))$

剩下的事情非常显然：令$S1_m=\Sigma_{l=1}^{m}v_m$，$S2_m=\Sigma_{l=1}^{m}v_l\times x_l$

则$\Sigma_{l=1}^{k}{max\{v_i,v_l\}\times|x_i-x_l|}$

$=x_i\times(2S1_j-S1_k)+(S2_k-2S2_j)$

可O(1)求得

其它步骤其它大佬的题解已经说的够清楚了，此处就不说了。

附上AC代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
template<class T>inline void read(T&a){
	char c=getchar();int f=1;a=0;
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c<='9'&&c>='0') a=(a<<1)+(a<<3)+c-48,c=getchar();
	a*=f;
}
template<class T>void write(T a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) write(a/10);
	putchar(a%10+48);
}
const int o=1e5+10;
long long n,x[o],v[o],p[o],q[o],ans,s1[o],s2[o];
inline bool cmp(int A,int B){return v[A]<v[B];}
inline bool cmp2(int A,int B){return x[A]<x[B];}
void cdq(long long p[],long long N){
	if(N==1) return;
	int md=N>>1,i,j;
	cdq(p,md);cdq(p+md,N-md);
	for(i=1;i<=N;++i) q[i]=p[i];
	sort(p+1,p+md+1,cmp2);sort(p+md+1,p+N+1,cmp2);
	for(i=md+1;i<=N;++i) s1[i-md]=s1[i-md-1]+v[p[i]],s2[i-md]=s2[i-md-1]+v[p[i]]*x[p[i]];
	for(i=1,j=md+1;i<=md&&j<=N;)
		if(x[p[i]]<x[p[j]]) ans+=x[p[i]]*(2*s1[j-md-1]-s1[N-md])-2*s2[j-md-1]+s2[N-md],++i;else ++j;
	if(j==N+1) for(;i<=md;++i) ans+=x[p[i]]*(2*s1[j-md-1]-s1[N-md])-2*s2[j-md-1]+s2[N-md];
	for(i=1;i<=N;++i) p[i]=q[i];
}
int main(){
	read(n);
	for(int i=1;i<=n;++i) read(v[i]),read(x[i]),p[i]=i;
	sort(p+1,p+1+n,cmp);
	cdq(p,n);
	write(ans);
	return 0;
}
```

---

## 作者：zhouenji (赞：10)

树状数组，额额，本人表示不是很会；写写线段树还行，楼下的线段树似乎并不完整，于是只有自己写了。

本题由于是取音量较大的奶牛，于是可以先将奶牛的音量排序，然后将奶牛一个一个加入线段树中（线段树是以x值建立的）；

本题中可维护两个sum值，sum1为（l，r)中所有奶牛到0点的距离和；sum2位（l，r）中奶牛的个数；

然后就可O（1）的查询此前奶牛与当前奶牛的距离差和了；

下面是代码：


```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=100000+10;
struct nod
{
    long long v,x;
}s[maxn];
struct node
{
    int left,right;
    long long sum1,sum2;
}t[maxn*4];
long long n,maxs,ans;
bool cmp(nod a,nod b)
{
    return a.v<b.v;
}
void build(int g,int l,int r)
{
    t[g].left=l;t[g].right=r;t[g].sum1=t[g].sum2=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(g<<1,l,mid);build(g<<1|1,mid+1,r);
}
long long get(int g,int l,int r,int opt)
{
    if(r<t[g].left || t[g].right<l) return 0;
    if(l<=t[g].left&&t[g].right<=r)
    {
        if(opt==1) return t[g].sum1;
        if(opt==2) return t[g].sum2;
    }
    return get(g<<1,l,r,opt)+get(g<<1|1,l,r,opt);
}
void add(int g,int x,long long y)
{
    if(t[g].left==t[g].right)
    {
        t[g].sum1+=y;t[g].sum2++;return;
    }
    if(x<=t[g<<1].right) add(g<<1,x,y);
    else add(g<<1|1,x,y);
    t[g].sum1=t[g<<1].sum1+t[g<<1|1].sum1;
    t[g].sum2=t[g<<1].sum2+t[g<<1|1].sum2;
}
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&s[i].v,&s[i].x);
        maxs=max(maxs,s[i].x);
    }
    sort(s+1,s+n+1,cmp);
    build(1,1,maxs);
    for(int i=1;i<=n;i++)
    {
        long long g=get(1,s[i].x+1,maxs,1);//距离
        long long k=get(1,s[i].x+1,maxs,2);//个数
        ans+=s[i].v*(g-k*s[i].x);
        g=get(1,1,s[i].x-1,1);
        k=get(1,1,s[i].x-1,2);
        ans+=s[i].v*(k*s[i].x-g);
        add(1,s[i].x,s[i].x);
    }
    printf("%lld\n",ans);
}
```

---

## 作者：KagurazakaKano (赞：7)

我非常玄学地[没**开**任何优化](https://www.luogu.org/record/show?rid=9327058)然后过了这道~~大水~~题。

具体思路：对于音量进行升序排序，那么如果$i > j$，那么肯定有$cow[i].v > cow[j].v$，然后在进行枚举取max的时候肯定是选择$cow[i].v$，正确性显而易见。

~~吐槽：对于本题的数据，其实暴力算法可以过的，为何你们这群julao都要用树状数组这种东西啦w~~

```cpp
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

struct node{
	int v,x;
	bool operator < (node x){  //重载小于号
		return v < x.v;
	}
}cow[20005];

/*以下部分是如果选择传cmp进去的cmp代码
bool cmp(node x, node y){
    return x.v < y.v;
}
*/

int main(){
	int n;
	ll ans = 0;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d%d",&cow[i].v,&cow[i].x); //读入
	}
	
	sort(cow + 1, cow + 1 + n);  //或者说可以写个cmp进去，在这里笔者选择了重载运算符。
    
    //sort(cow + 1, cow + 1 + n, cmp); 这行是如果选择cmp的写法
	
	for(int i = 1; i <= n; i++){
		for(int j = 1; j < i; j++){
			ans += cow[i].v * abs(cow[i].x - cow[j].x);  //根据题意进行N^2暴力的操作。
		}
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：小蒟蒻皮皮鱼 (赞：6)

一道树状数组的题。

话说题目直接告诉做法是什么鬼？

首先这个题直接暴力是$O(n^2)$的，不能通过（~~评论里说可以？可能数据太水了，建议加强~~）

考虑优化，首先对于答案里的$max$，可以直接通过排序优化掉，即把数据从小到大排序，每次更新答案的时候就直接使用当前的$V$就可以了。

之后看这个式子：$|X_i - X j|$。单独看没有什么特点，但是如果我们对于$i$，讨论一下$j$，就可以发现规律。显然对于$j$，可以分成两类，即$\{j_1|X_{j1}<X_i \}$和$\{ j_2|X_{j2}>X_i \}$。设当前$i$两边分别有$x_1,x_2$个$j$，那么答案就是$(x_1\times X_i- \Sigma X_{j1})+(\Sigma X_{j2}-x_2 \times X_i)$。

显然对于$\Sigma X_{j1}$，可以用前缀和直接求出。对于$\Sigma X_{j2}$，只需要用总的减去$\Sigma X_{j1}$就可以求出。

$x_1,x_2$同理也可以求出

这里选择树状数组。

最后别忘了开longlong，否则100pts->45pts。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 20005;
typedef long long ll;
int n;
ll iAns, iSum[N], iCnt[N];
struct sCow
{
	int V, X;
}cow[N];

inline bool cmp(sCow a, sCow b){return a.V < b.V;}
inline int lowbit(int x){return x & -x;}
inline void Add(int x, int k){for(; x <= N; x += lowbit(x)) iSum[x] += k, iCnt[x] += 1;}
inline void Query(int x, ll &ans, int &cnt){ans = 0, cnt = 0;for(; x; x -= lowbit(x)) ans += iSum[x], cnt += iCnt[x];}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &cow[i].V, &cow[i].X);
	sort(cow + 1, cow + 1 + n, cmp);
	ll S = 0, C = 0;
	for(int i = 1; i <= n; i++)
	{
		ll ans = 0;
		int cnt = 0;
		Query(cow[i].X, ans, cnt);
		iAns += cow[i].V * (cnt * cow[i].X - ans);
		iAns += cow[i].V * ((S - ans) - (C - cnt) * cow[i].X);
		Add(cow[i].X, cow[i].X);
		S += cow[i].X, C +=1;
	}
	cout << iAns;
}
```


---

## 作者：YoungNeal (赞：4)

## Solution

看到楼下大佬们的log级数据结构表示并不会，我只会暴力数据结构，于是我用分块过了这题。

首先将所有奶牛按照坐标升序排序，并假设我们已经求出每个奶牛到前面所有奶牛的距离和存进了qzh数组。  
考虑这个性质：当前扫到了奶牛i，那么奶牛i的贡献至少是$v[i]\times qzh[i]$，称这个为基础贡献。

所以我们不妨对所有奶牛先求出基础贡献，然后再在之后扫描一遍用奶牛i前面的v值比它大的奶牛j来更新一下答案，设答案为ans，也就是 $ans+=(v[j]-v[i])\times (x[i]-x[j])$ 。

展开这个式子， $v[j]\times x[i]-v[j]\times x[j]-v[i]\times x[i]+v[i]\times x[j]$。

发现这几项都可以用前缀和维护，就做完了。

用分块只是为了平衡一下时间复杂度

## Code
```cpp
#include<cmath>
#include<cstdio>
#include<cctype>
#include<vector>
#include<algorithm>
#define N 20005
#define int long long
#define min(A,B) ((A)<(B)?(A):(B))
#define max(A,B) ((A)>(B)?(A):(B))
#define swap(A,B) ((A)^=(B)^=(A)^=(B))

int n,ans;
int qzh[N];
int belong[N];
int block,l[N],r[N];
int vx[204][N],v[204][N],x[204][N];

struct Node{
    int a,b;
}node[N];

bool cmp(Node x,Node y){
    return x.a<y.a;
}

bool cmp2(Node x,Node y){
    return x.b<y.b;
}

int getint(){
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch)) f|=ch=='-',ch=getchar();
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}

void write(int x){
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

void init(int y){
    std::sort(node+l[y],node+r[y]+1,cmp2);
    vx[y][l[y]]=node[l[y]].a*node[l[y]].b;
    v[y][l[y]]=node[l[y]].b;
    x[y][l[y]]=node[l[y]].a;
    for(int i=l[y]+1;i<=r[y];i++){
        vx[y][i]=vx[y][i-1]+node[i].a*node[i].b;
        v[y][i]=v[y][i-1]+node[i].b;
        x[y][i]=x[y][i-1]+node[i].a;
    }
}

int bsearch(int l,int r,int p){
    int ans=0;
    while(l<=r){
        int mid=l+r>>1;
        if(node[mid].b>p)
            ans=mid,r=mid-1;
        else l=mid+1;
    }
    return ans;
}

signed main(){
    n=getint();
    block=sqrt(n);
    for(int i=1;i<=n;i++){
        belong[i]=(i-1)/block+1;
        node[i].b=getint();
        node[i].a=getint();
    }
    int tot=n/block+(n%block?1:0);
    for(int i=1;i<=tot;i++){
        l[i]=(i-1)*block+1;
        r[i]=i*block;
    } r[belong[n]]=n;
    std::sort(node+1,node+1+n,cmp);
    for(int i=2;i<=n;i++)
        qzh[i]=qzh[i-1]+(node[i].a-node[i-1].a)*(i-1),ans+=node[i].b*qzh[i];
    for(int i=2;i<=n;i++){
        if(belong[i]!=belong[i-1])
            init(belong[i-1]);
        for(int j=1;j<belong[i];j++){
            int p=bsearch(l[j],r[j],node[i].b);
            if(!p) continue; p--;
            int q=node[i].a*(v[j][r[j]]-v[j][p])-vx[j][r[j]]+vx[j][p]+node[i].b*(x[j][r[j]]-x[j][p])-(r[j]-p)*node[i].a*node[i].b;
            ans+=q;
        }
        for(int j=l[belong[i]];j<i;j++){
            if(node[j].b>node[i].b)
                ans+=node[i].a*node[j].b-node[j].b*node[j].a+node[i].b*node[j].a-node[i].a*node[i].b;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：墨舞灵纯 (赞：2)

    我的第六篇题解。（请大佬们多指教。当然，如果有看不懂的地方欢迎和我私信交流。）
    我略略翻看了一下题解，好像没有什么大佬写树状数组。那么我来讲一下树状数组的思路吧。我们用两个树状数组维护，一个维护xi的个数，另一个维护xi的和。先按照vi升序排序，保证前面所有处理过的vi比当前处理的小，后面所有处理过的vi比当前处理的大。那么ans=Σ(xi之前数的个数*xi-xi之前的总和+xi之后的总和-xi之后数的个数*xi)*vi.
    #include<cstdio>
	#include<algorithm>
	using namespace std;
	const int N=100005;
	typedef long long ll;
	ll ans,t1[N],t2[N],maxn;
	struct ro{
 	   int w,x;
	}a[N];
	int n;
	void add1(int x,int num){
  	  while(x<=maxn) t1[x]+=num,x+=(x&-x);
	}
	ll calc1(int x){
   	 	ll s=0;
   		 while(x) s+=t1[x],x-=(x&-x);
    	return s;
	}
	void add2(int x,int num){
    	while(x<=maxn) t2[x]+=num,x+=(x&-x);
		}
	ll calc2(int x){
    	ll s=0;
    	while(x) s+=t2[x],x-=(x&-x);
    	return s;
	}//树状数组模版
	bool cmp(ro p,ro q){
    	return p.w<q.w;
	}//排序
	int main(){
        scanf("%d",&n);
    	int i;
    	for(i=1;i<=n;i++) fast_read(a[i].w),fast_read(a[i].x),maxn=a[i].x>maxn?a[i].x:maxn;//这里的fr是快读，已经删去了，请不要复制哦
    	sort(a+1,a+1+n,cmp);
    	for(i=1;i<=n;i++){
        	add1(a[i].x,1),add2(a[i].x,a[i].x);//第一个记录个数，第二个记录总和
        	ll q1=calc1(a[i].x-1),q2=i-calc1(a[i].x),h1=calc2(a[i].x-1),h2=calc2(maxn)-calc2(a[i].x);
        	ans+=((q1-q2)*a[i].x+h2-h1)*a[i].w;
    	}
    	printf("%lld",ans);//注意longlong
    	return 0;
	}

---

## 作者：Invoker (赞：2)

开两个树状数组，一个维护x[i]的个数，另一个维护x[i]的总和。

先按照v[i]排序，保证前面所有处理过的数v[i]比当前处理的小，后面所有处理过的数v[i]比当前处理的大。

那么ans=Σ(x[i]前面的数的个数\*x[i]-x[i]前面的数的和+x[i]后面的数的和-x[i]后面的数的个数\*x[i])\*v[i].

代码丑勿喷....

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cctype>
#include<string>
#include<vector>
#include<cmath>
#include<stack>
#include<set>
#include<map>
#define for0(i,a,b) for(int i=(a);i<=(b);++i)
#define for1(i,a,b) for(int i=(a);i>=(b);--i)
#define prt printf
#define ms(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define mp make_pair
#define LL long long
const int oo=0x3f3f3f3f;
using namespace std;

inline int read()
{
    int x=0,f=1,hhh=getchar();
    while(!isdigit(hhh))
    {
        if(hhh=='-')
            f=-1;
        hhh=getchar();
    }
    while(isdigit(hhh))
    {
        x=x*10+hhh-'0';
        hhh=getchar();
    }
    return x*f;
}

const int maxn=100005;
#define lowbit(x) ((x)&(-x))
LL b[maxn],c[maxn];
int n;
int ma=-1;

void badd(int x,int d)
{
    while(x<=20001)
    {
        b[x]+=d;
        x+=lowbit(x);
    }
}

LL bquery(int x)
{
    LL ans=0;
    while(x>0)
    {
        ans+=b[x];
        x-=lowbit(x);
    }
    return ans;
}

void cadd(int x,int d)
{
    while(x<=20001)
    {
        c[x]+=d;
        x+=lowbit(x);
    }
}

LL cquery(int x)
{
    LL ans=0;
    while(x>0)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}

struct node
{
    int x,v;
    bool operator < (const node & tmp)const{return v<tmp.v;}
}a[100005];

LL sum=0;

int main()
{
    n=read();
    for0(i,1,n)
        a[i].v=read(),a[i].x=read(),ma=max(ma,a[i].x);
    sort(a+1,a+n+1);
    for0(i,1,n)
    {
        badd(a[i].x,a[i].x);
        cadd(a[i].x,1);
        LL prenum=cquery(a[i].x-1);
        LL lastnum=i-cquery(a[i].x);
        LL presum=bquery(a[i].x-1);
        LL lastsum=bquery(20001)-bquery(a[i].x);
        sum+=(prenum*a[i].x-presum+lastsum-lastnum*a[i].x)*a[i].v;
       }
    printf("%I64d\n",sum);
    return 0;
}
```

---

## 作者：ModestCoder_ (赞：1)

**P党的福利**（借鉴于在下某位基友）

这道题目是一道不错的练手题

我来发个树状数组的

max(vi,vj)\*abs(xi-xj)

看出两点

1、根据v从小到大排序，这个max就迎刃而解了

2、看这个abs，我刚开始天真的以为第i个牛与前面的牛（这里是按照v排序的）的总和为v\*(i\*xi-sigma(xj))

忽略了一个绝对值的性质，abs(a-(a+b))+abs(a-(a-b))=2b<>abs(2a-(a+b+a-b))=0

得分为两类，一类为位置比当前小的，另一类为位置比当前大的

令num为比当前小的个数，sum为比当前小的和,s为前缀和（用于求出比当前大的和）

那么第一类的和为v\*(num\*xi-sum)

第二类的和为v\*(s-sum-(i-1-num)\*xi)

另外，树状数组的下标得注意，i是表示<i还是<=i，会不一样









```cpp
type
    ar=array[0..100000] of int64;
var
    a,b,num,sum:ar;
    i:longint;
    ans,n,s:int64;
function lowbit(x:int64):int64;
begin
    exit(x and -x);
end;
procedure change(var c:ar;x,y:int64);
begin
    while x<=20000 do  //特别注意，开到足够，不然拿63分
        begin
            inc(c[x],y);
            inc(x,lowbit(x));
        end;
end;
function getsum(var c:ar;x:int64):int64;
begin
    getsum:=0;
    while x>0 do
        begin
            inc(getsum,c[x]);
            dec(x,lowbit(x));
        end;
end;
procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                y:=b[i];
                b[i]:=b[j];
                b[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;
begin
    readln(n);
    for i:=1 to n do
        readln(a[i],b[i]);
    sort(1,n);
    for i:=1 to n do
        begin
            inc(ans,a[i]*(getsum(num,b[i]-1)*b[i]-getsum(sum,b[i]-1)));
            inc(ans,a[i]*(s-getsum(sum,b[i]-1)-(i-1-getsum(num,b[i]-1))*b[i]));
            change(num,b[i],1);
            change(sum,b[i],b[i]);  //这边下标是<=i的情况
            inc(s,b[i]);
        end;
    writeln(ans);
end.

```

---

## 作者：hahalidaxin2 (赞：1)

【思路】

树状数组。

首先按照v从大到小的顺序排序，这样就相当于消除了v的影响，前面已经考虑的v一定小于等于当前的v。

其次考虑abs(x[i]-x[j])部分，刚开始想的是前缀和，但是注意到

abs(x-x1)+abs(x-x2)!=abs(2\*x-(x1+x2))

这里令numl表示之前的x比当前x小的数目，suml表示之前的x比当前x小的x之和，类似的定义sumr，numr。则当前

ans=(x\*numl-suml+sumr-numr\*x)

这里的numl suml等都可以通过BIT在O(logn)的时间内得到。总的时间复杂度为O(nlogn)。


需要注意从x开始查询或是从x-1开始查询在本题中并无区别。

【代码】

```cpp

#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define FOR(a,b,c) for(int a=(b);a<=(c);a++)
using namespace std;

typedef long long LL;
const int maxn = 100000+10 , maxm=20000+10;
struct Node{
    int x,v;
    bool operator<(const Node&rhs) const{
        return v<rhs.v;
    }
}nodes[maxn];
int n,Max;
////BIT 
int lowbit(int x) { return x&(-x); }
void Add(LL *C,int x,int v) {
    while(x<=Max) {
        C[x]+=v; x+=lowbit(x);
    }
}
LL query(LL *C,int x) {
    LL res=0;
    while(x>0) {
        res+=C[x]; x-=lowbit(x);
    }
    return res;
}
LL num[maxm],sum[maxm];

////read
int read_int() {
    char c=getchar();
    while(!isdigit(c)) c=getchar();
    int x=0;
    while(isdigit(c)) {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
} 
int main()
{
    n=read_int();
    FOR(i,1,n){
        nodes[i].v=read_int();
        nodes[i].x=read_int();
        Max=max(Max,nodes[i].x);
    }
    sort(nodes+1,nodes+n+1);
    LL ans=0;
    FOR(i,1,n) {
        int x=nodes[i].x,v=nodes[i].v;
        LL numl=query(num,x-1);
        LL suml=query(sum,x-1);
        LL numr=query(num,Max)-query(num,x);
        LL sumr=query(sum,Max)-query(sum,x);
        ans += v*(sumr-x*numr+x*numl-suml);
        Add(num,x,1);
        Add(sum,x,x);
    }
    cout<<ans<<"\n";
    return 0;
}

```

---

## 作者：attack (赞：1)

推公式的题目

设当前奶牛的音量为V,坐标为X,ai表示第i头奶牛的坐标

假定a1,a2>X,a3<X(方便理解)

我们发现abs不满足分配率(就是abs(a+b)!=abs(a)+abs(b) )

此时我们分情况讨论

设有n个奶牛的坐标比X大，有m个奶牛的坐标比X小,把上面的abs拆开

 ![](https://cdn.luogu.com.cn/upload/pic/9381.png) 

 ![](https://cdn.luogu.com.cn/upload/pic/9383.png) 

那么对于N,M,a1+a2+...,a3+,,,

利用用树状数组求逆序对的思想

我们可以用两个树状数组维护

代码
http://www.cnblogs.com/zwfymqz/p/7710854.html



---

## 作者：king_xbz (赞：0)

刷树状数组题目时遇到的题，题本身是好题，但数据太弱了

简单的模拟即可

注意千万不要重复计算奶牛间的说话次数，简单的排列组合即可
```cpp
#include<bits/stdc++.h>
#define int long long
#define p 34545
#define h 5001
#define fint register int
using namespace std;
int v[p],x[p];
inline int read();
signed main()
{
	int n;
	n=read();
	for(fint i=1;i<=n;i++)
	{
		v[i]=read();
		x[i]=read();
	}
	int t=0;
	for(fint i=1;i<=n;i++)
	for(fint j=i+1;j<=n;j++)
		t+=max(v[i],v[j])*abs(x[i]-x[j]);
	cout<<t;
	exit(0);
}
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
```
管理应该去调整一下数据了

---

## 作者：zhengzhi726 (赞：0)

分块
发现还没有人用分块做这个题来着
提供新思路
n根n复杂度
这种千奇百怪的数据结构体 就是分块的很好的练手题
分块的具体细节大家自己也都会
上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 20005
struct node{ll x,v;}s[maxn];
bool cmp(node a,node b){return a.v<b.v;}
ll n,m,k,a,b,c,ans=0,bs,mx,bn,pos[maxn],l[200],r[200],pre[200],nxt[200],sz[200],tag[maxn];
int main(){cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i].v>>s[i].x,mx=max(s[i].x,mx);
	bs=sqrt(mx),bn=mx/bs;l[1]=1;
	ll now=0;for(int i=1;i<=bn;i++)r[i]=now+bs,now+=bs,l[i]=r[i-1]+1;r[bn]=mx;
	for(int i=1;i<=bn;i++)for(int j=l[i];j<=r[i];j++)pos[j]=i;sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++){ll p=pos[s[i].x];
		for(int j=1;j<p;j++)ans+=s[i].v*(sz[j]*(s[i].x-l[j])-pre[j]);
		for(int j=p+1;j<=bn;j++)ans+=s[i].v*(sz[j]*(r[j]-s[i].x)-nxt[j]);
		for(int j=l[p];j<=r[p];j++){
			if(tag[j])ans+=s[i].v*abs(j-s[i].x);
		}sz[p]++,pre[p]+=s[i].x-l[p],nxt[p]+=r[p]-s[i].x,tag[s[i].x]=1;
	}cout<<ans<<endl;return 0;
}
```


---

## 作者：klzz (赞：0)

第一次打使用归并，但是调不出来，后来改用线段树，先以下标v来一次sort，因为v[i]>v[j]时才有价值，线段树按x来排序，这样每次都能得到其他点与当前点的距离差的和。

```cpp
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <set>
#include <queue>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define INF 0x3f3f3f3f
#define maxn 200010
using namespace std;
struct data{
    int v,x;
}e[maxn];
long long ans;
int now,L,R,Min,Max,n;
int sum[maxn],num[maxn];
bool cmp(const data&a,const data&b)
{
    return a.v<b.v;
}
void insert()；
long long query();
int main(){
    scanf("%d",&n);
    Min=INF;
    Max=-INF;
    for (int i=1;i<=n;i++)
    {
      scanf("%d%d",&e[i].v,&e[i].x);
      Min=min(Min,e[i].x);
      Max=max(Max,e[i].x);
    } 
    sort(e+1,e+1+n,cmp);
    ans=0;
    for (int i=1;i<=n;i++)
    {
        now=e[i].x;
        L=e[i].x; R=Max; //比e[i].x大范围
        ans+=e[i].v*query(1,Min,Max); //查找
        L=Min; R=e[i].x;//比e[i].x小范围
        ans-=e[i].v*query(1,Min,Max);//得到的是负数，所以 -
        insert(1,Min,Max,e[i].x);//插入
    }
    printf("%lld",ans);
    return 0;
}

```

---

## 作者：loidc (赞：0)

按v升序排序，答案就是vi\*abs(xi-xj) (2<=i<=n,1<=j<i)

如何处理abs(xi-xj)这部分呢？ 我们可以用线段树处理区间[xl,xr]内x的个数以及他们的和

答案就是

```cpp

                long long lsum = getsum(1,0,data[i].x);
        long long rsum = getsum(1,data[i].x+1,20000);
        int lnum = getnum(1,0,data[i].x);
        int rnum = getnum(1,data[i].x+1,20000);
        long long tmpl = ((long long)data[i].x * lnum) - lsum;
        long long tmpr = rsum - ((long long)data[i].x * rnum);
    //    printf("%d %d %d\n",data[i].x,lnum,rnum);
        ans += (tmpl + tmpr) * (long long)data[i].v;

```
完整代码如下：

```cpp

#include<cstdio>
#include<algorithm>
#define MAXN 100010
using namespace std;
struct Data{int x,v;}data[MAXN];
int n;
long long ans = 0;
struct Tree{int o,l,r,num;long long sum;}tree[1000010];
bool cmp(Data A,Data B)
{
    if(A.v==B.v) return A.x < B.x;
    return A.v < B.v;
}
void build(int o,int l,int r)
{
    tree[o].l = l , tree[o].r = r;
    if(l==r) return;
    int mid = (l+r) >> 1;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
}
long long getsum(int o,int l,int r)
{
    int L = tree[o].l , R = tree[o].r;
    if(r<L || R<l) return 0;
    if(L==l && R==r) return tree[o].sum;
    int mid = (L+R) >> 1;
    if(r<=mid) return getsum(o<<1,l,r);
    if(mid<l) return getsum(o<<1|1,l,r);
    return getsum(o<<1,l,mid)+getsum(o<<1|1,mid+1,r);
}
int getnum(int o,int l,int r)
{
    int L = tree[o].l , R = tree[o].r;
    if(r<L || R<l) return 0;
    if(L==l && R==r) return tree[o].num;
    int mid = (L+R) >> 1;
    if(r<=mid) return getnum(o<<1,l,r);
    if(mid<l) return getnum(o<<1|1,l,r);
    return getnum(o<<1,l,mid)+getnum(o<<1|1,mid+1,r);
}
void insert(int o,int pos)
{
    int L = tree[o].l , R = tree[o].r;
    if(L==R && L==pos)
    {
        tree[o].num++;
        tree[o].sum += pos;
        return;
    }
    int mid = (L+R) >> 1;
    if(pos<=mid) insert(o<<1,pos);
    else  insert(o<<1|1,pos);
    tree[o].sum = tree[o<<1].sum + tree[o<<1|1].sum;
    tree[o].num = tree[o<<1].num + tree[o<<1|1].num;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&data[i].v,&data[i].x);
    sort(data+1,data+1+n,cmp);
    build(1,0,20000);
    insert(1,data[1].x);
    for(int i=2;i<=n;i++)
    {
        long long lsum = getsum(1,0,data[i].x);
        long long rsum = getsum(1,data[i].x+1,20000);
        int lnum = getnum(1,0,data[i].x);
        int rnum = getnum(1,data[i].x+1,20000);
        long long tmpl = ((long long)data[i].x * lnum) - lsum;
        long long tmpr = rsum - ((long long)data[i].x * rnum);
    //    printf("%d %d %d\n",data[i].x,lnum,rnum);
        ans += (tmpl + tmpr) * (long long)data[i].v;
        insert(1,data[i].x);
    }
    printf("%lld",ans);
    return 0;
}

```

---

## 作者：MajorB_ (赞：0)

按位置进行划分而不是按人数进行划分，线段树维护三个域 num distl distr ，分别表示位置l到位置r之间的人数、到0的距离（sum(x[i]-0)）、到右端点的距离(sum(20000-x[i]+1))。对

v进行排序，然后每次拿出来一个最大的，求解其左侧点的答案和右侧点的答案，求出解之后删除。关键代码如下。

```cpp

for ( i=1;i<=n;++i)  
    {  
        ans = ans+v[i]*(queryl(x[i]+1,20000,1)-querynum(x[i]+1,20000,1)*x[i]+queryr(1,x[i]-1,1)-querynum(1,x[i]-1,1)*(20000-x[i]+1));  
        del(x[i],1,x[i],20000-x[i]+1);  
    }  

```
最难的就是求距离的公式  queryl(x[i]+1,20000,1)-querynum(x[i]+1,20000,1)\*x[i] 多画画图写个样例就懂了


---

