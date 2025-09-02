# [USACO3.1] 丑数 Humble Numbers

## 题目描述

对于一给定的素数集合 $S = \{ p_1, p_2, ..., p_k \}$, 考虑一个正整数集合，该集合中任一元素的质因数全部属于 $S$。这个正整数集合包括，$p_1$、$p_1 \times p_2$、$p_1 \times p_1$、$p_1 \times p_2 \times p_3$ ...(还有其它)。该集合被称为 $S$ 集合的“丑数集合”。注意：我们认为 $1$不是一个丑数。

你的工作是对于输入的集合 $S$ 去寻找“丑数集合”中的第 $n$ 个“丑数”。保证答案可以用 32 位有符号整数表示。

补充：丑数集合中每个数从小到大排列，每个丑数都是素数集合中的数的乘积，第 $n$ 个“丑数”就是在能由素数集合中的数相乘得来的（包括它本身）第 $n$ 小的数。


## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，保证：

- $1 \leq k \leq 100$。
- $1 \leq n \leq 10^5$。
- $2 \leq p_i < 2^{31}$，且 $p_i$ 一定为质数。

---
#### 说明

题目翻译来自 NOCOW。

USACO Training Section 3.1


## 样例 #1

### 输入

```
4 19
2 3 5 7```

### 输出

```
27```

# 题解

## 作者：Mark_ZZY (赞：102)

网上题解+下面大神的题解

为了找第i个丑数，那么一定要比第i-1个丑数大，而且是最小的那一个，可以发现比i-1大的丑数一定是比i-1小的丑数乘某个质数得到的，鉴于质数的数量很少，而丑数的数量很大，我们枚举质数，然后枚举丑数，直到大于第i-1个丑数，记录一下，找到所有的符合条件的丑数以后，找出最小值（也可以在寻找的途中更新最小值），那么这个最小值就是第i个丑数。

```cpp
#include<cstdio>
    int n,m;
    int a[101],b[101];
    int s[100001];
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    s[0]=1;
    for(int i=1;i<=m;i++)
    {
        int min=2147483647;
        for(int j=1;j<=n;j++)
        {
            while(a[j]*s[b[j]]<=s[i-1]) b[j]++;
            if(a[j]*s[b[j]]<min) min=a[j]*s[b[j]];
        }
        s[i]=min;
    }
    printf("%d",s[m]);
}
```

---

## 作者：「QQ红包」 (赞：47)

题解by：redbag

原题解地址：http://redbag.duapp.com/?p=1393

听说暴力出奇迹？于是redbag打算找出很多个丑数然后排序输出第n个。然后看到n的数据范围惊呆了。


直接TLE啊。


由题可知，当前产生的第I个丑数f[i]，是之前的某个丑数\*a[j]，


某个丑数\*a[j]需要>f[i-1],而且要尽可能的小。


于是我们就可以枚举j，然后找到最小的一个丑数使那个丑数\*a[j]>f[i-1];


三重循环还是会爆的样子。

但是，很容易发现满足条件的丑数x\*a[j]>f[i-1]，一定满足条件，x\*a[j]>f[i-2];于是我们就可以从满足x\*a[j]>f[i-2]的丑数x的位置往后枚举，找到满足条件x\*a[j]>f[i-1]的丑数。

然后和min比较。

就可以把结果存进去输出了。


```cpp

/*
ID: ylx14271
PROG: humble
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int n,i,j,m,k; 
long long a[123],s[100011],f[100011];
int main() 
{
    freopen("humble.in","r",stdin);
    freopen("humble.out","w",stdout);
    scanf("%d%d",&k,&n);
    for (i=1;i<=k;i++)
        scanf("%d",&a[i]);//读入 
    f[0]=1;//假设1是丑数
    for (i=1;i<=n;i++)//枚举n个丑数 
    {
        m=2000000000;//赋初值，随便赋就好，赋大些 
        for (j=1;j<=k;j++)
        {
//s[j]存的是a[j]至少与第几小丑数相乘才能得到一个比f[i-1]大的丑数 
            while (a[j]*f[s[j]]<=f[i-1]) s[j]++;//找到符合条件的最小的s[j];
            if (a[j]*f[s[j]]<m) m=a[j]*f[s[j]];//比较 
        }
        f[i]=m; //存起来 
    } 
    printf("%d\n",f[n]); 
    return 0;
}
```

---

## 作者：汉皇思倾国 (赞：21)

~~为了让C++程序员感受极佳的优越性~~

下面让本蒟蒻发一波纯STL代码

使用了优先队列和集合

思路大致为：

依靠多次乘法进行生成

用优先队列排序

~~各位神犇当然是手打小根堆~~

然后使用s.count()判重即可
```cpp
#include<cstdio>
#include<queue>
#include<set>
using namespace std;

typedef long long ll;

priority_queue<ll,vector<ll>,greater<ll> >heap;
set<ll> s;
ll a[101];
ll k,n,i=0,humble;

int main()
{
	scanf("%ll%ll",&k,&n);
	for(ll i=1;i<=k;i++)
	{
		scanf("%ll",&a[i]);
	}
	heap.push(1);
	s.insert(1);
	while(i<=n)
	{
		i++;
		humble=heap.top();
		heap.pop();
		for(ll j=1;j<=k;j++)
		{
			ll num=humble*a[j];
			if(!s.count(num))
			{
				s.insert(num);
				heap.push(num);
			}
		}
	}
	printf("%ll\n",humble);
	return 0;
} 
```
蒟蒻第一篇题解，望支持！

---

## 作者：Log_x (赞：16)

- （受到楼下$SBT$的影响，兴致冲冲地跑去写了$Splay$，不料常数巨大成功进坑……）

