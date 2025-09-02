# Ralph And His Tour in Binary Country

## 题目描述

Ralph is in the Binary Country. The Binary Country consists of $ n $ cities and $ (n-1) $ bidirectional roads connecting the cities. The roads are numbered from $ 1 $ to $ (n-1) $ , the $ i $ -th road connects the city labeled ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF894D/680973cce2f1e5e60b4409ccf1cbf5b447773a47.png) (here $ ⌊\ x⌋ $ denotes the $ x $ rounded down to the nearest integer) and the city labeled $ (i+1) $ , and the length of the $ i $ -th road is $ L_{i} $ .

Now Ralph gives you $ m $ queries. In each query he tells you some city $ A_{i} $ and an integer $ H_{i} $ . He wants to make some tours starting from this city. He can choose any city in the Binary Country (including $ A_{i} $ ) as the terminal city for a tour. He gains happiness $ (H_{i}-L) $ during a tour, where $ L $ is the distance between the city $ A_{i} $ and the terminal city.

Ralph is interested in tours from $ A_{i} $ in which he can gain positive happiness. For each query, compute the sum of happiness gains for all such tours.

Ralph will never take the same tour twice or more (in one query), he will never pass the same city twice or more in one tour.

## 说明/提示

Here is the explanation for the second sample.

Ralph's first query is to start tours from city $ 2 $ and $ H_{i} $ equals to $ 4 $ . Here are the options:

- He can choose city $ 5 $ as his terminal city. Since the distance between city $ 5 $ and city $ 2 $ is $ 3 $ , he can gain happiness $ 4-3=1 $ .
- He can choose city $ 4 $ as his terminal city and gain happiness $ 3 $ .
- He can choose city $ 1 $ as his terminal city and gain happiness $ 2 $ .
- He can choose city $ 3 $ as his terminal city and gain happiness $ 1 $ .
- Note that Ralph can choose city $ 2 $ as his terminal city and gain happiness $ 4 $ .
- Ralph won't choose city $ 6 $ as his terminal city because the distance between city $ 6 $ and city $ 2 $ is $ 5 $ , which leads to negative happiness for Ralph.

So the answer for the first query is $ 1+3+2+1+4=11 $ .

## 样例 #1

### 输入

```
2 2
5
1 8
2 4
```

### 输出

```
11
4
```

## 样例 #2

### 输入

```
6 4
2
1
1
3
2
2 4
1 3
3 2
1 7
```

### 输出

```
11
6
3
28
```

# 题解

## 作者：Kelin (赞：4)

## [题解](https://blog.csdn.net/BeNoble_/article/details/107156232)

这棵树是一颗完全二叉树。

设 ${\rm dep}_u$ 表示 $u$ 到 $1$ 的距离。

分别考虑 $u$ 子树内的答案和子树外的答案：

### $1.$ 子树内的答案

即：

$$\sum_{{\rm dep}_v-{\rm dep}_u<H}H-({\rm dep}_v-{\rm dep}_u)=\sum_{{\rm dep}_v<H+{\rm dep}_u}(H+{\rm dep}_u)-{\rm dep}_v=s(H+{\rm dep}_u)-\sum_{{\rm dep}_v<H+{\rm dep}_u}{\rm dep}_v$$

其中 $s=\sum[{\rm dep}_v<H+{\rm dep}_u]$ 。

将 $u$ 子树内所有的 ${\rm dep}_v$ 放到的一个数组 $a_u$ 中，对 $a_u$ 排序后求其前缀和数组 ${\rm Sum}_u$ 。

那么这部分答案就可以通过对 $a_u$ 数组二分得到 $s$ 算出来，即 $s(H+{\rm dep}_u)-{\rm Sum}_u[s]$ 。

### $2.$ 父亲 $fa_u$ 及其兄弟节点 $w$ 

父亲的答案即 $H-L_u$ 。兄弟节点 $w$ 的子树内的节点的答案即：

$$\sum_{{\rm dep}_v-{\rm dep}_w+L_u+L_w<H}H-({\rm dep}_v-{\rm dep}_w+L_u+L_w)=s'(H+{\rm dep}_w-L_u-L_w)-\sum_{{\rm dep}_v<H+{\rm dep}_w-L_u-L_w}{\rm dep}_v$$

可以发现上式和 $1.$ 中的式子形式相同，故可以统一处理。

### $3.$ 父亲的父亲及父亲的兄弟节点......

由于这是棵完全二叉树，故暴力跳父亲算答案最多跳 $\log n$ 次，算上二分的 $\log n$ ，单次询问复杂度为 $\log^2n$ 。

