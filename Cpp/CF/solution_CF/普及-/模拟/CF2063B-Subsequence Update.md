# Subsequence Update

## 题目描述

在小约翰向阿姨借了几百次膨胀螺丝后，她最终决定来收回那些没用过的螺丝。

但由于膨胀螺丝是家居设计的重要组成部分，小约翰决定把它们藏在最难以触及的地方--环保木皮下面。

给你一个整数序列 $a_1, a_2, \ldots, a_n$ 和其中一段 $[l,r]$ ( $1 \le l \le r \le n$ )。

您必须对该序列执行以下操作次。

- 选择序列 $a$ 的任意子序列 $^{\text{∗}}$ ，并将其倒转。注意，子序列不必是连续的。

形式上，选择任意数量的索引 $i_1,i_2,\ldots,i_k$ ，使得 $ 1 \le i_1 \lt i_2 \lt \ldots \lt i_k \le n $ 。然后，将所有 $1 \le x \le k$ 的 第 $i_x$ 个元素同时改为第 $i_{k-x+1}$ 个元素的原始值。

求操作后 $a_l+a_{l+1}+\ldots+a_{r-1}+a_r$ 的最小值。

$^{\text{∗}}$ 如果 $b$ 可以从 $a$ 中删除任意位置上的几个（可能是零个或全部）元素而得到，则序列 $b$ 是序列 $a$ 的子序列。

## 说明/提示

在第二个测试用例中，数组为 $a=[1,2,3]$ ，段为 $[2,3]$ 。

选择子序列 $a_1,a_3$ 并将其反转后，序列变为 $[3,2,1]$ 。然后，和 $a_2+a_3$ 变为 $3$ 。由此可见，和的最小可能值为 $3$ 。

## 样例 #1

### 输入

```
6
2 1 1
2 1
3 2 3
1 2 3
3 1 3
3 1 2
4 2 3
1 2 2 2
5 2 5
3 3 2 3 5
6 1 3
3 6 6 4 3 2```

### 输出

```
1
3
6
3
11
8```

# 题解

## 作者：special_y (赞：9)

# 思路
不妨考虑对于下标为 $i<l$，$j>r$，此时若交换 $i,j$ 所对应的元素，发现 $i,j$ 交换位置后并不影响区间内的最终输出结果，此时尝试缩小 $i,j$ 的范围，发现最后这样的能交换的子序列一定在区间 $[1,r]$ 或者 $[l,n]$ 中，此时我们只需要拷贝一份数组出来，用开好的两个数组分别排序一侧，这样最后取 $r-l+1$ 的区间长度最小值即可，注意不开 long long 最后会溢出。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t, l, r, n; ll a[100005], b[100005];
int main()
{
    cin.tie(0); cout.tie(0);
    cin >> t;
    for(int i = 1; i <= t; ++i)
    {
       cin >> n >> l >> r;
       memset(a, 0, sizeof(a));
       memset(b, 0, sizeof(b));
       for(int j = 1; j <= n; ++j)
       {
            cin >> a[j];
            b[j] = a[j];
       }
        sort(a+1, a+r+1);
        sort(b+l, b+n+1);
        ll sum1 = 0, sum2 = 0;
        for(int k = 1; k <= r - l + 1; ++k) sum1 += a[k];
        for(int k = l; k <= r; ++k) sum2 += b[k];
        ll minn = min(sum1, sum2);
        cout << minn << endl;
    }
    return 0;
}
```

```

---

## 作者：ran_qwq (赞：4)

对一个子序列反转相当于交换 $a_{b_i}$ 与 $a_{b_{k-i+1}}$。

对于一个区间 $[l,r]$，其中的所有数要么一部分和 $[1,l)$ 中的数交换，不和 $(r,n]$ 中的数交换；要么反过来。反正不能即和左边交换也和右边交换。具体证明就是交换的区间肯定是两两有包含关系的，按中心的位置分讨证明。

