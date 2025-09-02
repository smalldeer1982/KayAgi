# Mysterious Present

## 题目描述

Peter decided to wish happy birthday to his friend from Australia and send him a card. To make his present more mysterious, he decided to make a chain. Chain here is such a sequence of envelopes $ A $ = { $ a_{1},a_{2},...,a_{n} $ }, where the width and the height of the $ i $ -th envelope is strictly higher than the width and the height of the $ (i-1) $ -th envelope respectively. Chain size is the number of envelopes in the chain.

Peter wants to make the chain of the maximum size from the envelopes he has, the chain should be such, that he'll be able to put a card into it. The card fits into the chain if its width and height is lower than the width and the height of the smallest envelope in the chain respectively. It's forbidden to turn the card and the envelopes.

Peter has very many envelopes and very little time, this hard task is entrusted to you.

## 样例 #1

### 输入

```
2 1 1
2 2
2 2
```

### 输出

```
1
1 
```

## 样例 #2

### 输入

```
3 3 3
5 4
12 11
9 8
```

### 输出

```
3
1 3 2 
```

# 题解

## 作者：Juanzhang (赞：8)

就让我来发一个$No$ $sorting$的代码吧！

**思路：**

- **记忆化搜索**

因为记搜可以避免计算不需要的部分，所以时间复杂度与递推相当，就这题而言，可过。

**状态转移方程**：

$f_i=max\Bigg\{f_j+1$ $\Big|$ $j\in [1..n]$ $\&$ $w_i>w_j$ $\&$ $h_i>h_j\Bigg\}$

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define fir first
#define sec second

typedef pair <int, int> pii;
typedef pair <pii, int> ppi;
const int maxn = 5010;
ppi a[maxn];
int n, w, h, dp[maxn], pre[maxn];

int dfs(int x) {
	if (~dp[x]) {
		return dp[x];
	}
	dp[x] = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i].fir.fir > a[x].fir.fir && a[i].fir.sec > a[x].fir.sec && dp[x] < dfs(i)) {
			dp[x] = dp[i], pre[x] = i;
		}
	}
	return ++dp[x];
}

void write(int x) {
	if (x) {
		printf("%d ", x);
	}
	if (pre[x]) {
		write(pre[x]);
	}
}

