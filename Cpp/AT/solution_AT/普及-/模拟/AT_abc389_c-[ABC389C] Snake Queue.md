# [ABC389C] Snake Queue

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc389/tasks/abc389_c

存在一个蛇的队列。初始时队列为空。

给定 $ Q $ 个查询，请按顺序处理。查询有以下三种类型：

- **类型 1**：以 `1 l` 的形式给出。将长度为 $ l $ 的蛇添加到队列末尾。此时，若原队列为空，则添加的蛇的头部坐标为 $ 0 $；否则，新蛇的头部坐标为队列最后一条蛇的头部坐标加上其长度。
- **类型 2**：以 `2` 的形式给出。队列最前端的蛇离开队列。此时保证队列不为空。设离开的蛇长度为 $ m $，队列中剩余所有蛇的头部坐标将减少 $ m $。
- **类型 3**：以 `3 k` 的形式给出。输出队列中从前往后数第 $ k $ 条蛇的头部坐标。此时保证队列中至少有 $ k $ 条蛇。

## 说明/提示

### 约束条件

- $ 1 \leq Q \leq 3 \times 10^{5} $
- 类型 1 的查询中，$ 1 \leq l \leq 10^{9} $
- 类型 2 的查询保证队列不为空
- 类型 3 的查询中，设队列中有 $ n $ 条蛇，则 $ 1 \leq k \leq n $
- 输入均为整数

### 样例解释 1

- **第 1 个查询**：添加长度为 $ 5 $ 的蛇。队列为空，因此其头部坐标为 $ 0 $。
- **第 2 个查询**：添加长度为 $ 7 $ 的蛇。原最后一条蛇的头部坐标为 $ 0 $ 且长度为 $ 5 $，因此新蛇的头部坐标为 $ 5 $。
- **第 3 个查询**：输出第 2 条蛇的头部坐标。队列中蛇的头部坐标依次为 $ 0, 5 $，因此输出 5。
- **第 4 个查询**：添加长度为 $ 3 $ 的蛇。原最后一条蛇的头部坐标为 $ 5 $ 且长度为 $ 7 $，因此新蛇的头部坐标为 $ 12 $。
- **第 5 个查询**：添加长度为 $ 4 $ 的蛇。原最后一条蛇的头部坐标为 $ 12 $ 且长度为 $ 3 $，因此新蛇的头部坐标为 $ 15 $。
- **第 6 个查询**：移除队列最前端的蛇（长度为 $ 5 $）。剩余蛇的头部坐标减少 $ 5 $，此时坐标为 $ 0, 7, 10 $。
- **第 7 个查询**：输出第 3 条蛇的头部坐标。队列中蛇的头部坐标依次为 $ 0, 7, 10 $，因此输出 10。

### 样例解释 2