即在 $[1,r]$ 中取最小的 $r-l+1$ 个数，在 $[l,n]$ 中取最小的 $r-l+1$ 个数，两种情况取个最小值。

```cpp
int n,l,r,cb,cc,a[N],b[N],c[N]; ll s1,s2;
void QwQ() {
	n=rd(),l=rd(),r=rd(),cb=cc=s1=s2=0;
	for(int i=1;i<=n;i++) a[i]=rd();
	for(int i=1;i<=r;i++) b[++cb]=a[i];
	for(int i=l;i<=n;i++) c[++cc]=a[i];
	sort(b+1,b+1+cb),sort(c+1,c+1+cc);
	for(int i=1;i<=r-l+1;i++) s1+=b[i],s2+=c[i];
	wrll(min(s1,s2),"\n");
}
```

---

## 作者：cqbzhzf (赞：4)

[vjudge 中文翻译](https://vjudge.net/problem/CodeForces-2063B#author=GPT_zh)
### 思路
- 注意读题，只能翻转**一次**。
- 其次，有两种翻转方案，分别对操作区间的左区间和右区间进行翻转。
- 首先用 vector 把左区间和右区间存下来从小到大排序。其次对操作区间从大到小排序（贪心思想）。
- 对于第一种翻转方案，遍历操作区间，如果当前左区间的值比当前操作区间的值小，就进行替换，最后进行求和。
- 第二种翻转方案同理。
- 最后取两种方案最小值。实现时注意细节，如多测清空、循环边界等（详见代码）。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int t,n,l,r,a[N],d[N];
vector<int> b,c;
bool cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>l>>r;
		for(int i=1;i<=n;i++)
			cin>>a[i],d[i]=a[i];
		int sum1=0,sum2=0;
		for(int i=1;i<l;i++)
			b.push_back(a[i]);
		sort(b.begin(),b.end());
		int tt=0;
		sort(a+l,a+r+1,cmp);
		sort(d+l,d+r+1,cmp);
		for(int i=l;i<=r;i++)
		{
			if(tt==b.size())
				break;
			if(b[tt]<a[i])
				swap(b[tt],a[i]),tt++;
		}
		for(int i=l;i<=r;i++)
			sum1+=a[i];
		for(int i=r+1;i<=n;i++)
			c.push_back(a[i]);
		sort(c.begin(),c.end());
		int tt2=0;
		for(int i=l;i<=r;i++)
		{
			if(tt2==c.size())
				break;
			if(c[tt2]<d[i])
				swap(c[tt2],d[i]),tt2++;
		}
		for(int i=l;i<=r;i++)
			sum2+=d[i];
		cout<<min(sum1,sum2)<<"\n";
		b.clear(),c.clear();
	}
	return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/5ncpkn4c.png)

---

## 作者：bryce (赞：3)

## 思路
先来猜一下结论，子序列反转后 $[l, r]$ 区间最小和要么是 $[1, r]$ 中前 $r - l + 1$ 小的的和，要么是 $[l, n]$ 中前 $r - l + 1$ 小的和。

证明：$[l, r]$ 之内的较小值显然可以通过不调换位置继续待在 $[l, r]$ 中，然后 $[l, r]$ 之间的子序列翻转不改变区间最小和，于是我们只需要看最靠近 $r$ 且需要动的位置上的数调换到哪，以及最靠近 $l$ 且需要动的位置上的数调换到哪，这样整个子序列翻转的方式都是唯一确定的。

以下分别进行讨论，设 $x$ 表示最靠近 $l$ 且需要动的位置，$y$ 表示最靠近 $r$ 且需要动的位置：
+ 若 $x$ 上的数与 $r$ 后的数交换，则整个 $[x, y]$ 中的数都会与 $r$ 后面的数交换或不交换，由此一定能将 $[l, n]$ 中最小的 $r - l + 1$ 个数交换到 $[l, r]$ 内。
+  若 $y$ 上的数与 $l$ 前的数交换，则整个 $[x, y]$ 中的数都会与 $l$ 前面的数交换或不交换，由此一定能将 $[1, r]$ 中最小的 $r - l + 1$ 个数交换到 $[l, r]$ 内。
+ 若 $x$ 或 $y$ 在 $[l, r]$ 内选择数交换，则区间和不变。
于是用堆维护 $[1, l]$ 中最小的 $r - l + 1$ 个数的和 $[r, n]$ 中最小的 $r - l + 1$ 个数的和，取个 $\min$ 即为答案。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}

