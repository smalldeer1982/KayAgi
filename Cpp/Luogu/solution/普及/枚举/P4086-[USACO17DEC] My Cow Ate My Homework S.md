# [USACO17DEC] My Cow Ate My Homework S

## 题目描述

在你的牛历史课上，你被布置了一份相当长的作业，包含 $N$ 个问题（$3 \leq N \leq 100,000$），每个问题的得分是一个在 0 到 10,000 之间的整数。按照惯例，你的老师计划通过去掉你得分最低的一个问题，然后对剩余问题的得分取平均来给出最终成绩。不幸的是，你的宠物奶牛 Bessie 刚刚吃掉了你前 $K$ 个问题的答案！（$K$ 可能小到 1，也可能大到 $N-2$）。

经过多次解释，你的老师终于相信了你的说法，并同意按照之前的方式对剩余的未被吃掉的部分作业进行评分——即去掉得分最低的问题（或在得分相同的情况下去掉其中一个），然后对剩余问题取平均。

请输出所有能够使你获得最高可能成绩的 $K$ 值，并按升序排列。

## 说明/提示

如果 Bessie 吃掉了前两个问题，那么剩余的得分是 9、2 和 7。去掉最低分并取平均后，最终成绩为 8，这是可能的最高成绩。

## 样例 #1

### 输入

```
5
3 1 9 2 7```

### 输出

```
2```

# 题解

## 作者：_jimmywang_ (赞：28)

此题，$emmmm...$

其实简化一下题目，就是在从$a_{k+1}$到$a_n$里找一个最小值，并把它去掉，再算剩下的几个数的平均值，求是这个平均值最大的$k$

那么，其实就是$3$部分：最小值、平均数、求平均数最大值。

一个一个看：

### $1.$

最小值的朴素解法是什么？$O(n)$扫一遍啊

但是我们还要遍历一次$k$从$1$到$n$，而且如果求平均值也是$O(n)$的话，总的来说就是$O(n^3)$了，绝对爆炸。

想一想，我们不用每次都求最小值啊，一开始就预处理掉不就好了，反正是静态的

于是就有了这份代码：

```
for(int i=n;i>=2;i--)mn[i]=min(mn[i+1],a[i]);
```
就这么一行？

对，就这么一行。

这样，我们就能$O(1)$求最小值啦~~

### $2.$

平均值。。。

要求平均值，就要知道一个区间的和

和最小值一样，朴素的方法是$O(n)$的

但是我们还要遍历一次$k$从$1$到$n$，总的来说又是$O(n^2)$了，还是炸了。

但是我们有什么？前缀和啊！

而且这里还不用前缀和，只要倒着一个一个加，还能合并到上面最小值代码里

于是就是这样了：

```
for(int i=n;i>=2;i--)mn[i]=min(mn[i+1],a[i]),sum[i]=sum[i+1]+a[i];
```
就这么一行？

对，还是就这么一行。

于是，$O(1)$求平均值也$OK$啦~~

### $2.5:$

其实平均数也能与处理啊，就是

```
(sum[i]-min[i])/(n-i)
```
嘛

于是就是这样了：

```
for(int i=n;i>=2;i--){
    mn[i]=min(mn[i+1],a[i]);
    sum[i]=sum[i+1]+a[i];
    if(i!=n)avr[i]=(sum[i]-mn[i])/(double)(n-i);
}
```
再就是比较了，此处不再说明。

完整代码：

```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll n;
double a[1000010];
double avr[1000010];
double sum[1000010];
double mn[1000010];
double mx;
int main(){
	n=d;
	f(i,1,n+1)mn[i]=10010;
	f(i,1,n)scanf("%lf",&a[i]);
	for(int i=n;i>=2;i--){
		mn[i]=min(mn[i+1],a[i]);
		sum[i]=sum[i+1]+a[i];
		if(i!=n)avr[i]=(sum[i]-mn[i])/(double)(n-i);
	}
	f(i,2,n-1)mx=max(mx,avr[i]);
	f(i,2,n-1)if(mx==avr[i])printf("%lld\n",i-1);
	return 0;
}
```


---

## 作者：Siyuan (赞：17)

## 本题思路：

1. 按正常思维读入题目所述的所有数据。暂时不做任何预处理。


2. 定义关键变量：mins表示当前区间内的最小成绩，sum表示当前区间内成绩总和，aver表示当前已知最大平均成绩。


