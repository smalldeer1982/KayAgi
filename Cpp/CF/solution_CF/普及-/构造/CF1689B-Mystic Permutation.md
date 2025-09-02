# Mystic Permutation

## 题目描述

Monocarp is a little boy who lives in Byteland and he loves programming.

Recently, he found a permutation of length $ n $ . He has to come up with a mystic permutation. It has to be a new permutation such that it differs from the old one in each position.

More formally, if the old permutation is $ p_1,p_2,\ldots,p_n $ and the new one is $ q_1,q_2,\ldots,q_n $ it must hold that $ $$$p_1\neq q_1, p_2\neq q_2, \ldots ,p_n\neq q_n. $ $$$

Monocarp is afraid of lexicographically large permutations. Can you please help him to find the lexicographically minimal mystic permutation?

## 说明/提示

In the first test case possible permutations that are mystic are $ [2,3,1] $ and $ [3,1,2] $ . Lexicographically smaller of the two is $ [2,3,1] $ .

In the second test case, $ [1,2,3,4,5] $ is the lexicographically minimal permutation and it is also mystic.

In third test case possible mystic permutations are $ [1,2,4,3] $ , $ [1,4,2,3] $ , $ [1,4,3,2] $ , $ [3,1,4,2] $ , $ [3,2,4,1] $ , $ [3,4,2,1] $ , $ [4,1,2,3] $ , $ [4,1,3,2] $ and $ [4,3,2,1] $ . The smallest one is $ [1,2,4,3] $ .

## 样例 #1

### 输入

```
4
3
1 2 3
5
2 3 4 5 1
4
2 3 1 4
1
1```

### 输出

```
2 3 1
1 2 3 4 5
1 2 4 3
-1```

# 题解

## 作者：qW__Wp (赞：5)

### 题目大意：

给你一个包含 $1-n$ 的排列，你需要输出一个与原序列每位元素不同的**字典序最小**的序列，若无解，则输出 $-1$。

### 思路：

首先需要特判 $n$ 是否为 $1$，很明显，$n$ 为 $1$ 时无解，直接输出 $-1$ 即可。我们的贪心策略是：因为我们要使输出序列字典序最小，所以先从最小的数开始选，能放在前面就放在前面，否则就放在下一位。当放 $n$ 时，如果不能放在最后一位（也就是最后一位为 $n$，见样例一的第三组数据）那么就与 $n-1$ 位交换，将 $n-1$ 位的数放在第 $n$ 位 ，再将 $n$ 放在第 $n-1$ 位。

