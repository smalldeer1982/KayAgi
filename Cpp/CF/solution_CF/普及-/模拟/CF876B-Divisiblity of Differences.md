# Divisiblity of Differences

## 题目描述

You are given a multiset of $ n $ integers. You should select exactly $ k $ of them in a such way that the difference between any two of them is divisible by $ m $ , or tell that it is impossible.

Numbers can be repeated in the original multiset and in the multiset of selected numbers, but number of occurrences of any number in multiset of selected numbers should not exceed the number of its occurrences in the original multiset.

## 样例 #1

### 输入

```
3 2 3
1 8 4
```

### 输出

```
Yes
1 4 ```

## 样例 #2

### 输入

```
3 3 3
1 8 4
```

### 输出

```
No```

## 样例 #3

### 输入

```
4 3 5
2 7 7 7
```

### 输出

```
Yes
2 7 7 ```

# 题解

## 作者：yutong_Seafloor (赞：2)

# [题目在这里 · CF876B Divisiblity of Differences](https://www.luogu.com.cn/problem/CF876B) 

~~我来仗着我代码短来发题解啦！~~


------------


### 题目简要：
给你 $n$ 个整数，需要找到 $k$ 个数，使他们的差可以被 $m$ 整除，否则输出 `No`。


------------

### 题意分析
这道题主要是用[“同余定理”](https://baike.baidu.com/item/%E5%90%8C%E4%BD%99%E5%AE%9A%E7%90%86/1212360?fr=ge_ala)

“给定一个正整数 $m$，如果两个**整数** $a$ 和 $b$ 满足 $a - b$ 能够被 $m$ 整除，即 $( a - b ) \div m $ 得到一个整数，那么就称整数 $a$ 与 $b$ 对模 $m$ 同余，**记作** $a \equiv b \pmod m$。”
——百度百科

如果按照题意列出式子的话，我们会列出 $( a - b ) \div m $，恰好和同余定理的导推式一模一样，也就是说：
$$a \bmod m = b \bmod m$$
利用此我们得到了大致思路，但这里可不是一个简简单单的同余，因为这里我们要找的数可不只有一个，于是有了下半段。

为了储存余数的所有情况，我们就需要桶排（又称堆排序），简单来说就是用一个数组储存好所有情况的个数，具体的我会在代码中加入注释。

作为优化，我们可以发现我们并不需要等到所有数都数完了再进行判断，因为往往我们会发现有些情况下的同余数字要大于 $k$，为了防止溢出还需要判断，而放入输入程序一起中就不需要这种担心，因为一次输入一个一次顶多加 $1$，到了需求正好卡上，就可以达到缩减代码的目的，一共 $17$ 行是目前最短代码。


------------


## 代码 


```cpp 
#include<bits/stdc++.h>
using namespace std;
int n,k,m,i,j,pd,a[10000010],b[10000010];
int main(){
	cin>>n>>k>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
		if(++b[a[i]%m]==k){//这里++b[a[i]%m]就是桶排
			cout<<"Yes"<<endl;
			for(j=1;j<=i;j++)
			if(a[j]%m==a[i]%m) cout<<a[j]<<" ";
			return 0;
		}
	}
	cout<<"No";
	return 0;
}//by·yutong_Seafloor 
``` 


------------

**这里要注意：**

1. 请注意，题中给的是 `Yes`，`No`，请勿写成 `yes`，`no`，`YES`，`NO`。
2. 第 $10$ 行中的 `if` 一定要是 **`++b[a[i]%m]`**！！！！不然爆零两行泪。

 [AC！](https://www.luogu.com.cn/record/121466332)

请勿抄袭谢谢。

---

## 作者：Fengyiwei1234 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF876B)

# 思路：模拟

这题十分简单，如果 $k$ 个数的差能被 $m$ 整除，那么这 $k$ 个数一定模 $m$ 是同一个余数。

通过数组枚举即可。

时间复杂度：$O(n^2)$。

AC 代码：

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int x[N],cnt[N],n,k,m;
int main()
{
    cin>>n>>k>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i];
        cnt[x[i]%m]++;
    }
    for(int i=0;i<m;i++)
    {
        if(cnt[i]>=k)
        {
            cout<<"Yes"<<endl;
            int sum=0;
            for(int j=1;j<=n;j++)
            {
                if(x[j]%m==i)
                {
                    cout<<x[j]<<" ";
                    sum++;
                }
                if(sum==k)return 0;//有可能数量大于 k,所以需要判断，到了立刻停止
            }
        }
    }
    cout<<"No"<<endl;
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/113362599)

---

## 作者：yxy666 (赞：1)

竟然没有人发题解。。。那就让我这个蒟蒻来发一篇吧。

看到这一道题，我的第一思路是 $dfs$ ，然后随机选取 $k$ 个数，求出两两之间的差值，再看差值能否整除 $m$ 。很显然， $n$ 的上限是 $100000$ ，所以肯定行不通。那我应该怎么办呢？

