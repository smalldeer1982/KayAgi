# Monsters

## 题目描述

Monocarp is playing yet another computer game. And yet again, his character is killing some monsters. There are $ n $ monsters, numbered from $ 1 $ to $ n $ , and the $ i $ -th of them has $ a_i $ health points initially.

Monocarp's character has an ability that deals $ k $ damage to the monster with the highest current health. If there are several of them, the one with the smaller index is chosen. If a monster's health becomes less than or equal to $ 0 $ after Monocarp uses his ability, then it dies.

Monocarp uses his ability until all monsters die. Your task is to determine the order in which monsters will die.

## 说明/提示

In the first example, the health points change as follows: $ [1, 2, \underline{3}] \rightarrow [1, \underline{2}, 1] \rightarrow [\underline{1}, 0, 1] \rightarrow [-1, 0, \underline{1}] \rightarrow [-1, 0, -1] $ . The monster that is going to take damage the next time Monocarp uses his ability is underlined.

In the second example, the health points change as follows: $ [\underline{1}, 1] \rightarrow [-2, \underline{1}] \rightarrow [-2, -2] $ .

In the third example, the health points change as follows: $ [2, \underline{8}, 3, 5] \rightarrow [2, \underline{5}, 3, 5] \rightarrow [2, 2, 3, \underline{5}] \rightarrow [2, 2, \underline{3}, 2] \rightarrow [\underline{2}, 2, 0, 2] \rightarrow [-1, \underline{2}, 0, 2] \rightarrow [-1, -1, 0, \underline{2}] \rightarrow [-1, -1, 0, -1] $ .

## 样例 #1

### 输入

```
3
3 2
1 2 3
2 3
1 1
4 3
2 8 3 5```

### 输出

```
2 1 3 
1 2 
3 1 2 4```

# 题解

## 作者：船酱魔王 (赞：3)

# CF1849B Monsters 题解

## 题意回顾

$ n $ 个怪物，一刀 $ k $ 血，每次打剩余血量最多的怪物，多个选编号最小的，输出怪物被击杀的顺序。

**多测**，$ \sum n \le 3 \times 10^5 $。

## 分析

首先，怪物的血量严格大于 $ k $ 的时候被打一次也不会死，而怪物的血量小于等于 $ k $ 时候被打一次必死。

可以发现，只要有大于 $ k $ 的怪物的话一定不会打小于等于 $ k $ 的怪物，因此在所有怪物血量跌到 $ k $ 及以下之前没有怪物会死。

而在所有怪物的血量小于等于 $ k $ 之后，玩家是一击必杀的。所以我们只要知道所有怪物的血量小于等于 $ k $ 后每个怪物的血量即可求出击杀顺序（即剩余血量从大到小排序，一样就按照编号从小到大排序）。

