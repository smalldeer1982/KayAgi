# Similar Sets

## 题目描述

You are given $ n $ sets of integers. The $ i $ -th set contains $ k_i $ integers.

Two sets are called similar if they share at least two common elements, i. e. there exist two integers $ x $ and $ y $ such that $ x \ne y $ , and they both belong to each of the two sets.

Your task is to find two similar sets among the given ones, or report that there is no such pair of sets.

## 样例 #1

### 输入

```
3
4
2 1 10
3 1 3 5
5 5 4 3 2 1
3 10 20 30
3
4 1 2 3 4
4 2 3 4 5
4 3 4 5 6
2
3 1 3 5
3 4 3 2```

### 输出

```
2 3 
1 2 
-1```

# 题解

## 作者：sunset_breeze (赞：14)

##### [CF1468M Similar Sets](https://www.luogu.com.cn/problem/CF1468M)

我们设阈值为 $B$。

我们称**集合大小大于 $B$** 的集合为**大集合**，否则为**小集合**。

- 对于**大集合**，因为只有 $\frac{n}{B}$ 个，我们可以暴力枚举回答这 $\frac{n}{B}$ 个大集合。具体的，我们将每个大集合中元素标记为 $1$，然后再枚举每个集合，看是否具有至少两个标记即可。时间复杂度：$\mathcal O(\frac{n}{B}\times n)$。
- 对于**小集合**，我们只需处理小集合和小集合的贡献即可。那么我们枚举一个小集合中的二元组，收集其它小集合是否具有这个二元组的标记即可。时间复杂度：$\mathcal O(B^2 \times \frac{n}{B})$。证明：因为 $a^2+b^2 \le (a+b)^2$，所以最坏情况下肯定不会有集合大小小于 $B$，所以复杂度为 $\mathcal O(B^2 \times \frac{n}{B})$。

均衡一下，取 $B=\sqrt{n}$，即可达到 $\mathcal O(n \sqrt{n})$ 的优秀复杂度。

---

## 作者：agicy (赞：6)

本文将同步发布于：

