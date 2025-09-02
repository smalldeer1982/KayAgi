# Inna and Sequence

## 题目描述

Dima's spent much time thinking what present to give to Inna and gave her an empty sequence $ w $ . Now they want to fill sequence $ w $ with numbers zero and one. For that, they decided to play an amusing game.

Before the game begins, Dima chooses $ m $ integers $ a_{1},a_{2},...,a_{m} $ $ (1<=a_{1}<a_{2}<...<a_{m}) $ . Then Inna and Dima start playing, that is, adding numbers to sequence $ w $ . Each new number they choose is added to the end of the sequence. At some moments of time Dima feels that the game is going to end too soon (and he wants to play with Inna as long as possible), so he hits a table hard with his fist. At that the $ a_{1} $ -th, $ a_{2} $ -th, $ a_{3} $ -th, $ ... $ , $ a_{k} $ -th numbers from the beginning simultaneously fall out of the sequence (the sequence gets $ k $ numbers less). Here $ k $ is such maximum number that value $ a_{k} $ doesn't exceed the current length of the sequence. If number $ a_{1} $ is larger than the current length of $ w $ , then nothing falls out of the sequence.

You are given the chronological sequence of events in the game. Each event is either adding a number to the end of sequence $ w $ or Dima's hit on the table. Calculate the sequence $ w $ after all these events happen.

## 样例 #1

### 输入

```
10 3
1 3 6
-1
1
1
0
0
-1
0
1
-1
1
```

### 输出

```
011
```

## 样例 #2

### 输入

```
2 1
1
1
-1
```

### 输出

```
Poor stack!
```

# 题解

## 作者：如我西沉 (赞：3)

序列最多有10万个1或0.   删除操作最多进行10万次。

于是用线段树来储存。每个节点，存这个点还剩下多少个点没有删除，这样就可以删除指定的第k 个数。

给序列加元素最多进行n次，每次复杂度 O（log2(n)） ，最多O(n*log2(n));

删除元素最多进行 n 次，每次复杂度 O（log2(n)） ，最多 O(n*log2(n));

所以总复杂度O(n*log2(n));

