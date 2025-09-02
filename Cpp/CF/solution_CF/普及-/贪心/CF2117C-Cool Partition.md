# Cool Partition

## 题目描述

鸭鸭有一个大小为 $ n $ 的数组 $ a $。他想将这个数组分割成一个或多个连续的段，使得每个元素 $ a_i $ 恰好属于一个段。

如果对于每一个段 $ b_j $，所有在 $ b_j $ 中的元素也出现在 $ b_{j + 1} $ 中（如果存在的话），那么这个分割就被称为**酷分割**。也就是说，一个段中的每一个元素必须也出现在它之后的段中。

例如，如果 $ a = [1, 2, 2, 3, 1, 5] $，鸭鸭可以做出一个酷分割 $ b_1 = [1, 2] $，$ b_2 = [2, 3, 1, 5] $。这是一个酷分割，因为 $ b_1 $ 中的所有元素（即 $ 1 $ 和 $ 2 $）也出现在 $ b_2 $ 中。相反，$ b_1 = [1, 2, 2] $，$ b_2 = [3, 1, 5] $ 不是一个酷分割，因为 $ 2 $ 出现在 $ b_1 $ 中但没有出现在 $ b_2 $ 中。

注意，在分割数组后，不能改变段的顺序。另外，如果一个元素在某段 $ b_j $ 中出现多次，它只需要在 $ b_{j + 1} $ 中出现至少一次。

你的任务是帮助鸭鸭找到一个酷分割的最大段数。

## 说明/提示

第一个测试用例在题目描述中已经解释过。我们可以将其分割为 $ b_1 = [1, 2] $，$ b_2 = [2, 3, 1, 5] $。可以证明没有其他分割方式能得到更多的段。

在第二个测试用例中，我们可以将数组分割为 $ b_1 = [1, 2] $，$ b_2 = [1, 3, 2] $，$ b_3 = [1, 3, 2] $。最大段数为 $ 3 $。

在第三个测试用例中，唯一可行的分割是 $ b_1 = [5, 4, 3, 2, 1] $。任何其他分割方式都无法满足条件。因此，答案是 $ 1 $。

## 样例 #1

### 输入

```
8
6
1 2 2 3 1 5
8
1 2 1 3 2 1 3 2
5
5 4 3 2 1
10
5 8 7 5 8 5 7 8 10 9
3
1 2 2
9
3 3 1 4 3 2 4 1 2
6
4 5 4 5 6 4
8
1 2 1 2 1 2 1 2```

### 输出

```
2
3
1
3
1
3
3
4```

# 题解

## 作者：Program_A2 (赞：5)

> 一个分段中的每个元素都必须同时出现在它后面的分段中。

由这句话不难看出，$b_j$ 包含了此前出现过的所有数，而想要 $b_j+1$ 满足题目中的条件，也必须包含 $b_j$ 里出现过的所有数。为方便存储，我们可以用 set 来存储，因为这个容器里不会出现同样的数，因为要尽可能多分，所以比较两个分区的数字数量是否相同就行了。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
		int n,ans=0;
		set<int>s,g;           //set数组，其中s容器表示下一个要分的分区，g容器表示此前出现的所有数
		cin>>n;
		int a[n+1];
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			g.insert(a[i]);
			s.insert(a[i]);
			if(g.size()==s.size()){
				ans++;
				s.clear();         //记得清空
			}
		}
		if(ans==0)cout<<1<<'\n';else cout<<ans<<'\n';      //记得带上特判
	}
    return 0;
}

```

---

## 作者：zhujiajun2013 (赞：2)

先放代码吧。
### AC code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n,ans;
int a[N];
set<int>u,v; 
int main() {
	cin>>t;
	while(t--){
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		u.clear();v.clear(); 
		for(int i=1;i<=n;i++){
			u.insert(a[i]);
			v.insert(a[i]);
			if(u.size()==v.size()){
				ans++;
				u.clear();
			}
		}
		if(!ans)cout<<1;
		else cout<<ans;
		cout<<"\n";
	}
	return 0;
}
```
### 代码解析

这代码其实挺巧妙的，核心思路就是利用两个集合 $u$ 和 $v$ 来动态维护分段信息。

#### 变量说明
$u$：记录当前分段内的所有元素（相当于一个临时容器）。

$v$：记录从数组开头到当前位置的所有元素（相当于全局记录）。
 
$ans$：最终要输出的最大分段数。

### 核心逻辑
每次循环时：
先把当前元素 $a_i$ 丢进 $u$ 和 $v$ 里，判断： `if(u.size() == v.size())` 这个条件成立说明当前分段 $v$ 里的元素和全局 $u$ 完全一致。也就是说，从数组开头到现在为止的所有元素，都在当前分段里出现过。这时候就可以在这里直接分段。

这样就能得出正确答案啦。

---

## 作者：P2441M (赞：2)

## 题意

