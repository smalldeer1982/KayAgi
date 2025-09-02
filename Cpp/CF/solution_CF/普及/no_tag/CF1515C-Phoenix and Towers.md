# Phoenix and Towers

## 题目描述

凤凰菲克斯有 $ n $ 个方块，分别高 $ h_1,h2,\dots,h_n $，所有 $ h_i $ 都不超过 $ x $ 。他计划将 $ n $ 个方块堆叠成 $ m $ 座塔。为了让塔看起来更漂亮，没有两座塔的高度差可以超过 $ x $ 。

请帮助菲克斯建造 $ m $ 座漂亮的塔，每个塔必须至少由一个方块构成，并且必须使用所有方块。

## 样例 #1

### 输入

```
2
5 2 3
1 2 3 1 2
4 3 3
1 1 2 3```

### 输出

```
YES
1 1 1 2 2
YES
1 2 2 3```

# 题解

## 作者：45dino (赞：12)

题目大意：

- 给定 $n$ 块积木，每块积木都有一个小于 $x$ 的高度，要将这 $n$ 块积木分成 $m$ 堆非空的集合，且满足任意两集合的高度和的差都不大于 $x$，求任意一种构造方案。

- $1≤n,m≤10^5$

$\mathcal{Analysis}$

这一题其实大有学问。

法一：
可以用优先队列解决本题。每次取出当前高度和最小的一堆，加入一块积木。最后判断最大高度和最小高度差是否大于 $x$即可。
时间复杂度:$\Theta(log_2n)$