代码如下：
```cpp
#include <iostream>  
#include <cstdio>  
#include <cmath>  
#include <cstring> 
#define lson rt<<1
#define rson rt<<1|1 
#define maxn 1000010  
using namespace std;  
int N,n,m,now,op;  
int a[maxn];  
int index[maxn<<2];  
int value[maxn];   
inline void pushup(int rt){  
    index[rt]=index[lson]+index[rson];  
}  
inline void update(int x,int c,int l,int r,int rt){
    if(l==r){  
        value[l]=c;  
        index[rt]=1;  
        ++now;  
        return;  
    }  
    int m=(l+r)>>1;  
    if(x<=m) update(x,c,l,m,lson);  
    else update(x,c,m+1,r,rson);  
    pushup(rt);  
}  
inline void del(int x,int l,int r,int rt){ 
    if(l==r){  
        index[rt]=0;  
        return;  
    }  
    int m=(l+r)>>1;  
    if(x<=index[lson]) del(x,l,m,lson);  
    else del(x-index[lson],m+1,r,rson);  
    pushup(rt);  
}  
int main()  
{   
    while(~scanf("%d%d",&n,&m)){  
        now=1;
		N=1;
		while(N <n+2) N<<=1;  
    	memset(index,0,sizeof(index));    
        for(int i=0;i<m;++i) scanf("%d",&a[i]);  
        for(int i=0;i<n;++i) {  
            scanf("%d",&op);  
            if(~op)  
                update(now,op,1,N,1);            
            else
                for(int j=0;j<m && a[j]-j<=index[1];j++)
                    del(a[j]-j,1,N,1);                   
        }  
        if(index[1])  
        {
            for(int i=0;i<now;++i)  
        		if(index[N+i])  
            		printf("%d",value[i+1]); 
		}
        else 
            printf("Poor stack!\n");
    }  
	return 0;  
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
题意简述：给定一个序列 $w$ 包括 $m$ 个数据。你需要进行 $n$ 次操作，每次操作会在下面的三种方法中任取一种：
- 在数列末尾添加数据 $1$。
- 在数列末尾添加数据 $0$。
- 删除位置为 $a_i\left(i\leq n\right)$ 的数据。

求 $n$ 次操作后的序列的样子。

添加数据，修改数据，显然的线段树查询，添加与修改，所以思路很明显。这里提供两种思路。
## 分析。
首先提供一种线段树的思路。这个也是比较容易想到的思路。我们考虑到最多只有 $n$ 次操作会添加 $0$ 或者 $1$ 所以最后面的 $01$ 串的长度最多就是 $n$ 个。那么我们不妨用一个变量进行统计，表示当前在后面插入一个数的话应该插入到哪个位置。然后在此过程中记录插入的数有多少个，此时判断它是不是小于等于 $n$ 即可。

删除操作，相当于直接进行查询，然后删除该叶子。直接用最朴素的递归求解即可。具体来说，如果某个叶子的下标大于要删除的叶子的下标，则往左儿子递归，反之往右儿子，最后递归到叶子节点是直接令其为 $0$ 即可。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int n,m,opt,a[1000005];
int flag;
int t[2000005],val[1000005],tot=1;
void push_num(int root){
    t[root]=t[root<<1]+t[root<<1|1];
}
void add(int num,int x,int l,int r,int root){
    if(l==r){
        t[root]=1;
        val[l]=x;
        return;
    }
    int mid=l+r>>1;
    if(num<=mid){
        add(num,x,l,mid,root<<1);
    }
    else add(num,x,mid+1,r,root<<1|1);
    push_num(root);
}
void delete_tree(int num,int l,int r,int root){
    if(l==r){
        t[root]=0;
        return;
    }
    int mid=l+r>>1;
    if(t[root<<1]>=num){
        delete_tree(num,l,mid,root<<1);
    }
	else{
        delete_tree(num-t[root<<1],mid+1,r,root<<1|1);
    }
    push_num(root);
}
void print(int l,int r,int root){
    if(l==r){
    	cout<<val[l];
        return;
    }
    int mid=l+r>>1;
    if(t[root<<1]){
        print(l,mid,root<<1);
    }
    if(t[root<<1|1]){
        print(mid+1,r,root<<1|1);
    }
}
int main(){
    cin>>n>>m;
    //int n2=n;
    for(int i=0;i<m;i++){
    	cin>>a[i];
    }
    for (int j=0;j<n;j++){
    	cin>>opt;
        if(opt>=0){
            add(tot++,opt,1,n+2,1);
        }
		else{
            for(int i=0;i<m;i++){
                if(a[i]-i>t[1]){
                    break;
                }
                delete_tree(a[i]-i,1,n+2,1);
            }
        }
    }
    if(t[1]){
        print(1,n+2,1);
    }
	else{
        cout<<"Poor stack!\n";
    }
    return 0;
}
```
另一种思路就是二分和树状数组。我们要删除一个数，不妨直接去找二分找没删除前的位置，这样我们可以直接进行二分查找，这应该是一个很经典的思路。

代码如下，仅供参考：
```
#include<iostream>
#include<vector>
using namespace std;
int n,m,opt,a[1000005];
int ans[1000005],vised[1000005],t[1000005];
int tot;
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
void add(int id,int num){
    while(id<=1e6){
	    t[id]+=num;
		id+=id&-id;
	}
}
vector<int> v;
int empty(int id){
    int size_=0;
    while(id){
    	//cout<<id<<" "<<size_<<"\n";
	    size_+=t[id];
		id-=id&-id;
	}
    return size_;
}
int cheak(int num){
    int l=1,r=1000000;
    //int res;
    int mid=l+r>>1;
    while(l<r){
    	//int mid=l+r>>1;
    	//res=mid;
        if(empty(mid)>=num){
		    r=mid;
		}
        else l=mid+1;
        mid=l+r>>1;
        //cout<<mid<<" yep!!\n";
    } 
    return mid;
}
int main(){
    for(int i=1;i<=1000000;i++){
	    add(i,1);
	}
    read(n);
    read(m);
    for(int i=0;i<m;i++){
		read(a[i]);
	}
    for(int j=0;j<n;j++){
        cin>>opt;
        if(opt>=0){
        	ans[++tot]=opt;
		}
        else{
            v.clear();
            for(int i=0;i<m;i++){
                int ch=cheak(a[i]);
                if(ch>tot){
				    break;
				}
				//cout<<ch<<" yexo!\n";
                v.push_back(ch);
            }
            for(int i=0;i<v.size();i++){
                vised[v[i]]=1;
                add(v[i],-1);
            }
        }
    }
    if(empty(tot)!=0){
    	for (int i=1;i<=tot;i++){
    		if(!vised[i]){
    			write(ans[i]);
			}
		}
	}
    else cout<<"Poor stack!\n";
    return 0; 
}
```
## 后记。
最后提醒打击本题的数据范围一定要开够啊，因为经测试数据点 $8$ 的 $n$ 和 $m$ 就超过了 $10^5$。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：MagicalGirl_0d00 (赞：0)

