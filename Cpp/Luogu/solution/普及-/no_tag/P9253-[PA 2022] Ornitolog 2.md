# [PA 2022] Ornitolog 2

## 题目描述

**题目译自 [PA 2022](https://sio2.mimuw.edu.pl/c/pa-2022-1/dashboard/) Runda 1 [Ornitolog 2](https://sio2.mimuw.edu.pl/c/pa-2022-1/p/orn/)**

交替鹡鸰（*Motacilla alterna*）是鹡鸰属的一种鸟类。它因其独特的鸟鸣而与众不同，这种鸟的鸟鸣中，连续的音高交替地增加和减少。例如，如果我们用整数来表示音高，那么，鸟鸣可以是 $[2, 1, 3]$ 和 $[4, 5, -6, -5]$，但不能是 $[1, 2, 3, 2]$ 或 $[6, 5, 5, 4]$。为了记录这种迷人的生物，鸟类学家 Byteasar 将他的录音笔留在森林中数天。他现在想知道录到的声音是否与鹡鸰的鸟鸣相似。

写一个程序，给定音高序列，确定最少将音高序列中多少个整数改成 $[-10^9,10^9]$ 区间内的任意整数，才能使得这个序列成为交替鹡鸰鸟鸣的音高序列。

## 说明/提示

对于 $100\%$ 的数据，满足：

$3\le n\le 5 \times 10^4, -10^6\le a_i\le 10^6$。

## 样例 #1

### 输入

```
5
4 1 3 3 1
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
-1000000 -1000000 -1000000 -1000000
```

### 输出

```
2```

# 题解

## 作者：wmrqwq (赞：7)

# 题目链接

[P9253 [PA 2022] Ornitolog 2](https://www.luogu.com.cn/problem/P9253)

# 题目简述

给定一个音高序列，输出最少要修改多少整数才能使这个序列成为交替鹡鸰鸟鸣的音高序列。

# 题意分析

操作后的音高序列总共有 $2$ 种可能：

1. 音量由高变低再由低变高；

2. 音量由低变高再由高变低。

又因为大小范围是 $10^4  \times 5$，因此将数组开大一点定义大小为 $10^5+10$。

这样也需要考虑 $2$ 种情况：

1. 如果 $i$ 为偶数，且 $a_{i-1} \le a_{i}$，那么将对应的 $sum$ 增加 $1$，将 $pd$ 设为 ```true```；

2. 如果 $i$ 为奇数，且 $a_{i-1} \le a_{i}$，那么将对应的 $sum$ 增加 $1$，将 $pd$ 设为 ```true```，否则将 $pd$ 设为 ```false```。

最后只需要输出两种情况所需要的操作次数的最小值即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define QwQ return 0;
int a[100010],n,sum1,sum2,pd;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++)//首先考虑第一种情况
	{
		if(i%2==0)
		{
			if(a[i-1]>=a[i]&&pd==0)
				sum1++,pd=1;
			else
				pd=0;
		}
		else
		{
			if(a[i-1]<=a[i]&&pd==0)
	         	sum1++,pd=1;
			else//否则将pd设为0
				pd=0;
		}
	}
	pd=0;
	for(int i=1;i<n;i++)//然后再考虑第二种题目
	{
		if(i%2==1)//如果i为奇数，且a[i]>=a[i-1]那么sum2增加1，将pd设为 1
		{
			if(a[i-1]>=a[i]&&pd==0)
				sum2++,pd=1;
			else//否则将pd设为0
				pd=0;
		}
		else//如果i为偶数，且a[i]>=a[i-1]那么sum2增加1，将pd设为1
		{
			if(a[i-1]<=a[i]&&pd==0)
				sum2++,pd=1;
			else//否则将pd设为 0
				pd=0;
		}
	}
	cout<<min(sum1,sum2);//输出最小值
   QwQ;
}
```


---

## 作者：yangyang826 (赞：3)

交替音高有两种形式，分别是：     
低高低高 …… 和 高低高低 ……    
分别求如果要修改成这种形式最少需要几次修改，   
每次要改大就用 $10^9$，改小就用 $-10^9$ 即可。     
答案为两个结果的最小值。
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;cin>>n;
	int a[n],b[n];
	for(int i=0;i<n;i++){
		cin>>a[i];b[i]=a[i];
	} 
	int lh=0,hl=0;
	for(int i=1;i<n;i++){
		if(i%2==1&&a[i]>=a[i-1]||i%2==0&&a[i]<=a[i-1]){
			hl++;
			if(i%2==1) a[i]=-1e9;
			else a[i]=1e9;
		}
		if(i%2==1&&b[i]<=b[i-1]||i%2==0&&b[i]>=b[i-1]){
			lh++;
			if(i%2==1) b[i]=1e9;
			else b[i]=-1e9;
		}
	}
	cout<<min(lh,hl);
	return 0;
}
```

