# New Game

## 题目描述

Monocarp 想玩一个新游戏。这个游戏使用一副有 $n$ 张牌的牌堆，第 $i$ 张牌上写着一个整数 $a_i$。

游戏开始时，在第一回合，Monocarp 可以从牌堆中拿走任意一张牌。在之后的每一回合，Monocarp 只能拿走一张牌，这张牌上写的数字要么与上一回合拿走的牌上的数字相同，要么比上一回合拿走的牌上的数字大 $1$。

换句话说，如果上一回合 Monocarp 拿走的牌上的数字是 $x$，那么这一回合他可以拿走数字为 $x$ 或 $x+1$ 的任意一张牌，无论它在牌堆中的位置如何。

每当 Monocarp 拿走一张牌，这张牌就会从牌堆中移除。

根据游戏规则，Monocarp 拿走的牌上所写的不同数字的数量不能超过 $k$。

如果在某一回合后，Monocarp 无法在不违反上述规则的情况下继续拿牌，游戏就结束。

你的任务是：给定初始牌堆，求 Monocarp 在游戏中最多能拿走多少张牌。第一回合可以拿任意一张牌。

## 说明/提示

在第一个样例中，Monocarp 需要先拿任意一张数字为 $3$ 的牌。接下来的两回合，他需要拿剩下的两张数字为 $3$ 的牌。再接下来的三回合，他需要拿三张数字为 $4$ 的牌。之后，Monocarp 将无法再拿牌，此时他一共拿了 $6$ 张牌。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
10 2
5 2 4 3 4 3 4 5 3 2
5 1
10 11 10 11 10
9 3
4 5 4 4 6 5 4 4 6
3 2
1 3 1```

### 输出

```
6
3
9
2```

# 题解

## 作者：Cosine_Func (赞：5)

来一发似乎比现有题解都简洁的双指针做法。

先对数组排序，然后从左向右移动左端点。取右端点为原右端点和左端点的较大值，然后向右移动右端点直到不满足题目中的条件，并将两端点之间的距离计入答案。时间复杂度 $O(T\times N\times\log N)$。

核心代码如下：
```cpp
int n,k,l,r,ans,a[N];
inline void Solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	l=1,r=0,ans=0;
	while(l<=n){
		r=max(l,r);
		while(r<n and a[r+1]-a[r]<=1 and a[r+1]-a[l]<k)r++;
		ans=max(ans,r-l+1),l++;
	}
	cout<<ans<<endl;
}
```

---

## 作者：Crimson_Moon (赞：3)

## 题目

$Monocarp$ 想玩一个新游戏。游戏使用一副 $n$ 纸牌，其中 $i$ 纸牌上正好写着一个整数 $a_i$ 。

游戏开始时，在第一个回合，$Monocarp$ 可以从牌组中任意抽取一张牌。在随后的每个回合中，$Monocarp$ 都可以拿走一张牌，这张牌上的数字要么与上一回合拿走的牌上的数字相同，要么比上一回合拿走的牌上的数字大 $1$。

换句话说，如果上一回合 $Monocarp$ 拿了一张数字为 $x$ 的牌，那么本回合他就可以拿一张数字为 $x$ 或 $x + 1$ 的牌。Monocarp 可以取走任何符合该条件的牌，无论其在牌组中的位置如何。

当 $Monocarp$ 在当前回合取走一张牌后，这张牌就会从卡组中移除。

根据游戏规则，$Monocarp$ 拿的牌上所写的不同数字的数量不能超过 $k$ 。

如果在一个回合后，$Monocarp$ 无法在不违反上述规则的情况下拿牌，游戏就会结束。

你的任务是确定 $Monocarp$ 在游戏中最多可以从牌组中抽取多少张牌。（他在第一回合可以从牌组中抽取任何一张牌。）

## 思路

先对给出的序列 $a$ 进行排序。显然，任何一组合法解（或者说选出的任何一组牌）在排好序的序列 $a$ 中一定是连续的区间。考虑实现一个滑动窗口，使得滑动窗口里的牌构成合法解。最终的答案就是滑动窗口的最大长度。

用一个桶维护滑动窗口内每个值的出现次数，一个计数器维护滑动窗口内不同的 $a_i$ 的个数，两个指针控制滑动窗口的左边界和右边界。

每次右边界向右移动时，再根据窗口内新元素的值进行操作（详见代码）。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int T;
int n, k, a[N], cnt;
int main() {
    cin >> T;
    while (T --) {
        cin >> n >> k;
        for (int i = 1; i <= n; i ++) cin >> a[i];
        sort (a + 1, a + n + 1);
        int l = 1, r = 2;
        cnt = 1;
        map<int, int> b;
        b[a[1]] ++;
        int len = 1;
        while (r <= n) {
            len = max(len, r - l);
            if (a[r] - a[r - 1] > 1) {
                cnt = 1;
                while (l < r) b[a[l]] --, l ++;
                b[a[r]] ++;
                r ++;
                continue;
            }
            b[a[r]] ++;
            if (b[a[r]] == 1) {
                while (cnt == k) {
                    b[a[l]] --;
                    if (b[a[l]] == 0) cnt --;
                    l ++;
                }
                cnt ++;
            }
            r ++;
        }
        len = max(len, r - l);
        cout << len << endl;
    }
    return 0;
}
```
注意：如果定义 `unordered_map` 可能会 $TLE$。

