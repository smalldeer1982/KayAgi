# Team Training

## 题目描述

在 IT Campus "NEIMARK" 中，有个人训练和团队训练两种形式的竞技编程训练课程！

在接下来的团队训练课程中，将有 $n$ 名学生参加，其中第 $i$ 名学生的技能值由一个正整数 $a_i$ 表示。

教练认为一个团队是强大的，当且仅当其强度至少为 $x$。团队的强度计算方式为：团队成员数量乘以团队成员中的最低技能值。

例如，如果一个团队由技能值为 $[5, 3, 6, 8]$ 的 $4$ 名成员组成，那么该团队的强度为 $4 \cdot \min([5, 3, 6, 8]) = 12$。

在满足每个团队至少有 $1$ 名成员且每个学生必须属于恰好一个团队的前提下，输出可能形成的强大团队的最大数量。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
6 4
4 5 3 3 2 6
4 10
4 2 1 3
5 3
5 3 2 3 2
3 6
9 1 7
6 10
6 1 3 6 3 2```

### 输出

```
4
0
4
2
1```

# 题解

## 作者：Clare613 (赞：6)

~~早上起来就好了？那就整一道。~~
## 题外话
建议评橙。
## 思路
这是一道贪心题，主要是想贪心策略。\
因为题目说了，我们要求出实力值大于等于 $k$ 的团队有最多能有几个，而每个团队的实力值就是这个团队个人实力的最小值乘上人数，所以说我们就可以推测，每一次尽量选择实力强的人组合在一起，原因是不能有一个拖后退的队友。\
于是就把实力排一下序，发现一旦实力大于等于 $k$ 了，就立即把找的人划为一个团队，然后开始再开始找新的团队，最后输出团队数量就行了。
## code:
```C++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+n+1,cmp);
		int ans=0,cnt=0;
		for(int i=1;i<=n;i++){
			cnt++;
			if(a[i]*cnt>=k){
				ans++;
				cnt=0;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：zyen11451425 (赞：1)

# CF2091B Team Training

## 思路

这是一道贪心题。

强度计算方式为：团队成员数量乘以团队成员中的最低技能值。应该尽可能多地组成满足条件的小团队，而较大的技能值可以更容易满足条件，因此应该优先处理较大的技能值。

因此需要从大到小进行排序。


```cpp
sort(a+1,a+n+1,cmp);
```

而后进行判断，找出满足强度至少为  $x$  的团队。


```cpp
for(int i=1;i<=n;i++){ 
	cnt++;//人数
	if(a[i]*cnt>=x){ 
		c++;//方案数量
		cnt=0;
	}
}
```

## 完整代码


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,x,t,a[N];
bool cmp(int a,int b){return a>b;}
int main(){
	cin>>t; 
	while(t--){ 
		cin>>n>>x; 
		for(int i=1;i<=n;i++)cin>>a[i]; 
		sort(a+1,a+n+1,cmp);
		int cnt=0,c=0;
		for(int i=1;i<=n;i++){ 
			cnt++;
			if(a[i]*cnt>=x){ 
				c++; 
				cnt=0;
			}
		} 
		cout<<c<<'\n';
	} 
	return 0; 
}
```

---

## 作者：Mitchell_Dracula (赞：1)

### 题目描述：（题外话）
~~自行翻译。~~

### 思路

个人认为是**贪心**题，所以只要整出贪心策略就好办了。

首先我们需要明白，越大的数越容易成为一段。

贪心时，我们当然最好要把最厉害的分到一队，这样可以防止拖后腿的现象。

到了实现方法上，首先我们先把数组按实力排序，然后从后往前找，找到最大的 $k$，使得 $k \times a_i \ge x$，然后马上分割出来，形成一个团队。最后输出。

策略都摆在这了，那么直接上代码。

还有一点，不开 long long 见祖宗。

### 代码
```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <deque>
#include <stack>
#include <algorithm>
#define int long long

const int N = 1e6 + 5;

int a[N], t, n, m;

bool cmp (int x, int y) {
	return x > y;//注意是大到小 
}
 
int read() {
    int res = 0;
    char c = getchar();
    bool f = false;
    while (c < '0' || c > '9') {
        if (c == '-')
            f = true;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        res = res * 10 + (c - '0');
        c = getchar();
    }
    if (f)
        res = -res;
    return res;
}

void print (int x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    int b[50] = {}, top = 0;
    for (; x; x /= 10) {
        b[++top] = x % 10;
    }
    do {
        putchar(b[top] + '0');
    } while (--top > 0);
}

signed main() {
	t = read ();
	while (t --) {
		n = read ();
		m = read ();
		for (int i = 1 ;i <= n;i ++) a[i] = read ();
		std::sort (a + 1, a + n + 1, cmp);
		int jsq = 0, k = 0;
		for (int i = 1;i <= n;i ++) {
			if (a[i] * (++ k) >= m) {
				jsq ++;
				k = 0;
			}
		}
		print (jsq);
		putchar (' ');
	}
	return 0;
}


```
完美结束 QWQ。

---

## 作者：Lyw_and_Segment_Tree (赞：1)

## 开始解题！

二分答案做法，虽然可以不用二分答案直接贪，但还是分享一下这种做法。

因为题目说了要使分割的段数最大，自然能想到二分这个段数应该是多少，并且这个答案显然是具有单调性的。这可以说明二分的正确性。

然后我们可以发现我们应该把 $a_i$ 越大的学生排在越前面，防止有一个 $a_i$ 非常小的学生使分组不够优。

所以接下来我们只需要关注 `check` 函数即可。也是很简单的，考虑记录当前团队的人数 $cnt$ 和最小值 $mn$，并且用 $res$ 存下能分成的段数，假设我们当前二分的答案是 $x$，那么只要判断是否有 $res \ge x$ 即可说明该答案是否正确。

贴一下 `check` 函数的代码，可以辅助理解：

```cpp
bool ck(ll x) {
    ll cnt = 0, res = 0, mn = LLONG_MAX;
    
    for (ll i = 1; i <= n; i++) {
        cnt ++, mn = min(mn, a[i]); 
        
        if (cnt * mn >= m) res ++, cnt = 0, mn = LLONG_MAX;
    
        // cout << cnt << " " << mn << "\n";
    }
    
    return res >= x;
}
```

因为二分也没什么细节，所以直接贴代码了。

```cpp
// Problem: B. Team Training
// Contest: Codeforces - Codeforces Round 1013 (Div. 3)
// URL: https://codeforces.com/contest/2091/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Auther: Lyw_and_Segment_Tree

#include <bits/stdc++.h>
#define ll long long
#define db double
#define vec vector
#define pll pair<ll, ll>
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

namespace fastio {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
	
	const ll getc() {
	    return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
	}
	
	const ll read() {
		ll x = 0, f = 1;
		
		char ch = getc();
		
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -1; ch = getc();
		}
		
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
		}
		
		return x * f;
	}
	
	const void write(ll x) {
		if (x < 0) {
			putchar('-'), x = -x;
		}
		
	    ll sta[35], top = 0;
	    
	    do {
	        sta[top++] = x % 10, x /= 10;
	    } while (x);
	    
	    while (top) putchar(sta[--top] + 48);
	}
}

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, a[200005]; string s;

