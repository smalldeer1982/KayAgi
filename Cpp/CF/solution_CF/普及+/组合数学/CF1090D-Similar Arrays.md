# Similar Arrays

## 题目描述

Vasya had an array of $ n $ integers, each element of the array was from $ 1 $ to $ n $ . He chose $ m $ pairs of different positions and wrote them down to a sheet of paper. Then Vasya compared the elements at these positions, and wrote down the results of the comparisons to another sheet of paper. For each pair he wrote either "greater", "less", or "equal".

After several years, he has found the first sheet of paper, but he couldn't find the second one. Also he doesn't remember the array he had. In particular, he doesn't remember if the array had equal elements. He has told this sad story to his informatics teacher Dr Helen.

She told him that it could be the case that even if Vasya finds his second sheet, he would still not be able to find out whether the array had two equal elements.

Now Vasya wants to find two arrays of integers, each of length $ n $ . All elements of the first array must be distinct, and there must be two equal elements in the second array. For each pair of positions Vasya wrote at the first sheet of paper, the result of the comparison must be the same for the corresponding elements of the first array, and the corresponding elements of the second array.

Help Vasya find two such arrays of length $ n $ , or find out that there are no such arrays for his sets of pairs.

## 样例 #1

### 输入

```
1 0
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3 1
1 2
```

### 输出

```
YES
1 3 2 
1 3 1 
```

## 样例 #3

### 输入

```
4 3
1 2
1 3
2 4
```

### 输出

```
YES
1 3 4 2 
1 3 4 1 
```

# 题解

## 作者：rui_er (赞：3)

一道简单构造题。

如果 $m=\frac{n(n-1)}{2}$，此时任意两个数都要有偏序关系，但是又要求第二个数列有两个数相等，因此无解。

否则一定有解。不难想到构造两个数列使它们几乎完全相等。可以找到两个没有偏序关系的下标 $(i,j)$，在第一个数列中分别赋值为 $n-1,n$，在第二个数列中均赋值为 $n-1$。剩下的数随便填，让两个数列对应位置相等即可。

```cpp
// Problem: CF1090D Similar Arrays
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1090D
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
	uniform_int_distribution<int> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 1e5+5;

int n, m, vis[N], a[N];
vector<int> e[N];

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	if(m == n * (n - 1) / 2) return puts("NO")&0;
	int pa = -1, pb = -1, now = 0;
	rep(i, 1, n) {
		if((int)e[i].size() == n - 1) continue;
		for(int j : e[i]) vis[j] = 1;
		rep(j, 1, n) if(i != j && !vis[j]) {pa = i; pb = j; break;}
		break;
	}
	rep(i, 1, n) if(i != pa && i != pb) a[i] = ++now;
	a[pa] = n - 1; a[pb] = n;
	puts("YES");
	rep(i, 1, n) printf("%d%c", a[i], " \n"[i==n]);
	rep(i, 1, n) printf("%d%c", min(a[i], n-1), " \n"[i==n]);
	return 0;
}

```

---

## 作者：Ryder00 (赞：1)

题意清晰，不再阐述。

## 思路
把输入进来的约束关系看作边，建出一张图。我们的目的是对这些边定向，满足大小关系后，选出两个点赋成一样的值，且不与之前存在的关系矛盾。

显然，这两个点在输入里必须没有约束关系。我们可以贪心的将这两个点的值赋成 $1$，这样其他关于这两个点的约束关系中，永远是这两个点小。

对于剩下的点，我们发现，可以贪心的用度数来赋值。度数越少，说明约束关系越少，值也尽量小。用类似拓扑排序的做法，对剩余的点按照度数从小到大赋值。这样就完成了构造。

代码长得很恶心。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define tup tuple<int,int,int> 
#define mkt make_tuple
#define _ 0
const int N=1e5+10,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n,m,ans[N],siz[N],vis[N],tim[N],cnt;
vector<int> e[N];
set<tup> s;
void work(int x){
    ans[x]=++cnt;
    vis[x]=1;
    tim[x]=cnt;
    for(int y:e[x]){
        if(vis[y]) continue;
        s.erase(s.find(mkt(siz[y],tim[y],y)));
        siz[y]--;
        tim[y]=cnt;
        s.insert(mkt(siz[y],tim[y],y));
    }
}
void solve(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        if(u>v) swap(u,v);
        e[u].pb(v),e[v].pb(u);
    }
    if(m==(n-1)*n/2){
        cout<<"NO"<<endl;
        return ;
    }
    for(int i=1;i<=n;i++){
        siz[i]=e[i].size();
        tim[i]=0;
        s.insert(mkt(e[i].size(),0,i));
    }
    auto pp=*s.begin();
    int head=get<2>(pp);
    s.erase(s.begin());
    work(head);

    set<tup> qq;
    qq.clear();
    for(int i=1;i<=n;i++){
        if(i==head) continue;
        qq.insert(mkt(e[i].size(),0,i));
    }
    for(int y:e[head]){
        qq.erase(qq.find(mkt(e[y].size(),0,y)));
    }
    int head2=get<2>(*qq.begin());
    s.erase(mkt(e[head2].size(),0,head2));
    work(head2);

    while(!s.empty()){
        auto p=*s.begin();
        int x=get<2>(p);
        s.erase(s.begin());
        ans[x]=++cnt;
        vis[x]=1;
        tim[x]=cnt;
        for(int y:e[x]){
            if(vis[y]) continue;
            s.erase(s.find(mkt(siz[y],tim[y],y)));
            siz[y]--;
            tim[y]=cnt;
            s.insert(mkt(siz[y],tim[y],y));
        }
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    ans[head]=ans[head2]=1;
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    // ios::sync_with_stdio(false),cin.tie(0);
    while(T--){
        solve();
    }
    // cerr<<endl<<"Time: "<<1.0*clock()/CLOCKS_PER_SEC<<" s";
    return ~~(0^_^0);
}
```

---

