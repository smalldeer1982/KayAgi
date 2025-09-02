# k-Amazing Numbers

## 题目描述

You are given an array $ a $ consisting of $ n $ integers numbered from $ 1 $ to $ n $ .

Let's define the $ k $ -amazing number of the array as the minimum number that occurs in all of the subsegments of the array having length $ k $ (recall that a subsegment of $ a $ of length $ k $ is a contiguous part of $ a $ containing exactly $ k $ elements). If there is no integer occuring in all subsegments of length $ k $ for some value of $ k $ , then the $ k $ -amazing number is $ -1 $ .

For each $ k $ from $ 1 $ to $ n $ calculate the $ k $ -amazing number of the array $ a $ .

## 样例 #1

### 输入

```
3
5
1 2 3 4 5
5
4 4 4 4 2
6
1 3 1 5 3 1```

### 输出

```
-1 -1 3 2 1 
-1 4 4 4 2 
-1 -1 1 1 1 1```

# 题解

## 作者：STDquantum (赞：6)

可以发现一个性质（记为性质 $1$）：若一个数 $x$ 能出现在所有长度为 $k$ 的子区间内，则两个相同的 $x$ 之间的距离 $dis=j-i$ 不大于 $k$（包括最左边的 $x$ 到 $i=0$ 的距离和最右边的 $x$ 到 $i=n+1$ 的距离）。

然后我们还可以发现一个性质（记为性质 $2$）：如果一个数能出现在所有长度为 $k$ 的子区间内，则一定能出现在所有长度大于 $k$ 的子区间内。

所以我们有了一个思路：

计算出每个数两两之间的最大距离 $maxx$，然后用一个 $pos$ 数组（即所有 `k-Amazing Number`），在 $pos_{maxx}$ 的地方插入 $a_i$（与 $pos_{maxx}$ 取 $\min$），对应性质 $1$。

然后求一下 $pos$ 的前缀最小值（即 $pos_k=\displaystyle \min_{i=1}^kpos_i$），对应性质 $2$。

现在 $pos$ 数组中所存储的就是答案。

```cpp
inline void max(int &x, const int &y) { x = x < y ? y : x; }
inline void min(int &x, const int &y) { x = x > y ? y : x; }

const int N = 3e5 + 10, inf = 0x3f3f3f3f;
int t, n, a[N], las[N], maxx[N], pos[N];
inline void main() {
    for (read(t); t--;) {
        read(n);
        memset(las, 0, sizeof(las));
        memset(pos, 0x3f, sizeof(pos));
        memset(maxx, 0, sizeof(maxx));
        
        for (int i = 1; i <= n; ++i) {
            read(a[i]);
            max(maxx[a[i]], i - las[a[i]]);
            las[a[i]] = i;
        }
        for (int i = 1; i <= n; ++i) max(maxx[a[i]], n + 1 - las[a[i]]);
        for (int i = 1; i <= n; ++i) min(pos[maxx[a[i]]], a[i]);
        
        for (int i = 1; i <= n; ++i) {
            min(pos[i], pos[i - 1]);
            write(pos[i] == inf ? -1 : pos[i]), putchar(' ');
        }
        putchar('\n');
    }
}
```



---

## 作者：江户川·萝卜 (赞：1)

## [CF1416A k-Amazing Numbers](https://www.luogu.com.cn/problem/CF1416A) 题解

发现有一个性质：

假设在序列中有两个相同的数 $k_1,k_2$，它们的距离为 $l$，即：
$$k_1,\overbrace{...}^{l\text{个数}},k_2$$
只有当区间长度大于等于 $l+1$ 时，才能确保能够在不同的区间内都能包含 $k_1$ 或 $k_2$，如：
$$|k_1,\overbrace{...}^{l\text{个数}}|,k_2$$
$$k_1,|\overbrace{...}^{l\text{个数}},k_2|$$

拓展到在序列中有 $m$ 个相同的数 $a_i$，设它们的位置分别为 $d_i$，则区间长度要大于 $\max\{d_i-d_{i-1}\}$。

当然，还要要确保区间长度大于 $d_1$（不然第一个区间将会取不到 $a_i$），也要确保区间长度大于等于$d_m$到序列最后的距离（不然最后一个区间将会取不到 $a_i$ ）。

于是可以对于每一个数x，找到与它相等的数，然后根据上面做一次 $\max$，得到的值设为k，于是`k数`就更新为与k的最小值。

一个显然的结论：`k数`肯定包含在每一个长度为 $k+1$ 甚至更长的区间内。

所以最后输出时，若某一个`k数`没有被更新过，而`(k-i)数`被更新过，那么取 `(k-i)数`的值。

---
具体操作时，用pair分别记录值和下标，值升序和下标升序sort一遍，对于每一组相同的数做一遍上面的 $\max$。因为有多组数据，考虑到`memset`效率，所以用栈来代替`memset`。具体看代码。

~~（为了防止标题行过长删掉了头文件部分）~~

