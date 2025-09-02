# Pairs

## 题目描述

你有 $2n$ 个整数 $1,2,\cdots,2n$，你需要将其分成 $n$ 对，然后选择其中 $x$ 对，取出其中的较小数，并取出其余 $n-x$ 对中的较大数，使得最终取出的数组成的集合为 $\{b_1,b_2,\cdots,b_n\}$。问有多少个满足题意的 $x$。

数据范围：$1 \le t \le 1000$，$\sum n \le 2 \cdot 10^5$。

## 样例 #1

### 输入

```
3
1
1
5
1 4 5 9 10
2
3 4```

### 输出

```
1
3
1```

# 题解

## 作者：IIIIndex (赞：16)

## 题意：

​	有一个长度为$n$的序列$b_1,b_2...b_n$，序列中每个元素的取值都在$[1,2n]$，其中，序列中每个元素，都是由某一个**不在此序列中**且在$[1,2n]$范围内的元素和它取$min/max$得到，设取$min$的对数为$x$，求所有$x$的可能取值的**个数**

## 思路：

​	首先，对于$[1,2n]$中所有的元素，都存在着一个**一一对应**的关系。我们连续不断地从$1$到$2n$进行遍历，并且维护一个叫$sp$的变量，一个叫$maxs$的变量（代表$sp$的最大值）和一个叫$mins$的变量（代表$sp$的最小值），（$sp$遇到在$b$序列中出现的元素就$+1$，反之$-1$）$sp$代表着“我们必须取$sp$个$min$”。假设我们现在遍历到$m$，$sp$的值为k，如果k为正，则说明**在过去的元素中**，存在于$b$序列内的元素个数比不存在$b$内的元素个数多$k$，所以说我们就需要额外的$k$个**比$m$大**的元素，和某k个**无法和其他元素取$max$**的元素（因为这$k$个元素无法和小于等于$m$的元素进行匹配了）进行匹配，此时的$k$，就大于等于$x$的**最小值**，我们把它和$maxs$取$max$就好。反之，对k为负的情况，就说明我们需要取$k$个比$m$大且在$b$序列内的元素和，此时$k$的绝对值，就是我们取$max$个数的最小值，我们把它和$mins$取$min$就好。

​	最后我们得到的$|mins|$，就是我们“至少得有$|mins|$对数取最大值”；$|maxs|$，就是我们“至少得有$|maxs|$对数取最小值”，$x$一共有n+1个取值，减去$|mins|$和$|maxs|$就是我们的答案，也就是$n+1-(maxs-mins)$

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int inf=1e9+7;
const int maxn=1e6;

int b[maxn];
bool used[maxn*2];

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=0;i<=n*2;i++)used[i]=false;
        for(int i=0;i<n;i++){
            cin>>b[i];
            used[b[i]]=true;
        }
        int sp=0,maxs=0,mins=0;
        for(int i=1;i<=2*n;i++){
            if(used[i])sp++;
            else sp--;
            maxs=max(maxs,sp);
            mins=min(mins,sp);
        }
        cout<<n-(maxs-mins)+1<<endl;
    }
    return 0;
}
```



---

## 作者：xhhhh36 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1463D)

首先可以发现所有的 $b_i$ 都必须分到不同的组里，如果在同一组出现了 $b_i$ 和 $b_j$，那么这两个数必须删去一个，并且数字没有重复，一定不合法。

那么分别按顺序考虑 $b_i$ 能否通过取较大值和取较小值得到。例如考虑取较小值，顺序遍历 $b_i$，设 $cnt$ 为剩余的小于 $b_i$ 的数的数量，这些数都可以和 $b_i$ 组成取较小数的一组，最开始 $ans=n+1$。每次让 $cnt+b_i-b_{i-1}-2\to cnt$，因为 $b_{i-1}$ 和 $b_i$ 之间有 $b_i-b_{i-1}-1$ 个小于 $b_i$ 的数，然后给 $b_i$ 匹配需要用一个。若此时 $cnt<0$ 说明 $b_i$ 无法匹配，让 $0\to cnt$，$ans-1\to ans$。考虑较大值也同理，逆序遍历即可。

由于一个 $b_i$ 不能通过取较小值得到则一定可以通过去较大值得到，所以 $ans$ 不会减至负数。
# AC code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,b[N],tmp,cnt,ans,now;
void work(){
	cin>>n;tmp=cnt=0;ans=n+1;
	for (int i=1;i<=n;i++) cin>>b[i];
	for (int i=1;i<=n;i++){
		cnt+=b[i]-b[i-1]-1;
		cnt--;
		if (cnt<0) cnt=0,ans--;
	}cnt=0;b[n+1]=n*2+1;
	for (int i=n;i>=1;i--){
		cnt+=b[i+1]-b[i]-1;
		cnt--;
		if (cnt<0) cnt=0,ans--;
	}
	cout<<ans<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	int t;cin>>t;while (t--) work();
	return 0;
}
```

