# [USACO12OPEN] Balanced Cow Subsets G

## 题目描述

我们定义一个奶牛集合 $S$ 是平衡的，当且仅当满足以下两个条件：

- $S$ 非空。
- $S$ 可以被**划分**成两个集合 $A,B$，满足 $A$ 里的奶牛产奶量之和等于 $B$ 里的奶牛产奶量之和。划分的含义是，$A\cup B=S$ 且 $A\cap B=\varnothing$。

现在给定大小为 $n$ 的奶牛集合 $S$，询问它有多少个子集是平衡的。请注意，奶牛之间是互不相同的，但是它们的产奶量可能出现相同。

## 说明/提示

对于全部数据，保证 $1\le n\le 20$，$1\le a_i\le 10^8$。

## 样例 #1

### 输入

```
4 
1 
2 
3 
4 
```

### 输出

```
3 
```

# 题解

## 作者：houzhiyuan (赞：81)

首先，一个有$20$头奶牛，那么考虑对于每一头奶牛来说有$3$种状态，放在一组，放在另一组，不放任何一组，如果暴力枚举时间复杂度为$O(3^n)>1E9$，无法接受。

考虑将$n$头奶牛分为两半，每组分别暴力求解，时间复杂度$O(3^\frac{n}{2})$可以通过。

假设在前一半中，在第一组中放的数的和为$a$，在第二组中放的数为$b$。

假设在后一半中，在第一组中放的数的和为$c$，在第二组中放的数为$d$。

那么$a+c=b+d$

由于我们要对每一半分开处理，所以考虑将同一半的数放在一起处理，即移项得$a-b=c-d$。

因此，我们只需要统计在每一半中和为$a-b$的方案有多少中，在进行组合。

一个数被放入第一组中，$a-b$的值变大，在第二组中，$a-b$的值变小，如果不放，则$a-b$不变，所以维护$a-b$的值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,N,a[21],ans[2000001],s,tot;
vector<int> p[2000001];
map<int,int> b;
void dfs1(int x,int sum,int now){//对前一半搜索，x表示到了第几个，sum表示a-b的值，now表示状压，取了那些数
	if(x>N){
		if(b[sum]==0) b[sum]=++tot;//离散化
		p[b[sum]].push_back(now);//放入方案
		return;
	}
	dfs1(x+1,sum+a[x],now|(1<<(x-1)));  //三种情况讨论
    dfs1(x+1,sum-a[x],now|(1<<(x-1)));  
    dfs1(x+1,sum,now);
} 
void dfs2(int x,int sum,int now){//对后一半搜索，同上
	if(x>n){ 
		int t=b[sum];
		if(t!=0)  for(int i=0;i<p[t].size();i++)  ans[p[t][i]|now]=1;//对于每一种可能的组合，将值赋为1，注意，题目中要求的方案数为取数的方案数而不是分数的方案数，因此不是+1而是=1
		return;
	}
	dfs2(x+1,sum+a[x],now|(1<<(x-1)));  
    dfs2(x+1,sum-a[x],now|(1<<(x-1)));  
    dfs2(x+1,sum,now);
} 
int main(){
	scanf("%d",&n); N=n/2;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	dfs1(1,0,0);
	dfs2(N+1,0,0);
	for(int i=1;i<=(1<<n);i++)s+=ans[i];
	printf("%d",s);
} 
```


---

## 作者：ZAGER (赞：42)

## 题解

#### 这道题算是一个折半搜索(meet in the middle)的好题

[透彻](https://www.cnblogs.com/ZAGER/p/9823171.html)

如果对折半搜索不太熟悉，可以先做一道较简单的题  [CEOI2015 Day2]世界冰球锦标赛

[BZOJ链接](https://www.lydsy.com/JudgeOnline/problem.php?id=4800)或[洛谷链接](https://www.luogu.org/problemnew/show/P4799)  附加[my blog](https://www.cnblogs.com/ZAGER/p/9827160.html)

这道题有三种状态

1. 不放入任何集合
2. 放入左边集合
3. 放入右边集合

在搜索时如何表示呢，我们可以0,1,-1来表示，代码如下：

```cpp
dfs(dep+1,sum);
dfs(dep+1,sum+v[dep]);
dfs(dep+1,sum-v[dep]);
```

但是我们得到的答案可能会有重复，就是我们可能把一个数选入左集合或右集合，但是都加入了状态，所以我们需要判重。

如何去判重，状态压缩，压成2进制去判重。

所以搜索时还要去记录状态，用一个$vis$数组判重。

```cpp
if(!vis[a[l].state|b[r].state])
	vis[a[l].state|b[r].state]=1;//state记录二进制的选数状态  1表示选 0表示没选
```

最后要统计答案，排序后双指针扫描一遍即可。

注意，最后别忘了把0的那种方案减去。

### code：

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cctype>
#define ll long long
#define R register
#define N 22
using namespace std;
template<typename T>inline void read(T &a){
    char c=getchar();T x=0,f=1;
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    a=f*x;
}
int n,v[N<<1],maxdep,cnta,cntb;
bool vis[1<<N];
ll ans;
struct node{
    int state,x;
}a[1<<N],b[1<<N];
inline bool cmp1(R node a,R node b){
    return a.x<b.x;
}
inline bool cmp2(R node a,R node b){
    return a.x>b.x;
}
inline void dfs(R int dep,R int sum,R int now,R int flg){
    if(dep==maxdep+1){
        if(!flg){
            a[++cnta].x=sum;
            a[cnta].state=now;
        }
        else{
            b[++cntb].x=sum;
            b[cntb].state=now;
        }
        return;
    }
    dfs(dep+1,sum,now,flg);
    dfs(dep+1,sum+v[dep],now+(1<<(dep-1)),flg);
    dfs(dep+1,sum-v[dep],now+(1<<(dep-1)),flg);
}
int main(){
    read(n);
    for(R int i=1;i<=n;i++)read(v[i]);
    maxdep=n/2;dfs(1,0,0,0);
    maxdep=n;dfs(n/2+1,0,0,1);
    sort(a+1,a+1+cnta,cmp1);
    sort(b+1,b+1+cntb,cmp2);
    R int l=1,r=1;
    while(l<=cnta&&r<=cntb){
        while(-a[l].x<b[r].x&&r<=cntb)r++;
        R int pos=r;
        while(r<=cntb&&-a[l].x==b[r].x){
            if(!vis[a[l].state|b[r].state]){
                vis[a[l].state|b[r].state]=1;
                ans++;
            }
            r++;
        }
        if(l<cnta&&a[l].x==a[l+1].x)r=pos;//相同让b数组的指针回来
        l++;
    }
    printf("%lld\n",ans-1);//减去一个空集
    return 0;
}
```



