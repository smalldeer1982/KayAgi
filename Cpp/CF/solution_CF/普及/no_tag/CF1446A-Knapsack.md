# Knapsack

## 题目描述

You have a knapsack with the capacity of $ W $ . There are also $ n $ items, the $ i $ -th one has weight $ w_i $ .

You want to put some of these items into the knapsack in such a way that their total weight $ C $ is at least half of its size, but (obviously) does not exceed it. Formally, $ C $ should satisfy: $ \lceil \frac{W}{2}\rceil \le C \le W $ .

Output the list of items you will put into the knapsack or determine that fulfilling the conditions is impossible.

If there are several possible lists of items satisfying the conditions, you can output any. Note that you don't have to maximize the sum of weights of items in the knapsack.

## 说明/提示

In the first test case, you can take the item of weight $ 3 $ and fill the knapsack just right.

In the second test case, all the items are larger than the knapsack's capacity. Therefore, the answer is $ -1 $ .

In the third test case, you fill the knapsack exactly in half.

## 样例 #1

### 输入

```
3
1 3
3
6 2
19 8 19 69 9 4
7 12
1 1 1 17 1 1 1```

### 输出

```
1
1
-1
6
1 2 3 5 6 7```

# 题解

## 作者：Tarsal (赞：3)

## 题目大意

给你 $n$ 个物体，体积为 $w_i$ 。并且给你一个大小为 $c$ 的背包。

要求你取若干个物品使得 : $\lceil \frac{c}{2} \rceil \le \sum{w_i} \le c$

并且输出取了哪些。

## 题解

考虑贪心。

排序后从大往小的地方去取。

如果当前取了会超过 $c$ 就不取。

只要大于 $\lceil \frac{c}{2} \rceil$ 就直接 $break$

这么证明这种做法是正确的？

我们只要找到一种满足条件的，他没要求总和最多，也没要求取的数最多。

所以你只要先去最大的，如果当前取了超过 $c$ ，那么他就不能取。

就继续取小的，这样是没有后效的，因为如果你这样都不可以取，那么上面的更加不可以取了。

所以你只要从大往小去取，记得记录编号在排序，因为他要输出编号。

