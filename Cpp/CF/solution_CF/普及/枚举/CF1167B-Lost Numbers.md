# Lost Numbers

## 题目描述

This is an interactive problem. Remember to flush your output while communicating with the testing program. You may use fflush(stdout) in C++, system.out.flush() in Java, stdout.flush() in Python or flush(output) in Pascal to flush the output. If you use some other programming language, consult its documentation. You may also refer to the guide on interactive problems: <https://codeforces.com/blog/entry/45307>.

The jury guessed some array $ a $ consisting of $ 6 $ integers. There are $ 6 $ special numbers — $ 4 $ , $ 8 $ , $ 15 $ , $ 16 $ , $ 23 $ , $ 42 $ — and each of these numbers occurs in $ a $ exactly once (so, $ a $ is some permutation of these numbers).

You don't know anything about their order, but you are allowed to ask up to $ 4 $ queries. In each query, you may choose two indices $ i $ and $ j $ ( $ 1 \le i, j \le 6 $ , $ i $ and $ j $ are not necessarily distinct), and you will get the value of $ a_i \cdot a_j $ in return.

Can you guess the array $ a $ ?

The array $ a $ is fixed beforehand in each test, the interaction program doesn't try to adapt to your queries.

## 说明/提示

If you want to submit a hack for this problem, your test should contain exactly six space-separated integers $ a_1 $ , $ a_2 $ , ..., $ a_6 $ . Each of $ 6 $ special numbers should occur exactly once in the test. The test should be ended with a line break character.

## 样例 #1

### 输入

```
16
64
345
672```

### 输出

```
? 1 1
? 2 2
? 3 5
? 4 6
! 4 8 15 16 23 42```

# 题解

## 作者：rui_er (赞：4)

我们有一个由 $4,8,15,16,23,42$ 组成的排列，只能询问四次两个位置上的数的乘积。

下面是一些可能会考虑到的**错误的**策略（也是我做题时的思路），在这里放出体现我们的思考过程：

**策略 1**：每次询问两个相同的下标 $i$ 和它本身。

这种策略是最容易想到的，但是这样的话只能询问出 $4$ 个位置的值，剩下两个位置就没办法了。考虑其它策略。

**策略 2**：询问 $1$ 与 $1$ 的乘积，得到第一个数，此后三次询问 $(1,2)(2,3)(3,4)$。

和策略 1 有着同样的问题。

---

**正确策略**

通过上面的思考，我们得到了一个结论：**只有 $4$ 个位置是显然不行的**，考虑添加第五个位置。

我们可以询问 $(1,2)(2,3)(3,4)(4,5)$，这样就能方便的获得和五个位置相关的信息。

**具体解法**

在按照上面的策略询问完前五个数后得到了四个答案（代码中记做 $mutiple$），我们枚举所有 $6!=720$ 种可能的排列情况，对于每个排列，循环一遍判断是否符合询问得到的答案即可。

但是这样还不够，我们还要知道**满足四个答案的排列是唯一的**。

**唯一性证明**

自己口胡的，可能不太严谨，但是自认为比较好理解，可以手玩几个理解一下。

因为上面数列任意两个数的乘积都不同，我们想到，满足 $a_i\times a_j=k$ 的只有两种可能，即 $i$ 与 $j$ 交换。而上面就相当于固定了前五个数，因为数列中的六个数给定，可以通过排除来获得第六个数的信息。

唯一性得证，策略正确。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int a[7] = {-1, 4, 8, 15, 16, 23, 42}, multiple[5];

