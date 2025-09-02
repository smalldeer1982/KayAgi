# kry loves 2048

## 题目背景

kls是一个人赢。

## 题目描述

kls最近在玩一款类似2048的游戏，规则是这样的：

一开始，有$n$个方块，每个方块上有一个$1$到$m$的整数。

kls可以进行两种操作：

1. 选择两个数字相同的方块（不一定要相邻），将它们合并成一个数字为原来的两倍的方块；

2. 减小一个方块上的数字。

操作的次数没有限制，最终的得分为所有方块上的最大的数字。

因为kls要去陪妹子了，没有时间继续玩，他想让你帮忙计算一下，最多能得到多少分。

## 说明/提示

### 样例解释

样例1生成出来的数是 6 10 7 5 4。

样例2生成出来的数是 8 12 48 4 4。

### 数据范围

对于30%的数据，$n, m \le 10$；

对于60%的数据，$n, m \le 10^5$；

对于100%的数据，$n, m \le 10^7$，$1 \le seed \le 10^9$。

## 样例 #1

### 输入

```
5 10 233```

### 输出

```
24```

## 样例 #2

### 输入

```
5 50 3```

### 输出

```
48```

## 样例 #3

### 输入

```
1000 1000 666```

### 输出

```
374784```

# 题解

## 作者：叶小枫 (赞：15)

# 一道卡桶排卡的很死的题目
-------
## 基本思路

首先我们拿到这道题，先来读一遍……读完之后发现这道题好像闹着玩一样，就是每次把最小的那个数乘2就好了。只是有一点需要注意那就是最后一次比较的判断：如果一趟乘2下来后第二大的数字乘上2比最大的那个数还要小，那么就输出最大的那个，之前的就不用管了。

## 问题实现

为了更好的实现我们的思路，我们可以开一个队列q，类型为`long long` ：`queue<long long> q`

说到这个队列里面存的数具体表示什么意义，还真不是一两句话就能说明白的。那么我们暂且抛开对q的具体定义，先来说一说开这个q的目的：

&emsp;&emsp;**用来暂存当前已得到的最大数值，在数组待选择的下一个数比队列元素小时使用队列中的元素，并弹出**

这样一来咱们的问题实现就很简单了，分为以下步骤：

1. 使用给定的随机数生成器生成数据并存储
2. 排序该数组
3. 向q中推入目前得到的最大数
4. 数组中没有更大的数可以选择时，调用q中元素直到**数组**元素选完（此时q中仅存的数字就是答案）
5. 输出`q.front()`

~~这题做完了~~

## 巨大问题

但是我们看到了这一题的**数据范围**非常**不友好**：n,m≤10^7 ……

> nlogn基本超了十的五次方就炸了，n的话能坚持到六次方    ——jiang25262

那么我们回头来捋一捋我们学过的一些排序算法：

- 冒泡
- 插入
- 选择
- 快排
- 归并
- ~~基数~~（太玄学）
- …………

我们发现好像上面说到的方法都最多只能撑到1e5，这样的程序是不会AC的。但是结合我们上述的问题实现分析，我们起码可以写出一个**及格（60分）的代码**：

### 60分代码
```cpp
#include<iostream>
#include<queue>
#include<algorithm>
#define ll long long
#define rint register int
using namespace std;
const int maxn=1e7+10;
ll cnt,n,m;
int a[maxn],b[maxn];
queue<ll>q;
void generate_array(int n, int m, int seed) {
    unsigned x = seed;
    for (int i = 0; i < n; ++i) {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        a[i]=(x % m+ 1);
    }
}

inline ll get(){
    if(q.empty())
        return a[cnt++];

    ll f=q.front();
    if(cnt==n||a[cnt]>f){
        q.pop();
        return f;
    }

    return a[cnt++];
}

int main(){
    ios::sync_with_stdio(false);//使用最快速的读入（其实没用）
    int seed;
    cin>>n>>m>>seed;
    generate_array(n,m,seed);

    sort(a,a+n);//使用还可以的快排排序

    ll a1,a2;
    for(rint i=1;i<=n-1;i++){
        a1=get();a2=get();
        q.push(max(a1<<1,a2));
    }
    cout<<q.front()<<'\n';
    return 0;
}
```
## 问题解决

