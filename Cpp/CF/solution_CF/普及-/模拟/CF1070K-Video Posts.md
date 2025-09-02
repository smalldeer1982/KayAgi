# Video Posts

## 题目描述

Polycarp took $ n $ videos, the duration of the $ i $ -th video is $ a_i $ seconds. The videos are listed in the chronological order, i.e. the $ 1 $ -st video is the earliest, the $ 2 $ -nd video is the next, ..., the $ n $ -th video is the last.

Now Polycarp wants to publish exactly $ k $ ( $ 1 \le k \le n $ ) posts in Instabram. Each video should be a part of a single post. The posts should preserve the chronological order, it means that the first post should contain one or more of the earliest videos, the second post should contain a block (one or more videos) going next and so on. In other words, if the number of videos in the $ j $ -th post is $ s_j $ then:

- $ s_1+s_2+\dots+s_k=n $ ( $ s_i>0 $ ),
- the first post contains the videos: $ 1, 2, \dots, s_1 $ ;
- the second post contains the videos: $ s_1+1, s_1+2, \dots, s_1+s_2 $ ;
- the third post contains the videos: $ s_1+s_2+1, s_1+s_2+2, \dots, s_1+s_2+s_3 $ ;
- ...
- the $ k $ -th post contains videos: $ n-s_k+1,n-s_k+2,\dots,n $ .

Polycarp is a perfectionist, he wants the total duration of videos in each post to be the same.

Help Polycarp to find such positive integer values $ s_1, s_2, \dots, s_k $ that satisfy all the conditions above.

## 样例 #1

### 输入

```
6 3
3 3 1 4 1 6
```

### 输出

```
Yes
2 3 1 ```

## 样例 #2

### 输入

```
3 3
1 1 1
```

### 输出

```
Yes
1 1 1 ```

## 样例 #3

### 输入

```
3 3
1 1 2
```

### 输出

```
No```

## 样例 #4

### 输入

```
3 1
1 10 100
```

### 输出

```
Yes
3 ```

# 题解

## 作者：宁_缺 (赞：7)

### 类似于一个暴力模拟的做法
首先如果总和不是k的倍数就直接输出no结束

否则求出平均值，看看能不能拼出来，如果长度超了就不能，输出no，否则输出拼的结果
```cpp
#include<bits/stdc++.h>
#define N 100002
using namespace std;
int n,k,a[N],sum,s[N],now,cnt,x;
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),sum+=a[i];
	if(sum%k)puts("No"),exit(0);
	sum/=k,now=1,cnt=a[1];
	for(int i=1;i<=n;i++,now++,cnt+=a[i])
		if(cnt==sum)s[++x]=now,now=cnt=0;
		else if(cnt>sum)puts("No"),exit(0);
	puts("Yes");
	for(int i=1;i<=k;i++)printf("%d ",s[i]);
	return 0;
}
```
### 正好差不多一个月没发题解了，发一个短一点的练练

---

## 作者：vocaloid (赞：1)

模拟。先判断总和能否整除 $k$ ，不能则无解，然后从头开始累加，同时记录当前段的长度，如果刚好等于平均值即 $sum/k$ 则**记录**长度，然后把和以及长度清零，如果和大于平均值亦无解，如果最终依然有解，输出 `Yes` ，并把记录的长度输出即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005],sum,ans[100005],tot;
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	if(sum%k) return puts("No"),0;
	sum/=k;
	int now=0,cnt=0;
	for(int i=1;i<=n;i++)
	{
		now++;
		cnt+=a[i];
		if(cnt==sum)
		{
			ans[++tot]=now;
			now=cnt=0;
		}
		else if(cnt>sum) return puts("No"),0;
	}
	puts("Yes");
	for(int i=1;i<=k;i++) printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：ruruo (赞：0)

# 分析

- 对于整个序列，我们需要遍历三次：

- 第一次求出元素和 $sum$ ，如果 $sum \bmod k \ne 0$ ，显然不可能，直接输出 `No` 。

- 第二次遍历判断能否分成 $k$ 段。每次分段我们记录一个 $summ$ 记录该段元素和，如果在某次累加后 $summ > sum {\div} k$ ，显然不可能，直接输出 `No` 。

- 第三次遍历计算每段长度，与第二次类似，但还需要记录每段长度 $cnt$ ，分段时直接输出 $cnt$ 并清零即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k, a[100005], sum = 0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++){ // 第一次遍历
        cin >> a[i];
        sum += a[i];
    }
    if(sum % k != 0){
        cout << "No";
        return 0;
    }
    sum /= k;
    int summ = 0;
    for(int i = 1; i <= n; i++){ // 第二次遍历
        summ += a[i];
        if(summ > sum){
            cout << "No";
            return 0;
        }else if(summ == sum) summ = 0;
    }
    cout << "Yes\n";
    int cnt = 0;
    for(int i = 1; i <= n; i++){ // 第三次遍历
        summ += a[i];
        cnt++;
        if(summ == sum){
            cout << cnt << " ";
            cnt = 0;
            summ = 0;
        }
    }
    return 0;
}
```


---

## 作者：chlchl (赞：0)

## 题意简述
给定长度为 $n$ 的数组 $a_i$，问能否将其分为 $k$ 段，使每段的和相等。如果可以，输出每一段长度。

## Solution
这种题测完样例应该一遍就能过的。

首先，如果所有数的和不是 $k$ 的倍数，一定无解（很简单，每一段的和是 $\frac{n}{k}$（记为 $m$），不是 $k$ 的倍数必然导致有一组和太大）。

如果总和是 $k$ 的倍数，也不一定有解。例如下面这组样例就是无解的。

```
输入：
5 3
3 6 2 3 1

