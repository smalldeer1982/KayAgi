# Indivisible

## 题目描述

给定一个整数 $n$。

你需要构造一个一个长度为 $n$ 的排列 $A$，使得对于任意一对 $l,r$（$1\le l<r\le n$），都满足 $A_l+A_{l+1}+\dots+A_r$ 不可以被 $r-l+1$ 整除。

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
1 2
-1```

# 题解

## 作者：panxz2009 (赞：6)

## 题意简述
 - 构造一个长度为 $n$ 的排列 $A$，使得对于任意的 $l,r$（ $1 \le l < r \le n$）都满足 $A_l+A_{l+1}+⋯+A_r$ 不可以被 $r-l+1$ 整除。
 - 输出其中一种合法排列即可。
 
## 解题思路

构造题。考虑对 $n$ 进行分类讨论：

- 当 $n = 1$ 时，由样例即可得合法排列为 $1$。 
- 当 $n$ 为大于 $1$ 的奇数时，因为 $n-1$ 和 $n+1$ 必然能被 $2$ 整除，故不论 $A$ 如何排列，只需取 $l=1,r=n$，必有
$$\begin{aligned}
  A_l+A_{l+1}+⋯+A_r &= A_1+A_2+⋯+A_n \\
  &=\frac{n \times (n+1)}{2}
\end{aligned}$$
被 $r-l+1=n$ 整除。故程序输出 $-1$。

- 当 $n$ 为偶数时，先猜后证。

先猜测构造方案：

首先，取  $l=i,r=i+1$（其中 $1 \le i \le n-1$），则 
$$\begin{aligned}
  A_l+A_{l+1}+⋯+A_r &= A_i+A_{i+1} 
\end{aligned}$$
如果 $A_i,A_i+1$ 同奇偶，则上式为偶数，有可能会被 $n$ 整除。

所以 $A_i,A_i+1$ 奇偶性不同（其中 $1 \le i \le n-1$）。

其次，取 $l=i,r=i+2$（其中 $1 \le i \le n-2$），则 
$$\begin{aligned}
  A_l+A_{l+1}+⋯+A_r &= A_i+A_{i+1}+A_{i+2}
\end{aligned}$$
同理分析可得排列 $A$ 不能出现 $3$ 个连续的数字。

综上所述，一种合法的排列 $A$ 必须满足以下两点：

1. 相邻的两个数奇偶性不同。
2. 不能出现 $3$ 个连续的数字。

则猜测答案为形如 $2,1,4,3,⋯,n,n-1$ 的排列。

再证明其正确性：

考虑分类讨论 $l,r$ 的奇偶性异同：
1. 当 $l,r$ 的奇偶性不同时，不妨 $l$ 为奇数，$r$ 为偶数，则
$$\begin{aligned}
  S_{l,r} &= A_l+A_{l+1}+⋯+A_r &= \frac{(l+r) \times (r-l+1)}{2}
\end{aligned}$$
因为 $l+r$ 为奇数，则
$ \frac{l+r }{2} $
一定不是整数，那么
$S_{l,r}$
一定不被 $r-l+1$ 整除。

2. 当 $l,r$ 的奇偶性相同时，则
$$\begin{aligned}
  S_{l,r} &= A_l+A_{l+1}+⋯+A_r &= \frac{(l+r) \times (r-l+1)}{2} \pm 1
\end{aligned}$$
与上一种情况相反，因为 $l+r$ 为偶数，则
$ \frac{l+r }{2} $
是整数，那么
$$(r-l+1)\times (\frac{l+r }{2})$$
被 $r-l+1$ 整除。
则所求 $S_{l,r}$ 不被 $r-l+1$ 整除。

证毕！
## 代码实现
~~很简单，就不放了~~

---

## 作者：wei2013 (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF1818B)
## 题目大意：
构造长度为 $n$ 的数列，使得任何区间的和都不能被项数整除，问是否可以成功构造，不成功输出 $-1$，反之输出任意一个合法数列。
## 思路：
首先，我们知道各项数据之和公式是：
$$\frac{n \times (n+1)}{2}$$

变形之后，为：
$$n \times \frac{n+1}{2}$$
当 $n$ 为**非一奇数**，项数为 $n$ 时，明显无法构造，故输出 $-1$。

然后，先猜一手构造方案：

若第 $i$ 项为奇数输出 $i+1$，反之输出 $i-1$。

考虑 $n$ 为偶数的情况：

**奇偶性相同**：

一段的区间和是：

$$(l+r) \times \frac{(r-l+1)}{2}$$
因奇数 $+$ 偶数 $=$ 奇数，所以满足猜测的构造方案。

**奇偶性不同**：

奇数 $+$ 奇数 $=$ 偶数，偶数 $+$ 偶数 $=$ 偶数。
所以，区间和为：
$$\frac{(l+r)}{2} \times (r-l+1) \pm 1$$
也满足猜测的构造方案，所以猜测的构造方案是可行的。

注意：题目中提到 $1 \le n$，需要特判，输出 $1$ 即可。
## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        if(n==1){
        	cout<<1<<endl;
        	continue;
		}else if(n%2==1){
            cout<<-1<<endl;
            continue;
        }
        for(int i=1;i<=n;i++){
            if (i%2==1){
                cout<<i+1<<" ";
            }else{
                cout<<i-1<<" ";
            }
        }
        cout<<endl;
    }   
    return 0; 
}
```
望审核通过！

