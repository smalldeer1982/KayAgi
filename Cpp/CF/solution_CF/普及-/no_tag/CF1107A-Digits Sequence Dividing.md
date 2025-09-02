# Digits Sequence Dividing

## 题目描述

You are given a sequence $ s $ consisting of $ n $ digits from $ 1 $ to $ 9 $ .

You have to divide it into at least two segments (segment — is a consecutive sequence of elements) (in other words, you have to place separators between some digits of the sequence) in such a way that each element belongs to exactly one segment and if the resulting division will be represented as an integer numbers sequence then each next element of this sequence will be strictly greater than the previous one.

More formally: if the resulting division of the sequence is $ t_1, t_2, \dots, t_k $ , where $ k $ is the number of element in a division, then for each $ i $ from $ 1 $ to $ k-1 $ the condition $ t_{i} < t_{i + 1} $ (using numerical comparing, it means that the integer representations of strings are compared) should be satisfied.

For example, if $ s=654 $ then you can divide it into parts $ [6, 54] $ and it will be suitable division. But if you will divide it into parts $ [65, 4] $ then it will be bad division because $ 65 > 4 $ . If $ s=123 $ then you can divide it into parts $ [1, 23] $ , $ [1, 2, 3] $ but not into parts $ [12, 3] $ .

Your task is to find any suitable division for each of the $ q $ independent queries.

## 样例 #1

### 输入

```
4
6
654321
4
1337
2
33
4
2122
```

### 输出

```
YES
3
6 54 321
YES
3
1 3 37
NO
YES
2
21 22
```

# 题解

## 作者：wzmzmhk (赞：4)

- [题目传送门](https://www.luogu.com.cn/problem/CF1107A)
- [博客食用更佳](https://www.luogu.com.cn/blog/wzmzmhk/solution-cf1107a)


------------
>**题目大意**：你有一个长度为 $n$ 的由 $0$ 到 $9$ 之间的数组成的序列 $s$，你必须最少把它分成两段,使得每一段组成的数字都比前一段组成的数字大。成功输出`YES`，否则输出`NO`。

观察可以发现：
1. 只要 $n$ 的值比 $2$ 大就一定可以成功（分成两段：第一段是第一个数，第二段是剩下的所有数）。
1. 当 $n$ 的值刚好等于 $2$ 时，就需要看 $s_0$ 和 $s_1$ 的数量关系了。
1. 当 $n$ 的值小于 $2$ 时，肯定无法成功。

AC 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        int n;
        string s;
        cin >> n, getline(cin, s);
        if (n < 2 || (n == 2 && s[1] <= s[0])) //输出 NO 的情况
            cout << "NO" << endl;
        else {
            cout << "YES" << endl << 2 << endl << s[0] << " ";
            for (int i = 1; i < n; i++) cout << s[i];
            cout << endl;
        }//输出 YES 的情况
    }
    return 0;
}

```


---

## 作者：Reywmp (赞：3)

又是一道可怕的思维题。~~CF真的是考智商~~

------------

>题面给一个数字字符串，让你分成任意（至少2）份，每份必须按升序（a1<a2<a3<...<ax)，不可以改变原数字字符串。

这题首先是要判断有解无解的，那么我们先推无解的情况。

无解就是怎么分都无法得到升序，那么我们知道，多位数一定大于少位数，所以我们只有在2位时无解，那么，得到一个2位字符串并且**前一位大于后一位**时，无解。

那么由多位数一定大于少位数这个性质，我们贪心：前面分的越少越好。那么大家想一想，如果只分2份，第一份是第一个数并且不是无解情况时不就可以了吗。

比如说：32是无解的，因为在不改变原串时是无法分成升序的。

而233可以分成2 33；789 可以分成 7 89；223213421412412可以分成2 23213421412412等。先把第一位分出去就行了。

------------

那么这题就很简单了：

```cpp
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int t;
	read(t);
	while(t--)
	{
		read(n);
		scanf("%s",a);
		if(n==2&&a[0]>=a[1])printf("NO");//先判断是否无解
		else {//有解
			printf("YES\n");
			printf("%d\n",2);//分2份
			printf("%c ",a[0]);//第一位
			for(int i=1;i<n;i++)
			{
				printf("%c",a[i]);//后面的
			}//这样就保证有解了
		}
		putchar('\n');//要记得换行。。。
	}
	return 0;
}
```


---

## 作者：精神小伙！ (赞：2)

## 思路

这道题可以分三种情况来分析：

1. $ n $ 的值小于二，肯定成功不了。

1. $ n $ 的值等于二，就需要比较 $ s_0 $ 和 $ s_1 $ 的大小。如果 $ s_0 $ 比 $ s_1 $ 大，就不能成功，否则能成功。

1. $ n $ 的值大于二，肯定能成功，只需要把 $ s_0 $ 分为一部分，剩下的分为另一部分。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
using namespace std;
string s;
int main()
{
    int T,n;
    cin>>T;
    while(T--)
    {
    	cin>>n>>s;
    	if(n>2)
    	{
    		cout<<"YES"<<endl;
    		cout<<2<<endl;
    		cout<<s[0]<<" ";
    		for(int i=1;i<n;++i)
    		    cout<<s[i];
    		cout<<endl;//n大于2，分成两段
    	}
    	else if(n<2) cout<<"NO"<<endl;//小于2不行
    	else
    	{
    		int a=s[0]-'0',b=s[1]-'0';
    		if(a>=b) cout<<"NO"<<endl;
    		else
    		{
    			cout<<"YES"<<endl;
    			cout<<2<<endl;
    			cout<<s[0]<<" "<<s[1]<<endl;
    		}//比较s_0和s_1的大小
    	}
    }
	return 0;
}
```

