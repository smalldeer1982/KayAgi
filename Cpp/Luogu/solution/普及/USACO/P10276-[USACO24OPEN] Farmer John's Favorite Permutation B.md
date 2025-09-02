# [USACO24OPEN] Farmer John's Favorite Permutation B

## 题目描述

Farmer John 有一个长为 $N$（$2\le N\le 10^5$）的排列 $p$，包含从 $1$ 到 $N$ 的每个正整数恰好一次。然而，Farmer Nhoj 闯入了 FJ 的牛棚并拆散了 $p$。为了不至于太过残忍，FN 写了一些能够帮助 FJ 重建 $p$ 的提示。当 $p$ 中剩余多于一个元素时，FN 会执行以下操作：

令 $p$ 的剩余元素为 $p_1^\prime,p_2^\prime,\ldots,p_n^\prime$，

- 如果 $p_1^\prime>p_n^\prime$，他写下 $p_2^\prime$ 并从排列中删除 $p_1^\prime$。
- 否则，他写下 $p_{n−1}^\prime$ 并从排列中删除 $p_n^\prime$。

最终，Farmer Nhoj 将按顺序写下 $N−1$ 个整数 $h_1,h_2,\ldots,h_{N−1}$。给定 $h$，Farmer John 希望得到你的帮助重建与 Farmer Nhoj 的提示相一致的最小字典序 $p$，或者判断 Farmer Nhoj 一定犯了错误。我们知道，给定两个排列 $p$ 和 $p^\prime$，如果在第一个两者不同的位置 $i$ 处有 $p_i<p_i^\prime$，则 $p$ 的字典序小于 $p^\prime$。

## 说明/提示

对于第四个测试用例，如果 $p=[3,1,2,4]$ 则 FN 将写下 $h=[2,1,1]$。

```plain
p' = [3,1,2,4]
p_1' < p_n' -> h_1 = 2
p' = [3,1,2]
p_1' > p_n' -> h_2 = 1
p' = [1,2]
p_1' < p_n' -> h_3 = 1
p' = [1]
```

注意排列 $p=[4,2,1,3]$ 也会产生同样的 $h$，但 $[3,1,2,4]$ 字典序更小。

对于第二个测试用例，不存在与 $h$ 相一致的 $p$；$p=[1,2]$ 和 $p=[2,1]$ 均会产生 $h=[1]$，并非 $h=[2]$。

### 测试点性质

- 测试点 $2$：$N\le 8$。
- 测试点 $3-6$：$N\le 100$。
- 测试点 $7-11$：没有额外限制。

## 样例 #1

### 输入

```
5
2
1
2
2
4
1 1 1
4
2 1 1
4
3 2 1```

### 输出

```
1 2
-1
-1
3 1 2 4
1 2 3 4```

# 题解

## 作者：cff_0102 (赞：8)

每次去掉两个中更大的一个数，最后必然剩下 $1$，所以 $h_{n-1}$ 必须为 $1$，否则无解。

$1$ 最多只会被输出两次，即左边删掉的一次和右边删掉的一次。如果有超过两次则也无解。

其它数最多只会被输出一次，因为另一边有一个 $1$ 挡着呢。如果一个非 $1$ 的数被输出两次，则也无解。

无解的情况分析完了，那么怎么构造呢？

注意到刚开始在最两边的数（如果不是 $1$）不会被输出。可以把不出现的的两个数（或者一个数，如果 $1$ 只出现了一次）挑出来，先放到数列的两端。要求字典序最小的方案，则将更小的那个安排在前面。如果只有一个数没被输出，说明 $1$ 在数列的最前面。

接下来按 $h$ 数组顺序安排元素就行。每次判断当前的左右两个数谁更大，再把 $h$ 的新元素放到那边。

