# Yet Another Bookshelf

## 题目描述

There is a bookshelf which can fit $ n $ books. The $ i $ -th position of bookshelf is $ a_i = 1 $ if there is a book on this position and $ a_i = 0 $ otherwise. It is guaranteed that there is at least one book on the bookshelf.

In one move, you can choose some contiguous segment $ [l; r] $ consisting of books (i.e. for each $ i $ from $ l $ to $ r $ the condition $ a_i = 1 $ holds) and:

- Shift it to the right by $ 1 $ : move the book at index $ i $ to $ i + 1 $ for all $ l \le i \le r $ . This move can be done only if $ r+1 \le n $ and there is no book at the position $ r+1 $ .
- Shift it to the left by $ 1 $ : move the book at index $ i $ to $ i-1 $ for all $ l \le i \le r $ . This move can be done only if $ l-1 \ge 1 $ and there is no book at the position $ l-1 $ .

Your task is to find the minimum number of moves required to collect all the books on the shelf as a contiguous (consecutive) segment (i.e. the segment without any gaps).

For example, for $ a = [0, 0, 1, 0, 1] $ there is a gap between books ( $ a_4 = 0 $ when $ a_3 = 1 $ and $ a_5 = 1 $ ), for $ a = [1, 1, 0] $ there are no gaps between books and for $ a = [0, 0,0] $ there are also no gaps between books.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, you can shift the segment $ [3; 3] $ to the right and the segment $ [4; 5] $ to the right. After all moves, the books form the contiguous segment $ [5; 7] $ . So the answer is $ 2 $ .

In the second test case of the example, you have nothing to do, all the books on the bookshelf form the contiguous segment already.

In the third test case of the example, you can shift the segment $ [5; 5] $ to the left and then the segment $ [4; 4] $ to the left again. After all moves, the books form the contiguous segment $ [1; 3] $ . So the answer is $ 2 $ .

In the fourth test case of the example, you can shift the segment $ [1; 1] $ to the right, the segment $ [2; 2] $ to the right, the segment $ [6; 6] $ to the left and then the segment $ [5; 5] $ to the left. After all moves, the books form the contiguous segment $ [3; 4] $ . So the answer is $ 4 $ .

In the fifth test case of the example, you can shift the segment $ [1; 2] $ to the right. After all moves, the books form the contiguous segment $ [2; 5] $ . So the answer is $ 1 $ .

## 样例 #1

### 输入

```
5
7
0 0 1 0 1 0 1
3
1 0 0
5
1 1 0 0 1
6
1 0 0 0 0 1
5
1 1 0 1 1```

### 输出

```
2
0
2
4
1```

# 题解

## 作者：Eason_AC (赞：5)

## Content
在一个仅有 $0,1$ 这两个数的数列上，每次可以选择一段全为1的连续区间将其左移 $1$ 或者右移 $1$。现给出 $t$ 次询问，每次询问给出一个长度为 $n$ 的满足上述条件的数列，求出使所有为 $1$ 的位置在唯一一个连续区间的最小操作次数。

**数据范围：$1\leqslant t\leqslant 200,1\leqslant n\leqslant 50$。**
## Solution
每次我们选择全为 $1$ 的区间向右移，其实就是为了把目标区间中的 $0$ 给它补齐，所以，我们不难看出，这题目就是让我们求每两个 $1$ 之间的 $0$ 的数量的总和。直接扫一遍统计一下即可。
## Code
```cpp
int t, n, a[57];

int main() {
	//This program is written in Windows 10 by Eason_AC
	getint(t);
	while(t--) {
		int ans = 0, tmp = 0, flag = 0;
		getint(n);
		_for(i, 1, n) {
			getint(a[i]);
			if(a[i] == 0 && flag) {
				tmp++;
				if(i == n)	tmp = 0;
			} else if(a[i] == 1) ans += tmp, tmp = 0, flag = 1;
		}
		writeint(ans), puts("");
	}
	return 0;
}
```

---

## 作者：黄文烽 (赞：3)

## 这是萌新的第一篇题解，写的不好，大佬勿喷

### 做法的推理过程：

首先，我们可以想到一个很简单的思路：

因为每一次移动的时候只会移动书，所以说我们可以每一次将$[l, r]$（$l$为最左的书，$r$为最右的书，**这里的书都是指没有放在一起的**）往右移一格，这样是最优的做法。

那么，我们便可以得到这种方法的伪代码了：
```cpp
while(还有书右边有0){
    [l, r]右移一格;
    ans++;
}

cout << ans << endl;
```

然后，我们可以发现，每一次移动都会抹掉$[l, r]$内最右边的空位（被书填掉了），直到$[l, r]$内没有空位才结束。那么，我们可以通过数$[l, r]$内的空位来直接求出要移动多少次。

