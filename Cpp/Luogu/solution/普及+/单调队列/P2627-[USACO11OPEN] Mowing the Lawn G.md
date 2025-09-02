# [USACO11OPEN] Mowing the Lawn G

## 题目描述

在一年前赢得了小镇的最佳草坪比赛后，Farmer John 变得很懒，再也没有修剪过草坪。现在，新一轮的最佳草坪比赛又开始了，Farmer John 希望能够再次夺冠。

然而，Farmer John 的草坪非常脏乱，因此，Farmer John 只能够让他的奶牛来完成这项工作。Farmer John 有 $N$（$1\le N\le 10^5$）只排成一排的奶牛，编号为 $1\ldots N$。每只奶牛的效率是不同的，奶牛 $i$ 的效率为 $E_i$（$0\le E_i\le 10^9$）。

靠近的奶牛们很熟悉，因此，如果 Farmer John安排超过 $K$ 只连续的奶牛，那么，这些奶牛就会罢工去开派对 :)。因此，现在 Farmer John 需要你的帮助，计算 FJ 可以得到的最大效率，并且该方案中没有连续的超过 $K$ 只奶牛。

## 样例 #1

### 输入

```
5 2
1
2
3
4
5
```

### 输出

```
12
```

# 题解

## 作者：Koakuma (赞：276)

单调队列优化dp入门好题.

这里介绍3种方法(思路)

## $\mathcal{Solution\ One}$

顺推.

令 $dp[i][1]$ 表示在前 $i$ 头奶牛中,选了第 $i$ 头奶牛能获得的最大效率

$dp[i][0]$ 表示在前 $i$ 头奶牛中,不选第 $i$ 头奶牛能获得的最大效率

显然可以得出以下转移方程 ( **注意 $K$ 是题目给出的区间长度**)

$$dp[i][0]=max(dp[i-1][0],dp[i-1][1])$$

$$dp[i][1]=max\{dp[j][0]+\sum\limits_{j=i-K+1}^{i}E_j \}$$

可以预处理出前缀和优化掉一重循环,转移方程就变成了如下所示

$$dp[i][1]=max\{dp[j][0]+Sum[i]-Sum[j]\}$$

因为最终都要加上一个 $Sum[i]$ ,所以可以把 $Sum[i]$ 移到 $max$ 函数外,所以

$$dp[i][1]=max\{dp[j][0]-Sum[j]\}+Sum[i]\ \ \ (i-K\leq j < i)$$

这时候我们可以发现,要使 $dp[i][1]$ 最大,我们就要让 $dp[j][0]-Sum[j]$ 尽可能的大,所以只需要用一个单调队列维护长度为 $K$ 的区间中 $dp[j][0]-Sum[j]$ 的最大值就好了.

## $\mathcal{Solution\ Two}$

顺推.但状态和之前描述的有些不同

令 $dp[i]$ 表示到前 $i$ 头奶牛为止能得到的最大效率

我们可以在区间 $[i-K,i]$ 间枚举休息的奶牛,所以转移方程就可以初步推出

$$dp[i]=max\{dp[j-1]+\sum\limits_{k=j+1}^{i}E_k\}\ \ \ (i-K\leq j\leq i)$$

同样,我们预处理出前缀和进行优化

$$dp[i]=max\{dp[j-1]+Sum[i]-Sum[j]\}\ \ \ (i-K\leq j\leq i)$$

然后也是把 $Sum[i]$ 移到外面

$$dp[i]=max\{dp[j-1]-Sum[j]\}+Sum[i]\ \ \ (i-K\leq j\leq i)$$

我们发现,这里又可以用一个单调队列维护 $dp[j-1]-Sum[j]$ ,问题也就迎刃而解了.

## $\mathcal{Solution\ Three}$

**逆推,正难则反**.

重点讲逆推法

由于题目要求区间 $[1,N]$ 中不能有连续超过 $K$ 头的奶牛,也就是**两头休息的奶牛间的距离是 $\leq$ $K$的** (这里的"**距离**"指奶牛的数量,单位 $1$ 即为一头奶牛),并且我们要求的是能获得的最大的效率,反过来想,也就是当损失的效率值越少时,能获得的效率也就越大,所以我们可以将问题转化为**求出最小的效率损失**.

想到这里,$dp$ 的模型就很自然而然地出来了

令 $dp[i]$ 表示前 $i$ 头奶牛且第 $i$ 头奶牛不工作时的最小损失

则状态转移方程为

$$dp[i]=min\{dp[j]\}+E[i]\ \ \ (i-K-1\leq j<i)$$

这里 $j$ 的左边界为 $i-K-1$ 而不是 $i-K$ 的原因是如果不选第 $i$ 头奶牛则上一头休息的奶牛的位置就是 $i-K-1$ ,也就是说,此时我们单调队列维护的是**长度为 $K+1$ 的区间**中 $dp[j]$ 的最小值.

另外,这里有个小技巧就是**最后一段区间的奶牛可能全都不休息**,所以我们可以加一个编号为 $N+1$ 的虚点,最终答案即为 $\sum\limits_{i=1}^{N}E_i-dp[N+1]$.

## $\mathcal{After\ Writing}$

此篇文章是笔者为了加深印象而写的,讲的可能比较快,有些关于变量边界的问题还请读者自行画图理解,或者在评论区指出,笔者会尽己所能解疑的.如果文章有什么漏洞或者错误,还请你们指出,感激不尽.

---

## 作者：thmyl (赞：62)

考虑动归，在第i点时，在i-k到i中肯定有一个点j不能选择，即：j为断点。

所以###f[i]=max(f[i],f[j-1]+a[j+1]+a[j+2]……a[i])（i-k<=j<=i）

所以维护前缀和，然后方程就变成了

###f[i]=max(f[i],f[j-1]+sum[i]-sum[j]) (i-k<=j<=i) 

变形一下变成：###f[i]=max(f[i],f[j-1]-sum[j])+sum[i] (i-k<=j<=i)

发现max里面的值只与j有关，所以可以用单调队列优化转移。


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long n,m,a[100010],sum[100010],f[100010];
long long d[100010];
int q[100010],head=0,tail=1;
long long que(int i){//让返回值尽量的大，队列单调减，使首元素恒最大 
    d[i]=f[i-1]-sum[i];
    while(head<=tail&&d[q[tail]]<d[i])tail--;
    q[++tail]=i;
    while(head<=tail&&q[head]<i-m)head++;
    return d[q[head]];
}
int main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)cin>>a[i],sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=n;i++)f[i]=que(i)+sum[i];
    cout<<f[n];
}
```

---

## 作者：Refined_heart (赞：35)

单调队列优化$DP$的例题之一。

用$dp[i][0/1]$表示序列选到第$i$个奶牛时，第$i$个奶牛选$/$不选的最大效率，则有：

$dp[i][0]=max(dp[i-1][0],dp[i-1][1])$

$dp[i][1]=max(dp[j][0]-sum[j]+sum[i]),[i-k<=j<i]$

枚举$j$，考虑继续优化。

观察第二个方程发现，可以把$sum[i]$提出来，则：

$dp[i][1]=max(dp[j][0]-sum[j])+sum[i],[i-k<=j<i]$

我们发现，只要使得$MAX$中的值最大即可。故可以使用单调队列使其递减。

每次取的是队头，队头维护$max$，题目得解。

$Code:$

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long q[2000000],f[2000000][2];
long long n,k,s[2000000],a[2000000];
long long tail,head;
int main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
		s[i]=s[i-1]+a[i];//sum
	}
	tail=head=1;//初始化 
	for(int i=1;i<=n;++i){
		f[i][0]=max(f[i-1][0],f[i-1][1]);//对于不选i，只考虑前面两个即可 
		while(q[head]<i-k&&head<=tail)head++;//判断队头是否在所找区间内 
		f[i][1]=f[q[head]][0]-s[q[head]]+s[i];//取MAX转移 
		while(f[i][0]-s[i]>f[q[tail]][0]-s[q[tail]]&&head<=tail)tail--;
		q[++tail]=i;//更新队尾，当队列有数且当前队尾若插入i不满足单调性时
		//写成s[i]-f[i][0]<s[q[tail]]-f[q[tail]][0]也可以
		//可以理解为选到i和队尾时，两者不选的奶牛的效率和相比较，显然浪费少的更优，不优的删除即可 
	}printf("%lld\n",max(f[n][0],f[n][1]));
	return 0;
}
```


---

## 作者：wick (赞：31)

**一道训练stl与dp的基础题**

下面将用3种数据结构来解题（有标准思路与“先礼后兵”的思路）