给定一个长度为 $n$ 的序列 $a$，将其划分为若干连续子段。称一种划分方案是合法的，当且仅当其中每一个段都包含了前一个段的所有元素。多测，$1\leq T\leq 10^4$，$1\leq a_i\leq n\leq \sum{n}\leq 2\times 10^5$。

## 题解

~~我真是无聊透了。~~

提供一个线性做法。

划段肯定是能划就划。假设我们划分出一个段 $[l,r]$，那么考虑如何确定下一个段的右端点。其实很简单，预处理 $nxt_i$ 表示 $a_i$ 右边第一个与 $a_i$ 相同的位置，那么下一个段的右端点就是 $\max_{i=l}^r nxt_i$。扫一扫，跳一跳，就做完了。

时间复杂度 $\mathcal{O}(n)$。

## 代码

```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 2e5 + 5;

int t, n, a[N], nxt[N], pos[N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while (t--) {
    	cin >> n;
    	for (int i = 1; i <= n; ++i) cin >> a[i];
    	for (int i = 1; i <= n; ++i) pos[i] = n + 1;
    	for (int i = n; i; --i) nxt[i] = pos[a[i]], pos[a[i]] = i;
    	int l = 1, r = 1, ans = 1;
    	while (true) {
    		int mx = 0;
    		for (int i = l; i <= r; ++i) chk_max(mx, nxt[i]);
    		if (mx == n + 1) break;
    		l = r + 1, r = mx;
    		++ans;
    	}
    	cout << ans << '\n';
    }
    return 0;
}
```

---

## 作者：Mier_Samuelle (赞：2)

不难想到贪心策略：对于每个位置，如果可以断开必定断开。

> 证明：假设当前位置为 $i$ 且可以断开。如果最优方案是在位置 $j$（$j>i$）断开的话，我们可以将位置 $[i+1,j]$ 并入下一段内。
>
> 根据我们的假设，这样做一定是合法的，并且由于当前段中的元素变少了，我们的总段数也一定不会变少。
>
> 最后一段是否合法也不影响，因为如果不合法，我们可以简单地将其并入前面一段，这样做不会影响总段数。

考虑实现，可以开两个 ``set``，一个存前一段中的元素（记作集合 $A$），一个存当前段中的元素（记作集合 $B$）。

遍历到 $a_i$ 时，将其从 $A$ 中移除，并将其加入 $B$。当 $A$ 为空时，即意味着可以从当前位置断开，此时更新答案并将 $B$ 作为新的 $A$ 继续遍历。

时间复杂度 $O(n \log n)$。

[CF 提交记录](https://codeforces.com/contest/2117/submission/323454722)

---

## 作者：Prico (赞：1)

### 思路

#### 就一步：

经过我~~查看标签~~的深思熟虑，这题显然**贪心**是成立的。

为什么？

因为遇到可以断的点就断，那必定是最优的。也就是当遇到当前已选数段中的任意元素相同的数，就断开。

那就很容易想到 **set** 类型，开俩，一个记录已选数段中的元素，一个记录当前判断哪一个。（说起 set 想起了 24 年 J 组的复赛第一题）。

本题需要用到 set 的这几个功能：

1. insert：添加元素。

2. size：与字符串的 size 相同，计算长度。

3. clear：清空。

记得**特判**，即当整个数列都没有重复数的话，只有这个数列本身这一种情况。

### Code：


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200010];
int main(){
	int t;//询问次数 
	cin>>t;
	while(t--){//t次询问 
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){//不用清空数组是因为这里输入直接把之前的覆盖掉了 
			cin>>a[i];
		}
		int cnt=0;//用来计数最大段数
		set<int>zsh,qjh;
		for(int i=1;i<=n;i++){
			zsh.insert(a[i]);
			qjh.insert(a[i]);
			if(zsh.size()==qjh.size()){
				cnt++;
				zsh.clear();//相比第10行，这里要清空是因为会影响后面的结果 
			} 
		} 
		if(ans==0){
			cout<<1<<"\n";//换行不要用endl,很慢 
		} 
		else{
			cout<<ans<<"\n";
		} 
	}
    return 0;
}