3. 用前缀和的思想，枚举区间，也就是枚举k的值，递推求出最优解，存在数组k中。（详见代码注释）


~~（**最优解**保持者！2018.1.23提交）~~


上代码

```cpp
#include<cstdio>
#define min(a,b) (a<b?a:b)
#define rep1(i,a,b) for(register int i=a;i<=b;i++)
#define rep2(i,a,b) for(register int i=a;i>=b;i--)
//请自行忽略以上define……
using namespace std;
int n,k[100002],cnr=0;     //cnr表示k的数量，初始为0
int s[100002],mins,sum;
double aver=0;
inline int read()     //快读
{
    int s=0;
    char c=getchar();
    while(c<'0'||c>'9')  c=getchar();
    while(c>='0'&&c<='9')
    {
        s=(s<<1)+(s<<3)+c-'0';
        c=getchar();
    }
    return s;
}
int main()
{
    n=read();
    rep1(i,1,n)  s[i]=read();     //按照正常思路读入
    mins=s[n];  sum=s[n];     //将当前的mins（区间[n,n]最小成绩）赋为s[n]；将当前的sum（区间[n,n]总成绩）赋为s[n]
    rep2(i,n-1,2)     //枚举区间左界i，即枚举区间[i,n]
    {
        mins=min(mins,s[i]);     //区间[i,n]中的最小成绩（前缀和思想）
        sum+=s[i];     //区间[i,n]中的总成绩（依旧是前缀和思想……）
        if((sum-mins)/(double)(n-i)>aver)     //如果总成绩除去最小成绩后的平均成绩小于当前最大平均成绩
        //注意：区间[i,n]中原本有n-i+1个元素，然而除去了最小元素，故有n-i个元素
        {
            cnr=1;     //cnr的值变为0，因为此时有其他k的值使得平均成绩大于当前最大平均成绩
            k[cnr]=i-1;     //k的值为：区间左界-1
            aver=(sum-mins)/(double)(n-i);     //更新最大平均成绩
        }else  if((sum-mins)/(double)(n-i)==aver)     //如果当前平均成绩也是最大平均成绩
            k[++cnr]=i-1;     //k的数量增加1，且将此时的k的值存入数组
    }
    rep2(i,cnr,1)  printf("%d\n",k[i]);     //因为在递推过程中，k的值是降序存入数组的，故此时要逆序输出使得k的值升序
    return 0;     //完美地结束
}
```

看到楼上大佬的代码开了3个double数组、用了好多次for、过程也挺繁琐的……


本人蒟蒻，题解如果有误请各位大佬纠正！


---

## 作者：TRZ_2007 (赞：7)

