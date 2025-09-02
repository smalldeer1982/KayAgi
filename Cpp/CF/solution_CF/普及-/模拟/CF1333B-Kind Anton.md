# Kind Anton

## 题目描述

Once again, Boris needs the help of Anton in creating a task. This time Anton needs to solve the following problem:

There are two arrays of integers $ a $ and $ b $ of length $ n $ . It turned out that array $ a $ contains only elements from the set $ \{-1, 0, 1\} $ .

Anton can perform the following sequence of operations any number of times:

1. Choose any pair of indexes $ (i, j) $ such that $ 1 \le i < j \le n $ . It is possible to choose the same pair $ (i, j) $ more than once.
2. Add $ a_i $ to $ a_j $ . In other words, $ j $ -th element of the array becomes equal to $ a_i + a_j $ .

For example, if you are given array $ [1, -1, 0] $ , you can transform it only to $ [1, -1, -1] $ , $ [1, 0, 0] $ and $ [1, -1, 1] $ by one operation.

Anton wants to predict if it is possible to apply some number (zero or more) of these operations to the array $ a $ so that it becomes equal to array $ b $ . Can you help him?

## 说明/提示

In the first test-case we can choose $ (i, j)=(2, 3) $ twice and after that choose $ (i, j)=(1, 2) $ twice too. These operations will transform $ [1, -1, 0] \to [1, -1, -2] \to [1, 1, -2] $

In the second test case we can't make equal numbers on the second position.

In the third test case we can choose $ (i, j)=(1, 2) $ $ 41 $ times. The same about the fourth test case.

In the last lest case, it is impossible to make array $ a $ equal to the array $ b $ .

## 样例 #1

### 输入

```
5
3
1 -1 0
1 1 -2
3
0 1 1
0 2 2
2
1 0
1 41
2
-1 0
-1 -41
5
0 1 -1 1 -1
1 1 -1 1 -1```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：奇米 (赞：4)

## 题解- CF1333B Kind Anton

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

### **题目意思**

* [B](https://www.luogu.com.cn/problem/CF1333B)
* 给你一个数组$A$，$A_i∈[-1,0,1]$。称一次操作$(i,j),i<j$为：$a_j=a_i+a_j$。问是否能通过若干次操作让他变成$B$

### $\mathrm{Sol}$

* 首先：我的做法比较麻烦
* 我们先记录原序列$A$中$1,-1$的数量。我们重前往后找，如果存在$A_i<B_i$那么前面一定存在$A_i=1$。如果存在$A_i>B_i$那么前面一定存在$A_i=-1$。于是就直接模拟即可。注意$1,-1$个数的更新。

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=1e5+5;

int n,m,a[N],b[N]; 

int main()
{
	int T=read();
	for (;T--;)
	{
		n=read();
		int s0=0,s1=0,s2=0;
		for ( int i=1;i<=n;i++ ) 
			a[i]=read();
		for ( int i=1;i<=n;i++ )
		{
			b[i]=read();
		}
		for ( int i=1;i<=n;i++ )
		{
			if(a[i]==b[i])
			{
				if(a[i]==1) s1++;
				if(a[i]==-1) s2++;
				continue;
			}
			if(a[i]<b[i])
			{
				if(s1)
				{
					if(b[i]==-1) s2++;
					if(b[i]==1) s1++;
				}
				else 
				{
					printf("NO\n");
					goto rp;
				}
				if(a[i]==-1) s2++;
				if(a[i]==1) s1++;
			}
			if(a[i]>b[i])
			{
			
				if(s2)
				{
					if(b[i]==-1) s2++;
					if(b[i]==1) s1++;
				}
				else 
				{
					printf("NO\n");
					goto rp;
				}	
				if(a[i]==-1) s2++;
				if(a[i]==1) s1++;
			}
		}
		printf("YES\n");
		rp:;
	}
}
```


---

## 作者：AutumnKite (赞：4)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

考虑从后往前依次将 $a_i$ 变成 $b_i$。

考虑对于当前位置 $i$，若 $b_i < a_i$（即需要变小），那么显然只需要存在一个 $j$ 满足 $j < i$ 且 $a_j=-1$ 就可以不断将 $a_i$ 减 $1$ 直到等于 $b_i$；同理，若 $b_i > a_i$（即需要变大），那么只需要存在一个 $j$ 满足 $j < i$ 且 $a_j=1$ 就可以不断将 $a_i$ 加 $1$ 直到等于 $b_i$。

那么我们只需要从左往右找到第一个 $1$ 和 $-1$ 然后进行判断即可。

### 代码

```cpp
const int N = 200005;

int n, a[N], b[N];

void solve() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	for (int i = 1; i <= n; ++i) {
		read(b[i]);
	}
	int p1 = 1, p2 = 1;
	while (p1 <= n && a[p1] < 1) {
		if (a[p1] < b[p1]) {
			printStr("NO");
			return;
		}
		++p1;
	}
	if (p1 <= n && a[p1] < b[p1]) {
		printStr("NO");
		return;
	}
	while (p2 <= n && a[p2] > -1) {
		if (a[p2] > b[p2]) {
			printStr("NO");
			return;
		}
		++p2;
	}
	if (p2 <= n && a[p2] > b[p2]) {
		printStr("NO");
		return;
	}
	printStr("YES");
}
```

---

## 作者：banned_xiejiayun (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1333B)

#### STEP 1：简化题意

题目的意思很好理解，就是要通过加 $1$ 或减 $1$ 将 $a$ 数组的每个元素变成 $b$ 数组。

但是前提是 $a$ 数组前面（包括 $a$ 要变成的 $b$）有 $1$ 或 $-1$ 才行。


------------
#### STEP 2：思路推导

我们可以循环一个一个判断 $a$ 数组中的这个元素可否变成 $b$ 的元素。

第一种情况：当 $a$ 第 $i$ 个位置的元素和 $b$ 相等，就什么也不需要转换。

```cpp
	if (a[i] == b[i]) {
		if (a[i] == -1) {
			if (!x) x = 1;
		} else if (a[i] == 1) {
			if (!y) y = 1;
		}
		//x 是标记是否有 -1 ， y 是标记是否有 1。
		continue;
	}
    
