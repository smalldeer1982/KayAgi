# Clockwork

## 题目描述

你有一排 $n$ 个计时钟，其中第 $i$ 个时钟的初始时间为 $a_i$。每秒中，以下事件按顺序发生：

- 每个时钟的时间减少 $1$。如果任意时钟的时间变为 $0$，你将立即失败。
- 你可以选择移动到相邻的时钟或停留在当前时钟。
- 你可以将当前所在时钟的时间重置为其初始值 $a_i$。

注意上述事件按顺序执行。如果某个时钟的时间在某一秒变为 $0$，即使你可以在该秒移动到这个时钟并重置其时间，你仍会失败。

你可以从任意时钟开始。请判断是否能够无限持续这个过程而不失败。

## 说明/提示

第一个测试用例中，你可以在两个时钟之间来回移动并反复重置它们的时间。

第三个测试用例中，假设你从时钟 $1$ 开始并采用以下策略：

初始时 $a = [4, 10, 5]$：
1. $a$ 变为 $[3, 9, 4]$。你移动到时钟 $2$ 并重置其时间，得到 $a = [3, 10, 4]$。
2. $a$ 变为 $[2, 9, 3]$。你移动到时钟 $3$ 并重置其时间，得到 $a = [2, 9, 5]$。
3. $a$ 变为 $[1, 8, 4]$。你移动到时钟 $2$ 并重置其时间，得到 $a = [1, 10, 4]$。
4. $a$ 变为 $[0, 9, 3]$。你试图移动到时钟 $1$，但由于 $a_1$ 变为 $0$ 而失败。

可以证明不存在其他策略能够无限持续该过程。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
2
4 10
2
2 2
3
4 10 5
3
5 3 5
5
12 13 25 17 30```

### 输出

```
YES
NO
NO
YES
YES```

# 题解

## 作者：ryf2011 (赞：2)

# 题目思路
对于每个时钟，我们要考虑最坏的情况，即从当前时钟出发，往左或往右走到头，再走回来，如果这种情况所需的时间大于或等于当前时钟时间，那么总有一刻会输掉，因为任何一个时钟都不能不被走到，都需要被重置，才能保证不输。

如果全部遍历完成后，仍然没输，那么说明可以无限期不输，按照对应格式输出即可。

# 代码
注：本代码仅供参考。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int t,n,a[500005];
bool f;
int main(){
	scanf("%d",&t);
	for(int z=1;z<=t;z++){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		f=true; //将 f 重设为 true 
		for(int i=1;i<=n;i++){
			//如果往左走回来的次数大于或等于 a[i] 或往右走回来的次数大于或等于 a[i]，说明走回来之后 a[i] 将变为 0，将会输掉 
			if((i-1)*2>=a[i]||(n-i)*2>=a[i]){ 
				f=false;
				printf("NO\n");
				break;
			}
		}
		if(f==true){ //如果一直没有退出循环，说明不会输 
			printf("YES\n");
		}
	} 
	return 0;
} 
```

