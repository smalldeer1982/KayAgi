# Minimum Varied Number

## 题目描述

找出数码和为 $s$ 的最小数字，使得其中的所有数字都是不同的（即所有数字都是唯一的）。

例如，如果 $s=20$ ，那么答案是 $389$。这是最小的数字，其中所有数字都不同，数字的总和为 $20$ （$3+8+9=20$）。

对于给定的 $s$ ，输出这个最小数字。

## 样例 #1

### 输入

```
4
20
8
45
10```

### 输出

```
389
8
123456789
19```

# 题解

## 作者：FQR_ (赞：9)

### 题目翻译

给定正整数 $s$，将它拆成几个小于 $10$ 的不同数字的和，再将这几个数字拼起来。

求上述操作的最小值。
___
### 思路

要求拼出来的数字最小，就要保证位数最小，第一个数字最小。

想使上述条件成立，必须满足 倒数第一位是 $9$，倒数第二位是 $8$，倒数第三位是 $7$……

第一位就是 总数减去已经填过的数字。

___
### 代码思路

将 $i$ 从 $9$ 向 $1$ 遍历。

如果 $s$ 比 $i$ 大，就把 $i$ 填到答案里，并将 $s$ 减去  $i$。

否则，表示填到第一位了，就将 $s$ 填到答案里，跳出循环。

___
### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		int s;cin>>s;
		string ans;
		for(int i=9;i>=1;i--)
		{
			if(s>i) 
			{
				ans+=(i+'0');
				s-=i;
			}
			else
			{
				ans+=(s+'0');
				break;
			}
		}
		for(int i=ans.size()-1;i>=0;i--) cout<<ans[i];
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：linyihdfj (赞：6)

## C.Minimum Varied Number