ll opt, l, r, ans = 0;

bool ck(ll x) {
    ll cnt = 0, res = 0, mn = LLONG_MAX;
    
    for (ll i = 1; i <= n; i++) {
        cnt ++, mn = min(mn, a[i]); 
        
        if (cnt * mn >= m) res ++, cnt = 0, mn = LLONG_MAX;
    
        // cout << cnt << " " << mn << "\n";
    }
    
    return res >= x;
}

int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;
    
    ll T = rd();
    
    while (T--) {
        n = rd(), m = rd();
        
        for (i = 1; i <= n; i++) a[i] = rd();
        
        sort(a + 1, a + n + 1, greater<ll>());
        
        l = 1, r = n, ans = 0;
        
        while (l <= r) {
            ll md = (l + r) >> 1;
            
            if (ck(md)) {
                l = md + 1, ans = md;
            } else {
                r = md - 1;
            }
        }
        
        wt(ans), puts("");
    }
    
	return 0;
}
```

[AC record](https://codeforces.com/contest/2091/submission/312764177)

---

## 作者：ZMQ_Ink6556 (赞：1)

## 题解：CF2091B Team Training

### 解题思路

考虑**贪心**，优先向一个队伍中添加实力更高的人。

证明：若排序后数列 $a$ 如下：

$$a_1 , a_2 , a_3 , a_4 , a_5 , a_6$$

若能够选中 $2$ 队（红色和蓝色）：

$$a_1 , \color{Red} a_2 , a_3 , a_4 \color{Black} , \color{Blue} a_5,a_6$$

则以下换法不优于上述做法，即不能剩下更多的人来给分值更小的人：

$$a_1 , \color{Red} a_2 , a_3 \color{Black} , \color{Blue} a_4 \color{Black} , \color{Red} a_5 \color{Black} , \color{Blue} a_6$$

因为红队仍然是 $a_2 \times 3$，但是蓝队变成了 $a_4 \times 2 \le a_5 \times 2$。

如果把整个红色都放在蓝色中间：

$$a_1 , \color{Blue} a_2 \color{Black} , \color{Red} a_3 , a_4 , a_5 \color{Black} , \color{Blue} a_6$$

此时不但不能剩下更多的数值，反而可能浪费掉蓝色队伍，导致队伍数量减少。因为如果能够节省下这个 $\color{Blue} a_2$ 则一定会继续表示成一个前蓝后红的样子。

综上，**排序**后从大到小**贪心选择**即可。

时间复杂度：$O(n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t , n , x , a[200005] , cnt , ans;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> x;
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
		}
		sort(a + 1 , a + n + 1);
		cnt = ans = 0;
		for(int i = n ; i >= 1 ; i--)
		{
			cnt++;
			if(cnt * a[i] >= x)
			{
				ans++;
				cnt = 0;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：wrh316 (赞：1)

### 思路
假设一个团队中有 $k$ 人，$a _ {1}$ 是技能最低的学生。那么所有其他参与者的技能都将大于或等于，即 $a _ {1} \leq a _ {2}, \ldots a _ {k}$。$a _ {1}$ 的值越大，组成团队所需的人数就越少。

我们可以选择当前的学生 $a_i$ 是否是团队中最弱的。如果不选，则意味着我们将暂时搁置该学生，以便为团队添加新成员。如果选，则意味着我们将从被搁置的学生中添加一些人数，即 $x \leq a_i \times k$，其中 $k$ 是团队中的学生人数。每换一个学生，如果他是最弱的，那么团队的规模就会单调地不递减。为了最大限度地增加强队的数量，强队的规模应尽可能小，这才适合强队。

因此，当我们找到一个可以被称为团队中最弱的学生，但同时团队成员的数量又能让团队变得强大时，我们就会立即组建这样一个强大的团队。时间复杂度为 $O(n \operatorname{log} n)$。

### 代码
```c++
#include <bits/stdc++.h>
using namespace std;

