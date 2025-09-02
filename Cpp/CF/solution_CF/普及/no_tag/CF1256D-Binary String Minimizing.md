# Binary String Minimizing

## 题目描述

给定一个长度为n的二进制串(即由n个'0'和'1'构成的字符串)，你最多可以进行k次交换相邻两个字符的操作。

一共q组询问。

## 样例 #1

### 输入

```
3
8 5
11011010
7 9
1111100
7 11
1111100
```

### 输出

```
01011110
0101111
0011111
```

# 题解

## 作者：theb0t (赞：3)

贪心。

数据范围 $n \le 10^{6}$，因此我们要用时间复杂度为 $\mathcal{O}\left( n \right)$ 的算法来解决这个问题。

# 思路

从左至右扫一遍序列，如果遇到 $10$，则要将这个 $0$ 交换到前面的位置。由于是字典序最小，$0$ 应该尽量在最高位。现在需要知道这个 $0$ 被交换到哪个位置，因此我们有变量 $t$ 来记录下一个 $0$ 所在的位置。

记刚才找到的 $10$ 的 $0$ 的位置为 $i$。则要交换 $i-t$ 次，我们只需要判断 $k\ge i-t$ 是否成立即可。

如果成立，则直接交换，将序列的第 $t$ 个位置置为 $0$，第 $i$ 个位置，置为 $1$。这样成立的原因是因为序列的第 $t$ 到 $i-1$ 这些位置的数不可能有 $0$，因此我们并不需要去移动，直接 $\mathcal{O}\left( 1 \right)$ 交换即可。

如果不成立，则尽量向前交换，将序列的第 $i-k$ 个为位置置为 $0$（还能交换 $k$ 次），第 $i$ 个位置置为 $1$，这样做的正确性与上文相同。

# 代码

注意小特判：如果序列的前面一段都是 $0$ 则 $t$ 的初始值应为这一段的最后一个位置 $+1$。

开 `long long` 否则爆炸，$n^{2}\ge 2147483647$。$2147483647$ 为 `int` 最大值。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,k,t;
const int maxn=1e6+5;
int a[maxn];

