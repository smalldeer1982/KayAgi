# [XJTUPC 2024] Everyone's ALL IN

## 题目描述


女士们，先生们。

早上好，中午好，以及晚上好。

欢迎来到“好得不能再好了！泰拉大师投资课”，我是你们的坎老师。

不要 10000，不要 5000，只需要 999 源石锭，一对一指导，手把手教学，从入门到精通，让你：


——**每选必赢，每投必中**，快速实现财富自由，富甲一方！

今天我们来到的地点是——**卡西米尔骑士锦标赛**。

本次的赛事有点不同，首先， $N$ 位骑士将自行组成骑士团，其中第 $i$ 号骑士将进入第 $a_i$ 号骑士团；

然后接下来的 $M$ 天里，每天将指定两个不同的骑士团 $x$ 和 $y$ ，接下来每一位 $x$ 骑士团里的成员都和每一位 $y$ 骑士团里的成员进行一次比试。

我们每一次比试将会下注，如果两位骑士的编号分别为 $a$ 和 $b$，那么如果你下注成功了，你将获得你的本金和 $a\times b$ 的源石锭。

当然了，每次下注你需要压上你的**所有本金**！

那么请问，接下来的 $M$ 天里，在我的指导下你每天分别可以获得多少源石锭？

**数据保证答案不超过 64 位有符号整型能表达的范围。**

**赌博有风险，投资需谨慎！**

![](https://cdn.luogu.com.cn/upload/image_hosting/gof3mumx.png)

## 说明/提示

骑士团 $1$ 的成员有 $\{1,2,9\}$，骑士团 $2$ 的成员有 $\{3,4,8\}$，骑士团 $3$ 的成员有 $\{5,6,7\}$。


第一天，骑士团 $1$ 和骑士团 $2$ 进行比赛。

获得的收益为：$1\times 3+1\times 4+1\times 8+2\times 3+2\times 4+2\times 8+9\times 3+9\times 4+9\times 8=180$。

第二天，骑士团 $2$ 和骑士团 $3$ 进行比赛。

获得的收益为：$3\times 5+3\times 6+3\times 7+4\times 5+4\times 6+4\times 7+8\times 5+8\times 6+8\times 7=270$。

第三天，骑士团 $1$ 和骑士团 $3$ 进行比赛。

获得的收益为：$1\times 5+1\times 6+1\times 7+2\times 5+2\times 6+2\times 7+9\times 5+9\times 6+9\times 7=216$。

## 样例 #1

### 输入

```
9 3
1 1 2 2 3 3 3 2 1
1 2
2 3
3 1
```

### 输出

```
180
270
216
```

# 题解

## 作者：Stars_visitor_tyw (赞：6)

## P10523 [XJTUPC2024] Everyone's ALL IN 题解
### 分析
水黄没错了。

主要思路是拆一个式子，拿样例中第一天来分析。$1\times 3+1\times 4+1\times 8+2\times 3+2\times 4+2\times 8+9\times 3+9\times 4+9\times 8=180$ 这是第一天的收益，由题可知每天的收益是由 $x$ 骑士团的成员编号分别乘上 $y$ 骑士团的成员编号再加起来。根据小学的乘法分配律，$1\times 3+1\times 4+1\times 8+2\times 3+2\times 4+2\times 8+9\times 3+9\times 4+9\times 8=(1+2+9) \times 3+(1+2+9) \times 4+(1+2+9) \times 8$，再用一次乘法分配律，$(1+2+9) \times 3+(1+2+9) \times 4+(1+2+9) \times 8=(1+2+9)\times (3+4+8)$。这时我们就可以得到思路了。统计每个骑士团的成员编号之和 $cnt_i$，每次询问用 $cnt_x \times cnt_y$ 即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int cnt[1000005], n, m;
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        cnt[x]+=i;
    }
    while(m--)
    {
        int x, y;
        cin>>x>>y;
        cout<<cnt[x]*cnt[y]<<"\n";
    }
}
```

---

## 作者：nevershow (赞：2)

## 思路
### 1. 暴力
可以暴力模拟比赛的过程。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[1000000];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
	}
	while(m--) {
		int sum=0,x,y;
		cin>>x>>y;
		for(int i=1;i<=n;i++){
			if(a[i]==x){
				for(int j=i;j<=n;j++){
					if(a[j]==y){
						sum+=i*j;
					}
				}
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}
```
超时，总时间复杂度为 $ O(mn^2) $。

