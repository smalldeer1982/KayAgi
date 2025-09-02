# StORage room

## 题目描述

In Cyprus, the weather is pretty hot. Thus, Theofanis saw this as an opportunity to create an ice cream company.

He keeps the ice cream safe from other ice cream producers by locking it inside big storage rooms. However, he forgot the password. Luckily, the lock has a special feature for forgetful people!

It gives you a table $ M $ with $ n $ rows and $ n $ columns of non-negative integers, and to open the lock, you need to find an array $ a $ of $ n $ elements such that:

- $ 0 \le a_i < 2^{30} $ , and
- $ M_{i,j} = a_i | a_j $ for all $ i \neq j $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR).

The lock has a bug, and sometimes it gives tables without any solutions. In that case, the ice cream will remain frozen for the rest of eternity.

Can you find an array to open the lock?

## 样例 #1

### 输入

```
4
1
0
4
0 3 3 5
3 0 3 7
3 3 0 7
5 7 7 0
5
0 7 7 5 5
7 0 3 2 6
7 3 0 3 7
5 2 3 0 4
5 6 7 4 0
3
0 0 1
0 0 0
1 0 0```

### 输出

```
YES
7
YES
1 3 2 5 
YES
5 2 3 0 4
NO```

# 题解

## 作者：引领天下 (赞：8)

题意：

给出一个矩阵 $M$，问是否能构造数列 $a$，满足对 $\forall i,j\le n$，均有 $M_{i,j}=a_i \operatorname{OR} a_j$，其中 $\operatorname{OR}$ 为按位或操作。

做法：

按位或其实是一个挺强的限制条件，他相当于得到了如果 $M_{i,j}$ 中某个二进制位是 0，则 $a_i,a_j$ 中该位都得是 0。

至于 $M_{i,j}$ 中是 1 的二进制位，我们令 $a_i,a_j$ 该位都是 1，这样在处理其他的 $M_{i,j}$ 的时候，利用上面的限制条件去看他能否保住。

整个矩阵做完之后，得到了所有限制条件都满足的 $a_i$，然后依次判断 $a_i \operatorname{OR} a_j$ 是否等于 $M_{i,j}$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,m[1003][1003];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        if(n==1){
            cin>>m[0][0];
            cout<<"YES"<<'\n'<<0<<'\n';
            continue;
        }
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)cin>>m[i][j];
        vector<int>ans(n);
        for(int i=0;i<n;i++){
            ans[i]=0x7fffffff;
            for(int j=0;j<n;j++)if(i!=j)ans[i]&=m[i][j];
        }
        bool flag=1;
        for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)if(i!=j)flag&=(ans[i]|ans[j])==m[i][j];
        if(flag){
            cout<<"YES"<<'\n';
            for(int i=0;i<n;i++)cout<<ans[i]<<' ';
            cout<<'\n';
        }
        else cout<<"NO"<<'\n';
    }
    return 0;
}
```

---

## 作者：wanglexi (赞：4)

### 解法
首先我们看一下按位或对数的限制。

$a_i|a_j=M_{i,j}$ 是题目中给出的条件。如果 $M_{i,j}$ 的某一个二进制位上是 $0$，那么 $a_i$ **和** $a_j$ 这一位上也应该是 $0$；如果 $M_{i,j}$ 的某一个二进制位上是 $1$，那么 $a_i$ 和 $a_j$ 中**至少有一个**这一位上是 $1$。显然，按位或的位上是 $0$ 的限制更大，所以先处理 $0$ 的情况。

如果 $a_i$ 和其他任意一个数按位或的某一位是 $0$，那么 $a_i$ 的这个位就一定是 $0$。“任意一位是 $0$，那么就是 $0$”，也就是说，$a_i$的所有 $1$，$M_{i,1},M_{i,2}\dots M_{i,n}$ **按位与**的结果的对应位置上也应该是 $1$。

接下来看 $1$ 的情况。首先易见，这些数的 $1$ 越多，越容易满足条件。

所以，让 $a_i$就等于所有满足 $1\le j\le n$ 且 $i\ne j$ 的 $M_{i,j}$ 全部按位与的结果。最后，看现在这样构造出来的数列 $a$ 是否满足矩阵 $M$ 的限制。

### AC 代码

两点要注意：

- 因为要按位与，所以 $a_i$ 的初始值要初始为 $2^{30}-1$（二进制下的 $(111111\dots1)_2$）

- 无论是前面构造还是后面判断，都要注意排除 $i=j$ 的情况。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
int t,n,a[1005],m[1005][1005],flag;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			a[i]=(1<<30)-1;
			for(int j=1;j<=n;j++){
				cin>>m[i][j];
				if(i!=j)a[i]&=m[i][j];
			}
		}
		flag=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i!=j&&(a[i]|a[j])!=m[i][j])flag=0,i=n+1,j=n+1;//退出循环
			}
		}
		if(flag==1){
			cout<<"YES\n";
			for(int i=1;i<=n;i++)cout<<a[i]<<" ";
			cout<<"\n";
		}
		else{
			cout<<"NO\n";
		}
	}
	return 0;
}

```

