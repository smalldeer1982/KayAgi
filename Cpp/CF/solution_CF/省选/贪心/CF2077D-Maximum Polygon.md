# Maximum Polygon

## 题目描述

给定一个长度为 $n$ 的数组 $a$，确定字典序最大的 $^{\text{∗}}$ 子序列 $^{\text{†}}$ $s$，使得 $s$ 可以作为多边形的边长。

当且仅当 $|s| \geq 3$ 且满足以下条件时，$s$ 可以作为多边形的边长：

$$ 2 \cdot \max(s_1, s_2, \ldots, s_{|s|}) < s_1 + s_2 + \ldots + s_{|s|}. $$

如果不存在这样的子序列 $s$，输出 $-1$。

$^{\text{∗}}$ 序列 $x$ 的字典序小于序列 $y$，当且仅当以下条件之一成立：
- $x$ 是 $y$ 的前缀，但 $x \neq y$；
- 在 $x$ 和 $y$ 第一个不同的位置，$x$ 的元素小于 $y$ 中对应的元素。

$^{\text{†}}$ 序列 $x$ 是序列 $y$ 的子序列，当且仅当 $x$ 可以通过从 $y$ 中删除若干（可能为零或全部）元素得到。

## 说明/提示

在第一个测试用例中，不存在可以作为多边形边长的子序列。

在第二个测试用例中，有两个可以作为多边形边长的子序列：$1, 4, 2, 3$ 和 $4, 2, 3$。后者是字典序更大的子序列。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
3
3 1 2
4
1 4 2 3
6
1 6 4 5 3 2
6
43 12 99 53 22 4
7
9 764 54 73 22 23 1```

### 输出

```
-1
3
4 2 3 
4
6 5 3 2 
5
43 99 53 22 4 
4
54 73 23 1```

# 题解

## 作者：未来姚班zyl (赞：4)

感觉 D 过的少可能都是把做法想难了导致的。榜歪了大概率是因为这题属于看了题解觉得很简单，但要有正确的思考方向却很困难的题。

这题有两个因素：多边形与字典序。

这题最大的坑就是如果你考虑枚举的是子序列的第一个位置，也就是优先考虑字典序，再验证能否组成多边形，这道题的讨论将会变得非常复杂，笔者就是因此在赛时没有想出清晰的做法。

更加简明的思路应该是从多边形的性质推出字典序的性质。

考虑最简单的情况：三角形。

如果三条边从小到大分别是 $A,B,C$，则只要 $A+B>C$ 就可以构造出一个解。

考虑 $a$ 从小到大后排序后的序列 $b$（也就是从值域上考虑）。

考虑 $b$ 的相邻位置 $b_i,b_{i+1},b_{i+2}$，则只需要 $b_i+b_{i+1}>b_{i+2}$，则 $b_i,b_{i+1},b_{i+2}$ 在原序列上的位置就是一种可能的子序列，其开头至少为 $b_i$。

所以我们从大到小枚举 $i$，一旦找到了一个满足条件的 $i$，则就可以找到一个答案的下界，使得第一个位置至少是 $b_i$。

我们的枚举量是 $O(\log V)$ 的，因为 $i$ 不合法当且仅当 $b_i+b_{i+1}\le b_{i+2}$，这是 $b_{i+2}\ge 2b_i$，所以 $b$ 的值会翻倍。事实上这个量级应该是斐波那契数列中 $\le V$ 的位置数量。

所以我们可以把选出子序列的第一个值 $w$ 控制在 $w\ge b_i$。

但我们依旧很难求出**字典序**最大的子序列。

这里我们要有一个**关键的思维跳跃**：子序列的最大值 $Max\ge b_i$。

这有什么用呢？答案是如果确定了最大值 $Max$，字典序最大的子序列就非常好求。

此时只需选择的数 $\le Max$，且选出的数的和 $S>2\times Max$。

考虑用从左往右扫描 $a$ 序列，维护当前选择的子序列 $s$。设当前扫到了 $i$，考虑加入 $a_i$。

我们肯定是要找到 $s$ 中一个最靠前的位置 $p$，使得：

- $a_i>s_p$
- 如果在 $s$ 中把 $p$ 与右边的位置全部删除，加上 $a_i\sim a_n$ 中的数依旧可以合法。

然后用 $a_i$ 剃掉 $s$ 中 $p$ 及后面的位置，并把 $a_i$ 加到 $s$ 的末尾。

这样我们每一步都能求出前缀 $i$ 的最大字典序子序列。

这个过程是 $O(n^2)$ 的，考虑优化。

找到 $s$ 中的第一个位置使得 $s_x<s_{x+1}$，此时说明 $s_{x+1}$ 无法剔除 $s_x$。

这时候我们发现，对于后面的位置 $y>a_{x+1}$，$a_{[y,n]}$ 的和肯定小于 $a_{[x+1,n]}$ 的和，$y$ 肯定无法剔除 $x$，更无法剔除 $x$ 之前的位置。所以这时 $s$ 的前 $x$ 位就已经确定了。

这样我们只用考虑 $s$ 的不增的后缀，用栈维护 $s$，每次尝试弹出末尾即可，复杂度 $O(n)$。

枚举的 $Max$ 只有 $O(\log V)$ 个，所以复杂度 $O(n\log V)$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
inline ll read(){ll s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N=2e5+5,inf=(1LL<<31)-1;
int n,a[N],Sum,b[N],lsh[N],ln;
vector<int>Ans,Now;
inline vector<int> Max(vector<int>A,vector<int>B){
	int n=A.size(),m=B.size();
	rep(i,0,min(n,m)-1)if(A[i]!=B[i]){
		if(A[i]>B[i])return A;
		return B;
	}
	if(n>m)return A;
	return B;
}
inline void sol(int &x){
	x=lower_bound(b+1,b+ln+1,x)-b;
}
int sf[N];
inline void Main(){
	n=read(),Ans.clear(),Ans.pb(-inf),ln=0;
	repn(i)a[i]=read(),lsh[i]=a[i];
	sort(lsh+1,lsh+n+1),lsh[n+1]=0;
	repn(i)if(lsh[i]!=lsh[i+1])b[++ln]=lsh[i];
	repn(i)sol(a[i]);
	per(Mx,ln,max(1LL,ln-32)){
		Now.clear();
		sf[n+1]=0;
		per(i,n,1)sf[i]=sf[i+1]+b[a[i]]*(a[i]<=Mx);
		if(sf[1]<=2*b[Mx])continue;
		Sum=0;
		repn(i)if(a[i]<=Mx){
			while(!Now.empty()){
				int w=Now.back();
				if(w>=b[a[i]])break;
				if(Sum-w+sf[i]>2*b[Mx])Now.pop_back(),Sum-=w;
				else break;
			}
			Now.pb(b[a[i]]),Sum+=b[a[i]];
		}
		Ans=Max(Ans,Now);
		
	}
	if(Ans[0]==-inf)return puts("-1"),void();
	cout <<(int)Ans.size()<<'\n';
	for(auto x:Ans)cout <<x<<" ";
	cout <<'\n';
}
signed main(){
	int T=read();
	while(T--)Main();
	return 0;
}
```

