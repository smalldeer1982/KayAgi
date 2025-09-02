# Dances (Easy version)

## 题目描述

This is the easy version of the problem. The only difference is that in this version $ m = 1 $ .

You are given two arrays of integers $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ . Before applying any operations, you can reorder the elements of each array as you wish. Then, in one operation, you will perform both of the following actions, if the arrays are not empty:

- Choose any element from array $ a $ and remove it (all remaining elements are shifted to a new array $ a $ ),
- Choose any element from array $ b $ and remove it (all remaining elements are shifted to a new array $ b $ ).

Let $ k $ be the final size of both arrays. You need to find the minimum number of operations required to satisfy $ a_i < b_i $ for all $ 1 \leq i \leq k $ .

This problem was too easy, so the problem author decided to make it more challenging. You are also given a positive integer $ m $ . Now, you need to find the sum of answers to the problem for $ m $ pairs of arrays $ (c[i], b) $ , where $ 1 \leq i \leq m $ . Array $ c[i] $ is obtained from $ a $ as follows:

- $ c[i]_1 = i $ ,
- $ c[i]_j = a_j $ , for $ 2 \leq j \leq n $ .

## 说明/提示

In the first test case for the pair of arrays $ ([1, 1], [3, 2]) $ , the answer is $ 0 $ . No operations or reordering of elements are needed.

## 样例 #1

### 输入

```
4
2 1
1
3 2
4 1
5 1 5
3 8 3 3
8 1
4 3 3 2 2 1 1
1 1 1 1 3 3 3 3
9 1
9 2 8 3 7 4 6 5
1 2 3 2 1 4 5 6 5```

### 输出

```
0
1
4
4```

# 题解

## 作者：FFTotoro (赞：7)

## 解法

先考虑如果数组最终大小 $k$ 确定怎么判断答案是否合法：有一个显然的贪心，把 $a$ 数组中最大的 $n-k$ 个移除，把 $b$ 中最小的 $n-k$ 个移除，排序后进行比较所有 $a_i$ 与 $b_i$ 的大小关系即可。

再观察到 $k$ 具有单调性，直接二分即可。

放代码（Easy Version）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t; cin>>t;
  while(t--){
    int n,m; cin>>n>>m;
    vector<int> a(n),b(n);
    a[0]=1; for(int i=1;i<n;i++)cin>>a[i];
    for(auto &i:b)cin>>i;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int l=0,r=n;
    auto pd=[&](int x){
      vector<int> p,q;
      for(int i=0;i<x;i++)
        p.emplace_back(a[i]);
      for(int i=n-x;i<n;i++)
        q.emplace_back(b[i]);
      for(int i=0;i<x;i++)
        if(p[i]>=q[i])return false;
      return true;
    }; // 判断合法
    while(l<r){
      int m=l+r+1>>1;
      if(pd(m))l=m;
      else r=m-1;
    } // 二分最终数组最大大小
    cout<<n-l<<endl; // 答案即为 n 减去最大数组大小
  }
  return 0;
}
```

---

## 作者：One_JuRuo (赞：2)

## 思路

考虑从大到小给每一个 $b_i$ 匹配一个 $a_j$，那么如果对于 $b_i$，$a_j$ 不能匹配，那么对于后续更小的 $b_i$，$a_j$ 同样无法匹配，所以可以直接忽略，跳到下一个，一直匹配，直到无法匹配为止，那么无法匹配的 $b_i$ 的数量就是需要的操作数。

因为简单版本 $m=1$，所以直接把 $a_1$ 赋值为 $1$ 即可。

因为对于这个 $b_i$，匹配 $a_j$ 可以从上一个 $b_i$ 匹配的后一个 $a_j$ 开始，所以总复杂度是 $O(n)$，加上最开始对数组 $a$ 和数组 $b$ 排序的 $O(n\log n)$，时间复杂度是 $O(n\log n)$，所以不会 TLE。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,a[100005],b[100005],ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m),a[1]=1,ans=0;
		for(int i=2;i<=n;++i) scanf("%d",&a[i]);
		for(int i=1;i<=n;++i) scanf("%d",&b[i]);
		sort(a+1,a+n+1),sort(b+1,b+n+1);
		int j=n;
		for(int i=n;i>=1;--i)
		{
			while(j>1&&a[j]>=b[i]) --j;
			if(j==1&&a[j]>=b[i]){ans=n-i;break;}
			else if(j==1&&a[j]<b[i]){ans=n-i+1;break;}
			--j;
		}
		printf("%d\n",n-ans);
	}
	return 0;
}
```

---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1883G1)

