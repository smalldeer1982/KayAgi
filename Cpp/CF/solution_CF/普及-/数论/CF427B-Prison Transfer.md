# Prison Transfer

## 题目描述

The prison of your city has $ n $ prisoners. As the prison can't accommodate all of them, the city mayor has decided to transfer $ c $ of the prisoners to a prison located in another city.

For this reason, he made the $ n $ prisoners to stand in a line, with a number written on their chests. The number is the severity of the crime he/she has committed. The greater the number, the more severe his/her crime was.

Then, the mayor told you to choose the $ c $ prisoners, who will be transferred to the other prison. He also imposed two conditions. They are,

- The chosen $ c $ prisoners has to form a contiguous segment of prisoners.
- Any of the chosen prisoner's crime level should not be greater then $ t $ . Because, that will make the prisoner a severe criminal and the mayor doesn't want to take the risk of his running away during the transfer.

Find the number of ways you can choose the $ c $ prisoners.

## 样例 #1

### 输入

```
4 3 3
2 3 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 1 1
2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
11 4 2
2 2 0 7 3 2 2 4 9 1 4
```

### 输出

```
6
```

# 题解

## 作者：_Emiria_ (赞：4)

### [这里](https://www.cnblogs.com/Violet-Ever-Garden/p/14770669.html)观看效果更佳

相信大家都看得懂题意，所以就不再多说了。

为方便表示，下文中统一用 $n$ 表示囚犯总数，$t$ 表示囚犯犯罪水平应不高于 $t$， $c$ 表示要转移 $c$ 个连续的囚犯 。

由于这道题数据比较小~~可以乱搞~~，所以下面提供三种能过的做法。

------

### 0. 暴力

暴力地枚举每一个长度为 $c$ 的区间，求区间的最大值，统计符合题意的区间数量。

时间复杂度为 $O(n - c + 1) \times O(c)$ 约为 $n ^ 2$，妥妥 T 飞，就不放代码了。

------

### 1. 模拟

依据题意模拟即可。

线性的扫一遍，若当前的数字小于等于 $t$ ，则计数器 +1 ，否则计数器清空。

在线处理的话，可以将空间复杂度降到最小，时间复杂度为 $O(n)$。

```cpp
#include <cstdio>

int n, t, c, k, cnt, ans;

int main(){
    scanf("%d %d %d", &n, &t, &c);
    for(int i = 1; i <= n; i++){
	scanf("%d", &k);
	if(k <= t){
	    if(++cnt >= c) ans++; //囚犯数量足够，则开始累加答案
	}
	else cnt = 0; //若出现不满足的囚犯，则清空计数
    }
    printf("%d\n", ans);
    return 0;
}
```

------

### 2. 线段树

其实刚看题的时候我并没有想到线段树，后来发现 $n \le 2 \times 10^5$ 的数据实在是太宽松了。

我们只需要维护一段区间的最大值，然后进行 $n - c + 1$ 次区间查询即可，由于线段树单次区间查询的复杂度为 $O(\log n)$ ，所以复杂度约为 $O(n \log n)$ ，还是比较稳的。

```cpp
/*珂爱的线段树*/

#include <cstdio>
#include <algorithm>
#include <iostream>

#define maxn 200005

using namespace std;

int sum, n, T, c, a[maxn];

struct Tree_Node{
    int val, l, r;
}tr[maxn << 2]; //我一般习惯开 4 倍空间，防止越界

inline void update(int node){ //这个函数可以不写，直接放在 build 函数中
    tr[node].val = max(tr[node << 1].val, tr[node << 1 | 1].val);
}

void build(int s, int t, int node){
    tr[node].l = s, tr[node].r = t;
    if(s == t){tr[node].val = a[s]; return;}
    int mid = s + t >> 1;
    build(s, mid, node << 1);
    build(mid + 1, t, node << 1 | 1);
    update(node);
}

int ask_max(int s, int t, int node){ //查询区间最大值，与 t 比较
    int ans = 0;
    if(s <= tr[node].l && t >= tr[node].r){
        return tr[node].val;
    }
    int mid = tr[node].l + tr[node].r >> 1;
    if(s <= mid) ans = max(ans, ask_max(s, t, node << 1));
    if(t > mid) ans = max(ans, ask_max(s, t, node << 1 | 1));
    return ans;
}

int main(){
    scanf("%d %d %d", &n, &T, &c);
    for(int i = 1; i <= n; i++){
	scanf("%d",&a[i]);
    }
    build(1, n, 1);
    for(int i = 1; i + c - 1 <= n; i++){
	if(ask_max(i, i + c - 1, 1) <= T) sum++; // 查询每一个长度为 c 的区间
    }
    printf("%d",sum);
    return 0;
}
```

