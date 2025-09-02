# Similar Pairs

## 题目描述

如果两个数$x$和$y$具有相同的奇偶性（除以2时的余数相同），或者$|x-y|=1$，我们称$x$和$y$相似。例如，在数对$(2,6)$,$(4,3)$,$(11,7)$中，数字彼此相似，而在数对$(1,4)$,$(3,12)$中，数字则不相似。

给你一个有$n$($n$是偶数)个正整数的数组$a$，判断是否有一种方法把数组中的数两两配对，使得数组中每个数恰好处于一个数对中并且每个数对中的数彼此相似。

## 样例 #1

### 输入

```
7
4
11 14 16 12
2
1 8
4
1 1 1 1
4
1 2 5 6
2
12 13
6
1 6 3 10 5 8
6
1 12 3 10 5 8```

### 输出

```
YES
NO
YES
YES
YES
YES
NO```

# 题解

## 作者：Blunt_Feeling (赞：9)

## CF1360C Similar Pairs 题解
题目大意：给你 $n$ 个整数（$n$ 为偶数），问是否可以将这 $n$ 个数分为若干对数，使得每对数的奇偶性相同或差值为 $1$？

可以分成两个步骤判断：

设数列中偶数的个数为 $m$，当 $m$ 为偶数时，所有的偶数因为奇偶性相同，可以被分为 $m/2$ 对。由于总个数为偶数，奇数的个数也为偶数，因此所有的奇数也可以被分为偶数对。所以，当数列中偶数的个数为偶时，直接输出 YES 。

当数列中偶数的个数不为偶时，就要把数列排序，看看有没有两个数的差值为 $1$。只要有两个数差值为 $1$，就输出 YES 。否则输出 NO 。

简单证明一下：由于此时数列中偶数的个数不为偶，可得数列里奇数和偶数的个数都为奇。只要有两个数差值为 $1$，就可以先把这组提出。而剩下的数里就会少掉一个偶数和一个奇数，于是就只剩下了偶数个偶数和偶数个奇数，就可以利用奇偶性相同分完剩余的数。

思路应该还是比较清晰的。
### Code
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
int T,n,a[55];
int main()
{
    cin>>T;
    while(T--)
	{
		cin>>n;
		int m=0,cnt=0; //m用来统计数列中偶数的个数
		For(i,1,n)
		{
			cin>>a[i];
			if(a[i]%2==0) m++;
		}
		if(m%2==0) puts("YES");
		else
		{
			sort(a+1,a+n+1); //升序排序
			For(i,2,n)
				if(a[i]-a[i-1]==1)
					cnt++; //统计差值为1的数对的个数
			puts(cnt>=1?"YES":"NO"); //有一对数差值为一就输出YES，否则输出NO
		}
	}
    return 0;
}
```

---

## 作者：liuyi0905 (赞：5)

**题目大意：**

共有 $t\ (1\le t\le1000)$ 组数据，每组数据给定一个正整数 $n\ (2\le n\le50)$，和 $n$ 个正整数 $a_1,a_2...a_n (1\le a_i\le100)$，求是否存在 $x$ 和 $y$ 相似的分组。

**思路：**

把偶数或奇数的个数求出来，如果它的个数 $\bmod\ 2=0$，就一定可以分成功。如果不行，就把 $x$ 和 $y$ 相差一的组数求出来，只要大于等于一，就也能分成。

有请 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){	
		int n,a[51],ji=0,sum=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			ji+=a[i]%2;
		}
		if(ji%2==0)cout<<"YES\n";
		else{
			sort(a+1,a+n+1);
			for(int i=2;i<=n;i++){
				if(a[i]-a[i-1]==1)sum++,i++;//求出x和y相差一的组数
			}
			if(sum>=1)cout<<"YES\n";
			else cout<<"NO\n";
		}

	}	
	return 0;
}
```

---

## 作者：liruixiong0101 (赞：2)

## P1 题意：
$T$ 次询问，每次询问分别给你一个数 $n$（$n$ 为偶数）和 $n$ 个数，$a_1,a_2,\dots,a_n$，请问是否可以将其两两分组，分成 $(x_i,y_i)$，每组保证为下列条件中的一种：

1. $x_i \bmod 2 = y_i \bmod 2$
2. $|x_i-y_i|=1$