```
    
第二种情况：当 $a$ 第 $i$ 个位置的元素比 $b$ 大，就需要 $-1$ 来减。
```cpp

	if (a[i] > b[i]) {
		if (x == 0) {
		// a[i] > b[i] 时需要 -1，没有的话就结束了。
			printf("NO\n");
			flag = false;
			break;
		}
		if (b[i] == -1) {
			if (!x) x = 1;
		} else if (b[i] == 1) {
			if (!y) y = 1;
		}
		if (a[i] == -1) {
			if (!x) x = 1;
		} else if (a[i] == 1) {
			if (!y) y = 1;
		}
		//正常标记。
	}
    
```
    
第三种情况：当 $a$ 第 i 个位置的元素比 $b$ 小，就需要 $1$ 来加。
```cpp

	if (a[i] < b[i]) {
		//当 a[i] < b[i] 时同理。
		if (y == 0) {
			printf("NO\n");
			flag = false;
			break;
		}
		if (b[i] == -1) {
			if (!x) x = 1;
		} else if (b[i] == 1) {
			if (!y) y = 1;
		}
		if (a[i] == -1) {
			if (!x) x = 1;
		} else if (a[i] == 1) {
			if (!y) y = 1;
		}
	}
```

当循环结束时，只需判断输出 $YES$ 就行了。

```cpp
	if (flag) printf("YES\n");
