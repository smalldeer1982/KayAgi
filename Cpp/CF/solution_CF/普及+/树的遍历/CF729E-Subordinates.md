# Subordinates

## 题目描述

There are $ n $ workers in a company, each of them has a unique id from $ 1 $ to $ n $ . Exaclty one of them is a chief, his id is $ s $ . Each worker except the chief has exactly one immediate superior.

There was a request to each of the workers to tell how how many superiors (not only immediate). Worker's superiors are his immediate superior, the immediate superior of the his immediate superior, and so on. For example, if there are three workers in the company, from which the first is the chief, the second worker's immediate superior is the first, the third worker's immediate superior is the second, then the third worker has two superiors, one of them is immediate and one not immediate. The chief is a superior to all the workers except himself.

Some of the workers were in a hurry and made a mistake. You are to find the minimum number of workers that could make a mistake.

## 说明/提示

In the first example it is possible that only the first worker made a mistake. Then:

- the immediate superior of the first worker is the second worker,
- the immediate superior of the third worker is the first worker,
- the second worker is the chief.

## 样例 #1

### 输入

```
3 2
2 0 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 3
1 0 0 4 1
```

### 输出

```
2
```

# 题解

## 作者：xzggzh1 (赞：10)

题意：

一个公司有 $n$ 个员工，除了主管之外，每个员工都有一个直接上级。要求每个工人告诉他们有多少上级。有些工人很匆忙，犯了个错误。你要找出可能犯错误的最少工人人数。

---

我们考虑对于一个合法的序列它应该是怎么样的。

除了根节点，每一个点都有一个父亲，很显然，这个点的祖先个数一定比它父亲节点多一。

那么如同 $0,1,1,2,2,3,4$ 或 $0,1,2,2,2,2,3$ 等都是合法的序列。

即 $0$ 有且只有一个，其他的数都是连续的（在升序排列后）。

想到这里，这个题就很简单了，只要贪心的把大的数填到小的“缺口”里就好了。


---

核心代码：

```cpp
int n, s, x, ans, cnt = 1, a[200005];
int main()
{
	cin >> n >> s;
	for ( int i = 1; i <= n; i++ ){cin >> x;i == s ? ans += x > 0 : a[x]++;}
	for ( int i = 1; cnt < n; i++ ){cnt	+= a[i] ? a[i] : 1;ans	+= a[i] == 0;}
	cout << ans;
}
```

---

## 作者：activeO (赞：2)

## 题目大意

一个公司有 n 个员工，第 s 个是主管，除了主管都有一个直接上司（简称父亲）。每个员工可能会记错自己上司的个数，现在让每一个员工回答他们的上司数 $ a_i $，问最少有几个员工记错了。

## 思路

~~又是一道小清新思维题~~

首先很容易想到 $ a_s $ 这个主管一定没有上司，就是 0，否则就是他记错了。

然后对于每一个员工，他都会比他的父亲只多一个上司，所以说把员工的回答从小到大排序后，这肯定是形如：0 1 2 2 2 3 3 3 3 3 4 这样的数列，如果在某个地方有缺口（即连续的数中有一个数的个数为 0），我们就要填补上也就是 $ ans \gets ans+1 $。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

using namespace std;

const int maxn=2e5+10;
int num[maxn];

int main(){
	
	int n,m,cnt=1,ans=0;//因为有个主管，所以 cnt 初始为 1。
	
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		if(i==m) ans+=(x>0);//如果主管回答的不是0，那他肯定记错了。
		else num[x]++;//统计序列中的数。
	}
	
	for(int i=1;cnt<n;i++){//直到所有员工遍历完为止
		if(num[i]) cnt+=num[i];
		else cnt++;//尽管是0也会填补上。
		ans+=(num[i]==0);//有缺口。
	}
	
	printf("%d\n",ans);
	
	return 0;
}
```


---

## 作者：_d_h_f (赞：0)

## Solution

考虑序列的合法性。

由题意可知，如果第 $i$ 人的上司个数为 $a_i$，那么他的直接上司的上司个数为 $a_i-1$，也就是说，如果序列合法，即对于 $1 \le i \le n$ 且 $i \ne s$，$a_i-1$ 必定存在于序列中，也就是说排序序列中的数，序列中的每个元素要么等于前面的数且不等于 $0$，要么就是等于前面的数加一。

实现可以使用桶，方便统计，注意我们这里会使用一个计数器 $cnt$，初值为 $0$，判定条件为 $cnt < n$，这里的 $cnt$ 不能等于 $n$，不然会导致后面一个数同样被算进去。

## Code


```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 5;

int n, s, ans;

int a[N];