---

## 作者：ssfx2019s005 (赞：2)

算法：类似单调队列

通过题面描述可得知，选出来的数字一定是连续且单调不降的，容易想到单调队列。

根据题意，选出来的数字前后之差一定是小于 $k$ 的，再根据连续且单调不降的性质，我们先将数组排序并去重。假设当前将要入队的点编号为 $i$，那么如果队头项与当前节点相减大于等于 $k$，就将队头弹出。如果队尾节点与第 $i$ 项相差不为一，就将队尾弹出。

代码：


```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <deque>
using namespace std;
int T,n;
const int N=2e5+15;
int k;
int a[N];
int main(){
	cin>>T;
	while(T--){
		int ans=0;
		map<int,int> mp;
		deque<int> que;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			++mp[a[i]];
		}
		sort(a+1,a+n+1);
		int len=unique(a+1,a+n+1)-a-1;
		int res=0;
		for(int i=1;i<=len;i++){
			while(que.size() && i-que.front()+1>k){
				res-=mp[a[que.front()]];
				que.pop_front();
			}
			while(que.size() && a[que.back()]!=a[i]-1){
				res-=mp[a[que.back()]];
				que.pop_back();
			}
			res+=mp[a[i]];
			que.push_back(i);
			ans=max(ans,res);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：GCSG01 (赞：2)

### 思路
不难发现，在对卡牌进行排序后，一段合法的区间 $l,r$ 满足 $a[r]-a[l]+1 \le k$，这段区间的答案即为 $r-l+1$，用双指针枚举 $l$，并每次都拓展 $r$ 至满足条件的最远处，并统计答案。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
signed main()
{
    #ifndef ONLINE_JUDGE
        freopen("1.in","r",stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        sort(a+1,a+n+1);
        int l,r,ans;
        l=r=ans=0;
        while(l<=n)
        {
            l++;
            r=max(l,r);
            while(r<n&&a[r+1]-a[r]<=1&&a[r+1]-a[l]<k)r++;
            ans=max(ans,r-l+1);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：cly312 (赞：1)

题意：找到一组数字，这些数字最多包含 $k$ 个不同的数字，并且这些数字在排序后是连续的（即相邻数字之差不超过 $1$）。

思路：先统计每个数字的出现次数，然后对所有数字排序，使用滑动窗口寻找最多包含 $k$ 个连续数字的窗口，并计算该窗口内数字的总出现次数。

代码：

```cpp
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		vector<int> a(n);
		map<int,int> mp;
		for(auto &x:a) cin>>x,mp[x]++;
		vector<pair<int,int>> nums;
		for(auto &[num,cnt]:mp){
			nums.push_back({num,cnt});
		}
		sort(nums.begin(),nums.end());
		int m=nums.size();
		int l=0;
		ll tmp=0;
		ll maxn=0;
		for(int r=0;r<m;r++){
			tmp+=nums[r].second;
			while(l<=r&&(r-l+1)>k){
				tmp-=nums[l].second;
				l++;
			}
			while(l<=r&&nums[r].first-nums[l].first>r-l){
				tmp-=nums[l].second;
				l++;
			}
			maxn=max(maxn,tmp);
		}
		cout<<maxn<<"\n";
	}
}
```

---