```


------------

#### STEP 3：分析难点

     
有人可能不理解为什么在第二三种情况中还要记录 $a$ 数组中是否有 $1$ 或 $-1$。

拿着样例数据一起说吧（懂的可以跳过这段）：

```
3
1 -1 0
1 1 -2
```


如果在比较 $-1$ 和 $1$ 时不标记 $y = 1$ 的话，后面的 $0$ 和 $-2$ 就无法完成。

但实际上我们先让 $0$ 减去两次 $-1$ 得到 $-2$，再让 $-1$ 加上两个  $1$ 也可以完成 $a$ $b$ 数组的转换。

所以这里我们要留个心眼，可能会让本次操作后面再去做。
     


------------

### AC 代码：

注释比较多，希望你能认真看。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[100001], b[100001];
bool x, y;
int main() {
	scanf("%d", &t);
	while (t--) {
		x = 0, y = 0;
		// x 是记录 a 数组中是否有 -1 。
		// y 是记录 b 数组中是否有  1 。
		bool flag = true;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++)scanf("%d", &b[i]);
		for (int i = 1; i <= n; i++) {
			//若第 i 个位置相等，就什么也不需要转换。
			if (a[i] == b[i]) {
				if (a[i] == -1) {
					if (!x) x = 1;
				} else if (a[i] == 1) {
					if (!y) y = 1;
				}
				//别忘了记录是否有 1 或 -1 。
				continue;
			}
			if (a[i] > b[i]) {
				if (x == 0) {
					// a[i] > b[i] 时需要 -1，没有的话就结束了。
					printf("NO\n");
					flag = false;
					break;
				}
				if (b[i] == -1) {
					if (!x) x = 1;
				} else if (b[i] == 1) {
					if (!y) y = 1;
				}
				if (a[i] == -1) {
					if (!x) x = 1;
				} else if (a[i] == 1) {
					if (!y) y = 1;
				}
				//正常标记。
			} else {
				//当 a[i] < b[i] 时同理。
				if (y == 0) {
					printf("NO\n");
					flag = false;
					break;
				}
				if (b[i] == -1) {
					if (!x) x = 1;
				} else if (b[i] == 1) {
					if (!y) y = 1;
				}
				if (a[i] == -1) {
					if (!x) x = 1;
				} else if (a[i] == 1) {
					if (!y) y = 1;
				}
			}
		}
		if (flag) printf("YES\n");
	}
	return 0;
}
```


~~这是一篇很正经的题解~~


---

## 作者：Warriors_Cat (赞：3)

### $Description:$

一个长度为 $n$ 的序列 $a$，问能否通过若干次操作：

* 选出 $1 \le i < j \le n$ 的数，把 $a_j$ 替换成 $a_i+a_j$。

变成序列 $b$，其中 $a_i \in \{-1, 0, 1\}$。

### $Solution:$

我们从后往前枚举，每次判断 $a_i$ 与 $b_i$ 的大小。如果比 $b_i$ 小就判断前面有没有 $1$，比 $b_i$ 大就判断有没有 $-1$。没有直接输出 ``NO``。

最后如果全部都能遍历就代表答案为 ``YES``。

