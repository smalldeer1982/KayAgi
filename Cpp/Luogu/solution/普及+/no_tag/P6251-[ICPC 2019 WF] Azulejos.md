# [ICPC 2019 WF] Azulejos

## 题目描述

陶艺家 Maria 和 João 正在波尔图开设一家小型的 azulejo 商店。Azulejos 是葡萄牙著名的美丽陶瓷瓷砖。Maria 和 João 想要创建一个吸引人的橱窗展示，但由于店内空间有限，他们必须将瓷砖样品在一个架子上排列成两行。João 的每块瓷砖前面都有 Maria 的一块瓷砖，Maria 的每块瓷砖后面都有 João 的一块瓷砖。这些手工制作的瓷砖有许多不同的尺寸，重要的是后排的每块瓷砖都比前排的瓷砖高，以便路人都能看到。为了方便顾客，每排瓷砖按价格从左到右非递减排列。相同价格的瓷砖可以在满足上述可见性条件的情况下以任何顺序排列。

你的任务是找到满足这些约束条件的瓷砖排列，或者确定不存在这样的排列。

## 说明/提示

来源：ICPC 2019 世界总决赛。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4
3 2 1 2
2 3 4 3
2 1 2 1
2 2 1 3```

### 输出

```
3 2 4 1
4 2 1 3```

## 样例 #2

### 输入

```
2
1 2
2 3
2 8
2 1```

### 输出

```
impossible```

# 题解

## 作者：CashCollectFactory (赞：2)

### 题目大意
题目要求将两排砖按照以下条件排列：
1. 前排的要严格矮于后排的。
2. 每一排的价格从左到右需要是越来越贵（可以相等）。

### 贪心解法

这题算是很简单的贪心了。首先将两排砖分别**按价格排序**，价格相同的划到同一个 set。然后都从最低价开始，拿出前排当前最低价的一块砖摆上（多块的话随意摆一块），然后到后排的当前最低价的砖里面找一块刚好能满足要求的（刚好比前排的高 $1$ 个单位，没有的话就是比这个高的最矮的），一直到摆完就可以了。要是这时候找不到这样的砖(就是最低价的都比前面的矮)，那就知道没法摆了（后排的有砖匹配不上前排，前排出现同样的情况也是一样），直接输出 ```impossible```。

由于**只需要遍历所有砖块一遍就可以解决**，所以总时间复杂度是 $O(n)$。

### 代码时间（~~有点抽象~~）
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
struct tile {
	int index;
	int price;
	int height;
};
int main() {
	cin >> n;
	vector<tile> front_row(n), back_row(n);
	//读数据，然后仅按价格排序
	auto read_tile = [&](vector<tile> &tile_row) {
		for (int i = 0; i < n; i++) {
			tile_row[i].index = i + 1;
			cin >> tile_row[i].price;
		}
		for (int i = 0; i < n; i++)
			cin >> tile_row[i].height;
		sort(tile_row.begin(), tile_row.end(), [&](const tile &a, const tile &b) { return a.price < b.price; });
	};
	read_tile(back_row);
    read_tile(front_row);
    //存储当前价格相同的tile
    //height -> iter in front/back row
    multimap<int,vector<tile>::iterator> front_tile_map, back_tile_map;
	int front_index = 0, back_index = 0;
	vector<int> front_ret(n),back_ret(n);
    int front_ret_index = 0, back_ret_index = 0;
    //插入当前价格的tile到set
    struct insert_map_arg{
        multimap<int,vector<tile>::iterator>& tile_map;
        vector<tile>& tile_vec;
        int& vec_index;
    }
        front_map_arg{front_tile_map, front_row, front_index},
        back_map_arg{back_tile_map, back_row, back_index};
	while (1) {
        auto insert_map=[&](insert_map_arg& arg){
            //每次都尝试insert front map和back map两者中空了的那个
        	if (arg.tile_map.empty()) {
                int price = arg.tile_vec[arg.vec_index].price;
                while (arg.vec_index < arg.tile_vec.size() && arg.tile_vec[arg.vec_index].price == price) {
                    arg.tile_map.insert(make_pair(arg.tile_vec[arg.vec_index].height, arg.tile_vec.begin() + arg.vec_index));
                    ++arg.vec_index;
                }
            }
        };
        insert_map(front_map_arg);
        insert_map(back_map_arg);
		//用贪心法，从当前价格区间找出最合适的砖, 具体就是刚好和当前tile差一的
        if(front_tile_map.size() < back_tile_map.size()){
            for(auto t:front_tile_map){
                int frontH=t.second->height;
                auto iter=back_tile_map.lower_bound(frontH + 1);
                if(iter==back_tile_map.end()){
                    cout<<"impossible"<<endl;
                    return 0;
                }
                front_ret[front_ret_index++]=t.second->index;
                back_ret[back_ret_index++]=iter->second->index;
                back_tile_map.erase(iter);
            }
            front_tile_map.clear();
        } else{
            for(auto t:back_tile_map){
                int backH=t.second->height;
                auto iter=front_tile_map.upper_bound(backH-1);
                if(iter==front_tile_map.begin()){
                    cout<<"impossible"<<endl;
                    return 0;
                }
                iter=prev(iter);
                front_ret[front_ret_index++]=iter->second->index ;
                back_ret[back_ret_index++]=t.second->index;
                front_tile_map.erase(iter);
            }
            back_tile_map.clear();
        }
        if(front_ret_index>=n && back_ret_index>=n)
            break;
	}
    //输出答案
    for(auto i:back_ret)
        cout<<i<<" ";
    cout<<endl;
    for(auto i:front_ret)
        cout<<i<<" ";
    cout<<endl;
    return 0;
}
```