### 鲜花
开局想 `set` 去了，然后发现不好弄时人机都快写完了。

最后慢了 5 min 惜败人机。

### sol
$n$ 为询问次数， $m$ 为 $a$ 数组的长度。

注意到每个元素只会被删去一次。

然后我们每次遍历一个 $a$ 数组中的元素至少可以带走一个元素，删不掉了就 `break`。

那么我们暴力删除的复杂度就是 $O(n)$ 而不是 $O(nm)$ 的。

输出答案直接写个 dfs 遍历线段树就行了，复杂度和空间都是 $O(n\log n)$ 的。
### code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,m,t,k,a[1000001],b[1000001],tot,sum[1000001],f[55][55][55];
multiset<int> s;
struct dcz{
	int siz,sum;
}tr[4000001];
void insert(int wh,int sum,int l,int r,int root){
	if(l==r){
		tr[root].sum=sum;
		tr[root].siz=1;
		return;
	}
	int mid=l+r>>1;
	if(wh<=mid) insert(wh,sum,l,mid,root<<1);
	if(wh>mid) insert(wh,sum,mid+1,r,root<<1|1);
	tr[root].siz=tr[root<<1].siz+tr[root<<1|1].siz;
}
void erase(int wh,int l,int r,int root){
	if(l==r){
		tr[root].siz=0;
		tr[root].sum=-1;
		return;
	}
	int mid=l+r>>1;
	if(tr[root<<1].siz>=wh) erase(wh,l,mid,root<<1);
	else erase(wh-tr[root<<1].siz,mid+1,r,root<<1|1);
	tr[root].siz=tr[root<<1].siz+tr[root<<1|1].siz;
}
void dfs(int l,int r,int root){
	if(l==r){
		cout<<tr[root].sum;
		return;
	}
	int mid=l+r>>1;
	if(tr[root<<1].siz) dfs(l,mid,root<<1);
	if(tr[root<<1|1].siz) dfs(mid+1,r,root<<1|1);
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		if(b[i]==1||b[i]==0) insert(++tot,b[i],1,n,1);
		else{
			for(int j=1;j<=m;j++){
				if(tr[1].siz<a[j]-j+1) break;
				erase(a[j]-j+1,1,n,1);
			}
		}
	}
	if(!tr[1].siz) cout<<"Poor stack!";
	else dfs(1,n,1);
	return 0;
}
```

---

## 作者：GoldenCreeper (赞：0)

### CF374D Inna and Sequence 题解

题目传送门：[CF374D Inna and Sequence](https://www.luogu.com.cn/problem/CF374D)

---

感觉这个翻译的有点难以理解
~~（可能是我语文不太好）~~，所以我来简述一下题意。

有一个空序列 $w$ 和一个长为 $m$ 的序列 $a$，有 $n$ 次操作，每次操作可以：

- 向序列 $m$ 中添加一个 $0$ 或 $1$；
- 把序列中第 $a_1,a_2,a_3,\dots,a_m$ 项元素删除，如果 $a_m$ 大于当前序列 $w$ 的长度，则无事发生。

求 $n$ 次操作后的序列 $w$。

---



因为有末尾添加和按照排名删除，考虑使用平衡树来维护。

~~而且题解中全是线段树，写出来就可以抢首发！~~

这里给一种 FHQ-Treap 的写法，按照排名分裂即可，基本都是板子内容，就不给注释了。

```cpp
#include <bits/stdc++.h>
// #define int long long
using namespace std;

int const N = 1e6 + 10;
mt19937 rd(114514);
struct FHQ{
    int ls, rs, sz, key, val;
} a[N];

int root, t1, t2, t3, cnt;

int xj(int v){
    a[++cnt] = {0, 0, 1, (int)rd(), v};
    return cnt;
}

void pushup(int x){
    a[x].sz = a[a[x].ls].sz + a[a[x].rs].sz + 1;
}

