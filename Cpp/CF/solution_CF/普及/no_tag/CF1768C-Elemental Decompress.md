# Elemental Decompress

## 题目描述

给定整数 $n$ 和长度为 $n$ 的序列 $a$。  
构造任意一组 $1\sim n$ 的排列 $p,q$，使得对于任意整数 $i(1\leq i\leq n)$ 都有 $\max(p_i,q_i)=a_i$。  
有解输出 `YES` 然后输出任意一组满足要求的 $p,q$ 即可；无解输出 `NO`。  
每个测试点包含 $t$ 组数据。

## 样例 #1

### 输入

```
3
1
1
5
5 3 4 2 5
2
1 1```

### 输出

```
YES
1 
1 
YES
1 3 4 2 5 
5 2 3 1 4 
NO```

# 题解

## 作者：igAC (赞：10)

# $\text{Describe}$

[洛谷link](https://www.luogu.com.cn/problem/CF1768C)

[CFlink](https://codeforces.com/problemset/problem/1768/C)

简要题意：给定数组 $a$，构造数组 $p,q$ 使得 $\max(p_i,q_i)=a_i$。

$p,q$ 都是 $1 \sim n$ 的排列。

# $\text{Solution}$

首先能够造出来的有很明显的三个性质：

- 每个数字不能出现超过 $2$ 次。

- 数字 $1$ 不能出现超过 $1$ 次。

- 数字 $n$ 不能不出现。

接着我们考虑其他数字分别出现 $0,1,2$ 次的情况。

对于出现 $1$ 次的数字 $k$，显然可以构造 $p_i=q_i=k$，可以证明这样绝对不劣于其他方法。

对于出现 $2$ 次的数字 $k$，我们记录它的两个位置，之后两个数组可以分别设为对应值。

那么出现两次的数字的位置所对应的另一个数组的位置上将会有空缺。

即：

![](https://cdn.luogu.com.cn/upload/image_hosting/mkhuxerw.png)


之后我们就发现，能填补空缺的只有那些出现次数为 $0$ 的数字。

显然最优的填法是：填入小于当前数字 $d$ 的最大的数。

我们将能填补空缺的数全部存进一个 ``set`` 里，接着用 ``lower_bound`` 查询一下，是否是 ``s.begin()``。

若不是则迭代器 $-1$。

若是，那么说明没有更小的值了，于是就输出 ``NO``。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,Max,n,k,a[N],p[N],q[N];
vector<int>pos[N];
set<int>s;
void clean(){
	Max=0;s.clear();
	for(int i=1;i<=n;++i){
		p[i]=q[i]=0;
		pos[i].clear();
	}
}
int main(){
	T=read();
	while(T--){
		n=read();clean();
		for(int i=1;i<=n;++i) Max=max(Max,a[i]=read());
		for(int i=1;i<=n;++i) pos[a[i]].push_back(i);
		bool flg=true;
		for(int i=1;i<=Max;++i){
			sort(pos[i].begin(),pos[i].end());
			if(pos[i].empty()) s.insert(i);
			else if(pos[i].size()==1) p[pos[i][0]]=q[pos[i][0]]=i;
			else if(pos[i].size()==2) p[pos[i][0]]=q[pos[i][1]]=i;
			else{
				flg=false;
				break;
			}
		}
		if(pos[n].empty() || pos[1].size()>=2) flg=false;
		for(int i=1;i<=n;++i){
			if(p[i] && !q[i]){
				int pre=pos[p[i]][1];
				set<int>::iterator it=s.lower_bound(p[i]);
				if(it==s.begin()){
					flg=false;
					break;
				}
				else{
					it--;
					q[i]=p[pre]=*it;
					s.erase(it);
				}
			}
		}
		if(!flg) puts("NO");
		else{
			puts("YES");
			for(int i=1;i<=n;++i) printf("%d ",p[i]);puts("");
			for(int i=1;i<=n;++i) printf("%d ",q[i]);puts("");
		}
	}
	return 0;
}
```

---

## 作者：ExplodingKonjac (赞：3)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1768C)**

## 题目分析

首先如果 $a$ 有三个相同的数显然不可行，先判掉。

那么对于 $a$ 中的每个数 $k$，可以通过这样的方式构造：如果在 $x$ 出现一次，令 $p_x,q_x\gets k$；如果在 $x,y$ 出现，令 $p_x,q_y\gets k$，且 $p_y,q_x$ 需要另一个比 $k$ 小的数填补。

然后就用 $a$ 中没有出现的数去填补空隙，显然对于上文中每一对 $x,y$，把 $p_y,q_x$ 填补为一个数最优，而这个配对也显然是较大的配对较大的最优。如果这样无法配对则误解。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 快读

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

int T,n,a[200005],p1[200005],p2[200005];
vector<int> pos[200005];
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n;
		for(int i=1;i<=n;i++) pos[i].clear();
		for(int i=1;i<=n;i++) qin>>a[i],pos[a[i]].push_back(i);
		bool fl=true;
		queue<int> q;
		for(int i=n;i>=1;i--)
		{
			if(pos[i].size()>2) { fl=false;break; }
			if(pos[i].empty())
			{
				if(q.empty()) { fl=false;break; }
				int j=q.front();
				p2[pos[j].front()]=i;
				p1[pos[j].back()]=i;
				q.pop();
			}
			else
			{
				p1[pos[i].front()]=i;
				p2[pos[i].back()]=i;
				if(pos[i].size()>1) q.push(i);
			}
		}
		if(!fl) { qout<<"NO\n";continue; }
		qout<<"YES\n";
		for(int i=1;i<=n;i++) qout<<p1[i]<<' ';
		qout<<'\n';
		for(int i=1;i<=n;i++) qout<<p2[i]<<' ';
		qout<<'\n';
	}
	return 0;
}
```

---

## 作者：jifbt (赞：2)

比官方题解更容易实现的解法。与官方题解不同，这回我们从小到大遍历。

- 如果一个值 $x$ 在数组第 $i$ 位出现一次，则令 $p_i = q_i = x$。
- 如果没出现，丢到一个集合里。
- 如果在第 $i$、$j$ 位出现两次，集合已经空了则无解；否则从集合里任取一个数 $y$（我用栈来实现），令 $p[i]=q[j]=x$，$p[j]=q[i]=y$。
- 如果出现更多次，无解，因为一个数顶多在 $p$ 里出现一次，在 $q$ 里出现一次。

（从大到小遍历应该也可做，把没出现的和出现两次的处理调换一下就行了。就是实现时稍微不方便一些。）

```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
template<typename T>void rd(T&x){
	x=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48;c=getchar();}
	x*=f;
}
template<typename T>T rd(){T x;rd(x);return x;}
template<typename T,typename...T2>void rd(T&x,T2&...y){rd(x),rd(y...);}
int getc(){int c;while(isspace(c=getchar()));return c;}
const int N=2e5+10;
int T,n,a[N];
int s[N][2],t[N];
int p[N],q[N];
int ss[N],tt;
int main(){
	rd(T);
	while(T--){
		rd(n),memset(t,0,(n+10)<<2),tt=0;
		bool f=1;
		for(int i=1;i<=n;++i){
			rd(a[i]);
			if(++t[a[i]]>2)f=0;
			else s[a[i]][t[a[i]]-1]=i;
		}
		if(!f)goto end;
		for(int i=1;i<=n;++i){
			if(!t[i])ss[tt++]=i;
			else if(t[i]==1)p[s[i][0]]=q[s[i][0]]=i;
			else{
				if(!tt)goto end;
				p[s[i][0]]=q[s[i][1]]=i;
				p[s[i][1]]=q[s[i][0]]=ss[--tt];
			}
		}
		puts("YES");
		for(int i=1;i<=n;++i)printf("%d ",p[i]);
		puts("");
		for(int i=1;i<=n;++i)printf("%d ",q[i]);
		puts("");
		continue;
		end:puts("NO");
	}
}

```

---

## 作者：zajasi (赞：2)

## 解题思路
不可以的一个显然的结论就是：如果一个数在数组中出现了 $3$ 次及以上，肯定不行，因为最多只能出现两次（有两个排列）。

然后我们考虑一个数在数组中出现两次的情况：首先两个地方的上下肯定分别要出现一次这个数，然后另一个数是什么呢？我们可以把在数组中没出现过的数找出来，也就是说最大值里面没有它。考虑到别的小的出现过两次的数可能要用到更小的数，所以我们需要在没出现过的序列中挑一个小于当前数且尽量大的数，也就是可以用二分查找。另外，对于每一个只出现过一次的数，只要上下都输出这个数就行了。

是不是没听懂？看看代码就懂啦。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int n;
int a[200020];
int h[200020];
int x[200020],y[200020];
pair<int,int> c[200020];
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		int f=0,ff=1;
		for(int i=1;i<=n;i++){
			h[i]=0;
			x[i]=y[i]=1145141919810;//初始两个序列随便赋个值
			c[i].first=c[i].second=0;//first 和 second 记录出现 i 的位置
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
			h[a[i]]++;
			if(h[a[i]]>2)f=1;//出现次数大于两次，就不行了
			if(h[a[i]]==2)ff=0;
			if(c[a[i]].first==0)c[a[i]].first=i;
			else c[a[i]].second=i;//记录位置
		}
		if(f==1){
			cout<<"NO\n";
			continue;
		}
		
		if(ff==1){
			cout<<"YES\n";
			for(int i=1;i<=n;i++){
				cout<<a[i]<<" ";
			}
			cout<<"\n";
			for(int i=1;i<=n;i++){
				cout<<a[i]<<" ";
			}
			cout<<"\n";
			continue;
            		//没有出现过两次的情况，非常好，只要上下都输出这个序列就合法啦。
		}
		vector<int> d;
		for(int i=1;i<=n;i++){
			if(h[i]==0)d.push_back(i);
		}
		for(int i=1;i<=n;i++){
			if(h[a[i]]==2){
				x[i]=a[i];
				y[c[a[i]].second]=a[i];
				int l=upper_bound(d.begin(),d.end(),a[i])-d.begin();//找到一个最优的数
				l--;
				if(l<0){
					f=1;
					break;
				}//找不到了就也不行
				x[c[a[i]].second]=d[l];
				y[i]=d[l];
				d.erase(d.begin()+l,d.begin()+l+1);//用完删掉
//				for(int j=1;j<=n;j++){cout<<x[j]<<" ";}cout<<"\n";
//				for(int j=1;j<=n;j++)cout<<y[j]<<" ";cout<<"\n\n";
				h[a[i]]=1145141919810;
			}
		}
		if(d.size()||f==1){
			cout<<"NO\n";
			continue;			
		}
		cout<<"YES\n";
		for(int i=1;i<=n;i++){
			if(x[i]==1145141919810)cout<<a[i]<<" ";
			else cout<<x[i]<<" ";
		}
		cout<<"\n";
		for(int i=1;i<=n;i++){
			if(y[i]==1145141919810)cout<<a[i]<<" ";
			else cout<<y[i]<<" ";			
		}
		cout<<"\n";
	}
	return 0;
}
 
```


---

## 作者：_Remake_ (赞：1)

简单构造题。

首先可以发现，如果一个数出现了**两次以上**，是无解的。

其次可以发现，如果 `N ` **没有出现**，是无解的。

然后可以发现，如果 `1` 出现了**两次**，是无解的。

原因显然，大家可以自己推一下，然后就可以开始构造了。

我们采用从大到小的构造方式，原因是确定了比一个元素大的所有元素的位置，它只能填在之前的构造过程中出现的空位内，原因是填在之前的空位内不会影响答案，而填在别的地方就会使 $\max(a_i,b_i)$ 改变，就会出现错误答案。

显然有一个构造策略：

当一个数仅仅出现一次，就把 `A` 数组和 `B` 数组内这个数的出现位置同时填入这个数，因为这样即不会影响答案，也可以避免消耗空位。

当一个数出现两次，设它首次出现的位置为 $i$，再次出现的位子为 $j$，把 $A_i$ 和 $B_j$ 设为这个数并产生两个空位 $A_j$ 和 $B_i$，使用 `vector` 存储。

当一个数没有出现，将这个数填入两个之前产生的空位中，如果没有足够的空位即为无解。

时间复杂度：$\mathcal{O}(n)$

代码：
```cpp
#include<bits/stdc++.h>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define debug puts("51522jqwlwdbb");
//#define int long long
int read()
{
    int n=0,k=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        {
            k=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        n=n*10+ch-'0';
        ch=getchar();
    }
    return n*k;
}
int n,m;
int A[200001];
int B[200001];
char C[200001];
int t;
int cnt[200001];
int D[200001];
int idx[200001][3];
std::vector<int>Ak;
std::vector<int>Bk;
namespace qwq
{
    void main()
    {
    	t=read();
    	while(t--)
    	{
    		std::vector<int>X,Y;
    		std::swap(X,Ak);
    		std::swap(Y,Bk);
    		n=read();
    		for(int r=1;r<=n;r++)
    		{
    			cnt[r]=0;
    			idx[r][1]=idx[r][2]=0;
    			B[r]=0;
    			D[r]=0;
    		}
    		bool flag=0;
    		for(int r=1;r<=n;r++)
    		{
    			A[r]=read();
    			cnt[A[r]]++;
    			idx[A[r]][cnt[A[r]]]=r;
    			if(cnt[A[r]]>=3)
    			{
    				flag=1;
    			}
    		}
    		if(flag)
    		{
    			puts("NO");
    			continue;
    		}
    		if(cnt[1]>=2)
    		{
    			puts("NO");
    			continue;
    		}
    		if(cnt[n]==0)
    		{
    			puts("NO");
    			continue;
    		}
    		for(int r=n;r>=1;r--)
    		{
    			if(cnt[r]==2)
    			{
    				B[idx[r][1]]=r;
    				Ak.push_back(idx[r][1]);
    				D[idx[r][2]]=r;
    				Bk.push_back(idx[r][2]);
    			}
    			else if(cnt[r]==1)
    			{
    				B[idx[r][1]]=D[idx[r][1]]=r;
    			}
    			else
    			{
    				if(Ak.size())
    				{
    					D[Ak[(int)Ak.size()-1]]=r;
    					Ak.pop_back();
    				}
    				else
    				{
    					flag=1;
    					break;
    				}
    				if(Bk.size())
    				{
    					B[Bk[(int)Bk.size()-1]]=r;
    					Bk.pop_back();
    				}
    				else
    				{
    					flag=1;
    					break;
    				}
    			}
    		}
    		if(flag)
    		{
    			puts("NO");
    			continue;
    		}
    		else
    		{
    			puts("YES");
    			for(int r=1;r<=n;r++)
    			{
    				printf("%d ",B[r]);
    			}
    			puts("");
    			for(int r=1;r<=n;r++)
    			{
    				printf("%d ",D[r]);
    			}
    			puts("");
    		}
    	}
        return;
    }
}
signed main()
{
    //freopen("qwq.in","r",stdin);
    //freopen("qwq.out","w",stdout);
    qwq::main();
    return 0;
}
```


---

## 作者：hcywoi (赞：0)

## $\mathcal Solution$

### 【题意】

题目要你构造两个序列 $p, q$，满足 $\max\{p_i, q_i\}=a_i$。

### 【分析】

如果满足 $\max\{p_i, q_i\}=a_i$，则满足 $p_i=a_i, q_i\le a_i$ 或者 $q_i=a_i, p_i\le q_i$。

> 引理 $1$：如果有解，那么 $p_i = a_i$ 还是 $q_i = a_i$ 都是有解的。

证明：

因为有解，所以对于 $\forall i(1\le i\le n)$ 都满足 $p_i=a_i$ 或者 $q_i=a_i$。

如果 $p_i = a_i$ 有解，则我们对于 $\forall i (1\le i\le n)$ 进行 $\operatorname{swap}(p_i, q_i)$，也一定有解，这种情况就是 $q_i=a_i$，$\operatorname{swap}(p_i, q_i)$ 就是交换两个数。

然后我们根据性质 $1$，枚举每个数 $a_i$，然后判断 $p_i$ 序列中是否存在 $a_i$，不存在，则把 $a_i$ 加入序列 $p$ 中，否则，如果 $q$ 序列中出现了 $a_i$，则无解，否则将 $a_i$ 加入序列 $q$ 中。

接着我们看如何填入其他数。

我们贪心的考虑，一定是选能选的数最大的那个。

然而直接暴力枚举是 $\mathcal O(n^2)$，会 `TLE`，我们考虑优化。

我们是否能枚举小于一次就找到没有用过的最大值。

这个可以用并查集来维护，即一个数变成用过，判断其左边和右边是否为用过，如果用过，则合并成一个集合，然后维护每一个集合中的左端点。

那么找最大值就等价于找 $a_i$ 所在的集合的左端点减 $1$，还要特判 $a_i$ 没用过的情况。

具体实现见[代码](https://codeforces.com/contest/1768/submission/188380557)。

---

## 作者：IYSY2009I (赞：0)

这里提供一种十分清晰易懂的做法。

由于 $p$ 和 $q$ 都是一个排列，所以每个数字的出现次数最多只有两次。如果在 $a$ 数组中存在某个数字出现次数超过了两次，直接输出 $\texttt{NO}$。

那么每个数字出现的次数只能是零次、一次或两次。我们接着证明，在 $[1,n]$ 范围内的整数中，出现次数为零的数字与出现次数为二的数字种类个数相等。

设出现零、一、二次的数字种类个数为 $x,y,z$。

易得：

$\begin{cases} x+y+z=n \\ 0x+1y+2z=n \end{cases}$

所以 $x=z$。

于是我们开两个 $\texttt{vector}$，把出现次数为零的数字和出现次数为二的数字分别存进这两个 $\texttt{vector}$ 里，再比对一下两个 $\texttt{vector}$ 内的元素数量，不相等则输出 $\texttt{NO}$，否则进行下一步。

我们又可以发现，如果一种数字的出现次数为零次，那么这种数字在排列中另一个数组对应下标上的数字一定大于它；反之，如果一种数字的出现次数为两次，那么这种数字在排列中另一个数组对应下标上的数字一定小于它。

根据上述分析，我们就可以得出一个显然正确的构造方案了：

- 枚举两个 $\texttt{vector}$ 的下标，如果发现存在一个下标对应的存储出现次数为零的 $\texttt{vector}$ 中存储的数字大于（严谨地说是大于等于，不过显然不可能出现等于的情况）这个下标对应的存储出现次数为两的 $\texttt{vector}$ 中存储的数字，就输出 $\texttt{NO}$；否则一定有解，输出 $\texttt{YES}$。
- 将 $p$ 和 $q$ 赋一个初值，使得 $p_i=i,q_i=i$。
- 枚举两个 $\texttt{vector}$ 的下标，令其中一个 $\texttt{vector}$ 的下标所对应的数字为 $x$，另一个 $\texttt{vector}$ 的下标所对应的数字为 $y$，然后 $\operatorname{swap}(p_x,p_y)$。
- 执行完上一步后，$\max(p_i,q_i)$ 已经可以和 $a$ 数组中的数字一一对应了，但是位置还不对，所以利用排序，调整一下 $p$ 和 $q$ 的顺序。
- 输出答案即可。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
struct node{
	int id;
	int num;
};
struct pq{
	int p;
	int q;
};
pq qp[200005];
node a[200005];
bool cmp1(node x,node y){
	return x.num<y.num;
}
bool cmp2(pq x,pq y){
	return max(x.p,x.q)<max(y.p,y.q);
}
int mp[200005];
vector<int> v0;
vector<int> v2;
int ansp[200005];
int ansq[200005];
void cf(){
	int n=read();
	for(int i=1;i<=n;i++){
		a[i].id=i;
		a[i].num=read();
		mp[a[i].num]++;
		qp[i].p=i;
		qp[i].q=i;
	}
	sort(a+1,a+n+1,cmp1);
	for(int i=1;i<=n;i++){
		if(mp[i]==2) v2.push_back(i);
		if(!mp[i]) v0.push_back(i);
	}
	if(v0.size()!=v2.size()){
		printf("NO\n");
		for(int i=1;i<=n;i++){
			qp[i].p=0;
			qp[i].q=0;
			mp[i]=0;
			a[i].id=0;
			a[i].num=0;
		}
		v0.clear();
		v2.clear();
		return;
	}
	for(int i=0;i<v0.size();i++){
		if(v0[i]>v2[i]){
			printf("NO\n");
			for(int j=1;j<=n;j++){
				qp[j].p=0;
				qp[j].q=0;
				mp[j]=0;
				a[j].id=0;
				a[j].num=0;
			}
			v0.clear();
			v2.clear();
			return;
		}
		swap(qp[v0[i]].p,qp[v2[i]].p);
	}
	printf("YES\n");
	sort(qp+1,qp+n+1,cmp2);
	for(int i=1;i<=n;i++){
		ansp[a[i].id]=qp[i].p;
		ansq[a[i].id]=qp[i].q;
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ansp[i]);
	printf("\n");
	for(int i=1;i<=n;i++)
		printf("%d ",ansq[i]);
	printf("\n");
	for(int i=1;i<=n;i++){
		qp[i].p=0;
		qp[i].q=0;
		mp[i]=0;
		a[i].id=0;
		a[i].num=0;
	}
	v0.clear();
	v2.clear();
	return;
}
int main(){
	int n=read();
	for(int i=1;i<=n;i++)
		cf();
	return 0;
}
```

---

## 作者：Micnation_AFO (赞：0)

纪念我第一次 CF 过 C 不会 B。

提供一种对前置知识要求不高的方法。

首先把 $a$ 全部给 $p$ 数组，遇到冲突（一个数出现了两次）的时候再给 $q$ 数组。

```cpp
	int n; cin >> n;
        for (int i = 1; i <= n; i++) vis[i] = p[i] = q[i] = 0;
        for (int i = 1; i <= n; i++) cin >> a[i], vis[a[i]]++;
        for (int i = 1; i <= n; i++) {
            if (vis[a[i]] > 1) q[i] = a[i], vis[a[i]]--;
            else p[i] = a[i];
        }
```        

接下来，我们 把 $p$ 数组给填满。首先用 $x$ 数组记录 $p$ 中还没用的数字。

注意到，$p$ 未填的数字，$q$ 一定填了，所以我们贪心，按照 $q$ 中填了的数字的大小进行放置（比如在 $q$ 中最小的数字，在 $p$ 的同样位置填上 $x$ 的最小值）。

```cpp
        for (int i = 1; i <= n; i++) vis[i] = 0;
        for (int i = 1; i <= n; i++) vis[p[i]]++;
        int tot = 0;
        for (int i = 1; i <= n; i++)
            if (!vis[i]) x[++tot] = i;
        int tot2 = 0;
        for (int i = 1; i <= n; i++)
            if (q[i]) y[++tot2] = make_pair(q[i], i);
        sort(y + 1, y + 1 + tot2);
        for (int i = 1; i <= tot; i++) p[y[i].second] = x[i];
```

然后，以同样的方法把 $q$ 数组填满：

```cpp
        for (int i = 1; i <= n; i++) vis[i] = 0;
        for (int i = 1; i <= n; i++) vis[p[i]]++;
        int tot = 0;
        for (int i = 1; i <= n; i++)
            if (!vis[i]) x[++tot] = i;
        int tot2 = 0;
        for (int i = 1; i <= n; i++)
            if (q[i]) y[++tot2] = make_pair(q[i], i);
        sort(y + 1, y + 1 + tot2);
        for (int i = 1; i <= tot; i++) p[y[i].second] = x[i];
```

这样，$p$ 和 $q$ 数组就都填好了。此时，判断 $p$ 和 $q$ 是否都是排列，并看看 $\max(p_i, q_i)$ 是不是 $a_i$，如果不满足，则不合法。

完整代码：[188109759](https://codeforces.com/contest/1768/submission/188109759)。

---

## 作者：lfxxx (赞：0)

考虑构造。

首先第一轮构造我们把第一次出现的数放到 $p$ 里面，第二次出现的放到 $q$ 里面。如果有数第三次出现呢？那么显然无解。

那么现在 $p$ 和 $q$ 中都填了一些数，但是因为题目要求，所以**填后面某个位置的数时要比这个位置已经填的数小**所以把排列中没有的数存起来，按照**从小到大**的顺序填入即可，填的时候**优先填入另一个排列对应位置较小的位置**即可。显然，这是一种贪心的构造。

那么注意好代码实现就好，~~不要像我调了半个小时~~

```cpp
#include<bits/stdc++.h>
//#define int long long
//#define lowbit(x) (x&-(x))
using namespace std;
const int maxn = 2e5+10;
int t;
int a[maxn],cnt[maxn];
int p[maxn],q[maxn];
int Search[maxn][2];
void work(){
	int n;
	int flag=0;
	stack<int> op;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		Search[i][0]=Search[i][1]=p[i]=q[i]=cnt[i]=0;
	}
	for(int i=1;i<=n;i++){	
		if(cnt[a[i]]==2){
			cout<<"NO\n";
			return ;
		}	
		if(cnt[a[i]]==0){
			p[i]=a[i];
			Search[a[i]][0]=i;
		}
		else{
			flag=1;
			q[i]=a[i];
			Search[a[i]][1]=i;
		}
		cnt[a[i]]++;
	}
	if(flag==0){
		cout<<"YES\n";
		for(int i=1;i<=n;i++){
			cout<<a[i]<<' ';
		}
		cout<<'\n';
		for(int i=1;i<=n;i++){
			cout<<a[i]<<' ';
		}
		cout<<'\n';
		return ;
	}
	for(int i=1;i<=n;i++) cnt[i]=0;
	for(int i=1;i<=n;i++){
		cnt[p[i]]++;
	}
	for(int i=n;i>=1;i--){
		if(cnt[i]==0){
			op.push(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(p[Search[i][1]]==0){
			p[Search[i][1]]=op.top();
			op.pop();
		}
	}
	for(int i=1;i<=n;i++){
		cnt[i]=0;
	}
	for(int i=1;i<=n;i++){
		cnt[q[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(cnt[i]==0)
			op.push(i);
	}
	for(int i=1;i<=n;i++){
		if(q[Search[i][0]]==0){
			q[Search[i][0]]=op.top();
			op.pop();
		}
	}
	for(int i=1;i<=n;i++){
		if(max(p[i],q[i])!=a[i]){
			cout<<"NO\n";
			return ;
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++){
		cout<<p[i]<<' ';
	}
	cout<<'\n';
	for(int i=1;i<=n;i++){
		cout<<q[i]<<' ';
	}
	cout<<'\n';
}
int main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
int t;
cin>>t;
while(t--){
	work();
}

return 0;
}

```


---

## 作者：c20231020 (赞：0)


### 题目链接
[luogu](https://www.luogu.com.cn/problem/CF1768C)

[codeforces](https://codeforces.com/contest/1768/problem/C)

### 题目大意
给你一个由 $n$ 个整数组成的数组 $a$。

找到两个长度为 $n$ 的 $p$ 和 $q$ 的排列 $^\dagger$，使 $\max(p_i,q_i)=a_i$ 适用于所有 $1\leq i\leq n$ 或报告说这样的 $p$ 和 $q$ 不存在。

$^\dagger$ 一个长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的不同整数按任意顺序组成的数列。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（$2$ 在数列中出现两次），$[1,3,4]$ 也不是排列（$n=3$ 但在数列中有 $4$）。

### 思路
开一个结构体，包含原位置 $i$，原位置上的 $a$，构造出的 $p$ 和 $q$。

将结构体数组按 $a$ 从小到大排序。再对 $p$ 和 $q$ 分别开一个记录数字使用情况的桶 $f$ 和 $g$。

然后就是大力分类讨论。

> 下面的 $a$ 指的是固定一个位置讨论。

1. 有三个及以上的 $a$ 相同。由于同一个数最多出现两次（$p,q$ 各一次），不能贡献三个最大值，这种情况无解。

2. 假设有一个 $a$ 排序后存在于位置 $j$ 上，当 $a<j$ 时，由于前面有 $j-1$ 个数，这个位置的最小值是 $j$，则不能满足 $a$，无解。

3. $a$ 只有一个。那么 `p=q=a`，$f$ 和 $g$ 的 $a$ 位置打标记。

4. 有两个 $a$ 相同。分别维护一个指针 $pp$ 和 $pq$，在标记数组中扫到最小的没有用过的数，然后交叉赋值，打标记。

（其实只用维护一个数组和一个指针，因为两个排列所用数字一定对称。）

最后将结构体按原序号 $i$ 排序，输出 $p$ 和 $q$ 即可。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define ll long long
int n,f[200010],g[200010],pp,pq;
struct G{
	int i,a,p,q;
}a[200010];
void solve(){
	cin>>n;fill(f+1,f+1+n,0);fill(g+1,g+1+n,0);pp=pq=1;//注意多组清空
	for(int i=1;i<=n;++i)cin>>a[i].a,a[i].i=i;
	sort(a+1,a+1+n,[](G x,G y){return x.a<y.a;});//按 a 排序
	for(int i=1;i<=n;++i)if(a[i].a<i){
		cout<<"no\n";//上述第 2 种情况
		return;
	}
	for(int i=1;i<n-1;++i)if(a[i].a==a[i+1].a&&a[i].a==a[i+2].a){
		cout<<"No\n";//第 1 种
		return;
	}
	for(int i=1;i<=n;++i){
		if(i<n&&a[i].a==a[i+1].a){//第 4 种
			while(f[pp])++pp;
			while(g[pq])++pq;
			a[i].p=a[i+1].q=a[i].a;
			a[i].q=pq;a[i+1].p=pp;
			f[a[i].a]=g[a[i].a]=f[pp]=g[pq]=1;
			++i;//把下一个位置也算了，i 需要多加一次
		}else a[i].p=a[i].q=a[i].a,f[a[i].a]=g[a[i].a]=1;//第 3 种
	}
	cout<<"yes\n";
	sort(a+1,a+1+n,[](G x,G y){return x.i<y.i;});//恢复原序
	for(int i=1;i<=n;++i)cout<<a[i].p<<' ';cout<<'\n';
	for(int i=1;i<=n;++i)cout<<a[i].q<<' ';cout<<'\n';
	return;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;cin>>t;
	while(t--)solve();
	return 0;
}
```

End.

---

## 作者：yeshubo_qwq (赞：0)

## Description

构造两个长度为 $n$ 的排列 $a,b$，使 $\max(a_i,b_i)=x_i$。

## Solution

对于第 $i$ 位，排列 $a$ 中如果没出现过 $x_i$，就使 $a_i=x_i$，否则如果排列 $b$ 中如果没出现过 $x_i$，就使 $b_i=x_i$，否则显然无解。

这时候排列 $a$ 剩下一些位置要填，对于每个需要填的位置 $i$ 必须满足 $a_i \le b_i$。

我们按照 $b_i$ 的限制将这些位置排序，从小到大把排列中没有出现的数放进去即可，如果放不了则无解。

排列 $b$ 同理。

## Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
const int N=2e5+5;
int T,n,i,x,cnt[N],cnt1[N],a[N],b[N],qwq,y;
queue <int> Q,P;
struct node{
	int id,mx;
}c[N];
bool cmp(node x,node y){
	return x.mx<y.mx;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while (T--){
		cin>>n;
		for (i=1;i<=n;i++) cnt[i]=0,cnt1[i]=0,a[i]=0,b[i]=0;
		while (!Q.empty()) Q.pop();
		while (!P.empty()) P.pop();
		y=0;
		for (i=1;i<=n;i++){
			cin>>x;
			if (!cnt[x]) a[i]=x,cnt[x]=1;
			else if (!cnt1[x]) b[i]=x,cnt1[x]=1;
			else y=1;
		}
		if (y) {cout<<"NO\n";continue;}
		for (i=1;i<=n;i++) if (!cnt[i]) Q.push(i);
		for (i=1;i<=n;i++) if (!cnt1[i]) P.push(i);
		qwq=0;
		for (i=1;i<=n;i++) if (!a[i]) c[++qwq].id=i,c[qwq].mx=b[i];
		sort (c+1,c+1+qwq,cmp);
		for (i=1;i<=qwq;i++)
			if (Q.front()<=c[i].mx)
				a[c[i].id]=Q.front(),Q.pop();
		qwq=0;
		for (i=1;i<=n;i++) if (!b[i]) c[++qwq].id=i,c[qwq].mx=a[i];
		sort (c+1,c+1+qwq,cmp);
		for (i=1;i<=qwq;i++)
			if (P.front()<=c[i].mx)
				b[c[i].id]=P.front(),P.pop();
		if (Q.empty() && P.empty()){
			cout<<"YES\n";
			for (i=1;i<=n;i++) cout<<a[i]<<(i==n?'\n':' ');
			for (i=1;i<=n;i++) cout<<b[i]<<(i==n?'\n':' ');
		}
		else
			cout<<"NO\n";
	}
	return 0;
}

```


---

## 作者：fengxiaoyi (赞：0)

### 思路

这题对于每一个 $a_i$，判断是否在 $p$ 里出现过：

- 如果否，则 $p_i=a_i$，标记 $a_i$ 在 $p$ 里出现过；

$q_i=q_i$，标记 $a_i$；
- 否则判断，是否在 $q$ 里出现过：  
$\circ$ 如果否，则 $q_i=a_i$，标记 $a_i$ 在 $p$ 里出现过；  
$\circ$ 否则，说明这个 $a_i$ 无法放进两个数组的任何一个中，输出 `NO`。

接下来就是处理 $p,q$ 还没填的数了。

将填在 $p$ 里的数计入进 $k_1$ 数组，将填在 $q$ 里的数计入进 $k_2$ 数组，对于每个在 $k_1,k_2$ 其中一个里的数，记录下他们的位置。

接着，将两个数组从大到小排序，接着将每个数组剩余未填的数从大到小按照另一个数组对应的 $k$ 数组排序后的每一个数的位置填进去，如果这个数组当前位置的值比另一个大，输出 `NO`（因为这意味着 $\max(p_i,q_i)\not=a_i$）。

如果都成功的填进去了，输出 `YES`，然后输出这两个数组。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200010],p[200010],q[200010];
bool m1[200010],m2[200010];
struct QAQ{
	int sum,id;
}k1[200010],k2[200010];
bool cmp(QAQ _a,QAQ _b){
	return _a.sum<_b.sum;
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		memset(m1,0,sizeof(m1));
		memset(m2,0,sizeof(m2));
		int n1=0,n2=0,now1=1,now2=1;
		bool f=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(!m1[a[i]]) p[i]=a[i],k1[++n1].sum=a[i],k1[n1].id=i,m1[a[i]]=1;
			else if(!m2[a[i]]) q[i]=a[i],k2[++n2].sum=a[i],k2[n2].id=i,m2[a[i]]=1;
			else if(!f){
				printf("NO\n");
				f=1;
			}
		}
		if(f) continue;
		sort(k1+1,k1+n1+1,cmp);
		sort(k2+1,k2+n2+1,cmp);
		for(int i=1;i<=n1;i++){
			while(m2[now2]) now2++;
			if(now2<=0||now2>k1[i].sum){
				printf("NO\n");
				goto qaq;
			}
			q[k1[i].id]=now2;
			m2[now2]=1;
			now2++;
		}
		for(int i=1;i<=n2;i++){
			while(m1[now1]) now1++;
			if(now1<=0||now1>k2[i].sum){
				printf("NO\n");
				goto qaq;
			}
			p[k2[i].id]=now1;
			m1[now1]=1;
			now1++;
		}
		printf("YES\n");
		for(int i=1;i<=n;i++)
			printf("%d ",p[i]);
		putchar('\n');
		for(int i=1;i<=n;i++)
			printf("%d ",q[i]);
		putchar('\n');
		qaq:;
	}
	return 0;
}
```

---

