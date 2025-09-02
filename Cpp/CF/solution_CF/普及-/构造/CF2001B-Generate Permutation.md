# Generate Permutation

## 题目描述

There is an integer sequence $ a $ of length $ n $ , where each element is initially $ -1 $ .

Misuki has two typewriters where the first one writes letters from left to right, with a pointer initially pointing to $ 1 $ , and another writes letters from right to left with a pointer initially pointing to $ n $ .

Misuki would choose one of the typewriters and use it to perform the following operations until $ a $ becomes a permutation of $ [1, 2, \ldots, n] $

- write number: write the minimum positive integer that isn't present in the array $ a $ to the element $ a_i $ , $ i $ is the position where the pointer points at. Such operation can be performed only when $ a_i = -1 $ .
- carriage return: return the pointer to its initial position (i.e. $ 1 $ for the first typewriter, $ n $ for the second)
- move pointer: move the pointer to the next position, let $ i $ be the position the pointer points at before this operation, if Misuki is using the first typewriter, $ i := i + 1 $ would happen, and $ i := i - 1 $ otherwise. Such operation can be performed only if after the operation, $ 1 \le i \le n $ holds.

Your task is to construct any permutation $ p $ of length $ n $ , such that the minimum number of carriage return operations needed to make $ a = p $ is the same no matter which typewriter Misuki is using.

## 说明/提示

In the first testcase, it's possible to make $ a = p = [1] $ using $ 0 $ carriage return operations.

In the second testcase, it is possible to make $ a = p = [1, 2] $ with the minimal number of carriage returns as follows:

If Misuki is using the first typewriter:

- Write number: write $ 1 $ to $ a_1 $ , $ a $ becomes $ [1, -1] $
- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Write number: write $ 2 $ to $ a_2 $ , $ a $ becomes $ [1, 2] $

If Misuki is using the second typewriter:

- Move pointer: move the pointer to the next position. (i.e. $ 1 $ )
- Write number: write $ 1 $ to $ a_1 $ , $ a $ becomes $ [1, -1] $
- Carriage return: return the pointer to $ 2 $ .
- Write number: write $ 2 $ to $ a_2 $ , $ a $ becomes $ [1, 2] $

It can be proven that the minimum number of carriage returns needed to transform $ a $ into $ p $ when using the first typewriter is $ 0 $ and it is $ 1 $ when using the second one, so this permutation is not valid.

Similarly, $ p = [2, 1] $ is also not valid, so there is no solution for $ n = 2 $ .

In the third testcase, it is possibile to make $ a = p = [3, 1, 2] $ with $ 1 $ carriage return with both the first and the second typewriter. It can be proven that, for both typewriters, it is impossible to write $ p $ with $ 0 $ carriage returns.

With the first typewriter it is possible to:

- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Write number: write $ 1 $ to $ a_2 $ , $ a $ becomes $ [-1, 1, -1] $
- Move pointer: move the pointer to the next position. (i.e. $ 3 $ )
- Write number: write $ 2 $ to $ a_3 $ , $ a $ becomes $ [-1, 1, 2] $
- Carriage return: return the pointer to $ 1 $ .
- Write number: write $ 3 $ to $ a_1 $ , $ a $ becomes $ [3,1,2] $

With the second typewriter it is possible to:

- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Write number: write $ 1 $ to $ a_2 $ , $ a $ becomes $ [-1, 1, -1] $
- Carriage return: return the pointer to $ 3 $ .
- Write number: write $ 2 $ to $ a_3 $ , $ a $ becomes $ [-1, 1, 2] $
- Move pointer: move the pointer to the next position. (i.e. $ 2 $ )
- Move pointer: move the pointer to the next position. (i.e. $ 1 $ )
- Write number: write $ 3 $ to $ a_1 $ , $ a $ becomes $ [3, 1, 2] $

## 样例 #1

### 输入

```
3
1
2
3```

### 输出

```
1
-1
3 1 2```

# 题解

## 作者：Program_A2 (赞：1)

