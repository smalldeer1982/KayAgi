# Long Number

## 题目描述

给定一个一个n位数，以及1~9数字的替换数。现请你在这个n位数上选一个连续的数段，将段内的每个数字替换成相应数字的替换数。要求：输出按照要求替换后的最大n位整数。

## 样例 #1

### 输入

```
4
1337
1 2 5 4 6 6 3 1 9
```

### 输出

```
1557
```

## 样例 #2

### 输入

```
5
11111
9 8 7 6 5 4 3 2 1
```

### 输出

```
99999
```

## 样例 #3

### 输入

```
2
33
1 1 1 1 1 1 1 1 1
```

### 输出

```
33
```

# 题解

## 作者：yuzhechuan (赞：4)

一道水题，但由于题意原因wa了几次QAQ

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[200005],b[10];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%1d",&a[i]); //%1d表示读入一个一位整数
	for(int i=1;i<=9;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++){
		if(a[i]<b[a[i]]){ //一个简单的数学常识：高位越大，低位不管
			for(int j=i;a[j]<=b[a[j]]&&j<=n;j++) //可以替换了就一直换直到还是原来的数大（注意j<=n还是要写不然会RE/TLE）
				a[j]=b[a[j]];
			break; //换完跑路
		}
	}
	for(int i=1;i<=n;i++) printf("%d",a[i]); //输出。。。
}
```


---

## 作者：water_tomato (赞：3)

已有的题解或是说的太麻烦了，或是一笔带过，本篇题解决定简明扼要地好好讲一讲。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1157B) 大体题意不再阐述，注意你只能根据给出的规则更换一段数而不能隔开来换就好了。

## 解析

已有的题解也都提到了，遇到第一个 $b_{num_i}>num_i$ ( $b$ 数组为更换规则，$num$ 数组为每一位的数字)时开始更换，一直更换到 $b_{num_i}<num_i$ 为止。

那么，为什么呢？

首先我们知道，越是高位增大，效益就越大， 因此我们要尽早**开始更换**，也就是从第一个可以变大的最高位开始，而又由于题目中要求更换的是**一段数**，同样的，越是高位变小，亏损就越大，因此我们要在找到第一个会变小的数时就及时止损，即停止更换并退出。

至于为什么是 $>$ 而不是 $\ge$ 呢？

显然的，我们找到第一个 $b_{num_i}\ge num_i$ 的数时，我们如果直接进行更换，那就容易**过早碰壁**，且这个行为时毫无意义的，这样还不如放到后面换。

例：样例一中的数若改为 $1733$ 则采用 $\ge$ 在替换了第一个数后，碰到 $7$ 就会停止，而实际上应该把这次更换的机会留下来，从第三位开始更换。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,num[N],b[N];
char a[N];
bool flag;
int main(){
	scanf("%d",&n);
	scanf("%s",a+1);
	for(int i=1;i<=n;i++)
		num[i]=a[i]-'0';
	for(int i=1;i<=9;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=n;i++){
		if(b[num[i]]>num[i]){
			if(!flag) flag=true;//flag 判断有无开始更换 
			num[i]=b[num[i]];
		}
		else if(b[num[i]]<num[i])
			if(flag) break; //若开始更换后碰到会亏损的数，就退出 
	}
	for(int i=1;i<=n;i++)
		printf("%d",num[i]);
	return 0;
}
```
## 琐记
这题恶意评分了吧，实际难度橙或黄差不多了吧。


---

## 作者：Erotate (赞：2)

很显然，这题应该用字符串来存储原来的数。

那么我们从高位到低位遍历一遍这个字符串，一旦遇到比原来数字大的可替换数字，就替换，直到不能替换为止，立马退出循环。

为什么这样做呢，因为高位的数字越大，整个数就越大，增加更多，所以应该优先替换高位的数字而不是低位的数字。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,b[10],flag=0;
string s;
int main(){
    cin>>n>>s;
    for(int i=1;i<=9;++i) cin>>b[i];
    for(int i=0;i<n;++i){
      int tmp=s[i]-'0';
      if(b[tmp]>tmp){
        	s[i]=b[tmp]+'0';
        	flag=1;
      }else if(b[tmp]<tmp && flag) break;
    }
    cout<<s<<endl;
    return 0;
}
```


---

## 作者：MiniLong (赞：1)

# 贪心
这是一道水题

只需要从头开始遍历一次数字，如果可替换的数字比当前大的话，就立即替换，因为**位数越大增加的就更多**，这就是贪心的体现了

还有就是替换的数字要连续的，如果发现不能替换了就立即退出（原因与上面的一样）

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[200005], b[10];
string s;
bool start;
signed main(){
	cin >> n;
	cin >> s;
	for(int i = 0; i < s.size(); ++i) a[i+1] = s[i] - '0';
	for(int i = 1; i <= 9; ++i) cin >> b[i];
	for(int i = 1; i <= n; ++i){
		int x = a[i], y = b[x];
		if(y > x) a[i] = y, start = 1;
		else if(y < x && start) break;
	}
	for(int i = 1; i <= n; ++i) cout << a[i];
	return 0;
}
```

