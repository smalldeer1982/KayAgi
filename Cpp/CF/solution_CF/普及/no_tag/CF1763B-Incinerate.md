# Incinerate

## 题目描述

# Incinerate


为了消灭人类，怪物协会向地球表面派出了 $n$ 只怪兽。第 $i$ 只怪物有一个生命值 $h_i$ 和一个攻击力 $p_i$ .

凭借他最后的一击，真螺旋焚烧炮，Genos 可以对所有活着的怪物造成 $k$ 点伤害。换句话说，Genos 可以通过一次攻击降低所有怪物 $k$ 点生命值（如果 $k>0$）。

然而，在 Genos 发动的每一次攻击之后，怪物们都会反击。在他们的共同努力下，它们通过活着的最弱的怪物的力量降低 Genos 的攻击伤害。换句话说，在每次攻击后，将$k$的值减去当前所有活着的怪物中的最小$p_i$。

最弱的怪物是力量最小的怪物。

如果怪物的生命值严格大于0，则它是活着的。

Genos 会成功杀死所有怪物吗？

## 说明/提示

在第一个样例中，在 Genos 第一次攻击后，$h$和$k$将更新为：

- $ h: [11,0,6,2,3,0] $
- $ k: 7-1 = 6 $

第二次攻击后：

- $ h: [5,0,0,0,0,0] $
- $ k: 6-2 = 4 $

第三次攻击后：

- $ h: [1,0,0,0,0,0] $
- $ k: 4-2 = 2 $

第四次攻击后：

- $ h: [0,0,0,0,0,0] $

由于 Genos 可以杀死所有怪物，所以输出YES。

## 样例 #1

### 输入

```
3
6 7
18 5 13 9 10 1
2 7 2 1 2 6
3 4
5 5 5
4 4 4
3 2
2 1 3
1 1 1```

### 输出

```
YES
NO
YES```

# 题解

## 作者：zajasi (赞：3)

## 题意
你现在在打怪兽。每次，所有怪兽的生命值会减去 $k$，而每次 $k$ 会减去还活着（生命值大于 $0$）的怪兽中攻击力最小的。问能不能打败所有怪兽。
## 基本知识：set
如果你想要看懂本蒟蒻写的这篇题解，必须先对 set 有基础的了解。下面是一些基本操作。
```cpp
set<int> s;//定义一个 set。
s.insert(1);//往 set 里面添加一个数 1。
s.erase(s.begin());//删除 set 中第一个数。
s.clear();//清空 set。
s.empty();//判断 set 是否为空，若为空，返回 1；否则返回 0.
```
敲黑板，重点来了！万一你想删除 $1$ 这个数，但是不知道 $1$ 在 set 中是第几个该怎么办呢？这时候，就需要用到 find 函数啦！具体操作见下。
```cpp
s.erase(s.find(1));//在 set 里找到 1 的位置并删除。注意：find 返回的是一个指针。
```
在 set 里面套 pair 也差不多。

有了这些知识的铺垫，你就能看懂本蒟蒻的代码啦！
## 解题思路
维护两个 set，第一个以生命值为第一关键字，第二个以攻击力为第一关键字。然后每一次先删除已经死了的怪兽，然后在第二个 set 中找到最小的攻击力，将 $k$ 减去这个攻击力。周而复始，直至 $k$ 已经 $\le 0$ 或者其中的一个 set 已经删空了，结束循环。最后判断 set 是否为空，为空就可以，否则不行。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n,k;
int h[200020],p[200020];
set<pair<int,int> > s,s2;//由于我们要建立攻击力和生命值两个量，所以得用 set<pair<int,int> >。
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		s.clear();
		s2.clear();
		for(int i=1;i<=n;i++){
			cin>>h[i];
		}
		for(int i=1;i<=n;i++){
			cin>>p[i];
			s.insert(make_pair(h[i],p[i]));
			s2.insert(make_pair(p[i],h[i])); 
        		//将 set 中加入当前怪兽的信息。
		}
		int x=0;
		while(!s.empty()&&k>0){
			x+=k;//累加目前对怪兽造成的总伤害。
			while(!s.empty()&&(*s.begin()).first<=x){
				int l=(*s.begin()).first;
				int r=(*s.begin()).second;
				s.erase(s.begin());
				s2.erase(s2.find(make_pair(r,l)));//由于在 s2 中攻击力是第一关键字，所以这里 l 和 r 的顺序要颠倒。
			}
			k-=(*s2.begin()).first;//减去还活着的怪兽中攻击力最小的那一个。
		}
		if(s.empty())cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：FireFy (赞：2)

