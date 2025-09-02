# Rudolf and 121

## 题目描述

Rudolf has an array $ a $ of $ n $ integers, the elements are numbered from $ 1 $ to $ n $ .

In one operation, he can choose an index $ i $ ( $ 2 \le i \le n - 1 $ ) and assign:

- $ a_{i - 1} = a_{i - 1} - 1 $
- $ a_i = a_i - 2 $
- $ a_{i + 1} = a_{i + 1} - 1 $

Rudolf can apply this operation any number of times. Any index $ i $ can be used zero or more times.

Can he make all the elements of the array equal to zero using this operation?

## 说明/提示

In the first example, the original array is $ [1, 3, 5, 5, 2] $ , to make all its elements zero, Rudolf can act as follows:

- apply the operation at $ i=4 $ and get the array $ [1, 3, 4, 3, 1] $ ;
- apply the operation at $ i=3 $ and get the array $ [1, 2, 2, 2, 1] $ ;
- apply the operation at $ i=2 $ and get the array $ [0, 0, 1, 2, 1] $ ;
- apply the operation at $ i=4 $ and get the array $ [0, 0, 0, 0, 0] $ .

## 样例 #1

### 输入

```
7
5
1 3 5 5 2
5
2 4 4 5 1
5
0 1 3 3 1
6
5 6 0 2 3 0
4
1 2 7 2
3
7 1 0
4
1 1 1 1```

### 输出

```
YES
NO
YES
NO
NO
NO
NO```

# 题解

## 作者：littlebug (赞：8)

## Description

给定一个长度为 $n$ 的序列 $a$，可以进行任意次操作，每次操作选择一个 $i$，满足 $2\le i\le n-1$，求是否能将整个序列都变为 $0$。

定义一次对于 $i$ 的操作为：
- $ a_{i - 1} = a_{i - 1} - 1 $
- $ a_i = a_i - 2 $
- $ a_{i + 1} = a_{i + 1} - 1 $

## Solution

因为对于 $i$ 的操作需要改变 $a_{i-1},a_i,a_{i+1}$，前后都需要改变，不易操作，所以不妨将整个操作往后推一步，改为：

- $ a_i = a_i - 1 $
- $ a_{i + 1} = a_{i + 1} - 2 $
- $ a_{i + 2} = a_{i + 2} - 1 $

其中，$1\le i\le n-2$。

这样，就能满足操作 $i$ 只能改变 $\ge i$ 的部分了，贪心从前往后推即可。对于每个 $i$ 进行操作直到 $a_i=0$，并同时更改 $a_{i+1}$ 和 $a_{i+2}$ 的值，若在循环过程中遇到一个 $a_i<0$，则无解。另外注意要在循环结束后判断 $a_{n-1}$ 和 $a_n$ 的值是否为 $0$ 就可以了。

时间复杂度 $O(n)$。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define il inline
using namespace std;
const int MAXN=2e5+5;
int n;
int a[MAXN];
il void solve()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1;i<=n-2;++i)
	{
		if(a[i]<0)
		{
			puts("No");
			return;
		}
		a[i+1]-=a[i]*2;
		a[i+2]-=a[i];
	}
	if(a[n-1]==0 && a[n]==0)
		puts("Yes");
	else
		puts("No");
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：2huk (赞：2)

给定一个长度为 $n$ 的序列 $a$。求最少进行多少次操作后所有 $a_i = 0$：

- 选择一个 $2 \le i < n$，并让 $a_i \gets a_i - 2, a_{i - 1} \gets a_{i - 1} - 1, a_{i + 1} \gets a_{i + 1} - 1$。

---

我们记选择 $i = x$ 时的操作为 $\operatorname{opt}(x)$。

发现 $a_1$ 只有 $\operatorname{opt}(2)$ 才会发生变化。也就是说我们只能通过若干次 $\operatorname{opt}(2)$ 才能使 $a_1 = 0$。所以 $\operatorname{opt}(2)$ 需要做 $a_1$ 次。

此时 $a_1 = 0$。

同理，对于 $a_2$，显然我们不能选择 $\operatorname{opt}(1)$ 或 $\operatorname{opt}(2)$。因为这两种操作都会使 $a_1$ 变小。所以此时能影响到 $a_2$ 的只有 $\operatorname{opt}(3)$。

同理依次操作 $\operatorname{opt}(i), i = (2, 3, 4, \dots, n - 1)$。然后判断所有元素是否均为 $0$ 即可。

