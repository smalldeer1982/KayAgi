# Asuna and the Mosquitoes

## 题目描述

在 Asuna 生日时，她的 $n$ 位仰慕者每人赠送了一座塔。第 $i$ 位仰慕者赠送的塔高度为 $a_i$。

Asuna 将礼物的美观度定义为 $\max(a_1, a_2, \ldots, a_n)$。她可以执行以下操作任意次数（包括零次）：

- 选择满足 $1 \leq i \neq j \leq n$ 的两个下标，使得 $a_i + a_j$ 为奇数且 $a_i > 0$。随后将 $a_i$ 减少 $1$，并将 $a_j$ 增加 $1$。

容易验证，在操作过程中塔的高度始终保持非负。请帮助 Asuna 求出经过任意次操作后可能达到的最大美观度。

## 说明/提示

第一个测试用例中，没有满足操作条件的塔对，因此无法进行任何操作。此时答案为 $\max(5, 3, 9) = 9$。

第二个测试用例中，可以对 $i=2$ 和 $j=1$ 执行两次操作。操作后数组变为：$a = [5, 0]$，因此答案为 5。

第三个测试用例中，可以执行以下操作序列：

1. 对 $i=1$ 和 $j=2$ 执行操作：  
   $$[1, 2, 2, 1] \quad \rightarrow \quad [0, 3, 2, 1]$$
2. 对 $i=3$ 和 $j=2$ 执行操作：  
   $$[0, 3, 2, 1] \quad \rightarrow \quad [0, 4, 1, 1]$$
3. 对 $i=3$ 和 $j=2$ 执行操作：  
   $$[0, 4, 1, 1] \quad \rightarrow \quad [0, 5, 0, 1]$$