若可以满足上述条件输出 `YES` 否则输出 `NO`。

## P2 思路：
观察上述条件的条件一可想到，统计 $a$ 数组中的奇数个数和偶数个数，将其分别记为 $odd,even$。

- 若 $odd \bmod 2 = 0 \wedge even \bmod 2 = 0$，即奇数个数与偶数个数同为偶数，这种情况一定可以两两分组，因为每一个偶数都可以和其他的任何一个没有选过的偶数组合，奇数同理。
- 若 $odd \bmod 2 = 1 \wedge even \bmod 2 = 1$，即奇数个数与偶数个数同为奇数，这种情况就需要用到第二条条件，找出两个数的差的绝对值的值为 $1$ 的两个数，若找的到一定可以两两分组，否则不行。

---

找到 $a$ 数组里的两个数的差的绝对值的值为 $1$ 的查找可以先将数组排序，若所有相邻两数的差的绝对值的值都不为 $1$ 即不可以两两分组，否则可行。

## P3 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 55;
int n , a[N];
int main(){
    // freopen("in.txt" , "r" , stdin);
    // freopen("out.txt" , "w" , stdout);
    ios::sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    int T;
    for(cin >> T; T-- && cin >> n;){
        int odd = 0 , even = 0;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(a[i] & 1) odd++;
            else even++;
        }//算出odd,even
        if(odd % 2 == 0 && even % 2 == 0){
            cout << "YES\n";
            continue;
        }//若同为偶数一定可以两两分组
        sort(a + 1 , a + 1 + n);
        bool flag = 1;
        for(int i = 1; i < n; i++){
            if(abs(a[i] - a[i + 1]) == 1){
                cout << "YES\n";
                flag = 0;
                break;
            }//若相邻的两个数的差值的绝对值的值为1，一定也可以两两分组
        }
        if(flag) cout << "NO\n";//不可以两两分组
    }
    return 0;
}
```

---

## 作者：2011FYCCCTA (赞：1)

# [原题](https://www.luogu.com.cn/problem/CF1360C)
大水题！

---
### 分析
很明显是一道贪心。

可以先求出输入数据中奇偶数的数量，这对之后的分析有很大帮助。

现在，以奇偶数的数量来分类讨论：

0. 特判：$n$ 为奇数

	虽然我知道这很愚蠢，但题目里毕竟没说呀。
    
   如果是这种情况，不能两两一组，输出 `NO`。
   
   若 $n$ 为奇数，就不存在有奇数个奇数和偶数个偶数或偶数个奇数和奇数个偶数这种情况了（绕口令）。

1. 奇数个奇数和偶数

	将奇偶性相同的一组两两先分好，还剩下一个奇数一个偶数。如果这两个数相邻，就可以分配完，输出 `YES`，否则输出 `NO`。
    
   由于任意两个奇数或偶数都可分到一组，因此只需枚举一遍所有的元素，找到有相邻的就行了（剩下的奇偶性相同的一组两两分），这里用 `map` 比较方便。 

2. 偶数个奇数和偶数

	奇偶性相同的一组两两刚好分完，输出 `YES`。

---
代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
map<int , bool> mp;//存储数字是否出现，偏于判断奇数个奇数和偶数这种情况。
//其实用数组也可以，因为这题出题人良心地将数据范围缩到了1≤ai≤100。
int t , n , a[55] , odd , even;
int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n;
		odd = even = 0; mp.clear();
		for (int i = 1 ; i <= n ; i++)
		{
			cin >> a[i]; mp[a[i]] = true;
			if (a[i] % 2 == 0) ++even;
			else ++odd;
		}
		
        //特判n为奇数
		if (n % 2 == 1) cout << "NO";
        //奇数个奇数和偶数
		else if (odd % 2 == 1 && even % 2 == 1)
		{
            bool flag = false;
			for (int i = 1 ; i <= n ; i++)
                if (mp[a[i] + 1]) {flag = true; break;}
            if (flag) cout << "YES";
            else cout << "NO";
		}
        //偶数个奇数和偶数
        else cout << "YES";
        cout << "\n";
	}
	return 0;
}
```

---

## 作者：CSP_Sept (赞：1)

### 题意

