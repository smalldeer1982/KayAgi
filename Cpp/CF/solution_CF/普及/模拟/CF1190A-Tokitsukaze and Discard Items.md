# Tokitsukaze and Discard Items

## 题目描述

Recently, Tokitsukaze found an interesting game. Tokitsukaze had $ n $ items at the beginning of this game. However, she thought there were too many items, so now she wants to discard $ m $ ( $ 1 \le m \le n $ ) special items of them.

These $ n $ items are marked with indices from $ 1 $ to $ n $ . In the beginning, the item with index $ i $ is placed on the $ i $ -th position. Items are divided into several pages orderly, such that each page contains exactly $ k $ positions and the last positions on the last page may be left empty.

Tokitsukaze would do the following operation: focus on the first special page that contains at least one special item, and at one time, Tokitsukaze would discard all special items on this page. After an item is discarded or moved, its old position would be empty, and then the item below it, if exists, would move up to this empty position. The movement may bring many items forward and even into previous pages, so Tokitsukaze would keep waiting until all the items stop moving, and then do the operation (i.e. check the special page and discard the special items) repeatedly until there is no item need to be discarded.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1190A/a059bb92f5a4888ea9bb5a2b1a83486b43dcecf3.png)Consider the first example from the statement: $ n=10 $ , $ m=4 $ , $ k=5 $ , $ p=[3, 5, 7, 10] $ . The are two pages. Initially, the first page is special (since it is the first page containing a special item). So Tokitsukaze discards the special items with indices $ 3 $ and $ 5 $ . After, the first page remains to be special. It contains $ [1, 2, 4, 6, 7] $ , Tokitsukaze discards the special item with index $ 7 $ . After, the second page is special (since it is the first page containing a special item). It contains $ [9, 10] $ , Tokitsukaze discards the special item with index $ 10 $ .Tokitsukaze wants to know the number of operations she would do in total.

## 说明/提示

For the first example:

- In the first operation, Tokitsukaze would focus on the first page $ [1, 2, 3, 4, 5] $ and discard items with indices $ 3 $ and $ 5 $ ;
- In the second operation, Tokitsukaze would focus on the first page $ [1, 2, 4, 6, 7] $ and discard item with index $ 7 $ ;
- In the third operation, Tokitsukaze would focus on the second page $ [9, 10] $ and discard item with index $ 10 $ .

For the second example, Tokitsukaze would focus on the second page $ [6, 7, 8, 9, 10] $ and discard all special items at once.

## 样例 #1

### 输入

```
10 4 5
3 5 7 10
```

### 输出

```
3
```

## 样例 #2

### 输入

```
13 4 5
7 8 9 10
```

### 输出

```
1
```

# 题解

## 作者：Eismcs (赞：5)

并不是很难，作为div1的T1，这题只是模拟加一点数论而已

