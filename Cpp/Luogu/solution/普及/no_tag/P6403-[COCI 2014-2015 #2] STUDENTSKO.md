# [COCI 2014/2015 #2] STUDENTSKO

## 题目描述

一年一度的萨格勒布大学学生乒乓球团体赛将于下周六举行！每队由 $k$ 名学生组成。$n$ 个兴奋的学生们正在排队等候登记。Krešo 在登记处工作。他真的不想做他的工作，所以他决定不让学生选择团队。他决定第一组将由第一个排队的 $k$ 名学生组成，第二组由下面的 $k$ 名学生组成，第三组由后面的 $k$ 名学生组成，以此类推。（$n\equiv 0\pmod k$，因此没有人剩余。）

Ante 用一个整数来估计每个玩家的技能。他希望第一队拥有最弱的 $k$ 个球员，第二队拥有第二弱的 $k$ 个球员，依此类推，最后一队拥有最强的 $k$ 个球员。

Krešo 刚刚休息了一下，Ante 决定转移排队的学生以达到自己的目标。他转移学生的方式是告诉一个学生从队列中走出来，在另一个学生后面排队，或者走到队列的前面。每转移一个学生花费一分钟。Krešo 有可能随时从休息中回来，所以 Ante 需要尽快实现他的目标。帮助 Ante 确定实现目标所需的最少分钟数。

## 说明/提示

#### 样例 3 说明

Ante 应该将技能等级为 $5,6$ 和 $3$ 的学生移到队列的前面，花了三分钟。

#### 数据范围与约定

- 对于 $30\%$ 的数据，有 $1\le n\le 20$。
- 对于 $100\%$ 的数据，有 $1\le k\le n\le 5\times 10^3$。

对于所有合法的 $v_i$，都有 $1\le v_i\le 10^9$。

#### 说明

**题目译自 [COCI2014-2015](https://hsin.hr/coci/archive/2014_2015/) [CONTEST #2](https://hsin.hr/coci/archive/2014_2015/contest2_tasks.pdf) _T3 STUDENTSKO_。**

## 样例 #1

### 输入

```
4 1
9 12 5 13```

### 输出

```
1```

## 样例 #2

### 输入

```
6 2
16 2 1 7 5 10```

### 输出

```
1```

## 样例 #3

### 输入

```
6 3
7 9 8 3 6 5 ```

### 输出

```
3```

# 题解

## 作者：Acabbage (赞：3)


#### 发现没人用二分 + 贪心求最长不下降子序列的做法？那作为最优解的我就来发一篇吧。


------------

## 题意简述

给定 $n$ 个数的序列 $a$，分为若干组，保证每组恰好 $k$ 个数。现要通过每次移动一个数的位置，使每组都满足其中所有数大于前一组并小于后一组，求移动次数的最小值。


------------

## 解法

- ### 如何转化为最长不下降子序列问题？

显然，每个数应在的组是确定的，所以可以先对整个序列 $a$ 按数值大小 $v$ 来排序，再根据每个 $a_i$ 的原位置 $p$，用 $b$ 数组维护出其应在的组。

得到 $b$ 数组后，我们发现只有它的最长不下降子序列是不用转移位置的，所以只要求出 $b$ 的最长不下降子序列长度 $c$，移动次数的最小值即为 $n-c$。

- ### 如何用二分 + 贪心求最长不下降子序列？

维护一个单调栈 $s$，$s_c$ 表示长度为 $c$ 的最长不下降子序列末尾元素的最小值。对于每个 $b_i$，如果 $b_i\geq{s_i}$，满足单调不减性，直接入栈；否则，运用贪心思想在 $s$ 中二分查找第一个大于 $b_i$ 的位置 $t$，将 $s_t$ 替换为 $b_i$，即能最大限度地满足单调性。最后，$c$ 即为最长不下降子序列长度。

- ### 时间复杂度

$O(n\log{n})$



------------

## AC 代码（76ms）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define gch getchar() 
#define ub upper_bound
using namespace std;
ll rd()
{
	ll f=1,x=0; char c;
	while (!isdigit(c=gch)) if (c==45) f=-1;
	while (isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=gch;
	return f*x;
}
void wt(ll x)
{
	if (x<0) putchar('-'),x=-x;
	if (x>9) wt(x/10);
	putchar(x%10+'0');
}
const int N=5e3+5;
int n,k,t,c,b[N],s[N];
struct node
{
	int v,p;
	bool operator<(const node &x){return v<x.v;}
}a[N];
void in() //读入
{
	n=rd(),k=rd();
	for(int i=1;i<=n;i++)a[i].v=rd(),a[i].p=i;
}
void pre() //预处理
{
	sort(a+1,a+n+1); //排序
	for(int i=1;i<=n;i++)b[a[i].p]=(i-1)/k+1; //分组
}
void slv() //求最长不下降子序列
{
	s[++c]=b[1];
	for(int i=2;i<=n;i++)
	{
		if(b[i]>=s[c])s[++c]=b[i]; //满足单调性就直接入栈
		else t=ub(s+1,s+c+1,b[i])-s,s[t]=b[i]; //否则，用二分+贪心
	}
}
int main()
{
	in();pre();slv();wt(n-c); //答案是n-c
	return 0;
}
```



---

## 作者：zumgze (赞：2)

### 算法 排序+最长不下降子序列

### 最优复杂度 $O(nlogn)$

先排序，计算出每一个每个人所应该在的小组的编号，之后用小组编号跑最长不下降子序列

可以这样理解，你先得到了最长不下降子序列的m个人，你可以让其余n-m个人按照顺序依次走到队伍的最前面或最后面，完毕！

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int no,e;
}a[10000];
int b[10000];
int ans[10000];
bool cmp(node a,node b)
{
	return a.e<b.e;
}
int main()
{
    ios::sync_with_stdio(false);
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
    	cin>>b[i];
		a[i].e=b[i];
    	a[i].no=i;
	}
	sort(a,a+n,cmp);//排序
	for(int i=0;i<n;i++)
		b[a[i].no]=i/k;//计算小组编号
	int kotae=0;
	for(int i=0;i<n;i++)//最长不下降子序列
	{//由于数据范围不大，我选择了时间复杂度较高但码量比较小的写法
		ans[i]=1;
		for(int j=0;j<i;j++)
			if(b[j]<=b[i])ans[i]=max(ans[i],ans[j]+1);
		kotae=max(kotae,ans[i]);	
	}
	cout<<n-kotae;
    return 0;
}
```


---

## 作者：xAlec (赞：1)

# 1、题目理解

共有 $ n $ 个学生，每个学生都有不同的技能点数，现在要将他们排序，求他们的 **最长不下降子序列**。

# 2、实现方法

这是一道排序题，首先需要一个结构体去储存编号、能力以及每个人被分到的小组编号，在依据能力从大到小先排序得到目标数组，再进行 $ dp $。用 $ ans $ 储存最长不下降子序列的长度，最后用 $ n $ 减去 $ ans $，因为这 $ ans $ 个学生不用再移动了。

# 3、LIS怎么求

 **LIS** 是最长不下降子序列，整个子序列 **单调不降**，并且是序列中 **最长的单调不降子序列** 我们要在状态转移方程中进行判断,看是不是每一个枚举到的数据均为单调不下降的，然后将子序列长度加一。最后每次要取最大值。

# 4、代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e4+10;
struct node{
	int vice;
	int id;
	int pos;
}v[N];//储存能力、编号、队伍编号
bool cmp(node x,node y){return x.vice<y.vice;}//能力排序
bool tmp(node x,node y){return x.id<y.id;}//编号排序
int n,k,f[N];
int ans=-1;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>v[i].vice;
		v[i].id=i;//存储下编号
	}
	sort(v+1,v+n+1,cmp);//排序得到目标数组
	for(int i=1;i<=n;i++)
		v[i].pos=(i-1)/k+1;//每个队伍编号
	sort(v+1,v+n+1,tmp);//再排序回来
	for(int i=1;i<=n;i++){
		f[i]=1;
		for(int j=1;j<i;j++){
			if(v[j].pos<=v[i].pos)
				f[i]=max(f[i],f[j]+1);//dp部分求最长不下降子序列
		}
		ans=max(ans,f[i]);//得到ans
	}
	cout<<n-ans<<endl;//注意要用n去减
	return 0;
}
```


---

## 作者：pxb0801 (赞：1)

### 0.题目大意

一共有 $n$ 个人，每个人有技能，技能强弱不同，现要求分组，每组 $k$ 人，要求每组的人均比上一组强，比下一组弱。

---------------
### 1.思考过程

看到这道题其实很容易想到[最长不下降子序列](https://blog.csdn.net/xiaoxi_hahaha/article/details/119602482)，可以说这题只是有一点点变化，几乎就是模板。不会的同学可以先自行学习。

--------------
### 2.分析

首先我们应该记录每个人所在的组别，这很容易做到，因为组别分配是根据技能，而技能就是输入数据。

当我们分配好组别后，再用每个人所在组别做最长不下降子序列。这样同一组别内的就已经不再区分技能强弱了，这也正好达成我们的目的：同一组别内不需要按照技能强弱排序。

最后，我们已经找到了最长不下降子序列的长度，这是保留下来的，剩下的要进行移动，输出 $n-$ 最长不下降子序列长度 即可。

### 3.正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,f[5005],ans;
struct node{
	int x,tem,id;
}a[5005];//预处理 
bool cmp(node x,node y){
	return x.x<y.x;
}
bool cmp2(node x,node y){
	return x.id<y.id;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].x;//读入 
		a[i].id=i;//记录序号，便于在记录组别后排回来 
	}
	sort(a+1,a+n+1,cmp);//按照技能排序 
	for(int i=1;i<=n;i++){
		a[i].tem=(i-1)/k+1;//予以记录组别 
		//tem 是 team 的简写，本蒟蒻的英语不好，见谅~ 
	}
	sort(a+1,a+n+1,cmp2);//按序号排回来
	//最长不下降子序列的 O(n^2)做法（数据水） 
	for(int i=1;i<=n;i++){
		f[i]=1;
		for(int j=1;j<i;j++){
			if(a[j].tem<=a[i].tem){//按照组别进行，别忘了取 "=" 
				f[i]=max(f[i],f[j]+1);
			}
		}
		ans=max(ans,f[i]);
	}
	cout<<n-ans;//要输出移动的人数，要用 n减 
	return 0;
}
```


---

## 作者：ggc123 (赞：0)

## 思路
1. 因为 Ante 希望第一队拥有最弱的 $k$ 个球员，第二队拥有第二弱的 $k$ 个球员，依此类推，最后一队拥有最强的 $k$ 个球员。所以应先将球员**按能力从小到大排序**。
2. 此时球员的顺序是最理想的状态，将球员排序后，打上球队的标记，并还原球员的顺序。
3. 因为原来的顺序不一定是最理想的顺序，所以要让移动次数最小，符合队伍排序的顺序最长。而这个符合队伍排序的顺序就是**队伍编号的最长不降子序列**。

## 代码
蒟蒻还不会 $O\left ( n\log_{2}{n}  \right ) $，只会 $O\left ( n^2 \right ) $。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct stu {
	int a, id, team;
} s[5005];
int n, k;
bool cmp1(stu A, stu B) {
	return A.a < B.a;
}
bool cmp2(stu A, stu B) {
	return A.id < B.id;
}
int f() {//最长不降子序列，即符合队伍排序的顺序
	int dp[5005], ans = -1e9;
	for (int i = 1; i <= n; i++) {
		dp[i] = 1;
		for (int j = 1; j < i; j++)
			if (s[i].team >= s[j].team)
				dp[i] = max(dp[i], dp[j] + 1);
	}
	for (int i = 1; i <= n; i++)	ans = max(ans, dp[i]);
	return ans;
}
signed main() {
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)	cin >> s[i].a;//输入
	for (int i = 1; i <= n; i++)	s[i].id = i;//编号，为后面还原做标记
	sort(s + 1, s + 1 + n, cmp1);//按能力排序
	for (int i = 1; i <= n; i++)	s[i].team = (i + k - 1) / k;//打上队伍标号
	sort(s + 1, s + 1 + n, cmp2);//还原
	cout << n - f()<<"\n";
	return 0;
}
```

---

## 作者：qw1234321 (赞：0)

算是 LIS 板子题了吧，没想到还能写题解。

首先，将原序列排序（即成为目标状态），然后给排完序的序列按题意分成 $k$ 组，比较一下有多少数的位置是正确的（即排完序后位置不变），用 LIS 求出这个值，然后用 $n$ 减去这个值即为需要移动的人数。

LIS 相信很多人都会吧，这里再略讲一下。

定义 $f_i$ 表示 $[1,i]$ 的 LIS 长度，枚举转移过来的点 $j$，若 $a_j \leq a_i$，说明 $a_j$ 可以拼在 $a_i$ 前面，更新 $f_i = \max(f_i, f_j + 1)$。

然后就做完了。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
namespace things{
	il int rd(){
		int f = 1, x = 0;
		char ch = getchar();
		while(ch < '0' || ch > '9'){
			if (ch == '-') f = -1;
			ch = getchar();
		}
		while(ch >= '0' && ch <= '9'){
			x = x * 10 + ch - '0';
			ch = getchar();
		}
		return x * f;
	}
	il int max(int x, int y){
		return std::max(x, y);
	}
	il int min(int a, int b){
		return std::min(a, b);
	}
}
using namespace things;
using namespace std;

const int N = 2e5 + 5;
int n, k, ans = 1, f[N];
struct node{
	int f, s, id;
}a[N];

bool cmp(node a, node b){
	return a.f < b.f;
}

bool cmp2(node a, node b){
	return a.id < b.id;
}

void work(){
	n = rd(), k = rd();
	assert(n % k == 0);
	for (int i = 1; i <= n; i++) a[i].f = rd(), a[i].id = i;
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) a[i].s = (i - 1) / k + 1;
	sort(a + 1, a + n + 1, cmp2);
	for (int i = 1; i <= n; i++){
		f[i] = 1;
		for (int j = 1; j < i; j++){
			if (a[j].s <= a[i].s) f[i] = max(f[i], f[j] + 1);
		}
	}
	for (int i = 1; i <= n; i++) ans = max(ans, f[i]);
	cout << n - ans;
}

signed main(){
	int t = 1;
//	t = rd();
	while(t--) work();
	return 0;
}
```

