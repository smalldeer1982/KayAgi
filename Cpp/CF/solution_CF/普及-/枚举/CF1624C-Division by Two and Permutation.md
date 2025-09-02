# Division by Two and Permutation

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers. You can perform operations on it.

In one operation you can replace any element of the array $ a_i $ with $ \lfloor \frac{a_i}{2} \rfloor $ , that is, by an integer part of dividing $ a_i $ by $ 2 $ (rounding down).

See if you can apply the operation some number of times (possible $ 0 $ ) to make the array $ a $ become a permutation of numbers from $ 1 $ to $ n $ —that is, so that it contains all numbers from $ 1 $ to $ n $ , each exactly once.

For example, if $ a = [1, 8, 25, 2] $ , $ n = 4 $ , then the answer is yes. You could do the following:

1. Replace $ 8 $ with $ \lfloor \frac{8}{2} \rfloor = 4 $ , then $ a = [1, 4, 25, 2] $ .
2. Replace $ 25 $ with $ \lfloor \frac{25}{2} \rfloor = 12 $ , then $ a = [1, 4, 12, 2] $ .
3. Replace $ 12 $ with $ \lfloor \frac{12}{2} \rfloor = 6 $ , then $ a = [1, 4, 6, 2] $ .
4. Replace $ 6 $ with $ \lfloor \frac{6}{2} \rfloor = 3 $ , then $ a = [1, 4, 3, 2] $ .

## 说明/提示

The first test case is explained in the text of the problem statement.

In the second test case, it is not possible to get a permutation.

## 样例 #1

### 输入

```
6
4
1 8 25 2
2
1 1
9
9 8 3 4 2 7 1 5 6
3
8 2 1
4
24 7 16 7
5
22 6 22 4 22```

### 输出

```
YES
NO
YES
NO
NO
YES```

# 题解

## 作者：gzlinzy (赞：5)

根据全排列的定义，如果 $a$ 数组经过操作能成为全排列，那么它最终应当满足以下条件：

- 数组中每个数都不大于 $n$。

- 每个数在数组中都只出现一次。

因此，在操作时，判断一个数应不应该继续除，也应满足上面的条件，即此数不大于 $n$，且没有出现过。

对数组进行操作的次序没有关系，从左到右即可。因为如果由于两数位置的交换导致本不会重复的它们重复了，那么恰恰说明它们交不交换没有所谓，不影响结果。

代码：

```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[55],b[55],flag;
int main(){
	cin>>t;
	while(t--){
		flag=0;
		memset(b,0,sizeof(b));
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			while(a[i]>n||b[a[i]]==1)a[i]/=2;
			if(a[i]==0){
				cout<<"NO\n";
				flag=1;
				break;
			}
			else b[a[i]]=1;
		}
		if(!flag)cout<<"YES\n";
	}
	return 0;
}
```


---

## 作者：donk_666 (赞：4)

一道CF的大水题，代码如下，~~配注释食用更佳。~~


------------

题意：

有一个长度为 $n$ 的数组 $a$ 。

不断除以 $2$ ，并向下取整。

使得 $a$ 数组变成一个 $1$ $\sim$ $n$ 的全排列。



------------

思路：

不断向下除并取整，直到找到一个最大的合法位置。