输出：No
```

所以，我们在探究如何分的时候，也要检查是否不合法。具体地，如果有一个位置 $i$，以 $i$ 结尾的这一段和小于 $m$，但是以 $i+1$ 位为结尾就大于 $m$，证明这一段不可能分出和为 $m$ 的段。这样的数列同样是不能分的。

刚刚的判断可以使用前缀和优化，时间复杂度是 $O(n)$ 的。

最后输出所有长度即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, k, l, now, s[N], p[N];
//now表示上一段结尾 

int main(){
	scanf("%d%d", &n, &k);
	for(int i=1;i<=n;i++)	scanf("%d", &s[i]), s[i] += s[i - 1];
	if(s[n] % k)	return printf("No\n"), 0;//压行语法，可以加很多个逗号，返回值是最后面那个 
	int m = s[n] / k;//除法是很慢的，用变量存下来可以节省几毫秒（ 
	for(int i=1;i<=n;i++){
		if(s[i] - s[now] == m)	p[++l] = i - now, now = i;//先用数组存下来，避免输出到一半发现无解 
		else if(s[i] - s[now] > m)	return printf("No\n"), 0;//不一定能整除就有解 
	}
	printf("Yes\n");
	for(int i=1;i<=l;i++)	printf("%d ", p[i]);
	return 0;
}
```


---

## 作者：j1ANGFeng (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1070K)

### 分析
首先求出总和，如果不是 $k$ 的倍数就无解。

否则求出平均值，看看能不能拼出来等于平均值，不能则无解，否则输出结果。