<https://codeforces.com/contest/1941/submission/251189560>

---

## 作者：lalaji2010 (赞：1)

# CF1941B
## 分析

很显然的，如果这个数组是可以通过此操作全部变为 $0$ 的，那么一定**与操作顺序无关**。

考虑贪心，既然操作的顺序与正确性无关，那么我们就顺序遍历，让每一位都变成 $0$，并附加统计当前位置变为 $0$ 的影响即可。当然，如果在操作过程中发现某一位已经小于 $0$，这个数组也是一定不能被操作成功的。

而由于对 $a_{i-1}$ 进行操作过于困难，我们就可以将题目中的操作等价替换为:

* $a_i \leftarrow a_i-1$
* $a_{i+1} \leftarrow a_{i+1}-2$
* $a_{i+2} \leftarrow a_{i+2}-1$

然后我们遍历 $1$ 到 $n-2$ 进行操作，最后再判断 $a_{n-1}$ 与 $a_n$ 是否为 $0$ 即可。 

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005];
int main(){
    cin>>t;
    while(t--){
        bool flag=0;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<n-1;i++){
            if(a[i]<0){
                flag=1;
                break;
            }
            a[i+1]-=a[i]*2;
            a[i+2]-=a[i];
        }
        if(!a[n]&&!a[n-1]&&!flag){
            puts("YES");
        }else{
            puts("NO");
        }
    }
    return 0;
}
```

---

## 作者：Stone_Xz (赞：1)

## [传送门](https://www.luogu.com.cn/problem/CF1941B)

## 题意：
给出一个 $n$ 个点的序列 $a$，需要每次指定一个下标 $i$ ($2 \le i \le n - 1$)，进行以下操作：

 - $a_{i - 1} = a_{i - 1} - 1$ 

 - $a_i = a_i - 2$
 
 - $a_{i + 1} = a_{i + 1} - 1$

问能否将序列 $a$ 中的所有元素变成 $0$。

## 分析：

我们要将序列 $a$ 的所有元素变为 $0$，就要想怎样才能让 $a_i$ 这个位置变成 $0$。

我们不妨先来思考，怎样把 $a_1$ 变成 $0$？

显然，我们只能操作 $i = 2$ 的位置，操作一次，$a_1$ 就会减一。我们必须在 $i = 2$ 的位置上进行恰好 $a_1$ 次的操作，就能将 $a_1$ 减成 $0$。但如果一开始就 $a_1 < 0$，则无解。

现在将 $a_1$ 变成了 $0$，那 $a_2$ 呢？

$a_1$ 已经是 $0$，不能再动它了。所以只能在 $i = 3$ 的位置进行 $a_2$ 次操作。

发现没有，如果一直这样下去，$a_3,a_4, \dots ,a_{n - 1}$ 都是同理，对于第 $i$ 个位置，只能让 $i + 1$ 的位置进行操作来变成 $0$。对于 $a_n$，判断是否在 $n - 1$ 的位置操作时就变成了 $0$ 即可。

我们再简化一下每次操作，对于位置 $i$ ($1 \le i \le n - 2$)，一次操作可以：

 - $a_i = a_i - 1$
 
 - $a_{i + 1} = a_{i +1} - 2$
 
 - $a_{i + 2} = a_{i + 2} - 1$
 
将操作往右移了一下，代码实现更加方便了（^_^）。

根据以上的分析，我们得到了最终的思路：

> 遍历每一个 $i$，如果 $a_i < 0$，无解，输出 ```NO```。否则对 $a_i$ 进行简化后的操作，将 $a_i$ 减成 $0$。$i + 1$ 和 $i + 2$ 这两个位置也要同时更新。最后判断一下没有遍历到的两个位置 $a_{n - 1}$ 和 $a_n$ 是否也变成了 $0$，如果是，输出 ```YES```，反之输出 ```NO```。

## AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, a[N], T;

void work()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	for(int i = 1; i <= n - 2; i++) // 将 a[i] 变成 0 
	{
		if(a[i] < 0)
		{ 
			cout << "NO\n"; // 无解 
			return ;
		}
		int tmp = a[i];
		a[i + 1] -= tmp * 2; // 更新 
		a[i + 2] -= tmp;
	}
	if(a[n - 1] != 0 || a[n] != 0) // 特判两个位置 
	{
		cout << "NO\n";
		return ; 
	}
	cout << "YES\n";
}

int main()
{
	cin >> T;
	while(T--) // 多组数据 
		work();
	return 0;
}
```

