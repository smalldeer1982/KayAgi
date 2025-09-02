# Tournament

## 题目描述

Recently a tournament in $ k $ kinds of sports has begun in Berland. Vasya wants to make money on the bets.

The scheme of the tournament is very mysterious and not fully disclosed. Competitions are held back to back, each of them involves two sportsmen who have not left the tournament yet. Each match can be held in any of the $ k $ kinds of sport. Loser leaves the tournament. The last remaining sportsman becomes the winner. Apart of this, the scheme can be arbitrary, it is not disclosed in advance.

Vasya knows powers of sportsmen in each kind of sport. He believes that the sportsmen with higher power always wins.

The tournament is held every year, and each year one new participant joins it. In the first tournament, only one sportsman has participated, in the second there were two sportsmen, and so on. Vasya has been watching the tournament for the last $ n $ years. Help him to find the number of possible winners for each of the $ n $ tournaments.

## 说明/提示

In the first sample:

In the first tournament there is only one sportsman, and he is the winner.

In the second tournament, there are two sportsmen, and everyone can defeat another, depending on kind of sports.

In the third tournament, the third sportsman in the strongest in both kinds of sports, so he is the winner regardless of the scheme.

## 样例 #1

### 输入

```
3 2
1 5
5 1
10 10
```

### 输出

```
1
2
1
```

## 样例 #2

### 输入

```
3 2
2 2
3 3
1 10
```

### 输出

```
1
1
3
```

## 样例 #3

### 输入

```
3 2
2 3
1 1
3 2
```

### 输出

```
1
1
2
```

# 题解

## 作者：fighter (赞：6)

## 思路

​       又是一道建模思维题。我们考虑两个选手之间的关系，如果一个选手能在某一项运动中战胜对手，那么就从他自身向对手连一条有向边。这样显然会出现很多环，于是可以大力缩点，将整张图缩成一个DAG（实际实现中会变为一条链）。那么显然入度为零的环中包含的点数即为最后可能成为冠军的人数。

## 实现细节

​       由于题目要求动态插入点，那么tarjan就不再适合了~~（虽然我并不清楚有没有大佬能用tarjan切掉）~~，于是我们换一种方法建图。由于一位选手不可能战胜对手，当且仅当所有运动能力均弱于对方。那么我们就以这个条件来判断，如果满足这个条件就连单向边，否则就合并到一个连通块中。于是我们可以选择set作为容器，把上述判断的条件重载成小于号，在set中用find查找是否有与当前选手可以合并的，并进行合并操作。合并后，我们的节点（即一个环）记录的是环中每项运动所有选手中的最大值和最小值，这样可以方便地进行环与环之间的比较。

​	将所有点插入后，答案即为set中的最后一个元素的大小，因为我们重载了小于号，所以最后一个节点都是“大于”之前的点的，在缩点后的图中一定是入度为零。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, k;

struct node{
    int sz;
    int mx[15], mn[15];
    node(){
        memset(mx, 0, sizeof(mx));
        memset(mn, 0x3f, sizeof(mn));
    }
    friend bool operator <(node a, node b){
        for(int i = 1; i <= k; i++){
            if(a.mx[i] > b.mn[i]){
                return false;
            }
        }
        return true;
    }
};

set<node> s;
set<node>::iterator it;

