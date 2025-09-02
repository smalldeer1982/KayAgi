# Bit Guessing Game

## 题目描述

这是一道交互题。

Kira 和 Hayato 正在玩一种猜数游戏，Kira 想，Hayato 猜。

对于每一轮游戏，设 Kira 想的数为 $n$。初始时，Kira 会给出 $cnt$，表示 $n$ 的二进制中 $1$ 的个数。Hayato 只能进行以下两种操作：

1. `- x`：修改操作。Kira 会将 $n$ 减去 $x$（注意此处 $n$ 会被修改），并给出此时的 $cnt$。特别地，若 $x > n$，则 Kira 直接获胜。
2. `! x`：查询操作。Kira 会将 $x$ 与最初的 $n$ 对比，若二者相同则 Hayato 获胜，反之 Kira 获胜，这轮游戏立即结束。

他们一共会进行 $t$ 轮游戏，你需要帮助 Hayato 在每一轮中获胜。同时，Kira 并不是一个很有耐心的人，因此你进行操作 1 的次数不能超过 $30$。

注意样例中的空行只是为了显示更清晰，不会出现在实际评测中。

## 样例 #1

### 输入

```
3

1

0

1

1

0

2

1

0```

### 输出

```
- 1

! 1

- 1

- 1

! 2

- 2

- 1

! 3```

# 题解

## 作者：Feyn (赞：7)

考虑给这个数减去一个一会发生些什么。假设 $n=12$，那么 $(1100)_2\rightarrow(1011)_2$，二进制下一的个数从两个变成了三个，可以看成是有两位从零变成了一，有一位从一变成了零，这就意味着当前最低的一位 $1$ 在从低到高的第 $3$ 位上。于是就可以通过这种方式，每次询问找到当前最低一位 $1$ 的位置，这样就可以还原出原来的数了。