---

## 作者：__sxx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9253)
# 题意
将数组变成一个交替鹡鸰鸟鸣的音高序列，需要改多少个数。
## 思路
因为 $3\le n\le 5 \times 10^4$ ，所以可以直接模拟。
分两种情况考虑:
1. 第一个比第二个大。
1. 第一个比第二个小。

然后进行循环统计，最终输出他们的最小值。
## 注意
**在统计时需把数组改为保证下一个数比当前小或保证下一个数比当前大，记得将数组变成原来的。**
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[50005],b[50005],p1,p2,pd=0;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    	b[i]=a[i];
	}
  for(int i=2;i<=n;i++)
  {
  	if(i%2==0)
  	{
  	if(a[i]<=a[i-1]) 
  	{
  		p1++;
  		a[i]=1e18;//保证下一个数比当前小
	}
   }
   else
   {
   	if(a[i]>=a[i-1]) 
  	{
  		p1++;
  		a[i]=-1e18;//保证下一个数比当前大
	}
   }
  }
  for(int i=1;i<=n;i++)a[i]=b[i];
  for(int i=2;i<=n;i++)
  {
  	if(i%2==1)
  	{
  	if(a[i]<=a[i-1]) 
  	{
  		p2++;
  		a[i]=1e18;//保证下一个数比当前小
	}
   }
   else
   {
   	if(a[i]>=a[i-1]) 
  	{
  		p2++;
  		a[i]=-1e18;//保证下一个数比当前大
	}
   }
  }
  cout<<min(p1,p2);
  return 0;
}

```

---

## 作者：Mason123456 (赞：1)

## P9253

### 题面翻译

给定一个序列 $S$，求最小次数 $k$ 使得 $S$ 中的数字一大一小。

### 思路

贪心橙题。

分两种情况：第一种，$S$ 的奇数位为大位。第二种，$S$ 的偶数位为小位。

先看第一种情况。既然要保证奇数位最大，那么当奇数位 $i$ 满足 $S_i \le S_{i-1}$ 时，**更改** $S_i$ 使得 $S_i$ 最大。当偶数位 $j$ 满足 $S_j \ge S_{j-1}$ 时，**更改** $S_j$ 使得 $S_j$ 最小。

再看第二种情况。同理可得，当偶数位 $j$ 满足 $S_j \le S_{j-1}$ 时，**更改** $S_j$ 使得 $S_j$ 最大，当奇数位 $i$ 满足 $S_i \ge S_{i-1}$ 时，**更改** $S_i$ 使得 $S_i$ 最小。

### Code

对于第一种情况，有数组 `a1` 存储 $S$ 改变后的值。`aans` 为第一种情况，奇数位最大，改变次数。

对于第二种情况，有数组 `b1` 存储 $S$ 改变后的值。`bans` 为第二种情况，偶数位最大，改变次数。

`MAXN` 为在题面要求下的最大值，`-MAXN` 即为最小值。最后记得 `if` 要取等于号。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e4 + 5;
const int MAXN = 1e9;
int n;
int a[N], a1[N], b1[N];
int aans, bans;

main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i = 1;i <= n;i++){
		cin>>a[i];
	}
	int aans = 0, bbns = 0;//aans表示奇数最高
	a1[0] = -MAXN;
	b1[0] = MAXN;
	
	for(int i = 1;i <= n;i++){
		if(i % 2){
			if(a[i] <= a1[i-1]){
				aans++;
				a1[i] = MAXN;
			}
			else{
				a1[i] = a[i];
			}
		}
		else {
			if(a[i] >= a1[i-1]){
				aans++;
				a1[i] = -MAXN;
			}
			else{
				a1[i] = a[i];
			}
		}
	}
	
	
	for(int i = 1;i <= n;i++){
		if(i % 2 == 0){
			if(a[i] <= b1[i-1]){
				bans++;
				b1[i] = MAXN;
			}
			else
				b1[i] = a[i];
		}
		else {
			if(a[i] >= b1[i-1]){
				bans++;
				b1[i] = -MAXN;
			}
			else
				b1[i] = a[i];
		}
	}

	cout<<min(aans, bans);
}
```

