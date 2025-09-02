# [USACO17OPEN] Paired Up S

## 题目描述

Farmer John 发现，当他的奶牛附近有另一头奶牛提供精神支持时，每头奶牛挤奶会更容易。因此，他希望将他的 $M$ 头奶牛（$M \leq 1,000,000,000$，$M$ 为偶数）分成 $M/2$ 对。每对奶牛将被引导到谷仓中一个单独的隔间进行挤奶。这些 $M/2$ 个隔间中的挤奶过程将同时进行。

为了增加一些复杂性，Farmer John 的每头奶牛都有不同的产奶量。如果产奶量分别为 $A$ 和 $B$ 的两头奶牛被配对，那么挤完它们总共需要 $A+B$ 单位时间。

请帮助 Farmer John 确定整个挤奶过程完成所需的最少时间，假设他以最佳方式配对奶牛。

## 说明/提示

在这里，如果产奶量为 8 和 2 的奶牛配对，产奶量为 5 和 5 的奶牛配对，那么两个隔间的挤奶时间均为 10 单位时间。由于挤奶是同时进行的，因此整个挤奶过程将在 10 单位时间后完成。任何其他配对方式都会导致某个隔间的挤奶时间超过 10 单位时间，因此不是最优的。

## 样例 #1

### 输入

```
3
1 8
2 5
1 2```

### 输出

```
10```

# 题解

## 作者：x_faraway_x (赞：14)

一题简单的贪心。

每次选产奶量最少的和产奶量最多的配对，取它们产奶时间的最大值就可以啦

具体见代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100005;
struct Node
{
    int x, y;
}a[N];
bool cmp(Node s, Node t) //按照产奶量从大到小排序
{
    return s.y<t.y;
}
int n,ans;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+1+n,cmp);
    int i=1,j=n; //头尾指针分别指向产奶量最少的和产奶量最多的
    while(i<=j)
    {
        if(a[i].y+a[j].y>ans) ans=a[i].y+a[j].y; //产奶时间当前最长，更新答案ans
        if(a[i].x>a[j].x) //产奶少的奶牛数量大于产奶多的
        {
            a[i].x-=a[j].x; //产奶少的奶牛数量减去与产奶多的奶牛配对的数量
            j--; //修改尾指针
        } //下面同上不解释
        else if(a[i].x<a[j].x)
        {
            a[j].x-=a[i].x;
            i++;
        }
        else //产奶一样多，同时修改头尾指针
        {
            i++;
            j--;
        }
    }
    printf("%d",ans); //最后输出ans即可
}
```

---

## 作者：ZhanPJ (赞：8)

~~本蒟蒻的第一篇题解！~~

[题目传送门:P3669](https://www.luogu.com.cn/problem/P3669)

---
题意解释:

有N组牛，第 $i$ 种牛有 $x$ 个产量为 $y$ 的牛，让他们**两两分组**后，使得产奶时间最少。

---

算法:

这道题目是一道贪心题,适合向我这样的蒟蒻练习贪心az。

对于贪心算法还不懂的蒟蒻可以看一看[【百度百科】贪心算法](https://baike.baidu.com/item/%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95/5411800?fr=aladdin)哦！

---

思路:

最小的时间与最长的时间进行配对，然后取他们的最大和。

配对完成后有以下几种情况：
- 最小与最大的时间刚好全部匹配结束了。
- 最小与最大中，只有最大的匹配结束了。
- 最小与最大中，只有最小的匹配结束了。

所以，我们需要先排序（建议不会快排的使用自带的快排函数），再贪心。

---

核心代码(配对和取时间和):
```cpp
	//在此以前为输入和排序!需要函数cmp和sturct的cow数组
	int Max=-1;
	for(int i=1,j=n;i<j;){
		if(cow[i].m==cow[j].m){
			Max=max(Max,cow[i].second+cow[j].second); 
			i++;j--;//首尾指针向内移动
		}else if(cow[i].m<cow[j].m){
			Max=max(Max,cow[i].second+cow[j].second);
			cow[j].m-=cow[i].m;//匹配完成要去掉,方便下一次计算
			i++;
		}else if(cow[i].m>cow[j].m){
			Max=max(Max,cow[i].second+cow[j].second);
			cow[i].m-=cow[j].m;//匹配完成要去掉,方便下一次计算
			j--;
		}
	}
    cout<<Max;
