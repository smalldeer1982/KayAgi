# Knights of a Polygonal Table

## 题目描述

有  $n$  个骑士想决战。每个骑士都有能力值，且身上带有一些金币。如果骑士  $A$  的能力值大于骑士  $B$ ，那么骑士  $A$  就可以杀死骑士  $B$ ，并获得骑士  $B$  身上的所有金币。但就算是骑士也不会残忍过度，他们最多只会杀死  $k$  个骑士。对于每一位骑士，请你求出在决战后他身上金币的最大值。

## 说明/提示

- 第  $1$  组样例的解释：

第  $1$  个骑士是最蒻的，因此他谁也不能杀，只能保留自己原有的金币。

第  $2$  个骑士只能杀死第  $1$  个骑士，因此他最多拥有  $2 + 1 = 3$  个金币。

第  $3$  个骑士是最蔃的，但他只能选择杀  $k = 2$  个骑士。显然他会杀死第  $2$  个骑士和
第  $4$  个骑士，因为他们身上的金币更多。因此他最多拥有  $11 + 2 + 33 = 46$  个金币。

第  $4$  个骑士应该杀死第  $1$  个和第  $2$  个骑士，因此他最多拥有  $33 + 1 + 2 = 36$  个金币。 

- 第  $2$  组样例的解释：

除了最蒻的第  $1$  个骑士谁也不能杀，其他骑士都能杀死前一个骑士并获得他的金币。

- 第  $3$  组样例的解释：

由于只有一个骑士在决战中，他无法杀死任何人。

感谢@Sooke 提供翻译

## 样例 #1

### 输入

```
4 2
4 5 9 7
1 2 11 33
```

### 输出

```
1 3 46 36 ```

## 样例 #2

### 输入

```
5 1
1 2 3 4 5
1 2 3 4 5
```

### 输出

```
1 3 5 7 9 ```

## 样例 #3

### 输入

```
1 0
2
3
```

### 输出

```
3 ```

# 题解

## 作者：fls233666 (赞：1)

可以发现，此题处理的难点在于：

- 如何确定一个骑士可以打败哪些骑士。
- 如何在一个骑士能打败是所有骑士中选出带有的金币数量最大的 $k$ 个

首先，要确定一个骑士能打败哪些骑士。由于一个骑士能否打败其它骑士取决于这个骑士的力量值，我们考虑**将所有骑士按力量值从小到大排序。** 这样，对于排序后在位置 $i$ 的骑士，他能打败的骑士就是在 $i-1,i-2,i-3,...,1$ 位置上的骑士。那么处理起来就方便了很多。

接下来要在 $[1,i-1]$ 的位置范围内找到持有金币数为前 $k$ 大的骑士。考虑到题目中 $1 \le n \le 10^5$ ,$O(n^2)$ 暴力查找显然是不可能的，要寻找更优的解决方案。

我们注意到，当排序后处理完前 $i-1$ 个骑士时，对于第 $i$ 个骑士，他的选择只会增加一个：第 $i-1$ 个骑士因为能力值比第 $i$ 个骑士小，所以排在第 $i$ 个骑士前面，也就能被第 $i$ 个骑士打败。而且，可以发现，每个骑士打败的骑士数量也是很少的（$0 \le k \le \min(10,n-1)$）。**因此，我们使用堆进行维护。** 

具体来说，就是当开始计算排序后的第 $i$ 个骑士对应的答案时，先将第 $i-1$ 个骑士持有的金币数放入堆中。计算答案时，取出堆中前 $k$ 大的金币数加入答案。答案计算完成后再将取出的 $k$ 个数放回堆中。由于 $k$ 最大值为 $10$ ，因此可以忽略不计，总时间复杂度为 $O(n \log n)$ ，可以通过此题。

最终代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 1e5+5;

int n,nk,ltmp;

ll ans[mxn],tmp[mxn];

struct knights{
	int power;
	ll coin;
	int id;
}kn[mxn];

