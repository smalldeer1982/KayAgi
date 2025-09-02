# Brr Brrr Patapim

## 题目描述

Brr Brrr Patapim 正在尝试破解 Tiramisù 的秘密密码，这个密码是一个由 $2 \cdot n$ 个元素组成的排列 $^{\text{∗}}$。为了帮助 Patapim 猜测，Tiramisù 给了他一个 $n \times n$ 的网格 $G$，其中 $G_{i,j}$（即网格第 $i$ 行第 $j$ 列的元素）包含 $p_{i+j}$，也就是排列中的第 $(i+j)$ 个元素。

给定这个网格，请帮助 Patapim 破解这个被遗忘的密码。题目保证这样的排列存在，并且可以证明该排列是唯一确定的。

$^{\text{∗}}$ 一个由 $m$ 个整数组成的排列是指一个包含 $1,2,\ldots,m$ 每个数恰好一次的序列。例如，$[1, 3, 2]$ 和 $[2, 1]$ 是排列，而 $[1, 2, 4]$ 和 $[1, 3, 2, 3]$ 不是。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
3
1 6 2
6 2 4
2 4 3
1
1
2
2 3
3 4```

### 输出

```
5 1 6 2 4 3 
2 1 
1 2 3 4```

# 题解

## 作者：Clare613 (赞：3)

## 思路
### 题目大意
就是给你一个二维数组，让你把它变成一个一维数组，规则是一维数组的 $a_{i+j}$ 对应二维数组的 $b_{i,j}$。
### 模拟方法
很明显，会有一个数在二维数组中不存在，也就是 $a_1$，这用脑干都能想得到，于是只要求出 $a_1$ 的值，其他的正常算就行了。\
对于求出 $a_1$ 的方法，就是找到那个不存在的值就可以了。\
最后总结一下，这就是一道模拟题，没有任何其他的方法，直接干就行了。
## code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool f[1605];
int q[1605];
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--){
    	memset(f,0,sizeof(f));
		int n,cnt=0,sum;
		cin>>n;
		sum=(2*n+1)*n;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>q[i+j];
				if(f[q[i+j]]==0){
					sum-=q[i+j];
				}
				f[q[i+j]]=1;
			}
		}
		cout<<sum<<" ";
		for(int i=2;i<=2*n;i++){
			cout<<q[i]<<" \n"[i==n*2];
		}
	}
	return 0;
}
```

---

## 作者：wwwidk1234 (赞：3)

