# Guess The Maximums

## 题目描述

This is an interactive problem.

Ayush devised a new scheme to set the password of his lock. The lock has $ k $ slots where each slot can hold integers from $ 1 $ to $ n $ . The password $ P $ is a sequence of $ k $ integers each in the range $ [1, n] $ , $ i $ -th element of which goes into the $ i $ -th slot of the lock.

To set the password of his lock, Ayush comes up with an array $ A $ of $ n $ integers each in the range $ [1, n] $ (not necessarily distinct). He then picks $ k $ non-empty mutually disjoint subsets of indices $ S_1, S_2, ..., S_k $ $ (S_i \underset{i \neq j} \cap S_j = \emptyset) $ and sets his password as $ P_i = \max\limits_{j \notin S_i} A[j] $ . In other words, the $ i $ -th integer in the password is equal to the maximum over all elements of $ A $ whose indices do not belong to $ S_i $ .

You are given the subsets of indices chosen by Ayush. You need to guess the password. To make a query, you can choose a non-empty subset of indices of the array and ask the maximum of all elements of the array with index in this subset. You can ask no more than 12 queries.

## 说明/提示

The array $ A $ in the example is $ [1, 2, 3, 4] $ . The length of the password is $ 2 $ . The first element of the password is the maximum of $ A[2] $ , $ A[4] $ (since the first subset contains indices $ 1 $ and $ 3 $ , we take maximum over remaining indices). The second element of the password is the maximum of $ A[1] $ , $ A[3] $ (since the second subset contains indices $ 2 $ , $ 4 $ ).

Do not forget to read the string "Correct" / "Incorrect" after guessing the password.

## 样例 #1

### 输入

```
1
4 2
2 1 3
2 2 4

1

2

3

4

Correct```

### 输出

```
? 1 1

? 1 2

? 1 3

? 1 4

! 4 3```

# 题解

## 作者：Alex_Wei (赞：16)

