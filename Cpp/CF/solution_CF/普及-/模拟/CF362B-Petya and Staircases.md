# Petya and Staircases

## 题目描述

有很多级台阶，皮特想走过他们，有的台阶很脏，所以他不想踏上去。他一次可以跨过 **1 或 2 级** 台阶，也可以只走到上一级，而不跨过台阶。现在他在第一级台阶，他要到第 $n$ 级台阶上，问是否能在不踏上脏台阶的情况下做到。

注意：皮特一定会踏上第一个和最后一个台阶，所以如果第一个或最后一个台阶是脏的，那么皮特一定会踏上脏台阶。

## 样例 #1

### 输入

```
10 5
2 4 8 3 6
```

### 输出

```
NO```

## 样例 #2

### 输入

```
10 5
2 4 5 7 9
```

### 输出

```
YES```

# 题解

## 作者：what_else (赞：1)

这是一道简单的贪心。

如果要保证不会踩到脏台阶，那么就要使连续的脏台阶个数不能超过 $2$，因为最多只能跨过 $2$ 级的台阶，而在其他的情况下，脏台阶可以一脚跨过去，所以这里的 $n$ 是无用的，我们只需考虑脏台阶的位置。

具体解释见代码

```
#include<bits/stdc++.h>//万能头
using namespace std;
int s[3001],n,m,i;//s储存脏台阶的位置
int main(){
    cin>>n>>m;
    for(i=1;i<=m;i++)
    cin>>s[i];
    sort(s+1,s+m+1);//将脏台阶位置排序
    if(s[1]==1 || s[m]==n){//特判，如果就在脚底下或终点，就直接输出NO
        cout<<"NO";
        return 0;
    }
    for(i=1;i<=m;i++){
        if((s[i]+1)==(s[i+1]) && (s[i+1]+1)==(s[i+2])){
            cout<<"NO";break;
        }//判定，若有连续的三个脏台阶，就输出NO
    }
    if(i==m+1)
    cout<<"YES";//若没找到连续的三个脏台阶，说明不会踏上脏台阶了
}
```

---

## 作者：xu222ux (赞：1)

# [Petya and Staircases](https://www.luogu.com.cn/problem/CF362B)

此题很简单，只需要判断两种情况，开头和结尾是脏的和连续3个以上是脏的。只要符合任意一个就输出 `no`。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[3005];
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a[i];
        if(a[i]==1||a[i]==n)
            return cout<<"NO",0;
    } 
    sort(a+1,a+m+1);
    for(int i=1;i<=m;i++)
        if(a[i]+1==a[i+1]&&a[i]+2==a[i+2])
            return cout<<"NO",0;
    cout<<"YES";
    return 0;
}
```

---

## 作者：708151_qwq (赞：1)

[题面传送门](https://www.luogu.com.cn/problem/CF362B)

# 题意简述

有很多级台阶，皮特想走过他们，有的台阶很脏，所以他不想踏上去。

他一次可以跨过 $1$ 或 $2$ 级台阶，也可以只走到上一级，而不跨过台阶。

现在他在第一级台阶，他要到第 $n$ 级台阶上，问是否能在不踏上脏台阶的情况下做到。

注意：皮特一定会踏上第一个和最后一个台阶，所以如果第一个或最后一个台阶是脏的，那么皮特一定会踏上脏台阶。

# Solution

一道简单练手题。

这题方法很简单，只需要判断有没有三个及三个以上的连续的脏台阶，因为这样皮特就无法不踏上脏台阶。

但是这题直接枚举是不行的，因为数据太大，$1 \leq n \leq 10^9$。

所以我们就要提前排序，然后用排好序的数组来枚举判断。代码：

```cpp
if((a[i]+1)==(a[i+1])&&(a[i+1]+1)==(a[i+2])) {//判断
            printf("NO");
			return 0;
}
```

注意，这里需要特判一下，如果第一个或者最后一个台阶是脏台阶，那么直接输出 `NO`，但这里我们已经对数组排好序了，所以直接判断脏台阶数组的第一项和最后一项就行，不用挨个枚举。~~因为这样会 TLE~~

特判代码：

```cpp
if(a[0]==1||a[m]==n-1) {//特判 
		printf("NO");
		return 0;
}
```

# AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m, a[3005];
	scanf("%d%d", &n, &m);
	for(int i=0; i<m; i++) scanf("%d", &a[i]);
	sort(a, a+m);//排序，为后面的判断做准备 
	if(a[0]==1||a[m]==n-1) {//特判 
		printf("NO");
		return 0;
	}
	for(int i=0; i<m; i++) {
        if((a[i]+1)==(a[i+1])&&(a[i+1]+1)==(a[i+2])) {//判断
            printf("NO");
			return 0;
        }
    }
    printf("YES");//如果没有输出 NO，输出 YES 
	return 0;
}//虽然和上一篇题解的代码有点像，但是是自己写的 QwQ 
```