~~[在博客园食用更佳（？）](https://www.cnblogs.com/wwwidk1234)~~

## 题目

给定一个 $n \times n$ 的表格 $G$ 和一个长度为 $2n$ 的排列 $p$，其中 $p_{i+j}=G_{i,j}$，求该排列 $p$。

## 思路

由题意知 $i,j \ge 1$，$i+j \ge 2$，所以排列 $p_2 \sim p_{2n}$ 的数字都在网格 $G$ 中给出，剩下的 $p_1$ 就是 $1 \sim 2n$ 中唯一一个没有出现的自然数。

使用一个标记数组在更新 $p$ 时标记一下，最后 $p_1$ 就是唯一一个没有标记的数字。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N=807*2+7;
int a[N];
bool vis[N];
inline void solve()
{
    int n;
    cin>>n;
    for(int i=1;i<=2*n;i++) vis[i]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>a[i+j];
            vis[a[i+j]]=1;
        }
    }
    for(int i=1;i<=2*n;i++)
    {
        if(!vis[i])
        {
            a[1]=i;
            break;
        }
    }
    for(int i=1;i<=2*n;i++) cout<<a[i]<<' ';
    cout<<'\n';
}
int main()
{
//	freopen("neuvillette.in","r",stdin);
//	freopen("neuvillette.out","w",stdout);
    int T;
    cin>>T;
    while(T--) solve();
	return 0;
}
```

---

## 作者：jinhangdong (赞：1)

我们只需要看边上的，然后看看边上哪个没有先输出哪个，然后从 $(1,1)$ 点开始，先往左到头这一排是 $2$ 到 $n+1$ 的，然后再往下这一排是 $n+1$ 到 $2n$ 的。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=805;
int t,n,a[N][N];
bool vis[2*N];
int main()
{
	cin>>t;
	while(t--)
	{
		memset(vis,0,sizeof(vis));
		cin>>n;
		for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j) cin>>a[i][j];
		for(int i=1;i<=n;++i) vis[a[1][i]]=1;
		for(int i=2;i<=n;++i) vis[a[i][n]]=1;
		for(int i=1;i<=2*n;++i)
		if(!vis[i])
		{
			cout<<i<<" ";
			break;
		}
		for(int i=1;i<=n;++i) cout<<a[1][i]<<" ";
		for(int i=2;i<=n;++i) cout<<a[i][n]<<" ";
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：yangxizhe111 (赞：1)

## 题目大意
给你一个 $n$ 和 $n \times n$ 的矩阵 $G$，$G_{ij}=P_{i+j}$，最后输出 $2 \times n$ 个数，即 $P$ 数组。同时，$P$ 数组是 $n$ 的排列。
## 思路
思路很简单，题目已经说了，$G_{ij}=P_{i+j}$，所以我们直接双 for 循环遍历 $G$ 数组，$P_{i+j}=G_{ij}$，再特殊处理 $P_1$ 的情况，直接用大小为 $n$ 的桶数组存一遍，看哪个数没出现过，就是 $P_1$。
## 如何提交
~~什么东西~~

[cf](https://codeforces.com/contest/2094/problem/C)

[洛谷](https://www.luogu.com.cn/problem/CF2094C)
## AC 代码
禁止复制。  

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int g[802][802],p[1602];
bool flag[1602];	//桶数组
int main(){
	scanf("%d",&t);
	while(t--){
		memset(p,-1,sizeof(p));
		memset(flag,false,sizeof(flag));
		//初始化
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",&g[i][j]);
		//读入
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				p[i+j]=g[i][j];
		//p数组2~n的答案
		for(int i=1;i<=2*n;i++)
			flag[p[i]]=true;
		for(int i=1;i<=2*n;i++)
			if(flag[i]==false){
				p[1]=i;
				break;
			}
		//单独处理p1
		for(int i=1;i<=2*n;i++)
			printf("%d ",p[i]);
		printf("\n");
		//输出，别忘了空格和换行
	}
	return 0;
}
```
## 最后
我还是一个小学生，如有错误还请指出。  
如果你想支持我，欢迎来看我的账号，期待与大家一起探索AI于编程。

[我的账号——喜欢编程的杨同学](https://www.douyin.com/user/MS4wLjABAAAAq-SryDl1Y_LAnBgl6qdsdKtZJ3Q3HduqCq0IgNClnewkJjJ8gEBpGT5vJSwncYip)

完结。

---

## 作者：zhangli828 (赞：0)

## 题目大意
给你一个 $n\times n$ 的表格 $G$，其中 $p_{i+j}=G_{i,j}$，并且 $p$ 是一个长为 $2\times n$ 的排列，请你输出 $p$。
## 题目解法
我们发现一个斜线上的数一定是相等的所以我们把没出现的数先输出，然后输出那些斜线的第一个数就好了。

其中第 $1\sim n$ 个斜线的第一个数为 $G_{1,i}$，而最后 $n-1$ 个斜线的第一个数为 $G_{i,n}$，所以就可以轻而易举的处理出 $p$ 了。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 1010;

int G[kMaxN][kMaxN], vis[kMaxN * 2], t, n;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; cout << '\n') {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> G[i][j], (i == 1) && (vis[G[i][j]] = 1);  // 标记出现的数
      }
      vis[G[i][n]] = 1;  // 标记出现的数
    }
    for (int i = 1; i <= 2 * n; i++) {
      if (!vis[i]) {  // 找出没有出现的数
        cout << i << ' ';
      }
      vis[i] = 0;  // 清空方便下次使用
    }
    // 输出，详见题目解法
    for (int i = 1; i < n; i++) {
      cout << G[1][i] << ' ';
    }
    for (int i = 1; i <= n; i++) {
      cout << G[i][n] << ' ';
    }
  }
  return 0;
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF2094C)
# 思路
本题就是给你一个二维数组，一维数组 $p_{i+j}$ 上的数就对应二维数组中 $G_{i,j}$ 表示的数。

