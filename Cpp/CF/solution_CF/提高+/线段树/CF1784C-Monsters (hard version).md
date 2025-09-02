# Monsters (hard version)

## 题目描述

在一款电脑游戏中，你正在与 $n$ 个怪物作战。怪物 $i$ 的生命值为 $a_i$，所有的 $a_i$ 都是整数。只要怪物的生命值至少为 $1$，它就活着。

你可以施放两种类型的法术：

1. 对任意一个存活的怪物造成 $1$ 点伤害。
2. 对所有存活的怪物造成 $1$ 点伤害。如果至少有一个怪物死亡（其生命值降到 $0$），则该法术会继续重复施放，直到没有怪物死亡为止。

对怪物造成 $1$ 点伤害会减少其生命值 $1$ 点。

类型 $1$ 的法术可以施放任意次数，而类型 $2$ 的法术只能施放一次。

对于每个 $k = 1, 2, \dots, n$，请回答以下问题：假设游戏中只有前 $k$ 个怪物（编号为 $1, 2, \dots, k$）存在，那么最少需要施放多少次类型 $1$ 的法术才能击杀所有这 $k$ 个怪物？

## 说明/提示

#### 示例 1

在第一个测试用例中，当 $k = n$ 时，怪物的初始生命值为 $[3, 1, 2]$。此时只需要施放一次类型 $2$ 的法术：

- 使用类型 $2$ 法术，对所有怪物造成 $1$ 点伤害，怪物的生命值变为 $[2, 0, 1]$。由于怪物 $2$ 死亡，法术会继续施放。
- 使用类型 $2$ 法术，怪物的生命值变为 $[1, 0, 0]$，此时怪物 $3$ 死亡，法术继续施放。
- 使用类型 $2$ 法术，怪物的生命值变为 $[0, 0, 0]$，此时怪物 $1$ 死亡，法术继续施放。
- 使用类型 $2$ 法术，所有怪物的生命值都降为 $0$，结束。

因此，最后无需再使用类型 $1$ 法术，答案是 $0$ 次。

#### 示例 2

在第二个测试用例中，怪物的初始生命值为 $[4, 1, 5, 4, 1, 1]$。一种最优的行动顺序如下：

- 先使用类型 $1$ 法术，给怪物 $1$ 造成 $1$ 点伤害，生命值变为 $[3, 1, 5, 4, 1, 1]$。
- 再使用类型 $1$ 法术，给怪物 $4$ 造成 $1$ 点伤害，生命值变为 $[3, 1, 5, 3, 1, 1]$。
- 再使用类型 $1$ 法术，给怪物 $4$ 造成 $1$ 点伤害，生命值变为 $[3, 1, 5, 2, 1, 1]$。
- 然后使用类型 $2$ 法术：
  - 所有怪物的生命值减去 $1$，变为 $[2, 0, 4, 1, 0, 0]$，怪物 $2$、$5$ 和 $6$ 死亡，法术继续施放。
  - 再次使用类型 $2$ 法术，怪物的生命值变为 $[1, 0, 3, 0, 0, 0]$，怪物 $4$ 死亡，法术继续施放。
  - 再次使用类型 $2$ 法术，怪物的生命值变为 $[0, 0, 2, 0, 0, 0]$，怪物 $1$ 死亡，法术继续施放。
  - 使用类型 $2$ 法术，怪物的生命值变为 $[0, 0, 1, 0, 0, 0]$。
- 然后使用类型 $1$ 法术，给怪物 $3$ 造成 $1$ 点伤害，生命值变为 $[0, 0, 0, 0, 0, 0]$，结束。

因此，总共需要施放 $4$ 次类型 $1$ 法术。

## 样例 #1

### 输入

```
2
3
3 1 2
6
4 1 5 4 1 1```

### 输出

```
2 1 0
3 2 4 4 4 4```

# 题解

## 作者：xcyle (赞：24)

提供一种码量较小的做法。

容易发现，对于单个问题，我们可以这样求解：

维护变量 $lev$，初始为 $1$。每次找到剩下的数中，不小于 $lev$ 的数中最小的一个，记为 $x$。将答案加上 $x-lev$，并把 $x$ 删掉。直到不存在不小于 $lev$ 的数停止。

我们把上述过程中所有找到的 $x$ 放进一个可重集 $s$ 中，其它数放进另一个可重集 $t$ 中。

考虑倒序，将加数变为删数。假设删除的数是 $a$。只有 $a\in S$ 时，答案才有可能改变。接下来我们考虑对上述过程的修正。