---

## 作者：Cure_Wing (赞：1)

[P9253 [PA 2022] Ornitolog 2](https://www.luogu.com.cn/problem/P9253)

### 解法

仔细观察可以发现修改后的序列只可能是如下两种情况：

- 增加、减少、增加、减少、...、增加/减少；

- 减少、增加、减少、增加、...、增加/减少。

所以我们直接从 $1$ 开始，分类讨论将序列改成哪一种情况，如果对应位置合法就跳过，否则如果对应增加的设为最大值，对应要减小的设为最小值即可，这样子它对于下一个一定符合条件。

时间复杂度 $O(n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
constexpr int N=500005,inf=1e9;
int n,a[N],last,cnt,sum;
signed main(){
	freopen("watch.in","r",stdin);
	freopen("watch.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    last=a[1];
    for(int i=2;i<=n;++i){
        if(i&1){
            if(last>=a[i]){
                last=inf;
                ++cnt;
            }else last=a[i];
        }else{
            if(last<=a[i]){
                last=-inf;
                ++cnt;
            }else last=a[i];
        }
    }
    last=a[1];
    for(int i=2;i<=n;++i){
        if(i&1){
            if(last<=a[i]){
                last=-inf;
                ++sum;
            }else last=a[i];
        }else{
            if(last>=a[i]){
                last=inf;
                ++sum;
            }else last=a[i];
        }
    }
    cout<<std::min(cnt,sum);
    return 0;
}
```

---

## 作者：sxq9 (赞：1)

这一题看一眼数据范围就会发现可以直接搜，这里分两种情况讨论：峰形和谷形，就是先向上和先向下，细节看代码。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50010],b[50010];//这里的b数组用来记录是否更改过
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int s2=0,s=0;
	for(int i=2;i<=n;i++){//谷形 
		if(i%2==0&&a[i]>=a[i-1]&&!b[i-1])b[i]=1,s++;
		else if(i%2==1&&a[i]<=a[i-1]&&!b[i-1])b[i]=1,s++;
	}
	memset(b,0,sizeof(b));
	for(int i=2;i<=n;i++){//峰形 
		if(i%2==1&&a[i]>=a[i-1]&&!b[i-1])b[i]=1,s2++;
		else if(i%2==0&&a[i]<=a[i-1]&&!b[i-1])b[i]=1,s2++;
	}
	cout<<min(s,s2);
    return 0;
}
```

---

## 作者：_xdd_ (赞：0)

按照题意模拟一遍即可。

序列一共有两种情况，一种是先小后大，另一种是先大后小，答案就是这两种情况的答案的最小值。

假设这个序列为 $f$，模拟的是先小后大这种情况。

- 如果 $i$ 是偶数（需要 $f_i>f_{i-1}$），但 $f_i \le f_{i-1}$，就需要给 $f_i$ 设一个很大的值，并将答案加 $1$。

- 如果 $i$ 是奇数（需要 $f_i<f_{i-1}$），但 $f_i \ge f_{i-1}$，就需要给 $f_i$ 设一个很小的值，并将答案加 $1$。

另一种情况请举一反三，代码：

```cpp
#include<iostream>
using namespace std;
int n,d[50005]={1000001},x[50005]={-1000001},ans1,ans2;//如果你76pts，注意这里的数组初始化
int main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> d[i];
        x[i]=d[i];
        if(i%2){
            if(d[i]>=d[i-1]){ans1++;d[i]=-1000001;}
            if(x[i]<=x[i-1]){ans2++;x[i]=1000001;}
        }else{
            if(d[i]<=d[i-1]){ans1++;d[i]=1000001;}
            if(x[i]>=x[i-1]){ans2++;x[i]=-1000001;}
        }
    }
    cout << min(ans1,ans2);
    return 0;
}
```

---

## 作者：Vct14 (赞：0)

我们把交替鹡鸰鸟鸣的音高序列中大于相邻整数的数称为“较大数”，小于相邻整数的数称为“较小数”。考虑到序列中的元素一大一小间隔排列，最终的序列只有两种情况，即第一个数是较大数或较小数。我们分类讨论即可。在讨论时，如果一个本应是较大数的数小于上一个整数，那么就将它修改为一个较大数 $10^6+1$，反之亦然。最后求两种方法所用修改次数的较小值即可。

```c++
#include<bits/stdc++.h>
using namespace std;

const int N=5e4+2,A=1e6+1,B=-1e6-1;
int a[N],b[N];

int main(){
	int n;cin>>n;
	int cnt1=0,cnt2=0;
    a[0]=B,b[0]=A;
	for(int i=1; i<=n; i++){
		cin>>a[i];b[i]=a[i];
		if(i%2){
			if(a[i]<=a[i-1]) cnt1++,a[i]=A;
			if(b[i]>=b[i-1]) cnt2++,b[i]=B;
		}
		else{
			if(b[i]<=b[i-1]) cnt2++,b[i]=A;
			if(a[i]>=a[i-1]) cnt1++,a[i]=B;
		}
	}
	cout<<min(cnt1,cnt2);
	return 0;
}
```

---

## 作者：Chillturtle (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9253)

# 题意

有一种鸟，叫声满足（低高低高）或（高低高低）的规律，然后题目给出一个数组，对这个数组可以进行替换操作（把当前位的数字换成 $-10^9$ 到 $10^9$ 内的任意整数）问最少交换多少次后这个数组满足以上规律。

# 思路

一拿到题目，很容易想到直接对该数组进行遍历，分成两种情况来处理：

- 如果是低高低高，如果当前位置是偶数位那么判断 $a_i$ 与 $a_{i+1}$ 的大小关系，如果前者大则换，后者大则无操作。如果当前位是奇数位同理。

- 如果是高低高低，那么处理方式正好与上种处理方式相反。

这部分的代码很好实现，但写好后交一发就 ``wrong answer`` 了。为什么？

好我们来分析一下，然后我们就能够发现，我们把这个数换成了什么是问题的关键。如果有两个连续的数都不符合以上规律，**那么我们只需要改前一个数的值，就可以使这个位置符合条件**，所以我们可以用一个标记数组来记录当前位的前一位在这次遍历之前有没有被改过，如果被改过我们这一次就没有必要进行改动了。

最后将（低高低高）与（高低高低）两种情况的答案取最小值即可。

# AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10;
int n;
int a[N],b[N];
int marka[N],markb[N];
int ans;
int main(){
	cin>>n;
	memset(marka,0,sizeof(marka));
	memset(markb,0,sizeof(markb));
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int opt=0,optt=0;
	for(int i=2;i<=n;i++){
		if(i%2==0&&a[i]>=a[i-1]){
			if(marka[i-1]!=1){
				marka[i]=1;
				opt++;
			}
		}else if(i%2==1&&a[i]<=a[i-1]){
			if(marka[i-1]!=1){
				marka[i]=1;
				opt++;
			}
		}
	}
	for(int i=2;i<=n;i++){
		if(i%2==0&&a[i]<=a[i-1]){
			if(markb[i-1]!=1){
				markb[i]=1;
				optt++;
			}
		}else if(i%2==1&&a[i]>=a[i-1]){
			if(markb[i-1]!=1){
				markb[i]=1;
				optt++;
			}
		}
	}
	cout<<min(opt,optt)<<endl;
	return 0;
}
```

---

## 作者：zfhzzzzzzzzzzz (赞：0)

# 题意
给定一个序列，更改其中若干个元素，得到一个新序列。新序列中任意一个元素都要比相邻元素大或小。

# 思路
啥意思呢？即新序列有两种情况：
``` 
	 a[2]  a[4]  a[n-1]       
1.       /  \  /  \.../  \  
      a[1]  a[3]         a[n]  
 
      a[1]  a[3]         a[n]  
2.       \  /  \  /...\  /
         a[2]  a[4]  a[n-1]



```

我们只需要分类讨论，然后比较两种情况修改次数即可。

# Code

```
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[5000006]；
int cnt1,cnt2;//记录两种情况修改次数
bool fl[5000006];//判断是否被遍历过，不然可能重复
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=2;i<=n;i++){//情况1
			if(i%2==0&&a[i]<=a[i-1]&&!fl[i-1]){
				cnt1++;
				fl[i]=1;
			}
			if(i%2==1&&a[i]>=a[i-1]&&!fl[i-1]){
				cnt1++;
				fl[i]=1;
			}
		}
		memset(fl,0,sizeof fl);//注意清零
		for(int i=2;i<=n;i++){//情况2
			if(i%2==0&&a[i]>=a[i-1]&&!fl[i-1]){
				cnt2++;
				fl[i]=1;
			}
			if(i%2==1&&a[i]<=a[i-1]&&!fl[i-1]){
				cnt2++;
				fl[i]=1;
			}
		}
	cout<<min(cnt1,cnt2);//比较结果
}


```
 _The end_

---

## 作者：danb123 (赞：0)

一道思路非常清晰的题目。问我们最少该多少次数据中的元素才能使整个序列变成鹡鸰鸟鸣的音高序列。

## 解题思路

像扫雷游戏一样，只要确定了第一个数字为高音还是低音，后面的只需遍历一遍就可以了。像这样：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,a[1000001],cnt1,cnt2,flag;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	flag=1;
	if(a[1]<=a[2]) cnt1++;
	for(int i=2;i<=n;i++){
		if(i%2==1&&a[i]<=a[i-1]) cnt1++;
	}
	if(a[1]>=a[2]) cnt2++;
	for(int i=3;i<=n;i++){
		if(i%2==0&&a[i]<=a[i-1]) cnt2++;
	}
	cout<<min(cnt1,cnt2);
}
```
然后得到了一半的分，为什么呢？

假如说遍历到一个数了，可是它前面得数改了，那检测到不对了又要加一次。所以，我们要加一个标记变量来标记前一个数是否修改过，如果是就跳过这个数。

### 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000001];
int suan(int x) {
	int cnt=0,flag=0;
	if(x) {
		for(int i=2; i<=n; i++)
			if(i%2==0) a[i-1]<=a[i]&&flag==0?flag=1,cnt++:flag=0;
			else a[i-1]>=a[i]&&flag==0?flag=1,cnt++:flag=0;
		return cnt;
	} else{
		for(int i=2; i<=n; i++)
			if(i%2==1) a[i-1]<=a[i]&&flag==0?flag=1,cnt++:flag=0;
			else a[i-1]>=a[i]&&flag==0?flag=1,cnt++:flag=0;
		return cnt;
	}
}
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	cout<<min(suan(1),suan(0));
}
```




---

## 作者：Contain_Thunder (赞：0)

### 题目
[P9253 [PA 2022] Ornitolog 2](https://www.luogu.com.cn/problem/P9253)
### 题目描述
给你一个长度为 $n$ 的数列，求至少要修改多少个数才能让数列成为交替鹡鸰鸟鸣的音高序列。
### 思路
这道题有两种情况。

- 第一种是当前的数比左右两边的数都要小。
- 还有一种是当前的数比左右两边的数都要大。
```
 1     1	   1
  \   /		 /   \
    0		0     0