int main()
{
    cin >> n >> k;
    node t;
    for(int i = 1; i <= n; i++){
        t.sz = 1;
        for(int j = 1; j <= k; j++){
            scanf("%d", &t.mn[j]);
            t.mx[j] = t.mn[j];
        }
        while((it = s.find(t)) != s.end()){
            t.sz += it->sz;
            for(int j = 1; j <= k; j++){
                t.mn[j] = min(t.mn[j], it->mn[j]);
                t.mx[j] = max(t.mx[j], it->mx[j]);
            }
            s.erase(it);
        }
        s.insert(t);
        printf("%d\n", (--s.end())->sz);
    }
    
    return 0;
}
```



---

## 作者：老莽莽穿一切 (赞：3)

[更好的阅读体验](https://www.cnblogs.com/LaoMang-no-blog/p/16304953.html)

---

[**你谷 link**](https://www.luogu.com.cn/problem/CF878C)

[**CF link**](https://codeforces.com/problemset/problem/914/F)

这个题也是非常神奇了。

CF 评分 2700，看起来很难搞的样子，其实难度并没有想象中那么大，主要是要利用 C++ 的优势——STL。

废话不多说，直接讲做法，考虑我们先定义一个说法，如果两个人 $A$ 和 $B$ 满足 $A$ 任何运动都强于 $B$，则称 $A$ **吊打** $B$。

想想什么时候**只有**一个人能夺冠，那就是他吊打所有人的时候，而如果一个人可能夺冠，条件不需要这么苛刻，只要他要能间接打败所有人，比如石头剪刀布，三个对决的时候次序决定了冠军。

考虑加入我们已经维护好一个冠军集合，即这个集合里的人都可能成为冠军，那么一个人如果想成为冠军，那么他只需要将这个集合中的某人从某个方面打败就好了，这样的话先执行之前这个人获得冠军的对局，然后再让新人打败他就好了，但如果他想要让别人无法成为冠军，就必须吊打这个集合里的所有人。

同时需要注意如果新人能成为冠军，而之前本来无法成为冠军的人可以打败这个新人，那么这个人也可以成为冠军，同理能打败这个人的人也能成为冠军。

维护起来其实不麻烦，我们考虑模仿冠军集合维护很多集合，每个集合表示一群人，这群人单独取出来每个人都能成为冠军，接下来就是新人加入时对这么多集合进行维护。

先要减少集合维护的信息，我们发现我们只要记录每个集合每个运动最强者和最弱者的能力值就好了，用来判断能不能打败和被打败，然后再记录人数就好了，同样，如果一个集合 $A$ 每个运动的最强值都弱于另一个集合 $B$ 该运动的最小值，我们称集合 $A$ **吊打** $B$，如果 $A$ 和 $B$ 都不会互相吊打，那么这两个集合显然是可以合并的，而冠军集合就是能吊打其他所有集合的那个集合。

接下来就是要维护这么多集合的关系，发现 C++ 的 STL 里有个东西叫做 `set`，我们可以方便地使用这个东西，首先定义比较运算符，出于形象我们定义大于号，我们用吊打定义大于号，这样的话 $set$ 内置也会把等号定义好，就是满足 $A\not>B\land B\not>A$，这样的话自然地就形成了两个集合可以合并的条件，所以我们可以将新插入的人一个人看做一个集合，每次用 `set` 的 `find` 函数找出 `set` 中与新人可以合并的集合，就可以直接维护合并，然后取出最大的集合输出大小就好了。

[代码](https://codeforces.com/contest/878/submission/158257559)实现上难度不大，因为 STL 给我们带来了很大的便利。

---

## 作者：daniEl_lElE (赞：2)

考虑动态维护哪些点在同一个强连通分量中，给每个点一个编号，使得两个点编号 $a=b$ 表示 $a,b$ 可以互相吊打，两个点编号 $a>b$ 表示 $a$ 可以吊打 $b$ 而 $b$ 不能吊打 $a$。

新加入一个点时，首先按第一种项目的顺序给个初始编号 $t$，找到能吊打的编号最大的点 $p$ 和能吊打他的编号最小的点 $q$。如果 $q\leq p$，那么可以将所有 $p\sim q$ 之间的点缩到一起，不妨令他们都是 $q$。如果 $q>p$，那么不会影响原图，只需要添加该点即可。

最后每次输出编号最大值的个数即可。

需要使用 $k$ 个线段树以及一车操作维护，总复杂度 $O(kn\log n)$。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
struct node{
	int a[12];
}b[100005];
int lsh[100005];
struct sgt{
	int minv[200005],maxv[200005],lzt[200005],f[200005],maxnum[200005];
	void pushdown(int i){
		if(lzt[i]!=-1){
			if(f[i*2]){
				minv[i*2]=maxv[i*2]=lzt[i*2]=lzt[i];
				maxnum[i*2]=f[i*2];
			}
			if(f[i*2+1]){
				minv[i*2+1]=maxv[i*2+1]=lzt[i*2+1]=lzt[i];
				maxnum[i*2+1]=f[i*2+1];
			}
			lzt[i]=-1;
		}
	}
	void pushup(int i){
		f[i]=f[i*2]+f[i*2+1];
		minv[i]=min(minv[i*2],minv[i*2+1]);
		maxv[i]=max(maxv[i*2],maxv[i*2+1]);
		maxnum[i]=0;
		if(maxv[i*2]==maxv[i]) maxnum[i]+=maxnum[i*2];
		if(maxv[i*2+1]==maxv[i]) maxnum[i]+=maxnum[i*2+1];
	}
	void build(int i,int l,int r){
		lzt[i]=-1,minv[i]=1e9,maxv[i]=0;
		f[i]=maxnum[i]=0;
		if(l==r){
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		pushup(i);
	}
	void change(int i,int l,int r,int pos,int cg){
		if(l==r){
			maxv[i]=minv[i]=cg;
			f[i]=maxnum[i]=1;
			return ;
		}
		pushdown(i);
		if(pos<=mid) change(i*2,l,mid,pos,cg);
		else change(i*2+1,mid+1,r,pos,cg);
		pushup(i);
	}
	void modify(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			minv[i]=maxv[i]=lzt[i]=cg;
			maxnum[i]=f[i];
			return ;
		}
		pushdown(i);
		if(ql<=mid) modify(i*2,l,mid,ql,qr,cg);
		if(qr>mid) modify(i*2+1,mid+1,r,ql,qr,cg);
		pushup(i);
	}
	int qrymin(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return minv[i];
		if(ql>r||qr<l) return 1e9;
		pushdown(i);
		return min(qrymin(i*2,l,mid,ql,qr),qrymin(i*2+1,mid+1,r,ql,qr));
	}
	int qrymax(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return maxv[i];
		if(ql>r||qr<l) return 0;
		pushdown(i);
		return max(qrymax(i*2,l,mid,ql,qr),qrymax(i*2+1,mid+1,r,ql,qr));
	}
	int qfirst(int i,int l,int r,int val){
		if(l==r) return l;
		pushdown(i);
		if(maxv[i*2]>=val) return qfirst(i*2,l,mid,val);
		return qfirst(i*2+1,mid+1,r,val);
	}
	int qlast(int i,int l,int r,int val){
		if(l==r) return l;
		pushdown(i);
		if(minv[i*2+1]<=val) return qlast(i*2+1,mid+1,r,val);
		return qlast(i*2,l,mid,val);
	}
}tree[12];
signed main(){
	int n,k; cin>>n>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++) cin>>b[i].a[j];
	}
	for(int i=1;i<=k;i++){
		tree[i].build(1,1,n);
		for(int j=1;j<=n;j++) lsh[j]=b[j].a[i];
		sort(lsh+1,lsh+n+1);
		for(int j=1;j<=n;j++) b[j].a[i]=lower_bound(lsh+1,lsh+n+1,b[j].a[i])-lsh;
	}
	for(int i=1;i<=n;i++){
		int minv=b[i].a[1],maxv=b[i].a[1];
		for(int j=1;j<=k;j++) minv=min(minv,tree[j].qrymin(1,1,n,b[i].a[j],n)),maxv=max(maxv,tree[j].qrymax(1,1,n,1,b[i].a[j]));
		for(int j=1;j<=k;j++) tree[j].change(1,1,n,b[i].a[j],minv);
		if(minv!=maxv){
			for(int j=1;j<=k;j++){
				int lpos=tree[j].qfirst(1,1,n,minv);
				int rpos=tree[j].qlast(1,1,n,maxv);
				tree[j].modify(1,1,n,lpos,rpos,minv);
			}
		}
		cout<<tree[1].maxnum[1]<<"\n";
	}
	return 0;
}
```

