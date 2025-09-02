# [BalticOI 2007] Sound 静音问题

## 题目描述

数字录音中，声音是用表示空气压力的数字序列描述的，序列中的每个值称为一个采样，每个采样之间间隔一定的时间。 

很多声音处理任务都需要将录到的声音分成由静音隔开的几段非静音段。为了避免分成过多或者过少的非静音段，静音通常是这样定义的：$m$ 个采样的序列，该序列中采样的最大值和最小值之差不超过一个特定的阈值 $c$。 

请你写一个程序，检测 $n$ 个采样中的静音。

## 样例 #1

### 输入

```
7 2 0
0 1 1 2 3 2 2```

### 输出

```
2
6```

# 题解

## 作者：田大坑 (赞：22)

### 超级树状数组


------------

对于大部分oier来说，码线段树是一件十分困难的事情，对于这一个OB的算法又不得不去学习

而对于另一种友好的树形结构——树状数组就特别好码，可惜的是只能去求区间的和，以及单点修改

真的是这样吗？树状数组不是什么鸡肋，其实可以和线段树有一样的操作，对于区间的最大最小，是可以手动维护的

```
void add(int p,int x)//添加一个数（不能修改）
{
    for(;p<=n;p+=p&(-p))
    {
        c[p].mx=max(c[p].mx,x);//维护区间的最大以及最小
        c[p].mn=min(c[p].mn,x);
    }
}
```
之后求和就好了
```
bool sum(int l,int r)
{
    int mx=-0x7f7f7f7f,mn=0x7f7f7f7f;
    while(l<=r)
    {
        for(;r-(r&(-r))>=l;r-=r&(-r))//标配
        {
            mx=max(c[r].mx,mx);
            mn=min(c[r].mn,mn);
        }
        mx=max(mx,a[r]);
        mn=min(mn,a[r]);
        r--;//不是所有区间都已处理，所以会多次维护
    }
    if(abs(mx-mn)<=ci)
    return true;
    return false;
}
```
a下这到题目只需要上述两个操作

下面ac代码
```
#include<bits/stdc++.h>
using namespace std;
struct tree{
    int mx=-0x7f7f7f7f,mn=0x7f7f7f7f,a;
}c[1100101];
int n,m,ci,ans[1000001],a[1000001],cnt;
void add(int p,int x)
{
    for(;p<=n;p+=p&(-p))
    {
        c[p].mx=max(c[p].mx,x);
        c[p].mn=min(c[p].mn,x);
    }
}
bool sum(int l,int r)
{
    int mx=-0x7f7f7f7f,mn=0x7f7f7f7f;
    while(l<=r)
    {
        for(;r-(r&(-r))>=l;r-=r&(-r))
        {
            mx=max(c[r].mx,mx);
            mn=min(c[r].mn,mn);
        }
        mx=max(mx,a[r]);
        mn=min(mn,a[r]);
        r--;
    }
    if(abs(mx-mn)<=ci)
    return true;
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    scanf("%d%d%d",&n,&m,&ci);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&a[i]);
        add(i,a[i]);
    }
    for(int i=1;i<=n-m+1;i++)
    {
        if(sum(i,i+m-1))
        ans[++cnt]=i;
    }
    for(int i=1;i<=cnt;i++)
    {
        printf("%d\n",ans[i]);
    }
    if(cnt==0)
    cout<<"NONE";
}
```
其实怎么做的原因，手动模拟一下树状数组的维护操作就可以知道

其实我们还可以进行区间修改以及查询
```
void add(int c[],int p,int x)
{
    while(p<=n)
    {
        c[p]+=x;
        p+=p&(-p);
    }
}
void modify(int l,int r,int x)//区间修改（l——r的每一个数加上x）
{
    add(d1,l,x);
    add(d1,r+1,-x);
    add(d2,l,x*(l-1));
    add(d2,r+1,-x*r);
}
int sum_(int c[],int p)
{
    int s=0;
    while(p)
    {
        s+=c[p];
        p-=p&(-p);
    }
    return s;
}
int query(int l,int r)//区间求和（l——r）
{
    return r*sum_(d1,r)-sum_(d2,r)-((l-1)*sum_(d1,l-1)-sum_(d2,l-1));//想一想，为什么（huaji）
}
```
那么我们就用简单易懂的树状数组代替了线段树，由于代码量少，认真思考一两分钟就可以得出原因的代码，就不多加阐述

在考场上，面对功能极度全面的线段树O（Ologn），以及代码量少的树状数组O（nlognlogn），加以权衡

其实想要详细解释，可以去看洛谷日报22期，有说明和图的

---

## 作者：Uni_Tune (赞：21)

题目的意思是，对于每个长为$m$的序列，找出这些序列中最大值和最小值的差值不超过$c$的，并输出它们的起始位置

因为题目要求找每个区间的最大和最小值的差值，用模拟绝对不行，所以考虑使用单调队列来找出每个$m$长序列的最大最小值

用两个队列$q1$和$q2$，来储存每个从左往右长度为$m$的采样序列中的最大值以及最小值的位置，同步相减来看看有没有超过$c$的值，注意输出的是起始位置即可。

顺便解释一下，队列里存的是位置，方便操作。

所说的从左往右的$m$长序列是指：
$a_1$到$a_m$，$a_2$到$a_{m+1}$...$a_{n-m+1}$到$a_n$(这样自己看也可以懂得)

具体操作代码可见

```cpp
#include<cstdio>
#define MAXN 1000001
using namespace std;
bool p;
int n,m,c,dui1[MAXN],dui2[MAXN],a[MAXN],heada=1,taila=0,headb=1,tailb=0;
int main(){
	scanf("%d%d%d",&n,&m,&c);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		while(heada<=taila&&dui1[heada]+m<=i){
			heada++;
		}//这里的两个while的意思是如果最大值的位置不在所要寻找最大值的序列当中，就把它踢出去,反正是从左往右找吗
		while(headb<=tailb&&dui2[headb]+m<=i){
			headb++;
		} 
		while(heada<=taila&&a[i]>a[dui1[taila]]){
			taila--;
		} //这里的两个while能够减小时间复杂度,先把已经比要插入的小或大踢出去		
        dui1[++taila]=i;
		while(headb<=tailb&&a[i]<a[dui2[tailb]]){
			tailb--;
		} 
		dui2[++tailb]=i;
		if(i>=m){
			if(a[dui1[heada]]-a[dui2[headb]]<=c){
				printf("%d\n",i-m+1);
				p=true;
			}
		}
	}
	if(!p) printf("NONE");
	return 0;
}
```