//code by ZhanPJ
```

---

后记:

本蒟蒻求出来的局部最优解与整体最优解：

1. 局部最优解：**最大**的产奶量与**最小**的产奶量进行一一匹配。
2. 整体最优解：按照**从小到大**排序后，再从**最大**产奶量与**最小**产奶量开始搜索，并一一匹配，匹配的时候再进行最大值的比较。


---

## 作者：Zenith_Yeh (赞：4)

这是一道简单的贪心模拟题。

我们只需要把最大的和最小的配对即可，用队列处理即可。

**上菜：**
```cpp
#include<bits/stdc++.h>
#define int long long
#define read() Read<int>()
namespace pb_ds{
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
struct bb
{	int tou,nl;
}op[100005];
int n,now,head,tail,ans;
inline bool cmp(bb a,bb b)
{	return a.nl<b.nl;
}
signed main()
{	n=read();
	now=n;
	head=1,tail=n;
	for(register int i=1;i<=n;++i)op[i].tou=read(),op[i].nl=read();
	sort(op+1,op+n+1,cmp);
	while(head<=tail)
	{	int yu=min(op[head].tou,op[tail].tou);
		op[tail].tou=op[tail].tou-yu;
		if(head!=tail)op[head].tou=op[head].tou-yu;
		ans=max(ans,op[head].nl+op[tail].nl);
		if(op[tail].tou==0)tail--;
		if(op[head].tou==0)head++;
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Tatayy (赞：4)

## 贪心

没啥好说的。简单的贪心题。

***1.*** 首先，按照奶牛的产量排序。

***2.*** 定义两个指针 _begin_ 和 _end_ ，分别初始化为0和n-1。双双枚举，先把他们奶牛个数的最小值配对，如果为 _begin_ 下标的奶牛个数为0则 _begin_ ++；否则，如果为 _end_ 下标的奶牛个数为零，则 _end_ ++；直到 _begin_ > _end_ 。

***3.*** 指针模拟同时，记得取奶牛产奶量（cow[_begin_]+cow[_end_]）的最大值。最大值即结果（因为产奶可以同时进行，否则这题估计就会变成DP题了）。

上代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct Cow
{
    int x,y; // x为这种奶牛的数量，y为产奶量
};
bool cmp(const Cow& x,const Cow& y) // 写一个operator也行
{
    return x.y<y.y; // 按产奶量排序
}
Cow cows[100005];
int main()
{
    int ans=0,n;
    cin>>n;
    for(int i=0; i<n; i++) cin>>cows[i].x>>cows[i].y;
    sort(cows,cows+n,cmp);
    int b=0,e=n-1; // 两个指针
    while(b<=e)
    {
        int t=min(cows[b].x,cows[e].x);
        ans=max(ans,cows[b].y+cows[e].y);
        cows[b].x-=t,cows[e].x-=t;
        if(cows[b].x<=0) b++; // 如果cow[b]种奶牛没有了，b++；
        if(cows[e].x<=0) e--; // 如果cow[e]种奶牛没有了，e++；
// 注意!以上两个if语句里不能写x==0，因为万一减出来个负数，就会陷入死循环
    }
    cout<<ans<<endl;
    return 0;
}
```
###### ~~这题坑了我好几次：）~~

---

## 作者：荷叶下 (赞：3)

### 题意
##### ~~十分简单~~
##### 将最大的和最小的组合,求出其中所需时间的最大值
### 实现
##### 一道简单的贪心
##### 每次将产奶量最少的和最多的配对
##### 找出产奶时间最大值
##### AC代码如下
```cpp
#include <bits/stdc++.h>
using namespace std ;
int n , ans , cnt ;
struct node
{
    int sum , val ; //sum为奶牛数量,val为产奶量
    bool operator < (const node x)
    {
        return x.val < val ;
    } //重载
}cow[100010] ;

int main()
{
    cin >> n ;
    for(int i = 1 ; i <= n ; ++i)
        cin >> cow[i].sum >> cow[i].val ;
    sort(cow + 1 , cow + n + 1) ;
    for(int i = 1 , j = n ; i <= j ;)
    {
        int x = min(cow[i].sum , cow[j].sum) ; //求出两边产量一致的奶牛数量
        ans = max(ans , cow[i].val + cow[j].val) ; //更新答案为产奶时间最长的
        cow[i].sum -= x ; cow[j].sum -= x ;
        if(cow[i].sum <= 0) //左边的奶牛没有了
            ++i ;
        if(cow[j].sum <= 0) //右边的奶牛没有了
            --j ;
    }
    cout << ans ;
    return 0 ;
}
```
##### 感谢观看！/*~__~*/


---

## 作者：PersistentLife (赞：3)

[博客阅读体验更佳](https://www.luogu.com.cn/blog/302837/solution-p3669)

### 样例提供

为方便大家调试程序，我准备了一组比较强的样例，以剪贴板的形式提供：

[输入](https://www.luogu.com.cn/paste/1z9ax9r5) [输出](https://www.luogu.com.cn/paste/s7ll6dz6)

展开源码复制即可。

### 题目分析

本题用贪心做，即每次将产奶量最大的奶牛与最小的奶牛配对，这样可以使答案最小。

### 贪心证明

我们假设只有 $4$ 头奶牛，产奶量分别为 $a$ $b$ $c$ $d$，假设 $a \le b \le c \le d$，那么答案为：

$\min(\max(a+b,c+d),\max(a+c,b+d),\max(a+d,b+c))$。

因为 $a \le b \le c \le d$；

所以 答案为 $\max(a+d,b+c)$。

那么 $6$ 头，$8$ 头也是同理。

### 代码实现

具体做法详见注释：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct cow
{
	int x,y;//分别表示奶牛数量和产奶量 
}c[123456];
bool cmp(cow a,cow b)
{
	return a.y>b.y;
}//按产奶量从大到小排序 
int n,ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i].x>>c[i].y;
	sort(c+1,c+1+n,cmp);//读入 排序  
	int i=1,j=n;//头尾指针 
	while(i<=j)
	{
		ans=max(ans,c[i].y+c[j].y);//计算ans，即每组奶牛最大的产奶量
		c[i].x--;
		c[j].x--;//把已经分组的奶牛减去
		if(c[i].x==0) i++;
		if(c[j].x==0) j--;//移动指针 
	}
	cout<<ans;
	return 0;//输出，别忘了return 0
}
```
交上去，发现只有 $10$ 分，全部 TLE 了。

我们怎么优化它呢？

哦！循环里面的减去奶牛的操作耗时很多，所以我们可以改成这样：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct cow
{
	int x,y;//分别表示奶牛数量和产奶量 
}c[123456];
bool cmp(cow a,cow b)
{
	return a.y>b.y;
}//按产奶量从大到小排序 
int n,ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>c[i].x>>c[i].y;
	sort(c+1,c+1+n,cmp);//读入 排序  
	int i=1,j=n;//头尾指针 
	while(i<=j)
	{
		ans=max(ans,c[i].y+c[j].y);//计算ans，即每组奶牛最大的产奶量
		if(c[i].x>c[j].x)//如果产奶量小的奶牛数量多 
		{
			c[i].x-=c[j].x;//产奶量小的奶牛减去 
			j--;//移动j指针 
		}
		//下同，为产奶量大的奶牛多 
		else if(c[i].x<c[j].x)
		{
			c[j].x-=c[i].x;
			i++;
		}
		//如果一样多 
		else
		{
			i++;
			j--;//同时移动两个指针 
		}
	}
	cout<<ans;
	return 0;//输出，别忘了return 0
}
```

AC 了！

---

## 作者：sycqwq (赞：2)

贪心题

策略：把大的配小的

不需要完全展开，可以一堆一堆的配

复杂度 $o(n log(n))$ （其实就是排序复杂度）

```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//雅礼祖传快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
#define int long long
typedef long long ll;
const int maxn=5e5+5;
struct node
{
	int x,y;
}a[maxn];
int n;
int cmp(node s1,node s2)
{
	return s1.y<s2.y;
}
signed main(){
//	freopen("pairup.in","r",stdin);
//	freopen("pairup.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	int i=1,j=n,ma=0;//i指向产奶量小的，j指向大的
	while(i<j)
	{
		if(a[j].x<a[i].x)//因为每一堆的数量可能不同，所以需要判断哪一堆数量多
		{
			a[i].x-=a[j].x;
			ma=max(ma,a[i].y+a[j].y);
			--j;
		}
		else if(a[j].x>a[i].x)
		{
			a[j].x-=a[i].x;
			ma=max(ma,a[i].y+a[j].y);
			++i;
		}
		else
		{
			ma=max(ma,a[i].y+a[j].y);
			--j;
			++i;
		}
	}
	cout<<ma;
	return 0;
}
```

---

## 作者：LZOI_LYH (赞：2)

这一道题，做完之后看见只有一片题解，于是来写一篇。

这题的题面大意有点太过于~~简洁~~清楚了

可能是因为我太水了，所以乍一眼没有看出来题目到底讲了啥。

后来想了一会儿，这不就是一个无脑贪心吗？

其实本质上这题就是一个让最大和最小的配对的题目。

一开始先按照挤奶时间从小到大排个序。然后从两边往中间配对就行了

代码如下：

为方便解释，我们暂且把挤奶时间相同的奶牛视为同一种牛

代码变量解释：

$quantity$：每种牛的只数

milk_time：每种牛的挤奶时间

minimum_milk_time：最终答案，也就是挤奶时间的最小值

$left$：左端点

$right$：右端点

$number$：当前这一对中奶牛的个数

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
	int quantity,milk_time;
}s[100001];//结构体存储，方便排序
bool comp(node x,node y){
	return x.milk_time<y.milk_time;
}//按照每种牛的挤奶时间从小到大进行排序
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&s[i].quantity,&s[i].milk_time);
   	//输入
	sort(s+1,s+n+1,comp);//排序
	int minimum_milk_time=0;
	for(int left=1,right=n;left<=right;){
		int number=min(s[left].quantity,s[right].quantity);
        	//确定当前对的牛数
		number/=(left==right)?2:1;
        	//如果left==right，就要除以2，避免重复
		minimum_milk_time=max(minimum_milk_time,s[left].milk_time+s[right].milk_time);//然后取一个答案
		s[left].quantity-=number;s[right].quantity-=number;
     		//成功配对，减去对中牛的个数
		left+=(s[left].quantity==0)?1:0;
		right+=(s[right].quantity==0)?-1:0;
        	//如果当前种类的牛用完了，就去到下一个种类
	}
	printf("%d",minimum_milk_time);//输出
}
```

蒟蒻仍有不足之处，希望各位大佬多多指教

PS：本题解部分参考了USACO官方题解

---

## 作者：tribool4_in (赞：1)

将产奶量从小到大 $sort$ 一遍，然后将大的和小的两两配对即可（但我一开始只想到了这点），结果 $M \le 1,000,000,000$，就~~很愉快的~~超时了。

那么我们发现，有很多奶牛产奶量一致，我们可以一块处理，然后就如此愉快的过了。

代码：

```cpp
#include<bits/stdc++.h>
#define itn int
#define elif else if
#define rg register
#define psb push_back
#define pii pair<int, int>
#define priq priority_queue<pii>
#define lpriq priority_queue<pii, vector<pii>, greater<pii> >
#define mp make_pair
#define mem(s, x) memset((s), (x), sizeof(s))
#define debugok cout<<"OK"<<endl
#define debug(i) cout<<#i<<"="<<i<<endl
const int N = 1e5 + 5;
using namespace std;
inline int read() {
	int s=0, w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
struct node {
	int x, y;
};
bool cmp(node x, node y) {
	return x.y < y.y;
}
int n, ans = 0;
node c[N];
int main() {
	n = read();
	for(int i = 1; i <= n; ++i) {
		c[i].x = read(), c[i].y = read();
	}
	sort(c + 1, c + 1 + n, cmp);
	int l = 1, r = n;
	while (l <= r) {
		int t = min(c[l].x, c[r].x);
		ans = max(ans, c[l].y + c[r].y);
		c[l].x -= t, c[r].x -= t;
		if(c[l].x <= 0) l++;
		if(c[r].x <= 0) r--;
	}
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：羚羊WANG (赞：1)

[题目传输门](https://www.luogu.com.cn/problem/P3669)

题目意思并不难理解

让我们把$m$头奶牛排列成$m/2$对，求这$m/2$对的奶牛最大和最小

显然，我们把一头大的奶牛和一头小的奶牛排成一队，这样一直到最后一个，就可以得到理想的最小值

那是不是用$O(m)$的时间复杂度去实现就行呢?

结果就超时了

我们可以考虑对这个程序的优化

经过很短$(jiu)$的时间观察，可以发现有一些奶牛他们的贡献是一样的，但我们重复计算了很多次

所以，我们在乎的谁和谁配了对，而不是一共有多少对

首先将奶牛按照贡献排序

然后开两个指针，$l$指向头，$r$指向尾，一步步计算贡献即可

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
int l=1,r;
struct node{
	int val;
	int many;
}e[100010];
inline bool cmp(node a,node b){
	return a.val<b.val;
}
int ans;
int sum;
signed main(){
	n=read();
	for(register int i=1;i<=n;++i)
		{
			e[i].many=read();
			e[i].val=read();
		}
	sort(e+1,e+n+1,cmp);
	r=n;
	while(l<r)
		{
			sum=min(e[l].many,e[r].many);
			e[l].many-=sum;
			if(l!=r)
				e[r].many-=sum;
			ans=max(ans,e[l].val+e[r].val);
			if(e[l].many==0)
				l++;
			if(e[r].many==0)
				r--;
		}
	write(ans);
	return 0;
}

```

最后祝大家$AC$此题

---

## 作者：Unordered_OIer (赞：1)

# P3669 题解
这么简单一道题，怎么只有4篇题解？  
→既然如此，我就来发一篇~~

其实思路很简单：贪心就行了，每一次把产奶量**最少**的和**最多**的匹配即可。

实现方法：先$sort$一波，根据头尾下标定$l,r$，然后进行双游标操作。

## 编码简单，经济实惠！！！
好吧，附上代码  
输入：
```cpp
void init(\){
	scanf("%lld",&n);
	for(ll i=0;i<n;i++)scanf("%lld%lld",&hehe[i].x,&hehe[i].y);
// 输入
	sort(hehe,hehe+n,cmp); // 排序
}
```
双游标：
```cpp
void solve(\){
	ll l=0,r=n-1;
	while(l<=r){ // 双游标
		ans=max(ans,hehe[l].y+hehe[r].y);
		if(hehe[l].x<hehe[r].x)hehe[r].x-=hehe[l].x,l++; // 左游标++
		else if(hehe[l].x>hehe[r].x)hehe[l].x-=hehe[r].x,r--; // 右游标-- 
		else l++,r--; // 不解释，=的情况
	}
}
```
输出：
```cpp
void print(\){printf("%lld\n",ans);} // 
```
完整版代码：
```cpp

//
//              Copy right by ***
//
//              algorithm:双游标
//
//              score:100(AC)
//
//
//

#include<bits/stdc++.h>
#define N 100005
using namespace std;

typedef long long ll;
struct _c_o_w_{ll x,y;}hehe[N];
// hehe
// 结构体好排序
bool cmp(const _c_o_w_ &a,const _c_o_w_ &b){return a.y<b.y;}

ll n,ans; // 没什么好说的

void init(\){
	scanf("%lld",&n);
	for(ll i=0;i<n;i++)scanf("%lld%lld",&hehe[i].x,&hehe[i].y);
// 输入
	sort(hehe,hehe+n,cmp); // 排序
}

void solve(\){
	ll l=0,r=n-1;
	while(l<=r){ // 双游标
		ans=max(ans,hehe[l].y+hehe[r].y);
		if(hehe[l].x<hehe[r].x)hehe[r].x-=hehe[l].x,l++; // 左游标++
		else if(hehe[l].x>hehe[r].x)hehe[l].x-=hehe[r].x,r--; // 右游标-- 
		else l++,r--; // 不解释，=的情况
	}
}

void print(\){printf("%lld\n",ans);} // 

int _main(\){
	init(\); // 
	solve(\); // 
	print(\); // 
	return 0;
}

int main(\){
	_main(\);
}
```
欢迎来[**访问我的博客**](https://www.luogu.com.cn/blog/291706/)  
吾等写题解不易，转载请标明出处，不胜感谢！  

---

## 作者：wangyibo201026 (赞：0)

## 思路

首先根据纪念品分组这道题可知肯定是最小的配最大的最划算，所以要排遍序。可是将每头奶牛都用数组存起来的话会炸，所以考虑让一段奶牛和一段奶牛这样的配对，于是便想到了双指针。

## 实现

定义指针 $l$ 和 $r$，让这两个指针往中间扫。如果 $a_l < a_r$，则 $l$ 加一，$a_r$ 的 $y$ 减去 $a_l$ 的 $y$。反之，$r$ 减一，$a_l$ 的 $y$ 减去 $a_r$ 的 $y$。当 $l > r$ 时停止，此时统计一下前面 $a_l + a_r$ 的最大值就可以了。

## 代码

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n;

struct node{
  int x, y;
}a[100005];

bool cmp(node i, node j){    //排序函数
  return i.y < j.y;
}

void Solve(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i].x >> a[i].y;
  }
  sort(a + 1, a + 1 + n, cmp);    //按照时间排序
  int l = 1, r = n, ans = -1e9;
  while(l <= r){    //一定注意，本题数据太水，l < r 也能过，但 l <= r 才是正解（因为到了最后自己和自己分）
    if(a[l].x < a[r].x){
      a[r].x -= a[l].x;
      ans = max(ans, a[l].y + a[r].y);    //第一种情况
      l++;
    }
    else if(a[l].x > a[r].x){    //第二种
      a[l].x -= a[r].x;
      ans = max(ans, a[l].y + a[r].y);
      r--;
    }
    else{     //这一种没讲，是两个都相等的情况
      ans = max(ans, a[l].y + a[r].y);
      l++;
      r--;
    }
  }
  cout << ans;
}

int main(){
  Solve();
  return 0;
}
```

---

