# Columns Swaps

## 题目描述

You are given a table $ a $ of size $ 2 \times n $ (i.e. two rows and $ n $ columns) consisting of integers from $ 1 $ to $ n $ .

In one move, you can choose some column $ j $ ( $ 1 \le j \le       n $ ) and swap values $ a_{1, j} $ and $ a_{2, j} $ in it. Each column can be chosen no more than once.

Your task is to find the minimum number of moves required to obtain permutations of size $ n $ in both first and second rows of the table or determine if it is impossible to do that.

You have to answer $ t $ independent test cases.

Recall that the permutation of size $ n $ is such an array of size $ n $ that contains each integer from $ 1 $ to $ n $ exactly once (the order of elements doesn't matter).

## 样例 #1

### 输入

```
6
4
1 2 3 4
2 3 1 4
5
5 3 5 1 4
1 2 3 2 4
3
1 2 1
3 3 2
4
1 2 2 1
3 4 3 4
4
4 3 1 4
3 2 2 1
3
1 1 2
3 2 2```

### 输出

```
0

2
2 3 
1
1 
2
3 4 
2
3 4 
-1```

# 题解

## 作者：Pecco (赞：9)

如果某个数在同侧出现了两次，说明这两列必须一个换、一个不换；如果某个数在两侧分别出现一次，说明这两列必须都换或者都不换；其他情况无解。那么这可以用**种类并查集**维护。

具体地，开两倍大小的并查集。如果两列换/不换的状态相同，就`merge(a,b);merge(a+n,b+n);`如果状态不同，就`merge(a,b+n);merge(a+n,b);`。最后枚举每个连通块，如果编号小于等于$n$的元素个数$cnt$多过一半，则加上$cnt$，否则加上$n-cnt$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4e5 + 5;
int fa[MAXN];
int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        int n, x, a, b, ok = true;
        cin >> n;
        for (int i = 1; i <= n * 2; ++i)
            fa[i] = i;
        vector<vector<int>> P(n + 5), Q(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> x, P[x].push_back(i);
        for (int i = 1; i <= n; ++i)
            cin >> x, Q[x].push_back(i);
        for (int i = 1; i <= n; ++i)
        {
            if (P[i].size() == 2 && Q[i].size() == 0)
            {
                a = P[i].front(), b = P[i].back();
                merge(a, b + n);
                merge(a + n, b);
            }
            else if (P[i].size() == 0 && Q[i].size() == 2)
            {
                a = Q[i].front(), b = Q[i].back();
                merge(a, b + n);
                merge(a + n, b);
            }
            else if (P[i].size() == 1 && Q[i].size() == 1)
            {
                a = P[i].front(), b = Q[i].front();
                merge(a, b);
                merge(a + n, b + n);
            }
            else
            {
                ok = false;
                break;
            }
        }
        if (!ok)
        {
            cout << -1 << endl;
            continue;
        }
        vector<int> ans;
        vector<vector<int>> each(n * 2 + 5);
        for (int i = 1; i <= n; ++i)
            each[find(i)].push_back(i);
        for (int i = 1; i <= n; ++i)
            if (each[i].size() < each[i + n].size())
                ans.insert(ans.end(), each[i].begin(), each[i].end());
            else
                ans.insert(ans.end(), each[i + n].begin(), each[i + n].end());
        cout << ans.size() << endl;
        for (auto e : ans)
            cout << e << " ";
        cout << endl;
    }
    return 0;
}
```

---

## 作者：gyh20 (赞：5)

很好的一道题。

先判断所有的数是否构成两个全排列。

对于某一个数 $x$，判断它出现的两个位置（横列）是否相同，相同则两个纵列必须一个交换一个不交换，否则两个必须同时交换或同时不交换。

这就是一个 $2-SAT$ 模型！

把这个 $2-SAT$ 模型建出来之后，变成了对于每一个 $1\sim n$ 的 $i$，要么选 $i$，要么选 $i+n$，然后可达的点全部选。使得选中的大于 $n$ 的数最少。

根据上面的建图，我们发现这个图是对称的，且一定有解，也就是说，我们可以假设就选 $i$，然后一直找，计算到达点个数和大于 $n$ 点个数，如果超过一半则把路径上的点取反 $(i=i+n(i<=n),i=i-n(i>n))$。并打标记。

最后根据标记输出即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[800002],b[800002],ans,pos1[800002],pos2[800002],num[800002],vis[800002],tim,tot,q[800002],tp,cnt,head[800002];
struct edge{
	int to,next;
}e[3200002];
inline void add(re int x,re int y){
	e[++cnt]=(edge){y,head[x]};
	head[x]=cnt;
	e[++cnt]=(edge){x,head[y]};
	head[y]=cnt;
}
inline int inv(re int x){
	return x>n?x-n:x+n;
}
inline void dfs(re int x){//printf("%d\n",x);
	if(x>n)++tot;vis[x]=tim;q[++tp]=x;
	for(re int i=head[x];i;i=e[i].next)if((!vis[e[i].to])&&(!vis[inv(e[i].to)]))dfs(e[i].to);
}
int main(){
	t=read();
	while(t--){
		n=read();ans=0;cnt=0;
		for(re int i=1;i<=n*2;++i)pos1[i]=pos2[i]=num[i]=vis[i]=head[i]=0;
		for(re int i=1;i<=n;++i){
		a[i]=read();++num[a[i]];if(pos1[a[i]])pos2[a[i]]=i;else pos1[a[i]]=i;}
		for(re int i=1;i<=n;++i){
		a[i]=read();++num[a[i]];if(pos1[a[i]])pos2[a[i]]=i;else pos1[a[i]]=i;}
		bool ia=0;
		for(re int i=1;i<=n;++i)if(num[i]!=2)ia=1;
		if(ia){
			puts("-1");continue;
		}
		for(re int i=1;i<=n;++i){
			if(pos1[i]==pos2[i])continue;
			if((a[pos1[i]]==i)==(a[pos2[i]]==i))add(pos1[i],pos2[i]+n),add(pos2[i],pos1[i]+n);
			else add(pos1[i],pos2[i]),add(pos1[i]+n,pos2[i]+n);
		}
		for(re int i=1;i<=n;++i){
			if(!vis[i]&&!vis[inv(i)]){
			tim=i;tot=0;tp=0;
			dfs(i);
			if(tot>tp-tot){
				for(re int j=1;j<=tp;++j)swap(vis[q[j]],vis[inv(q[j])]);
				ans+=tp-tot;
			}
			else ans+=tot;
			}
		}
		printf("%d\n",ans);
		for(re int i=1;i<=n;++i)if(!vis[i])printf("%d ",i);puts("");
	}
}
```