By 2022.7.2 蒟蒻的第二十篇题解

---

## 作者：huangzhixia (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/CF362B)**

### 题意

现在有 $n$ 个台阶，其中有 $m$ 个台阶是脏的，Petya 想要走到第 $n$ 个台阶去。并且 Petya 一次可以走 $1$ 阶，也可以走 $2$ 阶。问 Petya 能不能不踩到脏的台阶走到第 $n$ 个台阶， 能输出 ```YES```，否则输出 ```NO```。

### 思路

有以下几种情况：

- Petya 最开是就在第一个台阶，所以如果第一个台阶是脏的，那就肯定不能了。

- 第 $n$ 个台阶是脏的。而 Petya 的目标就是走到第 $n$ 个台阶， 第 $n$ 个台阶又是脏的，也不能。

- 有连续的 $2$ 个脏台阶及以上的脏台阶在一起，Petya 又只能走 $1$ 步或 $2$ 步，那么也肯定不行了。

- 剩下的情况 Petya 就可以到达第 $n$ 个台阶。

我们把以上的情况判断一下，然后输出对应的 ```YES``` 和 ```NO``` 就行啦！

### Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, a[3001];

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
		if (a[i] == 1 || a[i] == n) {
        	puts("NO");
		    return 0;
        }
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; i++)
        if (a[i] + 1 == a[i + 1] && a[i] + 2 == a[i + 2]) {
        	puts("NO");
        	return 0;
		}
    puts("YES");
}
```


---

## 作者：_int123_ (赞：0)

题目：

## Petya and Staircases

### 题意：

有很多级台阶，皮特想走过他们，有的台阶很脏，所以他不想踏上去。他一次可以跨过 $1$ 或 $2$ 级台阶，也可以只走到上一级，而不跨过台阶。现在他在第一级台阶，他要到第 $n$ 级台阶上，问是否能在不踏上脏台阶的情况下做到。

注意：皮特一定会踏上第一个和最后一个台阶，所以如果第一个或最后一个台阶是脏的，那么皮特一定会踏上脏台阶。


#### 输入格式：

第一行两个整数 $n$ 和 $m$，表示有 $n$ 级台阶，和 $m$ 级脏的台阶，接下来是 $m$ 级脏台阶的编号。

#### 输出格式：

如果皮特在不踏上脏台阶的情况下也能到第 $n$ 级台阶上，输出 ``YES``。

否则输出 ``NO``。

$( 1<=n<=10^{9},0<=m<=3000 ) $

### 思路：

1. 由于输出的是无序的，我们可以考虑先对它排序。

2. 因为皮特一定会踏上第一个和最后一个台阶，所以如果第一个或最后一个台阶是脏的，那么皮特一定会踏上脏台阶，直接特判输出。

3. 如果排序后存在连续 $3$ 级台阶都脏了，显然就不行了，判到了就直接输出并结束。

4. 如果都没判到，就满足条件。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int n,m;
int a[3005];//记录脏的台阶 
int main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	cin>>n>>m;//输入 
	for(int i=1;i<=m;i++) cin>>a[i];//输入 
	sort(a+1,a+m+1);//排序 
	if(a[m]==n||a[1]==1)//特判 
	{
		cout<<"NO";
		return 0;
	}
	for(int i=1;i<=m-2;i++)
		if(a[i]+1==a[i+1]&&a[i+2]==a[i+1]+1)//如果连着 3 级台阶都脏，直接结束 
		{
			cout<<"NO";
			return 0;
		}
	cout<<"YES";//没结束即可行 
	return 0;
}
```