### AC代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int a[1005];
int a1[1005];
bool vis[1005];
bool visj[1005];
int main(){
	int t,n;
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));
		memset(visj,0,sizeof(visj));
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			a1[i]=a[i];
		}
		if(n==1){
			cout<<"-1\n";
			continue;
		}
		sort(a1+1,a1+n+1);
		for(int i=1;i<=n;i++){
			if(vis[i]){
				continue;
			}
			for(int j=1;j<=n;j++){
				if(a1[j]!=a[i]&&!visj[j]){
					a[i]=a1[j];
					vis[i]=1;
					visj[j]=1;
					break;
				}
			}
		}
		if(!vis[n]){
			a[n]=a[n-1];
			a[n-1]=a1[n];
		}
		for(int i=1;i<=n;i++){
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	return 0;
}
```
### 提醒：
复制粘贴一时快，作弊标签两星期！

---

## 作者：KidzzZip (赞：2)

题目传送门： [Mystic Permutation](https://www.luogu.com.cn/problem/CF1689B)

### 题目大意：
   给一个从 $[1,n]$ 的序列，需要输出与原序列各个元素的不同的且**字典序最小**的新序列。
   
------------

### 解题思路：
  - 首先，可以看出当 $n = 1$ 是一定是无解的，直接输出 $-1$ ；
  - 接着，因为由题目可知： $ n∈ [1,1000] $，完全可以用暴力枚举，且题目要求是字典序最小，那么从 $1$ 到 $n$ 枚举；
  - 当然如果第 $n$ 号数，也就是说轮到最后只剩下了 $n$ 并且只有的第 $n$ 号没有数字，那么把 $n$ 与 $n-1$ 的元素调换一下就行了。

------------
### AC代码：

```cpp
#include<bits/stdc++.h>
#define N 1008   
using namespace std;
int a[N];
bool flag[N];   //标记有没有被选过
int main()
{
    int n,m;
    cin>>n;
    while(n--)
    {
        memset(a,0,sizeof(a));  //养成好习惯，多组数据要重置
        memset(flag,false,sizeof(flag));//同上
        cin>>m;
        if(m==1)    //当m==1时,输出-1
        {
            cin>>a[1];
            cout<<"-1\n";
            continue;
        }
        for(int i=1;i<=m;i++)
        {
            cin>>a[i];
        }
        for(int i=1;i<=m;i++)
        {
            if(i==m-1&&!flag[a[m]])//判断m-1和a[m]的情况
            {
                cout<<a[m]<<' ';
                flag[a[m]]=true;
            }
            for(int j=1;j<=m;j++)//枚举
            {
                if(!flag[j]&&j!=a[i])
                {
                    cout<<j<<' ';
                    flag[j]=true;
                    break;
                }
            }
        }
        cout<<'\n';
    }
    return 0;
}
```



---

## 作者：skyskyCCC (赞：1)

## 前言。
题意：[题意传送门](https://www.luogu.com.cn/problem/CF1689B)。  
算法：暴力即可。
## 分析。
此题数据范围较小，所以可以使用暴力。

为了使这个序列字典序最小，我们可以考虑把元素从小到大插入在新的序列中，遇到与给出序列相同的或者是用过的就跳过这个数字。

是不是这么直接模拟就行了？当然不是的，这么写虽然思路是对的，但对于样例数据就会有漏洞，比如这种数据：
```
4
2 3 1 4
```
我们发现，如果按照上面的思路，就会形成新序列：
```
1 2 3 4(这个4不会被填进去，但只剩下这一个元素了)
```
发现与题意不符，也就是说，在此序列的第 $n$ 项正好是 $n$ 时，且第 $n$ 项之前的元素的排列不是有序数列，那么，最后剩下的元素只能是 $n$ 这个元素，就无法构成合法的新序列。

怎么解决这个问题呢？其实也非常简单。

我们可以先填 $n$ 这个元素，但是不能将其放在前几位，因为那样字典序会比较大，又不能将其放在最后一位上，所以可以先将它与放在第 $n-1$ 个位置上的元素交换，这样就可以保证前 $n-2$ 个元素字典序是最小的。但是因为这个第 $n$ 个元素，我们不可能将其放在更前面的地方以保证字典序**最小**。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int t,n,p[1005],pd[1005];
int main(){
	cin>>t;
	for (int c=1;c<=t;c++){
		for (int i=1;i<=1005;i++){
			pd[i]=0;
		}//判断数组清零
		cin>>n;
		if(n==1){//对于n=1的情况，无论如何也构不成新的合法序列
			cin>>p[1];
			cout<<"-1\n";
			continue;
		}
		for(int i=1;i<=n;i++) cin>>p[i];
		for(int i=1;i<=n;i++){
			if(i==n-1&&pd[p[n]]==0){//判断刚才所说的情况
				cout<<p[n]<<" ";
				pd[p[n]]=1;//标记已用过
			}
			for(int j=1;j<=n;j++){
				if(j!=p[i]&&pd[j]==0){//其它情况
					cout<<j<<" ";
					pd[j]=1;//标记已用过
					break;
				}
			}
		}
		cout<<"\n";
   } 
	return 0;
}
```
## 后记。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：jhdrgfj (赞：0)

## 思路

看到题目要求字典序最小，于是可以想到使用贪心。

想让字典序最小，那么就需要让越前面的数越小。我们可以设数组 $b$，对于每个 $b_i$ 有 $b_i=i$，这便是无限制下字典序最小的排列。

我们再考虑限制。要让对于每个 $a_i$ 都有 $a_i {=}\mathllap{/\,} b_i$，则只需在每个 $b_i = a_i$ 处将 $b_i$ 与 $b_{i-1}$ 和 $b_i+1$ 中较大的交换就行。