若 $t$ 中存在不小于 $a$ 的数，记其中最小的一个是 $y$。我们需要将 $y$ 从 $t$ 中删除，加入 $s$ 。这是因为，假设 $s$  中不小于 $y$ 的最大数为 $z$。那么删除 $z$ 的操作进行的时候，原本的 $lev$ 满足 $lev\le z$，而将 $a$ 删掉后，这个时刻的 $lev$ 会 $-1$，因此在删除 $z$ 的下一轮，我们寻找不小于 $lev$ 的最小数时，就会找到 $y$。而 $y$ 又是第一个没被删除的，因此结论得证。

若 $t$ 中不存在不小于 $a$ 的数，那么修正就是将过程的最后一轮删掉。

两种情况对答案的影响都能简单计算，复杂度 $O(n\log n)$，代码比较好写。

```c
#include <bits/stdc++.h>
#define N 200005
using namespace std;
int T, n, a[N], lev; long long res[N], ans;
multiset<int> t;
void solve() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], t.insert(a[i]);
	for (auto it = t.begin(); it != t.end(); it = t.upper_bound(lev)) {
		ans += (*it) - ++lev;
		t.erase(it);
	}
	for (int i = n; i >= 1; i--) {
		res[i] = ans, ans -= a[i];
		auto it = t.lower_bound(a[i]);
		if(it == t.end()) ans += lev--;
		else ans += (*it), t.erase(it);
	}
	for (int i = 1; i <= n; i++) printf("%lld ", res[i]); printf("\n");
}
int main() {cin >> T; while(T--) solve();}

```


---

## 作者：Flanksy (赞：6)

### 贪心

尝试一种很新的解释方法，不喜勿喷。

~~其实就是笔者做题的思路。~~

------------

#### 思路

把所有元素从小到大排序之后可以用下图表示。

每个竖条对应一个元素，其高度对应元素的值。

![](https://cdn.luogu.com.cn/upload/image_hosting/oucgje8n.png)

执行操作一即消除一个竖条顶部的方块，执行操作二即消除图案最下面的一层。

很显然应当使操作二消除的方块尽可能多，因为剩下的方块只能由操作一消除。

在提前使用操作一使得操作二连续进行的情况下，操作二最多能消除的方块（红色）如下图。

**由于只有两种操作能消除方块，最大化操作二消除的方块数量就可以让操作一消除的方块数量最小。**

![](https://cdn.luogu.com.cn/upload/image_hosting/0ibco52w.png)

称红色图形为**阶形**，称元素对应竖条中红色方块的数量为该元素的**有效值**。

发现阶形中的元素的有效值要么比上一个元素的有效值大一，要么与上一个元素的有效值相等，存在相等有效值的情况如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/rl0x29ey.png)

**观察上方两张图片也可以发现黑色方块数量即答案。**

维护图形面积与阶形面积即可求解，由于有效值相等的元素不好维护，将加入后会导致元素有效值相等的元素存放至另一个集合，使得阶形中所有元素的有效值不同。

**接下来的讨论中阶形不包含相等元素。**

易得阶形面积为 $\sum\limits_{i=1}^{len} i$，其中 $len$ 为阶形横向长度；图形总面积可以轻易维护从而计算答案。

------------

#### 做法

容易发现能够作为阶形第 $i$ 个元素的元素 $x$ 满足 $x \geq i$。

笔者想了很长时间如何在添加元素时维护答案，最终仅得到一个不可实现的做法。

考虑转换思路，反转时间轴，变添加为删除。

维护两个集合，一个集合维护阶形，另一个集合维护加入后会导致元素有效值相等的元素。容易发现**第二个集合中的元素不影响答案**（在消除阶形中有效值与它们实际值相等的元素时被消除，简单来说就是不包含黑色方块所以不影响），如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ytgpih8k.png)

初始化时从小到大枚举序列元素，如果当前元素的值大于阶形长度就将其加入阶形并更新答案；否则将元素加入第二个集合中。

删除元素时，如果第二个集合中存在目标元素，就在第二个集合中删除它。

如果没有目标元素，先在阶形中删除该元素，更新答案。

然后考虑使用第二个集合中的元素补上这个元素在阶形中的位置，**一旦能够填补则必须填补，阶形面积最大时答案才是正确的**。

贪心填补，可能有多个值相同但有效值不同的目标元素，删除有效值最小的那个显然不劣（考虑填补一个缺失的位置，这个位置的有效值越小可供填补的数就越多，用来填补的数越小以后留有的余地就越多，**图形总面积的增加量就越小**），更新答案。

**使用树状数组能够确定目标元素的最小有效值。**

如果能够补上这个位置，在集合二中选择最小的数填补并更新答案；否则阶形长度减一并更新答案。

