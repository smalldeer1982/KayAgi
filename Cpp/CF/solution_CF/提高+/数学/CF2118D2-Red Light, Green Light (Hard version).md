# Red Light, Green Light (Hard version)

## 题目描述

**这是问题的困难版本。不同版本的区别在于对 $k$ 和单个测试点中的 $n,q$ 总和的限制不同。**

给你一个长度为 $10^{15}$ 的长条和一个常数 $k$。在长条上有 $n$ 个格子上有一个信号灯，第 $i$ 个信号灯在格子 $p_i$ 处，同时具有一个初相 $d_i<k$。第 $i$ 个信号灯将在时刻 $z\times k+d_i,z$ 为整数时亮红灯，其他时刻亮绿灯。

时刻 $0$ 时你在某个格子处，面向正方向。每个时刻你将执行如下操作：
- 如果你所在的格子上有一个红色的信号灯，转向；
- 向你所面向的方向走一格。

你要处理 $q$ 个询问，询问给出时刻 $0$ 时你在格子 $a_i$，问时刻 $10^{100}$ 你是否已经走出长条的范围。

## 说明/提示

对于第一组数据，从 $1,2,3$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/ce9b61d8441ec2687644e4fcb1ecf9c698d0d9de.png)

对于第二组数据，从 $2$ 出发的情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2118D2/b6fc75687c6b2b664c445b1824b01121fde0aaa1.png)

## 样例 #1

### 输入

```
4
2 2
1 4
1 0
3
1 2 3
9 4
1 2 3 4 5 6 7 8 9
3 2 1 0 1 3 3 1 1
5
2 5 6 7 8
4 2
1 2 3 4
0 0 0 0
4
1 2 3 4
3 4
1 2 3
3 1 1
3
1 2 3```

### 输出

```
YES
NO
YES
YES
YES
YES
NO
NO
YES
YES
NO
NO
YES
NO
YES```

# 题解

## 作者：chenxi2009 (赞：6)

## 思路
简单清新思维题。

不难发现从 $a_i$ 出发要么直接走出范围，要么碰上至少一个亮灯导致转向。于是考虑处理出“在第 $i$ 个信号灯亮时位于 $p_i$，下一步向左/向右，能否在有限时间内走出范围”。

那么，我们考虑求从一个正亮的灯出发（等价于在此灯处转向），它会到达的下一个亮灯是哪一个，或它可以直接走出范围。对于从灯 $i$ 亮时开始，从灯 $i$ 走到灯 $j(i<j)$，在什么情况下到达灯 $j$ 时它是亮的？显然相位差，即 $d_j-d_i$，要和到达两个点的时差，$p_j-p_i$，模 $k$ 同余，有
$$
p_j-p_i\equiv d_j-d_i\pmod k\\
p_i-d_i\equiv p_j-d_j\pmod k
$$
所以，从灯 $i$ 在其亮时出发向右走，碰到的第一个红灯是最小的 $j>i$ 满足 $d_i-p_i\equiv d_j-p_j\pmod k$。要得到这个 $j$，我们考虑从灯 $n$ 开始递减处理，开一个 `map` 桶，$mp_x$ 存已经处理到的最小的 $j$ 满足 $d_j-p_j\equiv x\pmod k$。

当 $i>j$ 时，即向左走，有
$$
p_i-p_j\equiv d_j-d_i\pmod k\\
p_i+d_i\equiv p_j+d_j\pmod k
$$

同样开 `map` 桶处理即可。上述步骤时间复杂度 $O(n\log n)$。至此，我们得到了**在每个灯处转向，面向左/右，下一个会到达的灯**。

每个灯拆成两个点区分方向，建一个点表示走出边界，向下一个可以到达的灯连边，我们要得知它是否可以走到那个走出边界的点——那我们不妨建个反图，找出边界点可以到达的所有的点，只需要一次 DFS 就够了。

至此，我们得到了**在每个灯处转向，面向左/右，能否在有限时间内走出边界**。