---

## 作者：Dream_poetry (赞：2)

### 思路：
有一定的思维难度，不过简单地说，分类讨论就行了。

首先，当 $n=1$ 时，输出 $1$ 即可。



------------


然后，当 $n$ 为非 $1$ 的奇数时，输出 $-1$。

#### 证明：

当 $n$ 为非 $1$ 奇数时，据初中老师传授的知识，$A$ 序列的各项元素之和为 $\frac{n \times (n+1)}{2}$，自然而然地，可变为 $n \times \frac{n+1}{2}$，当我们取 $l=1$，$r=n$ 时，自然无法符合要求，所以输出 $-1$。



------------


最后，我们来考虑当 $n$ 是一个偶数的情况。

第一，我们要保证 $A$ 中相邻的两个数的奇偶性不同，不然取相邻两个数就会不符合题意。

第二，我们也不能出现 $3$ 个连续的数字，不然取三个数字时也会和题意不符。

在满足以上两个条件的情况下，我们可以简单打表一下，结果如下：

输入：

```cpp
4
6
8
```

输出：

```cpp
2 1 4 3
2 1 4 3 6 5
2 1 4 3 6 5 8 7
```
就以上结果而言，我们显然已经推出了排列答案：当 $i$ 为奇数时，$A_i$ 为 $i+1$，当 $i$ 为偶数时，$A_i$ 为 $i-1$。

接下来，我们来分两种情况来论证一下：

1. 奇偶性不同

2. 奇偶性相同

当**奇偶性不同**时，某一段区间的和是 $\frac{(r-l+1) \times (r+l)}{2}$。

由于 $l$ 和 $r$ 奇偶性不同，所以 $(r-l+1)$ 必然的是一个偶数。所以，这段区间的答案就是 $(r+l) \times \frac{(r-l+1)}{2}$，又因为 $r$ 和 $l$ 奇偶性不同，所以我们上面的构造可以满足这种条件。

当**奇偶性相同**时，某一段区间和在 $l$ 和 $r$ 都是奇数或偶数时，分别为 $\frac{(r-l+1) \times (r+l)}{2}+1$，$\frac{(r-l+1) \times (r+l)}{2}-1$，又因为奇偶性相同，所以 $(r+l)$ 必然是一个偶数，答案变为  $(r-l+1) \times \frac{(r+l)}{2} \pm 1$，自然而然地，$(r-l+1)$ 整除自己，又因为 $\pm 1$，所以，我们的构造也能满足这种条件。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n;

