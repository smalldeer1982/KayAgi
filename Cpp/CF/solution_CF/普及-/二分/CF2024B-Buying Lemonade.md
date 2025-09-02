# Buying Lemonade

## 题目描述

有一台柠檬水自动售货机。机器上有 $n$ 个槽位和 $n$ 个按钮，每个槽位对应一个按钮，但你并不知道每个按钮对应的是哪个槽位。

当您按下第 $i$ 个按钮时，有两种可能的事件：
- 若 $i$ 号槽位有至少一瓶柠檬水，则其中一瓶柠檬水会从这个槽位里掉下来，然后你会把它取走。
- 若 $i$ 号槽位没有柠檬水，则什么都不会发生。

柠檬水下落速度很快，因此您看不清它从哪个槽位掉出。您只知道每个槽位中瓶装柠檬水的数量 $a_i (1 \le i \le n)$。

您需要求出至少收到 $k$ 瓶柠檬水的最小按按钮次数。

数据保证机器中至少存在 $k$ 瓶柠檬水。

## 说明/提示

对于 $100\%$ 的数据，保证 $1 \le n \le 2 \times 10^5$，$1 \le a_i, k \le 10^9$，

## 样例 #1

### 输入

```
5
2 1
1 1
2 2
1 2
3 4
2 1 3
10 50
1 1 3 8 8 9 12 13 27 27
2 1000000000
1000000000 500000000```

### 输出

```
1
2
5
53
1000000000```

# 题解

## 作者：Chenyanxi0829 (赞：3)

最优策略肯定是尽可能少的按没有柠檬水的按钮，所以一开始先把所有按钮都按 $\min_{i=1}^na_i$ 下，如果中途就有 $k$ 瓶了答案就是 $k$。但是按完后就会有一个空了的按钮，考虑最坏情况，一开始就按到了这个按钮，之后就可以排除掉。接下来的操作跟之前一样，把每个没排除掉的按钮按最小值下，中途就有 $k$ 瓶了就直接输出答案。实现时可以先排一遍序，从左到右每次把一个按钮以及它后面的按钮都按 $a_i-a_{i-1}$ 下。
## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 1;