------

### 3. 分块

请再思考一下 $2 \times 10^5$ 的数据还能支持什么样的时间复杂度呢？

显然，复杂度为 $O(n \sqrt{n})$ 的分块常数别太大也是能过的。~~（大家应该都会分块吧）~~

```cpp
/*分块大法*/

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int block, num, n, t, c, ans; 
// block : 块长 , num : 块的数量 , ans : 最终的答案，即有几个长度为 c 的区间满足条件 ;
int belong[200005], a[200005];
// belong[i] 记录下表为 i 的点在哪个块中。
int l[1005], r[1005], maxx[1005];
// l[i] 记录第 i 个块左边界的下标， r[i] 记录第 i 个块右边界的下标；
// maxx[i] 表示第 i 个块的最大值。

inline void build(){
    block = sqrt(n);
    num = n / block;
    if(n % block) num++;
    for(int i = 1; i <= n; i++){
        belong[i] = (i - 1) / block + 1;
    }
    for(int i = 1; i <= num; i++){
        l[i] = block * (i - 1) + 1,
        r[i] = block * i;
    }
    r[num] = n;
    for(int i = 1; i <= num; i++){
        for(int j = l[i]; j <= r[i]; j++){
            maxx[i] = max(a[j], maxx[i]);
        }
    }
}

inline int ask_max(int x, int y){
    int maxn = -1;    // maxn 用于记录查询的这个区间的最大值
    /*处理整块的部分*/
    for(int i = belong[x] + 1; i < belong[y]; i++){
        maxn = max(maxn, maxx[i]);
    }
    /*处理非整块的部分*/
    if(belong[x] != belong[y]){
        for(int i = x; i <= r[belong[x]]; i++){
            maxn = max(maxn, a[i]);
        }
        for(int i = l[belong[y]]; i <= y; i++){
            maxn = max(maxn, a[i]);
        }
    }
    else{
        for(int i = x; i <= y; i++){
            maxn = max(maxn, a[i]);
        }
    }
    return maxn;
}

signed main(){
    scanf("%d %d %d", &n, &t, &c);
    for(int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    build();
    for(int i = 1; i + c - 1 <= n; i++){
        if(ask_max(i, i + c - 1) <= t) ans++; //查询每个长度为 c 的区间的最大值。
    }
    printf("%d\n", ans);
    return 0;
}

```
-----
### 后记

我是真没想到分块和线段树差不多快，可能我人傻常数大吧。


---

## 作者：王熙文 (赞：3)

看到题解区没有人用 st 表就来交一发。

## 题意

有一个长度为 $n$ 的序列，求连续的 $c$ 个数最大值不超过 $t$ 的方案数。

$1 \le c \le n \le 2 \times 10^5,0 \le t \le 10^9$

**注意**：输入时先输入 $n$ 再输入 $t$ 最后才输入 $c$！

## 思路

考虑暴力枚举每一个区间，判断区间最大值是否小于等于 $t$。如果是，答案加一。

求区间最大值有很多方法，这篇题解使用了 st 表的做法来求区间最大值。

st 表的具体操作就不细讲了，可以看代码的注释。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int st[20][200010]; // 定义 st[i][j] 表示从 j 位置，向右 2^i 个数，这一段的区间最大值。区间就是 [j,j+(1<<i)-1]

