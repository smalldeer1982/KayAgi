# Ehab and the Expected XOR Problem

## 题目描述

Given two integers $ n $ and $ x $ , construct an array that satisfies the following conditions:

- for any element $ a_i $ in the array, $ 1 \le a_i<2^n $ ;
- there is no non-empty subsegment with [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) equal to $ 0 $ or $ x $ ,
- its length $ l $ should be maximized.

A sequence $ b $ is a subsegment of a sequence $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

## 说明/提示

In the first example, the bitwise XOR of the subsegments are $ \{6,7,4,1,2,3\} $ .

## 样例 #1

### 输入

```
3 5
```

### 输出

```
3
6 1 3```

## 样例 #2

### 输入

```
2 4
```

### 输出

```
3
1 3 1 ```

## 样例 #3

### 输入

```
1 1
```

### 输出

```
0
```

# 题解

## 作者：81179332_ (赞：4)

由于是连续子序列的限制，容易想到求原序列的前缀异或和序列

则转化为序列中任意两数的异或值不为 $0$ 或 $x$

直接贪心选即可，每选一个数，将 $i$ 和 $i\ \text{xor}\ x$ 标记为不可选，注意 $x$ 也不可选，因为 $x\ \text{xor}\ x=0$

最后还原原序列即可

```cpp
const int N = 1 << 19;
int n,x,a[N],cnt;
bool book[N];
int main()
{
	n = read(),book[x = read()] = 1;
	for(int i = 1;i < (1 << n);i++) if(!book[i])
		a[++cnt] = i,book[i ^ x] = book[i] = 1;
	fprint(cnt);
	for(int i = cnt;i;i--) a[i] = a[i] ^ a[i - 1];
	for(int i = 1;i <= cnt;i++) pprint(a[i]);
}

```

---

## 作者：灵茶山艾府 (赞：4)

说一个 $O(1)$ 空间复杂度的解法。

首先观察到当 $x\geq 2^n$ 时，无论怎么构造，是不会出现子数组异或和为 $x$ 的。在这种情况下，不妨考虑下一个元素为数组后缀异或和中的未出现元素的最小正值，比如现在数组为 $[1,2]$，后缀异或和为 $2,3$，那么构造出的下一个元素为 $1$.

通过简单的计算可以发现按照上述规则生成的数组就是 $lowbit(i)=i\&-i$.

接下来考虑 $x<2^n$ 的情况。考察 $x=1$，可以发现生成的数组只要没有奇数就不会出现异或和为 $1$，$x$ 为奇数，或者说 $x$ 的最低位为 1 的情况同理。

考察 $x=2$，那么类似上面的讨论，生成的数组元素$/2$ 后不是奇数就不会出现异或和为 $2$.

总结一下就是，若 x 的二进制表示中某一位为 $1$，而生成的数组元素的二进制表示该位均为 $0$，则不会出现子数组异或和为 $x$.

简单起见，不妨用 $lowbit(x)$ 来生成数组元素。记 $mask=lowbit(x)-1$，则数组的第 $i$ 个元素为 
$$ (lowbit(i) \&\sim mask) << 1\ |\ lowbit(i) \& mask $$

AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int lowbit(int x) { return x & -x; }

int main() {
    int n, x;
    cin >> n >> x;
    int m = 1 << n;
    if (x < m) {
        m >>= 1;
        cout << m - 1 << '\n';
        int mask = lowbit(x) - 1;
        for (int i = 1; i < m; i++)
            cout << ((lowbit(i) & ~mask) << 1 | lowbit(i) & mask) << " ";
    } else {
        cout << m - 1 << '\n';
        for (int i = 1; i < m; i++)
            cout << lowbit(i) << " ";
    }
    return 0;
}

