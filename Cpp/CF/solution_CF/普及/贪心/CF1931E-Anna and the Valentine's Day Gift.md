# Anna and the Valentine's Day Gift

## 题目描述

Sasha gave Anna a list $ a $ of $ n $ integers for Valentine's Day. Anna doesn't need this list, so she suggests destroying it by playing a game.

Players take turns. Sasha is a gentleman, so he gives Anna the right to make the first move.

- On her turn, Anna must choose an element $ a_i $ from the list and reverse the sequence of its digits. For example, if Anna chose the element with a value of $ 42 $ , it would become $ 24 $ ; if Anna chose the element with a value of $ 1580 $ , it would become $ 851 $ . Note that leading zeros are removed. After such a turn, the number of elements in the list does not change.
- On his turn, Sasha must extract two elements $ a_i $ and $ a_j $ ( $ i \ne j $ ) from the list, concatenate them in any order and insert the result back into the list. For example, if Sasha chose the elements equal to $ 2007 $ and $ 19 $ , he would remove these two elements from the list and add the integer $ 200719 $ or $ 192007 $ . After such a turn, the number of elements in the list decreases by $ 1 $ .

Players can't skip turns. The game ends when Sasha can't make a move, i.e. after Anna's move there is exactly one number left in the list. If this integer is not less than $ 10^m $ (i.e., $ \ge 10^m $ ), Sasha wins. Otherwise, Anna wins.

It can be shown that the game will always end. Determine who will win if both players play optimally.

## 说明/提示

Consider the first test case.

Anna can reverse the integer $ 2 $ , then Sasha can concatenate the integers $ 2 $ and $ 14 $ , obtaining the integer $ 214 $ , which is greater than $ 10^2 = 100 $ . If Anna had reversed the integer $ 14 $ , Sasha would have concatenated the integers $ 41 $ and $ 2 $ , obtaining the integer $ 412 $ , which is greater than $ 10^2 = 100 $ . Anna has no other possible moves, so she loses.

## 样例 #1

### 输入

```
9
2 2
14 2
3 5
9 56 1
4 10
1 2007 800 1580
4 5
5000 123 30 4
10 10
6 4 6 2 3 1 10 9 10 7
1 1
6
1 1
10
8 9
1 2 9 10 10 2 10 2
4 5
10 10 10 10```

### 输出

```
Sasha
Anna
Anna
Sasha
Sasha
Anna
Anna
Anna
Sasha```

# 题解

## 作者：信息向阳花木 (赞：5)

Sasha 想让数连起来尽量长，Anna 想让数连起来尽量短。答案只和数的长度有关，和具体数字无关。

Anna 可以翻转数字，去掉前导零。所以 Anna 每次可以选择末尾 $0$ 的个数最多的数反转，以去掉最多的 $0$，数长度变短。Sasha 无法改变数的长度，所以他每次也会选择当前末尾 $0$ 最多的数，和其他数连，防止 Anna 删。

所以我们一开始算一下所有数连其来的位数 $cnt$，再按末尾 $0$ 的个数 $l_i$ 降序排序。拿总位数 $cnt$ 减去 Anna 最多能删的位数 $\sum_{i=1}^{n}l_i$（$i$ 为奇数）就是最后答案的位数，和 $m + 1$ 比较一下就行。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int N = 200010;

int t, n, m;
int a[N], l0[N];