接下来我们只需要对每个询问，找出它会到达的第一个亮的灯，就可以回答询问了。从 $a$ 出发向右走到达亮灯 $i(p_i>a)$ 当且仅当
$$
p_i-a\equiv d_i\pmod k\\
a\equiv p_i-d_i\pmod k
$$
这和处理“每个灯向右到达的第一个灯”时的式子类似，同样对 $a$ 排序，从右往左处理即可。不用对 $a$ 排序的方法是离散化所有 $(p_i-d_i)$ 后对每一个 $(p_i-d_i)$ 开一个 set，在对应的 set 里面二分最小的 $i\ge a$。

时间复杂度 $O(\sum n\log n)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define gc getchar
#define eb emplace_back
#define ef emplace_front
#define ep emplace
#ifndef DEBUG
#define debug
#endif
using namespace std;
template<typename T>void read(T &x){x = 0;int f = 1;char c = gc();while(!isdigit(c)){if(c == '-') f = -1;c = gc();}while(isdigit(c)) x = (x << 3) + (x << 1) + c - '0',c = gc();x *= f;}
const int N = 500000;
int T,n,q,nxt[N][2],it;
long long k,p[N],d[N];
bool esc[N],ans[N];
pair<long long,int> a[N];
map<long long,int>mp;
vector<int>e[N];
inline int plus(long long a,long long b){return (a + b) % k;}//(a+b)%k
inline int minus(long long a,long long b){return ((a - b) % k + k) % k;}//(a-b)%k
void sch(int u){
  esc[u] = true;
  for(auto v : e[u]) if(!esc[v]) sch(v);
}
int main(){
  cin.tie(0)->sync_with_stdio(0);
  read(T);
  while(T --){
    mp.clear();
    read(n),read(k);
    for(int i = 0;i <= 2 * n;i ++) e[i].clear(),esc[i] = false;
    for(int i = 1;i <= n;i ++) read(p[i]);
    for(int i = 1;i <= n;i ++) read(d[i]);
    //0 表示边界；1~n 表示每个亮灯开始向左走；n+1~2n 表示每个亮灯开始向右走
    for(int i = 1;i <= n;i ++){
      nxt[i][0] = mp[plus(p[i],d[i])];//从这个亮灯开始向左走可以到达的最近的亮灯，0 为边界
      mp[plus(p[i],d[i])] = i;
      e[nxt[i][0] ? nxt[i][0] + n : 0].eb(i);
      //从到达的最近的亮灯向 i 连边，因为 i 向左走到达的状态是 nxt 向右走，所以点的编号是 nxt+n
    }
    mp.clear();
    for(int i = n;i;i --){
      nxt[i][1] = mp[minus(p[i],d[i])];//同上
      mp[minus(p[i],d[i])] = i;
      e[nxt[i][1]].eb(i + n);
    }
    sch(0);//找出所有 0（边界）可达的点，标记 esc 表示可以走出边界
    read(q);
    for(int i = 1;i <= q;i ++) read(a[i].first),a[i].second = i;
    sort(a + 1,a + q + 1,[](pair<long long,int> a,pair<long long,int> b){
      return a.first > b.first;
    });//给询问排序从右往左处理
    mp.clear(),it = n;
    for(int i = 1;i <= q;i ++){
      auto [x,w] = a[i];
      while(it && p[it] >= x) mp[minus(p[it],d[it])] = it,it --;
      //保证 map 里面存的是所有 p[it]>=a[i] 的灯，用一个指针记录加入到了哪个灯
      ans[w] = esc[mp[x % k]];
    }
    for(int i = 1;i <= q;i ++){
      if(ans[i]) printf("YES\n");
      else printf("NO\n");
    }
  }
  return 0;
}
```

---

## 作者：DHeasy (赞：5)

- 2025.6.17：将“向前”和“向后”改成“向左”“向右”。（感谢 @[Alliy666](https://www.luogu.com.cn/user/908741)）

---



[D1](https://www.luogu.com.cn/article/0724jw84)。

考虑优化 D1 的做法。还是拆点，我们有 D1 的结论：

> 如果 $(i,j)$ 向左能走到 $(u,v)$，当且仅当 $j+i-u\bmod k=v$。向右走同理。

仔细观察一下，发现这等价于 $i+j \equiv u+v\pmod k$，而如果向右走，等价于 $i-j\equiv u-v\pmod k$。

于是可以把所有 $p_i+d_i\bmod k$ 相同的放在一个桶里，把所有 $p_i-d_i\bmod k$ 相同的放在另一个桶里。

于是我们可以对于所有红绿灯，在桶中二分求出向左和向右走到的第一个红灯的位置。

桶可以用 [set](https://oi-wiki.org/lang/csl/associative-container/#set) 维护。

如何判断一个红灯向左或向右能不能走出去呢？不难想到建个反图然后跑拓扑排序。

然后考虑处理询问，可以把询问给的 $a_i$ 看做是 $(a_i,0)$，向右走，然后就能找到第一个遇到的红灯了，找不到肯定是 `YES`。

最后判断这个红灯向左走能不能走出去即可。

[提交记录](https://codeforces.com/contest/2118/submission/324535408)

---

## 作者：DrDuck (赞：2)

Update on `2025/6/22`：修正了时间复杂度。

图论好题。

注意到 $1 \le p_i \le 10^{15}$，暴力一步步走肯定超时。因为只有遇到红灯才会转向，在行走的过程中，一个思路是不妨略去中间的一大堆绿灯和空地，直接从红灯跳到红灯，可以把时间复杂度降下来。~~简单来说就是绯红之王。~~

考虑当我站在第 $i$ 个灯（第 $i$ 个灯是红灯），将要向右走时，假设我走到第 $j$ 个灯的时候恰好红灯了，$i$ 与 $j$ 存在什么样的关系式。

要使上述关系式成立，有：
$$
d_j - d_i + x \times k = p_j - p_i，x \in \mathbb{N}
$$

显然有：
$$
(d_j - d_i) \equiv (p_j - p_i) \pmod{k}
$$
再利用同余的性质进行移项：
$$
(p_i - d_i) \equiv (p_j - d_j) \pmod{k}
$$
不难发现 $p_i - d_i$ 是只与 $i$ 有关的一个式子，令 $b_i = (p_i - d_i) \mod k$，只需比较 $b_i$ 与 $b_j$ 是否相等即可。如果 $b_i$ 与 $b_j$ 相等，则说明我站在第 $i$ 个灯，将要向右走时，走到第 $j$ 个灯的时候恰好红灯（假设中间没有其它红灯挡路）。

那么从第 $i$ 个灯向左走呢？同理得，有：
$$
(p_i + d_i) \equiv (p_j + d_j) \pmod{k}
$$
令 $a_i = p_i + d_i$，剩下的和上面一样，只不过变成了向左走。

把每一个红绿灯拆成两个点，一个点表示当我走到这个节点时，我要从向右走变成向左走，称为左行点，还有一个点表示当我走到这个节点时，我要从向左走变成向右走，称为右行点。先处理右行点到左行点，从左往右扫一遍所有红绿灯，开一个数组 $mp_i$ 来代表当前的所有红绿灯中，$b$ 值为 $i$ 的红绿灯是哪一个，如果有多个的话记录最右边的那一个。这里由于 $k \le 10^{15}$，我用 STL 中的 map 来代替 $mp$。在扫一遍的过程中，假设我扫到第 $i$ 个红绿灯，如果这个时候 $mp_{b_i}$ 已经有值了，那么让 $mp_{b_i}$ 这个红绿灯的右行点向 $i$ 号红绿灯的左行点连边。别忘了**每次**都要更新 $mp_{b_i}$ 的值。处理右行点到左行点的方法大同小异。

把图建出来后，在图上跑一遍 DFS，如果遇到环，则环内所有点与连向环的点都是不可行点（也就是最终无法通过这些点走出去），因为每个点出度均为 $1$ 或 $0$。反之如果遇到了一个出度为 $0$ 的点，所有能通向这个点包括这个点本身都是可行点（也就是可以通过这些点走出去）。

处理完这些之后根据询问分类讨论即可。具体实现看代码。

时间复杂度 $O(\sum \log{n}(n + q))$，可以通过。带个 $\log{n}$ 是因为要离散化。
# CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 4e+5 + 5;
int n, k, T, ctot, q;
int p[maxn], d[maxn], a[maxn], b[maxn], c[maxn], to[maxn];
bool vis[maxn], neng[maxn];
map<int, int> mp;
vector<int> v[maxn];
void dfs(int p)
{
    vis[p] = true;
    if (!to[p])
    {
        neng[p] = true;
        return;
    }
    if (!vis[to[p]])
    {
        dfs(to[p]);
    }
    neng[p] = neng[to[p]];
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--)
    {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
        {
            cin >> p[i];
        }
        for (int i = 1; i <= n; i++)
        {
            cin >> d[i];
        }
        for (int i = 1; i <= n; i++)
        {
            a[i] = (p[i] + d[i]) % k;//向左走
            c[i] = b[i] = ((p[i] - d[i]) % k + k) % k;//向右走
        }
        sort(c + 1, c + n + 1);//离散化
        ctot = unique(c + 1, c + n + 1) - c - 1;
        for (int i = 1; i <= n; i++)
        {
            v[lower_bound(c + 1, c + ctot + 1, b[i]) - c].push_back(p[i]);//按b分类
        }
        mp.clear();
        /*
        1~n右行点
        n+1~2n左行点
        */
        for (int i = 1; i <= n; i++)
        {
            if (mp[b[i]])
            {
                to[mp[b[i]]] = i + n;
            }
            mp[b[i]] = i;
        }
        mp.clear();
        for (int i = n; i; i--)
        {
            if (mp[a[i]])
            {
                to[mp[a[i]] + n] = i;
            }
            mp[a[i]] = i;
        }
        for (int i = 1; i <= n * 2; i++)
        {
            if (!vis[i])
            {
                dfs(i);
            }
        }
        cin >> q;
        while (q--)
        {
            int x;
            cin >> x;
            int pos = lower_bound(c + 1, c + ctot + 1, x % k) - c;//钦定x脚下的灯是d为0的红灯
            if (c[pos] != x % k)//根本拦不住，也就是根本没有 b 值为 x % k 的红绿灯
            {
                cout << "YES" << '\n';
            }
            else
            {
                int xp = lower_bound(v[pos].begin(), v[pos].end(), x) - v[pos].begin();//找到第一个遇到的红灯的位置
                if (xp == v[pos].size())//第一个遇到的红灯不存在
                {
                    cout << "YES" << '\n';
                }
                else if (neng[lower_bound(p + 1, p + n + 1, v[pos][xp]) - p + n])//能走出去
                {
                    cout << "YES" << '\n';
                }
                else
                {
                    cout << "NO" << '\n';
                }
            }
        }
        for (int i = 1; i <= n * 2; i++)//多测清空
        {
            vis[i] = neng[i] = false;
            v[i].clear();
            to[i] = 0;
        }
    }
    return 0;
}
```
~~代码其实不算长，只是我码风比较松散。~~

