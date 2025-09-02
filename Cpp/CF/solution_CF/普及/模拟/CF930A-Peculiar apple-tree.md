# Peculiar apple-tree

## 题目描述

In Arcady's garden there grows a peculiar apple-tree that fruits one time per year. Its peculiarity can be explained in following way: there are $ n $ inflorescences, numbered from $ 1 $ to $ n $ . Inflorescence number $ 1 $ is situated near base of tree and any other inflorescence with number $ i $ ( $ i&gt;1 $ ) is situated at the top of branch, which bottom is $ p_{i} $ -th inflorescence and $ p_{i}&lt;i $ .

Once tree starts fruiting, there appears exactly one apple in each inflorescence. The same moment as apples appear, they start to roll down along branches to the very base of tree. Each second all apples, except ones in first inflorescence simultaneously roll down one branch closer to tree base, e.g. apple in $ a $ -th inflorescence gets to $ p_{a} $ -th inflorescence. Apples that end up in first inflorescence are gathered by Arcady in exactly the same moment. Second peculiarity of this tree is that once two apples are in same inflorescence they annihilate. This happens with each pair of apples, e.g. if there are $ 5 $ apples in same inflorescence in same time, only one will not be annihilated and if there are $ 8 $ apples, all apples will be annihilated. Thus, there can be no more than one apple in each inflorescence in each moment of time.

Help Arcady with counting number of apples he will be able to collect from first inflorescence during one harvest.

## 说明/提示

In first example Arcady will be able to collect only one apple, initially situated in $ 1 $ st inflorescence. In next second apples from $ 2 $ nd and $ 3 $ rd inflorescences will roll down and annihilate, and Arcady won't be able to collect them.

In the second example Arcady will be able to collect 3 apples. First one is one initially situated in first inflorescence. In a second apple from $ 2 $ nd inflorescence will roll down to $ 1 $ st (Arcady will collect it) and apples from $ 3 $ rd, $ 4 $ th, $ 5 $ th inflorescences will roll down to $ 2 $ nd. Two of them will annihilate and one not annihilated will roll down from $ 2 $ -nd inflorescence to $ 1 $ st one in the next second and Arcady will collect it.

## 样例 #1

### 输入

```
3
1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
1 2 2 2
```

### 输出

```
3
```

## 样例 #3

### 输入

```
18
1 1 1 4 4 3 2 2 2 10 8 9 9 9 10 10 4
```

### 输出

```
4
```

# 题解

## 作者：installb (赞：7)

对于这种题目  
我们需要把题目给的难以理解的条件给转化  

**题意:**  
有根树 1号点是根
一开始树上每一个节点都有一个苹果 每一个苹果每秒会跑到他的父亲节点  
在苹果移动完后如果某节点有多于一个苹果 苹果会**两两**碰撞消失  
然后苹果继续移动(回到上一句)
如果一个苹果在某一秒在1号点 下一秒它会~~被神鱼吃掉~~被收集  
问能收集几个  

题目说了那么多 说白了就是两个苹果会**在它们所在两个节点LCA的位置**碰撞消失  
下一步 我们发现如果让这两个苹果**从LCA滚落到1号**再碰撞消失 对答案完全**没有影响**  
再下一步 所在节点**深度(到根节点的距离)**相同的所有苹果都会在同一时刻到1号节点  

所以只要统计每个深度有多少个苹果就行了  
偶数个答案+0 奇数个答案+1  

行了 上代码吧  
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
using namespace std;
typedef long long LL;

LL n,ans = 0;
LL f[500005] = {0};
LL dep[500005] = {0}; // dep[i]:i号点深度
LL cnt[500005] = {0}; // cnt[i]:有多少个点深度为i
 
