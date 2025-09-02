# [COCI 2021/2022 #1] Volontiranje

## 题目描述

给定一个 $1\sim n$ 的排列 $p$，请从这里面取出尽可能多的不交的上升子序列，且他们的长度为原排列的 LIS 的长度，并构造一组方案。

## 说明/提示

#### 数据范围

对于全部数据，$1\le n\le 10^6$，$1\le p_i\le n$。

| Subtask |  数据范围   | 分值 |
| :-----: | :---------: | :--: |
|   $1$   |  $n\le 15$  | $10$ |
|   $2$   | $n\le 10^3$ | $40$ |
|   $3$   | 无特殊限制  | $60$ |

#### 说明
**本题总分 $110$ 分。**

本题译自 [Croatian Open Competition in Informatics 2021/2022](https://hsin.hr/coci/archive/2021_2022) [Contest #1](https://hsin.hr/coci/archive/2021_2022/contest1_tasks.pdf) T5 Volontiranje。

在附加文件中下发了一份 checker.cpp。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
1 3
1 2 3```

## 样例 #2

### 输入

```
4
4 3 2 1```

### 输出

```
4 1
1
2
3
4```

## 样例 #3

### 输入

```
7
2 1 6 5 7 3 4```

### 输出

```
2 3
1 3 5
2 6 7```

# 题解

## 作者：MiRaciss (赞：20)

## 前置芝士

LIS 的 $nlog(n)$ 算法

也就是说您可以去看看[这道博客](https://blog.csdn.net/lxt_Lucia/article/details/81206439)

## 题解

长度直接求就好了，现在考虑怎么求方案数。

我们把题目所给的序列中的每一个元素按照**下标**和**值**表示成一个点对，然后建立平面直角坐标系($x$ 为下标，$y$ 为值，这里以样例 $3$ 举例):

![](https://cdn.luogu.com.cn/upload/image_hosting/ev8gswxq.png)

我们发现，一个上升子序列反应到图上是由 $x$，$y$ 均递增的点组成的，且任意组 $x$ 递增，$y$ 递减的点一定不是上升子序列。

我们考虑从 $x=1$ 开始，将这些点划分成多组 $x$ 递增，$y$ 递减的点，如图:

![](https://cdn.luogu.com.cn/upload/image_hosting/h6yltz8m.png)

那么可以发现，任意一个最长上升子序列方案都可以表现为在每一层中分别选择一个点且满足它们均是 $x$，$y$ 均递增的点的前提下的方案。

以样例 $3$ 为例，其中的一个最长上升子序列的方案为 `1 3 5` ，反应在坐标系上就是选择 `A C E` 三个点。

那么这个问题就神奇的转换成了：在每一层中选一个点，在满足它们均是 $x$，$y$ 均递增的点的情况下且每个点只能选一次的方案数。


我们先解决怎么分层。

我们将 $LIS_i$ 定义为在下标 $i$ 处结束的最长递增子序列的长度,那么其实第 $k$ 层就是 $LIS_i=k$ 的下标的集合。

然后我们接下来证明一个问题：在某一层中的点跳到下一层中时，选择下标更小的点一定**不劣于**选择下标更大的点。

让我们再来看一看那张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/h6yltz8m.png)

举个例子，我现在已经选择了 $A$ 点，下一步可以选择 $C$，$D$ 点，但我选择 $C$ 点的总方案数一定不比选择 $D$ 点的方案数少。

我们考虑怎么证明。

以这里的 `A,B,C,D` 举例，如果我们选择 `A,D`，那么还有 `B,C` 这一条路；如果我们选择 `A,C`，那么还有 `B,D` 这一条路。推广到很多个，我们的选择一定不会导致答案变小

但是为什么不能用 `A,D`，`B,C` 这样交错的方法呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/38sj9a9u.png)


以这张图为例，如果我们选择 `A,D`, 会发现 `B,C` 无法选择，但我们可以选择 `A,C` `B,D` 这两种方法。推广一下，我们的方法一定是最优的。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,len=0;
int a[1000005];
int dp[1000005];
int id[1000005];
vector<int> v[1000005],st;
vector<vector<int> > ans;
//int ans=0x3f3f3f3f;

void File(){
	freopen("volunteering.in","r",stdin);
	freopen("volunteering.out","w",stdout);
}

void Solve(){
	while(1){
        if(st.empty())
            if(v[1].empty()) break;
            else st.push_back(v[1].back()),v[1].pop_back();
		else if(st.size()==len) ans.push_back(st),st.clear();
		else{
            int k=st.size()+1,now=st.back();
            while (v[k].size()&&v[k].back()<now) v[k].pop_back();
            if(v[k].empty()||a[now]>a[v[k].back()]) st.pop_back();
            else st.push_back(v[k].back()),v[k].pop_back();
        }
    }
}

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		if(dp[len]<a[i]){ ++len;dp[len]=a[i],id[len]=i;v[len].push_back(i);continue; }
		int now=lower_bound(dp+1,dp+len+1,a[i])-dp;
		dp[now]=a[i],id[now]=i;
		v[now].push_back(i); 
	}
	for(int i=1;i<=len;i++) reverse(v[i].begin(),v[i].end());
	Solve();
	printf("%d %d\n",ans.size(),len);
	for(int i=0;i<ans.size();i++){
		for(auto x:ans[i]) printf("%d ",x);
		printf("\n"); 
	}
	return 0;
} 
/*
14
9 12 8 3 5 4 13 1 14 10 6 2 11 7

7
2 1 6 5 7 3 4
*/
```

---

## 作者：Rem_CandleFire (赞：4)

## 题目大意

[传送门](https://www.luogu.com.cn/problem/P7931)

---

## 分析

### 关于 LIS

知周所众，LIS 的定义为：**一个序列中最长的单调递增子序列**。

求 LIS 一般有 3 种方式，我个人选择贪心，~~因为懒，不想写太多代码~~。

贪心求 LIS 的中心思想：让靠前的数尽可能小，又因 LIS 单调递增，故采用二分提速。

code：
```cpp
for(int i=1;i<=n;++i)
{
	scanf("%d",&a[i]);
	int pos=lower_bound(low,low+len,a[i])-low;
	low[pos]=a[i];
	len=max(len,pos+1);
}
```

### 回到题目

首先根据题目要求求出原序列的 LIS 长度 $len$。

根据 LIS 的定义，我们可以知道**任何递减的子序列中的数不可能在同一个 LIS 中**。

又根据其要求满足 **$a_{i}$ 递增且 $i$ 递增**，于是想到把 $a_{i}$ 当作一个点 $(i,a_{i})$，这样一来，我们就可以在二维层面上考虑了。

接下来我们需要解决两个问题：

**1. 如何分层。**

**2. 如何求解 LIS。**

先来看**第一个问题**，我们注意到对于每一个点 $(i,a_{i})$，对这个点寻找左上方的另一个点 $(j,a_{j})$ 的过程（即 $j<i$，$a_{j}>a_{i}$）与我们在上述贪心过程中，用 $a_{i}$ 替换 $low_{pos}$ 的行为有异曲同工之妙。

于是，我们只需要在贪心中加入代码：

```cpp
g[pos].push_back(i); //a[pos]>a[i] 加入这一层
```

就可以达到分层的效果了。

接下来是**第二个问题**，我们先来脑补一下该如何操作：在每一层中从上往下找到一个最上方的符合条件的点，一层层枚举直到长度达到 $len$ 为止。

注意到这样的行为很像 DFS，于是使用 DFS 来解决。

在写代码的过程中有一些小优化和细节，已经注释了。

---

### code：

```cpp
#include<bits/stdc++.h>
#define reg register
using namespace std;
const int size=1e6+5;
int n,len,cnt,tim;
// n,LIS长度为len 分为cnt层 可选出tim个不交LIS 
int a[size],low[size],top[size],lis[size],vis[size];
// 输入排列a[i] 用于贪心求LIS,low[i] 
// top[i]:第i层当前备选的点为g[i][top[i]]
// lis[i]:dfs过程中存储LIS
// vis[i]:记录i在某个LIS中是第几个，用于找到一个LIS之后倒退回初始情况避免重复 
vector<int> g[size],ans[size];
// 存储分层（下标） 存储答案 
void dfs(int x,int sum,int last)
{
	if(sum==len) //找到LIS 
	{
		++tim;
		for(int i=1;i<=len;i++)
			ans[tim].push_back(lis[i]),vis[lis[i]]=i;
		return ;
	}
	if(1+sum<x)return ;
	// len-x+1+sum<len 即剩下的每一层都取数也无法使LIS长度达到len 
	for(reg int i=top[x];i<g[x].size();++i)
	{
		if(a[g[x][i]]>a[last]&&g[x][i]>last) //LIS需要满足：a[i]递增 i递增 
		{
			top[x]=i+1;  //下一次枚举第i层直接从top[i]开始，节省时间 
			lis[sum+1]=g[x][i]; //记录 
			dfs(x+1,sum+1,g[x][i]);
			if(vis[g[x][i]]!=1)return ; 
			//一直退回到第一层重新搜索，避免样例出现1 3 5 \n 1 6 7的情况 
		}
	}
	if(top[x]>=g[x].size())dfs(x+1,sum,last);//这一层不可选 
}
int main()
{
	scanf("%d",&n); len=0;
	for(reg int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		int pos=lower_bound(low,low+len,a[i])-low;
		low[pos]=a[i];
		len=max(len,pos+1);
		//贪心求原排列的LIS 
		vis[i]=1; //一开始默认为第一个 
		g[pos].push_back(i);//a[pos]>a[i] 加入这一层 
	}
	dfs(0,0,0);
	printf("%d %d\n",tim,len);
	for(reg int i=1;i<=tim;++i)
	{
		for(reg int j=0;j<len;++j)
			printf("%d ",ans[i][j]);
		puts(""); 
	}
	return 0;//好习惯--完结撒花 
}
```

---

## 作者：cirnovsky (赞：4)

哲学题。

以下标为横轴，$p_i$ 为纵轴，画出一个坐标系。然后你会发现每个点的后继在其右上方，以此为依据来分层（具体来说，就是求出每个位置的 LIS）。

我毛了张图给你看啊：

![](https://img-blog.csdnimg.cn/img_convert/bc11a0ef9186b4536572ab0ad1d9a4a1.png)。

然后在每层搞事情。这里有个结论：

>**Claim**：存在一种选择 LISs 的方案，使得每个 LIS 都不交叉。

证明应该不难吧，因为每两个之间交换了没有影响，每层都看得到。那么选择下标更小的点一定~~苏卡~~不劣。然后优化下搜索的方式就可以解决了，这个具体看代码。

```cpp
int n,a[1000100],fwt[1000100],dp[1000100],st[1000100],ed[1000100],q[1000100],lis,ans,lst[1000100];
vector<int> rec;
void Add(int x,const int w) { for(; x<=n; x+=x&-x)	cmax(fwt[x],w); }
int Sum(int x) { int res=0; for(; x; x^=x&-x)	cmax(res,fwt[x]); return res; }
void digger() {
	printf("%d %d\n",ans,lis);
	for(int i=1; i<=ans; ++i) {
		for(int j=(i-1)*lis+1; j<=i*lis; ++j)	printf("%d ",rec[j-1]);
		puts("");
	}
	exit(0);
}
signed main() {
	n=read();
	for(int i=1; i<=n; ++i) {
		dp[i]=Sum((a[i]=read())-1)+1;
		Add(a[i],dp[i]),cmax(lis,dp[i]);
		ed[dp[i]]++;
	}
	for(int i=1; i<=n; ++i)	ed[i]+=ed[i-1],st[i]=ed[i];
	for(int i=n; i; --i)	q[st[dp[i]]--]=i;
	for(int i=1; i<=n; ++i)	st[i]=ed[i-1]+1;
	for(int i=1; i<=n; ++i)	sort(q+st[i],q+ed[i]+1);
	while(233) {
		for(int i=1; i<=lis; ++i) { // enumrating layers
			if(st[i]>ed[i])	digger();
			if(a[q[st[i]]]<a[lst[i-1]]) {
				----i; st[i+1]++;
				continue;
			}
			while(q[st[i]]<lst[i-1] && st[i]<=ed[i]) {
				st[i]++;
				if(a[q[st[i]]]<a[lst[i-1]]) {
					----i; st[i+1]++;
					goto Suc;
				}
			}
			if(st[i]>ed[i])	digger();
			lst[i]=q[st[i]];
			Suc:;
		}
		for(int i=1; i<=lis; ++i)	rec.push_back(lst[i]),st[i]++;
		ans++;
	}
	return 0;
}
```

---

## 作者：Glacial_Shine (赞：3)

# 题目大意
让你求最多有多少个不相交的最长上升子序列。

# 思路

我们可以将数 $a_i$ 看成一个点 $(i,a[i])$，于是我们可以按照 $x$ 递增 $y$ 递减考虑分层。

分层的方法就是从 $1$ 到当前点的 LIS 即为其所在层数。

此时 LIS 的长度就是层数，并且层数内的点 $x$ 递增，$y$ 递减，再考虑对于序列的可能性。

此时不能简单的想为每一层的数的个数的最小值，如下图就是一个反例。

![](https://cdn.luogu.com.cn/upload/image_hosting/9xet0bts.png)

我们直接贪心每一个序列能否填当前数即可，如果贪心不出来，即在下一层找不到满足条件的点，就直接弹出即可。

具体判断可以看代码实现。

时间复杂度是 $O(n\cdot \log n)$。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, b[1000005], s[1000005], a[1000005], nxt[1000005];
vector<int> ans[1000005];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {//分层
        scanf("%d", &a[i]);
        int l = 1, r = m, mid;
        while (l <= r) {
            mid = l + r >> 1;
            if (a[b[mid]] > a[i])
                r = mid - 1;
            else
                l = mid + 1;
        }
        if (r == m)
            m++, b[m] = i, s[m]++;
        else
            nxt[i] = b[r + 1], b[r + 1] = i, s[r + 1]++;
    }
    int minn = 0, ansm = 0;
    for (int i = 1; i <= m; i++) minn |= (s[i] == 0);
    while (minn == 0) {//判断每一个数列是否可行
        ansm++;
        for (int j = 1; j <= m; j++) {
            while (!ans[ansm].empty() && b[j] != 0 && a[b[j]] < a[ans[ansm].back()])
                b[j] = nxt[b[j]], s[j]--, minn |= (s[j] == 0);
            if (b[j] == 0) {
                minn = 1;
                ansm--;
                break;
            }
            if (!ans[ansm].empty() && b[j] < ans[ansm].back()) {//此时上一个数在这一层找不到任何x，y都比它大的数
                j -= 2, ans[ansm].pop_back();
                continue;
            }
            ans[ansm].push_back(b[j]), b[j] = nxt[b[j]], s[j]--, minn |= (s[j] == 0);
        }
    }
    printf("%d %d\n", ansm, m);
    for (int i = 1; i <= ansm; i++, printf("\n"))
        for (auto g : ans[i]) printf("%d ", g);
    return 0;
}
```


---

## 作者：jamesharden666 (赞：1)

## T5
我们可以画一个平面直角坐标系，将每个点用 $(i,a_i)$ 表示，可以发现，每个上升子序列由 $x,y$ 单调递增的若干个点对组成，于是我们考虑预处理出每个点在其构成的答案中的位置，也就是分层。推了几个小数据就可以发现，第 $j$ 层集合由所有满足 $LIS_i=j$ 的 $i$ 组成。这里 $LIS_i$ 可以用二分、树状数组或线段树算出来，分层后就可以用贪心构造。

![](https://cdn.luogu.com.cn/upload/image_hosting/c49ewcyc.png)

时间复杂度为 $\mathcal O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000000+10],f[1000000+10],maxn=0,tot=INT_MAX,fans=0;
vector<int> son[1000000+10],s;
vector<vector<int> > ans;
struct tree
{
    int l,r,v;
}t[8000000+10];
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
        s=s*10+(ch-'0'),ch=getchar();
    return s*w;
}
void build(int root,int l,int r)
{
    t[root].l=l;
    t[root].r=r;
    if(l==r)
    {
        t[root].v=0;
        return ;
    }
    int mid=(l+r)>>1;
    build(root*2,l,mid);
    build(root*2+1,mid+1,r);
}
void add(int root,int l,int r,int pos,int val)
{
    if(l==r)
    {
        t[root].v=val;
        return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)
        add(root*2,l,mid,pos,val);
    else
        add(root*2+1,mid+1,r,pos,val);
    t[root].v=max(t[root*2].v,t[root*2+1].v);
}
int ask(int root,int l,int r)
{
    if(t[root].l>=l&&t[root].r<=r)
        return t[root].v;
    if(t[root].r<l||t[root].l>r)
        return 0;
    int s=0;
    if(t[root*2].r>=l)
        s=max(s,ask(root*2,l,r));
    if(t[root*2+1].l<=r)
        s=max(s,ask(root*2+1,l,r));
    return s;
}
void work()
{
    while(1)
    {
        if(s.empty())
        {
            if(son[1].empty())
                break;
            else
                s.push_back(son[1].back()),son[1].pop_back();
        }
        else if(s.size()==maxn)
            ans.push_back(s),s.clear();
        else
        {
            int k=s.size()+1,now=s.back();
            while(!son[k].empty()&&now>son[k].back())
                son[k].pop_back();
            if(son[k].empty()||a[now]>a[son[k].back()])
                s.pop_back();
            else
                s.push_back(son[k].back()),son[k].pop_back();
        }
    }
}
int main()
{
    n=read();
    for(int i=1;i<=n;++i)
        a[i]=read();
    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        f[i]=ask(1,1,a[i]-1)+1;
        add(1,1,n,a[i],f[i]);
    }
    for(int i=1;i<=n;++i)
    {
        fans=max(fans,f[i]);
        son[f[i]].push_back(i);
        maxn=max(maxn,f[i]);
    }  
    for(int i=1;i<=maxn;++i)
        reverse(son[i].begin(),son[i].end());
    work(); 
    printf("%d %d\n",ans.size(),fans);
    int l=ans.size();
    for(int i=0;i<l;++i)
    {
        for(auto v:ans[i])
            printf("%d ",v);
        printf("\n");
    }
    return 0;   
}
```

---

## 作者：qwer6 (赞：0)

## 1. Description

给定一个 $1\sim n$ 的排列 $p$，请从这里面取出尽可能多的不交的上升子序列，且他们的长度为原排列的 LIS 的长度，并构造一组方案。

## 2. Solution

首先使用 $O(n\log n)$ 的算法求出 $f_i$ 表示以 $i$ 结尾的 LIS 的长度与原排列的 LIS 的长度，这一块比较基础，按下不表。

然后考虑构造方案，这里比较玄学，也比较难想到，考虑将 $(i,p_i)$ 视为一个点，反映到一个平面直角坐标系中，例如样例 $3$ 对应的排列可以视为下图。

![捕获](https://s1.imagehub.cc/images/2025/07/11/dd40466c4f084245b5df9426256d15dd.png)

根据 LIS 中相邻两项的定义 $i< j$ 且 $h_i<h_j$，可以发现一条完整的 LIS 反映到图中会是一条斜向右上的曲线，那么现在这个问题就被转换为了在图中构造尽可能多的合法曲线，他们之间没有公共的关键点。

更进一步的，我们发现 $f_i$ 相等的位置绝对不可能出现在同一条曲线上，因此将所有点按照 $f_i$ 分层，那么样例 $3$ 分层之后就可以得到这张图：

![捕获](https://s1.imagehub.cc/images/2025/07/11/a2827b3eb5585764e5e986858c35b211.png)

那么问题又转换为了在每层中选择一个点，不能重复选择，构成尽可能多的合法曲线。

我们发现，在同一组中，随着下标变大，对应的值越来越小，这样有一个很好看出的贪心，也就是每一次取出第一层中下标最小的点 $(x,p_x)$，然后遍历所有层，删除所有下标小于 $x$ 的位置，最后在每一层选择剩下的点中下标最小的那一个，检查是否合法即可。

具体的，我们判断假定上一个选择的点为 $(a,p_a)$，在这一层中剩下的点中饭下标最小的那一个为 $(b,p_b)$，如果 $p_a>p_b$，那么弹出 $(a,p_a)$，返回上一层重新选择。

这个贪心显然是正确的，我们只需要考虑两层之间这样决策的正确性，然后即可推广到更多层的情况。

我们不妨假设在第一层中有两个点 $(x_1,p_{x_1}),(x_2,p_{x_2})$，满足 $x_1<x_2,p_{x_1}>p_{x_2}$，如果可以接到这两个点之后的点组成的集合并不相同，那么贪心显然正确；而如果集合相同，对于第二层中下标最小且同时可以接到 $(x_1,p_{x_1}),(x_2,p_{x_2})$ 的点，我们把它分配给 $(x_1,p_{x_1})$，因为如果后面出现一个点又同时可以接到 $(x_1,p_{x_1}),(x_2,p_{x_2})$ 的点的话，我们可以把它分配给 $(x_2,p_{x_2})$；如果没有出现的话不管们将第一个点分配给哪一个点都只有一条曲线，不会减少。

所以贪心正确，因此，我们只需要记录每个层级的点，然后暴力模拟一下即可，每个点只会被尝试选中一次，时间复杂度就是 $O(n)$，那么最后的总体时间复杂度为 $O(n\log n)$。

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源与快读快写*/
const int N=1e6+5;
int n,len;
int a[N],f[N],dp[N],path[N],q[N],head[N],tail[N],cnt[N];
vector<int>now,ans;
signed main(){
	read(n);
	for(int i=1,p;i<=n;i++){
		read(a[i]);
		if(len==0||f[len]<a[i]){
			f[++len]=a[i],dp[i]=len,cnt[len]++;
			continue;
		}
		p=lower_bound(f+1,f+len+1,a[i])-f;
		f[p]=a[i],dp[i]=p,cnt[p]++;
	}
	for(int i=1;i<=len;i++){
		cnt[i]+=cnt[i-1];
		head[i]=cnt[i-1]+1;
		tail[i]=cnt[i-1];
	}
	for(int i=1;i<=n;i++)
		q[++tail[dp[i]]]=i;
	while(1){
		if(now.empty()){
			if(tail[1]<head[1])break;
			now.push_back(q[head[1]]),head[1]++;
		}else if(now.size()<len){
			int x=now.size()+1;
			while(head[x]<=tail[x]&&q[head[x]]<now.back())head[x]++;
			if(tail[x]<head[x])break;
			if(a[q[head[x]]]<a[now.back()]){
				now.pop_back();
				continue;
			}
			path[now.back()]=q[head[x]];
			now.push_back(q[head[x]]),head[x]++;
		}else{
			ans.push_back(now.front());
			now.clear();
		}
	}
	write(ans.size()),Spa,write(len),Nxt;
	for(int x:ans){
		while(x){
			write(x),Spa;
			x=path[x];
		}
		Nxt;
	}
}
}
```

---

## 作者：DengDuck (赞：0)

令人无语的是这题卡 $\text{STL}$ 的栈。

首先这题要先求 $\text{LIS}$，我是用树状数组求的，求出的值，以 $i$ 结尾的 $\text{LIS}$ 长度为 $f_i$。

然后我们发现，对于相等的一类 $f_i$，显然不可能在一个上升子序列中，事实上，我们把这些点在坐标系里点出来，应该是 $x$ 增大，$y$ 变小的样子。

所以我们可以以 $f_i$ 分层，由于题目要求序列是 $\text{LIS}$，所以要爬满每一层。

我们做法是从 $f_i=1$ 的较小值开始爬，我们发现可以贪心地在爬下一层的时候尽可能选最小值，原因显然。

爬不上去了没关系，说明上面那一层的值有问题，我都已经是现在的最小了，我都上不去，那其他人也上不去，所以把上面一层那个最小值删了。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL int
#define X first
#define Y second
using namespace std;
const LL N=1e6+5;
LL n,a[N],t[N],mx,cnt=1;
vector<LL>s[N];
vector<LL>ans[N];
inline LL lowbit(LL x)
{
	return x&-x;
}
inline LL query(LL x)
{
	LL ans=0;
	while(x)
	{
		ans=max(ans,t[x]);
		x-=lowbit(x);
	}
	return ans;
}
inline void update(LL x,LL y)
{
	while(x<=n)
	{
		t[x]=max(t[x],y);
		x+=lowbit(x);
	}
}
void work()
{
	LL t=1;
	while(t!=mx)
	{
		if(ans[cnt].empty())return;
		LL k=ans[cnt].back(); 
		while(1)
		{
			if(s[t+1].empty())return;
			LL to=s[t+1].back();
			if(a[k]>a[to])
			{
				s[t+1].pop_back();
				continue;
			}
			if(k>to)
			{
				ans[cnt].pop_back();
				t-=2;
				break;		
			}
			ans[cnt].push_back(to);
			s[t+1].pop_back();
			break;
		}
		
		t++;
	}
	if(t==mx)cnt++;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		LL k=query(a[i])+1;
		update(a[i],k); 
		mx=max(k,mx);
		s[k].push_back(i);
	}
	while(!s[1].empty())
	{
		LL t=s[1].back();
		ans[cnt].push_back(t);
		s[1].pop_back();
		work();
	}
	printf("%d %d\n",cnt-1,mx);
	for(int i=1;i<=cnt-1;i++)
	{
		for(LL j:ans[i])printf("%d ",j);
		printf("\n");
	}
}

```

---

## 作者：2020tanjunming (赞：0)

### 题解
求以序列中每个数结尾的最长上升子序列，可以用树状数组，也可以用[这个方法](https://blog.csdn.net/tanjunming2020/article/details/127013337)，都是 $O(n\log n)$ 的。

下面考虑如何求方案数和每种方案。

我们可以把题目所给序列中的每个元素的下标和值在平面直角坐标系中表示成一个点，并将这些点分层，第 $k$ 层的点中的每一个点 $i$ 都满足以序列中第 $i$ 个数结尾的最长上升子序列的长度为 $k$。

题目第三个样例的分层结果如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/pvvhu1eu.png)

那么问题就转换成了在每层中选一个点，满足它们的横坐标和纵坐标递增，且每个点最多被选一次，求最多能选几个序列。

有一点我们需要知道：当从一层到下一层时，选择下标小的点不劣于选择下标大的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/z4ij5bd8.png)

比如这个图，在选到 A 时，如果选 D，则 C 就不能再选了；但如果选 B，那 C 可以选 D，显然更优。

也可以自己举几个例子来理解。

时间复杂度为 $O(n\log n)$。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans1=0,ans2=0,a[1000005],f[1000005],tr[1000005];
vector<int>v[1000005],ans[1000005];
vector<int>::iterator it;
int lb(int i){
	return i&(-i);
}
void pt(int i,int v){
	while(i<=n){
		tr[i]=max(tr[i],v);
		i+=lb(i);
	}
}
int find(int i){
	int re=0;
	while(i){
		re=max(re,tr[i]);
		i-=lb(i);
	}
	return re;
}
void dd(){
	while(1){
		if(ans[ans1].empty()){
			if(v[1].empty()) break;
			else{
				ans[ans1].push_back(v[1].back());
				v[1].pop_back();
			}
		}
		else if(ans[ans1].size()==ans2) ++ans1;
		else{
			int t=ans[ans1].size()+1,w=ans[ans1].back();
			while(!v[t].empty()&&v[t].back()<w) v[t].pop_back();
			if(v[t].empty()||a[w]>a[v[t].back()]) ans[ans1].pop_back();
			else{
				ans[ans1].push_back(v[t].back());v[t].pop_back();
			}
		}
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		f[i]=find(a[i])+1;
		pt(a[i],f[i]);
		ans2=max(ans2,f[i]);
		v[f[i]].push_back(i);
	}
	for(int i=1;i<=ans2;i++){
		reverse(v[i].begin(),v[i].end());
	}
	dd();
	printf("%d %d\n",ans1,ans2);
	for(int i=0;i<ans1;i++){
		for(int j=0;j<ans2;j++){
			printf("%d ",ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Tsawke (赞：0)

# COCI2021-2022 Contest1 T5 题解

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=COCI-2021-2022-Contest1)

（建议您从上方链接进入我的个人网站查看此 Blog，在 Luogu 中图片会被墙掉，部分 Markdown 也会失效）

## [原题面链接](https://hsin.hr/coci/contest1_tasks.pdf)

## [Luogu题面](https://www.luogu.com.cn/problem/list?keyword=COCI2021-2022%231&page=1)

## T5 Volontiranje

~~这题比 T4 简单多了。~~

### 题面

给定一个长度为 $ n $ 的排列，求最多的不交叉最长上升子序列的（即每个数只能用一次）。~~（是的就这么简洁）~~

输出个数，长度，并输出每一个最长上升子序列。$ n \le 10^6 $。

### Examples

**Input_1**

> 3
>
> 1 2 3

**Output_1**

> 1 3
>
> 1 2 3

**Input_2**

> 4
>
> 4 3 2 1

**Output_2**

> 4 1
>
> 1
>
> 2
>
> 3
>
> 4

**Input_3**

> 7
>
> 2 1 6 5 7 3 4

**Output_3**

> 2 3
>
> 1 3 5
>
> 2 6 7

### Solution

考虑求 LIS 的长度直接 $ O(n \log n) $ 求即可，可以用 `` lower_bound `` 求。

而对于有哪些 LIS，我们则需要找到其中的一些性质，考虑将每个数的下标作为 $ x $，数值作为 $ y $，把每个数丢到二维坐标系里面观察性质，比如对于 Input_3，最后会形成下图：

![COCI-Contest1_1.png](http://monkey-hyx.tech/Images/Blog/COCI-Contest1_1.png)

观察这个奇怪的图形我们可以考虑从 $ x = 1 $ 开始划分层级，把 $ x $ 递增而 $ y $ 递减的点与初始点划分到同一层级。

也就是如下：

![COCI-Contest1_2.png](http://monkey-hyx.tech/Images/Blog/COCI-Contest1_2.png)

注意这里的层级划分是左下开右上闭的。

于是我们便可以发现，对于每一个 LIS 都应该是从每一个层级中选择一个点并且符合，下一层级的点符合在当前点的右上。

这里我们考虑如何分层，考虑当我们计算 LIS 时，一般用的状态是，以当前点为结尾的 LIS 长度，我们观察发现，第一层级里，$ A, B $ 长度一定为 $ 1 $，第二层级里，$ C, D, F $ 长度一定为 $ 2 $，$ E, G $ 长度一定为 $ 3 $。

于是我们便可以发现按照 $ LIS_i = k $，对于同一个 $ k $ 的所有下标 $ i $ 作为同一层级。

让后我们考虑如何选择每一层级的点，这里我们有一个结论，对于每一层级优先选择纵横坐标，也就是下标更低的未选择过的点一定是更优的，这个正确性可以去举例理解一下，如果对于上图的情况，连结 $ AD $ 与 $ BC $ 和链结 $ AC $ 与 $ BD $ 都可以符合要求，是两组不同的合法解，但是考虑如下情况：

![COCI-Contest1_3.png](http://monkey-hyx.tech/Images/Blog/COCI-Contest1_3.png)

（这里为了方便表述省略了一些点）

显然层级划分的线大概是这样，这个时候如果我们对于 $ A $，使其连结横坐标更小的 $ C $，会使 $ BD $ 也是一组合法解，而如果连结 $ AD $，则 $ BC $ 不合法。故显然优先连结未选择里面横坐标更小的是最优方案。

至此我们的推导已经结束，可以进行实现了。

### Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr

/******************************
abbr

******************************/

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;



template<typename T = int>
inline T read(void);

vector < int > LISv;
pair < int, int > LIS[1100000];
int N;
vector < int > current;
vector < int > tier[1100000];
int arr[1100000];
vector < vector < int > > anss;
int main(){
    N = read();
    for(int i = 1; i <= N; ++i){
        arr[i] = read();
        if(LISv.empty() || LISv.back() < arr[i])LISv.push_back(arr[i]), tier[(int)LISv.size()].push_back(i);
        else{
            auto pos = lower_bound(LISv.begin(), LISv.end(), arr[i]);
            int len = distance(LISv.begin(), pos) + 1;
            *pos = arr[i];
            tier[len].push_back(i);
        }
    }
    int maxLen = (int)LISv.size();
    for(int i = 1; i <= maxLen; ++i)
        reverse(tier[i].begin(), tier[i].end());
    while(true){
        if(current.empty()){
            if(tier[1].empty())break;
            current.push_back(tier[1].back());
            tier[1].pop_back();
        }else if((int)current.size() == maxLen){
            anss.push_back(current);
            current.clear();
        }else{
            int pos = current.size() + 1;
            int last = current.back();
            while(!tier[pos].empty() && tier[pos].back() < last)tier[pos].pop_back();
            if(tier[pos].empty() || arr[tier[pos].back()] < arr[last])current.pop_back();
            else current.push_back(tier[pos].back()), tier[pos].pop_back();
        }
    }
    printf("%d %d\n", (int)anss.size(), maxLen);
    for(auto i : anss){
        for(auto j : i)printf("%d ", j);
        printf("\n");
    }
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}



template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_08_30 T1-T3

update-2022_09_01 完成一部分的 T4

update-2022_09_02 T4 肝完

update-2022_09_04 初稿

update-2022_09_04 发现 T4 之前算法假掉了，修改了一下

update-2022_09_06 完善 latex 以符合 Luogu 题解要求

---

## 作者：Mu_tr (赞：0)

# 题目大意
给定一个数列，让你求其中的最长上升子序列长度以及互不相交的最长上升子序列个数。

# 题目思路
这道题自然可以分成两部分去做。
## 1.求最长上升子序列（LIS）
LIS 作为经典的 dp 题目，普通的 $O(n^2)$ dp，在这道题里会超时。这里我采用的是树状数组优化转移的 $O(n\log(n))$ 的做法。（当然权值线段树和二分都可以做到 $O(n\log(n))$）。

## 2.求最长上升子序列的个数
为方便讲解，这里沿用楼上大牛的图片。

![](https://img-blog.csdnimg.cn/img_convert/bc11a0ef9186b4536572ab0ad1d9a4a1.png)

我们可以发现在求最长上升子序列的过程中，我们可以找到在一个点前面最多能接上多长的序列，再加这个值加一，便是这个点的 LIS，于是我们便将这些点以下标为横坐标，权值为纵坐标建立一个平面直角坐标系，然后我们将 LIS 相同的点放在一起，LIS 不同的点之间划条线，可以发现每一块之间从左往右，权值都是单调递减的（这是我们后面优化复杂度的重要结论），这个结论可以通过最长上升子序列的定义证明得出。那么怎么找到一条最长上升子序列呢？可以发现只要在每一层之间找到一个点，并且从左往右满足权值单调递增即可。那么可以发现一个显然的贪心，就是两层之间，在那一层中权值较小的点连在另一层中权值较小的点，在那一层中权值较大的点连在另一层权值较大的点一定比在那一层中权值小的点连在另一层权值大的点，在那一层中权值大的点连在另一层权值小的点更优。（有点绕，慢慢理解一下），意识地说就是这样做有更大的可能有更多的最长上升子序列，证明可以参考楼上大牛。

# 代码实验
由于细节较多，这里结合代码注释理解一下
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum[4000005],p[1000005],ans,cnt=1;//p是题目中的序列，sum是树状数组 
vector<int> e[1000005],f[1000005];//e是存答案的数组，f是存各个层上数字的数组 
int lowbit(int x){
	return x&-x;
}
void modify(int x,int v){//树状数组单点修改 
	for(int i=x;i<=n;i+=lowbit(i)){
		if(i==x)sum[i]=v;
		sum[i]=max(sum[i],v);
	}
	return ;
}
int query(int x){//树状数组查询 
	int ret=0;
	for(int i=x;i;i-=lowbit(i)){
		ret=max(ret,sum[i]);
	}
	return ret;
}
void dfs(int k,int t,int past){//k表示点的编号，t表示层数，past表示过去的cnt的值是多少 
	if(t==ans){
		cnt++;//如果找到一组答案，那么改变cnt的值，以便退出 
		return;
	}
	for(int i=f[t+1].size()-1;i>=0;i--){//倒序枚举，因为每一层的值满足单调递减 
		if(p[k]>p[f[t+1][i]]){//如果下一层的点比这个还小，那一定没有贡献，直接删除 
			f[t+1].pop_back();
			continue;
		}
		if(!f[t+1].size()||k>f[t+1][i]){//如果匹配好的这个点不满足条件返回上一层循环 
			e[cnt].pop_back();
			return;
		} 
		int d=f[t+1][i];
		e[cnt].push_back(f[t+1][i]);f[t+1].pop_back();//递归的过程中自动存储答案 
		dfs(d,t+1,cnt);
		if(cnt!=past) return;//如果这次进入找到解了，退出 
	}
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){//计算最长上升子序列的长度并按照层数进行自动分层 
		scanf("%d",&p[i]);
		int d=query(p[i])+1;
		f[d].push_back(i);
		modify(p[i],d);
		ans=max(ans,d);
	}
	for(int i=f[1].size()-1;i>=0;i--){//将第一层的每个点都放进去跑一遍 
		int d=f[1][i];
		e[cnt].push_back(f[1][i]);
		f[1].pop_back();
		dfs(d,1,cnt);
	}
	cnt--;//因为最后一组没有找完，所以减 
	printf("%d %d\n",cnt,ans);
	for(int i=1;i<=cnt;i++){
		for(int j=0;j<e[i].size();++j) printf("%d ",e[i][j]);
		printf("\n");
	}
	return 0;
}
```

## 细节
1. 这里我的 f 数组里面的值都是从小到大的，保证刚刚单调递减的性质。

2. 51-59 行，中将第一层的每个点都拿来跑一遍，因为每一层都要贡献一个点，所以这么写。

3. 27-41 行，这是题目的核心所在，这里能删点的时候要删点，防止 TLE，好好理解一下

4. 这里我采用的因为是搜索，复杂度有点玄学，另外数据水勉强能过这道题。

---

