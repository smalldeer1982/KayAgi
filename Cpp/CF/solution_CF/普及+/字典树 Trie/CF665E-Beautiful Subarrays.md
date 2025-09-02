# Beautiful Subarrays

## 题目描述

One day, ZS the Coder wrote down an array of integers $ a $ with elements $ a_{1},a_{2},...,a_{n} $ .

A subarray of the array $ a $ is a sequence $ a_{l},a_{l+1},...,a_{r} $ for some integers $ (l,r) $ such that $ 1<=l<=r<=n $ . ZS the Coder thinks that a subarray of $ a $ is beautiful if the bitwise xor of all the elements in the subarray is at least $ k $ .

Help ZS the Coder find the number of beautiful subarrays of $ a $ !

## 样例 #1

### 输入

```
3 1
1 2 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 2
1 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 3
1 2 3
```

### 输出

```
2
```

# 题解

## 作者：wanghaoyu1008 (赞：12)

这道题的思路是比较显然的，但实现上就会有些细节，

我们知道，一个数异或其本身为0，而任何数异或0还是自身，

就可以用异或前缀和$s[ 0..n ]$来表示区间异或和了。（学术文章本来是该打实心句号的，这里懒得调成英文模式了）


------------
有了异或前缀和，我们对于1~n中的每个i，

求以第i的数结尾的区间异或和大于等于k的有多少，

即$s[ 0..i-1 ]$中有多少个与$s[ i ]$异或大于等于k。


------------
对$s[ 0..i-1 ]$建一棵$trie$树，

由高位到低位考虑每位，

如果到该位异或的结果已经大于k，就累计，

如果小于k，直接无视，

到该位不能确定，接着往下一层走


------------
以下是代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int X=2147483647;
const int N=1e6+1;
const int L=30;

int n,k;
int t[30*N][2],cnt;
int a[30*N];

int work(int s)
{
	int v,sum=0,p=k,q=s,i;
	v=1;                   //solve
	for(i=0;i<=L;i++){
		if(!v)break;
		if(p>>L){
			v=t[v][1^(q>>L)];//不确定往下走
            				//小于就不管
		}
		else{
			sum+=a[t[v][1^(q>>L)]];//大于直接统计
			v=t[v][q>>L];  //不确定往下走
		}
		p=(p<<1)&X;
		q=(q<<1)&X;
	}
	v=1;                   //以下是把当前的数加入trie树
	++a[v];
	for(i=0;i<=L;i++){
		if(t[v][s>>L])v=t[v][s>>L];
		else ++cnt,t[v][s>>L]=cnt,v=cnt;
		s=(s<<1)&X;
		++a[v];
	}
	return sum;
}

