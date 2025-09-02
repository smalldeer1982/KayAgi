# [SHOI2001] Panda的烦恼

## 题目描述

panda 是个数学怪人，他非常喜欢研究跟别人相反的事情。最近他正在研究筛法，众所周知，对一个范围内的整数，经过筛法处理以后，剩下的全部都是质数，不过 panda 对这些不感兴趣，他只对被筛掉的数感兴趣，他觉得在这些被筛掉的数中一定隐藏着重要的宇宙秘密，只是人们还没有发现罢了。

panda 还觉得如果只是单纯地从小到大筛的话，还不足够发现其中的奥秘，于是他决定对至多只包含某些质因数的数进行研究（比如说至多只包含质因数  $2,3$ 的数有  $2,3,4,6,8,9,\ldots$），他需要得到这些数中第  $k$ 小的数（ $k$ 是 panda 认为的宇宙系数），请你编个程序，帮助他找到这个数。

## 说明/提示

#### 样例解释

前六个数分别是  $3,5,9,15,25,27$。

#### 数据范围及限制

对于所有数据，有  $1\le n\le 100$， $1\le k\le 10^5$， $p_i\in\text{prime}$， $p_i\le 10^3$， $p_i\not=p_j(i\not=j)$， $1\le ans\le 2\times 10^9$。

## 样例 #1

### 输入

```
2 7
3 5```

### 输出

```
45

```

# 题解

## 作者：piggy (赞：28)

\* 附上博客链接  http://blog.csdn.net/jackypigpig/article/details/75213835

\* 鉴于 n 十分小，k 又十分大，而且发现 n\*k 的时间也是可以的，于是就想想用普通数组来模拟出优先队列。我用了个 b[i] 来记录第 i 个素数当前乘到了 ans[] 中第几个数（好像是下一个应该乘的数），然后每次要加一个数到 ans[] 中时，对每个素数乘一下它下一个要乘的，取出最小值，判一下重，如果无恙就放到 ans[] 后面即可。

\* 这样就保证了 ans[] 数组中的元素是单调递增的，而且不会跳元素。

\* 时间复杂度应该就是 n\*k

程序
```cpp
#include <cstdio>
int n,k,cnt;
int a[1005],b[1005],ans[100005];

int main(){
    scanf("%d%d",&n,&k);
    for (int i=1; i<=n; i++) scanf("%d",&a[i]);
    ans[0]=1;
    while (cnt<k){
        int Min=2147483647,Minx;
        for (int i=1; i<=n; i++)
            if (ans[b[i]]*a[i]<Min){
                Min=ans[b[i]]*a[i];
                Minx=i;
            }
        b[Minx]++;
        if (Min!=ans[cnt]) ans[++cnt]=Min;
    }
    printf("%d",ans[k]);
}
```

---

## 作者：Leap_Frog (赞：24)

### P.S.
此题较为毒瘤，需要开long long以及加优化。  
普通的构造方法貌似不能过QwQ。  

### Problem.
给定一堆质因数，求这些质因数构成（乘积）的所有数中的第K小值。  

### Solution.
首先，我们一看到这道题，笔者第一时间想到要用STL中的set来构造。  
于是就写了一个简单的代码（解释在代码注释中）。  
因为小的数$\times$
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n,k,a[105];set<int>s;//STL set万岁
int main()
{
	scanf("%d%d",&n,&k),s.insert(1);//插入1
	for(int i=1;i<=n;i++) scanf("%d",a+i);//读入n个质因数
	for(int i=1;i<k;i++)//因为要求第k大，所以要删去k-1个比它小的数
	{
		int t=*s.begin();s.erase(s.begin());//把当前最小的拿出来并删去
		for(int i=1;i<=n;i++) s.insert(t*a[i]);//构造出当前最小的能到达的所有数
	}
	return printf("%d\n",*s.begin()),0;//输出删去k-1个最小数后的第k个
}
```
然后结果我们一运行。。。$\color{red}\texttt{WOC}\text{怎么样例都不过啊}$  
然后我们再来仔细读一读题目  
> 比如说至多只包含质因数2，3的数有2,3,4,6,8,9,……  

好罢被坑了，1是无法构造出来的，所以要求第k个质因数是第k+1个。  
恭喜笔者绕过了第一个弯QAQ。  

然后笔者再打出这样一份代码	
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[105];set<long long>s;
int main()
{
	scanf("%d%d",&n,&k),s.insert(1);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=k;i++)//修改唯一一处：<k变成<=k
	{
		int t=*s.begin();s.erase(s.begin());
		for(int i=1;i<=n;i++) if(t*a[i]<=2000000000) s.insert(t*a[i]);
	}
	return printf("%lld\n",*s.begin()),0;
}
```
样例是过了，但是$\color{red}\texttt{WOC}\text{为什么}\texttt{WA40}\text{啊}$  
笔者仔细地看了看错误信息。  
> Wrong Answer. wrong answer On line 1 column 1, read -, expected 6.

