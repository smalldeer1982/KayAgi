# Monsters Attack!

## 题目描述

You are playing a computer game. The current level of this game can be modeled as a straight line. Your character is in point $ 0 $ of this line. There are $ n $ monsters trying to kill your character; the $ i $ -th monster has health equal to $ a_i $ and is initially in the point $ x_i $ .

Every second, the following happens:

- first, you fire up to $ k $ bullets at monsters. Each bullet targets exactly one monster and decreases its health by $ 1 $ . For each bullet, you choose its target arbitrary (for example, you can fire all bullets at one monster, fire all bullets at different monsters, or choose any other combination). Any monster can be targeted by a bullet, regardless of its position and any other factors;
- then, all alive monsters with health $ 0 $ or less die;
- then, all alive monsters move $ 1 $ point closer to you (monsters to the left of you increase their coordinates by $ 1 $ , monsters to the right of you decrease their coordinates by $ 1 $ ). If any monster reaches your character (moves to the point $ 0 $ ), you lose.

Can you survive and kill all $ n $ monsters without letting any of them reach your character?

## 说明/提示

In the first example, you can act as follows:

- during the $ 1 $ -st second, fire $ 1 $ bullet at the $ 1 $ -st monster and $ 1 $ bullet at the $ 3 $ -rd monster. Then the $ 1 $ -st monster dies, the $ 2 $ -nd and the $ 3 $ -rd monster move closer;
- during the $ 2 $ -nd second, fire $ 2 $ bullets at the $ 2 $ -nd monster. Then the $ 2 $ -nd monster dies, the $ 3 $ -rd monster moves closer;
- during the $ 3 $ -rd second, fire $ 2 $ bullets at the $ 3 $ -rd monster. Then the $ 3 $ -rd monster dies.

In the second example, you can fire only $ 1 $ bullet, so you can kill only one of the two monsters during the $ 1 $ -st second. Then, the remaining monster moves closer and kills your character.

## 样例 #1

### 输入

```
5
3 2
1 2 3
-1 2 3
2 1
1 1
-1 1
4 10
3 4 2 5
-3 -2 1 3
5 3
2 1 3 2 5
-3 -2 3 4 5
2 1
1 2
1 2```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：Hacker_Cracker (赞：2)