```


---

## 作者：kal0rona (赞：2)

原文首发于：[Kalorona 的博客](https://kaloronahuang.com/oi/codeforces-1174dehab-and-the-expected-xor-problem-%e9%a2%98%e8%a7%a3/)。

# 主要思路

这道题还蛮妙的，自己比较顺利的思考出来了。

考虑设置前缀异或和$\{S_i\}$，根据异或按位处理的性质，显然对于所有的$S_i$都会小于$2n$。最后，我们可以把限制变成：

- 不存在两个相同的前缀和。
- 不存在一对前缀和，其异或值为$x$。

针对$x$的大小关系，我们可以分成两种情况：

- $x \geq 2n$，不存在一对$(S_i, S_j)$的异或为$x$，因为存在更高的位并不会被消除。
- $x < 2n$，我们发现每选择一个数作为前缀和，整个$2n$中就会少一个对应的可以被选择的数。所以，我们每次选一个作为$S_i$的数时，都要把$S_i \ xor \ x$打标记。

结合一下就可以了。

# 代码

```cpp
// CF1174D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = (1 << 18) + 200;

int n, x, seq[MAX_N];
bool vis[MAX_N];

int main()
{
    scanf("%d%d", &n, &x);
    if (x >= (1 << n))
    {
        int len = (1 << n) - 1;
        printf("%d\n", len);
        for (int i = 1; i <= len; i++)
            printf("%d ", i ^ (i - 1));
    }
    else
    {
        vis[x] = true;
        int tot = 0;
        for (int i = 1, last = 0; i < (1 << n); i++)
            if (vis[i] == false)
                vis[i ^ x] = true, seq[++tot] = i ^ last, last = i;
        printf("%d\n", tot);
        for (int i = 1; i <= tot; i++)
            printf("%d ", seq[i]);
    }
    return 0;
}
```


---

## 作者：lrj124 (赞：1)

思路比较巧妙，因为元素可重复不太好搞，就考虑构造一个答案序列 $a$ 的异或前缀和 $b$，且 $b$ 满足任意 $b_i \  xor \  b_j  \ \not= \  x$ 或 $0$。
因为若 $a \ xor \ b \ = \ c$，则 $a \ xor \ c \ = \ b$，所以从 $1$ 枚举到 $2^n-1$ ，每次用可行的 $i$ 数加入答案并排除 $i \ xor \ x$ 这个数。

## 代码
```cpp
/************************************************
*Author        :  lrj124
*Created Time  :  2019.10.15.19:28
*Mail          :  1584634848@qq.com
*Problem       :  cf1174d
************************************************/
#include <cstdio>
const int maxn = 1<<18;
int n,x,ans[maxn];
bool vis[maxn];
int main() {
	//freopen("cf1174d.in","r",stdin);
	//freopen("cf1174d.out","w",stdout);
	scanf("%d%d",&n,&x);
	vis[0] = vis[x] = true;
	for (int i = 1;i < 1<<n;i++)
		if (!vis[i]) {
			vis[i^x] = true;
			ans[++ans[0]] = i;
		}
	printf("%d\n",ans[0]);
	for (int i = 1;i <= ans[0];i++) printf("%d ",ans[i]^(i ^ 1 ? ans[i-1] : 0));
	return 0;
}
```

---

## 作者：dyx131313 (赞：1)

这场CF很显然出题人想把他搞成数学大赛，然后发现三题的人从900+到2000+。很多人都卡在了D题（包括我）。

 解题思路:

1、题目要求构造一个数组，使其长度最长，且一段区间内的数异或和不能为0或X。我们根据异或的一个特殊性质:一个数异或自己本身等于0。

即可以得出如下性质:设a为输出数组，b[i]为a中前i项的异或和，即b[i]=a[1]^a[2]^...^a[i]。则有 i<=j,a[i]^a[i+1]^a[i+2]^...^a[j]=(a[j]^a[j-1]^...^a[1])^(a[i]^a[i-1]^...^a[1])=b[j]^b[i-1]。

那我们可以把所有这样的判定都转换成异或前缀和的判定，题目可以转换成构造一个长度最大的数组使得其中任意两数异或和不为0或X。


2、那么如何构造呢？（蒟蒻的我就卡在这步）。要使两个数异或起来不为0，则这两数不相等。我们有观察到n的范围非常小，2的n次方小于等于262144(2的18次方)。

那么我们就可以把它枚举出来了因为对于一个数y，只有一个数z可以与其异或变为x(根据异或的定义，它也满足交换律和结合律。y^z=x,x^(y^z)=x^x=0,x^(y^z)=(x^y)^z=0=z^z,则有y^x=z)。

我们可以通过穷举，选择i，否定i^x。就可以求出最后的前缀数组b，进而通过b的定义求出输出数组a。

code:
```cpp
/*
ID: dyx_6661
TASK:
LANG: C++
*/
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<iostream>
#include<deque>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef string str;
typedef vector<int> vec;

