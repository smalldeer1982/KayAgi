# Happy Birthday

## 题目描述

You have a set of birthday cake candles. Each of such candles represents a digit between $ 0 $ and $ 9 $ , inclusive.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1250H/d5cd74fe7ac15db0e75f654137471b0878202976.png)Example of birthday cake candles.Let's denote the candle representing the digit $ d $ as $ d $ -candle.

Your set contains $ c_0 $ instances of $ 0 $ -candles, $ c_1 $ instances of $ 1 $ -candles and so on. So, the total number of candles is $ c_0+c_1+\dots+c_9 $ .

These digits are needed to wish your cat a happy birthday. For each birthday, starting with the first, you want to compose the age of the cat using the digits from the set.

Since you light candles for a very short time, candles don't have time to burn out. For this reason you can reuse candles an arbitrary number of times (therefore your set of candles never changes).

For example, if you have one instance of each digit (i.e. $ c_0=c_1=\dots=c_9=1 $ ), you can compose any number from $ 1 $ to $ 10 $ using this set, but you cannot compose $ 11 $ .

You have to determine the first birthday, on which you cannot compose the age of the cat using the candles from your set. In other words, find the minimum number $ y $ such that all numbers from $ 1 $ to $ y-1 $ can be composed by digits from your set, but $ y $ cannot be composed.

## 样例 #1

### 输入

```
4
1 1 1 1 1 1 1 1 1 1
0 0 1 1 2 2 3 3 4 4
1 2 1 2 1 3 1 0 0 0
0 1 2 1 4 3 1 1 2 1
```

### 输出

```
11
1
7
10
```

# 题解

## 作者：naroto2022 (赞：1)

# CF1250H题解
### 题意
现在你有 $c_i$ 个 $i$（$0\leqslant i\leqslant 9$），问你不能拼的最小数是多少。
### 思路
先看数据范围：$0\leqslant c_i\leqslant 10^5$，暴力一看就是不行的！

那我们就换一种想法：

1. 若 $0$ 的个数大于等于数字个数最少的个数：首先先设有的数字个数最少的之中最小的数为 $i$，$i$ 的个数为 $cnt$，则最小不能拼的数为 $cnt+1$ 个 $i$（$i\times 10^{cnt+1}+i$）。
2. 若 $0$ 的个数小于数字个数最少的个数：设有 $cnt$ 个 $0$，则最小的数为 $10^{cnt+1}$（输出一个 $1$，然后输出 $cnt+1$ 个 $0$）。

### 总结
1. 分类讨论。
2. 换行。
3. 千万不能直接去算最大的数，绝对要超出数据范围（那可是 $10^{10^5}$）。
4. 一定要注意初始化。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int T;//T组数据。
int c[15],minn,cnt; 
//minn记录除0以外有的个数最少的最小数。
//cnt记录这个最小数的出现个数。 
int main(){
	scanf("%d",&T);
	while(T--){
		minn=2147483647;//附上最大值。(INT_MAX) 
		for(int i=0; i<=9; i++){
			scanf("%d",&c[i]);
			if(i!=0&&minn>c[i]){//记录。 
				minn=c[i];
				cnt=i;
			}
			//"minn>c[i]"不可以写>=因为是要取有的个数最少的最小数，加了'='则变成了求有的个数最少的最大数。	 
		}
		if(minn>c[0]){//特殊情况：0的个数最少。 
			printf("1");
			for(int i=1; i<=c[0]+1; i++) printf("0"); 
		} 
		else for(int i=1; i<=minn+1; i++) printf("%d",cnt);//记得cnt要加1
		printf("\n");//一定要记得换行！ 
	}
	return 0;
}
```


---

## 作者：Cappuccino_mjj (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1250H)
题目意思：

现在你有 ``0``~``9`` 的数字各 $a_i$ 个，请问最早不能组成的数字是哪个？

---

思路：

暴力是绝对不行的，因为在每个 $a_i$ 都很大的时候就会超时！因此我们要找规律。

在样例中我发现了，第 $i$ 个数最早不能组成的数一定用了 $a_i+1$ 个第 $i$ 个数。如果是这样，我们就在 $a_i$ 的值里找最小值就行了。找到最小值，输出 $a_i+1$ 个 $i$ 就行了。

但是最小值是 $a_0$ 怎么办呢？只要特判如果 ``0`` 的个数比其他数的最小值还小，就输出一个 ``1`` 和 $a_0+1$ 个 ``0`` 即可。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int a[15];
int main()
{
	cin>>t;
	while(t--)
	{
		int minn=0x3f3f3f3f,id;
		cin>>a[0];
		for(int i=1;i<=9;i++)
		{
			cin>>a[i];
			if(a[i]<minn)
				minn=a[i],id=i;
		}
		if(a[0]<minn)
		{
			cout<<1;
			for(int i=1;i<=a[0]+1;i++)
				cout<<0;
			cout<<endl;
		}
		else
		{
			for(int i=1;i<=minn+1;i++)
				cout<<id;
			cout<<endl;
		}
	}
}
```