具体而言，维护一个指针 $p$，然后尝试让 $n$ 减去 $2^p$，并比较二进制一的个数的增量 $s$，根据上面的结论，这个指针向左挪动 $s+1$ 位就可以指向最低位的 $1$ 了。然后重复这一过程，直到找到所有的 $1$。容易发现原先的数每个 $1$ 都需要通过一次操作来定位，所以可以用 $30$ 次查询来找出这个数。

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
	int m=0,ans=0,pl=0,now=0;cin>>m;
	while(true){
		cout<<"- "<<(1<<pl)<<endl;
		int n;cin>>n;
		int del=n-m+1;while(del--)pl++;
		ans+=(1<<pl);
		if(n==pl)break;m=n;
	}
	cout<<"! "<<ans<<endl;
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	int test;cin>>test;
	while(test--)solve();
	
	return 0;
}
```

---

## 作者：InoueTakina (赞：5)

比较简单的题。

我们考虑每次去掉 $\operatorname{lowbit}$，一种 naive 的思路是：

1. 首先把原数字 $-1$。
2. 根据变化量来确定最低位并删除。

我们冷静一下，这个东西好像是 $2\times \log_{2} n$ 的。

一种最显然的优化是把上一次的操作 $2$ 和这一次的操作 $1$ 合并。但是笔者脑子不太好使，因此使用了另一种分析：

首先可以发现，如果我的操作 $1$ 刚好减掉了 $\operatorname{lowbit}$，那我根本不需要进行操作 $2$。

我们注意到，如果我们不进行 $-1$ 操作，而是 $- 2^{w+1}$，其中 $w$ 是上次删除的 $\operatorname{lowbit}$，那么就能保证对于连续的 $1$，我们对每个 $1$ 只需要进行一次操作。而不连续的 $1$ 中间至少隔了一个 $0$，因此最终次数 $< \log_2 n$。

老奶奶手速，没拿到一血。

```c++
#include<bits/stdc++.h>
using namespace std;
int n, cnt, ans, lst, T, now;
int query(int x) {
	cout << "- " << x << "\n"; fflush(stdout); int res; cin >> res; fflush(stdout); return res;
}
void solve() {
	cin >> cnt; ans = lst = now = 0;
	while(cnt) {
		lst = cnt; cnt = query(1 << now);
		if(lst > cnt) { ans = ans + (1 << now), now ++;}
		if(lst == cnt) {cnt = query(1 << now); ans = ans + (1 << (++ now)); now ++;}
		if(lst < cnt) {
			int ret = now;
			now += cnt - lst + 1; cnt = query((1 << now) - (1 << ret)); 
			ans = ans + (1 << now); now ++;
		} 
	} cout << "! " << ans << "\n"; fflush(stdout);
}
int main() {
	cin >> T; while(T --) solve();
}
```



---

## 作者：xgyxgy111 (赞：1)

~~ac 之后看了一眼题解，貌似没有和我一样的做法，所以这里给出一个新的思路以纪念本蒟蒻第一次独自 ac 1800~~

审核大大辛苦了，求过~

首先题目中出现不得超过 $30$ 次询问，而数据范围是 $10^9$ 这显然在暗示我们需要一个 $\log n$ 的解法，由于询问到超过原本的数就会寄掉，那么我们考虑从最小的 $1$ 开始，然后是 $2, 4, 8,\dots$ 也就是按 $2^p$ 来考虑。

这样考虑的话有什么规律呢？我们先观察最后一位，如果最后 $1$ 位是奇数的话会直接被 $1$ 减掉，二进制表示下为 $1$ 的个数必然少 $1$；如果是偶数的话高位会过来补位（如果高位存在的话），这个时候最坏情况下 $1$ 的个数都会不变，那么如果正好是这种最坏情况就说明其上一位必然为 $1$ 那么此时答案应该加上 $2^1$，如果不是最坏呢？那么 $1$ 的个数必然会增加，那么前若干位原先必然为 $0$，注意这个性质可以从低位推广到任意高位。

举个例子如果原先的数是 $26$ 其二进制表示为 $00011010$：

- 首先我们减去 $2^0$，二进制变为 $00011001$，显然 $1$ 的个数没有改变。
- 接着我们减去 $2^1$，二进制变为 $00010111$，$1$ 的个数变多了。

那么 $1$ 的个数变多我们是不需要理会的，因为你从 $1, 2, 4, 8 \dots $ 从小到大一直减一定会把高位的 $1$ 减掉，然后转化成 $1$ 的位数和原来的相等的特殊情况加上 $2^{i+1}$ 即可。

上述推导过程也即是证明过程，最后判断如何找到数直接判断我们得到的答案是多少位的就行了，代码如下：

```
#include <bits/stdc++.h>

using namespace std;

int n;