---

## 作者：vectorxyz (赞：1)

思维构造题。

题目中说 $a_i \operatorname{or} a_j=M_{i,j}$，我们不妨逆向思维一下，将 $a_i$ 和 $a_j$ 分别处理一下，然后最后再判断是否合法，这样，我们就得到这题的最优解。

展开说，如果行列不重复的话，将 $a_i \operatorname{or} b_{i,j}$ 存入 $a_i$，但是，我们这里考虑反着的，所以把或改成与，$a_j$ 同理，最后判断一下 $a_i \operatorname{or} a_j$ 是否不等于 $b_{i,j}$ 即可。

##### 代码片段：

```cpp
for(int i = 0; i < n; i++){
   for(int j = 0; j < n; j++){
      int x;
      cin >> x;
      b[i][j] = x; 
      if (i != j){  //主要操作，说明如上
      	a[i] &= x;
      	a[j] &= x;
      }
   }
}
```

---

## 作者：BugGod (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1903B)

首先我们考虑按位或的性质。假设我们现在有 $a_i$，由于或运算的性质，如果 $a_i$ 二进制下的第 $j$ 位为 $1$，那么 $M_{i,k}(1\le k\le n,k\neq i)$ 的第 $j$ 位一定也为 $1$（因为 $1$ 或什么数 都是 $1$），所以如果 $M_{i,k}$ 中有一个数第 $j$ 位为 $0$，那么 $a_i$ 这一位一定也为 $0$。

初始化 $a_i$ 为 $2^{30}-1$，因为题目要求 $0\le a_i<2^{30}$，并且 $0\le M_{i,j}<2^{30}$，我们让 $a_i$ 在尽可能大的情况下全为 $1$，便于更改。

警示后人：

1. 不要把 $a_i$ 初始化为 $2^{31}-1$，会超出值域 WA。
1. C++ 中按位或的优先级比不等于小，如果你和我是一个写法，请带括号。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
struct matrix
{
	int a[1010][1010];
	matrix()
	{
		memset(a,0,sizeof(a));
	}
	int n,m;
}mat;
int t,n,b[1010];
void solve()
{
	cin>>n;
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)cin>>mat.a[i][j];
	}
	for(int i=1;i<=n;i++)b[i]=1073741823;//初始化
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i!=j)
			{
				b[i]=b[i]&mat.a[i][j];//由于与的性质，只要某个数这一位为0，b[i]这一位就一定为0
			}
		}
	}
	int flag=1;//筛出一个可能的，判断
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i!=j)
			{
				if((b[i]|b[j])!=mat.a[i][j])//一定要带括号
				{
					flag=0;
					break;
				}
			}
		}
		if(!flag)break;
	}
	if(flag)
	{
		cout<<"yes"<<'\n';
		for(int i=1;i<=n;i++)cout<<b[i]<<' ';
		cout<<'\n';
	}
	else cout<<"no\n";
}
signed main()
{
	cin>>t;
	while(t--)solve();
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

考察一下构造 $a_i$ 的必要条件。

当 $M_{i,j},1\le j\le n,j\ne i$ 有一个的第 $x$ 位为 $0$，$a_i$ 的第 $x$ 位必然为 $0$（二进制下）。

我们按照上面的要求构造出 $a_i$，然后判断一下。

因为按照上面的构造，或起来为 $0$ 的位满足了，判断或起来为 $1$ 的位是否满足即可。

构造、判断都是 $\mathcal{O}(n^2)$ 的，但是写的时候比较傻，把每一位拆开来了，其实直接 `&` 构造 $a_i$ 也是可行的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
int T, n, a[N][N], ans[N], flag;
inline void solve(){
	for(int i = 1; i <= n; i++) ans[i] = 0;
	for(int k = 29; ~k; k--){
		for(int i = 1; i <= n; i++){
			flag = 1;
			for(int j = 1; j <= n && flag; j++){
				if(i == j) continue ;
				if((a[i][j] >> k) & 1) ;
				else flag = 0;
			}
			if(flag) ans[i] += 1 << k;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(i == j) continue ;
			if(a[i][j] != (ans[i] | ans[j])){
				printf("NO\n");
				return ;
			}
		}
	}
	printf("YES\n");
	for(int i = 1; i <= n; i++) printf("%d ", ans[i]);
	printf("\n");
}
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				scanf("%d", &a[i][j]);
			}
		}
		solve();
	}
	return 0;
}
/*
1
4
0 3 3 5
3 0 3 7
3 3 0 7
5 7 7 0
*/
```

[评测记录](https://codeforces.com/contest/1903/submission/236447783)

---

## 作者：Cute__yhb (赞：0)

## 题意
给出一个矩阵 $m$，问是否能构造一个序列 $a$，满足 $a_{i}|a_{j}=m_{i,j}(i \ne j)$，如果有，输出这个矩阵。
## 做法
按位或运算法则：

对于两个整数 $a,b$，如果它们二进制上的某一位都为 $0$，则答案二进制上该位为 $0$，反之为 $1$。

根据定义可知，如果答案二进制上该位为 $0$，则两个数二进制该位都为 $0$。

可以先把序列设初值为 $int$ 类型最大值（因为二进制上每一位都为 $1$），再借助与运算（如果当前 $a_{i}$ 和 $m_{i,j}$ 二进制上有一个本位为 $0$，则答案二进制上该位肯定为 $0$）。

最后检查一遍 $a_{i}|a_{j}$ 是否等于 $m_{i,j}$，判断可行性。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned int n,c[1005],d[1005][1005];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		c[i]=2147483647;//赋初值
		for(int j=1;j<=n;j++){
			int x;
			cin>>x;
			d[i][j]=x;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			c[i]=c[i]&d[i][j];
		}
		for(int j=i+1;j<=n;j++){
			c[i]=c[i]&d[i][j];
		}
	}
	bool f=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j){
				if((c[i]|c[j])!=d[i][j]){//优先级问题，此处应加括号
					f=0;//不可行
					break;
				}
			}
		}
	}
	if(f) cout<<"YES\n";
	else cout<<"NO\n";
	if(n==1) cout<<"1\n";//一定要特判
	else if(f) for(int i=1;i<=n;i++) cout<<c[i]<<(i==n?'\n':' ');
}
int main(){
	int t;
	cin>>t;
	while(t--) solve();
    return 0;
}
```