const int n_size=1<<18+5;
int n,x,vis[n_size]; 
vector<int> ans;

int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	scanf("%d%d",&n,&x);
	ans.push_back(0);//0放进答案占个位，方便计算
	vis[x]=1;vis[0]=1;//0,x不可取
	for(int i=1;i<(1<<n);i++){
		if(!vis[i]){//拿i，否定i^x
			vis[i^x]=1;
			ans.push_back(i);
		}
	}
	printf("%d\n",ans.size()-1);//再把0去掉
	for(int i=1;i<ans.size();i++){
		printf("%d ",ans[i-1]^ans[i]);
	}
	return 0;
}

```

原codeforces英文题解[传送门](https://codeforces.com/blog/entry/67388)(往下拉)


---

## 作者：__LiChangChao__ (赞：1)

### 思路

首先异或有逆运算就是它本身。

由于其中不能有连续元素的异或和为 $0$ 或 $x$，则考虑算异或的前缀和 $sum$ 的性质。

显然，当有 $sum_i\oplus sum_j = 0 (i < j)$ 时，则区间 $[i+1,j]$ 的异或和为 $0$，而此时有 $sum_i=sum_j$，所以前缀和中的元素不重复，还有，由于两个数字异或起来不会更大，所以直接枚举 $0\le sum_i < 2^{n}$，对于当前枚举的元素 $i$，如果之前未出现过，则加入 $sum$ 序列，并标记 $i\oplus x$ 不能出现，最后还原序列即可。

### 代码
```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
const int maxn=(1<<18)+5;
int n,x;
bool vis[maxn];
vector<int>ans;
int main(){
	scanf("%d%d",&n,&x);
	vis[0]=1;
	vis[x]=1;
	for(int i=1;i<(1<<n);i++){
		if(!vis[i]&&!vis[i^x]){
			ans.push_back(i);
			vis[i^x]=1;
		}
	}
	for(int i=ans.size()-1;i>=1;i--){
		ans[i]^=ans[i-1];
	}
	printf("%d\n",ans.size());
	for(int i=0;i<ans.size();i++){
		printf("%d ",ans[i]);
	}
}
```

---

## 作者：封禁用户 (赞：0)

## 题解：CF1174D Ehab and the Expected XOR Problem

### 解题思路

求原序列的**前缀异或序列**即可，此时转化为原序列的前缀异或序列没有任意两数异或结果为 $0$ 或 $x$。

每次**贪心**选择最小可选数 $a$，并将 $a$ 和 $a \operatorname{xor} x$ 标记为不可选。初始时只有 $0$ 和 $x$ 不可选。

最后输出求出的这个序列的**差分序列**即可（原序列的前缀和序列的差分序列等于原序列）。

提示：数字最大 $2^{18} = 262144$。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , x , ans[262150] , atmp;
bool vis[262150];
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> x;
	vis[x] = 1;
	for(int i = 1 ; i < (1 << n) ; i++)
	{
		if(vis[i])
		{
			continue;
		}
		vis[i] = vis[x ^ i] = 1;
		atmp++;
		ans[atmp] = i;
	}
	cout << atmp << '\n';
	for(int i = 1 ; i <= atmp ; i++)
	{
		cout << (ans[i] ^ ans[i - 1]) << ' ';
	}
	return 0;
}
```

---

