# [GDCPC 2023] Swapping Operation

## 题目描述

给定长度为 $n$ 的非负整数序列 $A = a_1, a_2, \dots, a_n$，定义

$$
F(A)=\max\limits_{1\leq k<n} ((a_1 \,\&\, a_2 \,\&\, \cdots \,\&\, a_k)+(a_{k+1} \,\&\, a_{k+2} \,\&\, \cdots \,\&\, a_n))
$$

其中 $\&$ 表示按位与操作。

您可以进行至多一次交换操作：选择两个下标 $i$ 和 $j$ 满足 $1\leq i < j\leq n$，交换 $a_i$ 与 $a_j$ 的值。

求经过至多一次交换后，$F(A)$ 的最大值。

## 样例 #1

### 输入

```
3
6
6 5 4 3 5 6
6
1 2 1 1 2 2
5
1 1 2 2 2```

### 输出

```
7
3
3```

# 题解

## 作者：IdnadRev (赞：3)

首先，如果 swap，那么 $k$ 一定在 swap 的一对位置中间。

不妨提取出改变前缀 $\operatorname{and}$ 值与后缀 $\operatorname{and}$ 值的 $\log$ 个关键点。

如果交换非两个关键点，对应的前缀/后缀权值不会变大，因此不优。

如果交换一个关键点，一个非关键点。不妨假设是枚举的前缀关键点 $i$ 与非关键点 $j$，那么每个 $k$ 对应权值应是（记 $f(i,j)$ 为 $[i,j]$ 区间 $\operatorname{and}$ 值）：

$$(f(1,i-1)\operatorname{and} f(i+1,k)\operatorname{and} a_j)+(f(k+1,n)\operatorname{and}a_i)$$

枚举 $i$ 后右边的值固定，而左边注意到 $f(1,i-1)\operatorname{and} f(i+1,k)$ 的值只有 $\log^2 V$ 种，可以对每种 $O(n)$ 暴力枚举 $j$ 处理。

如果交换两个关键点，暴力枚举后计算。

