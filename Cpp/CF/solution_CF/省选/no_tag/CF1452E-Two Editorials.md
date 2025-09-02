# Two Editorials

## 题目描述

Berland regional ICPC contest has just ended. There were $ m $ participants numbered from $ 1 $ to $ m $ , who competed on a problemset of $ n $ problems numbered from $ 1 $ to $ n $ .

Now the editorial is about to take place. There are two problem authors, each of them is going to tell the tutorial to exactly $ k $ consecutive tasks of the problemset. The authors choose the segment of $ k $ consecutive tasks for themselves independently of each other. The segments can coincide, intersect or not intersect at all.

The $ i $ -th participant is interested in listening to the tutorial of all consecutive tasks from $ l_i $ to $ r_i $ . Each participant always chooses to listen to only the problem author that tells the tutorials to the maximum number of tasks he is interested in. Let this maximum number be $ a_i $ . No participant can listen to both of the authors, even if their segments don't intersect.

The authors want to choose the segments of $ k $ consecutive tasks for themselves in such a way that the sum of $ a_i $ over all participants is maximized.

## 说明/提示

In the first example the first author can tell the tutorial to problems from $ 1 $ to $ 3 $ and the second one — from $ 6 $ to $ 8 $ . That way the sequence of $ a_i $ will be $ [3, 2, 3, 3, 3] $ . Notice that the last participant can't listen to both author, he only chooses the one that tells the maximum number of problems he's interested in.

In the second example the first one can tell problems $ 2 $ to $ 4 $ , the second one — $ 4 $ to $ 6 $ .

In the third example the first one can tell problems $ 1 $ to $ 1 $ , the second one — $ 2 $ to $ 2 $ . Or $ 4 $ to $ 4 $ and $ 3 $ to $ 3 $ . Every pair of different problems will get the same sum of $ 2 $ .

In the fourth example the first one can tell problems $ 1 $ to $ 5 $ , the second one — $ 1 $ to $ 5 $ as well.

## 样例 #1

### 输入

```
10 5 3
1 3
2 4
6 9
6 9
1 8```

### 输出

```
14```

## 样例 #2

### 输入

```
10 3 3
2 4
4 6
3 5```

### 输出

```
8```

## 样例 #3

### 输入

```
4 4 1
3 3
1 1
2 2
4 4```

### 输出

```
2```

## 样例 #4

### 输入

```
5 4 5
1 2
2 3
3 4
4 5```

### 输出

```
8```

# 题解

## 作者：ql12345 (赞：17)

