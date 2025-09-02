# [USACO08NOV] Light Switching G

## 题目描述

Farmer John tries to keep the cows sharp by letting them play with intellectual toys. One of the larger toys is the lights in the barn. Each of the $N (2 \le N \le 10^5)$ cow stalls conveniently numbered $1\ldots N$ has a colorful light above it.

At the beginning of the evening, all the lights are off. The cows control the lights with a set of N pushbutton switches that toggle the lights; pushing switch i changes the state of light i from off to on or from on to off.

The cows read and execute a list of $M(1\le M \le 10^5)$ operations expressed as one of two integers ( $0 \le$ operation $\le 1$ ).

The first kind of operation (denoted by a $0$ command) includes two subsequent integers $S_i$ and $E_i (1 \le S_i \le E_i \le N)$ that indicate a starting switch and ending switch. They execute the operation by pushing each pushbutton from $S_i$ through $E_i$ inclusive exactly once.

The second kind of operation (denoted by a $1$ command) asks the cows to count how many lights are on in the range given by two integers $S_i$ and $E_i (1 \le S_i \le E_i \le N)$ which specify the inclusive range in which the cows should count the number of lights that are on.

Help FJ ensure the cows are getting the correct answer by processing the list and producing the proper counts.

农夫约翰试图让奶牛玩智力玩具来保持它们的敏锐。谷仓里的灯是较大的玩具之一。$N (2 \le N \le 10^5)$ 个牛栏编号为 $1 \ldots N$，每个牛栏上面都有一盏灯。起初所有的灯都关着。

共有 $M$ 次操作，分为两种。
1. 指定一个区间 $[S_i,E_i]$，然后改变编号在这个区间内的灯的状态（把开着的灯关上，关着的灯打开）；
2. 指定一个区间 $[S_i,E_i]$，要求你输出这个区间内有多少盏灯是打开的。







## 说明/提示

| 数据点编号 | $N$ | $M$ |
| :----------: | :----------: | :----------: |
| $1\sim 2$ | $\le 100$ | $\le 100$ |
| $3\sim 4$ | $\le 1000$ | $\le 1000$ |
| $5\sim 6$ | $\le 10000$ | $\le 10000$ |
| $7\sim 8$ | $\le 10^5$ | $\le 100$ |
| $9\sim 10$ | $\le 100$ | $\le 10^5$ |
| $11\sim 12$ | $\le 1000$ | $\le 10^5$ |
| $13\sim 14$ | $\le 10^5$ | $\le 1000$ |
| $15\sim 16$ | $\le 10000$ | $\le 10000$ |
| $17\sim 18$ | $\le 10$ | $\le 10^5$ |
| $19\sim 20$ | $\le 2000$ | $\le 10^6$ |


## 样例 #1

### 输入

```
4 5
0 1 2
0 2 4
1 2 3
0 2 4
1 1 4```

### 输出

```
1
2```

# 题解

## 作者：Liu_zj (赞：20)

这道题是练习线段树的优秀入门题，切掉他说明你对算法的理解程度已经不止局限于模板。

灯只有亮，暗两种状态，可以用0,1表示。那么怎样让0变成1,1变成0呢？

我们选择XOR（异或）。符号是^，属于二进制运算符的一种。作用与名称相似，“异”即为1，“同”即为0。1^1=0,1^0=1,0^0=1。
我们发现，只要将0或1异或1就可以完成0、1的转换。

询问区间的亮灯的数量，所以线段树维护亮灯的数量。一个区间只有亮灯和灭灯，所以异或之后区间亮灯的数量就是异或前区间灭灯的数量。
即
```
if异或
区间亮灯数=区间灯总数-区间亮灯数
```
区间修改需要懒标记（lazy），我们又一次惊奇地发现，区间修改两次等于没有修改，与灯的状态相似，所以lazy的变化也可以用异或。

在具体的代码实现中，由于所有的灯开始都是灭的，所以省去了建树的操作。

码风清奇
```
#include<bits/stdc++.h>
using namespace std;
int lz[1000001];//懒标记
long long sum[1000001];//区间亮灯和
void update(int now)
{
	sum[now]=sum[now<<1]+sum[now<<1|1];//大区间的亮灯和等于左右区间的亮灯和的和。。。
}
void pushdown(int now,int l,int r)//标记下传
{
	int mid=(l+r)>>1;
	if(lz[now]==1)
	{
		lz[now<<1]^=1;//lz的改变用异或
		lz[now<<1|1]^=1;
		sum[now<<1]=(mid-l+1-sum[now<<1]);//区间灯数-亮灯数
		sum[now<<1|1]=(r-mid-sum[now<<1|1]);
		lz[now]=0;
	}
}
void change(int now,int l,int r,int lgo,int rgo)//区间修改
{
	if(l>=lgo&&r<=rgo)//如果当前区间（l,r）在修改区间（lgo,rgo）中
	{
		lz[now]^=1;//lz异或
		sum[now]=(r-l+1-sum[now]);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(now,l,r);//别忘了标记下传
	if(lgo<=mid)
	change(now<<1,l,mid,lgo,rgo);
	if(rgo>mid)
	change(now<<1|1,mid+1,r,lgo,rgo);
	update(now);//修改后更新
}
long long find(int now,int l,int r,int lgo,int rgo)//区间查询
{
	long long ans=0;
	if(l>=lgo&&r<=rgo)//如果当前区间（l,r）在查询区间（lgo,rgo）中
		return sum[now];//返回值
	int mid=(l+r)>>1;
	pushdown(now,l,r);//标记下传double
	if(lgo<=mid)
	ans+=find(now<<1,l,mid,lgo,rgo);
	if(rgo>mid)
	ans+=find(now<<1|1,mid+1,r,lgo,rgo);
	return ans;
}
int main()
{
	int n,m,c,a,b;
	cin>>n>>m;//不必建树
	for(int i=1;i<=m;i++)
	{
		cin>>c>>a>>b;
		if(c==0)
			change(1,1,n,a,b);
		if(c==1)
			cout<<find(1,1,n,a,b)<<endl;
	}
}
```

做完这道题可以水一下双倍经验题目

