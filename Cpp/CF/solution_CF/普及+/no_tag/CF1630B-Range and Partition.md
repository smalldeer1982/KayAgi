# Range and Partition

## 题目描述

Given an array $ a $ of $ n $ integers, find a range of values $ [x, y] $ ( $ x \le y $ ), and split $ a $ into exactly $ k $ ( $ 1 \le k \le n $ ) subarrays in such a way that:

- Each subarray is formed by several continuous elements of $ a $ , that is, it is equal to $ a_l, a_{l+1}, \ldots, a_r $ for some $ l $ and $ r $ ( $ 1 \leq l \leq r \leq n $ ).
- Each element from $ a $ belongs to exactly one subarray.
- In each subarray the number of elements inside the range $ [x, y] $ (inclusive) is strictly greater than the number of elements outside the range. An element with index $ i $ is inside the range $ [x, y] $ if and only if $ x \le a_i \le y $ .

Print any solution that minimizes $ y - x $ .

## 说明/提示

In the first test, there should be only one subarray, which must be equal to the whole array. There are $ 2 $ elements inside the range $ [1, 2] $ and $ 0 $ elements outside, if the chosen range is $ [1, 1] $ , there will be $ 1 $ element inside ( $ a_1 $ ) and $ 1 $ element outside ( $ a_2 $ ), and the answer will be invalid.

In the second test, it is possible to choose the range $ [2, 2] $ , and split the array in subarrays $ (1, 3) $ and $ (4, 4) $ , in subarray $ (1, 3) $ there are $ 2 $ elements inside the range ( $ a_2 $ and $ a_3 $ ) and $ 1 $ element outside ( $ a_1 $ ), in subarray $ (4, 4) $ there is only $ 1 $ element ( $ a_4 $ ), and it is inside the range.

In the third test, it is possible to choose the range $ [5, 5] $ , and split the array in subarrays $ (1, 4) $ , $ (5, 7) $ and $ (8, 11) $ , in the subarray $ (1, 4) $ there are $ 3 $ elements inside the range and $ 1 $ element outside, in the subarray $ (5, 7) $ there are $ 2 $ elements inside and $ 1 $ element outside and in the subarray $ (8, 11) $ there are $ 3 $ elements inside and $ 1 $ element outside.

## 样例 #1

### 输入

```
3
2 1
1 2
4 2
1 2 2 2
11 3
5 5 5 1 5 5 1 5 5 5 1```

### 输出

```
1 2
1 2
2 2
1 3
4 4
5 5
1 1
2 2
3 11```

# 题解

## 作者：Morgen_Kornblume (赞：15)

## 前言

赛时把问题想复杂没有搞出来真是太气人了！

~~（实际是我太逊）~~

~~（洛谷最菜金钩就是我）~~

**对于一个问题，如果发现它的具体形式考虑起来非常复杂，那么不妨把具体的形式扔掉，寻找它背后隐藏的规律和性质，回到最根本的问题和要求中去，等确定了这些问题的答案，再反过来去确定具体的形式。**

## 正题

对于这道题，**最根本的问题**是最小化的 $(y-x)$ ，而**具体的形式**是如何划分整个序列。

我们可以发现，如果同时考虑这两个问题，事情会变得非常复杂，难以下手。

所以我们不妨暂且扔下具体的形式，去考察最根本的问题。

**性质**：

划分为 $k$ 段时，在 $[x,y]$ 内的数总体上至少要比在此区间以外的数多 $k$ 个。

**证明**：

因为对于每个段，在区间里的数严格大于不在区间里的数，所以至少大 $1$，共 $k$ 段，所以至少大 $k$。

于是我们就得到这样一种做法：

先将整个序列从小到大排序，然后用一个大小为 $n- \lfloor (n-k)/2 \rfloor$ 的滑动窗口去检测，窗口两端的数就是 $[x,y]$，取 $(y-x)$ 的最小值即可确定 $[x,y]$。

推理一下可以发现，让每一段都多一个，可以使滑动窗口尽可能小，这样 $(y-x)$ 也会相应更小，同时这样的一组 $[x,y]$ 一定有可行的划分方案。

最后构造方案时也是每一段多一个就划开即可。

注意细节。

这里是代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int T;

int n,k;

const int maxn=200010;