#### 后记
更多内容，请移步至 [$\color{red}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：BinaryPotatoTree (赞：2)

## 题意简述

有 $n$ 个时钟，每个时钟的初始时间为 $a_i$。

你可以选择在任意时钟开始。每秒内：

- 每个时钟的时间减少 $1$。
- 你可以移动到相邻的时钟，或者停留在当前所在的时钟上。
- 你可以将当前所在的时钟的时间重置为 $a_i$。

询问是否能使所有时钟的时间永不为 $0$。

## 思路分析

对于每个时钟，它的时间要足够遍历并重置在它左边和右边的时钟，并重置自己的时间，即：

$$a_i>2\times\max\{i-1,n-i\}$$

~~口胡~~反证：如果不遍历并重置在当前时钟左边或右边的某个时钟 $C$，时钟 $C$ 的时间最终也会达到 $0$。

## 程序实现

遍历，判断是否所有 $a_i$ 都符合标准即可。

---

## 作者：Lovely_Elaina (赞：2)

笑嘻了，赛时被卡了一下。比 C 难解释但比 C 简单。

建议根据结论自行模拟样例，去思考反证。

显然我们进行循环操作（即从第一个到最后一个再到第一个循环）。

如果不这么操作，对于一个不常操作的时间，在有穷次操作后，总需要移动到这个时间，此时对于常常操作的时间相当于进行循环操作时需要等待的时间（因为时间不可无限累计，只能恢复到一个值）。

那么我们考虑需要等待的最大时间。

对于端点，显然需要等待 $2\times(n-1)$ 个时间单位。推广到其他点，不难发现对于第 $i$ 个点，最大需要等待 $2\times\max(i-1,n-i)$ 个时间单位。

那么一一比较是否可以等待这么多时间即可。

```cpp
#include <bits/stdc++.h>
// #define int long long
#define endl '\n'
using namespace std;
const int N = 5e5+5;
 
int n,a[N];
 
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin >> T;
    while(T--){
        cin >> n;
        bool b = true;
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            if(a[i] <= 2*max(i-1,n-i))
                b = false;
        }
        if(b) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    
    return 0;
}
```

---

## 作者：zjinyi (赞：1)

# 题解：CF2062B 时钟问题
## 题目分析
为了让每一个钟的时间都大于 $0$，你要一直在每个时钟之间移动，重置钟的时间。

对于第 $i$ 个钟，如果这个钟的时间要在你遍历一遍之后还大于 $0$，那初始时间 $a_i$ 必须大于 $2 \cdot \max(i - 1, n - i)$。

注：$i - 1$ 是从第 $i$ 个钟往左到第 $1$ 个钟所需的时间。同样，$n - i$ 是从第 $i$ 个钟往右到第 $n$ 个钟所需的时间。

## 代码
杜绝抄袭，从我做起！
```cpp
#include <iostream>
using namespace std;

long long a[500005];
int main()
{
	long long t;
	cin >> t;
	while (t--) // 多组数据 
	{
		long long n;
		cin >> n; // 输入 
		for (long long i = 1; i <= n; ++i)
		{
			cin >> a[i];
		}
		bool flag = true;
		for (long long i = 1; i <= n; ++i) // 遍历 
		{
			if (a[i] <= 2 * max(i - 1, n - i)) // 判断是否符合要求 
			{
				flag = false; // 不符合要求 
			}
		}
		if (flag == true) // 输出答案 
		{
			cout << "YES\n";
		}
		else
		{
			cout << "NO\n";
		}
	}
	
	return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：1)

## 思路
这道题首先要发现所有钟表是排成一列的，如果要使一个钟表能够一直不为零，就要让每次复位的操作变为可循环的。

因此，我们就要考虑对于每一次复位的操作，指针总需要到达端点一次才能够返回，否则操作是无效的。假设当前位置为 $i$，则到达左端点再返回需要 $2\times (i-1)$ 步。到达左端点再返回则需要 $2\times (n-i)$ 步。如果一个钟表等不到 $\max(2\times (i-1),2\times (n-i))$ 的时间就归零了，那么游戏必然失败。我们只需要在读入的过程中判断即可。
## 代码
代码非常简单，重点是思路。

[AC记录](https://codeforces.net/contest/2062/submission/304712220)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[500005];
int main(){
	int T;
	cin>>T;
	while(T--){
    	cin>>n;
    	bool fl=0;
    	for(int i=1;i<=n;i++){
    		cin>>a[i];
    		if(a[i]<=2*max(i-1,n-i)) //等不到了 
    			fl=1;
		}
		if(fl==0)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}
```

---

## 作者：wuzebang2009 (赞：1)

## CF2061B Clockwork

### 题目意思
有  $n$  个时钟，每个时钟的时间为 $$a_i$$ $$(1\le{i}\le{n})$$ 。

每次会有三个情况发生：

1. 每个时间时钟减少 $1$ ，如果有一个时钟时间为 $0$ ，那么就输了。
2. 移动到相邻时钟或者不动。
3. 将所在位置的时钟调回初始值 $$a_i$$ 。

### 思路
对于每一个时钟 $i$ 它从 $1$ 到 $i$ 来回所需时间为 $2(i-1)$ 从 $i$ 到 $n$ 来回所需时间为 $2(n-i)$ 。

只要我们保证每一个 $$a_i > 2\max(i-1,n-i)$$ ，就可以实现从 $1$ 到 $n$ 的循环了。

### CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int a[500010],d[500010];

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        if(a[i]<=2*max(i-1,n-i)) {
            cout<<"NO"<<endl;
            return;
        }
    }
    cout<<"YES"<<endl;
    return;
}

int main(){
    cin>>t;
    while(t--) solve();
}
```

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF2062B)

很明显一直往一个方向移动直到移动到底的时候是最优的，因为肯定对于每个时钟都要重置，中途折返回去重置还要再返回来，这样会导致多走一段路浪费时间而且只让别的时钟时间编得更少。

于是只需要判断对于每个时钟从它开始走到 $1$ 再折返回来或走到 $n$ 在折返回来花的时间是否大于等于 $a_i$，如果有任意一个时钟是，那么就说明它必然会在后面的某一时刻变为 $0$，输出 `No`，否则输出 `Yes`。

很明显，满足上面条件的时钟不管最开始再哪它都可行，因为从任意一个时钟按照我们前面所设计的移动方案到这个时钟所花的时间必定小于等于这个时钟与相对应的时钟序列的某一端折返一趟所花的时间，这里的相对应的某一端是指任意一个时钟是在这个始终的左边还是右边，左边的话某一端是时钟 $1$，右边的话某一端是时钟 $n$。

# CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
int n;
int a[500010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) scanf("%d",&a[i]);
		int ans=1;
		for(register int i=1;i<=n;i++)
			if(2*(i-1)>=a[i]||2*(n-i)>=a[i]) ans=0;
		if(ans) puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：huanglihuan (赞：0)

### Solution
首先，最优方案一定是到头再回来，因为这样可以更多的时钟时间尽量多，那么一个钟如果在一圈之后小于零了就算输，而要到 $i$ 最多要走 $\max(2\times(i-1),2\times(n-i))$ 即从头开始和从末尾过来两种情况，那么一旦 $a_i\le\max(2\times(i-1),2\times(n-i))$，则不可能实现。
### Code
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 988444333
#define MOD 1000000007
#define in(x,y,z) x>=y&&x<=z
using namespace std;
const int N = 2e6 + 5;
int a [N];
inline int read ()
{
	int x = 0;
	char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return x;
}
inline void write (int x)
{
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
void aread (int t)
{
	int x;
	while (t --) cin >> x;
	return ;
}
void solve ()
{
	int n;
	cin >> n;
	for (int i = 1;i <= n;i ++)
	{
		int x;
		cin >> x;
		if (x <= 2 * max (i - 1,n - i))
		{
			cout << "NO\n";
			aread (n - 1);
			return ;
		}
	}
	cout << "YES\n";
}
signed main ()
{
	int T;
	cin >> T;
	while (T --) solve ();
	return 0;
}
```