此时 $\max(0, 5, 0, 1) = 5$，因此答案为 5。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
3
5 3 9
2
3 2
4
1 2 2 1
5
5 4 3 2 9```

### 输出

```
9
5
5
21```

# 题解

## 作者：LVFUyang1 (赞：2)

题意：给你一个数组，每次选一个奇数和一个偶数，然后使得其中一个 $+1$，另一个 $-1$，求可以得到的最大值。

一个奇数和偶数一直操作可以得到它们的和，也是一个奇数。那么只要有奇数就可以拿到所有偶数。同时我们可以让每个偶数和一个奇数操作使得奇数变成 $1$，偶数变成它们的和 $-1$。那么我们可以到达总和减奇数个数 $-1$ 的值。

非常显然，代码就非常容易实现了。



```
#include<bits/stdc++.h>
using namespace std;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		vector<int>a,b;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			if(x%2==1)
				a.push_back(x);
			else
				b.push_back(x);
		}
		sort(a.begin(),a.end(),greater<int>());
		sort(b.begin(),b.end(),greater<int>());
		if(a.empty()){
			cout<<b[0]<<'\n';
			continue;
		}
		if(b.empty()){
			cout<<a[0]<<'\n';
			continue;
		}
		long long ans=a[0];
		for(int i=0;i<b.size();i++)
			ans+=b[i];
		for(int i=1;i<a.size();i++)
			ans+=a[i]-1;
		cout<<ans<<'\n';
	} 
} 
```

---

## 作者：Zskioaert1106 (赞：2)

题目传送门：[CF2092C Asuna and the Mosquitoes](https://www.luogu.com.cn/problem/CF2092C)

### 做题过程

对于所有偶数，可以把所有奇数“吸”过来，但是为了能被一个奇数所用，所以可以“吸”得奇数都变成 $1$（这样自己还是偶数）。当所有奇数都变成了 $1$，可以让一个 $1$ 把所有的偶数都“吞掉”，这样即可得到最大值。

因为两个奇数之间不能互相合并，奇数加偶数还是奇数，因而最后奇数数量一定不变。而此时剩下一堆 $1$ 就是无效贡献最少的状态。

注意特判：当全奇或全偶时，无法合并。

### 代码实现

```cpp
#include<iostream>
using namespace std;
int main(){
	int t;
    cin>>t;
    while(t--){
    	int n,s1=0,s2=0,mx=0;
		long long sum=0;//不开龍竉……
    	cin>>n;
    	for(int i=1,a;i<=n;i++){
    		cin>>a;
    		(a&1)?s1++:s2++;
    		sum+=a,mx=max(mx,a);
		}
		if(s1&&s2)cout<<sum-s1+1<<'\n';//有一个奇数被充分利用了
		else cout<<mx<<'\n';//无法合并
	}
	return 0;
}
```

[AC on CF](https://codeforces.com/contest/2092/submission/313341231)。

---

## 作者：Chen_Johnny (赞：1)

# CF2092C Asuna and the Mosquitoes 题解
## 思路
首先，我们发现，要找两个和为奇数的数。根据小学数学，只有一个奇数和一个偶数加起来是奇数，所以考虑对奇数和偶数分类。

为了创造最大值，我们想到的方法是贪心。选择一个奇数 $a$ 和一个偶数 $b$。我们假设将 $a + 1$ 并将 $b - 1$，因为此时两数的总和不变还是奇数，所以不难发现可以将两数变为：$0, a + b$。

对于一个数组 $a$ 可以分为一个奇数数组 $p$ 和一个偶数数组 $q$。先取一个 $p_i,q_i$，变为 $0,p_i+q_i$ 并将 $p_i + q_i$ 置入 $p$ 中。然后再取一个 $p_i,q_i$，变为 $1, p_i + q_i - 1$ 并将 $p_i + q_i - 1$ 置入 $q$。如此往复，最后除了一个 $q$ 中的偶数都会变成 $1$，而 $p$ 中的奇数都会变成 $0$。而这个并没有变成 $1$ 的数就是答案。

因此得到通向式子：
$$Ans = 1 + \sum_{i\isin p} {(i - 1)} + \sum_{i\isin q}{i}$$
## 代码
思路都这么明确了，只需要照着写就行了哦！

---

## 作者：potata111 (赞：1)

## [_CF2092C_](https://www.luogu.com.cn/problem/CF2092C) Asuna and the Mosquitoes

### 题目大意

牢 Asuna 过生日，他的~~牢九门~~朋友们给他送来 $n$ 个塔。  
每个塔都有一个高度 $A$。

牢 Asuna 认为这些塔的 _美观度_ 是**最高塔的塔高**，  
即 $\max(A_1,\ A_2,\ A_3,\ \dots \ ,A_{n-1},\ A_n)$。

现在，牢 Asuna 可以**选定**两个下标 $i, j$，满足：
$$
2 \nmid i + j;\ 1 ≤ i \neq j ≤ n.
$$
然后将 $A_i$ 减少 $1$、将 $A_j$ 增加 $1$。

这样的操作可以做无限次。  
~~因为牢 Asuna 乐此不疲。~~



---

### 输入

首行一个 $t\ (t ≤ 10^4)$，表示数据组数。

对于每组数据：  
首行一个 $n\ (n ≤ 2 \times 10^5)$，表示牢 Asuna 的~~牢九门~~朋友数。  
接下来一行有 $n$ 个数，是牢 Asuna 的~~牢九门~~朋友送给他的**塔的高度** $A$。

保证所有数据中的 $n$ 的总和不超过 $2 \times 10^5$。

### 输出

经过**若干次**（当然可以是 $0$ 次）操作后，牢 Asuna 可以欣赏到的最大**_美观度_**。



---

### 同余与奇偶性

观察题意，发现本题操作的前提就是**奇偶性**。  
我们预先了解一下关于同余与奇偶性的**小知识**。  
~~会的巨佬们就可以跳过这一部分啦~~
$$
\forall\ x \in \bold{Z}.
$$ 

一般地，$x \bmod q = p$ 表示 $x$ 除以 $q$ 的余数为 $p$，称之为取余。  
也可以写作 $x \equiv p \pmod q$，称之为同余。

特殊地，$x \bmod 2 = 1$ 表示 $x$ 是一个奇数；$x \bmod 2 = 0$ 表示 $x$ 是一个偶数。

进一步，**两数之和取余**等于**两数分别取余之和**：
  $$\forall\ a,b,q \in \bold{Z},$$
  $$(a + b) \bmod q = ((a \bmod q) + (b \bmod q)) \bmod q.$$

**同奇偶性**两数之和为偶数：
$$\ (a \bmod 2) = (b \bmod 2) \Leftrightarrow (a + b) \bmod 2 = 0.$$

具有**相异**的奇偶性的两数之和为奇数：
$$\\ (a \bmod 2) \neq (b \bmod 2) \Leftrightarrow (a + b) \bmod 2 = 1.$$

某个数加上或减去一个**奇数**，其奇偶性**改变**（**相邻**两自然数必然有**不同**的奇偶性）：
$$\forall\ x \bmod 2 = 1，(a\pm x) \neq a \pmod 2$$
若加减一个偶数，其奇偶性则**不变**：
$$\forall\ y \bmod 2 = 0，(a\pm y) \equiv a \pmod 2$$


---


### 分析题目

我们考虑通过奇偶性的特性求解。

无论怎样操作都不会改变数列 $A$ 中奇数与偶数的个数。

---

**证明**：我们通过调整法证明。

每次操作都会使得数列中的两个元素 $A_i$ 和 $A_j$ 变成 $A_i + 1$ 和 $A_j - 1$。

$$∵ (A_i + A_j) \bmod 2 = 1$$
$$∴ A_i \bmod 2 \neq A_j \bmod 2$$

即 $A_i$ 与 $A_j$ 具有不同的奇偶性，
而一个数加减一会改变其奇偶性。  

最终的结果就是：$A_i$ 和 $A_j$ 中的奇数变成偶数，偶数变成奇数。奇偶数的总数不变。

---

显然如果要使得 $A$ 的美观度最高，就要使得操作完成后只会剩下若干个 $1$ 和若干个 $0$ 以及一个极大的数，且 $0$ 和 $1$ 的个数尽可能高。

具体的实现方法：

考虑最大值初始的奇偶性：

最大值最初为奇数，则我们让一个偶数将所有奇数操作至 $0$ 或 $1$。钦定 $1$ 个奇数，确保其最终值为 $1$。通过这个 $1$ 与所有偶数作操作，直至它们变成 $0$ 或 $1$，记此时的最大值（奇数）为 $S_1$。

最大值最初为偶数，同理。我们让一个奇数先把所有偶数干掉，再让这个偶数去把所有的偶数干掉，记此时的最大值为 $S_2$。

显然，只有 $S_1$ 和 $S_2$ 是可能最大的。

故若干次操作后，~~牢九门~~朋友们给牢 Asuna 送的塔的最大美观度为 $\max(S_1, S_2)$。



---

### 代码


```cpp
#include<iostream>