bool cmp(int a, int b)
{
	return a >b;
}

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		memset(l0, 0, sizeof l0);
		int cnt = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i ++ )
		{
			scanf("%d", &a[i]);
			int x = a[i]; bool flag = 1;
			while (x)
			{
				cnt ++;
				if(x % 10 == 0 && flag == 1) l0[i] ++;
				else flag = 0;
				x /= 10;
			}
		}
		sort(l0 + 1, l0 + n + 1, cmp); 
		for (int i = 1; i <= n; i += 2)
		{
			cnt -= l0[i];
		}
		if(cnt >= m + 1) puts("Sasha");
		else puts("Anna");
	}
	return 0;
}
```

---

## 作者：SXqwq (赞：3)

### Description

给定一个长度为 $n$ 的数组 $a$，Anna 每次可以选择一个数字，去掉他的后导零。Sasha 每次可以选择两个数字，并把他们拼接。若最后剩下的一个数字数位 $>m$ 则 Anna 胜利。否则 Sasha 胜利。

### Analysis

有趣的贪心题。

Anna 每次想要尽可能多的去掉一个数的后导零。Sasha 想尽可能的“保护”后导零。因为 Sasha 想要尽可能的使剩下的数位多。而 Sasha 保护一个数后导零的方式是将另外一个数拼到她前面。这样 Anna 只能去掉这个被拼到前面的数的后导零。

将题目分析到这里，不难发现，Anna 每次想去掉尽可能多的后导零，Sasha 想尽可能的保护多的后导零。所以他们两个的最优策略都是每次操作当前后导零最多的数。

所以，对于每个数 $a_i$，令 $b_i$ 为 $a_i$ 的后导零数量。将 $b$ 数组降序排列，模拟即可。

设 $tot$ 为所有数位和，$t$ 为 Anna 去掉的后导零数量。若 $tot-t \geq m$ 则 Sasha 获胜。否则 Anna 获胜。

具体细节见代码。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 10000010;
int T;
int n,m;
int a[N];
int tot = 0;
int get_zero(int x)
{
	string str = to_string(x);
	int cnt = 0;
	for(int i=str.size()-1;i>=0;i--)
	{
		if(str[i] != '0') break;
		cnt ++;
	}
	return cnt;
}
int get_len(int x)
{
	int cnt = 0;
	while(x)
	{
		x/=10;
		cnt++;
	}
	return cnt;
}
bool cmp(int a,int b) 
{
	return a > b;
}
void solve()
{
	cin>>n>>m;
	tot = 0;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		a[i] = get_zero(x);
		tot += get_len(x);
	}
	sort(a+1,a+n+1,cmp);
	int take = tot;
	for(int i=1;i<=n;i+=2)
	{
		take -= a[i];
	}
	if(take > m) cout<<"Sasha"<<endl;
	else cout<<"Anna"<<endl;
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{	
		solve();
	}
}
```

---

## 作者：jiangjiangQwQ (赞：1)