给定一个长度为 $n$ 的数列（$n$ 是偶数），求能否把这个数列分成 $\dfrac{n}{2}$ 段，每段 $2$ 个数，每一段数 $[a,b]$ 满足 $a,b$ 奇偶性相同或 $|a-b|=1$。

### 思路

令 $ou,ji$ 分别为这个数列中偶数和奇数的个数。

$$
\begin{matrix}
\because n\bmod 2=0,\therefore ou,ji\text{ 的奇偶性相同。}\\
\mathbf{if\ }ou\bmod 2=0,\mathbf{then\ }\text{you can }\mathbf{puts}(\tt{"YES"})\\
\mathbf{else:}
\end{matrix}
$$

$ou-1$ 个偶数和 $ji-1$ 个奇数可以分别配对。直接判断数列中是否存在一组数 $\{a,b\}$，使 $|a-b|=1$。

### 实现

其余的几篇题解都是使用 sort 来判断数列中是否存在一组数 $\{a,b\}$，使 $|a-b|=1$ 的，那么我现在介绍一种新的方法 map。

~~你们不知道 sort 的复杂度高吗~~

### map 的基本用法
##### map 相当于一个下标可以是任何类型的数组。

1. `#include <map>` map 头文件。

1. `map <A,B> ds` 建立一个叫 `ds` 的，下标类型为 `A` ，元素类型为 `B` 的映射表。

1. `ds[t1]=t2` 把下标为 `t1` 对应的值改为 `t2` 。

1. `ds[A]` 访问下标为 `A` 的元素。

### 代码

```cpp
#include <cstdio>
#include <map>

using namespace std;
int n,t,a[60];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        map <int,bool> ds;
        int ou=0,ji=0;
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
            ds[a[i]]=1;//a_i 存在
            if(a[i]%2) ji++;
            else ou++;
        }
        if(ji%2==0){puts("YES");continue;}
        bool f=0;
        for(int i=0;i<n;i++){
            if(!f&&(ds[a[i]+1]||ds[a[i]-1])){puts("YES");f=1;}//如果 a_i-1 或 a_i+1 存在, 则直接输出 "YES"
        }
        if(!f) puts("NO");//否则输出 "NO"
    }
    return 0;
}
```

---

## 作者：Warriors_Cat (赞：1)

## CF1360C

一个不错的题，也想了一段时间。

我们先得出这个 $a$ 序列中奇数的个数和偶数的个数，由于 $n$ 是偶数，所以奇数个数与偶数个数的奇偶性相同。

若奇数个数和偶数个数均为偶数，则可以配对，答案为 `YES`。

若奇数个数和偶数个数均为偶数，我们跟 B 一样把 $a$ 数组排个序，然后找找响铃两数之差有没有等于 $1$ 的。如果有就转化成第一种情况，答案为 `YES`，否则为 `NO`。

代码按上述讲解模拟即可。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
#define F(i, a, b) for(int i = a; i <= b; ++i)
#define R(i, a, b) for(int i = a; i >= b; --i)
int t, n, a[110];
int main(){
	t = read();
	while(t--){
		n = read();
		int cnt1 = 0, cnt2 = 0;
		F(i, 1, n) a[i] = read(), cnt1 += a[i] & 1, cnt2 += a[i] & 1 ^ 1;
		sort(a + 1, a + n + 1);
		if(cnt1 & 1 ^ 1){
			puts("YES");
			continue;
		}//如果是偶数就肯定行
		bool flag = 0;
		for(int i = 1; i < n; ++i) if(a[i + 1] - a[i] == 1){
			puts("YES");
			flag = 1;
			break;
		}//否则找一找有没有相差为 1 的数
		if(!flag) puts("NO");
	}
	return 0;
}