将答案倒序输出即可，总体时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],c[200005];
void add(int x,int y){while(x<=n) c[x]+=y,x+=x&-x;}
int sum(int x){int ret=0;while(x) ret+=c[x],x-=x&-x;return ret;}
void solution(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    multiset<int> e,s,u(a+1,a+n+1);//e:维护空闲元素 s:维护阶形
    vector<long long> v;
    long long ans=0ll;
    int cnt=0;
    fill(c+1,c+n+1,0);
    for(int i:u) if(i<=cnt) e.emplace(i);
        else ans+=i-(++cnt),add(i,1),s.emplace(i);
    reverse(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        v.push_back(ans);
        if(e.find(a[i])!=e.end()){//空闲元素挡刀
            e.erase(e.find(a[i]));
            continue;
        }
        ans-=a[i],add(a[i],-1);//注意更新树状数组
        s.erase(s.find(a[i]));
        auto it=e.upper_bound(sum(a[i]-1));
        if(it==e.end()) ans+=cnt,--cnt;
        else{
            ans+=*it,add(*it,1);
            s.emplace(*it),e.erase(it);
        }
    }
    reverse(v.begin(),v.end());
    for(long long i:v) printf("%lld ",i);
    putchar('\n');
}
int T;
int main(){
    scanf("%d",&T);
    while(T--) solution();
    return 0;
}
```

---

## 作者：Daidly (赞：4)

发现对于一个数列的答案求法类似于从小到大考虑赋值给递增的 $a_i$。

比如 $4\ 1\ 5\ 4\ 1\ 1$ 即 $\ 2\ 1\ 4\ 3\ 1\ 1$。

发现特殊的是每一个值可能对应一个值域上的不交区间，记 $x$ 对应的区间为 $[l_x,r_x]$，上面例子中 $l_4=2,r_4=3$。

考虑每次插入一个数 $a_i$ 对答案的影响。

- 若 $r_{a_i}<a_i$ 则 $a_i$ 可以起到更新答案的作用。令 $r_{a_i}\gets r_{a_i}+1$，从小到大更新 $x$ 满足 $x>a_i$。
  - 若 $r_x<x$，则 $l_x\gets l_x+1,r_x\gets r_x+1$。
  - 否则停止更新。
- 否则由于 $a_i$ 只能通过操作减小，所以对答案无影响。

停止更新即 $r_x=x$，我们可以使用线段树维护值对应区间以及最小的 $x-r_x$ 还有答案等。可以通过线段树二分找到 $r_x=x$，然后若满足 $r_{a_i}<a_i$ 就在区间 $[a_x+1,x-1]$ 上更新 $l,r$ 即可。时间复杂度 $O(n\log n)$。



---

## 作者：xuanxuan001 (赞：4)

虽然 tourist 还没出题解，但看了一下别人的代码并和同学讨论了一下，发现我的做法有些神奇，所以就发篇题解吧。

下面有一些赛时心路历程。

这题显然是要通过 1 操作来让这些值分布在一个前缀，所以给这些值开一个桶。那么考虑将这个过程分成两步：

首先，尽量不要有相同的值，所以如果有一个位置有多于一个怪，那么就让其中一个怪向下走（即进行 1 操作）到第一个没有怪的值上去，如果没有就不需要操作，这里的代价就是每个怪的移动距离和。

经过上面的操作，可以发现如果一个值的前面存在一个位置没有怪，那么这个位置上肯定只有一个怪。于是我们就直接移动即可，这里的代价就是对于每个空的值，它后面的有怪的位置的数量的和。当然从有怪的位置入手考虑也是可以的。

于是考虑依次插入这些怪，那么也是考虑维护上面的东西。设插入的位置是 $a$，那么：

首先，找到最大的 $p$ 满足 $p \le a$ 且 $p$ 位置为空。如果不存在则跳过本步，然后将答案加上 $a-p$，即为第一步的代价。

然后，维护第二步，首先将答案减去 $p$ 后面的有怪的值的个数，然后再加上 $p$ 前面的没有怪的值的个数。

那么可以同时用 set 和树状数组维护当前有怪的位置。set 处理第一步，树状数组处理第二步。

好，看起来没问题，交！WA #2！

哦，好像写挂了，再改！再交！再 WA #2！

不对啊，没写挂啊，思路也没问题啊，为啥不对啊。

于是就把 A 的代码拿过来开始人工造数据，懒得更没心情写拍，结果直接试出来了一个 hack：

```
1
10
7 8 9 7 8 9 1 2 5 6
```

这时我会在最后一个输出 11，但其实是 8。

手模一下，会发现前 9 个已经把 1 到 9 的值占满了，这时插进来一个 6，那么按我的思路它是不会有贡献的，但其实它让答案减少了 3。

为什么呢？是因为有一个在 9 的怪被操作到了 6 的前面，那么这时可以用 6 代替它，以此减少 9-6 的代价。

那么第一步修正就是在 $p$ 不存在时不应该不操作，而是找到一个最大的 $q$ 满足 $a \le q$ 且存在一个在 $q$ 上的怪走到了 $a$ 之前（包括 $a$ 本身），如果存在 $q$，那么将答案减去 $q - a$。

那么这个可以记录每个值上的怪是从哪里来的，然后就可以用一个线段树维护出前缀最大位置。

好，看起来没问题，交！WA #2！

哦，好像写挂了，再改！再交！再 WA #2！

为啥又不对呢？别的地方应该没啥问题，应该还是修正的地方有问题。

在有多个最大位置时是不是应该取最大的啊？然后又无脑来了两发 WA #2。

那么我们考虑下面这个图景（用线段表示怪的移动，只画出了一部分，剩下的就认为是已经有了）：

```
    O---O
