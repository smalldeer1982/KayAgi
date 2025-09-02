# Lost Root

## 题目描述

如果一个图是连通的且没有环，则称其为树。假设树以某个顶点为根，则当树满足每个节点要么是叶子节点（没有子节点），要么恰好有 $k$ 个子节点，并且所有叶子节点的深度都相同，则称其为完美 $k$ 叉树。

例如，下图展示了一个有 $15$ 个节点的完美二叉树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1061F/de3b5e14c77844d7d6fc27de5ae9982f4c3acaed.png)

现在有一棵包含 $n$ 个节点的完美 $k$ 叉树。节点被标记为 $1$ 到 $n$ 的不同整数，但你并不知道每个节点的具体标号。你需要找出树的根节点的标号。

你最多可以进行 $60 \cdot n$ 次如下类型的询问：

- "? $a$ $b$ $c$"：如果标号为 $b$ 的节点在从 $a$ 到 $c$ 的路径上，则返回 "Yes"，否则返回 "No"。

注意，$a$ 和 $c$ 本身也被认为在从 $a$ 到 $c$ 的路径上。

当你准备好报告树的根节点时，输出

- "! $s$"，其中 $s$ 是树根节点的标号。

你只能报告一次根节点，且该操作不计入 $60 \cdot n$ 次询问的限制。

## 说明/提示

示例中的树如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1061F/35da047bbd950ed349ebd6f2af925910ac0595d3.png)

示例输入输出展示了该测试的可能交互过程（空行仅为便于阅读）。

对应该示例的 hack 格式如下：

`<br></br>3 2<br></br>2 3 1<br></br>`

# 额外说明

我们称如下顺序为树的“自然顺序”：首先是树的根节点，然后是所有深度为 $1$ 的节点（从左到右），接着是所有深度为 $2$ 的节点（从左到右），依此类推，直到最大深度。

因此，hack 数据中的 $a_1$ 就是根节点的标号。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2

No

Yes
```

### 输出

```
? 1 3 2

? 1 2 3