---

## 作者：_szs9601 (赞：0)

### 思路
要是答案最大，应该尽可能地让高位变大。所以程序就变得很简单了。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len,i,f[100],a[200100];
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%1d",&a[i]); 
	for(i=1;i<=9;i++) scanf("%d",&f[i]);
	for(i=1;i<=n;i++)
		if(f[a[i]]>a[i]) break;//当=时不应该做改变，若只有当前一个数可以改变，就会浪费掉。
	for(i;i<=n;i++)
		if(f[a[i]]>=a[i]) a[i]=f[a[i]];//如果为=，则当前数不变，后面的数还可以继续改变
		else break;
	for(i=1;i<=n;i++) printf("%d",a[i]);
	return 0;
}
```


---

## 作者：danny101 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1157B)

####  题目大意：

给定一个十进制数，以及 $1\sim9$ 的替换数，求替换一段连续区间后的最大数。

#### 大致思路：

显然，如果一位上的数比它的替换数要小，那么替换它就是一个更好的选择。因为位数越高，替换后增加量就越大，所以从高位开始枚举，一旦这一位的替换数比原数大，就替换掉。

因为替换的数字要连续，所以遇到第一个替换数小于原数的数位就停止了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200001],b[10];
string s;
bool f;
signed main(){
	cin>>n>>s;
	for(int i=0;i<s.size();i++)a[i+1]=s[i]-'0';
	for(int i=1;i<=9;i++)cin>>b[i];
	for(int i=1;i<=n;i++){
		int x=a[i],y=b[x];
		if(y>x)a[i]=y,f=1;
		else if(y<x&&f)break;
	}
	for(int i=1;i<=n;i++)cout<<a[i];
}
```

---

## 作者：zbk233 (赞：0)

## 解题思路

这道题实际上就是一道简单的贪心题。

首先，答案不可能比原数小，所以只考虑更改比原数的数字大的数位。

我们都知道，增大离最高位越近的数字能让这个数变得更大，而如果让这个数字变小肯定会这个数变得更小。

而题目说的是要改变一段连续的区间。

所以我们的贪心思路就是：从最高位开始，把遇到的第一个比原数大的数字设为左端点 $l$。

接着，从 $l$ 开始，不断地找**大于或等于**原数的数字，直到找到第一个小于原数的数字，再把它设为右端点 $r$。

最后，对 $[l,r]$ 区间进行修改即可。

## 代码实现

```cpp
#include<iostream>
using namespace std;
int a[200005];
int b[114];
char c[200005];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		a[i]=c[i]-'0';
	}
	for(int i=1;i<=9;i++){
		cin>>b[i];
	}
	int l=n+1;
	for(int i=1;i<=n;i++){
		if(b[a[i]]>a[i]){
			l=i;
			break;
		}
	}
	for(int i=l;i<=n;i++){
		if(b[a[i]]>=a[i]){
			a[i]=b[a[i]];
		}else{
			break;
		}
	}
	for(int i=1;i<=n;i++){
		cout<<a[i];
	}
    return 0;
}
```


---

## 作者：BootsH (赞：0)

此题可以直接贪心。

我们从最高位遍历，若碰到了此位数替换后，替换后的数字比原数 __大__ ，我们就可以替换此位，并且把后面的几位按照基本相同（不是完全相同）的规则替换。当我们 __已经替换了数__ 后，接下来的替换规则应是：如果替换后的数字 __大于等于__ 原数，则可以替换。

解释：

1. 第一次尝试替换时，替换后的数字必须比原数大。

原因：这个数字替不替换无所谓，但如果下一位替换后比原数小，显然在此替换不划算。不如等到后面再替换。

2. 已经替换某些数后，再尝试替换时，替换后的数字必须大于等于原数。

原因：也是因为这个数字替不替换无所谓。但因为题面规定，替换的是 __连续的数__ ，所以如果这个不换而后面一位替换后比原数大，那么也不划算。所以此时，规则更改为：替换后的数字必须大于等于原数。

坑点：

1. 替换的必须是连续的一串数。

2. 见上面 解释 部分的2. 。

3. 一串数字替换完后，要立即 `break` 然后输出结果。

代码：