int a[maxn];
int at[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	
	cin>>T;
	
	while(T--){
		
		cin>>n>>k;
		
		for(int i=1;i<=n;i++){
			cin>>a[i];
			at[i]=a[i];
		}
		
		sort(a+1,a+1+n);
		
		int ans=0x7fffffff;
		int inc=n-(n-k)/2;
		int rx,ry;
		for(int i=1;i<=n&&i+inc-1<=n;i++){
			//ans=min(a[i+inc-1]-a[i],ans);
			if(a[i+inc-1]-a[i]<ans){
				ans=a[i+inc-1]-a[i];
				rx=a[i],ry=a[i+inc-1];
			}
		}
		cout<<rx<<" "<<ry<<endl;
		int tot=0;
		int st=1;
		int cnt=1;
		for(int i=1;i<=n;i++){
			if(rx<=at[i]&&at[i]<=ry)tot++;
			else tot--;
			if(tot==1){
				cout<<st<<" ";
				if(cnt==k){
					cout<<n<<endl;
					break;
				}
				else{
					cout<<i<<endl;
					tot=0;cnt++;st=i+1;
				}
			}
		}
	}
	
	return 0;
}
```

P.S. ：感谢 @DYF_dyf 凌晨一点钟的**亲切**教导

---

## 作者：XL4453 (赞：6)

### 解题思路：

挺巧妙的一个构造。

---
首先发现要求在区间中的数要比在区间外的数至少多 $k$ 个，否则一定无法构造，这是显然的。

设在区间内的数为 $x$，有 $x-k\ge n-x$，解得 $x\ge \dfrac{n+k}{2}$，由于 $x$ 为整数，需要取上整。


直接按照 $x$ 进行一个尺取即可求出最小的区间。

---
但是求出来的值是可能的最小值，考虑构造一组解以证明可行性。

这里直接按照上面求值得到方法构造，即一遇到有满足条件的区间立即划为一个区间，如果有多余的区间，直接合并到一起就行了。

---
但是直接给出这个构造并不能说明一定存在合法结果，接下来需要~~交一发看看~~证明存在性。

原问题也就是需要保证有至少 $k$ 个区间被划分出来（合并任意两个区间依然是一个合法的区间）。

转化问题，不妨将在区间中的数设为 $1$，不在的设为 $-1$，也就是要求有至少 $k$ 个区间权值和大于等于 $1$。

这里希望分出的区间尽可能多，而且任意一个权值和比 $1$ 大的区间一定能分成若干组权值和等于 $1$ 的区间，所以不妨直接将整个序列分成不少于 $k$ 个权值和等于 $1$ 的区间。

再利用前缀和的思想，在每一个权值和为 $1$ 的区间结尾处取前缀和，则前缀和一定是一个 $a_i=i$ 的至少为 $k$ 项序列，反之，如果能找到一个样的序列，则直接按照这个划分就能得到一个满足条件的序列。

最后一步就简单了，直接不断删除相邻的 $-1$ 和 $1$，最后得到至少长度为 $k$ 的全是 $1$ 的序列，记下这些数，还原即可得到所求序列。

代码实现的时候建议按照原方法构造。

---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,k,a[200005],b[200005],ans,l,r;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		int len=(n+k+1)/2;
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
		
		ans=2147483647;
		sort(a+1,a+n+1);
		for(int i=len;i<=n;i++){
			if(a[i]-a[i-len+1]<ans){
				ans=a[i]-a[i-len+1];
				l=a[i-len+1];
				r=a[i];
			}
		}
		
		printf("%d %d\n",l,r);
		int cnt1=0,cnt2=0,last=1,cnt=0;
		for(int i=1;i<=n;i++){
			if(b[i]<=r&&b[i]>=l)cnt1++;
			else cnt2++;
			if(cnt1>cnt2&&cnt<k-1){
				printf("%d %d\n",last,i);
				last=i+1;cnt1=cnt2=0;cnt++;
			}
		}
		printf("%d %d\n",last,n);
	}
	return 0;
}
```


---

## 作者：Guizy (赞：2)

### CF1630B Range and Partition 题解

先考虑最小化 $(y-x)$ 怎么做。

考虑一个双指针。

我们发现想要将数组划分成满足要求的 $k$ 段，就要使在区间内的元素个数大于等于区间外的元素个数加 $k$。

因为每个区间至少大 $1$，$k$ 个区间就至少大 $k$。

对于一个左端点 $i$，我们用一个 `while` 循环计算这个区间的右端点 $j$ 最小到哪里可以满足要求。

时间复杂度 $O(n)$。

```cpp

bool check(int l, int r)
{
    int in = cnt[r] - cnt[l - 1];
    return 2 * in >= n + k;
    //由 in >= n - in + k 解得
}

// 双指针算出 [x,y]:
for (int i = 1, j = 0; i <= n && j <= n; i++)
{
    if (j < i) j = i;//j >= i
    while (j <= n && !check(i, j)) j++;
    if (j <= n && j - i < minn)//更新答案
    x = i, y = j, minn = j - i;
}//最后 [x,y] 即为所求.
```

至于划分方案直接贪心求即可。

当在范围 $[x,y]$ 以内的元素个数大于在范围 $[x, y]$ 以外的元素个数时，就立即新开一段区间。

```cpp
int l = 0, r = 0;
while (k--)
{
    r++, l = r;
    int sum = inrange(a[r]);
    while (sum <= 0)
    sum += inrange(a[++r]);
    if (k == 0)
    r = n;
    cout << l << " " << r << "\n";
}
```

