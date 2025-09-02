# [USACO21JAN] Even More Odd Photos B

## 题目描述

Farmer John 正再一次尝试给他的 $N$ 头奶牛拍照（$2\le N\le 1000$）。

每头奶牛有一个范围在 $1\ldots 100$ 之内的整数的「品种编号」。Farmer John 对他的照片有一个十分古怪的构思：他希望将所有的奶牛分为不相交的若干组（换句话说，将每头奶牛分到恰好一组中）并将这些组排成一行，使得第一组的奶牛的品种编号之和为偶数，第二组的编号之和为奇数，以此类推，奇偶交替。

Farmer John 可以分成的最大组数是多少？ 

## 说明/提示

### 样例解释 1

在这个样例中，以下是一种分成最大组数三组的方案。将 1 和 3 分在第一组，5、7 和 9 分在第二组，11 和 13 分在第三组。 

### 样例解释 2

在这个样例中，以下是一种分成最大组数五组的方案。将 2 分在第一组，11 分在第二组，13 和 1 分在第三组，15 分在第四组，17 和 3 分在第五组。 

## 样例 #1

### 输入

```
7
1 3 5 7 9 11 13```

### 输出

```
3```

## 样例 #2

### 输入

```
7
11 2 17 13 1 15 3```

### 输出

```
5```

# 题解

## 作者：xyx404 (赞：10)

### [题目](https://www.luogu.com.cn/problem/P9941)
### 思路：

因为题中给出要使**奇数组的编号之和为偶数偶数组的编号之和为奇数**。

所以我们只需要**知道编号的奇偶性**。

所以我们可以先统计出奇数和偶数各有多少个。

然后会出现两种情况：奇数多，偶数多。

因为小学学过：奇数加奇数等于偶数，偶数加偶数等于偶数，奇数加偶数等于奇数。

所以可以得出解决方案：

1. 奇数多时，将两个奇数相加变成偶数，减少奇数的数量，增加偶数的数量。
2. 偶数多时，将偶数和奇数相加变成奇数，减少偶数的数量，增加奇数的数量。

### 代码

```cpp
#include <bits/stdc++.h> // 头文件
using namespace std;
bool jo (int x) { // 判断是奇数还是偶数函数
	if ( x % 2 == 0) return 1; // 是偶数返回真
	return 0; // 不是就返回假
}
int main() { // 主函数
	int n , j = 0 , k = 0; // j 为偶数的数量 k 为奇数的数量
	cin >> n; // 输入 n
	int a[n];
	for(int i = 0; i < n; i++){
		cin >> a[i]; // 输入
	}
	for(int i = 0; i < n ; i++){ // 判断奇数还是偶数
		if (jo(a[i])) j++; // 是偶数 j++
		else k++; // 不是偶数 k++
	}
	while(k > j){ // 第一种情况奇数多
		k -= 2; // 两个奇数相加等于偶数所以奇数每次减 2
		j++; // 偶数加 1
	}
	if(j > k+1) j=k+1; // 第二种情况偶数多
	cout << k+j; // 输出答案
  	return 0; // 好习惯
}
```



---

## 作者：scp020 (赞：9)

# P9941 [USACO21JAN] Even More Odd Photos B 题解

看到这么简单的题，题解区竟然千篇一律，没什么别的做法，并且代码如此相似，我感到万分的悲伤，于是来写个不一样的题解。

## 解法

我们可以贪心地分组。在此之前，我们需要达成共识：

- 尽量不让奶牛分到一组。
- 根据奇数加奇数等于偶数、偶数加偶数等于偶数、奇数加偶数等于奇数可以看出，通过合并两个组的操作不会使奇数组的数量增多。
- 偶数组的数量要么比奇数组的数量多一个，要么相等。

现在我们可以开始正文了。

考虑我们将品种编号为奇数和偶数的奶牛分开，然后一对一对（一个偶数跟着一个奇数）地加入到答案中，直到有一种奶牛没有了才停止。分情况讨论：

- 如果此时两种奶牛都没有了，那就直接输出答案（即组数的两倍）。
- 如果此时只剩下了偶数奶牛，因为一个数加偶数后奇偶性不变，所以我们可以将其中一个偶数奶牛加到答案末尾（因为原来答案末尾是奇数奶牛，所以可以加），并将其余偶数奶牛加到任意组里即可。
- 如果此时只剩下了奇数奶牛，因为两个奇数相加可以产生一个偶数，所以我们将每 $3$ 个奇数奶牛放在一对考虑，每对奶牛中前两个分为偶数组，最后一个分为奇数组，这样每 $3$ 个奇数奶牛就可以产生 $2$ 组贡献。考虑这样一组一组加还可能会剩下 $0,1,2$ 个奇数奶牛。如果剩下 $0$ 个（即没有剩余），则答案刚刚好，不用改动。如果剩下 $1$ 个，因为现在答案末尾是奇数组奶牛，而一个数加奇数后会改变奇偶性，所以只能将剩下的奇数奶牛和答案末尾的奇数组奶牛打包扔到前面任意组里，所以答案应减 $1$。如果剩下 $2$ 个，那就将这两个奶牛打包加到答案末尾，答案加 $1$。