可能存在没有类型 3 查询的情况。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
1 5
1 7
3 2
1 3
1 4
2
3 3```

### 输出

```
5
10```

## 样例 #2

### 输入

```
3
1 1
2
1 3```

### 输出

```
```

## 样例 #3

### 输入

```
10
1 15
1 10
1 5
2
1 5
1 10
1 15
2
3 4
3 2```

### 输出

```
20
5```

# 题解

## 作者：ryf2011 (赞：6)

# 题目思路
注：本题解的题目思路中所有没有提及意义但出现的变量或常量都为输入值或题目中给出的值。

我们直接根据题意模拟。

我们用一个结构体代替题目中说的队列，结构体中有头部位置和长度两个元素。

我们先来分析 $type = 1$ 的情况，即加入元素。

如果当前要新加入元素，且这是第一个元素，就将这个元素的头部位置设为 $0$，长度设为 $l$。如果不是第一个元素，就将这个元素的头部位置设为上一个元素的头部位置再加上上一个元素中记录的长度。

接下来分析 $type = 2$ 的情况，即弹出第一个元素。

我们定义一个变量 $head$，用于记录队列（结构体）开头的位置，此时加上 $1$。

由于 $Q$ 的范围很大，说明询问次数很多，如果在此时直接枚举，使每个元素减去当前队列中第一个元素的长度的值容易超出时限。所以再定义一个变量 $jian$，记录当前所有要减去的值，即在所有的 $type = 2$ 过程中被弹出的元素的长度和。此时让这个和加上当前被弹出的元素的长度即可。

最后分析 $type = 3$ 的情况，即查询队列中第 $k$ 个元素的头部位置的值。

由于我们之前在 $type = 2$ 的所有操作进行时并没有对数据作出改动，所以此时第 $k$ 个元素的真正位置实际上是 $k + head - 1$。我们再将这个位置的元素对应的头部位置值减去 $jian$ 即可。

最后，我们还要注意一下数据范围，对于本题，部分数据需要开 $\texttt{long long}$。

# 代码
注：本代码仅供参考。

```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int q,type,l,k,quehead=1,quel,jian; 
//quehead:模拟队列，记录队列头位置；quel:当前队列长度；jian:当前每个 snake 头部位置应减的值 
struct node{
	int head,len;
} que[310005]; //结构体，用来模拟队列 
signed main(){
	scanf("%lld",&q);
	for(int i=1;i<=q;i++){
		scanf("%lld",&type);
		if(type==1){
			scanf("%lld",&l);
			quel++;
			que[quel].head=(quel==quehead?0:(que[quel-1].head+que[quel-1].len)); //如果当前加入的 snake 是第一个，将头部位置设为 0，其余不变 
			que[quel].len=l;
		}
		else if(type==2){
			quehead++; //模拟队列弹出首个的过程 
			jian+=que[quehead-1].len; //要减去的值加上当前离开的 snake 的长度，即 len 
		}
		else{
			scanf("%lld",&k);
			printf("%lld\n",(que[k+quehead-1].head-jian)); //由于之前可能有离开的 snake，所以要先找到 k 真正所指的位置，再减去应减的值，注意不能直接在原数上减，因为这样会使数据改变，影响后面的计算 
		}
	}
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{red}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：xk2013 (赞：5)

题目传送门：[AT_abc389_c [ABC389C] Snake Queue](/problem/AT_abc389_c)

## 前置知识
- 模拟；
- 手写队列。

## 题意简述
本题要求我们模拟蛇队列的进出，并且要查询。

## 解题思路
首先想到暴力计算，但是 $\left(3\times10^5\right)^2=9\times10^{10}$，肯定会 TLE。

所以我们可以用前缀和维护它，出队的时候累计一个变量，查询的时候减去它就行了。

然后记得开 `long long int`，$\left(10^6\right)^2=10^{12}$ 会爆 `int`。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！
```cpp
#include <cstdio>

const int N = 3e5 + 5;
typedef long long int ll;
ll w, q, x, y, head = 1, tail = 1, queue[N], sum[N];

int main(void)
{
	scanf("%lld", &q);
	
	while (q--)
	{
		scanf("%lld", &x);
		
		if (x == 1)
		{
			scanf("%lld", &y);
			queue[tail++] = y;
			sum[tail] = sum[tail - 1] + y; // 计算前缀和
		}
		else if (x == 2)
		{
			w += queue[head]; // 累加
			head++;
		}
		else if (x == 3)
		{
			ll s = 0;
			scanf("%lld", &y);
			printf("%lld\n", sum[head + y - 1] - w); // 记得减去
		}
	}
	
	return 0;
}

```
----------------------
这是本五年级蒟蒻小学生的第 24 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2025/01/19：初版。

---

## 作者：include13_fAKe (赞：4)

**数组模拟队列**模板题。

考虑用一个静态数组模拟队列，用指针 $l$ 和 $r$ 代表目前队列的头和尾。

$l$ 代表队列头的上一个下标，$r$ 代表队列尾的下班。

## 操作 $1$

将数组的指针 $r$ 向后移动一个单位，在这个新的单位填上这个数。

注意数组一开始要开到 $Q$ 的长度，因为数组大小在定义之后无法改变。

## 操作 $2$

直接将指针 $l$ 向后移动一个单位弹出队列头部的变量。

## 操作 $3$

注意此处求的是**前缀和**！！！（笔者赛时就错了）

因为需要求前缀和，再用一个辅助数组记录前缀和即可。

前缀和数组也不需要因为操作 $2$ 改变。

设目前队列头的上一个下标为 $l$，操作的数为 $k$，答案即为 **$l+k-1$ 位置的前缀和**减去 **$l$ 位值的前缀和**，因为是第 $k$ 条蛇的**开始位置**，所以不把它算在里面。

前缀和数组随操作 $1$ 更新即可。

## 其他小细节 

注意 $Q\le {\color{red}3}\times 10^5$！！！（笔者赛时也错了）

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int l,r;
int n;
int a[5*114514];
int b[5*114514];
signed main(){
	cin>>n;
	while(n--){
		int op;
		cin>>op;
		switch(op){
			case 1:{
				int x;
				cin>>x;
				a[++r]=x;
				b[r]=b[r-1]+a[r];
				break;
			}
			case 2:{
				++l;
				break;
			}
			case 3:{
				int k;
				cin>>k;
				cout<<b[l+k-1]-b[l]<<endl;
				break;
			}
		}
	}
//	for(int i=1;i<=r;i++){
//		cout<<b[i]<<' ';
//	}
//	cout<<endl;
	return 0;
} //ABC389C
```

---

## 作者：run_away (赞：2)

## 题意

维护一些线段的队列，支持入队，出队，查当前第 $k$ 个的开头坐标。

## 分析

用双端队列即可，可以直接让入队的线段开头加上上一个的长，队列里面维护不考虑出队时的前缀和。

用前缀和的思想，记录所有已出队的线段长。

查询显然。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
// static char buf[100],*p1=buf,*p2=buf,obuf[100],*p3=obuf;
// #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,100,stdin),p1==p2)?EOF:*p1++
// #define putchar(x) (p3-obuf<100)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
mt19937_64 rnd(chrono::system_clock::now().time_since_epoch().count());
#define dbg(x) cout<<#x<<": "<<x<<"\n"
#define usetime() printf("time: %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(!x){putchar(48);putchar('\n');return;}short top=0,s[40];if(x<0)x=-x,putchar(45);while(x)s[top++]=x%10^48,x/=10;while(top--)putchar(s[top]);putchar('\n');}
namespace tobe{
    const ll maxn=6e5+5,mod=998244353;
	ll q[maxn],head=1,tail,a[maxn];
    inline void mian(){
		ll n=read(),sum=0;
		while(n--){
			ll op=read();
			if(op==1){
				ll x=read();
				q[tail+1]=q[tail]+a[tail];
				a[++tail]=x;
			}else if(op==2){
				sum+=a[head++];
			}else{
				ll k=read();
				write(q[head+k-1]-sum);
			}
		}
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ll t=1;
    while(t--)tobe::mian();
    // fwrite(obuf,p3-obuf,1,stdout);
    return 0;
}
```

---

## 作者：fengzhaoyu (赞：2)

## 题意
有一个蛇的序列，起初为空，且坐标从 $0$ 开始算。给出三种操作：

1. 在队列的末端加上一条长为 $l$ 的蛇，注意，这条蛇的头与上一条蛇的尾巴是同一坐标。
2. 将最前面的蛇去掉，所以后面的蛇坐标都会减一个头蛇的长度
3. 求当前队列第 $k$ 条蛇的的头部坐标。
## 思路
1. 对于操作一：只需记录一下蛇的头部坐标，长度以及它是第几条蛇，那么它的头坐标怎么找？只需记录一下蛇的总长度即可。
2. 对于操作二：我们用 $gout$ 记录一下当前有几条蛇出队，那么现在就应该是第 $gout+1$ 条蛇出队，那他产生的影响怎么计算呢？很多人都会想去暴力修改后面蛇的坐标，但无疑会爆。于是我们有一个绝妙的思路：用 $add$ 表示当前出队蛇的总长度，以服务于操作三，可以联想到懒标记，怎么用呢？
3. 对于操作三：先找出当前第 $k$ 条蛇是原队列第几条并求出其原头部坐标，这时我们再减去 $add$，为什么呢？因为当每一条蛇出队，后面蛇的坐标都会减去它的长度，且坐标前移是可加的。比方说先出队一条长为 $1$ 的蛇，再出队一条长为 $2$ 的蛇，那后面的蛇坐标是不是都前移了 $3$？
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int a[N],cnt,len,ah[N],gout;// a 存每条蛇长度，ah存头坐标，len是总长度，其他的如上面所说
int add;
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int opt,k;
		cin>>opt;
		if(opt==1)
		{
			cin>>k;
			a[++cnt]=k;
			ah[cnt]=len;
			len+=k;
		}
		if(opt==2)
		{
			++gout;
			add+=a[gout];
		}          
		if(opt==3)
		{
			cin>>k;
			cout<<ah[gout+k]-add<<endl;
		}
	}
	return 0;
}
```

---

## 作者：hjyowl (赞：2)

### 思路

首先，我们要介绍一个黑科技就是双端队列。

众所周知，系统封装好的双端队列，是能够查询第 $k$ 个的。

所以，我们用双端队列作为数据结构来做。

然后呢，我们在用一个技巧，对于第二种操作，我们用一个延迟标记，对于每一次头部，都加上当时的延迟标记，然后查询的时候剪掉延迟标记即可。

做完了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
struct owl{
	long long a,b;
};
int main(){
	deque<owl>q;
	long long Q;
	cin >> Q;
	long long t = 0;
	while (Q -- ){
		long long op;
		cin >> op;
		if (op == 1){
			long long l;
			cin >> l;
			long long tt = (q.empty() ? 0 : q.back().a + q.back().b - t);
			q.push_back({l,tt + t});
		}
		else if (op == 2){
			long long m = q.front().a;
			q.pop_front();
			t += m;
		}
		else{
			long long k;
			cin >> k;
			k -- ;
			cout << q[k].b - t << endl;
		}
	}
	return 0;
}
```

