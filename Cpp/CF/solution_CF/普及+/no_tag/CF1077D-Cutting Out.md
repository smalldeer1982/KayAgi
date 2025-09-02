# Cutting Out

## 题目描述

给你一个序列 $s$，长度为 $n$.

你需要找到一个长度为 $k$ 的序列 $t$ 使得它能被最多次数地从 $s$ 中切割。

一次切割的意思是你需要对于 $t$ 序列中所有 $t_i$，在 $s$ 中找到一个跟它相同的数，并将其移除。

举例，如果 $s=[1,2,3,2,4,3,1]$，$k=3$，那么一种可行的方案是 $t=[1,2,3]$，这个子序列可以被切割两次。

- 第一次切割，你可以选择 $[1, \underline{\textbf{2}}, 3, 2, 4, \underline{\textbf{3}}, \underline{\textbf{1}}]$，移除完后 $s=[1,3,2,4]$；
- 第二次切割，你可以选择 $s=[\underline{\textbf{1}},\underline{\textbf{3}},\underline{\textbf{2}},4]$，移除完后 $s=[4]$。

你的任务是找到一个序列 $t$，能最多次数地从 $s$ 中切割它。如果有多个可行的方案，只需输出任意一种。

## 样例 #1

### 输入

```
7 3
1 2 3 2 4 3 1
```

### 输出

```
1 2 3 
```

## 样例 #2

### 输入

```
10 4
1 3 1 3 10 3 7 7 12 3
```

### 输出

```
7 3 1 3
```

## 样例 #3

### 输入

```
15 2
1 2 1 1 1 2 1 1 2 1 2 1 1 1 1
```

### 输出

```
1 1 
```

# 题解

## 作者：MatrixCascade (赞：4)

为啥都写的二分啊，这题不是一眼直接贪心吗...

设 $b[i]$ 为 i 出现的次数，维护一个 pair 的堆，把所有 $(b[i],i)$ 都 push 进去，显然可以贪心选最大的。

接下来要考虑每个数重复选的情况，发现选一次是 $b[i]$，两次是 $b[i]/2$ 依次类推，我们只需要记录一个 tim 数组记录当前这个数已经被选了多少次，每次选完在把 $\frac{b[i]}{tim[i]+1}$ push 进堆就可以了

代码（500B 不到）

```cpp
#include<bits/stdc++.h>
#define up(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
using namespace std;
int n,m,k;
int b[202020],t[202002];
priority_queue<pair<int,int>>q;
signed main()
{
	cin>>n>>k;
	up(i,1,n)
	{
		int x;cin>>x;b[x]++;
	}
	up(i,1,200000)if(b[i])q.push(make_pair(b[i],i));
	up(i,1,k)
	{
		pair<int,int>nw=q.top();
		q.pop();
		int x=nw.first,y=nw.second;
		cout<<y<<" ";
		t[y]++;q.push(make_pair(b[y]/(t[y]+1),y));
	}
}
```


---

## 作者：zsc2003 (赞：3)

2018.11.16 codeforces div3 D

### 题目大意：
给定一个长度为 $ n $ 的 $s$ 数组,你需要从中选择一个长度为 $ k $ 的 **元素可重复** 的 $t$ 子集，并且不断将该子集从 $ s $ 数组中删除，直到不能再删为止。

你需要最小化 $ s $ 数组被删除后元素的个数(**元素可重复**)，并且输出 子集 $ t $ 。

如果有多种删除方案，请输出任意一种。

### 思路

本题可以采用二分的思想。

对进行删除操作的次数进行二分。

显然存在单调性...

确定玩对什么进行二分后，难点就在于二分的 $ check $ 函数了.

$ check $ 函数部分:

尽然已经知道可以删除多少次了，那么就可以计算出来每个数在 $ t $ 数组中出现的次数。

然后将所有出现的次数和与 $ t $ 数组的大小 $ k $ 进行比较即可。

二分的复杂度为 $\Theta(log_2N)$，$check$ 函数的复杂度为$ \Theta(N)$ ， 总体复杂度为 $\Theta(Nlog_2N) $ 本题可以过的 

具体细节详见在代码中实现

