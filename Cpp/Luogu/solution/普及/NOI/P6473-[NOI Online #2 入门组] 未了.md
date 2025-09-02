# [NOI Online #2 入门组] 未了

## 题目描述

由于触犯天神，Sisyphus 将要接受惩罚。

宙斯命 Sisyphus 推一块巨石上长度为 $L$ 的山坡。Sisyphus 匀速向上推的速度为每年 $v$ 的长度（由于是匀速，故经过 $\frac{1}{2}$ 年将能向上推 $\frac{v}{2}$ 的长度）。然而，宙斯并不希望 Sisyphus 太快到达山顶。宙斯可以施展 $n$ 个魔法，若宙斯施展第 $i$ 个魔法 $(1\leq i \leq n)$，则当 Sisyphus 第一次到达位置  $a_i$ 时，他将会同巨石一起滚落下山底，并从头推起。（滚落的时间忽略不计，即可看作第一次到达位置 $a_i$ 后 Sisyphus 立即从山底重新出发）

例如宙斯施用了 $a_i=3$ 和 $a_i=5$ 的两个魔法。Sisyphus 的速度 $v=1$ ，山坡的长度 $L = 6$，则他推石上山过程如下：

- 用 $3$ 年走到位置 $3$。

- 受 $a_i=3$ 的魔法影响，回到了山底出发。

- 再用 $3$ 年走到位置 $3$，然而因为是第二次到达，$a_i=3$ 的魔法不起作用。

- 用 $2$ 年走到位置 $5$。

- 受 $a_i=5$ 的魔法影响，回到了山底出发。

- 用 $6$ 年从山底走到了山顶。花费的总时间为 $14$ 年。

现在，宙斯有 $q$ 个询问。对于第 $i$ 个询问 $t_i$，宙斯想知道，他最少需要施展多少个魔法才能使 Sisyphus 到达山顶所用的年数大于 $t_i$。

## 说明/提示

1. 不使用任何魔法，Sisyphus 需要 $2$ 年走上山顶。
2. 使用魔法 $2$ ，Sisyphus 需要 $\frac{11}{3}$ 年走上山顶。（用时 $\frac{5}{3}$ 年走到魔法 $2$ 的位置并滚落下山，再用时 $\frac{6}{3}=2$ 年走到山顶）
3. 使用魔法 $1,2$ ，Sisyphus 需要 $\frac{14}{3}$ 年走上山顶。
4. 宙斯不能使 Sisyphus 用大于 $5$ 年的时间走上山顶。

对于测试点 $1\sim 8:n=1$。

对于测试点 $9\sim 12:n=2$。

对于测试点 $13\sim 17:n,q\le 1000$。

对于所有测试点：$1 \leq n,q \leq 2 \times 10^5$，$1\leq v\leq L\leq 10^{9}$，$1\leq a_i < L$，$1 \leq t_i\leq 10^9$。

数据保证 $a_i$ 两两不同。

## 样例 #1

### 输入

```
3 6 3
3 5 1
4
1
3
4
5
```

### 输出

```
0
1
2
-1
```

# 题解

## 作者：chen_zhe (赞：81)

这里是民间数据 std。

思路其实很简单。我们应该是先用在后面触发的魔法，再用在前面触发的魔法，这样触发次数才会尽可能少。

因此我们上来对 $a_i$ 排序，然后做个前缀和，那么 $s_i$ 就是触发 $i$ 次后所用的最大时间，显然单调递增。

我们就可以在 $s_i$ 上进行二分查找，使用 `C++ STL` 中的 `upper_bound()` 函数可以帮助我们完成实现。

时间复杂度 $O(q \log n)$，足以通过本题。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <queue>
#include <vector>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

int n,L,v;

long long a[200050],s[200050];

inline bool cmp(double a,double b)
{
	return a>b;
}

int main()
{
	n=read(),L=read(),v=read();
	for (int i=1;i<=n;i++)
		a[i]=read();
	sort(a+1,a+n+1,cmp);
	for (int i=1;i<=n;i++)
		s[i]=s[i-1]+a[i];
	int q=read();
	while (q--)
	{
		long long t=read();
		t=t*v-L;
		if (t<0)
			puts("0");
		else if (s[n]>t)
			cout << upper_bound(s+1,s+n+1,t)-s << endl;
		else
			puts("-1");
	}
	return 0;
}
```

---

## 作者：翼德天尊 (赞：76)

**贪心+二分**
## STEP 1 审题

为了方便理解，可以将本题转化为如下条件：

1. 已知正常爬山的速度，时间；

2. 有n个魔法，每个魔法可以让爬山的距离增加$a(i)$；（等同于倒回去重新上坡）

3. 给出q次询问，每次询问需要回答在$t(i)$之前最少要使用几次魔法，如无法达到，输出-1；

## STEP 2 分析方法

- **为了确保“最少”，我们需要用到贪心的方法，将没个魔法使用后所能延长的距离从大到小排序，从而得到最优解**

- **为了确保不会超时，我们需要用到二分的算法，降低时间复杂度，一路护送通关**

## STEP 3 AC代码及完整注释
```
#include<bits/stdc++.h>
using namespace std;
double b[200001],l,q,t,v,a[200001];
long long n;
int cmp(double x,double y){
	return x>y;
}
int main(){
//	freopen("endless.in","r",stdin);
//	freopen("endless.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n>>l>>v;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}//输入
	sort(a+1,a+1+n,cmp);//从大到小排序
	b[0]=l/v;//不适用魔法的时间为l/v；
	for (int i=1;i<=n;i++){
		b[i]=double(a[i])/v+b[i-1];//使用前i项魔法的时间
	}
	cin>>q;
	while (q--){//q次询问
		cin>>t;
		if (b[n]<=t){
			printf("-1\n");
			continue;
		}//所有魔法都使用还不行输出-1
		int l=0,r=n,ans=0;
		while (l<=r){
			int mid=(l+r)>>1;
			if (b[mid]>t){
				ans=mid;
				r=mid-1;
			}else{
				l=mid+1;
			}
		} //二分模板
		printf("%d\n",ans);//输出
	}
	return 0;//好习惯++
} 
```
---------
本次题解就这么结束啦！如果还有什么不懂的问题，欢迎各位在评论区回复哦！我会第一时间解答哒。

如果都明白了，就点个赞纪念一下你的成长吧！


---

## 作者：云浅知处 (赞：36)

此题作为NOI Online#2的第一题算是很良心了。

[更好的阅读体验？](https://www.luogu.com.cn/blog/wwwluogucn/solution-p6473)

------------

$1.$关于`魔法`

由于第 $i$ 个魔法 $a_i$ 会让 Sisyphus 在爬山爬到 $a_i$ 这个位置的时候从头重新爬，所以它的作用就是让 Sisyphus 白白爬 $a_i$ 长的山。

又因为 Sisyphus 每年可以爬 $v$ 的长度，所以这个魔法的作用本质上是让 Sisyphus 白白浪费 $\dfrac{a_i}{v}$ 的时间。

所以，我们可以在读入的时候就将 $a_i$ 除以 $v$。

$2.$（本题考查点）最少需要施展的魔法数量

一个很自然的想法是：将代表魔法能力的数组（此时已经除以 $v$ 了）降序排列，从第一个开始一直往后加，直到这个和大于要求的时间，再输出加了多少个数。

但是，这么做会导致最后三个点完美 TLE 。

~~TLE 了怎么办？前缀和+二分帮您完美解决！~~

我们可以将这个数组降序排列后计算每一项的前缀和，再利用`C++ STL`中自带`upper_bound`来二分查找最小的满足要求的数。

~~激动人心的时刻到了！~~ 最后，上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
double l,v,a[200005],s[200005],t,y;//l,v如题意；数组a是魔法强度；数组s是数组a降序排列后的前缀和
int n,i,ans;//n如题意
bool cmp(double r,double s){
    return r>s;
}//用于在sort函数中进行降序排列
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//高科技，可以给cin,cout加速
	cin>>n>>l>>v;
	y=l/v;//计算 Sisyphus 原本上山需要的时间
	for(i=1;i<=n;i++){
		cin>>a[i];//输入魔法强度
		a[i]/=v;//把魔法强度转化为这个魔法能让 Sisyphus 白白浪费的时间
	}
    sort(a+1,a+n+1,cmp);//降序排列
    for(i=1;i<=n;i++){
        s[i]=s[i-1]+a[i];//计算前缀和
    }
	cin>>q;
	while(q--){
		cin>>t;//对于每一次询问
		if(y>=t){//如果 Sisyphus 原本上山需要的时间就比宙斯想让他上山用的时间多
			cout<<0<<endl;//直接输出0
		}
		else if(s[n]+y<=t){//如果 Sisyphus 不可能用那么多时间上山
			cout<<-1<<endl;//输出-1
		}
		else{
			ans=upper_bound(s+1,s+n+1,t-y)-s;//在前缀和数组中二分查找最小的大于等于t-y（即 Sisyphus 需要多爬的时间）的数，记得减去数组头指针s
			cout<<ans<<endl;//输出查找的结果
			//可以简化为cout<<upper_bound(s+1,s+n+1,t-y)-s<<endl;
		}
	}
	return 0;//完结撒花～
}
```

---

## 作者：zjrdmd (赞：15)

看dalao们都用的二分，~~我这个蒟蒻瑟瑟发抖~~~。

首先，贪心的思路是一样的，但是既然已经贪心了，为什么不能贪到底呢QAQ。

前面的思路就是求前缀和+sort，但是我把二分的地方改成了一个贪心，我们把q组询问按照升序排一个序，这样后面一个数严格大于等于前面一个数，所以我们只需要在上次开始的位置枚举即可，虽然有两层循环，但是显而易见，每一个数最多背求2遍，即总的复杂度不超过2n，那么我们贪两边就好了啊QAQ。剩下的解释加代码里了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <stdlib.h>
#include <stack>
#include <queue>
#define N 200005

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x*f;
}