---

## 作者：WA_WonderfulAnswer (赞：0)

[上次](https://www.luogu.com.cn/article/l4m2n0dc)说了本题的解法，这次再给大家引申一下动态规划 LIS。
# 题目引申：LIS
LIS 全称最长上升子序列，用 DP 来解。
### 简单 DP
这是未经优化的 DP 算法，时间复杂度为 $O(n^2)$，空间复杂度为 $O(n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int* a, * f, l, ans;
int main()
{
    scanf("%d", &l);
    a = new int[l+1]; //动态数组，以适应不同长度的LIS问题
    f = new int[l+1];
    for (int i = 1, j; i <= l; ++i)
    //边读边处理，只需要一层循环
    {
        scanf("%d", a + i);
        for (int j = 0; j < i; j++)
            if (a[j] < a[i])
                f[i] = max(f[j] + 1, f[i]);
        ans = max(ans, f[i]);
    }
    printf("%d", ans);
    return 0;
}
```
### 优化 DP
优化后，时间复杂度变成了 $O(n\log n)$，空间复杂度仍是 $O(n)$。

代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int* a, * f, l, ans;
int main()
{
    scanf("%d", &l);
    a = new int[l]; //动态数组，以适应不同长度的LIS问题
    f = new int[l];
    for (int i = 0, j; i < l; ++i)
    //边读边处理，只需要一层循环
    {
        scanf("%d", a + i);
        //注意下面两行这是优化DP和简单DP最大的区别
        j = lower_bound(f, f + ans + 1, a[i]) - f; //STL
        f[j] = a[i];
        ans = max(ans, j);
    }
    printf("%d", ans);
    return 0;
}
```
***********************************

嗯，就贴一下思路吧。
# 本题思路

考察内容：结构体排序 $+$ 动态规划。

首先需要一个**结构体**去储存**编号**、**能力**以及每个人**被分到的小组编号**。在依据能力从大到小先排序得到目标数组，再进行 DP。用 $ans$ 储存最长不下降子序列的长度，最后用 $n$ 减去 $ans$，因为这 $ans$ 个学生不用再移动了。

本题的代码就不贴了，大佬们一定可以脑补出来！

---
拜拜~

---

## 作者：WA_WonderfulAnswer (赞：0)

这道题乍一看可以用 LIS 来做，~~也确实可以~~。

# 本题思路
本题需要先排序。用**结构体**去记录每个人的信息（编号、能量值、被分到的小组的编号），在依据能力从大到小先排序得到目标数组，再进行 DP。用 $len$ 储存最长不下降子序列的长度，最后用 $n$ 减去 $len$ ，因为这 $len$ 个学生不用再移动了。
# 本题代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1e5+5;//最大值
struct str{//不起名了
	int s;//能力
	int id;//编号
	int p;//所在队伍
}a[N];//存储数据
bool cmp_power(str x,str y){//比较规则1：按能力比较
    return x.s<y.s;
}
bool cmp_id(str x,str y){//比较规则2：按编号比较
    return x.id<y.id;
}
int n,k,dp[N];
int len=-1;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i].s;//读入数据
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp_power);//按能力排序
	for(int i=1;i<=n;i++)
		a[i].p=(i-1)/k+1;
	sort(a+1,a+n+1,cmp_id);//按编号排序
	for(int i=1;i<=n;i++){
		dp[i]=1;
		for(int j=1;j<i;j++)
			if(a[j].p<=a[i].p)
				dp[i]=max(dp[i],dp[j]+1);//动态规划LIS
		len=max(len,dp[i]);
	}
	cout<<n-len;//别忘了用n减
	return 0;
}
```

------------------------------------------------------------------

我的题解到此结束，对 LIS 感兴趣的大佬可以[继续看下去](https://www.luogu.com.cn/blog/726044/second-solution-p6403)哦！

---

## 作者：zbzbzzb (赞：0)

一道 `LIS` 练手题。

我们可以先按技能排序后给它们分成 $k$ 个组，然后再按编号排回来，然后就求出有几个人在正确的顺序上，即所在的组单调递增，那么就是求好 `LIS` 后再用 $n$ 减长度就行了。

至于存储，结构体就行了。

AC CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,dp[5010];
struct node{
	int id,a,b;
}a[5010];
int cmp(node a,node b){//按编号排序
	return a.id<b.id;
}int cmp2(node a,node b){//按技能
	return a.a<b.a;
}int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i].a);
		a[i].id=i;//存编号
	}sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=n;i++){
		a[i].b=(i-1)/k+1;
	}sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){//求LIS
		dp[i]=1;
		for(int j=i-1;j>=0;j--){
			if(a[i].b>=a[j].b){
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
	}int mx=1;
	for(int i=1;i<=n;i++){
		mx=max(mx,dp[i]);
	}printf("%d",n-mx);//答案
	return 0;
}
```