然后我们可以得到这种方法的关键代码：
```cpp
for(int i = l; i < r; i++){ //r的位置一定不是0
   if(a[i] == 0) ans++;
}

cout << ans << endl;
```

然而，作为一个蒟蒻的oier，卡常是必须掌握的技能，那么这道题如何卡常呢？

我们可以想到：

求$l$和$r$的时候，因为$l$一定$<= r$，所以说我们可以从左往右获得$l$，从右往左获得$r$，这样的执行次数一定$<=$直接扫描的次数，and then......

### 最终Code:
```cpp
//码风奇怪，请勿见怪
#include<iostream>

using namespace std;

int t, n;
int a[55];

int main(){
	ios::sync_with_stdio(false); //优化iostream的输入输出速度，但只能够在iostream和cstdio不同时用的时候使用
	
	cin >> t;
	
	while(t--){
		int b[55], ans = 0;
		
		cin >> n;
		
		for(int i = 0; i < n; i++) cin >> a[i];
		
		int l = 0, r = 0;
		
		for(int i = 0; i < n; i++){ //从左到右扫描，如果是书就存下来
			if(a[i]){
				l = i;
				break;
			}
		}
		
		for(int i = n - 1; i >= 0; i--){ //从右到左扫描，如果是书也存下来
			if(a[i]){
				r = i;
				break;
			}
		}
		
		for(int i = l; i < r; i++){ //数0
			if(!a[i]) ans++;
		}
		
		cout << ans << endl;
	}
	
	return 0;
}//虽然说没有加防抄袭标记，但是还是要认真看，做题不是为了AC，而是为了训练自己
```

---

## 作者：是个汉子 (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1443B)		[CF传送门](http://codeforces.com/problemset/problem/1443/B)

### Solution

这个题就是一个简单的贪心。

将连续的零的贡献一起算，比如： $11000011$ ，中间是 $4$ 个零，那么贡献是 $4\times b$ ，如果 $4\times b<a$ ，那就连上，不然就直接炸上一段。

~~如果还不懂可以看代码~~

### Code

```c++
#include<bits/stdc++.h>

using namespace std;
int t,a,b,s[100010];
char ch[100010];

int main(){
    scanf("%d",&t);
    while(t--){
        int ans=0;
        scanf("%d%d",&a,&b);
        scanf("%s",ch+1);
        int len=strlen(ch+1),cnt=0,flag=0;
        for(int i=1;i<=len;i++) s[i]=ch[i]-'0';
        for(int i=1;i<=len;i++){
            if(s[i]!=s[i-1]){
                if(s[i]==0) cnt=1;
                else{
                    if(flag) ans+=min(a,b*cnt);
                    flag=1;
                }
            }
            else if(s[i]==0) cnt++;
            //cout<<cnt<<endl;
        }
        if(cnt==len) puts("0");
        else printf("%d\n",ans+a);
    }
    return 0;
}
```



---

## 作者：听取wa声一片。 (赞：2)

## 萌新第二篇题解

### 1.题意核心


------------


在**首尾都为1**的子序列中**数0**。


------------


### 2.算法思路

**卡常**

蒟蒻的思路：设l，r。

>从序列中从左往右找1，第一个1的下标设为l（左）；
>
>从序列中从右往左找1，第一个1的下标设为r（右）；
>
>然后从l开始，从r结束，数到0就ans++。

就是这么~~暴力~~简单。


------------


### 3.题解代码

话不多说，上代码。

```cpp

//蒟蒻的代码

#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
	cin>>n;
	for(int i=1;i<=n;i++){
	    int a[55],b,ans=0,l=0,r=0;
		cin>>b;//输入
		for(int j=1;j<=b;j++) cin>>a[j];//输入
		for(int j=1;j<=b;j++) if(a[j]==1){l=j;break;}//确定l
		for(int j=b;j>=1;j--) if(a[j]==1){r=j;break;}//确定r
		for(int j=l+1;j<=r-1;j++) if(a[j]==0) ans++;//数0
		cout<<ans<<"\n";//输出
    }
	return 0; 
}

```

---

## 作者：vectorwyx (赞：1)

每次移动最多使得两段连续的 $1$ 之间的 $0$ 的数量减少 $1$，贪心地将连续的 $1$ 从左向右聚拢一定是最优的，不难看出这样做的答案为最左面的 $1$ 和最右面的 $1$ 之间的 $0$ 的数量。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

int a[1005];

void work(){
	int n=read(),l,r,ans=0;
	fo(i,1,n) a[i]=read();
	fo(i,1,n) if(a[i]){
		l=i;
		break;
	}
	go(i,n,1) if(a[i]){
		r=i;
		break;
	}
	fo(i,l,r) if(!a[i]) ans++;
	printf("%d\n",ans);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1433B)