---

## 作者：GY程袁浩 (赞：1)

### 题意
给出一个由 $n$ 个整数组成的数组 $a$，元素的编号从 $1$ 到 $n$。对于每一次操作，选择下标 $i$，执行以下赋值操作。

$a_{i−1}\gets a_{i−1}−1$

$a_{i}\gets a_{i}−2$

$a_{i+1}\gets a_{i+1}−1$

是否可以用这个操作，使整个数组变为零。
### 思路
题目中的操作是修改 $3$ 个元素的值，考虑对原序列差分。题目中的每一次操作就相当于将差分数组 $b_{i-1}$ 以及 $b_{i}$ 减 $1$，将 $b_{i+1}$ 与 $b_{i+2}$ 加 $1$。最终的目标是使得 $b$ 变为全零。

那么对于任何一个 $i$，如果 $b_{i-1}$ 是一个正数，那么就必须选择 $i$ 执行 $b_{i-1}$ 次操作，因为在 $i-1$ 后只有 $i$ 还能减小 $b_{i-1}$ 的值，而且也只能进行 $b_{i-1}$ 次操作，因为在操作就会使 $b_{i-1}$ 变为负数。如果 $b_{i-1}$ 此时为负数，那么就不可能在让它变为正数了，所以不可以使整个 $b$ 数组变为零。

那么我们从 $2$ 到 $n-1$ 遍历一遍所有 $b_{i}$ 然后按照刚刚的思路操作就可以了。

最后检查 $b$ 数组如果不全为零，那么就不可以使整个 $b$ 数组变为零。
### Code
```cpp
#include <iostream>
using namespace std;
const int N=1e5*2+10;
int a[N],b[N];
int n;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) if(a[i]<0)
		{
			puts("NO");
			continue;
		}
		b[1]=a[1];
		for(int i=2;i<=n;i++) b[i]=a[i]-a[i-1];
		bool flag=0;
		for(int i=2;i<n;i++)
		{
			if(b[i-1]<0) break;
			b[i]-=b[i-1];
			b[i+2]+=b[i-1];
			b[i+1]+=b[i-1];
			b[i-1]-=b[i-1];
		}
		for(int i=1;i<=n;i++)
			if(b[i]!=0) flag=1;
		if(flag) puts("NO");
		else puts("YES");
	}
	return 0;
}
```

---

## 作者：zhuhongye (赞：1)

## 题意
给定一个长度为 $n$ 的序列 $a$，每次可以执行一下操作
>选定一个下标 $i$。  
$a_i = a_i - 2$  
$a_{i-1} = a_{i-1} - 1$  
$a_{i+1} = a_{i+1} - 1$

询问序列 $a$ 是否能全部变成 $0$。

## 思路
拿到这个题，我的第一个反应就是贪心。

我们枚举 $i$，尽可能的把 $a_i$ 都减完，但我们要注意 $a_{i-1}$ 和 $a_{i+1}$ 的值必须要是自然数，因为如果 $a$ 数组的元素比 $0$ 小，则永远不可能成功。

也就是对于循环的每一个 $i$，都执行以下操作：
```cpp
int t=min(a[i-1],min(a[i+1],a[i]/2));//表示最多能减多少次		
a[i]-=t*2;
a[i-1]-=t;
a[i+1]-=t;
```

## 完整代码
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int N=2e5+5;