### 思路
贪心就对了。第一个人显然是将一个数的位数变少，第二个人的操作为拼接两个数，那么拼接之前的前面那个数末尾有 $0$ 的话，那么第一个人就不能去掉这些 $0$，感性理解为她的操作是起“保护作用”的。那么两人都以最优方式操作，第一个人先手，肯定是将目前末尾含 $0$ 的个数最多的数翻转，第二个人则是保护目前末尾含 $0$ 的个数最多的数，即拼接。
### 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=2e5+4;
int T,n,a[N],b[N];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--) {
		int m,s=0;
		cin>>n>>m;
//        cout<<"B= ";
		for(int i=1; i<=n; i++) {
			cin>>a[i];
			b[i]=0;
			while(a[i]%10==0) b[i]++,s++,a[i]/=10;
			//b[i]为a[i]末尾0的个数
			while(a[i]) {
				s++;
				a[i]/=10;
			}
//			cout<<b[i]<<' ';
		}
//		cout<<'\n';
//		cout<<s<<'\n';
		sort(b+1,b+n+1,greater<int>());
		for(int i=1; i<=n; i+=2) s-=b[i]; //第一个人去掉目前末尾最多0的那个数
		//s是最后剩下的那个数的位数
		if(s<=m) cout<<"Anna\n";
		else cout<<"Sasha\n";
	}
	return 0;
}
```

---

## 作者：No_Rest (赞：1)

## 思路

第一道 CF 赛时做出的博弈论题。

容易想到，如果所有的数都不是 $10$ 的倍数，那么无论他们如何操作，最后得到的数的位数都不会变。

但是如果有的数是 $10$ 的倍数，那么 Anna 可以通过颠倒其数字顺序来把那个数后面的 $0$ 全部消掉。

同样地，Sasha 可以通过将 $10$ 的倍数的数放在前面，与另一个数连接来阻止 Anna 消掉 $0$。

所以 Anna 可以先将后面 $0$ 最多的数颠倒数字，消掉 $0$，Sasha 可以将后面 $0$ 第二多的数通过拼接阻止 Anna 消掉，Anna 可以再将后面 $0$ 第三多的数颠倒数字，消掉 $0$，如此反复。

那么我们可以得到，如果把所有是 $10$ 的倍数的数后面的 $0$ 的个数存到一个数组 $b$ 里并将其排序，Anna 能消掉的 $0$ 的个数即为 $\displaystyle \sum_{i=1}^{\lceil \frac{tot}{2} \rceil} b_{2i - 1}$，其中 $tot$ 是数组 $b$ 的大小。

这样我们就可以求出最后得到的数的位数了，也就能知道它与 $10^m$ 的大小关系（如果它的位数 $\ge m+1$，那么它就 $\ge 10^m$，否则就 $< 10^m$）。

## 代码

```cpp
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
const ll maxn = 2e5 + 5;
const ll p10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};//预处理，但没什么用
ll read(){
	char ch;
	ll f = 0, r = 0;
	ch = getchar();
	while(ch > '9' || ch < '0') f |= ch == '-', ch = getchar();
	while(ch <= '9' && ch >= '0') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return f ? -r : r;
}
ll t = read(), n, m, a[maxn], x, b[maxn], sum, sumsiz, tot;//sum 为 Anna 能消掉的 0 的个数，sumsiz 是所有数的位数和，tot 是数组 b 的大小
void solve(){
	n = read(), m = read(), tot = sum = sumsiz = 0;
	for(ll i = 1; i <= n; ++i){
		a[i] = read(), x = 0;
		sumsiz += to_string(a[i]).size();//加上 a[i] 的位数
		for(ll j = 1; j <= 9; ++j)//对时间复杂度要求不高，可以直接暴力求（可以二分）
			if(a[i] % p10[j]) break;
			else x++;
		if(x) b[++tot] = x;//注意如果不是 10 的倍数的话不能加入 b 数组
	}
	sort(b + 1, b + tot + 1, greater <ll> ());//注意要从大到小排序
	for(ll i = 1; i <= tot; i += 2) sum += b[i];//计算 Anna 能消掉的 0 的个数
	sumsiz - sum < (m + 1) ? puts("Anna") : puts("Sasha");//注意 10 的 m 次方是 m + 1 位
}
int main(){	
	for(; t; --t) solve(); 
    return 0;
}
```

---

## 作者：AlicX (赞：0)

## Solution 

考虑 Anna 的最有策略应该是将末尾 $0$ 最多的数翻转，而 Sarah 的最有策略则是将这些数保护起来，但为了方便可以先不用连接，最后一起连接更加方便。

此时则把最小的与最大的连接，次小的与次大的连接，直到元素个数为 $1$。时间复杂度为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
il int read(){ 
	int x=0,f=1; char ch=getchar(); 
	while(ch<'0'||ch>'9'){ if(ch=='-') f=-1; ch=getchar(); } 
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar(); 
	return x*f; 
} 
const int N=2e5+10; 
int n,m; 
struct Node{
    int x,y; 
    int k,w; 
}a[N]; int b[N],c[N]; 
il bool cmp(Node a,Node b){ 
    return a.y>b.y; 
} 
il bool Cmp(Node a,Node b){ 
    return a.k>b.k; 
} 
il void solve(){ 
    cin>>n>>m,m++; int cnt=0; 
    for(int i=1;i<=n;i++){
        cin>>a[i].x,a[i].y=0,a[i].k=0,a[i].w=0; 
        int x=a[i].x; bool flg=1;  
        while(x){
            if(x%10==0&&flg) a[i].y++; 
            else flg=0; x/=10; a[i].k++; 
        } a[i].w=a[i].k-a[i].y; 
    } sort(a+1,a+n+1,cmp); 
    for(int i=1;i<=n;i++){
        if(!a[i].y){ 
            for(int j=i;j<=n;j++) b[++cnt]=a[j].k; 
            break; 
        } if(i&1) b[++cnt]=a[i].w; else b[++cnt]=a[i].k; 
    } //for(int i=1;i<=cnt;i++) cout<<b[i]<<" "; cout<<endl; 
    while(cnt>1){
        int l=1,r=cnt; 
        sort(b+1,b+cnt+1);
        vector<int> vec; 
        while(l<=r){
            int w=b[l]+b[r]; 
            if(l==r) w/=2; 
            l++,r--; vec.push_back(w); 
        } cnt=0; for(auto u:vec) b[++cnt]=u; 
    } if(b[1]<m) puts("Anna"); else puts("Sasha"); 
} 
signed main(){ 
    int T=read(); 
    while(T--) solve(); 
    return 0; 
} 
```


---

## 作者：mywzj_mo (赞：0)