**题解 [P4086 【[USACO17DEC]My Cow Ate My Homework S】](https://www.luogu.com.cn/problem/P4086)**  
# Description  
给你一串长度为 $n$ 的数组，在去掉前 $k$ 个数字和剰下来数字中**最小**的数字后，将剩下来的数字求**平均值**，使得平均值**最大**，求满足条件的**所有** $k$ 的值，把这些 $k$ **换行输出**。  
# Solution  
这题我们考虑前缀和，设 $\text{sum}(i)$ 表示区间 $[1,i]$ 中所有数字的和，$\min(i)$ 表示**区间 $[i,n]$** 之间所有数字的最小值。接下来枚举 $k$ 的**所有可能取值** ,并确定 **最大数字** 后找到所有的 $k$ 并且输出即可。  
# Code
```
#include <bits/stdc++.h>
using namespace std;

const int N = 1000009;
const double eps = 0.00000000000217;//确定最小精度，不然可能会出错

int sum[N],n,Min[N],a[N];
double Score,Max;

template<class T>
inline void read(T& x) {//快读
	x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
}

int main() {
	read(n);
	sum[0] = 0;Min[n + 1] = 2147483647;
	for(int i = 1;i <= n;i++) {
		read(a[i]);
		sum[i] = sum[i - 1] + a[i];//前缀和
	}
	for(int i = n;i >= 1;i--) {
		Min[i] = min(Min[i + 1],a[i]);//后缀最小值
	}
	for(int i = 1;i <= n - 2;i++) {//枚举所有满足条件的k值
		Score = (sum[n] - sum[i] - Min[i]) * 1.0 / (n - i - 1);//计算式子
		if(Score - Max >= eps) {//确定最大值
			Max = Score;
		}
	}
	for(int i = 1;i <= n - 2;i++) {
		Score = (sum[n] - sum[i] - Min[i]) * 1.0 / (n - i - 1);
		if(fabs(Score - Max) < eps) printf("%d\n",i);//找到所有的k并且输出
	}
	return 0;
}
```  
本算法时间复杂度为$\Theta(n)$。

---

## 作者：SuperJvRuo (赞：7)

只需要注意实数运算的一些问题（如精度）即可AC

```cpp
#include<cstdio>
#include<cctype>
#define EPS 1e-6
//实数比较大小，要带EPS
 
inline int Read()//快读 
{
    int x = 0;char c = getchar();
    while(!isdigit(c))
        c = getchar();
    while(isdigit(c))
    {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    return x;
}

double score[100005], minn[100005], grade[100005], maxn=0.0, sum=0.0;

int main()
{
    int n=Read();
    for (int i = 1; i <= n; ++i)
    {
        score[i] = Read();//记录每道题的得分 
        sum += score[i];//预处理得分总和 
    }
    minn[n] = score[n];
    for (int i = n - 1; i; --i)
        minn[i] = score[i] < minn[i + 1] ? score[i] : minn[i + 1];
    //minn数组代表[i,n]区间内的最低分 
    for (int i = 1; i <= n - 2; ++i)
    {
        sum -= score[i];
        //此时的sum为[i + 1, n]区间内的分数和 
        grade[i] = (sum - minn[i + 1]) / (double)(n - i - 1);
        maxn = grade[i] > maxn ? grade[i] : maxn;
        //maxn代表最高平均得分 
    }
    
    for (int i = 1; i <= n - 2; ++i)
    {
        if (maxn - grade[i] < EPS && maxn - grade[i] > - EPS)
        //即maxn==grade[i] 
            printf("%d\n", i);
    }
    return 0;
}
```

---

## 作者：Diamiko (赞：7)

这题的思路还是非常简单的，使用线段树来维护区间最小值和区间和，枚举k值，统计答案。

每次枚举的k，如果使得平均成绩大于当前最大平均成绩，就更新当前的最大平均成绩，清空答案数组，放入这个k值。

如果这次平均成绩等于当前最大平均成绩，那么直接把k值加入答案数组。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char c;int res=0,flag=1;
	for(;!isdigit(c);c=getchar())if(c=='-')flag=-1;
	for(;isdigit(c);c=getchar())res=res*10+c-'0';
	return res*flag;
}
const int N=100010;
int n;
int sum[N<<2],Min[N<<2];
int s,minn;
double last;
vector<int>ans; 
void build(int i,int l,int r)
{
	if(l==r)
	{
		sum[i]=Min[i]=read();
		return;
	}
	int mid=l+r>>1;
	build(i<<1,l,mid);
	build(i<<1|1,mid+1,r);
	sum[i]=sum[i<<1]+sum[i<<1|1];
	Min[i]=min(Min[i<<1],Min[i<<1|1]);
}
void query(int i,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)
	{
		s+=sum[i];
		minn=min(minn,Min[i]);
		return;
	}
	int mid=l+r>>1;
	if(x<=mid)query(i<<1,l,mid,x,y);
	if(y>mid) query(i<<1|1,mid+1,r,x,y);
}
int main()
{
	n=read();
	build(1,1,n);
	for(int k=1;k<=n-2;k++)
	{
		// k+1  ->  n
		minn=INT_MAX;
		s=0;
		query(1,1,n,k+1,n);
		double score=(s-minn)*1.0/(double)(n-k-1);
		if(score>last)
		{
			ans.clear();
			ans.push_back(k);
			last=score;
		}
		else if(score==last)
		{
			ans.push_back(k);
		}
	}
	for(int i:ans)
	{
		printf("%d\n",i);
	}
	return 0;
}
```

---

## 作者：philosopherchang (赞：4)

一开始看见想用线段树，后来发现暴力就行，于是暴力就来了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],sum[100001],mi[100001];//用int,不用double,这里用double会wa两个点。
int n;
int main()
{
	cin>>n;
	memset(mi,7873833,sizeof(mi));//mi是区间最小值，要在这里先赋一个大于100000的值，为什么大于100000请去看题。
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];//前缀和
	}
	for(int k=n-2;k>=1;k--)//从后向前，因为前面的数是会被吃掉的~~我也想要一只这样的宠物QAQ~~。
	{
		mi[k]=min(mi[k+1],a[k]);
	}
	double maxn=0.0,minn=1938120.0;//double,要用double，不然wa七个点。
	for(int k=1;k<=n-2;k++)
	{
		maxn=max((sum[n]-sum[k]-mi[k])/(double)(n-k-1),maxn);//预处理，统计最大值（注意精度，用double）。
	}
	for(int k=1;k<=n-2;k++)
	{
		if((sum[n]-sum[k]-mi[k])/(double)(n-k-1)==maxn)//注意精度，用double。
		cout<<k<<endl;//直接输出即可，反正是从前往后枚举。
	}
}
```