[传送门](https://www.luogu.com.cn/problem/CF1452E)

### 题面（经过我的魔改，更好理解）：

有两个讲师，$m$个听课的人，总的讲课范围为$[1,n]$，第i个听课的人感兴趣的范围为$[l_i,r_i]$，每个讲师的讲课范围为一段长度为$k$的连续的区间，每个听课的人只能听一个讲师讲课（你可以认为两个讲师同时讲课）

任务：任意选定两个讲师讲课的区间，并任意制定每个听课的人听的讲师，使得每个听课的人能听到的感兴趣的区间之和最大，你只需要输出这个最大值

sample input:
```cpp
10 5 3
1 3
2 4
6 9
6 9
1 8
```
sample output:
```cpp
14
```
解释：一个讲师在$[1,3]$，另一个讲师在$[6,8]$区间，第一个人对答案的贡献为3，从第二个人开始依次是：2 3 3 3

数据范围：$n,m,k<=2000$

### Solution：

- 考虑一个听课的人的区间和讲师的区间的重合部分如何计算
	
    观察到讲师的区间从$[1,k]$开始向右移动，重合部分变化过程是：（可能不是每种情况都完整地包含一下所有过程，但一定是一段连续的子过程）
    
    0 -> 逐渐增大 -> 最大 -> 持续一段时间 -> 最大 -> 逐渐减小 -> 0
    
    发现性质：而当两个区间的中点位置重合的时候，两个区间的重合面积一定是最大的
    
    于是我们可以将每个听课的人的区间用其中点位置表示，并排序，这样做可以保证存在一个位置：左边所有区间听课最优方案为左边的讲师区间，右边的所有区间的最优方案为右边的讲师区间（自己理解）

- 枚举每一种情况
	
    暴力是枚举两个讲师开始的位置，然后根据以上性质判断每个区间归到哪个讲师，并计算答案，求最大值，时间复杂度$O(n^2m)$，我看到CF上确实绝大多数人都是用这个方法A掉此题，但并不严谨，理论会$T$
    
    正解：考虑以上性质：“存在一个位置”，可以直接枚举这个“位置”
    
    只有一个区间的情况：枚举这个区间放在哪里，并枚举所有听课的人，计算出该区间下“后i个人的最大答案”，并用来更新“后i个人在只有一个区间下的最大答案”
   
    再枚举另一个区间的位置，枚举划分点在哪里，划分点以左的像刚才一样统计“该区间下前i个人的最大答案”，后m-i个人就是听另一个区间，“后m-i个人听同一个区间的最大答案”已经算出，可以直接加上，加和就为“该区间下该划分点为该位置的最大答案”，每求出一个更新ans，最终答案就是“所有区间下所有划分点时的最大答案”

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2005;
int n, m, k, sum[N];
struct P {
    int l, r;
    inline bool operator < (const P &A) const {
        return l + r < A.l + A.r;
    }
} a[N];
signed main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i) scanf("%d%d", &a[i].l, &a[i].r), -- a[i].l;
    sort(a + 1, a + m + 1);
    for (int i = 0; i <= n - k; ++i) {
        int cur = 0;
        for (int j = m; j; --j) {
            cur += max(0, min(i + k, a[j].r) - max(i, a[j].l));
            sum[j] = max(sum[j], cur);
        }
    }
    int ans = sum[0];
    for (int i = 0; i <= n - k; ++i) {
        int cur = 0;
        for (int j = 1; j <= m; ++j) {
            cur += max(0, min(i + k, a[j].r) - max(i, a[j].l));
            ans = max(ans, cur + sum[j + 1]);
        }
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：Celtic (赞：5)

题意：



给出 $n$ 和 $m$ 个区间 $[l_i,r_i]$，$l_i,r_i$ 在 $[1,n]$ 内。

要求选两个长度为 $k$ 的区间 $[a,b]$ 和 $[c,d]$ ，使得 所有区间 和 $[a,b],[c,d]$ 交集的最大值 之和最大。

也就是

$\sum_{i=1}^n max(max(0,min(b,r_i)-max(a,l_i)),max(0,min(d,r_i)-
max(c,l_i)))$

最大。

（文字和公式能看懂哪个就看哪个吧...）

考虑对于 $[l_i,r_i]$，$[a,b]$ 从左向右移动时，交集大小怎么变化的。

显然开始越来越大，当两个区间中心重合时最大，然后越来越小。

所以我们先把所有 $[l_i,r_i]$ 按 $l_i+r_i$，也就是按中心位置从小到大排序。

最优情况肯定是 $[a,b]$ 处理前缀和， $[c,d]$ 处理后缀和，两个加在一起。

所以设 $suf_i$ 表示 只用 $[a,b] $ 这个区间，第 $i$ 到 $m$ 这些区间与 $[a,b]$ 的交集的和最大是多少。设 $pre_i$ 表示 只用 $[a,b] $ 这个区间，第 $1$ 到 $i$ 这些区间与 $[a,b]$ 的交集的和最大是多少。

这两个数组可以 $O(nm)$处理。

答案 $ans$ 就是 $pre_i+suf_{i+1}$ 的最大值。

总复杂度是排序和预处理的复杂度，即 $O(n\log n+nm)$ 。

代码

```
#include<bits/stdc++.h>
#define N 2001001
#define re register
#define MAX 2001
#define inf 1e18
#define eps 1e-10
using namespace std;
typedef long long ll;
typedef double db;
inline void read(re ll &ret)
{
    ret=0;re char c=getchar();re bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
ll n,m,k,suf[N],ans;
struct node
{
	ll l,r;
	inline friend bool operator <(re node x,re node y)
	{
		return x.l+x.r<y.l+y.r;
	}
}a[N];
int main()
{
	read(n);
	read(m);
	read(k);
	for(re int i=1;i<=m;i++)
	{
		read(a[i].l);
		read(a[i].r);	
	}
	sort(a+1,a+m+1);
	for(re int i=1;i+k-1<=n;i++)
	{
		re ll from=i,to=i+k-1;
		re ll tmp=0;
		for(re int j=m;j;j--)
		{
			tmp+=max(0ll,min(to,a[j].r)-max(from-1,a[j].l-1));
			suf[j]=max(suf[j],tmp);
		}
	}
	ans=suf[1];
	for(re int i=1;i+k-1<=n;i++)
	{
		re ll from=i,to=i+k-1;
		re ll tmp=0;
		for(re int j=1;j<=m;j++)
		{
			tmp+=max(0ll,min(to,a[j].r)-max(from-1,a[j].l-1));
			ans=max(ans,tmp+suf[j+1]);
		}
	}
	printf("%lld\n",ans);
    exit(0); 
}
```


---

## 作者：封禁用户 (赞：4)

### 题意

[我的改编版本](https://www.luogu.com.cn/discuss/540279?page=1)

### 分析

可以发现，两个线段交的长度一定随着它们中点距离的减少而单调不减，所以可以吧线段按照中点从小到大进行排序，即按照 $l+r$ 从小到大进行排序。

```cpp
inline bool friend operator<(const node &X,const node &Y) {return X.l + X.r < Y.l + Y.r;}
```
排序完成后，一边的学生选择其中一个老师，另一边的学生选择另一个老师，这样一定更优。

  所以先枚举一个老师的区间，从前到后处理一遍；再枚举另一个老师的区间，从后到前处理一遍。在某个节点取最大值即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -1;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10^48);
}
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define ll long long
#define N 2010
int m,n,k,dp[2][N],ans = 0;
struct node
{
	int l,r;
	inline bool friend operator<(const node &X,const node &Y) {return X.l + X.r < Y.l + Y.r;}
}a[N];
int main()
{
	read(m),read(n),read(k); 
	F(i,1,n) read(a[i].l),read(a[i].r),--a[i].l;
	sort(&a[1],&a[n+1]);
	F(i,k,m)
	{
		register int now = 0;
		F(j,1,n)
		{
			now += max(0,min(a[j].r,i) - max(a[j].l,i-k));
			dp[0][j] = max(dp[0][j],now);
		}
	}
	F(i,k,m)
	{
		register int now = 0;
		D(j,n,1)
		{
			now += max(0,min(a[j].r,i) - max(a[j].l,i-k));
			dp[1][j] = max(dp[1][j],now);
		}
	}
	F(i,0,n) ans = max(ans,dp[0][i] + dp[1][i+1]);
	write(ans);
	return 0;
}
```


---

## 作者：Qiiiiiii_ (赞：3)

贪心+差分

考虑我们先钦定一个人的选择，即确定他选的左端点，然后判断另一个人选某一个点作为左端点的收益，这里的收益是指，当某一个线段在第二个人的选择中比第一个人的选择获得的值大多少，如果小于 $0$，视作 $0$。

为方便理解，我们建立一个坐标系，横坐标为第二个人选的左端点，纵坐标对应其收益。我们会发现，每一条线段会在坐标轴上留下两个斜率分别为 $1$ 和 $-1$ 的收益线段，线段的两端点根据第一个人选择情况以及线段自身决定(注意：这里得分类讨论，分线段长度大于等于 $K$ 和线段长度小于 $K$，同时一些线段在坐标轴上产生的收益线段启动可能为负值，所以我们得将坐标原点向左偏平移，而只有当某地方的真实横坐标大于等于 $1$ 的时候，我们才能取出来更新答案)。

对于这两条斜率为 $1$ 和 $-1$ 的收益线段，我们在横坐标上打 $tag$ 来实现。具体的，我们当前手上拿着的 $tag$ 表示，当前位置的斜率，即当前位置与前一个位置的差值。时间复杂度 $O(n^2)$ 。

```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
#define LL inline ll
#define I inline int
#define V inline void
#define B inline bool
#define FOR(i,a,b) for(re int i=(a),i##i=(b);i<=i##i;++i)
#define ROF(i,a,b) for(re int i=(a),i##i=(b);i>=i##i;--i)
#define gc getchar()
using namespace std;
const int N=4100;
LL read(){
	ll p=0; bool w=0; char ch=gc;
	while(!isdigit(ch)) w=ch=='-'?1:0,ch=gc;
	while(isdigit(ch)) p=p*10+ch-'0',ch=gc;
	return w?-p:p;
}
int n,m,K,l[N],r[N],nw,ans,tg[N],ad[N];
I get(int l1,int r1,int l2,int r2){	
	return max(0,min(r1,r2)-max(l1,l2)+1);
}
int main(){
	n=read(),m=read(),K=read();
	FOR(i,1,m) l[i]=read(),r[i]=read();
	FOR(i,1,n-K+1){
		memset(tg,0,sizeof(tg));
		nw=0;
		FOR(j,1,m){
			int len=get(i,i+K-1,l[j],r[j]);
			nw+=len;
			if(len==r[j]-l[j]+1) continue;
			if(r[j]-l[j]+1>=K){
				int pos=0;
				pos=n+len+l[j]-K;
				tg[pos+1]+=1;
				pos=n+l[j];
				tg[pos+1]-=1;
				pos=n+r[j]-K+1;
				tg[pos+1]-=1;
				pos=n+r[j]-len+1;
				tg[pos+1]+=1;
			}
			else{
				int pos=0;
				pos=n+len-K+l[j];
				tg[pos+1]+=1;
				pos=n+r[j]-K+1;
				tg[pos+1]-=1;
				pos=n+l[j];
				tg[pos+1]-=1;
				pos=n+r[j]-len+1;
				tg[pos+1]+=1;
			}
			
		}
		int tmp=0,us=0;
		FOR(j,1,2*n-K+1){
			us+=tg[j];
			tmp+=us;
			if(j>n) ans=max(ans,nw+tmp);
		}
	}
	cout<<ans;
	
	return 0;
}
```


---

## 作者：EuphoricStar (赞：1)

考虑枚举其中一个区间取 $[i, i + K - 1]$，考虑对于每个 $j$ 一次性处理出，区间取 $[j - K + 1, j]$ **多**产生的贡献（即以 $j$ 为右端点）。

对于一个 $[l_k, r_k]$，设其与 $[i, i + K - 1]$ 的交长度为 $t$。如果 $t = \min(r_k - l_k + 1, K)$ 则显然不会多产生贡献，直接判掉。否则：

- 若 $r_k - l_k + 1 \ge K$，当 $j$ 取 $[l_k + t, l_k + K - 1]$ 时，产生的贡献分别为 $1, 2, \ldots, K - t$；当 $j$ 取 $[l_k + K, r_k]$ 时，产生的贡献均为 $K - t$；当 $j$ 取 $[r_k + 1, r_k + K - t]$ 时，产生的贡献分别为 $K - t - 1, K - t - 2, \ldots, 1$。区间加一个数可以一阶差分处理，区间加等差数列可以二阶差分。

- 若 $r_k - l_k + 1 < K$，当 $j$ 取 $[l_k + t, r_k]$ 时，产生的贡献分别为 $1, 2, \ldots, r_k - l_k + 1 - t$；当 $j$ 取 $[r_k + 1, l_k + K - 1]$ 时，产生的贡献均为 $r_k - l_k + 1 - t$；当 $j$ 取 $[l_k + K, r_k + K - t]$ 时，产生的贡献分别为 $r_k - l_k - t, r_k - l_k - t - 1, \ldots, 1$。

二阶差分一下，最后枚举 $j$ 取 $\max$。时间复杂度 $O(n(n + m))$。

[code](https://codeforces.com/problemset/submission/1452/232616929)

---

## 作者：comcopy (赞：0)



题意不多赘述，这里直接讲做法。

我们可以暴力枚举其中一个区间，钦定另外一个区间在当前区间的左边，再计算出每个学生对每个点的贡献 ( 对于区间加减，具体可以用差分来解决 )，最后再对当前的长度为 $k$ 的区间值去取个最大值，就是我们要的答案。

具体看代码：

```cpp
#include<bits/stdc++.h>
#define mi(x,y) (fyn){x,y}
using namespace std;
const int N=2010;
struct fyn{
    int x,y;
}a[N];

