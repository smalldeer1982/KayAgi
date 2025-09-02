# The Forbidden Permutation

## 题目描述

You are given a permutation $ p $ of length $ n $ , an array of $ m $ distinct integers $ a_1, a_2, \ldots, a_m $ ( $ 1 \le a_i \le n $ ), and an integer $ d $ .

Let $ \mathrm{pos}(x) $ be the index of $ x $ in the permutation $ p $ . The array $ a $ is not good if

- $ \mathrm{pos}(a_{i}) < \mathrm{pos}(a_{i + 1}) \le \mathrm{pos}(a_{i}) + d $ for all $ 1 \le i < m $ .

For example, with the permutation $ p = [4, 2, 1, 3, 6, 5] $ and $ d = 2 $ :

- $ a = [2, 3, 6] $ is a not good array.
- $ a = [2, 6, 5] $ is good because $ \mathrm{pos}(a_1) = 2 $ , $ \mathrm{pos}(a_2) = 5 $ , so the condition $ \mathrm{pos}(a_2) \le \mathrm{pos}(a_1) + d $ is not satisfied.
- $ a = [1, 6, 3] $ is good because $ \mathrm{pos}(a_2) = 5 $ , $ \mathrm{pos}(a_3) = 4 $ , so the condition $ \mathrm{pos}(a_2) < \mathrm{pos}(a_3) $ is not satisfied.

In one move, you can swap two adjacent elements of the permutation $ p $ . What is the minimum number of moves needed such that the array $ a $ becomes good? It can be shown that there always exists a sequence of moves so that the array $ a $ becomes good.

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ , but there is $ 4 $ in the array).

## 说明/提示

In the first case, $ pos(a_1)=1 $ , $ pos(a_2)=3 $ . To make the array good, one way is to swap $ p_3 $ and $ p_4 $ . After that, the array $ a $ will be good because the condition $ \mathrm{pos}(a_2) \le \mathrm{pos}(a_1) + d $ won't be satisfied.

In the second case, $ pos(a_1)=1 $ , $ pos(a_2)=4 $ . The $ 3 $ moves could be:

1. Swap $ p_3 $ and $ p_4 $ .
2. Swap $ p_2 $ and $ p_3 $ .
3. Swap $ p_1 $ and $ p_2 $ .

 After these moves, the permutation $ p $ will be $ [2,5,4,3,1] $ . The array $ a $ will be good because the condition $ \mathrm{pos}(a_1) < \mathrm{pos}(a_2) $ won't be satisfied. It can be shown that you can't make the array $ a $ good with fewer moves.In the third case, $ pos(a_1)=1 $ , $ pos(a_2)=3 $ , $ pos(a_3)=5 $ . The $ 2 $ moves can be:

1. Swap $ p_4 $ and $ p_5 $ .
2. Swap $ p_3 $ and $ p_4 $ .

 After these moves, the permutation $ p $ will be $ [3,4,2,1,5] $ . The array $ a $ will be good because the condition $ \mathrm{pos}(a_2) < \mathrm{pos}(a_3) $ won't be satisfied. It can be shown that you can't make the array $ a $ good with fewer moves.In the fourth case, $ pos(a_1)=2 $ , $ pos(a_2)=1 $ . The array $ a $ is already good.

In the fifth case, $ pos(a_1)=2 $ , $ pos(a_2)=5 $ . The $ 2 $ moves are:

1. Swap $ p_1 $ and $ p_2 $ .
2. Swap $ p_5 $ and $ p_6 $ .

## 样例 #1

### 输入

```
5
4 2 2
1 2 3 4
1 3
5 2 4
5 4 3 2 1
5 2
5 3 3
3 4 1 5 2
3 1 2
2 2 1
1 2
2 1
6 2 4
1 2 3 4 5 6
2 5```

### 输出

```
1
3
2
0
2```

# 题解

## 作者：_acat_ (赞：2)

## sol

预处理求出每个数的 $pos$。

根据 $pos$ 和 $a$ 数组能得到 $a$ 序列的每个位置数组。

很显然，有以下情况：

1. 如果非升序，则一定是好的，答案为 $0$。

2. 否则，发现某个 `dis=pos[a[i+1]]-pos[a[i]]>d`, 则也是好的，答案为 $0$。

