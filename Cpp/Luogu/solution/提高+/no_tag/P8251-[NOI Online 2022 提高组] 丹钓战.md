# [NOI Online 2022 提高组] 丹钓战

## 题目背景

**经过管理员的考虑，我们打算将民间数据单独存放在最后一个 Subtask 中。这些测试点分数均为 0 分，但是没有通过其中的任何测试点将会视为此题不通过。**

**这一题中出现了评测记录测试点编号错乱的问题，是民间数据命名方式冲突导致的。但是我们保证其相对顺序没有混乱。**

民间数据提供者：@Froggy。

## 题目描述

有 $n$ 个二元组 $(a_i, b_i)$，编号为 $1$ 到 $n$。

有一个初始为空的栈 $S$，向其中加入元素 $(a_i, b_i)$ 时，先不断弹出栈顶元素直至栈空或栈顶元素 $(a_j , b_j)$ 满足 $a_i \neq a_j$ 且 $b_i < b_j$，然后再将其加入栈中。

如果一个二元组入栈后栈内只有这一个元素，则称该二元组是“成功的”。

有 $q$ 个询问 $[l_i, r_i]$，表示若将编号在 $[l_i, r_i]$ 中的二元组按编号从小到大依次入栈，会有多少个二元组是“成功的”。

询问之间相互独立。

## 说明/提示

**【样例解释】**

以第一次询问 $[1, 4]$ 为例。

一开始栈为 $\{\}$。

加入 $1$ 号二元组后栈为 $\{(3, 10)\}$，栈中只有一个元素，该二元组是“成功的”。

加入 $2$ 号二元组 $(1, 10)$ 时，栈顶的 $(3, 10)$ 的 $b$ 值不大于 $2$ 号二元组的，因此弹栈。此时栈空，$2$
号二元组入栈，栈为 $\{(1, 10)\}$，该二元组是“成功的”。

加入 $3$ 号二元组 $(3, 2)$，此时栈顶元素与之 $a$ 值不同，$b$ 值比它更大，因而不需要弹栈，直接将 $3$ 号二元组入栈，栈为 $\{(1, 10),(3, 2)\}$，栈中有多个元素，该二元组不是“成功的”。

加入 $4$ 号二元组 $(1, 9)$，此时栈顶元素 $(3, 2)$ 的 $b$ 值比它小，弹栈。弹栈后栈顶元素 $(1, 10)$ 与
$(1, 9)$ 的 $a$ 值相同，继续弹栈。此时栈空，$4$ 号二元组入栈，栈为 $\{(1, 9)\}$，该二元组是“成功的”。共有 $3$ 个二元组是“成功的”，因而答案为 $3$。

**【样例 2,3,4】**

见附件 $\texttt{stack/stack*.in}$ 与 $\texttt{stack/stack*.ans}$。

链接：<https://pan.baidu.com/s/14XxLN63bxvpJAod81foGOg> 
提取码：gugu

**【数据范围与提示】**

对于所有测试点：$1 \leq n, q \leq 5 \times 10^5$，$1 \leq a_i, b_i \leq n$，$1 \leq l_i \leq r_i \leq n$。

每个测试点的具体限制见下表：

| 测试点编号   | 特殊性质        |
| ------------ | --------------- |
| $1 \sim 3$   | $n,q \leq 1000$ |
| $4 \sim 6$   | $n \leq 5000$   |
| $7 \sim 10$  | $n,q \leq 10^5$ |
| $11 \sim 12$ | $b_i=n-i+1$     |
| $13 \sim 15$ | $a_i=i$         |
| $16 \sim 20$ | 无              |

## 样例 #1

### 输入

```
10 4
3 1 3 1 2 3 3 2 1 1
10 10 2 9 7 5 4 7 6 1
1 4
7 8
7 10
1 8```

### 输出

```
3
2
2
3```

# 题解

## 作者：Yansuan_HCl (赞：101)

记第 $i$ 个二元组为 $P_i$。

对于一个区间 $[L, R]$ 按题意模拟，我们会先把 $P_L$ 入栈。对于下一个成功的二元组 $P_i$，它会把栈顶元素直到 $P_L$ 都弹出，再把自己压进去。以此类推，可以发现，每一个二元组要么被一个成功的二元组弹出去，要么留到末尾。

因此，可以记录每个二元组能被哪个二元组弹出去。按题意模拟即可。

```cpp
struct P { int a, b; };
// ...
static pair<P, int> s[500005];
int p = 0;
for (int i = 1; i <= n; ++i) {
	while(p && (s[p].first.a == f[i].a || s[p].first.b <= f[i].b)) {
		nxt[s[p].second] = i; // 记录这个二元组被谁弹出去了
		--p;
	}
	s[++p] = {f[i], i};
}
```

此后，对于区间 $[L, R]$，首先成功的是 $P_L$，之后被 $nxt[P_L]$ 弹出去； $nxt[P_L]$ 再被 $nxt[nxt[P_L]]$ 弹出去……以此类推，顺着 $nxt$ 跳，一直跳到序列尾或是区间外。对于每个询问复杂度为 $O(n)$。无法通过。

可以使用倍增对跳的过程进行优化。记录 $nxt[i][j]$ 表示从 $j$ 处跳了 $2^i$ 此，则可以做到预处理 $O(n\log n)$，询问 $O(\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T& s) {
	char c = getchar();
	T f = 1; s = 0;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		s = (s << 1) + (s << 3) + (c ^ 48);
		c = getchar();
	}
	s *= f;
}
const int N = 500005;
struct P{ int a, b; } f[N];

int n,q;
int nxt[21][N];