### Code
```cpp
int t,n;
typedef pair<int,int> pii;
pii p[300001];
int ans[300001];
stack<int> st;
inline bool cmp(pii x,pii y){
	return x.first<y.first||x.first==y.first&&x.second<y.second;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) scanf("%d",&p[i].first),p[i].second=i;
		sort(p+1,p+n+1,cmp);
		int lstp,maxl;
		lstp=p[1].second;maxl=lstp;
		for(int i=2;i<=n;i++){
			if(p[i].first==p[i-1].first){
				maxl=max(maxl,p[i].second-lstp);
				lstp=p[i].second;
			}
			else{
				maxl=max(maxl,n-lstp+1);
				if(!ans[maxl]){
					ans[maxl]=p[i-1].first;
					st.push(maxl);
				}
				lstp=p[i].second;maxl=lstp;
			}
		}
		maxl=max(maxl,n-lstp+1);
		if(!ans[maxl]){
			ans[maxl]=p[n].first;
			st.push(maxl);
		}
		int k=-1;
		for(int i=1;i<=n;i++){
			if(ans[i]&&(k==-1||k>ans[i])) k=ans[i];
			printf("%d ",k);
		}
		puts("");
		while(!st.empty()) ans[st.top()]=0,st.pop();
	}
	return 0;
}
```


---

## 作者：寒冰大大 (赞：1)

在寝室口胡了一个做法。

大意是找到出现在在每个长度为 $k$ 的区间的最小的数字， $k$ 从 $1$ 到 $n$

首先数字相同的下标放进一个 $\text{vector}$ 然后找到最大的差值，大于等于这个差值的区间可以用被这个数字贡献答案，我们放一个标记，先记录 $f[i]=min(f[i],t)$（ $t$ 即为数字 ） 

然后我们考虑转移，发现设为 $-1$ 太麻烦了，于是我们不妨设为极大值，此时转移方程即为 $f[i]=min(f[i-1],i)$

注意边界 ， $\text{vector}$ 先插入 $0$ 在放标记的时候再插入 $n+1$ 

```
#include<touwenjian.h>

using namespace std;

const int maxn=300300;

int f[maxn],n;

vector <int> v[maxn];

int main()
{
	ios::sync_with_stdio(false);
	register int i,j;
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		int tmp;
		f[0]=0x3f3f3f3f;
		for(i=1;i<=n;i++) v[i].push_back(0);
		for(i=1;i<=n;i++)
		{	
			f[i]=0x3f3f3f3f;
			cin>>tmp;
			v[tmp].push_back(i);
		}
		int deltammx=0;
		for(i=1;i<=n;i++)
		{
			v[i].push_back(n+1);
			deltammx=0;
			for(j=1;j<v[i].size();j++)
			deltammx=max(v[i][j]-v[i][j-1],deltammx);
			if(v[i].size()!=2) 
			{
				f[deltammx]=min(f[deltammx],i);
			}
			v[i].clear();
		}
		for(i=1;i<=n;i++) 
		{
			f[i]=min(f[i],f[i-1]);
			if(f[i]==0x3f3f3f3f) cout<<-1<<" ";
			else cout<<f[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}

```



---

## 作者：SSerxhs (赞：1)

如果把 $a_0,a_{n+1}$ 看作任意元素，每个长度为 $k$ 的子串都含有 $x$ 等价于 $a$ 中相邻两个 $x$ 的下标差不超过 $k$。

考虑用链表维护一个值出现的位置，可以求出任意 $x$ 的相邻两个 $x$ 最大下标差 $b_x$，则当且仅当 $k\ge b_x$ 时 $x$ 可以更新答案，所以直接对 $b_x$ 排序并按顺序更新答案即可。

基排或快排均可，复杂度分别为 $O(\sum n),O(\sum nlogn)$

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf=1e9,N=3e5+2;
pair<int,int> mx[N];
int fir[N],nxt[N],lst[N];
int n,c,fh,i,ans,anss,t,x,j;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int main()
{
	read(t);
	while (t--)
	{
		read(n);
		memset(fir+1,0,n<<2);
		memset(lst+1,0,n<<2);
		memset(nxt+1,0,n<<2);
		for (i=1;i<=n;i++)
		{
			read(x);if (!fir[x]) fir[x]=lst[x]=i; else lst[x]=nxt[lst[x]]=i;
		}
		for (i=1;i<=n+1;i++) mx[mx[i].second=i].first=inf;
		for (i=1;i<=n;i++) if (fir[i])
		{
			mx[i].first=max(fir[i],n-lst[i]+1);
			for (j=fir[i];j!=lst[i];j=nxt[j]) mx[i].first=max(mx[i].first,nxt[j]-j);
		}
		sort(mx+1,mx+n+1);ans=inf;
		for (i=1,j=0;i<=n;i++)
		{
			while ((mx[j+1].first!=inf)&&(i>=mx[j+1].first)) 
			{
				++j;
				ans=min(ans,mx[j].second);
			}
			if (ans==inf) printf("-1 "); else printf("%d ",ans);
		}puts("");
	}
}
```

---

