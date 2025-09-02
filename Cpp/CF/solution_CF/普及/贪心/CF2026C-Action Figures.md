# Action Figures

## 题目描述

在 Monocarp 家附近有一家商店，专门售卖手办。近期，这家店将推出一套新的手办系列，总共包含 $n$ 个手办。其中，第 $i$ 个手办的价格为 $i$ 枚金币。在第 $i$ 天到第 $n$ 天之间，这个手办都是可以购买的。

Monocarp 知道他在这 $n$ 天中的哪几天可以去商店。

每次去商店的时候，他可以购买多件手办（当然，不能买尚未发售的手办）。如果他在同一天购买了至少两个手办，他可以享受一个折扣：他所购买的最贵手办是免费的，也就是说他无需为该手办支付费用。

Monocarp 的目标是从这个手办系列中，分别购买一个第 $1$ 个手办、一个第 $2$ 个手办……一直到一个第 $n$ 个手办。注意，每个手办只能购买一次。请你帮他计算，他最少需要花费多少金币？

## 说明/提示

在第一个测试用例中，Monocarp 可以在第一天购买第一个手办，花费 1 枚金币。

在第二个测试用例中，他可以在第三天购买第 1 和第 3 个手办，在第四天购买第 2 和第 4 个手办，在第六天购买第 5 和第 6 个手办。这样总费用为 $1+2+5=8$ 枚金币。

在第三个测试用例中，他可以在第三天购买第 2 和第 3 个手办，其余手办在第七天购买，最终花费 $1+2+4+5+6 = 18$ 枚金币。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4
1
1
6
101101
7
1110001
5
11111```

### 输出

```
1
8
18
6```

# 题解

## 作者：Drifty (赞：3)

### Solution

贪心地匹配，从大到小枚举 $i$：

- 如果 $s_i = 0$ 那么这个东西一定会花钱，计入答案，下一个。
- 如果 $s_i = 1$，如果当前存在 $j$ 使得 $j < i \land s_j = 0$ 那么让 $i$ 和 $j$ 一起买，这样 $i$ 就不会花钱，否则找出当前还没被买的最小的 $k\land s_k = 1$，让 $i$ 和 $k$ 一起买更优。因为 $i$ 和 $k$ 必然有一个要花钱，而 $i>k$。

然后都扔 `set` 里面维护一下就好。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int T, n; string s;
void solve() {
    cin >> n >> s;
    set <int> S({0}), T;
    i64 ans = 0;
    for (int i = 1; i <= n; i ++) {
        if (s[i - 1] == '0') S.insert(i), ans += i;
        if (s[i - 1] == '1') T.insert(i);
    }
    while (T.size()) {
        auto it = S.upper_bound(*T.rbegin());
        if (*(-- it) == 0) {
            ans += *T.begin(); T.erase(*T.begin());
            if (T.size() >= 1) T.erase(*T.rbegin());
        } 
        else S.erase(*it), T.erase(*T.rbegin());
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    for (cin >> T; T --; ) solve();
    return 0;
}
```

---

## 作者：zhouruoheng (赞：3)

首先肯定要贪心考虑，尽可能优惠后面的商品，尽可能多的优惠。

等于 $0$ 的商品肯定不能优惠，因为可以有更优的选择。

将 $0$ 和 $1$ 分开，用双端队列存 $1$ 的位置，每次取队尾，然后肯定是有 $0$ 就用 $0$ 的位置出现的商品和当前的拼起来优惠，否则取队首的 $1$。如果都没有的话就不能优惠。

``` cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
const int N=4e5+5;
int n;
string s;
deque<int> dq;
int st[N],tot;
ll ans;
void solve()
{
    cin>>n;
    cin>>s;
    tot=ans=0;
    for(int i=0;i<n;i++) 
    {
        if(s[i]-'0') dq.push_back(i+1);
        else st[++tot]=i+1;
        ans+=i+1;
    }
    while(dq.size())
    {
        int x=dq.back();dq.pop_back();
        while(tot&&st[tot]>x) tot--;
        if(tot) 
        {
            tot--;
            ans-=x;
        }
        else 
        {
            if(dq.size())
            {
                dq.pop_front();
                ans-=x;
            }
        }

    }
    cout<<ans<<'\n';
}
int main ()
{
    #ifndef ONLINE_JUDGE 
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    int T;
    cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：__Louis__ (赞：2)

### 题解：CF2026C Action Figures

### 题目大意

一共有 $n$ 天，每一天都会上架一种不同的玩具，其售价为 $i$，在第 $i$ 天上架。

现在你可以去超市买玩具，每一种玩具只能买一次，同时，如果有一天你买到了多个玩具，那么你买的玩具中售价最高的可以免费拿走。

同时再给你一个 $0/1$ 序列，表示你哪天能去，哪天不能去，求最小代价。保证最后一个为 $1$。

### 思路

首先我们可以转换问题，转换成最多可以优惠多少。

然后考虑贪心，我们从后面开始找 $1$ 的位置。

对于每一个 $1$。只要选择前面的某一天，那么这个位置的值一定能被我们免费拿走。

那么我们贪心的找出在这个 $1$ 前面的，离这个 $1$ 最近的 $0$ 或者最远的 $1$（先找 $0$ 再找 $1$ 才行)进行配对，就可以求出答案了。

如何证明？

首先证先找 $0$ 再找 $1$，如果我们先找了 $1$，很明显这些 $1$ 可以对应到其余的 $0$ 上，使得答案更加优秀。

然后考虑 $0$ 为什么最近，因为如果选择远的，那么有可能把前面的 $1$ 要寻找的 $0$ 匹配了，使得答案不优秀。

在考虑为什么找远的 $1$，很明显越远的 $1$ 的代价越小，越后面的 $1$ 答案越大。

复杂度可以做到 $O(n)$。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f3f3f

int n;
const int maxn=4e5+10;
char s[maxn];
bool g[maxn];
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%s",&n,s+1);
		int sum=0;
		for(int i=0;i<=n+3;i++){
			g[i]=false;
		}
		int _0=n-1,_1=1;
		for(int i=n;i>=1;i--){
			if(!g[i]){
				g[i]=true;
				if(s[i]=='1'){
					while(_0>0&&(s[_0]=='1'||g[_0])) _0--;
					if(_0>0){
						sum+=i;
						g[_0]=true;
					}else{
						while(_1<=n&&(s[_1]=='0'||g[_1])&&_1<=n) _1++;
						if(_1<=n) {
							sum+=i;
							g[_1]=true;
						}
					}
				}
			}
		}
		printf("%lld\n",n*(n+1)/2-sum);
	}
	return 0;
}

```