[点击送倚天剑](https://www.luogu.org/problem/P2627)（题目传送）

作为一道dp的题目，首先我们先想想状态转移方程

若是没有  

**“如果Farm John安排超过K只连续的奶牛，那么，这些奶牛就会罢工去开派对”**

这一条件限制，那么显然是将cow们都叫上最好啦 ~~，但谁让FJ辣么懒~~。

故在有限制的条件下，我们可以设dp[i]为1~i之间的最大效率之和。

```
for（i：1~n，i++）
   dp[i]=max{
      for（j：i~1，j--）{
	   //j代表的是第j个cow不选
	   if（j-i〉k）break；//限制的条件，不超过k个cow
	   dp[j-1]+s[i]-s[j-1+1]//s为前缀和
      }
    }
```

**我们是可以发现这段伪代码是可以更精简的（为下面的优化做准备）**
 


```
for（i：1~n，i++）
   dp[i]=s[i]+max{//s[i]是不变的，提到上面
      for（j：i~i-k，j--）{//限制的条件，不超过k个cow
	   //j代表的是第j个cow不选
	   dp[j-1]-s[j]//s为前缀和
      }
    }
```
与此同时我们可以发现时间复杂度已变为了O（k*n）。并且，d[j-1]-s[j]也是可以确定的。我们可以用一个数据结构将d[a]-s[a+1]的值存下来，并维护数据结构中的数据个数小于等于k，还可以将最大数直接取出。

那么我们可以用multiset或堆（堆手写快，但考试时相信一般人不会手写）

**这里先讲明一个东西，multiset.insert（）其实是有一个返回值的，便是指向插入数据的 迭代器！（故可以省去find）//也可以用multiset <pair<long long,int>> fd，上一个是值，下一个是下标。然后，将删除操作上移，判断fd.end()-1是否合法，若不则删去（用while)（若放下面则下标便不合法了。（想看实现可翻到最后）**

### 法1.上代码！！！：

**数据结构*1**

（讲解在代码里）
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
typedef long long ll;
typedef multiset < ll >  SET;//偷懒
typedef SET :: iterator itr;//偷懒
SET fk;//find kth 的缩小，即上文的数据结构
itr handle[maxn];//我们接下来为了维护fd的大小小于等于k，要从fd中删除最末尾的数据（可以用multiset的find函数，但会慢，毕竟是O（log n）嘛），用这个迭代器的数组指向每一个数
int n,k；
ll a[maxn],dp[maxn],s[maxn];//a是输入的数据（其实应该用e更好（efficiency）），dp上面已经说过了，s是前缀和

void solve（）{
	handle[0]=fk.insert(0);//dp[-1]-s[0]，但这样会下标溢出
	handle[1]=fk.insert(dp[0]-s[1]);//开始的初始话，i从1开始
	for(int i=1; i<=n; i++) {
		l1 tmp;
		tmp=*fk.rbegin();//取最后一个，即最大值（不是end哦）
		dp[i]=tmp+s[i];//上面的s[i]+max（dp[j-1]-s[j]），不过省去了一个循环
		if(i==n) break;//到了n就可以break，输出了
		handle[i+1]=fk.insert(dp[i]-s[i+1]);//插入数据，注意是handle[i+1]!!
		int j=i-k;
		if(j>=0) fk.erase(handle[j]);//维护数据
	}

}
int main() {
	scanf("%d%d",&n,&k);
	for(int j=1; j<=n; j++) {
		scanf("%lld",&a[j]);
		s[j]=s[j-1]+a[j];//前缀和
	}
	solve（）；
	printf("%lld",dp[n]);//输出
	return o;
}


```

**其实用find也是可以过的**
（并且比较易懂 ~~,不用那个 *** 迭代器了~~）

### 法2.直接上代码：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005；
typedef long long ll;
multiset < ll > fd;
int n,k;
ll a[maxn],dp[maxn],s[maxn];
void solve（）{
	fd.insert(0);//dp[-1]-s[0]，但这样会下标溢出
	fd.insert(dp[0]-s[1]);
	for(int i=1; i<=n; ++i) {
		ll tmp;
		tmp=*fd.rbegin();
		dp[i]=s[i]+tmp;
		if(i==n)break;
		fd.insert(dp[i]-s[i+1]);//上面的s[i]+max（dp[j-1]-s[j]），不过省去了一个循环
		int j=i-k;
		if(j>=0) {
			ll x;
			if(j==0)x=0;//要特判的
			else x=dp[j-1]-s[j];
			multiset < ll > :: iterator itr;
			itr=fd.find（x);
			fd.erase(itr);
		}
	}
}
int main() {

	scanf("%d%d"，&n,&k);
	for(int j=1; j<=n; j++) {
		scanf("%lld",&a[j]);
		s[j]=s[j-1]+a[j];
	}
	solve（）；
	printf("%lld",dp[n]);
	return o;
}

```

下面说一下法3

**可以用手写堆来打！！！！**

### 法3.上代码：

**数据结构*2**

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
typedef long long ll;
int n,k;
int handle[maxn];
ll a[maxn],dp[maxn],s[maxn];

//手写堆不清楚的同学可以百度一下

struct HEAP {//手写堆（stl中的heap不支持插入与删除）
	int tot ；//hp的大小
	ll hp[maxn];// 1..tot，从外面指到hp中
	int rec[maxn];//从hp中指出来
	void update(int p) {//更新数据（先上升后下降）==up（）+down（）
		int f,l,r,c;
		while(p>1) {
			f=p/2;
			if(hp[p] > hp[f]) {
				swap(hp[p],hp[f]);
				swap(handle[rec[p]],handle[rec[f]])；//上升
				swap(rec[p]，rec[f]);
				p=f；
			} else break;
		}
		while(p<=tot/2) {
			l=p*2;
			r=l+1;
			if(r>tot || hp[l]>hp[r]) {
				c=l;
			} else {
				c=r;
			}
			if(hp[c] > hp[p]) {
				swap(hp[p],hp[c]);
				swap(handle[rec[p]],handle[rec[c]]);//下降
				swap(rec[p],rec[c]);
				p=c;
			} else break;
		}
	}
	ll MAX() {
		return hp[1];//给最大值
	}
	int insert(ll x,int i) {//插入
		tot++;
		hp[tot]=x;
		rec[tot]=i;
		handle[i]=tot;
		update(tot);
	}
	void erase(int p) {//删除
		hp[p]=hp[tot];
		rec[p]=rec[tot];
		handle[rec[tot]]=p;
		tot--;
		update(p);
	}
};

void solve() {//算法与上相同
	HEAP hp;
	hp.insert(0,0);
	hp.insert(dp[0]-s[1],1);
	for(int i=1; i<=n; ++i) {
		ll tmp;
		tmp=hp.MAX() ;
		dp[i]=s[i]+tmp;
		if(i==n)break;
		hp.insert(dp[i]-s[i+1],i+1);
		int j=i-k;
		if(j>=0) {
			hp.erase(handle[j]);
		}
	}
}

int main() {
	scanf("%d%d",&n,&k);
	for(int j=1; j<=n; j++) {
		scanf("%lld",&a[j])；
		s[j]=s[j-1]+a[j];
	}
	solve();
	printf("%lld",dp[n]);
	return 0;
}

```

算法还请读者自行理解,或者在评论区指出,我会尽己所能解疑的。

如果文章有什么漏洞或者错误,还请您们指出,感激不尽。




ps： 

### 法4.上代码：




```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
typedef long long ll;
int n,k;
ll a[maxn],dp[maxn],s[maxn];
void solve() {
	multiset< pair<ll,int> >fd;
	dp[0]=0;
	fd. insert( make_pair(0,0) );
	fd. insert( make_pair(dp[0]-s[1]，1） );
	for(int i=1; i<=n; ++i) {
		ll tmp;
		while( fd.rbegin()->second < i-k) {//先礼后兵（先不删，到要选的时候再判断是否合法，若不合法再删
			fd. erase(--fd. end());
		}
		tmp=fd . rbegin()->first;
		dp[i]=s[i]+tmp;
		if(i==n)break;
		fd.insert( make_pair(dp[i]-s[i+1],i+1) );
	}
}
int main() {
	scanf("%d%d",&n,&k);
	for(int j=1; j<=n; j++) {
		scanf("%lld",&a[j]);
		s[j]=s[j-1]+a[j];
	}
	solve();
	printf("%lld",dp[n]);
	return 0;
}
```

### 法5.上代码：

**数据结构*3**

**（multiset换priority_queue）**
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
typedef long long ll;
int n,k;
ll a[maxn],dp[maxn],s[maxn];
void solve() {
	priority_queue< pair<ll,int> >hp；
	hp.push(make_pair(0,0));
	hp.push(make_pair(dp[0]-s[1]，1));
	for(int i=1; i<=n; ++i) {
		ll tmp;
		while(hp.top().second<i-k) {
			hp.pop();
		}
		tmp=hp.top().first;
		dp[i]=s[i]+tmp;
		if(i==n)break;
		hp.push( make_pair(dp[i]-s[i+1],i+1));
	}
}
int main() {
	scanf("%d%d",&n,&k);
	for(int j=1; j<=n; j++) {
		scanf("%lld",&a[j])；
		s[j]=s[j-1]+a[j];
	}
	solve(）;
	printf("%lld",dp[n]);
	return 0;
}
```

不说了会厕所哭一会。（卖惨求过）

[点击送屠龙刀](https://www.luogu.org/blog/wickphy/)（安利一下自己的博客）

致正在复制的同学，感受一下CE的魅力吧 ~~（淫笑）~~ （他们肯定看不到）



---

## 作者：EarthGiao (赞：22)

## 【思路】
单调队列 线性DP     
### 【说在前面的话】 
很有意思的一道题     
正着想那是选择最多的而且区间大小不定    
所以很麻烦对不对    
不想做这道题目了对不对？   

### 【前缀思路】 
正着不行那就反着来！   
找可以选择的奶牛很麻烦  
那就找出不选的奶牛  
不选的奶牛一定是小的  
而且是不会和别的成一个区间   
因为有两个连续的不选择的奶牛不会让结果更 优      
只会让结果更差     
因为多选一个比少选一个会更优的    
具体证明就不多说了   
自己感性理解一下下就好了   

### 【最终思路】    
然后从第一个点开始枚举    
入队   
如果这队首的到这个点的距离大于了k + 1那就弹出队首   
为什么是k + 1呢   
因为这是不选择的牛   
最长的连续区间是k的长度   
不选择的牛就会在这个区间的两边   
这种情况下是距离k + 1   
并且这种情况是最长情况     
所以是大于k + 1   
然后因为要选择最小的嘛   
那就把队尾大于这个f[i]那也弹出   
因为有了比队尾更小的值那队尾就没有可能会出现了   
比我小还比我强！    

### 【注意】 
要先弹出队首超出范围的值    
然后再处理出f[i]的值    
最后在弹出队尾的     
因为f[i]的值是取决于前面合法区间内的最小值    
要先把区间内不合法的弹掉   
不然不能保证f[i]合法    
而且弹出的比较依据就是f[i]的大小    
所以先在弹出队尾之前处理出f[i]的值    
这样顺序就出来了吼     
## 【完整代码】
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define int long long
using namespace std;
const int Max = 100005;
struct node
{
	int t;
	int v;
};
deque<node>q;
int a[Max];
int f[Max];
signed main()
{
	int n,k;
	cin >> n >> k;
	int tot = 0;
	for(register int i = 1;i <= n;++ i)
		cin >> a[i],tot += a[i];
	int M = 0x7f7f7f7f7f7f;
	q.push_back((node){0,0});
	for(register int i = 1;i <= n;++ i)
	{
		while(!q.empty() && i - q.front().t > k + 1)
			q.pop_front();
		f[i] = q.front().v + a[i];
		while(!q.empty() && f[i] < q.back().v)
			q.pop_back();
		q.push_back((node){i,f[i]});
	}
	for(register int i = n;i >= n - k;i --)
		M = min(M,f[i]);
	cout << tot - M << endl;
	return 0;
}
```

---

## 作者：零的风尘濶羽 (赞：21)

首先要想到转化为删去k个内效率最低的奶牛

由于相邻不能超k,所以很容易想到用f(i-k -> i-1)的数来dp求f(i)

然而O(n^2)算法可能会崩

因此，用单调队列来维护i-k -> i-1区间最小值

前一句更通俗的说法(i的自述):你在我前面还比我大,留你何用？

最后只要用总数减去最小删去效率就行了

这样虽然还是O(n^2),但是有极大的优化,只要不是出题人故意坑你卡数据就没问题。。。

注意单调队列头的更新(不能超k）

~~御坂御坂耐心地讲解道~~

附上代码和注释(代码有点冗长，请见谅，毕竟蒟蒻水平有限)
```
#include<stdio.h>
#include<iostream>
using namespace std;
long long line[100001],x,total;  //line存单调队列,x临时变量存输入，total存效率总数(long long注意!不然后果自负)
int NO[100001];     //NO存单调队列的编号,就是1~k,用于更新队列头
int main(){
	int n,k,head=0,tail=1;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%ld",&x);    //来一个搞一个
		total+=x;     //更新效率总数
		if(NO[head]<i-k-1) head++;   //把头控制在k个以内,不然更新头。
		x+=line[head];   //由于是单调队列,所以第一个一定最小,用它来更新f(i)
		while(line[tail-1]>x) tail--; //踢人模式,被我完爆的家伙们，你们不属于这里!(因为后面几项不但靠前且值还较大，所以不能还会用它们更新)
		line[tail]=x; //将刚来的f(i)存入队列
		NO[tail]=i;  //将它的序号存入队列
		tail++;  //尾指针记得加一哦~~(御坂御坂肯定地说到)~~
	}
	if(NO[head]<n-k) head++;   //这里注意,由于最后尾指针更新,所以头可能不在k的范围内
	cout<<total-line[head];  //由于单调队列头最小,所以可以直接用总数减去头
}
```

---

## 作者：QYQYQYQYQYQ (赞：18)

苣蒻的第一个题解！


转化题意 既然是求整个的效率最大之和 那就转化为求 剔除的牛的效率之和最小的值 最后再用总效率减去这个值就得到答案了

那么两个被剔除的牛之间的距离满足小于k

容易得到DP方程：F[I]=MIN(F[J])+A[I] （J∈[I-K,I-1]）

其中F[I]表示第I个物品被剔除出去且满足题意的最小值

复杂度：n方

然后居然发现有这样一个事情：题目中好像要维护一个区间的最小值

用单调队列呀！

那题目就简单啦（然而本蒟蒻还是调了很久很久 第一次写单调队列）

```cpp
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
long long dl[100010],dlindex[100010],head=0,tail=0,f[100010];
long long n,k,a[100010],fc[100010];
long long sum=0;
int main()
{
    cin>>n>>k;
    for(long long i=1;i<=n;i++)
    {
    cin>>a[i];
    sum+=a[i];
    }
    for(long long i=1;i<=n;i++)
    {
        f[i]=a[i]+dl[head];
        while(f[i]<dl[tail]&&head<=tail)
            tail--;
        while(dlindex[head]<i-k)
            head++;
        tail++;
        dlindex[tail]=i;
        dl[tail]=f[i];
    }    
    long long ans=0x7f7f7f7f7f7f;
        for(long long i=n-k;i<=n;i++)    
    ans=min(ans,f[i]);    
    cout<<sum-ans;
}

---

## 作者：quest_2 (赞：8)

## STL信仰用户不请自来

别的不说，我觉得 `deque` 是贞德香（~~我不会告诉你我栈和队列都是用双端队列写的~~）。个人认为手打数据结构容易写炸（或许只有我一个人是这么认为的？）8说了，笔者认为楼上的 $\mathtt{dalao}$ 都讲的十分清楚了，这里列举几项坑点？

（~~别问我是怎么踩到这些坑的~~）

1. 不开 `long long` 见祖宗，$0 \leq E_i \leq 10^9$ ，也就是说统计了两三个奶牛的前缀和就要爆 `int` 了$\dots\dots$

1. 像笔者这样的 `deque` 用户，应该务必全程保证 $q.front()$ 和 $q.back()$ 是有值的，是能被访问到的，否则就会爆炸。

1. 进入DP的 $for$ 循环之前，请往 `deque` 先 $\operatorname{push}$ 进一个0，这相当于一个火花塞，队列里有一个数才可以进行下面的比较、取数等操作。

1. $\operatorname{while}$ 的条件部分一定要加倍注意，尤其是子条件之间的顺序！且看下面的代码：

```cpp
while (!q.empty() && q.front() < i - K)
{
     q.pop_front();
}
```
笔者当时就是不以为意，把队列是否为空的判断放在了后面，导致 $q.front$ 爆炸，我太蒻了\kel。

5. $dp_{i,0}$ 也就是表示第 $i$ 个奶牛不参加的情况的最优解，它的转移不是直接等于 $dp_{i-1,1}$ 就可以了的，我们这只奶牛不选，并不代表他前一个的奶牛就一定要选，应为前一个奶牛参加或不参加的最优解。也就是 $\max(dp_{i-1,0},dp_{i-1,1})$ 

1. 最终输出的答案也应是两种情况的更优解。

这里放下代码～还希望体验单调队列优化的奥义的读者还可以移步[P2569 [SCOI2010]股票交易](https://www.luogu.com.cn/problem/P2569) ，是稍加思维的单调队列优化dp呀～

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int N, K;
int sum[100007];
deque<int> q;
int dp[100007][2];
signed main()
{
     cin >> N >> K;
     for (int i = 1; i <= N; i++)
     {
          int a;
          cin >> a;
          sum[i] = sum[i - 1] + a;
     }
     q.push_back(0);
     for (int i = 1; i <= N; i++)
     {
          dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
          while (!q.empty() && q.front() < i - K)
          {
               q.pop_front();
          }
          dp[i][1] = dp[q.front()][0] + sum[i] - sum[q.front()];
          while (!q.empty() && dp[q.back()][0] - sum[q.back()] < dp[i][0] - sum[i])
          {
               q.pop_back();
          }
          q.push_back(i);
     }
     cout << max(dp[N][0], dp[N][1]) << endl;
}
```


---

## 作者：YLWang (赞：8)

好像各位大佬用的都是单调队列优化？

这里提供一种线段树优化$DP$。

首先我们考虑暴力。

定义$dp[i]$为前$i$个数不取第$i$个的最大值。

显然最后的答案是$dp[n+1]$。

转移方程：$dp[i] = max \{sum(i-1, j) + dp[j-1]\}$，其中$sum(l, r)$表示$a$数组中$[l, r]$的和。

暴力：
```
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define INF (1 << 30) - 1
#define ll long long
#define reaD() read()
using namespace std;
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num*flag;
}
#define MAXN 100005
int a[MAXN], dp[MAXN];
int sum[MAXN];
signed main()
{
    int n = read(), k = read();
    For(i, 1, n)
        a[i] = read();
    n++, a[n] = 0;
    For(i, 1, n)
        sum[i] = sum[i-1] + a[i];
    For(i, 1, n)
        For(j, max(i-k, 1), i)
            dp[i] = max(dp[i], dp[j-1] + sum[i-1] - sum[j-1]);
    cout << dp[n] << endl;
    return 0;
}

```

显然复杂度为$O(nk)$。

转移时因为$sum[i-1]$是不变的，所以只需要用线段树维护$dp[i]-sum[i]$的最大值即可。

复杂度O(能过)

```
#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define mst(a,b) memset(a,b,sizeof(a))
#define For(i, k, j) for(register int i = (k); i <= (j); i++)
#define INF (1 << 30) - 1
#define ll long long
#define int long long
#define reaD() read()
using namespace std;
inline int read()
{
    int num=0,flag=1;char c=' ';
    for(;c>'9'||c<'0';c=getchar()) if(c=='-') flag = -1;
    for(;c>='0'&&c<='9';num=(num<<1)+(num<<3)+c-48,c=getchar());
    return num*flag;
}
#define MAXN 100005
int a[MAXN], dp[MAXN];
int sum[MAXN];
int c[MAXN << 2];
#define ls (k << 1) 
#define rs (k << 1 | 1)
inline void update(int k, int l, int r, int pos, int val) {
	if(l == pos && r == pos) {
		c[k] = val; return;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) update(ls, l, mid, pos, val);
	else update(rs, mid+1, r, pos, val);
	c[k] = max(c[ls], c[rs]);
}
inline int query(int k, int l, int r, int ql, int qr) {
	if(l == ql && r == qr) return c[k];
	int mid = (l + r) >> 1;
	if(qr <= mid) return query(ls, l, mid, ql, qr);
	else if(ql > mid) return query(rs, mid+1, r, ql, qr);
	else return max(query(ls, l, mid, ql, mid), query(rs, mid+1, r, mid+1, qr));
	
}
signed main()
{
	int n = read(), k = read();
	For(i, 1, n) a[i] = read();
	n++, a[n] = 0;
	For(i, 1, n)
		sum[i] = sum[i-1] + a[i];
	dp[1] = 0;
	update(1, 0, n, 1, dp[1] - sum[1]);
	For(i, 2, n) {
		int L = max(i-k, 1ll), R = i;
		dp[i] = sum[i-1] + query(1, 0, n, L-1, R-1);
		update(1, 0, n, i, dp[i] - sum[i]);
	}
	cout << dp[n] << endl;
    return 0;
}

```


---

## 作者：lgswdn_SA (赞：6)

朴素 DP 很简单，$f(i,0/1)$ 表示前 $i$ 头奶牛，选/不选第 $i$ 头奶牛的最大总和。决策为枚举区间 $[i-k+1,i]$ 中选择一个点 $j$，我们选择 $[j,i]$ 的奶牛且不选择奶牛 $j-1$。

$$
f(i,1)=\max_{j\in [i-k+1,i]} \small f(j-1,0)+\sum_{l=j}^{i}E_l
$$
$$
f(i,0)=\max (f(i-1,0),f(i-1,1))
$$

第二个式子莫得问题，第一个式子需要优化。

我们先用前缀和化简。

$$
f(i,1)=\max_{j\in [i-k+1,i]} \small f(j-1,0)+s_i-s_{j-1}
$$
$$
f(i,1)=s_i+\max_{j\in [i-k+1,i]} \small f(j-1,0)-s_{j-1}
$$
$$
f(i,1)=s_i+\max_{j\in p[i-k,i-1]} \small f(j,0)-s_j
$$

设 $g(x)=f(x,0)-s_x$，那么化成 $f(i,1)=s_i+\max g(j)$，区间最大值，用单调队列维护。

自己写的单调队列结构体；

```cpp
struct monoque {
	int q[N],g[N],size,l,r;
	monoque(int x=0) {memset(q,0,sizeof(0));l=r=1;size=0;}
	void maintain(int x) {
		while(l<r&&x-q[l]>size) l++;
	}
	void push(int x,int val) {
		g[x]=val;
		while(l<r&&g[x]>g[q[r-1]]) r--;
		q[r++]=x;
	}
	int max() {return g[q[l]];}
};
```

主函数:

```cpp
int n,k,e[N],s[N],f[N][2];

signed main() {
	scanf("%lld%lld",&n,&k);
	for(register int i=1;i<=n;i++)
		scanf("%lld",&e[i]), s[i]=s[i-1]+e[i];
	monoque q; q.push(0,0); q.size=k;
	for(register int i=1;i<=n;i++) {
		q.maintain(i);
		f[i][0]=max(f[i-1][0],f[i-1][1]);
		f[i][1]=s[i]+q.max();
		q.push(i,f[i][0]-s[i]);
	}
	printf("%lld",max(f[n][0],f[n][1]));
	return 0;
}
```

---

## 作者：Apro1066 (赞：6)

动态规划+单调队列好题。

先考虑使用线性dp。令$dp[i]$表示前$i$头奶牛能得到的最大效率。在第$i$头奶牛，一定在区间$[i-k,i]$内有奶牛$j$得休息。在区间$[i-k,j]$内枚举休息的奶牛，则

$$dp[i]=max(dp[i],dp[i-1]+sum[i]-sum[j])$$

其中$sum[i]$表示前缀和，即奶牛区间$[1,i]$的效率和，$sum[i]-sum[j]$为奶牛区间$[j,i]$的效率和。答案为$dp[n]$。这个方程还是比较容易的吧。

于是我们写出代码，发现只有60分。2个WA，2个TLE。
```cpp
60分
#include <stdio.h>
#include <iostream>
using namespace std;
int n,k,a[100001],s,dp[100001],sum[100001];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register int i,j;
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];//前缀和 
	}
	
	for(i=1;i<=n;i++)
	{
		for(j=i-k;j<=i;j++)
		{
			dp[i]=max(dp[i],dp[j-1]+sum[i]-sum[j]);
		}
	}
	cout<<dp[n]<<endl;
	return 0;
}
```
为什么会T呢？因为$n$达到了$10^{5}$。显然$2$层循环会TLE。

我们再仔细思考一下，发现如果想要$dp[i]$尽可能大，不就是想让$dp[j-1]+sum[i]-sum[j]$尽可能大吗？

那我们把方程变形，得：

$$dp[i]=max(dp[i],dp[j-1]-sum[j])+sum[i]$$

此时$(i-k) \leq j \leq i$。

即把$sum[i]$放到外面，这样保证了想让$dp[i]$尽可能大，就只和$j$有关系了，即$max$内的值只和$j$有关。现在只需要用单调队列维护$dp[j-1]-sum[j]$就好了。

按照这个思路，还是60。。WA4个点，发现这题要开long long。。不开long long见祖宗啊。
```cpp
#include <stdio.h>
#include <iostream>
#include <deque>
#define ll long long int
using namespace std;
ll n,k,a[100001],s,dp[100001],sum[100001];
struct node
{
	ll v,position;//v为权，position是下标 
};
deque<node> dq;
inline void update(ll i)
{
	ll x(dp[i-1]-sum[i]);//维护dp[j-1]-sum[j] 
	while(!dq.empty() && dq.back().v<=x) dq.pop_back();//如果队尾小于dp[j-1]-sum[j]，全扔掉 
	dq.push_back({x,i});//新元素放进去 
	
}
inline ll query(ll i)
{
	while(!dq.empty() && dq.front().position<i-k) dq.pop_front();//检查是否在区间[i-k,i]内 
	return dq.front().v;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register ll i,j;
	cin>>n>>k;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]+a[i];//前缀和 
	}
	dq.push_back({0,0});//先压一个元素 
	for(i=1;i<=n;i++)
	{
		update(i);
		dp[i]=query(i)+sum[i];//dp[i]=max(dp[i],dp[j-1]-sum[j])+sum[i]
	}
	cout<<dp[n]<<endl;
	return 0;
}
```

---

## 作者：Palace (赞：4)

[走你](https://www.luogu.org/problemnew/show/P2627)

## 思路：

（18年秋清北提高综合班$DAY1$  $T2$）

（考试的时候除了单调队列都想的差不多了，最后光荣爆零）

做这道题的时候，看到不能连续开$k + 1 $个机器，就想到了本校$wucstdio$大佬在校$ACM$赛中出的$T3$，那道题是设$dp_i$表示第$i$个位置设烽火台的最小花费，但好像在这个题里不太合适，于是变通了一下，设$dp_i$表示第$i$个位置不开机器的最大效率，发现好像可行。

设$dp_i$表示第$i$个位置不开机器的最大效率，因为不能连续开$k+1$台，那么在$[i-k-1,i-1]$里一定有一个不开的，设这个位置为$j$，那么$[j+1,i-1]$的机器是都开着的，那么**状态转移方程**为：

$dp_i=max(dp_j+e_{j+1}+e_{j+2}……+e_{i-1})$

对于后面这一坨$e$，我们可以用**前缀和**优化：

$dp_i=max(dp_j-sum_j+sum_{i-1})$

但是还是会$TLE$。

我们发现，$max(dp_j-sum_j)$只与$j$有关，我们考虑**单调队列**优化。

我们设$a_j$表示$dp_j-sum_j$，如果$x<y$且$a_x\leq a_{y}$，那么$x$不会用来更新。

状态$z$用来更新$dp$数组。$z_1……z_p$满足：$z_i>z_{i-1}$且$a_{z_i}>a_{z_{i-1}}$

对于一个新的状态$z$，如果队首不满足$a_{z_i}> a_z$就出队直到满足，同时要注意**队尾的边界**问题。

## 代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

#define N 100010
#define LL long long

using namespace std;

LL n, k, maxn, ans, head = 1, tail = 1;
LL c[N], sum[N], dp[N], q[N], a[N];

LL max( LL a, LL b ) {
    return a > b ? a : b;
}

int main() {
    scanf( "%lld%lld", &n, &k );
    for( LL i = 1; i <= n; i++ ) {
        scanf( "%lld", &c[i] );
        sum[i] = sum[i - 1] + c[i];
    }
    for( LL i = 1; i <= n + 1; i++ ) {/*
        maxn = -1;
        for( LL j = max( 0ll, i - k - 1 ); j <= i - 1; j++ )
            maxn = max( dp[j] - sum[j] + sum[i - 1], maxn );
        dp[i] = max( dp[i], maxn );*/
        while( head <= tail && q[head] < i - k - 1 ) head++;
        //if( q[head] < i - k - 1 ) head++;
        dp[i] = dp[q[head]] - sum[q[head]] + sum[i - 1];
        while( head <= tail && dp[q[tail]] - sum[q[tail]] <= dp[i] - sum[i] ) tail--;
        q[++tail] = i;
    }
    printf( "%lld\n", dp[n + 1] );
    return 0;
}
```