---

## 作者：光明正大 (赞：15)

# ST表 静态区间最值问题

## 翻了翻题解，发现都是什么超级树状数组，单调队列什么的，蒟蒻表示不会

## 而线段树略显麻烦

## 有人写ST表但因为空间问题MLE

## 我来一波ST表（96MB）

不会ST表写一下 [模板题](https://www.luogu.org/problemnew/show/P3865)

其实ST表并不难

码风略丑

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c,lm,flag,a[1000100],po[12]={1};
//lm:log2(m) po[i]:2^i flag:是否有有解的,为0则输出NONE 
int f1[1000100][12],f2[1000100][12];//最大值 最小值 
//有些人开f[n][log2(n)]在这里MLE了,实际上开f[n][log2(m)]即可 
//f数组第二维是log2(区间长度),这道题m<=10000 
inline int gint()//快读(其实这题有没有无所谓) 
{
    int s=0,w=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {s=(s<<1)+(s<<3)+(ch^48);ch=getchar();}
    return s*w;
}
int main()
{
    n=gint();m=gint();c=gint();lm=log(m)/log(2);
	for(int i=1;i<=n;i++) a[i]=gint(),f1[i][0]=f2[i][0]=a[i];//初始值 
    for(int i=1;i<=lm;i++) po[i]=po[i-1]<<1;//初始化 
    for(int j=1;j<=lm;j++) for(int i=1;i<=n-po[j]+1;i++)//nlogn处理最大值 
		f1[i][j]=max(f1[i][j-1],f1[i+po[j-1]][j-1]);
    for(int j=1;j<=lm;j++) for(int i=1;i<=n-po[j]+1;i++)//nlogn处理最小值 
		f2[i][j]=min(f2[i][j-1],f2[i+po[j-1]][j-1]);
	for(int i=1;i<=n-m+1;i++)//i<=n-m+1很关键 
		if(max(f1[i][lm],f1[i+m-po[lm]][lm])//[i,i+m-1]的最大值 
		-min(f2[i][lm],f2[i+m-po[lm]][lm])<=c)//[i,i+m-1]的最小值 
			printf("%d\n",i),flag=1;
	if(!flag) puts("NONE");//记得无解输出NONE 
    return 0;
}
```
## ST表毕竟可以O（nlogn）处理 O（1）查询，是一种解决静态区间最值得优秀数据结构
求管理给通过 谢谢

---

## 作者：Hexarhy (赞：8)

此题为适合线段树新手应用的题目。

---------

### 题意简述

给定 $n$ 个数，每次取连续的 $m$ 个数，如果这 $m$ 个数的里的最大值与最小值之差小于等于 $c$，输出第一个数在原数列的位置。如果没有任何一个符合的，输出`NONE`。

### 解题思路

对于本题解，你需要的**前置知识**：线段树入门。这里不再过多讲解线段树的具体细节。

很明显的维护**区间最大最小值**的问题，可以用线段树轻松切掉。

我们只需用线段树分别维护最大值和最小值即可。结构体内开两个变量存值即可。

而且本题并不需要修改序列，大大节省了线段树的码量。

每次维护的时候，我们只需要把模板线段树的加和操作变成`max()`或者`min()`就可以了。

时间复杂度 $O(n\log n)$，只要不是**常数**巨大，可以通过本题。

附注：考场上遇到 $10^6$ 级别的数据，通常情况下正解为**线性做法**。但由于实际运行效率总是更优，导致很多时候都是可以用 $O(n \log n)$ 算法通过的。

### 其他做法

以下列举的做法可以在其它题解找到。运行效率和代码难度各不相同。有兴趣的可以都打一遍。

- 单调队列，时间复杂度 $O(n)$。

- ST 表，时间复杂度 $O(n\log n)$。请注意**空间**。

- 改进后的树状数组，时间复杂度 $O(n\log n)$。

### 实现细节

- 请注意常数优化，并采用较快的读入方式。

- 别忘了输出`NONE`。

- 枚举子序列时注意边界。

### 参考代码

当然存在其他更简短的线段树维护的代码。这里为了方便理解直接上模板。

```cpp
#include<iostream>
#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;

typedef const int cint;
cint MAXN=1e6+5;
int n,m,c;
int a[MAXN];
struct node
{
	int l,r,minv,maxv;//minv保存区间最小值，maxv保存区间最大值
}tree[MAXN<<2];

void build(cint now,cint l,cint r)//模板
{
	tree[now].l=l;tree[now].r=r;
	if(l==r)
	{
		tree[now].minv=tree[now].maxv=a[l];
		return;
	}
	cint mid=(l+r)>>1,lson=now<<1,rson=now<<1|1;
	build(lson,l,mid);
	build(rson,mid+1,r);
    	tree[now].maxv=max(tree[lson].maxv,tree[rson].maxv);//维护最大值
	tree[now].minv=min(tree[lson].minv,tree[rson].minv);//维护最小值
}

int query_min(cint now,cint l,cint r)//查询区间最小值
{
	if(l<=tree[now].l && tree[now].r<=r)
	 return tree[now].minv;
	cint mid=(tree[now].l+tree[now].r)>>1,lson=now<<1,rson=now<<1|1;
	int ans=INT_MAX;
	if(l<=mid)	ans=min(ans,query_min(lson,l,r));
	if(mid<r)	ans=min(ans,query_min(rson,l,r));
	return ans;
}

int query_max(cint now,cint l,cint r)//查询区间最大值
{
	if(l<=tree[now].l && tree[now].r<=r)
	 return tree[now].maxv;
	cint mid=(tree[now].l+tree[now].r)>>1,lson=now<<1,rson=now<<1|1;
	int ans=INT_MIN;
	if(l<=mid)	ans=max(ans,query_max(lson,l,r));
	if(mid<r)	ans=max(ans,query_max(rson,l,r));
	return ans;
}

void input(void)
{
	cin>>n>>m>>c;
	for(int i=1;i<=n;i++)
	 cin>>a[i];
}

void solve(void)
{
	build(1,1,n);
	bool f=false;//标记是否需要输出NONE
	for(int i=1;i+m-1<=n;i++)//注意边界
	 if(query_max(1,i,i+m-1)-query_min(1,i,i+m-1)<=c)
	 {
	 	cout<<i<<endl;
		f=true;
	 }
	if(!f)
	 puts("NONE");
}

int main()
{
	ios_base::sync_with_stdio(false);//优化输入速度
	input();
	solve();
	return 0;
}
```

---

## 作者：lzpclxf (赞：5)

[题目链接](https://www.luogu.org/problem/P4392)
看题解里的线段树跟我某些地方不一样哇

#####其实不用另开一个数组的，会浪费空间！

其实写数据结构的题还是比较的令我开心的~~因为不用脑子~~

怎么判断这题是要写线段树的？
$1$.~~暴力只能拿50分~~

$2$.~~这题是个绿题~~

$3$.看数据范围

众所周知线段树有区间查询的功能，而我们正需要他时间复杂度是$log$的，很多$oier$不愿意码线段树觉得很繁琐，但我个人还是比较喜欢线段树的，觉得很好理解，可能是这类的题做的不少的原因。

######建树过程：
题解里一般都是这样的：
```cpp
 for(int i=1;i<=n;++i) a[i]=read();
 build(1,1,n);
```
其实我们完全可以
```cpp
build(1, 1, n);
```
在线段树的建树过程里的时候边建边输入，减少内存的使用，因为线段树已经要开四倍空间了，所以我们尽量少开内存
相应的建树时应该：
```cpp
	tr[k].l = ll, tr[k].r = rr;
	if(ll == rr) {tr[k].w = read();tr[k].maxn = tr[k].minn = tr[k].w;return;}
	int mid = (ll + rr) >> 1;
	build(lson, ll, mid);
	build(rson, mid + 1, rr);
	tr[k].minn = min(tr[lson].minn, tr[rson].minn);
	tr[k].maxn = max(tr[lson].maxn, tr[rson].maxn);
}
```
其实我的这个结构体里的w变量完全可以省掉，直接就
```cpp
if(ll == rr) {tr[k].maxn = tr[k].minn = read();return;}
```
就好，但是为了便于理解我加上了。

题解里的查询函数也和我的不一样啊，有很多冗杂的语句完全可以删掉的
```cpp
void ask_query(int k, int x, int y) {
	if(tr[k].l >= x && tr[k].r <= y) {minx = min(minx, tr[k].minn);maxx = max(maxx, tr[k].maxn);return;}
	int mid = (tr[k].l + tr[k].r) >> 1;
	if(x <= mid) ask_query(lson, x, y);
	if(y > mid) ask_query(rson, x, y);
}
```
这样写多么的简单又明了啊，在询问函数后边再加语句，看着真心不好受

The Last:
```cpp
#include <cstdio>
#include <iostream>
#define lson k << 1
#define rson k << 1 | 1
using namespace std;
const int N = 2000000;
int n, m, c, minx, maxx;
bool flag;
struct node{
	int l, r, minn, maxn, w;
}tr[N << 2];
int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') w = -1;ch = getchar();}
	while(isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
	return s * w;
}
void build(int k, int ll, int rr) {
	tr[k].l = ll, tr[k].r = rr;
	if(ll == rr) {tr[k].w = read();tr[k].maxn = tr[k].minn = tr[k].w;return;}
	int mid = (ll + rr) >> 1;
	build(lson, ll, mid);
	build(rson, mid + 1, rr);
	tr[k].minn = min(tr[lson].minn, tr[rson].minn);
	tr[k].maxn = max(tr[lson].maxn, tr[rson].maxn);
}
void ask_query(int k, int x, int y) {
	if(tr[k].l >= x && tr[k].r <= y) {minx = min(minx, tr[k].minn);maxx = max(maxx, tr[k].maxn);return;}
	int mid = (tr[k].l + tr[k].r) >> 1;
	if(x <= mid) ask_query(lson, x, y);
	if(y > mid) ask_query(rson, x, y);
}
int main() {
	n = read(), m = read(), c = read();
	build(1, 1, n);
	for(int i = 1; i + m - 1 <= n; i++) {
		minx = 0x3f3f3f3f, maxx = -0x3f3f3f3f;
		ask_query(1, i, i + m - 1);
		if(maxx - minx <= c)
			printf("%d\n", i), flag = 1;	
	}
	if(!flag) printf("NONE\n");
	return 0;
}
```
谢谢收看，住身体健康！




---

## 作者：RedreamMer (赞：5)

[题目](https://www.luogu.com.cn/problem/P4392)

好多人用线段树和树状数组写的这道题，貌似正解也是,~~而蒟蒻我却不会~~

### 思路：

看到**最大值**和**最小值**又看到**m个采样的序列**，这道题应该可以用 $ST$ 表做吧，因为 $ST$ 表的特点就是存储和查询区间最大值或最小值

不会 $ST$ 表的来这里[模板ST表](https://www.luogu.com.cn/problem/P3865)

时间复杂度 $O(n*log_2n)$ 刚好可以险过这道题

空间复杂度应该也可以卡过去，只要合理分配数组空间

### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1001000;
int a,b,c,mx[N][16],mn[N][16];//数组可以这么开
bool q;
inline int r() {//快读 
	char ch=getchar();
	int f1=0,f2=1;
	while(ch<'0'||ch>'9') {
		if(ch=='-') f2=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') f1=(f1<<3)+(f1<<1)+(ch^48),ch=getchar();
	return f1*f2;
}
inline int fx(int l,int r) {//查询区间最大值 
	int p=log2(r-l+1);
	return max(mx[l][p],mx[r-(1<<p)+1][p]);
}
inline int fm(int l,int r) {//查询区间最小值 
	int p=log2(r-l+1);
	return min(mn[l][p],mn[r-(1<<p)+1][p]);
}
int main() {
	a=r();
	b=r();
	c=r();
	for(int i=1; i<=a; i++)
		mx[i][0]=mn[i][0]=r();
	for(int l=1; l<=15; l++)//维护两个ST表 
		for(int i=1; i<=a; i++) {
			mx[i][l]=max(mx[i][l-1],mx[i+(1<<(l-1))][l-1]);
			mn[i][l]=min(mn[i][l-1],mn[i+(1<<(l-1))][l-1]);
		}
	for(int i=1; i<=a-b+1; i++) {//O(N)扫一遍进行判断 
		int Mx=fx(i,i+b-1),Mn=fm(i,i+b-1);
		if(Mx-Mn<=c) {
			printf("%d\n",i);
			q=1;
		}
	}
	if(!q)
	puts("NONE");//一定不要忘了NONE要输出 
	return 0;
}
```

