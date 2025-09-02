# Round Table Knights

## 题目描述

There are $ n $ knights sitting at the Round Table at an equal distance from each other. Each of them is either in a good or in a bad mood.

Merlin, the wizard predicted to King Arthur that the next month will turn out to be particularly fortunate if the regular polygon can be found. On all vertices of the polygon knights in a good mood should be located. Otherwise, the next month will bring misfortunes.

A convex polygon is regular if all its sides have same length and all his angles are equal. In this problem we consider only regular polygons with at least 3 vertices, i. e. only nondegenerated.

On a picture below some examples of such polygons are present. Green points mean knights in a good mood. Red points mean ones in a bad mood.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF71C/05771d25f3570e788948383d5e55e90ca186c9da.png)King Arthur knows the knights' moods. Help him find out if the next month will be fortunate or not.

## 样例 #1

### 输入

```
3
1 1 1
```

### 输出

```
YES```

## 样例 #2

### 输入

```
6
1 0 1 1 1 0
```

### 输出

```
YES```

## 样例 #3

### 输入

```
6
1 0 0 1 0 1
```

### 输出

```
NO```

# 题解

## 作者：AKPC (赞：3)

### 思路
有 $n$ 个点，显然对于任意的 $x$，只有在 $x\mid n$ 的时候才有可能形成正 $x$ 边形，反之就算每个点都是 $1$ 也无法形成。所以在枚举 $x$ 的时候可以只计算 $n$ 的所有 $\leq \sqrt{n}$ 的因子。

判断 $x\mid n$ 之后，直接暴力判断是否可以形成 $x$ 边形，即是否有可能每隔 $\dfrac{n}{x}$ 个格子都会是 $1$。如果可以就直接输出 `YES`，如果所有 $n$ 的因子都不行就输出 `NO`。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int ok(int x,int y){
	for (int i=x;i<=n;i+=y) if (a[i]==0) return 0;
	return 1;
}
int check(int x){
	for (int i=1;i<=n/x;i++) if (ok(i,n/x)) return 1;
	return 0;
}
signed main(){
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i*i<=n;i++)
		if (n%i==0&&((check(i)&&i!=1&&i!=2)||(check(n/i)&&n/i!=1&&n/i!=2))){
			cout<<"YES";
			return 0;
		}
	cout<<"NO";
	return 0;
}
```


---

## 作者：封禁用户 (赞：2)

## CF71C Round Table Knights 题解
### 解题思路
首先，我们先不考虑骑士的编号，先确定 $n$ 个点能生成几种正多边形。例如：

- 当 $n = 6$ 时：可以生成正三角形和正六边形。
- 当 $n = 12$ 时：可以生成正三角形，正四边形，正六边形和正十二边形。
- 当 $n = 23$ 时：只能生成正二十三边形。

所以我们先确定枚举哪几种正多边形，也就是 $n$ 的所有因数，可以有效降低时间复杂度。因为我们枚举 $n$ 的因数个数只需要枚举到 $\sqrt{n}$，即 $n$ 的因数个数不会超过 $2\sqrt{n}$ 个。所以，枚举时，复杂度就降为了 $O(n\sqrt{n})$，可以通过此题了。

而我们剩下需要做的就是枚举在 $n$ 的每一种情况下，能不能连出一个正多边形。所有因数中只要有至少一个能连成，输出：“YES”，否则输出：“NO”。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool a[200005];
bool flag = 1; 
bool check(int t)
{
	bool tmp;
	for(int i = 1 ; i <= t ; i++)
	{
		tmp = 1;
		for(int j = 0 ; j < n ; j += t)
		{
			if(!a[i + j])
			{
				tmp = 0;
			}
		}
		if(tmp)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	cin >> n;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> a[i];
	}
	for(int i = 1 ; i <= n ; i++)
	{
		a[n + 1] = a[i];
	}
	for(int i = 1 ; i + i < n ; i++)
	{
		if(n % i == 0)
		{
			if(check(i))
			{
				flag = 0;
			}
		}
	}
	if(flag)
	{
		cout << "NO";
		return 0;
	}
	cout << "YES";
	return 0;
}
```

---

## 作者：lightningZ (赞：2)