```
所以我们用两个循环依次判断 $n$ 为奇数和偶数的情况，每次比较当前数字左右两边的数字的大小就行了。
### code
```
#include<bits/stdc++.h>
using namespace std;
int n,a[50005],b[50005];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>b[i];
    memcpy(a,b,sizeof(a));
    int cnt=0;
    for(int i=2;i<=n;i++)
        if(i%2==1){if(a[i-1]<=a[i]) a[i]=-1000009,cnt++;}
        	else if(a[i-1]>=a[i]) a[i]=INT_MAX,cnt++;
    memcpy(a,b,sizeof(a));
    int cnt1=0;
    for(int i=2;i<=n;i++)
        if(i%2==0){if(a[i-1]<=a[i]) a[i]=-1000009,cnt1++;}
        	else if(a[i-1]>=a[i]) a[i]=INT_MAX,cnt1++;
    cout<<min(cnt,cnt1)<<endl;
    return 0;
}
```



---

## 作者：Ag77 (赞：0)

# 分析
因为数据范围不大 $3≤n≤5×10^{4}$，所以可以直接模拟。

一共需要考虑两种情况：

第一种：声音先升高再下降。

第二种：声音先下降再升高。

所以进行两遍循环，分别模拟这两种情况，每次遇到不符合规律的点就增加需要改变的数量。并且将当前的声音改成一个“极大”或“极小”值。

用一个布尔类型的变量来记录当前应该上升还是下降。

## 注意
因为 $-10^{6}≤a_{i} ≤10^{6}$，所以“极大”值要大于 $10^{6}$，“极小”值要小于 $-10^{6}$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10;
const int MIN=-1e6-1;
const int MAX=1e6+1; 
int a[N],b[N];
int sum1,sum2;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=a[i];
	}
	bool op=1;//第一种情况 
	for(int i=2;i<=n;i++){
		if(op==1){
			if(b[i-1]<b[i]){
				op=0;
			}else{
				b[i]=MAX;
				op=0;
				sum1++;				
			}
		}else{
			if(b[i-1]>b[i]){
				op=1;
			}else{
				b[i]=MIN;
				op=1;
				sum1++;
			}
		}
	}
	op=0;//第二种情况 
	for(int i=2;i<=n;i++){
		if(op==1){
			if(a[i-1]<a[i]){
				op=0;
			}else{
				a[i]=MAX;
				op=0;
				sum2++;				
			}
		}else{
			if(a[i-1]>a[i]){
				op=1;
			}else{
				a[i]=MIN;
				op=1;
				sum2++;
			}
		}
	}
	cout<<min(sum1,sum2);
	return 0;
}
```


