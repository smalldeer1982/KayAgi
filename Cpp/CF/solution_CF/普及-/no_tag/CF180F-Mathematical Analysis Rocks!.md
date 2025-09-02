# Mathematical Analysis Rocks!

## 题目描述

Students of group 199 have written their lectures dismally. Now an exam on Mathematical Analysis is approaching and something has to be done asap (that is, quickly). Let's number the students of the group from 1 to $ n $ . Each student $ i $ ( $ 1<=i<=n $ ) has a best friend $ p[i] $ ( $ 1<=p[i]<=n $ ). In fact, each student is a best friend of exactly one student. In other words, all $ p[i] $ are different. It is possible that the group also has some really "special individuals" for who $ i=p[i] $ .

Each student wrote exactly one notebook of lecture notes. We know that the students agreed to act by the following algorithm:

- on the first day of revising each student studies his own Mathematical Analysis notes,
- in the morning of each following day each student gives the notebook to his best friend and takes a notebook from the student who calls him the best friend.

Thus, on the second day the student $ p[i] $ ( $ 1<=i<=n $ ) studies the $ i $ -th student's notes, on the third day the notes go to student $ p[p[i]] $ and so on. Due to some characteristics of the boys' friendship (see paragraph 1), each day each student has exactly one notebook to study.

You are given two sequences that describe the situation on the third and fourth days of revising:

- $ a_{1},a_{2},...,a_{n} $ , where $ a_{i} $ means the student who gets the $ i $ -th student's notebook on the third day of revising;
- $ b_{1},b_{2},...,b_{n} $ , where $ b_{i} $ means the student who gets the $ i $ -th student's notebook on the fourth day of revising.

You do not know array $ p $ , that is you do not know who is the best friend to who. Write a program that finds $ p $ by the given sequences $ a $ and $ b $ .

## 样例 #1

### 输入

```
4
2 1 4 3
3 4 2 1
```

### 输出

```
4 3 1 2 ```

## 样例 #2

### 输入

```
5
5 2 3 1 4
1 3 2 4 5
```

### 输出

```
4 3 2 5 1 ```

## 样例 #3

### 输入

```
2
1 2
2 1
```

### 输出

```
2 1 ```

# 题解

## 作者：_shine_ (赞：3)

## 题目大意
现在有 $n$ 个学生，每个人会写一本笔记，在第一天供自己查看，到了第二天以后，他每天都会与他最好的朋友分享笔记，现在给你第三天笔记本 $i$ 到了学生 $a_i$ 手里，和第四天笔记本 $i$ 到了学生 $b_i$ 手里，问你谁是谁的好朋友。
## 思路
这道题其实可以发现，第三天笔记本 $i$ 在学生 $a_i$ 手里，但是第四天却是到了学生 $b_i$ 手里，其实我们可以发现，这样的话，$a_i$ 的好朋友就是 $b_i$，$p_{a_i}=b_i$，这道题就解决了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int n,a[maxn],b[maxn],p[maxn];
signed main(){
	cin >> n;
	for(int i=1;i<=n;++i){
		cin >> a[i];
	}
	for(int i=1;i<=n;++i){
		cin >> b[i];
	}
	for(int i=1;i<=n;++i){
		p[a[i]]=b[i];
	}
	for(int i=1;i<=n;++i){
		cout << p[i] << " ";
	}
	return 0;
}
```


---

## 作者：pitiless0514 (赞：2)

入门级的题目(~~闲着无聊写题解~~)，开三个数组乱搞一下就是了。

他先是告诉了你，第一天我会复习自己的笔记，第三天和第四天每个人会复习哪些人的笔记。

因为每个人只会与他最好的朋友交换笔记，那么可以把第三天的第$i$本笔记由第 $ a $ 个人复习的，第四天由$b$复习的。

很么很显然那么 $ a $ 就与 $ b $ 就是好朋友，因为只有好朋友才可以交换笔记本，那么你就这样可以统计出哪些人是好朋友。具体看代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5+9;
int n,a[N],b[N],p[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		p[a[i]]=b[i];
	}
	for(int i=1;i<=n;i++){
		cout<<p[i]<<" ";
	}
	return 0;
}
```


---

## 作者：CQ_Bab (赞：1)

# 思路
这道题我们可以知道每个数都一定出现在 $a$ 中，所以无需考虑无解，那么我们可以将 $a_i$ 表示出来那么 $a_i=p_{p_{p_i}}$，然后再将 $b_i$ 也表示出来那么 $b_i=p_{p_{p_{p_i}}}$，所以 $p_{a_i}$ 就等于 $b_i$。
# 代码
```
#include <bits/stdc++.h>
using namespace std ;
int n,a[101010],b[101010],s[101010];
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) s[a[i]]=b[i];
	for(int i=1;i<=n;i++) cout<<s[i]<<endl;
	return false;
}
```


