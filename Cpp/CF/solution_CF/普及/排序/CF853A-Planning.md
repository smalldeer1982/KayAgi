# Planning

## 题目描述

Helen在大都会机场工作，她的任务是安排每天的航班起飞时刻。今天一共有n架飞机将要起飞，第i架飞机将在第i分钟起飞。

大都会机场是大都会最重要的交通枢纽，因此想要原封不动地按照起飞时刻表的时刻起飞是很困难的。今天的情况也是如此：由于技术原因，在今天一开始的k分钟内飞机不允许起飞，因此必须创建一个新的起飞时刻表。

所有的航班必须在第(k+1)分钟到第(k+n)分钟内(包括两端)起飞，而且每分钟仅能有一架飞机起飞。然而，航班起飞的先后顺序可以与最初的时刻表排好的顺序不同，重排的时刻表只有一个限制：飞机不能比它在初始时刻表中起飞的时刻还要早的时刻起飞(即：第i架飞机必须在第i分钟后或第i分钟时起飞)。

Helen知道第i架飞机起飞时刻每延误一分钟机场所需支付的额外花费ci是多少。帮助她找到额外花费最小的方案。

## 说明/提示

在样例中，如果Helen仅把每架飞机的起飞时刻都推迟2分钟，那么总额外花费是38。
但是，对于最佳结果来说，总额外花费为20。

感谢@radish布団  提供的翻译

## 样例 #1

### 输入

```
5 2
4 2 1 10 2
```

### 输出

```
20
3 6 7 4 5 
```

# 题解

## 作者：NaN_HQJ2007_NaN (赞：14)

废话不多说，先上图：

