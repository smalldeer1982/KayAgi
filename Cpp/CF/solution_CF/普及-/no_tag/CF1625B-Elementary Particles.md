# Elementary Particles

## 题目描述

Martians are actively engaged in interplanetary trade. Olymp City, the Martian city known for its spaceport, has become a place where goods from all the corners of our Galaxy come. To deliver even more freight from faraway planets, Martians need fast spaceships.

A group of scientists conducts experiments to build a fast engine for the new spaceship. In the current experiment, there are $ n $ elementary particles, the $ i $ -th of them has type $ a_i $ .

Denote a subsegment of the particle sequence ( $ a_1, a_2, \dots, a_n $ ) as a sequence ( $ a_l, a_{l+1}, \dots, a_r $ ) for some left bound $ l $ and right bound $ r $ ( $ 1 \le l \le r \le n $ ). For instance, the sequence $ (1\ 4\ 2\ 8\ 5\ 7) $ for $ l=2 $ and $ r=4 $ has the sequence $ (4\ 2\ 8) $ as a subsegment. Two subsegments are considered different if at least one bound of those subsegments differs.

Note that the subsegments can be equal as sequences but still considered different. For example, consider the sequence $ (1\ 1\ 1\ 1\ 1) $ and two of its subsegments: one with $ l=1 $ and $ r=3 $ and another with $ l=2 $ and $ r=4 $ . Both subsegments are equal to $ (1\ 1\ 1) $ , but still considered different, as their left and right bounds differ.

The scientists want to conduct a reaction to get two different subsegments of the same length. Denote this length $ k $ . The resulting pair of subsegments must be harmonious, i. e. for some $ i $ ( $ 1 \le i \le k $ ) it must be true that the types of particles on the $ i $ -th position are the same for these two subsegments. For example, the pair $ (1\ 7\ 3) $ and $ (4\ 7\ 8) $ is harmonious, as both subsegments have $ 7 $ on the second position. The pair $ (1\ 2\ 3) $ and $ (3\ 1\ 2) $ is not harmonious.

The longer are harmonious subsegments, the more chances for the scientists to design a fast engine. So, they asked you to calculate the maximal possible length of harmonious pair made of different subsegments.

## 说明/提示

The first test case is shown on the picture below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1625B/8f8e2ae794791a59d3657c5398bdb22d42498124.png)As you can see from it, you may choose the subsegments $ (2\ 1\ 3\ 4) $ and $ (3\ 1\ 5\ 2) $ , which are a harmonious pair. Their length is equal to $ 4 $ , so the answer is $ 4 $ .

In the second test case, you need to take two subsegments: one with $ l=1 $ and $ r=5 $ , and one with $ l=2 $ and $ r=6 $ . It's not hard to observe that these segments are a harmonious pair and considered different even though they are both equal to $ (1\ 1\ 1\ 1\ 1) $ .

In the third test case, you cannot make a harmonious pair, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
4
7
3 1 5 2 1 3 4
6
1 1 1 1 1 1
6
1 4 2 8 5 7
2
15 15```

### 输出

```
4
5
-1
1```

# 题解

## 作者：EC75 (赞：5)

### 思路

请注意：对于每一对最佳的字符串，正确的和谐字符串确实以最后一个字符结尾。

证明：假设它是错的。然后，我们可以将字符串向右扩展一个字符，它们将保持和谐。

现在，证明下面的陈述，这将帮助我们解决这个问题：如果答案是 $n-\min(v-u)$，其中最小值是所有 $u$ 和 $v$，这样 $u<v$ 以及 $a_u=a_v$。

证明：考虑两个元素 $u$ 和 $v$。这样的话，$u<v$，$a_u=a_v$。假设它们在一对和谐子串中处于相同位置，那这些子串的最大长度是多少？

通过上面的证明，我们知道可以将字符串向右展开。我们取以 $u$ 开头的第一个字符串和以 $v$ 开头的第二个字符串。在进行展开操作以后，我们得到的是长度为 $n-v+1$ 的串。

不过，这还不够。因此，我们也将字符串从左侧展开。展开后，字符串的长度将变为 $n-v+u$，做个幼儿园数学计算后，得到 $n-(v-u)$。$v-u$ 越小，长度越大。

为了解决这个问题，我们需要找到一对最近的相等元素。我们可以执行以下操作：存储每个元素的所有位置（即 $a_i=1$，$a_i=2$ 等的所有位置），然后我们在 $a_i$ 的基础上迭代，并检查相邻位置对并计算最小值，答案就出来了。

### 代码

看似很难，但是我们前面的一步步推算都是为了后面的结论。代码很简单：
```python
def solve():
    n = int(input())
    a = [int(x) for x in input().split()]
    pos = {}
    ans = -1
    for i in range(n):
        if a[i] in pos:
            ans = max(ans, pos[a[i]] + 1 + (n - 1 - i))
        pos[a[i]] = i
    print(ans)