---

## 作者：dg114514 (赞：1)

upd：修改了错别字

提供一种和别人不同的解法（？）\
维护一个队列，保存原始数据，再维护一个双端队列（实际上就是一个能查下标的队列）维护原始数据的前缀和，每次根据操作维护。注：删除的时候维护一个 `tag`，表示实际输出是要减去 `tag`。详见代码。
```cpp
#ifndef ONLINE_JUDGE
	#pragma GCC optimize(2,"Ofast","inline")
#endif
#include<bits/stdc++.h>
#define x first
#define y second
#define int long long
#define dbg cout<<"debug"<<__LINE__<<"\n"
using namespace std;
constexpr int mod=998244353,N=5e5+5;
typedef pair<int,int> PII;
typedef pair<string,int> PSI;
typedef pair<double,double> PDD;
int Q,x,y,tag,cnt;
deque<int>sum;
queue<int>q;
signed main(){
	sum.push_front(0);//第一条蛇蛇头坐标是0
	cin>>Q;
	while(Q--){
		cin>>x;
		if(x==1){
			cin>>y,q.push(y);
			sum.push_back(sum.back()+y);
		}
		else if(x==2)tag+=q.front(),sum.pop_front(),q.pop();
		else cin>>y,cout<<sum[y-1]-tag<<"\n";
//		for(auto &i:sum)cout<<i-tag<<" ";
//		cout<<tag<<"\n";
	}
}
```

---

## 作者：__Ship_ (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc389_c)

## 思路

题目要求查询任意一个蛇的位置，我们可以将每一个蛇的位置存在数组中，以便更好的查询。

```cpp
if(op==1){
	cin>>l;
	q.push(l);
	idx++;
	a[idx]=a[idx-1]+l;//计算头部位置
}
```

然后考虑如何在尽可能短的时间内查询。

因为我们存储的时候没有考虑两件事情：蛇的位置与头部位置。

就拿样例举例：

第二次查询的时候，虽然查询的是第 $3$ 只蛇，但是应为我们前面走了一只蛇，所以应该是 $3+1$ 只蛇的位置，应为走了一只蛇的长度，所以再减去就好了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
queue<long long> q;
long long Q,op,idx=1,kk,d,a[300050],l,k;
int main(){
	cin>>Q;
	while(Q--){
		cin>>op;
		if(op==1){
			cin>>l;
			q.push(l);
			idx++;
			a[idx]=a[idx-1]+l;
		}
		if(op==2){
			d+=q.front();
			q.pop();
			kk++;
		}
		if(op==3){
			cin>>k;
			cout<<a[k+kk]-d<<endl;
		}
	}
	
	return 0;
}