# CF1763B—焚烧 题解


## 题目简述：

Genos 打怪兽，每个怪兽有它的血量 $h_i$ 和它的攻击力 $p_i$。

Genos 开始有 $k$ 的攻击力，每攻击一次，每个怪物的血量都减去 $k$。同时，每次攻击后 Genos 的攻击力 $k$ 会减去所有活着的怪物中最小的 $p_i$。
 
 问杰诺斯能不能杀死全部的怪物。


## 先分析样例：
第一个样例：

```
6 7
18 5 13 9 10 1
2 7 2 1 2 6
```

在 Genos 第一次攻击后，怪物的血量为：

-  $ h: [11,0,6,2,3,0] $
-  $k:7-1=6$

第二次攻击后，怪物的血量为：

-  $ h: [5,0,0,0,0,0] $
-  $k:6-2=4$

第三次攻击后，怪物的血量为：

-  $ h: [1,0,0,0,0,0] $
-  $k:4-2=1$

第四次攻击后，怪物的血量为：

- $ h: [5,0,0,0,0,0] $

怪物全部死亡，Genos 可以杀死所有怪物，所以输出 $YES$

## 思路：

这是一道**暴力模拟**题。

先按照 $P$ 的大小**从小到大**排序。

在挨个处理每个怪兽，累加每回合的攻击伤害。

每次的攻击伤害 $-p_i$。

每次处理完一个怪兽后，总伤害不变，与下一个怪兽的 $h_i$ 对比，如果总伤害小于怪兽的 $h_i$ ，那么总伤害 $+k$。

### **手玩一把样例：**

```
6 7
18 5 13 9 10 1
2 7 2 1 2 6

```

以 $p$ **从小到大**排序。

```
9 10 13 18 1 5
1 2 2 2 6 7
```

第一个怪物：

Genos 的伤害：$7$ 。

第一轮 总伤害为 $7$。

$7  \lt  9$  	所以第一个怪兽仍然存活。

Genos 的伤害：$7-1=6$ 。



第二轮 总伤害为 $7+6=13$。

$13  \gt  9$  	所以第一个怪兽死，轮到第二个怪兽。

$13  \gt  10$  	所以第二个怪兽死，轮到第三个怪兽。

$13-13=0$  	所以第三个怪兽死，轮到第四个怪兽。

$13 \lt 18$  	所以第四个怪兽仍然存活。

Genos 的伤害：$6-2=4$。



第三轮 总伤害为 $13+4=17$。

$17 \lt 18$  	所以第四个怪兽仍然存活。

Genos 的伤害：$4-2=2$。



第四轮 总伤害为 $17+2=19$。

$19 \gt 18$  	所以第四个怪兽死，判断第五个怪兽。

$19 \gt 1$  	所以第五个怪兽死，判断第六个怪兽。

$19 \gt 5$  	所以第六个怪兽死，怪兽全部死亡。

所以输出

```cpp
YES
```





