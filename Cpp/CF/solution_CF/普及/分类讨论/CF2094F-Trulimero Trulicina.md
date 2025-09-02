# Trulimero Trulicina

## 题目描述

Trulicina 给你三个整数 $n$、$m$ 和 $k$。题目保证 $k \geq 2$ 且 $n \cdot m \equiv 0 \pmod{k}$。

请输出一个 $n \times m$ 的整数网格，满足以下所有条件：
- 网格中的每个整数都在 $1$ 到 $k$ 之间（包含 $1$ 和 $k$）。
- 从 $1$ 到 $k$ 的每个整数出现的次数相同。
- 共享一条边的两个单元格不能包含相同的整数。

可以证明这样的网格总是存在。如果存在多个解，输出任意一个即可。

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
2 2 2
3 4 6
5 5 25```

### 输出

```
1 2
2 1
1 6 1 6
2 5 2 5
3 4 3 4
17 2 12 25 14
3 1 6 19 11
8 20 23 24 4
9 10 5 13 21
22 7 15 18 16```

# 题解

## 作者：zhangli828 (赞：4)

## 题目大意
请你构造一个含有 $1\sim k$ 的 $n\times m$ 网格，并且每个数的数量相等，没有两个数所在的表格的边相邻，请你输出一种合法的构造。
## 题目解法
最朴素的填法就是依次填上 $1\sim k$。但我们发现如果 $m$ 是 $k$ 的倍数，则上下相邻的两个数相等。为了避免上下相邻的两个数相等，我们把奇数行位移一位即可。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, n, m, k;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--;) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        cout << (((i - 1) * m + j + (i % 2 && m % k == 0)) % k ? ((i - 1) * m + j + (i % 2 && m % k == 0)) % k : k) << ' ';
        // (i % 2 && m % k == 0) 代表如果 m 是 k 的倍数，i 为奇数则位移
      }
      cout << '\n';
    }
  }
  return 0;
}
```

---

## 作者：bian_cheng123 (赞：2)

## 题意理解
我们需要构造一个 $n \times m$ 的网格，填入 $1$ 到 $k$ 之间的整数，使得四联通（上下左右）格子之间数字不同，并且每个数字的个数相同。
## 分析
如果一行正好可以摆好几个完整地周期（即当 $k \mid m$ 时），那么就每行按顺序正常输出，下一行往后错一位即可，这样显然可以保证上下数字不同且数量相同。