int main()
{
	int i,p,s=0;
	scanf("%d%d",&n,&k);
	cnt=1;
	k=k-1;                //不好统计等于的情况，就不统计
	long long ans=work(s);
	for(i=1;i<=n;i++){
		scanf("%d",&p);
		s=s^p;
		ans+=work(s);
	}
	printf("%lld",ans);  //如果要交到cf上，这要用%I64d
	return 0;
}
```

---

## 作者：Kobe303 (赞：5)

思路应该是能一眼出的吧。。

设 $pre_i=\oplus_{j=1}^{i}a_j$，且 $pre_0=0$。

那么区间异或和就可以转化成两个值的异或和。

即 $\oplus_{i=l}^{r}a_i=pre_r\oplus pre_{l-1}$。

那么就可以考虑用 $\texttt{Trie}$ 树来维护。

时间复杂度为 $\mathcal O(n\log w)$。

具体看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
int n, k;
int pre;
int trie[N*30][2], tot = 1;
int cnt[N*30]; //结点被经过的次数
ll ans;

void insert(int x) {
	int p = 1;
	for (int i = 30; ~i; --i) {
		int c = x >> i & 1;
		if (!trie[p][c]) trie[p][c] = ++tot;
		p = trie[p][c];
		++cnt[p];
	}
}

int query(int x, int y) {
	int p = 1, res = 0;
	for (int i = 30; ~i; --i) {
		int c1 = x >> i & 1, c2 = y >> i & 1;
		if (c2) {
			p = trie[p][c1 ^ 1];
		} //如果 y 这一位是 1，那么只能走，不能累加。
		else {
			res += cnt[trie[p][c1 ^ 1]];
			p = trie[p][c1];
		} //否则直接加上那一棵子树被经过的次数，然后往另一边走。
	}
   //注意上面统计的是大于。
	res += cnt[p]; //这里统计的是等于。
	return res;
} //查询 Trie 树中与 x 异或大于等于 y 的数量。

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		insert(pre), pre ^= x;
		ans += query(pre, k);
	}
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：yangchenxiao (赞：5)

使用分治，每次只考虑经过$mid$的序列:

对于 $[l,mid]$ 的区间，可以将每个点的后缀异或和挂在 $01 trie$树上；而在 $[mid+1,r]$ 的区间，根据异或可以相互抵消的性质，先求取每个点的前缀异或和，并在对应的左区间建立的$trie$树上查找。

查找过程：分解出k二进制的每一位op，分解出x二进制的每一位op1，分为以下情况讨论：

- 若op=1， 且trie树上有 $op1$ ^ $1$ 这个儿子，那么走到p的 $op1$ ^ $1$ 的儿子；

- 若op=1， 且trie树上没有 $op1$ ^ $1$ 这个儿子,  那么break；

- 若op=0， 且trie树上有 $op1$ ^ $1$ 这个儿子，那么累计 $op1$ ^ $1$ 儿子的size，如果有op儿子走到 op 儿子，否则berak；

- 若op=0， 且trie树上没有 $op1$ ^ $1$ 这个儿子，那么如果有op儿子走到 op 儿子，否则berak；

### 注意细节：

- 考虑可以开全局变量，但要改变递归顺序，先计算右区间，再计算左区间；

- 特判和k恰好的情况；

时间复杂度：$O$（$nlognlonga$），常数比较大，时间并不是非常好看，但是可以练习分治的思想。

以下是AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+2;
int a[maxn],n,trie[maxn*30][2],size[maxn*30],k,tot;
long long ans;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
void ask(int x){
	int p=0;
	for(int i=30;i>=0;i--){
		bool op=k&(1<<i);
		bool op1=x&(1<<i);
		if(op==0){
			if(op1==0){
				if(trie[p][1])ans+=size[trie[p][1]];
				if(trie[p][0])p=trie[p][0];
				else break;
			}
			else{
				if(trie[p][0])ans+=size[trie[p][0]];
				if(trie[p][1])p=trie[p][1];
				else break;
			}
		}
		else{
			if(op1==0){
				if(trie[p][1])p=trie[p][1];
				else break;
			}
			else{
				if(trie[p][0])p=trie[p][0];
				else break;
			}
		}
		if(i==0)ans+=size[p];//特判与k相等的情况
	}
	return ;
}
void insert(int x){
	int p=0;
	for(int i=30;i>=0;i--){
		bool op=x&(1<<i);
		if(!trie[p][op])trie[p][op]=++tot;
		p=trie[p][op];
		size[p]++;
	}
	return ;
}
void dfs(int l,int r,int op){
	if(l==r){
		if(a[l]>=k)ans++;
		if(op==1)insert(a[l]);
		return ;
	}
	int mid=l+r>>1;
	dfs(mid+1,r,0);
	dfs(l,mid,1);
	int sum=0;
	for(int i=mid+1;i<=r;i++){
		sum^=a[i];
		ask(sum);
	}
	for(int i=0;i<=tot;i++){
		trie[i][0]=trie[i][1]=size[i]=0;//清空trie树
	}
	tot=0;
	if(op){
		sum=0;
		for(int i=r;i>=l;i--){
			sum^=a[i];
			insert(sum);
		}
	}
	return ;
}
int main(){
	n=read();
	k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	dfs(1,n,0);
	cout<<ans;
	return 0;
}
```


---

## 作者：mango09 (赞：4)