---

## 作者：AveMarina (赞：2)

# 线段树+前缀和+STL
### 思路
我们可以先模拟下暴力计算的过程，即**枚举从当前成绩$i$开始到第$n-2$个成绩的和，顺便记录这段区间内的最小值**然后计算平均分并与最高平均分对比。

那么我们想下能不能优化这个过程，__对于求和而言，我们可以发现成绩是不会发生改变的，即某段区间内的成绩之和是固定值。__ 那么我们就能够想到利用 __前缀和__ 预处理下每一段区间的成绩和，然后枚举区间起点与终点并做差即可得到这**一段区间内的成绩之和**。

接下来考虑下怎么算这段区间的最小值。首先考虑下暴力，枚举每个分数然后记录下来，复杂度为$O(n)$，妥妥的 __超时__。 那么我们考虑下线段树，__用一个线段树维护所有区间的最小值__，然后枚举区间直接查询，复杂度为$O(logn)$，能过这个题。而且因为这个题没有修改要求，所以可以不写修改函数。

最后想想怎么记录答案，因为 __可能存在很多个满足条件的区间__~~事实上用例里就一个~~ ，所以这里我选择 __STL里的vector__ 来存放答案。

```
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long LL;
const int N = 100000 + 100, M = N * 4;
int arr[N], root[M];
LL s[N];
vector<int > res;
// 建立线段树
void build(int now, int left, int right) {
	// 如果走到了叶子节点，将其赋值
	if (left == right) {
		root[now] = arr[left];
		return;
	}
	int mid = (left + right) >> 1;
	int l_node = now << 1, r_node = now << 1 | 1;
	build(l_node, left, mid);
	build(r_node, mid + 1, right);
   // 当前节点的最小值就是它的左右子节点的最小值
	root[now] = min(root[l_node], root[r_node]);
}
int query(int now, int left, int right, int L, int R) {
	// 如果已经找到了合法区间，就可以直接返回答案从而提升效率
	if (L <= left && right <= R) return root[now];
   // 避免无意义查询
	if(L > right || R < left) return 1e9;
	int mid = (left + right) >> 1;
	int l_node = now << 1, r_node = now << 1 | 1;
   // 返回区间最小值
	return min(query(l_node, left, mid, L, R), query(r_node, mid + 1, right, L, R));
}
int main() {
	int n;
	scanf("%d", &n);
	s[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
     	// 预处理前缀和，注意开long long防止溢出
		s[i] = s[i - 1] + arr[i];
	}
	build(1, 1, n);
	double temp, maxScore = -1e9;
	for (int i = 1; i <= n - 2; i++) {
    // 计算平均分，注意这里的+.0将前面这个式子转换为double类型，否则答案就是个整形！
		temp = (s[n] - s[i] - query(1, 1, n, i + 1, n) + .0) / (n - i - 1);
     // 如果出现了新的最大值，清空结果，然后更新最大值
		if (temp > maxScore) maxScore = temp, res.clear();
     // 如果当前分数是最高分，就将它加入到结果里
		if (temp == maxScore) res.push_back(i);
	}
	int rLen = res.size();
    // 最后输出结果
	for (int i = 0; i < rLen; i++) printf("%d\n", res[i]);
	return 0;
}
```

---

## 作者：大头冲锋车丶 (赞：2)

**线段树简单应用**

**思路：**

线段树维护区间最小值以及区间和

然后枚举k（ i ≤ k ≤ n - 2 ） ，将[1 , n ] 分为 多个[ 1 + k ,n ]，取这所有区段的按题目所说的平均值

用flag数组存储相同平均值的 k 值，cnt来标记元素个数。若当前区段平均值大于之前的平均值，则清除flag数组，重新存入新的 k 值。