[CF传送门](https://codeforces.com/problemset/problem/1883/G1)

[AC记录](https://codeforces.com/contest/1883/submission/300398818)
# 题意简述
~~翻译真是简洁啊，直接粘过来吧！~~  

给定数组 $a$ 和 $b$。你可以对两个数组任意排序，你需要在两个序列中分别删除 $k$ 个数，使得对于剩下 $n-k$ 个数，有 $\forall 1\leq i\leq n-k\rightarrow a_i<b_i$。  
求 $k$ 的最小值。

# 题解
首先，根据可以排序，删去 $k$ 个数和 $a_i < b_i$ 可以看出，在 $k$ 一定的情况下，应将 $a$ 和 $b$ 从小到大排序，从 $a$ 中删去最大的 $k$ 个，从 $b$ 中删去最小的 $k$ 个。这样 $a$ 中就是最小的 $n-k$ 个数，$b$ 中就是最大的 $n-k$ 个数，可以更好的满足条件。  
其次，我们观察到，$k$ 越大，$a$ 中剩下的数就越小，$b$ 中剩下的数就越大，因此可以更好的满足条件，所以 $k$ 具有单调性，可以考虑使用二分。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
#define CLOSE ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define F first
#define S second
#define lowbit(x) x&-x
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int Stack[105];
inline void print(ll x){
    int cnt=0;
    if(x<0) putchar('-'),x=-x;
    while(x){
    	Stack[++cnt]=x%10;
    	x/=10;
    }
    while(cnt--) putchar((char)Stack[cnt+1]+'0');
    return;
}
int n,m,t,a[N],b[N];
bool check(int mid){
    for(int i=1;i<=n-mid;i++) if(a[i]>=b[i+mid]) return 0;//若不满足条件，返回0
    return 1;
}
int main(){
    CLOSE
    cin>>t;
    while(t--){
        cin>>n>>m;
        a[1]=1;
        for(int i=2;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        sort(a+1,a+1+n);
        sort(b+1,b+1+n);
        //排序
        int l=0,r=n;
        while(l<r){
            int mid=l+r>>1;
            if(check(mid)) r=mid;
            else l=mid+1;
        }
        //二分
        cout<<l<<'\n';
    }
    return 0;
}
```

---

## 作者：Gyc_Fisher (赞：1)

# CF1883G1 Dances (Easy version) 题解

题目链接：[Dances (Easy version)](https://www.luogu.com.cn/problem/CF1883G1)

首先看到题，发现可以对数组任意排序，于是有了以下的贪心思路：

针对 $a$ 和 $b$ 两个数组，我们需要的是让 $a_i < b_i (1\leq  i \leq n-k)$，那么我们删除 $a$ 数组中最大的 $k$ 个数，同时删除 $b$ 数组中最小的 $k$ 个数，此时 $a$ 数组中保留的就是就是更容易被 $b$ 数组覆盖的 $n-k$ 个数，$b$ 保留的也就是更具有覆盖 $a$ 数组能力的数。

那么，本题的解题步骤也非常的简单了：

1.先对 $a$ 和 $b$ 数组排序。

2.然后枚举 $a$ 中删除的数的个数（从头到尾遍历一遍），同时看 $b$ 数组中保留的数符不符合要求。但这里的 $n$ 是 $10^5$ 的级别，所以我们需要用一个双指针去判断该情况合不合法。



---

## 作者：Aveiro7 (赞：1)

### 题目链接：[CF1883G1](https://www.luogu.com.cn/problem/CF1883G1)

### 题意：

给定两个长度为 $n$ 的序列 $a$ 和 $b$，其中 $a_1=1$，$a_2\cdots a_n$ 与 $b_1\cdots b_n$ 由输入得到。

你可以对两个数组任意排序，你需要在两个序列中分别删除 $k$ 个数，使得对于剩下 $n-k$ 个数，对于所有 $1\le i\le n-k \to a_i<b_i$。

求最少删除数。

## 思路:

这题通过观察显然可以使用贪心来做，可以把 $a$ 序列中最大的 $n-k$ 个数删除，同时把 $b$ 序列中最小的 $n-k$ 个删除，随后进行排序且比较剩余每个 $a_i$ 和 $b_i$ 的大小就可以了。时间复杂度也不大，不会超时。

---

## 作者：Pollococido (赞：0)

## 大致解法

这道题可以用排序和贪心来搞定。我们需要处理两个数组：一个是 $c$（其中 $c_1 = 1$，后面跟着 $a_i$），另一个是 $b$。目标是尽量多地保留一些元素对，使得剩下的 $c_i < b_i$，然后算出最少需要删掉多少对。排序两个数组，再用双指针匹配，就能很快找到答案 $ans$，也就是 $n - k$，其中 $k$ 是能保留的对数。

---

## 详细步骤

### Part 1 初始化

先把基础东西准备好：  

- 对于 $1 \leq i \leq n$：  
    - $c_1 = 1$，然后 $c_i = a_i$（对 $2 \leq i \leq n$）。  
    - $b_i$ 直接从输入里拿。  
- 设置 $ans = 0$，表示一开始的操作次数。  
- 把 $c$ 和 $b$ 都按升序排个序，方便后面操作。

#### 变量含义

- $c$：第一个数组，开头是 $1$，后面接上 $a$ 的元素。  
- $b$：第二个数组，就是输入给的那个。  
- $ans$：我们要删掉的元素对数，也就是最少操作次数。

---

### Part 2 操作 1

接下来算出能保留多少对，然后更新 $ans$：  

- 用双指针来匹配：  
    - 用一个指针 $j$ 从 $b$ 的开头开始。  
    - 遍历 $c$ 的每个元素 $c_i$：  
        - 在 $b$ 里找第一个 $b_j$，要满足 $b_j > c_i$。  
        - 如果找到了，就保留这对 $(c_i, b_j)$，$k$ 加 1，然后 $j$ 往后移。  
        - 如果 $b_j \leq c_i$，就跳过这个 $b_j$，$j$ 继续往后走。  
- 最后算 $ans = n - k$，这就是要删掉的对数。

---

### Part 3 操作 2

直接把 $ans$ 扔出去就行。  

- $ans$ 就是我们在重排 $c$ 和 $b$ 后，需要最少删掉的对数，保证剩下的都满足 $c_i < b_i$。

---

## 复杂度分析

- **时间复杂度**：  
    - 给 $c$ 和 $b$ 排序 $O(n \log n)$。  
    - 双指针匹配 $O(n)$。  
    - 总共是 $O(n \log n)$。  
- **空间复杂度**：  
    - 两个数组各占 $O(n)$，所以空间是 $O(n)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, t;
int c[100010], b[100010];

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m;
        c[1] = 1;
        for (int i = 2; i <= n; i++) {
            cin >> c[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
        }
        sort(c + 1, c + 1 + n);
        sort(b + 1, b + 1 + n);
        int k = 0;
        int j = 1;
        for (int i = 1; i <= n; i++) {
            while (j <= n && b[j] <= c[i]) {
                j++;
            }
            if (j <= n) {
                k++;
                j++;
            }
        }
        cout << n - k << endl;
    }
    return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

## D1 题解

VP 时没读到可以事先移动位置，因此没秒掉 D1。

此时 $a_1=1$。

贪心一下，将 $a$ 排序，然后对每个 $a_i$ 找最小的没被选的 $b_i>a_i$，这个过程可以对 $b$ 排序+双指针解决。

## D2 题解

D2 被 long long 控了。

先尝试把这个贪心变得更易于推广。

先将 $b$ 排序。

记 $t_i$ 表示最小的，满足 $b_j>a_i$ 的 $j$。

此时，可以把 $a_i$ 挂在 $t_i$ 上。

这个时候，用大根堆维护 $t_i$，然后从右往左扫一遍 $b$，并贪心的取堆中的数即可。

具体流程是这样的：

1.遍历到位置 $i$。

2.取出堆顶元素 $v$。

3.若 $v>i$，重复 2 直到 $v\le i$。

4.若最后堆非空且 $v\le i$，则说明这个位置可以出现在最终的 $b$ 中，直接算即可。

此时指定 $a_1$ 相当于把 $t_{a_1}$ 扔堆里再问答案。

发现如果做上述第 4 步时出现 $v=i$ 的情况，则意味着若添加一个 $\ge v$ 的元素会丢掉 $v$ 的贡献。

枚举 $t_{a_1}$ 依照上述过程算即可。

## D1 代码


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=2e5+10;
int a[N],b[N];
void slv(){
    int n,m;cin>>n>>m;
    a[1]=1;for(int i=2;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    int it=1;
    int ans=0;
    sort(a+1,a+n+1);sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        while(it<=n&&b[it]<=a[i]) it++;
        if(it<=n) ans++,it++;
    }cout<<n-ans<<endl;
}
int main(){
    int t;cin>>t;while(t--) slv();
    return 0;
}
```

## D2 代码


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=2e5+10;
int a[N],b[N];
int tg[N],suc[N];
priority_queue<int> q;
void slv(){
    int n,m;cin>>n>>m;
    for(int i=1;i<n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    int it=1;while(!q.empty()) q.pop();
    long long ans=0;
    sort(a+1,a+n);sort(b+1,b+n+1);
    for(int i=1;i<n;i++){
        while(it<=n&&b[it]<=a[i]) it++;
        if(it<=n) q.push(it)/*,cout<<it<<' '*/;
    }int k=0;
    for(int i=n;i>=1;i--){
        tg[i]=0;
        while(!q.empty()){
            if(q.top()>i) q.pop();
            else break;
        }
        if(!q.empty()){if(q.top()==i) tg[i]=1;q.pop();k++;}
    }int fl=1;b[0]=1;
    for(int i=1;i<=n;i++){
        if(tg[i]==1) fl=0;
        if(b[i-1]>m) continue;
        if(fl) ans+=1ll*(min(b[i],m+1)-b[i-1])*(n-k-1);
        else ans+=1ll*(min(b[i],m+1)-b[i-1])*(n-k);
    }if(b[n]<=m) ans+=1ll*(n-k)*(m+1-b[n]);
    cout<<ans<<endl;
}
int main(){
    int t;cin>>t;while(t--) slv();
    return 0;
}
```

---

## 作者：jyc0322 (赞：0)

## 思路

$b，c$可以任意排序，删除，满足 $c_i\lt b_i$，使总删除数最少，很明显是贪心。

为了让 $b，c$ 中所有元素尽可能多的匹配，所以可以先排序，然后从 $b$ 中第一个大于 $c_1$ 开始，一直往后，如果$b_i \le c_j$ 则将 $i+1$ 否则 $i+1，j+1$ 。




## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=2e5+10;
int t,m,n,a[M],b[M],sum;

int main(){
  cin>>t;
  while(t--){
    sum=0;
    bool f=0;
    cin>>n>>m;
    //a[1]=1;
    for(int i=2;i<=n;i++){
      cin>>a[i];
    }
    for(int i=1;i<=n;i++){
      cin>>b[i];
    }
    sort(a+2,a+n+1);
    sort(b+1,b+n+1);
    int p=upper_bound(b+1,b+n+1,a[2])-b;
    for(int i=upper_bound(b+1,b+n+1,a[2])-b,j=2;i<=n;i++){
      if(b[i]>a[j]){
        sum++,j++;
      }else{
        p=max(p,i);
      }
    }

    cout<<n-sum;
    
    
  }
  return 0;
}
```

---

## 作者：AC_love (赞：0)

考虑对于任意一个数，我们都尽量找比它大的最小的数去匹配。可以证明这样的贪心策略一定是最优的。

具体做法是先把 $a, b$ 数组都排好序，然后用双指针去扫两个数组。

扫完之后，可能会出现以下两种情况：

1. $a$ 中元素都能找到匹配，$b$ 中剩下一个元素。
2. $a$ 中元素不全能找到匹配，$b$ 中剩下大于一个元素。

如果是前者的话，我们直接找到 $b$ 中剩下的元素是几即可，不难发现 $m$ 小于这个元素时 $k = 0$，而 $m$ 大于这个元素时 $k = 1$，就做完了。

如果是后者的话，我们就找到 $b$ 中剩下的元素的最大值即可，然后步骤同上。

[code](https://codeforces.com/contest/1887/submission/250568685)

---

## 作者：FireRain (赞：0)

# 思路

首先，有一个显然的贪心策略：如果要选择不删除一个 $a_i$，那么，我们一定会选择在 $b$ 没有被选的，大于 $a_i$ 最小的 $b_j$ 与 $a_i$ 配对。

那么，考虑先对 $a$ 和 $b$ 排序。

然后很容易进行一个双指针的操作，可以保证正确性是对的，因为如果 $b_j$ 无法与 $a_i$ 进行配对，那么显然不能与 $a_{(i + 1) \sim n}$ 配对。

# Code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 1e5 + 10;
int T,n,m;
int arr[N],brr[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void solve(){
	int ans = 0;
	n = read();
	m = read();
	arr[1] = 1;
	for (re int i = 2;i <= n;i++) arr[i] = read();
	for (re int i = 1;i <= n;i++) brr[i] = read();
	sort(arr + 1,arr + n + 1);
	sort(brr + 1,brr + n + 1);
	for (re int i = 1,j = 1;i <= n - ans && j <= n;i++){
		while (arr[i] >= brr[j] && j <= n){
			j++;
			ans++;
		}
		j++;
	}
	printf("%d\n",ans);
}

int main(){
	T = read();
	while (T--) solve();
	return 0;
}
```

---