[P3870 [TJOI2009]开关](https://www.luogu.org/problemnew/show/P3870)

这道题需要建树

[P2574 XOR的艺术](https://www.luogu.org/problemnew/show/P2574)



---

## 作者：mdzzzzzzzzzz (赞：11)

# 虽然我发了这篇题解后数据很有可能会加强

但我还是要发这篇题解

因为

# 这是一道模拟（纯暴力）题！！！

### 具体的代码如下，暴力我就懒得讲了

算了，忍不住还是要讲一下（代码后面有）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,zt[100020],a,b;
int main()
{
//	freopen("light.in","r",stdin);//这个千万不能加！
//	freopen("light.out","w",stdout);//这个也是！
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int pd;
		scanf("%d%d%d",&pd,&a,&b);
		if(pd==1)
		{
			int ans=0;
			for(int i=a;i<=b;i++)
			{
				if(zt[i])//灯开着就计入答案
				{
					ans++;
				}
			}
			printf("%d\n",ans);
		}
		else
		{
			for(int i=a;i<=b;i++)
			{
				if(zt[i])//如果灯开着，关上
				{
					zt[i]=0;
				}
				else//如果灯关着，打开
				{
					zt[i]=1;
				}
			}	
		}
	}
	return 0;
}
```

由题目可知道，这道题就是一个区间修改（整个区间都改变）

灯开了，就关上，灯关了，就打开。

1个for循环直接修改

再用一个for循环直接统计a到b里面所有开启的灯

输出

读者：怎么会那么简单？说好要线段树呢？

作者：额......作者打不来

---

## 作者：dailt (赞：8)

## 看到大佬们纷纷用线段树切掉了这个题，那我就来写一个用树状数组搞的题解吧（代码只有30多行哦）
首先，我们发现这个题目让我进行两个操作：一个是把x到y（包括x,y）中的亮的灯变灭，灭的灯变亮。另一个操作是查询x到y中（包括x,y）有多少盏灯是亮的。

对于第一个操作，我们发现，因为一开始所有的灯都是灭的，所以当某个灯被点了奇数次时，这个灯是亮的，被点了偶数次时，这个灯是灭的。让x到y被点时，只需要让x这个位置加1,y+1这个位置加1就好了。那么如果第i盏灯的前缀和为奇数的话,说明它是亮的,否则它就是灭的（即用前缀和表示操作次数）。

 ？？？ 为啥这样可以判断某盏灯是不是亮的了呢

 这其实是用到了一点差分的思想，当然不会也没关系。

 我们发现，当x这个位置的值加1，y+1这个位置加1，那么，i（i属于x到y）的前缀和一定会增加1，而小于x的数前缀和不变（相当于没操作），大于等于y+1的数的前缀和都变大了2（点了两次相当于没点，所以也是没操作）。这样我们就可以通过求前缀和的方式来判断对于某盏灯的操作次数了。而前缀和用树状数组维护和求值的话时间复杂度是logN的，所以这个题就可以用树状数组踩过去啦。

 至于第二个操作,就直接枚举x到y的每盏灯i,求i的前缀和是奇是偶然后统计答案就ok了。
 
 下面附上比~~线段树短几十行的~~代码
 ```
#include <iostream>
#include <cstdio>
using namespace std;
int n,m;
int a[102000];
void add(int x,int k){//修改树状数组 
	for(int i=x;i<=n;i+=i&(-i))
		a[i]+=k;
}
int query(int x){//用树状数组查询前缀和 
	int ans=0;
	for(int i=x;i>0;i-=i&(-i))
		ans+=a[i];
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){//操作一 
		int chk;
		scanf("%d",&chk);
		if(chk==0){
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,1);add(y+1,1);
		}
		if(chk==1){//操作二 
			int x,y;
			scanf("%d%d",&x,&y);
			int s=0;
			for(int i=x;i<=y;i++)
				if(query(i)&1==1)//前缀和为奇数 
					s++;//答案++ 
			printf("%d\n",s);	
		}
	}
	return 0;
}
```

---

## 作者：Peter_Z (赞：7)

题目中有两种情况：亮和暗。用0表示暗，1表示亮即可。

由于n的值过大，暴力O(n^2)肯定会超时，所以用线段树。
## 线段树中的操作
1.Build

由于此题起始值均为0，所以有些写法可以不用建树。

但由于此处区间左右端点是存在结构体里面的（好获得mid和len的值），所以必须要建树。

建树的过程不难，这里就不赘述了。

2.Update

Update时需注意两个问题：值的变化和lazytag的变化。

值的变化很简单：每次操作后区间内亮的变成暗的，暗的变成亮的，所以若原来亮的个数为num，则亮的个数变为了len-num。

lazytag的变化：

首先取反后状态会变成相反的状态，而lazytag的状态只有0和1，所以只可能是0变成1，1变成0。

实现的时候取反一下就行了。

3.Pushdown

Pushdown即Tagdown，把tag传给子节点。

比如现在父节点的tag是1，子节点的tag是0。
则父节点的状态已经反过来，而子节点若想接下父节点的tag，则变成1（也是取反）。

4.Query（很简单，不说了……）

## 代码
丑陋的代码如下……

```cpp
#include<stdio.h>
#include<cstring>
#define lc rt<<1
#define rc rt<<1|1
//左右孩子 lchild rchild 
using namespace std;
const int Size=100003;
int n,m,p,q,dir;
struct node {
	int l,r;
	int v;			//区间内的值 
	int lazy;		//tag 
	inline int len() {	return r-l+1;	}	//区间长 
	inline int mid() {	return (l+r)>>1;}	//区间中值 
} tree[Size<<2];
inline void Pushup(int rt) {
	tree[rt].v=tree[lc].v+tree[rc].v;
}
void Pushdown(int rt) {
	if(tree[rt].lazy) {
		/*传下lazytag和值*/
		tree[lc].lazy^=1; 
		tree[rc].lazy^=1;
		tree[lc].v=tree[lc].len()-tree[lc].v;
		tree[rc].v=tree[rc].len()-tree[rc].v;
		tree[rt].lazy=0;
	}
}
void Build(int l,int r,int rt) {		//建树 
	tree[rt].l=l;
	tree[rt].r=r;
	tree[rt].v=0;
	if(l==r)	return;
	int mid=(l+r)>>1;
	Build(l,mid,lc);
	Build(mid+1,r,rc);
}
void Update(int l,int r,int rt) {		//更新[l,r]区间内的状态 
	if(l<=tree[rt].l && tree[rt].r<=r) {
		tree[rt].v=tree[rt].len()-tree[rt].v;
		tree[rt].lazy^=1;
		return;
	}
	Pushdown(rt);
	int mid=tree[rt].mid();
	if(l<=mid)	Update(l,r,lc);
	if(r>mid)	Update(l,r,rc);
	Pushup(rt);
}
int Query(int l,int r,int rt) {			//查询[l,r]之间的值 
	if(l<=tree[rt].l && tree[rt].r<=r) {
		return tree[rt].v;
	}
	Pushdown(rt);
	int mid=tree[rt].mid(),ans=0;
	if(l<=mid)	ans+=Query(l,r,lc);
	if(r>mid)	ans+=Query(l,r,rc);
	return ans;
}
int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9') {
		if(ch=='-')	f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9') {
		x=10*x+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int main() {
	n=read();
	m=read();
	Build(1,n,1);
	while(m--) {
		dir=read();
		p=read();
		q=read();
		if(!dir) {
			Update(p,q,1);
		} else {
			printf("%d\n",Query(p,q,1));
		}
	}
	return 0;
}
```

---

## 作者：万物一 (赞：5)

# 虽然可以写线段树，但是我偏要用珂朵莉树(骄傲)

我们来复习一下珂朵莉树的基础操作

我们知道珂朵莉树维护着拥有相同值的一整个区间
所以其节点是一个区间

节点定义
```cpp
struct Node {
    mutable int l, r;
    mutable bool v;
    inline auto operator<(const Node & o)  const -> bool {
        return l < o.l;
    }
};

//等同typedef
using Iter = set<Node>::iterator;

set<Node> odt;
```

基本操作：分割节点(分隔区间)
```cpp
auto split(int p) -> Iter {
    auto it = odt.lower_bound(Node {p, 0, false});
    if(it != odt.end() && it->l == p) {
        return it;
    }
    --it;
    auto x = *it;
    odt.erase(it);
    odt.insert(Node {x.l, p - 1, x.v});
    return odt.insert(Node {p, x.r, x.v}).first;
}
```
有了上边的操作我们就可以拿珂朵莉树~~水~~过这道题了

~~套模板就完了~~
翻转灯光
```cpp
auto flip(int l, int r) -> void {
    auto iterR = split(r + 1);//一定要先split r + 1
    auto iterL = split(l);
    //暴力遍历所有区间
    for (; iterL != iterR; ++iterL) {
        iterL->v = !iterL->v;
    }
}

```

统计亮着的灯
```cpp
auto countLight(int l, int r) -> int {
    int count = 0;
    auto iterR = split(r + 1);
    auto iterL = split(l);
    for (; iterL != iterR; ++iterL) {
        if(iterL->v) {
            count += iterL->r - iterL->l + 1;
        }
    }
    return count;
}
```

完整代码
```cpp
#include <iostream>
#include <set>

using namespace std;

struct Node {
    mutable int l, r;
    mutable bool v;
    inline auto operator<(const Node & o)  const -> bool {
        return l < o.l;
    }
};

using Iter = set<Node>::iterator;

set<Node> odt;

auto split(int p) -> Iter {
    auto it = odt.lower_bound(Node {p, 0, false});
    if(it != odt.end() && it->l == p) {
        return it;
    }
    --it;
    auto x = *it;
    odt.erase(it);
    odt.insert(Node {x.l, p - 1, x.v});
    return odt.insert(Node {p, x.r, x.v}).first;
}
auto flip(int l, int r) -> void {
    auto iterR = split(r + 1);
    auto iterL = split(l);
    for (; iterL != iterR; ++iterL) {
        iterL->v = !iterL->v;
    }
}

auto countLight(int l, int r) -> int {
    int count = 0;
    auto iterR = split(r + 1);
    auto iterL = split(l);
    for (; iterL != iterR; ++iterL) {
        if(iterL->v) {
            count += iterL->r - iterL->l + 1;
        }
    }
    return count;
}

int main() {
	//加速 cin cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    odt.insert(Node {1, n, false});//一开始所有灯都是熄灭的
    for (int i = 0; i < m; ++i) {
        int op, a, b;
        cin >> op >> a >> b;
        if(op == 0) {
            flip(a, b);
        } else {
            cout << countLight(a, b) << endl;
        }
    }
    return 0;
}