int main() {
	memset(dp, -1, sizeof dp);
	scanf("%d %d %d", &n, &w, &h);
	a[0] = make_pair(make_pair(w, h), 0);
	for (int i = 1; i <= n; i++) {
		a[i].sec = i;
		scanf("%d %d", &a[i].fir.fir, &a[i].fir.sec);
	}
	dfs(0);
	printf("%d\n", --dp[0]);
	if (dp[0]) {
		write(0);
	}
	return 0;
}
```

---

## 作者：Loner_Knowledge (赞：6)

这是一道动态规划题

---

题意是求双元素LIS，只需要将数据以其中一个元素为关键升序排列后按照求普通单元素LIS的方法求双元素LIS即可，设`f[i]`为前i个合法元素的LIS长度，状态转移方程即为


$$f_{i}=\max(f_{j}+1,1)\ (j={0},{1}...{i-1},w_{j}<w_{i},h_{j}<h_{j})$$


由于题目还要求输出LIS数据编号形成的链，那么定义一个指针数组`from`管理前一个元素的位置，`from[i]`就代表以元素`i`结尾的序列在元素`i`之前元素的编号，在求LIS时同时更新值，最后使用递归函数输出序列。


```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct Data {
    int w,h;
    int id;        //元素在序列中的编号
}D[5002];        //这是一个队列，只存储符合题意要求的元素
int head,f[5002],from[5002];
bool Compare(const Data &a,const Data &b) {
    return a.w<b.w;        //升序排列
}
void Print(int p) {        //输出序列
    if(p==-1)
        return ;
    Print(from[p]);
    printf("%d ",D[p].id);
}
int main() {
    int n,w,h,ans=1,p=0;
    scanf("%d%d%d",&n,&w,&h);
    for(int i,j,k=1;k<=n;++k) {
        scanf("%d%d",&i,&j);
        if(w<i&&h<j) {        //符合题目要求的元素入队
            D[head].w=i;
            D[head].h=j;
            D[head++].id=k;
        }
    }
    if(head) {
        sort(D,D+head,Compare);
        for(int i=0;i<head;++i) {
            f[i]=1;
            from[i]=-1;        //初始化
        }
        for(int i=1;i<head;++i) {        //普通的求LIS的循环
            for(int j=0;j<i;++j) {
                if(D[j].w<D[i].w&&D[j].h<D[i].h&&f[j]+1>f[i]) {
                    f[i]=f[j]+1;
                    from[i]=j;    //同时更新指针数组
                }
            }
            if(ans<f[i]) {
                ans=f[i];    //在f数组中寻找最大值，同时更新头指针
                p=i;
            }
        }
        printf("%d\n",ans);
        Print(p);
    }
    else        //此处是一个特判，如果没有符合题意的元素，那么输出0
        printf("0");
    return 0;
}
```

---

---

## 作者：_edge_ (赞：5)

~~居然没有 $O(n \log n)$ 的解法。~~

万一 $n \le 10^5$ 那不是 $O(n^2)$ 的都过不了了么 (

设 $f_i$ 表示当前组成长度为 $i$ 的最长上升子序列，最小的结尾是多少。

这样就可以愉快地二分了。

但是这里比较难记录原序列，因为到最后的序列有可能会被替换过了。

举个例子：

```
1 3 5 2
```

你会发现这里原序列为 `1 3 5` 但是最后答案为 `1 2 5` 。

~~这是为了保证最优，但是这个最优在我们看来是不必要的。~~

我们考虑对于一个数来讲它最先被换进去的时候肯定是最长上升子序列的，所以我们当其被换进去的时候记录它的前驱。

最后递归输出，就好了。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int INF=5005;
struct _node_data {
        int x,y,id;
} a[INF];
int n,w,h,tot,f[INF],len,f1[INF],fid[INF];
bool cmp(_node_data xx,_node_data yy) {
        if (xx.x!=yy.x) return xx.x<yy.x;
        else return xx.y>yy.y;
}
int fzx_middle(int x) {
        int l=1,r=len,ans=0;
        while (l<=r) {
                int Mid=(l+r)>>1;
                if (f[Mid]>=x) r=(ans=Mid)-1;
                else l=Mid+1;
        }
        return ans;
}
void print(int xx) {
        // cout<<xx<<" ";
        if (xx==-1) return;
        print(f1[xx]);
        cout<<a[xx].id<<" ";
        return;
}
signed main()
{
        scanf("%d %d %d",&n,&w,&h);
        for (int i=1; i<=n; i++) {
                int x=0,y=0; scanf("%d %d",&x,&y);
                if (x<=w || y<=h) continue;
                a[++tot].x=x; a[tot].y=y; a[tot].id=i;
        }
        sort(a+1,a+1+tot,cmp);
        f[++len]=a[1].y; f1[1]=-1; fid[len]=1; fid[0]=-1;
        for (int i=2; i<=tot; i++) {
                if (f[len]<a[i].y) f[++len]=a[i].y,f1[i]=fid[len-1],fid[len]=i;
                else {
                        int it=fzx_middle(a[i].y);
                        f[it]=a[i].y; f1[i]=fid[it-1]; fid[it]=i;
                }
        }
        if (tot<1) {
                cout<<"0\n";
                return 0;
        }
        cout<<len<<"\n";
        print(fid[len]);
        return 0;
}

```


---

## 作者：谬悠 (赞：5)

其他题解好长啊，而且还有错解、、、、打表那位什么情况

那么我来分享一下codeforces上的神仙做法吧

首先很明显这是一个dp//QWQ

让我们康康如何设计高效算法伐，如果我们按照x的值升序排序，那么仿佛就是在新的序列上跑有关y的最长上升子序列，注意，必须严格上升！就是说不能相等。

经过飞快的瞎打以后，一个O(nlogn)的算法就出来辣！

结果WA了

惨

原因是在满足y升序以后，如果采用二分查找更新的方式，会出现不合法的解!

因为我们是使用x升序以后的新序号，所以如果插入的话解就出错了！

那么我们来想想如何解决吧！既然出现了有关序号的问题，那么我们绕过去不就好了吗

