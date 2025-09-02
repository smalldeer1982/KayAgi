# [BalticOI 2011] Plagiarism (Day2)

## 题目描述

世界编程竞赛的参与者向评分系统提交了 $N$ 个解决方案文件 $f_1 ,...,f_N$。在接受结果为最终结果之前，评审团希望排除任何抄袭的可能性。他们有一个程序，可以将两个文件进行比较，以决定它们是否过于相似。然而，文件的数量相当大，比较所有对将花费太多时间。另一方面，许多对可以基于文件大小差异过大而快速排除。更确切地说，评审团决定完全跳过比较每一对，其中较小文件的大小小于较大文件大小的 90%。因此，比较程序只需检查那些不同的文件对 $(f_i, f_j)$，其中 $i 
\ne j, size(f_i) \le size(f_j)$ 且 $size(f_i) \ge 0.9 \times size(f_j)$。编写一个程序来计算需要检查的文件对的数量。

## 说明/提示

对于 $50\%$ 的数据，$1 \le N \le 2000$。对于所有数据，$1 \le N \le 10^5,1 \le f_i \le 10^8$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
2 1```

### 输出

```
0```

## 样例 #2

### 输入

```
5
1 1 1 1 1```

### 输出

```
10```

# 题解

## 作者：TinyKiecoo (赞：14)

我们首先想到的朴素算法就是根据$size$从大到小排序，枚举$f[i]$与$f[j]$，判断是否需要比较，时间复杂度约$O(n^2)$。

代码：
```cpp
#include"cstdio"
#include"algorithm"
int n,s,f[100001];
bool cmp(int x,int y){
    return x>y;
}
int main(){
    scanf("%d",&n);
    for(register int i=1;i<=n;i++)scanf("%d",&f[i]);
    std::sort(f+1,f+1+n,cmp);
    for(register int i=1;i<=n;i++){
        for(register int j=i+1;j<=n;j++){
            if(f[j]>=0.9*f[i])s++;
        }
    }
    printf("%d",s);
}
```

但是纯暴力代码只能得$50$分，我们可以想办法优化。↓

我们把$size$从大到小排序后，则$f[x]>f[x+1]$。于是，若$f[i]×0.9>f[j]$，则$f[i]×0.9>f[j+1]$。换句话说，若$f[j]$不需比较，则$f[j]$之后的数也一定不需比较，所以我们可以先进行一个小优化，在第二层循环中，若$f[j]$不需要比较，则跳出当前循环，进行下一个循环。这样我们可以苟到$60$分。

代码：
```cpp
#include"cstdio"
#include"algorithm"
int n,s,f[100001];
bool cmp(int x,int y){
    return x>y;
}
int main(){
    scanf("%d",&n);
    for(register int i=1;i<=n;i++)scanf("%d",&f[i]);
    std::sort(f+1,f+1+n,cmp);
    for(register int i=1;i<=n;i++){
        for(register int j=i+1;j<=n;j++){
            if(f[j]>=0.9*f[i])s++;
            else break;
        }
    }
    printf("%d",s);
}
```
我们可以想办法再次优化。↓

还是观察已从大到小排好序的$size$，若$f[i]×0.9<=f[j]$，则$f[i+1]×0.9<=f[j]$，也就是若$f[i]$需要与$f[j]$比较，则$f[i+1]$也一定必须与$f[j]$比较，那么我们可以记录一下位置$l$，表示上一次判断到哪里了，下一次直接从$l+1$开始判断，并且加上$l$与$i$相差的数量，时间复杂度$O(2n)$。

代码：
```cpp
#include"cstdio"
#include"algorithm"
using namespace std;
int n;
long long s,l=1,f[100001];
inline bool cmp(long long x,long long y) {
    return x>y;
}
int main() {
    scanf("%d",&n);
    for(register int i=1; i<=n; i++)scanf("%lld",&f[i]);
    sort(f+1,f+1+n,cmp);
    for(register int i=1; i<=n; i++) {
        for(register int j=l+1; j<=n; j++){
            if(f[i]*9<=f[j]*10)l=j;
            else break;
        }
        s+=l-i;
    }
    printf("%lld",s);
}
```
$\mathbf{\color{red}\text{我只是蒟蒻，讲得不太好，大佬勿喷，谢谢}}$

---

## 作者：oimaster (赞：5)

洛谷传送门：<https://www.luogu.com.cn/problem/P4670>

LOJ 传送门：<https://loj.ac/p/2635>

博客传送门：<https://oi-master.gitee.io/2020/12/22/BalticOI-2011-Day2-Plagiarism-题解/>

这题绝对是道水题。跟我一样用 `STL` 的同学，请喊：

> STL！STL！STL 强！

我们发现 $n$ 只有 $10^5$ 大，意味着我们可以使用 $\operatorname{O}\left(n\log n\right)$ 的方法解决此题。

首先，我们先排序此数列。可以使用 `STL` 的 `sort()` 函数排序。

然后，我们发现对于每个数，需要对比的程序在排过序的数列中有单调性：当 $a_i$ 不用比较时，那么 $a_{i-1}$ 也不用比较。

那么可以算出每个数字 $90\%$ 是多少，然后用 `STL` 的 `lower_bound()` 函数二分。

所以需要您手写的除了输入输出就没什么了。

```c++
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define int long long
signed main(){
	int n;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;++i)
		cin>>a[i];
	sort(a+1,a+n+1);
	int sum=0;
	for(int i=1;i<=n;++i){
		int now=ceil(a[i]*90.0/100);
		int j=lower_bound(a+1,a+i,now)-a;
		sum+=i-j;
	}
	cout<<sum<<endl;
}
```

---

## 作者：Kevin_Wa (赞：4)

使用朴素的O(n^2)算法显然会超时，需要优化

由于本题需要size(fi)≤size(fj)，所以可以考虑先将size从小到大排序

我们可以发现（size已经事先从小到大排序），

****若(i<j<k&&size(fi)≤0.9size(fj))****

****则size(fi)≤0.9size(fk)****

****若(i<j<k&&size(fi)≥0.9size(fk))****

****则size(fj)≥0.9size(fk)****

于是，若size(fx)无法匹配，则size(fx+1)同样无法匹配，可以退出循环。同时，当我们匹配第(i+1)时,只需要从第i个无法匹配的位置开始就可以了，时间复杂度便降到了O(n)。

需要注意的是本题的数据范围，一定要开long long   
```cpp
#include<bits/stdc++.h> 
using namespace std;
int main()
{
	long long n,ans=0;  //要开long long
	int a[100001];
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	int w=2; //w表示前一个数无法匹配的位置
             //初值赋为2是因为第一个位置需要从第2个位置开始匹配
	for (int i=1;i<=n;i++)
	{
		for (;a[w]*9<=10*a[i]&&w<=n;w++);  //计算第i个数无法匹配的位置
		ans+=w-i-1;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：说好不哭 (赞：4)

# 二分法#

### 前两篇题解中提到了很考思维的O（n）算法，这种算法有点难想到。现在我再添一种二分的n log n算法。
##### 首先从小到大排序，然后二分。
##### emm，最最基础的二分，没有必要介绍了吧......

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100001],n,l,r,mid;
long long sum;
int main(){
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	scanf("%d",&a[i]);
sort(a+1,a+n+1);
for (int i=1; i<=n-1; i++){
l=i; r=n;
while (l<r){
mid=(l+r)/2+1;
if (a[mid]*0.9>a[i]) r=mid-1;
else l=mid; 		
}
sum=sum+l-i;
}
	cout<<sum;
return 0;	
}

```

### 如果n范围大于400万，就不能用二分了，所以想要得满分只能采用另两篇题解的算法优化。### 
###  通过这题，告诉我们一个道理：同一个题面，不同梯度的数据可以使难度~~由红变黑~~，Emm......
### （这个有点夸张了，不过我看过由红变紫的，看这两题[P2602 [ZJOI2010]数字计数](https://www.luogu.org/problemnew/show/P2602),[P1980 计数问题](https://www.luogu.org/problemnew/show/P1980)）
## 所以大家平时练习时一定要在AC的基础上进一步掌握最优算法！！！

---

## 作者：do_while_true (赞：2)

[可能会更好的食用效果](https://www.luogu.com.cn/blog/dilifox/solution-p4670)

### 题目分析

首先朴素的$n^2$算法肯定会超时，考虑优化

$n^2$算法即两两比较，所以我们想要尽可能减少比较次数。

我们看到两两比较是一个不等式，所以我们很容易想到排序优化。

所以我们从大到小排序，有以下两种性质

比较到第 j 位，如果当前第 j 位匹配失败了，那么后面所有的就肯定也匹配失败了，就可以break跳出

第 i 个能够匹配成功的，第 i 个后面的也一定都能够匹配成功 并且i+1与匹配成功的数不相等

所以我们可以记一个左端点l，l为第 i 个数最后一个匹配成功的数，再把ans加上l-i

### *CODE:*

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
ll n,l,ans;
ll a[100005];
bool cmp(ll x,ll y) {
	return x>y;
}
int main() {
	scanf("%lld",&n);
	l=1;
	for(int i=1; i<=n; i++)
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1,cmp);//排序
	for(int i=1; i<=n; i++) {
		for(l=l+1; l<=n; l++) {
			if(a[i]*9<=a[l]*10);
			else break;//如果没有匹配成功就跳出
		}
		//因为到这里l是第一个匹配失败的，最后一个匹配成功的在第一个匹配失败的前面，所以我们先要--l
		ans+=(--l)-i;//加上i能够匹配成功的个数
	}
	printf("%lld",ans);
	return 0;
}
```

看到好几篇题解的时间复杂度都算错了sort本身就是 $\mathcal{O}(nlogn$) 的时间复杂度 所以正确的时间复杂度既不是$\mathcal{O}(2n)$或者$\mathcal{O}(n)$

而是 $\mathcal{O}(nlogn + 2n) $  省略常数项就是 $\mathcal{O}(nlogn)$

---

## 作者：TheShadow (赞：1)

- ~~我最近是不是数据结构学傻了啊。。。~~
- 这道题看是1e5，所以复杂度为$O(nlogn)$的是完全可以跑过去的，然后看题，要求的对于每个数满足要求的区间的长度之和，我们自然而然的就可以想到用**FHQ-Treap**来维护这个序列了。
### - ps：不会FHQ的小伙伴们可以学习一下，这也是一个比较好用的数据结构（~~特别是打暴力~~）。
- 然后事情就很好办了。先建一个一颗平衡树，然后每次查询的时候直接用我们可奈的split操作分出满足条件的区间，然后直接统计答案即可。
- 但是有一个小小的问题，我们每次分出来的序列没有包含与这个相同的数，但它们也是要统计进去的，怎么办呢？
**~~map,你值得拥有！~~**
- 我们可以用map记录一下每个出现的次数，相同的数之间形成的匹配数为$ \frac {n*(n-1)}{2} $，因为每个数只能用一次，所以算过了之后要归0；
- 基本思路就是这样，还有一些处理上的小细节，我会在代码中指出。
### **AC CODE:**
```cpp
#include<bits/stdc++.h>
#define clean(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define lc(cur) ch[cur][0]
#define rc(cur) ch[cur][1]
using namespace std;
template<class T>il read(T &x)
{
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
const int MAXN = 1e5+5;
// 下方为FHQ-Treap的基本操作
int n,a[MAXN],ch[MAXN][2],val[MAXN],size[MAXN],rd[MAXN],cnt;
il pushup(int cur){size[cur]=size[lc(cur)]+size[rc(cur)]+1;}
it new_node(int a){
	val[++cnt]=a,size[cnt]=1,rd[cnt]=rand();
	return cnt;
}
it merge(int x,int y){
	if(!x||!y) return x+y;
	if(rd[x]<rd[y]){
		rc(x)=merge(rc(x),y);
		pushup(x);return x;
	}
	else{
		lc(y)=merge(x,lc(y));
		pushup(y);return y;
	}
}
il split(int cur,int k,int &x,int &y){
	if(!cur) x=y=0;
	else{
		if(val[cur]<=k) x=cur,split(rc(x),k,rc(x),y);
		else y=cur,split(lc(y),k,x,lc(y));
		pushup(cur);
	}
}
int root,x,y,z;
il insert(int val){split(root,val,x,y),root=merge(merge(x,new_node(val)),y);}
//打板子时间到此为止，下面是具体的一些操作细节
map<int,int> mp;//用来储存每个数出现的个数
ll ans;//注意要开longlong
int main()
{
	read(n);
	for(ri i=1;i<=n;i++) read(a[i]),mp[a[i]]++,insert(a[i]);//读入数据，对每个数的出现进行储存，顺便将这个节点插入到平衡树里
	for(ri i=1;i<=n;i++){
		ri t=a[i]*9/10;
		if(a[i]%10==0) t-=1;//这里的两步要注意下，我就是在这里死了好几次。首先是要先乘再除，这样可以保证精度。然后是后面的if判断，通过打表（或者直接推）可以发现，只有10的倍数乘上0.9才是一个整数。因为我们要将小于它的数中满足条件的分成两部分，所以为正数的时候边界还要左移（不太懂的可以自己举几个栗子，或者自己感性理解一下（逃））
		split(root,a[i]-1,x,z),split(x,t,x,y);
		ans+=size[y],root=merge(merge(x,y),z);//这里的两部都是FHQ的正常操作，顺带着统计下答案
	}
	for(ri i=1;i<=n;i++){
		ri sz=mp[a[i]];mp[a[i]]=0;//把每一个还没有计算过的数拿出来统计答案，级的统计过后要归0
		if(!sz) continue;
		ans+=1LL*sz*(sz-1)/2;
	}
	printf("%lld",ans);
	return 0;
}
```
### 最后再温馨提示一下，蒟蒻的这种做法其实并不是最优的，这道题可以做到O(n)，如果感兴趣可以看一下我的方法，但最优的解法还是要学习一下的

---

## 作者：int32 (赞：0)

首篇黄题题解，不喜勿喷。

## $\large \texttt {Step 1. 思路简述}$

先将 $f_{1\ldots n}$ 进行**升序排序**。

我们发现，**当 $f_i$ 不需要与 $f_j$ 比较时，$f_{i-1}$ 也不需要与 $f_j$ 比较**。具有单调性，使用二分答案求解（二分）。

可以使用```STL```中的```lower_bound```函数替换二分。

## $\large \texttt {Step 2. 核心代码}$

```cpp
sort(f+1,f+n+1);
for(int now=1;now<=n;now++){
	need=ceil(f[i]*0.9);
	to=lower_bound(f+1,f+i,now)-f;
	ans+=now-to;
}
```
完结撒花~~

---

## 作者：CoronaQL (赞：0)

# 思路/做法
**看到这道题，我们首先得想法就是用n*n的暴力算法,从i到j进行暴力枚举,显然,这种达到O(n*n)的算法是不满足题目要求1≤N≤10^5的，所以我们又想出了一种新的方法:在(a[i]<0.9*a[j])之后,return.但是，在吸氧之后,这程序依然只能拿70,于是，我们想到了一个代替for的方法：二分，然后我们就得到了AC。**
# AC代码
```cpp
//蒟蒻没有写多少注释，希望大家能从解析中领悟 
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
int n;
int a[1000003];
long long ans;
int read() //子程序 
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') //重复读取操作 
	{
        if(ch=='-') f=-f;
        ch=getchar();//读取 
    }
    while(ch>='0'&&ch<='9') 
	{
        x=x*10+ch-'0';
        ch=getchar();//读取 
    }
    return x*f;
}
int erfen(int i,int l,int r) //二分操作 
{
    while(l<=r) 
	{
    int mid=(l+r)/2;//二分 
    if(a[i]>=0.9*a[mid]) l=mid+1;
    if(a[i]<0.9*a[mid]) r=mid-1;//核心代码 
    }
    return l;
}
int main() 
{
    n=read();//调用 
    for(int i=1;i<=n;i++) 
	a[i]=read();
    sort(a+1,a+n+1);//快排 
    for(int i=1;i<n;i++) 
	{
        ans+=erfen(i,i,n)-i-1;
    }
    cout<<ans;//输出 
}
```
蒟蒻希望大家不要复制了代码就走，还是领会一下蒟蒻的思路吧

---