int main()
{
	int n,t,c,cnt=0;
	cin>>n>>t>>c;
	int log_2=log2(c);
	for(int i=1; i<=n; ++i)
	{
		cin>>st[0][i]; // 区间 [i,i+1-1] 的最大值就是 i 本身，直接输入
	}
	for(int i=1; i<=17; ++i) // 枚举区间长度 (1<<i)
	{
		for(int j=1; j+(1<<i)-1<=n; ++j) // 枚举左端点
		{
			st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
			// 区间 [j,j+(1<<i)-1] 可以被分为两段区间，它们覆盖了 [j,j+(1<<i)-1]
			// 它们是 [j,j+(1<<(i-1))-1],[j+(1<<(i-1)),j+(1<<i)-1]
			// 左面区间的最大值就是 st[i-1][j]
			// 右面区间的最大值就是 st[i-1][j+(1<<(i-1))]
		}
	}
	for(int i=1; i+c-1<=n; ++i) // 暴力枚举长度为 c 的区间
	{
		cnt+=(max(st[log_2][i],st[log_2][i+c-1-(1<<log_2)+1])<=t);
		// 现在要查区间 [i,i+c-1] 的最大值
		// 这个区间可以被分成两个长度为二的幂区间
		// [i,i+log2(c)-1] 和 [i+c-1-(1<<log2(c))+1,i+c-1]
		// 这两个区间都包含在大区间里，它们可能重叠，但是区间最大值重叠了也没关系
		// 于是这两个区间的最大值就是 st[log2(c)][i] 和 st[log2(c)][i+c-1-(1<<log2(c))+1]
		// 这个大区间的最大值就是这两个小区间最大值它们的最大值
	}
	cout<<cnt;
	return 0;
}
```

---

## 作者：MurataHimeko (赞：3)


## CF427B


------------

### 思路

连续 $c$ 个囚犯的最大犯罪水平不高于 $t$，我们很容易想到使用线段树来维护区间最大值，每次判断当前第 $i \sim  (i+c-1)$ 个数值的最大值是否大于 $t$ 即可。  
 
-----------
 
### 一点小优化
 
以上是这道题目的思路，笔者这里再提供一些优化的技巧：

1.  如果上一轮的第 $(i-1) \sim  (i+c-2)$ 个数值都不大于 $t$，那我们只需要判断当前第 $i+c-1$ 个数值是否大于 $t$ 即可。

2.  查找最大值的 query 函数的类型改为 bool ，表示该区间内的最大数值是否大于 $t$。如果当前区间的最大值已经大于 $t$，就没有必要再遍历子区间。

----------------------------------------

### 关于笛卡尔树

因为笔者是求区间最值做这个题的，显然也可以用笛卡尔树来做这道题，不过常数比线段树大了些。   


首先我们可以构造出一棵每个节点的编号满足二叉搜索树的性质
 ，每个节点的权值满足大根堆的性质的一棵二叉树，代码如下：
 
 ```cpp
for(register int i(1); i <= n; ++i) {
        head = pos;
        read(tr[i].val);
        while(head && tr[st[head]].val <= tr[i].val) head--;
        if(head) tr[st[head]].son[2] = i;
        if(head^pos) tr[i].son[1] = st[head+1];
        st[pos = ++head] = i;
    }
```



------------

然后的话，笛卡尔树具有一个关键性质：**一段区间的最值等于笛卡尔树上区间边界 l 和 r 节点的 lca**。所以我们在这颗笛卡尔树上做一遍树链剖分就能快速求出 lca 从而得知区间最值了。


------------



### 笛卡尔树代码

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define max_(a, b) a > b ? a : b
#define min_(a, b) a < b ? a : b
#define INF 0x3f3f3f3f

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;

const int maxn = 2e5+1;
int n, t, c, root, max_son, ans;
int st[maxn], head, pos;

struct node {
    int son[3], val;
}tr[maxn];

int dep[maxn], siz[maxn], son[maxn], fath[maxn];

void dfs_1(int u, int fa) {
    dep[u] = dep[fa]+1;
    fath[u] = fa;
    siz[u] = 1;
    max_son = -1;
    for(register int i(1); i <= 2; ++i) {
        if(!tr[u].son[i]) continue;
        int v = tr[u].son[i];
        dfs_1(v, u);
        siz[u] += siz[v];
        if(siz[v] > max_son) {
            max_son = siz[v];
            son[u] = v;
        }
    }
}

int top[maxn];

void dfs_2(int u, int topf) {
    top[u] = topf;
    if(!son[u]) return ;
    dfs_2(son[u], topf);
    for(register int i(1); i <= 2; ++i) {
        if(!tr[u].son[i]) continue;
        int v = tr[u].son[i];
        if(v == son[u]) continue;
        dfs_2(v, v);
    }
}

int lca(int x, int y) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) std::swap(x, y);
        x = fath[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

bool flag = 0;

int main() {
    read(n), read(t), read(c);
    for(register int i(1); i <= n; ++i) {
        head = pos;
        read(tr[i].val);
        while(head && tr[st[head]].val <= tr[i].val) head--;
        if(head) tr[st[head]].son[2] = i;
        if(head^pos) tr[i].son[1] = st[head+1];
        st[pos = ++head] = i;
    }
    root = st[1];
    dfs_1(root, 0);
    dfs_2(root, root);
    int k = n - c + 1;
    for(register int i(1); i <= k; ++i) {
        if(flag) {
            if(tr[i+c-1].val <= t) ans++;
            else flag = 0;
        }
        else {
            int tmp = lca(i, i+c-1);
            if(tr[tmp].val <= t) ans++, flag = 1;
        }
    }
    write(ans);
}
```



