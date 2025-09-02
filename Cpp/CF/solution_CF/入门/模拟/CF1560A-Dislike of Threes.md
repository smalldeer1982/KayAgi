# Dislike of Threes

## 题目描述

Polycarp doesn't like integers that are divisible by $ 3 $ or end with the digit $ 3 $ in their decimal representation. Integers that meet both conditions are disliked by Polycarp, too.

Polycarp starts to write out the positive (greater than $ 0 $ ) integers which he likes: $ 1, 2, 4, 5, 7, 8, 10, 11, 14, 16, \dots $ . Output the $ k $ -th element of this sequence (the elements are numbered from $ 1 $ ).

## 样例 #1

### 输入

```
10
1
2
3
4
5
6
7
8
9
1000```

### 输出

```
1
2
4
5
7
8
10
11
14
1666```

# 题解

## 作者：tongzhenxuan (赞：2)

## 题意简述
输出第 $n$ 个结尾不为 $3$ 并且不能被 $3$ 整除的数。

我们可以直接采用枚举方法来做。
## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,a[1005];
int n,i;
void work()
{
	i=1;
	while(k<=1000)
	{
		if(i%10!=3 && i%3!=0)
		{
			a[++k]=i;
		}
		i++;
	}
}
int main()
{
	work();//枚举序列中前一千个数
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		cout<<a[n]<<"\n";
	}
} 
```


---

## 作者：cjZYZtcl (赞：1)

# 来一发非暴力的题解！
我们发现，同时为三的倍数且以三结尾的数三十个里只有一个，那么我们可以以三十为一个单位来计算。

我们考虑三十个数里，不为三的倍数且末尾不为三的数有 $18$ 个。

那么我们算出输入的 $n$ 中有多少个十八，再列出十八个数分别是多少，单独考虑一下 $n \bmod 18$ 之后剩下的数字就好了。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[18] = {-1, 1, 2, 4, 5, 7, 8, 10, 11, 14, 16, 17, 19, 20, 22, 25, 26, 28};
//单独考虑剩下部分，注意如果n整除18，那么最后一部分将是不完整的30，而是29，所以0的位置要赋为-1。
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int t = read();
	while(t--){
		int n = read();
		write(n / 18 * 30 + a[n % 18]);
		putchar('\n');
	}
}
```


---

## 作者：Chinshyo (赞：1)

## 一句话题意
有一个数列，不存在可被3整除或以十进制表示的数字3结尾的整数，求数列中第 $k$ 个数。

## 思路简述
本题直接模拟即可。从1开始枚举数列的发展。如果下一个是三的倍数或结尾是3，我们就不记录下一位在数列中，否则我们就用计数器记录，当计数器与 $k$ 相等时就输出当前数字。

## 代码

```cpp
#include<bits/stdc++.h>
#define debug cout << "Helloworld" << endl
using namespace std;

int a[10005];

int main() {
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		int s, cnt = 1, r = 1; //cnt:数列中第几个，r:第cnt个数
		cin >> s;
		while(cnt < s) {
			if((r + 1) % 3 == 0 || (r + 1) % 10 == 3) { //判断下一个是否符合在数列中的条件
				r++; //不符合，数组加1
			} else {
				r++; 
				cnt++;//符合条件，全部加1
			}
		} 
		cout << r << endl; //输出解
	}
	return 0;
}

```


---

## 作者：jinxdtaiy (赞：0)

### 题意简述

- 求出一个从 $1$ 到 $n$ 的数列，数列中不含被 $3$ 整除的数，且不含末尾是三的数，求数列中从小到大的某一项。

### 分析

- 作为本场比赛的签到题，简单模拟一下就可以了。因为 $k$ 不会超过 $1000$，所以我们枚举几千项足够了。

爆搜挂着机，打表出省一！~~(bushi~~

#### 直接上代码:

```
#include<bits/stdc++.h>
#define maxn 20000
using namespace std;
long long sum,a[maxn],x,y,n;
int main() 
{
	cin>>n;
	for(int i=1;i<=2200;i++)
	{
		x=i%10; 
		if(i%3==0||x==3) continue;
		a[++y]=i;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		cout<<a[x]<<endl;
	}
	return 0;
}
```



---

## 作者：miserExist (赞：0)

## 题意
 $t$ 组询问，每一次询问第 $k$ 个满足条件的数是什么。
 
 条件是:不被 $3$ 整除且个位上不为 $3$ 的数。
 
## 思路
不被 $3$ 整除，也就是 $i$ $\bmod$ $3$ 不为 $0$。

个位上不为 $3$，也就是 $i$ $\bmod$ $10$ 不为 $3$。

所以我们可以打个表并新建一个数组，把满足条件的数依次插入，下标为 $k$ 的数即为所求。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
const int N = 1e6 + 10;

int n,m;

int st[N];
int cnt = 0;


signed main(){
    int ttt;
    cin >> ttt;

    for(int i = 1; i <= 1000000; i ++)
    {
        if(i % 3 == 0 || i % 10 == 3)continue;
        
        st[++ cnt] = i;
        
    }


    while(ttt --)
    {
        int k;
        cin >> k;
        
        cout << st[k];

        puts("");
    }
    
    return 0;
}
    
    
    
    
    
    
    
    
    


```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

很简单，用一个数组提前将 $1$ 到 $1000$ 个满足要求的数存下来就可以了。

注意，跳过不满足要求的数的语句用 `while`，不要写 `if`。

其实还有一个方法。根据 $n\div18$ 的余数判断。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
#define max_n 1000
int t;
int n;
int a[max_n+2];
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1560A_1.in","r",stdin);
	freopen("CF1560A_1.out","w",stdout);
	#endif
	for(int i=1,j=1;i<=max_n;++i,++j){
		while(j%3==0||j%10==3)++j;
		a[i]=j;
	}
	scanf("%d",&t);
	for(int ca=1;ca<=t;++ca){
		scanf("%d",&n);
		printf("%d\n",a[n]);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/56326915)

By **dengziyue**

---

