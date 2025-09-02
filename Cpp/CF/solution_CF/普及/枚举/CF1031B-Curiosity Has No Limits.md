# Curiosity Has No Limits

## 题目描述

When Masha came to math classes today, she saw two integer sequences of length $ n - 1 $ on the blackboard. Let's denote the elements of the first sequence as $ a_i $ ( $ 0 \le a_i \le 3 $ ), and the elements of the second sequence as $ b_i $ ( $ 0 \le b_i \le 3 $ ).

Masha became interested if or not there is an integer sequence of length $ n $ , which elements we will denote as $ t_i $ ( $ 0 \le t_i \le 3 $ ), so that for every $ i $ ( $ 1 \le i \le n - 1 $ ) the following is true:

- $ a_i = t_i | t_{i + 1} $ (where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR)) and
- $ b_i = t_i \& t_{i + 1} $ (where $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND)).

The question appeared to be too difficult for Masha, so now she asked you to check whether such a sequence $ t_i $ of length $ n $ exists. If it exists, find such a sequence. If there are multiple such sequences, find any of them.

## 说明/提示

In the first example it's easy to see that the sequence from output satisfies the given conditions:

- $ t_1 | t_2 = (01_2) | (11_2) = (11_2) = 3 = a_1 $ and $ t_1 \& t_2 = (01_2) \& (11_2) = (01_2) = 1 = b_1 $ ;
- $ t_2 | t_3 = (11_2) | (10_2) = (11_2) = 3 = a_2 $ and $ t_2 \& t_3 = (11_2) \& (10_2) = (10_2) = 2 = b_2 $ ;
- $ t_3 | t_4 = (10_2) | (00_2) = (10_2) = 2 = a_3 $ and $ t_3 \& t_4 = (10_2) \& (00_2) = (00_2) = 0 = b_3 $ .

In the second example there is no such sequence.

## 样例 #1

### 输入

```
4
3 3 2
1 2 0
```

### 输出

```
YES
1 3 2 0 ```

## 样例 #2

### 输入

```
3
1 3
3 2
```

### 输出

```
NO```

# 题解

## 作者：DarkShadow (赞：4)

# CF1031B（枚举）

## 题目大意：

给出长度为 $N-1$ 的两个数组 $A$、$B$，求一个数组 $t$，满足：

- 对于 $i \in [1,n]$，$0 \le t_i \le 3$
- 对于 $i \in [1,n-1]$，$t_i | t_{i+1} = A_i$，$t_i \& t_{i+1} = B_i$

## 思路分析：

观察到本题虽然 $N \le 10^5$，但 $t$ 数组的每个元素只有 $0,1,2,3$ 四种情况，所以我们可以枚举 $t_1$，然后只需要枚举后面的每个元素递推就可以了。时间复杂度 $O(N)$。

## 完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=100005;
int n,A[N],B[N],way[N];
bool check(int a){
	way[1]=a;
	bool flag;
	for(int i=2;i<=n;i++){//枚举后面的元素
		flag=0;
		for(int j=0;j<=3;j++)
			if((way[i-1]|j)==A[i-1]&&(way[i-1]&j)==B[i-1]){
				flag=1,way[i]=j;
				break;
			}
		if(!flag)  return 0;
	}
	printf("YES\n");
	for(int i=1;i<=n;i++)
		printf("%d ",way[i]);
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<n;i++)
		scanf("%d",&B[i]);
	for(int i=0;i<=3;i++)//枚举第一个元素
		if(check(i))  return 0;
	printf("NO");
	return 0;
}
```

---

## 作者：Karry5307 (赞：2)

### 题意

给两个长度为 $n=1$ 的序列 $a,b$，构造一个长度为 $n$ 的序列 $t$ 使得 $a_i=t_i\mid t_{i+1},b_i=t_i\&t_{i+1}$.

$\texttt{Data Range:}2\leq n\leq 10^5,0\leq a_i,b_i\leq 3$

### 题解

比较一眼吧。

首先根据初赛看程序写结果的第一题可知 $a_i+b_i=t_{i}+t_{i+1}$。

然后注意到 $a_i$ 最大为 $3$ 所以 $0\leq t_i\leq 3$。同时，如果已经知道 $t_1$ 的话可以顺理成章的推出所有的 $t$。暴力枚举 $t_1$ 是多少然后边填数边 check 即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,flg;
ll x[MAXN],y[MAXN],t[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read();
	for(register int i=2;i<=n;i++)
	{
		x[i]=read();
	}
	for(register int i=2;i<=n;i++)
	{
		y[i]=read();
	}
	for(register int i=0;i<=3;i++)
	{
		t[1]=i,flg=1;
		for(register int j=2;j<=n;j++)
		{
			t[j]=x[j]+y[j]-t[j-1];
			flg&=(((t[j]|t[j-1])==x[j])&&((t[j]&t[j-1])==y[j]));
		}
		if(flg)
		{
			puts("YES");
			for(register int j=1;j<=n;j++)
			{
				printf("%d ",t[j]);
			}
			return 0;	
		}
	}
	return puts("NO"),0;
}
```

---

## 作者：5G信号塔报装 (赞：1)

## 题意

给定两个序列 $a,b$，求出序列 $t$，$t$ 满足

$$a_i=t_i\ \text{or} \ t_{i+1},b_i=t_i \ \text{or} \ t_{i+1}$$