int main() {
	for(int i=1;i<=4;i++) {
		printf("? %d %d\n", i, i+1);
		fflush(stdout);
		scanf("%d", &multiple[i]);
	}
	do {
		bool _ = true;
		for(int i=1;i<=4;i++) {
			if(a[i] * a[i+1] != multiple[i]) {
				_ = false;
				break;
			}
		}
		if(_) {
			printf("! ");
			for(int i=1;i<=6;i++) printf("%d ", a[i]);
			puts("");
			break;
		}
	}while(next_permutation(a+1, a+7));
	return 0;
}
```

---

## 作者：mnesia (赞：2)

先对交互题做个介绍：这是一道比较典型的交互题。提交时，系统不会主动给你某一部分对解题有用的测试数据，而是根据你对系统的询问，提供给你相关的数据。一般来说，询问次数有一定的限制，能保证你不能仅通过询问系统得出正解。此类题目较为新颖，近些年来越来越多地出现在各类比赛中，因此大家需要特别关注并适当予以训练。

解这道题时，我原本想通过对 $(1,2)$、$(2,3)$、$(3,4)$、$(4,5)$ 区间分别询问，然后对其中是否含有 15、23、42 进行判断（具体是对形如 $(n,n + 2$ 这样的区间中的 $n + 1$ 那个数进行判断，如果 $n\cdot (n + 1)$ 与 $(n + 1)\cdot(n + 2)$ 都能被 15/23/42 整除，则 $n+1$ 一定为 15/23/42），然后对剩下的空缺进行依次计算并输出，结果发现测试数据的灵活程度远高于我的想象，如果按照此方法，代码将会变得非常冗长（截至我放弃这种方法时，代码已经长达 138 行，约 3k 个字符）。因此我考虑按照其他方法。

观察题目数据可以发现，要求我们计算的只是“4 8 15 16 23 42”的一种排列，而考虑到 $6! = 720$，时间复杂度并不大，因此我考虑暴力求解。

具体方法是：利用 STL 中的 $\text{next\_permutation}$ 函数。这个函数可以对给定的数组区间，求出其按照字典序的下一种排列方式（相对应的有 $\text{prev\_permutation}$）。同时该函数有 bool 型返回值，若还能求出当前区间的下一种排列，则返回 true，否则返回 false。据此，我们可以写出如下代码：
```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;
int num[7];
int product[5];//记录每次询问的乘积 | product[i] 表示 ans[i] * ans[i + 1] 的值 
int ans[7] = {0, 4, 8, 15, 16, 23, 42};

bool check(int *a)
{
	for(int i = 1;i <= 4;i++)
	{
		if(a[i] * a[i + 1] != product[i])
		{
			return false;
		}
	}
	return true;
}

int main()
{
	for(int i = 1;i <= 4;i++)
	{
		printf("? %d %d", i, i + 1);
		cout << endl;
		scanf("%d", product + i);
	}
	do
	{
		if(check(ans))
		{
			printf("! %d %d %d %d %d %d", ans[1], ans[2], ans[3], ans[4], ans[5], ans[6]);
			break;
		}
	}
	while(next_permutation(ans + 1, ans + 7)); 
	return 0;
}