[赛时代码](https://codeforces.com/contest/1515/submission/114905004)

**补充**

可以证明，必然存在一组解。
因为每一堆积木的高度都小于 $x$，所以每次加入一个数都能保证当前最大值和当前最小值的差是小于 $x$ 的。

这就说明需要充分利用题目给定的特殊性质。

法二：

[参考代码1](https://codeforces.com/contest/1515/submission/114869879) by [$\color{black}d \color{red}uality$](https://codeforces.com/profile/duality)

其实没有必要用优先队列之类的STL，可以直接构造。

将原积木序列按高度从小到大排序，第一个放在第一堆，第二个放在第二堆……依次类推。

根据规则，在放第 $i$ 堆的时候，前 $i-1$ 堆都比它多放一块积木，且该积木的高度大于等于该堆除这块积木的高度和与第 $i$ 堆的高度和的差。换句话说，前 $i-1$ 堆当前的高度不小于第 $i$ 堆。根据规则，第 $i+1$ 堆到第 $m$ 堆每一堆的积木的个数与第 $i$堆相同，且不小于于第 $i$ 堆的相应积木的高度，故第 $i+1$ 堆到第 $m$ 堆每一堆的积木高度都不小于第i堆。

综上，第 $i$ 堆此时是高度总和最小的一堆。

这样就能保证每次都放在最小的那一堆。

---

## 作者：Tachibana27 (赞：4)

由于高度不超过 $x$，所以显然全部是 ```YES```。

反证：假设会出现高度超过 $x$ 的两组，那么不妨让更高的那一组给更低的那一组一个方块。

根据上面的结论，我们只需维护 $m$ 组高度之和，每一次选择总和最小的加上方块即可。

code:

```cpp
int n,m,x;
class node{
	public:
		int id;
		int v;
		int ans;
}a[1000086];
int t;
std::priority_queue<std::pair<int,int> >q;
signed main(){
	std::cin>>t;
	while(t--){
	std::cin>>n>>m>>x;
	while(not q.empty())
	    q.pop();
	for(int i=1;i<=m;i++)
		q.push(std::make_pair(0,i));//维护m组的和
	for(int i=1;i<=n;i++)
		std::cin>>a[i].v;
// 	std::sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++){
		int qwq=q.top().first;
		int awa=q.top().second;
		q.pop();
		qwq*=-1;//大根堆转小根堆的经典操作
		qwq+=a[i].v;
		a[i].ans=awa;
		qwq*=-1;
		q.push(std::make_pair(qwq,awa));
	}
	puts("YES");
// 	std::sort(a+1,a+1+n,cmp2);
	for(int i=1;i<=n;i++)
		std::cout<<a[i].ans<<" ";
		puts("");
	}
	return 0;//撒花
}
```

---

## 作者：kevin1616 (赞：3)

### 审题
将 $n$ 个积木分成 $m$ 组，使得任意两组的高度和之差不超过 $x$。
***
### 思路
这题如果单看题面，优先队列做法是很好想的。可是一看数据范围 $1\le h_i\le x$，就可以想到一种构造做法。

众所周知，分组是不需要考虑顺序的。所以我们可以先将数组排序，使得后面的处理更方便。

由于每个积木的高度都小于 $x$，所以可以尝试在每 $m$ 个积木里第一个积木放到 $1$ 组，第二个积木放到 $2$ 组，以此类推。

如何证明这个方法？由于我们是每 $m$ 个积木里往所有的组加入一个积木，所以积木数量最多的组比最少的组的个数最多多 $1$ 个积木，而且积木数量最多的组的编号要比最少的编号小。因为按照我们从小到大的排序，所以积木数量最多的组去掉多出来的积木后得出的高度小于等于积木数量最少的组的高度，且差值必然小于等于相邻两个数的最大差值，这个值必然小于 $x$。再加上多出来的积木（也有可能没有多出积木），所以最后的差值也不会超过 $x$，证毕。

所以只要满足题目数据，必然不会有不可能的情况。最后恢复输入顺序，输出即可。
***
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct asdf{
    int x,id,num;
    //x是高度，id是读入顺序，num是分组
};
int t,n,m,x;
asdf h[1000005];
bool cmp(asdf a,asdf b){ //按高度从小到大排序
    return a.x < b.x;
}
bool cmp2(asdf a,asdf b){ //按输入顺序从前到后排序
	return a.id < b.id;
}
int main(){
    ios::sync_with_stdio(0); //关闭流同步，加快读入输出效率
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--){ //多组询问
        cin >> n >> m >> x;
        for(int i = 1;i <= n;i++){
            cin >> h[i].x;
            h[i].id = i;
        }
        sort(h + 1,h + n + 1,cmp); //排序
        for(int i = 1;i <= n;i++){ //将每m个数中第x个数分到第x组
            h[i].num = i % m;
            if(h[i].num == 0) h[i].num = m;
        }
        sort(h + 1,h + n + 1,cmp2); //恢复顺序，输出
        cout << "YES\n";
        for(int i = 1;i <= n;i++) cout << h[i].num << " ";
        cout << "\n";
    }
    return 0; //好习惯
}
```
不抄题解，从我做起！

---

## 作者：Adam1101 (赞：3)

### [题目传送门](https://www.luogu.com.cn/problem/CF1515C)

### 题意简述
给定 $ n $，$ m $，$ x $，在给出有 $ n $ 个元素的序列 $ h $，其中 $ h_i \le x $，求将其分为 $ m $ 组，且任意两组的元素之和的差值都不超过 $ x $。若无解输出 `NO`。

### 分析
很多大佬都使用的是优先队列，但本蒟蒻使用的是一个很好想的构造法。

首先发现因为每个 $ h_i $ 都不大于 $ x $，所以不存在无解的情况。

接着将 $ h $ 从小到大排序，因为既这样不会影响分组的结果，又能方便构造。

接下来将每 $ m $ 个元素中的第 $ i $ 个元素分到第 $ i $ 组。

最后按照输入的顺序排序，在输出即可。

### 为什么是正确的
排序后 $ h $ 单调不减，第 $ i $ 组的大小一定小于前 $ i - 1 $ 组的大小，因为它们比第 $ i $ 组多添加了一个元素，而后 $ m - i $ 组每一次加入的元素大小都大于或等于第 $ i $ 组添加的元素，所以它们的大小也大于或等于第 $ i $ 组。

所以，第 $ i $ 组是当前所有组中大小最小的。

又 $ h_i $ 一定是前 $ i $ 个元素中最大的，所以我们每次都将最大的元素加入了最小的分组，一定最优。

而根据题目推理得，一定存在至少一组解，所以我们选得的这一组最优解一定满足要求。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Fk{ //定义结构体存储
	int h;
	int id;
	int zb;
}a[1000010];

bool cmp(Fk x, Fk y) { //按高度从小到大排序
	return x.h < y.h;
}

bool cmp2(Fk x, Fk y) { //按原序排列
	return x.id < y.id;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int n, m, x;
		cin >> n >> m >> x;
		for (int i = 1; i <= n; i++) { //输入
			cin >> a[i].h;
			a[i].id = i;
		}
		
		sort(a + 1, a + n + 1, cmp); //排序
		
		for (int i = 1; i <= n; i++) { //分组
			a[i].zb = i % m;
			if (a[i].zb == 0) a[i].zb = m;
		}
		
		sort(a + 1, a + n + 1, cmp2); //排回原序
		
		cout << "YES\n"; //一定有解
		
		for (int i = 1; i <= n; i++) { //输出方案
			cout << a[i].zb << " ";
		}
		cout << "\n";
	}
	return 0;
}
```

---

## 作者：Cold_Eyes_bystander (赞：3)

这题是模拟赛出的题，考场忘记如何写成员函数了，希望大家不要像我一样。

这题我们先按前 $m$ 大的数，放入 $m$ 组中，每组一个数。

我们用优先队列维护，每次选出总和最小的一组，将剩下的最大的数放入那一组，因为题目保证 $h_i \le x$，所以这种贪心是可行的。

证明：最小的那一组加上某个数后，和其他组的差距最多是
$x$，下一次选完，差距也小于 $x$，所以这是正确的。

```c++
#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int N=1e6+1;
struct Stu
{
	int a,id;
	friend bool operator <(const Stu a1,const Stu id1)
	{
		if(a1.a!=id1.a)
		{
			return a1.a>id1.a;
		}
		else
		{
			return a1.id>id1.id;
		}
	}
}a[N];
bool cmp(Stu x,Stu y)
{
	return x.a>y.a;
}
int c[N];
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,m,x;
		cin>>n>>m>>x;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].a;
			a[i].id=i;
		}
		sort(a+1,a+n+1,cmp);
		priority_queue<Stu>qqq;
		for(int i=1;i<=m;i++)
		{
			Stu x;
			x.a=a[i].a;
			x.id=i;
			qqq.push(x);
			c[a[i].id]=i;
		}
		for(int i=m+1;i<=n;i++)
		{
			int minn=1e18,minnid=0;
			Stu x=qqq.top();
			qqq.pop();
//			cout<<x.a<<endl;
			x.a+=a[i].a;
			c[a[i].id]=x.id;
			qqq.push(x);
		}
		cout<<"YES\n";
		for(int i=1;i<=n;i++)
		{
			cout<<c[i]<<" ";
		}
		cout<<"\n";
	}
	
	return 0;
}
```

---

## 作者：zzb1217 (赞：2)

# [题目链接](https://www.luogu.com.cn/problem/CF1515C)
## 题目简述
给你一个长度为 $n$ 的序列 $h$，其中任意两个元素的差都小于 $x$，求是否可以满足将其分为 $m$ 组使得任意两组的和之差小于 $x$。

若可以，输出 `YES` 并输出一种可行方案，否则输出 `NO`。
### 分析
我们可以发现不论如何，都存在一种方案，所以不存在输出 `NO` 的情况。 

其次，我们考虑排序，这样可以保证下一步分组的正确性 
#### 证明
由于 $h$ 中每个元素的差都小于 $x$，所以排序后再分组的话每个组的差的和一定不会大于 $x$，符合题意。

特殊的，我们要记录输入时每个数的编号，用结构体存起来再排序，否则输出答案时会很麻烦。
```cpp
bool cmp(node a,node b)
{
    return a.x<b.x;
}
stable_sort(a+1,a+n+1,cmp);
```
排完序后，想一想，要把 $n$ 个数平均分配在 $m$ 组里，这是我们可以想到**取模**！考虑排序后枚举 $1 \le i \le n$，对 $i$ 取模后将 $a_i$ 放入答案数组。 

特殊判断 $i \bmod m$ 是否为 $0$，如果是，则将 $a_i$ 放入第 $m$ 组。
```cpp
for (int i=1;i<=n;i++)
{
    int x=i%m;//取模
    if (x==0) x=m;//特殊判断
    ans[a[i].id]=x;//放入答案数组
}
```
最后再按照输入顺序输出答案就愉快的AC了！
```cpp
for (int i=1;i<=n;i++)
{
  cout << ans[i] << " ";
}
return 0;
```
完整~~不加注释~~代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int ans[N];
struct node
{
    int x,id;
}a[N];
bool cmp(node a,node b)
{
    return a.x<b.x;
}
int mian()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m,x;
        cin >> n >> m >> x;
        for (int i=1;i<=n;i++)
        {
            cin >> a[i].x;
            a[i].id=i;
        }
        stable_sort(a+1,a+n+1,cmp);
        for (int i=1;i<=n;i++)
        {
            int x=i%m;
            if (x==0) x=m;
            ans[a[i].id]=x;
        }
        puts("YES");
        for (int i=1;i<=n;i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
  return 0;
}
```
#### 拒绝抄袭！（代码有坑）。

---

## 作者：Z_AuTwT (赞：2)

## 题意

将若干个数放进几个组中，使每个组的差不超过某个值（题目保证若干个数也都不超过那个值）。

## 思路

考虑贪心，我们建立一个堆（优先队列），每次取出当前的最小值，将还没有放的数中的最大值加上它，并重新加入堆。

### 证明

因为我们可以保证在操作前序列中的最小值与最大值的差不超过某个值（初始全为 0），那么再加上不超过那个数的一个数后一样不超过那一个值。

## CODE

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
int ans[1000100];
main(){
// 	freopen("yui.in","r",stdin);
// 	freopen("yui.out","w",stdout);
    int t;
    cin>>t;
    while(t--){
        priority_queue<pair<int,int> >que;
        priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q;
    	int n,m,x;
    	cin>>n>>m>>x;
    	for(int i=1;i<=n;i++){
    		int dt;
    		cin>>dt;
    		que.push(make_pair(dt,i));
    	}
    	for(int i=1;i<=m;i++){
    		Q.push(make_pair(0,i));
    	}
    	while(!que.empty()){
    		auto Now=que.top();
    		que.pop();
    		auto NOW=Q.top();
    		Q.pop();
    		NOW.first+=Now.first;
    		ans[Now.second]=NOW.second;
    		Q.push(NOW);
    	}
    	puts("YES");
    	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    	puts("");
    }
	return 0;
}
```

---

## 作者：Echo_Long (赞：2)

### [Phoenix and Towers](https://www.luogu.com.cn/problem/CF1515C)

一开始用优先队列维护整个序列中的合并情况，发现很不好统计，打出来 WA 了几发。

正难则反，我们可以用优先队列维护整个序列中的 $m$ 个塔，从前往后扫一遍序列，对于每一个数，我们贪心地选取它在当前高度最低的塔上即可。

因为保证了每一个数都 $\le x$，那么序列中的每两个塔之间的差值都 $\le x$。

那么为最低的塔高 $val$ 加上一个 $\le x$ 的值 $k$，此时该塔高变为 $val+k$，设此时的最小塔高为 $val'$ 那么 $val\le val'$ 且 $k\le x$ 那么一定有 $val+k-val'\le x$，所以我们保证了按照我们的贪心策略，一定可以让序列中的每两个塔之间的差值都 $\le x$。

所以这样证明了原题没有无解的情况。

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define inl inline
#define eb emplace_back
#define ls p<<1
#define rs p<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define getchar() cin.get()
#define print(x) cout<<#x<<'='<<x<<endl
const int N = 1e5 + 5;

int read()
{
	int f = 1 , x = 0;
	char ch = getchar();
	while ( !isdigit(ch) ) { if ( ch == '-' ) f = -1; ch = getchar(); }
	while ( isdigit(ch) ) { x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 ); ch = getchar(); }
	return x * f;
}