---

完美撒花~

---

## 作者：wangyixuan_s_father (赞：1)

## CF1250H题解

#### 题意
现在有 $10$ 个数 $c_0,c_1\cdots c_9$ 分别代表数字 $0$ 到 $9$ 的个数。求数 $y$ 最大值，使现有数字能拼出 $y-1$ 以内的任意数。

#### 思路
我们知道如果 $i$ 蜡烛的数量为 $x$，那么第一个必拼不出来的数一定是每位都是 $i$ 的 $x+1$ 位数。那么，我们就能想到在 $c_1$ 到 $c_9$ 中取 $\min$（如果有重复取最小  $i$）。但是，$0$ 需要特判，因为每位都是 $0$ 的数就等于 $0$，而最早需要 $x$ 个 $0$ 的正整数就是 $10^x$。那么我们就要特判，看 $0$ 的个数是否小于之前最小值。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int a[10],n=100001,ans,m,t;
int main()
{
	t=read();
	while(t--)//多测别忘
	{
		m=read();//0特殊输入
		for(int i=1;i<=9;i++)
		{
			a[i]=read();
			if(a[i]<n)
			{
				ans=i;
				n=a[i];
			}
		} 
		if(n==0)cout<<ans;
		else if(m<n)//0数量最少
		{
			cout<<1;
			for(int i=1;i<=m+1;i++)
			{
				cout<<0; 
			}
		}
		else
		{
			for(int i=1;i<=n+1;i++)
			{
				cout<<ans;
			}
		}
		cout<<endl;
		n=100001;//记得初始化
	} 
	return 0;//van结撒花
}
```

#### 扯一扯
提交于2022-4-11

修改于2023/5/8

打个郊县

---

## 作者：_Sonnet (赞：1)

这就是一道思维题，想通了就会觉得很简单。

### 思路如下：
什么时候会无法组成一个数呢？当这个数有 $n$ 位，且每一位都为 $a$，但是你**没有** $n$ 个 $a$ 时，这个数就无法被组成了。

所以我们只需要找出 $0$ 至 $9$ 中数量最少的那个数字 $a$，然后输出 $a$ 的数量 $+1$ 个 $a$ 就可以了。

**但是！！**

当 $0$ 是数量最少的时候就特殊一点，因为 $0$ 不能放在第一位，所以应该在前面加个 $1$ 。

### 代码如下：

```c
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[15];
int minn=0x3f3f3f;
int id;
signed main(){
	int t;
	cin>>t;
	while(t--){
		cin>>a[0];
		minn=0x3f3f3f3f3f3f;
		for(int i=1;i<=9;i++){
			cin>>a[i];
			if(minn>a[i]){
				minn=a[i];
				id=i;
			}
		}
		if(minn==0) cout<<id<<endl;
		else if(a[0]<minn){
			cout<<1;
			for(int i=1;i<=a[0]+1;i++){
				cout<<0;
			}
			cout<<endl;
		}
		else{
			for(int i=1;i<=minn+1;i++){
				cout<<id;
			}
			cout<<endl;
		}
	}
	return 0;
}

`````````

---

## 作者：_Violet_Evergarden (赞：0)

# 思路：
我们考虑两种：

当 $c_i$ 的最小值不是 $0$ 时，我们找到最小的 $c_i$ 中最小的 $i$ 那答案就是 $c_i+1$ 个 $i$。

当 $c_i$ 的最小值仅是 $0$ 时，我们找到最小的 $c_i$ 中最小的 $i$ 那答案就是 $1$ 后接 $c_i$ 个 $0$。

# 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
int c[101];
int t;
int minn,xia;
int main()
{
	cin>>t;
	while(t--){
		minn=10000000;
		for(int i=0;i<=9;i++){
			cin>>c[i];
		}
		c[10]=c[0];
		for(int i=1;i<=10;i++){
			if(minn>c[i]){
				minn=min(c[i],minn);
				xia=i;
			}
		}
		if(xia==10){
			cout<<'1';
			for(int i=1;i<=minn+1;i++){
				cout<<0;
			}
			cout<<endl;
		}
		else{
			for(int i=1;i<=minn+1;i++){
				cout<<xia;
			}
			cout<<endl;
		}
	}
	return 0;
}
```