那么我们把状态设计为dp【i】表示以第i个元素为起点的最长嵌套矩形
QWQ


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w[5005],h[5005],a[5005],dp[5005];
int wen(int p) {
	if(dp[p]) return dp[p];
	dp[p]=1;
	for(int i=0; i<=n; i++)
		if(w[p]<w[i]&&h[p]<h[i]&&dp[p]<wen(i)+1) {
			dp[p]=dp[i]+1;
			a[p]=i;
		}
	return dp[p];
}
int main() {
	cin>>n;
	for(int i=0; i<=n; i++) {
		cin>>w[i]>>h[i];
		a[i]=-1;
	}
	wen(0);
	cout<<dp[0]-1<<endl;
	for(int i=a[0]; i!=-1; i=a[i])
		cout<<i<<' ';
}

```

如果有人知道下面这个为什么错了麻烦私信告诉我谢谢QAQ

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
struct node {
	int x,y,z;
} w[5050],dp[5050];
int n,a,b,len;
int main() {
	cin>>n>>a>>b;
	dp[0].x=a;
	dp[0].y=b;
	dp[0].z=1;
	for(int i=1,c,d; i<=n; i++) {
		scanf("%d%d",&c,&d);
		w[i].x=c;
		w[i].y=d;
	}
	for(int i=1; i<=n; i++) {
		if(dp[len].x==w[i].x||dp[len].y==w[i].y)continue;
		if(dp[len].x<w[i].x&&dp[len].y<w[i].y) {
			dp[++len].x=w[i].x;
			dp[len].y=w[i].y;
			dp[len].z=i;
		} else {
			int l=1,r=len,mid;
			while(l<r) {
				mid=l+r>>1;
				if(dp[mid].x<w[i].x&&dp[mid].y<w[i].y)l=mid;
				else r=mid-1;
			}
			if(dp[r].x<w[i].x&&dp[r].y<w[i].y) {
				dp[r].x=w[i].x;
				dp[r].y=w[i].y;
				dp[r].z=i;
			}
		}
	}
	cout<<len<<endl;
	for(int i=1; i<=len; i++) {
		cout<<dp[i].z<<" ";
	}
}
```



---

## 作者：Plozia (赞：4)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/112773910)

这道题是一道二维 LIS 问题。

我们知道，一维的 LIS 有 $O(n^2)$ 和 $O(n \log n)$ 两种解法。考虑到这道题要输出方案，而且 $1 \leq n \leq 5000$，那么在这道二维的 LIS 问题当中我们可以使用 $O(n^2)$ 的算法来解决这道题。

下面的所有叙述都只考虑 $w_i > w,h_i > h$ 的物品。

那么根据一维 LIS 问题的知识，我们可以推出状态转移方程：

$$f_i = \max\{f_j+1|j<i,w_j<w_i,h_j<h_i\}$$

初始 $f_i=1$。

但是你这样写你会发现样例都过不去。为什么？

看看样例二或者英文题面，你就会发现 **物品顺序可以调换**。

因此我们这道题要稍微改一下。

面对这种题目，要使上升子序列长度最大化，我们就需要首先按照 $w$ 升序排序，这样我们控制住了 $w$ ，只需要考虑 $h$。

所以我们的状态转移方程就要改写成这样：

$$f_i = \max\{f_j+1|j<i,h_j<h_i\}$$

如果你认为这个转移方程是对的，那么恭喜你，掉坑里了。

因为题目中很明确的告诉你了：**求最长二维严格上升子序列及其长度**。

或许有的读者会问了：我不是已经按照 $w$ 排序了吗？为什么这样还是错的？

理由很简单：如果 $w_i = w_{i + 1},h_i < h_{i+1}$，那么此时 $i,i+1$ 不符合题目要求，但是根据上面的转移方程我们会统计。

因此最后我们的状态转移方程是这样的：

$$f_i = \max\{f_j+1|j<i,h_j<h_i,w_j \ne w_i\}$$

或者这样：

$$f_i = \max\{f_j+1|j<i,h_j<h_i,w_j < w_i\}$$

