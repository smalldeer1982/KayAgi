# Andrey and Escape from Capygrad

## 题目描述

An incident occurred in Capygrad, the capital of Tyagoland, where all the capybaras in the city went crazy and started throwing mandarins. Andrey was forced to escape from the city as far as possible, using portals.

Tyagoland is represented by a number line, and the city of Capygrad is located at point $ 0 $ . There are $ n $ portals all over Tyagoland, each of which is characterised by four integers $ l_i $ , $ r_i $ , $ a_i $ and $ b_i $ ( $ 1 \le l_i \le a_i \le b_i \le r_i \le 10^9 $ ). Note that the segment $ [a_i, b_i] $ is contained in the segment $ [l_i, r_i] $ .

If Andrey is on the segment $ [l_i, r_i] $ , then the portal can teleport him to any point on the segment $ [a_i, b_i] $ . Andrey has a pass that allows him to use the portals an unlimited number of times.

Andrey thinks that the point $ x $ is on the segment $ [l, r] $ if the inequality $ l \le x \le r $ is satisfied.

Andrey has $ q $ options for where to start his escape, each option is characterized by a single integer $ x_i $ — the starting position of the escape. He wants to escape from Capygrad as far as possible (to the point with the maximum possible coordinate). Help Andrey determine how far he could escape from Capygrad, starting at each of the $ q $ positions.

## 说明/提示

In the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1859D/e16f53a0bb292ac32fb706ca20fa668cca5f7c21.png)Optimal actions when starting from each position:

1. Use portal $ 1 $ and teleport to point $ b_1 = 14 $ .
2. Use portal $ 2 $ first and teleport to point $ 6 $ , which is on the segment $ [l_1, r_1] = [6, 17] $ , then use portal $ 1 $ and teleport to point $ b_1 = 14 $ .
3. Stay at point $ x_3=23 $ without using any portals.
4. Stay at point $ x_4=15 $ without using any portals.
5. Point $ x_5=28 $ is not on any segment, so Andrey won't be able to teleport anywhere.
6. Point $ x_6=18 $ is only on the segment $ [l_3, r_3] = [16, 24] $ , use portal $ 3 $ and teleport to point $ b_3 = 22 $ .

In the fifth test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1859D/039563dbba6cbb0aa164e573669410ec3fd16328.png)Optimal actions when starting from each position:

1. Use portal $ 1 $ first and teleport to point $ 15 $ on the segment $ [a_1, b_1] = [14, 20] $ , then use portal $ 2 $ and teleport to point $ 21 $ , which is on the segment $ [l_4, r_4] = [21, 33] $ and on the segment $ [a_2, b_2] = [13, 24] $ , then teleport to point $ b_4 = 32 $ .
2. Use portal $ 6 $ first and teleport to point $ 20 $ on the segment $ [a_6, b_6] = [20, 21] $ , then use portal $ 2 $ and teleport to point $ 22 $ , which is simultaneously on the segment $ [l_4, r_4] = [21, 33] $ and on the segment $ [a_2, b_2] = [13, 24] $ , then teleport to point $ b_4 = 32 $ .
3. Perform the same actions as from the first position.
4. Stay at point $ x_4=5 $ without using any portals.
5. Point $ 8 $ is not on any segment, so Andrey won't be able to teleport anywhere.
6. Stay at point $ x_6=33 $ without using any portals.
7. Use portal $ 5 $ and teleport to point $ b_5 = 4 $ .
8. Perform the same actions as from the first position.

## 样例 #1

### 输入

```
5
3
6 17 7 14
1 12 3 8
16 24 20 22
6
10 2 23 15 28 18
3
3 14 7 10
16 24 20 22
1 16 3 14
9
2 4 6 8 18 23 11 13 15
2
1 4 2 3
3 9 6 7
3
4 8 1
5
18 24 18 24
1 8 2 4
11 16 14 14
26 32 28 30
5 10 6 8
9
15 14 13 27 22 17 31 1 7
6
9 22 14 20
11 26 13 24
21 33 22 23
21 33 25 32
1 6 3 4
18 29 20 21
8
11 23 16 5 8 33 2 21```

### 输出

```
14 14 23 15 28 22 
14 14 14 14 22 23 14 14 15 
7 8 7 
15 14 14 30 24 17 31 4 8 
32 32 32 5 8 33 4 32```

# 题解

## 作者：shinzanmono (赞：11)

# CF1859D 题解

读题后发现，对于每一条线段，$(b,r]$ 只能跳回 $b$，做的是负贡献，$[l,b]$ 可以向前跳，这其实我们把所有 $[l,b]$ 合并起来，然后每次查找 $x$ 所在的线段的右端点，这就变成了一道板题了。

当然，如果 $x$ 不属于任何线段，他最多可以停在自己，所以要特判一下。

```cpp
#include<iostream>
#include<algorithm>
#include<set>
const int sz=2e5+10;
struct segment{
    int l,r;
    bool operator<(const segment &a)const{
        return l<a.l;
    }
}line[sz];
int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin>>t;
    while(t--){
        int n,q;
        std::cin>>n;
        for(int i=1;i<=n;i++){
            int l,r,a,b;
            std::cin>>l>>r>>a>>b;
            line[i]=segment{l,b};
        }
        std::sort(line+1,line+n+1);
        std::set<segment>cur;
        cur.insert(segment{0,0});
        for(int i=1;i<=n;i++){
            int l=line[i].l,r=line[i].r;
            while(i<n&&line[i+1].l>=l&&line[i+1].l<=r)i++,r=std::max(r,line[i].r);
            cur.insert(segment{l,r});
        }
        std::cin>>q;
        for(int i=1,x;i<=q;i++){
            std::cin>>x;
            auto it=--cur.upper_bound(segment{x,x});
            if(x<=it->r)std::cout<<it->r<<" ";
            else std::cout<<x<<" ";
        }
        std::cout<<"\n";
    }
    return 0;
}
```