因为血量每次减少 $ k $，因此一个怪物血量模 $ k $ 一直同余。又因为最终血量，即 $ 1 \sim k $ 中所有数模 $ k $ 余数不同，因此可以通过初始血量模 $ k $ 的余数求出最终血量，进而求出顺序。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 3e5 + 5;
int T;
int n, k;
struct node {
	int id;
	int val;
} a[N];
bool operator<(node p1, node p2) {
	if(p1.val != p2.val) {
		return p1.val > p2.val;
	}
	return p1.id < p2.id;
}
int main() {
	scanf("%d", &T);
	for(int ti = 1; ti <= T; ti++) {
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i].val);
			a[i].id = i;
			if(a[i].val % k == 0) {
				a[i].val = k;
			} else {
				a[i].val = a[i].val % k;
			}
		}
		sort(a + 1, a + n + 1);
		for(int i = 1; i <= n; i++) {
			printf("%d ", a[i].id);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：__Aaaaaaaa (赞：3)

## 前言
比赛的时候脑抽，高估了T2，写了个可并堆……

## Description
有 $n$ 个怪物，第 $i$ 个怪物血量是 $a_i$，玩家每次操作是对当前生命值最高的怪物扣除 $k$ 的血量，如果某个怪物血量非正则称它被杀死了。

## Solution
对于每个怪物被砍死的次数记录下来，玩家肯定会先砍次数较多的。

那直接用大根可并堆模拟一下，先对于次数从大到小排序，对于砍的次数不同的，先下放一个 $lazytag$，使得目前枚举到的怪物距离死亡的次数是一样的，然后不断合并，最后挨个弹出就行了。

时间复杂度 $O(nlog_2n)$

## Code:
```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=3e5+10;
struct number{
	int num,ti,id;
	bool operator<(const number &t)const{
		return ti>t.ti;
	}
}a[N];
int p[N],l[N],r[N],v[N],lazy[N],dist[N];
int find(int x){
	return x==p[x]?x:p[x]=find(p[x]);
}
bool cmp(int x,int y){//并查集的根就是左偏树的根
	return v[x]==v[y]?x<y:v[x]>v[y];
}
void trans(int u,int d){
	v[u]+=d,lazy[u]+=d;
}
void pushdown(int u){
	if(lazy[u]==0)return;
	trans(l[u],lazy[u]);
	trans(r[u],lazy[u]);
	lazy[u]=0;
}
int merge(int x,int y){
	if(!x||!y)return x+y;
	pushdown(x),pushdown(y);
	if(cmp(y,x))swap(x,y);
	r[x]=merge(r[x],y);
	if(dist[l[x]]<dist[r[x]])swap(l[x],r[x]);
	dist[x]=dist[r[x]]+1;
	return x;
}
void Merge(int x,int y){//合并
	x=find(x),y=find(y);
	if(x==y)return;
	if(cmp(y,x))swap(x,y);
	merge(x,y),p[y]=x;
}
void remove(int x){
	x=find(x);
	int nt=merge(l[x],r[x]);
	p[x]=nt,p[nt]=nt,l[x]=r[x]=0;
}
int n,k;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i].num);
		for(int i=1;i<=n;++i)
			a[i].ti=(a[i].num+k-1)/k,a[i].id=i,l[i]=r[i]=dist[i]=0,p[i]=i;//初始化
		sort(a+1,a+1+n);//对于砍死次数排序
		for(int i=1;i<=n;++i){
			v[a[i].id]=a[i].num;
			if(i!=1){
				if(a[i].ti<a[i-1].ti)//下方lazytag
					trans(find(a[i-1].id),-(a[i-1].ti-a[i].ti)*k);
				Merge(a[i-1].id,a[i].id);//不断合并
			}
		}
		int rt=find(1);
		while(rt){//不断弹出
			printf("%d ",rt);
			remove(rt),rt=find(rt);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：saixingzhe (赞：2)

# 分析
我们发现，每个数 $a$ 可以变为 $a \div k + a \bmod k$，这其中先被打掉的一定是 $a \div k$ 的部分，考虑把所有数对 $k$ 取模，先输出为 $0$ 的，
然后其他按从大到小排序输出。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,k;
struct Node{
	int id,Num;
}a[300002];
bool cmp(Node x,Node y){
	if(x.Num!=y.Num)	return x.Num>y.Num;
	return x.id<y.id; 
}
int main(){
	cin>>T;
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].Num),a[i].id=i,a[i].Num%=k;
			if(a[i].Num==0)	printf("%d ",i);
		}	
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			if(a[i].Num==0)	break;
			printf("%d ",a[i].id);
		}
		printf("\n"); 
	}
	return 0;
}
```

---

## 作者：ylch (赞：1)

# 洛谷 CF1849B 题解

[【猛击这里 查看题目】](https://www.luogu.com.cn/problem/CF1849B)

## 题目大意

有 $n$ 个怪物，每个怪物都有自己的生命值，你可以每次对当前血量最高的怪物实施 $k$ 点伤害（存在多个最大血量时按照输入顺序实施伤害），直到所有怪物的血量小于等于 $0$ 为止。请你求出怪物的死亡顺序，以输入序号的形式输出。

## 解题思路

这道题纯暴力的话肯定超时，但是有一个小技巧，不难证明，每个怪物在即将进行死亡前最后一次伤害时的血量一定为 $a_i  \bmod k$。这是因为之前每次对怪物实施的伤害是固定的，也就是说到死亡前它一定经历了 $a_i \div k$ 次伤害，其剩余生命值就一定为 $a_i \bmod k$ 了。

所以我们可以用结构体来存储 $a_i \bmod k$ 的值与输入时的序号 $id$，然后通过排序来确定死亡顺序。注意排序时要特判 $0 \equiv a_i \pmod k$ 的情况，血量为 $0$ 的排在前面，其余的按照剩余血量由大到小排序（因为先攻击血量多的），血量一样按照输入顺序升序排序。

这样，我们就攻克了一道看似复杂的难题。其实题目并不难，只要我们静下心来，认真分析，认真整理，就不难思考出正解。

## AC 代码

```cpp
#include <algorithm>
#include <cstdio>
#define ll long long
using namespace std;

int T,n,k;
struct St
{
	int blood_volume;
	int id;
	static bool cmp(St &p1, St &p2)
	{
		if (p1.blood_volume == 0)	return true;
		else if (p2.blood_volume == 0)	return false;
		else if (p1.blood_volume != p2.blood_volume)
			return p1.blood_volume > p2.blood_volume;
		else
			return p1.id < p2.id;
	}
}st[300005];

signed main()
{
	for (scanf("%d", &T); T--; )
	{
		scanf("%d %d", &n, &k);
		for (int i=1; i<=n; i++)
		{
			scanf("%d", &st[i].blood_volume);
			st[i].blood_volume %= k;
			st[i].id = i;
		}
		sort(st+1, st+n+1, St::cmp);
		for (int i=1; i<=n; i++)
			printf("%d ", st[i].id);
		printf("\n");
	}
	return 0;
}
```

End
-------------

管理员大大辛苦啦~

谢谢大家！

---

## 作者：Spir1t (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1849B)


------------

#### 题目大意：

题目的意思就是给出怪物的血量和你技能的伤害，技能每次会攻击生命值最高的怪物，最后让你求出怪物的死亡顺序。

#### 思路：

不难想到，最后每只怪物一定会被打到只剩血量 $\bmod$ $k$ 的值，也就是说我们其实只需要将每个数 $\bmod$ $k$，然后用一个 `cmp` 函数，定义一下排序规则，优先将生命值从大到小排，第二优先将索引从小到大排即可。

代码就不放了，很好写。

---

## 作者：PikachuQAQ (赞：1)

## Description

$n$ 只怪物，第 $i$ 只怪物的血量是 $a_i$，你每回合对 $a_i$ 最大的敌人造成伤害，如果有多个敌人 $a_i$ 相同，你会对 $i$ 最小的敌人造成伤害。输出怪物的死亡顺序。

本题**有多组数据**。

$1\leq n\leq3\cdot 10^5$，$1\leq k\leq10^9$，$1\leq a_i\leq 10^9$，时限 $2$ 秒。

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1849B)

[CF 题面传送门](https://codeforces.com/contest/1849/problem/B)

## Analysis

容易想到可以用优先队列模拟，时间复杂度 $O(\sum a_i\cdot n \log_2 n)$，显然会超时。

手玩样例发现：对于数组 $a$，总有一个 $a$ 的变化过程中的**阶段性状态** $a'$ 中的 $a'_i=a_i\bmod k$，这个状态实际上是因为在攻击时把所有 $a_i$ 中包含的 $k$ 都取出来**必定得到**的。也就是说，当所有 $a_i\leq k$ 时，所有怪物均一击必杀，死亡顺序就是按剩余血量从大到小排列，所有怪物均一击必杀的 $a$ 数组的状态**一定存在**。

听不懂？考虑数组 $a=\{7,\color{red}8\color{black},5,4,1\}$，其中 $k=3$，第一个最大值标红。

我们来模拟这个过程：

取出最大 $a_i=8$，$a_i\rightarrow a_i-k$，即 $a_i\rightarrow a_i-3=5$，并不小于等于 $0$，放回去。

此时 $a=\{\color{red}7\color{black},5,5,4,1\}$。

取出最大 $a_i=7$，$a_i\rightarrow a_i-k$，即 $a_i\rightarrow a_i-3=4$，并不小于等于 $0$，放回去。

此时 $a=\{4,\color{red}5\color{black},5,4,1\}$。

取出最大 $a_i=5$，$a_i\rightarrow a_i-k$，即 $a_i\rightarrow a_i-3=2$，并不小于等于 $0$，放回去。

此时 $a=\{4,2,\color{red}5\color{black},4,1\}$。

取出最大 $a_i=5$，同上。$a=\{\color{red}4\color{black},2,2,4,1\}$。

取出最大 $a_i=4$，$a_i\rightarrow a_i-k$，即 $a_i\rightarrow a_i-3=1$，并不小于等于 $0$，放回去。

此时 $a=\{1,2,2, \color{red}4\color{black},1\}$。

取出最大 $a_i=5$，同上，$a=\{1,2,2,1,1\}$，$a_i$ 均小于 $k$。

此时再回来考虑我们的结论：对于数组 $a$，总有一个阶段性状态 $a'$ 中的 $a'_i=a_i\bmod k$。我们对其进行验证，发现 $a'=\{1,2,2,1,1\}$，正等同于上述的计算，结论正确。

我们再进行考虑：

首先，对于 $a'_i=0$，则判定为“已经死亡”，需要优先输出。

然后，因为 $i$ 最大 $a_i$ 优先被选中，我们对 $a'$ 按 $a_i$ 从大到小排序，如果则选择最小 $i$ 对应 $a_i$。

最后，我们输出排序过后 $a_i$ 在 $a$ 中原来的下标。

时间复杂度 $O(n \log_2 n)$。

## Code

```cpp
// 2023/7/28 Accepted

#include <algorithm>
#include <iostream>

using namespace std;

const int kMaxN = 3e5 + 7;

struct E {
    int id, x;
    bool operator < (const E &b) const {
        return (x < b.x) ? 0 : (x == b.x ? (id < b.id) : 1);
    }
} a[kMaxN];

int t, n, k, tmp, id;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> t; t; t--) {
        cin >> n >> k;
        for (int i = 1, x; i <= n; i++) {
            cin >> a[i].x;
            a[i].x %= k, a[i].id = i;
            if (a[i].x == 0) {
                cout << i << ' ';
            }
        } 
        sort(a + 1, a + n + 1);
        for (int i = 1; i <= n; i++) {
            if (a[i].x != 0) {
                cout << a[i].id << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}

```

---

## 作者：Crazyouth (赞：1)

**翻译**

有 $n$ 个怪物，每个怪物有血量 $a_i$，有一个技能可以使最高血量的怪物血量减 $k$，假如一个怪物血量小于等于 $0$，它就死了。求把怪物按死亡顺序排序。

**分析**

诈骗题。~~观察样例可得~~我们只需要排序 $a_i$ 模 $k$ 的余数即可，简单证一下。对于任意一个怪物，我们都需要到它血量小于等于 $k$ 时才会死，所以它大于 $k$ 的几次减法其实是无效的，所以排序余数即可。特别地，假如一个数整除 $k$，我们认为它模 $k$ 余 $k$，不然排序会挂。

**AC Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,k;
struct mon
{
	int hp,pos;//血量，下标
}a[int(3e5+10)];
int cmp(mon x,mon y)//排序
{
	int xm=x.hp%k,ym=y.hp%k;
	if(xm==0) xm=k;
	if(ym==0) ym=k;
	if(xm!=ym) return xm>ym;
	else return x.pos<y.pos;
}
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].hp;
			a[i].pos=i;
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++) cout<<a[i].pos<<' ';
		cout<<endl;
	} 
	return 0;
}