O---------O
      X
  X
```

O 是已经插入的怪，按行依次插入两个 X。

那么第一个 X 就会替代第二行的那个怪，然后第二个 X 又会把第一个 X 替代掉，那么最终就变成了这样：

```
    O---O
O-X       O
      X
```

但其实可以变成这样：

```
    O-X O
O-X       O
```

所以怎么修呢？就是再改一下第一步：

在将答案加上 $q-a$ 后，再将 $a \leftarrow q$，并重新执行本操作，直到不存在 $q$ 为止。

那么这样不断循环的复杂度为什么是对的呢？我也不知道，但反正它过了，也没 FST。

代码（罚时吃满了，C 拿 677 分的全场估计也没谁了）：

```
#include<cstdio>
#include<algorithm>
#include<set>
#define TY ll
#define MAXN 200002
#define debug if(1==1)
#define FOR(i,a,b) for(TY i=(a);i<=(b);i=-~i)
#define fOR(i,a,b) for(TY i=(a);i<(b);i=-~i)
#define ROF(i,a,b) for(TY i=(a);i>=(b);i=~-i)
#define rOF(i,a,b) for(TY i=(a);i>(b);i=~-i)
using namespace std;
typedef double db;
typedef long long ll;
const TY M=998244353;
typedef unsigned long long ull;
TY _abs(TY a){return a<0?-a:a;}
TY maxn(TY a,TY b){return a>b?a:b;}
TY minn(TY a,TY b){return a<b?a:b;}
inline void updmx(TY &x,TY y){if(x<y)x=y;}
inline void updmn(TY &x,TY y){if(x>y)x=y;}
TY gcd(TY a,TY b){return b?gcd(b,a%b):a;}
TY qp(TY a,TY b){TY ans=1;do{if(b&1)ans=ans*a%M;a=a*a%M;}while(b>>=1);return ans;}
char getc(){char ch=getchar();while(ch==' '||ch=='\n'||ch=='\r')ch=getchar();return ch;}
TY qr(){
	char ch=getchar();TY s=0,x=1;
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')x=-1;
	for(;ch>='0'&&ch<='9';ch=getchar())s=s*10+ch-'0';return x*s;
}void qw(TY a,char ch){
	if(a<0){a=-a;putchar('-');}
	if(a>9)qw(a/10,0);putchar(a%10+'0');
	if(ch)putchar(ch);
}TY T=qr(),n,k,a,tmp,ps,bit[MAXN],ar[MAXN],tre[MAXN<<2],ans;
set<TY>st;set<TY>::iterator it;
void add(TY x){for(;x<=n;x+=x&-x)++bit[x];}
TY ask(TY x){TY s=0;for(;x;x^=x&-x)s+=bit[x];return s;}
void build(TY i,TY j,TY id){
	tre[id]=i;if(i==j)return;TY mid=i+j>>1;
	build(i,mid,id<<1);build(mid+1,j,id<<1|1);
}void chg(TY i,TY j,TY id){
	if(i==j)return;TY mid=i+j>>1;
	if(ps<=mid)chg(i,mid,id<<1);
	else chg(mid+1,j,id<<1|1);
	if(ar[tre[id<<1]]>ar[tre[id<<1|1]])tre[id]=tre[id<<1];
	else tre[id]=tre[id<<1|1];
}void ask(TY i,TY j,TY id){
	if(j<=a){
		if(ar[ps]<ar[tre[id]])ps=tre[id];return;
	}TY mid=i+j>>1;ask(i,mid,id<<1);
	if(a>mid)ask(mid+1,j,id<<1|1);
}int main(){
	while(T--){
		n=qr();ans=0;st.clear();
		FOR(i,1,n)st.insert(i);
		FOR(i,1,n)bit[i]=ar[i]=0;build(1,n,1);
		//st 是维护值的 set，bit 是树状数组，ar 记录每个值上是哪个位置来的怪
		FOR(i,1,n){
			it=st.upper_bound(a=qr());
			if(it!=st.begin()){//p 存在
				--it;add(*it);ans-=(ask(n)-ask(*it));//第一步的代价是 a-*it，剩下的都是第二步的
				ar[ps=*it]=a;chg(1,n,1);ans+=a-*it;st.erase(it);ans+=a-ask(a);
			}else{//p 不存在
				while(1){
					ps=0;ask(1,n,1);if(ar[ps]<=a)break;//重复寻找 q（即为代码中的 ps）
					ans-=(ar[ps]-a);tmp=ar[ps];ar[ps]=a;chg(1,n,1);a=tmp;
				}
			}qw(ans,' ');
		}putchar('\n');
	}
	return 0;
}
```

---

## 作者：Leasier (赞：2)

在 Easy Version 的贪心结束、此后可以直接调用操作二恰好一次时，$a$ 此时一定是一个不降序列，且相邻项之差 $\leq 1$。设 $a$ 的值域为 $[1, m]$。

设 $cnt_i$ 表示 $\leq i$ 的数中被操作过的数的数量。

考虑加入一个 $a_i$。我们先强制操作 $a_i$，再求出最小的 $j$ 使得 $cnt_j > j$，若 $j$ 不存在则当前值域不够用了，需要将 $m$ 加 $1$，且答案加上 $a_i - m$；否则将 $j$ 改回不可操作，且答案加上 $a_i - j$。

线段树维护 $cnt_j - j$，每次在线段树上二分即可。时间复杂度为 $O(\sum n \log n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

typedef struct {
	int l;
	int r;
	int add;
	int max;
} Node;

int a[200007];
Node tree[800007];

inline int max(int a, int b){
	return a > b ? a : b;
}

inline void update(int x){
	tree[x].max = max(tree[x * 2].max, tree[x * 2 + 1].max);
}

void build(int x, int l, int r){
	tree[x].l = l;
	tree[x].r = r;
	tree[x].add = 0;
	if (l == r){
		tree[x].max = -l;
		return;
	}
	int mid = (l + r) >> 1;
	build(x * 2, l, mid);
	build(x * 2 + 1, mid + 1, r);
	update(x);
}

inline void pushdown(int x){
	if (tree[x].add != 0){
		int ls = x * 2, rs = x * 2 + 1;
		tree[ls].add += tree[x].add;
		tree[rs].add += tree[x].add;
		tree[ls].max += tree[x].add;
		tree[rs].max += tree[x].add;
		tree[x].add = 0;
	}
}

void add(int x, int l, int r, int k){
	if (l <= tree[x].l && tree[x].r <= r){
		tree[x].add += k;
		tree[x].max += k;
		return;
	}
	int mid = (tree[x].l + tree[x].r) >> 1;
	pushdown(x);
	if (l <= mid) add(x * 2, l, r, k);
	if (r > mid) add(x * 2 + 1, l, r, k);
	update(x);
}

int get_first(int x){
	if (tree[x].max <= 0) return -1;
	if (tree[x].l == tree[x].r) return tree[x].l;
	int ls = x * 2;
	pushdown(x);
	if (tree[ls].max > 0) return get_first(ls);
	return get_first(x * 2 + 1);
}

inline ll sum1(int n){
	return (ll)n * (n + 1) / 2;
}

int main(){
	int t;
	scanf("%d", &t);
	for (register int i = 1; i <= t; i++){
		int n, cnt = 0;
		ll sum = 0;
		scanf("%d", &n);
		build(1, 1, n);
		for (register int j = 1; j <= n; j++){
			scanf("%d", &a[j]);
		}
		for (register int j = 1; j <= n; j++){
			int pos;
			add(1, a[j], n, 1);
			pos = get_first(1);
			sum += a[j];
			if (pos == -1){
				cnt++;
			} else {
				sum -= pos;
				add(1, pos, n, -1);
			}
			printf("%lld ", sum - sum1(cnt));
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Fanch100 (赞：1)

### 分析

沿用和 easy version 一样的思路，即操作 1 会将原序列减小至连续递增状态再进行操作 2。

以下的操作均指操作 1。

从小到大考虑序列中的元素，可以发现对于前 $i$ 个数，只会对 $\min(i,a_i)$ 个数进行操作，并对答案产生贡献，对其他数字的操作是冗余的，据此可以写出 easy version 的代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 200010;
int n;
int a[N];
void solve(){
    cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i];
    sort(a+1,a+1+n);
    ll ans=0,len=0;
    for (int i=1;i<=n;++i){
        len++;
        if (a[i]>=len) ans+=a[i]-len;
        else len--;
    }
    cout<<ans<<endl;
}
int main(){
    int t;cin>>t;
    while(t--) solve();
    return 0;
}

```
回到 hard version，我们记录当前真正被进行操作的数字个数 $len$，并维护一个数组 $d_i$ 表示小于等于 $i$ 的数中，还可以被操作的数字个数，初始时 $d_i=i$。

