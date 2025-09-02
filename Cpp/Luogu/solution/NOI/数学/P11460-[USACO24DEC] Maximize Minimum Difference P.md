# [USACO24DEC] Maximize Minimum Difference P

## 题目描述

**注意：本题的时间限制为 4 秒，通常限制的 2 倍。**

哞！你被给定了一个整数 $N$（$2\le N\le 2000$）。考虑 $[0,1,2\dots, N-1]$ 的所有排列 $p=[p_0,p_1,\dots, p_{N-1}]$。令 $f(p)=\min_{i=0}^{N-2}|p_i-p_{i+1}|$ 表示 $p$ 中任意两个连续元素之间的最小绝对差值，并令 $S$ 表示所有达到 $f(p)$ 最大可能值的 $p$ 的集合。

你还被给定了 $K$（$0\le K\le N$）个限制，形式为 $p_i=j$（$0\le i,j<N$）。计算 $S$ 中满足所有限制的排列数量，对 $10^9+7$ 取模。

## 说明/提示

样例 1 解释：

$f(p)$ 的最大值为 $2$，且 $S=\{[2,0,3,1], [1,3,0,2]\}$。

样例 2 解释：

$p=[5, 0, 6, 1, 7, 2, 9, 4, 10, 3, 8]$ 在所有测试用例中都应当被计算在内。


样例 3 解释：

$p=[4, 9, 3, 8, 2, 7, 0, 5, 10, 1, 6]$ 在所有测试用例中都应当被计算在内。

样例 4 解释：


确保输出答案对 $10^9+7$ 取模。

- 测试点 $5$：$N=15$。
- 测试点 $6$：$N=2000$。
- 测试点 $7\sim 9$：对于所有测试用例，均存在限制 $p_0=\lfloor N/2\rfloor$。
- 测试点 $10\sim 13$：对于所有测试用例，均存在某个限制 $p_i = j$，其中 $j$ 等于 $\lfloor N/2\rfloor$。
- 测试点 $14\sim 20$：没有额外限制。




## 样例 #1

### 输入

```
3 4
0
1
1 1
2
0 2
2 3```

### 输出

```
2
0
1```

## 样例 #2

### 输入

```
9 11
2
0 5
6 9
3
0 5
6 9
1 0
4
0 5
6 9
1 0
4 7
5
0 5
6 9
1 0
4 7
2 6
6
0 5
6 9
1 0
4 7
2 6
9 3
7
0 5
6 9
1 0
4 7
2 6
9 3
5 2
8
0 5
6 9
1 0
4 7
2 6
9 3
5 2
7 4
9
0 5
6 9
1 0
4 7
2 6
9 3
5 2
7 4
3 1
10
0 5
6 9
1 0
4 7
2 6
9 3
5 2
7 4
3 1
8 10```

### 输出

```
6
6
1
1
1
1
1
1
1```

## 样例 #3

### 输入

```
10 11
0
1
3 8
2
3 8
5 7
3
3 8
5 7
4 2
4
3 8
5 7
4 2
10 6
5
3 8
5 7
4 2
10 6
8 10
6
3 8
5 7
4 2
10 6
8 10
1 9
7
3 8
5 7
4 2
10 6
8 10
1 9
7 5
8
3 8
5 7
4 2
10 6
8 10
1 9
7 5
2 3
9
3 8
5 7
4 2
10 6
8 10
1 9
7 5
2 3
6 0```

### 输出

```
160
20
8
7
2
1
1
1
1
1```

## 样例 #4

### 输入

```
5 987
3
654 321
543 210
432 106
2
654 321
543 210
1
654 321
1
0 493
0```

### 输出

```
0
538184948
693625420
932738155
251798971```

# 题解

## 作者：qiuzx (赞：21)

最优的最小差值为 $\lfloor\frac n2\rfloor$，故下面只需要计算有多少个排列满足任意相邻两数之差不小于这个值即可。

若 $n$ 为偶数，则 $\frac n2$ 只能和 $0$ 相邻，故必须填在一个端点，且此时 $0$ 的位置被固定。然后发现 $\frac n2+1$ 只能和 $0/1$ 相邻，所以它必须挨着 $0$，以此类推可以确定所有点的位置。因此此时只有 $\frac n2$ 放在最前面和最后面两种情况，讨论一下即可。

下面考虑 $n$ 为奇数的情况，令 $m=\lfloor\frac n2\rfloor$。先假定 $m$ 的位置已经确定，且是第一个位置，则 $m$ 只能与 $0,n-1$ 相邻。不妨设 $m$ 旁边是 $0$。此时考察 $m+1$，这个数只能和 $0$ 或 $1$ 相邻，因此它只有两种可能性，要么放在一个端点处，要么放在 $0$ 的旁边。无论是哪一种情况，$1$ 都必须和它相邻，因此可以看作这两个点被捆为一组，一定是一起放置的。