priority_queue < ll >que;

inline bool cmp(struct knights k1,struct knights k2){
	return k1.power<k2.power;
}

int main(){
	//读入数据
	scanf("%d%d",&n,&nk);
	for(rgt i=1;i<=n;i++){
		scanf("%d",&kn[i].power);
		kn[i].id=i;  //记录排序前每个骑士的位置
	}
	for(rgt i=1;i<=n;i++)
		scanf("%lld",&kn[i].coin);
	sort(kn+1,kn+1+n,cmp);  //排序
	
	for(rgt i=1;i<=n;i++){
		if(i>1)
			que.push(kn[i-1].coin);  //加入第i-1个骑士持有的金币数
		while(!que.empty()&&ltmp<nk){
			ltmp++;
			tmp[ltmp]=que.top();
			ans[kn[i].id]+=que.top();
			que.pop();
		}  //取出前k大，如果没有k个就全取出
		ans[kn[i].id]+=kn[i].coin; 
		while(ltmp){  //算完后把取出的数放回去
			que.push(tmp[ltmp]);
			ltmp--;
		}
	}
	for(rgt i=1;i<=n;i++)
		printf("%lld ",ans[i]);  //按原本输入顺序输出
	return 0;
}
```


---

## 作者：傅思维666 (赞：1)

## 题解：

感觉这些绿题都比上面的黄题简单呢...

很容易想的贪心策略：在所有自己能吃的骑士里，尽可能吃金币多的。（采用了CSP2020贪吃蛇的说法（滑稽））

贪心策略这么好想，我觉得应该是卡时间的，也就是卡依题意模拟。

后来发现根本不卡直接模拟的做法。不需要套什么平衡树，有病么？

直接按武力值大小排序，然后从头到尾维护一个大根堆来维护金币数量，再加一个编号的映射，就OK了啊。

时间复杂度级别在$O(n\log n)$。完全可以通过本题。

于是开始思考有没有$O(n)$做法，但是没想出来...（太菜了）

如果各路大神能想到这道题的数据加强版，请一定要联系我哦！我们交流一下思路。

代码：

```cpp
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#define int long long
using namespace std;
const int maxn=1e5+5;
int n,k;
struct node
{
    int p,c,ans,id;
}a[maxn];
priority_queue<int> q;
vector<int> v;
bool cmp(node a,node b)
{
    return a.p<b.p;
}
bool cmp1(node a,node b)
{
    return a.id<b.id;
}
signed main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i].p);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i].c);
        a[i].ans=a[i].c;
        a[i].id=i;
    }
    sort(a+1,a+n+1,cmp);
    q.push(a[1].c);
    for(int i=2;i<=n;i++)
    {
        int s=q.size();
        int t=min(k,s);
        for(int j=1;j<=t;j++)
        {
            int x=q.top();
            q.pop();
            v.push_back(x);
        }
        for(int j=0;j<v.size();j++)
        {
            a[i].ans+=v[j];
            q.push(v[j]);
        }
        v.clear();
        q.push(a[i].c);
    }
    sort(a+1,a+n+1,cmp1);
    for(int i=1;i<=n;i++)
        printf("%lld ",a[i].ans);
    return 0;
}
```



---

## 作者：cz666 (赞：1)

## 思路

排序+贪心。

## 具体实现方法

1. 读入每个武士的能力值和金币数，并记录一下初始武士序列 $id$ （后面有重要的作用）

2. 以武士的武力值从小到大排序，这样可以保证第 $i$ 位武士都能任意抢走前面 $i-1$ 位武士的金币。

3. 这样第一位武士只能得到自己的金币，所以第一位武士最后得到的金币数只能是他自己原有的金币数。

4. 然后从第二位武士开始，对每一位武士要杀的排在他前面的武士进行类似于队列的操作，把第 $i-1$ 位武士放入第 $i$ 位武士要杀的数组中，排个序，取前 $k$ 个人，最后做一下这 $k$ 个人金币数的累加，再加上自己原有的金币数就是第 $i$ 位武士最多能得到的金币数。

5. 到了现在，我们答案是都统计完了，但是由于有过排序，顺序问题又出现了，怎么办呢？这时我们开始记录的 $id$ 就要发挥它存在的作用了。我们只要再来一次排序，这次排序按照 $id$ 的大小，从小到大再排一遍，我们就回到初始的武士序列了，问题成功解决。

## 时间复杂度预估

排序 $O(N*logN)$，查找并统计答案 $O(N*K*logN)$ 。

所以总时间复杂度可以估计为 $O((K+2)*N*logN)$ ，可以很优秀地通过这道题。

## AC代码：


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define dd c=getchar()
inline int read(){int s=0,w=1;char c;while (dd,c>'9' || c<'0') if (c=='-') w=-1;while (c>='0' && c<='9') s=s*10+c-'0',dd;return s*w;}
inline void write(int x){if (x<0) putchar('-'),x=-x;if (x>=10) write(x/10);putchar(x%10|'0');}
inline void wln(int x){write(x);puts("");}
inline void wlk(int x){write(x);printf(" ");}
#undef dd
//fastIO 
struct node{int power,worth,id,presure;}warrior[100003];
inline bool cmps(int x,int y){return x>y;}
inline bool cmp(node a,node b){return a.power<b.power;}
inline bool reduction(node a,node b){return a.id<b.id;}
signed main(){
	int n=read(),k=read(),opt=0,a[13];memset(a,0,sizeof a);
	for (int i=1;i<=n;i++) warrior[i].power=read();
	for (int i=1;i<=n;i++) warrior[i].worth=read();
	for (int i=1;i<=n;i++) warrior[i].id=i;
	sort(warrior+1,warrior+n+1,cmp);
	warrior[1].presure=warrior[1].worth;
	for (int i=2;i<=n;i++){
		if (opt==k){
			sort(a+1,a+k+1,cmps);
			a[k]=max(a[k],warrior[i-1].worth);
		}
		if (opt<k) a[++opt]=warrior[i-1].worth;
		for (int j=1;j<=opt;j++) warrior[i].presure+=a[j];
		warrior[i].presure+=warrior[i].worth;
	}
	sort(warrior+1,warrior+n+1,reduction);
	for (int i=1;i<=n;i++) wlk(warrior[i].presure);
	return 0;
}
```