### 题目描述：
[原题面](https://codeforc.es/contest/1714/problem/C)

### 题目分析：
为了使得这个数最小我们肯定是贪心地从大到小选取数，因为这样可以保证位数最小。然后能选则选，最后按从小到大的顺序输出就好了，因为显然这样是选择这些数的前提下的最小的方案。

### 代码详解：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int s;
		cin>>s;
		stack<int> st;
		for(int i=9; i>=1; i--){
			if(s - i >= 0)	st.push(i),s-=i;
		}
		while(!st.empty()){
			int now = st.top();st.pop();
			printf("%d",now); 
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Qerucy (赞：3)

因为我们要求的数尽可能地小，所以我们的位数就要尽可能地少，那么最后得到的答案就要每一位上的数都要尽可能地大，而且我们要使较小的数字在较高位，较大的数字在较低位，这个是在小学数学的教学范围里的。

我们只需要从 $9$ 到 $1$ 枚举看看能不能用，能用就保留下来，不能用就看看下一个数能不能用即可。

最后再从小到大输出保留下来的数字即可。

代码：

```cpp
#include<bits/stdc++.h>
 
int b,c,t;
int n,h,m;
int a[1000010];
int cnt;
 
int main(){
    scanf("%d",&t);
    while(t--){
        cnt=0;
        int i=9;
        scanf("%d",&n);
        while(n){
            if(n>=i) n-=i,a[++cnt]=i;//能用就用。
            i--;//枚举下一个。
        }
        for(int i=cnt;i>=1;i--){
            printf("%d",a[i]);//因为存储时已经是从大到小存储的了，所以只需要倒序输出即可。
        }
        puts("");
    }
    return 0;
}
```


---

## 作者：Jasper08 (赞：3)

本题可以用贪心的做法。由于题目要求输出的数每位上的数字都不能相同，所以对于一个 $n$ 位数，其最大数字和为 $9+8+\cdots+(9-n+1)=\dfrac{n(19-n)}{2}$。所以我们可以枚举计算使得数字和为 $s$ 至少要多少位数字。

确定了位数，接下来我们就要填上每一位的数字了。由于题目要求的是最小值，所以首位要尽量小，那么后面的几位就要尽量大。从最后一位开始填，每次填上当前能填的最大值。对于第 $i$ 位上的数 $nun_i$，其应该满足 $num_i+[1+2+\cdots+(i-1)]=num_i+\dfrac{i(i-1)}{2}\le s$，保证前面的 $i-1$ 位能填上互不相同的数。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

int num[12]; //存储答案

int find_digit(int s) { //计算使得数字和为s至少需要几位数
	int digit = 0;
	while (s > digit*(19-digit)/2) digit ++;
	return digit;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t -- ) {
		int s;
		scanf("%d", &s);
		int digit = find_digit(s);
		int k = 9; //从大到小开始填数
		for (int i = digit; i >= 1; --i) { //为了确保首位最小,应该倒着填数
			while (s < k+i*(i-1)/2) k --; //判断k能否填入
			s -= k;
			num[i] = k;
			k --;
		}
		for (int i = 1; i <= digit; ++i) printf("%d", num[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：cst_123 (赞：2)

### - [传送门](https://www.luogu.com.cn/problem/CF1714C)

------------

### 题意

给你 $T$ 个数，你需要找到一个各个数位为该数总和的最小数字，数字中的各个数位不能相同。

### 思路

我们可以从大到小地选取数字，再用一个数组存一下，这样数位使是最小的。然后我们就倒着输出，那么该数字会是最小的。

### 代码

```cpp
//ans数组记录我们需要求出的数字的数位
while(T--){
	n=read();
	for(int i=1;i<=9;i++)//多组数据需清0
		ans[i]=0;
	for(int i=9;i>=1;i--)//题目中n很小，最多循环之和为45
		if(n>=i){
			ans[i]=i;n-=i;
		}
		else{//n比i小了，直接存入n，退出
			ans[i]=n;break;
		}
	for(int i=1;i<=9;i++)//由于我们是不会选0的，所以只输出不为0的，当然也可以提前退出
		if(ans[i]!=0)
			printf("%d",ans[i]);
	printf("\n");
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 视频题解

![](bilibili:BV1Qg41117Qb)

### 2 思路

考虑到 $s\le45$，我们发现最大的答案也不过是 $123456789$。

首先我们可以枚举答案的位数。

然后先填上 $123456……$。如果啊填完后发现超出目标直接离开。

否则，我们可以发现，尽可能增加低位的数字才好。

首先将个位数字增加，如果到 $9$ 还不能满足要求，就增加十位数到 $8$，以此类推。

如果最后没能满足要求，说明答案的位数会更大；如果满足要求，它就是最优的答案。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t;
int n;
int ans[12];
int ansi;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1714C_1.in","r",stdin);
	freopen("CF1714C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(ansi=1;ansi<=9;++ansi){
			int x=n-(((ansi+1)*ansi)>>1);
			if(x<0)continue;
			for(int i=1;i<=ansi;++i)ans[i]=i;
			for(int i=ansi,ok=9;i>=1&&x>0;--i,--ok){
				if(ok-ans[i]<=x){
					x-=ok-ans[i];
					ans[i]=ok;
				}
				else{
					ans[i]+=x;
					x=0;
				}
			}
			if(x<=0)break;
		}
		for(int i=1;i<=ansi;++i)printf("%d",ans[i]);
		printf("\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/82203984)

By **dengziyue**

---

## 作者：sixrc (赞：0)

考虑贪心，首先优先使得位数尽量小，也就是说尽量从 $9$ 开始从高位往低位选，能选大的就选大的，直到不能选，也就是选出的数字之和等于 $s$ 为止。其次，要使得首位尽量小，所以将选出的数字从小到大输出即可。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int t, n, p, a[15];
int main(){
	scanf ("%d", &t);
	while (t --){
		memset(a, p=0, sizeof(a));
		scanf ("%d", &n);
		if (n < 10){
			printf ("%d\n", n);
			continue;
		}
		for (int i=9; i>=1; i--){
			if (n - i >= 0){
				n -= i;
				a[++p] = i;
			}
		}
		for (int i=p; i>=1; i--) printf ("%d", a[i]);
		puts ("");
	}
	return 0;
}
```

---

## 作者：zhicheng (赞：0)

### 思路

显然，要使得最后的答案最小，那么我们要先保证位数最小。又要求每个数位不相同，因此我们考虑每一位的顺序应该是 $9,8,...,1$。接下来，答案最小就意味着高位要小，低位要大。因此我们从最低位开始放 $9,8,...,1$，直到 $n$ 放完。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int s[15];
int main(){
	int n,a,k,now;
	scanf("%d",&n);
	while(n--){
		now=0;
		scanf("%d",&a);
		k=9;  //从9开始放
		while(a>=k&&k>=1){  //放到1结束，或者放到放不了k
			a-=k;
			s[++now]=k;  //从低位开始放
			k--;
		}
		if(a!=0){
			s[++now]=a;  //最后的剩余
		}
		for(int i=now;i>=1;i--){
			printf("%d",s[i]);  //从高位开始输出
		}
		printf("\n");
	}
}
```

---

## 作者：tian_jun_cheng (赞：0)

## 大意

给你一个数，请你找出每一位不同的，数字和为这个数的最小的数。

## 方法

因为数据范围很小，所以打表计算。

根据题目给的输入输出，判断终止条件。

```cpp
for(int i=1;i<=45;i++)
{
    for(int j=1;j<=123456789;j++)
    {
        int sum=0;
        int k=j;
        set <int> s;
        int cnt=0;
        while(k)
        {
            sum+=k%10;
            cnt++;
            s.insert(k%10);
            k/=10;
        }
        if(sum==i && s.size()==cnt)
        {
            cout<<j<<",";
            break;
        }
    }
}
```
然后把答案记录在数组里面，解决问题。

## 规律

打完表后，我发现了一种规律。

每一次确定结尾，把开头加一，如果出现进位或重复数字就往后延伸一位。

---

## 作者：zfx_VeXl6 (赞：0)

## 我的翻译
### 题目描述

找出数码和为 $s$ 的最小数字，使得其中的所有数字都是不同的（即所有数字都是唯一的）。

例如，如果 $s=20$ ，那么答案是 $389$ 。这是最小的数字，其中所有数字都不同，数字的总和为 $20$ （$3+8+9=20$）。

对于给定的 $s$ ，输出这个最小数字。

### 输入格式

第一行包含整数 $t$ ( $1≤t≤45$） — 测试用例的数量。

每个测试用例由包含一行唯一整数：指定的 $s$ ($1≤s≤45$)。

### 输出格式

输出 $t$ 个整数 ― 给定测试用例的答案。

### 样例解释

对于第一个测试用例，$s=20$，最小数字为 $389$。

对于第二个测试用例，$s=8$，最小数字为 $8$（$8=8$）。

对于第一个测试用例，$s=45$，最小数字为 $123456789$（$1+2+3+4+5+6+7+8+9=45$）。

对于第一个测试用例，$s=10$，最小数字为 $19$（$1+9=10$）。

---

## 解法
这是一道数学问题。

不难发现当 $s<10$ 时，最小数字就是 $s$ 。

而当 $s\ge10$ 时，要让答案最小，那么位数就要最小，最高位也要最小，因此就要让低位尽可能大。

所以，有如下的模拟过程：
- $10$ -> $19$
- $11$ -> $29$
- $12$ -> $39$
- $\dots$
- $17$ -> $89$
- $18$ -> $189$
- $\dots$

十位无法增加就增加百位，以此类推。

用代码模拟如下：
```cpp
int ans=9,p=1;
for(int i=1;i<=n;i++)
{
	if(check(ans+p))	//有重复数字
    	p*=10;			//模拟进位
    ans+=p;				//最高位加1
}
```

~~其实我在比赛时用的是打表，因为数据较小。~~
我当时其实已经找到方法了。希望大家在打比赛时
~~（除非迫不得已）~~
不要有我这种想法。

---

## 作者：Jeremiahy (赞：0)

## 题意

给出一个数字 $s$，求出最小的数使得这个数各位数字之和为 $s$ 且这个数各位数字互不相同。

# 分析


可以使用打表过此题，那就讲一下暴力的思路。

从小到大枚举数字，遇见符合要求的数就输出。

怎么判断是否符合要求呢？分解每一位，并判断是否互不相同。如果有重复数字或各位之和不等于 $s$，就不符合要求。反之则符合。

我们可以写出如下的暴力打表代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, s;
bool check(int x) {
	int cnt = 0, v[11];
	memset(v, 0, sizeof(v));
	while (x) {
		if (v[x % 10])//有重复
			return 0;
		v[x % 10] = 1;
		cnt += x % 10;
		x /= 10;
	}
	return cnt == s;//是否各位数字之和为 s
}
signed main () {
	for (s = 1; s <= 45; s++)
		for (register int i = 1; ; i++)
			if (check(i)) {//符合要求
				cout << i << ", ";	
				break;			
			}
	}
	return 0;
}
```

于是我们得到了如下打表代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, s;
int ans[500] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 19, 29, 39, 49, 59, 69, 79, 89, 189, 289, 389, 489, 589, 689, 789, 1789, 2789, 3789, 4789, 5789, 6789, 16789, 26789, 36789, 46789, 56789, 156789, 256789, 356789, 456789, 1456789, 2456789, 3456789, 13456789, 23456789, 123456789};
signed main () {
	cin >> t;
	while (t--) {
		cin >> s;
		cout << ans[s] << '\n';
	}
	return 0;
}
```


---

## 作者：Error_Eric (赞：0)

橙罢，最多黄。

#### 题意：

定义 $sum(x)$ 为（十进制意义下） $x$ 各位数字和。

给定 $sum(x)$ 求最小的 $x$ 使得 $x$ 各位数字不同。

#### 解法：

首先位数尽量少，能三位数不四位数。


对于 $n$ 位数

$\overline{a_na_{n-1}...a_2a_1}$

$=\sum_{i=1}^{n}a_i10^{n-1}$

$=\sum_{i=1}^{n}a_i+\sum_{i=1}^{n}a_i(10^{n-1}-1)$

$=sum(x)+\sum_{i=1}^{n}a_i(10^{n-1}-1)$

这样看可能不直观。

$n=5$ 时展开:

$9999a_5+999a_4+99a_3+9a_2+0a_1+sum(x)$ 

那么显然下标小的数尽量大。

数据有限，最佳方案是打表。

#### Code:

[打表](https://www.luogu.com.cn/record/82111463)(建议用正解打表)

正解（正常解法）：

```cpp
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<stack>
using namespace std;
#define il inline
#define rei register int
il const void readln(int &I){
    I=0;char C=getchar();
    while(!isdigit(C))C=getchar();
    while( isdigit(C))I=I*10+C-'0',C=getchar();
}
int n,t,sum;
stack<int>num;
int main(){
	readln(t);
	while(t--){
		readln(n),sum=0;
		for(rei i=9;sum+i<n;i--)
			num.push(i),sum+=i;
		num.push(n-sum);
		while(!num.empty()){
			cout<<num.top();
			num.pop();
		}
		cout<<endl 
	}

}
```



---

## 作者：cachejtt (赞：0)

## 题意
给你一个数 $s$，你需要构造一个数 $n$ 使得 $n$ 的数位和等于 $s$，并且 $n$ 的各位各不相同。输出 $n$ 的最小值。

## 思路
注意到 $n$ 的位数越小，则 $n$ 越小，因此各位上必须尽量大。

正难则反，由于各不相同，因此从 $9$ 开始放，依次向前，若当前剩余不足，则直接输出即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define endl "\n"
using namespace std;
int t,n,a[15],cnt;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n;
    cnt=0;
    while(n>0){
      cnt++;
      if(n>=10-cnt){
        a[cnt]=10-cnt;
        n-=10-cnt;
      }
      else {
        a[cnt]=n;
        n=0;
      }
    }
    nrep(i,cnt,1)cout<<a[i];
    cout<<endl;
  }
  return 0;
}
```

---

## 作者：YCSluogu (赞：0)

## CF1714C 题解

### 题目翻译

对于每组数据，给你一个数字 $s$，要求你求出最小的数并且满足的各个数字之和刚好是 $s$

例如数 $389$，所对应的 $s$ 就是 $3 + 8 + 9 = 20$

同时每一个数内各个数字不能相同

### 思路

数据范围仅仅只是 $1 \le s \le 45$

~~那么打表不就行了~~

确实，很多人都会用 ~~简短~~ 时间敲出如下这个表：

``` cpp
long long ans[50] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 19, 29, 39, 49, 59, 69, 79, 89, 189, 289, 389, 489, 589, 689, 789, 1789, 2789, 3789, 4789, 5789, 6789, 16789, 26789, 36789, 46789, 56789, 156789, 256789, 356789, 456789, 1456789, 2456789, 3456789, 13456789, 23456789, 123456789
};
```

~~然后直接查表是吧~~

可是我们怎么能够苟且于简单的打表呢！这里提供一下深搜的思路 ~~并且也是我的表生成器~~

我们可以很快得到一个结论：一个数内的数字是单调递增的。可以很简单地证明：若存在此数内各个数字不单调递增，那一定可以通过重新排列各个数字得到一个更小、同时对应的 $s$ 不变的数。

然后设计一下深搜状态 $(d, p, s)$，其中 $d$ 是上一个选择的数字，$p$ 是当前处理出来的数，$s$ 为各个数字之和。

对此我们可以灰常快得得到深搜代码：

``` cpp
void dfs(int d, int p, int s) {
  ans[s] = min(ans[s], p);
  for (int i = d + 1; i <= 9; i++) { dfs(i, p * 10 + i, s + i); }
}
```

完美收官。

``` cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1000;

int t;
int ans[kMaxN];

void dfs(int d, int p, int s) {
  ans[s] = min(ans[s], p);
  for (int i = d + 1; i <= 9; i++) { dfs(i, p * 10 + i, s + i); }
}

void solve() {
  int n;
  cin >> n;
  cout << ans[n] << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  memset(ans, 0x3f, sizeof(ans));
  dfs(0, 0, 0);
  cin >> t;
  while (t--) { solve(); }
  return (0 - 0);
}
```


---