### 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
    int r,s=0,c;
    for(;!isdigit(c=getchar());s=c);
    for(r=c^48;isdigit(c=getchar());(r*=10)+=c^48);
    return s^45?r:-r;
}
const int N=210000;
int n,k,l,r,mid,cha;
int a[N],num[N],tot,ans[N],cnt;
inline bool check(int x)
{
    int sum=0;
    for(int i=1;i<=tot;i++)
        sum+=num[i]/x;
    if(sum>=k)
        return 1;
    return 0;
}
int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    sort(a+1,a+1+n);//二分答案需要满足单调性
    a[0]=-1314856;//防止最初出现错误，随便敲的数，没有任何意义...
    for(int i=1;i<=n;i++)
    {
        if(a[i]==a[i-1])
            num[tot]++;//统计每一种数的出现的次数
        else
            num[++tot]=1;
    }
    unique(a+1,a+1+n)-a-1;//将a数组去重，这样unique后的a数组1~tot中每个数仅出现一次
//	for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
//	for(int i=1;i<=tot;i++)cout<<num[i]<<' ';cout<<endl;
    l=1,r=n;
    while(l<=r)//二分答案部分
    {
        mid=l+r>>1;
        if(check(mid))
        {
            l=mid+1;
            cha=mid;
        }
        else
            r=mid-1;
    }
    for(int i=1;i<=tot;i++)//记录答案
    {
        while(num[i]>=cha)
        {
            ans[++cnt]=a[i];
            num[i]-=cha;
        }
    }
    for(int i=1;i<=k;i++)//输出答案
        printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：_6_awa (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1077D)

大意是找出一个长度为 $k$ 的序列，使这个序列在原序列中出现的次数最多（这里不定序列出现的顺序）。

我们怎么判断出现的具体次数呢？这个可以用二分答案来求。当二分出答案后，再用一个桶判断能否达到要求就可以了。

由题意可知，假设一个数在原序列出现的次数为 $x$，二分答案的结果为 $m$。为了让成功可能性更高，我们肯定会让更多的数放进长度为 $k$ 的序列里，此时最佳方案为放进 $\lfloor\frac{x}{m}\rfloor$ 个。当放进的数比这个更多时，就无法出现 $m$ 次，方案就不行了。

注意：因为题目要求序列的长度只能为 $k$，所以当序列长度达到 $k$ 的时候，应停止操作——防止输出的数组长度过长。

```cpp
#include <iostream>
using namespace std;
int l,r,n,k,a[200005],b[200005],ji;
bool check(int mi)
{
    int num = 0;
    for(int i = 1;i <= 200000;i ++)
        num += b[i] / mi;//记录最大长度
    return num >= k;//判断是否可行
}
int main()
{
    cin >> n >> k;
    for(int i = 1;i <= n;i ++)cin >> a[i],b[a[i]] ++;//桶
    r = n;
    while(l < r)//二分答案
    {
        int mid = (l + r + 1) / 2;
        if(check(mid))l = mid;
        else r = mid - 1;
    }
    for(int i = 1;i <= 200000;i ++)
        while(b[i] >= l && ji < k)//输出
        {
            ji ++;
            cout << i << " ",b[i] -= l;
        }
}
```

---

## 作者：Nephren_Sakura (赞：2)

