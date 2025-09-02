# Final Boss

## 题目描述

你正在面对你最喜欢的游戏中的最终  BOSS。敌人的生命值是 $h$。你的角色有 $ n $ 攻击。第 i 次攻击会对 BOSS 造成 $ a_i $ 伤害，但冷却时间为 $ c_i $ 个回合，也就是说，如果你当前的回合为 $ x $，那么下一次可以使用该攻击的时间为 $ x + c_i $ 个回合。 每个回合，你都可以一次性使用当前未冷却的所有攻击。如果所有攻击都处于冷却状态，则本回合什么也不做，跳到下一回合。

最初，所有攻击都不在冷却时间内。要花多少回合才能打败 BOSS？当 BOSS 的生命值为 $ 0 $ 或更低时，它就被打败了。

## 样例 #1

### 输入

```
8
3 2
2 1
2 1
5 2
2 1
2 1
50 3
5 6 7
5 6 7
50 3
2 2 2
3 3 3
90000 2
200000 200000
1 1
100000 1
1
200000
6 7
3 2 3 2 3 1 2
6 5 9 5 10 7 7
21 6
1 1 1 1 1 1
5 5 8 10 7 6```

### 输出

```
1
3
15
25
1
19999800001
1
21```

# 题解

## 作者：BrotherCall (赞：6)

小时候看这集 fst 了。

## 题意

有个 boss 有 $h$ 的血量，你作为玩家有 $n$ 个技能，每个技能伤害为 $a_i$，冷却时间为 $c_i$。

每一回合你可以使用所有已冷却的技能，然后该技能会进入冷却并在 $c_i$ 回合后才可使用。

求最少多少回合击败 boss。

## 思路

对 boss 造成的伤害是随着回合数单调不降的。

所以直接二分答案就行了。

若进行了 $x$ 回合，则技能 $i$ 的使用次数为 $\displaystyle\frac{x - 1}{c_i} + 1$，造成的伤害为 $\displaystyle a_i\cdot(\frac{x - 1}{c_i} + 1)$。

**注意：计算总伤害会爆 long long。所以在计算过程中若足够击败 boss 就应直接退出循环。**~~笔者就是因为这个 fst 了。~~

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long
using namespace std;

const int N = 1e6 + 100;
char ch[N];
int t , n , m , z , k , a[N] , b[N];

