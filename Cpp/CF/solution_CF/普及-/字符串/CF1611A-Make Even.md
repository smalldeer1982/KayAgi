# Make Even

## 题目描述

Polycarp 有一个不包含数字 $0$ 的整数 $n$。他可以使用他的数字执行以下操作数次（可能为零）：

将 $n$ 的长度 $l\ (1 \leq l \leq |n|$，这里 $|n|$ 指 $n$ 的十进制长度 $)$ 的前缀反转，即反转 $n$ 的 前 $l$ 位数字。那么，第 $1$ 个数位（默认从左向右数，下文同理）将与第 $l$ 个数位交换，第 $2$ 个数位与第 $(l-1)$ 个交换......以此类推。

例如，如果 $n=123456789$ 且 $l=5$，则 $n$ 变换后的值将为 $543216789$。

对于不同的操作，$l$ 的值可能不同。

Polycarp 喜欢偶数，并且非常不耐烦。因此，他想用最少的操作次数使他的数字 $n$ 变成偶数。

**本题有多组数据。**

## 样例 #1

### 输入

```
4
3876
387
4489
3```

### 输出

```
0
2
1
-1```

# 题解

## 作者：user470883 (赞：3)

## 思路：
如果我们将其分情况，不多。

先将其分成两类：
1. 数是偶数，输出 `0`。
2. 数是奇数。

然后再分类看第二种：
1. 所有数位上都是奇数，无解，输出 `-1`。
2. 第一位是偶数，翻转整个字符串，一次操作，输出 `1`。
3. 第 $l$ 位为偶数，我们先翻转 $1$ 至 $l$ 位的字符串，然后再翻转整个字符串即可。

总的来说：

分四种讨论就足够了，偶数一种，奇数三种。

## AC CODE:
```
#include<bits/stdc++.h>//万能头
using namespace std;

int main() 
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, a[20], l = 0;
        cin >> n;
        int t = n;
        bool flag = false;//输入+初始化
        while(t != 0)
        {
            a[l++] = t % 10;
            t /= 10;
            if(a[l] % 2 == 0) 
            {
                flag = true;
            }
        }
        if(n % 2 == 0) //分别查看四种情况
        {
            cout << 0 << endl;
            continue;
        }
        if(a[l] % 2 == 0)
        {
            cout << 1 << endl;
            continue;
        }
        if(flag) 
        {
            cout << 2 << endl;
            continue;
        }
        cout << -1 << endl;//无解
    }

    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/64197869)

码字辛苦，给个赞呗。

---

## 作者：szkzyc (赞：1)

这道题虽然看起来没法做，但仔细想想就发现这只是一个分类讨论。

对于这个数偶数数位的数量及位置进行讨论。

设这个数有 $n$ 个偶数数位：

当 $n = 0$ 时，全是奇数数字，不可能让原数变为偶数，输出 $-1$。

当 这个数的末尾是偶数数字 时，本来就是偶数，不需要操作，输出 $0$。

当 这个数的首位是偶数数字 时，直接翻转全部就变为偶数，输出 $1$。

当 这个数的偶数数字在中间 时，需要先让这个偶数翻到首位，再整体翻转一次，输出 $2$。

代码就很容易实现了！

```cpp
#include<bits/stdc++.h>
using namespace std;
bool y(char c){
	return (c - '0') % 2;//将这个数位转换为对2取模 
}
int main(){
	int t;
	cin >> t;
	while(t--){
		string str;//用字符串处理方便一些 
		cin >> str; 
		int len = str.size();//长度 
		int cnt = 0;//记录多少个偶数数位 
		for(int i = 0; i < len; i++){
			if(y(str[i]) == 0) cnt++;
			//如果对2取模为0就cnt+1 
		}
		if(cnt == 0) puts("-1");//全是奇数，输出-1 
		else{
			if(y(str[len - 1]) == 0) puts("0");//本来就是偶数，输出0 
			else if(y(str[0]) == 0) puts("1");//首位是偶数，输出1 
			else puts("2");//否则中间就输出2 
		}
	}
	return !0;
} 
```



---

## 作者：Dragonbell_exp (赞：1)

### 思路：
分情况讨论。

偶数有一个性质，这个数的最后一位一定是偶数。

如果此数列全为奇数，无论怎么颠倒无法出现偶数。

如果此数列有偶数，一定能出现偶数。

如果此数列第一位是偶数，则一定能通过一次颠倒使最后一位成为偶数。

如果此数列第一位不是偶数，可以把此数列在一个偶数处分为两段。通过颠倒靠前的一段使此数列的第一位成为偶数，然后再颠倒一次使此数列最后一位是偶数。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string a;
bool c;
int main(){
	scanf("%d",&t);
	while(t--){
		c=0;
		cin>>a;
		for(int i=0;i<a.size();i++){
			if((a[i]-'0')%2==0){
				c=1;
				break;
			}
		}
		if(c==0){
			cout<<-1<<endl;
			continue;
		}
		if((a[a.size()-1]-'0')%2==0){
			cout<<0<<endl;
			continue;
		}
		else{
			if((a[0]-'0')%2==0){
				cout<<1<<endl;
				continue;
			}
			else{
				cout<<2<<endl;
				continue;
			}
		}
	}
}
```