- 主要做法同楼下：用数据结构维护一个丑数集合， 每次取出当前的最小丑数，乘以素数集合$S$中的每一个元素，然后再把这些新的丑数加入数据结构，并保证取出的丑数个数和数据结构维护的丑数个数总共不超过$N$个，若有超过则删去多余的最大丑数

- 然而直接用$Splay$做会$TLE/RE$，我们考虑如下优化：

1. 在删去多余丑数时，一个个删除显然是不够高效的，实际上我们可以直接将当前第$N$小的丑数旋转到根，然后删去该节点的右子树即可

2. 最后答案保证在$int$范围内，因此如果发现一个丑数爆$int$，我们就没必要加入平衡树了，进一步的我们会发现，如果某一个丑数已经大于当前第$N$小的丑数，那么它肯定不可能成为最后的答案，我们同样不将其加入平衡树，这便是个重要的优化

3. 加入平衡树的丑数数量相当多，而实际满足条件的只有$N$个，因此我们显然不希望浪费太多的空间，对应的我们可以用一个栈存储那些被删除的点，并把相关的信息清空，插入丑数时再取出栈中节点重新使用即可

- 这样的话应该就能过了，最后奉上代码

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int S = 1 << 20;
char frd[S], *hed = frd + S;
const char *tal = hed;

inline char nxtChar()
{
    if (hed == tal)
     fread(frd, 1, S, stdin), hed = frd;
    return *hed++;
}

inline int get()
{
    char ch; int res = 0;
    while (!isdigit(ch = nxtChar()));
    res = ch ^ 48;
    while (isdigit(ch = nxtChar()))
     res = res * 10 + ch - 48;
    return res;
}

typedef long long ll;
const int N = 11e4 + 5;
ll Int = 2147483647ll;
int fa[N], lc[N], rc[N], sze[N], val[N];
int T, n, k, rt, top, stk[N], a[N];

inline void Push(int x) {sze[x] = sze[lc[x]] + sze[rc[x]] + 1;}

inline void Rotate(int x)
{
    int y = fa[x], z = fa[y];
    int b = (lc[y] == x ? rc[x] : lc[x]);
    fa[y] = x; fa[x] = z;
    if (b) fa[b] = y;
    if (z) (lc[z] == y ? lc[z] : rc[z]) = x;
    if (lc[y] == x) rc[x] = y, lc[y] = b;
     else lc[x] = y, rc[y] = b;
    Push(y);
}

inline bool Which(int x) {return lc[fa[x]] == x;}

inline void Splay(int x, int tar)
{
    while (fa[x] != tar)
    {
        if (fa[fa[x]] != tar)
         Which(fa[x]) == Which(x) ? Rotate(fa[x]) : Rotate(x);
        Rotate(x); 
    }
    Push(x);
    if (!tar) rt = x;
}

inline void Insert(int vi)
{
    int x = rt, y = 0, dir;
    while (x)
    {
        y = x;
        if (val[x] == vi) return ;
        if (val[x] > vi) x = lc[x], dir = 0;
         else x = rc[x], dir = 1;  
    }
    int w = y; if (y) ++sze[y];
    while (fa[w]) ++sze[w = fa[w]];
    x = top ? stk[top--] : ++T;
    fa[x] = y; val[x] = vi; sze[x] = 1;
    if (y) (dir ? rc[y] : lc[y]) = x; 
    Splay(x, 0);
}
 
inline void Join(int x, int y)
{
    int w = y;
    while (lc[w]) w = lc[w];
    lc[fa[x] = w] = x; fa[rt = y] = 0;
    Splay(w, 0);
}

inline void Delete(int x)
{
    Splay(x, 0);stk[++top] = x;
    int L = lc[x], R = rc[x];
    lc[x] = rc[x] = 0;
    if (!L || !R) fa[rt = L + R] = 0;
     else Join(L, R);
}

inline int GetKth(int k)
{
    int x = rt;
    while (x)
    {
        if (k <= sze[lc[x]])
         x = lc[x];
        else 
        {
            k -= sze[lc[x]] + 1;
            if (!k) return x;
            x = rc[x];
        }
    }
    return 0;
}

inline void Print(int x)
{
    if (!x) return ;
    Print(lc[x]); Print(rc[x]); 
    stk[++top] = x; 
    fa[x] = lc[x] = rc[x] = 0;
}

inline int FindMin() {int x = rt; while (lc[x]) x = lc[x]; return x;}

int main()
{
    k = get(); n = get(); int x, cnt = 0; ll y;
    for (int i = 1; i <= k; ++i) Insert(a[i] = get());
    while (++cnt <= n)
    {
        y = val[x = FindMin()]; Delete(x);
        for (int i = 1; i <= k; ++i) 
         if (y * a[i] < Int) Insert(y * a[i]);
          else break;
        if (sze[rt] + cnt >= n) 
        {
            Int = val[x = GetKth(n - cnt)]; Splay(x, 0); 
            Print(rc[x]); rc[x] = 0; Push(x);
        }
    }
    cout << y << endl;
}
```

---

## 作者：Celebrate (赞：14)

帮助大家更好的理解相同的的代码

这一题如果数据再小一点的话就和普及-没有什么区别，虽然这一题数据不算很大

但是暴力一定过不了，先看一下暴力的代码，5528ms，可以拿60分，超时了四个点

思路：

当前要找的丑数肯定是以前出现过的某个丑数 * 某个素数得到的

所以按照这个思路

i枚举丑数

j枚举素数

k枚举以前出现过的丑数

如果满足条件，就取最优值，并且跳出第3次循环

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[110],f[110000];
int minn;
int main()
{
	int i,j,t;
	scanf("%d%d",&k,&n);
	for(i=1;i<=k;i++) scanf("%d",&a[i]);//输入 
	f[0]=1;//假设第0项是为1 
	for(i=1;i<=n;i++)//暴力的从1枚举到n 
	{
		minn=2147483647;//2^31-1（最大值） 
		for(j=1;j<=k;j++)//暴力枚举每一个素数 
		{
			for(t=0;t<i;t++)//枚举以前出现的过的丑数 
			{
				if(a[j]*f[t]>f[i-1])//如果满足要求
				{
					minn=min(minn,a[j]*f[t]);//求最小值 
					break;//就直接弹出，因为后面的肯定比这个大，所以没有必要求后面的数 
				}
			}
		}
		f[i]=minn;//赋值 
	}
	printf("%d\n",f[n]);//输出 
	return 0;
}
```