const int N = 1e5 + 10;
int T, n, l, r;
int a[N];
priority_queue<int> q;

signed main(){
    T = read();
    while (T--){
        n = read(), l = read(), r = read();
        for (int i = 1; i <= n; i++) a[i] = read();
        int sz = 0, sum = 0, ans;
        for (int i = 1; i <= r; i++){
            if (sz < r - l + 1) q.push(a[i]), sz++, sum += a[i];
            else if (a[i] < q.top()) sum -= q.top(), q.pop(), q.push(a[i]), sum += a[i];
        }
        ans = sum;
        while (!q.empty()) q.pop();
        sz = 0, sum = 0;
        for (int i = n; i >= l; i--){
            if (sz < r - l + 1) q.push(a[i]), sz++, sum += a[i];
            else if (a[i] < q.top()) sum -= q.top(), q.pop(), q.push(a[i]), sum += a[i];
        }
        cout << min(ans, sum) << '\n';
        while (!q.empty()) q.pop();
    }
    return 0;
}
```

---

## 作者：cqbzFGR (赞：2)

## 思路
我们可以很容易发现：只能在所求区间左边和右边选一些数将其翻转，而且不能同时选。证明：因为其所求的转换方法是翻转，所以若又转左区间又转右区间，右区间数会与左区间的数翻转，有效也只有中间的数，还不如直接翻中间的。\
那么这道题就很简单了，直接将左中右三个区间分别排序，分两种情况，左中和右中，分别遍历，遇到比中间小的直接翻转即可。
## code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
int t;
const int maxn=1e5+5;
int a[maxn];
vector<int> v1,v2,v3;
long long res1,res2;
void solve(){
    res1=0,res2=0;
    int n,l,r;
    cin>>n>>l>>r;
    v1.clear(),v2.clear(),v3.clear();
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<l;i++){v1.push_back(a[i]);}
    for(int i=l;i<=r;i++){res1+=a[i];v2.push_back(a[i]);}
    for(int i=r+1;i<=n;i++){v3.push_back(a[i]);}
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end(),greater<int>());
    sort(v3.begin(),v3.end());
    res2=res1;
    for(int i=0;i<int(min(v1.size(),v2.size()));i++){
        if(v1[i]<v2[i]) res1-=(v2[i]-v1[i]); 
    }
    for(int i=0;i<int(min(v2.size(),v3.size()));i++){
        if(v3[i]<v2[i]) res2-=(v2[i]-v3[i]);
    }
    cout<<min(res1,res2)<<"\n";
}
int main(){
    cin>>t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：_anll_ (赞：1)

本题瓶颈在于能否记住选点可以不连续。
## 思路
令 $[1,l-1]$ 为左区间，$[l,r]$ 为标准区间，$[r+1,n]$ 为右区间。

首先，标准区间一定只能和左区间或右区间中的一个进行翻转，不然就变成了左区间和右区间反转，没有贡献。其次，一定是左/右区间取 $k$ 个与标准区间中取 $k$ 个进行反转，如果想让 $k$ 个中的某几个进行反转而剩下的不翻，可以直接选择需要反转的那几个操作。

弄清楚这个后直接贪心地解决就好。我们可以枚举 $k$ 的取值，每次选标准区间中前 $k$ 大的和左/右区间前 $k$ 小的进行作差，最后取差的最大值去减标准区间的和即可。

注意极大值要尽量大。

## 代码
直接排序会更简单吧，但我比较钟爱优先队列。
```cpp
#include<queue>
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5;
int t,l,r,num[N];
priority_queue<int> pa,pb,pc;
void solve(){
	int n,l,r,L,R,k,ans=0,sum=0;
	while(!pa.empty()) pa.pop();
	while(!pb.empty()) pb.pop();
	while(!pc.empty()) pc.pop();
	cin>>n>>l>>r;L=l,R=r;int s1=0,s2=0,s=0,x=0;
	for(int i=1;i<=n;i++) cin>>num[i];
	for(int i=1;i<l;i++)
		pa.push(-num[i]);
	for(int i=l;i<=r;i++){
		ans+=num[i];
		pb.push(num[i]);
	}
	for(int i=r+1;i<=n;i++)
		pc.push(-num[i]);
	while(!pb.empty()){
		if(pa.size()){
			s1-=pa.top();pa.pop();
		}
		else s1=1e17;
		if(pc.size()){
			s2-=pc.top();pc.pop();
		}
		else s2=1e17;
		s+=pb.top();pb.pop();
		x=max(x,max(s-s2,s-s1));
	}
	cout<<ans-x<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;while(t--) solve();
	return 0;
} 
```

---

## 作者：boluo2014 (赞：1)

这道题目并不难，可能结论比较好想。

### 思路

要求 $l$ 到 $r$ 的最小值，选择子序列的时候，肯定是吧大的移走，小的移来。不过，在选择子序列时不能 $l$ 以前和 $r$ 以后都要，否则是没有用的。只是交换了 $l$ 以前和 $r$ 以后。所以正确的做法应该是：

先将 $l$ 到 $r$ 的数进行排序，这样可以遍历较大的数。然后大的数要换成小的数，但是只能单独管前面和后面。所以需要把和前面交换的和和后面交换的取最小值。

这里举一个例子，我取样例的第四组：

前面和中间交换：把最大的 $2$ 和最小的 $1$ 交换，结果是 $3$。

中间和后面交换：把最大的 $2$ 和最小的 $2$ 交换，结果是 $4$。

故最小为 $3$。

### 代码

简单描述：分别对 $1$ 到 $l-1$，$l+1$ 到 $r$ 和 $r+1$ 到 $n$ 进行排序。然后计算出 $l+1$ 到 $r$ 的和。接着分别看把 $1$ 到 $l-1$ 的某个值和 $l+1$ 到 $r$ 的某个值交换；还有 $l+1$ 到 $r$ 的某个值和 $r+1$ 到 $n$ 的某个值交换，取最小值。

当然，如果你比较懒，可以中间直接判断有一个数组不够了，比如 $l$ 以前的数没有了，就无法再和 $l+1$ 到 $r$ 之间的数交换了。

代码（有点丑）：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005];
int b[100005];
int c[100005];
int d[100005];
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int T=1;
    cin>>T;
    while(T--)
    {
        int n,l,r,i,len;
        cin>>n>>l>>r;
        for(i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        len=r-l+1;//中间那一段的长度
        int mn,sum1=0,sum=0;//sum是和前面交换，sum1是和后面交换
        for(i=l;i<=r;i++)
        {
            b[i-l+1]=a[i];
            sum+=a[i];
        }
        sum1=sum;
        sort(b+1,b+1+len);//排序
        if(l!=1)
        {
            for(i=1;i<=l-1;i++)
            {
                c[i]=a[i];
            }
            sort(c+1,c+l);//存入c并排序
            for(i=len;i>=1;i--)
            {
                if((1+(len-i))>l-1)
                {
                    break;
                }
                sum=min(sum,sum-b[i]+c[1+(len-i)]);
            }
        }
        if(r!=n)
        {
            for(i=r+1;i<=n;i++)
            {
                d[i-r]=a[i];
            }
            sort(d+1,d+1+(n-r));//存入d并排序
            for(i=len;i>=1;i--)
            {
                if((len-i+1)>(n-r))
                {
                    break;
                }
                sum1=min(sum1,sum1-b[i]+d[len-i+1]);
            }
        }
        cout<<min(sum,sum1)<<endl;
    }
    return 0;
}

```