---

## 作者：ForgotMe (赞：2)

假设最大值一定会选，此时该怎么做？这时左侧固定，那么就是要求选出的所有数之和大于 $2mx$。要让字典序最大化，使用经典的贪心思路。假设上一个选的位置为 $pos$，已经选的数之和为 $sum$，那么二分找到最大的 $pos_1>pos$ 且 $suf_{pos_1}+sum>2mx$，其中 $suf_{i}$ 表示后缀和。那么下一个选的数就是 $[pos,pos_1]$ 的最大值，如果有多个选最靠前的一个，使用 st 表即可。

于是得到了一个 $\mathcal{O}(n^2\log n)$ 的做法，暴力枚举选出的所有数中的最大值然后跑上述算法即可。

实际上这个做法离正解只差一步，注意到当最大值不选时，所有大于 $\lfloor\frac{mx}{2}\rfloor$ 的数一定不选。证明是容易的，对于所有选了大于 $\lfloor\frac{mx}{2}\rfloor$ 的**合法方案**，选上最大值一定也是一个合法方案并且字典序更大！于是只需要跑 $\mathcal{\log_2 }V$ 轮，每次做完一遍后把大于 $\lfloor\frac{mx}{2}\rfloor$ 的数删除即可。

时间复杂度 $\mathcal{O}(n\log n\log V)$。

参考代码：https://www.luogu.com.cn/paste/2tcsisud

---

## 作者：Milthm (赞：1)

这题好啊。

这种带最大值的有一种可能做法是枚举最大值，考虑当前枚举的最大值是 $mx$，并且我们已经去除了原序列中大于 $mx$ 的元素。

现在我们要完成这样一个问题：

- 找到 $a$ 中满足子序列的和大于 $2mx$ 的字典序最大的子序列。