```cpp
#include<bits/stdc++.h>
using namespace std;
int h[100005];
int v[100005];
int a[100005];
bool in[100005];
void mian(){
	memset(v,0,sizeof v);
	memset(in,0,sizeof in);memset(a,0,sizeof a);memset(h,0,sizeof h);
	int n;cin>>n;
	for(int i=1;i<=n-1;i++){
		cin>>h[i];
		v[h[i]]++;
	}
	if(h[n-1]!=1){
		cout<<-1<<endl;return;
	}
	int x1=0,x2=0;
	for(int i=1;i<=n;i++){
		if(v[i]==0){
			if(x1)x2=i;
			else x1=i;
		}if(v[i]>1&&i>1||v[i]>2){
			cout<<-1<<endl;return;
		}
	}
	if(x1>x2)swap(x1,x2);
	if(x1==0)x1=1;
	int l=1,r=n;
	a[l]=x1;a[r]=x2;
	in[x1]=in[x2]=1;
	int nw=1;
	for(int i=3;i<=n;i++){//这里的 i 是目前填第几个数 
		if(a[l]>a[r]){
			while(in[h[nw]])nw++;
			a[++l]=h[nw];
			in[h[nw]]=1;
		}else{
			while(in[h[nw]])nw++;
			a[--r]=h[nw];
			in[h[nw]]=1;
		}
	}
	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int t;cin>>t;
	while(t--)mian(); 
	return 0;
}
```

---

## 作者：complete_binary_tree (赞：4)

