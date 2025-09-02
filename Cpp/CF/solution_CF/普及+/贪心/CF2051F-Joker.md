# Joker

## 题目描述

考虑一副有 $n$ 张牌的情况。牌中的位置从上到下编号为 $1$ 到 $n$。小丑位于位置 $m$ 。

$q$ 操作按顺序应用于牌组。在第 $i$ 次操作期间，您需要在位置 $a_i$ 处取出卡片并将其移动到牌堆的开头或末尾。例如，如果牌组是 [_2,1,3,5,4_] ，并且 $a_i$   =2 ，那么在操作之后牌组将是 [_1,2,3,5,4_]（从第二个位置开始的牌移动到开头）或 [_2,3,5,4,1_]（卡片从第二个位置移到最后）。

您的任务是计算每次操作后小丑可以所处的不同位置的数量。

## 样例 #1

### 输入

```
5
6 5 3
1 2 3
2 1 4
2 1 1 2
5 3 1
3
3 2 4
2 1 1 1
18 15 4
13 15 1 16```

### 输出

```
2 3 5 
2 2 2 2 
2 
2 3 3 3 
2 4 6 8```

# 题解

## 作者：Leo235 (赞：4)

考虑使用一个数组维护每组得到的位置。 \
我们发现，所有情况将构成一颗类二叉树结构，及每组情况下单一的一个情况将在下一组给出两个贡献。 \
因此，在处理每个输入的时候，将上一组的答案提出来遍历，并更新如下答案：\
定义 $(l,r)$ 表示上一组其中一种情况的两贡献。

1. 若 $q_i < l$，$l$ 将贡献其左侧的位置。
2. 若 $q_i > r$，$r$ 将贡献其右侧的位置。
3. 若 $l < q_i < r$，将保持不变，同时更新左右端点。

剩下的就只用算答案就行了，详见代码：