void solve(){
	cin>>n;
	
	int ans=0,nn=n;
	for(int i=0;i<=30;i++){
		int t;
		cout<<"- "<<(1<<i)<<endl;
		cin>>t;
		
		if(t<n) ans+=1<<i,n=t;
		else if(t==n) ans+=1<<i+1;
		
		int tt=ans,cnt=0;
		while(tt){
			if(tt&1) cnt++;
			tt>>=1;
		}
		
		if(cnt==nn) break;
	}
	
	cout<<"! "<<ans<<endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	cin>>T;
	while(T--) solve();
	return (0-0);
}
```

---

## 作者：Dream__Sky (赞：1)

对于这道题，首先我们要知道：如果给一个数 $n$ 减一，那么在 $n$ 的二进制下，从低位起最后一个 $1$ 后面的所有 $0$ 都会变成 $1$，最后一个 $1$ 会变成 $0$。

举个例子：$n=20,(10100)_2\to(10011)_2$。即，对于任意 $n$，操作 `-1` 会使 $\operatorname{popcount}(n)$ 增加 $\operatorname{lowbit}(n)-1$。知道了这个性质，我们就可以通过每次对原数减一的方式判断每个 $1$。

但是这样操作有一个前提，需要把当前查询的第 $i$ 个 $1$ 后面全部清 $0$，这样才能用我们之前提到的性质。

还是举个例子：$n=20,(10100)_2\to(10011)_2$，现在我们可以推算出，最后一个 $1$ 在哪一位。当我们查询更高一位的 $1$ 时，要把最低两位，即查询上一个时遗留下来的 $1$ 去掉。即 $(10011)_2\to(10000)_2$。如果分两次减，那么操作次数为 $2\times \log_2(n)$，不能通过本题。需要把两次合在一起减去。

可以发现，我们每次其实减去的就是当前查询的这个 $1$ 在二进制中所占的权重。

证明：
设这个 $1$ 在二进制数中的第 $i$ 位。

第一次 $-1$，第二次 $-(2^i-1)$。

共需要 $-1-(2^i-1)=-1-2^i+1=-2^i$。

根据这个思路模拟即可。



---

## 作者：Coffee_zzz (赞：1)

### 题意

有一个不大于 $10^9$ 的正整数 $n$，先告诉你 $n$ 在二进制下 $1$ 的个数；每次操作你可以将 $n$ 减去一个小于等于 $n$ 的整数，接着再告诉你当前的 $n$ 在二进制下 $1$ 的个数。你需要在 $30$ 次操作内计算出 $n$ 的值。

### 分析

$\log _2 10^9 < 30$，每次询问至少需要计算出 $n$ 的一个二进制位。

举个例子，$(100100)_2-1=(100011)_2$，发现这个数减 $1$ 后二进制下 $1$ 的个数增加了 $1$。

我们不妨设原数在二进制下最低的 $1$ 的位置为 $f$（最低位是第 $0$ 位），减 $1$ 后二进制下 $1$ 的个数增加了 $x$，可以得到式子 $f=x+1$。

于是，我们可以通过这个式子，求出 $n$ 在二进制下每一个为 $1$ 的位。

记得每次减的时候不仅要减 $1$，还要减去 $2^f-1$，因为要把上次减 $1$ 得到的末尾的好多 $1$ 减去，即每次减的数为 $2^f$。

若询问得到的 $cnt$ 恰好等于 $f$，说明此时 $n$ 只剩下末尾的好多 $1$ 了，减去 $2^f$ 会导致 $n$ 变为负数，需要及时退出循环。

最后统计一下所有减的数，这些数的和即 $n$。

### 代码

```c++
#include <bits/stdc++.h>

using namespace std;
int cnt[32];
signed main(){
	int t,k,sum,p,f;
	cin>>t;
	for(int temp=0;temp<t;temp++){
		k=0,sum=0,p=1;
		cin>>cnt[k];
		while(cnt[k]){
			cout<<"- "<<p<<endl;
			sum=sum+p;
			cout.flush();
			cin>>cnt[++k];
			f=cnt[k]-cnt[k-1]+1;
			cnt[k]=cnt[k]-f;
			p=pow(2,f);
			if(cnt[k]==0) sum=sum+p-1;
		}
		cout<<"! "<<sum<<endl;
		cout.flush();
	}
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

入门交互。考虑每一次询问出每一个位的值。从低位到高位考虑，若此时当前位的 $1$ 的数量减少 $1$，则说明这一位的值为 $1$，否则直接暴力推算出其下一个 $1$ 的位置。

交互次数为 $\log$ 级别，可以通过。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N = 1000100, mod = 998244353;
int a[N], res[N];
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int cnt, A = 0;
        cin >> cnt;
        int i = 0;
        while (1) {
            cout << "- " << (1ll << i) << endl;
            int x;
            cin >> x;
            for (int j = 0; j < x - cnt + 1; ++j) {
                ++i;
            }
            A |= (1ll << i);
            if (x == i) {
                break;
            }
            cnt = x;
        }
        cout << "! " << A << endl;
    }
    return 0;
}

/*



*/
 
```

---

## 作者：Xiphi (赞：0)

比较牛逼的题。有一道类似的 lowbit 性质的[题](https://www.luogu.com.cn/problem/P8055)，每次减去 lowbit 就相当于把后边若干位 $0$ 都变成 $1$，然后 popcount 就会增加后边若干位 $0$ 的个数减 $1$，这样就能用“知道增量”的方法来求哪一位是 $1$（在原数中）。

然后就可以枚举 lowbit 然后根据增量算每一位有什么数了，然后统计和就没了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,cnt;
int main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>T;
	while(T--){
		cin>>cnt;
		int ans=0,i=0,ls=cnt,x=1919810;
		for(;;){
			cout<<"-"<<' '<<(1<<i)<<endl;
			cin>>x;
			int D=x-ls+1;
			while(D--) i++;
			ans+=1ll<<i;
			if(x==i) break;
			ls=x;
		}
		cout<<'!'<<' '<<ans<<endl;
	}
	return 0;
}




```

