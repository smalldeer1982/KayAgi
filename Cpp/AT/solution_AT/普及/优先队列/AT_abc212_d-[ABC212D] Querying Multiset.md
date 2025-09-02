# [ABC212D] Querying Multiset

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc212/tasks/abc212_d

高橋君は何も書かれていないたくさんのボールと $ 1 $ つの袋を持っています。 最初、袋は空で、高橋君は $ Q $ 回の操作を行います。 それぞれの操作は以下の $ 3 $ 種類のうちのいずれかです。

- 操作 $ 1 $ : まだ何も書かれていないボール $ 1 $ つに整数 $ X_i $ を書き込み、袋に入れる。
- 操作 $ 2 $ : 袋に入っているすべてのボールについて、そこに書かれている数を、それに $ X_i $ を加えたものに書き換える。
- 操作 $ 3 $ : 袋に入っているボールのうち書かれている数が最小のもの（複数ある場合はそのうちの $ 1 $ つ）を取り出し、そこに書かれている数を記録する。その後、そのボールを捨てる。

$ 1\leq\ i\leq\ Q $ について $ i $ 回目の操作の種類 $ P_i $ および操作 $ 1 $ , $ 2 $ における $ X_i $ の値が与えられるので、操作 $ 3 $ において記録された数を順に出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ Q\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ P_i\ \leq\ 3 $
- $ 1\ \leq\ X_i\ \leq\ 10^9 $
- 入力は全て整数である。
- $ P_i=3 $ であるような $ i $ が $ 1 $ つ以上存在する。
- $ P_i=3 $ であるとき、 $ i $ 回目の操作の直前の時点で、袋には $ 1 $ つ以上のボールが入っている。

### Sample Explanation 1

高橋君は次のように操作を行います。 - $ 3 $ の書かれたボールを袋に入れる。 - $ 5 $ の書かれたボールを袋に入れる。 - 今、袋には $ 3 $ の書かれたボールと $ 5 $ の書かれたボールが入っているため、このうち小さい $ 3 $ の書かれたボールを取り出し、 $ 3 $ を記録した後に捨てる。 - 今、袋には $ 5 $ の書かれたボールのみが入っているため、この数を $ 5+2=7 $ に書き換える。 - 今、袋には $ 7 $ の書かれたボールのみが入っているため、このボールを取り出し、 $ 7 $ を記録した後に捨てる。 よって、記録された順に $ 3 $ , $ 7 $ を出力します。

### Sample Explanation 2

答えが $ 32 $ bit整数に収まらないことがある事に注意してください。

## 样例 #1

### 输入

```
5
1 3
1 5
3
2 2
3```

### 输出

```
3
7```

## 样例 #2

### 输入

```
6
1 1000000000
2 1000000000
2 1000000000
2 1000000000
2 1000000000
3```

### 输出

```
5000000000```

# 题解

## 作者：Redamancy_Lydic (赞：4)

## 题意

维护一个集合，使得其支持插入元素，区间修改，单点（最小数）删除三种操作。

## 分析

~~不会有人去用线段树的吧~~。首先看到最小值，想到小根堆。然后考虑前两种操作，关键在于操作二。

把根里面的每一个元素遍历更新显然不符合时间复杂度要求，考虑如何把操作二变为单点修改。所以我们不难想到，用一个值 $t$ 来表示当前的增加量，这样操作二可以解决。在这种情况下：

+ 对于操作一，把 $t$ 看作后面插入元素所需的减少量，那么插入的数字 $x$ 可以用 `q.push(x-t)` 来代替。

+ 对于操作三，只需要输出堆里最小元素加上 $t$ 的值即可。

然后就可以写了。

#Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
    int s=0,w=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
    while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
    return w*s;
}//快读
int Q,t;
priority_queue<int,vector<int>,greater<int> > q;//小根堆
signed main()
{
//	freopen("xxx.in","r",stdin);
//	freopen("xxx.out","w",stdout);
	cin>>Q;
	while(Q--)
	{
		int op=read();
		if(op==1)
		{
			int x=read();
			q.push(x-t);//操作一
		}
		else if(op==2)
		{
			int x=read();
			t+=x;//操作二
		}
		else if(op==3)
		{
			printf("%lld\n",q.top()+t);
			q.pop();//别忘了删除
		}
	}
   return 0;
}
```


---

## 作者：Coffee_zzz (赞：3)

一眼题。

### 分析

维护一个小根堆。

比较讨厌的主要就是操作 $2$ 了，需要给堆中所有元素加 $X$。不难想到不改变堆中的元素，而是给之后插入的所有元素减去 $X$，相对差不改变。

执行操作 $1$ 时可以给当前插入的元素减去之前所有 $X$ 的和，执行操作 $3$ 时再给当前取出的元素加上之前所有的 $X$，可以类似地看做一个差分。

最后提醒一句不开 `long long` 见祖宗。

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
priority_queue <int,vector<int>,greater<int> > q;
signed main(){
	ios::sync_with_stdio(0);
	int t,p,x,k=0,a;
	cin>>t;
	for(int temp=0;temp<t;temp++){
		cin>>p;
		if(p==1){
			cin>>x;
			a=x-k;
			q.push(a);
		}
		else if(p==2){
			cin>>x;
			k=k+x;
		}
		else{
			a=q.top();
			q.pop();
			cout<<a+k<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：zibenlun (赞：2)

# 前置知识
首先看到要取出最小值，那么一定就是优先队列了。

### [优先队列](https://baike.baidu.com/item/%E4%BC%98%E5%85%88%E7%BA%A7%E9%98%9F%E5%88%97/6737671?fr=ge_ala)


# 思路

由于输出的是最小值，所以我们要用到的是小根堆，定义有稍许不同。
```cpp
priority_queue<int,vector<int>,greater<int>>q;
```
解决了优先队列看到他还有修改操作，要是整体修改肯定是会超时的，所以我们可以想到一个类似于前缀和的算法。

如果把每一次添加的数当做一个数组，那么我们可以得出一个数所增加的值一定是它添加之后增加的数到他取出前的数的前缀和，那么我们可以找到规律，如果一个数添加上目前增加的所有的数，那么它比真正的值所大的就是他之前的数的总和，那么由此我们可以判断出，每一次添加一个数的时候，我们可以添加这个数减去之前增长的值，这样一来可以快速记录当前的值，同时我们也更好地维护优先队列中数的顺序。（如果没有看懂就看代码吧）

# CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
//十年OI一场空，不开long long见祖宗 
priority_queue<long long,vector<long long>,greater<long long>> q;
long long cnt,n,x;//cnt统计一共加了多少数 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	//前三行是加快cincout速度的
	//本人懒得写scanf与快读 
	cin>>n;
	for(int i=1,h;i<=n;i++){
		cin>>h;
		if(h==1){
			cin>>x;
			q.push(x-cnt);
		}
		else if(h==2){
			cin>>x;
			cnt+=x;
		}
		else {
			cout<<q.top()+cnt<<"\n";
			//换行使用'\n'速度更快 
			q.pop();
		}
	}
	return 0;
	//return 0;是好习惯 
}
```

---

## 作者：Engulf (赞：1)

大水题。

我们直接用 `multiset` 维护之。

`multiset` 可维护重复的数字，`set` 会自动去重。

`multiset` 可以维护一堆数，支持插入、删除，内部元素自然有序，也就是说最小值就是 `*s.begin()`，$s$ 是一个 `multiset`。

操作二显然不能暴力修改，考虑维护一个永久标记 `add`，这样操作三的时候直接输出 `*s.begin() + add` 即可，$s$ 是我们的 `multiset`。

但这样会有一个问题，修改是对集合内的数而言的，对于修改之后再插入的数怎么办呢？既然我们输出的时候加上了 `add`，我们插入的时候不妨直接插入原数减去 `add`，这样就消除了影响了。

感觉这个套路跟郁闷的出纳员挺像的。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    multiset<ll> s;
    ll add = 0;
    while (q--) {
        int op;
        ll x;
        cin >> op;
        if (op == 1) cin >> x, s.insert(x - add);
        if (op == 2) cin >> x, add += x;
        if (op == 3) cout << *s.begin() + add << "\n", s.erase(s.begin()); // 这里注意一下，如果参数传入对应的数字，将会删除所有的值为传入参数的数，所以删除一个的正确方法是删除迭代器。
    }
    return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc212_d)

看到第三个操作是将集合最小的数删除，立马就会想到小根堆。

