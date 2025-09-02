# Two Types of Spells

## 题目描述

你有许多咒语。

咒语可以被分为两种：火之咒和电之咒。

每一条咒语有一个初始攻击力。

众所周知，一连串咒语的总攻击力和它们释放的顺序是密切相关的。

对于一种释放顺序，设第`i`个释放的咒语的初始攻击力为$w_i$。那么，如果第`i-1`个释放的咒语为电之咒，则它最终产生的攻击力为$2\cdot w_i$，如果第`i-1`个释放的咒语为火之咒，则它最终产生的攻击力为$w_i$。

总攻击力即为所有咒语的最终攻击力之和。

作为一名魔法师，你会学习新的咒语，同时也会忘掉旧的咒语。

刚开始你不会任何咒语，为了评估自己的实力，你想知道在每一次学习或忘却后，对于所有可能的咒语释放顺序，总攻击力能达到的最大值是多少。

## 样例 #1

### 输入

```
6
1 5
0 10
1 -5
0 5
1 11
0 -10```

### 输出

```
5
25
10
15
36
21```

# 题解

## 作者：奇米 (赞：7)

# 题解 $\mathrm{CF1398E}$

## 题目意思

[题目传送门](https://www.luogu.com.cn/problem/CF1398E)

## $\mathrm{Sol}$

感觉这是最近我做过比较难的 $E$ 啦，细节真的草鸡多

我们在这里假定 $A$ 为能翻倍的法术，$B$ 相反


我们首先有个贪心思路就是每个 $A$ 尽量配对大的 权值，并且第一个使用 $A$ 的本身权值尽可能小，因为其不能产生翻倍贡献。

我们考虑用 set 维护 $A$ 权值的集合（既保证不重复也从小到大排序便于操作）。并且假设现在有 $s$ 个 $A$ 那么我们计 $s1$ 表示前 $s$ 大的权值和，$s2$ 表示前 $s+1$ 大的权值和，以及 $S$ 为当前所有权值的总和。

于是我们分类讨论：

* 假设当前 $A$ 的最小值 $mi$ 在所有权值的排名 $\leq s$ 那么贡献即为 $(S+pre2-mi)$。具体地就是把这个最小的作为 $A$ 的开头然后 $s$ 个 $A$ 本身连接使用，最后带一个 $B$。

* 对于其他情况的贡献即为 $(S+pre1)$ 即一个配一个即可。

对于权值的排名我们直接平衡树维护一下就好了（div2E 就要用平衡树/fad，直接贺了个fhq就好了）

时间复杂度：$O(n\log  n)$

## $\mathrm{Code}$

```cpp
const int N=1e6+5;

int n,m,noden,tot,cnt,pre1,pre2;
int ans,sum;
set<int> S;
 
struct node
{
	int lc,rc,rnd,val,sz;
}a[N];
 
struct fhq{
	#define new NEW
	int rt;
	void pushup(int x){
		a[x].sz=a[a[x].lc].sz+a[a[x].rc].sz+1;
	}
	
	int new(int val){
		a[++noden]=(node){0,0,rand(),val,1};
		return noden;
	}
	void split(int now,int val,int &x,int &y){
		if(!now){
			x=y=0;
			return ;
		}
		if(a[now].val>=val){
			x=now;
			split(a[now].rc,val,a[now].rc,y);
		}
		else{
			y=now;
			split(a[now].lc,val,x,a[now].lc);
		}
		pushup(now);
	}
	int merge(int x,int y){
		if(!x||!y) return x|y;
		if(a[x].rnd<a[y].rnd){
			a[x].rc=merge(a[x].rc,y);
			pushup(x);
			return x;
		}
		else{
			a[y].lc=merge(x,a[y].lc);
			pushup(y);
			return y;
		}
	}
	int getk(int x,int k){
		if(!k||k>a[rt].sz) return 0;
		for(;;){
			if(k<=a[a[x].lc].sz) x=a[x].lc;
			else if(k==a[a[x].lc].sz+1) return x;
			else{
				k-=a[a[x].lc].sz+1;
				x=a[x].rc;
			}
		}
	}
	void insert(int val){
		int x,y;
		split(rt,val,x,y);
		rt=merge(merge(x,new(val)),y);
	}
	void Del(int val){
		int x,y,z;
		split(rt,val,x,z);
		split(x,val+1,x,y);
		y=merge(a[y].lc,a[y].rc);
		rt=merge(merge(x,y),z); 
	}
	int Find(int val){
		int res,x,y;
		split(rt,val+1,x,y);
		res=a[x].sz+1;
		rt=merge(x,y);
		return res;
	}
	int Kth(int rank){
		return a[getk(rt,rank)].val;
	}
}T;

signed main()
{
	io.read(n);
	for (;n--;)
	{
		int op,x;
		io.read(op),io.read(x);
		int y=abs(x);
		sum+=x;
		int rk=T.Find(y);
		if(x>0) 
		{
			if(rk<=cnt) pre1+=(y-T.Kth(cnt));
			if(rk<=cnt+1) pre2+=(y-T.Kth(cnt+1));
			T.insert(y);
			if(op==1)
			{
				cnt++;
				pre1+=T.Kth(cnt);
				pre2+=T.Kth(cnt+1);
				S.insert(y);
			}
			if(T.Find(*S.begin())==cnt) ans=sum+pre2-*S.begin();
			else ans=sum+pre1;
		}
		else 
		{
			if(rk<=cnt) pre1-=(y-T.Kth(cnt+1));
			if(rk<=cnt+1) pre2-=(y-T.Kth(cnt+2));
			T.Del(y);
			if(op==1)
			{
				pre1-=T.Kth(cnt);
				pre2-=T.Kth(cnt+1);
				cnt--;
				S.erase(y);
			}
			if(cnt&&T.Find(*S.begin())==cnt) ans=sum+pre2-*S.begin();
			else ans=sum+pre1;
		}
		io.write(ans);
		puts("");
	}
	return 0;
}
			
			
			

```


---

## 作者：MarSer020 (赞：3)

~~为什么我打的场次的 Div2 E 都这么难/lh~~

$\Large\text{Solution}$

题意：有两种球，第一种能让下一个球价值翻倍，每次操作添加或删除一个球，每次操作后求最大总价值，保证不存在同样价值的球。

首先想到贪心：翻倍显然要给价值最大的球用，每次暴力加入删除排序统计答案，时间复杂度 $\Theta(n^2\log n)$。注意如果此时选择的翻倍的球都是第一种球，由于不可能使所有第一种球都翻倍，需要判断一下选择剩余球中最大的。

考虑优化：需要维护插入删除，查询全局前 $k$ 大，可以使用平衡树，每次二分当前的 $k$ 大值，时间复杂度 $\Theta(n\log^2 n)$。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ls t[cur].lc
#define rs t[cur].rc
using namespace std;
int q,rt[2],tot,tp,val,a,b,c,d,e,l,r,mid;
int64_t ans;
mt19937 rng(random_device{}());
uniform_int_distribution<int>gen(1,0x3f3f3f3f);
struct node{
	int val,lc,rc,siz,rnk;
	int64_t sum;
}t[400005];
int add(int val){
	t[++tot]={val,0,0,1,gen(rng),val};
	return tot;
}
void split(int cur,int&a,int&b,int val){
	if(!cur){
		a=b=0;
		return;
	}
	if(t[cur].val>=val)
		a=cur,split(rs,rs,b,val);
	else
		b=cur,split(ls,a,ls,val);
	t[cur].siz=t[ls].siz+t[rs].siz+1,t[cur].sum=t[ls].sum+t[rs].sum+t[cur].val;
}
void merge(int&cur,int a,int b){
	if(!a||!b){
		cur=a|b;
		return;
	}
	if(t[a].rnk<t[b].rnk)
		cur=a,merge(rs,rs,b);
	else
		cur=b,merge(ls,a,ls);
	t[cur].siz=t[ls].siz+t[rs].siz+1,t[cur].sum=t[ls].sum+t[rs].sum+t[cur].val;
}
int fmin(int cur){
	while(rs)
		cur=rs;
	return t[cur].val;
}
int fmax(int cur){
	while(ls)
		cur=ls;
	return t[cur].val;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>q;
	while(q--){
		cin>>tp>>val;
		if(val>0)
			split(rt[tp],a,b,val),merge(a,a,add(val)),merge(rt[tp],a,b);
		else
			val=-val,split(rt[tp],a,b,val),split(a,a,c,val+1),merge(rt[tp],a,b);
		//插入删除
		l=1,r=0x3f3f3f3f,val=t[rt[1]].siz;
		if(!val){
			cout<<t[rt[0]].sum<<'\n';
			continue;
		}//如果没有可以翻倍的直接判掉
		while(l<=r){
			mid=(l+r)>>1,split(rt[0],a,b,mid),split(rt[1],c,d,mid),e=t[a].siz+t[c].siz;
			if(e==val)
				break;//如果当前选中的刚好够就直接 break 掉
			else if(e>val)
				l=mid+1;
			else
				r=mid-1;
			merge(rt[0],a,b),merge(rt[1],c,d);
		}//二分k大值
		if(t[a].siz)
			ans=((t[a].sum+t[c].sum)<<1)+t[b].sum+t[d].sum;
		else
			ans=(t[c].sum<<1)+t[b].sum+t[d].sum-fmin(c)+fmax(b);//如果所有选中的都是能翻倍的
		cout<<ans<<'\n',merge(rt[0],a,b),merge(rt[1],c,d);
	}
	return 0;
}
```

---

## 作者：Ryo_Yamada (赞：2)

fhq Treap 解法

题目要求我们支持插入和删除两种咒语，其中放在电之咒后一个的咒语效果会翻倍。

设 $cnt_{0/1}$ 表示当前 火之咒/电之咒 的个数。

考虑如何求这个最大值。首先电之咒的翻倍效果很容易想到用在攻击力最大的咒语上。所以每次求出最大的 $cnt_1$ 个数，将它们的攻击力 $\times 2$ 算入答案。

显然有一个问题，就是最大的 $cnt_1$ 个咒语都是电之咒。此时将攻击力第 $cnt_1$ 大的电之咒的效果变成一倍，然后在剩余的咒语（如果有的话）中取最大的翻倍。

平衡树维护即可。

$\text{Code}$：

```cpp
def(N, int, 2e5 + 5);

struct fhq {
    int ls, rs, sze, rnd;
    int x, tp, c[2];
    ll sum;
} t[N];

int q;
int root;
int cnt[2], sz;
ll sum;

int New(int op, int x) {
    static int r = 0;
    ++r;

    t[r].ls = t[r].rs = 0;
    t[r].sze = 1;
    t[r].rnd = rand();
    t[r].x = t[r].sum = x;
    t[r].tp = op;
    ++t[r].c[op];

    return r;
}

void pushup(int x) {
    t[x].sze = t[t[x].ls].sze + t[t[x].rs].sze + 1;
    t[x].sum = t[t[x].ls].sum + t[t[x].rs].sum + t[x].x;
    t[x].c[0] = t[t[x].ls].c[0] + t[t[x].rs].c[0] + (t[x].tp == 0);
    t[x].c[1] = t[t[x].ls].c[1] + t[t[x].rs].c[1] + (t[x].tp == 1);
}

int merge(int x, int y) {
    if(!x || !y) return x + y;
    if(t[x].rnd < t[y].rnd) {
        t[x].rs = merge(t[x].rs, y);
        pushup(x);
        return x;
    }
    else {
        t[y].ls = merge(x, t[y].ls);
        pushup(y);
        return y;
    }
}

void split(int rt, int &x, int &y, int k) {
    if(!rt) return x = y = 0, void();
    if(t[rt].x <= k) {
        x = rt;
        split(t[x].rs, t[x].rs, y, k);
    }
    else {
        y = rt;
        split(t[y].ls, x, t[y].ls, k);
    }
    pushup(rt);
}

void insert(int op, int x) {
    int l, r;
    split(root, l, r, x - 1);
    root = merge(l, merge(New(op, x), r));  
}

void del(int x) {
    int l, mid, r;
    split(root, l, r, x - 1);
    split(r, mid, r, x);
    root = merge(l, r);
}

int kth(int rt, int k) {
    while(1) {
        if(t[t[rt].ls].sze + 1 == k) return t[rt].x;
        if(t[t[rt].ls].sze + 1 < k) k -= t[t[rt].ls].sze + 1, rt = t[rt].rs;
        else rt = t[rt].ls;
    }
}

ll calc() {
    ll ret = sum;
    if(!cnt[1]) return ret;
    int nw = kth(root, t[root].sze - cnt[1] + 1);
    int l, r;
    split(root, l, r, nw - 1);
    if(t[r].c[1] == cnt[1]) {
        ret += t[r].sum;
        ret -= kth(r, 1);
        if(t[l].sze) ret += kth(l, t[l].sze);
    }
    else ret += t[r].sum;
    root = merge(l, r);
    return ret;
}

int main() {
    srand(19260817);
    qread(q);
    W(q) {
        int op, x;
        qread(op, x);
        sum += x;
        if(x < 0) {
            --sz;
            --cnt[op];
            del(-x);
        }
        else {
            ++sz;
            ++cnt[op];
            insert(op, x);
        }
        printf("%lld\n", calc());
    }
	return 0;
}
```


---

## 作者：Wall_breaker (赞：2)

~~比赛的时候脑子抽了，竟然选择用了堆，简直是zz~~
## SET——永远滴神（当前最优解，时间4.22s）

看到题解中各路神仙辈出，平衡树线段树各种大法都有，但都没有用set的人，那么我就来写一发set的题解。

### 1.题意

有火咒和闪咒两种咒语，其中闪咒有给下一个咒语2倍伤害的加成，那么，如果要求最大伤害，自然应当把前 $k$ 大的咒语放在 $k$ 个闪咒的后面，这样能使伤害增加的最多。但有两种情况要特殊判断，

**A.最小的闪咒一定不会被翻倍，运用反证法，如果它被翻倍，说明在它之前一定存在一个没有被翻倍的闪咒，则交换两者顺序能获得更优解** 

**B.即全部都是闪咒，这时最后一个也是最大的闪咒后面是空的，最小的闪咒没有办法翻倍**

**总结：最小的闪咒不能翻倍** 

例如 $1 3 4 5 7$，那么 $7$ 后面没有咒语，无需翻倍，1前面没有闪咒，不能翻倍

### 2.思路

大致搞定题意要求，那么，我们如何在每一次修改后直接得到答案呢？我当时想到的对顶堆的方法，事实证明这是可行的，只不过用的是set（qwq）。我们用 $q$ 表示存前len大伤害的咒语的集合（len表示闪咒的个数），$p$ 表示存剩余的 **不是最小闪咒的** 咒语集合， $s$ 表示存**所有**闪咒的集合。

下面是很关键的一步：**调整**

如果说 $q$ 中放的不是最优解或者不合法怎么办？

1.$q$ 中元素个数超过闪咒个数，那么把 $q$ 中最小值去掉并放到 $p$ 中

2.$q$ 中元素个数少于闪咒个数，那么 **如果 $p$ 中元素个数为0，说明当前全部是闪咒，就不需要操作，否则将 $p$ 中最大值去掉并放进 $q$**

3.如果 $q$ 中元素个数等于闪咒的个数但放的不是最优解，即 $p$ 中存在最大值 $A$ 比 $q$ 中最小值 $B$ 大，那么交换 $A$ 和 $B$，重复执行该操作直至 $q$ 中放着最优解为止。

ps:在调整中，可以记 $ans$ 为 $q$ 中所有元素的和，每一次对 $q$ 操作时，ans也相对应操作，就能在单位时间内记录下总和了。

对于每个操作分成以下四类：

1.加一个火 $X$，直接往 $p$ 里面丢，调整见上。

2.加一个闪 $X$，如果之前没有任何闪咒，则不加入 $p$，否则与当前闪咒集合 $s$ 中最小值 $Y$ 进行比较，**如果 当前闪咒比 $Y$ 还要小，说明 $X$ 是所有闪咒中的最小值，此时应当把 $Y$ 加入 $P$ 中（它不是最小值，可能有被翻倍的概率）,而不是加入 $X$。**
操作完后，把 $X$ 加入 $s$，调整见上

3.删一个火 $X$, 在 $p$ 和 $q$ 中找一下，删掉它就行了，调整见上。

4.删一个闪 $X$, 类比2，先在 $s$ 中删去 $X$, 如果删完后没有闪咒了，则没有任何其余操作，否则应当比较当前闪咒集合 $s$ 中的最小值 $Y$ 与 $X$ 的大小：

**A：如果 $Y$ 大于 $X$, 说明删去的 $X$ 本来是最小值，那么 $Y$ 本来是在 $p$ 或 $q$ 中候选的，现在要把 $Y$ 从 $p$ 或 $q$ 中删除**

**B:如果 $Y$ 小于 $X$, 说明原来的最小值不是 $X$， 则 $X$ 本来是在 $p$ 或 $q$ 中候选的，现在要把 $X$ 从 $p$ 或 $q$ 删除**
操作完后，调整见上。

最后，我们就得到了当前利用闪咒翻倍能增加的最多的伤害 $ans$ 。加上本来所有咒语的伤害 $sum$ 就是当前的答案。

**重要的事情说三遍：堆不能删除！堆不能删除！堆不能删除！**

### 3.代码实现
```c++
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void readin(T &x) {
    x = 0;
    T fh = 1;
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') fh = -1;
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x *= fh;
}
template <typename T>
inline void wt(T x) {
    if (x > 9) wt(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void writeln(T x, char c) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    wt(x);
    putchar(c);
}
const int N = 2e5 + 5;
set <int> s, q, p;
int len;
long long ans = 0;
inline void check() { // 调整
    int cnt = q.size();
    set <int> :: iterator ip, iq;
    while(cnt < len && !p.empty()) {
        ip = p.end();
        ip --;
        ans += *ip;
        q.insert(*ip);
        p.erase(ip);
        cnt ++;
    }
    while(cnt > len) {
        iq = q.begin();
        ans -= *iq;
        p.insert(*iq);
        q.erase(iq);
        cnt --;
    }
    while(!q.empty() && !p.empty()) {
        ip = p.end();
        ip --;
        iq = q.begin();
        if (*ip > *iq) {
            int tmp = *ip;
            ans += *ip - *iq;
            p.erase(ip);
            p.insert(*iq);
            q.insert(tmp);
            q.erase(iq);
        }
        else break;
    }

}
int main() {
    int n, opt, num;
    readin(n);
    len = 0;
    long long sum = 0;
    while(n --) {
        readin(opt); readin(num);
        sum += num;
        if (opt == 0) {
            if (num > 0) {
                p.insert(num);
            }
            else {
                num = -num;
                if (p.find(num) != p.end()) p.erase(num);
                else {
                    q.erase(num); 
                    ans -= num;
                }
            }
        }
        else{
            if (num > 0) {
                len ++;
                if (s.size() && num < *s.begin()) {
                    p.insert(*s.begin());
                }
                else if (s.size() && num > *s.begin()){
                    p.insert(num);
                }
                s.insert(num);
            }
            else {
                num = -num;
                len --;
                s.erase(num);
                if (s.size() && *s.begin() > num) {
                    if (p.find(*s.begin()) != p.end()) p.erase(*s.begin());
                    else {
                        ans -= *s.begin();
                        q.erase(*s.begin());
                    }
                }
                else if (s.size()) {
                    if (p.find(num) != p.end()) p.erase(num);
                    else {
                        ans -= num;
                        q.erase(num);
                    } 
                }
            }
        }
        check();
        writeln(ans + sum, '\n');
    }
    return 0;
}
```

---

## 作者：ctq1999 (赞：2)

## 题解简述

有两种符咒，当 $tp_i = 0$ 时，第 $i$ 个符咒能产生 $d_i$ 点攻击力，当 $tp_i = 1$ 时，第 $i$ 个能产生 $d_i$ 点攻击力，并使下一个使用的符咒产生的攻击力翻倍。

每次战斗，每个符咒可以使用一次，而使用顺序是任意的。

有 $n$ 次操作，每次操作你会得到一种符咒，或失去一种符咒。问第 $i$ 次操作后，战斗能产生的攻击力的最大值。

## 思路

参考了 Codeforces 上代码最短的人的代码。（还不是因为没题解/baojin）

首先，不考虑翻倍的效果，当前能产生的攻击力就是当前拥有符咒的 $d$ 的和。

那么剩下的就是考虑如何使用翻倍，使攻击力最大化了。

设 $tot$ 为 $tp=1$ 的符咒的数量。翻倍的肯定是前 $tot$ 个当前拥有的符咒的 $d$ 最大的符咒。因为可能会失去符咒，所以要维护当前拥有符咒的 $d$ 从大到小的前 $tot$ 个。

对于这题，可以使用 set，set 中的元素是默认从小到大排序的，而插入和删除的操作都是 $O(\log n)$。

开三个 set，$\text{fire}$ 存 $tp=0$ 的符咒的 $d$，$\text{lightning}$ 当前翻倍的符咒的 $d$，$\text{remaining}$ 存当前拥有的符咒没翻倍的。

可以发现，$\text{remaining}$ 中任意一个值一定比 $\text{lightning}$ 中任意一个值小或等于。

$tot$ 的值是 $tp=1$ 的符咒的数量，$ans$ 的值是当前能造成的伤害。

对于所有符咒，先直接累计 $d$ 到 $ans$。

对于 $tp=0$ 的符咒的操作，需要直接对 $\text{fire}$ 进行 $insert$ 和 $erase$。

对于所有的符咒的操作，

- 当 $d > 0$ 时，如果比 $\text{remaining}$ 最大的值小，那么直接插入到 $\text{remaining}$ 中，否则插入到 $\text{lightning}$ 中。

- 当 $d < 0$ 时，如果比 $\text{remaining}$ 最大的值小，那么在 $\text{remaining}$ 中删除，否则在 $\text{lightning}$ 中删除。

- 插入或删除需要更新 $ans$ 的值。当 $tp=1$ 时，需要更新 $tot$ 的值。

- 之后需要对 $\text{lightning}$ 进行维护，因为 $\text{lightning}$ 的大小 $size$ 要与 $tot$ 相等。

  - 若 $\text{lightning}$ 的 $size$ 大于 $tot$，那么需要从 $\text{lightning}$ 中 $erase$ 掉前 $size - tot$ 个最小的值，并把这些值插入到 $\text{remaining}$。
  - 若 $\text{lightning}$ 的 $size$ 小于 $tot$，那么要从 $\text{remaining}$ 中 $erase$ 前 $tot - size$ 个最大的值，并把这些值插入到 $\text{lightning}$ 中。维护的同时更新 ans。

那么当前要输出的值就是 $ans$ 了。但注意到最后一个翻倍的符咒一定 $tp=0$，所以输出时要对 $ans$ 进行小修改，即 $ans$ 也加上 `min((lightning.size() ? (fire.size() ? *fire.rbegin() : 0) - *lightning.begin() : 0), 0)`。

## 代码

```cpp
#include<bits/stdc++.h>

#define ll long long
#define y1 caibictq
#define P pair<int, int>
#define fi first
#define se second

using namespace std;

const int MAXN = 200010;
const int MAXM = 100010;
const int mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int n, m, k;
ll tot, cnt, ans;

set<int> fire, lightning, all;

int main() {
	int T;
	scanf("%d", &n);
	for (int i = 1, tp, d; i <= n; i++) {
		scanf("%d%d", &tp, &d);
		if (d > 0) {
			ans += d;
			if (tp) ++tot;
			else fire.insert(d);
			if (all.size() && d < *all.rbegin()) all.insert(d);
			else {
				lightning.insert(d);
				ans += d;
			}
		}
		else {
			ans += d;
			if (tp) --tot;
			else fire.erase(-d);
			if (all.size() && -d <= *all.rbegin()) all.erase(-d);
			else {
				lightning.erase(-d);
				ans += d;
			}
		}
		while (lightning.size() < tot) {
			ans += *all.rbegin();
			lightning.insert(*all.rbegin());
			all.erase(--all.end());
		}
		while (lightning.size() > tot) {
			ans -= *lightning.begin();
			all.insert(*lightning.begin());
			lightning.erase(lightning.begin());
		}
		printf("%lld\n", ans + min((lightning.size() ? (fire.size() ? *fire.rbegin() : 0) - *lightning.begin() : 0), 0));  
	}
	return 0;
}
/*
6
1 5
0 10
1 -5
0 5
1 11
0 -10
*/
```

这时调试程序，大家想用就用吧。

```cpp
		if (fire.size()) printf("set fire: ");
        for (set<int>::iterator it = fire.begin(); it != fire.end(); ++it) {
        	printf("%d ", *it);
		}
		if (fire.size()) printf("\n");
        if (all.size()) printf("set all: ");
        for (set<int>::iterator it = all.begin(); it != all.end(); ++it) {
        	printf("%d ", *it);
		}
		if (all.size()) printf("\n");
        if (lightning.size()) printf("set lightning: ");
        for (set<int>::iterator it = lightning.begin(); it != lightning.end(); ++it) {
        	printf("%d ", *it);
		} 
		if (lightning.size()) printf("\n");
```

---

## 作者：EternalEpic (赞：2)

赛场上这道题没来得及交，赛后来阐述一下思路。

要想结果最优，就要保证雷电要用在大的power法术之前。

我们考虑有k个雷电法术，则有k个法术威力可以翻倍。那么选前k大个肯定是最优的。

但是我们可以知道，第一次的雷电法术是不能强化的，也就是说雷电法术自身不能全部乘二，第一个使用的法术应该是power最小的那个雷电法术。

我使用了FHQTreap来维护k大查询，BinaryIndexedTree来维护序列和，set来维护雷电法术。

但在操作之前，要先把法术离散化，离线来做。

注意细节，就能AC。要开long long。

code：

```cpp
const int Maxn = 2e5 + 5;
int n, typ[Maxn], d[Maxn], b[Maxn], t[Maxn], tot = 0, k = 0;

struct FHQTreap {
	int lson[Maxn], rson[Maxn], data[Maxn];
	int sze[Maxn], rnd[Maxn], tot, seed, root;
	
	FHQTreap(void) {
		Ms(lson, 0), Ms(data, 0);
		Ms(sze, 0), Ms(rnd, 0), root = 0;
		Ms(rson, 0), tot = 0, seed = 1;
	}
	
	inline int _rand(void) { return seed *= 482711; }
	inline void pushup(int pos) { sze[pos] = sze[lson[pos]] + sze[rson[pos]] + 1; }
	inline void split(int pos, int val, int &x, int &y) {
		if (!pos) { x = y = 0; return; }
		if (data[pos] <= val) x = pos, split(rson[pos], val, rson[pos], y);
		else y = pos, split(lson[pos], val, x, lson[pos]); pushup(pos);
	}
	
	inline int merge(int x, int y) {
		if (!x || !y) return x + y;
		if (rnd[x] < rnd[y]) return rson[x] = merge(rson[x], y), pushup(x), x;
		else return lson[y] = merge(x, lson[y]), pushup(y), y;
	}
	
	inline void insert(int val) {
		int x, y, pos = ++tot; sze[pos] = 1;
		data[pos] = val, rnd[pos] = _rand();
		split(root, val, x, y);
		root = merge(merge(x, pos), y);
	}
	
	inline void remove(int val) {
		int x, y, z;
		split(root, val - 1, x, y);
		split(y, val, y, z);
		if (y) y = merge(lson[y], rson[y]);
		root = merge(x, merge(y, z));
	}
	
	inline int query_rank(int val) {
		int x, y, ret;
		split(root, val - 1, x, y);
		ret = sze[x] + 1, root = merge(x, y);
		return ret;
	}
	
	inline int select(int kth) {
		int pos = root; chkmin(kth, sze[root]);
		if (kth == 0) return 0;
		while (kth != sze[lson[pos]] + 1)
			if (kth <= sze[lson[pos]]) pos = lson[pos];
			else kth -= sze[lson[pos]] + 1, pos = rson[pos];
		return data[pos];
	}
	
	inline int pred(int val) { return select(query_rank(val) - 1); }
	inline int succ(int val) { return select(query_rank(val + 1)); }
} treap;

struct BinaryIndexedTree {
	ll c[Maxn];
	inline void update(int pos, int val) { for (; pos <= tot; pos += lowbit(pos)) c[pos] += val; }
//	inline void clear(int pos) { for (; pos <= tot; pos += lowbiot(pos)) c[pos] }
	inline ll query(int pos) { ll ret = 0; for (; pos; pos -= lowbit(pos)) ret += c[pos]; return ret; }
} T;

set <int> sss;

signed main(void) {
//	file("");
	read(n);
	for (int i = 1; i <= n; i++) {
		read(typ[i]), read(d[i]);
		if (d[i] > 0) b[++tot] = d[i], t[i] = 1;
		else t[i] = -1, d[i] = -d[i];
	} sort(b + 1, b + tot + 1); tot = unique(b + 1, b + tot + 1) - (b + 1);
	
	int lmn = 1 << 29;
	for (int i = 1; i <= n; i++) {
		d[i] = lower_bound(b + 1, b + tot + 1, d[i]) - b;
		if (typ[i] == 1) k += t[i];
		if (t[i] == 1) treap.insert(-d[i]), T.update(d[i], b[d[i]]);
		else treap.remove(-d[i]), T.update(d[i], -b[d[i]]);

		if (typ[i] == 1) {
			if (t[i] == 1) {
				if (sss.size() && d[i] < *sss.begin()) {
					treap.insert(-(*sss.begin()));
					T.update(*sss.begin(), b[*sss.begin()]);
				}
				sss.insert(d[i]);
			}
			else {
				if (d[i] == *sss.begin()) T.update(d[i], b[d[i]]);
				sss.erase(d[i]);
			}
		}
		
		if (sss.size()) {
			treap.remove(-(*sss.begin()));
			ll x = T.query(*sss.begin()) - T.query((*sss.begin()) - 1);
			T.update(*sss.begin(), -x);
		} else {
			writeln(T.query(tot)); continue;
		}
		
		int tmp = -treap.select(k); if (tmp == 0) { writeln(b[*sss.begin()] + T.query(tot)); continue; }
		ll ret = T.query(tmp - 1) + (T.query(tot) - T.query(tmp - 1)) * 2 + (ll)b[*sss.begin()];
		writeln(ret);
	}
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}
```


---

## 作者：ifffer_2137 (赞：0)

### 题意
维护一个初始为零的集合，每次加入或删除一个元素。一个元素有种类和权值，其中一种类型可以使排在它后一个的元素权值乘 $2$，另一种无效果。每次修改后求将集合内元素排序后的最大权值总和。
### 分析
一眼的贪心是尽量把前 $k$ 大的权值翻倍，$k$ 是有翻倍效果的元素个数。然后你发现如果前 $k$ 大全是有翻倍效果的就排不了了，只能舍弃第 $k$ 大去取第 $k+1$ 大。现在你考虑维护这个东西。

你先想办法搞出第 $k$ 大的值，并且动态维护集合内前 $k$ 大之和。然后判断一下普通元素最大值是否小于第 $k$ 大，如果是的话就把翻倍元素中的最小值扔掉换成普通元素最大值。两种类型元素的 $\min$ 或 $\max$ 用个 `set` 就好了。

然而动态前 $k$ 大不好搞，考虑离线下来离散化，然后弄个值域 sgt，单点修改区间求和再带一个求第 $k$ 大，直接朴素 sgt 上二分，这样就 $O(n\log n)$ 了。

注意一些实现上的细节，比如某种类型元素 `set` 为空。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
int n;
pii a[maxn];
int t[maxn],tot;
set<int> s[2];
struct Segment_Tree{
	int sm[maxn*4],cnt[maxn*4];
	void pushup(int o){
		sm[o]=sm[o*2]+sm[o*2+1];
		cnt[o]=cnt[o*2]+cnt[o*2+1];
	}
	void update(int o,int l,int r,int x,int k){
		if(l==r){
			sm[o]+=k*t[x];
			cnt[o]+=k;
			return;
		}
		int m=(l+r)>>1;
		if(x<=m) update(o*2,l,m,x,k);
		else update(o*2+1,m+1,r,x,k);
		pushup(o);
	}
	int binary(int o,int l,int r,int k){
		if(l==r) return l;
		int m=(l+r)>>1;
		if(cnt[o*2+1]>=k) return binary(o*2+1,m+1,r,k);
		return binary(o*2,l,m,k-cnt[o*2+1]);
	}
	int query(int o,int l,int r,int x,int y){
		if(x<=l&&r<=y) return sm[o];
		int m=(l+r)>>1,res=0;
		if(x<=m) res+=query(o*2,l,m,x,y);
		if(y>m) res+=query(o*2+1,m+1,r,x,y);
		return res;
	}
}seg;
signed main(){
	cin.tie(0),cout.tie(0);
	n=read();
	for(int i=1;i<=n;i++){
		a[i].fir=read(),a[i].sec=read();
		if(a[i].sec>0) t[++tot]=a[i].sec;
	}
	sort(t+1,t+tot+1);tot=unique(t+1,t+tot+1)-t-1;
	for(int i=1;i<=n;i++){
		if(a[i].sec>0) a[i].sec=lower_bound(t+1,t+tot+1,a[i].sec)-t;
		else a[i].sec=-(lower_bound(t+1,t+tot+1,-a[i].sec)-t);
	}
	for(int i=1;i<=n;i++){
		int op=(a[i].sec>0);
		a[i].sec=abs(a[i].sec);
		if(op) seg.update(1,1,tot,a[i].sec,1),s[a[i].fir].insert(a[i].sec);
		else seg.update(1,1,tot,a[i].sec,-1),s[a[i].fir].erase(a[i].sec);
		if(!s[1].size()){
			cout<<seg.sm[1]<<"\n";
			continue;
		}
		if(!s[0].size()){
			cout<<seg.sm[1]*2-t[*s[1].begin()]<<"\n";
			continue;
		}
		int pos=seg.binary(1,1,tot,s[1].size()),ans=seg.query(1,1,tot,pos,tot)*2+seg.query(1,1,tot,1,pos-1);
		if((*s[0].rbegin())<pos) ans+=t[*s[0].rbegin()]-t[*s[1].begin()];
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：sansesantongshun (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1398E)

~~该题解使用分块思想，平衡树大佬请飘过~~

首先要理解题意，咒语分火之咒和电之咒，其中电之咒给后面的咒语攻击力翻倍，而火之咒不能翻倍。

根据贪心思想，假设有 $x$ 个电之咒，则这些电之咒应该给初始攻击力前 $x$ 大的咒语翻倍，则最终攻击力等于初始攻击力总和加上攻击力前 $x$ 大的咒语的攻击力的总和。

对于总攻击力很好维护，而前 $x$ 大攻击力就需要使用数据结构维护，大多数人用的都是平衡树，~~而我太菜了不会平衡树~~，而且数据范围较小，所以我使用值域分块维护。由于值域很大，需要离散化后离线处理。

当然还有个细节，就是如果有电之咒，根据贪心思想，攻击力最小的电之咒应牺牲自己而不能让自己翻倍，所以还需要维护攻击力最小的电之咒，如果攻击力前 $x$ 大的咒语包括攻击力最小的电之咒，答案等于初始攻击力总和加上攻击力前 $x+1$ 大的咒语的攻击力的总和减去最小的电之咒攻击力。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,nm,a[200005][2],lsh[200005],b[200005],l[450],r[450],d[450],num=0,x,minn,dd[450],bl;
long long e[450],sum=0,ans;
bool c[200005],cc[200005];
/*
n：初始攻击力种数 m：询问数 nm：块长
a：存储询问 b：块的编号 l：块的左端点 r：块的右端点
c[x]：是否存在攻击力为x的咒语
d[x]：攻击力在第x块内的咒语的总数
cc[x]：是否存在攻击力为x的电之咒
dd[x]：攻击力在第x块内的电之咒的总数
e[x]：攻击力在第x块内的咒语的总攻击力
num：电之咒数量 sum：咒语总攻击力
minn：电之咒攻击力最小值 x：第k大攻击力
*/
long long kth(int k)//攻击力前k大咒语攻击力和
{
	long long result=0;
	for (bl=b[n];bl>0;--bl)
	{
		if (k-d[bl]<=0)
		break;
		k-=d[bl];
		result+=e[bl];
	}
	if (bl)
	for (int i=r[bl];i>=l[bl];--i)
	{
		if (k-c[i]<=0)
		{
			x=i;//记录一下第k大攻击力
			result+=lsh[i];
			break;
		}
		k-=c[i];
		if (c[i])
		result+=lsh[i];
	}
	return result;
}
int main()
{
	cin>>m;
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d",&a[i][0],&a[i][1]);
		if (a[i][1]>0)
		lsh[++lsh[0]]=a[i][1];
	}
	sort(lsh+1,lsh+lsh[0]+1);
	n=unique(lsh+1,lsh+lsh[0]+1)-lsh-1;//离散化
	nm=round(sqrt(n));
	for (int i=1;i<=n;++i)//值域分块
	{
		b[i]=(i-1)/nm+1;
		if (l[b[i]]==0)
		l[b[i]]=i;
		r[b[i]]=i;
	}
	for (int i=1;i<=m;++i)
	if (a[i][1]>0)
	a[i][1]=lower_bound(lsh+1,lsh+n+1,a[i][1])-lsh;
	else
	a[i][1]=lsh-lower_bound(lsh+1,lsh+n+1,-a[i][1]);
	for (int i=1;i<=m;++i)
	{
		if (a[i][1]>0)//学习
		{
			if (c[a[i][1]])//学过的话
			{
				if (!cc[a[i][1]] && a[i][0])//火之咒变电之咒
				{
					++num;
					cc[a[i][1]]=1;
					++dd[b[a[i][1]]];
				}
				else if (cc[a[i][1]] && a[i][0]==0)//电之咒变火之咒
				{
					--num;
					cc[a[i][1]]=0;
					--dd[b[a[i][1]]];
				}
			}
			else//没学过
			{
				c[a[i][1]]=1;
				++d[b[a[i][1]]];
				e[b[a[i][1]]]+=lsh[a[i][1]];
				if (a[i][0])//要特判电之咒
				{
					cc[a[i][1]]=1;
					++dd[b[a[i][1]]];
					++num;
				}
				sum+=lsh[a[i][1]];
			}
		}
		else//忘记
		{
			c[-a[i][1]]=0;
			--d[b[-a[i][1]]];
			e[b[-a[i][1]]]-=lsh[-a[i][1]];
			sum-=lsh[-a[i][1]];
			if (a[i][0])//还是要特判电之咒
			{
				--num;
				cc[-a[i][1]]=0;
				--dd[b[-a[i][1]]];
			}
		}
		if (num==0)//没有电之咒，不能翻倍
		cout<<sum<<'\n';
		else
		{
			ans=kth(num);//前k大攻击力
			for (bl=1;bl<=b[n];++bl)
			if (dd[bl])
			break;
			if (bl<=b[n])
			for (int i=l[bl];i<=r[bl];++i)
			if (cc[i])
			{
				minn=i;
				break;
			}//最小电之咒攻击力
			if (x>minn)//不包括
			cout<<sum+ans<<'\n';
			else//包括，要刨去
			cout<<sum+kth(num+1)-lsh[minn]<<'\n';
		}
	}
}
```

---

## 作者：XiangyuHu (赞：0)

先考虑没有修改怎么做。

记现在有 $x$ 次闪电，显然将最大的 $x$ 次伤害翻倍更优。记最大的 $x$ 次伤害中，有 $y$ 次闪电，$z$ 次火焰。

1. $z>0$，此时把 $y$ 次闪电放到火焰前面，将剩下的 $z$ 次闪电放到没有翻倍的法术前面，即可达到最优
2. $z=0$，此时不可能所有闪电都翻倍，将最小的闪电伤害替换成最大的火焰伤害翻倍最优

加入修改后，问题转化为找序列第 $k$ 大值，并求前缀和。可以使用线段树二分，也可以在树状数组上倍增，码量较小。

代码（树状数组倍增）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
typedef pair<int, int> pii;
pii op[200200];
set<int> st;
map<int, int> mp;
int cntcnt;
int kkk;
struct Fuck {
    int tree[200200];
    int lowbit(int x) {
        return x & (-x);
    }
    void add(int x, int y) {
        for (int i = x; i <= n; i += lowbit(i)) tree[i] += y;
    }
    int query(int x) {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i)) ans += tree[i];
        return ans;
    }
} a, b, c;
signed main() {
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%lld%lld", &x, &y);
        op[i] = make_pair(x, y);
        if (y > 0) st.insert(y);
    }
    int k = 0;
    for (auto it = st.begin(); it != st.end(); it++) {
        mp[*it] = ++k;
    }
    int cc = 0;
    for (int i = 1; i <= n; i++) {
        int x = op[i].first, y = op[i].second, z;
        if (y > 0) {
            z = mp[y];
            a.add(z, 1);
            b.add(z, y);
            if (x) c.add(z, 1), cntcnt++;
            cc++;
        } else {
            z = mp[-y];
            a.add(z, -1);
            b.add(z, y);
            if (x) c.add(z, -1), cntcnt--;
            cc--;
        }
        int pp = 0, sm = 0, minu = 0;
        int tmp = cc - cntcnt;
        for (int i = 20; i >= 0; i--) {
            if ((pp | (1 << i)) <= n && (sm + a.tree[pp | (1 << i)]) <= tmp)
                sm += a.tree[pp | (1 << i)], pp |= (1 << i);
        }
        if (!c.query(pp) && cntcnt) {
            minu = b.query(pp + 1) - b.query(pp);
            tmp--;
            pp = sm = 0;
            for (int i = 20; i >= 0; i--) {
                if ((pp | (1 << i)) <= n && (sm + a.tree[pp | (1 << i)]) <= tmp)
                    sm += a.tree[pp | (1 << i)], pp |= (1 << i);
            }
        }
        printf("%lld\n", b.query(n) * 2 - b.query(pp) - minu);
    }
    return 0;
}
```

---

## 作者：Theophania (赞：0)

题目中的操作可以分为以下四种：

1. 学会一个伤害为 $d$ 的火焰法术
2. 学会一个伤害为 $d$ 的闪电法术
3. 忘记一个伤害为 $d$ 的火焰法术
4. 忘记一个伤害为 $d$ 的闪电法术

施放闪电法术后的下一个法术伤害加倍，需要求出每次操作后能够打出的最大伤害。

显然，我们要尽量把伤害高的法术放在闪电法术后面打出。假设我们当前拥有 $k$ 个闪电法术，如果伤害最高的 $k$ 个法术全部都是闪电法术，那么这 $k$ 个法术中就有一个不能被翻倍，而剩下的火焰法术中有一个可以被翻倍，为了使伤害最大化就选择翻倍伤害最高的火焰法术来代替伤害最低的闪电法术；如果伤害最高的 $k$ 个法术不完全是闪电法术，那么这 $k$ 个法术的伤害都可以被翻倍。

策略想起来比较简单，下面考虑如何实现。

首先我们需要记录闪电法术的个数 $k$，并使用一个支持插入删除的数据结构来维护所有法术中伤害最高的 $k$ 个法术，还需要判断这 $k$ 个法术是否都是闪电法术。一个非常直接的想法是使用四颗平衡树，分别维护所有火焰法术、所有闪电法术；伤害最高的 $k$ 个法术以及剩下的伤害较低的法术，用四个 `set` 即可。

每次进行操作时，根据操作类型使维护伤害最高的 $k$ 个法术的 `set` 大小始终等于闪电法术的个数。同时更新所有法术伤害之和 $sum$ 与伤害最高的 $k$ 个法术伤害之和 $suml$。通过比较伤害最低的闪电法术与伤害最高的火焰法术的值，判断伤害最高的 $k$ 个法术是否都是闪电法术，计算当前能打出的最高伤害。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
inline void read(T &x)
{
    T data = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        data = (data << 3) + (data << 1) + ch - '0';
        ch = getchar();
    }
    x = f * data;
}

inline int get_last(const set<int> &s)
{
    if (s.empty())
        return 0;
    auto it = s.end();
    --it;
    return *it;
}

set<int> big, small, fire, lightning;

signed main()
{
    int t;
    read(t);
    ll sum = 0, suml = 0;
    while (t--)
    {
        int op, d;
        read(op), read(d);
        sum += d;
        if (op)
        {
            if (d > 0)
            {
                lightning.insert(d);
                if (small.empty())
                {
                    big.insert(d);
                    suml += d;
                }
                else
                {
                    int p = get_last(small);
                    if (d > p)
                    {
                        big.insert(d);
                        suml += d;
                    }
                    else
                    {
                        small.erase(p);
                        big.insert(p);
                        small.insert(d);
                        suml += p;
                    }
                }
            }
            else
            {
                d = -d;
                lightning.erase(d);
                int p = *big.begin();
                if (d >= p)
                {
                    big.erase(d);
                    suml -= d;
                }
                else
                {
                    small.erase(d);
                    big.erase(p);
                    small.insert(p);
                    suml -= p;
                }
            }
        }
        else
        {
            if (d > 0)
            {
                fire.insert(d);
                if (big.empty())
                    small.insert(d);
                else
                {
                    int p = *big.begin();
                    if (d > p)
                    {
                        big.erase(p);
                        small.insert(p);
                        big.insert(d);
                        suml += d - p;
                    }
                    else
                        small.insert(d);
                }
            }
            else
            {
                d = -d;
                fire.erase(d);
                if (big.empty())
                    small.erase(d);
                else
                {
                    int p = *big.begin();
                    if (d >= p)
                    {
                        int q = get_last(small);
                        big.erase(d);
                        small.erase(q);
                        big.insert(q);
                        suml += q - d;
                    }
                    else
                        small.erase(d);
                }
            }
        }
        if (fire.empty() || (!lightning.empty() && get_last(fire) < *lightning.begin()))
            cout << sum + suml - *big.begin() + get_last(small) << '\n';
        else
            cout << sum + suml << '\n';
    }
    return 0;
}
```



---