## 源代码

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int N=1e5+7;
struct monster
{
	ll h,p;
}a[N];
bool cmp(monster p1,monster p2)
{
	return p1.p<p2.p;
}
int main()
{
	ll t,n,k,i,j;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(i=1;i<=n;i++) cin>>a[i].h;
		for(i=1;i<=n;i++) cin>>a[i].p;
		ll damage=k; //总攻击量
		bool die=true; //能否打败怪兽
		sort(a+1,a+n+1,cmp); //按照p从小到大排序
		for(i=1;i<=n;i++)//挨个枚举每个怪物
		{
			while(damage<a[i].h)//当总攻击量小于这个怪物的血量时 
			{ 					
				k-=a[i].p;		//Genos攻击力-这个怪物的攻击力 
				if(k<=0)       //没有攻击力了就不行了
				{
					die=false; 
					break;
				}
				damage+=k; //累加总攻击量
			}
		}
		if(die) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;;
	}
	return 0;
}
```
管理大大辛苦啦~



---

## 作者：baoziwu2 (赞：1)

听同学讲的（$h_i, p_i \leq 10^{18}$）的版本, 想出的一个比较麻烦的做法。

我们发现 $k$ 的减小实际上只与当前 $p_i$ 最小的怪物（我们设这只怪兽的属性分别为 $p_m, h_m$）有关，也就是说，如果存在一只怪兽，它的 $p_i > p_m, h_i < h_m $，那么这只怪兽不会对 $k$ 产生任何影响（因为在它还没有来得及发挥作用前就已经嗝屁了）。

也就是说，其实只需要关心当前 $p_i$ 最小的怪物的血量即可，所以我们先对 $p_i$ 进行升序排序，维护一个伤害和 $res$ 和一个指针 $p$ 指向一开始为最小 $p_i$ 的怪兽。

当我们的 $p$ 指向一个怪兽时，会出现两种情况：
1. 当前伤害和 $res \geq h_i$，这只怪兽不会产生任何影响，直接 `p++`。
2. 当前伤害和 $res < h_i$，这只怪兽在被打倒之前会一直产生影响，因此计算需要出攻击的轮数（代码中给出了二分实现，实际暴力实现好像也没啥问题），将伤害累加到 $res$ 中，如在计算时发现 $k < 0$ 就输出 `NO` 即可。

一直进行到 $p > n$, 输出 `YES`。

在实现中还要注意一下细节，比如进行完 $x$ 轮之后 $k$ 应当减去 $(x - 1)p_i + p_{next}$ 而不是 $xp_i$。

```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define int long long

using namespace std;
using pii = pair<int, int>;

int const N = 2e5 + 5;

int n, k, res;

#define p first
#define h second

inline int read() {
	int res = 0, f = 1; char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) {
		res = res * 10 + c - '0';
		c = getchar();
	}
	return res * f;
}

pii a[N];

inline bool check(int x, int p, int h) {
    return res + (k + k - x * p) * (x + 1) / 2 >= h;
}

int binarySerach(int l, int r, int p, int h) {
    while(l + 1 < r) {
        int mid = l + r >> 1;
        (check(mid, p, h) ? r : l) = mid;
    }
    return check(l, p, h) ? l : r;
}

signed main() {
    int T = read();
    while(T --) {
        n = read(), k = read();
        for(int i = 1; i <= n; ++ i) a[i].h = read();
        for(int i = 1; i <= n; ++ i) a[i].p = read();
        
        sort(a + 1, a + 1 + n);
        int p = 1; res = 0;
        while(p <= n and k > 0) {
            if(res < a[p].h) {
                if(p != 1) k -= a[p].p;
                if(k <= 0) {puts("NO"); goto loop;}
                int x = binarySerach(0, k / a[p].p, a[p].p, a[p].h);
                if(!check(x, a[p].p, a[p].h)) {puts("NO"); goto loop;}
                res += (k + k - x * a[p].p) * (x + 1) / 2;
                k -= x * a[p].p;
            }
            p ++;
        }
        
        puts("YES");
        loop : continue;
    }
    
    return 0;
}
```

---

## 作者：Micnation_AFO (赞：1)

比较垃圾的无脑做法。

首先将 $h$ 和 $p$ 按照 $h_i$ 的大小升序排序。然后用线段树维护 $p_i$ 的区间最大值。

然后当 $k > 0$ 时，一直重复以下操作：
- 将 $k$ 累加起来，记做 $sum$。
- 在 $h$ 数组里二分查找最后一个小于等于 $sum$ 的值，这个值的下标记做 $x$，若 $x$ 等于 $n$，则说明可以完成。否则令 $k$ 减去 $p$ 数组内 $[x + 1, n]$ 的最小值。

这里值得注意的是，二分的时候，左边界首先要赋值为 $0$，否则如果 $h$ 数组全部大于 $sum$，就会出现明显的问题。

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100010;
#define int long long

struct SegmentTree {
    int l, r;
    int dat;
} t[N << 2];

int T;
pair<int, int> a[N];

void build(int p, int l, int r) {
    t[p].l = l, t[p].r = r;
    if (l == r) { t[p].dat = a[l].second; return; }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid), build((p << 1) | 1, mid + 1, r);
    t[p].dat = min(t[p << 1].dat, t[(p << 1) | 1].dat);
}

int ask(int p, int l, int r) {
    if (l <= t[p].l && r >= t[p].r) return t[p].dat;
    int mid = (t[p].l + t[p].r) >> 1, val = 1e9;
    if (l <= mid) val = min(val, ask(p << 1, l, r));
    if (r > mid) val = min(val, ask((p << 1) | 1, l, r));
    return val;
}

signed main() {
    cin >> T;
    while (T--) {
        int n, k; scanf("%lld%lld", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%lld", &a[i].first);
        for (int i = 1; i <= n; i++) scanf("%lld", &a[i].second);
        sort(a + 1, a + 1 + n);
        build(1, 1, n);
        int sum = 0;
        bool flag = false;
        while (k > 0) {
            sum += k;
            int l = 0, r = n;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (a[mid].first <= sum) l = mid;
                else r = mid - 1;
            }
            if (l == n) {
                flag = true;
                break;
            }
            int val = ask(1, r + 1, n);
            k -= val;
        }
        flag ? puts("YES") : puts("NO");
    }
    return 0;
}
```