---

## 作者：uid_310801 (赞：0)

开始时把原数字 $-1$.

如果 $1$ 的位数刚好减少 $1$ 个说明最低位是 $1$.

否则最低位是 $0$。现在它变成了 $1$，我们需要在下一次把这个 $1$ 减去以防影响我们后续的判断。

保证最低位是 $0$ 了，我们就可以 $-2$（如果需要把上一步的 $1$ 减去就是 $-3$），$-4$......以此类推，重复上述操作直到 $cnt=0$.

答案就是历次询问的总和。

如果最后减去后发现 $1$ 的个数没有减少，但是只剩下 $1$ 个 $1$，那么最后剩余的 $1$ 一定在这一位上，如果再往高问会出现负数，需要跳出循环，并将答案加上 $2^i$.



询问次数为 $\log n$.

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
const ll N=2e3+10;
ll n,m,a[N],t[N],c[N];
void work(){
	ll cnt,ans=0,tmp,i=0,exp=0,exp2=0;
	cin>>cnt;
	while(cnt){
		cout<<"- "<<(1<<i)+exp<<endl;
		cin>>tmp;
		ans+=(1<<i)+exp;
		if(tmp==cnt-1-exp2)	exp=exp2=0;
		else if(tmp==1){
			ans+=(1<<i);
			break;
		}
		else exp=(1<<i),exp2=1;
		cnt=tmp;
		i++;
	}
	cout<<"! "<<ans<<endl;
}
signed main(){
	ll T;
	cin>>T;
	while(T--){
		work();
		
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# CF1780D 题解



## 思路分析

考虑这样的操作：

> 对于 $n=2^k$ 的情况，操作 `- 1` 会使得 $\operatorname{popcount}(n)$ 从 $1$ 变成 $k$。
>
> 同理，对于任意 $n$，操作 `- 1` 会使得 $\operatorname{popcount}(n)$ 增加 $\operatorname{lowbit}(n)-1$。

同理，我们用类似这样的方法，根据 $\operatorname{popcount}(n)$ 的变化量每一次都能求出 $n$ 的下一个 $1$ 位在哪里。

每次询问找到一个 $1$，总询问次数不超过 $\log_2 n$ 次，满足要求。

时间复杂度 $\Theta(\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(int x) {
	cout<<"- "<<x<<endl;
	int ret; cin>>ret; return ret;
}
inline int bit(int x) { return 1<<x; }
inline void solve() {
	int tot;
	cin>>tot;
	int ans=0,lst=0,pre=tot;
	for(int i=1;i<=tot;++i) {
		int now=read(bit(lst));
		int nxt=lst+(now+1-pre);
		ans|=bit(nxt);
		lst=nxt+1,pre=now;
	}
	cout<<"! "<<ans<<endl;
}
signed main() {
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
```



---

## 作者：ztlh (赞：0)

蒟蒻的第一道交互题，赛时吃了一次罚时，拿了 $1066 \text{pts}$。

# Solution

看到操作上限为 $30$，果断想到拆位。

$i$ 从 $0$ 循环到 $29$，每次给原数 $n$ 减去 $2 ^ i$，比较操作前后二进制 $1$ 的数量。

设原数二进制位 $1$ 的个数为 $cnt$，新数为 $cnt'$。观察可知：

- 若 $cnt' < cnt$，则原数中减去的这一位为 $1$；

- 否则该位为 $0$。

但是每次操作后被操作数都会改变，怎么办呢？

只要在下次操作加上就行了！

换言之，只要下一次操作中减去的不是 $2^i$，而是 $2^i - 2^{i-1}$，就可以将上一次操作的更改抵消。

最后统计答案即可。

代码很简单，不放了。

---