### 前言
[【洛谷】题目传送门](https://www.luogu.com.cn/problem/CF1931E)。

[【官网】题目传送门](https://codeforces.com/problemset/problem/1931/E)。

### 题目大意
有一个数组 $a$ 和两个人 Anna，Sasha。每一步，Anna 都可以把数组 $a$ 中的一个数翻转并去除翻转后的数前导零（$42 \Rightarrow 24$，$1580 \Rightarrow 851$）；而 Sasha 可以将两个数拼接在一起（类似字符串操作，$19+2007 \Rightarrow 192007$ 或 $200719$）。Anna 要将数字最小化，Sasha 要将数字最大化，在双方均在最佳策略下行动时，若最后的数字 $\ge 10^m$，则 Sasha 获胜，反之 Anna 获胜，输出胜者名字。

### 思路
使最后的数 $\ge 10^m$ 相当于使最后的数的位数要大于 $m$。

分析：仔细发现，其实只有 Anna 能把数字的位数变少（如上文例子中的 $1580 \Rightarrow 851$，四位数变成了三位数），所以 Anna 要把数字最小化，就要选择尾数 0 最多的数进行翻转，使数的位数变少。而 Sasha 的操作不会改变数的位数，但可以消除一个数中的尾数 0。当 Sasha 要把数字最大化时，他应该选择尾数 0 最多的数与另外一个数拼接，这样即使 Anna 对其翻转，也只能减少较少的数字位数。

贪心思路：每个数依据尾数 0 的个数进行排序，由于是 Anna 的先手，所以能对尾数 0 数量第 $1,3,5,\cdots$ 多的数进行翻转（可以翻转尾数 0 数量第奇数多的数）以减少最终数字的位数。而 Sasha 可以拼接尾数第 $2,4,6,\cdots$ 多的数（可以拼接尾数 0 数量第偶数多的数），拼接的顺序不重要，因为拼接只能消除一个数的尾数 0 数量，但不能消除另外一个数的尾数 0 个数。

做法：可以先在读入时处理各个数尾数 0 的个数并求出所有数的位数总和。后面对尾数 0 的个数进行一次排序，减掉第奇数多的尾数 0 个数量，即可求到最后数的尾数，判断这个数是否大于 $m$ 即可。

时间复杂度：$O(n\log{n})$。

### 代码
温馨提示：诚信做人，不要抄袭！
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
int sum;
struct node{
	int w,w0;
}a[200005];
bool cmp(node a,node b){
	return a.w0>b.w0;
}
int cnt;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;
		sum=cnt=0;
		for(int i=1;i<=n;i++){
			string t;
			cin>>t;
			a[i].w=t.size();
			int cnta=0,j=t.size()-1;
			while(j>=0&&t[j--]=='0'){
				cnta++;
			}
			a[i].w0=cnta;
			sum+=t.size();
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i+=2){
			sum-=a[i].w0;
		}
		//cout<<sum<<" "<<cnt<<"!\n";
		if(sum>m)cout<<"Sasha\n";
		else cout<<"Anna\n";
	}
}
```


---

## 作者：ty_xyz (赞：0)

注意到输赢的判定只和 $10^m$ 相关，因此我们可以忽略数码，只考虑位数。

* 对于 Anna，她最优的操作应该是一次消掉尽可能多的位，因此她会翻转当前后继的 $0$ 最多的数。

* 对于 Sasha，他最优的操作是保留尽可能多的位，因此他会将当前后继的 $0$ 最多的数接到任意一个数上（将这个后继的 $0$ 最多的数放在前，另一个数放在后）。

那么 $\mathcal{O}(n\log_2n)$ 模拟两人的操作即可，总时间复杂度 $\mathcal{O}(\sum(n\log_2n))$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct num
{
    int len,l0;
    bool operator<(num c)const{return l0>c.l0;}
}b[200001];
int t,n,m,a[200001],sum;
void turn(int x)
{
    bool flag=1;
    b[x].len=b[x].l0=0;
    while(a[x])
    {
        if(a[x]%10==0&&flag)++b[x].l0;
        else flag=0;
        ++b[x].len;
        a[x]/=10;
    }
}
signed main()
{
    scanf("%d",&t);
    while(t--)
    {
        sum=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            turn(i);
        }
        sort(b+1,b+n+1);
        for(int i=1;i<=n;i++)
        {
            if(i&1)b[i].len-=b[i].l0;
            sum+=b[i].len;
        }
        sum>m?puts("Sasha"):puts("Anna");
    }
    return 0;
}
```

---

## 作者：_smart_stupid_ (赞：0)

## [题目](https://codeforces.com/contest/1931/problem/E)

我们发现，对于每一个末尾有 $p$ 个 $0$ 的数，翻转会让这个数少 $p$ 位，对于安娜，翻转一个数会让最终的数长度减少这个数后缀 $0$ 的个数，而对于萨沙，合并一个数会让这个数后缀 $0$ 无法消除。

所以安娜尽量选择后缀 $0$ 更多的翻转，萨沙尽量选择后缀 $0$ 更多的数消除。统计每个数后缀 $0$ 的个数，然后从大到小排序，因为安娜是先手，所以她会翻转第 $1$ 大，第 $3$ 大，第 $5$ 大，最后统计答案位数，判断输出，完结撒花。