#### [$\color{blue}\text{My Blog}$](https://www.luogu.com.cn/blog/184549/)

---

## 作者：Schwarzkopf_Henkal (赞：4)

求一段静态区间内的最大值减最小值……

这不就是ST表**裸题**吗？？？

然而事情并没有那么简单，ST表怎么调最后一个点就是MLE，实在是F*\*k。

慢着，我们查询的区间长度为m，也就是说根本用不到查询长度为n的区间，那么我们ST表的第二维还需要开到$log2(n)$那么大么？答案是否定的，第二维只需要开到$log2(m)$规模，其他就是一个ST表板子啦。

代码贴一下。
```cpp
#include<cstdio>
#include<cmath>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;
int n,m,c,a[1000005],stg[1000005][12],stl[1000005][12];
bool flag=1;
int diff(int l,int r){
    int k=log2(r-l+1);//找到不大于区间长度的最小2^k
    return max(stg[l][k],stg[r-(1<<k)+1][k])-min(stl[l][k],stl[r-(1<<k)+1][k]);
}
int main(){
    scanf("%d%d%d",&n,&m,&c);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        stg[i][0]=stl[i][0]=a[i];//初始化
    }
    for(int j=1;1<<j<=m;j++)
        for(int i=1;i-1+(1<<j)<=n;i++){
            stg[i][j]=max(stg[i][j-1],stg[i+(1<<j-1)][j-1]);
            stl[i][j]=min(stl[i][j-1],stl[i+(1<<j-1)][j-1]);
        }//递推导出ST表，复杂度十分优秀，初始化O(nlogn)，查询O(1)。
    for(int i=1;i+m-1<=n;i++)//(在这题里面复杂度是O(nlogm))
        if(diff(i,i+m-1)<=c){
            flag=0;//推倒旗子
            printf("%d\n",i);
        }
    if(flag)
        printf("NONE");
}
```