## 思路
首先我们需要意识到**不一定所有的多边形都能构成**，比如说 $10$ 个点就不可能生成正三角形。所以我们假设有 $n$ 个点，那么就只可能生成 $n$ 的约数的正多边形，用 $O(\sqrt{n})$ 的复杂度判断。

其次就是判断多边形时只需要判断顶点之间的**距离是否相等**就可以判断是否为 _正_ 多边形，然后用 $O(n)$ 的复杂度去判断是否可行，总复杂度 $O(n \sqrt{n})$

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005];
int ZDX(int x,int y)//判断能否生成
{
	for(int i=x;i<=n;i+=y)
	{
		if(a[i]==0) return false;
	}
	return true;
}
int zdx(int x)//判断是几边形
{
	for(int i=1;i<=n/x;i++)
	{
		if(ZDX(i,n/x)) return true;
	}
	return false;
}
signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i*i<=n;i++)
	{
		if(n%i==0)//判断能否生成正多边形
		{
			if(zdx(i)&&i!=1&&i!=2)//特判1,2
			{
				printf("YES");
				return 0;
			}
			if(zdx(n/i)&&n/i!=1&&n/i!=2) 
			{
				printf("YES");
				return 0;
			}
		}
	}
	printf("NO");
	return 0; 
}
```


---

## 作者：qingchenMC (赞：0)

## 思路

注意到如果要形成正多边形，每两个顶点之间相隔的点数必须要是一样的。

我们设每两个顶点之间隔了 $x-1$ 个点，而构成的是正 $k$ 边形。

则会有：$kx=n$。于是我们就可以枚举 $n$ 的所有因子来得到可能的 $k$，时间复杂度为 $O(\sqrt{n})$。

**这里注意：循环的变量是小于等于 $\sqrt{n}$ 的，所以我们还要考虑 $\frac{n}{i}$ 的情况。**

知道了 $k$ 之后，我们可以用 $\frac{n}{k}$ 来得到 $x$，然后枚举所有可能的起点，时间复杂度为 $O(x)$，再去检查每一个顶点是否都为 $1$，时间复杂度为 $O(\frac{n}{x})$，所以这一步的时间复杂度为 $O(n)$。

综合这两步，可得此算法时间复杂度为 $O(n\sqrt{n})$，结合数据范围 $n\le10^5$ 可知该算法可以通过此题。

## 代码

```cpp
#include<bits/stdc++.h> 
 
using namespace std;
 
int c[100002];
 
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	for(int i=1;i*i<=n;i++){//枚举周期长度。 
		if(n%i==0){
			if(i>2){
				int x=n/i;
				for(int j=1;j<=x;j++){//枚举起点，在一个长度为x的循环周期内。 
					bool flag=1;
					for(int k=j;k<=n;k+=x){//枚举每一个顶点。 
						if(!c[k]){
							flag=0;
							break;
						}
					}
					if(flag){
						cout<<"YES";
						return 0;
					}
				}
			}
			if(n/i>2){//和上面的一样。
				int x=i;
				for(int j=1;j<=x;j++){
					bool flag=1;
					for(int k=j;k<=n;k+=x){
						if(!c[k]){
							flag=0;
							break;
						}
					}
					if(flag){
						cout<<"YES";
						return 0;
					}
				}
			}
		}
	}
	cout<<"NO";
	return 0;
}
```

---

## 作者：zym20249_ (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF71C)

## 题意
有 $n$ 个点围成一个圆，每个点的距离相等。每个点对应的不是 $1$ 就是 $0$，请问能否连接若干个 $1$，使得所连成的图形是正多边形？

## 思路
这个题可以简单的理解为每隔 $x$ 个点是否可以可以构成一个正多边形，所以我们可以简单地暴力枚举，从一个为 $1$ 的点出发查看隔了 $x$ 点以后是否同时为 $1$。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
bool flag=false;
int n,i,j,d,a[N];
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	for(d=1;d<n/2;d++)
	{
		if(n%d!=0) continue;
		if(flag) break;
		for(i=1;i<=d;i++)
		{
			if(flag) break;
			if(a[i]!=1) continue;
			bool f=1;
			int p=i;
			for(j=1;j<n/d;j++)
			{
				p+=d;
				if(a[p]==0)
				{
					f=0;
					break;
				}
			}
			if(f) flag=1;
		}

	}
	if(n==3&&(a[1]+a[2]+a[3]==3))flag=1;
	if(flag) cout<<"YES";
	else cout<<"NO";
	return 0;
 } 
```