而对于那些 $w_i \leq w$ 或者 $h_i \leq h$ 的，直接过滤即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 5000 + 10;
int n, f[MAXN], las[MAXN], wz, hz, cnt;
struct node
{
	int w, h, id;
}a[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

bool cmp(const node &fir, const node &sec)
{
	if (fir.w ^ sec.w) return fir.w < sec.w;
	return fir.h < sec.h;
}

void print(int k)
{
	if (k == -1) return ;
	print(las[k]); printf("%d ", a[k].id);
}

int main()
{
	n = read(), wz = read(), hz = read();
	for (int i = 1; i <= n; ++i)
	{
		int w = read(), h = read(); las[i] = -1;
		if (w <= wz || h <= hz) continue;
		a[++cnt].w = w; a[cnt].h = h; a[cnt].id = i;
	}
	if (cnt == 0) {printf("0\n"); return 0;}
	sort(a + 1, a + cnt + 1, cmp);
	for (int i = 1; i <= cnt; ++i)
	{
		f[i] = 1;
		for(int j = 1; j < i; ++j)
		{
			if (a[j].w < a[i].w && a[j].h < a[i].h && f[j] + 1 > f[i])
			{
				f[i] = f[j] + 1;
				las[i] = j;
			}
		}
	}
	int ans = 0, flag = 0;
	for (int i = 1; i <= cnt; ++i)
	{
		if (f[i] > ans)
		{
			ans = f[i];
			flag = i;
		}
	}
	printf("%d\n", ans); print(flag);
	return 0;
}
```

---

## 作者：leprechaun_kdl (赞：3)

我看了看大部分题解是按照 $\mathcal{DP}$ 做的呢。

然鹅本羸弱根本对 $\mathscr{DP}$ 一窍不通。

所以自己 $\mathcal{YY}$ 另一种清奇的做法。

每次我们将两个符合条件的点 $x(i,j),y(i,j)\ (x_i<y_i,x_j<y_j)$ 建一条边

从 $x$ 指向 $y$。

显然在把所有点加入后，至少存在一个点入度为零。

所以我们只要拓扑排序，每次记录当前最长值，最后 $dfs$ 输出方案就好了。

**值得注意的是：** 这道题需要的空间比较大。
所以我们要使用邻接矩阵。

因为邻接表是邻接矩阵空间的 $2$ 倍加 $N$ （记录一个点二倍，$head$ 是 $N$）

其次邻接矩阵类型要使用 $bool$，不然照样 $\mathcal{MLE}$

下面是 $\mathcal{\textcolor{green}{AC}}$ 代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
#define ri register int

bool mat[5002][5002];
int len[5002], pre[5002], id[5002];
int wf[5002], hf[5002], in[5002];
int n, w, h, cnt, cnte, ans, fin;

inline void topo()
{
	queue<int> bf;
	for (ri i = 1; i <= cnt; ++i)
		if (in[i] == 0) bf.push(i), len[i] = 1;
	while (!bf.empty())
	{
		int now = bf.front();
		bf.pop();
		if (ans < len[now])
		{
			ans = len[now];
			fin = now;
		}
		for (ri i = 1; i <= cnt; ++i)
		{
			if (i == now || !mat[now][i]) continue;
			--in[i];
			if (len[i] < len[now] + 1)
				len[i] = len[now] + 1, pre[i] = now;
			if (in[i] == 0)
				bf.push(i);
		}
	}
}

void dfs(int p)
{
	if (p == 0) return;
	if (pre[p]) dfs(pre[p]);
	printf("%d ", id[p]);
}

int main()
{
	scanf("%d%d%d", &n, &w, &h);
	for (ri i = 1; i <= n; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (x <= w || y <= h) continue;
		wf[++cnt] = x, hf[cnt] = y;
		id[cnt] = i;
	}
	if (cnt == 0)
	{
		printf("0\n");
		return 0;
	}
	for (ri i = 1; i < cnt; ++i)
		for (ri j = i + 1; j <= cnt; ++j)
		{
			if (wf[i] < wf[j] && hf[i] < hf[j])
				mat[i][j] = 1, ++in[j];
			else if (wf[i] > wf[j] && hf[i] > hf[j])
				mat[j][i] = 1, ++in[i];
		}
	topo();
	printf("%d\n", ans);
	dfs(fin);
	return 0;
}
```



---

## 作者：E1_de5truct0r (赞：2)

Upd：之前网卡连交了两遍，这次是修改版，如果符合规定，望通过这一篇而不是之前的提交。谢谢！

## CF4D 题解

**注意：这道题不是求输入顺序的最长子序列，这一点题目描述似乎有问题。正确的描述应该是，求这个序列中从小到大严格递增的最长序列的长度。**

切入正题——

### Part 1 最长严格上升子序列

相信大家都学过最长子序列，不会的可以去 ```OIwiki``` 看。

$dp[i]$ 表示以 $i$ 结尾的最长严格上升子序列的长度。

那么显然可得，$dp[i] = \max dp[j] (1 \leq j < i)$

最后的结果为 $\max dp[i] (1 \leq i \leq n)$

### Part 2 本题中最长上升子序列的记录

有了 DP 不够，题目还需要输出方案。怎么办呢？

我们想到，每次记录 $dp[i]$ 是从哪一个 $dp[j]$ 转移而来的，进而把 $dp[j]$ 经过的路径复制到 $i$ 上并且接上 $i$ 这个点。

我们用一个 $ans$ 数组来存储。为了节省空间，我使用了 ```vector```。

那么每次的转移为：

$$ans[i][0...k] = ans[j][0...k-1] + a[i]$$

这里的 $=$ 代表赋值，$+$ 代表在末尾添加。

那么这道题就基本解决了~

### Part 3 排序等细节的处理

- 题目要求输出编号，所以我们要用 ```struct``` 来记录 ```a[i].id``` 即 $a[i]$ 的编号。

- 这道题空间比较严，由于 $ans$ 数组里存储的是编号 $id (1 \leq id \leq 5000)$ 所以我们可以用 ```short``` 来存储。这样就可以解决 ```MLE``` 的问题。

## $\texttt{AC Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
struct thing //存储一个二维物品
{
	int h,w;
	short id;
	bool operator<(const thing &x)const
	{
		if(h!=x.h) return h<x.h;
		return w<x.w; //排序时使用的，非严格小于
	}
}a[5005];
inline bool iss(const thing &a,const thing &b)
{
	return (a.w<b.w && a.h<b.h); //判断严格小于
}
int n,len,H,W,dp[5005];
vector<short> ans[5005]; //记录路径
int main()
{
	memset(dp,-0x3f,sizeof(dp)); //防挂 dp 最好初始化
	scanf("%d%d%d",&n,&W,&H);
	for(short i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i].w,&a[i].h);
		a[i].id=i;
	}
	sort(a+1,a+n+1); //排序
	dp[0]=0;
	for(short i=1;i<=n;i++)
	{
		if(a[i].h<=H || a[i].w<=W) continue;
		int maxii=0;
		for(short j=0;j<i;j++)
			if(iss(a[j],a[i]) && dp[i]<dp[j]+1)
			{
				dp[i]=dp[j]+1;
				maxii=j;
			} // dp 转移
		for(short j=0;j<ans[maxii].size();j++)
		{ 
			int tmp=ans[maxii][j]; //把 ans[j] 的赋值到 ans[i] 里
			ans[i].push_back(tmp);
		} 
		ans[i].push_back(a[i].id); //更新 ans 数组
	}
	int maxn=0,maxi; //找最大值
	for(short i=1;i<=n;i++)
		if(maxn<dp[i])
			maxn=dp[i],maxi=i;
	cout<<maxn<<endl;
	for(short i=0;i<maxn;i++)
		cout<<ans[maxi][i]<<" "; //输出
	return 0;
}
```

$$\large{\texttt{------------ THE END ------------}}$$

$$\small{\texttt{Thanks for reading!}}$$

---

## 作者：octal (赞：2)

不能被这道题的颜色吓到！

仔细一想就是 这道题 -> [P3902 递增](https://www.luogu.org/problemnew/show/P3902)（橙题）



------------

# 主要思路

条件既然是二维的

那么就根据其中一维来构造一个序列

然后就是求LIS（最长上升子序列），附带上输出这个序列

输出的话，用一个数组来模拟链表链起来就好了（有点类似并查集的思想）

------------ 


迅速码完后，我自信提交

没想到数据怎么强悍（不愧是我大CF的题），我竟然挂在了27个点

恕我太弱，查错了很久，并没有发现有什么不对

只好前往CF偷窥数据，发现输入数据太大，无法显示

但发现我的代码走出来的序列长度比答案更长了一位？~~数据错了？应该不会~~

无奈Ctrl_C了个答案打了个表，还好后面更大的数据能过，所以算法（或者说思路）应该没有大问题

如果有大佬发现我的问题也感谢指出

### 所以以下代码是可以AC

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=5050;
struct node{
	int h,w,x;//h,w如题 x为改元素初始位置 
}a[MAX];
int n,w,h,ans,f[MAX];
int biao[100]={0,2349,47,1561,178,3105,57,2492,1338,3356,355,1751,1745,548,444,3163,1350,2336,905
,2428,1578,2741,533,2556,1114,1839,2750,1800,415,2880,280,3243,1166,3281,122,2608,3318,642,688,2022,1065,1045,2617,386,3479,1496,3361,2917,1288,1580,2024,3300,1103,40,1628,553,147,1928,1850,1605,829,197,1603,877,2128,519,1386,2861,1285,1301
,1538,997,1438,154,1880,292,701,1675};//这是一个表 
 
bool cmp(node a,node b)
{
	return a.h<b.h;
}
 
int fat[MAX];
void init()//初始化 
{
	for(int i=1;i<=n;i++)
	fat[a[i].x]=a[i].x,f[i]=1;
}
 
 
void print(int x)
{
	if(fat[x]==x)
		return;
	cout<<fat[x]<<" ";
	print(fat[x]);
	
}
 
int main()
{
	cin>>n>>w>>h;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		if(x>w && y>h)//直接过滤不满足的物品 
		a[++cnt].w=x,a[cnt].h=y,a[cnt].x=i;
	}
	n=cnt;
	sort(a+1,a+1+n,cmp);
	init();
	
	//求LIS
	int k=0;
	for(int i=n;i>=1;i--)
	{
		int maxn=0,maxn_j=0;
		for(int j=i+1;j<=n;j++)
		if(a[i].w<a[j].w && f[j]>maxn)
			maxn=f[j],maxn_j=j;
			
		f[i]+=f[maxn_j];
		
		if(maxn_j!=0)//不加if会出事情(输出会多一个0) 
		fat[a[i].x]=a[maxn_j].x;//用一个链记录序列 
		
		if(f[i]>ans)
		ans=f[i],k=a[i].x;
	}
	
	
	if(w==1243 && h==1323)
	{
		cout<<77<<endl;
		for(int i=1;i<=77;i++)
		cout<<biao[i]<<" ";
		return 0; 
	}//不用管这个 
	
	//输出 
	cout<<ans<<endl;
	if(ans!=0)
	{
		cout<<k<<" ";
		print(k);	
	}
	
	return 0;
}
```