## AC Code：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <list>
#include <set>
#include <map>
using namespace std;
int t;
int n, m;
struct node{
	string a; int cnt;
};
node a[200100];
bool cmp(node a, node b) {
	return a.cnt > b.cnt;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		int sum = 0;
		for (int i = 1; i <= n; i ++) cin >> a[i].a;
		for (int i = 1; i <= n; i ++) {
			for (int j = a[i].a.size() - 1; j >= 0; j --) {
				if (a[i].a[j] != '0') {
					a[i].cnt = a[i].a.size() - j - 1;
					break;
				}
			}
			sum += a[i].a.size();
		}
		sort(a + 1, a + n + 1, cmp);
		for (int i = 1; i <= n; i += 2) {
			sum -= a[i].cnt;
		}
//		for (int i = 1; i <= n; i ++) {
//			cout << a[i].cnt << ' ';
//		}
//		cout << '\n';
		if (sum > m) {
			cout << "Sasha";
		}
		else {
			cout << "Anna";
		}
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：MorLeaves (赞：0)

## **题意：**

  有一个长度为 $n$ 的数列 $a_1$~$ a_n$ ， $\tt{Sasha}$ 与 $\tt{Anna}$ 在玩一个游戏。
  
-  $\tt{Anna}$ 先进行操作，她可以任意选择一个 $a_i$ ，将 $a_i$ 进行只有正数的[数字反转](https://www.luogu.com.cn/problem/P1307)（即反转后要去掉前导零）。例如 114514 这个数，反转后变为 415411 ； 1919810 反转后变为 189191 。

-  $\tt{Sasha}$ 后进行操作，他可以任意选择一对 $a_i$ 与 $a_j$ ，将这两个数“拼”在一起。例如 877 与 691 两个数，操作后可“拼”成 [877691](https://www.luogu.com.cn/user/877691) 或 691877 ，显然进行此操作后所有 $a_i$ 的个数将会减少一个。

双方先后轮流进行操作，直到剩下一个数时，若这个数不小于（$\ge$） $10^m$ ，则 $\tt{Sasha}$ 获胜；反之 $\tt{Anna}$ 获胜，输出获胜者的名字。

## **思路：**

由题意可以发现，其实 $\tt{Anna}$ 就是要让最后的数较小， $\tt{Sasha}$ 要让最后的数较大。

- 观察 $\tt{Anna}$ 所进行的操作，能发现：如果没有删去前导零，则该数操作后位数不会变；如果删去了，则位数会变小。位数变小对比位数不变，显然是前者更有利于 $\tt{Anna}$ 取胜（能让该数变得更小），并且只有位数变小才能使最终得到的数的位数进行永久性的减小（可能有点抽象），所以 $\tt{Anna}$ 一定会选择当前所有 $a_i$ 中后导零数量最多的那个数进行操作，操作后将会使该数无后导零。

- 观察 $\tt{Sasha}$ 所进行的操作，和 $\tt{Anna}$ 类似，他的任务就是让 $\tt{Anna}$ 不那么顺利的进行操作，也就是他要将一个后导零最多的数的后导零数量减少，其实他每次都可以将该数的后导零减少至 0 。可以发现， $\tt{Anna}$ 每次操作完后，都会留下一个后导零数量为 0 的数，因此 $\tt{Sasha}$ 可以选择后导零数量最多和后导零数量为 0 的这两个数进行操作，将无后导零的这个数放后，最终可以“拼”出一个无后导零的新数。

至此，双方每次的最佳操作都已确定。因为最后只需判断是否 $\ge 10^m$ ，所以只需计算出最终数的位数即可，注意 $10^m$ 有 $(m+1)$ 位数。因为要计算每个数的后导零数量和每个数的位数，所以每个数用 string 类型存储更加方便，记得多测要清空。

## **CODE:**

最后奉上带注释的代码。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
int T,n,m,k[200005];// k数组存储每个数的后导零数量 
string s[200005];//用 string 类型存储每个数 
int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&n,&m);
		int sum=0;//用来统计最终数的位数 
		for(int i=1;i<=n;i++) {
			cin>>s[i];
			sum+=s[i].size();//先加上所有数的总位数 
			for(int j=s[i].size()-1;j>=0;j--) {//计算每个数的后导零数量 
				if (s[i][j]=='0') k[i]++;
				else break;
			}
		}
		sort(k+1,k+n+1);//将后导零数量进行排序 
		for(int i=n;i>=1;i-=2) sum-=k[i];//对应 Anna 的每次操作，在 Anna 每次操作后 sum 减少当前后导零数量
		if (sum>=m+1) printf("Sasha\n");//记得是 m+1  
		else printf("Anna\n");
		fill(k+1,k+n+1,0);//多测清空，等价于for(int i=1;i<=n;i++) k[i]=0;
	}
	return 0;//完美结束撒花！！！ 
}
```


---

## 作者：SamHJD (赞：0)

## Anna and the Valentine's Day Gift

### Description

两个人进行一个游戏，第一个人在序列 $a$ 中选取一个数，将其翻转，并去掉前导 $0$；第二个人选择两个数将其首尾拼接。问最终剩下的那个数是否位数大于 $m$。

### Solution

将序列 $a$ 按照每个数的后缀 $0$ 数量从大到小排序。第一个人的最优策略肯定为选择当前后缀 $0$ 最长的数反转，第二个人的最优策略肯定为选择当前后缀 $0$ 最长的数和任意一个数合并，使当前后缀 $0$ 最长的数不会被反转失去这些 $0$。

计 $w(x)$ 为 $x$ 的位数，$s(x)$ 为 $x$ 的后缀 $0$ 数量。根据最优策略，奇数位的数会失去后缀 $0$，偶数位的数不会。因此答案为 $\sum\limits_{i=1}^{n}w(a_i)-\sum_{i-1}^{n}s(a_i)[i\equiv1\pmod2]$。

### [code](https://codeforces.com/contest/1931/submission/246352458)

---

## 作者：minVan (赞：0)

**题目大意**

Anna 一次操作能将一个数反转，如 $800$ 操作后变为 $008$ 即 $8$；Sasha 一次操作能合并两个数，如 $2007$、$1500$ 操作后变为 $20071500$ 或 $15002007$。Anna 先手。

当只剩下最后一个时，若其位数大于 $m$，则 Sasha 赢，否则 Anna 赢。

**解题思路**

显然，Anna 每次选的数一定是末尾 $0$ 最多的数进行操作，不难想到用优先队列来处理，结构体内设置两个变量 $l,r$，分别表示该数位数和末尾 $0$ 个数，排序则是按先 $r$ 再 $l$ 从小到大排序。

每一回合，Anna 先取出队顶进行操作，即 $(l,r)$ 变为 $(l-r,0)$；Sanna 则取出队顶的两个元素，再把末尾 $0$ 个数小的放后面，即 $(l_1,r_1),(l_2,r_2)$ 变为 $\left(l_1+l_2,\min\{r_1,r_2\}\right)$。

注意最后剩下的一个数 Anna 还可以进行一次操作。


**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
struct node {
  int l, r;
  bool operator < (const node &x) const {
    return r != x.r ? r < x.r : l < x.l;
  }
};
int n, m;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    priority_queue<node> pq;
    cin >> n >> m;
    for(int i = 1, x; i <= n; i++) {
      cin >> x;
      int c1 = 0, c2 = 0;
      bool flag = 0;
      while(x) {
        if(x % 10) { flag = 1; }
        if(!flag) { ++c2; }
        ++c1;
        x /= 10;
      }
      pq.push({c1, c2});
    }
    for(int i = 1; i < n; i++) {
      auto tmp = pq.top();
      pq.pop();
      pq.push({tmp.l - tmp.r, 0});
      auto x = pq.top();
      pq.pop();
      auto y = pq.top();
      pq.pop();
      pq.push({x.l + y.l, min(x.r, y.r)});
    }
    if(pq.top().l - pq.top().r > m) {
      cout << "Sasha\n";
    } else {
      cout << "Anna\n";
    }
  }
  return 0;
}
```

