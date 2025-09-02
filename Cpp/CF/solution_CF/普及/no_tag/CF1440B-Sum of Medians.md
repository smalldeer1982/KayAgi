# Sum of Medians

## 题目描述

A median of an array of integers of length $ n $ is the number standing on the $ \lceil {\frac{n}{2}} \rceil $ (rounding up) position in the non-decreasing ordering of its elements. Positions are numbered starting with $ 1 $ . For example, a median of the array $ [2, 6, 4, 1, 3, 5] $ is equal to $ 3 $ . There exist some other definitions of the median, but in this problem, we will use the described one.

Given two integers $ n $ and $ k $ and non-decreasing array of $ nk $ integers. Divide all numbers into $ k $ arrays of size $ n $ , such that each number belongs to exactly one array.

You want the sum of medians of all $ k $ arrays to be the maximum possible. Find this maximum possible sum.

## 说明/提示

The examples of possible divisions into arrays for all test cases of the first test:

Test case $ 1 $ : $ [0, 24], [34, 58], [62, 64], [69, 78] $ . The medians are $ 0, 34, 62, 69 $ . Their sum is $ 165 $ .

Test case $ 2 $ : $ [27, 61], [81, 91] $ . The medians are $ 27, 81 $ . Their sum is $ 108 $ .

Test case $ 3 $ : $ [2, 91, 92, 95], [4, 36, 53, 82], [16, 18, 21, 27] $ . The medians are $ 91, 36, 18 $ . Their sum is $ 145 $ .

Test case $ 4 $ : $ [3, 33, 35], [11, 94, 99], [12, 38, 67], [22, 69, 71] $ . The medians are $ 33, 94, 38, 69 $ . Their sum is $ 234 $ .

Test case $ 5 $ : $ [11, 41] $ . The median is $ 11 $ . The sum of the only median is $ 11 $ .

Test case $ 6 $ : $ [1, 1, 1], [1, 1, 1], [1, 1, 1] $ . The medians are $ 1, 1, 1 $ . Their sum is $ 3 $ .

## 样例 #1

### 输入

```
6
2 4
0 24 34 58 62 64 69 78
2 2
27 61 81 91
4 3
2 4 16 18 21 27 36 53 82 91 92 95
3 4
3 11 12 22 33 35 38 67 69 71 94 99
2 1
11 41
3 3
1 1 1 1 1 1 1 1 1```

### 输出

```
165
108
145
234
11
3```

# 题解

## 作者：Retired_lvmao (赞：4)

### 题意  :
给定 $n\times k$ 个正整数，要求将这些数分成 $k$ 组，每组 $n$ 个，并且希望每一组第 $\lceil\frac{n}{2}\rceil$ 大的数的和尽可能大，请求出这个和。
### 思路  :
我们考虑到，这 $k$ 个数显然是越大越好，于是就想到了一个贪心的做法，我们先将这 $n\times k$ 个数排序。分组的时候，每一组都从未选的大的一侧选取 $\lceil\frac{n}{2}\rceil$ 个数，剩下的数都从小的一侧选，这样可以使得和最大。选择的复杂度是 $O(k)$，因此本题的时间复杂度为 $O(p \log p)$ 且 $p=n\times k$。
 ### 代码  :
 ```
 #include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,s[200010];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&k);
		int tot=0;
		for(int i=1;i<=k;i++)
		{
			for(int j=1;j<=n;j++)
				scanf("%lld",&s[(i-1)*n+j]);
		}
		sort(s+1,s+n*k+1); 
		int hd=1,tl=n*k;
		while(hd<=tl)
		{
			if(n&1)
			{
				hd+=n/2;
				tl-=n/2+1;
				tot+=s[tl+1];
			}
			else
			{
				hd+=n/2-1;
				tl-=n/2+1;
				tot+=s[tl+1];
			}
		}
		printf("%lld\n",tot);
	}
}
 ```

---

## 作者：我梦见一片焦土 (赞：1)

#### 这是本蒟蒻第一次写题解，球球管理员通过吧！

------------
# [题目传送门](https://www.luogu.com.cn/problem/CF1440B)

------------
# 题意：
划分序列，求每个块中的中位数之和，构造使得最大。

------------
# 思路：
1. $n = 2$ 的时候，$n \div 2 = 1$，贪心从前往后取 $ 2 $ 个，不浪费后面的大数。

2. $n \ge 2$ 且 $n \neq 2$ 的时候，比如 $n = 3$，前取 $ 1 $ 个，后取 $ 2 $ 个，贪心最大。

3. $n = 4$的时候，$n \div 2 = 2$;所以要前面 $ 1 $ 个，后面 $ 3 $ 个。中位数在大的一边。

4. $n \div 5$ 的时候 $n \div 2 = 3$,前面 $ 2 $ 个，后面 $ 3 $ 个。中位数在大的一边。

最后 $O ( n )$ 后往前扫。