int a[N];
double sum[N];
int ans[N];
struct Node{
	int t,b;//t代表他要求询问的>t的数 
}qx[N];

bool cmp(int x,int y){
	return x>y;
}

bool cmp2(Node x,Node y){
	return x.t<y.t;
}
int main(){
//	freopen("endless.in","r",stdin);
//	freopen("endless.out","w",stdout);
    int n,l,v,q,p=0;
	n=read();l=read();v=read();
	for(int i=1;i<=n;i++)a[i]=read();
	std::sort(a+1,a+n+1,cmp);//极其朴素的读入+排序（这里其他dl讲的很清楚。 
	q=read();
	for(int  i=1;i<=q;i++)qx[i].t=read(),qx[i].b=i;//读入+初始化编号 
	std::sort(qx+1,qx+q+1,cmp2);//贪心的重点 
	for(int i=1;i<=n;i++){
		sum[i]=(double)a[i]/v;
		sum[i]+=sum[i-1];
	}
	for(int i=0;i<=n;i++){
		sum[i]+=(double)l/v;
	} //求前缀和 
	for(int i=1;i<=q;i++){
		int pi=p;
		for(int j=p;true;j++){//从前往后枚举每一个数 
			if(j>n){//如果超过n个数，那么输出-1 
				ans[qx[i].b]=-1;
				break;
			}
			if(sum[j]>(double)qx[i].t) {//记录位置 
				ans[qx[i].b]=j;
				break;
			}
			pi++;
		}
		p=pi;
	}
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);//输出答案 
	return 0;
}

```

感觉自己写的比很多题解都要详细QAQ，麻烦管理员神仙给窝过吧/kk，毕竟这是一种新的思路嘛。

---

## 作者：moocpp (赞：11)

算法是贪心，魔法距离起点a[i]越远越优先用。所以先从大到小排序a[i]，再用前缀和预处理一下用了i个魔法走的距离s[i]，再求出时间t[i]，这里的t[i]是向上取整的。将下来是难点二分查找，要用STL的upper_bound，返回的是刚好比查找数要大一点的数的地址，再减t就是数组下标了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
long long s[200005],t[200005];
bool cmp(const int&x,const int&y)
{
	return x>y;
}
int main()
{
	int n,v,l,q,x;
	scanf("%d%d%d",&n,&l,&v);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+1+n,cmp);
	s[0]=l;
	for (int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
	for (int i=0;i<=n;i++)t[i]=s[i]/v+(s[i]%v>0);
	scanf("%d",&q);
	while(q)
	{
		q--;
		scanf("%d",&x);
		if (x>=t[n])printf("-1\n");
		else printf("%lld\n",upper_bound(t,t+1+n,x)-t);
	}
	return 0;
}
```


---

## 作者：Mine_King (赞：9)

发现过了后第一时间来交题解啦~

首先可以发现的是高度越高耗费的时间越多（废话）。那么我们优先使用$a_i$高的魔法可以耗费更多的时间。所以就先对$a_i$排序。然后，对于每个询问，一种做法是一个个枚举，直到满足要求为止，但这样太慢了。我们可以记录前缀和$sum_i$表示排完序后用前i个魔法耗费的时间。在查询时，我们只需要二分即可。