---

## 作者：MiaoYu (赞：1)

## 题意
Monocarp 要去超市买东西。超市会在第 $i$ 天上架一份售价为 $i$ 的物品，一共 $n$ 天。超市老板决定给 Monocarp 提供优惠：

> 如果 Monocarp 一次购买**至少 $2$ 件**物品，那么这一笔交易中最贵的那一件商品将免费送给他。比如 Monocarp 一次购买 $[1, 2, 5]$，那么将只需要付 $1+2=3$ 元。

现在给定一个长为 $n$ 的字符串 $s$，$s_i = 1$ 表示：“Monocarp 会在第 $s_i$ 天前往超市”，$s_i = 0$ 表示这天不会去。请求出 Monocarp **不重复地**买到所有 $n$ 个物品的最小花费。

## CodeForces 问题 tag
*1500，二分搜索，暴力，构造，数据结构，贪心。
## 题解
这题只要知道**双端队列**就特别好做。

先讲简单的，我们每次如果要选择打折的物品，必定会选择**当天上架的那一件**，因为它是所有可以购买的商品里**最贵的一个**。另外我们还需要找一个物品“凑单”，表示我们需要购买的物品，那这个物品肯定**越便宜越好**。

来看一个例子：$1001$。

- 由于在第 $2$ 和第 $3$ 天我们不会光顾商店，所以这两个商品**必定无法享受折扣**，
  - 之前的物品（比如第 $1$ 天）打折时他们还没有上架；
  - 之后的物品（比如第 $4$ 天）打折时他们不是最贵的那一个。

所以他们会被第 $4$ 天一起打包带走。再看一个例子：$10011$。

- 可以将第 $2$ 天和第 $3$ 天分别凑给第 $4$ 和第 $5$ 天，这样就能免费多得一些物品。

由此，**我们用尽可能少的 $0$ 去带走比它更贵的物品**。开一个双端队列`deque<int>`，从后向前遍历字符串 $s$。

- 遇到 $1$ 就插入到队列里；
- 遇到 $0$ 就弹出一个队列头（免费带走一个最贵的），然后把 $0$ 买了，队列空的也没关系，反正 $0$ 是一定要买的。

到最后 $s$ 遍历完，队列里应该会剩下 一些 $1$（没有最好），那我们继续贪心。选择队尾和队首进行搭配（最贵配最便宜）。

## 代码 （一定要开 long long 啊）
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n;
string s;
deque<int> q;

int main () {
    cin >> t; while (t--) {
        cin >> n >> s;
        int len = s.length();
        long long ans = 0;

        //搭配 1 和 0
        for (int i = len - 1; i >= 0; i--) {
            int x; x = s[i] - '0';
            if (x == 1) q.push_back(i + 1);
            else {
                if (!q.empty()) q.pop_front();
                ans += i + 1;
            }
        }

        //清空队列
        while (!q.empty()) {
            ans += q.back();
            q.pop_back();
            if (q.empty()) break;
            q.pop_front();
        }
        cout << ans << '\n';
    }
}
```

---

## 作者：the_Short_Path (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2026C)
## 思路
对于第 $i$ 天来说：

- $s_i=0$，那么恭喜它一定要花钱，下一位。
- $s_i=1$，我们就找一个 $j(j<i,s_j=0)$，这样就能让 $i$ 不花钱了。如果找不到，就找没被买且最小的 $k(k<i,s_k=1)$，反正 $k$ 必须花钱，不如让 $i$ 能免费。

可以用两个 `set` 分别存 $s_i=0$ 和 $s_i=1$ 的天。
## CODE
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> s;
        set <int> s1, s2;
        long long ans = 0;
        s1.insert(0);
        for (int i = 1; i <= n; i++) {
            if (s[i - 1] == '0') s1.insert(i), ans += i; // 一定要花钱，跳过
            else s2.insert(i);
        }
        while (s2.size()) {
            auto it = s1.upper_bound(*s2.rbegin()) - 1;
            if (!(*it)) { // 找一个 j（具体见上）
                ans += *s2.begin(), s2.erase(s2.begin());
                if (s2.size()) s2.erase(*s2.rbegin()); // 注意要加 *
            } else s1.erase(it), s2.erase(*s2.rbegin()); // 否则就找一个 k（具体见上）
        }
        cout << ans << endl;
    }
    return 0;
}
```
### 小贴士
`std::set::erase()` 可以删除一个元素，也可以删除一个迭代器，**但不能删除反迭代器 `rbegin()` 和 `rend()`**，~~至于为啥我也不知道~~。

所以，在 `rbegin()` 前应加上 `*` 取值，不然就会获得这样的[报错内容](https://www.luogu.com.cn/paste/2y1gzvfd)（来自 CF）。

---