---

## 作者：NKU_AI_HMX (赞：34)

这是提交记录中140ms，最快的算法。

## 目录
1. 题意解读
2. 算法思想
3. 代码展示
4. 习题推荐

## 正文
#### 1.题意解读


------------
对于每个人我们有三种选择，不取、取出至1队、取出至2队。我们分别给这几种情况赋值为0、1、-1，那么问题就类似于给每个人分配三个权值中的一个，和为0的方案数。但是这里要注意题中问的是：
 **“给n个数，从中任意选出一些数，使这些数能分成和相等的两组。求有多少种选数的方案。”**
也就是说，只要某一组数可以分成两个相等的集合，不管这一组可以有多少种方案分成两个相等的集合那么计数加一，**而不是求所有的两个集合相等的组合方案数**。

大家看了其他题解或者根据经验也明白这一题用二分搜索是一个不错的选择，可以比较轻松搜完。但麻烦就麻烦在如何去重？


------------
#### 2. 算法思想


------------
本算法的 $bitset$ 数组为核心，建议先行了解。

我们的第一部分搜索为 $ldfs$，搜索数组下标0到 $mid-1$ 的数据，我们每层搜索向下传递3个变量分别为 $k$（数组下标）,$cost$（当前所选择数的总权值）,$id$（由选择的数所组成的二进制 $key$）， 每次搜索到底后记录下对应总权值 $cost$ 并把对应 $cost$ 下的 $id$ 标记为1。

#### 代码如下：
```cpp
const int maxN = 20, halfN = 10;
int n,mid,ans, a[maxN];
bitset<1 << halfN> vis[1 << halfN];
map<int, bitset<1 << halfN>> mp;

void ldfs(int k, int cost, int id) {
    if (k ==mid) {
        mp[cost].set(id);//bitset中的set（id）意思是把bitset数组中的id位设置为1，这里意思是标记为去过。
        return;
    }
    ldfs(k + 1, cost, id);
    ldfs(k + 1, cost + a[k], id | (1 << k));
    ldfs(k + 1, cost - a[k], id | (1 << k));
}
```
我们的第二部分搜索为 $hdfs$,其在 $mid$ 至 $n-1$ 间搜索其与第一部分不同的是在搜索到底后我们需要找到搜索第一部分中与第二部分 $cost$ 相等的数据，**然后记录那些没被重复计算的部分**。

**代码如下：**
```cpp
void hdfs(int k, int cost, int id) {
   
    if (k == n) {
        if (mp.count(cost)) { 
           
            bitset<1 << halfN> s(mp[cost]);//拷贝函数 
             s &= ~vis[id];//vis数组表示此id和其他id1组合的记录，若组合过则vis[id]的第id1位为1。这一步操作将s中与vis[id]同为1的位计为0，意思就是去重。
            ans += s.count();//s中剩余的仍为1的位数之和即为符合条件的答案。
            vis[id] |= s;//把上面记录答案的s中的对应1在vis[id]中标记，表示这个id1已经去过。为接下来去重准备。
        }
        return;
    }
    hdfs(k + 1, cost, id);
    hdfs(k + 1, cost + a[k], id | (1 << k-mid));
    hdfs(k + 1, cost - a[k], id | (1 << k-mid));
}
```
$main$ 函数部分大家都看得懂，就不细说了，只是里面用了次 $sort$，经验表明大部分情况排序后再二分搜索会更快。


------------
#### 3. 代码展示


------------

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
char ch1;
template<class T>
inline void rd(T& x) {
	x = 0; bool w = 0;
	ch1 = getchar();
	while (!isdigit(ch1)) { ch1 == '-' && (w = 1), ch1 = getchar(); }
	while (isdigit(ch1)) { x = (x << 1) + (x << 3) + (ch1 & 15), ch1 = getchar(); }
	w && (x = (~x) + 1);
}
template<class T>
inline void wr(T x)
{
	if (x < 0) x = -x, putchar('-');
	if (x < 10) {
		putchar(x + 48);
		return;
	}
	T L = x / 10;
	wr(L);
	putchar(x - ((L << 1) + (L << 3)) + 48);
}
const int maxN = 20, halfN = 10;
int n,mid,ans, a[maxN];
bitset<1 << halfN> vis[1 << halfN];
map<int, bitset<1 << halfN>> mp;

void ldfs(int k, int cost, int id) {
    if (k ==mid) {
        mp[cost].set(id);
        return;
    }
    ldfs(k + 1, cost, id);
    ldfs(k + 1, cost + a[k], id | (1 << k));
    ldfs(k + 1, cost - a[k], id | (1 << k));
}
void hdfs(int k, int cost, int id) {
   
    if (k == n) {
        if (mp.count(cost)) { 
           
            bitset<1 << halfN> s(mp[cost]); 
             s &= ~vis[id];
            ans += s.count();
            vis[id] |= s;
        }
        return;
    }
    hdfs(k + 1, cost, id);
    hdfs(k + 1, cost + a[k], id | (1 << k-mid));
    hdfs(k + 1, cost - a[k], id | (1 << k-mid));
}
int main() {
    cin >> n; mid = n >> 1;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    sort(a, a + n);//加了更快
    ldfs(0, 0, 0);
    hdfs(mid, 0, 0);
    cout << ans - 1 ;//去除两个都为0的情况所以减1
    return 0;
}
```


------------
#### 4. 习题推荐：
[Scales S](https://www.luogu.com.cn/problem/P5194)，[世界冰球锦标赛](https://www.luogu.com.cn/problem/P4799)

注：算法思想来自[DataSailor](https://www.luogu.com.cn/user/8513#practice)
笔者基于其思想在代码的可读性等方面优化，比原代码稍快35ms。



---

## 作者：Ofnoname (赞：23)

这道题的题解大都是将搜到的两个数组排序，用两个指针寻找合法答案的。但是如果前一半数组的有相同的值，后一半的指针就不能移动了，而前一半数组里相同的值之间如果直接累加相同的答案，又导致重复，所以只能将后一半的指针移到上次的位置再跑一次。可以设想，如果前一半数组的数全部相同，那么就很容易`TLE`，过不了加强版。

我们换个角度考虑，`N`只有区区20，所有选或不选的方案数只有$2^N\ = \ 1e6$，如果在两次搜索就把每种选的情况可行性做出来，就可以解决问题。

第一次搜索时，我们记录每一种结果可以被哪些组合拼出来（`N == 20`，组合状态是可以压缩的）。当然一种结果可能被多个组合拼出来，所以要用`vector`记录，而一个结果也可能很大，需要用`map`离散化（编个号就行，不用排序）。

那么第二次搜索时，每当我们得到一个结果`S`，我们是需要前一半产生`-S`的总和来得到方案的，显然`-S`的方案就是`S`的方案反过来而已，是完全等效的，那么我们遍历第一次搜到的所有能使前一半算出`S`的方案，他们的组合与后一半的组合并在一起就是一个可能的答案。

```cpp
#include <bits/stdc++.h>
#define MAX (2000000 + 7)
using namespace std;