! 2```

# 题解

## 作者：MatrixCascade (赞：11)

挺好玩的一个题，被 sh 带飞 ![](//啧.tk/kk)

看到 $n=1500$，次数限制 $60n$ 感觉不大像 5 log，因此考虑随机化算法。

注意到我们可以通过 $n$ 次操作实现一个 getdis 函数（询问树上某两个点的距离（也可以是两个点路径中的点数））。并且考虑到树上只有直径的形态是固定的，所以想着去把直径拉出来。

直径的两个端点必定是树上两个不同子树的叶子节点，并且 ，两个点的 $dis$ 值是 $2*dep+1$。

先计算出**二叉树**随机选出两个点是直径的概率，每个子树有 $\frac{n+1}{4}$ 个叶子结点，因此概率是 $\frac{1}{4}*\frac{1}{4}*2=\frac{1}{8}$ 基本上是随机 $30$ 次多一点就能随到了。

如果分叉数大于 $2$ 的话，概率显然比二叉树的概率更大。

拉出直径后，由于直径长度是 $\log$ 级别的，可以把直径上的点和端点的距离一一询问，如果 $dis$ 值是 $dep+1$ 那么就是根了。~~然而复杂度还是和 log 搭上了边~~

然后就做完了。

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define int long long
#define YES puts("YES")
#define NO puts("NO")
#define Yes puts("Yes")
#define No puts("No")
#define edl puts("")
#define mc cerr<<"qwq\n"
#define error goto gg
#define def gg:
#define rd(x) x=read()
#define opl(x) printf("%lld",x)
#define opls(x) printf("%lld ",x)
#define opd(x) printf("%d",x)
#define opds(x) printf("%d ",x)
#define ver(x) for(int i=head[x];i;i=nxt[i])
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define pu(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ft(x) for(int i=head[x];i;i=nxt[i])
#define upn up(i,1,n)
#define upm up(j,1,m)
#define pun pu(i,n,1)
#define pum pu(j,m,1)
#define up_(x) up(i,1,x)
#define pu_(x) pu(j,x,1)
#define ep emplace_back
#define fp for(auto to:
#define pf )
#define pii pair<int,int>
#define pis pair<int,string>
#define psi pair<string,int>
#define mkp make_pair
#define fi first
#define se second
#define mii map<int,int>
#define mis map<int,string>
#define msi map<string,int>
#define mvi map<vector<int>,int>
#define miv map<int,vector<int>>
#define rdn rd(n)
#define rdm rd(m)
#define rdk rd(k)
using namespace std;
int n, m, k;
int read()
{
    int s = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}

#define inf 1000000000000000000ll
ll Max(ll a=-inf,ll b=-inf,ll c=-inf,ll d=-inf,ll e=-inf,ll f=-inf,ll g=-inf,ll h=-inf)
{
	return max(max(max(a,b),max(c,d)),max(max(e,f),max(g,h)));
}
ll Min(ll a=inf,ll b=inf,ll c=inf,ll d=inf,ll e=inf,ll f=inf,ll g=inf,ll h=inf)
{
	return min(min(min(a,b),min(c,d)),min(min(e,f),min(g,h)));
}
#undef inf
vector<int>v;
int ask(int x,int y)
{
	v.clear();
	int ans=0;
	up(i,1,n)
	{
		printf("? %lld %lld %lld\n",x,i,y);fflush(stdout);
		string s;cin>>s;
		if(s=="Yes")++ans,v.ep(i);
	}
	return ans;
}
int ask2(int x,int y)
{
	int ans=0;
	up(i,1,n)
	{
		printf("? %lld %lld %lld\n",x,i,y);fflush(stdout);
		string s;cin>>s;
		if(s=="Yes")++ans;
	}
	return ans;
}
signed main()
{
	srand(time(0));
	int T=1;
	while(T--)
	{
		rdn;rdk;
		int dep=0;
		int nw=1;
		int sum=1;
		while(1)
		{
			nw*=k;sum+=nw;dep++;
			if(sum==n)break;
		}
	//	opl(dep);edl;
		int px,py;
		int kk=0;
		while(1)
		{
			++kk;
			px=rand()%n+1;py=rand()%n+1;
			while(px==py)py=rand()%n+1;
			int w=ask(px,py);
			//if(kk>50)assert(0);
			if(w==2*dep+1)
			{
				break;
			}
		}
		assert(kk<=30);
		fp v pf
		{
			if(to==px||to==py)continue;
			int w=ask2(px,to);
			++kk;
			if(kk>50)assert(0);
			if(w==dep+1)
			{
				cout<<"! "<<to<<endl;
				return 0;
			}
		}
	}
}
```


---

## 作者：CJZJC (赞：4)

先看这个查询，可以查一个点 `b` 是否在其他两个点 `x y` 的路径上。

简单思考一下，我们发现可以用 $n$ 次查询查出两点之间的路径上的点的数量和集合。

再发现题目给出的是一颗满 $k$ 叉树，可以发现叶子结点的个数 $>\lfloor \frac{n}{2} \rfloor$。

于是一个思路就出来了，我们每次在树上随出两个点，用 $n$ 次查询求出它们的距离。此时两个节点都是叶子结点的概率最少为 $\frac{1}{4}$，所以我们可以在比较少的次数内求出来。然后我们依次查询这两叶子路径上的所有点和其中一个叶子的距离（如图）。如果距离正好是深度，就说明这个点就是根。