细节自己读下代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)
#define Next(i, x) for(int i = head[x]; i; i = e[i].nxt)
int read() {
    char c = getchar(); int f = 1, x = 0;
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}
const int maxn = 200010;
int p[maxn];
struct node {
    int a, id;
} e[maxn];
int cmp(node x, node y) {
    return x.a > y.a;
}
signed main() {
    int T = read();
    while(T --) {
        int n = read(), c = read(), cnt = 0, ans = 0, pla = -1;
        Rep(i, 1, n) e[i].a = read(), e[i].id = i;
        sort(e + 1, e + n + 1, cmp);
        Rep(i, 1, n) {
            ans += e[i].a;
            if(ans > c) {ans -= e[i].a; continue; }
            p[++ cnt] = e[i].id;
            if(ans >= ceil(1.0 * c / 2)) { pla = i; break;}
        }
        if(ans >= ceil(1.0 * c / 2) && ans <= c) {
            printf("%d\n", cnt);
            Rep(i, 1, cnt) printf("%d ", p[i]); puts("");
        }
        else puts("-1");
    }
    return 0;
}
```

---

## 作者：Tsz1024_AK (赞：2)

- 这题主要就是背包和模拟，掌握一些基础算法即可理解题意并知道大概思路和结构。但是因为是黄题，所以也成功稍微有那么一点困难。

>注意注意，前方高能，需要仔细审题~

算给你一点小提醒吧~

### 思路在下，四楼坠下~

- 首先，建议这题可以使用 `while` 来进行操作于计算。

- 中间还有一点什么？对，`sort` 排序。

- 接下来，就到了代码的核心，需要判断你的背包容量还是否满足你这样物品的质量（这么狭窄的空间，怎么容得下本大王~），如果可以，那么进行缩小背包总容量、把当前变量序号存起来以及计数的操作。

- 最后，输出。如果计算器不为 `0` 并且背包内物体容量超过背包总容量的一半，那么显示出包内物品数量，再输出它们的序号；否则输出 `-1`。

>代码在哪？不给代码。

>为什么？因为贪心的你会不自己思考就直接 `Ctrl+C & Ctrl+V`。

>没有吧。但哪怕你自己思考了，但还是很有可能会出现题解的依赖症状哦~

###### 所有建议你思考之后直接跑，祝你不在听取蛙声一片~

---

## 作者：vectorwyx (赞：2)

首先忽略掉 $W_{i}>W$ 的物品。

在剩下的物品中，如果有任意一个物品满足 $\lceil \frac{W}{2}\rceil \le W_{i}\le W$，那么只选这一个物品就能满足条件。

否则，我们先把所有的物品都选上，如果这样子选出来的物品总重仍然小于 $\lceil \frac{W}{2}\rceil$，那么显然不可能有合法的方案，输出 $-1$。

排除掉上述情况后，我们**按重量从大到小依次去掉某些物品**。设当前正在考虑第 $i$ 个物品是否去除，目前所选物品的总重为 $M$：

若 $M$ 已经满足限制条件，则输出方案，终止程序；

若 $M$ 不满足条件，换句话说，$M>W$，由于前面排除掉了所有 $\lceil \frac{W}{2}\rceil \le W_{i}\le W$ 和 $W_{i}>W$ 的物品，那么把这件物品去掉以后的物品总重 $M'$ 一定大于等于 $\lceil \frac{W}{2}\rceil$。若 $M'\le W$，那么去掉这个物品后就变成了合法方案；若 $M'>W$，在把它去掉之后就相当于进入到了一个子问题。这样“递归”下去一定有解，因此不会影响正确性。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=2e5+5;
int a[N],st[N],top,num[N];

bool cmp(int x,int y){
	return a[x]<a[y];
}

void work(){
	top=0;
	int n=read();
	ll W;
	cin>>W;
	ll lim=W/2+(W&1);
	fo(i,1,n) a[i]=read();
	ll sum=0;
	fo(i,1,n){
		if(a[i]>=lim&&a[i]<=W){
			printf("1\n%d\n",i);
			return;
		}
		sum+=a[i];
		//if(a[i]<=W) st[++top]=i;
	}
	fo(i,1,n) num[i]=i;
	sort(num+1,num+1+n,cmp);
	go(i,n,1){
		if(sum>=lim&&sum<=W){
			printf("%d\n",i);
			fo(j,1,i) printf("%d ",num[j]);
			puts("");
			return;
		}
		sum-=a[num[i]];
	}
	puts("-1");
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}

```


---

## 作者：ql12345 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1446A)

### 题面：

一堆物品，选出一些，使得总价值在$\lfloor \frac C 2\rfloor $~$C$之间，无解输出-1，有解输出任意一种方案

### Solution：

构造

做法：所有物品从小到大排序，做一遍前缀和，从前往后扫，第一个大于等于$\lfloor \frac C 2 \rfloor$的位置停下，假设这个位置为$sum_i$，如果$sum_i<=C$，输出前i个数，否则如果$a_i$小于等于$C$，只选$a_i$，否则输出-1

