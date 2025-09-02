# [GCJ 2010 Qualification] Snapper Chain

## 题目描述

Snapper 是一种巧妙的小装置，一端将其输入插头插入输出插座，另一端则暴露一个输出插座，可以插入灯泡或其他设备。

当 Snapper 处于 ON 状态且其输入插头正在接收电源时，连接到其输出插座的设备也会获得电源。当你打响指——发出咔哒声时，任何正在接收电源的 Snapper 都会在 ON 和 OFF 状态之间切换。

为了通过奇点摧毁宇宙，我购买了 $N$ 个 Snapper，并将它们串联起来，第一个插入电源插座，第二个插入第一个，依此类推。灯泡插在第 $N$ 个 Snapper 上。

最初，所有 Snapper 都处于 OFF 状态，因此只有第一个 Snapper 从插座接收电源，灯泡是熄灭的。我打响指一次，第一个 Snapper 切换到 ON 状态，并为第二个 Snapper 供电。我再次打响指，两个 Snapper 都切换状态，随后第二个 Snapper 断电，保持在 ON 状态但没有电源。我第三次打响指，第一个 Snapper 再次切换状态，并为第二个 Snapper 供电。现在两个 Snapper 都处于 ON 状态，如果我的灯泡插在第二个 Snapper 上，它就会亮。

我这样持续打响指数小时。打响指 $K$ 次后，灯泡是亮着还是灭着？只有当灯泡从其插入的 Snapper 获得电源时才会亮。

## 说明/提示

**数据范围**

- $1 \leqslant T \leqslant 10\,000$。

**小数据集（10 分，测试集 1 - 可见）**

- $1 \leqslant N \leqslant 10$；
- $0 \leqslant K \leqslant 100$；

**大数据集（23 分，测试集 2 - 隐藏）**

- $1 \leqslant N \leqslant 30$；
- $0 \leqslant K \leqslant 10^{8}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 0
1 1
4 0
4 47```

### 输出

```
Case #1: OFF
Case #2: ON
Case #3: OFF
Case #4: ON```

# 题解

## 作者：__CuSO4__ (赞：2)

### 题解：

这是一道结论题。

把 $n$ 个灯的状态视为一个 $n$ 位的二进制数（第一个灯对应**个位**），可以发现，每次操作就相当于对这个数加上了 $1$，比如，当 $n=4$ 时：

- $k = 0$ 时，二进制表示为 `0000`。
- $k = 1$ 时，二进制表示为 `0001`。
- $k = 2$ 时，二进制表示为 `0010`。
- $k = 3$ 时，二进制表示为 `0011`。
- $k = 4$ 时，二进制表示为 `0100`。

所以，我们发现，$k$ 的二进制的后 $n$ 位就对应了所有灯的状态，当它们全为 $1$ 时，第 $n$ 个灯泡就可以点亮，满足条件。

所以当 $k \bmod 2^n = 2^n-1 $ 时，满足条件。

### Code：
``` cpp
#include<iostream>
using namespace std;

int main(){
    long long T,n,k;
    cin>>T;
    for(int i=1;i<=T;i++){
        cin>>n>>k;
        if (k%(1ll<<n)==(1ll<<n)-1) printf("Case #%d: ON\n",i);
        else printf("Case #%d: OFF\n",i);
    }
    return 0;
}
```

---

## 作者：jojo_fan (赞：1)

## 问题分析
 Snapper 链的状态变化呈现二进制计数特征：\
每个 Snapper 相当于二进制的一位，每次响指相当于二进制数，灯泡亮起当且仅当前 $N$ 位全为 $1$（即 $K \bmod 2^N = 2^N-1$）。

## 解题思路
计算 $2^N$ 的值检查 $K$ 是否满足 $(K+1) \bmod 2^N = 0$ 或者等价判断 $ K \operatorname{and} (2^N -1)= 2^N - 1$。
## 代码