![](https://cdn.luogu.com.cn/upload/image_hosting/le1z8x4k.png)

首先要说一句：虽然这张图可能有点大，但我也花了一个多小时做好（~~请容忍我的菜~~）

首先看一下图的内容，左边竖着的是航班号，上边横着的是时间，每行红色部分是该行航班不能起飞的时间，每行的白色部分是若该行的航班在这时起飞所需要增加的费用，最右边的$+x$是这一行的航班每延迟一分钟要增加的费用，拿红圈圈起来的数代表该航班所要增加的费用和起飞时间。

#### 切入正题：

这道题是优先队列+贪心，先说一下如何贪心：

感谢 @Juanzhang 题解中的公式

设时间安排为$d_i$,则总花费为

$\sum_{i=1}^n{(d_i-t_i)\cdot{c_i}}$

改变一下，即变成

$\sum_{i=1}^n{d_i\cdot{c_i}}-\sum_{i=1}^n{t_i\cdot{c_i}}$

∵ $t_i\cdot{c_i}$不变

∴ $d_i$必须尽可能小

这么一说，我猜许多人都想到了一个办法：对每个航班的$c_i$从大到小排个序，然后找到能起飞的最短时间（红色部分右面其中的一个白色部分），并把时间标记一下，以防两个航班同时起飞。
# NO！NO！NO！

如果你这么做，一提交你就会看到：

![](https://cdn.luogu.com.cn/upload/image_hosting/dwfkx8h2.png)

(~~这是我亲身经历过的~~)

#### 那要怎么做呢？？？接下来，图就要其大作用了！（~~再插一遍~~）：
![](https://cdn.luogu.com.cn/upload/image_hosting/le1z8x4k.png)

首先请看红色部分，你会发现，起飞时间小于等于$k+1$的航班最早能起飞的时间为$k+1$,而剩下的最早起飞时间就成为了阶梯状，$k+2,k+3......k+n$。

进一步分析：仔细观察，若从红色部分一样的那些航班中选出任意一个航班，让它在最早时间起飞，则对$4$号和$5$号航班没有任何影响。假设以让$1$号航班在$3$时起飞，那么如果要在$2$,$3$,$4$号航班中选出一个航班，让它在最早时间起飞，仔细看图，你还会发现它对$5$号航班没有任何影响。既然是这样，那选的时候为什么不选$c_i$最大的呢$?$ (这句话充满了奥妙,仔细想一想)

#### 分析就到这儿，剩下的留给读者自己思考改如何贪心（~~不是我不会（逃~~）

做法：先定义一个优先队列，对它进行重载运算符，然后先把起飞时间小于等于$k+1$的航班读入到优先队列中，取出队头，进行一部分操作，然后通过循环一一把剩下的航班读入队列，每读一个，取出队头，进行一部分操作，弹出队头......最后把答案输出。（详细见代码）这不会违反我们的贪心原则

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const long long maxn=2*300000+10; 
struct node{
	long long m,id;//m是每延迟一分钟所要增加的钱数 
}a[maxn];          //id是他的编号+原起飞时间 
struct cmp1{
	bool operator () (node x,node y){//重载运算符 
		if(x.m!=y.m){//钱数不等于 
			return x.m<y.m;//钱数大的靠近对头 
		}else{
			return x.id<y.id;//编号大的在前头（随便设定的） 
		}
	}
};
long long tong[maxn]={0};//以防万一都开long long...... 
long long n,k,mo,lie,hang;//变量介绍看下方 
long long ans=0;
node tmp;
priority_queue<node,vector<node>,cmp1> q;
int main(){
	register long long i,j;
	scanf("%lld%lld",&n,&k);
	for(i=1;i<=n;i++){
		scanf("%lld",&mo);
		a[i].m=mo;
		a[i].id=i;
	}
	for(i=1;i<=1+k;i++){//把1至k-1红色部分相同的部分读入 
		q.push(a[i]);
	}
	lie=k+1,hang=k+2;//hang是当前航班的编号，lie是当前航班的最早起飞时间 
	tong[q.top().id]=lie;//存答案用的 
	ans+=(lie-q.top().id)*q.top().m;//ans是所要增加的钱数 
	q.pop();//弹出队首 
	for(i=2;i<=n;i++){//对剩下的航班进行操作 
		if(hang<=n){//如果没有都读入，就读入 
			q.push(a[hang]);
		}if(hang<=n){//同理，<=n是为了不让上面的if再做一遍没用的操作 
			hang++;
		}
		lie++;//找到当前航班最早的起飞时间 
		ans+=(lie-q.top().id)*q.top().m;//计算花费 
		tong[q.top().id]=lie;//放入桶中 
		q.pop();//弹出队首 
	}
	printf("%lld\n",ans);//输出 
	for(i=1;i<=n;i++){
		printf("%lld ",tong[i]);
	}
	printf("\n");
	//over 
	return 0;
}

```

# 再见


---

## 作者：爬行者小郑 (赞：5)

## 用STL:priority_queue来贪心

具体怎么实现呢？

我们可以这样想，因为题目中说新的时间不能早于原来的时间（原来的时间就是编号），所以我们可以一个一个地从k+1到k+n模拟时间，每次都压入原来时间不超过延迟后的时间的航班（好抽象……）。也就是说，候选队列里面的时间绝对不会早于原来的时间。

那么详细过程请见具体代码：
```cpp
#include <iostream>//基本输入输出
#include <queue>//一会要用到优先队列
using namespace std;
int n,k;
struct Node
{
    int id;
    int c;
    bool operator < (const Node &t)const//重载运算符
    {
        return c<t.c;//注意，还是花费最大的在堆顶
    }
}t[300005];
priority_queue<Node>q;
Node tmp;
int ans[300005];
long long all;//记得开long long
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>t[i].c;//花费
        t[i].id=i;//原来时间
    }
    int tot=0;
    for(int i=1;i<=n;i++)
    {   
        for(int j=tot;j<=i+k&&j<=n;j++)q.push(t[j]),tot++;
        
        /*
        记录时间，
        并且把符合题意的push进去。
        i=1的时候会push进去
        min(i+k,n)个
        之后会每次push进去1个
        */
        
        tmp=q.top();q.pop();//取出来最贵的
        int t=i+k;//原来时间加上延迟后的时间
        ans[tmp.id]=t;//记录这一个航班的答案
        all+=(long long)(tmp.c)*(long long)(t-tmp.id);//记录花费
    }
    cout<<all<<endl;//所有花费
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i]<<" ";//输出新的时间
    }
    return 0;//养成好习惯
}
```
谢谢大家


---

## 作者：Juanzhang (赞：5)

**正解**：
- **贪心** + **堆**维护


**思路**：
- **贪心** + **线段树**维护

~~不知怎的就比堆维护的慢~~

***

设时间安排为$d_i$，
则总花费为$\displaystyle\sum_{i=1}^n{(d_i-t_i)\cdot{c_i}}$

改变一下，即$\displaystyle\sum_{i=1}^n{d_i\cdot{c_i}}$ $-$ $\displaystyle\sum_{i=1}^n{t_i\cdot c_i}$

$∵t_i\cdot c_i$不变

$∴d_i$需尽量小

于是按照$c_i$排序，尽量向小的取

于是记一个$vis_i$记录 时间为$i$是否已安排飞机

但每次寻找最小的未被安排的时间可能达到$O(n)$

果断上**线段树**

~~贪心证明略~~

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 3e5 + 10;
ll sum;
bool vis[maxn];
int n, k, ans[maxn];

struct plane {
	int t;
	ll val;
	inline bool operator < (const plane& p) const {
		return p.val ^ val ? val > p.val : t < p.t;
	}
} a[maxn];

struct segment_tree {
	int l, r;
	bool flag;
} tree[maxn << 2];

void maintain(int k) {
	tree[k].flag = tree[k << 1].flag && tree[k << 1 | 1].flag;
}

void build(int k, int l, int r) {
	tree[k].l = l, tree[k].r = r;
	if (l == r) {
		return;
	}
	int mid = l + r >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
}

void update(int k, int x) {
	if (tree[k].l == tree[k].r) {
		tree[k].flag = 1;
		return;
	}
	int mid = tree[k].l + tree[k].r >> 1;
	if (x <= mid) {
		update(k << 1, x);
	} else {
		update(k << 1 | 1, x);
	}
	maintain(k);
}

int query(int k, int x) {
	if (tree[k].l == tree[k].r) {
		return tree[k].l;
	}
	int mid = tree[k].l + tree[k].r >> 1;
	if (!tree[k << 1].flag && x <= mid) {
		return query(k << 1, x);
	} else {
		return query(k << 1 | 1, x);
	}
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i].val), a[i].t = i;
	}
	sort(a + 1, a + n + 1);
	build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		int t = query(1, max(a[i].t - k, 1));
		vis[t] = 1;
		update(1, t);
		ans[a[i].t] = t + k;
		sum += (t + k - a[i].t) * a[i].val;
	}
	printf("%lld\n", sum);
	for (int i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	return 0;
}
```

