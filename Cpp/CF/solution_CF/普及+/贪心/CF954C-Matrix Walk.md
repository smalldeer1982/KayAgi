# Matrix Walk

## 题目描述

## 【题目大意】

你有一个大小未知（假设为 $x\times y$）的矩阵，这个矩阵中的格子的编号的排列有规律，比如说 $(i,j)$ 号格子的编号为 $y\times (i - 1) + j$。  
但是现在这个矩阵的大小是未知的，我们的任务是算出来这个矩阵的**任意一种可能的大小**。  
接下来，你有一个长度为 $n$ 序列，表示你在矩阵中行动时走到的格子的编号。（你在矩阵中**只能上下左右行动，不能走出矩阵**） 如果说有符合这种序列的矩阵，那么输出 ```YES```，并输出矩阵的**任意一种可能的大小** ；否则输出 ```NO```。

## 说明/提示

$1 \le n\le 2 \times 10^5$，序列中任意的数字都小于等于 $10^9$，矩阵大小小于 $10 ^ 9\times 10^9$。

## 样例 #1

### 输入

```
8
1 2 3 6 9 8 5 2
```

### 输出

```
YES
3 3
```

## 样例 #2

### 输入

```
6
1 2 1 2 5 3
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
2
1 10
```

### 输出

```
YES
4 9
```

# 题解

## 作者：wmrqwq (赞：3)