signed main() {
	
	scanf("%lld %lld", &n, &s);
	
	for (int i = 1; i <= n; ++i) {
		
		int x;
		
		scanf("%lld", &x);
		
		if (i == s)
			ans += (int)(x != 0);
		else
			a[x] ++;
		
	}
		
	int tot = 1;	
		
	for (int i = 1; i <= n && tot < n; ++i)
		if (a[i] == 0)
			tot ++, ans ++;
		else
			tot += a[i];
	
	printf("%lld\n", ans);
			
	return 0;
	
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

我们想一想什么样的序列满足题目条件。

- 首先它有且仅有一个 $0$，且恰好 $a_s=0$。
- 其次，我们设 $fa_i$ 表示 $i$ 的父节点，那么应有 $a_i=a_{fa_i}+1$，所以 $a$ 序列在值域上应是连续的。

这样化简完题意就不难想到一个方法来暴力求答案。初始时 $a$ 序列在值域上会有很多洞（即存在某些 $i$ 使得不存在 $a_j=i$），那么由于它只能有一个 $0$，我们先拿 $0$ 去补洞，如果还补不完，就从大到小贪心地拿数去补洞，每补一个洞就令答案加一即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200010;
int a[N],cnt[N<<1];
int main()
{
	int n,s,ans=0,mx=0;
	cin>>n>>s;
	for(int i=1;i<=n;i++) cin>>a[i],mx=max(mx,a[i]);
	if(a[s]) ans++,a[s]=0;
	for(int i=1;i<=n;i++) cnt[a[i]]++;
	int pt=1;
	while(cnt[0]>1)
	{
		if(!cnt[pt]) cnt[pt]=1,mx=max(mx,pt),cnt[0]--,ans++;
		pt++;
	}
	pt=mx;
	for(int i=1;i<=pt;i++)
	{
		if(!cnt[i]) cnt[i]=1,ans++,cnt[pt]--;
		while(!cnt[pt]) pt--; 
	}
	cout<<ans;
}

---

## 作者：ZJle (赞：0)

### CF729E Subordinates
CF评分：$1900$ (我觉得高了)

这题就是贪心， $s$ 表示这棵树的起点,同时题目可以表示将这个序列更改多少次可以组成一个深度不断层的树。

显然, $01112222333$ 这是符合要求的。

### step 1
将所有的元素 $a[i]$ 都装入 $cnt[a[i]]$ 中，  $cnt[a[i]]$ 表示 $a[i]$ 出现的次数。

### step 2
当 $a[s]≠0$ 的时候，显然， $ans+1$ ，接着就是排序。

### step 3
对于每个点，如果 $cnt[i]=0$ ，我们可以贪心的让最大的点插到 $i$ 这个位置上，最后输出 $ans$ 即可。

实现细节需要自己考虑，本题解不再细讲，可以看代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void file(){
   ios::sync_with_stdio(false);
   cin.tie(0),cout.tie(0);
}
int n,s;
int a[200005],cnt[200005];
auto main() ->signed{
    file();
    memset(cnt,0,sizeof cnt);
    cin>>n>>s;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cnt[a[i]]++;
    }
    int ans=0;
    if(a[s]!=0){
        ans++;
        cnt[a[s]]--;
        a[s]=0;
        cnt[0]++;
    }
    sort(a+1,a+1+n);
    int ui=n,op=a[n]+1;
    int yu=cnt[0]-1;
    for(int i=1;;i++){
        while((cnt[op]+yu)==0){
            op--;
        }
        if(i>op&&yu==0) break;
        if(cnt[i]==0){
            if(yu!=0){
                ans++;
                yu--;
                cnt[i]++;
            }
            else{
                cnt[op]--;
                cnt[i]++;
                ans++;
            }
        }
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：0)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/16741113.html)

[题目传送门](https://www.luogu.com.cn/problem/CF729E)

## 题目分析

这是一道思维题。

首先我们要找到这道题的突破口，即比较特殊的人——主管。

主管一定没有上司，那么回答 $0$ 的就会有两种人：回答错误的人或主管。

接着我们再看其他员工的上司。由于员工之间的关系构成了一棵树，所以一个员工的上司数量一定只比他父亲（直接上司）的上司数量多 $1$。

那么不难推出这个数列的性质：

1. 只有一个 $0$（主管）。

2. 数列必须是连续的。

然后就开始找，一旦发现没有连续的部分，直接把最大的数填进去就可以了。

## 贴上代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,s;
int x;
int bot[maxn];
int cnt,ans;
inline void init(){
	cin>>n>>s;cnt=1;
	for(register int i=1;i<=n;++i){
		cin>>x;
		if(x>0&&i==s) ans++;
		else bot[x]++;
	}
}
int main(){
	init();
	for(register int i=1;cnt<=n-1;++i){
		if(bot[i]==0) cnt++;
		else cnt+=bot[i];
		if(bot[i]==0) ans++;
	}
	cout<<ans;
}
```

---

## 作者：lskksl (赞：0)

自评此题难度为黄到绿，有思维的题，算法难度很低。

显然既然是一棵有根树树则必然有且仅有一个 $0$ 存在。~~两个老板岂不是要打起来。~~

而且，树的性质告诉我们，上下级之间不会存在代差。也就是说，这个数列必须是连续的。

**总的来说，这道题有两个性质：只有一个 $0$ 且数列是连续的。**

最后思路很明确了，就是一个贪心分配，大的补给小的就行了。

---