***

当然，还有**正解**贪心 + 堆维护

此处不做过多介绍~~STL就这么短~~

**代码**：

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;
const int maxn = 3e5 + 10;
ll sum;
int n, k, cnt = 1, w[maxn], ans[maxn];

priority_queue <pii> q;

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", w + i);
	}
	for (int i = k + 1; i <= k + n; i++) {
		for (; cnt <= n && cnt <= i; ) {
			q.push(make_pair(w[cnt], cnt)), cnt++;
		}
		pii node = q.top();
		q.pop();
		ans[node.second] = i;
		sum += 1ll * node.first * (i - node.second);
	}
	printf("%lld\n", sum);
	for (int i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	return 0;
}
```

---

## 作者：Peiyuan (赞：1)

[原题通道](https://www.luogu.com.cn/problem/CF853A)

### 思路
首先，为了操作方便，我们可以用一个优先队列 ```priority_queue``` 来模拟，自动按照延误时间从小到大排序。然后做一个循环，遍历一下 $k+1$ 到 $k+n$ 这个区间，每次取出队头计算最小额外花费和第 $i$ 架航班起飞的时刻。

鲁迅说过：“十年 OI 一场空，不开 ```long long``` 见祖宗”。由于答案最大值可能达到 $n \times c_i \rightarrow 3000 \times 10^7$，所以要开 ```long long```。
### AC代码
```cpp
#include<iostream>
#include<queue>
using namespace std;
typedef long long ll;
struct node{
	ll num,id; //分别是这个航班的延误时间和编号 
	friend bool operator <(node x,node y){ //重载小于号排序规则：
		//注意，在优先队列里，小于号代表大的在前，大于号代表小的在前
		if(x.num!=y.num) return x.num<y.num; //优先考虑延误时间，大的在前
		return x.id<y.id; //其次考虑编号，大的在前
	}
}a[300005];
ll t[300005],n,k,c,ans; //t[i]表示第i架家航班起飞的时刻，如题 
priority_queue<node> q;
int main(){
	scanf("%lld%lld",&n,&k);
	for(ll i=1; i<=n; i++){
		scanf("%lld",&c);
		a[i]={c,i}; //把延误时间和编号记录在a[i]里 
	}
	for(ll i=1; i<=k; i++) q.push(a[i]); //将1~k的航班信息全部加入到优先队列里 
	for(ll i=k+1; i<=k+n; i++){ //遍历k+1~k+n这个区间 
		if(i<=n) q.push(a[i]); //小于n的航班也加入优先队列 
		node x=q.top(); q.pop(); //取出队首元素（最大值）并将其移出优先队列 
		t[x.id]=i; //记录第x.id架航班起飞的时刻
		ans+=(i-x.id)*x.num; //累加最小额外花费
	}
	printf("%lld\n",ans);
	for(int i=1; i<=n; i++){
		printf("%lld ",t[i]);
	}
	return 0;
}
```

---

## 作者：刘辰雨 (赞：1)

正解：**贪心**+**并查集**维护。

# Sulution of CF853A(Planning)

### 简述题意 / General describe:

题目要求将 $1,2,...,n$ 重新排列在 $k+1,k+2,...,k+n$ 的区间内，并产生 $\sum _{i=1}^{n} [(total_i-start_i)\times c_i]$ 的贡献。其中 $start_i$ 表示初始数值， $total_i$ 表示排列后数值， $c_i$ 为参数，由题目给出。

求一种排列方法，产生最小贡献。

### 心路历程 / General ideas:

1. 首先，**一眼贪心**。详细证明见下：

设贡献为 $w$：

 $w=\sum _{i=1}^{n} (total_i-start_i)\times c_i=\sum _{i=1}^{n}(total_i\times c_i-start_i\times c_i)$ 
 
 显然， $\sum_{i=1}^{n}(-start_i\times c_i)$ 为定值，只需构造 $\sum_{i=1}^n(total_i\times c_i)$ 尽可能小即可。
 
2. 思考贪心策略。 $c_i$ 为参数， $total_i$ **可以改变但不能重复**，那么对于更大的 $c_i$， $total_i$ 应当更小，即更靠近 $start_i$ ，证明只需任意反例做差即可，略。

3. 很快可以想到，对 $c_1,c_2,...,c_n$ 从大到小排序，并依次为他们找到目前可用的最小 $total$ 计算贡献并记录即可。但是显然复杂度是 $O(n\log n+n^2)$，很劣。

4. 第一时间想优化掉遍历产生的 $O(n)$ 复杂度，因为每确定一个 $total$，其他位置的最佳选择都要随之变动，所以第一时间想到**并查集**，因为它可以实时改变状态。

5. 明白一点说，使用 $nr$ 数组记录当前每个 $start$ 的最优 $total$，每改变一个值，将该 $nr_{start}$ 修改为 $nr_{start}+1$，其他与之重复的值会随之改变。详见Code。

## 代码 / Code：

[AC记录](https://www.luogu.com.cn/record/103929898)

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long n,k;
long long out[(long long)3e5+5]; 
struct cost {
	long long time, value;
}c[(long long)3e5+5];
bool cmp(cost a, cost b) {
	return a.value > b.value;
}
long long ans;
long long nr[(long long)6e5+5];
long long find(long long x) {
	if(nr[x] == x)
		return x;
	return nr[x] = find(nr[x]);
}

int main() {
	freopen("plan.in","r",stdin);
	freopen("plan.out","w",stdout);
	scanf("%lld%lld", &n, &k);
	for(long long i = 1 ; i<= n ; i++) {
		scanf("%lld", &c[i].value);
		c[i].time = i;
	}
	for(long long i = 1 ; i<= k ; i++) {
		nr[i] = k+1;
	}
	for(long long i= k+1 ; i<= k+n ; i++) {
		nr[i] = i;
	}
	sort(c+1, c+n+1, cmp);
	for(long long i = 1 ; i<= n ; i++) {
		long long place = c[i].time;
		ans += c[i].value*(find(place)-place);
		out[place] = find(place);
		nr[find(place)] = find(place)+1;
	}
	printf("%lld\n",ans);
	for(int i = 1 ; i<= n ; i++) {
		printf("%lld ", out[i]);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
} 
```

