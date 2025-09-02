# Lemper Cooking Competition

## 题目描述

Pak Chanek is participating in a lemper cooking competition. In the competition, Pak Chanek has to cook lempers with $ N $ stoves that are arranged sequentially from stove $ 1 $ to stove $ N $ . Initially, stove $ i $ has a temperature of $ A_i $ degrees. A stove can have a negative temperature.

Pak Chanek realises that, in order for his lempers to be cooked, he needs to keep the temperature of each stove at a non-negative value. To make it happen, Pak Chanek can do zero or more operations. In one operation, Pak Chanek chooses one stove $ i $ with $ 2 \leq i \leq N-1 $ , then:

1. changes the temperature of stove $ i-1 $ into $ A_{i-1} := A_{i-1} + A_{i} $ ,
2. changes the temperature of stove $ i+1 $ into $ A_{i+1} := A_{i+1} + A_{i} $ , and
3. changes the temperature of stove $ i $ into $ A_i := -A_i $ .

Pak Chanek wants to know the minimum number of operations he needs to do such that the temperatures of all stoves are at non-negative values. Help Pak Chanek by telling him the minimum number of operations needed or by reporting if it is not possible to do.

## 说明/提示

For the first example, a sequence of operations that can be done is as follows:

- Pak Chanek does an operation to stove $ 3 $ , $ A = [2, -2, 1, 4, 2, -2, 9] $ .
- Pak Chanek does an operation to stove $ 2 $ , $ A = [0, 2, -1, 4, 2, -2, 9] $ .
- Pak Chanek does an operation to stove $ 3 $ , $ A = [0, 1, 1, 3, 2, -2, 9] $ .
- Pak Chanek does an operation to stove $ 6 $ , $ A = [0, 1, 1, 3, 0, 2, 7] $ .

There is no other sequence of operations such that the number of operations needed is fewer than $ 4 $ .

## 样例 #1

### 输入

```
7
2 -1 -1 5 2 -2 9```

### 输出

```
4```

## 样例 #2

### 输入

```
5
-1 -2 -3 -4 -5```

### 输出

```
-1```

# 题解

## 作者：MatrixCascade (赞：10)

全复刻 noip2021。

我们看到这个操作，发现：   
1. 全体数的和不变
2. 同一个位置操作两次等于没操作

这引导我们去想差分、前缀和，然后发现每次操作相当于**交换相邻两个的前缀和**。并且不能交换最后两个。

然后就是冒泡排序的最少交换次数，逆序对即可。无解的情况很容易，前 $n-1$ 项中的某一项 $>sum_n$ 或者 $<0$ 就是无解。

然后就做完了。

---

## 作者：xhhhh36 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1725L)

可以根据题意来推一下性质，设前缀和数组 $s_i$ 为 $a_1$ 到 $a_i$ 的和，分析操作对 $s$ 数组的影响。

首先 $a_{i-1}+a_i\to a_{i-1}$ 相当于 $s_{i-1}+a_i=s_i\to s_{i-1}$，然后 $a_{i+1}+a_i\to a_{i+1}$ 和 $-a_i\to a_i$ 相当于 $s_{i}+a_i-2\times a_i=s_i-a_i\to s_i$。而 $s_{i+1}+a_i-2\times a_i+a_i=s_{i+1}\to s_{i+1}$，同理 $s$ 数组中的其他数也不变。

所以每一次对 $i$ 操作就相当于将前缀和数组中的 $s_{i-1}$ 和 $s_i$ 交换。由于要序列中的元素都处于非负值，所以要通过操作使 $s$ 数组单调不减，那么最少操作次数就是逆序对个数，可以用树状数组维护。又因为 $2\le i \le n-1$，所以无解的情况就是 $s_n$ 不为 $s$ 数组中的最大数或者 $s$ 数组中存在负数。