## CF1923B Monsters Attack! 题解
[站内](https://www.luogu.com.cn/problem/CF1923B) [原址](http://codeforces.com/problemset/problem/1923/B)
### Solution
我们可以采用**贪心**。只要当前的怪物没有被打死，我们就无法阻止怪兽，即失败。为方便计算，我们可以用桶来计数。因为坐标绝对值相等的怪物对于我们来说意义一样的，因此我们可以在桶计数前给  $ x _ i $  赋绝对值。

注意  $ 1 \le a _ i \le 10 ^ 9 , 1 \le n \le 3 \times 10 ^ 5 $  ，需要开 `long long` 。
### [AC](https://www.luogu.com.cn/record/158752675) Code
```cpp
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 3e5 + 10;
ll t[N] , a[N] , p[N];
int abs_read (void) {
	int f = 1 , res = 0;
	char ch = getchar ();
	while (ch < '0' || ch > '9') {
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		res = res * 10 + (ch - '0');
		ch = getchar();
	}
	return res;
}
int main() {
	ll __T = abs_read() ;
	while (__T --) {
		int n = abs_read() , k = abs_read(), f = 1;
		ll sum = 0;
		for (int i = 1 ; i <= n ; i ++) t[i] = 0 , a[i] = abs_read();
		for (int i = 1 ; i <= n ; i ++) {
			p[i] =  abs_read();
			t[p[i]] += a[i];
		}
		for (int i = 1 ; i <= n ; i ++) {
			sum = sum + k - t[i];
			if (sum >= 0) f = 1;
			else {
				f = 0;
				break;
			}
		}
		if (f) puts ("YES");
		else puts ("NO");
 	}
	return 0;
}
```

---

## 作者：QoQ_ (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1923B)

一道较简答的贪心与模拟结合题。

其实只需要把每次来的怪物的血量总和与一共能发射的子弹数比较，如果怪物的血量更大，那么肯定没法通关；如果子弹数更多，那么只要每次都打走在最前面的怪物就肯定可以通关，而如果距离为复数，只需要取它的绝对值即可。

## Code 参考：
```
#include<bits/stdc++.h>
using namespace std;
long long n,t,a[1000001],x[1000001],k,ans,s[1000001];
bool cmp=false;
int main(){
    ios::sync_with_stdio(false);    //加速
    cout.tie(0); cin.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>k;
        ans=0;
        cmp=true;     //默认为可以
        for(long long i=1;i<=n;i++){
            cin>>a[i];
        }
        for(long long i=1;i<=n;i++){
            cin>>x[i];
            s[i]=0;   //不初始化会与上一次存入的数据冲突
            x[i]=abs(x[i]);
        }
        for(long long i=1;i<=n;i++){
            s[x[i]]+=a[i];
        }
        for(long long i=1;i<=n;i++){
            ans+=k;
            ans-=s[i];
            if(ans>=0){
                cmp=true;
            }else{
                cmp=false;
                break;  //如果有一个怪物打不死，那么肯定会有一个怪物来到我们的位置，所以直接跳出，不需要继续计算
            }
        }
        if(cmp==false){
            cout<<"NO"<<"\n";
        }else if(cmp==true){
            cout<<"YES"<<"\n";
        }
    }
    return 0;
}
```
提示：不开 `long long` 见祖宗。

本蒟蒻的第六篇题解，望过~

---

## 作者：Jerry_heng (赞：1)

（一）

注意到 $x_i$ 的绝对值 $\le n$。

那么统计每一个位置的血量和。

先从靠近的击杀必定最优，剩余的子弹用 $sum$ 存储。

还是直接上代码吧。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,k,a[300010],dis[300010],s[300010];
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++)s[i]=0,cin>>a[i];
		int mx=0;
		for(int i=1;i<=n;i++){
			cin>>dis[i],dis[i]=abs(dis[i]);
		}
		for(int i=1;i<=n;i++)s[dis[i]]+=a[i];
		bool op=1;
		int sum=0;
		for(int i=1;i<=n;i++){
			sum+=k-s[i];
			op&=(sum>=0);
		}
		if(op)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：2huk (赞：1)

## Description

数轴上有 $n$ 个怪兽。最初第 $i$ 个怪兽在 $x_i$ 位置上，且血量为 $a_i$。你在位置 $0$ 上。

在每秒钟会发生：

- 你给任意怪兽发射总共 $k$ 颗子弹，受到攻击的怪兽血量减一。
- 血量小于等于 $0$ 的怪兽死亡。
- 没有死亡的怪兽向你移动一个单位。
- 当一个怪兽来到你的位置，你就输了。

问你能不能赢。

多测。$1 \le t \le 3 \times 10^5$，$1 \le k \le 2 \times 10^9$，$1 \le a_i \le 10^9$，$-n \le x_1 < x_2 < x_3 < \cdots < x_n \le n$。

## Solution

首先可以发现，位置在 $\pm p$ 上的怪兽本质上是一样的。\
所以我们可以将所有位置取绝对值，然后用桶维护每个位置上的怪物的总血量。\
对于那些原来就没有怪兽的位置，我们可以认为上面有血量为 $0$ 的怪兽。

根据题意，在第 $0$ 秒时，位置为 $1$ 的怪兽在你面前；第 $1$ 秒时，位置为 $2$ 的怪兽在你面前；第 $i$ 秒时，位置为 $i + 1$ 的怪兽在你面前。\
也就是说，你如果能赢，就代表在 $i$ 秒时，位置在 $1 \sim i$ 的怪兽都能被打败。

所以我们可以贪心。\
在第 $i$ 秒时，我们的主要任务是打败第 $i$ 个怪兽。\
如果能打死，我们先打死怪兽 $i$。\
那么对于剩下的子弹显然不能浪费了，我们可以让它们打 $i$ 之后的怪兽。