---

## 作者：Shikita (赞：4)

# 好吧今天这题改了三种算法终于过掉了，于是来水个题解

刚开始用暴力会莫名WA和TLE，于是打了个线段树。

线段树也莫名WA加OLE？？

继续打一个单调队列，还是WA加OLE

好吧继续回去修改线段树

## 代码
```
#include<iostream>
using namespace std;
const int INF=2147483647;
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9'){if(c=='-')flag=1;   c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+c-'0';c=getchar();}
    return flag?-x:x;
}
int a[1000005];
int n,m,c;
struct node{int l,r,maxn,minn;}tree[4000005];
void build(int p,int l,int r)
{
    tree[p].l=l,tree[p].r=r;
    if(l==r){tree[p].maxn=a[l];tree[p].minn=a[l];return;}
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    tree[p].maxn=max(tree[p<<1].maxn,tree[p<<1|1].maxn);
    tree[p].minn=min(tree[p<<1].minn,tree[p<<1|1].minn);
}
bool ask(int p,int l,int r)
{
    //if(tree[p].l==tree[p].r) return 0;
    if(l<=tree[p].l&&r>=tree[p].r) 
    {return (tree[p].maxn-tree[p].minn)>c?0:1;}
    int mid=(tree[p].l+tree[p].r)>>1;
    if(l<=mid) if(ask(p<<1,l,r)) return 1;
    if(r>mid) if(ask(p<<1|1,l,r)) return 1;
    return 0;
}
int main()
{
    n=read(),m=read(),c=read();
    for(int i=1;i<=n;++i) a[i]=read();
    build(1,1,n);
    bool flag=1;
    for(int i=1;i+m-1<=n;++i)
    {
        //cout<<i<<" "<<i+m-1<<endl;
        //cout<<ask(1,i,i+m-1)<<" "<<123123<<endl;
        if(ask(1,i,i+m-1))
        {
            cout<<i<<endl;
            flag=1;
        }
    }
    if(!flag) cout<<"NONE"<<endl;
    return 0;
}
```
结果莫名WA加OLE0分

后来自己模拟一遍，发现


