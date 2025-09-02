# 「PFLOI R1」PFL 变换

## 题目背景

五大高手云集于此，思想的火花激烈碰撞。很快，PFLOI Round 1 准备完毕。

开始了……

## 题目描述

新的征途已经开始：智力踏上了寻香蕉之旅。道路上共有 $n$ 个香蕉，编号从 $1$ 到 $n$。

智力看到如此美食，非常激动。但是智力不想吃得太饱或太少，所以它会吃**刚好** $m$ 个香蕉。

智力是一个挑剔的人，只有当它吃的 $m$ 个香蕉的编号的异或和**恰好为** $2^{\lfloor\log_2 n\rfloor+1}-1$ 时他才会满意。请你帮忙找出他应该吃哪些香蕉，好让他满意。

如果怎样都不能满足智力的需求，就请输出 `-1` 吧。

------------

**形式化题面**：

请你从 $1$ 到 $n$ 中选出 $m$ 个数，使得它们的异或和恰好为 $2^{\lfloor\log_2 n\rfloor+1}-1$。若无解输出 `-1`。

## 说明/提示

**本题不采用捆绑测试**。

| 测试点编号 | 特殊性质 | 分值 |
| :----------: | :----------: | :-----:| 
| $1,2$ | $n\le15$ | $2\times4=8$ |
| $3\sim11 $ | $n\le128$ | $9\times3=27$ |
| $12\sim24 $ | $\sum n\le10^5$ | $13\times3=39$ |
| $25\sim29$ | 无特殊限制 | $5\times4=20$ |
| $30$ | 无特殊限制 | $1\times6=6$ |

对于所有数据，$1\le m\le n\le10^6$，$1\le\sum n,T\le10^6$。

## 样例 #1

### 输入

```
7
5 2
6 6
7 6
8 3
9 3
10 1
7 4```

### 输出

```
3 4
1 6 2 4 3 5 
1 2 3 4 5 6
8 6 1
8 1 6
-1
3 5 6 7```

# 题解

## 作者：yydtq (赞：24)

### 前言
我认为有紫，难度较高且细节较多。

感觉确定性做法很难，但因为我想冲无伤 AK 就一直在推确定性（结果因为 C 卡评测机波动没了）。

但我最后为了避免推导选择了打表。

所以是不带证明的确定性。

但我依旧认为难度和喵了个喵有得一拼。

当然这道题出的是真的好，给出题人点赞！

### 打表

首先这个表是必须要打的，标算也对 $n\le3$ 进行了特判，而手动特判很明显比小范围特判更容易出错。

设 $f_{x,k}$ 表示 $x$ 个数字凑出 $k$ 所需要的 $n$ 的最小值，枚举最后一个数可以做到 $O(n^3)$ 转移。

```cpp
memset(f,0x3f,sizeof(f));
f[0][0]=0;
for(x=1;x<128;++x)
    for(y=0;y<128;++y)
       for(k=1;k<128;++k)
            if(f[x-1][y^k]<k){
                f[x][y]=k;break;
            }
for(x=1;x<128;++x)
   for(y=1;y<128;y=(y<<1)+1)
      printf("%d%c",f[x][y]," \n"[y==128-1]);
```

考虑当 $n\le127$ 时如何暴力求答案，显然是 $f_{m,t}\le n$ 时有解，其中 $t=2^{\lfloor\log_2n\rfloor+1}-1$。

发现 $f_{m,15}$ 的表是这样的：
```
15,8,8,8,8,8,8,10,10,12,12,15,15,14
```

### 解决问题

这个规律已经很明显了，我们将 $n$ 赋值为 $f_{m,t}$（只有 $f_{m,t}\le n$ 时有解） 之后，若 $m=1$，则直接输出 $t$，若 $n=\dfrac t2$，则 $\dfrac t2$ 必选，然后化归到了 $(\dfrac t2,\dfrac t2,m-1)$ 的问题。

剩余的情况，都有 $m\ge n-2$，我们可以枚举一个不选的数字，求出另一个数字，看是否合法。

代码：
```cpp
int sol(int n,int m){
    if(m<0||m>n)return 0;
    int i,t=(1<<__lg(n)+1)-1;
    if(t<=31){
        if(f[m][t]>n)return 1;
        for(i=m;i;t^=f[i--][t])
            printf("%d ",f[i][t]);
        return 0;
    }if(m==1){
        if(n==t){
            printf("%d ",n);return 0;
        }return 1;
    }if(m<=(t>>1)){
        if(sol(t>>1,m-1))return 1;
        printf("%d ",t+1>>1);
        return 0;
    }if(m==t)return 1;
    if(m==t-1){
        if(n<t-1)return 1;
        for(i=1;i<=m;++i)printf("%d ",i);
        return 0;
    }if(m==t-2){
        if(n<t)return 1;
        for(i=2;i<=t;++i)
            if(i!=t-1)printf("%d ",i);
        return 0;
    }if(m==t-3){
        if(n<t)return 1;
        for(i=3;i<=t;++i)
            if(i!=t-3)printf("%d ",i);
        return 0;
    }
    int lm=(m+2>>1)<<1;
    if(n<lm)return 1;
    n=lm;
    if(m==n-1){
        int i,k=t;
        for(i=1;i<=n;++i)k^=i;
        if(k<1||k>n)return 1;
        for(i=1;i<=n;++i)if(i!=k)printf("%d ",i);
        return 0;
    }
    if(m==n-2){
        int i,x,y,k=t;
        for(i=1;i<=n;++i)k^=i;
        if(!k)return 1;
        for(i=1;i<=n;++i)
            if((i^k)>=1&&(i^k)<=n)
                {x=i,y=i^k;break;}
        for(i=1;i<=n;++i)
            if(i!=x&&i!=y)printf("%d ",i);
        return 0;
    }
}
```
应当说这能一遍过真的是奇迹！