**code：**
```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,L,v,q,a[200005];
double s[200005];
int main()
{
	freopen("endless.in","r",stdin);
	freopen("endless.out","w",stdout);
	scanf("%d%d%d",&n,&L,&v);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);//排序
	for(int i=n;i>=1;i--) s[n-i+1]=s[n-i]+(1.0*a[i]/v);//记录前缀和
	scanf("%d",&q);
	while(q--)
	{
		int t;
		double sum=1.0*L/v;//不用魔法的时间
		scanf("%d",&t);
		if(t<sum)//不用魔法就行
		{
			printf("0\n");
			continue;
		}
		if(t>=sum+s[n])//用所有魔法都不行
		{
			printf("-1\n");
			continue;
		}
		int l=1,r=n;
		while(l<r)//二分
		{
			int mid=(l+r)/2;
			if(t<sum+s[mid]) r=mid;//mid可行，那么将右边界缩小到mid
			else l=mid+1;//mid不可行，就将左边界移动到mid+1（不用包含mid）
		}
		printf("%d\n",r);//最后输出的就是r了
	}
	return 0;
}
```
[安利一发博客](https://www.luogu.com.cn/blog/195331/)

---

## 作者：Scrutiny (赞：9)

贪心+二分查找。

我们记用$i$个魔法使$Sisyphus$到山顶的时间最长为$dp_i$。

显然$dp_0=\dfrac{L}{v}$。

魔法高度越高，造成$Sisyphus$浪费的时间也就越多。

因此我们将数列$\{a_n\}$从小到大排序。

那么想用$i$个魔法使$Sisyphus$到山顶的时间最长，必定是用第$n-i+1$到第$n$个魔法（包括两端）中的所有魔法。

所以$dp_i=dp_{i-1}-\dfrac{L}{v}+a_{n-i+1}+\dfrac{L}{v}=dp_{i-1}+a_{n-i+1}$。

接着我们需要查找在$\{dp_n\}$数列中比$t_i$大的第一个数的下标。

于是我们自然想到`upper_bound`，题目就做完了。

### 注意：

$1.$$L,v$用`double`类型存储。

$2.$`upper_bound`返回的是指针类型，直接输出会`WA`。

$3.$如果`upper_bound`返回的是$n+1$则需要输出$-1$。

### CODE:

```cpp

#include<bits/stdc++.h>
using namespace std;
long long n,l,v,q,a[200007],w[200007];
long double tmpa[200007],dp[200007];
int main(){
	freopen("endless.in","r",stdin);
	freopen("endless.out","w",stdout);
	scanf("%lld%lld%lld",&n,&l,&v);
	long double tmpl=l,tmpv=v;
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		tmpa[i]=a[i];
	}
	sort(tmpa+1,tmpa+n+1);
	scanf("%lld",&q);
	for(int i=1;i<=q;++i){
		scanf("%lld",&w[i]);
	}
	dp[0]=tmpl/tmpv;
	for(int i=1;i<=n;++i){
		dp[i]=dp[i-1]+(tmpa[n-i+1]/tmpv);
//		cout<<dp[i]<<" ";
	}
	for(int i=1;i<=q;++i){
		int ans=upper_bound(dp,dp+n+1,w[i])-dp;
		if(ans==n+1){
			printf("-1\n");
			continue;
		}
		printf("%d\n",upper_bound(dp,dp+n+1,w[i])-dp);
	}
	return 0;
} 

```

~~要抄代码请理解后再抄。~~

---

## 作者：Diamiko (赞：5)

用一个数组`cost[]`预处理出使用i次魔法时的最长时间`cost[i]`，对于每次询问，进行二分查找。

再就是贪心，这题的贪心策略很明显，优先选择靠后的魔法。因为能让他多滚一会是一会……

详见代码。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<set>
#include<cctype>
using namespace std;
inline int read()
{
	char c;int res=0;
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())res=res*10+c-'0';
	return res;
}
const int N=2e5+10;
int n,q;
//魔法个数，询问次数
double L,v,a[N],t,cost[N];
//L长度，v速度，a[]魔法位置，t询问，cost[i]用i次魔法的最长时间
bool cmp(double a,double b)
{
	return a>b;
}
//排序函数
int main()
{
//	freopen("endless.in","r",stdin);
//	freopen("endless.out","w",stdout);
	n=read(),L=read(),v=read();
	double completeTime=(double)L/v;
	//completeTime是不使用魔法的最大时间
	for(int i=0;i<n;i++)
	{
		a[i]=read();
	}
	sort(a,a+n,cmp);
	//排序
	for(int i=0;i<n;i++)
	{
		cost[i]=(double)a[i]/v;
		//第一次到魔法点走的时间
		if(i)
			cost[i]+=cost[i-1];
		//加上以前走的
		else
			cost[i]+=completeTime;
		//如果是第一个那就加上总时间
	}
	q=read();
	while(q--)
	{
		t=read();
		if(completeTime>t)
		{
			puts("0");
			continue;
		}
		//这种情况根本不用使用膜法
		int order=upper_bound(cost,cost+n,t)-cost;
		//二分查找第一个大于此时间的位置（即魔法使用数）
		if(cost[order]>t)
			printf("%d\n",order+1);
		//+1是因为我的下标从0开始的
		else
			puts("-1");
	}
	return 0;
}
```

---

## 作者：Mikemao666 (赞：5)

#### NOI Online没来得及报名QAQ
只好看着洛谷的题面做了……

这道题的人物背景（摘自百度）：[Sisyphus](https://baike.baidu.com/item/%E8%A5%BF%E8%A5%BF%E5%BC%97%E6%96%AF/6690210?fromtitle=Sisyphus&fromid=5322905)

###### 他也认为自己是幸福的。这个从此没有主宰的世界对他来讲既不是荒漠，也不是沃土。这块巨石上的每一颗粒，这黑黝黝的高山上的每一矿砂唯有对西西弗斯才形成一个世界。他爬上山顶所要进行的斗争本身就足以使一个人心里感到充实——加缪《西西弗的神话》
看完这段百度，我也唏嘘不已。其实，我们的OI之路也是如此。有可能我们曾无限接近于成功，接近胜利，也有可能因为那一丝疏忽而前功尽弃，只能卷土重来。但我们并不后悔，因为我们是**幸福的**，**我们有自己的目标，有自己的梦想，为之奋斗，不留遗憾。**

~~不行这不是语文阅读~~

### 正题
题目虽然长，但仔细看看还是很好懂的。
这里只讲思路~~代码错了别怪我，lz住校初中生，平时也没有时间上洛谷~~

这道题的主要思路就是：

- 在什么魔法都不用放的情况下，直接$cout0$,然后$q-- $   $ continue$
- 在用一次魔法就可以解决问题的情况下，直接用离山顶最近的魔法点施法，
然后$cout0$ ,$q-- $  , $ continue$
- 在上述两种情况都不满足的情况下，我们就一步一步来：
	1. 首先用两个施法点，分别为最远和第二远，先计算到第二远的点时的时间T，再累加最远；在循环外判断$T$和是否大于$Ti$。
    
   2. 如果不行，再用三个施法点，分别为最远、第二远和第三远，先计算第三远的点所需时间……以此类推。
   3. 一旦符合，马上输出＋标记+跳出循环；最后如果标记的$bool$变量没有改变，则输出$-1$。 
   
   **P.S**解决此题的关键是把施法点从大到小排序，所以用$sort$的童鞋们，要加$cmp$哦~
   
  下面$code$(仅供参考+启发思路，不保证对)

```cpp
#include<bits/stdc++.h>
using namespace std;
double a[200001];
int t[200001];
bool cmp(double a,double b){
    return a>b;
}
int main (){
	double l,v;//double是为了求T是避免取整
	int n,i;
	cin>>n>>l>>v; 
	for(i=1;i<=n;++i){
		cin>>a[i];
	}
	sort(a+1,a+n+1,cmp);
	int q;
	cin>>q;
	while(q!=0){//多组测试数据
		int ans(0);
		int ti;
		cin>>ti;
		if(l/v>ti){//特判情况1
			cout<<0<<endl;
			q--;
			continue;
		}
		else if(l/v+a[1]/v>ti){//特判情况2
			cout<<1<<endl;
			q--;
			continue;
		}
		else{
			bool f=true;//判断是否符合题意
			for(i=2;i<=n;i++){
				double t1=0;
				for(int j=i;j>=1;j--){
					t1+=a[j]/v;//到达施法点所需时间累加
					ans++;//魔法次数
				}t1+=l/v;//加上最后一次到山顶
				if(t1>ti){
					cout<<ans<<endl;
					f=false;
					break;//判断
				}	
			}if(f==true){//无解
				cout<<"-1"<<endl;
			}q--;	
		}	
	}
	return 0;
}
```

---

## 作者：grass8cow (赞：4)

解题方法：贪心+二分。

我们可以发现，如果我们能使用 $n$ 个魔法，那么就选择前 $n$ 大的魔法，这样它们的和最大。我们可以预处理出使用 $n$ 个魔法时需要的时间。对于每个询问，我们通过二分找出最小的$sum_n>t_i$ 的 $n$ 。思维难度：入门难度 算法难度：普及-
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l,v,m,a[200001],i,le,ri,now[200001],ans,mid;
bool cmp(long long a,long long b)
{
	return a>b;
}
int main()
{
	//freopen("endless.in","r",stdin);
	//freopen("endless.out","w",stdout);
	cin>>n>>l>>v;
	for(i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1,cmp);
	now[0]=l;
	for(i=1;i<=n;i++)now[i]=now[i-1]+a[i];
	cin>>m;
	while(m--)
	{
		cin>>l;
		le=0;ri=n;
		ans=-1;
		while(le<=ri)
		{
			mid=(le+ri)/2;
			if(now[mid]>l*v)ans=mid,ri=mid-1;
			else le=mid+1;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
考察的是选手的基本功。

---

## 作者：empty_zhm (赞：3)

# 贪心+分块
## 一、算法解析
### 1.贪心
这个贪心大家都很容易看的出来，由大到小施魔法是最容易达成目的的。证明我就不证了。   
但是裸查询的耗时为 $O(qn)$ 。算一下就知道最大是 $4×10^{10}$ 。这个是绝对接受不了的。于是便需要构思优化。  
### 2.优化  
这里用了分块来优化查询，将排好序的魔法序列分成大小为 $\sqrt{n}$ 的块，预处理加和。 
### 3.分块大小
如果直接开大小 $\sqrt n$ 的块得出最坏时间复杂度 $O(2 \times q \sqrt n)$ ，算是勉强过关。（~~在 TLE 的边缘疯狂试探~~）  
所以我们可以思考优化一下，把均摊复杂度降低，我们尝试使每块前大后小（大小等差为$1$），感性理解一下即可，这样就可以把跳到后面的块所须的多余的时间复杂度均摊到前面的块。然后我们可以得出第一块的大小是为 $\frac{\sqrt{8n+1}-1}{2}$ ，刚好可以覆盖，但是由于是整数，考虑**向上取整**，且为了避免精度（~~奇奇怪怪的~~）问题，取近似值 $\sqrt {2n}$ 即可，时间复杂度为 $O(\sqrt2 \times q\sqrt n)$。（跑起来比前面一个快了 300ms）
## 二、代码
```
#include<bits/stdc++.h>//注意这里的数据范围明显超过了int，所以要开LL
#define LL long long
#define N 1000010
#define s_N 1010
using namespace std;
LL A[N],siz,B[s_N],S[s_N];//B为分块中的和,S为分块边界
int n,L,v;
inline bool cmp(int a,int b){return a>b;}
int solve(LL a)//解决问题
{
	LL sum=L;
	if(sum>a*v) return 0;
	for(int i=1;i<=siz;i++)
	{
		sum+=B[i];//累加一整块
		if(sum>a*v)//答案在刚刚累加的块里
		{
			sum-=B[i];
			for(int j=S[i-1];j<S[i];j++)//在块里逐个累加，知道找到准确答案
			{
				sum+=A[j];
				if(sum>a*v) return j;
			}
		}
	}
	return -1;
}
void get_blank()//分块，并给每个块做累加
{
	int sum=0;
	for(int i=ceil(sqrt(2*n));sum<=n;i--)
	{
		S[siz++]=sum+1;
		sum+=i;
	}
	S[siz]=n+1;
	for(int i=1;i<=siz;i++)
		for(int j=S[i-1];j<S[i];j++)
			B[i]+=A[j];
} 
int main()
{
	cin >> n >> L >> v;
	for(int i=1;i<=n;i++) scanf("%lld",A+i);
	sort(A+1,A+n+1,cmp);
	get_blank();
	int q;
	cin >> q;
	while(q--)
	{
		LL a;
		scanf("%lld",&a);
		cout << solve(a) << '\n';
	}
	return 0;
}
```
$\texttt{updata 2020/12/23}:$ 回想起了之前分块的优化，块的大小有改动。

---

## 作者：LinkZelda (赞：3)

- ###  **思考**：

因为题目要求是至少要从山底走到山顶的，所以那一段路程（**山底 - > 山顶** ）是一定会走的。然后与每一次魔法，因为是让他在 $a_{i}$ 的地方回到起点，所以我们可以看作有 $a_{i}$ 的距离是**白走了的**（用于拖时间），所以找最少要用的魔法次数，可以用贪心的思路，先排序一遍，再从最大的开始，找一次满足的答案，输出。

- ###  **优化**：

如何可以不开 $double$ 来做这题呢? 有一个公式 $S = Vt$ ，我们可以根据这个公式算出最少要的距离，然后就贪心就行  。（考场上突然发现的，~~调 double 调到心累~~）。

- ###  **代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
bool cmp(int a,int b)//自定义从大到小排序
{
	return a>b;
}
int a[200005];
int main()
{
	//freopen("endless.in","r",stdin);
	//freopen("endless.out","w",stdout);
	long long n,q,cnt=0,L,t,v;//不开long long 见祖宗
	scanf("%lld%lld%lld",&n,&L,&v);
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	scanf("%lld",&q);
	sort(a,a+n,cmp);//排序
	for(int i=0;i<q;i++)
	{
		scanf("%lld",&t);
		long long k=t*v;
		k-=L;
		int j=0;
		while(k>=0)//贪心
		{
			k-=a[j];
			j++;
			cnt++;
			if(j==n&&k>=0)//如果魔法用完还没到目的地
			{
				printf("-1\n");//输出-1，无解
				break;//退出循环
			}
		}
		if(k<0)printf("%lld\n",cnt);//如果距离走完了，就输出答案
		cnt=0;//初始化
	 } 
	//fclose(stdin);fclose(stdout);
	return 0;
}
```



