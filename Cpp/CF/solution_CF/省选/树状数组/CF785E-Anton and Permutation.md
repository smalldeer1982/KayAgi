# Anton and Permutation

## 题目描述

Anton likes permutations, especially he likes to permute their elements. Note that a permutation of $ n $ elements is a sequence of numbers $ {a_{1},a_{2},...,a_{n}} $ , in which every number from $ 1 $ to $ n $ appears exactly once.

One day Anton got a new permutation and started to play with it. He does the following operation $ q $ times: he takes two elements of the permutation and swaps these elements. After each operation he asks his friend Vanya, how many inversions there are in the new permutation. The number of inversions in a permutation is the number of distinct pairs $ (i,j) $ such that $ 1<=i<j<=n $ and $ a_{i}>a_{j} $ .

Vanya is tired of answering Anton's silly questions. So he asked you to write a program that would answer these questions instead of him.

Initially Anton's permutation was $ {1,2,...,n} $ , that is $ a_{i}=i $ for all $ i $ such that $ 1<=i<=n $ .

## 说明/提示

Consider the first sample.

After the first Anton's operation the permutation will be $ {1,2,3,5,4} $ . There is only one inversion in it: $ (4,5) $ .

After the second Anton's operation the permutation will be $ {1,5,3,2,4} $ . There are four inversions: $ (2,3) $ , $ (2,4) $ , $ (2,5) $ and $ (3,4) $ .

After the third Anton's operation the permutation will be $ {1,4,3,2,5} $ . There are three inversions: $ (2,3) $ , $ (2,4) $ and $ (3,4) $ .

After the fourth Anton's operation the permutation doesn't change, so there are still three inversions.

## 样例 #1

### 输入

```
5 4
4 5
2 4
2 5
2 2
```

### 输出

```
1
4
3
3
```

## 样例 #2

### 输入

```
2 1
2 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6 7
1 4
3 5
2 3
3 3
3 6
2 1
5 1
```

### 输出

```
5
6
7
7
10
11
8
```

# 题解

## 作者：lhm_ (赞：14)

考虑用分块解决这个题，一次交换对当前逆序对个数的影响是，加上两倍的在区间$[l+1,r-1]$中比$a_r$小的元素个数，减去两倍的在区间$[l+1,r-1]$中比$a_l$小的元素个数，再根据$a_l$和$a_r$的大小关系决定这两个位置对答案的影响。

可以用$vector$来维护每个块内元素有序，然后就可以支持询问了。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 200010
#define lower(a,x) lower_bound(ve[a].begin(),ve[a].end(),x)
#define upper(a,x) upper_bound(ve[a].begin(),ve[a].end(),x)
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,k,S;
int bel[maxn],a[maxn];
ll ans;
vector<int> ve[maxn];
void change(int l,int r)
{
    if(bel[l]!=bel[r])
    {
        ve[bel[l]].erase(lower(bel[l],a[l])),ve[bel[l]].insert(upper(bel[l],a[r]),a[r]);
        ve[bel[r]].erase(lower(bel[r],a[r])),ve[bel[r]].insert(upper(bel[r],a[l]),a[l]);
    }
    swap(a[l],a[r]);
}
int query(int l,int r,int v)
{
    if(l>r) return 0;
    int cnt=0;
    for(int i=l;i<=min(S*bel[l],r);++i) cnt+=(a[i]<v);
    if(bel[l]==bel[r]) return cnt;
    for(int i=S*(bel[r]-1)+1;i<=r;++i) cnt+=(a[i]<v);
    for(int i=bel[l]+1;i<=bel[r]-1;++i) cnt+=lower(i,v)-ve[i].begin();
    return cnt;
}
int main()
{
    read(n),read(k),S=sqrt(n);
    for(int i=1;i<=n;++i) a[i]=i,bel[i]=(i-1)/S+1,ve[bel[i]].push_back(a[i]);
    while(k--)
    {
        int l,r;
        read(l),read(r);
        if(l>r) swap(l,r);
        if(l==r)
        {
            printf("%lld\n",ans);
            continue;
        }
        ans+=2*(query(l+1,r-1,a[r])-query(l+1,r-1,a[l]));
        if(a[l]<a[r]) ans++;
        else ans--;
        change(l,r),printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：素质玩家孙1超 (赞：5)

这个题目怎么只有树套权值线段树的题解，我来一发线段树套平衡树的题解。

然而树套树的复杂度严格 $\log^2$ 却跑不过分块的 $\log \times \sqrt{\ \ \ }$，而且还差点 TLE 了，不愧是树套树。

---

题意：每次可以交换两个数，求每次操作后的逆序对数。

---

假设这两个数的位置为 $x_1,x_2$ ($x1 \leq x2$ )。

我们只要计算在 $(x_1,x_2)$ 中 $x_1$ 与 $x_2$ 移动对于总的逆序对有多少贡献。其实就是动态查询 $x$ 在某个区间里的排名。

显然一次交换之后：

$$ans=ans+2*query(x_1+1,x_2-1,val[x_1])-2*query(x_1+1,x_2-1,val[x2])+val[x_2]>val[x_1]?1:-1$$

其中 $query(l,r,X)$ 表示在区间 $[l,r]$ 中有多少个值大于 $X$。

---

以上东西都好理解也容易推，但是平衡树我不想打，那就用`pb_ds` 好了。

具体的所有的操作可以自己搜索，这里只用到了以下函数

```cpp
a.insert(x)//a中插入x
a.erase(x)//a中删除x
a.join(b) //把b并入a
a.size()//元素个数
a.order_of_key(x)//x的排名
a.lower_bound(x)//大于等于x的第一个数
```

其中要注意的是`tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>` 

这个东西是会自动去重的，所以删除和修改操作有时候要注意细节。

更加细节的东西比如关于树套树的具体实现可以看我的代码，

这个线段树套`pb_ds`的好处就是好写，大概只是普通线段树的码量，并且 `pb_ds` 的效率在普通平衡树的模板里是可以和离线的树状数组相差不多的，只是线段树常数有点大，所以虽然时间复杂度正确，但实际速度没有分块优秀。

---

代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define ls (root<<1)
#define rs (root<<1|1)
#define mid (l+r>>1)
#define int long long 
using namespace std;
using namespace __gnu_pbds;
const int Maxn=2e5+5;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>tr[Maxn*4],tmp;
inline int R()
{
	char c;int sign=1,res;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;
}
int num[Maxn],pos[Maxn];
void build(int root,int l,int r)
{
	if(l==r)
	{
		num[l]=root;
		tr[root].insert(l);
		return;
	}
	build(ls,l,mid);
	build(rs,mid+1,r);
	tmp=tr[ls];//.jion会把tmp清空 
	tr[root].join(tmp);
	tmp=tr[rs];
	tr[root].join(tmp);
}
void modify(int root,int l,int r,int pos,int pre,int val)
{
	if(pos>r||pos<l) return;
	if(*tr[root].lower_bound(val)!=val){tr[root].erase(pre);tr[root].insert(val);}
	//上面这句表示若区间包含了pre和val，则不操作 
	if(l==r) return;
	modify(ls,l,mid,pos,pre,val);
	modify(rs,mid+1,r,pos,pre,val);
}
int query(int root,int l,int r,int z,int y,int val)//找在[z,y]中有多少元素比val大 
{
	if(l>y||r<z) return 0;
	if(l>=z&&r<=y) return tr[root].size()-tr[root].order_of_key(val);
	return query(ls,l,mid,z,y,val)+query(rs,mid+1,r,z,y,val);
}
int n,m;
signed main()
{
	n=R();m=R();
	build(1,1,n);
	for(int i=1;i<=n;i++) pos[i]=i;//pos[x]表示x当时的位置 
	int x,y,X,Y,xxx,yyy,ans=0;
	while(m--)
	{
		xxx=R();yyy=R(); 
		if(xxx==yyy){printf("%lld\n",ans);continue;}
		x=pos[xxx];y=pos[yyy];
		if(x>y) swap(x,y);
		X=*tr[num[x]].begin();//num[i]表示i在线段树的那个叶子 
		Y=*tr[num[y]].begin();
		if(x!=y-1)ans-=2*query(1,1,n,x+1,y-1,Y);
		if(x!=y-1)ans+=2*query(1,1,n,x+1,y-1,X);
		ans+=X<Y?1:-1;
		modify(1,1,n,x,X,Y);
		modify(1,1,n,y,Y,X);
		printf("%lld\n",ans);
		swap(pos[xxx],pos[yyy]);
	}
}
```

---

## 作者：Owen_codeisking (赞：5)

## 分块大法好！！！！！

考虑用块中在 $vector$ 中二分，边角暴力，$swap$ 两个元素就二分然后 $erase,insert$ 一下，时间复杂度为 $O(n\sqrt{n}\log n)$

个人经验：以下两种分块写法是不等价的

写法一：

```cpp
	for(int i=1;i<=blo;i++){
		L[i]=(i-1)*blo+1,R[i]=i*blo;
		for(int j=L[i];j<=R[i];j++) pos[j]=i,v[i].push_back(j);
	}
	if(blo*blo!=n){
		int i=blo+1;L[i]=(i-1)*blo+1,R[i]=n;
		for(int j=L[i];j<=R[i];j++) pos[j]=i,v[i].push_back(j);
	}
    for(int i=1;i<=n;i++) a[i]=i;
```

写法二：

```cpp
	for(int i=1;i<=blo;i++){
		L[i]=(i-1)*blo+1,R[i]=i*blo;
		for(int j=L[i];j<=R[i];j++) v[i].push_back(j);
	}
	if(blo*blo!=n){
		int i=blo+1;L[i]=(i-1)*blo+1,R[i]=n;
		for(int j=L[i];j<=R[i];j++) v[i].push_back(j);
	}
    for(int i=1;i<=n;i++) pos[i]=(i-1)/blo+1,a[i]=i;
```

注意：写法二的 $pos[i]$ 是错的，因为最后一块的大小可以超过 $\sqrt{n}$ 的！！！

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=200000+10;
const int inf=0x3f3f3f3f;
int n,m,a[maxn],pos[maxn],L[maxn],R[maxn],cnt[maxn],blo;ll ans;

vector<int> v[500];

inline int read(){
    register int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}

void update(int l,int r){
    int p=pos[l],q=pos[r];
    if(p < q){
        v[p].erase(lower_bound(v[p].begin(),v[p].end(),a[l]));
        v[p].insert(upper_bound(v[p].begin(),v[p].end(),a[r]),a[r]);
        v[q].erase(lower_bound(v[q].begin(),v[q].end(),a[r])); 
        v[q].insert(upper_bound(v[q].begin(),v[q].end(),a[l]),a[l]);
    }
    swap(a[l],a[r]);
}
ll query(int l,int r,int k){
    if(l > r) return 0;
    int p=pos[l],q=pos[r];ll ans=0,num;
    if(p+1>=q){
        for(int i=l;i<=r;i++)
            if(a[i]<k) ans++;
    }
    else {
        for(int i=l;i<=R[p];i++)
            if(a[i]<k) ans++;
        for(int i=L[q];i<=r;i++)
            if(a[i]<k) ans++;
        for(int i=p+1;i<=q-1;i++){
            num=upper_bound(v[i].begin(),v[i].end(),k)-v[i].begin();
            ans+=num;
        }
    }
    return ans;
}

int main()
{
    n=read(),m=read();blo=sqrt(n);
    for(int i=1;i<=blo;i++){
        L[i]=(i-1)*blo+1,R[i]=i*blo;
        for(int j=L[i];j<=R[i];j++) pos[j]=i,v[i].push_back(j);
    }
    if(blo*blo!=n){
        int i=blo+1;L[i]=(i-1)*blo+1,R[i]=n;
        for(int j=L[i];j<=R[i];j++) pos[j]=i,v[i].push_back(j);
    }
    for(int i=1;i<=n;i++) a[i]=i;
    int l,r;
    for(int i=1;i<=m;i++){
        l=read(),r=read();
        if(l>r) swap(l,r);
        if(l==r) printf("%I64d\n",ans);
        else {
            ans+=2*query(l+1,r-1,a[r])-(r-l-1);
            ans+=(r-l-1)-2*query(l+1,r-1,a[l]);
            ans+=(a[l]<a[r])?1:(a[l]>a[r])?-1:0;
            update(l,r);
            printf("%I64d\n",ans);
        }
    }
    return 0;
}
```

---

## 作者：winter2020 (赞：4)

目前全谷最优解。

本题的题解里没有严格 $\sqrt{n}$ 的，故我这里严格 $\sqrt{n}$ 的就吊打了全谷（bushi

写严格 $\sqrt{n}$ 的原因竟然是 ~~rp太差~~ 常数太大，我带 $\log n$ 过不去。

### 开始正题

一开始的思路是：分 $\sqrt{n}$ 块，每次对于两个数分别算一下贡献，换过去再算贡献，于是他寄了。

考虑怎样降 $\log$，决定再套一个值域分块。

- 我先维护好每个块内 1 到 $\sqrt{n}$ 一共出现了几次，$\sqrt{n} + 1$ 到 $2*\sqrt{n}$ 等等。

- 然后维护每个块这个值的前缀和。

对于交换，就暴力 -1 和 +1，时间复杂度明显 $\sqrt{n}$。

对于查询，先找到你要询问的那些整块，也就是询问的那个数的快，把这个答案 $O(1)$ 返回去。但这样会有个小问题：你可能把某些比当前数小的数，但在这个数的位置的前面也算进去了。

为了搞这个东西，可以记每个数在数组中出现的位置 $pos$，$pos_i$ 表示 $i$ 这个数在哪里出现的。枚举 $\sqrt{n}$ 判就可以了。

~~这样说你可能根本不知道怎么写，~~ 所以给代码，里面有更详尽的注释。

### 完整代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;
int n, q;
int block, len;
int _a[N], a[N], st[N], ed[N], mp[N];
LL now;
int sum[505][505], pos[N];

int check1(int i, int x) { //在当前位置前面，有多少比当前数大的
    return ed[i] - st[i] + 1 - sum[i][mp[x]];
}

int check2(int i, int x) { //在当前位置后面，有多少比当前数小的
    return sum[i][mp[x]];
}

//可以看出，上面两个，一个少算了一些东西（check1），另一个多算了一些东西（就是跟当前数在一个值域块里，但比当前数大的数）

int query(int j) {
    int x = mp[j], ans = 0;
    for (int i = 1; i < x; i ++ ) ans += check1(i, _a[j]);
    for (int i = _a[j]; mp[i] == mp[_a[j]]; i++)
        if(pos[i] < st[x])
            ans ++; //处理check1里少算的，与当前数一个值域块的东西但比当前数大的数
            
    for (int i = st[x]; i < j; i ++ )
        if (_a[i] > _a[j]) ans ++;
    for (int i = j + 1; i <= ed[x]; i ++ )
        if (_a[i] < _a[j]) ans ++;
        
    for (int i = x + 1; i <= block; i ++ ) ans += check2(i, _a[j]);
    for (int i = _a[j]; mp[i] == mp[_a[j]]; i++)
        if(pos[i] > ed[x])//同理，处理多出来的数，这里是多算了比当前数大的数，上面是少算了。
            ans -- ;
    return ans;
}

//这块可能略微难懂，建议多看看两个check是怎么算的

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i ++ ) _a[i] = a[i] = i;
    len = sqrt(n);
    for (int i = 1, j = len + 1; i <= n; i ++, j ++ ) {
        if (j == len + 1) {
            block ++;
            st[block] = i;
            ed[block - 1] = i - 1;
            j = 1;
        }
        if (i == n)
            ed[block] = n;
        mp[i] = block;
    }
    for(int i = 1; i <= n; i++)
        sum[mp[i]][mp[_a[i]]]++;
    for(int i = 1; i <= block; i++)
        for(int j = 1; j <= block; j++)
            sum[i][j] += sum[i][j - 1];
    for(int i = 1; i <= n; i++)
        pos[i] = i;
    while (q -- ) {
        int x, y, k = 0;
        cin >> x >> y;
        if (x > y) swap(x, y);
        if (_a[x] == _a[y]) {
            cout << now << endl;
            continue;
        }
        int aa = query(x), bb = query(y);
        if (_a[x] < _a[y]) k = 1;
        for(int i = mp[_a[x]]; i <= block; i++)
            sum[mp[x]][i]--;
        for(int i = mp[_a[y]]; i <= block; i++)
            sum[mp[y]][i]--;
        swap(_a[x], _a[y]);
        for(int i = mp[_a[x]]; i <= block; i++)
            sum[mp[x]][i]++;
        for(int i = mp[_a[y]]; i <= block; i++)
            sum[mp[y]][i]++;//暴力加加减减
        swap(pos[_a[x]], pos[_a[y]]);
        int a_ = query(x), b_ = query(y);
        int sum = a_ + b_ - k, num = aa + bb - !k; //这里的k是为了处理这两个数的逆序对关系
        now = (long long)now - num + sum;
        cout << now << endl;
    }
    return 0;
}
```

---

## 作者：ykuouzf (赞：4)

对于每次交换，易知只会对 $l$ 到 $r$ 这一区间内的逆序对个数造成影响，不妨设区间内小于 $a_l$ 的数的个数为 $x_1$, 大于 $a_l$ 的为 $y_1$, 小于 $a_r$ 的为 $x_2$, 大于 $a_r$ 的为 $y_2$，如此我们可得到以下柿子：

$x_1 + y_1 = r - l + 1$

$x_2 + y_2 = r - l + 1$

于是，有，

$ans = (y_1 - x_1) + (x_2 - y_2)$

$= ((r - l + 1 - x_1) - x1) + (x_2 - (r - l + 1 - x_2)) $

$= 2 * (x_2 - x_1)$

由上述可得，我们仅需要求出 $l$ 到 $r$ 区间内小于 $a_l$ 和小于 $a_r$ 的数的个数即可，具体用分块实现，对两端的散块暴力处理，中间部分完整的块用权值块排好序（提前预处理），通过二分处理答案，别忘了在每次交换过后对两个权值块重新排个序

### Code:

```
#include <bits/stdc++.h>