int T;
int n;
int a[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
	cin>>T;
	
	while(T--){
		cin>>n;
		
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		
		for(int i=2;i<n;i++){
			int t=min(a[i-1],min(a[i+1],a[i]/2));
			
			a[i]-=t*2;
			a[i-1]-=t;
			a[i+1]-=t;
		}
		
		bool tmp=1;
		for(int i=1;i<=n;i++){
			if(a[i]!=0){
				tmp=0;
				break;
			}
		}
		if(tmp)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}


```

---

## 作者：Otue (赞：1)

抓住一个性质：$a_1$ 变成 $0$ 的话只能选择 $i=2$ 进行操作。$a_1$ 变为 $0$ 之后，$a_2$ 变为 $0$ 只能选择 $i=3$ 进行操作（选择 $i=2$ 进行操作会将 $a_1$ 变为小于 $0$）。

那么我们可以从 $1$ 开始逐步操作，每一步操作将当前这个数变为 $0$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;

int T, n, a[N];

signed main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		int res = 1;
		for (int i = 1; i < n - 1; i++) {
			if (a[i] < 0) {
				res = 0;
				break;
			}
			a[i + 1] -= 2 * a[i];
			a[i + 2] -= a[i];
			a[i] = 0;
		}
		for (int i = 1; i <= n; i++) res &= (a[i] == 0);
		if (res == 1) puts("Yes");
		else puts("No");
	}
}
```

---

## 作者：lpx666666 (赞：0)

## 题目概括
题目有多组数据，每组数据都输入一个数组，判断数组是否只由 $121$ 叠加而成。
## 思路
其实不用把它看复杂了，它反正是求是否只由 $121$ 叠加而成，所以可以直接从最左边开始便利，枚举三个的区间，判断能包含几个 $121$，然后分别减去 $1$，$2$，$1$，最后判断整个数组是否都为 $0$。
## 代码
又到了你们最喜欢的环节了。
```cpp
#include<iostream>
#include<string>
#include<iostream>
#include<iostream>
using namespace std;
int t,n,a[200005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=3;i<=n;i++){
			int u=min(min(a[i],a[i-1]/2),a[i-2]);
			a[i]-=u;
			a[i-1]-=2*u;
			a[i-2]-=u;
		}
		int u=0;
		for(int i=1;i<=n;i++){
			if(a[i]!=0){
				u=1;
				break;
			}
		}
		if(!u){
			cout<<"YES"<<endl;
		}
		else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}

```

---

## 作者：hhce2012 (赞：0)

省流：跑过去，当前的数的方案是唯一的（

# 思路

首先我们发现 $a_1$ 只能由 $a_2$ 波及。

然后我们对 $2$ 做 $a_1$ 次操作。

于是 $a_1$ 被减完后问题与 $a_1$ 无关了，所以我们把整个问题转化成了一个规模为 $N - 1$ 的子问题。

$T(N) = T(N - 1) + O(1)$，所以 $T(N) = O(N)$。

如法炮制。

出现以下两种情况为不合法：

- 某个数为负数；

- 最后还剩两个数，其中有至少一个不为 $0$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, arr[200020];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  for(cin >> t; t--; ) {
    cin >> n;
    for(int i = 1; i <= n; i++) {
      cin >> arr[i];
    }
    for(int i = 1; i <= n - 2; i++) {
      if(arr[i] < 0) {
        cout << "NO" << '\n';
        goto nxt;
      }
      arr[i + 1] -= 2 * arr[i];
      arr[i + 2] -= arr[i];
    }
    cout << ((!arr[n - 1]) && (!arr[n])? "YES" : "NO") << '\n';
    nxt:;
  }
  return 0;
}
```

---

## 作者：xiongyuhan (赞：0)

简单点说，一道水题（

# 题意

选一个 $2\le i \le n$，使 $a_{i - 1} - 1,a_i -2,a_{i + 1}-1$ 问是否能通过若干次操作使所有的 $a_i(1 \le i \le n)$ 归零。

# 思路

递推

我们设变零就是从需要处理的数中删掉，所以就可以得出每次的第一个数都只能被第二个影响，所以就一个个地变成零就行了。

**注意：循环过程中变成负数要直接跳出！！！**

```cpp
#include<bits/stdc++.h>

using namespace std;

const int Kmaxn = 2e5 + 5;

int t, n, a[Kmaxn];

int main(){
  cin >> t;
  while(t--){
    cin >> n;
    for(int i = 1 ; i <= n ; i++) cin >> a[i];
    for(int i = 1 ; i <= n - 2 ; i++){
      a[i + 1] -= a[i] * 2;
      a[i + 2] -= a[i];
      a[i] = 0;
      if(a[i + 1] < 0 || a[i + 2] < 0) break;
    }
    bool flag = 1;
    for(int i = 1 ; i <= n ; i++){
      if(a[i] != 0) flag = 0;
    }
    if(flag == 1) cout <<"yes\n";
    else cout <<"no\n";
  }
  return 0;
}
```

---

## 作者：OPEC (赞：0)

可以模拟每个点进行减数。

模拟减数会超时，所以要减 $\min(\min(a_{i-1},a_{i+1}),a_{i}\div2)$。

因为 $a_{i-1}$ 这个点减不掉的话，那下一次就碰不到这个点了，所以最后判断剩余数组有没有不是零的。

```cpp
 //不要抄题解 QAQ