实现上，我们维护当前剩余的子弹数。每次这个值加 $k$。然后比较这个值和怪兽的血量即可。

## Code

```cpp
// Problem: B. Monsters Attack!
// Contest: Codeforces - Educational Codeforces Round 162 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1923/problem/B
// Memory Limit: 256 MB
// Time Limit: 2500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

#define int long long
typedef long long ll;
typedef unsigned long long LL;
typedef pair<int, int> PII;

struct FASTREAD {
	template <typename T>
	FASTREAD& operator >>(T& x) {
		x = 0; bool flg = false; char c = getchar();
		while (c < '0' || c > '9') flg |= (c == '-'), c = getchar();
		while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
		if (flg) x = -x; return *this;
	}
	template <typename T>
	FASTREAD& operator >>(vector<T>& x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) >> *it;
		return *this;
	}
}fin;

struct FASTWRITE {
	template <typename T>
	FASTWRITE& operator <<(T x) {
		if (x < 0) x = -x, putchar('-');
		static int buf[35]; int top = 0;
		do buf[top ++ ] = x % 10, x /= 10; while (x);
		while (top) putchar(buf[ -- top] + '0');
		return *this;
	}
	FASTWRITE& operator <<(char x) {
		putchar(x); return *this;
	}
	template <typename T>
	FASTWRITE& operator <<(vector<T> x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) << *it, putchar(' ');
		putchar('\n');
		return *this;
	}
}fout;

const int N = 1e6 + 10;
const int P = 998244353;

void Luogu_UID_748509() {
	int n, k;
	fin >> n >> k;
	vector<int> a(n + 1), b(n + 1), x(n + 1);
	for (int i = 1; i <= n; ++ i ) fin >> a[i];
	for (int i = 1; i <= n; ++ i ) fin >> b[i];
	for (int i = 1; i <= n; ++ i ) x[abs(b[i])] += a[i];
	int lst = 0;
	for (int i = 1; i <= n; ++ i ) {
		lst += k;
		if (lst < x[i]) {
			puts("NO");
			return;
		}
		lst -= x[i];
	}
	puts("YES");
}

signed main() {
	int Testcases = 1;
	fin >> Testcases;
	while (Testcases -- ) Luogu_UID_748509();
	return 0;
}
```

---

## 作者：Elhaithan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1923B)  
### 题意
人物角色处于数轴原点每秒向怪兽发射 $k$ 颗子弹，每颗子弹可射向不同怪兽；第 $i$ 个怪兽一开始血量为 $a_i$，位于数轴上坐标为 $x_i$ 的位置；每个怪兽每秒向原点前进 $1$ 个单位长度，当其血量小于等于 $0$ 时死亡。判断是否有怪兽能到达原点。
### 思路
先向距离原点最近的怪兽射击。

怪兽的坐标有正有负，为了方便排序，读入时取坐标的绝对值。然后对怪兽按距离进行排序。

枚举，令当前怪兽与上一个怪兽的距离为 $d$，因为人物角色每秒发射 $k$ 颗子弹并且怪兽每秒走 $1$ 个单位长度，所以每个怪兽的血量要减去 $d\times k$（第一个怪兽的 $d$ 即为其坐标），若其血量小于零则传递至下一个怪兽。

判断，若当前怪兽的血量仍然大于零，则有怪兽会到达原点，否则继续遍历至第 $n$ 个怪兽。
### code
```cpp
#include <iostream>
#include <algorithm>
#define int long long
constexpr int N = 3e5 + 5;
int T, n, k;
bool flag;
class Node{
  public:
  	int a, x;
  	bool operator < (const Node &p) const{
  		return x < p.x;
  	}
}mon[N];
void solve() {
	scanf("%lld", &T);
	while(T --) {
		flag = false;
		scanf("%lld%lld", &n, &k);
		for(int i = 1; i <= n; i ++) scanf("%lld", &mon[i].a);
		for(int i = 1; i <= n; i ++) {
			int d;
			scanf("%lld", &d);
			mon[i].x = labs(d); //取绝对值
		}
		std::sort(mon + 1, mon + 1 + n); //按距离大小排序
		for(int i = 1; i <= n; i ++) {
			if(mon[i - 1].a < 0) mon[i].a += mon[i - 1].a;
			mon[i].a -= k * (mon[i].x - mon[i - 1].x);
			if(mon[i].a > 0) {
				flag = true;
				break;
			}
		}
		if(flag) puts("NO");
		else puts("YES");
	}
}
#undef int
int main() {
	solve();
	return 0;
}
```