---

## 作者：xujunlang2011 (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1859D)

## 思路

这是一道思维题。

我们通过观察样例发现在一个大区间中，在小区间左侧和小区间内进行传送，都会往前移动至少 $0$ 的距离。

所以我们可以将一对区间简化，保留大区间的左端点和小区间的右端点，只要位于这个新区间内，就可以传送到新区间的右端点（贪心地向前移动更多距离）。

接下来把简化后的区间合并。如果两个区间有相交（包括端点重合），就可以连着往前动两下，所以我们可以把这个两个区间合并成一个区间，新区间保留左区间的左端点和右区间的右端点。注意：**区间可以多次合并**。

然后就~~变成二分板子题~~可以查询了，每次查询时找到在 $x$ 左侧最右边的左端点，然后就可以跳到这个区间右端点了。注意：**需要特判 $x$ 是否不在任何区间内**。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int t, n, q, x, y, cnt;
struct node
{
    int l, r;
}a[N];
bool cmp(node a, node b)
{
    return a.l < b.l;
}
int main()
{
    std::ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin >> t;
    for (int ti = 1;ti <= t;ti++)
    {
        cin >> n;
        for (int i = 1;i <= n;i++)
        {
            cin >> a[i].l >> a[i].r >> a[i].r >> a[i].r;//保留新区间的端点
        }
        sort(a + 1, a + n + 1, cmp);
        node p;
        p.l = -1;
        for (int i = 1;i <= n;i++)
        {
            if (p.l == -1)
            {
                p = a[i];
            }
            else if (p.r >= a[i].l)
            {
                p.r = max(p.r, a[i].r);
            }
            else
            {
                a[++cnt] = p;
                p = a[i];
            }
        }
        if (p.l != -1)
        {
            a[++cnt] = p;
        }//合并区间
        cin >> q;
        for (int i = 1;i <= q;i++)
        {
            cin >> x;
            int l = 1, r = cnt;
            while (l < r)
            {
                int mid = (l + r + 1) / 2;
                if (a[mid].l > x)
                {
                    r = mid - 1;
                }
                else
                {
                    l = mid;
                    if (a[mid].l == x)
                    {
                        break;
                    }
                }
            }//二分查询
            if (a[l].l <= x)
            {
                cout << max(a[l].r, x);
            }
            else
            {
                cout << x;
            }//特判
            cout << " ";
        }
        cout << "\n";
        cnt = 0;
    }
    return 0; 
}
```

---

## 作者：Jie_Xu_Sheng (赞：4)

### 题意

有 $n$ 个传送门，每个传送门可从 $l_i$, $r_i$ 之间的任意一点传送到 $a_i$, $b_i$ 之间的任意一点。询问从一点 $x$ 经过任意次传送门可以到达的最远点。

保证 $[a_i,b_i]$ $∈$ $[l_i,r_i]$。

### 思路

这道题有一个很有趣的条件，$[a_i,b_i]$ $∈$ $[l_i,r_i]$。

这个条件保证了从一个传送门不能到达更远的点。

有一个结论：传送到 $b_i$ 一定是最优的。

------------
证明：

若传送到 $b_i$ 不最优，则设传送到 $x$ 为最优。

显然有 $x<b_i$。

若 $x$ 优于 $b_i$, 则至少存在一个传送门能从 $x$ 进入而不能从 $b_i$ 进入。

则这个传送门的 $r_i$ 必然在 $x$ 和 $b_i$ 之间。

那么从这个传送门必然不能到达比 $b_i$ 更远的点，$x$ 不为最优，矛盾。


------------


所以从每个传送门出来必然走到 $b_i$。

然后就考虑每个传送门从 $b_i$ 走出来能走到那些传送门。

只用考虑 $l_j$ 小于等于 $b_i$ 的传送门即可，因为如果有一个传送门 $l_j,r_j$ 都小于等于 $b_i$，这个传送门必然不优于在 $b_i$ 不动。

按照 $l_i$ 排序，从大往小遍历每一个传送门，区间询问 $l_j$ 小于等于 $b_i$ 的所有传送门的最远值即可。

然后再更新这个传送门的值，单点修改。

单点修改，区间查询最大值，无脑上线段树即可。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200010;
struct node{
	int l,r,b;
	bool operator<(const node&c)const{
		if(l!=c.l) return l<c.l;
		else return r<c.r;
	}
}a[N];
int n,mx[N<<2];
void pushup(int p){
	mx[p]=max(mx[p*2],mx[p*2+1]);
}
void build(int p,int l,int r){
	if(l==r){
		mx[p]=a[l].b;
		return ;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	pushup(p);
}
void modify(int p,int l,int r,int x,int y){
	if(l>x||r<x) return ;
	if(l==r&&r==x){
		mx[p]=y;
		return ;
	}
	int mid=(l+r)/2;
	modify(p*2,l,mid,x,y);
	modify(p*2+1,mid+1,r,x,y);
	pushup(p);
}
int query(int p,int l,int r,int x,int y){
	if(l>y||r<x) return 0;
	if(x<=l&&r<=y) return mx[p];
	int mid=(l+r)/2;
	return max(query(p*2,l,mid,x,y),query(p*2+1,mid+1,r,x,y));
}
void work(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>a[i].l>>a[i].r>>x>>a[i].b;
	}
	sort(a+1,a+n+1);
	build(1,1,n);
	for(int i=n;i>=1;i--){
		int l=1,r=n,ans=0;
		while(l<=r){
			int mid=(l+r)/2;
			if(a[mid].l<=a[i].b){
				ans=mid;
				l=mid+1;
			}else r=mid-1;
		}
		modify(1,1,n,i,query(1,1,n,1,ans));
	}
	int q;
	cin>>q;
	while(q--){
		int x;
		cin>>x;
		int rt=x;
		int l=1,r=n,ans=0;
		while(l<=r){
			int mid=(l+r)/2;
			if(a[mid].l<=x){
				ans=mid;
				l=mid+1;
			}else r=mid-1;
		}
		rt=max(rt,query(1,1,n,1,ans));
		cout<<rt<<" ";
	}
	cout<<endl;
	return ;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--) work(); 
	return 0;
}
```