本代码需要使用 C++11 以上版本才可以，只因里面用了“auto”这个新东西~



---

## 作者：pufanyi (赞：2)

对于一段 $p$ 相同的区间，我们可以将里面的瓷砖随意调换。

考虑如何贪心。

我们发现有两种不同的情况，我们的目的不同：

![](https://pufanyi.pages.dev/WF2019A/case1.png)

此时我们是想让匹配完 $a$ 中 $p=2$ 情况后，$b$ 中剩余的 $p=3$ 的瓷砖的 $h$ 尽量小。

我们可以将 $a$ 中 $p=2$ 的每块瓷砖都找到 $b$ 中一个恰好比它小的瓷砖进行匹配。

![](https://pufanyi.pages.dev/WF2019A/case2.png)

此时我们是想让匹配完 $b$ 中 $p=2$ 的情况后 $a$ 中剩余的 $p=3$ 的瓷砖的 $h$ 尽量大。

我们可以将 $b$ 中 $p=2$ 的每块瓷砖都找到 $a$ 中一个恰好比它大的瓷砖进行匹配。

我们维护目前第 $i$ 个位置可以填哪些数，如果 $a$ 中可填的数比 $b$ 中少，那么是情况一，否则就是情况二。

```cpp
#include <cstdio>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

const int inf = 0x3f3f3f3f;
const int maxn = 500005;

struct sxd
{
	int p, h, id;
	friend bool operator < (sxd a, sxd b) { return a.p < b.p; }
};

struct pii
{
	int x, y;
	friend bool operator < (pii a, pii b) { return a.x < b.x; }
	pii (int x = 0, int y = 0) { this->x = x, this->y = y; }
};

multiset<pii> sta, stb;

int n;

sxd aa[maxn];
sxd bb[maxn];

int ansa[maxn];
int ansb[maxn];

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &aa[i].p);
		aa[i].id = i;
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d", &aa[i].h);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &bb[i].p);
		bb[i].id = i;
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d", &bb[i].h);
	sort(aa + 1, aa + n + 1);
	sort(bb + 1, bb + n + 1);
	for(int i = 1, nowa = 0, nowb = 0; i <= n; ++i)
	{
		if(sta.empty())
		{
			nowa++;
			sta.insert(pii(aa[nowa].h, aa[nowa].id));
			while(nowa + 1 <= n && aa[nowa].p == aa[nowa + 1].p)
			{
				nowa++;
				sta.insert(pii(aa[nowa].h, aa[nowa].id));
			}
		}
		if(stb.empty())
		{
			nowb++;
			stb.insert(pii(bb[nowb].h, bb[nowb].id));
			while(nowb + 1 <= n && bb[nowb].p == bb[nowb + 1].p)
			{
				nowb++;
				stb.insert(pii(bb[nowb].h, bb[nowb].id));
			}
		}
		if(sta.size() < stb.size())
		{
			set<pii>::iterator it = stb.lower_bound(pii((sta.rbegin())->x, 0));
			if(it == stb.begin())
			{
				puts("impossible");
				return 0;
			}
			--it;
			ansa[i] = (sta.rbegin())->y;
			ansb[i] = it->y;
			sta.erase(--sta.end());
			stb.erase(it);
		}
		else
		{
			set<pii>::iterator it = sta.upper_bound(pii((stb.begin())->x, 0));
			if(it == sta.end())
			{
				puts("impossible");
				return 0;
			}
			ansa[i] = it->y;
			ansb[i] = (stb.begin())->y;
			sta.erase(it);
			stb.erase(stb.begin());
		}
	}
	for(int i = 1; i <= n; ++i)
		printf("%d ", ansa[i]);
	puts("");
	for(int i = 1; i <= n; ++i)
		printf("%d ", ansb[i]);
	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

细节题

 - 叫第一个瓷砖序列（后面） $A$，第二个瓷砖序列（前面）$B$。
 - 叫第 $i$ 个瓷砖 $(A|B)_i$。
 - 叫一个瓷砖的价值 $(A|B)_i^P$。
 - 叫一个瓷砖的大小 $(A|B)_i^S$。

注意到对于答案两个瓷砖序列，这些瓷砖的价钱序列唯一，因为价钱必须上升。因此我们先俺价钱排序，考虑怎么在价钱相同的一段瓷砖重新排列使得合法。

假设现在已经排好序了：

$$A_0^P\le A_1^P\le A_2^P\le\dots\le A_{n-1}^P$$
$$B_0^P\le B_1^P\le B_2^P\le\dots\le B_{n-1}^P$$

最后把答案数组进行重新标号。

如果我们求到了答案数组的 $[0,i-1]$ 位置了，怎么排列后面？

假设有 $p_{S=(A|B)}=max(j:S_i^P=S_{i+1}^P=\dots=S_j^P)+1$

最长的一直价值一样的块（因此也是可以随意重拍的快）为 $\min(p_A,p_B)-1$

我们想把问题从
>做好 $[0,i-1]$ 位置了，怎么做后面

变成  
>做好 $[0,\min(p_A,p_B)-1]$ 位置了，怎么做后面

有两个情况：

1. $p_A<p_B$，这个时候 $B$ 会有剩余，想让剩余尽量小来让后面匹配更多可能性
2. $p_A\ge p_B$，这个时候 $A$ 可能会有剩余，想让剩余尽量大来让后面匹配更多可能性

对于第一个情况，枚举 $i\le idx<p_A$，对 $A_{idx}$ 找一个 $i\le j<p_B$ 使得 $A_{idx}^S>B_j^S$ 并且 $B_j^S$ 最大（来让更小的剩下）

对情况 2 做类似的枚举，唯一区别是在 $A$ 里面搜最小 $B_j^S$ 使得 $B_j^S>A_{idx}^S$。

这些显然可以用 $set$ 等支持删除，二分的无序数据结构。

预处理 $p_S$ 就可以过了。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define fi first
#define se second
#define pb push_back
 
#define ll long long
#define pii pair<int, int>
//#define int ll
const int MOD = 1000000007;

map<int, set<pii>> A, B;
int Aend[500005], Bend[500005];
int Tmp1[500005], Tmp2[500005];
int pr1[500005], pr2[500005];
int r1[500005], r2[500005];

void halt() {
    cout << "impossible" << endl;
    exit(0);
}

int n;

void solve(int idx) {
    if(idx == n) return;
    int pa = pr1[idx], pb = pr2[idx];
    if(Aend[idx] > Bend[idx]) {
        for(auto& dx:B[pb]) {
            int ht = dx.fi;
            // find one taller than this in A[pa] but is shortest
            auto k = A[pa].lower_bound({ht+1, -1});
            if(k == A[pa].end()) halt();
            r1[idx] = k->se; r2[idx] = dx.se;
            idx++;
            A[pa].erase(k);
        }
        B.erase(pb);
        solve(idx);
    } else {
        for(auto& dx:A[pa]) {
            int ht = dx.fi;
            // find one shorter than this in A[pa] but is tallest
            auto k = B[pb].lower_bound({ht, -1});
            if(k == B[pb].begin()) halt();
            k = prev(k);
            r1[idx] = dx.se; r2[idx] = k->se;
            idx++;
            B[pb].erase(k);
        }
        A.erase(pa);
        solve(idx);
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    rep(i, n) cin >> Tmp1[i];
    rep(i, n) cin >> Tmp2[i];
    rep(i, n) A[Tmp1[i]].insert({Tmp2[i], i});
    rep(i, n) cin >> Tmp1[i];
    rep(i, n) cin >> Tmp2[i];
    rep(i, n) B[Tmp1[i]].insert({Tmp2[i], i});
    int idx;
    idx = 0;
    for(auto& p:A) {
        int bbBB = idx + p.se.size();
        for(auto& _p:p.se) {
            Aend[idx] = bbBB;
            pr1[idx] = p.fi;
            idx++;
        }
    }
    assert(idx == n);
    idx = 0;
    for(auto& p:B) {
        int bbBB = idx + p.se.size();
        for(auto& _p:p.se) {
            Bend[idx] = bbBB;
            pr2[idx] = p.fi;
            idx++;
        }
    }
    assert(idx == n);
    solve(0);
    rep(i, n) cout << r1[i]+1 << ' ';
    cout << endl; rep(i, n) cout << r2[i]+1 << ' ';
}
```

---

## 作者：yanxu_cn (赞：0)

简单的贪心题，时限估计在标程 $20$ 倍以上（不卡常、各种 STL 的代码最长的点就跑了 $1.01$ 秒，拜谢出题人）。

思路就是给价值开个桶，然后每个桶里面用平衡树维护。从小到大查询这两个桶，每次分别取 $a,b$ 中 $p$ 最小的桶，比较哪个桶中剩余元素比较少，取那个比较少的桶里的最小的元素（其实这里随便选一个都是可以的），删除另外那个桶里面的最小的比他大的元素或者最大的比他小的元素，并把这个元素删除掉，不满足就直接 impossible 就可以了。

贴代码，不知道有多少只 $log$ 哈哈（但是常数意外没有很大）。另外，多检验，多检验，多检验！

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
class node
{
	public:
	int ht,idx;
	const bool operator<(const node&ndx)const
	{
		return ht<ndx.ht||ht==ndx.ht&&idx<ndx.idx;
	}
};

const string imp="impossible"s;
constexpr int maxn=5e5+7;

map<int,set<node>>mpxa,mpxb;

int arr[maxn];

int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int n;
	cin>>n;
	vector<int>ansa,ansb;
	for(int i=1;i<=n;i++)
		cin>>arr[i];
	for(int i=1;i<=n;i++)
	{
		int htp;
		cin>>htp;
		mpxb[arr[i]].insert(node{htp,i});
	}
	for(int i=1;i<=n;i++)
		cin>>arr[i];
	for(int i=1;i<=n;i++)
	{
		int htp;
		cin>>htp;
		mpxa[arr[i]].insert(node{htp,i});
	}
	for(int i=1;i<=n;i++)
	{
		// check
		while(!mpxa.empty()&&(mpxa.begin())->second.empty())mpxa.erase(mpxa.begin());
		while(!mpxb.empty()&&(mpxb.begin())->second.empty())mpxb.erase(mpxb.begin());
		if(mpxa.empty()||mpxb.empty())break;
		// a is earlier clear
		if(mpxa.begin()->second.size()<=mpxb.begin()->second.size())
		{
			auto ra=mpxa.begin()->second.begin();
			auto res=mpxb.begin()->second.lower_bound(node{ra->ht+1,0});
			if(res==mpxb.begin()->second.end())
			{cout<<imp;return 0;}
			ansa.push_back(ra->idx);
			ansb.push_back(res->idx);
			mpxb.begin()->second.erase(res);
			mpxa.begin()->second.erase(ra);
		}
		// b is earlier clear
		else
		{
			auto rb=mpxb.begin()->second.begin();
			auto res=mpxa.begin()->second.lower_bound(node{rb->ht,0});
			if(res==mpxa.begin()->second.begin())
			{cout<<imp;return 0;}
			else res--;
			ansa.push_back(res->idx);
			ansb.push_back(rb->idx);
			mpxa.begin()->second.erase(res);
			mpxb.begin()->second.erase(rb);
		}
	}
	for(auto i:ansb)
	cout<<i<<' ';
	cout<<'\n';
	for(auto i:ansa)
	cout<<i<<' ';
	return 0;
}

```

---