---

## 作者：晨曦墨凝 (赞：1)

这是一道很好的锻炼映射思维的橙题，本题解将讲解两种解法。

### 题意梳理

如果你确定你已经理解了题目，可以跳过下面几段直接看解法说明部分。

首先明确一点，题目中的朋友关系是单向的。

再了解一下题目描述的是一个什么样的过程，举个例子，假设有四个人：刘一、陈二、张三、李四，且刘一的朋友是陈二，陈二的朋友是张三，张三的朋友是李四（李四的朋友一定是刘一，但这对解题不重要）。

第一天，刘一会复习自己的笔记，第二天，刘一会将自己手中的笔记提供给陈二，而不是互换，第三天，陈二会将自己手中的笔记（原本刘一的笔记）提供给自己的朋友张三，第四天，张三会将自己手中的笔记给自己的朋友李四。

### 解法一：

观察样例，可得：$p_{a_{i}}=b_{i}$。

**证明**：可以类比无路径压缩的并查集或者最近公共祖先的那种追踪溯源的感觉。题目告诉我们 $a_i$ 与 $b_i$ 的含义，$a_{i}$ 代表第三天时第 $i$ 号人的笔记在 $a_{i}$ 手里，$b_{i}$ 代表第四天时第 $i$ 号人的笔记在 $b_{i}$ 手里。翻译一下，$a_i$ 即 $p_{p_{i}}$，$b_i$ 即 $p_{p_{p_{i}}}$，将 $a_i$ 带入 $b_i$，可得 $p_{a_{i}}=b_{i}$。

举个例子，在样例 $1$ 中：$a_1=2$，$b_1=3$，则 $p_2=3$。

```
#include <iostream>
#include <cstdio>
#define MAXN 100005
using namespace std;

int n, a[MAXN], b, p[MAXN];

int read()
{
    int x = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}

void init()
{
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
}

void solve()
{
    for (int i = 1; i <= n; ++i)
    {
        b = read();
        p[a[i]] = b;
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", p[i]);
}

int main()
{
   init();
   solve();
   return 0;
}
```

------------

### 解法二：
观察样例，可得：若 $a_{i}=b_{j}$ 则 $p_j = i$。

**证明**：可以类比无路径压缩的并查集或者最近公共祖先的那种追踪溯源的感觉，甲朋友的朋友是乙的朋友的朋友的朋友，那么甲即为乙的朋友。

$a_{i}=b_{j}$ 可写作 $p_{p_i}=p_{p_{p_j}}$，$i$ 即为甲，$j$ 即为乙，则易得 $p_j=i$。

由此规律建立映射关系即可。

```
#include <iostream>
#include <cstdio>
#define MAXN 100005
using namespace std;

int n, a[MAXN];

int read()
{
    int x = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}

void init()
{
    n = read();
    for (int i = 1; i <= n; ++i)
    {
        int tmp = read();
        a[tmp] = i;
    }
}

void solve()
{
    for (int i = 1; i <= n; ++i)
    {
        int tmp = read();
        printf("%d ", a[tmp]);
    }
}

int main()
{
    init();
    solve();
    return 0;
}
```

------------
### Update
[原始版本(2022.10.23)](https://www.luogu.com.cn/paste/nt7r9wet)

第一次更新(2022.11.18)
- 增加原始版本中非常规解法的证明；
- 将"常规解法"改称为"解法一"，将"非常规解法"改称为"解法二"（给出证明后感觉它没那么离谱了）；
- 改了一下排版。

---

## 作者：dengyujie2020 (赞：1)

### 题目要点：
1. 一个人有一个好盆友，而那**两人不一定互为好盆友；**（我理解错了哈哈 论审题的重要性）
2. $ai$ 表示在第三天是拿到第 $i$ 个笔记本的学生，而不是笔记本……

### 算法
其实有点像有向图（瞎猜的），但是我们只要求出**指向的关系**（比如 $a\to b$ )就行。