$a_u$ 可以自底向上通过归并求出，且根据完全二叉树的特性，可以采用非递归的形式求解降低常数。

时间复杂度 $O(n\log n+m\log^2n)$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
typedef long long ll;
int n, m, dep[N], Len[N];
vector<int> a[N];
vector<ll> Sum[N];
inline ll Calc(int u, int H) {
    if (H <= 0 || !a[u].size())
        return 0;
    int s = lower_bound(a[u].begin(), a[u].end(), H) - a[u].begin();
    return s ? (ll)s * H - Sum[u][s - 1] : 0;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; ++i)
        scanf("%d", Len + i);
    for (int u = 1; u <= n / 2; ++u) {
        int L = u << 1, R = L | 1;
        if (L <= n)
            dep[L] = dep[u] + Len[L];
        if (R <= n)
            dep[R] = dep[u] + Len[R];
    }
    for (int u = n; u; --u) {
        int L = u << 1, R = L | 1;
        a[u].emplace_back(dep[u]);
        if (R <= n)
            merge(a[L].begin(), a[L].end(), a[R].begin(), a[R].end(),
                  back_inserter(a[u]));
        else if (L <= n)
            a[u].insert(a[u].end(), a[L].begin(), a[L].end());
        Sum[u].resize(a[u].size());
        Sum[u][0] = a[u][0];
        for (int i = 1; i < (int)Sum[u].size(); ++i)
            Sum[u][i] = Sum[u][i - 1] + a[u][i];
    }
    for (int u, H; m--;) {
        scanf("%d%d", &u, &H);
        ll Ans = Calc(u, H + dep[u]);
        for (H -= Len[u]; H > 0 && u != 1; H -= Len[u >>= 1])
            Ans += H + Calc(u ^ 1, H - Len[u ^ 1] + dep[u ^ 1]);
        printf("%lld\n", Ans);
    }
    return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：1)

题意非常清晰，这里就不再赘述。

考虑到这是一个完全二叉树，所以如果每个点直接记录子树的所有权值，所需空间是 $O(n\log n)$ 的，也就是说我们其实存的下。

于是接下来就能想到一个简单的做法：从当前节点开始，先求出当前子树的合法答案之和，接着跳到当前节点的父亲节点，解决另一个儿子的子树；再跳到父亲节点，解决另一个儿子的子树……

直到我们已经走完了 $H$ 的距离，后面不会对答案产生影响，就可以结束了。

```cpp
int n,m;
ll ls[1000005],rs[1000005];
vector<ll>al[1000005],s[1000005];
void dfs(int now){
	if((now<<1)<=n)dfs(now<<1);
	if((now<<1|1)<=n)dfs(now<<1|1);
	if((now<<1)>n){
		al[now].push_back(0);
		ll curs=0;
		for(auto i:al[now])s[now].push_back(curs+=i);
		return;
	}
	if((now<<1)==n){
		al[now].push_back(0);
		for(auto i:al[now<<1])al[now].push_back(ls[now]+i);
		ll curs=0;
		for(auto i:al[now])s[now].push_back(curs+=i);
		return;
	}
	vector<ll>&a=al[now],&l=al[now<<1],&r=al[now<<1|1];
	a.push_back(0);
	int i=0,j=0;// 归并两个儿子
	while(i<l.size()&&j<r.size()){
		if(l[i]+ls[now]<=r[j]+rs[now])a.push_back(l[i]+ls[now]),i++;
		else a.push_back(r[j]+rs[now]),j++;
	}
	while(i<l.size())a.push_back(l[i]+ls[now]),i++;
	while(j<r.size())a.push_back(r[j]+rs[now]),j++;
	ll curs=0;
	for(auto i:al[now])s[now].push_back(curs+=i);
}
ll calc(int now,ll mx){// 计算子树
	if(mx<0||now>n)return 0;
	int id=lower_bound(all(al[now]),mx)-al[now].begin()-1;
	if(id<0)return 0;
	return mx*(id+1)-s[now][id];
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	cin>>n>>m;
	for(int i=2;i<=n;i++)if(i&1)cin>>rs[i>>1];else cin>>ls[i>>1];
	dfs(1);
	while(m--){
		int a,h;
		cin>>a>>h;
		ll ans=calc(a,h);
		for(;a>1;a>>=1){// 不断向上跳
			h-=((a&1)?rs[a>>1]:ls[a>>1]);
			if(h<=0)break;
			ans+=h+calc(a^1,h-((a&1)?ls[a>>1]:rs[a>>1]));
		}
		cout<<ans<<"\n";
	}
}
```

---