---

## 作者：wz20201136 (赞：3)

首先考虑贪心。假设已经得到 $x$，如何判断是否可行呢。显然的，我们应该让 $b$ 数组前 $x$ 小的数是数对中的较小值。其余的是数对中的较大值。而为了取到较小值，前 $x$ 个数对的其余数应为 $b$ 数组以外的前 $x$ 大的数。分组情况如下：

![插图](https://cdn.luogu.com.cn/upload/image_hosting/d6hezo03.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

于是我们处理出 $b$ 数组的补集，二分出答案的左右端点 $l,r$（红线满足条件为 $[0,l]$，蓝线满足条件为 $[r,n]$）。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=4e5+5;
int t,n,b[MAXN],a[MAXN];
bool book[MAXN];
bool check1(int x)
{
	for(int i=1,j=n-x+1;i<=x;i++,j++)
		if(b[i]>a[j]) return 0;
	return 1;
}
bool check2(int x)
{
	for(int i=1,j=n-x+1;i<=x;i++,j++)
		if(a[i]>b[j]) return 0;
	return 1;
}
int main()
{
	cin>>t;
	while(t--)
	{
		memset(book,0,sizeof(book));
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&b[i]); 
			book[b[i]]=1;
		}
		for(int i=1;i<=n;i++)
			for(a[i]=a[i-1]+1;book[a[i]];a[i]++);
		int l=0,r=n,findl=n,findr=0;
		while(l<=r)//求答案的左端点
		{
			int mid=(l+r)/2;
			if(check1(mid)) findr=mid,l=mid+1;
			else r=mid-1;
		}
		l=0,r=n;
		while(l<=r)//右端点
		{
			int mid=(l+r)/2;
			if(check2(n-mid)) findl=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",max(0,findr-findl+1));
	}
	return 0;
}
```

---

## 作者：chager (赞：3)

同学打VP的时候卡在了这题……~~然后我就来了兴趣把这道题切了~~

我们不妨先来看个引理：

对于一个 $x$ ，如果它是合法的，那么我们一定可以通过交换法使得偏小的 $x$ 个元素所在的元素对取的是较小的那一个。

证明：不妨用反证法，我们发现 $(a,b)$ 取较大值 $b$， $(c,d)$ 取较小值 $c$，且 $b<c$ ，则：

易得 $a<b<c<d$。

那么我们交换 $b,c$，那么我们就可以得到两个新组：

$(b,d),(a,c)$

此时 $b$ 所在的组取最小值，$c$ 所在的组取最大值。

证毕。

因为数据给出的是有序的，所以我们对于每一组数据，就可以事先预处理出前面最多有多少点可以满足这些点都有点配使得这些点是配对中较小的那些个，同时同样算出后面最多有多少点可以满足这些点都有点配使得这些点是配对中较大的那些个。最后我们通过简单的计算即可得到答案。

代码：（绝对简单易懂）

```cpp
# include <stdio.h>
# include <algorithm>
int a[200010];
int f[200010],exi[400010];
void lf(int &x,int y)
{
	x--;
	while(exi[x] || x>y)
		x--;
	return;
}
void rf(int &x,int y)
{
	x++;
	while(exi[x] || x<y)
		x++;
	return;
}
int main()
{
	int i,j,n,m,tot,le,ri,x;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d",&m);
		for(i=1;i<=2*m+1;i++)
			exi[i]=0;
		for(j=1;j<=m;j++)
		{
			scanf("%d",&a[j]);
			exi[a[j]]=1;
		}
		le=-1;
		ri=-1;
		tot=0;
		x=2*m+1;
		for(j=m;j>=1;j--)
		{
			lf(x,a[j]);
			if(x==0)
			{
				le=j+1;
				break;
			}
		}
		tot=0;
		x=0;
		for(j=1;j<=m;j++)
		{
			rf(x,a[j]);
			if(x==2*m+1)
			{
				ri=j-1;
				break;
			}
		}
		if(le==-1)
			le=1;
		if(ri==-1)
			ri=m;
		printf("%d\n",std::max(ri-le+2,0));
	}
	return 0;
}
```

---

## 作者：Fairicle (赞：1)

可以发现 $x$ 应当是连续的，这个可以通过反证法使用交换进行证明。

所以只要能找到最小的 $x$ 和最大的 $x$ 就能得到答案。

而找最小的 $x$ 又可以转化成找最大的 $n-x$ 也就是找最大的取 $\text{max}$ 的次数。

找最小的 $x$ 只需要从小到大枚举 $b_i$，看当前 $b_i$ 前面是否有未被取的数，有就取走，容易证明这样一定优（通过决策包容性）

同理找最小的 $n-x$ 只需要从大到小枚举 $b_i$，看当前 $b_i$ 后面是否有未被取的数，有就取走。

code：

```cpp
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ri register int
inline ll rd(){
	ll x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
#define N 400010
int t,n,b[N],a[N];
set<int> s;
int main()
{
	t=rd();
	while(t--){
        n=rd();
        for(ri i=1;i<=n;++i) b[i]=rd(),a[b[i]]=1;
        s.insert(-1),s.insert(2*n+1);
        for(ri i=1;i<=2*n;++i) if(!a[i]) s.insert(i);
        int ansmx=0,ansmn=0;
        for(ri i=1;i<=n;++i){
            int pre=*--s.lower_bound(b[i]);
            if(pre==-1) continue;
            ansmx++;
            s.erase(pre);
        }//最多的取最小值次数
        s.clear();
        s.insert(-1),s.insert(2*n+1);
        for(ri i=1;i<=2*n;++i) if(!a[i]) s.insert(i);
        for(ri i=n;i>=1;--i){
            int nxt=*s.upper_bound(b[i]);
            if(nxt==2*n+1) continue;
            ansmn++;
            s.erase(nxt);
        }//最多的取最大值次数
        s.clear();
        for(ri i=1;i<=2*n;++i) a[i]=0;
        cout<<ansmx-(n-ansmn)+1<<endl;
    }
    return 0;
}

```


---

## 作者：ny_Dacong (赞：0)

# 思路

枚举集合 $b$ 当中的每一个元素究竟是较小的数还是较大的数。

如果没有比这个元素小且不在 $b$ 集合中的元素，那么这个元素一定是较小的数，因为没有其他数可以跟它匹配了。反之同理。

所以我们可以算出确定的数的个数，那么不确定的数就是总可能数减去确定的数。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n = 0,ans = 0,Max = 0,Min = 0;
int num[5000005],inque[10000005];
int main(){
	scanf("%d",&t);
	while(t--){
		ans = 0,Max = 0,Min = 0;
		for(int i = 0; i <= n*2; i++){
			num[i] = inque[i] = 0;
		}
		scanf("%d",&n);
		for(int i = 1; i <= n; i++){
			scanf("%d",&num[i]);
			inque[num[i]] = 1;
		}
		for(int i = 1; i <= n*2; i++){
			if(inque[i]){
				ans++;
			}else{
				ans--;
			}
			Max = max(Max,ans);
			Min = min(Min,ans);
		}
		printf("%d\n",n+1-Max+Min);
	}
	return 0;
}
```

---