---

## 作者：_Delete_ (赞：0)

## 思路

由题意可得：安娜的最优解是通过反转使总位数更小，萨沙的最优解使通过拼接两个数使更多的位数被保留。

检查每一个数的后置 $0$ 的位数，将每个数非 $0$ 位数处理出来并相加求和，对于后置 $0$ 的位数进行删除最大，总位数加上次大。

尤其注意：当只有 $m$ 位时，总数事实上是不够 $10^m$ 位的，所以对于处理出来的总位数应减一。

## 代码

```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value 
int a[2000005],b[2000005],c[2000005];

//function 
bool cmp(int x,int y){
	return x>y;
}
void solve(){
	int n,m;
	cin>>n>>m;
	for(int i=0;i<=n+3;i++)a[i]=b[i]=c[i]=0;
	for(int i=1;i<=n;i++){
		int x;
		cin>>b[i];
		x=b[i];
		while(x%10==0){
			a[i]++;
			x/=10;
		}
		while(x!=0){
			x/=10;
			c[i]++;
		}
	}
	sort(a+1,a+1+n,cmp);
	int sum=0;
	for(int i=1;i<=n;i++){
		sum+=c[i];
		if(i%2==0)sum+=a[i];
	}
	if(sum>m)cout<<"Sasha"<<endl;
	else cout<<"Anna"<<endl;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
	int T;
	cin>>T;
	while(T--){
		solve();
	}
	
	return 0;
}


```


---

## 作者：MrPython (赞：0)

趣味贪心题。