---

## 作者：_Only_this (赞：3)

### CF1859D Andrey and Escape from Capygrad 题解

------------

题意已经很清晰了，无需再解释，没读题的请原路返回。

作为一道难遇的水 $D$，赛时竟没敲出来，被 wyq 薄纱，太菜了还是。。

------------

不难发现，本题具有单调性，将询问数组排好序，就可以离线处理了。

先将区间就黑线左端点排序，对于排好序的每一个询问，设当前所在的点为 $x$，如果 $x>$ 此区间黑线左端点，就走到此区间红线的最右端，直到发现不能往前走了就停下来。

黑线是完全包括红线的，因此这么贪心是正确的。

对于下一个待询问的点，设其初始位置为给定位置和上一个询问节点的最大值，至于为什么，如果之前询问可到达的点的位置在 $x$ 的前面，那么 $x$ 也一定可以走到那个位置（模拟几个例子就能发现）。

至于实现，个人感觉像一个双指针，具体的看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
struct qwe{
	int L1,R1,L2,R2;
}a[maxn];
struct QU{
	int st,id;
}q[maxn];
int T,n,Q;
int ans[maxn];
inline bool Cmp(QU x,QU y){
	return x.st<y.st;
}
inline bool _Cmp(qwe x,qwe y){
	return x.L1<y.L1;
}
inline void Solve(){
	sort(a+1,a+n+1,_Cmp);
	int j=1,now=q[1].st;
	for(int i=1;i<=Q;i++){
		now=max(now,q[i].st);
		while(j<=n){
//			printf("j=%d now=%d\n",j,now);
			if(now>=a[j].L1){
				now=max(now,a[j].R2),j++;
			}
			else{
				break;
			}
		}
		ans[q[i].id]=now;
	}
	for(int i=1;i<=Q;i++){
		printf("%d ",ans[i]);
	}
	printf("\n");
	return ;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d%d%d",&a[i].L1,&a[i].R1,&a[i].L2,&a[i].R2);
		}
		scanf("%d",&Q);
		for(int i=1;i<=Q;i++){
			scanf("%d",&q[i].st),q[i].id=i;
		}
		sort(q+1,q+Q+1,Cmp);
		Solve();
	}
	return 0;
}
```


---

## 作者：Wf_yjqd (赞：2)

首次场切 2D 祭。

很简单啊这题。

------------

显然满足能到的位置单调性，后面的位置能到的一定大于等于前面的位置能到的。

可以反证一下：假设前面的能到的远于后面的，则前面的一定能到一个红线右端点大于后面的位置，且后面的不能到一个为止，所以后面的必须在这个红线所在黑线左端点前，而前面的必须在黑线左端点后，矛盾，得证。

考虑离线处理询问，每个位置可以直接从上一个的答案位置继续向后移动，同时每个黑线最多更新一次答案。

复杂度 $\operatorname{O}(n\log n)$，即排序询问和线段的复杂度。

------------

实现起来也很容易，赛时就用了 15 分钟。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,q;
struct Segment{
    int l,r,a,b;
    friend bool operator<(Segment xy,Segment zb){
        if(xy.l!=zb.l)
            return xy.l<zb.l;
        return xy.b<zb.b;
    }
}s[maxn];
struct Query{
    int ad,id;
    friend bool operator<(Query xy,Query zb){
        return xy.ad<zb.ad;
    }
}qq[maxn];
inline bool cmp(Query xy,Query zb){
    return xy.id<zb.id;
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d%d%d%d",&s[i].l,&s[i].r,&s[i].a,&s[i].b);
        sort(s+1,s+n+1);
        scanf("%d",&q);
        for(int i=1;i<=q;i++){
            scanf("%d",&qq[i].ad);
            qq[i].id=i;
        }
        sort(qq+1,qq+q+1);
        qq[0].ad=-0x3f3f3f3f;
        for(int i=1,j=1;i<=q;i++){
            qq[i].ad=max(qq[i].ad,qq[i-1].ad);
            while(j<=n&&qq[i].ad>=s[j].l){
                qq[i].ad=max(qq[i].ad,s[j].b);
                j++;
            }
        }
        sort(qq+1,qq+q+1,cmp);
        for(int i=1;i<=q;i++)
            printf("%d ",qq[i].ad);
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：Ryder00 (赞：1)

题意清晰，不再阐述。
## 思路
发现这题跟今年省选 d1t1 很像啊，尝试往这方面靠。在纸上画一画就可以发现，只有大区间的左端点和小区间的右端点有用。假设询问在某个小区间的右端点和大区间的右端点之间，如果这对区间没有与其他任何区间有交，那么显然此时不移动是更优的。而若在这对区间的其他地方，在不考虑与其他区间有交的情况下，小区间的右端点显然是此时可以到达最远的地方。所以可以将所有成大小对的区间，左右端点都改成上述形式。

接着，就可以用类似省选 d1t1 的搞法来做了。将所有新区间按照左端点排序，扫一遍过去，处理出所有有交的连续区间段，插入到 set 里维护。对于每一次询问，只需要在 set 里二分查找，判断输出即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=2e5+10,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n;
struct node{
    int l,r;
}a[N];
bool cmp(node x,node y){
    if(x.l==y.l) return x.r<y.r;
    return x.l<y.l;
}
void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y>>y>>y;
        a[i].l=x,a[i].r=y;
    }
    sort(a+1,a+1+n,cmp);
    set<P> s;
    int mn=a[1].l,mx=a[1].r,pd=1;
    for(int i=2;i<=n;i++){
        if(a[i].l>=mn&&mx>=a[i].r){
            continue;
        }
        if(mx>=a[i].l&&mx<=a[i].r){
            mx=a[i].r;
            continue;
        }
        s.insert(mkp(mn,mx));
        mn=a[i].l,mx=a[i].r;
    }
    if(mn&&mx) s.insert(mkp(mn,mx));
    s.insert(mkp(inf,inf));
    int q;
    cin>>q;
    for(int i=1;i<=q;i++){
        int x;
        cin>>x;
        auto it=s.lower_bound(mkp(x,x));
        auto it2=prev(it);
        if(it==s.end()) cout<<x<<" ";
        else if(it==s.begin()) {
            if((*it).first<=x) cout<<(*it).second<<" ";
            else cout<<x<<" ";
        }
        else if((*it2).second>=x) cout<<(*it2).second<<" ";
        else if((*it).first<=x) cout<<(*it).second<<" ";
        else cout<<x<<" ";
    }
    cout<<endl;
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>T;
    while(T--){
        solve();
    }
    // cerr<<endl<<"Time: "<<1.0*clock()/CLOCKS_PER_SEC<<" s";
    return ~~(0^_^0);
}
```