int n , m , x , a[N] , vis[N] , cnt , ans[N];

vector<int> vec;
struct node { int id , val; friend bool operator < ( const node &a , const node &b ) { return a.val > b.val; } };
priority_queue < node > q;

signed main ()
{
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
    int T = read();
    while ( T -- )
    {
        while ( !q.empty() ) q.pop();
        n = read() , m = read() , x = read();
        for ( int i = 1 ; i <= n ; i ++ ) a[i] = read();
        for ( int i = 1 ; i <= m ; i ++ ) q.push({i,0});
        for ( int i = 1 ; i <= n ; i ++ )
        {
            node u = q.top(); q.pop();
            ans[i] = u.id;
            u.val += a[i];
            q.push(u);
        }
        cout << "YES" << endl;
        for ( int i = 1 ; i <= n ; i ++ ) cout << ans[i] << ' ';
        cout << endl;
    }
    return 0;
}
```

### 

---

## 作者：LinkZelda (赞：1)

- **题意** 给定 $n$ 个整数和 $x$ 与 $m$，保证任意整数大小 $\leq x$，求将这 $n$ 个整数划分为 $m$ 个集合使得每个集合中的数的和 $\leq x$。

- $Solution$:

考虑贪心，将每个集合的编号和所有数的和扔进一个按和的大小排序的小根堆里，每次将现在这个数放入堆顶集合即可。

- $prove$.

因为题目给出任意整数大小 $\leq x$ 这个条件，那么我们先将每个集合放入一个数，现在必定是满足题意的。

考虑后续的数，将现在正在放的第 $i$ 个数放入和最小的集合中，发现集合加入这个数后与次小集合的差也肯定是 $\leq x$ 的，由数学归纳法得知，原贪心策略成立。

同时上述过程也证明了没有无解的情况。

- [代码](https://www.luogu.com.cn/paste/98c2kkmr)

---

## 作者：mnlbnkk (赞：0)

# 写在前面
这道题目其实比较考思维，被当成了摸底测的第一题，结果本人状态过差，直接导致爆零……
# 题意
给定 $x$ 和 $m$ 以及一个长度为 $n$ 的序列 $a_i$，保证 $\forall 1\le i\le n\ a_i\le x$，要求你把 $a$ 分成 $m$ 组，要求满足每一组的和之差不超过 $x$，并输出方案。
# 思路
很明显，绝对是有一种分组方案满足要求的，这和做法有关：\
像我的做法就是模拟这 $m$ 个组加入数字的过程：\
每一次你把当前的数放在和最小的组里面，然后很明显，如果再放之前和最大的组与和最小的组之差不到 $x$ 那么加入了这个数之后，还是绝对满足这个性质的，所以绝对有答案。\
所以这样做法就水落石出了，只要每一次把当前这个数放到和最小的组里面就可以了，这个过程可以用堆维护，如果没看懂可以看代码理解一下。
# Code 
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+9;
int n,m,x,ans[N];
struct node{int h,id;}a[N];
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > >que;
inline bool cmp(node x,node y) {return x.h<y.h;}
signed main()
{
    int T;
    cin>>T;
    while(T--)
    {
        while(!que.empty()) que.pop();
        cin>>n>>m>>x;
        for(int i=1;i<=n;i++)
            cin>>a[i].h,a[i].id=i;
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=m;i++)
            que.push(make_pair(0,i));
        for(int i=1;i<=n;i++)
        {
            int x=que.top().second,y=que.top().first;que.pop();
            que.push(make_pair(y+a[i].h,x));ans[a[i].id]=x;
        }
        cout<<"YES\n";
        for(int i=1;i<=n;i++)
            cout<<ans[i]<<' ';
        cout<<endl;
    }
	return 0;
}
```

