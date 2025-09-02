# Easy Demon Problem

## 题目描述

机器人定义了一个网格的美丽值，就是其中所有元素的总和。现在他给了你两个数组：一个长度为 $n$ 的数组 $a$ 和一个长度为 $m$ 的数组 $b$。你的任务是利用这两个数组建立一个 $n \times m$ 的网格 $M$，其中 $M_{i,j} = a_i \cdot b_j$ 对于所有的 $1 \leq i \leq n$ 和 $1 \leq j \leq m$ 均成立。

接下来，机器人会提供 $q$ 个查询。对于每个查询，会给出一个整数 $x$。你的目标是判断是否可以通过以下操作，使得网格 $M$ 的美丽值恰好为 $x$：

1. 选择一行 $r$ 和一列 $c$，满足 $1 \leq r \leq n$ 和 $1 \leq c \leq m$。
2. 将所有在第 $r$ 行或第 $c$ 列，或者同时位于这两者交叉处的元素设为 $0$。

需要注意的是，各个查询之间是相互独立的，这意味着你不必实际修改网格的元素为零——你只需判断是否存在这样的一对 $r$ 和 $c$，如果进行上述操作能使网格的美丽值为 $x$。即便网格的初始美丽值已经是 $x$，你仍然需要选择行和列并执行这个操作。

## 样例 #1

### 输入

```
3 3 6
-2 3 -3
-2 2 -1
-1
1
-2
2
-3
3```

### 输出

```
NO
YES
NO
NO
YES
NO```

## 样例 #2

### 输入

```
5 5 6
1 -2 3 0 0
0 -2 5 0 -3
4
-3
5
2
-1
2```

### 输出

```
YES
YES
YES
YES
NO
YES```

# 题解

## 作者：ohjun (赞：4)

## 思路分析
为了方便，将 $b$ 的和设为 $s_b$，$a$ 的和设为 $s_a$。不难发现第 $i$ 行的和等于 $a_i b_1 + a_i b_2 + \ldots + a_i b_m$，可以化简为 $a_i s_b$。所以所有值的和就等于 $a_1 s_b + a_2 s_b \ldots + a_n s_b$，等价于 $s_a s_b$。同理我们可以得出第 $i$ 列的表达式为 $b_is_a$。那么我们可以用容斥原理得出一次对第 $i$ 行，第 $j$ 列的操作所减少的量就等于 $a_is_b + b_js_a - a_ib_j$。每次询问就是问是否有满足条件的 $a_i, b_j$ 使所有值的和减第 $i$ 行，第 $j$ 列的变化量可以得到 $x$。可以列出如下方程：
$$
  s_as_b - a_i s_b - b_j s_a + a_i b_j = x
$$
十字相乘化简得：
$$
  (s_a - a_i)(s_b - b_j) = x
$$
显然我们不能一个个枚举 $i, j$，但可以将所有的 $s_a - a_i$ 和 $s_b - b_j$ 存下来，对于每个 $x$ 分解因数为 $l \cdot r$ 形式，检查是否存在 $l, r$ 分别在 $s_a - a_i$ 和 $s_b - b_j$ 中即可。
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;
int n, m, q;
ll A[maxn], B[maxn];
ll s_a = 0LL, s_b = 0LL;
unordered_map<ll, bool> vis[2];

void input()
{
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++)
    {
        cin >> A[i];
        s_a += A[i];
    }
    for(int i = 1; i <= n; i++)
        vis[0][s_a - A[i]] = true;
    for(int i = 1; i <= m; i++)
    {
        cin >> B[i];
        s_b += B[i];
    }
    for(int i = 1; i <= m; i++)
        vis[1][s_b - B[i]] = true;
}