int N, mx, mc, ans, a[23], use[MAX];

vector <int> d[MAX];
map <int, int> M;

void DFS1(int i, int sum, int now)//now为压缩状态，sum为当前和 
{
	if (i > mx)
	{
		if (!M.count(sum)) M[sum] = ++mc;//（伪）离散化
		d[M[sum]].push_back(now);//当前now可以拼出sum的和 
		return;
	}
	DFS1(i+1, sum, now);
	DFS1(i+1, sum+a[i], now|(1<<(i-1)));
	DFS1(i+1, sum-a[i], now|(1<<(i-1)));
}

void DFS2(int i, int sum, int now)
{
	if (i > N)
	{
		if (M.count(sum))
		{
			int x = M[sum];//寻找前一半能拼出-sum的组合 
			for (int i = 0; i < d[x].size(); i++)
				use[d[x][i] | now] = 1;//两半组合就是一个可能的一个答案 
		}return;
	}
	DFS2(i+1, sum, now);
	DFS2(i+1, sum+a[i], now|(1<<(i-1)));
	DFS2(i+1, sum-a[i], now|(1<<(i-1)));
}

int main()
{
	scanf("%d", &N), mx = N >> 1;
	for (int i = 1; i <= N; i++)
		scanf("%d", a + i);
	DFS1(1, 0, 0), DFS2(mx + 1, 0, 0);
	for (int i = 1; i <= 1<<N; i++)//遍历每一种 
		ans += use[i];
	printf("%d\n", ans);
}
```

---

## 作者：E_huan (赞：16)

## 三进制状态压缩写法


看了一下其它题解，似乎没有这种写法，所以发一篇题解**提供一个新写法**。

由于可以把双向的两个部分合在一起写，代码会比大部分搜索写法短不少，只有 $33$ 行。

发现每个数其实有 $3$ 种状态: $1$ 组、 $2$ 组、不分组。

虽然 $N$ 很小但直接枚举是 $3^{20}$ 仍然无法接受。


但是 $N$ 确实很小，考虑怎么优化纯暴力枚举，不难想到 meet in middle。

但这里说的 meet in middle 也可以用状态压缩来实现，枚举是三进制状态压缩，判重是二进制状态压缩。


$f[0][i]$ 存储考虑前一半的数，分成两组的差值（ $1$ 组- $2$ 组）是  $i$ 的所有方案。


$f[1][i]$ 存储考虑后一半的数，分成的两组的差值是 $i$ 的所有方案。


三进制状压 DP 即可求出这两个数组（用 `unordered_map` 实现）。


然后 `for()` 一遍累加答案即可，需要判重。


注意求的是选数的方案不是分组的方案。


## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,B[2],a[22],pow3[12],ans;
bool st[(1<<20)+5];
unordered_map<int,vector<int> > f[2];
int main()
{
    scanf("%d",&n); 
    B[0]=(n/2),B[1]=n-B[0];//B[0] B[1]是“前一半” 后一半“大小（因为n可能是奇数 所以不一定相等）
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    pow3[0]=1;
    for(int i=1;i<=B[1];i++) pow3[i]=pow3[i-1]*3;//B[1]>=B[0] 处理到B[1]就够了
    for(int t=0;t<=1;t++)
        for(int s=0;s<pow3[B[t]];s++)
        {
            int d=0,S=(1<<B[0])-1;
            if(t==1) S=((1<<n)-1)-S;
            for(int i=0;i<B[t];i++)
            {
                int v=(s/pow3[i])%3; 
                if(v==1) d+=a[i+t*B[0]];
                else if(v==2) d-=a[i+t*B[0]];
                else S-=(1<<(i+t*B[0]));
            }//i+t*B[0] 则t=0的时候就是i,t=1的时候会加上B[0],就可以把两个数组放到一起求
            f[t][d].push_back(S);
        }
    for(pair<int,vector<int> > a:f[0])
        for(int b:a.second)
            for(int c:f[1][-a.first])
                if(!st[c|b]) ans++,st[c|b]=1;
    printf("%d\n",ans-1);
    return 0;
}
```

**其实也有其它的双向搜索题可以用状态压缩实现枚举。**

