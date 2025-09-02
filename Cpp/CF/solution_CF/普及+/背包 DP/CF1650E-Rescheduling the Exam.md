# Rescheduling the Exam

## 题目描述

Now Dmitry has a session, and he has to pass $ n $ exams. The session starts on day $ 1 $ and lasts $ d $ days. The $ i $ th exam will take place on the day of $ a_i $ ( $ 1 \le a_i \le d $ ), all $ a_i $ — are different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/80b5043cb96246fb12fe0316b7ae224994f04da5.png)Sample, where $ n=3 $ , $ d=12 $ , $ a=[3,5,9] $ . Orange — exam days. Before the first exam Dmitry will rest $ 2 $ days, before the second he will rest $ 1 $ day and before the third he will rest $ 3 $ days.For the session schedule, Dmitry considers a special value $ \mu $ — the smallest of the rest times before the exam for all exams. For example, for the image above, $ \mu=1 $ . In other words, for the schedule, he counts exactly $ n $ numbers — how many days he rests between the exam $ i-1 $ and $ i $ (for $ i=0 $ between the start of the session and the exam $ i $ ). Then it finds $ \mu $ — the minimum among these $ n $ numbers.

Dmitry believes that he can improve the schedule of the session. He may ask to change the date of one exam (change one arbitrary value of $ a_i $ ). Help him change the date so that all $ a_i $ remain different, and the value of $ \mu $ is as large as possible.

For example, for the schedule above, it is most advantageous for Dmitry to move the second exam to the very end of the session. The new schedule will take the form:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/ea72ffbaa1a469cfa577e07f4a541e64f273ed21.png)Now the rest periods before exams are equal to $ [2,2,5] $ . So, $ \mu=2 $ .Dmitry can leave the proposed schedule unchanged (if there is no way to move one exam so that it will lead to an improvement in the situation).

## 说明/提示

The first sample is parsed in statement.

One of the optimal schedule changes for the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/a8127e465b7998df08b0c9dd6be925e73333852b.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c109ce56a74359821f30b8b4de03ca418349d132.png)New schedule.

In the third sample, we need to move the exam from day $ 1 $ to any day from $ 4 $ to $ 100 $ .

In the fourth sample, any change in the schedule will only reduce $ \mu $ , so the schedule should be left as it is.

In the fifth sample, we need to move the exam from day $ 1 $ to any day from $ 100000000 $ to $ 300000000 $ .

One of the optimal schedule changes for the sixth sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c42982828b6b783bfe2b7287e37a4f2be5dfff0a.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/40bee0dd841380562f7e8f2d4a71c924f5f6fe41.png)New schedule.

In the seventh sample, every day is exam day, and it is impossible to rearrange the schedule.

## 样例 #1

### 输入

```
9

3 12
3 5 9

2 5
1 5

2 100
1 2

5 15
3 6 9 12 15

3 1000000000
1 400000000 500000000

2 10
3 4

2 2
1 2

4 15
6 11 12 13

2 20
17 20```

### 输出

```
2
1
1
2
99999999
3
0
1
9```

# 题解

## 作者：DaiRuiChen007 (赞：7)

# $\text{CF1650E - Rescheduling the Exam}$ 题解

## 题目大意

小 P 有 $n$ 场考试要考，它们的开始时间是 $a_1\sim a_n$（保证 $a$ 按升序排列），所有的考试都会在 $d$ 之前结束。

对于时间相邻的两场考试 $a_{i-1},a_{i}$，定义它们的距离为 $a_{i}-a_{i-1}-1$，而 $a_0$ 与 $a_{1}$ 的距离定义为 $a_n$ 与 $0$ 的距离。

定义对于这个数组 $a$ 的 $\mu$ 值为所有 $a_{i-1}$ 与 $a_{i}$ 之间距离的最小值。