bool solve(int x)
{
    bool flag = false;
    if(x < 0)
    {
        x *= -1;
        flag = true;
    }
    for(int i = 1; i  <= sqrt(x); i++)
        if(!(x % i))
        {
            if(flag)
            {
                if(vis[0][i] && vis[1][x / i * -1] || vis[0][x / i * -1] && vis[1][i])
                    return true;
                if(vis[0][i * -1] && vis[1][x / i] || vis[0][x / i] && vis[1][i * -1])
                    return true;
            }
            else
            {
                if(vis[0][i] && vis[1][x / i] || vis[0][x / i] && vis[1][i])
                    return true;
                if(vis[0][i * -1] && vis[1][x / i * -1] || vis[0][x / i * -1] && vis[1][i * -1])
                    return true;
            }
        }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    input();
    while(q--)
    {
        int num;
        cin >> num;
        if(solve(num)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}

```

---

## 作者：Peaky (赞：2)

### 题目大意
给定两个序列 $A B$，一个二维数组，其中 $a_{i,j}=A_i\times B_i$。  
$q$ 次询问，每次询问给定一个 $x$，问是否存在一个 $i,j$ 使得第 $i$ 行 $j$ 列全部改为 $0$ 后，二维数组每一个元素之和为 $x$。
### 思路
考虑删掉一个 $i,j$ 的结果。  
![](https://cdn.luogu.com.cn/upload/image_hosting/gtyt2epx.png)  
考虑这张图的情况。  
我们删掉 $i,j$ 后，把剩余的四块拼到一起，答案变成： 
$$
\sum_{p\ne i}{\sum_{q\ne j}{A_p\times B_q}}
$$
容易想到把他们分开来求，上述式子也就变成：
$$
\sum_{p\ne i}{A_p}\times\sum_{q\ne j}{B_q}
$$
其中：
$$
suma=\sum{A_i},sumb=\sum{B_i}
$$
考虑预处理，于是就有：
$$
(suma-A_i)\times(sumb-B_j)
$$
从而问题也就传换成了求因数。
### 实现
将所有的 $suma-A_i$ 和 $sumb-B_i$ 用两个集合存储，判断能否在其中一个集合中存在 $x$ 的因数 $p$，并且在另一个集合中，找到 $\frac{x}{p}$。  
时间复杂度：$O(n+m+\sqrt{x})$。
### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=5e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
set<int> ta,tb;
int t,a[N],b[N],n,m,q,suma,sumb;
void Solve(){
	cin>>n>>m>>q; suma=sumb=0;
	for(int i=1;i<=n;i++) cin>>a[i],suma+=a[i];
	for(int i=1;i<=m;i++) cin>>b[i],sumb+=b[i];
	for(int i=1;i<=n;i++) ta.insert(suma-a[i]);
	for(int i=1;i<=m;i++) tb.insert(sumb-b[i]);
	while(q--){
		int x,res;
		cin>>x;
		if(!x){
			cout<<(ta.count(x)||tb.count(x)?"YES":"NO")<<"\n";
			continue;
		}
		bool f=0; res=abs(x);
		for(int i=1;i<=res/i&&!f;i++){
			if(res%i==0){
				if(ta.count(i)&&tb.count(x/i)) f=1;
				if(ta.count(-i)&&tb.count(-x/i)) f=1;
				if(tb.count(i)&&ta.count(x/i)) f=1;
				if(tb.count(-i)&&ta.count(-x/i)) f=1;
			}
		}
		cout<<(f?"YES":"NO")<<"\n";
	}
}
signed main(){
	Solve();
	return 0;
}
```

---

## 作者：Misaka屮Mikoto (赞：2)

# CF2044F Easy Demon Problem 
### 题目大意
给定两个长度为 $n,m$ 的数列 $a_i$ ，$b_j$ ，并且依据该数列构造一个矩阵 $M_{n,m}$，使得 $M_{i,j}=a_i \times b_j$ 。

再给出 $q$ 个查询，对于每个 $x_i$，查找是否存在一对 $i,j$ 使得该矩阵删去第 $i$ 行和第 $j$ 列，使得矩阵剩下所有数之和为 $q_i$。

**每一组询问是独立的。**
### 思路
我们发现，矩阵之和可以写为
$$\sum_{i=0}^{n}{\sum_{j=0}^{m}{a_i \times b_j} }$$
可以变形为

$$\sum_{i=0}^{n}{a_i} \times \sum_{j=0}^{m}{b_i}$$

上式等价于 
$$sum(a) \times sum(b) $$

我们神奇的发现，当删去这个矩阵的第 $i$ 行第 $j$ 列的时候，矩阵里面的所有元素之和就是：
$$[sum(a)-a_i]\times[sum(b)-b_j]$$

我们的目的就转换为求是否有一对 $a_i$ 和 $b_j$ 使得 $[sum(a)-a_i]\times[sum(b)-b_j]=x$ 。

**重点：**
我们分别记录每一个数组 $a,b$ ，并分别求出他们的和。对于每一个询问 $x$ ，分解 $x$ 的因数，查找每一对因数 $l,r$ ，假设 $l=sum(a)-a_i,r=sum(j)-b_j$ ，则问题又被转换为求是否存在 $a_i=sum(a)-l,b_j=sum(j)-r$ 。这里考虑数据范围，开个大数组记录即可。

注意数存在负数需要处理，时间复杂度为 $O(q)$ (有个 $\sqrt {2⋅10^5}$ 的常数)可过。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
bool ina[500010],inb[500010];
int la[300010],lb[300010];
ll sum1=0,sum2=0;
bool checkin(bool f,ll num){
    if(num>250000||num<-250000)return false;
    if(!f)return ina[num+250000];
    return inb[num+250000];
}
bool checkit(ll a,ll b,int f){
    int fl1=1,fl2=1;
    if(f)fl1=-1;
    if(checkin(0,sum1-a*fl1)&&checkin(1,sum2-b*fl2))return true;
    if(checkin(1,sum2-a*fl1)&&checkin(0,sum1-b*fl2))return true;

    fl1=-fl1,fl2=-fl2;

    if(checkin(0,sum1-a*fl1)&&checkin(1,sum2-b*fl2))return true;
    if(checkin(1,sum2-a*fl1)&&checkin(0,sum1-b*fl2))return true;
    return false;

}
int main()
{
    //freopen("read.in","r",stdin);
    int n,m,q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;++i)scanf("%d",&la[i]),sum1+=la[i],ina[la[i]+250000]=true;
    for(int i=1;i<=m;++i)scanf("%d",&lb[i]),sum2+=lb[i],inb[lb[i]+250000]=true;
    for(int i=1;i<=q;++i){
        int x;
        scanf("%d",&x);
        int f=0;
        if(x<0)f=1,x=-x;

        for(int j=1;j<=sqrt(x);++j){
            if(x%j==0){
                if(checkit(j,x/j,f)){
                    printf("Yes\n");
                    f=2;
                    break;
                }
            }
        }
        if(f==2)continue;
        printf("No\n");
    }
}
```

---

## 作者：hujiasheng1234 (赞：1)

令 $suma$ 为所有的 $a_i$ 和，$sumb$ 为所有的 $b_i$ 和

首先对于每一次操作，不难发现矩阵去掉一行一列后拼接，元素和即为 $(suma-a_i) \times (sumb-b_i)$ 

其实也有 $suma \times sumb - a_i \times sumb -b_i \times suma +a_i\times b_i = (suma-a_i) \times (sumb-b_i)$ 

然后就可以想到对 $x$ 求因数，将每一个 $(suma-a_i)$ 和 $(sumb-b_i)$ 分别用两个 $map$ 保存

注意 $x$ 可能是负数，所以若 $i$ 是 $n$ 的因子 则 $-i$ 也要一起判断

其他详见代码：

```
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int mx=2e5+5;
int T,n,m,q,a[mx],b[mx],x;
map<int,int> mp1,mp2;
void solve(){
	mp1.clear();mp2.clear();
	int _1=0,_2=0;
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++) cin>>a[i],_1+=a[i];
    for(int i=1;i<=m;i++) cin>>b[i],_2+=b[i];
    for(int i=1;i<=n;i++) mp1[_1-a[i]]++;//统计 suma-a_i 
    for(int i=1;i<=m;i++) mp2[_2-b[i]]++;//统计 sumb-b_i 
    while(q--){
    	cin>>x;
    	int f=1;
    	for(int i=1;i<=sqrt(abs(x));i++){//求因数 
			int ii=-i;//-i的情况 
    		if(x%i==0&&((mp1[i]&&mp2[x/i]||mp2[i]&&mp1[x/i])||(mp1[ii]&&mp2[x/ii]||mp2[ii]&&mp1[x/ii]))){//ii和i, suma-a_i 和 sumb-b_i 是哪个因子都要判断 
    			cout<<"YES"<<endl;
    			f=0;
    			break;
			}
		}
		if(f) cout<<"NO"<<endl;
	}
}
signed main(){
	ios::sync_with_stdio(0);cout.tie(0);cin.tie(0);
	T=1;
	while(T--) solve();
	return 0;
}