---

## 作者：ataraxiaer (赞：1)

# 思路

**一道比较水的题目，每次操作中选择血量最高的怪物并将其血量减去 $k$,(如果两只怪物血量相同且最高则选择编号较小的），事实上不难想到，最后的死亡顺序只取决于各只怪物的血量均不大于 $k$ 之后血量排序，因此模 $k$ 以后，从高到低排序即可，注意对模 $k$ 为 $0$ 的要特殊处理。**

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct mo
{
    long long a;
	int s;
}m[300005];
int n;
long long k;
bool cmp(mo x,mo y)
{
	if(x.a>y.a)return 1;
	else if(x.a<y.a)return 0;
	else
	{
		return x.s<y.s;
	}
}
 
void solve()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>m[i].a;
		m[i].s=i;
		if(m[i].a%k!=0)
		{
			m[i].a%=k;
		}
	    if(m[i].a%k==0)
		{
			m[i].a=k;
		}
	}
	
	sort(m+1,m+n+1,cmp);
	
	for(int i=1;i<=n;i++)
	{
		cout<<m[i].s<<" ";
	}
	cout<<endl;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		solve();
	}
}
```


---

## 作者：xiazha (赞：0)

### 思路
贪心排序题。

显然，如果怪物的初始血量是 $k$ 的倍数肯定是最先死掉的。如果血量无法整除 $k$，那么余数较大的先死掉，因为所有无法整除 $k$ 的血量每次减 $k$ 到最后一定都只剩下了余数，而此时剩余血量较大的怪兽就会被杀死。因此，我们只需结构体排序即可。

需要注意的是，余数相同的情况需按编号小到大排序。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k,x;
struct node
{
	int id,sh,yu;
}a[300003];
bool cmp(node a,node b)
{
	if(a.yu==b.yu) return a.id<b.id;
	else if(a.yu==0||b.yu==0) return a.yu<b.yu;
	else return a.yu>b.yu;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>x,a[i].id=i,a[i].sh=x/k,a[i].yu=x%k;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++) cout<<a[i].id<<" ";
		cout<<"\n";
	}
	return 0;
}
```