---

## 作者：Kiana_1207 (赞：1)

根据题意，被选中翻转的子序列只能从区间 $[l,r]$ 中间或任意一侧选取，如果同时选取了区间外两侧的数，那么翻转后，一定会有某一侧的数仍全部落在区间外，相当于没有选取，举例说明，假设序列 $a=\{1,2,3,4,5,6,7\}$ 的区间 $[3,5]$，选取 $a_1,a_2,a_4,a_6$，变为 $a=\{6,5,3,4,2,1,7\}$，对于区间 $[3,5]$ 而言，$a_1,a_6$ 的交换显然是无效的，所以我们可以只考虑一边的数。

此时我们分离出 $[1,r]$ 与 $[l,n]$ 两个序列，分别统计答案，最终两者取较小值。显然，序列中第 $1$ 到第 $r-l+1$ 小的值的和就是答案，因为假设有一个更大的数被翻转入区间，我们必然可以将它换为区间外更小的数，或者取消翻转这个数，使得更小的数仍留在区间内。

思路已经很清晰了，贴个代码：
~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=100010;
int T,n,l,r,minn1,minn2,a[N],b[N],c[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>T;
	while (T--)
	{
		minn1=minn2=0;
		cin>>n>>l>>r;
		for (int i=1;i<=n;i++)
			cin>>a[i];
		for (int i=1;i<=n;i++)
		{
			if (i<=r) b[i]=a[i];
			if (i>=l) c[i-l+1]=a[i];
		}
		sort(b+1,b+r+1);
		sort(c+1,c+n-l+2);
		for (int i=1;i<=r-l+1;i++)
		{
			minn1+=b[i];
			minn2+=c[i];
		}
		cout<<min(minn1,minn2)<<'\n';
	}
	return 0;
}
~~~