---

## 作者：ziyistudy (赞：0)

简单贪心。

把怪物按照坐标的绝对值从小到大排序，一步一步走，如果剩余子弹总和无法击败该坐标上（绝对值）的所有怪物，则失败。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll MOD=998244353;
// head
const int N=3e5+5;
int a[N],x[N];
vector<PII> V;
signed main() 
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int q;cin>>q;
    while(q--)
    {
        V.clear();
        int n,k;cin>>n>>k;
        for(int i=0;i<n;i++) cin>>a[i];
        for(int i=0;i<n;i++) cin>>x[i];
        for(int i=0;i<n;i++) V.pb({abs(x[i]),a[i]});
        sort(all(V));
        int last=0,cnt=0;
        bool flag=true;
        for(auto it:V)
        {
            if(it.fi!=last) {cnt+=(it.fi-last)*k;last=it.fi;}
            if(it.se>cnt) {flag=false;break;}
            cnt-=it.se;
        }
        if(flag) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}
```

---

## 作者：Fubaogege (赞：0)

数轴上有 $n$ 个怪兽。最初第 $i$ 个怪兽在 $x_i$ 位置上，且血量为 $a_i$。你在位置 $0$ 上。

每秒钟会发生：

- 你给任意怪兽发射总共 $k$ 颗子弹，受到攻击的怪兽血量减 $1$。
- 血量小于等于 $0$ 的怪兽死亡。
- 没有死亡的怪兽向你移动一个单位。
- 当一个怪兽来到你的位置，你就输了。

问你能不能赢。

很明显，每次输出就两种情况：`YES` 和 `NO`，我们只需要分别求出来就行。

- 算法：贪心加模拟。
- 维护剩余子弹数量。
- 每次加 $k$，如果这一秒剩余的子弹数量 $\le$ 这一秒到来的怪兽的总血量，就是输了，否则减去子弹数。

代码：
```c
		for(int i=1;i<=n;i++)
			if((s=s+k)<f[i]=f[i]f[i-1])){
				cout<<"NO\n";
			}
		cout<<"YES\n";
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

数轴上有 $n$ 个怪兽。最初第 $i$ 个怪兽在 $x_i$ 位置上，且血量为 $a_i$。你在位置 $0$ 上。

在每秒钟会发生：

- 你给任意怪兽发射总共 $k$ 颗子弹，受到攻击的怪兽血量减一。
- 血量小于等于 $0$ 的怪兽死亡。
- 没有死亡的怪兽向你移动一个单位。
- 当一个怪兽来到你的位置，你就输了。

问你能不能赢。

$1 \le k \le 2 \times 10^9$，$1 \le a_i \le 10^9$，$-n \le x_1 < x_2 < x_3 < \cdots < x_n \le n$。

## 题目分析

首先我们发现位于 $x$ 的怪兽会在 $\lvert x \rvert$ 秒到达 $0$ 点，这启发我们可以用一个桶统计第 $i$ 秒到达的怪兽的总血量。