最后输出每个 $b_i$ 就好了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005],b[1005];
int main(){
	int t;
	cin>>t;
	while (t--){
		int n;
		cin>>n;
		for (int i=1;i<=n;i++){
			cin>>a[i];
			b[i]=i;
		}
		if (n==1){    //特判无解情况
			cout<<-1<<endl;
			continue;
		}
		for (int i=1;i<=n;i++){
			if (b[i]==a[i]){
				 if (i==n){
				 	swap(b[i-1],b[i]);    //此时只有 b[i-1] 能与 b[i] 交换
				 }else if (i==1){
				 	swap(b[i],b[i+1]);    //此时只有 b[i+1] 能与 b[i] 交换
				 }else{
				 	swap(b[i],b[i+1]>b[i-1]?b[i+1]:b[i-1]);   //将 b[i] 与相邻两数中较大的交换
				 }
			}
		}
		for (int i=1;i<=n;i++){
			cout<<b[i]<<" ";
		}
		cout<<endl;
	}
}
```


---

## 作者：legend_cn (赞：0)


## 1 简化题意
给定一个排列，求一个与原排列上的每一个数都不相同的排列，使这个排列的字典序尽可能小。
## 2 思路
首先，当 $n=1$ 时必定无解，所以需要在最前面进行特判，直接输出 $-1$。

然后开一个标记数组（在代码中就是 $F$ 数组），记录每个元素在新排列中有没有被用过。从 $1$ 开始枚举，使得得到的排列的字典序最小。如果这个元素不符合上面简化题意中的要求，就跳过这个数，试一试下一个数。

最后，每次当位置 $n$ 上的数不符合要求时，可以直接把新排列中的元素 $n$ 和元素 $n-1$ 互换就可以了。
## 3 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005];
int F[1005];
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		memset(F,0,sizeof F);
		int n;
		cin>>n;
		if(n==1)
		{
			cin>>a[1];
			cout<<"-1\n";
			continue;
		}
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			if(i==n-1&&F[a[n]]==0)
				cout<<a[n]<<" ",
				F[a[n]]=1;
			for(int j=1;j<=n;j++)
				if(j!=a[i]&&F[j]==0)
				{
					cout<<j<<" ";
					F[j]=1;
					break;
				}
		}
		cout<<"\n";
	} 
	return 0;
}
```


---

## 作者：arkerny (赞：0)

简明题意：

给定一个排列，求解一个与原排列每个位置上的数互不相同的排列，并且使这个排列的字典序尽可能小。

思路：

首先，考虑 $n=1$ 的情况，显然，当 $n=1$ 时必定无解，所以需要特判，当 $n=1$ 时输出 $-1$。

可以考虑开一个 $flag$ 数组，记录每个元素在新排列中的使用情况，从最小的元素开始枚举，使得所得排列的字典序最小，如有不符合位置要求的使用下一个数字跳过。

特别的，当不能新排列位置 $n$ 上的数不符合要求时，将新排列位置 $n$ 上的数与位置 $n-1$ 上的数交换即可。

代码如下：
``` cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define il inline
#define lowbit(_x) (_x&-_x)
#define clr(_arr,_val) memset(_arr,_val,sizeof(_arr));

int T;
int n,a[1010],flag[1010];

il void solve()
{
    clr(flag,0);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
    }
    if(n==1)
    {
        printf("-1\n");
        return ;
    }
    for(int i=1;i<=n;i++)
    {
        if(i==n-1&&flag[a[n]]==0)
        {
            printf("%d ",a[n]);
            flag[a[n]]=1;
        }
        for(int j=1;j<=n;j++)
        {
            if(j!=a[i]&&flag[j]==0)
            {
                printf("%d ",j);
                flag[j]=1;
                break;
            }
        } 
    }
    printf("\n");
    return ;
}

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        solve();
    }
    return 0;
}
```





---

## 作者：Tomato_Ya (赞：0)

## 题意
给你一个长度为 $n$ 的排列，让你用这 $n$ 个数组成一个新的的数列，使得这两个排列之间的任意一个相同位置的元素都不相同，且满足这个排列的字典序最小。如果无法构造出这样的序列则输出 $-1$。
## 思路
我们在构造数组时，必须让每个位置上的元素不同，当 $n$ 等于 $1$ 时，两个数列肯定相同，所以先在代码中进行判断。
```cpp
if(n==1){
    cout<<"-1\n";
    continue;
}
```
我们需要定义三个数组，数组 $a$ 存放第一个数列，数组 $s$ 存放答案，也就是第二个数列，数组 $b$ 是标记数组，记录这个数有没有用过。