> [题面传送门](https://www.luogu.com.cn/problem/CF1363D)。

> 题意简述：这是一道交互题。给定一个序列 $a$ **的长度** $n$ 和 $k$ 个**互不相交**的子集 $S_i$。

> 一次查询中，你可以输出一些下标 $q_1,q_2,\cdots,q_c$ 并得到序列 $a$ 的这些下标中最大的数，即 $\max a_{q_i}$。

> 对于每个子集 $S_i$，求出序列 $a$ 不在该子集的下标的最大值，即 $\max_{j\notin S_i} a_j$。

一道有趣的交互题。

---

首先我们可以找到序列 $a$ 最大值的下标 $ind$，这需要 $\lceil \log_2 n \rceil+1=11$ 次询问。

又因为子集是互不相交的，所以含有 $ind$ 的子集只可能有一个，记为 $S_{mx}$。

显然，除了 $S_{mx}$ 之外，其他子集的答案都为 $a_{ind}$。

这时我们再询问一次序列 $a$ 不在 $S_{mx}$ 的下标的最大值，即求出 $\max_{j\notin S_{mx}} a_j$ 即可。

总询问次数不超过 $12$ 次，符合题目条件。

注意需要特判 $index$ 不在任意一个子集里的情况。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair <int,int>
#define fi first
#define se second
#define pb emplace_back
#define all(x) x.begin(),x.end()
#define sor(x) sort(all(x))
#define rev(x) reverse(all(x))
#define mem(x,v) memset(x,v,sizeof(x))

const int N=1e3+5;

int t,n,k,c[N],ind[N];
string s;

int query(int l,int r){
	cout<<"? "<<r-l+1<<" ";
	for(int i=l;i<=r;i++)cout<<i<<" ";
	cout<<endl;
	int ans; cin>>ans; return ans;
}

int main(){
	cin>>t;
	while(t--){
		cin>>n>>k; mem(ind,0);
		for(int i=1;i<=k;i++){
			cin>>c[i];
			for(int j=0,d;j<c[i];j++)cin>>d,ind[d]=i;
		} // input
		
		int l=1,r=n,mx=query(1,n);
		while(l<r){
			int m=l+r>>1;
			if(query(l,m)==mx)r=m;
			else l=m+1;
		} // query index
		
		cout<<"? "<<n-c[ind[l]]<<" ";
		for(int i=1;i<=n;i++)if(ind[i]!=ind[l]||!ind[l])cout<<i<<" ";
		cout<<endl; // query notin S_mx
		
		int ans; cin>>ans; cout<<"! ";
		for(int i=1;i<=k;i++)cout<<(i==ind[l]?ans:mx)<<" ";
		cout<<endl; cin>>s;
	}
	return 0;
}
```

---

## 作者：Eibon (赞：3)

因为 $2^{12} > 1000$，所以联想到二分。

先询问全体求出最大值，再询问 $\lceil \log_{2}1000 \rceil=10$ 次。

因为要求 $\max v_{i}$，因为**这些子集两两的交集为空**，所以进行分讨，最大值要么在其中的一个子集中，要么不在任意一个子集中。

当最大值在其中的一个子集时，除了该子集，询问其他自己的答案都应当为最大值，而该子集的答案不妨再询问一次。

如果不在，也是一样的，可以将两种情况合并成一种。

总计询问正好为 $12$ 次。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;
int T,n,k,mx,num,ans,ans2;
int a[maxn],c[maxn],sc[maxn],sum[maxn];
string s;
void VIP(int l,int r)
{
	cout<<"? "<<r-l+1<<" ";
	for(int i=l;i<=r;i++){
		cout<<i<<" ";
	}
	cout<<endl;
}
void solve()
{
	cin>>T;
	while(T--){
		memset(sc,0,sizeof sc);
		cin>>n>>k;
		for(int i=1;i<=k;i++){
			cin>>sum[i];
			for(int j=1;j<=sum[i];j++){
				int x;
				cin>>x;
				sc[x]=i;
			}
		}
		int l=1,r=n;
		VIP(1,n);
		cin>>mx;
		while(l<=r){
			int mid=(l+r)>>1;
			VIP(l,mid);
			cin>>num;
			if(num==mx){
				ans=mid;
				r=mid-1;
			}
			else{
				l=mid+1;
			}
		}
		cout<<"? "<<n-sum[sc[ans]]<<" ";
		for(int i=1;i<=n;i++){
			if(sc[i]!=sc[ans]||!sc[ans]){
				cout<<i<<" ";
			}
		}
		cout<<endl;
		cin>>ans2;
		cout<<"! ";
		for(int i=1;i<=k;i++){
			if(i==sc[ans]){
				cout<<ans2<<" ";
			}
			else{
				cout<<mx<<" ";
			}
		}
		cout<<endl;
		cin>>s;
	}
}
signed main()
{
	solve();
    return 0;
}
//dyyyyds
```

---

## 作者：Meatherm (赞：2)

看了官方题解之后来写一下题解吧。


设 $a=[1,2,3,4,6,5]$。有 $5$ 个子集，第一个子集是 $\{1,2\}$，第二个子集是 $\{3\}$，第三个子集是 $\{4\}$，第四个子集是 $\{5\}$，第五个子集是 $\{6\}$（集合中的元素代表**下标**）。

首先一遍查询全局最大值，得到 $6$。

然后我们判断这个最大值在哪个子集里，可以二分来实现：

- 查询子集 $1$ 到 $3$ 的最大元素，是 $4$ —— 最大值不在这几个子集中
- 查询子集 $4$ 到 $5$ 的最大元素，是 $6$ —— 最大值在这几个子集中
- 查询子集 $4$ 的最大元素，是 $6$


至此，我们找到了全局最大值所属的子集 $4$。容易发现该步骤的复杂度是 $O(\log_2 k)$，当 $k$ 取最大值 $1000$ 时，需要 $10$ 次查询。

因为这些子集互不相交，容易发现，对于不包含全局最大值的子集，答案就是全局最大值。

而对于包含全局最大值的那个子集，需要额外的一次查询，才能求出答案。

需要注意的情况是，题目并没有保证所有子集的并大小为 $n$，所以会出现全局最大值**不在任何一个子集中**的情况。但在代码实现中，几乎没有影响。

$\text{Idleness~limit~exceeded}$ 的同学可以对照着检查一下自己的 `fflush` 是否用够了。

```cpp
# include <bits/stdc++.h>
# define rr
const int N=1010,INF=0x3f3f3f3f;
std::vector <int> S[N];
int n,k;
int T;
bool use[N];
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
inline int query(int l,int r){ // 询问子集 l~r
	int ans=0;
	for(rr int i=l;i<=r;++i){
		ans+=(int)(S[i].size());
	}
	printf("? %d ",ans);
	for(rr int i=l;i<=r;++i){
		for(rr int j=0;j<(int)(S[i].size());++j){
			printf("%d ",S[i][j]);
		}
	}
	puts("");
	fflush(stdout);
	return read();
}
int main(void){
	T=read();
	while(T--){
		n=read(),k=read();
		for(rr int i=1;i<=k;++i){
			S[i].resize(read());
			for(rr int j=0;j<(int)S[i].size();++j){
				S[i][j]=read();
			}
		}
		int all_max; // 查询全局最大值
		printf("? %d ",n);
		for(rr int i=1;i<=n;++i){
			printf("%d ",i);
		}
		puts("");
		fflush(stdout);
		all_max=read();
		int l=1,r=k;
		while(l<r){ // 二分查询全局最大值所属的子集
			int mid=(l+r)>>1;
			if(query(l,mid)==all_max){
				r=mid;
			}else{
				l=mid+1;
			}
		}
		int max_ans;
		int x=l;
		int cnt=n-S[x].size();
		memset(use,false,sizeof(use));
		printf("? %d ",cnt); // 额外的一次查询
		for(rr int i=0;i<(int)S[x].size();++i){
			use[S[x][i]]=true;
		}
		for(rr int i=1;i<=n;++i){
			if(!use[i]){
				printf("%d ",i);
			}
		}
		puts("");
		fflush(stdout);
		max_ans=read();
		printf("! ");
		for(rr int i=1;i<=k;++i){
			if(i==x){
				printf("%d ",max_ans);
			}else{
				printf("%d ",all_max);
			}
		}
		puts("");
		fflush(stdout);
		std::string ans;
		std::cin>>ans;
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：lgx57 (赞：0)

简单交互题。

从询问次数 $\le 12$ 就可以看出是二分。

注意到 $S_1,S_2,\cdots S_k$ 互不相交，所以其中正好有一个子集包含整个序列的最大值（如果有多个最大值，我们就假定其中一个为最大的数）。

我们可以在 $a$ 上二分最大值的位置，这个操作需要 $\lceil \log_2 n \rceil+1=11$ 次询问来完成。

我们设二分出来最大值的位置为 $pos$，那么对于任意的子集 $S_i$，如果它包含了 $pos$，那么对它单独进行一次询问。否则，它的答案就是 $a$ 的最大值。

这样，我们就可以在 $11+1=12$ 次询问内解决这个问题，可以通过本题。

注意每一组结束后要读入一个字符串。

[code](https://codeforces.com/contest/1363/submission/288437503)

---

## 作者：_sunkuangzheng_ (赞：0)

$\textbf{1.1 Hint}$

- $\textbf{1.1.1 Hint 1}$

设最大值的位置是 $p$，当 $p \notin S$ 时，$S$ 的答案是多少？

- $\textbf{1.1.2 Hint 2}$

在 $\log_2 n + 1$ 次询问内找到 $p$ 的值。

- $\textbf{1.1.3 Hint 3}$

所有 $a_i$ 互不相同，所有子集互不相交，$1$ 次询问足够问出 $p \in S$ 的集合 $S$ 的答案。

$\textbf{1.2 Solution}$

如 $\text{Hint 2}$，我们需要先用 $\log_2 n+1$ 次询问得到 $p$ 的值，可以采用分治或二分完成。当 $p \notin S$ 时，答案显然是最大值。

然后我们找到唯一一个包含 $p$ 的集合 $S$，用 $1$ 次询问得到这个集合的答案，即可解决问题。

下面的代码使用的是分治法。

$\textbf{1.3 Code}$

```cpp
/**
 *    author: sunkuangzheng
 *    created: 04.10.2023 20:26:12
**/
#include<bits/stdc++.h>
using namespace std;
int t,n,k,c,a[500005],x,p,f,y;string s;
int ask(int l,int r){
    cout << "? " << r - l + 1 << " ";
    for(int i = l;i <= r;i ++) cout << i << " ";cout << endl;
    cin >> y;return y;
}int solve(int l,int r){
    if(l == r) return l;
    int mid = (l + r) / 2;
    if(ask(l,mid) == p) return solve(l,mid); return solve(mid+1,r);
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t --){
        cin >> n >> k;
        for(int i = 1;i <= n;i ++) a[i] = 0;
        for(int i = 1;i <= k;i ++){
            cin >> c;
            for(int j = 1;j <= c;j ++) cin >> x,a[x] = i;
        }p = ask(1,n),f = solve(1,n);vector<int> acc;
        for(int i = 1;i <= n;i ++) if(a[i] != a[f]) acc.push_back(i);
        cout << "? " << acc.size() << " ";
        for(int i : acc) cout << i << " ";cout << endl;
        cin >> y;cout << "! ";
        for(int i = 1;i <= k;i ++) cout << (i == a[f] ? y : p) << " ";cout << endl;cin >> s;
    }
}
```

---

## 作者：离散小波变换° (赞：0)

很有趣，就是不是很有趣。

## 题解

首先发现如果题设所给的集合还有一些数字没选上，我们总是可以将剩下来的数字放在另外一个集合内。根据「题必有解」定理，因为数据完全可以这样多问你一个区间，所以这么做不会使得这道题目变得无解。

注意到我们回答答案时是以每个集合作为单位的，有个想法就是将一个集合内的所有点浓缩成一个点。因为询问的时候返回的是最大值，所以就想着把每个集合合并成它里面的最大值吧。询问一些「点」的最大值就是询问对应集合的并集的最大值。

问题就被简化成了，有 $k+1$ 个点 $w_1,w_2,w_3,\cdots,w_{k+1}$，你需要对于每个 $i$ 求出 $\max \{w_1,w_2,\cdots,w_{i-1},w_{i+1},\cdots,w_{k},w_{k+1}\}$。

容易注意到：

- 如果某个数不是序列的最大值，那么对于它而言答案总是整个序列的最大值；
- 如果多个数都是序列的最大值，那么对于它而言答案也是整个序列的最大值；
- 如果仅有一个数是序列的最大值，那么对于它而言答案就是序列的次大值。

那么我们先通过一次询问求出整个序列的最大值 $m$，再通过二分随便找一个最大值的位置 $w_f=m$。然后通过一次询问 $w_f$ 以外的数字的最大值来确定 $w_f$ 是不是唯一的最大值。

总询问次数是 $1+\lceil \log_2 1000\rceil+1=12$，刚好符合题目要求。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MAXN= 1e3 + 3;
int C[MAXN]; vector <int> V[MAXN]; bool F[MAXN];
int query(vector <int> &X){
    int s = 0, w = 0;
    for(auto &x : X) s += V[x].size();   cout << "? " << s;
    for(auto &x : X) for(auto &y : V[x]) cout << " "  << y;
    cout << endl; cin >> w;
    return w;
}
int main(){
    int T; cin >> T;
    up(1, T, _){
        int n, k;
        cin >> n >> k;
        up(1, k, i){
            cin >> C[i];
            up(1, C[i], j){
                int a; cin >> a; V[i].push_back(a), F[a] = true;
            }
        }
        ++ k;
        up(1, n, i) if(!F[i]) V[k].push_back(i);
        vector <int> X0;
        vector <int> X1;
        up(1, k, i) X0.push_back(i);
        int ans = 0, m = query(X0);
        dn(9, 0, i){
            int p = ans | 1 << i;  if(p >= k) continue;
            vector <int> X; up(1, p, j) X.push_back(j);
            if(query(X) != m) ans = p;
        }
        ++ ans;
        up(1, k, i) if(i != ans) X1.push_back(i);
        int t = query(X1);
        cout << "!";
        up(1, k - 1, i){
            if(i == ans) cout << " " << t;
                else     cout << " " << m;
        }
        cout << endl;
        string result; cin >> result;
        up(1, k, i) V[i].clear();
        up(1, n, i) F[i] = false;
    }
    return 0;
}
```