```

---

## 作者：yyycj (赞：1)

## [题目传送门](https://atcoder.jp/contests/abc389/tasks/abc389_c)

## 题目简述
有一个放蛇的队列，起初是空的。

现在有 $Q$ 次操作，操作有三种类型：
- 类型 $1$：输入格式 `1 l`，将一条长度为 $l$ 的是加入队列尾，它的头部坐标为前一条蛇的尾坐标，如果加入前队列里没有蛇，则头坐标为 $0$。设的尾坐标等于头坐标加长度。
- 类型 $2$：输入格式 `2`，删除队列最前面的蛇，后面的蛇的头坐标会因此改变。
- 类型 $3$：输入格式 `3 k`，输出第 $k$ 条蛇的头坐标，保证出现此操作蛇的数量 $\ge k$。

## 主要思路
首先，如果操作 $2$ 直接根据题意模拟，遍历整个队列，将每条蛇的头坐标改变，并删除第一条蛇，时间复杂度为 $O(Q^{2})$，对于 $Q\le3\times 10^{5}$，显然超时。

所以说我们可以不删除第一条蛇，而是定义一个 $sum$ 变量，初值为 $0$，对于每个操作 $2$，将 $sum$ 加上第一条蛇的长度，这样在进行操作 $3$ 时，答案即为（记存储蛇头坐标的数组为 $S$，进行操作 $2$ 的次数为 $p$）$S_{k+p}-sum$，表示由于删掉了 $p$ 条蛇，但数组里存放的蛇的数量没有减少，所以要加上一个 $p$，并且操作 $2$ 后蛇的头坐标会改变，但数组里也没有改变，所以减去 $sum$ 就表示减去前面删掉的蛇的长度的总和。

最最后：十年 OI 一场空，___________________。

## AC Code
```cpp
#include<map>
#include<set>
#include<list>
#include<stack>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<unordered_set>
using namespace std;