---

## 作者：落花月朦胧 (赞：0)

# 题目大意

给出一个数字， 可以进行反转的操作（选择一个区间     $[1, l]$ 并颠倒这个区间的顺序）。

询问最少多少次操作才可以让原数变成一个偶数。

# 解题思路

很明显的分类讨论。

## 偶数

如果原数是偶数就不需要反转了。

## 奇数

如果是奇数呢？

可以发现， 颠倒一个区间 $[1, l]$ 的顺序可以理解将 $a_l$ 一道最前面去。


概括这个操作：
+ 把任意的一个数字转换到这个数的第一位 

+ 把第一位的数字转换到第 $l$ 位。

那问题转化为：第一位是一个偶数需要操作多少次？

可以很容易的想到在做一次区间为 $[1, n]$ （其中 $n$ 为这个数字的长度）的操作， 第一位的偶数字就到了最后一位， 这个数不就是一个偶数了吗？


# Code 实现

```cpp
// the code is from zxy
#include <bits/stdc++.h>
int a[100], ai, n, f;
inline void solve() {
	scanf("%d", &n); memset(a, 0, sizeof a); ai = 0, f = 0;
	if (n % 2 == 0) {printf("0\n");return;}
	while (n)  {
		a[++ai] = n % 10;
		n /= 10;
	}
	if (a[1] % 2 == 0) {printf("0\n");return;}
	if (a[ai] % 2 == 0) {printf("1\n");return;}
	for (int i = 2; i < ai; i++) if ((a[i]) % 2 == 0) {f = 1; break;}
	if (!f) {printf("-1\n"); return;}
	printf("2\n");
	return;
}
int main() {
	int T; scanf("%d", &T);
	while (T--) solve();
	return 0;
}
```


---

## 作者：Anonymous_U (赞：0)

思路简单的一道数学题。

首先考虑如果是偶数，则直接输出 $0$。

如果数字中没有偶数，直接输出 $-1$。

接下来考虑翻转操作，很容易得出操作两次就可以将在任意位上的数字翻转至最后一位。及如果数字中出现偶数，通过两次操作就可以将数字变成偶数。

一个特殊情况：如果第一位是偶数，则操作一次即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[20];
void solve(){
	scanf("%s",c+1);
	int l=strlen(c+1);
	if((c[l]-'0')%2==0){
		printf("0\n");
		return ;
	}
	if((c[1]-'0')%2==0){
		printf("1\n");
		return ;
	}
	for(int i=1;i<=l;i++){
		int x=c[i]-'0';
		if(x%2==0){
			printf("2\n");
			return ;
		}
	}
	printf("-1\n");
	return ;
}
int main(){
	int T; cin>>T;
	while(T--) solve();
}
```


---

## 作者：智子 (赞：0)

## 题意

输入一个数 $n$，每次操作可以翻转 $n$ 的前 $l$ 位，问最少要进行多少次操作才能使 $n$ 变成偶数。

## 思路

分情况讨论：

1. 如果这个数是偶数，答案显然为 0。
2. 如果这个数是奇数，第一位为偶数，只需翻转整个数即可，答案为 1。
3. 如果这个数是奇数，其中第 $l$ 位是偶数，那么先翻转 $1$ ~ $l$ 位将它翻转到第一位，再翻转整个数即可。
4. 否则，即如果这个数所有数位上都是奇数，那么不管进行多少次操作都无法变成偶数，输出 -1。

## 代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;

int main() {
    int T;

    scanf("%d", &T);
    while(T--) {
        int n, a[15], l = 0;

        scanf("%d", &n);
        int t = n;
        bool flag = false;
        while(t != 0) {
            a[++l] = t % 10;
            t /= 10;
            if(a[l] % 2 == 0) {
                flag = true;
            }
        }
        if(n % 2 == 0) {
            printf("%d\n", 0);
            continue;
        }
        if(a[l] % 2 == 0) {
            printf("%d\n", 1);
            continue;
        }
        if(flag) {
            printf("%d\n", 2);
            continue;
        }
        printf("%d\n", -1);
    }

    return 0;
}

```