#define int long long 

const int N = 2e5 + 10;

int n, T, block, cnt, ans;
int a[N], pre[N], pos[N], l[N], r[N]; 

int ask(int x, int k) { //二分 
	int L = l[x], R = r[x], mid, sum = l[x] - 1;
	while (L <= R) {
		mid = L + ((R - L) >> 1);
		if (pre[mid] < k) { L = mid + 1; sum = mid; }
		else { R = mid - 1; }
	} return sum - (l[x] - 1);
}

int query(int L, int R, int x, int sum = 0) { //查询L到R之间小于x的个数 
	if (L > R) { return 0; }
	if (pos[L] == pos[R]) {
		for (int i = L; i <= R; i++) { if (a[i] < x) { sum++; } }
		return sum;
	}
	for (int i = L; i <= r[pos[L]]; i++) { if (a[i] < x) { sum++; } }
	for (int i = l[pos[R]]; i <= R; i++) { if (a[i] < x) { sum++; } }
	for (int i = pos[L] + 1; i <= pos[R] - 1; i++) { sum += ask(i, x); }
	return sum;
}

signed main() {
	std::ios::sync_with_stdio(0);
	std::cin >> n >> T;
	block = std::sqrt(n);
	cnt = n / block + (n % block != 0); 
	for (int i = 1; i <= n; i++) {
		a[i] = pre[i] = i;
		pos[i] = (i - 1) / block + 1;
	}
	for (int i = 1; i <= cnt; i++) {
		l[i] = (i - 1) * block + 1;
		r[i] = i * block;
	} r[cnt] = n;
	for (; T; --T) {
		int x, y; std::cin >> x >> y;
		if (x > y) { std::swap(x, y); }
		ans += 2 * (query(x + 1, y - 1, a[y]) - query(x + 1, y - 1, a[x])); //修改 
		if (a[x] < a[y]) { ans++; }
		if (a[x] > a[y]) { ans--; } //对两个端点特判 
		std::swap(a[x], a[y]); 
		for (int i = l[pos[x]]; i <= r[pos[x]]; i++) { pre[i] = a[i]; }
		for (int i = l[pos[y]]; i <= r[pos[y]]; i++) { pre[i] = a[i]; }
		std::sort(pre + l[pos[x]], pre + r[pos[x]] + 1);
		std::sort(pre + l[pos[y]], pre + r[pos[y]] + 1); //更新权值块 
		std::cout << ans << "\n";
	}
	return 0;
}
```

### The end.

---

## 作者：MCAdam (赞：4)

[题目](https://www.luogu.com.cn/problem/CF785E)

怎么能没有CDQ分治的做法呢？交换操作可以看成：$2$次插入，$2$次删除

记五元组$<a,b,c,type,id>$分别表示：

时间、位置、值、插入/删除/、对应询问的编号

对于每一个元素，它能贡献的逆序对的数量：

前面（位置）比它大的数的个数$+$后面比它小的个数，很显然这就是一个三维偏序的问题（时间上也要满足偏序）

首先把第一维时间排序（原本就有序了）

然后对位置进行CDQ分治，对右半部分计算左半部分：位置在其左边值大，位置在其右边值小的方案

注意：左右两半部分在位置上是独立有序的，在计算时还要看另一边是否满足位置上的限制

这样就能得到当前区间，每一个操作对应的逆序对，如果是插入，对应答案就加上，如果是删除，就剪掉

注意上面的这一个过程，其实只是单独考虑每个操作对答案的影响，最后还要把答案求个前缀和

```cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int N=2e5+10,M=5e4+10;
int n;
int val[N],t[N];
ll ans[M];
struct node
{
	int a,b,c;
	int type,id;
}v[N+4*M],w[N+4*M];
inline int lowbit(int x)
{
	return x&(-x);
}
inline void change(int x,int c)
{
	for(int i=x;i<=n;i+=lowbit(i))
		t[i]+=c;
}
inline int query(int x)
{
	int res=0;
	for(int i=x;i>=1;i-=lowbit(i))
		res+=t[i];
	return res;
}
inline void CDQ(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)/2,p,q;
	CDQ(l,mid),CDQ(mid+1,r);
	p=l,q=mid+1;
	while(q<=r)//计算左边位置小值大 
	{
		while(p<=mid&&v[p].b<=v[q].b) change(v[p].c,v[p].type),p++;
		ans[v[q].id]+=v[q].type*(query(n)-query(v[q].c)),q++;
	}
	for(int i=l;i<p;i++) change(v[i].c,-v[i].type);
	p=mid,q=r;
	while(q>mid)//计算左边位置大值小 
	{
		while(p>=l&&v[p].b>=v[q].b) change(v[p].c,v[p].type),p--;
		ans[v[q].id]+=v[q].type*query(v[q].c-1),q--;
	}
	for(int i=mid;i>p;i--) change(v[i].c,-v[i].type);
	p=l,q=mid+1;
	for(int i=l;i<=r;i++)//归并排序
	{
		if((p<=mid&&v[p].b<=v[q].b)||q>r) w[i]=v[p++];
		else w[i]=v[q++];
	} 
	for(int i=l;i<=r;i++) v[i]=w[i];
}
int main()
{
	int m,tot=0,a,b;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		val[i]=i,v[++tot]=(node){tot,i,i,1,0};
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		v[++tot]=(node){tot,a,val[a],-1,i};
		v[++tot]=(node){tot,b,val[b],-1,i};
		v[++tot]=(node){tot,a,val[b],1,i};
		v[++tot]=(node){tot,b,val[a],1,i};
		swap(val[a],val[b]);
	}
	CDQ(1,tot);
	for(int i=1;i<=m;i++)
		ans[i]+=ans[i-1];
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```




---

## 作者：GKxx (赞：4)

这么经典的题目怎么少得了树套树？

树状数组套权值线段树

可以很方便地查询一段区间中值域在某区间内的数有多少个。

一开始答案是0

每次交换$a[l]$和$a[r](l<r)$的时候，就把答案减去$[l+1,r-1]$中比$a[l]$小的数的个数，加上$[l+1,r-1]$中比$a[l]$大的数的个数，减去$[l+1,r-1]$中比$a[r]$大的数的个数，加上$[l+1,r-1]$中比$a[r]$小的数的个数，然后再单独判断一下$a[l]$和$a[r]$的大小关系即可。

空间要开两个$\log$，但是又要小心不要MLE，好烦。

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T &x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Args>
inline void read(T &x, Args &...args) {
    read(x); read(args...);
}
template <typename T> void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); puts(""); }
template <typename T> inline bool chkmin(T &x, const T &y) { return y < x ? x = y, 1 : 0; }
template <typename T> inline bool chkmax(T &x, const T &y) { return x < y ? x = y, 1 : 0; }

typedef long long LL;
const int maxn = 2e5 + 7;
int lc[maxn << 7], rc[maxn << 7], sum[maxn << 7], tot;
int root[maxn], a[maxn];
int n, m;
LL ans = 0;

void insert(int &o, int l, int r, int pos, int val) {
    if (!o) o = ++tot;
    sum[o] += val;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) insert(lc[o], l, mid, pos, val);
    else insert(rc[o], mid + 1, r, pos, val);
}
int query(int o, int lb, int rb, int l, int r) {
    if (!o || l > rb || r < lb) return 0;
    if (l <= lb && r >= rb) return sum[o];
    int mid = (lb + rb) >> 1;
    return query(lc[o], lb, mid, l, r) + query(rc[o], mid + 1, rb, l, r);
}
void insert(int x, int y, int v) {
    for (; x <= n; x += x & -x)
        insert(root[x], 1, n, y, v);
}
int query(int lb, int rb, int l, int r) {
    if (lb > rb || l > r) return 0;
    int ans = 0;
    for (; rb; rb -= rb & -rb) ans += query(root[rb], 1, n, l, r);
    for (--lb; lb; lb -= lb & -lb) ans -= query(root[lb], 1, n, l, r);
    return ans;
}

int main() {
    read(n, m);
    for (int i = 1; i <= n; ++i) insert(i, a[i] = i, 1);
    for (int i = 1, l, r; i <= m; ++i) {
        read(l, r); if (l == r) { writeln(ans); continue; }
        if (l > r) std::swap(l, r);
        ans -= query(l + 1, r - 1, 1, a[l] - 1);
        ans += query(l + 1, r - 1, a[l] + 1, n);
        ans -= query(l + 1, r - 1, a[r] + 1, n);
        ans += query(l + 1, r - 1, 1, a[r] - 1);
        a[l] < a[r] ? ++ans : --ans;
        insert(l, a[l], -1);
        insert(l, a[r], 1);
        insert(r, a[r], -1);
        insert(r, a[l], 1);
        std::swap(a[l], a[r]);
        writeln(ans);
    }
    return 0;
}
```

