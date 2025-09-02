# [ABC337F] Usual Color Ball Problems

## 题目描述

### 题目翻译

你现在手上有 $n$ 个排成一列的球、 $m$ 个盒子。每个球有一种颜色。

现在你需要对于每个 $0\le x< n$，执行以下操作：

1. 将第一个球移动至序列末尾。该操作将执行 $x$ 次。
2. 从前往后处理每个球，假设当前球的颜色为 $c$。具体地，我们通过以下步骤来把球放到盒子里：
> 1. 如果存在一个非空盒子 $y$，这个盒子里的所有球颜色为 $c$ 并且这个盒子里球的个数小于 $k$，你应当将球放入 $y$ 号盒子中。
>2. 如果不存在 (1) 中所述情况，但是存在一个盒子为空，你应当将球放进一个空盒子里。
> 3. 如果不存在 (1)、(2) 中所述情况，你应当将这个球吃掉。

3. 当序列中没有球之后（所有球都被放进盒子里或吃掉后），输出**盒子里**的球的数量。

询问之间互不影响，所有盒子一开始都是空的。

## 样例 #1

### 输入

```
7 2 2
1 2 3 5 2 5 4```

### 输出

```
3
3
3
4
4
3
2```

## 样例 #2

### 输入

```
20 5 4
20 2 20 2 7 3 11 20 3 8 7 9 1 11 8 20 2 18 11 18```

### 输出

```
14
14
14
14
13
13
13
11
8
9
9
11
13
14
14
14
14
14
14
13```

# 题解

## 作者：yanhao40340 (赞：6)

F>G。纪念一下做出来的 F。

## 分析

题意描述得很复杂，建议先手玩样例来理解题意。

大体思路：破环成链。每次放入新的盒子时计算并累加该盒子对答案的贡献，一直加到盒子用完。然后删去开头的数的贡献，并重复上述过程。

接下来分析实现方法。

因为每个盒子都只能装同一种数，所以我们考虑求出每个盒子装的数及个数。

按顺序从前往后扫过去，如果这个数没有出现过或者装这个数的盒子已经装满了，那么就需要用一个新的盒子。

那么我们记录盒子中出现的数及其个数。如果扫到一个出现次数为 $x$，且 $x  \equiv 1 \pmod k$，就说明需要开一个新盒子。

以上操作可以知道盒子里装了哪些数。接下来就需要求出每种数的个数。

显然，对于一个数 $x$，若其出现次数为 $y$，有 $z$ 个盒子装了这个数，那么它在盒子中出现的次数即为 $\min(y,kz)$。

可以发现，一个数的出现次数只和该数的总数量 $s$ 与该数已经被加入盒中的数量 $t$ 有关，因此我们可以在加入数时直接计算此数新增加的次数 $\min(k,s-t)$。

这样我们就解决了末尾增加的问题，接下来要解决在开头删除的问题。

容易发现，当开头的数在盒子中的个数 $x \equiv 1 \pmod k$，那么就一定有其中一个数是单独装在一个盒子中。此时如果将这个数删去，就可以少用一个盒子。因此我们同样也可以直接在一轮答案统计完后删除开头，并更新当前数据。

时间复杂度：$\Theta(n)$。

## 代码

代码很短（ABC 特色），建议自己敲。已省略快读快输。

```cpp
#include <iostream>
using namespace std;
const int maxn=2e5+5;
int cnt[maxn],a[maxn<<1],f[maxn];
int main(){
	int n=read(),m=read(),k=read();
	for (int i=1;i<=n;++i) a[i]=read(),++f[a[i]],a[n+i]=a[i];
	int now=0,tmp=1,ans=0;
	for (int i=1;i<=n;++i){
		for (;now<m&&tmp<i+n;++tmp){
			++cnt[a[tmp]];
			if ((cnt[a[tmp]]-1)%k==0) // 写成这个样子是防止 k=1 的情况
            ++now,ans+=min(f[a[tmp]]-(cnt[a[tmp]]-1),k);
		}
		write(ans);putchar(10);
		--cnt[a[i]];
		if (cnt[a[i]]%k==0) --now,ans-=min(f[a[i]]-cnt[a[i]],k);
	}
	return 0;
}
```

---