以上即是考场代码，希望有所帮助。


---

## 作者：Sternenlicht (赞：1)

思路：

发现若把飞机全部停在机场，则每隔 $1$ 分钟飞机会对答案贡献加 $1$。

并且当前选择的飞机虽然会影响之后的选择，但保证之后的选择是最优的，即具有贪心的性质，所以让当前答案最小即可。

首先把飞机加入优先队列，直到加到 $k$ 为止，然后每加一个数，把最大的数弹出。

```cpp
#include <bits/stdc++.h>
namespace IO{
	#define LL long long
	inline LL read(){
		LL x=0,f=1;char c=getchar();
		for (;!isdigit(c);c=getchar())if (c=='-')f=-1;
		for (;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+(c^48);
		return x*f;
	}
	inline void write(LL x,char c='\n'){
		if (x){
			if (x<0)x=-x,putchar('-');
			char a[30];short l;
			for (l=0;x;x/=10)a[l++]=x%10^48;
			for (l--;l>=0;l--)putchar(a[l]);
		}else putchar('0');putchar(c);
	}
}using namespace IO;
using namespace std;

#define int long long
const int N = 3e5+10;
int a[N],res[N],n,k,ans,sum;
priority_queue<pair<int,int> > que;
signed main(){
	n=read(),k=read();
	for (int i=1;i<=n;i++)a[i]=read();
	for (int i=1;i<=k;i++)
		que.push(make_pair(a[i],i)),
		ans+=sum,sum+=a[i];
	for (int i=k+1;i<=k+n;i++)
		if (i>n)
			res[que.top().second]=i,ans+=sum,
			sum-=que.top().first,que.pop();
		else
			if (que.top().first>a[i])
				res[que.top().second]=i,ans+=sum,
				sum-=que.top().first,sum+=a[i],
				que.pop(),que.push(make_pair(a[i],i));
			else
				res[i]=i,ans+=sum;
	write(ans);
	for (int i=1;i<=n;i++)write(res[i],' ');
	return 0;
}
```