#define OUT 0
#define endl '\n'
#define MAMBA return
typedef long long ll;
const int N = 3e5 + 10;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
int _pow(int a,int b){int x=1,y=a;while(b>0){if(b&1)x*=y;y*=y;b>>=1;}return x;}
void print(ll x){if(x<0){putchar('-');x=-x;}if(x>9){print(x/10);}putchar(char(x%10+'0'));}
void print(int x){if(x<0){putchar('-');x=-x;}if(x>9){print(x/10);}putchar(char(x%10+'0'));}
void print(string s){int n=s.length();for(int i=0;i<n;i++)putchar(s[i]);}
inline int read_int(){int f=1,x=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline ll read_ll(){int f=1;ll x=0;char ch=getchar();while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
// ----------------------------

// ----------------------------
ll len[N];
ll head_idx[N];
// ----------------------------


int man() {
	int q = read_int();
	// ------------------------
	int op,k;
	ll sum = 0;
	int pop_cnt = 0;
	int snake_cnt = 0;
	while (q--) {
		op = read_int();
		if (op == 1) {
			len[++snake_cnt] = read_int();
			head_idx[snake_cnt] = head_idx[snake_cnt-1] + len[snake_cnt-1];
		}
		else if (op == 2) sum += len[++pop_cnt];
		else {
			k = read_int();
			print(head_idx[k+pop_cnt]-sum);
			putchar('\n');
		}
	}
	MAMBA OUT;
}
 		   	  				   			  						   														   															  	 																																			int main() {MAMBA man();}
```

---

## 作者：_wsq_ (赞：1)

`deque` 是个好东西，不仅支持在两端加入或删除元素，还支持用 `[]` 直接访问某一位的值。这样，我们只需要开一个 `deque<pair<int,int> >` 分别存下 $length$ 和 $head$ 就可以实现操作 1 和 3 了。

至于操作 2，在弹出的同时还要将队列中所有元素的 $head$ 减少一个数。因此考虑维护一个 $head$ 的总体减少量，操作 2 直接减少这个数，操作 1 时去掉这个数的影响即可。

代码：

```cpp
#include <iostream>
#include <deque>
#include <utility>
using namespace std;
#define int long long
int c,sum;
deque<pair<int,int> > q;
signed main(){
    int t;
    cin>>t;
    while(t--){
        int op;
        cin>>op;
        if(op==1){
            int l;
            cin>>l;
            q.push_back(make_pair(l,sum-c));//在这里我用的是队列中所有元素的 length 的和，用队尾元素的 length 和 head 相加也可
            sum+=l;
        }
        if(op==2){
            sum-=q.front().first;
            c-=q.front().first;
            q.pop_front();
        }
        if(op==3){
            int k;
            cin>>k;
            cout<<q[k-1].second+c<<'\n';//deque 的下标从 0 开始
        }
    }
    return 0;
}
```

---

## 作者：PDAFX (赞：1)

## 题目大意

### 题目翻译

有一条蛇的等待队列。最开始，队列为空。
给定 $Q$ 个查询，请按照给定的顺序处理这些查询。每个查询有以下三种类型：

- **类型 1**：`1 l`\
  向队列的末尾添加一条长度为 $l$ 的蛇。若队列为空，则蛇的头部坐标为 $0$；若队列不为空，则蛇的头部坐标为队列中最后一条蛇的头部坐标加上其长度。

- **类型 2**：`2`\
  删除队列前端的蛇。删除时，队列中剩下的所有蛇的头部坐标会减去被删除蛇的长度。

- **类型 3**：`3 k`\
  输出队列中第 $k$ 条蛇的头部坐标。队列中至少有 $k$ 条蛇。

## 思路

直接暴力求解会 $O(n^2)$, 会超时。\
根据题意，我们可以采用前缀和 + 队列形式维护。\
操作一，可以转化为在队列尾部添加一个前缀和如下：

```cpp
t++,q[t]=q[t-1]+x
```

操作二，可以弹出队头。

```cpp
h++;
```

操作三，目前队列中第 $x$ 个与头部前缀和相减，因为队列头是 $0$, 所以当前位为 $a_{hd+x-2}$。

```cpp
	cout<<s[hd+x-2]-s[hd-1]<<endl;
```

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,opt,x,s[600001],t,tag,hd=1;
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>opt;
		if(opt==1)
		{
			cin>>x;
			t++;
			s[t]=s[t-1]+x;
		}
		if(opt==2)
		{
			hd++;
		}
		if(opt==3)
		{
			cin>>x;
			//cout<<s[hd+x-2]<<endl;
			cout<<s[hd+x-2]-s[hd-1]<<endl;
		}
	}
}
```

---

## 作者：XXh0919 (赞：1)

这次的 C 题真的是很简单啊，~~因为我做出来了~~。

### 解法

首先很容易想到暴力做法。具体思路就是直接暴力处理每个操作，然后输出答案。但是这样肯定会炸，所以要考虑优化。我们定义一个结构体数组：

```cpp
struct snake {
	int h, len;
}q[N];
```
其中 $q_i$ 表示第 $i$ 段的各种信息，$h$ 表示这一段的段首下标，$len$ 表示这一段的长度。在操作 $1$ 的时候，我们可以直接模拟这个过程，直接在序列末尾新插入一段。但在操作 $2$ 的时候，我们不能直接暴力删除第一段，否则就会 TLE。我们可以再定义两个变量 $cnt$ 和 $siz$，分别表示已经删除的段数和已经删除的长度，在每次操作 $2$ 时只需要将 $cnt$ 自增 $1$，$siz$ 加上第 $cnt$ 段的长度即可（因为到这个操作已经删了 $cnt$ 段了，所以现在的第一段就是第 $cnt$ 段）。同理，操作 $3$ 时输出就应该是第 $k+cnt$ 段的段首下标减去已经删除的长度 $siz$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N = 1e6 + 15;

const int I_LOVE_CCF = 1;//hahaha

int Q;
int tot;
struct snake {
	int h, len;
}q[N];
int cnt, siz;

inline int read (int &n) {
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) {
		if (ch == '-') f = -1;
		ch = getchar ();
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar ();
	}
	n = x * f;
	return n;
}

signed main () {
	read (Q);
	while (Q --) {
		int op;
		read (op);
		if (op == 1) {
			int l;
			read (l);
			++ tot;
			if (tot == 1) q[tot].h = 0;//特判（其实好像不需要）
			else q[tot].h = q[tot - 1].h + q[tot - 1].len;//当前段的段首下标
			q[tot].len = l;//段的长度
		} else if (op == 2) {
			cnt ++;
			siz += q[cnt].len;//（假装）删去第一段
		} else {
			int k;
			read (k);
			printf ("%lld\n", q[k + cnt].h - siz);//输出答案
		}
	}
	return 0;
} 
```

---

## 作者：chinazhanghaoxun (赞：1)

## 前言
看到这道题，我先想到的是前缀和，但是写普通模拟会更为简单，所以我选择了后者。首先，要介绍一个数据结构，就是 [deque](https://oi-wiki.org/lang/csl/sequence-container/#deque)，称为双向队列，是一种很方便的容器。可以快速实现插入，查询，删除的操作。
## 思路
进入正题，我们使用一个容器 $q$ 记录每条蛇的尾部下标，我以第一条蛇的尾部下标为 $q_0$ 存储。后文中很多地方都会涉及下标起始的问题，还是有点麻烦的。

对于每个进入的蛇，我们都用加入之前的尾部加上这条蛇的长度，就得到了这条蛇的尾部位置。注意当对列为空时，尾部位置应为 $l-1$，因为下标从 0 开始。

对于每个要删除的蛇，我们可以使用一个偏移量 $offset$ 记录每条蛇比自己的下标向左的距离。每一次有蛇删除，就将偏移量记为 $offset\gets q_0+1$，由于下标的问题。

对于每个查询操作，答案就是 $q_{k-2}-offset+1$，但是，重点来了，如果 $k=1$ 要特判并输出 0，否则会越界，我就因为这一点写挂了。
## 代码
这里提供两种方式，分别是使用 deque 和手动模拟的，两种都一定要注意特判越界的情况。
### Deque
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
deque<int> q;//每条蛇的尾部下标
int Q,offset;
signed main(){
    cin>>Q;
    for(int i=1;i<=Q;i++){
        int type;
        cin>>type;
        if (type==1){
            int l;
            cin>>l;
            if(q.empty()){
                q.push_back(l-1);
            }else{
                q.push_back(q.back()+l);
            }
        }else if(type==2){
            offset=q.front()+1;
            q.pop_front();
        }else if(type==3){
            int k;
            cin>>k;
            if(k==1)//特判越界！
            	cout<<0<<endl;
			else
            	cout<<q[k-2]-offset+1<<endl;
        }
    }
    return 0;
}
```
### 手动模拟
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int q[300005];//每条蛇的尾部下标 
int Q,head,tail=-1,offset;
signed main(){
    cin>>Q;
    for(int i=1;i<=Q;i++){
        int type;
        cin>>type;
        if(type==1){
            int l;
            cin>>l;
            if(head==tail+1){
                q[++tail]=l-1;
            }else{
            	int t=q[tail]+l;
                q[++tail]=t;
            }
        }else if(type==2){
            offset=q[head]+1;
            head++;
        }else if(type==3){
            int k;
            cin>>k;
            if(head==0 && k==1)//特判越界！
            	cout<<0<<endl;
			else
            	cout<<q[head+k-2]-offset+1<<endl;
        }
    }
    return 0;
}
```

---

## 作者：HG27895 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc389_c)

# 题意：

有一个空的蛇队列。

有 $Q$ 个查询，查询有三种类型：

- 类型 $1$ ：以 `1 l` 的形式给出。一条长度为 $l$ 的蛇会被添加到队列的末尾。如果添加前队列为空，则新添加的蛇的头部位置为 $0$ ；否则，它就是队列中最后一条蛇的头部坐标与最后一条蛇的长度之和。
- 类型 $2$ ：以 `2` 的形式给出。队列最前面的蛇离开队列。保证此时队列不是空的。假设 $m$ 是离开队列的蛇的长度，那么队列中剩余的每条蛇的头部坐标都会减少 $m$ 。
- 类型 $3$ ：以 `3 k` 的形式给出。输出第 $k$ 条蛇的蛇头坐标。

# 思路：

用 $a$ 数组记录蛇头坐标，$b$ 数组记录蛇的长度，$i$ 表示末尾蛇的序号，$j$ 表示已删除的蛇的数量，$cnt$ 表示已删除的蛇的长度和。

- 对于 $1$ 操作， 假如要放进第 $k$ 条蛇（不算已删除的蛇），则 $a_k=a_{k-1}+b_{k-1}$，$b_k=l$（$l$ 是输入的）。

- 对于 $2$ 操作，$cnt=cnt+b_{j+1}$，即已删除的蛇的长度要加等于删除的蛇的长度，并且已删除的蛇的数量也要加一。

- 对于 $3$ 操作，直接输出 $a_{k+j}-cnt$（$k$ 是输入的），即第 $k+j$ 条蛇的长度（因为要查询的是第 $k$ 条蛇，但是删除的 $j$ 条蛇的长度并没有从总长度中减去，所以是 $k+j$）减去已删除的蛇的长度。 

# AC代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define fi(l) freopen(l".in","r",stdin)
#define fo(l) freopen(l".out","w",stdout)
//#pragma G++ optimize(2)
using namespace std;
inline ll read()//快读
{
	ll v=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		v=v*10+c-'0';
		c=getchar();
	}
	return v*f;
}
ll a[300020],b[300020],i,j;//a数组记录头的位置，b数组记录长度，i表示末尾蛇的序号，j表示已删除的蛇的数量
int main()
{
	ll q=read(),cnt=0;//q是询问的次数，cnt是已删除的蛇的长度和
	while(q--)
	{
		ll op=read();//查询的类型
		if(op==1)
		{
			a[i+1]=a[i]+b[i];//增加一条蛇
			i++;
			b[i]=read();
		}
		else if(op==2)cnt+=b[++j];//删除一条蛇
		else
		{
			ll k=read();
			cout<<a[k+j]-cnt<<'\n';//输出第k条蛇的蛇头位置
		}
	}
	return 0;
}
```

---

## 作者：_wzx (赞：1)

#### [传送门](https://atcoder.jp/contests/abc389/tasks/abc389_c)

## 思路
  这题直接根据题意**模拟**即可。我们有 $Q_i$ 来表示第 $i$ 条蛇的头部在位置 $Q_i$，$r_i$ 表示第 $i$ 条蛇的长度，$del$ 表示当前删掉了多少条蛇，$k$ 表示为题面中的 $m$，即删掉蛇的总长度。
  
  当 $opt = 1$ 时，表示添加一条蛇。我们用一个 $cnt$ 来记录当前蛇的数量。当 $cnt = 1$ 时，表示当前是添加的第一条蛇，所以将 $Q_1$ 记录为 0，$r_1$ 直接记录为 $l$。否则 $Q_{cnt}$ 标记为上一条蛇的头部的位置加上上一条的长度，即为当前这一条蛇的头部的位置，$r_{cnt}$ 则直接标记为 $l$。

  当 $opt = 2$ 时，表示删除位于最前面的一条蛇。这时 $del$++，表示删除的蛇加一，然后 $k$ 加上 $r_{del}$，表示删除的蛇的总长度加上当前删除的这条蛇的长度，便于下面查询。

  当 $opt = 3$ 时，表示查询第 $l$ 条蛇的头部的位置。这时前面记录的 $k$ 就派上用场了，这里我们直接用第 $l$ 条蛇的头部的位置减去 $k$ 即为当前查询的答案。

## AC 代码


```cpp
#include<bits/stdc++.h>

using LL = long long; //注意要开 long long
using namespace std;

LL q, cnt, Q[300005], k, i, del, r[300005];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> q;
	while (q--) {
		int opt, l;
		cin >> opt;
		if (opt == 1) { //从尾部添加一条蛇
			cin >> l;
			++cnt;
			if (cnt > 1) Q[cnt] = Q[cnt - 1] + r[cnt - 1], r[cnt] = l;
			else Q[cnt] = 0, r[cnt] = l;
//			for(int j=1;j<=cnt;j++) cout<<Q[j]<<' ';
//			cout<<endl;
		} else if (opt == 2) { //删除位于最前面的那条蛇
			del++;
			k += r[del];
		} else { //查询第l条蛇的头部的位置
			cin >> l;
			cout << Q[l + del] - k << endl;
		}
	}
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

题意：维护一个队列。有三种操作：队尾加入元素，队首删除元素，询问队列中前 $x$ 个元素的总和。       
首先因为总操作数 $\le 3 \times 10^5$，所以不能暴力求和。        
可以使用前缀和思想，维护加入的元素前缀和和被删除的元素总和。则队列中前 $x$ 个元素总和为二者之差。    
坑：问你第 $x$ 个元素的坐标，其实是问你前 $x-1$ 个元素的总和。      
还有记得开 long long。
```cpp
// LUOGU_RID: 199108872
#include<stdio.h>
int n,a,b,l,r;long long qz[300005];
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&a);
		if(a==2) l++;
		else if(a==3) scanf("%d",&b),printf("%lld\n",qz[b+l-1]-qz[l]);
		else scanf("%d",&b),r++,qz[r]=qz[r-1]+b;
	}
}
```

---

## 作者：xmy201315 (赞：0)

这道题我用的是前缀和来做的。

如果我们每次在需要输出时进行将蛇的总长度（除了最后一条）加一遍，这个时候，我们会发现代码会 TLE。

我们用前缀和。我们首先使用 $p$ 数组将这几条蛇的总长度的前缀和记录下来，我们再用双指针记录队列的头和尾。这时
，$p_{f-1}$ 就是所有出了这个队列的蛇的总长度，$p_{f+k-2}$ 即为题目中叫你求的这前 $k$ 条蛇的总长度。我们再两个一减，就是答案啦。

**AC code：**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 300010
#define sz(s) s.size()
#define db double
#define mod 1000000007
#define P 998244353
#define ll long long
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define per(i,l,r) for(ll i=l;i>=r;i--)
#define rep(i,l,r) for(ll i=l;i<=r;i++)
#define in insert
#define y1 y142857
//pair<ll,ll> PII;
//unordered_map<int,int> f;
vector<int>edges[N];
//set<int>c;
int huiwen(int x){int b[100],l=0,t=x;while(t!=0){b[++l]=t%10;t/=10;}for(int i=1,j=l;i<=j;i++,j--)if(b[i]!=b[j])return 0;return 1;}
int prime(int x){for(int i=2;i*i<=x;i++)if(x%i==0)return 0;return 1;} 
inline int gcd(int a,int b){if(a<b)gcd(b,a);if(!b)return a; return gcd(b,a%b);} 
inline int lcm(int a,int b){return a*b/gcd(a,b);}
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline void pri(int x){
    if(x==1)putchar(' ');
    if(x==2)putchar('\n');
}
inline void put(int x){
    if(x==1)puts("Yes");
    if(x==2)puts("No");
    if(x==3)puts("YES");
    if(x==4)puts("NO");
    if(x==5)puts("yes");
    if(x==6)puts("no");
}
inline void write(ll x,ll w,ll e){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10,w,e);
    putchar(x%10+'0');
    if(x==e){
        if(w==1)putchar(' ');
        if(w==2)putchar('\n');
    }
    return;
}
int q=read(),f=1,r,a[N],l=0;ll p[N];
void sovel(){
	rep(i,1,q){
		int type=read();
		if(type==1){cin>>a[++l];r++;if(l==1)continue;else p[l-1]=p[l-2]+a[l-1];}
		else if(type==2)f++;
		else{
			int k;
			cin>>k;
			cout<<p[f+k-2]-p[f-1]<<"\n";
		}
	}
}
int main(){
    int _=1;
    while(_--)sovel();
}
```

