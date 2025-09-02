# [JOI 2018 Final] 美术展览 / Art Exhibition

## 题目背景

JOI 共和国将举行一个艺术展。许多来自全国各地的艺术作品将在艺术展中展出。

## 题目描述

有 $N$ 件艺术品是展览的候选作品。艺术品编号从 $1$ 到  $N$。每件艺术品都定义了两个整数：尺寸和价值。艺术品 $i$（$1 \leq i \leq N$）的尺寸为 $A_i$，艺术品 $i$ 的价值为 $B_i$。  
在艺术展中，至少会选择并展示一件艺术品。由于展厅足够大，可以将 $N$ 件作品全部展示。但是，由于 JOI 共和国人的审美意识，我们希望展览选择的艺术品，使展出的艺术品尺寸之间的差异不会太大。另一方面，我们想展示许多具有高价值的艺术品。我们决定按照以下规则选择展览的艺术品：  
- 在选择的展览作品中，$A_{max}$ 为所选作品中最大的尺寸，$A_{min}$ 为所选作品中最小的尺寸。设 $S$ 为所选艺术品的总价值。  
- 然后，我们想要最大化 $S−(A_{max}−A_{min})$。  
现给定展览的艺术品候选数量，以及每件艺术品的尺寸和价值，请编写一个程序来计算 $S−(A_{max}−A_{min})$ 的最大值。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$2 \leq N \leq 5×10^5$，$1 \leq A_i \leq 10^{15}$（$1 \leq i \leq N$），$1 \leq B_i \leq 10^9$（$1 \leq i \leq N$）。  
- Subtask $1$（$10$ points）：$N \leq 16$。  
- Subtask $1$（$20$ points）：$N \leq 300$。  
- Subtask $2$（$20$ points）：$N \leq 5000$。  
- Subtask $3$（$50$ points）：没有额外的限制。  
#### 样例说明  
**对于样例 $1$**：本次展览共有 $3$ 幅作品候选。每件艺术品的尺寸和价值如下：  
- 艺术品 $1$ 的尺寸为 $2$，价值为 $3$。  
- 艺术品 $2$ 的尺寸为 $11$，价值为 $2$。  
- 艺术品 $3$ 的尺寸为 $4$，价值为 $5$。  