for _ in range(int(input())):
    solve()
```
没错，结束了！

---

## 作者：alm_crax (赞：2)

## 题目[传送门](https://www.luogu.com.cn/problem/CF1625B)
### 1. 题目大意

在一个长度为 $n$ 的数组中，找出所有符合要求的两段中最长的。

### 2. 题目要求

- 这两段不相同。

- 两段的长度相同。

- 存在至少一个这两段中同一位置上的数相等。

## 思路

由于题目重点在于第二，三条要求，所以可以先找到在数组中不同位置的相等的数 $a_i$，$a_j$。
再从 $i$ 向左延展为 $1$~$i$，从 $j$ 向右延展为 $j$~$n$，取两段的和就是最大值。

则求长度的公式为 $i+n-j$。

由于 $n$ 固定，想要长度最大，则 $j-i$ 要尽可能小，即 $i$ 和 $j$ 的距离要小。

## 代码
代码具体有注释。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,l[150005],ans;//l数组记录同一个数有没有出现过
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        memset(l,0,sizeof(l));
        ans=-1;
        for(int i=1;i<=n;i++)
        {
            cin>>a;
            if(l[a])//之前出现过 
            {
               	ans=max(ans,i-l[a]+n);//公式 
			}
            l[a]=i;//记录 
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Xdl_rp (赞：0)

~~还是太水了~~

进入正题：
------------
要求两个长度相同的连续的序列，且有一位置上的数相等，说明整一个序列中这一个相等的数是至少出现了两次的。他们要长度最长，说明前一个数相同的数离最顶端的距离要长，且后一个相同的数要离最底端的距离要长，这才能满足数量最长。

例如：

$7$

$3 \ 1 \ 5 \ 2 \ 1 \ 3 \ 4$

有相同数的只有 $1$ 和 $3$，我们需要将最长长度算出来，可以定义一个数组 $pos$，遍历 $a$ 数组，对于每个数值 $x$，用 $pos_x$ 记录 $x$ 上一次出现的位置 当前遍历到的 $a_i$ 为 $x$，求出所有 $i-pos_x$ 中的最小值， 设最小值为 $gap$，最终答案就是 $n-gap$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int a[N], pos[N];
int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		int ans = -1;
		for (int i = 1; i <= n; i++) {
			if (pos[a[i]] != 0) {
				ans = max(ans, pos[a[i]] + n - i);
			}
			pos[a[i]] = i;
		}
		cout << ans << endl;
		memset(pos, 0, sizeof(pos));
	}
	return 0;
}
```


---

## 作者：Disjoint_cat (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1625B)

先说结论：令 $t$ 为 $\min(j-i)(i<j,a_i=a_j)$，那么答案是 $n-t$。

我们可以把这两段数理解为把靠左的一段数向右移动，使一个数移动到它右边一个相同的数。