```

---

## 作者：shihanyu2013 (赞：1)

> 如果一个元素在某段 $b_j$ 中出现多次，它只需要在 $b_{j+1}$ 中出现至少一次。

这句话明显告诉我们本题应使用 `set` 通过，因为 `set` 中不会出现值相同的元素。[不会用的戳这里。](https://oi-wiki.org/lang/csl/associative-container/)

我们声明两个 `set` 类型，第一个用来记录 $i$ 之前出现过哪些数，另一个用于记录当前这一段的数，每次把 $a_i$ 加入两个 `set`，如果两个 `set` 中元素数量相同，说明可以分割，为了多分一些，我们能分就分，`ans++` 然后清空第二个 `set`。

---

## 作者：Listar (赞：0)

[传送门](https://codeforces.com/contest/2117/problem/C)

思路
---

第一组划分之后，我们如果想让划分组数尽可能的多，就应该让后边每一组的长度尽可能的小，我们不难理解如果第 $i$ 组多了一个元素，那么第 $i+1$ 组的长度不会变小。

我们不妨假设第 $k$ 组的长度已经尽可能的小了，要使第 $k+1$ 组的长度最小，我们只需要找到一个尽可能小的 $l$ 使得 $k+1$ 组包含 $k$ 组中所有不同元素满足题目要求。

我们给出数学归纳法中递推的证明了，现在只需要使得第一组足够小即可。

第一组取元素没有限制，当第一组仅包含第一个元素的时候长度可以取到最小值。由数学归纳法立即可知，我们找到的方法去求出的第 $k$ 组元素的长度可以取到最小值。

我们只需要通过将第一个元素单独分为第一组，通过模拟的方法就可以求出之后每一组最短长度，如果最后元组有剩余元素没有被划分，我们将它们分到最后一组中。


代码实现
---

代码实现并不容易。

我们可以将创建两个 set，通过 set 来查找当前组需要查找到的不同元素，并且记录下一组需要查找到的不同元素，可以实现时间复杂度 $\operatorname{O}(n\operatorname{log}n)$。

我这里采用时间戳的方法，把时间复杂度优化到 $\operatorname{O}(n)$。

通过记录当前时间有多少个不同元素需要被查找到，每个元素进入查找的时候去检查它是否需要被查找到并记录下来，同时更新每个元素的时间戳，保证下一次需要查找到这个元素。


```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int a[N], lp[N], p[N];

void solve(){
    int n, flg = 0, tm = 1, ans = 1;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        lp[i] = 0;
        p[i] = 0;
    }
    lp[a[1]] = 1;
    p[1] = 1;
    for(int i = 2; i <= n; i++){
        if (lp[a[i]] == tm){
            p[tm] --;
            lp[a[i]] = tm + 1;
            p[tm+1] ++;
            if (!p[tm]){
                ans ++;
                tm ++;
                continue;
            }
        }
        else{
            if (lp[a[i]] != tm + 1){
                lp[a[i]] = tm + 1;
                p[tm + 1] ++;
            }
        }
    }
    cout << ans << endl; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_ --) {
        solve();
    }
    return 0;
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF2117C)
# 思路
从题目中不难看出，$b_j$ 需要包含 $b_1 \sim b_{j-1}$ 所出现过的所有数。我们可以建两个 set，一个记录一个段的数 $s$，另外一个记录之前的所有数 $sall$，当两个 set 的长度一样说明成功找到了一个段，那么此时数量 $+1$，并且清空 $s$。

最后还要再特判一下，当数量为 $0$ 时，说明无法分割，只有一大段（即原数组），此时答案为 $1$。
# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N]; 
void solve()
{
	set<int> s,sall;
	int n;
	cin >>n;
	int cnt=0;
	for(int i=1;i<=n;i++) cin >>a[i];
	for(int i=1;i<=n;i++)
	{
		s.insert(a[i]);
		sall.insert(a[i]);
		if(s.size()==sall.size())
		{
			cnt++;
			s.clear();
		}
	}
	if(!cnt) cout <<cnt<<'\n';
	else cout <<cnt<<'\n';
}
int main()
{
	int t;
	cin >>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

## 作者：c_legg (赞：0)

## 题意

<https://www.luogu.com.cn/problem/CF2117C>

<https://vjudge.net/problem/CodeForces-2117C#author=DeepSeek_zh>

## 思路

从前往后划分显然太麻烦了，考虑从后往前扫描。

用一个 `map` 表示目前还有多少个数字，以及每个数字出现了多少次；用一个 `set` 表示目前的这一段还要加入多少个数字。

如果这个 `set` 空了，就可以划分出一个新的段，就要把 `map` 中的所有元素加到这个 `set` 里，然后继续扫描并更新 `map` 和 `set`。

这样的分割方式是贪心的，可以将段数最大化。

具体实现细节见代码。

## 代码

``` cpp
#include <bits/stdc++.h>
typedef long long ll;
#define one(x) ((ll)(1e##x))
using namespace std;
typedef pair<int, int> pii;

int t;

int n, ans, k;

int a[200010];

unordered_map<int, int> cnt;

unordered_set<int> need;

void slove() {
    cin>>n;
    ans=0;
    cnt.clear();
    need.clear();
    for(int i(1); i<=n; i++) {
        cin>>a[i];
        cnt[a[i]]++;
    }
    for(auto i : cnt) need.insert(i.first);
    for(int i(n); i>=1; i--) {
        cnt[a[i]]--;
        if(need.count(a[i])) need.erase(a[i]);
        if(cnt[a[i]]==0) cnt.erase(a[i]);
        if(need.size()==0) {
            ans++;
            for(auto i : cnt) need.insert(i.first);
        }
    }
    cout<<ans<<"\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    
    cin>>t;
    
    while(t--) slove();
    return 0;
}
```

---