```
~~(友情提示 我是挂氧气过的)~~


---

## 作者：阿廖 (赞：4)

基础线段树。开两个变量，存当前线段上0和1的数量，每次动开关就是swap一下0和1的数量，统计时用累加。

#include<bits/stdc++.h>

using namespace std;

class bigpig

{
public:

```cpp
        void build(int l,int r,int k)
        {
            tree[k].left=l,tree[k].right=r;
            if(l==r)tree[k].data0=1,tree[k].flag=0,tree[k].kkk=1;
            else
            {
                int mid=(l+r)>>1;
                build(l,mid,k<<1),build(mid+1,r,(k<<1)+1);
                tree[k].data0=tree[k<<1].data0+tree[(k<<1)+1].data0,tree[k].kkk=1;
            }
            return;
        }
        int query(int l,int r,int k)
        {
            int mid=(tree[k].left+tree[k].right)>>1;
            if(tree[k].right<l || tree[k].left>r)return 0;
            if(tree[k].flag)pushdown(k);
            if(tree[k].left==l && tree[k].right==r)return tree[k].data1;
            if(r<=mid)return query(l,r,k<<1);
            if(l>mid)return query(l,r,(k<<1)+1);
            return query(l,mid,k<<1)+query(mid+1,r,(k<<1)+1);
        }
        void insert(int l,int r,int k)
        {
            int mid=(tree[k].left+tree[k].right)>>1;
            if(tree[k].right<l || tree[k].left>r)return;
            if(tree[k].flag)pushdown(k);
            if(tree[k].left==l && tree[k].right==r){swap(tree[k].data0,tree[k].data1),swap(tree[k].flag,tree[k].kkk);return;}
            if(r<=mid)insert(l,r,k<<1);
            else if(l>mid)insert(l,r,(k<<1)+1);
            else insert(l,mid,k<<1),insert(mid+1,r,(k<<1)+1);
            tree[k].data0=tree[k<<1].data0+tree[(k<<1)+1].data0;
            tree[k].data1=tree[k<<1].data1+tree[(k<<1)+1].data1;
            return;
        }
        void pushdown(int k)
        {
            swap(tree[k<<1].flag,tree[k<<1].kkk);
            swap(tree[(k<<1)+1].flag,tree[(k<<1)+1].kkk);
            swap(tree[k<<1].data0,tree[k<<1].data1);
            swap(tree[(k<<1)+1].data0,tree[(k<<1)+1].data1);
            swap(tree[k].flag,tree[k].kkk);
            return;
        }
        void print(int n)
        {
            int q=1,p[15]={0,1,3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383};
            for(int i=1;i<=2*n-1;i++)
            {
                cout<<" i:"<<i<<" l:"<<tree[i].left<<" r:"<<tree[i].right<<" d0:"<<tree[i].data0<<" d1:"<<tree[i].data1<<" f:"<<tree[i].flag<<endl;
                if(i==p[q])cout<<endl,q++; 
            }
            return;
        }
```
private:
```cpp
        struct smallpig
        {
            int left,right,data0,data1,flag,kkk;
        }tree[400005];
};
bigpig t;
int n,m;
int main()
{
    cin>>n>>m;
    t.build(1,n,1);
    for(int i=1,x,y,z;i<=m;i++)
    {
        cin>>x>>y>>z;
        if(x)cout<<t.query(y,z,1)<<endl;
        else t.insert(y,z,1);
    }
    return 0;
}
```

---

## 作者：Teddy_Di (赞：3)

这题貌似可以不用异或的2333

~~（其实是因为我根本不知道怎么用异或）~~

主要就是懒标记，如果这个区间被左击的次数是偶数次，那就是状态不变，如果是奇数次就反转，其他的和普通的线段树一样

具体看代码好了2333

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 2e5 + 5;
//线段树结点
struct Node {
	//cnt存[l,r]区间里亮灯个数，tag为懒标记
	int l, r, cnt;
	int tag;
	Node() {}
	Node(int l1, int r1, int cnt1, int tag1)
	{
		l = l1, r = r1, cnt = cnt1, tag = tag1;
	}
}tree[maxn << 2];
int ans, n, m;
//建立线段树，因为全暗所以cnt和tag都是0
void build(int o, int l, int r)
{
	tree[o] = Node(l, r, 0, 0);
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}
//普通的上浮
void pushup(int o)
{
	if (tree[o].l == tree[o].r)
		return;
	tree[o].cnt = tree[o << 1].cnt + tree[o << 1 | 1].cnt;
}
void pushdown(int o)
{
	//tag下移
	tree[o << 1].tag += tree[o].tag;
	//根据tag的值（即被左击的次数)判断是否反转
	//反转就是r-l+1-cnt
	for (int i = 1; i <= (tree[o].tag) % 2; i++)
		tree[o << 1].cnt = tree[o << 1].r - tree[o << 1].l + 1 - tree[o << 1].cnt;
	tree[o << 1 | 1].tag += tree[o].tag;
	for (int i = 1; i <= (tree[o].tag) % 2; i++)
		tree[o << 1 | 1].cnt = tree[o << 1 | 1].r - tree[o << 1 | 1].l + 1 - tree[o << 1 | 1].cnt;
	tree[o].tag = 0;
}
void update(int o, int l, int r)
{
	if (tree[o].l >= l && tree[o].r <= r)
	{
		//被左击，必定反转，反转次数+1
		tree[o].cnt = tree[o].r - tree[o].l + 1 - tree[o].cnt;
		tree[o].tag++;
		return;
	}
	//下面就是普通的线段树的递归升级操作
	pushdown(o);
	int mid = (tree[o].l + tree[o].r) >> 1;
	if (r <= mid)
		update(o << 1, l, r);
	else if (l > mid)
		update(o << 1 | 1, l, r);
	else
	{
		update(o << 1, l, mid);
		update(o << 1 | 1, mid + 1, r);
	}
	pushup(o);
}
//照搬模板的查询操作
int query(int o, int l, int r)
{
	if (tree[o].l >= l && tree[o].r <= r)
		return tree[o].cnt;
	pushdown(o);
	int mid = (tree[o].l + tree[o].r) >> 1;
	if (r <= mid)
		return query(o << 1, l, r);
	else if (l > mid)
		return query(o << 1 | 1, l, r);
	else
		return query(o << 1, l, mid) + query(o << 1 | 1, mid + 1, r);
}
int main()
{
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for (int i = 1; i <= m; i++)
	{
		int a, l1, r1;
		scanf("%d%d%d", &a, &l1, &r1);
		if (a == 0)
			update(1, l1, r1);
		if (a == 1)
		{
			ans = query(1, l1, r1);
			printf("%d\n", ans);
		}
	}
	return 0;
}
```

---

## 作者：Treaker (赞：3)

## 指针题解来一发！！！
这道题很简单，一眼切。

我们考虑区间异或以后，这个区间1的个数就变为了len - 原来的个数。