```
这里对代码中输出部分做一个说明：在判断函数 `check` 中，由于只要有一个位置 n，使得 $\text{a[n]} \times \text{a[n + 1]} \neq \text{product[n]}$，函数就会返回 false，因此该函数能够保证返回 true 时，ans[1~5] 的值一定都与答案相符。从而可得出 ans[6] 的值与答案也一定相符。

另外做个提示：根据实测，交互题使用 `fflush(stdout);` 大概率不能达到预期效果，因此建议使用 `cout << endl;` 作为替代。

---

## 作者：Haphyxlos (赞：1)

# CF1167B Lost Numbers

[题目传送门](https://www.luogu.com.cn/problem/CF1167B)

本题是道思维题，还是比较简单的。

关于交互题的简介看本文文末。

### 思路

对于每次询问，我们可以询问$a_i$和$a_{i+1}$，然后再全排列枚举判断即可。

对于正确性的具体证明可以看看rui_er神仙的[证明](https://www.luogu.com.cn/blog/ak-ioi/solution-cf1167b)，写的太好了%%%

### 自己的简单证明
找$a_i$和$a_{i+1}$就一共能确定5个位置：$(1,2)(2,3)(3,4)(4,5)$，因为数组一共就6个数，所以第6个位置也就自然确定了。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const double eps=1e7-8;
const int INF=0x3f3f3f3f;
const int maxn=1e5+5;
const int maxm=1e6+5;
int num[10]={0,4,8,15,16,23,42},a[10];
int main(int argc, char const *argv[]){
	for(int i=1;i<=4;++i){
		printf("? %d %d\n",i,i+1); 
		fflush(stdout);
		scanf("%d",&a[i]);
	}
	do{
		bool f=true;
		for(int i=1;i<=4;++i){
			if(num[i]*num[i+1]!=a[i]){
				f=false;
				break;
			}
		}
		if(f){
			printf("! ");
			for(int i=1;i<=6;++i)printf("%d ",num[i]);
			fflush(stdout);
			return 0;
		}
	}while(next_permutation(num+1,num+7));
	return 0;
}
```
### 交互题简介
不同于传统题，交互题可以理解为有个问题需要你解决，通过和系统的交互，来得到一些信息，来解决该问题。

在每次输出后，一般需要清空缓存区，以免发生奇怪的错误。
- 对于 C/C++：fflush(stdout)；
- 对于 C++：std::cout << std::flush；
- 对于 Java：System.out.flush()；
- 对于 Python：stdout.flush()；
- 对于 Pascal：flush(output)；

本篇题解就到此结束了，如果喜欢，还请点个赞吧。

---

## 作者：StudyingFather (赞：1)

这其实是一道 pj 难度的简单交互题目。

我们考虑最暴力的方法：四次询问每次询问相邻的两个数的乘积： $ a_i \cdot a_{i+1} $ 。然后枚举所有可能的排列，判断是否满足给定的乘积即可。

因为排列的总数只有 $ 6!=720 $ 种，这样的效率是很高的。

```cpp
#include <cstdio>
#include <algorithm>
int a[15]={0,4,8,15,16,23,42},b[15];
using namespace std;
int main()
{
 for(int i=1;i<=4;i++)
 {
  printf("? %d %d\n",i,i+1);
  fflush(stdout);
  scanf("%d",&b[i]);
 }
 while(1)
 {
  int flag=1;
  for(int i=1;i<=4;i++)
   if(a[i]*a[i+1]!=b[i])
   {
    next_permutation(a+1,a+7);
    flag=0;
    break;
   }
  if(!flag)continue;
  printf("! ");
  for(int i=1;i<=6;i++)
   printf("%d ",a[i]);
  fflush(stdout);
  return 0;
 }
}
```


---

## 作者：wasa855 (赞：1)

首先可以发现这6个数中任意两个乘起来得到的乘积两两不同，所以询问$a[1]\times a[2]\ \ ,\ \  a[1]\times a[3]\ \ ,\ \  a[4]\times a[5]\ \ ,\ \  a[4]\times a[6]$。    
其中$a[1]\times a[2]\ \ ,\ \  a[1]\times a[3]\ \ $ 可以求出$a[1],a[2]$ 和 $a[1],a[3]$含有的数，合并一下即能求出$a[1]$，然后解出$a[2]$，$a[3]$，同理能解出$a[4]$，$a[5]$，$a[6]$。
所以询问出$a[1]\times a[2]\ \ ,\ \  a[1]\times a[3]\ \ ,\ \  a[4]\times a[5]\ \ ,\ \  a[4]\times a[6]$可以解出唯一答案。      
具体方法：暴力枚举每个排列，判断是否满足条件。   
代码：   
``` cpp
#include<bits/stdc++.h>
using namespace std;
int a[5];
int ans[7];
bool used[7];
int mp[7]={0,4,8,15,16,23,42};
bool judge()
{
	if(mp[ans[1]]*mp[ans[2]]!=a[1]) return false;
	if(mp[ans[1]]*mp[ans[3]]!=a[2]) return false;
	if(mp[ans[4]]*mp[ans[5]]!=a[3]) return false;
	if(mp[ans[4]]*mp[ans[6]]!=a[4]) return false;
	return true;
}
void dfs(int dep)
{
	if(dep==7)
	{
		if(judge())
		{
			printf("! ");
			for(int i=1;i<=6;i++)
			{
				printf("%d ",mp[ans[i]]);
			}
			fflush(stdout);
			exit(0);
		}
	}
	for(int i=1;i<=6;i++)
	{
		if(used[i]==false)
		{
			used[i]=true;
			ans[dep]=i;
			dfs(dep+1);
			used[i]=false;
		}
	}
}
int main()
{
	printf("? 1 2\n");
	fflush(stdout);
	scanf("%d",&a[1]);
	printf("? 1 3\n");
	fflush(stdout);
	scanf("%d",&a[2]);
	printf("? 4 5\n");
	fflush(stdout);
	scanf("%d",&a[3]);
	printf("? 4 6\n");
	fflush(stdout);
	scanf("%d",&a[4]);
	dfs(1);
	return 0;
}
```