---

## 作者：_22222222_ (赞：0)

### 题面

[CF994B Knights of a Polygonal Table](https://www.luogu.com.cn/problem/CF994B)

### solution

一道贪心题。

设当前枚举到的骑士为 $now$。

如果要在一个乱序的序列里找到所有 $p$ 值低于 $now$ 的所有骑士，时间复杂度显然爆炸，所以我们不能乱序，为了方便实时插入决策，我们将所有的骑士按 $p$ 升序排列。于是我们只需要从前往后扫一遍。

然后就是经典的贪心了，一个优先队列维护所有的最优决策点，然后一个变量维护这个最优决策点里所有 $c$ 值的和，为了保证这个优先队列里所有的点一定是最优的，我们需要实时出队一些不需要留的点，因此建一个小根堆，$c$ 值最小的位于堆顶。

由于一名骑士最多杀死 $k$ 名能力比他小的骑士，我们需要保证优先队列大小为 $k$。具体做法就是在优先队列大小大于 $k$ 时，将堆顶出队，同时更新答案。

显然我们动态维护的变量就是 $now$ 的答案，最后把 $now$ 入队更新变量即可。

正确性：堆中的每一个决策显然都是对于 $now$ 的最优决策，同时由于 $p$ 按从小到大排序，先进入堆中的决策 $i$ 显然对于 $now$ 来说都是合法决策，因为 $p_i<p_{now}$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int o=2222222;
struct node{
    int p;
    int c;
    int id;
    int ans;
}a[o];
struct cmp{
    bool operator ()(node a,node b){
        return a.c>b.c;
    }
};
priority_queue<node,vector<node>,cmp>q;
int n,k;
bool cmp1(node c,node b){
    return c.p<b.p;
}
bool cmp2(node c,node b){
    return c.id<b.id;
}
void in(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i].p);
    }
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i].c);
    }
    for(int i=1;i<=n;i++){
        a[i].id=i;
    }
}
void work(){
    sort(a+1,a+n+1,cmp1);
    int now=0;
    for(int i=1;i<=n;i++){
        a[i].ans=now+a[i].c;
        q.push(a[i]);
        now+=a[i].c;
        while(q.size()>k){
            now-=q.top().c;
            q.pop();
        }
    }
    sort(a+1,a+n+1,cmp2);
}
void out(){
    for(int i=1;i<=n;i++){
        printf("%lld ",a[i].ans);
    }
}
signed main(){
    in();
    work();
    out();
    return 0;
}