signed main() {
	cin >> t;
	while(t --) {
		cin >> n >> m;
		for(int i = 1;i <= m;i ++) 
			cin >> a[i];
		for(int i = 1;i <= m;i ++) 
			cin >> b[i];
		int l = 1 , r = 1e12;
		int ans = 1;
		while(l <= r) {
			int mid = l + r >> 1;
			int sum = 0;
			for(int i = 1;i <= m;i ++) {
				int cs = (mid - 1) / b[i] + 1;
				sum += cs * a[i];
				if(sum >= n) break;
			}
			if(sum >= n) {
				ans = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：ZhaoV1 (赞：4)

## CF1985F Final Boss

### 题目分析
每个技能都有固定冷却时间，且在同一时间可以释放所有不在冷却的技能，显然我们可以选择二分法或优先队列解决问题。

方法一：

介于范围 $1≤h≤2×10^5$ 且 $1≤a≤2×10^5$，所以最多释放技能 $2×10^5$ 次，那么我们可以用优先队列来存储每一个已释放的技能，冷却完成的时间点越早越优先。

```cpp
struct node{
	int a,c,now;
	bool operator < (const node &b) const{
		return this->now > b.now;
	}//冷却完成的时间点越早越优先
};
priority_queue<node> pq;
```

每一回合我们释放当前回合所有能使用的技能，然后放入优先队列中，下一次再取出最早冷却完毕的一个或一批技能使用，直到血量 $h<0$ 就结束。

复杂度为 $\operatorname{O(n)}$。

Code（优先队列）
------------

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,h,n;
struct node{
	int a,c,now;
	bool operator < (const node &b) const{
		return this->now > b.now;
	}//冷却完成的时间点越早越优先
}b[200005];

void solve(){
	cin >> h >> n;
	int turn = 1;
	for(int i=1;i<=n;i++) cin >> b[i].a;
	for(int i=1;i<=n;i++) cin >> b[i].c;
	queue<node> que;
	priority_queue<node> pq;
	for(int i=1;i<=n;i++) que.push({b[i].a,b[i].c,1});
	while(h > 0){
		if(!pq.empty()){
			turn = pq.top().now;
			while(!pq.empty() && pq.top().now == turn){
				que.push({pq.top().a,pq.top().c,pq.top().now});
				pq.pop();
			}
		}
		while(!que.empty()){
			h -= que.front().a;
			pq.push({que.front().a,que.front().c,que.front().c+que.front().now});
			que.pop();
		}
	}
	cout << turn << '\n';
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
```

方法二：

由于每回合可以将所有可用技能释放掉，所以每个技能实际上都从第一回合后开始进入冷却，显然只要确定了回合数量，就可以用简单计算来算出每个技能使用次数和伤害总和，因此我们还可以二分求回合数。

复杂度为 $\operatorname{O(nlogn)}$。

Code（二分）
------------

```cpp
#define int long long
int t,h,n;
int a[200005];
int c[200005];

inline bool check(int mid){
	unsigned long long sum = 0;
	for(int i=1;i<=n;i++){
		//初始回合为1，所以mid-1就是用于冷却的总回合数 
		sum += ((mid-1)/c[i]+1)*a[i];//计算公式 
	}
	return sum >= h;
}

void solve(){
	cin >> h >> n;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=n;i++) cin >> c[i];
	unsigned long long left = 0,right = 4e10+1;
	while(left + 1 < right){
		unsigned long long mid = left + right >> 1;
		if(check(mid)){
			right = mid;
		}else{
			left = mid;
		}
	}
	cout << right << '\n';
}
```

---

## 作者：YZMX (赞：3)

## 题目描述

给出 $n$ 个攻击方式，每个攻击有伤害 $a$ 和冷却 $c$。每回合可以任意使用不在冷却的攻击。敌人血量为 $h$。求最少多少回合可以打败敌人。 

## 题目分析

如果使用常规优先队列等，我认为处理伤害时比较麻烦。如果使用二分答案，那么处理会比较简单。

当我们知道了回合，如何计算第 $i$ 个攻击总共造成多少伤害？

由题目可知，第一回合一定可以造成一次伤害，那么假设经过 $x$ 回合恰好使用了 $n$ 次第 $i$ 个攻击，可以得到 $x =1 + (n-1) \times c_i$。只有当 $x$ 增加一个 $c_i$ 时才会让攻击次数增加，所以下取整就能得到 $x$ 回合之后用了几次攻击。

攻击次数 $n = \lfloor \frac{ x + c_i - 1 }{ c_i } \rfloor$。

## 代码

```
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#define int unsigned long long
#define qwq ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define pii pair<int,int>
using namespace std;

int t,n,h;
struct node{
    int a,c;
}e[200005];
bool check(int x){
    int res=0;
    for(int i=1;i<=n;i++){
        res+=((x-1+e[i].c)/e[i].c)*e[i].a;//计算
        //注意：如果不开unsigned long long 这里需要加上res>=h的判断
    }
    return res>=h;
}


signed main(){
    cin>>t;
    while(t--){
        cin>>h>>n;
        for(int i=1;i<=n;i++){
            cin>>e[i].a;
        }
        for(int i=1;i<=n;i++){
            cin>>e[i].c;
        }
        int l=0,r=4e14;//其实不用开这么大
        while(l<r){//二分
            int mid=(l+r-1)/2;
            if(check(mid)){
                r=mid;
            }else{
                l=mid+1;
            }
        }
        cout<<l<<endl;

    }





    return 0;
}
```

---