**代码如下：**
```cpp
#include<bits/stdc++.h>
#define MAXN 100008
#define lson root<<1
#define rson root<<1|1
using namespace std;
int n, a[MAXN], flag[MAXN];
int ans, m, cnt;
struct Tree
{
    int l, r;
    int  mmin, sum;
}xtree[MAXN << 2];
inline void build(int root, int l, int r)
{
    xtree[root].l = l, xtree[root].r = r;
    if (l == r)
    {
        xtree[root].mmin = xtree[root].sum = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(lson, l, mid), build(rson, mid + 1, r);
    xtree[root].mmin = min(xtree[lson].mmin, xtree[rson].mmin);
    xtree[root].sum = xtree[lson].sum + xtree[rson].sum;
    return;
}
inline void query(int root, int fl, int fr)
{
    if (xtree[root].l >= fl && xtree[root].r <= fr)
    {
        ans += xtree[root].sum;
        m = min(xtree[root].mmin, m);
        return;
    }
    int mid = (xtree[root].l + xtree[root].r) / 2;
    if (fl <= mid)
        query(lson, fl, fr);
    if (mid < fr)
        query(rson, fl, fr);
    return;
}
int main()
{
    while (~scanf("%d", &n))
    {
        memset(xtree, 0, sizeof(xtree));
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        build(1, 1, n);
        cnt = 0;
        double t = 0;
        for (int i = 1; i <= n - 2; i++)
        {
            ans = 0;
            m = 0x3f3f3f3f;
            query(1, 1 + i, n);
            double s = (double)(ans - m) / (double)(n - i - 1);//取这段区间的平均值
            if (t == s)//如果与之前最大平均值相同，则加入flag数组
                flag[++cnt] = i;
            else if (s > t)//如果当前平均值更大，则重新存储 k 值
            {
                cnt = 0;
                flag[++cnt] = i;
                t = s;
            }
        }
        for (int i = 1; i <= cnt; i++)
            printf("%d\n", flag[i]);
    }
}
```


---

## 作者：B_1168 (赞：1)

看了一圈，竟然没有分块……$N=10^5$ 跑 $O(n\sqrt{n})$ 的算法，不仅难度不大，思维直接，还~~方便套模板，在TLE边缘疯狂试探~~~

这题本质就是维护一串数据的区间和与区间最小值，对分块算法来说，每次查询都是$O(\sqrt{n})$级别的，将所有可能的K遍历一次，复杂度$O(n\sqrt{n})$，结合数据范围，完全可以接受

因为本题解套模板本质太明显，就不写多少注释了~~其实就是懒~~

