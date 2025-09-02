# Gold Rush

## 题目描述

Initially you have a single pile with $ n $ gold nuggets. In an operation you can do the following:

- Take any pile and split it into two piles, so that one of the resulting piles has exactly twice as many gold nuggets as the other. (All piles should have an integer number of nuggets.)

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829D/7d414b1e40fe9f84ac7152f64f7f831c73043b5b.png)One possible move is to take a pile of size $ 6 $ and split it into piles of sizes $ 2 $ and $ 4 $ , which is valid since $ 4 $ is twice as large as $ 2 $ .

 Can you make a pile with exactly $ m $ gold nuggets using zero or more operations?

## 说明/提示

The first test case is pictured in the statement. We can make a pile of size $ 4 $ .

In the second test case, we can perform the following operations: $ \{\color{red}{9}\} \to \{\color{red}{6},3\} \to \{4,2,3\} $ . The pile that is split apart is colored red before each operation.

In the third test case, we can't perform a single operation.

In the fourth test case, we can't end up with a larger pile than we started with.

## 样例 #1

### 输入

```
11
6 4
9 4
4 2
18 27
27 4
27 2
27 10
1 1
3 1
5 1
746001 2984004```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
YES
NO
NO```

# 题解

## 作者：zhlzt (赞：11)

### BFS 做法
其实很简单，要满足题目要求，每次将一个有 $num$ 个金币的金堆分成两堆，就是将 $num$ 拆分成 $\dfrac{n}{3}$ 和 $2\times \dfrac{n}{3}$，跑一遍 BFS 就行了，复杂度约为 $O(t\times2^{\log n})$。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
bool bfs(int n,int m){
	queue<int>q;q.push(n);
	while(!q.empty()){
		int num=q.front();q.pop();
		if(num==m) return 1;
		if(num<m) continue;
		if(num%3==0) q.push(num/3),q.push(num/3*2);
	}
	return 0;
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,m;scanf("%d%d",&n,&m);
		if(bfs(n,m)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

```

---

## 作者：cjh20090318 (赞：5)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

**本题有多组数据。**

给你一堆金条，有 $n$ 个，你可以把一堆金条刚好分成两份使得其中一堆金条的数量正好为另外一堆数量的 $2$ 倍。

问你有没有一种分割方法使得其中一堆金条的数量为 $m$。

## 分析

由题意，一堆能分割的金条必须为 $3$ 的倍数。

如果这一堆金条的数量为 $m$，那么一定输出 `YES`。

如果这一堆金条的数量（这里设为 $a$）为 $3$ 的倍数，那么就把它分割为 $\dfrac{1}{3}a$ 和 $\dfrac{2}{3}a$。

就可以直接用 `vector` 来存每一堆金条，然后遍历每一堆金条进行操作即可。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<vector>
std::vector<int> a;
void solve(){
	int n,m;scanf("%d%d",&n,&m);
	if(n<=m){puts(n==m?"YES":"NO");return;}
	a.clear();//注意清空 vector。
	a.push_back(n);//加入第一堆金条。
	int size=1;
	while(1){
		for(int i=0;i<size;i++){//遍历 vector。
			if(a[i]==m){puts("YES");return;}//这一堆金条数量为 m 直接输出 "YES"。
			if(!(a[i]%3)) a.push_back(a[i]/3*2),a[i]/=3;//这一堆为 3 的倍数，将当前堆直接修改，另加一堆至 vector 末尾。
		}
		if(a.size()>size)size=a.size();//更新 vector 长度。
		else{puts("NO");return;}//当前长度没有变化，说明已经无解。
	}
	puts("YES");
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}