当 $k \nmid m$ 时，那么正常按顺序输出即可，因为它每一行最后都不是一个完整的周期，所以上下一定不会相同。又因为 $k \geq 2$ 且 $n \cdot m \equiv 0 \pmod{k}$ 吗，所以依旧可以保证每个数数量相同。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
void solve(){
	int n,m,k; cin >> n >> m >> k;
	if (m % k != 0){
		int now = 0;
		for (int i = 1 ; i <= n ; i++){
			for (int j = 1 ; j <= m ; j++){
				now++; 
				if (now > k) now = 1;
				cout << now << " ";
			}
			cout << endl;
		}
	}
	else{
		int s = 0;
		for (int i = 1 ; i <= n ; i++){
			s++; 
			if (s > k) s = 1;
			int now = s - 1;
			for (int j = 1 ; j <= m ; j++){
				now++;
				if (now > k) now = 1;
				cout << now << " ";
			}
			cout << endl;
		}
	}
}
int main()
{
	int T; cin >> T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：yanrs1019 (赞：0)

# 题解：CF2094F Trulimero Trulicina  
## 分析题目本质
由于这是一道构造题，所以我们考虑分类讨论。  
## 分类讨论  
### 1. $k \nmid m$：  
#### 填充方法  
按顺序，从上到下，从左到右填充。  
#### 举例  
如 $n=5,m=3,k=5$：  
```
1 2 3
4 5 1
2 3 4
5 1 2
3 4 5
```  
### 2. $k \mid m$ 且 $k \nmid n$：  
#### 填充方法  
按顺序，从左到右，从上到下填充。  
#### 举例  
如 $n=3,m=5,k=5$：  
```
1 4 2 5 3
2 5 3 1 4
3 1 4 2 5
```
### 3. $k \mid m$ 且 $k \mid n$：  
#### 填充方法  
每行顺序填充，但是每换一行就错位一下。  
#### 举例  
如 $n=5,m=5,k=5$：
```
1 2 3 4 5
2 3 4 5 1
3 4 5 1 2
4 5 1 2 3
5 1 2 3 4
```
## ACcode  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define N 200005
void solve(){
	LL n,m,k,cnt=1;
	scanf("%lld%lld%lld",&n,&m,&k);
	if(m%k){
		for(LL i=1;i<=n;i++){
			for(LL j=1;j<=m;j++){
				printf("%lld ",cnt++);
				if(cnt>k)cnt=1;
			}
			printf("\n");
		}
	}
	else if(n%k){
		for(LL i=1;i<=n;i++){
			cnt=i%k;
			if(cnt==0)cnt=k;
			for(LL j=1;j<=m;j++){
				printf("%lld ",cnt);
				cnt+=n;
				cnt%=k;
				if(cnt==0)cnt=k;
			}
			printf("\n");
		}
	}
	else if(n%k==0&&m%k==0){
		for(LL i=1;i<=n;i++){
			cnt=i%k;
			if(cnt==0)cnt=k;
			for(LL j=1;j<=m;j++){
				printf("%lld ",cnt++);
				if(cnt>k)cnt=1;
			}
			printf("\n");
		}
	}
}
int main(){
	LL T;
	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：sjh0626 (赞：0)

## 思路分析
构造题，经典。

我们分两种情况：
- $m$ 为 $k$ 的倍数时，我们要错位着去排（就是第一行第一个为 $1$，第二行第一个为 $2$，每行是连续的（$k$ 的后面是 $1$）。

- $m$ 不为 $k$ 的倍数时，我们就正常按顺序输出（$k$ 的后面是 $1$）。

## 代码解析
```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
#define PII pair<int,int>
using namespace std;
int t=1,n,m,k,cnt;
void solve(){
	cin>>n>>m>>k;
	cnt=1;
	if(m%k!=0){
		for(int i=1;i<=n;i++){
			for(int i=1;i<=m;i++){
				cout<<cnt<<" ";
				if(cnt==k)cnt=1;
				else cnt++;
			}
			cout<<"\n";
		}
	}
	else{
		for(int i=1;i<=n;i++){
			cnt=i;
			if(cnt>k)cnt%=k;
			if(cnt==0)cnt=k;
			for(int j=1;j<=m;j++){
				cout<<cnt<<" ";
				if(cnt==k)cnt=1;
				else cnt++;
			}
			cout<<"\n";
		}
	}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>t;
    while(t--){
        solve();
    }
    sjh0626s code;
}
```

---

## 作者：HYdroKomide (赞：0)

### 题意

给定 $n\times m$ 格子，往里面填入 $[1,k]$ 的整数，使得各个整数出现次数相同且相同整数不相邻。

### 思路

简单构造。我们观察 $k=2$ 的情况，不难发现这个结果其实非常容易满足。

如果按照横平竖直的顺序，依次填入 $[1,k]$，在很多情况下就可以满足条件。唯一一点例外是当 $m$ 是 $k$ 的倍数时，每一横行的所有数都会相同。

严谨一点说，当 $m$ 不是 $k$ 的倍数时，依次填入 $[1,k]$，由于 $k\ge 2$，所以一个数左右两边一定是与此数不同的。而上下的数由于存在余数的缘故，也一定不同。

因此特判 $m$ 是 $k$ 的倍数的情况，将一行所有数平移一格并将头部数字放到尾部即可。

### 程序如下

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int T,n,m,k;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&k);
		int cur=0;
		for(int i=1;i<=n;i++){
			if(m%k==0&&i%2==0){
				cur++;
				for(int i=1;i<=m;i++)printf("%d ",(++cur)%k+1);
				cur--;
			}
			else
				for(int i=1;i<=m;i++)
					printf("%d ",(++cur)%k+1);
			puts("");
		}
	}
	return 0;
}
```

### THE END

![](https://cdn.luogu.com.cn/upload/image_hosting/1mwql2t3.png)

---

## 作者：szh_AK_all (赞：0)

模拟题。

首先如果 $m$ 不被 $k$ 整除，那么显然可以将 $1\sim k$ 按从左到右、从上到下的顺序放进我们需构造的二维数组中，然后一直循环重复这样的操作即可。

如果 $m$ 被 $k$ 整除，那么对于行号为奇数的行，将 $1\sim k$ 按顺序放入该行即可；对于行号为偶数的行，考虑将 $1$ 和 $2$、$3$ 和 $4$、$5$ 和 $6$ 等交换位置，注意特判 $k$ 为奇数的情况，当 $k$ 为奇数时将最后三个数 $k-2,k-1,k$ 互换位置即可。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int a[N], b[N];
 
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		int n, m, k;
		cin >> n >> m >> k;
		int now = 1;
		if (m % k == 0) {
			if (k % 2 == 0)
				for (int i = 1; i <= k; i += 2)
					b[i] = i + 1, b[i + 1] = i;
			else {
				for (int i = 1; i <= k - 3; i += 2)
					b[i] = i + 1, b[i + 1] = i;
				b[k - 2] = k - 1, b[k - 1] = k, b[k] = k - 2;
			}
			for (int i = 1; i <= n; i++) {
				if (i % 2 == 1)
					for (int j = 1; j <= m; j++) {
						if (j % k == 0)
							cout << k;
						else
							cout << j % k;
						cout << " ";
					} else {
					for (int j = 1; j <= m; j++) {
						if (j % k == 0)
							cout << b[k];
						else
							cout << b[j % k];
						cout << " ";
					}
				}
				cout << "\n";
			}
			continue;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cout << now << " ";
				now++;
				if (now > k)
					now -= k;
			}
			cout << "\n";
		}
	}
}
```

---

## 作者：Ag2WO4 (赞：0)

分类讨论：
- 如果 $m$ 和 $n$ 都不能被 $k$ 整除则直接 $1$ 到 $k$ 循环摆 $\frac{mn}k$ 遍然后穿到矩阵里，余数产生的列号位移让相同的数包碰不上的。
- 如果其中一种能被 $k$ 整除（不妨设是 $n$）可以则直接每行 $1$ 到 $k$ 循环摆 $\frac nk$ 遍，每行之间位移一格，同样包碰不上的。
#### Python 代码
```python
for _ in range(int(input())):
    m,n,k=map(int,input().split())
    if m%k and n%k:
        for i in range(m):print(*((i*n+j)%k+1 for j in range(n)))
    else:
        for i in range(m):print(*((i+j)%k+1 for j in range(n)))
```
#### C/C++ 代码
```c
#include<stdio.h>
int t,m,n,k,j;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&m,&n,&k);
        j=n;
        if(m%k&&n%k)
        {
            while(m--)
            {
                while(--n)printf("%d ",(m*j+n)%k+1);
                n=j;
                printf("%d\n",m*j%k+1);
            }
        }
        else
        {
            while(m--)
            {
                while(--n)printf("%d ",(m+n)%k+1);
                n=j;
                printf("%d\n",m%k+1);
            }
        }
    }
}
```

---