---

## 作者：wky32768 (赞：2)

考虑把两个人的比赛连边，如果A可能赢B且B可能赢A，则他们可以互相到达，用强连通分量的方法进行缩点，那么最后整张图一定是一个链(想一想，为什么)，那么第一个强连通分量的大小就是答案。

不过对于强连通分量的处理，这题有一个非常精妙的方法，就是用set，把输赢变成重载运算符，那么如果如果A可能赢B且B可能赢A，则A==B，可以直接用find函数。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
    int data=0,w=1;
    char ch=0;
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') {w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {data=data*10+ch-'0';ch=getchar();}
    return data*w;
}
void write(int x) {
    if(x>=10) write(x/10);
    register char ch=x%10+'0';	
    putchar(ch);
}
int n,m,ans,k;
struct node {
    int sz,mx[12],mn[12];
    friend bool operator < (node a,node b) {
        for(int i=1;i<=k;i++)
            if(a.mx[i]>b.mn[i]) return 0;
        return 1;
    }	
} sxd;
set <node> q;
signed main() {
    cin>>n>>k;
    for(int i=1;i<=n;i++) {
        sxd.sz=1;
        for(int j=1;j<=k;j++) {sxd.mn[j]=sxd.mx[j]=read();}
        set <node> :: iterator it=q.find(sxd);
        while(it!=q.end()) {
            sxd.sz+=(*it).sz;
            for(int j=1;j<=k;j++) {
                sxd.mx[j]=max(sxd.mx[j],(*it).mx[j]);
                sxd.mn[j]=min(sxd.mn[j],(*it).mn[j]);
            }
            q.erase(it);
            it=q.find(sxd);
        }
        q.insert(sxd);
        write((*q.rbegin()).sz);
        puts("");
    }
    return 0;
}
```

---