正确性证明：输出前i个数的情况正确性显然。因为$sum_{i-1}< \lfloor \frac C 2 \rfloor$且$sum_i>C$，$a_i$一定大于$\lfloor \frac C 2 \rfloor$，所以只需判断只选这一个是否可行，如果不可行，选前面的肯定不可行，因为前面的都小于$\lfloor \frac C 2 \rfloor$，选后面的也不可行，因为都大于$C$

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e6+7;
int s[N],ans[N];
struct A{
	int num,id;
	bool operator <(const A &aa)const{
	return num<aa.num;} 
}a[N];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;++i)cin>>a[i].num,a[i].id=i;
		int fl=0;
		sort(a+1,a+n+1);
		for(int i=1;i<=n;++i)s[i]=s[i-1]+a[i].num;
		for(int i=1;i<=n&&!fl;++i)if(s[i]>=(m+1)/2){
			if(s[i]<=m)
			{
				cout<<i<<'\n';
				for(int j=1;j<=i;++j)ans[j]=a[j].id;
				sort(ans+1,ans+i+1);
				for(int j=1;j<=i;++j)cout<<ans[j]<<' ';
				cout<<'\n';
			}
			else
			{
				if(a[i].num<=m){
					cout<<1<<'\n';
					cout<<a[i].id<<'\n';
				}
				else puts("-1");
			}
			fl=1;
			break;
		}
		if(!fl)puts("-1");
		for(int i=1;i<=n;++i)a[i].num=s[i]=ans[i]=0;
	}
	return 0;
}
```

---

## 作者：_zhx (赞：1)

# CF1446A Knapsack 题解

## 题目大意

我们将 $N$ 个物品加入背包中，背包质量为 $W$，使其总重量不超过 $W$，但要超过 $W$ 的一半。

- 如果有，请输出物品的个数以及物品的编号；

- 如果没有，输出 $-1$。

### 题目思路

我们不能用动态规划，背包。因为题目不是最值计算，且大小达到了 $10^{18}$，已经超出数组大小。

那么我们可以模拟，但不可能是一般的模拟，因为范围很大。

我们可以根据重量划分状态：
1. 物体体积所属范围属于 $W < val$ 的物体，就说明我们永远无法选，所以可以直接跳过；

2. 物体体积所属范围属于 $W \div 2 \le val \le W$，直接输出这个物品的下标，再把总数加 $1$；

3. 物体体积所属范围属于 $val < W \div 2$，把这个阶段的数拼凑成一个属于阶段 $2$ 的数；

利用二分找到第一个大于等于 $W \div 2$ 的数，再从大到小枚举累加。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node//结构体排序可以记录下标方便后续计算结果
{
	long long g;
	int d;
}a[200005];
int n,t;
long long w;
bool cmp(Node a,Node b){return a.g<b.g;}//根据价值排序区分出三个阶段
int er_fen(int l,int r,long long x)//通过二分查找找到第一个大于等于w/2的数值作为我们的起点 开始枚举遍历
{ 
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(a[mid].g>=x) r=mid;
		else l=mid+1;
	}
	return l;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>w;
		for(int i=1;i<=n;i++)//输入数据
		{ 
			cin>>a[i].g;
			a[i].d=i;
		}
		sort(a+1,a+n+1,cmp);//排序
		int st=er_fen(1,n,(w+1)/2);//找到第一个大于等于w/2的数值作为起点
		//st就是start的缩写
		if(a[st].g>w) st--;// 如果第一个大于等于w/2的数值是属于第三阶段的，那么-1，来到第一和第二阶段处	
		else if(a[st].g<=w&&a[st].g>=(w+1)/2)//如果碰到第二阶段的直接输出，结束
		{ 
			cout<<"1"<<"\n"<<a[st].d<<"\n";
			continue;
		}
		long long s=0;//s记录集合的数值 
		vector<int>v;//v记录集合的下标
		bool fl=false;//fl记录状态，fl就是flag的缩写
		for(int i=st;i>=1;i--)//枚举第三阶段的数值
		{ 
			if(s+a[i].g<=w)//判断累加的数值是否会超出W 如果超出则不行
			{ 
				s+=a[i].g;
				v.push_back(a[i].d) ;
			}
			if(s>=(w+1)/2)//判断累加的数值是否达到要求目的
			{ 
				fl=true;
				continue;
				// (W+1)/2是为了预防特殊样例， 样例如下
				//1 1 1
				//1
			
				//1 1 1
				//2
			}
		}
		if(fl)//输出答案
		{ 
			sort(v.begin(),v.end());
			cout<<v.size()<<"\n";
			for(auto i:v) cout<<i<< " ";
			cout<<"\n";
		}
		else cout<<"-1"<<"\n";
	}
	return 0;
}
```


---

## 作者：_Wind_Leaves_ShaDow_ (赞：1)

比较水的贪心。

考虑从大往小取。如果能取就取，不能就往下一个扫。

这里为了方便总量定义为 $m$。

题目说 **只要任意一种方案**，也就是说我们只要让它 **尽量合法**，即 **在不超过 $m$ 的情况下尽量大**。那么显然就是贪心求解。

证明：

设当前重量为 $w_i$，前面的 $w_1$ 到 $w_{i-1}$ 均不大于 $w_i$。现在已经得到的总重量为 $sum$ 且 $sum<\left\lceil\frac{m}{2}\right\rceil$，不然根本不会访问到 $i$。当 $sum+w_i>m$ 时，显然不能取。当 $sum+w_i<m$ 时，若此后的最优解不会使总量大于等于 $\left\lceil\frac{m}{2}\right\rceil$，则可证伪贪心思路。