---

## 作者：RainFestival (赞：1)

这里提供一种 $O(n\log^2n)$ 的 $\texttt{BIT}$ 做法。

我们应该先将所有的飞机按照 $c$ 从大到小排序，每架飞机都应该选择**当前未安排飞机起飞并且飞行时间满足题意的最早的时间**。这里“满足题意”指不早于原定飞行时间。

~~简要证明~~感性理解：假设有 $x,y$ 两架飞机，将它们进行交换起飞时间使总花费更少，其中不妨设 $c_x\ge c_y$，$x$ 在 $x'$ 时起飞，$y$ 在 $y'$ 时起飞，显然 $x\neq y,x'\neq y'$。计算得花费 $w=(x'-x)\times c_x+(y'-y)\times c_y$。

+ 若 $x'>y'$，则一定是 $x>y'$ 不然 $x$ 先选择一定会选择 $y'$，所以不能交换起飞时间。

+ 若 $x'<y'$

    + 如果 $y>x'$ 则不能交换。
    
    + 如果 $y\le x'$ 花费 $w'=(y'-x)\times c_x+(x'-y)\times c_y$，作差 $\Delta w=w'-w=(y'-x')(c_x-c_y)$。由于 $y'>x'$ 并且 $c_x\ge c_y$，所以 $\Delta w\ge 0$，新方案不比原方案优秀。
    
现在我们需要快速求出“当前未安排飞机起飞并且飞行时间满足题意的最早的时间”。

假设现在考虑飞机 $x$。首先飞行时间满足题意是指 $x'\in[\max(k+1,x),k+n]$。然后考虑在这个区间内二分，每次用 $\texttt{BIT}$ 求出 $[l,mid]$ 中是否有未安排飞机起飞的时间。

由于飞机一共有 $n$ 架。总时间复杂度为 $O(n\log^2n)$。

代码如下：

```cpp
#include<cstdio>
#include<cstdlib>
#include<utility>
#include<algorithm>
struct bit
{
	int n,s[600005];
	int lowbit(int x){return x&(-x);}
	int query(int x){int ans=0;for (;x>=1;x=x-lowbit(x)) ans=ans+s[x];return ans;}
	void add(int x,int y){for (;x<=n;x=x+lowbit(x)) s[x]=s[x]+y;}
	int full(int x,int y){return query(y)-query(x-1)==y-x+1;}
};
bit t;
int n,k,p[300005];
long long ans=0;
std::pair<int,int> f[300005];
int bs(int l,int r)
{
	if (l==r) return l;
	int mid=(l+r)/2;
	if (!t.full(l,mid)) return bs(l,mid);
	return bs(mid+1,r);
}
int main()
{
	scanf("%d%d",&n,&k);
	t.n=n+k;
	for (int i=1;i<=n;i++) scanf("%d",&f[i].first),f[i].second=i;
	std::stable_sort(f+1,f+n+1);std::reverse(f+1,f+n+1);
	for (int i=1;i<=n;i++)
	{
		int now=f[i].second,x=std::max(k+1,f[i].second),y=bs(x,k+n);
		p[now]=y;t.add(y,1);
		ans=ans+1ll*f[i].first*(y-now);
	}
	printf("%lld\n",ans);
	for (int i=1;i<=n;i++) printf("%d ",p[i]);
	puts("");
	return 0;
}
```