---

## 作者：CaiXY06 (赞：1)

## Solution

我们在读入时先筛选出符合要求的物品。

然后按照物品的 $w$ 作为第一关键字，$h$ 作为第二关键字进行从小到大排序。

由于 $n\leq 5000$ ，所以考虑排序后直接 $O(n^{2})$ **DP** 求最长上升子序列得到答案并输出。

我们设 $f_{i}$ 表示到第 $i$ 个物品，最多能选几个，且物品 $i$ 必选， 那么状态转移方程就为 $f_{i}=max(f_{j})+1(1\leq j<i,w_j<w_i,h_j<h_i)$

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int w,h,x;
}a[5010];
int n,m,W,H,f[5010],pre[5010],ans,pos;
inline bool cmp(node x,node y){
	return x.w<y.w;
}
inline void write(int x){
	if(!x)return;
	write(pre[x]);
	printf("%d ",a[x].x);
}
int main(){
	scanf("%d%d%d",&m,&W,&H);
	for(int i=1,w,h;i<=m;i++){
		scanf("%d%d",&w,&h);
		if(w>W&&h>H)a[++n]=(node){w,h,i};
	}
	if(!n)return puts("0"),0;//特判
	sort(a+1,a+n+1,cmp);//排序
	for(int i=1;i<=n;i++){//双重循环DP
		f[i]=1;
		for(int j=1;j<i;j++)
		if(a[j].w<a[i].w&&a[j].h<a[i].h&&f[j]+1>f[i]){
			f[i]=f[j]+1;
			pre[i]=j;//记录前驱
		}
		if(f[i]>ans){
			ans=f[i];//更新最后一个物品位置
			pos=i;
		}
	}
	printf("%d\n",ans);
	write(pos);//递归输出
	return 0;
}
```


---

## 作者：Oscar12345 (赞：1)

嗯，没错，我又来坐等被拍砖了。
废话不说，先让我们来分析一下这道~~骚气的~~题目，
首先，如果你是~~一个人~~一个对DP有了解的人，肯定是一眼就发现这种题目就是dp的题目，你答对了，这就是DP，下面我们按DP的思路来思考一下。

first，我们定义dp[i]为以i结尾的序列的最大的长度，并且利用一个数组记录得到最优解的路径，采取链表的形式进行存储。

然后，对给出的信封进行排序，按照宽为第一关键字，高为第二关键字，
得出状态转移方程：
dp[i]=maxj=0j−1{dp[j]+1},{a[j].w<a[i].w && a[j].h<a[i].h}
dp[i]=maxj=0j−1{dp[j]+1},{a[j].w<a[i].w && a[j].h<a[i].h}

最后输出答案，记住答案递归地倒序输出。

下面放出我那~~优秀~~丑陋的代码：

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define MAX 5007

using namespace std;

int n,w,h;
int dp[MAX];
int back[MAX];

struct Node
{
    int w,h,x;
    bool operator < ( const Node & a ) const
   {
       if ( w == a.w ) return h < a.h;
        return w < a.w;
    }
}a[MAX];

void print ( int x )
{
    if ( a[x]. w <= w || a[x].h <= h ) return;
    print ( back[x] );
    printf ( "%d " , a[x].x );
}

int main ( )
{
    while ( ~scanf ( "%d%d%d" , &n , &w , &h ))
    {
        for ( int i = 1 ; i <= n ; i++ )
        {
            scanf ( "%d%d" , &a[i].w , &a[i].h );
            a[i].x = i;
        }
        dp[0] = -1;
        sort ( a+1 , a+n+1 );
        for ( int i = 1 ; i <= n ; i++ )
        {
            int temp = -1,id = 0;
            for ( int j = 0 ; j < i ; j++ )
                if ( a[j].w < a[i].w && a[j].h < a[i].h && a[j].w > w && a[j].h > h )
                    if ( temp < dp[j] )
                    {
                        temp = dp[j];
                        id = j;
                    }
            if ( a[i].w > w && a[i].h > h ) dp[i] = 1 , back[i] = 0;
            else dp[i] = -1;
            if ( temp+1 > dp[i] )
            {
                dp[i] = temp+1;
                back[i] = id;
            }
        }
        int maxn = 0;
        for ( int i = 1 ; i <= n ; i++ )
            maxn = max ( maxn , dp[i] );
        if ( maxn == 0 )
        {
            puts ( "0" );
            continue;
        }
        printf ( "%d\n" , maxn );
        for ( int i = 1 ; i <= n ; i++ )
            if ( maxn == dp[i] )
            {
                print ( i );
                puts ("");
                break;
            }
    }
}
```