你可以改变某一个 $a_i$ 的值（但不能 $>d$），最大化修改后 $a$ 的 $\mu$ 的值，输出最大的 $\mu$ 值。

## 思路分析

显然，如果要让 $a$ 的 $\mu$ 值变大，一定要修改某两个距离最小的 $a_{i-1},a_{i}$ 其中之一。

感性理解一下，如果要修改 $a_i$ 的值使得 $\mu$ 值最大，那么这个 $a_i$ 只有两种可能使 $\mu$ 成为最大值：

1. $a_i$ 放到距离最大的 $a_{j-1}$ 和 $a_{j}$ 之间，这种情况下距离是 $\left\lfloor\dfrac{a_{j-1}-a{j}-1}{2}\right\rfloor$。
2. $a_i$ 放到 $d$ 处，这种情况下距离是 $d-a_n-1$。

所以只需要考虑在这两个方案的距离之间取最小值即可。

分别对修改 $a_{i-1}$ 和 $a_i$ 的最优方案进行计算即可。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int a[MAXN],n,d;
inline int calc(int x) {
	//修改x后的最优解 
	int lst=0,min_gap=d,max_gap=0;
	//分别代表上一场考试,距离最远的两场考试,距离最近的两场考试 
	for(int i=1;i<=n;++i) {
		if(i==x) continue;
		int gap=a[i]-a[lst]-1;
		min_gap=min(min_gap,gap);
		max_gap=max(max_gap,gap);
		lst=i;
	}
	return min(min_gap,max(((max_gap-1)/2),d-a[lst]-1));
}
inline void solve() {
	int pos=1,res=0;
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		if(a[i]-a[i-1]-1<a[pos]-a[pos-1]-1) pos=i;
		//求出距离最小的两场考试 
	}
	res=calc(pos); //修改a[pos] 
	if(pos>1) res=max(res,calc(pos-1));
	//如果最短距离不是和0计算而取得的就修改a[pos-1] 
	printf("%d\n",res);
	return ;
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

## 作者：OIer_ACMer (赞：2)

~~考试时间竟然由我说的算？！~~

------------
注：本题思路较为简单，所以笔者不会过多赘述原理以及证明，望周知！

------------
## 大致思路：
本题可以用二分做~~好像全网我是第一个用二分做的屑~~，具体来讲，求最小值的最大值，也就是需要二分答案，这个不难想到，关键点就是在于如果写 $\operatorname{check}$ 函数。

首先，我们要知道一个概念：休息时间（之后我们称它为间隔期）是 $t[i]-t[i-1]-1$，而**休息时间最少的那两门考试必须要移动一个**（因为你要**最大化间隔最小时**间）。所以需要两门都进行计算。

接着，我们讨论一下怎么设置 $\operatorname{check}$ 函数：设置一个 $mid$ 变量（这个干啥用我就不说了），我们需要做的就是**判断该情况下间隔期可否有 $mid$ 变量这么大**，这是为了**在存在的情况下通过修改来找出更大的**。首先找到间隔期小于 $x$ 的部分（那个 $x$ 就是我们传进去的 $mid$ 的值，只不过在 $\operatorname{check}$ 函数中我们不称它为 $mid$），如果找不到的话，说明现有安排的间隔期都比 $mid$ 大返回 $1$。 如果有小于 $mid$ 的间隔期话，用 $index$ 变量记录下它的位置。接下来进行遍历，因为，因为要重新安排该门考试的时间，所以我们可以开一个数组 $b$ 记录下其他考试的时间。如果此时最后一门考试之后剩余的天数比 $mid$ 大，就设置 $f$ 为 $1$。

预处理做完后，接下来我们就要遍历 $b$ 数组，如果出现**有两门考试之间的间隔期比 $mid$ 小的话**，$f$ 就赋值为 $0$，表示这种情况不行，结束遍历。**如果两门考试之间的间隔期特别久，就代表着这种情况可以**，超过 $2 \times x$ 的时候，那么刚才拿出的考试就塞进去之后同样满足大于 $mid$ 的情况，再次将 $f$ 赋值为 $1$。此时，如果 $f$ 为 $1$ 的话，就返回 $1$，表示这种修改可以。