新加入一个数 $x$ 时，我们假设强制选择 $x$ 进行操作，那么 $x$ 会让 $i \in [x,n]$ 这一段区间的 $d_i$ 减 $1$。

若此时 $\forall i \in [1,n] ,d_i \geqslant 0$，说明序列仍合法，那么将序列长度 $len$ 加 $1$ 后，对答案有 $x-len$ 的贡献。

否则，找到最小的使得 $d_{pos}<0$ 的 $pos$，一定有 $x\leqslant pos$。那么在不改变序列长度的情况下，留下 $x$ 一定比留下 $pos$ 优秀。因此我们把 $i \in [pos,n]$ 这一段区间的 $d_i$ 加 $1$，表示撤销 $pos$ 原本对 $d_i$ 的贡献，这样操作对答案的贡献是 $x-pos$。

可以发现 $pos$ 上一定有之前被操作的数，否则设 $y$ 为满足 $y < pos$ 的第一个被操作的数，由于 $y$ 的限制比 $pos$ 更紧而选择的数字个数不变， 一定也满足 $d_y < 0$，那么 $pos$ 就不是最小的数了。

上述过程涉及区间加和查询最小值，可以维护一颗线段树，查询 $pos$ 时在线段树上二分。

每次加入一个数后修改答案即可。