完结撒花！！！

---

## 作者：Eazin_star (赞：0)

### 思路
当有连续三级台阶都是脏的时，皮特一定会踏上脏的台阶。所以只用开个 $a$ 数组，把脏的台阶存起来，排序之后查看是否有连续三个台阶都是脏的。
### AC code
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[3005];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	sort(a+1, a+m+1);
	if (a[1] == 1 || a[m] == n) {
		printf("NO\n");
		return 0;
	}
	for (int i = 3; i <= m; i++) {
		if (a[i] == a[i-1]+1 && a[i-2]+1 == a[i-1]) {
			printf("NO\n");
			return 0;
		}
	}
	printf("YES\n");
	return 0;
}
```



---

## 作者：ys_kylin__ (赞：0)

建议评红。

## 题目大意
你可以走一级台阶、两级或三级，有 $n$ 级台阶，$m$ 级是脏的，再给出脏的台阶（无序），问能否不踩脏到达第 $n$ 级。

## 思路
题目说明了，当第一级与最后一级脏时，无解，这个特判就好了。然后需要排序脏台阶，sort 就行了。不难发现，当连续脏台阶超 $3$ 级时，绝对跳不过去，剩下都可以跳过。

然后就做完了。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10005];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) {
		scanf("%d",&a[i]);
		if(a[i]==1 || a[i]==n) printf("NO"),exit(0);//如果第一级或第 n 级是脏的，必定登不上去。 
	}
	sort(a+1,a+m+1);//排序 
	for(int i=1;i<m-1;i++) {
		if(a[i]+1==a[i+1] && a[i]+2==a[i+2]) printf("NO"),exit(0);//三个连续脏台阶也不行。 
	}
	printf("YES");//可以 
	return 0;
}

```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF362B)

此题建议评红。

题目大意：有 $n$ 级台阶，从第一级开始每次可以走 $1 \sim 3$ 格，其中有 $m$ 级台阶是脏的不能踩，问能不能到达台阶最顶部。

不难发现，如果出现了连续三级脏台阶，就不能走上去了。

所以给数组排序后寻找有没有连续的三级脏台阶就行了。