主要是删掉特殊数后，每个数都会前移，需要注意
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
#define int unsigned long long
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int n,m,k,a[100005];
signed main(){
    n=read();m=read();k=read();
    for(int i=1;i<=m;i++)a[i]=read();
    if(k==1){cout<<m<<endl;return 0;}
    sort(a+1,a+m+1);//排序，按顺序删除
    int l=0,j,s=0;
    for(int i=1;i<=m;i++){
        j=i+1;
        while((a[i]-l)/k-(!((a[i]-l)%k))==(a[j]-l)/k-(!((a[j]-l)%k))&&j<=m)j++;
        //寻找与当前在同一组的数，一起删
        //稍微加了一点处理，因为若a[i]是k的倍数,组号为a[i]/k-1
        l+=(j-i);i=j-1;s++;//s是删得次数，也就是答案
        //l是删到j，每个数向前一点个数，l也就是下一轮的i
        if(j>m)break;
    }
    cout<<s<<endl;
    return 0;
}
```
这道题难度不是很大，但还是有些细节要注意

---

## 作者：hsfzLZH1 (赞：4)

## 题目大意

给定从小到大排列的 $1,2,...n$ 这 $n$ 个数。要删除其中的 $m$ 个数 $p_1,p_2,...,p_m$ 。删除的方法如下：

将这 $n$ 个数分成若干块，每块的大小为 $k$ ，最后一段的大小可以小于 $k$ 。从左到右给每段编号（从 $1$ 开始）。

每次删除操作，找到编号最小的有要删除的数的块，删除这块中的 **所有** 要删除的数。然后将剩下的所有数再次分成若干块（即填上删除的数的空位），每块的大小为 $k$ ，重复以上过程，直到所有待删除的数都被删除为止。

问删除操作的次数。

$1\le m,k\le n\le 10^{18},1\le m\le 10^5$

$1\le p_1<p_2<...<p_m\le n$

## 解题思路

观察到 $n$ 的范围很大，而 $m$ 的范围较小，且每次至少会删除一个数，所以总的删除操作次数不会超过 $m$ ，我们可以考虑用总时间复杂度为 $O(m)$ 去模拟每次操作。

首先我们观察一下分成若干块的性质。每块的大小为 $k$ 。第一次分块后，数 $x$ 所在的块为 $\lceil \frac x k \rceil=\lfloor \frac {x+k-1} k \rfloor$ 。

观察到我们在删除一个数前，小于等于一个值 $v$ 的数都已经被删除了，其余比它小的数都和它在同一块里，同时删除。根据 $v$ 在 $p$ 数组中的位置，我们可以知道在这次删除操作之前已经被删除的数的个数，记为 $lst$ 。根据这个值，我们可以求得删除后一个数 $x$ 所在的块为 $\lfloor \frac {x-lst+k-1} k \rfloor$ 。

我们每次找到没有删除的最小的数，按照上述的方法求出最小的有要删除结点的编号，然后删除和该数所在块相同的所有数。这些数在 $p$ 数组上都是连续的。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn=100010;
ll n,m,k,p[maxn],cur,lst,nww,ans;
int main()
{
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=m;i++)scanf("%lld",p+i);
    cur=1;
    while(cur<=m)
    {
    	lst=cur-1;
    	nww=(p[cur]-lst+k-1)/k;
    	for(;((p[cur]-lst+k-1)/k)==nww;cur++);
    	ans++;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：xu222ux (赞：3)

~~这是一道比较水的题。~~

# 思路

### 如何知道本点为第几组？

我假设前面一共删掉了 $cnt$ 个点，把删掉的点扣除总数，再用这个公式算：

$$ans = \left\lceil(a_i-cnt)/k\right\rceil$$

### 咋算？？

从一扫到 $m$ ，如果发现 $a_i$ 这个数的组数与前面的不同，就结算前面的。


# code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k;
long long a[100005];
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)cin>>a[i];//输入
    long long ans=0,cnt=0,q=(a[1]+k-1)/k;
    //分别表示答案，个数，前一个所属小组
    for(int i=2;i<=m;i++){
        if((a[i]-cnt+k-1)/k!=q){//判断是否换组了
            //换了
            ans++,cnt=i-1;//答案加一，个数刚更新
	    	q=(a[i]-cnt+k-1)/k;
        }
    }
    if(cnt!=m)ans++;//结尾特判 
    cout<<ans;
    return 0;
}
```


---

## 作者：Alex_Wei (赞：2)

这题的 $n$ 给的其实没什么用，$10^{18}$ 就是用来~~吓唬人的~~让你开 $long\ long$ 的

因为这题给我们的 $p_i$ 保证有序，所以我们就不用排序了，直接模拟

首先，我们把每个读进来的 $p_i$ 减 $1$，方便模拟

根据删除规则，**如果 $p_{i-1}$ 没有被删除，则 $p_i$ 一定不会被删除**

所以我们设一个变量 $poi$，表示当前即将删除的下标 （下标从 $0$ 开始，方便模拟），再设一个变量 $del$，表示已经删除了多少个数

接下来一直循环到 $poi$ 超出数组范围：

1. 每次循环都是一次删除，$ans++$

2. 把当前要删的数减去已经删掉的数，**得到现在 $p_{poi}$ 真正的位置**

3. 再来一个 $while$ 循环：

$poi+1$，如果当前的 $p_{poi}$ 与 $p_{poi-1}$ 在同一页面上，即 $(p_{poi}-del)/k=p_{poi-1}/k$

那么就把 $p_{poi}$ 减去 $del$，否则退出循环

4. $del=poi$（因为下标从 $0$ 开始，**所以当前 $poi$ 的值就等于删除了多少个数**）