```
### update

可以看下[[TJOI2013] 奖学金](https://www.luogu.com.cn/problem/P3963)。

如果做过，那么这个题就非常显然了。

本题于 $2022.07.02$ 通过，题解写于 $2022.08.22$。

[广告位](https://www.cnblogs.com/22222222STL/)

---

## 作者：KKarshilov (赞：0)

优化算法的一个很好的方向就是向范围更小的变量~~下手~~优化

这题所有变量很明显是k最小，我的做法就是先按武力值排个序，这样所有在第i个骑士前面的武士都可以被杀掉，然后只需要动态维护前面所有的武士的钱的前k大即可，用一个堆就搞定了

堆可以直接用priority_queue

```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long

template <typename T> inline void read(T &x) {
    int c = getchar();
    bool f = false;
    for (x = 0; !isdigit(c); c = getchar()) {
        if (c == '-') {
            f = true;
        }
    }
    for (; isdigit(c); c = getchar()) {
        x = x * 10 + c - '0';
    }
    if (f) {
        x = -x;
    }
}

const int MAXN = 100100;
const int INF = 0x3f3f3f3f;

int n, m, a[MAXN];
LL ans[MAXN];

struct knight {
    int Pow, Coin, index;
    knight() {
        index = Pow = Coin = 0;
    }
}k[MAXN];

struct SB {
    priority_queue<int>q;
    LL sum;
}ss;

bool operator < (knight a, knight b) {
    return a.Pow < b.Pow; 
}

signed main() {
    read(n), read(m);
    for(int i = 1; i <= n; i++) read(k[i].Pow), a[i] = k[i].Pow;
    for(int i = 1; i <= n; i++) read(k[i].Coin), k[i].index = i;
    if(m == 0) {
        for(int i = 1; i <= n; i++) printf("%d ", k[i].Coin);
        return 0;
    }
    if(n == 1) {
        printf("%d ", k[1].Coin);
        return 0;
    }
    sort(k + 1, k + n + 1);
    for(int i = 1; i <= m + 1; i++) {
        for(int j = 1; j <= i; j++) {
            ans[k[i].index] += (LL) k[j].Coin;
        }
    }
    for(int i = 1; i <= m; i++) ss.q.push(-k[i].Coin), ss.sum += k[i].Coin;
    if(k[m + 1].Coin > -ss.q.top()) {
        ss.sum -= -ss.q.top();
        ss.q.pop();
        ss.q.push(-k[m + 1].Coin);
        ss.sum += k[m + 1].Coin;
    }
    for(int i = m + 2; i <= n; i++) {
        ans[k[i].index] += k[i].Coin;
        ans[k[i].index] += ss.sum;
        if(k[i].Coin > -ss.q.top()) {
            ss.sum -= -ss.q.top();
            ss.q.pop();
            ss.q.push(-k[i].Coin);
            ss.sum += k[i].Coin;
        }	
    }
    for(int i = 1; i <= n ; i++) printf("%I64d ", ans[i]);
    return 0;
} 
```

---