## 作者：Lotus_Land (赞：0)

由于连续子序列异或和的限制，考虑构造前缀异或和数组 $s_i$。

因为连续子序列异或和不会出现 $0$，所以不存在 $s_i=s_j,i\not=j$。

当 $x=2^n$ 时，由于 $1\leq a_i<2^n$，所以子序列异或和一定不会出现 $x$。（异或结果的位数不大于参与异或的两个数的位数。）此时可构造前缀异或和数组为 $1$ 到 $2^n-1$ 的排列。

当 $x=0$ 时，同理可构造 $s_i$ 为 $1$ 到 $2^n-1$ 的排列。

当 $0<x<2^n$ 时，因为连续子序列异或和不会出现 $x$，所以不存在 $s_i\oplus s_j=x$，即不存在 $s_j=s_i\oplus x$。故在前缀异或和数组中，$i$ 与 $i\oplus x$ 不能同时存在，任选其一即可。又由于前面的限制，$x$ 与 $0$ 都不能存在。

构造出前缀异或和数组后，再推出 $a_i$ 就好了。


```cpp
#include<bits/stdc++.h>
#define N 300005
using namespace std;
int n,x,a[N],s[N];
int main() {
	cin>>n>>x;
	if(x==(1<<n)||x==0) {
		cout<<(1<<n)-1<<endl;
		int val=0;
		for(int i=1; i<(1<<n); i++) {
			a[i]=i^val;
			cout<<a[i]<<' ';
			val=val^a[i];
		}//考虑构造前缀异或和数组为 1 2 ... (1<<n)-1 
	}else{
		//不能有重复的前缀异或和
		//不存在 s[i]^s[j]=x 即不存在 s[j]=s[i]^x
		// i 与 i^x 只能存在一个
		int tot=0;
		for(int i=1;i<(1<<n);i++){
			if((i^x)<i)continue;
			s[tot++]=i;//构造前缀异或和数组 
			//cout<<s[i]<<' ';
		}  
		//cout<<endl;
		cout<<tot<<endl;//实际上是 (1<<(n-1))-1 
		for(int i=1;i<=tot;i++){
			cout<<(s[i]^s[i-1])<<" ";
		}
	}
	return 0;
}
```

---

## 作者：Pt_crN (赞：0)

一样的结论，可能会有不同的思维过程。

看到这个题面，我们会发现，不存在异或和为 $0$ 的子段这个条件看着还算舒服，但是不存在为 $x$ 的子段就非常的丑。怎么办呢？

我们尝试将每个数后面插入一个 $x$ 并去掉上文后半段的条件。惊奇地发现这个 $x$ 相当于给每个子段异或上了一个 $x$，但不会产生多余影响！这下好办了！

但是此时，我们还是很难求得答案。于是，我们可以再次进行问题转化：一个子段的异或和可以转化为一段后缀异或和异或上另一段。所以，子段异或和不为 $0$ 就可以变为：没有两段后缀异或和相等。这时答案已经呼之欲出了，再进行一次分类讨论：

- 若 $x\geq 2^n$

容易发现，被前面插入的 $x$ 影响到的子段一定和没被影响到的不一样。所以答案即为 $2^n-1$。

- 否则

被影响的子段也会额外占用一个值。即原序列上一段后缀会占用两个值。答案即为 $2^{n-1}-1$。

code：

```cpp
int n,m,e[N];
bool vis[N];
void Yorushika(){
	scanf("%d%d",&n,&m);
	const int k=1<<n;
	if(m>=(1<<n)){
		printf("%d\n",k-1);
		rep(i,1,k-1){
			printf("%d ",i^(i-1));
		}
	}else{
		printf("%d\n",k/2-1);
		int lst=0,s=k/2-1;
		drep(i,k-1,1){
			if(vis[i]||i==m)
				continue;
			vis[i]=vis[i^m]=true;
			e[s--]=i^lst;
			lst=i;
		}
		rep(i,1,k/2-1){
			printf("%d ",e[i]);
		}
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