---

## 作者：_xxxxx_ (赞：0)

### 题解

给出 `0` 到 `9` 的数码的个数，记为 $bit_i$，现在你需要求出第一个不能通过这些数码拼出来的数字。（如：`114` 是 $2$ 个 `1` 和 $1$ 个 `4`）

### 分析

很容易想到从小到大枚举每一个数，然后对其进行数位拆分，看看够不够用，不够用就输出。但是看数据范围，$a_i\le 2\times 10^{5}$，时间复杂度大的吓人。但是我们是已经知道每个数码有多少个的，所以可以用另一种算法。

我们可以显然发现，对于一个个数最小的数码 $minn$，最小不能凑出的就是第一个个数为 $minn$ 的数码 $i$，所以答案就是 $minn+1$ 个 $i$。因为第 $minn+1$ 是第一个凑不出来的，用的比个数要多。

但是这样我们会发现，如果 $minn$ 是 `0` 的话，只有 $minn+1$ 个 `0` 显然不对。这时就需要一个 `1` 放在最前面，使其符合十进制的规则。那就是 `1` 和 $minn+1$ 个 `0`，这是 $minn+1$ 个 `0` 中最小的数。

可以让 $minn$ 从数码 `1` 开始找，然后比较一下就行，会简单一点。

总结一下：

1. $minn$ 是 `0` 时，输出一个 `1` 后，输出 $bit_0$ 加一。

2. 其他情况，输出 $minn+1$ 个 $bit_i$ 就行了。

### 代码

```
#include <iostream>
#include <stack>
#include <cmath>
#include <vector>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <iomanip>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
int bit[20]; 
signed main()
{
	int T;
	cin >> T;
	while(T--)
	{
		int minn = INF, now = 0;//now是最少的数码 
		for(int i = 0; i <= 9; i++)
		{
			cin >> bit[i];
			if(bit[i] < minn && i != 0)//不要把0算进去，会简单 
			{
				minn = bit[i];
				now = i; 
			}
		}
		bool f = 0;//记录0是否最小 
		if(bit[0] < minn)
		{
			cout << "1";
			f = 1;//是最小 
			now = 0;//要改变！ 
		}
		for(int i = 1; i <= (f ? bit[0] + 1 : minn + 1)/*如果是0，就是0的个数加1，否则就是minn加1*/; i++)
		{
			cout << now;
		}
		puts("");
	}
	return 0;
}

```

---

## 作者：Wander_E (赞：0)

挺有意思的一道思维题。

这题的思路其实很简单，就是将 $c$ 中最小的数（记为 $c_i$）所对应的数（$i$）重复 $c_i + 1$ 次即可。如果 $i=0$ 那么就输出 $10^{c_i}$ （换句话说，先输出 $1$ 再输出 $c_i$ 个 $0$）。

附上 AC 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
const int N = 1e6 + 5;
const int INF = 0x3f3f3f3f;
int n;
int c[N];
int T;

