# Brukhovich and Exams

## 题目描述

The boy Smilo is learning algorithms with a teacher named Brukhovich.

Over the course of the year, Brukhovich will administer $ n $ exams. For each exam, its difficulty $ a_i $ is known, which is a non-negative integer.

Smilo doesn't like when the greatest common divisor of the difficulties of two consecutive exams is equal to $ 1 $ . Therefore, he considers the sadness of the academic year to be the number of such pairs of exams. More formally, the sadness is the number of indices $ i $ ( $ 1 \leq i \leq n - 1 $ ) such that $ gcd(a_i, a_{i+1}) = 1 $ , where $ gcd(x, y) $ is the greatest common divisor of integers $ x $ and $ y $ .

Brukhovich wants to minimize the sadness of the year of Smilo. To do this, he can set the difficulty of any exam to $ 0 $ . However, Brukhovich doesn't want to make his students' lives too easy. Therefore, he will perform this action no more than $ k $ times.

Help Smilo determine the minimum sadness that Brukhovich can achieve if he performs no more than $ k $ operations.

As a reminder, the greatest common divisor (GCD) of two non-negative integers $ x $ and $ y $ is the maximum integer that is a divisor of both $ x $ and $ y $ and is denoted as $ gcd(x, y) $ . In particular, $ gcd(x, 0) = gcd(0, x) = x $ for any non-negative integer $ x $ .

## 说明/提示

In the first test case, a sadness of $ 1 $ can be achieved. To this, you can simplify the second and fourth exams. After this, there will be only one pair of adjacent exams with a greatest common divisor (GCD) equal to one, which is the first and second exams.

In the second test case, a sadness of $ 0 $ can be achieved by simplifying the second and fourth exams.

## 样例 #1

### 输入

```
9
5 2
1 3 5 7 9
5 2
3 5 7 9 11
8 2
17 15 10 1 1 5 14 8
5 3
1 1 1 1 1
5 5
1 1 1 1 1
19 7
1 1 2 3 4 5 5 6 6 7 8 9 10 1 1 1 2 3 1
15 6
2 1 1 1 1 2 1 1 2 1 1 1 2 1 2
5 2
1 1 1 1 2
5 2
1 0 1 0 1```

### 输出

```
1
0
2
2
0
5
5
2
1```

# 题解

## 作者：未来姚班zyl (赞：2)

#### 前记（没必要看，属于博客内容）

第二次 VP div.2，直接跟同学合体打，我打 BDF，他打 ACE，结果我半小时就做完了，一起死磕 E，结果我们都想到正解，但都 WA on test 2。结果我发现是一个地方判错了，一改就过了，两个人都不能 rk20，烂完了。

## 题目大意

有一个长度为 $1$ 的序列 $a$。你可以使得 $k$ 个数变成 $0$，最小化相邻两个数的最大公约数为 $1$ 的总对数。特别的，$\gcd(x,0)=x$。

## 题目分析

显然的一个结论，修改一个数最多能将答案减二，这是做这道题的前提。

注意到 $1$ 在这道题看起来很烦，因为 $\gcd(1,x)=1$。

不妨先把一次能减少两对的先给操作了，这肯定优。

这些数的左右两边肯定都大于 $1$。所以剩下的大于 $1$ 的数肯定做不到一次减少两对。

这一步我们漏了一种可以一次减少两对的情况，那就是对于一段极长的连续的 $1$（两边还有数），设其长度为 $len$，如果把它们全都删去，对数能减少 $len+1$。显然，我们剩下的 $k$ 要尽量先把这种情况消除了。用优先队列记录即可。

剩下的数顶多删一个少一对。这时候也就只剩两边连续的 $1$ 和中间零散的对数了。对于两边连续的 $1$ 一定要从内往外删，否则除非全删完，就会有一次没减少任何一对。剩下的由于是零散的，直接扫过去就够了。

思维还很顺畅的，2500 有点水了，可能是代码细节有亿点多。