---

## 作者：信息向阳花木 (赞：1)

贪心从 $l$ 跳到 $b$。具体地说，因为 $[a,b]$ 是在 $[l,r]$ 内部的，所以如果一个点 $x$ 满足 $l \le x \le r$，则我们一定跳。由于 $[a,b]$ 是在 $[l,r]$ 内部的（注意这点很重要），所以如果 $x$ 跳到了 $r$ 的右边以至于不能传送到 $b$，那也是最优的。（$x>b$）因此我们放心贪心就可以啦。

至于 TLE 的事，我们可以预处理出来一个 $l$ 能调到最远的 $b$，把它们称为一组。询问时只要二分出第一个小于等于 $x$ 的 $l$ 就行。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 200010;

int t, n, q;
struct node
{
	int l, r, a, b;
}w[N];
int maxx[N], l[N], r[N], cnt;

bool cmp(node x, node y)
{
	return x.l < y.l;
}

int erfen(int x)
{
	int l = 1, r = n;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if(w[mid].l > x) r = mid - 1;
		else l = mid + 1;
	}
	return l - 1;
}

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		cnt = 0;
		scanf("%d", &n);
		
		for (int i = 1; i <= n; i ++ )
		{
			scanf("%d%d%d%d", &w[i].l, &w[i].r, &w[i].a, &w[i].b);
		}
		sort(w + 1, w + n + 1, cmp);
		
		r[0] = -0x3f3f3f3f;
		for (int i = 1; i <= n; i ++ )
		{
			if(w[i].l <= r[cnt] && w[i].b > r[cnt]) r[cnt] = w[i].b;
			else if(w[i].l > r[cnt])
			{
				cnt ++;
				l[cnt] = w[i].l, r[cnt] = w[i].b;
			}
		}
		
		scanf("%d", &q);
		while (q -- )
		{
			int x;
			scanf("%d", &x);
			
			printf("%d ", max(x, r[upper_bound(l + 1, l + cnt + 1, x) - l - 1]));
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：WilliamFranklin (赞：1)

~~一道非常傻冒的 1800* 的题。~~

### 主要思路

这题的 $a$ 根本就用不着！

直接贪心。

我们首先考虑，数轴上的每一个点跳一步做能跳到的最远的点。

发现就是所有覆盖这个点的区间的 $b$ 的最大值。

很容易就想到用线段树直接维护即可。

求出来每一个点跳一步所能跳到的最远的点，我们就可以求每一个点所能跳到的最远的点了。

设当前点为 $i$，它跳一步做能跳到的最远的点为 $j$，那么一定有 $j$ 所能跳到的最远的点就是 $i$ 所能跳到的最远的点。

由此，我们直接从后往前枚举，依次求出每一个点所能跳到的最远的点即可。

但由于数据过大：$1 \le l_i \le a_i \le b_i \le r_i \le 10^9$，所以我们可以用离散化。

这里注意，因为 $a$ 是用不到的，所以我们不用算它，否则点数一共就 $10^6$ 个了，可能会 TLE，所以我们就只用开 $8 \times 10^5$ 即可。

废话不多说，上代码。

### AC Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const int N = 8e5 + 5, M = 2e5 + 5;

int n, q;
int l[M], r[M], a[M], b[M];
int s[M];
struct node {
	int l, r;
	int val;
	int lazy;
} tr[N * 4];
int maxn[N];
int st[N];
int cnt;

void pushup(int u) {
	tr[u].val = max(tr[u << 1].val, tr[u << 1 | 1].val);
}

void pushdown(int u) {
	tr[u << 1].val = max(tr[u << 1].val, tr[u].lazy);
	tr[u << 1 | 1].val = max(tr[u << 1 | 1].val, tr[u].lazy);
	tr[u << 1].lazy = max(tr[u << 1].lazy, tr[u].lazy);
	tr[u << 1 | 1].lazy = max(tr[u << 1 | 1].lazy, tr[u].lazy);
	tr[u].lazy = 0;
}

void build(int u, int l, int r) {
	tr[u] = {l, r, 0, 0};
	if (l == r) {
		tr[u].val = l;
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

void modify(int u, int x, int y, int z) {
	if (tr[u].l >= x && tr[u].r <= y) {
		tr[u].val = max(tr[u].val, z);
		tr[u].lazy = max(tr[u].lazy, z);
		return;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (x <= mid) {
		modify(u << 1, x, y, z);
	}
	if (y > mid) {
		modify(u << 1 | 1, x, y, z);
	}
	pushup(u);
}

void query(int u, int l, int r) {
	//cout << u << ' ' << l << ' ' << r << endl;
	if (l == r) {
		maxn[l] = tr[u].val;
		return;
	}
	pushdown(u);
	int mid = l + r >> 1;
	query(u << 1, l, mid);
	query(u << 1 | 1, mid + 1, r);
	pushup(u);
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		map<int, int> mp;
		map<int, int> mp1;
		scanf("%d", &n);
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d%d%d%d", &l[i], &r[i], &a[i], &b[i]);
			st[++cnt] = l[i];
			st[++cnt] = r[i];
			st[++cnt] = b[i];
		}
		scanf("%d", &q);
		for (int i = 1; i <= q; i++) {
			scanf("%d", &s[i]);
			st[++cnt] = s[i];
		}
		sort(st + 1, st + cnt + 1); 
		
		int m = 0;
		for (int i = 1, j = 1; j <= cnt; j++) {
			if (st[j] != st[j - 1]) {
				mp[st[j]] = i;
				mp1[i] = st[j];
				i++;
				m++;
			}
		}
		
		build(1, 1, m);
		
		for (int i = 1; i <= n; i++) {
			//cout << mp[l[i]] << ' ' << mp[r[i]] << ' ' << mp[b[i]] << '.' << endl;
			modify(1, mp[l[i]], mp[r[i]], mp[b[i]]);
		}
		
		query(1, 1, m);
		
//		for (int i = 1; i <= st.size(); i++) {
//			cout << mp1[i] << ' ' << mp1[maxn[i]] << endl;
//		}
//		cout << endl;
		
		//exit(0);
		
		for (int i = m; i >= 1; i--) {
			maxn[i] = max(maxn[i], maxn[maxn[i]]);
		}
		
		for (int i = 1; i <= q; i++) {
			printf("%d ", mp1[maxn[mp[s[i]]]]);
		}
		printf("\n");
	}
	
	return 0;
} 
```

### 谢谢观看

---

## 作者：Reunite (赞：1)

## 一

首先，将所有的值离散化，然后我们倒序考虑每一个离散化后的点 $i$ 能向右到达的最大值。显然这是一个类似 DP 的过程。

考虑所有 $[a_i,b_i]$ 的线段，因为他们被包含于 $[l_i,r_i]$，所以直接合并。记 $mx_i$ 为 $i$ 向右能到达的 $\max$，则初始时，$mx_i=b_i'$，$b_i'$ 为合并后覆盖点 $i$ 的最右端点（若没有被覆盖则就是 $i$）。有一个显然的贪心转移，若 $i$ 能到 $i+1$，则 $mx_i\leftarrow mx_{i+1}$。下面我们就要考虑如何快速做到：

- 合并所有 $[a_i,b_i]$ 的线段，并初始化 $mx_i$。

- 快速判断 $i$ 与 $i+1$ 是否可达。

对于第一个，可以直接用并查集解决，不清楚的可以去看看[白雪皑皑](https://www.luogu.com.cn/problem/P2391)这题。

对于第二个，因为我们已经初始化过了，被一起覆盖过的话我们就不用管。而且我们也不一定恰找 $i+1$，事实上，任意一个 $>i$ 的点都可以转移。那么判断条件可以是找一个 $j$，使得 $l_j\le i \wedge r_j\ge i\wedge b_j>i$。考虑类似扫描线的东西，把所有 $b_j>i$ 的线段以 $l_i$ 降序扔到一个堆里面，则只需要根据堆顶转移即可。

## 二
---
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int t,n,qq;
struct seg{int l,r,a,b;};
seg a[200005];
int q[200005];
int fa[1000005];
int mx[1000005];
int bb[1000005];
struct node{int pos,x;};
bool operator < (node p,node q){return p.pos>q.pos;}
priority_queue <node> que;

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}

inline bool cmp(seg p,seg q){return p.a>q.a;}

int main(){
	in(t);
	while(t--){
		in(n);
		int cnt=0;
		for(int i=1;i<=n;i++){
			in(a[i].l),in(a[i].r),in(a[i].a),in(a[i].b);
			bb[++cnt]=a[i].l;
			bb[++cnt]=a[i].r;
			bb[++cnt]=a[i].a;
			bb[++cnt]=a[i].b;
		}
		in(qq);
		for(int i=1;i<=qq;i++){
			in(q[i]);
			bb[++cnt]=q[i];
		}
		sort(bb+1,bb+1+cnt);
		cnt=unique(bb+1,bb+1+cnt)-bb-1;
		for(int i=1;i<=cnt;i++) mx[i]=fa[i]=i;
		for(int i=1;i<=n;i++){
			a[i].a=lower_bound(bb+1,bb+1+cnt,a[i].a)-bb;
			a[i].b=lower_bound(bb+1,bb+1+cnt,a[i].b)-bb;
			a[i].l=lower_bound(bb+1,bb+1+cnt,a[i].l)-bb;
			a[i].r=lower_bound(bb+1,bb+1+cnt,a[i].r)-bb;
			int ll=Find(a[i].a);
			while(ll<=a[i].b-1){
				fa[Find(ll)]=Find(ll+1);
				ll=Find(ll+1);
			}
		}
		for(int i=1;i<=cnt;i++) mx[i]=Find(i);
		while(!que.empty()) que.pop();
		sort(a+1,a+1+n,cmp);
		int lst=1;
		for(int i=cnt;i>=1;i--){
			mx[i]=max(mx[i],mx[Find(i)]);
			while(lst<=n&&(a[lst].a>i||(a[lst].a==i&&a[lst].b>i))){
				que.push((node){a[lst].l,a[lst].b});
				lst++;
			}
			if(que.size()==0) continue;
			node tmp=que.top();
			if(tmp.pos<=i) mx[i]=max(mx[i],mx[tmp.x]);
		}
		for(int i=1;i<=qq;i++) printf("%d ",bb[mx[lower_bound(bb+1,bb+1+cnt,q[i])-bb]]);
		putchar('\n');
	}
	
	return 0;
}

```

---

## 作者：仁和_童博扬 (赞：1)

# CF1859D Andrey and Escape from Capygrad

## 题意
给定 $ n $ 条线段 $ [l_i, r_i] $ ，在线段内可以跳转到 $ [a_i, b_i] $ 中的任意位置，保证跳转位置在线段内。给定 $ q $ 个位置，求每个位置可以到达的最远位置。

## 分析
由于本题要求可以到达的**最远位置**，所以对于每段 $ [l_i, r_i] $ ，其中**需要考虑的有效位置**仅有 $ [l_i, b_i] $ ，而在这些位置上时必定会选择跳到 $ b_i $ 上。根据 **“能往后跳则往后跳”** 的原则，合并有重叠的 $ [l_i, b_i] $ 为同一条线段。

对于提问，我们采取**离线**的形式进行处理。

我们**将所有问题的位置与合并后的线段信息存储在同一个结构体中**，将问题标记为 $ opt = 0 $ ，线段信息标记为 $ opt = 1 $ ，将问题的坐标和线段起始位置均存储为 $ x $ ，存储问题编号为 $ i $ ，线段可传送到的最远点为 $ r $ 。

我们对这个结构体以 $ x $ 为关键字进行升序排序，由于线段均为闭区间，为保证覆盖到起始点，我们在 $ x $ 相等时，按 $ opt $ 降序排序，即**在同一点处，先处理线段信息，后处理询问**。

排序后，进行一次遍历，使用变量 $ r $ 记录当前可以到达的最远点，遇到询问信息则将询问点的位置与 $ r $ 进行比较，大者即为该次询问的答案，将其存在 $ ans $ 数组中的询问位置（输入时已经存储了原始下标）。

处理完毕后，输出 $ ans $ 数组即可。

时间复杂度为 $ O((n + q)\log(n + q)) $ ，可以通过本题。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
struct place{
	int l, r, a, b;
}a[N], b[N]; 
int n;
struct xx{
	int x;
	int opt;//0表示询问，1表示开始
	int r;//如果opt=1，则r为当前可以传送到的最远点
	int i;//如果opt=0，则i为问题编号 
}g[N*3];
int ans[N];//记录答案 
bool cmp(place x, place y)
{
	return x.l < y.l;
}
bool cmp2(xx x, xx y)
{
	if(x.x == y.x)
		return x.opt > y.opt;
	return x.x < y.x;
}
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		scanf("%d",&n);
		for(int i = 1; i <= n; i++)
			scanf("%d%d%d%d",&a[i].l,&a[i].r,&a[i].a,&a[i].b);
		sort(a+1,a+1+n,cmp);//按a排序 
		int m = 0;
		int r = a[1].b, lst = 1;
		//r是目前可以传送到的最右侧，lst是目前段落的左端点 
		a[n+1].l = 1e9 + 1;//用来保证最后一段可以被存储 
		for(int i = 2; i <= n + 1; i++)
		{
			if(a[i].l <= r)
				r = max(r,a[i].b);
			else
			{
				g[++m].opt = 1;
				g[m].r = r;
				g[m].x = a[lst].l;
				lst = i;
				r = a[i].b;
			}
		}
		int q;
		scanf("%d",&q);
		for(int i = 1; i <= q; i++)
		{
			scanf("%d",&g[++m].x);
			g[m].opt = 0;
			g[m].i = i;
		}
		sort(g+1,g+1+m,cmp2);
		r = 0;
		for(int i = 1; i <= m; i++)
		{
			if(g[i].opt == 1)
				r = g[i].r;
			else
				ans[g[i].i] = max(g[i].x,r);
		}
		for(int i = 1; i <= q; i++)
			printf("%d%c",ans[i],i==q?'\n':' ');
	}
	return 0;
}
```


---

## 作者：yukari1735 (赞：0)

离散化，设 $r_i$ 表示 $i$ 的原值，dp 一个 $f_i$ 表示在区间 $[r_i,r_{i+1})$ 起始的答案。

容易发现，我们向后跳是一定不优的，设当前在 $p$，如果要向后跳那么一定是为了之后的向前跳到一个新的位置 $r>p$，然而我们发现这样的话 $p$ 也一定包含在 $r$ 的大区间里面，这样就无需向后跳了。

类似的证明可以发现一定是跳到 $b_i$ 上，因此从右往左扫，维护当前所有能跳到的 $b_i$，选取最大的一个用 $f_{b_i}$ 更新 $f$，可以用 `multiset` 实现，时间复杂度 $O(n\log n)$。

```cpp
# include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 225;