---

## 作者：tth37 (赞：4)

一道单调队列入门题。

面对动规题，首先设计状态转移方程。令$f[i]$表示$1-i$中连取不超过$K$个数，且**第$i$个数不取**所能累加的最大和。

因为第$i$个数不取，所以在$i$之前一定连取了一段数。这段数的长度可能为$0-K$（注意是$0-K$而不是$1-K$，可以通过手推样例发现最优解中可能存在连着两个数不取的情况）。连取的一段数所能累加的和可以用前缀和计算。考虑边界条件后，状态转移方程如下：

$$
f[i]=\max_{i-K-1\le j \le i-1} \lbrace f[j]+s[i-1]-s[j] \rbrace
$$

由于$max$函数的循环变量是$j$，所以**只与$i$相关的变量**$s[i-1]$可以作为常数提出到$max$函数之外，即：

$$
f[i]=\max_{i-K-1\le j \le i-1}\lbrace f[j]-s[j]\rbrace +s[i-1]
$$

将状态转移方程化简到这样，就已经可以用单调队列进行优化了。我们可以用单调队列维护$f[j]-s[j]$的最值，在循环时将其最大值取出再加上$s[i-1]$即为$f[i]$。

如果想不到该如何操作，也可以这样理解：

$$
g[i]=f[i]-s[i]
$$
$$
f[i]=\max_{i-K-1\le j \le i-1}\lbrace g[j]\rbrace+s[i-1]
$$