为了方便，此处使用样例第一组数据来说。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1625B/8f8e2ae794791a59d3657c5398bdb22d42498124.png)

这里，我们可以把第一段数右移三个数，这样左边的 $1$ 就移动到了右边的 $1$ 处。

显然，移动的数越少，那么数段的长度就可以更大。举个栗子，如果我们要把左边的 $3$ 就移动到右边的 $3$，就最多只能选择 $\{3,1\}$ 和 $\{3,4\}$，显然比答案的短。而且我们应该把数段靠到端点处。

那么数段的长度是多少呢？设 $t$ 为最相邻的相同数的距离，则第二段数中最左边 $t$ 个数无法选中，而右端可以到 $a_n$ 处。所以答案是 $n-t$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=150005;
int T,n,a[N],last[N],ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=N;i++)last[i]=0;
		ans=0;
		for(int i=1;i<=n;i++)
		{
			if(last[a[i]]>0)ans=max(ans,n-i+last[a[i]]);
			last[a[i]]=i;
		}
		if(ans==0)printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：xiaoqinglang11 (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/CF1625B)

## 题目大意
有一个长度为 $n$ 的数组，在数组中找出不同的两段：

1. **长度**相同；

2. **至少**有**一个位置**上的数**相等**。

（$t$ 组数据）

## 数据范围
- $1 \leq t \leq 100$

- $2 \leq n \leq 1.5 * 10^5$

- $\sum N \leq 3 * 10^5$

- $1 \leq a_i \leq 1.5 * 10^5$

## 思路
### 关健先找到相同的数，使他们的距离最短。

为什么要使它们距离最短呢？

设找到的两个相同的数分别为 $a_i,a_j (i<j)$，

则以它们为相同数的两段长度相等的子串长度就为 $i + n - j$。