剩下的就是代码了，超级简单，建议题目评红。

## 代码

```cpp
#include<bits/stdc++.h>
int n,odd,even,gap;
int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++) scanf("%d",&x),odd+=x&1;
	even=n-odd;
	if(odd==even) printf("%d",odd*2);
	else if(odd<even) printf("%d",odd*2+1);
	else
	{
		gap=odd-even;
		if(gap%3==0) printf("%d",even*2+gap/3*2);
		else if(gap%3==1) printf("%d",even*2+gap/3*2-1);
		else printf("%d",even*2+gap/3*2+1);
	}
	return 0;
}
```

---

## 作者：zzhbpyy (赞：4)

## [原题传送门](https://www.luogu.com.cn/problem/P9941)
该题很有思维性，通过**奇数和偶数**的特性解题，一遍 Accept。

首先明确以下三点公理：

1. 奇+奇=偶

2. 奇+偶=奇

3. 偶+偶=偶（本题用不到）

对输入的奇数和偶数进行统计讨论：

1. 当奇数多于偶数个数，不断将两个奇数合成（或者说分到同一组）一个偶数；

2. 偶数多于奇数时可将奇偶合成一奇。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1005];
int k,l;//k表示奇数个数，l表示偶数个数
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];//输入直接统计处理
		if(a[i]%2==0)l++;
		else k++;
	}
	while(k>l){
		k-=2;
		l++;
	}
   if(l>k+1)//偶数多直接赋值即可
		l=k+1;
	cout<<l+k;
}
```


---

## 作者：lutaoquan2012 (赞：3)

### [传送门](https://www.luogu.com.cn/problem/P9941)

## 思路：
假设偶数有 $cnt1$ 个，奇数有 $cnt2$ 个。

- 如果 $cnt1=cnt2$ 或者 $cnt1=cnt2+1$，显然可以把每个元素单独放在一个组里面，答案就是 $n$。
- 如果 $cnt1>cnt2+1$，说明偶数太多了，所以我们可以拿一个偶数和一个奇数进行分组。这样就有 $2 \times cnt2$ 组，剩下来的所有数都在一个组，所以答案就是 $2\times cnt2 + 1$。
- 如果 $cnt1<cnt2$，说明奇数太多了，所以我们可以那两个奇数变成一个偶数，相当于少了两个奇数，多了一个偶数。我们重复这个操作，直到 $cnt1\ge cnt2$。问题也就成为了上面的问题。

## 代码：
```cpp
//
// Created by 55062 on 2023/12/29.
//
#include<bits/stdc++.h>

using namespace std;
typedef long ll;
ll n, x, cnt1, cnt2;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        if (x % 2 == 0) cnt1++;//偶数的数量
        else cnt2++;//奇数的数量
    }
    while (cnt2 > cnt1) {//两个奇数变成一个偶数
        cnt2 -= 2;
        cnt1++;
    }
    if (cnt1 > cnt2 + 1) cnt1 = cnt2 + 1;
    cout << cnt1 + cnt2;
    return 0;
}
```

---

## 作者：Tachibana27 (赞：2)

### [传送门](https://www.luogu.com.cn/problem/P9941)

## 思路：
不难发现这道题我们希望能够让奇数和和偶数尽量的差不多。

根据：
1. 奇+奇=偶

2. 奇+偶=奇

如果奇数多，那么用奇+奇=偶来把两个奇数合成一个偶数。

如果偶数多，那么按照奇+偶=奇可以抵消一个偶数。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long ll;
ll n,x,ou,ji;
int main() {
    cin >> n;
    for (int i=1;i<=n;i++){
        cin>>x;
      	//统计一开始奇数和偶数的数量
        if(x%2==0) ou++;
        else ji++;
    }
    while(cnt2>cnt1) {//合并偶数
        ji-=2;
        ou++;
    }
    if (ou>ji+1){
      ou=ji+1;
    }
    cout<<ou+ji;
    return 0;//撒花
}
```

---

## 作者：wwxxbb (赞：1)

## [题目](https://www.luogu.com.cn/problem/P9941)


## 思路：
首先明确题意，要使奇数组的编号之和为偶数偶数组的编号之和为奇数，所以先要统计输入的数据当中奇数和偶数有多少；但是会出现奇数多或者偶数多的情况，所以就要运用小学知识：

* 奇+奇=偶

* 奇+偶=奇

当奇数多的时候，将两个奇数相加变成偶数；

偶数多的时候，将奇数和偶数相加变成奇数。

