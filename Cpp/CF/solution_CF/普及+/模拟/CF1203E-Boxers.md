# Boxers

## 题目描述

有$n$个拳击手，第$i$个拳击手的重量是$a_i$。 他们每个人都可以在比赛前将体重改变不超过1（体重不能等于零，也就是说，它必须保持正值）。，重量始终是整数。  
你需要根据人数选择最大的拳击队，使得团队中每名拳击手的重量都是唯一的。  
编写一个程序，对于给定的重量$a_i$，找出团队中最大可能的拳击手数量。经过一些改变后，所有拳击手的重量不超过150001。

## 样例 #1

### 输入

```
4
3 2 4 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6
1 1 1 4 4 4
```

### 输出

```
5
```

# 题解

## 作者：w1049 (赞：4)

题意：选出最多的拳击手，使他们的体重两两不相同（拳击手的体重可以+1或-1）

首先可以看出体重有重复，所以使用桶记录一下每种体重各有多少人

显而易见的策略是，尽量让每个体重都有人

所以从1到体重最大值枚举体重，如果该体重有人则答案+1

注意优先使用体重小1的，再使用体重正好的，再使用体重大1的

因为体重大的可以为下一个位置做出贡献
```
#include <cstdio>
int cnt[150010];
int n, ans, mx;
int main() {
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), cnt[x]++, mx < x ? mx = x : 0;
    for (int i = 1; i <= mx + 1; i++) {
        if (cnt[i - 1])
            cnt[i - 1]--, ans++;
        else if (cnt[i])
            cnt[i]--, ans++;
        else if (cnt[i + 1])
            cnt[i + 1]--, ans++;
    }
    printf("%d", ans);
}
```

---

## 作者：Mr_Wu (赞：3)

左边放 $150000$ 个点，右边放 $150001$ 个点。

对每个数 $u$，从左 $u$ 分别连右 $u-1,u,u+1$ （$u=1$ 时特判）然后跑二分图。

但是数可能会重复。怎么办呢？

建一个源点 $S$，若 $u$ 在序列中出现的次数为 $t$，将 $S$ 向左 $u$ 连容量为 $t$ 的边。把右边的所有点都向 $T$ 连容量为 $1$ 的边即可。然后跑最大流。

由于这个图比较好看，所以它能过。

```cpp
#include <cstdio>
#include <queue>
using namespace std;
 
typedef long long ll;
 
inline ll read()
{
    char c = getchar();
    ll ret = 0, t = 1;
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') t = -1, c = getchar();
    while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret * t;
}
 
const int MAXN = 450005, INF = 2147483647;
struct node
{
    int u, v, flow, next;
} E[MAXN << 2]; int Elen = 1, head[MAXN];
void add(int u, int v, int flow) { ++Elen, E[Elen].u = u, E[Elen].v = v, E[Elen].next = head[u], head[u] = Elen, E[Elen].flow = flow; }
void ADD(int u, int v, int flow) { /*printf("add(%d,%d,%d)\n",u,v,flow);*/ add(u, v, flow), add(v, u, 0); }
 
int S, T, dis[MAXN], cur[MAXN];
queue<int> Q;
bool bfs()
{
    int i, u; for (i = 1; i <= T; ++i) dis[i] = 0; dis[S] = 1; while (!Q.empty()) Q.pop(); Q.push(S);
    while (!Q.empty())
    {
        u = Q.front(), Q.pop();
        for (i = head[u]; i; i = E[i].next) if (E[i].flow && !dis[E[i].v]) dis[E[i].v] = dis[u] + 1, Q.push(E[i].v);
    }
    return (bool)dis[T];
}
ll dfs(int u, ll lim)
{
    if (u == T || !lim) return lim;
    int i; ll flow = 0, d;
    for (i = cur[u]; i; i = E[i].next)
    {
        cur[u] = i;
        if (dis[E[i].v] != dis[u] + 1) continue;
        d = dfs(E[i].v, min(lim, E[i].flow));
        if (d)
        {
            E[i].flow -= d, E[i ^ 1].flow += d, lim -= d, flow += d;
            if (!lim) break;
        }
    }
    return flow;
}
ll dinic()
{
    ll ans = 0; int i;
    while (bfs())
    {
        for (i = 1; i <= T; ++i) cur[i] = head[i];
        ans += dfs(S, INF);
    }
    return ans;
}
 
int N, cnt[MAXN];
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif
    N = read(); int i, x;
    for (i = 1; i <= N; ++i)
    {
        x = read(), ++cnt[x];
        if (x > 1) ADD(x, x - 1 + 150001, 1);
        ADD(x, x + 1 + 150001, 1), ADD(x, x + 150001, 1);
    }
    S = 2 * 150001 + 1, T = 2 * 150001 + 2;
    for (i = 1; i <= 150001; ++i)
    {
        if (cnt[i]) ADD(S, i, cnt[i]);
        ADD(i + 150001, T, 1);
    }
    printf("%d", dinic());
    return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：2)

### 题意

- 给定长度为 $n$ 的序列 $a$，对于 $a_i$，可对其之多进行一次操作。
- 定义 $a_i\gets a_i+1$ 或 $a_i\gets a_i-1$ 为一次操作。需要注意，$a_i$ 不能为 $0$。
- 求最多可以选出几个 $a_i$，使她们各不相等。
- $1\le n\le 150000,1\le a_i\le 150000$


### 解法

Greedy.

我们开一个桶记录 $a_i$ 的出现次数，然后从 $1$ 扫到 $150000$。对于一个不等于 $1$ 的 $i$，假设其出现次数为 $1$。我们显然可以有三种转换：$i-1,i,i+1$。

那么很显然转换成最小的 $i-1$ 一定不会更优，因为后面一个数 $i+1$ 如果有多个，就可以有一个被转换成 $i$。


但是 what if  $i$ 的个数不为 $1$ 了，怎么转化呢？

事实上， $i$ 转化成 $i+1$，和 $i+1$ 转化成 $i$ 的效果（对最终答案的贡献）是一样的，那么我们就可以先把 $i$ 尽可能全转换掉，再考虑对 $i+1$ 操作。

尽可能讲的很明白了，不懂的话康康代码吧。

### 代码

```cpp
//实现的有点麻烦了 qwq
#include<bits/stdc++.h>
using namespace std;
int n,ans,mx=-2e9;
bool used[200005];
int a[200005];
int num[200005];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)	a[i]=read(),num[a[i]]++,mx=max(mx,a[i]);
	if(num[1]==1)	used[1]=true,ans++;
	if(num[1]>=2)	used[1]=true,used[2]=true,ans++,ans++;
	for(int i=2;i<=200000;i++)
	{
		if(!num[i])	continue;
		if(num[i]&&!used[i-1])	used[i-1]=true,ans++,num[i]--;
		if(num[i]&&!used[i])	used[i]=true,ans++,num[i]--;
		if(num[i]&&!used[i+1])	used[i+1]=true,ans++,num[i]--;
	}
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：远辰 (赞：1)