接下来，我们考虑贪心，策略是先打先到的怪兽。有了思路，我们直接模拟即可。具体来说，就是维护剩余的子弹数量，每过一秒加上 $k$，如果剩余的子弹数量大于等于这一秒到来的怪兽的总血量，那么减去它即可，否则就是输了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
long long t,n,k,pos[N],sum;
struct foreigner
{
	long long a,x;
}b[N];
void solve()
{
	sum=0;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i].a;
		pos[i]=0;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i].x;
		pos[abs(b[i].x)]+=b[i].a;
	}
	for(int i=1;i<=n;i++)
	{
		sum+=k;
		if(sum<pos[i])
		{
			printf("No\n");
			return;
		}
		else sum-=pos[i];
	}
	printf("Yes\n");
	return;
}
int main()
{
   ios::sync_with_stdio(false);
   cin.tie(0);
   cin>>t;
   while(t--)
   {
    	solve();
   }
   return 0;
}
```

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1923B)
## 解题思路
贪心。

我们先把每个怪兽的位置与数组的坐标对应起来，得到从近到远每个位置上的怪兽血量，这样就可以省去一次排序。

接下来，我们记录当前有的子弹数 $sum$，每秒 $sum \gets sum+k$。再把在当前位置之前的怪兽血量求一个前缀和，与 $sum$ 比较，如果有一秒怪兽总血量大于子弹数，输出 `NO`，退出循环，否则输出 `YES`。

记得把怪兽血量的数组初始化。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[300010],b[300010];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	BREAK:
	while(t--)
	{
		memset(b,0,sizeof b);
		int n,k,sum=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			b[abs(x)]+=a[i];
		}
		for(int i=1;i<=n;i++)
			if((sum+=k)<(b[i]+=b[i-1]))
			{
				cout<<"NO\n";
				goto BREAK;
			}
		cout<<"YES\n";
	}
	return 0;
}

```

---

## 作者：jiangjiangQwQ (赞：0)