---

## 作者：鱼跃于渊 (赞：0)

## 1. 题意
给定 $n$ 个元素，第 $i$ 个元素有高度 $h_i$，均小于 $x$。现在要将其分成 $m$ 个组，要求高度和最大的组的高度和减去高度和最小的组的高度和，得到的差不超过 $x$。有 $t$ 组数据，问对于每个组是否有一个方案满足上述条件，如果有就输出这个方案。  
取值范围：$1\le t \le 10^3 ; 1\le m \le n \le 10^5,\sum n \le 10^5;1\le h_i \le x \le 10^4$。
## 2. 做法
我们考虑直接贪心，依次遍历每一把方块，将其放入当前价值和最小的组，用优先队列维护即可。  
证明一下这个做法的正确性：  
若我们当前遍历到点 $i$，优先队列中的最小值为 $min$，次小值为 $min'$，则有 $h_i\le x$ 和 $min \le min'$，整合两式可以得到：$min+h_i-min'\le x$。  
这个式子保证了此做法所构造出来的方案一定满足题意，同时也证明了不存在无解的情况。  
## 3. 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
struct node{
	int x,id;
	friend bool operator <(const node &x,const node &y){
		if(x.x!=y.x) return x.x>y.x;
		else return x.id>y.id;
	}
};
int t,n,m,x,a[N],id[N];
priority_queue <node> q;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>t;
	while(t--){
		while(!q.empty()) q.pop();
		cin>>n>>m>>x;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=m;i++) q.push({0,i});
		node tp;
		for(int i=1;i<=n;i++){
			tp=q.top();q.pop();
			tp.x+=a[i];id[i]=tp.id;
			q.push(tp);
		}
		cout<<"YES\n";
		for(int i=1;i<=n;i++)
			cout<<id[i]<<" \n"[i==n];
	}
	return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：0)