这个问题可以采用贪心解决，即一次一次地选数。假设我们上一次选的数是 $lst$，而且前面选的所有数的和为 $sum$，那么如果能选某个数 $a_i$，当且仅当 $i>lst$ 且**存在方案**使得在选 $i$ 情况下子序列和大于 $2mx$。贪心的思想处理这个存在方案很好处理，只需要假设把后面所有的数都选上。设后缀和为 $g_i$，那么只要满足 $i>lst$ 且 $sum+g_i>2mx$，$i$ 位置就可以被选。

注意到可选的 $i$ 位置是连续的（因为 $g_i$ 单调减）。所以我们可以二分出来最后一个满足条件的 $i$（设为 $now$），然后这次选的数就是 $[lst+1,now]$ 区间的最大值（如果有多个取前面的）。

这个问题可以用 ST 表做到 $O(n\log n)$，从而原问题的时间复杂度是 $O(n^2\log n)$，这是无法通过的。

这时候我们需要用到本题最难想到，也是最重要的性质了：

- 如果所有不小于 $mx$ 的数都不在子序列中，那么所有 $\lfloor \frac{mx}2 \rfloor <a_i <mx$ 都不能成为子序列的最大值。

证明：如果这样的 $a_i$ 选上了最大值，那么我们可以再选上 $mx$，这样题目给定的不等式中，左式增加的量不会超过 $mx$，而右式增加了 $mx$，故仍然满足条件。而且因为 $mx$ 已经比原来子序列的所有数大了，所以拿它替换一定比原来的子序列字典序更大，从而得出选这样的 $a_i$ 一定不优。

所以这题的正解就是，我们设原序列的最大值是 $mx$，每次钦定 $mx$ 为最大值跑刚才的贪心，然后删除 $\lfloor \frac{mx}2 \rfloor <a_i <mx$ 的元素，最后将 $mx$ 重新设定为剩余元素最大值，重复进行即可。时间复杂度 $O(n \log n \log V)$。


```cpp
#include<bits/stdc++.h>
#define pi pair<int,int>
#define int long long 
#define N 200005
using namespace std;
int T,n,a[N],f[N][21],id[N][21],g[N];
int query(int l,int r){
	int k=__lg(r-l+1);
	if(f[l][k]>=f[r-(1<<k)+1][k])return id[l][k];
	else return id[r-(1<<k)+1][k];
}
vector<int>solve(int mx,vector<int>a){
	g[n+1]=0;
	for(int i=n;i>=1;--i)g[i]=g[i+1]+a[i];
	for(int i=1;i<=n;++i)f[i][0]=a[i],id[i][0]=i;
	for(int j=1;j<=20;++j){
		for(int i=1;i+(1<<j-1)<=n;++i){
			if(f[i][j-1]>=f[i+(1<<j-1)][j-1])f[i][j]=f[i][j-1],id[i][j]=id[i][j-1];
			else f[i][j]=f[i+(1<<j-1)][j-1],id[i][j]=id[i+(1<<j-1)][j-1];
		}
	}
	vector<int>yy,noans;noans.push_back(-1);
	int lst=0,sum=0;
	while(lst<n){
		int l=lst+1,r=n,ans=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(g[mid]+sum>mx*2)ans=mid,l=mid+1;
			else r=mid-1;
		}
		if(ans==-1)return noans;
		lst=query(lst+1,ans);yy.push_back(a[lst]);sum+=a[lst];
	}
	return yy;
}
signed main(){
	cin>>T;
	while(T--){
		cin>>n;int maxn=0,x;
		vector<int>a,ans;a.push_back(0);
		for(int i=1;i<=n;++i)cin>>x,a.push_back(x),maxn=max(maxn,x);
		while(maxn){
			vector<int>now=solve(maxn,a);int f=1;
			if(now[0]!=-1){
				for(int i=0;i<min(ans.size(),now.size());++i){
					if(now[i]>ans[i]){
						ans=now;break;
					}
					if(now[i]<ans[i]){
						f=0;break;
					} 
				}
				if(now.size()>ans.size()&&f)ans=now;
			}
			vector<int>b;int qwq=0;
			for(int v:a)if(v<=maxn/2)b.push_back(v),qwq=max(qwq,v);
			a=b;n=a.size()-1;maxn=qwq;
		}
		if(!ans.size())cout<<"-1\n";
		else{
			cout<<ans.size()<<'\n';
			for(int v:ans)cout<<v<<" ";cout<<'\n';
		}
	}
	return 0;
}

```

---