用小根堆来维护集合，并用 $now$ 记录当前的累加数。
- 对于第一种操作，将 $x-now$ 放入小根堆，这样就可以体现出 $x$ 与已经在堆中的元素的差距。
- 对于第二种操作，将 $now$ 加上 $x$。
- 对于第三种操作，此时的堆顶是放入该元素时的 $x$ 减去当时的 $now$，而 $now$ 经历了变化，所以 $x$ **增加了**现在的 $now$ 减去当时的 $now$。但是该元素被放进堆中时已经减过 $now$ 了，所以输出当前堆顶加上 $now$ 即可。然后删除堆顶。

核心代码：
```cpp
priority_queue<ll,vector<ll>,greater<ll> >q;//小根堆
void solve()
{
	int opt;
	ll x;
	cin>>opt;
	if(opt==1) cin>>x,q.push(x-now);//加入操作
	else if(opt==2) cin>>x,now+=x;//累加
	else cout<<q.top()+now<<'\n',q.pop();//删除操作
}
```

---

## 作者：Chenyichen0420 (赞：0)

# 题目大意

给你 $n$ 次操作，每次操作有三类：

- 1.将一个新的数放入序列，使整个序列依旧单调递减。
- 2.将此时在序列中的数加上另一个数。
- 3.取出此时序列中的最小数，并输出。

# 解法分析

不开 `longlong` 见祖宗！！！！！！！

上面的仅作提醒，本人并没有采坑。

这里我们可以用优先队列来维护，十分的方便。

但是我们又有一个问题，第二个操作怎么办？

我们可以学习一下线段树的做法，用一个 `lazy` 标记之类的东西将要加的数存储下来，输出时再加上就行了。

但是还有一个细节需要处理，就是后加进来的数是不会加前面加的数的！

这个也好办，动一动脖子上面的那个玩意想一想就知道了：输入进来的时候减掉 `lazy` 标记的数就行了呀！