至此，相当于我们讨论了间隔期小于 $mid$ 的两门考试中后面的一门，接下来讨论前面的一门，只需要 $index$ 减 $1$，同理按照上述方法再讨论一遍即可。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int maxn = 2e5 + 2;
int n, d;
int a[maxn], b[maxn];
bool check(int x)
{
    int index = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] - a[i - 1] - 1 < x)
        {
            index = i;
            break;
        }
    }
    if (!index)
    {
        return 1;
    }
    int cnt = 0, f = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i != index)
        {
            b[++cnt] = a[i];
        }
    }
    if (d - b[cnt] - 1 >= x)
    {
        f = 1;
    }
    for (int i = 1; i < n; i++)
    {
        if (b[i] - b[i - 1] - 1 < x)
        {
            f = 0;
            break;
        }
        if (b[i] - b[i - 1] >= 2 * x + 2)
        {
            f = 1;
        }
    }
    if (f)
    {
        return 1;
    }
    index--;
    cnt = f = 0;
    if (index == 0)
    {
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        if (i != index)
        {
            b[++cnt] = a[i];
        }
    }
    if (d - b[cnt] - 1 >= x)
    {
        f = 1;
    }
    for (int i = 1; i < n; i++)
    {
        if (b[i] - b[i - 1] - 1 < x)
        {
            f = 0;
            break;
        }
        if (b[i] - b[i - 1] >= 2 * x + 2)
        {
            f = 1;
        }
    }
    if (f)
    {
        return 1;
    }
    return 0;
}
void littlefat()
{
    n = read(), d = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    int l = 0, r = d;
    while (l < r - 10)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    for (int i = r; i >= l; i--)
    {
        if (check(i))
        {
            cout << i << endl;
            return;
        }
    }
}
signed main()
{
    int t = read();
    while (t--)
    {
        littlefat();
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122530712)

---

## 作者：王熙文 (赞：2)

## 思路

提供一种特别无脑的做法。

考虑枚举改变的这个点，如果我们将这个点删掉，为了使解最优，它会放到哪里呢？有两种情况：

* 插到两个考试之间（为了方便，时间为 $0$ 的那个点也是一场考试），为了使距离最大，这场考试显然要插到距离最大的两个考试之间。
* 插到最后（时间为 $d$），可以直接算出来。

那么我们可以用一个数据结构维护每两场考试之间的距离（最小值即为答案），这个数据结构需要支持：

* 插入数：最初要插入相邻考试的距离 / 删掉某个点时要插入它相邻的两个点之间的距离；
* 删除数：删掉某个点时要删掉它与相邻的点的距离；
* 求最大值：这场考试要插入到当前距离最大的两个考试之间；
* 求最小值：答案即为最小值。

我使用了两个堆的方式来插入、删除、求最大值（求最小值再用两个堆即可），具体方式是：

使用一个堆来存所有插入的数，另一个堆来存所有删除的数，那么插入和删除操作可以通过插入这两个堆解决。

对于查询最大/最小数可以疯狂弹两个堆的堆顶，如果这两个堆的堆顶相同就一起弹出，否则答案就是维护所有插入的数的堆的堆顶。

发现某个堆里的一个数会插入一次、删除（弹堆顶）一次，所以复杂度还是对的。

注意：对这两种情况求出答案后还要复原到原来的情况。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,d;

int a[200010];

priority_queue<int> aa,bb; // 这两个堆维护最大值
priority_queue<int,vector<int>,greater<int> > cc,dd; // 这两个堆维护最小值

int inscnt=0,ins[400010],delcnt=0,del[400010]; // 记录插入和删除的数，用于复原

void insert(int x)
{
	aa.push(x),cc.push(x); // 插入 push 到插入的堆
	ins[++inscnt]=x;
}

void ddel(int x)
{
	bb.push(x),dd.push(x); // 删除 push 到删除的堆
	del[++delcnt]=x;
}

int get_max()
{
	while(!bb.empty() && aa.top()==bb.top()) aa.pop(),bb.pop(); // 当删除的堆顶和插入的堆顶相同时就一起弹
	return aa.top();
}

int get_min()
{
	while(!dd.empty() && cc.top()==dd.top()) cc.pop(),dd.pop();
	return cc.top();
}

void clear() // 复原，将之前插入的删除，之前删除的插入
{
	for(int i=1; i<=inscnt; ++i) bb.push(ins[i]),dd.push(ins[i]);
	for(int i=1; i<=delcnt; ++i) aa.push(del[i]),cc.push(del[i]);
}

int main()
{
	int t; cin>>t;
	while(t--)
	{
		int ans=0;
		while(!aa.empty()) aa.pop();
		while(!bb.empty()) bb.pop();
		while(!cc.empty()) cc.pop();
		while(!dd.empty()) dd.pop();
		cin>>n>>d;
		for(int i=1; i<=n; ++i) cin>>a[i];
		a[0]=0;
		for(int i=1; i<=n; ++i)
		{
			insert(a[i]-a[i-1]-1);
		}
		for(int i=1; i<=n; ++i)
		{
			// 放某个区间里
			inscnt=delcnt=0;
            // 删除当前考试（更新两个考试之间的距离 
			ddel(a[i]-a[i-1]-1); // 删除当前考试与左面的距离 
			if(i!=n)
			{
				ddel(a[i+1]-a[i]-1); // 删除当前考试与右面的距离 
				insert(a[i+1]-a[i-1]-1); // 插入当前考试左面与右面的距离 
			}
			int nowqj=get_max(); // 找到删除当前考试之后相邻两个考试的最大距离 
			ddel(nowqj); // 删除最大距离，从中插入 
			if(nowqj&1) insert(nowqj/2),insert(nowqj/2);
			else insert(nowqj/2),insert(nowqj/2-1);
			ans=max(ans,get_min()); // 答案即最小距离 
			clear();
			// 放最后
			inscnt=delcnt=0;
			// 还要删除一遍当前考试（因为上面复原了） 
			ddel(a[i]-a[i-1]-1);
			if(i!=n)
			{
				ddel(a[i+1]-a[i]-1);
				insert(a[i+1]-a[i-1]-1);
			}
			insert(d-(i==n?a[n-1]:a[n])-1); // 注意特判当前考试已经为最后一个了（就找倒数第二个） 
			ans=max(ans,get_min());
			clear();
		}
		cout<<ans<<'\n'; 
	}
	return 0;
}
``` 

---

## 作者：Fislett (赞：1)

# 题意：
题意简单明了，就不多赘述了。
# 解题方法：
这道题我们要考虑贪心。由于我们只有一次修改 $a_i$ 的机会，所以我们修改的值一定是产生最小距离的两个相邻的点之中修改。

那么如何修改是最优的呢？有一下两种情况：

1. 插入到距离最大的两个相邻点的最中间。因为只有插入到距离最大的两个相邻点的最中间，才能使它和相邻的点的距离最大。

1. 插入到最后的 $d$ 这个时间。

在这两种情况中取最近距离的 $max$ 即可。

另外注意，这里求距离的公式有点另类。

# 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, d, a[200001];
int dis(int x, int y) {return a[x] - a[y] - 1;}
int f(int x)
{
	int Min = 2e9, Max = 0, last = 0; //Min表示最小值，Max表示最大值，last表示当前为止的最后一个点 
	for (int i = 1; i <= n; i ++)
	{
		if (i == x) continue; //千万注意要continue 
		Min = min(dis(i, last), Min);
		Max = max(dis(i, last), Max);
		last = i;
	}
	return min(Min, max((Max - 1) >> 1, d - a[last] - 1));
}
int main()
{
	scanf("%d", &t);
	while (t --)
	{
		int minn = 2e9, minx, ans = 0;
		scanf("%d%d", &n, &d);
		for (int i = 1; i <= n; i ++)
		{
			scanf("%d", &a[i]);
			if (dis(i, i - 1) < minn) //读入的时候顺便取min 
			{
				minn = dis(i, i - 1);
				minx = i;
			}
		}
		ans = f(minx);
		if (minx != 1) ans = max(ans, f(minx - 1)); //如果minx为1，就不能修改它前面的点了（以为它前面没有点） 
		printf("%d\n", ans);
	}
}
```
~~码字不易，求管理员大大通过~~

---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF1650E (luogu)](https://www.luogu.com.cn/problem/CF1650E)

[CF1650E (codeforces)](https://codeforces.com/contest/1650/problem/E)

# 解题思路

首先，你发现你只能改一个日期，那么我们肯定是改距离最近的旁边的两场考试，此时我们就可以将操作转化为删去一场考试并添加一场新考试的最小的休息时长，容易使用贪心 $O(n)$ 解决。

总时间复杂度 $O(n \log_2 n)$，瓶颈在于排序。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define forll(i,a,b,c) for(register long long i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(register long long i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll n,m;
ll a[200010],b[200010],cz2[200010];
struct node{
	ll x,id;
}cz[200010];
bool cmp(node x,node y){
	return x.x<y.x;
}
ll f(ll x)// del x 
{
	ll k=0;
	forl(i,1,n)
		 if(i!=x)
		 	b[++k]=a[i];
	ll ans=0;
	forl(i,1,n-1)
		cz2[i]=b[i]-b[i-1];
	forl(i,1,n-1)
		ans=max(ans,cz2[i]/2);
	ans=max(ans,m-b[n-1]);
	sort(cz2+1,cz2+n);
//	cout<<ans<<' '<<cz2[1]<<endl;
	return min(ans,cz2[1]);
}
void solve()
{
	ll ans=0;
	cin>>n>>m;
	forl(i,1,n)
		cin>>a[i],cz[i].x=a[i]-a[i-1],cz[i].id=i;
	sort(cz+1,cz+1+n,cmp);
	ans=max(ans,f(cz[1].id));
	ans=max(ans,f(max(cz[1].id-1,1ll)));
	ans=max(ans,f(min(cz[1].id+1,n)));
	cout<<ans-1<<endl;
}
int main()
{
	IOS;
	t=1;
	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 1900}$
---
### 解题思路：

考虑贪心。

要求最小的一个间隔时间最大，则一定是更改间隔时间最小的一个位置上的时间，而可能最这个位置造成影响的只有更改当前位置和更改这个位置的前一个位置两种可能选项。

确定更改位置之后，将当前位置移动到对应的位置同样只有移动到最大的两者之间和移动到最后两种可能情况。

讨论一下即可，注意计算距离的公式不要写错。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,a[200005],b[200005],d,minx,mini,maxn,T,ans;
int work(int pos){
	minx=2147483647;
	maxn=0;
	int la=0;
	for(int i=1;i<=n;i++){
		if(i==pos)continue;
		minx=min(minx,a[i]-a[la]-1);
		maxn=max(maxn,a[i]-a[la]-1);
		la=i;
	}
	return min(minx,max((maxn-1)/2,d-a[la]-1));
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&d);
		for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
		minx=2147483647;
		for(int i=1;i<=n;i++)
		if(a[i]-a[i-1]-1<minx){
			minx=a[i]-a[i-1]-1;
			mini=i;
		}
		ans=work(mini);
		if(mini!=1)ans=max(ans,work(mini-1));
		printf("%d\n",ans);
	}
	return 0;
}
```



---