复杂度 $O(n\log^2 V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005,maxk=19,S=(1<<30)-1;
int n,m,T,ans;
int a[maxn],lg[maxn],st[maxk][maxn],pv[maxn],ispre[maxn],issuf[maxn],mx[maxn];
vector<int>pre,suf;
map<int,vector< pair<int,int> >>mp;
int query(int l,int r){
	if(l>r)
		return S;
	int k=lg[r-l+1];
	return st[k][l]&st[k][r-(1<<k)+1];
}
void calc(){
	pv[0]=S;
	for(int i=1;i<=n;i++)
		pv[i]=pv[i-1]&a[i];
	for(int i=n,v=S;i>1;i--){
		v&=a[i],ans=max(ans,pv[i-1]+v);
	}
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n),ans=0,lg[0]=-1;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]),st[0][i]=a[i],lg[i]=lg[i>>1]+1,ispre[i]=issuf[i]=0;
		for(int i=1;i<=18;i++)
			for(int j=1;j+(1<<i)-1<=n;j++)
				st[i][j]=st[i-1][j]&st[i-1][j+(1<<(i-1))];
		pre.clear(),suf.clear();
		for(int i=1,now=S;i<=n;now&=a[i],i++)
			if((now&a[i])<now)
				pre.emplace_back(i),ispre[i]=1;
		for(int i=n,now=S;i>=1;now&=a[i],i--)
			if((now&a[i])<now)
				suf.emplace_back(i),issuf[i]=1;
		calc();
		for(int i=0;i<pre.size();i++)
			for(int j=0;j<suf.size();j++)
				swap(a[pre[i]],a[suf[j]]),calc(),swap(a[pre[i]],a[suf[j]]);
		mp.clear();
		for(int i=0;i<pre.size();i++)
			for(int j=pre[i];j<n;j++){
				int v=query(1,pre[i]-1)&query(pre[i]+1,j);
				mp[v].emplace_back(make_pair(j+1,query(j+1,n)&a[pre[i]]));
			}
		for(map<int,vector<pair<int,int>>>::iterator it=mp.begin();it!=mp.end();it++){
			int v=it->first;
			mx[n+1]=-2e9;
			for(int i=n;i>=1;i--){
				mx[i]=mx[i+1];
				if(issuf[i]==0)
					mx[i]=max(mx[i],v&a[i]);
			}
			vector<pair<int,int>>V=it->second;
			for(int i=0;i<V.size();i++)
				ans=max(ans,mx[V[i].first]+V[i].second);
		}
		mp.clear();
		for(int i=0;i<suf.size();i++)
			for(int j=1;j<suf[i];j++){
				int v=query(j+1,suf[i]-1)&query(suf[i]+1,n);
				mp[v].emplace_back(make_pair(j,query(1,j)&a[suf[i]]));
			}
		for(map<int,vector<pair<int,int>>>::iterator it=mp.begin();it!=mp.end();it++){
			int v=it->first;
			mx[0]=-2e9;
			for(int i=1;i<=n;i++){
				mx[i]=mx[i-1];
				if(ispre[i]==0)
					mx[i]=max(mx[i],v&a[i]);
			}
			vector<pair<int,int>>V=it->second;
			for(int i=0;i<V.size();i++)
				ans=max(ans,mx[V[i].first]+V[i].second);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Graphcity (赞：2)

先简要给出几个显然的观察：

- **观察一**：设前缀与数组为 $pre$，后缀与数组为 $suf$。令所有满足 $pre_i\not=pre_{i-1}$ 的位置 $i$ 称为前缀断点，后缀断点同理。则断点数目级别为 $O(\log V)$ 。
- **观察二**：如果交换了 $i,j\ (i<j)$，则选择的 $k$ 必定在 $[i,j)$ 之间，否则交换不起作用。
- **观察三**：交换两个非断点的数只会让答案变劣，因为交换后前后缀和只会变得更小。

对于一次交换可以在 $O(n)$ 内完成。所以不交换和交换两个断点的情况可以 $O(n\log^2 V)$ 解决。接下来考虑仅交换一个断点的情况，不妨设它为前缀断点 $x$。

对于前缀与数组，可以令 $x$ 所在位置为 $2^{31}-1$。对于后缀与数组，可以在序列的末尾加入一个 $a_x$。设新得到的数组分别为 $pre'$ 和 $suf'$。此时如果交换 $x,i$，位置 $k$ 的贡献就是 $(a_i \ \& \ pre'_k)+suf'_{k+1}$。

类似于之前的观察，最优解中的 $k$ 一定位于 $suf'$ 数组的后缀断点的前一位。这又是 $O(\log V)$ 级别的了。一共要枚举 $O(\log V)$ 个断点，总时间复杂度依然是 $O(n\log^2V)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int T,n,ans,a[Maxn+5],pr[Maxn+5],sf[Maxn+5];

inline int Count()
{
    pr[0]=INT_MAX; For(i,1,n) pr[i]=pr[i-1]&a[i];
    sf[n+1]=INT_MAX; Rof(i,n,1) sf[i]=sf[i+1]&a[i];
    int res=0; For(i,1,n-1) res=max(res,pr[i]+sf[i+1]); return res;
}
inline int Solve(int x)
{
    pr[0]=INT_MAX; For(i,1,n) pr[i]=(i==x)?pr[i-1]:pr[i-1]&a[i];
    sf[n+1]=a[x]; Rof(i,n,1) sf[i]=sf[i+1]&a[i]; int res=0;
    for(int l=x+1,r;l<=n;l=r+1)
    {
        for(r=l;r<n && sf[r+1]==sf[l];++r);
        For(i,l,n) res=max(res,(pr[l-1]&a[i])+sf[l]);
    } return res;
}
inline void Solve()
{
    n=read(); For(i,1,n) a[i]=read();
    ans=Count(); vector<int> v1,v2;
    For(i,1,n) if(pr[i]!=pr[i-1]) v1.push_back(i);
    Rof(i,n,1) if(sf[i]!=sf[i+1]) v2.push_back(i);
    for(auto i:v1) for(auto j:v2) if(i!=j)
        swap(a[i],a[j]),ans=max(ans,Count()),swap(a[i],a[j]);
    for(auto i:v1) ans=max(ans,Solve(i));
    reverse(a+1,a+n+1);
    for(auto i:v2) ans=max(ans,Solve(n-i+1));
    cout<<ans<<endl;
}

int main()
{
    T=read();
    while(T--) Solve();
    return 0;
}
```



---

## 作者：RAND_MAX (赞：0)

一道好题啊，思维量挺大的。

我们设值域为 $M$，由于前缀与单调不增，那么前缀与的值最多有 $\log M$ 种。我们称前缀与值与上一个不同的点为分割点，对于后缀与同理。

考虑交换操作，不难发现若交换两个非分割点，得到的答案不优于不交换的情况。我们分类讨论另外两种。

#### 若交换双方均为分割点
我们注意到分割点最多有 $2\times \log M$ 个，我们只需枚举交换的分割点并 $O(n)$ 暴力统计答案即可，这部分复杂度为 $O(n\log^2M)$。

#### 若交换双方仅一个是分割点
我们不妨设这个分割点是前缀分割点，对于后缀分割点只需反转序列即可。\
我们发现若是交换后的最大值优于原序列，那么 $k$ 必定在交换的两个位置之间，否则不优于原序列。\
进一步观察，发现 $k$ 必在后缀分割点的前一位，否则不优。那么我们只需枚举参与交换的前缀分割点 $i$，并在枚举非分割点的同时枚举后缀分割点前一位 $k$ 的位置。这部分时间复杂度同样是 $O(n\log^2M)$。

总时间复杂度为 $O(n\log^2M)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-')
		{
			f=-1;
		}
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+c-48;
		c=getchar();
	}
	return x*f;
}
void write(int x)
{
	static int st[35],top=0;
	if(x<0)
	{
		x=-x;
		putchar('-');
	}
	do
	{
		st[top++]=x%10;
		x/=10;
	}while(x);
	while(top)
	{
		putchar(st[--top]+48);
	}
	putchar('\n');
}
int T,n,a[100010],num[100010],bk[100010],U=(1ll<<30)-1,ans;
vector<int>b,f;
signed main()
{
	T=R;
	while(T--)
	{
		n=R;
		for(int i=1;i<=n;i++)
		{
			a[i]=R;
		}
		num[0]=bk[n+1]=U,ans=0;
		b.clear(),f.clear();
		for(int i=1;i<=n;i++)
		{
			num[i]=num[i-1]&a[i];
			if(num[i]!=num[i-1]) f.push_back(i);
		}
		for(int i=n;i>=1;i--)
		{
			bk[i]=bk[i+1]&a[i];
			if(bk[i]!=bk[i+1]) b.push_back(i);
		}
		for(int i:f)
		{
			for(int j:b)
			{
				swap(a[i],a[j]);
				for(int k=1;k<=n;k++)
				{
					num[k]=num[k-1]&a[k];
				}
				for(int k=n;k>=1;k--)
				{
					bk[k]=bk[k+1]&a[k];
				}
				for(int k=1;k<n;k++)
				{
					ans=max(ans,num[k]+bk[k+1]);
				}
				swap(a[i],a[j]);
			}
		}
		for(int i:f)
		{
			num[0]=U,bk[n+1]=a[i];
			for(int j=1;j<=n;j++)
			{
				if(j==i) num[j]=num[j-1];
				else num[j]=num[j-1]&a[j];
			}
			for(int j=n;j>=1;j--)
			{
				bk[j]=bk[j+1]&a[j];
			}
			int j=i+1,k;
			while(j<=n)
			{
				k=j;
				while(k<n&&bk[k+1]==bk[j]) k++;
				for(int l=j;l<=n;l++)
				{
					ans=max(ans,(num[j-1]&a[l])+bk[j]);
				}
				j=k+1;
			}
		}
		reverse(a+1,a+n+1);
		for(int ii:b)
		{
			int i=n-ii+1;
			num[0]=U,bk[n+1]=a[i];
			for(int j=1;j<=n;j++)
			{
				if(j==i) num[j]=num[j-1];
				else num[j]=num[j-1]&a[j];
			}
			for(int j=n;j>=1;j--)
			{
				bk[j]=bk[j+1]&a[j];
			}
			int j=i+1,k;
			while(j<=n)
			{
				k=j;
				while(k<n&&bk[k+1]==bk[j]) k++;
				for(int l=j;l<=n;l++)
				{
					ans=max(ans,(num[j-1]&a[l])+bk[j]);
				}
				j=k+1;
			}
		}
		write(ans);
	}
 	return 0;
}

```

---

