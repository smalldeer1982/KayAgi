# Frog Jumps

## 题目描述

There is a frog staying to the left of the string $ s = s_1 s_2 \ldots s_n $ consisting of $ n $ characters (to be more precise, the frog initially stays at the cell $ 0 $ ). Each character of $ s $ is either 'L' or 'R'. It means that if the frog is staying at the $ i $ -th cell and the $ i $ -th character is 'L', the frog can jump only to the left. If the frog is staying at the $ i $ -th cell and the $ i $ -th character is 'R', the frog can jump only to the right. The frog can jump only to the right from the cell $ 0 $ .

Note that the frog can jump into the same cell twice and can perform as many jumps as it needs.

The frog wants to reach the $ n+1 $ -th cell. The frog chooses some positive integer value $ d $ before the first jump (and cannot change it later) and jumps by no more than $ d $ cells at once. I.e. if the $ i $ -th character is 'L' then the frog can jump to any cell in a range $ [max(0, i - d); i - 1] $ , and if the $ i $ -th character is 'R' then the frog can jump to any cell in a range $ [i + 1; min(n + 1; i + d)] $ .

The frog doesn't want to jump far, so your task is to find the minimum possible value of $ d $ such that the frog can reach the cell $ n+1 $ from the cell $ 0 $ if it can jump by no more than $ d $ cells at once. It is guaranteed that it is always possible to reach $ n+1 $ from $ 0 $ .

You have to answer $ t $ independent test cases.

## 说明/提示

The picture describing the first test case of the example and one of the possible answers:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1324C/662a540925813072330b737ce66b1eb08560ce29.png)

In the second test case of the example, the frog can only jump directly from $ 0 $ to $ n+1 $ .

In the third test case of the example, the frog can choose $ d=3 $ , jump to the cell $ 3 $ from the cell $ 0 $ and then to the cell $ 4 $ from the cell $ 3 $ .

In the fourth test case of the example, the frog can choose $ d=1 $ and jump $ 5 $ times to the right.

In the fifth test case of the example, the frog can only jump directly from $ 0 $ to $ n+1 $ .

In the sixth test case of the example, the frog can choose $ d=1 $ and jump $ 2 $ times to the right.

## 样例 #1

### 输入

```
6
LRLRRLL
L
LLR
RRRR
LLLLLL
R```

### 输出

```
3
2
3
1
7
1```

# 题解

## 作者：zct_sky (赞：3)

### Solution:
-----
简单贪心。

青蛙要从 $0$ 到 $n+1$，方向是往右的（$R$），那么 $L$ 就可以忽略。只需找出相邻两个 $R$ 和第一个 $R$ 与起点（$0$）之间的距离以及最后一个 $R$ 与终点（$n+1$）之间的距离，再求出这些距离中的最大值即可。如果没有 $R$，则直接输出 $n+1$。
### Code:
-----
```c++
#include<bits/stdc++.h>
using namespace std;
int t,l,ans;
string a; 
int main(){
	cin>>t;
	for(int tt=0;tt<t;tt++){
		cin>>a;
		l=a.length(),ans=-1;
		int k=0,last=-1;
		for(int i=0;i<l;i++)
		    if(a[i]=='R'){
		    	k++;
		    	ans=max(ans,i-last);
		    	last=i;
			}
		if(last!=-1) ans=max(ans,l-last);
		if(k==0) cout<<l+1<<"\n";
		else cout<<ans<<"\n";
	}
    return 0;
}
```

---

## 作者：do_while_true (赞：2)

### 题目翻译

现在有$n+2$个格子，青蛙在 0号格子上，第1到第n个格子都有一个字符$s_i$，青蛙可以在跳之前选择一个d (不能改变)，然后从0号格子向右跳最多d个，当他在1到n号格子时，如果$s_i$为 'L'，则可以向左最多跳d个，如果$s_i$为'R'，则可以向右跳最多d个。

请你确定一个最小的d，使得青蛙能够从0号格子跳到$n+1$号格子

#### 输入格式

第一行一个整数T，表示T组数据

接下来T行，一个字符串s

#### 输出格式

T行 表示每组数据最大的d

### 题目分析

考虑贪心。

首先我们可以把0号格子看做一个'R'，因为它只能往右跳。

想要使d尽量小，我们每次跳跃就要尽量小，那么如果我们想要跳到一个'R'，从它往左边最近的那个'R'跳过来肯定是最优的。对于终点，从终点往左边最近，也就是最靠右的'R'跳过来肯定是最优的。

所以我们只需要记录每个'R'之间距离最长的即可。