### 后记

看来我构造题是真的做得不够多，要是打 CF 也用两个小时就完了。

看来许多 `Ad-hoc` 的题目都可以通过小范围规律、打表、随机化来解决，这似乎也算是一种通解。

---

## 作者：ddxrS_loves_zxr (赞：20)

## 8pts

用 $O(2^n)$ 的暴力枚举每个数选还是不选，并在选出 $m$ 个数时判断其是否满足条件。

## 35pts

考虑一个 $dp_{i,j,k}$ 表示从 $1$ 到 $i$ 中选出了 $j$ 个数，其异或和为 $k$ 是否可行，再用一个 $pre_{i,j,k}$ 来存方案，时间复杂度 $O(n^3)$。 

## 100pts

记 $p=\lfloor \log{n}\rfloor$。我们先只考虑 $m\ge2^p$ 的情况，有以下构造方式：

先选取 $1$ 到 $2^p-1$ 共 $2^p-1$ 个数，接着在从 $2^p$ 到 $n$ 中选取奇数个数，这样我们就可以得到一个二进制最高位上全部是 $1$ 的数，记作 $r$。可以发现，当 $m$ 为奇数时，我们可以从 $1$ 到 $2^p-1$ 选出一个数并将它删去使 $r$ 满足条件；当 $m$ 为偶数时，我们则可以从 $1$ 到 $2^p-1$ 选出两个数使 $r$ 满足条件。但是，当 $r$ 等于 $2^{p+1}-1$ 时，我们是无法满足条件的，但是，当 $m$ 为偶数时：我们可以选择 $1$ 到 $n-4$ 以满足条件；当 $m$ 为奇数时：我们可以选择 $1$ 到 $2^p-1$ 和 $2^p+2$ 到 $n$ 以满足条件。

同时，我们能发现一个问题：我们构造的方案只能够满足 $m\ge2^p$ 的方案。

所以接下来考虑如何构造 $m<2^p$ 的方案：

1. 当 $p=0$ 或 $1$ 即 $n$ 为 $1,2,3$ 时构造显然。

2. 当 $n>3$ 时，我们假设当 $n$ 为 $1$ 到 $2^{p}-1$ 时都能够被成功构造，则我们可以先选出 $2^{p}-1$ 和 $2^{p}$ 共两个数使他们的异或和为 $2^{p+1}-1$，然后，$2^{p}-1$ 又能被变成 $1$ 到 $2^{p}-2$ 中的 $2$ 到 $2^{p-1}-1$ 个数的异或和，所以，我们一共可以用 $2$ 到 $2^{p-1}$ 个数来构造；此外我们则可以先选出 $1$ 到 $2^{p}-2$ 和 $2^{p}$ 共 $2^{p}-1$ 个数来构造，同时，我们也留下了一个 $2^{p}-1$。当 $n$ 为 $1$ 到 $2^{p}-1$ 都能够被成功构造时，我们总可以选出 $2$ 到 $2^{p-1}-1$ 个数在 $1$ 到 $2^{p}-2$ 以满足它们的异或和等于 $2^{p}-1$，此处，我们就可以删去 $2$ 到 $2^{p-1}-1$ 个数再加上一个数以使得 $m$ 的个数减去 $1$ 到 $2^{p-1}-2$。我们又能发现这时 $m$ 最小为 $(2^{p}-1)-(2^{p-1}-2)=2^{p}-2^{p-1}+1=2^{p-1}+1$。满足条件。

接下来考虑几种无解的情况：

- 当 $n$ 为 $2^p-2$ 且 $m=n-1$ 或 $n-2$ 时无解。

- 其他情况下，当 $n$ 为 $2^p-1$ 且 $m=n$ 时无解。

- 其他情况下，当 $n$ 为奇数且 $m=n$ 或 $m=n-1$ 时无解。

- 其他情况下，当 $n$ 为偶数且 $m=n$ 时无解。

- 其他情况下，当 $n$ 不为 $2^p-1$ 且 $m=1$ 时无解。