**Update 2024/8/3：修复了一处问题。（感谢 @[Problem1613end](https://www.luogu.com.cn/user/1281623) 提出的错误）**

---

~~什么东西？Farmer Nhoj？！绷不住了~~

首先，~~手推可得~~如果有解，必定满足以下条件：

- $\text{Farmer Nhoj}$ 的序列中每个数至多出现一次（$1$ 至多出现两次）。

- $\text{Farmer Nhoj}$ 的序列中最后一个数必定是 $1$。

然后思考怎么构造：

- 序列中只在最后出现一个 $1$：

那么原排列的头肯定是 $1$（因为字典序最小）。

此时由于第一次删除的数不会留在序列中，所以最后一个数肯定是那个没留在序列中的数。

剩下的，按序列的顺序倒推即可。

如：

```
6 2 4 3 1
solve:
1 _ _ _ _ 5（5 没出现过）
1 _ _ _ 6 5（那第一次删掉的肯定是 5，所以 6 放里面）
1 _ _ 2 6 5（第二次删除的肯定是 6，所以 2 放里面）
……
1 3 4 2 6 5（直到最后）
```

- 序列中有 $2$ 个 $1$：

这样 $1$ 两边都有元素，所以 $1$ 才会被记录两次。

首先序列中没出现的元素一定在首尾，而且因为字典序最小，所以较小的那个肯定放前面，较大的肯定放后面。

然后剩下的按照 $\text{Farmer Nhoj}$ 删除的顺序双指针一步步模拟即可。

如：

```
5 4 7 2 1 3 1
solve:
6 _ _ _ _ _ _ 8（6 和 8 没出现过）
^             ^（指针）

（8 比 6 大，所以 Farmer Nhoj 肯定先删除 8，留下的 5 就是 8 前一个数，右指针向左移动一位）
6 _ _ _ _ _ 5 8
^           ^  （指针）

（6 比 5 大，所以 Farmer Nhoj 肯定先删除 6，留下的 4 就是 6 后一个数，左指针向右移动一位）
6 4 _ _ _ _ 5 8
  ^         ^  （指针）

（5 比 4 大，右指针左移）
6 4 _ _ _ 7 5 8
  ^       ^    （指针）
  
（……）
最终就是：
6 4 1 3 2 7 5 8（指针在 1 处重合）
```

时间复杂度 $O(n)$，代码也很好写。

最逆天的是，**USACO 不允许行末多余空格**（因为我多了行末空格，提交的时候样例都没有过去）。

开了个快读就到 $295\text{ms}$ 了。喜提你谷最优解（？）

[记录](https://www.luogu.com.cn/record/152613173)

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int a[N], f[N], t, cnt1, cnt2, bowl[N];
int n;

int main(){
	scanf("%d", &t);
	while(t--){
		memset(bowl, 0, sizeof bowl);
		scanf("%d", &n);
		for(int i = 1; i < n; ++i) scanf("%d", &a[i]), bowl[a[i]]++;
		if(a[n - 1] != 1 || bowl[1] > 2){
			puts("-1");
			continue;
		}
		int can = 1;
		for(int i = 2; i <= n; ++i) if(bowl[i] >= 2) can = 0;
		if(!can){
			puts("-1");
			continue;
		}
		cnt1 = 1, cnt2 = n;
		if(bowl[1] == 1){
			f[cnt1] = 1;
			for(int i = 1; i <= n; ++i) if(bowl[i] == 0) f[cnt2] = i;
		}
		else{
			int i = 1;
			for(; i <= n; ++i) if(bowl[i] == 0){
				f[cnt1] = i;
				break;
			}
			++i;
			for(; i <= n; ++i) if(bowl[i] == 0){
				f[cnt2] = i;
				break;
			}
		}
		for(int i = 1; i < n - 1; ++i){
			if(f[cnt1] > f[cnt2]) cnt1++, f[cnt1] = a[i];
			else cnt2--, f[cnt2] = a[i];
		}
		for(int i = 1; i <= n; ++i){printf("%d", f[i]);if(i != n) printf(" ");}
		puts("");
	}
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：4)

需要我来讲一下铜组该怎么通过吗？

首先最后剩下的数字一定是 $1$，考虑一个不是 $1$ 的数，如果不在最外面，那么在删除它之前会先删除它左右的一个，此时它会在序列 $h$ 中出现。

考虑 $h$ 中没有出现的数字，如果超过 $2$，显然无解，如果等于 $1$，那么 $1$ 一定在最外面，因为 $1$ 不会被删除，所以即使出现了 $1$，也可能在最外面。

于是我们知道了最外面的两个数，它们的顺序对合法性没有影响，于是我们需要让小的在前面来最小化字典序。

然后直接模拟删除过程即可，因为每次删除之后最外面的数字都是知道的，时空复杂度 $O(n)$，注意特判最后的序列并不是排列的情况：
```cpp
int T,n,K,m,a[N],b[N],c[N];
bitset<N>vs;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z,v1,v2;
    for(cin>>T;T--;){
        for(i=1,cin>>n;i<n;++i)cin>>c[i];
        if(c[n-1]!=1){puts("-1");continue;}
        for(k=1,m=0;k<=n;++k)vs[k]=0;
        for(i=1;i<n;++i)vs[c[i]]=1;
        for(k=1;k<=n;++k)if(!vs[k])b[++m]=k;
        if(m==1)b[++m]=1;
        if(m!=2){puts("-1");continue;}
        a[l=1]=b[1],a[r=n]=b[2],k=1;
        while(l<r-1){
            if(a[l]<a[r])a[--r]=c[k];
            else a[++l]=c[k];++k;
        }
        for(i=1;i<=n;++i)vs[i]=0;
        for(i=1;i<=n;++i)vs[a[i]]=1;
        for(k=1;k<=n;++k)
            if(!vs[k]){puts("-1");goto lc1;}
        if(a[1]>a[n])reverse(a+1,a+n+1);
        for(i=1;i<=n;++i)printf("%d%c",a[i]," \n"[i==n]);
        lc1:;
    }
    return 0;
}
```

---

## 作者：haozige (赞：3)

# P10276 Farmer John's Favorite Permutation

[题目传送门](https://www.luogu.com.cn/problem/P10276)

## 题意概括

给你 $N$ 个样例，对于每个样例，给你一个数组，定义一种操作，对于一个数组，每次去掉最左边或最右边更大的数，然后记录下这个数旁边的数，直到只剩一个数为止，问你有没有可能有一个数组经过这个操作能得到输入的数组，如果可能，输出这个操作后的数组，如果不可能，输出 $-1$。

## 思路

这是一道找规律题，要自己打一下表，这里直接给出结论；首先如果是可能的，输入的数组一定要有以下性质：

1. 数字 $1$ 出现了 $1$ 次或者 $2$ 次（不可能只出现 $0$ 次，因为最后一个肯定是 $1$）。

2. 出现的数字 $1$ 一定有 $1$ 个在最后面（因为是最小的，最后一定会出现）。

3. 其他数字出现不超过 $1$ 次（有概率不出现，像一些边界情况）。

只要判断之后若不满足直接输出就好，满足我们再进行下一步，把操作前的数组再处理一遍，然后要分情况讨论。

第一种是只有 $1$ 个 $1$ 的情况，这种情况说明 $1$ 一定在边界，直接倒过来，再把没出现的数放在最后就好（因为没出现意味着它在另一个边界，开始就被删除了）。

第二种就是有 $2$ 个 $1$ 的情况，因为这样有 $2$ 个不存在题目给的数组里面，所以我们就把他们小的放在最前面，大的放在最后面（思考一下，只有边界条件才会不存在，至于为什么小的在前，是因为题目要求字典序），然后就模拟把每个数放回去的过程就好了（把他们都放在较大的数旁边）。

最后模拟以上的过程就能做出此题。

## 代码

这是最后的代码，时间复杂度 $O(TN)$：

~~这里不得不批评一下逆天的 USACO，行末有多余空格不让过，比赛的时候我一脸懵逼看着它说我的样例没过，查了半天才发现是空格。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,h[100005],bkt[100005],ans[100005],k=0;
void slove(){
	cin>>n;
	memset(bkt,0,sizeof(bkt));
	memset(ans,0,sizeof(ans));
	for(int i=1;i<=n-1;i++){
		cin>>h[i];
		bkt[h[i]]++;
	}
	if(bkt[1]==0||bkt[1]>=3){
		cout<<-1;
		if(k!=1) cout<<endl;
		return;
	}if(h[n-1]!=1){
		cout<<-1;
		if(k!=1) cout<<endl;
		return;
	}for(int i=2;i<=n;i++){
		if(bkt[i]>=2){
			cout<<-1;
			if(k!=1) cout<<endl;
			return;
		}
	}if(bkt[1]==1){
		int r;
		for(int i=1;i<=n;i++){
			if(bkt[i]==0){
				r=i;
				break;
			}
		}
		for(int i=n-1;i>=1;i--) cout<<h[i]<<" ";
		cout<<r;
		if(k!=1) cout<<endl;
		return;
	}
	for(int i=1;i<=n;i++){
		if(bkt[i]==0){
			if(ans[1]==0) ans[1]=i;
			else ans[n]=i;
		}
	}
	int l=1,r=n,i=1;
	while(i<n-1){
		if(ans[l]>ans[r]){
			l++;
			ans[l]=h[i];
		}else{
			r--;
			ans[r]=h[i];
		}i++;
	}
	for(int i=1;i<=n-1;i++) cout<<ans[i]<<" ";
	cout<<ans[n];
	if(k!=1) cout<<endl;
}
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		if(i==t) k=1;
		slove();
	}
    return 0;
}
```

---

## 作者：No_Rest (赞：2)

## 思路

神仙找规律题。

经过一定尝试后，可以发现，$h_{n-1} = 1$（因为没有数比 $1$ 小，所以 $1$ 必然会一直保留，直至剩下两个数时，容易想到一定会把另一个数删掉，写下 $1$），且 Farmer Nhoj 给出的 $h$ 可以分为以下两种情况：

- 在 $h$ 的末尾有一个 $1$，其他位置均不为 $1$；

- 共有两个 $1$，一个在 $h$ 的末尾，另一个在其他位置。

又因为当一个数被写上后，一定处于 $p$ 的边缘，如果不是 $1$，则不会再被写下。所以如果 $h$ 不是以上两种情况，即任何一个大于 $1$ 的数出现了不止一次，或 $1$ 出现了不止两次，那么这个 $h$ 一定是非法的。

接下来讨论第一种情况：在 $h$ 的末尾有一个 $1$，其他位置均不为 $1$。在这种情况下，$1$ 必然在边缘，因为若 $1$ 在中间，必然会在最后一次出现前再出现一次。于是为了使 $p$ 字典序最小，我们把 $h_{n-1} = 1$ 排在 $p_1$ 的位置上。

剩余数的位置不难确定了，不难想到，$h$ 是如下顺序写下的：$p_n > p_1 = 1$，所以写下 $p_{n - 1}$，删去 $p_n$；$p_{n - 1} > p_1 = 1$，所以写下 $p_{n - 2}$，删去 $p_{n - 1}$；$p_{n - 2} > p_1 = 1$，所以写下 $p_{n - 3}$，删去 $p_{n - 2}\dots$

于是，$h_{1} = p_{n - 1}, h_2 = p_{n - 2}, \dots , h_i = p_{n - i}, \dots , h_{n - 1} = p_1=1$。那么 $h$ 中唯一没有出现的数就等于 $p_n$ 了。这样，第一种情况的答案就呼之欲出了。

当共有两个 $1$，一个在 $h$ 的末尾，另一个在其他位置时，易知 $h$ 中有两个数没有出现，这两个数即为 $p_1$ 和 $p_n$。为了使字典序最小，可以让 $p_1$ 等于较小的没有出现的数，$p_n$ 等于较大的没有出现的数。

因为 $p_n > p_1$，所以最开始一定是写下了 $p_{n - 1}$ 并删去 $p_n$，于是 $p_{n - 1} = h_1$。接下来我们还可以比较 $p_1$ 与 $p_{n - 1}$ 的大小，确定 $h_2$ 等于 $p_2$ 还是 $p_{n - 2}$，以此类推。那么，我们就可以通过 $h$ 倒推出原来的 $p$ 了。

时间复杂度 $\mathcal O(Tn)$。

## 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
const ll maxn = 2e5 + 5;
ll read(){
    ll r = 0, f = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9') f |= ch == '-', ch = getchar();
    while(ch >= '0' && ch <= '9') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
    return f ? -r : r;
}
ll t = read(), n, h[maxn], p[maxn], p1, p2, cnt[maxn], x, y;
void solve(){
	memset(cnt, 0, sizeof(cnt));//多测不清空，亲人两行泪
	n = read(), x = y = 0;
	for(ll i = 1; i < n; ++i) h[i] = read(), cnt[h[i]]++;
	for(ll i = 1; i <= n; ++i)
		if((i == 1 && (cnt[i] > 2 || !cnt[i])) || (i > 1 && cnt[i] > 1)){//如果 1 的个数不为 1，2 或其他数的个数比大于 1 个，那么 h 是非法的
			puts("-1");
			return;
		} else if(!cnt[i] && !x) x = i;//寻找没在 h 里出现的数
		else if(!cnt[i]) y = i;
	if(h[n - 1] != 1){//如果 h 的最后一个数不是 1，那么 h 也是非法的
		puts("-1");
		return;
	}
	if(cnt[1] == 1){//第一种情况，在 h 的末尾有一个 1，其他位置均不为 1
		for(ll i = n - 1; i; --i) printf("%lld ", h[i]);//p[i] = h[n - i]，这里可以直接倒序输出
		printf("%lld\n", x);//p[n] 等于没出现的数
	} else {//第二种情况，除了在 h 的末尾有一个 1，在其他位置还有一个 1
		p1 = 1, p2 = n, p[1] = min(x, y), p[n] = max(x, y);
		for(ll i = 1; i < n - 1; ++i)//直接进行模拟
			if(p[p1] < p[p2]) p[--p2] = h[i];
			else p[++p1] = h[i];
		for(ll i = 1; i <= n; ++i) printf("%lld ", p[i]);//输出
		putchar('\n');
	}
}
int main(){
	for(; t; --t) solve();
    return 0;
}
```

---

## 作者：Problem1613end (赞：1)

这道题有三种情况。

第一种 $-1$。

由题目可知，$1$ 不会被删除，所以 $1$ 一定回留到最后两个，而此时定会写上 $1$，所以 $h$ 数组最后一个必须是 $1$。

而每个数被左边或右边影响才会写上，写上后左边或右边又会被删去，所以一个数最多写上两个，然而由于删去左边或右边后，该数会成为边界，必须最小才能写上两个，即 $1$ 最多两个，其余最多一个。

由于总数是 $n$ 个，基于前两条推论以及鸽巢原理，可推得个数为 $0$ 的最多两种数，再详细点，即个数为 $0$ 的数字种数与 $1$ 的个数相等。

第二种 $1$ 的个数为一个。

此时定然要最后一个为 $1$（参前文）。

为了让 $1$ 只有一个，即令 $1$ 只有一个相邻数，则 $1$ 只能在 $a$ 数组边界上，而另一个边界则会没有写出，即个数为 $0$ 的那种数，便可模拟推得剩余部分为 $h$ 数组从第 $n-2$ 项到第 $1$ 项。
```
for(int j=2;j<=n;j++){
	if(tt[j]==0){
		pd=j;
		break;
	}
}
cout<<1<<" ";
for(int j=n-2;j>=1;j--) cout<<h[j]<<" ";
cout<<pd<<endl;
```

第三种 $1$ 的个数为两个。

与第二种类似，可推得 $1$ 在非边界之处，两个边界都不会被写出，即个数为 $0$ 的两种数，用双指针模拟。
```
pd=0;
pd2=0;
for(int j=2;j<=n;j++){
	if(tt[j]==0){
		if(pd==0)  pd=j;
		else  if(pd2==0)  pd2=j;
		else  break;
	}
}
a[1]=min(pd,pd2);
a[n]=max(pd,pd2);
l=1;
r=n;
for(int j=1;j<=n-2;j++){
    if(a[l]>a[r]){
		l++;
		a[l]=h[j];
	}
	else{
		r--;
		a[r]=h[j];
		}
	}
}
```

下面是完整代码，欢迎 HACK。
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll t,a[100100],h[100100],tt[100100],l,r,k,n,pd=0,pd2;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		memset(a,0,sizeof(a));
		memset(h,0,sizeof(h));
		memset(tt,0,sizeof(tt));
		cin>>n;
		for(int j=1;j<=n-1;j++){
			cin>>h[j];
			tt[h[j]]++;
		}
		if(h[n-1]!=1)  cout<<-1<<endl;
		else{
			pd=0;
			for(int j=2;j<=n;j++){
				if(tt[j]>=2){
					pd=1;
					break;
				}
			}
			if(pd!=0)  cout<<-1<<endl;
			else  if(tt[1]>=3)  cout<<-1<<endl;
			else{
				if(tt[1]==1){
					for(int j=2;j<=n;j++){
						if(tt[j]==0){
							pd=j;
							break;
						}
					}
					cout<<1<<" ";
					for(int j=n-2;j>=1;j--) cout<<h[j]<<" ";
					cout<<pd<<endl;
				}
				else{
					pd=0;
					pd2=0;
					for(int j=2;j<=n;j++){
						if(tt[j]==0){
							if(pd==0)  pd=j;
							else  if(pd2==0)  pd2=j;
							else  break;
						}
					}
					a[1]=min(pd,pd2);
					a[n]=max(pd,pd2);
					l=1;
					r=n;
					for(int j=1;j<=n-2;j++){
						if(a[l]>a[r]){
							l++;
							a[l]=h[j];
						}
						else{
							r--;
							a[r]=h[j];
						}
					}
					for(int j=1;j<=n;j++){
						cout<<a[j];
						if(j==n)  cout<<endl;
						else  cout<<" ";
					}
				}
			}
		}
	}
	return 0;
}