好罢，知道了，没开long long。  
恭喜笔者绕过了第二个弯。  

然后笔者又打出了第三份代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[105];set<long long>s;//修改：int变成long long
int main()
{
	scanf("%d%d",&n,&k),s.insert(1);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=k;i++)
	{
		long long t=*s.begin();s.erase(s.begin());//修改：int变成long long
		for(int i=1;i<=n;i++) s.insert(t*a[i]);
	}
	return printf("%lld\n",*s.begin()),0;
}
```
WA是不WA了，但是$\color{red}\texttt{WOC}\text{为什么}\texttt{T}\text{了一个点啊}$  
笔者随便加了点优化。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[105];set<long long>s;
int main()
{
	scanf("%d%d",&n,&k),s.insert(1);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	sort(a+1,a+n+1);//排个序更快
	for(int i=1;i<=k;i++)
	{
		long long t=*s.begin();s.erase(s.begin());
		for(int i=1;i<=n;i++) if(t*a[i]<=2000000000) s.insert(t*a[i]);
		//因为题目中已经说了，保证答案不超过2000000000。
		//那么超过2000000000的肯定不需要加入set，一个优化
	}
	return printf("%lld\n",*s.begin()),0;
}
```
结果还是$\color{red}\texttt{T}$  

于是笔者从整份代码来考虑，T的原因应该是在set中加入太多超过第K大的数了吧。  
那么我们可以记录当前set的最大值。  
如果的接下来构造的这个数已经大于最大值且set中有k个数了。  
我们就可以break结束了。  
然后加了这个优化之后，笔者顺利AC了这道题QAQ。  

### Coding.  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,f=1,a[105];long long mx,INF=2000000000;set<long long>s;
//f表示当前set中是否有k个数
int main()
{
	scanf("%d%d",&n,&k),s.insert(1);
	for(int i=1;i<=n;i++) scanf("%d",a+i),a[i]==1?(i--,n--):0;
	sort(a+1,a+n+1),mx=1;//最大值变成当前唯一的一个1
	for(int i=1;i<=k;i++)
	{
		long long t=*s.begin();s.erase(s.begin());
		for(int i=1;i<=n&&t*a[i]<=INF;i++) if(f||a[i]*t<=mx) s.insert(t*a[i]),mx=max(mx,t*a[i]);
		//首先，刚刚加的优化仍然有（在循环条件中）
		//然后，这个判断条件就是刚刚说的那个break的反条件QAQ
		f=((int)s.size()+i<=k);
		//更新f，检查加入后是否set中有k个数
	}
	return printf("%lld\n",*s.begin()),0;
}
```

### Ending.
写题解辛苦，管理大大求过，无耻求赞

---

## 作者：Rush_Hht (赞：12)

      2019年1月17日第一次参加本校组织的比赛。这道题是唯一写了的题，但只有90分，当时是暴力破解，后来学会正解，特此记录，也希望能帮助到大家。
  
      以下为当时比赛时的暴力代码
  ```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int sum[100];