int n;
int f[ N ];
vector< int >P[ N ] , Q[ N ];
vector< int >Rev;
# define pb push_back
# define lb lower_bound

struct Segment{ int l , r , a , b; }L[ N ];

multiset< int >S;

void Solve(){
	Rev . clear() , Rev. pb( -1 ) , Rev . pb( 1 );
	scanf( "%d" , & n );
	for( int i = 1 ; i <= n ; i ++ ){
		int l , r , a , b;
		scanf( "%d%d%d%d" , & l , & r , & a , & b );
		L[ i ] = { l , r , a , b };
		Rev . pb( l ) , Rev . pb( b );	
	}
	S . clear() , sort( Rev . begin() , Rev . end() ) , Rev . erase( unique( Rev . begin() , Rev . end() ) , Rev . end() );
	for( int i = 0 ; i < Rev . size() ; i ++ ) P[ i ] . clear() , Q[ i ] . clear() , f[ i ] = i;
	for( int i = 1 ; i <= n ; i ++ ){
		int b = lb( Rev . begin() , Rev . end() , L[ i ] . b ) - Rev . begin();
		int l = lb( Rev . begin() , Rev . end() , L[ i ] . l ) - Rev . begin();
		P[ b ] . pb( b ) , Q[ l - 1 ] . pb( b );
	}
	for( int i = Rev . size() - 1 ; i >= 1 ; i -- ){
		for( int t : P[ i ] ) S . insert( t );
		for( int t : Q[ i ] ) S . erase( S . find( t ) );
		if( S . empty() ) continue;
		int p = * S . rbegin();
		f[ i ] = f[ p ];
	}
	int q;
	scanf( "%d" , & q );
	for( int i = 1 ; i <= q ; i ++ ){
		int x;
		scanf( "%d" , & x );
		int p = lb( Rev . begin() , Rev . end() , x ) - Rev . begin();
		if( Rev[ p ] ^ x ) p --;
		printf( "%d\n" , max( x , Rev[ f[ p ] ] ) );
	}
}