以此类推可以发现，第 $i$ 次放置 $(m+i,i)$ 这一个点对，要么按照 $m+i,i$ 的顺序放在最开始的两个空位，要么按照 $i,m+i$ 的顺序放在最后的两个空位，这样一定是合法的，并且每一步也只有这两种选择。最后会剩下唯一一个空位放 $n-1$，这个位置也是合法的，故这样就可以算出总方案数。

下面考虑更一般的情形，即如果 $m$ 所处的位置前后都有偶数的空位。此时 $m$ 两侧有两个空位，故不妨设 $0$ 在 $m$ 左侧，$n-1$ 在 $m$ 右侧。此时 $(m+1,1)$ 这一组仍然可以放在端点处或 $0$ 旁边，但与刚刚不同的是，此时它不能放在右端点处。这是因为每一对相邻的点一定是一个 $<m$，一个 $>m$，所以固定了 $0,m,n-1$ 的位置之后，每个位置是要求 $<m$ 还是 $>m$ 已经被确定。可以发现在这种情况下，最后一个位置必须 $<m$，因此 $m+1$ 不能放在这个位置上，所以它只能放在左侧。

以此类推，在放完左侧的空位之前，每一对点都只能放在 $m$ 左侧这个区间的左右两个端点处。最后会剩下一个空位，此时只能是 $m+i$ 放在这个空位上，否则会导致后面不合法。然后后面这个部分可以看作是将所有值 $x$ 变成 $n-x-1$ 之后一个和左边完全相同的问题。所以只需要对两边分别计算方案数，而计算的方法和 $m$ 在开头的情形所使用的方法是一样的。

具体应该如何计算呢？有一些区间 dp 之类的方法，但难以优化到线性。考虑枚举区间中最后剩余空位的位置，则对于这个空位左边所有剩余的点，如果它的值已经被确定了，则和它同一组的点所处的位置也被确定了。并且可以得知的信息是“在放置这一组时，其左边已经被放了多少组数，右边已经被放了多少组数”。

于是现在的问题被转化为：有若干个数，每个数可以选择左右两个方向。还有若干个限制，每个限制形如“在前 $i$ 个数中，有 $a$ 个数选择了左边，$i-a$ 个数选择了右边，且第 $i$ 个球选择了做左/右边”。可以发现将所有限制按照 $i$ 排序后，一个数的选择只受到它前后的第一个限制，因此只需考虑每一对相邻的限制，计算同时满足它们时的方案数，并将这些方案数乘起来即可。而这个方案数是一个组合数，因此可以线性计算。

但直接实现还是需要枚举空位，复杂度 $O(n^2)$。不过可以发现这个空位的位置不影响最后所有限制的 $i$，而只会影响 $i$ 限制的内容。且如果从右往左扫描这个空位，那么一个 $i$ 的限制只会变动一次。因此可以动态维护所有相邻限制方案数的乘积，发生变动时除掉原来的方案数并乘上新的即可。这样复杂度就做到了 $O(n\log v)$（因为需要左除法）。实际上也可以 $O(n)$，只需预处理组合数的逆元即可，不过这个不重要。

因此如果 $m$ 前面有偶数个位置，就已经能在线性时间内解决了。下面考虑 $m$ 前面有奇数个位置的情形，同样不妨设 $0$ 在 $m$ 左侧而 $n-1$ 在右侧。类似于上一种情况，通过分析每个位置需要 $<m$ 还是 $>m$，可以发现每一组 $(m+i,i)$ 都一定要按照 $i,m+i$ 的顺序摆放，且要么放在 $m$ 左侧这个区间的最右边，要么放置 $m$ 右侧区间的最右边。因此这种情况的问题可以被看作类似于上一种情形中当区间空位的位置被固定之后需要解决的问题（即每组数可以选择左右两个区间之一，有若干限制给出前 $i$ 组数有几个在左边），直接组合数计算即可。

综上所述，先枚举 $m$ 的位置，再根据位置奇偶性分类讨论即可做到 $O(n^2)$。为了避免分类讨论，在上面不妨钦定 $0$ 在 $m$ 左侧，实际实现时对于 $n-1$ 在 $m$ 左侧的情况可以通过将每个值 $x$ 变成 $n-x-1$ 来转化为 $0$ 在 $m$ 左侧的情形，所以并不需要进行分类讨论。

赛时代码（由于是从暴力改过来的，写的非常混乱，仅供参考）