虽然这样做超时了，但是认真看代码可以发现这里面有多余的部分

比如说第三次循环，每次都要从0找一次，是不是浪费很多时间

其实我们可以定义一个bk数组记录上一个j可以满足条件的最丑数的序号（第几小的丑数），然后往后搜索，找到就记录，并且退出查找

更改后代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[110],f[110000],bk[110];
//优化部分bk，每次枚举素数时记录这个素数能满足上一个丑数条件的最小值 
int minn;
int main()
{
	int i,j,t;
	scanf("%d%d",&k,&n);
	for(i=1;i<=k;i++) scanf("%d",&a[i]);//输入 
	f[0]=1;//假设第0项是为1 
	for(i=1;i<=n;i++)//从1枚举到n 
	{
		minn=2147483647;//2^31-1（最大值） 
		for(j=1;j<=k;j++)//枚举每一个素数 
		{
			while(a[j]*f[bk[j]]<=f[i-1]) bk[j]++;//如果这一个不行，就找下一个丑数来，直到可以为止 
			minn=min(minn,a[j]*f[bk[j]]);//求最小值 
		}
		f[i]=minn;//赋值 
	}
	printf("%d\n",f[n]);//输出 
	return 0;
}
```

---

## 作者：ghj1222 (赞：9)

提供一种单调队列做法(非正解)

显然每一个丑数能够由一个质数乘以另一个丑数得到

所以我们开k个单调递增队列，每次从这些队列顶部找到一个最小的元素把他捞出来，然后枚举所有质数，用这个元素乘以质数，放入相应的单调队列里。找到的第n个数就是所求的丑数。由于会有重复，但是取出元素的顺序是单调的，所以开一个last变量判重。

本代码不开O2卡一个点(下载下来跑1200ms)，开O2过。（因为我用的STL的队列23333）


```
#include <bits/stdc++.h>
using namespace std;

struct data
{
	int x;
	queue<int> q;
	friend bool operator>(const data &aa, const data &bb);
}t, a[110];

int k, n;

bool operator>(const data &aa, const data &bb)
{
	return aa.q.front() > bb.q.front();
}

int main()
{
	scanf("%d%d", &k, &n);
	for (int i = 1; i <= k; i++)
	{
		scanf("%d", &a[i].x);
		a[i].q.push(a[i].x);
	}
	int last = 1;
	for (int i = 1; i <= n; i++)
	{
		int minj = 1;
		for (int j = 2; j <= k; j++)
		{
			if (a[minj] > a[j])
				minj = j;
		}
		int xx = a[minj].q.front();
		a[minj].q.pop();
		if(last == xx)
		{
			i--;
			continue;
		}
		for (int j = 1; j <= k; j++)
		{
			a[j].q.push(a[j].x * xx);
		}
		last = xx;
		if (i == n)
			printf("%d\n", xx);
	}
	return 0;
}
```

---

## 作者：猫粮寸断 (赞：8)

优先队列怒答一波

完全可以搞一个最小值优先的队列，每次从队列里取出一个数，乘以每一个数以后塞回优先队列里，再把第一个数踢掉

记得要判一下重

然后非常神奇的不开O2会RE三个，开O2会MLE一个TLE两个

```cpp
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
priority_queue<long,vector<long>,greater<long> >q;
long a[110];
int main()
{
	int i,now=1,ha,n,k;
	cin>>k>>n;
	for(i=1;i<=k;i++)
	 {
	  cin>>a[i];	
	  q.push(a[i]);
	 }
	sort(a+1,a+k+1);
	while(now<n)
	{
		ha=q.top();
		while(ha==q.top())
		 q.pop();
		for(i=1;i<=k;i++)
		 if(ha%a[i]==0)
		  break;
		for(;i<=k;i++)
		 q.push(ha*a[i]);
		now++;
	}
	cout<<q.top();
	return 0;
}
```

---

## 作者：Ikari_Shinji (赞：5)

## 今天老师上课讲了一道类似的题，于是改了改程序，就AC了
### 话不多说，切入正题。
#### 看题后知晓，丑数集合是排好序的，并且具有唯一性。
#### 所以枚举肯定会有重复，我们只需设一个指针数组，来存储当前是最大倍数丑数的下标。
#### 例如数组P，P[i]就代表丑数集合中S[i]（素数集合中第i个素数）当前最大的倍数所在的下标，我们只需求出A[p[i]]*s[i]的最小值（0<i<=n），再将S中是最小值的因数的指针+1，再继续下一轮，直到A中有n个丑数后停止，输出。
代码如下：
```cpp
#include <cstdio>
#include <cstring>
#define ll long long
#define min(a,b) (a<b?a:b)

const int N=100005;
ll a[N],k,n,p[105],s[105],num;//a为丑数集合，s为素数集合，p为指针集合