---

## 作者：TainityAnle (赞：0)

### 题意

你需要维护一个队列，有三种操作。

1. 插入一个长度为 $l$ 的蛇。
2. 将队头出队，剩下的蛇都往前走。
3. 查询当前队列中第 $k$ 个蛇的头的位置。

### 思路

记 $id_i$ 表示假设所有蛇都不出队，第 $i$ 条蛇的头的位置。只需要维护一个 $cur$，$cur$ 只加不减，只要插入就把 $cur$ 加上 $l$。

记 $d$ 表示已出队的蛇的总长。不难发现，当前每条蛇的蛇头就是 $id_i-d$。

每有一条蛇出队，第 $k$ 条蛇的编号就会加一。记 $del$ 表示已经有多少条蛇出队，则每次查询的答案是 $id_{x+del}-d$。

### AC Code

赛时代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int Q,op,d,x,cur,id[N],cnt,del;
queue<int> q;
signed main(){
	cin>>Q;
	while(Q--){
		cin>>op;
		if(op==1){
			cin>>x;
			id[++cnt]=cur;
			cur+=x; 
			q.push(x);
		}
		if(op==2){
			d+=q.front();
			del++;
			q.pop();
		}
		if(op==3){
			cin>>x;
			cout<<id[x+del]-d<<endl;
		}
	}	return 0;
}
```

---

## 作者：KfZ_awa (赞：0)

题目传送门：[[ABC389C] Snake Queue](https://www.luogu.com.cn/problem/AT_abc389_c)

## 前置知识
+ 前缀和
## 题目简述
有一条空的蛇队列，操作为 `1` 时从队列尾部加入新蛇，操作为 `2` 时将开头的蛇弹出，操作为 `3` 时输出一头蛇的头部位置。
## 解题思路
可以发现我们可以维护前缀和，每弹出一条蛇时对后面的蛇的长度前缀和减去此条蛇的长度即可。又因为弹出的蛇总长度为最后被弹出的蛇的长度前缀和，可知我们在操作为 `3` 时输出 $sum_{k+start-1}-sum_{start}$（$start$ 指最后被弹出的蛇的位置）
## 代码
```cpp
#include<cstdio>
long long sum[300001],Q,op,val,start,end;
int main()
{
	scanf("%lld",&Q);
	while(Q--)
    {
		scanf("%d",&op);
		if(op==2)start++; //将开头弹出
		if(op==1)
        {
			scanf("%d",&val);
			sum[end+1]=sum[end]+val; //前缀和
			end++; //末尾＋1
		}
		if(op==3)
        {
			scanf("%d",&val);
			printf("%lld\n",sum[val+start-1]-sum[start]);
		}
	}
}
```
~~新人第一次投题解，求审核大大通过~~

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[ABC389C](https://www.luogu.com.cn/problem/AT_abc389_c)

## Statement

维护一个队列，里面存的是一条一条的线段，有如下操作：

$1 \enspace l$：加入一条长度为 $l$ 的线段，若当前队列为空，该线段的头为 $0$ 下标，否则为队尾线段头下标加上队尾线段长对应下标。

$2$：删除队头线段，队内线段头下标减去队头线段长度。

$3 \enspace k$：查询队伍中第 $k$ 条线段的头下标。

$Q \leq 3 \times 10^5,l \leq 10^9$

## Solution

维护一个队列，里面存线段头下标和长度，每次操作 $2$ 相当于给线段头下标加了一个偏移量，输出的时候减去即可。

手写队列或 STL 均可实现。

## Code

赛时代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 3e5 + 10;
int Q, head, tail, delta;
struct Snake { int st, Len; } q[MAXN];

signed main() {
	cin.tie (0) -> sync_with_stdio (0);
	cout.tie (0) -> sync_with_stdio (0);
	cin >> Q;
	while (Q --) {
		int opt, k;
		cin >> opt;
		if (opt == 1) {
			cin >> k;
			if (head == tail)
				q[++ tail] = (Snake){0, k};
			else
				q[++ tail] = (Snake){q[tail - 1].st + q[tail - 1].Len, k};
		}
		if (opt == 2)
			delta += q[++ head].Len;
		if (opt == 3) {
			cin >> k;
			cout << q[head + k].st - delta << '\n';
		}
	}
	return 0;
}
```

