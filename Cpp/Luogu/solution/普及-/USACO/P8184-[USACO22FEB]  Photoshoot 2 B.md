# [USACO22FEB]  Photoshoot 2 B

## 题目描述

在一个熟悉的情景中，Farmer John 正在为他的 $N$ 头奶牛（$1 \leq N \leq 10^5$，编号为 $1 \cdots N$）排队拍照。  
初始时，奶牛从左到右的排列顺序为 $a_1, a_2, \cdots , a_N$。Farmer John 的目标是将奶牛从左到右排列成 $b_1, \cdots , b_N$ 的顺序。为了实现这一目标，他可以对排列顺序进行一系列修改。每次修改包括选择一头奶牛并将其向左移动若干位置。

请计算 Farmer John 将奶牛排列成目标顺序所需的最少修改次数。

## 说明/提示

- 测试用例 3-6 满足 $N \leq 100$。
- 测试用例 7-10 满足 $N \leq 5000$。
- 测试用例 11-14 没有额外限制。

## 样例 #1

### 输入

```
5
1 2 3 4 5
1 2 3 4 5```

### 输出

```
0```

## 样例 #2

### 输入

```
5
5 1 3 2 4
4 5 2 1 3```

### 输出

```
2```

# 题解

## 作者：cfkk (赞：4)

想要写出这道题就要想一个关键的问题：到底什么数应该移动？

自己想一下，想好了往下看。

# 正文开始：

相信大家刚拿到这道题，肯定会毫无头绪，但是我们设一个映射数组为 dep ，$dep_i$ 表示 $a_i$ 在 $b_i$ 中的位置，让我们以样例2举例：

$a=[5,1,3,2,4]$

$b=[4,5,2,1,3]$

$dep=[2,4,5,3,1]$

如果有这个数列，那么我们就会发现一个事实：一个数如果要往左移，那么左面一定有比它大的值。

所以问题就可以转换成左面有多少个大于 $dep_i$ 的值。

代码来喽：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    char ch=getchar();
    int s=0,w=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-'){w=-1;}
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        s=(s<<1)+(s<<3)+ch-48;
        ch=getchar();
    }
    return w*s;
}
inline void print(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>9){print(x/10);}
    putchar(x%10+'0');
}
int a[100001],b[100001],dep[100001],kep[100001];
signed main()
{
    int n=read();
    for(int i=1;i<=n;i++){a[i]=read();}
    for(int i=1;i<=n;i++){b[i]=read();dep[b[i]]=i;}
    for(int i=1;i<=n;i++){kep[i]=dep[a[i]];}//映射序列
    int cnt=0,x=0;
    for(int i=1;i<=n;i++)
    {
        x=x>kep[i]?x:kep[i];//求左面是否有比它大的值
        if(x>kep[i]){cnt++;}//如果有就答案加1 
    }
    print(cnt);
    return 0;
}