由于我们定义$f[i]$是第$i$个数不取的最优解，可以强行求解$f[N+1]$（虽然它似乎没有实际意义）作为本题的最终答案。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, K;
ll s[100005], f[100005];
int q[100005];

int main() {
    scanf("%d%d", &N, &K);
    for (register int i = 1; i <= N; ++i) {
        scanf("%lld", &s[i]);
        s[i] += s[i-1];
    }
    int l = 0, r = 1;
    q[0] = 0, f[0] = 0;
    for (register int i = 1; i <= N + 1; ++i) {
        while (l < r && q[l] < i - K - 1) l++;
        f[i] = f[q[l]] - s[q[l]] + s[i-1];
        while (l < r && f[q[r - 1]] - s[q[r - 1]] < f[i] - s[i]) r--;
        q[r++] = i;
    }
    printf("%lld", f[N + 1]);
    return 0;
}
```

---

## 作者：asuldb (赞：4)

一句话题意：给定有n个数的序列，选择其中一些数，使得不能有超过k个数连续，且选择的数的和最大

我们发现如果我们在dp的时候来判断哪些数留下来不太滋磁，于是我们在dp的时候判断让那些数删去，最后用总和一减就是答案了

于是我们用f[i]表示从1到i去除包括a[i]在内的一些数并符合条件的最小值，于是在最开始我们直接把使f[i]=a[i]就好了

那我们想选择删去a[i]这个数的话只要在保证i这个位置前面k+1个数中有一个被选择删去就好了，当然删去这个位置也会使这个位置前面满足条件，于是就有f[i]=a[i]+min(f[j])(i-k-1<=j<=i-1)我们注意到这里的f[j]是与i没有什么关系的，那就跟滑动窗口没什么区别了，于是我们就可以用单调队列来优化这个dp了

记得最后统计答案时要从n-k到n找最小值

之后就是丑陋的代码了
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define re register
#define maxn 100001
#define int long long
using namespace std;
int f[maxn],a[maxn],tot;
int n,k;
struct node
{
	int p,w;
};
inline int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')
	  x=(x<<3)+(x<<1)+c-48,c=getchar();
	return x;
}
signed main()
{
	n=read();k=read();
	for(re int i=1;i<=n;i++)
		a[i]=f[i]=read(),tot+=a[i];
	deque<node> q;
	for(re int i=1;i<=k+1;i++)
	{
		while(q.size()&&f[i]<q.back().w) q.pop_back();
		q.push_back((node){i,f[i]});
	}
	for(re int i=k+2;i<=n;i++)
	{
		while(q.size()&&q.front().p<i-k-1) q.pop_front();
		f[i]+=q.front().w;
		while(q.size()&&f[i]<q.back().w) q.pop_back();
		q.push_back((node){i,f[i]});
	}
	int minn=999999999999999999;
	for(re int i=n-k;i<=n;i++)
	minn=min(minn,f[i]);
	cout<<tot-minn;
	return 0;
}
```