```cpp
#include"bits/stdc++.h"
#define ll long long
using namespace std;

int T;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	for(int t=1;t<=T;t++)
	{
		int n,k;
		cin>>n>>k;
		int m=(1<<n)-1;
		cout<<"Case #"<<t<<": "<<(((k&m)==m)?"ON":"OFF")<<'\n';
	}
	return 0;
}

```

---

## 作者：x_Toi_QiQi (赞：1)

## 解题思路：
题目要求时在打 $k$ 个响指有 $n$ 个灯泡是否全部亮着？如果我们去硬模拟，肯定是过不了的，具体数据范围看题目。

因为样例过于大，所以我们要找到一种更快速的方法，这时候就可以来看 $k$ 的二进制的状态，一下我们用 $n=3$ 来看 $k$ 的变化：

当 $k=1$ 时，二进制为 $001$。

当 $k=2$ 时，二进制为 $010$。

当 $k=3$ 时，二进制为 $011$。

当 $k=4$ 时，二进制为 $100$。

当 $k=5$ 时，二进制为 $101$。

当 $k=6$ 时，二进制为 $110$。

当 $k=7$ 时，二进制为 $111$。

转成二进制后我们可以发现，二进制中如果第 $i$ 位为 $1$ 代表第 $i$ 盏灯是亮着的，所以只要 $k$ 的二进制的前 $n$ 位都 $1$ 就代表，前 $n$ 位都是亮的，就满足题意。

## code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define endl "\n"
#define pii pair <int, int>

int main() {
	int t;
	cin >> t;
	
	for (int c = 1; c <= t; ++c) {
		int n, k;
		cin >> n >> k;
		
		int temp = (1 << n) - 1; // 创造一个前n位都是1的数（在10进制中不是全是1，但在二进制中是） 
		
		bool flag = false;
		if ((k & temp) == temp) flag = true; // 这里应为是与运算，只有k中有一位不为1，那么整个数就不是全部亮着的，应为这里的temp前n位都是1，所以不用一个一个比较 
		
		cout << "Case #" << c << ": " << (flag == false ? "OFF" : "ON") << endl;
	}
	
	return 0;
}
```

---

## 作者：wenhaoran11 (赞：1)

## 思路
我们可以把 $n$ 个灯的状态用一个长度为 $n$ 的二进制来表示，每次操作把它打开相当于把那个位置上的数变成了一。

接着我们不难发现，二进制串的后 $n$ 为就对应了所有灯的状态，当他们全为一时，就满足条件。

所以我们只要算出来 `(k & ans)` 的结果是不是等于 `ans` 就行了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,t=0,n,k;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		t++;
		cin>>n>>k;
		int cnt=(1<<n)-1;//1<<n要加括号，因为优先级太低了。 
		if((k&cnt)==cnt) printf("Case #%d: ON\n",t);//k&ans也是一样的。 
		else printf("Case #%d: OFF\n",t);
	}
	return 0;
}
```

---

## 作者：qwq_Furry (赞：1)

## 题目简述
 - 第一个开关在每一个时刻都会发生变化，初始为 OFF。
 - 其余开关只有当前面的所有开关都是 ON 的时候才会发生变化。

## 解题思路
### 第一步
 - 看到标签是数学与位运算，然后再看到题目，我们可以使用找规律的方法去做题。

### 第二步
 - 我们先设 $n$ 等于 $1$ 的情况下，$k$ 的数值对结果有什么影响，所以我们可以列出表格：



|$k$ 的数值（操作次数）|灯泡状态|用二进制去表示|
|:-:|:-:|:-:|
|$0$|OFF|$0$|
|$1$|**ON**|$1$|
|$2$|OFF|$0$|
|$3$|**ON**|$1$|

可以发现，当 $k \bmod 2 = 1$ 时，灯泡状态是 ON，否则为 OFF。

周期是：$2^1$。

 - 然后设 $n$ 等于 $2$ 的情况下，$k$ 的数值对结果有什么影响，所以我们可以列出表格：