#include<bits/stdc++.h>
using namespace std;
#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define int long long
const int N=1e6+10,M=2e6+10;
const int INF=0x3f3f3f3f3f3f3f3f;
const int P=998244353;//3221225477
int t;
int n;
int a[N];
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=2;i<n;i++)
	{
		int b=min(min(a[i-1],a[i+1]),a[i]/2);
		a[i]-=2*b;
		a[i-1]-=b;
		a[i+1]-=b;
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=0)
		{
			cout<<"No/n";
			return;
		}
	}
	cout<<"Yes/n";
	return;
}
signed main()
{
	fst
	cin>>t;
	while(t--)
	{
		solve();
	}
	return 0;
}

```

---

## 作者：nyC20 (赞：0)

# 思路
题目描述的对 $a_i$ 的赋值操作既要改变 $a_i$ 的值，还要改变 $a_{i+1}$ 和 $a_{i-1}$ 的值，不方便思考，所以将题目的赋值操作换一种说法，即对第 $i$ 个元素的赋值操作为：

- $a_{i}=a_{i}-1$
- $a_{i+1}=a_{i+1}-2$
- $a_{i+2}=a_{i+2}-1$

然后，遍历 $a$ 数组，对于每一个数进行贪心处理，因为对于每一个数，能直接改变它的值的次数有且只有一次（在遍历它前两个数时改变它的值为间接改变），即遍历到它的时候，所以这时我们必须将它变为 $0$。但是如果 $a_{i+1}$ 和 $a_{i+2}$ 不够减，那么就说明 $a$ 数组不能全部变为 $0$，反之则可以。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[200003];
int main() {
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=n-2;i++){
			if(a[i+1]>=2*a[i]&&a[i+2]>=a[i]){
				a[i+1]-=2*a[i];
				a[i+2]-=a[i];
				a[i]=0;
			}
			else{
				printf("NO\n");
				goto endd;
			}
		}
		if(a[n-1]==0&&a[n]==0){
			printf("YES\n");
		}
		else printf("NO\n");
		endd:;
	}
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

#### [传送门](https://www.luogu.com.cn/problem/CF1941B)
### 题目大意
给定一个长度为 $n$ 的序列 $a$，可以对第 $i(2\le i \le n-1)$ 个数执行任意次以下操作：
- $a_{i - 1} = a_{i - 1} - 1$
- $a_i = a_i - 2$
- $a_{i + 1} = a_{i + 1} - 1$

问能否使序列中每一个数都为 $0$。
### 思路
首先题目的操作从 $2$ 开始，我觉得不方便，所以改为了对 $i(1\le i \le n-2)$ 个数做以下操作：
- $a_i = a_i - 1$
- $a_{i + 1} = a_{i + 1} - 2$
- $a_{i + 2} = a_{i + 2} - 1$

我们可以用循环解决。因为我们要尽可能使每个点都为 $0$，所以我们每枚举到一个点 $a_i$，就执行以下操作：
- $a_i = a_i - a_i$
- $a_{i + 1} = a_{i + 1} - 2 \times a_i$
- $a_{i + 2} = a_{i + 2} - a_i$

这样就可以保证当前的数一定为 $0$ 了。

如果如此操作使得后面的数 $a_{i+x}$ 变为负数，我们又并没有加法操作，可得此序列一定是无法满足现在的数 $a_i$ 和 $a_{i+x}$ 都为 $0$ 的。那我们只需要跳出循环进行输出就可以了。

那么我们怎么实现这个操作呢？

我们只需要定义一个判断变量 $bj$，在每一次循环的最前面判断此数是否为负数，如果是就使得 $bj = 1$ 并跳出循环，在输出时就只需要判断 $bj$ 的值就可以了。（具体可以看代码）

### 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t, n, num[200005];
signed main() {
	ios::sync_with_stdio(0);//输入输出优化 
	cout.tie(0);
	cin.tie(0);
	cin >> t;
	while (t--) {
		int bj = 0;//定义bj变量 
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> num[i];
		for (int i = 1; i <= n - 2; i++) {
			if (num[i] < 0) { //判断是否为负 
				bj = 1;
				break;
			}
			num[i + 1] -= num[i] * 2;
			num[i + 2] -= num[i];
			num[i] = 0;
		}
		for (int i = n - 1; i <= n; i++) if (num[i] != 0) bj = 1; //特判最后两个数 n-1 与 n 以及特判 n<3 的情况 
		if (bj == 1) cout << "no\n"; //bj=1 即不可能让所有数都为 0 
		else cout << "yes\n";
	}
	return 0;
}
```