---

## 作者：sjh0626 (赞：0)

## 题意概括
#### 问题陈述

有一个队列。

最初，队列一条蛇都没有的。

你会得到 $Q$ 个查询，这些查询应按给出的顺序处理。查询有三种类型：

- 类型 $1$：以 `1 l` 的形式给出。一条长度为 $l$ 的蛇会被添加到队列的末尾。如果添加前队列为空，则新添加的蛇的头部位置为 $0$；否则，它就是队列中最后一条蛇的头部坐标与最后一条蛇的长度之和。
- 类型 $2$：以 "2 "的形式给出。队列最前面的蛇离开队列。保证此时队列不是空的。假设 $m$ 是离开队列的蛇的长度，那么队列中剩余的每一条蛇的头部坐标都会减少 $m$。
- 类型 $3$：以 `3 k` 的形式给出。输出距离队列最前面 $k$ 的蛇的头部坐标。保证此时队列中至少有 $k$ 条蛇。
## 思路分析
一道模拟队列题。

对于类型 $1$，我们在添加蛇时记录尾部，方便计算长度。

对于类型 $2$，我们可以增加尾部，在类型 $3$ 时方便计算头部。

对于类型 $3$，类似于前缀和，我们可以将在没删除前的第 $1 \sim tail+k-1$ 条蛇的长度减去 $1 \sim tail$ 的长度，就可以得出现在第 $k$ 条蛇的长度。
## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
#define PII pair<int,int>
using namespace std;
long long q,op,k,head,pos[400000],tail;
int main(){
	cin>>q;
	for(int i=1;i<=q;i++){
		cin>>op;
		if(op==1){
			cin>>k;
			head++;
			pos[head]=pos[head-1]+k; //记录尾部 
		}
		else if(op==2){
			tail++;
		} 
		else{
			cin>>k;
			cout<<pos[tail+k-1]-pos[tail]<<"\n"; //计算坐标 
		}
	}
	sjh0626s code;
}
```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

有一个初始为空的队列和 $Q$ 次询问，每次询问为一种类型 $type$。若 $type=1$ 则新建一条长度为给定的 $l$ 的线段，左端点坐标为上一条新建线段的右端点。若 $type=2$ 则删除最左边的线段，并置下一条线段左端点坐标为 $0$，后面所有线段依次接上来。若 $type=3$ 则查询当前从左数给定的第 $k$ 条线段的左端点坐标，数据范围 $Q\le 3\times 10^5$。

## 解题思路

使用数组 $a$ 模拟队列，存储线段 $i$ 的左端点 $a_{i,0}$ 和右端点坐标 $a_{i,1}$。$type=1$ 时队列末尾 $tail+1$，$type=2$ 时队列头 $head+1$。因为删除队头时后面的坐标不能暴力减掉（会超时），所以可以使用相对位置的方法，累加每次所删掉线段的左端点，记为 $sum$，查询的时候减掉即可。若新建第 $i+1$ 条线段，则有 $a_{i+1,0}=a_{i,1},a_{i+1,1}=a_{i+1,0}+l$，若查询目前第 $i$ 条线段的左端点坐标，则结果为 $a_{head+k-1,0}-sum$。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll q,t,k,a[300001][2],sum,head=1,tail;

int main()
{
	q=read();
	
	while(q--)
	{
		t=read();
		
		if(t<2)
		{
			k=read(); ++tail;
			a[tail][0]=a[tail-1][1];
			a[tail][1]=a[tail][0]+k;
		}
		
		else if(t<3) sum+=a[head][1]-a[head][0], ++head;
		else k=read(), write(a[k+head-1][0]-sum), endl;
	}
	
    return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

这题不能写暴力，否则 TLE。

先放一个暴力代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main () {
    int Q; cin >> Q;
    deque <pair <int, long long> > snakeQueue;
    long long head = 0; 
    for (int i = 0; i < Q; i ++) {
        int op; cin >> op;
        if (op == 1) { 
            int l; cin >> l;
            if (snakeQueue.empty ()) head = 0;
          	else head += snakeQueue.back ().first;
            snakeQueue.push_back ({l, head}); 
        } 
		else if (op == 2) { 
            int m = snakeQueue.front().first; 
            snakeQueue.pop_front (); 
            for (auto& it : snakeQueue) it.second -= m;
            head -= m; 
        } 
		else if (op == 3) { 
            int k;
            cin >> k;
            cout << snakeQueue[k - 1].second << endl; 
        }
    }
    return 0;
}
```

考虑优化。可以用前缀和维护它，出队的时候累计一个变量，查询的时候减去它就行了。

最最后，十年 OI 一场空，_____________。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 3e5 + 10;
int w, x, head = 1, tail = 1, Queue[MAXN], sum[MAXN];
void read () {
	int op; cin >> op;
	if (op == 1) {
		cin >> x;
		Queue[tail ++] = x;
		sum[tail] = sum[tail - 1] + x; 
	}
	else if (op == 2) {
		w += Queue[head]; 
		head ++;
	}
	else if (op == 3){
		int s = 0;
		cin >> x;
		cout << sum[head + x - 1] - w << endl;
	}	
}
signed main () {
	int Q; cin >> Q;
	while (Q --) read ();
	return 0;
}
```

---

