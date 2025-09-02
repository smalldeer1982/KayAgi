# Teleporters (Easy Version)

## 题目描述

The only difference between the easy and hard versions are the locations you can teleport to.

Consider the points $ 0, 1, \dots, n $ on the number line. There is a teleporter located on each of the points $ 1, 2, \dots, n $ . At point $ i $ , you can do the following:

- Move left one unit: it costs $ 1 $ coin.
- Move right one unit: it costs $ 1 $ coin.
- Use a teleporter at point $ i $ , if it exists: it costs $ a_i $ coins. As a result, you teleport to point $ 0 $ . Once you use a teleporter, you can't use it again.

You have $ c $ coins, and you start at point $ 0 $ . What's the most number of teleporters you can use?

## 说明/提示

In the first test case, you can move one unit to the right, use the teleporter at index $ 1 $ and teleport to point $ 0 $ , move two units to the right and use the teleporter at index $ 2 $ . You are left with $ 6-1-1-2-1 = 1 $ coins you don't have enough coins to use another teleporter. You have used two teleporters, so the answer is two.

In the second test case, you go four units to the right and use the teleporter to go to $ 0 $ , then go six units right and use the teleporter at index $ 6 $ to go to $ 0 $ . The total cost will be $ 4+6+6+4 = 20 $ . You are left with $ 12 $ coins, but it is not enough to reach any other teleporter and use it so the answer is $ 2 $ .

In the third test case, you don't have enough coins to use any teleporter, so the answer is zero.

## 样例 #1

### 输入

```
10
5 6
1 1 1 1 1
8 32
100 52 13 6 9 4 100 35
1 1
5
4 5
4 3 2 1
5 9
2 3 1 4 1
5 8
2 3 1 4 1
4 3
2 3 4 1
4 9
5 4 3 3
2 14
7 5
5 600000000
500000000 400000000 300000000 200000000 100000000```

### 输出

```
2
2
0
1
2
2
1
1
1
2```

# 题解

## 作者：arrow_king (赞：2)

## 思路

因为只能从 $0$ 出发，所以可以发现使用一个传送器（即，从 $0$ 到达该传送器再使用传送器返回 $0$）的花费是一定的。

这就有了一个贪心思路：首先计算使用每个传送器的总花费，然后由小到大排序，最后从花费小的传送器开始枚举，计算能使用多少次。

