# Suspects

## 题目描述

As Sherlock Holmes was investigating a crime, he identified $ n $ suspects. He knows for sure that exactly one of them committed the crime. To find out which one did it, the detective lines up the suspects and numbered them from $ 1 $ to $ n $ . After that, he asked each one: "Which one committed the crime?". Suspect number $ i $ answered either "The crime was committed by suspect number $ a_{i} $ ", or "Suspect number $ a_{i} $ didn't commit the crime". Also, the suspect could say so about himself ( $ a_{i}=i $ ).

Sherlock Holmes understood for sure that exactly $ m $ answers were the truth and all other answers were a lie. Now help him understand this: which suspect lied and which one told the truth?

## 说明/提示

The first sample has the single person and he confesses to the crime, and Sherlock Holmes knows that one person is telling the truth. That means that this person is telling the truth.

In the second sample there are three suspects and each one denies his guilt. Sherlock Holmes knows that only two of them are telling the truth. Any one of them can be the criminal, so we don't know for any of them, whether this person is telling the truth or not.

In the third sample the second and the fourth suspect defend the first and the third one. But only one is telling the truth, thus, the first or the third one is the criminal. Both of them can be criminals, so the second and the fourth one can either be lying or telling the truth. The first and the third one are lying for sure as they are blaming the second and the fourth one.

## 样例 #1

### 输入

```
1 1
+1
```

### 输出

```
Truth
```

## 样例 #2

### 输入

```
3 2
-1
-2
-3
```

### 输出

```
Not defined
Not defined
Not defined
```

## 样例 #3

### 输入

```
4 1
+2
-3
+4
-1
```

### 输出

```
Lie
Not defined
Lie
Not defined
```

# 题解

## 作者：WYFwyf (赞：7)

将输入定为int型

