# Amazing Trick

## 题目描述

Alice is a magician and she creates a new trick. She has $ n $ cards with different numbers from $ 1 $ to $ n $ written on them. First, she asks an audience member to shuffle the deck and put cards in a row. Let's say the $ i $ -th card from the left has the number $ a_i $ on it.

Then Alice picks two permutations $ p $ and $ q $ . There is a restriction on $ p $ and $ q $ — permutations can't have fixed points. Which means $ \forall i: p_i \ne i\ and\ q_i \ne i $ .

After permutations are chosen, Alice shuffles the cards according to them. Now the $ i $ -th card from the left is the card $ a[p[q[i]] $ . The trick is considered successful if $ i $ -th card from the left has the number $ i $ on it after the shuffles.

Help Alice pick the permutations $ p $ and $ q $ or say it is not possible for the specific starting permutation $ a $ .

## 样例 #1

### 输入

```
4
2
2 1
3
1 2 3
4
2 1 4 3
5
5 1 4 2 3```

### 输出

```
Impossible
Possible
3 1 2
2 3 1
Possible
3 4 2 1
3 4 2 1
Possible
4 1 2 5 3
3 1 4 5 2```

# 题解

## 作者：Alex_Wei (赞：7)

记号：$p\circ a$ 表示 $p$ 作用于 $a$，即 $a_i\to a_{p_i}$：将序列 $a$ 位置为 $i$ 上的数移动至位置 $p_i$。

问题等价于构造两个错排 $p, q$，使得 $q\circ p \circ a = \epsilon$，其中 $\epsilon_i = i$。

**随机法**：

直接随机打乱 $\epsilon$ 有 $\frac 1 e$ 的概率得到错排 $p$。而因为 $p$ 随机，所以 $p\circ a$ 也有 $\frac 1 e$ 的概率为错排，使得 $q$ 为错排。注意这个分析并不严谨，因为 $p$ 并非在所有排列里随机，而是只在错排中随机，但是 $p\circ a$ 为错排的概率不会很低。随机 $10 ^ 3$ 次已经足够。

```cpp
#include <bits/stdc++.h>
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
constexpr int N = 1e5 + 5;
int n, a[N], p[N], b[N], q[N];
void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i], p[i] = i;
  for(int _ = 1; _ <= 1000; _++) {
    shuffle(p + 1, p + n + 1, rnd);
    bool ok = 1;
    for(int i = 1; i <= n && ok; i++)
      if(p[i] == i || a[p[i]] == i) ok = 0;
      else q[a[p[i]]] = i;
    if(ok) {
      puts("Possible");
      for(int i = 1; i <= n; i++) cout << p[i] << " "; cout << "\n";
      for(int i = 1; i <= n; i++) cout << q[i] << " "; cout << "\n";
      return;
    }
  }
  puts("Impossible");
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T;
  cin >> T;
  while(T--) solve();
  return 0;
}
/*
g++ A_rnd.cpp -o A -std=c++14 -O2 -DALEX_WEI
*/
```

**构造法**：

首先 $n = 1$ 显然无解。

将排列视为若干置换环。从 $a_i$ 向 $i$ 连边，则需要找到错排（环长大于 $1$）$p$ 使得不存在边 $i\to p_i$，因为边 $i\to p_i$ 使得 $a_{p_i} = i$。

注意到对于二元环 $(i, j)$（$a_i = j$ 且 $a_j = i$），$i, j$ 要么不在 $p$ 的相同环，要么在相同环上不相邻。

当不存在二元环时，用一个大环将所有环串起来。

当存在至少两个二元环时，用一个环把所有二元环的一个点和其它所有不在二元环上的点串起来，用另一个环把所有二元环的另一个点串起来。

当恰存在一个二元环时，若 $n < 4$ 显然无解，否则可以类似构造出两个环，使得环上的点数均大于 $1$。

时间复杂度 $\mathcal{O}(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 5;
int n, a[N], b[N], vis[N];
vector<int> cyc;
void dfs(int id) {
  vis[id] = 1, cyc.push_back(id);
  if(!vis[a[id]]) dfs(a[id]);
}
void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) cin >> a[i], vis[i] = 0;
  if(n == 1) return puts("Impossible"), void();
  vector<int> P, ra, rb, p(n + 1, 0), q(n + 1, 0);
  vector<vector<int>> _2;
  for(int i = 1; i <= n; i++) {
    if(vis[i]) continue;
    cyc.clear(), dfs(i);
    if(cyc.size() == 2) _2.push_back(cyc);
    else for(int it : cyc) P.push_back(it);
  }
  ra = P;
  if(_2.size() >= 2) for(auto it : _2) ra.push_back(it[0]), rb.push_back(it[1]);
  else if(_2.size() == 1) {
    if(P.size() <= 1) return puts("Impossible"), void();
    rb.push_back(ra.back()), ra.pop_back();
    ra.push_back(_2[0][0]), rb.push_back(_2[0][1]);
  }
  puts("Possible");
  for(int i = 0; i < ra.size(); i++) p[ra[i]] = ra[(i + 1) % ra.size()];
  for(int i = 0; i < rb.size(); i++) p[rb[i]] = rb[(i + 1) % rb.size()];
  for(int i = 1; i <= n; i++) b[i] = a[p[i]];
  for(int i = 1; i <= n; i++) q[b[i]] = i;
  for(int i = 1; i <= n; i++) cout << p[i] << " "; cout << "\n";
  for(int i = 1; i <= n; i++) cout << q[i] << " "; cout << "\n";
}
int main() {
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  int T;
  cin >> T;
  while(T--) solve();
  return 0;
}
/*
g++ A.cpp -o A -std=c++14 -O2 -DALEX_WEI
*/
```

---

## 作者：FFTotoro (赞：6)

## 前言

感谢 _HMZ_ 大佬在我 [一直调不出 Test #5](https://www.luogu.com.cn/discuss/541771) 时给了一些点拨，在经过 $25$ 分钟的的调测后通过了本题。~~也算警示后人吧~~

## 解法

本题可以使用随机化做法。

记 $m_i(1\le i\le n)$ 为 $i$ 在排列 $a$ 中的位置，那么容易观察到题目的要求 $a_{p_{q_i}}=i$ 等价于 $p_{q_i}=m_i$。

又因为排列 $p$ 需要满足 $p_i\ne i$，根据上面的转化，就可以得到 $q_i\ne m_i$。

这样，原问题就转化为了**构造一个排列 $q$，使得 $q_i\ne i$ 且 $q_i\ne m_i$**，然后再根据 $q$ 构造出 $p$ 满足 $p_{q_i}=m_i$。

## 实现

先用一个 `std::vector` 顺序存储 $1,2,\ldots,n$，然后对于每个 $i$，从 `vector` 中随机选取一个数 $k$，如果 $k_i\ne i$ 且 $k_i\ne m_i$，那么将 $q_i$ 赋值为 $k$。如果找很多次还找不到满足条件的 $k$，那么就退出循环，**重新回到开始再从头构造一遍 $q$**。

如果找了非常多遍都没有合法的 $q$ 序列，就可以判断为无解。可以证明，在构造次数足够多时，出错的概率可以忽略不计。

找到 $q$ 序列后，将所有的 $p_{q_{i}}$ 赋值为 $m_i$ 即可。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],m[100001],p[100001],q[100001];
int main(){
  ios::sync_with_stdio(false);
  int t; cin>>t; srand(time(0)); // srand 设置随机种子
  while(t--){
    int n; bool flag=false; cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],m[a[i]]=i;
    for(int r=1;r<=80;r++){ // 找 80 遍（这个数足够大）
      flag=true;
      vector<int> v(n); iota(v.begin(),v.end(),1); // vector 初始化
      for(int i=1;i<=n;i++)q[i]=i;
      for(int i=1;i<=n;i++){
        for(int j=1;j<=10;j++){
          int k=rand()%v.size();
          if(v[k]==i||v[k]==m[i])continue;
          else{q[i]=v[k]; v.erase(v.begin()+k); break;}
          // 判断 k 的合法性
         }
         if(q[i]==i||q[i]==m[i]){flag=false; break;} // 再找一遍
      }
      if(flag)break; // 找到了
    }
    if(!flag){cout<<"Impossible\n"; continue;} // 无解
    cout<<"Possible\n";
    for(int i=1;i<=n;i++)p[q[i]]=m[i]; // 根据排列 q 构造排列 p
    for(int i=1;i<=n;i++)cout<<p[i]<<' ';
    cout<<endl;
    for(int i=1;i<=n;i++)cout<<q[i]<<' ';
    cout<<endl;
  }
  return 0;
}
```