时间复杂度 $\mathcal O(n\log n)$。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n,c,a[200005];
int main() {
	t=read();
	while(t--) {
		n=read(),c=read();
		for(int i=1;i<=n;i++) {
			a[i]=read();
			a[i]+=i;
		}
		sort(a+1,a+n+1);
		int ans=0;
		for(int i=1;i<=n;i++) {
			if(c>=a[i]) {
				c-=a[i];
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：LincW (赞：1)

每次用完传送器都会被传送至 $0$ 点。

所以每次使用传送器都要先从 $0$ 走到 $i$（因为上一次使用会让位置变为 $0$ 且初始状态位置为 $0$）。

所以使用传送器 $i$ 的成本要加上从 $0$ 走到 $i$ 的成本。

对于传送器 $i$，实际成本 $b_i=a_i+i$。

所以就是把传送器按 $b$ 升序排序，再按照排序后的顺序依次使用，每次使用时 $c\gets c-b_i$。

若使用传送器 $j$ 后 $c<0$，当前已使用的传送器数量减一（减一是为了除去传送器 $j$）就是答案。

```cpp
#include<iostream>
#include<algorithm>
#define endl '\n'
using namespace std;
typedef long long ll;
ll arr[200005];
int main()
{
	ll t;
	cin>>t;
	while(t--)
	{
		ll n,c;
		cin>>n>>c;
		for(int i=1;i<=n;++i)
		{
			cin>>arr[i];
			arr[i]+=i;
		}
		sort(arr+1,arr+1+n);
		ll sum=0,ans=0;
		for(int i=1;i<=n;++i)
		{
			sum+=arr[i];
			ans++;
			if(sum>c)
			{
				ans--;
				break;
			}
		}
		cout<<ans<<endl;
	 } 
	return 0;
}
```


---

## 作者：BlackPanda (赞：1)

**[Problem](https://www.luogu.com.cn/problem/CF1791G1)**

------------
## Description

有 $t$ 组数据，每次给出 $n$、$c$ 和 $n$ 个整数 $a_i$。

你现在在 $0$ 点，在 $1 \sim n$ 中每个点上都有一个传送器，**且每个传送器只能使用一次**，在点 $i$，可以执行如下操作：

* 向左移动一个单位，花费 $1$ 硬币。

* 向右移动一个单位，花费 $1$ 硬币。

* 在点 $i$ 使用传送器，传送回到 $0$ 点，花费 $a_i$ 个硬币。

你有 $c$ 个硬币，求出从 $0$ 点出发，最多可以使用的传送器个数。

------------
## Solution

建议评橙。

由于影响答案的只有传送器的花费和到达传送器所移动单位长度，所以可以用结构体来存储 $a_i$ 和到达第 $i$ 个传送器所花费的单位长度 $i$。

最后用结构体按照 $a_i$ 和 $i$ 的和排序然后从小到大累加判断 $c$ 最多可以使用多少个传送器即可。

具体细节见代码。

------------
## Code

赛时 AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

struct node
{
	int x, id;
} c[200005];

int n, m, tmp;

bool cmp(node a, node b)
{
	return a.x+a.id <= b.x+b.id;
}

void solve()
{
	memset(c, 0, sizeof(c));
	cin >> n >> m;
	for (int i = 1; i <= n; i ++ )
	{
		cin >> tmp;
		c[i].x = tmp;
		c[i].id = i;
	}
	sort(c + 1, c + n + 1, cmp);
	//for (int i = 1; i <= n; i ++ )
	{
		//cout << c[i].x << " " << c[i].id << endl;
	}
	int i = 0;
	while (m >= 0 && i <= n)
	{
		i ++ ;
		m = m - c[i].x - c[i].id;
	}
	cout << i - 1 << endl;
	return ;
}

int main()
{
	int t;
	cin >> t;
	while (t -- )
		solve();
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

~~这题咋比 E 和 F 都简单？~~

由于每一个点都可以通过传送器回归 $0$ 点，所以往回走肯定不好。

那么考虑计算从 $0$ 点开始，走到 $i$ 点然后通过传送器回来的代价。不难发现是 $i + a_i$。

然后按照代价从小到大贪心即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
struct node{
  int x,id;
}c[N];
int a[N];
signed main(){
  int T;
  cin>>T;
  while(T--){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)c[i].x=i+a[i],c[i].id=i;
    sort(c+1,c+n+1,[&](const node&lhs,const node&rhs){
      return lhs.x<rhs.x;
    });
    int cnt=0;
    for(int i=1;i<=n;i++){
      if(m<c[i].x)break;
      cnt++,m-=c[i].x;
    }
    cout<<cnt<<'\n';
  }
  return 0;
}
```

---

## 作者：loser_seele (赞：0)

还是简单题。

不难发现往回退肯定不优，所以我们的策略是每次不断往右走，然后选择一个点回退。

走到一个点的代价是 $ i $，回退需要 $ a_i $ 的代价，所以使用一个点的代价实际上是 $ i+a_i $，于是我们将代价从小到大排序后贪心选择即可。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int a[2000020],ans=0;
void gen(int n)
{
int f[2000020];
for(int i=1;i<=n;i++)
f[i]=i;
do
{
if(0)//add something here.
ans++;
}while(next_permutation(f+1,f+n+1));
}
#define Y cout<<"Yes"<<'\n'
#define N cout<<"No"<<'\n'
int cnt[26],p[26];
signed main()
{
int T;
cin>>T;
while(T--)
{
    int n, c, ans = 0; 
    cin >> n >> c;
    priority_queue<int,vector<int>,greater<int> >q;
    for(int i = 1; i <= n; ++i) 
    {
        int x;
        cin >> x;
        q.push(x+i);
    }
    while(!q.empty()) 
    {
        int x = q.top(); 
        q.pop();
        if(x > c) 
        break;
        ans++;
        c-=x;
    }
    cout << ans << "\n";
}
}
```


---