```

---

## 作者：zajasi (赞：3)

## 题意
给你一个 $n$ 表示总数量，$m$ 表示你需要分出的数量。每一次分，你需要按照 $1:2$ 的比例把一堆分成两堆。问能不能分出数量为 $m$ 的一堆？
## 解题思路
赛时，我的朋友用了推结论的方法，还错了好几发。我觉得其实不必这么麻烦。

考虑到 $n\le 10^7$，我们直接深搜。对于每一堆，如果是 $3$ 的倍数，就将它分，否则就不分。然后直接查找有没有。由于每个数只会被搜一次，所以复杂度应该是 $\Theta(n)$ 左右。

交上去就离谱了:

![](https://cdn.luogu.com.cn/upload/image_hosting/ir3306pd.png)
## AC 代码
```cpp
/*
written by : zjs123
QQ : 755328053
Wechat : zoujinshu18
CZOJ : zjs123
luogu : _JSYX_
atcoder : zajasi10
codeforces : _JSYX_
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long  
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
int t;
int n,m;
int f;
void dfs(int x,int y){
    if(f==1)return;
    if(x==y){
        f=1;
        return;
    }
    if(x%3==0){
        dfs(x/3,y);
        dfs(x/3*2,y);
    }
}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n>>m;
        f=0;
        dfs(n,m);
        if(f==1)cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}

```

---

## 作者：guanyf (赞：2)

### 思路：
**直接 DFS**：设当前金币数为 $x$，分成两份一份是另一份的两倍，设分后的金币数为 $y$，则 $2y+y=x$，可以得出 $y=\frac{x}{3}$，显然当 $x$ 不是 $3$ 的倍数时，金币是分不了的。且当 $x < m$ 的时候，无论怎么分，都是不行的。否则，去对 $\frac{x}{3}$ 与 $\frac{2x}{3}$ 进行操作，直到 $x = m$。


#### 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, n, m;
bool dfs(int x) {
  return x == m ? 1 : (x % 3 || x < m ? 0 : dfs(x / 3) | dfs(x / 3 * 2));
}
signed main() {
  ios::sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n >> m;
    cout << (dfs(n) ? "YES" : "NO") << '\n';
  }
  return 0;
}
```

### 拓展：
$n$ 经过若干次除三和乘二 变成了 $m$，且乘二的次数 $x$ 小于等于乘三的次数 $y$，因此题目可以转换成：$n \times 2^x=m \times 3^y$。我们可以先预处理出 $2^{31}-1$ 以内的 $2$ 的某次幂与 $3$ 的某次幂，接着枚举 $x$，因此 $3^y = \frac{n \times 2^x}{m}$。用 `unordered_map` 判断它是否出现过，且 $x \le y$。

时间复杂度约等于：$\operatorname{O}(t)$。

[![](https://cdn.luogu.com.cn/upload/image_hosting/n379ma5b.png)](https://cdn.luogu.com.cn/upload/image_hosting/n379ma5b.png)


---

## 作者：封禁用户 (赞：2)

## 分析

爆搜即可。

我们对于每一个 $n$，如果这个 $n$ 刚好等于 $m$，返回 $1$。如果这个 $n$ 不为 $3$ 的倍数，则它一定不能分成 $a~b$，使 $a=2 \times b$，因为在 $a=2 \times b$ 时，$n$ 满足：$n=3 \times b$，返回 $0$。若 $n$ 是 $3$ 的倍数，则将 $n$ 分成 $a~b$，返回 $a$ 与 $b$ 返回的值的最大值，因为有一个返回 $1$ 就一定可以，而 $1＞0$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int dfs(int now,int m)
{
	if(now==m) return 1;
	else if(now<m) return 0;
	else
	{
		if(now%3!=0) return 0;
		else return max(dfs(now/3,m),dfs(now/3*2,m));
	}
}
int main() 
{
	cin>>t;
	while(t--) 
	{
		cin>>n>>m;
		if(dfs(n,m)) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：沉石鱼惊旋 (赞：2)

[更好的阅读体验](http://blog.cyx2009.top/archives/169/)

# D.[Gold Rush](https://codeforces.com/contest/1829/problem/D)

## 题目翻译

> 有一堆含有 $n$ 个石子的石子堆，你每次可以选择大小为 $k$ 的一堆，将其分成 $\frac{k}{3}$ 与 $\frac{2\times k}{3}$ 两堆，问是否可以得到大小为 $m$ 的堆。
> 
> $1\leq n,m\leq 10^7$。
> 
> $t$ 组数据，$t\leq 1000$。

## 题目思路

我们通过阅读题面，因为这个 $n$ 是要分成三份然后一堆一份一堆两份，显然可以得到 $n,m$ 只有可以表示为 $n=3^i\times p,m=2^j\times p(0\leq j\leq i,p\geq 0)$ 时，我们才可以分出来。

考虑到 $n,m$ 都很小，我们枚举这个 $i,j$，判断是否可行即可。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve()
{
    int n,m,tmp3=1,tmp2;
    cin>>n>>m;
    for(int i=0;i<=15;i++)
    {
        tmp2=1;
        for(int j=0;j<=i;j++)
        {
            if(n%tmp3==0&&n/tmp3*tmp2==m)
            {
                puts("YES");
                return;
            }
            tmp2*=2;
        }
        tmp3*=3;
    }
    puts("NO");
}
int main()
{
    int t;cin>>t;while(t--)
    solve();
    return 0;
}
```


---

## 作者：tbdsh (赞：1)

# 题意简述
[题目传送门](/problem/cf1829d)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-cf1829d)

本题有 $t$ 组数据。对于每组数据，你都会得到 $n$ 个金币。

现在，你可以对这 $n$ 个金币进行分堆。每次分堆只能分成两堆，并且需要使分堆后的一堆恰好是另一堆的**两倍**。同时，分成的两堆都必须有**整数**个金币。

请你判断：在经过多次或不经过分堆后能否有任意一堆的金币数为 $m$。如果可以，请输出 `YES` 或其它任意的大小写形式；否则，请输出 `NO` 或其它任意的大小写形式。
# 分析
因为 $n\le 10^7$，所以考虑爆搜。

每次从 $x$ 转移到 $\dfrac{x}{3}$ 和 $\dfrac{2\times x}{3}$，总共转移 $2\times\log_3 n$ 次，不会超时。

当 $x=m$ 时，退出递归，$x<m$ 时，同样退出递归。

时间复杂度：$O(t\times \log_3 n)$。

空间复杂度：$O(1)$。
# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
int t, a, b;
bool flag;
void dfs(int x){
  flag |= x == b;//这行代码 = flag = flag | x == b。采用了一个二进制运算技巧。
  if (x < b || x % 3 || flag){
    return ;
  }
  dfs(x / 3), dfs(x / 3 * 2);//转移。
}
void Solve(){
  cin >> a >> b;
  flag = 0;
  dfs(a);
  cout << (flag ? "YES\n" : "NO\n");
}
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：luqyou (赞：1)

# 题意

有一堆黄金，有 $n$ 块，每次可以把它分成 $n \times \dfrac{1}{3}$ 块和 $n \times \dfrac{2}{3}$ 块两堆。给出 $n,m$，问能否将一堆 $n$ 块黄金通过上述操作零次或多次来分出一堆 $m$ 块黄金。

# 思路

对于一个数 $n$，对其操作一次，相当于去掉其因子中的一个 $3$，在获得一个因子 $2$（当然，如果是少的那一堆就是只去掉一个因子 $3$）。那么我们对 $n,m$ 中 $2$，$3$ 的因子数量统计，如果可以通过去掉因子 $3$，并适当地加上因子 $2$ 来使 $n$ 变为 $m$，那么输出 ```yes```，否则输出 ```no```。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
	int n,m,nsum2=0,nsum3=0,msum2=0,msum3=0;
	cin>>n>>m;
	if(n<m){//不可能越分越多
		cout<<"no"<<endl;
		return ;
	}
	if(n==m){//不需要操作，输出 yes，在这里特判掉是因为后面有没有因子 3 的情况
		cout<<"yes"<<endl;
		return ;
	}
	while(n%2==0){
		nsum2++;
		n/=2;
	} 
	//分解 2 和 3
	while(n%3==0){
		nsum3++;
		n/=3;
	}
	while(m%2==0){
		msum2++;
		m/=2;
	}
	while(m%3==0){
		msum3++;
		m/=3;
	}
	if(n!=m){//其他因子不同
		cout<<"no"<<endl;
		return ;
	}
	if(nsum3==0){//无因子 3，无法分下去，当然是 no
		cout<<"no"<<endl;
		return ;
	}
	if(nsum2>msum2){//自己因子 2 比目标多，由于因子 2 只加不减，所以输出 no
		cout<<"no"<<endl;
		return ;
	}
	if(nsum3>=msum2-nsum2){//可以通过去掉因子 3 并适当加上因子 2 变为相同
		cout<<"yes"<<endl;
	}
	else{//否则就是 no
		cout<<"no"<<endl;
	}
}
int main(){
 	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：szhqwq (赞：0)

## 分析

考虑 dfs。

我们可以从 $m$ 反推到 $n$，令当前数为 $x$，那么有 $2$ 种情况：

1. 当 $x$ 为 $2$ 的倍数，搜索 $x \cdot \frac{3}{2}$ ；
2. 搜索 $x \cdot 2$。

当 $x > n$，即不可行，结束当前分支。

当 $x = n$，可行，我们标记一下，结束当前分支。

最后判断是否标记过，输出答案即可。

## AC Code of [CF1829D](https://codeforces.com/contest/1829/problem/D)

[Link](https://codeforces.com/contest/1829/submission/204814229)

---

## 作者：Sk_sync_opener (赞：0)

太细节了。

$n=m$ 时，显然可以。

$n<m$ 时，显然不行。

否则，在 $n\equiv 0\pmod 3$ 时，不断将 $n$ 除以 $3$，设 $n=k\times 3^b$，则 $m$ 必须表示乘 $k\times 2^a(a\le b)$ 的形式才可以。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
string k = "codeforces";
signed main() {
    ios::sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
    	int n, m; cin >> n >> m;
    	if(m == n) {puts("YES"); continue;}
    	if(n < m) {puts("NO"); continue;}
    	set<int> can; can.clear(); int cnt =0 ;
    	while(n % 3 == 0) {
    		n /= 3;
    		cnt++;
			for(int i = 0; i <= cnt; i++) can.insert(n * (1 << i));
		}
    	if(can.find(m) != can.end()) puts("YES"); else puts("NO");
	}
    return 0;
}
```

---

## 作者：rmzls (赞：0)

### 思路
若有解，则 $m$ 一定是 $n$ 乘上若干个 $\dfrac{1}{3}$ 或 $\dfrac{2}{3}$ 得到的（前者可以看成选择了拆分后较小的那一块，后者选择了较大的那一块），所以我们将 $n$ 和 $m$ 约分一下，判断 $n$ 和 $m$ 分别是否是 $3$ 和 $2$ 的正整数次幂便可。
要注意的一点是 $\log_3n$ 应当大于等于 $\log_2m$。

------------
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+10;
int t,a,b,cnt; 
int is2[N],is3[N];
int gcd(int a,int b){
	if(b==0){
		return a;
	}
	else return gcd(b,a%b);
}
int main(){
	scanf("%d",&t);
	cnt=0;
	for(int i=1;i<=10000005;i*=2){
		is2[i]=++cnt;
	}
	cnt=0;
	for(int i=1;i<=10000005;i*=3){
		is3[i]=++cnt;
	}
	while(t--){
		scanf("%d%d",&a,&b);
		if(a<b){
			printf("NO\n");
			continue;
		}
		int l=gcd(a,b);
		a/=l;b/=l;
		if(is3[a]>=is2[b]&&is2[b]>0){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
} 
```


---

## 作者：aeiouaoeiu (赞：0)

首先发现当一个数 $x$ 能够被拆开，这个数必须是 $3$ 的倍数，且拆开的数一个是 $\dfrac13x$，一个是 $\dfrac23x$，所以一个数 $x$ 能被拆成 $\dfrac{2^t}{3^s}x$，其中 $t\le s$，则我们可以设 $n=3^px$，则我们要满足 $m=2^qx$ 并且有 $q\le p$，注意特判 $n=m$ 的情况即可，时间复杂度 $\mathcal{O}(t(\log_3n+\log_2m))$。
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
ll n,m,on,p,q;
string solve(void){
	if(n==m) return "Yes";
	if(n<m) return "No";
	on=n;
	for(p=0;n%3==0;n/=3,p++);
	if(m%n) return "No";
	m/=n;
	for(q=0;m%2==0;m/=2,q++);
	if(q>p||(on%m)) return "No";
	return "Yes";
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	ll T=1;
	cin>>T;
	for(;T--;){
		cin>>n>>m;
		cout<<solve()<<"\n";
	}
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1829D)       
很简单的 dfs 题。           
我们对于输入的 $n$ 和 $m$，有些情况可以直接判断：      
- $m>n$ 这种情况是 `NO`。     
- $n=m$ 这种情况是 `YES`。       
- $n≠m$ 且 $n\bmod 3≠0$ 这种情况是 `NO`。    

这三种情况我们直接判断即可。       
对于其他情况，我们进行 dfs。        
我们易知对于任何 $n(n\bmod 3=0)$ 都有且仅有一种分割的方法。          
所以我们进行分割，往下 dfs 即可。      
dfs 有三个终止条件，同上面的。           
[CODE](https://www.luogu.com.cn/paste/8gie26zu)

---