---

## 作者：kczw (赞：0)

# 题意
共 $t$ 组数据。

每组数据给定一个长 $n$ 的序列 $a$。你可以对其操作，操作时选定三个相邻下标 $i,i+1,i+2(1\le i\le n-2)$，并使：

- $a_{i-1}=a_{i-1}-1$
- $a_i=a_i-2$
- $a_{i+1}=a_{i+1}-1$

问是否可以通过若干次操作，使 $a_i=0(1\le i\le n)$
# 思路
不妨假定 $a$ 时可以通过若干次操作使得所有元素为 $0$ 的。

很容易注意到 $a_1$，它很特殊，它只有在修改 $a_1,a_2,a_3$ 时能够被修改。因为我们的假定，可以知道 $a_1,a_3,a_3$ 需要 $a_1$ 次修改，修改过后 $a_1$ 的值便为 $0$ 了，此时重复上述思路直到 $a_{n-2}$。

修改过程中，如果有某个数变为了负数或者最后 $a_{n-1}\ne 0$ 或 $a_n\ne 0$，则说明无法达成条件。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n,a[N];
main(){
	scanf("%d",&t);
	while(t--){
		int flag=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n-2;i++){
			a[i+1]-=a[i]*2;
			a[i+2]-=a[i];
			a[i]=0;
			if(a[i+1]<0||a[i+2]<0){
				flag=1;
				break;
			}
		}
		if(flag||a[n-1]!=0||a[n]!=0){
			puts("NO");
			continue;
		}
		puts("YES");
	}
	return 0;
}
```

---

## 作者：Weekoder (赞：0)

### 思路

首先，观察到操作的 $i$ 范围为 $2\le i\le n-1$，而且通过样例发现操作的顺序不分前后，考虑枚举 $i$。 

由于操作的顺序不分前后，我们可以想到一次性在一个点上操作多次，即 $\lfloor\frac{a_i}{2}\rfloor$ 次。我们记 $tmp=\lfloor\frac{a_i}{2}\rfloor$。同时，$a_{i-1}$ 和 $a_{i+1}$ 减去 $tmp$，$a_i$ 减去 $tmp\times2$。

那如果 $a_{i-1}$ 或 $a_{i+1}$ 小于 $tmp$，也就是减不了呢？我们可以取 $\min(a_{i-1},a_{i+1})$，并**让 $tmp$ 等于 $\min(a_{i-1},a_{i+1})$** 就可以了，再执行上面的操作。

最后检查 $a$ 数组是否全部为 $0$ 即可。

# $\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int T, n, a[N], b[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T --) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 2; i < n; i++) {
            if (!a[i]) continue;
            int tmp = a[i] / 2;
            if (tmp <= a[i - 1] && tmp <= a[i + 1]) {
                a[i] -= tmp * 2;
                a[i - 1] -= tmp;
                a[i + 1] -= tmp;
            }
            else {
                tmp = min(a[i - 1], a[i + 1]);
                a[i] -= tmp * 2;
                a[i + 1] -= tmp;
                a[i - 1] -= tmp;
            }
        }
        bool f = 1;
        for (int i = 1; i <= n; i++) {
            if (a[i]) {
                cout << "NO\n";
                f = 0;
                break;
            }
        }
        if (f) cout << "YES\n";
    }
    return 0;
} 
```

---

## 作者：Bc2_ChickenDreamer (赞：0)

## CF1941B

### Sol

首先，经过推理我们可以发现使 $a_i = 0$ 有 $3$ 种办法。但如果 $a_{i - 1} = 0$ 了，那么就只能在 $a_{i + 1}$ 上使用操作了。所以我们就枚举中间的（$1 \sim n - 2$），如果 $a_i \ge 0$ 那么就将 $a_{i + 1}$ 通过多次操作变为 $0$。

最后遍历一遍，如果 $a_i$ 全部为 $0$ 就有解。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

using ll = long long;

const int kMaxN = 2e5 + 20, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;