---

## 作者：LAWArthur (赞：2)

这题属于机测T2-T3的水准，不难也不算太简单

## 破题

首先我们可以想到把$t_i$乘以$v$，这样题目中所有的数据就都是路程，方便处理也不会丢失精度。

这道题目最终要求的是在$\{a_n\}$中选出$k$个数$b_1,b_2,...,b_k$使$L+\sum b_i>vt$，要求最小化$k$。

我们很容易就能得出我们选的这$k$个数要尽可能大，所以将a从大到小排序。

于是便得到了一种贪心算法：（就给核心代码）

```cpp
for(int i=1;i<=q;i++){
	long long cnt=L;
	int j;
	for(j=0;j<=n;j++){//从0开始就不用特判L>vt的情况 
		cnt += a[j];
		if(cnt > t[i]*v){
			cout << j << endl;
			break;
		}
	}
	if(j>n){//无解 
		cout << -1 << endl;
	}
}
```

这样子的复杂度是$O(nq)$（~~显然过不了~~）

## 优化

经过观察，我们发现这道题目满足一个单调性：
若$t_i<t_j$，则$ans_i<=ans_j$

这又是一道离线问询，然后我们就考虑对问询从小到大排序，这样我们就能用上之前的计算过的东西，能够线性解决这个问题。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//ll是个好习惯 
#define N 200005
ll n,l,v,q,a[N],t[N],id[N];//id数组用来标记排序后各问询的下标 
ll ans[N];
bool cmp(const int &a,const int &b){
	return a>b;
}
bool cmp2(const int &a,const int &b){
	return t[a]<t[b];
}

int main(){
	cin >> n >> l >> v;
	for(int i=1;i<=n;i++){
		cin >> a[i];
	}
	sort(a+1,a+n+1,cmp);
	cin >> q;
	for(int i=1;i<=q;i++){
		cin >> t[i];
		id[i]=i;
	}
	sort(id+1,id+q+1,cmp2);//对问询排序 
	int curl=l,j=0,cnt=0;//curl当前西西弗斯要走的长度，j当前已经用到第j个魔法 
	for(int i=1;i<=q;i++){
		while(curl<=v*t[id[i]]&&j<n)curl+=a[++j]; 
		ans[id[i]] = curl>v*t[id[i]]?j:-1;//注意最后要特判一下无解的情况（已经把魔法用完了） 
	}
	for(int i=1;i<=q;i++){
		printf("%lld\n",ans[i]);//卡常优化
	}
	return 0;
}
```

这样子的复杂度就是$O(n\log n+q\log q)$（因为有排序），能够AC此题。

## 优化2

我们其实还能有一个思路：

由于我们最后用的魔法都是排序后的a数组中从头开始的一段连续区间，因此考虑对a计算一个前缀和。

于是问题就变成了求$min\{i|L+s_i>vt\}$。

看到这个式子，我们不难想到二分。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;//ll是个好习惯 
#define N 200005
#define INF 100000000000005LL
ll n,l,v,q,a[N],t[N],s[N];
ll ans[N];
bool cmp(const int &a,const int &b){
	return a>b;
}

int main(){
	cin >> n >> l >> v;
	for(int i=1;i<=n;i++){
		cin >> a[i];
	}
	sort(a+1,a+n+1,cmp);
	cin >> q;
	for(int i=1;i<=q;i++){
		cin >> t[i];
	}
	
	//前缀和 
	 for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
	 s[n+1]=INF;
	for(int k=1;k<=q;k++){
	//二分答案
		ll lb=0,rb=n+1,mid;
		while(lb<rb){
	 		mid=(lb+rb)>>1;
	 		if(l+s[mid]>t[k]*v)rb=mid;
	 		else lb=mid+1;
		} 
		
		printf("%lld\n",lb>n?-1ll:lb);
	}
	
	return 0;
}
```

这种方法的复杂度为$O(n\log n+q)$（比之前那种还快了一点点）

---