|$k$ 的数值（操作次数）|装置 $1$ 的状态|装置 $2$ 的状态|灯泡状态|用二进制去表示|
|:-:|:-:|:-:|:-:|:-:|
|$0$|OFF|OFF|OFF|$00$|
|$1$|ON|OFF|OFF|$01$|
|$2$|OFF|ON|OFF|$10$|
|$3$|**ON**|**ON**|**ON**|$11$|
|$4$|OFF|OFF|OFF|$00$|
|$5$|ON|OFF|OFF|$01$|

至于为什么当 $k$ 为 $1$ 时是 $01$ 而不是 $10$，是因为二进制和十进制一样，最右边数第一个是第一位，并以此类推。

然后可以发现，每 $4$ 个之后就又循环了一遍，所以可以推断出其周期性为：$2^2$。

 - 为了更加理解，所以我们也可以设 $n$ 等于 $3$ 的情况：



|$k$ 的数值（操作次数）|装置 $1$ 的状态|装置 $2$ 的状态|装置 $3$ 的状态|灯泡状态|用二进制去表示|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$0$|OFF|OFF|OFF|OFF|$000$|
|$1$|ON|OFF|OFF|OFF|$001$|
|$2$|OFF|ON|OFF|OFF|$010$|
|$3$|ON|ON|OFF|OFF|$011$|
|$4$|OFF|OFF|ON|OFF|$100$|
|$5$|ON|OFF|ON|OFF|$101$|
|$6$|OFF|ON|ON|OFF|$110$|
|$7$|**ON**|**ON**|**ON**|**ON**|$111$|
|$8$|OFF|OFF|OFF|OFF|$000$|

可以发现，以 $8$ 个为 $1$ 个循环，其周期性为：$2^3$。

### 第三步
 - 我们总结发现，当 $k \bmod 2^n = 2^n - 1$ 时，这个灯泡的状态一定是 ON。

 - 所以我们只需要在每个测试数据当中，输入 $k, n$，然后判断即可。

## 时间复杂度及空间复杂度分析
按照此思路来写，时间复杂度为 $O(T)$，题目限制是 $1 \le T \le 10000$，可以通过此题目。

按照此思路来写，空间复杂度为 $O(1)$，题目限制是 $1.00$ GB，可以通过此题目。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int T, pri = 1; cin >>T;
    while(T--) {
        long long n, k; cin >>n >>k;
        long long m = pow(2, n); //要开long long防止爆掉
        long long t = k % m;
        if(t == m - 1) {
            cout <<"Case #" <<pri++ <<": ON\n";
        }
        else cout <<"Case #" <<pri++ <<": OFF\n";
    }
}
```

---

## 作者：YuTinMin (赞：1)

## 思路

又来写题解了。

说真的看到这道题的时候还不会写，看到标签位运算时，就知道了。题目说的 `ON` 和 `OFF` 不就是 $1$ 和 $0$ 嘛。诶！那我就弄一个数 `ans`，用位运算左移给他弄成一个二进制全为 `ON` 而且转换成二进制是 `n` 位的数。你问我为什么？你想想。如果你要让 `n` 亮起来，是不是要前面 `n` 全亮才可以对吧，那就好搞了，算 `(k & ans)` 的结果是不是等于 `ans`。为什么呢？

我自己搞个样例，比如 $7$ 次响指，第 $3$ 盏灯。

![](https://cdn.luogu.com.cn/upload/image_hosting/mmq1jxbc.png)

图中可以看出，第三个是 $1$，所以答案是 `ON`。

然后自己看代码吧，就这样。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        int n, k;
        cin >> n >> k;
        int ans = (1 << n) - 1; //创建一个二进制全是1的数
        if ((k & ans) == ans) //如果刚好全是1，那就是说n可以亮起
            printf("Case #%d: ON \n", t);
        else
            printf("Case #%d: OFF \n", t);
    }

    system("pause");
    return 0;
}
```

---

## 作者：shihanyu2013 (赞：0)