[AC Code](https://www.luogu.com.cn/paste/er6vbl34)

---

## 作者：Cure_Wing (赞：2)

[CF1630B Range and Partition](https://www.luogu.com.cn/problem/CF1630B)

### 思路

看到最小值想到二分，于是对 $y-x$ 进行二分。

为什么可以二分？显然，$y-x$ 越大，在其它条件一定时，所覆盖的数肯定是越大的，也就越有可能多于不在范围内的数。

考虑符合条件的 $[x,y]$ 的必要条件是什么。设 $a_i$ 表示分出的第 $i$ 段中在 $[x,y]$ 范围内的数的个数， $b_i$ 表示分出的第 $i$ 段中不在 $[x,y]$ 范围内的数的个数，则 $a_i\ge b_i+1$，也就是 $\sum\limits_{i=1}^ka_i\ge\sum\limits_{i=1}^k(b_i+1)=\sum\limits_{i=1}^kb_i+k$。可以理解，只要满足前面的不等式，一定存在合法的划分方案。所以二分时可以暴力枚举值域左端点，统计符合条件的数的个数，然后判断是否符合上述式子。

接下来就是如何给出方案。考虑最省的方案，除去第 $k$ 个区间，前面 $(k-1)$ 个区间都让 $a_i=b_i+1$。此时开个 $cnt$ 维护 $a_i-b_i$，当 $b_i>0$ 且 $cnt=1$ 时，划分一段；而当 $b_i=0$ 时，考虑在这里划分能不能使后面仍然满足必要条件，能就划分。如果已经划分到 $(k-1)$ 段了，那么剩余部分自动成为第 $k$ 段。

我写的时候对 $\sum\limits_{i=1}^ka_i$ 取了个最大值，应该没什么必要。

时间复杂度 $O(n\log n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=200005;
int t,n,k,a[N],b[N];
inline bool check(int x){
    int t=1,cnt=0;
    for(int i=1;i+x<=n;++i){
        int p=b[i+x]-b[i-1];
        if(p>=n-p+k) return 1;//上面说的判断
    }
    return 0;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    for(cin>>t;t--;){
        cin>>n>>k;
        for(int i=1;i<=n;++i) b[i]=0;//多测不清空，爆零两行泪。
        for(int i=1;i<=n;++i){cin>>a[i];++b[a[i]];}
        for(int i=1;i<=n;++i) b[i]+=b[i-1];
        int l=0,r=n-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)) r=mid-1;
            else l=mid+1;
        }
        int w=1,cnt=0,d=0,la=1,used=0,count=0,c2=0,c3=0;bool flag=0;
        //w:值域区间左端点,cnt如上文所说,d为已经划分了多少段,la表示这一段的左端点,used/c3为在/不在值域区间内用过的数个数;
        //count/c2为当前段内在/不在值域区间数的个数,flag为是否含有不在值域区间内的数。
        for(int i=1;i+l<=n;++i){
            int p=b[i+l]-b[i-1];
            if(p>=n-p+k){w=i;break;}
        }
        cout<<w<<' '<<w+l<<'\n';
        for(int i=1;i<=n;++i){
            if(w<=a[i]&&a[i]<=w+l){++cnt;++count;}
            else{--cnt;flag=1;++c2;}
            if(d+1<k&&(cnt==1&&flag||cnt>0&&b[w+l]-b[w-1]-used-1>=b[n]-b[w+l]+b[w-1]-c3+k-d-1)){
            //b[w+l]-b[w-1]-used-1:剩下的a[i]之和
            //b[n]-b[w+l]+b[w-1]-c3+k-d-1:剩下的b[i]之和
                cout<<la<<' '<<i<<'\n';used+=count;c3+=c2;
                c2=count=cnt=flag=0;++d;la=i+1;
                if(d==k-1){
                    cout<<i+1<<' '<<n<<'\n';
                    ++d;
                    break;
                }
            }
        }
        if(d==k-1) cout<<la<<' '<<n<<'\n';
    }
    return 0;
}
```

---

## 作者：huhexuan (赞：1)

很有趣的题！

易看出此序列在范围中的数至少要比在范围外的数多 $k$ 个，这样便一定有解。

设该序列在范围内的数的个数为 $len$，则范围外为 $n-len$，由题意可得，$len-k \ge n-len$，即 $len \ge (n+k) \div 2$ 当然是上取整。

之后我们发现，题目要求的 $x$ 和 $y$ 一定为给定序列中的数，证明考虑反证。

若 $x$ 或 $y$ 不在序列中，则一定有一种调整方式，使它们在序列中且包含数字个数不变，长度却更小，这是显然的。

于是我们考虑将 $(n+k) \div 2$ 作为区间长度，将给定序列排序，滑动窗口即可。

至于输出方案，很简单，这里不再赘述。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
//sum>=(n+k)/2（上取整） 
int n,a[2000005],t,k,b[2000005],ans=9e18;
signed main()
{
 	cin>>t;
 	while(t--)
 	{
 		ans=9e18;
 		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
		sort(a+1,a+n+1);
		int len=(n+k+1)/2;
		int resx=0,resy=0;
		for(int i=1;i+len-1<=n;i++)
		{
			if(a[i+len-1]-a[i]<ans) ans=a[i+len-1]-a[i],resx=a[i],resy=a[i+len-1];
		}
		cout<<resx<<" "<<resy<<"\n";
		int last=1,sum=0,cnt1=0,cnt2=0;
		for(int i=1;i<=n;i++)
		{
			if(b[i]>resy||b[i]<resx) cnt1++;
			else cnt2++;
			if(cnt1<cnt2&&sum!=k-1)
			{
				sum++;
				cout<<last<<" "<<i<<"\n";
				last=i+1,cnt1=0,cnt2=0;
			}
		}
		cout<<last<<" "<<n<<"\n";
	}
	return 0;
}
```