---

## 作者：chenxia25 (赞：0)

>### [CF题目页面传送门](https://codeforces.com/contest/1385/problem/G)

>有一个$2\times n$的矩阵$a$，每个数在$[1,n]$内。要求若干次交换某一列的$2$个值，使得最后每行都是$1\sim n$的排列。求最小次数以及对应方案，或报告无解。本题多测。

>$\sum n\in[1,2\times 10^5]$。

首先，每个数出现的次数必须要是$2$，否则无解。

然后。看到排列想到图论。不难发现结论：若$\forall i\in[1,n]$，连有向边$(a_{1,i},a_{2,i})$，得到的图可以表示为一个排列当且仅当上下都是排列。证明的话，必要性可以用置换的乘积证，充分性xjb随便证即可（就是每个点入出度都为$1$，则在上下各出现过一次）。

那么，原操作相当于将一条边反向。考虑将原$a$的图建出来，不考虑方向依次考虑每个CC（环），然后可以整体调成$2$种方向，比个大小即可。对于CC大小为$1$和$2$需要讨论一下，有点烦？（当时差点讨论绝望了）

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
const int N=200000;
int n;
int a[N+1],b[N+1];
vector<pair<int,pair<int,int> > > nei[N+1];
int cnt[N+1];
bool vis[N+1];
vector<int> zero,one;
int st,to;
void dfs(int x){//找环 
	vis[x]=true;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i].X,z=nei[x][i].Y.X,xx=nei[x][i].Y.Y;
		if(!vis[y]){
			if(x==st)to=y;
			dfs(y);
			if(xx)one.pb(z);else zero.pb(z);
		}
	}
}
void mian(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)cnt[i]=0,nei[i].clear(),vis[i]=false;
	for(int i=1;i<=n;i++)scanf("%d",a+i),cnt[a[i]]++;
	for(int i=1;i<=n;i++)scanf("%d",b+i),cnt[b[i]]++;
	for(int i=1;i<=n;i++)if(cnt[i]!=2)return puts("-1"),void();//判无解 
	for(int i=1;i<=n;i++)nei[a[i]].pb(mp(b[i],mp(i,1))),nei[b[i]].pb(mp(a[i],mp(i,0)));//建图 
	vector<int> ans;
	for(int i=1;i<=n;i++)if(!vis[i]){
		one.clear(),zero.clear(),st=i,dfs(i);
		if(one.empty()&&zero.empty())continue;//大小为1 
		if(nei[st][0].X==nei[st][1].X){//大小为2 
			if(nei[st][0].Y.Y==nei[st][1].Y.Y)ans.pb(nei[st][0].Y.X);
			continue;
		}
		int id=nei[st][0].X==to?1:0;
		if(nei[st][id].Y.Y)zero.pb(nei[st][id].Y.X);else one.pb(nei[st][id].Y.X);
		if(one.size()<zero.size())for(int i=0;i<one.size();i++)ans.pb(one[i]);
		else for(int i=0;i<zero.size();i++)ans.pb(zero[i]);//比大小压进答案序列 
	}
	printf("%d\n",int(ans.size()));
	for(int i=0;i<ans.size();i++)printf("%d ",ans[i]);
	puts("");
}
int main(){
	int testnum;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