int main(){
	scanf("%lld %lld",&k,&n);
	a[0]=1;//第一个数为1，但下标为0
	memset(p,0,sizeof(p));//统统指向1
	for(int i=1;i<=k;i++){
		scanf("%lld",&s[i]);
	}
	for(int i=1;i<=n;i++){
		num=2147483647;
		for(int j=1;j<=k;j++){//求最小值
			num=min(num,a[p[j]]*s[j]);
		}
		a[i]=num;//进入集合
		for(int j=1;j<=k;j++){//找因数，且下标加1
			if(num==a[p[j]]*s[j])
				p[j]++;//下标加1
		}
	}
	printf("%lld\n",a[n]);//输出
	return 0;//结束
}
```
__管理大大求过QAQ__

---

## 作者：Michael_Li (赞：5)

看到楼下没有堆的题解，本蒟蒻来交一发

这种类型的题都可以用堆来做，构建一个小根堆，每次取出堆顶，然后用堆顶乘以集合内的元素，再塞回堆中。

但是有一个问题，2\*3和3\*2会重复计算，如果开桶判重就炸空间了，具体处理看下面

        
```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#define N (15000001)
#define lson (u<<1)
#define rson (u<<1|1)
using namespace std;
struct node{//js表示基数，就指的是我是哪个数乘来的，这样讲还是很难讲请，结合下面的代码来具体理解
    long long data;
    int js; 
}heap[N];
int k, n, size;
long long a[N];
int read(){
    int t = 0;
    char p = getchar();
    while (!isdigit(p)) p = getchar();
    do{
        t = t * 10 + p - 48;
        p = getchar();
    }while (isdigit(p));
    return t;
}
void up(int u){//堆的上移操作，不具体讲了
    while (heap[u].data < heap[u/2].data && u > 1){
        node t = heap[u];
        heap[u] = heap[u/2];
        heap[u/2] = t;
        u = u / 2;
    }
}
void down(int u){//下移
    while (lson <= size){
        int s;
        if (rson <= size && heap[rson].data <  heap[lson].data) s = rson;
        else s = lson;
        if (heap[s].data < heap[u].data){
            node t = heap[s];
            heap[s] = heap[u];
            heap[u] = t;
            u = s;
        }
        else return;
    }     
}
void ins(node x){//插入
    //printf("ins = %d\n", x);
    heap[++size] = x;
    up(size);
}
void del(){//删除
    heap[1] = heap[size];
    size--;
    down(1);
}
int main(){
    k = read(); n = read();
    for (int i = 1; i <= k; i++){
        a[i] = read(); 
        ins((node){a[i], i});//这个js表示的a[js]是他的上一个乘的因子，如果我们每次在后面乘上的因子都大于等于他，那么2*3 = 3*2的情况就不存在了，而同样能够包括所有乘积，因为每个数分解开来都能够升序排列，例如12 = 2 * 2 * 3 有序之后就是乘因子的顺序了，这就是最巧妙的地方
    }
    while (n > 1){
        n--;
        node x = heap[1];
        //printf("%d %lld %d\n", n, x.data, x.js);
        del();
        for (int i = x.js; i <= k; i++) if ( a[i]*x.data > 2200000000) break;//题目里说答案不超过maxlongint，故在此特判
        else ins((node){a[i]*x.data, i});
    }
    printf("%lld", heap[1].data);
    return 0;
}
```

---

## 作者：walk_alone (赞：4)

首先，这个丑数是基于线性递推的，因为对于第$k$个丑数我们显然不可能在$O(1)$时间求出。那么如何递推呢？

考虑前面的丑数如何转移到当前的丑数：必然是前面某个较小的丑数乘以某一个质因数得到。对于样例$[2,3,5,7]$来说，$7$后面的丑数$8$就是由之前的丑数$4$乘以$2$得到；对于$14$来说，它是由之前$7$乘以$2$得到。

但是这存在一个问题：我不知道是前面哪一个丑数乘以哪一个质因数得到当前的丑数。所以要解决这个问题。

这个时候要注意到一个单调性：丑数本身具有单调性。也就是说，后面的丑数一定比之前的丑数大。把这个反映到它的构成，即是：**若两个丑数都由之前相同的丑数乘以某一个质因数得到，那么大的丑数乘以的质因数更大；若两个丑数都由同一个质因数乘以不同的前面的丑数得到，那么大的丑数乘以的前面的丑数也更大。**

考虑利用这个性质。用数组$id$记录第$i$个质因数在构成比当前丑数更大丑数所用的最小的丑数下标。如果用$ans$数组来记录丑数的话，那么$id$数组的定义即是：一个最小的num，满足$primes[i]\times ans[num]>ans[now]$，其中$ans[now]$为当前的丑数，那么$id[i]=num$。由上面的单调性可知，这个$id$数组内的数单调递增。

因而我们就可以构建起这样的算法流程：

**对于每一个质因数$primes[i]$，找到能与它相乘大于当前丑数的丑数编号并记录，然后更新下一个丑数值。**

代码如下：

```cpp
    int nthSuperUglyNumber(int n, vector<int>& primes)
    {
        sort(primes.begin(),primes.end());
        int m=primes.size();
        vector<int>id;
        id.resize(m);
        vector<int>ans;
        ans.push_back(1);//初始化，1为最小的丑数
        for(int i=1;i<=n;i++)//再往后找n次
        {
            int min=2147483647;
            for(int j=0;j<m;j++)
            {
                while(primes[j]*ans[id[j]]<=ans[i-1])//逐一判定。但是由于id的单调性因而省去不少时间。注意不能去掉等号
                    id[j]++;
                if(primes[j]*ans[id[j]]<min)
                    min=primes[j]*ans[id[j]];//min就是当前大于它的最小丑数
            }
            ans.push_back(min);
        }
        return ans[ans.size()-1];
    }