ll n, a[kMaxN];
bool f = 1;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    cin >> n, f = 1;
    for (int i = 1; i <= n; ++ i) {
      cin >> a[i];
    }
    for (int i = 1; i <= n - 2; ++ i) {
      if (a[i] < 0) {
        cout << "NO\n";
        f = 0;
        break;
      }
      ll k = a[i];
      a[i + 1] -= 2 * k;
      a[i] = 0;
      a[i + 2] -= k;
    }
    for (int i = 1; i <= n; ++ i) {
      if (a[i] != 0 && f) {
        cout << "NO\n";
        f = 0;
        break;
      }
    }
    if (f) {
      cout << "YES\n";
    }
  } 
  return 0;
}
```

---

## 作者：minVan (赞：0)

**题目大意**

给定一个数列 $a_1,a_2,\cdots,a_n$，每一次操作选定一个 $i\in(1,n)$，使得 $a_{i-1}\gets a_{i-1} - 1,a_i\gets a_i-2,a_{i+1}\gets a_{i+1}-1$。

问能否进行若干次操作后使得任意 $a_i=0$。

**解题思路**

枚举 $i$ 从 $2$ 到 $n-1$，此时用几次操作将 $a_{i-1}$ 变为 $0$，需要 $a_{i-1}$ 次操作，若 $a_i<2a_{i-1}$ 或者 $a_{i+1}<a_{i-1}$，那么 $a_i$ 无法变为 $0$；否则将 $a_i$ 减去 $2a_{i-1}$，$a_{i+1}$ 减去 $a_{i-1}$。

**AC 代码，请勿抄袭。**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int a[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    a[0] = a[n + 1] = 0;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    bool flag = 0;
    for(int i = 2; i < n; i++) {
      if(a[i - 1]) {
        if(a[i - 1] > (a[i] >> 1) || a[i + 1] < a[i - 1]) {
          flag = 1;
          break;
        }
        a[i] -= a[i - 1] << 1, a[i + 1] -= a[i - 1];
      }
    }
    if(a[n] || a[n - 1]) { flag = 1; }
    cout << (!flag ? "YES\n" : "NO\n");
  }
  return 0;
}
```

---

## 作者：_dbq_ (赞：0)

## 题目大意
给定一个长度是 $n$ 的序列 $a$，可以进行任意次操作，操作方法如下：

- 选择一个 $i$ ( $2 \le i \le n-1$ )。
- $a_{i-1}=a_{i-1}-1$。
- $a_{i}=a_{i}-2$。
- $a_{i+1}=a_{i+1}-1$。

求操作后能否使所有的 $a_i=0$。

## 做法
考虑从左往右依次变成 0，只需先使 $i=2$ 操作 $a_1$ 次，这样就使 $a_1$ 变成了 0。接下来使 $i=3$ 操作 $a_2$ 次，此时并不会影响 $a_1$ ，以此类推。

当我们全部操作完成后，遍历一遍 $a$ 序列，只要全部为 0，就表示可以使所有的 $a_i=0$，否则不可以。