![](https://cdn.luogu.com.cn/upload/image_hosting/pyy6451b.png)

AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 100010
int n,k;
bool f[N];
signed main(){
    mt19937 rd(time(0));
    cin>>n>>k;
    int dep=0,tmp=1;
    while(tmp<n){
        dep++;
        tmp=tmp*k+1;
    }
    for(int i=1;;i++){
        int x=rd()%n+1,y=rd()%n+1,sum=0;
        while(x==y){
            y=rd()%n+1;
        }
        for(int j=1;j<=n;j++){
            if(j==x||j==y){
                continue;
            }
            cout<<"? "<<x<<' '<<j<<' '<<y<<endl;
            string opt;
            cin>>opt;
            if(opt=="Yes"){
                sum++;
                f[j]=1;
            }
        }
        if(sum==dep*2-1){
            for(int i=1;i<=n;i++){
                if(f[i]){
                    int sum=0;
                    for(int j=1;j<=n;j++){
                        if(j==i||j==x){
                            continue;
                        }
                        cout<<"? "<<x<<' '<<j<<' '<<i<<endl;
                        string opt;
                        cin>>opt;
                        if(opt=="Yes"){
                            sum++;
                        }
                    }
                    if(sum==dep-1){
                        cout<<"! "<<i;
                        return 0;
                    }
                }
            }
        }
        else{
            for(int i=1;i<=n;i++){
                f[i]=0;
            }
        }
    }
}
```

---

## 作者：Computer1828 (赞：4)

根不好找，先尝试找叶子。

官方题解的 $20n$ 次查询很劣。考虑随便两个点 $u,v$，枚举 $t$，如果 `? u v t` 是 `Yes`，则让 $v \leftarrow t$。这样到最后就能得到其中一个叶子，并且这么做只要查询 $n$ 次。

有了一个叶子，然后考虑随机化找到另一个叶子，满足两叶子的树上路径长为 $2h-1$（$h$ 为树高），然后根就是这两个叶子树上路径的中点。这样随机一次找到另一个叶子的概率至少是 $\dfrac{1}{2}$。

前面节省了很多次查询，这里随便搞都能找到另一个叶子。

最后有了两个叶子，并且在找另一个叶子时可以顺便记录树上节点，这样只要枚举每个树上节点，看下它到两叶子距离是否相等即可，这一步是 $O(h^2)$ 的。

```cpp
#include<bits/stdc++.h>
#include<random> 
using namespace std;
mt19937 rnd(time(0));
int n,m,h;
char str[3];
int cnt,trenode[50005];
int main(){
	scanf("%d%d",&n,&m);
	int leaf = 2,totpnt = 0;
	for(h = 0;totpnt != n;++h) totpnt += pow(m,h);//算h
	for(int i = 3;i<=n;++i){//找叶子1
		printf("? 1 %d %d\n",leaf,i);fflush(stdout);
		scanf("%s",str);
		if(str[0] == 'Y') leaf = i;
	}
	int fael;
	while(true){//找叶子2
		while(true){
			fael = rnd()%n+1;
			if(fael != leaf) break;
		}
		int tot = 2;cnt = 0;
		for(int i = 1;i<=n;++i){
			if(i == fael || i == leaf) continue;
			printf("? %d %d %d\n",leaf,i,fael);fflush(stdout);
			scanf("%s",str);
			if(str[0] == 'Y') tot++,trenode[++cnt] = i;
		}
		if(tot == 2*h-1) break;
	}
	//fael->leaf
	for(int i = 1;i<=cnt;++i){//枚举树上节点
		int lsum = 0,rsum = 0;
		for(int j = 1;j<=cnt;++j){
			if(j == i) continue;
			printf("? %d %d %d\n",leaf,trenode[j],trenode[i]);fflush(stdout);
			scanf("%s",str);
			if(str[0] == 'Y') lsum++;
			printf("? %d %d %d\n",fael,trenode[j],trenode[i]);fflush(stdout);
			scanf("%s",str);
			if(str[0] == 'Y') rsum++;
		}
		if(lsum == h-2 && rsum == h-2){
			printf("! %d\n",trenode[i]);fflush(stdout);
			break;
		}
	}
	return 0;
}
```

---

## 作者：秋云暗几重 (赞：3)

#### 首先明确这是一个随机化的题  
~~不过交互题不都是随机吗2333~~

很容易想到取两个位于根的不同子树的两个叶子节点的$lca$

考虑有$n$个节点的满二叉树的情况:

共有$\frac{n+1}{2}$个叶子节点

这时如果我们随机取一对点，则取到的两个点均为叶子的概率约为$\frac{1}{2} * \frac{1}{2} = \frac{1}{4}$  
然后容易推出在子树的不同的根中的概率为$( \frac{1}{2} * \frac{1}{2} * 2 ) * \frac{1}{4} = \frac{1}{8}$

这个概率为所有$k$叉树中最小的一个,证明很简单这里不再赘述.

#### 怎么判断随机出了一对正确的点

假设我们随机出的点为$u$和$v$,树的深度为$dep$  

只需要对树上的点都询问一遍它是否在$u$到$v$的路径上,如果有$2 * dep -1 $个点在它们之间的路径上那么它们就是合理的一对点.  
这需要消耗$n$次询问.  
这样一来随机$50$次,就只有千分之一的概率随机不到这样的一对点.

#### 最后怎么找根

这时我们可以顺便记录一下$u$到$v$的路径上有哪些点.

对于路径上的任意一点$x$,如果在$x$到$u$(或者$v$)的路径上有$dep-1$个点,则$x$为$u$和$v$的$lca$,也就是根.  
注意只需要询问这条路径上的点是否在$x$到$u$(或者$v$)的路径上就可以了,其他的点问了也没用.

此题完结辣QAQ  
巨丑无比的代码

```cpp
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <time.h>
using namespace std;
#define il inline
const int N=2000;
int n,k,x,y,dep,now,sum,in[N];
char a[4];
il bool iflca(int t){
    now=0;
    for(int i=1;i<=sum;i++){
        if(in[i]==t) continue;
        printf("? %d %d %d\n",x,in[i],t);
        cin>>a;
        if(a[0]=='Y') now++;
    }
    return now==dep-2;
}
il void work(){
    sum=-1;
    while(sum!=(dep<<1)-3){
        sum=0;
        for(int i=1;i<=n;i++) in[i]=0;
        x=rand()%n+1;y=rand()%n+1;
        while(y==x) y=rand()%n+1;
        for(int i=1;i<=n;i++){
            if(i==x||i==y) continue;
            printf("? %d %d %d\n",x,i,y);
            cin>>a;
            if(a[0]=='Y'){sum++;in[sum]=i;}
        }
    }
    //for(int i=1;i<=sum;i++) printf("%d ",in[i]);
    for(int i=1;i<=sum;i++){
        if(iflca(in[i])){printf("! %d",in[i]);return;}
    }
}
int main() {
    srand((unsigned int)time(NULL));
    scanf("%d%d",&n,&k);
    dep=1;now=1;sum=1;
    while(sum<n){
        sum+=now*k;dep++;
        now*=k;
    }
    work();
    return 0;
}
```


---

## 作者：Sol1 (赞：2)

乱搞做法，失败率过高所以有一定概率过不了，想看正解可以参考其他题解（

考虑通过 **树上有多少条过某一个点的路径** 来区分树上点的深度。但是我们不能暴力统计，所以考虑 **随机抽样**。

我们发现对于较深的树，根节点和根的直接儿子的抽样成功的概率均大于 $\dfrac{1}{2}$，过浅的树可以特判。

所以对于每一个点抽取 $59$ 对点进行询问，如果路径上包含它的对数超过 $25$，则判定为深度 $\leq 2$，提取出所有这样的点以后，就可以简单地找到根的位置了。

交一下会发现在 $n=1023$，$k=2$ 的时候有很大概率萎掉。

计算一下，第 $3$ 层抽样成功的概率约为 $0.4$，根的概率非常接近 $0.5$，此时失败的概率较大，考虑缩小这一概率。

由于第 $4$ 层抽样成功的概率仅为 $0.2$，与 $0.4$ 差距较大，所以对于这种数据特殊设计算法：

取概率前 $7$ 大的，不随机抽样，而是暴力枚举所有可能，将成功数量不为 $0$ 的提取出来，得到根和两个直接儿子，暴力枚举出根即可。

虽然此时失误概率仍较大，但是已经可以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline bool Query(int u, int v, int x) {
	cout << "? " << u << " " << x << " " << v << endl;
	string s;
	cin >> s;
	return (s == "Yes");
}

int n, k;
vector <pair <int, int> > pAns;

inline void Prefix() {
	for (int i = 1;i <= n;i++) {
		int cnt = 0;
		for (int j = 1;j <= 59;j++) {
			int u = rand() % n + 1, v = rand() % n + 1;
			while (u == v || u == i || i == v) {
				u = rand() % n + 1; v = rand() % n + 1;
			}
			cnt += Query(u, v, i);
		}
		pAns.push_back(make_pair(cnt, i));
	}
}

inline void Solve() {
	if (k == 2 && n == 1023) {
		sort(pAns.begin(), pAns.end(), greater <pair <int, int> > ());
		pAns.resize(7);
		vector <int> pAns2;
		if (k == n - 1) {
			cout << "! " << pAns[0].second << endl;
			return;
		}
		for (int i = 0;i < 7;i++) {
			int cnt = 0;
			for (int j = 0;j < 7;j++) {
				for (int k = j + 1;k < 7;k++) {
					if (j == i || k == i) continue;
					cnt += Query(pAns[j].second, pAns[k].second, pAns[i].second);
				}
			}
			if (cnt == 9) {
				pAns2.push_back(pAns[i].second);
			}
		}
		assert(pAns2.size() == 3);
		if (Query(pAns2[0], pAns2[1], pAns2[2])) cout << "! " << pAns2[2] << endl;
		else if (Query(pAns2[0], pAns2[2], pAns2[1])) cout << "! " << pAns2[1] << endl;
		else if (Query(pAns2[2], pAns2[1], pAns2[0])) cout << "! " << pAns2[0] << endl;
	} else {
		sort(pAns.begin(), pAns.end(), greater <pair <int, int> > ());
		pAns.resize(k + 1);
		if (pAns.size() == 1) {
			cout << "! " << pAns[0].second << endl;
			return;
		}
		for (int i = 2;i < pAns.size();i++) {
			if (Query(pAns[0].second, pAns[1].second, pAns[i].second)) {
				cout << "! " << pAns[i].second << endl;
				return;
			}
		}
		if (Query(pAns[0].second, pAns[2].second, pAns[1].second)) cout << "! " << pAns[1].second << endl;
		else cout << "! " << pAns[0].second << endl;
	}
}

int main() {
	srand(unsigned(time(NULL)));
	cin >> n >> k;
	Prefix();
	Solve();
	#ifdef CFA_44
	while (1);
	#endif
	return 0;
}

```

---

## 作者：DJRzjl (赞：1)

# [CF1061F](https://www.luogu.com.cn/problem/CF1061F)  Lost Root

我们先可以通过 $n,k$ 算出树高 $h$。

如果只知道某个点在另外两点路径上，并不方便确定这些点具体的相对位置，所以可以考虑选择两个点，询问其他所有点是否在它们之间路径上，以此缩小根所在的范围。那么什么情况下可以缩小根的范围呢？

容易想到，当询问的 `a i c` $(i\in[1,n],i\not=a,c)$ 中 $a,c$ 恰好是根不同子树中的叶子节点时，会有 $2h-3$ 个节点在路径上，并且如果有 $2h-3$ 个点在 $a,c$ 路径上，也一定可以说明 $a,c$ 恰是根不同子树的叶子，此时两点的 $lca$ 就是根，故根就在这 $2h-3$ 个点组成的路径正中间，成功缩小了范围。

但我们并不知道如何取得这样的 $a,c$​，考虑随机化，先计算随机选择 $a,c$ 时，$a,c$​​ 恰是根不同子树的叶子的概率。

下面只讨论 $k=2$​ 二叉树的情况，可以发现在 $k$ 变大时，成功选到我们想要的 $a,c$ 的概率也会随之增大。

总共 $n$ 个点，大约有 $\frac n2$​（略大于）个叶子，根左右子树内分别有 $\frac n4$ 个叶子，随即情况下选到我们想要 $a,c$ 的情况约有 $\frac n4\times \frac n4=\frac{n^2}{16}$ 种，总共有 $\binom{n}{2}=\frac{n(n-1)}2$ 种情况，所以这个概率约等于 $\frac 1 8$。

那么我们随机个 $50$ 次，总共询问约 $50n$ 次，取不到想要的 $a,c$ 的概率大约是 $(\frac 78)^{50}\approx0.00126$，找不到的概率只有千分之一，$k>2$ 时这个概率则更小，这样一来我们就能成功将根的范围缩小到这条长 $2h-3$​​ 的路径上了。那么接下来如何找到根？

可以发现 $h$​ 肯定很小，最大不超过 $10$​，所以这 $2h-3$​​ 个点也很少，设它们构成点集 $S$​。我们依次枚举点 $u\in S$​，再依次枚举点 $v\in S(v\not=u)$​，询问 `a v u`，统计有多少 $v$ 在 $u$ 和 $a$ 路径上，若为 $h-2$ 则这个点 $u$ 就是我们要找的根。因为根在这些点正中间，所以它到叶子 $a$ 或 $c$ 路径中也就分别只有 $S$ 中 $h-2$​ 个点，并且也只有根满足这个性质。这些操作的步数远达不到 $10n$，于是可以通过本题。



## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;

char op[5];
int ask(int a,int b,int c){
	printf("? %d %d %d\n",a,b,c);
	fflush(stdout);
	scanf("%s",op+1);
	return op[1]=='Y';
}
vector<int>node;

int main(){
	srand(time(0));
	scanf("%d%d",&n,&k);
	int dep=1,s=1,base=k;
	for(;s<n;dep++,base*=k) s+=base; 
	int u,v;
	while(true){
		v=u=rand()%n+1;
		while(v==u) v=rand()%n+1;
		node.clear();
		for(int i=1;i<=n;++i){
			if(i==u||i==v) continue;
			if(ask(u,i,v)) node.push_back(i);
		}
		if((int)node.size()==2*dep-3) break;
	}
	for(auto t1:node){
		int sum=0;
		for(auto t2:node){
			if(t1==t2) continue;
			sum+=ask(u,t2,t1);
		}
		if(sum==dep-2){
			printf("! %d\n",t1);
			fflush(stdout);
			return 0;
		} 
	}
	return 0;
}
```


---

## 作者：快斗游鹿 (赞：1)

和官方题解不一样的做法。

考虑对于一个点 $x$，会有多少对 $(u,v)$ 满足 $x$ 在 $u$ 到 $v$ 的路径上，可以发现根节点与它的直系儿子数量最多。因此对每个点先进行随机化，随机两个点出来判断，则合法数量最多的前三个点，大概率是根节点或它的直系儿子，那只需要从这三个点中取出两个，如果存在一个 $i$ 在这两个点的路径上，$i$ 就是根。

但在 $k=2$，$n$ 较大时，第三层点的合法数量与第二层相近，随出来的概率相差不大，而第四层相差就比较大。对于这种情况，可以改成取前七个点出来，每个点判断它是否在其他六个点中任意两点路径上，如果都不在说明这是第三层的点，舍掉即可。这样正确率就有保证。

---

## 作者：wangyibo201026 (赞：0)

## solution

致敬传奇随机化交互题。

首先我们发现直接找根节点肯定不行，我们先思考如何找到叶子节点。

我们发现一个事情，考虑在 $k = 2$ 时，叶子节点个数量级大概是 $\frac{n}{4}$ 左右，我们随机两个点，很容易对于 $n$ 个点都查询一遍以此来判断他们的距离是否是两倍深度，大概随机 $40$ 次，我们就能够随机到两个叶子节点。

然后我们将在这两个叶子节点路径上的点拿出来，最多就是 $\log$ 级别的，然后我们挨个暴力查询距离即可。

查询次数大概是 $O(40n + n \log n)$ 级别，能过就行。

## code

code：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;
mt19937 rnd ( time ( 0 ) );

const int N = 1505;

int n, k, dep;
vector < int > ans;

int getdis ( int u, int v, int op ) {
	string res;
	int cnt = 0;
	if ( op ) {
		ans.clear ();
	}
	for ( int i = 1; i <= n; i ++ ) {
		if ( i != u && i != v ) {
			cout << "? " << u << " " << i << " " << v << '\n';
			cout << endl;
			cin >> res;
			cout << endl;
			cnt += ( res == "Yes" );
			if ( op == 1 && res == "Yes" ) {
				ans.push_back ( i );
			}
		}
	}
	return cnt + 1;
}

signed main () {
	cin >> n >> k;
	int sum = 1, suf = 1;
	while ( sum + suf * k <= n ) {
		dep ++;
		sum += suf * k;
		suf *= k;
	}
	int u = 0, v = 0;
	for ( int i = 1; i <= 60; i ++ ) {
		u = rnd () % n + 1, v = rnd () % n + 1;
		if ( getdis ( u, v, 1 ) == 2 * dep ) {
			break;
		}
	}
	for ( int x : ans ) {
		if ( getdis ( u, x, 0 ) == dep ) {
			cout << "! " << x << '\n';
			cout << endl;
			return 0;
		}
	}
	return 0;
}
```

---