---

## 作者：huanglihuan (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P10276)

### 思路

对于测试点2，我们可以暴力枚举 $n$ 个数的全排列，时间复杂度 $O (T n!)$，仅适用于 $n \le 8$ 的测试点2。

对于测试点3 ~ 11，我们先思考在什么样的情况下无解，经过计算得到在序列 $h$ 中必定只有1 ~ 2 个 1，且其他数字均只出现最多1次，否则答案为无解。

接下来分类讨论：

- 如果只有一个1，把原数列倒过来，再填充数就可以了。

- 否则，我们按照字典序最小的要求去模拟放的过程就可以了。

具体见代码。

时间复杂度 $O (T n)$，适用于所有数据。

[代码](https://www.luogu.com.cn/paste/p5qiatiq)

---

## 作者：wdsjl (赞：1)

## 发现规律
这题要做出来的重点就是要发现最重要的 $1$ 的出现规律，因为 $1$ 是序列中最小的数，所以**一定不会被删除**所以在只剩两个数的时候， $1$ 一定会被留下，所以输入最后一位是 $1$ 了,再考虑在输入中出现过一次就证明这个数在下一轮**一定是序列的端点**而除了 $1$ 其他数成为端点后都会被删去，既**除了 $1$ 的所有数都只会出现一次**。

得出如下不合法的情况：

- 最后一位不是 $1$。
- 有除了 $1$ 的数出现了两次。
- $1$ 没有出现或出现次数大于两次。

## 考虑构造
因为我们已经说过成为端点后都会被删去，所以：

- $1$ 出现两次时没有在输入中出现过的数既是第一次的端点。
- $1$ 出现一次，既 $1$ 和没有出现过的一个数为第一次的端点。

为了字典序最小我们将小的那个放在前边。

之后两个端点的大小确定我们即可按顺序往序列里填数。

各种情况的特判我已经在代码中备注。


```cpp
scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		init();
		for(int i=1;i<n;i++){
			scanf("%d",&a[i]);
			v[a[i]]++; 
		}
		int flag=0;
		for(int i=2;i<=n;i++){
			if(v[i]>1)flag=1;
		}
		if(a[n-1]!=1){//结尾不是1 
			printf("-1\n");
		}else if(v[1]==0){//1没出现过 
			printf("-1\n");
		}else if(v[1]>2){//1次数大于两次 
			printf("-1\n");
		}else if(flag){//2-n出现超过一次 
			printf("-1\n");
		}else if(v[1]==1){//分讨 
			p[1]=1;
			int op;
			for(int j=1;j<=n;j++){
				if(v[j]==0)op=j;
			}
			p[n]=op;
			int l=2,r=n-1,idx=1;
			while(l<r){
				if(p[l-1]>p[r+1]){
					p[l++]=a[idx];
				}else{
					p[r--]=a[idx];
				}
				idx++;
			}
			if(!p[l])p[l]=a[idx];
			for(int i=1;i<=n;i++){
				printf("%d ",p[i]);
			}
			printf("\n");
		}else if(v[1]==2){
			int boo=1;
			for(int j=1;j<=n;j++){
				if(v[j]==0&&boo){
					p[1]=j;
					boo=0; 
				}else if(v[j]==0){
					p[n]=j;
				}
			}
			if(p[1]>p[n])swap(p[1],p[n]);
			int l=2,r=n-1,idx=1;
			while(l<r){
				if(p[l-1]>p[r+1]){
					p[l++]=a[idx];
				}else{
					p[r--]=a[idx];
				}
				idx++;
			}
			p[l]=a[idx];
			for(int i=1;i<=n;i++){
				printf("%d ",p[i]);
			}
			printf("\n");
		}
	}
```

---