---

## 作者：lgx57 (赞：1)

非常妙的好题。

首先容易发现 $[x,y]$ 满足要求的必要条件是：在 $[x,y]$ 中的数的个数比不在 $[x,y]$ 的数的个数至少多 $k$。（每个区间都至少多一个）。可以用二分找出最小的 $y-x$。下面我们都假定已经求出了 $x$ 和 $y$。

然后我们需要发现一个结论：这个必要条件同时也是充分条件。

证明：我们令 $b_i=\begin{cases} 1 & l \le a_i \le r \\ -1 & \text{otherwise} \end{cases}$，然后 $sum_i=\displaystyle\sum_{j=1}^i b_i$。易知 $sum_0=0,sum_n \ge k$，那么由离散的介值定理得必然存在 $sum_j=1,2,\cdots,k$，即为长度为 $k$ 的**严格**上升子序列，且可以通过调整使得最后一个元素一定为 $sum_n$。那么每一段的和均 $>0$，满足要求，证毕。

接下来就简单了。我们找到一个长度为 $k$ 的**严格**上升子序列，最后一个元素一定为 $sum_n$。这件事情很简单，只要去掉 $sum_n$，把前面的小于 $sum_n$ 的数拿出来找一个长度为 $k-1$ 的上升子序列即可。

```cpp
bool check(int x){
	for (int i=1;i+x<=n;i++){
		int j=i+x;
		int cnt=sum[j]-sum[i-1];
		int la=n-cnt;
		if (cnt-la>=k) return 1;
	}
	return 0;
}
struct node{
	int x,id;
}b[N],dp[N];
void sol(){
	cin>>n>>k;
	for (int i=1;i<=n;i++) sum[i]=0;
	for (int i=1;i<=n;i++) cin>>a[i],sum[a[i]]++;
	for (int i=1;i<=n;i++) sum[i]+=sum[i-1];
	int L=0,R=n-1,Ans=0;
	while (L<=R){
		int mid=(L+R)>>1;
		if (check(mid)) Ans=mid,R=mid-1;
		else L=mid+1;
	}// 二分找出 x 和 y
	int l=0,r=0;
	for (int i=1;i+Ans<=n;i++){
		int j=i+Ans;
		int cnt=sum[j]-sum[i-1];
		int la=n-cnt;
		if (cnt-la>=k){
			l=i,r=j;
			break;
		}
	}
	cout<<l<<' '<<r<<endl;
	for (int i=1;i<=n;i++){
		if (l<=a[i]&&a[i]<=r) sum[i]=1;
		else sum[i]=-1;
	}
	for (int i=1;i<=n;i++) sum[i]+=sum[i-1];
	int x=sum[n];
	int m=0;
	for (int i=1;i<=n;i++){
		if (sum[i]<x&&sum[i]>0) b[++m]={sum[i],i};//把前面的小于 sum[n] 的数拿出来
	}
	int cnt=0;
	for (int i=1;i<=m;i++){
		if (dp[cnt].x<b[i].x) dp[++cnt]=b[i];
		else{
			int L=0,R=cnt+1,Ans=0;
			while (L<=R){
				int mid=(L+R)>>1;
				if (dp[mid].x>=b[i].x) Ans=mid,R=mid-1;
				else L=mid+1;
			}
			if (b[i].x<dp[Ans].x) dp[Ans]=b[i];
		}
	}//求 LIS
	vector<int> ans;
	for (int i=1;i<k;i++) ans.pb(dp[i].id);
	ans.pb(n);
	int la=1;
	for (int x:ans){
		cout<<la<<' '<<x<<endl;
		la=x+1;
	}
}
```

---

## 作者：DarkMoon_Dragon (赞：1)

考虑给出 $[x,y]$，如何求出一种合法方案

把在 $[x,y]$ 范围内的数看做 1，不在范围内的数看做 -1，对于 $\sum _l ^r a_i$，如果严格大于零即合法。设前缀和数组 sum，$sum_r-sum_{l-1}>0 \implies sum_r>sum_{l-1}$。而当前区间的左端点减一 $l_i-1$ 即为上一个区间的右端点 $r_{i-1}$。即要求每个区间的右端点严格大于上一个区间的右端点，即求最长严格上升子序列，并且以最后一个数 $sum_n$ 结尾。