int t, n, a[kMaxN], k, ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t; t--;) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1), ans = 0;
    for (int i = 1; i <= n; i++) {
      if (k <= 1ll * (a[i] - a[i - 1]) * (n - i + 1)) {
        cout << ans + k << '\n';
        break;
      }
      ans += 1 + (a[i] - a[i - 1]) * (n - i + 1), k -= (a[i] - a[i - 1]) * (n - i + 1);
    }
  }
  return 0;
}
```

---

## 作者：DragonForge (赞：1)

# 题解：CF2024B Buying Lemonade
[题目传送门](https://www.luogu.com.cn/problem/CF2024B)


---

注：本文部分参考 @Accepted_100 的题解。
### 题目分析
由于我们并不知道每个按钮对应的槽位，所以一次性把同一列全部按完是不优的。这时考虑一整排一个一个按。注意到 $a_i$ 的取值范围是 $1 \le a_i \le 10^9$，直接暴力枚举一定是不优的，用复杂度为 $\theta(\log n)$ 的二分进行查找。找到的这一行并不是所需要的这一行，还要再往上取几瓶柠檬汁，最后统计并输出。

code

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

int n,k,a[400005];

inline bool check(int x){
	int res=0;
	for(int i=1;i<=n;i++){
		res+=min(x,a[i]);
		if(res>=k){
			return true;
		}
	}
	return false;
}
void slove(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=0,r=1e9,mid;
	while(l<r){
		mid=(l+r+1)>>1;
		if(check(mid)){
			r=mid-1;
		}
		else{
			l=mid;	
		}
	}
	int ans=0,sum=0;
	for(int i=1;i<=n;i++){
		sum+=min(a[i],l);
		if(a[i]<l){
			ans+=a[i]+1;
		}
		else{
			ans+=l;
		}
	}
	for(int i=1;i<=n;i++){
		if(a[i]==l){
			ans++;
		}
		if(sum<k&&a[i]>l){
			ans++,sum++;
		}
	}
	cout<<ans<<endl;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		slove();
	}
	return 0;
}
```
[AC记录](https://codeforces.com/contest/2024/submission/287920150)

---

## 作者：_Michael0727_ (赞：1)

# 题解：CF2024B Buying Lemonade

[文章食用效果更佳](https://www.luogu.com.cn/article/0bjm7elh)

---

## 审题

[题目传送门](https://www.luogu.com.cn/problem/CF2024B)

---

## 思路

我们要让按到空饮料机的次数最少，就应尽量避免出现有饮料机为空的情况。这样容易想到每次把所有还没确认为空的饮料机都按一遍，直到获得 $k$ 瓶饮料。

---

**AC 代码**

```cpp
# include <bits/stdc++.h>
using namespace std ;
int main ( )
{
	unsigned long long t ;
	cin >> t ;
	while ( t -- )
	{
		unsigned long long n , k , ans = 0 , cnt = 0 ;
		cin >> n >> k ;
		unsigned long long a [n + 1] ;
		for ( unsigned long long i = 1 ; i <= n ; i ++ )
		{
			cin >> a [i] ;
		}
		sort ( a + 1 , a + n + 1 ) ;
		if ( k <= n )
		{
			cout << k << endl ;
			continue ;
		}
	    for ( unsigned long long i = 1 ; i <= n ; i ++ )
		{
	        if ( cnt + ( n - i + 1 ) * a [i] >= k )
			{
	            ans += k - cnt ;
	            break ;
	        }
	        cnt += a [i] ;
	        ans += a [i] + 1 ;
	    }
	    cout << ans << endl ;
	}
	return 0 ;
}
```

---

[AC 记录](https://codeforces.com/contest/2024/submission/288673508)

---

## 作者：CEFqwq (赞：1)

好题，但是感觉难于 C。

考虑本题让我们最小化的是什么。表面上是操作次数，实际上是按了按钮但没有出柠檬水的次数。

如何最小化呢？我们容易发现，记当前还有柠檬水且柠檬水数量最少的格子里柠檬水数量为 $x$，那么每个没有被排除的格子按 $x$ 下是一定优的。但是因为当前柠檬水数量 $x$ 的格子刚好被按完（你不知道它是哪一个格子），所以在下一次按的时候，最坏情况下你要把这些格子也按一遍，然后把这些格子排除。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k;
int a[1000005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin >> t;
	while (t--){
		cin >> n >> k;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		sort(a + 1, a + 1 + n);
		int l = 1, sum = 0, ans = 0;
		while (1){
			int gx = (a[l] - a[l - 1]) * (n - l + 1);//当前最小值乘以还有柠檬水的格子数量
			if (sum + gx >= k){
				ans += k - sum;//注意如果全按一遍已经大于等于 k 就不需要多按一遍空格子了
				break;
			}else{
				sum += gx;
				ans += gx;//加上这一轮按的次数
				int pos = a[l];
				while (a[l] == pos)
					l++, ans++;//注意这里直接排除掉了，因为柠檬水还不够，一定会再取
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```

彩蛋：[154](https://codeforces.com/bestRatingChanges/15402155)。

---

## 作者：myyyIisq2R (赞：1)

注意到把每个按钮全按一遍答案一定不劣，直到把某一个机子按空。那么我们可以从小到大排序，直到把某一个机子按空之前一直从左向右按，接下来再从第二个机子开始向右按，以此类推，模拟即可。排序复杂度 $O(n \log n)$，计算复杂度 $O(n)$。
```cpp
int T = read();
while(T--)
{
    int n = read(),b = read();
    for(int i{1};i<=n;i++) a[i] = read();
    sort(a+1,a+1+n);
    int tg{};
    int ti{};
    for(int i{1};i<=n;i++)
    {
      while(a[i]-tg == 0) i++,ti++;
      int val = (a[i] - tg) * (n-i+1);
      if(b > val) b -= val,tg = a[i],ti+=val,ti++;
      else{ti += b;break;}		
    }
    writeln(ti);
}
```

---

## 作者：chenxi2009 (赞：1)

# 思路
简单贪心。由于需要考虑最坏情况我们假设如果接下来存在空的饮料机我们按到的一定是它。我们要让按到空饮料机的次数最少，就尽量避免出现有饮料机为空的情况。这样容易想到每次把所有还没确认为空的饮料机都按一遍，直到获得 $k$ 瓶饮料。

直接写会超时，我们每次不止按一轮而是按到某一个饮料机为空可以达到 $O(n\log n)$ 的复杂度。
# 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int T,n,a[200001],k,ans,cnt;//ans 为按钮次数，cnt 为已得饮料数
int main(){
	scanf("%d",&T);
	while(T --){
		ans = cnt = 0;
		scanf("%d%d",&n,&k);
		for(int i = 1;i <= n;i ++){
			scanf("%d",&a[i]);
		}
		sort(a + 1,a + n + 1);
		for(int i = 1;i <= n;i ++){
			if(cnt + (long long)(n - i + 1) * (a[i] - a[i - 1]) >= k){//long long 防爆；如果说在按到这个饮料机为空之前可以满足需求：
				ans += k - cnt;
				break;
			}
			else{
				ans += (n - i + 1) * (a[i] - a[i - 1]) + 1;//按到了一次这个空饮料机
				cnt += (n - i + 1) * (a[i] - a[i - 1]);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：AK_400 (赞：1)

大概是类似这个的东西。
![](https://cdn.luogu.com.cn/upload/image_hosting/1fhpz2sx.png)

你一列一列地选肯定不优，因为会拿到更多的少的导致浪费步数。

于是一行一行地选。

因为 $a_i\le10^9$ 于是你考虑二分最多选几层拿不到 $k$ 个，因为二分的是最多的，所以再选一层就够了，暴力即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[400005];
bool chk(int x){
    int res=0;
    for(int i=1;i<=n;i++){
        res+=min(x,a[i]);
        if(res>=k)return 1;
    }
    return 0;
}
void slv(){
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    int l=0,r=1e9,mid;
    while(l<r){
        mid=l+r+1>>1;
        if(chk(mid))r=mid-1;
        else l=mid;
    }
    int ans=0,sum=0;
    for(int i=1;i<=n;i++){
        sum+=min(a[i],l);
        if(a[i]<l)ans+=a[i]+1;
        else ans+=l;
    }
    for(int i=1;i<=n;i++){
        if(a[i]==l)ans++;
        if(sum<k&&a[i]>l){
            ans++;
            sum++;
        }
    }
    cout<<ans<<endl;
}
signed main(){
    int T;
    cin>>T;
    while(T--)
    slv();
    return 0;
}
```

---

## 作者：Chenaknoip (赞：0)

一道裸贪心。

定义“按钮按空”表示：该按钮按下若干次后，不再掉下柠檬水（即对应槽位中没有柠檬水）。

设当前有柠檬水的槽位中，数量最少的槽位为 $p$，显然对于每个**已知按下能掉出柠檬水**的按钮，至少需要按 $a_p$ 次，才能使这些槽位中存在“被按空”的槽位。

因此考虑进行如下操作：找到所有有柠檬水的槽位中，数量最少的槽位的柠檬水数，设为 $x$，然后对于所有“没有被按空”的按钮，每个分别按下 $x$ 次。由于是最坏情况，下一个按钮将“被按空”。此时标记这个按钮，并在下一轮中不再按下它。

可以考虑从小到大对数组 $a$ 排序，再从小到大进行枚举，直到已经掉出的柠檬水数量达到 $k$。

总时间复杂度 $O(n \text{log} n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, k, a[200010];
priority_queue<long long, vector<long long>, greater<long long> > q;
// priority_queue<int> q;
int main() {
	long long t;
	scanf("%lld", &t);
	while (t--) {
		while (!q.empty()) q.pop();
		scanf("%lld%lld", &n, &k);
		for (long long i = 1; i <= n; i++) {
			scanf("%lld", &a[i]);
			q.push(a[i]);
		}
		long long tmpn = n, cnt = 0;
		long long ans = 0;
		while (true) {
			if ((q.top() - cnt) * tmpn >= k) {
				ans += k;
				break;
			}
			ans += (q.top() - cnt) * tmpn + 1;
			k -= (q.top() - cnt) * tmpn;
			tmpn--;
			cnt = q.top();
			q.pop();
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Introl (赞：0)

# CF2024B
## 题意简述
给定 $n$ 个按钮，每个按钮对应 $a_i$ 瓶柠檬水，你不清楚哪个按钮对应哪个 $a_i$，按下按钮后，如果有柠檬水就会掉落一瓶，反之则没有任何东西。求至少按多少次按钮可以保证至少收到 $k$ 瓶柠檬水。
## 题意分析
首先题目要求保证至少收到 $k$ 瓶，那么我们可以考虑最坏的情况：每次选择一个按钮时都会选择到容量最少的那个。

在这种情况下，我们不可避免的每个按钮多按一次。所以我们可以考虑贪心。首先可以将 $a_i$ 排序，然后从小到大依次更新获取到的柠檬水数量，同时每次将操作次数多加 $1$。显然这样不是最优，所以在更新过程中考虑，由于每次读取的都比之后的小，所以如果当前的值乘上剩余的按钮数量再加上已经获得的柠檬水数量之和大于等于 $k$，就直接加上 $k$，减去已获得的柠檬水数量就是答案。

形式化的说，设操作次数为 $cnt$，答案为 $ans$，

则对于 $1\le i\le n$，若 $ans+(n-i+1)\times a_i<k,ans\gets ans+a_i,cnt\gets cnt+a_i+1$。

若 $ans+(n-i+1)\times a_i\ge k, cnt\gets cnt+k-ans$ 此时的 $cnt$ 就是答案。
## Code
```cpp
#pragma GCC optimize(1, 2, 3, "Ofast", "inline")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define ONLINE_JUDGE
#define MULTI_CASES
#define endl '\n'
const int MaxN = 2e5+100;
const int INF = 1e9;
const int mod=212370440130137957ll;
int T=1, N, M;
int a[MaxN];
inline void Solve()
{
	cin>>N>>M;
    for(int i=1;i<=N;i++){
        cin>>a[i];
    }
    sort(a+1,a+N+1);
    if(M<=N){
        cout<<M<<endl;
        return;
    }
    int ans=0,cnt=0;
    for(int i=1;i<=N;i++){
        if(cnt+(N-i+1)*a[i]>=M){
            ans+=M-cnt;
            cout<<ans<<endl;return;
        }
        cnt+=a[i];
        ans+=a[i]+1;
    }
    cout<<ans<<endl;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

#ifdef MULTI_CASES
    cin >> T;
    while (T--)
#endif
       Solve();
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}

```

---

## 作者：Gapple (赞：0)

我们的策略是：每一轮把所有按钮全按一遍，如果有一个按钮空了，就把它记录下来，下一轮不按它。

首先，先把 $a$ 升序排序。记录一个 $l$，表示在当前，位置 $\ge l$ 的按钮都非空。

同时，只有 $a_i < 0$ 了，第 $i$ 个按钮才能不按。在 $a_i = 0$ 时，我们需要按一下才能知道它空了。

[赛时代码](https://mirror.codeforces.com/contest/2024/submission/287009357)。

---