[蒟蒻的blog](https://www.cnblogs.com/cmath-po8/p/11355004.html)

# 作者水平低怕被喷
//如果英语基础好的话建议自己看英文题面

(像我这种身在外语学校外语却很渣的就算了，Google翻译不错)，这样既学了OI，英语也有所复习（雾）；


------------

题目大意（）：给定n个拳击手的重量值ai，每个拳击手可更改自己重量值的范围是1(即可以-1，+0，+1)，现在需要你选择一支拳击队，队伍中人数尽量多，而且重量不可以重复，求最多人数


------------

如果是放在平时刷题的话这道题我是上来硬钢，不看数据范围，也不顾及空间限制，WA到起飞，我认为现在应该注意正确率和效率了

应该是不用开long long的，毕竟max_ai才150000，自然想到这题应该没太多求和骚操作；

空间也比较正常吧；

思路：要尽可能选的人多，表面上看起来很复杂，但代码短的一批，还很好理解；
为了让人尽量多，输入的重量顺序显然没有影响，那就先sort排下序(后面的应该是排序原因，基操)。

以下给出两种做法，思想基本一致，在[Kendrick_Z](https://www.luogu.org/space/show?uid=142373)大佬的点拨下我两种做法都AC了:

①从大到小枚举重量（注意以下重量都排过序），再一层循环内枚举+1，0，-1，这样做是为了让前面较大值对最大个数选取影响尽可能小，累计最前面的改变过的数，注意判断大于0！！！！；

②从小到大，循环内枚举-1，0，+1，原理和①xiangsi;

1
```cpp
/*
writer:qiyujun&&cmathpo8&&yuanchen;
date:2019/8/14 11:00;
*/
 
#include<bits/stdc++.h>
#define re register
#define il inline
typedef long long ll;
 
using namespace std;
 
inline int readINT()//快读
{
    register int x = 0, ch = getchar(), f = 1;
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
int n,sum=999999999,ans=0;//sum作为累计的判断值
//ans是记录答案
int h[150011]; //h[]作为储存重量数组
 
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=readINT();
    for(re int i=1;i<=n;i++){
    h[i]=readINT();
    }
    sort(h+1,h+1+n);//重量排序
    for(re int i=n;i>=1;i--){
        for(re int j=1;j>=-1;j--){
            if(h[i]+j<sum&&h[i]+j>0){
                sum=h[i]+j;ans++;
                break;
            }    //从大到小
        }
    }
    printf("%d",ans);
    return 0;
}
//注意这份代码是从大到小枚举，注意判断大于0
//累计后注意break；
```

2
```cpp
/*
writer:qiyujun&&cmathpo8&&yuanchen;
date:2019/8/14 11:00;
*/
 
#include<bits/stdc++.h>
#define re register
#define il inline
typedef long long ll;
 
using namespace std;
 
inline int readINT()
{
    register int x = 0, ch = getchar(), f = 1;
    while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return x * f;
}
int n,sum=0,ans=0;//sum作为累计的判断值
int h[150011]; 
 
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n=readINT();
    for(re int i=1;i<=n;i++){
    h[i]=readINT();
    }
    sort(h+1,h+1+n);
    for(re int i=1;i<=n;i++){
        for(re int j=-1;j<=1;j++){
            if(sum<h[i]+j){
                sum=h[i]+j,ans++;
                break;
            }    
        }
    }
    printf("%d",ans);
    return 0;
    //这份是从小到大枚举，一定是大于sum值
}
```
谢谢观看啊，轻喷，若果有错请尽快指正，有好的方法也欢迎分享啊！！！

---

## 作者：BADFIVE (赞：0)

**题意:** 给定一个长度为 $n$ 的序列 $a$ ,可以对 $a_i$ 进行加减的操作，最多可以选定几个 $a_i$ 组成一个新的序列，且新序列中每个元素必须是唯一的   
**思路:** 先对数组元素进行排序，对于 $1$ 元素进行特判，因为 $0$ 元素无效，先判断 $1$ 本身是否出现，若没则标记 $1$ ，否则标记为 $2$ ，当然可以不采取特判，对于其他元素，利用贪心思路，先向左边扩展，再考虑元素本身，最后考虑向右扩展，尽量先做 $-1$ 的操作  

需要注意的地方是，数组大小一定要符合数据范围  
$codes:$
```
#include<bits/stdc++.h>
using namespace std;
int arr[500001],a[500001];
int main(){
	int n,ans=0;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){ 
        if(a[i]>1&&arr[a[i]-1]==0)arr[a[i]-1]=1,ans++;
        else if(arr[a[i]]==0)arr[a[i]]=1,ans++;
        else if(a[i]<500001&&arr[a[i]+1]==0)arr[a[i]+1]=1,ans++;
    }
    cout<<ans;
}
```

---

## 作者：Fan_Tuan (赞：0)

# 题意
给定一个长度为$n$的序列$a$, $a_i\in[1,150001]$。对于任意$a_i$, 你可以进行加一或减一的操作， 询问，你最多可以选定几个$a_i$组成一个新的序列， 使得新序列中每个元素的是唯一的。

# 思路
将序列$a$进行排序， 用一个$vis$ 数组进行标记哪个值已经被使用， 显然对于排完序的$a$来说， $a_i$考虑占哪种值的顺序应该先为$vis_{a_i-1}$, 再为$vis_{ai}$, 最后为$vis_{ai + 1}$。
# 代码
```
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <queue>
// #define d lld
// #define int long long
using namespace std;

const int maxn = 150051;
int n, m, p, k, vis[maxn], a[maxn];

signed main () {
    scanf ("%d", &n);
    int ans = 0;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort (a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++) { 
        if (a[i] > 1 && vis[a[i] - 1] == 0) vis[a[i] - 1] = 1, ans++;
        else if (vis[a[i]] == 0) vis[a[i]] = 1, ans++;
        else if (a[i] < 150001 && vis[a[i] + 1] == 0) vis[a[i] + 1] = 1, ans++;
    }
    printf ("%d", ans);
    return 0;
}
```


---

## 作者：Star_Wind (赞：0)

签到提啊。。。

把体重排序之后，优先判断-1kg能不能参加比赛，再判断改变0和1体重能不能参赛。

接下来~~毒瘤模拟~~一波

AC抱回家~~~~

代码

```cpp
#include<>
using namespace std;
const int maxn = ？？？？？;
int box[maxn],a[maxn];
int main()
{
	int n,ans = 0;
	memset(box,0,sizeof(box));
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort(a,a+n);
	for(int i=0;i<n;i++)
	{
		if(a[i] != 1)
		{
			if(box[a[i]-1]==0)
			{
				box[a[i]-1]++;
				ans++;
			}
			else if(box[a[i]]==0)
			{
				box[a[i]]++;
				ans++;
			}
			else if(box[a[i]+1]==0)
			{
				box[a[i]+1]++;
				ans++;
			}
		}
		else
		{
			if(box[a[i]]==0)
			{
				box[a[i]]++;
				ans++;
			}
			else if(box[a[i]+1]==0)
			{
				box[a[i]+1]++;
				ans++;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：学委 (赞：0)

有一种贪心做法，让小的重量尽可能小，以给后面的重量腾出空间。

考虑排序后，最小的点减小1只可能更优，那么第二小的点减小1也只可能更优。

```cpp
#include <cstdio>
#include <algorithm>
using std::sort;
 
const int N = 2e5 + 10;
 
int n, a[N], ans = 0;
int used[N];
 
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i) {
    if (a[i] != 1 and not used[a[i] - 1])
      used[a[i] - 1] = 1, ++ans;
    else if (not used[a[i]])
      used[a[i]] = 1, ++ans;
    else if (not used[a[i] + 1])
      used[a[i] + 1] = 1, ++ans;
  }
  printf("%d\n", ans);
  return 0;
}
```

---