---

## 作者：tbdsh (赞：0)

# 题意简述
[洛谷原题](/problem/cf1849b)

[CF 原题](http://codeforces.com/contest/1849/problem/B)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf1849b)

有 $t$ 组数据。每组数据给定 $n$ 个怪物，其血量为 $a_i$。Monocarp 的攻击力为 $k$。

每次攻击，Monocarp 会选择一个血量最高的怪物进行攻击。如果血量相同就选择编号小的。

当怪物的血量 $a_i\le 0$ 时它就死了。

请你按每个怪物死亡的顺序输出他们的编号。



# 分析
首先考虑用优先队列维护，每次攻击，最后输出。

但是很显然，当 $\min\{a_i\}\ge10^8,k=1$ 时会超时。

不难发现：每个怪物最后的血量一定会 $<k$。~~废话~~

那么我们考虑对每个怪物 $i$ 直接进行 $\left\lfloor\dfrac{a_i}{k}\right\rfloor$ 次攻击，即 $a_i\gets a_i \mod k$。如果此时 $a_i$ 已经为 $0$，那么就直接加入答案，否则加入队列。

然后再用优先队列维护即可。

时间复杂度：$O(n\log n)$。

空间复杂度：$O(n)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 3e5 + 5;
int t, n, k, ans[MAXN];
struct Node{
  int p, id;
  bool operator<(const Node &i)const{
    return (p == i.p ? id > i.id : p < i.p);
  }
};
void Solve(){
  priority_queue<Node> a;
  int cnt = 0;
  cin >> n >> k;
  for (int i = 1; i <= n; i++){
    int x;
    cin >> x;
    x %= k;
    if (x){
      a.push({x, i});
    }else {
      ans[++cnt] = i;
    }
  }
  while (a.size()){
    auto x = a.top();
    a.pop();
    x.p -= k;
    if (x.p <= 0){
      ans[++cnt] = x.id;
    }else {
      a.push(x);
    }
  }
  for (int i = 1; i <= cnt; i++){
    cout << ans[i] << " \n"[i == cnt];
  }
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：sz_jinzikai (赞：0)

[洛谷传送门](/problem/CF1849B) &[CF 传送门](//codeforces.com/problemset/problem/1849/B)
# 题目大意
给定 $n$ 个怪物的血量 $a_i$ 和你的技能伤害 $k$，你每次对血量最多的怪物释放一次技能使怪物血量减少 $k$（如果有多个血量最多的怪物，则对编号最小的怪物释放技能），当怪物血量 $\le0$ 时怪物死亡，按怪物死亡的顺序输出怪物的编号。
# 思路
不难想到，每个怪物到最后血量都会变成 $\le k$ 的，然后再释放一次技能就死亡，所以我们只要看每个怪物的血量到了 $\le k$ 时具体是多少，即 $(a_i-1)\mod k+1$，然后从大到小排序就得到了答案。
# 代码
```cpp
//CF1849B
# include <bits/stdc++.h> //万能头 
using namespace std;
struct node { //定义结构体 
	int num, id; //num 是怪物血量，id 是输入的顺序 
	bool operator < (const node &x) const { //重载运算符，当然你也可以写成 cmp 的形式 
		if (num != x.num) //血量不同 
			return num > x.num; //看血量 
		return id < x.id; //血量相同看输入顺序 
	}
} a[300005];
int t, n, k;
int main () {
	cin >> t;
	while (t --) { //多组数据通用写法 
		cin >> n >> k;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i].num, a[i].id = i, a[i].num = (a[i].num - 1) % k + 1;
		sort (a + 1, a + n + 1); //排序 
		for (int i = 1; i <= n; ++ i)
			cout << a[i].id << ' '; //输出 
		cout << '\n'; //别忘了换行！！！ 
	}
	return 0; //结束程序 
}
```

---

## 作者：hjsxhst2022 (赞：0)

[~~点击这里，题目10倍奖励~~](https://www.luogu.com.cn/problem/CF1849B)

### 题意
有 $n$ 个怪物，每个怪物都有血量，你可以对当前血量最高的怪物减少 $k$ 点生命，如果存在多个最大血量则按照输入顺序伤害，直到所有怪物的血量小于等于 $0$ 为止。请你输出怪物的死亡顺序。

~~但是为什么怪物不能反击啊~~

### 思路
这题暴力肯定超时。那么：我们先考虑只剩下两只怪物时它们谁会先死掉。

当只有两只怪物时，血量较大的一只一定会被先伤害，一直打到血量小等于另一只。然后它们轮流被伤害。最后，一定会被伤害到血量都只剩下原血量 $\bmod k$ 的值。

所以我们可以用结构体来存储 $a_i \bmod k$ 的值与怪物的序号，然后通过排序来确定死亡顺序。按照剩余血量由大到小排序，如果血量一样按照输入顺序升序排序。

代码不写了，很简单。

~~蒟蒻的第 $2$ 篇题解!~~

---

## 作者：Night_sea_64 (赞：0)

我们先考虑其中两只怪物它们谁会先死掉。

当只有两只怪物时，血量较大的一方会被先打，一直打到血量小于等于另一方。然后它们轮流被打。最后，一定会被打到都只剩下血量 $\bmod k$ 的值。

1. 如果至少有一方当前血量 $=0$：
	1. 只有一方为 $0$，它先死；
    1. 两方都为 $0$，编号小的先死。
1. 否则：
	1. 两方当前血量不相等，血量多的先死；
    1. 两方当前血量相等，编号小的先死。

知道了任意两只怪物死掉的先后顺序，就能通过排序确定所有怪物死掉的顺序了。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,k;
struct node{int x,id;}a[300010];
bool cmp(const node &x,const node &y){
    if(x.x%k!=y.x%k)
    {
        if(x.x%k==0||y.x%k==0)return x.x%k==0;
        else return x.x%k>y.x%k;
    }
    else return x.id<y.id;
}
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i].x;
            a[i].id=i;
        }
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=n;i++)cout<<a[i].id<<" ";
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：_Only_this (赞：0)

### CF1849B Monsters 题解

------------

给定 $n$ 个怪物的血量和一次技能的伤害，每次攻击当前血量最高的怪物，如果血量一样，攻击最往前的，问怪物的死亡顺序。

------------

此题暴力模拟不现实，因此考虑将所有怪物的血量 $\bmod$ $k$，目的是让模拟过程直接快进到最后一步。

如果当前的怪物直接就挂了，那么从前往后将这些挂了的怪物的下标输出。

剩下的怪物攻击一下也就死了，于是直接从大到小排个序输出下标即可。

贴个代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+5;
struct qwe{
	int a,id;
}a[maxn];
int T,n,k;
inline bool Cmp(qwe x,qwe y){
	if(x.a!=y.a)
		return x.a>y.a;
	return x.id<y.id;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i].a),a[i].a%=k,a[i].id=i;
		sort(a+1,a+n+1,Cmp);
		for(int i=1;i<=n;i++){
			if(!a[i].a){
				printf("%d ",a[i].id);
			}
		}
		for(int i=1;i<=n;i++){
			if(a[i].a){
				printf("%d ",a[i].id);
			}
		}
		printf("\n");
	}
	return 0;
}
```


---

## 作者：LIUYC_C (赞：0)


[题目链接](https://www.luogu.com.cn/problem/CF1849B)。
## 大体思路：

这题不需要可并堆。

我只能说这道题真的不符合 B 题水准，~~虽然说一开始写了个优先队列摁模拟 T 了~~，但是这题还是非常水的，不难想到，每次挑最大的值减，那这样的话肯定就会减到一个再减一次就小于等于 $0$ 了的状态，那么，有了这样一个性质，我们只需要让每个数模上 $k$，得到这样一个再减一次就小于等于 $0$ 的状态，对这个状态的值作为第一关键字从大到小排序，下标作为第二关键字从小到大排序就好了。

需要注意的是，如果模上$k$ 等于 $0$ 的话，它的最终状态的值的大小就是 $k$。

## 代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=301010;
 
typedef long long LL;
 
 
struct node{
    LL x;
    LL y;
    int id;
};
node a[N];
 
bool cmp(node a,node b){
  if(a.y==b.y)return a.id<b.id;
  return a.y>b.y;
}
 
 
int main(){
  int t;
  cin>>t;
 
  while(t--){
    LL n,k;
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++){
      scanf("%lld",&a[i].x);
      a[i].id=i;
      if(a[i].x%k!=0)a[i].y=a[i].x%k;
      else a[i].y=k;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
      cout<<a[i].id<<" ";
    }
    cout<<endl;
  }
  return 0;
}
```
时间复杂度 $O(n\log n)$。