------------
代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100],f[100];//a是原数组，f是访问数组
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		memset(a,0,sizeof(a));//数组不清空，OI见祖宗
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++){//整体类似贪心的策略，把数放到能放的最大地方
			cin>>a[i];//输入
				while(a[i]>n){//当a[i]比n大，不停往下除，直到小于n为止
					a[i]=a[i]/2;
				}
				while(f[a[i]]>=1&&a[i]/2!=0){//当a[i]已经存在过，继续往下除，注意此时a[i]除后不能为0
					a[i]=a[i]/2;
				}
			f[a[i]]++;
		}
		bool d=0;
		for(int i=1;i<=n;i++){
			if(f[i]!=1){
				d=1;
			}
		}
		if(d==1){
        	cout<<"NO"<<endl;
        }
		else{
        	cout<<"YES"<<endl;
        }
	}
}
```

---

## 作者：yeshubo_qwq (赞：2)

## 题意
有一个长度为 $n$ 的数组。

可以对其中的数进行除以二并向下取正的操作。

问：能否使该数组变成一个 $1 \sim n$ 的全排列。
## 思路
我们考虑一个数，什么时候要继续往下除。

显然第一种：当这个数大于 $n$ 时，要往下除。

第二种：一个 $1 \sim n$ 的全排列显然没有重复数字，所以当这个数字出现过时，同样要往下除。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,x,i,a[55],f[55];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		memset(f,0,sizeof(f));//初始化
		for(i=1;i<=n;i++){
			cin>>x;
			while(x>n||(x<=n&&f[x]&&x/2>0))x/=2;//往下除
			f[x]++;//计数
		}
		for(i=1;i<=n;i++)
			if(f[i]==0)break;//如果有一个没有就退出
		i>n?cout<<"YES\n":cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：togeth1 (赞：1)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1624C)

### **[题意解析]**
有 $T$ 次询问，每个询问会给你一个长度为 $n$ 的数组 $a$。你可以对 $a_i$ 进行一个操作。
+ 把 $a_i$ 除以 $2$，并把结果向下取整。

问：能否通过这个操作，使得数组 $a$ 能变成 $n$ 的全排列。

### **[思路分析]**
我们思考一下，既然是 $n$ 的**全排列**，那肯定要把所有情况囊括进去，少一种都不行。而对于一个 $a_i$，要具备什么条件才能做一次除以 $2$ 的操作呢？

1. 当前的 $a_i$ 大于 $n$。
2. 如果 $a_i$ 已经出现过了，且 $a_i$ 除以 $2$ 之后**不能等于 $0$**。

如果满足这两个条件，那 $a_i$ 就可以一直除以 $2$，并且标记多一种全排列的情况。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[110],x;
bool vis[110],f;
/*vis用于标记全排列情况数*/
int main()
{
	cin>>T;
	while(T--){
		cin>>n;
		memset(vis,0,sizeof(vis));
		/*记得清0*/
		f=0; 
		for(int i=1; i<=n; i++){
			cin>>x;
			/*为了看得清晰，我就写了两个while，方便理解*/
			while(x>n)x/=2;
			while(vis[x]&&x/2!=0)x/=2;
			/*满足我们的两个条件，就能进行除以2的操作*/
			vis[x]=1;
			/*标记出现过*/
		}
		for(int i=1; i<=n; i++)
			if(!vis[i]){
				cout<<"NO\n";
				f=1;
				break;
			}
		/*因为是n的全排列，所以循环一遍n，一旦发现有一种情况没出现，直接输出NO*/
		if(!f)cout<<"YES\n"; 
		/*输出YES*/
	}
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

大家好，本蒟蒻来水一篇题解。

[CF1624C 题目传送门](https://www.luogu.com.cn/problem/CF1624C)

这道题用到的算法是贪心。

怎么贪心？肯定是找一个方法既能满足这一个，后面的也更有利。不难（~~很难~~）想到，每一个数变成能变的最大的一个。

为什么呢？如果每个数变成能变的最小的数，那么如果后面再来一个更小的数，那么它能变成的数不就都被前面的数给占了吗？

拿样例举个例子，$a=\{1,8,25,2\}$。如果每个数变成能变的最小的数，那么它的操作将会是这样的：

- 首先是 $1$，不变；

- 其次是 $8$，除了 $2$ 次变成 $2$；

- 然后再到 $25$，除了 $3$ 次变成 $3$；

- 最后是 $2$。我们惊喜地发现，居然变不了了。

反之，每个数变成能变成的最大的数，那么操作将会是这样：

- 首先是 $1$，不变；

- 其次是 $8$，除了 $1$ 次变成 $4$；

- 然后再到 $25$，除了 $3$ 次变成 $3$；

- 最后是 $2$，不变。

这样就能变成 $1\sim4$ 的全排列了。

AC 代码如下：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[60];
bool flag[60];//记录这个数有没有被占。
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        memset(flag,0,sizeof(flag));//一定记得初始化。
        int n;
        bool flag2=1;//有没有可能满足要求。
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)
        {
            while(a[i]>n||flag[a[i]])a[i]/=2;
  			//还大于 n 或这个数已经被占了就继续除以 2。
            if(a[i]==0)//如果除到 0 说明满足不了要求了。
            {
                flag2=0;
                break;
            }
            flag[a[i]]=1;
        }
        if(flag2)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
```

---

## 作者：AFewSuns (赞：1)

**CF764 Div.3（VP） 做题记录**

- A. plus One on the Subset

- B. Make AP

- $\color{red}\texttt{C. Division by Two and Permutation}$

- D. Palindromes Coloring

- E. Masha-forgetful

- F. Interacdive Problem

- G. MinOr Tree

### 题目大意