第一次写这么长的题解，如果有错误请在评论区指出，谢谢！

---

## 作者：gcx12012 (赞：2)

### 前言
傻逼题，赛时就不应该把 D1 和 D2 分开写。
### Solution
看到这题首先应该想到如何处理红灯的相关信息，因为只有红灯会改变运动方向。

于是我们可以先预处理 $p_i$ 左边和右边第一个碰到红灯的位置，设为 $L_i$ 和 $R_i$，如果没有则 $L_i=0$ 或 $R_i=n+1$。左边的话找最大 $j$ 满足 $p_i+d_i\equiv p_j+d_j\pmod k,j<i$，右边的话找最小 $j$ 满足 $p_i-d_i\equiv p_j-d_j\pmod k,j>i$。
然后把它当成一张图，$i\to L_i$ 和 $i\to R_i$ 当成边，发现如果一个点在环内是出不去的，于是我们可以直接处理环。

还有一种方法是设 $i\to R_{L_i}$ 为一次跳跃，此时直接倍增跳足够多次就可以判断是否在环内。

然后这题就做完了，这里提供后者的代码。


```cpp
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define ull unsigned long long
#define lll __int128
#define N 500010
#define For(i,a,b) for(ll i=a;i<=b;++i)
#define Rof(i,a,b) for(ll i=a;i>=b;--i)
#define ls (x<<1)
#define rs (x<<1|1)
#define lson ls,l,mid
#define rson rs,mid+1,r 
#define pb push_back
#define mk make_pair
#define pque priority_queue
#define pii pair<ll,ll>
#define fi first
#define se second

using namespace std;
set<ll >s[N];
ll p[N],d[N],c[N],tot=0,a[N];
ll T,n,k,q;

ll read(){	
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;		
}
map<ll ,ll >lst;
ll L[N],R[N],to[N][50];

void sol(){
	n=read(),k=read();
	For(i,1,n) p[i]=read();
	For(i,1,n) d[i]=read();
	For(i,0,49) to[0][i]=0,to[n+1][i]=n+1;
	For(i,1,n){
		ll pp=lst[(p[i]+d[i])%k];
		L[i]=pp;
		lst[(p[i]+d[i])%k]=i;
	}
	lst.clear();
	tot=0;
	Rof(i,n,1){
		ll pp=lst[((p[i]-d[i])%k+k)%k];
		if(!pp) R[i]=n+1;
		else R[i]=pp;
		c[++tot]=a[i]=((p[i]-d[i])%k+k)%k;
		lst[((p[i]-d[i])%k+k)%k]=i;
	}
	lst.clear();
	For(i,1,n) to[i][0]=R[L[i]];
	For(j,1,49){
		For(i,1,n){
			to[i][j]=to[to[i][j-1]][j-1];
		}
	}
	sort(c+1,c+tot+1);
	tot=unique(c+1,c+tot+1)-c-1;
	c[tot+1]=1e18;
	c[0]=-1e18;
	For(i,1,n) a[i]=lower_bound(c+1,c+tot+1,a[i])-c;
	For(i,1,tot) s[i].clear();
	For(i,1,n) s[a[i]].insert(p[i]);
	q=read();
	while(q--){
		ll x=read();
		//cout<<x<<endl;
		int now=lower_bound(c,c+tot+2,x%k)-c;
		if(c[now]!=x%k){
			printf("YES\n");
			continue;
		}
		auto it=s[now].lower_bound(x);
		if(it==s[now].end()){
			printf("YES\n");
			continue;
		}
		ll val=*it;
		//cout<<val<<endl;
		val=lower_bound(p+1,p+n+1,val)-p;
		Rof(i,49,0) val=to[val][i];
		if(val==0 || val==n+1) printf("YES\n");
		else printf("NO\n");
	}
}

int main()
{
	//freopen("game.in","r",stdin);
    //freopen("game.out","w",stdout);
    T=read();
    while(T--) sol();
	return 0;
}
/*

*/

```