---

## 作者：moosssi (赞：0)

先询问 $(1,1)$ 和 $(2,2)$ 把前两位确定下来。

在询问 $(3,4)$ 和 $(3,5)$ 暴力枚举三个数判断乘积是否满足。

确定了前五位后，最后一位自然就确定了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=10;
int a[N],ans[N];
int num[N]={4,8,15,16,23,42};
bool vis[N];
int main(){
	printf("? 1 1\n");
	fflush(stdout);
	scanf("%d",&a[1]);
	ans[1]=sqrt(a[1]);
	for(int i=0;i<=5;i++)if(num[i]==ans[1])vis[i]=1;// 确定后打个标记以防重选
	printf("? 2 2\n");
	fflush(stdout);
	scanf("%d",&a[2]);
	ans[2]=sqrt(a[2]);
	for(int i=0;i<=5;i++)if(num[i]==ans[2])vis[i]=1;// 同上 
	printf("? 3 4\n");
	fflush(stdout);	
	int x,l,r;
	scanf("%d",&x);
	for(int i=0;i<=5;i++){
		for(int j=i+1;j<=5;j++){
			if(vis[i]||vis[j])continue;
			if(num[i]*num[j]==x)l=i,r=j;//暴力枚举 
		}
	}
	int L,R;
	printf("? 3 5\n");
	fflush(stdout);	
	scanf("%d",&x);
	for(int i=0;i<=5;i++){
		for(int j=i+1;j<=5;j++){
			if(vis[i]||vis[j])continue;
			if(num[i]*num[j]==x)L=i,R=j;//暴力枚举 
		}
	}	
	if(l==R)swap(L,R);//这一部分在判断哪两个数相同，并把两个数换到l和L 
	else if(l!=L){
		swap(l,r);
		if(l==R)swap(L,R);
	}
	ans[3]=num[l],ans[4]=num[r],ans[5]=num[R];
	vis[l]=vis[r]=vis[R]=1;
	for(int i=0;i<=5;i++)if(!vis[i])ans[6]=num[i];//没选的即为最后一位 
	printf("! ");
	for(int i=1;i<=6;i++)printf("%d ",ans[i]);
	fflush(stdout);	
	return 0;
}
```


---

## 作者：Link_Space (赞：0)

一道比较简单的交互题，由于六个数只有四次询问机会，那么我们必须每两次询问就要确定三个数，如何使用两次询问确定三个数呢？

对于每三个数，我们询问 $1$ 与 $2$ 的乘积和 $2$ 与 $3$ 的乘积，如果有一个数同时是两个乘积的约数，那么这个数就是第二个数，知道了第二个数我们就知道了第一和第三个数，这道题就解决了。

但是考虑特殊情况，就是 $4，8，16$ 这三个数，他们任意两个的乘积都是其中任意一个数的倍数，对于这些情况我们只需要特判一下就可以了。详情见代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[10];
int num[10] = {0, 4, 8, 15, 16, 23, 42};
bool aim[100];
int main()
{
	aim[4] = aim[8] = aim[15] = aim[16] = aim[23] = aim[42] = 1;
	printf("? 1 2\n");
	fflush(stdout);
	int x12;
	scanf("%d", &x12);
	printf("? 2 3\n");
	fflush(stdout);
	int x23;
	scanf("%d", &x23);
	printf("? 4 5\n");
	fflush(stdout);
	int x45;
	scanf("%d", &x45);
	printf("? 5 6\n");
	fflush(stdout);
	int x56;
	scanf("%d", &x56);
	for (int i = 1; i <= 6;i++)
	{
		if(x12%num[i]==0&&aim[x12/num[i]]&&x12/num[i]!=num[i]&&x23%num[i]==0&&aim[x23/num[i]]&&x23/num[i]!=num[i])
			a[2] = num[i];
		if(x45%num[i]==0&&aim[x45/num[i]]&&x56%num[i]==0&&aim[x56/num[i]]&&x45/num[i]!=num[i]&&x56/num[i]!=num[i])
			a[5] = num[i];
	}
	a[1] = x12 / a[2];
	a[3] = x23 / a[2];
	a[4] = x45 / a[5];
	a[6] = x56 / a[5];
	printf("! ");
	for (int i = 1; i <= 6; i++)
		printf("%d ", a[i]);

	fflush(stdout);
}
```