void split(int u, int v, int &x, int &y){ //ok
    if (!u){
        x = y = 0;
        return;
    }
    int tmp = a[a[u].ls].sz + 1;
    if (tmp == v){
        x = u;
        y = a[u].rs;
        a[u].rs = 0;
    } else if (tmp > v){
        y = u;
        split(a[u].ls, v, x, a[u].ls);
    }
    else{
        x = u;
        split(a[u].rs, v - tmp, a[u].rs, y);
    }
    pushup(u);
}

int merge(int x, int y){ //ok
    if (!x || !y) return x + y;
    if (a[x].key > a[y].key){
        a[x].rs = merge(a[x].rs, y);
        pushup(x);
        return x;
    } else{
        a[y].ls = merge(x, a[y].ls);
        pushup(y);
        return y;
    }
}

void insert(int v){
    root = merge(root, xj(v));
}

int find(int x){ 
    split(root, x, t1, t2);
    split(t1, x - 1, t1, t3);
    int ret = a[t3].val;
    root = merge(merge(t1, t3), t2);
    return ret;
}

int n, m, s[N], op, x, siz;

void mian(){
    cin >> n >> m;
    for (int i = 1;i <= m;++i) cin >> s[i];
    for (int i = 1;i <= n;++i){
        scanf("%d", &op);
        if (op == -1){
            for (int j = m;j >= 1;--j){
                if (a[root].sz >= s[j]){
                    split(root, s[j], t1, t2);
                    split(t1, s[j] - 1, t1, t3);
                    root = merge(t1, t2);
                }
            }
        }
        else insert(op);
    }
    if (a[root].sz == 0) cout << "Poor stack!" << endl;
    else for (int j = 1;j <= a[root].sz;++j) cout << find(j);
}
signed main() {
    // freopen("in.in", "r", stdin);
    // freopen("cpp.out", "w", stdout); 
    // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    while(T--) mian();
    // cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
    return 0;
}
```

然后就成功 TLE 了。~~这下知道为什么题解了没有平衡树了。~~

FHQ-Treap 的常数还是太大了，本蒟蒻也不太会优化，所以我们老老实实的去写线段树吧。

---

### 正解：线段树

用线段树维护也很简单。只需要维护区间内存在点的个数即可。具体的讲，删除一个排名为 $x$ 的元素时，把他所有所在区间的存在点的个数 $-1$ 即可。添加一个元素时，把他放在树的最后面，然后把所含该节点的所有区间 $+1$ 即可。

代码：
```cpp
/*
 @Author: CreeperOI
 @Problem: Luogu_CF_374_D
 @Start Time: 2024-04-01 20:52
 @Finish Time: 2024-04-02 08:32
*/
#include <bits/stdc++.h>
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

// const int mod = 1e9 + 7;

// ------------------------- templates above -------------------------

int const N = 1e6 + 10;

int n, m, a[N], s[4 * N], v[N];

void pushup(int x){
    s[x] = s[ls] + s[rs];
}

void add(int x, int l, int r, int qx, int k){
    if (l == r){
        v[l] = qx;
        s[x] = 1;
        return;
    }
    if (k <= mid) add(ls, l, mid, qx, k);
    else add(rs, mid + 1, r, qx, k);
    pushup(x);
}

void earse(int x, int l, int r, int k){
    if (l == r){
        s[x] = 0;
        return;
    }
    if (k <= s[ls]) earse(ls, l, mid, k);
    else earse(rs, mid + 1, r, k - s[ls]);
    pushup(x);
}

void mian(){
    cin >> n >> m;
    int l = 1, siz = 0;
    while (l < n + 2) l <<= 1; // 最小的大于 n 的 2 的幂次的数，用来维护线段树，因为这样可以把每个叶节点都卡到最后一排，方便输出
    for (int i = 1; i <= m; ++i) scanf("%d", &a[i]);
    for (int j = 1; j <= n; ++j){
        int op;
        cin >> op;
        if (op == -1){
            for (int i = 1;i <= m;++i) // 正着循环会快一点
                if (s[1] >= a[i] - i + 1) // a[i] - i + 1 是删掉前 i - 1 个元素后的线下标
                    earse(1, 1, l, a[i] - i + 1);
                else break;
        }
        else add(1, 1, l, op, ++siz);
    }
    if (s[1] == 0){
        cout << "Poor stack!";
        return;
    }
    for (int i = 1; i <= siz; ++i)
        if (s[l + i - 1] == 1) printf("%d", v[i]);
}
signed main(){
    // freopen("cpp.in", "r", stdin);
    // freopen("cpp.out", "w", stdout);
    // ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--)
        mian();
    // cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
    return 0;
}
```

---