其他细节见代码注释。
### AC CODE
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<cmath>
#define int long long
#define N 10000001
#define inf 2147483647
#define in inline
#define re register
using namespace std;
inline long long rd(){char a=getchar();long long f=1,x=0;while(a<'0'||a>'9'){if(a=='-')f=-1;a=getchar();}while(a>='0'&&a<='9'){x=(x<<3)+(x<<1)+(long(a^48));a=getchar();}return f*x;}in void qwqqwq(long long x){if(x!=0){qwqqwq(x/10);putchar(x%10^48);}return;}inline void wt(long long x){if(x==0){putchar('0');return;}if(x<0){x=-x;putchar('-');}qwqqwq(x);return;}
int a[N],b[N],tot;
signed main(){
    int n=rd(),k=rd(),sum=0;
    for(int i=1;i<=n;++i)
      a[i]=rd(),sum+=a[i];
    if(sum%k!=0){   //是否是 k 的倍数
        puts("No");
        return 0;
    }
    int cnt=0,len=0;
    for(int i=1;i<=n;++i){
        cnt+=a[i];
        ++len;
        if(cnt==sum/k){   //能拼出平均值
            b[++tot]=len;
            len=0;
            cnt=0;
        }
        if(cnt>sum/k){   //不能拼出平均值
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    for(int i=1;i<=tot;++i){
        wt(b[i]);
        putchar(' ');
    }
    return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

## 题目大意

能否将一个长度为 $n$ 的数列分成 $k$ 段，使每段的和相等？如果能，输出每段的长度。

# 解析

### `Yes` 的情况

我们可以首先求出每段的和。我们知道，共 $k$ 段，每段的和相等，所以**每段的和就是总长度除以 $k$**。

然后，我们可以在求出每段和后，重新扫一遍原数列，累加和并记录长度。**当累加到等于每段和后，累加的长度就是答案**。

### `No` 的情况

对于 `No` 的情况，我们可以发现，有以下两种可能：

1. **每段的和不是整数，即总长度不能被 $k$ 整除**。

2. **累加长度时无法恰好等于每段和**。

对于第二种情况，需要在扫第二遍的途中判断，所以在第二遍扫完之前不能判断是 `Yes` 还是 `No`。故**不能一边扫一边输出 `Yes` 的答案**，我们需要把答案记录下来。

# $\textcolor{#52C41A}{\texttt{AC}}$ 代码

```cpp
#include<cstdio>
using namespace std; 

int n,k;
int a[100005];
int tot,ans[100005],ans_cnt=0;
//ans 记录答案 

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		tot+=a[i];		//tot 记录总和 
	}
	if(tot%k!=0)		//判断 No 的第一种情况 
	{
		printf("No\n");
		return 0;
	}
	tot/=k;				//tot 在此时变成每段的和 
	int sum=0,cnt=0;	//sum 记录当前累加和，cnt记录当前段长度 
	for(int i=1;i<=n;i++)
	{
		sum+=a[i];
		if(sum>tot)		//判断 No 的第二种情况 
		{
			printf("No\n");
			return 0;
		}
		cnt++;
		if(sum==tot)
		{
			ans[++ans_cnt]=cnt;	//记录答案 
			sum=cnt=0;			//清空上一段的数据 
		}
	}
	//到这里还没有被 return 掉，说明这是 Yes 
	printf("Yes\n");
	for(int i=1;i<=ans_cnt;i++)
		printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：_easy_ (赞：0)

# 思路
首先，如果这个序列的和不能被 $\texttt{k}$ 整除，直接输出 $\texttt{No}$，否则输出 $\texttt{Yes}$。当可以按照题目要求分割时，我们直接看能不能按照要求取出来就行了。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[100005],sum,b,ans[100005],kk,cnt;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(sum%k!=0){
		cout<<"No";
		return 0;
	}
	sum/=k;
	for(int i=1;i<=n;i++){
		b++;
		cnt+=a[i];
		if(cnt==sum){
			ans[++kk]=b;
			b=cnt=0;
		}
		else if(cnt>sum){
			cout<<"No";//如果不能凑出来就输出no
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	for(int i=1;i<=k;i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}

```

---

## 作者：atarashiTLE (赞：0)

### 思路：
对于序列 $A$，如果 $\sum{A}\%k\neq0$ 的话，它显然不满足条件，所以可以提前剔除掉这些序列。

接下来是满足 $\sum{A}\%k\neq0$ 的序列。我们采用暴力模拟的方式进行扫描，如果当序列中的子串 $A'$ 满足  $\sum{A'}>\sum{A}\div k$，则序列 $A$ 不满足条件。否则当 $\sum{A'}=\sum{A}\div k$ 时,可以继续循环。

code:
```cpp
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>
#include <cstdio>
#define int long long
using namespace std;
int a[100010], n, k, add, tmp, ans[100010], anssz;
signed main()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		add += a[i];
	}
	if (add % k)
	{
		cout << "No" << endl;
		return 0;
	}
	add /= k;
	for (int i = 0; i < n; i++)
	{
		tmp += a[i];
		ans[anssz]++;
		if (tmp == add)
			tmp = 0, anssz++;
	}
	if (tmp)
		cout << "No" << endl;
	else
	{
		cout << "Yes" << endl;
		for (int i = 0; i < anssz; i++)
			cout << ans[i] << ' ';
	}
	return 0;
}
```

---

## 作者：梧桐灯 (赞：0)

**这题其实真的很简单。**（为什么现在是蓝题QAQ）

首先算出数列所有数的和（不会爆int），然后看能否整除k，不能的话肯定不行。

然后算出每段的和（即总和/k段），然后一段段拼凑即可，如果无法拼凑，输出No就行。

```cpp
#include <cstdio>
#define N 100005
using namespace std;

int n, k, a[N];
int ans = 0, p[N], v;

int main () {
	scanf ("%d %d", &n, &k);
	int i, j;
	for (i = 1; i <= n; i++) {
		scanf ("%d", &a[i]);
		ans += a[i];
	}
	if (ans % k) { //除k有余数（即不能整除），肯定不行
		puts ("No");
		return 0;
	}
	ans /= k; //算出每段和
	int s;
	for (i = 1; i <= n; i++) {
		s = 0;
		j = i;
		while (s < ans) { //拼凑
			s += a[j];
			j++;
		}
		j--;
		if (s > ans) { //无法拼凑
			puts ("No");
			return 0;
		}
		p[++v] = j - i + 1;
		i = j; //可以的话就保存答案
	}
	puts ("Yes");
	for (i = 1; i <= v; i++)
		printf ("%d ", p[i]);
	return 0;
}

```

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 个数 $a_1,a_2,a_3,...,a_n$，要求分成 $k$ 段，每一段的数的总和相等。输出这些段的长度，或者不可能满足要求。

**数据范围：$1\leqslant n,k\leqslant 10^5,1\leqslant a_i\leqslant 10^4$。**
## Solution
我们先暴力扫一遍，把每一段的总和求出来，具体来说，如果有总和 $=\overline{a_i}$ 的一段，那么就把它加入答案序列里面，这样的话还可以很好地判断无法满足要求的情况。最后再看如果分的段数是否 $=k$，不等于的话就不可能满足题目要求，否则将答案序列输出即可。

感觉这样讲的不太懂的去看代码理解一下吧。
## Code
```cpp
int n, k, sum, a[100007], s, len = 0, ans[100007];

int main() {
	getint(n), getint(k);
	_for(i, 1, n) {getint(a[i]); sum += a[i];}
	_for(i, 1, n) {
		len++;
		s += a[i];
		if(s == sum / k) {ans[++ans[0]] = len; len = s = 0; if(ans[0] == k && i != n) return printf("No"), 0;}
	}
	if(ans[0] < k)	printf("No");
	else {
		puts("Yes");
		_for(i, 1, ans[0]) {writeint(ans[i]); putchar(' ');}
	}
	return 0;
}
```

---

