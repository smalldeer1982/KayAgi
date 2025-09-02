# たのしい家庭菜園

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2014/tasks/joisc2014_b



# 题解

## 作者：是个汉子 (赞：15)

[洛谷传送门](https://www.luogu.com.cn/problem/AT1218)	[AT传送门](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/1218)

### Solution

#### 考虑如何求出操作次数

有一个结论是：设原序列的下标分别是 $1,2,\cdots ,n$ ，那么最后序列的操作次数为原序列下标的逆序对数。

证明很显然，因为每一次操作都会增加一对逆序对。

#### 考虑如何达到最优

题目要求最后的序列先不递减再不递增，所以中间那个一定放最高的，然后往两边依次放。

那么现在只需要思考怎么让新序列的逆序对数最少

当放入一个数的时候，判断放左边和右边哪个产生的逆序对数少，贪心的选即可。

小细节：注意两个数相等的情况。

### Code

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=300010;
ll ans;
int n,l,r,c[N],h[N],p[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

inline int lowbit(int x){
    return x&-x;
}

inline void update(int x,int v){
    for(int i=x;i<=n;i+=lowbit(i))
        c[i]+=v;
}

inline int query(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i))
        res+=c[i];
    return res;
}

inline bool cmp(int a,int b){
    return h[a]>h[b];
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        h[i]=read(),p[i]=i;
    sort(p+1,p+n+1,cmp);
    for(int i=1,j;i<=n;){
        for(j=i;j<=n;j++){
            int k=query(p[j]); ans+=min(k,i-1-k);   
            if(h[p[j+1]]!=h[p[j]]) break;
        }
        for(;i<=j;i++) update(p[i],1);
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：Poncirus (赞：11)

# [たのしい家庭菜園](https://www.luogu.com.cn/problem/AT1218)

### Description

给定 $h_{1\sim n}$，求最少交换几次可以使得原序列 **不** 满足 $h_1\sim h_{i-1}$ 和 $h_{i+1}\sim n$ 中同时存在某个 $\geqslant h_i$ 的数。

### Solution

~~总感觉这题就思维难度与实现难度而言评不到紫，差不多蓝的亚子~~

看到交换等关键词就知道与逆序对有关，这里提供一个形象化的思路。

先思考如下特殊情况：$h$ 中没有重复元素。

假设 $h_x$ 是 $h$ 中的最小值。

那么，$h_x$ 不管在中间那个位置，两边都会有比它大的。

所以 $h_x$ 应该挪到序列的两端。具体是哪一端呢？移到不同的地方会不会对其他数带来不同的影响呢？

这就要根据 $x$ 离 $1$ 和 $n$ 的距离来判断了，因为不管 $h_x$ 移到哪一端，中间剩下的数排列顺序都是一样的，所以 $h_x$ 对中间的那些数造成的影响是一样的，自然是移到距离更近的一端更优。

我们把这个操作看做将 $h_x$ 从 $h$ 中删去，那么剩下的数又构成了一个新的问题。重复这个操作即可得到答案。

但我们不可能模拟这个过程计算。

所以我们有必要搞明白如下这件事：

假设进行到某一步时，当前的最小值为 $h_y$，那么就应该这么移动：

![图示](https://zebra-common-system-pre.oss-cn-shanghai.aliyuncs.com/bmdev/ca44a426-0e45-4513-b54c-14a08b3c9814.png)

所以 $h_y$ 往两边跳的过程，其实一共跳过的是 $h_y$ 左边或右边 $>h_y$ 的数的个数。

不过，这只是 $h$ 中元素不重复的情况，有重复的情况呢，其实同理。

如果按从左到右的顺序处理序列，当 $h_y$ 向左跳时，左边未归位的数中一定没有与 $h_y$ 相等的值。（因为从左向右处理，在处理 $h_y$ 之前已经把前面与 $h_y$ 相等的值挪好了，所以不用担心左边）

但是，如果 $h_y$ 要向右跳呢？右边可能有相等的数，所以要跳过的是 $\geqslant h_y$ 的数。

当然，如果你喜欢，也可以从右到左，那么此时 $h_y$ 向左就要跳过 $\geqslant h_y$ 的数，向右跳过 $>h_y$ 的所有数。

那，这题用树状数组维护一下不就出来了吗？

但是，我们考虑一种情况，以下是这种情况的最简形式：

```
5
2 2 1 1 2
```

按照我们刚刚的步骤，这一组数据应该像这样处理：

$\to2_{(1)}\ 2_{(2)}\ 1_{(3)}\ 1_{(4)}\ 2_{(5)}$

$\to h_y=1_{(3)}$

$\to1_{(3)}$ 向右挪至 $2_{(5)}$ 的位置，经历 $2$ 次交换操作，此时总交换次数 $ans=2$。

$\to 2_{(1)} \ 2_{(2)}\ 1_{(4)}\ 2_{(5)}\ 1_{(3)}$

$\to h_y=1_{(4)}$

$\to 1_{(4)}$ 向右挪至 $2_{(5)}$ 的位置，经历 $1$ 次交换操作，此时总交换次数 $ans=3$。

$\to 2_{(1)} \ 2_{(2)}\ 2_{(5)}\ 1_{(4)}\ 1_{(3)}$

$\to$ 操作完成，最终答案 $ans=3$。

但相信我们大家都能看出来，正确的交换次序是：

$\to2_{(1)}\ 2_{(2)}\ 1_{(3)}\ 1_{(4)}\ 2_{(5)}$

$\to h_y=1_{(4)}$

$\to1_{(4)}$ 向右挪至 $2_{(5)}$ 的位置，经历 $1$ 次交换操作，此时总交换次数 $ans=1$。

$\to 2_{(1)} \ 2_{(2)}\ 1_{(3)}\ 2_{(5)}\ 1_{(4)}$

$\to h_y=1_{(3)}$

$\to 1_{(3)}$ 向右挪至 $2_{(5)}$ 的位置，经历 $1$ 次交换操作，此时总交换次数 $ans=2$。

$\to 2_{(1)} \ 2_{(2)}\ 2_{(5)}\ 1_{(3)}\ 1_{(4)}$

$\to$ 操作完成，最终答案 $ans=2$。

咦？那么不能从左到右，只能从右到左咯？

当然不行，把刚刚的数据反过来输就可以 Hack 这种做法（

这说明了我们只能适当地在不同时机选择不同的选择次序，但是我们不难发现，最终都是要把位置更靠外的数往更外面的地方挪，比如上例中的 $1_{(4)}$ 就比 $1_{(3)}$ 更靠外（右），**处理次序比 $1_{(3)}$ 更优先**， 最终的位置也比 $1_{(3)}$  更靠外（右）。

而上面那条简单的规律，就帮我们免去了决定选择次序的痛苦。

因为按以上的规律，越靠外的数，处理次序更优先，所以当我们处理一个数 $h_y$ 时，$h_y$ 一定是当前序列中值最小的数中位置最靠外的，所以直接查询 $>h_y$ 的数的个数，就是 $h_y$ 要交换的次数。

### Code

树状数组和离散化相信各位都会吧。在这里我们用两个树状数组当做桶，分别维护当前 $h_y$ 左边和右边的所有值的个数。

不过有个坑点在于必须输出文末回车，不然会 WA。

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
const int maxn=3e5+5;
const int LEN=(1<<20);
int n,a[maxn];
int ans1,ans2,ans;
int Bit[2][maxn],Lsh[maxn];
inline int Lowbit(int x){return x & (-x);}
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void Update(int k,int x,int typ){
	for(int i=k;i<=n;i+=Lowbit(i))
		Bit[typ][i]+=x; 
	return; 
}
inline int Sum(int k,int typ){
	int ans=0;
	for(int i=k;i;i-=Lowbit(i))
		ans+=Bit[typ][i];
	return ans;
}
inline int nec(){
    static char buf[LEN],*p=buf,*e=buf;
    if(p==e){
        if((e=buf+fread(buf,1,LEN,stdin))==buf)return EOF;
        p=buf;
    }
    return *p++;
}
inline bool read(int&x){
    static char neg=0,c=nec();
    neg=0,x=0;
    while((c<'0'||c>'9')&&c!='-'){
        if(c==EOF)return 0;
        c=nec();
    }
    if(c=='-'){
        neg=1;
        c=nec();
    }
    do{x=x*10+c-'0';}while((c=nec())>='0');
    if(neg)x=-x;
    return 1;
}
signed main(){
	read(n);
	for(int i=1;i<=n;++i){
		read(a[i]);
		Lsh[i]=a[i];
	}
	std::sort(Lsh+1,Lsh+1+n);
	int cnt=std::unique(Lsh+1,Lsh+1+n)-Lsh-1;
	for(int i=1;i<=n;++i){
		a[i]=std::lower_bound(Lsh+1,Lsh+cnt+1,a[i])-Lsh;
		Update(a[i],1,1);
	}
	for(int i=1;i<=n;++i){
		Update(a[i],-1,1);
		ans1=n-i-Sum(a[i],1);
        Update(a[i],1,0);
        ans2=i-Sum(a[i],0);
		ans+=min(ans1,ans2);
	}
	printf("%lld\n",ans);
	return 0;
}
```

**end.**



---

## 作者：是个妹子啦 (赞：3)

前置知识：对于一个序列，只能相邻两两交换时，排成有序序列的最小次数为逆序对的个数。

假如我们知道了每个数在序列中的排名，且确定了最终的某个可能最优解时（假单峰函数），我们把下标重新赋给每个数，这时的最小次数就是下标的逆序对数。

证明考虑微扰相邻。
假如现在改变最优解，且之变动一个数 $x$ 时：
这时 $x$ 有两种可能，一最后在最大值的左侧，二最后在右侧。且我们又能发现无论怎么变动，x对于比它权值小的数大小情况都不会改变，所以只考虑比 $x$ 大的数。
这时我们发现，在左侧时，$x$ 与 $x$ 左侧的权值比它大的数构成逆序对；在右侧时，$x$ 与 $x$ 右侧权值比它大的数构成逆序对。
所以综上，应对每个数统计左侧大的数和右侧大的数，取个数最小值。

代码就看楼上的吧

---

## 作者：PCCP (赞：2)

~~感觉只有绿或蓝吧~~。

## 思路

考虑要我们构造的是单峰数列，那大的肯定在中间，小的在两边。求最小代价，发现按大的放中间求还要分奇偶，所以考虑小的放两边。从小到大移动，向某一边移动，那这个方向上有几个比他大的就要交换多少次。而且可以发现小的移过去后不会影响后面移过来的贡献，所以求出每一个数他左右两边比他大的数的数量，取最优的即可。

可以使用后缀和及树状数组维护，时间复杂度 $ O(n\log_2{n}) $。

## 代码：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
const int N=3e5+10;
int n,a[N],sum[N],c[N];
long long ans;
vector<int> q;
int get(int x){
	return lower_bound(q.begin(),q.end(),x)-q.begin();
}
int lowbit(int x){
	return x&-x;
}
void add(int x){
	while(x<=(int)q.size()){
		++c[x];
		x+=lowbit(x);
	}
}
int ask(int x){
	int res=0;
	while(x){
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		q.push_back(a[i]);
	}
	sort(q.begin(),q.end());
	q.erase(unique(q.begin(),q.end()),q.end());
	for(int i=1;i<=n;i++)
		++sum[get(a[i])];
	for(int i=q.size()-1;i>=0;i--)
		sum[i]+=sum[i+1];
	for(int i=1;i<=n;i++){
		int l=ask(q.size())-ask(get(a[i])+1);
		int r=sum[get(a[i])+1]-l;
		ans+=min(l,r);
		add(get(a[i])+1);
	}
	printf("%lld\n",ans);
}
```


---

## 作者：_zhy (赞：1)

[Link](https://www.luogu.com.cn/problem/AT1218)。

### 题目大意

给定一个序列，已知序列中每个数的值，你可以交换相邻两数的值。

最终，你要使得整个序列呈一个山峰型，即序列的前一部分为**不降**序列，后一部分为**不升**序列，求这个最小的交换次数。

### 思路

由于我们需要构造一个山峰型，所以越大的数应该在越中间。反之，越小的数应该在越旁边。

所以，我们就需要将中间的较小的数向旁边移动，那具体该怎样移动呢？

我们认真观察一下题目：**交换相邻两数**。相信大家都学过冒泡排序吧，所以大家应该都知道：将一个数反复同相邻数交换，是不会改变其他数的相对位置的。

因此，在这道题中，将位于中间部分的较小数向旁边移动时并不会改变其他数的相对位置，也就是说将 $a_x$ 向旁边交换，若交换前 $a_i$ 在 $a_j$ 左边，则在 $a_x$ 换完后 $a_i$ 依旧在 $a_j$ 左边（右边同理）。

所以我们将较小的数向旁边移动即可，那么什么是较小的数呢？

其实较小的数就是那种在它的左边和右边**都有**比它**大**的数，因为我们需要山峰型，所以这样的数一定还要往旁边移动。

那么每个数应该向哪边移动呢？

其实既可以向左，又可以向右，因为不影响其他数相对位置。但为了保证答案是最小的，所以往哪边移动的交换次数少，就往哪边移动。

可是我们怎么知道具体的交换次数呢？

刚才说了，要保证左边**或**右边**没有**大于此数的数，因此交换次数就是左边（或右边）比当前数大的数的个数。

万一在交换完成前出现小于等于当前数的数呢？

其实这种情况并不会发生，因为比它小的数已经同它交换过了。

那我们如何求到左边（右边）有多少数比当前数大呢？

这其实大家都能想到了，就是从前往后（从后往前）的逆序对数即可，所以维护树状数组即可~~（你要写归并排序或树链剖分我也不介意，但这里就不讲了）~~。

---

## 作者：yzq_yzq (赞：1)

### [题面](https://www.luogu.com.cn/problem/AT1218)


**题意：**

求交换相邻的数，将序列变成升序再降序的序列的次数。（操作完后序列就像[P1091 [NOIP2004 提高组] 合唱队形](https://www.luogu.com.cn/problem/P1091)）

**第一眼就可以看出这道题与逆序对有关，而逆序对最高效的算法就是树状数组了，但与逆序对有点区别：**

### 关于树状数组求逆序对：

```cpp
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        add(a[i], 1);
        ans += i - sum(a[i]);
    }
    //树状数组存小于等于i的数个数的前缀和
    //每次i-sum(a[i])就是已经插入数的总数减去小于等于a[i]的个数就是大于a[i]的个数
    
```

他是选一个点把整体分成两个区间，计算两个区间的逆序对之和的最小值。

# 55~70 PTS

枚举中点，分成两个区间，分别计算两个区间的逆序对之和，累加取min，写得好能有55~70分

伪代码：

```cpp
for(int i=1;i<=n;i++){
   求1到i的逆序对个数
   求i到n的逆序对个数
   ans=min(ans,sum1+sum2);
}                  
```


# 100 PTS

我们可以建两个树状数组，分别存储左区间和右区间，操作每个点看是放在哪边，每次放在哪边花费更小就选哪边，累加每次的答案，就可以求出总的答案了。

注意：在做的时候要把值相等的数一起做，不然会把相等的也累进去 **（因为前面还没删这些与他相等的点，会把相等的也加进去）**

具体代码如下：

**蒟蒻のcode：**

```cpp
#include <bits/stdc++.h>
#define lowbit(x) x & -x
using namespace std;
long long n, ans, t1[300030], t2[300300];
struct ex {
    long long id, w;//id是原序列中他的位置
} a[300003];
int cmp(ex a, ex b) { return a.w < b.w; }//从小到大排序
void add(long long x, long long y) {
    for (long long i = x; i <= n; i += lowbit(i)) t1[i] += y;
    for (long long i = x; i; i -= lowbit(i)) t2[i] += y;
}
long long sum(long long x) {
    long long ans1 = 0, ans2 = 0;
    for (int i = x; i; i -= lowbit(i)) ans1 += t1[i];
    for (int i = x; i <= n; i += lowbit(i)) ans2 += t2[i];
    return min(ans1, ans2);//取较小的一个
}
int main() {
    scanf("%lld", &n);
    for (long long i = 1; i <= n; i++) scanf("%lld", &a[i].w), a[i].id = i, add(i, 1);
    //初始化：第i个点有一棵草
    sort(a + 1, a + 1 + n, cmp);
    //排序，确保每次都没有比目前的草更小的草，这样逆序对的值才是对的
    for (long long i = 1, j = 1; i <= n; i = j) {
        for (j = i; a[j].w == a[i].w; j++) add(a[j].id, -1);
        for (j = i; a[j].w == a[i].w; j++) ans += sum(a[j].id);
        //将相等的点同时操作，因为相等的点如果不同时删就会把与他相等的点也加在答案里
    }
    cout << ans;
    return 0;
}
```

完


---

## 作者：luqyou (赞：1)

# 前言
这题是我同学考试的题目，于是我就拿来做了一下，~~花了我8个小时~~，我果然还是太蒻了

# 还是题意
题意特容易理解：

给你一个数组，你每次可以交换两个相邻的位置，问你要交换多少次才能使得这个数组变成先上升后下降的形式。

# 思路

不难想到贪心，做法肯定是每次移动至左边或者右边。

那么我们是不是就可以求出**移到左边和右边的费用**了？然后每次都对费用取**最小值**即可。

然后移到某一边的费用大概就是比它高的个数（因为这些要被移动出来），那这个我们用**两次树状数组**求即可。

代码还算比较短。

# $code$

```cpp

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int n, a[300001], f[300001], g[300001], tr[300001];
int b[300001];
ll ans;
void Add(int x, int y) {//树状数组
	for (; x <= n; x += x & (-x)) tr[x] += y;
}
int Ask(int x) {
	int re=0;
	for (; x; x -= x & (-x)) re += tr[x];
	return re;
}

int main() {
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d", &a[i]);
	}
	memcpy(b,a,sizeof(b));
	sort(b+1,b+n+1);//离散化，不要浪费空间
	int nn=unique(b+1,b+n+1)-b-1;
	for (int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+nn+1,a[i])-b;
	for (int i=1;i<=n;i++) {
		f[i]=i-1-Ask(a[i]);
		Add(a[i], 1);
	}
	for (int i = 1; i <= n; i++) Add(a[i], -1);
	for (int i = n; i >= 1; i--){
		g[i] = n - i - Ask(a[i]);
		Add(a[i], 1);
	}
	for (int i = 1; i <= n; i++)
		ans += min(f[i], g[i]);
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：iPhoneSX (赞：0)

## 前言
第二篇题解的写法非常简洁，不用离散化而且只用一个树状数组。但本蒟蒻刚开始没想明白为什么是对的，故详细的写一下。
## 题解
大体思路比较好想，就是贪心，假设当前序列中最小的数为 $h_x$，如果 $h_x$ 不在最边上，它的两边一定有比它高的。所以必须把它移到最左端或最右端。移到哪一段取决于左边和右边哪个产生的逆序对数少，重复此过程即可。

常见的逆序对求法是对值域上使用树状数组，但在这里也可以在下标上使用树状数组。先把所有数按草的高度**从大到小**排序，然后每遍历到一个数，就把它**在原数组中的位置**在树状数组上加  $1$。

假设排完序，现在处理第 $i$ 个数。比它大的数有 $i-1$ 个，都插入了树状数组中。此时用树状数组查询它**在原数组中的位置**的前缀和，就可以得到在原数组中它的**前面**有几个比它大的数，设这个数为 $k$。那么它的**后面**比它大的数的个数就是 $i-1-k$。

如果有高度相等的数，在排序后的数组中一定是相邻的，它们需要一起处理。考虑第一篇题解中给的样例：
```cpp
5
2 2 1 1 2
``````
中间的两个 $1$ 都要移到右边去，如果位置 $3$ 上的 $1$ 先移动了，它要跨过两个数。而位置 $4$ 的先移动的话，两个 $1$ 都只需要跨过 $1$ 个数。也就是说，两数高度相同时，一定要让**相对位置更靠外的先移动**才会更优。即保证没有数在移动时会跨过和自己高度相同的数。对应到代码中就是如果有多个相同的数，要先把多个相同的数对答案的贡献都算出来，再挨个把这些数加进树状数组。

代码如下（可能和第二篇题解很像，拜谢大佬提供思路）：
```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
#define ll long long
#define int long long
#define DBG(x) cout << #x << "=" << x << endl
#define inf 0x3f3f3f3f
#define mod 1000000007
#define N 300005
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    ll t = 1;
    char ch;
    ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            t = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= t;
}
template <typename T, typename... Args>
void read(T& first, Args&... args) {
    read(first);
    read(args...);
}
template <typename T>
void write(T y) {
    T x = y;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename T, typename... Ts>
void write(T arg, Ts... args) {
    write(arg);
    if (sizeof...(args) != 0) {
        putchar(' ');
        write(args...);
    }
}
int n,ans,c[N],h[N],p[N];
bool cmp(int x,int y){
	return h[x]>h[y];
}
int lowbit(int x){
	return x&(-x);
}
void update(int x,int v){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=v;
	}
}
int query(int x){
	int sum=0;
	for(int i=x;i;i-=lowbit(i)){
		sum=sum+c[i];
	}
	return sum;
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(h[i]);
		p[i]=i;
	}
	sort(p+1,p+n+1,cmp);
	for(int i=1,j;i<=n;){
		for(j=i;j<=n;j++){
			int k=query(p[j]);
			ans=ans+min(k,i-1-k);
			if(h[p[j+1]]!=h[p[j]]){
				break;
			}
		}
		for(;i<=j;i++){
			update(p[i],1);
		}
	}
	write(ans);
	putchar('\n');
    return 0;
}
````````````

---

## 作者：封禁用户 (赞：0)

这道题的思路并不难想，用树状数组和贪心就可以解决这道题。

不难发现：如果一个序列的下标是 $1,2,⋯ ,n$，且只能相邻两个元素两两交换，那么将原序列变为有序序列的操作次数为原序列下标的逆序对数。

证明过程可以参考[这位大佬的题解](https://www.luogu.com.cn/article/citgpgh9)。

考虑构造单峰数列，那么考虑将大的数放中间，小的数依次往两边放。题目要求求最小代价，显然从小到大移动代价更小。当一个数向某一边移动时，最少交换次数就是这个方向上比这个数大的数的个数。

其次，我们发现当把小的数转移时不会影响后面的数转移，所以考虑用树状数组维护逆序对，用贪心去最小代价即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5;
int n,a[N],id[N],tree[N],ans;
int lowbit(int x){
	return x&-x;
}
void update(int pos,int v){
	while(pos<=n){
		tree[pos]+=v;
		pos+=lowbit(pos);
	}
}
int sum(int pos){
	int ans=0;
	while(pos>0){
		ans+=tree[pos];
		pos-=lowbit(pos);
	}
	return ans;
}
bool cmp(int x,int y){
	return a[x]>a[y];
}
signed main(){
	ios::sync_with_stdio(NULL);
	cin.tie(NULL);cout.tie(NULL);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		id[i]=i;
	}
	sort(id+1,id+n+1,cmp);
	for(int i=1,j;i<=n;){
		for(j=i;j<=n;j++){
			int q=sum(id[j]);
			ans+=min(q,i-1-q);
			if(a[id[j+1]]!=a[id[j]])
				break;
		}
		for(;i<=j;i++)
			update(id[i],1);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：菲斯斯夫斯基 (赞：0)

## AT_joisc2014_b たのしい家庭菜園 题解

**前言**

第一次在考场上切紫题，~~虽然我感觉这题远远没有紫题的难度~~。

**题意**

每次可以交换一个序列中的**相邻**元素，使得存在某个 $k\in[1,n]$，对于任意 $1\le i<k$，有 $a_i\le a_{i+1}$；且对于任意 $k\le i<n$，有 $a_i\ge a_{i+1}$。

求最少的交换次数。

**思路**

注意到序列两边的数都是最小的，所以我们不妨先对序列中的**最小**的数进行思考。

对于当前的**最小**的数，可以选择往**左移**或**右移**，需要的操作次数即为左边和右边数的个数。

考虑完最小的，就应该考虑**次小**了。同样可以左移或右移，但是如果有比自己小的数，就应当忽略，因为最小的数已经处理过了。

同样的，我们可以将这个结论推广到所有的数上，对于第 $i$ 个数 $a_i$，若左边有 $x$ 个数**大于** $a_i$，右边有 $y$ 个数**大于** $a_i$。那么该数对答案的贡献应为 $\min\{x,y\}$。

接下来证明答案的正确性。

当我们对序列中的一个数**只**进行左移或右移时，它并不会打乱除该数之外序列的顺序。当它移到**最左端**或**最右端**，它不会对答案再次影响，所以不需要再考虑它了。

注意应当是**大于**，而不是大于等于，因为交换两个相同的数是不优的，以及小于当前数的会在移动此数前移动过了。

回到结论上，还是比较明显的单点修改、区间查询问题，所以可以用**树状数组**或**线段树**来维护。当然，因为 $a_i$ 较大，所以也需要使用**离散化**。

题解似乎写得有点绕，但希望你能够理解。

**代码**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
int n,ans;
int a[N],f[N<<2],c[N],b[N];
void add(int k,int l,int r,int x,int y)
{
	if(l>x||r<x)return ;
	if(l==r&&l==x)
	{
		f[k]+=y;
		return ;
	}
	int mid=(l+r)/2;
	add(k*2,l,mid,x,y);
	add(k*2+1,mid+1,r,x,y);
	f[k]=f[k*2]+f[k*2+1];
}
int ask(int k,int l,int r,int x,int y)
{
	if(l>y||r<x)return 0;
	if(x<=l&&r<=y)return f[k];
	int mid=(l+r)/2;	
	return ask(k*2,l,mid,x,y)+ask(k*2+1,mid+1,r,x,y);
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]),b[i]=a[i];
	sort(b+1,b+1+n);
	int m=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;i++)
		a[i]=lower_bound(b+1,b+1+m,a[i])-b;//离散化
	for(int i=1;i<=n;i++)
	{
		add(1,1,m,a[i],1);//记录当前的数
		c[i]=ask(1,1,m,a[i]+1,m);//查询大于当前的数的个数
	}
	memset(f,0,sizeof(f));
	for(int i=n;i>=1;i--)//倒着再来一遍，同理
	{
		add(1,1,m,a[i],1);
		c[i]=min(c[i],ask(1,1,m,a[i]+1,m));
		ans+=c[i];
	}
	cout<<ans<<endl;
	return 0;
}
```

如果你有什么不明白的地方，欢迎在讨论区回复我。我会及时的做出回复和修改，谢谢。

---

## 作者：zhou_ziyi (赞：0)

## Description

有一个数组，你每次可以交换两个相邻的位置，问你要交换多少次才能使得这个数组变成单峰序列。
## Solution

我们不难发现最终得到的是一个单峰序列，所以中间那个草一定放最高的，然后往两边依次放叫矮的。

由于每一次操作会增加一组逆序对，所以只需要思考如何让最终序列的逆序对数最少。

我们可以正反跑两次，放那边的逆序对最少，就是每一个草的贡献，就去那边，最后求和即可。

## Code
```cpp
#include <cstdio>
#include <algorithm>
#define int long long
#define lowbit(x) (x & (-x))
using namespace std;
const int MAXN = 3e5 + 5, INF = 1e18;
int n;
int a[MAXN];
int aux[MAXN];
int c[MAXN];
void update(int x, int k) {
	while (x <= n) {
		c[x] += k;
		x += lowbit(x);
	} 
}
int query(int x) {
	int res = 0;
	while (x > 0) {
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}
int ans[MAXN];
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]), aux[i] = a[i], ans[i] = INF;
	sort(aux + 1, aux + n + 1);
	int res = unique(aux + 1, aux + n + 1) - aux - 1;
	for (int i = 1; i <= n; i++)
		a[i] = lower_bound(aux + 1, aux + res + 1, a[i]) - aux;
	for (int i = 1; i <= n; i++)
		ans[i] = min(ans[i], i - 1 - query(a[i])), update(a[i], 1);
	for (int i = 1; i <= n; i++)
		c[i] = 0;
	for (int i = n; i >= 1; i--)
		ans[i] = min(ans[i], n - i - query(a[i])), update(a[i], 1);
	res = 0;
	for (int i = 1; i <= n; i++)
		res += ans[i];
	printf("%lld", res);
	return 0;
}
```

---

## 作者：WeLikeStudying (赞：0)

- 普及水平的作者误点了提交题解键，感到十分抱歉，希望不要 ban 掉我的博客 QwQ。

**[题意](https://www.luogu.com.cn/problem/AT1218)**
- IOI 草（？？原文确实如此）排成一列长了很多（$n$ 个）。
- IOI 草只要满足以下任一条件就不会枯萎。
- - 在那草的左侧，不存在比那草高的草。
- - 在（那）草的右侧，不存在比（那）草高的草。
- （要求）很好地排列 IOI 草，使所有的 IOI 草不枯萎。
- 请计算最少要进行多少次排序。

**分析**
- 你发现你需要排成一个非严格单峰序列。
- 你尝试发现一些结论，比如从寻找分割点在两边排序之类的，却无果。
- 为什么？因为中间的具体位置没有确定，但是两边却是确定的，应该先从两边开始寻找。
- 我们可以想到一个简单的贪心，（从外到里）枚举最小的数，判断它往哪里移动更优。
- 因为它对后面的结果没有影响，所以这个贪心是正确的。
- 因此你发现我们需要计算的不过是每个点左边或者右边大于它的数的个数（这是移动的步数），因此用树状数组即可完成。
- 实现细节：离散化，文末回车，[代码](https://www.luogu.com.cn/paste/kfaf8ryw)。

---

## 作者：Others (赞：0)

这题的简化题意就是移动若干次相邻的数，使得数列满足先非严格递增再非严格递减。

首先会有一个很~~常规~~的思路，枚举分割点，看左边和右边的逆序对数（也就是要交换的次数），单数这样有个问题，just like：

8 7 2 5 4 6 这一组，它就不符合，它只需要将 2 和 6 左移两格，而 8 7 并不用移动，这就只能换一种方法了。

我们思考一下，最后的结果，最小的一定在左边或右边，所以就看每个数移几次就行了，最暴力的方法 $O(n^3)$，必爆，先 $O(n\log n)$ 的复杂度处理出从小到大的位置可以 $O(n^2)$，也要炸，于是我们考虑它要移的条件。

首先我们从小移，这时所有数都是大于它的，所以就考虑左边和右边哪个更近，然后是第二小，因为最小的已经被移走了，它要移也不受比它小的影响，所以移的次数就是比它大的数的个数，当然左边和右边要取最小值，这样的复杂度是 $O(n^2)$，再用个树状数组维护值域就是 $O(n\log n)$ 了，没有问题，最后，记得离散化和开 `long long`。

*不开 long long 见祖宗*

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;
int n,a[100005],bit[2][100005],ans;
void add(int p,int x){
	while(x<=100000){
		bit[p][x]++;
		x+=lowbit(x);
	}
}
void del(int p,int x){
	while(x<=100000){
		bit[p][x]--;
		x+=lowbit(x);
	}
}
int get(int p,int x){
	int tot=0;
	while(x){
		tot+=bit[p][x];
		x-=lowbit(x);
	}
	return tot;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		add(0,a[i]);
	}
	for(int i=1;i<=n;i++){
		ans+=min(get(1,100000)-get(1,a[i]),get(0,100000)-get(0,a[i]));
		add(1,a[i]);
		del(0,a[i]);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：pomelo_nene (赞：0)

我们发现序列合法，当且仅当能够找到一个$i \in [1,n]$使得每一个$j$和$k$满足$a_j\leq a_i(1 \leq j<i)$并且$a_i \leq a_k(i<k \leq n)$，于是我们想到构造最终序列。

构造最终序列应该是对于某一个$i$，它的左边和右边都比它小。我们考虑每次添加一个IOI草。有可能比它小，不管。如果比它大，只有可能放在左边或者右边，因为两个操作不会影响已经摆好了的IOI草，所以说这其实只是一个求逆序对的过程。并且两个操作互相不影响，所以每一个IOI草的贡献是两个操作的最小值

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<queue>
using namespace std;
long long read()
{
	long long x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
long long tree[300005],a[300005],b[300005],tmp[300005],n;
long long lowbit(long long x){return x&(-x);}
void modify(long long situ,long long x){while(situ<=n)	tree[situ]+=x,situ+=lowbit(situ);}
long long query(long long situ)
{
	long long ans=0;
	while(situ)	ans+=tree[situ],situ-=lowbit(situ);
	return ans;
}
int main(){
	n=read();
	for(long long i=1;i<=n;++i)	a[i]=b[i]=read();
	sort(b+1,b+1+n);
	long long len=unique(b+1,b+1+n)-b-1,ans=0;
	for(long long i=1;i<=n;++i)	a[i]=lower_bound(b+1,b+1+n,a[i])-b;//离散化
	for(long long i=1;i<=n;++i)	tmp[i]=i-1-query(a[i]),modify(a[i],1);//这里其实就是一个逆序对过程，每次计算，存在数组里面，放在左边的操作
	memset(tree,0,sizeof tree);//注意清空
	for(long long i=n;i;--i)	ans+=min(tmp[i],n-i-query(a[i])),modify(a[i],1);//放在右边的操作
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：jjy2023 (赞：0)

# AT_joisc2014_b たのしい家庭菜園
## Solution：
考虑差分做法。考虑正着做时若想要将任意 $a_{i+1}<a_i$ 时需要的步骤，倒着做时若想要将任意 $a_{i+1}>a_i$ 时需要的步骤。令正着操作时需要的次数为 $s1$，倒着操作时需要的次数为 $s2$，则最后若想要其满足要求，操作次数就是： 
$$\min_{1\rightarrow n}(\max(s1_i,s2_i))$$
所以先做差分，再用 `for` 循环跑一遍即可。
## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[200005],b[200005],s1[200005],s2[200005],ans=1e18;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=a[i]-a[i-1];
	}
	for(int i=1;i<=n;i++)
	{
		if(b[i]>0) s1[i]=s1[i-1];
		else s1[i]=s1[i-1]-b[i]+1;
	}
	for(int i=n;i>=1;i--)
	{
		if(b[i]<0) s2[i]=s2[i+1];
		else s2[i]=s2[i+1]+b[i]+1;
	}
	for(int i=1;i<=n;i++)
		if(max(s1[i],s2[i+1])<ans) ans=max(s1[i],s2[i+1]);
	cout<<ans;
	return 0;
}
```

---