---

## 作者：薛定谔的鱼 (赞：3)

。dp无疑了其实。（语言表述能力是一个迷，所以解释的应该会很迷，请优先看代码，后看注释）

在考场上，我写了一个错解，但是数据小都能过，只是会爆空间，考场上想着怎么用滚动数组优化来着。。。。把错解的方程列出来吧
```cpp
for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=k;j++)
		{
			if(j!=0)
			dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]+a[i]);//dp[i][j]第i个是当前序列连续的第j个，于是得到此方程式
			else
			dp[i][j]=ans;
			ans=max(dp[i][j],ans);
		}
	}
```

很明显错的了。但是回家发现离正解也差得不远了。我一开始已经想到了前缀和，但是不知道哪里出了点问题。

总结错误原因：空间炸了。观察方程，其实除了的小问题在这里：我明明可以把一整段加起来，但是却用了单个的加，这就导致了时空的炸裂。

于是改造dp数组：还是前i个点，但是第二个改造为j为断点，所以dp表示前i个点在j断时的最大值，方程：
dp[i]=max(dp[i],dp[j-1]+a[j]+...+a[i]);

dp类似一个前缀和吧。可以把后面一大串的a[j]+...+a[i]用前缀和维护，就变成了
dp[i]=max(dp[i],dp[j-1]+sum[i]-sum[j]);