## 思路：
先构造一些数进行模拟，不难看出，本题当 $n$ 为偶数时，没有正确的数列，相反，当 $n$ 为奇数时，则中间数为 $1$，先右边比它大 $1$，然后左边又比他大 $2$，然后最右边又来了个比他大 $3$ 的数……以此类推，便有了下面的代码。

## 代码：

```
#define IOI return
#define AK 0
#define ME ;
#include <bits/stdc++.h>
using namespace std;
int n[501];
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)cin>>n[i];
	for(int i=1;i<=t;i++){
		int ci=1;
		int jia=0;
		int v=n[i];
		if(n[i]%2==0){
			cout<<-1<<endl;
			continue;
		}
		cout<<v<<" ";
	   for(int l=n[i]-1;ci!=n[i];l--){
	   	ci++;
	   	if(jia==0){
			  v-=l;	
			  jia++;
		}else{
			v+=l;
			jia--;
		}
		cout<<v<<" ";
	   }
	   cout<<endl;
	}
	IOI AK ME
}
```

---

## 作者：zlqwq (赞：1)

如果序列长度为 $1$，那么显然满足，不需要纠结。

如果输入的 $n$ 为偶数，那么也不需要纠结，一定无解。

至于其他情况，我们看第三个样例，中间一个 $1$，接下来右边一个 $2$，这样就不均衡了，因此左边要有一个 $3$，这样就均衡了。

因此我们要构造距离起点两端的数都尽量差值较小的序列。


```cpp
void solve() {
	if(n % 2 == 0) cout << -1;
	else {
		int s = n,l = 1,r = n;
		while(l < r) {
			a[l] = s--;
			a[r] = s--;
      l++;
      r--;
		}
		a[l] = s++;
		for(int i = 1;i <= n;++i) cout << a[i] << " ";
	}
}
```

---

## 作者：Magallan_forever (赞：1)

#### 简要说明题意：

有一个 $n$ 项的数列（初始值均为 $-1$），可以选择从左到右或从右到左两种填写方式将数列填写为 $\{1, 2, \ldots, n\}$ 的一个排列，填写过程中有三项操作可以执行：

1. 若当前数为 $-1$，在这个位置填一个未出现的最小正整数。
2. 将填写位置挪回填写开始时的位置。
3. 若未到数列末尾，向填写方向移动 $1$。

要求数列使得两种填写方式的最小操作 $2$ 数量相同。

#### 题目分析：

先考虑一下什么情况下我们会使用操作 $2$。假定我们总在一个已经填过数的位置使用操作 $2$。（对于未填过的位置，可以等价为在最后一个填数位置使用操作 $2$）

使用操作 $2$ 会回到开始填写的位置，并且一定会在使用位置和开始填写位置之间填写一个（更大的）数，否则该操作无意义。也就是说，**当我们需要在前置位填写更大数时，我们需要一次操作 $2$。**

那么题目就转化为了：构建 $\{1, 2, \ldots, n\}$ 的一个排列 $a$，满足若 $a_{b_i}=i$，则 $\{i|b_i<b_{i+1},i \in \{1, 2, \ldots, n-1 \}\}$，$\{i|b_i>b_{i+1},i \in \{1, 2, \ldots, n-1\}\}$ 两集合元素数相等。

更具象一点：你要构建 $\{1, 2, \ldots, n\}$ 的一个排列 $a$，构造完成之后，对于 $i \in \{1, 2, \ldots, n-1\}$，画从 $i$ 指向 $i+1$ 的箭头，要求你的左右箭头数量相等。 