---

## 作者：szhqwq (赞：0)

## $\tt{Solution}$

可以考虑到，对于每一个 $a_i$ 会影响到 $M_{i,j}$ 和 $M_{j,i}$（$i \not = j$ 且 $1 \leq j \leq n$）。所以我们可以使用 $M_{i,j}$ 来找到 $a_i$ 的值，$M_{j,i}$ 来找到 $a_j$ 的值，再依次判断 $a_i \mid a_j$ 是否等于 $M_{i,j}$ 即可。

我们来考虑如何通过 $M_{i,j}$ 来找到 $a_i$ 的值，因为运算是**按位或**，所以如果 $M_{i,j}$ 在二进制下某一位为 $0$，$a_i$ 在二进制下的那一位也必须为 $0$。这个操作我们可以使用**按位与**来实现，并在开始时将 $a_i$ 设为 $2^{30} - 1$。

[Link](https://codeforces.com/contest/1903/submission/236032469)

---

## 作者：江户川·萝卜 (赞：0)

### 题意

对于序列 $a_i$ 定义 $M_{i,j}=a_i\mid a_j$，特别地，有 $M_{i,i}=0$。

给定 $M_{i,j}$ 方阵求任意合法序列 $a_i$，须判无解。

### 解法

按位或意味着 $\forall 1\le i\neq j\le n, a_i\subseteq M_{i,j}$（此处将二进制看做集合），则有 $a_i\subseteq \bigcap M_{i,j}$，这显然是必要条件，记 $S_i=\bigcap M_{i,j}$。

若 $a_i \mid a_j = M_{i,j}$，则 $S_i \mid a_j = S_i\mid a_i \mid a_j=S_i \mid M_{i,j}=M_{i,j}$（因为 $S_i=\bigcap M_{i,j}\subseteq M_{i,j}$）。因此取合法 $a_i$ 等价于取 $S_i$。

所以将 $a_i$ 设为 $S_i$，生成一下 $M_{i,j}$ 矩阵，检验是否相等即可。

---

## 作者：zhangshuhang2011 (赞：0)

## 思路

注意到如果 $a~|~b$ 的某一位是 $0$，则 $a$ 和 $b$ 的对应位都是 $0$，而如果那一位是 $1$ 的话对应位只需要有一个是 $1$ 就行了。所以我们可以先把所有数的所有位都设成 $1$，然后不断和条件按位与就行了。

但是这样是无法判断无解的，所以最后需要再判断一下每一个条件是否满足。由于在前面的步骤中已经尽量保留 $1$，如果这时还有不满足条件的数则必然无解。代码实现如下：

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int all_1 = 0x3fffffff; // 1.
int n, m[1002][1002], a[1002];
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> m[i][j];
        }
    }
    for(int i = 1; i <= n; i++){
        a[i] = all_1;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i == j) continue;
            a[i] = a[i] & m[i][j];
            a[j] = a[j] & m[i][j];
        }
    }
    bool flg = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i == j) continue;
            if((a[i] | a[j]) != m[i][j]){ // 2.
                flg = 0;
                break;
            }
        }
    }
    if(flg){
        cout << "YES" << endl;
        for(int i = 1; i <= n; i++) cout << a[i] << " ";
        cout << endl;
    }else{
        cout << "NO" << endl;
    }
}
int main(){
    int t; cin >> t;
    while(t--) solve();
    return 0;
}

```

## 注意事项（调了半天才发现）

1. `all_1` 必须是 `0x3fffffff`，`0x7fffffff` 会 WA（超过输出上限，输出上限为 `0x3fffffff`）。
2. 按位或（`|`）的优先级比不等号（`!=`）低，需要加括号。


---