------------

### 线段树代码





```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define max_(a, b) a > b ? a : b
#define min_(a, b) a < b ? a : b

namespace IO {
char buf[1<<21], *p1 = buf, *p2 = buf, buf1[1<<21];
inline char gc () {return p1 == p2 && (p2 = (p1 = buf) + fread (buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;}

#ifndef ONLINE_JUDGE
#endif

template<class I>
inline void read(I &x) {
    x = 0; I f = 1; char c = gc();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = gc(); }
    while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = gc(); }
    x *= f;
}

template<class I>
inline void write(I x) {
    if(x == 0) {putchar('0'); return;}
    I tmp = x > 0 ? x : -x;
    if(x < 0) putchar('-');
    int cnt = 0;
    while(tmp > 0) {
        buf1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while(cnt > 0) putchar(buf1[--cnt]);
}

#define in(x) read(x)
#define outn(x) write(x), putchar('\n')
#define out(x) write(x), putchar(' ')

} using namespace IO;

int n, t, c;
int val[200003];
bool flag;

struct node {
    int l, r, maxn;
}tr[4000003];

void build (int p, int l, int r) {
    tr[p].l = l, tr[p].r = r;
    if(l == r) {tr[p].maxn = val[l]; return ;}
    int m = l + r >> 1;
    build(p<<1, l, m);
    build(p<<1|1, m+1, r);
    tr[p].maxn = max_(tr[p<<1].maxn, tr[p<<1|1].maxn);
}

bool query (int p, int l, int r) {
    if(l <= tr[p].l && tr[p].r <= r) return (tr[p].maxn <= t);
    int m = (tr[p].l + tr[p].r) >> 1;
    if(l <= m) if(!(query(p<<1, l, r))) return 0;
    if(r > m) if(!(query(p<<1|1, l, r))) return 0;
    return 1;
}

int ans;

int main () {
    read(n), read(t), read(c);
    for(register int i(1); i <= n; ++i) read(val[i]);
    build(1, 1, n);
    int k = n - c + 1;
    flag = 0;
    for(register int i(1); i <= k; ++i) {
        if(flag) {
            if(val[i+c-1] <= t) ans++;
            else flag = 0;
        } 
        else {
            if(query(1, i, i+c-1)) ans++, flag = 1;
        }
    }
    write(ans);
    return 0;
}
```


------------

谢谢您能阅读本篇文章！


---

## 作者：Ptilopsis_w (赞：2)

# 题意
给定一个长度为 $n$ 数列 $a$ 、区间长度 $c$ 、和一个值 $t$ ，询问有多少个区间的最大值不超过 $t$

# 思路
**我只是个蒟蒻什么数据结构啥的都不会，所以我就直接模拟了**  
首先我们可以枚举每个区间，然后遍历每个区间，判断最大值，但是这样会妥妥的T飞掉，只能用其他方法  
我在模拟样例的时候发现，这个题非常类似于滑动窗口，然后我就有思路了  
我们可以先让 `前c-1个数和他们的下标` 入队，然后判断哪些数大于 $t$ ，再开一个队列 $q1$ 记录所有队列里**大于 $t$ 的元素在数组中的下标**  
然后就是滑动窗口式维护队列，每次入队一个元素，判断 $q1$ 是否为空，若为空说明这个区间符合，`ans++`，若不为空就略过，最后输出`ans`即可