## Std：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010],j,o,n;//j表示奇数的数量，o表示偶数的数量
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]%2)j++;//先判断
        else o++;
    }
    while(j>o){//奇数多
        j-=2;
        o++;
    }
    if(o>j+1)o=j+1;//偶数多
    cout<<j+o;
    return 0;
}
```
### end

---

## 作者：Igunareo (赞：1)

# [原题传送门](https://www.luogu.com.cn/problem/P9941)
## 思路
题目只有奇偶性有关，所以不必考虑其他信息。

地球人都知道：

二奇等于一偶，偶数加不出奇数，偶数加奇数等于奇数。

同时，题目要求最多组，也就是每组最少。

即调用奇数只用一个，调用偶数有则一偶，无则二奇。

### 注意
如果调用奇数时只剩一个偶数咋办？

首先，不能摆队尾。

其次，偶加奇等于奇，会破坏原有奇偶性。

还有，奇加奇等于偶，也不能加。

只好很悲催的少拍一张了。

啊，你说万一只有一头奇数奶牛，还没拍过照咋办？

别担心，出题人早想好了，$2\le N\le1000$，不用打特判了，耶！
## 代码来喽
```
#include<bits/stdc++.h>
using namespace std;
int n,a,ji[3];//ji:奇偶数组 
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a;
    	ji[a%2]++;//计入奇偶性 
	}
	for(int i=0;;i++){
		if(ji[i%2]>0)ji[i%2]--;//有符合的最好了 
		else{
			if(i%2==0&&ji[1]>=2)ji[1]-=2;//没有偶数两个奇数来凑 
			else if(i%2==0&&ji[1]==1){//只剩一个奇数了qwq 
				cout<<i-1;//少拍一张吧 
				return 0;
			}
			else{//其他就别烦了（剩偶数加哪都行，不剩最好） 
				cout<<i;
				return 0;
			}
		}
	}
    return 0;//二十五行挺短，不压行了 
}
```


---

## 作者：OIerWu_829 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P9941)

## 思路

先统计出奇数个数 $odd$ 和偶数个数 $even$。

然后对于不符合最终情况的方案分类处理：

+ 奇数多时，可将**两个奇数相加变成偶数**，从而减少奇数，增加偶数，直到奇数个数 $\le$ 偶数个数为止。
+ 偶数多时，可将**一个偶数和一个奇数相加变成奇数**，从而减少偶数，直到偶数个数 $=$ 奇数个数 $+1$ 为止。

```cpp
#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int even = 0, odd = 0;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		if (x % 2 == 0) even++; // 偶数
		else odd++; // 奇数
	}
	while (odd > even) { // 第一种情况
		odd -= 2;
		even++;
	}
	if (even > odd + 1) // 第二种情况
        even = odd + 1;
	cout << odd + even << endl;
	return 0;
}
```


---

## 作者：LegendaryGrandmaster (赞：0)

先统计一共有多少个奇数和偶数。

* 奇数+奇数=偶数
* 奇数+偶数=奇数

-------------------

1. 奇数比偶数多或等于时：两个奇数相加变为偶数，可使得奇偶交替，组数则为奇偶相加。

2. 奇数比偶数少时：因为偶数和偶数凑不出奇数，所以每个偶数与奇数对应，最后一组为剩余偶数全部相加。总组数为奇数数量的两倍加一。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[2];
int main()
{
    int n;
    cin>>n;
    for(int i=1,x;i<=n;i++)cin>>x,f[x&1]++;
    while(f[1]>f[0])f[1]-=2,f[0]++;
    cout<<(f[0]>f[1]?2*f[1]+1:f[0]+f[1]);
}
```

---

## 作者：_little_Cabbage_ (赞：0)

# P9941 [USACO21JAN] Even More Odd Photos B 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-p9941)~~

这是一道思维题。

我们可以发现，如果奇数多，可以将两个奇数相加变成偶数，所以在奇数多的情况下，我们需要把奇数的数量一直 $-2$，然后一直给偶数的数量 $+1$。

否则，如果偶数多，那么可以将一个偶数与一个奇数相加，也就是说，强行将偶数的数量设为奇数 $+1$。