## 思路
看完题目观察 $k$ 的二进制值，不难发现 $k$ 的每一位其实对应了每一个灯泡的状态，当第 $i$ 位是 $0$ 时对应第 $i$ 个 灯泡是断电的，否则为有电。要想让第 $n$ 个灯泡发光，应让每一位都为 $1$，即 $k \bmod 2^n=2^n-1$。

## 代码
```cpp
#include<iostream>
using namespace std;
int t,n,k;
int qpow(int a,int b){//快速幂
    int ans=1;
    while(b){
        if(b&1) ans*=a;
        a*=a;
        b>>=1;
    }
    return ans;
}
signed main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n>>k;
        cout<<"Case #"<<i<<": ";
        if((k+2)%(qpow(2,n))==1) {//判断
            puts("ON");
        } else {
            puts("OFF");
        }
    }
    return 0;
}
```

---

## 作者：wjh27465 (赞：0)

# 题解：P13387 [GCJ 2010 Qualification] Snapper Chain
## 分析
本题为一道数学题。  
令装置状态开为 $1$，装置状态关为 $0$。根据题目给的两个装置的例子寻找规律：  
打响指 $0$ 次，状态为`00`。  
打响指 $1$ 次，状态为`01`。  
打响指 $2$ 次，状态为`10`。  
打响指 $3$ 次，状态为`11`。  
容易发现，将装置状态看作二进制后，每多打一次响指，相当于在这个二进制数后面加一。我们继续枚举：  
打响指 $4$ 次，状态为`00`。  
打响指 $5$ 次，状态为`01`。  
打响指 $6$ 次，状态为`10`。  
打响指 $7$ 次，状态为`11`。  
打响指 $8$ 次，状态为`00`。  
打响指 $9$ 次，状态为`01`。  
打响指 $10$ 次，状态为`10`。  
打响指 $11$ 次，状态为`11`。  
只有当装置状态全为 $1$ 时，灯泡才能亮。在 $n=2$ 的情况下，当 $k$ 模 $4$ 余 $3$ 时成立。所以我们可以得出最终结论：当 $k$ 模 $2^n$ 余 $2^n-1$ 时，灯泡状态为`ON`，否则为`OFF`。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n,k;
        cin>>n>>k;
        int x=pow(2,n);
        if(k%x==x-1)
            cout<<"Case #"<<i<<": ON"<<endl;
        else
            cout<<"Case #"<<i<<": OFF"<<endl;
    }
    return 0;
}
```

---

## 作者：xiaowenxu_qwq (赞：0)

# 题目意思
给定正整数 $n$ 和 $k$，求 $k$ 在二进制下 1 到 $n$ 位是否都为 1。
# 思路
我们可以将 $k$ 转成二进制，判断一下 1 到 $n$ 位是否都为 1，如果是的话就输出 ON，否则输出 OFF。

$O(T \log k)$ 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*f;
}
void write(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else write(x/10),putchar(x%10+'0');
}
signed main()
{
	int T=read();
    int t=0;
    while(T--){
        t++;
        int n=read(),k=read(),i=0;
        bool book=1;
        while(k){
            if(k%2==0)book=0;
            k>>=1,i++;
            if(i==n||!book)break;
        }
        if(book&&i==n)printf("Case #%lld: ON\n",t);
        else printf("Case #%lld: OFF\n",t);
    }
	return 0;
} 
```
这样写出来的代码虽然可以通过此题，但并不是最优的解法。如果我们不是转换 $k$ 去检查是否合法，而是去将合法的答案算出来与 $k$ 进行比较。就可以通过计算机二进制计算的特性，以更快的速度求解出答案。

$O(T)$ 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*f;
}
void write(int x)
{
    if(x<0)putchar('-'),x=-x;
    if(x<10)putchar(x+'0');
    else write(x/10),putchar(x%10+'0');
}
signed main()
{
	int T=read();
    int t=0;
    while(T--){
        t++;
        int n=read(),k=read();
        int con=(1<<n)-1;
        if((k&con)==con)printf("Case #%lld: ON\n",t);
        else printf("Case #%lld: OFF\n",t);
    }
	return 0;
} 

```

---