inline int dis(int l1,int r1,int l2,int r2){
    return max(min(r1,r2)-max(l1,l2)+1,0);
}

int n,m,k;

int f[N];

signed main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;++i) cin>>a[i].x>>a[i].y;
    int ans=0;
    for(int i=k;i<=n;++i){
        int sum(0);
        for(int j=1;j<=m;++j){
            sum+=dis(i-k+1,i,a[j].x,a[j].y);//统计对第一个区间的贡献
            if(!(i>=a[j].y || i-k+1>=a[j].x)){ //如果相交，容斥消掉重复部分
                int len1=a[j].x-i+k-1;
                int len2=a[j].y-i;
                f[max(0,a[j].x-i)]++;
                f[len1+1]--;
                f[len2+1]--;
                f[
                    max(len1,len2) //相离
                    +min(k,a[j].y-a[j].x+1) //包含
                    -dis(i-k+1,i,a[j].x,a[j].y) //相交
                    +1
                ]++;//容斥
            }
        }
        int now=f[0];
        ans=max(ans,sum);
        for(int j=1+i;j<=n;++j){
            now+=f[j-i];
            sum+=now;
            ans=max(ans,sum);
        }//统计最终答案
        memset(f,0,sizeof f);
    }
    
    cout<<ans<<endl;
    
    return(0-0);
}
```


---

## 作者：free_fall (赞：0)

# 题目大意
有 $m$ 个区间，要求用两个长度为 $k$ 的区间与其相交，求这两个区间与所有区间重复部分的总和最大值（如果有同时与这两个区间相交的区间，只取它与其中一条区间相交的长度）是多少。
# 思路
首先是最暴力的写法，枚举这两个区间的初始位置，再枚举每一条边与它们的相交情况，就可以得到答案。但是时间复杂度是 $O(n^2 m)$，只能骗个部分分。

如果加上一些玄学优化，去掉重复枚举的情况，再排序求答案，加上头文件优化、快读等等，你会发现居然过了（有够水的）。当然，这肯定不是正解。

我们可以先枚举第一个区间的初始位置，再用**差分**的方式记录另一个区间从这个位置出发，逐渐向右移动对答案产生的影响。

1.  相交的长度**小于等于**枚举的线，不变。

2.  相交的长度**大于**枚举的线，加一。

3.  **包含**关系，不变。

4.  分离，相交的长度**大于**枚举的线，减一。

5.  相交的长度**小于等于**枚举的线，不变。

![](https://cdn.luogu.com.cn/upload/image_hosting/flhv7xop.png)

在每一次做完之后，用将答案加上差分的值的**前缀和**，取它们的最大值，即为最后的答案。时间复杂度为 $O(n \times m)$，可以过掉这道题了，记得每一次枚举第一个区间的起点时要清空差分数组。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
const int N=2005;
int n,m,k,d[N],p[N],ans;
struct student{
	int l,r;
}a[N];
bool cmp(student x,student y){
	if(x.l==y.l)return x.r<y.r;
	return x.l<y.l;
}
int solve(int l1,int r1,int l2,int r2){
	return max(0,min(r1,r2)-max(l1,l2)+1);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a[i].l,&a[i].r);
	}
	sort(a+1,a+m+1,cmp);
	for(int i=k;i<=n;i++){
		int sum=0;
		memset(d,0,sizeof(d));
		for(int j=1;j<=m;j++){
			sum+=solve(i-k+1,i,a[j].l,a[j].r);
			if(!(i>=a[j].r||i-k+1>=a[j].l)){
				int len1=a[j].l-i+k-1,len2=a[j].r-i;
				d[max(0,a[j].l-i)]++;
				d[min(len1,len2)+1]--;
				d[max(len1,len2)+1]--;
				d[max(len1,len2)+min(k,a[j].r-a[j].l+1)-solve(i-k+1,i,a[j].l,a[j].r)+1]++;
			}
		}
		ans=max(ans,sum);
		for(int j=1;j+i<=n;j++){
			d[j]+=d[j-1];
			sum+=d[j];
			ans=max(ans,sum);
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

# [E](https://www.luogu.com.cn/problem/CF1452E)        

实际难度其实低于 2500 。             

首先我们可以想到我们可以 $O(n ^ 3)$ 具体而言我们把所有合法老师区间都拿去对应的学生区间算一下贡献然后枚举两两老师区间各取 max 求整体 max 即可，显然做法。                

比较好笑的是，这种做法可以过这道题。                 
  
接着继续想下去，就感觉没有性质很难去一维于是就在显然做法上面狂暴了一个也很显的优化方法：比如说我们有一个学生很明显都是在左半边了，你老师非得一个选左半边的区间一个选右半边的区间，我这时不比较也知道肯定找左半边区间的那个老师更优嘛。                 

接着就想到了一个很 trick 的做法，我们先枚举一个位置 idx 表示 $[1 , idx]$ 的学生归一个老师后面的归另一个老师感觉左端点小并且区间长度很小的那些学生就应该往前面放，然后单独处理一些跨域了区间的学生……两边前缀和中间单独判？玄学时间复杂度并且我也不会写做法。                        

感觉这道题的性质还没研究完。于是考虑起了老师区间的一些性质。                      

老师区间首先长度固定了，那么我们抽象一个老师区间移动的过程：对于大多数的学生区间，它的过程基本都是没交，然后有交，接着取到最大值一个包含一个，接着离开。我们发现在这一过程中，老师区间的中点如果越接近学生区间的中点话，我们答案就会越大，这点很显然，~~不是暴论~~。                   

有了这个性质我们又发现，如果我们按区间中点排个序，是不是就可以直接拿去算了啊？想一想好像有点问题，比如说我们现在从中间一刀切两半分给两个老师管，假如中间有一个区间出现了上述的跨越中间界限的情况，比如说我本来划给左边的老师，但是我算给右边老师更优呢？         

别忘了我们可以枚举。           

接下来也是一个很简单的证明，首先此题肯定有一个中转点是一刀切两半后，左边归左边管，右边归右边管，如果当前不合法比如说左边的一个区间应该归右边管那么我们往后面枚举一个就可以了嘛，而在交界点往左右延伸的点就更不用说了，你左/右的点都不能越界了那么你哪还能越界？这明显不会更优。            

于是这道题就做完了，其实分的很细的话就是若干个小结论把大结论做出来了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 2e3 + 5;
int n,m,k,num[Len][Len],sum[Len][Len],MaxnPre[Len],MaxnSuf[Len],ans;
struct node
{
	int l,r;
}Sec[Len];
bool cmp(node x,node y){return x.l + x.r < y.l + y.r;}
int Calc(int l,int r,int L,int R)
{
	if(l <= L && r >= R) return R - L + 1;
	if(L <= l && R >= r) return r - l + 1;
	if(l > L) swap(l , L) , swap(r , R);
	return max(0 , r - L + 1);
}
signed main()
{
	scanf("%d %d %d",&n,&m,&k);
	for(int i = 1 ; i <= m ; i ++) scanf("%d %d",&Sec[i].l,&Sec[i].r);
	sort(Sec + 1 , Sec + 1 + m , cmp);
	for(int l = 1 ; l <= n - k + 1 ; l ++)
	{
		int r = l + k - 1;
		for(int j = 1 ; j <= m ; j ++) 
		{
			num[l][j] = Calc(l , r , Sec[j].l , Sec[j].r);
			sum[l][j] = sum[l][j - 1] + num[l][j];
			MaxnPre[j] = max(MaxnPre[j] , sum[l][j]);
		}
	}
	for(int l = 1 ; l <= n - k + 1 ; l ++)
	{
		int r = l + k - 1;
		for(int j = m ; j >= 1 ; j --) 
		{
			sum[l][j] = sum[l][j + 1] + num[l][j];
			MaxnSuf[j] = max(MaxnSuf[j] , sum[l][j]);
		}
	}
	ans = max(ans , MaxnSuf[1]);
	for(int i = 1 ; i <= m ; i ++) ans = max(ans , MaxnPre[i] + MaxnSuf[i + 1]);
	printf("%d\n",ans);
	return 0;
}
```

---