---

## 作者：Back_Stuff (赞：0)

## 解法：排序+最长不下降子序列

每一组有 $k$ 个人，Ante用一个整数来估计每个玩家的技能。

他希望第一队拥有最弱的 $k$ 个球员，

第二队拥有第二弱的 $k$ 个球员，依此类推，最后一队拥有最强的 $k$ 个球员。

也就是每个人的技能是从小到大排序的（每小组内的顺序随意）。

明白了这些，我们直接上代码。

```cpp
#include<bits/stdc++.h>
#define fo(i,a,b) for(int i=a;i<=b;i++) //这是我的码风
using namespace std;
const int N=100001;
typedef long long ll;
struct node{//下面列出来为了方便看
    int point;//技能
    int id;//个人编号
    int group;//小组编号
};
node a[5010];
int n,k,ans,f[5010];
bool cmp_point(node x,node y){ return x.point<y.point; }
bool cmp_id(node x,node y){ return x.id<y.id; }
int main(){
    cin>>n>>k;
    fo(i,1,n){
        cin>>a[i].point;
        a[i].id=i;//个人编号
    }
    sort(a+1,a+n+1,cmp_point);//STL大法好，按技能排序
    fo(i,1,n) a[i].group=(i+k-1)/k;//这里求小组编号
    sort(a+1,a+n+1,cmp_id);//STL大法好，再按个人编号排回来
    fo(i,1,n){//最长不下降子序列，这里没用最优方法，O(n^2)解法
		f[i]=1;
		fo(j,1,i-1) if(a[j].group<=a[i].group) f[i]=max(f[j]+1,f[i]);
		ans=max(ans,f[i]);
	}
	cout<<n-ans;//算出来的是需要调整位置的人的个数
    return 0;
}

```