仔细阅读我们的60分代码我们可以发现一个显而易见的问题，即：**该程序的时间复杂度其实就是排序的时间复杂度**。因为对于队列的操作都是O(1)的，获取元素的操作是O(n)的，排序的复杂度再低也低不到O(n)以下。故排序复杂度决定了这题的复杂度。

所以我们现在亟待解决的就是排序问题。

分析到现在，想必我们的目的已经非常明确：**我们需要一个O(n)的排序算法！**

### 桶排！

桶排的基本思路是这样，我们把它形象化：

&emsp;&emsp;先开一个数组作为一个桶，然后把等待排序的元素倒进桶里。为了维护“倒进去”的过程，我们对于每一个元素按照其数值计数：
```cpp
b[a[i]]++;//其中a为待排序数组，b为桶
```
&emsp;&emsp;接着我们需要找到这些数的最大值，从0开始（如果保证数据>0的话）依次枚举数字，以检查桶中是否有这个数字。如果桶中有，就倒出来，有几个就倒几个：
```cpp
int t=0;
    for(rint i=0;i<=m;++i)
        while(b[i]>=1){
            a[t++]=i;
            b[i]--;
        }
```
&emsp;&emsp;倒完了，咱们也就排完了。上标准代码：
```cpp
for(int i=0;i<n;++i)
		b[a[i]]++;
    int t=0;
    for(rint i=0;i<=m;++i)
        while(b[i]>=1){
            a[t++]=i;
            b[i]--;
        }
//其中，n为元素个数，m为这些元素的最大值
```
桶排就讲完了，讲完了桶排，这一题也就没有什么可以讲的了。我们接下来要做的只是把原来的`sort(a,a+n)`换成标准桶排就可以了。

这题真正做完，最后奉上AC代码。
## AC代码
```cpp
#include<iostream>
#include<queue>
#define ll long long
#define rint register int
using namespace std;
const int maxn=1e7+10;
ll cnt,n,m;
int a[maxn],b[maxn];
queue<ll>q;
void generate_array(int n, int m, int seed) {
    unsigned x = seed;
    for (int i = 0; i < n; ++i) {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        a[i]=(x % m+ 1);
    }
}

inline ll get(){
    if(q.empty())
		return a[cnt++];

    ll f=q.front();
    if(cnt==n||a[cnt]>f){
		q.pop();
		return f;
	}

    return a[cnt++];
}

int main(){
	ios::sync_with_stdio(false);
    int seed;
    cin>>n>>m>>seed;
    generate_array(n,m,seed);

    for(rint i=0;i<n;++i)
		b[a[i]]++;
    int t=0;
    for(rint i=0;i<=m;++i)
        while(b[i]>=1){
            a[t++]=i;
            b[i]--;
        }

    ll a1,a2;
    for(rint i=1;i<=n-1;i++){
        a1=get();a2=get();
        q.push(max(a1<<1,a2));
    }
    cout<<q.front();
    return 0;
}
```
## 鸣谢

教会了我桶排的 @晨搏的小迷妹 U84254

部分代码提供 @晨搏的小迷妹 U84254

复杂度简要区分 @jiang25262 U50227

## 最后宣传一下我们的团队