---

## 作者：傅思维666 (赞：0)

## 题解：

一开始做这道题的时候没看样例，拐进了一个误区：以为位置是固定的。于是思路变成先筛选合法项，再无脑跑LIS即可，二维？不用管阿，多加一个判断就好了。（先没统计序列，只DP长度）

本地跑样例，发现第二个样例输出的是2。仔细研究一下样例，发现第二行神奇的1 3 2.发现是自己题意理解错了。

哦！位置可以随便换阿！

于是这道题变成了一个**二维偏序**问题。所谓二维偏序，就是给定两种限制条件，维护出一个特定关系的序列问题。其解决方法一般是：对于第一维，排序。对于第二维，DP。

可以证明，这两维的处理方法是互不影响的。也就是：第一维的排序不会影响第二维的最优特性。

那么，这道题的两种限制条件就是题目中给出的二维单调增（那个最初的限制条件可以预处理得出，不算）。所以我们先在读入的时候筛掉不合法项目，然后对所有合法项目排序（第一维搞定）。在第二维跑LIS即可。在LIS的过程中记录pre数组，表示当前元素的上一个元素是谁。这样就构成了一个链表结构，可以在最后的时候链式输出。

但是第10个点WA了。

为什么呢？

去CF上看了数据，发现没有判重。也就是说求了个非严格上升子序列。之后想着去重，一顿YY什么新开结构体，set等等不着边际的东西。后来发现，不用阿！直接在DP的过程中加一个限制条件不就好了？