int num[100];
long long anssum[10000000];
const long long top=2000000000;
int now=1;int n;
void find() {
	anssum[now]=1;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= num[i];j ++){
		   anssum[now]*=sum[i];
		   if(anssum[now]>top) return;
		} 
	return;
}
void findjj(int posi){
	if(posi>n) return;
	for(int j = 0; j <= 33 ; j ++){
		find();
		if(anssum[now]>top) {
			num[posi]=0;return;
		}
		if(anssum[now]<=top&&anssum[now]!=1) now++;
		num[posi]=j;
		findjj(posi+1);
	}
}
int main() {
	int pu;
	cin >> n >> pu;
	for(int i = 1; i <= n; i++)
	   cin >> sum[i];
    findjj(1);
	sort(anssum+1,anssum+1+now);
	int a=0;
	 for(int i=1;i<=now;i++){
	 	if(anssum[i]!=anssum[i-1]) a++;
	 	if(a==pu){
	 		cout<<anssum[i]<<endl;
	 		return 0;
		 }
	 }
     
}
```
      9个AC，一个TLE。
      
      刚开始肯定想过筛去其它数的解法，但是看了一下数据范围（不会超过2000000000）20亿，还是放弃吧。
      然后又想到了组合（两个质数相乘去找符合条件的数），但是当时的方法用的是暴力的深搜，就是上面的代码，经过了优化还是TLE一个点。
      正解：优先队列。
      
      正解代码附上：
```cpp
#include <iostream>
using namespace std;
int sum[111];  //储存题目限定的质数。
int ans[111111];  //储存单调递增的序列。
int position[111];  //储存当前限定质数下一次乘的位置。
int main() {
	int n , k;
	cin >> n >> k;
	for(int i = 1; i <= n; i++)
		cin >> sum[i];
	int now = 0;
    ans[0] = 1;
	while(now < k) {
		int Min=2147483647 , Max_position;//Min用来更新符合质数的最小值；Min_position用来存符合质数的最小值是由哪个质数乘过来的。
		for(int i = 1; i <= n ; i++){     //这重复的循环有点像归并排序，这里需要仔细去理解一下的，这里懂了基本上就透了。
			if(ans[position[i]] * sum[i] < Min){
				Min = ans[position[i]] * sum[i];
				Max_position = i;
			}
		}
		position[Max_position]++;
		if(Min != ans[now])  ans[++now] = Min;//判重。
	}
	cout << ans[k] <<endl;
	return 0;
}
```

      这道题的代码量是不多的，还是思想问题。
      帮你们模拟一下好了 ，便于理解吧。
      sum pos ans
      0   0   1     0
      3   0   0     1
      5   0   0     2  初始的样子  3*1 与  5*1 比
      0   0   0     3
      0   0   0     4
      0   0   0     5
      
      
      0   0   1     0
      3   1   3     1
      5   0   0     2  循环一次得出满足条件的数 3
      0   0   0     3       
      0   0   0     4      3*3 与 5*1 比
      0   0   0     5
      
       
      0   0   1     0
      3   1   3     1
      5   1   5     2  循环两次得出满足条件的数 5
      0   0   0     3
      0   0   0     4      3*3 与 5*3 比
      0   0   0     5
      

      0   0   1     0
      3   2   3     1
      5   1   5     2  循环三次得出满足条件的数 9 
      0   0   9     3 
      0   0   0     4      3*5 与 5*3 比
      0   0   0     5
      

      0   0   1     0
      3   3   3     1
      5   1   5     2  循环四次得出满足条件的数 15
      0   0   9     3
      0   0   15    4       3*9 与 5*3 比 
      0   0   0     5
      

      0   0   1     0
      3   3   3     1
      5   2   5     2  循环五次得出满足条件的数 15 重复 不保存
      0   0   9     3
      0   0   15    4        3*9 与 5*5 比
      0   0   0     5
      

      0   0   1     0
      3   3   3     1
      5   3   5     2  循环六次得出满足条件的数 25 
      0   0   9     3
      0   0   15    4        3*9 与 5*9 比
      0   0   25    5


      0   0   1     0
      3   4   3     1
      5   3   5     2  循环七次得出满足条件的数 27
      0   0   9     3
      0   0   15    4        3*15 与 5*9 比
      0   0   25    5
      0   0   27    6

      0   0   1     0
      3   5   3     1
      5   3   5     2
      0   0   9     3  循环八次得出满足条件的数45
      0   0   15    4
      0   0   25    5       stop！
      0   0   27    6
      0   0   45    7
      
      
      45
      
      速度还是非常快的
      结束了。
      
      
      总结：优先队列的思想。


   


 

---

## 作者：李尧 (赞：6)

~~题目很简单~~

有一种东西叫STL（手动滑稽）

前一篇代码写的很好，但是我比较懒。。。

set走起来~

~~差点忘了还有介绍思想这个环节。。~~

只包含这n个质因数的数是什么数呢？？？

of course，埃式筛法知道不？原理是一样一样的。只是倍数是数组内的数而已。

以下放代码。

```
#include <bits/stdc++.h>
using namespace std;
int n,k;
int a[107],ans=1,mx;
bool flag;
set <int> s;//STL
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) {
        scanf("%d",&a[i]);	
        s.insert(a[i]);mx=max(mx,a[i]);
    }
    sort(a+1,a+1+n);
    while(ans<k){
    	int p=*s.begin();//找到第一个元素
    	s.erase(p);//删除该数
        for(int i=1;i<=n&&a[i]<=2147483647/p;i++){
        	if(flag&&a[i]*p>mx) break;
            s.insert(a[i]*p);mx=max(mx,a[i]*p);  
        }//在数组内找数更新
        if(s.size()+ans>k) flag=true;//优化，防止超时，如果set内的数数目达到k且后面大于最大数的就不用了
        ans++;
    }
    printf("%d",*s.begin());//输出
    return 0;
}
```
注：不用set会有重复！！！
祝大家AC

---

## 作者：麦克斯韦の妖 (赞：4)

一篇用 ``priority_queue`` AC 的题解。


------------
思路：先把 $p_{i}$ 全部扔到优先队列（小顶堆）里，每次取出队首。先判断有没有重复，如重复了就直接弹出队列，否则把 $top \times p_{i}$ 扔到优先队列里。

**这样做只有 90 pts，所以我们充分发扬人类智慧。**

**优化**：第一个点超了 0.1 s，非常离谱。
我们发现，当 $n$ 较大时，有些 $p_{i}$ 也较大，在队内已有较多元素时，$top \times p_{i}$ 只有在 $p_{i}$ 较小时才有可能在前 $k$ 个。于是，我们在已经弹出一半（确定了前 $\dfrac{k}{2}$ ）以后只取前 $5$ 个 $p_{i}$（ $p{i}$ 从小到大排序，$n$ 较大）。


代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<string.h>
#include<cmath>
#include<queue>
#include<algorithm>
#include<deque>
#include<vector> 
using namespace std;
typedef long long ll;
priority_queue<ll,vector<ll>,greater<ll> > q;
int n,k;
int p[101];
int tot;
vector<ll> ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
		q.push(p[i]);
	}
	sort(p+1,p+1+n);
	ans.push_back(0);
	while(tot<=k)
	{
		ll now=q.top();
		if(now!=ans[tot])
		{
			tot++;
			ans.push_back(now);	
			int t=n;
			if(tot>k/2)
			{
			    t=min(n,5);
			}	
			for(int i=1;i<=t;i++)
			{
				q.push(now*p[i]);
			}
		}
		q.pop();
	}
	printf("%lld\n",ans[k]);
}
```