使 $i + n - j$ 最大，因 $n$ 不变，即使 $|i - j|$ 最大。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int ai;
int last[150005];//记录每个数上次出现的位置
int main()
{
	scanf("%d",&t);//t组数据
	while(t--)
	{
		memset(last,0,sizeof(last));
		scanf("%d",&n);
		int ans=-1;//初始化为-1，若没被更新也可以直接输出
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&ai);
			if(last[ai])//若a[i]已出现过
				if(n-i+last[ai]>ans)//更新ans
					ans=n-i+last[ai];
			last[ai]=i;//记录
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：zbk233 (赞：0)

## 解题思路

一道简单的思维题。

先让我们考虑如下情况：

```
1 2 3 4 5
9 8 7 2 6

```

显然，两个序列只有 $2$ 是相同的。

如何求出题目中所要求的序列的长度呢？

为简化过程，我们把两个原序列化为：

```
* 2 * * *
* * * 2 *

```

易得，```* 2 *``` 是题目所求的序列。

实际上，这个简化后的序列中 ```*``` 可以变为任何数字，因为这个序列只有 $2$ 是有效的。

那么 ```*``` 的个数是如何得来的呢？

由第一个序列可以看出，$2$ 的前面有 $1$ 个 ```*```，后面有 $3$ 个 ```*```，我们把这个数量记录下来。

由第二个序列可以看出，$2$ 的前面有 $3$ 个 ```*```，后面有 $1$ 个 ```*```，我们把这个数量记录下来。

我们把 $2$ 前面与后面的 ```*``` 数量求最小值，即得最终序列里 $2$ 前面与后面 ```*``` 的数量。

## 代码实现

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int a[150005];
int t[150005];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T,n;
	cin>>T;
	while(T--){
		memset(t,0,sizeof(t));
		cin>>n;
		int ans=-1;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(!t[a[i]]){
				t[a[i]]=i;
			}else{
				ans=max(ans,t[a[i]]+n-i);
				t[a[i]]=i;
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1625B](https://www.luogu.com.cn/problem/CF1625B)

* **【题目大意】**

给定一个序列 $a$，定义它的子串 $a_{l_1,r_1}$ 与 $a_{l_2,r_2}$ 相同，当且仅当 $l_1=l_2\land r_1=r_2$。

找出两个子序列 $b=a_{l_1,r_1}$ 与 $c=a_{l_2,r_2}$ 且 $b\neq c$，使得他们长度相等且 $\exists 1\leq i\leq |b|,b_i=c_i$。

* **【解题思路】**

首先我们只要找到两个相等的元素，我们就可以找到满足条件的子串。设这两个元素为 $a_i$ 与 $a_j$（$i<j$），则我们可以构造出 $b=a_{1,i+n-j},c=a_{j-i+1,n}$，显然他们的长度均为 $i+n-j-1$。可以看出，这两个相等的元素离得越近，它们产生的答案就越大。那么，我们开桶记录每个元素上次出现的位置即可。

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

array<int,150001> bucket;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	bucket.fill(-1);
	while(testcnt--)
	{
		int cnt,tmp,ans=-1;
		cin>>cnt;
		for(int i=1;i<=cnt;i++)
		{
			cin>>tmp;
			if(bucket[tmp]==-1)
				bucket[tmp]=i;
			else
				ans=max(ans,bucket[tmp]+cnt-i),bucket[tmp]=i;
		}
		for(int i=0;i<=150000;i++)
			bucket[i]=-1;
		cout<<ans<<'\n';
	}
	return 0;
}


```

---

## 作者：heaksicn (赞：0)

## 1 题意
给一个长度为 $n$ 的序列 $a$，在其中选取两个长度相同的连续子序列，使得这两个序列至少有一位是相等的。

求选取序列的最长长度。

多组数据。
## 2 思路
假定这两个序列只有一位一样。

为了使序列总长最长，那么我们应该使一样的那一位的前面和后面尽量长。

那么，一样的那一位在大的序列中的距离应该尽量小。

开一个桶维护即可。

时间复杂度 $O(Tn)$。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int T,n; 
int a[150001],s[150001],lst[150001];//s为这个数出现的次数，lst为这个数上一次出现的位置
int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=150000;i++) s[i]=0,lst[i]=0;//清空
		bool flag=0;
		int ans=-1;
		for(int i=1;i<=n;i++) a[i]=read(); 
		for(int i=1;i<=n;i++){
			s[a[i]]++;
			if(s[a[i]]>1) flag=1;//存在答案
			//cout<<lst[a[i]]<<" "<<i<<endl;
			if(s[a[i]]>1)ans=max(ans,lst[a[i]]+n-i);//求出当前答案
			lst[a[i]]=i;//更新
			//cout<<ans<<endl;
		}
		if(flag==0){//不存在答案
			cout<<-1<<endl;
		}else cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：zhongcy (赞：0)

## Solution

------------
对于每一对满足条件的子集，都满足右边的子集以数组末尾数字结尾。



Proof:假设这是错的。

如果将数组向右扩展一个数字，那么左边的子集可以向左扩展一位，右边的子集向右扩展一位。此时，它们仍然满足条件。

与假设矛盾。得证。

------------

根据以上的证明，我们就知道最佳的答案是：  $n-\min(x-y)$   
其中  $x,y$  满足  $x>y$   且   $a_x=a_y$

为了在2s内解决问题，我们需要快速查找一对最近的相等元素。可以考虑建立一个pos数组，存储每个数字最近出现的位置。每次输入已经存在的数字时，就计算并更新答案。

时间复杂度   $O(tn)$

## Code

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans=-1,pos[150001];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;ans=-1;
		memset(pos,0,sizeof(pos));
		for(int x,i=1;i<=n;i++)
		{
			cin>>x;
			if(pos[x])//如果出现过x
				ans=max(ans,n-i+pos[x]);//更新答案
			pos[x]=i;//将x最近出现的位置设置为i
		}
		cout<<ans<<"\n";
	} 
	return 0;
} 
```

------------


---