## 作者：rotate (赞：2)

这次考试还没公布成绩，但我也是勉勉强强做出了这题。我的独门秘籍记忆化（题中没提到ti不给重复）算法也用上了。题到不是很难，n循环也还好。但最坑的一点：n<=2*10^9

我当时看到直接蒙了，一脸黑人问号，心跳猛烈，差点就要喊专业团队了（哭笑）

你n循环还搞2*10^9！！！！！！！

（~~出题的人没良心~~）

因此，我的这篇题解的答案很有可能会错上几十分，但用来参考还是行的，~~毕竟这里还没题解~~

A：n循环在哪？？

Q:
你看样例，有三种魔法，也就是说，每个提问只看一种的话，有3种方案。

但是但是但是！！！划重点！！！可以用多种魔法！！！！

n循环可以用递归做粗来，你这n<=2*10^9就太凶了（~~好像在哪里听过~~）

而且，要定义很多变量，看看我的：
```
long long n,l,u,t,k,q,i,j,f,d[200001];
bool pd=false;
double z[200001]={0},ans;
double anj;
```
真凶……

所以我不敢保证全对（~~我感觉能拿70就不错了~~）

话不多说，上代码！！！（~~你这话还少吗……~~）

```
#include<bits/stdc++.h>
using namespace std;
long long n,l,u,t,k,q,i,j,f,d[200001];
bool pd=false;
double z[200001]={0},ans;
void fo(long long i2,long long ans)
{
	if(i2>n) return;
	double anj;
	for(int i1=i2;i1<=n;i1++)
	{
		anj=ans+z[i1];
		if(anj>(double)t && !pd)
		{
			printf("%d\n",i2);
			d[t]=i2;
			pd=1;
			return;
		}
	}
	for(int i1=i2;i1<=n;i1++)
	{
		anj=ans+z[i1];
		fo(i2+1,anj);
	}
}
int main()
{
	freopen("endless.in","r",stdin);
	freopen("endless.out","w",stdout);
	scanf("%d%d%d",&n,&l,&u);
	f=l/u;
	for(i=1;i<=n;i++)
	{
		scanf("%d",&k);
		z[i]+=(double)k/u;
	}
	scanf("%d",&q);
	for(i=1;i<=q;i++)
	{
		scanf("%d",&t);
		pd=0;
		if(t<f) cout<<0<<endl;
		else if(d[t]) cout<<d[t]<<endl;
		else
		{
			ans=f;
			fo(1,ans);
			if(!pd) printf("-1\n");
		}
	}
	return 0;
}

```

freopen我没去，考试要freopen。

~~看看时间，还剩5分钟，反正你们看到时考试结束了,不怕抄袭~~

审核官求过！！！

---

## 作者：_jimmywang_ (赞：2)

首先，我们想到，要使$Sisyphus$推的时间最长，一定要让他在最接近终点的时候，一下掉到山脚，一切重新来过。。。~~可怜~~

于是，我们就有了贪心思路了：按照魔法的使用位置从大到小排序，再一个一个取就行了~~

说明：算每个魔法的贡献值的时候，是不能把原来的长度加进去的。要不然相当于你只算只用当前魔法的贡献，但是魔法是可以一起用的。

所以$magic_i=a_i/v,$其中$magic_0=L/v$

还有一种情况：$-1$