## 代码
```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<vector>
#define LL long long
#define ULL unsigned long long
#define cint const int 
using namespace std;
cint INTINF=0x7f7f7f7f;
const LL LLINF=9e18;//以上是模板
cint N=2e5+10;//定义n的上限
int a[N];//存数据
inline auto read(){//输入量大,建议快读
    auto x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int main()
{
    #ifdef dbq
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    int T=read();//有多组数据
    while(T--)
    {
        memset(a,0,sizeof(a));//多组数据,清空数组好习惯
        cint n=read();
        for(int i=1;i<=n;i++)
            a[i]=read();//读入a[i]
        for(int i=2;i<=n-1;i++)
            if(a[i-1]<0) break;//由于每个数只会减少,所以一旦有负数,就不可能再变成0
            else if(a[i-1]==0) continue;//如果是0的话就不用调了
            else
            {
                //要使a[i-1]变成0,每次减1,就要减a[i-1]次
                a[i]-=2*a[i-1];//a[i]每次减2,减a[i-1]次
                a[i+1]-=a[i-1];//a[i+1]每次减1,减a[i-1]次
                a[i-1]=0;//a[i-1]直接清空
                if(a[i]<0||a[i+1]<0) break;//判一下负数
            }
        bool flag=false;
        for(int i=1;i<=n;i++)//最后检验一下
            if(a[i]!=0)//如果有0,就不可能了
            {
                flag=true;
                break;
            }
        if(flag) cout<<"NO"<<endl;//输出
        else cout<<"YES"<<endl;
    }
    return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1941B
## 题意
给定一个长度为 $n$ 的数组 $a$，每次操作可以将下标为 $i$ 的元素 $-2$，将下标为 $i-1$ 和 $i+1$ 的元素 $-1$，问能否把所有元素都变成 $0$。
## 思路
本题考虑使用贪心。因为 $2 \le i \le n-1$，所以要使 $a _ {1}$ 变成 $0$，必须做若干次 $i=2$ 的操作。这时 $a _ {1}$ 等于 $0$，要使 $a _ {2}$ 等于 $0$，显然不能做 $i=2$ 的操作，只能做 $i=3$ 的操作让 $a _ {2}$ 等于 $0$。以此类推，要使 $a _ {x}$ 等于 $0$，必须做若干次 $i=x+1$ 的操作。我们只要枚举 $i$，最后判断 $a _ {n-1}$ 和 $a _ {n}$ 是否为 $0$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t,n,a[N];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int flag=1;
		for(int i=2;i<n;i++){
			if(a[i]-a[i-1]*2<0){
				flag=0;
				break;
			}
			a[i]-=a[i-1]*2;
			a[i+1]-=a[i-1];
			a[i-1]=0;
		}
		if(a[n-1]!=0||a[n]!=0)flag=0;
		if(flag)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：wuyin331 (赞：0)

# 题解
让我们先令 $a_{1}$ 为零，此时我们只能对 $a_{2}$ 进行操作。接下来我们令 $a_{2}$ 为零，假设我们对 $a_{2}$ 进行操作，那么此时 $a_{1}$ 的值将会改变，结果不优，因此我们只能对 $a_{3}$ 进行操作，重复上述操作，我们就能贪心令数组元素为零，接下来只需要判断下数组是否全部为零即可。

# 代码
```cpp
ll n, m, k, T, q;
ll nums[2000005];
ll A[1000005],B[1000005];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    T = 1;
    cin >> T;
 
    while (T--)
    {
        cin>>n;
        for(int i=1;i<=n;i++) cin>>nums[i];
 
        for(int i=2;i<=n-1;i++){
            if(nums[i-1]>0){
                ll tmp=nums[i-1];
                nums[i-1]=0;
                nums[i]-=tmp*2;
                nums[i+1]-=tmp;
            }
        }
        
        sort(nums+1,nums+1+n);
        if(nums[1]==nums[n]&&nums[1]==0){
            cout<<"YES"<<'\n';
        }
        else cout<<"NO"<<'\n';
    }
    return 0;
}
```

---

## 作者：Programming_Konjac (赞：0)

# 赛时思路
打暴力。

普通打暴力必然超时，所以需要用**线性时间复杂度**求解。

用 $i$ 从 $2 \rightarrow (n-1)$ 依次遍历，我们设当前这个数去减 $2$，然后左右两边的数去减一，那么减次数就显而易见了（因为都要减完，所以式子很好推）。

设 $k$ 为 $\min({a_{i-1},\lfloor\frac{a_i}{2}\rfloor,a_{i+1}})$（$\min$ 是为了防止出现任何一个数减了之后会出现负数），那么 $a_i$ 就应该减去 $2k$，左右两边的 $a_{i-1}$ 和 $a_{i+1}$ 都分别减去 $k$，然后进行下一次循环。

最后循环遍历，如果有 $a_i\ne 0(1\le i \le n)$ 的情况，那么就输出 `NO`，否则输出 `YES`。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[200005];
		for(int i=1; i<=n; i++){
			cin>>a[i];
		}
		int flag=0;
		for(int i=2; i<n; i++){
			int jjb=min(a[i]/2,min(a[i-1],a[i+1]));
			a[i-1]-=jjb;
			a[i+1]-=jjb;
			a[i]-=jjb*2;
		}
		for(int i=1 ;i<=n; i++){
			if(a[i]!=0){
				flag=1;
				break;
			}
		}
		if(flag) cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：GenesisCrystal (赞：0)

~~很简单~~

## Soulution

对于每个 $1 \le i < n - 1$ 的 $i$，如果 $a_i<0$，那么就是 `No`，否则，将 $a_{i+1} \gets a_{i+1}-2\times a_i$，$a_{i + 2} \gets a_{i+2}-a_i$。

然后判断 $a_{n-1}$ 和 $a_{n}$ 是不是 $0$，最后输出即可。

---