---

## 作者：冷却心 (赞：0)

唉黑长直 /fn /fn /fn，我的早坂茜 /ll，我的宫前栞 /ll。

简单题。

注意到一个完整的移动过程可以视为在若干个红灯之间来回移动的过程。我们对每个灯开两个点 $(i,0/1)$，分别表示当前位于红灯状态的 $i$，下一步向右/向左。我们找到每种状态不停移动会到达的状态：

- 当前在 $(i,0)$，下一步会移动到 $(j,1)$，满足此时 $j$ 也是红灯并且 $j$ 是 $i$ 往右第一个满足这种状态的点。形式化地描述此时 $j$ 也是红灯，即为 $p_i-p_j\equiv d_j-d_i \pmod k$，移项得到 $p_i+d_i \equiv p_j + d_j \pmod k$。
- 当前在 $(i,1)$，下一步移动到 $(j,0)$，满足此时 $j$ 也是红灯，并且 $j$ 是 $i$ 往左第一个满足这种状态的点。形式化地，此时 $p_j-p_i\equiv d_j-d_i \pmod k$，移项得到 $d_i-p_i\equiv d_j-p_j \pmod k$。

所以我们可以处理出每个点的后继点，这里以 $(i,0)$ 为例，我们从后往前枚举，开一个哈希表维护 $\mathrm{next}_t$ 表示往后第一个 $p_j+d_j\equiv t$ 的 $j$，那么 $(i,0)$ 的后继点就是 $\mathrm{next}_{(p_i+d_i)\bmod k}$，然后把 $\mathrm{next}$ 对应的值修改。$(i,1)$ 的后继点处理则从前往后枚举并且下标是 $d_i-p_i$ 而不是 $d_i+p_i$。