---

## 作者：XichenOC (赞：0)

## [Subsequence Update](https://www.luogu.com.cn/problem/CF2063B)
# 题目翻译：
给定一个序列。在给定一个区间 $[l,r]$，你可以任意选择几个数，使所选的所有数左右颠倒。求如何颠倒才能使区间内的所有数之和最小。
# 思路：
若要使整个区间内所有数和最少，那一定就使尽量小的数翻转到区间内。我们发现我们只需要在区间左边或右边选择几个数，在在区间内选等量的数，翻转之后，所选的数就进去了。因此我们可以根据该性质。就可以发现，我们只需要在区间左边或右边选择较小的数与区间内较大的数替换即可。
# 实现：
可以建两个小根堆，分别储存区间加区间左边和区间加区间右边。然后只需要在两个小根堆中选择区间长度个数，在取最小值即可。这样所选择的就是最少答案。
# 完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N];
priority_queue<int,vector<int>,greater<int>>q1,q2;
signed main(){
    int t;
    scanf("%lld",&t);
    while(t--){
        int n,l,r;
        scanf("%lld%lld%lld",&n,&l,&r);
        int len=r-l+1;
        while(!q1.empty())q1.pop();
        while(!q2.empty())q2.pop();
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            if(i<=r){
                q1.push(a[i]);
            }
            if(i>=l){
                q2.push(a[i]);
            }
        }
        int sum1=0,sum2=0;
        for(int i=1;i<=len;i++){
            sum1+=q1.top();
            sum2+=q2.top();
            q1.pop();
            q2.pop();
        }
        cout<<min(sum1,sum2)<<endl;
    }
}
```

---

## 作者：TainityAnle (赞：0)

### 题意

有一个长度为 $n$ 的序列，给定区间 $[l,r]$。可以在序列上进行一次操作，选中一个子序列然后将它翻转。问操作后区间 $[l,r]$ 和的最小值。

### 思路

翻转子序列一定是有 $[l,r]$ 之间的元素的，不然就对原序列没什么影响。

如果又包含区间左边的元素，又包含区间右边的元素，那么可以考虑以下两种情况。

1. 区间左右两边选择要翻转的元素个数是相等的，那么左边的到了右边，区间内的没变。
2. 区间左边选的多，那么就相当于把右边的翻转到左边，中间和左边的交换。反之亦然。

这样我们发现一定是将区间左右某一边的值与区间中的值交换，这样的操作可以得到最优值。

答案就是从 $1$ 到 $r$ 即区间左边和区间的前 $r-l+1$ 小的和，与 $l$ 到 $n$ 即区间右边和区间的前 $r-l+1$ 小的和两个值取最小值。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int T,n,l,r,a[N],b[N],c[N],cnt;
signed main() {
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>T;
	while(T--) {
		cnt=0;
		cin>>n>>l>>r;
		for(int i=1; i<=n; i++) cin>>a[i];
		for(int i=1; i<=r; i++) b[i]=a[i];
		sort(b+1,b+r+1);
		int R=0;
		for(int i=1; i<=r-l+1; i++) R+=b[i];
		for(int i=l; i<=n; i++) c[++cnt]=a[i];
		sort(c+1,c+cnt+1);
		int L=0;
		for(int i=1; i<=r-l+1; i++) L+=c[i];
		cout<<min(L,R)<<endl;
	}
	return 0;
}
```