---

## 作者：_edge_ (赞：0)

首先，询问次数非常少，提示我们需要某些神奇的，最好是 $\log$ 级别的算法。

不难想到 $2^{10}>1000$ 因此，我们需要一个二分。

那么，二分啥呢？于是我们闲着没事去二分全局的最大值。

最大值找出来之后，如果说一个子集没有包含这个最大值，那么这个子集的答案就是最大值。

如果不是呢？那就询问除去这个子集的最大值。

因为每两个子集都不会有交，因此上述子集出现次数只有 $1$ 次，所有暴力询问次数是不会超的。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring> //233333
using namespace std;
const int INF=1e3+5;
int num[INF],cnt[INF][INF],n,k,t,p[INF],vis[INF];
int check(int l,int r) {
	cout<<"? ";
	cout<<r-l+1<<" ";
	for (int i=l;i<=r;i++)
		cout<<i<<" ";
	cout<<"\n";
	cout.flush();
	int x=0;
	cin>>x;
	return x;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	while (t--) {
		memset(vis,0,sizeof vis);
		cin>>n>>k;
		for (int i=1;i<=k;i++) {
			cin>>num[i];
			for (int j=1;j<=num[i];j++)
				cin>>cnt[i][j];
		}
		int l=1,r=n,ans=-1;
		int la=check(l,r);
		while (l<=r) {
			int Mid=(l+r)>>1;
			if (check(Mid,r)==la) l=(ans=Mid)+1;
			else r=Mid-1;
		}
//		cout<<" over?\n";
		// ans
		for (int i=1;i<=k;i++) {
			int fl=0;
			for (int j=1;j<=num[i];j++) {
				if (cnt[i][j]==ans) fl=1;
			}
			if (!fl) p[i]=la;
			else {
				int sum=0;
				for (int j=1;j<=num[i];j++) vis[cnt[i][j]]=1;
				for (int j=1;j<=n;j++) if (vis[j]==0) sum++;
				cout<<"? ";cout<<sum<<" ";
				for (int j=1;j<=n;j++) if (vis[j]==0) {cout<<j<<" ";}
				cout<<"\n";
				cout.flush();int kk=0;cin>>kk;
				p[i]=kk;
			}
		}
		cout<<"! ";
		for (int i=1;i<=k;i++)
			cout<<p[i]<<" ";
		cout<<"\n";
		cout.flush();
		string s1;cin>>s1;
	}
	return 0;
}
```


---

## 作者：Fan_sheng (赞：0)

其实是道蛮简单的题。


------------


## 思路


首先是发现各子集**交集为空**，这也就意味着每个元素最多只会出现在一个子集里，那么就很好做了。

记数组 $a$ 中元素最大值对应下标为 $pos$，并且属于子集 $S_i$；

Case 1：对于 $j\neq i$，子集 $S_j$ 的答案都是 $a[pos]$，因为这些集合都不包含下标 $pos$，去掉 $S_j$ 包含的下标后不影响 $a[pos]$ 的最大值地位；

Case 2：对于 $S_i$ 而言，$a[pos]$ 需要被排除，直接询问所有不属于 $S_i$ 的坐标就可以了，只花费一次询问。






## 实现


注意到 $12$ 次这个数据很怪，这种东西一般可以往 $\log$ 上面去靠，发现 $n$ 最大时，$12=\lceil \log_2 n \rceil+1+1$。

Case 2 很简单，这里仅讨论 Case 1 的做法。

对于 Case 1，我们可以二分来寻找 $pos$，先询问整个数组的最大值 $mx$。

将数组从中间分为两段区间 $[l,mid]$ 和 $[mid+1,r]$，如果询问到 $[l,mid]$ 上的最大值等于 $mx$，那么就将 $[l,mid]$ 再二分接着找；

如果不是，$pos$ 一定在 $[mid+1,r]$ 区间上，**不用再次询问 $[mid+1,r]$ 的最大值**，直接将 $[mid+1,r]$ 二分寻找。

这样一直查找到区间只剩下一个值为 $mx$ 的元素，就可以确定该位置为 $pos$ ，耗费询问次数 $\lceil \log_2 n \rceil$。

可以知道，就算 $[l,mid]$ 和 $[mid+1,r]$ 上都有元素值等于 $mx$，也不妨碍答案正确性。





## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,c[1003][1003],mx,pos,tmp,belong[1003];
char s[10];
void find_pos(int l,int r,bool skip){
	if(pos>=0)return;
        int get,mid=(l+r)>>1;
	if(!skip){
		printf("? %d ",r-l+1);
	    for(int i=l;i<=r;i++)printf("%d ",i);
        printf("\n");fflush(stdout);
	    scanf("%d",&get);
	}
	else get=mx;
	if(l==1&&r==n){
		mx=get;find_pos(l,mid,0);find_pos(mid+1,r,1);
	}
	else{
		if(mx==get){
			if(l==r)pos=l;
			find_pos(l,mid,0);find_pos(mid+1,r,1);
		}
		else return;
	}
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);mx=pos=-1;
        memset(belong,0,sizeof(belong));
		for(int i=1;i<=k;i++){
			scanf("%d",&c[i][0]);
			for(int j=1;j<=c[i][0];j++){
				scanf("%d",&c[i][j]);belong[c[i][j]]=i;
			}
		}
		find_pos(1,n,0);
		printf("? %d ",n-c[belong[pos]][0]);
		for(int i=1;i<=n;i++)if(!belong[i]||belong[i]!=belong[pos])printf("%d ",i);
        printf("\n");fflush(stdout);scanf("%d",&tmp);
		printf("! ");
		for(int i=1;i<=k;i++)printf("%d ",(i==belong[pos])?tmp:mx);
        printf("\n");fflush(stdout);scanf("%s",s);
	}
	return 0;
}
```



---