这种情况，我们记一个$mx$,表示所有魔法都用的时候用的时间，如果$mx<=$输入的数，就是$-1$了

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll r() {
	ll x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	if(c=='-')f=-1,c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d r()
ll n;
double l,v;
double a[100010];
bool cmp(double a,double b){return a>b;}
double mag[100010],mx;
int main(){
	n=d;
	cin>>l>>v;
	f(i,1,n)cin>>a[i];
	sort(a+1,a+n+1,cmp);
	mag[0]=l/v,mx=l/v;
	f(i,1,n)mag[i]=a[i]/v,mx+=mag[i];
	ll q=d;
	while(q--){
		double x;
		cin>>x;
		bool fl=0;
		if(l/v>x){cout<<0<<endl;continue;}
		if(mx<=x){cout<<-1<<endl;continue;}
		f(i,0,n){x-=mag[i];if(x<0){cout<<i<<endl;fl=1;break;}}
	}
	return 0;
}

```


---

## 作者：DYH060310 (赞：2)

场外选手悠闲解题

本题我的做法比较特殊（没有用二分）

我的做法：

1.把魔法按照由远到近的顺序排列，因为为了使使用的魔法数量最小，肯定是要先让宙斯使用较远的魔法，让西西弗斯多走一点路

2.处理出从大到小前$i$个魔法能走的路程

3.把询问按照由远到近的顺序排序

因为假如使用第$i$个魔法可以走那么多路，则使用$i+1$个魔法只能走更多的路(答案单调不下降)

因此，我们可以定义一个累加器$tot$，假如有一个点的路程大于从$1 \to tot$的路程，就把$tot$加一

因为答案单调不下降，因此这个做法应该是正确的

4.按照原顺序输出即可

还有一点需要注意，因为处理小数很烦，我们可以把查询的路程同意$*v$，这样就可以保证是整数了

下面贴出代码和数据生成器

希望管理员重新审核，思路仅供参考，把代码拿走了
```
//Data Maker
#include<bits/stdc++.h>
using namespace std;
void fro(int n)
{
	char ipt[20];
	sprintf(ipt,"endless%d.in",n);
	freopen(ipt,"w",stdout);
}
long long mr(long long n)
{
	long long r=rand();
	r^=r<<31;
	r^=r>>17;
	r^=r>>21;
	r^=r<<31;
	r^=r>>21;
	r^=r>>5;
	r^=r>>11;
	r^=r<<20;r^=r>>10;
	return r%n+1;
}
map<int,bool>has;
int main()
{
	srand(time(NULL));
	int n,l,q;
	for(int i=1;i<=20;i++)
	{
		has.clear();
		if(i<=8)
		{
			n=1;
			q=200000;
		}
		else if(i<=12)
		{
			n=2;
			q=200000;
		 } 
		else if(i<=17)
		{
			n=1000,q=1000;
		}
		else
		{
			n=200000,q=200000;
		}
		fro(i);
		int len=mr(1000000)+9000000;
		cout<<n<<" "<<len<<" "<<mr(100000)<<endl;
		for(int j=1;j<=n;j++)
		{
			if(j%5000==0)
			{
				cout<<endl;
			}
			int c=mr(len);
			while(has[c])
			{
				c=mr(len);
			}
			has[c]=1;
			cout<<c<<" ";
		}
		cout<<endl;
		cout<<q<<endl;
		for(int j=1;j<=q;j++)
		{
			cout<<mr(len)<<endl;
		}
	}
} 
```


---

## 作者：coolbreeze (赞：1)

## NOI-online-Round·2 the solution of the first problem.（P6473 [NOI Online #2 入门组]未了）解题报告
#### 这是一篇解题报告，并不是一篇单纯的题解，尽可能的包含了做题的完整思路历程。

这次3题总时长为3.5h，在完整的阅读了各题题面后，发觉T2应该是BFS+图论，图论没学，不可做；T3是个计数递推，我组合数学底子不好，不可做，综上所述，决定先开T1。

**事实证明我的决定是正确的。**

阅读题目，我们可以得到一个重要的性质，每使用一次$a_i=x$的魔法，$Sisyphus$到达山顶的总时长**便增加**$\frac{x}{v}$。

这样以来，为了使使用魔法的次数**尽可能少**，我们需要**尽可能地**增加$Sisyphus$到达山顶的总时长，也就是**尽可能地**使用$a_i$值较大的魔法,增加反复爬上来的时长。看到这里，**贪心**的正确性便是显然的了。

为了选取**尽可能大**的$a_i$,对魔法进行**排序**，**保证数值大的下标在前**，选用快速排序，时间复杂度$O(n\ log\ n)$——本文使用$C++\ STL$自带$sort$。


------------


接着，愉快进行$q$次对$t_i$的查询，手推复杂度，意识到朴素的$O(n*q)$的查询复杂度**并不足以应对此题**。

于是考虑采用**二分查找**以及**累加和**维护复杂度。

首先用**累加和维护$ai$数组**，令$a_i[i]$表示为使用了数值前$i$大的魔法后所能增加的时间——（累加和也可称作**前缀和**，因为本题用不到前缀和的区间查询，所以在此我仅仅把这种方式称作累加和）。

接着**特判两个方面**：

1.**能否用魔法使$Sisyphus$到达山顶使用的年数大于$t_i$**；

2.**是否需要使用魔法**。

最后运用**二分查找**，查找第一个$a_i[i]>t_i$时$i$的位置，输出即可，$q$次查询的总时间复杂度为$O(q*log\ n)$，如此优秀的复杂度，足以应对该题。——本文使用$C++\ STL$自带$upper\_bound$。

**总的时间复杂度为:$O(n\ log\ n+q*log\ n)$。**

**需要注意的点**：计算$\frac{a_i}{v}$时会使用除法运算，用$double$保存可能需要**考虑精度**的问题（该问题待核实）。


------------


### code：

(已在洛谷民间数据AC：[评测地址](https://www.luogu.com.cn/record/33117695))：



```
#include<cstdio>
#include<algorithm>
using namespace std;
double ai[200001];
bool cmp(double a,double b){
	return a>b;
}
int main(){
	//freopen("endless.in","r",stdin);
	//freopen("endless.out","w",stdout);
	int n,q;
	double L,v;
	scanf("%d%lf%lf",&n,&L,&v);
	for(register int i=1;i<=n;i++){
		scanf("%lf",&ai[i]);
		ai[i]/=v;//计算时间。
	}
	scanf("%d",&q);
	sort(ai+1,ai+n+1,cmp);//快速排序。
	int ti=0,ans=0;
	double s=L*1.0/v;
	ai[0]=s;
	for(register int i=1;i<=n;i++)
		ai[i]+=ai[i-1];//累加和.
	for(register int i=1;i<=q;i++){
		scanf("%d",&ti);
		ans=0;
		if(ai[ans]>ti){
			printf("0\n");
			continue;
		}//↕特判
		if(ai[n]<=ti){
			printf("-1\n");
			continue;
		}
		ans=upper_bound(ai+1,ai+n+1,ti)-ai;//二分查找。
		printf("%d\n",ans);
	}
	return 0;
}
```
感谢大家阅读至此，谢谢你们的支持，这是我写题解的最大动力。






---

## 作者：Na2PtCl6 (赞：1)

## 分析题目
这道题我们用贪心+排序+前缀和+二分查找来实现
### 贪心策略：
因为宙斯想让自己用的魔法尽可能少，所以不难发现，我们可以从大到小去取施魔法的值。

为什么呢？因为在一个集合中，如果要选出$n$个值，使其和最大，选择最大的$n$个数即可。而选出若干个数，使其和严格大于t也是一个道理。

### 排序
从大往小排序，辅助贪心。

### 前缀和
我们需要制造**排序后的**魔法数组的前缀和，**最后加上直接从山脚走到山顶的路程，再除以速度v**

### 二分查找
找出前缀和数组中比t大的第一个数,用std::upper_bound()实现

## 代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int n,q;
double L,v,t,a[200004],sum[200004];

int main(){
	cin>>n>>L>>v;
	for(int i=0;i<n;i++)
		cin>>a[i];
	sort(a,a+n,greater<double>());
	//维护前缀和 
	for(int i=0;i<n;i++)
		sum[i]=sum[i-1]+a[i];
	for(int i=0;i<n;i++)
		sum[i]=(sum[i]+L)/v;
	cin>>q;
	for(int i=0;i<q;i++){
		cin>>t;
		//如果不用施魔法就已经满足要求了，就直接输出0 
		if(L/v>t){
			puts("0");
			continue;
		}
		/*找出前缀和数组中比t大的第一个数的下标,
		前缀和数组的单调性保证了此操作的正确性*/ 
		int p=upper_bound(sum,sum+n,t)-sum;
		//如果没有这样的前缀和，即无解 
		if(p==n)
			puts("-1");
		//输出找到的下标加上1，因为数组内的元素是从下标0开始的 
		else
			cout<<p+1<<"\n";
	}
	return 0;
}
```

---

## 作者：wkjwkj (赞：1)

[可能更好的阅读体验](http://mywkj.github.io/2020/04/25/noi-online-2-ru-men-zu-wei-liao-ti-jie/)

~~考试时想了半天才做出~~

- 首先考虑宙斯**最少**需要施展多少个魔法才能使 Sisyphus 到达山顶所用的年数**大于** $t_i$那么根据贪心的思想，我们可以先将每个魔法以生效距离由长到短排序。(即能做到每个魔法使 Sisyphus 增加$a_i/v$年的时间)
- 接下来我们就可以愉快的使用前缀和+二分来解决我们的问题了，定义一个$sum$数组，令$sum_0=l*1.0/v$接下来对于每个$sum_i$均执行$sum[i]=sum[i-1]+a[i]*1.0/v$。对于每个询问$x$，我们只需在$sum$数组二分查找**第一个**比$x$大的数字，此时的$i$即为所求的答案

代码如下(手写二分)

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
double sum[200005];
bool cmp(int x,int y)
{
	return x>y;
}
int main()
{
	freopen("endless.in","r",stdin);//文件输入输出，请自行注释
	freopen("endless.out","w",stdout);
	int n,l,v;
	scanf("%d%d%d",&n,&l,&v);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1,cmp);
	sum[0]=l*1.0/v;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+a[i]*1.0/v;//前缀和
	int q;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		int x;
		scanf("%d",&x);
		if(sum[0]>(x*1.0)){//特判
			puts("0");
			continue;
		}
		if(sum[n]<=(x*1.0)){//特判
			puts("-1");
			continue;
		}
		int l=1,r=n;
		while(l<r)//手写二分
		{
			int mid=(l+r)>>1;
			if((x*1.0)>=sum[mid])l=mid+1;
			else r=mid;
		}
		printf("%d\n",l);
	}
	//printf("sum[n]=%lf",sum[n]); 
	return 0;
 } 
```



---

## 作者：pengyule (赞：1)

## 由于这是我这次比赛唯一做出来的一道题，我一定要发这篇题解！
我们知道 Sisyphus 他要推石头，然后假设我们是邪恶的宙斯，怎么样才能让他白费的力气最大——我们要尽量让他爬得更多，浪费掉更多的时间，再滚下去，这样子就会耗费他最多的时间，所以我们每一次都要选择高度最高的那一种魔法（贪心思路）。因此，我们把他的魔法的高度从大到小排个序。

排完序之后，我们就来看一下，如果我们使用一个魔法，可不可以达到目标啊？如果不行，如果我们再多使用一个魔法，可不可以达到不目标啊？其实啊，这就是一个查找的过程。查找什么呢？就是我们想要找到一个 $i$，使得我们使用魔法使用到第 $i$ 大的时候，Sisyphus 就必须用**大于** $t$ 年爬到山顶。考虑到数据范围不可能去挨个看“用这个行不行啊？再用一个下一个行不行啊？……”因为这样肯定会超时。

我们知道，其实有更快的查找方式——二分。下面阐述具体的查找过程，不会二分的同学需要先另行去系统地学习一下。

为了避免小数的出现，我们可以转化一下，不一定要把规定年数 $t$ 去和用 $i$ 次魔法的最大效应的 Sisyphus 所用总时间去做比较，我们可以把用 $i$ 次魔法的最大效应的 Sisyphus 所用**总路程**去和规定时间用速度 $v$ 走需要走的路程去做比较。我们需要找到一个 $i$，使得我们用 $i$ 次最好的魔法让 Sisyphus 所需要走的总路程恰好大于用规定时间所需走的总路程 _（再次强调，是“**大于**”，不是“大于等于”，很容易看错）_ ，并且使这个 $i$ 最小。 于是我们写下下面这个二分模板：
```cpp
while(l<r-1){
    mid=(l+r)/2;
    if(num[mid]>v*t)r=mid;
    else l=mid;
}
```
其中 $num_{i}$ 是使用 $i$ 次魔法所能让 Sisyphus 走的最长路程，而 $v,t$ 分别是 Sisyphus 的速度与查询的时间。想一想，是不是这样呢？这样，我们的程序也就写的差不多了。只需要再写一写前面对 $num$ 的预处理啦，读入输出啦，这些东西。具体细节见代码。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
ll n,q,L,v,a[200010],t,num[200010];//如题所示，其中num[i]是使用i次魔法所能让Sisyphus走的最长路程
bool cmp(ll x,ll y){
    return x>y;
}//从大到小
int main()
{
	 freopen("endless.in","r",stdin);
	 freopen("endless.out","w",stdout);
    scanf("%d%lld%lld",&n,&L,&v);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    sort(a+1,a+n+1,cmp);//排序
    num[0]=L;//如果根本不用使用魔法（用0次，所以是num[0]）
    for(int i=1;i<=n;i++) num[i]=num[i-1]+a[i];//num预处理
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
		scanf("%lld",&t);
		int l=-1,r=n+1,mid;
        while(l<r-1){
            mid=(l+r)/2;
            if(num[mid]>v*t)r=mid;
            else l=mid;
        }//二分查找
        if(r==n+1) printf("-1\n");//找不到
        else printf("%d\n",r);
    }
    return 0;
}//这是比赛时的代码，若要提交洛谷，请自行注释freopen
```