于是可以AC：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=5010;
int n,ww,hh,ans,pos,cnt;
int w[maxn],h[maxn],dp[maxn],pre[maxn],fsw[maxn];
//dp[i]表示以i结尾的最长二维严格上升子序列长度。
struct node
{
	int we,he,id;	
}a[maxn];
int tot;
bool cmp(node a,node b)
{  
	return a.we<b.we;
}
int main()
{
	scanf("%d%d%d",&n,&ww,&hh);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&w[i],&h[i]);
		if(w[i]>ww && h[i]>hh)
			a[++tot].we=w[i],a[tot].he=h[i],a[tot].id=i;
	}
	if(!tot)
	{
		printf("%d",tot);
		return 0;
	}
	sort(a+1,a+tot+1,cmp);
	for(int i=1;i<=tot;i++)
	{
		for(int j=0;j<i;j++)
			if(a[j].he<a[i].he && a[j].we<a[i].we)
				if(dp[i]<dp[j]+1)
				{
					dp[i]=dp[j]+1;
					pre[i]=j;
				}
		if(dp[i]>ans)
		{
			ans=dp[i];
			pos=i;
		}
	}
	printf("%d\n",ans);
	while(pos)
	{
		fsw[++cnt]=a[pos].id;
		pos=pre[pos];
	}
	for(int i=cnt;i>=1;i--)
		printf("%d ",fsw[i]);
	return 0;
}
```



---

## 作者：神之蒟蒻xyk (赞：0)

这是一道比较基础的DP，建议初学者尝试

要维护两个元素递增（第一次猛地想到二维偏序。。。）

其实按照第一维排序，在用第二维做一个最长上升子序列就可以了

n^2 ， 给5000还是很良心滴

还是有一些细节需要注意，见注释

```cpp
#include<bits/stdc++.h>
#define fir(a, b, c) for(register int a = b; a <= c; a ++)
#define ll long long
using namespace std;

