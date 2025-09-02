# Martial Arts Tournament

## 题目描述

Monocarp is planning to host a martial arts tournament. There will be three divisions based on weight: lightweight, middleweight and heavyweight. The winner of each division will be determined by a single elimination system.

In particular, that implies that the number of participants in each division should be a power of two. Additionally, each division should have a non-zero amount of participants.

 $ n $ participants have registered for the tournament so far, the $ i $ -th of them weighs $ a_i $ . To split participants into divisions, Monocarp is going to establish two integer weight boundaries $ x $ and $ y $ ( $ x < y $ ).

All participants who weigh strictly less than $ x $ will be considered lightweight. All participants who weigh greater or equal to $ y $ will be considered heavyweight. The remaining participants will be considered middleweight.

It's possible that the distribution doesn't make the number of participants in each division a power of two. It can also lead to empty divisions. To fix the issues, Monocarp can invite an arbitrary number of participants to each division.

Note that Monocarp can't kick out any of the $ n $ participants who have already registered for the tournament.

However, he wants to invite as little extra participants as possible. Help Monocarp to choose $ x $ and $ y $ in such a way that the total amount of extra participants required is as small as possible. Output that amount.

## 说明/提示

In the first testcase of the example, Monocarp can choose $ x=2 $ and $ y=3 $ . Lightweight, middleweight and heavyweight divisions will have $ 2 $ , $ 1 $ and $ 1 $ participants, respectively. They all are powers of two, so no extra participants are required.

In the second testcase of the example, regardless of the choice of $ x $ and $ y $ , one division will have $ 1 $ participant, the rest will have $ 0 $ . Thus, Monocarp will have to invite $ 1 $ participant into both of the remaining divisions.

In the third testcase of the example, Monocarp can choose $ x=1 $ and $ y=2 $ . Lightweight, middleweight and heavyweight divisions will have $ 0 $ , $ 3 $ and $ 3 $ participants, respectively. So an extra participant is needed in each division.

In the fourth testcase of the example, Monocarp can choose $ x=8 $ and $ y=9 $ . Lightweight, middleweight and heavyweight divisions will have $ 8 $ , $ 0 $ and $ 0 $ participants, respectively. Middleweight and heavyweight division need an extra participant each.

## 样例 #1

### 输入

```
4
4
3 1 2 1
1
1
6
2 2 2 1 1 1
8
6 3 6 3 6 3 6 6```

### 输出

```
0
2
3
2```

# 题解

## 作者：dottle (赞：5)

求出 $f_i$ 代表如果要选出至多 $i$ 个最小的数，我们至多可以选出多少个数；$g_i$ 代表要选出最大的数。在 $2$ 的次幂中枚举 $i,j$ 作为第一、三段的长度，利用 $f$ 和 $g$ 求出第一三段中原先的选手的数量，从而计算第二段中原先选手的数量，进一步计算第二段的长度，加起来就是总长度，取最小的作为答案。注意求出的是总人数，所以还需要减去 $n$。

时间复杂度 $O(n)$，不会求 $f$ 和 $g$ 的建议直接参考代码。