经过一番推证（简称胡搞），我貌似发现了什么：如果集合中两两之差能被 $m$ 整除，那么它们 $%m$ 之后的余数应该相等。然后我试着码了一下，然后，竟然过了！好开森！

思路：在把数读进来的的时候将每个数 $%m$ 的值计数记下来，然后找相同余数数量大于等于 $k$ 的，然后将所有数字遍历一趟，如果余数等于这个数量大于等于 $k$ 的余数，输出，一直到总共输出了$k$ 个。结束。否则就输出 “ $No$ ”。

$code$ :
```cpp
#include <bits/stdc++.h>
#define maxn 100005
using namespace std;
int a[maxn],b[maxn];
int n,k,m;
int vis[maxn];
bool flg;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
    n=read();k=read();m=read();
    for(int i=1;i<=n;i++)b[i]=a[i]=read(),b[i]%=m;
    for(int i=1;i<=n;i++)vis[b[i]]++;
    for(int i=0;i<m;i++){
        if(vis[i]>=k){
            int cnt=0;flg=1;
            printf("Yes\n");
            for(int j=1;j<=n;j++){
                if(b[j]==i){
                    printf("%d ",a[j]);
                    cnt++;
                }
                if(cnt==k) return 0;;
            }
        }
    }
	printf("No\n");
    return 0;
}
```


---

## 作者：sssscy_free_stdio (赞：0)

这题很简单，就是因为如果 $k$ 个数的差是 $m$ 的倍数，那么它们都对于模 $m$ 同余。

于是，我们就可以用一个 $cnt$ 数组来统计 $a$ 数组中模 $m$ 得到的结果分别有多少个，然后枚举一遍 $0$ 到 $m-1$，判断一遍 $a$ 数组中模 $m$ 为这个值的有多少个，如果 $\ge k$，就输出 `Yes`，然后枚举一遍 $a$ 数组，如果 $a_j$ 模 $m$ 为 $i$,就输出就行了。

注意，要有一个变量 $vis$ 来记录已经输出了多少个，如果到了 $k$ 个，就 `exit(0);` 就行了。

无注释 AC CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,k,m,a[N],cnt[N];
int main(){
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		cnt[a[i]%m]++;
	}for(int i=0;i<m;i++){
		if(cnt[i]>=k){
			printf("Yes\n");
			int vis=0;
			for(int j=1;j<=n;j++){
				if(a[j]%m==i){
					printf("%d ",a[j]);
					vis++;
				}if(vis==k){
					exit(0);
				}
			}		
		}
	}printf("No");
	return 0;
}
```

---

## 作者：ssSSSss_sunhaojia (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/CF876B)
# 题意简述：
给定 $n$ 个数，要求选出其中 $k$ 个数，使得这 $k$ 个数之间的差能被 $m$  整除。

# 思路：
读完题目后我们发现，$k$ 个数之间的差能被 $m$ 整除这个问题不是很好解决，于是我们将其转换为：$k$ 个数除以 $m$ 的余数相同。

再观察题目数据范围可知，$m$ 不会超过 $100000$，所以我们用一个桶来存储每种余数对应的个数有多少个，如果个数不小于 $k$，直接输出。若到最后都没有找到一种合格的余数，输出 ```No```。

# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
LL n, k, m, a[(LL)1e5 + 10], b[(LL)1e5 + 10]; 
namespace FastIO {
    char *p1, *p2, buf[1 << 14];
    #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 14), stdin), p1 == p2) ? EOF : *p1++)
    template <typename T> inline void read(T& x) {
        x = 0; register int t = 1; register char ch = getchar();
        while (ch < '0' || ch > '9') {if (ch == '-') t = -1; ch = getchar(); }
        while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
        x *= t;
    }
    template <typename T> void write(T x) {
        if (x < 0) {putchar('-'); x = -x; } if (x > 9) write(x / 10);
        putchar(x % 10 ^ 48);
    }
    template <typename T> inline void writeln(T x, char sep = '\n') {write(x); putchar(sep); }
}
using namespace FastIO;
in LL qpow(LL a, LL b) {LL res = 1; while(b) {if(b & 1) res = res * a; a = a * a; b >>= 1; } return res; }
in LL max(LL a, LL b) {return (a > b) ? a : b; }
in LL min(LL a, LL b) {return (a < b) ? a : b; }
int main() {
	IOS;
	read(n); read(k); read(m); 
	for(re int i = 1; i <= n; ++ i)  read(a[i]), ++ b[a[i] % m]; //统计每个桶里的元素个数
	for(re int i = 0; i < m; ++ i) 
		if(b[i] >= k) {//如果数量不小于k
			LL cnt = 0; 
			cout << "Yes\n"; 
			for(re int j = 1; j <= n; j ++) if(a[j] % m == i) {cout << a[j] << " "; cnt ++; if(cnt == k) break; }//输出k个数
			exit(0); 
		} 
	return cout << "No", 0; //输出No
	return 0;
}

```

---

## 作者：oceanfish (赞：0)