由于要求字典序最小，所以双层循环从头枚举每一个 $j$ 和 $a_i$ 是否相等并且判断这个数之前用没有过，如果既不相等，也没用过，它就是答案，把它存进 $s$ 数组，并把这个数标记为用过，跳出循环。

最后再进行一次特判，如果第一个数列第 $n$ 个数是 $n$，并且第二个数列其它数都用了，不得不放 $n$ 时，把 $s_n$ 和 $s_{n-1}$ 交换，这个问题就解决了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1010],s[1010],b[1010],_;
int main(){
	cin>>_;
	while(_--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		if(n==1){
            cout<<"-1\n";
            continue;
        }
		memset(b,0,sizeof(b));
        s[n]=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(j!=a[i]&&!b[j]){
					s[i]=j;
                    b[j]=true;
                    break;
				}
			}
		}
		if(!s[n])s[n]=s[n-1],s[n-1]=a[n];
		for(int i=1;i<=n;i++)cout<<s[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：JAMES__KING (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1689B)

### 题目大意：

给定一个 $[1,n]$ 的排列，输出与原排列各个元素**顺序不同**，但元素值不改变，且**字典序最小**的新排列。

抓住关键点，顺序不同且字典序最小。

### 思路：

我们可以先令排列的字典序最小。然后进行循环，如果两个数组同下标位置的数值相同，则与这个位置前后两个位置的较大值进行交换，听起来有点绕，用代码显示其实就是这样：

```cpp
swap(b[i],b[i+1]>b[i-1]?b[i+1]:b[i-1])//b数组为记录最终答案的数组。
```

可以证明，进行交换的循环进行一次便可以令输出的排列满足条件。

其他没有什么注意点，但要特判 $n = 1$ 的情况，需输出 $-1$，因为不能满足**顺序不同**这个条件。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,a[1005],b[1005],n;
int main()
{
   cin>>T;
   while(T--)
   {
      cin>>n;
      for(int i=1;i<=n;i++) cin>>a[i],b[i]=i;//读入，设初始值
      if(n==1)//特判
      {
         cout<<"-1"<<"\n";
         continue;
      }
      for(int i=1;i<=n;i++)
         if(b[i]==a[i])
         {
            if(i==1) swap(b[1],b[2]);
            else if(i==n) swap(b[n],b[n-1]);//两种特别情况
            else swap(b[i],b[i+1]>b[i-1]?b[i+1]:b[i-1]);//普通交换
         }
      for(int i=1;i<=n;i++) cout<<b[i]<<" ";//输出
      cout<<"\n";//记得换行
   }
   return 0;
}
```


---

## 作者：linyihdfj (赞：0)

## B. Mystic Permutation ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16366229.html)
#### 题目描述 ####
[原题面](https://codeforces.com/problemset/problem/1689/B)

给定一个 $[1,n]$ 的排列，要求你构造一个 $[1,n]$ 的排列，使得这两个排列之间的任意一个相同位置的元素都不相同，且满足这个排列的字典序最小。
如果无法构造出这样的序列则输出 `-1`。
#### 题目分析 ####
一个非常正常的想法：把元素从小到大插入，如果遇到了相同的或者用过的就跳过。

但是这样会出现一种情况那就是序列的最后一个元素是 $n$，那么放到最后一个元素的时候就只剩下了 $n$，那么就无论如何也无法放置了。

这个问题也非常好解决：最后的这个元素 $n$ 我们肯定不能放在很靠前的位置，因为这样很明显字典序不会最小了，那么为了使得这个元素放得下我们就放在 $n-1$ 的位置上，让 $n-1$ 的位置上原本应该放的元素放到 $n$ 上，这样能保证前 $n-2$ 个一定是最小的，而不存在一种别的方法使得可以使得最后的两个元素比我们现在放置的更小而且前 $n-2$ 个依旧保持最小。

有一说一样例是真强，不然的话我应该发现不了这一点。
#### 代码详解 ####
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
bool flag[MAXN];
int a[MAXN];
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(flag,false,sizeof(flag));
		int n;
		cin>>n;
		if(n == 1){
			cin>>a[1];
			printf("-1\n");
			continue;
		}
		for(int i=1; i<=n; i++){
			cin>>a[i];
		}
		for(int i=1; i<=n; i++){
			if(i == n - 1 && !flag[a[n]]){
				printf("%d ",a[n]);
				flag[a[n]] = true;
			}
			for(int j=1; j<=n; j++){
				if(!flag[j] && j != a[i]){
					printf("%d ",j);
					flag[j] = true;
					break;
				}
			}
		}
		cout<<endl;
	} 
	return 0;
}

```

因为数据范围比较小，所以为了写的来更加舒服就写了这样非常暴力的做法，但是我们应该理解起来更容易一些。

---

## 作者：Chronomaly_Atlandis (赞：0)

$n≤1000$，爆搜就行。

只要先找到每一位的满足条件的最小的数就行。

但如果这一位没有满足条件的数，那就回溯到上一位，更改上一位的数。

需要特判 $n=1$ 的情况，绝对无解。

**Code**

```cpp
#include<iostream>
using namespace std;
const int maxn=1010;
int old[maxn],x[maxn],n;
bool vis[maxn],check;
void dfs(int stp){
    if(stp==n+1){
	check=1;
	return;
}
	for(int i=1;i<=n;i++){
		if(old[stp]==i||vis[i])continue;
		vis[i]=1;
		x[stp]=i;
		dfs(stp+1);
		vis[i]=0;
		if(check)break;
	}
}
int main(){
	cin.tie(NULL);cout.tie(NULL);
	int T;
	cin >> T;
	while(T--){
		cin >> n;
		for(int i=1;i<=n;i++)cin >> old[i];
	if(n==1){
	cout << "-1\n";
		continue;
}
    check=0;
		dfs(1);
		for(int i=1;i<=n;i++)cout << x[i] << " ";
	cout << "\n";
	}
	return 0;
}
```

---

## 作者：yanhao40340 (赞：0)

### 题意
给定 $[1,n]$ 的排列 $p$，对于 $p$，求出字典序最小的一个错排。
### 分析
此题 $n \leq 1000$，爆搜即可。

对于每一位，都找到最小的满足条件的数，并将其放入答案数组。

如果这一位找不到满足条件的数，那么回溯到上一位，改动上一位的数。

这里为方便查找数是否在答案数组中，用了 $\texttt{vis}$ 数组进行标记，每一次回溯时将单个标记重置，就不需要用 $\texttt{memset}$ 或 $\texttt{fill}$ 去设置初始值。

特别要注意的是，如果 $n$ 为 $1$，必定无解，要特判，输出 $-1$。而其它的 $n \in \mathbb{N}$ 均有解，这里简要说明一下（证明中的解不保证字典序最小）：

- $n=2$ 时，结论显然。

- 假设 $ n\leq k$ 时，结论成立。

- 考虑 $n=k+1$ 时，如果 $n$ 在 $p$ 的最后一项，那么将 $n$ 与前一项交换。如果 $n$ 不在 $p$ 的最后一项，那么将 $n$ 与后一项交换。这样交换的两项一定是错排，并且根据假设可知，其它项也满足条件，因此 $n=k+1$ 时有符合题意的解。从而得证。

复杂度不会证，实际跑起来大概在 $O(n \log n)$ 左右，特殊数据好像可以卡到 $O(n^2)$。

### 代码
代码中的 $\texttt{tar}$ 数组是用于存储输入的，而 $\texttt{a}$ 数组才是用来存答案的。
```cpp
#include <iostream>
using namespace std;
const int maxn=1005;
int tar[maxn],a[maxn],n;
bool vis[maxn],flg;//flg用于标记是否搜到答案
void dfs(int step){
	if (step==n+1){flg=true;return;}
	for (int i=1;i<=n;++i){
		if (tar[step]==i||vis[i]) continue;
		vis[i]=true;a[step]=i;dfs(step+1);vis[i]=false;
		if (flg) break;//如果搜到答案就break
	}
	return;
}
int main(){
	int t;scanf("%d",&t);
	while (t--){
		scanf("%d",&n);
		for (int i=1;i<=n;++i) scanf("%d",&tar[i]);
		if (n==1){puts("-1");continue;}//特判
		flg=false;dfs(1);
		for (int i=1;i<=n;++i) printf("%d ",a[i]);
		putchar('\n');
	}
	return 0;
}
```
完结撒花！

---