3. 对于符合条件的 $pos_{a_{i}}$ 和 $pos_{a_{i+1}}$，有两种方法：将对应的 $a_{i+1}$ 一直移到 $a_{i}$ 的前面，需要 $dis$ 次；或者将 $a_i$ 和 $a_{i+1}$ 远离，需要 $pos_{a_{i}}-1+n-pos_{a_{i+1}}$ 次，第二种情况还需要考虑是否左边和右边加起来够移动。

## Code

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define RFOR(i,a,b) for(int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
const int N=1e6+5;
int t,n,m,d,ans;
int p[N],a[N],pos[N];
int main(){
	t=read();
	while(t--){
		n=read(),m=read(),d=read();
		for(int i=1;i<=n;i++){
			p[i]=read();
			pos[p[i]]=i;
		}
		for(int i=1;i<=m;i++) a[i]=read();
		ans=INF;
		for(int i=1;i<m;i++){
			int dis=pos[a[i+1]]-pos[a[i]];
			if(pos[a[i+1]]<=pos[a[i]] || dis>d){
				ans=0;
				break;
			}
			ans=min(ans,dis);
			if((pos[a[i]]-1+n-pos[a[i+1]])>=d-dis+1){
				ans=min(ans,d-dis+1);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：atomic_int (赞：1)

## 题意：
题意翻译中已有。

## 分析：
如果存在 ${\rm pos}(a_i) > {\rm pos}(a_{i+1})$ 或者 ${\rm pos}(a_{i+1})-{\rm pos}(a_i)>d$ 直接返回 $0$ 即可。如果不是，对于每个 $a_i(1\leq i <m)$ 分类讨论 ${\rm pos}(a_i)<{\rm pos}(a_{i+1})$：
- 将 ${\rm pos}(a_{i+1})$ 向左移，需要移动 ${\rm pos}(a_{i+1})-{\rm pos}(a_i)$ 次。
- 将 ${\rm pos}(a_{i+1})$ 向右移，需要移动 $d+1-{\rm pos}(a_{i+1})+{\rm pos}(a_i)$ 次。这里要注意应该保证 $d + 1 < n$，否则会发生越界。

每次取两者的最小值更新答案。

## 代码：
主要片段：
```cpp
inline void solve() {
	int n, m, d, ans = inf64;
	cin >> n >> m >> d;
	vector<int> p(n + 1), a(m + 1);
	map<int, int> pos;
	for (int i = 1; i <= n; i ++) {
		cin >> p[i];
		pos[p[i]] = i;
	}
	for (int i = 1; i <= m; i ++) {
		cin >> a[i];
	}
	for (int i = 1; i < m; i ++) {
		if (pos[a[i]] > pos[a[i + 1]] || pos[a[i + 1]] - d > pos[a[i]]) {
			cout << 0 << '\n';
			return ;
		}
		int res = min(pos[a[i + 1]] - pos[a[i]], (d + 1 < n ? d + 1 - pos[a[i + 1]] + pos[a[i]] : inf64));
		ans = min(ans, res);
	}
	cout << ans << '\n';
}
```


---

## 作者：zfx_VeXl6 (赞：1)

如果序列 $a$ 已经是好的，输出 $0$。

如果想让序列 $a$ 成为好的序列，只需有一个 $i$ 不满足 $\mathrm{pos}(a_i)<\mathrm{pos}(a_{i+1})\le\mathrm{pos}(a_i)+d$ 即可。也就是说，对于一个不好的序列，只需要通过操作让其中一个 $i$ 不满足 $\mathrm{pos}(a_i)<\mathrm{pos}(a_{i+1})\le\mathrm{pos}(a_i)+d$ 就能让其变为好的序列。

对于一个满足 $\mathrm{pos}(a_i)<\mathrm{pos}(a_{i+1})\le\mathrm{pos}(a_i)+d$ 的 $i$，让其变为不满足的操作方式有两种：

一种是通过操作使 $\mathrm{pos}(a_i)\ge\mathrm{pos}(a_{i+1})$。因为 $a$ 中的数字两两不同，所以不会取到等号，即 $\mathrm{pos}(a_i)>\mathrm{pos}(a_{i+1})$。最小的操作次数即为 $\mathrm{pos}(a_{i+1})-\mathrm{pos}(a_i)$。

另一种是通过操作使 $\mathrm{pos}(a_{i+1})>\mathrm{pos}(a_i)+d$。这意味着在 $p$ 中，$a_i$ 和 $a_{i+1}$ 之间至少要隔着 $d$ 个数字，也就是说当 $d+2\le n$ 时才能进行这种操作。最小的操作次数即为 $d-(\mathrm{pos}(a_{i+1})-\mathrm{pos}(a_i)-1)$。

最后的结果就是所有的 $i$ 操作次数的最小值。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,d,p[100001],pos[100001],a[100001],ans;
int main()
{
    cin>>t;
    while(t--)
    {
        int f=0;
        ans=1145141919;
        cin>>n>>m>>d;
        for(int i=1;i<=n;i++)
        {
            cin>>p[i];
            pos[p[i]]=i;
        }
        for(int i=1;i<=m;i++)
            cin>>a[i];
        for(int i=1;i<m&&!f;i++)
            if(!(pos[a[i]]<pos[a[i+1]]&&pos[a[i+1]]<=pos[a[i]]+d))
                f=1;
        if(f)
        {
            cout<<0<<'\n';
            continue;
        }
        for(int i=1;i<m;i++)
            if(pos[a[i]]<pos[a[i+1]]&&pos[a[i+1]]<=pos[a[i]]+d)
            {
                ans=min(ans,pos[a[i+1]]-pos[a[i]]);
                if(d<=n-2)
                    ans=min(ans,d-(pos[a[i+1]]-pos[a[i]]-1));
            }
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1778B)

注意到当 $a$ 是不好的，必须所有的 $a_i$ 都满足题目条件。也就是说，我们只需修改一对数（显然这样步数最少）。

对于每一对数，我们有两种方法将其变为好的：

- 操作 $p$ 数组直到 $\operatorname{pos}(a_{i+1})<\operatorname{pos}(a_{i})$。

- 同时移动 $a_i,a_{i+1}$ 的位置，直到 $\operatorname{pos}(a_{i+1})>\operatorname{pos}(a_{i})+d$。

两种情况步数分别取最小值，其中后者需要特判是否会移动出界。

无解很好判断，具体见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,d,a[N],p[N],l[N];
int solve()
{
    int ret=1e9;
    scanf("%d%d%d",&n,&m,&d);
    for(int i=1;i<=n;i++)scanf("%d",&p[i]);
    for(int i=1;i<=m;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)l[p[i]]=i;
    for(int i=1;i<m;i++)
        if(l[a[i+1]]>l[a[i]]&&l[a[i+1]]<=l[a[i]]+d)
        {
            ret=min(ret,l[a[i+1]]-l[a[i]]);
            if(d+1<n)ret=min(ret,l[a[i]]+d-l[a[i+1]]+1);
        }
        else return 0;
    return ret;
}
signed main()
{
    int T;
    scanf("%d",&T);
    while(T--)printf("%d\n",solve());
    return 0;
}
```

---

## 作者：yimuhua (赞：0)

如果 $a$ 已经是好的，答案显然为 $0$。对于每一对 $a_i$ 和 $a_{i+1}(i<m)$，可以发现只有两种情况可以使 $a$ 变好：

设 $y$ 为 $a_i$ 与 $a_{i+1}$ 中 $pos$ 较右的，$x$ 为较左的。

1.使 $pos(y)>pos(x)+d$，需要 $d-(pos(y)-pos(x))+1$ 次操作。

2.使 $pos(y)<pos(x)$，需要 $pos(y)-pos(x)$ 次操作。

于是对于每对 $a_i$ 和 $a_{i+1}$ 求最小值即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m, d, ans, p[200005], a[200005], pos[200005];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> m >> d, ans = 1e9;
        for(int i = 1; i <= n; i++)
            cin >> p[i], pos[p[i]] = i;
        for(int i = 1; i <= m; i++)
            cin >> a[i];
        for(int i = 1; i < m; i++) {
            ans = min(ans, max(0, pos[a[i + 1]] - pos[a[i]]));
            if(1 + d < n)
                ans = min(ans, max(0, pos[a[i]] + d + 1 - pos[a[i + 1]]));
        }
        cout << ans << '\n';
    }
    return 0;
}
```


---