int main(){    
	read(n); read(q);
	for (int i = 1; i <= n; ++i) read(f[i].a);
	for (int i = 1; i <= n; ++i) read(f[i].b);

	static pair<P, int> s[500005]; int p = 0;
	for (int i = 1; i <= n; ++i) {
		while(p && (s[p].first.a == f[i].a || s[p].first.b <= f[i].b)) {
			nxt[0][s[p].second] = i;
			--p;
		}
		s[++p] = {f[i], i};
	}

    for (int i = 1; i <= 20; ++i) {
        for (int j = 1; j <= n; ++j)
            nxt[i][j] = nxt[i - 1][nxt[i - 1][j]]; // 处理倍增
    }
    
	while (q--){
		int cnt = 0;
		int l, r;
		read(l); read(r);
        for (int i = 20; i >= 0; --i) {
            if (nxt[i][l] && nxt[i][l] <= r) { // 向右跳，但不越过边界
                cnt += 1 << i; // 跳了 2^i 次
                l = nxt[i][l];
            }
        }
		printf("%d\n", cnt + 1); // 要算上 L 本身
	}
	return 0;
}
```

不需要任何高级数据结构。

---

## 作者：enucai (赞：26)

## Preface

这不是倍增吗？为什么要 主席树/BIT 呢？

## Analysis

令 $dp_{i,j}$ 表示从 $i$ 开始入栈，第 $2^j$ 个 成功的 二元组的编号。

通过一遍对题意得模拟我们可以求出对于所有的 $i$ 的 $dp_{i,0}$。即当 $i$ 把 $j$ 弹出时，记录 $dp_{j,0}=i$。

接着，预处理倍增数组，在 $O(n\log n)$ 的时间内求出所有的 $dp_{i,j}$。

对于每次询问，枚举 $i$ 从 $\log n$ 到 $0$，看当前位往后 $2^i$ 个 成功的 二元组的编号是否还在 $[l,r]$ 区间内（类似倍增求 LCA）。单次询问时间复杂度 $q\log n$。

最终时间复杂度 $O(n\log n+q\log n)$，可以通过本题。

## Code

**Talk is cheap, show me the code.**

奉上极简代码。

```cpp
// And in that light, I find deliverance.
#define int long long
int n,q,a[500010],b[500010],dp[500010][25];
int st[500010],top=0;
signed main(){
	read(n,q);
	For(i,1,n) read(a[i]);
	For(i,1,n) read(b[i]);
	For(i,1,n+1) dp[i][0]=n+1;
	For(i,1,n){
		while(top!=0&&(a[i]==a[st[top]]||b[i]>=b[st[top]])) dp[st[top]][0]=i,top--;
		st[++top]=i;
	}
	For(j,1,20) For(i,1,n+1) dp[i][j]=dp[dp[i][j-1]][j-1];
	while(q--){
		int l,r;
		read(l,r);
		int res=0,pos=l;
		Rof(i,20,0) if(dp[pos][i]<=r) pos=dp[pos][i],res+=(1<<i);
		write(res+1,'\n');
	}
}
```

---

## 作者：Jerrlee✅ (赞：20)

谨以此题解，纪念我第一次 NOIO TG 前 $25\%$。
## 题意
每次向栈中加入一个二元组 $(a_i,b_i)$，先不断弹出栈顶元素直至栈空或栈顶元素 $(a_j,b_j)$ 直到其满足 $a_i \neq a_j$ 且 $b_i<b_j$，然后入栈。如果一个二元组入栈后栈内只有这一个元素，则称该二元组是“成功的”。

在 $[l,r]$ 的区间中每对元素依次做如上操作，求有多少个“成功的”二元组。
## 思路
看到这题，可以尝试打个 $15$ 分的暴力，在此直接给出代码：
```cpp
#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
#define int long long
pair<int,int> a[500010];
#define fi first
#define se second
signed main(){
    //freopen("stack.in","r",stdin);
    //freopen("stack.out","w",stdout);
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i].fi;
    for(int i=1;i<=n;i++) cin>>a[i].se;
    while(q--){
        stack<int> s,s1;
        int x,y,ans=0;
        cin>>x>>y;
        for(int i=x;i<=y;i++){
            int tmp=a[i].fi,temp=a[i].se;
            if(s.empty()){
                s.push(tmp);
                s1.push(temp);
                ans++;
            }
            else{
                be:;
                if(s.empty()){
                    s.push(tmp);
                    s1.push(temp);
                    ans++;
                    continue;
                }
                int xx=s.top(),yy=s1.top();
                if(xx!=tmp&&yy>temp){
                    s.push(tmp);
                    s1.push(temp);
                    if(s.size()==1) ans++;
                }
                else{
                    s.pop();
                    s1.pop();
                    goto be;
                }
            }
        }
        cout<<ans<<endl;
    }
}
```
接下来讲正解：

我使用的算法是归并树，其实就是归并排序和线段树的结合体，利用线段树记录归并排序的步骤。

它可以用于计算某区间中比某个数小或大的数有多少个，正好适用本题。建树时递归构造子节点，回溯时构造父节点。

学习归并树可以看此篇文章：<https://www.cnblogs.com/bennettz/p/8342242.html>

为什么本题可以转化成求解某区间比某数小的数的数量呢？

这样想：每个元素可以弹出他前面的若干元素，我们计他可以弹出至 $a[i]$ 号元素。如果求解一个区间 $[l,r]$，那么如果这个区间内的某个元素 $a[i]$ 可以弹出至 $l$ 以下，就肯定可以把栈弹空，所以本题就转化为求解区间 $<l$ 的数的数量了。

在程序最开始先模拟一下题目所说的操作，用栈记录下来，然后直接套模板求解某区间比某数小的数的数量即可。

最开始读入的数据可以用一个 `pair` 记录下来，注意细节，刚开始准备的 `stack` 先将一对 `0,0` 入栈以防出错。

本代码时间复杂度大概为 $O(n \ \log^2 \ n)$。
## 代码
```cpp
/* / / / / / / / / /
written by Jerrlee

算法使用：归并树
/ / / / / / / / / */
#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
#define int long long
#define fi first
#define se second
pair<int,int> a[500010];
int c[500010],f[50][500010];
void Build(int de,int l,int r){
	if(l==r){
		f[de][l]=c[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(de+1,l,mid);
    Build(de+1,mid+1,r);
    for(int i=l,j=mid+1,k=l;i<=mid||j<=r;){
        if(j>r) f[de][k++]=f[de+1][i++];
        else if(i>mid||f[de+1][i]>f[de+1][j]) f[de][k++]=f[de+1][j++];
        else f[de][k++]=f[de+1][i++];
    }
}//建树
int calc(int de,int L,int R,int l,int r,int x){
    if(L>=l&&R<=r) return lower_bound(f[de]+L,f[de]+R+1,x)-f[de]-L;
    int mid=(L+R)>>1,ans=0;
    if(mid>=l) ans+=calc(de+1,L,mid,l,r,x);
    if(mid<r) ans+=calc(de+1,mid+1,R,l,r,x);
    return ans;
}//模板部分
signed main(){
    //freopen("stack.in","r",stdin);
    //freopen("stack.out","w",stdout);
	int n,q;
	cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i].fi;
    for(int i=1;i<=n;i++) cin>>a[i].se;
	stack<pair<int,int> > s,s1;
	s.push({0,0});
    s1.push({0,0});
	for(int i=1;i<=n;i++){
        be:
		c[i]=s.top().fi;
		if(s.size()>1&&!(s.top().se!=a[i].fi&&s1.top().se>a[i].se)){
            s.pop();
            s1.pop();
            goto be;
        }
		s.push({i,a[i].fi});
        s1.push({i,a[i].se});
	}//模拟
	Build(1,1,n);
	while(q--){
		int x,y;
		cin>>x>>y;
		cout<<calc(1,1,n,x,y,x)<<endl;//求出 x-y 区间内数字小于 x 的数量 
	}
}
```
注：此代码在洛谷只有 $50$ 分，需要加快读（但是我测完 CCF 的官方数据是 $100$）。

快读版：<https://www.luogu.com.cn/paste/1c5p7sdz>

[AC 记录](https://www.luogu.com.cn/record/72805036)

---

## 作者：xieyikai2333 (赞：18)

- [题目传送门](https://www.luogu.com.cn/problem/P8251)

---

### 思路分析

- 既然题目叫做丹钓战，当然是用 ~~单调栈（谐音梗，扣钱！）~~ **树状数组**做。

---

### 具体做法

对于每组数据：

1. 读入，将询问存入数组并记录询问编号；

2. 对询问按右端点从小到大排序：

3. 将 $n$ 个二元组的编号依次加入题目所述的单调栈，记加入第 $i$ 个二元组时栈顶元素为 $t_i$ ，则当左端点在区间 $[t_i+1,i]$ 中且右端点不小于 $i$ 时第 $i$ 个二元组对答案有贡献（请自行思考原因），所以对区间 $[t_i+1,i]$ 中的每一个数加 $1$。当右端点为 $i$ 时，询问的答案即为当前左端点对应的值。区间修改单点查询可以用树状数组维护；

---

### 代码实现


**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	int l,r,id;
	bool operator < (const node &x)const
	{
		return this->r<x.r;
	}
}Q[500005];
int a[500005],b[500005],c[500005],ans[500005],n;
stack<int> stk;
int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x;
}
void write(int x,int flag)
{
	if(!x)
	{
		if(flag)putchar('0');
		return;
	}
	write(x/10,false);
	putchar(x%10+'0');
	return;
}
int lowbit(int x)
{
	return x&(-x);
}
void add(int x,int v)
{
	for(int i=x;i<=n;i+=lowbit(i))c[i]+=v;
	return;
}
int sum(int x)
{
	int res=0;
	for(int i=x;i;i-=lowbit(i))res+=c[i];
	return res;
}
int main()
{
//	freopen("stack.in","r",stdin);
//	freopen("stack.out","w",stdout);
	int q,pos=1;
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=q;i++)Q[i].l=read(),Q[i].r=read(),Q[i].id=i;
	sort(Q+1,Q+q+1);
	a[0]=b[0]=INT_MAX;
	stk.push(0);
	for(int i=1;i<=n;i++)
	{
		while(true)
		{
			int j=stk.top();
			if(a[i]!=a[j]&&b[i]<b[j])break;
			stk.pop();
		}
		add(stk.top()+1,1),add(i+1,-1);
		stk.push(i);
		while(Q[pos].r==i)ans[Q[pos].id]=sum(Q[pos].l),pos++;
	}
	for(int i=1;i<=q;i++)write(ans[i],true),putchar('\n');
	return 0;
}
```

---

## 作者：2020kanade (赞：11)

本题解默认读者已经学习过单调栈。下文中的对于单调栈的“插入某元素之前”若未特殊说明均已经完成单调性的维护，也就是已经把此时栈里不该有的东西飞了。

题中给的栈可看作是单调栈的一种变形，因此下文对此也称为“单调栈”。

结论：把二元组按序全都往单调栈里插一次，如果对于某个区间内的某二元组对这个区间的答案产生了贡献，那么这个二元组往单调栈里进的时候要么栈是空的要么栈顶二元组的下标小于左边界。

比较简单粗暴的证明思路：单调栈为空的情况显然；单调栈栈顶下标小于左边界下标时，说明左区间点到当前二元组之间的二元组已经从单调栈里被飞了；换句话说，此时如果从左边界开始插入单调栈的话，到这个二元组的时候栈是空的。

还有一种证明思路：建立一颗以二元组下标为BST关键字，以相邻二元组相对大小为堆关键字的大根堆笛卡尔树。至于为什么是大根堆，拿单调栈建树的话会发现这里的单调栈和题目中的单调栈一致。之后会发现：建树时右链就是单调栈反过来的样子，而如果发生了因维护单调性而导致的元素弹出，右链也会对应地发生改变，且若加入的二元组是“成功的”，该二元组对应结点会在此时成为右链的根节点，此时差不多就想到为什么了，留给读者思考。

由此易得若是将全部二元组按下标顺序全部往单调栈里塞一边的话将一个二元组插入单调栈之前，若栈不为空，则该二元组对于以栈顶下标往后一位为左边界、以当前二元组下标为右边界的区间产生1的贡献。

显然现在有个朴素的思路：拿树状数组按照统计逆序对的方法（将产生贡献的位置+1，之后统计）进行计数，很显然会BOOM，因为对于一个查询区间每个二元组可能都需要操作树状数组，时间复杂度比平方还烂。

这时候如果没有思路的话，建议出门左转[P1972](https://www.luogu.com.cn/problem/P1972)，这算是树状数组进行离线多区间处理的板子，对于思路可能会有启发。其实这一部分本题与这道题基本一致。

回到本题。笔者的思路是：把统计方法转化一下。通过单调栈我们获得的是某个点会对询问区间左端点在哪个下标后面的区间产生贡献的那个下标，那么我们可以反过来知道对于一个下标，有哪个下标的二元组的“贡献产生开始左边界”是此下标，我们姑且称其为“前驱”。我们对所有二元组提前记录初始下标，之后按照其前驱递增排序，这样可以对整个区间线性扫描一次通过前驱求出此前驱对应哪个二元组产生贡献，之后直接区间求和即可，可以用树状数组维护前缀和，直接一个树状数组扬了?

没这么简单，注意这个由前驱产生的贡献并不是静态的。同时注意到这个前驱显然与询问区间左端点有关，至于为什么可以仔细想想结论。要是每次都单独处理复杂度和前面那个naive思路是一样的。此时可借鉴P1972的思路，将询问区间通过左/右端点组织成单调的，之后随区间移动进行修改。显然由前面说的，这里应该按左端点升序排序所有区间，以区间左端点作为每次修改操作终点，在修改结束后进行统计。排序后该指针的移动次数显然最大为二元组个数次，即 $O(n)$ ，因此本算法时间复杂度为 $O((q+n)\log n)$ ，空间复杂度线性。

献上洛谷民间数据AC代码：（先别走，后面还有内容）
```cpp
/*
はらり、滑り落ちる
掴んだ幸せの脆さに
それでも、願うのは
愛した男と活きること
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N=5e5+15;
stack<LL> st;
LL C[N],n;
inline LL lbt(LL x) {return x&(-x);}
inline void cha(LL x,LL q) {while(x<=n&&x) C[x]+=q,x+=lbt(x);}
inline LL sum(LL x) {LL ans=0;while(x>0) ans+=C[x],x-=lbt(x);return ans;}
inline LL getsm(LL l,LL r) {return sum(r)-sum(l-1);}
inline char gc()
{
    static char buf[1<<23],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++;
}
//#define gc getchar
inline LL qread()
{
    LL a=0,f=1;char ch=gc();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1;ch=gc();}
    while(ch>='0' && ch<='9') {a=(a<<3)+(a<<1)+ch-'0';ch=gc();}
    return a*f;
}
inline void qwrite(LL x)
{
    if(x==0) {putchar('0'),putchar('\n');return;}
    char w[128];LL cnt=0;
    if(x<0) putchar('-'),x*=-1;
    while(x) {w[cnt++]=(x%10)+'0';x/=10;}
    while(cnt--) putchar(w[cnt]);putchar('\n');
}
inline void file(string name)
{
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}
struct AWSL{LL a,b,pos,id;} WA[N];//此处的id其实为idx，即下标
const inline bool operator <(const AWSL &a,const AWSL &b) {return a.pos<b.pos;}
LL ans[N],q;
struct queries{LL l,r,id;}Q[N];
const inline bool operator <(const queries &a,const queries &b) {return a.l<b.l;}
int main()
{
    //file("stack4");
    n=qread(),q=qread();
    for(LL i=1;i<=n;++i) WA[i].id=i,WA[i].a=qread();for(LL i=1;i<=n;++i) WA[i].b=qread();
    for(LL i=1;i<=n;++i) {while(!st.empty() && (WA[st.top()].a==WA[i].a || WA[st.top()].b<=WA[i].b)) st.pop();WA[i].pos=st.empty()?0:st.top();st.push(i);}
    for(LL i=1;i<=q;++i) Q[i].id=i,Q[i].l=qread(),Q[i].r=qread();
    stable_sort(WA+1,WA+n+1);stable_sort(Q+1,Q+q+1);LL rptr=1;
    for(LL i=1;i<=q;++i)//伪双指针
    {
        while(WA[rptr].pos<Q[i].l) cha(WA[rptr].id,1),++rptr;
        ans[Q[i].id]=getsm(Q[i].l,Q[i].r);
    }
    for(LL i=1;i<=q;++i) qwrite(ans[i]);
    return 0;
}
/*
たけのはな
さいてただ
ちるまでのみをかかえて
だれにでなくあいをさけぶ
ともにいきていたこと
だたしあわせをねがったが
それでもはかなくきゆるのみ
ただふかいアイのおわらずに
いつまでものこされて、ああ
*/
```
此外，易得在笛卡尔树上，某个区间的答案为区间左端点对应结点与区间两个端点对应结点的LCA之间的最短路径上对应下标在该区间内的结点个数。笔者与 @Rnfmabj  正在尝试由此结论引申出的点分治解法，若有进展会在此处更新。

---

## 作者：Galex (赞：10)

[惊险的提交记录](https://www.luogu.com.cn/record/72363685)。
卡到了 $993$ 毫秒。。。

## 进入正题

先看题目，经典静态查询问题，用普通莫队就行啦。

对于每个位置 $i$ 记录一个值 $pre_i$，表示这个二元组 $(a_i,b_i)$ 在 $pre_i + 1$ 到 $i$ 的位置是成功的。这个可以一开始用单调栈预处理出来。

然后就是莫队的事情了，我们要找的相当于就是 $p_l$ 到 $p_r$ 中有多少个数是比 $l$ 小的。所以在转移过程中记录一下插入和删除的位置的数量就行了。

最后查询的时候，把值域分块即可，这样可以保证复杂度是 $O(n \times \sqrt n)$ 的。

最后莫队排序的时候记得用奇偶玄学优化。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	int s = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
		(ch == '-' ? -1 : 1), ch = getchar();
	while (ch >= '0' && ch <= '9')
		s = (s << 1) + (s << 3) + (ch ^ 48), ch = getchar();
	return s * f;
}

int n, Q;
int a[500005], b[500005], p[500005];
int s[500005], top = 0;
int bl[500005];
struct qry{
	int l, r, id;
	friend bool operator < (const qry &x, const qry &y) {
		if (bl[x.l] != bl[y.l])
			return bl[x.l] < bl[y.l];
		if (bl[x.l] % 2 == 0)
			return x.r > y.r;
		return x.r < y.r;
	}
}q[500005];
int ans[500005], c[500005];
int head = 1, tail = 0;

int l[1005], r[1005], sum[1005], pos[500005];

void buildblock(){
	int k = sqrt(n);
	for (int i = 1; i <= k; i++)
		l[i] = r[i - 1] + 1, r[i] = r[i - 1] + k;
	if (r[k] < n)
		l[k + 1] = r[k] + 1, r[k + 1] = n, k++;
	for (int i = 1; i <= k; i++)
		for (int j = l[i]; j <= r[i]; j++)
			pos[j] = i;
}

int query(int p){
	int P = 0, ans = 0;
	for (int i = 1; i < pos[p]; i++)
		ans += sum[i];
	for (int i = l[pos[p]]; i <= p; i++)
		ans += c[i];
	return ans;
}

void mdf(int x, int v){
	c[p[x]] += v;
	sum[pos[p[x]]] += v;
}

signed main() {
	n = read(), Q = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n; i++)
		b[i] = read();
	for (int i = 1; i <= n; i++){
		while (top > 0 && !(a[i] != a[s[top]] && b[i] < b[s[top]]))
			top--;
		p[i] = s[top] + 1;
		s[++top] = i;
	}
	buildblock();
	int t = sqrt(n);
	for (int i = 1; i <= n; i++)
		bl[i] = (i - 1) / t + 1;
	for (int i = 1; i <= Q; i++)
		q[i].l = read(), q[i].r = read(), q[i].id = i;
	sort(q + 1, q + Q + 1);
	for (int i = 1; i <= Q; i++){
		while (tail < q[i].r)
			mdf(++tail, 1);
		while (tail > q[i].r)
			mdf(tail--, -1);
		while (head < q[i].l)
			mdf(head++, -1);
		while (head > q[i].l)
			mdf(--head, 1);
		ans[q[i].id] = query(q[i].l);
	}
	for (int i = 1; i <= Q; i++)
		printf("%d\n", ans[i]);
	return 0;
}
```


---

## 作者：赵悦岑 (赞：9)

# P8251 [NOI Online 2022 提高组] 丹钓战题解

[P8251 [NOI Online 2022 提高组] 丹钓战](https://www.luogu.com.cn/problem/P8251)

这道题我的方法是**主席树**，请不了解主席树的同学移步这道题： [P3834 【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834)

## 分析

### 模拟入栈

首先我们可以发现，这个栈的元素 $b_i$ 一定是单调下降的，如果要模拟入栈的操作，我们可以通过二分查找第一个比 $b_i$ 大的元素来模拟，可以在 $n\log n$ 的复杂度内完成一次模拟。但是同时还要满足任意两个相邻元素的 $a$ 不同，我们只需要在找到第一个比 $b_i$ 大的元素后，弹出栈顶直到栈顶元素的 $a$ 与 $a_i$ 不相等。注意要首先把 $inf$ 入栈，防止越界。

$b$ 代表 $b$ 序列，$c$ 代表栈。

```cpp
int l=0,r=t,z;
while(l<r)
 {
    z=(l+r+1)>>1;
    if(b[i]<b[c[z]]) l=z;
    else r=z-1;
}
while(a[c[l]]==a[i]) --l;
```

## 查询

如果我们先把所有元素按顺序入栈，由于任意的 $[l,r]$ 都应该是 $[1,n]$ 的一部分，并且栈中的元素编号一定递减，所以 $\forall [l,r]$，最终形成的栈一定是 $[1,r]$ 形成的栈的一部分，具体来说就是 $[1,r]$ 形成的栈去掉所有编号比 $l$ 小的元素。如果 $r$ 号元素想要在 $[l,r]$ 形成的栈中成为第一个，那么 $[1,r]$ 所形成的的栈中在 $r$ 之前的元素的编号必然都比 $l$ 小，只有这样前面所有元素才会被删去。所以用 $d$ 来储存每个数入栈后前一个元素的编号，那么 $[l,r]$ 中成功二元组的个数就是 $k \in [l,r],d_k < l$ 成立的 $k$ 的个数。

## 优化

但是上面这种方法的复杂度为 $O(n\times q)$ ，显然过不了。通过上面的分析，我们发现查询的实质是求 $d$ 中 $[l,r]$ 中小于 $l$ 的数的个数。有什么数据结构能实现？主席树！于是这道题就变成了主席树的板子题。然后，就没有然后了。

## code
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
int n,m,p,t,a[500001],b[500001],c[500001],rt[500001];
struct tree
{
    int l,r,s;
}T[30000001];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s;
}
void build(int &x,int l,int r)
{
    x=++p;
    if(l==r) return;
    int z=l+r>>1;
    build(T[x].l,l,z);
    build(T[x].r,z+1,r);
}
void modify(int &x,int l,int r,int q)
{
    T[++p]=T[x];
    ++T[p].s;
    x=p;
    if(l==r) return;
    int z=l+r>>1;
    if(q<=z) modify(T[x].l,l,z,q);
    else modify(T[x].r,z+1,r,q);
}
int num(int x,int l,int r,int k)
{
    if(l==r) return 0;
    int z=l+r>>1;
    if(k==z) return T[T[x].l].s;
    if(k<z) return num(T[x].l,l,z,k);
    return T[T[x].l].s+num(T[x].r,z+1,r,k);
}
int main()
{
    freopen("stack.in","r",stdin);
    freopen("stack.out","w",stdout);
    n=read(),m=read();
    for(int i=1;i<=n;++i) a[i]=read();
    for(int i=1;i<=n;++i) b[i]=read();
    a[0]=0;
    b[0]=1e9;
    c[0]=0;
    build(rt[0],0,n);
    for(int i=1;i<=n;++i)
    {
        int l=0,r=t,z;
        while(l<r)
        {
            z=(l+r+1)>>1;
            if(b[i]<b[c[z]]) l=z;
            else r=z-1;
        }
        while(a[c[l]]==a[i]) --l;
        t=l+1;
        c[t]=i;
        rt[i]=rt[i-1];
        modify(rt[i],0,n,c[l]);
    }
    for(int i=1;i<=m;++i)
    {
        int l=read(),r=read();
        printf("%d\n",num(rt[r],0,n,l-1)-num(rt[l-1],0,n,l-1));
    }
    return 0;
}
```

---

## 作者：WYXkk (赞：8)

简要题意：给你一串二元组。有一个栈，初始为空，将一个二元组入栈前会不断将栈顶出栈直到栈空或者栈顶和将入栈的二元组满足某关系。每次询问给定一个区间，问将这个区间的二元组依次入栈时，有多少个二元组入栈前会把栈弹空。

分析：诈骗题，那个关系是什么完全不重要。

容易注意到，在某个二元组出栈前，栈内在这个二元组以后的部分，与从这个二元组开始入栈的结果是一样的。从而，每个二元组能弹出到哪些二元组不受从哪个二元组开始入栈影响。

因此，先从头模拟一遍入栈操作，然后记录每个二元组真正入栈前栈顶的编号，那么比这个编号大的全都可以被这个二元组或者更之前的二元组弹出。记第 $k$ 个二元组可以弹出 $L_k,L_k+1,\cdots,k-2,k-1$。

那么，每个询问 $l,r$ 相当于问 $\sum\limits_{i=l}^r[L_i\le l]$。容易想到离线询问或者使用可持久化数据结构，然后按 $L_i$ 从小到大修改再区间查询。

于是这题就做完了。

[参考代码：可持久化线段树](https://www.luogu.com.cn/paste/ceg7fvsv)

---

## 作者：CasseroleGoose (赞：6)

### 一些扯淡
好嘛，这题目我愣是看了半天没看出来“丹钓战”。

退役选手，从一些地方嫖来了题面和数据，看了看T1。

### 回归正题
#### 简要叙述
这个题目我可能做法跟大家的不太一样（？）

首先对于这**整个数组**，预处理出每个二元组可以往前一直弹到第几个二元组的前面，这个值用一个数组 $f$ 记录下来。如果第 $i$ 个二元组压入栈的时候，可以把之前栈里面的全部元素都弹出来，也就是成为一个“成功的”二元组，那么我们就令 $f_i=0$

##### 举个栗子：
```
a[i]=3  1  3 1 2
b[i]=10 10 2 9 7
f[i]=0  0  2 0 4
```
##### 解释：
我们把 $(3,10)$ 压入栈，它前面没有任何一个二元组，$f_1=0$

我们把 $(1,10)$ 压入栈，由于 $b_2=b_1=10$，$(3,10)$ 就被弹出，此时它前面就也没有任何一个二元组，$f_2=0$

我们把 $(3,2)$ 压入栈，发现 $(1,10)$ 满足题目的条件，不必弹出，此时 $(3,2)$ 的前面是第二个二元组，$f_3=2$

我们把 $(1,9)$ 压入栈，发现 $(1,10),(3,2)$ 都要弹出（由于题目条件），所以此时 $(1,9)$ 前面不再剩下任何一个二元组，$f_4=0$

$f_5=4$ 也同理

#### 做法
有了这个 $f$ 数组，我们发现对于每个询问 $l,r$ ，我们只需要数一数区间 $[l,r]$ 中有多少个 $f_i$ 是满足 $f_i<l$ 的，如果满足这个条件，也就说明了第 $i$ 个二元组是可以成为一个“成功的”。\
这是因为能让第 $i$ 个二元组“不成功”的二元组是第 $f_i$ 个二元组，而又因为 $f_i<l$，不在询问区间内，所以没有一个二元组能够“阻挡”第 $i$ 个二元组在此次询问中成为“成功的”。

然后不难发现 $f$ 数组可以线性求得，统计答案的话是一个经典问题——“统计询问区间内有多少个数字小于 $x$ ”，树状数组求解即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define F(i,l,r) for(register int i=l;i<=r;i++)
#define D(i,r,l) for(register int i=r;i>=l;i--)
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define p_b push_back
#define m_p make_pair
#define il inline
#define fi first
#define se second
const int INF=0x7f7f7f7f,N=1e6+5;
void rd(int &num) {
    num=0;
    int k=1;
    char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') k=-1,ch=getchar();
    while(ch<='9'&&ch>='0') {
        num=num*10+ch-'0';
        ch=getchar();
    }
    num*=k;
}
int n,T;
int a[N],b[N];
struct node {
    int f,ind;
}p[N];
struct query {
    int l,r,ind;
}q[N];
bool cmp1(node x,node y) {return x.f<y.f;}
bool cmp2(query x,query y) {return x.l<y.l;}
int sum[N],ans[N];
il int lbt(int x) {return x&(-x);}
il void add(int p) {
    while(p<=n) {
        sum[p]+=1;
        p+=lbt(p);
    }
    return;
}
il int ask(int p) {
    int res=0;
    while(p>0) {
        res+=sum[p];
        p-=lbt(p);
    }
    return res;
}
int main() {
    // freopen("stack.in","r",stdin);
    // freopen("stack.out","w",stdout);
    rd(n),rd(T);
    F(i,1,n) rd(a[i]);
    F(i,1,n) rd(b[i]);
    F(i,2,n) {
        int pos=i-1;
        while(pos) {
            if(a[i]==a[pos]||b[i]>=b[pos]) pos=p[pos].f;
            else break;
        }
        p[i].f=pos;
        p[i].ind=i;
    }
    p[1].ind=1;
    // F(i,1,n) printf("%d ",p[i].f);puts("");
    sort(p+1,p+1+n,cmp1);
    F(i,1,T) {
        rd(q[i].l),rd(q[i].r);
        q[i].ind=i;
    }
    sort(q+1,q+1+T,cmp2);
    // F(i,1,n) printf("%d ",p[i].f);
    int po=1;
    F(i,1,T) {
        while(p[po].f<q[i].l&&po<=n) {
            add(p[po].ind);po++;
        }
        ans[q[i].ind]=ask(q[i].r)-ask(q[i].l-1);
    }
    F(i,1,T) printf("%d\n",ans[i]);
    return 0;
}
```
~~（码风应该还行吧）~~

~~(给个赞吧)~~

---

## 作者：lg_zhou (赞：5)

update on 2022/4/6

做法：离线 + 树状数组

因为每次询问时连续的，所以对于每个元素来说，我们只在意第一个把它 pop 出栈的元素，并可以把它预处理出来。

很显然第一个把它 pop 出栈的元素只有一个（或没有）。所以可以把它想象成若干棵树（一个森林）。这样有如下好处：

1. 一棵树内的编号是连续的。

2. 任意一个节点的后代编号都比它小。

3. 当任意一个节点入栈时，它的后代肯定已经全部出栈了。

我们可以预处理出来数组 $mn$ 来表示它的后代中编号最小的数。**（update on 2022/4/6 : 因为后代编号都比它小，所以在访问它的时候它的后代早就被访问过了，所以不用递归求解, 但是把它想象成一棵树的确是非常直观的）。**

那么对于每一个节点 $id$ , 它会对所有 $mn[id] \le l \le id$ 且 $r \ge id$ 的询问贡献加一。

因为 $mn[id] \le l \le id$ ，保证了它入栈时为空的，它的后代已经全部推出。因为 $r \ge id$，所以它有入栈的机会。

那我们就可以把询问离线下来，以 $r$ 为关键字从小到大排序，对于每一个询问，将 $id \le r$ 的所有节点对应的 $l$ 范围加一。

这个操作可以用树状数组实现，区间加转化成差分操作即可。

代码：

```cpp
//#pragma GCC optimize(2)
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<cstdio>
using namespace std;
const int maxn = 5e5+5;

struct t{
	int a,b;
	int pos;
};
struct Q{
	int l,r;
	int pos;
}q[maxn];
vector<int> v[maxn];


int mn[maxn];

/*int vis[maxn];
void dfs(int u){
	vis[u] = 1;
	mn[u] = u;
	for (int i = 0; i < v[u].size(); i++){
		int to = v[u][i];
		mn[u] = min(mn[u], mn[to]);
		if (!vis[to]) dfs(to);
	}
}*/ //之前的递归 
bool cmp(Q a, Q b){
	return a.r < b.r;
}
int a[maxn], b[maxn],ans[maxn];
int n,m;

//树状数组
int C[maxn];
int lowbit(int x){
	return x&-x;
}
void add(int x, int v){
	if (!x) return;
	for (int i = x; i <= n; i += lowbit(i)){
		C[i] += v;
	}
}
int getsum(int x){
	int ans = 0;
	for (int i = x; i; i -= lowbit(i)){
		ans += C[i];
	}
	return ans;
}
//


t s[maxn*2];
int main(){
	//freopen("stack.in","r",stdin);
	//freopen("stack.out","w",stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) scanf("%d",&a[i]);
	for (int i = 1; i <= n; i++) scanf("%d",&b[i]);
	
	int l,r;
	l = r = 0;
	for (int i = 1; i <= n; i++){
		while(r > l && (s[r].a == a[i] || s[r].b <= b[i])){
			v[i].push_back(s[r].pos);
			r--;
		}
		s[++r] = (t){a[i],b[i],i};
	}//预处理出来第一个pop元素
    
    
	for (int i = 1; i <= n; i++){
		//if (!vis[i]) dfs(i);//找最小节点
		mn[i] = i;
		for (int j = 0; j < v[i].size(); j++) mn[i] = min(mn[i], mn[v[i][j]]);
	}
    
	for (int i = 1; i <= m; i++){
		scanf("%d%d",&q[i].l, &q[i].r);
		q[i].pos = i;
	}
	sort(q+1,q+1+m,cmp);
	int now = 1;
	for (int i = 1; i <= m; i++){
		while(now <= n && now <= q[i].r){
			add(mn[now],1);
			add(now+1,-1);//差分
			now++;
		}
		ans[q[i].pos] = getsum(q[i].l);
	}
	for (int i = 1; i <= m; i++){
		printf("%d\n",ans[i]);
	}
	return 0;
} 
```



---

## 作者：Danno0v0 (赞：5)

~~单调栈？吃桃吧你莫队yyds~~

虽然题面上已经提醒我们要用单调栈了。

但是我们要有~~叛逆~~创新思维。

~~首先观察到 $1 \leq n, q \leq 5 \times 10^5$，这个数据范围说明出题人不仅提示我们可以用单调栈，还可以用莫队做~~

知道出题人给我们的提示后，我们就可以开始莫队了。

首先我们预处理一个 fa 数组，然后这个 fa 数组是干什么用的呢，是用来记录**假如从第1个开始放，那么当第 $i$ 个二元组入栈前栈顶的下标。**

实现也肥肠简单：

```cpp
	k=i-1;
	while(k&&((a[k]==a[i])||((a[k]^a[i])&&b[k]<=b[i])))
		k=fa[k];
	fa[i]=k;
```

实际上原理就是模拟一下栈的情况，随便手推一下就可以了。

另外对于每个下标 $i$ 我们都开一个 vector cnt 记录所有将 $i$ 作为 fa 的位置：

```cpp
    cnt[i].emplace_back(-0x7ffffff);//先压一个方便二分
    cnt[k].emplace_back(i);
```

易知预处理是 $O(n)$ 的。

接下来就是莫队环节了。

首先我们考虑右指针的移动，比较简单：

右端的移动表示把一个新的数压进栈内。

右移（压栈）：

```cpp
	while(q[i].r>r)
		ans+=(fa[++r]<l?1:0);
```

假如阻挡这个二元组到达栈底的二元组不在当前的询问区间（没有入栈）那么自然这个数可以一通到底；

左移（弹栈）：

```cpp
	while(q[i].r<r)
		ans-=(fa[r--]<l?1:0);
```

同理假如这个二元组做出了贡献就要减掉。

然后来考虑左指针。

左指针移动有一点麻烦，因为不管是在操作序列最前端加入或者删除都有可能影响操作序列后端的二元组对答案的贡献。

这个时候之前预处理的 cnt 就有用了：

左移（加入）：

```cpp
	while(q[i].l<l)
	{
		l--,ans++;
		vector<int>::iterator t1=upper_bound(cnt[l].begin(),cnt[l].end(),l);
		vector<int>::iterator t2=upper_bound(cnt[l].begin(),cnt[l].end(),r)-1;
		if(t1!=cnt[l].end()&&t2!=cnt[l].begin())
		ans-=(t2-t1+1);
	}
```

二分找到在区间 $[l,r]$ 内以 $i$ 为 fa 的二元组。

由于假如 $i$ 没有加入，那么这些二元组可以为答案做出贡献，现在加入了，就要减掉。

另外由于 $i$ 成为了第一个入栈的，所以 $i$ 会对答案产生贡献，所以 ```ans++``` 。

同理可得右移（删除）：

```cpp
	while(q[i].l>l)
	{
		vector<int>::iterator t1=upper_bound(cnt[l].begin(),cnt[l].end(),l);
		vector<int>::iterator t2=upper_bound(cnt[l].begin(),cnt[l].end(),r)-1;
		if(t1!=cnt[l].end()&&t2!=cnt[l].begin())
			ans+=(t2-t1+1);
		l++,ans--;
	}
```

时间复杂度 $n\sqrt {nlogn}$ ，应该还有更紧的上界，但是我懒得算了（

~~我也不知道为什么这东西为什么可以过，总之各种玄学卡常就过了~~

code:

```cpp
#include<bits/stdc++.h>
#define Maxn 500100
using namespace std;
namespace DEBUG {
	inline void cerr_out(){cerr<<'\n';}
	template<typename Head,typename... Tail>
	inline void cerr_out(Head H,Tail... T){cerr<<' '<<H,cerr_out(T...);}
	void debug_out() { cerr << '\n'; }
	template <typename Head, typename... Tail>
	void debug_out(Head H, Tail... T) { cerr << ' ' << H, debug_out(T...); }
#define debug(...) cerr << '[' << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
} using namespace DEBUG;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define getchar() (S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?EOF:*S++)
namespace get_out
{
	char B[1<<20],*S=B,*T=B;
	char op;
	inline void read_(int &x)
	{
		x=0;
		int fi(1);
		op=getchar();
		while((op<'0'||op>'9')&&op!='-') op=getchar();
		if(op=='-') op=getchar(),fi=-1;
		while(op>='0'&&op<='9') x=(x<<1)+(x<<3)+(op^48),op=getchar();
		x*=fi;
		return;
	}
	inline void read_(long long &x)
	{
		x=0;
		int fi(1);
		op=getchar();
		while((op<'0'||op>'9')&&op!='-') op=getchar();
		if(op=='-') op=getchar(),fi=-1;
		while(op>='0'&&op<='9') x=(x<<1)+(x<<3)+(op^48),op=getchar();
		x*=fi;
		return;
	}
	inline void read_(double &x)
	{
		x=0.0;
		float fi(1.0),sm(0.0);
		op=getchar();
		while((op<'0'||op>'9')&&op!='-') op=getchar();
		if(op=='-') op=getchar(),fi=-1.0;
		while(op>='0'&&op<='9') x=(x*10.0)+(op^48),op=getchar();
		if(op=='.') op=getchar();
		int rtim=0;
		while(op>='0'&&op<='9') sm=(sm*10.0)+(op^48),++rtim,op=getchar();
		while(rtim--) sm/=10.0;
		x+=sm,x*=fi;
		return;
	}
	inline void read_(string &s)
	{
		char c(getchar());
		s="";
		while(!isgraph(c)&&c!=EOF) c=getchar();
		for(;isgraph(c);c=getchar()) s+=c;
	}
	inline void read_(char &c)
	{
		for(c=op;c==' '||c=='\n'||c=='\r'||c=='\t';c=getchar());
		op=c;
	}
	
	template<typename Head,typename ...Tail>
	inline void read_(Head& h,Tail&... t)
	{read_(h),read_(t...);}
	
	inline void write_(){}
	inline void postive_write(unsigned x)
	{
		if(x>9) postive_write(x/10);
		putchar(x%10|'0');
	}
	inline void postive_write(unsigned long long x)
	{
		if(x>9) postive_write(x/10);
		putchar(x%10|'0');
	}
	inline void postive_write(int x)
	{
		if(x>9) postive_write(x/10);
		putchar(x%10|'0');
	}
	inline void postive_write(long long x)
	{
		if(x>9) postive_write(x/10);
		putchar(x%10|'0');
	}
	inline void postive_write(short x)
	{
		if(x>9) postive_write(x/10);
		putchar(x%10|'0');
	}
	inline void write_(const char* ss) {while(*ss) putchar(*ss++);}
	inline void write_(char c) {putchar(c);}
	inline void write_(string s) {for(unsigned i=0;i<s.size();++i) putchar(s[i]);}
	inline void write_(short x)
	{
		if(x<0) putchar('-'),postive_write(-x);
		else postive_write(x);
	}
	inline void write_(int x)
	{
		if(x<0) x=-x,putchar('-');
		postive_write(x);
	}
	inline void write_(long long x)
	{
		if(x<0) x=-x,putchar('-');
		postive_write(x);
	}
	inline void write_(unsigned x) {postive_write(x);}
	inline void write_(ull x) {postive_write(x);}
	
	template<typename Head,typename ...Tail>
	inline void write_(Head h,Tail ...t) {write_(h),write_(t...);}
}
using get_out::read_;
using get_out::write_;
//dalao嘉年华提供的快到飞起的快读
vector<int>cnt[Maxn<<1];
int n,F,m,fa[Maxn<<1];
int a[Maxn<<1],b[Maxn<<1],ans_[Maxn<<1];
struct ques
{
	int l,r,id;
	int bl;
}q[Maxn<<1];
inline bool cmp(ques &a,ques &b)
{
	return a.bl!=b.bl?a.bl<b.bl:a.r<b.r;
}
int main()
{
	read_(n,m);
	F=pow(n,0.45)+5;
	for(register int i=1;i<=n;i++) read_(a[i]);
	for(register int i=1;i<=n;i++) read_(b[i]);
	for(register int i=1,k;i<=n;i++)
	{
		cnt[i].emplace_back(-0x7ffffff);
		k=i-1;
		while(k&&((a[k]==a[i])||((a[k]^a[i])&&b[k]<=b[i])))
			k=fa[k];
		cnt[fa[i]=k].emplace_back(i);
	}
	for(register int i=1;i<=m;i++)
	{
		read_(q[i].l,q[i].r);
		q[i].id=i,q[i].bl=q[i].l/F;
	}
	sort(q+1,q+m+1,cmp);
//	cerr<<clock();
	int l=1,r=1,ans=1;
	for(register int i=1;i<=m;i++)
	{
		while(q[i].r>r)
			ans+=(fa[++r]<l?1:0);
		while(q[i].l<l)
		{
			l--,ans++;
			vector<int>::iterator t1=upper_bound(cnt[l].begin(),cnt[l].end(),l);
			vector<int>::iterator t2=upper_bound(cnt[l].begin(),cnt[l].end(),r)-1;
			if(t1!=cnt[l].end()&&t2!=cnt[l].begin())
				ans-=(t2-t1+1);
		}
		while(q[i].r<r)
			ans-=(fa[r--]<l?1:0);
		while(q[i].l>l)
		{
			vector<int>::iterator t1=upper_bound(cnt[l].begin(),cnt[l].end(),l);
			vector<int>::iterator t2=upper_bound(cnt[l].begin(),cnt[l].end(),r)-1;
			if(t1!=cnt[l].end()&&t2!=cnt[l].begin())
				ans+=(t2-t1+1);
			l++,ans--;
		}
		ans_[q[i].id]=ans;
	}
	for(register int i=1;i<=m;i++) write_(ans_[i],'\n');
}
```

---

## 作者：xiaozeyu (赞：5)

[P8251 [NOI Online 2022 提高组] 丹钓战（民间数据）](https://www.luogu.com.cn/problem/P8251)

题目要求把数字放在一个新定义的栈中。

题目会给出每个数的两个关键字，还会在最后给出每一次查询的范围，每一次查询时是从左端点到右端点依次进行入栈操作。询问间独立。

（比较懒，这里的第一第二是指每一列第一、二个值）

在这个栈中，每次加入新元素都要判断一下，只有在第一关键字不同且第二关键字比原来的栈顶小的或栈为空才能把一个数放上去。统计值为每次入完栈后栈里只要一个元素的次数。

那么这个栈就是满足相邻数字的第一关键字不同且第二关键字从顶到底单调。

一看就感觉可以直接离线。

第一反应可能将询问按照右端点排序。

开始的时候还不确定该怎么处理。然后看了下数据范围。

![数据范围](https://cdn.luogu.com.cn/upload/image_hosting/yxds7jrd.png)

可以看到第四类和第五类是十分特殊的。

感觉我们可以分别从这两个点入手，也就是分别思考第一关键字的处理以及第二关键字的处理，那么合起来就可以过了。

先看 $a_i=i$ 的情况，这个就是说第一关键字都不同，可以不考虑，只要考虑第二关键字就好了。

直接思考如何单调。只要小于等于现有的数就可以直接踢掉，那我们可以发现，一个数能踢掉的范围内的数都能被这个新数覆盖，也就是从被踢掉的数都可以在到了新数时次数加一。因为向左覆盖，此时若是将右端点排序，就不会被范围外的数影响。

再用线段树维护一下差分就好了。

再思考 $b_i=n-i+1$ 的情况。就是保证第二行单调递减了，我们只要考虑第一行是否相同，相同的可以往前踢。

![覆盖图示](https://cdn.luogu.com.cn/upload/image_hosting/bj8u7ul4.png)

可以用数组记录一下每个数最多覆盖到哪个点来方便给后面的点找覆盖范围。

开始都视作算完为一，如果查询的范围的左端点做过右端点要在算完后减一。

用了下快输。

代码如下。

---


```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define f(a) ((a)*(a))
#define p(x) printf("%lld ",(x))
#define fp(x) printf("%.10Lf ",(x))
#define P() puts("")
#define lowbit(x) ((x)&(-(x)))
using namespace std;
inline int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
inline void write(int re)
{
	if (re>9) write(re/10);
	putchar(re%10+'0');
}
const int maxn=500010;
const int mod=1e9+7;
const int base=10007;
struct node
{
	int l,r,Pos;
}Q[maxn];
int n,q,L,R;
int a[maxn],b[maxn],c[maxn],d[maxn],e[maxn];
int ans[maxn];
inline void add(int pos,int x)
{
	while(pos<=n)
	{
		c[pos]+=x;
		pos+=lowbit(pos);
	}
}
inline int query(int x)
{
	int res=0;
	while(x>0)
	{
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
bool cmp(node a,node b)
{
	return a.r<b.r;
}
signed main()
{
	//freopen("stack.in","r",stdin);
	//freopen("stack.out","w",stdout);
	n=read();q=read();
	For(i,1,n) a[i]=read();
	For(i,1,n) b[i]=read();
	For(i,1,q)
	{
		Q[i].l=read();Q[i].r=read();Q[i].Pos=i;
	}
	sort(Q+1,Q+q+1,cmp);
	add(1,1);
	For(i,1,n) d[i]=i;
	R=1;L=1;
	a[0]=n+1;
	b[0]=n+1;
	For(i,1,q)
	{
		while(R<Q[i].r)
		{
			R++;
			L=R-1;
			while(1)
			{
				if(a[L]==a[R]||b[L]<=b[R])
				{
					if(d[L]!=L)
					{
						L=d[L];
					}
					L--;
				}
				else 
				{
					L++;
					break;
				}
			}
			if(L==R) continue;
			else 
			{
				d[R]=L;
				e[R]=1;
				add(L,1);
				add(R+1,-1);
			}
		}
		ans[Q[i].Pos]=query(Q[i].l)-e[Q[i].l];
	}
	For(i,1,q)
	{
		write(ans[i]);
		P();
	}
	return 0;
}
```

---

感谢管理员的审核。


---

## 作者：Legitimity (赞：4)

[不知是否更好的阅读体验](https://www.cnblogs.com/tiatto/p/16060222.html)

### Description
给出 $n$ 个二元组 $(a_i,b_i)$ 和 $q$ 个询问 $[l_i,r_i]$，对于每个询问回答将区间 $[l_i,r_i]$ 内的二元组依次加入满足相邻两数 $a$ 值不同、$b$ 值递减的单调栈的的过程中，有多少次将栈弹空。

$1\leq n,q\leq 5\times 10^5$


------------

### Solution

发现左端点相同的询问加入元素的过程是相同的，考虑将询问离线，处理一起左端点相同的询问。

设 $p_{l,i}$ 表示以 $l$ 为左端点的情况下加入二元组 $(a_i,b_i)$ 时是否能将栈弹空，那么 $[l,r]$ 的答案即为 $\sum_{i=l}^rp_{l,i}$。考虑以 $l$ 为左端点相较于以 $l+1$ 为左端点产生了怎样的变化。设 $(a_i,b_i)$ 为将 $(a_l,b_l)$ 从栈中弹出的元素，那么有：
1. $\forall j\in(l,i),p_{l,i}=0$。考虑反证，若 $j_0\in(l,i)$ 能将栈弹空，则 $j_0$ 就会将 $l$ 弹出，与定义不符。
2. $\forall j\in[i,n],p_{l,i}=p_{l+1,i}$。$i$ 若能将 $l$ 弹出，则也能将 $l+1$ 弹出。那么加入 $i$ 后以 $l$ 为左端点和以 $l+1$ 为左端点栈中都只剩 $(a_i,b_i)$，此后过程完全一致。

如何找到 $i$？首先 $i$ 一定满足 $p_{l+1,i}=1$。考虑要么 $a_i=a_l$，这种情况对于每个 $a$ 值开一个 `set`，存放 $a_j=a_l$ 且 $p_{l+1,j}=1$ 的所有 $j$，取 $a_l$ 对应的 `set` 中的最小值即为 $i$；另外一种情况就是 $b_l\leq b_i$，那么我们可以用线段树维护 $p_{l+1,i}$ 和区间中满足 $p_{l+1,i}=1$ 的最大 $b_i$，的通过线段树上二分找到 $i$。

对于修改，需要实现单点修改和区间推平。这里有个特殊之处，一个位置只会被插入一次和推平一次，如果用线段树维护的话推平不需要懒标记，暴力推平即可，也因为这个性质，所以也可以用珂朵莉树继续维护，时间复杂度也是正确的。推平的时候要同时修改 `set`。

时间复杂度为 $O((n+q)\log n)$。

```cpp
struct que{ int r,id; que(int r=0,int id=0):r(r),id(id) {}  };
int n,q;
int a[500005],b[500005],ans[500005];
vector<que> m[500005];
set<int> s[500005];
struct node{
	int l,r,mxb,sum; 
}t[500005<<2];
inline void up(int x){ t[x].mxb=max(t[x<<1].mxb,t[x<<1|1].mxb); t[x].sum=t[x<<1].sum+t[x<<1|1].sum; }
void build(int x,int l,int r){
	t[x].l=l,t[x].r=r;
	if(l==r) return;
	const int mid=l+r>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
}
void insert(int x,const int id){
	if(t[x].l==t[x].r) return t[x].sum=1,t[x].mxb=b[id],void();
	const int mid=t[x].l+t[x].r>>1; 
	if(id<=mid) insert(x<<1,id);
	else insert(x<<1|1,id);
	up(x);
}
void assign(int x,const int sl,const int sr){
	if(sl>sr) return;
	if(t[x].l==t[x].r) return t[x].mxb=t[x].sum=0,s[a[t[x].l]].erase(t[x].l),void();
	const int mid=t[x].l+t[x].r>>1; 
	if(sl<=mid&&t[x<<1].sum) assign(x<<1,sl,sr);
	if(sr>mid&&t[x<<1|1].sum) assign(x<<1|1,sl,sr);
	up(x);
}
int bound(int x,const int k){
	if(t[x].l==t[x].r) return t[x].l;
	if(t[x<<1].mxb>=k) return bound(x<<1,k);
	if(t[x<<1|1].mxb>=k) return bound(x<<1|1,k);
	return n+1;
}
int query(int x,const int sl,const int sr){
	if(sl<=t[x].l&&sr>=t[x].r) return t[x].sum;
	const int mid=t[x].l+t[x].r>>1; int ret=0;
	if(sl<=mid) ret+=query(x<<1,sl,sr);
	if(sr>mid) ret+=query(x<<1|1,sl,sr);
	return ret;
}
signed main(){
	//system("fc stack4.out stack4.ans");
	file();
  	n=read(),q=read(); 
	for(rg int i=1;i<=n;++i) s[i].insert(n+1);
  	for(rg int i=1;i<=n;++i) a[i]=read();
  	for(rg int i=1;i<=n;++i) b[i]=read();
  	for(rg int i=1,l,r;i<=q;++i) l=read(),r=read(),m[l].epb(que(r,i));
  	build(1,1,n);
  	for(rg int i=n;i;--i){
  		const int sr=min(bound(1,b[i]),*s[a[i]].begin());
  		assign(1,i+1,sr-1); insert(1,i); s[a[i]].insert(i);
  		for(que j:m[i]) ans[j.id]=query(1,i,j.r);
  	}
  	for(rg int i=1;i<=q;++i) printf("%d\n",ans[i]);
  	return 0;
}
```


---

## 作者：Naro_Ahgnay (赞：3)

## 题目大意
现维护一个单调栈，有两个决定的变量 $a_i,b_i$。向栈中加入元素 ($a_i,b_i$) 时，先不断弹出栈顶元素直至栈空或栈顶元素 ($a_j,b_j$) 满足 $a_j≠b_j$ 且 $b_i<b_j$ ，然后将其加入栈中。

如果一个二元组入栈后栈内只有这一个元素，则称该二元组是“成功的”。

询问 $q$ 次，每次询问区间 $[l,r]$ 之间有多少个二元组是“成功的”。

## 思路

看到此题，第一反应是莫队算法。再一看数据范围——$n,q<=10^5$，硬上莫队的话有点悬。考虑带一个 $\log$ 的算法。

最初，我们先将所有二元组加入栈中。同时，记录每个二元组在单调栈中前一个数的编号，若没有前一个数，将编号记为零。将所有二元组在单调栈中前一个数的编号在一个优先队列中从小到大排序。这是最重要的部分，记住了奥。

然后，将所有询问离线处理，按照左端点从小到大排序。注意：在该做法中，不用管右段点是不是从小到大排序的。

接下来，将优先队列队头中每一个前一个数的编号小于左端点的二元组贡献加上一。为了维护这个贡献，我们使用树状数组保存，实现每一次增加贡献为 $O(\log n)$。

最后，对于每一次询问的答案就是 $sum(r)-sum(l-1)$。

时间复杂度：排序：$O(q\log q)$，询问 $O(n\log n)$。总时间复杂度：$O(n\log n+q\log q)$。

## code
```cpp
//sto 吴戈 orz 保我AC此题 
#include<bits/stdc++.h>
using namespace std;
struct node1{
	int l,r,id;
}d[500001];
struct node2{
	int a,b,id;
}a[500001];
int n,q;
long long ans[500001],t[500001];
stack<node2> st;
priority_queue<pair<int,int> > qu;
inline int read()
{
	int x(0);char ch=getchar();
	while(ch<48||ch>57) ch=getchar();
	while(ch>=48&&ch<=57) x=x*10+(ch^48),ch=getchar();
	return x;
}
bool cmp(node1 x,node1 y)
{
	return x.l==y.l?x.r<y.r:x.l<y.l;
}
void add(int x)
{
	for(;x<=n;x+=x&-x) t[x]++;
	return;
}
long long sum(int x)
{
	long long s=0;
	for(;x;x-=x&-x) s+=t[x];
	return s;
}
int pr[30],cnt;
void pu(long long x)
{
	while(x) pr[++cnt]=x%10,x/=10;
	while(cnt) putchar(pr[cnt--]+48);
	putchar('\n'); 
}
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i].a=read(),a[i].id=i;
	for(int i=1;i<=n;i++) a[i].b=read();
	for(int i=1;i<=q;i++) d[i].l=read(),d[i].r=read(),d[i].id=i;
	for(int i=1;i<=n;i++)
	{
		while(!st.empty()&&(st.top().b<=a[i].b||st.top().a==a[i].a)) st.pop();
		if(st.empty()) qu.push(make_pair(0,i));else qu.push(make_pair(-st.top().id,i));st.push(a[i]);
	}
	sort(d+1,d+1+q,cmp);
	for(int i=1;i<=q;i++)
	{
		while(!qu.empty()&&-qu.top().first<d[i].l) {add(qu.top().second);qu.pop();} 
		ans[d[i].id]=sum(d[i].r)-sum(d[i].l-1);
	}
	for(int i=1;i<=q;i++) pu(ans[i]);
	return 0;
}
```


---

## 作者：qwqUwU (赞：3)

## 丹钓战   题解报告

看到这种 $Q$ 次询问区间的题，不难往 $O(n)$ 预处理 $O(logn)$ 查询想。

可以想到直接做一次 $1\sim n$ の 单调栈，记录每一个点**入栈前的栈顶** $l_i$。

为什么要这样做呢？

因为对于每一个点 $i$，只有在询问 $l\sim r$ 满足 $l>l_i \wedge i\le r$ 时，$i$ 才会产生 $1$ 的贡献。

也就是说，询问 $l\sim r$ 的答案为

$$ans=\sum_{i=1}^{r} [l_i < l \le i]$$

观察到算式里有 $\sum_{i=1}^{r}$ 这个式子，可以考虑**离线**所有询问，按照 $r$ 从小到大排序。

然后开一个**值域** $t$ 统计每个值被多少个区间覆盖，即**区间加**。

想到这里，就自然会想到**树状数组**+**差分**的做法，对于区间加 $l_i+1\sim i$ 转化为 $t[l_i+1]+1$，$t[i+1]-1$，最后前缀和即可。

上代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lb(x) (x&(-x))
using namespace std;
const int N=5e5+10;
int n,Q,a[N],b[N],ans[N];
struct Question{
	int l,r,id;
}q[N];
inline bool cmp(Question a,Question b){
	return a.r==b.r?a.l<b.l:a.r<b.r;
}
stack<int>st;
int l[N];
int tree[N<<1];
inline void add(int x,int k){
	while(x<=n){
		tree[x]+=k;
		x+=lb(x);
	}
}
inline int query(int x){
	int res=0;
	while(x){
		res+=tree[x];
		x-=lb(x);
	}
	return res;
}
int main(){
//	freopen("stack.in","r",stdin);
//	freopen("stack.out","w",stdout);
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	for(int i=1;i<=n;i++)scanf("%d",b+i);
	for(int i=1;i<=Q;i++)scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
	sort(q+1,q+Q+1,cmp);
	for(int i=1;i<=n;i++){
		while(!st.empty()&&(a[st.top()]==a[i]||b[st.top()]<=b[i]))st.pop();
		if(st.empty())l[i]=1;
		else l[i]=st.top()+1;
		st.push(i);
	}
	int lst=0;
	for(int i=1;i<=Q;i++){
		while(lst<q[i].r){
			lst++;
			add(l[lst],1);
			add(lst+1,-1);
		}
		ans[q[i].id]=query(q[i].l);
	}
	for(int i=1;i<=Q;i++)printf("%d\n",ans[i]);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
```


---

## 作者：FjswYuzu (赞：3)

对于一个元素 $(a_i,b_i)$，如果继续顺次加入元素直到加入 $(a_j,b_j)$ 导致自己被弹出，那么就连边 $i \to j$。如果不存在，那就 $i \to n+1$。

这是一个树形结构，结合题目考虑一条边的实际意义。假设我们从 $(a_l,b_l)$ 开始加，在加入 $(a_p,b_p)$ 的时候被弹出（意味着边 $l \to p$），可以知道 $l,p$ 都会对答案造成贡献。直到加入完 $[l,r]$ 内的所有元素后，$(a_q,b_q)$ 留在栈底，还会造成一点贡献。

那么不难发现，从 $l$ 开始跳父边直到跳到的点编号大于 $r$ 的跳跃次数就是答案。

还有问题是，怎么建父边才能保证正确？

答案是从 $1$ 开始用单调栈根据题意模拟即可。在做 $[l,r]$ 的时候，加入 $[l+1,p-1]$ 也不会使 $l$ 弹出，在实际上是和从 $1$ 开始相同的。

这样的话就可以直接倍增了。时间复杂度 $O(n \log n)$。

```cpp
int n,q;
int a[500005],b[500005],top,stk[500005],fa[20][500005];
bool cmp(int x,int y)
{
	if((a[x]^a[y]) && b[x]<b[y])	return true;
	return false;
}
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;++i)	a[i]=read();
	for(int i=1;i<=n;++i)	b[i]=read();
	for(int i=1;i<=n;++i)
	{
		while(top && !cmp(i,stk[top]))	fa[0][stk[top]]=i,--top;
		stk[++top]=i;
	}
	for(int i=1;i<=n;++i)	if(!fa[0][i])	fa[0][i]=n+1;
	for(int i=0;i<=19;++i)	fa[i][n+1]=n+1;
	for(int i=1;i<=19;++i)	for(int j=1;j<=n;++j)	fa[i][j]=fa[i-1][fa[i-1][j]];
	while(q-->0)
	{
		int l=read(),r=read();
		int ans=0,u=l;
		for(int i=19;~i;--i)	if(fa[i][u]<=r)	ans|=(1<<i),u=fa[i][u];
		++ans;
		write(ans),puts("");
	}
	return 0;
}
```

---

## 作者：Meaninglessness (赞：3)

whker 过来写一篇题解。

观察到每个二元组会被它前面的一个二元组卡住，或者没有，我们将其记为 $lst_i$，没有记 $lst_i=0$。

用单调栈求出 $lst$ 数组后，考虑对于一个二元组 $x$ 在区间 $[l,r]$ 满足什么要求时会记作“成功的”。

不难想到，如果唯一能卡住他的二元组在区间外，即 $lst_x<l$，那么这一定是一个“成功的”二元组。

然后就可以实现了，具体用树状数组、倍增还是其它都随便你，复杂度为 $O(n\log n)$。

---

## 作者：Otomachi_Una_ (赞：2)

和之前的题目差不多类型。我主要讲一下我赛时是怎么做出来的。

## 解题思路

### 1. 按照往年的题目发现应该要枚举左界 $l$
实际上当 $l$ 确定以后，成功的数组和 $r$ 无关。直接前缀和优化即可。

### 2. 发现实际上 $a$ 数组能改变的东西很少，干脆不考虑

不考虑 $a$ 数组以后，为题就变成了有多少个 $i$ 使得 $\min_{j=l}^i a_j=a_i$。实际上我们把 $a$ 数组理解成一座座山，本质上就是有多少个点可以看到 $l$ 这个位置。

我们假设 $las_i$ 表示第一个 $j>i$ 使得 $a_j>a_i$。那么最终所有的可以看到 $l$ 位置的 $i$ 实际上是 $i,las_i,las_{las_i},\dots$。我们可以把它理解成为“链 $i$”。

现在考虑如何从 $l$ 转移到 $l+1$。

经过简单的枚举可以发现“链 $l$”和“链 $l+1$”如果在某处重合了，那么后面也会重合。

所以当 $l$ 转移到 $l+1$ 的时候只要把所有多出来的“成功二元组”丢进去树状数组维护即可。

时间复杂度 $\mathcal O(n\log n)$

### 3. 重新考虑 $a$ 数组，乱搞出正解

根据前面的经验，我们只需要重新改造 $a$ 数组的意义。

$las_i$ 数组本质上就是 $i$ 在栈尾，第一个丢掉它的元素。那我们同样地构造就可以了。

然后随便试了一下换 $las$ 的推导公式，直接出来正解

## 参考代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
const int MAXN=5e5+5;
int n,m;
int a[MAXN];
int b[MAXN];
int las[MAXN];bool flag[MAXN];
int st[MAXN];int cnt=0;
int tree[MAXN];
struct ask{
	int l,r,id;
}q[MAXN];
int ans[MAXN];
bool cmp(ask x,ask y){
	return x.l<y.l;
}
int lowbit(int x){
	return ((-x)&x);
}
void update(int x,int k){
	while(x<=n){
		tree[x]+=k;
		x+=lowbit(x);
	}
	return;
}
int query(int x){
	int r=0;
	while(x){
		r+=tree[x];
		x-=lowbit(x);
	}
	return r;
}
inline int read(){
	int re=0;char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while(ch>='0'&&ch<='9') re=10*re+ch-'0',ch=getchar();
	return re;
}
int main(){
	//freopen("stack.in","r",stdin);
	//freopen("stack.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	for(int i=1;i<=m;i++)
		q[i].l=read(),q[i].r=read(),q[i].id=i;
	sort(q+1,q+m+1,cmp);
	for(int i=n;i>=1;i--){
		while((b[st[cnt]]<b[i]&&a[i]!=a[st[cnt]])&&cnt>0) cnt--;
		las[i]=st[cnt];
		st[++cnt]=i;
	}
	int k=0;
	for(int i=1;i<=n;i++){
		for(int j=i;j;j=las[j])
			if(!flag[j]){
				flag[j]=true;
				update(j,1);
			}
        else break;//一定一定要记得break!!!!!!!
		while(k<m&&q[k+1].l==i){
			k++;
			ans[q[k].id]=query(q[k].r)-query(q[k].l-1);
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

## Upd 2022.3.30

源代码当中少了一个 `else break;` 直接挂掉了 $45pts$。

警醒后人！

---

## 作者：SUNCHAOYI (赞：1)

丹钓战，顾名思义单调栈。

首先是 $\texttt{15 pts}$ 做法，对于每个询问的区间，进行一次单调栈的模拟。时间复杂度 $O(nq)$。   

然后可以稍微的优化一下，我们可以进行 $n$ 次单调栈来维护以第 $i$ 个数为起点的区间的答案。时间复杂度 $O(n^2)$，预计得分 $\texttt{30 pts}$。 

数据点 $11-15$，针对的是序列的一些特殊性质，与最终算法可能关系不大，在此不赘述。接下来讲正解。

一个二元组如果是“成功的”，那么会有一个明显的特征，就是该二元组可以弹出所有入栈的二元组，并成为唯一的二元组被压入栈。当然，栈为空时将其压入栈便是一种特殊的情况，因此可以说是仍然满足该特征。所以我们可以定义 `pre[i]` 表示第 $i$ 个二元组可以弹出的最早的二元组所对应的编号，显然初始化有 `pre[i] = i`。询问一段区间中有多少个二元组符合题意，也就是求出该区间中的 `pre[i]` 满足小于等于区间左端点的个数。举个例子，区间 $[2,4]$ 对应的 `pre[i]` 的值为 $1,2,3$，则编号为 $2,3$ 的二元组符合题意。所以说，对于一个 `pre[i]`，它会对区间 `[pre[i],i]` 均产生贡献。那么，我们只需要按编号从小打大扫描一遍后分别求出询问左端点对应的答案即可。

那么如何求 `pre[i]` 的值呢，联系题目名称，不禁再次想到单调栈。当栈顶被弹出时，同时更新 `pre[i]` 的值为 `pre[s.top ()]` 即可。维护产生的贡献，不难看出是区间加的操作，当求解时，又是单点询问，于是树状数组变成了本题的首选（~~码量大，常数大的线段树默默靠边~~）。最后需要注意的一点时，因在扫描时的顺序为编号从小到大，而询问无序，因此我们需要对询问进行处理，以右端点为下标，记录左端点，这样在求解时左端点的答案就已经被计算出来了。总时间复杂度为 $O(n \log n)$。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stack>
#include <vector>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 5e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
vector <int> point[MAX];
stack <int> s;
int n,q,a[MAX],b[MAX],c[MAX],pre[MAX];
struct node
{
	int l,r,ans;
} query[MAX];
void add (int x,int y);
int ask (int x);
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();q = read ();
	for (int i = 1;i <= n;++i) a[i] = read ();
	for (int i = 1;i <= n;++i) b[i] = read ();
	for (int i = 1;i <= q;++i)
	{
		query[i].l = read (),query[i].r = read ();
		point[query[i].r].push_back (i);//右端点为下标
	}
	for (int i = 1;i <= n;++i)
	{
		pre[i] = i;//初始化
		while (!s.empty () && (a[s.top ()] == a[i] || b[s.top ()] <= b[i])) pre[i] = pre[s.top ()],s.pop ();//单调栈维护
		s.push (i);
	}
	for (int i = 1;i <= n;++i)
	{
		add (pre[i],1);add (i + 1,-1);//树状数组区间更新
		for (int j = 0;j < point[i].size ();++j) query[point[i][j]].ans = ask (query[point[i][j]].l);//对于若干个以 i 为右端点的询问，进行求解
	}
	for (int i = 1;i <= q;++i)
		printf ("%d\n",query[i].ans);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
void add (int x,int y)
{
	for (int i = x;i <= n;i += (i & (-i))) c[i] += y;
}
int ask (int x)
{
	int sum = 0;
	for (int i = x;i;i -= (i & (-i))) sum += c[i];
	return sum;
}
```

---

## 作者：Lonely_NewYear (赞：1)

# P8251 题解

## 题目大意

给出一个序列和一个单调栈，问当需要顺序插入序列中一段区间中的元素时，在多少个元素插入后，单调栈中只剩这一个元素。

## 题目分析

注意到每次都是按一个固定的顺序插入某一段元素的。

所以说无论插入的是哪一段区间，对于某个元素来说，最后都一定是一个固定的元素把这个元素弹出。

所以可以先模拟一遍单调栈求出每个元素被哪个元素弹出，记为 $f_i$。

再分析一下每个问题。

首先插入第一个元素，显然此时单调栈中只有这一个元素，$ans++$。

现在这个元素在栈底，所以说如果有其他元素想到达栈底，就必须先把它弹出，这个我们已经求过了，能够把它弹出的那个元素是 $f_i$。

弹出栈底后，还要加入元素 $f_i$，所以此时单调栈中只有一个 $f_i$，$ans++$。

接下来还是一样，要找到下一个能把栈底弹出的数，即 $f_{f_i}$，直到下一个能把栈底弹出的数超出了 $r$。

此时问题就转化为，从 $l$ 开始沿 $f$ 数组往后跳，问跳几个数会超出 $r$。

这显然是倍增板子。

记 $f_{i,j}$ 为从 $i$ 开始往后跳 $2^j$ 次能到达哪个元素。

直接用倍增求出跳多少次即可。

时间复杂度 $O(n\log n)$。

记得加快读。

## 代码

```cpp
#include<cstdio>
using namespace std;
int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x;
}
void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
int n,q;
int a[500001],b[500001];
int sa[500001],sb[500001],sid[500001],top;//单调栈
int f[500002][20];//倍增数组
int main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)//模拟单调栈，求每个元素被哪个元素弹出
	{
		while(top&&(sa[top]==a[i]||sb[top]<=b[i]))
			f[sid[top--]][0]=i;
		top++,sa[top]=a[i],sb[top]=b[i],sid[top]=i;
	}
	while(top)f[sid[top--]][0]=n+1;
//求倍增数组
	for(int i=0;i<20;i++)
		f[n+1][i]=n+1;
	for(int i=1;i<20;i++)
		for(int j=1;j<=n;j++)
			f[j][i]=f[f[j][i-1]][i-1];
	while(q--)
	{
		int l=read(),r=read(),ans=1;
		for(int i=19;i>=0;i--)
			if(f[l][i]<=r)
				ans+=1<<i,l=f[l][i];
		write(ans);
		puts("");
	}
	return 0;
}
```

谢谢观看！

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8251)

## 题意

有 $n$ 个二元组 $(a_i, b_i)$，编号为 $1$ 到 $n$。

有一个初始为空的栈 $S$，向其中加入元素 $(a_i, b_i)$ 时，先不断弹出栈顶元素直至栈空或栈顶元素 $(a_j , b_j)$ 满足 $a_i \neq a_j$ 且 $b_i < b_j$，然后再将其加入栈中。

如果一个二元组入栈后栈内只有这一个元素，则称该二元组是“成功的”。

有 $q$ 个询问 $[l, r]$，表示若将编号在 $[l, r]$ 中的二元组按编号从小到大依次入栈，会有多少个二元组是“成功的”。

询问之间相互独立。

## 分析

仔细观察可以发现，在加入元素 $(a_i, b_i)$ 前，弹出元素后，要么栈变空了，要么会出现一个满足 $a_i = a_{c_i}$ 或 $b_i > b_{c_i}$ 的元素 $(a_{c_i}, b_{c_i})$ 阻止弹出，又因为加入操作的顺序是固定从左到右的，所以 $c_i$ 是固定的一个数（如果 $c_i$ 不存在则设为 $0$）。

所以在一组询问 $[l,r]$ 中，二元组 $(a_i, b_i)(l\le i\le r)$ 是成功的仅当 $c_i$ 不在 $[l,r]$ 中，即 $c_i<l$。

那么，问题就转化成了求 $c_i<l(l\le i\le r)$ 的个数。

于是大致流程就出来了。

首先把询问读入，要进行离线处理，再根据题意模拟一遍，求出所有的 $c_i$，同时把 $c_i$ 放进树状数组，求出 $c_i$ 的个数的前缀和 $sum_{l-1},sum_r$，二者的差就是答案。

## 代码

时间复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=5e5+10;
int n,q,a[N],b[N],z[N],t,ans;
struct Q{
	int l,r,ans;
}d[N];
int headl[N],nxtl[N*2],verl[N*2],totl;
void addl(int x,int y){
	verl[++totl]=y;
	nxtl[totl]=headl[x];
	headl[x]=totl;
}
int headr[N],nxtr[N*2],verr[N*2],totr;
void addr(int x,int y){
	verr[++totr]=y;
	nxtr[totr]=headr[x];
	headr[x]=totr;
}
vector<int>el[N],er[N];
int f[N];
void add(int x,int v){
	x++;
	for(;x<=n;x+=x&-x)
		f[x]+=v;
}
int ask(int x){
	x++;
	int ans=0;
	for(;x;x-=x&-x)
		ans+=f[x];
	return ans;
}
int main(){
	//freopen("stack.in","r",stdin);
	//freopen("stack.out","w",stdout);
	n=read();q=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=read();
	for(int i=1;i<=q;i++){
		d[i].l=read();
		d[i].r=read();
		addl(d[i].l-1,i);
		addr(d[i].r,i);
	}
	for(int i=1;i<=n;i++){
		while(t&&(a[z[t]]==a[i]||b[z[t]]<=b[i]))
			t--;
		add(z[t],1);
		z[++t]=i;
		for(int j=headl[i];j;j=nxtl[j])
			d[verl[j]].ans-=ask(d[verl[j]].l-1);
		for(int j=headr[i];j;j=nxtr[j])
			d[verr[j]].ans+=ask(d[verr[j]].l-1);
	}
	for(int i=1;i<=q;i++){
		write(d[i].ans);
		puts("");
	}
	return 0;
}
```


---

## 作者：staly (赞：0)

我们可以维护每个二元组与其不冲突的前驱 $pre_i$，也就是说，$pre_i$ 到 $i$ 的所有二元组都可以被二元组 $i$ 换出来。特别的，如果该二元组没有前驱，前驱记为第 $0$ 个二元组。如果 $pre_i < l$，二元组就会把单调栈中所有二元组换出来，成为一个“成功”的二元组。原先的问题就被转化为求 $pre$ 数组中 $[l,r]$ 的区间内小于 $l$ 的元素数量问题。

该问题有不少解决方法，但树状数组较为方便。我们把询问按 $l$ 的大小排序。处理询问前先把所有小于 $l$ 的元素对应的位置改成 $1$，询问的答案就等于 $[l,r]$ 中 $1$ 的数量，在数值上等于 $r$ 与 $l-1$ 的前缀和之差。

代码如下：

```cpp
#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;
const int maxn = 5e5 + 7;
int n, m;
int a[maxn], b[maxn];
int s[maxn], scnt;
pair<int, int> pre[maxn];
int c[maxn];
pair<pair<int, int>, int> q[maxn];
int ans[maxn];
void add(int x, int k)
{
    for (; x <= n; x += x & -x)
        c[x] += k;
}
int ask(int x)
{
    int k = 0;
    for (; x; x -= x & -x)
        k += c[x];
    return k;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]);
    s[++scnt] = 0, b[0] = 1e7;
    for (int i = 1; i <= n; i++)
    {
        while (a[s[scnt]] == a[i] || b[s[scnt]] <= b[i])
            scnt--;
        pre[i] = make_pair(s[scnt], i);
        s[++scnt] = i;
    }
    sort(pre + 1, pre + n + 1);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &q[i].first.first, &q[i].first.second);
        q[i].second = i;
    }
    sort(q + 1, q + m + 1);
    int p = 1;
    for (int i = 1; i <= m; i++)
    {
        while (p <= n && pre[p].first < q[i].first.first)
            add(pre[p].second, 1), p++;
        ans[q[i].second] = ask(q[i].first.second) - ask(q[i].first.first - 1);
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", ans[i]);
    }
}

```

---

## 作者：novax (赞：0)

[题面](https://www.luogu.com.cn/problem/P8251)。

### 思路

由于二元组以从左到右顺序入栈，所以如果从头开始入栈且元素 $x$ 在插入元素 $y$ 时被弹出栈，那么从 $x$ 前的任何一个元素为起点入栈，$x$ 都会在插入 $y$ 时被弹出。

本题所要求的是在按给定区间插入元素，能把栈弹空的元素数量，则考虑一个下标 $x$ 的元素，当其为合法的答案时仅当 $[L,x-1]$ 都已经被弹出。设从头开始入栈，元素 $x$ 入栈时的栈顶元素下标为 $last$，则根据刚才的结论，如果当前询问的 $L$ 在 $[last+1,x-1]$ 之间，元素 $x$ 就是该询问的一个合法答案。因为这个区间内的所有元素都会在插入 $x$ 之前被弹出栈，而最近的一个不会被弹出的元素 $last$ 在该询问中未曾入栈。

因此我们可以先用单调栈跑一遍整个二元组序列，得到每一个元素 $x$ 的对应 $last_x$。对于每个询问 $[L,R]$，相当于求满足 $last_x < L$ 且 $L \leq x \leq R$ 的元素 $x$ 数量。

可以对询问离线，使用树状数组实现。

### 代码

```cpp
#include <cstdio>
#include <algorithm>
const int Nx=500010;
int N,Q,A[Nx],B[Nx],con[Nx],lst[Nx],L[Nx],R[Nx],idx[Nx],ans[Nx];
bool cmp_c(int x,int y){return lst[x]<lst[y];}
bool cmp_i(int x,int y){return L[x]<L[y];}
int sta[Nx],top,bit[Nx];
void upd(int x,int delta)
{
	while(x<Nx)
		bit[x]+=delta,x+=x&-x;
}
int query(int x)
{
	int ret=0;
	while(x)
		ret+=bit[x],x-=x&-x;
	return ret;
}
int main()
{
	scanf("%d%d",&N,&Q);
	int i,j,k;
	for(i=1;i<=N;i++)
		scanf("%d",&A[i]);
	for(i=1;i<=N;i++)
		scanf("%d",&B[i]);
	for(i=1;i<=Q;i++)
	{
		scanf("%d%d",&L[i],&R[i]);
		idx[i]=i;
	}
	for(i=1;i<=N;i++)
	{
		con[i]=i;
		while(top>0&&B[i]>=B[sta[top]])
			top--;
		while(top>0&&A[i]==A[sta[top]])
			top--;
		lst[i]=sta[top];
		sta[++top]=i;
	}
	std::sort(idx+1,idx+Q+1,cmp_i);
	std::sort(con+1,con+N+1,cmp_c);
	j=1;k=1;
	for(i=0;i<=N;i++)
	{
		while(lst[con[j]]==i)
			upd(con[j],1),j++;
		while(L[idx[k]]==i+1)
			ans[idx[k]]=query(R[idx[k]])-query(L[idx[k]]-1),k++;
	}
	for(i=1;i<=Q;i++)
		printf("%d\n",ans[i]);
}
```


---

## 作者：comando (赞：0)

**定义1：** $(a_j,b_j)$ 是 $(a_i,b_i)$ 的**宿敌**当且仅当 $\forall l\le j,r\ge l$ ，二元组 $(a_i,b_i)$ 不是“成功的”。为了方便讨论，规定 $(a_0,b_0)$ 是一切二元组的宿敌。

**定义2：** $(a_j,b_j)$ 是 $(a_i,b_i)$ 的**最近宿敌**当且仅当 $j$ 是满足 $(a_j,b_j)$ 是 $(a_i,b_i)$ 的宿敌的最大的 $j$。

记 $f(i)$ 为 $(a_i,b_i)$ 的最近宿敌的下标。

由定义显然： $(a_i,b_i)$ 是“成功的” 当且仅当 $f(i)\lt l\le i,r\ge i$。

我们可以模拟一次入栈、弹栈的过程，那么当 $(a_i,b_i)$ 入栈时，栈顶元素即是它的宿敌。由此我们在 $O(n)$ 的复杂度内求出了所有 $f(i)$。

接下来考虑如何用 $f(i)$ 求出答案。

题目中的查询就是要求使得 $f(i)\lt l ,i\in [l,r]$ 的 $i$ 的个数。不难发现这个东西可以用主席树维护。令主席树中第 $v$ 个版本中区间 $[l,r]$ 表示 $[l,r]$ 中 $f(i)\le v$ 的个数，只要在生成第 $f(i)$ 个版本时将点 $i$ 加入主席树即可。

复杂度是 $O((n+q)\log n)$ 的。鉴于主席树的大常数，可能需要卡常。

------------
以下为考后口胡内容：

事实上我们并不需要主席树来维护历史版本，因为每一个版本只有在查询时的 $l=v+1$ 时会用到。所以可以将查询按 $l$ 排序，然后用一颗线段树或者树状数组在生成版本的同时处理查询。这样常数应该会小很多。


考场代码（极其惨烈的主席树做法）（既被卡时间又被卡空间）：https://www.luogu.com.cn/record/72364566   

AC代码（线段树做法）：  
```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>
using namespace std;

template<typename Int>
class xds{
	private:
		class node{
			public:
				node *lc,*rc;
				Int value,tag;
				virtual ~node(){delete lc,delete rc;}
				node(){lc=rc=nullptr;}
				node(const Int&value){lc=rc=nullptr;this->value=value;tag=0;}
		};
		node *root;
		size_t ln,rn;
		xds(){;}
		static node* build(size_t left,size_t right)
		{
			if(right==left+1)
				return new node(0);
			size_t mid=(left+right)/2;
			node *pt=new node;
			pt->lc=build(left,mid),pt->rc=build(mid,right);
			pt->tag=0,pt->value=pt->lc->value+pt->rc->value;
			return pt;
		}
		static void pushtag(size_t left,size_t right,node *pt)
		{
			if(pt->lc==nullptr)
				return;
			size_t mid=(left+right)/2;
			pt->lc->tag+=pt->tag,pt->rc->tag+=pt->tag;
			pt->lc->value+=pt->tag*(mid-left),pt->rc->value+=pt->tag*(right-mid);
			pt->tag=0;
			return;
		}
		static void add(size_t left,size_t right,size_t l,size_t r,Int x,node* pt)
		{
			if(l<=left&&r>=right)
			{
				pt->value+=(right-left)*x;
				pt->tag+=x;
				return;
			}
			if(l>=right||r<=left)
				return;
			pushtag(left,right,pt);
			size_t mid=(left+right)/2;
			add(left,mid,l,r,x,pt->lc),add(mid,right,l,r,x,pt->rc);
			pt->value=pt->lc->value+pt->rc->value;
			return;
		}
		static Int quest(size_t left,size_t right,size_t l,size_t r,node* pt)
		{
			if(l<=left&&r>=right)
				return pt->value;
			if(l>=right||r<=left)
				return 0;
			pushtag(left,right,pt);
			size_t mid=(left+right)/2;
			return quest(left,mid,l,r,pt->lc)+quest(mid,right,l,r,pt->rc);
		}
	public:
		xds(size_t left,size_t right)
		{
			ln=left,rn=right;
			root=build(left,right);
			return;
		}
		void add(size_t l,size_t r,Int x)
		{
			add(ln,rn,l,r,x,root);
		}
		Int quest(size_t l,size_t r)
		{
			return quest(ln,rn,l,r,root);
		}
};

class pnt{
	public:
		int pos,a,b;
		pnt(int _pos,int _a,int _b){pos=_pos,a=_a,b=_b;}
};

int n,q;
int a[500010],b[500010];
vector<pair<int,int> >pre;
stack<pnt> stk;
xds<int> *tree;

class que{
	public:
		int l,r,ans,pos;
		bool operator<(const que&x)const{
			return l==x.l?r<x.r:l<x.l;
		}
};

bool tmp(const que&x,const que&y)
{
	return x.pos<y.pos;
}

void work(istream&ins,ostream&ous)
{
	ins>>n>>q;
	for(int i=1;i<=n;i++)
		ins>>a[i];
	for(int i=1;i<=n;i++)
		ins>>b[i];
	for(int i=1;i<=n;i++)
	{
		while(!stk.empty()&&(stk.top().a==a[i]||stk.top().b<=b[i]))
			stk.pop();
		if(stk.empty())
		{
			pre.push_back(make_pair(0,i));
		}
		else
		{
			pre.push_back(make_pair(stk.top().pos,i));
		}
		stk.push(pnt(i,a[i],b[i]));
	}
	vector<que>qes;
	for(int i=0;i<q;i++)
	{
		que x;
		ins>>x.l>>x.r;
		x.pos=i;
		qes.push_back(x);
	}
	sort(qes.begin(),qes.end());
	sort(pre.begin(),pre.end());
	tree=new xds<int>(0,n+1);
	int it=0;
	int it2=0;
	for(int i=0;i<n;i++)
	{
		while(it<pre.size()&&pre[it].first<=i)
		{
			tree->add(pre[it].second,pre[it].second+1,1);
			it++;
		}
		while(it2<q&&qes[it2].l-1==i)
		{
			qes[it2].ans=tree->quest(qes[it2].l,qes[it2].r+1);
			it2++;
		}
	}
	sort(qes.begin(),qes.end(),tmp);
	for(int i=0;i<q;i++)
	{
		ous<<qes[i].ans<<'\n';
	}
	delete tree;
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	work(cin,cout);
	return 0;
}
```



---