#define ll long long
using namespace std;

const int Potata = 2e5 + 5;

int q;
int n;
ll arr[Potata];
ll odd, even;
int cnt;
ll dp[Potata];
ll ans;

void solve()
{
	cin >> n;

	odd = even = cnt = 0;

	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	for (int i = 1; i <= n; i++)
		(arr[i] & 1) ? (odd += arr[i]) : (even += arr[i]),
		cnt += (arr[i] & 1);

	for (int i = 1; i <= n; i++)
	{
		dp[i] = max(dp[i - 1], arr[i]);

		if (arr[i] & 1)
			dp[i] = max(dp[i], arr[i] + even);
		else
			dp[i] = max(dp[i], odd - cnt + ((cnt > 0) ? (1) : (0)) * (1ll + even));
	}

	ans = -1;
	for (int i = 1; i <= n; i++)
		ans = max(ans, dp[i]);

	//	cout << "Answer is here: "; 考场没注释调了至少五分钟 真的糖丸了
	cout << ans << '\n';
}

int main()
{
	cin >> q;

	while (q--)
		solve();

	return 0;
}
```

---

## 作者：zyen11451425 (赞：1)

# [CF2092C Asuna and the Mosquitoes](https://www.luogu.com.cn/problem/CF2092C)

## 思路

题目中由：

- 选择满足 $1 \le i = j \le n$ 的两个下标，使得 $a_i + a_j$ 为奇数且 $a_i > 0$。随后将 $a_i$ 减少 $1$，并将 $a_j$ 增加 $1$。

可知，要将两个数（$a_i$ 和 $a_j$）之间进行操作，它们的奇偶性需要不同。

考虑统计塔高中的奇数和偶数进行处理。

```cpp
cin>>a;
if(a%2)ji++;
else ou++;
```

在一个奇数和一个偶数之间，可以将偶数加上奇数减一，让奇数变为 $1$，既保持两数奇偶性，又使偶数的值最大化。

最后，所有的奇数都被这个偶数“剥削”成 $1$，被完全榨干。

但是！

一个 $1$ 一跃而起，将所有偶数合并，成为了最大值，也就是答案。

当然，如果所有数奇偶性相同，就无法执行上述操作，特判输出其中最大值。
## 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
const int N=2e5+5;
using namespace std;
ll t,n,a,cnt,ans,ji,ou;//不开 long long 见祖宗
int main(){
    cin>>t;
    while(t--){
    	cin>>n;
        ji=0,ou=0,cnt=0,ans=0;
    	for(int i=1;i<=n;i++){
    		cin>>a;
    		if(a%2)ji++;
            else ou++;
    		cnt+=a,ans=max(ans,a);
		}
		if(ji&&ou)cout<<cnt-ji+1<<'\n';
		else cout<<ans<<'\n';
	}
	return 0;
}
```