- [洛谷博客](https://www.luogu.com.cn/blog/Lu-Anlai/solution-cf1468m)；
- [csdn](https://blog.csdn.net/Lu_Anlai/article/details/117731334)；
- [博客园](https://www.cnblogs.com/Lu-Anlai/p/14865604.html)；
- [简书](https://www.jianshu.com/p/5be99908c975)。

## 题目

题目链接：[洛谷](https://www.luogu.com.cn/problem/CF1468M)、[CF1468M](https://codeforces.com/problemset/problem/1468/M)。

### 题意简述

给定 $n$ 个集合 $S_{1\sim n}$，问是否存在 $i,j$ 满足 $i\neq j$ 且 $\left\lvert S_i\cap S_j\right\rvert\geq 2$。

若存在，输出 $i,j$（任意一对都可）；否则输出 $-1$。

$n\leq 10^5$，$\sum\limits_{i=1}^n\left\lvert S_i\right\rvert\leq 2\times 10^5$。

## 题解

### 图论转化

直接思考有点难，考虑经典套路，我们把这个问题转化成二分图模型。

对于一个集合 $S_i$，我们将其构造为一个左部点 $i$。

对于一个元素 $x$，我们将其构造为一个右部点 $x$。

如果 $x\in S_i$，那么图上有一条边 $(i,x)$。

那么 $\left\lvert S_i\cap S_j\right\rvert\geq 2$，就对应有至少两个右部点连到了同样的两个点。

换句话说，符合条件的答案对应了图中的一个四元环。

并且，这张图的度数总和为 $\sum\limits_{i=1}^n\left\lvert S_i\right\rvert$。

### 按点的度数分治

现在我们要解决的问题就是一个二分图内是否存在四元环。

这同样是一个简单的问题，具体地，我们考虑按点的度数分治：

- 找到一个非负整数 $B$；
- 称度数 $\geq B$ 的为大点，度数 $< B$ 的为小点；
- 对于大点，其个数为 $\Theta\left(\frac{\sum\texttt{deg}}{B}\right)$。

我们对于每个大左部点，标记其所有相连点，如果存在另一个左部点，其连接的标记点个数 $\geq 2$，那么存在一个四元环。

我们对于每个小左部点，我们枚举其对应的所有的右部点对，然后对于每一个点对，我们枚举其最小值，然后标记其对应点，如果一个点在之前被标记过，那么就存在一个四元环。

根据上面的分析，我们得出算法的时间复杂度为 $\Theta\left(\frac{\sum\texttt{deg}}{B}\sum\texttt{deg}+B\sum\texttt{deg}\right)$。

理论分析可以得出，最优的时间复杂度为 $\Theta\left(\sum\texttt{deg}\sqrt{\sum\texttt{deg}}\right)$。

### 参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;
const int MAXS=2e5+5;

struct Event{
	int x,y,id;
	inline Event(reg int x=0,reg int y=0,reg int id=0):x(x),y(y),id(id){
		return;
	}
};

struct Link{
	int val,id;
	inline Link(reg int val=0,reg int id=0):val(val),id(id){
		return;
	}
};

int n;

inline pair<int,int> solve(void){
	n=read();
	reg int sum=0;
	vector<vector<int>> S(n+1);
	vector<int> V;
	for(reg int i=1;i<=n;++i){
		reg int k=read();
		sum+=k;
		S[i].resize(k);
		for(reg int j=0;j<k;++j)
			S[i][j]=read(),V.push_back(S[i][j]);
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		for(int& x:S[i])
			x=lower_bound(V.begin(),V.end(),x)-V.begin();
	reg int m=V.size();
	reg size_t B=sqrt(sum/16);
	vector<int> Big,Sma;
	for(int i=1;i<=n;++i)
		if(S[i].size()>=B)
			Big.push_back(i);
		else
			Sma.push_back(i);
	vector<bool> vis(m);
	vis.resize(m);
	for(reg int i=0,siz=Big.size();i<siz;++i){
		int u=Big[i];
		for(int x:S[u])
			vis[x]=true;
		for(reg int j=1;j<=n;++j){
			int v=j;
			if(u!=v){
				reg int cnt=0;
				for(int x:S[v])
					if(vis[x])
						++cnt;
				if(cnt>=2)
					return make_pair(u,v);
			}
		}
		for(int x:S[u])
			vis[x]=false;
	}
	vector<Event> E;
	for(reg int i=0,siz=Sma.size();i<siz;++i){
		reg int u=Sma[i];
		for(reg int j=0,siz=S[u].size();j<siz;++j)
			for(reg int k=j+1;k<siz;++k)
				E.push_back(Event(S[u][j],S[u][k],u));
	}
	vector<vector<Link>> G;
	G.resize(m);
	for(Event e:E)
		if(e.x<e.y)
			G[e.x].push_back(Link(e.y,e.id));
		else
			G[e.y].push_back(Link(e.x,e.id));
	vector<int> from;
	from.resize(m);
	for(reg int i=0;i<m;++i){
		for(Link L:G[i])
			if(!from[L.val])
				from[L.val]=L.id;
			else
				return make_pair(from[L.val],L.id);
		for(Link L:G[i])
			from[L.val]=0;
	}
	return make_pair(-1,-1);
}

int main(void){
	reg int t=read();
	while(t--){
		static pair<int,int> ans;
		ans=solve();
		if(ans.first==-1)
			write(-1),putchar('\n');
		else
			write(ans.first),putchar(' '),write(ans.second),putchar('\n');
	}
	flush();
	return 0;
}
```


---

## 作者：whiteqwq (赞：4)

[CF1468M Similar Sets](https://www.luogu.com.cn/problem/CF1468M)解题报告：

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/15234586.html)

## 题意

定义两个集合相似当且仅当这两个集合有至少两个相同的元素，给定若干个集合，输出一对相似集合或者报告无解。

$1\leqslant \sum|S|\leqslant 2\times 10^5$。

## 分析

下面设 $m=\sum|S|$。

看到 2e5 考虑根号分治，设集合大小大于 $\sqrt m$ 的点为大集合，其余为小集合，那么对于每个大集合，我们标记它所有元素，并枚举每个集合判断，由于大集合只会有根号个，所以复杂度是 $O(m\sqrt m)$ 的。

对于每个小集合，我们枚举其中两个元素并记录下来，然后判断有没有重复的点对，精细实现以下就是 $O(m\sqrt m)$。（具体就是固定第一维，第二维用桶统计）

## 代码

实现需要精细一点，否则会爆空间。

```
#include<stdio.h>
#include<vector>
#include<map>
#include<math.h>
using namespace std;
const int maxn=100005,maxm=200005;
int T,n,m,B,x,y,tot,flg;
int vis[maxm];
vector<int>v[maxn];
vector< pair<int,int> >w[maxm];
map<int,int>mp;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n),mp.clear(),m=x=y=tot=flg=0;
		for(int i=1,k;i<=n;i++){
			scanf("%d",&k),m+=k,v[i].clear();
			for(int j=0,x;j<k;j++){
				scanf("%d",&x);
				if(mp[x]==0)
					mp[x]=++tot,vis[tot]=0,w[tot].clear();
				x=mp[x],v[i].push_back(x);
			}
		}
		B=sqrt(m)/2;
		for(int i=1;i<=n;i++){
			if(v[i].size()>B){
				for(int j=0;j<v[i].size();j++)
					vis[v[i][j]]=1;
				for(int j=1;j<=n;j++){
					if(j==i)
						continue;
					int cnt=0;
					for(int k=0;k<v[j].size();k++)
						cnt+=vis[v[j][k]];
					if(cnt>=2){
						flg=1,printf("%d %d\n",i,j);
						break;
					}
				}
				for(int j=0;j<v[i].size();j++)
					vis[v[i][j]]=0;
			}
			if(flg)
				break;
		}
		if(flg)
			continue;
		for(int i=1;i<=n;i++)
			if(v[i].size()<=B)
				for(int j=0;j<v[i].size();j++)
					for(int k=j+1;k<v[i].size();k++)
						w[min(v[i][j],v[i][k])].push_back(make_pair(max(v[i][j],v[i][k]),i));
		for(int i=1;i<=tot;i++){
			for(int j=0;j<w[i].size();j++){
				if(vis[w[i][j].first]){
					flg=1,printf("%d %d\n",vis[w[i][j].first],w[i][j].second);
					break;
				}
				vis[w[i][j].first]=w[i][j].second;
			}
			if(flg==1)
				break;
			for(int j=0;j<w[i].size();j++)
				vis[w[i][j].first]=0;
		}
		if(flg==0)
			puts("-1");
	}
	return 0;
}
```

---

## 作者：little_sun (赞：3)

### 题目大意

你有 $n$ 个序列，每个序列里有一些元素。每个序列中的元素互不相同，但不同序列中的元素可以相同。

定义两个序列 $A, B$ 是相似的，如果存在两个不同的整数 $x, y$ ，满足 $x, y \in A, x, y \in B$。

现在你要找出任意一对相似的序列，或者输出无解。

$1 \leq n, \sum k_i \leq 10^5$，其中 $k_i$ 表示第 $i$ 个序列的元素个数

### 题目分析

直接做不太好做，我们考虑根号分治。设 $m$ 表示 $\sum k_i$，考虑到 $m,n$ 在同一数量级，我们下文复杂度分析中的 $m$ 统一用 $n$ 代替。

首先我们考虑那些大小超过 $\sqrt n$ 的序列，枚举每一个大小超过 $\sqrt n$ 的序列。

考虑用一个桶存下这个序列中的所有元素，接着我们枚举所有其他序列，并检查有没有任何一个序列和当前序列有两个以上的数重复。

如果我们在一开始做一个离散化的话，每次操作的时空复杂度就是 $ \Theta (n)$ 的，考虑到最多有 $ \sqrt n $ 个这样的序列，这部分的时间复杂度为 $ n \sqrt n$ 。

然后我们再考虑那些大小小于 $ \sqrt m$ 的所有序列。枚举所有这些数列的所有元素对 $(x, y)$ ，并把它们存储下来。容易发现这样的元素对有

$ \sum_{k_i < \sqrt n} \frac{k_i \times (k_i - 1)}{2}$ 个，根据均值不等式知道总共有 $ \Theta (n \sqrt n)$ 个这样的数对，并且我们可以用 $n$ 个 $\texttt{vector}$ 在 $ \Theta (n \sqrt n)$ 的时间里检查是否有两对相同数对。

这样我们就有了一个对所有情况都有效的算法，总时间复杂度  $ \Theta (n \sqrt n)$。

### 代码

``` cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

#define R register
#define ll long long
#define pair std::pair<int, int>
#define mp(i, j) std::make_pair(i, j)
#define sum(a, b, mod) (((a) + (b)) % mod)
#define meow(cat...) fprintf(stderr, cat)

const int MaxN = 2e5 + 10;

int n, m, cnt, vis[MaxN];
std::vector<int> v, b, a[MaxN];
std::vector<pair> vec[MaxN];

void init()
{
    v.clear(), b.clear();
    memset(vis, 0, 4 * (m + 10));
    for (int i = 1; i <= n; i++)
        a[i].resize(1);
}

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}

signed main()
{
    int T = read();
    while (T--)
    {
        int flag = 0;
        n = read(), init();
        for (int i = 1; i <= n; i++)
        {
            a[i][0] = read(), m += a[i][0], a[i].resize(a[i][0] + 1);
            for (int j = 1; j <= a[i][0]; j++)
                a[i][j] = read(), b.push_back(a[i][j]);
            std::sort(++a[i].begin(), a[i].end());
        }
        m = sqrt(m) / 2, std::sort(b.begin(), b.end());
        b.erase(std::unique(b.begin(), b.end()), b.end());
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= a[i][0]; j++)
                a[i][j] = std::lower_bound(b.begin(), b.end(), a[i][j]) - b.begin() + 1;
                //  meow("%d%c", a[i][j], " \n"[j == a[i][0]]);
        for (int i = 1; i <= n; i++)
        {
            if (a[i][0] > m)
            {
                cnt = 0;
                memset(vis, 0, 4 * (b.size() + 10));
                for (int j = 1; j <= a[i][0]; j++)
                    vis[a[i][j]] = 1;
                for (int j = 1; j <= n; j++)
                    if (i ^ j)
                    {
                        cnt = 0;
                        for (int k = 1; k <= a[j][0]; k++)
                        {
                            vis[a[j][k]]++, cnt += (vis[a[j][k]] == 2);
                            if (cnt == 2 && !flag)
                            {
                                flag = 1, printf("%d %d\n", i, j);
                                break;
                            }
                        }
                        for (int k = 1; k <= a[j][0]; k++)
                            vis[a[j][k]]--;
                        if (flag) break;
                    }
            }
            else
                v.push_back(i);
        }
        memset(vis, 0, 4 * (b.size() + 10));
        for(int i = 1; i <= b.size(); i++)
            vec[i].clear();
        for(auto i : v)
        {
            for(int j = 1; j <= a[i][0]; j++)
                for(int k = j + 1; k <= a[i][0]; k++)
                    vec[a[i][j]].push_back(mp(a[i][k], i));
        }
        for(int i = 1; i <= b.size(); i++)
        {
            for(int j = 0; j < vec[i].size(); j++)
            {
                if(vis[vec[i][j].first] && !flag)
                {
                    printf("%d %d\n", vis[vec[i][j].first], vec[i][j].second);
                    flag = 1; break;
                }
                vis[vec[i][j].first] = vec[i][j].second;
            }
            if(flag) break;
            for (int j = 0; j < vec[i].size(); j++)
                vis[vec[i][j].first] = 0;
        }
        if(!flag) puts("-1");
    }
    return 0;
} 
```





---

## 作者：ABookCD (赞：1)

### I. CF1468M

简单根号分治。

令 $m=\sum k_i$。

选择按照序列长度分治，设一个长度阈值 $B$，则长度长于 $B$ 的只有至多 $\frac{m}{B}$ 条。

这一种，我们可以给每一个元素打标记，然后扫整个字典进行匹配。（也是最直接的暴力），复杂度 $O(\frac{m^2}{B})$。

再找一种基于 $B$ 的做法平衡时间复杂度。

考虑剩下的长度小于 $B$ 的序列，我们可以直接枚举二元组 $(i,j)$，并记录其属于第几个集合，然后遍历寻找答案即可，每一个集合复杂度 $O(B^2)$，总复杂度至多为 $O(n B^2)=O(mB)$。

我们取 $B=\sqrt m$ 即可。

不卡常。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int k[200010];
vector<int> g[200010];
int B;
map<int,int> mp;
int tot;
int vis[200010];
int n;
struct node{
	int mx,id;
}; 
vector<node> e[200010];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
//根号分治 平衡时间复杂度 简单题。 
int main(){
	int t;
	t=read();
	while(t--){
		mp.clear();
		tot=0;
		n=read();
		for(int i=1;i<=n;i++) g[i].clear();
		int cnt=0;
		bool tg=0;
		for(int i=1;i<=n;i++){
			k[i]=read();
			cnt+=k[i];
			for(int j=1;j<=k[i];j++){
				int x;
				x=read();
				if(mp[x]==0){
					mp[x]=++tot;
				}
				x=mp[x];
				g[i].push_back(x);
			}
		}
		for(int i=1;i<=tot;i++) e[i].clear(),vis[i]=0;
		B=sqrt(cnt);
		for(int i=1;i<=n;i++){
			if(k[i]>=B){
				for(int j=0;j<k[i];j++) vis[g[i][j]]=1;
				for(int j=1;j<=n;j++){
					if(j==i) continue;
					int tmp=0;
					for(int p=0;p<k[j];p++){
						if(vis[g[j][p]]) tmp++;
					}
					if(tmp>=2){
						tg=1;
						printf("%d %d\n",i,j);
						break;
					}
				}
				for(int j=0;j<k[i];j++) vis[g[i][j]]=0;
			}
			if(tg) break;
		}
		if(tg) continue;
		for(int i=1;i<=n;i++){
			if(k[i]<B){
				for(int j=0;j<k[i];j++){
					for(int p=j+1;p<k[i];p++){
						e[min(g[i][j],g[i][p])].push_back(node{max(g[i][j],g[i][p]),i});
					}
				}
			}

		}
		if(tg) continue;
		for(int i=1;i<=tot;i++){
			for(auto v:e[i]){
				if(vis[v.mx]){
					printf("%d %d\n",vis[v.mx],v.id);
					tg=1;
					break;
				}	
				vis[v.mx]=v.id;
			} 
			if(tg==1) break;
			for(auto v:e[i]){
				vis[v.mx]=0;
			}
		}
		if(!tg) printf("-1\n");
	}
}
```

---

