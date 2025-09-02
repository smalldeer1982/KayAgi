# [SDCPC 2023] Orders

## 题目描述

某工厂在第 $1$ 天开工之前收到了 $n$ 笔订单，第 $i$ 笔订单可以用两个整数 $a_i$ 和 $b_i$ 描述，表示工厂需要在第 $a_i$ 天结束时交付 $b_i$ 件货物。

已知工厂每天能生产 $k$ 件货物，且第 $1$ 天开工之前没有任何存货，问该工厂能否完成所有订单。

## 样例 #1

### 输入

```
2
4 5
6 12
1 3
6 15
8 1
3 100
3 200
4 300
6 100```

### 输出

```
Yes
No```

# 题解

## 作者：LOSpace (赞：5)

[原题链接](https://www.luogu.com.cn/problem/P9556)

## 解题思路

可以使用一个结构体数组存下一笔订单的交付时间和交付数量。因为要在规定时间内完成对应的任务，所以可以进行排序：以交付时间为第一关键字从小到大，再以交付数量为第二关键字从小到大排序。当前任务即为未完成的最靠前订单。

要判断能不能完成一批订单，就要判断到了某一笔订单的交付时间存货够不够交付这一笔订单。如果不够就说明不能完成这一批订单；反之存货减少这一笔订单所需货物数量，然后继续。

**注意：要开 long long 。**

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
struct node {
	long long a, b;
};
bool cmp(node x, node y) {
	return x.a == y.a ? x.b < y.b : x.a < y.a;
}
int main() {
	for (scanf("%d", &T); T --; ) {
		long long n, k, now, last;
		bool flag;
		now = last = flag = 0;
		scanf("%lld%lld", &n, &k);
		node q[n + 5];
		for (int i = 0; i < n; i ++)
			scanf("%lld%lld", &q[i].a, &q[i].b);
		sort(q, q + n, cmp);
		for (int i = 0; i < n && !flag; i ++) {
			now += (q[i].a - last) * k;
      	//当前存货为之前存货加上这次交付时间
         //减去上一次交付时间乘上每天生产数量
			if (now < q[i].b) flag = true;
			else {
				last = q[i].a;
				now -= q[i].b;
			}
		}
		if (!flag) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：Albatross_LC (赞：2)

将 $n$ 笔订单按 $a_i$ 从小到大排序，将存货量每次加上这次与上次交货的时间差乘 $k$ 的积，每次比较一下货够不够用，够用减去交货量，不够输出 No 即可

附上我的代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 101;
struct Node {
	int a, b;
} e[N];//这里要用结构体
bool cmp(Node x, Node y) {
	return x.a < y.a;
}
signed main() {
	int t;
	cin >> t;
	while (t -- ) {
		int n, k;
		cin >> n >> k;
		for (int i = 1; i <= n; i ++ )
			cin >> e[i].a >> e[i].b;
		sort(e + 1, e + 1 + n, cmp);//按时间先后顺序排序
		int sum = 0;
		bool ok = true;
		for (int i = 1; i <= n; i ++ ) {
			sum += (e[i].a - e[i - 1].a) * k;//加上存货量
			if (sum < e[i].b) {//不够用
           ok = false;
				printf("No\n");
				break;
			} else sum -= e[i].b;//够用
		}
		if (ok) printf("Yes\n");
	}
}
```

---

## 作者：zzx114514 (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/P9556)
# 题目大意
某工厂在第 $1$ 天开工之前收到了 $n$ 笔订单，第 $i$ 笔订单可以用两个整数 $a_i$ 和 $b_i$ 描述，表示工厂需要在第 $a_i$ 天结束时交付 $b_i$ 件货物。
已知工厂每天能生产 $k$ 件货物，且第 $1$ 天开工之前没有任何存货，问该工厂能否完成所有订单。
# 解题思路
将每笔订单的信息用结构体存储，按照交付时间从早到晚排序，然后直接模拟，对于每笔订单，当前生产的量为上一笔订单到这一笔订单的时间乘以每天生产的量，如果当前生产的量大于等于需求量，说明能够交付，已生产总量减去交付的量，否则无法交付，直接返回。
# 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,k,sum;
struct Node
{
	long long a,b;//结构体存储订单信息，记得开long long 
} x[105];
bool cmp(Node a,Node b)
{
	return a.a<b.a;//按照时间排序 
}
bool flag;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for (int i=1;i<=n;i++) cin>>x[i].a>>x[i].b;
		sort(x+1,x+n+1,cmp);//排序 
		sum=0,flag=true;//初始化 
		for (int i=1;i<=n;i++)
		{
			sum+=k*(x[i].a-x[i-1].a);//计算当前生产量 
			if (sum>=x[i].b) sum-=x[i].b;//如果可以交付则交付 
			else
			{
				flag=false;
				break;//否则直接返回 
			}
		}
		cout<<(flag? "Yes":"No")<<endl;
	}
	return 0;//华丽的结尾 
}

```


---

## 作者：scp020 (赞：2)

# P9556 [SDCPC2023] A-Orders 题解

签到题，是这场比赛第二简单的题。

## 解法

考虑要在第 $a_i$ 天交付 $b_i$ 件货物，我们就将订单按照 $a_i$ 排序。在每件订单之前（包括这个订单）工厂最多可以生产 $a_i \times k$ 件货物，如果 $\sum \limits _{i=1} ^{i \le a_i} b_i > a_i \times k$，则一定不能按时交付。否则如果一直满足 $\sum \limits _{i=1} ^{i \le a_i} b_i \le a_i \times k$，则有解。

### 实现方案一

排完序后对 $b_i$ 求一遍前缀和，记作 $pre_i$，每求完一次前缀和就判断一下是否满足 $pre_i \le a_i \times k$，如果不满足则无解，如果一直满足则有解。

### 实现方案二

排完序后遍历从 $1$ 到 $n$ 的订单，对于每次订单，我们可以记录一下交付完这次订单最多有多少剩余货物，定义为 $last_i$，$last_i = (a_i - a_{i-1}) \times k + last_i - b_i$（$i \ge 2$），我们认为 $last_1 = a_1 \times k - b_1$。如果 $\exists i \in [1,n]$ 使得 $last_i < 0$，则无解，否则有解。

### 代码（实现方案二）

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace fast_IO
{
	/*
	快读快写代码，可忽略。
	*/
};
using namespace fast_IO;
#define int long long
int t,n,k,last,flag;
struct node
{
	int a,b;
};
node arr[200];
inline bool cmp(const node &x,const node &y)
{
	return x.a<y.a;
}
signed main()
{
	read(t);
	while(t--)
	{
		read(n),read(k),last=0,flag=0;
		for(int i=1;i<=n;i++) read(arr[i].a),read(arr[i].b);
		sort(arr+1,arr+1+n,cmp);
		if(arr[1].a*k<arr[1].b)
		{
			write("No\n");
			continue;
		}
		last=arr[1].a*k-arr[1].b;
		for(int i=2;i<=n;i++)
		{
			if((arr[i].a-arr[i-1].a)*k+last<arr[i].b)
			{
				write("No\n"),flag=1;
				break;
			}
			last=(arr[i].a-arr[i-1].a)*k+last-arr[i].b;
		}
		if(!flag) write("Yes\n");
	}
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```

---

## 作者：Shadow_T (赞：2)

模拟水题，首先将输入数据按交货时间从先到后排序，这里选择用 `struct` 捆绑 $a_i,b_i$ 然后根据 $a_i$ 做指标排序一遍。

这里从上一个任务到下一个任务后很显然还有 $sum-(a_i-a_{i-1})\times k+b_i$ 的剩余货物，这里 $sum$ 即为剩余货物数，然后若对于出现在一次跳转后 $sum<0$ 即无法完成订单，输出 $\texttt{No}$，如果能一直操作到结束就输出 $\texttt{Yes}$。

注意要开 long long。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct st
{
	int a;
	int b;
}x[101];
bool cmp(st a,st b)
{
	return a.a<b.a;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		cin>>x[i].a>>x[i].b;
		sort(x+1,x+1+n,cmp);
		int sum=0;
		bool p=true;
		for(int i=1;i<=n;i++)
		{
			sum=sum+(x[i].a-x[i-1].a)*k-x[i].b;
			if(sum<0)
			{
				p=false;
				puts("No");
				break;
			}
		}
		if(p) puts("Yes");
	}
}
```

---

## 作者：__zfy__ (赞：1)

### 思路
工厂要在 $a_i$ 天前完成 $i$ 个订单，我们不妨使用结构体进行排序，之后就根据题意进行模拟运算，每次检查货物数是否是负数，如果是直接输出 `No`，如果全 $\le 0$，输出 `Yes`。
### 部分代码
首先实现结构体排序：
```cpp
bool cmp(Node a,Node b)
{
	return a.x<b.x;
}//结构体排序。
```
主函数：
```cpp
sort(a+1,a+n+1,cmp);
```
接着实现模拟：
```cpp
for(int i=1;i<=n;i++)
{
	sum+=k*(a[i].x-a[i-1].x);
	if(sum<a[i].y)
   	{
		cout<<"No"<<endl;
		flag=true;
		break;
	}
	else 
	{
   		sum-=a[i].y;
	}
}
```
最后判断是否输出 `Yes`。
```cpp
if(flag==true)
{
	cout<<"Yes"<<endl;
}
```

---

## 作者：ScapegoatTree (赞：1)

可以对订单按照截至日期 $a_i$ 进行排序。

然后计算出每两次订单之间新生产的货物，加入存货中，如果存货不足以交付当前订单，直接输出 $\texttt{No}$，退出，否则把存货减去 $b_i$，如果所有的订单都可以顺利完成，输出 $\texttt{Yes}$。

代码：
```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
const int MAXN=1005;
struct node{
    int a,b;
}a[MAXN];
int cmp(node a,node b){
    return a.a<b.a;
}
void solve(){
    int n;
    std::cin>>n;
    int k;
    std::cin>>k;
    int s1=0,s2=0;
    for(int i=1;i<=n;i++){
        std::cin>>a[i].a>>a[i].b;
    }
    std::sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++){
        s1=a[i].b;
        s2+=k*(a[i].a-a[i-1].a);
        if(s2>=s1){
            s2-=s1;
        }
        else{
            std::cout<<"No\n";
            return;
        }
    }
    std::cout<<"Yes\n";
}
int t;
signed main(){
    std::cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

这题还是很好写的。

#### 分析
我们肯定先要确保数组是有序的，即先把小的天数做掉，然后我们枚举每天，如果天数减去上一天的天数乘上每天能做的数量大于第 $a_i$ 天时交付 $b_i$ 件物品，就把他视为用过，否则不合法。

#### 代码
核心代码如下:

这里的 $sg$ 就是上个天数，$sum$ 是当前物品数。
```cpp
sort(a + 1, a + 1 + n, cmp);
for(int i = 1;i <= n;i ++ ){
	sum += (a[i].x - sg) * k;
	if(a[i].y > sum){
		puts("No");
		flag = 0;
		break;
	}	
	else sum = sum - a[i].y;
	sg = a[i].x;
}
```

---

## 作者：_colin1112_ (赞：1)

+ 一道简单的模拟。

~~尽管我也是发帖问了后才对的~~

## 思路

首先，用一个结构体存每个订单的日期、需求量信息，输入后对日期进行排序，然后进行遍历，如果这个订单的需求量大于之前剩余的货物+生产的货物，就输出 `No`，反之，如果遍历完成后都没有输出 `No`就输出 `Yes`。

**Warning：多测数组要清空**

## AC Code

```c++
#include <bits/stdc++.h>
#define endl '\n'
#define ll long long

using namespace std;
const int E=1e6+5;
ll t;
ll n,k;
struct wjh{
    ll a=0;
    ll b=0;
}arr[E];
inline bool cmp(wjh a,wjh b){
    return a.a<b.a;
}
int main(){
    cin >>t;
    while(t--){
        cin >>n>>k;
        ll sy=0,cnt=0;
        bool flag=true;
        memset(arr,false,sizeof(arr));
        for(int i=1;i<=n;i++){
            cin >>arr[i].a>>arr[i].b;
        }
        stable_sort(arr+1,arr+n+1,cmp);
        for(int i=1;i<=n;i++){
            cnt+=(arr[i].a-sy)*k;
            sy=arr[i].a;
            if(cnt<arr[i].b){
                flag=false;
                break;
            }
            else{
                cnt-=arr[i].b;
            }
        }
        if(flag){
            cout <<"Yes\n";
        }
        else{
            cout <<"No\n";
        }
    }
    return 0;
}
```

---

## 作者：flangeborg (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P9556)

一道非常水的模拟，建议评红。

对于这道题我们只需要对交货批次按时间进行排序，时间早的排在前面，计算当前日的存货量，与交货量相减，判断是否大于 $0$ 即可。

## code
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<string>
#define ll long long
using namespace std;
struct node{
	ll sum,date;
}need[105];  
ll n,k,t,cnt;
bool cmp(node a,node b)
{
	return a.date < b.date;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> k;
		for(int i = 1; i <= n; i++)
			cin >> need[i].date >> need[i].sum;
		ll last = 0;
		cnt = 0;
		bool check = true;
		sort(need + 1,need + n + 1,cmp); // 按时间进行排序 
		for(int i = 1; i <= n; i++)
		{
			cnt += k * (need[i].date - last); // 计算当前存货量 
			last = need[i].date;
			cnt -= need[i].sum;
			if(cnt < 0) // 判断是否能按时交货 
			{
				check = false;
				break;
			}
		}
		if(check) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
```


---

## 作者：Eason_cyx (赞：1)

简单题。

因为时间限制更重要，所以我们以交付日期为第一关键字排序（有没有第二关键字都行）。

记录在每一个交付事件前能做多少货物。对于每一个订单，用之前订单剩下来的数量加上这两个订单之间能做好的货物量，就可以得到交付时的货物数量。如果 $\le b$，则无法完成，输出 `No`；否则让货物交付。


```cpp
#include <iostream>
#include <algorithm>
using namespace std;
struct work {
	long long a,b;
	bool operator < (const work& y) {
		return a < y.a;
	}
};
work w[105];
int main() {
	int T; cin >> T;
	while(T--) {
		long long n,k; cin >> n >> k;
		for(int i = 1;i <= n;i++) {
			cin >> w[i].a >> w[i].b;
		}
		sort(w+1,w+n+1);
		long long nownum = 0,oknum = 1;
		bool flag = true;
		for(int i = 1;i <= n;i++) {
			//做第i份订单
			nownum += (w[i].a - w[i-1].a) * k;
			if(nownum < w[i].b) {
				flag = false;
				break;
			}
			else nownum -= w[i].b;
		}
		if(flag) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
```

挺简单的一道题，考察简单贪心，建议评橙。

---

## 作者：Morishima_zj_zhy (赞：1)

### 题目传送门

[P9556 [SDCPC2023] A-Orders](https://www.luogu.com.cn/problem/P9556)

### 思路
由题面可知，每笔订单结束的时间 $i$ **不会**保证从小到大，那我们可以进行排序，使得 $i$ 的顺序变成从小到大，再进行计算。

排序代码：
```cpp
for (int i = 1; i < n; i++) {
	for (int j = i + 1; j <= n; j++) {
		if (a[i] > a[j]) {
			swap(b[i], b[j]);
			swap(a[i], a[j]);
		}
	}
}
// 先交换所需数量，再交换结束时间，可以避免出错。
```
再仔细观察部分样例：
```
3 100
3 200
4 300
6 100
```
根据样例列出表格，看看工厂库存的实际情况：

| 天数 | 数量 |
| :-----------: | :-----------: |
| $1$ | $0 + 100 = 100$ |
| $2$ | $100 + 100 = 200$ |
| $3$ | $300 - 200 = 100$ |
| $4$ | $100 + 100 = 200$ |


我们假设**没有订单**，让我们看看每天的**生产数量** $k$ 与**每日生产数量**的关系：

| 天数 | 数量 | 与 $k$ 的关系 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $100$ | $1 \times k$ |
| $2$ | $200$ | $2 \times k$ |
| $3$ | $300$ | $3 \times k$ |
| $4$ | $400$ | $4 \times k$ |
| $\vdots$ | $\vdots$ | $\vdots$ |
| $n$ | $n \times 100$ | $n \times k$ | 


我们再次假设**没有订单**，让我们再看看每天的**生产数量** $k$ 与每日**增加**数量的关系：

| 天数 | 增长数量 | 与 $k$ 的关系 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $100$ | $(1 - 0) \times k$ |
| $2$ | $100$ | $(2 - 1) \times k$ |
| $3$ | $100$ | $(3 - 2) \times k$ |
| $4$ | $100$ | $(4 - 3) \times k$ |
| $\vdots$ | $\vdots$ | $\vdots$ |
| $n$ | $100$ | ${n - (n - 1)} \times k$ | 

我们设当前订单的结束时间为 $a$，上一个订单的结束时间为 $b$，其中间时间增长的产品数量为 $u$。

我们可以推出公式：

$$u = (a - b) \times k$$

那么，这题就可以迎刃而解了。

### AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	long long t;
	cin >> t;
	long long n, k;
	long long cnt = 0; // 用于记录当前的库存。
   // 注意要开 long long，不然会越界。
	bool flag = false; // 用来记录当前这组数据中间是否有订单无法按时完成。
	while (t--) {
		cnt = 0;
		flag = false;
		cin >> n >> k;
		long long a[105];
		long long b[105];
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b)); // 每一次记得清零。
		for (int i = 1; i <= n; i++) {
			cin >> a[i] >> b[i];
		}
		for (int i = 1; i < n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (a[i] > a[j]) {
					swap(b[i], b[j]);
					swap(a[i], a[j]);
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			cnt = cnt + k * (a[i] - a[i - 1]);
			if (cnt < b[i]) {
				cout << "No" << endl;
				flag = true;
				break;
			}
			cnt -= b[i];
		}
		if (!flag) cout << "Yes" << endl;
	}
	return 0;
} 
```

---

## 作者：Escapism (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9556)

# 题意

翻译很明晰。

# 思路

我们计算对于每个订单时仓库里有多少存货，即前一个订单时剩下的货物加上两个订单之间的时间里工厂生产的货物数量，如果存货数量不足以交付订单，那么就输出 No，如果所有订单都能满足，则输出 Yes。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 5;
struct Node{ //定义结构体
	int x,y;
} a[MAXN];
bool cmp(Node r1,Node r2){
	if (r1.x != r2.x) return r1.x < r2.x;
	else return r1.y > r2.y; 
}
int main(){
	int q;
	cin>>q;
	while(q--){
		long long n,k;
		cin>>n>>k;
		for (int i = 1;i <= n;i++) cin>>a[i].x>>a[i].y; //输入
		sort(a + 1,a + n + 1,cmp);
		long long sum = 0;
		bool flag = true;
		for (int i = 1;i <= n;i++){ //对 n 个订单进行计算
			sum = sum + k * (a[i].x - a[i - 1].x); //计算存货数量
			if (a[i].y <= sum) sum -= a[i].y; //可以交付
			else{//无法交付
				flag = false;
				break;	
			}
		}
		if (flag == false) cout<<"No"<<endl; //无法交付
		else cout<<"Yes"<<endl;//可以交付
		for (int i = 1;i <= n;i++) a[i].x = a[i].y = 0; //清零
	}
}
```


---

## 作者：lichenzhen (赞：0)

## 题目大意
某工厂每天能生产 $k$ 件货物，有 $n$ 个订单，每个订单要在 $a_i$ 内完成 $b_i$ 件货物。

问工厂能否完成任务。

## 题目解法
这是一道很简单的模拟题，只需要按照题意模拟即可。

我们把订单的信息存在一个结构体中，然后在输入之后按照交货的时间 $b_i$ 从早到晚排一下序。

之后按照循环交货时间的顺序生产，若某一批货物无法按照指定时间完成，直接跳出循环即可。

**注意：题目数据范围较大，在计算过程中会爆 `int`，所以部分变量要用 `long long`。**

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct lcz{
    int a,b;
}v[1000010];
bool cmp(lcz x,lcz y){
    if(x.a!=y.a)return x.a<y.a;
    return x.b<y.b;
}
int main()
{

    int n,T,k;
    cin>>T;
    while(T--){
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>v[i].a>>v[i].b;
        sort(v+1,v+n+1,cmp);
        long long sum=0,f=1;
        for(int i=1;i<=n;i++){
            sum+=(long long)k*(v[i].a-v[i-1].a);
            if(sum<v[i].b){
                f=0;
                break;
            }
            else sum-=v[i].b;
        }
        puts(f?"Yes":"No");
    }
}
```


---

## 作者：hjqhs (赞：0)

首先将所有订单按时间排序。定义一个 `have` 变量代表当前有多少货物，依次枚举每一个订单，设这个订单和前一个订单相差 $x$ 个时间，那么 $have \gets have + x \times k$，并判断 `have` 是否大于等于当前所需货物数量，一旦不够立刻输出 `No` 并 `return`。如果所有订单枚举玩了都没有 `return`，则输出 `Yes`。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;
int t,n,k;
pair<int,int>a[105];
void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>a[i].first>>a[i].second;
	sort(a+1,a+1+n);
	int have=0;
	for(int i=1;i<=n;++i){
		have+=(a[i].first-a[i-1].first)*k;
		if(have>=a[i].second)have-=a[i].second;
		else{cout<<"No"<<'\n';return;}	
	}
	cout<<"Yes"<<'\n';
}
signed main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		solve();
	}
    return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9556)

一道模拟题。

可以命名一个订单的结构体，然后将订单的结束时间进行排序。用一个变量模拟货物的数量，每遇到一个订单，货物的数量就会加上距离上一个订单的天数乘上 $k$。即对于第 $i$ 个订单，距离第 $i-1$ 订单货物数量增加了 $(a_{i}-a_{i-1})\times k$。

如果在模拟过程中出现货物数量不够交付，输出 `No`。

### Code

```cpp
#include <bits/stdc++.h>

namespace xvl_ { 
    #define ll long long
    #define IMAX 1e9
    #define LMAX 1e18
    void debug() { std :: cerr << "debug" << "\n"; } 
    template <typename T> inline T Max(T a, T b) { return a > b ? a : b; }
    template <typename T> inline T Min(T a, T b) { return a < b ? a : b; }
    template <typename T, typename... Args> inline T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
    template <typename T, typename... Args> inline T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
struct order { int x, y; } a[105];
ll T, n, k, sum;
bool flag;
bool cmp(order tmp1, order tmp2) { return tmp1.x < tmp2.x;  }
int main() {
    /*
    freopen("InName.in", "r", stdin);
    freopen("OutName.out", "w", stdout);
    */
    ios :: sync_with_stdio(0);
    cin >> T;
    while (T--) {
        flag = 1, sum = 0;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y;
        sort(a + 1, a + 1 + n, cmp);
        for (int i = 1; i <= n; i++) {
            sum += (a[i].x - a[i - 1].x) * k;
            if (sum < a[i].y) flag = 0;
            else sum -= a[i].y;
        }
        if (flag) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
```


---

## 作者：Crasole (赞：0)

## 题意

-----

某个工厂在第一天前收到了 $n$ 笔订单，每笔订单要在 $a_i$ 天结束时交付 $b_i$ 件货物，已知工厂每天生产 $k$ 件货物，且在第一天前没有任何存货，问该工厂能否完成 $n$ 笔订单。如果能完成就输出 `Yes`，否则输出 `No`。

一共有 $T$ 组数据。

## 思路

-----

对于每一组输入的 $a_i$，需要找到一种合适的安排方案，那么很显然，对于 $a_i$ 与 $a_{i+1}$，$a_i$ 更小就代表订单要更早完成，应该排在更前面。如果 $a_i = a_{i+1}$，则将 $b_i$ 与 $b_{i+1}$ 比较，更小就排更前面。

接着，按照题意模拟，如果说一天一天看过去，显然会超时，所以直接计算，先定义一个 $f$ 变量标记状态，初始化成 $1$，$1$ 表示能完成，$0$ 表示不能完成。

然后一个个订单看过去，两天的时间之差乘上每天的生产个数 $k$：$(a_i - a_{i-1}) \times k$。如果结果比 $b_i$ 小，输出 `No`，同时标记 $f = 0$。否则将生产总数减去 $b_i$，模拟提交订单，然后看下一个订单。

循环结束后，如果 $f = 1$，说明完成所有的订单，输出 `Yes`。

## 代码

-----

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k;
struct node{
	long long a,b;
}a[110];//把a和b写在一共结构体里面
bool cmp(node x,node y){
	return x.a==y.a?x.b<y.b:x.a<y.a;
   //判断函数，如果x的a和y的a相等，比较x的b和y的b
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;	
		for(int i=1;i<=n;i++)
			cin>>a[i].a>>a[i].b;
		sort(a+1,a+n+1,cmp);
		long long sum=0,time=0;bool f=1;//用变量f标记
		for(long long i=1;i<=n;){
        	//按照题意模拟
			sum+=1ll*(a[i].a-a[i-1].a)*k;
			if(sum>=a[i].b) sum-=a[i].b,i++;//完成订单i
			else{
				f=0;break;//不能完成，f=0，然后break
			}
		}
		if(f) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：KAqwq (赞：0)

## 思路
签到题。时间复杂度 $O (n \log n)$，容易一眼发现思路。这道题应该按照天数 $a_i$ 排序，然后考虑当前的零件数 $(a_i - a_{i-1}) \times k$ 是否大于应当交付零件数 $b_i$，如果大于，就用当前的零件数减去交付零件数，否则直接跳出循环（在这一次已经无法交付，意味着没有继续生产零件的必要了）。

## 如何保证正确性
当前的零件数一定为 $(a_i - a_{i-1}) \times k$，因为要计算的是上一个日期 $a_{i-1}$ 到这个日期 $a_i$ 所生产的零件，所以要乘以每天生产的零件数 $k$，又因为排序保证了序列一定具有单调性，所以得证。
## Code
```
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(false)
#define C std::cin.tie(0)
#define Co std::cout.tie(0)

typedef long long LL;
const int N = 2e5 + 5;
LL T;
struct node {
	LL a, b;
	friend bool operator <(node & x, node & y) {
		return x.a < y.a;
	}
}a[N];
int main() {
	IOS; C; Co;
	std::cin >> T;
	bool flag = 0;
	while (T--) {
		LL n, k;
		std::cin >> n >> k;
		for (LL i = 1; i <= n; ++i) std::cin >> a[i].a >> a[i].b;
		std::sort(a + 1, a + n + 1);
		LL P = 0;
		for (LL i = 1; i <= n; ++i) {
			LL R = a[i].b;
			P += (a[i].a - a[i - 1].a) * k;
			if (P >= R) {
				P -= R;
				flag = 1;
			}
			else {
				flag = 0;
				break;
			}
		}
		if (flag) puts("Yes");
		else puts("No");
	}
	return 0;
}
```



---

## 作者：yanxiashi (赞：0)

简单题，建议评红。

[原题链接](https://www.luogu.com.cn/problem/P9556)

# 题意

某工厂在第 $1$ 天开工之前收到了 $n$ 笔订单，第 $i$ 笔订单可以用两个整数 $a_i$ 和 $b_i$ 描述，表示工厂需要在第 $a_i$ 天结束时交付 $b_i$ 件货物。

已知工厂每天能生产 $k$ 件货物，且第 $1$ 天开工之前没有任何存货，问该工厂能否完成所有订单。

# 思路

1. 开一个结构体数组，存下订单信息；
2. 根据开工天数大小排序；
3. 检查利用整数 $last$ 存储囤积， $now$ 存储最晚订单，推出任意时刻是否合法；
4. 注意开 `long long`。

时间复杂度瓶颈在排序，为 $O(n\log n)$。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 102;
struct node{
  int A,B;
}a[maxn];
int Read();
int T,n,k,last,now,flag;
bool cmp(node x,node y){
  return x.A < y.A;
}
signed main(){
  T = Read();
  while(T--){
  	last = 0; now = 0; flag = 1;
  	n = Read(); k = Read();
  	for(int i = 1;i <= n;++i)
  	  a[i].A = Read(),a[i].B = Read();
	sort(a + 1,a + n + 1,cmp);
	for(int i = 1;i <= n;++i){
  	  if(flag) last = (last + (a[i].A - now) * k - a[i].B);
	  if(last < 0) flag = 0;
	  now = a[i].A;
	}
	if(flag) cout << "Yes" << endl;
	else cout << "No" << endl;
  }
  return 0;
}
int Read(){
  char c = getchar();
  int x = 0,f = 1;
  while(c < '0' || c > '9'){
    if(c == '-') f = -1;
    c = getchar();
  }
  while(c >= '0' && c <= '9'){
    x = x * 10 + c - '0';
    c = getchar();
  }
  return x * f;
}
```





---

## 作者：_5t0_0r2_ (赞：0)

标准模拟题。

读入所有订单，先按照日期排序，建立一个 $cnt$ 用来存放此时的存货（初始设为 $0$），然后遍历订单：

1、生产阶段：当遍历到第 $i$ 个订单时，工厂有 $a_i - a_{i - 1}$ 天的时间生产，可以生产 $k(a_i - a_{i - 1})$ 的货物，将 $cnt$ 加上这个数。

2、交货阶段：判断 $cnt$ 是否大于 $b_i$，如果大于，将 $cnt$ 减去 $b_i$，否则，表示不能完成，立刻退出遍历。

注意，极端情况下会出现 $k$ 很大 $b$ 很小的情况，可能会爆 int。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 109;
int t,n,k;
int cnt;
struct Data{
	int a,b;
} x[N];
bool cmp(Data d1,Data d2){
	return d1.a < d2.a;
}
signed main(){
	scanf("%lld", &t);
	for(int i = 1;i <= t;i++){
		scanf("%lld%lld", &n, &k);
		cnt = 0;
		bool ans = true;
		for(int j = 1;j <= n;j++)
			scanf("%lld%lld", &x[j].a, &x[j].b);
		sort(x + 1,x + n + 1,cmp);
		for(int j = 1;j <= n;j++){
			cnt += k * (x[j].a - x[j - 1].a);
			if(cnt < x[j].b){
				ans = false;
				break;
			}
			cnt -= x[j].b;
		}
		puts(ans ? "Yes" : "No");
	}
}
```


---

## 作者：xiaoyang111 (赞：0)

# P9556 [SDCPC2023] A-Orders 题解

## 前言

[题目传送门。](https://www.luogu.com.cn/problem/P9556)

[可能更好的阅读体验。](https://www.luogu.com.cn/blog/xiaoyang111/solution-p9556)

## 讲解

### 思路

此题涉及到的算法有排序和模拟，具体解题步骤见下。

1. 输入各种数据。

2. 进行排序，排序是按照交货时间从小到大排序的。

3. 从前往后顺序遍历，算出交货那一天有多少存货。如果存货不够，按照题目要求输出相应文本；如果存货够，减去要交多少货。

4. 如果所有过程都模拟完成，中途没有任何存货不够的情况，按照题目要求输出相应文本。

时间复杂度较为小，可以通过本题。

还有需要注意的是，此题数据要开 long long，因为在计算存货的时候 $k$ 可能会很大。

### 代码

这是我的代码，可能风格有些不好看，请见谅。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
signed main(){
	int T;
	cin >> T;
	while (T--){
		int n,k;
		cin >> n >> k;
		vector<pair<int,int>> a;
		for (int i=0;i<n;++i){
			int t1,t2;
			cin >> t1 >> t2;
			a.emplace_back(t1,t2);
		}
		sort(a.begin(),a.end(),[](const pair<int,int> &a,const pair<int,int> &b){
			return a.first<b.first;
		});
		int up=0,time=0;//上一个订单剩余的数量和上一个订单交付的时间 
		bool flag=true;
		for (const auto &item : a){
			up+=k*(item.first-time);
			if (up<item.second){
				flag=false;
				break;
			}
			up-=item.second;
			time=item.first;
		}
		if (flag){
			cout<<"Yes\n";
		}else{
			cout<<"No\n";
		}
	}
	return 0;
} 
```

---

## 作者：Moon_Wind (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9556)



------------

**算法分析**：

因为工厂需要在 $a_i$ 天之内完成第 $i$ 个订单，所以我们应该将要求交付的日期从小到大排序一下，再根据题意进行模拟。当工厂中剩下的货物小于 $0$ 时，则退出循环，说明无法完成所有订单。如果库存一直非负，则可以完成所有订单。

**代码部分**：



------------
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,sum=0,k;
struct node{
	int x,y;
}a[1000011];//定义结构体。
bool cmp(node a,node b){
	return a.x<b.x;
}//结构体排序。
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	int t;
	cin>>t;
	while(t--){ 
		sum=0;
		int f=-1;
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			sum+=k*(a[i].x-a[i-1].x);
			if(sum<a[i].y){
				cout<<"No"<<endl;
				f=1
				break;
			};//库存为负数，无法完成所有订单。
			else sum-=a[i].y;
		}
		if(f==-1) 
        		cout<<"Yes"<<endl;
	} 
	return 0;
}
```


------------




---

## 作者：_ImposterX_ (赞：0)

### 题目描述

[Luogu](https://www.luogu.com.cn/problem/P9556)

### 思路讲解

很简单的一个模拟题，建议评红。

我们只需要对每个需要交货的日期按时间顺序进行排序。记录一个 $sum$ 表示当前的存货，然后枚举每个日期。对于第 $i$ 个日期，令 $sum$ 增加第 $i$ 次交货的时间和 $i-1$ 次交货的时间之差 $\times k$。看看当前的 $sum$ 是否满足需求即可。

### 代码环节

```cpp
#include <bits/stdc++.h>
#define int long long
#define gt getchar
#define pt putchar

using namespace std;

const int MAXN=105;

signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		pair<int,int> a[MAXN];
		int n,k;
		cin>>n>>k;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].first>>a[i].second;
        //这里方便就用pair了
		}
		sort(a+1,a+n+1);//按时间排序
		int sum=0;
		bool f=true;
		for(int i=1;i<=n;i++)
		{
			sum+=k*(a[i].first-a[i-1].first);
			if(sum<a[i].second)
			{
          `//不符合要求
				f=false;
				break;
			}
			else
			{
           //符合要求
				sum-=a[i].second;
			}
		}
		if(f)
		{
			cout<<"Yes\n";
		}
		else
		{
			cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：InversionShadow (赞：0)

发现我的做法和官方题解好像啊。

首先按天数 $a_i$ 为第一关键字**从小到大**排序。然后模拟。设 `last` 为昨天剩下的，那么今天就是 `last + k`，我们可以算出在 $a_{i - 1} \sim a_i$ 中可以生产的零件个数，即 `now = last + (a[i].l - a[i - 1].l) * k`，就是剩下的加上每天生产的，然后与第 $i$ 天的期望比较即可。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int MAXN = 1e5 + 100;

struct Node{
  int l, r;
} a[MAXN];

int t, n, k;

bool cmp(Node i, Node j) {
  if (i.l == j.l) {
    return i.r < j.r;
  }
  return i.l < j.l;
}

signed main() {
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i].l >> a[i].r;
    }
    sort(a + 1, a + n + 1, cmp);
    int last = 0, now = 0, p = 1;
    bool flag = 1;
    for (int i = 1; i <= n; i++) {
      now = last + k * (a[i].l - a[i - 1].l);
      if (now < a[i].r) {
        cout << "No\n";
        flag = 0;
        break;
      } else {
        now -= a[i].r;
      }
      last = now;
    }
    if (flag) {
      cout << "Yes\n";
    }
  }
  return 0;
}
```

---

## 作者：CheZiHe929 (赞：0)

## 原题链接

[P9556 [SDCPC2023] A-Orders](https://www.luogu.com.cn/problem/P9556)

## 简要思路

用结构体存储下每笔订单的交货时间以及交货数量，以时间为第一关键字、数量为第二关键字进行排序。

维护 $num$ 表示当前的交货数量，用每笔订单需交货的时间 $a$ 乘上每天生产的货物数 $k$，再减去 $num$，最终将得到的结果与 $b$ 进行比较即可。注意每次更新 $num$ 的值。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

struct node{
	int a;//时间
	int b;//数量
}c[105];

int t;

bool cmp(node x,node y){
	if(x.a!=y.a)return x.a<y.a;//时间为第一关键字
	else return x.b<y.b;
}

signed main(){
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		
		for(int i=1;i<=n;i++)
			cin>>c[i].a>>c[i].b;

		sort(c+1,c+n+1,cmp);
		
		int num=0;//当前需交货的数量
		bool f=1;
		for(int i=1;i<=n;i++){
			int x=c[i].a*k-num;
			if(x<c[i].b){//看能否交上货
				cout<<"No"<<endl;
				f=0;
				break;
			}
			num+=c[i].b;//维护 num 的值
		}

		if(f)cout<<"Yes"<<endl;
	}
	return 0;
}
```

## AC 记录

[This](https://www.luogu.com.cn/record/121664360).

**THE END**

**THANK YOU**

---

## 作者：__Octhyccc__ (赞：0)

首先，我们要知道，一定是时间紧的越重要，所以需要排序，至于工作量多少可以不作为排序标准。

然后按照题目模拟，令 $h$ 为仓库累积货物（初始为 $0$），那么第 $a_i$ 天货物就可以这么表示：

$$h+(a_i-a_{i-1})\times k$$

然后减去对应的 $b_i$，判断一下是否够用就行了。

还有，由于每个 $k\le 10^9$，在最坏情况下 $h$ 最大为 $10^9\times 100$，也就是 $10^{11}$，int 已经无能为力，**所以找 long long 去，不开 long long 见祖宗。**

AC 代码：

```cpp
#include<cstdio>
#include<algorithm>
#define int long long//改动后的精华。
using namespace std;
struct S{
	int a,b;
}l[101];
bool cmp(S x,S y){
	if(x.a!=y.a)return x.a<y.a;
	else return x.b<y.b;
}
long long T,n,k;
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%lld%lld",&l[i].a,&l[i].b);
		}
		sort(l+1,l+n+1,cmp);
		bool ok=1;long long h=0;//记住开 long long！
		for(int i=1;i<=n;i++){
			h+=((l[i].a-l[i-1].a)*k);
			h-=l[i].b;//计算剩余货物。
			if(h<0){
				ok=0;break;
			}
		}
		ok?puts("Yes"):puts("No");
		for(int i=1;i<=n;i++){
			l[i].a=0,l[i].b=0;//养成清空的好习惯，否则可能会 WA。
		}
	}
	return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

直接上暴力。    
首先把每个任务按照结束时间从早到晚排序。     
对于每一个任务，计算从上一个任务结束到这一个任务截止时生产了多少货物，并加上上一个任务结束时遗留的货物。此时如果可以把货物交付，则把当前货物数量减去需要交付的货物数量，否则就不能完成所有订单，输出 $\texttt{No}$。最后如果全部订单都完成了，就输出 $\texttt{Yes}$。    
如果使用了全局变量统计，记得处理完一组数据之后要清空，俗话说：多测不清空，爆零两行泪。（当然了还要记得换行！）
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long t,n,k;struct sss{long long a,b;}s[105];
bool cmp(sss a,sss b){return a.a<b.a;}
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld",&n,&k);
        for(int i=1;i<=n;i++) scanf("%lld%lld",&s[i].a,&s[i].b);
        sort(s+1,s+n+1,cmp);
        long long sum=0;int i=1;
        //sum表示当前剩余的货物，i表示当前处理到第几个订单。
        for(;i<=n;i++)
        {
            sum+=(s[i].a-s[i-1].a)*k;
            if(sum>=s[i].b) sum-=s[i].b;
            else {printf("No\n");break;}
        }
        if(i>n) printf("Yes\n");
    }
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

如果 $k$ 和每个订单都是固定的，那所有的生产和剩余的货物都是固定的，那直接模拟就好。

可以提前对订单按照天数排序，对于排序后第 $i$ 个订单，可以提前累加前面所有订单所需的货物，再与天数乘以 $k$ 判断能否完成。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{long long a,b;}t[105];
inline bool cmp(node x,node y){return x.a<y.a;}
long long T,n,k,sum,flag;
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		for(long long i=1;i<=n;++i) scanf("%lld%lld",&t[i].a,&t[i].b);
		sort(t+1,t+n+1,cmp),flag=sum=0;//排序+赋初值
		for(long long i=1;i<=n;++i)
		{
			sum+=t[i].b;//累加前面订单的货物总和
			if(t[i].a*k<sum){printf("No\n"),flag=1;break;}//直接判断
		}
		if(!flag) printf("Yes\n");
	}
}
```

---

## 作者：SakurajiamaMai (赞：0)

## 思路:
利用一个结构体存储天数和货物数量，由于时间是一天一天进行的，我们需要先对天数排序，然后遍历数组，利用天数之差求出货物数量是否满足要求即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=1e9+7;
string s;
int n,t,res,num,ans,m,k;
bool vis[N];
struct node
{
    int a,b;
    bool operator<(const node&w)const
    {
        return a<w.a;
    }
}p[N];
void solve()
{
    cin>>n>>m;
    res=0;
    for(int i=1;i<=n;i++) cin>>p[i].a>>p[i].b;
    sort(p+1,p+1+n);
    for(int i=1;i<=n;i++){
        res+=(p[i].a-p[i-1].a)*m;
        if(res<p[i].b){
            cout<<"No"<<endl;
            return;
        }
        res-=p[i].b;
    }
    cout<<"Yes"<<endl;
}
signed main()
{
    std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
```


---

## 作者：unknown_risk (赞：0)

本题思路：采用贪心思想，根据交付时间排序，然后循环模拟，统计到 $a_{i}$ 天要交付货物总件数与前 $a_{i}$ 天生产货物总件数进行比较。

Tip：十年 oi 一场空，不开 long long 见祖宗。
### My code
```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=110;
int T,n,k;
bool flag;
struct node
{
	int a,b;
}e[N];
bool cmp(node s1,node s2)
{
	if(s1.a!=s2.a)return s1.a<s2.a;
	else return s1.b<s2.b;
}
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)cin>>e[i].a>>e[i].b;
		sort(e+1,e+1+n,cmp);
		int ans=0;
		flag=1;
		for(int i=1;i<=n;i++)
		{
			ans+=e[i].b;
			if(1ll*e[i].a*k<ans)
			{
				puts("No");
				flag=0;
				break;
			}
		}
		if(flag)puts("Yes");
	}
	return 0;
}
```


---