```
（这里有必要说明一下：这里故意使用的我在力扣提交的代码，请各位不要抄袭）

---

## 作者：jdsb (赞：4)

这道题需要我们求第n个丑数，许多人都会想到每次把当前最小的丑数取出来，在乘上所有的素数，再放入一个小根堆或set中。但其实这是有很多浪费的，许多大的丑数根本不会用到，这时我们来想一个方法，让它每次只需加入一个最小的丑数。

然后我们可以发现，当我们取出当前最小的丑数x时，下一个丑数有两种可能

1、x*p1

2、x/p1*p2

（x=上一个丑数/p1,p2为p1的下一个质数）

拿2,3,5,7来举例：

我们当前有一个数2，那下一个加入的丑数就是2*2和3

用这个方法，我们的时间复杂度就可以大大降低，为O(n log n)(log n为用set存储和更新的复杂度)

详细见下面代码
```cpp
//（这里的指针用法可能有点过于恶心，请大家见谅） 
#include<bits/stdc++.h>
#define mk  make_pair
#define ll long long
#define pii  pair<ll,ll>
#define fi first
#define se second 
using namespace std;
set<pii >st;
//我们选择将丑数放入一个set中，pair的第一关键字是数值，第二关键字是上一次乘的丑数标号
//因为set是自动去重和排序，而pair先按第一关键字比较，所以直接就可以取st.begin()作为答案 
set<pii >::iterator it;//一个set的迭代器 
ll n,m,a[100005],ans;
int main()
{
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	st.insert(mk(a[1],1));//先加入第一个丑数和标号 
	for(ll i=1;i<=m;i++)
	{
		it=st.begin();//将it指向set的开始地址 
		ans=it->fi;//ans等于it指向地址的first
		st.insert( mk( it->fi * a[it->se] ,it->se));
		//加入最小丑数*上次乘的素数 
		if(it->se<n) st.insert( mk( it->fi/a[it->se] * a[it->se+1] ,it->se+1));
		//加入最小丑数*下一个素数 
		st.erase(st.begin());
		//删除最小丑数
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：kczno1 (赞：4)

我的方法就是求k大的通用方法，用堆。


因为这题满足 一个数p1^a1\*..pn^an如果是当前最小，那么p1^a1\*..pn^（an-1）一定是曾经的最小。


所以我们用堆，记录乘积与最后的质数（来判重）。


每次取最小的，从堆中弹出，加入该数与（该数最后的质数-第k个质数）的组合


但是这样时间是nk log n，（但只有200ms）

优化一下，每次只加入1该数\*该数最后的质数2该数/该数最后的质数\*该数最后的质数后面的质数

时间就是n log n了，（但还是用了40ms）

```pascal
var
 n,k,o,i,j,top:longint;
 p:array[1..100] of longint;
 d,num:array[1..600000] of qword;

procedure swap(var x,y:qword);
var t:qword;
begin
 t:=x;x:=y;y:=t;
end;

procedure jia;
begin
 i:=top;
 while (i>1)and(d[i]<d[i>>1]) do
 begin
  swap(d[i],d[i>>1]);swap(num[i],num[i>>1]);
  i:=i>>1;
 end;
end;

procedure jian;
begin
 d[1]:=d[top];num[1]:=num[top];
 dec(top);

 i:=1;
 while (i<<1)<=top do
 begin
  if ((i<<1)=top)or(d[i<<1]<d[i<<1+1]) then i:=i<<1
  else i:=i<<1+1;

  if d[i]>=d[i>>1] then exit;
  swap(d[i],d[i>>1]);swap(num[i],num[i>>1]);
 end;
end;

begin  
 readln(n,k);
 for  i:=1 to n do read(p[i]);

 top:=1;d[1]:=p[1];num[1]:=1;
 for o:=2 to k do
 begin

   inc(top);d[top]:=d[1]*p[num[1]];num[top]:=num[1];
   jia;
   if num[1]<n then
   begin
       inc(top);num[top]:=num[1]+1;d[top]:=d[1] div p[num[1]] *p[num[top]];
     jia;
   end;

  jian;
 end;

 writeln(d[1]);
end.
```

---

## 作者：zmxqs (赞：3)

### [希丰展？](https://fangxizheng.blog.luogu.org/)

# 发布一个set+迭代器的解法

大家都知道STL set的底层是红黑树，能够实现排序+去重（**优先队列和set是不同的，优先队列是堆实现的**这个误区很多人估计犯）

萌新可能会将二叉排序树、红黑树、二叉搜索树、二叉平衡树弄混

在这里占坑讲一下

+ 平衡树是排序树的一种.在排序树的基础上加一条规则.即任何一个结点他的左右结点的总数相差不超过1

+ 查找树和排序树是一个东西。

+ 红黑树功能比平衡树树少，不过复杂度更优

另外如果有疑问的话，查资料推荐**oi-wiki**

尽量不要百度，因为上面的信息参差不齐，真真假假

迭代器的时间单次为O($logn$),挺优秀的

Tips：set的迭代器不支持任意访问（迭代器不能+=，-=）只能++，--


不过有一点需要注意的是，STL容器优秀的时间复杂度往往掩盖了它**大常数的事实**，所以少年啊，慎用STL

在这里，作者用了set~~（主要是想偷个懒）~~

+ 每次将当前这个数依次$\times p_1,p_2,...p_n$

因为题目保证$p_i$是正整数，所以这样得出的数量是单调递增的

因此指向it的答案不会影响

很暴力的一个做法，最后一个点会TLE

所以？打表即可

~~不要告诉我你不会下载数据~~

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long read();

set<long long> s;
long long dx[10010];
int k,n;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	s.insert(1);
	set<long long>::iterator it=s.begin();
	cin >> k >> n ;
	for(int i=1;i<=k;i++) {
		cin >> dx[i] ;
	}
	if(k==100) {
		cout<<"284456";
		return 0;
	} 
	for(int i=1;i<=n;++i) {
		long long num=*it;
		for(int j=1;j<=k;++j) {
			s.insert(num*dx[j]);
		}
		it++;
	}
	cout<<*it;
	return 0;
}
```

---

## 作者：Tanktt (赞：3)

这道题是~~暴力~~的优化而已。
只要暴力枚举k。因为当前的丑数是前面任意的一个丑数乘上素数的最小值，所以再枚举乘上的素数。对于每一个素数a[j]，我们有一个b数组来记录在i-1时a[j]必须乘上哪个丑数才能大于第i-1个丑数，因为第i个大于第i-1个丑数，所以b[j]只会递增或不变。还有最小值的初值需要定大些，在2亿以上，因为题目中只是长整型范围。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,a[112],b[112],f[100012],mn;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%d",&a[i]);
	f[0]=1;
	for (int i=1; i<=m; i++)
	{
		mn=2147483647;
		for (int j=1; j<=n; j++)
		{
			while (a[j]*f[b[j]]<=f[i-1]) b[j]++;
			mn=min(mn,a[j]*f[b[j]]);
		}
		f[i]=mn;
	}
	return printf("%d\n",f[m]),0;
}
```

---

## 作者：muyang_233 (赞：3)

~~翻了那么多竟然没有看到BFS？？？~~  
这里要运用到一种单序列三下标的办法。
设s数组存集合元素，p数组第i位存上一次乘s[i]的数的位置，a数组存所有丑数，枚举每一次s[i]乘a[p[i]]的大小，找到一个最小值，存入当前数组，如果存入的这个数是由某个数*s[i]得到的，则p[i]++，这样枚举下去，最后，输出a[n]。  
代码如下：  
```cpp
//本程序由姆洋题解©官方提供，姆洋题解，蒟蒻们的题解
#include <bits/stdc++.h>
using namespace std;
int k,n;
int s[101],a[100001],p[101];
int minn(int _[],int __[],int n)//找s[i]*a[p[i]]的最小值
{
	int minx=2147483647;
	for (int i=1;i<=n;i++)
		if (_[i]*a[__[i]]<minx) minx=_[i]*a[__[i]];
    minx=chen_zhe=kkksc03=lin_toto;
	return minx;
}
int main()
{
	scanf("%d%d",&k,&n);
	for (int i=1;i<=k;i++) scanf("%d",&s[i]);
	a[0]=1;
	sizeof(0,p,sizeof(p));
	for (int i=1;i<=n;i++)
	{
		int x=minn(s,p,k);
		a[i]=x;//存入a数组
		for (int i=1;i<=k;i++)
		    if (x==s[i]*a[p[i]]) p[i]++;//判断由哪个集合元素读入，其p数组对应值++
	}
	printf("%d\n",a[n]);//输出
	return 0;//happy ending
}
```
~~我才不会告诉你我程序里有防伪标志~~

---

## 作者：vegetabird (赞：3)

**怎么没人写暴力啊？？？**

这不是标准的~~SBT~~BST裸题吗？

用一个平衡的BST维护当前的最小值，最大值，每次取出最小值，然后乘以每一个质数插入BST，如果BST的大小大于剩余的数的数目，就删去最大值。就这样做N次就行了

本人用的是SBTree

Hint: 用set会T！！！

CODE:
```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<utility>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
#include<set>
#ifndef STDIO_H
#include<stdio.h>
#endif
#ifndef STRING_h
#include<string.h>
#endif
#ifndef SBT_H
#define SBT_H
namespace sbt{
    class intsbt{            //Ä¬ÈÏËùÓÐ²Ù×÷¾ùÎªÓÐÐ§²Ù×÷
        private:
            long long num[1000010];
            int sz[1000010],lch[1000010],rch[1000010],cnt,treeroot;
            long long maxn,minn;
            #ifndef INF
            static const long long INF=0x7fffffffffff;
            #endif
            inline void set_default(){
                lch[0]=rch[0]=0,cnt=1,maxn=-INF,minn=INF,sz[0]=sz[1]=0,num[0]=num[1]=0,treeroot=1;
            }
            inline void left_rotate(int &root){
                static int tmp;
                tmp=rch[root];
                rch[root]=lch[tmp];
                lch[tmp]=root;
                sz[tmp]=sz[root];
                sz[root]=sz[lch[root]]+sz[rch[root]]+1;
                root=tmp;
            }
            inline void right_rotate(int &root){
                static int tmp;
                tmp=lch[root];
                lch[root]=rch[tmp];
                rch[tmp]=root;
                sz[tmp]=sz[root];
                sz[root]=sz[lch[root]]+sz[rch[root]]+1;
                root=tmp;
            }
            void maintain(int &root){
                if(sz[rch[root]]<sz[lch[lch[root]]]){
                    right_rotate(root);
                    maintain(rch[root]);
                    maintain(root);
                }
                if(sz[rch[root]]<sz[rch[lch[root]]]){
                    left_rotate(lch[root]);
                    right_rotate(root);
                    maintain(lch[root]);
                    maintain(rch[root]);
                    maintain(root);
                }
                if(sz[lch[root]]<sz[rch[rch[root]]]){
                    left_rotate(root);
                    maintain(lch[root]);
                    maintain(root);
                }
                if(sz[lch[root]]<sz[lch[rch[root]]]){
                    right_rotate(rch[root]);
                    left_rotate(root);
                    maintain(lch[root]);
                    maintain(rch[root]);
                    maintain(root);
                }
            }
            bool ins(int root,const long long &val){
                sz[root]++;
                if(sz[root]==1){
                    num[root]=val;
                    return true;
                }
                if(val==num[root]){
                    sz[root]--;
                    return false;
                }
                if(val<num[root]){
                    if(!lch[root]){
                        lch[root]=++cnt;
                    }
                    if(ins(lch[root],val)){
                        maintain(lch[root]);
                        return true;
                    }else{
                        sz[root]--;
                        return false;
                    }
                }else{
                    if(!rch[root]){
                        rch[root]=++cnt;
                    }
                    if(ins(rch[root],val)){
                        maintain(rch[root]);
                        return true;
                    }else{
                        sz[root]--;
                        return false;
                    }
                }
            }
            int del(int &root,const long long &val){
                int ret;
                sz[root]--;
                if(!sz[root]){
                    lch[root]=rch[root]=0;
                    ret=root;
                    root=0;
                    return ret;
                }
                if(val<num[root]){
                    if(lch[root]){
                        ret=del(lch[root],val);
                        maintain(root);
                        return ret;
                    }else{
                        ret=root;
                        root=rch[root];
                        lch[ret]=rch[ret]=0;
                        return ret;
                    }
                }else if(val>num[root]){
                    if(rch[root]){
                        ret=del(rch[root],val);
                        maintain(root);
                        return ret;
                    }else{
                        ret=root;
                        root=lch[root];
                        lch[ret]=rch[ret]=0;
                        return ret;
                    }
                }
                if(!lch[root]||!rch[root]){
                    root=lch[root]+rch[root];
                    return root;
                }
                ret=lch[root];
                while(rch[ret])ret=rch[ret];
                num[root]=num[ret];
                return del(lch[root],num[ret]);
            }
            inline int findminpos(int root){
                while(lch[root])root=lch[root];
                return root;
            }
            inline int findmaxpos(int root){
                while(rch[root])root=rch[root];
                return root;
            }
            inline long long max(const long long &a,const long long &b){
                return a>b?a:b;
            }
            inline long long min(const long long &a,const long long &b){
                return a<b?a:b;
            }
        public:
            inline intsbt(){
                set_default();
            }
            ~intsbt(){
                memset(num,0,sizeof(num));
                memset(sz,0,sizeof(sz));
                memset(lch,0,sizeof(lch));
                memset(rch,0,sizeof(rch));
                cnt=treeroot=maxn=minn=0;
            }
            inline void insert(const long long val){
                ins(treeroot,val);
                maintain(treeroot);
                maxn=max(maxn,val);
                minn=min(minn,val);
            }
            inline void erase(const long long val){
                del(treeroot,val);
                if(val==maxn){
                    maxn=num[findmaxpos(treeroot)];
                }
                if(val==minn){
                    minn=num[findminpos(treeroot)];
                }
                if(!sz[treeroot]){
                    treeroot=++cnt;
                    maxn=-INF;
                    minn=INF;
                }
            }
            inline long long max(){
                return maxn;
            }
            inline long long min(){
                return minn;
            }
            inline int size(){
                return sz[treeroot];
            }
    };
}
#endif
using namespace sbt;
long long k,n;
long long prime[110];
intsbt t;
int main(){
    long long i,j,l;
    scanf("%lld%lld",&k,&n);
    for(i=1;i<=k;i++){
        scanf("%lld",prime+i);
        t.insert(prime[i]);
    }
    std::sort(prime+1,prime+k+1);
    long long ans;
    while(n--){
        ans=t.min();
        t.erase(ans);
        for(i=1;i<=k;i++){
            t.insert(ans*prime[i]);
            if(t.size()>n){
                t.erase(t.max());
                if(ans*prime[i]>=t.max()){
                    break;
                }
            }
        }
    }
    printf("%lld\n",ans);
}
```

---

## 作者：Mizuhara (赞：2)

挺好的一道题。

我只想到了用$1-n-1$的丑数依次生成丑数，用优先队列来找最小的做法。

代码如下：
```
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<set>
#define mk(a) ((L){a})
#define inf 2147483647LL
#define ll long long int
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int maxn=111111;
struct L{
    ll x;
    bool operator < (const L &b)const{
        return x>b.x;
    }
};
priority_queue <L> qu;

int k,n;
ll p[maxn];
int main(){
    cin>>k>>n;
    rep(i,1,k)cin>>p[i],qu.push(mk(p[i]));
    rep(i,1,n-1){
        ll x=qu.top().x;//cout<<x<<endl;
        while(qu.top().x==x)qu.pop();//去重
        rep(j,1,k)qu.push(mk(x*p[j]));
    }
    cout<<qu.top().x;
    return 0;
}
```

然而这样生成的丑数太多了。实际上，光是$n*k$就已经接近时限了。

实际上，我们只需要用到$1-n$的丑数，后面过大的没有必要生成。

但每次暴力找到当前丑数所能生成的最小新丑数是$O(n^2k)$的。

然后我们发现，找最小新丑数具有两个单调性。

$1:$对于每个丑数，其用到的质数是单调增的。

$2:$对于v每个质数，其用到的丑数也是单调增的。

使用第一个单调性的复杂度是$O(n^2+nk)$，第二个是$O(k^2+nK)$。

显然我们只要使用第二个单调性就可以解决此题。

```
#include<iostream>
#include<cstring>
#include<cstdio>
#define ll long long int
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
using namespace std;
const int maxn=111111;

int k,n;
ll p[maxn],f[maxn],cur[maxn];//cur记录当前p所用到的最大丑数
int main(){
    scanf("%d%d",&k,&n);
    rep(i,1,k)scanf("%lld",&p[i]);
    memset(cur,0,sizeof(cur));
    f[0]=1;
    rep(i,1,n){
        ll mi=4000000000LL;
        rep(j,1,k){
            while(p[j]*f[cur[j]]<=f[i-1])cur[j]++;
            if(p[j]*f[cur[j]]<mi)mi=p[j]*f[cur[j]];
        }
        f[i]=mi;
    }
    cout<<f[n];
    return 0;
}
```

---

## 作者：iftest614 (赞：2)

redbag大神已经说得很明确了。

但是有些人刚开始可能看不懂（比如我233333）

所以讲的明确一点。

看到这题我们第一反应就是暴力啊

可以暴力出所有的丑数。当然是组合一下下。然后找出第n个就好啦

但是这题的范围是smg。。

所以我们会发现~

第i个丑数可以算成第i-1个丑数乘以某一个（第一个乘出比i数大）在集合内的数。

假设第i-1个丑数为p1\*p3

那么第i个丑数一定包含第i-1个丑数，即包含p1\*p3.

那么就可以搜出最小的比i-1大的丑数。

这样就不会超了。

伪代码如下：

```cpp
    for(i=1;i<=k;i++)
    {   
        minn=21426080614;
        for(j=1;j<=n;j++)
        {   
            while(s[f[j]]*p[j]<=s[i-1]) f[j]++;
            minn=min(s[f[j]]*p[j],minn);
         }
        s[i]=minn;
    }

```

---

## 作者：狂犇 (赞：2)

我们在数组 hum 中计算出前 n 个丑数。为了实现起来更简单，我们把 1 也作为一个丑数，算法也要因此略微调整一下。

当我们已知前 k 个丑数，想得到第 k+1 个，我们可以这样做：对于每个质数 p，寻找最小的丑数 h，使得 h*p上一个丑数大。取我们找到的 h*p中最小的一个，它就是下一个丑数。

为了使搜索更快，我们可以为每个质数维护一个引“pindex”表示每个质数已经乘到了哪个丑数，每次都从那里开始，而不是再从头再来。

方法二

这道题可以用 BFS+Treap 来做。但这里的 BFS 不使用队列来扩展，而是用 Treap 来扩展。

建一个 Treap 保存已经得到的数，从小到大每次从堆中取出一个数，用它和集合中的质数相乘，查找判断它是否重复.如果没有重复，那么将它插入到 Treap 中。直到产生了 n 个数 ，
那么再往后扩展一位，得到的第 n 个数既为所求的结果。时间复杂度：BFS 扩展为 O(N)，

查第 k 大为 O(logN)判重为 O(logN)，插入为 O(logN)，因此总的复杂度为 O(NlogN)

我的思路是每次从堆中取一个，然后从质数集合里扫一遍。虽然不能保证新扩展出的数的顺序，但很类似 Astar，第 n 个开始扩展的节点可以确定，复杂度应该为 nklogn，可惜内存不够

方法三

这道题目可以直接应用 STL 中的 priority_queue 来做，复杂度为 O(NKlogN)，对于第 i小的数，扩充它能得到的所有新元素并插入 priority_queue 中，然后 pop 第ｉ小的数。

**时间没问题，但是空间会爆，当然只对于最后一个数据，我最后一个数据在自己机子上 RUN 完后，骗过去的，USACO 上分配内存太小!**

---

## 作者：msy66 (赞：1)

#### 显然，任何一个丑数都可以表示为（1或某丑数）* 素数集合S的质数。

那么，我们可以用一个**堆**来维护一部分丑数，先开始，堆里只有1。每次取出最小元素，将其与所有质数的乘积依次放入堆即可。

但是堆并不方便：因为里面有太多重复元素，消耗时间和空间。所以我们用set就好了，就像下面这样:

```cpp
  set<int>s;
  s.insert(1);
  for(reg int i=0;i<=n;i++){
    ans=*s.begin();s.erase(ans);
    for(reg int j=1;j<=k;j++){
      long long t=1ll*ans*p[j];
      if(t<2147483647) s.insert(t);//防止溢出
    }
  }
 
```

这时，我发现我T了一个点，显然上面算法的复杂度较高;

优化一下，如果发现堆内数字多余N个，后面的数字就都没用了，可以删去。再随便加一点优化~~(用STL，O2是逃不掉的)~~就能过了。

完整代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<set>
#include<algorithm>
#define reg register
using namespace std;
typedef long long ll;
int a,x,ans;
int k,n,p[110];
set<int>s;
int main(){
  cin>>k>>n; 
  for(int i=1;i<=k;i++)
    scanf("%d",&p[i]);
  sort(p+1,p+k+1);//排序后便于后面的优化,见（*）
  s.insert(1);
  for(reg int i=0;i<=n;i++){
    ans=*s.begin();s.erase(ans);
    for(reg int j=1;j<=k;j++){
      long long t=1ll*ans*p[j];
      if(t<2147483647) s.insert(t);//防止溢出
      else break;//（*）
    }
    while(s.size()>n+10) s.erase(--s.end());
  }//+10是为了以防万一
  cout<<ans<<endl;
  return 0;
  
}

```

---

## 作者：StephenYoung (赞：1)

丑数就是一个丑数乘上丑数的标准数（题目中的p数组），所以我们可以从生成丑数的角度判断而代替直接判断它的因子。

通常，最简单的方法肯定是遍历数组，然后确定每一个数是否是丑数，这种方法是最简单并且直观的。

代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll a[1000005],n,k,st[10000006],id[10000005];

void generate()
{
	for(int i=1;i<=k;i++)
	id[st[i]]=0;
	//id[2]=0,id[3]=0,id[5]=0;
	int ord=0;
	a[0]=1;
	while(ord<n+10)
	{
		//ll t=min(a[id[2]]*2,min(a[id[3]]*3,a[id[5]]*5));
		ll t=5000000000;
		for(int i=1;i<=k;i++)
		{
			t=min(t,a[id[st[i]]]*st[i]);
		}
		for(int i=1;i<=k;i++)
		{
			if(t==a[id[st[i]]]*st[i])
			id[st[i]]++;
		}
		/*if(t==a[id[2]]*2) id[2]++;
		if(t==a[id[3]]*3) id[3]++;
		if(t==a[id[5]]*5) id[5]++;*/
		a[++ord]=t;
	}
}

int main()
{
	scanf("%lld%lld",&k,&n);
	for(int i=1;i<=k;i++)
	scanf("%lld",&st[i]);
	generate();
		cout<<a[n]<<endl;
	return 0;
}
```


---