所以，dp里面的值只和一个变量有关，所以可以使用（我及其不熟练的）单调队列进行维护。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
int n,m;
int a[maxn];
int sum[maxn];
int dp[maxn];
int que[maxn];//队列下标
int d[maxn];//值
int h=0,t=1;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]+a[i];//前缀和
	}
	for(int i=1;i<=n;i++)
	{
		d[i]=dp[i-1]-sum[i];//首先，队尾值是当前值
    	while(h<=t&&d[que[t]]<d[i])t--;//然后比较此值与队列前值的大小，找到一个左边比他小右边比他大的值的位置，更新队列
    	que[++t]=i;//标此时，t指向的是那个比他小的数，我们把对尾覆盖，保证了单调性
    	while(h<=t&&que[h]<i-m)h++;//更新头指针，保持头最大
		dp[i]=d[que[h]]+sum[i];//加值
	}
	printf("%d",dp[n]);
	return 0;
}
```
估计有很多讲的不好不对，我自己都还有点懵呢，希望大佬指正。

（我恨dp）

---

## 作者：王珩030115 (赞：3)

如果考虑使用哪些牛，则情况复杂，如果反过来考虑不取哪些牛，那么题目就变成了简单的线性dp，不会推方程的同学可以转——>普及试炼场,当然，还需要使用单调队列优化，不清楚的同学可以先做一下滑动窗口。

关于long long 和int 。。。。。。
（2018 day1 t1 作死用了int，
本题又用int WA了30min）

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100002
long long i,j,k,n,m,f[maxn],a[maxn],q[maxn];
int main()
{
	long long sum=0;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)
	{
	   scanf("%d",&a[i]);
	   sum+=a[i];
}
    int front=1,rear=1;
     for(i=1;i<=n;i++)
     {
       while(front<=rear&&i-q[front]>k+1) front++;
	   f[i]=a[i]+f[q[front]];
	   while(front<=rear&&f[q[rear]]>=f[i]) rear--;
	   q[++rear]=i;
}
    for(i=n-k;i<n;i++)    //此处要注意 
       f[i+1]=min(f[i+1],f[i]);
    printf("%lld",sum-f[n]);
	return 0;
}
```

---

## 作者：狸狸养的敏敏 (赞：3)

思路1：$O(N^2)$算法

首先必须要考虑到，这题转化后就是求在$N$个数每$K+1$个数删去一个数，并求最大值

一种非常容易想到的思路就是DP，从1到N枚举，第二维从i到N枚举，然后 前缀和+DP 乱搞就好了

显然，这种算法度复杂度是$O(N^2)$的，~~N方过百万~~，我们普遍认为计算机1s能够计算$10^9$次（luogu神机也许更多，CCF老爷机也许更少）

再看数据范围，$N\le 100000$，显然，这种算法虽然正确，但是并不怎么符合我们的时限要求

考虑优化：

如果一头奶牛比当前枚举到的奶牛小，还比他弱，那么这头奶牛就没有用了，我们可以用这个方法来维护一个单调上升的序列，即我们的单调队列!

单调队列涉及去头，删尾两个操作

什么时候去头呢？

当头位置的已经没法再给当前位置做贡献的时候（即已经超出K+1的限制的时候），我们去头，因为他已经没有用了

什么时候删尾呢？

当尾部的位置不如当前位置的时候，我们把尾部位置的牛替换为当前牛，以获得最大收益

很明显，我们这道题必须使用这种方法求解，最优情况下，复杂度是可以降到$O(N)$的，差一点的估计就是$O(KN)$(K为3-5之间的一个常数)

$O(NlogN)$也是常见的复杂度，往往出现在限制与单调性难以统一的情况下，不过也能过

那么，这道题的复杂度不就降下来了?

实现方法，本人使用队列进行模拟，似乎C++的deque也是不错的选择，只不过我不怎么会用QwQ

有会用deque的dalao教教我呗2333

详见代码(似乎单调队列不是pj组考的内容。。。不过ZJ哪有什么pj，tg之分2333)

```
#include<bits/stdc++.h>//万能头不解释
#define ll long long //宏定义long long秀一脸
using namespace std;//调用命名空间
ll sum[111111],f[111111],d[111111],q[111111];//sum数组维护前缀和，用以查询区间内奶牛的收益总和
//f数组用来转移状态
//d数组用来存储k头牛前的状态
//q数组用来维护单调上升的序列
int n,k,head,tail;//n,k如题意，head，tail分别指向队列的头、尾
void put(int j){
    d[j]=f[j-1]-sum[j];//储存状态，后面的去头工作可能要用到
    if(j>=k+1&&d[j-k-1]==q[head])
        head++;//去头
    while(head<tail&&d[j]>q[tail-1])
        tail--;//删尾，当尾部的牛不如自己时，把他们弹(zhu)出(le)去(chi)
    q[tail++]=d[j];//把状态储存进队列尾部，维护起一个单调上升并且始终最优的序列
}
int main(){
    head=0,tail=1;//初始化头指针和尾指针
    scanf("%d%d",&n,&k);//输入N，K
    for(int i=1;i<=n;i++){
        ll x;
        scanf("%lld",&x);
        sum[i]=sum[i-1]+x;//维护前缀和
    }
    for(int i=1;i<=n;i++){
        put(i);//操♂作，考虑i这头牛的最优位置
        f[i]=q[head]+sum[i];//更新答案
    }
    printf("%lld\n",f[n]);//输出结果
    return 0;//再见各位QWQ
}
```

~~我觉得虽然思路差不多，但是我讲的会不会稍微详细辣么一点点呢QWQ~~

---

## 作者：qa24601 (赞：3)

今天考了这道题

70分还是很容易打的

然而dalao们的单调队列都看得很迷（主要是楼下的，竟然把特判藏起来了=n=）

辣么写一份优先队列的题解把