本文同步在 [cnblog](https://www.cnblogs.com/wangmarui/p/18030366) 发布。

# 题目链接

[题目链接(CF)](https://codeforces.com/problemset/problem/954/C)

[题目链接(luogu)](https://www.luogu.com.cn/problem/CF954C)

# 题意简述

有一个 $n \times m$ 的矩阵，矩阵上的数字 $1 \sim n \times m$ 自上到下，自左到右，对于每次操作，你可以向上，下，左或右移动一步，你需要构造出符合操作序列的 $n$ 和 $m$ 或报告无解。

# 解题思路

容易证明，合法的操作序列相邻两项绝对值之差最后**最多**有**两种**取值，否则一定无解。

然后就可以直接模拟了，这题需要注意一些细节：

1. 对于相邻的两次操作，**一定**不能站在同一个格子上。

hackin：
```
3
1 2 2
```
hackout：
```
NO
```

2. 对于相邻的两次操作，编号相差 $1$ 的两个格子**不一定**能够互相到达。

hackin：
```
5
1 2 4 3 2
```
hackout：
```
NO
```

3. 向左走要注意减去列的长度

hackin：
```
8
1 2 3 2 3 4 3 8
```

hackout：
```
YES
1000000000
```

判掉了这几点，就能轻松 AC 了。

# 参考代码

```cpp
// LUOGU_RID: 148123666
/*
Tips:
你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
*/
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define ll long long
#define lcm(x,y) x/__gcd(x,y)*y
ll t;
void solve()
{
	ll n,pd=0,num=0,su=0,sum=0;
	cin>>n;
	ll a[n+10]={0};
	forl(i,1,n)
		cin>>a[i];
	forl(i,2,n)
	{
		if(abs(a[i]-a[i-1])==0)
		{
			su=0;
			cout<<"NO\n";
			return ;
		}
		if(abs(a[i]-a[i-1])>1)
		{
			su=0;
			if(pd && abs(a[i]-a[i-1])!=num)
			{
				cout<<"NO\n";
				return ;
			}
			else
				pd=1,num=abs(a[i]-a[i-1]);
		}
		if(abs(a[i]-a[i-1])==1)
			su+=a[i]-a[i-1];
		sum=max(su,sum);
	}
	if(pd)
	{
		if(num<sum)
			cout<<"NO\n";
		else
		{
			forl(i,2,n)
			{
				if(abs(a[i]-a[i-1])==1)
				{
					if(min(a[i],a[i-1])%num==0 && num!=1)
					{
						cout/*<<i*/<<"NO\n";
						return ;
					}
				}
			}
			cout<<"YES\n"<<1000000000<<' '<<num<<endl;
		}
	}
	else
		cout<<"YES\n"<<1000000000<<' '<<1000000000<<endl;
}
int main()
{
	IOS;
	t=1;
//	cin>>t;
	while(t--)
		solve();
    /******************/
	/*while(L<q[i].l) */
	/*    del(a[L++]);*/
	/*while(L>q[i].l) */
	/*    add(a[--L]);*/
	/*while(R<q[i].r) */
	/*	  add(a[++R]);*/
	/*while(R>q[i].r) */
	/*    del(a[R--]);*/
    /******************/
	QwQ;
}
```

---

## 作者：wuyixiang (赞：1)

题目大意：一个 $x \times y$ 的矩阵，第 $i$ 行 $j$ 列表示的数为 $(i - 1) \times y + j$。现在从一个点，有 $n$ 次行动，每次上下左右行走一格并记录走到的编号，问 $x$ 和 $y$ 可能是多少，没有输出 `NO`。

算法分析：这里分两种情况讨论。

$1.$ 相邻的两个格子走的编号差不为 $1$。这里就只有可能是上下走了，并可以得知有多少列。如果两次得出来的结果不符，输出 `NO`。

$2.$ 相邻的两个格子走的编号差为 $1$。这里只有左右跳或列为 $1$ 的情况上下跳。但是有一种情况不符：就是当列数 $\ge 2$ 时，从最左侧跳到最右侧或者最右侧跳到最左侧，此时很显然已经不是左右跳了，输出 `NO`。

$3.$ 相等。很显然不管往哪个方向跳都不能回到原点，输出 `NO`。

代码解读：这里献上作者极为丑陋的代码，仅做参考。

```cpp
#include <iostream>
#define int long long
using namespace std;
int n,x = 1e9,y = 0,r = 0,a[200005];//初值x可以设为无限大，因为行数没有直接关系
void rk()//输出NO函数
{
    cout << "NO";
    exit(0);
}
signed main()
{
    cin >> n >> a[1];
    for(int i = 2;i <= n;i ++)
    {
        cin >> a[i];
        if(abs(a[i - 1] - a[i]) > 1)
        {
            if(r == 0)r = 1,y = abs(a[i - 1] - a[i]);//记录列数，注意相差一定是>1的
            else
            {
                if(abs(a[i - 1] - a[i]) != y)rk();//如果两次不一样，直接输出NO
            }
        }
        else if(a[i - 1] == a[i])rk();//相等的情况
    }
    for(int i = 2;i <= n;i ++)
        if((r == 1 && ((a[i] % y == 1 && a[i - 1] % y == 0 && a[i - 1] < a[i]) || (a[i - 1] % y == 1 && a[i] % y == 0 && a[i - 1] > a[i]))))rk();//当列数被记录时，遇上两种不符的情况，输出NO
    if(y == 0)y = 1e9;//列数没有被记录默认为1e9
    cout << "YES\n" << x << " " << y;//如果全部满足，输出
}

---

## 作者：SamHJD (赞：1)

[题目传送](https://www.luogu.com.cn/problem/CF954C)

这道题细节比较多，~~调的我心态都快炸了~~。

**题目大意：**

你需要求出一个形如下图的矩阵：

```
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 16
```

给你一条路线，判断有没有一种矩阵满足，若有输出一种长与宽，否则输出没有。

**题目分析：**

首先可以简单的推出，这个矩阵的长与合不合法没有关系，因此长直接输出 ```1000000000``` 即可。

求出宽是本题重点，设宽为 $c$，我们可以从以下几个方面判断路线是否合法。

* 不难得出，同一列上下差都为 $c$，一条合法路线的其中一步只要不是左右走**必定两数差为 $c$**。

* **不能原地停留**，其中一步的两个数不能相同。

* **不能走出矩阵**，也就是若从 $u$ 走到 $v$，并且 $\dfrac{u-1}{c}\ne\dfrac{v-1}{c}$，这里是判断 $u$ 为这一行第 $c$ 个点 走到第 $c+1$ 个点。

$c$ 在代码开头就可以设初始值，只要路线其中两个数差不为 $1$，便把 $c$ 设为这个数。

注意还要判断 $c$ **不为 $0$**，要不然后面判断第三项时会报 ```Float Point Exception```。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,c=1,a[N],t=1;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%d",&a[i]);
        if(i>1 && a[i]==a[i-1]) t=0;//第二项
        if(i>1 && abs(a[i]-a[i-1])!=1 && a[i]!=a[i-1]) c=abs(a[i]-a[i-1]);//c设初始值
    }
    for(int i=2;i<=n;++i){
        if(abs(a[i]-a[i-1])!=1 && abs(a[i]-a[i-1])!=c) t=0;//第一项
        else if(abs(a[i]-a[i-1])==1 && c!=1 && (a[i]-1)/c!=(a[i-1]-1)/c) t=0;//第三项
    }
    if(!t) printf("NO");
    else printf("YES\n1000000000 %d",&c);//注意长不能超过1e9
    return 0;   
}
```


---

## 作者：qiliu (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/CF954C)

~~用手机写题解好难啊qwq~~

------------

### 题目大意：

给你一条路线，让你构造一个矩阵，是这条路线可以走的通。如果能走通，输出 ```YES``` 并输出矩阵的长和宽，否则输出 ```NO```。

矩阵形如下图：

```cpp
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 16
```


------------

### 题目思路：

我们先设一个变量 $y$ 表示列数。

首先，我们可以轻易地推出，矩阵的行数对于答案没有任何影响，所以我们先把行数设为 $ 10^9 $ 即可。而且，如果行数是 $10^9$ 的话，从数据来看，$a_i$ 无论怎么走都不可能越界，所以大可以直接抛弃判断走出矩阵的条件。

然后，我们可以发现，在同一行中移动时，$ a_{i} $ 和 $ a_{i-1} $ 差的绝对值必定为 $1$。而在同一列中移动时，$ a_{i} $ 和 $ a_{i-1} $ 差的绝对值必定为这个矩阵的列数。典型的例子是样例三：从 $ 1 $ 走到 $ 10 $ 所需要的列数是 $ 9 $，等于 $ \operatorname{abs} (10-1) $。证明十分简单，在此就不赘述了。

由此，我们可以得出三个非法的条件：

- $ \operatorname{abs} ( a_{i} -  a_{i-1} ) \neq 0$ 即不能在原地停留
- 若在不同行移动，则 $ \operatorname{abs} ( a_{i} - a_{i-1} ) = y $ 
- 另外还有一附加条件，判断是否串行，即如果 $ \frac{ a_{i} -1 }{y} \neq  \frac{ a_{i-1} -1 }{y} $ 且 $y \neq 1$ 那么就会NO。

于是，正解便呼之欲出。

注：由于篇幅原因，此处无法展开太多证明，请移步 ```code``` 处见详细证明。

------------
### AC Code

```c
#include<bits/stdc++.h>
#define int long long
#define DEBUG(x) cerr<<#x<<'='<<x<<endl
using namespace std;
int a[400005];
int ans=0;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    int n;
    cin>>n;
    int y=1;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    	if(i>1)
    	{
    		if(a[i]==a[i-1])//条件一
    		{
    			cout<<"NO";
    			return 0;
			}
			if(abs(a[i]-a[i-1])!=1)
			{
				y=abs(a[i]-a[i-1]);//这里我们直接赋值，在我们后面判条件二的时候就能一块判出来。
			}
		}
	}
	for(int i=2;i<=n;i++)
	{
		if(abs(a[i]-a[i-1])!=1&&abs(a[i]-a[i-1])!=y)//条件2
		{
			cout<<"NO";
			return 0;
		}
		if(abs(a[i]-a[i-1])==1&&y!=1&&(a[i]-1)/y!=(a[i-1]-1)/y)//条件3
        //注意这个算式算出来的是整形，代表的应当是a[i]和a[i-1]的行数。减一的话，可以试试手算一下 5 1 4 7 8 9 这个数据，就能明白。（7 8 9应当在一行，但由于下取整的原因，直接除判不到，因此要减一。）
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES"<<endl<<1000000000<<' '<<y;
    //fclose(stdin);
    //fclose(stdout);
	return 0;
}

```


---

## 作者：Hot_tear (赞：0)

题意不再赘述

考虑模拟，如果说 $|a_i-a_{i-1}|\not=1$ 那么这说明一个合法的序列当且仅当一行有 $|a_i-a_{i-1}|$ 个元素才合法，知道了一行有多少个元素之后，很显然最小的满足要求的行数就是 $\lceil\dfrac{a_i}{p}\rceil$ 其中 $p$ 是列数，即一行有多少个元素，对于 $\forall i\in [2,n]$ 来说，当且仅当 $|a_i-a_{i-1}|=1\land |a_i-a_{i-1}|=p$ 才合法

细节 tips：

1. $p$ 作为列数，显然因为一行中的元素可以左右移动，所以显然有 $p\not=1$
2. 若 $\forall i\in[1,n],|a_i-a_{i-1}|=1$ ，即 $p$ 只能取 1，那么输出一个行数无限大，列数为 1 的矩阵即可
3. 如果说 $\exist\ i\in[1,n],(p|a_i\wedge p|(a_{i+1}-1))\land(p|(a_i-1)\wedge p|a_{i+1})$ ，那么这个时候说明从一行末尾/开头转向了一行的开头/末尾，这个时候是不合法的
4. 如果 $\exist \ i\in[2,n],a_i=a_{i-1}$ ，那么这个时候无论怎么走都不可能留在原地，那么此数据即为不合法

After_light's Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for(ll i=a;i<=b;i++)
#define R(i,a,b) for(ll i=a;i>=b;i--)
#define sc(a) scanf("%lld",&a)
#define ps(a) printf("%lld ",a)
#define pn(a) printf("%lld\n",a)
using namespace std;
const ll N=3e6+7;
ll n,a[N],p,mn;
int main(){
	sc(n);
	F(i,1,n) sc(a[i]);
	if(n==1){
		puts("YES");
		ps(1ll);
		pn(a[1]);
		return 0;
	}
	F(i,2,n){
		if(labs(a[i]-a[i-1])==0){
			p=-1;
			break;
		}
		if(labs(a[i]-a[i-1])>1ll){
			p=labs(a[i]-a[i-1]);
			break;
		}
		if(labs(a[i]-a[i-1])==1ll){
			p=-2;
			continue;
		}
	}
	if(p==-2){
		puts("YES");
		ps(1000000000ll);
		pn(1ll);
		return 0;
	}
	if(p==-1){
		puts("NO");
		return 0;
	}
	if(!p){
		puts("NO");
		return 0;
	}
	F(i,1,n){
		mn=max(mn,a[i]/p+(a[i]%p!=0ll));
		if(i==1) continue;
		ll k=min(a[i],a[i-1]),f=max(a[i],a[i-1]);
		if(k-f==-1ll&&((k%p==0)&&(f%p==1))){
			puts("NO");
			return 0;
		}
		if(labs(a[i]-a[i-1])==1ll||labs(a[i]-a[i-1])==p){
			continue;
		}
		puts("NO");
		return 0;
	}
	puts("YES");
	ps(mn),pn(p);
	return 0;
}

```

---

## 作者：流绪 (赞：0)

首先我们可以发现上下两行的差为矩阵的列数,然后可以发现矩阵太大是没有关系的,因为只要输出任意符合题意的答案,那么我们可以考虑将矩行的一边设置为最大可能值 1e9 ,然后只要求另外一边即可

另外一边怎么求呢?
我们知道他的移动要么是左右移动要么是上下移动,左右移动的话 d=1 ,前面说到上下两行的差就是矩阵的列数,那么我们就知道了上下移动的距离就是矩形的边长了,答案就出来了,接下来只要特判不能构成的情况,这些情况我在代码里注释了

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#define maxn 1000010
using namespace std;
int a[maxn];
int main()
{
	ios::sync_with_stdio(false);
    int n;
	cin>>n;
	int y=1;
	cin >> a[1];
	int flag = 1;
	for(int i=2;i<=n;i++)
	{
		cin >> a[i];
		if(a[i]==a[i-1])
			flag = 0;//不能再同一格不动 
		if(abs(a[i]-a[i-1])!=1)
			y=abs(a[i]-a[i-1]));
	}
	for(int i=2;i<=n;i++)
	{
		if(abs(a[i]-a[i-1])!=1&&abs(a[i]-a[i-1])!=y)
			flag = 0;//距离不为 1 的走必须是相邻的两行 
		else if(y!=1&&abs(a[i]-a[i-1])==1&&(a[i-1]-1)/y!=(a[i]-1)/y)
			flag = 0;//同一行才能距离为 1 地走 
	}
	if(!flag)
		cout <<"NO";
	else
		cout <<"YES\n1000000000 " << y ;
}
```


---

## 作者：codeLJH114514 (赞：0)

[Problem](https://www.luogu.com.cn/problem/CF954C)

# Problem #

有一个矩阵，大小未知，假设大小是 $a_1$ 行 $a_2$ 列，定义一个坐标 $(t_1,t_2)$ 的编号为 $a_2 \times (t_1 - 1) + t_2$；

给定一串长度为 $u_1$ 的序列 $\{v_1, \ldots,v_{u_1}\}$，这个序列中的每一个元素都是一个位置的编号。

你需要确定一对 $(a_1, a_2)$，使得在这个矩阵内编号为 $v_i(1 \le i \le u_1)$ 的坐标存在并且编号为 $v_j(2 \le j \le u_1)$ 的坐标与编号为 $v_{j - 1}$ 的坐标相邻。

$(t_1, t_2)$ 和 $(t_3, t_4)$ 这两个坐标相邻当且仅当 $(t_4 = t_2 \land |t_3 - t_1| = 1) \lor (t_1 = t_3 \land |t_4 - t_2| = 1)$。

# Analysis #

显然，$a_1$ 对于这些编号**毫无影响**，由于输出任何一个都行，所以我们直接让 $a_1 = 10^9$。（因为这样能覆盖更多的编号）

定义 $C$ 就是当前的 $a_2$，最开始把它设成特殊值（比如 $10^9 + 1$）。

首先，扫一遍 $v$ 序列，如果 $|v_i - v_{i - 1}| \neq 1$，那么就把 $C$ 设成 $|v_i - v_{i - 1}|$，如果 $C$ 不是特殊值并且不是 $|v_i - v_{i - 1}|$，直接无解。（因为如果 $|v_i - v_{i - 1}| \neq 1$，那么就相当于换了一行，换了一行编号一定会加 $a_2$ 或减 $a_2$）

然后对于每一个 $|v_i - v_{i - 1}| = 1$ 再判断，如果更小的那个编号是 $C$ 的倍数，那么也无解。（因为如果更小的那个编号是 $C$ 的倍数，就相当于从一行的末尾跳到了下一行的开头，显然不行）

如果直到最后 $C$ 还是等于最开始的特殊值，那么就说明没有跳行操作，直接把 $C$ 设成 $10^9$。

最后如果没无解就输出 $(10^9, C)$。

还有要特判一下 $v_i = v_{i - 1}$ 的情况。（不然会 RE）

# Coding #

```cpp
#include <iostream>
#include <vector>
#include <cmath>
int n, xval;
std::vector<int> vec;
int Column;
const int infinity = 1000000001;
bool Xolved() {
	Column = infinity;
	for (int i = 1; i < vec.size(); i++) {
		if (vec[i - 1] == vec[i])
			return false;
		if (vec[i] > vec[i - 1]) {
			if (vec[i] != vec[i - 1] + 1)
				if (Column == infinity)
					Column = vec[i] - vec[i - 1];
				else if (Column != vec[i] - vec[i - 1])
					return false;
		} else {
			if (vec[i] != vec[i - 1] - 1)
				if (Column == infinity)
					Column = vec[i - 1] - vec[i];
				else if (Column != vec[i - 1] - vec[i])
					return false;
		}
	}
	for (int i = 1; i < vec.size(); i++)
		if (vec[i] > vec[i - 1]) {
			if (vec[i] == vec[i - 1] + 1)
				if (vec[i - 1] % Column == 0)
					return false;
		} else {
			if (vec[i] == vec[i - 1] - 1)
				if (vec[i] % Column == 0)
					return false;
		}
	if (Column == infinity)
		Column -= 1;
	return true;
}
int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> xval, vec.push_back(xval);
	bool x = Xolved();
	std::cout << (x ? "YES" : "NO") << std::endl;
	if (x) std::cout << infinity - 1 << " " << Column;
	return 0;
}
```

---

## 作者：hubin1 (赞：0)

# Matrix Walk

## 题目大意

给定一个矩阵和一条线路，矩阵的长和宽不确定。问这条线路能否在这个矩阵中合法行走，合法行走指只能上、下、左、右行走。

这个矩阵满足特定条件，编号为 $i,j$ 的点的值为 $y \times (i-1) + j$，其中 $y$ 是这个矩阵的列数。

矩阵类似于：

```
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
```

## 思路

1. 对于一个合法的矩阵，我们令 $x$ 为这个矩阵的行数，$y$ 为这个矩阵的列数。可以发现，$x$ 只要一直够大，就符合题意。因此我们直接让 $x$ 为矩阵行数的最大值 $10^9$。

2. 而 $y$ 的值非常关键，会根据线路而改变。因此先判断这个线路是否合法。

   1. 对于一个合法线路，如果某一步是左、右移动，那么它们的差一定是 $1$；如果不是 $1$，那么它们的差值就一定是列数。如果有一个线路，它存在多个差值都不为 $1$、但互不相同的情况，那么这个线路就是不合法的。
   2. 在原地停留也是不合法的，即如果 $a_i=a_{i-1}$，同时 $i\neq 1$。
   3. 还有一种情况，$a_i$ 和 $a_{i-1}$ 的差也是 $1$，但依旧不能走到，这种情况就是**换行**的情况。因此要判断这种情况，即 $\lfloor \frac{a_i-1}{t} \rfloor\neq \lfloor \frac{a_{i-1}-1}{t} \rfloor$，其中 $t$ 是 通过第一步得到的列数。这里为什么减一呢？是为了防止一个数是 $t$ 的倍数，但它旁边的一个并不是，这种情况程序认为走不到，但实际上向右走一步可以到。

## Code
``` cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define debug(x) cerr<<#x<<"="<<x<<"\n"

const int MAX=2e5+10;
const int MAXX=1e9;
int a[MAX];

int main()
{
	int n;
	int t=1;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==a[i-1]&&i!=1)//原地等待，即条件2
		{
			cout<<"NO"<<endl;
			return 0;
		}
		else if(abs(a[i]-a[i-1])!=1&&i!=1)
			t=abs(a[i]-a[i-1]);//预处理列数
	}
	for(int i=2;i<=n;i++)//从2开始
	{
		if(abs(a[i]-a[i-1])!=1&&abs(a[i]-a[i-1])!=t)//有多个差值不等于1但互不相同，条件1
		{
			cout<<"NO"<<endl;
			return 0;
		}
		else if(abs(a[i]-a[i-1])==1&&t!=1&&((a[i]-1)/t!=(a[i-1]-1)/t))//条件3，换行情况
		{
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES"<<endl;
	cout<<MAXX<<" "<<t<<endl;
	//MAXX=1e9
	return 0;
}
```

---