---

## 作者：KiDDOwithTopTree (赞：3)

题目在这：[传送门](https://www.luogu.com.cn/problem/CF785E)。

### 做法：树状数组套主席树（树状数组套动态开点值域线段树）。

题目写得很清楚了，感觉并没有什么需要解释的。

开始思考思路：

首先，看到求逆序对、交换两个数，我想到的便是[这题](https://www.luogu.com.cn/problem/P3157)。

当 x 交换到 y 处后，区间 $[1,x-1]$ 与 $a_x$ 的逆序对**不会改变**，区间 $[y+1,n]$ 与 $a_x$ 的逆序对也**不会改变**，但是区间 $[x+1,y-1]$ 与 $a_x$ 的逆序对**会改变**，因为进行交换 x 和 y 后这段区间原来与 $a_x$ 逆序对变成了顺序对，原来与 $a_x$ 的顺序对变成了逆序对。而 y 则同理。

当然，我们还没有判断 x 与 y 的关系：如果交换前 $a_x>a_y$，即原来 $a_x$ 与 $a_y$ 是逆序对，那么交换后 ans 则要减去这对逆序对，反之则加上。

大概思路讲完后，我们来盘点一下**坑点**：

1.  $x_j$ 会大于 $y_j$，这时我们需要交换 $x_j$ 和 $y_j$ 再进行操作。
2. 不知道是不是我的代码问题，此题卡空间……虽是动态开点的，但还是过不去。这时我们需要进行**垃圾回收**来节省一些空间。
3. 在我的写法中，需要特判 $x_j=y_j$ 的情况。~~我也不知道为什么，反正加上我就对了。~~

可能有些 dalao 会问什么是垃圾回收，我这里给出一个**较为感性**的回答：

因为线段树会删除节点，但是节点删除之后可能之后都没用了（操作不会调用到这个节点），所以我们可以开一个栈，存放没用的节点编号，新建节点时先判断栈中有没有没用的节点，如果有就用栈顶的编号，再弹出栈顶，否则就新开一个节点。

这里给出我的代码（带注释）：
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int N=2e5+10;
struct segment_tree{
	int lson,rson;
	long long val;
};
segment_tree hjt[N<<7];
int tmp[2][20];
int root[N],a[N],sta[N];//sta就是垃圾回收的栈 
int t,tot,top;
int n,m;
int lowbit(int x){
	return x&-x;
}
void hjt_ins(int &now,int l,int r,int pos){
	if(!now)
		now=top?sta[top--]:++tot;//垃圾回收 
	hjt[now].val++;
	if(l==r)
		return ;
	int mid=l+r>>1;
	if(pos<=mid)
		hjt_ins(hjt[now].lson,l,mid,pos);
	else
		hjt_ins(hjt[now].rson,mid+1,r,pos);
}
void hjt_del(int &now,int l,int r,int pos){
	if(!now)
		now=top?sta[top--]:++tot;//垃圾回收 
	hjt[now].val--;
	if(l==r)
		return ;
	int mid=l+r>>1;
	if(pos<=mid)
		hjt_del(hjt[now].lson,l,mid,pos);
	else
		hjt_del(hjt[now].rson,mid+1,r,pos);
	if(!hjt[now].val)//判断是否要扔进栈里 
		sta[++top]=now,now=0;
}
long long hjt_query1(int l,int r,int pos){
	if(l==r)
		return 0;
	long long val=0;
	for(int i=1;i<=tmp[1][0];i++)
		val+=hjt[hjt[tmp[1][i]].rson].val;
	for(int i=1;i<=tmp[0][0];i++)
		val-=hjt[hjt[tmp[0][i]].rson].val;
	int mid=l+r>>1;
	if(pos<=mid){
		for(int i=1;i<=tmp[1][0];i++)
			tmp[1][i]=hjt[tmp[1][i]].lson;
		for(int i=1;i<=tmp[0][0];i++)
			tmp[0][i]=hjt[tmp[0][i]].lson;
		return (long long)(val+hjt_query1(l,mid,pos));
	}
	else{
		for(int i=1;i<=tmp[1][0];i++)
			tmp[1][i]=hjt[tmp[1][i]].rson;
		for(int i=1;i<=tmp[0][0];i++)
			tmp[0][i]=hjt[tmp[0][i]].rson;
		return hjt_query1(mid+1,r,pos);
	}
}
long long hjt_query2(int l,int r,int pos){
	if(l==r)
		return 0;
	long long val=0;
	for(int i=1;i<=tmp[1][0];i++)
		val+=hjt[hjt[tmp[1][i]].lson].val;
	for(int i=1;i<=tmp[0][0];i++)
		val-=hjt[hjt[tmp[0][i]].lson].val;
	int mid=l+r>>1;
	if(pos<=mid){
		for(int i=1;i<=tmp[1][0];i++)
			tmp[1][i]=hjt[tmp[1][i]].lson;
		for(int i=1;i<=tmp[0][0];i++)
			tmp[0][i]=hjt[tmp[0][i]].lson;
		return hjt_query2(l,mid,pos);
	}
	else{
		for(int i=1;i<=tmp[1][0];i++)
			tmp[1][i]=hjt[tmp[1][i]].rson;
		for(int i=1;i<=tmp[0][0];i++)
			tmp[0][i]=hjt[tmp[0][i]].rson;
		return (long long)(val+hjt_query2(mid+1,r,pos));
	}
}
void bit_ins(int pos,int val){
	for(int i=pos;i<=n;i+=lowbit(i))
		hjt_ins(root[i],1,n,val);
}
void bit_del(int pos,int val){
	for(int i=pos;i<=n;i+=lowbit(i))
		hjt_del(root[i],1,n,val);
}
long long bit_query1(int l,int r,int val){
//查询l~r中所有>pos的个数 
	if(l>r)
		return 0;
	memset(tmp,0,sizeof tmp);
	for(int i=r;i;i-=lowbit(i))
		tmp[1][++tmp[1][0]]=root[i];
	for(int i=l-1;i;i-=lowbit(i))
		tmp[0][++tmp[0][0]]=root[i];
	return hjt_query1(1,n,val);
}
long long bit_query2(int l,int r,int val){
//查询l~r中所有<pos的个数 
	if(l>r)
		return 0;
	memset(tmp,0,sizeof tmp);
	for(int i=r;i;i-=lowbit(i))
		tmp[1][++tmp[1][0]]=root[i];
	for(int i=l-1;i;i-=lowbit(i))
		tmp[0][++tmp[0][0]]=root[i];
	return hjt_query2(1,n,val);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		a[i]=i;
		bit_ins(i,a[i]);//插入节点 
	}
	long long ans=0;//因为是顺序，所以逆序对个数为0 
	int x,y;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		if(x>y)//特判x>y的情况 
			swap(x,y);
		if(x==y){//特判x=y的情况 
			cout<<ans<<'\n';
			continue;
		}
		ans+=bit_query1(x+1,y-1,a[x]);//加上新增的逆序对 
		ans-=bit_query2(x+1,y-1,a[x]);//减去原来的逆序对 
		ans+=bit_query2(x+1,y-1,a[y]);//加上新增的逆序对 
		ans-=bit_query1(x+1,y-1,a[y]);//减去原来的逆序对 
		if(a[x]<a[y])//原来p[x]与p[y]是逆序对 
			ans++;
		else//原来p[x]与p[y]不是逆序对 
			ans--;
		bit_del(x,a[x]);//在x处删除x 
		bit_del(y,a[y]);//在y处删除y 
		bit_ins(x,a[y]);//在x处加入y 
		bit_ins(y,a[x]);//在x处加入x 
		swap(a[x],a[y]);//交换 
		cout<<ans<<'\n';
	}
}
```

---

## 作者：Utilokasteinn (赞：2)

## [Link](https://www.luogu.com.cn/problem/CF785E)

先算出原数组的逆序对数 $ans$。对于每次修改，容易发现交换 $a_i$ 和 $a_j$ 时：

若 $a_i>a_j$，则答案减 $1$。

若 $a_i<a_j$，则答案加 $1$。

然后

$ans$ 加上 $[i+1,j-1]$ 中大于 $a_i$ 的数的个数，

$ans$ 减去 $[i+1,j-1]$ 中小于 $a_i$ 的数的个数，

$ans$ 加上 $[i+1,j-1]$ 中小于 $a_j$ 的数的个数，

$ans$ 减去 $[i+1,j-1]$ 中大于 $a_j$ 的数的个数。 

最后记得交换 $a_i$ 和 $a_j$。

发现可以用分块维护。

对每一块都设一个辅助数组 $b$，先让 $b=a$，然后对 $b$ 进行排序。

对于修改，直接交换，然后将两个点所在的块的 $b$ 数组排序。

对于查询，整块的话二分在 $b$ 里面找，散块暴力扫一遍即可。最后答案累加。

注意要开 ```long long```。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,a[200005],c[200005],d[200005];
int pos[200005],L[480],R[480];
ll ans;
vector<int>b[480];
inline int read()
{
	int s=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())
		if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())
		s=s*10+c-'0';
	return s*f;
}
void merge_sort(int l,int r)
{
	if(l==r)return;
    int mid=(l+r)/2;
    merge_sort(l,mid);
    merge_sort(mid+1,r);
    int i=l,j=mid+1,k=l;
    while(i<=mid&&j<=r)
    	if(c[i]>c[j])
    		d[k++]=c[j++],ans+=mid-i+1;
    	else d[k++]=c[i++];
    while(i<=mid)d[k++]=c[i++];
    while(j<=r)d[k++]=c[j++];
    for(int i=l;i<=r;i++)
		c[i]=d[i];
}
void input()
{
	n=read(),m=read();
	int len=sqrt(n),block=n/len;
    for(int i=1;i<=n;i++)
		a[i]=c[i]=i;
	for(int i=1;i<=block;i++)
        L[i]=R[i-1]+1,R[i]=i*len;
    R[block]=n;
    for(int i=1;i<=block;i++)
    	for(int j=L[i];j<=R[i];j++)
            pos[j]=i,b[i].push_back(a[j]);
    for(int i=1;i<=block;i++)
		sort(b[i].begin(),b[i].end());
}
void query(int l,int r)
{
	int p=pos[l],q=pos[r],ps;
    if(a[l]>a[r])ans--;
    if(a[r]>a[l])ans++;
    if(p==q)
    {
    	for(int i=l+1;i<r;i++)
            ans+=(a[i]>a[l])-(a[i]<a[l])+(a[i]<a[r])-(a[i]>a[r]);
        swap(a[l],a[r]);
        return;
	}
	for(int i=p+1;i<=q-1;i++)
	{
		ps=upper_bound(b[i].begin(),b[i].end(),a[l])-b[i].begin();
		if(ps!=b[i].size())ans+=b[i].size()-ps;
		ps=lower_bound(b[i].begin(),b[i].end(),a[l])-b[i].begin()-1;
		ans-=ps+1;
		ps=lower_bound(b[i].begin(),b[i].end(),a[r])-b[i].begin()-1;
		ans+=ps+1;
		ps=upper_bound(b[i].begin(),b[i].end(),a[r])-b[i].begin();
        if(ps!=b[i].size())ans-=b[i].size()-ps;
    }
    b[p].erase(lower_bound(b[p].begin(),b[p].end(),a[l]));
    b[q].erase(lower_bound(b[q].begin(),b[q].end(),a[r]));
    b[p].insert(upper_bound(b[p].begin(),b[p].end(),a[r]),a[r]);
    b[q].insert(upper_bound(b[q].begin(),b[q].end(),a[l]),a[l]);
    for(int i=l+1;i<=R[p];i++)
		ans+=(a[i]>a[l])-(a[i]<a[l])+(a[i]<a[r])-(a[i]>a[r]);
    for(int i=L[q];i<r;i++)
        ans+=(a[i]>a[l])-(a[i]<a[l])+(a[i]<a[r])-(a[i]>a[r]);
    swap(a[l],a[r]);
}
int main()
{
    input();
    while(m--)
	{
        int l=read(),r=read();
        if(l>r)swap(l,r);
        if(a[l]==a[r])
		{
			printf("%lld\n",ans);
			continue;
		}
		query(l,r);
		printf("%lld\n",ans);
    }
    return 0;
}
```