（DP的公式还是很容易想的啦就不说了233）

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int max_size = 100000;
long long F[max_size + 1];
long long E[max_size + 1];
//按值从大到小排序，值相同则按位置从先到后排序（若不按照位置排序可能会把本来能在后面使用的值先pop掉）
struct node {
    int pos;
    long long val;
    bool operator<(const node &x) const {
        if (val != x.val) {
            return val < x.val;
        } else {
            return pos < x.pos;
        };
    };
};
priority_queue<node> p;
int N, K;
int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        cin >> E[i];
        E[i] += E[i - 1];
    };
    p.push({0, 0});//特判：保证F[1]的正常产出
    for (int i = 1; i <= N; ++i) {
        p.push({i, F[i - 1] - E[i]});
        while (!p.empty() && p.top().pos < i - K) {//舍去非法内容
            p.pop();
        };
        F[i] = p.top().val + E[i];
    };
    cout << F[N] << endl;
};
```

---

## 作者：你的背包 (赞：2)

优先考虑动态规划
,首先维护一个前缀和sum[i]

状态：设F[i][0]表示以i结尾的并且这个数字不选所得的最大效率值；F[i][0]表示以i结尾并且i这个数字选所得的最大效率值

易得转移方程为:

F[i][1]=max(F[j][0]+sum[i]-sum[j])  {i-k<=j<i}

F[i][0]=max(f[i-1][0],f[i-1][1])

可以变形为F[i][1]=max(F[j][0]-sum[j])+sum[i]       {i-k<=j<i}

参考代码
```cpp
#include<iostream>
using namespace std;
long long n,k,a[200005],num[200005],q[200005],s[200000],f[200005][2];
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	int head=1,tail=1;
	for(int i=1;i<=n;i++)
	{
	     f[i][0]=max(f[i-1][0],f[i-1][1]);
	     while(q[head]<i-k&&head<=tail)head++;
	     f[i][1]=f[q[head]][0]-s[q[head]]+s[i];
	     while(f[i][0]-s[i]>f[q[tail]][0]-s[q[tail]]&&head<=tail)tail--;
	     q[++tail]=i;
	}cout<<max(f[n][1],f[n][0])<<endl;
}    
```

---

## 作者：HH_Halo (赞：1)

# Mowing the Lawn G「单调队列优化DP」
[博客食用效果更佳](https://www.cnblogs.com/hhhhalo/p/13391805.html)
## 思路分析
* 首先不难想到，每只奶牛在当前选或者不选都有可能对后续的最佳答案产生影响，所以我们在转移时完全可以将这两个状态分开来存，即开一个**二维**的$f$数组。
* 另外像这种需要**连续**选物品的$DP$，使用**前缀和**数组会有奇效
* 定义$f[i][0/1]$数组表示到第i头牛，状态为$0/1$的情况，$0$表示不选，$1$表示选。那么两种状态的转移方程就可以得出：
	* 对于不选的情况，我们直接从上一个转移即可，即：$f[i][0] = max(f[i-1][1],f[i-1][0])$。
    * 选了的情况相对复杂，我们让当前这头牛为一连串牛的结尾，遍历起点，则有：$f[i][1] = max(f[i][1],f[j-1][0]+sum[i]-sum[j-1])$;

  ~~信心满满的交上去，70分T掉~~
* 显然，这样的转移方程在一串牛的长度很长时时间效率会很低，所以考虑优化
* 仔细看一看$f[i][1]$的这个转移方程，我们是以$i$为终点寻找一个最优起点，那最最优的起点应该有两条性质：
	1. 效率值大
    2. 位置靠后(这样才可以形成更长的序列)
* 根据上面的性质，**对于一些两个都不符合的点，显然就没有机会再选了**，要想对后面的情况产生贡献，最起码得占一个，显然要用**单调队列**来维护，这也是单调队列的核心思想：人家比你小还比你强，凭什么选你
* 根据上面的转移方程，因为$sum[i]$是定值，所以用队列维护$f[j-1][0]-sum[j-1]$就可以了（别把前缀和丢了）


管理大大审核辛苦了qwq
## Code
```c++
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 100010
#define ll long long
using namespace std;
inline ll read(){
	ll x = 0,f = 1;
	char ch =getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x * f;
}
ll n,k;
ll f[N][2],e[N],sum[N],q[N];
int main(){
	n = read(),k = read();
	for(int i = 1;i <= n;i++){
		e[i] = read();
		sum[i] = sum[i-1] + e[i];
	}
	int head = 0,tail = 1;//注意队首为0，要不你会默认最开始1不选是最优的
	q[tail] = 1;
	f[1][1] = e[1];
	for(int i = 2;i <= n;i++){
		while(head<=tail && i-q[head] > k)head++;
		f[i][1] = f[q[head]][0] + sum[i] - sum[q[head]];//既然在队首没被弹掉，肯定是最大的啦
		f[i][0] = max(f[i-1][0],f[i-1][1]);//这个直接转移就行
		while(head<=tail && f[i][0]-sum[i]>=f[q[tail]][0]-sum[q[tail]])tail--;
		q[++tail] = i;
	}
	printf("%lld\n",max(f[n][0],f[n][1]));
	return 0;
}
```

---

## 作者：zimindaada (赞：1)

[题面](https://www.luogu.com.cn/problem/P2627)

这一道题很明显是一个$O(n)$或$O(n log n)$的DP。

我是令$f_i$为前$i$头牛（满足条件）的排列中最高的价值，首先，我们可以先推出来一个暴力DP式子：

$f_i = max(f_{j-1}+sum_i-sum_j)(j∈[i-k, i])$，其中$sum_i$表示到$f_i$的前缀和。

我们可以看出，在式子里$sum_i$是不变量，可以把他从max里面提出来，则$f_i = max(f_{j-1}-sum_j)+sum_i$  。那我们可以把$f_{j-1}-sum_j$做成单调队列，以加快维护速度。

```cpp
//Luogu P2627 修剪草坪
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+7;
inline ll read() {
    int ret=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f;ch=getchar();}
    while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    return ret*f;
}
ll n, k, a[maxn], s[maxn];
ll q[maxn], head, tail;
ll f[maxn], b[maxn];
signed main(){
    n = read(), k = read();
    for(int i = 1; i <= n; ++i){
        a[i] = read();
        s[i] = s[i-1]+a[i];
    }
    for(int i = 1; i <= n; ++i){
        //单调队列:更新
        b[i] = f[i-1] - s[i];
        while(tail >= head && q[head] < i-k) ++head; 
        while(tail >= head && b[i] > b[q[tail]]) --tail;
        q[++tail] = i;
        f[i] = b[q[head]] + s[i];
    }
    printf("%lld\n",f[n]);
    return 0;
}
```


---

## 作者：Forever丶CIL (赞：1)

这个题，我们可以抽象成：

从一个序列中每隔1~k的长度取走一个数，使取走的数之和最小

考虑可以动规一下233；

设f[i]为取到第i位的最优解

顺着想：

第i位数可以从第i-k-1~i-1位数转移过来

那么我们自然要找f[i-k-1]~f[i-1]中最小的那个转移啦；

逆着推：

    f[i]=min(f[i+j]+E[i],f[i])  (1<=j<=k+1)

顺着推这个方程也是可以的，只是个人喜好233

这样的话，很明显复杂度是O(n^2)的，明显TLE了

那怎么办呢？

在回过头来看看方程，会发现什么特点？

在“顺着想”中已经提到了每次我们都是找一个区间最小值；

所以可以用单调队列优化到O(n)



------------


```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll; //用 ll 代替掉 long long，写起来方便一些 
const ll inf=1000000000000000001ll;  //数比较大，要开long long才可以 
ll E[101010];
ll f[101010];
int n,k;
ll ES=0ll;
ll ans=inf;
struct Queue 
{
    ll v;
    int num;
};
struct Queue Q[100101];   //单调队列
void dp()
{
    int tail=0,head=1;
    for(int i=n+k;i>=n+1;i--)    //先预处理出一部分 
    {
        while(f[i]<=Q[tail].v&&head<=tail)
            tail--;
        Q[++tail].v=f[i];
        Q[tail].num=i;
    }
    for(int i=n;i>=1;i--)   //更新f数组 
    {
        while(Q[head].num>i+k)
            head++;
        f[i]=E[i]+Q[head].v;
        while(f[i]<=Q[tail].v&&head<=tail)
            tail--;
        Q[++tail].v=f[i];
        Q[tail].num=i;
    }
}
void print()
{
    for(int i=1;i<=n;i++)
    {
        printf("%d ",f[i]);
    }
}
int main()
{ 
    scanf("%d%d",&n,&k);  
    k++;  //这有一个 k++ 大家可以想想是为什么
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&E[i]);
        ES+=E[i];
    }
    dp();
    for(int i=1;i<=k;i++)
    {
        ans=min(ans,f[i]);
    }
    printf("%lld",ES-ans);
    return 0;
}
```


------------

因为题目要求连续的牛不超过k个，所以允许连续k个，所以每次转移时
可以从i-k-1处转移  样例———> 

k=2

| 1 | 2 | 3 | 4 | 5 |
| -----------: | -----------: | -----------: | -----------: | -----------: |
|  a-k-1| a-k | a-1 | a | a+1 |



      


不知道大家伙理解了没有

可以先做一下P1725 琪露诺 这之后再来做这个题就轻松一些


------------

```cpp
O(n^2) dp:
void dp()
{
    for(int i=1;i<=n;i++)
    {
        f[i]=inf;
    }
    for(int i=n;i>=1;i--)
    {
        for(int j=1;j<=k;j++)
        {
            f[i]=min(f[i+j]+E[i],f[i]);           
        }
    }
}
```
送大家一组样例
6 1
4 7 2 0 8 9  -> 16

不用谢我233



------------


rp++

---

## 作者：CaCl2 (赞：1)

[点此获得更好的阅读体验](https://www.cnblogs.com/LJA001100/p/10500501.html)

题目链接 [bzoj 2442](https://www.lydsy.com/JudgeOnline/problem.php?id=2442) [洛谷2627](https://www.luogu.org/problemnew/show/P2627)
线性DP+单调队列优化

DP好题，不过需要单调队列优化（不用优化有60分），还要开longlong

代码(因为我有重度STL依赖症，连手写队列都不会了，所以用了deque)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
long long a[120000];
long long m = 0;//总效率
long long f[120000] = {0};
//f数组，用来存储去除第n头奶牛时要去除多少效率，不开longlong后果自负
deque<int> q;
//用deque来存储单调队列
int main(){
    scanf("%d%d",&n,&k);
    for(int i = 1;i<=n;i++){
        scanf("%lld",&a[i]);
        m += a[i];
    }
    q.push_front(0);
    for(int i = 1;i<=n+1;i++){
    	while(i-q.front()>k+1) q.pop_front();
        //如果队首到i大于k(有超过k头连续奶牛)则弹出队首
    	f[i] = f[q.front()] + a[i];
    	while(f[q.back()]>f[i]) q.pop_back();
        //如果前面的反而更小就弹出前面的
    	q.push_back(i);
    }
    printf("%lld",m-f[q.front()]);
    //因为队首一定最优，所以直接输出总效率-队首即可
    return 0;
} 
```

---

## 作者：BeyondStars (赞：1)

其实就是单调队列优化的dp。首先，我们先设计一个最朴素的方程，之后再来优化。不难~~难死我了~~ 设计出如下方程
$$F[i] = \underset{i-K \leq j\leq i}{max}(F[i],F[j-1]+sum[i]-sum[j])$$