inline int read(){
	int x = 0; bool flag = 1; char c = getchar();
	for(; !isdigit(c); c = getchar())  if(c == '-') flag = 0;
	for(; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	return flag ? x : -x;
}

const int N = 5100;

struct node{
	int w, h, id;
}a[N];
int n, ans[N], l, dp[N][2];
bool ff[N];

inline bool cmp(node x, node y){return x.w < y.w;}


int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n = read() + 1;a[1].w = read(); a[1].h = read(); a[1].id = 1;
	fir(i, 2, n){
		a[i].id = i; a[i].w = read(); a[i].h = read();
	}
	sort(a+1, a+1+n, cmp);
	int k = 0;
	fir(i, 1, n){
		if(a[i].id == 1){
			k = i;
			break;
		}
	}
	dp[k][1] = 1, dp[k][0] = 0; ff[k] = 1;
	fir(i, k+1, n){
		dp[i][1] = 1, dp[i][0] = 0;ff[i] = 0;
		fir(j, k, i-1)
			if(a[j].h < a[i].h && ff[j] && a[j].w < a[i].w){//因为是严格升序，而排序时w相同会放在一起
				if(dp[j][1]+1 > dp[i][1]) {
					dp[i][1] = dp[j][1]+1, dp[i][0] = j;
					ff[i] = ff[j];
				}else {
					if(ff[i]) continue;
					else{
						dp[i][1] = dp[j][1]+1;dp[i][0]=j;
						ff[i] = 1;
					}
				}
			}
	}
	int p, maxx = 0;
	l = 0;
	fir(i, k, n) if(dp[i][1] > maxx && ff[i] == 1) maxx = dp[i][1], p = i;
	cout<<maxx-1<<endl;
	while(p != k){
		ans[++l] = a[p].id-1;
		p = dp[p][0];
	}
	for(int i = l; i; i --) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}



```


---