在这种情况下，如果我们为展览选择艺术品 $1$ 和艺术品 $3$，我们有 $S−(A_{max}−A_{min})$  如下：  
- 在选择的艺术品中，艺术品 $3$ 的尺寸最大。因此，$A_{max} = 4$。  
- 在所选的艺术品中，艺术品 $1$ 的尺寸最小。因此，$A_{min} = 2$。  
- 所选艺术品的总价值为 $3+5=8$。因此，$S=8$。  
由于 $S−(A_{max}−A_{min})$ 不能大于 $7$，因此输出 $6$。
#### 题目说明：  
来源于 The 17th Japanese Olympiad in Informatics (JOI 2017/2018) Final Round 的 [T2：Art Exhibition](https://www.ioi-jp.org/joi/2017/2018-ho/2018-ho-t2-en.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
3
2 3
11 2
4 5```

### 输出

```
6```

## 样例 #2

### 输入

```
6
4 1
1 5
10 3
9 1
4 2
5 3```

### 输出

```
7```

## 样例 #3

### 输入

```
15 
1543361732 260774320
2089759661 257198921
1555665663 389548466
4133306295 296394520
2596448427 301103944
1701413087 274491541
2347488426 912791996
2133012079 444074242
2659886224 656957044
1345396764 259870638
2671164286 233246973
2791812672 585862344
2996614635 91065315
971304780 488995617
1523452673 988137562```

### 输出

```
4232545716```

# 题解

## 作者：Aw顿顿 (赞：5)

## 题目分析

乍一看，好像有很多个变量，要在这些变量中得到答案没有那么直观。但是如果我们关注题目“令 $S-(A_{\max}-A_{\min})$ 最大” 这一要求，我们不难发现，当 $A_{\max}$ 和 $A_{\min}$ 这一范围确定之后，我们要尽可能把这一范围内的所有展品全部带走，这样才能保证 $S$ 尽可能大，从而保证在 $(A_{\max}-A_{\min})$ 确定的情况下整体尽可能大。

那我们是不是应该要枚举 $\max$ 和 $\min$ 值呢？实际上这种思路是可行的，在 $O(n\log n)$ 排序使得价值按序排列之后，枚举复杂度达到了 $O(n^2)$ 级别，这样的时间复杂度还不够优秀。

所以我们考虑只枚举 $\max$，在确定一个 $A_i$ 作为最小值之后，我们考虑把这个状态转移到下一个数，试图找出他们的关系。在从 $A_i$ 转化到 $A_{i+1}$ 之后，我们所求的目标值的变化为 $B_{i-1}-(A_i-A_{i+1})$，这应该是容易理解的。而实际上如果我们要连贯地将状态进行转移以方便枚举，我们就可以进行一步预处理，令：

$$f_i=B_i-(A_i-A_{i+1})$$

这样我们就可以在常数时间内实现状态的转移，鉴于复杂度瓶颈在于排序部分的 $O(n\log n)$，而这个复杂度已经足以通过本题，于是不继续深入考量。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct num{
	int sz,val;
	bool operator <(const num &temp)const{
		return sz<temp.sz;
	}
}a[500005];
int n,f[500005],ans,mx;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i].sz>>a[i].val;
	sort(a+1,a+n+1);
	for(int i=1;i<n;i++)
		f[i]=a[i].val-a[i+1].sz+a[i].sz;
	for(int i=1;i<=n;i++){
		int t=a[i].val;
		ans=max(ans,t+mx);
		mx=max(mx+f[i],(long long)0);
	}cout<<ans<<endl;
	return 0;
 } 
```

---

## 作者：7KByte (赞：5)

对 $A$ 排序，然后写成前缀和的形式，即我们需要使得 $Sum_i-Sum_{j-1}-A_i+A_j$ 最大。

拆成 $Sum_i-A_i$ 和 $A_j-Sum_{j-1}$ 两部分，扫一遍即可，时间复杂度 $\mathcal{O}(N\log N)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
using namespace std;
typedef long long ll;
int n;ll s[N];
struct node{
	ll a,b;bool operator<(const node o)const{return a<o.a;}
}a[N];
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%lld%lld",&a[i].a,&a[i].b);
	sort(a + 1, a + n + 1);
	rep(i,1,n)s[i] = s[i - 1] + a[i].b;
	ll cur, ans;
	cur = ans = 0xcfcfcfcfcfcfcfcfLL;
	rep(i,1,n){
		cur = max(cur,a[i].a - s[i - 1]);
		ans = max(ans,s[i] - a[i].a + cur);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Da_un (赞：1)

### [题目大意](https://www.luogu.com.cn/problem/P7667)

## 思路
1.  对于其中一部分数据，完全可以用打暴力的方法来解决，可这毕竟是练习题，还是锻炼思维力争满分最好。

1.  对于所有数据，因为题目求的是 $S-(A_{max}-A_{min})$ 的最大值，所以我们应该尽可能的多选商品，并且尽可能的在使 $S$ 最大的情况下使 ($A_{max}-A_{min}$) 最小。所以我们可以对结构体进行排序使得尺寸越小的商品越靠前，当尺寸相同时，价值越大越靠前，并且我们还需要记录当时所选商品的价值，我们可以用前缀和来实现这一功能，这样的话，我们就确保了最优解一定会在前缀和的运算中，最后，我们从 $1$ 枚举到 $N$，对于每一次枚举，我们先求出这一次枚举的最大的 $S$，然后加上之前的前缀和即为此时最大的 $S$，因为 $A_{min}$ 已经包含其中了，所以用此时最大的 $S-A_{max}$ 即为此时的最优解，所以枚举完之后即可得到最后答案。


看数据范围，别忘了开 long long。

## code
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define maxn 500010
using namespace std;
inline ll read()
{
	ll s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') w=-1;
		ch=getchar();
	} 
	while(ch>='0'&&ch<='9'){
		s=s*10+ch-'0';
		ch=getchar();
	}
	return s*w;
}//快读
ll N;
struct node{
	ll a;
	ll b;
}f[maxn];
bool cmp(node x,node y)
{
	if(x.a!=y.a) return x.a<y.a;
	return x.b>y.b;
}//排序
ll sum[maxn];
ll t,ans;
int main()
{
	N=read();
	for(int i=1;i<=N;i++)
		f[i].a=read(),f[i].b=read();
	sort(f+1,f+1+N,cmp);
	for(int i=1;i<=N;i++)
		sum[i]=sum[i-1]+f[i].b;//预处理出每一次价值
	for(int i=1;i<=N;i++){
		t=max(t,f[i].a-sum[i-1]);//这一次的S
		ans=max(ans,t+sum[i]-f[i].a);//算出此时最大的S-此时最大的a，求出此时最优解
	}
	printf("%lld",ans);
	return 0;
}
```
完结撒花~~


---

## 作者：CPPfive (赞：1)

## 题目分析
题目要求我们最大化 $S-(A_{max}-A_{min})$ 的值，由于所有物品的价值都为正，因此在不影响 $A_{max}$ 和 $A_{min}$ 的情况下，物品取得越多越好，即当 $A_{max}$ 与 $A_{min}$ 确定后，所有尺寸在二者之间的物品都应该被选择。

因此，我们对物品根据尺寸排序，这样我们就可以通过枚举最大和最小的尺寸得到答案，复杂度为 $\mathcal{O}(n^{2})$。

考虑优化。当我们确定某一个 $A_{max}$ 后，把 $A_{min}$ 从第 $i$ 个物品转移到 $i-1$ 个物品，$S-(A_{max}-A_{min})$ 的值增加了 $B_{i-1}-A_{i}+A_{i-1}$。

因此令 $Diff_{i}=B_{i}-A_{i+1}+A_{i}$，可以预处理出 $Diff$ 数组。此时对于 $A_{max}$ 和 $A_{min}$，就有：
$$S-(A_{max}-A_{min})=\sum\limits_{i=min}^{max-1}Diff_{i}+B_{max}$$

所以对于一个确定的 $A_{max}$，我们只需要让 $Diff_{min}$ 到 $Diff_{max-1}$ 的和最大即可。实际实现中，可以用上一个 $A_{max}$ 对应的 $A_{min}$ 来在常数时间里转移。由于需要排序，所以总的复杂度是 $\mathcal{O}(n\log{n})$。

## Code
```
//洛谷P7667 

#include <bits/stdc++.h>
using namespace std;
#define cin std::ios::sync_with_stdio(false);cin//输入优化 
const int MAXN=500050;
typedef long long LL;
struct work{
	LL size;int value;
	bool operator < (const work &temp) const{
		return size<temp.size;
	}
}dat[MAXN];
LL N,Diff[MAXN],ans,temp_max;

int main()
{
	cin >> N;
	for(int i=1;i<=N;i++){
		cin >> dat[i].size >> dat[i].value;
	}
	sort(dat+1,dat+N+1);
	for(int i=1;i<N;i++){
		Diff[i]=dat[i].value-dat[i+1].size+dat[i].size;
	}
	for(int i=1;i<=N;i++){
		LL temp=dat[i].value;
		ans=max(ans,temp+temp_max);//更新答案 
		temp_max=max(temp_max+Diff[i],(LL)0);//更新Diff和的最大值 
	}
	printf("%lld",ans);
 } 
```


---

## 作者：Avocadooo (赞：0)

我们想要最大化 $ S-(A_{\max}-A_{\min}) $ 的值，优先考虑将所有的展品按 $ A $ 值（即尺寸）从小到大排序。

显然，因为 $ B_i \geq 1 $，所以现在我们选择其中的一些展品，那么选择的一定为**排序后一个连续的区间中的所有展品**，不存在其中部分展品不选的可能。即（$ [L^{\prime},R^{\prime}] \in [L,R] $）：

$$ \left(\sum\limits_{i=L}^{R}B_{i} \right)-A_{R}+A_{L}>\left(\sum\limits_{i=L}^{R}B_{i} \right)-\left(\sum\limits_{i=L^{\prime}}^{R^{\prime}}B_{i} \right)-A_{R}+A_{L} $$

故考虑求连续区间中的最大权。尝试枚举区间左端点 $ L $。然后求出当区间右端点 $ R>L $ 时最大的权值   $ V_{L}=\max \{S[L,R]-A_{R}+A_{L}\} $。

考虑如何在 $ \Theta(1) $ 或 $ \Theta(\log n) $ 的时间复杂度内求出对于一个左端点 $ L $ 的最大权 $ V_{L} $。

考虑把一个区间 $ [L,R] $ 扩展至 $ [L,R+1] $ 时的**权值变化**。即 $ D_{R+1}=B_{R+1}-(A_{R+1}-A_{R}) $。那么对 $ D $ 求前缀和，并取出在区间 $ [L+1,n] $ 中最大的前缀和，即基于 $ L $ 的最大的增量。这样便求出了当 $ L $ 为左端点时最大的权值。

显然 $ D $ 值和 $ D $ 值的前缀和均可以 $ \Theta(n) $ 预处理。前缀和的最大值也可以倒序 $ \Theta(n) $ 预处理。

代码如下：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
#define int ll
using namespace std;
const int N=1000005;
pair<int,int> e[N];
int n,d[N],sum[N],maxx[N];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld %lld",&e[i].first,&e[i].second);
	sort(e+1,e+n+1);
	for(int i=1;i<=n;i++) d[i]=e[i].second-(e[i].first-e[i-1].first);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+d[i];
	maxx[n+1]=-LLONG_MAX; for(int i=n;i>=1;i--) maxx[i]=max(maxx[i+1],sum[i]);
	int Ans=0;
	for(int i=1;i<=n;i++)
	{
		if(i!=n) Ans=max(Ans,e[i].second+max(0ll,maxx[i+1]-sum[i]));
		else Ans=max(Ans,e[n].second);
	}
	printf("%lld\n",Ans);
}

```

---

## 作者：书雪 (赞：0)

题意： $n$ 个物品有 体积 $a[i]$ 和 价值 $b[i]$ ，挑出任意个物品使它们的价值总和 $-(Amax-Amin)$ 最大

$n$ 最大 $500000$ ，故排除暴力枚举$Amax$ 和 $Amin$

可以发现所有变量均大于 $0$ ，所以当 $Amax$ 和 $Amin$ 确定后处于它们中间的所以物品都要选取

用结构体存储变量并按体积排序排序后用前缀和 $s[i]$ 存储价值，问题简化成为 $s[i]-s[j-1]+a[j]-a[i]$

有两个变量 $i$ 和 $j$ ，但因为排好序后体积为不降序列且在问题的式子中 $i\ge j$ 我们可以用一个循环解决

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,s[500010],ss;
struct node{
	long long a,b;
}p[500010];
bool cmp(node q1,node q2){
	if(q1.a!=q2.a) return q1.a<q2.a;
	else return q1.b>q2.b;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&p[i].a,&p[i].b);
	} 
	sort(p+1,p+n+1,cmp);//按体积升序排序
	for(int i=1;i<=n;i++){
		s[i]=s[i-1]+p[i].b;//前缀和存储价值
	} 
	for(int i=1;i<=n;i++){
		ss=max(ss,p[i].a-s[i-1]);
		ans=max(ans,ss-p[i].a+s[i]);//这里ans能减去的ss的值必然在i前面得出
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：Silence_World (赞：0)

[题面](https://www.luogu.com.cn/problem/P7667)

### 题意

美术馆中有 $n$ 个物品，每个物品有自己的大小和价值，
我们要在其中选取若干个物品，使他们的价值总和减去其中大小最大值与大小最小值的差最大。

### 思路

一开始看到价值以为是背包，仔细审了审题发现很明显是道贪心，因为很明显这个最大值和最小值是可以分开处理的，开个结构体，以大小更大的放后面，用前缀和记录前面所有的价值（这个比较关键，因为大小已经排序，所以前面的大小都是不可能比后面的大小大的，所以可以放心大胆用前缀和，最小值也一样）。

然后可以开始处理最大最小值，逆序循环遍历 $n$，最大值就是以当前情况为最大值所得的值和上一个的最大值中最大的，这样我们就可以处理出在 $i$ 时的最大值的最优情况。

最小值也相同，顺序循环遍历 $n$，判断以当前这个为最小值和上一个的最小值中的最大的（因为题目中所要求的是加上最小值，所以我们取更优情况）再加上我们以求的最大值最优情况，就能得到一个以 $i$ 时的最优情况，用一个变量记录这些最优的最大的输出变量，结束！

不懂得可以借助代码理解：

下面为本题代码：
``` cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node {
    int x, y;
} a[1000005];
bool cmp(node b, node c) {
    if (b.x != c.x) return b.x < c.x;
    return b.y < c.y;
}
int b[1000005];
int sum[10000005];
signed main() {
    int n;
    cin >> n;
    for (int i=1; i<=n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a+1, a+n+1, cmp);
    for (int i=1; i<=n; i++) {
        sum[i] = sum[i-1] + a[i].y; // 排序之后前缀和
    }
    b[n+1] = -1000000000000000000;
    int max1 = -10000000000000000; // 你觉得我会告诉你因为我max1开太大了wa了五六次吗QAQ
    for (int j=n; j>=1; j--) {
        b[j] = max(b[j+1], sum[j]-a[j].x);//求最大值的最优情况。
    }
    for (int j=1; j<=n; j++) {
        max1 = max(max1, a[j].x-sum[j-1]+b[j]);//求最小值的最优情况，加上之前求的最大值最优情况就变成了本题要求的。
        // cout << max1 << " ";
    }
    cout << max1 << endl;
    return 0;
}

```

---

## 作者：drinktowind (赞：0)

# 题目大意
给定 $n$ 个艺术品，每个艺术品都有它的尺寸和价值，选定几个艺术品，使选定的总价值减去物品尺寸的极差（最大值减最小值）最大。 
# 思路
开结构体分别存当前艺术品的尺寸和价值，排序后求前缀和，遍历更新答案。 
```
#include <bits/stdc++.h>
using namespace std;
long long b[1000010],f[10000010],n,mx=-1e18;//不开longlong见祖宗，mx一定要开很小，不然会wa 
struct node{
    long long x,y;//尺寸和价值 
}a[1000010];
bool cmp(node b,node c)//排序，尺寸小的在前面，尺寸一样，价值小的在前面 
{
    if(b.x!=c.x) 
		return b.x<c.x;
    return b.y<c.y;
}
int  main()
{
	cin>>n;
	b[n+1]=mx;//初始值 
    for(int i=1;i<=n;i++)
        cin>>a[i].x>>a[i].y;
    sort(a+1,a+n+1,cmp);//排序 
    for(int i=1;i<=n;i++)
        f[i]=f[i-1]+a[i].y;//前缀和 
    for(int i=n;i;i--)
    {
        b[i]=max(b[i+1],f[i]-a[i].x);//遍历最小值 
        mx=max(mx,a[i].x-f[i-1]+b[i]);//遍历当前答案 
	}
    cout<<mx;//输出 
    return 0;
}
```

---