数据范围: $0 \leq a_i, b_i, t_i \leq 3$，$2 \leq n \leq 10^5$

## 思路

首先关注数据范围，十分特别—— $a_i, b_i, t_i$ 
**最大只有** $3$！

那么对于 $10^5$ 的 $n$ 来讲，线性确定 $t$ 是绰绰有余的。

如何确定？观察满足 $t$ 的条件，可以发现 $t$  **最后一位确定了，其他的数也都随着后一位的改变而确定了！**

## Code

代码过程中的小插曲：

![](https://img.imgdb.cn/item/5ffea4a83ffa7d37b3caa360.jpg)

仔细阅读一遍英文题面：

> If there are multiple answers, print any of them.

**注意了！当最后一位有多种情况时，只需输出一种！**

----------

**Think Twice, Code Once**

```cpp
# include <bits/stdc++.h>
using namespace std;

# define MAXN 100005

int n, allojbk;
int a[MAXN], b[MAXN], t[MAXN];

void solve(int p) {
	t[n] = p;
	for (int i = n - 1; i >= 1; i--) {
		int ojbk = 0;
		for (int j = 0; j <= 3; j++) {
			t[i] = j; //更改当前位 
			if ((a[i] == (t[i] | t[i+1])) && (b[i] == (t[i] & t[i+1]))) {
				ojbk = 1; break;
			}
		}
		if (ojbk == 0) return; //不咋行 
	}
	printf("YES\n"); allojbk = 1;
	for (int i = 1; i <= n; i++) {
		printf("%d ", t[i]);
	}
	return;
}

signed main() {
	puts("5G 赋能未来！电信移动联通线路检修员 | 5G 信号塔报装");
	scanf("%d", &n);
	for (int i = 1; i < n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) scanf("%d", &b[i]);
	for (int i = 0; i < 4; i++) if (!allojbk)solve(i);
	if (!allojbk) puts("NO\n");
	return 0;
} 

// 调试记录
// (1) or,逻辑and 优先级根本性错误 
// (2) 还是这一行，t[i+1]打成t[i]+1 太丢人了。。。 
// (3) 输出了多次答案，应只需输出一次（即多个solve都可行） 
```

---

## 作者：StudyingFather (赞：0)

我们只需枚举 $ t_1 $ 的值就可以利用规律：$ a \& b + a | b = a+b $ 来推算序列其余项的值。如果发现出现矛盾，说明枚举的 $ t_1 $ 的值是非法的。

由于每个元素只有4种取值，所以不用担心TLE。

```cpp
#include <stdio.h>
int a[100005],b[100005],t[100005];
int main()
{
 int n;
 scanf("%d",&n);
 for(int i=1;i<n;i++)
  scanf("%d",&a[i]);
 for(int i=1;i<n;i++)
  scanf("%d",&b[i]);
 for(int i=0;i<=3;i++)
 {
  bool flag=true;
  t[0]=i;
  for(int j=1;j<n;j++)
  {
   t[j]=a[j]+b[j]-t[j-1];
   if((t[j-1]|t[j])!=a[j]||(t[j-1]&t[j])!=b[j])
   {
    flag=false;
    break;
   }
  }
  if(flag)
  {
   puts("YES");
   for(int i=0;i<n;i++)
    printf("%d ",t[i]);
   return 0;
  }
 }
 puts("NO");
 return 0;
}
```

---

## 作者：Ruff (赞：0)

首先题意：**给你两个长度为n-1的序列a,b，求一个长度为n的序列t使得对于任意1<=i<=n-1都有a 
i
​	 =t 
i
​	 ∣t 
i+1，b 
i
​	 =t 
i
​	 &t 
i+1**
# 观察数据可以发现序列a,b,t的每个数都在[0,3]内
## 于是就开始愉快的暴力
### 详情见注释


------------

~~~cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
template <typename T> inline void read(T &l)
{
    l=0;
    int w=1;
    char ch=0;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
        w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        l=(l<<1)+(l<<3)+(ch-'0');
        ch=getchar();
    }
    l*=w;
}//快读模板
int n,flag;
int a[100005],b[100005],t[100005];
int main()
{
    read(n);
    for(int i=1;i<=n-1;i++)
    read(a[i]);
    for(int i=1;i<=n-1;i++)
    read(b[i]);//正常数据读入
    memset(t,-1,sizeof(t));//初始化一下t数组
    for(int i=0;i<=3;i++)
    {
        t[1]=i;//暴力枚举t1
        int num=0;//这里比赛时可能写丑了,判断t序列是否符合题意
        for(int j=2;j<=n;j++)
        {
            for(int k=0;k<=3;k++)
            if(((k|t[j-1])==a[j-1])&&((k&t[j-1])==b[j-1]))
            t[j]=k;//很暴力的枚举了t[j],判断是否符合情况
        }
        for(int i=1;i<=n;i++)
        if(t[i]!=-1)num++;//这里是检查是否t中每一个数都是存在的
        if(num==n)break;//如果都存在那就直接跳出,否则继续枚举
    }
    for(int i=1;i<=n;i++)
    if(t[i]==-1)
    {
        printf("NO");
        return 0;
    }//枚举完发现不存在这样的序列t就输出NO
            printf("YES\n");
        for(int i=1;i<=n;i++)
        printf("%d ",t[i]);//输出t
    return 0;
}
~~~


------------

##### 还是挺水的吧~~因为数据给小所以第一反应就是暴力~~码风丑见谅



---