int t, n, x;
int a[200005];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> x;
		for (int i = 1; i <= n; i++) cin >> a[i];
		sort(a + 1, a + n + 1, greater<int>());
		int ans = 0, cnt = 0;
		for (int i = 1; i <= n; i++) {
			cnt++;
			if (a[i] * cnt >= x) {
				ans++;
				cnt = 0;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Eric1030 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF2091B)

## 思路进解
首先我们把每一组数据输入进来，然后把每一组的 $a_i$ 从大到小排序，最后用循环来枚举以 $a_i$ 为结尾的组数，最后把每次算出来的值相加即可。

还有一种方法是把每一组的 $a_i$ 从小到大排序，但思路和上面的差不多，就不在这里讲解了。

## AC 记录
![](https://cdn.luogu.com.cn/upload/image_hosting/jo07m7f9.png)

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[200005],k,sum;
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        sum=0; 
        memset(a,0,sizeof(a));//a数组记得清0
        cin>>n>>k;
        for(int j=1;j<=n;j++)
        {
            cin>>a[j];
        }
        sort(a+1,a+1+n,greater<int>());//把a数组从大到小排序
        int cnt=0;
        for(int j=1;j<=n;j++)//计算以a[j]为结尾的组数
        {
            cnt++;//团队人数+1，因为上一次是以a[j-1]结尾的
            if(cnt*a[j]>=k)//a[j]是一组中的最后一个，因此它就是最小的
            {
                sum++;//组数+1
                cnt=0;//团队人数清零，方便下一次计算
            }
        }
        cout<<sum<<endl;//输出组数
    }
    return 0;//结束！
}
```

---

## 作者：Kratos_Charger (赞：0)

## CF2091B Team Training 题解

### 题目大意

有 $n$ 名学生参加编程训练，每名学生有一个技能值 $a_i$。教练认为一个团队是强队的条件是：团队的力量至少为 $x$。团队力量的计算方式是：团队成员数量 $\times$ 团队成员中的最小技能值。

要求输出可以组成的强队最大数量，每个学生必须恰好属于一个团队。

### 思路

这个问题可以通过贪心算法来解决。

为了最大化团队数量，应该尽可能多地组成满足条件的小团队，而较大的技能值可以更容易满足条件，因此应该优先处理较大的技能值。

将学生技能值按从大到小排序，然后遍历排序后的数组，维护当前团队的人数。

每当当前团队人数 $\times$ 当前学生技能值大于或等 $x$ 时，就形成一个团队，并重置人数计数器。

最后统计形成的团队总数。

### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N];
bool cmp(int x,int y){return x>y;}
void solve(){
    int n,x;
    scanf("%d%d",&n,&x);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    sort(a,a+n,cmp); // 从大到小排序
    int res=0,cnt=0;
    for(int i=0;i<n;i++){
        cnt++; // 当前团队人数增加
        if((long long)a[i]*cnt>=x){ // 检查是否满足条件
            res++; // 团队数增加
            cnt=0; // 重置人数计数器
        }
    }
    printf("%d\n",res);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
```