------------
代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m,k,c,cnt,ans,a[1000001],s[1001][1001];
signed main(){
	cin>>t;
	while(t--){
		ans=cnt=0;
		memset(a,0,sizeof(a));
		cin>>m>>k;
		n=m*k;
		if(m%2==1){
			c=m/2+1;
		}else{
			c=m/2;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=k;i++){
			for(int j=1;j<c;j++){
				cnt++;
			}
		}
		for(int i=1;i<=k;i++){
			for(int j=c;j<=m;j++){
				cnt++;
				if(j==c){
					ans+=a[cnt];
				}
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

------------

完结撒花~

---

## 作者：David_H_ (赞：1)

这题打 cf 的时候因为太晚了所以没打，现在回来补一下题解。

题意就不写了。

我们先明确一下：

**对于每一个长度为 $\textbf{\textit{n}}$ 的序列，最大的 $\left\lceil\displaystyle\frac{\textbf{\textit{n}}}{\bf 2}\right\rceil$ 个数不可能成为中位数。**

证明：记这个序列为 $a_i(i\le n)$，满足 $\forall i<j,a_i<a_j$，那么，如果前 $\displaystyle\left\lceil\frac{n}{2}\right\rceil$ 个数中，任意一个数成为了中位数，不妨设为 $a_k$，那么对于 $a_k$，显然至多有小于 $\left\lceil\displaystyle\frac{n}{2}\right\rceil$ 个数大于它，不满足其为 $a_i$ 中第 $\left\lceil\displaystyle\frac{n}{2}\right\rceil$ 个数的条件，证毕。

那么利用这个思路，每一次扔掉当前最大的 $\left\lceil\displaystyle\frac{n}{2}\right\rceil$ 的数，留下一个，最后输出总和就好了。

时间复杂度差不多（经过优化）可以达到 $O(Tk)$，足以通过此题。

代码看其他题解的（

---

## 作者：nytyq (赞：0)

## 分析

考虑到排序之后进行选取。

本质实际是贪心，容易证明，不做赘述。

考虑逆向思维求解，我们知道在如果要取 $n$ 个数的话，则选取大的 $\lceil \frac{n}{2} \rceil$ 个，剩下的从小的里面选择。

令 $L=n \times k$，则考虑到排序的复杂度最高，则总体复杂度为 $O(L\log L)$。

## ACcode

```
#include<bits/stdc++.h>

using namespace std;

int n,k;

int t;

int a[1000005];

void solve(){
	cin>>n>>k;
	int L=n*k;
	for(int i=1;i<=L;i++)cin>>a[i];
	sort(a+1,a+1+L);
	int h=1,t=L;
	int sum=0;
	while(h<=t){
		if(n%2==1){
			h+=n/2;
			t-=n/2+1;
			sum+=a[t+1];
		}
		else{
			h+=n/2-1;
			t-=n/2+1;
			sum+=a[t+1];
		}
	}
	cout<<sum<<endl;
} 
int main(){
	cin>>t;
	while(t--) solve();
	return 0;
}
 
```

---

## 作者：charleshe (赞：0)

这是一道贪心的题目。

根据题目要求，要让每一组的第 $\lceil\dfrac{n}{2}\rceil$ 项最大，我们可以先对数组进行排序，再分奇偶来讨论：

- $n$ 是奇数：则每一组的 $\lceil\dfrac{n}{2}\rceil$ 项就是第 $\dfrac{n+1}{2}$ 项，从数组末尾取 $\dfrac{n+1}{2}$ 个数，开头取 $\dfrac{n-1}{2}$ 项，并把取前的倒数 $\dfrac{n+1}{2}$ 项加入总量（因为这个数就是取出的数中第 $\lceil\dfrac{n}{2}\rceil$ 大的）。

- $n$ 是偶数：则 $\lceil\dfrac{n}{2}\rceil$ 项就是整个数列中的第 $\dfrac{n}{2}+1$ 项（注意要有一个加一，不然第 $\lceil\dfrac{n}{2}\rceil$ 项会被选到较小的数中）。

至于为什么要取很多非常小的数，那是用来垫底的，只要有  $\left \lfloor \dfrac{n}{2}  \right \rfloor$ 个数就行了（这样可以保证下一组数中第 $\lceil\dfrac{n}{2}\rceil$ 项尽量大）。

容易发现，上述步骤可以用队列实现，但队列常数太大，因此我选择了数组模拟队列。

注意事项：

- 要开长整型。

- 给出的数组不一定有序，因此需要排序。

- 数组长度是 $n \times k$，而不是 $n$ 或 $k$，数组需要开大点。

考虑了这些，代码便好写了。

```cpp
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
int n,k,y;
int a[1000001];
signed main(){
	cin>>y;
	while(y--){
		cin>>n>>k;
		int p=n*k;//p才是真正的数组长度
		for(int i=1;i<=p;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1);//进行升序排序
		int hd=1,tl=p;
		int ans=0;
		int c,d;
		if(n%2==0) c=n/2+1,d=n/2-1;
		else c=n/2+1,d=n/2;
		for(int i=1;i<=k;i++){//模拟队列
			hd+=d;
			tl-=c;
			ans+=a[tl+1];
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Ba_creeper (赞：0)

#### 题目分析
算法：贪心，暴力。

题目需要找到每组数中，中位数所在的位置。如果中位数不是第一个数，那么就用最小的数放在前面占位，剩下的位置从小到大排序，分成 $k$ 组，每组中的第一个数就是需要找到的中位数。

不要忘记开 `long long`。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;

ll T;
ll a[1000001];

int main()
{
	T=read();
	while(T--)
	{
		memset(a,0,sizeof a);
		ll n=read(),k=read(),ans=0;
		if(n==1)
		{
			for(ll i=1;i<=n*k;++i)
			{
				ll x=read();
				ans+=x;
			}
			printf("%lld\n",ans);
			continue;
		}
		ll num=(n+1)/2; //中位数的个数
		//cout<<num<<endl;
		for(int i=1;i<=n*k;++i)
		{
			a[i]=read();
		}
		sort(a+1,a+(n*k)+1);
		ll first=(num-1)*k+1;
		while(first<=n*k)
		{
			ans+=a[first];
			first+=(n-num+1);
		}
		printf("%lld\n",ans);
		
		
		
	}
	return 0;
}
```

---

## 作者：PragmaGCC (赞：0)

贪心 + 一点结论题。

题目大意就是要你把长为n*k的序列分成k段，每段长n，求k段的中位数的和的最小值。

乍一看没思路，那么我们不妨考虑：怎样的数**不可能**成为中位数？

答案显然：最大的 $\frac{n}{2}$ 个数不可能成为中位数。

那么，剩下的数中的最大的数就是可能的最大中位数。

我们用前面较小的数与这几个数补成一个序列，删掉，则剩下的数又构成刚才的那个问题。

那样，我们只需要不断用这样的方法找到k个中位数即可。

证明：

如果我们取了更小的一个数作为中位数，则更大的那个在下一个问题中就取代了这个较小数的位置，不会改变下一组的中位数。这样就会使答案变小。

tip : 答案记得开 `long long`

```cpp
#include <cstdio>
int read() {
    register int n = 0;
    register char ch = getchar();
    bool f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = 0;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        n = (n << 3) + (n << 1) + (ch ^ '0');
        ch = getchar();
    }
    return f ? n : -n;
}
const int N = 1005;
int a[N*N];
void work() {
    int n = read(), k = read();
    int blo = n / 2, siz = n * k, tot = 0;
    for (int i=1; i<=siz; i++) a[i] = read();
    long long ans = 0;
    for (int i=siz - blo; i>=blo; i -= blo + 1) {
        ans += 1ll * a[i];
        tot++;
        if (tot == k) break;
        //printf("%d\n", a[i]);
    }
    printf("%lld\n", ans);
}
int main(void) {
    int T = read();
    while(T--) work();
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
给你 $n\times k$ 个数，将这些数分成 $k$ 组，每组 $n$ 个数，最大化所有组中第 $\lceil\frac{n}{2}\rceil$ 个数的和。
# 分析
贪心。先用最小的把第 $\lceil\frac{n}{2}\rceil$ 个数之前的全部填满，当遇到一个第 $\lceil\frac{n}{2}\rceil$ 位后将其后面的数把该组填满即可。需要开 `long long`。
# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read()
{
    char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	int res=0;
    while(ch>='0'&&ch<='9')
    {
    	res=res*10+ch-'0';
		ch=getchar();
    }
    return res;
}
int T,n,k,a[1000001];
ll ans;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		k=read();
		int pos=(n+1)/2;
		ans=0;
		for(int i=1;i<=n*k;++i)
			a[i]=read();
		for(int i=(pos-1)*k+1;i<=n*k;i+=n-pos+1)
			ans+=a[i];
		printf("%lld\n",ans);
	}
	return 0;
}

```


---

## 作者：fisheep (赞：0)

## 题意：

给$n * k$个数，分为$k$组每组$n$个数，求每组中位数的最大值。输出$k$个中位数之和。

## 想法：
找到每组中位数所在的位置，然后前面用最小的数去填充，剩下的位置按照递增的序列平均分成$k$组，每组第一个数就是中位数。

## Code:
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int a,t;
int n,k;
int main() {
	t=read();
	while(t--) {
		n=read(),k=read();
		int la;
		if(n&1) la=n/2+1;
		else la=n/2;
		long long sum=0,cnt=0;
		for(int i=1; i<=n*k; i++) {
			a=read();
			if((la-1)*k<i) {
				cnt++;
				if(cnt==1)sum+=a;
				if(cnt+la>n)cnt=0;
			}
		}
		printf("%lld\n",sum);
	}
	return 0;

}
```

---