![不吸氧的评测结果，其实挺慢的](https://i.ibb.co/FmNYzq4/P4086.png)

有一说一，对于$N=10^5$的数据来说，这个真不算快了……

话不多说，下面放代码：

```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;

long long n,m,len,a[maxn],add[maxn],val_sum[maxn],val_min[maxn],be[maxn];

float ans[maxn],max_ans=0;

//devised from my P3372 Segment Tree I Template  
  
/*//not needed for this problem
void modify(long long from,long long to,long long ad){  
    for(long long i=from;i<=min(to,be[from]*len);i++) a[i]+=ad,val[be[from]]+=ad;
    if(be[from]!=be[to]){
        for(long long i=(be[to]-1)*len+1;i<=to;i++) a[i]+=ad,val[be[to]]+=ad;
    }
    for(long long i=be[from]+1;i<=be[to]-1;i++) add[i]+=ad;
}
*/

long long query_sum(long long from,long long to){
    long long cnt=0;
    for(long long i=from;i<=min(to,be[from]*len);i++) cnt+=(a[i]+add[be[from]]);
    if(be[from]!=be[to]){
        for(long long i=(be[to]-1)*len+1;i<=to;i++) cnt+=(a[i]+add[be[to]]);
    }
    for(long long i=be[from]+1;i<=be[to]-1;i++) cnt+=(val_sum[i]+add[i]*len);
    return cnt;
}

long long query_min(long long from,long long to){
    long long cnt=9223372036854775805; //giving the minimum counter a de facto infinite value is critical for the functioning of the algorithm
    for(long long i=from;i<=min(to,be[from]*len);i++) cnt=min(cnt,a[i]+add[be[from]]);
    if(be[from]!=be[to]){
        for(long long i=(be[to]-1)*len+1;i<=to;i++) cnt=min(cnt,a[i]+add[be[to]]);
    }
    for(long long i=be[from]+1;i<=be[to]-1;i++) cnt=min(cnt,val_min[i]);
    return cnt;
}


int main(){
    scanf("%lld",&n);
    len=sqrt(n);
    for(long long i=1;i<=n;i++){
    	be[i]=(i-1)/len+1;
    }//initialization
    for(long long i=1;i<=n;i++){
    	val_min[be[i]]=9223372036854775805;
    }//initialization
    for(long long i=1;i<=n;i++){
    	scanf("%lld",&a[i]);
		val_sum[be[i]]+=a[i];
		val_min[be[i]]=min(val_min[be[i]],a[i]);
    }//initialization
    for(long long i=1;i<=n-2;i++){
//      printf("%d ",query_sum(i+1,n)-query_min(i+1,n));
		ans[i]=(query_sum(i+1,n)-query_min(i+1,n)*1.0)/(n-i-1);
		max_ans=max(max_ans,ans[i]);
//		cout<<ans[i]<<endl;
    }
    //to ensure that the numbers are properly stored as floats, some test printout messages are used
    for(int i=1;i<=n-2;i++){
    	if(ans[i]==max_ans){
    		cout<<i<<endl;
    	}
    }//counting the final answer
}
```


---

## 作者：Mkarry (赞：1)

哇哇哇，难道没有人用

## 集合

求解的吗？

我的想法就是集合先把a数组全部塞进去，然后k枚举一遍，然后运用集合中的$find$函数以及$erase$函数就可以把集合中的第a[k]个元素删除了。注意$find(a[k])$返回一个迭代器，而$erase(find(a[k]))$就可以把集合中的一个值为a[k]的元素删掉。然后就可以按照题目所说，挑一个最大的答案了。

需要注意的是集合一定要声明成$multiset$才可以，因为$set$会自动去掉重复的元素，~~十分猥琐~~

```
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],s; double maxn,ans[100005];
inline int read(){
	int ret=0,f=1; char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') f=-f;
	for(;ch>='0'&&ch<='9';ch=getchar()) ret=ret*10+ch-'0';
	return ret*f;
}
multiset<int>S;
multiset<int>::iterator it;	//只能声明成multiset

int main(){
	n=read();
	for(int i=1;i<=n;i++) S.insert(a[i]=read()),s+=a[i];
	int num=n;
	for(int k=1;k<=n-2;k++){
		S.erase(S.find(a[k]));
		s-=a[k];
		num-=1;
		ans[k]=(double)(s-*S.begin())/(num-1);		//S.begin()是集合中的根节点的迭代器，也就是最小的一个
		maxn=max(maxn,ans[k]);
	}
	for(int i=1;i<=n-2;i++) if(maxn==ans[i]) printf("%d\n",i);
	return 0;
}

```

这道题就这么解完了。。。

**END**



------------


---

## 作者：Na2PtCl6 (赞：0)

## 分析题目
这是一道后缀和+区间最小值问题，可以用线段树或ST表来解决，下面我讲一下线段树做法。

因为题目是从前往后吃掉的，所以我们倒序维护数组后缀和。接着，建立线段树，在每个节点上存储当前区间的最小值。然后从k=1的情况开始顺序枚举直到k=n-2，对于每次枚举，我们把后`n-i`个元素的和减去下标`i`到`n-1`的最小值除以`n-i-1`，即吃掉i个题目时的分数，储存下来，以便以后查询，并与当前最大分数比较，取`max`值。**最后遍历储存分数的数组，找出和最大分数一样的元素，输出其下标**。

## 注意事项
- 最后一步很重要，我就因为这个WA了3次，还是要好好读题。

- 注意精度，分数要用`double`存储

## 代码
这题虽然思维难度不大，但要注意的地方挺多。
### 维护后缀和
```cpp
for(int i=n-1;i>=0;i--)
		sum[i]=sum[i+1]+arr[i];
```
### 建立线段树
非常模板
```cpp
void build(int l,int r,int node){
	if(l==r){
		tree[node]=arr[l];
		return ;
	}
	int mid=l+r>>1;
	int lnode=(node<<1)+1;
	int rnode=(node<<1)+2;
	build(l,mid,lnode);
	build(mid+1,r,rnode);
	tree[node]=min(tree[lnode],tree[rnode]);
}
```

### 询问
非常模板
```cpp
int query(int l,int r,int node,int start,int end){
	if(end<l||start>r)
		return 0x7fffffff;
	if(start<=l&&r<=end)
		return tree[node];
	if(l==r)
		return tree[node];
	int mid=l+r>>1;
	int lnode=(node<<1)+1;
	int rnode=(node<<1)+2;
	int lmin=query(l,mid,lnode,start,end);
	int rmin=query(mid+1,r,rnode,start,end);
	return min(lmin,rmin);
}
```
### 枚举
```cpp
for(int i=1;i<=n-2;i++){
		//计算分数 
		k[i]=(double)(sum[i]-query(0,n-1,0,i,n-1));
		k[i]/=n-i-1;
		res=max(res,k[i]);
	}
```

### 完整代码
### 版本1
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=100004;
int n,m,arr[maxn],sum[maxn],tree[maxn<<2];
double res=-1,comp,k[maxn];

void build(int l,int r,int node){
	if(l==r){
		tree[node]=arr[l];
		return ;
	}
	int mid=l+r>>1;
	int lnode=(node<<1)+1;
	int rnode=(node<<1)+2;
	build(l,mid,lnode);
	build(mid+1,r,rnode);
	tree[node]=min(tree[lnode],tree[rnode]);
}

int query(int l,int r,int node,int start,int end){
	if(end<l||start>r)
		return 0x7fffffff;
	if(start<=l&&r<=end)
		return tree[node];
	if(l==r)
		return tree[node];
	int mid=l+r>>1;
	int lnode=(node<<1)+1;
	int rnode=(node<<1)+2;
	int lmin=query(l,mid,lnode,start,end);
	int rmin=query(mid+1,r,rnode,start,end);
	return min(lmin,rmin);
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(int i=n-1;i>=0;i--)
		sum[i]=sum[i+1]+arr[i];
	build(0,n-1,0);
	for(int i=1;i<=n-2;i++){
		//计算分数 
		k[i]=(double)(sum[i]-query(0,n-1,0,i,n-1));
		k[i]/=n-i-1;
		res=max(res,k[i]);
	}
	for(int i=1;i<=n-2;i++)
		if(res==k[i])
			printf("%d\n",i);
	return 0;
}
```
### 版本2
其实除了`duoble`，也可以用`long long`调整精度，为避免重复冗余，只贴部分代码

#### 精度设置
```cpp
const int e=1000000;
```
如果你愿意可以调得更高
#### 枚举

```cpp
for(int i=1;i<=n-2;i++){
		k[i]=sum[i]-query(0,n-1,0,i,n-1);
      k[i]=k[i]*e/(n-i-1);
		if(res<k[i])
			res=k[i];
	}
```

---

## 作者：封禁用户 (赞：0)

### 前言

A 掉了这么一道题目，如果不发题解也太可惜了 ……

我也是太惨了，我 [发了贴](https://www.luogu.com.cn/discuss/show/207014) 下载了两次数据，然后再调了 30 minutes。

### 分析

这道题目其实可以暴力或者线段树做出来，但是我想利用 单调栈 这种 o(n) 的线性表来做，顺便巩固一下 单调栈 。

~~不过题解区好像没有 单调栈 。~~

那么题意就不多讲了，就是要你求一个区间的最小值，总和，平均值。

那么区间最小值，毫无疑问利用单调栈的单调优势，如何你不懂单调队列，建议还是看暴力。

然后就是总和，总和我利用了前缀和的 o(1) 查询操作来做。

平均值要注意精度问题。

输出么，就要注意是升序输出的 ！我这里用栈来做存储答案的容器。

并且，$1 \le K \le N-2$，这个表示 K 只有在 1~N-2 之间存在着答案。

利用一个来变量来记录最大值。

剩下的细节也只有见代码了：

### 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=100005;
int n,a[INF],q[INF<<1],r,sum[INF],ans1[INF],r1;
double Max;
//定义变量，这里我单调栈开了 2 倍空间，就怕不够。其实不用管这些的，一般来说，1 倍空间就够了。
signed main()
{
        scanf("%d",&n);
        //读入 n 。
        for (int i=1; i<=n; i++) {
                scanf("%lld",&a[i]);
                sum[i]=sum[i-1]+a[i];
               	 //读入 a[i] 并且建立 sum 前缀和。
        }
        for (int j=n; j>=n-2; j--) {
                while (r>0 && a[q[r]]>=a[j]) r--;
                q[++r]=j;
        }
        //我用的是倒序的处理方式，因为这样子单调队列比较好实现，上面的是预处理最后两个。
        for (int k=n-2; k>=1; k--)
        {
                double ans=0;
                ans=(double) ((sum[n]-sum[k])-a[q[1]])/(1.0*(n-k-1));
                // printf("%lf %d %d\n",ans,k,q[1]);
                //然后就是吃掉了 前 k 个那么就减去，然后再去掉一个最小值，那么每一次单调栈里面的最小值或最大值一般是第 1 个或者第 0 个，单调队列里是 l ，后面是笔者比较容易出错的地方，n-k-1 表示了有 n 个数，去掉了前 k 个数，还要去掉一个最小值的数。所以大家引以为戒。
                if (Max<ans) {
                        r1=1;
                        ans1[r1]=k;
                        Max=ans;
                }
                //假如说找到了比 Max 还要大的，那么就将队列清空，也就是 r1=1 。并且 Max 赋值为 ans 。
                else if (Max==ans) {
                        ++r1;
                        ans1[r1]=k;
                        Max=ans;
                }
                //如果一样呢？那么就利用栈来存起来。
                while (r>0 && a[q[r]]>=a[k]) r--;
                q[++r]=k;
                //这里就是单调栈的维护方式，(如果遇到一个比你小还比你强的人，AFO 吧。也就是 r-- 弹出。然后在利用下标存现在的值。
        }
        for (int i=r1; i>=1; i--)    printf("%d\n",ans1[i]);//倒序输出，这样可以保证升序。
        //然后输出，注意用换行符输出 ，但是空格输出我不清楚会不会炸。
        return 0;
}

```

### 写在后面的话

我这篇题解如果有错误，那么请在评论区里留言，我将会很感谢反映的人。

**谢谢观赏！**

---

## 作者：曹老师 (赞：0)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco17dec-mcamh.html)

哇哇哇，难道就我一个人写线段树吗？？？

很简单，直接枚举$k$，然后检查这个$k$求出来的值是否是最大的，或者是否与最大值相等，然后用队列存起来~~(蒟蒻实在不知道用什么存是最好的，胡乱搞了个队列)~~，接着就是答案。对于每一个$k$，求答案的时候，我们需要知道的是区间$[k+1$ ，$ n]$之间去掉一个最小值之后的平均值。我们可以用前缀和维护前$i$个数字(乘积)的总和，这样$O(1)$就能知道$[k+1$， $n]$之间没有去掉最小值时候的总和，接下来就是去掉最小值的操作。我这里用线段树维护，毕竟只有建树和查询最小值，是非常好写的。这样求出最小值来，然后用总和减去，再除以元素个数，就能求得平均数，注意精度，更新和保存答案。

~~(好久没算时间复杂度了……)~~

查询最小值：$O(logn)$ 总的查询时间：$O(k × logn)$ 总和查询时间：$O(1)$ 总的时间复杂度：$O(k × logn)$

## Code ##

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<vector>
using namespace std;

struct SegTree {
    int l , r , min;
};
SegTree seg[400005];
int n , data[100005] , sum[100005];
double opt = 0;
queue<int>q;

void update(int num) {
    seg[num].min = min(seg[num<<1].min , seg[num<<1|1].min);
}

void build(int num , int l , int r) {
    seg[num].l = l;
    seg[num].r = r;
    if(l == r) {
        seg[num].min = data[l];
        return ;
    }
    int mid = (l + r)>>1;
    build(num<<1 , l , mid);
    build(num<<1|1 , mid+1 , r);
    update(num);
}

int query(int num , int l , int r) {
    if(seg[num].l >= l && seg[num].r <= r)
        return seg[num].min;
    int mid = (seg[num].l + seg[num].r)>>1 , res = 1e9;
    if(l <= mid)
        res = min(query(num<<1 , l , r) , res);
    if(r > mid)
        res = min(query(num<<1|1 , l , r) , res);
    return res;
}

int main() {
    scanf("%d",&n);
    for(int i=1; i<=n; i++) {
        scanf("%d",&data[i]);
        sum[i] = sum[i - 1] + data[i];	
    }
    build(1 , 1 , n);
    for(int k=1; k<=n-2; k++) {
        int l = k+1 , r = n;
        double res;
        res = (double)(sum[r] - sum[l-1]);
        res -= query(1 , l , r);
        res = res / (r - l);
        if(res > opt) {
            while(!q.empty())
                q.pop();
            q.push(k);
            opt = res;
        }else 
            if(res == opt)
                q.push(k);
    }
    while(!q.empty()) {
        printf("%d\n",q.front());
        q.pop();
    }
    return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P4086

---