### 思路
题目给出 $n$ 个怪物的坐标和血量，你自己在 $0$，每轮你可以**最多**发射 $k$ 个子弹，射向任意个怪物，血量小于等于 $0$ 的怪物将会死去，每轮过后每只怪物朝你逼近，如果有怪物达到你的位置，则你死亡，问是否能无伤通关。因为题目求的是**能否通关**，所以我们要规划一种最优方式击杀这些怪物，那么容易得出**优先击杀最近的怪物**一定是最优的，这就是贪心。所以我们可以对每个怪物的位置排序后直接遍历一遍逐个击破即可。
### 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=3e5+5;
int T,n,k;
struct Node{
    int a,x;
}inp[N];
bool cmp(Node x,Node y){
  //排序，其实血量可以不用排
    if(x.x!=y.x) return x.x<y.x;
    else return x.a<y.a;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>inp[i].a;
        }
        for(int i=1;i<=n;i++){
            cin>>inp[i].x;
            inp[i].x=abs(inp[i].x);
          //为了方便，直接把负数位置的怪物统一放到右边处理，这是没有影响的。
        }
        stable_sort(inp+1,inp+n+1,cmp);
      //对怪物位置进行排序
        // for(int i=1;i<=n;i++){
        //     cout<<inp[i].x<<' '<<inp[i].a<<'\n';
        // }
        int bullet=k,diff=0,flag=1;
        for(int i=1;i<=n;i++){
            if(bullet>=inp[i].a){
              //当前这一轮的子弹足以击杀，直接来下一个
                bullet-=inp[i].a;
            }else{
                inp[i].a-=bullet;
                bullet=0;
                int t=(inp[i].a-1)/k+1;
              //计算击杀他的轮数
                bullet=t*k-inp[i].a;
                diff+=t;
              //diff为每个怪物的位置偏移量
                if(inp[i].x-diff<=0){
                  //击杀之前已经到达我的位置，则失败
                    flag=0;
                    // cout<<i<<' '<<'2'<<'\n';
                    break;
                }
            }
        }
        puts(flag==1?"YES":"NO");
    }
    return 0;
}
```

---

## 作者：N_zzz (赞：0)

明显的贪心。

策略是每次优先打坐标绝对值最小的。

可以用一种简单的写法：处理每个坐标的绝对值的位置上的怪物总血量。从左往右扫，如果当前的总伤害小于总血量则打不完。

```cpp
int main(){
	int T;
	read(T);
	while(T--){
		read(n);
		read(k);
		for(int i=0;i<=n+2;i++)sm[i]=0;
		for(int i=1;i<=n;i++)read(a[i]);
		for(int i=1,t;i<=n;i++)read(t),sm[t]+=a[i];
		int fl=1;
		for(int i=1;i<=n;i++){
			sm[i]=sm[i]+sm[i-1];
			if(i*k<sm[i])fl=0;
		}
		if(fl)puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：modfisher (赞：0)

## 思路
显然先打离的近的。

简单证明：如果先打最近的会死，那么先打更远的显然也会死；如果先打远的，再打最近的不会死，那么先打最近的，再打远的也不会死。

所以简单模拟即可。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 5;

struct node{
	int a, x;
}mon[maxn];

bool cmp(node x, node y){
	return x.x < y.x;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T --){
		int n, k;
		scanf("%d %d", &n, &k);
		for(int i = 1; i <= n; i ++){
			scanf("%d", &mon[i].a);
		}
		for(int i = 1; i <= n; i ++){
			scanf("%d", &mon[i].x);
			if(mon[i].x < 0) mon[i].x *= -1;
		}
		sort(mon + 1, mon + n + 1, cmp);
		int tim = 0;
		bool fl = true;
		int nk = k;
		for(int i = 1; i <= n; i ++){
			tim ++;
			while(i <= n && nk - mon[i].a >= 0){
				if(tim > mon[i].x){
					fl = false;
					break;
				}
				nk -= mon[i ++].a;
			}
			if(i > n || !fl) break;
			mon[i].a -= nk;
			if(tim >= mon[i].x){
				fl = false;
				break;
			}
			if(mon[i].a % k == 0){
				tim += mon[i].a / k;
				if(tim > mon[i].x){
					fl = false;
					break;
				}
				nk = k;
			}else{
				tim += mon[i].a / k;
				if(tim >= mon[i].x){
					fl = false;
					break;
				}
				nk = k - mon[i].a % k;
			}
		}
		printf(fl ? "YES\n" : "NO\n");
	}
	return 0;
}
```

---

## 作者：FeiDing (赞：0)

# 思路

很容易证明这是道贪心，贪心策略是先打离自己近的。

### 证明（不严谨）：

有 $2$ 个怪物 $i$ 和 $j$，如果 $\left | x_i \right| < \left | x_j \right |$，且先打 $j$ 更优。

由于先打 $j$ 更优，所以我们在先打 $j$ 的情况下自己不会被怪物吃掉。

但是，不管怎样顺序，打死这两只怪物的总时间相等，所以我们先打 $i$ 和先打 $j$ 是一样的。

而且在有些情况下，先打远的会导致近的偷家，于是就没有先打近的优。

---

# 实现

虽然怪物从两个方向来，但两个方向本质是一样的。所以我们把怪物都放到数轴的正半轴，也就是取距离的绝对值。

具体就很简单了，直接模拟，看看[代码](https://codeforces.com/contest/1923/submission/247937836)。

---

## 作者：kczw (赞：0)

# 题意
你在数轴原点上打怪，第 $i(1\le i\le n)$ 个怪物有 $a_i$ 血从 $x_i$ 开始向你以每秒一单位距离的速度移动，若其抵达原点，你就无了。

每秒，你可以打出 $k$ 发子弹锁定任意只怪物，每发子弹降低怪物一点血，怪物生命值小于一时它就无了。

问，你最终无没无。
# 思路
对于第 $i$ 秒判断需要的子弹数量 $need_i$ 与 $i\times k$ 的关系。对于位于 $x$ 的怪物，它会在 $|x|$ 秒到达，我们维护一个数组 $c$，令 $c_i$ 为第 $i$ 秒到达怪物的总生命值。

聪明人已经发现了，$need$ 其实就是 $c$ 的前缀和。

维护好 $need$ 后，若有 $need_i>i\times k$，输出 `NO`，否则输出 `YES`。

---