---

## 作者：lylcpp (赞：0)

## 思路

因为每次只能移动到相邻的时钟上，所以我们可以开始推理。

很显然到 $i$ 号时钟需要 $i-1$ 个单位时间，而从 $i$ 到 $n$ 号时钟需要 $n-i$ 个单位时间，而我们还需要处理来回，所以都要乘 $2$，而最终，如果

$a_i > \max(2(i-1), 2(n-i)) = 2 \times \max(i-1, n-i)$

只要对于任意的 $i$ 满足上面的式子，那么我们就能做到在 $1$ 号时钟和 $n$ 号时钟之间来回切换。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>

using namespace std;

int t, n, a[500005];

signed main() {
	scanf("%d", &t);
	while (t--) {
		bool flag = 1;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) {
			if (a[i] <= 2 * max(i - 1, n - i)) {
				printf("NO\n");
				flag = 0;
				break;
			}	
		} 
		if (flag) printf("YES\n");
	}
	return 0;
}
``````

---

## 作者：FXLIR (赞：0)

### 思路
首先，对于一个钟，应在某次重置这个钟的时间后，尽可能地重置更多钟的时间，然后再回来重置这个钟的时间。

推广到所有钟，即，若想要无限继续这个过程，最优的重置方案应为：从第 $1$ 个钟至第 $n$ 个钟依次重置，再从第 $n$ 个钟至第 $1$ 个钟依次重置。

然后，考虑如何判断能否无限期继续这个过程。不难发现，若一个钟的初始时间小于等于上面重置方案两次重置之间的间隔时间，则无法无限继续这个过程。

也就是说，若存在一个 $a_i$，使得 $a_i \leq \max(2(i-1),2(n-i))$，则输出 `NO`，反之输出 `YES`。
### AC code
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=5e5+5;
int t,n,a[N];
bool check(){
	for(int i=1;i<=n;i++){
		if(a[i]<=max((i-1)*2,(n-i)*2)){
			return 0;
		}
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		cout<<(check()?"YES\n":"NO\n");
	}
	return 0;
}

```

---

## 作者：The_jester_from_Lst (赞：0)

先来个警示后人：这堆钟排成的是一行，不是一个环。

考虑一个序列合法的条件：即对于每个钟，它去经过一遍其他所有钟回来，还有时间再救自己一把。如果它的指针值不支持它这样走一遍，那么为了不让它寄掉，必有一些钟无法到达。而这些无法到达的钟不久也会寄掉。

那就可以直接判合法了：一个序列合法，当且仅当对于每个 $a_i$，都有：

$$(a_i-1)/2\geq\max(n-i,i-1)$$

否则不合法。

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define pii pair<int,int>
#define mk make_pair
#define fir first
#define sec second
#define pb emplace_back
#define mod 1000000007
#define put putchar
using namespace std;
il int rd(){
    int jya=0,tl=1;char jyt=getchar();
    while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
    while(isdigit(jyt)){jya=(jya<<1)+(jya<<3)+(jyt-'0');jyt=getchar();}
    return jya*tl;
}
il void wr(int jjy){
    if(jjy<0)putchar('-'),jjy=-jjy;
    if(jjy>9)wr(jjy/10);
    putchar(jjy%10+48);
}
const int JYAAKIOI=1e18,N=1e6+86,M=2e5+86;
int T,n,a[N];
signed main(){
	//freopen("csnm.in","r",stdin);
	//freopen("csnm.out","w",stdout);
	T=rd();
	while(T--){
		n=rd();
		for(int i=1;i<=n;++i)a[i]=rd();
		if(n==2){
			if(a[1]>2&&a[2]>2)puts("YES");
			else puts("NO");
			continue;
		}
		bool p=0;
		for(int i=1;i<=n;++i){
			if((a[i]-1)/2<max(n-i,i-1)){
				p=1;
				puts("NO");
				break;
			}
		}
		if(!p)puts("YES");
	}
    return 0;
}
```

---

