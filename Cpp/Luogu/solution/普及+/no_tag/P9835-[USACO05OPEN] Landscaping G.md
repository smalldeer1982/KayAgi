# [USACO05OPEN] Landscaping G

## 题目描述

农夫约翰正在做一次艰难的转型，从养山羊改成养奶牛，他的农场，由于是为养山羊而设计的所以有太多的山，为了养牛就必须将它整平。但是，将山整平是件很花钱的工作，所以他要移走尽可能少的土。

由于农场很细长，所以可以用一个 $n$ 和 $n$ 个整数（范围 $[1,10^6]$）组成的二维的数组来表示，如：

```
1 2 3 3 3 2 1 3 2 2 1 2
```

上述农场的侧面图是这样的：

```
    * * *     *
  * * * * *   * * *   *
* * * * * * * * * * * *
1 2 3 3 3 2 1 3 2 2 1 2
```

一个或是一些连续等高的地面，如果它左边与右边的海拔都比它低的话，就被称为山顶，上面的例子就有三个山顶。 确定如果要使地图上仅有 $k$ 个山顶，至少要移走多少体积的土（每块地面减少一单位海拔需移走一单位的土）。注意，地面的海拔只能被降低不能被升高。 对于例子，如果要减少到只有 $1$ 个山顶，这需要移走 $2+1+1+1=5$ 个单位的土（`-` 表示移走的土）：

```
    * * *     -
  * * * * *   - - -   -
* * * * * * * * * * * *
1 2 3 3 3 2 1 3 2 2 1 2
```

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^3$，$1 \leq k \leq 25$。

## 样例 #1

### 输入

```
12 1
1
2
3
3
3
2
1
3
2
2
1
2
```

### 输出

```
5```

# 题解

## 作者：Mydeimos (赞：3)

### 1. 思维 + 树形 dp 题。

### 2. 题意：

左边为单调不下降，右边为单调不上升的部分为山顶，可以任意移走土块，但显然是一个一个山顶去移走，求最多留下 $k$ 个山顶时的最小移走土数。

---

### 3. 思路：

提供一种加强版 $n$ 为 $10^5$ 也能过的方法。

时间复杂度为 $O( n \times k^2 )$。

做法不难，但细节较多。
先将山分为多块，也是矩阵，划分方法如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/efzm668n.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/8tenn0kp.png)

即将一个山顶划分为不同层的矩阵，

然后对矩阵建立从属关系，及左右边界是否包含。

下图黑字为编号，蓝字为块大小。