AC 代码
```cpp
#include<bits/stdc++.h>
#define jiou a[i]%2==1
#define jibiouda ji>ou
#define oubijida ou>ji+1
using namespace std;
int a[1010];
int ji,ou;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(jiou)
		{
			ji++;
		}
		else
		{
			ou++;
		}
	}
	while(jibiouda)
	{
		ji-=2;
		ou++;
	}
	if(oubijida)
	{
		ou=ji+1;
	}
	printf("%d",ji+ou);
}
```
[AC 记录](https://www.luogu.com.cn/record/142459514)

---

## 作者：lqsy002 (赞：0)

## 题目大意
给 $n$ 个数字分组，并按照偶数、奇数、偶数、奇数等这样的顺序进行排列。[题目链接](https://www.luogu.com.cn/problem/P9941)。

## 解题思路
1. 能够形成题目要求的顺序只有两种情况，一种是偶数的组合比奇数多一个，一种是偶数的组合和奇数一样多。
2. 奇数可以两两结合变成偶数，但是偶数如果想变成奇数则必须结合一个奇数才可以。

## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,oushu,jishu,tmp;
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>tmp;
		if(tmp%2==1)
			jishu++;
		else 
			oushu++;
	}
	while(jishu>oushu){
		jishu-=2;
		oushu++; 
	}
	if(jishu==oushu) 
		cout<<2*oushu;
	else if(jishu+1==oushu)
		cout<<2*jishu+1;
	else 
		cout<<2*jishu+1;
	return 0;
}
```

---

## 作者：TruchyR (赞：0)

由于编号和只有奇偶的要求，所以我们也**只在意编号的奇偶性**。  
考虑我们怎么凑出奇数或偶数：
1. 和为奇数时，至少需要 $1$ 个奇数。
2. 和为偶数时，至少需要 $1$ 个偶数，或者 $2$ 个奇数。  
3. 分组后，还需要判定剩下的**奇数个数**是不是偶数。  
如果有剩的偶数，可以随意分配。

发现分组的时候，条件 $3$ 能否满足不是我们能决定的，所以我们只看条件 $1,2$：  
- 在**偶数组（和为奇数）**，分配 $1$ 个奇数。
- 在**奇数组（和为偶数）**：  
  - 如果还有偶数编号可以分配，分配 $1$ 个偶数。
  - 否则为了让组中还有奶牛，我们需要分配 $2$ 个奇数。
- 判一下**奇数个数**是否是偶数即可。

```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
using namespace std;
const int CHECK=0,FIL=0;int read();
int n,p[2],res;
signed main(){
	n=read();
	//p[0]偶数个数 p[1]奇数个数
	for(int i=1;i<=n;i++) p[read()%2]++;
	for(int i=1;i<=n;i++){
		if(i&1){
			if(p[0]) p[0]--;//还有偶数，分配1个偶数
			else p[1]-=2;   //没有偶数，分配2个奇数
		}else p[1]--;       //分配1个奇数
		if(p[1]>=0 && p[1]%2==0) res=max(res,i);//判条件3
	}
	printf("%d",res);
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```


---

## 作者：bitset_iTM (赞：0)

很不错的一道思维题，难度**很适合我这种蒟蒻**。  
### 思路：  
将这些编号中的奇数以及偶数的个数统计出来，然后开始模拟。  
模拟过程：

1. 先判断当前组别编号总和应为奇数还是偶数（见题目）
1. 若为奇数，检查还有没有剩余的编号为奇数的牛。
1. 如果有，就挑一只组成一队，剩余标号为奇数的牛的数量减一。
1. 如果没有，说明取完了。这时，如果还剩有奇数只编号为奇的牛，组数减一并输出；反之直接输出组数。**THE END.**
1. 若为偶数，检查还有没有剩余的编号为偶数的牛。
1. 如果有，就挑一只编号为偶数的牛组成一队，剩余标号为偶数的牛的数量减一。
1. 如果没有，检查是否能取两只编号为奇数的牛（奇+奇=偶）。
1. 若有，就挑两只编号为奇数的牛组成一队，剩余标号为奇数的牛的数量减二。
1. 若没有，说明取完了。这时，如果还剩有奇数只编号为奇的牛，组数减一并输出；反之直接输出组数。**THE END.**

讲的可能不太清楚，见谅！

### Code：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, p = 0, q = 0, res = 0;
    scanf("%d", &n);
    while (n-- && "love.YW" == "love.YW")
    {
        int x;
        scanf("%d", &x);
        if (x & 1) p++; //统计编号为奇数/偶数的牛的数量（见前面讲述的第1条）
        else q++;
    }
    
    for (bool i = false; ; i = !i) 
    //i为否说明该取总和偶数的牛拼为一组；反之该取总和奇数数的牛拼为一组
    {
        if (i) //奇数
        {
            if (p > 0) //见前面讲述的第2条
                p--, res++; //见前面讲述的第3条
            else //见前面讲述的第4条
            {
            	if (p % 2 != 0) res--; 
                printf("%d\n", res);
                return 0;
            }
        }
        
        else //偶数
        {
            if (q > 0) //见前面讲述的第5条&第6条
                q--, res++;
            else if (p >= 2) //见前面讲述的第7条&第8条
                p -= 2, res++;
            else //见前面讲述的第9条
            {
            	if (p % 2 != 0) res--;
                printf("%d\n", res);
                return 0;
            }
        }
    }
    return 0; //Good Job!
}
```


---