```cpp
#include<bits/stdc++.h>
const int N=1000005;
using namespace std;
 
void solve(){
	int n;cin>>n;
	vector<int> a(n+1),f(n+1),g(n+1);
	for(int i=1;i<=n;i++){
		int x;cin>>x;a[x]++;
	}
	for(int i=1,s=0;i<=n;i++){
		for(int j=s;j<s+a[i];j++)f[j]=s;
		s+=a[i];
	}f[n]=n;
	for(int i=n,s=0;i;i--){
		for(int j=s;j<s+a[i];j++)g[j]=s;
		s+=a[i];
	}g[n]=n;
	int ans=1e9;
	for(int a=1;a<=n;a<<=1)	
		for(int b=1;b<=n;b<<=1){
			int x=f[a],y=g[b];
			int ac=1;while(ac<n-x-y)ac<<=1;
			ans=min(ans,a+b+ac);
		}
	cout<<ans-n<<endl;
}
 
main(){
	int _T=1;cin>>_T;
	while(_T--)solve();
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2100}$
---
### 解题思路：

直接通过枚举断点不好做，考虑从反面出发，枚举前两个组别的人数，然后贪心计算出最后一个组别需要的人数。

贪心策略是在已经确定了前两个个组别的人数之后，往这两个组里放尽可能多的人。假设将一种重量移出前两个组别，放到最后一个里，容易发现一定不可能出现最后一个组别的代价减少的情况，由此说明贪心是正确的。

实现的时候先用一个桶求出每一个值有多人，然后求前缀和。枚举出前两个组的人数之后通过二分查找找到能够放置的最大位置，直接计算出最后一个组需要多少人就行了。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define  int long long
int n,T,t[200005],x,f1[200005],f2[200005],ans,sum;
int calc(int num){
	int now=1;
	while(now<num)now*=2;
	return now;
}
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)t[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			t[x]++;
		}
		for(int i=1;i<=n;i++)
		t[i]+=t[i-1];
		ans=2147483647;
		for(int i=1;i<=n;i=i<<1){
			for(int j=1;j<=n;j=j<<1){
				int p1=upper_bound(t+1,t+n+1,i)-t;p1--;
				int p2=upper_bound(t+1,t+n+1,t[p1]+j)-t;p2--;
				ans=min(ans,i+j+calc(n-t[p2])-n);
			}
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：1)

## 思路

首先，现将 $n$ 人排序，然后我们考虑枚举从哪里将这些人断开。显然，这个做法是 $O(n^2\log n)$ 的。

这时，我们观察到选断开点的方案数很多，然而 $2^i$ 与 $i$ 的增长速度完全不是一个级别的。考虑到我们分出的一定是 $2^i$ 人，我们可以对于每一段枚举这个 $i$ 而不是断开的地方，然后二分答案查找即可。这样复杂度就可以最快优化到 $O(\log^3n)$。（当然比赛时我没有时间继续优化，写了一个 $O(\log^4n)$ 的算法，速度同样十分优秀）

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	cin.tie();
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+2];
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int b[n+2],k=0;
		sort(a+1,a+n+1);//排序，便于离散化
		b[0]=0;
		a[n+1]=998244353;
		for(int i=1;i<=n;i++){
			int j=i;
			while(a[i]==a[i+1]){
				i++;
			}
			k++;
			b[k]=i-j+1;
			b[k]+=b[k-1];//这一大段主要的作用是离散化
		}
		b[0]=0;
		b[k+1]=1145141919810;
		int minv=1145141919810;//赋边界，以防 RE 与 WA
		for(int i=0;i<=20;i++){
			for(int j=0;j<=20;j++){
				for(int ll=0;ll<=20;ll++){//枚举每一段长度
					int l=(1<<i);//计算长度
					int pos=upper_bound(b+1,b+k+2,l)-b-1;//二分查找最优
					int cha=l-b[pos];//计算差值，累加，后面两段类似
					int l2=(1<<j);
					int pos2=upper_bound(b+1,b+k+2,l2+b[pos])-b-1;
					cha+=(l2+b[pos]-b[pos2]);
					int l3=(1<<ll);
					int pos3=upper_bound(b+1,b+k+2,l3+b[pos2])-b-1;
					cha+=(l3+b[pos2]-b[pos3]);
					if(pos3==k){//注意，当且仅当可以取满才能比最优值
						minv=min(minv,cha);//更新最优解
					}
				}
			}
		}
		cout<<minv<<endl;
	}
	return 0;
}
/* things to check
1.  int overflow or long long memory need
2.  recursion/array/binary search/dp/loop bounds
3.  precision
4.  special cases(n=1,bounds)
5.  delete debug statements
6.  initialize(especially multi-tests)
7.  = or == , n or m ,++ or -- , i or j , > or >= , < or <= , - or =
8.  keep it simple and stupid
9.  do not delete, use // instead
10. operator priority
11. is there anything extra to output?
12. if you don't know where the bug is , try to clear some parts of the code
 and check each part seperately.
13. ...
*/

```