时间复杂度 $O(n \log n)$。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 200010;
int n;
int a[N];
struct node{
    int mn,tag;
    #define ls p<<1
    #define rs p<<1|1
    #define mn(p) t[p].mn
    #define tag(p) t[p].tag
}t[N<<2];
void pushdown(int p){
    if (tag(p)!=0){
        mn(ls)+=tag(p); mn(rs)+=tag(p);
        tag(ls)+=tag(p); tag(rs)+=tag(p);
        tag(p)=0;
    }
}
void pushup(int p){
    mn(p)=min(mn(ls),mn(rs));
}
void build(int p,int l,int r){
    tag(p)=0;
    if (l==r) {
        mn(p)=l;
        return;
    }
    int mid=(l+r)>>1;
    build(ls,l,mid); build(rs,mid+1,r);
    pushup(p);
}
void update(int p,int l,int r,int pl,int pr,int d){
    if (l<=pl && pr<=r){
        mn(p)+=d; tag(p)+=d;
        return;
    }
    pushdown(p);
    int mid=(pl+pr)>>1;
    if (mid>=l) update(ls,l,r,pl,mid,d);
    if (mid+1<=r) update(rs,l,r,mid+1,pr,d);
    pushup(p);
}
int find(int p,int l,int r){
    if (mn(p)>=0) return 0;
    if (l==r) return l;
    pushdown(p);
    int mid=(l+r)>>1;
    if (mn(ls)<0) return find(ls,l,mid);
    else return find(rs,mid+1,r);
}
void solve(){
    cin>>n;
    for (int i=1;i<=n;++i) cin>>a[i];
    ll ans=0,len=0;
    build(1,1,n);
    for (int i=1;i<=n;++i){
        update(1,a[i],n,1,n,-1);
        int pos=find(1,1,n);
        if (pos){//ai对之后的答案有更新
            ans+=a[i]-pos;
            update(1,pos,n,1,n,1);
        }
        else {
            len++;
            ans+=a[i]-len;
        }
        printf("%lld ",ans);
    }
    puts("");
}
int main(){
    int T;cin>>T;
    while(T--) solve();
    return 0;
}