废话不多说了，精简小代码代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,v,c,lz; priority_queue<int,vector<int>,greater<int> >pq;
inline int read(){
	register int r=0; register char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9') r=(r<<3)+(r<<1)+(c^48),c=getchar();
	return r;
}
inline void write(int x){
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
signed main(){
    n=read();
    while(n--){
    	c=read();
    	if(c==1) v=read(),pq.push(v-lz);
		else if(c==2) v=read(),lz+=v;
		else write(pq.top()+lz),putchar('\n'),pq.pop();
	}
	return 0;
}
```

---

## 作者：zhu_wen (赞：0)

# Querying Multiset
## 主要题意
给定一个集合，我们需要维护几个操作，最终输出结果。
## 主要思路
我们可以维护一个优先队列，来进行模拟。但注意，如果直接进行模拟的话，会超时。所以我们可以利用**前缀和**的思想来进行做题。我们有以下几个操作。
- 如果操作类型是 $1$，表示将一个数 $x$ 放入集合中，我们就将 $x-k$ 放入队列。
- 如果操作类型是 $2$，表示将集合中的所有数都加上 $x$，就将变量 $k$ 加上 $x$。
- 如果操作类型是 $3$，表示取出栈顶，并记录下来，然后将该数从队列中出队。输出栈顶元素加上前缀变量 $k$。


## 代码
```cpp
/*
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fi first
#define se second
#define re register
#define swap(a, b) a ^= b, b ^= a, a ^= b
#define pb push_back
#define all(x) x.begin(), x.end()
#define fst                      \
    ios::sync_with_stdio(false); \
    cin.tie(0);                  \
    cout.tie(0);

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int Max = 1e3 + 5;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

inline int read()
{
    int x = 0;
    bool f = true;
    char c = getchar();
    while (c < 48 || c > 57)
    {
        if (c == '-')
            f = false;
        c = getchar();
    }
    while (c >= 48 && c <= 57)
        x = (x << 3) + (x << 1) + c - 48, c = getchar();
    return f ? x : -x;
}
inline void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}
inline void wsp(int x) { write(x), putchar(' '); }
inline void wel(int x) { write(x), putchar('\n'); }

struct node
{
    int x;
    bool operator<(const node &q) const
    {
        return x > q.x;
    }
};
int n;
int op, y;
priority_queue<node> pq;
int k;

signed main()
{
    fst;
    cin >> n;
    while (n--)
    {
        cin >> op;
        if (op == 1)
        {
            cin >> y;
            pq.push({y - k});
        }
        else if (op == 2)
        {
            cin >> y;
            k += y;
        }
        else
        {
            cout << pq.top().x + k << endl;
            pq.pop(); //别忘了出队
        }
    }
    return 0;
}
```


---

## 作者：Demons_Killer (赞：0)

# 解题思路：
优先队列模版题。

构建一个小根堆，每次往面加上 $x$，在建一个数储存一共额外加了多少，新添加的元素要减去这个，不然会加重。每次删除直接推出头元素，在输出这个数加上额外加的，就得出了最后的答案。

# CODE：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int,vector<int>,greater<int> > q;
int cnt;
int Q;
signed main(){
	cin>>Q;
	int op,x;
	while(Q--){
		cin>>op;
		if(op==1){
			cin>>x;
			q.push(x);
			x-=cnt;
		} 
		else if(op==2){
			cin>>x;
			cnt+=x;
		}
		else{
			cout<<q.top()+cnt<<endl;
			q.pop();
			
		}
	}
	return 0;
}

```

---

## 作者：Silence_World (赞：0)

# 思路

题意很简单，不多赘述，很明显的优先队列，维护小根堆，模拟即可。

然而就 TLE （哭），所以需要一点点的小优化，只需加一个变量来维护第二个操作，不直接模拟加而是将新进队的减去这个变量，每次执行二操作的时候加上二操作的值，最后输出的时候直接加入这个变量，结束！！！

# 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
priority_queue<int,vector<int>,greater<int> >q;
queue<int>q1;
signed main(){
	int t;
	cin>>t;
	int y=0;
	while(t--){
		int a,b;
		cin>>a;
		if(a==1){
			int x;
			cin>>x;
			q.push(x-y);
		}
		if(a==2){
			int x;
			cin>>x;
			y+=x;
		}
		if(a==3){
			cout<<q.top()+y<<endl;
			q.pop();
		}
	}
	return 0;
} 
```


---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc212_d)

## 思路

很容易想到此题应用 STL 中的 multiset 解决。

因为 $1\le Q\le 2\times 10^5$，所以很容易想到如果每次把数字集合都 $+x$ 必定会 TLE，这时我们考虑用**差分维护**。

每次读入数据后，对操作种类分来讨论。

- 定义 $sum$ 为当前累计增加的值。

**对于每次操作 $1$**：在 multiset 中插入读入的值**减去** $sum$ 的值，即可完成维护序列的操作。

**对于每次操作 $2$**：将 $sum$ 加上当前读入数据。

**对于每次操作 $3$**：读入数据后输出 ``begin()`` 的值**加上** $sum$ 的结果还原为本来应当的值，输出。之后删除 ``begin()`` 这个位置的数据。

- 数据范围大，记得开 long long。

这里不放代码了，根据上面的思路一步步写即可。

---

## 作者：Genius_Star (赞：0)

### 思路：

~~感觉 ``priority_queue`` 好慢啊~~~

发现这是一个对于堆的模板题目。

对于操作 $1$，就可以直接使用 STL 库里面的 ``push_heap`` 函数，插入这个数之后可以保持堆的性质，对于操作 $3$，我们可以直接输出 $a_1$，然后将 $a_1$ 和 $a_n$ 交换一下，使用 ``pop_heap`` 函数维护堆。

对于操作 $2$，如果我们暴力去改肯定要超时，不难发现，我们可以直接存储所有 $x$ 的和 $sum$，对于后面加入集合的元素，我们需要将其减去 $sum$，操作 $3$ 的时候，输出 $a_1+k$，这样我们减去的又加回来了，元素值还是不变的。

对于此题我们要维护的是小根堆，用数组怎么办呢？没事，将其转换为负数就行了。

### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000100;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll a[N],q,op,x,sum=0,l=1;
int main(){
	q=read();
	while(q--){
		op=read();
		if(op==1){
			x=read()-sum;
			a[l++]=-x;
			push_heap(a+1,a+l);
		}
		else if(op==2)
		  sum+=read();
		else{
			write(-(a[1])+sum),putchar('\n');
			swap(a[1],a[l]);
			pop_heap(a+1,a+l);
			l--;
		}
	}
	return 0;
}
```


---

## 作者：shyr (赞：0)

$\sf{Statement}$
---

给定一个集合和 $t$ 次操作，每个操作可能是以下操作之一：

- 第一个操作给定整数 $x$，表示将 $x$ 放入集合。

- 第二个操作给定整数 $x$，表示将集合的数分别加上 $x$。

- 第三个操作将集合最小的数删除。

对于每个第三个操作，输出你删去的数。

$\sf{solution}$
---

这题唯一的难度在于处理第二个操作。

很容易想到对于每个第二个操作，集合内的数相对大小不变。

令后加入的数为 $a$，最早加入的数为 $b$，第二次操作加上的数的总和为 $\Delta$。

那么就是 $a$ 与 $b+\Delta$ 作比较，等价为 $a-\Delta$ 与 $b$ 作比较。

做完了。

$\sf{Code}$
---
```cpp
int t,op;
LL k,delta;
multiset<LL> S;
signed main(){
	read(t);
	while(t--){
		read(op);
		if(op==1)read(k),S.insert(k-delta);
		if(op==2)read(k),delta+=k;
		if(op==3)printf("%lld\n",*S.begin()+delta),S.erase(S.begin());
	}
	return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

## 题意

给出三种操作：
- $1\;X_i$ 表示向序列里面加入一个大小为 $X_i$ 的元素。
- $2\;X_i$ 表示序列里面所有的元素加上 $X_i$。
- $3$ 输出序列里面最小的元素。

## 思路

用一个优先队列始终维护最小值。

再维护一个 $add$ 表示序列里的元素需要加的，新加入的减去 $add$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int,vector<int>,greater<int>>q;
signed main(){
	int n,add=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		int op,x;
		cin>>op;
		if(op==1){
			cin>>x;
			x-=add;
			q.push(x);
		}
		if(op==2){
			cin>>x;
			add+=x;
		}
		if(op==3){
			cout<<q.top()+add<<"\n";
			q.pop();
		}
	}
	return 0;
}
```

---

## 作者：_zexal_ (赞：0)

## 思路
显然，对于每一个数，我们不可能每次执行加的操作都拿出来加，那样一定会超时，那么我们不妨最后输出时再加。这样，我们维护一个小根堆，每次拿堆顶即可。但是，我们还需要注意一个事，那就是对于加操作，不是所有数都能加到的，那么我们怎么保证这样的情况呢？事实上，只需要加入时减去前面加过的数值，保持他们的相对大小就好了。
#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define int long long
const int Maxn=4e6;
int a,b,n,m,k,q,opt,ans;
priority_queue<int,vector<int>,greater<int> > Q;
 
signed main(){
	cin>>n;
	F(i,1,n){
		cin>>opt;
		if(opt!=3){
			cin>>k;
			if(opt==1) Q.push(k-ans);
			else ans+=k;
		}
		else {
			cout<<Q.top()+ans<<endl;
			Q.pop();
		}
	}
	return 0;
}
```
这里再推荐[一道题](https://www.luogu.com.cn/problem/P2827)，是这道题的加强版。


---

## 作者：loser_seele (赞：0)

如果没有 $ 2 $ 操作，朴素优先队列即可。

其实加入 $ 2 $ 操作后也大体类似，维护一个全局变化值 $ delta $，在加操作时直接加 $ delta $ 即可，则对于 $ 3 $ 操作设队列内最小值为 $ x $，则答案显然为 $ x+delta $，因为全局加不会改变元素相对大小。插入操作类似，插入 $ x-delta $ 即可抵消影响。

时间复杂度 $ \mathcal{O}(q\log{q}) $，可以通过。这里使用 STL 的优先队列实现，注意要开 long long。

代码：

```cpp
#import <bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int,vector<int>,greater<int> >p;
signed main()
{
int q,delta=0;
cin>>q;
while(q--)
{
int op;
cin>>op;
if(op==1)
{
int x;
cin>>x;
p.push(x-delta);
}
else if(op==2)
{
int x;
cin>>x;
delta+=x;
}
else
cout<<(p.top()+delta)<<'\n',p.pop();
}
}
```


---

## 作者：zhanghao233 (赞：0)

# [题目](https://www.luogu.com.cn/problem/AT_abc212_d)大意

- 给定整数 $x$，将 $x$ 放入集合；

- 给定整数 $x$，将集合的数分别加上 $x$；

- 将集合最小的数输出并删除；

# 思路
由第三个操作可以得出结论：要维护一个小根堆

考虑第二个操作，想到加法结合律，得出在输出时可以把前面的所有二操作的 $x$ 总和相加。

我们要考虑后加入的不用再次加入前面的所有二操作的 $x$ 总和，可以加入集合时减去 $x$ 总和，输出时用最新 $x$ 总和相加

```cpp
if(opt==1)
	q.push(read()-add);
if(opt==2)
	add+=read();
if(opt==3){
	cout<<q.top()+add<<"\n";
	q.pop();
}
```

---