具体看代码：

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int t, n, a[100010], b[100010], cnt[2];
//cnt[0] 表示 -1 的个数，cnt[1] 表示 1 的个数。
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i){
			scanf("%d", a + i);
			if(i < n){
				if(a[i] == 1) cnt[1]++;
				if(a[i] == -1) cnt[0]++;
			}//预处理
		}
		for(int i = 1; i <= n; ++i) scanf("%d", b + i);
		bool flag = 1;
		for(int i = n; i >= 1; --i){
			if(a[i] == b[i]){
				if(a[i - 1] == 1) cnt[1]--;
				if(a[i - 1] == -1) cnt[0]--;
			}//相等直接略过，注意要把 a[i - 1] 除掉
			else if(a[i] > b[i]){
				if(!cnt[0]){
					flag = 0;
					break;
				}//没有就返回 0
				if(a[i - 1] == 1) cnt[1]--;
				if(a[i - 1] == -1) cnt[0]--;
			}//a_i 比 b_i 大
			else if(a[i] < b[i]){
				if(!cnt[1]){
					flag = 0;
					break;
				}
				if(a[i - 1] == 1) cnt[1]--;
				if(a[i - 1] == -1) cnt[0]--;
			}//同上
		}
		if(!flag) puts("NO");
		else puts("YES"); 
		memset(cnt, 0, sizeof(cnt));//注意清零
	}
	return 0;
} 
```


---

## 作者：gyh20 (赞：3)

因为后面不对前面造成影响，所以可以直接从前往后计算。

如果 $a_i=b_i$，那么没问题

如果 $a_i<b_i$，如果存在 $a_j=1,j<i$ 那么可以一直给 $a_i$ 加。否则无解。

如果 $a_i>b_i$，检查是否存在 $-1$ 即可。

这样做是 $O(n^2)$ 的，但我们直接维护是否存在 $1/-1$ 的标记即可，这样就是 $O(n^2)$ 的。

```
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
int n,a[100002],b[100002],m,t,v0,v1;
int main(){
	t=read();
	while(t--){
		n=read();v0=v1=0;
		bool ia=0;
		for(re int i=1;i<=n;++i)a[i]=read();
		for(re int i=1;i<=n;++i)b[i]=read();
		for(re int i=1;i<=n;++i){
			if(a[i]==b[i]){if(a[i]==-1)v0=1;if(a[i]==1)v1=1;}
			else if(a[i]>b[i]&&v0){if(a[i]==-1)v0=1;if(a[i]==1)v1=1;}
			else if(a[i]<b[i]&&v1){if(a[i]==-1)v0=1;if(a[i]==1)v1=1;}
			else{
				ia=1;puts("NO");break;
			}
		}
		if(!ia)puts("YES");
	}
}
```


---

## 作者：tuzhewen (赞：2)

### 题目大意
一共有$T$组输入，每组输入给你两个长度均为$n(n\le 10^5)$的数组$a$和$b$。$a$中只包含$3$个元素$-1,0,1$。现在让你选择一对$(i,j)(1\le i<j\le n)$，让$a_j$加上$a_i$。问你如果一直对$a$数组做这个操作，最后能不能把$a$数组变成$b$数组。

### 思路
既然$a$数组中只有$1,0,-1$，那么我们只需要从$1$~$n$遍历一遍就行了，当$a_i==b_i$时，不用管它~~（不是废话么）~~，当$a_i<b_i$时，我们只需要看一看当前$a_i$的前面有没有出现过$1$，因为$a_i$一直加$1$一定可以得到$b_i$；同理，当$a_i>b_i$时，我们也只要看一看$a_i$的前面有没有出现过$-1$就行了。

$ACcode:$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define F(i,l,r) for(int i=l;i<=r;i++)
const int N=1e5+5;
int T;
int n;
int a[N],b[N];
int main() {
	scanf("%d",&T);
	while(T--) {
		bool small=0,big=0;//分别用来判断是否出现了-1和1
		bool flag=true;
		scanf("%d",&n);
		F(i,1,n) scanf("%d",&a[i]);
		F(i,1,n) scanf("%d",&b[i]);
		F(i,1,n) {
			if(a[i]>b[i]&&!small) {flag=false;break;}//如果a[i]比b[i]大并且没有-1，那么就不对
			else if(a[i]<b[i]&&!big) {flag=false;break;}//如果a[i]比b[i]小并且没有1，那么就不对
			if(a[i]==-1) small=1;//标记-1
			else if(a[i]==1) big=1;//标记1
		}
		flag ? puts("YES") : puts("NO");//三目运算符输出~
	}
	return 0;//完结撒花~
}
```

---

## 作者：yutong_Seafloor (赞：1)

# [题目在这里 · Kind Anton CF1333B](https://www.luogu.com.cn/problem/CF1333B)
### 题目简要：
有两个相同长度的数据 $a$ 和 $b$，现在你有机会选择一对 $(i,j)$ 让 $a _ {j}$ 加上 $a _ {i}$ 这个位置的数字，请问通过这几次相加操作能不能把数据 $a$ 变成数据 $b$。

### 题意分析
题意其实很好理解，数据 $a$ 要通过“操作”变成数据 $b$，操作是选择数对 $(i,j)$，将 $a _ {j}$ 上的数字加上 $a _ {i}$ 上的数字，具体的，这个操作可多次，可更改，且数据 $a$ 中只含有 $1$，$0$，$-1$ 三个数字。

乍一看是不是应该都输出 `YES`？？？并不是，由于我们的 $i < j$，这就要求 $a _ {j}$ 要加的数字必须在它的前面，那我们分情况讨论一下：

情况1：$a _ {j} < b _ {j}$，这种情况下如果要做到复原，前面应当有 $1$ 进行增加，若没有，则不可能完成。

情况2：$a _ {j} > b _ {j}$，这种情况下如果要做到复原，前面应当有 $-1$ 进行减少，若没有，同上。

情况3：$a _ {j} = b _ {j}$，~~孩子，你是不是傻，这种情况你还动什么啊。~~

## 代码 