比如 P4799 [CEOI2015 Day2] 世界冰球锦标赛 。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,B[2],cnt[2];
ll a[45],m,ans,f[2][(1<<20)+5];
int main()
{
    scanf("%d%lld",&n,&m); B[0]=(n/2);B[1]=n-B[0];
    for(int i=0;i<n;i++) scanf("%lld",&a[i]);
    for(int t=0;t<=1;t++)
    {
        int up=(1<<B[t])-1;
        for(int s=0;s<=up;s++)
        {
            ll val=0;
            for(int i=0;i<B[t];i++)
                if(s&(1<<i))
                    val+=a[t*B[0]+i];
            if(val<=m) f[t][++cnt[t]]=val;
        }
    }
    sort(f[0]+1,f[0]+cnt[0]+1);
    for(int i=1;i<=cnt[1];i++) 
        ans+=(upper_bound(f[0]+1,f[0]+cnt[0]+1,m-f[1][i])-f[0]-1);
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Mr_Skirt (赞：9)

介绍一种解这道题的新思路：$bitset$强行怼。

先从暴力算法开始，我们只需要枚举所有集合以及他们的子集，如果发现子集以及其补集的和相等，那么这个集合就是一种方案。

更具体的说，假设$P$是原集合，$S$是$P$的所有子集。如果$\forall s\in S$ 的子集有 $sum(s) == sum(\bar{s})$，那么$S$就贡献一个答案。

于是我们可以写出如下的代码：
```cpp
    for (int i = 1; i < (1 << n); i++) {
        for (int s1 = i; s1; s1 = (s1 - 1) & i) {
            if (sum[s1] == sum[i ^ s1]) {
                ans++;
                break;
            }
        }
    }
```
子集求和是$O(n2^n)$但是枚举子集的子集是$O(3^n)$的，显然会TLE的死死的。

于是我们会想到折半枚举，假设我们能枚举前一半和后一半的所有子集，那么应该怎么确定哪些子集是符合条件的呢？

假设对于一个集合$S_1$我们有一个子集$s_1$和补集$\bar{s_1}$，同时我们有另一个集合$S_2$和子集$s_2$和$\bar{s_2}$，如果这个集合能合并，那么我们需要有

- $S_1 \cap S_2 = \emptyset$
- $sum(s_1) + sum(s_2) == sum(\bar{s_1}) + sum(\bar{s_2})$

第一个条件用折半枚举可以保证。对于第二个来说，假设我们有$sum(s_1)-sum(\bar{s_1})=d$，那么如果$sum(\bar{s_2})-sum(s_2)=d$，那么就满足了第二个条件。

于是我们可以枚举左边的所有可能，然后记录有多少个集合具有差值$d$。然后在枚举右边的时候，对于每个右边子集，找到它的子集总共能匹配多少个左边子集。为了表述清晰，设$S_l$为左边集合的子集，$S_r$为右边集合的子集。对于每个右边集合的子集$s_r \subset S_r$，以及它的子集$ss_r \subset s_r$，我们要求：
$$
	\sum_{s_r}|\bigcap_{ss_r\in s_r}\{s_l\text{使得}ss_r\text{可以与左边合并}\}|
$$

所以我们要求差值为$d$集合的并集，但是集合个数有$2^{\frac{n}{2}}$个，无法用状态压缩($int$和long long)表示。于是我们就想到了使用$bitset$，$2^{\frac{n}{2}}$在这道题中仅有$1024$，$bitset$实现中每个集合所占空间仅有$\frac{1024}{8} = 128$字节。

我们再来计算一下总共可能会有多少种差值，不好计算但是可以估算出是小于$3^{10}=6\times10^4$的，也就是最坏也只是$sum$数组的内存级别。

于是我们只要维护一个map<int,bitset<1024>>就可以了。

以下是这种解法对应的代码：

时间复杂度$O(n2^n+3^{n/2}\log{3^{n/2}})$，因为我用了map。
```cpp
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <map>
using namespace std;
const int MAXN = 25;
int n, m, k;
int arr[MAXN];
int sum[(1 << 20) + 5];
map<int, bitset<1024>> mpp;
int main() {
#ifdef LOCALLL
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    // 求出所有子集的和
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) sum[i] += arr[j];
        }
    }
    // 枚举左边
    int mid = n / 2;
    for (int i = 0; i < (1 << mid); i++) {
        for (int s1 = i;; s1 = (s1 - 1) & i) {
            mpp[sum[s1 ^ i] - sum[s1]].set(i, true);
            if (!s1) break;
        }
    }
    // 枚举右边
    int ans = 0;
    for (int i = 0; i < (1 << (n - mid)); i++) {
        bitset<1024> sss(0);
        // 这里我刻意保留了子集为空的情况
        for (int s1 = i;; s1 = (s1 - 1) & i) {
            int diff = sum[s1 << mid] - sum[(s1 ^ i) << mid];
            sss |= mpp[diff];
            if (!s1) break;
        }
        // 对答案的贡献就是这个集合的大小
        ans += sss.count();
    }
    // 要减去左边右边都是空集的情况
    printf("%d\n", ans - 1);
    return 0;
}
```




---

## 作者：attack (赞：8)

首先观察数据范围n<=20，可以想到搜索算法


转化一下模型，不难想到这道题对于每个数来说会有三种情况


1.没有被选择


2.被选择进了左边的集合里


3.被选择进了右边的集合里


那么我们可以将这三种情况用-1,0,1表示


那么我们所需要做的就是枚举所有可能暴力统计


但是3^n很明显是会超时的


那怎么办的？


我们可以用meet in the middle的思想，也就是所谓的折半搜索


先枚举左边的情况


再枚举右边的情况


最后把两种情况排个序，暴力统计


时间复杂度比较玄学

大约是2.23^n?

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=21;
inline void read(int &n)
{
    char c=getchar();bool flag=0;n=0;
    while(c<'0'||c>'9')    c=='-'?flag=1,c=getchar():c=getchar();
    while(c>='0'&&c<='9')    n=n*10+c-48,c=getchar();flag==1?n=-n:n=n;
}
int n;
int a[MAXN];
int vis[1<<MAXN];
struct node
{
    int val,cur;// val权值  cur状态 
}Left[1<<MAXN],Right[1<<MAXN];
int LeftCnt=0,RightCnt=0;
void dfs(int bg,int ed,int nowval,int nowstate)
{
    if(bg>ed)// 本次搜索完成
    {
        if(ed==n/2)    Left[++LeftCnt].val=nowval,Left[LeftCnt].cur=nowstate;
        else Right[++RightCnt].val=nowval,Right[RightCnt].cur=nowstate;
        return ;    
    } 
    dfs(bg+1,ed,nowval,nowstate);// 不选
    dfs(bg+1,ed,nowval-a[bg],nowstate+(1<<(bg-1)));// 选了且放在左边的区间里 
    dfs(bg+1,ed,nowval+a[bg],nowstate+(1<<(bg-1)));// 选了且放在右边的区间里 
}
int comp1(const node &a,const node &b){    return a.val<b.val;        }
int comp2(const node &a,const node &b){    return a.val>b.val;        }
int main()
{
    read(n);
    for(int i=1;i<=n;i++)    read(a[i]);
    dfs(1,n/2,0,0);
    dfs(n/2+1,n,0,0);//分开dfs
    sort(Left+1,Left+LeftCnt+1,comp1); 
    sort(Right+1,Right+RightCnt+1,comp2);
    int l=1,r=1,ans=0;
    while(l<=LeftCnt&&r<=RightCnt)
    {
        while(Left[l].val+Right[r].val>0&&r<=RightCnt)    r++;
        int pre=r;
        while(Left[l].val+Right[r].val==0&&r<=RightCnt)    
        {
            if(vis[ Left[l].cur|Right[r].cur ] == 0)    vis[ Left[l].cur|Right[r].cur ]=1,    ans++;
            r++;
        }
        if(Left[l].val==Left[l+1].val)/*一个小剪枝*/     r=pre;
        l++;
    }
    printf("%d",ans-1);
    return 0;
}
```

---

## 作者：顾z (赞：7)

# [顾](https://www.luogu.org/blog/RPdreamer/#)[z](https://www.cnblogs.com/-guz/)

~~你没有发现两个字里的blog都不一样嘛~~ qwq

> ### Description
>
> 给n个数，从中任意选出一些数，使这些数能分成和相等的两组。
>
> 求有多少种选数的方案。
>
> ### Input
>
> 第$1$行：一个整数$N$
>
> 第$2$到$N+1$行,包含一个整数$m_i$
>
> ### Output
>
> 一行：平衡的集合的个数.

看到题的一瞬间数据范围?

$N \leq 20$？状压!

明显直接做过不去,选择**折半搜索**.

折半搜索的话会有三种情况

- 一.选择当前位置
- 二.选择当前位置,给第一组.
- 三.选择当前位置,给第二组.

然后直接跑折半搜索+状压即可.

存储类似链式前向星,应该不是很难理解,就不过多解释了.

然后就枚举状态即可,可是直接枚举到$2^n-1$显然会$T$掉.

由于我们后半截的状态已知,所以说,我们只需要枚举前一半的状态即可.

注意要$sort$找到两边值相等的.

其他的就不太难理解了,如果不能理解的话可以私信我 qwq.

``代码``

```c++
#include<cstdio>
#include<cctype>
#include<algorithm>
#define N 10000008
#define R register
using namespace std;
inline void in(int &x)
{
	int f=1;x=0;char s=getchar();
	while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
	while(isdigit(s)){x=x*10+s-'0';s=getchar();}
	x*=f;
}
int n,w[28],mid,head[N];
struct cod{int u,val;}e[200008],edge[N];
int v[N],ans,tot,ttt,sta,cnt;
bool vis[2500000];
void dfs1(int dep,int sum,int state)
{
	if(dep>mid)
	{
		edge[++tot].u=head[state];
		edge[tot].val=sum;
		head[state]=tot;
		return;
	}
	dfs1(dep+1,sum,state);
	dfs1(dep+1,sum+w[dep],state|(1<<(dep-1)));
	dfs1(dep+1,sum-w[dep],state|(1<<(dep-1)));
}
void dfs2(int dep,int sum,int state)
{
	if(dep>n)
	{
		e[++ttt].u=state;
		e[ttt].val=sum;
		return;
	}
	dfs2(dep+1,sum,state);
	dfs2(dep+1,sum+w[dep],state | (1<<(dep-1)));
	dfs2(dep+1,sum-w[dep],state | (1<<(dep-1)));
}
inline bool ccp(const cod&a,const cod&b)
{
	return a.val<b.val;
}
int main()
{
	in(n);mid=(n+1)>>1;sta=(1<<n)-1;
	for(R int i=1;i<=n;i++)in(w[i]);
	dfs1(1,0,0);dfs2(mid+1,0,0);
	sort(e+1,e+ttt+1,ccp);
	for(R int i=0;i<=(1<<mid);i++)
	{
		R int cnt=0;
		for(R int j=head[i];j;j=edge[j].u)
			v[++cnt]=edge[j].val;
		sort(v+1,v+cnt+1);
		R int pos=1;
		if(v[1]>e[ttt].val)break;
		for(R int j=1;j<=ttt;j++)
		{
			while(pos<=cnt and v[pos]<e[j].val)pos++;
			if(pos>cnt)break;
			if(v[pos]==e[j].val)
				vis[i|e[j].u]=true;
		}
	}
	for(R int i=1;i<=sta;i++)
		if(vis[i])ans++;
	printf("%d",ans);
}
```

---

## 作者：Tan_Wei_Ye (赞：6)

**这里介绍一种不用双指针的写法**

~~其实是我看不懂双指针所以写的暴力~~

------------
## 一、折半搜索
**适用情况** ：
1. 知道总共要搜索的步数和最终的答案状态。
2. 普通的搜索难以通过，也没有更好的做法。

拿这题来举例子：

显然我们可以写出一个 $O(3^n)$ 的做法：暴力枚举每个数“不选”，“放进 $A$ 组”，“放进 $B$ 组”三种情况。

所以我们知道了总共要搜索 $n$ 步，那么考虑把这 $n$ 步分成 $2$ 半来走：
1. 先枚举 $ 1 \sim n/2 $ 个数的状态。
2. 再枚举 $ n/2+1 \sim n $ 个数的状态。
3. 求出答案。

当然这是一个很 $naive$ 的想法，因为这样完全没考虑重复的情况，那么怎么判重呢？这就是接下来要讲的：

## 二、暴力判重
对，就是暴力判重，没有什么花里胡哨的东西。

我们在 `dfs` 时，用一个二进制数记录取数的情况。

然后每次在搜索完后，按照它的值存入一个 `map` 中，最后暴力统计答案。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=21;
int n,a[N],ans;
map<int,vector<int> > m;
bool s[1<<20];
void dfs(int x,int sum,int t)
{
	if(x>n/2)
	{
		m[sum].push_back(t);//把能到达 sum 的状态存起来
		return ;
	}
	dfs(x+1,sum,t);		     // 不选的话 sum 不变
	dfs(x+1,sum+a[x],t|1<<x-1);// 放入 A 组就是 sum+a[x]
	dfs(x+1,sum-a[x],t|1<<x-1);// 放入 B 组就是 sum-a[x]
}
void dfs2(int x,int sum,int t)
{
	if(x>n)
	{
		if(!m.count(sum)) return ;
		int r=m[sum].size();
		for(int i=0;i<r;i++)
			s[t|m[sum][i]]=1;//把 2 次搜索的状态合并起来
		return ;
	}
	dfs2(x+1,sum,t);
	dfs2(x+1,sum+a[x],t|1<<x-1);
	dfs2(x+1,sum-a[x],t|1<<x-1);
}
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	dfs(1,0,0);
	dfs2(n/2+1,0,0);
	for(int i=1;i<1<<n;i++)//枚举所有状态，找出可行的
		ans+=s[i];
	cout<<ans;
}
```
时间复杂度:
$$
O(3^\frac{n}{2} \times log_2(3^\frac{n}{2}) + 2^n)
$$
简单易懂，非常好写。

——那么，代价是什么呢？

~~代价是你不吸氧过不了。~~

---

## 作者：一只书虫仔 (赞：5)

#### Description

> 给定一个长度为 $n$ 的序列 $a_i$，求选择两个 $a_i$ 的不相交子序列使得这两个子序列的和相等，求选择子序列数。

#### Solution

考虑将序列劈成两半，对于两半分别枚举，每次考虑将其分到第一组，分到第二组还是不分到任意一组。

考虑状态表示，对于分到第一组可以将其设为正数，分到第二组可以将其设为负数，不分就不将其设入答案，如果最后和为 $0$ 就是一组合法解。

但是注意，不能两组都为空，因此答案还需要减 $1$。

这么一打，不难发现，样例过不了！！1 为什么呢？因为这么计数会出现重复。

考虑去重，定义 $vis$ 数组（bool），$vis_i$ 中的 $i$ 为一个长度为 $n$ 的二进制数（可以用 int 十进制存储），如果 $vis_i=0$，那么就记录这一个值，并 $vis_i \leftarrow 1$；如果 $vis_i=1$，那么就跳过这个值。记录 $i$ 也不是难事，在进入新的 dfs 时进行更新，跳出时回溯（使用位运算）即可。

---

## 作者：一颗赛艇 (赞：5)

如果不是牛奶生产的牛奶量不大，那么这个问题将是一个比较简单的动态规划案例。另一方面，N是相当小的，所以指数时间方法可能是可行的。


显而易见的方法是依次测试每个子集S。如果S的总和为A，则尝试S的所有子集，以查看其中一个是否有A / 2的总和。迭代所有子集的所有子集需要3 ^ N个步骤，这对于可用的时间有一点太大。


为了减少所需的时间，我们可以使用“中间会议”方法。将牛均匀分成两组，涂一套棕色，另一只白色。假设集合S是平衡的，并且可以被分成具有相同和的子集A和B。然后总和（A中的棕色） - 总和（B中的棕色）=和（B中的白色） - 总和（A中的白色），即S中的棕色奶牛可以分成两组，S中的白色奶牛也可以分裂分为两组，“不平衡”程度相同。我们现在可以尝试扭转这个过程：对于褐色牛的每一个子集，计算所有可能的不平衡值并存储它们; 类似于白牛。然后，对于每个可能的不平衡值，将所有具有该值的棕色子集与所有具有该值的白色子集进行配对，以使平衡的棕白色组的母牛。


什么是计算效率？较慢的部分将是最终的匹配。不清楚如何获得一个紧密的界限，但是近似值要注意，有分配O（3 ^（N / 2））种方式来分配褐色牛的子集，而在最坏的情况下，这些分区之一可能会匹配给出白牛的所有子集，给出O（3 ^（N / 2）.2 ^（N / 2））= O（6 ^（N / 2））时间，这是足够好的。


可以做出的另一个优化是当尝试将一个棕色子集与一个白色子集匹配时，可以选择两个子集中较小的子集，迭代该子集的每个不平衡，然后通过执行另一个子集寻找相同的不平衡查找哈希表。这导致分析运行时更快但更复杂，可以显示为（1 + sqrt 1.5）^ N，有点好于（sqrt 6）^ N。








```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <utility>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
vector<pii> half(const vector<int> &S)
{
    vector<pii> ans;
    int N = S.size();
    for (int i = 0; i < (1 << N); i++)
        for (int j = i; ; j = (j - 1) & i)
        {
            int sum = 0;
            for (int k = 0; k < N; k++)
            {
                if (j & (1 << k))
                    sum -= S[k];
                else if (i & (1 << k))
                    sum += S[k];
            }
            if (sum >= 0)
                ans.push_back(pii(sum, i));
            if (j == 0)
                break;
        }
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    return ans;
}
int main()
{
    //ifstream in("subsets.in");
    //ofstream out("subsets.out");
    int N;
    cin >> N;
    vector<int> SL, SR;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        if (i & 1)
            SL.push_back(x);
        else
            SR.push_back(x);
    }
    vector<pii> L = half(SL);
    vector<pii> R = half(SR);
    int p = 0;
    int q = 0;
    int LS = L.size();
    int RS = R.size();
    vector<bool> good(1 << N);
    while (p < LS && q < RS)
    {
        if (L[p].first < R[q].first)
            p++;
        else if (L[p].first > R[q].first)
            q++;
        else
        {
            int p2 = p;
            int q2 = q;
            while (p2 < LS && L[p2].first == L[p].first)
                p2++;
            while (q2 < RS && R[q2].first == R[q].first)
                q2++;
            for (int i = p; i < p2; i++)
                for (int j = q; j < q2; j++)
                {
                    good[L[i].second | (R[j].second << SL.size())] = true;
                }
            p = p2;
            q = q2;
        }
    }
    int ans = count(good.begin() + 1, good.end(), true);
    cout << ans << endl;
}
```

---

## 作者：wmy_goes_to_thu (赞：3)

# 不是折半搜索，是二进制枚举！！！

我是吸氧过的

不会VECTOR的睡觉

不会MAP的睡觉

不会BITSET的勉强看吧

把数组排个序，分成两半

二进制枚举不说了

在一个MAP里记录状态，用VECTOR存

用BITSET判重，BOOL数组也行

然后就A了

代码：压行压行再压行，抄题解会TLE

```cpp
#include<bits/stdc++.h>
using namespace std;
struct apple
{
	int tot;
	vector<int>zt;
	void append(int ztt){zt.push_back(ztt);tot++;}
};
int a[25],n;
map<int,apple>mp;
int dv1[1025],dv2[1025];
bitset<1050000>bs;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	int zb1=n>>1,zb2=n-(n>>1);
	int ans=0;
	for(int i=0;i=(1<<zb1);i++)for(int j=1;j<=zb1;j++)if(i&(1<<j-1))dv1[i]+=a[j];
	for(int i=0;i<(1<<zb1);i++)for(int j=0;j<(1<<zb1);j++)if(!(i&j)&&(i||j)&&dv1[i]>=dv1[j])mp[dv1[i]-dv1[j]].append(i^j);
	apple ppa=mp[0];
	for(int i=0;i<ppa.tot;i++)bs[ppa.zt[i]]=1;
	for(int i=0;i<(1<<zb2);i++)for(int j=1;j<=zb2;j++)if(i&(1<<j-1))dv2[i]+=a[zb1+j];
	for(int i=0;i<(1<<zb2);i++)for(int j=0;j<(1<<zb2);j++)if(!(i&j)&&(i||j)&&dv2[i]==dv2[j])bs[(i^j)<<zb2]=1;
	for(int i=0;i<(1<<zb2);i++)for(int j=0;j<(1<<zb2);j++)if(!(i&j)&&(i||j)&&dv2[i]>=dv2[j])
	{
		int mg=(i^j)<<zb2;
		apple pa=mp[dv2[i]-dv2[j]];
		for(int k=0;k<pa.tot;k++)bs[mg^pa.zt[k]]=1;
	}
	cout<<bs.count();
	return 0;
}
```


---

## 作者：Isprime (赞：2)

题意简述：一个数要么放入集合 $S_1$，要么放入集合 $S_2$，要么两个都不放，求使得集合非空时的$\Sigma_{v\in S_1}v=\Sigma_{u\in S_2}u$ 的方案数。

$n\leq20$ 明示搜索或者状压 dp，但这题爆搜的话 $O(3^{20})$ 的复杂度显然会爆炸，有没有什么办法呢？

考虑折半搜索。将这 $n$ 个数分为两部分，每部分分别爆搜处理，再合并答案。对于这道题，我们就爆搜出两个部分的数可能的和，排序之后双指针答案。

记录答案时有一个很巧妙的想法：对于选入 $S_1$ 的数就在 dfs 传参时传一个 $sum+a[i]$ ，对于选入 $S_2$ 的数就在 dfs 传参时传一个 $sum-a[i]$，最后合并答案时判断两部分是否和为 $0$ 即可。

最后状压一下记录个状态（第 $i$ 位为 $1$ 表示选了，反之没选）就完事了

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
inline int read() {
	int res=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
	return res*f;
}
const int N=25;
int n,ans,sump;
int p[N];
bool vis[10000000];
struct Node {
	int val,status;
	bool operator <(const Node &x) const {
		return val<x.val;
	} 
}a[10000000],b[10000000];
inline bool cmp(Node a,Node b) {return a.val>b.val;}
inline void dfs(int dep,int limit,int sum,int status,Node *t) {
	if(dep>limit) {
		t[++t[0].val].val=sum;
		t[t[0].val].status=status;
		return ;
	}
	dfs(dep+1,limit,sum+p[dep],status+(1<<(dep-1)),t);
	dfs(dep+1,limit,sum-p[dep],status+(1<<(dep-1)),t);
	dfs(dep+1,limit,sum,status,t);
}
signed main() {
	n=read();
	for(int i=1;i<=n;++i)
		sump+=(p[i]=read());
	dfs(1,n/2,0,0,a);
	dfs(n/2+1,n,0,0,b);
	sort(a+1,a+a[0].val+1);
	sort(b+1,b+b[0].val+1,cmp);
	int l=1,r=1;
	while(l<=a[0].val&&r<=b[0].val) {
		while(-a[l].val<b[r].val&&r<=b[0].val) r++;
		int pos=r;
		while(r<=b[0].val&&-a[l].val==b[r].val) {
			if(!vis[a[l].status|b[r].status]) {
				vis[a[l].status|b[r].status]=1;
				ans++;
			}
			r++;
		}
		if(l<a[0].val&&a[l].val==a[l+1].val) r=pos;
		l++;
	}
	printf("%lld",ans-1);
	return 0;
}
```

---

## 作者：FxorG (赞：2)

## 对Ofnoname大佬思路的个人观点


~~个人并没有看懂大佬的文字阐述~~

```cpp
我们设第一次所选的数和为x1，放入另一个集合所失去的数和为y1;同理，设第二次所选的数和为x2,放入另一个集合所失去的数为y2,2个集合最终表示出来的数为num

易得:
x1-y1=num
x2-y2=num

显然
x1+y2=x2+y1

那么这就验证了我们在代码中的dfs放入另一个集合而不会影响答案正确性
```

### 核心代码

```cpp
void dfs1(int l,int r,int sum,int sta) {
	if(l==r+1) {
		if(!book.count(sum)) book[sum]=++cnt;
		t[book[sum]].push_back(sta);
		return;
	}
	dfs1(l+1,r,sum,sta);
	dfs1(l+1,r,sum+a[l],sta|(1<<(l-1)));
	dfs1(l+1,r,sum-a[l],sta|(1<<(l-1)));
}

void dfs2(int l,int r,int sum,int sta) {
	if(l==r+1) {
		if(book.count(sum)) {
			int cur=book[sum];
			for(int i=0;i<t[cur].size();i++) {
				vis[sta|t[cur][i]]=1;
			}
		} 
		return; 
	}
	dfs2(l+1,r,sum,sta);
	dfs2(l+1,r,sum+a[l],sta|(1<<(l-1)));
	dfs2(l+1,r,sum-a[l],sta|(1<<(l-1)));
}
```


---

## 作者：dingshengyang (赞：1)

这题是一个很坑的题。

坑点：只要选的数一样，就只算一种方案。所以我们使用二进制状态压缩。选了：$1$，不选：$0$。

然后每个数都有选择，如下：

1. 啥都不投（`sum` 不变）
1. 投奔左派 (`sum-w[i]`)
1. 投奔右派 (`sum+w[i]`)

没啥好说的，接下来用 `map` 保存答案，干就完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,vis[1<<21];
int a[1001],ans,idx;
map<int,int> m;
vector<int> g[1<<21];
void dfs(int step,int sum,int state){
	if(step >= n/2){
		if(!m.count(sum))m[sum] = ++idx;
		g[m[sum]].push_back(state);
	}else{
		dfs(step+1,sum,state);
		dfs(step+1,sum+a[step],state|(1<<step));
		dfs(step+1,sum-a[step],state|(1<<step));
	}
}
void dfs2(int step,int sum,int state){
	if(step >= n){
		if(m.count(sum)){
			int t = m[sum];
			for(int i = 0;i < g[t].size();i++){
				vis[g[t][i]|state] = 1;
			}
		}
	}else{
		dfs2(step+1,sum,state);
		dfs2(step+1,sum-a[step],state|(1<<step));
		dfs2(step+1,sum+a[step],state|(1<<step));
	}
}
int main(){
	cin >> n;
	for(int i = 0;i < n;i ++)cin >> a[i];
	dfs(0,0,0);
	dfs2(n/2,0,0);
	for(int i = 1;i < (1<<n);i ++){
		if(vis[i]){
			ans ++;
		}
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：OrezTsim (赞：1)

考虑枚举 $3^n$ 种情况，用三进制数表示。

对于每一位，$0$ 表示不放，$1$ 表示放入第一个集合，$2$ 表示放入第二个集合。

这样显然会 TLE。考虑 meet in the middle。

考虑枚举前 $3^{\left\lfloor\frac{n}{2}\right\rfloor}$ 种情况，开一个数组 / map 处理出所有可能的情况。

随后枚举后 $3^{n-\left\lfloor\frac{n}{2}\right\rfloor}$ 种情况，和前面处理出的答案合并。

考虑如何合并。设前半段的第一个集合和为 $a$，第二个集合和为 $b$；后半段的第一个集合为 $a'$，第二个集合和为 $b'$，则有 $a+a'=b+b'$。

移项有 $a-b=b'-a'$，那么只要将答案用差为索引记录即可。

但是我们会发现一个情况，就是第一个集合和第二个集合只是我们规定的顺序，本质上它是无序对；除此之外，你不可以选两个空集。那么答案就是 $\dfrac{ans-1}{2}$ 了吗？

其实不是。

看题目，发现要求选数的方案而非具体的安排方案，例如：

```
3 3 3 3
```

对于这四个数，分段为 `3 3/3 3`，前半段和后半段内共可以组成 $2$ 个合法答案。

你会发现，$a_1+a_2=a_3+a_4$ 本质上和 $a_1+a_3=a_2+a_4$ 是一种选数方案。

考虑在枚举状态时加入选数的状态，用二进制 $0/1$ 来表示。

开一个数组记录是否计算过一种方案的答案即可。

复杂度是 $O(3^{\left\lfloor\frac{n}{2}\right\rfloor}\times2^{\left\lfloor\frac{n}{2}\right\rfloor})$ 即 $O(6^{\left\lfloor\frac{n}{2}\right\rfloor})$ 的。$3$ 为枚举集合分布，$2$ 为记录的选数方案。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1 << 20;
unordered_map <int, int> id; bool kk[N];
int n, idx, a[N]; vector <int> kel[N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> n; for (int i = 1; i <= n; ++i) cin >> a[i];
    int mid = n >> 1, lim = 1, res = 0; for (int i = 1; i <= mid; ++i) lim *= 3;
    for (int s = 0; s < lim; ++s) {
        int tmp = s, sum = 0, sta = 0;
        for (int cnt = 1; cnt <= mid; ++cnt, sta = tmp % 3? (sta << 1 | 1) : (sta << 1), tmp /= 3)
            if ((tmp % 3) & 1) sum += a[cnt]; else if (tmp % 3) sum -= a[cnt];
        if (!id[sum]) id[sum] = ++idx;
        kel[id[sum]].emplace_back(sta);
    }
    int lst = mid; mid = n - mid, lim = 1;
    for (int i = 1; i <= mid; ++i) lim *= 3;
    for (int s = 0; s < lim; ++s) {
        int tmp = s, sum = 0, sta = 0;
        for (int cnt = 1; cnt <= mid; ++cnt, sta = tmp % 3? (sta << 1 | 1) : (sta << 1), tmp /= 3)
            if ((tmp % 3) & 1) sum -= a[cnt + lst]; else if (tmp % 3) sum += a[cnt + lst];
        int curid = id[sum]; if (!curid) continue;
        for (auto dk: kel[curid]) {
            if (!((dk << mid) + sta)) continue;
            if (kk[(dk << mid) | sta]) continue;
            kk[(dk << mid) | sta] = true, ++res;
        }
    }
    cout << res << endl;
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

题意理解上注意无论如何划分，只要集合是一样的就算一种方案，不能瞎写。

直接搜索的状态数量为 $O(3^n)$，就是直接将每一个位置分为不选，放在第一个部分中和放在第二个部分中三种可能情况，同时记录下被取到的数的集合就行了。明显的是，本题中只关心两个部分的差值，直接记录这个差值就行了。

虽然不能直接用搜索通过，但是较少的搜索状态启示我们使用效率更高的折半搜索。也就是将所有的数分成两个部分，分别进行搜索，在最后进行相应的匹配。

进行匹配的时候可以直接记录下所有能达成当前数的位置，虽然这样复杂度会达到相等数的平方级。但是容易得知，这样的最大值出现在全相等的时候，毛估估算一下即使是最大的情况也只有不到 $9000$ 相等的数，吸口氧随便过。



---
### 代码：

```cpp
#include<vector>
#include<cstdio>
#include<map>
using namespace std;
#define int long long
int n,n1,n2,a[50],ans,cnt,rep[2048576];
vector<int> r[60000];
map<int,int>mp;
void dfs1(int now,int num,int p){
	if(now==n1+1){
		if(mp[num]==0)mp[num]=++cnt;
		r[mp[num]].push_back(p);
		return;
	}
	dfs1(now+1,num,p);
	dfs1(now+1,num+a[now],p|(1<<(now-1)));
	dfs1(now+1,num-a[now],p|(1<<(now-1)));
}
void dfs2(int now,int num,int p){
	if(now==n+1){
		int u=mp[-num];
		for(int i=0;i<r[u].size();i++){
			if(rep[p|r[u][i]]==0){
				rep[p|r[u][i]]=1;
				ans++;
			}
		}
		return;
	}
	dfs2(now+1,num,p);
	dfs2(now+1,num+a[now],p|(1<<(now-1)));
	dfs2(now+1,num-a[now],p|(1<<(now-1)));
}
signed main(){
	scanf("%lld",&n);
	n1=n/2;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	dfs1(1,0,0);
	dfs2(n1+1,0,0);
	printf("%lld\n",ans-1);
	return 0;
}
```


---

## 作者：MilkyCoffee (赞：0)

难得遇见一道会的紫题

----

第一眼看到这道题我想的是爆搜（$O(3^N)$），第二眼发现数据范围 $n \le 20$ 当场暴毙。

再看一眼，发现这道题可以折半搜索。

直接按照折半搜索的板子 [P4799](https://www.luogu.com.cn/problem/P4799) 来打。

```cpp
void dfs(int l, int r, long long sum, long long a[], long long &cnt) {
    if (sum > m) return;
    if (l > r) {
        a[++cnt] = sum;
        return;
    }
    dfs(l + 1, r, sum + qwq[l], a, cnt);
    dfs(l + 1, r, sum, a, cnt);
    dfs(l + 1, r, sum - qwq[l], a, cnt);
}
```

可以拿到 $90pts$ 的好成绩。

怎么解决如上问题呢？

结合题意 / 开 O2 即可。

我们只需要在搜索 $[1, mid]$ 的时候记录可以拼接出当前组合的的状态，然后在搜索 $[mid + 1, n]$ 的时候求出一个结果 $sum$ 的时候，我们需要找到在 $[1, mid]$ 里面可以求出同样的结果 $sum$ 的方案数量，这时只需要调用储存的状态，并且记录所有的在 $[1, mid]$ 里结果为 $sum$ 的状态加上当前（$[mid + 1, n]$）的状态，最后求和就可以了。

需要注意相同的状态只有一个，不能累加。

---