int main(){
	cin >> n;
	cnt[1] = 1; dep[1] = 1; // 先给1号店弄个深度 再把1号点计算上
	for(LL i = 2;i <= n;i ++){
		cin >> f[i];
		dep[i] = dep[f[i]] + 1; // 儿子深度为父亲深度+1
		cnt[dep[i]] ++;
	}
	for(LL i = 1;i <= n;i ++) if(cnt[i] & 1) ans ++;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Symbolize (赞：1)

# $\tt{Solution}$
首先，不难发现任意一个深度为 $x$ 的节点，如果不被融合，它将会在 $x$ 时 被吃掉。又因为 $(a+b)\bmod p=(a\bmod p+b\bmod p)\bmod p$，所以就可以先处理出来深度为 $x$ 的数量，然后再分别对 $s_i$ 取模，又由于模数为 $2$，所以可以在记录时采用异或运算。

```cpp
/*
    Luogu name: Symbolize
    Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=1e6+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,h[N],e[N],ne[N],idx,ans,dep[N]/*记录深度*/;
bool a[N];//因为只有01，所以可以用bool
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return f*x;
}
void add(int x,int y)
{
    e[idx]=y;
    ne[idx]=h[x];
    h[x]=idx++;
    return;
}
void dfs(int x,int fa)
{
    dep[x]=dep[fa]+1;//记录深度
    a[dep[x]]^=1;//模2的值
    rep3(i,h,x,ne)
    {
        int to=e[i];
        if(to==fa) continue;//不能等于走回去
        dfs(to,x);
    }
    return;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    memset(h,-1,sizeof h);
    n=read();
    rep1(i,2,n)
    {
        int fa=read();
        add(fa,i);
        add(i,fa);
    }
    dfs(1,0);
    rep1(i,1,n) ans+=a[i];//累加答案
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

对于一个深度为 $i$ 的节点，在不被融合的情况下，它将会在时间 $i$ 被吃掉。

这里有一个性质，$(x+y)\bmod z =(x \bmod z+y\bmod z) \bmod z$。所以我们可以将所有深度为 $i$ 的点的数量统计出来，最后在时间 $i$ 能被吃掉的苹果数量就是其对于 $2$ 取模的结果。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline

const int N=2e5+10;
int n,dep[N],s[N],ans;
int ne[N],e[N],h[N],idx;

il void add(int a,int b){ne[++idx]=h[a],e[idx]=b,h[a]=idx;}
il void dfs(int now,int fa){
	dep[now]=dep[fa]+1,s[dep[now]]^=1;
	for(re int i=h[now];i;i=ne[i]){
		int j=e[i];if(j==fa) continue;
		dfs(j,now);
	}
}

il void solve(){
	cin>>n;
	for(re int i=2,x;i<=n;++i) cin>>x,add(i,x),add(x,i);
	dfs(1,0);
	for(re int i=1;i<=n;++i) ans+=s[i];
	cout<<ans;
}

signed main(){
	solve();
}
```


---

## 作者：_cpp (赞：0)

### 1. 思路：
本题只是题意较为难以理解。由题得，对于同一根节点下的兄弟节点（父节点上的苹果），统计它们的个数，如果为偶数，那就全部两两抵消；为奇数，答案就加一。所以对于每一个节点，它的深度都为父节点的深度加一（根节点的深度为一）。再将同一深度的兄弟节点统计。

### 2. 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,ans,x,a[100010],sum[100010];
int main()
{
	scanf("%d",&n);
	cnt[1] = 1;
    a[1] = 1; //初始化根节点
	for(int i = 2;i <= n;i++){
		scanf("%d",&x);
		a[i] = a[x] + 1; //深度为父节点加一
		sum[a[i]]++; //统计
	}
	for(int i = 1;i <= n;i ++) ans += cnt[i] % 2; //累加
	cout << ans;
	return 0;
}
```

---

## 作者：Rosemary_dream (赞：0)

## [CF930A Peculiar apple-tree](https://www.luogu.com.cn/problem/CF930A)

此题的关键在于“延迟”。

看下图

![](https://cdn.luogu.com.cn/upload/image_hosting/0almzaim.png)

对于此图来说，第三深度的苹果在掉到第二深度后只剩一个，第二深度的苹果掉到根时不会被消除。共计吃到两个。

那么我们就明显的发现了两条性质。

>1. 苹果的掉落可以放在根处处理，因为所有苹果同步，不会有不同 $\operatorname{LCA}$ 的苹果在互相影响。

对于性质 $1$ 的第一句： **苹果的掉落可以放在根处处理** 。我们可以将其优化为性质 $2$ （见下）的第一句

>2. $N$ 个 $\operatorname{LCA}$ 苹果直接计数模二即可，因为同深度的苹果一定会在根处全部汇集（一棵树只有一个根）。

总结一下，即为 **不同 $\operatorname{LCA}$ 的苹果无法互相干涉，同 $\operatorname{LCA}$ 苹果视为一个个体**

那么将这一条性质应用于代码，只需要计算每个拥有相同公共祖先的苹果个数，模二，统计所有结果即为答案。

又见下图

![](https://cdn.luogu.com.cn/upload/image_hosting/o7vxq6o7.png)

将所有 dep 相等的层级视为一个个体。即：对于 dep4 来说，四模二等于零；对于 dep3 来说，三模二等于一；对于 dep2 来说，一模二等于一。共计可以拿到两个苹果。~~（他们的祖先不都是 dep2 吗）~~

$\large Code:$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define maxn 100001
using namespace std;
ll sum[maxn],ans=1;
ll n,a,dep[maxn];
int main(){
	scanf("%lld",&n);
	for(int i=2;i<=n;i++){
	    scanf("%lld",&a);
	    dep[i]=dep[a]+1;//指向它的父节点
	    sum[dep[i]]++;//累计
	}
	for(int i=1;i<=n;i++) ans+=(sum[i]&1);//&1等价于%2
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：Noby_Glds (赞：0)

对于这道题，我们需要“拖延”。
### 思路：
先看一张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/t3snjscn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)


可以发现，位于节点 $3$ 和节点 $4$ 的苹果会在节点 $2$ 消除。

如果节点 $2$ 偷懒，放这两个苹果到根节点，也会**在根节点**被消除。

所以我们不妨偷个懒，让一堆苹果滚到根节点再进行消除。

很容易可以发现，同一深度的苹果会同时滚到根节点，然后进行消除。
	
记录深度为 $i$ 的节点有多少个，那么这个深度的一堆节点对答案所做的贡献就是**节点个数除以 $2$ 的余数**。

统计所有深度，这题就完结了。
### 代码：
```cpp
#include<bits/stdc++.h>
#define N 100010
using namespace std;
int n,a,dep[N],sum[N],ans=1;
int main(){
	cin>>n;
	for(int i=2;i<=n;i++) cin>>a,dep[i]=dep[a]+1,sum[dep[i]]^=1;
	for(int i=1;i<=n;i++) ans+=sum[i];
	cout<<ans;
	return 0;
}
```


---

## 作者：极寒神冰 (赞：0)

这题的关键在于我们可以假设在非根节点上不会消失，而是全部在根节点上消失。

这个假设显然是正确的，因为在$t$时刻苹果的数量只取决于$t$时刻到达根节点苹果数量的奇偶性。

所以我们可以计算$cnt_t$，表示在$t$时刻(即深度为$t$)到达根的苹果数量，这可以使用$BFS$和$DFS$实现。

统计$0$~$n$所有$cnt_t\bmod 2=1$即可

---