题目传送门：[link](https://www.luogu.com.cn/problem/CF1077D)

显然的，有一种暴力的做法，对每一个元素开一个桶，记录出现次数。然后枚举序列被切割了多少次。对于每一个切割次数，枚举所有的元素，计算出这个元素最多可以出现几次，最后判断序列长度是否不小于 $k$，时间复杂度 $O(N^2)$。

仔细观察题目，发现了切割次数满足单调性：若切割次数 $i$ 可以满足序列长度不小于 $k$，则 $i-1$ 也同样能满足序列长度不小于 $k$。所以可以使用二分优化第一重循环，将时间复杂度优化到 $O(N \times \log N)$ 即可通过本题。

最后输出时记得特判输出的数不超过 $k$ 个。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int n=read(),m=read(),a[1000005],maxi=-1e18,ans,mini=1e18,sum[1000005],cnt;
bool check(int x){
    int ans=0;
    for(int i=1; i<=200000; i++)
        ans+=sum[i]/x;
    return ans>=m;//序列长度是否大于等于m
}
signed main(){
    for(int i=1; i<=n; i++)
        a[i]=read();
    for(int i=1; i<=n; i++)
        sum[a[i]]++;//开桶计算
    int lt=0,rt=1e9+1;
    while(lt+1<rt){
        int mid=lt+rt>>1;
        if(check(mid))
            lt=mid;
        else
            rt=mid;
    }//二分答案
    for(int i=1; i<=200000; i++)
        for(int j=1; j*lt<=sum[i]; j++){
            cnt++;
            if(cnt>m)
                break;//特判，最后输出的数不能超过k个
            cout<<i<<' ';
        }
    return 0;
}
```

---

## 作者：little_sun (赞：2)

# 题解 CF1077D 【Cutting Out】

* 昨晚刚打的场，感触深刻啊
* 昨天打的时候死命WA16结果才发现16是$n=k$的的点
* $rp--,rating-=inf$

* 好了说正事
* 这道题我们可以枚举删除次数，发现满足单调性，果断二分
* check扫一遍$1-200000$，对于每个数i，每次将序列长度加上(i出现的次数/当前check的删除次数)，如果序列长度$\ge k$就return true;否则return false;
* 在二分时处理一下答案即可

* 其实用不着queue,但已经STL依赖症了qwq

```cpp
#include <bits/stdc++.h>

int n, k;
int a[200010], ans[200010];
int s[200010];
std::queue<int> st;

int check(int x)
{
    while(!st.empty())
        st.pop();
    for(int i = 1; i <= 200000; i++)
        for(int j = s[i] / x; j; j--)//能加的全部加进去
            st.push(i);
    if(st.size() >= k)//满足条件
    {
        for(int i = 1; i <= k; i++)
            ans[i] = st.front(), st.pop();
        return true;
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), s[a[i]]++;
    int l = 0, r = 200001;
    while (l < r)//二分
    {
        int mid = (l + r + 1) >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    for (int i = 1; i <= k; i++)
        printf("%d ", ans[i]);
    return 0;
}
```

---

## 作者：Disjoint_cat (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1077D)

## CF1077D Cutting Out

这道题一看就是**二分**啊。

把相同的数的出现次数存进一个 $cnt$ 数组中，然后二分切割的次数，当切割的次数为 $t$ 时，每个数可以提供 $\left\lfloor\dfrac{cnt_i}{t}\right\rfloor$ 个数用来切割，然后直接套二分模板就可以了。

没有任何难想的地方，时间复杂度为 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,k,s,l,r,m,cnt[N],t;
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&s);
		cnt[s]++;
	}
	l=1,r=n/k;
	while(l<=r)
	{
		m=l+r>>1,t=0;
		for(int i=1;i<=N;i++)t+=cnt[i]/m;
		if(t>=k)l=m+1;
		else r=m-1;
	}
	for(int i=1;i<=N;i++)
		while(cnt[i]>=r)
		{
			printf("%d ",i);
			k--,cnt[i]-=r;
			if(!k)return 0;
		}
	return 0;
}
```


感觉难度只有橙到黄，很好奇这道题是怎么评上紫的。

---

## 作者：Peaky (赞：0)

按照惯例，应该先有[传送门](https://www.luogu.com.cn/problem/CF1077D)。  
### 题目大意
从数组 $s$ 中选 $k$ 个数，组成一个新的数组 $t$，使得 $t$ 在 $s$ 中出现的次数最多。

### 思路
简单贪心。   
把所有元素出现的次数用一个桶数组存起来，放进大根堆里，依次取出出现次数最多的数。但是有一个问题，就是**每一个数都可以重复选**，但是如何判断重复选之后依旧能保证 $t$ 出现的次数最多呢？  
我们可以用一个数组 $st$ 统计每一个数用了多少次对于每一次多用一个用过的数，那么他总出现数就应该是 $\frac{t_i}{st_i+1}$，所以我们再把他放回大根堆里排序就可以了。
### AC code

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
priority_queue<pii> q;
int n,k,st[N],t[N],x;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>x,t[x]++;
	for(int i=1;i<=N-10;i++) if(t[i]) q.push({t[i],i});
	while(k--){
		x=q.top().y;
		cout<<x<<" ";
		st[x]++;
		q.pop();
		q.push({t[x]/(st[x]+1),x});
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：0)

### solution
不难看出切割次数是具有单调性的，所以考虑使用萌萌哒的二分。

然后了解到二分后就要解决的是 $check$ 函数的问题了。

我们拿个桶把所有数的出现次数给记录下来，然后使用二分的出来的 $mid$ 一直减去出现次数（$mid$ 指切割次数），然后如果有 $k$ 个数被成功切割了就 $l=mid+1$ 增大答案，否则 $r=mid-1$ 缩小答案。

注意覆盖答案时要在被成功切割时再覆盖。
### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,o,t,sum,a[200001],b[200001],cnt,ans[200001],mx,rl[200001];
bool check(int k){
	cnt=0;
	for(int i=1;i<=mx;i++){
		if(b[i]>=k){
			int sb=b[i];
			while(sb>=k){
				sb-=k,ans[++cnt]=i;
				if(cnt==m) return 1;
			}
		}
	}
	return cnt==m;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mx=max(mx,a[i]);
		b[a[i]]++;
	}
	int l=1,r=n;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			l=mid+1;
			for(int i=1;i<=m;i++){
				rl[i]=ans[i];
			}
		}
		else r=mid-1;
	}
	for(int i=1;i<=m;i++){
		cout<<rl[i]<<' ';
	}
	return 0;
}
//stO vanyou Orz
```

---

## 作者：zbk233 (赞：0)

## 解题思路

这道题我用的是二分的做法。

先拿样例举例：

```
10 4
1 3 1 3 10 3 7 7 12 3
```

因为 $1\le s_i\le 2\times 10^5$，所以我们显然可以用一个数组 $t$ 来保存每个数字出现的次数。

那么，对于上面的样例：$t_1=2,t_3=4,t_7=2,t_{10}=1,t_{12}=1$，其余数字都为 $0$。

接下来，对 $t$ 数组进行降序排序，因为 $t$ 数组的下标改变了，所以注意要记录好 $t$ 数组每一个元素所代表的数字。

那么，就可以将上面样例转化为：$t.sum=\{4,2,2,1,1,0,...\}$。

下标为 $t.pos=\{3,1,7,10,12,0,...\}$。

我们把保存答案的数组设为 $ans$。

我们要输出能分割次数最多的序列，而能分割的次数是由保存答案的 $ans$ 数组中出现次数最少的数决定的。

什么意思呢？

还是上面的样例，这个样例的答案，也就是 $ans$ 数组为：

```
7 3 1 3
```

而 $1$ 与 $7$ 在样例输入给出的数组中都只出现了 $2$ 次，$3$ 却出现了 $4$ 次，所以 $1$ 与 $7$ 是保存答案的 $ans$ 数组中出现次数最少的数。

所以样例输入的数组能分割的次数就为 $1$ 与 $7$ 在样例输入给出的数组中出现的 $2$ 次除以在保存答案的 $ans$ 数组中出现的 $1$ 次。

所以，要想让分割次数最多，就要让 $ans$ 数组中出现次数最少的数在样例输入中出现的次数最多。

求最小值最大，那么我们就要考虑二分答案了。

我们考虑对分割的次数进行二分，求出最后最多可以形成的序列长度，再与 $k$ 进行比较即可。

## 参考代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct node{
	int pos,sum;
}t[200005];
int n,k,len,a;
bool cmp(node x,node y){
	return x.sum>y.sum;
}
bool check(int mid){
	long long sum=0;
	for(int i=1;i<=len;i++){
		sum+=t[i].sum/mid;
	}
	return sum>=k;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(!t[a].sum) len++;
		t[a].pos=a;
		t[a].sum++;
	}
	sort(t+1,t+200001,cmp);
	int l=1,r=200000,mid,ans;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}else{
			r=mid-1;
		}
	}
	for(int i=1;i<=len;i++){
		for(int j=1;j<=t[i].sum/ans&&k>0;j++){
			k--;
			cout<<t[i].pos<<' ';
		}
	}
	return 0;
}
```


---