PS：格式错误已修改，望通过。

---

## 作者：lytqwq (赞：2)

~~OTZ 你们都是会O（N*K）的神仙~~

很明显我们可以开一个小根堆来存每个 包含要求的质因数的数 ，然后每次取最小的数来更新出后面的一些数，来加入小根堆，然后，第k小的数就是第k次从堆里出来的数。

然后你会发现你过不了样例，原因就是会有重复的元素进队，比如样例中的15 ，可以从3更新上来，也可以从5更新上来，所以你可以判重（代码中我用了更懒的方法

然后根据ans不会超过2000000000的条件 优化一下，~~开上O2~~就可以AC了

复杂度貌似是 $ O(K*N log(K *N)) $ 但是加上优化跑的不算太慢（

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 101
#define K 100001
int n,k,a[N];
priority_queue<int,vector<int>,greater<int> > Q;
int sum,ans;
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		Q.push(a[i]);
	}
	int last=0;
	while(!Q.empty())
	{
		int now=Q.top();
		Q.pop();
		if(now==last)
		{
			continue;
		}
		last=now;
		sum++;
		if(sum==k)
		{
			ans=now;
			break;
		}
		for(int i=1;i<=n;i++)
		{
			if(1LL*now*a[i]>2000000000)
			{
				continue;
			}
			Q.push(now*a[i]);
		}
	}
	printf("%d\n",ans);
}
```


---

## 作者：ztntonny (赞：1)

## 解法
本解法异常玄乎，但是程序跑得异常的快，我都感到很惊诧：

![输入图片说明](https://cdn.luogu.com.cn/upload/image_hosting/10ypa8ka.png)

离天大谱。先给出程序：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n , a[105] , k , l , r;
int cmp , cnt , ans[10000005];
void fnd()
{
	for ( int i = 1; i <= n; i++ )
		for ( int j = 1; j <= cnt && cnt <= 1e7; j++ )
		{
			l = a[i] * ans[j];
			l <= r ? ans[++cnt] = l : 1;
		}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL) , cout.tie(NULL);
	cin >> n >> k;
	if ( n >= 90 )	r = 5e5;
	else	r = 2e9;
	for ( int i = 1; i <= n; i++ )	cin >> a[i];
	ans[1] = 1;
	cnt = 1;
	fnd();
	sort( ans + 1 , ans + cnt + 1 );
	cout << ans[k + 1] << endl;
	return 0;
}
```
我的解法是类似于这么一个框架：