考虑这个前缀和子序列的特殊性，每次变化最多为 $\pm 1$，所以只要 $sum_n \ge k$，一定能找到 $k$ 个数，使得这 $k$ 个右端点被找到。这样就解决了固定 $[x,y]$ 的问题。至此，我们得到一个结论为 $sum_n \ge k$，则问题一定有解。而 $sum_n$ 的实际意义为，所有满足 $x\le a_i\le y$ 的个数减去不满足条件的个数。

我们可以推出如下公式

$$
f(a_i) = 
\begin{cases}
1, x\le a_i \le y; \\
-1, a_i<x\;|\;a_i>y.
\end{cases}
\\
sum_n \ge k \\
\sum f(a_i) \ge k \\
\sum -1+2\cdot [x \le a_i \le y] \ge k \\ 
\sum [x \le a_i \le y] \ge \left\lceil \frac{n+k}{2} \right\rceil
$$

即满足在范围内的数字个数 $\ge \left\lceil \frac{n+k}{2} \right\rceil $ 即可，不妨设个数就是 $\left\lceil \frac{n+k}{2} \right\rceil\le n$. 贪心地，满足 $y-x$ 尽量小，直接尺取法即可。

细节：

- 尺取法时，相同的数不用跳掉，跳掉也没问题，只要保证区间长度大于等于$(n+k)/2$ 即可.
- 注意边界，前缀和相当于是区间右端点，所以下标从 1 开始

尺取法算出 $x,y$ 后，我们在利用上面的贪心思想，因为前缀和的新 max 一定是单调递增的，所以每次新出现 max 输出下标即可


```cpp
const int N = 2e5 + 56;
int sum[N], a[N], b[N];
int pos[N];
int main() {
    int T = read();
    while (T--) {
        // puts("Input:");
        int n = read(), k = read();
        int len = ceil(double(n + k) / 2);
        for (int i = 1; i <= n; ++i) {
            a[i] = b[i] = read();
            pos[i] = 0;
        }
        sort(b + 1, b + 1 + n);
        int minn = 1e9, x, y;
        for (int l = 1, r = l + len - 1; r <= n; l++, r = l + len - 1) {
            if (b[r] - b[l] < minn) {
                y = b[r];
                x = b[l];
                minn = b[r] - b[l];
            }
        }
        // puts("Output");
        cout << x << ' ' << y << endl;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] + (x <= a[i] && a[i] <= y ? 1 : -1);
            if (sum[i] > 0 && !pos[sum[i]]) pos[sum[i]] = i;  // 注意下标负数！
        }
        pos[sum[n]] = n;
        int las = 1;
        for (int i = sum[n] - k + 1; i <= sum[n]; ++i) {
            cout << las << ' ' << pos[i] << endl;
            las = pos[i] + 1;
        }
        // puts("---------");
    }
}
// 1 RE，下标负数
// 2 AC
```


---

## 作者：vectorwyx (赞：1)

好题啊好题，属实是把我拿捏了。 

先考虑固定了 $[x,y]$ 咋做，如果把在 $[x,y]$ 里的数看做 $+1$，不在的看做 $-1$，那么问题变为能否将原数组划分成恰好 $k$ 个和大于零的连续子段。转为前缀和，即前缀和序列是否存在一个长度为 $k$ 且开头元素 $>0$ 、以第 $n$ 个位置为结尾的上升子序列。

dp？不不不，~~格局太小了~~。由于数组内的元素只有 $±1$，所以前缀和序列的变化是连续的。那么，如果某个位置出现了 $x(x>0)$，那在该位置之前一定存在一个值为 $x-1$ 的位置。所以以第 $n$ 个位置为结尾、开头元素 $>0$ 的最长上升子序列的长度一定等于 $S_n$，即整个序列元素之和！所以如果全局在 $[x,y]$ 范围内的数比不在其范围内的数多至少 $k$ 个就一定可以，否则不可以。记录每个值出现的次数尺取 $[x,y]$ 即可。复杂度 $O(n)$。

代码如下：
```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')fh=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=1e6+5;
int a[N],b[N],n,k;

void solve(){
	cin>>n>>k;fo(i,1,n) b[i]=0;
	int m=(n+k+1)/2;
	fo(i,1,n) a[i]=read(),b[a[i]]++;
	int R=0,sum=0;
	pii ans=mk(1,n);
	fo(i,1,n){
		//big(R,i);
		while(R<n&&sum+b[R+1]<m) sum+=b[++R];
		if(R==n) break;
		//sml(ans,R-i+2);
		if(ans.se-ans.fi>R+1-i) ans=mk(i,R+1);
		sum-=b[i];
	}
	cout<<ans.fi<<' '<<ans.se<<'\n';
	vector<int> g;
	sum=0;
	fo(i,1,n) a[i]=(a[i]<ans.fi||a[i]>ans.se)?-1:1,sum+=a[i];
	int id=sum,lim=k;
	go(i,n,1){
		if(g.size()==lim) break;
		if(sum==id) id--,g.pb(i);
		sum-=a[i]; 
	}g.pb(0);
	go(i,lim,1) cout<<g[i]+1<<' '<<g[i-1]<<'\n';
}

signed main(){
	int T=read();
	while(T--) solve(); 
	return 0;
}
/*
-------------------------------------------------
*/

```