void Main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		char ch;
		cin>>ch;
		a[i]=ch-'0';
	}
	int t=1,g=1;
	while(a[g]==0) t++,g++;
	for(int i=2;i<=n;i++){
		if(a[i-1]==1&&a[i]==0){
			if(k>=i-t){
				k-=i-t;
				a[t]=0,a[i]=1;
				if(k==0) break;
				t++;
			}
			else{
				a[i-k]=0,a[i]=1;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<a[i];
	cout<<"\n";
}
signed main(){
	int T;
	cin>>T;
	while(T--) Main();
	return 0;
}
```

---

## 作者：installb (赞：2)

Codeforces Round #598 (Div. 3) D  

字典序最小值 这算是一种常见贪心模型吧  

这题和这场比赛的B完全是一模一样的思想  

显然如果第一位是$0$ 那么一定是比所有第一位是$1$的方案优的  
如果最左边一位已经确定 那么对于次高位 次高位为$0$的**任意**方案 一定比次高位为$1$的**所有**方案优  

这里先不管$1$怎么样 我们需要通过操作把$0$尽量往前移  
交换两个相邻数等同于把一个$0$往前移一位 如果这个$0$的前面是$0$ 这步操作是没有意义的 所以我们只会把**前一位为1的0**往前移 $1$在什么位置无所谓  

由于高位对字典序的决定性高于低位(见上文) 然后我们每一次选择最左边的$0$ 把它移到第1位 再选择次左边的 移动到**第2位** 以此类推 直到某一步剩余步数不足 把当前处理的$0$移到能移到的最左边位置 结束  

具体实现详见代码 这里我记录了所有$0$原来的位置 方便处理

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
typedef long long LL;

string s,t;
LL T,n,k;
LL zer[2000005],zc;

int main(){
	cin >> T;
	while(T --){
		zc = 0;
		cin >> n >> k; cin >> s;
		for(LL i = 0;i < n;i ++){
			if(s[i] == '0') zer[zc ++] = i;
            // 保存所有0的位置
		}
		for(LL i = 0;i < zc;i ++){
        // 这里从0开始了 第几个零和第几个位置都从0开始
			if(k >= zer[i] - i){
            k -= (zer[i] - i);
            zer[i] = i;
            // 这里第i个1需要移动到第i位 算出需要移动的步数 查看是否足够
            // 直接改变0的位置
         }
			else {
				zer[i] -= k; //剩余步数不足 当前零前移k位
				k = 0;
			}
		}
		t = s; for(LL i = 0;i < n;i ++) t[i] = '1';
		for(LL i = 0;i < zc;i ++) t[zer[i]] = '0';
     // 剩下位置全填1
		cout << t << endl;
	}
	return 0;
}
```

---

## 作者：small_turtle (赞：0)

因为要让字典序最小，所以要尽可能让 `0` 移到前面去，预处理每个 `0` 的位置，使最好移的都排在前面，最后扫一遍字符串即可。

**注意要开 long long。**

CODE:
```cpp
/*
Author:xwg
Time:2022.11.9
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define unordered_map map
const int inf=2147483647;
const double eps=1e-6;
using namespace std;

const int MAXN=1e6+5;
ll t,n,k,top,a[MAXN],s[MAXN];
char tmp;

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
	top=0;//清空
        for(int i=0;i<n;++i)
        {
            cin>>tmp;
            if(tmp=='0')
            {
                a[top++]=i;
            }
        }
        for(int i=0;i<top;++i)
        {
            if(k>=a[i]-i)
            {
                k-=a[i]-i;
                a[i]=i;
            }
            else
            {
                a[i]-=k;
                k=0;
            }
        }
        for(int i=0;i<n;++i)
        {
            s[i]=1;
        }		
		for(int i=0;i<top;++i)
        {
            s[a[i]]=0;
        }
        for(int i=0;i<n;++i)
        {
            cout<<s[i];
        }
		cout<<"\n";
    }
	return 0;
}
```

---

## 作者：3a51_ (赞：0)

暴力算法 $O(qnk)$ 肯定超时。

考虑优化，用一个 $\texttt{tot}$ 变量来储存第一个 $1$ 的位置。然后从头到尾扫一遍，如果当前为 $0$，判断一下 $\texttt{tot}$ 与当前的 $0$ 需要交换的次数是否 $>k$。

- 如果 $>k$，那么交换到 $k=0$ 为止然后`break`即可。

- 否则，交换完毕后继续交换。

如果对于思路有疑问可以看代码或私信我。

**Code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int Mod1=998244353;
const int Mod2=1000000007;
int gcd(int a,int b){return __gcd(a,b);}
int lcm(int a,int b){return a*b/gcd(a,b);}
void read(int &x){x=0;char ch=' ';while(ch>'9' || ch<'0'){ch=getchar();}while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}return;}
void write(int x){if(x>9){write(x/10);}putchar(x%10+'0');return;}
int q,n,k,tot;
signed main()
{
	read(q);
	for(int i=1;i<=q;i++){
		tot=0;//哪怕s[0]不是1那么第一个枚举到的自己和自己交换下面的j>tot也能判断出来。
		read(n);read(k);
		string s;cin>>s;
		for(int j=0;j<s.size();j++){
			if(s[j]=='0' && j>tot){//如果说当前位置为0
				if(j-tot<=k){//判断距离<=k
					swap(s[j],s[tot]);//交换
					k-=(j-tot);//消耗步数。
					tot++;//位置后移1位，如果后移一位为0那么就直接判断出来了。所以后移一位肯定是1
				}else{
					swap(s[j],s[j-k]);//否则直接交换就行了。
					k=0;//清空，可以不写。
				}
			}
		}
		cout<<s<<endl;//输出字符串，多组数据记得换行。
	}
	return 0;
}

```

---

## 作者：lsr1409111459 (赞：0)

#### 1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1256D)）

##### 1.1 题目大意

给你一个长度为 $n$ 的二进制串，要求你最多进行 $k$ 次交换相邻两个字符的操作，使得操作后的字符串字典序最小。共有 $q$ 组提问。

##### 1.2 输入格式

第一行一个整数 $q(1\leq q \leq 10^4)$ 。

对于每组提问，第一行两个整数 $n,k(1 \leq n \leq 10^6,1 \leq k \leq n^2)$ 。分别表示二进制数的长度和允许的最大操作数。

第二行是一个由 $n$ 个' $0$ '或' $1$ '组成的字符串。为给定的二进制串。

##### 1.3 输出格式

共 $q$ 行。

每行一个长度为 $n$ 的二进制串，为最多 $k$ 次操作后字典序最小的二进制串。

#### 2 解题思路

贪心。字典序最小，我们需要让前面的数尽可能是 $0$ 。因此，我们的目标是将当前状态下的第一位 $1$ 变成 $0$ 。但是是用哪个 $0$ 去变这个 $1$ 呢？我们来考虑一个例子： $1010$ 。

如果我们用第一个 $0$ ，则可变成 $0110$ 。

如果我们用第二个 $0$ ，则需变成 $0011$ 。但我们发现，在这个过程中，其实是包含 $0110$ 这个过程的，即我们想变成 $0011$ ，就必须经历 $0110$ 。原因很简单，我们考虑第一个 $1$ ，要想变成 $0011$ ，它一定要向后动。它向后动的时候首先变成 $0110$ ，然后才会一点点变成 $0011$ 。

所以，虽然我们用第二个 $0$ 变成的 $0011$ 比用第一个 $0$ 变成的      $0110$ 字典序要小，但是变 $0011$ 的过程可以视作先变成 $0110$ ，再用第一个 $0$ 去替换第一个 $1$ ，将其分解成两部分。因此，我们每一步做的都是将当前状态下第一个 $1$ 和第一个 $0$ 进行交换。

最后考虑 $k$ 这个量。我们每次大交换其实都进行了第一个 $0$ 的下标减第一个 $1$ 的下标的小交换。因此我们只需要判断当前 $k$ 值支不支持我们进行这样的大交换。如果支持，我们直接进行交换，然后修改 $k$ 的值。如果不支持，则将当前状态的第一个 $0$ 尽可能的往前移，用光所有操作次数为止。

#### 3 解题代码

```cpp
#include <iostream>
using namespace std;
int q,n;
long long k;
char s[1000010];
int main()
{
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%lld%s",&n,&k,s);
        int one=0,zero=0;
        while(one<n&&zero<n&&k)
        {
            while(s[one]=='0'&&one<n)one++;
            zero=max(zero,one);
            while(s[zero]=='1'&&zero<n)zero++;
            if(one>=n||zero>=n)break;
            if(zero-one<k)
            {
                s[one]='0';
                s[zero]='1';
                k-=(zero-one);
            }
            else
            {
                s[zero-k]='0';
                s[zero]='1';
                k=0;
                break;
            }
        }
        printf("%s\n",s);
    }
    return 0;
}
```

#### 4 解题心得

代码部分没有写注释，按照思路模拟即可。

 $zero$ 要取 $zero$ 和 $one$ 中大的那个，否则如果只取 $one$ 的话会    $TLE$ 。

开 $long\ long$ ，开 $long\ long$ ，开 $long\ long$ 。 $k$ 到 $n^2$ ，没开 $long\ long$ 调了半个小时。

---

## 作者：KaguyaH (赞：0)

> [CF1256D](https://www.luogu.com.cn/problem/CF1256D)

### 题目分析

一个比较显然的贪心思路是：从前向后枚举 $0$，每次遇到 $0$ 就尽量前移。

> #### 易证：
>
> 1. 这样做可以使前缀 $0$ 最多。
> 2. 在 1 的条件下满足操作次数最少，下一个 $0$ 可以尽量前移。
>
> #### 简单的证明：
>
> 假设我们枚举到了位置 $i$ 的 $0$，我们能够把这个 $0$ 移到前缀 $0$ 的末尾，那我们移动后的操作次数就是原序列 $s_{[1, i]}$ 的逆序对数。
>
> 而移动后的序列 $t_{[1, i]}$ 形如 $000\cdots0111\cdots1$，是有序的，故通过交换操作把 $s$ 变为当前的 $t$ 所需操作次数至少为 $s_{[1, i]}$ 的逆序对数。
>
> 而当 $k > 0$ 且我们枚举到的 $0$ 无法前移至前缀 $0$ 中，我们就将其前移 $k$ 次，使字典序最小。

我们考虑，在 $k > 0$ 时如何这样移动。

由于我们尽量前移，而 $k > 0$，所以我们可以知道，当前 $0$ 的前面是 $000\cdots0111\cdots1$ 的形式。

我们可以记录一个 $l$ 值表示 $111\cdots1$ 的左端点（若没有 $1$ 则为当前位置），设当前 $0$ 的位置为 $i$：

- 若 $k > i - l$，则交换 $s_l, s_i$，$l \leftarrow l + 1$，$k \leftarrow k - (i - l)$；
- 否则，交换 $s_{i - k}, s_i$，$k \leftarrow 0$，$l$ 以后用不到，我们并不关心怎么处理 $l$。

上述过程已经可以通过本题，但可以简化。

我们考虑，我们对这个 $0$ 所做的前移次数为 $\min(k, i - l)$，记为 $t$，则我们可以

交换 $s_i, s_{i - t}$，$k \leftarrow k - t$，$l \leftarrow i - t + 1$。

### Code

下标从 $0$ 开始。

```cpp
# include <cctype>
# include <cstdio>