---

## 作者：BlackPanda (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1107A)

------------
### 思路：
这道题可以分情况考虑：
- $N = 2$，并且 $s0 ≤ s1$，**可以**分解。如果 $s0 > s1$，**不可以**分解。
- $N > 2$，肯定**可以**分解，把 $s$ 分成两部分，$s0$ 为一部分，剩下的为一部分。
- $N < 2$，肯定**不可以**分解。

------------
### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int q,n;
string str; 
int main(){
	cin>>q;
	while(q--){
		cin>>n>>str;
		if(n<2){	//n的值小于2肯定不可以 
			cout<<"NO"<<endl;
		}
		else if(n>2){	//n的值大于2肯定可以成功 
			cout<<"YES"<<endl; 
			cout<<"2"<<endl;
			cout<<str[0]<<" ";
			for(int i=1;i<n;i++)	cout<<str[i];
			cout<<endl;
		}
		else if(n==2){
			if(str[0]-'0'>=str[1]-'0'){
				cout<<"NO"<<endl; 
			}
			else{
				cout<<"YES"<<endl;
				cout<<"2"<<endl;
				cout<<str[0]<<" "<<str[1]<<endl;
			}
		}
	}
	return 0;
}


```


---

## 作者：蒟蒻abcd (赞：0)

其实这种题目很能投机取巧的。在这里，你就只要特判一下输出NO的情况就行了，其他的输出YES，分成两段就可以了。  
```
#include<bits/stdc++.h>
using namespace std;
int a[301]={0};
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,last=0;
		cin>>n;
		string s;
		cin>>s;
		if(n==2&&s[0]>=s[1])
		{
			cout<<"NO"<<endl;
			continue;
		}
		cout<<"YES"<<endl<<2<<endl;
		cout<<s[0]<<" ";
		for(int i=1;i<n;i++)cout<<s[i];cout<<endl;
	}
	return 0;
}
```

---

## 作者：ciwomuli (赞：0)

读完题后我们可以发现如果数字大于两位那么肯定可以
只要将第一位单独拿出来分为一段
如果数字是两位那么第一位小于第二位时就可以，反之不可以
code:
```cpp
#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#define LL long long
#define P pair<int,int>
using namespace std;
template <typename T>
inline void read(T &t)
{
    int f = 0, c = getchar();
    t = 0;
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        t = t * 10 + c - 48, c = getchar();
    if (f)
        t = -t;
}
template <typename T, typename... Args>
inline void read(T &t, Args &... args)
{
    read(t);
    read(args...);
}
int main(){
    int t;
    read(t);
    for (int i = 1; i <= t;i++){
        int n;
        read(n);
        if(n>2){
            puts("YES");
            cout << 2 << endl;
            cout<<(char)getchar()<<" ";
            for (int i = 2;i<=n;i++)
                cout<<(char)getchar();
            cout << endl;
        }else{
            int a=getchar(),b=getchar();
            if(a>=b) puts("NO");
            else{
                puts("YES");
                puts("2");
                cout << (char)a << " " << (char)b << endl;
            }
        }
    }
}
  ```

---