---

## 作者：Chenaknoip (赞：0)

注意到可以通过一次交换，使得将 $a[l\dots r]$ 的元素替换为 $a[1\dots r]$ 的元素或 $a[l\dots n]$ 的元素。又考虑到题目中要求 $a[l\dots r]$ 中元素和最小，因此可以考虑进行对 $a[l\dots r]$ 的左右两侧分别贪心取最小值，然后进行比较。

时间复杂度 $O(n \log n)$。

赛时代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, l, r, a[100010], b[100010], sum;
int ansl() {
	if (l == 1) return 0x7f7f7f7f7f7f7f7f;
	for (int i = 1; i <= r; i++) {
		b[i] = a[i];
	}
	sort(b + 1, b + r + 1);
	int ans = 0;
	for (int i = 1; i <= r - l + 1; i++) {
		ans += b[i];
	}
	return ans;
}
int ansr() {
	if (r == n) return 0x7f7f7f7f7f7f7f7f;
	for (int i = l; i <= n; i++) {
		b[i] = a[i];
	}
	sort(b + l, b + n + 1);
	int ans = 0;
	for (int i = l; i <= r; i++) {
		ans += b[i];
	}
	return ans;
}
signed main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%lld%lld%lld", &n, &l, &r);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		sum = 0;
		for (int i = l; i <= r; i++) sum += a[i];
		if (1 == l && r == n) printf("%lld\n", sum);
		else printf("%lld\n", min(ansl(), ansr()));
	}
	return 0;
}
```

---

## 作者：ybclch2026 (赞：0)

## 题目大意
有一个序列，翻转序列中的一个子序列，但只能翻一次，使得区间 $[l,r]$ 的和最小。

## 思路
因为要将区间 $[l,r]$ 中的数翻出去，所以有只能与区间 $[1,l-1]$ 或与区间 $[r+1,n]$ 中的数进行交换。

所以就用三个数组存三个区间的数，将其排序，再将区间 $[l,r]$ 中大的数替换掉其余两个区间小的值，答案就取两者中小的值。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1e5+5;
int T,n,l,r,la,lb,lc;
ll a[maxn],b[maxn],c[maxn],v[maxn];
int cmp(int aa,int bb){return aa>bb;}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>l>>r;
		if(l>r)swap(l,r);
		for(int i=1;i<=n;i++)cin>>v[i];
		lb=la=lc=0;
		for(int i=1;i<=n;i++){
			if(i<l)a[++la]=v[i];
			else if(l<=i&&i<=r)b[++lb]=v[i];
			else c[++lc]=v[i];
		}
		sort(a+1,a+1+la);
		sort(b+1,b+1+lb,cmp);
		sort(c+1,c+1+lc);
		ll ans=0;
		for(int i=1;i<=lb;i++)ans+=b[i];
		if(lb==n){
			cout<<ans<<endl;
			continue;
		}
		ll res=ans;
		for(int i=1;i<=min(lc,lb);i++){
			if(c[i]<b[i])res=res-b[i]+c[i];
			else break;
		}
		for(int i=1;i<=min(la,lb);i++){
			if(a[i]<b[i])ans=ans-b[i]+a[i];
	    	else break;
		}
		cout<<min(res,ans)<<endl;
	}
	return 0;
}

```