考虑优化。

### 2. 优化

根据样例解释可以推出如下式子：
$$
1\times3+1\times4+1\times8+2\times3+2\times4+2\times8+9\times3+9\times4+9\times8

$$
$$
=[1\times(3+4+8)]+[2\times(3+4+8)]+[9\times(3+4+8)]
$$
$$
=15+30+135
$$
$$
=180
$$

根据推论过程，可以完成优化。计算出总时间复杂度为 $ O(\max(m,n)) $。

### code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int a[1000000],asd[1000000];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		cin>>a[i];asd[a[i]]+=i;
	}
	while(m--) {
		int sum=1,x,y;
		cin>>x>>y;
		sum=asd[x]*asd[y];
		cout<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：Eason_cyx (赞：2)

简单题。

首先假设 $1$ 号骑士团有 $n$ 人，第 $i$ 人编号为 $a_i$；$2$ 号骑士团有 $m$ 人，第 $i$ 人编号为 $b_i$。那么如果这两个骑士团对战，你获得的收益（记为 $M$）就是：

$$M = (a_1 \times b_1 + a_1 \times b_2 + \cdots + a_1 \times b_m) + (a_2 \times b_1 + a_2 \times b_2 + \cdots + a_2 \times b_m) + \cdots + (a_n \times b_1 + a_n \times b_2 + \cdots + a_n \times b_m)$$

运用一次乘法分配律，得到：

$$\displaystyle M = (a_1 \times \sum_{i=1}^{m}b_i) + (a_2 \times \sum_{i=1}^{m}b_i) + \cdots +  (a_n \times \sum_{i=1}^{m}b_i)$$

再运用一次乘法分配律，即为：

$$\displaystyle M = \sum_{i=1}^{n}a_i \times \sum_{j=1}^{m}b_j$$

那么，我们在输入的时候，记录下每一个骑士团的编号和，在查询时直接将两个团的和相乘即可。

时间复杂度 $O(n+m)$。

记得开 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long sum[1000005];
int main() {
    int n,m; cin >> n >> m;
    for(int i = 1;i <= n;i++) {
        int x; cin >> x;
        sum[x] += i;
    }
    while(m--) {
        int x,y; cin >> x >> y;
        cout << sum[x] * sum[y] << endl;
    }
    return 0;
}
```

本题使用空间较大，如果限制较小可考虑只存出现过的骑士团，可以减小内存使用。

---

## 作者：Melo_qwq (赞：1)

这题有橙？

# 题目大意

挺清楚的了，但是本金呢？题目描述半天还用黑体字加粗，看了样例和解释之后发现根本不用算本金，乐。

另外注意 $a_i\le1\times10^6$，数组别开小了。

# 题目实现

排除本金，我们要算的是：

$$
\sum_{i\in A,j\in B}i\times j
$$

其中 $A$ 和 $B$ 指那两个骑士团。

但是我们显然不能直接暴力枚举，复杂度 $O(mn^2)$ 显然会炸。

考虑优化。

我们假设两个骑士团分别是 $\{a,b,c\}$ 和 $\{d,e,f\}$，找一下规律（先依据题意有）：

$$
ans = a\times d+a\times e+a\times f+b\times d +b\times e+b\times f+c\times d+c\times e+c\times f
$$

化简有：

$$
ans =  (a+b+c)\times(d+e+f)
$$

那么我们只需要算出每个骑士团骑士的编号之和再相乘即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define rep(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using namespace std ;
const int N = 1e6 + 7 ;
typedef long long ll ;
ll n ,m ,sum[N] ;
template <typename T> inline void read (T &x) {
	x = 0 ;
	char ch = getchar () ;
	while (! isdigit (ch)) {
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch xor 48) ;
		ch = getchar () ;
	}
}
int main () {
	read (n) ,read (m) ;
	rep (i ,1 ,n ,1) {
		int x ;
		read (x) ;
		sum[x] += i ;
	}
	rep (i ,1 ,m ,1) {
		int x ,y ;
		read (x) ,read (y) ;
		cout << sum[x] * sum[y] << '\n' ;
	}
	return 0 ;
}
//kafka & かみや & やえみこ
```

---

## 作者：xiaoyang111 (赞：1)

## 前言

[题目传送门。](https://www.luogu.com.cn/problem/P10523)

## 题解

### 思路

题面其实就是给若干个团体，然后询问两个团体中所有数两两相乘的所有结果的和。


假设我们拿到了两个团体的每个数，第一个团体分别为 $a_1,a_2$，第二个团体分别为 $b_1,b_2,b_3$。那么答案就是 $a_1 \times b_1 + a_1 \times b_2 + a_1 \times b_3 + a_2 \times b_1 + a_2 \times b_2 + a_2 \times b_3$。枚举就是 $O(n^2)$ 的时间复杂度，这是不能接受的。

我们看到有很多的相同的数，考虑乘法分配律合并。就成了 $a_1 \times (b_1 + b_2 + b_3) + a_2 \times (b_1 + b_2 + b_3)$。能用 $O(n)$ 的时间复杂度解决，但是还是太慢了。

看到还有相同的 $(b_1 + b_2 + b_3)$，再合并就成了 $(a_1 + a_2) \times (b_1 + b_2 + b_3)$。

总的整理一下，设 $a$ 和 $b$ 为两个团体中的所有数，那么就是 $a$ 里面的所有数的和再乘上 $b$ 里面所有数的和。每次询问的时间复杂度就降到了 $O(1)$。

### 实现

对于总和，我们可以直接在输入的时候把团体内的所有数算出来，后面询问的时候直接算就可以了。

代码：

```cpp
#include <iostream>
using namespace std;
const int M=1e6+5;
long long sm[M];
int main(){
	int n,m;
	cin >> n >> m;
	int t;
	for (int i=0;i<n;++i){
		scanf("%d",&t);
		sm[t]+=i+1;
	}
	int a,b;
	for (int i=0;i<m;++i){
		scanf("%d%d",&a,&b);
		printf("%lld\n",sm[a]*sm[b]);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10523)

感觉评黄有点高，大致思路还是很好想的。

**暴力做法**

直接计算 $x$ 和 $y$ 两个队伍互相比试之后获得的源石锭，会超时。

**满分做法**

根据乘法分配律，有

$$a\times b+a\times c=a\times(b+c)$$

再代入到题目中，可以发现每次的答案就是 $x$ 队编号总和 $\times$ $y$ 队编号总和，预处理一下就好了。

注意开 `long long`！

---

## 作者：xzz_0611 (赞：1)

[题目传送门](/problem/P10523)
## 分析
显然，直接套两层 `for` 循环累加求和会 TLE。

可以设每次比试的两个骑士团中分别有 $a$ 和 $b$ 个人，第一个骑士团的成员的编号依次为 $c_1,c_2,c_3,\dots,c_a$，第二个骑士团的成员的编号依次为 $d_1,d_2,d_3,\dots,d_b$，如果这两个骑士团进行比试，将可以获得 $c_1\times d_1+c_1\times d_2+c_1\times d_3+\dots+c_1\times d_b+c_2\times d_1+c_2\times d_2+c_2\times d_3+\dots+c_2\times d_b+\dots+c_a\times d_1+c_a\times d_2+c_a\times d_3+\dots+c_a\times d_b$ 个源石锭，根据乘法分配律化简后得 $\displaystyle\big(\sum_{i=1}^{a}c_i\big)\times\big(\sum_{i=1}^{b}d_i\big)$，对于其他的任意两个骑士团进行比试也是一样，所以只需要将每个骑士团的成员的编号之和预处理出来即可。
## Code
```cpp
#include<iostream>
#define int long long//不开 long long 见祖宗
using namespace std;
int n,m,a,x,y,cnt[1000001];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a,cnt[a]+=i;//累加编号和
	while(m--) {
		cin>>x>>y;
		cout<<cnt[x]*cnt[y]<<"\n";//直接输出乘积
	}
	return 0;
}
```

---

## 作者：ghx0052 (赞：1)

## 思路
对于每个骑士团，只需要算出所有人的价值和，每次查询时算出两个骑士团的：
$$
\sum^n_{i=1}\sum^m_{j=1}a_i+b_j=\sum^n_{i=1}a_i\times\sum^m_{j=1}b_j
$$
也就是价值和之积；
## 代码
那么很好实现，只需注意把桶开到 $10^6$ 就行了；
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int mp[1001000]; // 开桶
signed main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		int x;
		cin >> x;
		mp[x] += i; // 统计和
	}
	while (m --) {
		int x, y;
		cin >> x >> y;
		cout << mp[x] * mp[y] << endl; // 计算价值
	}
}
```

---

## 作者：Drifty (赞：1)

### Preface

建议降级。

### Solution

我们由样例说明容易发现，两个骑士团比赛的最大收益即为两个骑士团成员下标之和相乘，直接实现即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int v[1000006];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	for (int i=1, a; i<=n; i++)
		cin >> a, v[a] += i;
	for (int x, y; m; m--)
		cin >> x >> y, 
		cout << v[x] * v[y] <<'\n';
	return 0;
}
```

---

## 作者：JYX0924 (赞：1)

这道题中两组骑士两两比试求和，将式子列出来提取公因数其实就是求二者集合内的元素和相乘，直接将集合内元素和初始化就可以轻松过掉。

注意事项在代码中。
```c
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,y,a,sum[1000005]; //记得开long long
int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0); //优化输入输出速度
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	cin>>a,sum[a]+=i;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y; printf("%lld\n",sum[x]*sum[y]);
	}
	return 0;
}
```
谢谢大家！！！

---

## 作者：Breath_of_the_Wild (赞：0)

根据样例可以看出，题目就是上我们求两组之间的数两两相乘得到的结果相加。

用公式写就是
$$a_1\times b_1+a_1\times b_2+\cdots+a_1\times b_m+a_2\times b_1+a_2\times b_2+\cdots+a_2\times b_m+a_n\times b_1+a_n\times b_2+\cdots+a_n\times b_m$$
整理，即为
$$(a_1+a_2+\cdots+a_n)(b_1+b_2+\cdots+b_m)$$
实际上，任意的 $a$ 和 $b$ 数组的和都是可以在输入中直接得到的。

输入时，输入得到第 $i$ 个位置在第 $x$ 个骑士团里，就让桶中 $x$ 对应的位置加入元素，即加上 $i$。

桶内元素的和就是某个骑士团的和。输出时，直接两个桶的乘积即可。

主函数不超十行。
```cpp
cin>>n>>m;
for(ll i=1;i<=n;i++){
	cin>>x;
	buc[x]+=i;
}
while(m--){
	cin>>x>>y;
	cout<<buc[x]*buc[y]<<'\n';
}
return 0;
```

---

## 作者：Genius_Star (赞：0)

### 题意：

定义集合 $S_i$ 表示第 $i$ 个骑士团的编号集合。

给定 $m$ 次询问，每次给定 $x,y$，求：

$$\sum_{i \in S_x} \sum_{j \in S_y} i \times j$$

### 思路：

定义 $a_i$ 表示第 $i$ 个骑士团的编号和，则式子化简为：

$$\sum_{j \in S_y} (\sum_{i \in S_x} i) \times j = \sum_{j \in S_y} a_i \times j = a_i \sum_{j \in S_y} j = a_i \times a_j$$

则输入的时候将 $a$ 预处理出来即可。

时间复杂度为 $O(N + M)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
using namespace std;
typedef long long ll;
typedef double db;
const ll N=1e6+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m;
ll a[N];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  a[read()]+=i;
	while(m--){
		write(a[read()]*a[read()]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：qw1234321 (赞：0)

不难得到，若骑士团 $x$ 与骑士团 $y$ 进行比赛，则要求下面这个式子的值：

$$\sum _ {i = 1} ^ {sz_x} \sum _ {j = 1} ^ {sz_y} x_i \times y_j$$

其中 $sz_i$ 表示骑士团 $i$ 的总人数，$a_i$ 表示骑士团 $a$ 的第 $i$ 位骑士。

很容易发现上面式子可以拆开，得：

$$\sum _ {i = 1} ^ {sz_x}x_i \times \sum _ {j = 1} ^ {sz_y} y_j$$

这是啥？骑士团 $x$ 每一个人的下标之和乘上骑士团 $y$ 每一个人的下标之和啊。

所以预处理出每一个骑士团人员下标的和即可。

时间复杂度：$\mathcal O(n+m)$。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5, M = 61, INF = LONG_LONG_MAX / 2;
int n, m;
int bel[N], a[N];

void work(){
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		cin >> bel[i];
		a[bel[i]] += i;
	}
	while(m--){
		int x, y;
		cin >> x >> y;
		cout << 1ll * a[x] * a[y] << "\n";
	}
}

signed main(){
	int t = 1;
	//	cin >> t;
	while(t--) work();
	return 0;
}
```

---