---

## 作者：heaksicn (赞：0)

## 1 题意
给你一个数 $n$ ，每次可以使第 $1\sim l$ 位翻转。问至少翻转多少次可以使这个数变成偶数。  
多组询问。
## 2 思路
首先，如果这个数中每一位都是奇数，那么无论怎么翻转都不能使其变为偶数，直接输出 $-1$ 。  
如果这个数本身就是偶数，输出 $0$ 。  
如果这个数的第一位是偶数，那么直接翻转整个数即可，输出 $1$ 。  
其余情况则先将一个偶数翻转到第一位在翻转整个数即可，输出 $2$ 。  
时间复杂度 $O(T)$ 。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
    if(x<0)
        putchar('-'),x=-x;
    int num=0;
    char sc[10];
    if(!x)
        sc[num=1]=48;
    while(x)
        sc[++num]=x%10+48,x/=10;
    while(num)
        putchar(sc[num--]);
    putchar('\n');
}
int T,n;
bool check(int x){//判断是否有偶数数字
	while(x){
		int q=x%10;
		if(q%2==0) return 1;
		x/=10;
	}
	return 0;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		if(n%2==0){//本身是偶数
			cout<<0<<endl;
			continue;
		}
		if(check(n)==0){//没有偶数数字
			cout<<-1<<endl;
			continue;
		}
		int ans;
		while(n){
			ans=n%10;n/=10;
		}
		if(ans%2==0){//最高位是偶数
			cout<<1<<endl;
		}else{//最高位是奇数
			cout<<2<<endl;
		}
	}
    return 0;
}
```


---

## 作者：Land_ER (赞：0)

## 题目大意
- 有 $t$ 组数据，每组给出一个数字 $n (1 \le n \le 10^{4})$，求将 $n$ 变成偶数的最少操作数，若无法完成则
- 定义一次操作为：给出一个数 $l$，将 $n$ 的第 $1$ 项与第 $l$ 项交换，第 $2$ 项与第 $l-1$ 项交换，以此类推

## 解题思路
**先给出推导的结果：**
1. 当原数中的任意一位都为奇数时无法完成
2. 当原数为偶数时，需要 $0$ 次操作
3. 当原数开头一位为偶数时，需要 $1$ 次操作
4. 否则需要 $2$ 次操作

**证明：**
1. 操作为对原数各数位的交换，原来没有偶数自然变不出来
2. ~~由题意得~~
3. 翻转整个数字
4. 因为无论如何，最后一位都只能与第一位交换，所以需要先将偶数交换到第一位上，然后翻转整个数字

## 代码实现
```cpp
#include<cstdio>
int t;
char n[15];
int s;
bool flag;
inline bool check(int pt){
	return (n[pt]-'0') & 1;
}
void solve(void){
	scanf("%s",n);
	flag = 1;
	for(s = 0;n[s] != '\0';++ s)
		flag = flag && check(s);
	if(flag)
		printf("-1\n");
	else{
		if(!check(s-1))
			printf("0\n");
		else if(!check(0))
			printf("1\n");
		else
			printf("2\n");
	}
	return;
}
int main(void){
	scanf("%d",&t);
	for(int i = 0;i < t;++ i)
		solve();
	return 0;
}
```


---

## 作者：qwq___qaq (赞：0)

### 题意
对于一个正整数 $n$，你可以每次可以使它的 $[l,r]$ 位反转。现在要把它变为一个偶数，求最少操作次数，无解输出 `-1`。
### 分析
首先，我们用字符串存储，这样方便访问，我们分成下面这几种情况求解：
1. 本身就是一个偶数，我们可以不操作，输出 `0`。
2. 首位为偶数，我们只需要将这个数反转即可，输出 `1`。
3. 中间第 $k$ 位为偶数，先交换 $[1,k]$ 再将得到的整数反转。
4. 每一位都没有偶数，绝对无解，输出 `-1`。
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	scanf("%d",&T);
	for(int i=1;i<=T;i++){//多测
		string s;
		cin>>s;
		int len=s.size();//求长度
		if(!((s[len-1]-'0')&1))
			puts("0");
		else if(!((s[0]-'0')&1))
			puts("1");
		else{
			bool p=1;
			for(int j=1;j<len-1;++j)
				if(!((s[j]-'0')&1)){
					p=0;
					puts("2");
					break;
				}
			if(p)
				puts("-1");
		}
	}
    return 0;
}
```

---