时间复杂度 $O(m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, pos, flg;
int LOG[1000005];
struct node {
	vector<int> pre;
};
inline node solve(int n, int m) {
    if(m == 0) {
		node t;
		return t;
	}
	if(m == 1) {
		node t; 
		t.pre.push_back((1 << LOG[n] + 1) - 1);
		return t;
	} 
	if(m <= (1 << LOG[n] - 1)) {
		node t = solve((1 << LOG[n]) - 1, m - 1);        
		t.pre.push_back(1 << LOG[n]);
		return t;
	} else {
        if((1 << LOG[n]) - 1 == m) {
            node t;
            for(int i = 1; i <= (1 << LOG[n]) - 2; i++) t.pre.push_back(i);
            t.pre.push_back(1 << LOG[n]);
            return t;
        }
		node t = solve((1 << LOG[n]) - 2, (1 << LOG[n]) - m), t1;
		t1.pre.push_back(1 << LOG[n]);
		t1.pre.push_back((1 << LOG[n]) - 1);
		int j = 0;
        sort(t.pre.begin(), t.pre.end());
        t.pre.push_back(0); 
        for(int i = 1; i <= (1 << LOG[n]) - 2; i++) {
			while(j < t.pre.size() - 1 && t.pre[j] < i) j++;
			if(i == t.pre[j]) continue;
			t1.pre.push_back(i);
		}
		return t1;
	}
}
int main() {
	for(int i = 2; i <= 1000000; i++) {
		LOG[i] = LOG[i >> 1] + 1;
	}
	scanf("%d", &t);
	while(t--) {
        flg = 0;
		scanf("%d %d", &n, &m);
		if((1 << LOG[n] + 1) - 2 == n && (m == n - 1 || m == n - 2)) {
			puts("-1");
			continue;
		}
		if((1 << LOG[n] + 1) - 2 == n && m == n) {
			for(int i = 1; i <= n; i++) {
				printf("%d ", i);
			}
			puts("");
			continue;
		}
		if(n == (1 << LOG[n] + 1) - 1 && m == n - 1) {
			for(int i = 1; i <= m; i++) {
				printf("%d ", i);
			}
			puts("");
			continue;
		}
		if(m == 1) {
			if(n == (1 << LOG[n] + 1) - 1) {
				printf("%d\n", n);
			} else {
				puts("-1");
			}
			continue;
		}
		if(!(n & 1) && m == n) {
			puts("-1");
			continue;
		}
		if((n & 1) && (m == n || m == n - 1)) {
			puts("-1");
			continue;
		}
		if(m < (1 << LOG[n])) {
			node t = solve(n, m);
			for(int i = 0; i < m; i++) {
				printf("%d ", t.pre[i]);
			}
		} else {
			int p = 0, cnt = 0, lim = (1 << LOG[n]) - 1;
			for(int i = 1; i <= lim; i++) {//1 到 lim 都选上 
				p ^= i;
				cnt++;                     
			}
			for(int i = lim + 1; i <= n; i++) {
				if((m & 1) && cnt == m + 1) break;
				if(!(m & 1) && cnt == m + 2) break;
				p ^= i;
				cnt++; 
			}
			int flg = lim - (p & (lim));
			if(flg == 0) {
				if(!(m & 1)) {
					for(int i = 1; i <= n - 4; i++) printf("%d ", i);
					printf("%d", n);
				} else {
					for(int i = 1; i < lim; i++) printf("%d ", i);
					for(int i = lim + 2; i <= n; i++) printf("%d ", i);
				}	
			} else if(m & 1) {
				for(int i = 1; i <= cnt; i++) {
					if(i == flg) continue;
					printf("%d ", i);
				}		
			} else {
				int flg1 = lim, flg2 = abs(flg - flg1);
				for(int i = 1; i <= cnt; i++) {
					if(i == flg1 || i == flg2) continue;
					printf("%d ", i);
				}
			}
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：zibenlun (赞：18)

# 骗分还得是[模拟退火](https://baike.baidu.com/item/%E6%A8%A1%E6%8B%9F%E9%80%80%E7%81%AB%E7%AE%97%E6%B3%95/355508)

## 思路

了解了模拟退火算法后，本题几乎成为了一道板子题，但是还有一些细节需要去解决一下。

模拟退火算法本来是用来求最值的，所以对于本题来说其中退火的环节确实有点多余，所以我们为了本人~~更好地偷懒~~解法的正确性，我们要舍去多余的退火。

舍去了退火之后会发现，如何解决是否交换的问题呢？其实只需要全部交换就可以了，因为异或这种运算没什么太大的规律。

之后是我们总体的思路，首先预处理一下要用的 $lg$ 数组，然后对于每一个 $n$ 准备好的原数组和它的前 $m$ 个异或和，还有要比较的数。之后跑模拟退火直到出结果或者无解就好了。

更多的代码细节还是直接看代码吧。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {
		s=(s<<3)+(s<<1)+(ch^48);
		ch=getchar();
	}
	return s;
}
inline void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int flag=0,lg[1000005];
int a[1000005],n,m,t,pos=1,sum;
void SA(){
	for(int i=1;i<=10000;i++){
		int l=rand()%m+1,r=m+rand()%(n-m)+1;
		sum^=a[l];
		sum^=a[r];
		swap(a[l],a[r]);
		if(sum==pos){
			flag=1;
			return ;
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	srand(time(0));
	cin>>t;
	for(int i=1;i<=1000000;i++) lg[i]=lg[i-1]+(1<<lg[i-1]==i);
	while(t--){
		cin>>n>>m;
		if(n==m){
			for(int i=1;i<=n;i++) a[i]=i;
			flag=sum=0;
			for(int i=1;i<=m;i++) sum^=i;
			pos=1;
			for(int i=1;i<=lg[n];i++) pos*=2;
			pos--;
			if(sum==pos) {
				for(int i=1;i<=n;i++) cout<<i<<" ";
				cout<<"\n";
				continue;
			}
			else {
				cout<<"-1\n";
				continue;
			}
		}
		for(int i=1;i<=n;i++) a[i]=i;
		flag=sum=0;
		for(int i=1;i<=m;i++) sum^=i;
		pos=1;
		for(int i=1;i<=lg[n];i++) pos*=2;
		pos--;
		for(int i=1;i<=90;i++){
			SA();
			if(flag){
				for(int j=1;j<=m;j++){
					cout<<a[j]<<" ";
				}
				cout<<"\n";
				break;
			}
		}
		if(!flag){
			cout<<"-1\n";
		}			
	}
	return 0;
}
```

## 温馨提示
本代码不一定可以一遍过，如果答案错误的话，多提交几遍就可以了。


---

## 作者：yimuhua (赞：10)

更简单的解法。

考虑怎么用比较少的数搞出 $2^{\lfloor\log_2 n\rfloor+1}-1$，发现一个方法是选择 $\operatorname
{highbit}(n)$ 和 $\operatorname
{highbit}(n) - 2$。此时可能个数还不够 $m$，那么我们试图搞搞第 $0$ 位。

把 $n=7$ 写出来：

```
111
110
101
100
 11
 10
  1
```

首先选的是 ```100``` 和 ```10```，然后我们发现 $2i$ 和 $2i + 1$ 异或值恰为 $1$，可以两个两个选。分讨一下 $m$ 的奇偶性即可。

但是我们发现这个做法在少数情况下会出错，具体为 $m=1$ 和 $n-m\leq2$ 时。

$m=1$ 出错的原因显然：这个做法首先就要选两个数。这时可以 $O(n)$ 枚举做。

而另一种的问题在于我们有可能浪费了两个数 $\operatorname{highbit}(n)-1$ 和 $n$，此时也可以 $O(n)$ 枚举做。

于是特判后按此方法做，总时间为 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m;
vector<int> res[4][4];
vector<int> f(int n, int m) {
	if(max(n, m) < 4)
		return res[n][m];
	int tmp, t;
	vector<int> ans;
	for(int i = 29; ~i; i--)
		if(n >> i & 1) {
			tmp = i;
			break;
		}
	t = (1 << tmp + 1) - 1;
	if(m == 1) {
		if(n == t)
			return {n};
		return {};
	}
	if(n - m < 3) {
		int s = 0;
		for(int i = 1; i <= n; i++)
			s ^= i;
		if(n == m) {
			if(s == t) {
				for(int i = 1; i <= n; i++)
					ans.push_back(i);
				return ans;
			}
			return {};
		}
		if(n == m + 1) {
			for(int i = 1; i <= n; i++)
				if((s ^ i) == t) {
					for(int j = 1; j <= n; j++)
						if(i ^ j)
							ans.push_back(j);
					return ans;
				}
			return {};
		}
		if(n == m + 2) {
			for(int i = 1; i <= n; i++) {
				int cur = s ^ i ^ t;
				if(cur != i && cur <= n) {
					for(int j = 1; j <= n; j++)
						if(i != j && cur != j)
							ans.push_back(j);
					return ans;
				}
			}
			return {};
		}
	}
	ans = {1 << tmp, (1 << tmp) - 2}, ans.reserve(m);
	int f = 1;
	if(m & 1)
		ans.push_back(1), f = 0;
	for(int i = 2; i < n && ans.size() < m; i += 2)
		if(i != (1 << tmp) && i != (1 << tmp) - 2)
			ans.push_back(i), ans.push_back(i + 1), f ^= 1;
	if(!f)
		return ans;
	ans[1]++;
	return ans;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t, res[1][1] = {1}, res[2][2] = {1, 2}, res[3][1] = {3}, res[3][2] = {1, 2};
	while(t--) {
		cin >> n >> m;
		vector<int> v = f(n, m);
		if(v.empty())
			cout << -1;
		else
			for(int i : v)
				cout << i << ' ';
		cout << '\n';
	}
	return 0;
}
```


---

## 作者：Unnamed114514 (赞：9)

### 8 pts

暴搜，时间复杂度 $O(m2^n)$，期望得分 $8$。

### 35 pts

背包，定义 $f_{i,j,k}$ 表示前 $i$ 个数中选了 $j$ 个的异或值是否为 $k$，然后就转化成了一个背包问题。

时间复杂度 $O(n^3)$，期望得分 $35$。

### 47 pts

转化一下问题：长度为 $n$ 的排列取前 $m$ 个数。

一个最原始的搜索方式：枚举 $n$ 的全排列，然后取前 $m$ 个数，时间复杂度 $O(n!m)$。

本着随机化贪心的思想，我们可以限制枚举全排列的数量，然后从全排列里随机选择一些数，这一步可以用 `random_shuffle` 实现。

期望得分玄学，如果要追求正确率的话，次数设成 $10^4$，然后就能得到 $47$ 分的好成绩。

### 100 pts

考虑异或的性质：

- 对于一个集合 $\mathbb S$，其异或值为 $s$，此时插入和删除一个数 $k$ 的话，$s\gets s\operatorname{xor} k$。

考虑全排列的实现方法中，可以交换这个排列的任意两个值，从而得到新的排列。

此时我们从 $[1,m]$ 和 $[m+1,n]$ 中选择两个数 $x,y$，那么我们只需要删除 $a_x$，加入 $a_y$ 即可。

注意阈值的设计：

若直接设置一个值 $H$，那么此时在多测的 $10^6$ 组数据下会 TLE，所以我们可以直接把阈值设成 $\dfrac{10^8}{T}$ 即可。

---

## 作者：MarSer020 (赞：5)

联考 $\text{T1}$ 放 $\text{Ad-hoc}$，没有一点素质。

$\Large\text{Solution}$

看到 $\text{Ad-hoc}$ 应该干什么？打表，启动！

（由于我太菜了，只会 $\Theta(2^n)$ 暴力打表，但是打得飞快/xyx）

首先可以把 $n,m\le 3$ 特判掉，这是很 naive 的。

然后看无解时有什么性质，发现一对 $n,m$ 无解当且仅当满足如下条件之一：

- $m>n$
- $m=n$ 且 $n\neq 2^k-2$
- $m=1$ 且 $n\neq 2^k-1$
- $m=n-1,n-2$ 且 $n=2^k-2$
- $m=n-1$ 且 $n$ 为奇数

（$k$ 为正整数且 $n,m\geq 3$）

然后我们就可以写出如下的 `checker`：

```cpp
bool check(int n,int m){
    if(n==1&&m==1)
        return 1;
    if(__builtin_popcount(n+1)==1)
        return n!=m;
    if(m==1)
        return 0;
    if(__builtin_popcount(n+2)==1){
        if(n==m+1||n==m+2)
            return 0;
        return 1;
    }
    if(n==m||(n==m+1&&n&1))
        return 0;
    return 1;
}
```

在这之后我们来观察最后一项，打出表长这样（以 $n=24$ 为例）：

```cpp
-1 16 16 16 16 16 16 16 16 16 16 16 16 16 16 18 18 20 20 22 22 24 24 -1
```

定义 $f_{x,y}$ 为 $n=x,m=y$ 时的一组答案，$t=2^{\lfloor\log_2 n\rfloor+1}$。 

发现前面 $m<16$ 的部分最后一项全部都是 $16$，大胆猜测有 $f_{n,m}=f_{\frac{t}{2}-1,m-1}+\frac{t}{2},m<\frac{t}{2}$，这种情况递归计算即可。

考虑 $n=t-1$ 的情况：

- 若 $m=n-1$，则 $f_{n,m}=f_{n-1,m}$
- 若 $m=n-2$，则 $f_{n,m}=\{x\mid x\in\left[2,m\right]\cup\{n\}\}$
- 若 $m=n-3$，则 $f_{n,m}=\{x\mid x\in\left[1,m-1\right]\cup\{n\}\}$
- 若 $m<n-3$，则 $f_{n,m}=f_{n-3,m}$

然后是 $n=t-2$ 的情况：

- 若 $m=n$，则 $f_{n,m}=\{x\mid x\in\left[1,m\right]\}$
- 若 $m\neq n$，则 $f_{n,m}=f_{n-2,m}$

再考虑 $n>m+2$ 的情况，此时注意到最后一项是 $\leq n-2$ 的，所以有 $f_{n,m}=f_{n-2,m},n>m+2$。

最后来看 $n-m\leq 2$ 的情况，设此时 $sum=t\oplus(\bigoplus_{i=1}^{n}i)$，则我们只需要去掉 $n-m$ 个满足异或和为 $sum$ 的数即可，故有：

- $n-m=1$ 时，取所有满足 $x\in\left[1,n\right],x\notin\{sum\}$ 的 $x$ 即可。
- $n-m=2$ 时：
	- 若 $\exists a\texttt{ s.t. }2^a=sum$，取所有满足 $x\in\left[1,n\right],x\notin\{1,sum+1\}$ 的 $x$ 即可。
    - 若 $\nexists a\texttt{ s.t. }2^a=sum$，设 $sum=2^a+2^b$，则取所有满足 $x\in\left[1,n\right],x\notin\{2^a,2^b\}$ 的 $x$ 即可。
	- 由于无解情况已经判断过了，所以 $sum$ 一定满足上述两个条件之一。

大力模拟即可，时间复杂度 $\Theta(\sum n)$。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t;
vector<int>ans,f[5][5];
bool check(int n,int m){
    if(n==1&&m==1)
        return 1;
    if(__builtin_popcount(n+1)==1)
        return n!=m;
    if(m==1)
        return 0;
    if(__builtin_popcount(n+2)==1){
        if(n==m+1||n==m+2)
            return 0;
        return 1;
    }
    if(n==m||(n==m+1&&n&1))
        return 0;
    return 1;
}
void solve(int n,int m){
    if(n<=3){
        for(int x:f[n][m])
            ans.emplace_back(x);
        return;
    }
    if(m==1){
        ans.emplace_back(n);
        return;
    }
    int t=(1<<((int)log2(n)+1));
    if(m<(t>>1)){
        ans.emplace_back(t>>1),n=(t>>1)-1,m--,solve(n,m);
        return;
    }
    if(n==t-1){
        if(m>=n-3){
            if(m==n-1)
                for(int i=1;i<=m;i++)
                    ans.emplace_back(i);
            else if(m==n-2){
                for(int i=2;i<=m;i++)
                    ans.emplace_back(i);
                ans.emplace_back(n);
            }
            else if(m==n-3){
                for(int i=1;i<m;i++)
                    ans.emplace_back(i);
                ans.emplace_back(n);
            }
            return;
        }
        n-=3;
    }
    if(n==t-2){
        if(m==n){
            for(int i=1;i<=m;i++)
                ans.emplace_back(i);
            return;
        }
        n-=2;
    }
    if(n&1)
        n--;
    while(n-2>m)
        n-=2;
    int s=t-1,p=-1;
    for(int i=1;i<=n;i++)
        s^=i;
    if(n-m==1){
        for(int i=1;i<=n;i++)
            if(i!=s)
                ans.emplace_back(i);
        return;
    }
    for(int i=0;i<30;i++)
        if((s>>i)&1)
            p=i;
    if(__builtin_popcount(s)==1){
        for(int i=1;i<=n;i++)
            if(i!=1&&i!=s+1)
                ans.emplace_back(i);
        return;
    }
    p=1<<p;
    for(int i=1;i<=n;i++)
        if(i!=p&&i!=(s^p))
            ans.emplace_back(i);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    f[1][1]={1},f[2][2]={1,2},f[3][1]={3},f[3][2]={1,2};
    while(t--){
        cin>>n>>m,ans.clear();
        if(!check(n,m)){
            cout<<"-1\n";
            continue;
        }
        solve(n,m);
        for(int x:ans)
            cout<<x<<' ';
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：Z1qqurat (赞：3)

神仙题，感谢 xde 组题 & zdc 提供的简洁做法。

设 $k = \left\lfloor \log_2 n \right\rfloor, t = 2 ^ {k + 1} - 1$。首先考虑如果只是想要最小化选的数的个数那怎么选，肯定就是直接选 $2 ^ k, 2 ^ k - 1$。

当然还得先特判掉 $m = 1$ 的情况，这很简单，接下来默认 $m > 1$。

但是这可能不足 $m$ 个啊，怎么补充？我们试图最小化影响到的位数，发现 $2i \oplus (2i + 1) = 1$，所以我们选择 $(2i, 2i + 1), i \neq 2 ^ {k - 1}, 2 ^ {k - 1} - 1$。这样选择了若干组后，直到选出了 $m$ 个。可能 $m$ 是奇数，这样选不满，我们就再选一个 $1$，并不冲突。

但是这样可能最后，这 $m$ 个数的异或和的个位变成了 $0$，那么我们就把原来的 $2 ^ k - 1$ 改选为 $2^k - 2$。

这可以适用于大部分情况，而当 $n - m \le 2$ 是会错的，因为我们浪费了一些数。

考虑特判一下啊！设 $s$ 为 $1 \sim n$ 所有数的异或和。

* $n = m$，那么只有 $s = t$ 时才有解。
* $n = m + 1$，那么抛弃一个数 $i = s \oplus t$。
* $n = m + 2$，抛弃两个数，枚举其中抛弃的一个 $i$，那么另一个 $j = s \oplus t \oplus i$。

每种情况的复杂度都不超过 $\mathcal O(n)$，阿妹胫骨！

代码有点丑，话说当时是一个交互格式，我在判 `s ^ t ^ i = j` 时没有打括号，Dangerous Syscalls 了一波。

```cpp
/*
ああナイチンゲール　ああナイチンゲール　共に歌おう
Tica-linga-lira Tica-linga-lira　世界の目覚め
*/

#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector <int> a;

vector <int> Shu_Itsuki(int n, int m) {
    int k = log2(n), s = 0, t = (1 << k + 1) - 1;
    vector <int> ans;
    for (int i = 1; i <= n; ++i) s ^= i;
    if(m == 1) {
        if(t >= 1 && t <= n) return {t};
        else return {-1};
    }
    else if(n == m) {
        if(s == t) {
            for (int i = 1; i <= n; ++i) ans.emplace_back(i);
            return ans;
        }
        else return {-1};
    }
    else if(n == m + 1) {
        for (int i = 1; i <= n; ++i) {
            if((s ^ i) != t) continue;
            for (int j = 1; j <= n; ++j) {
                if(j != i) ans.emplace_back(j);
            }
            return ans;
        }
        return {-1};
    }
    else if(n == m + 2) {
        for (int i = 1; i <= n; ++i) {
            int j = (s ^ i ^ t);
            if(j != i && j >= 1 && j <= n) {
                for (int k = 1; k <= n; ++k) {
                    if(k != i && k != j) ans.emplace_back(k);
                }
                return ans;
            }
        }
        return {-1};
    }
    int f = 1;
    ans = {(1 << k) - 2, 1 << k};
    if(m & 1) ans.emplace_back(1), f = 0;
    for (int i = 2; i <= n && ans.size() < m; i += 2) {
        if(i != ans[0] && i != ans[1]) ans.emplace_back(i), ans.emplace_back(i + 1), f ^= 1;
    }
    if(f) ans[0]++;
    return ans;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T; cin >> T;
    while(T--) {
        int n, m; cin >> n >> m;
        a = Shu_Itsuki(n, m);
        for (int i : a) cout << i << " ";
        cout << "\n";
    }
    return 0;
}
```



---

## 作者：StormWhip (赞：2)

### 思路
不难发现，如果已经计算过一组数的异或和，则仅更改其中一个元素后计算其异或和是 $O(1)$ 的。因此可以采用**随机化算法**，预处理前 $m$ 个数的异或和，再重复随机交换其中的数与剩下的数，直到找到答案或判断无解。   
注意特判 $m=n$ 时，若预处理算出的异或和不满足条件，可直接判断无解，否则在选取要交换的两个数时会无法选择。  

### 代码  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,Lim=1e7;
int T,n,m,a[N],p,cnt;
int Pows(int base,int t)
{
	if(t==0) return 1;
	if(t==1) return base;
	int x=Pows(base,t/2),ans=x*x;
	if(t&1) ans*=base;
	return ans;
}
void Output()
{
	for(int i=1;i<=m;i++) cout<<a[i]<<" ";
	cout<<"\n";
}
void Solve()
{
	cin>>n>>m;
	p=0,cnt=Pows(2,(int)log2(n)+1)-1;
	for(int i=1;i<=n;i++) a[i]=i;
	for(int i=1;i<=m;i++) p^=i;
	for(int times=1;times<=Lim/(T+1);times++)
	{
		if(p==cnt) {Output();return;}
		if(n==m) {cout<<"-1\n";return;}
		int p1=rand()%m+1,p2=rand()%(n-m)+m+1;
		p^=a[p1],p^=a[p2];
		swap(a[p1],a[p2]);
	}
	cout<<"-1\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	srand(time(0));
	cin>>T;
	while(T--) Solve();
	return 0;
}
```

---

## 作者：youkasgs_wyb (赞：2)

随机化算法永远的神！！！

### 思路
正解不好想，但对于随机化算法来说这道题还是很~~简单~~的。我们只需要先取 $1$ 到 $m$ ，然后异或进行特判，如果成功了就代表有解，没成功就从 $m+1$ 到 $n$ 中随机选出一个与选好的数中交换，这样的过程重复越多，正确概率越大，但评测有时间限制，所以时间到了跳出，输出 $-1$ 就行，由于多组样例，所以无法调用特殊的取时间函数，所以只能进行特殊的处理，具体见代码。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>inline void readT(T &x)
{
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
template<typename T>inline void writeT(T x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) writeT(x/10);
    putchar(x%10+'0');return;
}
int a[1000005],n,m,t,f,g,s,l,r,tt;
int main(){
	srand(19491001);//祖国保佑 
	srand(rand());
	srand(rand());
	readT(t);
	tt=t;
	while(t--)
	{
		f=0;
		s=1;
		readT(n);
		readT(m);
		g=1;
		while(g<=n)//取出pow(2,[log2(n)]+1)-1的值，注意一定要是小于等于 
		{
			g=g*2;
		}
		g--;
		for(int i=1;i<=n;i++)
		{
			a[i]=i;
		}
		for(int i=2;i<=m;i++)//求出前m个数的异或值 
		{
			s^=i;
		}
		for(int i=1;i<=100000000/tt;i++)//用到之前的tt，用1e8/tt决定随机次数，接近时间的限制，并且最大化解的正确率
		//md逆天出题人放了一个t=1e6，直接卡崩了，然后又放两个t=1,n=1e6，真服了（数据是开while(1)卡测评特判出的） 
		{
			if(s==g)//取到了解 
			{
				f=1;//标记 
				for(int j=1;j<=m;j++)
				{
					writeT(a[j]);
					printf(" ");
				}
				puts("");
				break;
			}
			if(n==m)//一定要特判，没有这个特判会RE，因为下面随机数n-m会等于0 
			{
				break;
			}
			l=rand()%m+1;//取好的数 
			r=rand()%(n-m)+m+1;//没取的数 
			//交换 
			s^=a[l];
			s^=a[r];
			swap(a[l],a[r]);
		}
		if(f==0)//随机够多了，还是没有解肯定是数据不会有解 
		{
			puts("-1");
		}	
	}
	return 0;
}
```

### 后记

随机化算法在不会的情况或者是时间不够的时候真的挺好用的，因为思路简单，好实现。实测交了几次都是对的，所以正确率挺高的。

本文用到的链接。

[快读快写](https://blog.csdn.net/m0_73020012/article/details/133470285)

[随机化算法](https://www.cnblogs.com/int-Hello-world/p/17218478.html)

---

## 作者：EuphoricStar (赞：1)

NOIP 模拟赛 T1。

避免被 corner case 卡，首先暴力特判 $n \le 7$，以及 $m = 1$。

令 $t = 2^{\left\lfloor\log_2 n\right\rfloor + 1} - 1$。

手玩一下 $n = 20$。转化一下我们要在 $1 \sim 20$ 中去除 $n - m$ 个数，使得剩下的数异或和为 $t$。

因为 $1 \oplus 2 \oplus 3 \oplus \cdots \oplus 20 = 20$，$t = 31$，所以 $m = 20$ 显然无解。

考虑 $m = 19$，发现我们可以把 $11$ 去掉，变成 $1 \sim 10, 12 \sim 20$。

$m = 18$ 时，发现 $10 \oplus 1 = 11$，所以可以变成 $2 \sim 9, 11 \sim 20$。

$m = 17$ 时，我们没有 $1$ 了，需要弄出一个 $1$。发现可以合并 $2, 3$，变成 $1, 4 \sim 9, 11 \sim 20$。

发现这个过程是可以一直做的。如果有 $1$ 就把 $10$ 变成 $11$ 或者把 $11$ 或者 $10$，没有就选两个最小的相邻的数，使得它们的异或是 $1$，合并它们。

这个做法是可以推广到所有 $n$ 为偶数的，因为 $n$ 为偶数时 $1 \oplus 2 \oplus \cdots \oplus n = n$ 或 $n + 1$。

但是发现有例外。当 $n = 2^k - 2$ 时，$1 \oplus 2 \oplus \cdots \oplus n = t$，例如 $n = 14$ 时，$1 \oplus 2 \oplus \cdots \oplus 14 = 15$，意味着 $m = 14$ 有解，且 $m = 12, 13$ 都无解。$m = 11$ 时可以把 $1, 2, 3$ 抠出来，变成 $4, 5, \ldots, 14$。$m = 10$ 时，合并 $4, 6$，得 $2, 5, 7, 8, \ldots, 14$。之后采取这样的策略，如果有 $1$ 就把 $1$ 和当前除 $1$ 的最小数合并，否则制造一个 $1$，也就是：

$$1, 2, 5, 10, 11, 12, 13, 14$$

$$3, 5, 10, 11, 12, 13, 14$$

$$1, 3, 5, 12, 13, 14$$

$$2, 5, 12, 13, 14$$

$$1, 2, 5, 14$$

$$3, 5, 14$$

这时候可以把 $3, 5$ 合并变成 $6, 14$。

当 $n$ 为奇数时，$1 \oplus 2 \oplus \cdots \oplus n = 0$ 或 $1$。此时 $m = n - 1$ 无解。对于 $m = n - 2$，例如 $n = 19, m = 17$ 时，可以把 $8, 6$ 抠出来变成 $1 \sim 5, 7, 9 \sim 19$。发现可以按 $n$ 为偶数做了，有 $1$ 就把 $1$ 和 $7$ 合并得到 $6$ 或 $1$ 和 $6$ 合并得到 $7$，否则合并最小的相邻两个数使得它们异或起来是 $1$。

```cpp
vector<int> haruka_sora(int n, int m) {
	int s = 0, t = (1 << (__lg(n) + 1)) - 1;
	if (m == 1) {
		return n == t ? vector<int>(1, n) : vector<int>();
	}
	if (n <= 7) {
		for (int S = 0; S < (1 << n); ++S) {
			if (__builtin_popcount(S) != m) {
				continue;
			}
			int x = 0;
			for (int i = 1; i <= n; ++i) {
				if (S & (1 << (i - 1))) {
					x ^= i;
				}
			}
			if (x == t) {
				vector<int> ans;
				for (int i = 1; i <= n; ++i) {
					if (S & (1 << (i - 1))) {
						ans.pb(i);
					}
				}
				return ans;
			}
		}
		return vector<int>();
	}
	for (int i = 1; i <= n; ++i) {
		s ^= i;
	}
	if (m == n) {
		if (s == t) {
			vector<int> ans;
			ans.resize(n);
			for (int i = 0; i < n; ++i) {
				ans[i] = i + 1;
			}
			return ans;
		} else {
			return vector<int>();
		}
	}
	if (s == t) {
		if (m == n - 1 || m == n - 2) {
			return vector<int>();
		}
		if (m == n - 3) {
			vector<int> ans;
			ans.resize(n - 3);
			for (int i = 4; i <= n; ++i) {
				ans[i - 4] = i;
			}
			return ans;
		}
		vector<int> ans;
		ans.resize(n - 4);
		int len = 0;
		for (int i = n; i >= 5; --i) {
			if (i != 6) {
				ans[len++] = i;
			}
		}
		ans[len++] = 2;
		for (int _ = n - 4; _ > m; --_) {
			if (ans.back() == 1) {
				int x = ans.back();
				ans.pop_back();
				x ^= ans.back();
				ans.pop_back();
				ans.pb(x);
			} else {
				bool flag = 1;
				for (int i = (int)ans.size() - 1; i; --i) {
					if ((ans[i] ^ ans[i - 1]) == 1) {
						ans.erase(ans.begin() + i);
						ans.erase(ans.begin() + i - 1);
						ans.pb(1);
						flag = 0;
						break;
					}
				}
				if (flag) {
					break;
				}
			}
		}
		if ((int)ans.size() == m) {
			return ans;
		}
		reverse(ans.begin(), ans.end());
		while ((int)ans.size() > m) {
			int x = ans[0], y = ans[1];
			ans.erase(ans.begin());
			ans.erase(ans.begin());
			ans.insert(ans.begin(), x ^ y);
		}
		return ans;
	}
	if ((s ^ t) <= n) {
		vector<int> ans;
		ans.resize(n - 2);
		int len = 0;
		for (int i = n; i; --i) {
			if (i != (s ^ t) && i != (s ^ t ^ 1)) {
				ans[len++] = i;
			}
		}
		int x = s ^ t ^ 1;
		for (int _ = n - 1; _ > m; --_) {
			if (ans.back() == 1) {
				x ^= 1;
				ans.pop_back();
			} else {
				for (int i = (int)ans.size() - 1; i; --i) {
					if ((ans[i] ^ ans[i - 1]) == 1) {
						ans.erase(ans.begin() + i);
						ans.erase(ans.begin() + i - 1);
						ans.pb(1);
						break;
					}
				}
			}
		}
		ans.pb(x);
		return ans;
	}
	if (m == n - 1) {
		return vector<int>();
	}
	int x = (1 << __lg(n));
	int y = s ^ t ^ x ^ 1;
	vector<int> ans;
	ans.resize(n - 3);
	int len = 0;
	for (int i = n; i; --i) {
		if (i != x && i != y && i != (y ^ 1)) {
			ans[len++] = i;
		}
	}
	for (int _ = n - 2; _ > m; --_) {
		if (ans.back() == 1) {
			y ^= 1;
			ans.pop_back();
		} else {
			for (int i = (int)ans.size() - 1; i; --i) {
				if ((ans[i] ^ ans[i - 1]) == 1) {
					ans.erase(ans.begin() + i);
					ans.erase(ans.begin() + i - 1);
					ans.pb(1);
					break;
				}
			}
		}
	}
	ans.pb(y);
	return ans;
}
```


---