```




---

## 作者：GreatJMore (赞：1)

~~亵渎题。重点考察术学。~~

不需要线段树二分。

亵渎，重点是排列出 $1,2,3,\dots$ 等的序列。那么如果有这样的 $a=\{1,2,5,4,7\}$，就考虑先打 $4$ 下 $7$，把 $7$ 变成 $3$，就可以放亵渎了。

可以发现一个性质：

事实上，把 $7$ 直接变成 $3$，与把 $5$ 变成 $3$，把 $7$ 变成 $5$ 所需的代价相同。也就是说，不需要随便变动我们之前所考虑的变法，只需要微调补缺就可以了。

考虑构造一颗线段树维护最大值，把对应位置的值定为谁来当这个数值的怪（如： $5$ 来当 $3$），初始值设置为 $+\infty$，代表缺失这个怪，然后尽量往高了凑就行了。

加入一个数 $a$ 的时候，$[1,a]$ 为这个怪所能当的怪，那么在 $[1,a]$ 的区间内寻找最左边的最大值，若为 $+\infty$，直接填补，否则填补后将其拿出，因为一个大的怪能当的怪总是比小怪要多些的。（同时，因为小的空不填满大的怪也没用，所以只动这一个是正确的。）

拿出来后，重复插入的操作，直到被插入的值和自己相等或是插入到 $+\infty$ 为止即可。

每一个空平均至多能插入 $\log(n)$ 次，所以时间复杂度为 $O(n\log^2(n))$。但事实上非常快且难以构造来卡，所以比线段树二分要快很多。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int T,n,a[200005];//,tow[200005];
bool checked[200005];
 
struct Object
{
	int id,fill;
	Object(){}
	Object(int id,int fill):id(id),fill(fill){}	
};
 
Object max(Object a,Object b)
{
	if(a.fill==b.fill)
		return (a.id<b.id?a:b);
	return (a.fill>b.fill?a:b);
} 
 
struct Node
{
	Object mx;
	int l,r;
}s[200005<<2];
 
#define L(A) ((A)<<1)
#define R(A) (((A)<<1)|1)
 
void build(int nw,int l,int r)
{
	s[nw].l = l;
	s[nw].r = r;
	if(l==r)
	{
		s[nw].mx = Object(l,2147483647);	
		return;
	}	
	int mid = (l+r)/2;
	build(L(nw),l,mid);
	build(R(nw),mid+1,r);
	s[nw].mx = max(s[L(nw)].mx,s[R(nw)].mx);
}
 
Object query(int nw,int l,int r)
{
	if(s[nw].l==l && s[nw].r==r)
		return s[nw].mx;
	if(s[L(nw)].r>=r)
		return query(L(nw),l,r);
	if(s[R(nw)].l<=l)
		return query(R(nw),l,r);
	Object res1 = query(L(nw),l,s[L(nw)].r),
		   res2 = query(R(nw),s[R(nw)].l,r);
	return max(res1,res2);
}
 
void change(int nw,int x,Object obj)
{
	if(s[nw].l==s[nw].r)
	{
		s[nw].mx = obj;
		return;
	}
	if(s[L(nw)].r>=x)
		change(L(nw),x,obj);
	else
		change(R(nw),x,obj);
	s[nw].mx = max(s[L(nw)].mx,s[R(nw)].mx);
}
 
int main()
{
	scanf("%d",&T);
	
	while(T--)
	{
		scanf("%d",&n);
		
		long long int c = 0;
		
		for(int i=1;i<=n;i++)
			checked[i] = 0;
		
		build(1,1,n);
		
		for(int i=0;i<n;i++)
		{
			scanf("%d",a+i);	
			
			Object res = query(1,1,a[i]);
			while(res.fill>a[i])
			{
				change(1,res.id,Object(res.id,a[i]));
				if(res.fill==2147483647)
				{
					c += a[i]-res.id;
					break;
				}
				else 
				{
					c -= res.fill-res.id;
					c += a[i]-res.id;
					a[i] = res.fill;
					res = query(1,1,a[i]);
				}
			}
			
			printf("%lld ",c);
		}
		
		putchar('\n');
 
	}
	
	return 0;
}
```


---

## 作者：_ZSR_ (赞：0)

### [ CF1784C Monsters (hard version)](https://www.luogu.com.cn/problem/CF1784C)

根据贪心容易想到，一只怪兽在进行操作，二之前需要受到的操作一的伤害为它的健康值减去它的健康值的排名，那么考虑怎么在每次新加入一个值后维护排名。

由于健康值的范围不大，于是我们可以开一棵权值线段树，维护对于每个值来说，当前加入的数中有多少个数小于等于它。如果当前加入的数中小于等于 $x$ 的个数大于 $x$，我们把当前这个 $x$ 删掉是没有影响的，因为根据之前的的贪心策略，$x$ 减去 $x$ 的排名一定小于等于 $0$。

为了方便，线段树可以维护 $cnt_x-x$，这样的话只要跟 $0$ 比就可以了。