---

## 作者：wuyouawa (赞：0)

###  题目大意

在 IT 校园 "NEIMARK" 上，有关于竞争编程的训练课程 — 包括个人和团队训练！

下一次团队训练会有 $n$ 名学生参加，每个学生的技能值为正整数 $a_i$。

教练认为，如果一个团队的强度至少为 $x$，那么这个团队是强团队。团队的强度计算方式为：团队成员人数乘以团队成员中的最小技能值。

例如，如果一个团队由 4 个成员组成，技能值分别为 $[5, 3, 6, 8]$，那么该团队的强度为 $4 \times \min([5, 3, 6, 8]) = 12$。

请输出最大可能的强团队数量，前提是每个团队至少有一个成员，并且每个成员必须属于一个且仅属于一个团队。

###  思路

贪心。

首先因为方便后面求最小值，先从大到小排序。

接着直接扫一遍，每次只要当前实力大于等于 $x$，强团队数量就加 $1$，易证这是最优的。

最后输出答案即可。

注意清零。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a[200005],cnt,s;
int main(){
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&x);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		sort(a+1,a+n+1,greater<int>());
		cnt=0;
		s=0;
		for(int i=1;i<=n;i++)
		{
			cnt++;
			if(a[i]*cnt>=x)
			{
				s++;
				cnt=0;
			}
		}
		printf("%d\n",s);
	}
	return 0;
} 

```

---

## 作者：nannangua (赞：0)

### 建议
简单的贪心题，建议评橙。

### 思路
大概的贪心策略就是先对总共的 $n$ 个人的战力进行排序，然后从战力大到小进行遍历。若发现队伍内的战斗力大于等于 $k$ 则划分为一组，以此类推继续进行划分直到分完为止。

### 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long  
using namespace std;
const int N=200006;
int T,a[N],cnt,ans;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		int n,x;
		cin>>n>>x;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		sort(a+1,a+n+1);
		cnt=ans=0;	
		for(int i=n;i>=1;i--)
		{
			cnt++;
			if(cnt*a[i]>=x)
			{
				ans++;
				cnt=0;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：RyanLi (赞：0)

传送门：洛谷 [CF2091B Team Training](https://www.luogu.com.cn/problem/CF2091B) | Codeforces [B. Team Training](https://codeforces.com/contest/2091/problem/B)

更佳的阅读体验：[CF2091B 题解](https://blog.ryanli.top/index.php/archives/269/)

---

**简要题意**：给定长度为 $n$ 的序列 $a$，将序列划分为 $k$ 段，使得尽可能多的段中最小元素与段长的乘积不小于 $x$。求 $k$ 的值。

读完题我们首先可以自然地想到：当某个元素已经不小于 $x$ 时，它自己就可以成为一个单独的段。也就是说，越大的元素越容易成为单独的一段。

由此我们想到贪心。我们将序列 $a$ 从大到小排序，那么排在前面的元素如果可以成为一段，那么这个段的长度一定是较小的。因此排序后我们从头到尾遍历整个序列，每当可以构成一段就给答案 $+1$。可以证明这样的贪心策略是正确的。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2e5 + 10;
int t, n, x, a[N], last, ans;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    for (cin >> t; t; --t) {
        ans = last = 0;
        cin >> n >> x;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        sort(a + 1, a + n + 1, greater<>());
        for (int i = 1; i <= n; ++i)
            if (a[i] * (i - last) >= x) {
                ++ans;
                last = i;
                continue;
            } 
        cout << ans << '\n';
    } return 0;
}
```

---