---

## 作者：fmj_123 (赞：0)

容易发现，因为原数列没有$15/23/42$（以下数字按顺序一一对应）的倍数，亦没有数可组成这些数的倍数，所以对于 $(i,j)$ ，若乘积为 $15/23/42$ 的倍数，则 $i$ 或 $j$ 必有一个是 $15/23/42$。

那么如何判断是 $i$ 还是 $j$ 呢？另询问一对 $(i,k)$ 即可。若这个答案为 $15/23/42$ 的倍数，则是 $i$，否则便是 $j$。

另外的三个数为 $4/8/16$，若出现数据两两相乘，即组成 $32/64/128$。对此，同样询问 $(i,k)$ ，若仍旧为上述数的中任意一个，那么手推即可，否则，问题实际上变成了前面的“乘积为 $15/23/42$ 的倍数的题，依照上面的方法处理即可。

按照这种方法，我们可以做到 $2$ 次询问得出 $3$ 个数。将数列分成两半再处理便可得出数列。

这种方法相比枚举全排列快了不少，目前是最优解第一。~~在这种题上优化有意义吗~~

上代码
```
//写代码时较仓促，实际上函数间通用性仍可提高
#include<bits/stdc++.h>
using namespace std;
int x,xa,ans[10];
void spc(int x,int s,int tmp)
{
	cin>>xa;
	if (xa%x==0) ans[s+1]=x,ans[s+3]=xa/x,ans[s+2]=tmp/x;
	else ans[s+2]=x,ans[s+1]=tmp/x,ans[s+3]=xa/ans[s+1];
}
void alj(int X)
{
	cout<<"? "<<X+1<<" "<<X+2<<endl;
	fflush(stdout);
	cin>>x;
   //以下为42/23/15的处理
	if (x%42==0) 
	{
		int tmp=x/42;
	    cout<<"? "<<X+1<<" "<<X+3<<endl;
		fflush(stdout);
		spc(42,X,x);return ;
	}
	if (x%23==0)
	{
		int tmp=x/23;
		cout<<"? "<<X+1<<" "<<X+3<<endl;
		fflush(stdout);
		spc(23,X,x);return ;
	}
	if (x%15==0)
	{
		int tmp=x/15;
		cout<<"? "<<X+1<<" "<<X+3<<endl;
		fflush(stdout);
		spc(15,X,x);return ;
	}
   //以下为 4 8 16互乘处理
	if (x==32)
	{
		cout<<"? "<<X+1<<" "<<X+3<<endl;
		fflush(stdout);
		cin>>xa;
		if (xa==64) ans[X+1]=4,ans[X+2]=8,ans[X+3]=16;
		if (xa==128) ans[X+1]=8,ans[X+2]=4,ans[X+3]=16;
		if (xa%15==0) ans[X+1]=xa/15,ans[X+2]=x/ans[X+1],ans[X+3]=15;
		if (xa%23==0) ans[X+1]=xa/23,ans[X+2]=x/ans[X+1],ans[X+3]=23;
		if (xa%42==0) ans[X+1]=xa/42,ans[X+2]=x/ans[X+1],ans[X+3]=42;
		return ;
	}
	if (x==64)
	{
		cout<<"? "<<X+1<<" "<<X+3<<endl;
		fflush(stdout);
		cin>>xa;
		if (xa==32) ans[X+1]=4,ans[X+2]=16,ans[X+3]=8;
		if (xa==128) ans[X+1]=16,ans[X+2]=4,ans[X+3]=8;
		if (xa%15==0) ans[X+1]=xa/15,ans[X+2]=x/ans[X+1],ans[X+3]=15;
		if (xa%23==0) ans[X+1]=xa/23,ans[X+2]=x/ans[X+1],ans[X+3]=23;
		if (xa%42==0) ans[X+1]=xa/42,ans[X+2]=x/ans[X+1],ans[X+3]=42;
		return ;
	}
	if (x==128)
	{
		cout<<"? "<<X+1<<" "<<X+3<<endl;
		fflush(stdout);
		cin>>xa;
		if (xa==64) ans[X+1]=16,ans[X+2]=8,ans[X+3]=4;
		if (xa==32) ans[X+1]=8,ans[X+2]=16,ans[X+3]=4;
		if (xa%15==0) ans[X+1]=xa/15,ans[X+2]=x/ans[X+1],ans[X+3]=15;
		if (xa%23==0) ans[X+1]=xa/23,ans[X+2]=x/ans[X+1],ans[X+3]=23;
		if (xa%42==0) ans[X+1]=xa/42,ans[X+2]=x/ans[X+1],ans[X+3]=42;
		return ;
	}
}
int main()
{
	alj(0);
	alj(3);//分1 2 3 / 4 5 6 两段询问
	cout<<"! ";
	for (int i=1;i<=6;i++)
	  cout<<ans[i]<<" ";
	fflush(stdout);
	return 0;
}
```

---

## 作者：a1ioua (赞：0)

~~一道比较水的交互题~~

------------
分析：直接相邻两个位置问，能问到 4 个乘积，然后全排列，暴力获得 5 个数，那么第 6 个数就知道了。

要注意交互题的格式，**要换行**，不然你可以获得一个UKE。

好啦！
```cpp
for (int i = 1; i <= 4; i++) {
        printf("? %d %d\n", i, i + 1);
        fflush(stdout);
        scanf("%d", &b[i]);
    }询问成绩。
    do {
        bool f = 1;
        for (int i = 1; i <= 4; i++)
            if (a[i] * a[i + 1] != b[i]) {
                f = 0;
                break;
            }判断此排列是否是正确排列。
        if (f) {
            printf("! ");
            for (int i = 1; i <= 6; i++) printf("%d ", a[i]);
            fflush(stdout);
            return 0;得出解
        }
    } while (next_permutation(a + 1, a + 7));全排列来试。
```
对了，看各位大佬都没解释`next_permutation`，我来解释一下。

`next_permutation`可以让一个数组获得下一个全排列。

比如说数组 $(0,1,2)$，那么这个函数就可以把它变成 $(0,2,1)$。

---
谢谢观看。

---