## 题目大意
题目给定含有 $n$ 个整数的集合，让你选择其中的 $k$ 个数，使这些数中的每两个数之间的差可以被 $m$ 整除，若可以，则先输出 `Yes`，再在第二行输出这 $k$ 个数，若不可以，则输出 `No`。

[题目传送门](https://www.luogu.com.cn/problem/CF876B)
## 方法分析
我们假设有两个数 $a$ 与 $b$，若 $(a-b) \bmod m = 0$，则会有 $a \equiv b \pmod m$。这是对于同余的定义，不会可以自行上网查询。

对于多个数，上述也是成立的，多进行几次分析就行了，而使用这个定理，我们就可以解决这个问题了，而由于只需要输出 $k$ 个数，答案会有较多种，也就是题目拥有 SPJ,只要输出其中一种答案即可。
## code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100005//宏定义
int x[N], sum[N];//sum数组用来保留x[i]%m的相同数量

int main() {
	int n, k, m;
	cin >> n >> k >> m;
	for (int i = 0; i < n; i++) {
		cin >> x[i];
		sum[x[i] % m]++;
	}
	for (int i = 0; i < m; i++) {
		if (sum[i] >= k) {//只输出一种，所以可以直接判断
			cout << "Yes" << '\n';
			int cnt = 0;
			for (int j = 0; j < n; j++) {//枚举
				if (x[j] % m == i) {
					cout << x[j] << ' ';
					cnt++;
				}
				if (cnt == k)//要及时停步
					return 0;
			}

		}
	}
	cout << "No";//否则输出No
	return 0;//养成好习惯
}
```


---

## 作者：qfpjm (赞：0)

- 这篇题解的思路和 [楼上](https://www.luogu.com.cn/blog/2020NOIP/solution-cf876b) 的这篇一样，不过我在此基础上进行了一些空间上的优化，和对样例的模拟。

# 题解

- 这道题的体面比较直观，直接给出了所求的东西。

- 首先，我们肯定考虑暴搜，但是对于 $2\leq n\leq 100000$ 的数据是绝对过不了的。

- 那么，我们需要换个角度，从这 $k$ 个数的性质入手，因为它们之间的差可以被 $m$ 整除，所以我们可以猜测出出，这 $k$ 个数取模之后的结果可能相等（拿两个数来模拟一下即可）。

- 但是，这不一定对，我们需要结合样例来模拟：

```
3 2 3
1 8 4

```

拿出取模 $m$ 后相等的数：

```
1：1 4

2：8
```

发现取模后为 $1$ 的数的个数刚好满足 $k$ 个，于是这就是答案。

# 代码

这是 [楼上](https://www.luogu.com.cn/blog/2020NOIP/solution-cf876b) 的代码：

```cpp
#include <bits/stdc++.h>
#define maxn 100005
using namespace std;
int a[maxn],b[maxn];
int n,k,m;
int vis[maxn];
bool flg;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int main(){
    n=read();k=read();m=read();
    for(int i=1;i<=n;i++)b[i]=a[i]=read(),b[i]%=m;
    for(int i=1;i<=n;i++)vis[b[i]]++;
    for(int i=0;i<m;i++){
        if(vis[i]>=k){
            int cnt=0;flg=1;
            printf("Yes\n");
            for(int j=1;j<=n;j++){
                if(b[j]==i){
                    printf("%d ",a[j]);
                    cnt++;
                }
                if(cnt==k) return 0;;
            }
        }
    }
	printf("No\n");
    return 0;
}
```

- 我们发现，$b$ 数组是可以不需要的，多出来的那一行 $for$ 也是，于是我们得到优化的代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, k, m;
int a[100005];
int visited[100005];

int main()
{
	cin >> n >> k >> m;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> a[i];
		visited[a[i] % m] ++;
	}
	for (int i = 0 ; i < m ; i ++)
	{
		if (visited[i] >= k)
		{
			cout << "Yes" << endl;
			int cnt = 0;
			for (int j = 1 ; j <= n ; j ++)
			{
				if (a[j] % m == i)
				{
					cout << a[j] << " ";
					cnt ++;
				}
				if (cnt == k)
				{
					return 0;
				}
			}
		}
	}
	cout << "No";
	return 0;
}

```


---

## 作者：WuMin4 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF876B)

# 思路

首先得知道个性质，即若 $a \bmod b = c \bmod b$，那么 $(a-c) \bmod b =0$，因为余数在 $(a-c)$ 中被减掉了。

于是我们可以把所有余数相同的 $a_i$ 丢进一个 vector 里，之后再看余数相同的 $a_i$ 的数量有没有 $\ge k$，有的话就输出前 $k$ 个数，没有就输出 No。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,m,ans,id;
vector<int> y[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(),cout.tie();
	cin>>n>>k>>m;
	for(int x,i=1;i<=n;i++)
		cin>>x,y[x%m].push_back(x);
	for(int i=0;i<m;i++){
		if(y[i].size()>=k){
			cout<<"Yes"<<endl;
			for(int j=0;j<k;j++)
				cout<<y[i][j]<<" ";
			return 0;
		}
	}
	cout<<"No";
	return 0;
}
```

---