```cpp 
#include<bits/stdc++.h>
using namespace std;
int t,n,i,j;
int a[100000010],b[100000010];
bool fy=true,zy=true,yt=true;
int main()
{
	cin>>t;
	for(i=1;i<=t;i++)
	{
		fy=true,zy=true,yt=true;
		cin>>n;
		for(j=1;j<=n;j++)
		cin>>a[j];
		for(j=1;j<=n;j++)
		cin>>b[j];
		for(j=1;j<=n;j++)
		{
			if((a[j]<b[j] && zy)||(a[j]>b[j] && fy))
			{
				yt=false;
				break;
			}
			if(a[j]==-1) fy=false;
			if(a[j]==1) zy=false;
		}
		if(yt)
		cout<<"YES\n";
		else
		cout<<"NO\n";
	}
	return 0;
}//by·yutong_Seafloor 
``` 
一定要注意一下小细节，比如在循环的时候一定要重置上一轮的数据（就是三个判断的 `bool` 数据）。

---

## 作者：do_while_true (赞：1)

~~无脑贪心~~

$a$ 数组为只含 $\left\{1,0,-1\right\}$ 的数组，每次操作可以选定任意 $1\le i < j \le n$，使得 $a_j=a_j+a_i$。求 $a$ 数组是否能通过上述操作变成数组 $b$

首先先将数组 $b$ 的所有 $b_i$ 减去 $a_i$ ，也就是 $a_i$ 到 $b_i$ 要变化的值。因为操作可以无限次，则出现以下情况为 "NO" :

1. $b_i>0$ 但 没有$a_j>0\ (j<i)$

1. $b_i<0$ 但 没有$a_j<0\ (j<i)$

所以我们只需要记录 $a$数组 当前 $a_i$ 的前面有没有出现过 $1$ 和 $-1$ 即可。


## $\mathcal{Code}$
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,a[100010],b[100010];
bool cnt1[100010],cnt2[100010];
bool f;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			cnt1[i]=cnt2[i]=0;
		f=1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]>0||cnt1[i]==1) cnt1[i+1]=1;
			if(a[i]<0||cnt2[i]==1) cnt2[i+1]=1;
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&b[i]);
			b[i]-=a[i];
			if(b[i]>0&&!cnt1[i]) f=0;
			if(b[i]<0&&!cnt2[i]) f=0;
		}
		if(f) puts("YES");
		else puts("NO");
	}
}
```


---

## 作者：ICU152_lowa_IS8 (赞：0)

首先上来看到数据范围：$1\leq \sum n\leq100000$，显然暴力过不去。

对于本题，对每一个数分类讨论：

$a_i<b_i$，如果前面有 $a_i=1$ 则继续，否则直接输出 `NO`；

$a_i=b_i$，不管；

$a_i>b_i$，如果前面有 $a_i=-1$ 则继续，否则输出 `NO`。

在操作时倒着改，显然上述分类讨论正确。

正向遍历一遍记录 $a_i=1$ 和 $a_i=-1$ 在之前有没有出现过即可，代码：

```
#include<bits/stdc++.h>
using namespace std;
int a[1000005],b[1000005];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		int pos=0,neg=0,flag=1;
		for(int i=1;i<=n;i++){
			if(b[i]>a[i]&&!pos){
				flag=0;
				break;
			}
			if(b[i]<a[i]&&!neg){
				flag=0;
				break;
			}
			if(a[i]==1)pos=1;
			if(a[i]==-1)neg=1;
		}
		cout<<(flag?"YES":"NO")<<endl;
	}
	return 0;
}