int main(){
	int T;
	scanf( "%d" , & T );
	while( T -- ) Solve();
	return 0;	
}
```


---

## 作者：nullqtr_pwp (赞：0)

注意到对于任意的线段 $[l_i,r_i],[a_i,b_i]$，跳到 $b_i$ 总是最优的。因为 $r_i$ 要往回跳，$a_i$ 也不是最优的，所以本题中其实只有 $l_i,b_i$ 有用。

问题转化成给定 $n$ 个线段 $[l_i,b_i]$，每次可以从 $x_i$ 开始跳线段的右端点，求最远到哪里。

对于这个，可以离线下来所有询问然后进行离散化，考虑用线段树维护每个位置可以**直接**跳到哪条线段的右端点上。先对所有线段按照 $b_i$ 排序，每次就是对 $[l_i,b_i]$ 区间推平为 $b_i$。这样操作完之后可以求出离散化后每个位置在哪条线段上。

这之后可以考虑用并查集维护最远跳到哪里。时间复杂度 $O(n\log n)$。
```cpp
struct seg{
	int l,r,a,b;
	bool operator<(const seg &sb)const{
		return b<sb.b;
	}
}s[maxn];
int c[maxn],l[maxn],b[maxn],t[maxn<<2],nxt[maxn],add[maxn<<2],f[maxn];
#define ls (o<<1)
#define rs (o<<1|1)
void pushup(int o){t[o]=t[ls]+t[rs];}
void pushdown(int o,int l,int r){
    if(add[o]){
    	int mid=(l+r)>>1;
    	add[ls]=add[o];
    	add[rs]=add[o];
    	t[ls]=add[o]*(mid-l+1);
    	t[rs]=add[o]*(r-mid);
    	add[o]=0;
	}
}
void update(int o,int l,int r,int ql,int qr,int v){
    if(ql<=l&&qr>=r){add[o]=v;t[o]=v*(r-l+1);return;}
    int mid=(l+r)>>1;
    pushdown(o,l,r);
    if(ql<=mid) update(ls,l,mid,ql,qr,v);
    if(qr>mid) update(rs,mid+1,r,ql,qr,v);
    pushup(o);
}
int query(int o,int l,int r,int ql,int qr){
    if(ql<=l&&qr>=r) return t[o];
    pushdown(o,l,r);
    int mid=(l+r)>>1,ans=0;
    if(ql<=mid) ans+=query(ls,l,mid,ql,qr);
    if(qr>mid) ans+=query(rs,mid+1,r,ql,qr);
    pushup(o);
    return ans;
}
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
int q[maxn],ans[maxn],qq[maxn],bk[maxn];
void solve(){
	int n=read();
	F(i,1,n) s[i]=(seg){read(),read(),read(),read()};
	int m=read();
	F(i,1,m) qq[i]=q[i]=read();
	sort(s+1,s+n+1);
	F(i,1,n){
		c[i*2-1]=s[i].l;
		c[i*2]=s[i].b;
	}
	F(i,1,m) c[2*n+i]=q[i];
	int p=2*n+m;
	sort(c+1,c+p+1);
	int len=unique(c+1,c+p+1)-c-1;
	F(i,1,n){
		l[i]=lower_bound(c+1,c+len+1,s[i].l)-c;
		bk[l[i]]=s[i].l;
		b[i]=lower_bound(c+1,c+len+1,s[i].b)-c;
		bk[b[i]]=s[i].b;
	}
	F(i,1,m) q[i]=lower_bound(c+1,c+len+1,q[i])-c;
	F(i,1,4*p) t[i]=add[i]=0;
	F(i,1,n) update(1,1,p,l[i],b[i],b[i]);
	F(i,1,p) nxt[i]=query(1,1,p,i,i);
	F(i,1,p) f[i]=i;
	F(i,1,p) f[find(i)]=find(nxt[i]);
	F(i,1,m){
		int x=q[i];
		if(!nxt[x]) printf("%d ",qq[i]);
		else printf("%d ",bk[find(x)]);
	}
	HH;
}
```


---

## 作者：ollo (赞：0)

# 题目大意

给定 $n$ 个四元组 $[l,r,a,b]$ 满足 $l \leq a \leq b \leq r$，若 $l\leq i \leq r$，则可以从 $i$ 到区间 $[a,b]$ 上任意一点。

$q$ 次询问，每次从 $x$ 出发，问向右最远可以到哪。

# 大致思路

由于 $[l, r]$ 包含 $[a,b]$，显然若 $b < x \leq r$ 则不跳一定比跳更好。

但是如果存在一个区间包含了 $[a, b]$ 且可以跳到比 $x$ 更远的地方呢？

显然这种情况是不存在的，若 $b'>x$，则显然有 $r'>x$，所以 $x$ 也可以跳进这个区间。

所以只有区间 $[l, b]$ 是有效的，又因上述证明，每个点都会跳到区间右端点。所以区间中每个点都与左端点等价。

所以现在区间被离散化成 $2n+q$ 个点，又同上证，若点坐标单调递增，则对应的答案也单调递增。

考虑倍增，首先离散化，然后对于每个左端点 $l$（包括询问），找出最大的前缀右端点 $r$，记为 $f_{l,0}$，直接倍增即可。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int T, n, m, tot;
int p[N], f[N << 1][20];
int l[N], r[N], t[N << 1], v[N << 1];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> T;
	while(T--){
		tot = 0;
		cin >> n;
		for(int i = 1; i <= n; i++){
			int r1, l2;
			cin >> l[i] >> r1 >> l2 >> r[i];
			t[++tot] = l[i]; t[++tot] = r[i];
		}
		cin >> m;
		for(int i = 1; i <= m; i++) cin >> p[i], t[++tot] = p[i];
		sort(t + 1, t + tot + 1);
		tot = unique(t + 1, t + tot + 1) - t - 1;
		for(int i = 1; i <= tot; i++) for(int j = 0; j <= 19; j++) f[i][j] = 0;
		for(int i = 1; i <= tot; i++) v[i] = 0;
		for(int i = 1; i <= n; i++){
			l[i] = lower_bound(t + 1, t + tot + 1, l[i]) - t;
			r[i] = lower_bound(t + 1, t + tot + 1, r[i]) - t;
			v[l[i]] = max(v[l[i]], r[i]);
		}
		for(int i = 1; i <= m; i++) p[i] = lower_bound(t + 1, t + tot + 1, p[i]) - t;
		for(int i = 1, mx = 0; i <= tot; i++){
			mx = max(mx, v[i]);
			if(i <= mx) f[i][0] = mx;
		}
		for(int j = 1; j <= 19; j++)
			for(int i = 1; i <= tot; i++)
				f[i][j] = f[f[i][j - 1]][j - 1];
		for(int i = 1; i <= m; i++)
			cout << max(t[f[p[i]][19]], t[p[i]]) << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：rmzls (赞：0)

### 思路
考虑到 $l,r,a,b,x$ 都很大，但是 $n$ 很小，因此我们将 $l,r,a,b,x$ 离散化。  
类似于[P9166 [省选联考 2023] 火车站 ](https://www.luogu.com.cn/blog/rmzls/p9166-xing-xuan-lian-kao-2023-huo-ju-zhan-ti-xie-wei-post#)，因为这个题目要求的是一个点能到达最右边的节点是什么，我们从右往左扫，利用右边已经更新过的信息更新左边的点。  
记录 $d_i$ 为 $i$ 节点能到达最右边的节点，那么假如 $i$ 处于一个区间 $l,r$ 内，那么 $i$ 能到达的最远节点为 $d_b$，$d_i$ 中的最小值。当然 $i$ 可能会处于很多区间内，因此我们要找到最大的一个 $b_i$ 去更新。  
我们将每个 $b$ 存入一个数组里面，从大到小排序（若 $b$ 相同则 $l$ 小的放前面）。我们从右往左走的时候，如果当前扫到的这个点超出该 $b$ 所属区间的 $l$，则跳到下一个合法的区间。  
当然，我们这里只判了当前扫到的这个节点 $i$ 有没有大于 $l$ 而没有判 $r$，因为如果该节点大于 $r$ ，那么假设 $d_b$ 大于 $d_i$,那么一定存在若干个有交集的区间，能让 $d_b$ 更新到比 $d_i$ 更大的地方，而 $i$ 必然也在这若干个区间内，所以会提前被更新到，因此只用判 $l$ 即可。


------------
### 代码
这里要注意以下数组的上限。理论上限即所有的 $l,r,a,b,x$ 都不同，即 $5\times2\times10^5=10^6$。（赛场上报TLE一直以为是时间问题，比完赛才注意到是数组开太小，悲）
```cpp
#include<bits/stdc++.h>
#define o printf("a\n");
using namespace std;
const int N=2e6+100;
int t,n,p,mx1,zgd,mx2,mxb,ans,cntt,lb[N],x[N],d[N],lsh[N],cnt,l1,r1,a1,b1;
struct node{
	int l,r,a,b;
}seg[N];
struct bb{
	int l,b,id;
	bool operator <(const bb &p){
		if(b==p.b){
			return l>p.l;
		}
		return b<p.b;
	}
}ydd[N];
signed main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d%d%d",&l1,&r1,&a1,&b1);
			seg[i].l=l1;seg[i].r=r1;seg[i].a=a1;seg[i].b=b1;ydd[i].b=b1;ydd[i].id=i,ydd[i].l=l1;
			lsh[++cnt]=l1;lsh[++cnt]=r1;lsh[++cnt]=a1;lsh[++cnt]=b1;
		}
		scanf("%d",&p);
		for(int i=1;i<=p;i++){
			scanf("%d",&x[i]);
			lsh[++cnt]=x[i];
		}
		sort(lsh+1,lsh+cnt+1);
		sort(ydd+1,ydd+n+1);
		lsh[0]=-1;
		for(int i=1;i<=cnt;i++){
			if(lsh[i]!=lsh[i-1]){
				lb[++cntt]=lsh[i];
			}
		}
		cnt=cntt,mxb=n;
		for(int i=1;i<=cnt;i++){
			d[i]=lb[i];
		}
		zgd=lower_bound(lb+1,lb+1+cnt,ydd[mxb].b)-lb;
		for(int i=cnt;i>=1;i--){
			while(lb[i]<ydd[mxb].l&&mxb>=1){
				mxb--;
				zgd=lower_bound(lb+1,lb+1+cnt,ydd[mxb].b)-lb;
			}
			if(lb[i]>=ydd[mxb].l){
				d[i]=max(d[i],d[zgd]);
			}
		}
		for(int i=1;i<=p;i++){
			printf("%d ",d[lower_bound(lb+1,lb+1+cnt,x[i])-lb]);
		}
		printf("\n");
		cnt=cntt=0;
	}
	return 0;
} 
```


---