signed main()
{
	cin >> T;
	while(T--)
	{
		for(int i = 0; i <= 9; i++) cin >> c[i];
		int minn = min_element(c + 1, c + 10) - c;
		if(c[minn] == 0) 
		{
			cout << minn << endl;
			continue;
		}
		else if(c[minn] > c[0])
		{
			cout << 1;
			for(int i = 1; i <= c[0] + 1; i++) cout << 0;
			cout << endl;
			continue;
		}
		for(int i = 1; i <= c[minn] + 1; i++) cout << minn;
		cout << endl;
	}
	return 0;
}
```

---

## 作者：_Winham_ (赞：0)

题目意思：

说一个人有 $0$ 到 $9$ 的蜡烛分别有 $c_{0}$ 到 $c_{9}$ 根，问从 $1$ 开始，第几个数字，无法用蜡烛组成。

-----

思路：

先观察第二组数据，发现输出 $1$ 的情况，就是 $c_1$ 为 $0$ 的情况。当我们排除 $1$ 的情况后。我们就来找一下规律。经过我们观察这组样 ` 0 1 2 1 4 3 1 1 2 1` 例能发现只要 $c_{0}$ 的个数小于 $c_{1}$ 至 $c_{9}$ 的最小值小于 $c_{0}$ 那么我们就能直接输出 `1` 之后再输出 $c_{0} + 1$ 个 $0$ 就行了。可是如果不小于最小值呢，我们接下来看到 `1 2 1 2 1 3 1 0 0 0` 这组样例，能发现 $c_{1}$ 至 $c_{9}$ 的最小值，输出最小值加上 $1$ 个最小值的下标。

---
验证：

既然找到了规律我们就来验证规律的三种情况。我们先来测试一下 $c_{1}$ 为 $0$ 的情况，不过能发现只要为 $1$ 的蜡烛为 $0$ 就肯定答案是 $1$。第二种情况 $c_{0}$ 大于等于 $c_{1}$ 至 $c_{9}$ 最小值，我们来试试 `7 3 5 6 4 5 6 7 1 9` 这组数据，发现输出为 $88$ 与猜测的没错。到底三种情况 $c_{0}$ 小于 最小值的情况，我们用 `2 3 5 6 4 5 6 7 3 9` 这组数据发现输出的是 $1000$，与猜测没错。既然找到了规律，那就上代码吧。

----

```cpp
#include<iostream>
#include<string>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<iomanip>
using namespace std;
#define LL long long
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
int T,a[N],minn=INF,cnt; 
int main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	cin>>T;
	while(T--){
		minn=INF,cnt=10;
		for(int i=0;i<=9;i++)cin>>a[i];
		if(a[1]==0){
			cout<<1<<endl;
			continue;
		}
		for(int i=1;i<=9;i++)
			if(a[i]<minn)minn=a[i],cnt=i;
		if(a[0]>=minn)
			for(int i=1;i<=minn+1;i++)cout<<cnt;
		else {
			cout<<1;
			for(int i=1;i<=a[0]+1;i++)cout<<0;
		}
		cout<<endl;
	}
	return 0;
}


```

---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1250H)

# 思路

思路很清晰，找出 ${c}_{0}$ 至 ${c}_{9}$ 中的最小值即可。

## 但是！

第一个需要特判，因为如果都是 0，那结果也是 0。

AC 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
const int INF=1e8;
int T,x,a0;
int main()
{
    cin>>T;
    while(T--)
    {
        int p=-1,minA=INF;
        cin>>a0;
        for(int i=1;i<=9;i++)
        {
            cin>>x;
            if(x<minA)
            {
                minA=x;
                p=i;
            }
        }
        if(minA==0)cout<<p;
        else if(a0<minA)
        {
            cout<<"1";
            for(int i=1;i<=a0+1;i++)cout<<"0";
        }
        else for(int i=1;i<=minA+1;i++)cout<<p;
        cout<<endl;
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/111438127)

---

## 作者：分离性漫游 (赞：0)

## CF1250H题解
### 一、题目大意
首先这道题会给你 $t$ 给数据组，每一组会给你 $10$ 个数字分别表示从 $0$ 到 $9$ 每一个数字的个数，让你找出来每一个组中你这个组中最大能拼出来的数减去 $1$ 。
### 二、思路讲解
因为我们要找出最大能输出的数，因此我们需要找出 $10$ 个数字中最少的个数。

之所以找出最小的个数是因为他的个数不足以让他拼出他的个数加 $1$ 的位数，同时因为我们要找出最早拼不出来的数，所以如果同时有 $2$ 个或多个有的蜡烛数相同的话我们要选择最前面的数字。

接下来是重点，$0$ 需要特判。

**$0$ 不需要和其他数字一样，因为如果拼出 $10$ 只需要一个 $0$ 不需要和其他的数一样需要多个相同的蜡烛，例如 $11$ 和 $333$ 。**

因此在代码中我们需要特判 $0$ ，$0$ 只需要其他数字的蜡烛数减去 $1$ 即可，还需要加上如果数字 $0$ 的个数为 $0$ 个，我们不能输出 $1$ ,因为我们是从数字 $1$开始拼的，所以是 $10$ 。
### 三、参考代码
```C++
#include<bits/stdc++.h>
using namespace std;
int t,a[15];
int main()
{
	cin>>t;
	while(t--)
	{
		int ok=0;
		for(int i=0;i<10;i++) cin>>a[i];
		for(int i=0;i<0x3f3f3f3f;i++)
		{
			if(a[0]==i-1)
			{
				cout<<1;
				for(int j=0;j<i;j++) cout<<0;
				cout<<endl;
				break;
			}
			for(int j=1;j<10;j++)
			{
				if(a[j]==i)
				{
					for(int k=0;k<=i;k++) cout<<j;
					cout<<endl;
					ok=1;
					break;
				}
			}
			if(ok==1) break;
		}
	}
	return 0;
}
```



---

