# Turtle and a MEX Problem (Hard Version)

## 题目描述

两个版本的问题是不同的。在这个版本的问题中，你不能选择同一个整数两次或更多次。只有当两个版本都解决时，才能进行 hack。

有一天，乌龟正在玩 $n$ 个序列。设第 $i$ 个序列的长度为 $l_i$，则第 $i$ 个序列为 $a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i}$。

当乌龟在玩耍时，小猪给了他一个问题来解决。问题的陈述如下：

- 最初有一个非负整数 $x$。乌龟可以对这个整数执行任意次数（可能为零）的操作。
- 在每次操作中，乌龟可以选择一个之前未被选择过的整数 $i$（满足 $1 \le i \le n$），并将 $x$ 设为 $\text{mex}^{\dagger}(x, a_{i, 1}, a_{i, 2}, \ldots, a_{i, l_i})$。
- 乌龟被要求找到答案，即在执行任意次数操作后 $x$ 的最大值。

乌龟轻松解决了上述问题。他定义 $f(k)$ 为初始值 $x$ 为 $k$ 时上述问题的答案。

然后小猪给了乌龟一个非负整数 $m$，并要求乌龟找出 $\sum\limits_{i = 0}^m f(i)$ 的值（即 $f(0) + f(1) + \ldots + f(m)$ 的值）。不幸的是，他无法解决这个问题。请帮助他！

$\text{mex}(c_1, c_2, \ldots, c_k)$ 定义为不在序列 $c$ 中出现的最小非负整数 $x$。例如，$\text{mex}(2, 2, 0, 3)$ 是 $1$，$\text{mex}(1, 2)$ 是 $0$。

## 说明/提示

在第一个测试用例中，当 $x$ 初始值为 $2$ 时，乌龟可以选择 $i = 3$ 并将 $x$ 设为 $\text{mex}(x, a_{3, 1}, a_{3, 2}, a_{3, 3}, a_{3, 4}) = \text{mex}(2, 7, 0, 1, 5) = 3$。可以证明乌龟无法使 $x$ 的值大于 $3$，因此 $f(2) = 3$。

可以看出 $f(0) = 3$，$f(1) = 3$，$f(2) = 3$，$f(3) = 3$，$f(4) = 4$。所以 $f(0) + f(1) + f(2) + f(3) + f(4) = 3 + 3 + 3 + 3 + 4 = 16$。

在第二个测试用例中，当 $x$ 初始值为 $1$ 时，乌龟可以选择 $i = 1$ 并将 $x$ 设为 $\text{mex}(x, a_{1, 1}, a_{1, 2}, a_{1, 3}, a_{1, 4}, a_{1, 5}) = \text{mex}(1, 0, 2, 0, 4, 11) = 3$。可以证明乌龟无法使 $x$ 的值大于 $3$，因此 $f(1) = 3$。

可以看出 $f(0) = 4$，$f(1) = 3$，$f(2) = 4$，$f(3) = 3$，$f(4) = 4$。所以 $f(0) + f(1) + f(2) + f(3) + f(4) = 4 + 3 + 4 + 3 + 4 = 18$。

在第四个测试用例中，可以看出 $f(0) = 3$ 和 $f(1) = 1$。所以 $f(0) + f(1) = 3 + 1 = 4$。

## 样例 #1

### 输入

```
6
3 4
2 0 2
3 2 3 3
4 7 0 1 5
3 4
5 0 2 0 4 11
1 1
5 1 3 0 3 3
2 50
2 1 2
2 1 2
1 1
7 1 2 4 1 4 9 5
4 114514
2 2 2
5 7 3 6 0 3
3 0 1 1
5 0 9 2 1 5
5 1919810
1 2
2 324003 0
3 1416324 2 1460728
4 1312631 2 0 1415195
5 1223554 192248 2 1492515 725556```

### 输出

```
16
18
1281
4
6556785365
1842836177961```

# 题解

## 作者：Mirage_Insane (赞：3)

赛时犯智，气得不想调了，结果第二天起来十分钟就调过了，更气了。