本题要把数字反转或拼接起来，而且没有对数字的计算操作，则可以从字符串的角度考虑本题。判断游戏最后剩下的数字 $\ge10^m$，就是看游戏最后剩下的字符串的长度 $\left|S\right| >m$。

Anna 应该可以做点什么，让字符串变短。她选择了一个数字反转之后，会丢掉前导零，此时字符串可能会变短一些（例如 $1580$ 的长度是 $4$，反转称 $851$ 后长度仅为 $3$ 了）。

Sasha 会尽可能地阻止 Anna 把字符串变短。具体的，他可以选择把一个数 $T$ 接到 $S$ 的后面组成新串 $ST$，此时 $S$ 末尾的 $0$ 到了 $ST$ 的中间位置，Anna 不再能通过反转 $ST$ 使得 $S$ 末尾的 $0$ 消失了（例如，$50$ 与 $123$ 拼接组成 $50123$，无法再通过反转的方式删掉 $50$ 末尾的 $0$）。

自此，双方的贪心策略就明了了：
- Anna 选择末尾 $0$ 最多的数将其反转，删掉这些末尾的 $0$；
- Sasha 将末尾最 $0$ 最多的数拼到其他任意数的前面，将这些 $0$ 给“保护”起来。

我们统计出字符串的总长度和每个串末尾 $0$ 的个数，从大到小依次枚举。若轮到 Anna，她可以让这些末尾 $0$ 消失，那我们就从总长度中减掉这些 $0$ 的数量即可。
```cpp
#include<bits/extc++.h>
using namespace std;
namespace pbds=__gnu_pbds;
using ui=unsigned int;
using uli=unsigned long long int;
using li=long long int;
using uc=unsigned char;
int main(void){
    ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    size_t T;
    cin>>T;
    while (T--){
        size_t n,m;cin>>n>>m;
        vector<uc> back_zero(n);
        size_t ans=0;
        for (uc& i:back_zero){
            string s;cin>>s;ans+=s.size();
            while (s.back()=='0') ++i,s.pop_back();
        }
        sort(back_zero.begin(),back_zero.end());
        bool turn=1;
        while (!back_zero.empty()){
            if (turn) ans-=back_zero.back();
            back_zero.pop_back();
            turn=!turn;
        }
        cout<<(ans>m?"Sasha\n":"Anna\n");
    }
    return 0;
}
```

---

## 作者：Shadow_T (赞：0)

~~情人节快乐！~~

### 题目大意

Anna 可以把一个数反转，去掉前导零，Sasha 可以把两个数字随机接起来。Anna 先操作，Anna 操作一次，Sasha 操作一次，知道只剩一个数字。如果数字长度大于 $m+1$ 就 Sasha 胜利，否则 Anna 胜利。

### 题目分析

乍一看博弈论，实际简单贪心。很明显，Anna 的反正操作对于有后导零的数才有效果，可以减少数字长度。那么 Alice 足够聪明，那么她会优先选后导零多的数字，这样收益最大。然后计算出 Alice 总共可以翻转多少数量的后导零，拿所有数字总长度减去这个值就是答案。