不难看出，一维数组 $p$ 中唯一没有被赋值的数就是 $p_1$，我们只需要找出 $1 \sim 2 \times n$ 中没有出现过的数，然后将其赋值给 $p_1$ 即可。而其余位置上的数在输入时赋值就行。

# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=800+5;
int a[N*2];
int h[N*2];
int main()
{
	int t;
	cin >>t;
	while(t--)
	{
		memset(a,0,sizeof a);
		memset(h,0,sizeof h);
		int n;
		cin >>n;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				int x;
				cin >>x;
				a[i+j]=x;
				h[x]++;
			}
		}
		for(int i=1;i<=n*2;i++)
		{
			if(h[i]==0)
			{
				a[1]=i;
				break;
			}
		}
		for(int i=1;i<=n*2;i++) cout <<a[i]<<" ";
		cout <<'\n';
	}
	return 0;
}

```

---

## 作者：szh_AK_all (赞：0)

首先可以通过输入数据得到 $a_{2\sim 2n}$，然后由于 $a$ 是一个排列，所以 $1\sim 2_n$ 中没出现过的数即为 $a_1$。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
int p[N], t[N];
 
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	while (n--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> p[i + j];
		for (int i = 1; i <= 2 * n; i++)
			t[i] = 0;
		for (int i = 2; i <= 2 * n; i++) {
			t[p[i]]++;
		}
		for (int i = 1; i <= 2 * n; i++)
			if (!t[i])
				p[1] = i;
		for (int i = 1; i <= 2 * n; i++)
			cout << p[i] << " ";
		cout << "\n";
	}
}
```

---

## 作者：metrixgo_caozhendi (赞：0)

一道模拟题，你甚至不需要一个二维数组。由于对于 $a_{i,j}$，你的得到的是第 $i+j$ 位的密码，所以我们可以通过先固定 $i=1$，不断增加 $j$，等 $j=n$ 时，再固定 $j$，不断增加 $i$。这样可以得到密码的 $2$ 到 $2n$ 位。至于第一位，只需要输入的时候把出现的数记录在一个数组中，然后在 $1$ 到 $2n$ 中没有出现的数就是第一位。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=805;
int t,n,m,k,l,r;
int a[N][N],book[2*N];
string s;
queue<int> q;
int main()
{
   cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				cin>>m;
				if(i==1||j==n){
					q.push(m);
					book[m]=1;
				}
			}
		}
		for(int i=1;i<=2*n;i++)
		{
			if(!book[i]) cout<<i<<" ";
			book[i]=0;
		}
		while(q.size())
		{
			cout<<q.front()<<" ";
			q.pop();
		}
		cout<<endl;
		
	}
   return 0;
}
```

---

## 作者：huanglihuan (赞：0)

### Solution
发现第一个数是不确定的，走一个七字行，连起来为 $G_{1,1}\to G_{1,2}\to\ldots\to G_{1,n}\to G_{2,n}\to G_{3,n}\to\ldots\to G_{n,n}$，纵坐标与横坐标加起来为 $1+1,1+2,\ldots,1+n,2+n,3+n,\ldots,n+n$，那么 $p_1$ 就为前面遍历的数组中在 $1-2n$ 的自然数中没有出现的数。

可以通过计算 $1-2n$ 的自然数的总和减去数组中出现的数的总和求出第一个数。
### Code

```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 2e6 + 5,maxn = 3e3 + 5;
int g [maxn] [maxn];
int p [N];
signed main ()
{
	int T;
	cin >> T;
	while (T --)
	{
		int n;
		cin >> n;
		int cnt = 0;
		int s = 0;
		for (int i = 1;i <= n;i ++)
			for (int j = 1;j <= n;j ++)
			{
				int x;
				cin >> x;
				if (i == 1 || j == n) p [++ cnt] = x,s += x;
			}
		cout << 2 * n * (2 * n + 1) / 2 - s << ' ';
		for (int i = 1;i <= cnt;i ++) cout << p [i] << ' ';
		cout <<  endl;
	}
	return 0;
}
```

---