复杂度 $O(n\log n)$，瓶颈在求最大公约数。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =5e5+5,M=5e6+5,inf=(1LL<<31)-1;
const ll llf=1e18,mod=1e9+7;
using namespace std;
int T=read(),k,n,a[N]; 
inline int gcd(int x,int y){
	if(!x||!y)return x|y;
	return gcd(y,x%y);
}
bool f[N];
int s[N],tp,ln[N];
struct node{
	int x,k;
	bool friend operator<(node a,node b){
		return a.k>b.k;
	}
};
signed main(){
	while(T--){
		n=read(),k=read();
		rep(i,1,n)a[i]=read();
		int ans=0;
		rep(i,1,n-1)f[i]=(gcd(a[i],a[i+1])==1),ans+=f[i];
		rep(i,2,n-1)if(k){
			if(f[i]&&f[i-1]&&a[i-1]!=1&&a[i+1]!=1){
				k--,a[i]=0,f[i-1]=f[i]=0;
				ans-=2;
			}
		}
		if(!k){
			cout <<ans<<endl;
			continue;
		}
		bool fl=(a[1]==1),fr=(a[n]==1);
		int kl=0,kr=0;
		if(fl){
			kl++;
			while(kl<=n-1&&a[kl+1]==1)kl++;
		}
		if(kl==n){
			if(k==n){
				cout <<0<<endl;
			}else cout <<(n-k)<<endl;
			continue;
		}
		if(fr){
			kr++;
			int r=n;
			while(r>1&&a[r-1]==1)r--,kr++;
		}
		int Ll=kl+2,Rr=n-kr-1;
		int len=0;tp=0;
		rep(i,Ll,Rr){
			if(a[i]==1){
				if(!len)s[++tp]=i,ln[tp]=1,len=1;
				else len++,ln[tp]++;
			} 
			else len=0;
		}
		priority_queue<node>q;
		rep(i,1,tp)q.push({s[i],ln[i]});
		while(!q.empty()){
			if(!k)break;
			int x=q.top().x,len=q.top().k;
			q.pop();
			
			rep(i,x,x+len-1){
				k--;
				a[i]=0;
				if(!k)break;
			}
		}
		per(i,kl,1)if(k){
			a[i]=0,k--;
		}
		rep(i,n-kr+1,n)if(k)a[i]=0,k--;
		rep(i,1,n-1)if(k){
			if(gcd(a[i],a[i+1])==1)a[i]=0,k--;
		}
		ans=0;
		rep(i,1,n-1)ans+=gcd(a[i],a[i+1])==1;
		cout <<ans<<endl;
	}
	return 0;
}
```


---

## 作者：D2T1 (赞：1)

# 【题解】CF1891E - Brukhovich and Exams

<https://www.luogu.com.cn/problem/CF1891E>

我们考虑把区间分段：若两个相邻的数不互素，中间分开；若两个相邻的数中有且仅有一个 $1$，中间分开。那么我们得到了两种区间：全 $1$ 区间与无 $1$ 区间。若两个相邻数在同一区间内，那么就在区间内考虑；否则在两个区间的交点处，归到旁边的全 $1$ 区间考虑；若旁边两个区间都是无 $1$ 区间，那么这两个数一定不互素，不用考虑。

首先考虑无 $1$ 区间：设长度为 $len$，则有 $len-1$ 对相邻数。显然可以先通过 $\lfloor \dfrac{len-1}2\rfloor$ 次操作，每次答案减少 $2$，然后可能还剩一个，使用一次操作使得答案减少 $1$。

接着考虑全 $1$ 区间：设长度为 $len$，分三类讨论。

- 如果两端都非 $1$ 或 $n$，那么有 $len+1$ 对相邻数。可以通过 $len-1$ 次操作每次答案减少 $1$，最后一次操作答案减少 $2$。
- 如果有一段为 $1$ 或 $n$，那么从更靠中间的点的那端开始，$len$ 次操作每次答案减少 $1$。
- 否则就是 $1\sim n$ 全部都是 $1$，易得答案是 $n-k$，特判即可。

然后现在会有若干种操作：减 $2$，先减若干次 $1$ 最后减一次 $2$，减 $1$。

贪心地操作即可。

```cpp
//CF1891E
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int T, n, k, a[N], ot[N], ans[N];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &k);
		bool flg = true;
		for(int i = 1; i <= n; ++ i){
			scanf("%d", &a[i]);
			if(a[i] != 1){
				flg = false;
			}
		}
		if(flg){
			printf("%d\n", n - k);
			continue;
		}
		int le = 1, two = 0, one = 0, tp = 0;
		ans[0] = 0;
		for(int i = 1; i <= n; ++ i){
			if(i != 1 && __gcd(a[i-1], a[i]) == 1){
				++ ans[0];
			}
			if(a[i] == 1 && a[i+1] != 1){
				int len = i - le + 1;
				if(le == 1 || i == n){
					one += len;
				} else {
					ot[++tp] = len;
				}
				le = i + 1;
			} else if(__gcd(a[i], a[i+1]) != 1 || (a[i+1] == 1 && a[i] != 1)){
				int len = i - le;
				two += len / 2;
				one += len % 2;
				le = i + 1;
			}
		}
		sort(ot + 1, ot + tp + 1);
		for(int i = 1; i <= two; ++ i){
			ans[i] = ans[i-1] - 2;
		}
		int ps = two;
		for(int i = 1; i <= tp; ++ i){
			for(int j = 1; j < ot[i]; ++ j){
				ans[ps+1] = ans[ps] - 1;
				++ ps;
			}
			ans[ps+1] = ans[ps] - 2;
			++ ps;
		}
		for(int i = 1; i <= one; ++ i){
			ans[ps+i] = ans[ps+i-1] - 1;
		}
		printf("%d\n", ans[k]);
		for(int i = 0; i <= n; ++ i){
			ans[i] = 0;
			ot[i] = 0;
			a[i] = 0;
		}
	}
	return 0;
}
```

---

## 作者：EternityLove (赞：0)

## 题目描述：

给定一个长度为 $n$ 的非负整数序列 $a_i$。

你一共可以进行 $k$ 次操作，每次操作可以选择一个数 $i$，使得 $a_i$ 变成 $0$，你需要最小化 $S=\sum_{i=1}^{n-1}(\gcd(a_i,a_{i+1}))= 1$，输出最小的 $S$。

## 题解：

容易发现，每次操作至多减少 $2$ 个 $\gcd=1$ 的情况。

于是从左到右先扫描一遍，先将所有可以减少 $2$ 个 $\gcd=1$ 的情况的置为 $0$。

如果我们只考虑单次操作的贡献的话，那么我们此时应该考虑单次操作减少 $1$ 个 $\gcd=1$ 的情况。

但是有一种特殊的序列需要特殊处理一下，即一段连续的 $...111111...$，对于这样的一段连续的 $1$，我们容易注意到，对于 $x\overbrace{...111...}^{k}y$，其中 $x,y\not=1$，那么我们此时，可以将这 $k$ 个 $1$ 全部置 $0$，减少 $k+1$ 个 $\gcd=1$ 的情况。

容易注意到，如果这个连续的序列在开头或者结尾的位置，那么 $x,y$ 可能不存在，如 $\overbrace{1111...}^ky$，这个时候你从 $y$ 往左依次消除 $t$ 个 $1$，其中 $(t<=k)$，你可以消除掉 $t$ 个 $\gcd=1$ 的情况。请注意，一定要从 $y$ 的方向往左边消除，如果从左边往右边消除，那除非你消除了 $k$ 个$1$，即 $t=k$，否则你都只能减少 $t-1$ 个 $\gcd=1$ 的情况。对于 $x\overbrace{...111}$ 的情况类似。

处理完连续的 $1$ 的序列情况后，如果你还有操作机会，那就扫描一遍，把所有单次操作可以减少 $1$ 个 $\gcd=1$ 的情况置为 $0$ 即可。

### 代码：


~~~cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010

inline ll read() {
	char ch=getchar();ll ans=0,f=1;
	for (;!isdigit(ch);ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) ans=(ans<<3)+(ans<<1)+ch-'0';
	return ans*f;
}

struct Node{
	int l,r;
}node[N];

int a[N];

int gcd(int x,int y) {
	if (!y) return x;
	return gcd(y,x%y);
}

bool cmp(Node a,Node b) {
	return a.r-a.l<b.r-b.l;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t=read();
	while (t--) {
		int tot=0;
		int n=read(),k=read();
		for (int i = 1;i <= n;++ i) a[i]=read();
		a[0]=a[n+1]=0;
		for (int i = 2;i <= n-1;++ i) {
			if (k && gcd(a[i],a[i-1])==1 && gcd(a[i],a[i+1])==1 && a[i-1]!=1 && a[i+1]!=1) {
				a[i]=0;
				--k;
			} 
		}
		int lst=0;
		int e1=0;
		for (int i = 1;i <= n;++ i) {
			if (a[i]!=1) {
				if (lst>1) {
					node[++tot]={lst,i-1};
				} else if (lst==1) {
					e1=i-1;
				}
				lst=0;
			} else {
				if (lst) continue;
				lst=i;
			}
		}
		sort(node+1,node+tot+1,cmp);
		for (int i = 1;i <= tot;++ i) {
			if (!k) break;
			int len=node[i].r-node[i].l+1;
			if (k>=len) {
				for (int j = node[i].l;j <= node[i].r;++ j) --k,a[j]=0;
			} else {
				for (int j = node[i].l;k;++ j,-- k) a[j]=0;
			}
		}
		if (!lst) lst=n+1;
		for (int j = e1;j >= 1 && k;-- j,--k) a[j]=0;
		for (int j = lst;j <= n && k;++ j,-- k) a[j]=0;
		for (int i = 1;i <= n;++ i) {
			if (!k) break;
			if (k && (gcd(a[i],a[i-1])==1 && a[i-1]!=1 || gcd(a[i],a[i+1])==1 && a[i+1]!=1)) {
				a[i]=0;
				--k;
			}
		}
		int ans=0;
		for (int i = 1;i <= n-1;++ i) ans+=(gcd(a[i],a[i+1])==1);
		cout<<ans<<"\n";
	}
	return 0;
}
~~~



---