---

## 作者：hycqwq (赞：0)

## Problem

给定一个序列，问最少要改几个数才能使该序列变为一大一小交错的"波浪形"。

## Conditions

"波浪形"有两种可能：

### Condition 1

```text
1   3   5
 \ / \ /  ...
  2   4
```

即：第一个数是大数。

那么如果发现了一个不符合规律的数，如果应该是大数则设为 $+\infty$，否则（即应该是小数时）则设为 $-\infty$。

### Condition 2

 ```text
  2   4
 / \ / \  ...
1   3   5
```

即，第一个数是小数。

处理方法与另一种情况类似。

## Solution

对这两种情况分别进行遍历更改统计即可。

另外有一个小技巧：因为两种情况正好相反，所以可以用一个布尔值来表示现在模拟的情况。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
#define elif else if
#define il inline

int n, a[50005], b[50005];

int slv(bool f)
{
    memcpy(a, b, sizeof(a));
    int cnt = 0;
    for (int i = 2; i <= n; i++)
        if (i % 2 == f)
        {
            if (a[i - 1] <= a[i])
                a[i] = -inf, cnt++;
        }
        else
        {
            if (a[i - 1] >= a[i])
                a[i] = inf, cnt++;
        }
    return cnt;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    cout << min(slv(true), slv(false)) << endl;
    return 0;
}
```

---

## 作者：a18981826590 (赞：0)

# [P9253 [PA 2022] Ornitolog 2](https://www.luogu.com.cn/problem/P9253)
## 题意简述
这道题其实很简单，其实就是求把给定序列转成目标序列的最少步数。
## 解题思路
分为两种情况：

1. 声高先高再低；
2. 声高先低再高。

分析完后就直接模拟，取这两种情况的最小值即可。
## 解题方法
设置两个计数器，初始为 $0$；一个判断器，初始为 $0$。

从头到尾扫过去，遇到不合格的音高且判断器为 $0$ 计数器就 $+1$，为了让它的下一个不被重复计算（因为可以随意更改当前这个数，所以下一个肯定是合格的），要把判断器定为 $1$；否则判断器定为 $0$。

最后取这两个计数器的最小值。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[50010],n,x,y;
bool z;
int main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=1;i<n;i++){
		if(i%2==0){
			if(a[i]<=a[i-1]&&!z){
				x++;
				z=1;
			}
			else z=0;
		}
		else{
			if(a[i]>=a[i-1]&&!z){
				x++;
				z=1;
			}
			else z=0;
		}
	}
	z=0;
	for(int i=1;i<n;i++){
		if(i%2==0){
			if(a[i]>=a[i-1]&&!z){
				y++;
				z=1;
			}
			else z=0;
		}
		else{
			if(a[i]<=a[i-1]&&!z){
				y++;
				z=1;
			}
			else z=0;
		}
	}
	cout<<min(x,y);
	return 0;
}
```

---