`F[i]`的含义是前$i$头奶牛中，选一些奶牛获得的最大效率。然后因为一段连续的奶牛不能超过$K$，所以要枚举一下断点$j$，这个$j$号奶牛不选。于是乎就可以推出如下方程。我们发现i可以看做是常量，那么就可以使用单调队列优化，优化后的方程式如下
$$F[i] = \underset{i-K \leq j\leq i}{max}(F[i],F[j-1]-sum[j])+sum[i]$$
那么，我们就维护一个**$j$单调递增，$F[j-1]-sum[j]$也单调递增的单调队列**，为什么可以这样呢？因为我们发现对于$k_1$和$k_2$有$i-K\leq k_1<k_2<i$如果有$F[k_1-1]-sum[k_1]<F[k_2]-sum[k_2]$那么，就意味着$k_2$永远不会成为最优解，也就是说$k_2$将永远不会成为决策的一部分，那么我们还考虑它干嘛？直接删掉不管了。这就是单调队列优化dp的精髓。通俗一点，就是如果k1比k2小，并且它代表的值还比k2小，也就是说它的生存能力小于k2，就可删掉。~~当一个选手比你小，还比你强，你就永远打不过他了~~
然后看了题解开心的像个智商250的智障~~NOIP2018我250分~~一样的我开始写起了代码。
```cpp
//
// Created by dhy on 18-12-31.
//
#include <iostream>
#include <deque>
using namespace std;
long long F[100010];
long long s[100010];
long long d[100010];
int main(){
    int N,K;
    cin>>N>>K;
    for(int i = 1;i<=N;i++){cin>>s[i];s[i]+=s[i-1];}
    deque<int> q;
    for(int i = 1;i<=N;i++){
        d[i] = F[i-1]-s[i];
        while(!q.empty()&&d[q.back()]<=d[i])q.pop_back();
        q.push_back(i);
        while(!q.empty()&&q.front()<i-K)q.pop_front();
        F[i] = d[q.front()]+s[i];
    }
    cout<<F[N]+1;
    return 0;
}
```
然后挂了9个点，冥思苦想不得其因。然后看了题解，我也没搞懂l = 0 r = 1的含义。然后瞎向单调队里里面加了两个元素0和1，洛谷数据过了，但是bzoj数据却过不了。然后又一次陷入沉思，突然，我想起了四个字：**初始状态**。对呀！我的单调队列没有维护初始状态。对于$i<k$我们直接$F[i] = sum[i]$，然后维护一下单调队列就完事了呀！于是乎花了5小时终于A了这道题。
```cpp
//
// Created by dhy on 18-12-31.
//
#include <iostream>
#include <deque>
using namespace std;
long long F[100010];
long long s[100010];
long long work(int j){return F[j-1]-s[j];}
int main(){
    long long N,K;
    cin>>N>>K;
    for(int i = 1;i<=N;i++){cin>>s[i];s[i]+=s[i-1];}
    deque<int> q;
    for(int i = 1;i<=K;i++){
        F[i] = s[i];
        while(!q.empty()&&work(q.back())<=work(i))q.pop_back();
        q.push_back(i);
    }
    for(int i = K+1;i<=N;i++){
        while(!q.empty()&&q.front()<i-K)q.pop_front();
        while(!q.empty()&&work(q.back())<=work(i))q.pop_back();
        q.push_back(i);
        F[i] = work(q.front())+s[i];
    }
    cout<<F[N];
    return 0;
}
```
好了，到这里，我又积累了一点关于dp的坑了。~~元旦作业呀，做不完了~~
推销一下我的博客[dhy的博客](denghaoyu.leanote.com)

---

## 作者：曹老师 (赞：1)

~~蒟蒻此题写了一上午~~

AC了之后发现 也就是DP + 优先队列

状态转移方程 **f[i]=sum[i]+max(f[j]-sum[j+1])**

其中 **sum为前i项的和（前缀和求） **

**j+1 为删去的点的编号 有范围限制：i-k<=j<=i**

**注意：你要是循环i的时候一定要从1开始 否则就删不了1号**

其实不必每次都要取最大值~~（70与100的差距在这）~~

我们可以把每一次求出来的值压入优先队列

```cpp
        m.num=i+1,m.ch=f[i]-sum[i+1];
        que.push(m);
```

一定要一致！！！

前k个单独处理 我这里用的i循环

所以要从0 跑到 k （在这里陷了好长时间）

还有一定要注意的是：前k个单独处理的时候 直接f[i]=sum[i]

而不是你输入的数

**即：输入只是为了求前缀和 其他的交给sum数组来做**

还有呢  就是输出f[n] 不是别的

在找是否满足条件的过程中 要pop()

不满足条件的就弹出 满足条件就用 que.top() 来取

每一次只往里队列里压 不弹

唯独查找的时候pop出来

**保证每一个i都只进入1次 最多弹出2次**

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue> 
#define MAXN 100005
#define LL long long
#define MOD 100000007
using namespace std;
struct qqq{
    LL int num,ch;
  	bool operator < (const qqq &x)const{
            return ch < x.ch;
      }
};
LL int n,k,l,w[MAXN],f[MAXN],sum[MAXN],t;
priority_queue<qqq>que;
int main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&w[i]);
        t+=w[i];
        sum[i]=t;
    }
    for(int i=0;i<=k;i++)
    {
        qqq lm;
        f[i]=sum[i];
        lm.num=i+1,lm.ch=f[i]-sum[i+1];
        que.push(lm);
    }
    for(int i=k+1;i<=n;i++)
    {
        qqq m;
        while(que.top().num<i-k)
            que.pop();
        f[i]=sum[i]+que.top().ch;
        m.num=i+1,m.ch=f[i]-sum[i+1];
        que.push(m);
    }
    printf("%lld",f[n]);
    return 0;
}
```

---

## 作者：Priori_Incantatem (赞：0)

#### 题目大意
给出一个长度为 $n$ 的序列，你可以取若干个数，但要求最多只能连续取 $k$ 个数，求最大能取出的数的总和

$n \le 10^5$，想要快速求和，首选前缀和

考虑 $f[i][0]$ 表示前 $i$ 个数，第 $i$ 个数不取时的最优答案
$f[i][1]$ 就为第 $i$ 个数取时的最优答案

上面这个状态，可以很轻松的想到 $O(n^2)$ 的转移：  
$f[i][0]=max(f[i-1][0],f[i-1][1])$，此部分 $O(1)$ 就可以处理完
$f[i][1]=max \{ f[j][0]+\sum_{k=j+1}^{i} a[i] \}$，$(i-k \le j \le i-1)$ 也就是：  
$f[i][1]=max \{ f[j][0]+s[i]-s[j] \}$
$f[i][1]=max \{ f[j][0]-s[j] \} +s[i]$ （将$s[i]$提出来）

我们上面将 $s[i]$ 提出后，就变成了求 $f[j][0]-s[j]$ 的最大值，最后加上 $s[i]$。这里我们就可用单调队列来维护最大值啦！

**十年OI一场空，不开long long见祖宗**

**AC代码：**

```cpp
#include<cstdio>
#include<iostream>
#include<deque>
using namespace std;
const long long Maxn=100000+20,inf=0x3f3f3f3f;
long long a[Maxn],s[Maxn],f[Maxn][2];
deque <long long> q;
long long n,k;
inline long long read()
{
	long long s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
void pop(long long x)
{
	while(1)
	{
		if(q.empty())break;
		if(q.front()>=x-k)break;
		q.pop_front();
	}
}
void push(long long x)
{
	while(1)
	{
		if(q.empty())break;
		long long i=q.back();
		if(f[i][0]-s[i]>=f[x][0]-s[x] && i!=x)break;
		q.pop_back();
	}
	q.push_back(x);
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read(),k=read();
	for(long long i=1;i<=n;++i)
	a[i]=read(),s[i]=s[i-1]+a[i];
	
	for(long long i=1;i<=n;++i)
	{
		pop(i);
		push(i-1);
		long long j=q.front();
		f[i][1]=s[i]+f[j][0]-s[j];
		f[i][0]=max(f[i-1][1],f[i-1][0]);
	}
	printf("%lld\n",max(f[n][0],f[n][1]));
	
	return 0;
}
```

---

## 作者：Partial (赞：0)

- 这是一道单调队列的题。
- Q：为什么单调队列可以优化复杂度？
- A：原因在于它能够减少无用状态的统计。


------------
for example：对于一个f数组它的状态转移方程是 
f[i]=max{f[j]+w[j]}-a;
其中w[i]不能变动，a也是常量.

- 这时你就可以使用单调队列
- 队头放当时最大值，每次新更新出来的用队尾进行比较，再加入这个值的同时维护其单调递减的性质

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
ll a[N],f[N][2];
ll n,k,s[N];
ll h=1,t=1,q[2*N][2];
int main()
{
	std::ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>a[i],s[i]=s[i-1]+a[i];
	for(int i=1;i<=n;++i)
	{
		while(h<=t&&q[h][1]<i-k)h++;
		f[i][0]=max(f[i-1][1],f[i-1][0]);
		f[i][1]=q[h][0]+s[i];
		while(h<=t&&q[t][0]<=f[i][0]-s[i])t--;
		t++;q[t][0]=f[i][0]-s[i];q[t][1]=i;
	}
	cout<<max(f[n][0],f[n][1]);
} 
```
- 附：状态有约束范围的把不符合的踢出

---