然后依次假设每个人都是罪犯，然后判断 
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,i,num[100100],yes[100100],no[100010],ans_no=0,ans_maybe=0,ans_is[100100];
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>num[i];
		if(num[i]>0)
		 yes[num[i]]++;    //说第i个人是罪犯的人数
		else
		{
			no[-num[i]]++; //说第i个人不是罪犯的人数
			ans_no++;      //说不是罪犯的总人数    
		}
	}
	for(i=1;i<=n;i++)
	{
		if(yes[i]+ans_no-no[i]==m)
	 	{
	 		ans_is[i]=1;
	 		ans_maybe++;   //可能是罪犯的人数
	 	}
	}	 
	for(i=1;i<=n;i++)
	{
		if(num[i]>0)
		{
			if(ans_maybe==1&&ans_is[num[i]]==1)
			cout<<"Truth"<<endl;
			else if(ans_is[num[i]]==0)
			cout<<"Lie"<<endl;
			else
			cout<<"Not defined"<<endl;
		}
		else 
		{
			if(ans_is[-num[i]]==0)
			cout<<"Truth"<<endl;
			else if(ans_maybe==1)
			cout<<"Lie"<<endl;
			else
			cout<<"Not defined"<<endl;
		}
	}
	return 0;
}
```

---

## 作者：OIerZhao_1025 (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/CF156B)

## 题意
有 $n$ 个嫌疑人，$n$ 个嫌疑人中只有一个是罪犯。嫌疑人从 $1$ 到 $n$ 编号，并依次回答：“犯罪是由第 $a_i$ 号嫌疑人实施的”或者“第 $a_i$ 个嫌疑人没有实施犯罪”。知道恰好有 $m$ 个答案是真话，其它的都是谎言。你的任务是确定每个嫌疑人说的是谎话还是真话。

## 思路
直接暴力枚举依次设每个嫌疑人为罪犯，接下来看每一个人的话是否符合，如果不符合，那么就切换到下一个人继续暴力，如果符合直接输出每一个人是否说的是真话就可以。

## code
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
const int maxn=1e5+10;//定值
int n,m,i,num[maxn],yes[maxn],no[maxn],ano,amb,ais[maxn];//全局变量
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++)//依次设
	{
		cin>>num[i];
		if(num[i]>0)yes[num[i]]++; 
		else
		{
			no[-num[i]]++;
			ano++;       
		}
	}
	for(i=1;i<=n;i++)
		if(yes[i]+ano-no[i]==m)
	 	{
	 		ais[i]=1;
	 		amb++;   
	 	}
	for(i=1;i<=n;i++)
	{
		if(num[i]>0)//两种情况判断
		{
			if(amb==1&&ais[num[i]]==1) cout<<"Truth"<<endl;//三种情况判断
			else if(ais[num[i]]==0) cout<<"Lie"<<endl;
			else cout<<"Not defined"<<endl;
		}
		else 
		{
			if(ais[-num[i]]==0) cout<<"Truth"<<endl;//三种情况判断
			else if(amb==1) cout<<"Lie"<<endl;
			else cout<<"Not defined"<<endl;
		}
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：5)

## CF156B Suspects 题解

### 解题思路

#### 首先，我们发现这道题很类似一道 $\texttt{逻辑推理}$ 题：

逻辑推理题有一种简便的方法，那就是枚举每一个嫌疑人，从而锁定谁说了真话，谁说了假话。

但是这时的复杂度是 $O(n^2)$，完全过不了。

此时我们还可以请来万能的**桶**，以空间换时间。我们此时可以把每一个指责 $a_i$ 的人和每一个为 $a_i$ 辩护的人都分别装在桶里，成功将复杂度降为 $O(n)$。

#### 判断输出时细节比较多：

首先，我们用 $t$ 表示嫌疑人的数量，用 $d_i$ 表示第 $i$ 个人是不是嫌疑人，用 $a_i$ 表示第 $i$ 个人指责或辩护的人。

我们可以推出，在第 $i$ 个人**指责**第 $a_i$ 个人时：

1. 如果 $t<2$ 且 $d_i$ 为 $\texttt{True}$，输出：“$\texttt{Truth}$”。
1. 如果不符合 $1$ 的条件，且 $d_i$ 为 $\texttt{False}$，输出：“$\texttt{Lie}$”。
1. 如果不符合 $1$ 的条件，且不符合 $2$ 的条件，输出：“$\texttt{Not defined}$”。

在第 $i$ 个人为第 $a_i$ 个人**辩护**时：

1. 如果 $d_i$ 为 $\texttt{False}$，输出：“$\texttt{Truth}$”。
1. 如果不符合 $1$ 的条件，且 $t<2$，输出：“$\texttt{Lie}$”。
1. 如果不符合 $1$ 的条件，且不符合 $2$ 的条件，输出：“$\texttt{Not defined}$”。

#### 注意：在判断输出时，这几个判断顺序不能颠倒哦！

### 参考代码
```cpp
#include<bits/stdc--.h>
using namespace std;
int n , m , a[100005] , ayes[100005] , ano[100005] , yes , no , flag;
char c;
bool b[100005] , d[100005];
int main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 1 ; i <= n ; i++)
	{
		cin >> c >> a[i];
		if(c == '+')
		{
			b[i] = 1;
			ayes[a[i]]++;
			yes++;
		}
		else
		{
			b[i] = 0;
			ano[a[i]]++;
			no++;
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		if(ayes[i] + (no - ano[i]) == m)
		{
			d[i] = 1;
			flag++;
		}
		else
		{
			d[i] = 0;
		}
	}
	for(int i = 1 ; i <= n ; i++)
	{
		if(b[i])
		{
			if(flag < 2 && d[a[i]])
			{
				cout << "Truth\n";
			}
			else if(!d[a[i]])
			{
				cout << "Lie\n";
			}
			else
			{
				cout << "Not defined\n";
			}
		}
		else
		{
			if(!d[a[i]])
			{
				cout << "Truth\n";
			}
			else if(flag < 2)
			{
				cout << "Lie\n";
			}
			else
			{
				cout << "Not defined\n";
			}
		}
	}
	return 8;
}
```
### 感谢观看!

---

## 作者：rui_er (赞：4)

$n$ 个人中有 $1$ 个罪犯，每个人说一句话，说第 $i$ 个人是/不是罪犯，其中有 $m$ 句真话，要判断这些话的真假。

思路：

首先假设所有人都不是罪犯，统计出真话条数，然后枚举每一个人，在这个真话条数的基础上加上这个人是罪犯时对答案的贡献，如果刚好有 $m$ 句真话，标记有嫌疑，最后判断即可。

但是这个贡献怎么求呢？

很简单，如果所有人都不是罪犯，则真话条数就是 $a_i\lt 0$ 的数量；当 $x$ 是罪犯时，减去 $a_i=-x$ 的数量，加上 $a_i=x$ 的数量，即为最新的贡献，这里在读入时也处理出来。

最后话的真假的判断方式也很简单：

如果 $i$ 指控一个人是罪犯：经过如上处理，发现他不可能是罪犯，则为假话；如果他可能是罪犯且嫌疑人数为 $1$，则为真话；否则不确定。说一个人不是罪犯的情况类似，不展开细说，可以参考代码。

---

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 int T; for(scanf("%d", &T);T;T--)
#define mulT1 int T, rnds; for(scanf("%d", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const int N = 1e5+5;

int n, m, a[N], contribution[N], suspect[N], tot, s;

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) {
		scanf("%d", &a[i]);
		if(a[i] > 0) ++contribution[a[i]];
		else --contribution[-a[i]], ++s;
	}
	rep(i, 1, n) if(s + contribution[i] == m) suspect[i] = 1, ++tot;
	rep(i, 1, n) {
		if(a[i] > 0) {
			if(!suspect[a[i]]) puts("Lie");
			else if(tot == 1) puts("Truth");
			else puts("Not defined");
		}
		else {
			if(!suspect[-a[i]]) puts("Truth");
			else if(tot == 1) puts("Lie");
			else puts("Not defined");
		}
	}
	return 0;
}
```