---

## 作者：loser_seele (赞：1)

其实就是一个模拟题。

观察到我们要支持的操作实际上只有两个：删除 $ \leq k $ 的所有元素，寻找最小元素，且保证 $ k $ 单调递增。

这意味着删除的元素不会被恢复，不难想到 STL 里的 set 可以很好的维护。初始的时候先把所有元素丢入优先队列，按照血量排序，维护一个当前伤害值，每次弹出 set 内 $ \leq $ 当前伤害值的所有数，如果队列为空则成功，然后更新伤害值为 set 头部元素的攻击力，如果伤害为 $ 0 $ 则直接退出。否则更新当前伤害值，如此迭代下去。

这么做看上去像暴力，因为可能一次删除很多数，但每个元素最多被删除一次，所以总的时间复杂度仍为 $ \mathcal{O}(T \times n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int h[maxn],p[maxn];
int main() 
{
	int T;
	cin>>T;
	while(T--) 
    {
		int n,k;
		cin>>n>>k;
		set<pair<int,int> >cur;
		for (int i=1;i<=n;i++)
		cin>>h[i];
		for (int i=1;i<=n;i++)
		cin>>p[i];
		int tot=k;
		for (int i=1;i<=n;i++)
		cur.insert({p[i],h[i]});
		while(1145141919810) 
        {
			while(cur.size()&&tot>=(*cur.begin()).second) 
			    cur.erase(cur.begin());
			if(!cur.size()) 
            {
				cout<<"YES\n";
				break;
			}
			if(k<=0) 
			    break;
			k-=(*cur.begin()).first;
			tot+=k;
		}
		if(cur.size())
		    cout<<"NO\n";
	}
}
```


---

## 作者：ylch (赞：0)

# [CF1763B](https://www.luogu.com.cn/problem/CF1763B) Incinerate 题解

## PART1. 题目大意

勇敢的杰诺斯在打怪兽，每个怪兽有它的血量 $h_i$ 和它的力量值 $p_i$，杰诺斯开始有 $k$ 的攻击力，每攻击一次，每个怪物的血量都减去 $k$。同时，每次攻击后 $k$ 还会减去所有或者的怪物中最小的 $p_i$。问杰诺斯可以杀死全部的怪物吗？

## PART2. 解题思路

考虑到这道题的 $n$ 和 $k$ 都小于等于 $10^5$，可以以 $O(n)$ 的复杂度去遍历。

先按照 $p$ 从小到大排序，方便计算杰诺斯的攻击力 $k$，然后依次计算打败每一个怪兽需要多少代价（$k$ 需要减多少），同时累加总攻击力。判断一个怪物死亡的标准就是它的血量 $h_i$ 小于等于当前的总攻击力。

又因为每个怪物承受的都是相同的攻击，所以说并不用在意遍历的血量顺序。 

对于杰诺斯的攻击力 $k$ 的处理，我们可以每次攻击时都使其减去当前的 $p_i$，如果 $k$ 小于等于 $0$，而怪物还没死，说明杰诺斯无力打败怪物，输出 `NO`。否则，只要 $k$ 可以坚持跑完整个循环，说明可以，输出 `YES`。

$h_i$ 和 $p_i$ 都是 $10^9$ 的级别，要开 `long long`！

## PART3. AC 代码

```cpp
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int maxn = 1e5 + 7;

struct Monster{
	int h , p;
}a[maxn];

bool cmp(Monster &p1 , Monster &p2){
	return p1.p < p2.p;
}

int main()
{
	int t , n , k;
	scanf("%d" , &t);
	while(t --){
		scanf("%d %d" , &n , &k);
		for(int i = 1; i <= n; i ++){
			scanf("%d" , &a[i].h);
		}
		for(int i = 1; i <= n; i ++){
			scanf("%d" , &a[i].p);
		}
		sort(a + 1 , a + n + 1 , cmp); //按照p从小到大排序
		int attack = k; //总攻击量
		bool flag = true; //能否打败怪兽
		for(int i = 1; i <= n; i ++){
			while(attack < a[i].h){ //这个怪物还没被打败
				//更新k和attack
				k -= a[i].p;
				if(k <= 0){
					flag = false; //没有攻击力了就不行了
					break;
				}
				attack += k; //累加总攻击量
			}
		}
		if(flag == true){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
}
```

Tips:
> 这道题的数据范围较小，可以使用模拟去解。要是 $n$ 和 $k$ 顶到 $10^6$，$h_i$ 和 $p_i$ 顶到 $10^{18}$，这种解法就显得力不从心了，要使用更优秀的解法。这教育我们要因题施法。

## End

管理员大大辛苦啦~

谢谢大家！

---

## 作者：hbhz_zcy (赞：0)

这道题英文题面不是很好读，VP 的时候直接挂了。  

题目大意是 Genos 去打怪，$N$ 个怪各有属性 $h_i,p_i$ 表示血量和衰减值。初始攻击为 $K$，每打完一次（所有怪都能打到），攻击力减少活着的怪中的最小衰减值。问最后能否打完。  

不难想到存一个变量 $sum$ 累计攻击（因为对于所有怪来说攻击力一样），然后按衰减值 sort 一遍，拿一个指针从小到大去扫，保证了正确性，时间复杂度看上去也是对的了。  
如果一个怪的血量小于 $sum$ 就死亡直接跳过，否则就需要去打，一步步累加 $sum$。因为 $K$ 的范围是 $10^5$ 所以不需要推式子加速暴力打就可以。  
终止条件是把所有怪打完了或者攻击力非正数时**还有怪活着**。  

注意到打怪的中途有个性质，怪打不死就要扣攻击力，打死了还要找下一个活着的扣攻击力。考虑对于每个怪先扣攻击力再开始打，改一下初始 $K$ 即可。  

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
const int maxn=1e5+10;
int N,K;LL sum=0;
struct node{int h,p;}a[maxn];
bool cmp(const node &x,const node &y){return x.p<y.p;}
int qd(){
	int rt=0;char c=getchar();
	while(c<'0'||c>'9')  c=getchar();
	while('0'<=c&&c<='9')  rt=(rt<<3)+(rt<<1)+c-48,c=getchar();
	return rt;
}
int main(){
//	freopen("in.txt","r",stdin);
	int T=qd();
	while(T--){
		N=qd(),K=qd();sum=0;int ans=1;
		for(int i=1;i<=N;i++)  a[i].h=qd();
		for(int i=1;i<=N;i++)  a[i].p=qd();
		sort(a+1,a+N+1,cmp);K+=a[1].p;
		for(int i=1;i<=N;i++){
			while(sum<a[i].h&&K>0)  K-=a[i].p,sum+=K;
			if(sum<a[i].h){ans=0;break;}
		}
		printf("%s\n",ans?"YES":"NO");
	}
	return 0;
}
```

---