code 
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=200010;
int n,T;
int h[N];
struct Node{
    int l,r;
    int maxn,tag;
}tr[N<<2];
inline void pushup(int p)
{
    tr[p].maxn=max(tr[p<<1].maxn,tr[p<<1|1].maxn);
}
void build(int p,int inl,int inr)
{
    tr[p]={inl,inr};
    tr[p].tag=0;
    if (inl==inr)
    {
        tr[p].maxn=-inl;
        return;
    }
    int mid=inl+inr>>1;
    build(p<<1,inl,mid);
    build(p<<1|1,mid+1,inr);
    pushup(p);
}
inline void addit(int p,int k)
{
    tr[p].maxn+=k;
    tr[p].tag+=k;
}
inline void pushdown(int p)
{
    if (tr[p].tag)
    {
        addit(p<<1,tr[p].tag);
        addit(p<<1|1,tr[p].tag);
        tr[p].tag=0;
    }
}
void add_sum(int p,int x,int y,int k)
{
    if (x<=tr[p].l&&tr[p].r<=y)
    {
        addit(p,k);
        return;
    }
    pushdown(p);
    int mid=tr[p].l+tr[p].r>>1;
    if (x<=mid) add_sum(p<<1,x,y,k);
    if (y>mid) add_sum(p<<1|1,x,y,k);
    pushup(p);
}
int query(int p)
{
    if (tr[p].maxn<=0) return -1;
    if (tr[p].l==tr[p].r) return tr[p].l;
    pushdown(p);
    if (tr[p<<1].maxn>0) return query(p<<1);
    else return query(p<<1|1);
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("zsr.in","r",stdin);
    freopen("zsr.out","w",stdout);
#endif
    scanf("%lld",&T);
    while (T--)
    {
        int ans=0,cnt=0;
        scanf("%lld",&n);
        build(1,1,n);
        for (int i=1;i<=n;++i) scanf("%lld",&h[i]);
        for (int i=1;i<=n;++i)
        {
            ans+=h[i];
            add_sum(1,h[i],n,1);
            int pos=query(1);
            if (pos==-1) cnt++;
            else
            {
                ans-=pos;
                add_sum(1,pos,n,-1);
            }
            printf("%lld ",ans-cnt*(cnt+1)/2);
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1784C)

[CF](https://codeforces.com/contest/1786/problem/E)

### 分析

比较有特色的 Div.2 第五题。

分析 [easy version](https://www.luogu.com.cn/problem/CF1784A) 中的贪心策略，我们需要构造出一组  $1,2,3,\dots,len$ 的排列，一次全部消掉。

记 $sum_i$ 为数字 $i$ 出现的次数，可以发现当 $\sum_{j=1}^{i}{sum_j} > i$ 时，可重集中的一些数字是没有贡献的，如可重集 $\{1,1\}$ 中的其中一个 $1$ 是没有贡献的，直接删除即可。

所以，我们只需要维护一个线段树，记录 $\sum_{j=1}^{i}{sum_i} - i$ 的最小值。注意，当左右的最小值同时小于 $0$ 时，应当处理左边的。

答案就是当时的数列的 $\sum num - \frac{len \times (len+1)}{2}$。

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
		if(c == '-') p = -p;
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
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 200010
int t,n,a[N],len;
ll sum;
struct Segment
{
	#define mid (l+r)/2
	#define ls u<<1
	#define rs u<<1|1
	ll mn[N<<2],lazy[N<<2];
	inline void pushup(int u) {mn[u] = min(mn[ls],mn[rs]);}
	inline void tag(int u,int k)
	{
		mn[u] += k;
		lazy[u] += k;
	} 
	inline void pushdown(int u)
	{
		tag(ls,lazy[u]);
		tag(rs,lazy[u]);
		lazy[u] = 0;
	}
	void rebuild(int u,int l,int r)
	{
		lazy[u] = 0;
		if(l == r)
		{
			mn[u] = l;
			return;
		}
		rebuild(ls,l,mid);
		rebuild(rs,mid+1,r);
		pushup(u);
	}
	void update(int u,int l,int r,int x,int y,int k)
	{
		if(x <= l&&r <= y)
		{
			tag(u,k);
			return;
		}
		pushdown(u);
		if(x <= mid) update(ls,l,mid,x,y,k);
		if(y > mid) update(rs,mid+1,r,x,y,k);
		pushup(u);
	}
	int query(int u,int l,int r)
	{
		if(l == r) return l;
		pushdown(u);
		if(mn[ls] <= mn[rs]) return query(ls,l,mid);
		return query(rs,mid+1,r);
	}
}tree;
int main()
{
	read(t);
	while(t--)
	{
		read(n);
		tree.rebuild(1,1,n);
		F(i,1,n) read(a[i]);
		len = sum = 0;
		F(i,1,n)
		{
			++len,sum += a[i];
			tree.update(1,1,n,a[i],n,-1);
			if(tree.mn[1] < 0) 
			{
				int x = tree.query(1,1,n);
				tree.update(1,1,n,x,n,1);
				--len,sum -= x;
			}
			write(sum-1ll*len*(len+1)/2);
			putchar(' ');
		}
		putchar('\n');
	}
	return 0; 
}

```


---