---

## 作者：OIerZhang (赞：1)

# [CF156B Suspects](https://www.luogu.com.cn/problem/CF156B)

## 思路

### $O(n^2)$ 做法

既然只有一个罪犯，我们可以枚举这个罪犯，看看有几句真话。例如样例三中的罪犯（横轴）与真假话（纵轴）列表如下。

||1|2|3|4|
|:-:|:-:|:-:|:-:|:-:|
|**1**|$\textrm F$|$\textbf{\color{#52C41A}{T}}$|$\textrm F$|$\textrm F$|
|**2**|$\textbf{\color{#52C41A}{T}}$|$\textbf{\color{#52C41A}{T}}$|$\textrm F$|$\textbf{\color{#52C41A}{T}}$|
|**3**|$\textrm F$|$\textrm F$|$\textrm F$|$\textbf{\color{#52C41A}{T}}$|
|**4**|$\textrm F$|$\textbf{\color{#52C41A}{T}}$|$\textbf{\color{#52C41A}{T}}$|$\textbf{\color{#52C41A}{T}}$|

这里只有第一列和第三列符合样例意思，这两列上，第一人和第三人始终说谎，其余不确定。

我们就可以暴力求出这个表，答案就出来了。但是这道题 $n \le 10^5$，不能通过。

### $O(n)$ 正解

上一种做法不通过的原因就是每次都要算一下所有人说的真假话，为了使计算真假话的时间复杂度降为 $O(1)$，我们不妨思考真话数量的构成。

假设没有罪犯，那么真话数量就是为他人辩护的人的数量。若第 $x$ 个人是罪犯，那么原来为他辩护的人说的是假话，指责他的人说的是真话，即 $S_\text{真} = \displaystyle \sum_{i = 1}^{n} S_{\text{辩护 } i} - S_{\text{辩护 } x} + S_{\text{指责 } x}$。上述公式可以用桶进行预处理，这样计算真假话的时间复杂度就降为了 $O(1)$，如果真话数量符合样例，就可能是罪犯。

输出时，如果一个人指责他人，那么就有以下几种情况：
1. 当被指责的那个人为唯一嫌疑犯，输出 `Truth`。
2. 当被指责的人不是嫌疑犯，输出 `Lie`。
3. 其余情况输出 `Not defined`。

一个人辩护他人时的情况同理。

## 核心代码

解释的很清楚了，不必加注释了吧。

```cpp
for (int i = 1; i <= n; i++)
{
    cin >> a[i];
    if (a[i] > 0)
        cnt[a[i]]++;
    else
        cnt[-a[i]]--, real++;
}
for (int i = 1; i <= n; i++)
{
    cnt[i] += real;
    if (cnt[i] == m)
        flag[i] = true, sp++;
}
for (int i = 1; i <= n; i++)
{
    if (a[i] > 0)
    {
        if (flag[a[i]] && sp == 1)
          cout << "Truth\n";
        else if (!flag[a[i]])
          cout << "Lie\n";
        else
          cout << "Not defined\n";
    }
    else
    {
        if (!flag[-a[i]])
            cout << "Truth\n";
        else if (flag[-a[i]] && sp == 1)
            cout << "Lie\n";
        else
            cout << "Not defined\n";
    }
}
```

珍爱账号，远离抄袭。

---

## 作者：Yuanchenpu (赞：1)

先假设所有人都是无罪的，然后再逐个判断每个人有没有可能有罪，并统计个数。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const int MAXN = 1e5 + 10;

int accusation[MAXN], antiaccusation[MAXN], n, m, sumtruth, chaim[MAXN];
bool guilty[MAXN];
int sumcrime;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", chaim + i);
		if (chaim[i] > 0) accusation[chaim[i]]++; //因为假设所有人都无罪，所以这个指控不是真话
		else antiaccusation[-chaim[i]]++, sumtruth++; //真话数量加一
	}
	for (int i = 1; i <= n; i++) {
		if (sumtruth + accusation[i] - antiaccusation[i] == m) {
			guilty[i] = true; //第i个人可能有罪
			sumcrime++; //可能罪犯总数加一
		}
	}
	for (int i = 1; i <= n; i++) {
		if (chaim[i] > 0) {
			if (!guilty[chaim[i]]) { puts("Lie");   continue; }//这个人不可能有罪，输出Lie
			else if (sumcrime < 2) { puts("Truth"); continue; }//这个人可能有罪，且可能罪犯总数为1，说明罪犯就是他，输出Truth
		} else {
			if (!guilty[-chaim[i]]) { puts("Truth"); continue; }//这个人不可能有罪，输出Truth
			else if (sumcrime < 2)  { puts("Lie");   continue; }//这个人可能有罪，且可能罪犯总数为1，说明罪犯就是他，输出Lie
		}
		puts("Not defined");
	}
	return 0;
}

```

---

## 作者：Yulin_Wu (赞：0)

本人的第一篇绿题题解，求过。


---

[题目传送门（CF156B）](https://www.luogu.com.cn/problem/CF156B)


---
# 具体思路
## 准备工作
首先开一个数组 $x$，纪录有多少人说第 $i$ 是罪犯。

再开一个数组 $y$，纪录有多少人说第 $i$ 不是是罪犯。

## 开始操作
首先假设没有人是罪犯，那么此时说真话的人数就是所有符合 
``
a[i] < 0
``
 的个数。

然后再循环假设第 $i$ 个人是罪犯，那么此时说真话的为 ``sum - y[i] + x[i]``。
判断此时的 `` sum  == m `` 是否成立。如果成立，则让 $i$ 加入罪犯列表。

## 输出部分

首先如果那人说第 $i$ 个人是罪犯，那就判断第 $i$ 个人在不在罪犯列表中，如果不在，那就是假话；如果在，并且罪犯列表的长度为 $1$ 那么就是真话，否则就不一定。

同理，如果那人说第 $i$ 个人不是罪犯，那就判断第 $i$ 个人在不在罪犯列表中，如果不在，那就是真话；如果在并且罪犯列表的长度为 $1$ 那么就是假话，否则就不一定。
 
# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxx = 1e5+5;
long long n,m,a[maxx],x[maxx], y[maxx],people=0,cnt=0;
bool suspect[maxx];  //记录每人可不可能为罪犯 
int main() 
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i] > 0) x[a[i]]++;
		else 
		{
			y[a[i]]++;
			cnt++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(cnt + x[i] -y[i] == m) //判断此时说真话的人的数量 
		{
			suspect[i] = 1;
			people+=1;
		}
	}
	for(int i=1;i<=n;i++) //输出这个人说的是真话还是假话 
	{
		if(a[i] > 0) 
		{
			if(suspect[a[i]] == 0) cout<<"Lie"<endl;
			if(suspect[a[i]] == 1 && people == 1) cout<<"Truth"<<endl;
			else cout<<"Not defined"<<endl;
		}
		else 
		{
			if(suspect[a[i]] == 0) cout<<"Truth"<<endl;
			if(suspect[a[i]] == 1 && people==1)
			else cout<<"Not defined"<<endl; 
		}
	}
	return 0;
}
```


完结撒花！！！

---