下文记序列 $i$ 的 $\operatorname{mex}$ 为 $in_i$，当 $x = in_i$ 时使用 $i$ 操作得到的 $\operatorname{mex}$ 为 $out_i$。你可以理解为当 $x = in_i$ 时，通过序列 $i$ 就能将 $x$ 变成 $out_i$。这个 $\operatorname{mex}$ 可以直接求，因为它肯定无法太大，最多也就遍历 $\sum l_i$ 次。

显然，先不管当前的 $x$ 为多少，你只要进行了 $i$ 操作就能将 $x$ 变为 $in_i$。

我们要先求出一个 $Max$，表示：**不论当前的 $x$ 为多少，进行一些操作后总能将 $x$ 变成 $Max$ 且最大**。

首先，我们初始化 $Max = \max_{i = 1}^{n} in_i$，表示只进行了某一次操作后 $x$ 变成的最大值。接着，对于每一个 $i$，我们再记忆化搜索求出当 $x = in_i$ 时进行一系列操作后得到的最大值，记作 $dp_i$。容易发现，当 $n$ 个序列中至少出现了两次 $in_i$ 时，有：$Max = \max(Max,\ dp_i)$。因为我们可以用其中任意一次操作将 $x$ 变为 $in_i$，然后再一步步变成 $dp_i$。至此，我们求出了 $Max$。

记 $N = \max_{i = 1}^{n} l_i$，那么初始数 $x$ 通过这 $n$ 个序列最大也就变为 $N$ 左右。因此我们再对 $\min(m, \ N + 3)$ 内的所有数记忆化搜索求出其进行一系列操作后的最大值，剩下的数肯定不进行任何操作最优，使用等差数列公式加起来就可以了。

注意多组数据的清空，一定要清完！！！

### Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
#define int long long
struct node {
    int s, t;
}s[200005];
bool cmp(node a, node b) {
    return a.s == b.s ? a.t > b.t : a.s < b.s;
}
int a[200005], in[200005], out[200005], n, res[200005], num[200005], Max;
bool vis[200005];
int dfs(int x) {
    // cout <<"begin:" << x << endl;
    if(res[x] != -1) return res[x];
    int id = lower_bound(in + 1, in + 1 + n, x) - in;
    // cout <<"over:" << id << " " << in[id] << " " << out[id] << endl;
    if(id <= n && in[id] == x) {
        int ans = Max;
        while(id <= n && in[id] == x) ans = max(ans, dfs(out[id])), id++;
        return res[x] = ans;
    }
    else return res[x] = max(Max, x);
}
signed main() {
    memset(res, -1ll, sizeof(res));
    int T;
    SF("%lld", &T);
    while(T--) {
        Max = 0;
        int m, N = 0;
        SF("%lld%lld", &n, &m);
        for(int i = 1; i <= n; i++) {
            int p;
            SF("%lld", &p);
            N = max(N, p);
            for(int j = 1; j <= p; j++) {
                SF("%lld", &a[j]);
                if(a[j] > 200003ll) continue;
                vis[a[j]] = 1;
            }
            int now = 0;
            while(vis[now]) now++;
            s[i].s = now, now++;
            while(vis[now]) now++;
            s[i].t = now;
//            if(m == 1e9) cout << now << endl;
            for(int j = 1; j <= p; j++) {
                if(a[j] > 200003ll) continue;
                vis[a[j]] = 0;
            }
        }
        // cout << endl;
        sort(s + 1, s + 1 + n, cmp);
        for(int i = 1; i <= n; i++) in[i] = s[i].s, out[i] = s[i].t;
        for(int i = 1; i <= n; i++) {
//             cout << in[i] << " " << out[i] << endl;
            int now = dfs(in[i]);
            // cout << now << endl;
            Max = max(Max, in[i]);
            if(num[in[i]]) Max = max(Max, now);
            num[in[i]]++;
        }
        for(int i = 1; i <= n; i++) res[in[i]] = res[out[i]] = -1ll, num[in[i]] = 0; // 注意上述的 dfs 只是在求 Max，并不是 x 的最终值，因此也要清空 res。 
//         cout << Max << endl;
        int ans = 0;
        for(int i = 0; i <= min(m, N + 3); i++) {
            ans += dfs(i);
//            cout << i << " " << dfs(i) << endl;
        }
        for(int i = 0; i <= min(m, N + 3); i++) res[i] = -1ll;
        for(int i = 1; i <= n; i++) res[in[i]] = res[out[i]] = -1ll;
        if(m > N + 3) ans += (N + 4 + m) * (m - N - 3) / 2ll;
        PF("%lld\n", ans);
    }
    return 0;
}
```

如果还不是很理解就手玩几下样例吧，样例几乎把所有的情况都考虑到了。

---

## 作者：Ghosty_Neutrino (赞：2)

## 题意
建议学好英语，因为我把它粘贴到翻译器那里出大事了，完全看不懂，根本看不懂。

海龟有 $n$ 个序列。

起初有一个非负整数 $x$。海龟将对整数执行任意数量（可能为零）的操作。

在每次操作中，海龟都可以选择一个整数，而且这个数以前没有被选过。并设置 $x$ 到 $ \operatorname{mex}(x,a_{i,1},a_{i,2},\dots,a_{i,l_i})$。

海龟被要求找出答案，即最大值 $x$ 执行任意数量的操作后。

输入数据样例数 $n$，然后给一个非负整数 $m$ 求值，然后再输入序列。
## 分析
假设第 $i$ 个序列最小没出现的自然数是 $x_i$，第二小没出现的自然数是 $y_i$。如果 $k \ne x_i$，那么结合第 $i$ 个序列操作后有 $k=x_i$，否则有 $k=y_i$i。为此我们可以进行 $x_i$ 到 $y_i$ 的连边。

那个简单版的可以多次选择同一个序列，但这个困难版它每个序列只能选择一次，这又成一个问题了。

因为只能选一次，所以每个 $k$ 不一定都能到达 DAG 中最大的节点。贝贝们可以考虑什么情况下 $k$ 可以到达某个 DAG 的最大节点。

首先如果 $k$ 本身就是 DAG 中的节点那么一定可以。另外如果 DAG 中存在某个节点 $u$ 的出度至少为 $2$，那么我们可以先通过一次操作将 $k$ 变成 $u$，再通过 $u$ 一步一步变成最大节点。我们可以通过并查集维护每个 $x_i$ 和 $y_i$ 所在的 DAG，以及 DAG 中的最大节点。

记 $r$ 是 $y$ 中最大的数，对于 $k>r$ 的 $k$不应该进行操作，答案就是 $k$ 本身。对于 $k \le r$ 的情况，除了 $k$ 本身外，还可以变成最大的 $x_i$，以及存在出度至少为 $2$ 的节点的 DAG 中的最大节点，以及 $k$ 所在 DAG 中的最大节点。取这些情况的最大值就是答案。

---

## 作者：RayAstRa_ (赞：1)

因为 D2 TLE 调不过去导致没看 E，丢掉了 CM。

结果一看评级是 2100 的绿，差点没气晕。

## Description

有 $n$ 个序列，你每次可以选择一个（Easy：无限制，Hard：之前没有被选择过的）序列 $a$，将手中的数 $x$ 与取 $x\gets\text{mex}(x,a_1,a_2,...,a_l)$。

设 $f(x)$ 为你手中的数初始为 $x$，经过若干次操作可以达到的最大值。求 $\sum\limits_{i = 0}^m f(i)$。

## Solution

对序列 $a$，设 $u=\text{mex}(a_1,a_2,...,a_l)$，$v=\text{mex}(a_1,a_2,...,a_l,u)$。容易发现对于 $x\ne u$，将 $x$ 与 $a$ 操作会得到 $u$，否则会得到 $v$。 

对 Easy Version，任何一个数取两遍序列 $a$ 都能得到 $v$，则 $f(x)=\max(\max v,x)$。

对 Hard Version，我们不能再取两遍同一个序列了，考虑图论建模。

初始化 $g(x)\gets x$，对每一个序列，连接一条从 $u$ 到 $v$ 的有向边，并拓扑排序计算 $g(u)\gets\max(g(u),g(v))$。

同时，对于一个有不少于两条出边的点 $u$，我们可以先执行一次操作让任何 $x$ 变为 $u$，随后走某条出边变为 $g(u)$。因此使 $\max u\gets\max(\max u,g(u))$。

于是得到 $f(x)=\max(\max u,g(x))$。

时间复杂度分析：对于一个长度为 $l$ 的序列，其 $u,v$ 的大小为 $O(l)$ 的，瓶颈为计算 $u,v$ 时序列的排序与去重，因此时间复杂度为 $O(l\log l)$。

## Code (Hard Version)


```cpp
const int N=200005;
int n,m,l,a[N],u,v,now,maxv,maxu,g[N];
vec ed[N];
ll ans;
void solve(){
    read(n);read(m);
    maxu=maxv=0;
    For(i,1,n){
        read(l);
        For(j,1,l)
            read(a[j]);
        sort(a+1,a+1+l);
        l=unique(a+1,a+1+l)-a-1;
        now=u=v=0;
        if(a[1]>1)v=1;
        else if(a[1]>0){
            For(j,1,l)
                if(a[j]!=j){
                    v=j;
                    break;
            }
            if(!v)v=a[l]+1;
        }else{
            For(j,1,l){
                if(a[j]!=now){
                    if(u){
                        v=now;
                        break;
                    }else{
                        u=now++;
                        if(a[j]!=now){
                            v=now;break;
                        }
                    }
                }
                now++;
            }
            if(!u)u=a[l]+1,v=a[l]+2;
            if(!v)v=a[l]+1;
        }
        maxu=max(maxu,u);
        maxv=max(maxv,v);
        ed[u].pb(v);
    }
    Rof(i,maxv,0){
        g[i]=i;
        for(auto to:ed[i])
            g[i]=max(g[i],g[to]);
    }
    For(i,0,maxv)
        if(ed[i].size()>1)
            maxu=max(maxu,g[i]);
    ans=0;
    For(i,0,min(maxv,m))
        ans+=max(maxu,g[i]);
    if(m>maxv)
        ans+=1ll*(m-maxv)*(m+maxv+1)/2;
    print(ans,'\n');
    For(i,0,maxv)
        ed[i].clear();
}
```

---

## 作者：Exp10re (赞：1)

EZ.ver 和 HD.ver 都是巧妙题啊。

### 解题思路

记一个数列的最小未出现非负整数为 $u_i$，次小未出现非负整数为 $v_i$。

若当前数为 $x$，每一个数列都没有执行过操作，考虑接下来能进行的操作：

- 操作 1：选取满足 $u_i=x$ 的 $i$，将 $x$ 变为 $v_i$。
- 操作 2：选取满足 $u_i\ne x$ 的 $i$，将 $x$ 变为 $u_i$。

我们的策略是：只进行小于等于一次操作 2，然后进行若干次操作 1，不进行大于一次操作 2 的原因是其中一次一定无用，相当于对该数列浪费了一次操作机会，更劣。

记 $v_p=\max\limits_{1\leq i \leq n} v_i$。

记 $f_i$ 表示只进行操作 1 的情况下从 $i$ 开始能得到的最大值，则倒序转移，转移方程如下：

$$f_i=\max\limits_{u_j=i} f_j$$

初始边界为 $f_i=i$。

如此，考虑以 $x$ 开始，能进行至多一次操作 2 时的答案 $g_x$：

- $g_x \geq \max\limits_{1\leq i \leq n} u_i$，原因是进行一次操作二一定能得到 $\max\limits_{1\leq i \leq n} u_i$。
- $g_x \geq f_x$，原因是不进行操作二一定能得到 $f_x$。
- 若存在 $k$ 满足：至少两个 $i$ 满足 $u_i=k$，则 $g_x \geq f_x$，原因是 $x$ 可以与其中一个进行一次操作 2，对另一个进行操作 1 得到 $f_k$。

预处理满足条件的 $f_k$ 最大值，则所有 $g_x$ 的计算是线性的。

故 $\sum\limits_{i=0}^n f(i)=\sum\limits_{i=0}^n \max(i,g_i)$，显然对于大于 $v_p$ 的 $i$ 有 $g_i\leq i$，对小于等于 $v_p$ 的部分求和，大于 $v_p$ 的部分等差数列求和即可。

时间复杂度 $O(\sum l_i)$。

---