signed main(){
	cin>>t;
	while (t--){
		cin>>n;
		if (n==1){
			puts("1");
		}
		else if (n%2==1){
			puts("-1");
		}
		else {
			for (int i=1;i<=n;i++){
				if (i%2==1){
					cout<<i+1<<' ';
				}
				else{
					cout<<i-1<<' ';
				}
			}
			puts("");
		} 
	}	
	return 0; 
}
```


---

## 作者：VitrelosTia (赞：2)

一道挺有意思的构造题。我们将 $n$ 分三类讨论。

$n = 1$ 时，显然只需要输出 `1` 即可。

$n$ 为其它奇数时，由于奇偶性，$n + 1$ 必然被 $2$ 整除，那么就有 $\sum\limits_{i = 1}^{n} A_i = \dfrac{n \times (n + 1)}{2} = n \times (\dfrac{n + 1}{2})$，显然被 $n$ 整除，所以此时一定不满足条件，输出 `-1`。

$n$ 为偶数时，构造 $2, 1, 4, 3 \cdots n, n - 1$ 的序列，接下来说明这种方式为什么是对的。

首先假如当题目中的 $l$ 和 $r$ 奇偶性不同时，容易推出 $\sum\limits_{i = l}^{r} A_i = \dfrac{(r - l + 1) \times (l + r)}{2}$，然后由于奇偶性，$r - l + 1$ 必然被 $2$ 整除， $l + r$ 必然不被 $2$ 整除，所以这个式子可以变为 $\dfrac{r - l + 1}{2} \times (l + r)$，再结合 $l + r$ 不被 $2$ 整除，这个式子显然不能被 $r - l + 1$ 整除。

当 $l$ 和 $r$ 奇偶性相同时，假如同时是奇数，容易推出 $\sum\limits_{i = l}^{r} A_i = \dfrac{(r - l + 1) \times (l + r)}{2} + 1$；假如同时是偶数，容易推出 $\sum\limits_{i = l}^{r} A_i = \dfrac{(r - l + 1) \times (l + r)}{2} - 1$。由于奇偶性，$l + r$ 必然被 $2$ 整除，于是 $\dfrac{(r - l + 1) \times (l + r)}{2} = \dfrac{l + r}{2} \times (r - l + 1)$，显然被 $r - l + 1$ 整除，所以易知这里的两种情况都是不被 $r - l + 1$ 整除的。

所以这种构造必然正确。

```cpp
void solve() {
    scanf ("%d", &n);
    if (n == 1) { cout << 1 << '\n'; return; }
    if (n & 1) { cout << -1 << '\n'; return; }
    for (int i = 2; i <= n; i += 2) cout << i << ' ' << i-1 << ' ';
    putchar(10);
}
```

---

## 作者：zdq20110120 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1818B)

### 题意
- 构造一个长度为 $n$ 的序列 $A$，使得对于任意的 $l$,$r$（$1 \le l \le r \le n$）都满足 $A_l + A_{l+1} + \dots + A_r $ 不可以被 $r - l + 1$ 整除。
- 输出其中一种排列即可。

### 思路
- 如果 $n = 1$，显然只需输出 $1$。
- 因为所有项的和为 $\frac{n \times (n + 1)}{2}$，拆分等于 $n \times \frac{n + 1}{2}$，为 $n$ 的倍数，故当 $n$ 为非 $1$ 的奇数时无解，输出 $-1$。
- 若 $n$ 为偶数，则当 $i$ 为偶数时，$a_i = i - 1$，否则 $a_i = i + 1$。

### 论证
若 $l$ 和 $r$ 奇偶性不同，则区间和为 $(r + l) \times \frac{r - l + 1}{2}$，因为 $l$ 和 $r$ 的奇偶性不同，所以 $l + r$ 为奇数，满足题目条件。

若 $l$ 和 $r$ 奇偶性相同，则区间和可表示为 $(r - l + 1) \times \frac{l + r}{2} - 1$，必定不是 $r - l + 1$ 的倍数，满足题目条件。
 
 ### 代码
 
 ```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5 + 5;
