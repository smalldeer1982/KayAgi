# Sonya and Queries

## 题目描述

题意:

有t次操作,操作分三类:
1.形如<+,a>,在multiset中插入一个a.
2.形如<-,a>,在multiset中删除一个a.
3.形如<?,a>,询问multiset中有多少个数的每一位奇偶性都与a相同(位数不足以0补齐).

## 说明/提示

t:[1,1e5]
a:[0,1e18]

注意:

multiset不去重.
记得开long long.

感谢@尘染梦 提供的翻译

## 样例 #1

### 输入

```
12
+ 1
+ 241
? 1
+ 361
- 241
? 0101
+ 101
? 101
- 101
? 101
+ 4000
? 0
```

### 输出

```
2
1
2
1
1
```

## 样例 #2

### 输入

```
4
+ 200
+ 200
- 200
? 0
```

### 输出

```
1
```

# 题解

## 作者：Bogerman (赞：4)

看到到目前这道题还没题解，上传一下自己的AC代码，用的是很土的方法，想法是将读到的每一个数字转化为特有的编号，具体看代码内容应该能看明白吧...第一次发题解，希望能给大家帮助
```cpp
#include<iostream>
#include<cstring>
#include<string>
typedef long long ll;
using namespace std;
ll get(string a){ //将字符串内容转化为特定代号 
    ll len=a.length();
    ll b=0;//特定代号，初始化为0 
    ll cnt=1;
    for(int i=len-1;i>=0;i--){
        b+=((a[i]-'0')%2)*cnt;
/*
代码：b+=((a[i]-'0')%2)*cnt 的功能：
将读入的字符串逐位读取并检测其奇偶性，
奇数转化为1，偶数转化为0，并拼接成一个二进制数字，
最后再将这个二进制数转化为十进制数，也即是这个字符串内容的特定代号
例：1234 --> 1010(逐位读取转化为二进制数) --> 10(十进制特定代号) 
*/ 
        cnt*=2;
    }
    return b;
}
int p[262150];
//注意数组大小，开大了会超内存
//考虑到1e18按上诉转化方式转化得到的特定代号是262144 
int main()
{
    int t;cin>>t;
    while(t--){
        char c;cin>>c;
        string a;cin>>a;
        ll b=get(a);//将读到的字符串a转化为特定代号并存到b中 
        switch(c){
            case '+':{
                p[b]++;//该特定代号的个数+1 
                break;
            }
            case '-':{
                p[b]--;//该特定代号的个数-1 
                break;
            }
            case '?':{
                cout<<p[b]<<endl;//输出特定代号的个数 
                break;
            }
        }
    }
    return 0;
}
```


---

## 作者：Dream__Sky (赞：1)

这道题暴力的最坏复杂度约是 $O(T^2)$，显然会超时，那我们想想别的办法。

考虑到本题只需要考虑一个数各数位上的奇偶性，那么我们可以把每一个数位用 $0$ 和 $1$ 表示，表示奇与偶。接着我们可以把这个 $01$ 串看成二进制，存储在一个桶里，每次操作只要维护桶就行了。

关于桶的大小，因为我们是把每一位看成 $0$ 与 $1$ 的，最多只有 $18$ 位，桶只需要开到二的十八次方，并不会炸空间。


代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T,x,p[300000];
char opt;
int work(int k)
{
	int t=1,sum=0;
	while(k)
	{
		if(k&1) sum+=t;
		k/=10;
		t*=2;
	}
	return sum;
}//进行转二进制的操作
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>opt>>x;
		int s=work(x);
		if(opt=='+') p[s]++;
		else if(opt=='-') p[s]--;
		else cout<<p[s]<<"\n";
	}
	return 0;
}


```


---

## 作者：Wsy_flying_forever (赞：1)

## 进制转换题
### 思路：  
一个显然的性质，插入进去的数字只和它每一位数字的奇偶性有关。根据这个性质，我们可以将插入的每一个数转化为一个二进制数，开一个桶来储存、删除和查询。因为插入数字在 long long 范围内，桶的大小只要开 $ 2^{18} $ 即可。同时，在读入方面，由于可能有前导 $0$ ，直接快读即可（补位后还是 $0$ ）.  
顺便补充一句， ```multiset ```
做这题亲测超时。 （QwQ）
### 代码 
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=(1<<18);
int T;
int cnt[maxn];
char opt[10];
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (!isdigit(ch)) {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (isdigit(ch)) {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline int solve(int x) {
	int res=0,base=1;
	while (x) {
		if (x&1) res+=base;
		x/=10;
		base<<=1;
	}
	return res;
}
signed main() {
	T=read();
	while (T--) {
		scanf("%s",opt);
		int x=solve(read());
		switch (opt[0]) {
			case '+':
				cnt[x]++;
				break;
			case '-':
			    cnt[x]--;
			    break;
			case '?':
				printf("%d\n",cnt[x]);
				break;
		}
	}
	return 0;
}
```
完结撒花！

---

## 作者：Firstly (赞：1)

## **题目思路：**

本题若是直接开一个可重集模拟的话肯定会超时，那么我们需要使用别的思路。

我们可以发现，本题并不需要求准确的数字，只需要判断奇偶性，那么不妨将每一个数字各个数位的奇偶性转化为一个二进制数，开一个大小为 $2^{18}$ 的数组，每一个元素表示目前可重集内与其下标同奇偶性的数量。

当要加入一个数时，将下标为这个数所对应的编码的元素加一，要删掉一个数的时候，将此元素减一，询问时直接输出即可。

## **Code:**

```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int N=1<<18;
int e[N+5],t;
signed main(){
	cin>>t;
	while(t--){
		char ch;
		string s;
		cin>>ch>>s;
		int num=0,rate=1;
		for(int i=s.size()-1;i>=0;i--)
			num+=((s[i]-48)%2)*rate,rate*=2;//将每一位的奇偶性转化为二进制数的过程
		if(ch=='+')e[num]++;
		else if(ch=='-')e[num]--;
		else cout<<e[num]<<endl;
	}return 0;
}
```


---

## 作者：Chenyichen0420 (赞：0)

# 题目大意

给你三种操作：

1. 将一个数加入 multiset 中。
2. 将一个数从 multiset 中删除。
3. 统计每一位都与 $v$ 奇偶性相同的数的个数。

求每一次操作三的结果。

# 解法分析

突破口就是**每一位**都与 $v$ **奇偶性相同**的数的个数。

因为是存在 multiset 中的，所以可以视为不考虑重复。又因为所有操作对序列没有有序性的要求，所以 multiset 只是障眼法。

因为只要求每一位奇偶性相同，所以每一次存入或者去除的时候都可以将每一位简单的压缩为“奇一偶零”的存储方式。这样的话实际也就只有 $2^{18}=262144$ 种情况了。甚至可以直接用桶来存储。

当然，上述操作存在一个前提：取出操作时的数一定至少有一个。

翻译里虽然并没有提到，但是原题面中的 $\texttt{It's guaranteed,that there is at least one }a_i\texttt{ in the multiset}$ 就是这个意思。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t[(1<<18)+5],tmp; char c;
inline int read(){
	int r=0; char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9') r=(r<<1)+(c&1),c=getchar();
	return r;
}
void write(int x){
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int main(){
	cin>>n; getchar();
	while(n--){
		c=getchar();
		if(c=='+') t[read()]++;
		else if(c=='-') t[read()]--;
		else write(t[read()]),putchar('\n');
	}
	return 0;
} 
```

---