### Code:

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
int n,T,last,ans;
char ch[200001];
int main()
{
	scanf("%d",&T);
	while(T--){
		scanf("%s",ch+1);//从下标1开始读 
		last=0;
		//last代表的是上一个'R'出现的位置，这里我们把0号格子也看做'R' 
		ans=0;//答案 
		ch[0]='R';
		n=strlen(ch);//n就是字符串的长度
		for(int i=1;i<=n;i++)
		{
			if(ch[i]=='R')//如果遇到'R'，就要重新判断是否要更新答案 
			{
				ans=max(ans,i-last);//即答案为最大的 两个 'R'的距离 ” 
				last=i;
			}
		}
		ans=max(ans,n-last);//从最后一个'R'跳到n+1号格子 
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：oimaster (赞：2)

这一道题可以说把我的思维弄得乱七八糟，想出来正解后感觉自己实在是太蠢了。

这道题的思路是贪心。我们发现，往左边跳其实并不划算，我们往左边跳的时候，距离就会更远，我们想跳的只是朝向右边的石头，可以离终点的距离更近。这时候，你会发现这道题就很简单了，直接求出所有向右边的石头的坐标差，取其中最大值即可。

如果你想查看我的代码，请到 [这里](https://oi-master.github.io/post/codeforces-contest-1324-c-ti-jie/#%E4%BB%A3%E7%A0%81) 查看。

---

## 作者：do_while_false (赞：2)

【题目翻译】

有 $n+2$ 个格子，青蛙站在 $s_0$，它最终想要跳到 $s_{n+1}$。
青蛙在开始跳之前可以选定一个 $d$。对于任意一个 $s_i$，如果 $s_i=$ ' L ' ,就可以向左跳 $1 \sim d$ 个格子。如果 $s_i=$ ' R ' ,就可以向右跳 $1 \sim d$ 个格子。选定一个最小的 $d$ ，使青蛙能跳到 $s_{n+1}$ 。注意，$s_0$ 必定为 ' R '。

【大概思路】

用一个数组 $f$ 来记录 $s_i$之前有多少个连续的 ' L '，根据题意，答案 $d$ 即为 $f$ 数组中的最大值。

【具体做法】

如果 $s_{i-1}=$ ' L ' ，$f_i\Leftarrow f_{i-1}$ 。否则 $f_i\Leftarrow 0$。

【代码实现】

```cpp
#include<bits/stdc++.h>
#define MAXN 200000 + 10
using namespace std;
int t,top=1,f[MAXN],Max;
char s[MAXN],c;
inline int read() {//快读 
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
int main(void) {
	t=read();
	while(t--) {
		memset(f,0,sizeof(f));
		Max=-MAXN;//初始化 
		c=getchar();top=1;
		while(c=='L'||c=='R') {
			s[top++]=c;
			c=getchar();
		}//读入字符串 
		s[0]='R';
		for(int i=1;i<=top;i++) 
			if(s[i-1]=='L') 
				f[i]=f[i-1]+1;//求 f_i 
		for(int i=1;i<=top;i++) Max=max(Max,f[i]);//找出最大的 f_i 
		printf("%d\n",Max+1);//输出 
	}
	return 0;
}

```

---

## 作者：devout (赞：1)

[博客内食用更佳](https://blog.csdn.net/devout_/article/details/104858457)

考虑贪心，我们发现，往左跳是没有用的，所以我们只用关注R的情况就可以了

所以答案就是任意两个R之间的距离的最大值，注意0和n+1都是R

```cpp
#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=2e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
};

int t,n;
char s[N];
int ans=0;

int main()
{
    read(t);
    while(t--){
        scanf("%s",s+1);
        n=strlen(s+1);
        s[0]='R',s[n+1]='R';
        int lastr=0;ans=0;
        Rep(i,1,n+1)if(s[i]=='R')ans=max(ans,i-lastr),lastr=i;
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：zbk233 (赞：0)

## 解题思路

看到这道题，我的第一想法是二分，但是，对于数据范围，二分显然无法通过，所以，此题显然是一道贪心题。

首先，青蛙要是跳到了 ```L``` 的格子上，就一定要走回头路，而走回头路就一定到达不了终点。

所以，我们选择跳过 ```L``` 的格子，只走 ```R``` 的格子。

那么，这道题就只需要找出最长的 ```L``` 的区间的长度 $len$，最后输出 $len+1$ 即可。

## 参考代码

```cpp
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string str;
	int n,len,sum,ans;
	cin>>n;
	while(n--){
		cin>>str;
		len=str.size();
		sum=ans=0;
		for(int i=0;i<len;i++){
			if(str[i]=='L'){
				sum++;
			}
			else{
				sum=0;
			}
			ans=max(sum+1,ans);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF1324C) & [CodeForces题目页面传送门](https://codeforces.com/contest/1324/problem/C)

>有$n+2$个格子，编号$0\sim n+1$。$\forall i\in[1,n]$，格子$i$上有一个字母$a_i\in\{\texttt L,\texttt R\}$，分别表示在格子$i$上只能往左、右跳。青蛙一开始站在格子$0$，$a_0=\texttt R$。求一个最小的$d$，表示青蛙一次能跳$1\sim d$格且不能出格，使得青蛙能到达格子$n+1$。保证总有符合要求的$d$。本题多测。

首先，不难发现对于任意一个$d$，能到达的格子组成前缀。证明：反证法。若不组成前缀，即存在$i\in[1,n]$使得$i$不能到达且$i+1$能到达。此时必存在一个$x\in[0,i)$使得$a_x=\texttt R$且$x$能到达$[i+1,n+1]$中任意一个格子$y$。根据青蛙跳的规则，$[x+1,y]$内任意一个格子都能从$x$到达，又$x<i,y>i\Rightarrow i\in[x+1,y]$，与$i$不能到达矛盾。得证。

接下来，又~~双叒叕~~不难发现往左跳的格子不起丝毫作用，即任意一个能到达的格子都可以只往右跳来到达。证明：数学归纳法。设对于某一个$d$，能到达的格子组成的前缀为$[0,r](r\geq0)$。
1. 格子$0$显然满足可以只往右跳来到达；
2. $\forall x\in[1,r]$，假设$\forall i\in[0,x)$，格子$i$都满足可以只往右跳来到达。对于$x$的某一种到达方式，设最后一步是由$y$跳过来的，分$2$种情况：
   1. $y<x$。此时最后一步一定是往右跳。再加上$\forall i\in[0,x)$，格子$i$都满足可以只往右跳来到达，可以得出格子$x$满足可以只往右跳来到达；
   2. $y>x$。此时在$y$的到达方式中，必有一步是从$z\in[1,x)$跳到$xx\in[x,n+1]$。根据青蛙跳的规则，$[z+1,xx]$内任意一个格子都能从$z$到达，又$x>z,x\leq xx\Rightarrow x\in[z+1,xx]$，所以$x$能被$z$往右跳到达。再加上$z\in[1,x)\subsetneq[0,x)$且$\forall i\in[0,x)$，格子$i$都满足可以只往右跳来到达，可以得出格子$x$满足可以只往右跳来到达。

   综上，若$\forall i\in[0,x)$，格子$i$都满足可以只往右跳来到达，那么格子$x$满足可以只往右跳来到达。

综上，得证。

于是我们可以把所有$a_i=\texttt R$的$i$有序地抽出来组成序列$pos$，特殊地，$pos_{|pos|}=n+1$。显然，$\forall i\in[1,|pos|),pos_i\to pos_{i+1}$，这种跳法最省$d$。要满足每次跳，起点和终点的距离都在$d$以内，所以答案是$d=\max\limits_{i=1}^{|pos|-1}\{pos_{i+1}-pos_i\}$。

下面是AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=200000;
int n;
char a[N+5];
void mian(){
	cin>>a+1;
	n=strlen(a+1);
	vector<int> pos;
	pos.pb(0);
	for(int i=1;i<=n;i++)if(a[i]=='R')pos.pb(i);
	pos.pb(n+1);
	int ans=0;
	for(int i=0;i+1<pos.size();i++)ans=max(ans,pos[i+1]-pos[i]);//取最大距离 
	cout<<ans<<"\n";
}
int main(){
	int testnum;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

## 作者：菜鸡gyf (赞：0)

## 题目大意
   一只青蛙要从0跳到n+1格，第一次往右跳，它每次最多可以跳d格，如果脚下是“L”，则可以跳到[max(0,i−d);i−1],如果是“R”则可以跳到 [i+1;min(n+1;i+d)]，求最小的d。

## 题目分析
   这是Div.3的c题，挺水的。吐槽一句：样例解释什么鬼啊，真是完美误导。如果我们落在一个“L”上就要往左跳，往左跳肯定是到不了终点的，怎么办呢？就要再跳到“R”上。结果绕了一圈又回来了，我们发现：
## 落在“L”上没有任何意义!
   知道了这一点后我们只需要让青蛙每一步落在右侧里最近的“R”就可以保证ｄ最小，因为两个“R”中不管怎么跳都会跳出两格的距离一步。所以我们只需要设maxn这一个变量来不断更新青蛙跳的最大距离就可以了。

所以，我们可以得出代码：
```
#include<cstdio>
#include<iostream>
using namespace std;
int main()
{
	int t,i,j;
	scanf("%d",&t);
	for(i=1;i<=t;++i)
	{
		int len,maxn=0,v=-1;//v是用来记录前面一个"R"的 ,因为s第一个字符的下标为0，所以v设成-1 
		string s;
		cin>>s;//读入字符串s 
		len=s.length();
		s[len]='R';//设终点为"R" 
		for(j=0;j<=len;++j)
		{
			if(s[j]=='R')
			{
				if(maxn<j-v)
				maxn=j-v;
				v=j;
			}
		}
		printf("%d\n",maxn);
	}
	return 0;
}
```


---

## 作者：LB_tq (赞：0)

# Solution

贪心做法。

可以证明青蛙一直向右跳必然是最优的。

如果青蛙在 $s_i (s_i=L)$ 处向左跳到某个 $s_j(j<i,s_j=R)$ 处，则青蛙肯定也可以不跳到 $s_i$ 直接跳到 $s_j$。所以向左跳是没有意义的。

所以可以遍历整个序列，维护更新两个$R$之间距离的最大值即为所求。

由于青蛙要跳到 $n+1$ 的位置，所以最后特判一下答案是否加 $1$ 。

时间复杂度 $O(n)$ 。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=2e5+10;
int n,t,ans,sum;
string s;
int main(){
	cin>>t;
	while(t--){
		ans=sum=0;
		cin>>s;
		n=s.size();
		for(int i=0;i<n;i++){
			sum++;
			ans=max(ans,sum);
			if(s[i]=='R')
				sum=0;
		}
		if(sum==ans)
			ans++;
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Elma_ (赞：0)

### 不要停下来啊！
这里不要停下来指的是**贪心**，**永远不要走回头路**。

感觉此题最大的坑点其实是题目给出的这个图例。往回跳的那一下好像吓死了不少人。（~~包括我~~

我们就来讨论一下到底有没有走回头路的必要。

如题目的这个样例：$LRLRRLL$

题目给出的图例说明是先跳到第二个$L$上，然后再往回跳到第一个$R$的位置。我们可以发现其实可以直接就跳到第一个$R$上。如果你想走回头路，即先跳到一个$L$上，再往回跳到一个$R$上，都是浪费的。因为此时的那个$L$一定在那个$R$的右边，如果$d$足够让你跳到$L$上，那么也一定能够直接跳到$R$上，所以其实没有回头的必要。

于是所有的$L$往左跳的作用就失效了，唯一的用处就只剩当障碍而已。我们只需要使$d$能够跳过最长的障碍就可以了，即求出这个序列中最长的连续$L$的长度，答案就是这个长度$+1$。

### CODE
```
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int t;
string jump;

void work()
{
	cin>>t;
	
	while(t--)
	{
		cin>>jump;
		int tmp = 0;//tmp记录每个连续L的长度
		int ans = 0;//ans记录最长的连续L长度
		
		for(int i=0;i<jump.size();i++)
		{
			if(jump[i] == 'L')//遇到L时当前连续L的长度+1
				tmp++;
			
			if(jump[i] == 'R' || i == jump.size()-1） //遇到R或最后一个字符，即当前连续L结束
			{
				ans = max(tmp, ans);
				tmp = 0;//更新ans和tmp的值
			}
		}
		
		cout<<ans+1<<endl;//输出最长连续L的值+1
	}
}

int main(void)
{
	work();
	return 0;
}
```


---

## 作者：registerGen (赞：0)

考场上乱 yy 的做法，交一发就过？

---

考虑贪心，先令 $s_0:=\texttt{R},s_{n+1}:=\texttt{R}$，再取两个 $\texttt{R}$ 距离的最大值即为答案。（如果答案比它小，那么青蛙就一定会跳到 $\texttt{L}$ 然后再跳到 $\texttt{L}$ 然后跳到原来的位置就 GG 了）

---

下面放出代码，时间复杂度 $O(n)$。

```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<iostream>

const int N=2e5;

char s[N+10];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(s,0,sizeof(s));
		
		scanf("%s",s+1);
		int n=strlen(s+1)+1;
		s[0]='R',s[n]='R';
		int tmp=1,x; // tmp 为上一个 R 的位置
		int ans=0;
		for(int i=0;i<=n;i++)
		{
			if(s[i]=='R')
			{
				x=i;
				ans=std::max(ans,x-tmp);
				tmp=x;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：jxbe6666 (赞：0)


**题目思路：**
一道简单的贪心。

青蛙要从 $0$ 到 $n+1$，方向是往右的 R，那么 L 就可以忽略。只需找出相邻两个 R 和第一个 R 与起点 0 之间的距离以及最后一个 R 与终点 $n+1$ 之间的距离，再求出这些距离中的最大值即可。如果没有 R，则直接输出 $n+1$。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,l,ans;
string a; 
int main(){
    cin>>t;
    for(int tt=0;tt<t;tt++){
        cin>>a;
        l=a.length(),ans=-1;
        int k=0,last=-1;
        for(int i=0;i<l;i++)
            if(a[i]=='R'){
                k++;
                ans=max(ans,i-last);//取最大值
                last=i;
            }
        if(last!=-1) ans=max(ans,l-last);
        if(k==0) cout<<l+1<<"\n";
        else cout<<ans<<"\n";
    }
    return 0;
}
```


---