```cpp
for ( int i = 1; i <= n; i++ )
	for ( int j = 1; j <= cnt; j++ )
		if ( a[i] * ans[j] <= 2e9 )
			ans[++cnt] = a[i] * ans[j];
```

本质其实是递推，但是很隐晦。对于每一个给出的素数，都会将它乘上数组里原有的所有数，并且结果会同时塞进数组里，如果这个值没有超过我们要的极值也就是 $2e9$。为什么这么做可以？因为在把一些结果塞进去后，这些结果还会在同级被同一个素数再乘一遍、再乘一遍，直到 $2e9$。而这些结果同样会被以后的素数乘上多遍，所以我们实际上枚举了所有的情况（我都说了很玄学）。

然后我们开心的交上去这个代码，发现一个有趣的事情：

![输入图片说明](https://cdn.luogu.com.cn/upload/image_hosting/a1b03pew.png)

很显然为什么错了：数太多了内存炸了，数太多是因为质数太多。

那么如何解决？最玄学的来了，不难发现一个及其有利的事实：当质数越多的时候，数的分布就越密集，也就是说结果的最大值就会越小，我们需要存下来的数也就越少，于是内存就不会爆炸，那么加一个小小的特判：

```
if ( n >= 90 )	r = 1e7;
else	r = 2e9;
```

这个理论范围这么推导：首先意识到素数越大分布越稀疏，且数目越小分布越稀疏，在 $90$ 以下本程序还可以处理，于是在 $n=90$ 处分析：最大要求第 $1e5$ 个，那么我们推导一下，假设所有质数都取到最大值 $1e3$，那么分布会是：在 $1e3^1$ 层有 $90$ 个，在 $1e3^2$ 层有 $90^2$ 个，在 $1e3^n$ 层有 $90^n$ 个，于是最大值 $1e3^{\log_{90}^{1e5}}\approx1e3^{2.56}\approx47,863,009$，但是估计会差一些，取到 $1e7$ 刚好（其实好像最后证明 $5e5$ 对于本题数据就够用了呢）。

于是程序写就，上方已给，感谢您阅读如此一片玄学的题解。

---

## 作者：wenxutong (赞：1)

粗粗一看，我便只会用暴力做。

先把每个题中所给的质数放进一个小根堆里，

每次取一个出来，暴力乘上所有题中所给的质数，再将他们放到堆里。

由于是暴力，几个质数相乘无法避免的会重复，于是在每次“取出”操作时要判断下一个是否是相同的，在代码中用 while 判断实现。

这样，只要取出到第 $ k $ 个，就可以输出答案了。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
#define ll long long
#define upp 2000000000
int n,K;
ll a[105];
ll q[10000005],cnt=0;
void up(int now){
    if(now==1)return;
    int fa=now/2;
    if(q[now]<q[fa]){
        swap(q[now],q[fa]);
        up(fa);
    }
}
void down(int now){
    int son=now*2;
    if(son<=cnt){
        if(son+1<=cnt&&q[son+1]<q[son])son++;
        if(q[now]>q[son]){
            swap(q[now],q[son]);
            down(son);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>K;cnt=n;
    for(int i=1;i<=n;i++){cin>>a[i];}
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){q[i]=a[i];up(i);}
    for(int i=1;i<K;i++){
        for(int j=1;j<=n;j++){
            ll sum=q[1]*a[j];
            cnt++;
            q[cnt]=sum;
            up(cnt);
        }
        q[1]=q[cnt];
        cnt--;
        down(1);
        while(q[1]==min(q[2],q[3])){
            q[1]=q[cnt];
            cnt--;
            down(1);
        }
    }
    cout<<q[1]<<"\n";
    return 0;
}
```

很显然，这样是过不了的。

但注意到题中所说 $ 1\leq ans\leq 2\times 10^{9} $

所以，只要在 $ 2\times 10^{9}\leq $ 乘积 $sum$ 时，break 既可。

完整代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
#define ll long long
#define upp 2000000000
int n,K;
ll a[105];
ll q[10000005],cnt=0;
void up(int now){
    if(now==1)return;
    int fa=now/2;
    if(q[now]<q[fa]){
        swap(q[now],q[fa]);
        up(fa);
    }
}
void down(int now){
    int son=now*2;
    if(son<=cnt){
        if(son+1<=cnt&&q[son+1]<q[son])son++;
        if(q[now]>q[son]){
            swap(q[now],q[son]);
            down(son);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>K;cnt=n;
    for(int i=1;i<=n;i++){cin>>a[i];}
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){q[i]=a[i];up(i);}
    for(int i=1;i<K;i++){
        for(int j=1;j<=n;j++){
            ll sum=q[1]*a[j];
            if(sum>upp)break;
            cnt++;
            q[cnt]=sum;
            up(cnt);
        }
        q[1]=q[cnt];
        cnt--;
        down(1);
        while(q[1]==min(q[2],q[3])){
            q[1]=q[cnt];
            cnt--;
            down(1);
        }
    }
    cout<<q[1]<<"\n";
    return 0;
}
```



---

## 作者：ncwzdlsd (赞：0)

优先队列。

用优先队列维护 $k$ 小值。把序列 $p$ 压入优先队列，每次将队首元素与序列 $p$ 中的每一个元素相乘再压入队列，这样可以保证每一个队列中的数只会包含序列 $p$ 中的质因数。这里需要注意判重，如果该数在队列中出现过就跳过。

时间复杂度 $O(nk\log{(nk)})$。

要开 O2。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=105;
int p[maxn];
priority_queue<int,vector<int>,greater<int> > q;

int main()
{
    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>p[i],q.push(p[i]);
    int lst=0,cnt=0;
    while(!q.empty())
    {
        int ans=q.top();q.pop();
        if(lst==ans) continue;
        lst=ans,cnt++;
        if(cnt==k) cout<<ans,exit(0);
        for(int i=1;i<=n;i++) if(1ll*ans*p[i]<=2e9) q.push(ans*p[i]);
    }
    return 0;
}
```

---

## 作者：nvqlfi214 (赞：0)

看到这一题的想法是：跟[Blah数集](http://ybt.ssoier.cn:8088/problem_show.php?pid=1333)好像

然后空间复杂度 $O(nk)$，时间复杂度 $O(nk)$ 勉强能过。

于是我选择开 $n$ 个队列。

每个队列 $q_i$ 先存入 $p_i$，之后跑 $k$ 次寻找所有队列中最小的数，然后把这个数弹出，乘上 $p_i$ 后压入 $q_i$ 中。

当然可能有重复的数字，但是由于我们是从小到大选择的，所以判断和上一个是否相等就可以了。~~不过这样貌似并不能达到 $O(nk)$，但耗费的时间应该不会太多~~

然后，就过了。。。（开 O2 跑了 112ms，还挺快）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2 + 10;
int n, k, p[N];
queue<int> q[N];  //开 n 个队列
int read() {
    char ch = getchar();
    int x = 0;
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}
const int INF = INT_MAX;
int main() {
    n = read(), k = read();
    for (int i = 1; i <= n; i++) q[i].push(p[i] = read());
    int pre = 0;
    for (int i = 1; i <= k; i++) {
        int minx = INF, minid = 0;
        for (int j = 1; j <= n; j++)
            if (q[j].front() < minx)
                minx = q[j].front(), minid = j;  //寻找所有队列中最小的数
        q[minid].pop();
        if (minx == pre) {
            i--;
            continue;
        }  //不能重复
        pre = minx;
        if (i == k) {
            cout << minx;
            return 0;
        }
        for (int j = 1; j <= n; j++) q[j].push(minx * p[j]);
    }
    return 0;
}
```

---

## 作者：happybob (赞：0)

考虑优先队列广搜，第 $k$ 次出队的即为答案。注意需要去重。复杂度 $O(nk \log (nk))$，开 O2 可过，注意不要使用 `long long`，会 MLE。

```cpp
#include <iostream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 105;

#define ll int

priority_queue<ll, vector<ll>, greater<ll> > q;
int n, k;
int a[N];

ll bfs()
{
	int cnt = 0;
	ll last = 0;
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) q.push(a[i]);
	while (q.size())
	{
		ll p = q.top();
		q.pop();
		if (last == p) continue;
		last = p;
		if (++cnt == k) return p;
		for (int i = 1; i <= n; i++)
		{
			if (1ll * p * a[i] > (long long)2e9) break;
			q.push(p * a[i]);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> k;
	//k++;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cout << bfs() << "\n";
	return 0;
}
```


---

## 作者：ZhanPJ (赞：0)

[题目传送门:P2527](https://www.luogu.com.cn/problem/P2527)

---

题意简化：

已知有 $n$ 个质数 $a_i$，求第 $k$ 个包含了这些质因子的数。

---

算法：

这个蒟蒻看了各位大佬的 $O(nk)$ 算法，表示不懂，于是现在这个使用了优先队列，也就是 $O(k \times n \times \log(n \times k))$，所以开个氧气也能过。

---

思路：

笔者第一次做，发现题目中明确指出了 $ans \leq 2 \times 10^9$，所以想起来了要开 ```long long```，刚好学习了优先队列。而优先队列有一个特性——可以排序，然后……写出了这个代码。


```cpp
ll number[20005];
int bfs(int a[]){
	int cnt=n,id=0,nbs=n;
	for(int i=1;i<=n;i++)q.push(a[i]);
	while(!q.empty()){
		id++;
		int top=q.top();
		q.pop();
		if(id==k)return top;
		if(cnt>k)continue;
		for(int i=1;i<=n;i++){
			bool flag=1;int t=a[i]*top;
			for(int i=1;i<=nbs;i++){
				if(number[i]==t){flag=0;break;}
			}
			if(flag)q.push(t);
		}
	}
}
```

很恭喜，成功地只 AC 了一个点，还 TLE 了一个点。

现在我们可以发现，判重实际上很浪费时间，所以现在我们记录上一次的数字（因为一个大的数字不可能凑出来一个小的数字），节约时间。

再一次观察发现，函数内的 int 和优先队列使用的 long long 不为同一个类型，所以需要将 int 修改为 long long。

于是有了现在这个代码。

```cpp
int bfs(int a[]){
	int id=0;
	ll last=-1,top,t;
	for(int i=1;i<=n;i++)q.push(a[i]);
	while(!q.empty()){
		top=q.top();
		q.pop();
		if(top==last)continue;
		id++;
		if(id==k)return top;
		last=top;
		for(int i=1;i<=n;i++){
			t=a[i]*top;
			if(t>P)continue;
			q.push(t);
		}
	}
}
```

很恭喜，还是 TLE 了一个点。

到了这里，笔者想起来开 O2 优化，开了优化后，是 MLE，爆空间了。

所以……你还记得我们说的那个 $ans \le 2 \times 10^9$ 吗？

笔者此时想了一下：既然 $ans \leq 2 \times 10^9$（```int``` 的最大值近似为 $2.147 \times 10^9$），那么答案就在 ```int``` 类型的区间里。

所以，我们把改成 ```int``` 类型的队列。

很恭喜，开 O2 优化，过了。

---

停一下，我们整理一下思路：

1. 结果需要开 ```long long```，因为两个大于等于 $2^{15.5}$ 的数字相乘，是会超过 ```int``` 的最大值的，但是队列只用开 ```int```，因为答案不超过 ```int``` 的最大范围。
2. 不需要记录结果数字有没有重复（因为两个大于一的数字相乘一定越乘越大），但是需要记录这个数字有没有用过。
3. 需要 O2 优化。~~可能是 STL 的常数比较大。~~

---

ACcode:
```cpp
//头文件略
#define ll long long
int n,k;
priority_queue< int , vector<int> , greater<int> > q;
const int P=2000000000;//方便之后书写
ll bfs(int a[]){
	int id=0;
	sort(a+1,a+n+1);//这里可以方便后面的if(t>P)可以直接break，方便我们节约时间复杂度。
	for(int i=1;i<=n;i++)q.push(a[i]);//入队
	ll last=-1,top,t;//last代表上一次的数字
	while(!q.empty()){
		top=q.top();
		q.pop();
		if(top==last)continue;//跳过循环
		id++;last=top;//id统计有多少个有效数字了
		if(id==k)return top;//当前是正确的数字，那么返回队列的顶端
		for(int i=1;i<=n;i++){
			t=a[i]*top;
			if(t>P)break;//特判
			q.push(t);//入队
		}
	}
}
int main(){
	//读入略
	printf("%d",bfs(input));
	
	return 0;
}
```

---

附：[提交记录](https://www.luogu.com.cn/record/65173898)

---

## 作者：Ceritor_Hanio (赞：0)

是一道非常有趣数学推论题，用一种很奇怪的方法解决了我很长一段时间内的困惑。

**题意，给你 $n$ 个质数，求出只含有这些质因数的数中第 $k$ 小的数。**

本来的想法是利用欧拉筛的做法，构建一个数组存已经得到的数，然后枚举质数推出后面的数。这样利用唯一分解定理，每个数只算出来一遍，可以优化时间复杂度。但是！由于欧拉筛的筛法并不是从小到大筛的，可能会先筛大数再筛小数，导致我们也可能会先算出大数再算出小数。当 $k$ 非常大时，我们就可能要多算很多个多余的数才能得到答案。因此时间复杂度变大了。

然后题解的做法是，同样构建一个答案表，然后记录每个质数目前所要乘的答案表中的数，每次用 $n$ 的时间复杂度枚举质数算出一个最小的，把他加入答案表中，总时间 $ O(nk)$

```
while(o<k){//a为答案表，p为质数表
  ll Max=2*1e10,m;
	for(ll i=1;i<=n;i++){
	   if(a[q[i]]*p[i]<Max){
		Max=a[q[i]]*p[i];
		m=i;
		}//首先保证每次求出来的最小
	}
	q[m]++;
	if(Max!=a[o])	a[++o]=Max;
    //然后因为a是递增的,
    //所以不可能通过质数先算出一个大数,再算出一个小数,
    //这样我们只要保证不连续出现重复,就可以去重了。
    //毕竟表中不可能先加入大数，再加入小数
}
```


---