---

## 作者：pur_lin (赞：0)

# CF1849B Monsters

### 题目大意

给定长度为 $n$ 的序列，每次取序列中最大的数并减去 $k$，若有多个最大值则取序号最小的一个，求使所有的数小于等于 $0$ 的操作顺序。

### 思路

显然对于序列中所有大于 $k$ 的数 $x$，一定会经过若干次操作后变为 $x \bmod k$，因为 $> k$ 的数显然比 $\le k$ 的数更先操作，所以任意序列一定会先满足所有的元素 $\le k$ 后再出现 $\le 0$ 的数。

对于任意小于等于 $k$ 的元素，显然经过一次操作后就会满足 $\le 0$ 的条件。

那么正解是明晰的：将所有数 $x \bmod k$，然后从大到小排序即可。

特别地，对于 $x_1 \bmod k = 0$，可以证明 $x_1$ 一定会比任意 $x_2 \bmod k \ne 0$ 更先满足条件。因为 $x_1$ 会 $= k$ 而 $x_2$ 会 $< k$ ，证明是显然的。

特殊地，当 $k=1$，直接从 $1$ 到 $n$ 输出即可，证明同样是显然的。

### 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=3e5+10;
struct number{
    int id,num;
}a[N];
bool cmp(number x,number y){
    if(x.num!=y.num) return x.num>y.num;
    return x.id<y.id;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            int x;
            cin>>x;
            if(x%k) a[i].num=x%k;
            else a[i].num=k;
            a[i].id=i;
        }
        if(k==1){
            for(int i=1;i<=n;i++) cout<<i<<" ";
            cout<<endl;
            continue;
        }
        sort(a+1,a+n+1,cmp);
        for(int i=1;i<=n;i++) cout<<a[i].id<<" ";
        cout<<endl;
    }
    return 0;
}
```

#### 建议评橙

~~因为某要带我上分的巨佬在这道题上卡了所以特此写这篇题解~~

curlin 2023.7.28

---

## 作者：ant2010 (赞：0)

## 题意简述
有 $n$ 个怪，编号为 $i$ 的怪有一个血量值 $a_i$，每次 Monocarp 会把剩余血量最多的一个怪打掉 $k$ 点血（如果有血量一样多的就优先打编号更小的），输出怪的死亡顺序。
## 暴力
用优先队列来维护当前拥有最多血量的怪，将其血量值减去 $k$ ，如果血量值不大于 $0$ 就输出，否则重新加入队列。

时间复杂度 $O(\frac{n\max{a_i}}{k}\cdot \log n)$。
### 小优化
每次取出优先队列中血量最大值 $x$ 的同时记录次大值 $y$，可以直接将 $x$ 减去 $\left(\lfloor\frac{x-y}{k}\rfloor+1\right)\cdot k$。
## 正解
我们将所有的 $a_i$ 按照 $\lfloor a_i\div k\rfloor$ 的值进行分类。

找到其中 $\lfloor a_i\div k\rfloor$ 的值最大的那一类，发现里面所有的元素都会依次的进行减 $k$ 操作，使得 $\lfloor a_i\div k\rfloor$ 的值减少 $1$。

那么最终所有的元素都会满足 $\lfloor a_i\div k\rfloor=0$，即 $a[i]<k$，都只剩最后一次操作，只需排序输出即可。

但是，还会有特殊情况，若 $a_i\bmod k=0$，那么这个怪直接就死了，不会再有最后一步。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int const maxn=3e5+5;
pii a[maxn];
bool cmp(pii &a,pii &b){
	if(a.first!=b.first)return a.first>b.first;
	return a.second<b.second;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n,k,x;
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			if(x%k==0)a[i]=make_pair(k,i);
			else a[i]=make_pair(x%k,i);
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)printf("%d ",a[i].second);
		printf("\n");
	}
}
```

---