---

## 作者：LYY_yyyy (赞：0)

考虑将一个区间可以分为两个的充要条件：在 $[x,y]$ 中的数比不在的数至少多两个。略微拓展一下就能推得一个区间能分成 $k$ 个的充要条件：在 $[x,y]$ 中的数比不在的数至少多 $k$ 个。构造也是简单的：每次在 $[x,y]$ 中的数多于不在的数时就截断即可。于是 $[x,y]$ 中数的个数可以确定。可以将原数组排序，然后暴力算出每个长度符合的区间的 $y-x$ 的最小值，然后根据上述方法模拟构造即可。

代码如下：
```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define pb emplace_back
using namespace std;
int T;
int n,k;
int a[200010],p[200010];
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i],p[i]=a[i];
		sort(p+1,p+n+1);
		int pos=0,x=0,y=1e9;
		while(2*pos-n<k) pos++;
		for(int i=1;i<=n-pos+1;i++)
		{
			if(p[i+pos-1]-p[i]<y-x) y=p[i+pos-1],x=p[i];
		}
		cout<<x<<' '<<y<<"\n";
		int cnt=0,tot=0;
		int last=1;
		for(int i=1;i<=n;i++)
		{
			if(a[i]>=x&&a[i]<=y) cnt++;
			else cnt--;
			if(cnt>0)
			{
				if(tot<k-1) tot++,cout<<last<<' '<<i<<"\n",last=i+1,cnt=0;
			}
		}
		cout<<last<<' '<<n<<"\n";
	}
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 题解思路：
假设我们有若干个长为 $n$ 的数组。

有 $len$ 个满足条件 $A$ 的数字。

我们至少要分成 $k$ 组。

每组都要满足 $A$ 的数的个数 $>$ 不满足 $A$ 的个数。
 
那么每组若只多一个，那么 $n$ 里面满足条件 $A$ 的至少要比不满足的多 $k$ 个，

所以一组里不满足的就有 $\left \lfloor \frac{(n-k)}{2}  \right \rfloor$ 个。

所以满足的条件就是 $n - \left \lfloor \frac{(n-k)}{2}  \right \rfloor$。

你选的数 $len = \left \lceil \frac{(n-k)}{2}  \right \rceil = \left \lfloor \frac{(n-k + 1)}{2}  \right \rfloor$
 
那么你的值域区间就是 $\left[ a_i,a_{i+len-1}\right]$。

排完序之后，遍历一下，你就能知道他的最小的值域区间是多少。

但是知道了最小的值域我们还要构造一个区间的分开方式

我们回到原序列，若有一个在所选区间的数，就让计数器 $+1$。

若不在值域的数，那么计数器 $-1$。

那么计数器 $>1$ 的区间，就把左右端点记下来，若最后的数字没有分完就直接把他移到右端点就可以了。

最后直接输出左右端点就可以了。

## AC CODE:
```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
const int N = 200010;
int n;
int cnt;
int tot , k;
int a[N] , b[N];
int l[N] , r[N];
int ansl , ansr;
vector <int> p[N];
void solve() {
	scanf ("%d%d" , &n , &k);
	tot = 0;
	int len = (n + k + 1) / 2;//计算一个区间的长度
	for (int i = 1; i <= n; i++) {
		scanf ("%d" , &a[i]);
		b[i] = a[i];//b保存的是排序后的数组
	}
	sort(b + 1, b + 1 + n);//排序
	ansl = 1, ansr = len;
	for (int i = 2; i + len - 1 <= n; i++) 
		if (b[i + len - 1] - b[i] < b[ansr] - b[ansl]) 
			ansl = i, ansr = i + len - 1;
	for (int i = 1, u = 1; i <= k; u++, i++) {
		l[i] = u;
		for (int cnt = 0;; u++) {
			if (a[u] >= b[ansl] && a[u] <= b[ansr]) //若满足条件
				cnt++;//计数器++
			else //否则
				cnt--;//计数器--
			if (cnt > 0) {//只要大于0，就是
				r[i] = u;
				break;
			}
		}
	}
	r[k] = n;
	printf ("%d %d\n" , b[ansl] , b[ansr]);
	for (int i = 1; i <= k; i++) //输出
		printf ("%d %d\n" , l[i] , r[i]);
}
int main() {
	int T;
	scanf ("%d" , &T);
	while (T --)
		solve();
	return 0;
}
```
码字不易，求赞！

---

## 作者：IvanZhang2009 (赞：0)

一道不错的~~水~~题，赛时竟然没切出来……

## 正题
要分 $k$ 个区间，每个区间内在范围内的数的数量都严格大于在范围外的数的数量，那么当且仅当整个数组中范围内的数的数量大于等于 $\lceil\frac{n+k}{2}\rceil$ 可以做到分组。（好奇的同学可以自己想想为什么）

因为 $a_i$ 的数据范围只有 $2\cdot10^5$，那么可以统计每个数出现的次数，用双指针枚举 $x$,$y$，每次 $x$ 增加，当前在区间里的数就减少了一些，这时让 $y$ 继续增加直到在区间里的数到达了需要的 $\lceil\frac{n+k}{2}\rceil$，然后记录最小值和 $x$,$y$。最后输出。

输出的时候循环一遍，记录一下当前在区间内的数个数（$a$）和区间内数的总数（$b$），一旦满足 $a>b-a$，就输出这个区间，并将 $a$,$b$ 清零。需要注意的是当已输出 $k-1$ 个区间的时候，直接将剩下所有数组成一个区间输出，而不需要再去统计 $a$,$b$ 了。

## 代码
献上丑陋的代码 $\texttt{QWQ}$

可能码风有点奇怪，请见谅。~~当时脑子一片混乱，代码感觉也很奇怪，然后就稀里糊涂地 AC 了。~~

```cpp
int n,k;
int a[200005];
int cnt[200005];
int need;
void output(int x,int y){
	int alr=0,h=0,v=0;
	if(k==1){
		cout<<1<<' '<<n<<endl;
		return;
	}
	REP(i,0,n){
		h++;
		bool f=0;
		if(a[i]>=x&&a[i]<=y)alr++;
		if(alr*2>h&&v<k-1){
			cout<<i-h+2<<' '<<i+1<<endl;
			alr=0;
			h=0;
			v++;
			f=1;
		}
		if(v==k-1&&f){
			cout<<i+2<<' '<<n<<endl;
			return;
		}
	}
	return;
}
void Main(){
	memset(cnt,0,sizeof(cnt));
	cin>>n>>k;
	REP(i,0,n){
		cin>>a[i];
		cnt[a[i]]++;
	}
	need=(n+k+1)/2;
	int x=0,y=0;
	int ans=1e15,sum=cnt[0],ax,ay;
	while(sum<need){
		y++;
		sum+=cnt[y];
	}ans=min(ans,y-x);
	ax=x,ay=y;
	for(x=0;x<n;){
		sum-=cnt[x];
		x++;
		while(sum<need&&y<n){
			y++;
			sum+=cnt[y];
		}
		if(sum<need)continue;
		if(ans>(y-x)){
			ans=y-x;
			ax=x;
			ay=y;
		}
	}
	cout<<ax<<' '<<ay<<endl;
	output(ax,ay);
}