---

## 作者：AlicX (赞：0)

## Solution 

看到了好多 $O(\log^3 n)$ 的大佬做法，膜拜。

首先考虑枚举出第一个断点 $i$，此时如果继续枚举第二个断点的话无疑会超时，所以考虑枚举离第二段人数最近的 $2^j$，那么就可以二分找出断点，但是断点可以有很多个，我们该如何选择呢？ 最优的选择是选择最右边的点 $r$ 满足 $s_r-s_i \leq 2^j \land s_{r+1}-s_i > 2^j$。

因为我们会尽可能地填满第二段，而此时第三段的人数在不断减小，所以第三段的多付出的代价一定不会比第二段省去的代价多，也就是这样选一定是不劣的。

注意考虑某一段为空的情况，时间复杂度 $O(n \log^2n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2e5+10,M=20; 
int n; 
int b[N]; 
pii a[N]; 
int s[N]; 
il int get(int x){ 
	int id=0; 
	for(int j=0;j<M;j++){
		if(x==(1<<j)) return 0; 
		if(x>(1<<j)) id=j; 
	} return (1<<(id+1))-x; 
} 
il void solve(){ 
	int num=read(); n=0; 
	for(int i=1;i<=num;i++) b[i]=read(); 
	sort(b+1,b+num+1); int cnt=1; 
	for(int i=2;i<=num;i++){ 
		if(b[i]!=b[i-1]) a[++n]={b[i-1],cnt},cnt=1; 
		else cnt++; 
	} a[++n]={b[num],cnt}; 
	for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i].y; 
	int ans=get(num)+2; 
	for(int i=1;i<=n;i++){ 
		int res=get(s[i-1]); 
		ans=min(ans,res+get(s[n]-s[i-1])+1); 
		for(int j=0;j<M;j++){ 
			int sum=res; 
			int l=i,r=n,fg=0; 
			while(l<=r){ 
				int mid=l+r>>1; 
				if(s[mid]-s[i-1]<=(1<<j)) l=mid+1,fg=mid; 
				else r=mid-1; 
			} ans=min(ans,res+(1<<j)-(s[fg]-s[i-1])+get(s[n]-s[fg])); 
		} 
	} printf("%lld\n",ans); 
} 
signed main(){ 
	int T=read(); 
	while(T--) solve(); 
	return 0; 
} 
```

---

## 作者：徐天乾 (赞：0)

# 思路
先枚举两个数 $i$，$j$（均为 $2$ 的幂次）,分别表示权重小于 $x$ 的人数，权重大于等于 $y$ 的人数，之后我们可以知道权重大于等于 $x$、小于 $y$ 的人数至少有几个，又可以找到一个 $k$。$i$，$j$，$k$ 加起来取最小值就是最小的 $n+k$，再减去 $n$ 就是结果。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int i,j,k,n,T,l,r,L,R,x,mid,Min,a[200200];
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);Min=2e9; 
		for (i=1;i<=n;i++) a[i]=0;
		for (i=1;i<=n;i++) scanf("%d",&x),a[x]++;
		for (i=1;i<=n;i++) a[i]+=a[i-1];
		for (i=1;i<=n;i<<=1)
			for (j=1;j<=n;j<<=1){ //枚举i,j
				for (l=1,r=n,L=1;l<=r;){
					mid=(l+r)>>1;
					if (i>=a[mid]) l=L=mid+1;
					else r=mid-1;
				}
				for (l=1,r=n,R=n;l<=r;){
					mid=(l+r)>>1;
					if (j>=a[n]-a[mid-1]) r=R=mid-1;
					else l=mid+1; 
				} 
				for (k=1;k<a[R]-a[L-1];k<<=1) ; //a[R]-a[L-1]就是中间的人数
				Min=min(Min,i+j+k-n); //取最小值
			}
		printf("%d\n",Min);
	}
	return 0;
}
```


---