---

## 作者：wflhx2011 (赞：0)

首先，将要求的式子化简，若删去第 $i$ 行第 $j$ 列，设 $sum_a=\sum_{i=1}^n a_i$，$sum_b=\sum_{i=1}^m b_i$，答案为 $sum_a \times sum_b-sum_a \times b_j-sum_b \times a_i+a_i\times b_j=(sum_a-a_i)(sum_b-b_j)$。

显然，每个 $sum_a-a_i$ 和 $sum_b-b_j$ 都可以预处理并记录下来。

那么，对于每个询问，可以暴力枚举，若是 $x$ 的因数就判断有没有出现过。

时间复杂度准确一些是 $O(n+m+q \sqrt x)$，需要卡卡常。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
long long a[200005],b[200005],suma,sumb;
set<long long> mp1,mp2;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long t;
	cin>>n>>m>>t;
	for(long long i=1;i<=n;i++)	
		cin>>a[i],suma+=a[i];
	for(long long i=1;i<=m;i++)
		cin>>b[i],sumb+=b[i];
	for(long long i=1;i<=n;i++)
		mp1.insert(suma-a[i]);
	for(long long i=1;i<=m;i++)
		mp2.insert(sumb-b[i]);
	while(t--)
	{
		long long x,res;
		cin>>x;
		if(x==0)
		{
			cout<<((mp1.count(0)||mp2.count(0))?"YES":"NO")<<"\n";
			continue;
		}
		bool f=0;
		res=abs(x);
		for(long long i=1;i<=res/i&&!f;i++)
			if(res%i==0)
			{
				if(mp1.count(x/i)&&mp2.count(i)||mp1.count(i)&&mp2.count(x/i))
					f=1;
				if(mp1.count(-x/i)&&mp2.count(-i)||mp1.count(-i)&&mp2.count(-x/i))
					f=1;
			}
		cout<<(f?"YES":"NO")<<"\n";
	}
	return 0;
 }   
```

---