对于标记我们可以通过取异或来维护就行了
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N = 200020;
inline int read()
{
	int x = 0 , f = 1;	char ch = getchar();
	while(ch < '0' || ch > '9')	{if(ch == '-')	f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9') {x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar();}
	return x * f;
}
int n , m;
char s[N];
struct Segment_tree
{
	#define mid ((p -> l + p -> r) >> 1)
	struct node
	{
		node *ls , *rs;
		int l , r , sum , tag;
		node (int l = 0,int r = 0) : l(l) , r(r) {sum = tag = 0;}
		inline int len() {return r - l + 1;}
		inline void up() {sum = ls -> sum + rs -> sum;}
		inline void down() 
		{
			if(tag)
			{
				ls -> tag ^= 1;
				rs -> tag ^= 1;
				tag = 0;
				ls -> sum = ls -> len() - ls -> sum;
				rs -> sum = rs -> len() - rs -> sum;
			}
		}
	}*root , pool[N] , *tail;
	void build(node *&p,int l,int r)
	{
		p = new (tail ++)node(l,r);
		if(l == r)	return;
		build(p -> ls,l,mid);
		build(p -> rs,mid+1,r);
		p -> up();
	}
	void chenge(node *p,int x,int y)
	{
		if(x <= p -> l && p -> r <= y)	
		{
			p -> tag ^= 1;
			p -> sum = p -> len() - p -> sum;
			return;
		}
		if(p -> tag)	p -> down();
		if(x <= mid) chenge(p -> ls,x,y);
		if(y > mid)	chenge(p -> rs,x,y);
		p -> up();
	}
	int query(node *p,int x,int y)
	{
		if(x <= p -> l && p -> r <= y)	return p -> sum;
		if(p -> tag)	p -> down();
		int res = 0;
		if(x <= mid)	res += query(p -> ls,x,y);
		if(y > mid)		res += query(p -> rs,x,y);
		return res;
	}
	inline void LOL()
	{
		n = read(); m = read();
		build(root,1,n);
		for(int i = 1 , opt , l , r;i <= m;i ++)
		{
			opt = read(); l = read(); r = read();
			if(opt & 1)	printf("%d\n",query(root,l,r));
			else chenge(root,l,r);
		}
	}
	Segment_tree() {tail = pool;}
}CF;
int main()
{
	CF.LOL();
	return 0;
}

```


---

## 作者：Shallowy (赞：3)

## ~~大水题哟~~

很容易想到用0表示灯暗，1表示亮，那么由于**异或操作：相同为0，不同为1**，在取反时我们只要^1(异或1)就可以了。


其余操作就只是一般的线段树 区间修改和查询 吧...


还有，区间上的话千万别忘了标记。


大概是线段树中代码最短的一类题了...~~为压行而生~~


```cpp
#include <cstdio>
#include <iostream>
#include <cctype>
#include <cmath>
#define il inline
#define lu u<<1
#define ru u<<1^1
#define go return
using namespace std;
int rd(){int x=0; char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+c-48,c=getchar();
    return x;
}
il void rt(int x){x>=10?rt(x/10),putchar(x%10+48):putchar(x+48);}
struct tree{
    int l,r,v,f;
}a[400005]; //4倍空间别忘
int n=rd(),m=rd(),t,x,y,ans;
il void build(int u,int ul,int ur){
    a[u].l=ul,a[u].r=ur;
    if(ul==ur) go;
    int mid=ul+ur>>1;
    build(lu,ul,mid),build(ru,mid+1,ur);
}  //建树
il void down(int u){
    a[lu].f^=1,a[ru].f^=1,a[u].f=0,
    a[lu].v=a[lu].r-a[lu].l+1-a[lu].v,
    a[ru].v=a[ru].r-a[ru].l+1-a[ru].v;
}  //下传标记
il int update(int u){
    if(a[u].r<x||a[u].l>y) go 0;
    if(a[u].l>=x&&a[u].r<=y){
        a[u].f^=1,a[u].v=a[u].r-a[u].l+1-a[u].v; go 0; //标记也只要取反就行；修改等同于一段区间内0和1的个数互换，而0的个数是总个数减去1的个数~
    }
    if(a[u].f) down(u);
    update(lu),update(ru),a[u].v=a[lu].v+a[ru].v;
}    
il int query(int u){
    if(a[u].r<x||a[u].l>y) go 0;
    if(a[u].l>=x&&a[u].r<=y){ans+=a[u].v; go 0;}
    if(a[u].f) down(u);
    query(lu),query(ru);
}  //查询
int main(){
    build(1,1,n);
    while(m--) t=rd(),x=rd(),y=rd(),
        t?ans=0,query(1),rt(ans),putchar('\n'):update(1);
    go 0;
}
```

---

## 作者：Dawn_Sdy (赞：2)

前置芝士点：线段树 （不会的同学请做[线段树1](https://www.luogu.org/problem/P3372)）

首先观察此题特点，把题面抽象一下：

给你n个点，权值初始全为0，现在有两种操作：

1. 将 l ~ r的区间全部异或

2. 查询l ~ r的区间有多少为1

不难看出此题需要维护两个区间操作，很容易想到线段树。

线段树需要带4个变量：
```cpp
struct node{
	int l,r;//区间端点
	int sum;//区间中权值为1的个数
	int lz;//懒标记
}tree[400010];
```

由于是区间修改，所以我们要解决以下问题：

1. 如何维护sum（修改操作）

不难发现，如果我们将一个区间全部异或，那么此时权值为1点的其实就是以前权值为0的点；

考虑权值为0的点如何表示：所有点-权值一的点。

至于懒标记，我们只要将他与1异或就好

即
```cpp
tree[i].lz^=1;
tree[i].sum=tree[i].r-tree[i].l+1-tree[i].sum;
```

2. 如何维护懒标记（下传操作）

我们每次在修改，查询前都需要下传一次，把当前节点的懒标记分配给两个儿子，因为此区间的懒标记已经被修改过了，但他的儿子却并没有修改，所以需要下传，其实就是对左右儿子做出修改操作：

给出片段代码：
```cpp
inline void push_down(int i)
{
	if (tree[i].lz)
	   {
	   tree[i<<1].sum=(tree[i<<1].r-tree[i<<1].l+1)-tree[i<<1].sum;
	   tree[(i<<1)|1].sum=(tree[(i<<1)|1].r-tree[(i<<1)|1].l+1)-tree[(i<<1)|1].sum;
	   tree[i<<1].lz^=1;
	   tree[(i<<1)|1].lz^=1;
	   tree[i].lz=0;
	   }
}
```

其他的按常规线段树操作即可：

给出AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()//读入
{
	int x=0;
	char c=getchar();
	bool f=0;
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x;
}
int n,m;
struct node{
	int l,r;
	int sum;
	int lz;
}tree[400010];
inline void push_down(int i)//下传
{
	if (tree[i].lz)
	   {
	   tree[i<<1].sum=(tree[i<<1].r-tree[i<<1].l+1)-tree[i<<1].sum;
	   tree[(i<<1)|1].sum=(tree[(i<<1)|1].r-tree[(i<<1)|1].l+1)-tree[(i<<1)|1].sum;
	   tree[i<<1].lz^=1;
	   tree[(i<<1)|1].lz^=1;
	   tree[i].lz=0;
	   }
}
inline void build(int i,int l,int r)//建树
{
	tree[i].l=l,tree[i].r=r;
	if (l==r)//叶节点
	   {
	   tree[i].sum=0;
	   return ;
	   }
	int mid=(l+r)>>1;
	build(i<<1,l,mid);//对他的左右儿子建树
	build((i<<1)|1,mid+1,r);
}
inline void update(int i,int l,int r)//修改
{
	if (tree[i].l>=l&&tree[i].r<=r)//完全包含直接修改
	   {
	   tree[i].lz^=1;
	   tree[i].sum=tree[i].r-tree[i].l+1-tree[i].sum;
	   return ;
	   }
	push_down(i);
	if (l<=tree[i<<1].r)//如果左右儿子与区间有交集就去修改左右儿子
	   update(i<<1,l,r);
	if (r>=tree[(i<<1)|1].l)
	   update((i<<1)|1,l,r);
	tree[i].sum=tree[i<<1].sum+tree[(i<<1)|1].sum;
}
inline int query(int i,int l,int r)//查询
{
	if (tree[i].l>=l&&tree[i].r<=r)//完全包含直接返回
	   return tree[i].sum;
	push_down(i);
	int sum=0;
	if (l<=tree[i<<1].r)//如果左右儿子与区间有交集则查询左右儿子
	   sum+=query(i<<1,l,r);
	if (r>=tree[(i<<1)|1].l)
	   sum+=query((i<<1)|1,l,r);
	return sum;
}
int main(){
	n=read(),m=read();
	build(1,1,n);
	for (register int i=1;i<=m;++i)	
		{
		int c,a,b;
		c=read(),a=read(),b=read();
		if (!c)
		   update(1,a,b);
		else
		   printf("%d\n",query(1,a,b));
		}
	return 0;
}
//这样就可以AC了
```

---

## 作者：Ryang (赞：2)

看没有~~小学奥数的~~数组的解法我来发一个吧
```cpp
//这题用short的话会溢出!!!
#include<iostream> 
#include<cstdbool> 
using namespace std;
//0关  1开
int lis[100000];
int main(){
    int n;
    cin >> n;
    int caozuoshu;
    cin >> caozuoshu; 
    //操作只有0 1这里可以用bool值
    bool caozuo;
    int qujian1,qujian2;
    for (int i=0 ; i < caozuoshu ; i++){
    	//读入每次的数据
        cin >> caozuo >> qujian1 >> qujian2;
        //为 0 时的操作
        if(caozuo == 0){
        for (int j = qujian1 -1;j <= qujian2-1;j++){
                lis[j]=(!lis[j]);
            }
        }
        //为1时的操作
        else{
            int jishuqi=0;
            for (int j=qujian1-1;j<=qujian2-1;j++){
                if(lis[j]==1) jishuqi++; 
            }
            cout << jishuqi << endl ;
        }
    }
    return 0;
}
```

---

## 作者：Dreamunk (赞：2)

~~线段树这方面……线段树是不可能写的，这辈子不可能写线段树的。~~

题意就是让你处理一个01数组的 区间异或$1$ 和 区间求和。

显然本题可以分块。

不熟悉分块的同学可以去看[「分块」数列分块入门1 – 9 by hzwer](http://hzwer.com/8053.html)。

我们把$d$个元素分为一块，共有$n/d$块。对于每次操作，我们处理区间包含的每个整块和两个不完整的块。

在本题中，对于每个整块，我们记录整个块被异或的次数$(mod 2)$和块内的答案；对于每个元素，记录它被单个异或的次数$(mod 2)$。

实现时需要注意代码中一些$+1$，$-1$的玩意，并且分清楚块的下标和数组的下标。

显然，当$d=\sqrt n$时,时间复杂度最优秀。

时间复杂度$O(n\sqrt n)$。
```
//巨丑无比的代码
#include<cstdio>
#include<cmath>
inline int read(){
	int a=0;char c=getchar();
	for(;c<48||c>57;c=getchar());for(;c>47&&c<58;a=a*10+c-48,c=getchar());
	return a;
}
inline int min(int a,int b){return a<b?a:b;}
const int N=1e5+1,D=322;
int n,m,d,a[N],da[D],ds[D],p[N];
//n,m,块的大小，元素被单个异或的次数(mod 2)，整个块被异或的次数(mod 2)，块内的答案，元素所在块的编号
inline int Xor(int l,int r){
	for(int i=l;i<=min(p[l]*d,r);i++)ds[p[i]]+=a[i]^da[p[i]]?-1:1,a[i]^=1;
	if(p[l]!=p[r])for(int i=r;i>p[r]*d-d;i--)ds[p[i]]+=a[i]^da[p[i]]?-1:1,a[i]^=1;
	for(int j=p[l]+1;j<p[r];j++)da[j]^=1,ds[j]=d-ds[j];
}
inline int Sum(int l,int r){
	int s=0;
	for(int i=l;i<=min(p[l]*d,r);i++)s+=a[i]^da[p[i]];
	if(p[l]!=p[r])for(int i=r;i>p[r]*d-d;i--)s+=a[i]^da[p[i]];
	for(int j=p[l]+1;j<p[r];j++)s+=ds[j];
	return s;
}
int main(){
	d=sqrt(n=read());m=read();
	for(int i=1;i<=n;i++)p[i]=(i-1)/d+1;
	for(int o,l,r;m--;)
	  o=read(),l=read(),r=read(),
	  o?printf("%d\n",Sum(l,r)):Xor(l,r);
	return 0;
}
```

---

## 作者：7KByte (赞：1)

翻题的过程中无意看到了这道题，一看在能力范围之内就做了  
这题难度应该不大，但需要思考一下

------
## 步入正题
大致先看一遍题目：区间修改，区间查询，数据范围(n+m)log n可以过，无疑这题可以用线段树解决  
对于【模板】线段树1，我们只用进行一些小小的修改
 - 每个节点的data分别记录区间0和区间1的个数
 - 每个节点的lazytag记录这个区间是否需要修改
 - 修改的时候直接swap(data0,data1)即可
 - 这里的lazytag不进行累加，而是取反，以前是1现在则为0，以前是0现在则为1
 - 区间查询就与模板一样统计data1即可

---
### 放代码
```
#include<bits/stdc++.h>
#define N (100000+5)
using namespace std;
struct node{
	int l,r;
	int data0,data1;
	int tag;
}a[N*4];
void change(int p,int l,int r);
void down(int p){
	if(a[p].l==a[p].r)return;
	change(p*2,a[p*2].l,a[p*2].r);
	change(p*2+1,a[p*2+1].l,a[p*2+1].r);
	a[p].tag=0;
}
int ask(int p,int l,int r){
	if(a[p].l>=l&&a[p].r<=r)
	  return a[p].data1;
	if(a[p].tag)down(p);
	int mid=(a[p].l+a[p].r)>>1;
	int sum=0;
	if(mid>=l)sum+=ask(p*2,l,r);
	if(mid<r)sum+=ask(p*2+1,l,r);
	return sum;
}
void change(int p,int l,int r){
	if(a[p].l>=l&&a[p].r<=r){
		int t=a[p].data0;
		a[p].data0=a[p].data1;
		a[p].data1=t;
		a[p].tag=(a[p].tag==1?0:1);
		return;
	}
	if(a[p].tag)down(p);
	int mid=(a[p].l+a[p].r)>>1;
	if(mid>=l)change(p*2,l,r);
	if(mid<r)change(p*2+1,l,r);
	a[p].data0=a[p*2].data0+a[p*2+1].data0;
	a[p].data1=a[p*2].data1+a[p*2+1].data1;
}
void build(int p,int l,int r){
	a[p].l=l;a[p].r=r;a[p].tag=0;
	a[p].data0=r-l+1;a[p].data1=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
}
int main()
{
	//freopen("testdata(52).in","r",stdin);
	int n,m,x,y,z;
	scanf("%d%d",&n,&m);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		if(x)printf("%d\n",ask(1,y,z));
		else change(1,y,z);
		//printf("f: %d\n",ask(1,1,n));
	}
	return 0;
}
```
QwQ线段树最棒了

---

## 作者：风浔凌 (赞：1)

一道**线段树区间异或+区间求值**的题目

写这篇题解是为了自己能更好的掌握这个技巧+**更详细的注释解析。**

话不多说，上代码，注释在代码上——
```
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#define MAXN 200005
using namespace std;
int sum[MAXN<<2],lazy[MAXN<<2];
int n,m,a[MAXN<<2];
/*虽然说普通线段树开两倍空间貌似就够了，但是我也不知道究竟哪些特殊情况两倍不够，所以为了保险，数组日常开大一点
因为只是统计亮灯的个数，所以我们用0/1分别来分别表示灯的暗/亮，而因为灯一开始都是灭着的，所以初始数组为零。 */
inline int ls(int x)
{
    return x<<1;
}
inline int rs(int x)
{
    return x<<1|1;
}
inline void push_up(int root)
{
    sum[root]=sum[ls(root)]+sum[rs(root)];
}
//用子节点信息维护父节点
inline void build(int root,int l,int r)
{
    if(l==r)
    {
        //scanf("%1d",&sum[root]);
        sum[root]=a[l];
        return;
    }
    //如果相等，说明到达了叶子节点，我们为它赋值并返回
    int mid=(l+r)>>1;
    build(ls(root),l,mid);
    build(rs(root),mid+1,r);
    push_up(root);
}
//递归建树
inline void push_down(int root,int len)
{
    if(lazy[root])
    /*异或1就是取反，而因为取反两次还是自己，所以只有当lazy记录的1的时候需要取反操作*/
    {
        lazy[ls(root)]^=1;
        lazy[rs(root)]^=1;
        //懒标记取反
        sum[ls(root)]=(len-(len>>1))-sum[ls(root)];
        sum[rs(root)]=(len>>1)-sum[rs(root)];
        /*值取反：该节点子树结点个数（即区间总长度）减去它原先的值......如果有对len-(len>>1)不理解的可以手动画一棵简单的树看一看它记录的区间就明白了。
        注意位运算优先级比加减低！我开始就是因为这个错的！所以一定注意加括号......*/
        lazy[root]=0;
    }
}
//以上是将父节点的信息传递给子节点
inline void update(int root,int l,int r,int ll,int rr)
{
    if(ll<=l&&r<=rr)
    {
        lazy[root]^=1;
        sum[root]=r-l+1-sum[root];
        return;
    }
    int mid=(l+r)>>1;
    push_down(root,r-l+1);
    if(ll<=mid)  update(ls(root),l,mid,ll,rr);
    if(mid<rr)  update(rs(root),mid+1,r,ll,rr);
    push_up(root);
}
//更新
inline int query(int root,int l,int r,int ll,int rr)
{
    if(ll<=l&&r<=rr)   return sum[root];
    push_down(root,r-l+1);
    int mid=(l+r)>>1;
    int sum=0;
    if(ll<=mid)  sum+=query(ls(root),l,mid,ll,rr);
    if(mid<rr)    sum+=query(rs(root),mid+1,r,ll,rr);
    return sum;
}
//查询
int main(){
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        int p,l,r;
        scanf("%d%d%d",&p,&l,&r);
        if(p==0)
        {
            update(1,1,n,l,r);
        }
        else
        {
            printf("%d\n",query(1,1,n,l,r));
        }
    }
    return 0;
} 
```
以上。
### 双倍经验请看XOR的艺术

---

## 作者：muller (赞：1)

线段树裸题！直接记录l-r区间中灯turn on的个数！用左儿子，右儿子遍历！

记得要加lazy标记！TAG

TAG一定要下传，否则wa飞了！

我写的是比较简单的，希望大家向我学习！

```cpp
#include <bits/stdc++.h>
using namespace std;
#define            MAXN                100010
int Tag[MAXN << 5], Tr[MAXN << 5], n, m;
class Segment_Tree {
```
public:
```cpp
        void DownTag(int dep, int l, int r) {
            if(!Tag[dep])return;
            Tag[dep << 1] ^= 1;
            Tag[dep << 1 | 1] ^= 1;
            int mid = (l + r) >> 1;
            Tr[dep << 1] = (mid - l + 1) - Tr[dep << 1];
            Tr[dep << 1 | 1] = (r - mid) - Tr[dep << 1 | 1];
            Tag[dep] = 0; 
        } 
        void modify(int dep, int l, int r, int ql, int qr) {
            if(ql <= l && r <= qr) {
                Tag[dep] ^= 1;
                Tr[dep] = (r - l + 1) - Tr[dep];
                return;
            }
            DownTag(dep, l, r);
            int mid = (l + r) >> 1;
            if(ql <= mid)modify(dep << 1, l, mid, ql, qr);
            if(qr > mid)modify(dep << 1 | 1, mid + 1, r, ql, qr);
            Tr[dep] = Tr[dep << 1] + Tr[dep << 1 | 1];
        }
        int query(int dep, int l, int r, int ql, int qr) {
            if(ql > r || qr < l)return 0;
            if(ql <= l && r <= qr)return Tr[dep];
            DownTag(dep, l, r);
            int mid = (l + r) >> 1;
            return query(dep << 1, l, mid, ql, qr) + query(dep << 1 | 1, mid + 1, r, ql, qr); 
        }
}Tree;
int main() {
    scanf("%d %d", &n, &m);
    for(int i = 1;i <= m;i++) {
        int col, l, r;
        scanf("%d", &col);
        if(col == 0) {
            scanf("%d %d", &l, &r);
            Tree.modify(1, 1, n, l, r);
        }else {
            scanf("%d %d", &l, &r);
            printf("%d\n", Tree.query(1, 1, n, l, r));
        }
    } 
    return 0;
}

```

---

## 作者：x_faraway_x (赞：1)

一道比较容易的线段树题。

唯一可能和模板不太一样的可能是区间修改和标记修改这两个问题。

第一个问题还是很容易解决的。比如有一个区间一开始开的灯的数目是sum，总共的灯的数目是size，那么将这个区间取反后开的灯的数目就是size-sum。

第二个标记问题，显然标记只有0和1这两个状态，那么区间修改后直接给标记取反就可以啦，标记下传应该也没什么难的，稍微改一改就可以了。

具体可以看一看代码，如果会写线段树模板并且大概理解了上面的思路下面代码应该还是容易看懂的……

当然线段树模板就不解释啦，布吉岛线段树怎么写的可以移步3372

```cpp
#include<cstdio>

const int N=100005;
int st[N*3],add[N*3]; //add即标记，抄模板懒得改数组名了QwQ

void tagdown(int v, int l, int r) //下传标记
{
    if(!add[v]) return;
    add[v<<1]^=1; //左右孩子标记下传
    add[v<<1|1]^=1;
    int mid=(l+r)>>1;
    st[v<<1]=(mid-l+1)-st[v<<1]; //更新左右孩子值
    st[v<<1|1]=(r-mid)-st[v<<1|1];
    add[v]=0;
}

int query(int v, int l, int r, int sl, int sr) //区间查询，和模板一样
{
    if(sl>r||sr<l) return 0;
    if(sl<=l&&r<=sr) return st[v];
    tagdown(v,l,r);
    int mid=(l+r)>>1;
    return query(v<<1,l,mid,sl,sr)+query(v<<1|1,mid+1,r,sl,sr);
}

void update(int v, int l, int r, int sl, int sr) //区间修改
{
    if(sl>r||sr<l) return;
    if(sl<=l&&r<=sr)
    {
        add[v]^=1; //标记取反
        st[v]=(r-l+1)-st[v]; //更新当前值
        return;
    }
    tagdown(v,l,r);
    int mid=(l+r)>>1;
    update(v<<1,l,mid,sl,sr);
    update(v<<1|1,mid+1,r,sl,sr);
    st[v]=st[v<<1]+st[v<<1|1];
}

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
        //PS：这题由于灯全部为灭，所以按照这样的写法不用建树……
    while(m--)
    {
        int f,x,y;
        scanf("%d%d%d",&f,&x,&y);
        if(f) printf("%d\n",query(1,1,n,x,y));
        else update(1,1,n,x,y);
    }
}
```

---

## 作者：jins3599 (赞：0)

线段树区间和模板。

考虑维护一个线段树包含：区间有几个一，区间长度

于是我们每次修改的时候区间有几个一就可以就改成：区间长度-区间有几个一

然后我们发现我们需要维护一个$tag$，观察一下性质就能得出，我们每次把$tag$异或1即可，下放标记的时候判断$tag$等于1的时候再下放。

然后答案就是区间和的模板了。

$Code:$
```cpp
#include <bits/stdc++.h>
#define ls(x) x << 1
#define rs(x) x << 1 | 1

using namespace std;

const int N = 100000 + 5;

int n , m;

struct Seg {
	int l , r , dis , add , len;
	Seg() {add = 0;}
}t[N << 2];

void pushup(int x) {
	t[x].dis = t[ls(x)].dis + t[rs(x)].dis;
}

void built(int x , int l , int r) {
	t[x].l = l , t[x].r = r;
	t[x].len = r - l + 1;
	if(l == r) {
		t[x].dis = 0; return;
	}
	int mid = l + r >> 1;
	built(ls(x) , l , mid);
	built(rs(x) , mid + 1 , r);
	pushup(x);
}

void pushdown(int x) {
	if(t[x].add) {
		int tag = t[x].add;
		t[ls(x)].add ^= tag;
		t[ls(x)].dis = t[ls(x)].len - t[ls(x)].dis;
		t[rs(x)].add ^= tag;
		t[rs(x)].dis = t[rs(x)].len - t[rs(x)].dis;
		t[x].add = 0;
	}
}

void updata(int x , int l , int r) {
	if(t[x].l >= l && t[x].r <= r) {
		t[x].add ^= 1; t[x].dis = t[x].len - t[x].dis; return;
	}
	int mid = t[x].l + t[x].r >> 1;
	pushdown(x);
	if(l <= mid) updata(ls(x) , l , r);
	if(r > mid ) updata(rs(x) , l , r);
	pushup(x);
}

int query(int x , int l , int r) {
	if(t[x].l >= l && t[x].r <= r) return t[x].dis;
	pushdown(x);
	int mid  = t[x].l + t[x].r >> 1;
	int ans = 0;
	if(l <= mid) ans += query(ls(x) , l , r);
	if(r > mid ) ans += query(rs(x) , l , r);
	pushup(x);
	return ans; 
}

int main () {
	scanf("%d %d" , &n , &m);
	built(1 ,1 , n);
	while(m -- ) {
		int opt , l , r;
		scanf("%d %d %d" ,&opt, &l , &r);
		if(opt == 0) {
			updata(1 , l , r);
		} else printf("%d\n" , query(1 , l , r));
	}	
	return 0;
}
```

---

## 作者：x_liuier (赞：0)

~~线段树水题当然要用分块来做了~~

这题和[[TJOI2009]开关](https://www.luogu.org/problem/P3870)几乎没什么区别(水双倍经验),直接复制不作修改一遍AC...

所以,没什么好说的,分块不懂的话[戳这里](http://hzwer.com/8053.html),直接放code:

```cpp
#include <iostream>
#include<cmath>
using namespace std;
typedef unsigned int uint;
const uint MAX_N = 1e5;
const uint MAX_S = 1e3;

uint n, m;
int sum[MAX_S];
uint rang[MAX_N], BASE;
bool flag[MAX_S], data[MAX_N], cut[MAX_N];
// rang[i] = 第i个数所处块的下标
// data[i] = 输入数据
// cut[i] = 若i为当前块的开头则为真
// flag[rang[i]] = 当前块是否翻转
// sum[rang[i]] = 第i个数所处块开着的灯数

inline void init() {
	BASE = sqrt(n); // 每个块的大小
	for (uint i=0; i<n; i+=BASE) cut[i] = true;
	for (uint i=0, k=0; i<n; ++i) {
		if (i&&cut[i]) ++k;
		rang[i] = k;
	}
}

// 单点修改
inline void upPoint(uint in) {
	uint k = rang[in];
	sum[k] -= flag[k]^data[in];
	data[in] ^= true;
	sum[k] += flag[k]^data[in];
}

// 区间修改
inline void upRange(uint k) {
	sum[k] = BASE - sum[k];
	flag[k] ^= true;
}

// 单点查询
inline uint quPoint(uint in) { return flag[rang[in]]^data[in]; }

// 区间查询
inline uint quRange(uint k) { return sum[k]; }

// 处理区间[l, r)
inline void flip(uint l, uint r) {
	// 处理边缘部分
	while (l<r && !cut[l]) upPoint(l++);
	while (l<r && !cut[r]) upPoint(--r);
    // 整块处理
	while (l<r) upRange(rang[r-=BASE]);
}

// 查询区间[l, r)
inline uint query(uint l, uint r) {
	uint res = 0;
    // 查询边缘部分
	while (l<r && !cut[l]) res += quPoint(l++);
	while (l<r && !cut[r]) res += quPoint(--r);
    // 整块查询
	while (l<r) res += quRange(rang[r-=BASE]);
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin>>n>>m; init();
	uint type, l, r; ++m;
	while (--m) {
		cin>>type>>l>>r;
		if (type == 0) flip(--l, r);
		else cout<<query(--l, r)<<endl;
	}
	return 0;
}
```



> ~~USACO水题名不虚传~~

---

## 作者：Provicy (赞：0)

一道线段树偏板子的题

思考区间修改的懒标记怎么打，显然，对于序列中每一个数，只有$0$或$1$的赋值情况，那么我们可以用$flag[x]=flag$ $xor$ $1$来打标记。

如何在$Pushdown$的时候修改区间中开着的灯的数量呢？

我们考虑到对于一个区间中每盏灯的情况，只有开着或者关着，即$1$或$0$。显然，修改之后区间亮着的灯的数量$=$区间灯总数$-$修改前区间亮着的灯的数量，即$light[x]=(r-l+1)-light[x]$

了解了对于这道题线段树的$lazytag$的$Pushdown$做法后，这题就迎刃而解了

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=410000;
int n,m;
inline int read()
{
	int s=0,w=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar(); return s*w;
}
inline int LeftChild(int x) {return x<<1; }
inline int RightChild(int x) {return x<<1|1; }
struct Node//放在结构体里，方便调试查看
{
	int leaf[N],flag[N];
	inline void Push_Up(int x) {leaf[x]=leaf[LeftChild(x)]+leaf[RightChild(x)]; }
	inline void Change(int x,int l,int r) {leaf[x]=r-l+1-leaf[x]; flag[x]^=1; }
	inline void Push_Down(int x,int l,int r)
	{
		Change(LeftChild(x),l,(l+r)>>1);
		Change(RightChild(x),((l+r)>>1)+1,r); flag[x]=0;
	}
	void UpDate(int u,int v,int l,int r,int x)
	{
		if(l>=u&&r<=v) {Change(x,l,r); return; }
		if(flag[x]) Push_Down(x,l,r);
		if(u<=(l+r)>>1) UpDate(u,v,l,(l+r)>>1,LeftChild(x));
		if(v>(l+r)>>1) UpDate(u,v,((l+r)>>1)+1,r,RightChild(x));
		Push_Up(x);	
	}
	int Ask(int u,int v,int l,int r,int x)
	{
		if(l>=u&&r<=v) return leaf[x];
		if(flag[x]) Push_Down(x,l,r); int ans=0;
		if(u<=(l+r)>>1) ans+=Ask(u,v,l,(l+r)>>1,LeftChild(x));
		if(v>(l+r)>>1) ans+=Ask(u,v,((l+r)>>1)+1,r,RightChild(x));
		return ans;
	}
}D;
int main()
{
	n=read(); m=read();
	for(int i=1,opt,u,v;i<=m;i++)
	{
		opt=read(); u=read(); v=read();
		if(!opt) D.UpDate(u,v,1,n,1);
		else printf("%d\n",D.Ask(u,v,1,n,1));
	}
	return 0;
}
```


---

## 作者：Erusel (赞：0)

~~据说这题好像有六倍经验~~

我们简单分析一下

我们令灯关着的时候是0，开着的时候是1

初始所有数都是0

题目要求支持两种操作，一种是区间异或1，还有一种是区间查询1的个数

考虑到所有数中只有0和1

所以查询可以改为查询区间和

区间异或1也可以从区间和的角度取考虑问题

---

假设我们原来有$k$个1，区间长度为$l$

现在就有$l-k$个1

所以$sum_{now}=l-sum_{pre}$

标记下传也可以维护了

时间复杂度就是维护一颗线段树的时间$O(nlogn)$

code:

```
#include<bits/stdc++.h>

#define rd(x) x=read()
#define N 200005 
 
using namespace std;

int n,m;
struct T{
	int l,r,mid,v,tag;
}t[N<<2];

inline int read()
{
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}

void pushdown(int rt,int len)
{
	if(t[rt].tag)
    {
        t[rt<<1].tag^=1; 
        t[rt<<1|1].tag^=1;
        t[rt<<1].v=(len-(len>>1))-t[rt<<1].v;
        t[rt<<1|1].v=(len>>1)-t[rt<<1|1].v;
        t[rt].tag=0;
    }
}

void build(int rt,int l,int r)
{
	int mid=(l+r)>>1;
	t[rt].l=l,t[rt].r=r,t[rt].mid=mid,t[rt].tag=0;
	if(l==r)
	{
		t[rt].v=0;
		return;
	}
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
	t[rt].v=t[rt<<1].v+t[rt<<1|1].v;
}

void update(int rt,int l,int r)
{
    if(l<=t[rt].l&&t[rt].r<=r)
    {
        t[rt].tag^=1;     
        t[rt].v=t[rt].r-t[rt].l+1-t[rt].v;    
        return;
    }
    pushdown(rt,t[rt].r-t[rt].l+1);
    if(l<=t[rt].mid)update(rt<<1,l,r);    
    if(t[rt].mid<r)update(rt<<1|1,l,r);        
    t[rt].v=t[rt<<1].v+t[rt<<1|1].v; 
}
int query(int rt,int l,int r)
{
    if(l<=t[rt].l&&t[rt].r<=r)return t[rt].v;
    pushdown(rt,t[rt].r-t[rt].l+1);
    int sum=0;
    if(l<=t[rt].mid)sum+=query(rt<<1,l,r); 
    if(t[rt].mid<r)sum+=query(rt<<1|1,l,r);        
    return sum;
}

int main()
{
	rd(n),rd(m);
	build(1,1,n);
	while(m--)
	{
		int opt,l,r;
		rd(opt),rd(l),rd(r);
		if(opt)printf("%d\n",query(1,l,r));
		else update(1,l,r);	
	}
	
	return 0;
}

```

---

## 作者：mxr已死 (赞：0)

  快要noip了，该写些题解攒攒rp了（~~逃~~）

看到题解里那么多线段树啊，树状数组啊，本蒟蒻表示：这都是什么鬼东西？

  在所有高级数据结构中，树状数组是码量最小的，跑的也基本是最快的，但理解很难，并且支持的操作很少；线段树的码量，相信写过线段树题的童鞋都亲身体验过这种恐怖（~~那些3min写完splay的巨佬不要d我~~），理解虽然简单，但一题调一辈子啊！

所以说到这里，本蒟蒻想表达什么呢？

   # **分块大法吼啊！** 
有人会说：分块不是n√n的复杂度吗？怎么能跟nlogn的数据结构相提并论呢？或者说，分块在联赛中，有什么优势呢？

首先，虽然他复杂度高，但他能维护的东西多呀！（你看看n²的暴力什么不能维护）

而且，因为有时线段树有巨大的常数，反而比分块跑的慢！（比如洛谷P2801）

再者说，如果联赛一道题，好多方法都能做，你是用调一辈子的线段树呢，还是十分暴力好写的分块呢？

废话了这么多，也是想让大家知道，分块也是一种很好的算法。

那分块是怎么实现的呢？顾名思义，分块就是把一个区间分成好几个小区间，至于是几个呢，因题而异，但大部分题的复杂度都是n√n，所以默认是把区间分成√n块。如果某题用分块复杂度带log，就让块分的更多一些，大概是乘个log（我也不知道为什么）。

哪怎么维护呢？当询问某段区间时，把区间覆盖的整块打上一个tag标记，两边离散的块呢，就暴力就好了。有人会说，这么简单？当然。（不简单本蒟蒻怎么可能会写）

还有要注意的是询问区间如果在一个块里要特判，所以要多大几个if。（虽然有些麻烦，但都是板儿啊）

分块大体差不多说完了，但这个算法十分灵活，准确的说，分块这种思想十分可贵，能用到很多其他题上。

最后，本题其实不难，把分块板子粘过来，把加改成xor就行了。如果想看分块的板子，[hzwer大佬博客](http://hzwer.com/8053.html)里有，可以去看一看（巨佬的码风是真好看啊）

下贴代码：
```c
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<queue>
#define rint register int
#define maxn 200010
using namespace std;
inline int read()
{
    int s=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();if(ch=='-')f=-1;}
    while(ch>='0'&&ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return s*f;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
    return ;
}
int n,m,blo,o;
int bl[maxn],v[maxn],t[maxn],atag[maxn],sum[maxn],L[maxn],R[maxn];
inline void change(int l,int r)
{
    if(bl[l]==bl[r])
    {
        for(rint i=l;i<=r;++i)
        {
            if(v[i]) v[i]=0,--sum[bl[l]];
            else v[i]=1,++sum[bl[l]];
        } 
        return ;
    }
    for(rint i=l;i<=R[bl[l]];++i) 
    {
        if(v[i]) v[i]=0,--sum[bl[l]]; 
        else v[i]=1,++sum[bl[l]];
    }
    for(rint i=L[bl[r]];i<=r;++i) 
    {
        if(v[i]) v[i]=0,--sum[bl[r]];
        else v[i]=1,++sum[bl[r]];
    }
    for(rint i=bl[l]+1;i<=bl[r]-1;++i) atag[i]=1-atag[i];
}
inline int query(int l,int r)
{
    int ans=0;
    if(bl[l]==bl[r])
    {
        for(rint i=l;i<=r;++i) 
            if(v[i]^atag[bl[l]]) ++ans;
        return ans;
    }
    for(int i=l;i<=R[bl[l]];++i) 
        if(v[i]^atag[bl[l]]) ++ans;
    for(int i=L[bl[r]];i<=r;++i) 
        if(v[i]^atag[bl[r]]) ++ans;
    for(int i=bl[l]+1;i<=bl[r]-1;++i)
    {
        if(atag[i]) ans+=(R[i]-L[i]+1)-sum[i];
        else ans+=sum[i];
    }        
    return ans;
}
int main()
{
    n=read(),m=read();blo=sqrt(n);
    n%blo ? (o=n/blo+1) : (o=n/blo);
    for(rint i=1;i<=n;++i)
    {
    	v[i]=0;
    	bl[i]=(i-1)/blo+1;
    	if(v[i]) ++sum[bl[i]];
    }
    for(rint i=1;i<=o;++i)
    {
        L[i]=(i-1)*blo+1;
        R[i]=i*blo;
    }
    while(m--)
    {
        int p=read(),l=read(),r=read();
        if(p==0) change(l,r);
        if(p==1) write(query(l,r)),puts(" ");
    }
    return 0;
} 
```
谢谢大家

---

## 作者：dongjiajiedc (赞：0)

大蒟蒻表示并不会亦或，所以用0,1，2来表示灯的状态

```
#include <iostream>
using namespace std;
#define MAXN 100000
//  0 关灯 1开灯  2不会在根中出现，2表示它两个子叶不一样； 
struct tree{
	int val;
	int add;
}a[MAXN*5];
//全是关灯 全是0 所以不用build
void pushup(int i,int l,int r){
	if(a[i<<1].val!=a[(i<<1)+1].val){
		a[i].val=2;
	}else{
		a[i].val=a[(i<<1)+1].val;
	}
}
void f(int i,int l,int r,int k){
	a[i].add+=k;
	if(k==0)return ;
	if(k%2==1&&a[i].val!=2)                //修改偶数次等于没改 
	a[i].val=!a[i].val;
}
void putdown(int i,int l,int r,int k){
	int mid=(l+r)/2;
	f(i<<1,l,mid,k);
	f((i<<1)+1,mid+1,r,k);
	a[i].add=0;
	return ;
}
void update(int i,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		if(a[i].val!=2)
		a[i].val=!a[i].val;	
		a[i].add++;
		return;
	}
	putdown(i,l,r,a[i].add);
	long mid=(l+r)/2;
	if(mid>=x)update(i<<1,l,mid,x,y);
	if(mid+1<=y)update((i<<1)+1,mid+1,r,x,y);
		pushup(i,l,r);

}
int query(int i,int l,int r,int x,int y){
	long ans=0;
	if(x<=l&&y>=r&&a[i].val==1){
		return r-l+1;
	}
	if(l==r||a[i].val==0)
	return 0;
	int mid=(l+r)/2;
	putdown(i,l,r,a[i].add);
	 if(mid>=x)ans+=query(i<<1,l,mid,x,y);
	if(mid+1<=y)ans+=query((i<<1)+1,mid+1,r,x,y);
	return ans;
}
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int d,x,y;
	cin>>d>>x>>y;
	if(d==1){
		cout<<query(1,1,n,x,y)<<endl;
		}else{
		update(1,1,n,x,y);
		}
	}
}
```

---

## 作者：Sor4 (赞：0)

每次操作相当于把区间内的每个数取反，1变0，0变1。

可以去参考xor的艺术这一题。






    
    
    
    


```cpp
#include <cstdio>
#include <algorithm>
#define Rep( i , _begin , _end ) for(int i=(_begin),i##_END=(_end);i<=(i##_END);i++)
#define For( i , _begin , _end ) for(int i=(_begin),i##_END=(_end);i!=(i##_END);i++)
#define Lop( i , _begin , _end ) for(int i=(_begin),i##_END=(_end);i>=(i##_END);i--)
#define Dnt( i , _begin , _end ) for(int i=(_begin),i##_END=(_end);i!=(i##_END);i--)
using std :: min;
using std :: max;
const int maxx = 100000 + 25;
int n,m,x,y,z,f;
int T[maxx<<2],Add[maxx<<2];
namespace Segment_Tree{
    void pushdown(int i,int l,int r){
        int mid = (l+r) >> 1;
        T[i<<1] = (mid-l+1) - T[i<<1];T[i<<1|1] = (r-mid) - T[i<<1|1];
        Add[i<<1] ^= Add[i];Add[i<<1|1] ^= Add[i];Add[i] = 0;
    }
    void modify(int i,int x,int y,int l,int r){
        if(x <= l && r <= y) {T[i] = (r-l+1) - T[i];Add[i] ^= 1;return;}
        int mid = (l+r) >> 1;if(Add[i]) pushdown(i,l,r);
        if(x <= mid) modify(i<<1,x,y,l,mid);
        if(y >  mid) modify(i<<1|1,x,y,mid+1,r);
        T[i] = T[i<<1] + T[i<<1|1];
    }
    int Query(int i,int x,int y,int l,int r){
        if(x <= l && r <= y) return T[i];int ans = 0;
        int mid = (l+r) >> 1;if(Add[i]) pushdown(i,l,r);
        if(x <= mid) ans += Query(i<<1,x,y,l,mid);
        if(y >  mid) ans += Query(i<<1|1,x,y,mid+1,r);
        return ans;
    }
}
using namespace Segment_Tree;
int main(){
    scanf("%d%d",&n,&m);
    Rep( i , 1 , m ){
        scanf("%d%d%d",&f,&x,&y);
        if(f == 0) modify(1,x,y,1,n);
        if(f == 1) printf("%d\n",Query(1,x,y,1,n));
    }
    return 0;
}
```

---

## 作者：斯德哥尔摩 (赞：0)

看到题目就应该想到了 线段树 了吧。。。（虽说标签中也有。。。）

线段树 应该都会。。。

每个节点存 某一范围内所有1的个数 。

具体看注释吧。。。

附代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#define LSON rt<<1//左孩子
#define RSON rt<<1|1//右孩子
#define DATA(x) a[x].data//节点值
#define SIGN(x) a[x].c//懒惰标记
#define LSIDE(x) a[x].l
#define RSIDE(x) a[x].r//左右区间
#define WIDTH(x) (RSIDE(x)-LSIDE(x)+1)//区间范围
#define MAXN 100010
using namespace std;
int n,m;
struct node{
    int data,c;
    int l,r;
}a[MAXN<<2];//线段树 数组，切记，一定要开 4 倍空间，不然会炸。。。
inline int read(){//弱弱的读入优化。。。
    int date=0,w=1;char c=0;
    while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
    while(c>='0'&&c<='9'){date=date*10+c-'0';c=getchar();}
    return date*w;
}
void pushup(int rt){//数值上传
    DATA(rt)=DATA(LSON)+DATA(RSON);//每个节点（叶节点除外）的值 = 左孩子的值 + 右孩子旳值
}
void pushdown(int rt){//标记下传
    if(!SIGN(rt)||LSIDE(rt)==RSIDE(rt))
    return;
    SIGN(LSON)^=SIGN(rt);////处理左孩子。取反，从1变为0 或 从0变为1
    DATA(LSON)=WIDTH(LSON)-DATA(LSON);//区间范围 = 区间内0的个数 + 区间内1的个数，移项即可。。。
    SIGN(RSON)^=SIGN(rt);//处理右孩子
    DATA(RSON)=WIDTH(RSON)-DATA(RSON);
    SIGN(rt)=0;//标记清空
}
void buildtree(int l,int r,int rt){//建树
    int mid;
    LSIDE(rt)=l;
    RSIDE(rt)=r;//这两句是建树的核心之一
    if(l==r){
        DATA(rt)=0;
        return;
    }
    mid=l+r>>1;
    buildtree(l,mid,LSON);
    buildtree(mid+1,r,RSON);//这是核心之二
    pushup(rt);
}
void update(int l,int r,int rt){//修改
    int mid;
    if(l<=LSIDE(rt)&&RSIDE(rt)<=r){//如果该节点在范围内，则 处理 并 返回 
        SIGN(rt)^=1;
        DATA(rt)=WIDTH(rt)-DATA(rt);//已解释过。。。见 标记下传
        return;
    }
    pushdown(rt);//一定要先下传，再递归
    mid=LSIDE(rt)+RSIDE(rt)>>1;//分为 左孩子 与 右孩子，分别处理
    if(l<=mid)update(l,r,LSON);
    if(mid<r)update(l,r,RSON);
    pushup(rt);//一定要上传
}
long long query(int l,int r,int rt){
    int mid;
    long long ans=0;
    if(l<=LSIDE(rt)&&RSIDE(rt)<=r)//如果该节点在范围内
    return DATA(rt);//返回节点值
    pushdown(rt);//下传标记
    mid=LSIDE(rt)+RSIDE(rt)>>1;//分为 左孩子 与 右孩子，分别求和
    if(l<=mid)ans+=query(l,r,LSON);
    if(mid<r)ans+=query(l,r,RSON);
    return ans;//不要忘记返回值。。。
}
int main(){
    int f,x,y;
    n=read();m=read();
    buildtree(1,n,1);
    while(m--){
        f=read();x=read();y=read();
        if(f==0)update(x,y,1);//分类
        if(f==1)printf("%lld\n",query(x,y,1));
    }
    return 0;//终于结束。。。
}

```

---