~~咳咳，安利一下~~[图论神器](https://csacademy.com/app/graph_editor/)

![](https://cdn.luogu.com.cn/upload/image_hosting/q8515jyf.png)
分析：

像这张图

$1\to3$ 

$2\to1$

$3\to4$

$4\to2$

因为第三天的笔记本到第四天时肯定是由 $i$ 给 $p[i]$ ，于是我们追踪笔记本的从 $a$ 到 $b$ 的位置，就可以求出 $a$ 是 $b$ 的好朋友。
## AC Code：

```
#include<bits/stdc++.h>//万能头
using namespace std;
int n,a[100005],b[100005],t[100005];
//t[i]表示第i个学生的好朋友是t[i]
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];//输入数据ab组
	for(int i=1;i<=n;i++)
		t[a[i]]=b[i]; //第三天拿到i笔记本的学生（也就是a[i])，把笔记本给了b[i],记录在t数组中
	for(int i=1;i<=n;i++)
		cout<<t[i]<<" ";
	return 0; //好习惯
}

```

---

## 作者：Leternity (赞：1)

## 思路
这道题是一道映射，通过题意，我们可以发现学生 $a_{i}$ 与  $b_{i}$ 一定是好朋友。为什么呢？ 因为题目说过：


```
	每个学生与他最好的朋友交换笔记本
```
所以我们就可以通过数组来统计出哪些人是好朋友了。
###  _AC Code_:
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,a[N],b[N],p[N];//p数组存储的是第i个学生的好朋友是谁 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
		p[a[i]]=b[i];//b[i]是a[i]的好朋友 
	}
	for(int i=1;i<=n;i++){
		cout<<p[i]<<" ";
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 思路

这道题很简单。根据题意，我们发现：第 $i$ 个学生第四天看的书是第三天看的书的主人的最好的朋友。也就是: `s[a[i]]=b[i]` （其中 $s$ 数组表示最终答案，$a$ 数组表示第三天看的书，$b$ 数组表示第四天看到书）。然后把 $s$ 输出即可。

## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
const int N=1e5+10;
int a[N],b[N];
int s[N];
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) s[a[i]]=b[i];
	for(int i=1;i<=n;i++) cout<<s[i]<<" ";
	return 0;
}
```


---

## 作者：DioxygenDifluoride (赞：0)

我们可以用一个类似桶的方法来完成此题。

如果 $a$ 与 $b$ 是好朋友，就把它们的关系记录下来，（关系是 $u_{a_i}=b_i$），最后输出所有关系。

### 代码实现
```cpp
#include<stdio.h>
int n,a[100001],b[100001],u[100001],i; 
main(){
	scanf("%d",&n);
	for(i=1;i<=n;++i)scanf("%lld",a+i);
	for(i=1;i<=n;++i)scanf("%lld",b+i);
	for(i=1;i<=n;++i)u[a[i]]=b[i];
	for(i=1;i<=n;++i)urintf("%d ",u[i]);
}
```

---

## 作者：wangkangyou (赞：0)

比较简单的一道模拟题。
分析题目，我们可以知道:

**第三天和第四天所拿到的同一本笔记本的两位同学必定是朋友关系。**


举个栗子：

设当前一共有 $4$ 位同学，每位同学的朋友关系如下：
- $1$ 与 $2$；
- $2$ 与 $3$；
- $3$ 与 $4$；
- $4$ 与 $1$。

(注意一个人可能有很多的朋友，但最好的朋友只有一个，而且如果 A 的最好的朋友是 B ,但是 B 的最好的朋友未必是 A。)

于是我们就有了一张类似于并查集的表 $f$:

$f[1] = 2,f[2] = 3,f[3] = 4,f[4] = 1;$

好，现在我们来模拟一下这个过程：

第一天第 $i$ 个笔记本分别对应的同学序列 $a_i$ 为：$ 1, 2, 3, 4 $ 。(因为是第一天，所有人的笔记本都在自己手上。)

第二天:
- $1$ 的**手上的**笔记本交换到了 $2$ 的手上；
- $2$ 的**手上的**笔记本交换到了 $3$ 的手上；
- $3$ 的**手上的**笔记本交换到了 $4$ 的手上；
- $4$ 的**手上的**笔记本交换到了 $1$ 的手上。

形成的序列是 $4, 1, 2, 3$ 。

**第三天**（输入的数据来了）:\
~~(还是一样)~~
- $1$ 的**手上的**笔记本交换到了 $2$ 的手上；
- $2$ 的**手上的**笔记本交换到了 $3$ 的手上；
- $3$ 的**手上的**笔记本交换到了 $4$ 的手上；
- $4$ 的**手上的**笔记本交换到了 $1$ 的手上。

但是~~~~~~~~~~

------------
由于同学们只会把自己**手上的**笔记本交给自己的朋友，他们却不知道手上的是不是他们自己的 (~~话说这是不是侵犯版权~~)。所以形成的序列是：

$3,4,1,2$

再接下去就是 

$2,3,4,1$

那我们从过程里可以看出：原本在 $1$ 手上的 $3$ 号笔记本到了 $2$ 手上，于是我们就能发现 $f[1] = 2$。以此类推,第四次的序列为:

$2,3,4,1$

与 $f$ 恰恰相同。

剩下的容大家自己推吧，上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int sum=0,f=1;
	char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(;isdigit(ch);ch=getchar()) sum=(sum<<3)+(sum<<1)+(ch^48);
	return sum*f;
}
void write(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar('0'+x%10);
	return;
}
const int inf=1e10;
const int N=1e7+10;
int a[N], b[N], s[N];
signed main(){
	int n = read ();
	for (int i = 1; i <= n; ++ i) a[i] = read ();
	for (int i = 1; i <= n; ++ i) b[i] = read ();
	for (int i = 1; i <= n; ++ i) s[a[i]] = b[i];
	for (int i = 1; i <= n; ++ i) write (s[i]), putchar (' '); 
	return 0;
}
```
$Thank$ $you$ $for$ $reading$~~