```


---

## 作者：IOI_can_AK_lsr (赞：0)

# CF1333B题解

### [洛谷传送门](https://www.luogu.com.cn/problem/CF1333B) | [CF传送门](https://www.codeforces.com/contest/1333/problem/B)
 
[更好的阅读体验](https://www.luogu.com.cn/blog/910468/cf1333b-tijie)
## 思路

本题算是比较简单的一道题了。

我们要做的这些操作都可以由模拟实现，所以可以直接从前往后遍历一遍，不会影响到$a$数组的值。

因为 $a_i$ 有三种取值，所以这里分为三种情况：

- 如果 $a_i=b_i$，可以直接打标记判定；

- 如果 $a_i<b_i$，就需要判断一下，如果 $a_j=1$ 且 $j<i$，那么就可以打标记判定，否则无解；

- 如果 $a_i>b_i$，只需要判断 $a_i$ 中有没有 $-1$ 存在就可以了。

这样，$O(n^2)$的时间复杂度刚好可以通过本题。

[代码&&AC记录见此处](https://codeforces.com/contest/1333/submission/223606422)

完结撒花！！！

---

## 作者：Fan_Tuan (赞：0)

# 题意
给定两个长度为 $n$的序列 $a, b$， $a_i \in \{ -1, 0, 1\} $,可以任意次选取$1 <= i <j <=n$，让 $a_j $加上 $a_i$，询问能否将序列 $a$ 变为序列 $b$。
# 思路
定义一个数组 $f$, $f_i$表示的是 $a_1$到 $a_i$，$\{-1,1,0\}$是否出现过。**【**注意$f_i$ 的范围包括$a_i$这个点，代码实现时要注意**】**

$f_i = -1:$ 只出现过 $-1$； 

$f_i = 1 :$ 只出现过 $1$；

$f_i = 0:$ 只出现过 $0$；

$f_i = 2:$ $-1, 1$都出现过。

然后我们从后往前处理 $b_i$，共有以下几种情况：

$\bullet$ 如果 $b_i < 0$ $&&$ $f_{i-1} =2$或$-1$,则$a_i$ 可以变为 $b_i$,否则直接输出$NO$。

$\bullet$ 如果 $b_i > 0$ $&&$ $f_{i-1} =2$或$1$,则$a_i$ 可以变为 $b_i$,否则直接输出$NO$。

$\bullet$ 如果 $b_i = 0$ $&&$ $f_{i-1} =2$,则$a_i$ 可以变为 $b_i$,  如果$\begin{cases}f_{i-1}=1\And a_i = -1&\\f_{i-1}=-1\And a_i = 1&\end{cases}$ ，$a_i$ 也可以变为 $b_i$,否则输出 $NO$。

**注：** 为什么是$f_{i-1}$呢，  因为$a_i$这个点只能通过加它前面的点来成为$b_i$, 而我们的$f_i$是包括 $a_i$这个点的， 所以要用$f_{i - 1}$。
对于上述几种情况， 应该很容易理解吧， ~~我就不解释了~~

# 代码


```c
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <queue>
#include <iostream>
using namespace std;

const int maxn = 105005;
int n, t, a[maxn], b[maxn], k, f[maxn];