int t, n;
int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		if (n == 1) {
			printf("1\n");
			continue;
		}
		if (n & 1) {
			printf("-1\n");
			continue;
		}
		for (int i = 1; i <= n; i++)
			if (!(i & 1)) printf("%d ", i - 1);
			else printf("%d ", i + 1);
		printf("\n");
	}
	return 0;
}
 ```

---

## 作者：lgydkkyd (赞：1)

将这道题之前先给大家普及一下高斯求和公式：求 $x+(x+1)+(x+2)+...+(y-1)+y$ 的和可以转化成 $\lfloor (x+y)\times(y-x+1)/2 \rfloor$。


------------
然后进入正文，看完题目后可以得知，本题是一道构造题，还是大家最熟悉的分类讨论，当 $n$ 为一时，该序列只能为一这一个数，当 $3\le n$ 且 $n$ 为奇数时，本组数据无解，原因如下：题目明确要求对于任意 $l$ 和 $r$ 满足从第 $l$ 项至第 $r$ 项的和不为 $r-l+1$ 的倍数，那么当 $l$ 为一，而 $r$ 为 $n$ 时，第 $l$ 项至第 $r$ 项的和为 $\lfloor (1+n)\times n/2 \rfloor$ ，如果 $n$ 为奇数，则所有项之和一定为 $n$ 即 $1+n-1$ 的倍数，则无解。


------------
剩下的情况就是 $n$ 为偶数，无论 $l$ 和 $r$ 的奇偶性是否相同都存在合法解，于是开始构造序列，当 $i$ 为奇数时输出 $i+1$ 否则输出 $i-1$。
# Code
```cpp
#include<bits/stdc++.h>//万能头最好啦 
using namespace std;
int t,n;
int main(){
    scanf("%d",&t);
    while(t--){//t组数据 
        scanf("%d",&n);//输入n 
        if(n==1){//特判当n为1时 
            printf("1\n");//该序列只能为1 
        }
        else if(n%2==1){//当n为大于1的奇数时 
            printf("-1\n");
        }
        else{//n为偶数时 
        	for(int i=1;i<=n;i++){
            	if(i%2==0)printf("%d ",i-1);//i为偶数 
            	else printf("%d ",i+1);//i为奇数 
        	}
        	printf("\n");//换行 
		}
    }
    return 0;//华丽结束~~~ 
}
```

---

## 作者：tmpliyijiang (赞：1)

## 思路
对 $n$ 分类讨论：

1. $n=1$

$1$ 显然是一个合法排列。

2. $n\in \{ 2x+1\mid x\in N_{+} \}$

取 $l=1,r=n$，有

$$\begin{aligned} \sum_{i=l}^{r}a_i&=\sum_{i=1}^{n}a_i\\ &=\frac{n(n+1)}{2}\\&=\frac{n+1}{2}\cdot n\\&=\frac{n+1}{2}\cdot (r-l+1)\end{aligned}$$

故无解。

3. $n\in \{2x\mid x\in N_{+}\}$

构造数列 
$$a_i(i\in [1,n]\cap N_+ )=\begin{cases}i+1(i\bmod 2=1)\\i-1(i\bmod 2=0)\end{cases}$$

令 $k=r-l+1$
1. $k\in \{ 2x\mid x\in N_{+} \}$

$$\therefore l+r\in \{ 2x+1\mid x\in N_{+} \}$$
$$\begin{aligned} \sum_{i=l}^{r}a_i&=\frac{r(r+1)}{2}-\frac{l(l-1)}{2}\\&=\frac{r^2+r-l^2+l}{2}\\&=\frac{(r-l)(l+r)+(l+r)}{2}\\&=\frac{l+r}{2}\cdot k\end{aligned}$$

而 $\frac{l+r}{2}\notin N_+$，故合法。

2. $k\in \{ 2x+1\mid x\in N_{+} \}$

$$\therefore l+r\in \{ 2x\mid x\in N_{+} \}$$

- $l\in \{ 2x+1\mid x\in N_{+} \},r\in \{ 2x+1\mid x\in N_{+} \}$

$$\sum_{i=l}^{r}a_i=\frac{l+r}{2}\cdot k+1$$

$$\because\frac{l+r}{2}\in N_+$$

$$\therefore (\sum_{i=l}^{r}a_i) \bmod k =1$$

故合法。

- $l\in \{ 2x\mid x\in N_{+} \},r\in \{ 2x\mid x\in N_{+} \}$

$$\sum_{i=l}^{r}a_i=\frac{l+r}{2}\cdot k-1$$

$$\because\frac{l+r}{2}\in N_+$$

$$\therefore (\sum_{i=l}^{r}a_i) \bmod k =k-1$$

故合法。

证毕。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	scanf("%d",&t);
	for(register int i=0;i<t;i++){
		scanf("%d",&n);
		if(n==1)printf("1\n");
		else if(n&1)printf("-1\n");
		else{
			for(register int j=1;j<=n;j++){
				if(j%2==0)printf("%d ",j-1);//不知为何，写 j&1==0 会 WA
				else printf("%d ",j+1);
			}
			printf("\n");
		}
	}
	return 0;
}

```