namespace Main {
    namespace Source {
        typedef short unsigned int hu;
        typedef unsigned int uint;
        typedef long long unsigned int llu;
        static inline bool read() {
            char t;
            while (isspace(t = getchar()));
            switch (t) {
            case '0': return false;
            case '1': return true ;
            default : puts("Error!"); return false;
            }
        }
        static inline bool& read(bool& a) { return a = read(); }
        static inline const void write(const bool a) { putchar(a ? '1' : '0'); }
        static inline const void enter() { putchar('\n'); }
        static inline const llu min(const llu a, const llu b) { return b < a ? b : a; }
        static inline const void swap(bool& a, bool& b) {
            const bool c(a);
            a = b, b = c;
        }
    }
    using namespace Source;
    namespace Solve {
        enum { N = (const uint)1e6 };
        static uint n; static llu k;
        static bool s[N + 1];
        static inline const void main() {
            scanf("%u%llu", &n, &k);
            for (register uint i(0), l(0); i < n; ++i) {
                if (read(s[i]) or !k) continue;
                const uint t(min(k, i - l));
                swap(s[i], s[i - t]), k -= t, l = i - t + 1;
            }
            for (register uint i(0); i < n; ++i) write(s[i]);
            enter();
        }
    }
    static hu q;
    static inline const void main() {
        scanf("%hu", &q);
        for (register hu i(0); i < q; ++i) Solve::main();
    }
}

signed int main() { Main::main(); return 0; }
```

---

## 作者：AntiO2 (赞：0)

### Easy peasy, lemon-squeasy

(感觉和B题一样的)

因为是交换相邻的两个数，所以消耗x步可以让一个数字往前移动x格

显然要字典序最小得尽量把0放在前面，所以跑一遍字符串。如果当前数字为0则把它尽量往最前面移动。

```cpp
#include<bits/stdc++.h>
#define debug cout<<"debug"<<endl;
using namespace std;

int main() {
	long long n,k,q;
	cin>>q;
	while(q--) {
		cin>>n>>k;
		string s;
		int cnt = 0;
		cin>>s;
		for(int i = 0; i < n; i++) {
			if(!k) break;
				if(s[i]=='0') {
					if(k>=i-cnt) {
						k-=(i-cnt);
						swap(s[cnt], s[i]);
						cnt++;
					}
					else {
						swap(s[i-k],s[i]);
						k = 0;
					}
				}
		}
		cout<<s<<endl;
	}
	return 0;
}

```




---