signed main () {                   
    scanf("%d", &t); 
    while (t--) {
        int flag = 0;
        scanf("%d", &n);
        memset (a, 0, sizeof a);
        memset (b, 0, sizeof b);
        memset (f, 0, sizeof f);
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            a[i] = x;
            if (f[i - 1] == 2) f[i] = 2;
            else if (f[i - 1] == 1) {
                if (x == 0 || x == 1) f[i] = 1;
                else f[i] = 2;
            }
            else if (f[i - 1] == -1) {
                if (x == 0 || x == -1) f[i] = -1;
                else f[i] = 2;
            }
            else f[i] = x;
        }
        for (int i = 1; i <= n; i++) scanf ("%d", &b[i]);
        for (int i = n; i >= 1; i--) {
            if (b[i] == a[i]) continue;
            if (b[i] < 0) {
                if (f[i - 1] == 2 || f[i - 1] == -1) continue;
                else {
                    puts ("NO");
                    flag = 1;
                    break;
                }
            }
            if (b[i] > 0) {
                if (f[i - 1] == 2 || f[i - 1] == 1) continue;
                else {
                    puts ("NO");
                    flag = 1;
                    break;
                }
            }
            if (b[i] == 0) {
                if (f[i - 1] == 2) continue;
                else if (f[i - 1] == 1 && a[i] == -1) continue;
                else if (f[i - 1] == -1 && a[i] == 1) continue;
                else {
                    puts ("NO");
                    flag = 1;
                    break;
                }
            }
        } 
        if (flag == 0) puts ("YES");
    }
    return 0;
}
```



---

## 作者：_jimmywang_ (赞：0)

新鲜的CF题啊，来写一发题解好了~~

首先我们来看看题目。我们发现，对于每个$a_{j}$，其实要做的就是让$a_{j}$加上$a_{i}(1 \leq i<j)$，让$a_{j}$变成$b_{j}$。

怎么加呢？随便加。

真的随便加？

对，真的随便加，每个$a_{i}$加多少次都行。

哦！那就简单了啊，不就是对于每个$a_{j}DFS$，再判断啊！

好的，想法不错，嘿嘿，$B$题即将拿下！！！

于是我们看看数据范围：$n \leq 10^{5}$

。。。。。。（迷之沉默）

$TLE$撑死你

好吧，失去信心了吗？众所周知，某某某说过一句话：如果你失去信心了，就再去读一读题面。

于是你看啊看，看啊看，发现一个神奇的东西：

$a$中只包含$3$个元素 $-1$, $0$,$1$

于是如晴天霹雳版，你醒悟了过来。

接下来是重头戏，分类讨论！！

## 1.$a_{j}<b_{j}$

这时，我们要在$a_{j}$上加上$b_{j}-a_{j}$，即可达到效果。

因为$b_{j}-a_{j}>0$

所以只要在$j$前面有一个$i$满足$a_{i}==1$就行了呀~~，加上$b_{j}-a_{j}$次$1$就完事

## 2.$a_{j}>b_{j}$

这时，与上一种情况类似，我们要在$a_{j}$上**减去**$b_{j}-a_{j}$，即可达到效果。

因为$b_{j}-a_{j}<0$

所以只要在$j$前面有一个$i$满足$a_{i}==-1$就行了。

## 3.$a_{j}==b_{j}$

此时不用讨论。

你们是不是想说为什么啊？必须要有$1$和$-1$或$0$才行啊，为啥不讨论了？

请问：题中有说每个数都要操作吗？

既然没有，放着不动就行了啊。

。。。。。。（迷之沉默*2）

所以我们对于每个$a_{j}$，往前找，找到符合条件的就行。一旦不行，就全都不行了。

于是看看我上面的话：
>数据范围：$n \leq 10^{5}$

极限数据会把这个方法卡成$O(n^{2})$，$TLE$

于是乎，最后一步：建一个$k$数组，$k_{i,j}$表示$(i-1)$这个数在$j$之前有没有出现过，这样就成功的把复杂度降到$O(n)$，$AC$成功！！！

代码：

```
#include<algorithm>
#include<bitset>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<iostream>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
#define d read()
ll n,T;
ll a[1000010];
ll b[1000010];
bool k[3][1000010];
int main(){
	T=d;
	while(T--){
		bool fl=0;
		memset(k,0,sizeof(k));
		n=d;
		k[1][1]=1;
		f(i,1,n){
			a[i]=d;
			if(k[0][0])k[0][i]=1;
			if(k[2][0])k[2][i]=1;
			if(!k[a[i]+1][0])k[a[i]+1][0]=1;
		}
		f(i,1,n)b[i]=d;
		f(i,1,n){
			ll x=b[i]-a[i];
			if(x<0&&!k[0][i]){cout<<"NO\n";fl=1;break;}
			if(x>0&&!k[2][i]){cout<<"NO\n";fl=1;break;}
		}
		if(!fl)cout<<"YES\n";
	}
	return 0;
}

```


---

## 作者：流绪 (赞：0)

题意：给一个 $a$ 数组，其值只有 $0,1,2$ 和一个数组 $b$，对于 $a$ 数组每一个位置 $i$，你可以选择它之前的人一个位置的数，把他加到 $a_i$ 上，科奥做任意次。问最后 $a$ 数组能否和 $b$ 数组相等。

结论：若能成功变化，则对于每一个位置，若 $b_i>a_i$，那么前面必有一个$a_i=1$；若 $b_i<a_i$,前面必有一个 $a_i=-1$;>；若 $b_i=a_i$ 不用变化。

证明：对于第一个 $b_i>a_i$，因为前面均为未变化过，所以这一位肯定需要前面一个 $a_i=1$ 才能够成功变化。剩下的位置，由于前面有一个 $a_i=1$，故都能成功变化。$b_i<a_i$ 同理。

所以我们遍历整个数组，对于每个需要变化的位置，看看其前面有没有上述所说的数即可。

下面是 $AC$ 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define mod 998244353
#define db(x) cout << x << endl; 
#define eps 0.0001
using namespace std;
int a[maxn],b[maxn];
char s[maxn];
int v[5];
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >>n;
		v[1] = v[2] = v[3] = 0;//v[1]表示有吗-1,v[3]表示有没有1
		int flag = 1;
		for(int i=1;i<=n;i++)
		{
			cin >> b[i];
			if(b[i] > a[i]&&v[3]==0)
				flag = 0;
			if(b[i] < a[i]&&v[1]==0)
				flag = 0;
			if(a[i] == -1)
				v[1]++;
			if(a[i] == 1)
				v[3]++;
		}
		if(flag )
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
```


---