记住要特判第一和最后一级台阶是不是脏的。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[3001];
int main(){
	cin >> n >> m;
	for (int i = 1; i <= m; i++){
		cin >> a[i];
		if (a[i] == 1 || a[i] == n){cout << "NO"; return 0;}
	}
	sort(a + 1, a + m + 1);
	for (int i = 2; i < m; i++)
		if (a[i - 1] + 1 == a[i] && a[i] + 1 == a[i + 1]){cout << "NO"; return 0;}
	cout << "YES";
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目描述

[Petya and Staircases](https://www.luogu.com.cn/problem/CF362B)

## 算法思路

可以想到如果有三个的连续的脏台阶，Petya 一定会踏上脏台阶。

所以只要判断是否有三个的连续的脏台阶就可以了。

#### 注意

要特判第一个和最后一个台阶，因为第一个和最后一个台阶如果是脏的，那么 Petya 一定会踏上脏台阶。

### 样例讲解

样例画成图后（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/u0zs6ist.png)

如果我们走一个台阶（如下图），Petya 会踏上脏台阶。

![](https://cdn.luogu.com.cn/upload/image_hosting/u7a5jyu1.png)

如果我们走两个台阶（如下图），Petya 还是会踏上脏台阶。

![](https://cdn.luogu.com.cn/upload/image_hosting/i76arum0.png)

如果我们走三个台阶（如下图），Petya 依旧会踏上脏台阶。

![](https://cdn.luogu.com.cn/upload/image_hosting/2j78241x.png)

所以 Petya 一定会踏上脏台阶。

时间复杂度：$O(m)$。

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
const ll N=3010;
ll n,m,a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		cin>>a[i];
	}
	sort(a,a+m);//排序 
	if(a[0]==1||a[m]==n-1)//如果第一个或最后一个台阶是脏的
	{
		cout<<"NO\n";//Petya一定会踏上脏台阶
		return 0;
	}
	for(int i=0;i<m;i++)
	{
		if((a[i]+1)==(a[i+1])&&(a[i+1]+1)==(a[i+2]))//如果有三个的连续的脏台阶
		{
			cout<<"NO\n";//Petya一定会踏上脏台阶
			return 0;
		}
	}
	cout<<"YES\n";//可以不踏上脏台阶
	return 0;
}
```


---

## 作者：_lzy_ (赞：0)

## 题目大意：
首先题目会给出台阶数与脏的台阶的阶数，也就是 $n$ 和 $m$，要我们判断能不能不走脏的台阶就可以到达第 $n$ 级台阶。
## 思路：
思路一：暴力

将 $1$ 到 $n$ 暴力枚举一遍，看有没有连着三级台阶都是脏的，如果有那么输出 NO，循环完还没找到就输出 YES。

但是我们会发现一个问题： $n \leq 10^9$，就很可能会导致我们超时。

思路二：

我们从思路一中其实可以得到一点想法，那就是既然我们只需要判断三级相连的脏台阶，那为何我们不直接去从给出的 $m$ 级脏台阶里找呢？

所以我们可以先排序，后面再去判断是否有三级台阶连在了一起。
## 代码实现：
```cpp
#include<bits/stdc++.h>
#define N 30005
using namespace std;
int n,m;
int a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	bool flag=true;
	for(int i=1;i<=m;i++)cin>>a[i];
 	sort(a+1,a+m+1);
	if(a[1]==1||a[m]==n)flag=false;
	for(int i=1;i<=m;i++)
		if((a[i]+1)==a[i+1]&&(a[i+1]+1)==a[i+2]){
			flag=false;
			break;
		}
	if(flag)puts("YES");
	else puts("NO");
    return 0;
}

```


---

## 作者：szhqwq (赞：0)

## 分析

将序列从大到小排序，然后特判第一阶梯子和第 $n$ 阶梯子是否为脏的，接下来就遍历序列判断有无连续 $3$ 个阶梯都是脏的即可。

AC code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 3e3 + 10;

int n,m;
int a[N];

signed main() {
	ios :: sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; i ++ ) cin >> a[i];
	sort(a + 1,a + m + 1);
	if (a[1] == 1 || a[m] == n) { puts("NO"); return 0; }
	for (int i = 1; i <= m; i ++ )
		if (a[i] == a[i + 1] - 1 && a[i + 1] == a[i + 2] - 1) {
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}
```

---

## 作者：Slient_QwQ (赞：0)

[更好的体验](https://www.cnblogs.com/Manipula/p/17774470.html)

## 分析
简单排序题。

首先 Petya 可以通过跨过一个台阶和两个台阶保证不经过脏台阶，但是不可以通过跨过三个台阶来保证不经过脏台阶，所以只要看有没有连续的三个脏台阶即可。

同时，如果第一个台阶和最后一个台阶至少一个是脏台阶那么就不可以达成。

## Accepted Code
```cpp
/*Code By Manipula*/
#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
int high[N], n, m, last = -1, sum = 1;
int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)cin >> high[i];
	sort(high + 1, high + m + 1);
	if (high[1] == 1 || high[m] == n)return cout << "NO", 0;//特判
	for (int i = 1; i <= m; i++)
	{
		if (high[i] != last + 1)sum = 1;
		else if (++sum == 3)return cout << "NO", 0;
		last = high[i];//更新上一个台阶高度
	}
	cout << "YES";
	return 0;
}
```
最后，这道题建议评橙。

---

## 作者：Acheron_RBM (赞：0)

题面意思很简单，只需要判断是否有连续三级的脏台阶即可。

但是直接暴力会超时，所以，我们要提前排序数组。

接下来就很简单了，只需特判一下第一个台阶和最后一个台阶是否是脏台阶即可。

```cpp
int a[4000];
int main()
{
	int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
    	cin>>a[i];
	}
    sort(a+1,a+m+1);
    for(int i=1;i<=m;i++)
    {
    	if(a[i]+1==a[i+1]&&a[i+1]+1==a[i+2])//是否有连续的三个台阶 
    	{
    		cout<<"NO";
			return 0;
		}
	}
	if(a[1]==1||a[m]==n)//特判 
    {
		cout<<"NO";
    	return 0;
	}
    cout<<"YES";
    return 0;
}
```

---