---

## 作者：wangyi_c (赞：0)

[你谷题目传送门](https://www.luogu.com.cn/problem/CF180F)

[CF 题目传送门](http://codeforces.com/problemset/problem/180/F)

[搭配博客食用更佳](https://www.luogu.com.cn/blog/wangyi-blog/solution-cf180f)

## 1.题目大意
给出一个 $n$ 和两个序列：$a_1,a_2,a_3\dots a_n$，$b_1,b_2,b_3\dots b_n$。

告诉我们一个规则：一个人编号为 $p_i$，这一天看第 $i$ 本笔记，下一天会给 $p_{p_i}$ 号学生，让我们求序列 $p_1,p_2,p_3\dots p_n$。

## 2.思路讲解

这道题其实就考一个**映射**的思想，就相当于序列 $a$ 通过映射关系 $p$ 得到序列 $b$，就只要倒推就可以求出 $p$。既然是 $b_i$ 为后，那么前一个下标就是 $a_i$，不难得出如下关系式：$p_{a_i}=b_i$。

## 3.AC 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100010],b[100010],p[100010]; 
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) scanf("%lld",&b[i]);
	for(int i=1;i<=n;i++) p[a[i]]=b[i];//执行关系式
	for(int i=1;i<=n;i++) cout<<p[i]<<" ";
	return 0;
}
```
_THE END_

谢谢观看

By wangyi

---

## 作者：s_c_lmlm_L (赞：0)

### 题意要点：

1. 得到过同一篇笔记的两人一定是好朋友

2. 第一天得到笔记一定是自己的

3. 第三天得到笔记与前两天无所联系

4. 第四天得到笔记的人与笔记主人可以看做是好朋友

# $AC$ $code$
```cpp
#include<iostream>
using namespace std;
int hao1[100010],hao2[100010];
int main()
{	
	int n,m;
   cin>>n;
   for(int i=1;i<=n;i++)
  		cin>>hao1[i];
   for(int i=1;i<=n;i++)
   {
   		cin>>m;
      hao2[hao1[i]]=m;
	}
   for(int i=1;i<=n;i++)
      cout<<hao2[i]<<" ";
}
```



---

## 作者：OIerBoy (赞：0)

## 分析
题目意思清晰明了，简单来说就是两个用同一个笔记的人一定是好朋友，因为每个人只会把自己手上的笔记，交给自己的好朋友。由于第一天的笔记是自己的，第二天笔迹在谁手上的尚且不知，所以说，第三天得到笔记的和前两天没有什么关系。就只用将第四天得到笔记的人认为是他的朋友就行了。

## 代码
```
#include<stdio.h>
int n,a[100009],b,p[100009];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	    scanf("%d",&a[i]);//第三天得到第i本笔记的人
	for(int i=1;i<=n;i++){
	    scanf("%d",&b);//第四天得到第i本笔记的人
		p[a[i]]=b;//直接认为第四天得到笔记的人是第三天的人。
	}
	for(int i=1;i<=n;i++)
	    printf("%d ",p[i]);
	return 0;
}
```

不知道为什么将这道题评 $\color{#BFBFBF}\small\texttt{灰题（暂无评定）}$，~~（白嫖一道也不错）~~，难度有点像 $\color{#FE4C61}\small\texttt{红题（入门）}$.

---

## 作者：Fearliciz (赞：0)

不知道这题是怎么排到 F 的，建议评红。

由于第三天和第四天是连着的，所以这两天复习的笔记相同的同学必定是朋友。

由此乱搞就可以了。

实际上看着样例找找规律都行。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010],n,x;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>x,b[a[i]]=x;
	for(int i=1;i<=n;i++) cout<<b[i]<<" ";
}
```


---