![](https://cdn.luogu.com.cn/upload/image_hosting/ne5z2u7c.png)

对于奇数，箭头的数量是偶数，我们可以均分，因此有解。观察样例可以~~注意到~~一种构造方式，在左右两侧依次拓展即可。

同理，对于偶数，无法均分箭头，则无解。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int T,n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        if(n&1){
            for(int i=n;i>=1;i-=2) printf("%d ",i);
            for(int i=2;i<n;i+=2) printf("%d ",i);
            putchar('\n');//奇数仿照样例输出
        }
        else printf("-1\n");//偶数无解
    }
    return 0;
}
```

---

## 作者：Ryan_Adam (赞：1)

## 题解：CF2001B Generate Permutation
### 标签
简单构造题
### 分析
可以从序列长度 $n=1$ 时开始考虑，很显然可以。

如何构造 $n>1$ 时呢？发现如果 $n=2$ 的话，$2$ 放到 $1$ 的左边或右边都会造成左打字机或右打字机多用一个回车，为了保持平衡，应该在 $2$ 的另一边加上 $3$。

我们很容易发现 $n$ 为偶数时一定输出 $-1$，$n$ 为奇数时则构造类似 $n,n-2,\cdots,5,3,1,2,4,\cdots,n-3,n-1$ 的序列。看样例也能很容易的猜出这个结论。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int a[N];
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        if (n % 2 == 0)
            cout << -1 << endl;
        else
        {
            int cnt = n, l = 1, r = n;
            while (l < r)
            {
                a[l] = cnt--;
                a[r] = cnt--;
                l++, r--; 
            }
            a[l] = cnt++;
            for (int i = 1; i <= n; i++)
                cout << a[i] << " ";
            cout << endl;
        }
    }
    return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路

先给结论：$n \bmod 2 = 0$ 时无解。否则 $p$ 序列从中心向两侧发散进行排列。

给出~~一个不太严谨的~~证明：

对于 $n = 1$ 的情况，有解。此时两台打字机的回车数为 $0$。

对于 $n = 2$ 的情况，无解。无论你把 $2$ 放在 $1$ 的哪一边，总会有一台打字机回车数比另一台多 $1$。

对于 $n = 3$ 的情况，有解。因为 $n = 2$ 的情况下有一台打字机回车数比另一台少 $1$，那么只需要把 $3$ 放在回车数较少的一边即可，这个差值就被“扳”回来了。所以有解。

一直递推，即可得证。

# AC 代码

[AC 记录（祭 RMJ）](https://codeforces.com/contest/2001/submission/286214746)

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n;
int main(){
	scanf("%d",&q);
	while(q--){
		scanf("%d",&n);
		if((n&1) == 0){
			printf("-1\n");
			continue;
		}
		for(int i = n; i >= 1; i -= 2){
			printf("%d ",i);
		}
		for(int i = 2; i <= n; i += 2){
			printf("%d ",i);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：mc_xiexie (赞：0)

### 思路

题意是构造一个排列，使得从任意打字机完成的回车操作次数相同。通过分析，我们发现排列的构造需要满足一定条件，以保证无论从左向右还是从右向左打字时，回车操作的次数是对称的。

我们可以通过交替构造排列来确保这种对称性。例如，当 $n$  为奇数时，可以从中心向两侧发散进行排列；而当 $n$ 为偶数时，直接给出无解（如 $n=2$ 这种情况）。

那么结论出来了，$n$ 为 $2$ 的倍数时无解，非 $2$ 的倍数时由中间轮流先左后右的加一。

---

## 作者：huanglihuan (赞：0)

### 思路

如果 $n \bmod 2 = 0$ 即 $n$ 为偶数，则无解，因为无法保持平衡。

否则，可以构造序列 $n,n - 2,n - 4,\ldots,3,1,2,4,\ldots,n - 3,n - 1$，可以证明此时的序列可以保持平衡满足要求。

### 代码：

```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 2e6 + 5,maxn = 3e3 + 5;
int a [N],b [N],s [N],f [N];
inline int read ()
{
	int x = 0;
	bool f = 1;
	char c = getchar ();
	while (c < '0' || c > '9') f = (c == '-' ? !f : f),c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return f ? x : -x;
}
inline void write (int x)
{
	if (x < 0) putchar ('-'),x = -x;
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
signed main ()
{
	int T;
	cin >> T;
	while (T --)
	{
		int n;
		cin >> n;
		if (! (n & 1)) puts ("-1");
		else
		{
			for (int i = n;i >= 1;i -= 2) cout << i << ' ';
			for (int i = 2;i <= n - 1;i += 2) cout << i << ' ';
			cout << endl;
		}
	}
	return 0;
}
```

---

## 作者：ReturnXI (赞：0)

我们需要构造一个长度为 $n$ 的排列 $p$，使得无论使用哪台打字机，执行操作所需的最小回车次数相同。
### 题目分析
有两台打字机：
1. 第一台从左到右。
2. 第二台从右到左。

每台打字机都能进行以下操作：
- 写入数字（仅当当前位置为 $ -1 $ 时写入最小未使用的正整数）。
- 回车（返回到初始位置）。
- 移动指针（根据打字机方向移动）。

为了保证无论使用哪台打字机，回车操作的次数都相同，我们首先观察可以构造哪些排列。

### 特殊情况
1. 当 $ n=1$ 时只有一个元素，输出  $[1]$。
2. 当 $n=2$ 时任何排列 $[1, 2]$ 或 $[2, 1]$ 都会导致不同的回车次数，因此输出 $-1$。
3. 当  $n=3$ 时可以构造 $[3, 1, 2]$，这样的排列在两个打字机中都需要一次回车。

### 一般化构造
对于 $n≥3$ 的情况，我们可以利用以下构造规则：
- $n$ 是奇数，输出顺序为 $n, 1, 2, ..., (n-1)$。
- 对于 $n$ 是偶数，输出 $-1$，因为不可能构造满足条件的排列。
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;  
    while (t--) {
        int n;
        cin >> n;  
        if (n == 1) {
            cout << 1 << '\n';  // 只有一个元素的情况
        } else if (n == 2) {
            cout << -1 << '\n';  // 不可能构造的情况
        } else if (n % 2 == 0) {
            cout << -1 << '\n';  // 偶数 n 的情况
        } else {
            // 奇数 n 的情况
            cout << n << ' ';  // 首先输出 n
            for (int i = 1; i < n; i++) {
                cout << i << ' ';  // 输出 1 到 n-1
            }
            cout << '\n';  // 换行
        }
    }
    return 0;
}

```

---

## 作者：GeXiaoWei (赞：0)

# CF2001B Generate Permutation
## 解析
先从 $n=1$ 考虑，显然可以。

观察题意可以发现：如果要打印数字的数量是偶数，那么一定存在一台打印机至少比另一台少两次换行，因为这一台在打印完任意一次后，都可以去打印最大的数字，便会省掉一个换行。

考虑奇数，我们可以用枚举打印出所有方案，然后我们就会发现：只需要将最大的数字排在第一位，再正序放置 $2$ 到 $\dfrac{n}{2}$，最后倒序放置 $n-1$ 到 $\dfrac{2}{n}+1$ 即可。

具体实现只需要使用两个指针即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a[200005],n,cnt,l,r;
int main(){
    scanf("%d",&t);
    while(t--){
    	scanf("%d",&n);cnt=n,l=1,r=n;
        if(n&1){
            while(l<r) a[l++]=cnt--,a[r--]=cnt--;
            a[l]=cnt++;
            for(int i=1;i<=n;i++) printf("%d ",a[i]);
            printf("\n");
        }else printf("-1\n");
    }return 0;
}
```

---

## 作者：jubaoyi2011 (赞：0)

作为一个蒟蒻，我一开始看这题感觉很懵逼。

但是，看一看样例，发现输入样例
```
3
1
2
3
```
最后输出的结果为
```
1
-1
3 1 2
```
这么一看，咦？输入 ```2``` 时无解，那么 $2$ 的倍数也无解喽，所以得出代码：

```cpp
if(n%2==0){
    cout<<-1<<endl;
    return 0;
}
```

可是凭什么 $2$ 的倍数就无解呢？试一试，首先是一个 $1$，要求长度为 $2$，那就再添加 $2$，长度够了，但是不平衡，其他偶数同理。

既然排除了偶数，那么就考虑奇数，由于我懒（~~来自数学老师的懒~~），所以就再看样例。

首先看一看样例的第一组数据，输入 ```1```
，输出 ```1```。这是肯定的，因为长度为 $1$，而要求最小，那么肯定是 $1$ 喽，所以又得出一段特判代码：

```cpp
if(n==1){
    cout<<1<<endl;
    return 0;
}
```

再看第三组数据，感觉很难（因为我菜），那么就只能推结论了。

首先在中间放一个 $1$，然后在右边放一个 $2$，这样不平衡了，就在在左边放一个 $3$，长度够了就输出。所以根据这个结论就可以得出输出部分的代码：

```cpp
int x=n;
int l=0,r=n;//左右端点
while(l<=r){
    a[l]=n--;//注意要写n--,如果写成--n就会先让n减一，而这样会先让a[l]=n,然后n再减一。
    a[r]=n--;//同上
}
a[l]=n++;
for(int i=1;i<=n;i++)cout<<a[i]<<' ';
```

---

## 作者：Even_If (赞：0)

codeforces 特有的思维构造题。

观察题意可以发现：如果要打印数字的数量是偶数，那么一定存在一台打印机至少比另一台少两次换行，因为这一台在打印完任意一次后，都可以去打印最大的数字，便会省掉一个换行。

考虑奇数，我们可以用 next_permutation 打印出所有方案，然后我们就会发现：只需要将最大的数字排在第一位，再正序放置 $2$ 到 $\dfrac{n}{2}$，最后**倒序放置** $n-1$ 到 $\dfrac{n}{2}+1$ 即可。

代码：
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e5 + 10;

int T;
int n;

signed main(void) {
	cin >> T;
	
	while (T --) {
		cin >> n;
		
		if(n & 1) {
			cout << n << ' ';//最大的放最前面
			
			for (int i = 1; i <= n / 2; i ++) cout << i << ' ';//正序放置
			
			for (int i = n - 1; i > n / 2; i --) cout << i << ' ';//倒序放置
			
			cout << endl;
		}
		
		else cout << -1 << endl;//如果是偶数个就不行
	}

	return 0;//好习惯
}
```

---

## 作者：clx201022 (赞：0)

### 思路
由[题面](https://www.luogu.com.cn/problem/CF2001B)可知，我们要构造一个长度为 $n$ 的序列 $p$ 使得无论使用哪个打字机，$a=p$ 所需的回车次数最小。  

先只考虑第一个打字机。  
因为我们可以把放置的数字理解成其为第几个进行写操作，如 $p_i=x$ 时，我们可以知道 $i$ 位置应为第 $x$ 个进行写操作。  
而我们需要进行回车当且仅当第 $x$ 进行写操作的位置不可以通过移动指针到达第 $x+1$ 个进行写操作的位置。  
因此最少回车操作的数量则是 $p$ **只考虑相邻数的逆序对对数**。  

考虑第二个打字机。  
对于第二个打字机，可以视为第一个打字机对反转过的 $p$ 进行操作，其的最少回车操作数为原 $p$ **只考虑相邻数的顺序对对数**。  
要求 $p$ 无论对哪个打字机的回车次数都是最小的，可以想到只要 $p$ **只考虑相邻数的逆序对对数**与**只考虑相邻数的顺序对对数**相等即可。  
因此，存在长度为 $n$ 的 $p$ 满足**只考虑相邻数的逆序对对数**与**只考虑相邻数的顺序对对数**相等即直接输出，不存在即输出 $-1$。  

经过简单的逻辑推理可知存在 $p=[n,n-2,\dots,5,3,1,2,4,\dots,n-3,n-1]$ 满足条件当且仅当 $n\bmod 2=1$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,bucket_a[101],ans;
void solve()
{
    cin>>n;
    if(n%2==0)
    {cout<<-1<<endl;return;}
    for(int i=n;i>=1;i-=2)cout<<i<<' ';
    for(int i=2;i<n;i+=2)cout<<i<<' ';
    cout<<endl;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        solve();
    }
    return 0;
}
```

---