$t$ 组询问，每次给定一个长度为 $n$ 的序列 $a_i$。你可以进行无限次操作，每次操作选定一个数 $a_i$，让 $a_i \leftarrow \lfloor{\frac{a_i}{2}}\rfloor$。问最后能否让 $a$ 变成一个 $1 \sim n$ 的排列。

$1 \leq t \leq 10^4,1 \leq n \leq 50,1 \leq a_i \leq 10^9$

### 题目分析

首先，让 $a$ 成为一个 $1 \sim n$ 的排列的必要条件是 $1 \leq a_i \leq n$，所以可以先把所有 $>n$ 的 $a_i$ 除到 $<n$。

因为 $a$ 里面总共有 $n$ 个元素，要表示 $1 \sim n$ 的排列，必须做到所有元素不重不漏。用 $ck_i$ 记录一下 $i$ 这个数是否已经存在，然后枚举 $a_i$，让它不断除以 $2$，找到第一个空的位置，放进去。如果没有空则无解。

为什么这样是对的？如果某一个时刻 $a_i=a_j$，那么这之后它们永远相等，谁放哪个空位是没区别的。所以不会存在让位等情况。

每个 $a_i$ 最多会被除 $\log a_i$ 次 $2$，所以时间复杂度是 $O(tn\log W)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t,n,a[55];
bool ck[55],ans;
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) ck[i]=0;//记得清空 
		ans=1;
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++){
			while(a[i]>n) a[i]/=2;//先除到小于 n 为止 
			while(ck[a[i]]&&a[i]) a[i]/=2;
			if(!a[i]){//如果没有找到合适的位置，就无解 
				ans=0;
				break;
			}
			ck[a[i]]=1;//否则放进去 
		}
		if(!ans) printf("NO\n");
		else printf("YES\n");
	}
}
```

---

## 作者：hjfjwl (赞：0)

题目说给你一个长度为 $n$ 的数列，问你每次都可以把其中的一个数除以 $2$ 后使得新的数列的数字都在 $1 \sim n$ 里面并且不能重复。

我们对它进行一路除以 $2$，若果小于等于 $n$ 了但是这个数前面有了就要继续除以 $2$。当有一个数无法再除了也不符合要求就输出 NO。

AC code:
```cpp
#include <bits/stdc++.h>
using namespace std;
bool flag[55];
 
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(flag,false,sizeof(flag));//初始化
        int n;
        scanf("%d",&n);
        bool tot = false;
        for(int i = 1;i <= n;i++)
        {
            int x;
            scanf("%d",&x);
            while(true)
            {
                if(x <= n)
                {
                    if(flag[x] == false){flag[x] = true;break;}//小于等于n，并且也没有出现过
                }
                x >>= 1;
                if(x == 0)
                {
                    tot = true;
                    break;//NO
                }
            }
        }   
        if(!tot)puts("YES");
        else puts("NO");
    }   
    return 0;
}
```

---

## 作者：ys_kylin__ (赞：0)

今天其他地方比赛考了，发现好简单。

我们可以考虑贪心的做法，因为他是有规则的，也就是每次除的时候，选最大。为什么？因为大的数能变成小的数，小的数不能变成大的数。对于每个 $a _ i$，一直除以二直到小于 $n$ 且没出现过为止。最后判断每个数是否出现过就行了。时间有点极限，但不会超时。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[55],yes[55];
int main() {
	int t;
	scanf("%d",&t);
	while(t--){
		int n;
		scanf("%d",&n);
		memset(yes,0,sizeof yes);
		for(int i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			if(a[i]<=n) {
				if(yes[a[i]]==0)
					yes[a[i]]=1;//如果已经小于n，直接处理
				else goto el;
			}
			else {
				el:;
				while(a[i]) {//一直除以二
					if(a[i]<=n) {
						if(yes[a[i]]==0) {
							yes[a[i]]=1;
							break;
						}
					}
					a[i]/=2;
				}
			}
		}
	//	for(int i=1;i<=n;i++) printf("%d ",yes[i]);
	//	puts("");
		int fl=1;
		for(int i=1;i<=n;i++) {
			fl &= yes[i];
		}
		if(fl) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
//10
//1 4 16 32 62 43 13 31 144 87一组数据
```

---

## 作者：Zq_water (赞：0)