Update on 2024/2/1：补充了删除开头的解释。特别鸣谢 [spards](https://www.luogu.com.cn/user/400072) 大佬对本题解提出的建议。

---

## 作者：Zi_Gao (赞：2)

## 前言

F 居然比 G 难，考场上做完 F 就没时间了，亏大了。但是这场 0 伤通过 A 到 F 还是挺开心的。

## 正文

### 0x00 分析题目

一个基础的观察是，一个盒子里面只有一种颜色的球。继续观察发现这个第一步把球往后放的操作其实就是把球围成一个圈，从不同的地方断开进行操作。于是可以经典操作，断链成环，这样就只需要解决从每个点开始的一段长度为 $n$ 的区间内会发生的事情了。考虑用滑动窗口的方法解决，我这里使用的是从后向前滑动，维护所有盒子的第一个球的下标，以及每种颜色被放入盒子的球的下标。并且可以知道，同一个颜色的球肯定是某个前缀可以放进去，后面都没有放进去。若现在在序列开头加入了一个球，分类讨论一下：

1. 之前这个颜色的球每个都放入了某个盒子中。

   那么在序列开头加入这个颜色的球，肯定还是会有限处理这个颜色的球，相当于把这个的分配方案向前平移了一段，所以这个颜色的球放入的方案不会发生变化，仍然会每个球都能放入某个盒子中，并且弹出最后一个这个颜色的球。但是对于其他颜色的球会不会有影响呢？答案是不会的，正如前文所说这样的情况是在平移这个颜色放入方案，那么其他球并不会被影响到。

2. 之前并不是所有这个颜色的球都放入了盒子中。

   显然这时所有放这个颜色球的盒子都已经装满了，在序列开头加入，必定会优先处理这个颜色，新开一个盒子往里面放。但是与上面一种情况不同的是，这种情况会对其他球的分配方案造成影响，若当前用的盒子超出了限制，自然会导致最后一个开的盒子被踢出去。

### 0x01 代码实现

用一个 `set` 和 $n$ 个 `deque` 实现，分别维护全局每个盒子的第一个球的下标和每种颜色放入盒子的球的下标。

AC CODE

```cpp
#include<bits/stdc++.h>
#define int long long
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

std::set<int> Q;//fir:col sec:id
std::deque<int> QCol[200010];

int cntBox[200010],C[400010],buc[200010],ans[200010];

signed main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    register int i,col,res=0;
    int n=read();
    int m=read();
    int K=read();
    for(i=0;i<n;++i) C[i]=C[i+n]=read();
    if(m>=n){
        for(i=0;i<n;++i) print(n),putchar(' ');
        return 0;
    }
    for(i=n;i<n*2;++i){
        if(cntBox[C[i]]*K>=++buc[C[i]]) ++res;
        else if(Q.size()==m) ;
        else Q.insert(i),QCol[C[i]].push_back(i),++cntBox[C[i]],++res;
    }

    for(i=n-1;~i;--i){
        if(cntBox[C[i]]*K>=buc[C[i]]){
            Q.erase(QCol[C[i]].back()),QCol[C[i]].pop_back();
            Q.insert(i),QCol[C[i]].push_front(i);
        }else{
            res-=cntBox[C[i]]*K;
            Q.insert(i),QCol[C[i]].push_front(i),++cntBox[C[i]];
            res+=std::min(cntBox[C[i]]*K,buc[C[i]]);

            if(Q.size()>m){
                col=C[*std::prev(Q.end())],Q.erase(*std::prev(Q.end()));
                res-=std::min(buc[col],cntBox[col]*K);
                QCol[col].pop_back(),--cntBox[col];
                res+=std::min(buc[col],cntBox[col]*K);
            }
        }

        ans[i]=res;
    }

    for(i=0;i<n;++i) print(ans[i]),putchar('\n');

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```


---

## 作者：ZnPdCo (赞：0)

我们破环成链，发现成为了一个区间问题，容易发现当左端点往右移动，合法的右端点一定是递增的。

所以我们可以做到 $O(n)$，分成多个 $k$ 为一组，右端点不断递增，当总盒子个数超过 $m$ 时，退出递增并输出答案，下次接着递增。

如何判断盒子个数？可以模 $k$，如果原本这个球在区间里的个数模 $k$ 等于 $0$，那么说明这是一个新盒子，盒子个数加一。如果删除后球在区间里的个数模 $k$ 等于 $0$，那么说明这个盒子空了，盒子个数减一。

```c++
/**
 * @file A.cpp 
 * @tag: #AtCoder#ABC#ABC336
 * @author: ZnPdCo
 * @date: 2023-12-23 13:55:50
 * @problem: https://atcoder.jp/contests/abc337/tasks/abc337_f
 **/
#include<bits/stdc++.h>
#include<vector>
#define ll long long
#define N 400010
using namespace std;
void print() {}
template<typename T, typename... Ts>
void print(const T& x, const Ts&... y) {
	cout << x << ' ';
	print(y...);
}
void input() {}
template<typename T, typename... Ts>
void input(T& x, Ts&... y) {
	cin >> x;
	input(y...);
}
ll n, m, k;
ll a[N];
ll type, ans;
ll cnt[N];
vector<ll> num[N];
ll top[N];
int main() {
	input(n, m, k);
	for(ll i = 1; i <= n; i++) {
		num[i].push_back(k);
	}
	for(ll i = 1; i <= n; i++) {
		input(a[i]);
		a[i+n] = a[i];
		if(num[a[i]].back() == k) num[a[i]].push_back(1);
		else {
			ll x = num[a[i]].back();
			num[a[i]].pop_back();
			num[a[i]].push_back(x+1);
		}
	}
	ll r = 1;
	for(ll l = 1; l <= n; l++) {
		while(r < 2*n) {
			if(cnt[a[r]] % k == 0) {
				type++;
				ans += num[a[r]][++top[a[r]]];
			}
			cnt[a[r]]++;
			if(type > m) break;
			r++;
		}
		if(r < 2*n) {
			cnt[a[r]]--;
			if(cnt[a[r]] % k == 0) {
				type--;
				ans -= num[a[r]][top[a[r]]--];
			}
		}
		
		
		
		print(ans);
		putchar('\n');
		
		
		cnt[a[l]]--;
		if(cnt[a[l]] % k == 0) {
			type--;
			ans -= num[a[l]][top[a[l]]--];
		}
	}
}
```



---