---

## 作者：lory1608 (赞：1)

很简单的一到二分。

显然肯定是选大的魔法，所以可以将$a_i$从大到小排序，然后算个前缀和，二分即可。

二分出第一个**严格大于**$t\times v-l$的数就行了，可以自己手写二分或用$STL$的$upper$$_$$bound()$。

复杂度$(n+q)\log n$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#define ll long long
#define ull unsigned long long
using namespace std;
const int maxn=2e5+5;
ll n,l,v,q;
ll a[maxn],t,pre[maxn];
inline ll binary_search(ll x)
{
	int l=0,r=n,ans=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(pre[mid]>x)
		{
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	return ans;
}
int main()
{
	freopen("endless.in","r",stdin);
	freopen("endless.out","w",stdout);
	scanf("%lld%lld%lld",&n,&l,&v);
	for(int i=1;i<=n;++i)scanf("%lld",&a[i]);
	sort(a+1,a+n+1,greater<int>());
	for(int i=1;i<=n;++i)pre[i]=pre[i-1]+a[i];
	scanf("%d",&q);
	for(int i=1;i<=q;++i)
	{
		scanf("%lld",&t);
		if(t*v>=pre[n]+l)printf("-1\n");
		else printf("%d\n",binary_search(t*v-l));
	}
	return 0;
}
```

---

## 作者：_CloudySky_ (赞：1)

这道题不用二分！！！

- 其实不难想到，高度高的魔法比高度低的魔法要顶用，所以优先考虑用高度高的魔法。

- 其次，这道题不要求在线，可以将查询从小到大排序后离线扫一遍。

- 最终复杂度 $O(nlogn)$。

再说细节：

这道题大家应该都能想到要用前缀和。

- 不用魔法是，需要爬的高度就是 坡长。

- 用上最高的魔法时，高度即是 坡长+使用最高魔法的高度。

- 再用上次高的魔法时，高度即是 坡长+使用最高魔法的高度+使用次高魔法的高度。

- 以此类推

所以我们可以用前缀和来维护。

将 ans 数组初始化为 -1。因为排序过，所以询问数组满足单调性，前面无法做到，后面就更无法作到，所以如果扫到哪里发现做不到，就直接 break。

记着开 long long ！！！

Code for P6473 [NOI Online #2 入门组]未了：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm> 
#include<cstring>
#define int long long
const int Maxn=200010;
using namespace std;

int a[Maxn],s[Maxn],ans[Maxn];

struct Ask{
	int id,que;
	bool operator<(const Ask x)const{
		return que<x.que;
	}
}Q[Maxn];

bool cmp(int a,int b){
	return a>b;
}

signed main(){
//	freopen("endless.in","r",stdin);
//	freopen("endless.out","w",stdout);
	
	int n,L,v,q;
	scanf("%lld%lld%lld",&n,&L,&v);
	a[0]=L,s[0]=L;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	
	scanf("%lld",&q);
	for(int i=1;i<=q;i++){
		scanf("%lld",&Q[i].que);
		Q[i].que*=v;
		Q[i].id=i;
	}
	
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+a[i];
	}
	
	sort(Q+1,Q+q+1);
	int j=0;
	memset(ans,-1,sizeof(ans));
	for(int i=1;i<=q;i++){
		while(s[j]<=Q[i].que&&j<=n)j++;
		if(s[j]>Q[i].que)ans[Q[i].id]=j;
		else break;
	}
	
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
	return 0;
}
```


---

## 作者：HJY202three (赞：1)

# Update 5/13
不敢相信我竟然爆零了。发现题解代码有误，那我就给个没错的代码吧
```cpp
#include<cstdio>//O(nlogn)
#include<algorithm>
using namespace std;
long long a[100000];
long long length[100000];
bool cmp(long long x,long long y){return x>y;}
int main()
{
//	freopen("endless.in","r",stdin);
//	freopen("endless.out","w",stdout);
	long long n,l,v,q;
	scanf("%lld %lld %lld",&n,&l,&v);
	//printf("n=%d,l=%d,v=%d",n,l,v);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		//printf("a[%d]=%d\n",i,a[i]);
	}
	scanf("%lld",&q);
	//printf("q=%d\n",q);
	sort(a+1,a+1+n,cmp);
	length[0]=l;
	//printf("max_use_%d_magic_l=%d\n",0,t[0]);
	for(int i=1;i<=n;i++)
	{
		length[i]=length[i-1]+a[i];
		//printf("max_use_%d_magic_l=%d\n",i,t[i]);
	}
	for(int i=1;i<=q;i++)
	{
		long long tx;
		scanf("%lld",&tx);
		tx*=v;
		bool have=false;
		long long xyx=upper_bound(length,length+1+n,tx)-length;
		if(xyx>n)printf("-1\n");
		else printf("%lld\n",xyx);
	}
	return 0;
}
```
----

这道题就是一个人，往上走，有一种魔法可以让这个人在走到ai的高度时下来。

## 1.0版本：O(n*n!)

首先最容易想到的办法就是直接暴力搜索，每一个魔法都有选和不选的两种方案。那我们就可以打一个O(n*n!)复杂度的代码。

然而这种算法太慢了，n=十几就爆炸了...

代码就不贴了...

~~什么？？你非得让我贴？？好吧，告诉你，我不会.~~

## 2.0版本：O(n*n)

考虑第一个subtask~~或者什么**东西~~

我们可以算出不用魔~~膜~~法和用的时间，然后判断一下，伪代码如下：
```
var x=不用魔法的时间
var x2=用魔法的时间
t<x:0
x<t<x2:1
else -1
```
那么我们想想可不可以把这种方法推广。

先看一组样例：设宙斯有5种魔法，西西弗斯的速度为2,山的高度为10，作用地点值分别为
$$ 1 \space 5 \space 3 \space 4 \space 2$$
那么想想看，如果宙斯用一个膜法，最多能够使得他的多走多少时间呢？~~（作者提示：这是一个用脚都能想出来的问题）~~
如果宙斯选择最大的一个，就能使他走的时间变得更多

那如果选两个呢??当然是选第一大的和第二大的啦。

因为这题没有让我们输出都用了哪些魔法如果让我们输出~~那我就不会了~~所以可以在输入a了之后，建一个预处理数组time，表示使用n个魔法时西西弗斯的最大上山时间(注意要用double)，然后用for循环判断哪一个时间刚好大于宙斯询问的时间。如果询问的时间比time[n]还要大，那么输出-1

code:
```cpp
#include<cstdio>//O(n^2)
#include<algorithm>
using namespace std;
int a[100000];
double time[100000];
bool cmp(long long x,long long y){return x>y;}
int main()
{
//	freopen("endless.in","r",stdin);
//	freopen("endless.out","w",stdout);
	int n,l,v,q;
	scanf("%d %d %d",&n,&l,&v);
	//printf("n=%d,l=%d,v=%d\n",n,l,v);
	double T=l*1.0/v;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		//printf("a[%d]=%d\n",i,a[i]);
	}
	scanf("%d",&q);
	//printf("q=%d\n",q);
	sort(a+1,a+1+n,cmp);
	time[0]=T;
	//printf("max_use_%d_magic_time=%f\n",0,time[0]);
	for(int i=1;i<=n;i++)
	{
		time[i]=time[i-1]+a[i]*1.0/v;
		//printf("max_use_%d_magic_time=%f\n",i,time[i]);
	}
	for(int i=1;i<=q;i++)
	{
		int tx;
		scanf("%d",&tx);
		bool have=false;
		for(int j=0;j<=n;j++)
		{
			if(time[j]>tx)
			{
				printf("%d\n",j);
				have=true;
				break;
			}
		}
		if(!have)printf("-1\n");
	}
	return 0;
}
```
## 3.0版本：O(nlogn)
观察O(n*n)的代码，我们会发现time数组满足一个规律：
$$如果x>y,则time[x]>time[y]$$

那么，这个序列就是个不下降的序列。那么，你想起了什么？

对了，就是二分查找。我们可以使用stl中的upper_bound函数。这个函数可以返回序列中的第一个大于x的数。刚好满足我们的要求。优化后的代码如下：
```cpp
#include<cstdio>//O(nlogn)
#include<algorithm>
using namespace std;
int a[100000];
double time[100000];
bool cmp(long long x,long long y){return x>y;}
int main()
{
//	freopen("endless.in","r",stdin);
//	freopen("endless.out","w",stdout);
	int n,l,v,q;
	scanf("%d %d %d",&n,&l,&v);
	printf("n=%d,l=%d,v=%d\n",n,l,v);
	double T=l*1.0/v;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		//printf("a[%d]=%d\n",i,a[i]);
	}
	scanf("%d",&q);
	//printf("q=%d\n",q);
	sort(a+1,a+1+n,cmp);
	time[0]=T;
	//printf("max_use_%d_magic_time=%f\n",0,time[0]);
	for(int i=1;i<=n;i++)
	{
		time[i]=time[i-1]+a[i]*1.0/v;
		//printf("max_use_%d_magic_time=%f\n",i,time[i]);
	}
	for(int i=1;i<=q;i++)
	{
		int tx;
		scanf("%d",&tx);
		long long xyx=upper_bound(time,time+1+n,tx)-time;
		if(xyx>n)printf("-1\n");
		else printf("%lld\n",xyx);
	}
	return 0;
}
```
## 3.1版本 精度优化
因为如果每次都去算时间可能会有浮点数的精度误差，所以我们可以用路程替换时间

比如宙斯想要使得时间大于5，西西弗斯的速度是2，那么就相当于求使得西西弗斯的路程大于10.

高度为ai的魔法其实就是让他的路程增加ai，这里让大家想一想为啥。

code(我知道你们就看这里):
```cpp
#include<cstdio>//O(nlogn)
#include<algorithm>
using namespace std;
long long a[100000];
long long length[100000];
bool cmp(long long x,long long y){return x>y;}
int main()
{
//	freopen("endless.in","r",stdin);
//	freopen("endless.out","w",stdout);
	long long n,l,v,q;
	scanf("%lld %lld %lld",&n,&l,&v);
	//printf("n=%d,l=%d,v=%d",n,l,v);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		//printf("a[%d]=%d\n",i,a[i]);
	}
	scanf("%d",&q);
	//printf("q=%d\n",q);
	sort(a+1,a+1+n,cmp);
	length[0]=l;
	//printf("max_use_%d_magic_l=%d\n",0,t[0]);
	for(int i=1;i<=n;i++)
	{
		length[i]=length[i-1]+a[i];
		//printf("max_use_%d_magic_l=%d\n",i,t[i]);
	}
	for(int i=1;i<=q;i++)
	{
		long long tx;
		scanf("%lld",&tx);
		tx*=v;
		bool have=false;
		long long xyx=upper_bound(length,length+1+n,tx)-length;
		if(xyx>n)printf("-1\n");
		else printf("%lld\n",xyx);
	}
	return 0;
}
```
# 谢谢观看！！

---

## 作者：Chouquet (赞：0)

这道题看上去很难，其实~~也很难~~很简单（~~事实上赛时我写了近两个小时才写好~~

首先一看数据规模：$1 \le n,q \le 2 \times 10^5$！$O(qn)$的模拟就不用想了，肯定超时；再看其余的都$\le 10^9$，DP也不用考虑了，肯定MLE。

其实本题正解是贪心+二分，方法如下：

首先将$a[i]$从大到小排序（因为$a[i]$尽可能大的话西西弗斯爬到山顶的时间就越长，也就有更多的可能超过$t_i$，自己想一想就知道了）。

排好了以后，再用**前缀和**来加上西西弗斯从山脚爬到$a[i]$处所需的时间，即$\frac{a[i]}{v}$，因为根据样例解释可以发现从山脚到山顶的时间是固定的，也就是说只需要做$\frac{a[i]}{v}$的前缀和就行了，最后再单独加上从山脚到山顶的时间。

然后每次询问时查找就行了。

代码：
```cpp
#include <cstdio>
#include <algorithm>
bool cmp(int x,int y){return x>y;}
int n,l,v,a[200003],q,t;double y,s[200003];
int main(){
	scanf("%d%d%d",&n,&l,&v);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	std::sort(a+1,a+1+n,cmp);//排序
	y=1.0*l/v;y=从山脚到山顶的时间
	for(int i=1;i<=n;i++) s[i]=s[i-1]+1.0*a[i]/v;//前缀和
	scanf("%d",&q);
	while(q--){
		scanf("%d",&t);
		if(s[n]+y<=t) printf("-1\n");//如果连所有的魔法都用完后时间仍然不能大于t，则输出-1
		if(y>t) printf("0\n");//如果不用魔法上山的时间都比t要大，输出0
		else ……;//顺序查找一遍，这个应该会写吧
	}
	return 0;
}
```
代码写到这里时就不难发现，因为s数组是不降的，所以else处直接用二分就行了(upper_bound也可以)。这样总时间复杂度是$O(qlogn)$，肯定不会超时。

完整代码：
```cpp
#include <cstdio>
#include <algorithm>
bool cmp(int x,int y){return x>y;}
int n,l,v,a[200003],q,t;double y,s[200003];
int main(){
	scanf("%d%d%d",&n,&l,&v);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	std::sort(a+1,a+1+n,cmp);//从大到小排序
	y=1.0*l/v;//算从山脚到山顶不用魔法的时间
	for(int i=1;i<=n;i++) s[i]=s[i-1]+1.0*a[i]/v;//前缀和
	for(int i=1;i<=n;i++) s[i]+=y;//方便后面的判断，都加上y
	scanf("%d",&q);
	while(q--){
		scanf("%d",&t);
		if(s[n]<=t) printf("-1\n");//意义如前面的代码
		if(y>t) printf("0\n");//这个也是的
		else{
			int p=std::upper_bound(s+1,s+1+n,t)-s;//求最小的s[i]使其>t，p=s[i]在s中的位置
			if(s[p]>t) printf("%d\n",p);//最好加上这一句，因为要保证s[p]>t
		}
	}
	return 0;//完美地结束了
}
```
对了，补充一句，关于[Sisyphus](https://baike.baidu.com/item/西西弗斯/6690210?fromtitle=Sisyphus&fromid=5322905&fr=aladdin)

---