---

## 作者：Hovery (赞：4)

## problem

[Amazing Trick](https://www.luogu.com.cn/problem/CF1773A)

## Sol

可以转化为一个图论问题。

![](https://cdn.luogu.com.cn/upload/image_hosting/voryp42x.png)

假设 $q$，$p$ 已知的情况下。

对于每一个 $q$ 中的每一个位置，连一条向 $p$ 中 $q_i$ 的位置。

对于每一个 $p$ 中的每一个位置，连一条向 $a$ 中 $p_i$ 的位置。

对于每一个 $a$ 中的每一个位置，连一条向 $a$ 中 $a_i$ 的位置。

那么最后一个样例可以连出下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/hvwi293b.png)

不难发现对于每一个 $i$，都能从 $q$ 中第 $i$ 个位置走到 $a$ 中第 $i$ 个位置。

然后问题就转化成了让你连一些边，使得对于每一个 $i$，都能从 $q$ 中第 $i$ 个位置走到 $a$ 中第 $i$ 个位置，而且不能有垂直向下的边。

先枚举 $p$，然后用set去维护一下还没有成功匹配到的位置。

每次枚举到一个 $i$，找到堆中第一个 $j$ 使得 $j\neq i$，并且 $a_i\neq j$。

然后你会发现这样还是有问题，我们可以在set中加一维表示对应这个 $i$ 若想要它联通，在 $p$ 中还有几个点可选，然后按这个作为第一关键字即可。

## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int> 
#define pb push_back
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define int long long
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), to(n + 1), q(n + 1), p(n + 1), vis(n + 1), now(n + 1);
    set<pii> s;
    for (int i = 1;i <= n;i++)
    {
        int x;
        cin >> a[i];
        x = a[i];
        to[x] = i;
    }
    for (int i = 1;i <= n;i++)
    {
        if (to[i] != i)
        {
            s.insert({n - 2, i});
            now[i] = n - 2;
        }
        else s.insert({n - 1, i}), now[i] = n - 1;
    }
    for (int i = 1;i <= n;i++)
    {
        pii flag = {0, 0};
        for (auto j : s)
        if (j.se != i && i != to[j.se])
        {
            flag = j;
            break;
        }//这里最多遍历三次，可以自己去理解。
        if (flag.second == 0)//找不到这样的就不合法。
        {
            cout << "Impossible\n";
            return;
        }
        s.erase(s.lower_bound(flag));
        now[flag.second] = 0;
        if (now[i])
        {
            s.erase(s.lower_bound({now[i], i}));
            now[i]++;
            s.insert({now[i], i});
        }
        if (now[a[i]] && a[i] != i)
        {
            s.erase(s.lower_bound({now[a[i]], a[i]}));
            now[a[i]]++;
            s.insert({now[a[i]], a[i]});
        }//有两个位置是不会受影响的，把其它的减去1等价于把这两个加上1。
        q[flag.second] = i;
        p[i] = to[flag.second];
    }
    cout << "Possible\n";
    for (int i = 1;i <= n;i++)
    cout << p[i] << ' ';
    cout << '\n';
    for (int i = 1;i <= n;i++)
    cout << q[i] << ' ';
    cout << '\n';
}