#代码
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> Pair;//自定义类型，个人习惯
int n, t, c, ans;
int a[200005];
queue<Pair> q;//记录每个窗口的元素, first为值, second为下标
queue<int> q1;//记录窗口中所有大于t的元素的下标

int main()
{
    scanf("%d%d%d", &n, &t, &c);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for(int i = 1; i < c; i++)
    {//先让前c-1个元素和下标入队
        q.push(make_pair(a[i], i));
        if(a[i] > t)//如果入队的元素大于t, 就把下标push进q1里
            q1.push(i);
    }
    for(int i = c; i <= n; i++)
    {//到第c个元素时区间长度变为c, 开始判断

        q.push(make_pair(a[i], i));//跟上面一样的入队操作
        if(a[i] > t)
            q1.push(i);

        if(q1.empty())//q1为空说明队列里所有元素都大于t
            ans++;
            
        if(q.front().second == q1.front())
            q1.pop();//若当前即将出队的元素的下标和q1中队首元素相等,
                     //即为同一个元素，一起出队
        q.pop();
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：yzh_Error404 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF427B)
### 题意

给你$n$个数，求其中长度为$c$且值都小于$t$的子串个数

### 题解

#### 1.朴素模拟

很自然的可以想到模拟

在读入的同时记录当前这个元素**所在子串**的长度

用样例三举例：

初始状态为

![](https://cdn.luogu.com.cn/upload/image_hosting/fqunx3nc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

当遇到大于$t$的元素时子串长度重新开始计数

最后分成的子串和子串长度为

![](https://cdn.luogu.com.cn/upload/image_hosting/583couz1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

不难发现，每一个子串($len \ge c$)中都含有$len-c+1$个答案

在每次找到子串的结尾时累加即可

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,c;
int len,ans;//len为当前子串长度，ans为子串总个数
int main()
{
	scanf("%d%d%d",&n,&t,&c);
	for(register int i=1;i<=n;i++)
	{
		int op;
		scanf("%d",&op);
		if(op>t)//遇到的元素大于t
		{
			if(len>=c)ans+=(len-c+1);//如果子串长度大于c就累加答案
			len=0;
		}
		else len++;
	}
	if(len>=c)ans+=(len-c+1);//最后把没有累加的子串加上
	printf("%d",ans);
	return 0;
}
```

#### 2.~~线段树~~

看到题目中子串中的值**都小于**$t$时，窝还想到了线段树求区间最大值，当一个子串的区间最大值小于等于$t$，这个子串就一定满足条件

代码：

~~这个辣鸡线段树连修改都没有~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int SIZE=200005;
struct node
{
	int l,r;
	int dat;
}tr[SIZE*4];
int n,t,c;
int ans;
int a[SIZE];
inline void build(int p,int l,int r)//建树
{
	tr[p].l=l,tr[p].r=r;
	if(l==r)
	{
		tr[p].dat=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	tr[p].dat=max(tr[p*2].dat,tr[p*2+1].dat);
}
inline int ask(int p,int l,int r)//询问区间最大值
{
	if(l<=tr[p].l&&r>=tr[p].r)return tr[p].dat;
	int mid=(tr[p].r+tr[p].l)>>1;
	int val=-(1<<30);
	if(l<=mid)val=max(val,ask(p*2,l,r));
	if(r>mid)val=max(val,ask(p*2+1,l,r));
	return val;
}
int main()
{
	scanf("%d%d%d",&n,&t,&c);
	for(register int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	for(register int i=1;i<=n-c+1;i++)
		if(ask(1,i,i+c-1)<=t)ans++;//询问子串是否合法
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Halberd_Cease (赞：1)

枚举区间肯定会爆炸，所以我们按题目要求模拟。

由于是连续部分，我们用一个变量来表示到这个犯人的极大数量，如果大于 $c$ 答案就加一，如果这个犯人的危险度高了就清零变量，否则加一。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main()
{
    int n,t,c;
    cin>>n>>t>>c;
    int ans=0;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        if(x<=t)cnt++;
        else cnt=0;
        if(cnt>=c)ans++;
    }
    cout<<ans;
}
```

---

## 作者：荷叶下 (赞：1)

## 题意
##### 给出$n$个数,从中选出$c$个小于$t$的数
##### 求总共有多少种情况
---
## 思路
##### ~~模拟~~
##### 遍历整个序列,符合条件就记录下来
##### 如果囚犯严重程度大于$t$
##### 即不符条件,则重置为0
---
## 代码
```cpp
#include <bits/stdc++.h> //陋习
using namespace std ;
int read_() //快读优化
{
	int s = 0 , w = 1 ;
	char ch = getchar() ;
	while( ch == ' ' || ch == '\n' )
		ch = getchar() ;
	while( ch < '0' || ch > '9' )
	{
		if( ch == '-' )
			w = -1 ;
		ch = getchar() ;
	}
	while( ch >= '0' && ch <= '9' )
	{
		s = s * 10 + ch - '0' ;
		ch = getchar() ;
	}
	return s * w ;
} 
void print_( int x ) //快写优化
{
	if( x < 0 )
	{
		x = -x ;
		putchar( '-' ) ;
	}
	if( x > 9 )
		print_( x / 10 ) ;
	putchar( x % 10 + '0' ) ;
}
int n , c , t , sum , ans ;
int main()
{
    n = read_() ; t = read_() ; c = read_() ;
    for( int i = 1 ; i <= n ; ++i )
    {
        int x = read_() ;
        if( x <= t ) //符合条件就记录
        {
            ++sum ;
            if( sum >= c )
                ++ans ;
        }
        else //不符调节就重置
            sum = 0 ;
    }
    print_(ans) ;
    return 0 ;
}
```
[一遍AC](https://www.luogu.com.cn/record/41235692)
###### $LaTeX$可甄不戳


---

## 作者：shiroi (赞：0)

#### 题意简述

给定一个长度为 $n$ 的数列，询问有多少个长度为 $c$ 的子串使得子串序列中没有一个元素超过 $t$。

#### 题目分析

依据题意直接模拟即可。

从左向右遍历整个序列，每次记录一下当前符合条件的子串长度，如果不满足条件则置0。

代码实现相对比较简单。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0; int f=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}

int cur,ans;

int main(int argc, char const *argv[])
{
	int n=read(),t=read(),c=read();
	for (int i = 0; i < n; ++i)
	{
		int x=read();
		if(x<=t)
		{
			++cur;
			if(cur>=c) ++ans;
		}
		else cur=0;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：happybob (赞：0)

## 题意

给定序列 $a$，以及两个数 $c,t$，求 $\sum_{i=1}^{n-c+1} [(\max_{j=i}^{i+c-1} a_j) \leq t]$，即有多少个长度为 $c$ 的区间 $[l, r]$，满足这个区间最大值 $\leq t$。

$n \leq 2 \cdot 10^5$。 

## 解法

考虑暴力枚举每个区间，枚举的复杂度是 $O(n)$ 的，而每次要求最大值，复杂度 $O(n^2)$，无法承受。

但是，我们可以看到，区间最大值可以各种数据结构维护，例如分块或者线段树或者其他数据结构，分块是 $O(n \sqrt{n})$ 的复杂度，线段树是 $O(n \log n)$，当然也可以猫树或者 ST 表等。

另外也有一个 $O(n)$ 的解法，也就是滑动窗口。

线段树代码：

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 2e5 + 5;

int a[N];
int n, t, c, ans = 0;

class SegmentTree
{
public:
	struct Node
	{
		int l, r, maxn;
	}tr[N << 2];
	void push_up(int u)
	{
		tr[u].maxn = max(tr[u << 1].maxn, tr[u << 1 | 1].maxn);
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, -1 };
		if (l == r)
		{
			tr[u].maxn = a[l];
			return;
		}
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		push_up(u);
	}
	int query(int u, int l, int r)
	{
		if (tr[u].l >= l and tr[u].r <= r) return tr[u].maxn;
		int mid = tr[u].l + tr[u].r >> 1, res = -1;
		if (l <= mid) res = query(u << 1, l, r);
		if (r > mid) res = max(res, query(u << 1 | 1, l, r));
		return res;
	}
};

SegmentTree sg;

int main()
{
	scanf("%d%d%d", &n, &t, &c);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sg.build(1, 1, n);
	for (int i = 1; i <= n - c + 1; i++) ans += sg.query(1, i, i + c - 1) <= t;
	printf("%d\n", ans);
	return 0;
}
```


---

## 作者：李至擎 (赞：0)

[点我看题](https://www.luogu.com.cn/problem/CF427B)

题意：有一个长度为 $n$ 的数列，从中选出 $c$ 个小于 $t$ 的数，求总共有多少种情况。

思路：~~显然是模拟题，没什么好说的~~。在输入时找出符合条件的个数，就记录下来。如果囚犯严重程度大于 $t$ （不符条件），则重新计数。

方法：

- $1.$ 输入当前囚犯严重程度；

- $2.$ 如果严重程度小于 $t$ ，计数器 $+1$ ；

- $3.$ 反之，计算当前区间能有多少种可能方法，更新答案，计数器归零。

细节：

- $1.$ 当前找到的区间内的数的个数可能不及 $c$ 个；

- $2.$ 输入结束时，还有一个区间的答案储存在计数器中，要记得加上它。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,c,num,cnt,ans;//n、t和c如题意，num时当前罪犯的严重程度，cnt是计数器，ans是统计的答案 
int main()
{
	cin>>n>>t>>c;//输入 
	for(int i=1;i<=n;i++)
	{
		cin>>num;//输入严重程度 
		if(num>t)//如果大于t（不符条件） 
		{
			ans+=max(0,cnt-c+1);//更新答案
			//因为是加上了max(0,cnt-c+1)，所以不会出现加上负数，即长度小于c的可能 
			cnt=0;//计数器归零 
		}
		else//如果小于t（符合条件） 
		{
			cnt++;//计数器+1 
		}
	}
	cout<<ans+max(0,cnt-c+1);//记得加上最后一组答案 
	return 0;//结束程序 
}
```

---

## 作者：Level_Down (赞：0)

## 修订版

2020 / 7 / 31 将 “Just for fun”  中的代码改得更短了。
### 题意简述：

给定一个长度为 n 的数组，问其中有多少个连续的c个数每个数大小都不超过 t。

### 方法：

就拿样例三看吧，首先是一个数列：

11 4 2

2 2 0 7 3 2 2 4 9 1 4

我们可以在这个数列中从左往右找出连续的每个数大小都不超过 t 的数列：

2 2 0 ； 3 2 2 4 ； 1 4

然后我们对这三个子序列单独分析：

（1） 2 2 0，可以分成 2 个符合题目要求的数列；

（2） 3 2 2 4，可以分成 3 个符合题目要求的数列；

（3） 1 4，可以分成 1 个符合题目要求的数列；

对于这些数列，我们可以发现能分成的符合题目要求的数列是**原数列长度减 c 加 1**

所以最终答案就是 2 + 3 + 1 = 6 种。

但要注意一下，如果原数列长度减一比 c 还小，那就别管就行。

我们得出这份代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t,c,a,tt,ans;//tt是找到的数列（第一次）的长度 
int main()
{
	cin >> n >> t >> c;
	for (int i = 1; i <= n; i++) 
		{
			cin >> a;//这里可以边读入边判断 
			if (a > t) ans += max(0,tt - c + 1),tt = 0; else tt++;
			//如果输入的数不符合标准，答案增加，长度归零
			//注意是ans += max(0,tt - c + 1)而不是ans += tt - c + 1	
		}
	ans += max(0,tt - c + 1);//因为有可能最后的没增加循环就结束了，所以结束后还要加一句	
	cout << ans;//输出答案 
	return 0;//AC！	
}
```

就可以愉快地AC了！



------------

Just for fun:

```cpp
#include <bits/stdc++.h>
int n,t,c,a,tt,ans;int main(){scanf("%d%d%d",&n,&t,&c);for (int i = 1; i <= n; i++) {scanf("%d",&a);if (a > t) ans += std::max(0,tt - c + 1),tt = 0; else tt++;}ans += std::max(0,tt - c + 1);printf("%d",ans);return 0;}
```

两行秒蓝题，~~诶压行后怎么还变快不少？~~

---