```

---

## 作者：cszhpdx (赞：0)

首先看到最小化 $y-x$ 这个玩意，果断二分 $y-x$，显然假如区间更长合法，那么更短一定也合法，然后再枚举 $x$ 进而得到 $[x,y]$，接下来的事情就是要判断某一个区间 $[x,y]$ 是否合法。

我们首先把砍成 $k$ 段转化为尽可能地多段，因为如果 $t$ 段的分割是合法的，我们我们将最后两个区间合并，这就是 $t-1$ 段了。

我们将 $a_i$ 重新赋值，如果 $a_i \in [x,y]$ 那么赋值为 1，否则为 -1，这样我们分割的 $k$ 段区间每一段的 $a_i$ 的和满足是正数即可，鉴于这是区间求和，搞个前缀和 $s_i=\sum\limits_{j=1}^ia_j$，条件变成了 $s_r-s_{l-1}\gt0,s_r>s_{l-1}$，$l-1$ 为刚好上一个区间的右端点，也就是说我们在求一个 $s$ 的上升子序列并且长度为 $k+1$，起点为 $s_0=0$，终点为 $s_n$。于是搞完这一切发现复杂度还是不行。

但是我们发现其实还可以抢救一下，我们发现 $s$ 有个奇妙的性质，就是 $|s_i-s_{i-1}|=1$，所以如果 $s$ 里有 $x>0$，那么 $s$ 一定还有 $0,1,2\cdots x-2,x-1$，并且下标存在在其之前的。这个最长上升子序列是可以构造出来的，只需要中间是连续的正整数。还有最后一个条件那就是序列长度要有 $k+1$，这很简单只要让 $s_n\ge k$ 就行。所以我们判定区间合不合法只需要计算一个 $s_n$ 就完了。

回顾 $s_n$ 定义，我们令 $t=\sum\limits_{i=1}^n[a_i \in [x,y]]$，显然 $s_n=t-(n-t)=2t-n$，也就是在 $[x,y]$ 的数的个数减去不在的。我们再用一个前缀和便于查询在某个值域区间的数的个数来计算 $s_n$，于是这题就结束了，吗？

我当时以为到这就没了，结果发现题目还让我去求方案，人傻了。这其实也简单，既然都知道了 $[x,y]$，我们可以按照上升子序列的求解方式搞，也可以直接贪心，因为保证了 $[x,y]$ 合法，所以我们区间的和为正的时候就划分一下，显然这是对的。

枚举 $[x,y]$ 貌似也可以用双指针，但是我不会。

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define cmin(a, b) (a)=min((a), (b))
#define cmax(a, b) (a)=max((a), (b))
#define mem(a, x) memset(a, x, sizeof(a))
#define rps(i, b, e) for(int i=(b);i<=(e);i++)
#define prs(i, e, b) for(int i=(e);i>=(b);i--)
#define rpg(i, g, x) for(int i=g.head[x];i;i=g.e[i].nxt)
#define opf(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
using namespace std;
template<class T>
inline void read(T &x) {
	x=0;
	bool f=false;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'), c=getchar();
	while(isdigit(c))x=x*10+(c-'0'), c=getchar();
	if(f)x=-x;
}
const int NR=2e5+10;
int T, n, k, a[NR], s[NR];
int chk(int dif) {
	rps(l, 1, n-dif+1)
		if((s[l+dif]-s[l-1])*2-n>=k)
			return l;
	return 0;
}
struct node {
	int id, v, ct;
}st[NR], p[NR];
int top;
int main() {
	read(T);
	while(T--) {
		read(n), read(k);
		mem(s, 0);
		rps(i, 1, n)read(a[i]), s[a[i]]++;
		rps(i, 1, n)s[i]+=s[i-1];
		int l=0, r=n-1, mid, yx=1e9, xx=1e9;
		while(l<=r) {
			mid=l+r>>1;
			int res=chk(mid);
			if(res==0)l=mid+1;
			else yx=mid, xx=res, r=mid-1;
		}
		printf("%d %d\n", xx, xx+yx);
		int yy=xx+yx;
		l=1;
		int subct=0, ns=0;
		rps(i, 1, n) {
			if(a[i]>=xx && a[i]<=yy)ns++;
			else ns--;
			if(ns<=0 || subct+1>=k)continue;
			printf("%d %d\n", l, i);
			l=i+1, subct++, ns=0;
		}
		printf("%d %d\n", l, n);
	}
	return 0;
}
```