[AC on codeforces](https://codeforces.com/contest/2092/submission/314477102)

---

## 作者：K_J_M (赞：1)

# CF2092C Asuna and the Mosquitoes

## 题目描述

在 Asuna 生日时，她的 $n$ 位仰慕者每人赠送了一座塔。第 $i$ 位仰慕者赠送的塔高度为 $a_i$。

Asuna 将礼物的美观度定义为 $\max(a_1, a_2, \ldots, a_n)$。她可以执行以下操作任意次数（包括零次）：

- 选择满足 $1 \leq i \neq j \leq n$ 的两个下标，使得 $a_i + a_j$ 为奇数且 $a_i > 0$。随后将 $a_i$ 减少 $1$，并将 $a_j$ 增加 $1$。

容易验证，在操作过程中塔的高度始终保持非负。请帮助 Asuna 求出经过任意次操作后可能达到的最大美观度。
## Solution
考虑贪心。

首先如果我们选择了一个奇数，那么我们可以找到所有的偶数，然后加上他们，原因是奇数加上偶数还是奇数。

如果我们选择了一个偶数，那么我们可以加上每一个奇数减去一个一，最后再加上一个一，然后加上所有偶数。原因是我们先加上每一个奇数减去一个一，保持了原本的奇偶性，然后加上一个一使变为奇数，然后按照上面的操作加上所有的偶数。

我们对于每一个数进行如上操作即可得到最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5+10;
int t,n,a[N];
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        int sum1=0,sum2=0,num1=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            if(a[i]%2==1){
                sum1+=a[i];
                ++num1;
            }else{
                sum2+=a[i];
            }
        }
        int ans=0;
        for(int i=1;i<=n;++i){
            ans=max(ans,a[i]);
            if(a[i]%2==0){
                ans=max(ans,sum1-num1+1ll*(num1>0)+sum2*(num1>0));
            }else{
                ans=max(ans,a[i]+sum2);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：ccxXF (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/CF2092C)
## 题目分析
希望审核大大给过。

这是一道一道模拟贪心题，满足 $1 \leq i \neq j \leq n$ 的两个下标，使得 $a_i + a_j$ 为奇数且 $a_i > 0$。随后将 $a_i$ 减少 $1$，并将 $a_j$ 增加 $1$。

我们可以判断每一个奇数和偶数的个数，再将每一个奇数都变成了 $1$，就是最大值了，只需要判断一开始的两个数是否是**一奇一偶**即可。（比如，$2$ 和 $3$，无论 $2$ 给多少给 $3$，它们的总和都是 $5$，是一个奇数）

还有一点，如果数列中**全部是奇数**或**全部是偶数**时，需要特判，因为不能合并，输出最大值即可。

知道了思路后，就可以轻松写出代码了。
## 题目代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
signed main(){
	int t;
    speed;
    cin>>t;
    while(t--){
    	int n,s1=0,s2=0,mx=0;
		int sum=0;
    	cin>>n;
    	for(int i=1,a;i<=n;i++){
    		cin>>a;
    		(a&1)?s1++:s2++;
    		sum+=a,mx=max(mx,a);
		}
		if(s1&&s2)cout<<sum-s1+1<<'\n';
		else cout<<mx<<'\n';
	}
	return 0;
}
```

---

## 作者：wcy110614 (赞：0)

先说结论：

所有数的和减去奇数个数加一。

当所有数同奇偶的时候，输出最大的数。

为什么呢？

首先发现两个不同奇偶的数可以相互一直操作下去，因为两边和不变，一直是奇数。在没有外来的数的参与的情况下，两个同奇偶的数永远都不能操作。

那么只要有偶数，用最大的奇数先和其中一个偶数操作一下，然后把所有的奇数都操作得只剩下 $1$，这个时候显然没有改变奇偶。

最后再操作一下一个奇数变成原本的奇数，把所有的偶数全操作完。

因为多记了一下操作的那个奇数，少记了一下操作的那个偶数，所以抵消了，而最开始你操作的那个奇数不能记上，所以加上一。

现在操作完的那个数就是最终答案。

代码（因为没有推结论所以体现了过程）

```cpp
// chk out LAST
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,INF=1e9+7;
int tt,n,c1,c2,mx,mxo;
int a[N];
inline void work(){
	cin>>n,c1=c2=mx=mxo=0;
	for(int i=1;i<=n;++i){
		cin>>a[i],c1+=(a[i]&1);
		if(a[i]&1)mxo=max(mxo,a[i]);
		mx=max(mx,a[i]);
	}
	c2=n-c1;
	int mxmx=mxo;
	if(!c1||!c2)return cout<<mx<<"\n",void();
	for(int i=1;i<=n;++i){
		if((a[i]&1)&&(mxmx!=a[i]))mxo+=a[i]-1;
		else if(a[i]&1)mxmx=0; 
		else if(a[i]>2&&(!(a[i]&1)))mxo+=a[i]-2;
	}
	--c1;
	return cout<<mxo+(c2<<1)<<"\n",void();
}
signed main(){
	cin>>tt;
	while(tt--)work();
	return 0;
}
// CHKOUT:
// chk size of array.
// chk cases
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{55}$ 篇题解。

# $\mathbf{0x01}$ 承

每次找出数组中两个满足 $a_i\neq a_j>0$ 的数并 $a_i+1 \to a_i, a_j-1\to a_j$，求出若干次操作后数组元素的最大值。

# $\mathbf{0x02}$ 转

我们可以分奇偶判断：

- 如果数组中只有奇数或偶数，那么答案就是数组中元素的最大值；
- 此外找到数组中元素的最大值 $\text{mx}$ 并 $\text{mx}\to\text{ans}$ 之后，执行若干步如下操作：
  - 如果 $\text{mx}$ 为奇数，则加上最大的偶数；
  - 如果 $\text{mx}$ 为偶数，则加上最大的奇数；
- 如果此后数组中还有数（一定是全奇或全偶），则继续分 $\text{ans}$ 和剩下数的奇偶讨论。详见代码注释。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		vector<ll>a(n+1);
		priority_queue<ll>p,q;
		for(ll i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]%2)p.push(a[i]);
			else q.push(a[i]);
		}
		if(p.empty()){
//			cout<<"case 1: ";
			cout<<q.top()<<endl;
		}else if(q.empty()){
//			cout<<"case 2: ";
			cout<<p.top()<<endl;
		}else{
//			cout<<"case 3: ";
			ll ans=0;
			if(p.top()>q.top()){
				ans=p.top();
				p.pop();
			}else{
				ans=q.top();
				q.pop();
			}
			while(p.size()&&q.size()){
				if(ans%2){
					ans+=q.top();
					q.pop();
				}else{
					ans+=p.top();
					p.pop();
				}
			}
			if(p.size()){
				if(ans%2){
					while(p.size()){
						ans+=p.top()-1;
						//奇+偶=奇
						p.pop();
					}
				}else{
					ans+=p.top(),p.pop();
					//ans 是偶数，先加上一个最大的奇数
					while(p.size()){
						ans+=p.top()-1;
						p.pop();
					}
				}
			}else if(q.size()){
				if(ans%2){
					while(q.size()){
						ans+=q.top();
						//奇+偶=奇
						q.pop();
					}
				}else{
					while(q.size()){
						ans+=q.top()-1;
						q.pop();
					}
				}
			}
			cout<<ans<<endl;
		}
	}
}

```

---