# AC code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int lson,rson,sum;
}t[10000005];
int n,rt,cnt;
long long ans;
void update(int &u,int dot,int l,int r)
{
	if (!u)
	{
		u=++cnt;
	}
	t[u].sum++;
	if (l==r) return;
	int mid=(l+r)/2;
	if (mid>=dot) update(t[u].lson,dot,l,mid);
	else update(t[u].rson,dot,mid+1,r);
}
long long query(int &u,int l,int r,int L,int R)
{
    if (L>r||R<l) return 0;
	if (!u) u=++cnt;
	if (L>=l&&R<=r)
	{
		return t[u].sum;
	}
	int mid=L+R>>1;
	return query(t[u].lson,l,r,L,mid)+query(t[u].rson,l,r,mid+1,R);
}
int sum[100005];
signed main()
{
	cin>>n;
	int mx=0;
	for (int i=1;i<=n;i++)
	{
		cin>>sum[i];
		sum[i]+=sum[i-1];
		if (sum[i]<0)
		{
			cout<<"-1"<<endl;
			return 0;
		}
		mx=max(mx,sum[i]);
	}
	if (mx!=sum[n])
	{
		cout<<"-1"<<endl;
		return 0;
	}
	for (int i=1;i<=n;i++)
	{
		int x=sum[i];
		long long tmp=query(rt,x+1,1e14,0,1e14);
		update(rt,x,0,1e14);
		ans+=tmp;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：lowbit (赞：2)

操作 3 可以看做 $A_i\to A_i-A_i\times 2$。

于是我们得到性质：

**每次操作后所有数的总和不变**。

$\!$

考虑前缀和数组 $S$，发现操作后 $S_{i-1}\to S_{i-1}+A_i=S_i$，$S_i\to S_i-A_i=S_{i-1}$。

即操作相当于**交换前缀和数组中相邻两个位置的值**。

要求 $A_i\ge0$，等同 $S$ 不降。于是问题转化为冒泡排序的最少交换次数，答案即为逆序对个数，可以用[树状数组](https://www.luogu.com.cn/problem/P1908)求。

注意到我们不能交换 $S_{n-1}$ 和 $S_n$，所以 $S_n$ 必须是最大的。同时 $S$ 中不能有负数。这两种情况特判无解即可。

---

## 作者：toolong114514 (赞：1)

# CF1725L Lemper Cooking Competition 题解
## 题面大意
[原题传送门](https://www.luogu.com.cn/problem/CF1725L)。
## 解题思路
尝试分析题目中操作的性质。

记修改前的 $A$ 序列前 $i$ 个数的前缀和为 $sum_i$(特别地，我们认为 $sum_0$ 有意义，且值为 $0$)，修改后的 $A$ 为 $A'$，修改后的前缀和序列为 $sum'$。

则对位置 $i$ 进行一次操作后，$A'_{i-1}=A_{i-1}+A_i,A'_i=-A'_i,A'_{i+1}=A_i+A_{i+1}$。

同时将前缀和表示出来：$sum_{i-1}=sum_{i-2}+A_{i-1},sum_{i}=sum_{i-2}+A_{i-1}+{A_i},sum_{i-1}=sum_{i+2}+A_{i-1}+A_i+A_{i+1}$。

显然，操作后，$sum'_{0,1,\cdots,i-2}$ 均不变。

由此可得：
$$sum'_{i-1}=sum'_{i-2}+A'_{i-1}=sum_{i-2}+A'_{i-1}=A_{i-1}+A_i=sum_i$$

$$sum'_{i}=sum'_{i-2}+A'_{i-1}+A'_i=sum_{i-2}+A_{i-1}+A_i-A_i=sum_{i-2}+A_{i-1}=sum_{i-1}$$

$$sum'{i+1}=sum'_{i-2}+A'_{i-1}+A'_i+A'_{i+1}=sum_{i-2}+A_{i-1}+A_i-A_i+A_i+A_{i+1}=sum_{i-2}+A_{i-1}+A_i+A_{i+1}=sum_{i+1}$$

由前缀和的定义可知，$sum_{i+1,i+2,\cdots,n}$ 也不变。

根据如上推导，我们可以总结出操作的性质：

每次对 $i$ 的操作，等价于交换前缀和数组的 $sum_{i-1}$ 和 $sum_i$。 

明确操作性质后，我们可以制定策略：通过冒泡排序的交换使整个 $sum$ 数组单调不递减，且相邻差分值均为非负数。

无解的条件：

1. $sum$ 数组存在负数。容易证明，无论把负数元素挪到哪里，都会有至少一个还原为 $A$ 的元素为负值。
2. $sum_n$ 不是最大值。根据题面，操作的 $i$ 满足条件：$ 2 \le i \le N-1$。如果最后一个 $sum$ 的值不是最大，不能交换，必然使还原的 $A$ 中存在负数。

判完无解后，最小操作次数，即为对 $sum$ 进行冒泡排序（升序）的最小次数，也就是原始 $sum$ 中的逆序对个数。

根据以上策略，编写代码即可。

## 参考代码
```cpp
#include<iostream>
using namespace std;
#define int long long
const int N=1e5+10;
int a[N],b[N];
int n,ans;
void sort(int l,int r){
	if(l==r) return;
	int mid=(l+r)/2;
	sort(l,mid);
	sort(mid+1,r);
	int i=l,j=mid+1,tmp=l;
	while(i<=mid&&j<=r){
		if(a[i]>a[j]){
			b[tmp]=a[j];
			j++;
			ans+=mid-i+1;
		}else{
			b[tmp]=a[i];
			i++;
		}
		tmp++;
	}
	while(i<=mid){
		b[tmp++]=a[i];
		i++;
	}
	while(j<=r){
		b[tmp++]=a[j];
		j++;
	}
	for(i=l;i<=r;i++){
		a[i]=b[i];
	}
} 
signed main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i]+=a[i-1];
	} 
	for(int i=1;i<n;i++){
		if(a[i]>a[n]||a[i]<0){
			cout<<"-1";
			return 0;
		}
	}
	if(a[n]<0){
		cout<<"-1";
		return 0;
	} 
	sort(1,n);
	cout<<ans;
	return 0;
}
```
[本代码可以通过 CF 的评测](https://www.luogu.com.cn/record/158573363)。

Written by [toolong114514](https://www.luogu.com.cn/user/477821) on 2024/5/10.

---

## 作者：_edge_ (赞：1)

来一篇啥也发现不了的题解。>_< 

我菜死了。

容易发现，每次操作负数肯定是比较优秀的，于是可以得到一种策略即为从左往右遇到负数就进行操作，然后重复上述过程。

于是我们写出了一个暴力的代码，但是复杂度太高了过不去。

考虑这个操作的本质是啥，相当于是把负数移到前面，然后继续操作。

移动的次数即为其答案。

然后，我们来手玩一下这个操作。

$a_1,a_2,a_3,a_4,a_5,a_6$ 

如果说 $a_6$ 需要换到前面的话，可以直接操作它，那么 …… 在操作若干次之后就是可以得到。

$a_1,a_2,a_3,a_4,a_5+a_6,-a_6$

再来一次得到了

$a_1,a_2,a_3,a_4+a_5+a_6,-a_5-a_6,a_5$

再继续操作之后得到了

$a_1,a_2,a_3+a_4+a_5+a_6,-a_4-a_5-a_6,a_4,a_5$。

然后你会发现，当前如果从 $i$ 操作到 $j$，那么如果 $\sum \limits _{k=j}^i a_k \ge 0$ 那么就不操作了，然后观察一下，前一项刚好是 $- \sum \limits _{k=j+1}^i a_k$。

后面的即为前面的区间平移一下。

然后问题就变成了查找后缀和第一个大于等于 $0$ 的位置，然后单点插入。

随便上一个 FHQ 就解决了。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e6+5;
mt19937 rnd(114514);
int ans;
struct FHQ{
    #define ls(x) lson[x]
    #define rs(x) rson[x]
    int sum[INF],sum2[INF],sz[INF],lson[INF],rson[INF],sum3[INF],tot,rt;
    int add(int x) {++tot;sum2[tot]=rnd();sum[tot]=x;sum3[tot]=x;sz[tot]=1;return tot;}
    void split(int x,int &y,int &z,int xx) {
        if (!x) {y=z=0;return ;}
        if (sz[ls(x)]+1<=xx) y=x,split(rs(x),rs(x),z,xx-sz[ls(x)]-1);
        else z=x,split(ls(x),y,ls(x),xx);
        sz[x]=sz[ls(x)]+sz[rs(x)]+1;
        sum[x]=sum[ls(x)]+sum[rs(x)]+sum3[x];
    }
    void mer(int &x,int y,int z) {
        if (!y || !z) {x=y+z;return ;}
        if (sum2[y]>sum2[z]) x=z,mer(ls(x),y,ls(x));
        else x=y,mer(rs(x),rs(x),z);
        sz[x]=sz[ls(x)]+sz[rs(x)]+1;
        sum[x]=sum[ls(x)]+sum[rs(x)]+sum3[x];
    }
    void ins(int x,int y) {
        int now=add(x);
        mer(rt,rt,now);
        // cout<<rt<<" qwe?\n";
    }
    void add2(int x,int y) {
        int xx=0,yy=0,zz=0;
        split(rt,xx,yy,x);
        split(yy,zz,yy,1);
        sum[zz]+=y;sum3[zz]+=y;
        mer(yy,zz,yy);
        mer(rt,xx,yy);
    }
    int solve3(int x,int y) {
        if (!x) return 0;
        // cout<<sum[x]<<" "<<sum[ls(x)]<<" "<<sum[rs(x)]<<" "<<sz[x]<<" "<<sz[ls(x)]<<" "<<rs(x)<<" "<<y<<" qweqwe?\n";
        if (rs(x) && sum[rs(x)]>=y) return solve3(rs(x),y)+sz[ls(x)]+1;
        else if (sum[x]-sum[ls(x)]>=y) return sz[ls(x)]+1;
        else return solve3(ls(x),y-(sum[x]-sum[ls(x)]));
    }
    void solve2(int x) {
        int xx=0,aa=0,bb=0,cc=0;

        int rrt=0;
        split(rt,rt,rrt,1);
        split(rrt,xx,rrt,x);

        int j=solve3(xx,0);
        ans+=x-j;
        // cout<<x<<" "<<j<<" qweqwe?\n";
        // cout<<j<<" "<<rs(2)<<" "<<sum[3]<<" "<<sum[2]<<" "<<ls(2)<<" qwejqwie\n";
        
        split(xx,aa,bb,j);
        int sum2=sum[bb];
        split(bb,bb,cc,sz[bb]-1);
        sum[cc]=-sum2;sum3[cc]=-sum2;
        mer(bb,cc,bb);
        mer(xx,aa,bb);
        mer(rrt,xx,rrt);
        mer(rt,rt,rrt);
        add2(j,sum2);
    }
}T1;
int n,a[INF];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    int sum=0;
    for (int i=1;i<=n;i++) {
        sum+=a[i];
        if (sum<0) {cout<<"-1\n";return 0;}
    }
    
    sum=0;
    for (int i=n;i;i--) {
        sum+=a[i];
        if (sum<0) {cout<<"-1\n";return 0;}
    }

    T1.rt=1;T1.tot=1;
    T1.sum2[T1.rt]=-1;

    for (int i=1;i<=n;i++) T1.ins(a[i],i);

    for (int i=1;i<=n;i++) { // at!!!!!!!!!!!!!!!!!!!
        if (a[i]<0) {
            a[i+1]+=a[i];
            T1.add2(i+1,a[i]);
            T1.solve2(i);
        }
    }

    // int ans=0;
    // for (int i=1;i<=n;i++) {
    //     if (a[i]<0) {
    //         a[i+1]+=a[i];
    //         int sum2=0;
    //         for (int j=i;j;j--) {
    //             if (sum2+a[j]>=0) {
    //                 a[j]+=sum2;
    //                 for (int k=i;k>j;k--) a[k]=a[k-1];
    //                 a[j+1]=-sum2;
    //                 break;
    //             }
    //             sum2+=a[j];
    //             ans++;
    //         }
    //     }
    // }
    cout<<ans<<"\n";
    return 0;
}
```


---

## 作者：Elairin176 (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1725L)   
## 题意
定义一次操作为依次执行以下内容：  
- 选定一个满足 $2\le i<n$ 的整数 $i$。
- 令 $a_{i-1}\gets a_{i-1}+a_i$。
- 令 $a_{i+1}\gets a_{i+1}+a_i$。
- 令 $a_i\gets-a_i$。

现在进行若干次操作，求将 $a$ 的每个元素都变为非负的操作次数。无解输出 `-1`。   
## 解法
我们观察题面的三步操作，容易注意到执行完操作后整个数组的前缀和不变。   
我们令 $s$ 为 $a$ 的前缀和数组，那么我们可以把操作转化为交换 $s_i$ 和 $s_{i-1}$。让原数组非负就是让 $s$ 递增且没有负数。       
于是本题就转化为了求逆序对数。无解的两种情况：   
- $s$ 中存在负数。
- $s_n$ 不是最大值。因为 $s_n$ 不能参与交换。

CODE：   
```cpp
//luogu paste jo5j6ogx
cst int N=1e5;
int n,b[N+10],m;
ll s[N+10],a[N+10],ans;
umap<ll,int>mp;
il void add(int x,int y){
	while(x<=m){
		b[x]+=y;
		x+=lowbit(x);
	}
}
il int sum(int x){
	int s=0;
	while(x){
		s+=b[x];
		x-=lowbit(x);
	}
	ret s;
}
il int sum(int l,int r){ret sum(r)-sum(l-1);}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	n=read<int>();
	for(int i=1;i<=n;i++){
		a[i]=s[i]=s[i-1]+read<ll>();
		if(s[i]<0){
			write(-1);ret 0;
		}
	}
	for(int i=1;i<n;i++){
		if(s[i]>s[n]){
			write(-1);ret 0;
		}
	}
	sort(a+1,a+n);
	m=unique(a+1,a+n)-a-1;
	for(int i=1;i<=m;i++) mp[a[i]]=i;
	for(int i=1;i<n;i++){
		s[i]=mp[s[i]];
		ans+=sum(s[i]+1,m);
		add(s[i],1);
	}
	write(ans);
	ret 0;
}
```
[Record(Codeforces)](https://codeforces.com/contest/1725/submission/300573336)

---

## 作者：ast123 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/CF1725L)
****
模拟题目给的操作，不难发现操作后序列的和不变。考虑前缀和 $sum[i]$，经过一次变换后，$sum[i-1]$ 变为 $sum[i-1]+a[i]=sum[i]$（这里的 $sum[i]$ 和后面的 $sum[i-1]$ 都是指变换前的），而 $sum[i]$ 变为 $sum[i]-a[i] \times 2+a[i]=sum[i]-a[i]=sum[i-1]$，所以从前缀和的角度来看，一次操作相当于将一组相邻的 $sum[i]$ 与 $sum[i-1]$ 对调 $(2  \le i < n)$。

存储数组的前缀和，问题就变成了：通过对调相邻的 $sum[i]$ 和 $sum[i-1] (2 \leq i < n)$，使得 $sum$ 数组单调不减且 $sum[i]$ 非负，如果可行，输出最少的对调次数，否则输出 $-1$。对于判断是否可行，可以先排序求出前缀和数组的最小值和最大值，如果最小值 $<0$，那么不可行。在前面对调的操作中，$2 \le i < n$，所以前缀和的第 $n$ 项不会移动。如果前缀和的第 $n$ 项不等于最大值，那么不可行。

判断完是否可行后，就考虑如何求至少操作的次数了。显然这是一个求逆序对总数的问题，可以用归并排序，也可以用树状数组或线段树。我用的是树状数组，注意这里的 $sum[i]$ 很大，需要离散化，这就是为什么前面说排序求出最小值和最大值，而不是直接 $O(n)$ 扫一遍整个数组。

[洛谷](https://www.luogu.com.cn/record/157816171)

---

## 作者：COsm0s (赞：0)

设 $b_i$ 为 $a_i$ 的前缀和数组。

显然当 $b$ 中出现负数时，无解。

那么题目所给操作即可转化为：

+ $b_{i-1}\to b_{i-1}+a_i$ 即 $b_i$。

+ $b_i\to b_i-a_i$ 即 $b_{i-1}$。

也就是说，在前缀和意义上，操作就相当于将相邻两项交换。

当 $\forall a_i\geq0$ 时，容易发现 $b$ 数组为非严格上升序列。

那么我们要在最少的操作次数中使 $b$ 不降，即求出 $b$ 的逆序对即可。

再次注意到 $n - 1, n$ 无法交换，那么如果 $b_n$ 不是 $\max b_i$，那么同样无解。

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DOW(i, r, l) for (int i = (r); i >= (l); -- i)
#define int long long
using namespace std;
namespace COsm0s {
	const int N = 1e5 + 5;
	int n, ans, maxn, a[N], c[N];
	void qsort(int l, int r){
		if(l == r) return ;
		int mid = (l + r) / 2;
		int i = l, j = mid + 1, k = l;
		qsort(l, mid);
		qsort(mid + 1, r);
		while(i <= mid && j <= r)
			if(a[i] <= a[j]) c[k ++] = a[i ++];
				else c[k ++] = a[j ++], ans += mid - i + 1;
		while(i <= mid) c[k ++] = a[i ++];
		while(j <= r) c[k ++] = a[j ++];
		for(int x = l; x <= r; x ++) a[x] = c[x];
	}
	int main() {
		cin >> n;
		REP(i, 1, n) {
			cin >> a[i];
			a[i] += a[i - 1];
			if(a[i] < 0) cout << "-1", exit(0);
			maxn = max(maxn, a[i]);
		}
		if(maxn > a[n]) cout << -1, exit(0);
		qsort(1, n);
		cout << ans << '\n';
		return 0;
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) COsm0s::main();
	return 0;
}
```


---

## 作者：SamHJD (赞：0)

## [Lemper Cooking Competition](https://www.luogu.com.cn/problem/CF1725L)

### 题意

每次操作选择一个位置 $i$，使两边的位置加上 $a_i$，然后 $a_i$ 变为其相反数。

求最少的操作次数，满足所有数非负。

---

### 解法

观察到做一次操作序列的和不变，更严谨的说 $[1,i-2],[i+1,n]$ 的前缀和均不变。

记 $s_i=\sum\limits_{i=1}^{i}a_i$。则 $s_{i-1}$ 变为 $s_{i-1}+a_i$，即 $s_i$。$s_i$ 变为 $s_i-2a_i$，即 $s_{i-1}$。操作的实质即为交换两个位置的前缀和。

若所有数非负，则需满足前缀和单调不降，树桩数组求逆序对即可。

无解仅当 $\min\limits_{i=1}^{n}(s_i)<0$，或者 $\max\limits_{i=1}^{n-1}(s_i)>s_n$。

注意值域很大，需要对前缀和离散化处理。

---

### [代码](https://codeforces.com/contest/1725/submission/242649909)

---

## 作者：lucktains (赞：0)

首先分析三个操作：

第三个操作 $a_i\gets-a_i$ 相当于 $a_i\gets a_i-2a_i$。

前后修改容易想到前缀和。这三个操作在前缀和数组里就相当于交换 $a_i$ 和 $a_{i - 1} $，在 $i=n$ 时不能交换，所以直接求逆序对就行了。
## AC Code
```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
long long n, a[100010], ans, b[100010], sum = LLONG_MIN;
void merge(int l, int r) {
	if (l == r)return;
	int mid = l + r >> 1;
	merge(l, mid);
	merge(mid + 1, r);
	int i = l, j = mid + 1, k = l;
	while (i <= mid && j <= r) {
		if (a[i] <= a[j]) {
			b[k++] = a[i];
			i++;
		}
		else {
			b[k++] = a[j];
			j++;
			ans += mid - i + 1;
		}
	}
	while (i <= mid)b[k++] = a[i++];
	while (j <= r)b[k++] = a[j++];
	for (int i = l; i <= r; i++) {
		a[i] = b[i];
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i] += a[i - 1];
		sum = max(sum, a[i]);
		if (a[i] < 0) {
			cout << -1;
			return 0;
		}
	}
	if (a[n] < sum) {
		cout << -1;
		return 0;
	}
	merge(1, n);
	cout << ans;
}
```

---

## 作者：111101q (赞：0)

### 前缀和，树状数组维护


------------

注意到任何操作都不会改变整体的和，以及每一次操作都相当于交换两个数的前缀和，然后注意到无解条件：

$1.$ $s$ 数组中有负数，放在前面的任何地方都无法实现单调性

$2.$ $s$ 数组中有数据小于前面的最大值

下面附上树状数组维护程序：程序复杂度：$O(n\operatorname{log}n)$
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
ll n,a[N],sum[N],c[N],top,ans,s[N],flag;
int lowbit(int x){return x&(-x);}
void insert(int p,int v){
	for(;p<=N;p+=lowbit(p))
		c[p]+=v;
}
int query(int p){int ret=0;
	for(;p;p-=lowbit(p))
		ret+=c[p];
	return ret;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=sum[i]=s[i-1]+a[i];
		flag|=(s[i]<0);
	}
	for(int i=1;i<n;i++)if(sum[i]>sum[n])flag=1;
	if(flag){
		cout<<-1;
		return 0;
	}
	sort(sum+1,sum+n+1);
	top=unique(sum+1,sum+n+1)-sum-1;
	for(int i=1;i<=n;i++)
		s[i]=lower_bound(sum+1,sum+top+1,s[i])-sum;
	for(int i=1;i<=n;i++){
		ans+=i-1-query(s[i]);
		insert(s[i],1);
	}
	cout<<ans<<endl;
	//ACcode
}
```



---

## 作者：ReTF (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1725L)

### 题目描述
>有一个序列，可以进行若干次操作。
>
>在每一次操作里，可以选择第 $i$ 个元素（$ 2 \le i \le N-1$），然后执行以下操作：
>
>1. 把 $ A_{i-1}$ 变为 $A_{i-1} + A_{i}$。
>2. 把 $ A_{i+1}$ 变为 $A_{i+1} + A_{i}$。
>3. 把 $A_i$ 变为 $-A_i$。
>
>现在让你求执行的最少操作次数，以使序列的元素值都处于非负值。如果无解，请输出 $-1$ 。

### 题目分析

可以求出序列的前缀和数组 $s$。

我们发现每次操作后，$s_{i-1}$ 变成了 $a_1+a_2+\dots+a_i$，$s_i$ 变成了 $a_1+a_2+\dots+a_{i-1}$，$s_{i+1}$ 及后面的元素不变。

所以每次操作就是在交换 $s$ 数组中两个相邻的元素。

我们要求 $a$ 数组每个数非负，即 $s$ 数组单调不降。这是一个经典的问题，可以转化成 $s$ 数组的逆序对个数 $^{\dag}$。使用树状数组求解即可。

无解条件：

- $s$ 数组中有负数，令其中最小的负数为 $v$，则 $v$ 无论放在哪里都小于它前面的数，无法单调不降。

- $s_n$ 小于 $s_1\sim s_{n-1}$ 的最大值。注意到 $s_n$ 是不能和 $s_{n-1}$ 交换的。

[代码](https://codeforces.com/contest/1725/submission/220124729)

---
$^\dag$：存在一种最优策略，当且仅当存在 $i$ 使得 $s_{i-1}>s_i$ 时交换 $s_{i-1}$ 和 $s_{i}$。每次交换，逆序对个数就会减少 $1$，所以交换次数等于逆序对个数。

---

## 作者：_SeeleVollerei_ (赞：0)

考虑这个操作的本质是在位置 $i-1,i,i+1$ 分别 $+a_i,-2a_i,+a_i$，所以第一个结论就是所有数的和不会变。

遇到和不变考虑放到前缀和上考虑，相当于在位置 $i-1,i$ 上分别 $+a_i,-a_i$。

然后发现 $pre_i=pre_{i-1}+a_i,pre_{i-1}=pre_i-a_i$，所以这个操作本质上是一个交换相邻两个位置的前缀和的操作，然后要求排序，那么实际上就是模拟冒泡排序，就是求逆序对个数了。

或许会有人问这是怎么想出来的，我能给出来的回答就是**愣想**或者**运气好**。因为如果 adhoc 都有一个通用的流程的话就不叫 adhoc。不过这题有个可以参考的点就是遇到和的信息可以考虑放到前缀和上考虑，然而实际上数列的性质题可以经常考虑**前缀和**或**差分**。

应该不会有人蠢到不会判无解，所以不讲。

懒得离散化所以没写 BIT，直接写的归并排序。

https://codeforces.com/contest/1725/submission/170853780

---