刚开始的时候有一个值域想法是直接枚举当前的值域是什么然后判断合不合法，但很快就弃了。                             

等过完 D 后回头来看就发现这是水题了。              

我们初始化 m 个高度为 0 的楼，往优先队列里面扔，由于保证了每个数不超过 x，所以我们每次直接往当前高度最小的楼扔就行了，可以证明在上一个状态合法的情况下，这么构造出来的下一个状态一定合法。           

时间复杂度 $O(n \log n)$ ，在我们这么构造后也可以证明原题没有 No 的情况。      
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<bits/stdc++.h>
using namespace std;
const int Len = 1e5 + 5;
int n,m,x,a[Len];
struct node
{
	int idx,w;
	node(){idx = 0 , w = 0;}
	node(int IDX,int W){idx = IDX , w = W;}
	bool operator < (const node &oth) const { return w > oth.w; }
}smr;
priority_queue<node> q;
int flag[Len];
int main()
{
	int t;
	scanf("%d",&t);
	while(t --)
	{
		scanf("%d %d %d",&n,&m,&x);
		for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
		for(int i = 1 ; i <= m ; i ++) q.push(node(i , 0));
		for(int i = 1 ; i <= n ; i ++)
		{
			smr = q.top();q.pop();
			flag[i] = smr.idx;
			smr.w += a[i];
			q.push(smr);
		}
		int maxn = 0 , minn = 1e9;
		while(!q.empty())
		{
			smr = q.top();
			maxn = max(maxn , smr.w);
			minn = min(minn , smr.w);
			q.pop();
		}
		//printf("%d %d\n",maxn,minn);
		puts("YES");
		for(int i = 1 ; i <= n ; i ++) printf("%d ",flag[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：minVan (赞：0)

**解题思路**

线性构造。

先将原数组排序，然后我们让第 $h_i$ 放到第 $(i-1)\bmod m+1$ 堆里。这样在放 $h_i$ 时，前 $i-1$ 堆每一堆此时的高度均大于等于第 $i$ 堆，从而放完之后第 $i$ 堆与前 $i-1$ 堆的差一定 $\le h_i\le x$。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int read() {
  int x=0,f=1;char ch=getchar();
  while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
  while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
  return x*f;
}
const int N = 1e6 + 5;
struct node {
  int x, id;
  bool operator < (const node &y) const {
  	return x < y.x;
	}
} a[N];
int n, m, k, ans[N];
int main() {
  int t = read();
  while(t--) {
  	n = read(), m = read(), k = read();
    for(int i = 1; i <= n; i++) {
      a[i].x = read();
      a[i].id = i;
    }
    sort(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++) {
      ans[a[i].id] = (i - 1) % m + 1;
    }
    cout << "Yes\n";
    for(int i = 1; i <= n; i++) {
    	printf("%d ", ans[i]);
    }
    puts("");
  }
  return 0;
}
```

---