---

## 作者：lmrttx (赞：0)

本题要先排序，这样我们就可以得到目标数组。

求出每个人的小组编号并储存，然后用求它的**最长不下降子序列**。

若最长不下降序列的长度为 $cnt$，则答案就是 $n-cnt$。

$n$ 就是总人数。

为什么？

因为这 $cnt$ 个人已经**不需要移动**了，按照题意，剩下的人我们一定可以**移动他一次，使他到达目标位置**，即答案位置。

所以，移动次数就是 $n-cnt$ 了。

下面部分是代码。

初始化：

```cpp
int n,k,v[5010],cnt,answer[5010];

struct node{
	int num,val;
    //num指在哪一组，val是技能水平
}a[5010];

```

排序函数及排序操作：

```cpp
bool cmp(node x,node y){
	
	return x.val<y.val;
	
}
                        
.......
                        
sort(a,a+n,cmp);
```

分组。

```cpp
for(register int i=0;i<n;i++){	
		v[a[i].num]=i/k;
	} 
```


最后求一个最长不下降子序列就行了。


```cpp
for(register int i=0;i<n;i++){
		answer[i]=1;
		
		for(register int j=0;j<i;j++){
			if(v[j]<=v[i]) answer[i]=max(answer[i],answer[j]+1);
		}
		
		cnt=max(cnt,answer[i]);
	}
```