![](https://cdn.luogu.com.cn/upload/image_hosting/2w4a7689.png)

再利用块大小做一个树形 dp，具体转移如下，有具体解释。

---

### 4. 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100005
#define M 26
#define inf 1000000000000007
ll n,m,u,v,ans=inf,f[N][M],p; 
ll a[N],b[N],cnt;
ll q[N],qq[N],cnt1=1;
ll t[N],cnt2;
//f[i][j]为编号为i的块及其子树内 有j个山顶的 最小移走土数 
//a为该块大小  b为该块最左点下标  cnt为对应的块数
//q，qq为队列  cnt1为对应队内数  q为高度，是单调序列  qq为对应的最左点 
//t为可能为从属块队列，单调递增，且无包含关系  cnt2为对应队内数  
vector<ll>s[N];//记录块从属关系 
void dfs(ll x,ll y) {//树形dp 
	if(!s[x].size()) f[x][1]=0;//若x为叶子结点，则其自身为山顶 
	for(auto i:s[x]) if(i!=y) {
			dfs(i,x);
			a[x]+=a[i];//算x子树大小 
			for(ll j=m; j>=0; j--) {//按从大到小，先更新留下山顶多的 
				for(ll k=m-j; k>=1; k--) f[x][j+k]=min(f[x][j+k],f[x][j]+f[i][k]);//i的山顶移走k个，x内共j+k个山顶 
				f[x][j]+=f[i][0];//i的山顶全部移走 
			}
		}
	f[x][0]=a[x];//x全移走 
	return;
}
int main() {
	scanf("%lld%lld%lld",&n,&m,&u);
	q[cnt1]=u;
	qq[cnt1]=1;
	for(ll i=2; i<=n; i++) {
		scanf("%lld",&u),p=i;
		while(1) {
			if(q[cnt1]<=u) break;//山顶左侧必为单调不下降增
			p=qq[cnt1];
			v=q[cnt1]-u;
			if(cnt1>1) v=min(v,q[cnt1]-q[cnt1-1]);
			++cnt;
			a[cnt]=v*(i-qq[cnt1]);//计算块大小 
			b[cnt]=qq[cnt1];//块的最左点 
			while(cnt2&&b[cnt]<=b[t[cnt2]]) s[cnt].push_back(t[cnt2]),cnt2--;// 连接从属块，记得删掉被连了的 
			++cnt2;
			t[cnt2]=cnt;
			cnt1--;
		}
		if(q[cnt1]<u) ++cnt1,q[cnt1]=u,qq[cnt1]=p;//同高度不必多加入队列，因为前面的更左 
	}
	u=q[cnt1];
	while(cnt1) {//同上可得 
		++cnt;
		a[cnt]=(n+1-qq[cnt1])*(u-q[cnt1-1]);
		b[cnt]=qq[cnt1];
		u=q[cnt1-1];//更新高度 
		while(cnt2&&b[cnt]<=b[t[cnt2]]) s[cnt].push_back(t[cnt2]),cnt2--;
		++cnt2;
		t[cnt2]=cnt;
		cnt1--;
	}
	for(ll i=1; i<=cnt; i++) for(ll j=1; j<=m; j++) f[i][j]=inf;//初始化，j必须从1开始 
	dfs(cnt,0);
	for(ll i=1; i<=m; i++) ans=min(ans,f[cnt][i]);//不一定有m个山顶 
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：exLucas (赞：1)

我们先看一下题目样例，有这么一个部分：
```
    * * *     *
  * * * * *   * * *   *
* * * * * * * * * * * *
1 2 3 3 3 2 1 3 2 2 1 2
```
再看一下它给的删除方法：

```
    * * *     -
  * * * * *   - - -   -
* * * * * * * * * * * *
1 2 3 3 3 2 1 3 2 2 1 2
```

像不像拿着一根线从高往低扫掉最小的“山峰”？也就是说只要能够在知道该“山峰”峰顶时就知道它的大小，那么就贪心的把当前这个线扫到的最小“山峰”削掉就行。

But，有可能是我菜了，我不知道怎么在知道该“山峰”峰顶时就知道它的大小。所以这个复杂度有可能接近与 K 同阶的算法就交给读者了（~~虽然我也不知道它的正确性如何证明或证伪，但是读者自证不难~~）。

我们把图倒过来看一下：

```
1 2 3 3 3 2 1 3 2 2 1 2
* * * * * * * * * * * *
  * * * * *   * * *   *
    * * *     *
```

是不是很像一棵树？第 0 行为根节点，向下是区间状的子节点（~~有点线段树的感觉~~）。

所以问题就从把 $n - k$ 座山峰削平的最少花费转化成了保留 $k$ 个子树的最大权值。

显然子树的权值就是子树的大小，所以问题很明显为一个树形DP，转移方程为：
设 $dp_{u, i}$ 表示以 $u$ 为根，剩余叶子数量不大于于 $i$ 的最大权值和， $sum$ 为整棵树的权值和，则有：

$$
dp_{u, i} = \max_{j}^{i - 1} dp_{v, j} + dp_{u, i - j} \\
result = sum - f_{1, k}
$$

但是怎么建树呢？

注意到一个平面 $S$ 的父节点平面 $F$ 应当有：
$$
F_l \leq S_l \leq S_r \leq F_r
$$
所以用两次单调栈即可求出一个区间的父区间。

时间复杂度：
$O(nk^2)$

Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, K = 30;
int n, k, h[N], pt[N], ct, idx[N], stk[N], top;
int head[N], cnt, pre[N], nxt[N];
int sz[N], f[N][K], sum;
struct edge {
    int to, nxt;
} e[N];
void dfs(int u) {
	sum += sz[u];
    for(int i = 0; i <= k; i ++) f[u][i] = sz[u];
	for(int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
		dfs(v);
		for(int j = k; j >= 1; j --) {
            for(int k = j - 1; k >= 0; k --) {
				f[u][j] = max(f[u][j], f[v][j - k] + f[u][k]);   
            }
        }
	}
}
bool cmp(int a, int b) {
    return h[a] < h[b] || (h[a] == h[b] && a < b);
}
int main() {
    scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i ++) scanf("%d", &h[i]);
    for(int i = 1; i <= n; i ++) idx[i] = i;
	sort(idx + 1, idx + n + 1, cmp);
    top = 1;
    stk[top] = 0;
    for(int i = 1; i <= n; i ++) {
		while(top >= 1 && h[stk[top]] > h[i]) -- top;
		pre[i] = stk[top], stk[++ top] = i;
	}
    top = 1;
    stk[top] = n + 1;
    for(int i = n; i >= 1; i --) {
		while(top >= 1 && h[stk[top]] >= h[i]) -- top;
		nxt[i] = stk[top], stk[++ top] = i;
	}
    for(int j = 1; j <= n; j ++) {
        int i = idx[j];
        int u = nxt[i];
        if(h[pre[i]] >= h[nxt[i]]) u = pre[i];
		if(h[pre[i]] == h[i]) {
            pt[i] = pt[pre[i]];
            continue;
        }
        ct ++;
        pt[i] = ct;
		sz[pt[i]] = (nxt[i] - pre[i] - 1) * (h[i] - h[u]);

		e[++ cnt].to = ct;
        e[cnt].nxt = head[pt[u]];
        head[pt[u]] = cnt;
	}
    dfs(1);
    printf("%d", sum - f[1][k]);
    return 0;
}
```

---

## 作者：wanganze (赞：1)

### 题意
给你一个地图，让你将山峰调整到 $k$ 个。

### 思路
贪心。

我们先计算已有的山峰个数，再寻找体积最小的山挖掉，然后更新状态。

可以用一个结构体来存储山。为了方便计算可以写 `calc` 函数计算体积。

### 实现

**千万不要像我一样没有判不用砍的情况。**

关于峰可以用上下边界判断。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1010;
struct hill
{
	int l,r,h,v;
}a[N];
int n,k,h[N],cnt,res;
bool st[N];
void calc(int l,int r,int p)
{
	a[p] = {l,r,max(h[l],h[r]),0};
	for(int i = l; i <= r; i ++)
		if(h[i] > a[p].h) a[p].v += h[i] - a[p].h;
}
void get_h(int p)
{
	int l = a[p].l,r = a[p].r;
	while(l >= 1 && h[l - 1] <= h[l]) l --;
	while(r <= n && h[r + 1] <= h[r]) r ++;
	calc(l,r,p);
}
int main()
{
	cin>>n>>k;
	for(int i = 1; i <= n; i ++) cin>>h[i];
	for(int i = 1; i <= n; i ++)
		if(!st[i])
		{
			st[i] = 1;
			int l = i,r = i;
			bool fl = 0,fr = 0;
			while(l >= 1 && h[l - 1] <= h[l]) l --,st[l] = 1,fl |= (h[l] < h[i]);
			while(r <= n && h[r + 1] <= h[r]) r ++,st[r] = 1,fr |= (h[r] < h[i]);
			if(fl && fr) calc(l,r,++ cnt);
		}
	int hs = cnt;
	memset(st,0,sizeof st);
	while(hs > k)
	{
		int minv = 2e9,p = 0;
		for(int i = 1; i <= cnt; i ++)
			if(!st[i] && a[i].v < minv) minv = a[i].v,p = i;
		res += minv,st[p] = 1;
		hs --;
		for(int i = a[p].l; i <= a[p].r; i ++) h[i] = min(h[i],a[p].h);
		for(int i = 1; i <= cnt; i ++)
			if(!st[i]) get_h(i);
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：1)

这里提供一种时间复杂度为 $O(n \times k)$ 的做法，完美爆标，但是理解起来有难度。      
（要是数据范围出成这样，比如 $n \le 10^6$，那这道题绝对不止绿题了。）          
题外话：[双倍经验](https://www.luogu.com.cn/problem/SP350)。（别问为什么有一篇一模一样的题解，问就是都是我写的。）    

-----

我们考虑把一个个山顶切成一层层的平面，用带权点表示切成的平面（权值为削平这个平面所需的代价），用边表示平面之间的互相支撑关系。       
拿样例举例，它长这个样子。       
（图中圈内表示的是点的权值而不是编号；由于数据中可能出现“悬崖峭壁”即两边不是最小值的情况，我在下面又加了一个平面兜底。）     
![](https://cdn.luogu.com.cn/upload/image_hosting/9sm59j7z.png)   
由图可知：这个图是一棵树，因为一个平面最多只会被一个平面支撑着。     
对于一些情况，最底一层被分成了多个部分，这时就需要再设一个超级树根兜底。         
一个叶子结点就是一个山峰，而现在的目的是**删除一些子树，使得剩余的叶子结点数量不大于 $k$，并且删除的子树权值和最小。**      

---------

很显然这是一个树型 DP 问题。设 $f_{u,i}$ 表示以 $u$ 为根，剩余叶子数量不大于 $i$ 的**最大代价**，则有       
$$f_{u,i}=\max_{j=1}^{i-1}{f_{v,j}+f_{u,i-j}}$$

设整棵树权值和为 $sum$，则答案为 $sum-f_{1,k}$。   
现在的问题是如何建树。

----------

对于一个坐标（记为 $i$），我们尝试寻找 $i$ **所在的这一层**的**下一层**，即托起它的那一层。记位置 $i$ 的海拔为 $s_i$。      
如何寻找呢？这里可以通过寻找它前面最后一个不大于它的位置（记为 $pre_i$）和后面第一个不大于它的位置（记为 $nxt_i$）来确定这一层的范围。具体方案可使用 set 维护或单调栈。       
如果 $pre_i$ 位置的海拔和 $i$ 位置的海拔相同，那么恭喜你，你这一层还有别的坐标（就是 $pre_i$），并且你所在的平面已经被建点了。那么你只需要把当前坐标指向的点记录好就可以了。     
否则你发现了一个新平面，它的范围是 $(pre_i,nxt_i)$。你要确定这个平面的父亲指向哪个平面，以及这个平面的权值。       
不理解？画个图。
![](https://cdn.luogu.com.cn/upload/image_hosting/5knbplbg.png)
手搓一下（顺序从左到右读）发现，位置 $i$ 所在平面的下面的平面海拔，是 $s_{pre_i}$ 和 $s_{nxt_i}$ 中的较大者。       
因此我们定位到海拔较高位置（记为 $lst$）代表的平面的点，连边。   
至于抹平位置 $i$ 所在平面的代价，我们知道它的大小是 $nxt_i-pre_i-1$，高度为 $s_i-s_{lst}$，抹平这个平面的代价就是二者之乘积。     
由于 $s_{lst} \le s_i$，我们需要**按照海拔从低到高遍历坐标**（作者就是这里搞错了想了半天）。注意考虑两边的边界情况（相当于最下面一层的超级树根）。       
这样，一棵带权树就建好了，我们可以愉快地跑树型 DP 了。      

-----
细节多，细节多，注意开 long long。      
树型 DP 注意转移顺序问题（欢迎评论区讨论）。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long siz[1005],f[1005][30],ans;
int n,k,s[1005],poi[1005],tot;
int fir[1005],num,pre[1005],nxt[1005],id[1005],sta[1005],top;
struct ss{int ed,nxt;}bia[1005];
void dfs(int wh)
{
	ans+=siz[wh];for(int i=0;i<=k;i++) f[wh][i]=siz[wh];
	for(int i=fir[wh];i;i=bia[i].nxt)
	{
		dfs(bia[i].ed);
		for(int j=k;j>=1;j--) for(int w=j-1;w>=0;w--)
		f[wh][j]=max(f[wh][j],f[bia[i].ed][j-w]+f[wh][w]);
	}
}bool c(int a,int b){return s[a]<s[b]||s[a]==s[b]&&a<b;}
int main()
{
    scanf("%d%d",&n,&k),sta[top=1]=0;
	for(int i=1;i<=n;id[i]=i,i++) scanf("%d",&s[i]);
	sort(id+1,id+n+1,c);for(int i=1;i<=n;i++)
	{
		while(top>=1&&s[sta[top]]>s[i]) top--;
		pre[i]=sta[top],sta[++top]=i;
	}sta[top=1]=n+1;for(int i=n;i>=1;i--)
	{
		while(top>=1&&s[sta[top]]>=s[i]) top--;
		nxt[i]=sta[top],sta[++top]=i;
	}for(int ii=1,i=id[ii];ii<=n;ii++,i=id[ii])
	{
		int wh=(s[pre[i]]>=s[nxt[i]])?pre[i]:nxt[i];
		if(s[pre[i]]==s[i]) {poi[i]=poi[pre[i]];continue;}
		siz[poi[i]=++tot]=1ll*(nxt[i]-pre[i]-1)*(s[i]-s[wh]),
		bia[++num].ed=tot,bia[num].nxt=fir[poi[wh]],fir[poi[wh]]=num;
	}dfs(1),printf("%lld",ans-f[1][k]);
}
```

---

## 作者：Frozen_Ladybug (赞：1)

这个题就是暴力找到山，然后每次删掉花费最小的山。

我用样例来解释一下过程。

```
    * * *     *
  * * * * *   * * *   *
* * * * * * * * * * * *
1 2 3 3 3 2 1 3 2 2 1 2
```
在遍历整个图以后，记录的每个坡的左右端点分别为 $[2,6],[8,10],[12,12]$，高度分别为 $\{3,3,2\}$。

因为地面最低高度为 $1$，可以将所有的高度都减去 $1$。

用 $sum$ 记录每一个坡土的体积。我们记录最低的海拔，在此上面找山。样例中三个坡的体积分别就是 $\{8,4,1\}$。

则如果只留下一个坡，最优的方式就是移除体积为 $4$ 和 $1$  的两个坡，使得答案为 $4+1=5$。

注意当你删掉一个山后有可能会使其他的山发生变化，每次重新扫一遍就好。

比如这个。

```
          * *
 [* *]  * * * *
  * * * * * * * * *   * * *
* * * * * * * * * * * * * * *
```

其中左边画方括号的那一段只有 $2$ 格土，但是如果把它删掉，右边的整个就合并成了一座较大的山。

如果还需要删掉山，就应该整体考虑，把山的总量再算一遍。

代码如下。

```c
#include<bits/stdc++.h>
using namespace std;
struct hill{
    int l,r,h,sum;
}v[1005];//建立结构体，记录每一座山。
//表示这个山的区间为[l,r]，最大高度为h，土的总量为sum。
int n,k,a[1005],num=0;
bool vis[1005];//标记每座山是否需要删除。
void check_hill(int p){//搜索每一座山是否需要被删除。
    int x=v[p].l,y=v[p].r;//在搜索完山的位置后，记录山的左右端点。
    while(x>=1&&a[x-1]<=a[x]) x--;
    while(y<=n&&a[y+1]<=a[y]) y++;
    v[p].l=x;
    v[p].r=y;
    v[p].h=max(a[x],a[y]);//需要挖掉的话，挖到左右端点的较大值就可以停。
    v[p].sum=0;
    for(int i=x;i<=y;i++)
        if(a[i]>v[p].h) v[p].sum+=a[i]-v[p].h;//从最低点记录山的总量。
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        if(vis[i]) continue;//如果已经被访问，无需执行。
        vis[i]=1;//没有被访问，则记录。
        int x=i,y=i;
        bool ll=0,rr=0;//左右端点都是当前点，用于记录是否需要停止。
        while(x>=1&&a[x-1]<=a[x]){
            x--;
            vis[x]=1;//只要左边有东西，标记访问。
            if(a[x]<a[i]) ll=1;//左边有更高的了，不能再往左搜。
        }while(y<=n&&a[y+1]<=a[y]){
            y++;
            vis[y]=1;
            if(a[y]<a[i]) rr=1;//这边同理。
        }if(ll&&rr){//只要两边都已经访问完，统计山的总量。
            v[num].l=x;v[num].r=y;
            v[num].h=max(a[x],a[y]);
            v[num].sum=0;
            for(int j=x;j<=y;j++)
                if(a[j]>v[num].h) v[num].sum+=a[j]-v[num].h;
            num++;//山的个数加一。
        }
    }
    int ans=0,hnum=num;
    memset(vis,0,sizeof(vis));
    while(hnum>k){
        int M=INT_MAX,p;//M是可能的最大值，往小了更新；而且不可能不更新。
        for(int i=0;i<num;i++){
            if(vis[i]) continue;
            if(v[i].sum<M) M=v[i].sum,p=i;
        }//搜索每一座山。
        ans+=M;
        vis[p]=1;
        hnum--;
        for(int i=v[p].l;i<=v[p].r;i++) a[i]=min(a[i],v[p].h);
        for(int i=0;i<num;i++)
            if(!vis[i]) check_hill(i);//没有被访问，就再看一遍。
    }
    printf("%d\n",ans);
    return 0;
}
```

---