---

## 作者：Quartz_Blocks (赞：0)

### CF2063B Subsequence Update Editorial
###### $ \tiny\tiny\text{CF Round 1000 祭。}$
很有趣的一道题。

题意：选择长度为 $n$ 的序列 $a$ 的一个不一定连续的子序列进行反转，求经过一次反转后区间 $[l,r]$ 的和的最小值。

首先思考：是否经过反转，序列内最小的一段长度为 $(r - l + 1)$ 的一段子序列一定能够替换（可能改变顺序）至 $[l,r]$？

很明显不对。对于样例 #6：

```
6 1 3
3 6 6 4 3 2
```
最小长度为 $3$ 的子段和为 $9$，但是答案为 $8$。

再思考：是否直接贪心取序列中最小的长度为 $(r - l + 1)$ 的几个数之和即为答案？

还是不对。对于这个 Hack：

```
6 2 4
3 6 5 2 1 4
```

贪心求得的答案为 $1 + 2 + 3 = 6$，但实际结果为：

$$[3,\color{red}6\color{black},\color{red}5\color{black},2,\color{red}1\color{black},\color{red}4\color{black}]$$

反转红色数字组成的子序列，答案为：

$$[3,4,1,2,5,6] \,\,\,\,\,\,4 + 1 + 2 = 7$$

发现答案与 $[l,r]$ 区间外两边值能取得的值有关。

那对于 $[3,6,5,2,1,4]$，我们将序列拆分成三段：

$$[3],\color{red}[6,5,2]\color{black},[1,4]$$

现在我们需要贪心的将 $[l,r]$ 序列中的值与**单侧**的值进行交换，求得答案。

由于要替换出去大的值，换进来小的值，对 $[l,r]$ 这一段从大到小排序，对两端的段进行从小到大排序。

那么对于每一个点，前缀和预处理之后 $\mathcal{O}(1)$ 计算区间替换后的值，取最小值即可。

Code:

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 100010;

int n, l, r, a[N];
int x[N], y[N], z[N];
int c1, c2, c3;//分别统计 x,y,z 的长度
int cmp(int x, int y) {
	return x > y;
}
int b[N];//处理前缀和

void solve() {
	c1 = c2 = c3 = 0;//初始化
	memset(b, 0, sizeof(b));//初始化
	cin >> n >> l >> r;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (l <= i && i <= r) {//分别放入三个不同序列中
			x[++c1] = a[i];
		} else if (i < l) {
			y[++c2] = a[i];
		} else {
			z[++c3] = a[i];
		}
	}
	sort(x + 1, x + 1 + c1, cmp);
	sort(y + 1, y + 1 + c2);
	sort(z + 1, z + 1 + c3);
	int cntx = 0, cnty = 0, cntz = 0;
	for (int i = 1; i <= c1; i++)
		b[i] = b[i - 1] + x[i];
	int ans = b[c1];
	for (int i = 1; i <= c1; i++) {
		if (i <= c2) {
			cnty += y[i];
			ans = min(ans, cnty + (b[c1] - b[i]));//左侧替换后的值
		}
		if (i <= c3) {
			cntz += z[i];
			ans = min(ans, cntz + (b[c1] - b[i]));//右侧替换后的值
		}
	}
	cout << ans << endl;
}
int T;

signed main() {
	cin >> T;
	T = T;
	while (T--) {
		solve();
	}

	return 0;
}
```

---