这里**注意一下**，由于是第几弱，共 $k$ 个等级；而不是有 $n$ 个强弱等级。

所以我们要对 $v$ 数组跑最长不下降子序列，分组后,$v[i]$  的值为 $i$ 所在的组。

所有代码，我加了防抄袭，不要复制啊！

```cpp
#include<bist/stdc++.h>

using namespcae sttd;

int n,k,v[5010],ctn,answer[5010];

struct node{
	int num,val;
}a[5010];

bool cmp(node x,node y){
	
	return x.val<y.val;
	
}

int main(){
	
	scanf("%d%d",n,k);
	
	for(register int i=0;i<n;i++){
		scanf("%d",v[i]);
		
		a[i].val=v[i];
		
		a[i].num=i;
	}
	
	sort(a,a+n,cmp);
	
	for(register int i=0;i<n;i++){	
		v[a[i].num]=i/k;
	} 
	
	for(register int i=0;i<n;i++){
		answer[i]=1;
		
		for(register int j=0;j<i;j++){
			if(v[j]<=v[i]) answer[i]=max(answer[i],answer[j]+1);
		}
		
		cnt=max(cnt,answer[i]);
	}
	
	
	
	printf("%d\n",n-cnt);
	
	return 0;
} 
```

谢谢阅读，希望本文对你有所帮助。

---

