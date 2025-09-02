# [BalticOI 2018] 多角恋

## 题目描述

**题目译自 [BalticOI 2018](https://boi2018.progolymp.se/tasks/) Day1「[Love Polygon](https://boi18-day1-open.kattis.com/problems/boi18.polygon)」**

给一张 $N$ 个点的有向图，每个点的出度为 $1$。每次可以花费 $1$ 的代价修改图上的一条边的终点，也就是改变从一个点出发所到达的点。求最少需要花费多少代价，才能使这张图形成若干个两两不相交的二元环，并且图上的所有点都在某一个环里。

## 说明/提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/1ojydan1.png)

唯一的最优解如上图所示，图的上半部分为原图，底色为粉色的三个点为需要修改的边的起点；图的下半部分表示修改后的情况。

#### 样例 2 解释

存在多组最优解。其中一种是分别改变一条以 ``a``、``b`` 和 ``d`` 为起点的边，使他们分别连接到 ``b``、``a`` 和 `c`。

#### 样例 3 解释

图中有 $3$ 个点，无论如何修改边的终点，总会有一个人不在环里。


| 子任务 | 分值 | 数据范围 | 附加限制 |
|:----------:|:-------:|:-------------:|:-------------:|
|$1$|$21$|$2\leqslant N\leqslant 20$|.|
|$2$|$25$|$2\leqslant N\leqslant 100\, 000$|每个点都有一条入边（可能有自环）|
|$3$|$29$|$2\leqslant N\leqslant 100\, 000$|不存在两个点或更多个点构成的环|
|$4$|$25$|$2\leqslant N\leqslant 100\, 000$|.|



## 样例 #1

### 输入

```
8
leonard emmy
ada emmy
isaac leonard
emmy pierre
pierre bernhard
bernhard emmy
sofia karl
karl sofia```

### 输出

```
3
```

## 样例 #2

### 输入

```
4
a c
b c
c d
d d```

### 输出

```
3
```

## 样例 #3

### 输入

```
3
rocky scarlet
scarlet patrick
patrick rocky```

### 输出

```
-1
```

# 题解

## 作者：cc123321 (赞：9)

哎，我还是太弱了，一天偶然在办公室看都ZYC巨佬在看这个题目，身为一个小蒟蒻，当然要在大佬边上假装一起看。

然后我看了看这个毒瘤题，第一反应~~贪心~~。然后看着ZYC打开了LOJ的题解，我靠，什么子集动态规划，什么鬼。

然后放学的时候我跟kczno1大佬讲了讲我的想法，然后第二天他告诉我好像是对的。。。

然后我就来敲了一发，居然过掉了。。。

第一如果n是奇数，直接判-1；

定义nex[i]表示i的指向，如果i指向自己，那么就把nex[i] = 0；

use[i]表示i是否被用过；

deg[i]表示i点的入度；

先把已经构成那玩意儿的东西找出来。

然后算出剩下的deg；

每次选择入度为0的点，判断他的nex[]是否被用过。

如果nex[]被用过了，那就只把ans++；

否则看nex[]的入度是否为0，看看需不需要加入队列；

那么消到最后会剩下许多环（有可能也会没有），那么按照环的奇偶性判断一下需要加上多少答案就好了

（注意，代码里面长度为1的环已经判过了，所以就不用再判了）

由于输入比较~~恶心~~，所以我用了个map存；
```
#include<bits/stdc++.h>
#define maxn 500005
using namespace std;
inline int read()
{
	char x = getchar();
	int lin = 0, f = 1;
	while(x < '0' || x > '9')
	{
		if(x == '-') f = -1;
		x = getchar();
	}
    while(x >= '0' && x <= '9')
	{
		lin = lin * 10 + x - '0';
		x = getchar();
	}
	return lin * f;
}
map <string,int> mapp;
int n,tot,ans,u,v,nex[maxn],use[maxn],deg[maxn];
string a,b;
queue <int> q;
int sol(string s)
{
	if(!mapp.count(s))
		mapp[s] = ++tot;
	return mapp[s];
}
int solve(int pos)
{
	if(use[pos]) return 0;
	use[pos] = 1;
	return solve(nex[pos]) + 1;
}
#define PII pair<int,int>
#define fir first
#define sec second
#define ma(a,b) make_pair(a,b)
//PII ss[maxn];
int main(){
	n = read();
	if(n & 1)
	{
		printf("-1");
		return 0;
	}
	for(int i = 1; i <= n; i++)
	{ 
		cin >> a >> b;
		u = sol(a); v = sol(b);
		if(u != v)
			nex[u] = v;
	}
	use[0] = 1;//注意 
	for(int i = 1; i <= n; i++)//找出已经符合条件的东西 
		if(i == nex[nex[i]] && !use[i] && !use[nex[i]])
			use[i] = use[nex[i]] = 1;
	for(int i = 1; i <= n; i++)//处理deg 
		if(!use[i])
			++deg[nex[i]];
	for(int i = 1; i <= n; i++)
		if(!deg[i] && !use[i])
			q.push(i);
	while(q.size())//贪心 
	{
		int now = q.front(); q.pop();
		++ans;
		if(!use[nex[now]])
		{
			use[nex[now]] = 1;
			--deg[nex[nex[now]]];
			if(!deg[nex[nex[now]]] && !use[nex[nex[now]]])
				q.push(nex[nex[now]]);
		}
	}
	for(int i = 1; i <= n; i++)//判环 
		if(!use[i])
		{
			int k = solve(i);
			if(k <= 1) continue;
			if(k & 1) ++ans;
			ans += k / 2;
		}
	cout << ans;
}
```

---

## 作者：封禁用户 (赞：9)

# 「BalticOI2018D1T1」题解(译)
## ~~Love Arrow Shot~!~~
**题面：[BalticOI2018D1T1](https://boi18-day1-open.kattis.com/problems/boi18.polygon)**

简单来说，我们有一张有向图，其每一个顶点的出度都为1。我们的任务是用最少的步数改变一些边的终点，使得每个顶点都属于一个「点对」。这样的图，我们称为「 _Functional Graph_ 」

注意当$N$为奇数时，答案永远不存在。因此，如果$N$为奇数，我们可以立刻输出$-1$。

### 子任务 1
定义$G$为点集，$S$为$G$的子集，$T=G/S$。$S$是被「$\heartsuit-shot$」中的人的集合，我们必须满足以下条件。

- 如果我们移动始发点为$S$的边，图上每个连通分量最多只能有2个顶点，这是因为我们只能通过加边来实现最终的图，使得每个联通分量都有2个顶点。
- 因为在最终的图中，自恋是不允许的，因此在$T$中，没有一个自恋的人。

满足以上条件，可以随机将所有人拆散，以使得连通分量的大小为2。这样我们会用掉$|S|$支箭。因此，$S$为满足以上条件下，被「$\heartsuit-shot$」的人的集合

我们可以通过遍历整个集合$S$，找出最小的符合条件的集合$S^*$并且输出$|S^*|$。在$G$中，共有$2^N$个子集，检查每一个子集的复杂度为$O(N)$。那么总时间复杂度是$O(N2^N)$。

另一种方法是在子集上动态规划，时间复杂度同上。

### 子任务 2

每个人都只能被一个人爱。在这个子任务中，图中的每个连通分量都是一个环。我们可以分开处理每一个连通分量。定义$C$为连通分量中的顶点数，若$C$为偶数（若$C==2$，我们一支箭也不需要），只需要用$C/2$支箭。若$C$为奇数，把每两个顶点互相连接，把最后一个顶点和连通分量外的顶点连接，这样会用掉$\left \lfloor \frac{C}{2} \right \rfloor +1$支箭。时间复杂度为$O(N)$。

### 子任务 3

因为我们并没有任何一个「爱多边形( _Love Polygon_ )」，所以每一个连通分量中的环都会包含一个**自恋**的人，所以每一个连通分量的形式都是一个树，其中每一条边都指向它的树根。

我们定义在森林中顶点的集合$T$是_幸运_的当且仅当：

-  $T$中的每一个顶点的祖先都不在$T$中。
-  $T$中的每一个顶点的孩子都不在$T$中。
-  $T$中的每一个顶点的兄弟都不在$T$中。

定义$S^*$为在最优解中没有被「$\heartsuit-shot$」过的点的点集。显而易见，$S^*$肯定是_幸运_的。
集合中的每一个元素都会和他们最初爱上的元素_保持关系_，换句话说，他们将会和树上的祖先节点配对。定义$v$为$S^*$中的元素，那么
- $v$的祖先节点必须与「$\heartsuit-shot$」。因此$v$的祖先不在$S^*$里
- $v$的所有孩子都必须被「$\heartsuit-shot$」，要不然他们就必须和$v$配对，但我们知道$v$已经和他的祖先配对了，所以$v$的孩子不在$S^*$里。
- $v$的所有兄弟都必须被「$\heartsuit-shot$」，要不然他们就必须和$v$的祖先配对。但我们知道$v$已经和他的祖先配对了，所以$v$的兄弟不在$S^*$里。

因此，$S^*$是 _幸运_ 的。需要用掉$N-|S^*|$支箭。并且，给定一个不包含根 _幸运_ 的集合$S$，我们通过把$S$中的节点与他们的祖先配对，然后把其他人随机配对，我们可以构造出一个仅用$N-|S|$支箭的答案。因此，我们定$R$是 _幸运_ 的集合中不包含根的集合，这道题的答案就是:
$$\min \limits_{S \in R}(N-|S|)=B- \max \limits_{S \in R}|S| \qquad$$
我们的任务就是计算不包含根的最大 _幸运_ 集的大小。可以用动态规划解决问题。

定义$L_v$为顶点$v$的最初的爱人（也就是孩子），不包括顶点$v$自己，定义：
- $mls(v)$ 代表$v$的子树中的最大 _幸运_ 集的大小。（$v$本身不是）。
- $\overline{mls}(v)$ 代表$v$的子树中的最大 _幸运_ 集的大小。（$v$本身包含在内）

最大 _幸运_ 集的大小是$\sum mls(r)$。如果顶点$v$是个叶子节点，那么$mls(v)=0$且$\overline{mls}(v)=1$。令$v$是一个非叶节点，那么方程：$$\overline{mls}(v)=1+ \sum  \limits_{u \in L_v}(mls(u))$$
成立。在顶点$v$的子树中的不包含$v$自己的 _幸运_ 集可以满足以下条件的其中一个。
- 不包含$v$的任何一个孩子。他们中最大的 _幸运_ 集大小是$\sum _{u \in L_v}mls(u)$。
- 只包含$v$的一个孩子。最大的 _幸运_ 集包含$w$($v$的一个孩子)，大小为$(\sum _{u \in L_v}mls(u))+ \overline{mls}(w)-mls(w)$。

这样的 _幸运_ 存在，他们之中最大的 _ 幸运_  集的大小为：
$$\max\bigg\{\sum\limits_{u \in L_v}mls(u),\max\limits_{u \in L_v}\bigg(\bigg(\sum\limits_{u \in L_v}mls(u)\bigg)+\overline{mls}(w)-mls(w)\bigg)\bigg\}=$$

$$=\max\bigg\{\sum\limits_{u \in L_v}mls(u), \sum\limits_{u \in L_v}mls(u)+\max\limits_{u \in L_v}(\overline{mls}(w)-mls(w))\bigg\}=$$

$$=\max\bigg\{\overline{mls}(u)-1,\quad\overline{mls}(u)-1+\max\limits_{u \in L_v}(\overline{mls}(w)-mls(w))\bigg\}=$$

$$=\max\bigg\{0,\quad\max\limits_{u \in L_v}(\overline{mls}(w)-mls(w))\bigg\}+\overline{mls}(v)-1$$

因此，$$mls(v)= \max \limits_{w \in L_v} \bigg\{0,\quad\max\limits_{w \in L_v}(\overline{mls}(w)-mls(w))\bigg\}+\overline{mls}(v)-1$$

求一下和，对于任意一个顶点$v$：
$$ mls(v)= 0$$
当$v$是叶子节点时。

或：
$$mls(v)=\max\bigg\{0,\quad\max\limits_{w\in L_v}(\overline{mls}(w)-mls(w)\bigg\}+\overline{mls}(v)-1$$

并且
$$ \overline{\text{mls}}(v) = \begin{cases}1,\text{if }v\quad\quad\quad\quad\quad\text{ is a leaf;} \\ 1+\sum\limits_{u\in L_v}mls(u)\quad\text{otherwise}\end{cases} $$
通过这些递归式，遍历图中所有的连通分量，DFS，然后计算出所有顶点$v$的$\overline{mls}(v)$和$mls(v)$。

最后，以输出所有根节点$r$的$N-(\sum mls(r))$。由于每个节点只需要被遍历一遍，所以时间复杂度为$O(N)$。

### 子任务 4
其实和子任务3差不太多。分别处理每个联通分量。如果当前的环仅包含一个元素，那么和子任务3一样。如果环较长，我们选择一个任意元素。在最优解中，那个元素要不最终和它爱的人在一起，要不反之。不管哪种情况，都可以在分量中删掉一些边使得这个分量变成一个森林。这样，取在两种情况中，需要的箭的支数的最大值。时间复杂度为$O(N)$♥


---

## 作者：Endt (赞：3)

# Love Polygon-题解

贪心或基环树 DP，贪心码量小，容易想。

### 分析

$n$ 为奇数，直接 `-1`。

---

根据贪心的思想，已经是一对的就不要拆开了，把它们抠出来。对剩下的拓扑排序，如果一个点没有其它点指，就让它指的指它，然后把它俩扣出去；如果一个点指空气，就加入单身列表。

这样搞下来最后可能会剩几个环，我们随机选择环上的一个点开始，重复上面的操作即可。但深想一点就会发现，答案就是环中节点个数除以 $2$，并有可能剩下一个单身。

### 代码

```cpp
#include<bits/stdc++.h>

#define  Int  long long int
#define  Tem  template
#define  Pub  public

using std::min;using std::max;
using std::string;

int n;
string s,t;
int S,T;
class G{
Pub:
    int lover,dear;
}a[200005];
std::queue<int> q;//拓扑排序

std::unordered_map<string,int> h;//映射
int cnt;
int ans1,ans2,ans3;

int vis[200005];
int dfs(int x){
    if(a[a[x].dear].dear==0)vis[x]=1;
    if(vis[x])return 0;
    else vis[x]=1;
    return dfs(a[x].dear)+1;
}

int main(){
    scanf("%d",&n);
    if(n%2){//无解
        printf("-1");
        return 0;
    }
    for(int i=1;i<=n;++i){
        std::cin>>s>>t;
        if(h[s])S=h[s];
        else S=h[s]=++cnt;
        if(h[t])T=h[t];
        else T=h[t]=++cnt;
        a[S].dear=T;++a[T].lover;
    }
    for(int i=1;i<=n;++i){
        if(a[a[i].dear].dear==i&&a[i].dear!=i)
            a[i].dear=a[a[i].dear].dear=0;
        if(a[i].lover==0)q.push(i);
    }
    
    while(!q.empty()){
        int x=q.front();q.pop();
        if(a[x].dear==0)continue;
        if(a[a[x].dear].dear==0)++ans2;
        else{
            --a[a[a[x].dear].dear].lover;
            if(a[a[a[x].dear].dear].lover==0)q.push(a[a[x].dear].dear);
            a[x].dear=a[a[x].dear].dear=0;
            ++ans1;
        }
    }
    for(int i=1;i<=n;++i){
        ans3+=(dfs(i)+1)/2;
    }
    printf("%d",ans1+ans2+ans3);//改变所指、单身、环的答案和
    
    return 0;
}
```

---

## 作者：ynxynx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P4790)

## 题解：

这道紫题还是比较简单的，也没有太毒瘤。

很显然我们用贪心。

---

第一步：

如果 $n = 0$ , 直接输出 $-1$。

再把本来就成立的两个抠出来，比如样例一里的 $karl$ 和 $sofia$。

---

第二步：

我们用一个数组 $rd$ 记录每一个人的入度，将所有入度为0的人塞进队列 $que$  里面。

---

第三步：

我们不断取出队头 $t$， 如果 $t$ 喜欢的人没被改过，我们就更改 $t$ 喜欢的人，同时把他喜欢的人入度减一。

如果那个人入度变为 $0$，就把他塞进队列里。

注意一点：有一个特判被包括了（当这个人喜欢的人被更改过，他喜欢的人最后一定会消失，最后配对时直接将答案加一）。

---

第四步：

判断是否有环。

如果有，答案加上环大小除以二（只要更改环大小的一半次），如果环大小是奇数，说明和第三步中特判的人重合了。

最后输出答案即可。




```cpp
#include<bits/stdc++.h>
#define N 500005
using namespace std;
map <string,int> m;
int n,tot,ans,u,v,to[N],use[N],rd[N];
string a,b;
queue <int> que;
int pd(int pos){//判环
	if(use[pos]) return 0;
	use[pos]=1;
	return pd(to[pos])+1;
}
int main(){
	ios::sync_with_stdio(false);//读入优化
	cin>>n;
	if(n&1){
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=n;i++){
		cin>>a>>b;
		if(!m[a]) m[a]=++tot;
		if(!m[b]) m[b]=++tot;
		if(m[a]!=m[b]) to[m[a]]=m[b];//存现有情侣
	}
	use[0]=1;
	for(int i=1;i<=n;i++) if(i==to[to[i]] && !use[i] && !use[to[i]]) use[i]=use[to[i]]=1;
	for(int i=1;i<=n;i++) if(!use[i]) ++rd[to[i]];
	for(int i=1;i<=n;i++) if(!rd[i] && !use[i]) que.push(i);
	while(que.size()) {
		int now=que.front();
		que.pop();
		ans++;
		if(!use[to[now]]){
			use[to[now]]=1;
			--rd[to[to[now]]];//更改入度
			if(!rd[to[to[now]]] && !use[to[to[now]]]) que.push(to[to[now]]);//加入被更改符合条件的人
		}
	}
	for(int i=1;i<=n;i++) if(!use[i]){
		int k=pd(i);//判环
		if(k<=1) continue;//没有
		if(k&1) ++ans;//单独的一个
		ans+=k/2;
	}
	cout<<ans;
	return 0;
}
```

用IDE写的，自动对齐可能有点问题。

本人第```2```篇紫题题解，望管理员大大给过。

感谢各位大佬观看，不喜请喷。

---

## 作者：Forever1507 (赞：0)

## P4790

简要题意：给定内向基环树森林，一次操作可以改变一条边的终点，求最小操作次数或判断无解。

无解的话显然就是当且仅当点数是奇数，不然就算是两两暴力配对也一定能出解。

容易发现题目可以转化成一个相邻点配对的问题，最终答案就是配出的对数加上没配上的点数（因为相邻点配对就只用改一条边，没匹配上就最后一起改，一对就要改两条边了）。

然后考虑每一棵基环树，容易注意到环以下的树的部分直接从叶子向上贪心的选一定是不劣的。具体来说，如果一个点和他的父亲都是空余，那么我就算这里无脑选掉最坏情况下也就只会导致父亲和他的父亲没法匹配，额外多出 $1$ 的代价，但是反正我不选也有 $1$ 的代价，那么直接贪心选肯定就是对的。

因此先把树的部分贪心的选完，根据选出的结果，环的部分可能会被分割成若干条线段或者仍然是一个环，但是实际上没有区别，对于每一个连通块大小的奇偶性分别贡献到配对数和散点数里面就行了。

需要特判仍然是环且环长为 $2$ 的情况，因为不需要任何修改。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int n;
map<string,int>mp;
int cnt;
int to[N];
vector<int>nbr[N];
int siz[N];
bool vis[N],tag[N];
bool f[N];
int res,res2;
void dfs(int cur){
    siz[cur]=1;
    int cnt=0;
    for(auto to:nbr[cur]){
        if(vis[to])continue;
        dfs(to);
        siz[cur]+=siz[to];
        if(!f[to])cnt++;
    }
    if(cnt>1){
        res2+=cnt-1;
        f[cur]=1;
        res++;
    }
    else if(cnt==0)f[cur]=0;
    else f[cur]=1,res++;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    if(n&1){
        cout<<-1;
        return 0;
    }
    for(int i=1;i<=n;++i){
        string a,b;
        cin>>a>>b;
        if(!mp[a])mp[a]=++cnt;
        if(!mp[b])mp[b]=++cnt;
        to[mp[a]]=mp[b];
        nbr[mp[b]].push_back(mp[a]);
    }
    for(int i=1;i<=n;++i){
        if(!siz[i]){
            int now=i,tmp=0;
            deque<int>vec;
            while(!tag[now]){
                tag[now]=1;
                now=to[now];
            }
            int o=now;
            vec.push_back(now);
            now=to[now];
            while(now!=o){
                vec.push_back(now);
                now=to[now];
            }
            for(auto x:vec)vis[x]=1;
            bool flg=0;
            for(auto x:vec){
                dfs(x);
                tmp+=siz[x];
                flg|=f[x];
            }
            while(flg&&!f[vec.front()]){
                vec.push_back(vec.front());
                vec.pop_front();
            }
            if(vec.size()!=2){
                int len=0;
                for(auto x:vec){
                    if(f[x]==1){
                        res+=len/2;
                        res2+=len%2;
                        len=0;
                    }
                    else len++;
                }
                res+=len/2;
                res2+=len%2;
            }
        }
    }
    // cout<<res<<' '<<res2<<'\n';
    cout<<res+res2;
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

**引理 1**：若 $n$ 为奇数，一定无解；若 $n$ 为偶数，一定有解。

证明：两两配对，那么显然在 $2\nmid n$ 的时候会剩下一个，所以无解。否则在不考虑最优的情况下，对内两个互相指向对方，那么显然有解。

首先显然若已经存在两个点组成的环，那么可以直接将这两个点去掉，这样的代价为 $0$，并且删掉自环，记剩下的点数为 $n'$，由题意可以发现，这道题是个基环树。

接下来我们一个个 Subtask 来讨论。

### Subtask 1

$n\le 20$，于是可以考虑状压。

考虑当前状态下还没有选择到的两个点，那么就可以考虑这两个点匹配的代价，若这两个点有一条边相连，那么修改另一个点，代价为 $1$；否则两个点都需要修改，代价为 $2$。

时间复杂度 $O(n^22^n)$，不过常数比较小应该可以通过，但是题解区有 $O(n2^n)$ 的做法。

### Subtask 2

每个点都只有一条出边和一条入边，所以这就是个环。

**引理 2**：对于一个 $n$ 个点的环，处理它的代价是 $\lceil\dfrac{n}{2}\rceil$。

证明：对于长度为偶数的环， $\{1,2\},\{3,4\},\cdots,\{n-1,n\}$，这样分组，那么我们只需要改变 $2,4,\cdots,n$ 的边即可，代价 $\dfrac{n}{2}$；对于长度为奇数的环，最后会剩下一个 $n$，那么这个 $n$ 就应该和其它奇环中的点匹配，那么 $n$ 会造成贡献，所以这个环的总代价就是 $\dfrac{n-1}{2}+1=\dfrac{n+1}{2}$。综上所述，一个 $n$ 个点的环，代价是 $\lceil\dfrac{n}{2}\rceil$。

那么我们只需要找到每个环即可。

### Subtask 3

因为只有自环，所以基环树退化成树。

**引理 3**：对于一个 $n$ 个点的链，处理它的代价是 $\lceil\dfrac{n}{2}\rceil$。

证明思路同引理 $2$，篇幅限制所以这里就不写了。

但是考虑到父节点可能有多个子节点，而匹配不同的子节点可能会造成不同的代价，所以我们考虑一下匹配的优先级：对于每个节点，先考虑和子节点匹配，然后再考虑和父节点匹配。

于是定义 $out_u$ 表示 $u$ 到达的父节点节点，$in_u$ 表示 $u$ 的子节点中有多少个是没有被匹配的，$flg_u$ 表示 $u$ 是否被匹配。

考虑用队列维护已经匹配的节点，那么当 $in_u$ 为 $0$ 时，$u$ 入队，这个性质像拓补排序，于是考虑实现 topo。

容易想到对于 $u$，若 $flg_{out_u}=1$ 那么 $u$ 也只能和其它子树的点进行匹配，代价为 $1$，$flg_u=1$；否则 $u$ 和 $out_u$ 匹配，代价为 $1$，$flg_u=flg_{out_u}=1$。

### Subtask 4

纯种基环树。

首先仍然 topo 处理一下，考虑会剩下哪些点：

**引理 4**：若剩下点，就会剩下整个基环树的环。

证明：对点的种类进行分讨：

- 对于树上的点，显然 $flg$ 都被标记成了一。

- 对于环上的点，考虑一个点 $u$，若 $u$ 被它儿子匹配，则 $flg_u=1$，那么就会导致 $v$ 只由它的子树决定，如果 $v$ 和它儿子匹配，那么此时 $out_v$ 就会和 $v$ 陷入同一种情况，$flg_v=1$，继续递归；否则 $in_v=0$，入队，那么 $flg_v=1$，此时若 $flg_{out_v}=0$，那么 $flg_{out_v}\gets 1$；否则 $flg_{out_v}$ 本身就是 $1$，$out_v$ 来到了 $u$ 的情况，继续递归。那么此时就可以发现：一个环上，要么全都没被匹配，要么全都被匹配。

那么对于剩下的点，实现一遍 Subtask 2 即可。

---