总时间 $4.74s$ 在目前 $85$ 人中排在 $63$ 名，被各种 $O(n\log n)$ 的方法吊打。

---

## 作者：FutaRimeWoawaSete (赞：1)

首先是被线段树标签骗过来的，~~不过都想出来了总不能不做吧~~。  

果然$CF$的题不能看标签。    

首先我们发现我们如果把飞机滞留起来，   

每隔 $1min$ 我们滞留起来的飞机就会给我们的答案贡献加$1$，这很显然对吧。    

其次就很有意思的是，我们发现我们这道题具有最优子结构，  

即我们当前选择的飞机虽然会影响后面的选择，但是也保证了后面的选择是最优的。  

所以说我们只要让当前的答案最小就行了。   

只要能想通这点这道题就很好办了，我们就很好办这道题了，首先往优先队列里面加飞机加到 $k$ 。     

然后每次加一个数的时候我们扔最大数即可。   
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;
const int Len = 3e5 + 5;
struct node
{
	int idx;long long val;
	node(int a,long long b) {idx = a;val = b;}
    bool operator<(const node& a) const
    {
        return val < a.val; //大顶堆
    }
};
priority_queue<node> q;
long long n,m,a[Len],sum,ans,Pos[Len];
int main()
{
	scanf("%lld %lld",&n,&m);
	for(int i = 1 ; i <= n ; i ++) scanf("%lld",&a[i]);
	for(int i = 1 ; i <= m ; i ++) 
	{
		q.push(node(i , a[i]));
		ans += sum;
		sum += a[i];
	}
	for(int i = m + 1 ; i <= n + m ; i ++)
	{
		if(i > n) 
		{
			node f = q.top();
			q.pop();
			Pos[f.idx] = i;
			ans += sum;
			sum -= f.val;
		}
		else
		{
			node f = q.top();
			q.pop();
			if(f.val > a[i])
			{
				Pos[f.idx] = i;
				ans += sum;
				sum -= f.val;
				sum += a[i];
				q.push(node(i , a[i]));
			}
			else 
			{
				Pos[i] = i;
				ans += sum;
				q.push(f);
			}
		}
		//printf("%lld %lld\n",sum,ans);
	}
	printf("%lld\n",ans);
	for(int i = 1 ; i <= n ; i ++) printf("%lld ",Pos[i]);
	return 0;
} 
```

---

## 作者：Rosent (赞：0)

[题目Link](https://www.luogu.com.cn/problem/CF853A)

优先队列模板题，~~建议降黄~~。

题目要求找到额外花费最小的方案，配合数据范围 $1 \le k \le n \le 300000$，不难联想到贪心算法。

题目已知每架飞机每延误一分钟的额外花费，我们可以使延误花费大的飞机尽可能早起飞。

由于第 $i$ 架飞机必须在第 $i$ 分钟及以后起飞，我们可以维护一个大根堆，在第 $i$ 分钟时将第 $i$ 架飞机的花费加入堆，并弹出此时堆顶元素（$k\le n$ 时不弹出）。弹出的元素顺序即是最优飞机起飞顺序。

温馨提示：$1 \le c_{i} \le 10^7$，不开 `long long` 见祖宗。
```cpp
#include <bits/stdc++.h>
#define int long long
#define maxn 600010//记得开大一点，不然RE #6
using namespace std;
struct node
{
	int value,index;
}a[maxn],b[maxn];
struct cmp
{
	bool operator() (node a,node b)
	{
		return a.value<b.value;//大根堆 
	}
};
int c[maxn];
priority_queue<node,vector<node>,cmp> p;//自定义数据类型堆 
signed main()
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].value;
		a[i].index=i;
	}
	for(int i=1;i<=k;i++)
	{
		p.push({a[i].value,a[i].index});
	}
	int t=0;
	for(int i=k+1;i<=n+k;i++)
	{
		p.push(a[i]);
		b[++t]=p.top();
		c[p.top().index]=i;
		p.pop();
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		cnt+=b[i].value*(i+k-b[i].index);
	}
	cout<<cnt<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<c[i]<<" ";
	}
	return 0;
}
```

---

