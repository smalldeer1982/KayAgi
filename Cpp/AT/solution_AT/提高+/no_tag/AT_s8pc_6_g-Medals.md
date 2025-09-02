# Medals

## 题目描述

### 题意翻译

一场比赛有 $N$ 人参加，第一天第 $i$ 个人得到了 $A_i$ 分，且分数互不相同，第二天每个人的得分将是一个 $1,2\dots,N$ 的排列，比赛的排名按两天的总分从大到小排序（有同分则随机排序），第一、二、三名分别为金、银、铜牌。现在，你已知每个人第一天的分数，给定 $P$ 求符合以下要求的三元组 $\left (x,y,z\right ) $ 的数量。

1. 当 $P=1$ 时，$A_x>A_y>A_z$；当 $P=2$ 时，$A_x>A_z>A_y$。
2. 第 $x,y,z$ 个人在第二天结束后可能分别获得金、银、铜牌。

## 说明/提示

$5\le N\le 10^6$，$P\in\left \{ 1,2\right \}$，$1\le A_i\le10^9$

[Y204335](https://www.luogu.com.cn/user/360974) 翻译

## 样例 #1

### 输入

```
5 1
3 1 6 4 8```

### 输出

```
4```

## 样例 #2

### 输入

```
5 2
6 4 1 7 2```

### 输出

```
3```

## 样例 #3

### 输入

```
10 1
6 4 11 14 3 17 13 18 8 10```

### 输出

```
26```

## 样例 #4

### 输入

```
10 2
18 14 19 4 12 1 7 15 9 5```

### 输出

```
14```

# 题解

## 作者：Y204335 (赞：5)

# AT\_s8pc\_6\_g Medals

## 题目大意

有 $N$ 人，已知每人第一天的分数，且分数互不相同，第二天的分数未知，但一定是一个 $1,2\dots,N$ 的排列。第二天后会根据总分分出前三名（有同分则随机排序），给定 $P$ 求符合要求的三元组 $\left (x,y,z\right )$ 的数量。

## 题目分析

可以先把 $A$ 降序排序，那么很显然 $A_1+1 \ge A_2+2 \ge \dots \ge A_N+N$，也就是说加上一个 $1,2\dots,N$ 的排列后可以使其**大小关系不发生变化**，这样就比较好处理了，可以分类讨论。

#### 当 $P=1$ 时

- $\left (1,2,3\right)$ 显然是合法的。

- $\left (1,2,x\right) \left (3<x\right)$ 是合法的，当且仅当 $A_x+N\ge A_3+1$。

- $\left (1,x,y\right) \left (2<x<y\right)$ 是合法的，当且仅当 $A_y+N\ge A_2+1$。

- $\left (x,y,z\right) \left (1<x<y<z\right)$ 是合法的，当且仅当 $A_z+N\ge A_1+1$。

#### 当 $P=2$ 时

- $\left (1,x,2\right) \left (2<x\right)$ 是合法的，当且仅当 $A_x+N\ge A_2+1$。

- $\left (1,x,y\right) \left (2<y<x\right)$ 是合法的，当且仅当 $A_x+N\ge A_2+1$。

- $\left (x,y,z\right) \left (1<x<z<y\right)$ 是合法的，当且仅当 $A_y+N\ge A_1+1$。

直接统计即可，复杂度为 $O\left(n\right)$。

证明以 $P=2$ 的第一种情况为例，其他情况都类似。可以先令排列为初始的 $1,2,\dots,N$，此时 $A_1+1\ge A_2+2\ge\dots\ge A_N+N$，再把第 $N$ 项 与第 $1$ 项交换，并整体右移，即 $A_1+N\ge A_2+1\ge\dots\ge A_N+N-1$，并且此时右侧都符合条件（$A_2+1\ge A_3+2\ge \dots \ge A_N+N-1$）。现在记 $p=A_2+1-A_x\ge x$，由于 $A_x+N\ge A_2+1$，所以 $p=A_2+1-A_x\le N$。若 $p<N$，则交换 $p+1$ 与 $x$，此时 $A_1+N\ge A_x+p=A_2+1\ge others$；若 $p=N$，则令第一项为 $N-1$，第二项为 $N$，第 $N$ 项为 $x-1$，即 $A_1+N-1\ge A_x+N=A_2+1\ge others$。综上，只要满足 $A_x+N\ge A_2+1$ 一定合法。

注：证明参考了他人的想法，在这里致谢。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
int t, n, p, a[N];
ll ans;
bool cmp(int a, int b) { return a > b; }
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> p;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1, cmp);
    ans = 0;
    if (p == 1) {
        ans++;
        for (int i = 4; i <= n; i++) {
            if (a[i] + n >= a[3] + 1)
                ans++;
        }
        for (int i = 4; i <= n; i++) {
            if (a[i] + n >= a[2] + 1)
                ans += i - 2 - 1;
        }
        for (int i = 4; i <= n; i++) {
            if (a[i] + n >= a[1] + 1)
                ans += 1ll * (i - 2) * (i - 3) / 2;
        }
    } else {
        for (int i = 3; i <= n; i++) {
            if (a[i] + n >= a[2] + 1)
                ans++;
        }
        for (int i = 4; i <= n; i++) {
            if (a[i] + n >= a[2] + 1)
                ans += i - 3;
        }
        for (int i = 4; i <= n; i++) {
            if (a[i] + n >= a[1] + 1)
                ans += 1ll * (i - 2) * (i - 3) / 2;
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Larryyu (赞：3)

## _Description_

有 $n$ 名选手在打比赛，编号依次为 $1,2,\cdots ,n$，比赛分为两天：

- 第一天 $n$ 名选手的得分分别为 $A_1,A_2\cdots A_n$，保证 $A_i$ 互不相同。
- 第二天 $n$ 名选手的得分为 $n$ 的一个排列。

选手的排名为两天总分的排名，若有同分则同分的人随机排名，前三名的选手分别获得金、银、铜牌。

给定一个数 $P$，询问有多少个不同的三元组 $(x,y,z)$ 满足下列条件并且编号为 $x,y,z$ 的选手最终依次获得金、银、铜牌。

- 若 $P=1$，则需要保证 $A_x>A_y>A_z$。
- 若 $P=2$，则需要保证 $A_x>A_z>A_y$。

## _Solution_

首先特判 $n\le2$ 无解。

一个很重要的性质就是 $\forall 1\le i,j\le n,A_i\ne A_j$，这使得 $A_i$ 从大到小排序后，$A_i+x\ge A_{i+1}+x+1$。

应此我们先将 $A$ 从大到小排序。

然后我们对两种情况分别考虑。

### _Sol1_

对于 $(x,y,z)$，我们让他们第二天分别获得 $n-2,n-1,n$ 分，这样使得排名尽量前且不改变内部顺序。

对于其他选手，我们按 $A$ 从大到小依次给他们 $1,2,\cdots,n-3$ 分。

设 $w$ 是除三名选手外 $A$ 最大的选手编号，那么只要满足 $A_w+1\le A_z+n$，就能使 $(x,y,z)$ 合法。

枚举 $z$，通过 ```lower_bound``` 找到满足 $A_w+1>A_z+n$ 的 $w$ 的个数，分情况讨论：

- $w=0$，答案贡献为 $(z-1)\times(z-2)$。
- $w=1$，答案贡献为 $(z-2)$。
- $w=2$，答案贡献为 $1$。

- $w>2$，没有答案贡献。

### _Sol2_

对于 $(x,y,z)$，设 $A_z=A_y+k$，那么第二天 $y$ 得 $n$ 分，$z$ 得 $n-k$ 分，$x$ 得剩下分中最大的，这是最优分配方案，此时 $y,z$ 总分相同，$x$ 总分最大。

枚举 $y$，找到满足 $A_z< A_y+n$ 的选手个数 $w$，设其中最大的 $A$ 为 $val$，其标号为 $c$。

若 $c=1$，那么将 $w$ 减一，因为我们要留下 $x$ 的位置。

如果 $A_1+1\le A_y+n$，说明 $w$ 个选手中每一个的人都能成为 $z$，然后再找一个 $A$ 比他大的人当 $x$ 就行了，这里的贡献为 $n-(z+1)+n-(z+2)+\cdots+n-(z+w)$。

否则我们继续分讨。

注意到三人之外的 $A$ 最大的人可能取 $1$ 或 $2$。

当 $val=A_y+n-1$ 时，$y$ 把 $1$ 取了，那除 $x,y,z$ 外 $A$ 最大的只能取 $2$。

- $val=A_2$，那么含 $c,y$ 的合法三元组只有 $(1,y,2)$。
- 若 $A_2+2\le A_y+n$，那么含 $c,y$ 的合法三元组只有 $(1,y,c)$。
- 否则没有合法三元组同时包含 $c,y$。

现在只剩下判断 $(1,y,?)$ 是否合法，和 $P=1$ 差不多，但这里只需要判断 $A_2+1\le A_y+n$ 即可。

注意，为编写方便，下面所有 ```lower_bound``` 都在顺序数组中使用，所以与上文的下标有所不同。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,p,ans;
int a[1000010],b[1000010];
map<int,bool> vis; 
bool cmp(int x,int y){
	return x>y;
}
void solve(){
	cin>>n>>p;
	ans=0,vis.clear();
	for(int i=1;i<=n;i++){
		cin>>a[i];
		vis[a[i]]=1;
		b[i]=a[i];
	}
	if(n<=2){
		cout<<0<<'\n';
		return ;
	}
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+n);
	if(p==1){
		for(int i=3;i<=n;i++){
			int x=lower_bound(b+1,b+1+n,a[i]+n)-b;
			if(a[i]+n>a[1]){
				ans+=(i-1)*(i-2)/2;
			}else if(x==n){
				ans+=i-2;
			}else if(x==n-1) ans++;
		}
		cout<<ans<<'\n';
	}else{
		for(int i=3;i<=n;i++){
			int c=lower_bound(b+1,b+1+n,a[i]+n)-b-1;
			int y=lower_bound(b+1,b+1+n,a[i])-b;
			int w=c-y;
			if(c==n){
				w--,c--;
			}
			if(!w) continue;
			if(a[1]+1<=a[i]+n){
				ans+=w*(n-c+n-y-1)/2;
				continue;
			}
			if(b[c]+1==a[i]+n){
				if(c==n-1) ans++;
				else if(a[2]+2<=a[i]+n){
					ans++;
				}
				w--,c--;
			}
			if(!w) continue;
			if(a[2]+1<=a[i]+n){
				ans+=w;
			}
		}
		cout<<ans<<'\n';
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：qnqfff (赞：1)

唐龙题。

### 思路：

考虑 $p=1$ 怎么做，先排序，设答案为 $(x,y,z)$，令 $S$ 表示剩下人的下标集合，显然给这三个人分别分配 $n-2,n-1,n$，给其他人倒叙分配一定是最优的，则其满足 $a_z+n\ge(\max\limits_{i\in S}a_i)+1$，即可，因为剩下人的最大值只可能在后四个位置，随便算下答案就行了。

考虑 $p=2$ 怎么做，先排序，设答案为 $(x,y,z)$，令 $S$ 表示剩下人的下标集合，那么一定是让 $y$ 和 $z$ 相等最优，要满足 $a_z-a_y<n$，然后满足 $a_y+n\ge(\max\limits_{i\in S}a_i)+1$，对于一个 $z$，显然合法的 $y$ 有单调性，可以双指针也可以二分。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int T,n,typ,a[1000010];
void sub1(){
	if(n<3){cout<<0<<'\n';return ;}if(n==3){cout<<1<<'\n';return ;}
	int ans=1;for(int i=n-3;i&&a[i]+n>=a[n]+1;i--) ans+=(n-i-1)*(n-i-2)/2;
	for(int i=n-3;i&&a[i]+n>=a[n-1]+1;i--) ans+=n-i-2;
	for(int i=n-3;i&&a[i]+n>=a[n-2]+1;i--) ans++;cout<<ans<<'\n';
}
void sub2(){
	if(n<3){cout<<0<<'\n';return ;}if(n==3){cout<<(a[1]+3>=a[2]+1)<<'\n';return ;}
	int ans=(a[n-1]-a[n-2]<n);
	for(int i=n-2;i^1;i--){
		int l=1,r=i-1,res=0,mid;
		auto check=[&](int x){return a[i]-a[x]<n&&a[x]+n>=a[n]+1;};
		while(l<=r) (check(mid=l+r>>1)?res=i-mid,r=mid-1:l=mid+1);
		ans+=res*(n-i-1);
	}for(int i=n-2;i^1;i--){
		int l=1,r=i-1,res=0,mid;
		auto check=[&](int x){return a[i]-a[x]<n&&a[x]+n>=a[n-1]+1;};
		while(l<=r) (check(mid=l+r>>1)?res=i-mid,r=mid-1:l=mid+1);
		ans+=res;
	}for(int i=n-3;i&&a[n-1]-a[i]<n&&a[i]+n>=a[n-2]+1;i--) ans++;cout<<ans<<'\n';
}
signed main(){
	n=read();typ=read();for(int i=1;i<=n;i++) a[i]=read();sort(a+1,a+1+n);
	if(!(typ^1)){sub1();return 0;}else{sub2();return 0;}
	return 0;
}
```

---

## 作者：AC_love (赞：0)

先给 $a$ 数组从大到小排个序。

当 $P = 1$ 时：

对于一组 $(x, y, z)$，显然我们让他们第二天的分数变成 $(x + n - 2, y + n - 1, z + n)$ 是最好的。

$x, y, z$ 之外的最大的数，我们肯定要给它扔个 $1$。

这个最大的数显然只有可能是 $1, 2, 3$，取决于 $x, y$ 的选择。

$x = 1, y = 2$ 时，合法的 $z$ 满足 $a_z + n \ge a_3 + 1$。

$x = 1, y \neq 2$ 时，合法的 $z$ 满足 $a_z + n \ge a_2 + 1$。此时 $y$ 在比 $z$ 小的数中选即可。

$x \neq 1$ 时，合法的 $z$ 满足 $a_z + n \ge a_1 + 1$。此时 $x, y$ 在比 $z$ 小的数中选即可。

当 $P = 2$ 时：

对于一组 $(x, y, z)$，令 $y = z - w$，显然我们让他们第二天的分数变成 $(x + n - ?, y + n, z + n - w)$ 是最好的。

$x, y, z$ 之外的最大的数，我们肯定要给它扔个 $1$ 或 $2$。

这个最大的数显然只有可能是 $1, 2$，取决于 $x, z$ 的选择。

$x = 1, z = 2$ 时，合法的 $y$ 满足 $a_y + n \ge a_2 + 1$ 且 $a_y + n \ge a_3 + 2$。我们发现只要满足前一条就一定满足后一条。

$x = 1, z \neq 2$ 时，合法的 $y$ 满足 $a_y + n \ge a_2 + 1$ 且 $a_y + n \ge a_z + 2$，我们发现只要满足前一条就一定满足后一条。此时 $z$ 在比 $y$ 小的数中选即可。

$x \neq 1$ 时，合法的 $y$ 满足 $a_y + n \ge a_1 + 1$ 且 $a_y + n \ge a_z + 2$，我们发现只要满足前一条就一定满足后一条。此时 $x, z$ 在比 $y$ 小的数中选即可。

[code](https://atcoder.jp/contests/s8pc-6/submissions/59633367)

---