```cpp
#include <iostream>
#include <fstream>

namespace Solution
{
    int num[2000005];
    int ch[2000005];

    int main()
    {
        #ifndef ONLINE_JUDGE
            std::ifstream cin("main.in");
            std::ofstream cout("main.out");
        #else
            std::ios::sync_with_stdio(false);
            std::cin.tie(nullptr);
            std::cout.tie(nullptr);
            using std::cin;
            using std::cout;
        #endif
        int n;
        cin >> n;
        std::string s;
        cin >> s;
        for (int i = 1; i <= 9; ++i)
        {
            cin >> ch[i];
        }
        for (int i = 0; i < n; ++i)
        {
            num[i] = s[i] - 48;
        }
        for (int i = 0; i < n; ++i)
        {
            if (num[i] < ch[num[i]])
            {
                num[i] = ch[num[i]];
                ++i;
                while (i < n && num[i] <= ch[num[i]])
                {
                    num[i] = ch[num[i]];
                    ++i;
                }
                break;
            }
        }
        for (int i = 0; i < n; ++i)
        {
            cout << num[i];
        }
        #ifndef ONLINE_JUDGE
            cin.close();
            cout.close();
        #endif
        return 0;
    }
} // namespace Solution


int main(int argc, const char* argv[])
{
    Solution::main();
    return 0;
}
```

---

## 作者：Frozencode (赞：0)

模拟题。要使得到的数字尽可能大，我们肯定会想到从高位开始改。

那么什么时候改呢？我一开始觉得只要从第一个$f(x)\geqslant x$的地方往后改直到遇到第一个$f(x)< x$的位置就可以了，然后想到个反例 :

$a:123$   $f(1)=1$  $f(2)=1$ $f(3)=9$ 最大应该是$129$,但是按我这么想就会跑出来$123$。

修改下之前的思路，把条件$f(x)\geqslant x$改为$f(x)> x$，这题就被我们解决辣~


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=500010;
const ll INF=2147483647;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
inline void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
	{
		write(x/10);
	}
	putchar(x%10+'0');
}
ll n,a[maxn],f[15];
bool c[23];
char ch;
int main()
{
	cin>>n;
	ch=getchar();
	for(int i=1;i<=n;i++)
	{
		ch=getchar();
		a[i]=ch-'0';
		//cout<<a[i];
	}
	for(int i=1;i<=9;i++)
	{
		cin>>f[i];
		if(f[i]>i)c[i]=1;//c数组代表符合条件的数。
	}
	for(int i=1;i<=n;i++)
	{
		if(c[a[i]])
		{
			for(int j=i;j<=n;j++)
			{
				if(c[a[j]]||a[j]==f[a[j]])//这里与之前不同，只要f(x)不小于x我们就可以继续往下修改了。
				{
					a[j]=f[a[j]];
				}
				else
				{
					break;//遇到第一个不符合的数就停止。
				}
			}
			break;
		}
	}
	for(int i=1;i<=n;i++)cout<<a[i];
	return 0;
}
```


---

## 作者：Zekrom (赞：0)

遇到第一个**f[x]>x**的就换  
上代码  
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,f[20];
char ch[200010];
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
int main()
{
	n=read();
	cin>>(ch+1); 
	for(int i=1;i<=9;i++)
		f[i]=read();
	for(int i=1;i<=n;i++){
		int x=ch[i]-'1'+1;  
		//cout<<x<<endl;
		if(f[x]>x){             //第一个f[x]>x
			int t=x,j=i;
			while(f[t]>=t&&j<=n){   //之后只要f[x]>=x 就换
				ch[j]=(char)(f[t]-1+'1');
				j++;t=ch[j]-'1'+1; 		
			}
			break;
		}
	}
	cout<<(ch+1);
	return 0;
}

```


---

## 作者：VIOLET__FOREVER (赞：0)

题目传送门——[Long Number](https://www.luogu.com.cn/problem/CF1157B)

## 简单思路
由题意得我们要改变一个区间内的数，使得最后的结果最大，所以显而易见，根据数学规则，位数越高的数越大，最后的数越大，所以我们要尽可能早的开始更改数字，所以当我们便利的时候一旦发现有数的替换数大于本身，我们就将他替换，同时往后循环，如果后面的数的替换数大于等于本身，我们也将他更换（防止后面有遗漏）因为修改的要求是连续的数段，所以我们一旦遇到不符合的条件就直接退出就行了
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],num[15];
char ch;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>ch;//用字符串的形式读入
		a[i]=ch-'0';
	}
	for(int i=1;i<=9;i++) cin>>num[i];
	for(int i=1;i<=n;i++){
		if(num[a[i]]>a[i]){
			for(int j=i;j<=n;j++){
				if(num[a[j]]<a[j]) break;//不符合条件就退出
				a[j]=num[a[j]];
			}
			break;//数段结束后就退出，不用再继续了
		}
	}
	for(int i=1;i<=n;i++) cout<<a[i];//输出最后的结果
	return 0;
} 
```


---