```


---

## 作者：CANTORSORT (赞：4)

这一题本质上是一种 **类逆序对**，

我们可以建立一个数组 $pos$ 表示一个值在 **目标序列 $b$** 中的位置，即：

$$
pos_{b_i}=i\ (1\le i\le n)
$$

那么，

由于序列 $a$ 中的每一个数字 **都会在序列 $b$ 中出现**，

所以我们就能令 $a_i=pos_{a_i}$。

于是，就可用类似于 **逆序对** 的方法求解。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],b[100005],pos[100005],maxn=0,ans=0;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++)
		scanf("%d",b+i),pos[b[i]]=i;
	for(int i=1;i<=n;i++)
		a[i]=pos[a[i]];
	for(int i=1;i<=n;i++)
	{
		if(a[i]>maxn)
			maxn=a[i];
		else
			++ans;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Zirnc (赞：3)

考虑 $O(N)$ 算法。

样例的数据比较简单，我们来换一个：
| | 0 |1 |2 |3 |4 | 
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |
| $a$ | 5 | 1 | 4 | 3 | 2 |
| $b$ | 4 | 5 | 2 | 1 | 3 |

实际上的对应关系是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/sooz6ibi.png)

1. $b[0]\neq a[0]$，于是将 $\text{(原来的)}a[2]$ 移动至下标 $0$。但是我们**不改变数组**（整个过程中都如此），仅仅知道需要这样做。
2. $b[1]= a[0]$。为什么对应的是 $a[0]$ 呢？因为之前已经将 $\text{(原来的)}a[2]$ 移动过去了，但是数组没改变，所以 $\text{(新的)}a[1]$ 实际上是 $\text{(原来的)}a[0]$。
3. $b[2]\neq a[1]$。所以将 $\text{(原来的)}a[4]$ 移动至下标 $1$。但是我们依然不改变数组。
4. $b[3]= a[1]$。在实际上，$a[1]$ 是 $\text{(新的)}a[3]$，因为前面插入了两个数。
5. $b[4]= a[3]$。同理，$\text{(原来的)}a[3]$ 实际上是 $\text{(新的)}a[4]$。因为它的前面其实只多了一个 $\text{(原来的)}a[4]=2$，所以只是往后移了一位。

过程就是这样，似乎有点复杂。

实现的过程中，我们遍历 $b$，用一个 $fix$ 值来修正对应 $a$ 的下标。也就是说 $b[i]$ 对应 $a[i-fix]$。 

当我们遇到这两个数不一样的情况，就要将 $a[i-fix]$ 后面的某个数（记为 $a[x]$）移动到当前数的前面，且 $\text{新}fix = \text{老}fix +1$。（这样到了 $b[i+1]$ 的时候，由于 $i+1-(\text{老}fix+1)=i-\text{老}fix$，所以还是对应 $a[i-\text{老}fix]$ **目前的**这个数）。

如果后面遇到了 $a[x]$，因为它实际上已经移动到前面去了，所以对应的数应该是 $a[x]$ 后面的数，所以 $\text{新}fix = \text{老}fix -1$ (由于$i-(\text{老}fix-1)=i+1-\text{老}fix$)，于是就对应了 $a[x+1]$。

怎么知道后面遇到了这个 $a[x]$ 呢？用数组打标记（即代码中 `flag[]`）即可。

由于本人说理能力太逊，建议~~必须~~配合代码食用。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[100005], b[100005];
int flag[100005];
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int fix = 0;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> b[i];
		while (flag[a[i-fix]] == 1) fix--; // 遇到 a[x]。注意是 while，因为可能遇到一连串都是往前移动过的。
		if (b[i] != a[i-fix]) {
			fix++;
			ans++;
			flag[b[i]] = 1;
		}
	}
	cout << ans << endl;
	return 0;
}
```

附 [USACO 官方题解](http://www.usaco.org/current/data/sol_prob2_bronze_feb22.html)，虽然我看不懂。

---

## 作者：ZZQF5677 (赞：0)

### 题意
有数组 $a$ 和数组 $b$，现在要通过进行最少的若干次数将 $a_x$ 移到 $a_y$ 左边，使得 $a$ 的所有元素的顺序与 $b$ 相等。

### 解题思路
#### 首先
除了开 $a$、$b$ 数组外，再开一个记录移动次数的 $ans$ 和记录 $a_i$ **这个值**是否被移动过得标记器 $va$。
```cpp
bool va[100005];
```

#### 然后 
进行 $n$ 次外层循环时，我们先得找到没被标记的 $a_i$ 为止：
```cpp
while (va[a[i]] == 1) {  //一直找到没被标记的。
   i++;
}
```

而每次下标 $j$ 就只要 $j \gets j + 1$ 就行，因为是要让 $a$ 数组变成 $b$ 数组，要以 $b_j$ 为参照物。对比 $a_i$ 与 $b_j$，如果不相同，那就象征着需要移动，$ans \gets ans + 1$ 就行，最后标记一下移动的数或没移动的数已经用过就行 $va_{a_i} \gets 1$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005], b[100005], n, ans;
bool va[100005];
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0', ch = getchar();
  }
  return x * f;
}
int main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
  }
  for (int i = 1; i <= n; i++) {
    b[i] = read();
  }
  for (int i = 1, j = 1; j <= n; j++) {
    while (va[a[i]] == 1) {  //一直找到没被标记的。
      i++;
    }
    if (a[i] != b[j]) {
      ans++;
      va[b[j]] = 1;  //标记b需要的数，也可以理解因为b的需要所以a移动了某个数，既然移动了，就要标记。
    } else {
      va[b[j]] = 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}
```

---