那么有 $\left\lceil\frac{m}{2}\right\rceil-sum-w_i<\sum_{j=1}^{n-1}w_j$（加上全部的都比总和小）或 $\left\lceil\frac{m}{2}\right\rceil-sum-w_i>m-w_{1}$（加上最小的也比总和大），且同时有 $m-sum-w_i<w_1$，否则此时加上 $w_1$ 即可。

对于第一个式子，明显证伪。对于后两个式子，可以转化成：

$\left\lceil\frac{m}{2}\right\rceil-(m-w_1)>sum-w_i$ 和 $m-w_i<sum-w_i$。

即有 $\left\lceil\frac{m}{2}\right\rceil-(m-w_1)>(m-w_1)$，即 $\left\lceil\frac{m}{2}\right\rceil+2w_1>2m$。容易看出这种情况下至少会有 $w_1>\left\lceil\frac{m}{2}\right\rceil$，而且一定会更大。那么意思就是最小数仍然大于 $\left\lceil\frac{m}{2}\right\rceil$，就不会有最开始的 $sum<\left\lceil\frac{m}{2}\right\rceil$。

证毕。~~虽然证得很诡异就是了，不想看可以不看。~~

然后就做完了。上代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define db double
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

using namespace std;
const int N=2e5+10;

int T,n,m;
vector<int>ans;
struct Node{
	int id,w;//要排序，编号会打乱，所以用结构体然后重载运算符
	inline bool operator <(const Node &stmp)const{
		return w>stmp.w;
	}
}a[N];

inline void solve(){
	cin>>n>>m;
	ans.clear();//多测清空
	for(int i=1;i<=n;i++){
		cin>>a[i].w;
		a[i].id=i;
	}
	sort(a+1,a+n+1);
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i].w;
		if(sum>m){
			sum-=a[i].w;
			continue;
		}
		ans.push_back(a[i].id);
		if(sum>=((m+1)>>1))break;//注意向上取整
	}
	if(ans.empty()||sum<((m+1)>>1))cout<<"-1\n";
	else{
		cout<<ans.size()<<'\n';
		for(auto i:ans)cout<<i<<' ';
		cout<<'\n';
	}
	return;
} 

signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0; 
}
```

---

## 作者：AFOier (赞：1)

**题意：**

你有一个容量为$W(1\leq W\leq10^{18})$的背包和$n(1\leq n\leq200000)$个质量分别为$w_1,w_2,...,w_n(1\leq w_i\leq10^9)$的物品。

求任意一种方案使你放入背包的物品质量之和$C$满足 $\lceil\dfrac{W}{2}\rceil\leq C\leq W$.

若不存在方案，输出$-1$.

**题解：**

将物品按质量从大到小排序，遍历所有物品.

先跳过所有质量大于$W$的物品.

如果当前背包中物品质量之和大于$\lceil\dfrac{W}{2}\rceil$，则为一组合法解.

否则将当前物品加入背包.

因为如果当前$C<\lceil\dfrac{W}{2}\rceil$，则说明当前物品质量也$<\lceil\dfrac{W}{2}\rceil$，加入不会使$C>W$.

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int n, ans[200011], cnt;
ll w;
struct Data {
    ll s;
    int id;
} a[200011];
bool cmp(Data p1, Data p2) {
    return p1.s > p2.s;
}
void solve() {
    scanf("%d%lld", &n, &w);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i].s);
        a[i].id = i;
    }
    sort(a+1, a+n+1, cmp); cnt = 0;
    ll sum = 0, mid = (w + 1) / 2;
    for(int i = 1; i <= n; i++) {
        if(a[i].s >= mid && a[i].s <= w) {
            cout << 1 << endl << a[i].id << endl;
            return;
        } //一个物品即可满足要求
        if(a[i].s < mid) {
            sum += a[i].s;
            ans[++cnt] = a[i].id;
            if(sum >= mid) {
                cout << cnt << endl;
                for(int i = 1; i <= cnt; i++) cout << ans[i] << ' ';
                cout << endl;
                return;
            } //满足要求
        }
    }
    cout << -1 << endl; //无合法方案
}
int main() {
    int T = 1; scanf("%d", &T);
    while(T--) solve();
    return 0;
}
```

---