signed main()
{
    IOS;
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
```

---

## 作者：I_am_Accepted (赞：1)

题目等价于（**不是翻译**）给定一个排列 $\{a\}$，让你构造一个排列 $\{p\}$ 使得 $\{p\}$ 错排于 $\{a\}$ 和顺序排列，或报告无解。

特判掉 $n\le 3$ 的情况。

$n\ge 4$，有解等价于二分图 $G$ 有完美匹配。

$G$ 如下：

每种值建为左部点，每个位置建为右部点。

左右连边 $(i,j)$ 当且仅当 $i\ne j\ \land\ i\ne a_j$。

* * *

这样每个左部点的度 $\ge n-2$，对于左部大小为 $n-1$ 的点集，右部能连的大小必然 $\ge n-1\ ^{[\Delta]}$；左部大小为 $n$ 的点集（全集），右边能连的也为全集。

所以由 Hall 定理，$n\ge 4$ **必然有解**。

$[\Delta]$：反证法。若存在反例，则有 $n-1$ 个左部点不连边的点集均为相同的两个右部节点。而 $n\ge 4\implies n-1\ge 3$，综合不连边的条件，矛盾，原命题成立。

* * *

接下来随机多次排列 $\{p\}$（使用 `shuffle(...);`）直至合法即可。

要随多少次？别问我，问就是不知道。

猜一手当 $n$ 充分大的时候是两个排列的错排的概率是和 $n$ 无关的常数。

---

## 作者：Cxny (赞：1)

题意：给定排列 $a$，构造两个排列 $p,q$ 使得 $a[p[q[i]]]=i$ 且 $\forall i:\ p_i{=}\mathllap{/\,}i,\ q_i{=}\mathllap{/\,}i$。或报告无解。

发现若确定中间状态就可以确定排列 $p$ 和 $q$。而为了满足限制，中间状态 $x$ 需要满足 $x_i{=}\mathllap{/\,}i,x_i{=}\mathllap{/\,}a_i$。

$n=1$ 必定无解。$n=2,3$ 各有一种情况无解。

对于剩下的情况，考虑对值和位置建出二分图。每个位置有不超过两个限制，因此每个点度数 $\ge n-2$。

根据 $\text{Hall}$ 定理可以证明，此时一定有解。

感性理解，这样的排列 $x$ 有很多。直接随即可。

输出答案的时候注意一下细节。

讲个笑话：这个人一开始忘了判 $n\neq 1$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ti chrono::system_clock::now().time_since_epoch().count()
#define ll long long
const int maxn = 1e5 + 10;
int n, a[maxn], ans[maxn], pos[maxn], orz[maxn];
mt19937 rnd(ti + size_t(new char));
void wsyakioi(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) orz[a[i]] = i;
    for(int i = 1; i <= n; i++) a[i] = orz[i];
    if(n == 1 || (n == 2 && a[1] == 2)) return printf("Impossible\n"), void();
    if(n == 3){
        int cnt = 0;
        for(int i = 1; i <= n; i++) if(a[i] == i) cnt++;
        if(cnt == 1) return printf("Impossible\n"), void();
    }
    iota(ans + 1, ans + n + 1, 1);
    while(1){
        bool suc = 1;
        shuffle(ans + 1, ans + n + 1, rnd);
        for(int i = 1; i <= n; i++) if(ans[i] == i || ans[i] == a[i]){
            suc = 0; break;
        }
        if(!suc) continue;
        for(int i = 1; i <= n; i++) pos[ans[i]] = a[i];
        printf("Possible\n");
        for(int i = 1; i <= n; i++) printf("%d ", pos[i]);
        puts(""); for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
        puts(""); return;
    }
    printf("Impossible\n");
}
int main(){
    int T; scanf("%d", &T);
    while(T--) wsyakioi();
    return 0;
}
```

---

## 作者：吴思诚 (赞：0)

# CF1773A Amazing Trick 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1773A)
## 思路
我们就按题目的意思做，要让我们构造 $p,q$ 排列，可以考虑先生成一个 $p$，再利用 $p$ 构造 $q$，当 $p$ 序列确定时，$q$ 也确定了。接下来考虑怎么生成 $p$ 序列。其实可以用随机化生成。因为 $p,q$ 都是排列，而让它们都是错排，当 $n$ 较大时，成功的概率会极大，如果很多次都不行，就可以认为是无解。这里我讲一下随机数的生成。可以使用 `shuffle`。这个函数与 `random_shuffle` 并不一样，因为它的质量比较高。需要传入三个参数，分别表示起始位置、终止位置、均匀随机位生成器。第三个参数我一般用 `mt19937`，这是一个生成高质量随机数的函数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
random_device gen;
mt19937 rd(gen());
int T,n,a[N],p[N],pos[N],POS[N],q[N];
bool check(){
    for(int i=1;i<=n;++i){
        int po=pos[i];
        q[i]=POS[po];
        if(p[i]==i||q[i]==i)return 0;
    }
    puts("Possible");
    for(int i=1;i<=n;++i)printf("%d ",p[i]);
    puts("");
    for(int i=1;i<=n;++i)printf("%d ",q[i]);
    puts("");
    return 1;
}
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",a+i),pos[a[i]]=i;
    for(int i=1;i<=n;++i)p[i]=i,POS[p[i]]=i;
    if(check())return;
    for(int i=1;i<=1000;++i){
        shuffle(p+1,p+1+n,rd);
        for(int i=1;i<=n;++i)POS[p[i]]=i;
        if(check())return;
    }
    puts("Impossible");
}
int main(){
    scanf("%d",&T);
    while(T--)solve();
    return 0;
}
```

---