![](https://i.loli.net/2018/08/22/5b7cca2b56d17.png)

（手动画图，丑，对强迫症表示抱歉）

如果这么做的话

主要看ask函数
```
bool ask(int p,int l,int r)
{
    //if(tree[p].l==tree[p].r) return 0;
    if(l<=tree[p].l&&r>=tree[p].r) 
    {return (tree[p].maxn-tree[p].minn)>c?0:1;}
    int mid=(tree[p].l+tree[p].r)>>1;
    if(l<=mid) if(ask(p<<1,l,r)) return 1;
    if(r>mid) if(ask(p<<1|1,l,r)) return 1;
    return 0;
}
```
的确，如果两个数（假设为2,3）
那么各自为（2,2）（3,3）时必定返回1

因为无论如何结果都是0

又因为线段树的搜索性质和蒟蒻我的垃圾代码，导致只要搜到叶子节点就会返回1，所以错误

### 正解代码
```
#include<iostream>
using namespace std;
const int INF=2147483647;
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9'){if(c=='-')flag=1;   c=getchar();}
    while(c>='0'&&c<='9'){x=(x+(x<<2)<<1)+c-'0';c=getchar();}
    return flag?-x:x;
}
int a[1000005];
int n,m,c;
struct node{int l,r,maxn,minn;}tree[4000005];
struct nod{int maxn,minn;};
void build(int p,int l,int r)
{
    tree[p].l=l,tree[p].r=r;
    if(l==r){tree[p].maxn=a[l];tree[p].minn=a[l];return;}
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    tree[p].maxn=max(tree[p<<1].maxn,tree[p<<1|1].maxn);
    tree[p].minn=min(tree[p<<1].minn,tree[p<<1|1].minn);
}
nod ask(int p,int l,int r)
{
    if(l<=tree[p].l&&r>=tree[p].r)
    {nod x;x.maxn=tree[p].maxn,x.minn=tree[p].minn;return x;}
    int mid=(tree[p].l+tree[p].r)>>1;
    nod x;
    int maxn=-INF,minn=INF;
    if(l<=mid) x=ask(p<<1,l,r),maxn=max(maxn,x.maxn),minn=min(minn,x.minn);
    if(r>mid) x=ask(p<<1|1,l,r),maxn=max(maxn,x.maxn),minn=min(minn,x.minn);
    x.maxn=maxn,x.minn=minn;
    return x;
}
int main()
{
    n=read(),m=read(),c=read();
    for(int i=1;i<=n;++i) a[i]=read();
    build(1,1,n);
    bool flag=0;
    for(int i=1;i+m-1<=n;++i)
    {
        nod x=ask(1,i,i+m-1);
        if(x.maxn-x.minn<=c)
        {
            printf("%d\n",i);
            flag=1;
        }
    }
    if(!flag) cout<<"NONE"<<endl;
    return 0;
}
```
由于蒟蒻我代码过于丑陋，在下面开始正规讲解

build函数就是基本的线段树，所以就看看吧

主函数大概也都能看得懂，我主要讲一下我的ask函数

首先，如果搜索到一段完全覆盖的区间，返回极值

如果与左边区间有交集，那么搜索左边区间

同理，搜索右边区间

最后返回，让主函数自己进行判断

这题虽然不难但是对于蒟蒻我来说还是非常有趣的

希望大家多多指教！

---

## 作者：寒鸽儿 (赞：3)

$f(x) = min\{a[k]\}, k \in [x-m+1, x]$  
这显然是一个可以用优先队列优化的递推(dp)。  
若$i \leqslant j \&\& a[i] \geqslant a[i] $显然是无效的,优势只有数值更小或者下标更靠后(因为递推左边界在向右缩小)。  
所以用单调队列维护即可。  
$max$同理。  
复杂度$O(n)$
```cpp
#include <cstdio>
#include <queue>

using namespace std;

const int N = 1234567;
struct node{
	int x, v;
	node() {}
	node(int X, int V) :x(X), v(V) {}
};
deque<node> qmin, qmax;

int main() {
	int n, m, c, tmp, flg = 1;
	scanf("%d %d %d", &n, &m, &c);
	for(int i = 1; i <= m-1; ++i) {
		scanf("%d", &tmp);
		while(!qmin.empty()) {
			if(qmin.back().v >= tmp) qmin.pop_back();
			else break;
		}
		qmin.push_back(node(i, tmp));
		while(!qmax.empty()) {
			if(qmax.back().v <= tmp) qmax.pop_back();
			else break;
		}
		qmax.push_back(node(i, tmp));
	}
	for(int i = m; i <= n; ++i) {
		scanf("%d", &tmp);
		while(!qmin.empty()) {
			if(qmin.back().v >= tmp) qmin.pop_back();
			else break;
		}
		qmin.push_back(node(i, tmp));
		while(!qmax.empty()) {
			if(qmax.back().v <= tmp) qmax.pop_back();
			else break;
		}
		qmax.push_back(node(i, tmp)); 
		while(qmin.front().x < i-m+1) qmin.pop_front();
		while(qmax.front().x < i-m+1) qmax.pop_front();
		if(qmax.front().v - qmin.front().v <= c) {
			printf("%d\n", i-m+1);
			flg = 0;
		}
	}
	if(flg) {
		printf("NONE\n");
	}
	return 0;
}
```

---

## 作者：木木！ (赞：2)

先考虑ST表$\Theta(nlogn+n)$，然后最后一个点完美MLE

思路是建表，然后枚举起点$\Theta(1)$求最大值。

附MLE代码

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

int ai[1000005];
int maxi[21][1000005];
int mini[21][1000005];

int main()
{
    int n,m,c;
    scanf("%d%d%d",&n,&m,&c);
    for(int i=1; i<=n; ++i)
    {
        scanf("%d",ai+i);
    }
    
    int logn = 31-__builtin_clz(n);
    for(int i=1; i<=n; ++i)
    {
        maxi[0][i] = mini[0][i] = ai[i];
    }
    for(int i=1; i<=logn; ++i)
    {
        for(int j=1; j<=n-(1<<i)+1; ++j)
        {
            maxi[i][j] = max(maxi[i-1][j],maxi[i-1][j+(1<<(i-1))]);
            mini[i][j] = min(mini[i-1][j],mini[i-1][j+(1<<(i-1))]);
        }
    }
    
    int ansn = 0;
    int logm = 31-__builtin_clz(m);
    for(int i=1; i<=n-m+1; ++i)
    {
        if(max(maxi[logm][i],maxi[logm][i+m-(1<<logm)]) - min(mini[logm][i],mini[logm][i+m-(1<<logm)]) <= c)
        {
            printf("%d\n",i);
            ++ansn;
        }
    }
    
    if(!ansn)
    {
        printf("NONE");
    }
}
```

既然ST表MLE了，就考虑空间消耗$\Theta(n)$的单调队列。

单调队列讲解见[P1886滑动窗口](https://www.luogu.org/problemnew/show/P1886)。（顺便捞个双倍经验）

附AC代码

```cpp
#include <cstdio>
using namespace std;

int ai[1000005]; 
int maxq[1000005];
int minq[1000005];

int main()
{
	int n,m,c;
	scanf("%d%d%d",&n,&m,&c);
	for(int i=1; i<=n; ++i)
	{
		scanf("%d",ai+i);
	}
	
	int ahead = 0;
	int atill = 1;
	int ihead = 0;
	int itill = 1;
	
	int ansn = 0;
	for(int i=1; i<=n; ++i)
	{
		while(ahead>=atill && ai[maxq[ahead]]<=ai[i])
		{
			--ahead;
		}
		++ahead;
		maxq[ahead] = i;
		
		while(ihead>=itill && ai[minq[ihead]]>=ai[i])
		{
			--ihead;
		}
		++ihead;
		minq[ihead] = i;
		
		if(maxq[atill] <= i-m)
		{
			++atill;
		}
		if(minq[itill] <= i-m)
		{
			++itill;
		}
		
		if(i >= m)
		{
			if(ai[maxq[atill]]-ai[minq[itill]] <= c)
			{
				printf("%d\n",i-m+1);
				++ansn;
			}
		}
	}
	
	if(!ansn)
	{
		printf("NONE");
	}
}
```

---

## 作者：Jameswood (赞：2)

[原题链接](https://www.luogu.org/problemnew/show/P4392)

------------

### 题目大意：

有一个长度为 n 的数列 a 。求在长度为 m 的连续子数列中，有多少个的最大值与最小值的差小于等于 c。

### 暴力做法

#### （以下做法由 [U19533 KagurazakaKano](https://www.luogu.org/space/show?uid=19533) 提供）

```cpp
#include <cstdio>
#include <set> 
#include <queue>

const int MAXN = 1000005;

using namespace std;

int n,m,c,a[1000005];

int maxn = -10005, minn = 10005;

set<int> q;

int main(){
    scanf("%d%d%d",&n,&m,&c);
    for(int i = 1; i <= n; i++){
        scanf("%d",&a[i]);
    }
    for(int i = 1; i <= n - m + 1; i++){
        for(int j = i; j <= i + m - 1; j++){
            maxn = max(maxn,a[j]);
            minn = min(minn,a[j]);
        }
        if(maxn - minn <= c){
            printf("%d\n",i);
        }
        maxn = -10005;
        minn = 10005;
    }
    return 0;
}
```

实测 40 分，加 O2 优化分数不变，RE 变 TLE。

[测试详情](https://www.luogu.org/record/show?rid=9283148)

------------


### 满分做法

线段树求最大最小值。本题中的声音在记录后没有改变，所以只需进行建树过程中的赋值（少写一个函数）。

本处使用 Segtree 中的 minn 和 maxn 记录区间内的最小值。

容易出错的地方是 Query 的返回值不能直接赋值，应分别用 min 和 max 判断。还有就是如果从头到尾一直没有复合条件的数列则输出 NONE （程序中使用 con 判断）。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int SIZE=1000005;
struct Segtree{
    int l,r,maxn,minn;
}t[SIZE<<2];
int a[SIZE],n,m,c,Queryminn,Querymaxn,ans;
bool con=false;//false 代表没有符合条件
void PushUp(int id){//上推，将此区间的最大和最小值赋为下两个区域的。
    t[id].maxn=max(t[id<<1].maxn,t[id<<1|1].maxn);
    t[id].minn=min(t[id<<1].minn,t[id<<1|1].minn);
}
void Build(int id,int l,int r){//建树
    t[id].l=l;t[id].r=r;
    if(l==r){
        t[id].maxn=a[l];t[id].minn=a[l];//单个值时 maxn 和 minn 相等
    }
    else{
        int mid=(t[id].l+t[id].r)>>1;
        Build(id<<1,l,mid);
        Build(id<<1|1,mid+1,r);
        PushUp(id);//上推写在最后
    }
}
void Query(int id,int l,int r){
    if(t[id].l==l&&t[id].r==r){
    	//注意不能直接赋值
        Queryminn=min(Queryminn,t[id].minn);
        Querymaxn=max(Querymaxn,t[id].maxn);
    }
    else{
        int mid=(t[id].l+t[id].r)>>1;
        if(r<=mid) Query(id<<1,l,r);
        else{
            if(l>mid) Query(id<<1|1,l,r);
            else{
                Query(id<<1,l,mid);
                Query(id<<1|1,mid+1,r); 
            }
        }
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&c);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    Build(1,1,n);
    for(int i=1;i<=n-m+1;i++){
    	//Query的返回值需要赋初值
        Querymaxn=-1<<30;Queryminn=1<<30;
        Query(1,i,i+m-1);
        ans=Querymaxn-Queryminn;
        if(ans<=c){
            con=true;
            printf("%d\n",i);
        }
    }
    if(con==false) printf("NONE\n");
    return 0;
} 
```

[测试详情](https://www.luogu.org/record/show?rid=9284868)

当然啦，单调队列也能做QAQ


---

## 作者：谭之荔 (赞：0)

#### 这道题就是求区间max,区间min，然后和c比较就好
一开始用的**RMQ**，不会RMQ的阔以看一下[这个博客](https://blog.csdn.net/qq_41311604/article/details/79900893)（不是我的）
RMQ代码如下
```
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
#define rep(x,a,b) for(int x=(a);x<=(b);x++)
#define per(x,a,b) for(int x=(a);x>=(b);x--)
#define mem(x) memset(x,0,sizeof(x))

const int A=1e6+1;
int N,M,C,f;
int rl[19][A],rs[19][A];

int lg(int x)
{
	int p=0;
	while(x)
		p++,x>>=1;
	return p;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>N>>M>>C;
	rep(i,1,N) cin>>rs[0][i],rl[0][i]=rs[0][i];
	int maxl=lg(N)-1;
	rep(l,1,maxl)
		rep(i,1,N-(1<<l)+1)
		{
			rl[l][i]=max(rl[l-1][i],rl[l-1][i+(1<<(l-1))]);
			rs[l][i]=min(rs[l-1][i],rs[l-1][i+(1<<(l-1))]);
		}
	rep(i,1,N-M+1)
	{
		int l=lg(M)-1;
		int ansl=max(rl[l][i],rl[l][(i+M-1)-(1<<l)+1]);
		int anss=min(rs[l][i],rs[l][(i+M-1)-(1<<l)+1]);
		if((ansl-anss)<=C) f=1,cout<<i<<endl; 
	}
	if(!f) cout<<"NONE";
	return 0;
}

```

然后无论怎么改，第十个点都会MLE，改了好久后不得不放弃
然后选择了**线段树**！

首先是建树
```
void bld(LL nw,LL l,LL r)
{
	ll[nw]=l,rr[nw]=r;
	if(l==r) {mx[nw]=mn[nw]=a[l];return;}
	LL md=(l+r)>>1;
	bld(nw<<1,l,md);
	bld(nw<<1|1,md+1,r);
	upd(nw);
}
```
mx,mn分别维护区间最大最小值

update 即小区间max min合并入大区间
```
void upd(LL nw)
{
	mx[nw]=max(mx[nw<<1],mx[nw<<1|1]);
	mn[nw]=min(mn[nw<<1],mn[nw<<1|1]);
}
```

查询，如果查询的范围在nw范围内，就需要更新最大最小值，与区间求和相似
```
void quy(LL nw,LL x,LL y)
{
	if(ll[nw]>=x&&rr[nw]<=y)
	{
		maxx=max(maxx,mx[nw]);
		minn=min(minn,mn[nw]);
		return;
	}
	LL md=(ll[nw]+rr[nw])>>1;
	if(x<=md) quy(nw<<1,x,y);
	if(y>md) quy(nw<<1|1,x,y);
}
```

最后完整AC代码
```
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
#define rep(x,a,b) for(LL x=(a);x<=(b);x++)
#define per(x,a,b) for(LL x=(a);x>=(b);x--)
#define mem(x) memset(x,0,sizeof(x))

const int A=5e6+10;
LL N,M,C,f;
LL mx[A],mn[A],ll[A],rr[A]; 
LL a[A];
LL maxx,minn;

void upd(LL nw)
{
	mx[nw]=max(mx[nw<<1],mx[nw<<1|1]);
	mn[nw]=min(mn[nw<<1],mn[nw<<1|1]);
}

void bld(LL nw,LL l,LL r)
{
	ll[nw]=l,rr[nw]=r;
	if(l==r) {mx[nw]=mn[nw]=a[l];return;}
	LL md=(l+r)>>1;
	bld(nw<<1,l,md);
	bld(nw<<1|1,md+1,r);
	upd(nw);
}

void quy(LL nw,LL x,LL y)
{
	if(ll[nw]>=x&&rr[nw]<=y)
	{
		maxx=max(maxx,mx[nw]);
		minn=min(minn,mn[nw]);
		return;
	}
	LL md=(ll[nw]+rr[nw])>>1;
	if(x<=md) quy(nw<<1,x,y);
	if(y>md) quy(nw<<1|1,x,y);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); 
	cin>>N>>M>>C;
	rep(i,1,N) cin>>a[i]; 
	bld(1,1,N);
	rep(i,1,N-M+1)
	{
		maxx=0;
		minn=0x7fffffff;
		quy(1,i,i+M-1);
		if((maxx-minn)<=C) f=1,cout<<i<<endl;
	}
	if(!f) cout<<"NONE";
	return 0;
}

```
### 千万不要忘了maxx minn初值和NONE输出


---

## 作者：abandentsky (赞：0)

思路：也就是在一个长度为m的区间内找最大值减去最小值要小于等于c。那么直接使用RMQ处理就完事儿了，不过应该是数据太水。本来数组要开maxn[1000000][22]才行，因为n最大有1000000，所以2^21大约为1000000，但是这样就爆内存了，只能得到90。头铁把22改成了15.居然过了。RMQ模板。

```c
#include<stdio.h>
#include<math.h>
#include<iostream>
#include<algorithm>
#define MAXN  1000005
using namespace std;

int maxn[MAXN][25];
int minn[MAXN][25];
int n,m,c;

void RMQ_init()
{
    for(int i=1;(1<<i)<=n;i++)
    {
        for(int j=0;(j+(1<<i))-1<n;j++)
        {
            maxn[j][i]=max(maxn[j][i-1],maxn[j+(1<<(i-1))][i-1]);
            minn[j][i]=min(minn[j][i-1],minn[j+(1<<(i-1))][i-1]);
        }
    }
}

int RMQ_query(int L,int R,int d)
{
    int log=0;
    while((1<<(log+1))<=(R-L+1))
          log++;
    if(d==1)
        return max(maxn[L][log],maxn[R-(1<<log)+1][log]);
    return min(minn[L][log],minn[R-(1<<log)+1][log]);
}

int main()
{
    scanf("%d %d %d",&n,&m,&c);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&maxn[i][0]);
        minn[i][0]=maxn[i][0];
    }
    RMQ_init();
    bool ok=true;
    for(int i=0;i+m-1<n;i++)
    {
        int L=i;
        int R=i+m-1;
        if(RMQ_query(L,R,1)-RMQ_query(L,R,0)==c)
        {
            printf("%d\n",i+1);
            ok=false;
        }
    }
    if(ok)
        printf("NONE\n");
    return 0;
}

```


---

## 作者：Erusel (赞：0)

写完翻翻题解发现一个ST表 MLE的跑去写单调队列了

其实ST表是可以花式AC的

---

先来简单介绍一下ST表

ST表是用来解决区间最值问题的

我们把区间最值想成区间DP

考虑最大值

用$dp[i][j]$表示区间$[i,j]$的最大值。

显而易见，有$dp[i][j]=max(dp[i][j-1],a[i])$(时间复杂度$O(n^2)$)

我们采用倍增思想，用$dp[i][j]$表示以$i$为起点，长度为$2^j$的区间最大值，

求解时分成两个区间$[i,i+2^j-1-1],[i+2^j-1,i+2^j+1]$

有$dp[i][j]=max(dp[i][j-1],dp[i+2^j-1][j-1])$

由于长度为$2^j$，时间复杂度为$O(nlogn)$

以上是预处理部分。

实际查询时，我们需要求解一个任意的区间，

而上面的预处理只能求出长度为$2^j$的区间最大值。

我们利用一下一个小性质：

最值是可以由相交性的

我们的目标就是要把待查询的区间，转化成两个我们已经求出的区间。

找出最大的$2^k<=len$的$k$，其中$len=r-l+1$为区间长度，

取区间$[l,l+2k-1],[r-2k+1,r]$为两个小区间，显然满足且能找到，时间复杂度为$O(1)$

---

本题要求对于每个长为$m$的序列，找出这些序列中最大值和最小值的差值不超过$c$

考虑到ST表的空间复杂度有点高，高达$O(nlogn)$

于是在此题中会MLE

接下来介绍花式AC做法：

我们故意把空间开小

开到$N*15$的空间

还是一样的做法

暴力搜索就通过了

时间复杂度为$O(nlogn)(n*15)$

code:

```
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>

#define rd(x) x=read() 

#define N 1000001
#define M 16

using namespace std;

int n,m,c;
int a[N][M],b[N][M];

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

inline int query(int l,int r,int f)
{
	int k=log2(r-l+1);
	if(f)return max(a[l][k],a[r-(1<<k)+1][k]);
	else return min(b[l][k],b[r-(1<<k)+1][k]);
}

int main()
{
	rd(n),rd(m),rd(c);
	for(int i=1;i<=n;i++)rd(a[i][0]),b[i][0]=a[i][0];
	for(int j=1;j<=15;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            a[i][j]=max(a[i][j-1],a[i+(1<<(j-1))][j-1]),
            b[i][j]=min(b[i][j-1],b[i+(1<<(j-1))][j-1]);
    bool ok=0;
	for(int i=1;i<=n;i++)
	{
		int j=i+m-1;
		if(j>n)break;
		if(query(i,j,1)-query(i,j,0)<=c)
			printf("%d\n",i),ok=1;
	}
	if(!ok)cout<<"NONE"<<endl;
	
	return 0;
}
```

另外部分内容摘自[Link](https://www.cnblogs.com/Robin20050901/p/10311438.html)

博主是同一个人

---

总结：乱搞是可以AC的

---

## 作者：千反田 (赞：0)

~~自从本蒟蒻学了线段树之后就来开心地水各种模板题~~

## 题目大意
 给定一个序列，求在每一个长度为m的序列中最大值和最小值的差不超过c。如果有，输出这个序列的起始位置。
 
 以样例为例子，则有：
 
 ```cpp
m=2 c=0   
        0 1 1 2 3 2 2
case 1:[0,1] 1-0<=0 不成立
case 2:  [1,1] 1-1<=0 成立,输出这个序列的起始位置2
case 3:    [1,2] 2-1<=0 不成立
case 4:      [2,3] 3-2<=0 不成立
case 5:        [3,2] 3-2<=0 不成立
case 6:          [2,2] 2=2<=0 成立,输出这个序列的起始位置6
```
然后就是一道线段树~~模板~~题了

23333333

```cpp
#include<bits/stdc++.h>
#define N 1000005
typedef long long ll;
struct Segment_Tree{
    ll l,r,val,w;
}tree[N<<2];
ll n,m,c,input[N];
bool flag;
inline int read(){
    ll x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')
         f=-f;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void build(ll index,ll l,ll r){
    tree[index].l=l;
    tree[index].r=r;
    if(l==r){
        tree[index].val=tree[index].w=input[l];
        return;
    }
    ll mid=l+r>>1;
    build(index<<1,l,mid);
    build(index<<1|1,mid+1,r);
    tree[index].val=std::min(tree[index<<1].val,tree[index<<1|1].val);
    tree[index].w=std::max(tree[index<<1].w,tree[index<<1|1].w);
}
ll ask1(ll index,ll l,ll r){
    if(l<=tree[index].l&&r>=tree[index].r)
     return tree[index].val;
    ll mid=tree[index].l+tree[index].r>>1,ans=INT_MAX;
    if(l<=mid)
     ans=std::min(ans,ask1(index<<1,l,r));
    if(r>mid)
     ans=std::min(ans,ask1(index<<1|1,l,r));
    return ans;
}
ll ask2(ll index,ll l,ll r){
    if(l<=tree[index].l&&r>=tree[index].r)
     return tree[index].w;
    ll mid=tree[index].l+tree[index].r>>1,ans=-INT_MAX;
    if(l<=mid)
     ans=std::max(ans,ask2(index<<1,l,r));
    if(r>mid)
     ans=std::max(ans,ask2(index<<1|1,l,r));
    return ans;
}
int main(){
    n=read(),m=read(),c=read();
    for(register int i=1;i<=n;++i)
     input[i]=read();
    build(1,1,n);
    for(register int i=1;i<=n-m+1;++i){
        ll a=ask1(1,i,i+m-1);
        ll b=ask2(1,i,i+m-1);
        if(b-a<=c){
            printf("%d\n",i);
            flag=true;
        }
    }
    if(!flag)
     puts("NONE");
    return 0;
}
```
解释一下代码

build就是普通的建树外加维护区间最小值

ask1返回区间最小值

ask2返回区间最大值

在main函数里枚举判断有多少个区间满足条件

然后这道题就水过了2333333

---

## 作者：Hiraeth (赞：0)

区间最大和最小查询

本题还是静态区间

很明显一个ST表嘛

可惜只有90分…

~~我只会卡常啊 没有教我怎么卡MLE…~~

ST表是个很优秀的算法！

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,m,c,flag,a[1000005],f1[1000005][32],f2[1000005][32];
//len=r-l+1 
void ST_prework(){
	int t=log(n)/log(2);
	for (int j=1;j<=t;j++)
		for (int i=1;i<=n-(1<<j)+1;i++){
		f1[i][j]=max(f1[i][j-1],f1[i+(1<<(j-1))][j-1]);
		f2[i][j]=min(f2[i][j-1],f2[i+(1<<(j-1))][j-1]);  		
	}
} 
int ST_query(int l,int r){
	int k=log(r-l+1)/log(2);
	return max(f1[l][k],f1[r-(1<<k)+1][k])-min(f2[l][k],f2[r-(1<<k)+1][k]);//左端点覆盖区间 右端点覆盖区间 
}
int main(){
	scanf("%d%d%d",&n,&m,&c);
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		f1[i][0]=a[i];
		f2[i][0]=a[i];
	}
	ST_prework();
	for (int i=1;i<=n-m+1;i++)
		if (ST_query(i,i+m-1)<=c) {
			flag++;
			printf("%d\n",i);
		}
	if (!flag) printf("NONE");
	return 0;
}
```


---