---

## 作者：Karry5307 (赞：2)

### 题意

给定长度为 $n$ 的排列 $\pi$，一开始 $\pi_i=i$。有 $k$ 次询问，每次给定 $l,r$，交换 $\pi_l$ 和 $\pi_r$ 并回答交换后排列的逆序对数。

$\texttt{Data Range:}1\leq n\leq 2\times 10^5,1\leq k\leq 5\times 10^4$。

### 题解

好久没写分块了，写一下。

简单想了一下发现不会做只带 $\log$ 的，考虑分块。

首先考虑如何求每个位置的影响，这个相当于就是查询一整块中有多少个数大于或者小于这个数，可以对每个块排序然后二分。

对于交换的话，由于块内元素改变了所以需要重新排序。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,kk,blockSize,u,v;
li res,d1,d2;
ll x[MAXN],sz[MAXN],lx[MAXN],rx[MAXN],bel[MAXN],r[551][551];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline li query(ll pos)
{
	li res=0;
	for(register int i=1;i<bel[pos];i++)
	{
		res+=sz[i]-(upper_bound(r[i]+1,r[i]+sz[i]+1,x[pos])-r[i]-1);
	}
	for(register int i=lx[bel[pos]];i<pos;i++)
	{
		res+=(x[i]>x[pos]);
	}
	for(register int i=pos+1;i<=rx[bel[pos]];i++)
	{
		res+=(x[i]<x[pos]);
	}
	for(register int i=bel[pos]+1;i<=bel[n];i++)
	{
		res+=upper_bound(r[i]+1,r[i]+sz[i]+1,x[pos])-r[i]-1;
	}
	return res;
}
int main()
{
	n=read(),kk=read(),blockSize=sqrt(n);
	for(register int i=1;i<=n;i++)
	{
		x[i]=i,bel[i]=bel[i-1]+(i%blockSize==1);
		r[bel[i]][++sz[bel[i]]]=x[i];
		i%blockSize==1?lx[bel[i]]=i,rx[bel[i-1]]=i-1:1;
	}
	for(register int i=1;i<=bel[n];i++)
	{
		sort(r[i]+1,r[i]+sz[i]+1);
	}
	rx[bel[n]]=n;
	for(register int i=1;i<=kk;i++)
	{
		u=read(),v=read();
		if(u==v)
		{
			printf("%lld\n",res);
			continue;
		}
		u>v?swap(u,v):(void)1,d1=query(u),d2=query(v);
		res-=d1+d2-(x[u]>x[v]);
		if(bel[u]!=bel[v])
		{
			for(register int j=1;j<=sz[bel[u]];j++)
			{
				if(r[bel[u]][j]==x[u])
				{
					r[bel[u]][j]=x[v];
					break;
				}
			}
			for(register int j=1;j<=sz[bel[v]];j++)
			{
				if(r[bel[v]][j]==x[v])
				{
					r[bel[v]][j]=x[u];
					break;
				}
			}	
		}
		sort(r[bel[u]]+1,r[bel[u]]+sz[bel[u]]+1);
		sort(r[bel[v]]+1,r[bel[v]]+sz[bel[v]]+1);
		swap(x[u],x[v]);
		d1=query(u),d2=query(v);
		res+=d1+d2-(x[u]>x[v]),printf("%lld\n",res);
	}
}
```

---

## 作者：Memory_of_winter (赞：2)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10329505.html)

**题目大意：**有一串数为$1\sim n(n\leqslant2\times10^5)$，$m(m\leqslant5\times10^4)$次询问，每次问交换位置为$l,r$的两个数后数列中逆序对的个数。

**题解：**发现交换位置为$l,r$的数后，逆序对的变化只和区间$(l,r)$内的数与$s_l,s_r$的大小关系有关，设$S_i$表示区间$(l,r)$中比$s_i$小的数，$B_i$表示区间$(l,r)$中比$s_i$大的数，$ans'=ans+S_r-B_r-S_l+B_l$。设$len=r-l-1$，$ans'=ans+S_r-(len-S_r)-S_l+(len-S_l)=ans+2(S_r-S_l)$。

考虑分块，设块大小为$S$，在块内排序，在边角处暴力，在整块处二分查找位置，询问的复杂度是$O(2S+\dfrac n S\log_2S)$；修改为二分处位置直接插入或删除，复杂度$O(4S)$，所以当$S$略大于$\sqrt n$时最优。（反正我懒得算，随便猜一个）



**C++ Code：**

```cpp
#include <algorithm>
#include <cstdio>
#include <vector>
#define maxn 200010
const int BSZ = 1000, BNUM = maxn / BSZ + 10;

int n, m;
long long ans;
int L[BNUM], R[BNUM], bel[maxn], s[maxn];
std::vector<int> V[BNUM];

int query(int l, int r, int x) {
	if (l > r) return 0;
	const int lb = bel[l], rb = bel[r];
	int res = 0;
	if (lb == rb) for (int i = l; i <= r; ++i) res += s[i] < x;
	else {
		for (int i = l; i <= R[lb]; ++i) res += s[i] < x;
		for (int i = lb + 1; i < rb; ++i) res += std::upper_bound(V[i].begin(), V[i].end(), x) - V[i].begin();
		for (int i = L[rb]; i <= r; ++i) res += s[i] < x;
	}
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) V[bel[i] = i / BSZ + 1].push_back(s[i] = i);
	const int B = bel[n];
	for (int i = 1; i <= B; ++i) {
		L[i] = (i - 1) * BSZ;
		R[i] = L[i] + BSZ - 1;
	}
	L[1] = 1, R[B] = n;
	while (m --> 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		if (l == r) {
			printf("%lld\n", ans);
			continue;
		}
		if (l > r) std::swap(l, r);
		const int lb = bel[l], rb = bel[r];

		ans += (query(l + 1, r - 1, s[r]) - query(l + 1, r - 1, s[l])) * 2;
		ans += (s[l] < s[r]) ? 1 : -1;
		printf("%lld\n", ans);

		if (lb != rb) {
			V[lb].erase(std::lower_bound(V[lb].begin(), V[lb].end(), s[l]));
			V[lb].insert(std::upper_bound(V[lb].begin(), V[lb].end(), s[r]), s[r]);
			V[rb].erase(std::lower_bound(V[rb].begin(), V[rb].end(), s[r]));
			V[rb].insert(std::upper_bound(V[rb].begin(), V[rb].end(), s[l]), s[l]);
		}
		std::swap(s[l], s[r]);
	}
	return 0;
}

```





---

## 作者：moosssi (赞：1)

最近我都在练分块，所以我考虑用的分块

首先要知道，交换 $i$，$j$  两个位置的数对于 $1\sim i-1$
和 $j+1\sim n$ 的逆序对对数无影响，所以我们只需考虑中间的逆序对。

按照以往的套路，先分块，交换 $i$，$j$时，暴力计算两边不完整的块，对于中间的块，使用二分找出小于i和小于j的数的个数$x$，$y$，

那么逆序对对数的改变量则为$(y-x)*2$，（举几个例子，很容易发现规律）。代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
int a[N],b[N],dt[N],la[N],ra[N];
int n,m,len;
ll ans;
void chang(int l,int r){
	if(dt[l]==dt[r]){//暴力枚举每个位置，直接计算 
		ll cnt=0;
		if(a[l]>a[r])cnt--;
		else if(a[l]<a[r])cnt++;
		for(int i=l+1;i<=r-1;i++){
			if(a[l]>a[i])cnt--;
			else if(a[l]<a[i])cnt++;
			if(a[r]>a[i])cnt++;
			else if(a[r]<a[i])cnt--;
		}
		swap(a[l],a[r]);
		for(int i=la[dt[l]];i<=ra[dt[l]];i++)b[i]=a[i];//每次交换后，每个块的位置要重新排 
		sort(b+la[dt[l]],b+ra[dt[l]]+1);
		ans+=cnt;
	}
	else {
		int i=l+1,j=r-1;
		ll cnt=0;
		if(a[l]>a[r])cnt--;
		else if(a[l]<a[r])cnt++;
		while(dt[i]==dt[l]){//暴力计算两边不完整的块 
			if(a[l]>a[i])cnt--;
			else if(a[l]<a[i])cnt++;
			if(a[r]>a[i])cnt++;
			else if(a[r]<a[i])cnt--;
			i++;
		}
		while(dt[j]==dt[r]){
			if(a[l]>a[j])cnt--;
			else if(a[l]<a[j])cnt++;
			if(a[r]>a[j])cnt++;
			else if(a[r]<a[j])cnt--;
			j--;
		}
		for(int k=dt[i];k<=dt[j];k++){//中间的用找出的规律直接计算 
			int x=lower_bound(b+la[k],b+ra[k]+1,a[l])-(b+la[k]);
			int y=lower_bound(b+la[k],b+ra[k]+1,a[r])-(b+la[k]);
			cnt=cnt-2*(x-y);
		}
		ans+=cnt;
		swap(a[l],a[r]);
		for(int k=la[dt[l]];k<=ra[dt[l]];k++)b[k]=a[k];//重新记录块 
		for(int k=la[dt[r]];k<=ra[dt[r]];k++)b[k]=a[k];
		sort(b+la[dt[l]],b+ra[dt[l]]+1);
		sort(b+la[dt[r]],b+ra[dt[r]]+1);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	len=sqrt(n);
	for(int i=1;i<=n;i++){
		dt[i]=(i-1)/len+1;//记录每个位置在第几块里面 
		a[i]=b[i]=i;//b[i]将每个块分开从小到大排序，二分查找时好用 
	}
	for(int i=1;i<=dt[n];i++){
		la[i]=(i-1)*len+1;//记录每个块的左右端点 
		ra[i]=i*len;
		if(i==dt[n])ra[i]=n;
	}
	int l,r;
	while(m--){
		scanf("%d%d",&l,&r);
		if(l>r)swap(l,r);
		chang(l,r);
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Star_Cried (赞：1)

# 动态逆序对专练

为了说明这道题，顺便写了其他两道题，共三道题，~~三道题有递进关系~~

### 题意

维护一个序列，每次修改后求出当前序列逆序对个数。

### 思路

题目让我们求出
$$
\sum_{i=1}^n\sum_{j=i+1}^n[a_i>a_j]
$$
也就是让我们求出满足
$$
pos_i<pos_j\&\&a_i>a_j
$$
的点对数量。

对于不修改的情况，这显然是一个三维偏序问题，用树状数组或归并处理都可以。

对于修改的情况，我们可以用CDQ分治离线解决，或者使用树套树在线处理。

我这么懒当然是用树套树啦~

## 树状数组套值域线段树

### 思想

树状数组维护序列，值域线段树维护值域。

优点是可以写成非递归式查询，常数相对较小。

缺点是即使是动态开点空间消耗仍然很大。

### 实现

具体实现是每个树状数组节点开一棵线段树。修改时修改所有树状数组上包括的线段树，查询时类似。

```cpp
void update(int &ro,int l,int r,int x,int k){//l和r是当前值域区间，x为位置
    if(!ro) ro=++tot;
    val[ro]+=k;
    if(l==r)return;
    int mid=l+r>>1;
    if(x<=mid)update(ls[ro],l,mid,x,k);
    else update(rs[ro],mid+1,r,x,k);
}
```

墙裂安利非递归式线段树查询

```cpp
inline long long query(int l,int r,int x,int type){
    int cnta=0,cntb=0;
    long long ans=0;
    for(int i=l-1;i;i-=i&-i) qa[++cnta]=rt[i];//树状数组查询方法：差分
    for(int i=r;i;i-=i&-i)   qb[++cntb]=rt[i];//先将所有要处理的树状数组上的线段树全部记录，然后一起查询
    l=1,r=n;
    while(l<r){
        int mid=l+r>>1;
        if(x>mid){
            if(type){//type表示查询的类型，按照正常线段树查询的思路处理即可。这里type=1表示查左边
                for(int i=1;i<=cnta;i++) ans-=val[ls[qa[i]]];
                for(int i=1;i<=cntb;i++) ans+=val[ls[qb[i]]];
            }
            for(int i=1;i<=cnta;i++) qa[i]=rs[qa[i]];
            for(int i=1;i<=cntb;i++) qb[i]=rs[qb[i]];
            l=mid+1;
        }else{
            if(!type){
                for(int i=1;i<=cnta;i++) ans-=val[rs[qa[i]]];
                for(int i=1;i<=cntb;i++) ans+=val[rs[qb[i]]];
            }
            for(int i=1;i<=cnta;i++) qa[i]=ls[qa[i]];
            for(int i=1;i<=cntb;i++) qb[i]=ls[qb[i]];
            r=mid;
        }
    }
    return ans;
}
```

## [P3157 [CQOI2011]动态逆序对](https://www.luogu.com.cn/problem/P3157)

给你一个排列，每次删除一个位置上的数，求每次操作后的逆序对数。

### 思路

插入原序列之后得到原序列答案，每次删除一个数 $x$ 查询 $pos_i<x$ 、$a_i>a_x$ 和 $pos_i>x$ 、$a_i<a_x$ 的答案并用之前的答案减去，然后删除它的影响。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e5+10,maxm=3e7+10;
	int n,m,a[maxn],ls[maxm],rs[maxm],tot,rt[maxn],val[maxm];
	void update(int &ro,int l,int r,int x,int k){
		if(!ro) ro=++tot;
		val[ro]+=k;
		if(l==r)return;
		int mid=(l+r)>>1;
		if(x<=mid) update(ls[ro],l,mid,x,k);
		else update(rs[ro],mid+1,r,x,k);
	}
	int qa[maxn],qb[maxn];
	long long ans;
	inline long long query(int l,int r,int x,int type){
		int cnta=0,cntb=0;
		long long ans=0;
		for(int i=l-1;i;i-=i&-i) qa[++cnta]=rt[i];
		for(int i=r;i;i-=i&-i)   qb[++cntb]=rt[i];
		l=1,r=n;
		while(l<r){
			int mid=(l+r)>>1;
			if(x>mid){
				if(type){
					for(int i=1;i<=cnta;i++)ans-=val[ls[qa[i]]];
					for(int i=1;i<=cntb;i++)ans+=val[ls[qb[i]]];
				}
				for(int i=1;i<=cnta;i++)qa[i]=rs[qa[i]];
				for(int i=1;i<=cntb;i++)qb[i]=rs[qb[i]];
				l=mid+1;
			}else{
				if(!type){
					for(int i=1;i<=cnta;i++)ans-=val[rs[qa[i]]];
					for(int i=1;i<=cntb;i++)ans+=val[rs[qb[i]]];
				}
				for(int i=1;i<=cnta;i++)qa[i]=ls[qa[i]];
				for(int i=1;i<=cntb;i++)qb[i]=ls[qb[i]];
				r=mid;
			}
		}
		return ans;
	}
	int pos[maxn];
	inline void work(){
		n=read(),m=read();
		for(int i=1;i<=n;i++) {
			ans+=query(1,i-1,a[i]=read(),0);pos[a[i]]=i;
			for(int x=i;x<=n;x+=x&-x) update(rt[x],1,n,a[i],1);
		}
		printf("%lld\n",ans);
		while(--m){
			int x=read();
			ans-=query(1,pos[x]-1,x,0)+query(pos[x]+1,n,x,1);
			printf("%lld\n",ans);
			for(int j=pos[x];j<=n;j+=j&-j) update(rt[j],1,n,x,-1);
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```