```cpp
// CF #Round995 F
// MinGW64 C++-17
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int N = 2e5 + 5;
#define int long long
typedef pair<int, int> PII;

int t;

int n, m, q;

signed main ()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    cin >> t;
    while (t --)
    {

        cin >> n >> m >> q;

        vector<PII> a;
        a.push_back({m, m});

        for (int i = 1; i <= q; i ++)
        {

            int x;
            cin >> x;

            vector<PII> tot;

            for (auto [l, r] : a)
            {

                if (x < l)
                {
                    tot.push_back({l - 1, r});
                }
                else if (x > r)
                {
                    tot.push_back({l, r + 1});
                }
                else
                {
                    if (l != r)
                    {
                        tot.push_back({l , r});
                    }
                    tot.push_back({1, 1}), tot.push_back({n, n});
                }

            }

            a.clear(); // 记录新的一组的贡献
            sort (tot.begin(), tot.end());

            for (auto [l, r] : tot)
            {

                if (a.empty() || (a.back().second < l)) // 若最大的小于上一组， 全更新
                {
                    a.push_back({l, r});
                }
                else // 处理重复的情况
                {
                    a.back().second = max (a.back().second, r);
                }

            }

            int ans = 0;
            for (auto [l, r] : a)
            {
                ans += (r - l + 1);
            }

            cout << ans << " ";

        }

        cout << "\n";

    }

    return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：3)

# F. Joker

本场最后过的这题/xk

**实现。**

维护集合 $pos$ 表示目前 Joker 可能处在的位置的集合。

每次操作第 $x$ 个位置就是考虑哪些位置可能前移，哪些位置可能后移，哪些位置可能被新加入。

设有 $y\in pos$，如果 $y\lt x$ 那么 $y+1$ 可能成为新的答案（把 $x$ 位置的卡牌放到第一个）；如果 $y\gt x$ 那么 $y-1$ 可能成为新的答案（把 $x$ 位置的卡牌放到最后一个）；如果有 $y=x$ 那么先从集合中删去 $y$，把 $1$ 和 $n$ 添加进来。

直接模拟这个过程 TLE on 8。详见 <https://codeforces.com/contest/2051/submission/297931501>。

分析这个做法的问题，就是一个位置可能本来就在集合里，但是被插进去太多次了。

我们维护两个**可能成为答案**的集合。分别表示通过 $y+1$ 成为答案或者通过 $y-1$ 成为答案。每次操作在集合中二分出这些位置，把它们全插到 $pos$ 里。每次往 $pos$ 里新插入的时候，判断是否有新的元素可能成为答案。删除的时候判断它是否有机会再次成为答案。

<https://codeforces.com/contest/2051/submission/297945489>

<https://codeforces.com/contest/2051/submission/297946569>

<https://codeforces.com/contest/2051/submission/297947497>

上面是三发不同的初始和加了卡常的版本。

---

## 作者：Doyoulike (赞：1)

#### 不难发现
对于这道题目中输入的每一个$q_i$都有三种情况。


1. $q_i$ 在 Joker 左边。
2. $q_i$ 在 Joker 右边。
3. $q_i$ 就是 Joker。 


而对于每一种情况，都有两种可能新出现的位置。  
不妨设现在 Joker 在第 $i$ 处。

对于第一种情况：Joker 要么不动，要么移到 $i-1$ 的位置。

对于第二种情况：Joker 要么不动，要么移到 $i+1$ 的位置。

对于第三种情况：Joker 要么移到  $1$ 的位置，要么移到 $n$ 的位置。

便可以用 set 模拟写出如下代码： 
```cpp
#include<iostream>
#include<set>
using namespace std; 
long long n,m,q,x,t;
set<long long>a,p;
int main(){
	cin>>t;
	while (t--){
		cin>>n>>m>>q;
		a.clear();
		a.insert(m);
		for (int i=1;i<=q;i++){
			cin>>x;
			p.clear();
			for (set<long long>::iterator it=a.begin();it!=a.end();it++){
				long long j=*it;
				if (x>j){
					p.insert(j);
					p.insert(j+1);
				}else if (x<j){
					p.insert(j);
					p.insert(j-1);
				}else{
					p.insert(1);
					p.insert(n);
				}
			}
			swap(a,p);
			cout<<a.size()<<" ";
		}
		cout<<"\n";	
	}
	return 0;
}
```
But，这么做会在第八个测试点 TLE，因为 $n$ 最大为 $10^9$。

再次观察，不难发现：所有可能的位置在去除第三种情况时是连续的。而加上第三种情况后，不难发现：所有的可能性都是围绕着三个点扩散开来的，也就是 $1$，$m$ 和 $n$ 三个点，所以我们只需要维护三个连续的线段，求他们长度总和，并去重就可以了。  
但是我们忽略了两种情况：  
1. 输入的 $q_i$ 里没有一个数可能产生第三种情况。
2. $q$ 个数里的第一个数就是 $m$。

所以，还要加入一个标记数组来标记是否使用该线段。

答案就显而易见了：
```cpp
#include<iostream>
using namespace std; 
struct node{
	long long l,r;
};
long long n,m,q,x,t;
int main(){
	cin>>t;
	while (t--){
		cin>>n>>m>>q;
		node a[5]={};//储存线段
		bool vis[5]={},vid[5]={};//两个标记数组
		a[1].l=a[1].r=1;
		a[2].l=a[2].r=m;
		a[3].l=a[3].r=n;
		vis[2]=1;
		for (int i=1;i<=q;i++){
			cin>>x;
			for (int i=1;i<=3;i++){
				if (!vis[i])continue;
				//cout<<i;
				if (x<a[i].l){//第一种情况
					a[i].l--;
				}else if(x>a[i].r){//第二种情况
					a[i].r++;
				}else{//第三种情况
					if (a[i].l==a[i].r)vis[i]=0;//如果区间内只有一个点,这根线段就不再使用
					vid[1]=1;
					vid[3]=1;//首和尾可以使用
				}
			}
			if (vid[1])vis[1]=1;
			if (vid[3])vis[3]=1;

			if (vis[1]&&vis[2]&&vis[3]){//计算,输出,去重
				if (a[1].r>=a[2].l){
					if (a[2].r>=a[3].l){
						cout<<a[3].r-a[1].l+1;
					}else{
						cout<<a[2].r-a[1].l+1 + a[3].r-a[3].l+1;
					}
				}else{
					if (a[2].r>=a[3].l){
						cout<<a[3].r-a[2].l+1 + a[1].r-a[1].l+1;
					}else{
						cout<<a[1].r-a[1].l+1 + a[2].r-a[2].l+1 + a[3].r-a[3].l+1;
					}
				}
			}else if(vis[1]&&vis[2]){
				if (a[1].r>=a[2].l){
					cout<<a[2].r-a[1].l+1;
				}else{
					cout<<a[2].r-a[2].l+1 + a[1].r-a[1].l+1;
				}
			}else if(vis[1]&&vis[3]){
				if (a[1].r>=a[3].l){
					cout<<a[3].r-a[1].l+1;
				}else{
					cout<<a[3].r-a[3].l+1 + a[1].r-a[1].l+1;
				}
			}else if(vis[2]&&vis[3]){
				if (a[2].r>=a[3].l){
					cout<<a[3].r-a[2].l+1;
				}else{
					cout<<a[2].r-a[2].l+1 + a[3].r-a[3].l+1;
				}
			}else if(vis[1]){
				cout<<a[1].r-a[1].l+1;
			}else if (vis[2]){
				cout<<a[2].r-a[2].l+1;
			}else{
				cout<<a[3].r-a[3].l+1;
			}
			cout<<" ";
			
		}
		cout<<"\n";//换行不要忘记
	}
	return 0;
}
```

---

## 作者：postpone (赞：1)

简单分类讨论一下可以发现：当操作 Joker 前面的牌，Joker 的位置可能会往前移动一格；操作后面的牌，可能往后移动一格；正好操作到 Joker 的位置，则会出现在最前或者最后。也就是说，Joker 可能出现的位置能组成三个区间：最前面的一段、最后面的一段，以及由初始位置 $m$ 扩展得到。

按如上所述的方式，维护三个区间即可。需要注意的是，当区间只有一张牌，且正好操作这个牌，那么该区间转移变成最前面或最后面。每次操作的答案就是三个区间的并。

思路比较好理解，但实现上略复杂，可能会漏一些情况。我参考了题解的写法：把区间放在数组里；每次先更新，再遍历统计答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    m--;
    
    // [l, r)
    vector<pair<int, int>> segs(3);
    segs[1] = {m, m + 1};
    segs[0] = {0, 0};
    segs[2] = {n, n};
    
    while (q--) {
        int x;
        cin >> x;
        x--;

        bool inside{};
        
        for (auto &&[l, r] : segs) {
            if (r - l < 1) {
                continue;
            }
            if (x < l) {
                l--;
                l = max(l, 0);
            } else if (x >= r) {
                r++;
                r = min(r, n);
            } else {
                inside = true;
                if (r - l == 1) {
                    r = l;
                }
            }
        }
        if (inside) {
            segs[0] = {0, max(segs[0].second, 1)};
            segs[2] = {min(segs[2].first, n - 1), n};
        }
        
        int ans{}, pos{};
        for (auto [l, r] : segs) {
            if (r - l < 1) {
                continue;
            }
            ans += r - max(l, pos);
            pos = r;
        }
        cout << ans << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    for (cin >> T; T--;) {
        solve();
    }

    return 0;
}
```

---