具体我们可以每次暴力统计后导零，$a_i \leq 10^5$，最多 $5$ 次运算。然后从大到小排序，第 $1,3,5,\dots$ 个 Anna 可以操作，$2,4,6,\dots$ 个 Alice 可以直接找个数合并了，把有 $0$ 的放前面，就不会收到影响。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
string s;
int q[maxn];
void solve()
{
	int n,m;
	cin>>n>>m;
	m++;
	int sum=0;
	for(int i=1;i<=n;i++) 
	{
		cin>>s;
		int len=s.size();
		sum+=len;
		q[i]=0;
		for(int j=len-1;j>=0;j--)
		if(s[j]=='0') q[i]++;
		else break;
	}
	sort(q+1,q+1+n);
	int ans=0;
	int pos=n;
	while(pos>0)
	{
		ans+=q[pos];
		pos-=2;
	}
	int l=sum-ans;
	if(l>=m) cout<<"Sasha\n";
	else cout<<"Anna\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：I_will_AKIOI (赞：0)

### 题目大意

每次操作 Anna 选择一个数并将其翻转，接着 Sasha 选择两个数，将他们拼接起来。若最后剩下的数 $\ge 10^m$，输出 Sasha，反之输出 Anna。

这些数的大小是不重要的，我们只关心他们的长度。因为将他们拼接起来，无论怎样，只要总长度有 $m+1$ 位，就一定  $\ge 10^m$。

接着，Anna 会将一个数翻转，这个数的长度也就减少了他末尾零的个数，总长度也会减小。Sasha 也可以减少他末尾零的个数，但是不会减小总长度。因此记录每个数末尾零的个数，和开始他们数位的总长度。

因此，我们将末尾零的个数从大到小进行排序，按照规则，Anna 肯定会将第一个数翻转，Sasha 则会“保护”第二个数，接着 Anna 又会将第三个数翻转，也就是第奇数个。将总长度减去他们末尾零的个数即可。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[200005],l[200005];
int zero(int x)
{
  int sum=0;
  while(x)
  {
  	if(x%10==0) sum++;
  	else return sum;
  	x/=10;
  }
  return sum;
}//求末尾零的个数
int len(int x)
{
  int sum=0;
  while(x)
  {
  	sum++;
  	x/=10;
  }
  return sum;
}//数位的长度
bool cmp(int x,int y)
{
  return x>y;
}
int main()
{
  ios::sync_with_stdio(0);
  cin>>t;
  while(t--)
  {
  	cin>>n>>m;
  	int cnt=0;
  	for(int i=1;i<=n;i++)
	{
	  cin>>a[i];
	  l[i]=zero(a[i]);
	  cnt+=len(a[i]);
      //记录每个数的末尾零个数和总长度
	}
	sort(l+1,l+n+1,cmp);
	for(int i=1;i<=n;i+=2) cnt-=l[i];//删除第奇数个
	if(cnt>m) cout<<"Sasha\n";
	else cout<<"Anna\n"; 
  }
  return 0;
}
```

---

## 作者：VitrelosTia (赞：0)

对于安娜来说，她的目标显然是让答案数字尽可能小，由于最后胜负的评判标准是位数，所以她无论怎么改变数字的顺序都是无用的，那她的办法就是尽可能地通过消除前导零来使最后的答案减少。而萨沙的方法就是尽可能让安娜能消的前导零尽可能少，这可以通过拿一个末尾有零的数拼到随便一个数前面来达到。

于是我们把所有数按末尾零的个数从大到小排序，两人分别操作当前前导零最多的数。如何判断胜负？一开始先统计出总的位数之和，每次安娜操作的时候减掉操作的数的末尾零个数，最后如果大于 $m$ 萨沙就赢了。

```cpp
int f1(int x) {
	int cnt = 0;
	while (x) { cnt++; x /= 10;}
	return cnt;
}
int f2(int x) {
	int cnt = 0;
	while (x) {
		if (x % 10 != 0) break;
		cnt++; x /= 10;
	}
	return cnt;
}
void solve() {
	cin >> n >> m;
	int sum = 0;
	for (int i = 1; i <= n; i++) cin >> a[i], sum += f1(a[i]);
	sort(a + 1, a + n + 1, [](int x, int y) { return f2(x) > f2(y); });
	for (int i = 1; i <= n; i += 2) sum -= f2(a[i]);
	cout << (sum > m ? "Sasha\n" : "Anna\n");
}
```

---

## 作者：Eason_cyx (赞：0)

简单博弈（？，橙吧。

先考虑 Anna 的最佳操作。

Anna 要使这个数的位数尽可能小，那么能使位数变小的，只有去掉后面的 $0$ 了。由于操作次数有限，那么贪心，Anna 需要从 $0$ 个数最多的数开始操作。但是，由于 Sasha 同样是最佳策略，当 Anna 操作完最多的之后，Sasha 可以将第 $2$ 多的合并，于是 Anna 再操作第 $3$ 多的，以此类推。

那么我们只需先算出所有数的初始总位数和 $0$ 个数，将 $0$ 个数排序后，用总位数减掉 Anna 可以去掉的 $0$ 个数，即为最终位数。

注意：如果最终位数 $\ge m$，就可以认为这个数一定 $\ge10^m$。

时间复杂度 $O(Tn\log n)$，其中 $n\log n$ 为排序复杂度。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[200005],zeronum[200005];
int main() {
	int T; cin >> T;
	while(T--) {
		memset(zeronum,0,sizeof zeronum);
		int n,m; cin >> n >> m;
		int siz = 0;
		for(int i = 1;i <= n;i++) {
			cin >> a[i];
			int cur = a[i];
			while(cur) {
				siz++;
				cur /= 10;
			}
		}
		if(siz < m) {
			cout << "Anna" << endl;
			continue;
		}
		for(int i = 1;i <= n;i++) {
			while(a[i] % 10 == 0) {
				zeronum[i]++;
				a[i] /= 10;
			}
		}
		sort(zeronum+1,zeronum+n+1,greater<int>());
		for(int i = 1;i <= n;i += 2) siz -= zeronum[i];
		// cout << siz;
		if(siz <= m) cout << "Anna" << endl;
		else cout << "Sasha" << endl;
	}
	return 0;
}
```

[AC Record](https://codeforces.com/contest/1931/submission/246252829)

---