```

---

## 作者：rui_er (赞：1)

结论题。

自己列了几次找了一下规律，发现有两个数差为 $1$ 则必定可以，否则看奇偶数的个数。

找规律思考过程：

1. 如果有两个数差为 $1$，则必有一奇一偶。
2. 奇数个数与偶数个数的奇偶性必然相同。（因为总数是偶数个）
3. 去掉所有差为一的数，剩余的数仍然满足 $2$。
4. 如果剩余的数中奇数个数和偶数个数均为奇数，则将一对差为一的数拿出用于奇偶数对。（如果没有差为一的数，就不可能完成）
5. 否则将剩余的数按照奇数、偶数分组即可。

综上，如果有差为一的数，肯定能完成任务；否则如果奇偶数个数为奇数，不能完成，为偶数可以完成。

代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
using namespace std;

int T, n, a[51];

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		int odd = 0, even = 0;
		for(int i=1;i<=n;i++) {
			scanf("%d", &a[i]);
			if(a[i] & 1) {
				++odd;
			}
			else {
				++even;
			}
		}
		sort(a+1, a+1+n);
		bool book = false;
		for(int i=2;i<=n;i++) {
			if(a[i] - a[i-1] == 1) {
				book = true;
				break;
			}
		}
		if(book) {
			puts("YES");
		}
		else if(even % 2 == 0 && odd % 2 == 0) {
			puts("YES");
		}
		else {
			puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：Composite_Function (赞：0)

# 一、思路

题目中说了：保证 $n$ 为偶数

所以不用考虑总共有奇数个数而一定无法匹配的情况。

于是继续往下想：

只要奇数、偶数数量都是偶数即可。

但如果不是，则再看一看有没有两数相差 $1$ 。

但怎么快速找相差 $1$ 的两数呢？

实际上只要对原数组排序，再找，就能把 $O(n^2)$ 算法变成 $O(n\cdot log_{2}n)$ 算法。

------------

# 二、AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100
int t,n,val[100];
int main(){
    cin>>t;
    //注意有 t 组数据
    while(t--){
        int even=0; bool flag=false;
        //只要偶数有偶数个，奇数也有偶数个
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>val[i];
            even+=(val[i]%2==0);
        }
        if(even%2==0) flag=true;
        else{
            sort(val+1,val+n+1);
            //排序找更快一些
            for(int i=1;i<n;i++)
                if(val[i]+1==val[i+1])
                    flag=true;
        }
        cout<<(flag?"YES":"NO")<<endl;
    }
    return 0;
}
```

编者温馨提示：不要粘其然，不抄其然，也不知其然，更不知其所以然，反正棕了我不管。

---

## 作者：PLDIS (赞：0)

## CF1360C题解

首先，我们要知道：奇偶性相同的数可以变成一组，相差 $1$ 的一组数 **奇偶性不相同**，输出 `YES` 的条件就是经过奇数 $-2$，偶数 $-2$ 和奇数偶数一起 $-1$ 这三个操作任意次（**第三种操作要两个数相差 $\bold{1}$** ），奇数和偶数的个数都为 $0$。则如果奇数个数和偶数个数 $\mod2$ 都是 $0$，那么就一定会输出 `YES`。所以，如果它们的个数奇偶性**不相同**，那么怎么改都改不到奇数偶数均为 $0$ 的条件，所以直接输出 `NO`。这时，我们只剩下一种情况：**奇数偶数的个数都是奇数**的情况。

我们知道，奇数 $-1$ 等于偶数。于是，如果我们将两个奇数分别 $-1$ 的话，就会得到**两个偶数**。所以，只要进行一次奇数偶数分别 $-1$ 的操作就可以了。于是，**只要有一组数相差 $\bold{1}$，那么就输出 `YES`，否则输出 `NO`**。

## Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int a[n];
        int x, y;
        x = 0, y = 0;
        for(int i = 0;i < n;i++){
            cin >> a[i];
            if(a[i] % 2){
                y++;
            }
            else{
                x++;
            }
        }
        if(!(x % 2 || y % 2)){
            cout << "YES" << endl;
            continue;
        }
        else if(x % 2 == 0 || y % 2 == 0){
            cout << "NO" << endl;
            continue;
        }
        sort(a, a + n);
        int ans = 0; //相差1的一组数的个数
        for(int i = 1;i < n;i++){
            if(a[i] - a[i - 1] == 1){
                ans++;
            }
        }
        if(ans >= 1){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
    return 0;
}
```

---

## 作者：CSPJ10pts (赞：0)

题目难度约橙，不到黄

# 题目大意：

如果两个数 $x$ 和 $y$ 具有相同的奇偶性（除以2时的余数相同），或者 $|x-y|=1$ ，我们称 $x$ 和 $y$ 相似。

给你一个有 $n$ ( $n$ 是偶数)个正整数的数组 $a$，判断是否有一种方法把数组中的数两两配对，使得数组中每个数恰好处于一个数对中并且每个数对中的数彼此相似。

# 思路：

情况1：当输入的所有数奇偶性都相同，输出 $\texttt{YES}$ ;

情况2：当输入的所有数奇偶性有不同，根据 $n$ 为偶数这条性质，我们可以知道，当奇数和奇数，偶数和偶数匹配完毕后，要么剩下一奇一偶，要么啥也不剩，直接输出 $\texttt{YES}$。对于前者，我们只要去找是否有两个连续的自然数去满足第二个配合即可。如果有，输出  $\texttt{YES}$ ，不然输出 $\texttt{NO}$。

# AC代码

```
#include <iostream>
#include <algorithm>
using namespace std;
int t;
int main() {
    cin >> t;
    while (t--) {
        int n, a[51], b[101] = {}, cnta = 0, cntb = 0;
        cin >> n;
        if (n % 2 != 0) { // 其实不用这一步
            cout << "NO" << endl;
            continue;
        }
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            if (a[i] % 2 == 0) cnta++; //统计偶数出现次数
            else cntb++; //统计奇数出现次数
        }
        if (cnta == 0 || cntb == 0 || cnta % 2 == 0 && cntb % 2 == 0) cout << "YES" << endl; //情况1和情况2的第一种情况
        else {
            sort(a + 1, a + n + 1); // 排序方便找连续自然数
            bool f = 0;
            for (int i = 2; i <= n; i++) { 
                if (a[i] == a[i - 1] + 1) { // 发现连续自然数了
                    cout << "YES" << endl; // 直接输出YES
                    f = 1;
                    break; // 跳出去
                }
            }
            if (!f) cout << "NO" << endl; // 不可以，总司令
        }
    }
    return 0; // 结束
}
```

[AC记录～](https://www.luogu.com.cn/record/96975527)

说句闲话，我交这题前，提交 $350$，通过 $175$

---

## 作者：fuxiao (赞：0)

这是我提交的第 $2$ 篇题解，第 $1$ 篇没有通过。

进入正题，题意就是具有相同奇偶性或两数的差小于 $1$ 就可以两两配对，看能不能全部配对。

一看我们就有思路了，第一种情况：如果奇数个数是偶数，偶数个数也是偶数那就可以直接配对，输出 ``YES`` 。
第二种情况：奇数个数是奇数，偶数数个数也是奇数，那么判断有没有两数的差小于 $1$ 的情况，如果有那就又回到了奇数个数是偶数，偶数个数也是偶数情况，输出 ``YES`` 。
第三种情况：判断所有数能不能都符合两数的差小于 $1$ ，如果能那直接配对，输出 ``YES`` 。
因为奇偶数的数量只有一样且都是偶数，一样且都是奇数和数量不同三种情况，前两种情况前面说过，而第三种情况显然是不可能按照奇偶判断的，只能寄希望于差小于 $1$ 全部配对的情况，也就是上面说的第三种情况。
那么我们就可以知道，如果都不行就只能输出 ``NO`` 了。

然后用上述思路写出代码：
```cpp
#include<iostream>
#include<string>
#include<cmath>
#include<math.h>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<cstdlib>
#include<time.h>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int a[51];
int main(){
	int t,n,_1,_2,l;
	cin>>t;
	for(int i=1;i<=t;i++){
		l=0;
		cin>>n;
		_1=0;
		_2=0;
		for(int j=1;j<=n;j++){
			cin>>a[j];
			if(a[j]%2==0)_2++;//统计奇数，偶数数量
			else _1++;
		}
		if(_1%2==0&&_2%2==0){//第一种情况
			cout<<"YES"<<endl;
			l=1;
		}
		else if(_1%2==1&&_2%2==1){//第二种情况
			sort(a+1,a+n+1);
			for(int j=1;j<=n-1;j++){
				if(a[j+1]-a[j]<=1){
					cout<<"YES"<<endl;
					l=1;
					break;
				}
			}
		}
		if(l==0){//第三种情况
			sort(a+1,a+n+1);
			int sum=0;
			for(int j=1;j<=n-1;j++){
				if(a[j+1]-a[j]<=1){
					sum+=2;
				}
			}
			if(sum==n){
				cout<<"YES"<<endl;
				l=1;
			}
		}
		if(l==0)cout<<"NO"<<endl;
	} 
	return 0;//完结撒花
}
//求通过
```

---