---

## 作者：卷王 (赞：0)

[更好的阅读体验](https://blog.csdn.net/juan_wang123/article/details/139086893?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22139086893%22%2C%22source%22%3A%22juan_wang123%22%7D)

这是一道简单模拟题。

我们要让选的 $1$ 之间的距离相等，显然有一个性质：点数被距离整除。那么我们就可以用 $O(\sqrt{n})$ 的复杂度枚举每一个距离。对于每一个距离 $x$，进行以下两种判断：
* 按照距离为 $x$ 的情况，模拟，如果符合要求，输出 `YES`。
* 按照距离为 $n \div x$ 的情况，模拟，如果符合要求，输出 `YES`。

如果全部枚举完了，还没有满足要求，输出 `NO`。

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(i, l, r) for(int i = (l); i <= (r); i++)
#define down(i, r, l) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
int a[1000007];
int dp[1000007];

inline bool jud(int x, int y) {
	for(int i = x; i <= n; i += y) {
		if(a[i] == 0) return 0;
	}
	return 1;
}
inline bool check(int x) {
	for(int i = 1; i <= n / x; i++) {
		if(jud(i, n / x)) return 1;
	}
	return 0;
}

signed main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		a[i] = read();
		a[i + n] = a[i];
	}
	for(int i = 1; i * i <= n; i++) {
		if(n % i == 0) {
			if(check(i) && i >= 3) {
				cout << "YES";
				return 0;
			}
			if(check(n / i) && n / i >= 3) {
				cout << "YES";
				return 0;
			}
		}
	}
	cout << "NO";
	return 0;
}
```

---

## 作者：liuli688 (赞：0)

### 思路：
观察可得想要形成正 $e$ 边形，$n$ 必须是 $e$ 的倍数。所以，我们可以从 $3$ 枚举到 $\sqrt n$（没有正 $1,2$ 边形，由于因数是成对出现的所以可以只枚举 $\sqrt n$ 个，但对于每一个数要判断两遍），如果通过因数判断 $e$ 满足要求，则进行如下操作：

我们再用一个循环，以每一个在 $[1,\frac n e]$ 区间里的数作为正 $e$ 边形的一个端点，暴力判断以这个点作为一个端点的正 $e$ 边形的每一个端点是否都是 $1$。判断的伪代码如下：
```
function check(integer x)
	boolean flag.
	for i := 1 to n/x
		flag := true.
		for j := i to n,j := j + n/x
			if a_j = 0
				flag := false.
				break.
			if flag
				return true.
	return false.
for i := 1 to sqrt(n)
	if n mod i = 0 and ((check(i) and i != 1 and i != 2) or (check(n/i) and n/i != 1 and n/i != 2))
		output a string "YES".
		end.
output a string "NO".
end.
(a is knight array.)
```
### 代码：
```cpp
#define speedup ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define namesp using namespace std

#include <bits/stdc++.h>
namesp;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;

const int INF = INT_MAX;
const int UINF = INT_MIN;
const ll LINF = LONG_LONG_MAX;
const ll ULINF = LONG_LONG_MIN;

#define fp(i,a,b) for (i = a;i < b;i++)
#define fm(i,a,b) for (i = a;i > b;i--)
#define fl(i,a,b) for (i = a;i <= b;i++)
#define fg(i,a,b) for (i = a;i >= b;i--)
#define bk break
#define ctn continue
#define reg register

#define freo(n, m) freopen(n, "r", stdin), freopen(m, "w", stdout)
#define frec(n) fclose(stdin), fclose(stdout)

#define mp make_pair
#define fir first
#define sec second

#define pb push_back
#define pf push_front

const int MAX  = 1e5 + 1;
int n,a[MAX],sq;

bool check(int x)//检查正 e 边形是否符合条件
{
    reg int i,j;
    reg bool flag;
    const int tmp = n / x;//省时间（除法很慢）
    fl(i,1,n / x)//依次尝试以每一个在 [1，n/e] 区间里的数作为正 e 边形的一个端点
    {
        flag = true;//标记
        for(j = i;j <= n;j += tmp)//暴力判断以这个点作为一个端点的正 e 边形的每一个端点是否都是 1
            if(!a[j])//如果有一个为 0
            {
                flag = false;//这次尝试失败
                bk;
            }
        if(flag)//如果可以
            return true;
    }
    return false;
}