## [CF785E Anton and Permutation](https://www.luogu.com.cn/problem/solution/CF785E)

给你一个原序列为递增排列的序列，每次交换两个位置上的数，求每次操作后的逆序对数。

### 思路

相对于上一题，并非删除而是交换两个位置上的数，实际上就是在原位置删除两个数然后在彼此的位置又加上这两个数。

这里我先减去影响然后更新再加上影响，最后单独讨论一下这两个数之间互换对答案的贡献。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=2e5+1,maxm=3e7+1;
	int n,Q,a[maxn],rt[maxn];
	long long ans;
	int ls[maxm],rs[maxm],tot,val[maxm];
	void update(int &ro,int l,int r,int x,int k){
		if(!ro) ro=++tot;
		val[ro]+=k;
		if(l==r)return;
		int mid=l+r>>1;
		if(x<=mid)update(ls[ro],l,mid,x,k);
		else update(rs[ro],mid+1,r,x,k);
	}
	int qa[maxn],qb[maxn];
	inline long long query(int l,int r,int x,int type){
		int cnta=0,cntb=0;
		long long ans=0;
		for(int i=l-1;i;i-=i&-i) qa[++cnta]=rt[i];
		for(int i=r;i;i-=i&-i)   qb[++cntb]=rt[i];
		l=1,r=n;
		while(l<r){
			int mid=l+r>>1;
			if(x>mid){
				if(type){
					for(int i=1;i<=cnta;i++) ans-=val[ls[qa[i]]];
					for(int i=1;i<=cntb;i++) ans+=val[ls[qb[i]]];
				}
				for(int i=1;i<=cnta;i++) qa[i]=rs[qa[i]];
				for(int i=1;i<=cntb;i++) qb[i]=rs[qb[i]];
				l=mid+1;
			}else{
				if(!type){
					for(int i=1;i<=cnta;i++) ans-=val[rs[qa[i]]];
					for(int i=1;i<=cntb;i++) ans+=val[rs[qb[i]]];
				}
				for(int i=1;i<=cnta;i++) qa[i]=ls[qa[i]];
				for(int i=1;i<=cntb;i++) qb[i]=ls[qb[i]];
				r=mid;
			}
		}
		return ans;
	}
	inline void work(){
		n=read(),Q=read();
		for(int i=1;i<=n;i++){
			a[i]=i;
			for(int j=i;j<=n;j+=j&-j) update(rt[j],1,n,a[i],1);
		}
		while(Q--){
			int x=read(),y=read();
			if(x==y){
				printf("%lld\n",ans);continue;
			}
			if(x>y)swap(x,y);
			ans=ans-query(1,x-1,a[x],0)-query(x+1,n,a[x],1)-query(1,y-1,a[y],0)-query(y+1,n,a[y],1);
			for(int i=x;i<=n;i+=i&-i) update(rt[i],1,n,a[x],-1),update(rt[i],1,n,a[y],1);
			for(int i=y;i<=n;i+=i&-i) update(rt[i],1,n,a[x],1),update(rt[i],1,n,a[y],-1);
			swap(a[x],a[y]);
			ans=ans+query(1,x-1,a[x],0)+query(x+1,n,a[x],1)+query(1,y-1,a[y],0)+query(y+1,n,a[y],1);
			ans+=(a[x]<a[y]?1:-1);
			printf("%lld\n",ans);
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```

## [P1975 [国家集训队]排队](https://www.luogu.com.cn/problem/P1975)

给你一个序列，每次交换两个位置上的数，求每次操作后逆序对数。

### 思路

给上面的代码加个离散化~~XD~~

后面单独讨论两个数的贡献时有一点区别。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=2e4+1,maxm=3e6+1;
	int n,Q,a[maxn],cnt,b[maxn],rt[maxn];
	long long ans;
	int ls[maxm],rs[maxm],tot,val[maxm];
	void update(int &ro,int l,int r,int x,int k){
		if(!ro) ro=++tot;
		val[ro]+=k;
		if(l==r)return;
		int mid=l+r>>1;
		if(x<=mid)update(ls[ro],l,mid,x,k);
		else update(rs[ro],mid+1,r,x,k);
	}
	int qa[maxn],qb[maxn];
	inline long long query(int l,int r,int x,int type){
		int cnta=0,cntb=0;
		long long ans=0;
		for(int i=l-1;i;i-=i&-i) qa[++cnta]=rt[i];
		for(int i=r;i;i-=i&-i)   qb[++cntb]=rt[i];
		l=1,r=n;
		while(l<r){
			int mid=l+r>>1;
			if(x>mid){
				if(type){
					for(int i=1;i<=cnta;i++) ans-=val[ls[qa[i]]];
					for(int i=1;i<=cntb;i++) ans+=val[ls[qb[i]]];
				}
				for(int i=1;i<=cnta;i++) qa[i]=rs[qa[i]];
				for(int i=1;i<=cntb;i++) qb[i]=rs[qb[i]];
				l=mid+1;
			}else{
				if(!type){
					for(int i=1;i<=cnta;i++) ans-=val[rs[qa[i]]];
					for(int i=1;i<=cntb;i++) ans+=val[rs[qb[i]]];
				}
				for(int i=1;i<=cnta;i++) qa[i]=ls[qa[i]];
				for(int i=1;i<=cntb;i++) qb[i]=ls[qb[i]];
				r=mid;
			}
		}
		return ans;
	}
	inline void work(){
		n=read();
		for(int i=1;i<=n;i++) a[i]=b[i]=read();
		sort(b+1,b+1+n);
		cnt=unique(b+1,b+1+n)-b-1;
		for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+cnt,a[i])-b;
		for(int i=1;i<=n;i++){
			ans+=query(1,i-1,a[i],0);
			for(int j=i;j<=n;j+=j&-j) update(rt[j],1,n,a[i],1);
		}
		printf("%lld\n",ans);
		Q=read();
		while(Q--){
			int x=read(),y=read();
			if(x==y){
				printf("%lld\n",ans);continue;
			}
			if(x>y)swap(x,y);
			ans=ans-query(1,x-1,a[x],0)-query(x+1,n,a[x],1)-query(1,y-1,a[y],0)-query(y+1,n,a[y],1);
			for(int i=x;i<=n;i+=i&-i) update(rt[i],1,n,a[x],-1),update(rt[i],1,n,a[y],1);
			for(int i=y;i<=n;i+=i&-i) update(rt[i],1,n,a[x],1),update(rt[i],1,n,a[y],-1);
			swap(a[x],a[y]);
			ans=ans+query(1,x-1,a[x],0)+query(x+1,n,a[x],1)+query(1,y-1,a[y],0)+query(y+1,n,a[y],1);
			if(a[x]<a[y]) ans+=1;
			else if(a[x]>a[y]) ans-=1;
			printf("%lld\n",ans);
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```

****

~~复制了三遍代码显得很长的雅子~~

对于后两个题更简单并且更优秀的分块解法，~~我不会~~因为没有普适性所以我们不学，嗯嗯。

---

## 作者：BzhH (赞：1)

一道简单分块题，题目要求的是逆序对数量，那么对于每一次交换位置$l,r(l \le r)$的操作,我们只需要判断区间$(L,R)$中大于与小于两个端点的数字个数即可,可以考虑将每个块中进行排序再二分达到快速查询,时间复杂度为$O(n\sqrt{n}\log{n})$

具体见代码
```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int N = 2e5 + 500;

int len, num[N], block[N], gt[N], L[N], R[N];
long long ans = 0;

long long work(int x, int k)
{
    int l = L[k], r = R[k], res = R[k] + 1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (block[mid] > x)
            res = mid, r = mid - 1;
        else 
            l = mid + 1;
    }
    return R[k] - res + 1;
}

void update(int l, int r)
{
    if (gt[l] == gt[r])//直接暴力枚举
    {
        for (int i = l + 1; i < r; i++)
        {
            if (num[r] > num[i])
                ans++;
            else if (num[r] < num[i])
                ans--;
            if (num[l] < num[i])
                ans++;
            else if (num[l] > num[i])
                ans--;
        }
        if (num[l] > num[r])
            ans--;
        else if (num[l] < num[r])
            ans++;
        swap(num[l], num[r]);
    }
    else 
    {
        int i = l, j = r;
        i++, j--;
        while (gt[i] == gt[l])
        {
            if (num[r] > num[i])
                ans++;
            else if (num[r] < num[i])
                ans--;
            if (num[l] < num[i])
                ans++;
            else if (num[l] > num[i])
                ans--;
            i++;
        }
        while (gt[j] == gt[r])
        {
            if (num[r] > num[j])
                ans++;
            else if (num[r] < num[j])
                ans--;
            if (num[l] < num[j])
                ans++;
            else if (num[l] > num[j])
                ans--;
            j--;
        }
        for (int k = gt[i]; k <= gt[j]; k++)
        {
            ans += work(num[l], k);
            ans -= len - work(num[l], k);
            ans += len - work(num[r], k);
            ans -= work(num[r], k);
        }//二分找个数
        if (num[l] > num[r])
            ans--;
        else if (num[l] < num[r])
            ans++;
        swap(num[l], num[r]);
        for (int k = L[gt[r]]; k <= R[gt[r]]; k++)
            block[k] = num[k];
        for (int k = L[gt[l]]; k <= R[gt[l]]; k++)
            block[k] = num[k];
        sort(block + L[gt[l]], block + R[gt[l]] + 1);
        sort(block + L[gt[r]], block + R[gt[r]] + 1);//更行块中的数值
    }
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    len = sqrt(n);
    for (int i = 1; i <= n; i++)
        gt[i] = (i - 1) / len + 1, block[i] = i, num[i] = i;
    for (int i = 1; i <= gt[n]; i++)
    {
        L[i] = (i - 1) * len + 1, R[i] = i * len;
        sort(block + L[i], block + R[i] + 1);
    }//预处理区间端点
    while (k--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (l > r)
            swap(l, r);
        update(l, r);//进行更新
        printf("%lld\n", ans);
    }
    return 0;
}
```


---

## 作者：xixiup (赞：1)

## 思路分享

由于我们每次仅会交换两个值，所以我们可以直接 $\Theta(1)$ 地解决两个值的交换，故我们唯一需要考虑的是交换两个值对于答案的贡献。

我们可以首先设交换的两个节点是 $x,y\,\left( x \leqslant y \right)$。若 $x=y$，我们就可以什么都不做然后直接输出上一问的答案。

然后我们把这个排列分成 $5$ 个部分：$\left[1,x\right)$、$x$、$\left(x,y\right)$、$y$、$\left(y,n\right]$。我们可以思考每几个部分对答案的贡献。

首先思考对于第 $1$、$5$ 个部分，也就是 $\left[ 1,x \right)$ 和 $\left( y,n \right]$，因为这两个部分在交换前后本身的位置不发生变化，与其他几个部分的相对位置也不发生变化，故答案不会改变。

然后思考对于第 $2$、$4$ 个部分，也就是 $x$ 和 $y$，由于这两个部分都仅有一个数，所以我们可以直接 $\Theta \left( 1 \right)$ 处理掉。

最后的几个部分是最难的。

我们可以先考虑第 $2$、$3$ 部分，也就是 $x$ 和 $\left( x,y \right)$，思考转换后这两个部分是互换了的。

我们设 $len=y-x-1$，也就是 $x$ 与 $y$ 中间的元素个数，$z_1$ 为所有 $i\in\left( x,y \right)$ 且 $a_i<a_x$ 的 $i$ 的个数。（用人能听懂的话来讲，就是求 $x+1$ 到 $y-1$ 中有多少个 $i$ 满足 $a_i < a_x$）。

故这两个部分间的逆序对个数为 $z_1$，又因为 $a$ 数组是一个排列，所以这个区间内满足 $a_i > a_x$ 的 $i$ 的个数为 $len-z_1$

相同的，我们设所有 $i\in\left( x,y \right)$ 且 $a_i<a_y$ 的 $i$ 的个数为 $z_2$，同理可得，这个区间内所有满足 $a_i > a_y$ 的 $i$ 的个数为 $len-z_2$。

所以我们原来有的逆序对的个数为 $len+z_1-z_2$，这些逆序对需要从答案中减掉。而新增的逆序对的个数为 $len-z_1+z_2$，需要加上。故最后答案为：
$$
\boxed{len-z_1+z_2-\left(len+z_1-z_2 \right)=2*\left(z_2-z_1\right)}
$$
故我们只需要统计某个区间内有多少个数小于一个特定的值了。

那怎么做呢？

首先对于一个区间，我们可以考虑分块，然后对于每一个块中有多少个数小于一个特定的值，我不会 $lower_bound$，所以我就给每一个块开了一个树状数组维护。

整个算法算下来，时间复杂度 $\Theta \left( n\log(n)\sqrt n \right)$，空间复杂度 $\Theta \left( n \sqrt n \right)$，可以踩着过去的。

## 代码展示

（略有冗长，小心食用）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200100,logn=20,sqrtn=500;
int n,s,q,nu[sqrtn][maxn],a[maxn];
long long ans;//答案可能会爆int
int le[sqrtn],ri[sqrtn],num[maxn];
int lowbit(int x){//树状数组的lowbit
	return x&(-x);
}
int query2(int x,int y){//查询在第y个块中小于等于x的值的个数
	long long sum=0;
	while(x){
		sum+=nu[y][x];
		x-=lowbit(x);
	}
	return sum;
}
void change2(int x,int y,int i){//修改第y个块中值x的数字
	while(x<=n){
		nu[y][x]+=i;
		x+=lowbit(x);
	}
}
int query1(int l,int r,int v){//询问区间[l,r]中小于等于v的值的个数
	int nl=num[l],nr=num[r];
	long long sum=0;
	if(nl==nr){//同一个块中暴力处理
		for(int i=l;i<=r;i++){
			sum+=(a[i]<v);
		}
		return sum;
	}
	for(int i=l;i<=ri[nl];i++){//维护两端多出来的几个数
		sum+=(a[i]<v);
	}
	for(int i=le[nr];i<=r;i++){//同上一个循环
		sum+=(a[i]<v);
	}
	for(int i=nl+1;i<nr;i++){//求每一个块中的答案
		sum+=query2(v,i);
	}
	return sum;
}
void change1(int l,int v,int i){//把第l个位置权值为v的答案修改i
	int nl=num[l];
	change2(v,nl,i);
	return;
}
int main(){
	cin>>n>>q;
	s=(int)sqrt(n);//处理块的大小s
	int tot=n/s;
	if(s*s<n){
		s++;
	}
	for(int i=1;i<=s;i++){//初始化每一个块
		le[i]=ri[i-1]+1;
		ri[i]=min(le[i]+s-1,n);
		for(int j=le[i];j<=ri[i];j++){
			num[j]=i;
		}
	}
	for(int i=1;i<=n;i++){//初始化开始的排列
		a[i]=i;
		change1(i,a[i],1);
	}
	for(int i=1;i<=q;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x==y){
			printf("%lld\n",ans);//x=y直接输出答案
			continue;
		}
		if(x>y){
			swap(x,y);
		}
		if(a[x]<a[y]){//维护x与y构成的逆序对
			ans++;
		}
		else{
			ans--;
		}
		if(x+1<=y-1){//更新ans
			ans+=2*(query1(x+1,y-1,a[y])-query1(x+1,y-1,a[x]));
		}
		change1(y,a[y],-1);//往下5行都是交换x与y
		change1(x,a[x],-1);
		swap(a[x],a[y]);
		change1(y,a[y],1);
		change1(x,a[x],1);
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：MuYC (赞：0)

#### 题目解法
首先可以分析一下，假设交换的位置为 $i,j(i < j)$ ， 那么实际上对于 $[1,i - 1]$ 和 $[j + 1, n]$ 的逆序对数量是没有影响的。

真正受到影响的实际上的是 $[i,j]$ 的区间逆序对数量。

为了方便描述，下面设 $l = i+1$，$r=j - 1$。

我们设交换之前序列 $[l, r]$ 中比 $A[i]$ 大的数有 $x_1$ 个，比 $A[i]$ 小的数有 $y_1$ 个，比 $A[j]$ 大的数有 $x_2$ 个，比 $A[j]$ 小的数有 $y_2$ 个。那么答案的 $Ans$ 相对于上一次的答案 $Ans_{last}$ 就会变成： 

$Ans = Ans_{last} + x_1 - y_1 - x_2 + y_2$ 

$A_i > A_j$ 的话，答案还需要减一，否则加一。

上述答案变化并不难以理解，主要是难在维护区间中比某个数大 / 小的数的数量而且要动态交换两个数。

但是这其实就是 [hzwer](http://hzwer.com/8053.html) 的数列分块入门$2$ 需要支持的操作。于是上大分块。

考虑维护每一个整块都是从小到大排序好的，设 $i$ 所在的块是 $pos[i]$， $j$ 所在的块是在 $pos[j]$，设块的大小是 $\sqrt{n}$ ，块的数量也是 $\sqrt{n}$。

+ 对于交换操作，直接暴力交换即可，然后重新排序即可，复杂度 $O(\sqrt{n}\log n)$。

+ 对于查询区间 $[l,r]$ 内有个数比 $A_i,A_j$ 大 / 小，因为我们维护的每一个块都是从小到大排序好的，而且后一块的在原序列的位置编号最小的那一个大于这一块的最大编号。那么第 $pos[i] + 1$ 到第 $pos[j] - 1$ 块都可以对于整块进行二分知道有多少个数比 $A_i,A_j$ 大 / 小，对于零散的块我们就直接暴力判断即可，处理零散块的复杂度是 $O(\sqrt{n})$，整块的处理是$O(\sqrt{n}\log n)$。

时间复杂度: $O(Q\sqrt{n}\log n)$ 

ps: $\log {\sqrt{n}} = \frac{1}{2}\log n$ ，所以认为是 $\log n$。

一些细节见代码处。

### Code

虽然跑得慢而且长，但是自认为思路还挺清晰的。

```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, flag = 1;
    char ch = getchar();
    for( ; ch > '9'|| ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
    for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
    return x * flag;
}
const int MAXN = 2e5 + 56;
int n, m;
long long Ans = 0; // 答案可能是 n^2 级别的，所以要开long long
int block, L[MAXN], R[MAXN], num = 0, pos[MAXN];

struct data {
    int val, id; //id 表示它在原来数组中的位置，val 表示它当前的值
} A[MAXN]; //这个表示一个数组

bool cmp(data a, data b) {return a.val < b.val;}

void change(int l, int r) {
    int bl = pos[l], br = pos[r], rl, rr;
    for(int i = L[bl] ; i <= R[bl] ; i ++) //获取真实位置
        if(A[i].id == l) rl = i;
    for(int i = L[br] ; i <= R[br] ; i ++)
        if(A[i].id == r) rr = i;
    swap(A[rl].val, A[rr].val); // 进行交换
    sort(A + L[bl], A + 1 + R[bl], cmp); // 防止失序，进行整块排序
    sort(A + L[br], A + 1 + R[br], cmp);
    return ;
}

void Get(int l, int r) {
    int B1 = 0, B2 = 0, S1 = 0, S2 = 0; // B1 表示比 l 大的，S1 表示比 l 小的
    int bl = pos[l], br = pos[r], rl, rr;
    //------------Step 1：获取当前l 和 r 在有序数组中的位置 --------
    for(int i = L[bl] ; i <= R[bl] ; i ++) // 定位 l 以及 r 当前的“真实位置” 
        if(A[i].id == l) rl = i;
    for(int i = L[br] ; i <= R[br] ; i ++)
        if(A[i].id == r) rr = i;
    //------------Step 2：获取散块答案----------
    if(bl == br) { // 注意这里要判断一下两个在同一个块内的情况
        for(int i = L[bl] ; i <= R[bl] ; i ++) { //获取散块的答案
            if(A[i].id >= l && A[i].id <= r - 1 && A[i].val > A[rl].val) B1 ++;
            if(A[i].id >= l && A[i].id <= r - 1 && A[i].val < A[rl].val) S1 ++;
            if(A[i].id >= l + 1 && A[i].id <= r && A[i].val > A[rr].val) B2 ++;
            if(A[i].id >= l + 1 && A[i].id <= r && A[i].val < A[rr].val) S2 ++;
        }
        int flag = 0; 
        if(A[rl].val < A[rr].val) flag = 1;
        else flag = -1;
        Ans = Ans + B1 - S1 + S2 - B2 + flag;
        return ;
    }
    for(int i = L[bl] ; i <= R[bl] ; i ++) { //获取散块的答案
        if(A[i].id >= l && A[i].id <= r - 1 && A[i].val > A[rl].val) B1 ++;
        if(A[i].id >= l && A[i].id <= r - 1 && A[i].val < A[rl].val) S1 ++;
        if(A[i].id >= l + 1 && A[i].id <= r && A[i].val > A[rr].val) B2 ++;
        if(A[i].id >= l + 1 && A[i].id <= r && A[i].val < A[rr].val) S2 ++;
    }
    for(int i = L[br] ; i <= R[br] ; i ++) {
        if(A[i].id >= l && A[i].id <= r - 1 && A[i].val > A[rl].val) B1 ++;
        if(A[i].id >= l && A[i].id <= r - 1 && A[i].val < A[rl].val) S1 ++;
        if(A[i].id >= l + 1 && A[i].id <= r && A[i].val > A[rr].val) B2 ++;
        if(A[i].id >= l + 1 && A[i].id <= r && A[i].val < A[rr].val) S2 ++;
    }
    //-------------Step 3：采用块内二分的方法获取整块答案----------
    //Step:3.1 获取小于要交换的 l 对应的数的数量
    for(int i = pos[l] + 1 ; i <= pos[r] - 1 ; i ++) {
        int now = L[i];
        if(A[rl].val > A[R[i]].val) {S1 += R[i] - L[i] + 1; continue;}
        if(A[rl].val < A[L[i]].val) continue;
        for(int j = log2(R[i] - L[i] + 1) ; j >= 0 ; j --) {
            int t = now + (1 << j);
            if(t <= R[i] && A[t].val < A[rl].val) now = t;
        }
        S1 += now - L[i] + 1;
    }
    //Step:3.2 获取大于要交换的 l 对应的数的数量
    for(int i = pos[l] + 1 ; i <= pos[r] - 1 ; i ++) {
        int now = R[i];
        if(A[rl].val > A[R[i]].val) continue;
        if(A[rl].val < A[L[i]].val) {B1 += R[i] - L[i] + 1; continue;}
        for(int j = log2(R[i] - L[i] + 1) ; j >= 0 ; j --) {
            int t = now - (1 << j);
            if(t >= L[i] && A[t].val > A[rl].val) now = t;
        }
        B1 += R[i] - now + 1;
    }
    //Step:3.3 获取小于要交换的 r 对应的数的数量
    for(int i = pos[l] + 1 ; i <= pos[r] - 1 ; i ++) {
        int now = L[i];
        if(A[rr].val > A[R[i]].val) {S2 += R[i] - L[i] + 1; continue;}
        if(A[rr].val < A[L[i]].val) continue;
        for(int j = log2(R[i] - L[i] + 1) ; j >= 0 ; j --) {
            int t = now + (1 << j);
            if(t <= R[i] && A[t].val < A[rr].val) now = t;
        }
        S2 += now - L[i] + 1;
    }
    //Step:3.4 获取大于要交换的 r 对应的数的数量
    for(int i = pos[l] + 1 ; i <= pos[r] - 1 ; i ++) {
        int now = R[i];
        if(A[rr].val > A[R[i]].val) continue;
        if(A[rr].val < A[L[i]].val) {B2 += R[i] - L[i] + 1; continue;}
        for(int j = log2(R[i] - L[i] + 1) ; j >= 0 ; j --) {
            int t = now - (1 << j);
            if(t >= L[i] && A[t].val > A[rr].val) now = t;
        }
        B2 += R[i] - now + 1;
    }
    //--------------Step 4 更新答案---------------
    // 答案的表达式为 Ans = Ans + B1 - S1 + S2 - B2
    int flag = 0;
    if(A[rl].val < A[rr].val) flag = 1;
    else flag = -1;
    Ans = Ans + B1 - S1 + S2 - B2 + flag;
    return ;
}

int main() {
    n = read(), m = read();
    for(int i = 1 ; i <= n ; i ++)
        A[i].id =  A[i].val = i;
    block = (int)(sqrt(n)) + 1;
    while(R[num] != n) {
        num ++;
        L[num] = R[num - 1] + 1;
        R[num] = min(n, block * num);
        for(int i = L[num] ; i <= R[num] ; i ++)
        pos[i] = num;
    }
    for(int i = 1 ; i <= m ; i ++) {
        int l = read(), r = read();
        if(l > r) swap(l, r);
        if(l != r) Get(l, r), change(l, r);
        printf("%lld\n", Ans);
    }
    return 0;
}
```

---

## 作者：raincity (赞：0)

需要单点修改，查询一个数区间有多少个数小于这个数。

遇事不决先分块，假设分 $B$ 个块。

对于每一个块，记录不大于每一个数的数有多少个。

那么查询之前/之后有多少个块，可以将块内残余部分暴力计算，别的使用记录好的答案。

单点修改，也就是将当前块记录的答案区间修改。

所以对于记录的答案，需要区间修改，单点查询，可以使用树状数组。

单次修改：$O(\log N)$

单次查询：$O(B\log N+\dfrac{N}{B})$

让 $B\log N=\dfrac{N}{B}$，也就是 $B=\sqrt{\dfrac{N}{\log N}}$ 的时候时间复杂度最小。

总时间复杂度：$O(M\sqrt{N\log N})$

好在时间有 4 s，复杂度上好像是 $3.6\times 10^8$，常数应该不大，大概能过的样子。

然而空间爆炸了...

然后我发现 $B=\sqrt{N}$ 的时候不会爆炸。

然后 A 了。

发现 CF feature：`fread` 比 `getchar` 慢，而且理论上 $B=\sqrt{\dfrac{N}{\log N}}$ 时间复杂度最低，但是事实上好像并不是 /yiw 

貌似 $B=\sqrt N$ 更快一些？~~松松松卡常~~

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int N = 200005, B = 455;
int n, m, tree[B][N], b, t, L[B], R[B], in[N], a[N];
long long ans;

inline void add(int pos, int val, int id) {
	while (pos <= n) {
		tree[id][pos] += val;
		pos += pos & (-pos);
	}
}

inline int sum(int pos, int id) {
	int res = 0;
	while (pos) {
		res += tree[id][pos];
		pos &= pos - 1;
	}
	return res;
}

inline int query(int l, int r, int val) {
	int bl = in[l], br = in[r], res = 0;
	if (bl + 1 >= br) {
		for (register int i = l; i <= r; i++) res += a[i] <= val;
		return res;
	}
	for (register int i = bl + 1; i < br; i++) res += sum(val, i);
	for (register int i = l; i <= R[bl]; i++) res += a[i] <= val;
	for (register int i = L[br]; i <= r; i++) res += a[i] <= val;
	return res;
}

inline void modify(int pos, int val) {
	add(val, 1, in[pos]);
	add(a[pos], -1, in[pos]);
}

inline void read(int &ret) {
	char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	ret = 0;
	while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0', ch = getchar();
}

inline void makeblock() {
	b = sqrt(n), t = (b + n - 1) / b;
	for (register int i = 1; i <= t; i++) {
		L[i] = R[i - 1] + 1, R[i] = min(L[i] + b - 1, n);
		for (register int j = L[i]; j <= R[i]; j++) in[j] = i, a[j] = j, add(j, 1, i);
	}
}

int main() {
	read(n), read(m);
	makeblock();
	while (m--) {
		int x, y;
		read(x), read(y);
		if (x > y)
			swap(x, y);
		if (x ^ y) {
			if (a[x] > a[y])
				ans--;
			else
				ans++;
			ans -= (query(x + 1, y - 1, a[x]) - query(x + 1, y - 1, a[y])) * 2;
			modify(x, a[y]), modify(y, a[x]);
			swap(a[x], a[y]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

#### THE END



---

## 作者：Genius_Z (赞：0)

[$\Large \color{Green}{Blog}$](http://geiz-revive.github.io/)

题意 ：对于一个长度为$n$$(n\le 200000)$的序列进行$q$$(q \le 50000)$次操作，每次操作都是交换序列中的某两个数。对于每一个操作，回答当前序列中有多少个逆序对。

本题是一个三维偏序问题，所求即为满足$pos_i>pos_j 且 val_i<val_j$$或$$pos_i<pos_j 且 val_i>val_j$的$(i,j)$​的对数。

我们考虑每次交换操作，可以拆成两个删除和两个插入，先减去贡献，然后在原位置删除，再交换两个值的$pos$，之后在新位置插入，再加上现在的贡献，这样就做完了$......$吗？

写出来会发现样例都过不了，原因是我们在这样处理时会额外计算一些贡献

- 当交换后这两个数产生了一对逆序对时，$ans$- -
- 当交换后这两个数减少了一对逆序对时，$ans$++

因为当交换后产生了一对逆序对时，加贡献会把这一对加两遍，同理减少了一对时减贡献会减两遍。

然后就是上树状数组套动态开点权值线段树，时空复杂度均是$\Theta(nlog^2_n)$

$\Large Code:$

```cpp
#pragma region revive
#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#define inl inline
#define re register int
#define fa(x) t[x].fa
#define son(x,y) t[x].child[y]
#define ls(x) t[x].child[0]
#define rs(x) t[x].child[1]
#define ll long long
const int inf = 0x3f3f3f3f;
#define lowbit(x) ((x) & (-x))
using namespace std;
#ifndef _DEBUG
#define getchar() (*(IOB.in.p++))
#define putchar(c) (*(IOB.out.p++)=(c))
#define io_eof() (IOB.in.p>=IOB.in.pend)
struct IOBUF { struct { char buff[1 << 26], *p, *pend; }in; struct { char buff[1 << 26], *p; }out; IOBUF() { in.p = in.buff; out.p = out.buff; in.pend = in.buff + fread(in.buff, 1, 1 << 26, stdin); }~IOBUF() { fwrite(out.buff, 1, out.p - out.buff, stdout); } }IOB;
#endif
template<typename IO>
inl void write(IO x) {
	if (x == 0) return (void)putchar('0');
	if (x < 0)putchar('-'), x = -x;
	static char buf[30];
	char* p = buf;
	while (x) {
		*(p++) = x % 10 + '0';
		x /= 10;
	}
	while (p > buf)putchar(*(--p));
}
inl void writestr(const char *s) { while (*s != 0)putchar(*(s++)); }
template<typename IO>inl void writeln(IO x) { write(x), putchar('\n'); }
template<typename IO>inl void writesp(IO x) { write(x), putchar(' '); }
inl int readstr(char *s) {
	char *begin = s, c = getchar();
	while (c < 33 || c>127) {
		c = getchar();
	}
	while (c >= 33 && c <= 127) {
		*(s++) = c;
		c = getchar();
	}
	*s = 0;
	return s - begin;
}
template<typename IO>
inl IO read() {
	IO x = 0;
	register bool w = 0;
	register char c = getchar();
	while (c > '9' || c < '0') {
		if (c == '-') w = 1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + (c ^ 48);
		c = getchar();
	}
	return w ? -x : x;
}
#pragma endregion
#undef ls
#undef rs
#define ls(x) t[x].l
#define rs(x) t[x].r
int root[1000001], cnt, pos[1000001], tmpl[51], tmpr[51], cntl, cntr, n;
struct node {
	int w, l, r;
}t[20000001];
inl void maintain(int x) {
	t[x].w = t[ls(x)].w + t[rs(x)].w;
}
inl void change(int &k, int l, int r, int p, int w) {
	if (!k)k = ++cnt;
	if (l == r)return (void)(t[k].w += w);
	re mid = l + r >> 1;
	if (p <= mid)change(ls(k), l, mid, p, w);
	else change(rs(k), mid + 1, r, p, w);
	maintain(k);
}
inl int query(int l, int r, int x, bool op) {
	cntl = cntr = 0;
	for (re i = l - 1; i; i -= lowbit(i)) tmpl[++cntl] = root[i];
	for (re i = r; i; i -= lowbit(i))tmpr[++cntr] = root[i];
	l = 1, r = n;
	re mid, ans = 0;
	while (l != r) {
		mid = l + r >> 1;
		if (x <= mid) {
			if (op) {
				for (re i = 1; i <= cntl; i++)ans -= t[rs(tmpl[i])].w;
				for (re i = 1; i <= cntr; i++)ans += t[rs(tmpr[i])].w;
			}
			for (re i = 1; i <= cntl; i++)tmpl[i] = ls(tmpl[i]);
			for (re i = 1; i <= cntr; i++)tmpr[i] = ls(tmpr[i]);
			r = mid;
		}
		else {
			if (!op) {
				for (re i = 1; i <= cntl; i++)ans -= t[ls(tmpl[i])].w;
				for (re i = 1; i <= cntr; i++)ans += t[ls(tmpr[i])].w;
			}
			for (re i = 1; i <= cntl; i++)tmpl[i] = rs(tmpl[i]);
			for (re i = 1; i <= cntr; i++)tmpr[i] = rs(tmpr[i]);
			l = mid + 1;
		}
	}
	return ans;
}
signed main() {
	n = read<int>();
	re m = read<int>(), x, y;
	ll ans = 0;
	for (re i = 1; i <= n; i++) {
		pos[i] = i;
		for (re j = i; j <= n; j += lowbit(j)) change(root[j], 1, n, i, 1);
	}
	while (m--) {
		x = read<int>(), y = read<int>();
		if (x == y) {
			writeln(ans);
			continue;
		}
		ans -= query(1, pos[x] - 1, x, 1) + query(pos[x] + 1, n, x, 0);
		ans -= query(1, pos[y] - 1, y, 1) + query(pos[y] + 1, n, y, 0);
		for (re i = pos[x]; i <= n; i += lowbit(i))change(root[i], 1, n, x, -1);
		for (re i = pos[y]; i <= n; i += lowbit(i))change(root[i], 1, n, y, -1);
		swap(pos[x], pos[y]);
		for (re i = pos[x]; i <= n; i += lowbit(i))change(root[i], 1, n, x, 1);
		for (re i = pos[y]; i <= n; i += lowbit(i))change(root[i], 1, n, y, 1);
		ans += query(1, pos[x] - 1, x, 1) + query(pos[x] + 1, n, x, 0);
		ans += query(1, pos[y] - 1, y, 1) + query(pos[y] + 1, n, y, 0);
		ans -= (pos[x] > pos[y] && x < y) || (pos[x] < pos[y] && x > y);
		ans += (pos[x] > pos[y] && x > y) || (pos[x] < pos[y] && x < y);
		writeln(ans);
	}
}
```



---

## 作者：ThinkofBlank (赞：0)

## 			    题解 CF785E 【Anton and Permutation】

## ​一.闲谈

听说本题分块可以过而且吊打树套树？orz。。。我果然还是太菜了。。。

## 二.分析

### 1.求逆序对

简化题目:给出序列1-n，以及m个操作，每次交换两个数，求当前序列的逆序对数

如果,交换的两个数相同，我们直接输出当前答案即可，那么其他的情况呢？

**假设，我们知道交换前的逆序对数，那么新序列的逆序对数便等于原逆序对数加上两个数交换后的贡献**

那么，我们来考虑如何计算两个数交换的贡献

**我们设两个数分别为x和y,我们再设find_max(l,r,x)表示区间l->r内比x大的数的个数，find_min(l,r,x)同理，再设a[x]表示x的位置**

那么交换后，与x，y有关的逆序对为(注:这里a[x]与a[y]尚未交换,且以下不考虑x与y形成的逆序对):

find_max(1,a[y]-1,x)+find_min(a[y]+1,n,x)+find_max(1,a[x]-1,y)+find_min(a[x]+1,n,y)

那么我们加上这个答案就好了吗？

不对！思考下，交换前，可能有与x,y有关的逆序对，**如果我们直接加上当前的逆序对的话，我们就可能重复计算了！**所以，我们还需要把答案减去交换前的与x,y有关的逆序对数,即:

find_max(1,a[x]-1,x)+find_min(a[x]+1,n,x)+find_max(1,a[y]-1,y)+find_min(a[y]+1,n,y)

然后，我们再来考虑x,y形成的逆序对:

交换后，x与y有两个情况:

#### 1.x与y形成一个逆序对:

我们直接将答案加一即可

#### 2.x与y不形成逆序对，原逆序对消失:

那么，我们是否需要将答案减一呢？

不是的，因为，我们一开始，不是减去了与x,y有关的逆序对数嘛？**这时，我们在x里减去了逆序对(x,y)，又在y里减去了逆序对(x,y)，而我们本来只需要减一次的却减了两次！所以我们也需要将答案加一！**

所以，两种情况的处理方式是相同的！

### 2.求函数find_min、find_max

现在，我们已经知道如何求逆序对了，但是，我们还需要知道如何求find_min、find_max两个函数，我们首先考虑优秀的权值线段树，然而，全局线段树并不擅长区间，于是我们启用它的升级版:主席树，然后我们就可以轻松地求出来了，不过，我们这时，发现，我们还有交换操作没用，如果，我们写普通的主席树，我们就需要对a[x]>a[y]的每一个主席树都修改一遍，这时，我们再给它升级一下:我们用带修主席树来解决这些问题！

至于交换操作，我们可以如此理解:

**将a[x]位置上的x修改成y，将a[y]位置上的y修改成x,之后我们再把a[x]与a[y]交换一下就可以了！**

复杂度：O(mloglogn*巨大常数(雾))

## 三.优化

这题甚为毒瘤的一点在于:卡空间

经过试验(类似方法)，开long long的直接凉

开int 2e7会MLE,开1e7会Re

于是我~~愤怒之下~~，写了一个垃圾回收，然后空间开成1e7+5e6才过的QwQ

**注意:写垃圾回收时，不要把root[i]回收了，因为我们还需要查询值之类的操作。。。**

## 四.代码

```c++
//#pragma GCC optimize()//手动Ox优化
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+5e6;
struct node{
    int val,lson,rson;
}t[N];
int n,m;
int a[N];
int siz,root[N];
int Now[N],Pas[N],L,R;
int sta[N],top;
inline int lowbit(int x){
    return x&-x;
}
inline int news(){
    if(top){
        return sta[top--];
    }
    return ++siz;
}
inline void delt(int x){
    sta[++top]=x;
}
//垃圾回收 
inline void mest(int x){
    t[x].lson=t[x].rson=t[x].val=0;
}
inline void insert(int &now,int l,int r,int x){
    if(!now){
        now=news();
        mest(now);
    }
    t[now].val++;
    if(l==r){
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid){
        insert(t[now].lson,l,mid,x);
    }else{
        insert(t[now].rson,mid+1,r,x);
    }
}
inline int find_Max(int l,int r,int lc,int rc){
    int sum=0,tot=0;
    for(int i=1;i<=L;++i){
        sum-=t[Pas[i]].val;
        tot-=t[t[Pas[i]].rson].val;
    }
    for(int i=1;i<=R;++i){
        sum+=t[Now[i]].val;
        tot+=t[t[Now[i]].rson].val;
    }
    if(lc<=l&&r<=rc){
        return sum;
    }
    int mid=(l+r)>>1;
    if(rc<=mid){
        for(int i=1;i<=L;++i){
            Pas[i]=t[Pas[i]].lson;
        }
        for(int i=1;i<=R;++i){
            Now[i]=t[Now[i]].lson;
        }
        return find_Max(l,mid,lc,rc);
    }
    if(lc>mid){
        for(int i=1;i<=L;++i){
            Pas[i]=t[Pas[i]].rson;
        }
        for(int i=1;i<=R;++i){
            Now[i]=t[Now[i]].rson;
        }
        return find_Max(mid+1,r,lc,rc);
    }
    for(int i=1;i<=L;++i){
        Pas[i]=t[Pas[i]].lson;
    }
    for(int i=1;i<=R;++i){
        Now[i]=t[Now[i]].lson;
    }
    return find_Max(l,mid,lc,rc)+tot;
}
inline int find_Min(int l,int r,int lc,int rc){
    int sum=0,tot=0;
    for(int i=1;i<=L;++i){
        sum-=t[Pas[i]].val;
        tot-=t[t[Pas[i]].lson].val;
    }
    for(int i=1;i<=R;++i){
        sum+=t[Now[i]].val;
        tot+=t[t[Now[i]].lson].val;
    }
    if(lc<=l&&r<=rc){
        return sum;
    }
    int mid=(l+r)>>1;
    if(rc<=mid){
        for(int i=1;i<=L;++i){
            Pas[i]=t[Pas[i]].lson;
        }
        for(int i=1;i<=R;++i){
            Now[i]=t[Now[i]].lson;
        }
        return find_Min(l,mid,lc,rc);
    }
    if(lc>mid){
        for(int i=1;i<=L;++i){
            Pas[i]=t[Pas[i]].rson;
        }
        for(int i=1;i<=R;++i){
            Now[i]=t[Now[i]].rson;
        }
        return find_Min(mid+1,r,lc,rc);
    }
    for(int i=1;i<=L;++i){
        Pas[i]=t[Pas[i]].rson;
    }
    for(int i=1;i<=R;++i){
        Now[i]=t[Now[i]].rson;
    }
    return find_Min(mid+1,r,lc,rc)+tot;
}
inline int find_min(int l,int r,int x){
    if(!r){
        return 0;
    } 
    if(x==1){
        return 0;
    } 
    int now=l-1;
    L=R=0;
    while(now){
        Pas[++L]=root[now];
        now-=lowbit(now);
    }
    now=r;
    while(now){
        Now[++R]=root[now];
        now-=lowbit(now);
    }
    return find_Min(1,n,1,x-1);
}
inline int find_max(int l,int r,int x){//寻找l-r区间内，比x大的数
    if(l==n+1){
        return 0;
    }
    if(x==n){
        return 0;
    }
    int now=l-1;
    L=R=0;
    while(now){
        Pas[++L]=root[now];
        now-=lowbit(now);
    }
    now=r;
    while(now){
        Now[++R]=root[now];
        now-=lowbit(now);
    }
    return find_Max(1,n,x+1,n);
}
inline void delted(int now,int l,int r,int x){
    t[now].val--;
    if(l==r){
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid){
        delted(t[now].lson,l,mid,x);
        if(!t[t[now].lson].val){
            delt(t[now].lson);
            t[now].lson=0;
        }
        return;
    }else{
        delted(t[now].rson,mid+1,r,x);
        if(!t[t[now].rson].val){
            delt(t[now].rson);
            t[now].rson=0;
        }
    }
}
inline void change(int t,int x,int y){//将t位置的x修改为y 
    int now=t;
    while(now<=n){
        delted(root[now],1,n,x);
        insert(root[now],1,n,y);
        now+=lowbit(now);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        a[i]=i;
        int now=i;
        while(now<=n){
            insert(root[now],1,n,i);
            now+=lowbit(now);
        }
    }
    long long ans=0;
    while(m--){
        int x,y;
        scanf("%d%d",&x,&y);
        if(x>y){
            swap(x,y);
        }
        if(x==y){
            printf("%lld\n",ans);
            continue;
        }
        ans-=(find_max(1,a[x]-1,x)+find_min(a[x]+1,n,x));
        ans-=(find_max(1,a[y]-1,y)+find_min(a[y]+1,n,y));
        ans+=(find_max(1,a[y]-1,x)+find_min(a[y]+1,n,x));
        ans+=(find_max(1,a[x]-1,y)+find_min(a[x]+1,n,y));
        ans++;
        change(a[x],x,y),change(a[y],y,x);
        swap(a[x],a[y]);
        printf("%lld\n",ans);
    }
    return 0;
}
```





---

## 作者：PragmaGCC (赞：0)

考虑分块

使用vector，在边角处暴力求，块中暴力

单个块一般来说就开$\sqrt {N}$就好了

code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 200005;
typedef long long ll;
#define fd(a, b) find(f[a].begin(), f[a].end(), b) - f[a].begin()
#define lb(a, b) lower_bound(f[a].begin(), f[a].end(), b)
#define ub(a, b) upper_bound(f[a].begin(), f[a].end(), b)
#define st(a) sort(f[a].begin(), f[a].end())
int N, B, Q;
int a[maxn];
ll tot;
vector<int> f[maxn];
void init() {
    B = sqrt(N);
    for (int i = 1; i <= N; i++) {
        a[i] = i;
        f[i / B].push_back(i);
    }
}
void change(int &fx, int &fy, int &x, int &y, int &k, int &l, int &r) { //修改
    x = a[l], y = a[r];
    fx = l / B, fy = r / B;
    k = fd(fx, x);
    f[fx][k] = y;
    st(fx);
    k = fd(fy, y);
    f[fy][k] = x;
    st(fy);
}
ll query(int l, int r) {
    if (l == r)
        return 0;
    int fx, fy, x, y, k;
    change(fx, fy, x, y, k, l, r);
    int res = 0, ch = 1;
    if (x > y) { // x>y，相当于考虑x<y之后取相反数
        ch = -1; //乘上-1相当于取相反数
        swap(x, y);
    }
    if (fx != fy) {
        for (int i = l + 1; i < (fx + 1) * B; i++)
            if (x < a[i] && a[i] < y)
                res++;
        for (int id = fx + 1; id < fy; id++)
            res += ub(id, y) - lb(id, x);
        for (int i = fy * B; i < r; i++)
            if (x < a[i] && a[i] < y)
                res++;
    } else {
        for (int i = l + 1; i <= r - 1; i++) {
            if (x < a[i] && a[i] < y)
                res++;
        }
    }
    swap(a[l], a[r]);
    return (2 * res + 1) * ch;
}
int main() {
    ios::sync_with_stdio(false);
    cin >> N >> Q;
    init();
    int l, r;
    ll ans = 0;
    while (Q--) {
        cin >> l >> r;
        if (l > r)
            swap(l, r);
        ans += query(l, r); // ans“增加”了多少对
        cout << ans << endl;
    }
}
```

---