[E. Beautiful Subarrays](https://codeforces.com/problemset/problem/665/E)

记录前缀异或和 $s_i$，原式相当于
$$
s_{l - 1}\oplus s_r \ge k
$$
固定 $r$，需要快速求出有多少个满足要求的 $l - 1$，其中 $l - 1\in[0, n - 1]$。

这种异或问题可以考虑使用 01trie。

**注意：一开始需要将 $s_0 = 0$ 插入。**

对第 $i$ 个数 $a_i$，先查询 $a_0\sim a_{i - 1}$ 构成的 01trie，再将 $a_i$ 插入。

查询数 $x$ 的方法如下：

在二进制下，设 $k$ 的第 $i$ 位为 $k_i$，$x$ 的第 $i$ 位为 $x_i$。

- 若 $k_i$ 为 $1$，此时 trie 树只能跳 $\lnot x_i$ 这个儿子，保证当前位异或值为 $1$。
- 若 $k_i$ 为 $0$，选 $\lnot x_i$ 儿子就直接大于 $k$ 了，可以加上该儿子贡献；跳 $x_i$ 使得当前位异或值为 $0$，还不能确定大小。
- 如果儿子不存在，直接 `break`。
- 走到叶子节点意味着异或值等于 $k$，也可以加上该点贡献。

插入操作与正常的 trie 树插入无异，将路径上所有节点的贡献都加一。

[Code](https://codeforces.com/contest/665/submission/172642601)



---

## 作者：SentoAyaka (赞：3)

## [CF665E Beautiful Subarrays](https://www.luogu.com.cn/problem/CF665E)解题报告

### 题意：

给定长度为 n 的序列 a 

给定 k ,求有多少个 a 的子序列 满足 异或和 $\geqslant$ k
		
### 分析：

看到子序列异或和，想到运用前缀和的思想，建立 **前缀异或和** ，那么

 $a_l$ ^ $a_{l+1}$ ^......^ $a_{r-1}$ ^ $a_r$	= $sum_r$ ^ $sum_{l-1}$
 
 对于每个$sum_r$，查找所有$sum_{l-1}$使得其异或值$\geqslant$ k
 
 考虑数据 sum值域 及 异或，使用字典树 _从高位到低位_ 维护，查找时只需使 前i-1位相等 当前位 i 与 $sum_r$的i位 的异或值大于k值的即可累加所有情况，[最后一位需特判]
 
[注意]应加入$sum_0$即先insert(0)
 
#### 对于查找操作

 ```cpp
 
long long search(int val){
	int u=0;long long ans=0;
	for(int k=30;k>=0;k--){
		int c=(val>>k)&1,Mc=(m>>k)&1;	//val即为sum_r，m即为原k
		if(Mc==0&&node[u][c^1])
        	ans+=sum[node[u][c^1]];//m当前位=0，加上使异或和为1的所有情况
		if(k==0){
			if(Mc==1&&node[u][c^1])
            	ans+=sum[node[u][c^1]];//m最后一位为1，加上使异或和为1的所有情况
			if(Mc==0&&node[u][c])
            	ans+=sum[node[u][c]];//m最后一位为0，加上c的值（c^1的值已加过了）
		}
		if(node[u][c^Mc]==0)break;//如果没有合法的值，退出
		u=node[u][c^Mc];
	}
	return ans;
}
```
#### 对于修改操作

```cpp

void insert(int val){
	int u=0;sum[u]++;//已u这种情况结尾的情况数++
	for(int k=30;k>=0;k--){
		int c=(val>>k)&1;
		if(node[u][c]==0){//若无该情况，创建该情况
			node[u][c]=++tot;
		}
		u=node[u][c];sum[u]++;
	}
	return ;
}
````

### 代码

```cpp

const int N=1e6+5;
int n,m,now,node[N*31][2],tot;
long long Ans,sum[N*31];
long long search(int val){
	int u=0;long long ans=0;
	for(int k=30;k>=0;k--){
		int c=(val>>k)&1,Mc=(m>>k)&1;  
		if(Mc==0&&node[u][c^1])ans+=sum[node[u][c^1]];
		if(Mc==1);
		if(k==0){
			if(Mc==1&&node[u][c^1])ans+=sum[node[u][c^1]];
			if(Mc==0&&node[u][c])ans+=sum[node[u][c]];
		}
		if(node[u][c^Mc]==0)break;
		u=node[u][c^Mc];
	}
	return ans;
}
void insert(int val){
	int u=0;sum[u]++;
	for(int k=30;k>=0;k--){
		int c=(val>>k)&1;
		if(node[u][c]==0){
			node[u][c]=++tot;
		}
		u=node[u][c];sum[u]++;
	}
	return ;
}
int main(){
	n=read();m=read();
	insert(0);
	for(int i=1;i<=n;i++){
		int x=read();now^=x;
		Ans+=search(now);
		insert(now);
	}
	cout<<Ans;
	return 0;
}

```



---

## 作者：xixiup (赞：2)

## 思路分享

可以思考，由于异或具有如下性质：
$$
\boxed{x \oplus x=0}\boxed{x \oplus 0=x}
$$
故我们可以考虑使用异或前缀和。

思考，我们可以设 $s_i=\bigoplus\limits_{j=1}^{i} a_j$，则有：
$$
\boxed{\bigoplus\limits_{i=l}^{r}a_i=s_r \oplus s_{l-1}}
$$
然后我们就可以考虑建一个 $trie$ 树来维护 $s_0$ 到 $s_{i-1}$，就可以很方便地处理出 $r=i$ 时的答案了。

## 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1001000,logk=32;
int n,m,s,ans;//这里的m就是k
int cnt=1,ne[maxn*logk][2],si[maxn*logk];
//ne[i]表示节点i的两个子节点，si[i]表示节点i的子树大小
int query(int x){//搜索
	int p=1,sum=0; 
	for(int i=logk-1;i>=1;i--){
		if(p==0){
			break;
		}
		if(((m>>i)&1)==1){//若m的这一位为1则异或的两个数必须不同
			p=ne[p][1^(1&(x>>i))];
		}
		else{
			sum+=si[ne[p][1^(1&(x>>i))]];//若异或后这一位为1且m的这一位为0，则直接统计答案
			p=ne[p][1&(x>>i)];
		}
	}
	if((m&1)==1){//这里是处理最后一位的答案
		sum+=si[ne[p][1^(1&x)]];
	}
	else{
		sum+=si[ne[p][1^(1&x)]];
		sum+=si[ne[p][1&x]];
	}
	return sum;
}
void insert(int x){//加入一个节点
	int p=1;
	si[p]++;
	for(int i=logk-1;i>=0;i--){
		if(ne[p][1&(x>>i)]==0){//若子节点不存在则新建一个
			cnt++;
			ne[p][1&(x>>i)]=cnt;
		}
		p=ne[p][1&(x>>i)];
		si[p]++;
	}
}
int main(){
	cin>>n>>m;
	insert(s);
	for(int i=1;i<=n;i++){
		int q;
		scanf("%d",&q);
		s^=q;
		ans+=query(s);
		insert(s);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：whiteqwq (赞：2)

[CF665E Beautiful Subarrays](https://www.luogu.com.cn/problem/CF665E)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1749657)

## 题意
- 给定一个长度为$n$的序列$a$，求有多少个子序列的异或和大于等于$k$；
- 序列的异或和为序列中所有数异或起来的结果。
- 数据范围：$1\leqslant n\leqslant 10^6,1\leqslant a_i,k\leqslant 10^9$。

## 分析
自己想出了做法，鸡冻。

首先根据异或的性质，求出异或的前缀和，把异或和转化为有多少个数对满足异或起来大于等于$k$（其中数对需要在异或前缀和数组中）。

然后我们对异或前缀和数组建一颗$\text{01trie}$，并求出每个点子树中终止点的个数$size_x$（终止点就是$\text{01trie}$插入时最后一个点），查询的时候按位查询。

具体地，我们对于每一位分类讨论，设第$i$位$x$为$y$，第$i$位$k$为$p$（$y,p\in\{0,1\}$），假如我们前$i$位与$k$都相同：

- 如果$p=1$，那么异或起来必须为$1$，直接跳一个$y\oplus p$；
- 如果$p=0$，那么异或起来可以是$1$可以是$0$，不难发现异或起来为$1$的情况一定全部满足答案，因此我们加上跳到$y\oplus 1$的所有情况$size$，并跳一个$y\oplus p$来循环计算异或起来为$0$的贡献。
```
long long calc(int x,int k){
	int now=root;
	long long res=0;
	for(int i=30;i>=0;i--){
		int y=((x>>i)&1),p=((k>>i)&1);
		if(p==0)
			res+=1ll*size[chd[now][y^1]];
		now=chd[now][y^p];
	}
	res+=size[now];
	return res;
}
```

但是这样并不行，因为我们提前把$\text{01trie}$建出来了，这样会两个异或起来不能成为一个区间的数的贡献加进答案。

可以边修改边查询，把$\text{insert}$直接改成经过的所有点都增加$size$，在每一次查询前插入上一个前缀和，这样我们可以保证查询的所有贡献都是有效的了。

复杂度$O(n\log \max\{k,maxa\})$。

## 代码

记得开$\text{long long}$。
```
#include<stdio.h>
const int maxn=1000005,maxk=30;
int n,k,tot,root;
int a[maxn],sum[maxn],chd[maxn*maxk][2],size[maxn*maxk];
long long ans;
void insert(int x){
	int now=root;
	for(int i=30;i>=0;i--){
		int y=((x>>i)&1);
		if(chd[now][y]==0)
			chd[now][y]=++tot;
		size[now]++,now=chd[now][y];
	}
	size[now]++;
}
long long calc(int x,int k){
	int now=root;
	long long res=0;
	for(int i=30;i>=0;i--){
		int y=((x>>i)&1),p=((k>>i)&1);
		if(p==0)
			res+=1ll*size[chd[now][y^1]];
		now=chd[now][y^p];
	}
	res+=size[now];
	return res;
}
int main(){
	root=tot=1;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum[i]=sum[i-1]^a[i];
	}
	for(int i=1;i<=n;i++){
		insert(sum[i-1]);
		ans+=calc(sum[i],k);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：TLE_Automat (赞：1)

Problem E :

**题意：**

给定一个长度 $n$ 的序列 $a$ 和一个正整数 $k$ ，问有多少个区间 $[l,r]$ 满足 $1\le l\le r\le n$ 且 $\large\operatorname{xor}_{i=l}^r a_i\ge k$ 。

**数据范围：**

$1\le n\le 10^6,1\le k\le 10^9,1\le a_i\le 10^9$ 。

**做法：**

第一眼，好像只会暴力，绞尽脑汁冥思苦想了很久，想用各种数据结构维护，但都没有成功，于是看了一眼题解，发现是 $\text{01Trie}$ 树，艹，原来 $\text{Trie}$ 树还有那么多功能！故写一篇题解以纪念。

看来跟异或有关的的按位考虑的题要多往 $\text{Trie}$ 树等能够维护每一位信息的东西方面考虑。

首先，我们容易想到预处理出异或前缀和 $sum_i$ ，因为相同的数异或起来是 $0$ ，所以一段区间 $[l,r]$ 的异或和就是 $sum_r\oplus sum_{l-1}$ 。

那么我们就只需要求有多少个区间 $[l,r]$ ，满足 $sum_r\oplus sum_{l-1}\ge k$ 即可。

可以考虑枚举右端点 $r$ ，然后计算有多少个 $l$ 符合条件。考虑， 我们现在要维护一个数据结构，要求支持插入一个数字，查询之前插入的数字有多少个异或上这个数字大于等于 $k$ ，并且时间复杂度在 $O(\log_2x)$ 之内做到。

直接考虑不好考虑，可以把他们进行看成二进制的 $0,1$ 字符串，然后枚举每一个 $r$ 统计完答案之后把它建到 $\text{Trie}$ 树中，并统计每个节点子树中叶节点的个数，容易发现，每次插入操作的复杂度是 $O(\log_2n)$ 。

但我们如何查询呢，考虑 $sum_r$ 从低到高的第 $i$ 位 $dig$ ，设 $cur$ 为我们所选的 $\text{Trie}$ 树路径上对应的位与 $sum_r$ 对应位上的异或和，如果之前插入的数字从低到高第 $i$ 位有数字为 $dig\oplus 1$ ，并且 $cur+2^i\ge k$ ，那么就说明在 $dig\oplus 1$ 的子树中的所有数字都满足条件，就可以把这棵子树的 $size$ 加到答案里，并去查找另一棵 $dig$ 的子树。

如果 $cur+2^i<k$，那么说明即使下一位与 $sumr$ 的异或值为 $1$ ,并且我们加上下一位都小于 $k$ ，那么我们一定要去查找 $dig\oplus 1$ 所在的子树，并把 $cur$ 加上 $2^i$ 。

$Source(by\_myself):$

```cpp
#include <bits/stdc++.h>
#define mkp make_pair
#define lowbit(x) ((x)&(-x))

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int MAXN=1e6+10;

int n,k,cnt;
int a[MAXN];
int sum[MAXN],sz[MAXN*20];
int nxt[MAXN*20][2];

inline void insert(int x)
{
    int root=0;
    for(int i=30;i>=0;i--)
    {
        sz[root]++;
        int dig=(x>>i)&1;
        if(nxt[root][dig]==-1) nxt[root][dig]=++cnt;
        root=nxt[root][dig];
    }
    sz[root]++;
}

inline int calc(int x)
{
    int res=0,cur=0;
    int root=0;
    for(int i=30;i>=0;i--)
    {
        if(root==-1) break;

        int dig=(x>>i)&1;
        if(cur+(1<<i)>=k)
        {
            if(nxt[root][dig^1]!=-1) res+=sz[nxt[root][dig^1]];
            root=nxt[root][dig];
        }
        else
        {
            cur+=(1<<i);
            root=nxt[root][dig^1];
        }
    }

    return res;
}

void solve()
{
    memset(nxt,-1,sizeof(nxt));

    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]^a[i];

    ll ans=0; insert(0);
    for(int i=1;i<=n;i++)
    {
        ans+=calc(sum[i]);
        insert(sum[i]);
    }
 
    printf("%lld\n",ans);
}

int main()
{
    solve();
    return 0;
}
```

---

## 作者：BigJoker (赞：0)

01trie

根据异或的性质，我们可以通过前缀异或快速求出 $l\sim r$ 的异或和，假设 $s_i$ 表示前 $i$ 个数中的异或和，那么 $s_r\oplus s_{l-1}$ 就是 $\bigoplus_{i=l}^{r} a_i$

一个常用的思路，固定住一端，通过求符合条件的另一端达到计数的目的。

很自然的想到固定住 $r$，通过求符合条件的 $l$ 的数量，就可以求出答案。

现在讲问题转化为如何快速求符合条件的 $l$ 的数量。

考虑建一棵有关 $s_i$ 的 trie，通过检索字典树来进行快速求解。

由于字典树是 01 的形式呈现，不妨把 $k$ 也拆成二进制的形式，从高位到低位枚举。

思考一个小问题，如何判断一个数大于等于 $k$，如果在高位的二进制中，有一位 $k$ 比这个数小，那么后面的数无论是什么，都是这个数大于 $k$，当然前提是前面的数都要一样。

接着字典树说，我们假设当前已经找到了第 $i$ 位，数 $r$ 二进制的第 $i$ 位为 $c_1$，$k$ 的为 $c_2$，前面的都是相同的。

如果 $c_2=0$，那么如果字典树中存在与 $c_1\oplus 1$ 的节点，那么肯定接下来的全部都会大于 $k$，因此答案加上 $sz_{nxt_{p,c_1\oplus 1}}$，然后检索反方向。

否则的话只能检索 $c_1\oplus 1$。

最后检索完毕时，因为可以大于等于，所以还要加上 $sz_p$。

空间该开多大呢？这也是字典树中一个常见的问题，注意到有 $n\le 10^6$ 个数，每个数至多有 $31$ 位，所以开位数乘上数的个数即可。

---

## 作者：Arghariza (赞：0)

按照套路可以把 $\bigoplus\limits_{i=l}^{r}a_i=s_r\bigoplus s_{l-1}$，$s_i=\bigoplus\limits_{k=1}^{i}a_k$。

然后可以枚举 $r$，在 $r$ 这一位的贡献就是 $1$ 到 $r$ 内 $s_{l-1}\bigoplus s_r\ge k$ 的数的个数。

然后这东西可以用 `01-trie` 做。

记录每个点的子树内的数的个数，然后从高位向低位考虑贡献即可。

```cpp
#include <bits/stdc++.h>
#define ll long long
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(ll x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 1e6 + 100;
struct trie { int ch[2], sz; } tr[maxn << 5];
int n, k, tot;

void insert(int c) {
	int u = 0;
	for (int i = 30; ~i; i--) {
		int v = (c >> i) & 1;
		if (!tr[u].ch[v]) tr[u].ch[v] = ++tot;
		u = tr[u].ch[v], tr[u].sz++;
	}
}

int query(int c) {
	int u = 0, ans = 0;
	for (int i = 30; ~i; i--) {
		int v = (c >> i) & 1;
		if ((k >> i) & 1) {
			u = tr[u].ch[v ^ 1];
		} else {
			ans += tr[tr[u].ch[v ^ 1]].sz;
			u = tr[u].ch[v];
		}
		if (u == 0) break;
	}
	return ans + tr[u].sz;
}

signed main() {
	n = read(), k = read();
	insert(0);
	ll res = 0;
	for (int i = 1, s = 0; i <= n; i++) {
		res += 1ll * query(s ^= read());
//		cout << res << endl;
		insert(s);
	}
	write(res);
	return 0;
}

```

---