直观的思路。

由于每次只能移动 $1$ 位，那么要把所有的 $1$ 连在一起，就必须移动最左边的 $1$ 和最右边的 $1$ 中间的 $0$ 那么多次。

所以只要统计最左边的 $1$ 和最右边的 $1$ 中间的 $0$ 的数量就行了。注意特判一下只有一个 $1$ 的情况。

时间复杂度 $O(tn)$。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
	int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
int flag,tagl,tagr;
int t,n,sum,sum1,a[200005],b[200005];
int main()
{
	cin>>t;
	while(t--)
	{
		flag=0,sum=0,tagl=0,tagr=0; 
		cin>>n;
		for(ri i=1;i<=n;i++)
		{
			a[i]=read();
			if(a[i]==1)
			{
				if(!flag)
				{
					flag=1;
					tagl=i;
				}
				else
					tagr=i;
			} 
		}
		if(tagr==0)
		{
			cout<<0<<endl;
			continue;
		}
		for(ri i=tagl;i<=tagr;i++)
			if(a[i]==0)
				sum++;
		cout<<sum<<endl;	
	}
    back 0;
}
```

---

## 作者：Suzt_ilymtics (赞：0)

## Description

$T$ 组数据，每组数据给定一段 $01$ 序列，每次可以将一段连续的 $1$ 左移或右移一位，求将所有 $1$ 合并到一起的操作次数

## Solution

题目说我们可以将一段连续的 $1$ 移动 $1$ 位，那我们从 $0$ 的角度看，就是将 $0$ 移到一段 $1$ 的外面

贪心的想，每次我们都能把一个 $0$ 移到序列的最外边，这样的移动次数最少

所以这个题就转化成序列最两端的两个 $1$ 之间有多少 $0$ 的问题

数据范围很小，直接暴力即可

## Code

```cpp
/*
Work by: Suzt_ilymics
Knowledge: ??
Time: O(??)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 55;
const int INF = 1;
const int mod = 1;

int T, n;
int a[MAXN];

int read(){
	int s = 0, f = 0;
	char ch = getchar();
	while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
	return f ? -s : s;
}

int main()
{
	T = read();
	while(T--){
		n = read();
		for(int i = 1; i <= n; ++i){
			a[i] = read();
		}
		int l = 0, r = 0, cnt = 0;
		for(int i = 1; i <= n; ++i) if(a[i]) { l = i; break; }
		for(int i = n; i >= 1; --i) if(a[i]) { r = i; break; }
		for(int i = l; i <= r; ++i){
			if(a[i] == 0) cnt++;
		}
		printf("%d\n", cnt);
	}
	return 0;
}
```

---

## 作者：Natsume_Rin (赞：0)

这一题可以枚举一个位置 $pos$，把所有的 $1$ 向他靠近，统计最小的答案。

时间复杂度 $O(tn^2)$。

```cpp
#include<bits/stdc++.h>
#define RI register int
using namespace std;
const int MAXN = 55;
int q;
int n;
int a[MAXN];
int suma, sumb;
int ans;
int cnt;
int main(){
	scanf("%d",&q);//询问次数
	while(q--){
		ans=2147484;
		scanf("%d",&n);
		for(RI i=1;i<=n;++i) scanf("%d",&a[i]);//01序列
		for(RI i=1;i<=n;++i){
			if(a[i]==1){
				suma=sumb=cnt=0;
				for(RI j=1;j<i;++j){
					if(a[j]==0&&cnt>=1) suma++;//统计左区间答案。
					cnt+=(a[j]==1);
				}
				cnt=0;
				for(RI j=n;j>i;j--){
					if(a[j]==0&&cnt>=1) sumb++;//统计右区间答案。
					cnt+=(a[j]==1);
				}
				ans=min(ans,suma+sumb);//统计最小的答案
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：aakennes (赞：0)

结论题

先说一个坑：

由于每次选择的是一段连续为 $1$ 的区间移动，所以不能转换为拼接字符串问题，即：

球交换相邻两个字符使相同的字符在一段连续的区间的最小交换次数

这类问题的性质是两个字符间的最小交换次数为两个字符见距离减去两个字符间的相同字符个数

但如果按照这个性质做这道题就会WA，原因是由于可以移动一整个区间，所以可以把两边的 $1$ 不断往中间靠，直到靠到一个 $1$ ，然后把整个区间视为一个整体，以此类推

什么意思呢？举个例子：

1 0 1 0 1 1 0 1 0 0 

1 2 3 4 5 6 7 8 9 10 

先把 $1$ 靠到 $3$ ，再把 $13$当做整体靠到 $56$，最后 $1356$ 整体靠到 $8$，最小答案为首位 $1$ 和尾位 $1$ 之间 $0$ 的个数

直接球出第一个 $1$ 和最后一个 $1$ 之间 $0$的个数就是答案，注意第一个 $1$ 指第一段连续区间中的最后一个 $1$，最后一个 $1$ 指最后一段连续区间中第一个 $1$

```
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int nowl=1,nowr=n,ans=0;
		while(!a[nowl])nowl++;
		while(!a[nowr])nowr--;
		for(int i=nowl;i<=nowr;i++)ans+=(a[i]==0);
		cout<<ans<<endl;

```

---

## 作者：luosw (赞：0)

### 题目描述
- 给定一个长度为 $n$ 的二进制串 $a$。
- 对于每一次操作，可以选定含有连续的 1 的块进行左移或右移。
- 求最少的操作次数使得所有的 1 相邻。

### 题目分析

我们可以将题目转化。转化为：

> 求最少的操作次数使得给定的第一个 1（下标为 $l$）和最后一个 1（下标为 $r$）中没有 0。

这样，**就可以把原来的移动块变成消去 0**。

因此，最少的结果应该为在 $a_l,a_r$ 中的 0 的个数。

时间复杂度：$\mathcal O(t\cdot n)$。

### 部分代码

```cpp
while (a[l] == 0)
	l++;
r = n - 1;
while (a[r] == 0)
	r--;
for (int i = l; i <= r; i++)
	if (a[i] == 0)
		ans++;
        
```

---

## 作者：WuhenGSL (赞：0)

根据题意，将所有 $1$ 移动为连续的最小操作次数为所有 $1$ 之间 $0$ 的个数

因为数据范围很小，只要分别枚举找到第一个 $1$ 和最后一个 $1$ 统计他们之间 $0$ 的个数即可

```cpp
//AC代码
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 55
using namespace std;
int T,a[N],n;
int main()
{
	scanf("%d",&T);
	while(T--){
		memset(a,0,sizeof a);
		scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		int first,last;
		for(int i=1;i<=n;++i)
			if(a[i]==1){
				first=i;break;
			}
		for(int i=n;i>=1;--i)
			if(a[i]==1){
				last=i;break;
			}
		for(int i=first;i<=last;++i){
			if(a[i]==0)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：—维尼— (赞：0)

~~这道题简单的不能再简单了~~
## 题目描述
给定一个书架，然后书架中有空隙（两本书中间0的部分），你现在需要把所有书汇聚在一起，就是保证任意相邻两本书之间没有空隙，每次移动可以把$l-r$的书全部一起移动，每次移动要保证目标地点是空位



## 方法介绍



简单贪心，我们找出最左边的书，和最右边的书确定边界，然后来找规律



如果只有一个空隙

00000001111111110111111110000000

很简单，只要随便将左区间或右区间移动一格就行了

000000000011111011111110111111111100000

两个空隙同理，移动两次即可汇成一个连续区间

更多的也可以举出例子……

于是我们找到规律

**$l-r$之间的空隙数就等于移动步数**

找到结论代码就很好写了



## 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int a[55];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,l=0,r=0,ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(l==0&&a[i]>0)
				l=i;
		}
		for(int i=n;i>=1;i--){
			if(r==0&&a[i]>0)
				r=i;
		}
		for(int i=l;i<=r;i++){
			if(a[i]==0)
			ans++;
		}
		cout<<ans<<endl;
	}
}
```



---

## 作者：Laoshancun233 (赞：0)

## 题目大意

OB君已经发题目翻译了

再写大意就没必要了吧

## 题目思路

看着这样例

移动区间不就是把中间的$0$都移掉吗

所以最少的移动次数就是最左最右中间$0$的个数了

## 弱鸡的代码

```cpp
#include <iostream>

using namespace std;

const int Maxn = 60;

int n;
int a[Maxn];
int ans;
int t;
int L, R;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++){
		ans = 0;
		cin >> t;
		bool iL = 0, iR = 0;
		L = 1;
		R = t;
		for (int j = 1; j <= t; j++){
			cin >> a[j];
			if (a[j]){
				ans++;
			}
		}
		if (ans == 1){ //特判只有一个1的情况
			cout << 0 << endl;
			continue;
		}
		for (int j = 1; j <= t; j++){ //计算最左和最右的1
			if (a[j]&&!iL){
				iL = 1;
				L = j;
			}
			if (a[t-j+1]&&!iR){
				iR = 1;
				R = t-j+1;
			}
		}
		ans = 0;
		for (int j = L; j <= R; j++){ //统计中间0的个数
			if (!a[j])
				ans++;
		}
		cout << ans << endl;
	}
	return 0;
}
```


---