bool ex(int n)//特判 1 和 2，因为没有正 1 边形和正 2 边形
{
    return n != 1 && n != 2;
}

signed main()
{
    speedup;
    reg int i;
    cin >> n;
    sq = sqrt(n);
    fl(i,1,n)
        cin >> a[i];
    fl(i,1,sq)
        if(!(n % i) && ((check(i) && ex(i)) || (check(n / i) && ex(n/i))))//依次对两种边长进行尝试
        {
            cout << "YES";
            return 0;
        }
    cout << "NO";
    return 0;
}
```

---

## 作者：zsyyyy (赞：0)

# CF71C 数学

## 题意

有 $n$ 个骑士坐在一张圆桌旁，每位骑士的距离相等。

每个骑士对应都有一个编号，不是 $1$ 就是 $0$，请问能否用若干个 $1$，将它们分别对应的点连在一起，使得所连成的图形是正多边形？


## 思路

先破环为列。显然多边形的边数必须是 $n$ 的因数。假设找出了因数 $x$，将 $x$ 作为多边形的边数，然后枚举所有为 $1$ 的骑士作为起始点，确定一个起始点后，每次看之后 $k$ 个的骑士是否为 $1$，如果全部都是，就找到了一种方法，否则就继续找。

特判：如果所有骑士都为 $1$ 的情况，边数为 $n$ 时一定可以。

时间复杂度：$O(n\sqrt{n})$


## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+10;
int n,a[2*MAXN],sn,i;
bool flag,f;
bool check(int x)
{
	if(n/(x*2)<=2)  return false; //正多边形边数必须大于2
	for(int i=1;i<n/2;i++)
	{
		if(a[i])
		{
			f=0;
			for(int j=i;j<=n;j+=x)
			{
				if(!a[j])
				{
					f=1;
					break;	
				}
			}
			if(!f)  return true;
		}
	}
	return false;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++)  //特判全部为1的情况
	{
		if(!a[i])  flag=1;
	}
	if(!flag)
	{
		puts("YES");
		return 0;
	}
	for(int i=n+1;i<=2*n;i++)  a[i]=a[i-n];
	n*=2; //破环为列
	sn=sqrt(n);
	for(int i=3;i<=sn;i++)
	{
		if(n%i==0) //找到因数
		{
			if(check(i))
			{
				puts("YES");
				return 0;
			}
			if(check(n/i))
			{
				puts("YES");
				return 0;
			}
		}
	}
	if(check(2)) //特判
	{
		puts("YES");
		return 0;
	}
	puts("NO");
	return 0;
}
```


---

## 作者：Need_No_Name (赞：0)

# Solution for CF71C

## 题意

给定一个环，环上有 $n$ 个节点，节点上数为 $0$ 或 $1$ ,先要在环中选取若干节点使得这些节点形成一个正多边形（也就是节点之间的距离相等），且这些节点的数字必须为 $1$ 。先要判断是否存在此多边形。

## 思路

我们可以考虑去暴力枚举

我们需要去枚举以下因素：1.正多边形的边数 2.正多边形起点 3.是否可行

对于边数的因素，我们只需从 $3$ 到 $n$ 去枚举边数，需要判断是否边数是 $n$ 的约数即可

其它的因素来说，便没有难度可言了。从 $1$ 到 $n$ 不断枚举，发现不可行便 ```break``` 掉即可。

## 代码

```cpp
# include <bits/stdc++.h>
# define int long long
using namespace std;
const int N = 2e5 + 10;
int n;
int a[N];
signed main()
{
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = n + 1; i <= 2 * n; i++) a[i] = a[i - n];
	for(int i = 3; i <= n; i++)
	{
		if(n % i != 0) continue;
		else
		{
			bool flag = false;
			int step = n / i;
			for(int j = 1; j <= n; j++)
			{
				flag = false;
				int num = 1;
				for(int k = j; k; k += step)
				{
					if(a[k] == 0)
					{
						flag = true;
						break;
					}
					if(num == i) break;
					num++;
				}
				if(flag == false)
				{
					cout << "YES" << endl;
					return 0;
				}
			}
		}
	}
	cout << "NO" << endl;
	return 0;
}
```



---