最后输出 $ans$ 即可

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,m,k,poi,s,p[100005],del; 
int main()
{
	cin>>n>>m>>k;
	for(int i=0;i<m;i++)cin>>p[i],p[i]--;
	while(poi<m){
		s++;p[poi]-=del;
		while((++poi)<m&&(p[poi]-del)/k==p[poi-1]/k)p[poi]-=del;//核心
		del=poi;
	}
	cout<<s;
	return 0;
}
```


---

## 作者：王熙文 (赞：2)

#### 简单的题解：

这道题就是一道简单的模拟题。

考虑每一次操作会将后面的数向左移这次删除的数次，所以所有数都要减同样的数，不如定义一个 $\text{tag}$ 数表示要向左移几个数。

那么我们先求出当前数所在的块，然后在数组里二分到当前块最后需要取的数，然后拿走这些块里所有的数，$\text{tag}$ 加上这些数个数，当前数变成当前块最后需要取的数的下一个数。每一次答案都加一。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int a[100010];

signed main()
{
    int n,m,k;
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1; i<=m; ++i) scanf("%lld",&a[i]);
    int now=1,ans=0,tag=0;
    while(now<=m)
    {
        int block=(a[now]-tag-1)/k+1,last=block*k;
        int wz=upper_bound(a+1,a+m+1,last+tag)-a-1; // 后面所有数都减了 tag，就让二分的数加上 tag
        tag+=wz-now+1;
        now=wz+1;
        ++ans;
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Abeeel51 (赞：0)

这题的时间复杂度一定是  $O(m)$，如果是 $O(n)$ 一定超时。

题目中给定是升序的 $p$ 数组，所以直接记录每一个 $p_i$ 就好，删 $m$ 次。

说了这么多，到底应该怎么膜你？

他所在的块的位置就是 $a_i-delpos_i+(k-1)$ 位，其中 $a_i$ 表示第 $i$ 个数，$delpos_i$ 表示第 $i$ 位前删除的数量。

算出块，就可以算出最终结果了。

代码来了！！！

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,k;
ll a[100005];
int main(int argc, const char * argv[]) {
    // insert code here...
    scanf("%lld%lld%lld",&n,&m,&k);
    for(ll i=1;i<=m;i++) scanf("%lld",&a[i]);
    ll undeleteplace=1;//清晰明了
    ll Countdeleteplace=0;//清晰明了
    while(undeleteplace<=m){
        ll deleteplace=undeleteplace-1;//清晰明了
        ll nowneedplace=(a[undeleteplace]-deleteplace+k-1)/k;//清晰明了
        while(((a[undeleteplace]-deleteplace+k-1)/k)==nowneedplace){
            undeleteplace++;
        }
        Countdeleteplace++;//清晰明了
    }
    printf("%lld\n",Countdeleteplace);//清晰明了
    return 0;
}
```


---

## 作者：FLAMEs_ (赞：0)

本题是一道时间复杂度为 $\Theta(m)$ 左右的模拟。

首先，读入所有需要删除的数，由于题目中已经给出是**升序** $(1\le p_1 <p_2<p_3<\dots <p_{m-1}<p_m\le n)$，故我们可以不必排序，直接用一个 $pos$ 
记录当前扫到的位置即可。

对于每一次题目中所说的**操作**，我们考虑用模拟去实现。

以下是 $n=12,m=4,k=7,p_1=4,p_2=7,p_3=9,p_4=12$ 时的情况。

（注：右上角标有 $@$ 的数表示一组的开始。）

| $1^@$ | $2$ | $3$ | $4$ | $5$ | $6$ | $7$ | $8^{@}$ | $9$ | $10$ | $11$ | $12$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |

当进行第一次操作时，很显然，我们需要取出 $4$ 和 $7$。

在取走之后，数列变成了下面的这个样子：

| $1^@$ | $2$ | $3$ | $5$ | $6$ | $8$ | $9^{@}$ | $10$ | $11$ | $12$ |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |

再进行一次操作，取出 $9$ 和 $12$。

数列变成以下形式：

| $1^@$ | $2$ | $3$ | $5$ | $6$ | $8$ | $10^{@}$ | $11$ | 
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |

至此，操作结束。

为了解决数组在删除数据后的**后移**问题，我们可能会想到暴力，但数据范围 $(1\le n\le 10^{18},1\le m \le 10^{5},1\le m,k\le n)$ 令我们彻底死心。

此时，我们需要考虑优化。

令 $f(x)=\left \lfloor \frac{x+k-1}{k}\right \rfloor$，即求出他们在第几组。固然，同一组的 $f(x)$ 值一定相等。由此，我们联系到先前的升序，可以得出：

每一次操作时先求得当前数 $a_{pos}$ 的组别号码，然后一直增加 $pos$ 的值直到已经查询到的数的组别号码不等于本次操作的组别号码，操作结束，答案增加。

再次进行观察，我们可以发现：

已经扫过的数字数量 $used$ 等于当前的位置 $pos-1$！

至此，所有需要解决的问题解决，我们可以开始码代码了。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//别忘了开long long！
int n,m,k,a[100005],pos=1,ans,used;
signed main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)scanf("%lld",&a[i]);
	while(pos<=m)
	{
		used=pos-1;
		int temp=(a[pos]-used+k-1)/k;
		for(;(a[pos]-used+k-1)/k==temp;pos++);
		ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xukuan (赞：0)

这题的难度有点小高，不过不算恶评

首先时间复杂度肯定不会和n挂钩，不然会TLE到飞起

同时每次至少删一个数，所以最多删m次,时间复杂度应该是O(m)

对于每一个数字x，开始时他在块[(x+k-1)/k]里面，当前面有t个数字被删除时，他就在[(x+k1-1t)/k]这个块里面

这点算出来后，直接模拟即可

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,m,k,l,ans,a[100010];

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline ll kind(ll x){
	return x/k-(!(x%k));
}

int main(){
	n=read(); m=read(); k=read();
	for(ll i=1; i<=m; i++) a[i]=read();
	for(ll i=1; i<=m; i++){
		ll j=i+1;
		while(kind(a[i]-l)==kind(a[j]-l)&&j<=m) j++;
		l+=j-i; i=j-1; ans++;
		if(j>m) break;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