这样每个点有小于等于一个后继点，显然形成了由若干内向树和内向基环树组成的森林。对于每个询问 $x$，我们找到他往后第一次红灯的位置，即满足 $p_q\ge x$ 且 $p_q-x\equiv d_q$ 的最小的 $q$，这个可以开若干个 `set`，在下标为 $p_i-d_i$ 的 `set` 中插入 $i$，那么每次查询就相当于在下标为 $x$ 的 `set` 中查询后继。如果 $q$ 不存在显然能走出。否则我们就相当于在上述森林中从 $(q,1)$ 开始走，如果不停走后继能走到某个点没有出边，那么合法，否则遇到了环，不能走出。

是否能走出可以建反图，然后以原图中每个没有出度的点开始遍历，一个点合法当且仅当他能被这些点遍历到。

这样如果哈希表复杂度视为常数，则预处理出点 $O(n)$，询问由于查询后继需要 $O(q\log n)$，总复杂度 $O(q\log n)$。

弱化版则是暴力寻找后继，查询暴力跳后继，时间复杂度 $O(n(n+q))$，不知道为啥只开 $500$。

*代码实现中每个点的两种状态和文中相反。*
```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 4e5 + 10;
int n, Q; LL P[N], D[N], K;

int to[N];
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
__gnu_pbds::gp_hash_table<LL, int> mp;
vector<int> G[N]; bool res[N];
void DFS(int u) {
	res[u] = 1; for (int v : G[u]) if (!res[v]) DFS(v);
}
set<int> s[N]; int stot;

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int _; cin >> _;
	while (_ --) {
		cin >> n >> K;
		for (int i = 1; i <= n; i ++) cin >> P[i];
		for (int i = 1; i <= n; i ++) cin >> D[i];
		mp.clear();
		for (int i = 1; i <= n; i ++)
			to[i] = mp[(D[i] + P[i]) % K], mp[(D[i] + P[i]) % K] = i + n;
		mp.clear();
		for (int i = n; i >= 1; i --)
			to[i + n] = mp[(D[i] - P[i] % K + K) % K], mp[(D[i] - P[i] % K + K) % K] = i;
		for (int i = 1; i <= n * 2; i ++) if (to[i]) G[to[i]].push_back(i);
		for (int i = 1; i <= n * 2; i ++) if (!to[i]) DFS(i);
		mp.clear(); stot = 0;
		for (int i = 1; i <= n; i ++) {
			if (mp.find((P[i] - D[i] % K + K) % K) == mp.end()) mp[(P[i] - D[i] % K + K) % K] = ++ stot;
			s[mp[(P[i] - D[i] % K + K) % K]].insert(i);
		}
		cin >> Q; LL x;
		while (Q --) {
			cin >> x; 
			if (mp.find(x % K) == mp.end()) { cout << "YES\n"; continue; }
			int t = lower_bound(P + 1, P + 1 + n, x) - P;
			auto it = s[mp[x % K]].lower_bound(t);
			if (it == s[mp[x % K]].end()) { cout << "YES\n"; continue; }
			cout << (res[*it] ? "YES\n" : "NO\n");
		}
		for (int i = 1; i <= n * 2; i ++) to[i] = 0, G[i].clear(), res[i] = 0;
		for (int i = 1; i <= stot; i ++) s[i].clear();
	}
	return 0;
}
```

---