一道贪心题目，每次不停向下除以二，直到该位置没有被标记，那就给它打上标记。最后只需要查询一遍，每个数有没有被标记就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,a[55],vis[55];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        memset(vis,0,sizeof vis);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
            int t=a[i];
            while(t){
                if(t<=n&&!vis[t]){vis[t]=1;break;}
                else t/=2;
            }
        }
        int f=1;
        for(int i=1;i<=n;i++) if(!vis[i]) f=0;
        if(f) printf("YES\n");
        else printf("NO\n");
    }   
    return 0;
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现一个 $1∼n$ 的全排列就是 $1∼n$ 的 $n$ 个整数任意排列的一个数组，所以它有以下的特性：  

+ 数组里的所以数字小于等于 $n$。  

+ 数组里的所有数字不重复。  

根据以上特性模拟即可。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100];
bool f[100],flag;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		flag=true;
		memset(f,false,sizeof(f));
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			while(a[i]>n||f[a[i]]){
				a[i]/=2;
			}
			if(a[i]==0){
				cout<<"NO"<<endl;
				flag=false;
				break;
			}
			f[a[i]]=true;
		} 
		if(flag){
			cout<<"YES"<<endl;
		}
	}
	return 0;
} 
```


---

## 作者：scpchangyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1624C)

### [题目解析]

给定一个数组 $a$，不停除以 $2$ 并向下取整，问能否让数组 $a$ 是 $1 \sim n$ 的全排列。

### [思路]

模拟，但一直除以 $2$ 的前提条件是以下两个：

- $a_i$ 需要大于 $n$。

- $a_i$ 出现过，且除以 $2$ 后不为 $0$。

### [代码]

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cctype>
#include<climits>
#include<algorithm>
#include<map>
#include<queue>
#include<vector>
#include<ctime>
#include<string>
#include<cstring>
using namespace std;
int t,n,s[100],bj[100];
bool f=false; 
int main(){
	scanf("%d",&t);
	while(t--)
	{
		memset(bj,0,sizeof(bj));//清0 
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&s[i]);//输入 
		for(int i=1;i<=n;i++)
		{
			while(bj[s[i]]==1||n<s[i])//判断 
				s[i]=s[i]/2;
			if(s[i]!=0)//标记 
			{
				bj[s[i]]=1;
			}
			else
			{
				f=true;
				printf("NO\n");
				break;
			}
		}
		if(f==0)
			printf("YES\n");
		f=false;
	}
	return 0;
}
```

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1624C)

[$\color{red}{see}\space \color{green}{in}\space \color{blue}{my}\space \color{purple}{blog}$](https://www.luogu.com.cn/blog/liangbowen/solution-CF1624C)

小学生又双叒叕来写题解啦！

这题还是很简单的，甚至不需要像其他题解一样在最后扫全排列，**按顺序计算**即可。

从算法方面来说，就是**模拟**。

从全排列的定义入手，一个长度为 $n$ 的全排列满足两点：

+ 对于每个数 $a_i$，满足 $1 \le a_i \le n$。

+ 所有数互不相同。

我们只需要让每一个数疯狂除以 $2$，直到有一个空位，就停下。

如果一个数一直除，直到那个数都等于 $0$ 了，就说明无法构造全排列。

如果运行了 $n$ 次后仍然没有退出，说明 $n$ 个空位都被完好无缺地填好了。

肯定有同学会问，为什么能按顺序计算呢，万一后面的数比前面的数使用范围更广怎么办？

如果两个数可以到同样的位置，那么可以到达的更小的位置应该也是**相同的**。

这就说明，找最大的空位填即可。

代码实现相对较简单。

由于有多组数据，所以每次操作前要先**初始化**。

```cpp
//这一步非常重要，很容易忘掉。 
memset(use, false, sizeof(use));
```

输入完后，我们一直判断 $a_i$ 是否符合范围即可。

```cpp
while (true)
{
	if (a[i] == 0) return false;  //无法构造全排列。 
	if (1 <= a[i] && a[i] <= n && use[a[i]] == false)
	{
		//符合范围并且没用过，就标记并跳出。 
		use[a[i]] = true;
		break;
	}
	a[i] /= 2;
}
```

如果运行到这一步，就说明可以构造全排列。

```cpp
return true;  //返回可以就好了。
```

## 完整代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
bool use[55];
int a[55];
bool solve()
{
	memset(use, false, sizeof(use));  //这一步非常重要，很容易忘掉。 
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++)
	{
		while (true)
		{
			if (a[i] == 0) return false;  //无法构造全排列。 
			if (1 <= a[i] && a[i] <= n && use[a[i]] == false)
			{
				//符合范围并且没用过，就标记并跳出。 
				use[a[i]] = true;
				break;
			}
			a[i] /= 2;
		}
	}
	return true;
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		if (solve()) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