``` c++
#include <bits/stdc++.h>
#define INF 1000000000
#define LINF 1000000000000000000
#define mod 1000000007
#define F first
#define S second
#define ll long long
#define N 2010
using namespace std;
int ksm(int x,int y){
	int ret=1;
	while(y>0){
		if(y&1) ret=(1ll*ret*x)%mod;
		x=(1ll*x*x)%mod;
		y>>=1;
	}
	return ret;
}
int n,m,p[N],q[N],C[N][N],ans,sz;
pair<int,pair<int,int> > seq[N];
bool check(vector<int> per){
	for(int i=0;i<n;i++) if(p[i]!=-1&&p[i]!=per[i]) return false;
	return true;
}
bool isok(int x,int y){
	if(p[x]!=-1&&p[x]!=y) return false;
	if(q[y]!=-1&&q[y]!=x) return false;
	return true;
}
int calc1(int mid){
	if(!isok(mid-1,0)) return 0;
	if(!isok(mid+1,n-1)) return 0;
	int ret=1;
	sz=0;
	for(int i=1;i<n/2;i++){
		if(q[i]==-1&&q[i+n/2]==-1) continue;
		if(q[i]!=-1){
			if(q[i]<mid&&(q[i]&1)) return 0;
			if(q[i]>mid&&(!(q[i]&1))) return 0;
		}
		if(q[i+n/2]!=-1){
			if(q[i+n/2]>mid&&(q[i+n/2]&1)) return 0;
			if(q[i+n/2]<mid&&(!(q[i+n/2]&1))) return 0;
		}
		if(q[i]!=-1){
			if(q[i+n/2]!=-1&&q[i+n/2]!=q[i]+1) return 0;
			if(q[i]<mid) seq[sz++]=make_pair(i,make_pair(0,(mid-q[i])/2));
			else seq[sz++]=make_pair(i,make_pair(1,(n-q[i])/2));
		}
		else{
			if(q[i+n/2]<mid) seq[sz++]=make_pair(i,make_pair(0,(mid-q[i+n/2]+1)/2));
			else seq[sz++]=make_pair(i,make_pair(1,(n-q[i+n/2]+1)/2));
		}
	}
	for(int i=0;i<=sz;i++){
		int sx,sy,tx,ty;
		sx=(i==0?0:(seq[i-1].S.F==0?seq[i-1].S.S:seq[i-1].F-seq[i-1].S.S));
		sy=(i==0?0:(seq[i-1].S.F==1?seq[i-1].S.S:seq[i-1].F-seq[i-1].S.S));
		tx=(i==sz?mid/2:(seq[i].S.F==0?seq[i].S.S-1:seq[i].F-seq[i].S.S));
		ty=(i==sz?(n-mid)/2-1:(seq[i].S.F==1?seq[i].S.S-1:seq[i].F-seq[i].S.S));
		if(tx<sx||ty<sy||sx<0||sy<0||tx<0||ty<0) return 0;
		ret=(1ll*ret*C[tx-sx+ty-sy][tx-sx])%mod;
	}
	return ret;
}
int val[N][2][2],num[N][2][2],bel[N],idx[N],seq0[N];
int getvl(int mid){
	if(mid==0) return 1;
	sz=0;
	for(int i=1;i<=(mid-1)/2;i++){
		if(q[i]!=-1){
			if(q[i]>mid) return 0;
			if(q[i]%2==0) return 0;
		}
		if(q[i+n/2]!=-1){
			if(q[i+n/2]>mid) return 0;
			if(q[i+n/2]&1) return 0;
		}
		if(q[i]!=-1||q[i+n/2]!=-1) seq0[sz++]=i;
	}
	for(int i=0;i<sz;i++) for(int c=0;c<2;c++){
		num[i][c][0]=-1,num[i][c][1]=-1;
		if(c==0){
			int x;
			if(q[seq0[i]]!=-1){
				if(q[seq0[i]+n/2]!=-1&&q[seq0[i]+n/2]!=q[seq0[i]]-1) continue;
				x=q[seq0[i]];
			}
			else x=q[seq0[i]+n/2]+1;
			num[i][0][0]=x/2+1,num[i][0][1]=seq0[i]-num[i][0][0];
		}
		else{
			int x;
			if(q[seq0[i]]!=-1){
				if(q[seq0[i]+n/2]!=-1&&q[seq0[i]+n/2]!=q[seq0[i]]+1) continue;
				x=q[seq0[i]];
			}
			else x=q[seq0[i]+n/2]-1;
			num[i][1][1]=(mid-x)/2,num[i][1][0]=seq0[i]-num[i][1][1];
		}
	}
	for(int i=0;i<sz;i++) for(int cx=0;cx<2;cx++) for(int cy=0;cy<2;cy++){
		val[i][cx][cy]=0;
		if(i==0&&cx) continue;
		if(i==sz&&cy) continue;
		int sx,sy,tx,ty;
		if(i==0) sx=sy=0;
		else sx=num[i-1][cx][0],sy=num[i-1][cx][1];
		tx=num[i][cy][0]-(cy==0),ty=num[i][cy][1]-(cy==1);
		if(tx>=sx&&ty>=sy&&sx>=0&&sy>=0&&tx>=0&&ty>=0) val[i][cx][cy]=C[tx-sx+ty-sy][tx-sx];
	}
	int num0=0,pro=1,ret=0;
	for(int i=0;i<sz;i++){
		idx[seq0[i]]=i;
		bel[i]=0;
		if(val[i][0][0]==0) num0++;
		else pro=(1ll*pro*val[i][0][0])%mod;
	}
	for(int i=mid-2;i>=0;i-=2){
		if(isok(i,n/2+mid/2)&&(!num0)){
			int sx=(sz==0?0:num[sz-1][bel[sz-1]][0]);
			int sy=(sz==0?0:num[sz-1][bel[sz-1]][1]);
			int tx=i/2,ty=(mid-i)/2-1;
			if(tx>=sx&&ty>=sy&&sx>=0&&sy>=0&&tx>=0&&ty>=0) ret=(1ll*ret+1ll*pro*C[tx-sx+ty-sy][tx-sx])%mod;
		}
		if(i==0) break;
		if(p[i]!=-1||p[i-1]!=-1){
			int x;
			if(p[i]!=-1&&p[i-1]!=-1){
				if(p[i]!=p[i-1]+n/2) break;
				x=p[i-1];
			}
			else if(p[i]!=-1) x=p[i]-n/2;
			else x=p[i-1];
			x=idx[x];
			if(bel[x]==0){
				if(val[x][x==0?0:bel[x-1]][bel[x]]==0) num0--;
				else pro=(1ll*pro*ksm(val[x][x==0?0:bel[x-1]][bel[x]],mod-2))%mod;
				if(x+1<sz){
					if(val[x+1][bel[x]][bel[x+1]]==0) num0--;
					else pro=(1ll*pro*ksm(val[x+1][bel[x]][bel[x+1]],mod-2))%mod;
				}
				bel[x]=1;
				if(val[x][x==0?0:bel[x-1]][bel[x]]==0) num0++;
				else pro=(1ll*pro*val[x][x==0?0:bel[x-1]][bel[x]])%mod;
				if(x+1<sz){
					if(val[x+1][bel[x]][bel[x+1]]==0) num0++;
					else pro=(1ll*pro*val[x+1][bel[x]][bel[x+1]])%mod;
				}
			}
		}
	}
	return ret;
}
int getvr(int mid){
	if(mid==n-1) return 1;
	vector<int> cur;
	for(int i=0;i<n;i++) cur.push_back(p[i]);
	reverse(p,p+n);
	for(int i=0;i<n;i++) if(p[i]>=0) p[i]=n-p[i]-1;
	for(int i=0;i<n;i++) q[i]=-1;
	for(int i=0;i<n;i++) if(p[i]>=0) q[p[i]]=i;
	int ret=getvl(n-mid-1);
	for(int i=0;i<n;i++) q[i]=-1;
	for(int i=0;i<n;i++){
		p[i]=cur[i];
		if(p[i]>=0) q[p[i]]=i;
	}
	return ret;
}
int calc2(int mid){
	if(mid&&(!isok(mid-1,0))) return 0;
	if(mid<n-1&&(!isok(mid+1,n-1))) return 0;
	return (1ll*getvl(mid)*getvr(mid))%mod;
}
void solve(){
	for(int i=0;i<n;i++) if(isok(i,n/2)) ans=(ans+(i&1?calc1(i):calc2(i)))%mod;
	return;
}
int main(){
	for(int i=0;i<N;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
	}
	int T;
	scanf("%d%d",&T,&n);
	while(T--){
		scanf("%d",&m);
		for(int i=0;i<n;i++) p[i]=q[i]=-1;
		for(int i=0;i<m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			p[x]=y,q[y]=x;
		}
		if(n%2==0){
			vector<int> per(n);
			for(int i=0;i<n;i++) per[i]=(i&1?0:n/2)+i/2;
			ans=0;
			if(check(per)) ans++;
			reverse(per.begin(),per.end());
			if(check(per)) ans++;
			printf("%d\n",ans);
			continue;
		}
		ans=0;
		solve();
		for(int i=0;i<n;i++) q[i]=-1;
		for(int i=0;i<n;i++) if(p[i]>=0) p[i]=n-p[i]-1,q[p[i]]=i;
		solve();
		printf("%d\n",ans);
	}
	return 0;
}

---