---

## 作者：NRDI (赞：1)

### 思路

首先呢，如果 $n = 1$ 那么输出 $1$。

然后，如果 $n$ 为不是 $1$ 奇数，那么就无解，输出 $-1$。

因为，所有项的和为 $\frac{n \times (n + 1)}{2}$，等于 $n \times \frac{n + 1}{2}$，为 $n$ 的倍数，不满足。

若 $n$ 为偶数，则当 $i$ 为偶数时，$a_i$ 取 $i - 1$，否则取 $i + 1$。

先论证 $l$ 和 $r$ 奇偶性不同的情况。

区间和为 $(r + l) \times \frac{r - l + 1}{2}$，由于 $l$ ， $r$ 奇偶性不同，所以 $l + r$ 为奇数，满足条件；

如果奇偶性相同，则设他们同为奇数，区间和为 $(r - l + 1) \times \frac{l + r}{2} - 1$，不为 $r - l + 1$ 倍数，满足。

## 代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

int t, n;

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        if (n % 2 == 1) {
            cout << -1 << endl;
            continue;
        }
        for (int i = 1; i <= n; i++) {
            if (i % 2 == 0) cout << i - 1 << " ";
            else cout << i + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# Solution
**题目大意**：给定一个整数 $n$。你需要构造一个一个长度为 $n$ 的排列 $A$，使得对于任意一对 $l$，$r$（$1\le l<r\le n$），都满足 $A_l+A_{l+1}+\dots+A_r$ 不可以被 $r-l+1$ 整除。

**思路**：其实这就是一道~~纯粹的~~**构造题**，分类讨论即可。

1. 即 $n=1$，那么就直接输出 $1$ 并跳出循环。
2. 考虑**无解**情况：当 $n$ 为非 $1$ **奇数**时，则无解，输出 $-1$ 并跳出循环。**解释**：由求和公式知：该序列的和为 $\frac{n\times(n+1)}{2}$，化简后得$n\times\frac{n+1}{2}$ 必然可被 $n$ 整除，故排除。
3. 若 $n$ 为**偶数**必须要保证相邻两数奇偶性不同。如果奇偶性相同，任意取相邻两个数，就会有 $(n-1)+(n+1) \div 2 =0$ 不满足要求。

**代码**：
```cpp
#include<iostream>
using namespace std;
int n,t;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		if (n==1){cout<<"1"<<endl;continue;}
		else if(n%2==1){cout<<"-1"<<endl;continue;}
		else{
			for(int i=1;i<=n;i++){
				if (i%2==1)cout<<i+1<<' ';
				else cout<<i-1<<' ';
			}
			cout<<""<<endl;
		} 
	}	
	return 0; 
}
```


---

## 作者：_QyGyQ_ (赞：0)

## 思路
运用了分类讨论的思想。首先思考当数列项数为奇数的时候，数列的总和为 $n(n+1) \div 2$ 是数列的项数的个数，所以无解。但是要特判项数为一的情况。然后在思考项数为偶数的时候。当项数为偶数，必须要保证相邻两数奇偶性不同。如果奇偶性相同，任意取相邻两个数，就会有 $(n-1)+(n+1) \div 2 =0$ 不满足要求。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
using ll=long long;
const int N=1e6+7;
int n;
int a[N];
void solve(){
	if(n%2!=0){
		if(n==1){
			cout<<1<<"\n";
			return ;
		}
		cout<<-1<<"\n";
		return ;
	}
	for(int i=1;i<=n;i++){
		a[i]=i;
	}
	for(int i=1;i<=n;i++){
		if(i%2==0) cout<<a[i-1]<<" ";
		else cout<<a[i+1]<<" "; 
	}
	puts("");
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		solve();
	}
	return 0;
} 
```


---