---

## 作者：Purslane (赞：0)

## Solution

我们先了解一类问题 :

给定一个长度为 $n$ 的序列和一个区间 , 将这个序列分成 $k$ 个子串 , 使得每个字串中在区间内的数的个数大于在区间外的数的个数 .

这个问题可以通过正负性来解决 .

> 我们将每个数进行标记 , 如果在区间内记为 +$\text{1}$ , 区间外记为 $\text{-1}$ . 一个子串满足要求 , 就相当于这个子串的和大于0 .

> 进一步 , 我们对标记数组进行前缀和 . 子串和可以表示为前缀和的差 . 那么就相当于在前缀和数组里找一个首项为正 , 长度为 $k$ 且以 $n$ 结尾的上升子序列 . 可以 $\text{O(n log n)}$ 用 $\text{DP}$ 解决 .

> 实际上 , 这不需要 . 只要满足 $\text{pre} _ \text{n} \ge k$ 就可以了 . 因为 $|\text{pre} _ \text{i}-\text{pre} _ \text{i-1}| =1 $ . 我们思考 , 每一个数都是从 0 转换来的 , 所以对于每一个 $\text{pre} _ \text{i}$ , 前面必有 $\text{pre} _ \text{i-1}$ 出现 . 这样只要 $\text{pre} _ \text{n} \ge k$ , $1 , 2 , \cdots , k-1$ 肯定依次出现 , 就可以找到满足要求的序列 . 当然 , 如果 $\text{pre} _ \text{n} < k$ , 肯定也找不到符合的序列 . 这样复杂度是 $\text{O(n)}$ 的 .

> 计算 $\text{pre} _ \text{n}$ 其实也不用每次都 $\text{O(n)}$ . 我们可以按照值域预处理出区间外和区间内数的个数 , 做差即可 .

回到这道题 , 我们如果知道了 $[x,y]$ , 那么就可以判断是否满足 .

现在由于值域很小 , 可以枚举 $x$ . 考虑到区间越大 , 所包含的数也就越多 , 那么就越可能出现合法解 , 答案具有单调性 . 所以可以二分找到合适的 $y$ .

当我们找到答案区间 $[x,y]$ 后 , 就万事大吉了 . 可以把前缀和数组求出来 , 找出 $1 , 2 , \cdots , k-1$ , 输出 . 注意要开 `long long` . 复杂度 $\text{O(n log n)}$ . 可以用双指针优化到 $\text{O(n)}$ .

[code](https://codeforces.com/contest/1630/submission/145043319) 

练习 : [https://ac.nowcoder.com/acm/contest/23106/F](https://ac.nowcoder.com/acm/contest/23106/F) ( 牛客的一道题 , 需要给钱 . )

---