欢迎加入我们的团队：[洛谷团队传送门](https://www.luogu.org/team/show?teamid=10716)

刚刚入门的oier们可以在这里得到最基础的技能培训辅导，我们随时可以为入门级的oier们答疑解惑。进入团队即可获得本团队人员录制的线上课程，主要针对竞赛入门向。在语法课程结束后我们会开启算法线上课程，敬请期待！

当然也非常欢迎各路大佬神犇光临出题虐菜（主要是虐我，他们都比我强）

**私信我获取团队QQ群号和线上课程地址**

## 感谢阅读



---

## 作者：chrispang (赞：2)

建议可以先做完[合并果子](https://www.luogu.com.cn/problem/P6033)再来做这道题。

本题看似有点难度（大佬除外），所以本蒟蒻来给大家浅浅的分析一下吧！

### 基本思路


---


1. 把序列生成之后记录下来。
2. 每次选取队列中最小的两个数（可以用优先队列实现），要不然把次小数减到最小数，或者把最小数减到 $0$，选出最大值。
3. 输出队头元素，本题大致思路完成。

### 一些细节


---


那么贴上我们的 $60$ 分代码吧！（请注意，这是 $60$ 分的）


```cpp
#include <bits/stdc++.h>
#define int long long //不开long long见祖宗 
using namespace std;

int n, m, seed, cnt, temp, a[10000010];
priority_queue<int, vector<int>, greater<int> >q;
void generate_array(long long a[], long long n, long long m, long long seed) {
    unsigned x = seed;
    for (int i = 1; i <= n; ++i) {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        a[i] = x % m + 1;
    }
}

int get() {
	int x = q.top(); //取出队头元素 
	q.pop(); //删除队头元素 
	return x;
}

signed main() {
    cin >> n >> m >> seed;
    generate_array(a, n, m, seed);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
    	q.push(a[i]);
    for (int i = 1; i <= n - 1; i++) {
        int t1 = get(), t2 = get();
        q.push(max(t1 * 2, t2)); //两种情况，取最大值 
    }
    cout << q.top() << endl;
    return 0;
}
```

### 进行改进

很明显，这个代码太慢了，我们需要改进。而排序和取最小值的那一部分花费的时间为 $O(n\operatorname{log}n)$，所以我们只需要把这两个地方进行改进就行了。

那如何改进呢？先想排序（在这里大家可以去看看我的[这篇文章](https://www.luogu.com.cn/article/cxy6pl5o)，里面有详细的介绍）可以很容易想到用桶排。而取最小值可以建立两个队列，排序结果放进第一个当中，合并结果放在第二个当中，每次选从两个队列队头选取比较小的合并就可以了。

最后贴上我们的 AC 代码。（这次是真 AC）


```cpp
#include <bits/stdc++.h>
#define int long long //不开long long见祖宗 
using namespace std;

int n, m, seed, cnt, temp, a[10000010], t[10000010];
queue<int>q1;
queue<int>q2;
void generate_array(long long a[], long long n, long long m, long long seed) {
    unsigned x = seed;
    for (int i = 1; i <= n; ++i) {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        a[i] = x % m + 1;
    }
}

int get() {
	int x;
	if(q2.empty() || (!q1.empty() && q1.front() < q2.front())) { //如果q2空了，或者q1的队头元素大于q2的队头元素，则选q1的队头元素
		x = q1.front(); q1.pop();
	} else { //否则选q2的队头元素
		x = q2.front(); q2.pop();
	}
	return x;
}

signed main() {
    cin >> n >> m >> seed;
    generate_array(a, n, m, seed);
    for (int i = 1; i <= n; i++)
        t[a[i]]++; //桶排代码 
    for (int i = 0; i <= m; i++)
        while (t[i]--) q1.push(i); //加入元素 
    for (int i = 1; i <= n - 1; i++) {
        int t1 = get(), t2 = get();
        q2.push(max(t1 * 2, t2)); //取最大值 
    }
    cout << q2.front() << endl;
    return 0;
}
```

---

## 作者：zbk233 (赞：2)

## 题意简述

有 $n$ 个数字，你可以进行以下操作：

1. 任意选择两个相同的数字，将它们合并为一个值为原来的两倍的数字。

2. 减小任意一个数字。

请你求出这些数字的最大值。

## 解题思路

类似于[合并果子](https://www.luogu.com.cn/problem/P1090)的一道题。

一个数与小于等于它的数中最大的数合并一定是最优的。

所以，每次选出最小的两个数合并，最后得出的一定是最大值。

## 做法一

用小根堆维护一个从小到大的数组，也可以用 $\texttt{STL}$ 的优先队列实现。

每次弹出最小的两个数，再将最小数的两倍放进来。

时间复杂度：$O(n\log n)$，预计得分：$60$ 分。

十年 $\texttt{OI}$ 一场空，不开 $\texttt{long long}$ 见祖宗。

不开 $\texttt{long long}$ 预计得分：$20$ 分。

## 代码实现

```cpp
#include<iostream>
#include<queue>
#define ll long long
using namespace std;
const ll MAXN=1e7+5;
ll n,m,seed,ans;
ll a[MAXN];
priority_queue<ll,vector<ll>,greater<ll> > q;
void fuck(ll n,ll m,ll seed){ 
    unsigned x=seed;
    for(int i=1;i<=n;i++){ 
        x^=x<<13;
        x^=x>>17;
        x^=x<<5;
        a[i]=x%m+1;
    } 
}
int main(){
    cin>>n>>m>>seed;
    fuck(n,m,seed);
    for(int i=1;i<=n;i++){
        q.push(a[i]);
    }
    while(q.size()>1){
        ll x=q.top(),y,z;
        q.pop();
        y=q.top();
        q.pop();
        z=x*2;
        ans=max(ans,max(x,y));
        q.push(max(z,y));
    }
    ans=max(ans,q.top());
    cout<<ans;
    return 0;
}
```

## 做法二

优先队列明显是不行了，原方法有很大的优化空间。

我们需要一个新的方法。

我们先对原数组进行排序。

每次合并操作都是删除一个数字，那么一定要进行 $n-1$ 次操作。

所以，我们从 $1$ 到 $n-1$ 进行循环，之后就是取两个最小值的操作。

我们可以用一个队列，这个队列是维护一个最大值。

用一个指向原数组的指针。

当这个指针指向的数大于队首时，弹出队首，否则弹出这个指针指向的数。

事实上，这个做法已经很优了，唯一可以优化的地方就是排序方法了。

我们可以使用计数排序。

## 代码实现

```cpp
#include<iostream>
#include<queue>
#define ll long long
using namespace std;
const int MAXN=1e7+5;
int n,m,seed,cnt=1,len,maxa,mina=MAXN;
int a[MAXN],b[MAXN],t[MAXN];
queue<ll> q;
void fuck(ll n,ll m,ll seed){ 
    unsigned x=seed;
    for(int i=1;i<=n;i++){ 
        x^=x<<13;
        x^=x>>17;
        x^=x<<5;
        b[i]=x%m+1;
    } 
}
ll get(){
    if(q.empty()) return a[cnt++];
    ll tmp=q.front();
    if(cnt==n+1||a[cnt]>tmp){
        q.pop();
        return tmp;
    }
    return a[cnt++];
}
int main(){
    cin>>n>>m>>seed;
    fuck(n,m,seed);
    for(int i=1;i<=n;i++){
        t[b[i]]++;
        maxa=max(maxa,b[i]);
        mina=min(mina,b[i]);
    }
    for(int i=mina;i<=maxa;i++){
        for(int j=1;j<=t[i];j++){
            a[++len]=i;
        }
    }
    for(int i=1;i<n;i++){
        ll x=get(),y=get();
        q.push(max(x*2,y));
    }
    cout<<q.front();
    return 0;
}
```


---

## 作者：Alarm5854 (赞：1)

这一道题一看貌似可以用堆过?再一看，$n\le 10^7$，$nlog_2n\approx10^7*24=2.4*10^8$，超过运行速度的极限了，看来要另想方法了，桶排已经介绍过了，我来水一波基排题解(不过为什么不是$m\le 10^9$呢)，我选$256(2^8)$作为基数，来卡一级缓存，速度更快，而且$10^7\approx2^{24}$，所以只要进行3次基数排序即可，时间复杂度为$O(nlog_{256}n)$即$O(\frac{1}{8}nlog_2n)$，速度略比桶排慢，但可以通过本题，记得开long long。不开long long引发的惨案：![](https://cdn.luogu.com.cn/upload/image_hosting/60kbicbn.png)
### 完整代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 10000000+10
#define F(i,a,b) for(register ll (i)=(a);(i)<(b);++(i))//这两行偷懒用
#define D(i,a,b) for(register ll (i)=(b)-1;(i)>=(a);--(i))
using namespace std;
ll n,m,seed,cnt,a[N],b[N],c[256];//c数组储存对256取余的结果，为了方便我直接全部开long long
queue<ll>q;
void generate_array(ll a[],ll n,ll m,ll seed){
	unsigned x=seed;
	F(i,0,n){
		x^=x<<13;
		x^=x>>17;
		x^=x<<5;
		a[i]=x%m+1;
	}
}
inline void radixsort(ll a[]){
	F(k,0,3){
		F(i,0,256) c[i]=0;
		F(i,0,n)
			++c[(a[i]>>(k<<3))&255];//这里用到了常数优化，原本应写作c[a[i]/(8*k)%256]++;
		F(i,1,256) c[i]+=c[i-1];//前缀和
		D(i,0,n)
			b[--c[(a[i]>>(k<<3))&255]]=a[i];//把它储存到b数组
		F(i,0,n)
			a[i]=b[i];//复制元素
	}
}
inline ll get(){//类似于堆取最小值
	if(q.empty()) return a[cnt++];
	ll f=q.front();
	if(cnt==n||a[cnt]>f){
		q.pop();
		return f;
	}
	return a[cnt++];
}
int main(){
	scanf("%lld%lld%lld",&n,&m,&seed);
	generate_array(a,n,m,seed);
	radixsort(a);
	F(i,1,n){
		ll s1=get(),s2=get();
		q.push(max(s1<<1,s2));//这里有两种选择，把次小值减小到最小值或把最小值减少到0，取两种结果的最大值
	}
	printf("%lld",q.front());//直接输出
	return 0;
}
```
事实上，$O(nlog_2n)$算法的$n$一旦超过$2^{22}$，基本上凉凉了，所以基数排序也是要学会的。

---

## 作者：Wy_x (赞：0)

题目传送门：[P4829 kry loves 2048
](https://www.luogu.com.cn/problem/P4829)

**此题解不开 O2 能过。**

------------

### 解法：


双倍经验：[P6033 合并果子 加强版](https://www.luogu.com.cn/problem/P6033)

类似于合并果子的解法：最优方案一定是两个最小的数据进行合并，一共会合并 $n-1$ 次。

先根据题意造好数据,建立两个队列 $q_1,q_2$ 来模拟合并过程。

再用桶排把每个数字出现次数统计一下。

把排好序后的数字推入队列 $q_1$ 中，易发现 $q_1$ 中的数是单调不降的。
 
再维护一个队列 $q_2$，存储操作过后的数据，易发现 $q_2$ 中的数也是单调不降的。

最后，操作时，只需要取出两次队列 $q_1,q_2$ 的队头的最小值，再把操作后的数据推入 $q_2$ 的队尾即可。

**注意：操作时，有两种操作方法，即把最小的数** $\times 2$ **推入** $q_2$ **的队尾，或把第二小的数据直接推入** $q_2$ **的队尾，需要对这两种情况取** $\max$。

$n-1$ 次操作后，输出 $q_2$ 的队头即可。

------------


### 代码实现：
```cpp
#include<cstdio>
#include<queue>
#define int long long

using namespace std;
queue<int> q1,q2;
signed a[(int)1e7+7],t[(int)1e7+7];

inline int max(int x,int y) { return x>y?x:y; }
inline int min(int x,int y) { return x<y?x:y; }

inline int get_first()//取两个队列对头的最小值
{
	if(q2.empty()||(!q1.empty()&&q1.front()<q2.front()))
	{//q1 的队头最小或 q2 为空
		int x=q1.front();
		q1.pop();
		return x;
	}
	//q2 的队头最小或 q1 为空
	int x=q2.front();
	q2.pop();
	return x;
}

void generate_array(signed a[], signed n, signed m, signed seed) {
	unsigned x = seed;
	for (int i = 1; i <= n; ++i) {
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		a[i] = x % m + 1;
	}
}
signed n,m,seed;
signed main()
{
	scanf("%d%d%d",&n,&m,&seed);
	generate_array(a,n,m,seed);//构造数据
	for(register int i=1;i<=n;i++) t[a[i]]++;//桶排
	for(register int i=1,j=1;i<=10000000;i++)
	{
		if(t[i]) for(j=1;j<=t[i];j++) q1.push(i);
		//向 q1 中推入数据
	}
	
	for(register int i=1;i<n;i++)
	{
		int x=get_first();//第一次取队头的最小值
		int y=get_first();//第二次取队头的最小值
		q2.push(max(max(x,y),min(x,y)<<1));
		//对两种情况取 max
	}
	printf("%lld",q2.front());
	
	
	return 0;
}
```


---

